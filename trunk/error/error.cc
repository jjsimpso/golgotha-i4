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
 

#include "error/error.hh"
#include "file/file.hh"
#include "init/init.hh"
#include "string/string.hh"

const char *i4_error_file_on;
int i4_error_line_on;


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#ifdef __sgi
#include <unistd.h>
#endif

class i4_debug_file_class : public i4_file_class
{
public:
  i4_debug_file_class() {}

  virtual w32 read (void *buffer, w32 size)
  {
    return fread(buffer, size, 1, stdin);
  }

  virtual w32 write(const void *buffer, w32 size) 
  {
    return fwrite(buffer, size, 1, stdout);
  }

  virtual w32 seek (w32 offset) { return 0; }
  virtual w32 size () { return 0; }
  virtual w32 tell () { return 0; }
};
static i4_debug_file_class default_debug;

i4_file_class *i4_debug=&default_debug;     // stream you can print debug messages to
FILE *i4_error_mirror_file=0;

int i4_default_error(const char *st)
{
  static int died=0;

  setbuf(stdout, 0);
    
  i4_debug->printf("*****************************************************************\n"
                   "Error (%s:%d) : %s\n"
                   "*****************************************************************\n",
                   i4_error_file_on, i4_error_line_on, st);

  if (died)
    return 1;
  died = 1;


  if (getenv("FORCE_CORE_DUMP"))
		return *((int *)0xDeadBeef);  // cause a memory fault to stop debugger
  _Exit(0);
  return -1;
}


int i4_default_warning(const char *st)
{
  i4_debug->printf("Warning (%s:%d) : %s\n", i4_error_file_on, i4_error_line_on, st);

  return 0;
}

i4_error_function_type i4_error_function=i4_default_error;
i4_error_function_type i4_warning_function=i4_default_warning;


int i4_error_old(const char *format, ...)
{
  va_list ap;
  char st[500];

  va_start(ap, format);
  vsprintf(st, format, ap);
  int ret = (*i4_error_function)(st);
  i4_debug->printf("Error : %s\n",st);
  va_end(ap);

  return ret;
}



int i4_warning_old(const char *format, ...)
{
  va_list ap;
  char st[500];

  va_start(ap, format);
  vsprintf(st, format, ap);
  int ret = (*i4_warning_function)(st);
  i4_debug->printf("Warning : %s\n",st);
  va_end(ap);

  return ret;
}

i4_error_pointer_type i4_get_error_function_pointer(const char *file, int line)
{
  i4_error_file_on=file;
  i4_error_line_on=line;
  return i4_error_old;
}

i4_error_pointer_type i4_get_warning_function_pointer(const char *file, int line)
{
  i4_error_file_on=file;
  i4_error_line_on=line;
  return i4_warning_old;
}



void i4_set_error_function(i4_error_function_type fun)
{
  i4_error_function=fun;
}

i4_error_function_type i4_get_error_function()
{
  return i4_error_function;
}

void i4_set_warning_function(i4_error_function_type fun)
{
  i4_warning_function=fun;
}


i4_error_function_type i4_get_warning_function()
{
  return i4_warning_function;
}



