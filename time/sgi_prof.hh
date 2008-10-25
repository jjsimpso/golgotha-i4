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
 


#include <time.h>

class i4_profile_class
{
public:
  static i4_profile_class *list;

  i4_profile_class *next;
  char *name; 

	timespec start_time;
  double total_time;
  w32 recursion_level;  // current level of recursion


  i4_profile_class(char *debug_name) : name(debug_name)
  {
    recursion_level=0;
    total_time=0;
    next=list;
    list=this;
  }

  void start()
  {
    if (recursion_level==0)
		{
			clock_gettime(CLOCK_SGI_CYCLE, &start_time);
		}

    recursion_level++; 
 }

  void stop()
  {
    recursion_level--;
    if (recursion_level==0)
    {
      struct timespec end;
			clock_gettime(CLOCK_SGI_CYCLE, &end);

      double endt=(double)(end.tv_sec+(double)end.tv_nsec/(double)10000000000000.0);
      double startt=(double)(start_time.tv_sec+(double)start_time.tv_nsec/(double)10000000000000.0);

      total_time+=endt-startt;
    }
  }
} ;
