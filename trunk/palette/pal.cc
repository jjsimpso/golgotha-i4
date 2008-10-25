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
 

#include "palette/pal.hh"
#include "math/num_type.hh"
#include "memory/malloc.hh"
#include "file/file.hh"
#include <memory.h>

i4_pal_manager_class i4_pal_man;

int i4_lk_cmp_size[]={0,0,256*4, 16*4, 2*4};

void i4_pixel_format::default_format()
{

  red_mask    = 0x00ff0000;
  green_mask  = 0x0000ff00;
  blue_mask   = 0x000000ff;
  alpha_mask  = 0xff000000;

  calc_shift();

  lookup      = 0;
  pixel_depth = I4_32BIT;
}



w32 i4_pixel_format::write(i4_file_class *f)
{
  if (!f)
    return (13*4);

  f->write_32(red_mask);
  f->write_32(red_shift);
  f->write_32(red_bits);

  f->write_32(green_mask);
  f->write_32(green_shift);
  f->write_32(green_bits);

  f->write_32(blue_mask);
  f->write_32(blue_shift);
  f->write_32(blue_bits);

  f->write_32(alpha_mask);
  f->write_32(alpha_shift);
  f->write_32(alpha_bits);

  f->write_32(pixel_depth);
    
  return (13*4); //(# of bytes written)
}

void i4_pixel_format::read(i4_file_class *f)
{
  red_mask    = f->read_32();
  red_shift   = f->read_32();
  red_bits    = f->read_32();

  green_mask  = f->read_32();
  green_shift = f->read_32();
  green_bits  = f->read_32();

  blue_mask   = f->read_32();
  blue_shift  = f->read_32();
  blue_bits   = f->read_32();

  alpha_mask  = f->read_32();
  alpha_shift = f->read_32();
  alpha_bits  = f->read_32();

  pixel_depth = (enum i4_pixel_depth)f->read_32();

  lookup = 0;
}

i4_bool i4_lookup_pal::can_convert(const i4_pixel_format *source_fmt, 
                                   const i4_pixel_format *dest_fmt) const
{  
  return i4_T;
}


i4_color i4_lookup_pal::convert(const i4_color source_pixel,
                                const i4_pixel_format *dest) const
{
  w32 rgb=source.lookup[source_pixel];

  w32 r=((rgb>>16) & ((dest->red_mask>>dest->red_shift)<<(8-dest->red_bits)));
  w32 g=((rgb>>8)  & ((dest->green_mask>>dest->green_shift)<<(8-dest->green_bits)));
  w32 b=((rgb>>0)  & ((dest->blue_mask>>dest->blue_shift)<<(8-dest->blue_bits)));
  
  r = (r>>(8-dest->red_bits))<<dest->red_shift;
  g = (g>>(8-dest->green_bits))<<dest->green_shift;
  b = (b>>(8-dest->blue_bits))<<dest->blue_shift;

  return r|g|b;
}

i4_lookup_pal::i4_lookup_pal(i4_pixel_format *source_fmt)
{
  source=*source_fmt;
  int size=i4_lk_cmp_size[source.pixel_depth];
  source.lookup = (w32 *)i4_malloc(size, "pal memory");
  memcpy(source.lookup, source_fmt->lookup, size);
}

i4_lookup_pal::~i4_lookup_pal()
{
  i4_free(source.lookup);
}

i4_rgb_pal::i4_rgb_pal(i4_pixel_format *source_fmt)
{
  source=*source_fmt;
  source.lookup=0;
}

i4_bool i4_rgb_pal::can_convert(const i4_pixel_format *source_fmt, 
                                const i4_pixel_format *dest_fmt) const 
{
  if ((source_fmt->pixel_depth == I4_32BIT ||
       source_fmt->pixel_depth == I4_16BIT) &&
      (dest_fmt->pixel_depth == I4_32BIT ||
       dest_fmt->pixel_depth == I4_16BIT))
    return i4_T;
  else
    return i4_F;
}

i4_color i4_rgb_pal::convert(const i4_color source_pixel,
                             const i4_pixel_format *dest) const
{
  w32 argb = source_pixel;

  w32 a = ((argb & source.alpha_mask)>>source.alpha_shift)<<(8-source.alpha_bits);
  w32 r = ((argb & source.red_mask)>>source.red_shift)<<(8-source.red_bits);
  w32 g = ((argb & source.green_mask)>>source.green_shift)<<(8-source.green_bits);
  w32 b = ((argb & source.blue_mask)>>source.blue_shift)<<(8-source.blue_bits);

  a = (a>>(8-dest->alpha_bits))<<dest->alpha_shift;
  r = (r>>(8-dest->red_bits))<<dest->red_shift;
  g = (g>>(8-dest->green_bits))<<dest->green_shift;
  b = (b>>(8-dest->blue_bits))<<dest->blue_shift;

  return a|r|g|b;  
}



