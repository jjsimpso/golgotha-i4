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

#include "video/svgalib/svgalib_input.hh"
#include "device/event.hh"
#include "device/keys.hh"
#include "device/kernel.hh"
#include <vga.h>
#include <vgakeyboard.h>
#include <vgamouse.h>


static i4_svgalib_input_class *input = NULL; // used by callback wrappers


static void mousehandler_wrapper(int buttonstate, int  dx,  int dy,  int dz , int drx, int dry, int drz)
{
  if (input)
    input->mousehandler(buttonstate, dx, dy, dz, drz, dry, drz);
}

  
void i4_svgalib_input_class::mousehandler(int buttonstate, int dx, int dy, int dz, int drx, int dry, int drz)
{

  mouse_buttons = buttonstate;

  new_mouse_x += sw32(dx/mouse_scale);
  new_mouse_y += sw32(dy/mouse_scale);

}


i4_svgalib_input_class::i4_svgalib_input_class() {
  console_opened = i4_F;
  use_mouse = i4_T;
  mouse_x = new_mouse_x = mouse_y = new_mouse_y = 0;
  mouse_buttons = old_mouse_buttons = 0;
  mouse_scale = 10.0;
  mouse_locked = i4_F;

  scancode_press_state = NULL;
  scancode_map = NULL;
  input = NULL;
}


i4_svgalib_input_class::~i4_svgalib_input_class() {
  close_console();
}


i4_bool i4_svgalib_input_class::open_console(w32 w, w32 h)
{
  width = w;
  height = h;

  if (console_opened)
    return i4_F;

  if (vga_init()) {
    i4_error("svgalib_input_class::open_console() - vga_init failed");
    return i4_F;
  }

  if (keyboard_init()) {
    i4_error("svgalib_input_class::open_console() - keyboard_init failed");
    return i4_F;
  }

  input = this;

  // setup mouse
  int mtype = vga_getmousetype();
  char *mousedev;
  if (! (mousedev = getenv("I4_SVGALIB_MOUSEDEVICE")))
    mousedev = "/dev/mouse";
  int mouserate = MOUSE_DEFAULTSAMPLERATE;
  if (mouse_init(mousedev,mtype,mouserate)) {
    i4_warning("svgalib_input_class::open_console() - could not initialize mouse");
    use_mouse = i4_F;
  }
  else {
    mouse_seteventhandler(mousehandler_wrapper);
    use_mouse = i4_T;
  }
    
  keyboard_clearstate();
  get_scancode_info();   // sets max_scancode
  create_scancode_map(); // allocates the map, initializes it
  create_scancode_press_state(); // allocates the state array, initializes it
  modifier_state = 0;

  console_opened = i4_T;

  i4_kernel.add_device(this);

  return i4_T;
}


void i4_svgalib_input_class::close_console()
{
  if (console_opened) {
    keyboard_close();
    if (use_mouse)
      mouse_close();
    vga_setmode(TEXT); // puts us back in the console from whence we came
    console_opened = i4_F;
    input = NULL;
  }

  if (scancode_map)
    free(scancode_map);

  if (scancode_press_state)
    free(scancode_press_state);

}


