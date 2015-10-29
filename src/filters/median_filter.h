// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef FILTERS_MEDIAN_FILTER_PROCESS_H_INCLUDED
#define FILTERS_MEDIAN_FILTER_PROCESS_H_INCLUDED


#include "filters/filter.h"
#include "filters/tiled_mode.h"

#include <vector>

namespace filters {

  class MedianFilter : public Filter {
  public:
    MedianFilter();

    void setTiledMode(TiledMode tiled);
    void setSize(int width, int height);

    TiledMode getTiledMode() const { return m_tiledMode; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    // Filter implementation
    const char* getName();
    void applyToRgba(FilterManager* filterMgr);
    void applyToGrayscale(FilterManager* filterMgr);
    void applyToIndexed(FilterManager* filterMgr);

  private:
    TiledMode m_tiledMode;
    int m_width;
    int m_height;
    int m_ncolors;
    std::vector<std::vector<uint8_t> > m_channel;
  };

} // namespace filters

#endif
