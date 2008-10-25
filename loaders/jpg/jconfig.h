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
/* jconfig.mc6 --- jconfig.h for Microsoft C on MS-DOS, version 6.00A & up. */
/* see jconfig.doc for explanations */

#define HAVE_PROTOTYPES
#define HAVE_UNSIGNED_CHAR
#define HAVE_UNSIGNED_SHORT
/* #define void char */
/* #define const */
#undef CHAR_IS_UNSIGNED
#define HAVE_STDDEF_H
#define HAVE_STDLIB_H
#undef NEED_BSD_STRINGS
#undef NEED_SYS_TYPES_H
//#define NEED_FAR_POINTERS	/* for small or medium memory model */
#undef NEED_SHORT_EXTERNAL_NAMES
#undef INCOMPLETE_TYPES_BROKEN

#ifdef JPEG_INTERNALS

#undef RIGHT_SHIFT_IS_UNSIGNED

//#define USE_MSDOS_MEMMGR	/* Define this if you use jmemdos.c */

#define MAX_ALLOC_CHUNK 65520L	/* Maximum request to malloc() */

#define USE_FMEM		/* Microsoft has _fmemcpy() and _fmemset() */

#define NEED_FHEAPMIN		/* far heap management routines are broken */

#define SHORTxLCONST_32		/* enable compiler-specific DCT optimization */
/* Note: the above define is known to improve the code with Microsoft C 6.00A.
 * I do not know whether it is good for later compiler versions.
 * Please report any info on this point to jpeg-info@uunet.uu.net.
 */

#endif /* JPEG_INTERNALS */

#ifdef JPEG_CJPEG_DJPEG

//#define BMP_SUPPORTED		/* BMP image file format */
//#define GIF_SUPPORTED		/* GIF image file format */
//#define PPM_SUPPORTED		/* PBMPLUS PPM/PGM image file format */
//#undef RLE_SUPPORTED		/* Utah RLE image file format */
#define TARGA_SUPPORTED		/* Targa image file format */

#define TWO_FILE_COMMANDLINE
#define USE_SETMODE		/* Microsoft has setmode() */
//#define NEED_SIGNAL_CATCHER	/* Define this if you use jmemdos.c */
#undef DONT_USE_B_MODE
#undef PROGRESS_REPORT		/* optional */

#endif /* JPEG_CJPEG_DJPEG */
