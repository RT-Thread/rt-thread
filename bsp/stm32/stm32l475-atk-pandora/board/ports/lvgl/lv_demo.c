/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-17     Meco Man      First version
 */

#include <rtthread.h>
#include <lvgl.h>

#ifndef LV_THREAD_STACK_SIZE
#define LV_THREAD_STACK_SIZE 2048
#endif

#ifndef LV_THREAD_PRIO
#define LV_THREAD_PRIO (RT_THREAD_PRIORITY_MAX*2/3)
#endif

static void lv_example_get_started_1(void);
static void lv_example_get_started_3(void);

static void lvgl_thread(void *parameter)
{
    lv_example_get_started_1();
    lv_example_get_started_3();

    while(1)
    {
        lv_task_handler();
        rt_thread_mdelay(10);
    }
}

static int lvgl_demo_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("lvgl", lvgl_thread, RT_NULL, LV_THREAD_STACK_SIZE, LV_THREAD_PRIO, 0);
    rt_thread_startup(tid);

    return 0;
}
INIT_APP_EXPORT(lvgl_demo_init);

/* ------------------- demo1 ----------------------- */

static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
}

/**
 * Create a button with a label and react on click event.
 */
static void lv_example_get_started_1(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/
    lv_obj_center(label);
}

/* ------------------- demo3 ----------------------- */

static lv_obj_t * label;

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);

    /*Refresh the text*/
    lv_label_set_text_fmt(label, "%d", (int)lv_slider_get_value(slider));
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}

/**
 * Create a slider and write its value on a label.
 */
static void lv_example_get_started_3(void)
{
    /*Create a slider in the center of the display*/
    lv_obj_t * slider = lv_slider_create(lv_scr_act());
    lv_obj_set_width(slider, 200);                          /*Set the width*/
    lv_obj_center(slider);                                  /*Align to the center of the parent (screen)*/
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);     /*Assign an event function*/

    /*Create a label below the slider*/
    label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "0");
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}
