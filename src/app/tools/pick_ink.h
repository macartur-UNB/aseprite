// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_TOOLS_PICK_INK_H_INCLUDED
#define APP_TOOLS_PICK_INK_H_INCLUDED


#include "app/tools/ink.h"

namespace app {
  namespace tools {

    class PickInk : public Ink {
    public:
      enum Target { Fg, Bg };

    public:
      PickInk(Target target);
      Ink* clone() override;

      Target target() const { return m_target; }

      bool isEyedropper() const override;
      void prepareInk(ToolLoop* loop) override;
      void inkHline(int x1, int y, int x2, ToolLoop* loop) override;

    private:
      Target m_target;
    };

  } // namespace tools
} // namespace app

#endif  // APP_TOOLS_PICK_INK_H_INCLUDED
