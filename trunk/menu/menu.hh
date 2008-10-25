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
 

#ifndef __MENU_HPP_
#define __MENU_HPP_

#include "window/window.hh"
#include "error/error.hh"
#include "menu/menuitem.hh"
#include "string/string.hh"

class i4_menu_class : public i4_menu_item_parent_class
{
  // when a menu_item sends it's a press event should the menu hide itself?
  i4_bool           hide_on_pick;  
  i4_bool           deleted;             // debugging tool so we can see if we already got events

  i4_event_handler_class *focus_inform;
public:

  virtual void notify_focus_change(i4_event_handler_class *who)
  { focus_inform=who; }

  // show should make the menu visible on the screen
  virtual void show(i4_parent_window_class *show_on, i4_coord x, i4_coord y) = 0;

  virtual void hide() = 0;

  // apps should call hide() before add_item()
  virtual void add_item(i4_menu_item_class *item);
  
  virtual void receive_event(i4_event *ev);

  i4_menu_class(i4_bool hide_on_pick) 
    : hide_on_pick(hide_on_pick)
  {
    focus_inform=0;
    deleted=i4_F;
  }
  virtual ~i4_menu_class();


  virtual void add_child(i4_coord x, i4_coord y, i4_window_class *child)
  { i4_error("use add_item"); }

  virtual void note_reaction_sent(i4_menu_item_class *who,       // this is who sent it
                                  i4_event_reaction_class *ev,   // who it was to 
                                  i4_menu_item_class::reaction_type type);
} ;

class i4_menu_focus_event_class : public i4_object_message_event_class
{
public:
  enum focus_state_type { got_focus, lost_focus } focus_state;
  i4_window_class *lost_to;

  i4_menu_focus_event_class(i4_menu_class *menu,
                            focus_state_type state,
                            i4_window_class *lost_to)
    :  i4_object_message_event_class(menu),
       focus_state(state),
       lost_to(lost_to)
  {}

  virtual i4_event  *copy() 
  { 
    return new i4_menu_focus_event_class((i4_menu_class *)object,
                                              focus_state,
                                              lost_to); 
  }
  
  char *name() { return "menu lost focus"; }
};


#endif
