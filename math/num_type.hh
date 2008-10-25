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
 

#ifndef __NUM_TYPE_HPP_
#define __NUM_TYPE_HPP_

#include "arch.hh"

/* 
   Use i4_float instead of float so we can
   substitute fixed point later on 
   */

typedef float i4_float;
typedef float i4_angle;   // stored in radians

inline i4_float i4_fabs(const i4_float &x) 
{ 
  if (x<0) 
    return -x; 
  else return x; 
}

#ifdef WIN32
inline sw32 i4_f_to_i(i4_float f)
{
  w16 i4_f_to_i_control_word_1;
  w16 i4_f_to_i_control_word_2;
  sw32 res;
  __asm
  {
    fld f
    
    wait
    fnstcw i4_f_to_i_control_word_1
    wait

    mov    ax,i4_f_to_i_control_word_1
    or     ah,0xC
    mov    word ptr i4_f_to_i_control_word_2,ax
    fldcw  i4_f_to_i_control_word_2        
    fistp  res
    fldcw  i4_f_to_i_control_word_1
  }
  return res;
}

inline sw32 i4_s_to_i(double f)
{
  w16 i4_f_to_i_control_word_1;
  w16 i4_f_to_i_control_word_2;
  sw32 res;
  __asm
  {
    fld qword ptr [f]
    
    fnstcw i4_f_to_i_control_word_1

    mov    ax,i4_f_to_i_control_word_1
    or     ah,0xC
    mov    word ptr i4_f_to_i_control_word_2,ax
    fldcw  i4_f_to_i_control_word_2        
    fistp  res
    fldcw  i4_f_to_i_control_word_1
  }
  return res;
}

#else

#define i4_f_to_i(a) (sw32)(a)
#define i4_d_to_i(a) (sw32)(a)

#endif

inline i4_float i4_interpolate(i4_float from, i4_float to, i4_float frac)
{
  return (to - from)*frac + from;
}

#endif
