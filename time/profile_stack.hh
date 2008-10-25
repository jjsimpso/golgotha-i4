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
 

#ifndef I4_PROFILE_STACK_HH
#define I4_PROFILE_STACK_HH

#include "time/profile.hh"
#include "time/time.hh"

struct i4_profile_stack_item
{
  w64 start_clock;
  i4_profile_class *item;  
};

enum { I4_MAX_PROFILE_STACK_DEPTH=1000 };

extern int i4_profile_stack_top;

struct i4_profile_stack_struct
{
  static i4_profile_stack_item stack[I4_MAX_PROFILE_STACK_DEPTH];

  void overflow();
  void underflow();

  int top() { return i4_profile_stack_top; }

  void push(i4_profile_class *item, w64 current_clock)
  {
    if (top()==I4_MAX_PROFILE_STACK_DEPTH)
      overflow();

    stack[top()].item=item;
    stack[top()].start_clock=current_clock;
    i4_profile_stack_top++;
  }

  i4_profile_stack_item *pop()
  {
     if (!top())
       underflow();
    i4_profile_stack_top--;
    return stack+top();
  }

  i4_profile_stack_item *get_top() 
  { 
    if (top()) 
      return stack+top()-1;
    else return 0;
  }

  // this adds any time remaining on the stack into the profile classes
  // called before reports are formed
  void flush_stack()
  {
    i4_profile_stack_item *t=get_top();
    if (t)
    {
      w64 current_clock=i4_get_system_clock();
      t->item->total_time+=current_clock-t->start_clock;
      t->start_clock=current_clock;
    }
      
  }

  
  

};


#endif
