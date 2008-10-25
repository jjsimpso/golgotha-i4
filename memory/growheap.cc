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
 

#include "memory/growheap.hh"
#include "error/error.hh"

i4_grow_heap_class::i4_grow_heap_class(w32 initial_size, w32 grow_increment)
//{{{
{
  increment=grow_increment;

  if (initial_size)
  {
    heap *h=new heap(initial_size,"initial grow heap");
    list.insert(*h);
    current_size=initial_size;
    current_offset=0;
  } 
  else 
  {
    current_size=0;
    current_offset=0;
  }
}
//}}}


void *i4_grow_heap_class::malloc(w32 size, char *description)           
//{{{
// description not used right now
{
  if (size==0) 
    return 0;

  if (current_offset+size<current_size)
  {
    void *ret=(void *)(((w8 *)list.begin()->data)+current_offset);
    current_offset+=size;
    return ret;
  } else
  {
    if (size>increment)
      i4_error("grow heap param problem");

    heap *h=new heap(increment,"grow heap");
    list.insert(*h);
    current_size=increment;
    current_offset=0;
    return malloc(size,description);
  }
}
//}}}


void i4_grow_heap_class::clear()
//{{{
{
  heap_iter p = list.begin();
  heap_iter q(p);

  current_offset=0;

  ++p;

  while (p != list.end())
  {
    list.erase_after(q);
    delete &*p;
    p = q;
    ++p;
  }
  

}
//}}}


//{{{ Emacs Locals
// Local Variables:
// folded-file: t
// End:
//}}}


