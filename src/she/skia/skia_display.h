// SHE library
// Copyright (C) 2012-2015  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef SHE_SKIA_SKIA_DISPLAY_INCLUDED
#define SHE_SKIA_SKIA_DISPLAY_INCLUDED


#include "she/display.h"
#include "she/native_cursor.h"
#include "she/skia/skia_window.h"

namespace she {

class SkiaSurface;

class SkiaDisplay : public Display {
public:
  SkiaDisplay(EventQueue* queue, int width, int height, int scale);

  void setSkiaSurface(SkiaSurface* surface);

  void resize(const gfx::Size& size);
  void dispose() override;

  // Returns the real and current display's size (without scale applied).
  int width() const override;
  int height() const override;

  // Returns the display when it was not maximized.
  int originalWidth() const override;
  int originalHeight() const override;

  int scale() const override;
  void setScale(int scale) override;

  // Returns the main surface to draw into this display.
  // You must not dispose this surface.
  NonDisposableSurface* getSurface() override;

  // Flips all graphics in the surface to the real display.
  void flip() override;
  void maximize() override;
  bool isMaximized() const override;
  void setTitleBar(const std::string& title) override;
  NativeCursor nativeMouseCursor() override;
  bool setNativeMouseCursor(NativeCursor cursor) override;
  void setMousePosition(const gfx::Point& position) override;
  void captureMouse() override;
  void releaseMouse() override;

  // Returns the HWND on Windows.
  DisplayHandle nativeHandle() override;

private:
  SkiaWindow m_window;
  SkiaSurface* m_surface;
  bool m_customSurface;
  NativeCursor m_nativeCursor;
};

} // namespace she

#endif
