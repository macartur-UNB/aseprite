// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/ui/recent_listbox.h"

#include "app/app.h"
#include "app/commands/commands.h"
#include "app/commands/params.h"
#include "app/recent_files.h"
#include "app/ui/skin/skin_theme.h"
#include "app/ui/skin/style.h"
#include "app/ui_context.h"
#include "base/bind.h"
#include "base/path.h"
#include "ui/graphics.h"
#include "ui/link_label.h"
#include "ui/listitem.h"
#include "ui/message.h"
#include "ui/paint_event.h"
#include "ui/preferred_size_event.h"
#include "ui/system.h"
#include "ui/view.h"

namespace app {

using namespace ui;
using namespace skin;

//////////////////////////////////////////////////////////////////////
// RecentFileItem

class RecentFileItem : public LinkLabel {
public:
  RecentFileItem(const std::string& file)
    : LinkLabel(file) {
  }

protected:
  void onPreferredSize(PreferredSizeEvent& ev) override {
    SkinTheme* theme = static_cast<SkinTheme*>(getTheme());
    Style* style = theme->styles.recentFile();
    Style* styleDetail = theme->styles.recentFileDetail();
    Style::State state;
    gfx::Size sz1 = style->preferredSize(name().c_str(), state);
    gfx::Size sz2 = styleDetail->preferredSize(path().c_str(), state);
    ev.setPreferredSize(gfx::Size(sz1.w+sz2.w, MAX(sz1.h, sz2.h)));
  }

  void onPaint(PaintEvent& ev) override {
    SkinTheme* theme = static_cast<SkinTheme*>(getTheme());
    Graphics* g = ev.getGraphics();
    gfx::Rect bounds = getClientBounds();
    Style* style = theme->styles.recentFile();
    Style* styleDetail = theme->styles.recentFileDetail();

    Style::State state;
    if (hasMouse() && !getManager()->getCapture()) state += Style::hover();
    if (isSelected()) state += Style::active();
    if (getParent()->hasCapture()) state += Style::clicked();

    std::string name = this->name();
    style->paint(g, bounds, name.c_str(), state);

    gfx::Size textSize = style->preferredSize(name.c_str(), state);
    gfx::Rect detailsBounds(
      bounds.x+textSize.w, bounds.y,
      bounds.w-textSize.w, bounds.h);
    styleDetail->paint(g, detailsBounds, path().c_str(), state);
  }

  void onClick() override {
    static_cast<RecentListBox*>(getParent())->onClick(getText());
  }

private:
  std::string name() const { return base::get_file_name(getText()); }
  std::string path() const { return base::get_file_path(getText()); }
};

//////////////////////////////////////////////////////////////////////
// RecentListBox

RecentListBox::RecentListBox()
{
  m_recentFilesConn =
    App::instance()->getRecentFiles()->Changed.connect(
      Bind(&RecentListBox::rebuildList, this));
}

void RecentListBox::rebuildList()
{
  while (getLastChild())
    removeChild(getLastChild());

  onRebuildList();

  View* view = View::getView(this);
  if (view)
    view->layout();
  else
    layout();
}

//////////////////////////////////////////////////////////////////////
// RecentFilesListBox

RecentFilesListBox::RecentFilesListBox()
{
  onRebuildList();
}

void RecentFilesListBox::onRebuildList()
{
  RecentFiles* recent = App::instance()->getRecentFiles();

  auto it = recent->files_begin();
  auto end = recent->files_end();
  for (; it != end; ++it)
    addChild(new RecentFileItem(it->c_str()));
}

void RecentFilesListBox::onClick(const std::string& path)
{
  Command* command = CommandsModule::instance()->getCommandByName(CommandId::OpenFile);
  Params params;
  params.set("filename", path.c_str());
  UIContext::instance()->executeCommand(command, params);
}

//////////////////////////////////////////////////////////////////////
// RecentFoldersListBox

RecentFoldersListBox::RecentFoldersListBox()
{
  onRebuildList();
}

void RecentFoldersListBox::onRebuildList()
{
  RecentFiles* recent = App::instance()->getRecentFiles();

  auto it = recent->paths_begin();
  auto end = recent->paths_end();
  for (; it != end; ++it)
    addChild(new RecentFileItem(it->c_str()));
}

void RecentFoldersListBox::onClick(const std::string& path)
{
  Command* command = CommandsModule::instance()->getCommandByName(CommandId::OpenFile);
  Params params;
  params.set("folder", path.c_str());
  UIContext::instance()->executeCommand(command, params);
}

} // namespace app
