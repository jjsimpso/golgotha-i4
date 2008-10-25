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
 

#ifndef __LIST_PICK_HH
#define __LIST_PICK_HH

#include "window/window.hh"
class i4_menu_item_class;

class i4_list_pick : public i4_parent_window_class
{
  w32 total_items;
  i4_menu_item_class **items;
  i4_color background;
  w32 length;
  w32 scroll_event_id;
  sw32 start,end;
  i4_bool need_draw_all, free_items;

public:
  char *name() { return "list_pick"; }
  
  i4_list_pick(w16 width, w16 height,
               w32 total_items,
               i4_menu_item_class **items,
               w32 scroll_event_id,
               i4_color background,
               i4_bool free_item=i4_T);

  ~i4_list_pick();

  virtual void reposition_start(w32 new_start);
  
  virtual void parent_draw(i4_draw_context_class &context);
  virtual void draw(i4_draw_context_class &context);

  virtual void receive_event(i4_event *ev);
};


#endif

