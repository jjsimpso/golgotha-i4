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
 

#ifndef LI_SYMBOLS_HH
#define LI_SYMBOLS_HH


#include "lisp/li_types.hh"

// global symbols
extern li_symbol *li_nil, 
  *li_true_sym, 
  *li_quote, 
  *li_backquote,
  *li_comma,
  *li_function_symbol;

li_symbol *li_get_symbol(char *name);     // if symbol doesn't exsist, it is created

// if cache_to is 0, then the symbol is found and stored there, otherwise cache_to is returned
li_symbol *li_get_symbol(char *name, li_symbol *&cache_to);

void li_mark_symbols(int set);

#endif
