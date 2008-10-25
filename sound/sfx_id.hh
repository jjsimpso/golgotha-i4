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
 

#ifndef S1_SFX_ID_HH
#define S1_SFX_ID_HH

#include "arch.hh"
#include "math/vector.hh"

class i4_voice_class;
class i4_transform_class;
class i4_file_class;

enum
{ 
  S1_STREAMED=1,
  S1_3D=2
};

       
class s1_sfx_ref;
class s1_sound_handle;

// the sound manager will call a callback when a looping 3d sound
// enters hearing distance and is to be played.  The callback should
// return it's current velocity.
typedef void (*s1_3d_sound_callback)(s1_sound_handle *handle, 
                                     float &xv, float &yv, float &zv,
                                     float &frequency_scale);

class s1_sound_handle
{
public: 
  float x, y,z, xv, yv, zv;         // current position of source
  float frequency_scale;


  void setup(float _x, float _y, float _z,
             float _xv, float _yv, float _zv,
             float _frequency_scale=1.0)
  { x=_x; y=_y;  z=_z;  xv=_xv; yv=_yv; zv=_zv; frequency_scale=_frequency_scale; }


  // don't change these directly!
  s1_sfx_ref *originator;      
  float dist_sqrd;
  s1_sound_handle *next;
  static s1_sound_handle *first;
  sw16 channel_on;
  i4_bool playing;
  
  s1_sound_handle();
  ~s1_sound_handle();
};


class s1_sfx_ref
{
public:
  static s1_sfx_ref *first;
  s1_sfx_ref        *next;
  w8                 flags;
  w16                id;
  w8                 priority;
  char              *name;
  char              *file_defined_in;
  int                line_defined_on;
  i4_voice_class    *base_sfx;
  float              hearable_distance_sqrd;

  s1_sfx_ref(char *filename, w8 flags, w8 priority, float dist, char *file, int line);
  ~s1_sfx_ref();

  // for playing static (non-looping/moving) 3d sound
  void play(float x=0, float y=0, float z=0);

  void play_looping(s1_sound_handle &handle);
};

void s1_end_looping(s1_sound_handle &handle);


void s1_load();      // load all the referenced static & dynamic sounds
void s1_unload();
void s1_get_camera_pos(i4_3d_vector &pos);
void s1_set_camera_pos(i4_transform_class &new_cam_transform);
char *s1_get_sfx_path();
void s1_save_sfx_list(i4_file_class *fp);


#define S1_SFX(name, filename, type, priority) \
  static s1_sfx_ref name(filename, type, priority, 20, __FILE__,__LINE__)

#define S1_SFX_DISTANCE(name, filename, type, priority, distance) \
  static s1_sfx_ref name(filename, type, priority, distance,  __FILE__,__LINE__)

#endif

