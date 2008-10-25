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
#include "time/time.hh"
#include "time/timedev.hh"
#include "device/kernel.hh"
#include "init/init.hh"
#include "isllist.hh"
#include "time/time.hh"
#include "device/event.hh"

i4_time_device_class i4_time_dev;
extern int i4_show_events;

static i4_isl_list<i4_time_device_class::timed_event> events;

i4_time_device_class::timed_event::~timed_event()
{
  delete event;
}

i4_time_device_class::timed_event::timed_event(i4_event_handler_class *send_to,
                                               i4_event *event,
                                               w32 milli_wait)
  : send_to(send_to),
    event(event->copy()),
    milli_wait(milli_wait)
{
}

class i4_time_device_adder_class : public i4_init_class
{
  public :
  void init() 
  { 
    i4_kernel.add_device(&i4_time_dev);
  }
} i4_time_device_adder_instance;



i4_bool i4_time_device_class::cancel_event(const id &handle)
{
  i4_isl_list<timed_event>::iterator i=events.begin(),last=events.end();
  for (;i!=events.end();++i)
  {
    if (handle.reference==&*i)
    {
      if (last==events.end())
        events.erase();
      else
        events.erase_after(last);
      delete &*i;
      return i4_T;
    }
    last=i;
  }
  return i4_F;
}

i4_bool i4_time_device_class::process_events()       // returns true if an event was dispatched
{
  if (events.begin()==events.end()) 
    return i4_F;

  i4_time_class current;
  i4_bool ret=i4_F;

  i4_isl_list<timed_event>::iterator i=events.begin(),del=events.end(), last=events.end();

  for (;i!=events.end();)
  {
    if (current.milli_diff(i->start_time)>(sw32)(i->milli_wait))
    {
      if (last==events.end())
        events.erase();
      else
        events.erase_after(last);

#ifndef I4_RETAIL
      if (i4_show_events)
        i4_warning("sending : '%s' to '%s'",i->event->name(), i->send_to->name());
#endif
      del=i;
      ++i;

      del->send_to->receive_event(del->event);
      delete &*del;

      ret=i4_T;
    }
    else 
    {
      last=i;
      ++i;
    }

  }
  last=events.end();
  return ret;
}

i4_time_device_class::id 
i4_time_device_class::request_event(i4_event_handler_class *send_to, // who to send the event to
                                       i4_event *event,                 // what event to send
                                       w32 milli_wait) // how much time to wait (in milli-seconds)
{
  // first make sure this is not an event that needs to be sent right now
  // these events usually are two-way events that have return codes inside
  if (event->when()==i4_event::NOW)
    i4_error("Cannot send NOW events throught the time device!");

  timed_event *ev=new timed_event(send_to,event,milli_wait);
  events.insert_end(*ev);
  return id(ev);
}
