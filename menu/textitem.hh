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
 

#ifndef __TEXTITEM_HPP_
#define __TEXTITEM_HPP_

#include "menu/menu.hh"
#include "font/font.hh"
#include "window/style.hh"

class i4_text_item_class : public i4_menu_item_class
{
  protected :

  i4_color_hint_class *color;
  i4_font_class *font;

  i4_str *text;
  w16 pad_lr;

  public :
  w32 bg_color;

  
  i4_text_item_class(
               const i4_const_str &_text,      
               i4_graphical_style_class *style,
         
               i4_color_hint_class *color_hint=0,
               i4_font_class *font=0,
         

               i4_event_reaction_class *press=0,
               i4_event_reaction_class *depress=0,
               i4_event_reaction_class *activate=0,
               i4_event_reaction_class *deactivate=0,
               w16 pad_left_right=0,
               w16 pad_up_down=0
               );
  ~i4_text_item_class()
  {
    delete text;
  }

  char *name() { return "text_item"; }

  virtual void parent_draw(i4_draw_context_class &context);
  virtual void receive_event(i4_event *ev);
  void change_text(const i4_const_str &new_st);
  i4_const_str get_text() { return *text; }

  virtual i4_menu_item_class *copy();
} ;

#endif
