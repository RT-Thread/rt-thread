/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-11     enkiller     first version
 */

#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "drv_gpio.h"

static void _delay_us(rt_uint32_t ns)
{
    volatile rt_uint16_t    delay;

    while(ns--)
    {
        delay = 200;
        while(delay--);
    }
}

static void _delay_ms(rt_uint32_t ms)
{
    volatile rt_uint16_t    delay;

    while(ms--)
    {
        _delay_us(1000);
    }
}

#if defined(RT_USING_WIFI) && (defined(WIFI_USING_AP6212) || defined(WIFI_USING_AP6181))
/**
 * PC16 WL_WAKE_HOST
 * PC17 WL_REG_EN
 */
int io_AP6212(void)
{
    gpio_set_func(GPIO_PORT_C, GPIO_Pin_17, GPIO_FUNC_0);
    gpio_direction_output(GPIO_PORT_C, GPIO_Pin_17, 0);

    rt_kprintf("Enable WL_REG_EN\n");
    gpio_set_value(GPIO_PORT_C, GPIO_Pin_17, 0);
    rt_thread_delay(1);
    gpio_set_value(GPIO_PORT_C, GPIO_Pin_17, 1);

    return 0;
}
INIT_DEVICE_EXPORT(io_AP6212);
#endif

#if defined(RT_USING_BT) && (defined(WIFI_USING_AP6212) || defined(WIFI_USING_AP6181))
#include <drv_rtc.h>
/**
 * PC16 32768 clock
 */
int io_AP6212_bt(void)
{
    rtc32k_enable();

    return 0;
}
INIT_DEVICE_EXPORT(io_AP6212_bt);
#endif

#if defined(BOARD_HALLEY2)
int io_halley2(void)
{
#ifdef RT_USING_EMAC
    /* PC23 for MAC_RST_N */
    gpio_set_func(GPIO_PORT_C, GPIO_Pin_23, GPIO_FUNC_0);
    gpio_direction_output(GPIO_PORT_C, GPIO_Pin_23, 0);
    rt_thread_delay(1);
    gpio_direction_output(GPIO_PORT_C, GPIO_Pin_23, 1);
    rt_thread_delay(1);
#endif

    return 0;
}
INIT_DEVICE_EXPORT(io_halley2);
#endif

#if defined(BOARD_PHOENIX)
int io_phoenix(void)
{
    /* PB0(1) for Audio Shutdown IO */
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_0, GPIO_FUNC_2);
    gpio_direction_output(GPIO_PORT_B,GPIO_Pin_0, 0);
    gpio_set_value(GPIO_PORT_B,GPIO_Pin_0,0);

    /* PB3 for reset EMAC PHY */
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_3, GPIO_FUNC_2);
    gpio_direction_output(GPIO_PORT_B, GPIO_Pin_3, 0);
    rt_thread_delay(1);
    gpio_direction_output(GPIO_PORT_B, GPIO_Pin_3, 1);
    rt_thread_delay(1);

    return 0;
}
INIT_DEVICE_EXPORT(io_phoenix);
#endif

#ifdef BOARD_HALLEY2_REALBOARD
int io_realboard(void)
{
    /* Audio Shutdown IO */
    gpio_direction_output(AUDIO_SHUTDOWN_PORT,AUDIO_SHUTDOWN_PIN, AUDIO_SHUTDOWN_MUTE);
    gpio_set_value(AUDIO_SHUTDOWN_PORT,AUDIO_SHUTDOWN_PIN, AUDIO_SHUTDOWN_MUTE);

#ifdef RT_USING_EMAC
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_7,  GPIO_OUTPUT0);
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_8,  GPIO_OUTPUT0);
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_9,  GPIO_OUTPUT0);
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_10, GPIO_OUTPUT0);
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_11, GPIO_OUTPUT0);
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_12, GPIO_OUTPUT0);
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_13, GPIO_INPUT);
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_14, GPIO_INPUT);
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_15, GPIO_INPUT);

    /* PC23 for MAC_RST_N */
    gpio_direction_output(GPIO_PORT_C, GPIO_Pin_23, 0);
    _delay_ms(100);
    gpio_direction_output(GPIO_PORT_C, GPIO_Pin_23, 1);
    _delay_ms(100);
#endif
    return 0;
}
INIT_BOARD_EXPORT(io_realboard);
#endif /* BOARD_HALLEY2_REALBOARD_X1000 */

#ifdef BOARD_HALLEY2_REALBOARD_V2
int io_realboard_v2(void)
{
    /* Audio Shutdown IO */
    gpio_direction_output(AUDIO_SHUTDOWN_PORT,AUDIO_SHUTDOWN_PIN, AUDIO_SHUTDOWN_MUTE);
    gpio_set_value(AUDIO_SHUTDOWN_PORT,AUDIO_SHUTDOWN_PIN, AUDIO_SHUTDOWN_MUTE);

#ifdef RT_USING_TOUCH
    /* Reset LCD */
    gpio_direction_output(LCD_TP_INT_PORT, LCD_TP_INT_PIN,1);
    _delay_ms(300);
#endif
#ifdef RT_USING_SLCD
    /* Reset TP */
    gpio_direction_output(LCD_RST_PORT, LCD_RST_PIN,0);
    _delay_ms(100);
    gpio_set_value(LCD_RST_PORT, LCD_RST_PIN, 1);
#endif

    /* LED */
    gpio_direction_output(BLINK_LED0_PORT, BLINK_LED0_PIN,1);
    gpio_direction_output(BLINK_LED1_PORT, BLINK_LED1_PIN,1);
    gpio_direction_output(BLINK_LED2_PORT, BLINK_LED2_PIN,1);
    gpio_direction_output(BLINK_LED3_PORT, BLINK_LED3_PIN,1);

    return 0;
}
INIT_BOARD_EXPORT(io_realboard_v2);
#endif /* BOARD_HALLEY2_REALBOARD_V2 */

#ifdef BOARD_HALLEY2_FIR
int io_halley2_fir(void)
{
    /* Audio Shutdown IO */
    gpio_direction_output(AUDIO_SHUTDOWN_PORT,AUDIO_SHUTDOWN_PIN, AUDIO_SHUTDOWN_MUTE);

    /* LCD */
    rt_kprintf("lcd power enable...\n");
    gpio_direction_output(LCD_PWEN_PORT,LCD_PWEN_PIN, 0);   //LCD Power Enable
    gpio_direction_output(LCD_RST_PORT,LCD_RST_PIN, 0);
    gpio_direction_output(LCD_BL_PORT,LCD_BL_PIN, 0);

    /* Touch */
    gpio_direction_output(TP_PWEN_PORT,TP_PWEN_PIN, 0);
    gpio_direction_output(TP_RST_PORT,TP_RST_PIN, 0);

    /* LED */
    gpio_direction_output(LED_BT_PORT,LED_BT_PIN, 1);
    gpio_direction_output(LED_WIFI_PORT,LED_WIFI_PIN, 1);
    gpio_direction_output(LED_ZB_PORT,LED_ZB_PIN, 1);

    return 0;
}
INIT_BOARD_EXPORT(io_halley2_fir);
#endif /* BOARD_HALLEY2_FIR */
