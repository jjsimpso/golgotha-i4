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
 

#ifndef IMAGE_WIN_HH
#define IMAGE_WIN_HH

#include "window/window.hh"
#include "window/win_evt.hh"

class i4_image_class;

class i4_image_window_class : public i4_parent_window_class
{
  i4_image_class *im, *darken_im;
  i4_bool del, darken, active;

  void reparent(i4_image_class *draw_area, i4_parent_window_class *parent);
public:
  // if delete on destructor is true then change_image will delete the old image
  void change_image(i4_image_class *im);  

  i4_image_window_class(i4_image_class *im,
                        i4_bool delete_on_destructor=i4_F,
                        i4_bool dark_when_not_active=i4_T);

  virtual void parent_draw(i4_draw_context_class &context);
  void receive_event(i4_event *ev);
  ~i4_image_window_class();
  char *name() { return "image_window"; }
} ;

#endif
