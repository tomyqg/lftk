/**
 * File:   ui_builder_default.c
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  ui_builder default
 *
 * Copyright (c) 2018 - 2018  Li XianJing <xianjimli@hotmail.com>
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-02-14 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "base/button.h"
#include "base/check_button.h"
#include "base/dialog.h"
#include "base/enums.h"
#include "base/group_box.h"
#include "base/image.h"
#include "base/label.h"
#include "base/progress_bar.h"
#include "base/utf8.h"
#include "base/value.h"
#include "base/window.h"
#include "ui_loader/ui_builder.h"

static ret_t ui_builder_default_on_widget_start(ui_builder_t* b, uint16_t type, xy_t x, xy_t y,
                                                xy_t w, xy_t h) {
  widget_t* widget = NULL;
  widget_t* parent = b->widget;

  if (parent && parent->type == WIDGET_DIALOG) {
    dialog_t* dlg = DIALOG(parent);
    parent = dlg->client;
  }

  switch (type) {
    case WIDGET_DIALOG:
      widget = dialog_create(parent, x, y, w, h);
      break;
    case WIDGET_NORMAL_WINDOW:
      widget = window_create(parent, x, y, w, h);
      break;
    case WIDGET_IMAGE:
      widget = image_create(parent, x, y, w, h);
      break;
    case WIDGET_BUTTON:
      widget = button_create(parent, x, y, w, h);
      break;
    case WIDGET_LABEL:
      widget = label_create(parent, x, y, w, h);
      break;
    case WIDGET_PROGRESS_BAR:
      widget = progress_bar_create(parent, x, y, w, h);
      break;
    case WIDGET_GROUP_BOX:
      widget = group_box_create(parent, x, y, w, h);
      break;
    case WIDGET_CHECK_BUTTON:
      widget = check_button_create(parent, x, y, w, h);
      break;
    case WIDGET_RADIO_BUTTON:
      widget = check_button_create_radio(parent, x, y, w, h);
      break;
    default:
      log_debug("%s: not supported type %d\n", __func__, type);
      break;
  }

  b->widget = widget;
  if (b->root == NULL) {
    b->root = widget;
  }

  return RET_OK;
}

static ret_t ui_builder_default_on_widget_prop(ui_builder_t* b, const char* name,
                                               const char* value) {
  value_t v;
  if (strcmp(name, "text") == 0) {
    wchar_t str[128];
    uint32_t len = strlen(value);
    return_value_if_fail(len < ARRAY_SIZE(str), RET_BAD_PARAMS);

    value_set_wstr(&v, utf8_to_utf16(value, str, ARRAY_SIZE(str)));
    widget_set_prop(b->widget, name, &v);
  } else if (strcmp(name, "align_v") == 0) {
    const key_type_value_t* item = align_v_name_find(value);
    if (item != NULL) {
      value_set_int(&v, item->value);
      widget_set_prop(b->widget, name, &v);
    } else {
      log_debug("%s %s is invalid.\n", __func__, value);
    }
  } else if (strcmp(name, "align_h") == 0) {
    const key_type_value_t* item = align_h_name_find(value);
    if (item != NULL) {
      value_set_int(&v, item->value);
      widget_set_prop(b->widget, name, &v);
    } else {
      log_debug("%s %s is invalid.\n", __func__, value);
    }
  } else {
    value_set_str(&v, value);
    widget_set_prop(b->widget, name, &v);
  }

  return RET_OK;
}

static ret_t ui_builder_default_on_widget_end(ui_builder_t* b) {
  b->widget = b->widget->parent;

  return RET_OK;
}

static ui_builder_t s_ui_builder;

ui_builder_t* ui_builder_default() {
  memset(&s_ui_builder, 0x00, sizeof(ui_builder_t));

  s_ui_builder.on_widget_start = ui_builder_default_on_widget_start;
  s_ui_builder.on_widget_prop = ui_builder_default_on_widget_prop;
  s_ui_builder.on_widget_end = ui_builder_default_on_widget_end;

  return &s_ui_builder;
}
