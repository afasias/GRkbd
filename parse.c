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

extern int WIN;
extern char *DISPLAY;
extern long int geo_x, geo_y;
extern int first_row, last_row;
extern int lock;


void
parse (int argc, char **argv)
{
  int i;

  WIN = 1;
  first_row = 0;
  last_row = 7;
  lock = 1;

  for (i = 1; i < argc; i++)
    {
      if (strcmp (argv[i], "-nowin") == 0)
	{
	  WIN = 0;
	}
      else if (strcmp (argv[i], "-altgr") == 0)
	{
	  first_row = 2;
	  last_row = 9;
	}
      else if (strcmp (argv[i], "-nolock") == 0)
	{
	  lock = 0;
	}
      else if (strcmp (argv[i], "-display") == 0)
	{
	  if (i + 1 >= argc)
	    {
	      fprintf (stderr, "%s: syntax error after -display\n", argv[0]);
	      exit (0);
	    }
	  i++;
	  DISPLAY = argv[i];
	}
      else if (strcmp (argv[i], "-geometry") == 0)
	{
	  if (i + 1 >= argc)
	    {
	      fprintf (stderr, "%s: syntax error after -geometry\n", argv[0]);
	      exit (0);
	    }
	  i++;
	  if (sscanf (argv[i], "%ld%ld", &geo_x, &geo_y) < 2)
	    {
	      fprintf (stderr, "%s: invalid argument after -geometry\n",
		       argv[0]);
	      exit (0);
	    }
	}
      else
	{
	  fprintf (stderr, "%s: invalid argument %s\n", argv[0], argv[i]);
	  exit (0);
	}
    }
}
