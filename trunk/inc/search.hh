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
 


#ifndef I4_SEARCH_HH
#define I4_SEARCH_HH

#include "arch.hh"

// binary search template for sorted array
//
//  if found,     returns i4_T and location of item in loc
//  if not found, returns i4_F and location of insertion point in loc
//

typedef int (*i4_bsearch_compare_function_type)(const void *key, const void *member);

i4_bool i4_base_bsearch(const void *member, w32 &loc, 
                        const void *array, w32 member_size, w32 size, 
                        i4_bsearch_compare_function_type compare);

template <class Key, class T>
i4_bool i4_bsearch(const Key* member, w32 &loc,
                   const T* array, w32 size, int (*compare)(const Key*, const T*))
{
  return i4_base_bsearch(member, loc, array, sizeof(T), size, 
                         (i4_bsearch_compare_function_type)compare);
}

#endif
