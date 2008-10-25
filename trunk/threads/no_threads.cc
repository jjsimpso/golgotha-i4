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
 

#include <stdlib.h>
#include "threads/threads.hh"
#include "error/error.hh"
#include "time/time.hh"
#include "main/main.hh"

i4_critical_section_class::i4_critical_section_class() {}
void i4_critical_section_class::lock() {}
void i4_critical_section_class::unlock() {}
i4_critical_section_class::~i4_critical_section_class() {}


i4_signal_object::i4_signal_object(char *name) {}

void i4_signal_object::wait_signal() {}
void i4_signal_object::signal() {}
i4_signal_object::~i4_signal_object() {}


i4_bool i4_threads_supported() { return i4_F; }


// this will start the thread right away, regardless of how many threads are running
void i4_add_thread(i4_thread_func_type fun, w32 stack_size, void *context)
{
  i4_error("Threads not supported");
}

void i4_thread_yield() { i4_sleep(0); }

void i4_wait_threads() {}
int  i4_get_thread_id() { return 0; }
int  i4_get_main_thread_id() { return 0; }


void i4_suspend_other_threads() {}
void i4_resume_other_threads() {}

int i4_get_first_thread_id() { return 0; }
i4_bool i4_get_next_thread_id(int last_id, int &id) { return i4_F; }

void i4_get_thread_stack(int thread_id, void *&base, void *&top) 
{ 
  int t;
  base=i4_stack_base;
  top=(void *)(&t);
}


void i4_set_thread_priority(int thread_id, i4_thread_priority_type priority) { ;}
