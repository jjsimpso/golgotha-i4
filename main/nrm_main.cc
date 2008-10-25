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
 

#include "main/main.hh"
#include "string/string.hh"
#include "error/error.hh"
#include "file/file.hh"

#include <stdlib.h>


class tmp_main_str : public i4_const_str
{
public:
  tmp_main_str();
  void set_ptr(char *_ptr)
  {
    ptr=_ptr;
    len=strlen(ptr); 
  }
};

w32	      i4_global_argc;
i4_const_str *i4_global_argv;


void *i4_stack_base=0;

int main(int argc, char **argv)
{
  long t;
  i4_stack_base=(void *)(&t);


  tmp_main_str *tmp=(tmp_main_str *)malloc(sizeof(tmp_main_str)*(argc+1));
  for (int i=0; i<argc; i++)
    tmp[i].set_ptr(argv[i]);

  i4_global_argc=argc;
  i4_global_argv=tmp;
  i4_main(argc,tmp);
  free(tmp);
  
#ifdef __linux
  return 0;
#else
  return 1;
#endif
}
