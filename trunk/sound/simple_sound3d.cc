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
 

#include "sound/simple_sound3d.hh"
#include "error/error.hh"

#define speed_of_sound 512.0
#define position_to_volume 0.1

i4_simple_3d_sound_manager_class i4_simple_3d_sound;


void i4_simple_3d_voice_class::play()
//{{{
{
  update();
  voc->play();
}
//}}}


void i4_simple_3d_voice_class::update()
//{{{
{
  i4_frequency freq;
  i4_volume vol, pan;

  i4_3d_vector a(position);
  i4_float len = a.length();

  pan = (i4_volume)(a.x*position_to_volume);
  pan = 
    (pan>=I4_SOUND_VOLUME_LEVELS)? I4_SOUND_VOLUME_LEVELS-1 : 
    ((pan<=-I4_SOUND_VOLUME_LEVELS)? -I4_SOUND_VOLUME_LEVELS+1 : pan);

  if (len<0.0001)
    a.set(0,0,0);
  else
    a /= len;
  i4_float vel = a.dot(velocity);

  freq = (i4_frequency)((i4_float)frequency)*((-vel + speed_of_sound)/speed_of_sound);

  vol = volume - (i4_volume)(len*position_to_volume);
  vol = (vol<0)? 0 : vol;

  voc->set_frequency(freq);
  voc->set_volume(vol);
  voc->set_pan(pan);
}
//}}}


void i4_simple_3d_sound_manager_class::init()
//{{{
{
  i4_3d_sound_manager_class::init();

  // note: should theoretically turn itself off if the only sound manager
  //   available is the null_sound_manager;
}
//}}}


void i4_simple_3d_sound_manager_class::load_sounds(w32 max_sounds)
//{{{
{
  i4_sound_man->load_sounds(max_sounds);
}
//}}}


i4_3d_voice_class *i4_simple_3d_sound_manager_class::alloc(i4_sound_id sound_id, 
                                                           const i4_3d_sound_parameters& param)
//{{{
{
  i4_sound_manager_class::sound_parameters dummy;

  dummy.looping = param.looping;
  dummy.reverb = param.reverb;

  i4_voice_class *voc = i4_sound_man->alloc(sound_id, dummy);

  if (voc)
    return new i4_simple_3d_voice_class(voc, param);
  else
    return 0;
}
//}}}


//{{{ Emacs Locals
// Local Variables:
// folded-file: t
// End:
//}}}
