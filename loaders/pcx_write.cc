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
 


#include "image/depth.hh"
#include "image/image8.hh"
#include "file/file.hh"
#include "palette/pal.hh"

void i4_write_pcx(i4_image_class *im,
                  const i4_pal_handle_class &pal,
                  i4_file_class *fp)
{
  if (im->get_pal().type()!=i4_pal_handle_class::ID_8BIT)
    i4_error("cannot save non 8bit pcx files");

  fp->write_8(10);   // manufacturer
  fp->write_8(5);    // version
  fp->write_8(1);    // encoding
  fp->write_8(8);    // bits_per_pixel

  fp->write_16(0);               // xmin
  fp->write_16(0);               // ymin
  fp->write_16(im->width()-1);   // xmax
  fp->write_16(im->height()-1);  // ymax
  fp->write_16(320);             // hres
  fp->write_16(200);             // vres 


  w8 scrap[58];
  memset(scrap,0,sizeof(scrap));
  fp->write(scrap,48);

  fp->write_8(0);                // reserved
  fp->write_8(1);                // color planes
  fp->write_16(im->width());     // bytes per line
  fp->write_16(0);               // palette type
  
  fp->write(filter,58);

  
  sw32 y,run_length,x;
  w8 code;  
  i4_unmatched_image8 *im8=(i4_unmatched_image8 *)im;
  i4_unmatched_image8::iterator sl,run;

  for (y=0; y<im->height(); y++)
  {
    sl=im->create_iterator(0,y);

    for (x=0;x<im->width();)
    {
      run_length=1;      
      run=sl;
      while (x+run_length<im->width() && im->iterator_get(run)==im->iterator_get(sl))
      {
        ++run;
        ++run_length;
      }

      if (run_length==1 && im->iterator_get(sl)<64) 
        fp->write_8(im->iterator_get(sl));
      else
      {
        if (run_length>=64)
	  run_length=63;
	code=0xc0 | run_length;
	fp->write_8(code);
	fp->write_8(im->iterator_get(sl));	
      }      
      x+=run_length;
      sl=run;
    }
  }
  fp->write_8(12);  // note that there is a palette attached

  w8 packed_pal[256*3];
  w32 *p=i4_pal_man.get_pal(pal);
  for (w32 x=0; x<256; x++)
  {
    packed_pal[x*3+0]=((*p)>>16)&0xff;
    packed_pal[x*3+1]=((*p)>>8)&0xff;
    packed_pal[x*3+2]=((*p)>>0)&0xff;
  }

  fp->write(packed_pal,256*3);
  fclose(fp);    
}



