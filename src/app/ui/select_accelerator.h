// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_UI_SELECT_ACCELERATOR_H_INCLUDED
#define APP_UI_SELECT_ACCELERATOR_H_INCLUDED


#include "app/ui/keyboard_shortcuts.h"
#include "ui/accelerator.h"

#include "generated_select_accelerator.h"

namespace app {

  class SelectAccelerator : public app::gen::SelectAccelerator {
  public:
    SelectAccelerator(const ui::Accelerator& accelerator, KeyContext keyContext);

    bool isModified() const { return m_modified; }
    const ui::Accelerator& accel() const { return m_accel; }

  private:
    void onModifierChange(ui::KeyModifiers modifier, ui::CheckBox* checkbox);
    void onAccelChange(const ui::Accelerator* accel);
    void onClear();
    void onOK();
    void onCancel();
    void updateModifiers();
    void updateAssignedTo();

    class KeyField;

    KeyField* m_keyField;
    KeyContext m_keyContext;
    ui::Accelerator m_origAccel;
    ui::Accelerator m_accel;
    bool m_modified;
  };

} // namespace app

#endif
