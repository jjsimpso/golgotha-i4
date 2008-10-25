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
 

#include "loaders/wav_load.hh"
#include "file/file.hh"

// system independently ordered 4 byte id
inline w32 CtoID(char a, char b, char c, char d)
{
  return l_to_msb( (((w32)a)<<24) | (((w32)b)<<16) | (((w32)c)<<8) | ((w32)d) );
}


i4_bool i4_load_wav_info(i4_file_class *f, i4_sound_info &info)
{
  w32 end_pos, chunk_type, len;

  // look for RIFF signature
  if (f->read_32() != CtoID('R','I','F','F'))
    return i4_F;

  end_pos = f->read_32();
  end_pos += f->tell();

  // look for WAVE sig
  if (f->read_32() != CtoID('W','A','V','E'))
    return i4_F;

  // read all data chunks
  while (f->tell() < end_pos)
  {
    chunk_type = f->read_32();
    len = f->read_32();

    if      (chunk_type == CtoID('f','m','t',' '))
    {
      // sound format info
      f->read_16();
      info.channels = f->read_16();
      info.sample_rate = f->read_32();
      f->read_32();
      f->read_16();
      info.sample_size = f->read_16()/8;

      f->seek(f->tell() + len - 16);
    }
    else if (chunk_type == CtoID('d','a','t','a'))
    {
      info.size = len;

      return i4_T;
    }
    else
      f->seek(f->tell() + len);

  }

  return i4_F;
}
