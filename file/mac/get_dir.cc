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
 

#include "memory/malloc.hh"
#include "dirent.hh"
#include "file/get_dir.hh"

class i4_dir_string : public i4_str
//{{{
{
public:
  i4_dir_string(StringPtr st) : i4_str(st[0])
  {
    len=st[0];
    memcpy(ptr,st,len);
  }

  char *buffer() { return ptr; }
  void set_len(w16 _len) { len = _len; }
};
//}}}


extern char *i4_os_string(const i4_const_str &name);


i4_bool i4_get_directory(const i4_const_str &path, 
                      i4_str **&files, w32 &tfiles,
                      i4_str **&dirs, w32 &tdirs)
//{{{
{
  struct dirent *de;
  files=NULL;
  dirs=NULL;
  tfiles=0;
  tdirs=0;
  DIR *d=opendir(i4_os_string(path));
  if (!d) return i4_F;

  i4_dir_string **tlist=NULL;
  sw32 t=0;
  char curdir[256];
  getwd(curdir);
  if (chdir(i4_os_string(path))!=0)
    return i4_F;

  do
  {
    de=readdir(d);
    if (de)
    {
      t++;
      tlist=(i4_dir_string **)i4_realloc(tlist,sizeof(i4_dir_string *)*t,"tmp file list");
      tlist[t-1]=new i4_dir_string(de->d_name);
    }
  } while (de);
  closedir(d);

  for (int i=0;i<t;i++)
  {
    d=opendir(((i4_dir_string *)tlist[i])->buffer() );   // see if the file is a directory
    if (d)
    {
      tdirs++;
      dirs=(i4_str **)i4_realloc(dirs,sizeof(i4_str *)*tdirs,"dir list");
      dirs[tdirs-1]=tlist[i];
      closedir(d);
    } else
    {
      tfiles++;
      files=(i4_str **)i4_realloc(files,sizeof(i4_str *)*tfiles,"dir list");
      files[tfiles-1]=tlist[i];
    }
  }
  if (t)
    i4_free(tlist);
  chdir(curdir);
  return i4_T;
}
//}}}


//{{{ Emacs Locals
// Local Variables:
// folded-file: t
// End:
//}}}







