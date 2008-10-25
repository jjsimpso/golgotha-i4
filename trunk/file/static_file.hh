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
 

#ifndef STATIC_FILE_HH
#define STATIC_FILE_HH

#include "file/file.hh"
#include <stdio.h>

class i4_static_file_class : public i4_file_class
{
public:
  FILE *f;

  i4_static_file_class() : f(0) {}
  i4_static_file_class(const char *name) : f(0) {  }
  ~i4_static_file_class() { if (f) fclose(f); }

  i4_static_file_class* open(const char *name)
  {
    if (f)
      fclose(f);
    f=0;

    if ((f = fopen(name, "wt")))
      return this;
    else
      return 0;
  }

  virtual w32 read (void *buffer, w32 size) { return 0; }
  virtual w32 write(const void *buffer, w32 size) { return fwrite(buffer, size, 1, f); }
  virtual w32 seek (w32 offset) { return 0; }
  virtual w32 size () { return 0; }
  virtual w32 tell () { return 0; }
};

#endif
