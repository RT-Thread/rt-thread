/*
 * Copyright (c) 2021-2022 HPMicro
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "rtt_board.h"
#include "hpm_uart_drv.h"
#include "hpm_gpio_drv.h"
#include "hpm_mchtmr_drv.h"
#include "hpm_pmp_drv.h"
#include "assert.h"
#include "hpm_clock_drv.h"
#include "hpm_sysctl_drv.h"
#include <rthw.h>
#include <rtthread.h>
#include "hpm_dma_manager.h"

void os_tick_config(void);

extern int rt_hw_uart_init(void);

void rtt_board_init(void)
{
    board_init_clock();
    board_init_console();
    board_init_pmp();

    dma_manager_init();

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
    gpio_set_pin_output(BOARD_LED_GPIO_CTRL, BOARD_LED_GPIO_INDEX, BOARD_LED_GPIO_PIN);
    gpio_write_pin(BOARD_LED_GPIO_CTRL, BOARD_LED_GPIO_INDEX, BOARD_LED_GPIO_PIN, BOARD_LED_OFF_LEVEL);
}

void app_led_write(uint32_t index, bool state)
{
   gpio_write_pin(BOARD_LED_GPIO_CTRL, BOARD_LED_GPIO_INDEX, BOARD_LED_GPIO_PIN, state);
}


void BOARD_LED_write(uint32_t index, bool state)
{
    switch (index)
    {
    case 0:
        gpio_write_pin(BOARD_LED_GPIO_CTRL, BOARD_LED_GPIO_INDEX, BOARD_LED_GPIO_PIN, state);
        break;
    default:
        /* Suppress the toolchain warnings */
        break;
    }
}

void os_tick_config(void)
{
    sysctl_config_clock(HPM_SYSCTL, clock_node_mchtmr0, clock_source_osc0_clk0, 1);
    sysctl_add_resource_to_cpu0(HPM_SYSCTL, sysctl_resource_mchtmr0);

    mchtmr_set_compare_value(HPM_MCHTMR, BOARD_MCHTMR_FREQ_IN_HZ / RT_TICK_PER_SECOND);

    enable_mchtmr_irq();
}

void rt_hw_board_init(void)
{
    rtt_board_init();

    /* Call the RT-Thread Component Board Initialization */
    rt_components_board_init();
}

void rt_hw_console_output(const char *str)
{
    while (*str != '\0')
    {
        uart_send_byte(BOARD_APP_UART_BASE, *str++);
    }
}

ATTR_PLACE_AT(".isr_vector") void mchtmr_isr(void)
{
    HPM_MCHTMR->MTIMECMP = HPM_MCHTMR->MTIME + BOARD_MCHTMR_FREQ_IN_HZ / RT_TICK_PER_SECOND;

    rt_interrupt_enter();
    rt_tick_increase();
    rt_interrupt_leave();
}

void rt_hw_us_delay(rt_uint32_t us)
{
    clock_cpu_delay_us(us);
}

void rt_hw_cpu_reset(void)
{
    HPM_PPOR->RESET_ENABLE = (1UL << 31);
    HPM_PPOR->RESET_HOT &= ~(1UL << 31);
    HPM_PPOR->RESET_COLD |= (1UL << 31);

    HPM_PPOR->SOFTWARE_RESET = 1000U;
    while(1) {

    }
}

MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reset, reset the board);
