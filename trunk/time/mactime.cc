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
 

#include "time/time.hh"
#include <Timer.h>

i4_time_class::i4_time_class()
//{{{
{
  Microseconds((UnsignedWide*)private_data);
}
//}}}


i4_bool i4_time_class::operator <(const i4_time_class &other) const 
//{{{
{
  w32 *me_t=(w32 *)private_data;
  w32 *other_t=(w32 *)other.private_data;
  return (other_t[0]<me_t[0] || (other_t[0]==me_t[0] &&  other_t[1]<me_t[1]));
}
//}}}


i4_bool i4_time_class::operator >(const i4_time_class &other) const 
//{{{
{
  w32 *me_t=(w32 *)private_data;
  w32 *other_t=(w32 *)other.private_data;
  return (other_t[0]>me_t[0] || (other_t[0]==me_t[0] &&  other_t[1]>me_t[1]));
}
//}}}


sw32 i4_time_class::milli_diff(const i4_time_class &past_time) const
//{{{
{
  w32 *me_t=(w32 *)private_data;
  w32 *past_t=(w32 *)past_time.private_data;

  return ((sw32)me_t[1]-(sw32)past_t[1])/1000+(me_t[0]-past_t[0])*1000;
}
//}}}


//{{{ Emacs Locals
// Local Variables:
// folded-file: t
// End:
//}}}
