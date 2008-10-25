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
 

#ifndef I4_MP3_LOAD_HH
#define I4_MP3_LOAD_HH


class i4_file_class;
class i4_sound_info;
class i4_status_class;


i4_bool i4_load_mp3(i4_file_class *in,  // open file at beginging of mp3 data (after header)
                    i4_file_class *out,    // open file ready to write raw data
                    i4_sound_info &output_format,  // defined in i4/loaders/wav_load.hh
                    i4_status_class *status);   // tells user what's going on
                       


#endif
