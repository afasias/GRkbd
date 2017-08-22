/* GRkbd 1.4 - Greek keyboard for the X Window System
 * Copyright (C) 1998-2007 Giannis Tsakiris
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * You can contact the author by e-mail at: giannis.tsakiris@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define FORK

#define MESSAGE	"GRkbd 1.4  Linux  June 2007  Giannis Tsakiris\n"

int WIDTH;
int HEIGHT;

#define EN_TEXT "EN - grkbd"
#define GR_TEXT "GR - grkbd"

#define IS_DOWN(MAP,CODE)	(int)((MAP[CODE/8]>>(CODE%8))&1)

char *DISPLAY = NULL;
long int geo_x = 0, geo_y = 0;
int first_row, last_row;
int lock;

Display *disp;
KeySym *ORIGINAL, *KEYMAP, *OLDKEYMAP;
int MIN_CODE, MAX_CODE, KEYCODES, SYMS_PER_CODE, WIN;
int cur_lang = 0, cur_state = 0, flag = 1;

Window root, win;
Visual *visual;
int depth, black, white, screen;
XImage *image;
char *img;
GC gc;
XEvent event;
XSizeHints wmhints;
Colormap colormap;
unsigned long RootWidth, RootHeight;
int quote_flag = 0;

extern int deadkeys[9][7];

void parse (int argc, char **argv);
void set_quotes (int state);
void do_lock ();
void find_max_size ();
void analyze_xpms ();
void set_flag (int flag);
void apply_map (int map_id);

int
main (int argc, char **argv)
{
  unsigned char CUR_MAP[32], PREV_MAP[32];
  int i, code, is_dead, keypress;

  fprintf (stderr, MESSAGE);

  parse (argc, argv);

  if (lock)
    do_lock ();

  set_quotes (0);

  if ((disp = XOpenDisplay (DISPLAY)) == NULL)
    {
      fprintf (stderr, "cannot open display\n");
      exit (0);
    }

  if (WIN)
    {
      root = DefaultRootWindow (disp);
      screen = DefaultScreen (disp);
      visual = DefaultVisual (disp, screen);
      depth = DefaultDepth (disp, screen);
      black = BlackPixel (disp, screen);
      white = WhitePixel (disp, screen);
      colormap = DefaultColormap (disp, screen);
      RootWidth = DisplayWidth (disp, screen);
      RootHeight = DisplayHeight (disp, screen);

      find_max_size ();

      if (geo_x < 0)
	geo_x += (RootWidth - WIDTH);
      if (geo_y < 0)
	geo_y += (RootHeight - HEIGHT);
    }

  XDisplayKeycodes (disp, &MIN_CODE, &MAX_CODE);
  XSync (disp, False);
  KEYCODES = MAX_CODE - MIN_CODE + 1;
  ORIGINAL = XGetKeyboardMapping (disp, MIN_CODE, KEYCODES, &SYMS_PER_CODE);
  XSync (disp, False);

  if (
      (KEYMAP =
       (KeySym *) malloc (KEYCODES * SYMS_PER_CODE * sizeof (KeySym))) ==
      NULL)
    {
      perror ("malloc: KeySym");
      exit (0);
    }
  if (
      (OLDKEYMAP =
       (KeySym *) malloc (KEYCODES * SYMS_PER_CODE * sizeof (KeySym))) ==
      NULL)
    {
      perror ("malloc: KeySym");
      exit (0);
    }


#ifdef FORK
  switch (fork ())
    {
    case 0:
      break;
    case -1:
      perror ("fork");
    default:
      exit (0);
    }
#endif

  memcpy (OLDKEYMAP, ORIGINAL, KEYCODES * SYMS_PER_CODE * sizeof (KeySym));

  if (WIN)
    {
      win =
	XCreateSimpleWindow (disp, root, geo_x, geo_y, WIDTH, HEIGHT, 0,
			     black, black);
      XStoreName (disp, win, EN_TEXT);

      wmhints.flags = PSize | PMinSize | PMaxSize | USPosition;
      wmhints.x = 10;
      wmhints.y = 10;
      wmhints.width = wmhints.min_width = wmhints.max_width = WIDTH;
      wmhints.height = wmhints.min_height = wmhints.max_height = HEIGHT;
      XSetNormalHints (disp, win, &wmhints);

      XMapWindow (disp, win);

      gc = XCreateGC (disp, win, 0, NULL);

      img = (char *) malloc (WIDTH * HEIGHT * 4);
      image =
	XCreateImage (disp, visual, depth, ZPixmap, 0, (char *) img, WIDTH,
		      HEIGHT, 32, 0);

      XSelectInput (disp, win, ExposureMask | ButtonPressMask);

      analyze_xpms ();
      set_flag (0);
    }

  XQueryKeymap (disp, PREV_MAP);
  XSync (disp, False);

  while (1)
    {
      if (XPending (disp))
	{
	  XNextEvent (disp, &event);
	  switch (event.type)
	    {
	    case Expose:
	      XPutImage (disp, win, gc, image,
			 event.xexpose.x, event.xexpose.y,
			 event.xexpose.x, event.xexpose.y,
			 event.xexpose.width, event.xexpose.height);
	      XSync (disp, False);
	      continue;

	    case ButtonPress:
	      cur_lang = 1 - cur_lang;
	      cur_state = 0;
	      flag = 1;
	      if (cur_lang == 1)
		apply_map (cur_state);
	      else
		apply_map (-1);
	      
	      set_flag (cur_lang);
	      XStoreName (disp, win, cur_lang ? GR_TEXT : EN_TEXT);
	      XSync (disp, False);
	      continue;
	    }
	}

      usleep (10000);
      XQueryKeymap (disp, CUR_MAP);
      XSync (disp, False);
      if (memcmp (CUR_MAP, PREV_MAP, 32) == 0)
	continue;

      is_dead = 0;
      keypress = 0;
      for (code = MIN_CODE; code <= MAX_CODE; code++)
	if (IS_DOWN (CUR_MAP, code) - IS_DOWN (PREV_MAP, code) == 1)
	  {
	    if ((code == 50 || code == 62) && !flag)
	      continue;
	    keypress = 1;

	    for (i = first_row; i < last_row; i++)
	      if (((cur_lang == deadkeys[i][0]) || (deadkeys[i][0] == -1)) &&
		  (code == deadkeys[i][1]) &&
		  ((deadkeys[i][2] && IS_DOWN (CUR_MAP, deadkeys[i][2]))
		   || (!deadkeys[i][2])))
		{
		  is_dead = 1;
		  if (cur_lang != deadkeys[i][3])
		    {
		      if (WIN)
			{
			  set_flag (deadkeys[i][3]);
			  XStoreName (disp, win,
				      deadkeys[i][3] ? GR_TEXT : EN_TEXT);
			  XSync (disp, False);
			}
		    }
		  cur_lang = deadkeys[i][3];
		  cur_state &= deadkeys[i][4];
		  cur_state ^= deadkeys[i][5];
		  flag = deadkeys[i][6];

		  if (cur_lang == 1)
		    apply_map (cur_state);
		  else
		    apply_map (-1);

		  break;
		}
	    break;
	  }

      if (cur_lang == 1 && keypress && code == 48 && (IS_DOWN(CUR_MAP,50) == 1 || IS_DOWN(CUR_MAP,62) == 1))
	{
	  set_quotes (quote_flag = quote_flag ? 0 : 1);
	  apply_map (cur_state);
	}

      if (keypress && !is_dead && !flag)
	{
	  cur_state = 0;
	  flag = 1;

	  if (cur_lang == 1)
	    apply_map (cur_state);
	  else
	    apply_map (-1);
	}

      memcpy (PREV_MAP, CUR_MAP, 32);
    }
}
