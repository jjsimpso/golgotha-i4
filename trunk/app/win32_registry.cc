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
#include "app/registry.hh"


i4_bool i4_get_registry(i4_registry_type type, 
                        char *path, 
                        char *key_name,
                        char *buffer, int buf_length)
{
  HKEY key;

  if (RegOpenKeyEx(type==I4_REGISTRY_MACHINE ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER,
                   path,
                   0,
                   KEY_READ,
                   &key)==ERROR_SUCCESS)
  {
    for (int i=0; 1; i++)
    {
      char name[256];
      DWORD name_size=256, type;
      DWORD data_size=buf_length;
     


      if (RegEnumValue(key, i, name, &name_size, 0, 
                     &type, 
                     (LPBYTE)buffer, 
                     &data_size)==ERROR_SUCCESS)
      {
        if (strcmp(name, key_name)==0)
        {
          RegCloseKey(key);
          return i4_T;
        }
      }
      else
      {
        RegCloseKey(key);
        return i4_F;
      }
    }
  }
  return i4_F;
}


i4_bool i4_set_registry(i4_registry_type type, 
                        char *path, 
                        char *key_name,
                        char *buffer)
{
  HKEY key;

  if (RegCreateKey(type==I4_REGISTRY_MACHINE ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER,
                 path,
                 &key)==ERROR_SUCCESS)
  {
    RegSetValueEx(key, key_name, 0, REG_SZ, (w8 *)buffer, strlen(buffer)+1);
    RegCloseKey(key);
    return i4_T;
  }
  
  return i4_F;
}

