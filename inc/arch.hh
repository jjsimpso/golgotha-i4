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
 

//{{{ Interface 4 
//
//  System dependant #defines and macros
//  Endianess macros
//    short_swap,long_swap  - exchange endianess
//    lstl, lltl            - little short to local, little long to local (swaps to x86 endianess)
//

#ifndef __ARCH_HPP_
#define __ARCH_HPP_

#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#include "config_default.h"
#endif

#if defined (HAVE_TYPES_H) && defined (HAVE_FILES_H) && defined (HAVE_ERRORS_H)
#include <Types.h>
#include <Files.h>
#include <Errors.h>
#endif

// w8
#if SIZEOF_UNSIGNED_CHAR == 1
typedef unsigned char w8;
#else
#error no type found for w8
#endif

// sw8
#if SIZEOF_CHAR == 1
typedef char sw8;
#else
#error no type found for sw8
#endif

// w16
#if SIZEOF_UNSIGNED_CHAR == 2
typedef unsigned char w16;
#elif SIZEOF_UNSIGNED_SHORT == 2
typedef unsigned short w16;
#elif SIZEOF_UNSIGNED_INT == 2
typedef unsigned int w16;
#else
#error no type found for w16
#endif

// sw16
#if SIZEOF_CHAR == 2
typedef char sw16;
#elif SIZEOF_SHORT == 2
typedef short sw16;
#elif SIZEOF_INT == 2
typedef int sw16;
#else
#error no type found for sw16
#endif

// w32
#if SIZEOF_UNSIGNED_CHAR == 4
typedef unsigned char w32;
#elif SIZEOF_UNSIGNED_SHORT == 4
typedef unsigned short w32;
#elif SIZEOF_UNSIGNED_INT == 4
typedef unsigned int w32;
#elif SIZEOF_UNSIGNED_LONG == 4
typedef unsigned long w32;
#else
#error no type found for w32
#endif

// sw32
#if SIZEOF_CHAR == 4
typedef char sw32;
#elif SIZEOF_SHORT == 4
typedef short sw32;
#elif SIZEOF_INT == 4
typedef int sw32;
#elif SIZEOF_LONG == 4
typedef long sw32;
#else
#error no type found for sw32
#endif

// w64
#if SIZEOF_UNSIGNED_CHAR == 8
typedef unsigned char w64;
#elif SIZEOF_UNSIGNED_SHORT == 8
typedef unsigned short w64;
#elif SIZEOF_UNSIGNED_INT == 8
typedef unsigned int w64;
#elif SIZEOF_UNSIGNED_LONG == 8
typedef unsigned long w64;
#elif SIZEOF_UNSIGNED_LONG_LONG == 8
typedef unsigned long long w64;
#elif SIZEOF_UNSIGNED___INT64 == 8   // from config_default.h
typedef unsigned __int64 w64;
#else
#error no type found for w64
#endif

// sw64
#if SIZEOF_CHAR == 8
typedef char sw64;
#elif SIZEOF_SHORT == 8
typedef short sw64;
#elif SIZEOF_INT == 8
typedef int sw64;
#elif SIZEOF_LONG == 8
typedef long sw64;
#elif SIZEOF_LONG_LONG == 8
typedef long long sw64;
#elif SIZEOF___INT64 == 8   // from config_default.h
typedef __int64 sw64;
#else
#error no type found for sw64
#endif

#define w16_swap(x) (((((w16) (x)))<<8)|((((w16) (x)))>>8))
#define w32_swap(x) \
    ((( ((w32)(x)) )>>24)|((( ((w32)(x)) )&0x00ff0000)>>8)| \
    ((( ((w32)(x)) )&0x0000ff00)<<8)|(( ((w32)(x)) )<<24))

#ifdef WORDS_BIGENDIAN

enum { i4_bigend=1, i4_litend=0 };

#define s_to_lsb(x) w16_swap(x)
#define l_to_lsb(x) w32_swap(x)
#define s_to_msb(x) (x)
#define l_to_msb(x) (x)

#else

enum { i4_bigend=0, i4_litend=1 };

#define s_to_lsb(x) (x)
#define l_to_lsb(x) (x)
#define s_to_msb(x) w16_swap(x)
#define l_to_msb(x) w32_swap(x)

#endif // WORDS_BIGENDIAN

typedef sw16 i4_coord;  // use this type for all x & y positions withing images
typedef w32  i4_color;  // reserved as 32bits in case we expand to 32 bit color

#define i4_null 0

#ifdef HAVE___FASTCALL
#define I4_FAST_CALL __fastcall
#else
#define I4_FAST_CALL
#endif

typedef w8 i4_bool;

enum  { i4_F=0, 
        i4_T=1 };


// use this mainly for events, to cast to a known event type
#define CAST_PTR(var_name, type, source_obj) type *var_name=(type *)(source_obj)

inline void *ALIGN_FORWARD(void *addr)
{
  return (void*)(((w32)addr+3)&~3);
}

inline void *ALIGN_BACKWARD(void *addr)
{
  return (void*)(((w32)addr)&~3);
}

#endif // __ARCH_HPP_
