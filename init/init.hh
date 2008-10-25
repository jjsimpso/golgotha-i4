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
 

//{{{ Global Initializers Class
//
// all classes that need initialization at the begining of main should derive themselves from
// this no class should allocate memory or interact with other classes before the "init stage" 
// which follows the "construction stage"
//
//$Id: init.hh,v 1.3 1999/09/03 04:02:22 rob Exp $

#ifndef __i4INIT_HPP_
#define __i4INIT_HPP_

#include "arch.hh"

// these type numbers determine the order i4_init_class'es are initialized in
// deinitialization occurs in the reverse order
enum {
  I4_INIT_TYPE_MEMORY_MANAGER,     // main i4 memory manager
  I4_INIT_TYPE_THREADS,            // initialized thread info
  I4_INIT_TYPE_LISP_MEMORY,        // for lisp object allocations - uses i4 memory manager,
  I4_INIT_TYPE_LISP_BASE_TYPES,    // adds lisp types into the system (li_int.. etc)
  I4_INIT_TYPE_LISP_FUNCTIONS,     // adds lisp fuinctions (li_load & any user li_automatic..
  I4_INIT_TYPE_STRING_MANAGER,
  I4_INIT_TYPE_FILE_MANAGER,
  I4_INIT_TYPE_DLLS,
  I4_INIT_TYPE_OTHER
};

       
class i4_init_class
{
public:
  static i4_init_class *first_init; 
  i4_init_class *next_init;

  virtual int init_type() { return I4_INIT_TYPE_OTHER; }

  virtual void init()   {}
  virtual void uninit() {}

  i4_init_class();
  virtual ~i4_init_class();
};

// should be called at the begining of main (after memory manager is initialized)
void i4_init();

// should be called at the end of main (after memory manager is deinitialized)
void i4_uninit();                            

// used to report errors when things should be executed only when i4 is initialized
i4_bool i4_is_initialized();

#endif

