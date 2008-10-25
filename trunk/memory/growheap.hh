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
 


/* 
   Grow heap will only grow, it never shrinks.
   It should not be used for allocating large blocks.  And
   the largest allocation request should be less than grow_increment.

 */

#ifndef __GROWHEAP_HPP_
#define __GROWHEAP_HPP_

#include "memory/malloc.hh"
#include "isllist.hh"

class i4_grow_heap_class
{
public:
  class heap
  {
  public:
    heap *next;
    void *data;
    heap(w32 size, char *name) { data=i4_malloc(size,name); name=0; }
    ~heap() { i4_free(data); }
  } ;

  typedef i4_isl_list<heap>           heap_list;
  typedef i4_isl_list<heap>::iterator heap_iter;

  heap_list list;
  w32 current_offset,increment,current_size;

  i4_grow_heap_class(w32 initial_size, w32 grow_increment);
  void *malloc(w32 size, char *description);           // description not used right now
  ~i4_grow_heap_class() { list.destroy_all(); }
  void clear();
} ;


#endif