i4_bool i4_svgalib_input_class::process_events()
{

  /*
   * start keyboard
   */
  while (keyboard_update()) { ; }

  char *state = keyboard_getstate();

  for (unsigned int code=0; code<max_scancode+1; code++) {

    // this key's state has not changed
    if (state[code] == scancode_press_state[code])
      continue;
    scancode_press_state[code] = state[code];

    // no mapping for this scancode
    if (scancode_map[code] == I4_NO_KEY) {
      i4_warning("svgalib_input_class::process_events() - unhandled scancode = %u",
		 (unsigned int) code);
      continue;
    }

    if (state[code] == KEY_PRESSED) {
      switch (code) {
      case SCANCODE_LEFTSHIFT:    modifier_state |= I4_MODIFIER_SHIFT_L;    break;
      case SCANCODE_RIGHTSHIFT:   modifier_state |= I4_MODIFIER_SHIFT_R;    break;
      case SCANCODE_LEFTALT:      modifier_state |= I4_MODIFIER_ALT_L;      break;
      case SCANCODE_RIGHTALT:     modifier_state |= I4_MODIFIER_ALT_R;      break;
      case SCANCODE_LEFTCONTROL:  modifier_state |= I4_MODIFIER_CTRL_L;     break;
      case SCANCODE_RIGHTCONTROL: modifier_state |= I4_MODIFIER_CTRL_R;     break;
      case SCANCODE_CAPSLOCK:     modifier_state |= I4_MODIFIER_CAPS;       break;
      case SCANCODE_NUMLOCK:      modifier_state |= I4_MODIFIER_NUMLOCK;    break;
      default: break;
      }

      w16 key = i4_key_translate(scancode_map[code], 1, modifier_state);
      i4_time_class now;
      i4_key_press_event_class ev(key, scancode_map[code], modifier_state, now);
      send_event_to_agents(&ev, FLAG_KEY_PRESS);

    }
    else {
      switch (code) {
      case SCANCODE_LEFTSHIFT:    modifier_state &= ~I4_MODIFIER_SHIFT_L;    break;
      case SCANCODE_RIGHTSHIFT:   modifier_state &= ~I4_MODIFIER_SHIFT_R;    break;
      case SCANCODE_LEFTALT:      modifier_state &= ~I4_MODIFIER_ALT_L;      break;
      case SCANCODE_RIGHTALT:     modifier_state &= ~I4_MODIFIER_ALT_R;      break;
      case SCANCODE_LEFTCONTROL:  modifier_state &= ~I4_MODIFIER_CTRL_L;     break;
      case SCANCODE_RIGHTCONTROL: modifier_state &= ~I4_MODIFIER_CTRL_R;     break;
      case SCANCODE_CAPSLOCK:     modifier_state &= ~I4_MODIFIER_CAPS;       break;
      case SCANCODE_NUMLOCK:      modifier_state &= ~I4_MODIFIER_NUMLOCK;    break;
      default: break;
      }

      w16 key = i4_key_translate(scancode_map[code], 0, modifier_state);
      i4_time_class now;
      i4_key_release_event_class ev(key, scancode_map[code], modifier_state, now);
      send_event_to_agents(&ev, FLAG_KEY_RELEASE);
    }

  }
  /*
   * finished keyboard
   */


  /*
   * start mouse
   */
  if (use_mouse) {
    while (mouse_update()) { ; }

    // did mouse move?
    if (new_mouse_x != mouse_x || new_mouse_y != mouse_y) {

      i4_mouse_move_event_class move(mouse_x, mouse_y, new_mouse_x, new_mouse_y);
      send_event_to_agents(&move,FLAG_MOUSE_MOVE);
    }

    // button states changed?
    if (old_mouse_buttons != mouse_buttons) {

      int diffs = mouse_buttons ^ old_mouse_buttons;

      i4_mouse_button_event_class::btype but=i4_mouse_button_event_class::LEFT;

      i4_time_class now;

      if (diffs & MOUSE_LEFTBUTTON) {
	but=i4_mouse_button_event_class::LEFT;
	if (mouse_buttons & MOUSE_LEFTBUTTON) {
	  i4_mouse_button_down_event_class down(but, new_mouse_x, new_mouse_y,
					      now, last_down[but]);
	  send_event_to_agents(&down,FLAG_MOUSE_BUTTON_DOWN);
	  last_down[but] = now;
	}
	else {
	  i4_mouse_button_up_event_class up(but, new_mouse_x, new_mouse_y,
					    now, last_up[but]);
	  send_event_to_agents(&up,FLAG_MOUSE_BUTTON_UP);
	  last_up[but] = now;
	}
      }

      if (diffs & MOUSE_RIGHTBUTTON) {
	but=i4_mouse_button_event_class::RIGHT;
	if (mouse_buttons & MOUSE_RIGHTBUTTON) {
	  i4_mouse_button_down_event_class down(but, new_mouse_x, new_mouse_y,
						now, last_down[but]);
	  send_event_to_agents(&down,FLAG_MOUSE_BUTTON_DOWN);
	  last_down[but] = now;
	}
	else {
	  i4_mouse_button_up_event_class up(but, new_mouse_x, new_mouse_y,
					    now, last_up[but]);
	  send_event_to_agents(&up,FLAG_MOUSE_BUTTON_UP);
	  last_up[but] = now;
	}
      }

      if (diffs & MOUSE_MIDDLEBUTTON) {
	but=i4_mouse_button_event_class::CENTER;
	if (mouse_buttons & MOUSE_MIDDLEBUTTON) {
	  i4_mouse_button_down_event_class down(but, new_mouse_x, new_mouse_y,
						now, last_down[but]);
	  send_event_to_agents(&down,FLAG_MOUSE_BUTTON_DOWN);
	  last_down[but] = now;
	}
	else {
	  i4_mouse_button_up_event_class up(but, new_mouse_x, new_mouse_y,
					    now, last_up[but]);
	  send_event_to_agents(&up,FLAG_MOUSE_BUTTON_UP);
	  last_up[but] = now;
	}
      }
    }

    if (!mouse_locked) {
      mouse_x = new_mouse_x;
      mouse_y = new_mouse_y;
    }
    if (mouse_x < 0) mouse_x = 0;
    if (mouse_x >= (sw32)width) mouse_x = width-1;
    if (mouse_y < 0) mouse_y = 0;
    if (mouse_y >= (sw32)height) mouse_y = height-1;

    new_mouse_x = mouse_x;
    new_mouse_y = mouse_y;

    old_mouse_buttons = mouse_buttons;

  }
  /*
   * finished mouse
   */

  return i4_F;
}


