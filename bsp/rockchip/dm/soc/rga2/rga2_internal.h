/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#ifndef __ROCKCHIP_RGA2_INTERNAL_H__
#define __ROCKCHIP_RGA2_INTERNAL_H__

#include <rtthread.h>
#include <rga2.h>

#define RGA2_COMMAND_WORDS             32

rt_err_t rockchip_rga2_build_command(const struct rga2_req *req,
        rt_uint32_t command[RGA2_COMMAND_WORDS]);

#endif /* __ROCKCHIP_RGA2_INTERNAL_H__ */
