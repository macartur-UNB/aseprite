// SHE library
// Copyright (C) 2012-2015  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef SHE_ALLEG4_ALLEG_SURFACE_H_INCLUDED
#define SHE_ALLEG4_ALLEG_SURFACE_H_INCLUDED


#include <allegro.h>

#include "she/surface.h"
#include "she/common/locked_surface.h"

namespace she {

  class Alleg4Surface : public Surface
                      , public CommonLockedSurface {
  public:
    enum DestroyFlag {
      None = 0,
      DeleteThis = 1,
      DestroyHandle = 2,
      DeleteAndDestroy = DeleteThis | DestroyHandle,
    };

    Alleg4Surface(BITMAP* bmp, DestroyFlag destroy);
    Alleg4Surface(int width, int height, DestroyFlag destroy);
    Alleg4Surface(int width, int height, int bpp, DestroyFlag destroy);
    ~Alleg4Surface();

    // Surface implementation
    void dispose() override;
    int width() const override;
    int height() const override;
    bool isDirectToScreen() const override;
    gfx::Rect getClipBounds() override;
    void setClipBounds(const gfx::Rect& rc) override;
    bool intersectClipRect(const gfx::Rect& rc) override;
    LockedSurface* lock() override;
    void setDrawMode(DrawMode mode, int param) override;
    void applyScale(int scale) override;
    void* nativeHandle() override;

    // LockedSurface implementation
    int lockedWidth() const override;
    int lockedHeight() const override;
    void unlock() override;
    void clear() override;
    uint8_t* getData(int x, int y) const override;
    void getFormat(SurfaceFormatData* formatData) const override;
    gfx::Color getPixel(int x, int y) const override;
    void putPixel(gfx::Color color, int x, int y) override;
    void drawHLine(gfx::Color color, int x, int y, int w) override;
    void drawVLine(gfx::Color color, int x, int y, int h) override;
    void drawLine(gfx::Color color, const gfx::Point& a, const gfx::Point& b) override;
    void drawRect(gfx::Color color, const gfx::Rect& rc) override;
    void fillRect(gfx::Color color, const gfx::Rect& rc) override;
    void blitTo(LockedSurface* dest, int srcx, int srcy, int dstx, int dsty, int width, int height) const override;
    void scrollTo(const gfx::Rect& rc, int dx, int dy) override;
    void drawSurface(const LockedSurface* src, int dstx, int dsty) override;
    void drawRgbaSurface(const LockedSurface* src, int dstx, int dsty) override;

  private:
    BITMAP* m_bmp;
    DestroyFlag m_destroy;
  };

} // namespace she

#endif
