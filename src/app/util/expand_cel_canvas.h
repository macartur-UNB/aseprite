// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_UTIL_EXPAND_CEL_CANVAS_H_INCLUDED
#define APP_UTIL_EXPAND_CEL_CANVAS_H_INCLUDED


#include "doc/image_ref.h"
#include "filters/tiled_mode.h"
#include "gfx/point.h"
#include "gfx/rect.h"
#include "gfx/region.h"
#include "gfx/size.h"

namespace doc {
  class Cel;
  class Image;
  class Layer;
  class Site;
  class Sprite;
}

namespace app {
  class Document;
  class Transaction;

  using namespace filters;
  using namespace doc;

  // This class can be used to expand the canvas of the current cel to
  // the visible portion of sprite. If the user cancels the operation,
  // you've a rollback() method to restore the cel to its original
  // state.  If all changes are committed, some undo information is
  // stored in the document's UndoHistory to go back to the original
  // state using "Undo" command.
  class ExpandCelCanvas {
  public:
    enum Flags {
      None = 0,
      NeedsSource = 1,
      UseModifiedRegionAsUndoInfo = 2,
    };

    ExpandCelCanvas(Site site,
      TiledMode tiledMode, Transaction& undo, Flags flags);
    ~ExpandCelCanvas();

    // Commit changes made in getDestCanvas() in the cel's image. Adds
    // information in the undo history so the user can undo the
    // modifications in the canvas.
    void commit();

    // Restore the cel as its original state as when ExpandCelCanvas()
    // was created.
    void rollback();

    Image* getSourceCanvas(); // You can read pixels from here
    Image* getDestCanvas();   // You can write pixels right here

    void validateSourceCanvas(const gfx::Region& rgn);
    void validateDestCanvas(const gfx::Region& rgn);
    void invalidateDestCanvas();
    void invalidateDestCanvas(const gfx::Region& rgn);
    void copyValidDestToSourceCanvas(const gfx::Region& rgn);

    const Cel* getCel() const { return m_cel; }

  private:
    Document* m_document;
    Sprite* m_sprite;
    Layer* m_layer;
    Cel* m_cel;
    ImageRef m_celImage;
    bool m_celCreated;
    gfx::Point m_origCelPos;
    gfx::Point m_celPos;
    Flags m_flags;
    gfx::Rect m_bounds;
    ImageRef m_srcImage;
    ImageRef m_dstImage;
    bool m_closed;
    bool m_committed;
    Transaction& m_transaction;
    gfx::Region m_validSrcRegion;
    gfx::Region m_validDstRegion;
  };

} // namespace app

#endif
