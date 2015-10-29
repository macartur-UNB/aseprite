// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_CONSOLE_H_INCLUDED
#define APP_CONSOLE_H_INCLUDED


#include <exception>

namespace app {
  class Context;

  class Console {
  public:
    Console(Context* ctx = nullptr);
    ~Console();

    void printf(const char *format, ...);

    static void showException(const std::exception& e);

  private:
    bool m_withUI;
  };

} // namespace app

#endif
