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
 

#include "file/file.hh"
#include "error/error.hh"

#include "file/buf_file.hh"

#ifdef _SATURN
extern "C"
{
#include "libsn.h"
};
#endif


class i4_saturn_file_class : public i4_file_class
//{{{
{
  w32 fd;
  public :
  i4_saturn_file_class(w32 fd) : fd(fd) {}

  virtual w32 read (void *buffer, w32 size) 
  //{{{
  {
    w32 ret=PCread(fd,(char *)buffer,size); 
    return ret;
  }
  //}}}

  virtual w32 write(void *buffer, w32 size) {}

  virtual w32 seek (w32 offset)               
  //{{{
  { 
    PClseek(fd,offset,0);
  }
  //}}}

  virtual w32 size ()                       
  //{{{
  { 
    
    w32 cur=PClseek(fd,0,SEEK_CUR);
    w32 len=PClseek(fd,0,SEEK_END);
    PClseek(fd,cur,SEEK_SET);
    return len;
  }
  //}}}

  virtual w32 tell ()                       
  //{{{
  { 
    w32 ret=PClseek(fd,0,SEEK_CUR); 
    return ret;
  }
  //}}}

  ~i4_saturn_file_class()                   
  //{{{
  { 
    PCclose(fd);
  }
  //}}}
};
//}}}


char *i4_os_string(const i4_const_str &name);

i4_file_class *i4_file_manager_class::default_open(const i4_const_str &name, w32 flags)
//{{{
{
  sw32 f=0;
  i4_bool no_buffer=i4_F;

  if (flags & NO_BUFFER)
  {
    flags=(file_flags)(flags & (~NO_BUFFER));
    no_buffer=i4_T;
  }

  switch (flags)
  {
    case READ: 
      break;

    default: 
      i4_warning("i4_file_class::Bad open flags!");
      return NULL;     
  }

  int fd;


  fd=PCopen(i4_os_string(name),0,0);

  if (fd<0)
  {
    i4_warning("i4_file_class::open failed for %s\n",i4_os_string(name));
    return NULL;
  }


  i4_file_class *ret_fp;
  if (!no_buffer)
    ret_fp=new i4_buffered_file_class(new i4_saturn_file_class(fd));
  else
    ret_fp=new i4_saturn_file_class(fd);

  return ret_fp;
}
//}}}


i4_bool i4_file_manager_class::default_unlink(const i4_const_str &name)
//{{{
{
  i4_error("What are you crazy?");
  
  return 0;
}
//}}}


i4_bool i4_file_manager_class::default_get_status(const i4_const_str &name, 
                                                  i4_file_status_struct &return_stat)
//{{{
{
  i4_error("What are you crazy?");

  return 0;
}
//}}}


i4_bool i4_file_manager_class::default_mkdir(const i4_const_str &name)
//{{{
{
  // What?  Are you crazy?
  return 0;
}
//}}}


i4_bool i4_file_manager_class::default_get_directory(const i4_const_str &path, 
                                             i4_str **&files, w32 &tfiles, 
                                             i4_str **&dirs, w32 &tdirs)
// returns i4_F if path is bad (tfiles and tdirs will be 0 as well)
//{{{
{
  // What?  Are you crazy?
  return 0;
}
//}}}


//{{{ Emacs Locals
// Local Variables:
// folded-file: t
// End:
//}}}
