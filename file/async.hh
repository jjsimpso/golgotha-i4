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
 

#ifndef I4_ASYNC_READ_HH
#define I4_ASYNC_READ_HH

// This class should probably only be used by files in "i4/files/*"

// This class is a portable implemented of async file reading
// A thread gets created during init() which runs as long as
// there is stuff to read and then blocks for a signal from the main
// program so if nothing needs reading, it runs efficiently.  Request
// to be read are qued up (max of 16).  The request are processed
// serially.  If you want to read from multiple devices in parallel,
// you should create two i4_async_reads, one for each device.

#include "memory/que.hh"
#include "threads/threads.hh"
#include "init/init.hh"
#include "file/file.hh"

class i4_async_reader : public i4_init_class
{
  volatile i4_bool stop;
  i4_signal_object sig;

  i4_bool emulation;

  struct read_request
  {
    sw32 fd;
    void *buffer;
    w32 size;
    i4_file_class::async_callback callback;
    void *context;
    read_request(sw32 fd, void *buffer,
                 w32 size, i4_file_class::async_callback callback, 
                 void *context)
      : fd(fd), buffer(buffer), size(size), callback(callback), context(context) {}
    read_request() { ; }
  };

  enum { MAX_REQUEST=16 };
  enum { STACK_SIZE=8096 };
  i4_critical_section_class que_lock;
  i4_fixed_que<read_request, MAX_REQUEST> request_que;
  void emulate_speeds(read_request &r);

protected:

  virtual w32 read(sw32 fd, void *buffer, w32 count) = 0;

public:
  // name is just some unique name.  Windows requires this for Semaphores
  i4_async_reader(char *name);

  void init();   // creates thread (called by i4_init()
  void uninit(); // waits for thread to die (called by i4_uninit()

  // ques up a request
  i4_bool start_read(int fd, void *buffer, w32 size, 
                     i4_file_class::async_callback call,
                     void *context);

  void PRIVATE_thread();  // don't call this!
};


#endif
