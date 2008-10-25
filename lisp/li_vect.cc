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
 

#include "lisp/li_vect.hh"
#include "lisp/lisp.hh"
#include "file/file.hh"
#include "loaders/dir_save.hh"
#include "loaders/dir_load.hh"
#include "lisp/li_init.hh"

li_type_number li_vect_type;
class li_vect_type_function_table : public li_type_function_table
{ 
public:
  // free data associated with an instance of this type
  virtual void free(li_object   *o)
  {
    delete li_vect::get(o,0)->v;
  }

  virtual int equal(li_object  *o1, li_object *o2) 
  { 
    i4_3d_vector v1=li_vect::get(o1,0)->value(), v2=li_vect::get(o2,0)->value();
    return v1.x==v2.x && v1.y==v2.y && v1.z==v1.z;
  }

  virtual void print(li_object  *o, i4_file_class *stream)
  {
    i4_3d_vector v=li_vect::get(o,0)->value();
    stream->printf("(vector %f %f %f)",v.x, v.y, v.z);
  }

  virtual char *name() { return "vector"; }

  virtual li_object *create(li_object *params, li_environment *env)
  {
    i4_3d_vector v;
    if (params)
    {
      v.x=li_get_float(li_eval(li_car(params,env), env),env); params=li_cdr(params,env);
      v.y=li_get_float(li_eval(li_car(params,env), env),env); params=li_cdr(params,env);
      v.z=li_get_float(li_eval(li_car(params,env), env),env); params=li_cdr(params,env);
    }
      
    return new li_vect(v);
  }


  virtual void save_object(i4_saver_class *fp, li_object *o, li_environment *env)
  {
    i4_3d_vector v=li_vect::get(o,env)->value();
    fp->write_float(v.x);
    fp->write_float(v.y);
    fp->write_float(v.z);

  }

  virtual li_object *load_object(i4_loader_class *fp, li_type_number *type_remap,
                                 li_environment *env)
  {
    i4_3d_vector v;
    v.x=fp->read_float();
    v.y=fp->read_float();
    v.z=fp->read_float();
    return new li_vect(v);
  }
};

li_automatic_add_type(li_vect_type_function_table, li_vect_type);
