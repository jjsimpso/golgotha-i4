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
 

#ifndef __VECTOR_TEMPLATE_HPP_
#define __VECTOR_TEMPLATE_HPP_

#include "math/num_type.hh"
#include <math.h>

template <int dimension, class T>
class i4_vector_template
{
public:
  T elt[dimension];

  i4_vector_class() {}

  i4_vector_class(const T v)  
  {
    for (int i=0; i<dimension; i++)
      elt[i] = v;
  }

  i4_vector_class(const i4_vector_class &b)
  {
    memcpy(elt,b.elt,sizeof(*this));
  }

  i4_vector_class& operator=(const i4_vector_class &b)
  {
    for (int i=0; i<dimension; i++)
      elt[i] = b.elt[i];

    return *this;
  }

  i4_vector_class& operator+=(const i4_vector_class &b)
  {
    for (int i=0; i<dimension; i++)
      elt[i] += b.elt[i];

    return *this;
  }


  i4_vector_class& operator-=(const i4_vector_class &b)
  {
    for (int i=0; i<dimension; i++)
      elt[i] -= b.elt[i];

    return *this;
  }


  i4_vector_class& operator*=(const T b)
  {
    for (int i=0; i<dimension; i++)
      elt[i] *= b;

    return *this;
  }


  i4_vector_class& operator/=(const T b)
  {
    for (int i=0; i<dimension; i++)
      elt[i] /= b;

    return *this;
  }


  T dot(const i4_vector_class b) const
  {
    T ret = 0;

    for (int i=0; i<dimension; i++)
      ret += elt[i]*b.elt[i];

    return ret;
  }


  T length() const
  {
    return (sqrt(dot(*this)));
  }


  i4_vector_class& normalize()
  {
    T len = length();

    for (int i=0; i<dimension; i++)
      elt[i] /= len;

    return *this;
  }

};

template <class T>
class i4_vector3_class : public i4_vector_class<3,T>
{
  enum { x,y,z };
public:
  i4_vector3_class() {};
  i4_vector3_class(i4_float _x, i4_float _y, i4_float _z) 
  {
    elt[x]=_x;
    elt[y]=_y;
    elt[z]=_z;
  }

  const i4_vector3_class& cross(i4_vector3_class b)
  {
    i4_vector3_class temp(*this);

    elt[x] = temp.elt[y]*b.elt[z] - temp.elt[z]*b.elt[y];
    elt[y] = temp.elt[z]*b.elt[x] - temp.elt[x]*b.elt[z];
    elt[z] = temp.elt[x]*b.elt[y] - temp.elt[y]*b.elt[x];

    return *this;
  }

  void set(i4_float _x, i4_float _y, i4_float _z)
  {
    elt[x]=_x;
    elt[y]=_y;
    elt[z]=_z;
  }
};



typedef i4_vector3_class<i4_float>  i4_3d_vector;
typedef i4_vector_class<4,i4_float> i4_4d_vector;


#endif
