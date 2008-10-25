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
#include <process.h>
#include "error/error.hh"
#include "init/init.hh"

class r1_self_modify_class : public i4_init_class
{
public:

  void init()
  {
    HMODULE                       OurModule = GetModuleHandle(0);
    BYTE                         *pBaseOfImage = 0;

    if ( (GetVersion() & 0xC0000000) == 0x80000000)
    {
      // We're on Win32s, so get the real pointer
      HMODULE                       Win32sKernel = GetModuleHandle("W32SKRNL.DLL");

      typedef DWORD __stdcall       translator(DWORD);
      translator                   *pImteFromHModule =
        (translator *) GetProcAddress(Win32sKernel, "_ImteFromHModule@4");
      translator                   *pBaseAddrFromImte =
        (translator *) GetProcAddress(Win32sKernel, "_BaseAddrFromImte@4");

      if (pImteFromHModule && pBaseAddrFromImte)
      {
        DWORD                         Imte = (*pImteFromHModule) ( (DWORD) OurModule);

        pBaseOfImage = (BYTE *) (*pBaseAddrFromImte) (Imte);
      }
    }
    else
      pBaseOfImage = (BYTE *) OurModule;


    if (pBaseOfImage)
    {
      IMAGE_OPTIONAL_HEADER        *pHeader = (IMAGE_OPTIONAL_HEADER *)
        (pBaseOfImage + ( (IMAGE_DOS_HEADER *) pBaseOfImage)->e_lfanew +
         sizeof (IMAGE_NT_SIGNATURE) + sizeof (IMAGE_FILE_HEADER));

      DWORD                         OldRights;

      VirtualProtect(pBaseOfImage + pHeader->BaseOfCode, pHeader->SizeOfCode,
                     PAGE_READWRITE, &OldRights);
    }
  }

} r1_self_modify_instance;
