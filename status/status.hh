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
 

#ifndef I4_STATUS_HH
#define I4_STATUS_HH

#include "arch.hh"
class i4_const_str;

class i4_status_class
{
public:
  virtual i4_bool update(float percent) = 0;   // percent should be 0..1, ret false for cancel
  virtual ~i4_status_class() { ; }
};

enum { I4_STATUS_ALLOW_CANCEL=1,
       I4_STATUS_UNKNOWN_TOTAL=2 };
    
// this is operating system dependant
i4_status_class *i4_create_status(const i4_const_str &description, int flags=0);


typedef i4_status_class *(*i4_status_create_function_type)(const i4_const_str &description,
							   int flags); 
void i4_set_status_create_function(i4_status_create_function_type fun);

class i4_idle_class
{  
public:
  static i4_idle_class *first;
  i4_idle_class *next;

  virtual void idle() = 0;

  i4_idle_class();
  virtual ~i4_idle_class();
};

#endif
