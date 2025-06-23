/*
 * Copyright (c) 2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-06-21     Bernard      First version
 */

#include <rtthread.h>
#include "hello.h"

/**
 * @brief Hello world function implementation
 *
 * This function prints "Hello World!" to the console using rt_kprintf
 */
void hello_world(void)
{
    rt_kprintf("Hello World!\n");
}
