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
 

//{{{ Linear Allocator template
//
//  Implements a memory allocator that has constant time memory
//  allocation and deallocation.  Heap can optionally grow by a fixed 
//  amount when no items are left.
//
//Usage:
//
//  Create allocator with:
//    
//    i4_linear_allocator_template<type> Name(intial_number_of_items,
//                               growth_rate,
//                               debugging string
//                              );
//   
//  Get new item with:
//    
//    item = Name.alloc();
//
//  Free previously allocated item with:
//
//    Name.free(item);
//
//  When I4_DEBUG is defined, you can dump the contents of the
//    allocator with:
//
//    Name.dump();
//
//Oliver Yu
//
//$Id: lalloc.hh,v 1.5 1999/10/02 04:20:54 rob Exp $
//copyright 1996  Crack dot Com

#ifndef LALLOC_HPP
#define LALLOC_HPP

#include "arch.hh"
#include "memory/malloc.hh"
#include "error/error.hh"
#include "threads/threads.hh"
#include <stdio.h>

class i4_linear_allocator
{
protected:
  i4_critical_section_class lock;

  class PreBlock
  {
    typedef char *pointer;
  public:
    PreBlock *link;
#ifdef I4_DEBUG
    w32 items;
#endif
    void *GetPtr(int i, int size)
    {
      return (void*)(((pointer)this) + sizeof(PreBlock) + size*i );
    }

    void *init(w32 size, PreBlock *_link, w32 _items, void *_next)
    {
      void *ref;
#ifdef I4_DEBUG
      items = _items;
#endif
      link = _link;
      for (w32 i=0; i<_items; i++)
      {
        ref = GetPtr(i, size);
        *((void **)ref) = _next;
        _next = ref;
      }
      return _next;
    }

#ifdef I4_DEBUG
    void dump(w32 size)
    {
      printf("PreBlock: %p", GetPtr(0, size));
      for (w32 i=0; i<items; i++)
      {
        if (i%4 == 0)
          printf("\n%3lx: ",i);
        printf("%8lx ", *((w32*)GetPtr(i, size)) );
      }
      printf("\n");
    }

    int valid_pointer(void *ptr, int size)
    {
      w32 offs = (w32)((pointer)ptr - (((pointer)this) + sizeof(PreBlock)));

      return ( (offs/size < items) && (offs%size == 0) );
    }
#endif
  };
  
  PreBlock *mem;
  void *next;
  w32 size, grow;
  char *name;

  //{{{ Debugging Variables
#ifdef I4_DEBUG
  w32 blocks, items;
#endif
public:
  i4_linear_allocator(w32 size, w32 _number, w32 _grow, char *_name)
    : mem(0), next(0),
      size(size),
      grow(_grow),
      name(_name) 
  //
  //  Create linear allocator
  //
  //Param:
  //  w32 _number    number of items to start with
  //  w32 _grow      number of items to grow when out of free items
  //  char *_name    name of allocator for debugging
  //
  //{{{Notes:
  //  if _grow is 0, allocator will display an error when out of items
  //  if _number is 0, no space will be allocated until first item request
  {
    lock.lock();
    if (_number>0) {
      mem = (PreBlock*)i4_malloc( size*_number + sizeof(PreBlock), name );
      // assert(mem);
      next = mem->init(size, 0, _number, next);
    }
#ifdef I4_DEBUG
    items = 0;
    if (mem)
      blocks = 1;
#endif
    lock.unlock();
  }


  ~i4_linear_allocator()
  //
  //  destroys blocks of memory used by allocator
  {
    PreBlock *p;

    while (mem)
    {
      p = mem->link;
      i4_free((void*)mem);
      mem = p;
    }
  }
  
  void* alloc()
  //
  //  allocate an item void
  {
    lock.lock();
    void* ret;

    if (next)
    {
      ret = next;
      next = *((void **)next);
    }
    else
    {
      if (grow==0)
      {
	// Out of items, and can't grow
	printf("Allocator '%s' out of items\n",name);
      }

      PreBlock *newblock =
        (PreBlock*) i4_malloc( size*grow + sizeof(PreBlock), name );
      next = newblock->init(size, mem, grow, next);
      mem = newblock;

      ret = next;
      next = *((void **)next);
#ifdef I4_DEBUG
      blocks++;
#endif
    }
#ifdef I4_DEBUG
    items++;
#endif
    lock.unlock();

    return ret;
  }
  
  void free(void *item)
  //
  //  free item T back into pool
  //
  {
    lock.lock();

#ifdef I4_DEBUG
    PreBlock *p;

    p = mem;
    while ( p && !p->valid_pointer(item, size) )
      p = p->link;
    if (!p)
    {
      // invalid pointer! do error
      printf("Bad free!\n");
      return;
    }
#endif
    *((void **)item) = next;
    next = item;
#ifdef I4_DEBUG
    items--;
#endif
    lock.unlock();
  }
  
#ifdef I4_DEBUG

  //  debugging dump of contents of linear allocator
  void dump()
  {
    PreBlock *p;

    printf( "i4_linear_allocator '%s'\n"
           "Items: %ld  Blocks: %ld\n"
           "Next: %p\n",name, items, blocks, next);
    p = mem;
    while (p)
    {
      p->dump(size);
      p = p->link;
    }
  }
#endif
};

template <class T>
class i4_linear_allocator_template : public i4_linear_allocator
{
public:
  i4_linear_allocator_template(w32 _number, w32 _grow, char *_name) 
    : i4_linear_allocator(sizeof(T), _number, _grow, _name) {}

  T* alloc() { return (T*)i4_linear_allocator::alloc(); }
  void free(T *item) { i4_linear_allocator::free((void*)item); }
};

#endif
