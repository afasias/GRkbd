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
#include <string.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "grimage.xpm"
#include "ukimage.xpm"

extern Display *disp;
extern Window win;
extern int depth;
extern XImage *image;
extern GC gc;
extern Colormap colormap;

extern int WIDTH;
extern int HEIGHT;

unsigned long
alloc_color (unsigned long R, unsigned long G, unsigned long B)
{
  XColor aColor;

  switch (depth)
    {
    case 8:
      aColor.red = R << 8;
      aColor.green = G << 8;
      aColor.blue = B << 8;
      XAllocColor (disp, colormap, &aColor);
      return aColor.pixel;

    case 16:
      return ((R & 0xF8) << 8) + ((G & 0xFC) << 3) + ((B & 0xF8) >> 3);

    case 24:
      return (R << 16) + (G << 8) + (B);
    }
  return 0;
}

void
find_max_size ()
{
  int w1, h1, w2, h2;
  sscanf (grimage_xpm[0], "%d %d", &w1, &h1);
  sscanf (ukimage_xpm[0], "%d %d", &w2, &h2);
  WIDTH = (w1 > w2 ? w1 : w2);
  HEIGHT = (h1 > h2 ? h1 : h2);
}



static int uk_width, uk_height, uk_colors, uk_cpp;
static int gr_width, gr_height, gr_colors, gr_cpp;
static unsigned long *gr_map;
static unsigned long *uk_map;

static void
analyze_xpm (char **data, unsigned long *map, int *width, int *height,
	     int *colors, int *cpp)
{
  int red, green, blue, i;
  char st[20], fmt[40];
  char bit;
  unsigned char ch[2];

  sscanf (data[0], "%d %d %d %d", width, height, colors, cpp);
  if (*cpp > 2)
    {
      fprintf (stderr,
	       "XPM file uses more than 2 characters per pixel and cannot be handled by grkbd.\n");
      fprintf (stderr,
	       "Reduce the number of colors of your images ( #colors < 8000 )\n");
      exit (0);
    }
  bit = (*cpp == 1 ? 1 : 0);

  sscanf (data[(*colors)], "%*s %*c #%s", st);

  strcpy (fmt, bit ? "%c %*c " : "%c%c %*c ");
  strcat (fmt,
	  strlen (st) == 6 ? "#%02x%02x%02x" : "#%02x%*02x%02x%*02x%02x");

  for (i = 0; i < (*colors); i++)
    {
      if (bit)
	{
	  sscanf (data[i + 1], fmt, ch, &red, &green, &blue);
	  map[ch[0]] = alloc_color (red, green, blue);
	}
      else
	{
	  sscanf (data[i + 1], fmt, ch, ch + 1, &red, &green, &blue);
	  map[(ch[0] << 8) + ch[1]] = alloc_color (red, green, blue);
	}
    }
}

void
analyze_xpms ()
{
  if (!(gr_map = (unsigned long *) malloc (65536 * sizeof (unsigned long))))
    {
      perror ("malloc: gr_map");
      exit (0);
    }
  if (!(uk_map = (unsigned long *) malloc (65536 * sizeof (unsigned long))))
    {
      perror ("malloc: uk_map");
      exit (0);
    }
  analyze_xpm (grimage_xpm, gr_map, &gr_width, &gr_height, &gr_colors,
	       &gr_cpp);
  analyze_xpm (ukimage_xpm, uk_map, &uk_width, &uk_height, &uk_colors,
	       &uk_cpp);
}

void
set_flag (int flag)
{
  char **data;
  int width, height, colors, cpp;
  unsigned long *map;
  int i, j;
  char bit;

  if (flag)
    {
      data = grimage_xpm;
      width = gr_width;
      height = gr_height;
      colors = gr_colors;
      map = (unsigned long *) gr_map;
      cpp = gr_cpp;
    }
  else
    {
      data = ukimage_xpm;
      width = uk_width;
      height = uk_height;
      colors = uk_colors;
      map = (unsigned long *) uk_map;
      cpp = uk_cpp;
    }

  bit = (cpp == 1 ? 1 : 0);

  for (i = 0; i < width; i++)
    for (j = 0; j < height; j++)
      XPutPixel (image, i, j,
		 bit ? map[(int) (data[colors + 1 + j][i])] :
		 map[(data[colors + 1 + j][i * 2] << 8) +
		     data[colors + 1 + j][i * 2 + 1]]);

  XPutImage (disp, win, gc, image, 0, 0, 0, 0, width, height);
  XSync (disp, False);
}
