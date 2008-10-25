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
 

#include "file/sub_section.hh"
#include "error/error.hh"


w32 i4_sub_section_file::read (void *buffer, w32 rsize)
{
  if (foffset-fstart+(int)rsize>fsize)  // don't allow reads past the sub section
    rsize=fstart+fsize-foffset;

  int rs=fp->read(buffer, rsize);
  foffset+=rs;
  return rs;
}

w32 i4_sub_section_file::write(const void *buffer, w32 size)
{
  i4_error("don't write here");
  return 0;
}


w32 i4_sub_section_file::seek(w32 offset)
{
  if ((int)offset>=fsize)
    offset=fsize-1;
  
  foffset=fstart+offset;
  fp->seek(foffset);
  return foffset;
}

w32 i4_sub_section_file::size()
{
  return fsize;
}

w32 i4_sub_section_file::tell()
{
  return foffset-fstart;
}


i4_sub_section_file::i4_sub_section_file(i4_file_class *_fp, int start, int size)
{
  fp=_fp;
  if (!fp)
    i4_error("no file");

  fp->seek(start);
  fsize=size;
  fstart=start;
  foffset=start;
}

i4_sub_section_file::~i4_sub_section_file()
{
  if (fp)
    delete fp;
}


i4_bool i4_sub_section_file::async_read (void *buffer, w32 size, 
                                         async_callback call,
                                         void *context)
{
  if (foffset-fstart+(int)size>fsize)  // don't allow reads past the sub section
    size=fstart+fsize-foffset;


  foffset+=size;  
  return fp->async_read(buffer, size, call, context);
}
