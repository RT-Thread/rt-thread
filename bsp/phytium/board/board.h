/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * FilePath: board.h
 * Date: 2021-04-27 15:08:44
 * LastEditTime: 2022-02-18 08:29:25
 * Description:  This files is for 
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "fparameters.h"
#include "phytium_cpu.h"

#if defined(__CC_ARM)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif defined(__GNUC__)
extern int __bss_end;
#define HEAP_BEGIN ((void *)&__bss_end)
#endif

#define HEAP_END (void *)(0x80000000 + 1024 * 1024 * 1024)

void rt_hw_board_init(void);

#endif
