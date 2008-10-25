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
 

#include "menu/image_item.hh"
#include "image/image.hh"

i4_image_item_class::i4_image_item_class(const i4_const_str *context_help,
                                         i4_image_class *normal_image,
                                         i4_graphical_style_class *style,
                                         i4_image_class *active_image,     // if 0, then image will brighten
                                         i4_bool delete_images_on_death,
                                         i4_event_reaction_class *press,
                                         i4_event_reaction_class *depress,
                                         i4_event_reaction_class *activate,
                                         i4_event_reaction_class *deactivate)

  : i4_menu_item_class(context_help, style, normal_image->width(), 
                       normal_image->height(), press,depress,activate,deactivate)
{
  I4_ASSERT(normal_image, "no normal");

  im=normal_image;

  del_im=delete_images_on_death;

  if (active_image)
  {
    act=active_image;
    del_act=delete_images_on_death;
  }
  else
  {
    del_act=i4_T;



    int w=im->width(), h=im->height();
    act=i4_create_image(w,h, im->pal);


    for (int y=0; y<h; y++)
      for (int x=0; x<w; x++)
      {
        w32 c=im->get_pixel(x,y);
        int r=((c&0xff0000)>>16)<<1;  if (r>255) r=255;
        int g=((c&0xff00)>>8)<<1;    if (g>255) g=255;
        int b=((c&0xff)>>0)<<1;      if (b>255) b=255;
        
        act->put_pixel(x,y, (r<<16)|(g<<8)|b);
      }



  }
  
  
}


i4_image_item_class::~i4_image_item_class()
{
  if (del_im)
    delete im;
  
  if (del_act)
    delete act;
}

void i4_image_item_class::parent_draw(i4_draw_context_class &context)
{
  if (active)
    act->put_image(local_image,0,0,context);
  else 
    im->put_image(local_image,0,0,context);

}

void i4_image_item_class::receive_event(i4_event *ev)
{
  if (ev->type()==i4_event::MOUSE_BUTTON_DOWN)
  {
    CAST_PTR(b,i4_mouse_button_down_event_class,ev);
    if (b->but==i4_mouse_button_down_event_class::LEFT)
    {        
      do_press();
      send_event(send.press, PRESSED);

      do_depress();
      send_event(send.depress, DEPRESSED);

    } else i4_menu_item_class::receive_event(ev);
  }
  else i4_menu_item_class::receive_event(ev);
}


i4_menu_item_class *i4_image_item_class::copy()
{
  return new i4_image_item_class(context_help,
                                 im->copy(), 
                                 hint,
                                 act->copy(), 
                                 i4_T,
                                 send.press ? send.press->copy() : 0,
                                 send.depress ? send.depress->copy() : 0,
                                 send.activate ? send.activate->copy() : 0,
                                 send.deactivate ? send.deactivate->copy() : 0);
}
