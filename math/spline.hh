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
 

#ifndef I4_BSPLINE_HH
#define I4_BSPLINE_HH

#include "arch.hh"
#include "math/num_type.hh"

class i4_file_class;
class i4_linear_allocator;

class i4_spline_class
{
  w32 t_points;


  static i4_linear_allocator *p_alloc;
  static w32 point_refs;

  void cleanup();

public:
  class point
  {
  public:
    i4_float x,y,z;
    w32 frame;         // frame in time this point exsist, golgotha runs at 15hz

    i4_bool selected;
    point *next;
  };

protected:
  point *points;
public:
  void move(i4_float x_add, i4_float y_add, i4_float z_add);

  point *begin() { return points; }
  i4_spline_class *next;

  w32 total() { return t_points; }

  point *add_control_point(i4_float x, i4_float y, i4_float z, w32 frame);
  point *get_control_point(w32 p);

  point *get_control_point_previous_to_frame(w32 frame);

  i4_bool get_point(w32 frame, i4_float &x, i4_float &y, i4_float &z);

  // inserts a new control point after ever selected node
  void insert_control_points();

  void delete_selected();
  w32 last_frame();
  i4_spline_class();
  ~i4_spline_class();

  void save(i4_file_class *fp);
  void load(i4_file_class *fp);
};


#endif
