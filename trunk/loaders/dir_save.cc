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
 

#include "loaders/dir_save.hh"
#include "checksum/checksum.hh"
#include "memory/malloc.hh"
#include <string.h>

w32 i4_saver_class::tell () 
{ 
  if (state==DIRECTORY_CREATE)
    return current_offset;
  else
    return out->tell(); 
}

i4_saver_class::i4_saver_class(i4_file_class *out, i4_bool close_on_delete)
  : out(out),
    close_on_delete(close_on_delete),
    skips(0,256),
    sections(0,256),
    sizes(0, 512)
{
  state=DIRECTORY_CREATE;
  current_offset=out->tell();
}

int i4_saver_class::mark_size()
{
  if (state==DIRECTORY_CREATE)
  {
    current_offset+=4;

    int num=sizes.size();
    sizes.add(current_offset);
    
    return num;
  }
  else
  {
    out->write_32(sizes[marker_on++]);
    return 0;
  }
}

void i4_saver_class::end_mark_size(int marker_number)
{
  if (state==DIRECTORY_CREATE)
    sizes[marker_number]=current_offset-sizes[marker_number];
}


void i4_saver_class::start_version(w16 version)
{
  if (state==DIRECTORY_CREATE)
  {
    last_version_start=current_offset;
    current_offset+=4;
  }
  else
  {
    out->write_16(version);
    out->write_16(skips[current_skip++]);
  }
}

void i4_saver_class::end_version()
{
  if (state==DIRECTORY_CREATE)
    skips.add(current_offset-last_version_start);
}

void i4_saver_class::mark_section(w32 section_id)
{
  if (state==DIRECTORY_CREATE)
  {
#ifdef DEBUG
    for (int i=0; i<sections.size(); i++)
      if (sections[i].section_id==section_id)
        i4_error("mark_section : section_id arleady used");
    
#endif          
    sections.add(i4_saver_section_type(section_id, current_offset));
  }
}


void i4_saver_class::mark_section(char *section_name)  // calls above with checksum of name
{
  mark_section(i4_check_sum32(section_name, strlen(section_name)));
}


i4_bool i4_saver_class::begin_data_write()
{
  marker_on=0;
  state=DATA_WRITE;  
  current_skip=0;

  w32 signature=i4_check_sum32((void*)"GOLG_SECTION_ID=32",17);

  if (out->write_32(signature)!=sizeof(w32)) return i4_F;
  if (out->write_32(sections.size())!=sizeof(w32)) return i4_F;

  w32 off=4 + 4 +  sections.size() * (4 + 4);

  for (sw32 i=0; i< sections.size(); i++)
  {
    if (out->write_32(sections[i].section_id)!=sizeof(w32)) return i4_F;
    if (out->write_32(sections[i].section_offset + off)!=sizeof(w32)) return i4_F;
  }
  return i4_T;
}

w32 i4_saver_class::read (void *buffer, w32 size)
{
  i4_error("Bad bad");
  return 0;
}

w32 i4_saver_class::write(const void *buffer, w32 size)
{
  if (state==DIRECTORY_CREATE)
  {
    current_offset+=size;
    return size;
  }
  else
    return out->write(buffer,size);
}


i4_saver_class::~i4_saver_class()
{
  if (close_on_delete && out)
    delete out;
}

