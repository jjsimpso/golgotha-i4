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
 

#ifndef __BUTTON_HPP_
#define __BUTTON_HPP_

#include "menu/menuitem.hh"
#include "window/style.hh"
#include "time/timedev.hh"

class i4_button_class : public i4_menu_item_class
{
  protected :

  i4_window_class *decore;
  i4_bool grabbing;
  i4_bool repeat_down;
  i4_bool popup;

  enum { WAIT_CLICK, WAIT_DELAY, WAIT_REPEAT } state;
  i4_time_device_class::id time_id;
  i4_event_reaction_class *repeat_event;

  public :
  char *name() { return "button_class"; }
  i4_button_class(const i4_const_str *idle_context_help,  // can be null
                  i4_window_class *child,
                  i4_graphical_style_class *hint,
                  i4_event_reaction_class *press=0,
                  i4_event_reaction_class *depress=0,
                  i4_event_reaction_class *activate=0,
                  i4_event_reaction_class *deactivate=0      );

  virtual void reparent(i4_image_class *draw_area, i4_parent_window_class *parent);
  virtual void receive_event(i4_event *ev);
  virtual void parent_draw(i4_draw_context_class &context);

  void set_repeat_down(i4_bool value, i4_event_reaction_class *repeat_event=0);
  void set_popup(i4_bool value);
    
  i4_menu_item_class *copy() { return new i4_button_class(context_help, 
                                                          get_nth_window(0),
                                                          hint,
                                                          send.press, send.depress,
                                                          send.activate, send.deactivate); }

  ~i4_button_class();
} ;

#endif


