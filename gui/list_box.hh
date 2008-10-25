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
 

#ifndef I4_LIST_BOX_HH
#define I4_LIST_BOX_HH

#include "window/window.hh"
#include "memory/array.hh"
#include "menu/menu.hh"

class i4_button_class;
class i4_font_class;
class i4_graphical_style_class;
class i4_deco_window_class;
class i4_list_pull_down_class;

class i4_list_box_class : public i4_menu_class
{
  i4_button_class *down;
  i4_array<i4_menu_item_class *> entries;
  i4_menu_item_class *top;
  i4_list_pull_down_class *pull_down;
  i4_graphical_style_class *style;
  int current;
  i4_parent_window_class *root_window;
  w32 l,r,t,b;
  void set_top(i4_menu_item_class *item);

public:
  int get_current() { return current; }
  i4_menu_item_class *get_current_item() { return entries[current]; }
  i4_list_box_class(w16 width,                               // height is determined by first item
                    i4_graphical_style_class *style,         // uses normal font if none specified
                    i4_parent_window_class *root_window);
  ~i4_list_box_class();

  void add_item(i4_menu_item_class *item);
  void set_current_item(int entry_num);

  void show(i4_parent_window_class *show_on, i4_coord x, i4_coord y);
  void hide();
  void receive_event(i4_event *ev);
  void note_reaction_sent(i4_menu_item_class *who,       // this is who sent it
                          i4_event_reaction_class *ev,   // who it was to 
                          i4_menu_item_class::reaction_type type);

  void parent_draw(i4_draw_context_class &context);

  char *name() { return "list_box"; }
};


#endif
