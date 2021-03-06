/**
 * File:   widget.h
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  basic class of all widget
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
 * 2018-01-13 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef LFTK_WIDGET_H
#define LFTK_WIDGET_H

#include "base/value.h"
#include "base/rect.h"
#include "base/events.h"
#include "base/emitter.h"
#include "base/canvas.h"
#include "base/theme.h"

BEGIN_C_DECLS

/**
 * @enum widget_state_t
 * @scriptable
 * 控件状态常量定义。
 */
typedef enum _widget_state_t {
  /**
   * @const WIDGET_STATE_NONE
   * 无效状态。
   */
  WIDGET_STATE_NONE,
  /**
   * @const WIDGET_STATE_NORMAL
   * 正常状态。
   */
  WIDGET_STATE_NORMAL,
  /**
   * @const WIDGET_STATE_PRESSED
   * 指针按下状态。
   */
  WIDGET_STATE_PRESSED,
  /**
   * @const WIDGET_STATE_OVER
   * 指针悬浮状态。
   */
  WIDGET_STATE_OVER,
  /**
   * @const WIDGET_STATE_DISABLE
   * 禁用状态。
   */
  WIDGET_STATE_DISABLE,
  /**
   * @const WIDGET_STATE_FOCUSED
   * 聚焦状态。
   */
  WIDGET_STATE_FOCUSED,
  /**
   * @const WIDGET_STATE_CHECKED
   * 勾选状态。
   */
  WIDGET_STATE_CHECKED,
  /**
   * @const WIDGET_STATE_UNCHECKED
   * 没勾选状态。
   */
  WIDGET_STATE_UNCHECKED
}widget_state_t;

/**
 * @enum widget_type_t
 * @scriptable
 * 控件类型常量定义。
 */
typedef enum _widget_type_t {
  /**
   * @const WIDGET_NONE
   * 无效类型。
   */
  WIDGET_NONE = 0,
  /**
   * @const WIDGET_WINDOW_MANAGER
   * 窗口管理器。
   */
  WIDGET_WINDOW_MANAGER,
  /**
   * @const WIDGET_NORMAL_WINDOW
   * 窗口。
   */
  WIDGET_NORMAL_WINDOW,
  /**
   * @const WIDGET_TOOLBAR
   * 工具条。
   */
  WIDGET_TOOLBAR,
  /**
   * @const WIDGET_DIALOG
   * 对话框。
   */
  WIDGET_DIALOG,
  /**
   * @const WIDGET_POPUP
   * 弹出框。
   */
  WIDGET_POPUP,
  /**
   * @const WIDGET_LABEL
   * 简单文本。
   */
  WIDGET_LABEL,
  /**
   * @const WIDGET_BUTTON
   * 按钮。
   */
  WIDGET_BUTTON,
  /**
   * @const WIDGET_IMAGE
   * 图片。
   */
  WIDGET_IMAGE,
  /**
   * @const WIDGET_EDIT
   * 文本编辑器。
   */
  WIDGET_EDIT,
  /**
   * @const WIDGET_PROGRESS_BAR
   * 进度条。
   */
  WIDGET_PROGRESS_BAR,
  /**
   * @const WIDGET_GROUP_BOX
   * 分组框。
   */
  WIDGET_GROUP_BOX,
  /**
   * @const WIDGET_CHECK_BUTTON
   * 多选按钮。
   */
  WIDGET_CHECK_BUTTON,
  /**
   * @const WIDGET_RADIO_BUTTON
   * 单选按钮。
   */
  WIDGET_RADIO_BUTTON,
}widget_type_t;

struct _widget_t;
typedef struct _widget_t widget_t;

typedef ret_t (*widget_invalidate_t)(widget_t* widget, rect_t* r);
typedef ret_t (*widget_on_event_t)(widget_t* widget, event_t* e);
typedef ret_t (*widget_on_paint_self_t)(widget_t* widget, canvas_t* c);
typedef ret_t (*widget_on_paint_children_t)(widget_t* widget, canvas_t* c);
typedef ret_t (*widget_on_keydown_t)(widget_t* widget, key_event_t* e);
typedef ret_t (*widget_on_keyup_t)(widget_t* widget, key_event_t* e);
typedef ret_t (*widget_on_click_t)(widget_t* widget, pointer_event_t* e);
typedef ret_t (*widget_on_pointer_down_t)(widget_t* widget, pointer_event_t* e);
typedef ret_t (*widget_on_pointer_move_t)(widget_t* widget, pointer_event_t* e);
typedef ret_t (*widget_on_pointer_up_t)(widget_t* widget, pointer_event_t* e);
typedef ret_t (*widget_get_prop_t)(widget_t* widget, const char* name, value_t* v);
typedef ret_t (*widget_set_prop_t)(widget_t* widget, const char* name, const value_t* v);
typedef ret_t (*widget_grab_t)(widget_t* widget, widget_t* child);
typedef ret_t (*widget_ungrab_t)(widget_t* widget, widget_t* child);
typedef widget_t* (*widget_find_target_t)(widget_t* widget, xy_t x, xy_t y);
typedef ret_t (*widget_destroy_t)(widget_t* widget);

