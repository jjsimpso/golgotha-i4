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
 

#ifndef I4_RAM_FILE_HH
#define I4_RAM_FILE_HH

#include "file/file.hh"
#include <memory.h>

class i4_ram_file_class : public i4_file_class
{
  w8 *buf;
  w32 bs, offset;

public:
  virtual i4_file_class *dup() 
  { 
    i4_file_class *f=new i4_ram_file_class(buf, bs);
    f->seek(tell());
    return f;
  }

  i4_ram_file_class(void *buffer, int buffer_size)
    : buf((w8 *)buffer), bs(buffer_size), offset(0) { ; }
  
  virtual w32 read (void *buffer, w32 size)
  {
    if (size>bs-offset)
      size=bs-offset;
    memcpy(buffer, buf+offset, size);
    offset+=size;
    return size;
  }
    
  virtual w32 write(const void *buffer, w32 size)
  {
    if (size>bs-offset)
      size=bs-offset;
    memcpy(buf+offset, buffer, size);
    offset+=size;
    return size;
  }

  virtual w32 seek (w32 _offset) { offset=_offset; return offset; }
  virtual w32 size ()            { return bs;      }
  virtual w32 tell ()            { return offset;  }
};


#endif
