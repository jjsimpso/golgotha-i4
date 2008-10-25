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
 

/*
 * Mpeg Layer-1,2,3 audio decoder
 * ------------------------------
 * copyright (c) 1995 by Michael Hipp, All rights reserved. See also 'README'
 * version for slower machines .. decodes only every second sample
 * sounds like 24000,22050 or 16000 kHz .. (depending on original sample freq.)
 *
 */

#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "loaders/mp3/mpg123.hh"

#define WRITE_SAMPLE(samples,sum,clip) \
  if( (sum) > 32767.0) { *(samples) = 0x7fff; (clip)++; } \
  else if( (sum) < -32768.0) { *(samples) = -0x8000; (clip)++; } \
  else { *(samples) = (short) sum; }

static int bo = 1;

void init_decode_2to1(void)
{
	bo = 1;
}

int synth_2to1_8bit(real *bandPtr,int channel,unsigned char *samples)
{
  short samples_tmp[32];
  short *tmp1 = samples_tmp + channel;
  int i,ret;

  samples += channel;
  ret = synth_2to1(bandPtr,channel,(unsigned char *) samples_tmp);

  for(i=0;i<16;i++) {
    *samples = conv16to8[*tmp1>>4];
    samples += 2;
    tmp1 += 2;
  }

  return ret;
}

int synth_2to1_8bit_mono(real *bandPtr,unsigned char *samples)
{
  short samples_tmp[32];
  short *tmp1 = samples_tmp;
  int i,ret;

  ret = synth_2to1(bandPtr,0,(unsigned char *) samples_tmp);

  for(i=0;i<16;i++) {
    *samples++ = conv16to8[*tmp1>>4];
    tmp1 += 2;
  }

  return ret;
}


int synth_2to1_8bit_mono2stereo(real *bandPtr,unsigned char *samples)
{
  short samples_tmp[32];
  short *tmp1 = samples_tmp;
  int i,ret;

  ret = synth_2to1(bandPtr,0,(unsigned char *) samples_tmp);

  for(i=0;i<16;i++) {
    *samples++ = conv16to8[*tmp1>>4];
    *samples++ = conv16to8[*tmp1>>4];
    tmp1 += 2;
  }

  return ret;
}

int synth_2to1_mono(real *bandPtr,unsigned char *samples)
{
  short samples_tmp[32];
  short *tmp1 = samples_tmp;
  int i,ret;

  ret = synth_2to1(bandPtr,0,(unsigned char *) samples_tmp);

  for(i=0;i<16;i++) 
  {
    *( (short *) samples) = *tmp1;
    samples+=2;

    tmp1 += 2;
  }

  return ret;
}

int synth_2to1_mono2stereo(real *bandPtr,unsigned char *samples)
{
  int i,ret = synth_2to1(bandPtr,0,samples);
  for(i=0;i<16;i++) {
    ((short *)samples)[1] = ((short *)samples)[0];
    samples+=4;
  }
  return ret;
}

int synth_2to1(real *bandPtr,int channel,unsigned char *out)
{
  static real buffs[2][2][0x110];
  static const int step = 2;
  short *samples = (short *) out;

  real *b0,(*buf)[0x110];
  int clip = 0; 
  int bo1;

  if(flags.equalizer)
    do_equalizer(bandPtr,channel);

  if(!channel) {
    bo--;
    bo &= 0xf;
    buf = buffs[0];
  }
  else {
    samples++;
    buf = buffs[1];
  }

  if(bo & 0x1) {
    b0 = buf[0];
    bo1 = bo;
    dct64(buf[1]+((bo+1)&0xf),buf[0]+bo,bandPtr);
  }
  else {
    b0 = buf[1];
    bo1 = bo+1;
    dct64(buf[0]+bo,buf[1]+bo+1,bandPtr);
  }

  {
    register int j;
    real *window = decwin + 16 - bo1;

    for (j=8;j;j--,b0+=0x10,window+=0x30)
    {
      real sum;
      sum  = *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;
      sum += *window++ * *b0++;
      sum -= *window++ * *b0++;

      WRITE_SAMPLE(samples,sum,clip); samples += step;
#if 0
      WRITE_SAMPLE(samples,sum,clip); samples += step;
#endif
    }

    {
      real sum;
      sum  = window[0x0] * b0[0x0];
      sum += window[0x2] * b0[0x2];
      sum += window[0x4] * b0[0x4];
      sum += window[0x6] * b0[0x6];
      sum += window[0x8] * b0[0x8];
      sum += window[0xA] * b0[0xA];
      sum += window[0xC] * b0[0xC];
      sum += window[0xE] * b0[0xE];
      WRITE_SAMPLE(samples,sum,clip); samples += step;
#if 0
      WRITE_SAMPLE(samples,sum,clip); samples += step;
#endif
      b0-=0x20,window-=0x40;
    }
    window += bo1<<1;

    for (j=7;j;j--,b0-=0x30,window-=0x30)
    {
      real sum;
      sum = -*(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;
      sum -= *(--window) * *b0++;

      WRITE_SAMPLE(samples,sum,clip); samples += step;
#if 0
      WRITE_SAMPLE(samples,sum,clip); samples += step;
#endif
    }
  }

  return clip;
}


