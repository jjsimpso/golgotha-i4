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
 

#include "window/colorwin.hh"
#include "image/image.hh"
#include "window/style.hh"

void i4_color_window_class::parent_draw(i4_draw_context_class &context)
{     
  i4_rect_list_class child_clip(&context.clip,0,0);
  child_clip.intersect_list(&undrawn_area);

  child_clip.swap(&context.clip);

  
  if (color==style->color_hint->neutral())
  {
    for (i4_rect_list_class::area_iter c=context.clip.list.begin();c!=context.clip.list.end();++c)
      style->deco_neutral_fill(local_image, c->x1, c->y1, c->x2, c->y2, context);
  }
  else local_image->clear(color,context);

  child_clip.swap(&context.clip);
  i4_parent_window_class::parent_draw(context);
}

i4_parent_window_class *i4_add_color_window(i4_parent_window_class *parent, i4_color color, 
                                            i4_graphical_style_class *style,
                                            i4_coord x, i4_coord y, w16 w, w16 h)
{
  i4_color_window_class *cw=new i4_color_window_class(w,h,color, style);
  if (parent)
    parent->add_child(x,y,cw);
  return cw;
}

