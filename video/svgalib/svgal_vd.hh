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
/** \file
    Header for svgalib_display_class and embedded classes.
*/ 

#ifndef __SVGA_VD_HPP_
#define __SVGA_VD_HPP_

#include "device/event.hh" 
#include "video/display.hh"
#include "image/image8.hh"
#include "image/image32.hh"
#include "video/svgalib/svgalib_input.hh"

/**  Implements a full-screen software-rendered svgalib display. Keyboard and
 *   mouse management is done here, while the specifics of the devices and how
 *   they are translated into i4-ism's is controlled in svgalib_keyboard_class
 *   and svgalib_mouse_class.
 *
 *   svgalib_display_class renders through page-flipping (aka bank-switching)
 *
 *   @see i4_display_class
 *   \warning It doesn't work yet. Only the brave should proceed.
 */

class svgalib_display_class : public i4_display_class
{

  /** svgalib_input
   */
  i4_svgalib_input_class input;
  /** A node to be appended to a global i4_display_list to indicate that this 
      (svgalib) renderer is available. It is used only once in 
      svgalib_display_class::init()
  */
  i4_display_list_struct me;

  /** The palette for the mouse cursor. The graphics related to the
      mouse cursor have their own separate palettes, images,
      etc. Is this necessary with > 8bpp modes?
  */
  const i4_pal *mouse_pal;

  /** Offsets from the top-left of the mouse_image for the hot-spot.
      @see i4_cursor_class
      @see svgalib_display_class::set_mouse_shape()
   */
   i4_coord mouse_hot_x,mouse_hot_y;

  /** The actual coordinates of the mouse cursor on the screen. These
      get modified by the mouse_handler_class below. 

      @see svgalib_display_class::svgalib_mouse_notify
  */
   i4_coord mouse_x,mouse_y;

  /** The color of the mouse image which will not be drawn.
   */
  i4_color mouse_trans;
  
  /** The actual image of the mouse cursor. This is drawn during
      svgalib_display_class::flush() and is set during
      svgalib_display_class::set_mouse_shape()
   */
  i4_image_class *mouse_pict;    // generic image which will take the type of the screen when we copy the save portion

  /** The image behind the mouse cursor. When the mouse cursor is drawn, we
      first save the original image behind the cursor, then draw the mouse
      cursor, but keep the parts of the screen which correspond to the
      mouse_trans colors inside the mouse_image. 
  */
  i4_image_class  *mouse_save;

  /** Keeps track of dirty rectangles and changes to the screen. This is
      kindof like the queue for re-draw requests. When we need to redraw
      (in svgalib_display_class::flush() is called), we ask the context
      to calculate where the redrawing needs to occur. 
  */
  i4_draw_context_class *context;

  /** Holds the current graphics mode we are running. This should be 0
     when uninitialized, and any of the svga_modes[] listed in svgal_vd.cc.
     The call to vga_setmode() gets this variable as its argument.

     \warning This is not an i4-ism, it is one of the modes defined in
              vga.h. See vga_setmode(3).
  */
  int cur_svga_mode;

  /** Holds the status of our svgalib renderer
      @see svgalib_display_class::available()
  */
  enum { NOT_INITIALIZED, /**< We haven't even tried to set the graphics mode */
	 INITIALIZED_AND_NOT_AVAILABLE, /**< We tried to set the graphics mode, but we failed. */
	 INITIALIZED_AND_AVAILABLE /**< We tried to set the graphics mode, and it succeeded. */
	 } init_num;

  /** Our own little derived mode for use when another part of the program requires 
      information about this display's current mode. 
  */
   class svga_mode : public mode
  {
    public :
    i4_display_class *assoc;     // pointer to use, so we can confirm we created this mode
    w32 mode_num;          // for the display driver's use only
  } amode;

  /** Given an index into svga_modes[], fill out the member variable amode with
      the appropriate values.

      \param mode An index into svga_modes to fill out the data member amode's
                  values appropriately
  */
  void fill_amode(int mode);
  
public :

	/** Contains the image for the screen. It doesn't get any simpler than
		 that. This image is used to draw new contents onto the actual	
	    screen.
	*/
  i4_image_class *screen;
	
	/** Returns the width of the display's screen */
  virtual w16 width() const { return screen->width(); }

