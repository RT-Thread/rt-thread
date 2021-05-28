/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-05-23     aozima       first implementation for PIC32.
 */
#include <rtthread.h>

// Warning:
// if you want to use DBPRINTF in PIC32 Ethernet Starter Kit,
// you project must globl define PIC32_STARTER_KIT and debug in MPLAB.
// but,if you want run app without debug mode,you must remove this features.

// Adds support for PIC32 Peripheral library functions and macros
#include <plib.h>

void rt_hw_console_init(void)
{
    //Initialize the DB_UTILS IO channel
//  DBINIT();
}

/**
 * This function is used by rt_kprintf to display a string on console.
 *
 * @param str the displayed string
 */
void rt_hw_console_output(const char* str)
{
//    DBPRINTF(str);
}

