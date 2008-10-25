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
 

#include "string/string.hh"
#include "error/alert.hh"
#ifdef _MANGLE_INC
#include "../../golg/DRIVE~RO.HH"
#else
#include "../../golg/drive_map.hh"
#endif

FILE *out;

struct hack_str
{
  char *s;
  w16 len;  
};

void print_token(char *s)
{
  char *s2;
  i4_bool need_quote=i4_F;
  for (s2=s; *s2; s2++)
    if (*s2==' ')
      need_quote=i4_T;

  if (need_quote)
    fprintf(out,"\"");
  for (; *s; s++)
  {
    if (*s=='\n')
      fprintf(out,"\\n");
    else if (*s=='\r')
      fprintf(out,"\\r");
    else if (*s=='\"')
      fprintf(out,"\\\"");
    else if (*s=='\t')
      fprintf(out,"\\t");
    else if (*s=='\\')
      fprintf(out,"\\\\");
    else if (*s=='$')
      fprintf(out,"\\$");
    else if (*s=='/' && s[1]=='/')
      fprintf(out,"\\/");

    else fprintf(out,"%c",*s);
  }

  if (need_quote)
    fprintf(out,"\"");
}

void print_atoken(char **s)
{
  fprintf(out,"{");
  while (*s)
  {
    print_token(*s);
    s++;
    if (*s)          
      fprintf(out," ");

  }
  fprintf(out,"}");
}

class i4_string_manager_saver_class
{
public:
  void dump_node(i4_string_manager_class::node *p)
  {
    if (p)
    {
      print_token(p->str_token);
      fprintf(out," ");
      print_token(((hack_str *)&p->value)->s);
      fprintf(out,"\n");

      dump_node(p->left);
      dump_node(p->right);
    }
  }

  void dump_array_node(i4_string_manager_class::array_node *p)
  {
    if (p)
    {
      print_token(p->str_token);
      fprintf(out," ");
      print_atoken(p->value);
      fprintf(out,"\n");

      dump_array_node(p->left);
      dump_array_node(p->right);
    }
  }

  i4_string_manager_saver_class(i4_string_manager_class *str_man)
  {
    dump_node(str_man->root);
    dump_array_node(str_man->array_root);
  }

};

i4_string_manager_class lx_s;

void i4_main(w32 argc, i4_const_str *argv)
{
  i4_init(0,0);
  if (argc!=3)
    i4_error("bad # of argurments, ussage file_name symbol_name");

#ifdef __linux
  char *drive_map_resource = 
    "f:/ f:/ "
    "F:/ F:/ "
    "/u/ /u/ "
    "c:/ c:/ "
    "C:/ C:/ "
    "/tmp/ /tmp/ "
    "res_name c:/3dsmax/plugins/resource/ "
    "res_loc /u/oliy/src/crack/maxtool/res/ "
    "alpha1 \\//alpha1/ "
    "/ / "
    ;



  lx_s.load_buffer(0,drive_map_resource,"drive_map_resource");
  i4_file_man.mount_dir(lx_s.get("f:/"),new g1_drive_map(lx_s.get("/u/")));
  i4_file_man.mount_dir(lx_s.get("F:/"),new g1_drive_map(lx_s.get("/u/")));
  i4_file_man.mount_dir(lx_s.get("c:/"),new g1_drive_map(lx_s.get("/tmp/")));  
#endif


  i4_string_man.load(0,argv[1]);
  out=fopen("/tmp/parse.out","wb");
  if (!out)
    i4_error("unable to open tmp file");

  i4_string_manager_saver_class d(&i4_string_man);
  fclose(out);


  out=fopen("/tmp/parse.out","rb");
  printf("char %s[]={\n  ",((hack_str *)&argv[2])->s);
  int c,x=0;

  while (!feof(out))
  {
    c=fgetc(out);
    if (!feof(out))
    {
      if (x!=0)
        printf(",");
      if (((x+1)%15)==0)
      {
        printf("\n  ");
      }

      printf("0x%x",c);


    }
    x++;

  }
  printf("};\n");

  fflush(stdout);


  i4_uninit();
}
