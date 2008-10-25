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
 

#include "palette/pal8.hh"
#include "error/error.hh"

i4_pal8_manager i4_pal8_man;

i4_pal8_manager::i4_pal8_manager()
{
  memset(palette_references,0,sizeof(palette_references));    // no reference to any palettes yet
}

w8 *i4_pal8_manager::get_remap_table(i4_pal8_handle from, i4_pal8_handle to)
{
  w16 index=from.id*MAX_PALETTES+to.id;

  w8 *data=remap_tables+index*256;

  if (tables_calculated.get(index))
    return data;
  else
  {
    w32 *from_pal=palette_tables+from.id*256;
    w32 *to_pal=palette_tables+to.id*256;

    w16 x,y;
    w32 c1,c2;
    sw16 r1,g1,b1,
         r2,g2,b2,nd,d=-1,best;

    for (x=0;x<256;x++)
    {
      c1=*from_pal;

      r1=(c1&0xff0000)>>16;
      g1=(c1&0xff00)>>8;
      b1=(c1&0xff);
      

      for (y=0;y<256;y++)
      {
	c2=to_pal[y];

	r2=(c2&0xff0000)>>16;
	g2=(c2&0xff00)>>8;
	b2=(c2&0xff);       
	nd=(r1-r2)*(r1-r2)+(g1-g2)*(g1-g2)+(b1-b2)*(b1-b2);	
	if (nd<d)
	{
	  d=nd;
	  best=y;
	}
      }      
      *(data++)=best;      
    }
    return remap_tables+index*256;
  }
}

i4_pal8_handle i4_pal8_manager::register_pal(w32 *palette_data)
{
  int x;
  for (x=0;x<MAX_PALETTES;x++)
  {
    if (!palettes_allocated.get(x))
    {      
      palettes_allocated.set(x,i4_T);
      memcpy(palette_tables+x*256,palette_data,256*4);
      i4_pal8_handle ret(x);
      return ret;
    }
  }

  i4_error("Max palette allocation = %d, exceeded",MAX_PALETTES);
}

void i4_pal8_manager::unregister_pal(i4_pal8_handle id)
{
  if (!palettes_allocated.get(id.id))
    i4_error("unregistering bad palette");
  else if (palette_references[id.id])
    i4_error("unregistering referenced palette");
  else
    palettes_allocated.set(id.id,i4_F);
    

}

