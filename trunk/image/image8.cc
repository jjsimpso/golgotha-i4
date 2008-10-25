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
 

#include "image/image8.hh"
#include "memory/malloc.hh"
#include "palette/pal.hh"

#include <string.h>



i4_color i4_image8::get_pixel(i4_coord x, i4_coord y)
{    
  return i4_pal_man.convert_to_32(*(typed_data() + bpl*y + x), pal);
}
  
void i4_image8::put_pixel(i4_coord x, i4_coord y, w32 color)
{
  *(typed_data() + bpl*y + x)=i4_pal_man.convert_32_to(color, &pal->source);
}


i4_image8::i4_image8(w16 _w, w16 _h, const i4_pal *_pal)
{
  w=_w;
  h=_h;
  bpl=_w;
  set_pal(_pal);
  data=i4_malloc(w*h,"");  
}

i4_image8::i4_image8(w16 _w, w16 _h, const i4_pal *_pal,
                       void *_data, int _bpl)
{
  data=_data;
  bpl=_bpl;
  pal=_pal;
  w=_w;
  h=_h;

  dont_free_data=i4_T;
}


i4_image8::~i4_image8()
{
  if (!dont_free_data)
    i4_free(data);
}


i4_image_class *i4_image8::copy()
{
  i4_image_class *im=i4_create_image(width(), height(), pal);

  
  for (int y=0; y<h; y++)
    memcpy(((w8 *)im->data) + y*im->bpl,
           ((w8 *)data) + y*bpl,
           w);

  return im;
}
