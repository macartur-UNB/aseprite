// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef FILTERS_FILTER_INDEXED_DATA_H_INCLUDED
#define FILTERS_FILTER_INDEXED_DATA_H_INCLUDED


namespace doc {
  class Palette;
  class RgbMap;
}

namespace filters {

  // Provides a Palette and a RgbMap to help a Filter which operate
  // over an indexed image.
  class FilterIndexedData {
  public:
    virtual ~FilterIndexedData() { }
    virtual doc::Palette* getPalette() = 0;
    virtual doc::RgbMap* getRgbMap() = 0;
  };

} // namespace filters

#endif
