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
 

#include <windows.h>
#include "video/display_dialog.hh"
#include "video/win32/resource.h"
#include "main/win_main.hh"

static int i4_choices_t_picks;

BOOL FAR PASCAL displayDlgProc(HWND hDlg,DWORD dwMessage,DWORD wParam,DWORD lParam)
{
  int         result, ctrlMsg, i;
  static int  busy;


  switch(dwMessage)
  {
    case WM_INITDIALOG:
    {
      char **picks=(char **)lParam;
      int t_picks=0;  
      while (picks[t_picks]) t_picks++;
      i4_choices_t_picks=t_picks;
      busy=0;


      for(i=0; picks[i]; i++)
      {
        CreateWindowEx(WS_EX_NOPARENTNOTIFY,
                       "BUTTON",
                       picks[i],
                       (WS_CHILD|BS_AUTORADIOBUTTON|WS_VISIBLE|((i==0)? WS_GROUP|WS_TABSTOP : 0)),
                       20,	// horizontal position of window
                       10+(i*16),	// vertical position of window
                       300,	// window width
                       12,	// window height
                       hDlg,	// handle to parent or owner window
                       (HMENU)(i+69),	// child-window identifier
                       i4_win32_instance, // handle to application instance
                       (LPVOID)NULL); // pointer to window-creation data
      }


      SetFocus( GetDlgItem(hDlg, 69) );
      CheckDlgButton(hDlg, 69, 1);  //check the first one as a default

      //return 0 here indicating we have set the focus for the dialog box
      //and it doesn't need to help us
      return 0;
    }

    case WM_SETCURSOR:
      if(busy)
      {
        SetCursor(LoadCursor(NULL, IDC_WAIT));
        return TRUE;
      }
      break;
      
    case WM_COMMAND:
      ctrlMsg=HIWORD(wParam);
      switch(LOWORD(wParam))
      {
        case IDOK:
          if(busy > 0) break;
          else if(ctrlMsg==STN_CLICKED)
          {
            for(i=0; i<i4_choices_t_picks; i++)
              if(IsDlgButtonChecked(hDlg, (i+69))==1) break;

            if (i==i4_choices_t_picks) i=-1;

            EndDialog(hDlg, i);
          }
          break;
            
        case IDCANCEL:
          if(!busy && ctrlMsg==STN_CLICKED)
            EndDialog( hDlg, -1 );
          break;
      }
  }
  return 0;
}


int i4_system_choose_option(char **choices)
{
  return DialogBoxParam(i4_win32_instance, 
                        MAKEINTRESOURCE(101), 
                        NULL, 
                        (DLGPROC)displayDlgProc, 
                        (long)choices );
}
