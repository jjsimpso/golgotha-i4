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
 

#ifndef I4_GROW_ARRAY_HH
#define I4_GROW_ARRAY_HH


#include "arch.hh"
#include "memory/malloc.hh"
#include "error/error.hh"

template <class T>
class i4_grow_array
//{{{
{
protected:
  T *entry;
  w32 used,entries,grow;
  char *name;
public:

  int size() const { return used; }

  T& operator[](int i) { return entry[i];  }

  i4_grow_array(w32 entries, char *name, w32 grow = 0) 
    : entries(entries), name(name), grow(grow), entry(0), used(0)
  {
    if (entries>0)
      entry = (T*)i4_malloc(sizeof(T)*entries, name);
    else
      entry = (T*)i4_malloc(sizeof(T)*grow, name);
  }

  w32 add(T item)
  {
    if (used>=entries)
    {
      if (grow)
      {
        entries += grow;
        T* new_entry = (T*)i4_realloc(entry, sizeof(T *)*entries, name);
        entry = new_entry;
      }
      else
        i4_error("i4_grow_array '%s' out of entries",name);
    }
    entry[used] = item;
    used++;
    return used-1;
  }

  void clear() { used = 0; }
  ~i4_grow_array() { i4_free(entry); }
};



#endif
