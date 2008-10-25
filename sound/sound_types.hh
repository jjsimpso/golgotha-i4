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
 

#ifndef SOUND_TYPES_HH
#define SOUND_TYPES_HH

#include "arch.hh"

#ifdef I4_RETAIL
#define I4_SOUND_NAME(x)
#else
#define I4_SOUND_NAME(x) virtual char *name() { return x; }
#endif

typedef sw32 i4_frequency;
typedef sw32 i4_volume;
typedef sw32 i4_pan;

enum { I4_SOUND_VOLUME_LEVELS = 64 };
enum { I4_SOUND_MAX_PAN=10000 };

#endif

//{{{ Emacs Locals
// Local Variables:
// folded-file: t
// End:
//}}}
