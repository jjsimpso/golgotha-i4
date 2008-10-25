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


enum {MAX_UPDATES=100};

class win32_status_class
{
public:
  HWND hwndPB;    // handle of progress bar 

  int last_p;

  virtual i4_bool update(float percent)
  {
    int p=percent*MAX_UPDATES;
    while (last_p!=p)
    {
      last_p++;
      SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
    }
  }

  win32_status_class(HWND hwndPB) : hwndPB(hwndPB)
  {
    last_p=0;
  }

  virtual ~i4_status_class()
  {
    DestroyWindow(hwndPB);     
  }
};

// this is operating system dependant
i4_status_class *i4_create_status(const i4_const_str &description)
{
  RECT rcClient;  // client area of parent window 
  int cyVScroll;  // height of scroll bar arrow 
  HWND hwndPB;    // handle of progress bar 
  HANDLE hFile;   // handle of file 
  DWORD cb;       // size of file and count of bytes read 
  LPCH pch;       // address of data read from file 
  LPCH pchTmp;    // temporary pointer 
 
    // Ensure that the common control DLL is loaded and create a 
    // progress bar along the bottom of the client area of the 
    // parent window. Base the height of the progress bar on 
    // the height of a scroll bar arrow. 
  InitCommonControls(); 


  hwndPB = CreateWindowEx(0, PROGRESS_CLASS, (LPSTR) NULL, 
                          WS_BORDER | WS_VISIBLE, CW_USEDEFAULT,  CW_USEDEFAULT,
                          320, 20,
                          0, (HMENU) 0, i4_win32_instance, NULL); 
 
 
  // Set the range and increment of the progress bar. 
  SendMessage(hwndPB, PBM_SETRANGE, 0, MAKELPARAM(0, MAX_UPDATES)); 
  SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 
 
  return new win32_status_class(hwndPB);
} 



