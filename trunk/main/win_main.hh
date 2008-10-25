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
 

#ifndef I4_WIN_MAIN_HH
#define I4_WIN_MAIN_HH


#include <windows.h>

// globals that other windows routines may need access to

extern HINSTANCE i4_win32_instance;  // instance of the application passed in through main
extern int       i4_win32_nCmdShow;  // how the window was initially opened (minimized?)
extern HWND      i4_win32_window_handle;    // main window, for some reason direct sound needs this

struct i4_win32_startup_options_struct
{
  char fullscreen;
  i4_win32_startup_options_struct()
  {
    fullscreen=1;
  }
  void check_option(char *opt);
};

extern i4_win32_startup_options_struct i4_win32_startup_options;

#endif
