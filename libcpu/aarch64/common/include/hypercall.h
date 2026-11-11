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

#ifndef __HYPERCALL_H__
#define __HYPERCALL_H__

#include <rtdef.h>
#include <smccc.h>

#define HYPERCALL_START 0xc5000000 /* HVC64 */
#define HYPERCALL_END   0xc500ffff /* HVC64 */

rt_inline rt_uint32_t rt_hw_hypercall(rt_uint32_t w0, rt_uint64_t x1, rt_uint64_t x2,
        rt_uint64_t x3, rt_uint64_t x4, rt_uint64_t x5, rt_uint64_t x6, rt_uint32_t w7)
{
    struct arm_smccc_res_t res;

    arm_smccc_hvc(w0, x1, x2, x3, x4, x5, x6, w7, &res, RT_NULL);

    return res.a0;
}

rt_err_t rt_hv_version(rt_uint32_t *out_version);
rt_err_t rt_hv_debug(rt_uint32_t id, rt_uint32_t argc,
        rt_ubase_t arg0, rt_ubase_t arg1, rt_ubase_t arg2,
        rt_ubase_t arg3, rt_ubase_t arg4);
rt_err_t rt_hv_console(char c);

#endif /* __HYPERCALL_H__ */
