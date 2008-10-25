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
 

#ifndef I4_SUB_SECTION
#define I4_SUB_SECTION

#include "file/file.hh"

/*
The sub section file maps part of another file, it uses dup() on the other
file so seeks and closes won't cause problems.  The subsection file's offset 0,
begins somewhere inside the other file and reads are only allowed in this area.


 */

class i4_sub_section_file : public i4_file_class
{
  i4_file_class *fp;
  int fstart, fsize, foffset;
public:
  virtual w32 read (void *buffer, w32 size);
  virtual w32 write(const void *buffer, w32 size);
  virtual w32 seek (w32 offset);
  virtual w32 size ();
  virtual w32 tell ();

  virtual i4_bool async_read (void *buffer, w32 size, 
                              async_callback call,
                              void *context=0);

  i4_sub_section_file(i4_file_class *fp, int start, int size);
  ~i4_sub_section_file();
};


#endif
