/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-24     GuEe-GUI     first version
 * 2023-02-21     GuEe-GUI     update API
 */

#include <hypercall.h>

rt_err_t rt_hv_version(rt_uint32_t *out_version)
{
    if (out_version)
    {
        *out_version = rt_hw_hypercall(HYPERCALL_START + 0, 0, 0, 0, 0, 0, 0, 0);

        if ((int)*out_version < 0)
        {
            return *out_version;
        }
    }

    return -RT_EINVAL;
}

rt_err_t rt_hv_debug(rt_uint32_t id, rt_uint32_t argc,
        rt_ubase_t arg0, rt_ubase_t arg1, rt_ubase_t arg2,
        rt_ubase_t arg3, rt_ubase_t arg4)
{
    return rt_hw_hypercall(HYPERCALL_START + 1, id,
            arg0, arg1, arg2, arg3, arg4, argc);
}

rt_err_t rt_hv_console(char c)
{
    return rt_hw_hypercall(HYPERCALL_START + 2, c, 0, 0, 0, 0, 0, 0);
}
