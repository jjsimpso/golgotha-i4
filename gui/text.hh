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
 

#ifndef __TEXT_HH_
#define __TEXT_HH_

#include "window/window.hh"
#include "string/string.hh"
#include "window/style.hh"

class i4_text_window_class : public i4_window_class
{
  i4_str *text;
  i4_graphical_style_class *hint;
  i4_font_class *font;

public:
  i4_text_window_class(const i4_const_str &text,
                       i4_graphical_style_class *hint,
                       i4_font_class *_font=0)
    : i4_window_class(0, 0),
      text(new i4_str(text)),
      hint(hint),
      font(_font)
  {
    if (!font)
      font=hint->font_hint->normal_font;
    
    resize(font->width(text), font->height(text));
  }
                    
  virtual void draw(i4_draw_context_class &context)
  {
    local_image->add_dirty(0,0,width()-1,height()-1,context);
    font->set_color(hint->color_hint->text_foreground);

    hint->deco_neutral_fill(local_image, 0,0, width()-1, height()-1, context);
    //    local_image->clear(hint->color_hint->window.passive.medium,context);
    if (text)
      font->put_string(local_image,0,0,*text,context);  
  }

  ~i4_text_window_class() { delete text; }

  void set_text(i4_str *new_text)
  {
    if (text)
      delete text;
    text = new_text;
    request_redraw();
  }

  char *name() { return "text_window"; }
};


#endif
