// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_CMD_ADD_LAYER_H_INCLUDED
#define APP_CMD_ADD_LAYER_H_INCLUDED


#include "app/cmd.h"
#include "app/cmd/with_layer.h"

#include <sstream>

namespace doc {
  class Layer;
}

namespace app {
namespace cmd {
  using namespace doc;

  class AddLayer : public Cmd {
  public:
    AddLayer(Layer* folder, Layer* newLayer, Layer* afterThis);

  protected:
    void onExecute() override;
    void onUndo() override;
    void onRedo() override;
    size_t onMemSize() const override {
      return sizeof(*this) +
        (size_t)const_cast<std::stringstream*>(&m_stream)->tellp();
    }

  private:
    void addLayer(Layer* folder, Layer* newLayer, Layer* afterThis);
    void removeLayer(Layer* folder, Layer* layer);

    WithLayer m_folder;
    WithLayer m_newLayer;
    WithLayer m_afterThis;
    std::stringstream m_stream;
  };

} // namespace cmd
} // namespace app

#endif
