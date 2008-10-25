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
 

#include "video/glide/glide_display.hh"
#include "video/x11/x11_input.hh"


class i4_x11_glide_display_class : public i4_glide_display_class
{
public:
  x11_input_class input;
  virtual i4_device_class *local_devices() { return &input; }
  virtual void destroy_window() {  input.destroy_window(); }
  virtual i4_bool create_window()
  {
    int depths_to_try[] = { 32, 24, 16, 15, 8, 0 };
    int i=0;

    while (depths_to_try[i]) {
      if (
	  input.create_window(0,0,tmp.xres, tmp.yres, this, i4_F,
			      input.find_visual_with_depth(depths_to_try[i]))
	  )
	return i4_T;

      i++;
    }

    return i4_F;
  }

  virtual void get_mouse_pos(sw32 &mouse_x, sw32 &mouse_y)
  {
    mouse_x=input.mouse_x;
    mouse_y=input.mouse_y;
  }

  virtual i4_bool lock_mouse_in_place(i4_bool yes_no)
  {
    return input.lock_mouse_in_place(yes_no);
  }

};

i4_x11_glide_display_class i4_x11_glide_display_instance;
