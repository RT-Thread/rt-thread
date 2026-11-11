/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-11     RT-Thread    first version
 */
#include <rtthread.h>
#include <rthw.h>
#include <lwp.h>

/**
 * @brief Check if the current thread is in debug state.
 *
 * @return int Returns 1 if the thread is in debug state, 0 otherwise.
 */
int dbg_thread_in_debug(void)
{
    int ret = 0;
    struct rt_lwp *lwp = lwp_self();

    if (lwp && lwp->debug)
    {
        ret = 1;
    }
    return ret;
}

struct dbg_ops_t *rt_dbg_ops = RT_NULL;
RTM_EXPORT(rt_dbg_ops);

/**
 * @brief Register debugger operations.
 *
 * @param dbg_ops Pointer to debugger operations structure.
 */
void dbg_register(struct dbg_ops_t *dbg_ops)
{
    rt_dbg_ops = dbg_ops;
}
RTM_EXPORT(dbg_register);

/**
 * @brief Debug command handler function
 *
 * @param[in] argc Number of command arguments
 * @param[in] argv Array of command argument strings
 *
 * @return int Returns the result from the debug operations handler if available,
 *         otherwise returns -1 to indicate failure
 *
 * @note This function serves as a wrapper for debug operations, delegating to the registered
 *       debug operations handler if available. If no debug operations are registered,
 *       it prints an error message.
 */
static int dbg(int argc, char **argv)
{
    int ret = -1;

    if (rt_dbg_ops)
    {
        ret = rt_dbg_ops->dbg(argc, argv);
    }
    else
    {
        rt_kprintf("Error: DBG command is not enabled!\n");
    }
    return ret;
}
MSH_CMD_EXPORT(dbg, dbg);

/**
 * @brief Get the current instruction value from debug operations
 *
 * @return uint32_t Returns the current instruction value if debug operations are available,
 *         otherwise returns 0
 *
 * @note This function retrieves the current instruction value by calling the registered
 *       debug operations handler if available. If no debug operations are registered,
 *       it returns 0.
 */
uint32_t dbg_get_ins(void)
{
    uint32_t ins = 0;

    if (rt_dbg_ops)
    {
        ins = rt_dbg_ops->arch_get_ins();
    }
    return ins;
}

/**
 * @brief Activates single-step debugging mode if debug operations are registered
 *
 * @note This function checks if debug operations are registered (rt_dbg_ops) and if so,
 *       calls the architecture-specific single-step activation function.
 */
void dbg_activate_step(void)
{
    if (rt_dbg_ops)
    {
        rt_dbg_ops->arch_activate_step();
    }
}

/**
 * @brief Deactivates single-step debugging mode if debug operations are registered
 *
 * @note This function checks if debug operations are registered (rt_dbg_ops) and if so,
 *       calls the architecture-specific single-step deactivation function.
 */
void dbg_deactivate_step(void)
{
    if (rt_dbg_ops)
    {
        rt_dbg_ops->arch_deactivate_step();
    }
}

/**
 * @brief Checks for debug events and processes them if debug operations are registered
 *
 * @param[in] regs Pointer to the hardware exception stack containing register values
 * @param[in] esr Exception Syndrome Register value
 *
 * @return int Returns the result from the debug event check (0 if no debug operations registered)
 *
 * @note This function checks if debug operations are registered (rt_dbg_ops) and if so,
 *       calls the debug event checking function with the provided registers and exception status.
 *       If no debug operations are registered, it returns 0.
 */
int dbg_check_event(struct rt_hw_exp_stack *regs, unsigned long esr)
{
    int ret = 0;

    if (rt_dbg_ops)
    {
        ret = rt_dbg_ops->check_debug_event(regs, esr);
    }
    return ret;
}

/**
 * @brief Gets the GDB server communication channel if debug operations are registered
 *
 * @return rt_channel_t Returns the GDB server channel (RT_NULL if no debug operations registered)
 *
 * @note This function checks if debug operations are registered (rt_dbg_ops) and if so,
 *       retrieves the GDB server communication channel from the registered operations.
 *       If no debug operations are registered, it returns RT_NULL.
 */
rt_channel_t gdb_server_channel(void)
{
    rt_channel_t ret = RT_NULL;

    if (rt_dbg_ops)
    {
        ret = rt_dbg_ops->gdb_get_server_channel();
    }
    return ret;
}

/**
 * @brief Gets the current step type from debug operations
 *
 * @return int The current step type (0 if no debug operations are registered)
 *
 * @note This function checks if debug operations are registered (rt_dbg_ops) and if so,
 *       retrieves the current step type from the registered debug operations.
 *       If no debug operations are registered, it returns 0.
 */
int dbg_step_type(void)
{
    int ret = 0;

    if (rt_dbg_ops)
    {
        ret = rt_dbg_ops->gdb_get_step_type();
    }
    return ret;
}

/**
 * @brief Handles debug attach request
 *
 * @param[in] pc Pointer to the program counter value
 *
 * @note This function checks if debug operations are registered and calls
 *       the debug attach request handler if available.
 */
void dbg_attach_req(void *pc)
{
    if (rt_dbg_ops)
    {
        rt_dbg_ops->lwp_check_debug_attach_req(pc);
    }
}

/**
 * @brief Checks if debug suspend is requested
 *
 * @return int Returns the suspend status (0 if no debug operations are registered)
 *
 * @note This function checks if debug operations are registered and calls
 *       the debug suspend check handler if available.
 */
int dbg_check_suspend(void)
{
    int ret = 0;

    if (rt_dbg_ops)
    {
        ret = rt_dbg_ops->lwp_check_debug_suspend();
    }
    return ret;
}
