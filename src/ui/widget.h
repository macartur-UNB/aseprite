// Aseprite UI Library
// Copyright (C) 2001-2015  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef UI_WIDGET_H_INCLUDED
#define UI_WIDGET_H_INCLUDED


#include "gfx/border.h"
#include "gfx/color.h"
#include "gfx/point.h"
#include "gfx/rect.h"
#include "gfx/region.h"
#include "gfx/size.h"
#include "ui/base.h"
#include "ui/component.h"
#include "ui/graphics.h"
#include "ui/widget_type.h"
#include "ui/widgets_list.h"

#include <string>

#define ASSERT_VALID_WIDGET(widget) ASSERT((widget) != NULL)

namespace she {
  class Font;
}

namespace ui {

  class InitThemeEvent;
  class LoadLayoutEvent;
  class Manager;
  class Message;
  class MouseMessage;
  class PaintEvent;
  class PreferredSizeEvent;
  class ResizeEvent;
  class SaveLayoutEvent;
  class Theme;
  class Window;

  class Widget : public Component {
  public:

    // ===============================================================
    // CTOR & DTOR
    // ===============================================================

    Widget(WidgetType type = kGenericWidget);
    virtual ~Widget();

    // Safe way to delete a widget when it is not in the manager message
    // queue anymore.
    void deferDelete();

    // Main properties.

    WidgetType type() const { return m_type; }
    void setType(WidgetType type) { m_type = type; } // TODO remove this function

    const std::string& getId() const { return m_id; }
    void setId(const char* id) { m_id = id; }

    int flags() const { return m_flags; }
    bool hasFlags(int flags) const { return ((m_flags & flags) == flags); }
    void enableFlags(int flags) { m_flags |= flags; }
    void disableFlags(int flags) { m_flags &= ~flags; }

    int getAlign() const { return (m_flags & ALIGN_MASK); }
    void setAlign(int align) {
      m_flags = ((m_flags & PROPERTIES_MASK) |
                 (align & ALIGN_MASK));
    }

    // Text property.

    bool hasText() const { return hasFlags(HAS_TEXT); }

    const std::string& getText() const { return m_text; }
    int getTextInt() const;
    double getTextDouble() const;
    std::size_t getTextLength() const { return m_text.size(); }
    void setText(const std::string& text);
    void setTextf(const char* text, ...);
    void setTextQuiet(const std::string& text);

    int getTextWidth() const;
    int getTextHeight() const;

    gfx::Size getTextSize() const {
      return gfx::Size(getTextWidth(), getTextHeight());
    }

    // ===============================================================
    // COMMON PROPERTIES
    // ===============================================================

    // True if this widget and all its ancestors are visible.
    bool isVisible() const;
    void setVisible(bool state);

    // True if this widget can receive user input (is not disabled).
    bool isEnabled() const;
    void setEnabled(bool state);

    // True if this widget is selected (pushed in case of a button, or
    // checked in the case of a check-box).
    bool isSelected() const;
    void setSelected(bool state);

    // True if this widget wants more space when it's inside a Box
    // parent.
    bool isExpansive() const;
    void setExpansive(bool state);

    // True if this is a decorative widget created by the current
    // theme. Decorative widgets are arranged by the theme instead that
    // the parent's widget.
    bool isDecorative() const;
    void setDecorative(bool state);

    // True if this widget can receive the keyboard focus.
    bool isFocusStop() const;
    void setFocusStop(bool state);

    // True if this widget wants the focus by default when it's shown by
    // first time (e.g. when its parent window is opened).
    void setFocusMagnet(bool state);
    bool isFocusMagnet() const;

    // ===============================================================
    // LOOK & FEEL
    // ===============================================================

    she::Font* getFont() const;
    void resetFont();

    // Gets the background color of the widget.
    gfx::Color getBgColor() const {
      if (gfx::geta(m_bgColor) == 0 && m_parent)
        return m_parent->getBgColor();
      else
        return m_bgColor;
    }

    // Sets the background color of the widget
    void setBgColor(gfx::Color color);

    Theme* getTheme() const { return m_theme; }
    void setTheme(Theme* theme);

