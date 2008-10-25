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
 

#include "lisp/li_init.hh"
#include "lisp/lisp.hh"
#include "error/error.hh"
#include "time/profile.hh"


li_object *li_profile(li_object *o, li_environment *env)
{
  li_object *r=li_eval(li_car(o,env),env);
  if (r->type()!=LI_STRING)
    i4_warning("profile expects a string arg");
  else
  {
    i4_profile_clear();
    i4_profile_stack_top=0;

    for (i4_profile_class *c=i4_profile_class::list; c; c=c->next)
    {
      if (strstr(c->name, li_get_string(r,env))!=0)
        c->active=1;
      else
        c->active=0;
    }
  }

  
  return 0;
}

li_object *li_profile_report(li_object *o, li_environment *env)
{
  li_object *r=li_eval(li_car(o,env),env);
  if (r->type()!=LI_STRING)
    i4_warning("profile expects a string arg");
  else
    i4_profile_report(li_get_string(r,env));

  
  return 0;
}


li_automatic_add_function(li_profile,"profile");
li_automatic_add_function(li_profile_report,"profile_report");
