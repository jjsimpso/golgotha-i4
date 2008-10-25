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
 

#ifndef I4_DIR_SAVE_HH
#define I4_DIR_SAVE_HH


#include "file/file.hh"
#include "memory/array.hh"

struct i4_saver_section_type
{
  w32 section_offset;
  w32 section_id;
  i4_saver_section_type(w32  section_id, w32 section_offset)
    : section_offset(section_offset), section_id(section_id) {}
};


class i4_saver_class : public i4_file_class
{
protected:
  enum { DIRECTORY_CREATE, DATA_WRITE, DATA_LOAD } state;

  w32 current_offset, last_version_start, current_skip;

  i4_file_class *out;
  i4_bool close_on_delete;

  i4_array<w16>                    skips;
  i4_array<i4_saver_section_type>  sections;
  i4_array<w32>                    sizes;
  int marker_on;

public: 
  i4_saver_class(i4_file_class *out, i4_bool close_on_delete=i4_T);

  int mark_size();
  void end_mark_size(int marker_number);

  void mark_section(w32 section_id);
  void mark_section(char *section_name);  // calls above with checksum of name

  void start_version(w16 version);
  void end_version();

  i4_bool begin_data_write();          // returns false if error occured
 
  virtual w32 read (void *buffer, w32 size);
  virtual w32 write(const void *buffer, w32 size);

  virtual w32 seek (w32 offset) { return out->seek(offset); }
  virtual w32 size () { return out->size(); }
  virtual w32 tell ();

  virtual ~i4_saver_class();
};


#endif
