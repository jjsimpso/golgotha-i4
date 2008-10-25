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

#ifndef __GOLGOTHA_SVGALIB_INPUT_HH
#define __GOLGOTHA_SVGALIB_INPUT_HH

#include "device/device.hh"
#include "time/time.hh"

class i4_display_class;

class i4_svgalib_input_class : public i4_device_class
{
private:
  unsigned int max_scancode;
  void get_scancode_info();
  void create_scancode_map();
  w16 *scancode_map;
  char *scancode_press_state;
  void create_scancode_press_state();
  int mouse_buttons, old_mouse_buttons;
  i4_time_class last_up[3], last_down[3];
  i4_bool use_mouse;
  sw32 new_mouse_x, new_mouse_y;
  w32 width, height;
  float mouse_scale; // nasty hack

public:
  i4_bool mouse_locked;
  w16 modifier_state;
  sw32 mouse_x, mouse_y;
  i4_bool console_opened;

  void mousehandler(int buttonstate, int dx, int dy, int dz, int drx, int dry, int drz);

  char *name() { return "SVGALIB input"; }

  virtual i4_bool process_events();

  i4_bool lock_mouse_in_place(i4_bool yes_no)
  {
    mouse_locked = yes_no;
    return i4_T;
  }

  i4_bool open_console(w32 w, w32 h);

  void close_console();

  i4_bool console_open;

  i4_svgalib_input_class();
  ~i4_svgalib_input_class();

};

#endif // __GOLGOTHA_SVGALIB_INPUT_HH,
