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
 

#include "arch.hh"
#include "memory/malloc.hh"
#include <string.h>


class i4_bit_array_class
{
  w8 static_data[8];
  w8 *data;
  public :
  i4_bit_array_class(w32 length=32, void *bit_data)
  {
    if (length<=64) data=static_data;
    else data=(w8 *)i4_malloc((length+7)/8,"bit array");
    memcpy(data,bit_data,(length+7)/8);
  }

  i4_bit_array_class(w32 length=32)
  {
    if (length<=64) data=static_data;
    else data=(w8 *)i4_malloc((length+7)/8,"bit array");
    memset(data,0,(length+7)/8);
  }

  i4_bool get(w32 x)
  {
    if (data[x/8]&(1<<(x%8)))
      return i4_T;
    else return i4_F;
  }

  void set(w32 x, i4_bool value)
  {
    if (value==i4_F)
      data[x/8]&=~(1<<(x%8));
    else data[x/8]|=(1<<(x%8));
  }

  ~i4_bit_array_class() 
  {
    if (static_data!=data)
      i4_free(data);
  }
} ;
