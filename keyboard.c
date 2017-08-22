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
#include <X11/Xlib.h>

extern Display *disp;
extern KeySym *ORIGINAL, *KEYMAP, *OLDKEYMAP;
extern int MIN_CODE, MAX_CODE, KEYCODES, SYMS_PER_CODE;
extern int GREEK[4][30][3];
extern int quote_flag;

void
apply_map (int map_id)
{
  int keycode, aa, i;

  memcpy (KEYMAP, ORIGINAL, KEYCODES * SYMS_PER_CODE * sizeof (KeySym));

  if (map_id >= 0)
    for (i = 0; i < 30; i++)
      {
	keycode = GREEK[map_id][i][0];
	aa = keycode - MIN_CODE;
	KEYMAP[aa * SYMS_PER_CODE] = GREEK[map_id][i][1];
	KEYMAP[aa * SYMS_PER_CODE + 1] = GREEK[map_id][i][2];
      }

  for (i = MIN_CODE; i <= MAX_CODE; i++)
    if (KEYMAP[(i - MIN_CODE) * SYMS_PER_CODE] !=
	OLDKEYMAP[(i - MIN_CODE) * SYMS_PER_CODE]
	|| KEYMAP[(i - MIN_CODE) * SYMS_PER_CODE + 1] !=
	OLDKEYMAP[(i - MIN_CODE) * SYMS_PER_CODE + 1])
      XChangeKeyboardMapping (disp, i, SYMS_PER_CODE,
			      &KEYMAP[(i - MIN_CODE) * SYMS_PER_CODE], 1);

  XSync (disp, False);

  memcpy (OLDKEYMAP, KEYMAP, KEYCODES * SYMS_PER_CODE * sizeof (KeySym));

  if (map_id == -1) quote_flag = 0;
}
