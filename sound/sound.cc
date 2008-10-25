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
 

#include "sound/sound.hh"
#include "main/main.hh"
#include "string/string.hh"

i4_sound_manager_class i4_null_sound;
i4_sound_manager_class *i4_sound_man = &i4_null_sound;

void i4_sound_manager_class::init()
{ 
  for (w32 i=1; i<i4_global_argc; i++)
    if (i4_global_argv[i]=="-no_sound")
      return;

  if (this!=&i4_null_sound) 
    i4_sound_man=this;    
}


i4_sound_manager_class::sound_parameters::sound_parameters
     (i4_frequency  _frequency,
      w32           _channels,
      w32           _sample_size,
      i4_volume     _volume,
      i4_pan        _pan,
      i4_bool       _looping,
      i4_bool       _reverb,
      i4_bool       _streaming,
      i4_bool       _capable_3d)
{
  frequency   = _frequency;
  channels    = _channels;
  sample_size = _sample_size;
  volume      = _volume;
  pan         = _pan;
  looping     = _looping;
  reverb      = _reverb;
  streaming   = _streaming;
  capable_3d  = _capable_3d;
}
