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
 

#ifndef I4_BINARY_TREE_HH
#define I4_BINARY_TREE_HH

/*
pretty simple, uses linear_allocator for quick allocation
two methods, ::insert & ::find so far, you need to define the > & <
  operators for the type if they don't exsist.

example ussage:
-------------------

i4_binary_tree<int> tree;
tree.insert(6);
tree.insert(10);
if (tree.find(12))  x=5;
 
or for user defined structs :

struct complex
{
  float a;
  float b;

  i4_bool operator>(const command_matchup c) const { return (i4_bool)(a>c.b); }
  i4_bool operator<(const command_matchup b) const { return (i4_bool)(a<c.b); }
};

i4_binary_tree<complex> tree2;
tree2.insert(complex(3.1, 4.5));
tree2.find(complex(3.1,0));
*/

#include "memory/lalloc.hh"

template <class T>
class i4_binary_tree
{
  void recursive_delete(T * node)
  {
    if (node->right)
      recursive_delete(node->right);
    if (node->left)
      recursive_delete(node->left);
    delete node;
  }

public:
  T *root;

  i4_binary_tree()   { root=0; }


  // insert return a previous instance if already in tree
  T *insert(T *x)
  {   
    x->left=x->right=0;

    if (!root)
      root=x;
    else
    {
      T *p=root;
              
      while (1)
      {
        int cmp=x->compare(p);
        if (cmp<0)
        {
          if (!p->left)
          {
            p->left=x;
            return x;
          }
          else p=p->left;
        }
        else if (cmp>0)
        {
          if (!p->right)
          {
            p->right=x;
            return x;
          }
          else p=p->right;
        }
        else return p;
      }
    }

    return x;
  }

  T *find(const T *x)
  {
    T *p=root;
    while (1)
    {
      if (!p) return 0;

      int cmp=x->compare(p);
      if (cmp<0)
        p=p->left;
      else if (cmp>0)
        p=p->right;
      else return p;
    }
  }

  void delete_tree()
  {
    if (root)
      recursive_delete(root);
  }

};

#endif
