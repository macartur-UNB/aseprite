// Aseprite Gfx Library
// Copyright (C) 2001-2013 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef GFX_FWD_H_INCLUDED
#define GFX_FWD_H_INCLUDED


namespace gfx {

template<typename T> class BorderT;
template<typename T> class PointT;
template<typename T> class RectT;
template<typename T> class SizeT;

typedef BorderT<int> Border;
typedef PointT<int> Point;
typedef RectT<int> Rect;
typedef SizeT<int> Size;

} // namespace gfx

#endif
