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
 

#ifdef DEBUG
#include "file/file.hh"

static int i4_dsound_check(HRESULT err)
//{{{
{
  if (err==DS_OK) return 1;
  
  i4_debug->printf("Direct Sound:");
  switch (err)
  {
    case DSERR_ALLOCATED:
      i4_warning(" The call failed because resources (such as a priority level)");
      i4_warning(" were already being used by another caller.");
      break;

    case DSERR_CONTROLUNAVAIL:
      i4_warning(" The control (vol,pan,etc.) requested by the caller is not available.");
      break;

    case DSERR_INVALIDPARAM:
      i4_warning(" An invalid parameter was passed to the returning function");
      break;

    case DSERR_INVALIDCALL:
      i4_warning(" This call is not valid for the current state of this object");
      break;

    case DSERR_GENERIC:
      i4_warning(" An undetermined error occured inside the DirectSound subsystem");
      break;

    case DSERR_PRIOLEVELNEEDED:
      i4_warning(" The caller does not have the priority level required for the function to");
      i4_warning(" succeed.");
      break;

    case DSERR_OUTOFMEMORY:
      i4_warning(" Not enough free memory is available to complete the operation");
      break;

    case DSERR_BADFORMAT:
      i4_warning(" The specified WAVE format is not supported");
      break;

    case DSERR_UNSUPPORTED:
      i4_warning(" The function called is not supported at this time");
      break;

    case DSERR_NODRIVER:
      i4_warning(" No sound driver is available for use");
      break;

    case DSERR_ALREADYINITIALIZED:
      i4_warning(" This object is already initialized");
      break;

    case DSERR_NOAGGREGATION:
      i4_warning(" This object does not support aggregation");
      break;

    case DSERR_BUFFERLOST:
      i4_warning(" The buffer memory has been lost, and must be restored.");
      break;

    case DSERR_OTHERAPPHASPRIO:
      i4_warning(" Another app has a higher priority level, preventing this call from");
      i4_warning(" succeeding.");
      break;

    case DSERR_UNINITIALIZED:
      i4_warning(" This object has not been initialized");
      break;

    case DSERR_NOINTERFACE:
      i4_warning(" The requested COM interface is not available");
      break;      
  }
  return 0;
}

#else

#define i4_dsound_check(x) ((x)==DS_OK)?(1):(0)

#endif
