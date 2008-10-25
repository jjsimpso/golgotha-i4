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
 

#ifndef WAV_LOAD_HH
#define WAV_LOAD_HH

#include "arch.hh"

class i4_file_class;

// structure used to describe a sound
class i4_sound_info
{
public:
  w32 size;          // size of sound data in bytes
  w32 sample_rate;   // anything i.e. 22000
  w32 channels;      // 1 or 2
  w32 sample_size;   // 1 or 2 
};


// fills in the info field and advances file pointer to where sound data start
// returns false if something screwy is detected in the wav file
i4_bool i4_load_wav_info(i4_file_class *f, i4_sound_info &info);



#endif
