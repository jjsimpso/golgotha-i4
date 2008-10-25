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
 

#ifndef I4_BROWSE_TREE_HH
#define I4_BROWSE_TREE_HH


#include "window/window.hh"
#include "menu/menuitem.hh"
#include "error/error.hh"

class i4_graphical_style_class;

class i4_browse_window_class : public i4_parent_window_class
{
public:
  char *name() { return "browse_window"; }

  i4_bool expanded;
  i4_parent_window_class *title_area;
  i4_window_class *child_object, *toggle_button;

  i4_graphical_style_class *style;

  i4_browse_window_class(i4_graphical_style_class *style,
                         i4_window_class *title_object,
                         i4_window_class *child_object,
                         i4_bool show_plus_minus,
                         i4_bool expanded);


  virtual void compress();
  virtual void expand();


  void add_arranged_child(i4_window_class *child);
  virtual void replace_object(i4_window_class *object);
  virtual sw32 x_start();
  virtual void receive_event(i4_event *ev);
  virtual void parent_draw(i4_draw_context_class &context);
};


class i4_vertical_compact_window_class : public i4_parent_window_class
{
  i4_color color;
  i4_bool center;
public:
  char *name() { return "vertical_compact"; }

  virtual void receive_event(i4_event *ev);
  virtual void parent_draw(i4_draw_context_class &context);
  void compact();
  i4_vertical_compact_window_class(i4_color color, i4_bool center=i4_F) 
    : i4_parent_window_class(0,0), color(color), center(center) {}
  virtual void remove_child(i4_window_class *child)
  {
    i4_parent_window_class::remove_child(child);
    compact();
  }
};

class i4_horizontal_compact_window_class : public i4_parent_window_class
{
  i4_color color;
  i4_bool center;
public:
  char *name() { return "vertical_compact"; }

  virtual void receive_event(i4_event *ev);
  virtual void parent_draw(i4_draw_context_class &context);
  void compact();
  i4_horizontal_compact_window_class(i4_color color, i4_bool center=i4_F)
    : i4_parent_window_class(0,0), color(color), center(center) {}
  virtual void remove_child(i4_window_class *child)
  {
    i4_parent_window_class::remove_child(child);
    compact();
  }
};

#endif









