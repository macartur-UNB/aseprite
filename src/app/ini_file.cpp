// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/ini_file.h"
#include <cstdio>
#include "app/resource_finder.h"
#include "base/split_string.h"
#include "base/string.h"
#include "cfg/cfg.h"

#ifndef _WIN32
  #include "base/fs.h"
#endif

#include <cstdlib>
#include <vector>

namespace app {

using namespace gfx;

static std::string g_configFilename;
static std::vector<cfg::CfgFile*> g_configs;

ConfigModule::ConfigModule()
{
  ResourceFinder rf;
  rf.includeUserDir("aseprite.ini");
  std::string fn = rf.getFirstOrCreateDefault();

#ifndef _WIN32 // Migrate the configuration file to the new location in Unix-like systems
  {
    ResourceFinder old_rf;
    old_rf.includeHomeDir(".asepriterc");
    std::string old_fn = old_rf.defaultFilename();
    if (base::is_file(old_fn))
      base::move_file(old_fn, fn);
  }
#endif

  set_config_file(fn.c_str());
  g_configFilename = fn;
}

ConfigModule::~ConfigModule()
{
  flush_config_file();

  for (auto cfg : g_configs)
    delete cfg;
  g_configs.clear();
}

//////////////////////////////////////////////////////////////////////
// Allegro-like API to handle .ini configuration files

void push_config_state()
{
  g_configs.push_back(new cfg::CfgFile());
}

void pop_config_state()
{
  ASSERT(!g_configs.empty());

  delete g_configs.back();
  g_configs.erase(--g_configs.end());
}

void flush_config_file()
{
  ASSERT(!g_configs.empty());

  g_configs.back()->save();
}

void set_config_file(const char* filename)
{
  if (g_configs.empty())
    g_configs.push_back(new cfg::CfgFile());

  g_configs.back()->load(filename);
}

std::string main_config_filename()
{
  return g_configFilename;
}

const char* get_config_string(const char* section, const char* name, const char* value)
{
  return g_configs.back()->getValue(section, name, value);
}

void set_config_string(const char* section, const char* name, const char* value)
{
  g_configs.back()->setValue(section, name, value);
}

int get_config_int(const char* section, const char* name, int value)
{
  return g_configs.back()->getIntValue(section, name, value);
}

void set_config_int(const char* section, const char* name, int value)
{
  g_configs.back()->setIntValue(section, name, value);
}

float get_config_float(const char* section, const char* name, float value)
{
  return (float)g_configs.back()->getDoubleValue(section, name, (float)value);
}

void set_config_float(const char* section, const char* name, float value)
{
  g_configs.back()->setDoubleValue(section, name, (float)value);
}

double get_config_double(const char* section, const char* name, double value)
{
  return g_configs.back()->getDoubleValue(section, name, value);
}

void set_config_double(const char* section, const char* name, double value)
{
  g_configs.back()->setDoubleValue(section, name, value);
}

bool get_config_bool(const char* section, const char* name, bool value)
{
  return g_configs.back()->getBoolValue(section, name, value);
}

void set_config_bool(const char* section, const char* name, bool value)
{
  g_configs.back()->setBoolValue(section, name, value);
}

Rect get_config_rect(const char* section, const char* name, const Rect& rect)
{
  Rect rect2(rect);
  const char* value = get_config_string(section, name, "");
  if (value) {
    std::vector<std::string> parts;
    base::split_string(value, parts, " ");
    if (parts.size() == 4) {
      rect2.x = strtol(parts[0].c_str(), NULL, 10);
      rect2.y = strtol(parts[1].c_str(), NULL, 10);
      rect2.w = strtol(parts[2].c_str(), NULL, 10);
      rect2.h = strtol(parts[3].c_str(), NULL, 10);
    }
  }
  return rect2;
}

void set_config_rect(const char* section, const char* name, const Rect& rect)
{
  char buf[128];
  sprintf(buf, "%d %d %d %d", rect.x, rect.y, rect.w, rect.h);
  set_config_string(section, name, buf);
}

app::Color get_config_color(const char* section, const char* name, const app::Color& value)
{
  return app::Color::fromString(get_config_string(section, name, value.toString().c_str()));
}

void set_config_color(const char* section, const char* name, const app::Color& value)
{
  set_config_string(section, name, value.toString().c_str());
}

void del_config_value(const char* section, const char* name)
{
  g_configs.back()->deleteValue(section, name);
}

} // namespace app
