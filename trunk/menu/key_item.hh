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
 

#ifndef I4_KEY_ITEM_HH
#define I4_KEY_ITEM_HH


#include "menu/menu.hh"
#include "font/font.hh"
#include "window/style.hh"
#include "device/keys.hh"

class i4_key_item_class : public i4_menu_item_class
{
  protected :

  i4_color_hint_class *color;
  i4_font_hint_class *font;

  i4_str *text;
  w16 pad_lr, pad_ud;
  w16 use_key, key_modifiers;
  i4_bool key_focused, valid;

  public :
  i4_bool has_keyboard_focus() { return key_focused; }

  i4_key_item_class(
               const i4_const_str &_text,
               i4_color_hint_class *color_hint,
               i4_font_hint_class *font_hint,
               i4_graphical_style_class *style,
               w16 key=I4_NO_KEY,
               w16 key_modifiers=0,
               w16 pad_left_right=0,
               w16 pad_up_down=0
               );


  ~i4_key_item_class();

  char *name() { return "key_item"; }

  virtual void parent_draw(i4_draw_context_class &context);
  virtual void receive_event(i4_event *ev);

  // called when selected or key is pressed
  virtual void action() = 0;

  // if usage is disallowed then the item will be grayed out on the menu
  void allow_use()    { valid=i4_T; }
  void disallow_use() { valid=i4_F; } 
  virtual void do_press()
  {
    if (!valid) return;
    else i4_menu_item_class::do_press();
  }

  i4_menu_item_class *copy()
  {
    return 0;      // don't use this key_item anymore..
  }

} ;

class i4_key_accel_watcher_class : public i4_event_handler_class
{
  struct key_item_pointer_type
  {    
    i4_key_item_class *modkey[8];
    i4_key_item_class **get_from_modifiers(w16 modifiers);
  } 
  user[I4_NUM_KEYS];
  

  w32 total;
  i4_bool initialized;
public:
  i4_key_accel_watcher_class();
  void watch_key(i4_key_item_class *who, w16 key, w16 modifiers);
  void unwatch_key(i4_key_item_class *who, w16 key, w16 modifiers);
  void receive_event(i4_event *ev);
  
  char *name() { return "key accel watcher"; }
};



#endif



