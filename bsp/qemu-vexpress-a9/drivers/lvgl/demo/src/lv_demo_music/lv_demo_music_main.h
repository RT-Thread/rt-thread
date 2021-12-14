/**
 * @file lv_demo_music_main.h
 *
 */

#ifndef LV_DEMO_MUSIC_MAIN_H
#define LV_DEMO_MUSIC_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_music.h"
#if LV_USE_DEMO_MUSIC

/*********************
 *      DEFINES
 *********************/
#define LV_DEMO_MUSIC_SQUARE      (LV_HOR_RES_MAX <= 240 && LV_VER_RES_MAX <= 240 && LV_HOR_RES_MAX == LV_VER_RES_MAX ? 1 : 0)
#if LV_DEMO_MUSIC_SQUARE
#define LV_DEMO_MUSIC_LANDSCAPE 0
#define LV_DEMO_MUSIC_PORTRAIT 0
#else
#define LV_DEMO_MUSIC_LANDSCAPE    (LV_HOR_RES_MAX > LV_VER_RES_MAX ? 1 : 0)
#define LV_DEMO_MUSIC_PORTRAIT     (!LV_DEMO_MUSIC_LANDSCAPE)
#endif
#define LV_DEMO_LIST_CTRL_OVERLAP  60
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t * _lv_demo_music_main_create(lv_obj_t * parent);
void _lv_demo_music_play(uint32_t id);
void _lv_demo_music_resume(void);
void _lv_demo_music_pause(void);
void _lv_demo_music_album_next(bool next);

/**********************
 *      MACROS
 **********************/
#endif /*LV_USE_DEMO_MUSIC*/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DEMO_MUSIC_MAIN_H*/
