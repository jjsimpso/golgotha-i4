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
 

#ifndef __DIVIDER_HH
#define __DIVIDER_HH

#include "window/window.hh"
#include "device/device.hh"

class i4_graphical_style_class;

class i4_divider_class : public i4_parent_window_class
{
  i4_event_handler_reference_class<i4_window_class> w1,w2;
  i4_bool split_up_down;
  i4_graphical_style_class *style;
  int split_value, min1, min2;

  i4_bool dragging, w_attached, h_attached;
  

  void get_drag_area(int &x1, int &y1, int &x2, int &y2);
  virtual void reparent(i4_image_class *draw_area, i4_parent_window_class *parent);
public:
  void resize(w16 new_width, w16 new_height);

  i4_divider_class(int w, int h,               // -1 uses parent w or height
                   i4_bool split_up_down,
                   int split_x_or_y,           // -1 splits the middle
                   i4_window_class *window1,
                   i4_window_class *window2,
                   i4_graphical_style_class *style,
                   int window1_min_size=1,
                   int window2_min_size=1);

  void parent_draw(i4_draw_context_class &context);
  void receive_event(i4_event *ev);
  char *name() { return "divider"; }
};

#endif
