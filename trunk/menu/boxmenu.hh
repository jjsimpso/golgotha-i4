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
 

#ifndef __BOXMENU_HPP_
#define __BOXMENU_HPP_

#include "menu/menu.hh"
#include "window/window.hh"
#include "error/error.hh"
#include "menu/menuitem.hh"

class i4_graphical_style_class;

class i4_box_menu_class : public i4_menu_class
{

  i4_graphical_style_class *style;
  
  public :
  // show should make the menu visible on the screen
  virtual void show(i4_parent_window_class *show_on, i4_coord x, i4_coord y);
  virtual void hide();

  virtual void parent_draw(i4_draw_context_class &context);
  i4_box_menu_class(i4_graphical_style_class *style, 
                    i4_bool hide_on_pick) : 
    i4_menu_class(hide_on_pick),
    style(style)
  { ; }

  char *name() { return "box_menu"; }

} ;


#endif