typedef struct _widget_vtable_t {
  widget_get_prop_t get_prop;
  widget_set_prop_t set_prop;
  widget_on_click_t on_click;
  widget_on_keyup_t on_keyup;
  widget_on_keydown_t on_keydown;
  widget_on_paint_self_t on_paint_self;
  widget_on_paint_children_t on_paint_children;
  widget_on_pointer_down_t on_pointer_down;
  widget_on_pointer_move_t on_pointer_move;
  widget_on_pointer_up_t on_pointer_up;
  widget_invalidate_t invalidate;
  widget_on_event_t on_event;
  widget_grab_t grab;
  widget_ungrab_t ungrab;
  widget_find_target_t find_target;
  widget_destroy_t  destroy;
}widget_vtable_t;

/**
 * @class widget_t
 * @scriptable
 * 窗口基类。
 */
struct _widget_t {
  /**
   * @property {xy_t} x
   * @readonly
   * x坐标。
   */
  xy_t x;
  /**
   * @property {xy_t} y
   * @readonly
   * y坐标。
   */
  xy_t y;
  /**
   * @property {wh_t} w
   * @readonly
   * 宽度。
   */
  wh_t w;
  /**
   * @property {wh_t} h
   * @readonly
   * 高度。
   */
  wh_t h;
  /**
   * @property {uint8_t} type
   * @readonly
   * 类型。
   */
  uint8_t type;
  /**
   * @property {uint8_t} subtype
   * @readonly
   * 子类型，仅用于控制控件的Style。
   */
  uint8_t subtype:4; /*for style*/
  /**
   * @property {uint8_t} state
   * @readonly
   * 控件的状态。
   */
  uint8_t state:4;
  /**
   * @property {bool_t} enable
   * @readonly
   * 启用/禁用状态。
   */
  uint8_t enable:1;
  /**
   * @property {bool_t} visible
   * @readonly
   * 是否可见。
   */
  uint8_t visible:1;
  /**
   * @property {bool_t} focused
   * @readonly
   * 是否得到焦点。
   */
  uint8_t focused:1;
  /**
   * @property {bool_t} initializing
   * @readonly
   * @scriptable no
   * 标识控件是否还在初始化中。
   */
  uint8_t initializing:1;
  /**
   * @property {char*} name
   * @readonly
   * 控件名字
   */
  char name[NAME_LEN+1];
  /**
   * @property {widget_t*} parent
   * @readonly
   * 父控件
   */
  widget_t* parent;
  /**
   * @property {widget_t*} target 
   * @readonly
   * @scriptable no
   * 接收事件的子控件。
   */
  widget_t* target;
  /**
   * @property {array_t*} children
   * @readonly
   * @scriptable no
   * 全部子控件。
   */
  array_t* children;
  /**
   * @property {emitter*} emitter
   * @private
   * 事件发射器。
   */
  emitter_t* emitter;
  /**
   * @property {style_t} style
   * @private
   * Style数据。
   */
  style_t style;
  /**
   * @property {widget_vtable_t} vt
   * @private
   * 虚函数表。
   */
  const widget_vtable_t* vt;
};

/**
 * @method widget_init
 * 初始化控件。仅在子类控件构造函数中使用。
 * @private
 * @param {widget_t*} widget widget对象。
 * @param {widget_t*} parent widget的父控件。
 * @param {uint8_t} type 控件的类型。
 *
 * @return {widget*} widget对象本身。
 */
widget_t* widget_init(widget_t* widget, widget_t* parent, uint8_t type);

/**
 * @method widget_update_style
 * 让控件根据自己当前状态更新style。
 * @private
 * @param {widget_t*} widget widget对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_update_style(widget_t* widget);

/**
 * @method widget_count_children
 * 获取子控件的个数。
 * @param {widget_t*} widget 控件对象。
 *
 * @return {uint32_t} 子控件的个数。
 */
uint32_t widget_count_children(widget_t* widget);

/**
 * @method widget_get_child
 * 获取指定索引的子控件。
 * @param {widget_t*} widget 控件对象。
 * @param {uint32_t}  index 索引
 *
 * @return {widget_t*} 子控件。
 */
