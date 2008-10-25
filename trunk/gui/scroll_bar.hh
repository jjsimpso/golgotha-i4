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
 

#ifndef SCROLL_BAR_HH
#define SCROLL_BAR_HH

#include "device/event.hh"
#include "window/window.hh"

class i4_button_class;
class i4_graphical_style_class;

class i4_scroll_message : public i4_user_message_event_class
{
public:
  sw32 amount;
  sw32 scroll_total;

  i4_scroll_message(sw32 amount, sw32 scroll_total, w32 id)
    : i4_user_message_event_class(id),
      amount(amount), scroll_total(scroll_total)

  {}

  virtual i4_event *copy() { return new i4_scroll_message(amount, scroll_total, sub_type); } 
};



class i4_scroll_button;

class i4_scroll_bar : public i4_parent_window_class        // up-down scroll bar
{
  friend class i4_scroll_button;
  i4_graphical_style_class *style;
  w32 total_scroll_objects, total_visible_objects;
  i4_button_class *up_but, *down_but, *left_but, *right_but;
  i4_scroll_button *scroll_but;
  i4_parent_window_class *scroll_area;
  w32 id,pos;
  i4_event_handler_class *send_to;
  i4_bool vertical;

  i4_button_class *create_button(i4_button_class *&b, i4_image_class *im);
public:
  void send_position();
  void set_bar_pos(sw32 pos);
  void calc_pos();
  void set_new_total(int total);              // if total items under control changes
  i4_scroll_bar(i4_bool vertical,
                int max_dimention_size,      // width/height depending on vertical
                int total_visible_objects,   // used to determine scroll bar dragger size
                int total_scroll_objects,    // total number of objects that will be scrolled
                w32 message_id,
                i4_event_handler_class *send_to,
                i4_graphical_style_class *style);

  virtual void receive_event(i4_event *ev);

  char *name() { return "vscroll_bar"; }
};


#endif


