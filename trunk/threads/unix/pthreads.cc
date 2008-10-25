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
 

#include <stdio.h>
#include <pthread.h>
#include "error/error.hh"
#include "threads/threads.hh"
#include "init/init.hh"
#include "main/main.hh"
#include <sched.h>
#include <semaphore.h>

static w32 i4_thread_count=0;
static i4_critical_section_class i4_thread_start_lock;
static i4_critical_section_class i4_thread_lock;
static i4_thread_func_type i4_thread_to_start;

struct thread_node
{
  pthread_t handle;
  w32 thread_id;
  thread_node *next;
  void *base, *top;

  thread_node(pthread_t handle, w32 thread_id, void *base, void *top,
              thread_node *next) : handle(handle), thread_id(thread_id),
	      next(next), base(base), top(top) {}
};

static thread_node *thread_list=0;
thread_node *p=0;
int i4_main_thread_id;
static int i4_thread_size;

void i4_wait_threads()  // waits for all threads to terminate
                        // (don't call from a thread!)
{
  //i4_warning("Waiting threads");
  while (i4_thread_count!=0)
    i4_thread_yield();
}

void remove_thread(int id)
{
  i4_thread_start_lock.lock();

  thread_node *p=0;
  if (thread_list->thread_id==id)
  {
      p=thread_list;
      thread_list=thread_list->next;
  }
  else
  {
    thread_node *q;
    for (q=thread_list; q->next->thread_id!=id; q=q->next);
    p=q->next;
    q->next=p->next;
  }

  pthread_cancel(p->handle);
  delete p;
  i4_thread_start_lock.unlock();
}


void *i4_thread_starter(void *arg)
{
  //i4_warning("Inside thread");
  i4_thread_func_type start=i4_thread_to_start;
  int size=i4_thread_size;
  size-=200;
  i4_thread_to_start=0;

  i4_thread_start_lock.lock();
  w32 thread_id=pthread_self();

  pthread_t handle;
  thread_node *p=new thread_node(handle, thread_id,
                                 (void *)&size,
				 (void *)(((char *)&size)-size),
				 thread_list);

  thread_list=p;
  i4_thread_start_lock.unlock();
    
  start(arg);

  remove_thread(p->thread_id);
  
  i4_thread_lock.lock();
  i4_thread_count--;
  i4_thread_lock.unlock();

  //i4_warning("Exiting thread");
  pthread_exit(0);
  
  return 0;  
}

void i4_add_thread(i4_thread_func_type fun, w32 stack_size, void *arg_list)
{
  while (i4_thread_to_start!=0)
    i4_thread_yield();

  //i4_warning("Add thread");

  i4_thread_to_start=fun;
  i4_thread_size=stack_size;
  i4_thread_lock.lock();
  i4_thread_count++;
  i4_thread_lock.unlock();

  //i4_warning("Creating thread");
  pthread_create(&p->handle, 0, i4_thread_starter, arg_list);
}

void i4_thread_yield()
{
  //i4_warning("Thread yielding");
  sched_yield();
}

int i4_get_thread_id()
{
  //i4_warning("Get_thread_id");
  return pthread_self();
}

int i4_get_main_thread_id()
{
  //i4_warning("Get main thread");
  return i4_main_thread_id;
}

i4_bool i4_get_first_thread_id(int &id);

int i4_get_first_thread_id() { return 0; }

i4_bool i4_get_next_thread_id(int last_id, int &id);

i4_bool i4_get_next_thread_id(int last_id, int &id)
{
  //i4_warning("Get next thread id");

  for (thread_node *p=thread_list; p; p=p->next)
    if (p->thread_id==last_id)
      if (p->next)
      {
        id=p->next->thread_id;
	return i4_T;
      }
      else
        return i4_F;

  return i4_F;
}

void i4_suspend_other_threads()
{
  //i4_warning("Suspend other threads");

  i4_thread_start_lock.lock();

  w32 thread_id=pthread_self();
  for (thread_node *p=thread_list; p; p=p->next)
    if (p->thread_id!=thread_id)
      //i4_warning("I should be suspending this thread"); 

  i4_thread_start_lock.unlock();
}

void i4_resume_other_threads()
{
  //i4_warning("Resume other threads");

  i4_thread_start_lock.lock();

  w32 thread_id=pthread_self();
  for (thread_node *p=thread_list; p; p=p->next)
    if (p->thread_id!=thread_id)
      //i4_warning("I should be resuming this thread");

  i4_thread_start_lock.unlock();
}

void i4_get_thread_stack(int thread_id, void *&base, void *&top)
{
  //i4_warning("Get thread stack");

  base=0;
  top=0;

  if (thread_id==i4_main_thread_id)
  {
    base=i4_stack_base;
    if (i4_get_thread_id()!=i4_main_thread_id)
      i4_error("Can't get main thread stack from thread");
    
    int t;
    top=(void *)(&t);      
  }
  else
  {
    for (thread_node *p=thread_list; p; p=p->next)
      if (p->thread_id==thread_id)
      {
        base=p->base;
        top=p->top;
      }
  }
}

i4_bool i4_threads_supported() { return i4_T; }

class pthreads_init : public i4_init_class
{
public:
  virtual int init_type() { return I4_INIT_TYPE_THREADS; }
  void init()
  {
     //i4_warning("Init threads");
  }

  void uninit()
  {
     //i4_warning("UnInit threads");
  }

};

void i4_set_thread_priority(int thread_id, i4_thread_priority_type priority)
{
  //i4_warning("Set thread priority");

}


// Critical section (mutexes)

pthread_mutex_t mutex;

i4_critical_section_class::i4_critical_section_class(void)
{
//  i4_warning("Init mutex");
  pthread_mutex_init(&mutex,0);
}

i4_critical_section_class::~i4_critical_section_class(void)
{
  //i4_warning("Destroying Mutex");
  pthread_mutex_destroy(&mutex);
}

void i4_critical_section_class::lock(void)
{ 
  //i4_warning("Locking Mutex");
  pthread_mutex_lock(&mutex);
}

void i4_critical_section_class::unlock(void)
{
  //i4_warning("Unlocking Mutex");
  pthread_mutex_unlock(&mutex);
}

// Signals

sem_t semaphore;

i4_signal_object::i4_signal_object(char *name) 
{ 
  i4_warning("Create signal object");

//  sem_init(&semaphore, 0, 0);
}

void i4_signal_object::wait_signal()           
{
  i4_warning("Wait signal..");

//  sem_wait(&semaphore);

}

void i4_signal_object::signal()                
{
  i4_warning("Signal...");

//  sem_post(&semaphore);
}

i4_signal_object::~i4_signal_object()          
{
  i4_warning("Destroying signal object");

//  sem_destroy(&semaphore);
}

