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
 

#ifndef __I4_IMAGE32_HPP_
#define __I4_IMAGE32_HPP_

#include "image/image.hh"

class i4_image32 : public i4_image_class
{
public:
  w32 *paddr(int x, int y) { return (w32 *)(((w8 *)data)+x*4+y*bpl); }
  

  i4_image32(w16 w, w16 h, const i4_pal *pal);
  i4_image32(w16 w, w16 h, const i4_pal *pal, void *data, int bpl);
  i4_color get_pixel(i4_coord x, i4_coord y);  
  void put_pixel(i4_coord x, i4_coord y, w32 color);
  
  i4_image_class *quantize(const i4_pal *pal,
                           w32 skip_colors,
                           i4_coord x1, i4_coord y1,
                           i4_coord x2, i4_coord y2);
  
  ~i4_image32();
};


#endif
