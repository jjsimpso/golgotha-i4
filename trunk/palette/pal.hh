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
 

#ifndef __PALETTE_HPP_
#define __PALETTE_HPP_

#include "arch.hh"
#include "isllist.hh"
#include "init/init.hh"
#include "error/error.hh"

enum i4_pixel_depth
{ 
  I4_32BIT=0,      // 16.7 mil & alpha
  I4_16BIT=1,      // 64K color
  I4_8BIT=2,       // 256 color
  I4_4BIT=3,       // 16 color
  I4_2BIT=4        // 2 color
} ;

class i4_file_class;
struct i4_pixel_format
{
  // these not valid for 2,4, and 8 bit pixel depths
  w32 red_mask, red_shift, red_bits;
  w32 green_mask, green_shift, green_bits;
  w32 blue_mask, blue_shift, blue_bits;
  w32 alpha_mask, alpha_shift, alpha_bits;

  // lookup is not valid for 16 & 32 bit pixel depths
  w32 *lookup;

  i4_pixel_depth pixel_depth;

  void calc_shift();
  
  void default_format();
  w32 write(i4_file_class *f);
  void read(i4_file_class *f);
};

class i4_pal
{
public:
  i4_pal *next;

  i4_pixel_format source;

  virtual i4_bool can_convert(const i4_pixel_format *source_fmt, 
                              const i4_pixel_format *dest_fmt) const = 0;

  virtual i4_color convert(const i4_color source_pixel,
                           const i4_pixel_format *dest_fmt) const = 0;

  virtual ~i4_pal() { ; }
};

class i4_lookup_pal : public i4_pal
{
public:
  virtual i4_bool can_convert(const i4_pixel_format *source, 
                              const i4_pixel_format *dest) const;

  virtual i4_color convert(const i4_color source,
                           const i4_pixel_format *dest) const;

  i4_lookup_pal(i4_pixel_format *source);
  virtual ~i4_lookup_pal();

};

class i4_rgb_pal : public i4_pal
{
public:
  i4_rgb_pal(i4_pixel_format *source);

  virtual i4_bool can_convert(const i4_pixel_format *source, 
                              const i4_pixel_format *dest) const;

  virtual i4_color convert(const i4_color source,
                           const i4_pixel_format *dest) const;


};


class i4_pal_manager_class : public i4_init_class
{
  i4_isl_list<i4_pal> pal_list;

  i4_pal *def32, *def_na_32, *def8;

  public:
  void init();
  void uninit();

  i4_pal *register_pal(i4_pixel_format *format);

  // c will be converted from 32bit color to dest_format
  i4_color convert_32_to(i4_color c, const i4_pixel_format *dest_format) const;

  // c will be converted from source_format to 32bit color
  i4_color convert_to_32(i4_color c, const i4_pal *source_format) const;

  const i4_pal *default_no_alpha_32() { return def_na_32; }
  const i4_pal *default_32() { return def32; }
  const i4_pal *default_8() { return def8; }
} ;

extern i4_pal_manager_class i4_pal_man;

w32 g1_light_color(w32 color_32bit, float intensity);

#endif



