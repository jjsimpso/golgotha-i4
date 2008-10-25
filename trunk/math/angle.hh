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
 

#ifndef I4_ANGLE_HH
#define I4_ANGLE_HH

#include "math/num_type.hh"
#include "math/pi.hh"

// returns the absolute difference between two angles
// this will always be between 0 and 180 degrees
inline i4_angle i4_angle_diff(i4_angle angle1, i4_angle angle2)
{
  i4_angle d;
  if (angle1>angle2)
    d=angle1-angle2;
  else
    d=angle2-angle1;
  if (d>i4_pi())
    return 2*i4_pi()-d;
  else
    return d;
}

// returns the clockwise distance from angle2 to angle1, this may be over 180 degrees
inline i4_angle i4_angle_minus(i4_angle angle1, i4_angle angle2)
{
  if (angle1>angle2)
    return angle1-angle2;
  else
    return angle1+2*i4_pi()-angle2;
}

inline i4_angle i4_interpolate_angle(i4_angle from, i4_angle to, i4_float fraction)
{
  i4_angle diff=i4_angle_diff(from, to) * fraction;
  if (i4_angle_minus(to, from)>=i4_pi())
    return from-diff;
  else
    return from+diff;
}

inline void i4_normalize_angle(i4_float &angle)
{
  while (angle<0) angle += (i4_2pi());
  while (angle>=i4_2pi()) angle -= (i4_2pi());
}

inline i4_float i4_rotate_to(i4_float &from, i4_float to, i4_float speed)
{
  i4_float dangle;

  dangle = (to-from);
  if (dangle>i4_pi())
    dangle -= 2*i4_pi();
  else if (dangle<-i4_pi())
    dangle += 2*i4_pi();

  if (dangle>speed) dangle = speed;
  else if (dangle<-speed) dangle = -speed;

  from += dangle;
  i4_normalize_angle(from);

  return dangle;
}


#endif
