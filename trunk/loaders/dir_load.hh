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
 

#ifndef I4_DIR_LOAD_HH
#define I4_DIR_LOAD_HH



#include "file/file.hh"
#include "memory/array.hh"
#include "error/error.hh"

struct i4_loader_section_type
{
  w32 section_offset;
  w32 section_id;
  w32 section_size;
  i4_loader_section_type(w32 section_id, w32 section_offset)
    : section_offset(section_offset), section_id(section_id) {}
};


class i4_loader_class : public i4_file_class
{
protected:
  i4_file_class *in;
  i4_array<i4_loader_section_type> sections;

  i4_bool close_on_delete, _error;
  sw32 last;
  int seek_to_before_using; 
  int find_section(w32 section_id);
public: 

  i4_bool error() { return _error; }

  i4_loader_class(i4_file_class *in, i4_bool close_on_delete=i4_T);

  i4_bool goto_section(w32 section_id);
  i4_bool goto_section(char *section_name);       // calls above with checksum of name
 
  i4_bool get_section_info(char *section_name, w32 &offset, w32 &size);

  // if version numbers don't match AND seek_on_fail is i4_T, file pointer 
  // is advanced to the spot where
  // end_version was called when saving and i4_F is returned
  i4_bool check_version(w16 version);
  void end_version(I4_LF_ARGS);          // verifies you read the proper amount of data

  //check_version replaced with get_version
  void get_version(w16 &version,w16 &data_size);
  
  
  virtual w32 read (void *buffer, w32 size);
  virtual w32 write(const void *buffer, w32 size);

  virtual w32 seek (w32 offset);
  virtual w32 size ();
  virtual w32 tell ();

  virtual ~i4_loader_class();
};

// returns NULL if file is corrupted
i4_loader_class *i4_open_save_file(i4_file_class *in,
                                   i4_bool close_on_delete_or_fail=i4_T);

// this function will insert data into a demo_file
i4_bool i4_insert_sections(i4_file_class *in, i4_file_class *out,
                           int total_sections_to_insert,
                           i4_file_class **section_data,
                           char **section_names);

#endif
