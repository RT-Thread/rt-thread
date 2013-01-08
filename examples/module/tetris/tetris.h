/*
 * File      : tetris_modal.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-08-14     Yi.Qiu       first version
 */

 #include <rtthread.h>

 struct rt_tetris;
 typedef struct rt_tetris rt_tetris_t;

 struct rt_tetris_view;
 typedef struct rt_tetris_view rt_tetris_view_t;

 typedef rt_err_t (*on_update)(rt_tetris_view_t* thiz, rt_tetris_t* tetris);

 struct rt_tetris_view
 {
 	rt_uint32_t width;
	rt_uint32_t height;

	on_update update;
	on_update update_next_brick;
	on_update update_level;
	on_update update_score_and_lines;
	void *private;
 };
 
 rt_tetris_t* rt_tetris_create(rt_uint32_t width, rt_uint32_t height);
 rt_err_t rt_tetris_destory(rt_tetris_t* thiz);
 rt_err_t rt_tetris_start(rt_tetris_t* thiz);
 rt_err_t rt_tetris_pause(rt_tetris_t* thiz);
 rt_uint32_t rt_tetris_width(rt_tetris_t* thiz);
 rt_uint32_t* rt_tetris_next_brick(rt_tetris_t* thiz);
 rt_uint32_t rt_tetris_level(rt_tetris_t* thiz);
 rt_uint32_t rt_tetris_lines(rt_tetris_t* thiz);
 rt_uint32_t rt_tetris_score(rt_tetris_t* thiz);
 rt_uint32_t rt_tetris_height(rt_tetris_t* thiz);
 rt_bool_t rt_tetris_status(rt_tetris_t* thiz);
 rt_err_t rt_tetris_down(rt_tetris_t* thiz);
 rt_err_t rt_tetris_left(rt_tetris_t* thiz);
 rt_err_t rt_tetris_right(rt_tetris_t* thiz);
 rt_err_t rt_tetris_drop(rt_tetris_t* thiz);
 rt_err_t rt_tetris_rotate(rt_tetris_t* thiz, rt_bool_t direction);
 rt_err_t rt_tetris_add_view(rt_tetris_t* thiz, rt_tetris_view_t* view);
 rt_err_t rt_tetris_delete_view(rt_tetris_t* thiz, rt_tetris_view_t* view);
 rt_err_t rt_tetris_check_collision(rt_tetris_t* thiz, rt_uint32_t block);

 rt_tetris_view_t* rt_tetris_view_create(void* private);
 rt_err_t rt_tetris_view_destroy(rt_tetris_view_t* thiz);

void tetris_ui_entry(void* parameter);

