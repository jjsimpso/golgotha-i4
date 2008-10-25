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
 

#include "gui/slider.hh"
#include "window/style.hh"
#include "window/win_evt.hh"

i4_slider_class::i4_slider_class(sw32 width, 
                                 sw32 initial_start,
                                 i4_event_handler_class *notify,
                                 w32 milli_delay,
                                 i4_graphical_style_class *style)
  : i4_window_class(width,style->font_hint->normal_font->largest_height()+2),
    style(style),
    milli_delay(milli_delay),
    notify(notify)
{    
  off=initial_start;
  grab=i4_F;
  active=i4_F;
  w32 ol,oR,ot,ob;
  style->get_out_deco_size(ol,ot,oR,ob);
  bw=ol+oR+2;
  need_cancel=i4_F;
}

void i4_slider_class::draw(i4_draw_context_class &context)
{
  w32 il,ir,it,ib;
  w32 med=style->color_hint->window.passive.medium;
  local_image->clear(med, context);

  style->get_in_deco_size(il,it,ir,ib);
  style->draw_in_deco(local_image, 0,height()/2-it,width()-1,height()/2+ib, active, context);

  w32 ol,oR,ot,ob;
  style->get_out_deco_size(ol,ot,oR,ob);
  style->draw_out_deco(local_image, off,0,off+bw-1,height()-1, active, context);  
  local_image->bar(off+ol, ot, off+bw-oR, height()-ob, med, context);
}


void i4_slider_class::send_change()
{
  if (notify)
  {
    if (need_cancel)
    {
      i4_time_dev.cancel_event(t_event);
      need_cancel=i4_F;
    }

    i4_slider_event ev(this, off, width()-bw);

    if (milli_delay)
    {
      t_event=i4_time_dev.request_event(notify, &ev, milli_delay);
      need_cancel=i4_T;
    } else i4_kernel.send_event(notify, &ev);
  }
}


i4_slider_class::~i4_slider_class()
{
  if (need_cancel)
  {
    milli_delay=0;
    send_change();
  }
}


void i4_slider_class::set_off_from_mouse()
{
  w32 ol,oR,ot,ob;
  sw32 loff=off;

  style->get_out_deco_size(ol,ot,oR,ob);
  off=lx-bw/2;
  if (off<0) off=0;
  if (off+bw>=width())
    off=width()-bw;

  if (loff!=off)
  {
    send_change();
    request_redraw();
  }
}

void i4_slider_class::receive_event(i4_event *ev)
{
  switch (ev->type())
  {
    case i4_event::WINDOW_MESSAGE :
    {
      CAST_PTR(wev, i4_window_message_class, ev);
      if (wev->sub_type==i4_window_message_class::GOT_MOUSE_FOCUS)
      {
        active=i4_T;
        request_redraw();
      }
      else if (wev->sub_type==i4_window_message_class::LOST_MOUSE_FOCUS)
      {
        active=i4_F;
        request_redraw();
      }
    } break;

    case i4_event::MOUSE_MOVE :
    {
      CAST_PTR(mev, i4_mouse_move_event_class, ev);
      lx=mev->x;
      ly=mev->y;
        
      if (grab)
        set_off_from_mouse();                

    } break;

    case i4_event::MOUSE_BUTTON_DOWN :
    {
      CAST_PTR(bev, i4_mouse_button_down_event_class, ev);
      if (bev->left() && !grab)
      {
        grab=i4_T;
        i4_window_request_mouse_grab_class grab(this);
        i4_kernel.send_event(parent,&grab);
        set_off_from_mouse();
      }        

    } break;
    case i4_event::MOUSE_BUTTON_UP :
    {
      CAST_PTR(bev, i4_mouse_button_up_event_class, ev);
      if (grab && bev->left())
      {
        i4_window_request_mouse_ungrab_class ungrab(this);
        i4_kernel.send_event(parent,&ungrab);
        grab=i4_F;
      }
    } break;

  default:
    i4_warning("i4_slider_class::receive_event() - unhandled event type = %d",int(ev->type()));
    break;
   
  }
}
