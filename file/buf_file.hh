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
 

#ifndef __I4BUF_FILE_HPP
#define __I4BUF_FILE_HPP

#include "file/file.hh"


// This file provides buffering for another i4_file_class

class i4_buffered_file_class : public i4_file_class
{
protected:
  friend void i4_async_buf_read_callback(w32 count, void *context);
  i4_file_class *from;
  void *buf;
  w32 buf_size,buf_start,buf_end,offset;
  i4_bool write_file;
public:
  i4_buffered_file_class(i4_file_class *from, 
                         w32 buffer_size=0x1000,
                         w32 current_offset=0);


  virtual w32 read (void *buffer, w32 size);
  virtual w32 write(const void *buffer, w32 size);
  virtual w32 seek (w32 offset);
  virtual w32 size ();
  virtual w32 tell ();

  virtual i4_bool async_read (void *buffer, w32 size, 
                              async_callback call,
                              void *context);

  ~i4_buffered_file_class();
};

#endif
