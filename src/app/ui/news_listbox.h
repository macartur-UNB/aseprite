// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_UI_NEWS_LISTBOX_H_INCLUDED
#define APP_UI_NEWS_LISTBOX_H_INCLUDED


#include "ui/listbox.h"
#include "ui/timer.h"

#include <string>

namespace app {

  class HttpLoader;

  class NewsListBox : public ui::ListBox {
  public:
    NewsListBox();
    ~NewsListBox();

    void reload();

  private:
    void onTick();
    void parseFile(const std::string& filename);
    bool validCache(const std::string& filename);

    ui::Timer m_timer;
    HttpLoader* m_loader;
  };

} // namespace app

#endif
