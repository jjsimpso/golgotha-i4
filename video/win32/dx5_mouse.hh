/********************************************************************** 

    Golgotha Forever - A portable, free 3D strategy and FPS game.
    Copyright (C) 1999 Golgotha Forever Developers

    Sources contained in this distribution were derived from
    Crack Dot Com's public release of Golgotha which can be
    found here:  http://www.crack.com

    All changes and new works are licensed under the GPL:

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    For the full license, see COPYING.

***********************************************************************/
 

#ifndef DX5_MOUSE_HH
#define DX5_MOUSE_HH

#include "video/win32/dx5_util.hh"
#include "window/cursor.hh"

class i4_cursor_class;

class dx5_mouse_class
{
  struct save_struct
  {
    i4_dx5_image_class *save_buffer;
    int x,y;
    save_struct() { save_buffer=0; }

    ~save_struct()
    {
      if (save_buffer)
        delete save_buffer;
      save_buffer=0;
    }
  } 
  current, last;

  i4_cursor_class cursor;
  i4_bool page_flipped;

public:
  dx5_mouse_class(i4_bool page_flipped);

  virtual void save_and_draw(int x, int y);
  virtual void restore();
  virtual void set_cursor(i4_cursor_class *cursor);

  virtual ~dx5_mouse_class();
} ;


#endif
