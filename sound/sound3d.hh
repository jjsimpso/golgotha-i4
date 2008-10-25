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
 

#ifndef SOUND3D_HH
#define SOUND3D_HH

#include "sound/sound_types.hh"
#include "init/init.hh"
#include "math/vector.hh"

class i4_3d_sound_parameters
//{{{
{
protected:
  i4_3d_sound_parameters() {}
public:
  static i4_3d_vector null;

  i4_frequency frequency;
  i4_volume volume;
  i4_3d_vector position, velocity;
  i4_bool looping, reverb;
  
  i4_3d_sound_parameters(i4_frequency freq,
                         i4_volume vol = I4_SOUND_VOLUME_LEVELS-1,
                         const i4_3d_vector& pos = null,
                         const i4_3d_vector& vel = null,
                         i4_bool looping = i4_F,
                         i4_bool reverb = i4_F)
    : frequency(freq), 
      volume(vol), 
      position(pos),
      velocity(vel),
      looping(looping), 
      reverb(reverb) {}

  void set(const i4_3d_sound_parameters &param)
  //{{{
  {
    frequency = param.frequency;
    volume = param.volume;
    position = param.position; 
    velocity = param.velocity;
    looping = param.looping; 
    reverb = param.reverb;
  }
  //}}}
};
//}}}

class i4_3d_voice_class : public i4_3d_sound_parameters
{
protected:
  i4_3d_voice_class() : i4_3d_sound_parameters() {}
public:
  i4_3d_voice_class(const i4_3d_sound_parameters &param)
    : i4_3d_sound_parameters(param.frequency, 
                             param.volume, 
                             param.position, 
                             param.velocity,
                             param.looping, 
                             param.reverb) {}

  typedef i4_bool (*completion_function_type)(void *_context);

  virtual void set_completer(completion_function_type completer, void *_context) = 0;
  virtual void play() = 0;
  virtual void update() = 0;
};

class i4_3d_sound_manager_class;
extern i4_3d_sound_manager_class *i4_3d_sound_man;

class i4_3d_sound_manager_class : public i4_init_class
{
protected:
public:
  virtual void init() { i4_3d_sound_man = this; }
  virtual void load_sounds(w32 max_sounds) = 0;
  virtual i4_3d_voice_class *alloc(i4_sound_id sound_id, const i4_3d_sound_parameters& param) = 0;
  i4_3d_voice_class *play(i4_sound_id sound_id, const i4_3d_sound_parameters& param)
  //{{{
  {
    i4_3d_voice_class *voc = alloc(sound_id,param);
    
    if (voc)
      voc->play();

    return voc;
  }
  //}}}

#ifndef I4_RETAIL
  virtual char *name() const = 0;
#endif
};

class i4_null_3d_sound_class;
extern class i4_null_3d_sound_class i4_null_3d_sound;

#endif

//{{{ Emacs Locals
// Local Variables:
// folded-file: t
// End:
//}}}
