/*
 * File      : debug.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-06 11     mbbill       first version
 */

#include <rtdef.h>
#include <rtdebug.h>


/**
 * @addtogroup Kernel
 */

/*@{*/
#ifdef RT_DEBUG
rt_uint8_t rt_debug_reent_cnt = 0;
#endif

/*@}*/
