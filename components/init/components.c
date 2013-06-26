/*
 * File      : components.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012 - 2013, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-20     Bernard      Change the name to components.c
 *                             And all components related header files.
 * 2012-12-23     Bernard      fix the pthread initialization issue.
 * 2013-06-23     Bernard      Add the init_call for components initialization.
 */

#include "components.h"

static int rti_start(void)
{
    return 0;
}
INIT_EXPORT(rti_start, "0");

static int rti_board_end(void)
{
    return 0;
}
INIT_EXPORT(rti_board_end, "1.post");

static int rti_end(void)
{
    return 0;
}
INIT_EXPORT(rti_end,"7");

#if defined(_MSC_VER) || (defined(__GNUC__) && defined(__x86_64__))
/* fixed for MSC_VC and x86_64 in GNU GCC */
#define NEXT_COMPONENT_FN(fn_ptr, end)  fn_ptr = _next_component_fn(fn_ptr, end)

const init_fn_t *_next_component_fn(const init_fn_t *fn, const init_fn_t *end)
{
    unsigned int *ptr;
    ptr = (unsigned int*) (fn + 1);
    while ((*ptr == 0) && ((unsigned int*)ptr < (unsigned int*)end))
        ptr ++;

    return (const init_fn_t*)ptr;
}
#else
#define NEXT_COMPONENT_FN(fn_ptr, end)  fn_ptr++
#endif

/**
 * RT-Thread Components Initialization for board
 */
void rt_components_board_init(void)
{
    const init_fn_t *fn_ptr;

    for (fn_ptr = &__rt_init_rti_start; fn_ptr < &__rt_init_rti_board_end; )
    {
        (*fn_ptr)();
        NEXT_COMPONENT_FN(fn_ptr, __rt_init_rti_board_end);
    }
}

/**
 * RT-Thread Components Initialization
 */
void rt_components_init(void)
{
    const init_fn_t *fn_ptr;

    for (fn_ptr = &__rt_init_rti_board_end; fn_ptr < &__rt_init_rti_end; )
    {
        (*fn_ptr)();
        NEXT_COMPONENT_FN(fn_ptr, __rt_init_rti_end);
    }
}

