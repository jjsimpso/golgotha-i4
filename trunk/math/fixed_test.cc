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
 

#ifdef _MANGLE_INC
#include "FIXED~HA.HH"
#else
#include "fixed_point.hh"
#endif
#include <stdio.h>

i4_fixed_point<16> a,b;
i4_fixed_point<7> c,d,e,f,g,h;

main()
{
  a = 1.05;
  b = 5;
  i4_fixed_point_convert(c,a+b);
  d = 4;
  e = 0.3;
  f = e+0.6;
  f -= 0.3;
  g = d*e/f;
  printf("%f + %f = %f\n",double(a),double(b),double(c));
  printf("%f * %f / %f = %f\n",double(d),double(e),double(f),double(g));

  printf("%f / %f = %f\n",double(a), double(b), double(a.divide(b,3)));
}
