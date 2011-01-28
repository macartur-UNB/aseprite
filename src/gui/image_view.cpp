// ASE gui library
// Copyright (C) 2001-2011  David Capello
//
// This source file is ditributed under a BSD-like license, please
// read LICENSE.txt for more information.

#include "config.h"

#include <allegro/draw.h>
#include <allegro/gfx.h>

#include "gui/image_view.h"
#include "gui/jdraw.h"
#include "gui/jmessage.h"
#include "gui/jrect.h"
#include "gui/jsystem.h"
#include "gui/theme.h"

static bool image_msg_proc(JWidget widget, JMessage msg);

ImageView::ImageView(BITMAP* bmp, int align)
 : Widget(JI_IMAGE_VIEW)
{
  setAlign(align);
}

bool ImageView::onProcessMessage(JMessage msg)
{
  switch (msg->type) {

    case JM_REQSIZE: {
      struct jrect box, text, icon;

      jwidget_get_texticon_info(this, &box, &text, &icon,
				getAlign(), m_bmp->w, m_bmp->h);

      msg->reqsize.w = border_width.l + jrect_w(&box) + border_width.r;
      msg->reqsize.h = border_width.t + jrect_h(&box) + border_width.b;
      return true;
    }

    case JM_DRAW: {
      struct jrect box, text, icon;

      jwidget_get_texticon_info(this, &box, &text, &icon,
				getAlign(), m_bmp->w, m_bmp->h);

      jdraw_rectexclude(rc, &icon,
			jwidget_get_bg_color(this));

      blit(m_bmp, ji_screen, 0, 0,
	   icon.x1, icon.y1, jrect_w(&icon), jrect_h(&icon));

      return true;
    }
  }

  return Widget::onProcessMessage(msg);
}