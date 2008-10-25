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
 

#ifndef I4_PULL_HH
#define I4_PULL_HH


#include "menu/menu.hh"
#include "window/style.hh"

class i4_pull_menu_class : public i4_menu_class
{  
  win_list sub_menus;
  i4_parent_window_class *root;
  i4_menu_item_class *active_top;
  i4_menu_class *active_sub;
  i4_graphical_style_class *style;

  i4_bool sub_focused, focused;
  i4_bool watching_mouse;

  void unwatch();
  void watch();

public:
  i4_color_hint_class menu_colors;

  i4_pull_menu_class(i4_graphical_style_class *style, 
                     i4_parent_window_class *root_window);

  ~i4_pull_menu_class();

  virtual void resize(w16 new_width, w16 new_height);
  virtual void reparent(i4_image_class *draw_area, i4_parent_window_class *parent);

  virtual void note_reaction_sent(i4_menu_item_class *who,       // this is who sent it
                                  i4_event_reaction_class *ev,   // who it was to 
                                  i4_menu_item_class::reaction_type type);

  virtual void receive_event(i4_event *ev);
  virtual void parent_draw(i4_draw_context_class &context);

  void add_sub_menu(i4_menu_item_class *name,
                   i4_menu_class *sub_menu);

  void show_active(i4_menu_item_class *who);
  void hide_active();
  
  virtual void hide();

  void show(i4_parent_window_class *show_on, i4_coord _x, i4_coord _y)
  {
    show_on->add_child(_x, _y, this);
  }

  char *name() { return "pull_menu"; }
};


#endif
