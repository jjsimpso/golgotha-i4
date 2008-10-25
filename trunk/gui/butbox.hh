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
 

#ifndef __BUTBOX_HPP_
#define __BUTBOX_HPP_

#include "window/window.hh"
#include "gui/button.hh"

class i4_button_box_class : public i4_menu_item_parent_class
{
  i4_event_handler_class *receiver;
  i4_button_class *current_down;
  i4_bool require_one_down;

  void expand_if_needed();

  // I made this private so you have to call add_button
  virtual void add_child(i4_coord x, i4_coord y, i4_window_class *child);

public:
  char *name() { return "button_box"; }

  i4_button_box_class(i4_event_handler_class *receiver,
                      i4_bool require_one_down=i4_T);

  void parent_draw(i4_draw_context_class &context);

  virtual void add_button(i4_coord x, i4_coord y, i4_button_class *child);

  virtual void note_reaction_sent(i4_menu_item_class *who,       // this is who sent it
                                  i4_event_reaction_class *ev,   // who it was to 
                                  i4_menu_item_class::reaction_type type); 

  
  void push_button(i4_button_class *which, i4_bool send_event);

  // arranges child windows from left to right then down, also enlarges self to
  // fit this arrangement order
  virtual void arrange_right_down();

  // arranges child windows from top to bottom then right, also enlarges self to
  // fit this arrangement order
  virtual void arrange_down_right();
} ;


#endif
