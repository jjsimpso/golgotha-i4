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
 

#ifndef __i4TIME_HPP_
#define __i4TIME_HPP_

#include "arch.hh"
 
#include <stdlib.h>
#include <string.h>

class i4_time_class
{
  union
  {
    struct
    {
      sw32 sec, usec;
    } unix_time;

    struct 
    {
      sw32 clock;
      sw32 overflow;
    } win32_time;
  } time;
  
public:

  i4_time_class(sw32 milli_sec);


  i4_bool operator <(const i4_time_class &other) const;
  i4_bool operator >(const i4_time_class &other) const;

  // copies the time from another previously created i4_time_class
  i4_time_class(const i4_time_class &ref) 
  { 
    time=ref.time;
  }

  void get();    // gets the time from the system

  void add_milli(sw32 milli_sec);

  i4_time_class()
  { get(); }

  sw32 milli_diff(const i4_time_class &past_time) const;  
  // returns difference between our time and a past time in 1/1000th of a second
};

w64 i4_get_system_clock();
int i4_get_clocks_per_second();

void i4_sleep(int seconds);
void i4_milli_sleep(int milli_seconds);   // 1/100th of a seconds

#endif

//{{{ Emacs Locals
// Local Variables:
// folded-file: t
// End:
//}}}
