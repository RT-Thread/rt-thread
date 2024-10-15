/*
 * Copyright (c) 2023-2024 HPMicro
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "rtt_board.h"
#include "hpm_uart_drv.h"
#include "hpm_gpio_drv.h"
#include "hpm_pmp_drv.h"
#include "assert.h"
#include "hpm_clock_drv.h"
#include "hpm_sysctl_drv.h"
#include <rthw.h>
#include <rtthread.h>
#include "hpm_dma_mgr.h"
#include "hpm_mchtmr_drv.h"

extern int rt_hw_uart_init(void);
void os_tick_config(void);
void rtt_board_init(void);

void rt_hw_board_init(void)
{
    rtt_board_init();

    /* Call the RT-Thread Component Board Initialization */
    rt_components_board_init();
}

void os_tick_config(void)
{
    sysctl_config_clock(HPM_SYSCTL, clock_node_mchtmr0, clock_source_osc0_clk0, 1);
    sysctl_add_resource_to_cpu0(HPM_SYSCTL, sysctl_resource_mchtmr0);
    mchtmr_set_compare_value(HPM_MCHTMR, BOARD_MCHTMR_FREQ_IN_HZ / RT_TICK_PER_SECOND);
    enable_mchtmr_irq();
}

void rtt_board_init(void)
{
    board_init_clock();
    board_init_console();
    board_init_pmp();

    dma_mgr_init();

    /* initialize memory system */
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);

    /* Configure the OS Tick */
    os_tick_config();

    /* Initialize the UART driver first, because later driver initialization may require the rt_kprintf */
    rt_hw_uart_init();

    /* Set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}

void app_init_led_pins(void)
{
    gpio_set_pin_output(APP_LED0_GPIO_CTRL, APP_LED0_GPIO_INDEX, APP_LED0_GPIO_PIN);
    gpio_set_pin_output(APP_LED1_GPIO_CTRL, APP_LED1_GPIO_INDEX, APP_LED1_GPIO_PIN);
    gpio_set_pin_output(APP_LED2_GPIO_CTRL, APP_LED2_GPIO_INDEX, APP_LED2_GPIO_PIN);

    gpio_write_pin(APP_LED0_GPIO_CTRL, APP_LED0_GPIO_INDEX, APP_LED0_GPIO_PIN, APP_LED_OFF);
    gpio_write_pin(APP_LED1_GPIO_CTRL, APP_LED1_GPIO_INDEX, APP_LED1_GPIO_PIN, APP_LED_OFF);
    gpio_write_pin(APP_LED2_GPIO_CTRL, APP_LED2_GPIO_INDEX, APP_LED2_GPIO_PIN, APP_LED_OFF);
}

void app_led_write(uint32_t index, bool state)
{
    switch (index)
    {
    case 0:
        gpio_write_pin(APP_LED0_GPIO_CTRL, APP_LED0_GPIO_INDEX, APP_LED0_GPIO_PIN, state);
        break;
    case 1:
        gpio_write_pin(APP_LED1_GPIO_CTRL, APP_LED1_GPIO_INDEX, APP_LED1_GPIO_PIN, state);
        break;
    case 2:
        gpio_write_pin(APP_LED2_GPIO_CTRL, APP_LED2_GPIO_INDEX, APP_LED2_GPIO_PIN, state);
        break;
    default:
        /* Suppress the toolchain warnings */
        break;
    }
}

void rt_hw_console_output(const char *str)
{
    while (*str != '\0')
    {
        uart_send_byte(BOARD_APP_UART_BASE, *str++);
    }
}

void app_init_usb_pins(void)
{
    board_init_usb_pins();
}

ATTR_PLACE_AT(".isr_vector") void mchtmr_isr(void)
{
    HPM_MCHTMR->MTIMECMP = HPM_MCHTMR->MTIME + BOARD_MCHTMR_FREQ_IN_HZ / RT_TICK_PER_SECOND;

    rt_tick_increase();
}

void rt_hw_cpu_reset(void)
{
    HPM_PPOR->RESET_ENABLE = (1UL << 31);
    HPM_PPOR->SOFTWARE_RESET = 1000U;
    while(1) {

    }
}

MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reset, reset the board);

#ifdef RT_USING_CACHE
void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_FLUSH) {
        l1c_dc_flush((uint32_t)addr, size);
    } else {
        l1c_dc_invalidate((uint32_t)addr, size);
    }
}
#endif
