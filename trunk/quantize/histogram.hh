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
 

#ifndef HISTOGRAM_HH
#define HISTOGRAM_HH

#include "arch.hh"
#include "image/image.hh"

class i4_file_class;

class i4_histogram_class
{
  public :
  enum { HIST_SIZE=0x10000,  // 16 bit histogram table
         MAX_COLORS=256 };

  w16 reference[HIST_SIZE];
  w32 counts[HIST_SIZE];
  w32 tcolors;              // total original colors in the histogram [length of reference]
  w32 total_pixels;         // total pixels accounted for in image (affected by counts_per_pixel)


  i4_histogram_class();
  
  void increment_color(w16 color,  // this is expected to be a 16 bit color (5 6 5)
                       w32 count)
  {
    if (!counts[color])            // is this an original color?
    {
      reference[tcolors]=color;    // add this color to the reference list
      tcolors++;
    }
    counts[color]+=count;          // increment the counter for this color
    total_pixels+=count;           // count total pixels we've looked at
  }

  void reset()
  {
    for (w32 i=0; i<tcolors; i++)    
      counts[reference[i]]=0;
    tcolors=0;
    total_pixels=0;
  }

  void save(i4_file_class *fp);
  void load(i4_file_class *fp);

  // counts_per_pixel can be used to give smaller images more emphasis
  // I use this to give mip maps of original images more double emphasis
  // right now only image's of type i4_image32 will work
  void add_image_colors(i4_image_class *image, int counts_per_pixel=1);

} ;



#endif
