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
/*---------------------------------------------------------------------
 *
 * ia3d.h
 *
 *---------------------------------------------------------------------
 *
 * $Id: ia3d.h,v 1.3 1999/09/03 05:55:40 rob Exp $
 *
 *---------------------------------------------------------------------
 *
 * ia3d header file.  It's the part the outside world needs to see.
 *
 *---------------------------------------------------------------------
 *
 * AUREAL SEMICONDUCTOR, INC. PROPRIETARY AND CONFIDENTIAL
 * Copyright (c) 1996 Aureal Semiconductor, Inc. - All rights 
 * reserved. 
 *
 *---------------------------------------------------------------------
 */

/*
 *
 * $Log: ia3d.h,v $
 * Revision 1.3  1999/09/03 05:55:40  rob
 * * dsound: cleaned up
 *
 * Revision 1.2  1999/09/03 04:02:32  rob
 *
 * * Added License.txt to all source.  It should be added to all new files.
 *
 * Revision 1.1.1.1  1998/10/29 01:28:48  dereks
 * Adding the modules
 *
 * Revision 1.1  1997/05/29 20:02:59  trey
 * aureal header file
 *
 * 
 * 9     1/17/97 12:51p Ag
 * took out setdefaulthfabsorb
 * 
 * 8     1/15/97 6:01p Ag
 * added hf absorb functions
 *  plus C interface defines
 * 
 * 
 * 7     1/15/97 5:55p Ag
 * added hf absorb functions
 * 
 * 
 * 6     1/14/97 5:55p Pradek
 * Swapped values for OUTPUT_SPEAKER_WIDE and OUTPUT_SPEAKER_NARROW
 * 
 * 5     1/13/97 2:04p Pradek
 * Updated 'C' interface defines
 * Added A3D_OK value.
 * 
 * 4     1/05/97 5:34p Pradek
 * Added defines for Resource Management Modes
 * 
 * 3     12/30/96 2:36p Mike
 * Changed set/get output.
 * Added Resource Manager API template
 * 
 * 2     11/12/96 12:19a Pradek
 * 
 * 1     10/30/96 4:11p Pradek
 * 
 * 1     10/30/96 4:10p Pradek
 * 
 * 1     10/28/96 1:35a Pradek
 * Shared include files
 * Revision 1.1  1996/09/02  10:50:35  mike
 * Initial revision
 *
 *
 */

#ifndef _IA3D_H_
#define _IA3D_H_



#ifdef __cplusplus
extern "C" {
#endif


#define DEFINE_A3D_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        EXTERN_C const GUID CDECL name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

// A3d Class ID! {D8F1EEE0-F634-11cf-8700-00A0245D918B}
DEFINE_A3D_GUID(CLSID_A3d, 
0xd8f1eee0, 0xf634, 0x11cf, 0x87, 0x0, 0x0, 0xa0, 0x24, 0x5d, 0x91, 0x8b);

// A3d Interface ID! {D8F1EEE1-F634-11cf-8700-00A0245D918B}
DEFINE_A3D_GUID(IID_IA3d,
0xd8f1eee1, 0xf634, 0x11cf, 0x87, 0x0, 0x0, 0xa0, 0x24, 0x5d, 0x91, 0x8b);


// Bits for manipulating output modes

// Values for bOutputMode
#define OUTPUT_MODE_STEREO	0x00000001
#define OUTPUT_MODE_QUAD	0x00000002

// Values for FrontXtalkMode and bRearXtalkMode
#define OUTPUT_HEADPHONES		0x00000001    // headphones
#define OUTPUT_SPEAKERS_WIDE    0x00000002
#define OUTPUT_SPEAKERS_NARROW	0x00000003

// Values for Resource Management Mode
#define A3D_RESOURCE_MODE_OFF		0x00000000
#define A3D_RESOURCE_MODE_NOTIFY	0x00000001
#define A3D_RESOURCE_MODE_DYNAMIC	0x00000002

// Declare the IA3d Interface.  It's not very complex at all.

#undef INTERFACE
#define INTERFACE IA3d

typedef struct IA3d *LPIA3D;

DECLARE_INTERFACE_(IA3d, IUnknown)
{
    // IUnknown 
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // IA3d
    STDMETHOD(SetOutputMode)(THIS_ DWORD    dwFrontXtalkMode, DWORD    dwBackXtalkMode, DWORD    dwQuadMode) PURE;
    STDMETHOD(GetOutputMode)(THIS_ DWORD *lpdwFrontXtalkMode, DWORD *lpdwBackXtalkMode, DWORD *lpdwQuadMode) PURE;

	STDMETHOD(SetResourceManagerMode) (THIS_ DWORD  ) PURE;
	STDMETHOD(GetResourceManagerMode) (THIS_ DWORD *) PURE;

	STDMETHOD(SetHFAbsorbFactor)(THIS_ FLOAT  ) PURE;
    STDMETHOD(GetHFAbsorbFactor)(THIS_ FLOAT *) PURE;

};




// The library function that gets things going.  It returns an interface
// pointer to DirectSound.

#define A3D_OK			1	// A3dCreate returns this upon detection of A3D enabled hardware.

_declspec (dllexport) HRESULT WINAPI
A3dCreate(const GUID * lpGUID, LPDIRECTSOUND * ppDS, IUnknown FAR *pUnkOuter );


// Usefull Macros for C folks.

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IA3d_QueryInterface(p,a,b)			(p)->lpVtbl->QueryInterface(p,a,b)
#define IA3d_AddRef(p)						(p)->lpVtbl->AddRef(p)
#define IA3d_Release(p)						(p)->lpVtbl->Release(p)
#define IA3d_SetOutputMode(p,a,b,c)			(p)->lpVtbl->SetOutputMode(p,a,b,c)
#define IA3d_GetOutputMode(p,a,b,c)			(p)->lpVtbl->GetOutputMode(p,a,b,c)
#define IA3d_SetResourceManagerMode(p,a)	(p)->lpVtbl->SetResourceManagerMode(p,a)
#define IA3d_GetResourceManagerMode(p,a)	(p)->lpVtbl->GetResourceManagerMode(p,a)
#define IA3d_SetHFAbsorbFactor(p,a)			(p)->lpVtbl->SetHFAbsorbFactor(p,a)
#define IA3d_GetHFAbsorbFactor(p,a)			(p)->lpVtbl->GetHFAbsorbFactor(p,a)

    
#else										
#define IA3d_QueryInterface(p,a,b)			(p)->QueryInterface(a,b)
#define IA3d_AddRef(p)						(p)->AddRef()
#define IA3d_Release(p)						(p)->Release()
#define IA3d_SetOutputMode(p,a,b,c)			(p)->SetOutputMode(a,b,c)
#define IA3d_GetOutputMode(p,a,b,c)			(p)->GetOutputMode(a,b,c)
#define IA3d_SetResourceManagerMode(p,a)	(p)->lpVtbl->SetResourceManagerMode(a)
#define IA3d_GetResourceManagerMode(p,a)	(p)->lpVtbl->GetResourceManagerMode(a)
#define IA3d_SetHFAbsorbFactor(p,a)			(p)->lpVtbl->SetHFAbsorbFactor(a)
#define IA3d_GetHFAbsorbFactor(p,a)			(p)->lpVtbl->GetHFAbsorbFactor(a)

#endif



#ifdef __cplusplus
};
#endif

				  

#endif // _IA3D_H_
