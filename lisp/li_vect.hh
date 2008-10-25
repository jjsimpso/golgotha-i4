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
 

#ifndef LI_VECT_HH
#define LI_VECT_HH


#include "lisp/li_types.hh"
#include "math/vector.hh"
#include "lisp/li_class.hh"

extern li_type_number li_vect_type;
class li_vect : public li_object
{
  friend class li_vect_type_function_table;
  i4_3d_vector *v;
public:
  li_vect(i4_3d_vector _v) :li_object(li_vect_type), v(new i4_3d_vector)
  { 
    *v=_v;
  }

  li_vect(i4_3d_vector *v) : li_object(li_vect_type), v(v) {}

  i4_3d_vector &value() { return *v; }  
  static li_vect *get(li_object *o, li_environment *env)
  { check_type(o, li_vect_type, env); return ((li_vect *)o); }
} ;



struct li_vect_class_member : public li_class_member
{
  li_vect_class_member(char *name) : li_class_member(name) {}
  i4_3d_vector &operator()() { return li_vect::get(li_this->get(*this),0)->value(); }
};


#endif
