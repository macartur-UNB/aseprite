// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_CRASH_READ_DOCUMENT_H_INCLUDED
#define APP_CRASH_READ_DOCUMENT_H_INCLUDED


#include "doc/frame.h"
#include "doc/pixel_format.h"

#include <string>

namespace app {
class Document;
namespace crash {

  struct DocumentInfo {
    doc::PixelFormat format;
    int width;
    int height;
    doc::frame_t frames;
    std::string filename;

    DocumentInfo() :
      format(doc::IMAGE_RGB),
      width(0),
      height(0),
      frames(0) {
    }
  };

  bool read_document_info(const std::string& dir, DocumentInfo& info);
  app::Document* read_document(const std::string& dir);

} // namespace crash
} // namespace app

#endif
