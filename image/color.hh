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
 

#ifndef I4_COLOR_HH
#define I4_COLOR_HH
#include "arch.hh"

inline w16 i4_32bpp_to_16bpp(w32 color)
{
  w32 r=(color>>16)&0xff, g=(color>>8)&0xff, b=(color>>0)&0xff;

  r=(r>>3); 
  g=(g>>2); 
  b=(b>>3);

  return (r<<(5+6)) | (g<<5) | b;
}


inline w16 i4_32bpp_to_15bpp(w32 color)
{
  w32 r=(color>>(16+3))   & (1 | 2 | 4 | 8 | 16);
  w32 g=(color>>(8+3))    & (1 | 2 | 4 | 8 | 16);
  w32 b=(color>>(0+3))    & (1 | 2 | 4 | 8 | 16);

  return (r<<(5+5)) | (g<<5) | b;
}

inline void i4_32bpp_to_rgb(w32 color, w8 &r, w8 &g, w8 &b)
{
  r=(color>>16)&0xff;
  g=(color>>8)&0xff;
  b=color&0xff;
}

inline w32 i4_15bpp_to_32bpp(w32 color)
{
  return ((((color & ((1 | 2 | 4 | 8 | 16)<<0))  >> 0) << (3+0)) |
          (((color & ((1 | 2 | 4 | 8 | 16)<<5))  >> 5) << (3+8)) |
          (((color & ((1 | 2 | 4 | 8 | 16)<<10)) >> 10) << (3+16)));
}

inline w32 i4_16bpp_to_32bpp(w32 color)
{
  w32 r=((color>>11) & (1|2|4|8|16))   <<3;
  w32 g=((color>>5)  & (1|2|4|8|16|32))<<2;
  w32 b=((color>>0)  & (1|2|4|8|16))   <<3;
  return (r<<16)|(g<<8)|b;
}

inline w32 i4_rgb_to_32bit(w8 r, w8 g, w8 b)
{
  return (r<<16) | (g<<8) | b;
}

#if (I4_SCREEN_DEPTH==15)
inline w16 i4_32bpp_to_screen(w32 color, w32 *pal)
{
  return i4_32bpp_to_15bpp(color);
}
#endif



#if (I4_SCREEN_DEPTH==16)
inline w16 i4_32bpp_to_screen(w32 color, w32 *pal)
{
  return i4_32bpp_to_16bpp(color);
}
#endif



#if (I4_SCREEN_DEPTH==32)
inline w16 i4_32bpp_to_screen(w32 color, w32 *pal)
{
  return color;
}
#endif


#if (I4_SCREEN_DEPTH==8)
#error need to solve this problem
inline w16 i4_32bpp_to_screen(w32 color, w32 *pal) 
{ return 0; }

#endif




#endif
