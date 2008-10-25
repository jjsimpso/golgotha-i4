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
 

#ifndef LI_OPTR_HH
#define LI_OPTR_HH

class li_object;

// anything referenced by a li_object_pointer will be marked as in use furing gc
class li_object_pointer
{
public:
  li_object *o;
  li_object_pointer *next;
  
  li_object_pointer(li_object *o=0);
  ~li_object_pointer();

  li_object& operator*() const { return *o; }
  li_object* operator->() const { return o; }
  li_object *get() { return o; }

  li_object_pointer &operator=(const li_object_pointer &other) { o=other.o;  return *this; }
  li_object_pointer &operator=(li_object *object) { o=object; return *this;}    
};


#endif
