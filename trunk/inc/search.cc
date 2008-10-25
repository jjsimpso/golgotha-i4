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
 

#include "inc/search.hh"

i4_bool i4_base_bsearch(const void *member, w32 &loc,
                        const void *array, w32 member_size, w32 size, 
                        int (*compare)(const void *a, const void *b))
{
  w32 l=0,r=size,m;
  int c;

  while (l<r)
  {
    m = (l+r)/2;

    if ((c = compare(member, (void*)((w8*)array+member_size*m)))==0)
    {
      loc = m;
      return i4_T;
    }
    else if (c<0)
      r = m;
    else
      l = m+1;
  }
  loc = l;
  if (l<size && compare(member, (void*)((w8*)array+member_size*l))==0)
    return i4_T;
  return i4_F;
}
