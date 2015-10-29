// SHE library
// Copyright (C) 2012-2015  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef SHE_FONT_H_INCLUDED
#define SHE_FONT_H_INCLUDED


#include <string>

namespace she {

  class Font {
  public:
    virtual ~Font() { }
    virtual void dispose() = 0;
    virtual int height() const = 0;
    virtual int charWidth(int chr) const = 0;
    virtual int textLength(const std::string& str) const = 0;
    virtual bool isScalable() const = 0;
    virtual void setSize(int size) = 0;
  };

} // namespace she

#endif
