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
 

#ifndef I4_NET_SOCKET_HH
#define I4_NET_SOCKET_HH

#include "arch.hh"
#include "file/file.hh"

class i4_net_address;

class i4_net_socket : public i4_file_class
{
public:
  virtual i4_bool connect(i4_net_address *addr) { return i4_F; }

  virtual i4_bool accept(i4_net_socket *&sock, i4_net_address *&addr) = 0;

  virtual w32 read_from(void *buffer, w32 size, i4_net_address *&addr) = 0;

  virtual w32 read (void *buffer, w32 size) = 0;
  virtual w32 write(const void *buffer, w32 size) = 0;

  virtual i4_bool ready_to_read() = 0;
  virtual i4_bool ready_to_write() = 0;
  virtual i4_bool error_occurred() = 0;

  virtual w32 seek (w32 offset) { return 0; }
  virtual w32 size () { return 0; }
  virtual w32 tell () { return 0; }

  virtual void set_select_status(i4_bool read, i4_bool write, i4_bool error) = 0;

};


#endif
