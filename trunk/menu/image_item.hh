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

class i4_str;
class i4_image_class;

class i4_image_item_class : public i4_menu_item_class
{
  i4_image_class *im, *act;
  i4_bool del_im;
  i4_bool del_act;

public:  
  i4_image_item_class(const i4_const_str *context_help,
                      i4_image_class *normal_image,                      
                      i4_graphical_style_class *style,
                      i4_image_class *active_image=0,     // if 0, then image will brighten
                      i4_bool delete_images_on_death=i4_T,
                      i4_event_reaction_class *press=0,
                      i4_event_reaction_class *depress=0,
                      i4_event_reaction_class *activate=0,
                      i4_event_reaction_class *deactivate=0);

  ~i4_image_item_class();
  virtual void parent_draw(i4_draw_context_class &context);
  virtual void receive_event(i4_event *ev);

  virtual i4_menu_item_class *copy();
  char *name() { return "image_item"; }
};
