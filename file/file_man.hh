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
 

#ifndef I4_FILE_MAN_HH
#define I4_FILE_MAN_HH

#include "file/file.hh"
#include "init/init.hh"

// see file/file.hh for a description of what each of these functions do
class i4_file_manager_class : public i4_init_class
{
public:
  int init_type() { return I4_INIT_TYPE_FILE_MANAGER; }

  static i4_file_manager_class *first;
  i4_file_manager_class *next;

  virtual i4_file_class *open(const i4_const_str &name, w32 flags=I4_READ) { return 0; }

  virtual i4_bool unlink(const i4_const_str &name) { return i4_F; }

  virtual i4_bool mkdir(const i4_const_str &name) { return i4_F; }

  virtual i4_bool get_status(const i4_const_str &filename, i4_file_status_struct &return_stat)
  { return i4_F; }

  virtual i4_bool get_directory(const i4_const_str &path, 
                                i4_directory_struct &dir_struct,
                                i4_bool get_status=i4_F,
                                i4_status_class *status=0) { return i4_F; }

  
  virtual i4_bool split_path(const i4_const_str &name, i4_filename_struct &fn);

  virtual i4_str *full_path(const i4_const_str &relative_name) { return 0; }
};


void i4_add_file_manager(i4_file_manager_class *fman, i4_bool add_front);
void i4_remove_file_manger(i4_file_manager_class *fman);

#endif
