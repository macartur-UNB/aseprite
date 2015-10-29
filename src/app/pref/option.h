// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_PREF_OPTION_H_INCLUDED
#define APP_PREF_OPTION_H_INCLUDED


#include "base/signal.h"
#include <string>

namespace app {

  class Section {
  public:
    Section(const std::string& name) : m_name(name) { }
    const char* name() const { return m_name.c_str(); }

    Signal0<void> BeforeChange;
    Signal0<void> AfterChange;

  private:
    std::string m_name;
  };

  template<typename T>
  class Option {
  public:
    Option(Section* section, const char* id, const T& defaultValue = T())
      : m_section(section)
      , m_id(id)
      , m_default(defaultValue)
      , m_value(defaultValue)
      , m_dirty(false) {
    }

    Option& operator=(const Option& opt) {
      operator()(opt.m_value);
      return *this;
    }

    const char* section() const { return m_section->name(); }
    const char* id() const { return m_id; }
    const T& defaultValue() const { return m_default; }
    void setDefaultValue(const T& defValue) {
      m_default = defValue;
    }

    bool isDirty() const { return m_dirty; }
    void forceDirtyFlag() { m_dirty = true; }
    void cleanDirtyFlag() { m_dirty = false; }

    const T& operator()() const {
      return m_value;
    }

    const T& operator()(const T& newValue) {
      if (m_value == newValue)
        return m_value;

      BeforeChange(newValue);
      if (m_section)
        m_section->BeforeChange();

      m_value = newValue;
      m_dirty = true;

      AfterChange(newValue);
      if (m_section)
        m_section->AfterChange();

      return m_value;
    }

    Signal1<void, const T&> BeforeChange;
    Signal1<void, const T&> AfterChange;

  private:
    Section* m_section;
    const char* m_id;
    T m_default;
    T m_value;
    bool m_dirty;

    Option();
    Option(const Option& opt);
  };

} // namespace app

#endif
