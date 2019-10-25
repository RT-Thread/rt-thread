/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2010-02-04     Magicoe      add board.h to LPC176x bsp
 * 2013-12-18     Bernard      porting to LPC4088 bsp
 * 2017-08-02     XiaoYang     porting to LPC54608 bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__


#include <stdint.h>

#include <rtthread.h>

#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_reset.h"
#include "fsl_gpio.h"
#include "fsl_iocon.h"
#include "pin_mux.h"

// <RDTConfigurator URL="http://www.rt-thread.com/eclipse">

// </RDTConfigurator>
#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern int Image$$ARM_LIB_HEAP$$ZI$$Base;
#define HEAP_BEGIN  ((void *)&Image$$ARM_LIB_HEAP$$ZI$$Base)
#elif defined(__ICCARM__)
#pragma section="HEAP"
#define HEAP_BEGIN  (__segment_end("HEAP"))
#elif defined(__GNUC__)
extern int __bss_end;
#define HEAP_BEGIN  ((void *)&__bss_end)
#endif
#define HEAP_END    (void*)(0x20000000 + 0x40000)

void rt_hw_board_init(void);

#define BOARD_SDIF_BASEADDR SDIF
#define BOARD_SDIF_CLKSRC kCLOCK_SDio
#define BOARD_SDIF_CLK_FREQ CLOCK_GetFreq(kCLOCK_SDio)
#define BOARD_SDIF_CLK_ATTACH kMAIN_CLK_to_SDIO_CLK
#define BOARD_SDIF_IRQ SDIO_IRQn
#define BOARD_MMC_VCC_SUPPLY kMMC_VoltageWindows270to360
#define BOARD_SD_CARD_DETECT_PIN 17
#define BOARD_SD_CARD_DETECT_PORT 0
#define BOARD_SD_CARD_DETECT_GPIO GPIO
#define BOARD_SD_DETECT_TYPE kSDMMCHOST_DetectCardByHostCD

#define BOARD_SDIF_CD_GPIO_INIT()                                                                    \
    {                                                                                                \
        CLOCK_EnableClock(kCLOCK_Gpio2);                                                             \
        GPIO_PinInit(BOARD_SD_CARD_DETECT_GPIO, BOARD_SD_CARD_DETECT_PORT, BOARD_SD_CARD_DETECT_PIN, \
                     &(gpio_pin_config_t){kGPIO_DigitalInput, 0U});                                  \
    }
#define BOARD_SDIF_CD_STATUS() \
    GPIO_PinRead(BOARD_SD_CARD_DETECT_GPIO, BOARD_SD_CARD_DETECT_PORT, BOARD_SD_CARD_DETECT_PIN)

#endif


