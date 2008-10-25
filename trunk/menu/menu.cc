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
 

#include "menu/menu.hh"
#include "device/event.hh"
#include "window/win_evt.hh"

class i4_depress_menu_item : public i4_object_message_event_class
{
  public :

  i4_menu_item_class *item;
  
  i4_depress_menu_item(i4_menu_class *menu, 
                       i4_menu_item_class *item)
    : i4_object_message_event_class(menu),item(item) {}


  virtual i4_event  *copy() 
  { 
    return new i4_depress_menu_item((i4_menu_class *)object,item); 
  }

} ;

void i4_menu_class::add_item(i4_menu_item_class *item)
{
  item->set_menu_parent(this);
  i4_parent_window_class::add_child(0,0,item);
}


void i4_menu_class::note_reaction_sent(i4_menu_item_class *who,       // this is who sent it
                                       i4_event_reaction_class *ev,   // who it was to 
                                       i4_menu_item_class::reaction_type type)
{
  // if the item was pressed, send a delayed event to ourself to depress it
  if (type==i4_menu_item_class::PRESSED)
  {
    i4_depress_menu_item dn(this,who);
    i4_kernel.send_event(this,&dn);
    
    if (hide_on_pick)
      hide();
  }
}

void i4_menu_class::receive_event(i4_event *ev)
{
  if (deleted)
    i4_warning("getting events after death, talk about wierd");

  if (ev->type()==i4_event::OBJECT_MESSAGE)
  {
    CAST_PTR(r,i4_depress_menu_item,ev);
    if (r->object==this)
      r->item->do_depress();
    else i4_parent_window_class::receive_event(ev);
  }
  else
  {
    if (ev->type()==i4_event::WINDOW_MESSAGE && focus_inform)
    {
      CAST_PTR(wev,i4_window_message_class,ev);
      if (wev->sub_type==i4_window_message_class::LOST_MOUSE_FOCUS)
      {
        CAST_PTR(lost, i4_window_lost_mouse_focus_class, ev);

        i4_menu_focus_event_class mlost(this, 
                                       i4_menu_focus_event_class::lost_focus,
                                       lost->lost_to);

        i4_kernel.send_event(focus_inform, &mlost );
      }
      else if (wev->sub_type==i4_window_message_class::GOT_MOUSE_FOCUS)
      {
        i4_menu_focus_event_class got(this, 
                                      i4_menu_focus_event_class::got_focus,
                                      0);

        i4_kernel.send_event(focus_inform, &got );
      }        
    }
    i4_parent_window_class::receive_event(ev);
  }
}

i4_menu_class::~i4_menu_class()
{
  deleted=i4_T;
}

