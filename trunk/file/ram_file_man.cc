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
 

#include "file/ram_file_man.hh"
#include "file/ram_file.hh"
#include "file/file_man.hh"
#include "string/string.hh"

i4_openable_ram_file_info *i4_flist=0;

class i4_ram_file_manager_class : public i4_file_manager_class
{  
public: 

  virtual i4_file_class *open(const i4_const_str &name, w32 flags)
  {
    if (flags==I4_READ)
    {
      char buf[256];
      i4_os_string(name, buf, 256);

      for (i4_openable_ram_file_info *f=i4_flist; f; f=f->next)
        if (strcmp(buf, f->filename)==0)
          return new i4_ram_file_class(f->data, f->data_size);         
    }

    return 0;
  }

  i4_ram_file_manager_class()
  {
    i4_add_file_manager(this, i4_F);
  }

  ~i4_ram_file_manager_class()
  {
    i4_remove_file_manger(this);
  }
} i4_ram_file_manager_instance;

i4_openable_ram_file_info::i4_openable_ram_file_info(char *filename, void *data, w32 data_size)
  : filename(filename), data(data), data_size(data_size)
{ 
  next=i4_flist;
  i4_flist=this;
}
