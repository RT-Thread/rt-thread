/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022/12/25     flyingcys    first version
 * 2023/03/15     flyingcys    update bsp file structure
 */

#ifndef BOARD_H__
#define BOARD_H__

#include <rtconfig.h>

#include "bflb_uart.h"
#include "bflb_gpio.h"
#include "bflb_clock.h"
#include "bflb_rtc.h"
#include "bflb_flash.h"
#include "bl808_glb.h"
#include "bl808_psram_uhs.h"
#include "bl808_tzc_sec.h"
#include "bl808_ef_cfg.h"
#include "bl808_uhs_phy.h"

#define CONFIG_D0_FLASH_ADDR             0x100000
#define CONFIG_LP_FLASH_ADDR             0x0C0000

extern uint8_t __HeapBase;
extern uint8_t __HeapLimit;

#define RT_HW_HEAP_BEGIN    (void*)&__HeapBase
#define RT_HW_HEAP_END      (void*)&__HeapLimit

void rt_hw_board_init(void);

#endif
