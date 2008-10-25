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
 

#ifndef I4_QUE_HH
#define I4_QUE_HH

#include "arch.hh"

template <class T, w32 SIZE>
class i4_fixed_que
{
protected:
  T data[SIZE];
  w32 head, tail;
  
public:
  void reset() { head=tail=0; }

  i4_fixed_que() { reset(); }

  i4_bool empty() { return (i4_bool)(head==tail); }

  i4_bool full() { return (i4_bool)((head==SIZE-1 && tail==0) || head+1==tail); }

  i4_bool que(const T &object) 
  {
    w32 next_head=(head+1);
    if (next_head==SIZE) 
      next_head=0;

    if (next_head==tail)
      return i4_F;

    data[head]=object;
    head=next_head;
    return i4_T;
  }

  i4_bool deque(T &object)
  {
    if (empty())
      return i4_F;

    object=data[tail];
    tail++;
    if (tail==SIZE)
      tail=0;   
    return i4_T;
  }

  i4_bool front(T &object)
  {
    if (empty())
      return i4_F;

    object=data[tail];
    return i4_T;
  }
};

#endif
