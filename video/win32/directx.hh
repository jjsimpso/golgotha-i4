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
 

#ifndef __DIRECTX_HH
#define __DIRECTX_HH

#include "image/depth.hh"
#include "image/image16.hh"
#include "video/display.hh"
#include "video/win32/win32_input.hh"
#include <ddraw.h>

void dx_error(sw32 result);

//class directx_mouse_cursor_class;

class directx_display_class : public i4_display_class
{
protected:
  i4_image_class *mouse_pict;    

  I4_SCREEN_TYPE *mouse_save,
                 *screen;
  i4_coord           mouse_hot_x,mouse_hot_y;
  i4_pal_handle_class mouse_pal;
  i4_color           mouse_trans;



  I4_SCREEN_TYPE  *back_buffer;
  i4_bool          win_is_open, exclusive_mode, using_emulation;

  LPDIRECTDRAW        direct_draw_driver;           // DirectDraw object
  LPDIRECTDRAWSURFACE back_surface, primary_surface;


  //  directx_mouse_cursor_class *cursor;
  i4_draw_context_class   *context;

public:
  win32_input_class input;

  i4_bool saw_last, full_screen;

  void get_window_pos(sw32 &x, sw32 &y);

  // this is over-riding in the d3d_display so to search for hardware accelerators
  virtual i4_bool create_direct_draw();


  void destroy_direct_draw();

  directx_display_class();

  class directx_mode : public i4_display_class::mode
  {
    public :   
    directx_display_class *assoc;   // pointer to use, so we can confirm we created this mode

  } amode, cur_mode, *last_found;


  i4_bool create_back_surface(directx_mode *mode);

  virtual w16 width() const
  {
    return back_buffer->width();
  }

  virtual w16 height() const                              
  {
    return back_buffer->height();
  }

  virtual i4_bool remove_cursor() { return i4_T; }

  virtual i4_draw_context_class *get_context() { return context; }

  // called when windows gives us a WM_MOVE message, this tells everyone else interested
  virtual void move_screen(i4_coord x, i4_coord y);


  mode *current_mode() { return &cur_mode; }
  mode *get_first_mode();
  mode *get_next_mode(mode *last_mode);

  virtual i4_bool initialize_mode(mode *which_one);
  i4_bool open_window(directx_mode *mode);
  virtual i4_bool close();


  virtual void flush();
  virtual i4_image_class *get_screen();

  i4_bool set_mouse_shape(i4_cursor_class *cursor);
  virtual i4_bool realize_palette(i4_pal_handle_class pal_id)
  {
    return i4_T;   // pretend like this works for now
  }

  virtual i4_bool lock_mouse_in_place(i4_bool yes_no)
  {
    return input.lock_mouse_in_place(yes_no);
  }


  virtual i4_bool create_surfaces(directx_mode *mode);
  virtual void active(i4_bool act);  
  virtual w32 priority();

  virtual char *name() const { return "DirectX"; }
  virtual i4_bool available();
};


#endif
