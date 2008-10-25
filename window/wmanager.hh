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
 

#ifndef __WMANAGER_HPP_
#define __WMANAGER_HPP_

#include "window/window.hh"
#include "video/display.hh"
#include "palette/pal.hh"
#include "string/string.hh"
#include "window/style.hh"
#include "loaders/load.hh"
#include "device/keys.hh"

class i4_window_manager_class : public i4_parent_window_class
{
private:
  i4_display_class *display;
  i4_device_class::device_flags devices_present;
  i4_graphical_style_class *style;
  i4_cursor_class *default_cursor;
  i4_bool no_cursor_installed;  // set to true when cursor is not the default cursor
  i4_bool drag_dropping; 
  i4_color background_color;
  void cleanup_old_mode();

  struct
  {
    i4_bool active;
    w32 reference_id;
    void *further_info;
    i4_window_class *originator;
  } drag_drop;

public:
  int key_modifiers_pressed;

  void set_background_color(w32 color);
  i4_bool control_pressed() { return (key_modifiers_pressed & I4_MODIFIER_CTRL) ? i4_T : i4_F; }
  i4_bool alt_pressed() { return (key_modifiers_pressed & I4_MODIFIER_ALT) ? i4_T : i4_F; }
  i4_bool shift_pressed() { return (key_modifiers_pressed & I4_MODIFIER_SHIFT) ? i4_T : i4_F; }

  char *name() { return "window_manager"; }

  i4_graphical_style_class *get_style();

  virtual void parent_draw(i4_draw_context_class &context);

  virtual void root_draw();     // call from application, will call everyone else's draw function
  virtual void receive_event(i4_event *ev);

  i4_window_manager_class();     // if style cannot be found the first available on is used instead

  i4_menu_class *create_menu(i4_color_hint_class *hint, i4_bool hide_on_pick)
  { return style->create_menu(hide_on_pick); }

  void set_default_cursor(i4_cursor_class *cursor);

  void prepare_for_mode(i4_display_class *display, i4_display_class::mode *mode);

  i4_color i4_read_color_from_resource(char *resource);

  ~i4_window_manager_class(); 
};


#endif
