/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-04-17     Meco Man          first version
 */
#include <rtthread.h>

#ifdef BSP_USING_KEY
#define DBG_TAG    "KEY"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>
#include <rtdevice.h>
#include <drv_gpio.h>
#include <multi_button.h>

#define KEY0_PIN        GET_PIN(D, 10)
#define KEY1_PIN        GET_PIN(D, 9)
#define KEY2_PIN        GET_PIN(D, 8)
#define KEY_WKUP_PIN    GET_PIN(C, 13)

static struct rt_timer key_timer;

static struct button key0;
static struct button key1;
static struct button key2;
static struct button key_wkup;

/*---- user codes area begin ----*/
/*users can modify according to needs*/
static void key0_BtnCallback(void* state)
{
    rt_kprintf("key0!\n");
}

static void key1_BtnCallback(void* state)
{
    rt_kprintf("key1!\n");
}

static void key2_BtnCallback(void* state)
{
    rt_kprintf("key2!\n");
}

static void key_wkup_BtnCallback(void* state)
{
    rt_kprintf("key wkup!\n");
}
/*---- user codes area end ----*/

static void _cb_key_timer(void *parameter)
{
    button_ticks();
}

static uint8_t _cb_key0_pin_level(void)
{
    return rt_pin_read(KEY0_PIN);
}

static uint8_t _cb_key1_pin_level(void)
{
    return rt_pin_read(KEY1_PIN);
}

static uint8_t _cb_key2_pin_level(void)
{
    return rt_pin_read(KEY2_PIN);
}

static uint8_t _cb_key_wkup_pin_level(void)
{
    return rt_pin_read(KEY_WKUP_PIN);
}

static int onboard_key_init(void)
{
    rt_timer_init(&key_timer,
                  "key timer",
                  _cb_key_timer,
                  RT_NULL,
                  rt_tick_from_millisecond(TICKS_INTERVAL),
                  RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);

    if(rt_timer_start(&key_timer) < 0)
    {
        LOG_E("drv_key timer initialization failed");
        return -1;
    }

    rt_pin_mode(KEY0_PIN, PIN_MODE_INPUT);
    rt_pin_mode(KEY1_PIN, PIN_MODE_INPUT);
    rt_pin_mode(KEY2_PIN, PIN_MODE_INPUT);
    rt_pin_mode(KEY_WKUP_PIN, PIN_MODE_INPUT);

    button_init(&key0, _cb_key0_pin_level, PIN_LOW);
    button_init(&key1, _cb_key1_pin_level, PIN_LOW);
    button_init(&key2, _cb_key2_pin_level, PIN_LOW);
    button_init(&key_wkup, _cb_key_wkup_pin_level, PIN_HIGH);

    /*---- user codes area begin ----*/
    /*users can modify according to needs*/
    button_attach(&key0, PRESS_DOWN, key0_BtnCallback);
    button_attach(&key1, PRESS_DOWN, key1_BtnCallback);
    button_attach(&key2, PRESS_DOWN, key2_BtnCallback);
    button_attach(&key_wkup, PRESS_UP, key_wkup_BtnCallback);
    /*---- user codes area end ----*/

    button_start(&key0);
    button_start(&key1);
    button_start(&key2);
    button_start(&key_wkup);

    return 0;
}
INIT_APP_EXPORT(onboard_key_init);

#endif
