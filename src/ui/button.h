// Aseprite UI Library
// Copyright (C) 2001-2013, 2015  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef UI_BUTTON_H_INCLUDED
#define UI_BUTTON_H_INCLUDED


#include "base/signal.h"
#include "ui/widget.h"

#include <vector>

namespace she {
  class Surface;
}

namespace ui {

  class Event;

  class IButtonIcon {
  public:
    virtual ~IButtonIcon() { }
    virtual void destroy() = 0;
    virtual gfx::Size getSize() = 0;
    virtual she::Surface* getNormalIcon() = 0;
    virtual she::Surface* getSelectedIcon() = 0;
    virtual she::Surface* getDisabledIcon() = 0;
    virtual int getIconAlign() = 0;
  };

  // Generic button
  class ButtonBase : public Widget {
  public:
    ButtonBase(const std::string& text,
               WidgetType type,
               WidgetType behaviorType,
               WidgetType drawType);
    virtual ~ButtonBase();

    WidgetType getBehaviorType() const;
    WidgetType getDrawType() const;

    // Sets the interface used to get icons for the button depending its
    // state. This interface is deleted automatically in the ButtonBase dtor.
    void setIconInterface(IButtonIcon* iconInterface);

    // Used by the current theme to draw the button icon.
    IButtonIcon* getIconInterface() const { return m_iconInterface; }

    // Signals
    Signal1<void, Event&> Click;

  protected:
    // Events
    bool onProcessMessage(Message* msg) override;
    void onPreferredSize(PreferredSizeEvent& ev) override;
    void onPaint(PaintEvent& ev) override;

    // New events
    virtual void onClick(Event& ev);

  private:
    void generateButtonSelectSignal();

    bool m_pressedStatus;
    WidgetType m_behaviorType;
    WidgetType m_drawType;
    IButtonIcon* m_iconInterface;

  protected:
    bool m_handleSelect;
  };

  // Pushable button to execute commands
  class Button : public ButtonBase
  {
  public:
    Button(const std::string& text);
  };

  // Check boxes
  class CheckBox : public ButtonBase
  {
  public:
    CheckBox(const std::string& text, WidgetType drawType = kCheckWidget);
  };

  // Radio buttons
  class RadioButton : public ButtonBase
  {
  public:
    RadioButton(const std::string& text, int radioGroup, WidgetType drawType = kRadioWidget);

    int getRadioGroup() const;
    void setRadioGroup(int radioGroup);

    void deselectRadioGroup();

  protected:
    void onSelect() override;

  private:
    int m_radioGroup;
  };

} // namespace ui

#endif
