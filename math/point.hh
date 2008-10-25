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
 

#ifndef __POINT_HH_
#define __POINT_HH_

#include "arch.hh"
#include "math/vector.hh"

class i4_3d_point_class : public i4_3d_vector
{
public:
  i4_3d_point_class() {}
  i4_3d_point_class(const i4_3d_vector &p) : i4_3d_vector(p) {}
  i4_3d_point_class(i4_float _x, i4_float _y, i4_float _z) : i4_3d_vector(_x, _y, _z) {}

  i4_3d_point_class& operator=(const i4_3d_vector &p) { set(p.x,p.y,p.z); return *this; }

  i4_bool almost_equal(i4_3d_point_class &a, i4_float error=0.001)
  {
    return (i4_bool)
      ((i4_fabs(x - a.x)<error) &&
          (i4_fabs(y - a.y)<error) &&
          (i4_fabs(z - a.z)<error));
  }

  i4_float distance(const i4_3d_point_class &other)
  { return sqrt( (x-other.x)*(x-other.x) + (y-other.y)*(y-other.y) + (y-other.y)*(y-other.y)); }
};

#endif

