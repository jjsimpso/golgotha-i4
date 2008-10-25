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
 

#ifndef SIMPLE_SOUND3D_HH
#define SIMPLE_SOUND3D_HH

#include "sound/sound3d.hh"
#include "sound/sound.hh"

class i4_simple_3d_voice_class : public i4_3d_voice_class 
{
protected:
  i4_voice_class *voc;
public:
  i4_simple_3d_voice_class(i4_voice_class *_voc, const i4_3d_sound_parameters &param) :
    voc(_voc), i4_3d_voice_class(param)
  //{{{
  {

  }
  //}}}

  virtual void set_completer(completion_function_type completer, void *_context)
  //{{{
  {
    voc->set_completer((i4_voice_class::completion_function_type)completer,_context);
  }
  //}}}
  virtual void play();
  virtual void update();
};

class i4_simple_3d_sound_manager_class : public i4_3d_sound_manager_class 
{
protected:
public:
  I4_SOUND_NAME("SimpleSound");

  virtual void init();
  virtual void load_sounds(w32 max_sounds);
  virtual i4_3d_voice_class *alloc(i4_sound_id sound_id, const i4_3d_sound_parameters& param);
};

#endif

//{{{ Emacs Locals
// Local Variables:
// folded-file: t
// End:
//}}}
