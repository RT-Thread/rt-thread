/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     The first version
 */
#include <lvgl.h>
#include <rtdevice.h>
#include <drv_gpio.h>

#define BUTTON0_PIN        GET_PIN(D, 10)
#define BUTTON1_PIN        GET_PIN(D, 9)
#define BUTTON2_PIN        GET_PIN(D, 8)
#define BUTTON_WKUP_PIN    GET_PIN(C, 13)

lv_indev_t * button_indev;

/*Test if `id` button is pressed or not*/
static bool button_is_pressed(uint8_t id)
{
    switch(id)
    {
    case 0:
        if(rt_pin_read(BUTTON0_PIN) == PIN_LOW)
            return true;
        break;
    case 1:
        if(rt_pin_read(BUTTON1_PIN) == PIN_LOW)
            return true;
        break;
    case 2:
        if(rt_pin_read(BUTTON2_PIN) == PIN_LOW)
            return true;
        break;
    case 3:
        if(rt_pin_read(BUTTON_WKUP_PIN) == PIN_HIGH)
            return true;
        break;
    }

    return false;
}

static int8_t button_get_pressed_id(void)
{
    uint8_t i;

    /*Check to buttons see which is being pressed*/
    for(i = 0; i < 4; i++)
    {
        /*Return the pressed button's ID*/
        if(button_is_pressed(i))
        {
            return i;
        }
    }

    /*No button pressed*/
    return -1;
}

void button_read(lv_indev_drv_t * drv, lv_indev_data_t*data)
{
    static uint32_t last_btn = 0;   /*Store the last pressed button*/
    int btn_pr = button_get_pressed_id(); /*Get the ID (0,1,2...) of the pressed button*/
    if(btn_pr >= 0)
    {               /*Is there a button press? (E.g. -1 indicated no button was pressed)*/
       last_btn = btn_pr;           /*Save the ID of the pressed button*/
       data->state = LV_INDEV_STATE_PRESSED;  /*Set the pressed state*/
    }
    else
    {
       data->state = LV_INDEV_STATE_RELEASED; /*Set the released state*/
    }

    data->btn_id = last_btn;            /*Save the last button*/
}

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;
    /*assign buttons to coordinates*/
    static lv_point_t points_array[] =  {{200,35},{0,0},{70,35},{0,0}};

    /* Initialize the on-board buttons */
    rt_pin_mode(BUTTON0_PIN, PIN_MODE_INPUT);
    rt_pin_mode(BUTTON1_PIN, PIN_MODE_INPUT);
    rt_pin_mode(BUTTON2_PIN, PIN_MODE_INPUT);
    rt_pin_mode(BUTTON_WKUP_PIN, PIN_MODE_INPUT);

    lv_indev_drv_init(&indev_drv);      /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_BUTTON;
    indev_drv.read_cb = button_read;

    /*Register the driver in LVGL and save the created input device object*/
    button_indev = lv_indev_drv_register(&indev_drv);

    lv_indev_set_button_points(button_indev, points_array);
}
