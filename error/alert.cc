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
 

#include "error/alert.hh"
#include <stdio.h>


extern FILE *i4_error_mirror_file;

int i4_default_alert(const i4_const_str &ret)
//{{{
{
#ifdef __MAC__
  printf("Alert : ");
  i4_const_str::iterator s=ret.begin();
  while (s!=ret.end())
  {
    printf("%c",s.get().value());
    ++s;
  }
  printf("\n");
#else
  fprintf(stderr,"Alert : ");
  i4_const_str::iterator s=ret.begin();
  while (s!=ret.end())
  {
    fprintf(stderr,"%c",s.get().value());
    ++s;
  }
  fprintf(stderr,"\n");
#endif

  return 0;
}
//}}}

i4_alert_function_type i4_alert_function=i4_default_alert;

void i4_alert(const i4_const_str &format, w32 max_length, ...)
{
  va_list ap;
  va_start(ap, max_length);

  i4_str *ret=format.vsprintf(500,ap);  
  (*i4_alert_function)(*ret);

#if defined(WIN32)
  if (!i4_error_mirror_file)
    i4_error_mirror_file = fopen("error.out","wt");
  if (i4_error_mirror_file)
  {
    fprintf(i4_error_mirror_file,"Alert : ");
    i4_const_str::iterator s=ret->begin();
    while (s!=ret->end())
    {
      fprintf(i4_error_mirror_file,"%c",s.get().value());
      ++s;
    }
    fprintf(i4_error_mirror_file,"\n");
  }
#endif

  delete ret;
  va_end(ap);
}


void i4_set_alert_function(i4_alert_function_type fun)
{
  i4_alert_function=fun;
}


