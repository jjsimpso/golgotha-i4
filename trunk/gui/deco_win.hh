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
 

#ifndef I4_DECO_WIN_HH
#define I4_DECO_WIN_HH

#include "window/style.hh"

class i4_deco_window_class : public i4_parent_window_class
{
  i4_bool in;
  sw32 x1,y1;
  i4_graphical_style_class *style;

public:
  i4_deco_window_class(w16 w, w16 h,   // size not including deco border
                       i4_bool in,     // pressed in or out look?
                       i4_graphical_style_class *style)
    : i4_parent_window_class(0,0),
      in(in),
      style(style)
  {
    w32 l,r,t,b;
    if (in)
      style->get_in_deco_size(l,r,t,b);
    else
      style->get_out_deco_size(l,r,t,b);

    x1=l; y1=r;
    resize(w+l+r, h+t+b);
  }

  sw32 get_x1() { return x1; }
  sw32 get_y1() { return y1; }

  virtual void parent_draw(i4_draw_context_class &context)
  {
    w32 l,r,t,b;
    if (in)
    {
      style->get_in_deco_size(l,r,t,b);
      style->draw_in_deco(local_image, 0,0, width()-1, height()-1, i4_F, context);
    }
    else
    {
      style->get_out_deco_size(l,r,t,b);
      style->draw_in_deco(local_image, 0,0, width()-1, height()-1, i4_F, context);
    }


    style->deco_neutral_fill(local_image, l,t, width()-r, height()-b, context);
//     local_image->bar(l,t, width()-r, height()-b, 
//                      style->color_hint->window.passive.medium, 
//                      context);
  }

  char *name() { return "deco_window"; }
} ;

#endif
