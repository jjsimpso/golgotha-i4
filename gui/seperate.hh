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
 

#ifndef I4_SEPERATOR_HH
#define I4_SEPERATOR_HH

#include "menu/menuitem.hh"

class i4_seperator_line_class : public i4_menu_item_class
{
  w16 lr,ud;
  i4_graphical_style_class *style;
  i4_color bg;
public:
  i4_seperator_line_class(i4_graphical_style_class *style,
                          i4_color background,
                          w16 left_right_space,
                          w16 up_down_space)
    : i4_menu_item_class(0,0, 0,0),
      lr(left_right_space),
      ud(up_down_space),
      style(style),
      bg(background)
  {
    w32 l,r,t,b;
    style->get_in_deco_size(l,t,r,b);
    resize(lr*2, t+b+ud*2);
  }
  
  void reparent(i4_image_class *draw_area, i4_parent_window_class *parent)
  {
    i4_menu_item_class::reparent(draw_area, parent);
    if (parent && draw_area)
    {
      w32 l,r,t,b;
      style->get_in_deco_size(l,t,r,b);
      resize(parent->width()-lr*2, t+b+ud*2);
    }

  }

  void draw(i4_draw_context_class &context)
  {
    style->deco_neutral_fill(local_image, 0,0, width()-1, height()-1, context);
    style->draw_in_deco(local_image, 0, ud, width()-1, height()-1-ud,
                        i4_F, context);
  }

  i4_menu_item_class *copy() { return new i4_seperator_line_class(style, bg, lr, ud); }

  char *name() { return "seperator_line"; }
};


#endif
