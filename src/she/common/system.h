// SHE library
// Copyright (C) 2012-2015  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef SHE_COMMON_SYSTEM_H
#define SHE_COMMON_SYSTEM_H


#ifdef _WIN32
  #include "she/win/clipboard.h"
  #include "she/win/native_dialogs.h"
#elif defined(__APPLE__)
  #include "she/osx/clipboard.h"
  #include "she/osx/native_dialogs.h"
#else
  #include "she/clipboard_simple.h"
  #include "she/native_dialogs.h"
#endif

#include "she/common/font.h"

namespace she {

#ifdef __APPLE__
Logger* getOsxLogger();
#endif

class CommonSystem : public System {
public:
  CommonSystem()
    : m_nativeDialogs(nullptr) {
  }

  ~CommonSystem() {
    delete m_nativeDialogs;
  }

  void dispose() override {
    delete this;
  }

  Logger* logger() override {
#ifdef __APPLE__
    return getOsxLogger();
#else
    return nullptr;
#endif
  }

  NativeDialogs* nativeDialogs() override {
#ifdef _WIN32
    if (!m_nativeDialogs)
      m_nativeDialogs = new NativeDialogsWin32();
#elif defined(__APPLE__)
    if (!m_nativeDialogs)
      m_nativeDialogs = new NativeDialogsOSX();
#endif
    return m_nativeDialogs;
  }

  Clipboard* createClipboard() override {
#ifdef _WIN32
    return new ClipboardWin32();
#elif defined(__APPLE__)
    return new ClipboardOSX();
#else
    return new ClipboardImpl();
#endif
  }

  Font* loadBitmapFont(const char* filename, int scale) override {
    Surface* sheet = loadRgbaSurface(filename);
    Font* font = nullptr;
    if (sheet) {
      sheet->applyScale(scale);
      font = CommonFont::fromSurface(sheet);
    }
    return font;
  }

private:
  NativeDialogs* m_nativeDialogs;
};

} // namespace she

#endif
