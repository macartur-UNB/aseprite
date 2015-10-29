// Aseprite UI Library
// Copyright (C) 2001-2013  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef UI_PAINT_EVENT_H_INCLUDED
#define UI_PAINT_EVENT_H_INCLUDED


#include "ui/event.h"

namespace ui {

  class Graphics;
  class Widget;

  class PaintEvent : public Event
  {
  public:
    PaintEvent(Widget* source, Graphics* graphics);
    virtual ~PaintEvent();

    Graphics* getGraphics();

    bool isPainted() const;

  private:
    Graphics* m_graphics;
    bool m_painted;
  };

} // namespace ui

#endif
