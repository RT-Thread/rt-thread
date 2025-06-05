/*
 * @Author: xx
 * @Date: 2025-06-04 20:15:23
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-06-05 14:32:32
 * @Description: 
 * @FilePath: \undefinedf:\github\rtthread\rt-thread\bsp\stm32\stm32h7r7-atk\board\board.c
 */
/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-29     RealThread   first version
 */

#include "board.h"

#define DBG_TAG "board"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#ifdef RT_USING_INDEPENDENT_INTERRUPT_MANAGEMENT
#define RT_NVIC_PRO_BITS    __NVIC_PRIO_BITS

rt_base_t rt_hw_interrupt_disable(void)
{
    rt_base_t level = __get_BASEPRI();
    __set_BASEPRI(RT_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - RT_NVIC_PRO_BITS));

    __ISB();
    __DSB();

    return level;
}

void rt_hw_interrupt_enable(rt_base_t level)
{
    __set_BASEPRI(level);
}
#endif /* RT_USING_INDEPENDENT_INTERRUPT_MANAGEMENT */

/**
 * @brief System Clock Configuration
 * @retval None
*/
void SystemClock_Config(void)
{
    return;
}
