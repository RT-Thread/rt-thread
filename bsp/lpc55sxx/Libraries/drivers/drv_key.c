/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-19     Magicoe      The first version for LPC55S6x, refered github.com/Guozhanxin/RTT-BeepPlayer-pkg
 */

#include <rtthread.h>

#include "rtconfig.h"

#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_gpio.h"
#include "fsl_inputmux.h"
#include "drv_key.h"

/****    Debug     ****/
#define DBG_ENABLE
#define DBG_SECTION_NAME "button"
#define DBG_LEVEL        DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

#define MY_BUTTON_CALL(func, argv) \
    do { if ((func) != RT_NULL) func argv; } while (0)

struct my_button_manage
{
    rt_uint8_t num;
    rt_timer_t timer;
    struct my_button *button_list[MY_BUTTON_LIST_MAX];
};

static struct my_button_manage button_manage;

int my_button_register(struct my_button *button)
{
    if (button->press_logic_level == 0)
    {
        rt_pin_mode(button->pin, PIN_MODE_INPUT_PULLUP);
    }
    else
    {
        rt_pin_mode(button->pin, PIN_MODE_INPUT_PULLDOWN);
    }

    button->cnt = 0;
    button->event = BUTTON_EVENT_NONE;
    button_manage.button_list[button_manage.num++] = button;

    return 0;
}

static void my_button_scan(void *param)
{
    rt_uint8_t i;
    rt_uint16_t cnt_old;

    for (i = 0; i < button_manage.num; i++)
    {
        cnt_old = button_manage.button_list[i]->cnt;

        if (rt_pin_read(button_manage.button_list[i]->pin) == button_manage.button_list[i]->press_logic_level)
        {
            button_manage.button_list[i]->cnt ++;

            if (button_manage.button_list[i]->cnt == MY_BUTTON_DOWN_MS / MY_BUTTON_SCAN_SPACE_MS) /* BUTTON_DOWN */
            {
                LOG_D("BUTTON_DOWN");
                button_manage.button_list[i]->event = BUTTON_EVENT_CLICK_DOWN;
                MY_BUTTON_CALL(button_manage.button_list[i]->cb, (button_manage.button_list[i]));
            }
            else if (button_manage.button_list[i]->cnt == MY_BUTTON_HOLD_MS / MY_BUTTON_SCAN_SPACE_MS) /* BUTTON_HOLD */
            {
                LOG_D("BUTTON_HOLD");
                button_manage.button_list[i]->event = BUTTON_EVENT_HOLD;
                MY_BUTTON_CALL(button_manage.button_list[i]->cb, (button_manage.button_list[i]));
            }
            else if (button_manage.button_list[i]->cnt > MY_BUTTON_HOLD_MS / MY_BUTTON_SCAN_SPACE_MS) /* BUTTON_HOLD_CYC */
            {
                LOG_D("BUTTON_HOLD_CYC");
                button_manage.button_list[i]->event = BUTTON_EVENT_HOLD_CYC;
                if (button_manage.button_list[i]->hold_cyc_period && button_manage.button_list[i]->cnt % (button_manage.button_list[i]->hold_cyc_period / MY_BUTTON_SCAN_SPACE_MS) == 0)
                    MY_BUTTON_CALL(button_manage.button_list[i]->cb, (button_manage.button_list[i]));
            }
        }
        else
        {
            button_manage.button_list[i]->cnt = 0;
            if (cnt_old >= MY_BUTTON_DOWN_MS / MY_BUTTON_SCAN_SPACE_MS && cnt_old < MY_BUTTON_HOLD_MS / MY_BUTTON_SCAN_SPACE_MS) /* BUTTON_CLICK_UP */
            {
                LOG_D("BUTTON_CLICK_UP");
                button_manage.button_list[i]->event = BUTTON_EVENT_CLICK_UP;
                MY_BUTTON_CALL(button_manage.button_list[i]->cb, (button_manage.button_list[i]));
            }
            else if (cnt_old >= MY_BUTTON_HOLD_MS / MY_BUTTON_SCAN_SPACE_MS) /* BUTTON_HOLD_UP */
            {
                LOG_D("BUTTON_HOLD_UP");
                button_manage.button_list[i]->event = BUTTON_EVENT_HOLD_UP;
                MY_BUTTON_CALL(button_manage.button_list[i]->cb, (button_manage.button_list[i]));
            }
        }
    }
}

int my_button_start(void)
{
    if (button_manage.timer != RT_NULL)
        return -1;

    /* Create Timer 1 */
    button_manage.timer = rt_timer_create("timer1", /* Timer name is: timer1 */
                             my_button_scan,        /* Timeout callback func */
                             RT_NULL,               /* Timeout func entry */
                             RT_TICK_PER_SECOND * MY_BUTTON_SCAN_SPACE_MS / 1000,
                             RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);
    /* Start Timer */
    if (button_manage.timer != RT_NULL)
        rt_timer_start(button_manage.timer);

    return 0;
}

#ifdef RT_USING_FINSH
#include <finsh.h>

#ifdef FINSH_USING_MSH

#define KEY_PIN          51
#define KEY_PRESS_VALUE  0

void key_cb(struct my_button *button)
{
    switch (button->event)
    {
    case BUTTON_EVENT_CLICK_UP:
        rt_kprintf("This is click up callback!\n");
        break;
    case BUTTON_EVENT_HOLD_CYC:
        rt_kprintf("This is hold cyc callback!\n");
        break;
    default:
        ;
    }
}

void key_test(rt_uint32_t led_num, rt_uint32_t value)
{
    /* user app entry */
    static struct my_button key = {0};

    key.press_logic_level = KEY_PRESS_VALUE;
    key.hold_cyc_period = 100;
    key.cb = (my_button_callback)key_cb;
    key.pin = KEY_PIN;

    my_button_register(&key);

    my_button_start();
}
MSH_CMD_EXPORT(key_test, key_test);

#endif /* FINSH_USING_MSH */
#endif /* RT_USING_FINSH */
