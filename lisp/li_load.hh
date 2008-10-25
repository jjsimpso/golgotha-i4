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
 

#ifndef LI_LOAD_HH
#define LI_LOAD_HH


#include "lisp/li_types.hh"

class i4_loader_class;
class i4_saver_class;

// returns a remap array for li_ type numbers from old to new
// these should be freed by li_free_type_info
li_type_number *li_load_type_info(i4_loader_class *fp, li_environment *env);
void li_free_type_info(li_type_number *remap);

// this saves the names of the types so the can be found and
// a remap can be created on load-up
void li_save_type_info(i4_saver_class *fp, li_environment *env);


// loads some object from disk : if the object type no longer exist
// it is skiped over and 0 is returned
li_object *li_load_object(i4_loader_class *fp, li_type_number *type_remap, li_environment *env);

// saves an object to disk
void li_save_object(i4_saver_class *fp, li_object *o, li_environment *env);

// if you need to save a li_type_number to disk
void li_save_type(i4_file_class *fp, li_type_number type);

// loads a li_type_number from disk
li_type_number  li_load_type(i4_file_class *fp, li_type_number *type_remap);


// loads an object from disk.  If the type is not the type requested, it is discarded
// and li_new is called to create a new instance of this type
li_object *li_load_typed_object(char *type_name, i4_loader_class *fp, 
                                li_type_number *type_remap,
                                li_environment *env);

li_object *li_load_typed_object(int type, i4_loader_class *fp, li_type_number *type_remap,
                                li_environment *env);

#endif
