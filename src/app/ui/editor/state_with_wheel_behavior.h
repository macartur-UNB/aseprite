// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_UI_STATE_WITH_WHEEL_BEHAVIOR_H_INCLUDED
#define APP_UI_STATE_WITH_WHEEL_BEHAVIOR_H_INCLUDED


#include "app/ui/editor/editor_state.h"

namespace app {

  class StateWithWheelBehavior : public EditorState {
  public:
    virtual bool onMouseWheel(Editor* editor, ui::MouseMessage* msg) override;
  };

} // namespace app

#endif
