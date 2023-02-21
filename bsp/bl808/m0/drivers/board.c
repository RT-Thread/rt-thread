/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022/12/25     flyingcys    first version
 * 2023/01/17     chushicheng  add pin and i2c
 */
#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"

static void sipeed_bl_sys_enabe_jtag(int cpuid)
{
    GLB_GPIO_Cfg_Type gpio_cfg;

    gpio_cfg.drive = 0;
    gpio_cfg.smtCtrl = 1;
    gpio_cfg.pullType = GPIO_PULL_NONE;

    gpio_cfg.gpioMode = GPIO_MODE_AF;
    switch (cpuid) {
        case 0: {
            gpio_cfg.gpioFun = GPIO_FUN_JTAG_M0;
        } break;
        case 1: {
            gpio_cfg.gpioFun = GPIO_FUN_JTAG_D0;
        } break;
        default: {
        } break;
    }
    gpio_cfg.gpioPin = GLB_GPIO_PIN_0;
    GLB_GPIO_Init(&gpio_cfg);

    gpio_cfg.gpioPin = GLB_GPIO_PIN_1;
    GLB_GPIO_Init(&gpio_cfg);

    gpio_cfg.gpioPin = GLB_GPIO_PIN_2;
    GLB_GPIO_Init(&gpio_cfg);

    gpio_cfg.gpioPin = GLB_GPIO_PIN_3;
    GLB_GPIO_Init(&gpio_cfg);
}

static void cmd_jtag_m0(void)
{
    sipeed_bl_sys_enabe_jtag(0);
}

static void cmd_jtag_cpu0(void)
{
    sipeed_bl_sys_enabe_jtag(1);
}

/* This is the timer interrupt service routine. */
static void mtime_handler(void)
{
    rt_tick_increase();

    csi_coret_config(CPU_Get_MTimer_Clock() / RT_TICK_PER_SECOND, MTIME_IRQn);
}

void rt_hw_board_init(void)
{
    bl_sys_lowlevel_init();

    csi_coret_config(CPU_Get_MTimer_Clock() / RT_TICK_PER_SECOND, MTIME_IRQn);
    bl_irq_register(MTIME_IRQn, mtime_handler);
    bl_irq_enable(MTIME_IRQn);

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

    /* GPIO driver initialization is open by default */
#ifdef RT_USING_PIN
    rt_hw_pin_init();
#endif

    /* I2C driver initialization is open by default */
#ifdef RT_USING_I2C
    rt_hw_i2c_init();
#endif

    /* UART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

    /* Set the shell console output device */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef BSP_USING_JTAG_M0
    cmd_jtag_m0();
#endif
}

void rt_hw_cpu_reset(void)
{
    bl_sys_reset_por();
    while(1);
}

MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reboot, reset machine);
