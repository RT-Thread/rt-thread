// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.3
// PROJECT: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_HELPERS_H
#define _SQUARELINE_PROJECT_UI_HELPERS_H

#include "lvgl.h"

#define _UI_TEMPORARY_STRING_BUFFER_SIZE 32
#define _UI_BAR_PROPERTY_VALUE 0
#define _UI_BAR_PROPERTY_VALUE_WITH_ANIM 1
void _ui_bar_set_property(lv_obj_t *target, int id, int val);

#define _UI_BASIC_PROPERTY_POSITION_X 0
#define _UI_BASIC_PROPERTY_POSITION_Y 1
#define _UI_BASIC_PROPERTY_WIDTH 2
#define _UI_BASIC_PROPERTY_HEIGHT 3
void _ui_basic_set_property(lv_obj_t *target, int id, int val);

#define _UI_DROPDOWN_PROPERTY_SELECTED 0
void _ui_dropdown_set_property(lv_obj_t *target, int id, int val);

#define _UI_IMAGE_PROPERTY_IMAGE 0
void _ui_image_set_property(lv_obj_t *target, int id, uint8_t *val);

#define _UI_LABEL_PROPERTY_TEXT 0
void _ui_label_set_property(lv_obj_t *target, int id, char *val);

#define _UI_ROLLER_PROPERTY_SELECTED 0
#define _UI_ROLLER_PROPERTY_SELECTED_WITH_ANIM 1
void _ui_roller_set_property(lv_obj_t *target, int id, int val);

#define _UI_SLIDER_PROPERTY_VALUE 0
#define _UI_SLIDER_PROPERTY_VALUE_WITH_ANIM 1
void _ui_slider_set_property(lv_obj_t *target, int id, int val);

void _ui_screen_change(lv_obj_t *target, lv_scr_load_anim_t fademode, int spd, int delay);

void _ui_arc_increment(lv_obj_t *target, int val);

void _ui_bar_increment(lv_obj_t *target, int val, int anm);

void _ui_slider_increment(lv_obj_t *target, int val, int anm);

void _ui_keyboard_set_target(lv_obj_t *keyboard, lv_obj_t *textarea);

#define _UI_MODIFY_FLAG_ADD 0
#define _UI_MODIFY_FLAG_REMOVE 1
#define _UI_MODIFY_FLAG_TOGGLE 2
void _ui_flag_modify(lv_obj_t *target, int32_t flag, int value);

#define _UI_MODIFY_STATE_ADD 0
#define _UI_MODIFY_STATE_REMOVE 1
#define _UI_MODIFY_STATE_TOGGLE 2
void _ui_state_modify(lv_obj_t *target, int32_t state, int value);

void _ui_opacity_set(lv_obj_t *target, int val);

void _ui_anim_callback_set_x(lv_anim_t *a, int32_t v);

void _ui_anim_callback_set_y(lv_anim_t *a, int32_t v);

void _ui_anim_callback_set_width(lv_anim_t *a, int32_t v);

void _ui_anim_callback_set_height(lv_anim_t *a, int32_t v);

void _ui_anim_callback_set_opacity(lv_anim_t *a, int32_t v);

void _ui_anim_callback_set_image_zoom(lv_anim_t *a, int32_t v);

void _ui_anim_callback_set_image_angle(lv_anim_t *a, int32_t v);

int32_t _ui_anim_callback_get_x(lv_anim_t *a);

int32_t _ui_anim_callback_get_y(lv_anim_t *a);

int32_t _ui_anim_callback_get_width(lv_anim_t *a);

int32_t _ui_anim_callback_get_height(lv_anim_t *a);

int32_t _ui_anim_callback_get_opacity(lv_anim_t *a);

int32_t _ui_anim_callback_get_image_zoom(lv_anim_t *a);

int32_t _ui_anim_callback_get_image_angle(lv_anim_t *a);

void _ui_arc_set_text_value(lv_obj_t *trg, lv_obj_t *src, char *prefix, char *postfix);

void _ui_slider_set_text_value(lv_obj_t *trg, lv_obj_t *src, char *prefix, char *postfix);

void _ui_checked_set_text_value(lv_obj_t *trg, lv_obj_t *src, char *txt_on, char *txt_off);

#endif
