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
 

#include "loaders/load.hh"
#include "memory/malloc.hh"
#include "file/file.hh"
#include "image/image.hh"
#include "error/alert.hh"

#include <stdlib.h>

static i4_image_loader_class *loader_list=NULL;
static w16 max_header_need=0;

void i4_image_loader_class::init()
{
  i4_image_loader_class *who=this;

  who->next=loader_list;
  loader_list=who;
  w16 mh=who->max_header_size();
  if (mh>max_header_need)
    max_header_need=mh;
}

void close_file(i4_file_class *fp)
{
  delete fp;
}

i4_image_class *i4_load_image(const i4_const_str &filename,
                              i4_status_class *status)
{
  i4_file_class *fp;
  fp=i4_open(filename);

  if (!fp)
    return NULL;
  
  i4_image_class *im=i4_load_image(fp, status);
  if (!im)
    i4_alert(i4gets("load_failed"),200,&filename);

  delete fp;
  return im;
}


i4_image_class *i4_load_image(i4_file_class *fp,
                              i4_status_class *status)
{
  if (max_header_need==0)   // cannot identify any formats
    return NULL;

  i4_image_loader_class *il=loader_list;
  i4_image_class *im=0;
  

  w8 *buf=(w8 *)i4_malloc(max_header_need,"sig buf");
  w16 size_read=fp->read(buf,max_header_need);
 
  for (;!im && il;il=il->next)
  {
    if (size_read>=il->max_header_size())
    {
      if (il->recognize_header(buf))
      {
	fp->seek(0);
	im=il->load(fp, status);
      }
    }    
  }

  i4_free(buf);
  return im;
}
