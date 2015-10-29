// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_UI_EDITOR_MOVING_CEL_STATE_H_INCLUDED
#define APP_UI_EDITOR_MOVING_CEL_STATE_H_INCLUDED


#include "app/ui/editor/standby_state.h"

namespace doc {
  class Cel;
}

namespace app {
  class Editor;

  class MovingCelState : public StandbyState {
  public:
    MovingCelState(Editor* editor, ui::MouseMessage* msg);
    virtual ~MovingCelState();

    virtual bool onMouseUp(Editor* editor, ui::MouseMessage* msg) override;
    virtual bool onMouseMove(Editor* editor, ui::MouseMessage* msg) override;
    virtual bool onUpdateStatusBar(Editor* editor) override;

    virtual bool requireBrushPreview() override { return false; }

  private:
    Cel* m_cel;
    gfx::Point m_celStart;
    gfx::Point m_mouseStart;
    gfx::Point m_celNew;
    bool m_canceled;
    bool m_maskVisible;
  };

} // namespace app

#endif  // APP_UI_EDITOR_MOVING_CEL_STATE_H_INCLUDED
