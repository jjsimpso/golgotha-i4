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
 

#ifndef __I4IMAGE_HPP_
#define __I4IMAGE_HPP_


class i4_pal;
class i4_rect_list_class;
class i4_draw_context_class;

#include "arch.hh"


class i4_image_class
{  
public:
  const i4_pal *pal;
  // raw data,
  // depends on pal.pal->source.pixel_depth==(I4_32BIT,I4_16BIT,I4_8BIT,I4_4BIT,I4_2BIT)
  void *data;  
  int w, h, bpl;
  i4_bool dont_free_data;
  
  const i4_pal *get_pal() { return pal; }
  void set_pal(const i4_pal *which) { pal=which; }


  w16 width() { return w; }
  virtual w16 height() { return h; }

  // these do color conversion to & from 32bit
  virtual i4_color get_pixel(i4_coord x, i4_coord y)                                  = 0;
  virtual void put_pixel(i4_coord x, i4_coord y, w32 color)                           = 0;

  // put pixel does clipping and window offset moving and then calls put_pixel(x,y,c)
  void put_pixel(i4_coord x, i4_coord y, w32 color, i4_draw_context_class &context);
  
  w32  get_pixel(i4_coord x, i4_coord y,  i4_draw_context_class &context);

  virtual void xor_bar(i4_coord x1, i4_coord y1, 
                       i4_coord x2, i4_coord y2, 
                       i4_color xor_color, i4_draw_context_class &context);

  virtual void bar(i4_coord x1,    i4_coord y1, 
                   i4_coord x2,    i4_coord y2, 
                   i4_color color, i4_draw_context_class &context);

  virtual void line(i4_coord x1, i4_coord y1, 
                    i4_coord x2, i4_coord y2, 
                    i4_color color, i4_draw_context_class &context);

  void add_single_dirty(i4_coord x1, i4_coord y1, i4_coord x2, 
                        i4_coord y2, i4_draw_context_class &context);
  
  void add_dirty(i4_coord x1, i4_coord y1, i4_coord x2, 
                 i4_coord y2, i4_draw_context_class &context);

  
  //{ put_part :
  //  put_part transfers a rectanguar image of yourself to location x,y on image 'to'
  virtual void put_part(i4_image_class *to, 
			i4_coord x,  i4_coord y,                              
			i4_coord x1, i4_coord y1, i4_coord x2, i4_coord y2, 
                        i4_draw_context_class &context);

  virtual void put_part_trans(i4_image_class *to, 
                              i4_coord x,  i4_coord y,                                 
                              i4_coord x1, i4_coord y1, i4_coord x2, i4_coord y2,
                              i4_color trans_color, i4_draw_context_class &context);

  // copy is not expanded by the image template, it needs to be implemented per image
  virtual i4_image_class *copy();

  // Non-virtual functions, these are implemented as a convience 
  // not as a primative to be derived from
  void put_image(i4_image_class *to, i4_coord x, i4_coord y, i4_draw_context_class &context)
  { put_part(to,x,y,0,0,width()-1,height()-1,context); }

  void put_image_trans(i4_image_class *to, 
                       i4_coord x, i4_coord y, i4_color trans_color, 
                       i4_draw_context_class &context)
  { put_part_trans(to,x,y,0,0,width()-1,height()-1,trans_color,context); }

  virtual void clear(i4_color color, i4_draw_context_class &context)
  { bar(0,0,width()-1,height()-1,color,context); }

  virtual void rectangle(i4_coord x1, i4_coord y1, i4_coord x2, i4_coord y2, i4_color color, 
                         i4_draw_context_class &context);

  i4_image_class() { dont_free_data=i4_F; }
  virtual ~i4_image_class() { ; }
};

i4_image_class *i4_create_image(int width, int height, const i4_pal *pal);

i4_image_class *i4_create_image(int width, int height,
                                const i4_pal *pal,
                                void *data,
                                int bytes_per_line);

#endif
