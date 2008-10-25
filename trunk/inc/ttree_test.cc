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
 

#include "ttree.hh"
#include "init/init.hh"
#include "main/main.hh"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *delim=" ,.?!;:\"()-`'<>{}[]|-=+\n\t";

void test()
{
  i4_ternary_tree<int> t;

  int count=0;

  char buff[256];
  int val, cont=1;

  while (cont)
  {
    printf("> ");
    gets(buff);
    
    switch (buff[0])
    {
      case 'q':
        cont = 0;
        break;
      case 'a':
        if (t.add(&buff[2], count++, &val))
          printf("[%s] repeated at %d\n", &buff[2], val);
        break;
      case 's':
        if (t.find(&buff[2],&val))
          printf("found [%s] = %d\n", &buff[2], val);
        else
          printf("[%s] not found\n", &buff[2]);
        break;
      case 'd':
        if (t.remove(&buff[2],&val))
          printf("removed [%s] = %d\n", &buff[2], val);
        else
          printf("[%s] not removed\n", &buff[2]);
        break;
      case 'f':
      {
        char *name = &buff[2];

        if (!buff[1] || !buff[2])
          name = "/usr/dict/words";

        FILE *f = fopen(name,"rt");
        char line[1024], *s;

        if (f)
        {
          printf("Loading file '%s'\n", name);
          while (fgets(line, sizeof(line), f))
          {
            for (s = strtok(line, delim); s; s = strtok(0,delim))
            {
              for (char *c=s; *c; c++)
                *c = (char)tolower(*c);
              if (t.add(s, count++, &val))
                printf("[%s] repeated from %d.\n",s,val);
            }
          }
          fclose(f);
        }
      } break;
      case 'c':
      {
        FILE *f = fopen(&buff[2],"rt");
        char line[1024], *s;

        if (f)
        {
          printf("Checking file '%s'\n", &buff[2]);
          while (fgets(line, sizeof(line), f))
          {
            for (s = strtok(line, delim); s; s = strtok(0,delim))
            {
              for (char *c=s; *c; c++)
                *c = (char)tolower(*c);
              if (!t.find(s))
                printf("[%s] not found.\n", s);
            }
          }
          fclose(f);
        }
      } break;
      case 'u':
      {
        FILE *f = fopen(&buff[2],"rt");
        char line[1024], *s;

        if (f)
        {
          printf("Unloading file '%s'\n", &buff[2]);
          while (fgets(line, sizeof(line), f))
          {
            for (s = strtok(line, delim); s; s = strtok(0,delim))
            {
              for (char *c=s; *c; c++)
                *c = (char)tolower(*c);
              if (t.remove(s, &val))
                printf("Removing [%s] = %d\n", s, val);
            }
          }
          fclose(f);
        }
      } break;
      case 'l':
      {
        char name[256];
        i4_ternary_tree<int>::iterator i(t, name, sizeof(name));

        for (; !i.end(); i++)
          printf("[%s] = %d\n", i.key(), *i);
      } break;
    }
  }
}

void i4_main(w32 argc, i4_const_str *argv)
{
  i4_init();
  
  test();

  i4_uninit();
}
