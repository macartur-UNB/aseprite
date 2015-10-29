// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_UI_EDITOR_EDITOR_DECORATOR_H_INCLUDED
#define APP_UI_EDITOR_EDITOR_DECORATOR_H_INCLUDED


#include "gfx/color.h"
#include "gfx/rect.h"

namespace doc {
  class Image;
}

namespace app {
  class Editor;
  class EditorDecorator;

  using namespace doc;

  // EditorPreRender and EditorPostRender are two interfaces used to
  // draw elements in the editor's area. They are implemented by the
  // editor and used by a EditorDecorator.
  class EditorPreRender {
  public:
    virtual ~EditorPreRender() { }
    virtual Editor* getEditor() = 0;
    virtual Image* getImage() = 0;
    virtual void fillRect(const gfx::Rect& rect, uint32_t rgbaColor, int opacity) = 0;
  };

  class EditorPostRender {
  public:
    virtual ~EditorPostRender() { }
    virtual Editor* getEditor() = 0;
    virtual void drawLine(int x1, int y1, int x2, int y2, gfx::Color screenColor) = 0;
    virtual void drawRectXor(const gfx::Rect& rc) = 0;
  };

  // Used by editor's states to pre- and post-render customized
  // decorations depending of the state (e.g. SelectBoxState draws the
  // selected bounds/canvas area).
  class EditorDecorator {
  public:
    virtual ~EditorDecorator() { }
    virtual void preRenderDecorator(EditorPreRender* render) = 0;
    virtual void postRenderDecorator(EditorPostRender* render) = 0;
  };

} // namespace app

#endif  // APP_UI_EDITOR_EDITOR_DECORATOR_H_INCLUDED
