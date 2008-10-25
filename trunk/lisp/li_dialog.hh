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
 

#ifndef LI_DIALOG_HH
#define LI_DIALOG_HH


#include "window/colorwin.hh"
#include "lisp/lisp.hh"
#include "lisp/li_optr.hh"

class li_object;


class li_type_edit_class
{
public:
  // windows is a buffer of window *, maximum windows allowed is passed through max_windows
  // and total # created is returned.
  // o is the object being edited.  Property list is a generic 'looks' control parameter
  virtual int create_edit_controls(const i4_const_str &name,
                                   li_object *object, 
                                   li_object *property_list,
                                   i4_window_class **windows, 
                                   int max_windows,
                                   li_environment *env) = 0;

  // returns true if user input is ok and 'apply' can be done : windows is the created
  // window list from create_edit_controls
  virtual i4_bool can_apply_edit_controls(li_object *objectw, 
                                          li_object *property_list,
                                          i4_window_class **windows,
                                          li_environment *env) { return i4_T; }

  // returns a new instance of o (does not change o directly)
  virtual li_object *apply_edit_controls(li_object *o, 
                                         li_object *property_list,
                                         i4_window_class **windows,
                                         li_environment *env) = 0;

};


class li_dialog_item : public i4_color_window_class
{
protected:
  li_object_pointer o;
  li_object *prop_list;

public:
  i4_window_class **windows;
  int t_windows;

  li_dialog_item();
  li_dialog_item(const i4_const_str &name,
                 li_object *o, 
                 li_object *prop_list,
                 li_environment *env);

  virtual i4_bool can_apply(li_environment *env);
  virtual li_object *apply(li_environment *env);
  virtual ~li_dialog_item();
  char *name() { return "li_dialog_item"; }
};


class li_dialog_window_class : public i4_color_window_class
{
  i4_window_class *w[10];  
  li_object_pointer o, prop_list, new_value, enviroment;
  li_function_type called_on_close;
  li_environment *env() { return (li_environment *)enviroment.get(); }

public:
  i4_parent_window_class *mp_handle;

  i4_graphical_style_class *style();
  li_dialog_window_class(const i4_const_str &name,
                         li_object *o, 
                         li_object *prop_list,
                         li_function_type called_on_close,
                         li_environment *env);


  ~li_dialog_window_class();

  void receive_event(i4_event *ev);
  char *name() { return "li_dialog_window"; }
};


// function_called_on_delete (if supplied) gets 2 arguments, 1st is the new value, 
// 2nd is the old value
li_dialog_window_class *li_create_dialog(const i4_const_str &name,
                                         li_object *o, 
                                         li_object *prop_list=0,
                                         char *function_called_on_close=0,
                                         li_environment *env=0);  // for getting function

li_dialog_window_class *li_create_dialog(const i4_const_str &name,
                                         li_object *o, 
                                         li_object *prop_list=0,
                                         li_function_type function_called_on_close=0,
                                         li_environment *env=0);


#endif
