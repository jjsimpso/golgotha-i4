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
 

#ifndef TEST_HH
#define TEST_HH

#include <stdio.h>

class CStart
// Startup code test
{
public:
  CStart(char *name)
  {
    printf("%s loaded successfully\n",name);
  }
};

class CBase
// Base class for virtual functions & object members testing
{
protected:
  virtual char *Type() = 0;
public:
  char *name;

  CBase(char *_name) : name(_name) {}

  void print() 
  {
    printf("I'm [%s]:[%s].\n", Type(), name);
  }

  virtual void Action(char *command) = 0;
};

class CFoundry;
extern CFoundry *Foundry;
class CFoundry
{
private:
  friend class CBaseFoundry;
  CFoundry *next, *prev;

  CFoundry(int dummy) 
  {
    next = this;
    prev = this;
  }

public:
  CFoundry()
  {
    prev = Foundry;
    next = Foundry->next;
    Foundry->next->prev = this;
    Foundry->next = this;
    printf("Foundry registered.\n");
  }

  ~CFoundry()
  {
    next->prev = prev;
    prev->next = next;
    printf("Foundry unlinked.\n");
  }

  virtual char *Type() = 0;
  virtual CBase *Make(char *name) = 0;
};

typedef void (*test_func)(int a, int b);

extern CBase *Make(char *type, char *name);

#endif
