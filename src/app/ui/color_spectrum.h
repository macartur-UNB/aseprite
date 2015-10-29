// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_UI_COLOR_SPECTRUM_H_INCLUDED
#define APP_UI_COLOR_SPECTRUM_H_INCLUDED


#include "app/color.h"
#include "base/signal.h"
#include "ui/mouse_buttons.h"
#include "ui/widget.h"

namespace app {

  class ColorSpectrum : public ui::Widget {
  public:
    ColorSpectrum();
    ~ColorSpectrum();

    app::Color pickColor(const gfx::Point& pos) const;

    // Signals
    Signal2<void, const app::Color&, ui::MouseButtons> ColorChange;

  protected:
    void onPreferredSize(ui::PreferredSizeEvent& ev) override;
    void onResize(ui::ResizeEvent& ev) override;
    void onPaint(ui::PaintEvent& ev) override;
    bool onProcessMessage(ui::Message* msg) override;
  };

} // namespace app

#endif
