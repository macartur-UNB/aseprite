// Aseprite UI Library
// Copyright (C) 2001-2013, 2015  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef UI_BASE_H_INCLUDED
#define UI_BASE_H_INCLUDED


// Get the system's definition of NULL
#include <stddef.h>

#ifndef TRUE
  #define TRUE         (-1)
  #define FALSE        (0)
#endif

#undef MIN
#undef MAX
#undef MID

#define MIN(x,y)     (((x) < (y)) ? (x) : (y))
#define MAX(x,y)     (((x) > (y)) ? (x) : (y))
#define MID(x,y,z)   MAX((x), MIN((y), (z)))

#undef ABS
#define ABS(x)       (((x) >= 0) ? (x) : (-(x)))

#undef SGN
#define SGN(x)       (((x) >= 0) ? 1 : -1)

namespace ui {

  // Widget flags
  enum {
    HIDDEN           = 0x00000001, // Is hidden (not visible, not clickeable).
    SELECTED         = 0x00000002, // Is selected.
    DISABLED         = 0x00000004, // Is disabled (not usable).
    HAS_FOCUS        = 0x00000008, // Has the input focus.
    HAS_MOUSE        = 0x00000010, // Has the mouse.
    HAS_CAPTURE      = 0x00000020, // Captured the mouse .
    FOCUS_STOP       = 0x00000040, // The widget support the focus on it.
    FOCUS_MAGNET     = 0x00000080, // The widget wants the focus by default (e.g. when the dialog is shown by first time).
    EXPANSIVE        = 0x00000100, // Is expansive (want more space).
    DECORATIVE       = 0x00000200, // To decorate windows.
    INITIALIZED      = 0x00000400, // The widget was already initialized by a theme.
    DIRTY            = 0x00000800, // The widget (or one child) is dirty (update_region != empty).
    HAS_TEXT         = 0x00001000, // The widget has text (at least setText() was called one time).
    PROPERTIES_MASK  = 0x0000ffff,

    HORIZONTAL       = 0x00010000,
    VERTICAL         = 0x00020000,
    LEFT             = 0x00040000,
    CENTER           = 0x00080000,
    RIGHT            = 0x00100000,
    TOP              = 0x00200000,
    MIDDLE           = 0x00400000,
    BOTTOM           = 0x00800000,
    HOMOGENEOUS      = 0x01000000,
    WORDWRAP         = 0x02000000,
    ALIGN_MASK       = 0xffff0000,
  };

} // namespace ui

#endif  // UI_BASE_H_INCLUDED
