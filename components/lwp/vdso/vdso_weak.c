/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */

#include <rtthread.h>
#include <lwp_user_mm.h>
#include "vdso.h"

rt_weak int arch_setup_additional_pages(struct rt_lwp *lwp)
{
    return -RT_ERROR;
}

rt_weak void rt_vdso_update_glob_time(void)
{

}
