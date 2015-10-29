// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_UI_ZOOM_ENTRY_H_INCLUDED
#define APP_UI_ZOOM_ENTRY_H_INCLUDED


#include "render/zoom.h"
#include "ui/int_entry.h"
#include "ui/slider.h"

namespace app {

  class ZoomEntry : public ui::IntEntry
                  , public ui::SliderDelegate {
  public:
    ZoomEntry();

    void setZoom(const render::Zoom& zoom);

    Signal1<void, const render::Zoom&> ZoomChange;

  private:
    // SliderDelegate impl
    std::string onGetTextFromValue(int value) override;
    int onGetValueFromText(const std::string& text) override;

    void onValueChange() override;
  };

} // namespace app

#endif
