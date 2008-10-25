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
#include "loaders/tga_write.hh"
#include "file/file.hh"
#include "palette/pal.hh"


i4_bool i4_tga_write(i4_image_class *im, i4_file_class *fp, int include_alpha)
{
  fp->write_8(0);   // no id field
  fp->write_8(0);   // no color map
  fp->write_8(2);   // type = True color uncompressed
  
  fp->write_16(0);  // first color map entry
  fp->write_16(0);  // color map length
  fp->write_8(0);   // color map entry size

  fp->write_16(0);  // origin x & y
  fp->write_16(0);

  sw32 w=im->width(), h=im->height(), x,y;
  fp->write_16(w);   // image width & height
  fp->write_16(h);

  if (include_alpha)
    fp->write_8(32);   // bits per pixel
  else
    fp->write_8(24);   // bits per pixel

  fp->write_8(0);


  w8 out[4];
  i4_color color;

  i4_pixel_format to;
  to.default_format();

  if (include_alpha)
  {
    for (y=h-1; y>=0; y--)
    {
      for (x=0; x<w; x++)
      {
        color=im->get_pixel(x,y);
            
        out[0]=color&0xff;
        out[1]=(color>>8)&0xff;
        out[2]=(color>>16)&0xff;
        out[3]=(color>>24)&0xff;
        fp->write(out,4);
      }
    }
  }
  else
  {  
    for (y=h-1; y>=0; y--)
    {
      for (x=0; x<w; x++)
      {
        color=im->get_pixel(x,y);
            
        out[0]=color&0xff;
        out[1]=(color>>8)&0xff;
        out[2]=(color>>16)&0xff;
        fp->write(out,3);
      }
    }
  }

  return i4_T;
    
}
