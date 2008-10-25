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

#include "video/display.hh"
#include "video/svgalib/svgal_vd.hh"
#include "image/image8.hh"
#include "device/kernel.hh"
#include "image/context.hh"
#include "palette/pal.hh"
#include <string.h>
#include <vga.h>
#include <vgagl.h>
#include <unistd.h>
#include <sys/io.h>
#include <stdlib.h>

svgalib_display_class svgalib_display_instance;

//  static void safety_fork_crash(void)
//  {
//    vga_setmode(TEXT);
//    abort();
//  }

svgalib_display_class::svgalib_display_class()
{
  init_num=NOT_INITIALIZED;
  screen=NULL;
  mouse_pict=mouse_save=NULL;
  context=0;
  pal = NULL;
}

svgalib_display_class::~svgalib_display_class()
{
  close();
}


i4_bool svgalib_display_class::set_mouse_shape(i4_cursor_class *cursor)
{
  if(mouse_pict)
    {
      delete mouse_pict;
      delete mouse_save;
    }

  mouse_trans = cursor->trans;
  mouse_pal = cursor->pict->get_pal();
  mouse_pict = cursor->pict->copy();
  mouse_save = i4_create_image(mouse_pict->width(), mouse_pict->height(),
			       screen->get_pal());
  mouse_hot_x = cursor->hot_x;
  mouse_hot_y = cursor->hot_y;
  return i4_T;
}



void svgalib_display_class::flush()   // the actual work of the function is in copy_part_to_vram
{
  int mw,mh;
  i4_coord rmx,rmy;
  mouse_x = input.mouse_x;
  mouse_y = input.mouse_y;
  sw32 mx=mouse_x, my=mouse_y;
  if (mx-mouse_x<0) mx=mouse_hot_x;
  if (my-mouse_y<0) my=mouse_hot_y;

  rmx=mx-mouse_hot_x;
  rmy=my-mouse_hot_y;

  if (mouse_pict)
  {
    mw=mouse_pict->width();
    mh=mouse_pict->height();

    // <jhop> 8 bit stuff. etc, etc.
     if (pal->source.pixel_depth==I4_8BIT)
       mouse_save->set_pal(pal);


    i4_draw_context_class save_context(0,0,mw-1,mh-1);
    screen->put_part(mouse_save,0,0,rmx,rmy,mx+mw-1,my+mh-1,
	save_context);	// save area behind mouse

    if (! input.mouse_locked ) {
      mouse_pict->put_image_trans(screen,rmx,rmy,mouse_trans,*context);
    }
  }

  i4_rect_list_class::area_iter a;
  for (a=context->single_dirty->list.begin();
       a!=context->single_dirty->list.end();
       ++a)
    context->both_dirty->add_area(a->x1, a->y1, a->x2, a->y2);

  context->single_dirty->delete_list();


  context->both_dirty->intersect_area(0,0,width()-1,height()-1);

  a=context->both_dirty->list.begin();
  i4_bool error=i4_F;
  for (;a!=context->both_dirty->list.end();++a)
    
	gl_putboxpart(a->x1,a->y1,(a->x2)-(a->x1)+1,(a->y2)-(a->y1)+1,
				 width(),height(),screen->data,a->x1,a->y1);
	
  if (!error)
    context->both_dirty->delete_list();

  if (mouse_pict)
    mouse_save->put_part(screen,rmx,rmy,0,0,mw-1,mh-1,*context);   // restore area behind mouse
  
}

// FIXME: 16bpp dependency
static int svga_modes[]={
 //  G320x200x64K,
  G640x480x64K,
  G800x600x64K,
  G1024x768x64K,
  -1
};

void svgalib_display_class::fill_amode(int mode)
{
  amode.red_mask =   63488;
  amode.green_mask = 2016;
  amode.blue_mask =  31;
 

  strcpy(amode.name, "Svgalib");
  amode.flags = mode::PAGE_FLIPPED;
  amode.mode_num=mode;
  amode.bits_per_pixel=16; // FIXME: 16bpp dependency.
  amode.assoc=this;
 
  

  vga_modeinfo *m=vga_getmodeinfo(svga_modes[mode]);

  amode.xres=m->width;
  amode.yres=m->height;
}


i4_display_class::mode *svgalib_display_class::get_first_mode(int driver_id)
{
  if (!available()) return NULL;

  fill_amode(0);
  return &amode;
}


i4_display_class::mode *svgalib_display_class::get_next_mode(mode *last_mode)
{
  if (!last_mode || ((svga_mode *)last_mode)->assoc!=this) return NULL;   // make sure we created the last mode
  if (svga_modes[((svga_mode *)last_mode)->mode_num+1]==-1) return NULL;     // any mode modes left?
  fill_amode(  ((svga_mode *)last_mode)->mode_num+1);
  return &amode;
}

  // initialize_mode need not call close() to switch to another mode
