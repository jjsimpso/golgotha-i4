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

#include "video/x11/x11_display.hh"
#include "video/x11/x11_input.hh"
#include "image/context.hh"

// declare i4_global_arg[cv]
#include "string/string.hh"
#include "main/main.hh"

#define DEPTH 16

// <Gilley> 10.11.98  tried X11 soft on 8 bit color machine and got an
//                    empty window

x11_display_class x11_display_instance;


x11_display_class::x11_display_class()
{
  mouse_save=screen=0;
  context=0;
  shm_extension = create_x11_shm_extension_class();
  shm_image=0;
  ximage=0;
}



void x11_display_input_class::resize(int w, int h)
{
  x11_display_class *d=(x11_display_class *)i4_display;
  if (w!=d->width() || h!=d->height())
  {
    d->destroy_X_image();
    d->create_X_image(w,h);
  }
}

void x11_display_input_class::note_event(XEvent &xev)
{
  x11_display_class *d=(x11_display_class *)i4_display;
  if (d->shm_extension)
    d->shm_extension->note_event(xev);
}


#if 0
/* digulla 4.11.1998
    This code doesn't compile. screen->put_part needs another parameter
    of class context. How is such a context created ?
*/
/* phooky 5.11.1998
   This code isn't actually used anywhere.  It's cruft.  Axe it.
*/
i4_image_class *x11_display_class::get_back_buffer(int x1, int y1, int x2, int y2)
{
  if (x2<x1 || y2<y1) return 0;

  i4_image_class *im=i4_create_image(x2-x1+1, y2-y1+1, screen->pal);
  screen->put_part(im, 0,0, x1,y1,x2,y2);
  return im;
}
#endif /* Code doesn't compile */

i4_bool x11_display_class::open_X_window(w32 width, w32 height, i4_display_class::mode *mode)
{
  if (input.create_window(0,0,width,height, this, i4_F, get_visual(input.display)))
  {
    i4_pixel_format f;
    f.red_mask	 = mode->red_mask;
    f.green_mask = mode->green_mask;
    f.blue_mask  = mode->blue_mask;
    f.alpha_mask = 0;

    f.calc_shift();

    f.lookup	  = 0;

    switch(default_depth){
    case 8:
      f.pixel_depth = I4_8BIT;
      break;
    case 16:
      f.pixel_depth = I4_16BIT;
      break;
    default:
      f.pixel_depth = I4_32BIT;
    }

    pal = i4_pal_man.register_pal(&f);

    if (shm_extension)
    {
      char *ds_name=getenv("DISPLAY");
      if (!ds_name)
	ds_name="unix:0.0";
      w32 i;
      for (i=1; i<i4_global_argc; i++)
	{
	  if (i4_global_argv[i] == "-nomitshm")
	    {
	      i4_warning("x11_display_class::open_X_window() - MITSHM explicitly disabled");
	      shm_extension = 0;
	    }
	}

      if (shm_extension)
	{
	  i4_warning("looking for MITSHM extension... ");
	  if (!shm_extension->available(input.display,ds_name)) {
	    i4_warning(" MITSHM extension not available on this display.");
	    shm_extension=0;
	  } else
	    i4_warning(" MITSHM found. ");
	}
    }

    create_X_image(width, height);
    return i4_T;
  }
  else
    return i4_F;
}



void x11_display_class::close_X_window()
{
  destroy_X_image();
  if (shm_extension)
    shm_extension->shutdown(input.display);


  if (mouse_save)
  {
    delete mouse_save;
    mouse_save=0;
  }

  if (mouse_pict)
  {
    delete mouse_pict;
    mouse_pict=0;
  }
}


i4_bool x11_display_class::close()
{
  if (screen)
  {
    XAutoRepeatOn(input.display);
    close_X_window();
  }

  return i4_T;
}

void x11_display_class::init()
{
  if (input.display || input.open_display())
  {
    default_depth = XDefaultDepth(input.display, XDefaultScreen(input.display));
    if(default_depth == 24) default_depth = 32;
    me.add_to_list("X Windows", 0, this, i4_display_list);
    input.close_display();
  }

  printf("default_depth = %d\n", default_depth);
}

  // initialize_mode need not call close() to switch to another mode
i4_bool x11_display_class::initialize_mode()
{
  memcpy(&cur_mode, &amode, sizeof(cur_mode));

  // this should open an X window
  return open_X_window(cur_mode.xres, cur_mode.yres, &cur_mode);
}


XVisualInfo *x11_display_class::get_visual(Display *display)
{
#if 0
  return input.find_visual_with_depth(DEPTH);
#else
  return input.find_visual_with_depth(default_depth);
#endif
}

