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
 

#include "arch.hh"

class i4_window_class;
class i4_parent_window_class;
class i4_graphical_style_class;
class i4_event_reaction_class;

void i4_profile_watch(i4_graphical_style_class *style,
                      i4_parent_window_class *parent,                      
                      sw32 &win_x, sw32 &win_y,
                      w32 w, w32 h,
                      int open_type,  // 0==close, 1==open, 2==toggle window
                      i4_event_reaction_class *on_close=0);
