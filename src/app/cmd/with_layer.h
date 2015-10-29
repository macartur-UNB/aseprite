// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_CMD_WITH_LAYER_H_INCLUDED
#define APP_CMD_WITH_LAYER_H_INCLUDED


#include "doc/object_id.h"

namespace doc {
  class Layer;
}

namespace app {
namespace cmd {
  using namespace doc;

  class WithLayer {
  public:
    WithLayer(Layer* layer);
    Layer* layer();

  private:
    ObjectId m_layerId;
  };

} // namespace cmd
} // namespace app

#endif
