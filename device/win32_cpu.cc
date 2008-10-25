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
 

#include "device/processor.hh"
#include <string.h>

w32 x86_can_do_cpuid()
{
  w32 result;

  _asm
  {
    pushfd                          //save EFLAGS
    
    pop  eax
    test eax,0x00200000   //check ID bit (bit 21)
    jz   set_21           //bit 21 is not set, so jump to set_21
    and  eax,0xffdfffff  //clear bit 21
    push eax            //save new value in register
    
    popfd                         //store new value in flags
    pushfd
    
    pop  eax
    test eax,0x00200000 //check ID bit
    
    jnz  cpu_id_not_ok      //if bit 21 isnt clear,then jump to cpu_id_not_ok
    
    mov  dword ptr [result],1 // return 1
    jmp  done

set_21:
    or   eax,0x00200000  //set bit 21
    push eax             //store new value
    
    popfd                          //store new value in EFLAGS
    pushfd
    
    pop  eax
    test eax,0x00200000  //if bit 21 is on
    jz   cpu_id_not_ok       //then jump to cpu_id_ok
    
    mov  dword ptr [result],1 // return 1
		jmp  done

cpu_id_not_ok:

    mov  dword ptr [result],0 //CPUID inst is not supported

done:
  }

  return result;
}

w32 x86_get_cpu_type()
{
  char name[32];

  _asm
  {
    mov eax,0
    
    __emit 0x0F //cpuid
    __emit 0xA2
    
    //store it
    mov byte ptr [name],bl
    mov byte ptr [name+1],bh
    
    ror ebx, 16

    mov byte ptr [name+2],bl
    mov byte ptr [name+3],bh
    mov byte ptr [name+4],dl
    mov byte ptr [name+5],dh
  
    ror edx,16
  
    mov byte ptr [name+6],dl
    mov byte ptr [name+7],dh
    mov byte ptr [name+8],cl
    mov byte ptr [name+9],ch

    ror ecx,16

    mov byte ptr [name+10],cl
    mov byte ptr [name+11],ch
    mov byte ptr [name+12],0
  }

  if (!strcmp(name,"AuthenticAMD") || !strcmp(name,"CentaurHauls"))
    return i4_cpu_info_struct::AMD_X86;
  else
  if (!strcmp(name,"GenuineIntel"))
    return i4_cpu_info_struct::INTEL_X86;
  else
    return i4_cpu_info_struct::UNKNOWN_X86;
}

w32 x86_get_cpu_flags(w32 cpu_type)
{
  unsigned int processor_sig;
  unsigned int extended_flags;

  _asm
  {
		 mov eax,0x80000001 //the cpuid function we're requesting
		 
     __emit 0x0F
     __emit 0xA2 //cpuid

     mov dword ptr [processor_sig],eax
     mov dword ptr [extended_flags],edx
  }
  
  //perhaps check the processor signature too?

  w32 flags = 0;

  if (cpu_type==i4_cpu_info_struct::AMD_X86)
  {
    if (extended_flags & (1<<4))
      flags |= i4_cpu_info_struct::RDTSC;

    if (extended_flags & (23<<31))
      flags |= i4_cpu_info_struct::MMX;

    if (extended_flags & (1<<31))
      flags |= i4_cpu_info_struct::AMD3D;
  }
  else
  if (cpu_type==i4_cpu_info_struct::INTEL_X86)
  {
    if (extended_flags & (1<<4))
      flags |= i4_cpu_info_struct::RDTSC;

    /*
    if (extended_flags & (23<<31))
      flags |= i4_cpu_info_struct::MMX;

    if (extended_flags & (1<<31))
      flags |= i4_cpu_info_struct::AMD3D;
    */
  }
    
  return flags;
}

void i4_win32_get_cpu_info(i4_cpu_info_struct *s)
{
  _asm pusha

  if (!x86_can_do_cpuid())
  {
    s->cpu_type  = i4_cpu_info_struct::UNKNOWN_X86;
    s->cpu_flags = 0;
  }
  else
  {
    s->cpu_type  = x86_get_cpu_type();
    s->cpu_flags = x86_get_cpu_flags(s->cpu_type);
  }
  _asm popa
}
