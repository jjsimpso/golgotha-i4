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
 

#ifndef I4_KEY_MAN_HH
#define I4_KEY_MAN_HH



#include "device/device.hh"
#include "device/keys.hh"
#include "memory/array.hh"
#include "memory/binary_tree.hh"
#include "time/time.hh"

class i4_key_man_class : public i4_device_class
{
  int context_id;

  struct context
  {
    char *name;
    w16 modifiers_taken;  // in this context these modifiers cannot be used as combo-keys
    w16 modifiers_used;
    context() { modifiers_used=modifiers_taken=0; }
  };

  i4_array<context> *context_list;     // list of context's we've seen so far
  i4_array<char *> *command_list;
  i4_grow_heap_class *char_heap;
  struct key_item
  {
    w16 context_mask;
    w16 command_id;

    w8 command_active;;
    w8 modifier_flags;

    i4_key key;

    key_item *next;   
    key_item *next_active;

    key_item(w16 context_mask, w16 command_id, w8 modifier_flags, i4_key key, key_item *next)
      : context_mask(context_mask), command_id(command_id), 
        modifier_flags(modifier_flags), key(key), next(next)
    {
      command_active=0;
    }
  };
  
  key_item *keys[I4_NUM_KEYS];
  key_item *active_list;

  void add_active(i4_key_man_class::key_item *i, i4_time_class &time);
  void get_modifiers(int k_mod);
  void end_actives(int matches_key, i4_time_class &time);

  void receive_event(i4_event *ev);
  i4_bool process_events() { return i4_F; }
  void check_init();
  char *alloc_str(char *s);
  int use_modifiers_for_contexts(int context_mask, int mod, char *key_name);
  int acquire_modifiers_for_contexts(int context_mask, int mod, char *key_name);
  w16 key_modifiers_pressed;
  i4_bool loaded;

public:
  i4_bool control_pressed() { return (key_modifiers_pressed & I4_MODIFIER_CTRL) ? i4_T : i4_F; }
  i4_bool alt_pressed() { return (key_modifiers_pressed & I4_MODIFIER_ALT) ? i4_T : i4_F; }
  i4_bool shift_pressed() { return (key_modifiers_pressed & I4_MODIFIER_SHIFT) ? i4_T : i4_F; }


  i4_key_man_class();

  char *name() { return "key manager"; }
  i4_bool load(const i4_const_str &filename);
  void uninit();

  int get_context_id(char *context);
  int get_command_id(char *command);

  void set_context(int _context_id) { context_id=_context_id; }
  void set_context(char *context) {   set_context(get_context_id(context)); }

  int current_context() { return context_id; }
  char *context_name(int context) { return (*context_list)[context].name; }

  i4_bool get_key_for_command(int command_id, i4_key &key, w16 &mod);
  i4_bool get_key_for_command(char *command_name, i4_key &key, w16 &mod)
  { return get_key_for_command(get_command_id(command_name), key, mod); }
};



class i4_key_matchup_class
{
  struct command_matchup
  {
    command_matchup *left, *right;
    w16 command_id;
    int remap_id;

    command_matchup() {}
    command_matchup(w16 command_id, int remap) : command_id(command_id), remap_id(remap) {}

    int compare(const command_matchup *b) const
    {
      if (command_id>b->command_id)
        return 1;
      else if (command_id<b->command_id)
        return -1;
      else return 0;
    }

  };

  i4_binary_tree<command_matchup> matchup;  

public:
  void add(char *command, int remap);
  int remap(int command_id);

  ~i4_key_matchup_class() { matchup.delete_tree(); }
};

extern i4_key_man_class i4_key_man;


#endif
