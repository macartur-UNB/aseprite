// SHE library
// Copyright (C) 2012-2015  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef SHE_SKIA_SKIA_WINDOW_OSX_INCLUDED
#define SHE_SKIA_SKIA_WINDOW_OSX_INCLUDED


#include "base/disable_copying.h"
#include "she/native_cursor.h"

#include <string>

namespace she {

class EventQueue;
class SkiaDisplay;

class SkiaWindow {
public:
  enum class Backend { NONE, GL };

  SkiaWindow(EventQueue* queue, SkiaDisplay* display);
  ~SkiaWindow();

  int scale() const;
  void setScale(int scale);
  void setVisible(bool visible);
  void maximize();
  bool isMaximized() const;
  gfx::Size clientSize() const;
  gfx::Size restoredSize() const;
  void setTitle(const std::string& title);
  void captureMouse();
  void releaseMouse();
  void setMousePosition(const gfx::Point& position);
  void setNativeMouseCursor(NativeCursor cursor);
  void updateWindow();
  void* handle();

private:
  class Impl;
  Impl* m_impl;

  DISABLE_COPYING(SkiaWindow);
};

} // namespace she

#endif
