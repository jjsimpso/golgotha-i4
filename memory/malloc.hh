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
 

#ifndef __I4_MALLOC_HPP_
#define __I4_MALLOC_HPP_

#include "arch.hh"

#if 0 //( __linux && DEBUG )
#define i4_NEW_CHECK 1
#define i4_MEM_CHECK 1
#endif


void *i4_malloc(w32 size, char *file, int line);
void *i4_realloc(void *old_memory, w32 new_size, char *file, int line);

// if new checking, all news are logged by file and line number
// these logs can be obtained by calling i4_mem_report
// this is avaiable only under gcc

#ifdef i4_NEW_CHECK
#include <stdlib.h>
extern void *operator new( size_t size, char *file, w32 line);
//extern void *operator new [](size_t size, char *file, w32 line);
#define new new(__FILE__,__LINE__)

#define i4_malloc(size, reason) i4_malloc(size, __FILE__, __LINE__)
#define i4_realloc(old, new_size, reason) i4_realloc(old, new_size, __FILE__, __LINE__);
#else
#define i4_malloc(size, reason) i4_malloc(size, 0, 0)
#define i4_realloc(old, new_size, reason) i4_realloc(old, new_size, 0,0)

#endif

void i4_set_max_memory_used(int bytes);
void i4_set_min_memory_required(int bytes);

void i4_free(void *ptr);

void i4_mem_report(char *filename);
long i4_allocated();
long i4_available();
long i4_largest_free_block();

// for debugging purposes only...
int valid_ptr(void *ptr);        // returns 1 if is an address returned by i4_malloc
int valid_memory(void *ptr);     // returns 1 if address is in memory space managed by i4

#endif
