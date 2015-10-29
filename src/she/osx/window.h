// SHE library
// Copyright (C) 2012-2015  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef SHE_OSX_WINDOW_H_INCLUDED
#define SHE_OSX_WINDOW_H_INCLUDED


#include <AppKit/AppKit.h>
#include <CoreFoundation/CoreFoundation.h>
#include <Foundation/Foundation.h>

#include <stdio.h>

class CloseDelegate {
public:
  virtual ~CloseDelegate() { }
  virtual void notifyClose() = 0;
};

@interface OSXWindow : NSWindow
{
  CloseDelegate* closeDelegate;
}
- (OSXWindow*)init;
- (void)dealloc;
- (CloseDelegate*)closeDelegate;
- (void)setCloseDelegate:(CloseDelegate*)aDelegate;
@end

#endif
