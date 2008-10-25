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
 

#include "loaders/bmp_write.hh"
#include "image/image.hh"
#include "palette/pal.hh"
#include "file/file.hh"

inline void i4_32bpp_to_rgb(w32 color, w8 &r, w8 &g, w8 &b)
{
  r=(color>>16)&0xff;
  g=(color>>8)&0xff;
  b=color&0xff;
}

i4_bool i4_write_bmp(i4_image_class *im, i4_file_class *fp)
{
  const i4_pal *pal=im->get_pal();

  if (pal->source.pixel_depth==I4_8BIT)
  {
    w32 w=im->width();
    w32 h=im->height();
    w32 store_width=(w+3)&(~3);
    sw32 i;

    w8 buf[10];
    buf[0]='B';    buf[1]='M';

    if (fp->write(buf,2)!=2) return i4_F;
    fp->write_32(54 + 
                 4*256 +
                 store_width * h);

    fp->write_32(0);
    fp->write_32(54 + 256*4);

    fp->write_32(40);
    fp->write_32(w);
    fp->write_32(h);
    fp->write_16(1);
    fp->write_16(8);
    fp->write_32(0);
    fp->write_32(0);
    fp->write_32(320);
    fp->write_32(200);
    fp->write_32(256);
    fp->write_32(256);

    w32 *p=pal->source.lookup;
    for (i=0; i<256; i++)
    {
      w8 r,g,b;
      i4_32bpp_to_rgb(*p,r,g,b);
     
      buf[0]=b;
      buf[1]=g;
      buf[2]=r;
      buf[3]=0;

      fp->write(buf,4);
      p++;
    }
  
    buf[0]=0;
    buf[1]=0;
    buf[2]=0;
                 
    
    w8 *data=(w8 *)im->data;
    for (i=h; i; i--)
    {
      fp->write(data, w);
      data-=w;

      if (w!=store_width)
        fp->write(buf,w&3);
    }
    return i4_T;
  }
  else
    return i4_F;
}

