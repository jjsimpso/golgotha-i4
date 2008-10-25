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
 

//{{{ Table Template
//
//  Expanding Array Class
//
//$Id: table.hh,v 1.3 1999/09/03 04:02:21 rob Exp $
//}}}

#ifndef I4_TABLE_HH
#define I4_TABLE_HH

#include "arch.hh"
#include "error/error.hh"
#include "memory/malloc.hh"

//#define I4_TABLE_NO_GROWTH

template <class T>
class i4_table
{
protected:
  T *entry;
  w16 used,entries;
#ifndef I4_TABLE_NO_GROWTH
  w16 grow;
#endif
public:

  int size() const { return used; }
  T& operator[](int i) const 
  //{{{
  {
    I4_ASSERT(i>=0 && i<used, "table::bad array reference");
    return entry[i]; 
  }
  //}}}

  i4_table(int entries, int grow = 0) : entries(entries), entry(0), used(0)
#ifndef I4_TABLE_NO_GROWTH
                                        ,grow(grow)
#endif
  //{{{
  {
    if (entries>0)
      entry = (T*)i4_malloc(sizeof(T)*entries,"table");

    I4_ASSERT(entry, "table::can't allocate entries");
  }
  //}}}

  ~i4_table() 
  //{{{
  {
    clear(); 
    i4_free(entry);
    entries = 0;
  }
  //}}}

  int add(T item,int ref = -1)
  //{{{
  {
    I4_ASSERT(item, "table::bad item add");

    if (ref<0)
      ref += used+1;

    I4_ASSERT(ref>=0 && ref<=used,"table::bad item referenced");

    if (used>=entries)
    {
#ifndef I4_TABLE_NO_GROWTH
      if (grow)
      {
        entries += grow;

        T* new_entry = (T*)i4_realloc(entry, sizeof(T *)*entries, "table");
        
        I4_ASSERT(new_entry, "table::out of memory");

        entry = new_entry;
      }
      else
#endif
        I4_ASSERT(0, "table::out of entries");
    }

    for (int i=used; i>ref; i--)
      entry[i] = entry[i-1];
    entry[ref] = item;
    used++;

    return ref;
  }
  //}}}

  int add_table(const i4_table& tab,int ref = -1)
  //{{{
  {
    if (ref<0)
      ref += used+1;

    I4_ASSERT(ref>=0 && ref<=used,"table::bad item referenced");

    if (used+tab.size() >= entries)
    {
#ifndef I4_TABLE_NO_GROWTH
      if (grow)
      {
        if (used+tab.size() >= entries+grow)
          entries = used+tab.size();
        else
          entries += grow;

        T* new_entry = (T*)i4_realloc(entry, sizeof(T *)*entries, "table");
        
        I4_ASSERT(new_entry, "table::out of memory");

        entry = new_entry;
      }
      else
#endif
        I4_ASSERT(0, "table::out of entries");
    }

    int i;

    for (i=used-1; i>ref; i--)
      entry[i+tab.size()] = entry[i];
    for (i=0; i<tab.size(); i++)
      entry[ref+i] = tab.entry[i];

    used+=tab.size();

    return ref;
  }
  //}}}

  void remove(int ref)
  //{{{
  {
    I4_ASSERT(ref>=0 && ref<used, "table::bad item deletion");

    used--;
    for (int i=ref; i<used; i++)
      entry[i] = entry[i+1];
  }
  //}}}

  void clear()
  //{{{
  {
    used = 0;
  }
  //}}}
};

#endif

//{{{ Emacs Locals
// Local Variables:
// folded-file: t
// End:
//}}}
