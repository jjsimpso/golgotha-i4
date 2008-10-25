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
 

#include "status/status.hh"

i4_status_create_function_type i4_stat_fun=0;

void i4_set_status_create_function(i4_status_create_function_type fun)
{
  i4_stat_fun=fun;
}

i4_idle_class *i4_idle_class::first=0;


i4_idle_class::i4_idle_class()
{
  next=first;
  first=this;
}

i4_idle_class::~i4_idle_class()
{
  if (first==this)
    first=first->next;
  else 
  {
    i4_idle_class *p=first;
    for (;p->next && p->next!=this; p=p->next);
    p->next=next;
  }
}



#ifdef _WINDOWS
#include <windows.h>
#include <commctrl.h>
#include "main/win_main.hh"
#include "string/string.hh"
#include "time/time.hh"

enum {MAX_UPDATES=50};

static int stat_y=40;

class win32_status_class : public i4_status_class
{
public:
  HWND hwndPB;    // handle of progress bar 
  i4_time_class start_time;
  int last_p;
  i4_bool win_created;
  i4_str *description;

  virtual i4_bool update(float percent)
  {
    i4_time_class now;
    if (now.milli_diff(start_time)>500)
    {
      start_time.get();

      if (!win_created)
      {      
        InitCommonControls(); 

        char buf[100];
        i4_os_string(*description, buf, 100);

        hwndPB = CreateWindowEx(0, PROGRESS_CLASS, buf, 
                                WS_BORDER | WS_VISIBLE, 50, stat_y,
                                500, 40,
                                0, (HMENU) 0, i4_win32_instance, NULL); 
 
 
        // Set the range and increment of the progress bar. 
        SendMessage(hwndPB, PBM_SETRANGE, 0, MAKELPARAM(0, MAX_UPDATES)); 
        SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 
        win_created=i4_T;
      }   
    }

    if (win_created)
    {
      int p=percent*MAX_UPDATES;
      while (last_p!=p)
      {
        last_p++;
        SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
      }
    }

    return i4_T;
  }

  win32_status_class(const i4_const_str &d)
  {
    description=new i4_str(d);
    win_created=i4_F;
    last_p=0;
    stat_y+=60;
  }

  virtual ~win32_status_class()
  {
    delete description;

    if (win_created)
    {
      while (last_p!=MAX_UPDATES)
      {
        last_p++;
        SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
      }

      DestroyWindow(hwndPB);     
    }

    stat_y-=60;

  }
};



// this is operating system dependant
i4_status_class *i4_create_status(const i4_const_str &description, int flags)
{
  if (i4_stat_fun)
    return i4_stat_fun(description, flags);
  else
  {
    return new win32_status_class(description);
  }
} 


#else


class i4_null_status_class : public i4_status_class
{
public:
  i4_bool update(float percent) 
  { 
    for (i4_idle_class *p=i4_idle_class::first; p;p=p->next)
      p->idle();
    return i4_T; 
  }
};


i4_status_class *i4_create_status(const i4_const_str &description, int flags)
{
  if (i4_stat_fun)
    return i4_stat_fun(description, flags);
  else
    return new i4_null_status_class;
}



#endif
