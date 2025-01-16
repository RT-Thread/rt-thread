/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-11     RT-Thread    first version
 * 2025-01-16     wumingzi     add doxyzen comment
 */

#ifndef __LWP_DBG_H__
#define __LWP_DBG_H__

#include <rtthread.h>
#include <rthw.h>
#include <lwp.h>

/**
 * addtogroup  KernelService
 * @defgroup    lwp     lwp
 * @brief       lwp api
 * @ingroup     KernelService
 * @addtogroup  lwp
 *@{
 */

/**
 * @brief Get lwp debug state
 * @return int lwp debug state code
 */
int dbg_thread_in_debug(void);

/**
 * @brief Register dbg_ops to struct dbg_ops_t
 * @param dbg_ops Pointer to dbg_ops_t that contains function pointers for various debugging operations.
 */
void dbg_register(struct dbg_ops_t *dbg_ops);

/**
 * @brief Get lwp instructure state
 * @return Return the architecture number
 */
uint32_t dbg_get_ins(void);

/**
 * @brief Enable step debug feature
 */
void dbg_activate_step(void);

/**
 * @brief Disable step debug feature
 */
void dbg_deactivate_step(void);

/**
 * @brief Check event for related instruction by exception state register
 * @param regs Pointer to exception stack with type struct rt_hw_exp_stack *
 * @param esr Address of exception state register
 * @return Return the debug event number
 */
int dbg_check_event(struct rt_hw_exp_stack *regs, unsigned long esr);

/**
 * @brief Get gdb server channel and prepared by rt_channel_t
 * @return Return a Pointer to rt_channel_t
 */
rt_channel_t gdb_server_channel(void);

/**
 * @brief Get debug step type
 * @return Return the debug step type
 */
int dbg_step_type(void);

/**
 * @brief Start debug attach request
 * @param pc Pointer to programe counter
 */
void dbg_attach_req(void *pc);

/**
 * @brief Suspend debug attach request
 * @return Return result of suspend operation and 0 is failed.
 */
int dbg_check_suspend(void);

/*! @}*/

#endif /* __LWP_DBG_H__ */