	/** Returns the height of the display's screen */
  virtual w16 height() const { return screen->height(); }

  // jhop: Added these func's. 29 Aug 1999
	/** Returns the data member screen. */
  virtual i4_image_class * get_screen() { return screen; }

	/** Returns the data member amode */
  virtual mode * current_mode() { return &amode; }

	/** Right now, this call doesn't do anything. This was copied
		 straight out of x11_display.hh

		\param type IGNORED
		\param access IGNORED
		 \warning FIXME: This call doesn't do anything
	*/
  virtual i4_image_class *lock_frame_buffer(i4_frame_buffer_type type,
                                            i4_frame_access_type access)
  {
    return screen; // jhop: lifted straight out of x11_display.hh
  }
	/** Right now, this call doesn't do anything. This was copied
		straight out of x11_display.hh 

		\param type IGNORED.
		\warning FIXME: This call doesn't do anything
	*/
  virtual void unlock_frame_buffer(i4_frame_buffer_type type) { ; }

	/** Returns I4_PAGE_FLIP_REFRESH. This tells the caller that this display
		should be treated as a page-flipper (or bank-switcher), not as an 
		area-BLT-er. Does that make sense?
		
		
	*/
  virtual i4_refresh_type update_model() { return I4_PAGE_FLIP_REFRESH; }

	/** Assigns a new cursor image for the mouse.

		\param cursor The new cursor to be drawn by the display
	*/
  virtual i4_bool set_mouse_shape(i4_cursor_class *cursor);

	/** return input.lock_mouse_in_place(yes_no);
	*/
  virtual i4_bool lock_mouse_in_place(i4_bool yes_no)
  {
    return input.lock_mouse_in_place(yes_no);
  }
	/** Forces a reconcilliation between the dirty lists inside the context
		and the screen. This forces any undrawn changes made to the screen
		to be drawn to the screen. The undrawn changes mentioned above are
		contained inside context. This function is probably the most important
		for the class.

	*/
  virtual void flush();

	/** Constructor that initializes data members. */
  svgalib_display_class();

	/** Returns a valid mode for the caller to attempt to use 
		 initialize_mode() with later on. This function call will
		 return NULL if 1) the user does not have permission to run
		 a fullscreen program. or 2) the call to vga_init fails. 

		It is also worth noting that the data member init_num
		will be changed based on the results of this function call.
		
		 \param driver_id IGNORED 
  	*/
  virtual mode *get_first_mode(int driver_id);

	/** Returns a new mode to be tried. The new mode is based on the
		 next value of the array in svga_modes[]. Returns NULL when
		 all possible graphical modes have been attempted. Also
		 returns NULL when last_mode is NULL.

		\param mode The last mode the caller attempted.
	*/
  virtual mode *get_next_mode(mode *last_mode);
  virtual mode *get_next_mode() { return 0; }

	/** Returns the data member context */
  virtual i4_draw_context_class *get_context() { return context; }

	/** 8 bit function call to place an i4_pal into the vga palette.
		 This function is not used. We keep it around because we may
		 need it if we decide to support 8bit rendering.

		\warning Is not used. 
	*/
  virtual i4_bool realize_palette(const i4_pal *pal_id);

	/** After a successful call to get_first_mode or get_next_mode, the
		 caller should call this function to attempt to initialize the graphics
		 mode.
	*/
  virtual i4_bool initialize_mode();

	/**  Cleans itself up. Duh :-)
	*/
  virtual i4_bool close();

	/** Appends the class to the global i4_display_list to indicate that
		 this display is available.
	*/
  void init();

	/** Returns the string "SVGALIB console dislplay" */
  char *name() { return "SVGALIB console display"; }

	/** Tests whether or not the display is available. Checks permissions on
		 the video device, and calls vga_init. Returns i4_T when the screen is
		 available for use, and returns i4_F when one of these fails. This
		 function sets the data member init_num to reflect in more detail
		 what happened during this call.
	*/
  i4_bool available();

	/** Destructor to clean up after itself. NOTE: This destructor just calls
		 svgalib_display_class::close()
	*/
  ~svgalib_display_class();
} ;

extern svgalib_display_class svgalib_display_instance;


#endif
