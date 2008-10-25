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
/*==========================================================================
 *
 *  Copyright (C) 1995-1996 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       fastfile.h
 *  Content:    Definitions for fastfile access.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTBILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 ***************************************************************************/

typedef LPVOID  HFASTFILE;

extern BOOL FastFileInit( LPSTR fname, int max_handles );
extern void FastFileFini( void );
extern HFASTFILE FastFileOpen( LPSTR name );
extern BOOL FastFileClose( HFASTFILE pfe );
extern BOOL FastFileRead( HFASTFILE pfh, LPVOID ptr, int size );
extern BOOL FastFileSeek( HFASTFILE pfe, int off, int how );
extern long FastFileTell( HFASTFILE pfe );
extern LPVOID FastFileLock( HFASTFILE pfe, int off, int len );
extern BOOL FastFileUnlock( HFASTFILE pfe, int off, int len );
