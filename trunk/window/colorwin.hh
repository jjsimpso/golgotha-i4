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
 

#ifndef __COLOR_WIN_HPP_
#define __COLOR_WIN_HPP_

#include "window/window.hh"
#include "palette/pal.hh"

class i4_graphical_style_class;
class i4_color_window_class : public i4_parent_window_class
{
protected:
  i4_color color;
  i4_graphical_style_class *style;

public:
  char *name() { return "color_window"; }  

  i4_color_window_class(w16 w, w16 h, i4_color color, i4_graphical_style_class *style) :
     i4_parent_window_class(w,h), color(color), style(style) { ; }

  virtual void parent_draw(i4_draw_context_class &context);

} ;

i4_parent_window_class *i4_add_color_window(i4_parent_window_class *parent, i4_color color, 
                                            i4_graphical_style_class *style,
                                            i4_coord x, i4_coord y, w16 w, w16 h);



#endif
