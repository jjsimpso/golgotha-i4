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

enum { TSIZE=512 };
static w32   w32_rtable[TSIZE];
static float f_rtable[TSIZE];
static int seed=0;
static int initialized=0;

void next_seed()
{
  if (!initialized)
  {
    w32 inc=0xacd2d391, mul=0xf34f9201, x=0;
    for (int i=0; i<TSIZE; i++)
    {     
      w32_rtable[i]=x;
      f_rtable[i]=(double)x/(double)0xffffffff;
      x=(x+inc)*mul;
    }
    initialized=1;
  }

  seed++;  
}

w32 i4_rand() 
{ 
  next_seed();
  return w32_rtable[seed];
}

float i4_float_rand() 
{ 
  next_seed();
  return f_rtable[seed];
}

void i4_rand_reset(w32 _seed)
{
  seed=_seed % TSIZE;
}

