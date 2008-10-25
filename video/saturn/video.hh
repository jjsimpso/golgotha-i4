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
 

#ifndef __SATURN_VIDEO_HH
#define __SATURN_VIDEO_HH

#include "image/depth.hh"
#include "image/image8.hh"
#include "image/image15.hh"
#include "video/display.hh"

class i4_saturn_display_class : public i4_display_class
{  
private:
  // generic image which will take the type of the screen when we copy the save portion
  i4_image_class *mouse_pict;    

  I4_SCREEN_TYPE *mouse_save,
                 *screen;

  i4_coord mouse_x,mouse_y;

protected:
  virtual w16 width() { return 320; }
  virtual w16 height() { return 240; }

  i4_draw_context_class *context;

  public :
  i4_coord                 mouse_hot_x,mouse_hot_y;
  i4_pal_handle_class      mouse_pal;
  i4_color                 mouse_trans;
 
  virtual i4_bool set_mouse_shape(i4_cursor_class *cursor) { ; }

  // devices local to this display (Keys & mice)
  virtual i4_device_class *local_devices() { return 0; }

  virtual i4_image_class *get_screen() { return 0; }

  // makes the physical display consistant with previous gfx calls
  // either through page flipping or copying dirty rects from an
  // off-screen buffer
  virtual void flush() { ; }

  // returns some descriptive name for this display
  virtual char *name() { return "Saturn display"; }

  virtual i4_draw_context_class *get_context() { return context; }

  virtual mode *get_first_mode() { return 0; }
  virtual mode *get_next_mode(mode *last_mode) { return 0; }


  // initialize_mode need not call close() to switch to another mode
  virtual i4_bool initialize_mode(mode *which_one) { return i4_F; }

  // should be called before a program quits
  virtual i4_bool close() { return i4_F; }
  virtual i4_bool available() { return i4_F; }

  // loads the palette into hardware registers, return i4_F if pal_id is wrong color depth for display
  virtual i4_bool realize_palette(i4_pal_handle_class pal_id) { return i4_F; }

  virtual i4_bool display_busy() { return i4_F; }

} ;

extern i4_saturn_display_class saturn_display_instance;

#endif




