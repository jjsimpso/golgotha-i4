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
 

#ifndef __FILE_OPEN_HH
#define __FILE_OPEN_HH

class i4_parent_window_class;
class i4_event_handler_class;
class i4_graphical_style_class;

#include "string/string.hh"
#include "device/event.hh"

class i4_file_open_message_class : public i4_user_message_event_class
{
public:
  i4_str *filename;

  i4_file_open_message_class(w32 id, i4_str *filename)
    : i4_user_message_event_class(id), filename(filename) {}

  virtual i4_event  *copy() { return new i4_file_open_message_class(sub_type, 
                                                                    new i4_str(*filename)); }  

};

void i4_create_file_open_dialog(i4_graphical_style_class *style,
                                const i4_const_str &title_name,
                                const i4_const_str &start_dir,
                                const i4_const_str &file_mask,
                                const i4_const_str &mask_name,
                                i4_event_handler_class *tell_who,
                                w32 ok_id, w32 cancel_id);


void i4_create_file_save_dialog(i4_graphical_style_class *style,
                                const i4_const_str &default_name,
                                const i4_const_str &title_name,
                                const i4_const_str &start_dir,
                                const i4_const_str &file_mask,
                                const i4_const_str &mask_name,
                                i4_event_handler_class *tell_who,
                                w32 ok_id, w32 cancel_id);


#endif