widget_t* widget_get_child(widget_t* widget, uint32_t index);

/**
 * @method widget_move
 * 移动控件。
 * @param {widget_t*} widget 控件对象。
 * @param {xy_t}   x x坐标
 * @param {xy_t}   y y坐标
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_move(widget_t* widget, xy_t x, xy_t y);

/**
 * @method widget_resize
 * 调整控件的大小。
 * @param {widget_t*} widget 控件对象。
 * @param {wh_t}   w 宽度
 * @param {wh_t}   h 高度
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_resize(widget_t* widget, wh_t w, wh_t h);

/**
 * @method widget_move_resize
 * 移动控件并调整控件的大小。
 * @param {widget_t*} widget 控件对象。
 * @param {xy_t}   x x坐标
 * @param {xy_t}   y y坐标
 * @param {wh_t}   w 宽度
 * @param {wh_t}   h 高度
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_move_resize(widget_t* widget, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method widget_set_value
 * 设置控件的值。只是对widget_set_prop的包装，值的意义由子类控件决定。
 * @param {widget_t*} widget 控件对象。
 * @param {uint32_t}  value 值
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_set_value(widget_t* widget, uint32_t value);

/**
 * @method widget_set_text
 * 设置控件的文本。只是对widget_set_prop的包装，文本的意义由子类控件决定。
 * @param {widget_t*} widget 控件对象。
 * @param {wchar_t*}  text 文本。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_set_text(widget_t* widget, const wchar_t* text);

/**
 * @method widget_get_value
 * 获取控件的值。只是对widget_get_prop的包装，值的意义由子类控件决定。
 * @param {widget_t*} widget 控件对象。
 *
 * @return {uint32_t} 返回值。
 */
uint32_t widget_get_value(widget_t* widget);

/**
 * @method widget_get_text
 * 获取控件的文本。只是对widget_get_prop的包装，文本的意义由子类控件决定。
 * @param {widget_t*} widget 控件对象。
 *
 * @return {wchar_t*} 返回文本。
 */
const wchar_t* widget_get_text(widget_t* widget);

/**
 * @method widget_to_local
 * 将全局坐标转换成控件内的本地坐标，即相对于控件左上角的坐标。
 * @param {widget_t*} widget 控件对象。
 * @param {point_t*} p 坐标点。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_to_local(widget_t* widget, point_t* p);

/**
 * @method widget_to_global
 * 将控件内的本地坐标转换成全局坐标。
 * @param {widget_t*} widget 控件对象。
 * @param {point_t*} p 坐标点。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_to_global(widget_t* widget, point_t* p);

/**
 * @method widget_set_name
 * 设置控件的名称。
 * @param {widget_t*} widget 控件对象。
 * @param {char*} name 名称。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_set_name(widget_t* widget, const char* name);

/**
 * @method widget_set_enable
 * 设置控件的可用性。
 * @param {widget_t*} widget 控件对象。
 * @param {bool_t} enable 是否启动。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_set_enable(widget_t* widget, bool_t enable);

/**
 * @method widget_set_focused
 * 设置控件的是否聚焦。
 * @param {widget_t*} widget 控件对象。
 * @param {bool_t} focused 是否聚焦。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_set_focused(widget_t* widget, bool_t focused);

/**
 * @method widget_set_state
 * 设置控件的状态。
 * @param {widget_t*} widget 控件对象。
 * @param {widget_state_t} state 状态。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_set_state(widget_t* widget, widget_state_t state);

/**
 * @method widget_destroy_children
 * 销毁全部子控件。
 * @param {widget_t*} widget 控件对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_destroy_children(widget_t* widget);

/**
 * @method widget_add_child
 * 加入一个子控件。
 * @param {widget_t*} widget 控件对象。
 * @param {widget_t*} child 子控件对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_add_child(widget_t* widget, widget_t* child);

/**
 * @method widget_remove_child
 * 移出指定的子控件(并不销毁)。
 * @param {widget_t*} widget 控件对象。
 * @param {widget_t*} child 子控件对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_remove_child(widget_t* widget, widget_t* child);

/**
 * @method widget_find_target
 * 查找x/y坐标对应的子控件。
 * @private
 * @param {widget_t*} widget 控件对象。
 * @param {xy_t} x x坐标。
 * @param {xy_t} y y坐标。
 *
 * @return {widget*} 子控件或NULL。
 */
widget_t* widget_find_target(widget_t* widget, xy_t x, xy_t y);

