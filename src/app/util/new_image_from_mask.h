// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_UTIL_NEW_IMAGE_FROM_MASK_H_INCLUDED
#define APP_UTIL_NEW_IMAGE_FROM_MASK_H_INCLUDED


namespace doc {
  class Image;
  class Mask;
  class Site;
}

namespace app {

  doc::Image* new_image_from_mask(const doc::Site& site);
  doc::Image* new_image_from_mask(const doc::Site& site, const doc::Mask* mask);

} // namespace app

#endif