    void initTheme();

    // ===============================================================
    // PARENTS & CHILDREN
    // ===============================================================

    Window* getRoot();
    Widget* getParent() { return m_parent; }
    Manager* getManager();

    // Returns a list of parents, if "ascendant" is true the list is
    // build from child to parents, else the list is from parent to
    // children.
    void getParents(bool ascendant, WidgetsList& parents);

    // Returns a list of children.
    const WidgetsList& getChildren() const { return m_children; }

    Widget* at(int index) { return m_children[index]; }

    // Returns the first/last child or NULL if it doesn't exist.
    Widget* getFirstChild() {
      return (!m_children.empty() ? m_children.front(): NULL);
    }
    Widget* getLastChild() {
      return (!m_children.empty() ? m_children.back(): NULL);
    }

    // Returns the next or previous siblings.
    Widget* getNextSibling();
    Widget* getPreviousSibling();

    Widget* pick(const gfx::Point& pt, bool checkParentsVisibility = true);
    bool hasChild(Widget* child);
    bool hasAncestor(Widget* ancestor);
    Widget* findChild(const char* id);

    // Returns a widget in the same window that is located "sibling".
    Widget* findSibling(const char* id);

    // Finds a child with the specified ID and dynamic-casts it to type
    // T.
    template<class T>
    T* findChildT(const char* id) {
      return dynamic_cast<T*>(findChild(id));
    }

    template<class T>
    T* findFirstChildByType() {
      UI_FOREACH_WIDGET(m_children, it) {
        Widget* child = *it;
        if (T* specificChild = dynamic_cast<T*>(child))
          return specificChild;
      }
      return NULL;
    }

    void addChild(Widget* child);
    void removeChild(Widget* child);
    void removeAllChildren();
    void replaceChild(Widget* oldChild, Widget* newChild);
    void insertChild(int index, Widget* child);

    // ===============================================================
    // LAYOUT & CONSTRAINT
    // ===============================================================

    void layout();
    void loadLayout();
    void saveLayout();

    void setDecorativeWidgetBounds();

    // ===============================================================
    // POSITION & GEOMETRY
    // ===============================================================

    gfx::Rect getBounds() const { return m_bounds; }
    gfx::Point getOrigin() const { return m_bounds.getOrigin(); }
    gfx::Size getSize() const { return m_bounds.getSize(); }

    gfx::Rect getClientBounds() const {
      return gfx::Rect(0, 0, m_bounds.w, m_bounds.h);
    }

    gfx::Rect getChildrenBounds() const;
    gfx::Rect getClientChildrenBounds() const;

    // Sets the bounds of the widget generating a onResize() event.
    void setBounds(const gfx::Rect& rc);

    // Sets the bounds of the widget without generating any kind of
    // event. This member function must be used if you override
    // onResize() and want to change the size of the widget without
    // generating recursive onResize() events.
    void setBoundsQuietly(const gfx::Rect& rc);

    const gfx::Size& minSize() const { return m_minSize; }
    const gfx::Size& maxSize() const { return m_maxSize; }
    void setMinSize(const gfx::Size& sz);
    void setMaxSize(const gfx::Size& sz);

    const gfx::Border& border() const { return m_border; }
    void setBorder(const gfx::Border& border);

    int childSpacing() const { return m_childSpacing; }
    void setChildSpacing(int childSpacing);

    void noBorderNoChildSpacing();

    // Flags for getDrawableRegion()
    enum DrawableRegionFlags {
      kCutTopWindows = 1, // Cut areas where are windows on top.
      kUseChildArea = 2,  // Use areas where are children.
    };

    void getRegion(gfx::Region& region);
    void getDrawableRegion(gfx::Region& region, DrawableRegionFlags flags);

    gfx::Point toClient(const gfx::Point& pt) const {
      return pt - m_bounds.getOrigin();
    }
    gfx::Rect toClient(const gfx::Rect& rc) const {
      return gfx::Rect(rc).offset(-m_bounds.x, -m_bounds.y);
    }

