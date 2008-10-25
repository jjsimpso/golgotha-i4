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
 

class i4_socket_class
{
public:
  int fd;
  bind
  connect 
  accept
  gethostbyname
  socket( AF_INET,  SOCK_STREAM, 0); 
};



/* 
   This class responds to 'search' packets.  When other games are looking for
   a server they should have some way of finding the notifier socket.   
 */

class i4_notifier_socket
{
  i4_str *note_string;
protected:
  i4_notifier_socket(int port, const i4_const_str &notification_string);
public:
  virtual void set_notification_string(const i4_const_str &str);
  virtual void poll() = 0;
  virtual ~i4_notifier_socket();
};


class i4_finder_socket
{
protected:
  i4_finder_socket(int port);


}
