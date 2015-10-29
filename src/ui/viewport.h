// Aseprite UI Library
// Copyright (C) 2001-2013  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef UI_VIEWPORT_H_INCLUDED
#define UI_VIEWPORT_H_INCLUDED


#include "ui/widget.h"

namespace ui {

  class Viewport : public Widget
  {
  public:
    Viewport();

    gfx::Size calculateNeededSize();

  protected:
    // Events
    void onResize(ResizeEvent& ev) override;
    void onPreferredSize(PreferredSizeEvent& ev) override;
    void onPaint(PaintEvent& ev) override;
  };

} // namespace ui

#endif
