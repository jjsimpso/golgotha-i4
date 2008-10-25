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
 

#ifndef DX_CURSOR_HH
#define DX_CURSOR_HH

#include "threads/threads.hh"
#include "palette/pal.hh"
#include "image/image.hh"


#include "window/cursor.hh"
#include <dinput.h>

class win32_input_class;

class dx_threaded_mouse_class
{
protected:

  LPDIRECTINPUT          direct_input_driver;
  LPDIRECTINPUTDEVICE    direct_input_mouse_device;
  HANDLE                 direct_input_mouse_event;
  HWND                   window_handle;
    
  i4_cursor_class     cursor;
  
  i4_bool             position_locked;
  
  i4_bool             active;

  i4_bool             visible;        // this is false until cursor is first displayed
  
  volatile i4_bool    stop;           // set by delete(), who waits for thread to stop  

  enum { thread_stack_size = 4000*1024 };
  
  void uninit_mouse();
  void init_mouse(HWND hwnd);
    
public:
  i4_critical_section_class draw_lock; 
  i4_critical_section_class acquire_lock;

  sw32 clip_x1, clip_y1, clip_x2, clip_y2;


  win32_input_class *input;

  sw32 current_mouse_x,
       current_mouse_y;  

  sw32 save_mouse_x,
       save_mouse_y;
  
  void lock_position(i4_bool yes_no)
  {
    if (yes_no)
      position_locked = i4_T;
    else
      position_locked = i4_F;
  }

  // private, don't call
  void thread();

  virtual void remove()  {}
  virtual void save()    {}
  virtual void display() {}
  virtual void set_cursor(i4_cursor_class *cursor) {};
  virtual void use_backbuffer(i4_bool use_bbuf) = 0;
  
  virtual void set_visible(i4_bool set)
  {    
    visible = set;    
  }


  dx_threaded_mouse_class(const i4_pal *screen_pal, 
                          HWND window_handle,
                          sw32 clip_x1, sw32 clip_y1,
                          sw32 clip_x2, sw32 clip_y2);

  virtual ~dx_threaded_mouse_class();

  // call when app loses focus
  void set_active(i4_bool act);
};



#endif
