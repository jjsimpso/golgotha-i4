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
 

#ifndef __TIMEDEV_HPP_
#define __TIMEDEV_HPP_




#include "device/device.hh"
#include "time/time.hh"
class i4_event_handler_class;
class i4_event;


class i4_time_device_class : public i4_device_class
{


public:
#ifdef _WINDOWS
  void callback(w32 id);
#endif

  
  class timed_event
  {
  public:
    i4_event_handler_class *send_to;
    i4_event *event;
    i4_time_class start_time;
    w32 milli_wait;
    w32 win32_timer_id;
    timed_event *next;
    timed_event(i4_event_handler_class *send_to, i4_event *event, w32 milli_wait);
    ~timed_event();
  } ;

 
  class id
  {
  public:
    timed_event *reference;
    id(timed_event *reference) : reference(reference) {}
    id() { reference=0; }
  } ;


  id request_event(i4_event_handler_class *send_to,   // who to send the event to
      i4_event *event,                                // what event to send
      w32 milli_wait);                   // how much time to wait until sending (in milli-seconds)

  i4_bool cancel_event(const id &handle);
   
  virtual i4_bool process_events();       // returns true if an event was dispatched
  virtual char *name() { return "Time Device"; }
  virtual device_flags reports_events() { return 0; }  // doesn't not report common events
} ;

extern i4_time_device_class i4_time_dev;


#endif
