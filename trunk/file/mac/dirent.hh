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
 

/****************************************************************************************
 *
 *  File:   dirent.h
 *  Purpose:  Implements UNIX-like directory reading for the Macintosh.
 *        This file describes Filesystem-independent directory information.
 *  Modifications:
 *
 ****************************************************************************************/

#ifndef __dirent_h
#define __dirent_h

#include <Files.h>
#include <Errors.h>
#include <Types.h>

struct  dirent {
  /* PRIVATE FIELDS.  Use fields after PUBLIC */
  struct dirent **next;
  FSSpec      fsp;
  
  /*  PUBLIC. */
  long      d_off;          /* index (to seekdir()) of this entry */  
  long      d_fileno;       /* File number (dirID) of this entry  */
#define d_parent  fsp.parID       /* File number (dirID) of parent  */
#define d_reclen  sizeof(struct dirent) /* Size of this record  */
#define d_namelen strlen(fsp.name)    /*  Length of the name  */
#define d_name    fsp.name        /*  Name  */
#define d_volume  fsp.vRefNum
};

#define DIRSIZ(dp) sizeof(struct dirent)

/*  Maximum path length for opendir() */
#define MAXPATHLEN  255

/*
 * Definitions for library routines operating on directories.
 */
typedef struct __dirdesc 
{
  /*  PRIVATE FIELDS.  Use the fields & defines below PUBLIC */
  FSSpec  dir_fsp;
  long  dd_off;   /* Current offset (ioWDIndex) in dir (for telldir) */
  int   dd_cached;  /* true if dd_cache_hint points to the next dir to be read  */

  struct dirent **dd_cache_hint;
  struct dirent **dd_buf; /* directory data buffer */

  /*  PUBLIC  */
  long  dd_fd;              /* file descriptor (dirID) of this dir  */

#define dd_parent dir_fsp.parID     /* dirID of parent  */
#define dd_bsize  1           /* amount of entries read at a time */
#define dd_size   sizeof(struct dirent) /* amount of valid data in buffer */
#define dd_loc    1
#define dd_name   dir_fsp.name
#define dd_volume dir_fsp.vRefNum

  long  dd_numents; /* Number of files/directories in this directory  */
} DIR;

/*  See dirent.c for descriptions of these routines */
extern  DIR *opendir(char *dirname);
extern  struct dirent *readdir(DIR *dirp);
extern  int closedir(DIR *dirp);
extern  void seekdir(DIR *dirp, long loc);
extern  long telldir(DIR *dirp);

#ifndef lint
  #define rewinddir(dirp) seekdir((dirp), (long)0)
#else
  extern  void rewinddir(DIR *dirp);
#endif

/*  Convenient routines */
extern char *getwd(char *path);
extern int  chdir(char *path);
extern char *pathdir(DIR *dirp, char *path);

/*  Any errors in above routines (and hopendir()) are put here  */
extern OSErr  dd_errno;
extern char   *dd_separator;  /*  If you're feeling brave, change this to "/" */
extern int    dd_xform_seps;

/*  In case you like errno instead  */
#ifdef UNCOMMENT_ME_IF_YOUVE_GOT_TO_HAVE_ERRNO
#define errno dd_errno
#endif

/*  This routine is Mac-specific, but very convenient in certain situations */
OSErr hgetwd(short vRefNum, long startDirID, char *path, int max_path_len, char *sep);

/*  You probably don't want to call this. */
extern  DIR *hopendir(char *dirname, short vRefNum, long dirID);

#endif  /* !__dirent_h */
