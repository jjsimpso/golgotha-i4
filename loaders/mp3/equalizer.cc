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
 


#include "loaders/mp3/mpg123.hh"

real equalizer[2][32];
real equalizer_sum[2][32];
int equalizer_cnt;

void do_equalizer(real *bandPtr,int channel) 
{
	int i;

	if(flags.equalizer & 0x1) {
		for(i=0;i<32;i++)
			bandPtr[i] *= equalizer[channel][i];
	}

	if(flags.equalizer & 0x2) {
		equalizer_cnt++;
		for(i=0;i<32;i++)
			equalizer_sum[channel][i] += bandPtr[i];
	}
}

