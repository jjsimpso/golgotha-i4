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
 

#ifndef I4_DLL_MAN_HH
#define I4_DLL_MAN_HH

#include "init/init.hh"
#include "dll/dll.hh"
#include "string/string.hh"
#include "isllist.hh"

class i4_dll_manager_class : public i4_init_class
{
protected:
  struct dll_node
  {
    dll_node      *next;
    i4_str        *name;
    i4_dll_file   *dll;
    i4_init_class *init_list;  // list of all i4_init_class'es in the dll
    ~dll_node();
  };

  virtual int init_type() { return I4_INIT_TYPE_DLLS; }
  i4_isl_list<dll_node> dll_list;

  virtual void init();     // called by i4_init
  virtual void uninit();

public:
  i4_bool load(const i4_const_str &dll_name, i4_bool prepend_dll_dir=0);
  i4_bool is_loaded(const i4_const_str &dll_name);
  i4_bool unload(const i4_const_str &dll_name);  
};

extern i4_dll_manager_class i4_dll_man;

extern char *i4_dll_dir;

#endif
