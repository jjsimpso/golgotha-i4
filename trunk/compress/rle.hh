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
 

#ifndef I4_RLE_HH
#define I4_RLE_HH

#include "file/file.hh"

template <class T>
class i4_rle_class
{
  T last_value;
  T raw[256];
  int run_count;
  int raw_count;
  i4_file_class *fp;
  
public:
  i4_rle_class(i4_file_class *fp) : fp(fp)
  { 
    run_count=0; 
    raw_count=0;
  }

  void flush()
  {
    if (run_count)
    {
      fp->write_8(run_count);
      *fp << last_value;
      run_count=0;
    }
    else if (raw_count)
    {
      fp->write_8(128 | raw_count);
      for (int i=0; i<raw_count; i++)
        *fp << raw[i];
      raw_count=0;
    }
  }

  void write(T v)
  {
    if (run_count)
    {
      if (last_value==v && run_count!=127)
        run_count++;
      else
      {
        flush();
        raw_count=1;
        raw[0]=v;
      }        
    }
    else if (raw_count>1 && raw[raw_count-1]==raw[raw_count-2] && raw[raw_count-1]==v)
    {
      raw_count-=2;
      run_count=0;
      flush();
      run_count=3;
      last_value=v;
    }
    else 
    {
      if (raw_count==127) flush();
      raw[raw_count++]=v;
    }   
  }

  T read()
  {
    if (run_count)
    {
      run_count--;
      return last_value;
    }
    else if (raw_count)
    {
      raw_count--;
      T ret;
      *fp >> ret;
      return ret;
    }
    else 
    {
      int v=fp->read_8();
      if (v&128)
      {
        raw_count=v&(~128);
      }
      else 
      {
        run_count=v;
        *fp >> last_value;
      }
      return read();
    }
  }

  ~i4_rle_class() { flush(); }
};

#endif
