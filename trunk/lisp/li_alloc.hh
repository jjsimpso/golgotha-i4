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
 

#ifndef LI_ALLOC_HH
#define LI_ALLOC_HH

#include "arch.hh"
class li_list;
class li_symbol;
class li_object;

void *li_cell8_alloc();
void li_cell8_free(void *ptr);

int li_gc();
i4_bool li_valid_object(li_object *o);
extern int li_max_cells;               // set this before i4_init to change limits

// if you have li_object's that are not referenced by the stack and by a symbol,
// and you do not what them to be garbage collected, you must derive one of these
// call mark() on all the objects you reference

class li_gc_object_marker_class
{
public:
  li_gc_object_marker_class *next;
  virtual void mark_objects(int set) { ; }
  li_gc_object_marker_class();      // automatically adds to list
  virtual ~li_gc_object_marker_class();
};


#endif
