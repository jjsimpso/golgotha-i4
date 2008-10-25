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
 

#include "string/str_checksum.hh"

w32 i4_str_checksum(const i4_const_str &str)
{
  i4_const_str::iterator i=str.begin();

  int len=str.length();
  
  w8 c1=0,c2=0,c3=0,c4=0;

  while (len)
  {
    c1+=i.get().value();
    c2+=c1;
    c3+=c2;
    c4+=c3;
    ++i;
    len--;
  }

  return (c1|(c2<<8)|(c3<<16)|(c4<<24));
}
