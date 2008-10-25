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
 

#ifndef __IMAGE_LOAD_HPP_
#define __IMAGE_LOAD_HPP_

#include "arch.hh"
#include "init/init.hh"

class i4_const_str;
class i4_file_class;
class i4_image_class;
class i4_status_class;

class i4_image_loader_class : public i4_init_class
{
  public :
  // returns the maximum size you need to identify your file format
  virtual w16 max_header_size() = 0;                  

  // return true if you recognize your header signature
  virtual i4_bool recognize_header(w8 *buf) = 0;      

  // assume fp is at the start of the file
  // if status is non-null, then it should updated as the load progresses 
  virtual i4_image_class *load(i4_file_class *fp,
                               i4_status_class *status) = 0;            

  virtual void init();

  i4_image_loader_class *next;
} ;


i4_image_class *i4_load_image(const i4_const_str &filename, 
                              i4_status_class *status=0);

i4_image_class *i4_load_image(i4_file_class *fp,
                              i4_status_class *status=0);


#endif
