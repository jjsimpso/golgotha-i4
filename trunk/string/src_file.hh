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
 

#define I4 ".."
#define G1 "../../golg"

char *saturn_files[]= {0};

char *msvc_files[]= 
{
  I4 "/main/win_main.cc",
  I4 "/file/win32/get_dir.cc",

  0
};


char *linux_files[]= 
{
  I4  "/main/nrm_main.cc",
  I4 "/file/linux/get_dir.cc",
  I4 "/file/linux/linux_file.cc",
  0
} ;


char *common_files[]= 
{
  
  I4 "/file/file.cc",
  I4 "/file/buf_file.cc",
  I4 "/checksum/checksum.cc",

  I4 "/memory/bmanage.cc",
  I4 "/memory/malloc.cc",
  I4 "/memory/growheap.cc",
  
  I4 "/error/error.cc",
  I4 "/error/alert.cc",

  I4 "/string/string.cc",
  I4 "/init/init.cc",

  I4 "/time/profile.cc",

  "resource_save.cc",
  G1 "/drive_map.cc",
  0
} ;

char *includes[]= { I4 "/inc",
                    I4,
                    G1,
                    0 };

char *exe_base="resource_save";
