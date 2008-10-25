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
 * The aim of this file is to define symbols that autoconf would normally
 * take care of. Then this file is included #ifndef HAVE_CONFIG_H.
 */

#ifndef __CONFIG_DEFAULT_H
#define __CONFIG_DEFAULT_H

/*
 * which stat function to call
 */
#ifdef _WINDOWS
#define HAVE__STAT
#undef  HAVE_STAT
#else
#undef  HAVE__STAT
#define HAVE_STAT
#endif

/*
 * __fastcall on win32
 */
#ifdef _WINDOWS
#define HAVE___FASTCALL
#else
#undef HAVE___FASTCALL
#endif

/*
 * which mkdir() to call
 */
#ifdef _WINDOWS
#define HAVE__MKDIR
#undef  HAVE_MKDIR
#else
#undef  HAVE__MKDIR
#define HAVE_MKDIR
#endif

#if defined (__linux) || defined (__sun__)
#define HAVE_UNISTD_H
#define HAVE_SYS_WAIT_H
#else
#undef HAVE_UNISTD_H
#undef HAVE_SYS_WAIT_H
#endif

/*
 * win32 includes needed in various places
 */
#ifdef _WINDOWS
#define HAVE_DIRECT_H
#define HAVE_PROCESS_H
#define HAVE_WINSOCK_H
#else
#undef HAVE_DIRECT_H
#undef HAVE_PROCESS_H
#undef HAVE_WINSOCK_H
#endif

/*
 * MacOS includes needed in various places
 */
#ifdef __MAC__
#define HAVE_TYPES_H
#define HAVE_FILES_H
#define HAVE_ERRORS_H
#else
#undef HAVE_TYPES_H
#undef HAVE_FILES_H
#undef HAVE_ERRORS_H
#endif

/*
 * for typedefs in i4/inc/arch.hh
 */
#undef SIZEOF_UNSIGNED_CHAR
#undef SIZEOF_UNSIGNED_SHORT
#undef SIZEOF_UNSIGNED_INT
#undef SIZEOF_UNSIGNED_LONG
#undef SIZEOF_UNSIGNED_LONG_LONG
#undef SIZEOF_UNSIGNED___INT64
#undef SIZEOF_CHAR
#undef SIZEOF_SHORT
#undef SIZEOF_INT
#undef SIZEOF_LONG
#undef SIZEOF_LONG_LONG
#undef SIZEOF___INT64

// 32 bit architectures
#if defined(__sgi) || defined(__linux) || defined(__WATCOMC__) || defined(SUN4) || defined(_WINDOWS) ||defined(__MAC__)

#define SIZEOF_UNSIGNED_LONG 4   /* w32 */
#define SIZEOF_UNSIGNED_SHORT 2  /* w16 */
#define SIZEOF_UNSIGNED_CHAR 1   /* w8 */
#define SIZEOF_LONG 4            /* sw32 */
#define SIZEOF_SHORT 2           /* sw16 */
#define SIZEOF_CHAR 1            /* sw8 */

#if (__linux || __sgi || SUN4)         /* gcc has long long */
#define SIZEOF_UNSIGNED_LONG_LONG 8    /* w64 */
#define SIZEOF_LONG_LONG 8             /* sw64 */
#elif defined(_WINDOWS)                      // visual c has __int64
#define SIZEOF_UNSIGNED___INT64 8       /* w64 */
#define SIZEOF___INT64 8                /* sw64 */
#else
#error please define w64
#endif

#else
// 16 and 64 bit architectures are not defined yet
// but can be added here as long as the compiler supports 32 bit words
#error unknown architecture, please define basic types
#endif


/*
 * for endian settings in i4/inc/arch.hh
 */
#if defined(__linux) || defined(__WATCOMC__) || defined(_WINDOWS)
#undef WORDS_BIGENDIAN
#else
#define WORDS_BIGENDIAN
#endif


#endif /* __CONFIG_DEFAULT_H */
