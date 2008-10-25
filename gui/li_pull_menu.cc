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
 

#include "menu/pull.hh"
#include "menu/key_item.hh"
#include "lisp/lisp.hh"
#include "app/app.hh"
#include "menu/textitem.hh"
#include "gui/seperate.hh"
#include "device/key_man.hh"
#include "window/wmanager.hh"

i4_event_handler_reference_class<i4_pull_menu_class> li_pull;

static li_object *li_add_sub(li_object *o, li_environment *env)
{
  i4_graphical_style_class *style=i4_current_app->get_style();

  i4_menu_item_class *top_name;
  top_name=new i4_text_item_class(li_string::get(li_eval(li_car(o,env),env),env)->value(),
                                  style,
                                  &li_pull->menu_colors,                                   
                                  0,0,0,0,0,  5,3);

  i4_menu_class *sub=style->create_menu(i4_T);

  for (o=li_cdr(o,env); o; o=li_cdr(o,env))
  {
    if (li_car(o,env)->type()!=LI_LIST)
    {
      sub->add_item(new i4_seperator_line_class(style,
                                                li_pull->menu_colors.text_background,
                                                3,4));
    }
    else
    {
      li_object *s=li_car(o,env);
      char *view_name=li_string::get(li_eval(li_car(s,env),env),env)->value(); s=li_cdr(s,env);
      char *com_name=li_string::get(li_eval(li_car(s,env),env),env)->value();


      
      int command_id=i4_key_man.get_command_id(com_name);

      i4_do_command_event_class *do_cmd=new i4_do_command_event_class(com_name, command_id);
      i4_event_reaction_class *command=new i4_event_reaction_class(i4_current_app, do_cmd);

      i4_end_command_event_class *end_cmd=new i4_end_command_event_class(com_name, command_id);
      i4_event_reaction_class *end_command=new i4_event_reaction_class(i4_current_app, end_cmd);


      i4_text_item_class *ki=new i4_text_item_class(view_name, 
                                                    style,
                                                   &li_pull->menu_colors, 
                                                    0,
                                                   command, end_command,
                                                   0,0,
                                                   10,3);
      sub->add_item(ki);
    }
  }


  li_pull->add_sub_menu(top_name, sub);
  return 0;
}


i4_pull_menu_class *li_create_pull_menu(char *filename)
{
  if (li_pull.get())
    i4_error("pull menu already created");

  i4_graphical_style_class *style=i4_current_app->get_style();
  li_pull=new i4_pull_menu_class(style, i4_current_app->get_window_manager());

  li_environment *env=new li_environment(0, i4_T);
  li_add_function("add_sub_menu", li_add_sub, env);
  li_load(filename, env);

  return li_pull.get();
}
