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
 

#ifndef BMANAGE_HH__
#define BMANAGE_HH__

#include "arch.hh"
#include "memory/malloc.hh"
class i4_file_class;  // file/file.hh

struct memory_node
{
  sw32 size;
#ifdef i4_MEM_CHECK
  char *name;                     // name is allocated on regular heap
#endif                            // because it is used for debugging purposes
                                  // and will probably be run on my linux box with VMM
  memory_node *next;
};


struct small_block
{  
  sw32 size;                     // size of blocks...
  w32 alloc_list;               // bit field saying weither each block is allocated or not.
  small_block *next;                      // next small block of same size
#ifdef i4_MEM_CHECK
  char *name[32];
#endif 
} ;

// above 128 bytes is considered to be a big block and no hashing is done
#define JM_SMALL_SIZE 128      

class i4_block_manager_class
{
  public :

  sw32 block_size;                             // size of this memory_block
  small_block *sblocks[JM_SMALL_SIZE];
  void *addr;

  memory_node *sfirst,*slast;


  void init(void *block, long Block_size);
  void *alloc(long size, char *name);
  void free(void *ptr);

  long largest_free_block();
  long available();
  long allocated();
  long pointer_size(void *ptr);
  void report(i4_file_class *fp);
  void inspect();

  int valid_ptr(void *ptr);     // only called from within debugger
};

#endif
