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
 

#ifndef DRIVE_MAP_HH
#define DRIVE_MAP_HH

#include "file/file.hh"
#include "string/string.hh"

class i4_drive_map : public i4_file_manager_class
{  
protected:
  i4_str *drive_path;

public:

  i4_drive_map(const i4_const_str &path) 
  //{{{
  {
    drive_path=new i4_str(path,path.length()+1);
  }
  //}}}


  virtual i4_file_class *default_open(const i4_const_str &name, w32 flags)
  //{{{
  {
    i4_str *cat=new i4_str(*drive_path,drive_path->length()+name.length()+1);
    cat->insert(cat->end(),name);
    i4_file_class *fp=i4_file_manager_class::default_open(*cat,flags);
    delete cat;
    return fp;
  }
  //}}}


  virtual i4_bool get_status(const i4_const_str &filename, 
                             i4_file_status_struct &return_stat)
  //{{{
  {
    i4_str *cat=new i4_str(*drive_path,drive_path->length()+filename.length()+1);
    cat->insert(cat->end(),filename);
    i4_bool ret=i4_file_manager_class::get_status(*cat,return_stat);
    delete cat;
    return ret;
  }
  //}}}


  virtual i4_bool mkdir(const i4_const_str &name)
  //{{{
  {
    i4_str *cat=new i4_str(*drive_path,drive_path->length()+name.length()+1);
    cat->insert(cat->end(),name);
    i4_bool ret=i4_file_manager_class::mkdir(*cat);
    delete cat;
    return ret;
  }
  //}}}
};

#endif

//{{{ Emacs Locals
// Local Variables:
// folded-file: t
// End:
//}}}
