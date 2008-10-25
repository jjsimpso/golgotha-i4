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
 

#ifndef TEXT_SCROLL_WIN
#define TEXT_SCROLL_WIN

#include "window/window.hh"
#include "font/font.hh"
class i4_graphical_style_class;

class i4_text_scroll_window_class : public i4_parent_window_class
{
  i4_color fore,back;
  i4_char *term_out, *draw_start;
  w32 term_size, used_size;
  sw32 dx, dy, tdx, tdy;

  sw32 term_height;    // in characters
  w32 line_height;
  i4_bool need_clear;
  i4_graphical_style_class *style;

public:
  char *name() { return "text_scroll_window"; }

  void resize(w16 new_width, w16 new_height);

  i4_text_scroll_window_class(i4_graphical_style_class *style,
                              i4_color text_foreground,
                              i4_color text_background,
                              w16 width, w16 height);               // in pixels

  void clear();
  void skip_first_line();

  void output_char(const i4_char &ch);
  void output_string(char *string);
  void printf(char *fmt, ...);

  void parent_draw(i4_draw_context_class &context);

  virtual i4_bool need_redraw();

};



#endif
