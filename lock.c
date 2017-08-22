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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>

void
do_lock ()
{
  int fd;
  umask (0111);
  fd = creat ("/tmp/grkbd.lock", 0666);
  if (fd == -1)
    {
      perror ("/tmp/grkbd.lock");
      exit (0);
    }
  if (flock (fd, LOCK_EX | LOCK_NB))
    {
      fprintf (stderr,
	       "Probably there is already one instance of GRkbd running...\n");
      exit (0);
    }
}
