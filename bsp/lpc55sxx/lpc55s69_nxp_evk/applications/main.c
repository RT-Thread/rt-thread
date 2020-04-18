/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-24     Magicoe      first version
 * 2020-01-10     Kevin/Karl   Add PS demo
 *
 */

#include <rtdevice.h>
#include "drv_pin.h"

/* defined the LED pin: GPIO1_IO4 */
/* GPIO1_4 is Blue LED */
#define LEDB_PIN      GET_PINS(1, 4)

extern void protected_storage_demo_thread(void * parameters);

int main(void)
{
    rt_thread_t t_psa_ps_demo;

#if defined(__CC_ARM)
    rt_kprintf("using armcc, version: %d\n", __ARMCC_VERSION);
#elif defined(__CLANG_ARM)
    rt_kprintf("using armclang, version: %d\n", __ARMCC_VERSION);
#elif defined(__ICCARM__)
    rt_kprintf("using iccarm, version: %d\n", __VER__);
#elif defined(__GNUC__)
    rt_kprintf("using gcc, version: %d.%d\n", __GNUC__, __GNUC_MINOR__);
#endif

    t_psa_ps_demo = rt_thread_create("psa_ps_demo",
                                     protected_storage_demo_thread,
                                     RT_NULL,
                                     512,
                                     ( RT_MAIN_THREAD_PRIORITY - 1),
                                     50);
    if (t_psa_ps_demo != RT_NULL) rt_thread_startup(t_psa_ps_demo);

    rt_pin_mode(LEDB_PIN, PIN_MODE_OUTPUT);  /* Set GPIO as Output */
    while (1)
    {
        rt_pin_write(LEDB_PIN, PIN_HIGH);    /* Set GPIO output 1 */
        rt_thread_mdelay(500);               /* Delay 500mS */
        rt_pin_write(LEDB_PIN, PIN_LOW);     /* Set GPIO output 0 */
        rt_thread_mdelay(500);               /* Delay 500mS */
    }
}

// end file
