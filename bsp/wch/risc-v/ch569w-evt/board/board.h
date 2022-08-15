/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-15     Emuzit            first version
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdint.h>
#include "ch56x_sys.h"
#include "ch56x_gpio.h"
#include "ch56x_spi.h"
#include "ch56x_pwm.h"

#define LED0_PIN            GET_PIN(B, 24)
#define LED1_PIN            GET_PIN(B, 22)
#define LED2_PIN            GET_PIN(B, 23)

#define W25Q32_CS_PIN       GET_PIN(A, 12)
#define W25Q32_SPI_NAME     "spi00"

#define SYS_HCLK_FREQ       80000000  // 80 MHz

#define RAMX_SIZE           32  // USER_MEM 00/01/1x : 32/64/96 KB
#define RAMX_END            (RAMX_BASE_ADDRESS + RAMX_SIZE * 1024)

extern uint32_t _ebss, _heap_end;
extern uint32_t _susrstack, _eusrstack;

#define HEAP_BEGIN          ((void *)&_ebss)
#define HEAP_END            ((void *)&_heap_end)
#define SUSRSTACK           ((void *)&_susrstack)
#define EUSRSTACK           ((void *)&_eusrstack)

void rt_hw_board_init(void);

#endif /* __BOARD_H__ */
