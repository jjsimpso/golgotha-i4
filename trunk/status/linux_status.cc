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
 

enum { I4_STAT_LEN=70 };

#include "status/status.hh"
#include <stdlib.h>

class i4_linux_status_class : public i4_status_class
{
public:
  int last_percent;
  i4_linux_status_class() { last_percent=0; }

  virtual i4_bool update(float per)
  {
    while (per*I4_STAT_LEN > last_percent)
    {
      fprintf(stderr,".");
      last_percent++;
    }
  }

  virtual ~i4_linux_status_class()
  {
    int i;
    while (last_percent<I4_STAT_LEN)
    {
      fprintf(stderr,".");
      last_percent++;
    } 

    for (i=0; i<=I4_STAT_LEN; i++)      // backup
      fprintf(stderr,"%c",'\b');
    for (i=0; i<=I4_STAT_LEN+1; i++)     // erase
      fprintf(stderr,"%c",' ');
    for (i=0; i<=I4_STAT_LEN+1; i++)     // and backup again
      fprintf(stderr,"%c",'\b');    
  }
};

// this is operating system dependant
i4_status_class *i4_create_status(const i4_const_str &description, int allow_cancel)
{
  int i,j=description.length()>I4_STAT_LEN ? I4_STAT_LEN : description.length();
  fprintf(stderr,"[");
  
  i4_const_str::iterator it=description.begin();
  for (i=0; i<j;i++, ++it)
    fprintf(stderr,"%c",it.get().value());

  for (i=0; i<I4_STAT_LEN-j; i++)
    fprintf(stderr,"%c",' ');

  fprintf(stderr,"]");
  for (i=0; i<=I4_STAT_LEN; i++)     // erase
    fprintf(stderr,"%c",'\b');

  return new  i4_linux_status_class;
}
