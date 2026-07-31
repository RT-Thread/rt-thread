/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-10      Sherman      first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#define RA_SRAM_SIZE 660
#define RA_SRAM_END  (0x20000000 + 0x000a5000)

#ifdef __ARMCC_VERSION
extern int Image$$RAM_END$$ZI$$Base;
#define HEAP_BEGIN ((void *)&Image$$RAM_END$$ZI$$Base)
#elif __ICCARM__
#pragma section = "CSTACK"
#define HEAP_BEGIN (__segment_end("CSTACK"))
#else
extern int __RAM_segment_used_end__;
#define HEAP_BEGIN (&__RAM_segment_used_end__)
#endif

#define HEAP_END RA_SRAM_END

#ifdef BSP_USING_GPIO_W
#define R_IOPORT_Open                 R_GPIO_W_Open
#define R_IOPORT_Close                R_GPIO_W_Close
#define R_IOPORT_PinsCfg              R_GPIO_W_PinsCfg
#define R_IOPORT_PinCfg               R_GPIO_W_PinCfg
#define R_IOPORT_PinRead              R_GPIO_W_PinRead
#define R_IOPORT_PinWrite             R_GPIO_W_PinWrite
#define R_IOPORT_PortDirectionSet     R_GPIO_W_PortDirectionSet
#define R_IOPORT_PortEventInputRead   R_GPIO_W_PortEventInputRead
#define R_IOPORT_PortEventOutputWrite R_GPIO_W_PortEventOutputWrite
#define R_IOPORT_PortRead             R_GPIO_W_PortRead
#define R_IOPORT_PortWrite            R_GPIO_W_PortWrite

#define g_ioport      g_gpio_w
#define g_ioport_ctrl g_gpio_w_ctrl
int rt_hw_pin_init(void);
#endif

#ifdef __cplusplus
}
#endif

#endif

