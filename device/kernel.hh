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
 

#ifndef __KERNEL_HPP_
#define __KERNEL_HPP_

#include "arch.hh"

class i4_event_handler_class;
class i4_device_class;
class i4_event_reaction_class;
class i4_event;

/*
  The kernel is used to send all events to i4_event_handlers.  Currently whenever it gets an
  event it calls it virtual when() function and determines if the event should be que up and
  sent later (if when returns LATER) or sent immediatly (if when() return NOW or ANYTIME).

  example ussage :
  
  kernel.send_event(send_to,&ev);

 */


class i4_kernel_device_class
{
  enum {     
    TYPE_MOUSE_MOVE, 
    TYPE_MOUSE_BUTTON_DOWN, 
    TYPE_MOUSE_BUTTON_UP,
    TYPE_KEY_PRESS, 
    TYPE_KEY_RELEASE,
    TYPE_DISPLAY_CHANGE,   // when display screen changes (size, location, etc).
    TYPE_DISPLAY_CLOSE,
    TYPE_SYSTEM_SIGNAL,
    TYPE_IDLE,
    TYPE_DO_COMMAND,
    TYPE_END_COMMAND,
    TYPE_DRAG_DROP_EVENT,
    LAST_TYPE
  };

#ifndef I4_RETAIL
  void show_pending();
#endif
  protected :


  struct response_type
  {
    i4_event_handler_class *who;
    response_type *next;
    response_type(i4_event_handler_class *who, response_type *next) : who(who), next(next) {}
  } *response[LAST_TYPE];

  i4_device_class *device_list;

  i4_bool can_send_idle;
  w32 milliseconds_before_idle_events_sent;
  void check_for_idle();

  public :

  int events_sent;    // app uses this. if no events are sent and app is idle, then app sleeps

  void set_milliseconds_before_idle_events_sent(w32 milli_seconds);

  virtual i4_bool process_events();              // returns true if an event was dispatched  

  void send_event(i4_event_handler_class *send_to, i4_event *ev);

  void send(i4_event_reaction_class *r);  // r includes event and who to send to

  // call this if you want to deque any pending events for yourself
  // this is called automatically by event_handler's desturctor ref_count!=0
  void deque_events(i4_event_handler_class *for_who);

  // this used used mainly by the 3ds tool because the process_events()
  // never gets a chance to be called
  i4_bool flush_events();


  // call this when you want the kernel to think the use is not idle even though no user
  // events are coming in (so it won't send out IDLE events for idle_time)
  void not_idle(); 

  // this will add you to a list to receive events of this type
  virtual void request_events(i4_event_handler_class *for_who, w32 event_types);  

  // you will no longer receive events you requested previously
  virtual void unrequest_events(i4_event_handler_class *for_who, w32 event_types);

  void add_device(i4_device_class *device);       // returns 16 bits device id
  void remove_device(i4_device_class *device);
  i4_kernel_device_class();

  void broadcast_event_type(i4_event *ev, w32 event_type);
  void delete_handler(i4_event_handler_class *handler);
} ;

extern i4_kernel_device_class i4_kernel;

#endif
