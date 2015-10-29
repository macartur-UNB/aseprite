// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_CONTEXT_FLAGS_H_INCLUDED
#define APP_CONTEXT_FLAGS_H_INCLUDED


namespace doc {
  class Site;
}

namespace app {

  class Context;

  class ContextFlags {
  public:
    enum {
      HasActiveDocument           = 1 << 0,
      HasActiveSprite             = 1 << 1,
      HasVisibleMask              = 1 << 2,
      HasActiveLayer              = 1 << 3,
      HasActiveCel                = 1 << 4,
      HasActiveImage              = 1 << 5,
      HasBackgroundLayer          = 1 << 6,
      ActiveDocumentIsReadable    = 1 << 7,
      ActiveDocumentIsWritable    = 1 << 8,
      ActiveLayerIsImage          = 1 << 9,
      ActiveLayerIsBackground     = 1 << 10,
      ActiveLayerIsVisible        = 1 << 11,
      ActiveLayerIsEditable       = 1 << 12,
    };

    ContextFlags();

    bool check(uint32_t flags) const { return (m_flags & flags) == flags; }
    void update(Context* context);

  private:
    void updateFlagsFromSite(const doc::Site& site);

    uint32_t m_flags;
  };

} // namespace app

#endif
