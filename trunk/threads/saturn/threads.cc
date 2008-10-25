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
 

#include "threads/threads.hh"

// this will start the thread right away, regardless of how many threads are running
void i4_add_thread(i4_thread_func_type fun, w32 stack_size, void *arg_list)
{
  fun(arg_list);
}

// this will start the thread after all other threads have exited, useful for queing
// up things that to disk access but don't want to do seek-thrashing
void i4_que_thread(i4_thread_func_type fun, w32 stack_size, void *arg_list)
{
  fun(arg_list);
}


void i4_end_of_thread() { ; }
void i4_end_of_que_thread() { ; }
void i4_thread_yield() { ; }
void i4_wait_threads() { ; }  // waits for all threads to terminate (don't call from a thread!)

