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
 

#include "gui/smp_dial.hh"
#include "window/window.hh"
#include "device/event.hh"
#include "device/kernel.hh"
#include "window/win_evt.hh"
#include "image/image.hh"
#include "window/style.hh"
#include "gui/button.hh"
#include "gui/text.hh"

class i4_simple_dlg_class : public i4_parent_window_class
{
public:
  enum { YES, NO };

  char *name() { return "simple dlg"; }
  i4_event_handler_class *send_to;
  i4_event *yes_event, *no_event;
  i4_color bg_color;
  i4_graphical_style_class *style;
    
  i4_simple_dlg_class(w16 w, w16 h,
                      i4_graphical_style_class *style,
                      i4_event_handler_class *send_to,
                      i4_event *yes_event, i4_event *no_event)
    : i4_parent_window_class(w,h),
      send_to(send_to),
      yes_event(yes_event), no_event(no_event),
      bg_color(style->color_hint->window.passive.medium),
      style(style)
  {}

  void receive_event(i4_event *ev)
  {
    if (ev->type()==i4_event::USER_MESSAGE)
    {
      CAST_PTR(uev, i4_user_message_event_class, ev);
      if (uev->sub_type==YES)
      {
        i4_kernel.send_event(send_to, yes_event);        
        style->close_mp_window(parent);
      }
      else if (uev->sub_type==NO)
      {
        i4_kernel.send_event(send_to, no_event);
        style->close_mp_window(parent);
      }
    } else i4_parent_window_class::receive_event(ev);
  }

  void parent_draw(i4_draw_context_class &context)
  {
    local_image->clear(bg_color, context);
  }

};

static i4_button_class *i4_simple_create_button(const i4_const_str &name, 
                                                i4_event_handler_class *send_to,
                                                i4_event *ev,
                                                i4_graphical_style_class *style)
{
  i4_button_class *b=new i4_button_class(0,
                                         new i4_text_window_class(name, style),
                                         style,
                                         new i4_event_reaction_class(send_to, ev));
  b->set_popup(i4_T);
  return b;

}

i4_parent_window_class *i4_create_yes_no_dialog(i4_parent_window_class *parent,
                                                i4_graphical_style_class *style,
                                                const i4_const_str &title,
                                                const i4_const_str &message,
                                                const i4_const_str &yes, const i4_const_str &no,
                                                i4_event_handler_class *send_to,
                                                i4_event *yes_event, i4_event *no_event)
{
  i4_simple_dlg_class *sd=new i4_simple_dlg_class(0,0,
                                                  style,
                                                  send_to,
                                                  yes_event, no_event);


  i4_button_class *y=i4_simple_create_button(yes, sd, 
                                            new i4_user_message_event_class(0), style);
  i4_button_class *n=i4_simple_create_button(no, sd,
                                            new i4_user_message_event_class(1), style);
  i4_text_window_class *t=new i4_text_window_class(message, style);

  sw32 w=t->width(),h=t->height()+2+y->height();
  sw32 bw=y->width()+n->width();
  if (w<bw)
    w=bw;

  sd->resize(w,h);

  i4_parent_window_class *p; 
  p=style->create_mp_window(parent->width()/2-w/2, parent->height()/2-h/2, w,h, title);



  sd->add_child(p->width()/2-bw/2, 0, y);
  sd->add_child(p->width()/2-bw/2+y->width(), 0, n);
  sd->add_child(p->width()/2-t->width()/2, y->height()+1, t);

  p->add_child(0,0,sd);
  return p;
}




