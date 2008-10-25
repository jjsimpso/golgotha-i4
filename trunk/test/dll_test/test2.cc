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
 

#include "test.hh"

CStart startup("Test2");

class CTest2 : public CBase
{
protected:
  virtual char *Type() { return "Test2"; }
public:
  int accesses;
  CBase *sub;

  CTest2(char *name) : CBase(name), accesses(0), sub(0) {}

  ~CTest2()
  {
    if (sub)
      delete sub;
    sub = 0;
  }

  virtual void Action(char *command)
  {
    accesses++;
    switch (command[0]) {
    case 'c':
      if (sub)
	delete sub;
      sub = Make("Test1","subobject");
      break;
    case 's':
      sub->Action(command+2);
      break;
    case 'p':
      print();
      break;
    case 'a':
      printf("I've been accessed %d times.\n", accesses);
      break;
    }
  }
};

class CTest2Foundry : public CFoundry
{
public:
  char *Type() { return "Test2"; }
  CBase *Make(char *name) { return new CTest2(name); }
} CTest2Foundry;

extern "C" void test2(int a, int b)
{
  printf("Test 2 succesfully executed with %d and %d\n",a,b);
}
