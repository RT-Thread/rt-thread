/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-15     yby          the first version
 */

#ifndef   __BOARD_H__
#define   __BOARD_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <msp.h>
#include "hw_sysctl.h"
#include "sysctl.h"
#include "systick.h"
#include "gpio.h"
#include "pin_map.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MSP432_FLASH_START_ADRESS     ((rt_uint32_t)0x00000000)
#define MSP432_FLASH_SIZE             (1024 * 1024)
#define MSP432_FLASH_END_ADDRESS      ((rt_uint32_t)(MSP432_FLASH_START_ADRESS + MSP432_FLASH_SIZE))

#define MSP432_SRAM_SIZE      256
#define MSP432_SRAM_END       (0x20000000 + MSP432_SRAM_SIZE * 1024)

#if defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN      (__segment_end("HEAP"))
#else
extern int __end;
#define HEAP_BEGIN      ((void *)&__end)
#endif

#define HEAP_END        MSP432_SRAM_END

void uart_hw_config(void);

#ifdef RT_USING_PIN
#include "drv_gpio.h"
#endif /* RT_USING_PIN */

#ifdef RT_USING_SERIAL
#include "drv_uart.h"
#endif /* RT_USING_SERIAL */

#ifdef __cplusplus
}
#endif

#endif /*__BOARD_H__*/
