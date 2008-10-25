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
 

#include "inc/arch.hh"

#ifdef _WINDOWS

void null_function() {}

w32 MSVC_p[20];
w32 MSVC_params=0;
void (*MSVC_func)()=&null_function;
static char FP_SAVE[120];

typedef void (*func0)(void);
typedef void (*func1)(w32 a);
typedef void (*func2)(w32 a,w32 b);
typedef void (*func3)(w32 a,w32 b,w32 c);
typedef void (*func4)(w32 a,w32 b,w32 c,w32 d);
typedef void (*func5)(w32 a,w32 b,w32 c,w32 d,w32 e);

void MSVC_exec()
{
  __asm {
    pushfd
    pushad
    fsave FP_SAVE
    frstor FP_SAVE    

    push ebp
    mov  ebp, esp
    push ecx
    push ebx
    push esi
    push edi
  }

  switch (MSVC_params)
  {
    case 1: (*((func1)MSVC_func))(MSVC_p[0]); break;
    case 2: (*((func2)MSVC_func))(MSVC_p[0],MSVC_p[1]); break;
    case 3: (*((func3)MSVC_func))(MSVC_p[0],MSVC_p[1],MSVC_p[2]); break;
    case 4: (*((func4)MSVC_func))(MSVC_p[0],MSVC_p[1],MSVC_p[2],MSVC_p[3]); break;
    case 5: (*((func5)MSVC_func))(MSVC_p[0],MSVC_p[1],MSVC_p[2],MSVC_p[3],MSVC_p[4]); break;
    default:(*((func0)MSVC_func))(); break;
  }
  MSVC_func = &null_function;
  MSVC_params = 0;

  __asm {
    pop edi
    pop esi
    pop ebx
    pop ecx
    mov esp, ebp
    pop ebp

    frstor FP_SAVE    
    popad
    popfd
  }
}
#endif
