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
 

#ifdef _WINDOWS
#include <windows.h>
#include <windef.h>
#include <winbase.h>
#endif

#include "arch.hh"
#include "time/time.hh"

#include <stdio.h>
#include <stdlib.h>

sw32 i4_win32_start_clock=GetTickCount();

void i4_time_class::get()
{
  time.win32_time.clock=GetTickCount()-i4_win32_start_clock;
  time.win32_time.overflow=0;
}

void i4_time_class::add_milli(sw32 milli_sec)
{
  time.win32_time.clock+=milli_sec;
}



i4_bool i4_time_class::operator <(const i4_time_class &other) const 
{ 
  return (other.time.win32_time.clock<time.win32_time.clock);
}



i4_bool i4_time_class::operator >(const i4_time_class &other) const 
{ 
  return (other.time.win32_time.clock<time.win32_time.clock);
}


sw32 i4_time_class::milli_diff(const i4_time_class &past_time) const
{
  return (sw32)time.win32_time.clock-(sw32)past_time.time.win32_time.clock;
}

i4_time_class::i4_time_class(sw32 milli_sec)
{
  time.win32_time.clock=milli_sec - i4_win32_start_clock;
}


w64 i4_get_system_clock()
{
  w32 lo, hi;
  __asm
    {
      __emit 0x0F
      __emit 0x31
      mov lo, eax
      mov hi, edx
    };
  return (((w64)hi)<<32) | lo;
}

int i4_win_clocks_per_sec = -1;

int i4_get_clocks_per_second()
{
  if (i4_win_clocks_per_sec==-1)
  {
    w64 _start = i4_get_system_clock();
  
    i4_time_class now,start;
    while (now.milli_diff(start) < 1000) now.get();
  
    w64 end = i4_get_system_clock();

    i4_win_clocks_per_sec = end - _start;
  }
  
  return i4_win_clocks_per_sec;
}

void i4_sleep(int seconds) { Sleep(seconds*1000); }
void i4_milli_sleep(int milli_seconds) { Sleep(milli_seconds); }
