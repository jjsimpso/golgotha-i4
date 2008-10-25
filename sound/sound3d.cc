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
 

#include "sound/sound3d.hh"

i4_3d_vector i4_3d_sound_parameters::null(0,0,0);

class i4_null_3d_voice_class : public i4_3d_voice_class
//{{{
{
protected:
  completion_function_type complete;
  void *context;
public:
  i4_null_3d_voice_class() : i4_3d_voice_class(), complete(0), context(0) {}

  virtual void set_completer(completion_function_type _complete, void *_context)
  //{{{
  {
    complete = _complete;
    context = _context;
  }
  //}}}
  virtual void play() { if (complete) (*complete)(this); }
  virtual void update() {}
};
//}}}

class i4_null_3d_sound_class : public i4_3d_sound_manager_class
//{{{
{
public:
  i4_null_3d_voice_class null_3d_voice;

  I4_SOUND_NAME("No 3D sound");

  virtual void init() {}
  virtual void load_sounds(w32 max_sounds) { }

  virtual i4_3d_voice_class *alloc(i4_sound_id sound_id, const i4_3d_sound_parameters& param)
  //{{{
  {
    return &null_3d_voice;
  }
  //}}}
};
//}}}

i4_null_3d_sound_class i4_null_3d_sound;

i4_3d_sound_manager_class *i4_3d_sound_man = &i4_null_3d_sound;

//{{{ Emacs Locals
// Local Variables:
// folded-file: t
// End:
//}}}
