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
 

#include "device/device.hh"
#include "device/event.hh"
#include "error/error.hh"
#include "device/kernel.hh"
#include "init/init.hh"

#include <stdlib.h>

i4_device_class::i4_device_class()
{
  next=NULL;
}

void i4_device_class::send_event_to_agents(i4_event *ev, device_flags receive_types)
{
  i4_kernel.broadcast_event_type(ev, receive_types);
}

i4_event_handler_class::~i4_event_handler_class()
{
  I4_ASSERT(!thinking(), "i4_event_handler::thinking on destructor");

#ifndef I4_RETAIL
  if (!i4_is_initialized() && first)
  {
    i4_error("event_handler has references at end of program");
  }
#endif


  // clear out all the references to ourself 
  while (first)
  {
    first->ref=0;
    first=first->next;
  }
}


i4_event_reaction_class *i4_event_reaction_class::copy()
{
  i4_event *ev=event ? event->copy() : 0;

  return new i4_event_reaction_class(handler_reference.get(), ev);
}

i4_event_reaction_class::~i4_event_reaction_class()
{
  I4_ASSERT(i4_is_initialized() || handler_reference.get()==0, 
            "event reaction is global and has a reference at end of program");


  handler_reference.reference(0);

  I4_ASSERT(i4_is_initialized() || event==0,
            "event reaction is global and has an event at end of program");

  if (event)
    delete event;
}

i4_event_reaction_class::i4_event_reaction_class(i4_event_handler_class *hand,
                                                 i4_event               *event)
  : event(event)
{
  
  handler_reference.reference(hand);
}

i4_event_reaction_class::i4_event_reaction_class(i4_event_handler_class *hand, 
                                                 w32 user_message_id)
{
  event=new i4_user_message_event_class(user_message_id);  
  handler_reference.reference(hand);
}


void i4_event_handler_private_reference_class::destroy_ref()
{
  // see if we need to remove our reference from the object we were referencing
  if (ref)
  {
    i4_event_handler_private_reference_class *p, *last=0;
    p=ref->first;
    while (p && p!=this)
    {
      last=p;
      p=p->next;
    }

    I4_ASSERT(p, "destroy_ref : couldn't find reference");
    
    if (last)
      last->next=next;
    else
      ref->first=next;

    ref=0;
  }
}

// if who is 0, then reference is destroyed
void i4_event_handler_private_reference_class::reference(i4_event_handler_class *who)
{
  destroy_ref();
  if (who)
  {
    ref=who;
    next=who->first;
    who->first=this;
  }
}
