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
// glX routines for initialization of the OpenGL display

#ifndef GOLG_X11_OPENGL
#define GOLG_X11_OPENGL

#include "video/opengl/opengl_display.hh"
#include <GL/glx.h>
#include "video/x11/x11_input.hh"

int glx_attribs[] = { GLX_RGBA, 
					  GLX_DOUBLEBUFFER,
					  GLX_AUX_BUFFERS, 0,
					  GLX_DEPTH_SIZE, 16,
					  GLX_STENCIL_SIZE, 0,
					  GLX_ACCUM_RED_SIZE, 0,
					  GLX_ACCUM_BLUE_SIZE, 0,
					  GLX_ACCUM_GREEN_SIZE, 0,
					  GLX_ACCUM_ALPHA_SIZE, 0,
					  None
};

class i4_x11_opengl_display_class : public i4_opengl_display_class
{

private:

  XVisualInfo *find_visual();
  XVisualInfo *the_visual;
  XVisualInfo *visual();
  GLXContext glx_cx;
  void setup_modes();

protected:
  virtual void swap_buffers();

public:
  x11_input_class input;

  i4_x11_opengl_display_class() {
	the_visual = 0;
	glx_cx = 0;
  }

  virtual void init();
  virtual i4_bool close();

  virtual i4_device_class *local_devices() { return &input; }
  virtual void destroy_window() { input.destroy_window(); }

  virtual i4_bool create_window(w32 xres, w32 yres)
  {
	return input.create_window(0,0,xres,yres,this,i4_F,visual());
  }

  virtual i4_bool lock_mouse_in_place(i4_bool yes_no)
  {
    return input.lock_mouse_in_place(yes_no);
  }

  virtual char *name() { return "OpenGL (glX) display"; }

  virtual void get_mouse_pos(sw32 &mouse_x, sw32 &mouse_y)
  {
    mouse_x = input.mouse_x;
    mouse_y = input.mouse_y;
	mouse_y = mouse_y - 2 * ( mouse_y - height()/2 );
  }

  virtual i4_bool initialize_mode(mode *m);

};

i4_bool i4_x11_opengl_display_class::initialize_mode(mode *m) {

  // this sets up the window for us
  if (!i4_opengl_display_class::initialize_mode(m))
	return i4_F;

  glXMakeCurrent(input.display,input.mainwin,glx_cx);

  return i4_T;
}

void i4_x11_opengl_display_class::init() {
  int errbase, eventbase;

  // get the input handler to open X connection
  if (!input.display) {
	if (!input.open_display()) {
	  i4_error("X11 OpenGL renderer: could not convince input handler to open display");
	  return;
	}
  }

  if (!glXQueryExtension(input.display,&errbase,&eventbase)) {
	i4_error("glX extension unavailable");
	return;
  }

  glx_cx = glXCreateContext(input.display, visual(), NULL, True);
  if (!glx_cx) {
	i4_error("could not create glX rendering context");
	return;
  }

  setup_modes();

  i4_opengl_display_class::init();
}

void i4_x11_opengl_display_class::setup_modes()
{
  if (!input.display) // should have been opened already
	return;

  XVisualInfo *v = visual();
  if (!v)
	return;

  int xres[] = { 640 };
  int yres[] = { 480 };
  n_modes = sizeof(xres)/sizeof(int);
  modes = new mode[n_modes];

  for (int i=0; i<n_modes; i++) {

	modes[i].bits_per_pixel = v->depth;
	modes[i].red_mask =   v->red_mask;
	modes[i].green_mask = v->green_mask;
	modes[i].blue_mask =  v->blue_mask;
								   
	modes[i].xres = xres[i];
	modes[i].yres = yres[i];
	sprintf(modes[i].name, "glX Window: %dx%x, %ud bpp",xres[i], yres[i], v->depth);
  }

}

// For now we'll look for visual on DefaultScreen(), this should be changed later.
XVisualInfo *i4_x11_opengl_display_class::find_visual() {

  XVisualInfo *v;
  v = glXChooseVisual(input.display, DefaultScreen(input.display), glx_attribs);
  if (!v) {
	i4_alert("X11 OpenGL renderer: no visual found with attribute list\n",100,NULL);
	return NULL;
  }

  return v;
}

XVisualInfo *i4_x11_opengl_display_class::visual() {
  if (!the_visual)
	the_visual = find_visual();

  return the_visual;
}

void i4_x11_opengl_display_class::swap_buffers() {
  glXSwapBuffers(input.display, input.mainwin);
}

i4_bool i4_x11_opengl_display_class::close() {
  if (glx_cx && input.display)
	glXDestroyContext(input.display,glx_cx);
  input.close_display();
  return i4_opengl_display_class::close();
}

i4_x11_opengl_display_class i4_x11_opengl_display_instance;

#endif // GOLG_X11_OPENGL