i4_display_class::mode *x11_display_class::get_first_mode(int driver_id)
{
  if (!input.open_display())
    return 0;
  else
  {
    XVisualInfo *v = get_visual(input.display);
    if (v)
    {
      strcpy(amode.name,"Standard X11 window");
      amode.flags=mode::RESOLUTION_DETERMINED_ON_OPEN;
      amode.bits_per_pixel=default_depth;

      amode.red_mask	= v->red_mask;
      amode.green_mask	= v->green_mask;
      amode.blue_mask	= v->blue_mask;
      XFree((char *)v);

      Window root;
      int x,y;
      unsigned w,h,bord,depth;
      if (XGetGeometry(input.display,
		       RootWindow(input.display,DefaultScreen(input.display)),&root,
		       &x,&y,&w,&h,&bord,&depth)==0)
	i4_error("can't get root window attributes");

      //i4_error("root window depth = %d\n", depth);
      amode.xres=w;
      amode.yres=h;

      amode.assoc=this; 	 // so we know in 'initialize_mode' that we created this mode
      return &amode;
    }
    return 0;
  }
}





void x11_display_class::destroy_X_image()
{
  if (shm_extension)
  {
    if (shm_image)
      shm_extension->destroy_shm_image(input.display, shm_image);
    shm_image=0;
  }
  else
  {
    if (ximage)
      XDestroyImage(ximage);
    ximage=0;
  }
  if (screen)
  {
    delete screen;
    screen=0;
  }

  if (context)
  {
    delete context;
    context=0;
  }
}

void x11_display_class::create_X_image(w32 width, w32 height)
{
  destroy_X_image();

  if (shm_extension)
  {
    w16 w=width,h=height;
    shm_image=shm_extension->create_shm_image(input.display,
					      input.mainwin,
					      input.gc,
					      input.my_visual->visual,
					      input.my_visual->depth,
					      w,h);   // actual width and height from X
    screen=i4_create_image(w,h,pal,
			   (w8 *)shm_image->data,
			   w*(default_depth/8));
  }
  else
  {
    ximage = XCreateImage(input.display,
			  input.my_visual->visual,
			  input.my_visual->depth,
			  ZPixmap,
			  0,
			  (char *)malloc(width*height*((default_depth+7)/8)),
			  width,
			  height,
			  32,
			  0 );

    screen=i4_create_image(width, height, pal,
			   (w8 *)ximage->data,
			   width*(default_depth/8));            // bytes per line

  }

  if (context)
    delete context;

  context=new i4_draw_context_class(0,0,screen->width()-1,screen->height()-1);
  context->both_dirty=new i4_rect_list_class;
  context->single_dirty=new i4_rect_list_class;
}


void x11_display_class::flush()   // the actual work of the function is in copy_part_to_vram
{
  int mw=0, mh=0;
  i4_coord rmx,rmy;
  sw32 mx=input.mouse_x, my=input.mouse_y;
  if (mx-mouse_hot_x<0) mx=mouse_hot_x;
  if (my-mouse_hot_y<0) my=mouse_hot_y;

  rmx=mx-mouse_hot_x;
  rmy=my-mouse_hot_y;

  if (mouse_pict)
  {
    mw=mouse_pict->width();
    mh=mouse_pict->height();

    if (pal->source.pixel_depth==I4_8BIT)
      mouse_save->set_pal(pal);


    i4_draw_context_class save_context(0,0,mw-1,mh-1);
    screen->put_part(mouse_save,0,0,rmx,rmy,mx+mw-1,my+mh-1,
	save_context);	// save area behind mouse

    if (! input.mouse_locked )
      mouse_pict->put_image_trans(screen,rmx,rmy,mouse_trans,*context);
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
    error=(i4_bool)(error & copy_part_to_vram(a->x1,a->y1,a->x1,a->y1,a->x2,a->y2));

  if (!error)
    context->both_dirty->delete_list();

  if (mouse_pict)
    mouse_save->put_part(screen,rmx,rmy,0,0,mw-1,mh-1,*context);   // restore area behind mouse


}


i4_bool x11_display_class::copy_part_to_vram(i4_coord x, i4_coord y,
					     i4_coord x1, i4_coord y1,
					     i4_coord x2, i4_coord y2)
// this should copy a portion of an image to the actual screen at offset x, y
{
  if (shm_image)
    return shm_image->copy_part_to_vram(shm_extension,x,y,x1,y1,x2,y2);
  else
  {
    XPutImage(input.display, input.mainwin, input.gc, ximage,x1,y1,x,y,x2-x1+1,y2-y1+1);
    return i4_T;
  }
}


i4_bool x11_display_class::set_mouse_shape(i4_cursor_class *cursor)
{
  if (mouse_pict)
  {
    delete mouse_pict;
    delete mouse_save;
  }

  mouse_trans=cursor->trans;
  mouse_pict=cursor->pict->copy();

  mouse_save=i4_create_image(mouse_pict->width(),mouse_pict->height(),screen->get_pal());

  mouse_hot_x=cursor->hot_x;
  mouse_hot_y=cursor->hot_y;
  return i4_T;
}