i4_bool svgalib_display_class::initialize_mode()
{
  if (amode.assoc!=this) return i4_F;

 //   vga_safety_fork(safety_fork_crash);
  if(input.open_console((w32)amode.xres, (w32)amode.yres) == i4_F)
    {
      return i4_F;
    }

  cur_svga_mode=svga_modes[amode.mode_num];
  if(vga_hasmode(cur_svga_mode)==0)
	{
		i4_warning("Failed vga_hasmode: %d\n",cur_svga_mode);
		return i4_F;
	}
 
  vga_setmode(cur_svga_mode);
  gl_setcontextvga(cur_svga_mode);


   if (!pal)          // palette has not been created yet
     {
       // <jhop> 8bit stuff. May need later if we decide to support
       // 8 bits.
       // w32 initial_pal[256];
//        int x;
//        for (x=0;x<256;x++)                       // initialize to a gray scale pal
// 	 initial_pal[x]=(x<<16)|(x<<8)|x;
//        format.lookup = initial_pal;
//        format.pixel_depth = I4_8BIT;
        i4_pixel_format f;
	f.red_mask = amode.red_mask;
	f.green_mask = amode.green_mask;
	f.blue_mask = amode.blue_mask;
	f.alpha_mask = 0;

	i4_warning("f.red_mask = %d  f.green_mask = %d   f.blue_mask =
%d\nf.alpha_mask = %d", f.red_mask, f.green_mask, f.blue_mask, f.alpha_mask);	
	f.calc_shift();
	
	f.lookup	  = 0;
	f.pixel_depth = I4_16BIT;

        pal=i4_pal_man.register_pal(&f);
     }

   // <jhop> 8 bit call to setup palette under svgalib
 //  realize_palette(pal);

  if (screen) 
    delete screen;

  screen= i4_create_image(amode.xres,amode.yres,pal);

   if (!mouse_pal)
   {
     // <jhop> 8bit stuff. May need later when or if we decide to support
     // 8 bits.
    //  i4_pixel_format mformat;
//      w32 mpal[256];
//      memset(mpal,0,sizeof(mpal));
//      mpal[0]=0;
//      mpal[1]=0xffffff;
//      mpal[2]=0x080808;
//      mformat.lookup = mpal;
//      mformat.pixel_depth = I4_8BIT;

     i4_pixel_format mf; // mouse_pal's pixel format
     mf.red_mask = amode.red_mask;
     mf.green_mask = amode.green_mask;
     mf.blue_mask = amode.blue_mask;
     mf.alpha_mask = 0;
     
     mf.calc_shift();
     
     mf.lookup	  = 0;
     mf.pixel_depth = I4_16BIT;

     mouse_pal=i4_pal_man.register_pal(&mf);
   } 

  if (mouse_pict)    // has the mouse already been initialized?
  {
    delete mouse_pict;  mouse_pict=NULL;
  }
  if(mouse_save)
    {
      delete mouse_save;  mouse_save=NULL;
    }

  if(context)
    delete context;

  context = new i4_draw_context_class(0,0,screen->width()-1,
				      screen->height()-1);
  context->both_dirty = new i4_rect_list_class;
  context->single_dirty = new i4_rect_list_class;


  return i4_T;
}

  // should be called before a program quits
i4_bool svgalib_display_class::close()
{
  if (screen) 
  {
    delete screen;
    screen=NULL;
  }

  if (mouse_pict)
  {
    delete mouse_pict;
    mouse_pict=NULL;
  }

  if (mouse_save)
  {
    delete mouse_save;
    mouse_save=NULL;
  }

  input.close_console();
  return i4_T;

}

i4_bool svgalib_display_class::available()
{
  if (init_num==NOT_INITIALIZED)
  {
    // FIXME: Linux specific call - keep an eye on
    if (ioperm(0x3b4, 0x3df - 0x3b4 + 1, 1)!=0)   // make sure we have permission to vga ports
      init_num=INITIALIZED_AND_NOT_AVAILABLE;
   //   else if (vga_init()==-1)
//        init_num=INITIALIZED_AND_NOT_AVAILABLE;
    else 
      init_num=INITIALIZED_AND_AVAILABLE;
  } 

  return (i4_bool)(init_num==INITIALIZED_AND_AVAILABLE);
}


// 8bit stuff. May need later if we decide to support 8 bits.
i4_bool svgalib_display_class::realize_palette(const i4_pal * pal_id)
{
  //!!? svgalib DOES DO > 8 bit color !!

  if (pal_id->source.pixel_depth == I4_8BIT)
  {
    // w32 *data=i4_pal_man.get_pal(pal_id);
    w32 *data = pal_id->source.lookup;
    for (int i=0;i<256;i++,data++)
      vga_setpalette(i,(((*data)>>18)&0x3f),
		       (((*data)>>10)&0x3f),
		       (((*data)>>2)&0x3f));
    pal=pal_id;
    if (screen)
      screen->set_pal(pal);
    return i4_T;
  } else return i4_F;
}

void svgalib_display_class::init()
{
  me.add_to_list("SVGALIB", 0, this, i4_display_list);
}
