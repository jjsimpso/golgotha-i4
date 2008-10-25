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
 

#include "init/init.hh"
#include "error/error.hh"


i4_init_class *i4_init_class::first_init=0;
static i4_bool i4_inited=i4_F;

void i4_show_init_list()
{
  for (i4_init_class *f=i4_init_class::first_init; f; f=f->next_init)
    i4_warning("%p\n",f);
}

void i4_init()
{
  I4_ASSERT(!i4_inited, "i4 already initialized");


  for (int t=0; t<=I4_INIT_TYPE_OTHER; t++)
  {
    i4_init_class *i=i4_init_class::first_init;  
    for (;i;i=i->next_init)
      if (i->init_type()==t)
        i->init();

    if (t==I4_INIT_TYPE_MEMORY_MANAGER)
      i4_inited=i4_T;   // ok to allocate memory after this stage
  }


}

void i4_uninit()
{
  I4_ASSERT(i4_inited, "i4_uninit() without i4_init()");

  for (int t=I4_INIT_TYPE_OTHER; t>=0; t--)
  {
    i4_init_class *i=i4_init_class::first_init;  
    for (;i;i=i->next_init)
      if (i->init_type()==t)
        i->uninit();
  }

  i4_inited=i4_F;
}


i4_init_class::~i4_init_class()
{
  i4_init_class *last=0, *i=first_init;

  for (;i && i!=this;)
  {
    last=i;
    i=i->next_init;
  }
  
  if (!i)
    i4_error("couldn't find init to remove");

  if (last)
    last->next_init=next_init;
  else
    first_init=next_init;

  next_init=0;
}


i4_bool i4_is_initialized()
{
  return i4_inited;
}

i4_init_class::i4_init_class()
{
  this->next_init=first_init;
  first_init=this;
}
