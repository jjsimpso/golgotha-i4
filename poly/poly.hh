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
 

#ifndef I4_POLY_HH
#define I4_POLY_HH


#include "error/error.hh"
#include "math/point.hh"

//------------------------------------------------------------------------
// i4_Vertex_Class
//------------------------------------------------------------------------
struct i4_vertex_class
{
  w32 outcode;
  i4_3d_point_class v;                         // unprojected x,y,z
  i4_float s, t;                               // texture coordinates 0..1
  i4_float px, py;                             // projected x,y
  i4_float w;                                  // 1/v.z
  i4_float r,g,b;                              // lighting intensity 0..1
  i4_float a;                                  // alpha 0..1

  //-----------------------------------
  // project to screen space
  //-----------------------------------
  // w is 1/z, cx and cy are center of window
  void project(i4_float w, i4_float center_x, i4_float center_y)
  {
    px=v.x*w + center_x;
    py=v.y*w + center_y;
  }
};


//---------------------------------------------------------------
// i4_Polygon_Class
//---------------------------------------------------------------
class i4_polygon_class
{
public:
  enum { V_BUF_SIZE=8 };        //wha? max of 8 verts, this must not 
                                //be used for clipped verts also

  int t_verts;					 // number of poly vertices
  i4_vertex_class vert[V_BUF_SIZE];              // vertex buffer

  i4_polygon_class() { t_verts=0; }

  //add vert by individual elements
  i4_vertex_class *add_vert(i4_3d_point_class v,
                            i4_float s, i4_float t,
                            i4_float r, i4_float g, i4_float b)
  {
    I4_ASSERT(t_verts<V_BUF_SIZE, "vert buffer full");

    vert[t_verts].v=v; //xyz
    vert[t_verts].s=s; //textel U
    vert[t_verts].t=t; //textel V
    vert[t_verts].r=r; //red
    vert[t_verts].g=g; //green
    vert[t_verts].b=b; //blue
    t_verts++;
    return vert+t_verts-1;
  }
  
  //add vert by pointer
  i4_vertex_class *add_vert(i4_vertex_class *src_vert)
  {
    I4_ASSERT(t_verts<V_BUF_SIZE, "vert buffer full");

    vert[t_verts] = *src_vert;
    t_verts++;
    return vert+t_verts-1;    
  }
};


#endif
