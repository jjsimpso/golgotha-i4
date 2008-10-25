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
 

#ifndef LI_INIT_HH
#define LI_INIT_HH



#include "init/init.hh"
#include "lisp/lisp.hh"


#define li_automatic_add_function(fun_name, char_name)             \
class li_add_##fun_name##_class : public i4_init_class             \
{                                                                  \
  int init_type() { return I4_INIT_TYPE_LISP_FUNCTIONS; }          \
  void init()  { li_add_function(char_name, fun_name);  }          \
} li_add_function_##fun_name


#define li_automatic_add_type(type, var)                           \
class li_add_##type##_class : public i4_init_class                 \
{                                                                  \
  int init_type() { return I4_INIT_TYPE_LISP_FUNCTIONS; }          \
  void init()  { var=li_add_type(new type);  }                     \
} li_add_type_##type##_instance


#endif
