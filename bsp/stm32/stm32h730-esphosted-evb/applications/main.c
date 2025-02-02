/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-2-2       yekai        first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define LED_PIN    GET_PIN(E, 2)

int main(void) {
    /* set GPIO pin mode to output */
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    // this would be configured in bootloader
    uint32_t pwr_supply_conf = HAL_PWREx_GetSupplyConfig();
    if (pwr_supply_conf & PWR_CR3_LDOEN) {
        rt_kprintf("Vcore Power supply is LDO\r\n");
    }
    if (pwr_supply_conf & PWR_CR3_BYPASS) {
        rt_kprintf("Vcore Power supply is Bypass\r\n");
    }

    uint32_t freq = HAL_RCC_GetSysClockFreq();
    rt_kprintf("System Clock: %luMHz\r\n", freq / (int) 1e6);

    while (1) {
        rt_pin_write(LED_PIN, !rt_pin_read(LED_PIN));
        rt_kprintf("Hello RT-Thread\r\n");
        rt_thread_mdelay(1000);
    }
}
