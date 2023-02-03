/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-29     Rbb666       first version
 * 2022-07-26     Rbb666       Add Flash Config
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "drv_common.h"
#include "drv_gpio.h"

#include "cy_result.h"
#include "cybsp_types.h"
#include "cyhal.h"
#include "cybsp.h"

#ifdef BSP_USING_USBD
    #include "cy_usb_dev.h"
    #include "cy_usb_dev_hid.h"
    #include "cycfg_usbdev.h"
#endif

/*SRAM CONFIG*/
#define IFX_SRAM_SIZE                   (277)
#define IFX_SRAM_END                    (0x08002000 + IFX_SRAM_SIZE * 1024)

#ifdef __ARMCC_VERSION
    extern int Image$$RW_IRAM1$$ZI$$Limit;
    #define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
    #define HEAP_END        IFX_SRAM_END
#elif __ICCARM__
    #pragma section="HEAP"
    #define HEAP_BEGIN    (__segment_end("HEAP"))
#else
    extern unsigned int __end__;
    extern unsigned int __HeapLimit;
    #define HEAP_BEGIN    (void*)&__end__
    #define HEAP_END      (void*)&__HeapLimit
#endif

void cy_bsp_all_init(void);

#endif