void i4_svgalib_input_class::create_scancode_map()
{
  scancode_map = (w16 *)malloc(sizeof(w16) * (max_scancode + 1));

  // initialize map to no key
  for (unsigned int i=0; i<max_scancode+1; i++)
    scancode_map[i] = I4_NO_KEY;

  scancode_map[SCANCODE_0] =              '0';
  scancode_map[SCANCODE_1] =              '1';
  scancode_map[SCANCODE_2] =              '2';
  scancode_map[SCANCODE_3] =              '3';
  scancode_map[SCANCODE_4] =              '4';
  scancode_map[SCANCODE_5] =              '5';
  scancode_map[SCANCODE_6] =              '6';
  scancode_map[SCANCODE_7] =              '7';
  scancode_map[SCANCODE_8] =              '8';
  scancode_map[SCANCODE_9] =              '9';
  scancode_map[SCANCODE_KEYPAD0] =        I4_KP0;
  scancode_map[SCANCODE_KEYPAD1] =        I4_KP1;
  scancode_map[SCANCODE_KEYPAD2] =        I4_KP2;
  scancode_map[SCANCODE_KEYPAD3] =        I4_KP3;
  scancode_map[SCANCODE_KEYPAD4] =        I4_KP4;
  scancode_map[SCANCODE_KEYPAD5] =        I4_KP5;
  scancode_map[SCANCODE_KEYPAD6] =        I4_KP6;
  scancode_map[SCANCODE_KEYPAD7] =        I4_KP7;
  scancode_map[SCANCODE_KEYPAD8] =        I4_KP8;
  scancode_map[SCANCODE_KEYPAD9] =        I4_KP9;
  scancode_map[SCANCODE_A] =              'A';
  scancode_map[SCANCODE_B] =              'B';
  scancode_map[SCANCODE_C] =              'C';
  scancode_map[SCANCODE_D] =              'D';
  scancode_map[SCANCODE_E] =              'E';
  scancode_map[SCANCODE_F] =              'F';
  scancode_map[SCANCODE_G] =              'G';
  scancode_map[SCANCODE_H] =              'H';
  scancode_map[SCANCODE_I] =              'I';
  scancode_map[SCANCODE_J] =              'J';
  scancode_map[SCANCODE_K] =              'K';
  scancode_map[SCANCODE_L] =              'L';
  scancode_map[SCANCODE_M] =              'M';
  scancode_map[SCANCODE_N] =              'N';
  scancode_map[SCANCODE_O] =              'O';
  scancode_map[SCANCODE_P] =              'P';
  scancode_map[SCANCODE_Q] =              'Q';
  scancode_map[SCANCODE_R] =              'R';
  scancode_map[SCANCODE_S] =              'S';
  scancode_map[SCANCODE_T] =              'T';
  scancode_map[SCANCODE_U] =              'U';
  scancode_map[SCANCODE_V] =              'V';
  scancode_map[SCANCODE_W] =              'W';
  scancode_map[SCANCODE_X] =              'X';
  scancode_map[SCANCODE_Y] =              'Y';
  scancode_map[SCANCODE_Z] =              'Z';
  scancode_map[SCANCODE_F1] =             I4_F1;
  scancode_map[SCANCODE_F2] =             I4_F2;
  scancode_map[SCANCODE_F3] =             I4_F3;
  scancode_map[SCANCODE_F4] =             I4_F4;
  scancode_map[SCANCODE_F5] =             I4_F5;
  scancode_map[SCANCODE_F6] =             I4_F6;
  scancode_map[SCANCODE_F7] =             I4_F7;
  scancode_map[SCANCODE_F8] =             I4_F8;
  scancode_map[SCANCODE_F9] =             I4_F9;
  scancode_map[SCANCODE_F10] =            I4_F10;
  scancode_map[SCANCODE_F11] =            I4_F11;
  scancode_map[SCANCODE_F12] =            I4_F12;
  scancode_map[SCANCODE_ESCAPE] =         I4_ESC;
  scancode_map[SCANCODE_MINUS] =          '-';
  scancode_map[SCANCODE_EQUAL] =          '=';
  scancode_map[SCANCODE_BACKSPACE] =      I4_BACKSPACE;
  scancode_map[SCANCODE_TAB] =            I4_TAB;
  scancode_map[SCANCODE_BRACKET_LEFT] =   '[';
  scancode_map[SCANCODE_BRACKET_RIGHT] =  ']';
  scancode_map[SCANCODE_ENTER] =          I4_ENTER;
  scancode_map[SCANCODE_LEFTCONTROL] =    I4_CTRL_L;
  scancode_map[SCANCODE_SEMICOLON] =      ';';
  scancode_map[SCANCODE_APOSTROPHE] =     '\'';
  scancode_map[SCANCODE_GRAVE] =          '`';
  scancode_map[SCANCODE_LEFTSHIFT] =      I4_SHIFT_L;
  scancode_map[SCANCODE_BACKSLASH] =      '\\';
  scancode_map[SCANCODE_COMMA] =          ',';
  scancode_map[SCANCODE_PERIOD] =         '.';
  scancode_map[SCANCODE_SLASH] =          '/';
  scancode_map[SCANCODE_RIGHTSHIFT] =     I4_SHIFT_R;
  scancode_map[SCANCODE_KEYPADMULTIPLY] = I4_KPSTAR;
  scancode_map[SCANCODE_LEFTALT] =        I4_ALT_L;
  scancode_map[SCANCODE_SPACE] =          I4_SPACE;
  scancode_map[SCANCODE_CAPSLOCK] =       I4_CAPS;
  scancode_map[SCANCODE_NUMLOCK] =        I4_NUM_LOCK;
  //  scancode_map[SCANCODE_SCROLLLOCK] = ;
  scancode_map[SCANCODE_CURSORUPLEFT] =   I4_KP4;
  scancode_map[SCANCODE_CURSORUPRIGHT] =  I4_KP9;
  scancode_map[SCANCODE_CURSORUP] =       I4_KP8;
  scancode_map[SCANCODE_KEYPADMINUS] =    I4_KPMINUS;
  scancode_map[SCANCODE_CURSORLEFT] =     I4_KP4;
  scancode_map[SCANCODE_CURSORRIGHT] =    I4_KP6;
  scancode_map[SCANCODE_KEYPADPLUS] =     I4_KPPLUS;
  scancode_map[SCANCODE_CURSORDOWNLEFT] = I4_KP1;
  scancode_map[SCANCODE_CURSORDOWN] =     I4_KP2;
  scancode_map[SCANCODE_CURSORDOWNRIGHT]= I4_KP3;
  scancode_map[SCANCODE_KEYPADPERIOD] =   I4_KPPERIOD;
  scancode_map[SCANCODE_LESS] =           '<';
  scancode_map[SCANCODE_KEYPADENTER] =    I4_KPENTER;
  scancode_map[SCANCODE_RIGHTCONTROL] =   I4_CTRL_R;
  //  scancode_map[SCANCODE_CONTROL] = ;
  scancode_map[SCANCODE_KEYPADDIVIDE] =   I4_KPSLASH;
  //  scancode_map[SCANCODE_PRINTSCREEN] = ;
  scancode_map[SCANCODE_RIGHTALT] =       I4_ALT_R;
  //  scancode_map[SCANCODE_BREAK] = ;
  //  scancode_map[SCANCODE_BREAK_ALTERNATIVE] = ;
  scancode_map[SCANCODE_HOME] =           I4_HOME;
  scancode_map[SCANCODE_CURSORBLOCKUP] =  I4_UP;
  scancode_map[SCANCODE_PAGEUP] =         I4_PAGEUP;
  scancode_map[SCANCODE_CURSORBLOCKLEFT]= I4_LEFT;
  scancode_map[SCANCODE_CURSORBLOCKRIGHT]=I4_RIGHT;
  scancode_map[SCANCODE_END] =            I4_END;
  scancode_map[SCANCODE_CURSORBLOCKDOWN]= I4_DOWN;
  scancode_map[SCANCODE_PAGEDOWN] =       I4_PAGEDOWN;
  scancode_map[SCANCODE_INSERT] =         I4_INSERT;
  scancode_map[SCANCODE_REMOVE] =         I4_DEL;
}


