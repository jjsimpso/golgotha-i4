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
 


#include "image/image.hh"
#include "window/cursor.hh"
#include "string/string.hh"
#include "loaders/load.hh"
#include "image/context.hh"

i4_cursor_class *i4_load_cursor(char *cursor_name,
                                i4_string_manager_class *sman)
{
  i4_const_str st=sman->get(cursor_name);    // looks up the resource
  sw32 trans,hot_x,hot_y;

  i4_const_str::iterator s=st.begin();
  i4_str *fn=s.read_string();
  trans=s.read_number();
  hot_x=s.read_number();
  hot_y=s.read_number();


  i4_image_class *im=i4_load_image(*fn);  // try to load up the cursor image
  if (!im) 
  {
    delete fn;  
    return 0;
  }
  else 
  {
    i4_cursor_class *c=new i4_cursor_class(im,(i4_color)trans,hot_x,hot_y);
    delete im;
    delete fn;
    return c;
  }

}



i4_cursor_class::i4_cursor_class(i4_image_class *_pict, 
                                 i4_color trans, 
                                 i4_coord hot_x, i4_coord hot_y,
                                 const i4_pal *convert_to) 
: trans(trans),
  hot_x(hot_x),hot_y(hot_y)
{
  if (convert_to)
  {
    int w=_pict->width(), h=_pict->height();
    pict=i4_create_image(w,h, convert_to);
      
    i4_draw_context_class context(0,0, w-1,h-1);
    pict->clear(trans, context);
    _pict->put_image_trans(pict, 0,0, trans, context);
  }
  else pict=_pict->copy();
}

i4_cursor_class::~i4_cursor_class() 
{
  if (pict)
    delete pict;
}

i4_cursor_class::i4_cursor_class()
{
  pict = 0;
}

i4_cursor_class *i4_cursor_class::copy(const i4_pal *convert_to)
{
  return new i4_cursor_class(pict, trans, hot_x, hot_y, convert_to);
}

