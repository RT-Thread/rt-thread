/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-04     Haley        the first version
 */

#ifndef __FLASH_H_
#define __FLASH_H_

#include <rtthread.h>

/* Erase feature struct define */
struct rom_control_erase
{
    rt_uint8_t        type;
    rt_uint32_t       addrstart;
    rt_uint32_t       pagenums;
};

/**
 * @brief External function definitions
 *
 */
int rt_hw_rom_init(void);

#endif // __FLASH_H_