    void getTextIconInfo(
      gfx::Rect* box,
      gfx::Rect* text = NULL,
      gfx::Rect* icon = NULL,
      int icon_align = 0, int icon_w = 0, int icon_h = 0);

    // ===============================================================
    // REFRESH ISSUES
    // ===============================================================

    bool isDoubleBuffered() const;
    void setDoubleBuffered(bool doubleBuffered);

    bool isTransparent() const;
    void setTransparent(bool transparent);

    void invalidate();
    void invalidateRect(const gfx::Rect& rect);
    void invalidateRegion(const gfx::Region& region);

    // Returns the invalid region to being updated with PaintMessages
    // and onPaint() events.
    const gfx::Region& getUpdateRegion() const {
      return m_updateRegion;
    }

    void flushRedraw();

    void scrollRegion(const gfx::Region& region, const gfx::Point& delta);

    GraphicsPtr getGraphics(const gfx::Rect& clip);

    // ===============================================================
    // GUI MANAGER
    // ===============================================================

    bool sendMessage(Message* msg);
    void closeWindow();

    void broadcastMouseMessage(WidgetsList& targets);

    // ===============================================================
    // SIZE & POSITION
    // ===============================================================

    gfx::Size getPreferredSize();
    gfx::Size getPreferredSize(const gfx::Size& fitIn);
    void setPreferredSize(const gfx::Size& fixedSize);
    void setPreferredSize(int fixedWidth, int fixedHeight);

    // ===============================================================
    // MOUSE, FOCUS & KEYBOARD
    // ===============================================================

    void requestFocus();
    void releaseFocus();
    void captureMouse();
    void releaseMouse();

    bool hasFocus();
    bool hasMouse();
    bool hasMouseOver();
    bool hasCapture();

    // Offer the capture to widgets of the given type
    void offerCapture(ui::MouseMessage* mouseMsg, int widget_type);

    // Returns lower-case letter that represet the mnemonic of the widget
    // (the underscored character, i.e. the letter after & symbol).
    int getMnemonicChar() const;

  protected:
    void offsetWidgets(int dx, int dy);

    // ===============================================================
    // MESSAGE PROCESSING
    // ===============================================================

    virtual bool onProcessMessage(Message* msg);

    // ===============================================================
    // EVENTS
    // ===============================================================

    virtual void onInvalidateRegion(const gfx::Region& region);
    virtual void onPreferredSize(PreferredSizeEvent& ev);
    virtual void onLoadLayout(LoadLayoutEvent& ev);
    virtual void onSaveLayout(SaveLayoutEvent& ev);
    virtual void onResize(ResizeEvent& ev);
    virtual void onPaint(PaintEvent& ev);
    virtual void onBroadcastMouseMessage(WidgetsList& targets);
    virtual void onInitTheme(InitThemeEvent& ev);
    virtual void onSetDecorativeWidgetBounds();
    virtual void onEnable();
    virtual void onDisable();
    virtual void onSelect();
    virtual void onDeselect();
    virtual void onSetText();
    virtual void onSetBgColor();

  private:
    void removeChild(WidgetsList::iterator& it);
    void paint(Graphics* graphics, const gfx::Region& drawRegion);
    bool paintEvent(Graphics* graphics);

    WidgetType m_type;           // Widget's type
    std::string m_id;            // Widget's id
    int m_flags;                 // Special boolean properties (see flags in ui/base.h)
    Theme* m_theme;              // Widget's theme
    std::string m_text;          // Widget text
    mutable she::Font* m_font;   // Cached font returned by the theme
    gfx::Color m_bgColor;        // Background color
    gfx::Rect m_bounds;
    gfx::Region m_updateRegion;   // Region to be redrawed.
    WidgetsList m_children;       // Sub-widgets
    Widget* m_parent;             // Who is the parent?
    gfx::Size* m_preferredSize;
    bool m_doubleBuffered;
    bool m_transparent;

    // Widget size limits
    gfx::Size m_minSize, m_maxSize;

    gfx::Border m_border;       // Border separation with the parent
    int m_childSpacing;         // Separation between children
  };

  WidgetType register_widget_type();

} // namespace ui

#endif