i4_pal *i4_pal_manager_class::register_pal(i4_pixel_format *format)
{
  i4_pixel_format dest;
  dest.default_format();

  i4_pal *p;

  i4_isl_list<i4_pal>::iterator i;
  for (i=pal_list.begin(); i!=pal_list.end(); ++i)
  {
    if (format->pixel_depth == i->source.pixel_depth)
    {
      if (format->pixel_depth == I4_8BIT ||
          format->pixel_depth == I4_4BIT ||
          format->pixel_depth == I4_2BIT)
      {
        if (memcmp(format->lookup,
                   i->source.lookup,
                   i4_lk_cmp_size[format->pixel_depth])==0)
        {
          p=&(*i);
          return p;
        }
      } else if (format->red_mask == i->source.red_mask &&
                 format->green_mask == i->source.green_mask &&
                 format->blue_mask == i->source.blue_mask &&
                 format->alpha_mask == i->source.alpha_mask)
      {
        p=&(*i);
        return p;
      }
    }
  }
  
  if (format->pixel_depth == I4_8BIT ||
      format->pixel_depth == I4_4BIT ||
      format->pixel_depth == I4_2BIT)
  {
    i4_lookup_pal *l= new i4_lookup_pal(format);
    pal_list.insert(*l);
    p=l;
  }
  else
  {
    i4_rgb_pal *l= new i4_rgb_pal(format);
    pal_list.insert(*l);
    p=l;    
  }

  return p;
}

void i4_pal_manager_class::init()
{
  i4_pixel_format d;
  d.default_format();

  def32=register_pal(&d);
 
  d.alpha_mask=0;
  d.calc_shift();

  def_na_32=register_pal(&d);


  w32 tmp[256];
  d.pixel_depth=I4_8BIT;
  d.lookup=tmp;
  def8=register_pal(&d);

}

void i4_pal_manager_class::uninit()
{
  pal_list.destroy_all();
}


i4_color i4_pal_manager_class::convert_32_to(i4_color c, 
					     const i4_pixel_format *dest_format) const
{
  return def32->convert(c, dest_format);
}


i4_color i4_pal_manager_class::convert_to_32(i4_color c, const i4_pal *source_format) 
const
{
  return source_format->convert(c, &def32->source);
}

void i4_pixel_format::calc_shift()
{
  w32 c;

  // <jhop> If red_mask, green_mask, or blue_mask are zero
  // the first loop of these loop pairs will go on infinitely

  I4_ASSERT(red_mask != 0, "i4_pixel_format::red_mask is zero");
  c=red_mask;
  for (red_shift=0; (c&1)==0; red_shift++, c=c>>1);
  for (red_bits=0;  (c&1)==1; red_bits++,  c=c>>1);

  I4_ASSERT(green_mask != 0, "i4_pixel_format::green_mask is zero");
  c=green_mask;
  for (green_shift=0; (c&1)==0; green_shift++, c=c>>1);
  for (green_bits=0;  (c&1)==1; green_bits++,  c=c>>1);

  I4_ASSERT(blue_mask != 0, "i4_pixel_format::blue_mask is zero");
  c=blue_mask;
  for (blue_shift=0; (c&1)==0; blue_shift++, c=c>>1);
  for (blue_bits=0;  (c&1)==1; blue_bits++,  c=c>>1);

  c=alpha_mask;
  for (alpha_shift=0; (c&1)==0 && alpha_shift<99; alpha_shift++, c=c>>1);
  if (alpha_shift==99) alpha_shift=0;

  for (alpha_bits=0;  (c&1)==1 && alpha_bits<99; alpha_bits++,  c=c>>1);
  if (alpha_bits==99) alpha_bits=0;
}

w32 g1_light_color(w32 color, float intensity)
{
  float r=(color>>16)&0xff;
  float g=(color>>8)&0xff;
  float b=(color>>0)&0xff;
  
  r*=intensity;
  g*=intensity;
  b*=intensity;

  return ((i4_f_to_i(r)<<16) | (i4_f_to_i(g)<<8) | (i4_f_to_i(b)));
}