void i4_svgalib_input_class::create_scancode_press_state() {
 
  scancode_press_state = (char *)malloc(sizeof(char) * (max_scancode+1));

  for (unsigned int i=0; i<max_scancode+1; i++)
    scancode_press_state[i] = KEY_NOTPRESSED;

}

static const int scancodes[] = {
  SCANCODE_0,
  SCANCODE_1,
  SCANCODE_2,
  SCANCODE_3,
  SCANCODE_4,
  SCANCODE_5,
  SCANCODE_6,
  SCANCODE_7,
  SCANCODE_8,
  SCANCODE_9,
  SCANCODE_KEYPAD0,
  SCANCODE_KEYPAD1,
  SCANCODE_KEYPAD2,
  SCANCODE_KEYPAD3,
  SCANCODE_KEYPAD4,
  SCANCODE_KEYPAD5,
  SCANCODE_KEYPAD6,
  SCANCODE_KEYPAD7,
  SCANCODE_KEYPAD8,
  SCANCODE_KEYPAD9,
  SCANCODE_A,
  SCANCODE_B,
  SCANCODE_C,
  SCANCODE_D,
  SCANCODE_E,
  SCANCODE_F,
  SCANCODE_G,
  SCANCODE_H,
  SCANCODE_I,
  SCANCODE_J,
  SCANCODE_K,
  SCANCODE_L,
  SCANCODE_M,
  SCANCODE_N,
  SCANCODE_O,
  SCANCODE_P,
  SCANCODE_Q,
  SCANCODE_R,
  SCANCODE_S,
  SCANCODE_T,
  SCANCODE_U,
  SCANCODE_V,
  SCANCODE_W,
  SCANCODE_X,
  SCANCODE_Y,
  SCANCODE_Z,
  SCANCODE_F1,
  SCANCODE_F2,
  SCANCODE_F3,
  SCANCODE_F4,
  SCANCODE_F5,
  SCANCODE_F6,
  SCANCODE_F7,
  SCANCODE_F8,
  SCANCODE_F9,
  SCANCODE_F10,
  SCANCODE_F11,
  SCANCODE_F12,
  SCANCODE_ESCAPE,
  SCANCODE_MINUS,
  SCANCODE_EQUAL,
  SCANCODE_BACKSPACE,
  SCANCODE_TAB,
  SCANCODE_BRACKET_LEFT,
  SCANCODE_BRACKET_RIGHT,
  SCANCODE_ENTER,
  SCANCODE_LEFTCONTROL,
  SCANCODE_SEMICOLON,
  SCANCODE_APOSTROPHE,
  SCANCODE_GRAVE,
  SCANCODE_LEFTSHIFT,
  SCANCODE_BACKSLASH,
  SCANCODE_COMMA,
  SCANCODE_PERIOD,
  SCANCODE_SLASH,
  SCANCODE_RIGHTSHIFT,
  SCANCODE_KEYPADMULTIPLY,
  SCANCODE_LEFTALT,
  SCANCODE_SPACE,
  SCANCODE_CAPSLOCK,
  SCANCODE_NUMLOCK,
  SCANCODE_SCROLLLOCK,
  SCANCODE_CURSORUPLEFT,
  SCANCODE_CURSORUPRIGHT,
  SCANCODE_CURSORUP,
  SCANCODE_KEYPADMINUS,
  SCANCODE_CURSORLEFT,
  SCANCODE_CURSORRIGHT,
  SCANCODE_KEYPADPLUS,
  SCANCODE_CURSORDOWNLEFT,
  SCANCODE_CURSORDOWN,
  SCANCODE_CURSORDOWNRIGHT,
  SCANCODE_KEYPADPERIOD,
  SCANCODE_LESS,
  SCANCODE_KEYPADENTER,
  SCANCODE_RIGHTCONTROL,
  SCANCODE_CONTROL,
  SCANCODE_KEYPADDIVIDE,
  SCANCODE_PRINTSCREEN,
  SCANCODE_RIGHTALT,
  SCANCODE_BREAK,
  SCANCODE_BREAK_ALTERNATIVE,
  SCANCODE_HOME,
  SCANCODE_CURSORBLOCKUP,
  SCANCODE_PAGEUP,
  SCANCODE_CURSORBLOCKLEFT,
  SCANCODE_CURSORBLOCKRIGHT,
  SCANCODE_END,
  SCANCODE_CURSORBLOCKDOWN,
  SCANCODE_PAGEDOWN,
  SCANCODE_INSERT,
  SCANCODE_REMOVE,
  -1
};

/*
 * sets max_scancode
 */
void i4_svgalib_input_class::get_scancode_info()
{
  int i = 0;
  max_scancode = 0;

  while (scancodes[i] != -1) {
    if (scancodes[i] > (int)max_scancode)
      max_scancode = scancodes[i];
    i++;
  }

}
