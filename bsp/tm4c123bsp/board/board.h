/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#ifndef   __BOARD_H__
#define   __BOARD_H__

#include <rthw.h>
#include <rtthread.h>

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    #define TM4C123_SRAM1_START              (0x20000000)
    #define TM4C123_SRAM1_END                (TM4C123_SRAM1_START + 32 * 1024)   // end address = 0x20000000(base adddress) + 32K(RAM size)

    #if defined(__ARMCC_VERSION)
        extern int Image$$RW_IRAM$$ZI$$Limit;                   // RW_IRAM
        #define HEAP_BEGIN      ((void *)&Image$$RW_IRAM$$ZI$$Limit)
    #elif __ICCARM__
        #pragma section="HEAP"
        #define HEAP_BEGIN  (__segment_end("HEAP"))
    #else
        extern int _ebss;
        #define HEAP_BEGIN  ((void *)&_ebss)
    #endif
    #define HEAP_END                       TM4C123_SRAM1_END
#endif

#ifdef RT_USING_PIN
    #include "drv_gpio.h"
#endif /* RT_USING_PIN */

#ifdef RT_USING_SERIAL
    #include "drv_uart.h"
#endif /* RT_USING_SERIAL */

#ifdef RT_USING_PWM
    #include "drv_pwm.h"
#endif /* RT_USING_PWM*/

#ifdef RT_USING_SPI
    #include "drv_spi.h"
#endif /* RT_USING_SPI*/

#ifdef RT_USING_I2C
#include "drv_i2c.h"
#endif /* RT_USING_I2C*/

#endif /*__BOARD_H__*/

/************************** end of file ******************/
