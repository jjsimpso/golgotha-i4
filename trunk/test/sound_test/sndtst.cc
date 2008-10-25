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
 

#include "app/app.hh"
#ifdef _MANGLE_INC
#include "DRIVE~RO.HH"
#else
#include "drive_map.hh"
#endif
#include "main/main.hh"
#include "sound/sound.hh"

class sound_test_class : public i4_application_class
//{{{
{
public:
  I4_EVENT_HANDLER_NAME("m1_utility_app_class");

  virtual w32 max_memory() const { return 1000 * 1024; }
  
  sound_test_class(char *resource_file, void *resource_buffer) 
  {
    memory_init();

    //    g1_map_drives();

    resource_init(resource_file,resource_buffer);
    display_init();
  }
};
//}}}

sound_test_class *app;

int my_sleep(int val)
//{{{
{
  int val2 = -1;

  for (int i=0; i<val; i++)
    val2 *= val2;

  return val2;
}
//}}}

void i4_main(w32 argc, i4_const_str *argv)
//{{{
{
  app = new sound_test_class("resource.res",0);
  i4_voice_class *snd;
  int i;

  i4_sound_man->load_sounds(16);

  i4_sound_manager_class::sound_parameters param;
  param.frequency = 11025;
  param.volume = 63;
  param.pan = 0;
  param.looping = i4_T;

  snd = i4_sound_man->play(0, param);

  for (i=10000; i<100000; i+=50)
  {
    snd->set_frequency(i);
    my_sleep(4000);
  }
  snd->set_frequency(11025);

  for (i=0; i<=63; i++)
  {
    my_sleep(400000);
    snd->set_volume(i);
  }

  for (i=-63; i<=63; i++)
  {
    my_sleep(400000);
    snd->set_pan(i);
  }

  param.frequency = 10000;
  param.looping = i4_F;
  i4_sound_man->play(1, param);

  for (i=63; i>=0; i--)
  {
    my_sleep(10000);
    snd->set_volume(i);
  }
  snd->set_volume(63);

  param.frequency = 11025;
  i4_sound_man->play(1, param);

  app->run();
}
//}}}


//{{{ Emacs Locals
// Local Variables:
// folded-file: t
// End:
//}}}
