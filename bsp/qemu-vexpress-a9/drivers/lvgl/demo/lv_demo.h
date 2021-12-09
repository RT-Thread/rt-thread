/**
 * @file lv_examples.h
 *
 */

#ifndef LV_DEMO_H
#define LV_DEMO_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*If "lv_conf.h" is available from here try to use it later.*/
#ifdef __has_include
#  if __has_include("lvgl.h")
#    ifndef LV_LVGL_H_INCLUDE_SIMPLE
#      define LV_LVGL_H_INCLUDE_SIMPLE
#    endif
#  endif
#endif

#ifdef __has_include
#  if __has_include("lv_demo_conf.h")
#    ifndef LV_DEMO_CONF_INCLUDE_SIMPLE
#      define LV_DEMO_CONF_INCLUDE_SIMPLE
#    endif
#  endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include <lvgl.h>
#else
#include <lvgl.h>
#endif

#if defined(LV_DEMO_CONF_PATH)
#define __LV_TO_STR_AUX(x) #x
#define __LV_TO_STR(x) __LV_TO_STR_AUX(x)
#include __LV_TO_STR(LV_DEMO_CONF_PATH)
#undef __LV_TO_STR_AUX
#undef __LV_TO_STR
#elif defined(LV_DEMO_CONF_INCLUDE_SIMPLE)
#include "lv_demo_conf.h"
#else
#include <lv_conf.h>
#endif

#include "src/lv_demo_music/lv_demo_music.h"


/*********************
 *      DEFINES
 *********************/
/*Test  lvgl version*/
#if LV_VERSION_CHECK(8, 0, 0) == 0
#error "lv_demo: Wrong lvgl version"
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/


/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DEMO_H*/