/**
 * @method widget_lookup
 * 查找指定名称的子控件。
 * @param {widget_t*} widget 控件对象。
 * @param {char*} name 子控件的名称。
 * @param {bool_t} recursive 是否递归查找全部子控件。
 *
 * @return {widget_t*} 子控件或NULL。
 */
widget_t* widget_lookup(widget_t* widget, const char* name, bool_t recursive);

/**
 * @method widget_set_visible
 * 设置控件的可见性。
 * @param {widget_t*} widget 控件对象。
 * @param {bool_t} visible 是否可见。
 * @param {bool_t} recursive 是否递归设置全部子控件。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_set_visible(widget_t* widget, bool_t visible, bool_t recursive);

/**
 * @method widget_on
 * 注册指定事件的处理函数。
 * @scriptable custom
 * @param {widget_t*} widget 控件对象。
 * @param {event_type_t} type 事件类型。
 * @param {event_func_t} on_event 事件处理函数。
 * @param {void*} ctx 事件处理函数上下文。
 *
 * @return {uint32_t} 返回id，用于widget_off。
 */
uint32_t widget_on(widget_t* widget, event_type_t type, event_func_t on_event, void* ctx); 

/**
 * @method widget_off
 * 注销指定事件的处理函数。
 * @scriptable custom
 * @param {widget_t*} widget 控件对象。
 * @param {uint32_t} id widget_on返回的ID。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_off(widget_t* widget, uint32_t id);

/**
 * @method widget_off_by_func
 * 注销指定事件的处理函数。
 * @scriptable no
 * @param {widget_t*} widget 控件对象。
 * @param {event_type_t} type 事件类型。
 * @param {event_func_t} on_event 事件处理函数。
 * @param {void*} ctx 事件处理函数上下文。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_off_by_func(widget_t* widget, event_type_t type, event_func_t on_event, void* ctx); 

/**
 * @method widget_invalidate
 * 请求重绘指定的区域。
 * @param {widget_t*} widget 控件对象。
 * @param {rect_t*} r 矩形对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_invalidate(widget_t* widget, rect_t* r);

/**
 * @method widget_paint
 * 绘制控件到一个canvas上。
 * @private
 * @param {widget_t*} widget 控件对象。
 * @param {canvas_t*} c 画布对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_paint(widget_t* widget, canvas_t* c);

/**
 * @method widget_dispatch
 * 分发一个事件。
 * @private
 * @param {widget_t*} widget 控件对象。
 * @param {event_t*} e 事件。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_dispatch(widget_t* widget, event_t* e);

ret_t widget_on_paint_self(widget_t* widget, canvas_t* c);
ret_t widget_on_paint_children(widget_t* widget, canvas_t* c);

/**
 * @method widget_get_prop
 * 通用的获取控件属性的函数。
 * @param {widget_t*} widget 控件对象。
 * @param {char*} name 属性的名称。
 * @param {value_t*} v 属性的值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_get_prop(widget_t* widget, const char* name, value_t* v);

/**
 * @method widget_set_prop
 * 通用的设置控件属性的函数。
 * @param {widget_t*} widget 控件对象。
 * @param {char*} name 属性的名称。
 * @param {value_t*} v 属性的值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_set_prop(widget_t* widget, const char* name, const value_t* v);

ret_t widget_on_paint(widget_t* widget, canvas_t* c);
ret_t widget_on_keydown(widget_t* widget, key_event_t* e);
ret_t widget_on_keyup(widget_t* widget, key_event_t* e);
ret_t widget_on_click(widget_t* widget, pointer_event_t* e);
ret_t widget_on_pointer_down(widget_t* widget, pointer_event_t* e);
ret_t widget_on_pointer_move(widget_t* widget, pointer_event_t* e);
ret_t widget_on_pointer_up(widget_t* widget, pointer_event_t* e);

/**
 * @method widget_grab
 * 让指定子控件抓住事件。抓住之后，事件由窗口直接分发给该控件。
 * @param {widget_t*} widget 控件对象。
 * @param {widget_t*} child 子控件对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_grab(widget_t* widget, widget_t* child);

/**
 * @method widget_ungrab
 * 让指定子控件放弃抓住事件。
 * @param {widget_t*} widget 控件对象。
 * @param {widget_t*} child 子控件对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_ungrab(widget_t* widget, widget_t* child);

/**
 * @method widget_destroy
 * 销毁控件。
 * @param {widget_t*} widget 控件对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t widget_destroy(widget_t* widget);

#define WIDGET(w) (&(w.widget))
#define WIDGETP(w) (widget_t*)(w)

typedef widget_t* (*widget_create_t)(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

END_C_DECLS

#endif/*LFTK_WIDGET_H*/

