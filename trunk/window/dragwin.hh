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
 

#ifndef __DRAGWIN_HPP_
#define __DRAGWIN_HPP_

#include "window/window.hh"

class i4_drag_frame_class;

class i4_draggable_window_class : public i4_parent_window_class
{
  i4_coord last_mouse_x,
           last_mouse_y,
           current_mouse_x,
           current_mouse_y;

  i4_drag_frame_class *drag_frame;
  public :
  virtual void receive_event(i4_event *ev);
  i4_draggable_window_class(w16 w, w16 h);
  char *name() { return "drag_frame"; }
} ;



#endif
