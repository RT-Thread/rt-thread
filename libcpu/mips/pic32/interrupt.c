/*
 * File      : interrupt.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-05-23     aozima       first implementation for PIC32.
 */

#include <rtthread.h>

/**
 * @addtogroup PIC32
 */
/*@{*/

rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrput_flag;


/*@}*/

