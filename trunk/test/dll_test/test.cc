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
 

#include "dll/dll.hh"
#include "test.hh"
#include <string.h>
#include <stdlib.h>

CFoundry *Foundry = 0;

class CBaseFoundry : public CFoundry
{
public:
  CBaseFoundry() : CFoundry(0)
  {
    if (Foundry != 0) {
      printf("Can only build one base foundry!");
      return;
    }
    Foundry = this;     
  }

  ~CBaseFoundry()
  {
    if (Foundry->next!=this)
      printf("Foundries not destroyed!\n");
  }

  virtual char *Type() { return "Base"; }
  virtual CBase *Make(char *name) { printf("Illegal Make!\n"); }

  CBase *Make(char *type, char *name) 
  {
    CFoundry *p = Foundry;
    while (p->next != Foundry) {
      p = p->next;
      if (!strcmp(type, p->Type()))
	return p->Make(name);
    }
    printf("Couldn't find the [%s] foundry\n", type);
    return 0;
  }
  
} BaseFoundry;

char dll_name[] =
"/u/oliy/src/crack/i4/test/dll_test/test1.dll"
;

char test_name[] =
"test1"
;

CBase *Make(char *type, char *name) 
{
  BaseFoundry.Make(type,name);
}

void main()
{
  i4_dll_file *test_dll[3];
  test_func test;

#if 1
  for (int i=0; i<3; i++)
    test_dll[i] = 0;
#else
  for (int i=1; i<3; i++) {
    dll_name[strlen(dll_name)-5] = '0'+i;
    test_name[4] = '0'+i;

    test_dll[i] = i4_open_dll(dll_name);
    test = (test_func)test_dll[i]->find_function(test_name);

    (*test)(1,2);
  }
#endif

  int cont = 1;
  char com[80];
  CBase *obj=0;

  while (cont) {
    printf("Test> ");
    gets(com);
    switch (com[0]) 
    {
      case 'l':
      {
        i4_dll_file *t;
        int i=atol(com+1);

        dll_name[strlen(dll_name)-5] = '0'+i;
        test_name[4] = '0'+i;

        if (t = i4_open_dll(dll_name))
        {
          test_dll[i] = t;
          test = (test_func)test_dll[i]->find_function(test_name);
        
          if (test)
            (*test)(1,2);
          else
            printf("%s not loaded from dll.\n",test_name);
        }
        else
          printf("%s not loaded.\n",dll_name);
      } break;
      case 'u':
      {
        int i=atol(com+1);

        if (i>=0 && i<3 && test_dll[i])
        {
          delete test_dll[i];
          test_dll[i] = 0;
        }
      } break;
      case 'n': 
      {
        char *type, *name;
        
        if (obj) {
          delete obj;
          obj = 0;
        }
        strtok(com," ");
        type = strtok(0," ");
        name = strtok(0," ");

        obj = Make(type, name);
      } break;
      case 'q':
        cont = 0;
        break;
      default:
        if (obj)
          obj->Action(com);
        break;
    }
  }

  if (obj) {
    delete obj;
    obj = 0;
  }

  for (int i=0; i<2; i++)
    if (test_dll[i])
      delete test_dll[i];
}

