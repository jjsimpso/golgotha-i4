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
 

#ifndef I4_SLIDER_HH
#define I4_SLIDER_HH

#include "time/timedev.hh"

class i4_graphical_style_class;
class i4_event_handler_class;

#include "device/event.hh"
#include "window/window.hh"

class i4_slider_event : public i4_object_message_event_class
{
public:
  w32 x, divisor;
  i4_slider_event(void *object, w32 x, w32 divisor)
    : i4_object_message_event_class(object), x(x), divisor(divisor)  {}
  i4_event *copy() { return new i4_slider_event(object,x,divisor); }
  char *name() { return "slide event"; }
};

class i4_slider_class : public i4_window_class
{
  i4_graphical_style_class *style;
  sw32 off, lx,ly;
  i4_bool grab, active, need_cancel;
  sw32 bw, milli_delay;                  // button width

  
  i4_time_device_class::id t_event;
  i4_event_handler_class *notify;

  void set_off_from_mouse();
  void send_change();

public:
  void set_notify(i4_event_handler_class *n) { notify=n; }

  i4_slider_class(sw32 width, 
                  sw32 initial_start,
                  i4_event_handler_class *notify,
                  w32 milli_delay,
                  i4_graphical_style_class *style);
  ~i4_slider_class();

  void draw(i4_draw_context_class &context);
  void receive_event(i4_event *ev);
  char *name() { return "slider"; }
};


#endif
