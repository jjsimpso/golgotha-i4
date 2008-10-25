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
 

#include "video/win32/dx_cursor.hh"
#include "video/win32/dx5_util.hh"
#include <ddraw.h>

// base class that you should derive from
// this class will call at the appropriate times :
//    remove(), save(), and display()
// these should use the 'cursor' i4_image type to draw with

class ddraw_thread_cursor_class : public dx_threaded_mouse_class
{  
  public:  
  
  i4_dx5_image_class *mouse_save;

  ddraw_thread_cursor_class(const i4_pal *screen_pal,
                            HWND window_handle,
                            sw32 clip_x1, sw32 clip_y1,
                            sw32 clip_x2, sw32 clip_y2);

  void set_cursor(i4_cursor_class *cursor);

  i4_bool use_back_buffer;

  void use_backbuffer(i4_bool use);

  void remove();
  void save();
  void display();  
};
