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
 

#ifndef CONTEXT_HH
#define CONTEXT_HH

#include "area/rectlist.hh"

class i4_draw_context_class
{
  public :
  i4_rect_list_class clip;
  i4_rect_list_class *single_dirty; // all areas that only need updating for the next frame
  i4_rect_list_class *both_dirty;   // all areas that need updating on all future frames
  sw16 xoff,yoff;

  i4_draw_context_class(sw16 x1, sw16 y1, sw16 x2, sw16 y2)
  {
    clip.add_area(x1,y1,x2,y2);
    single_dirty=0;
    both_dirty=0;
    xoff=0;
    yoff=0;
  }
  ~i4_draw_context_class()
  {
    if (single_dirty) 
      delete single_dirty;
    if (both_dirty)
      delete both_dirty;
  }

  void add_single_dirty(sw16 x1, sw16 y1, sw16 x2, sw16 y2)
  {
    if (single_dirty)
      single_dirty->add_area(x1,y1,x2,y2);
  }

  void add_both_dirty(sw16 x1, sw16 y1, sw16 x2, sw16 y2)
  {
    if (both_dirty)
      both_dirty->add_area(x1,y1,x2,y2);
  }

} ;


#endif
