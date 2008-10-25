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
 

#include "file/async.hh"
#include "threads/threads.hh"
#include "time/time.hh"
#include "error/error.hh"

i4_async_reader::i4_async_reader(char *name) : sig(name)  
{ 
  emulation=i4_F; 
  stop=i4_F;
}

void i4_async_reader_thread_start(void *arg)
{
  ((i4_async_reader *)arg)->PRIVATE_thread();
}

void i4_async_reader::init()
{
  if (i4_threads_supported())
  {
    stop=i4_T;
    i4_add_thread(i4_async_reader_thread_start, STACK_SIZE, this);
  }
}

void i4_async_reader::uninit()
{
  if (i4_threads_supported())
  {
    while (stop==i4_T)       // wait to thread is read to be stopped
      i4_thread_yield();
  
    stop=i4_T;
    sig.signal();
    while (stop)
      i4_thread_yield();
  }
}

i4_bool i4_async_reader::start_read(int fd, void *buffer, w32 size, 
                                    i4_file_class::async_callback call,
                                    void *context)
{
  if (!i4_threads_supported())
    i4_error("threads not supported");

  que_lock.lock();

  read_request r(fd, buffer, size, call, context);
  if (!request_que.que(r))
  {
    que_lock.unlock();
    return i4_F;
  }
  que_lock.unlock();

  sig.signal();
  return i4_T;
}


void i4_async_reader::emulate_speeds(read_request &r)
{    
  if (emulation) 
  {
    i4_time_class now, start;
    while (start.milli_diff(now) < (sw32)(r.size*1000/(1000*1024) + 20*1000))
    {
      i4_thread_yield();
      now.get();
    }
  }
}


void i4_async_reader::PRIVATE_thread()
{
  read_request r;
  sw32 amount;

  do
  {
    while (request_que.empty())   // if no more request to satisfy, wait for main process signal
    {
      stop=i4_F;
      sig.wait_signal();
    }

    if (!stop)
    {
      que_lock.lock();

      if (request_que.deque(r))
      {
        que_lock.unlock();
        emulate_speeds(r);

        amount = read(r.fd, r.buffer, r.size);          

        r.callback(amount, r.context);
      }
      else que_lock.unlock();
    }

  } while (!stop);
  stop=i4_F;
}
