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
 


/*  

Example ussage of threads :

void test(void *arg)
{
.. do something..
}

my_main()
{
  i4_add_thread(test,10*1024);
}

*/

#ifndef I4_THREADS_HH
#define I4_THREADS_HH

#include "arch.hh"

typedef void (*i4_thread_func_type)(void *context);

i4_bool i4_threads_supported();

// this will start the thread right away, regardless of how many threads are running
void i4_add_thread(i4_thread_func_type fun, w32 stack_size=50*1024, void *context=0);

void i4_thread_yield();
void i4_wait_threads();  // waits for all threads to terminate (don't call from a thread!)
int  i4_get_thread_id();
int  i4_get_main_thread_id(); 


void i4_suspend_other_threads();  // stops all of threads from running
void i4_resume_other_threads();   // resumes execution of other threads

int i4_get_first_thread_id();
i4_bool i4_get_next_thread_id(int last_id, int &id);
void i4_get_thread_stack(int thread_id, void *&base, void *&top);


enum i4_thread_priority_type { I4_THREAD_PRIORITY_HIGH,
                               I4_THREAD_PRIORITY_NORMAL,
                               I4_THREAD_PRIORITY_LOW };
       
void i4_set_thread_priority(int thread_id, i4_thread_priority_type priority);


class i4_critical_section_class
{
  w32 data[6];  // to store operating system depandant data, enlarge if needed
public:
  i4_critical_section_class();
  void I4_FAST_CALL lock();
  void I4_FAST_CALL unlock();
  ~i4_critical_section_class();
};


class i4_signal_object
{
  w32 data[1]; // to store operating system depandant data, enlarge if needed
public:
  i4_signal_object(char *name);
  void wait_signal();
  void signal();
  ~i4_signal_object();
};


#endif
