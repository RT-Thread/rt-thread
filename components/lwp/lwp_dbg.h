/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-11     RT-Thread    first version
 */

#ifndef __LWP_DBG_H__
#define __LWP_DBG_H__

#include <rtthread.h>
#include <rthw.h>
#include <lwp.h>

int dbg_thread_in_debug(void);
void dbg_register(struct dbg_ops_t *dbg_ops);
uint32_t dbg_get_ins(void);
void dbg_activate_step(void);
void dbg_deactivate_step(void);
int dbg_check_event(struct rt_hw_exp_stack *regs, unsigned long esr);
rt_channel_t gdb_server_channel(void);
int dbg_step_type(void);
void dbg_attach_req(void *pc);
int dbg_check_suspend(void);

#endif /* __LWP_DBG_H__ */
