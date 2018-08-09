/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(TASK_MANAGER)
#include "nrf_mpu.h"
#include "nrf_atomic.h"
#include "app_util_platform.h"
#include "task_manager.h"

#if TASK_MANAGER_CLI_CMDS
#include "nrf_cli.h"
#endif

#define NRF_LOG_MODULE_NAME task_manager

#if TASK_MANAGER_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       TASK_MANAGER_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  TASK_MANAGER_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR TASK_MANAGER_CONFIG_DEBUG_COLOR
#endif
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#if TASK_MANAGER_CONFIG_STACK_GUARD
#define STACK_GUARD_SIZE    (1 << (TASK_MANAGER_CONFIG_STACK_GUARD + 1))
STATIC_ASSERT((TASK_MANAGER_CONFIG_STACK_SIZE % STACK_GUARD_SIZE) == 0);
#endif

STATIC_ASSERT((TASK_MANAGER_CONFIG_MAX_TASKS) > 0);
STATIC_ASSERT((TASK_MANAGER_CONFIG_STACK_SIZE % 8) == 0);

// Support older CMSIS avaiable in Keil 4
#if (__CORTEX_M == 4)
# ifndef CONTROL_FPCA_Pos
#  define CONTROL_FPCA_Pos  2u
#  define CONTROL_FPCA_Msk  (1ul << CONTROL_FPCA_Pos)
# endif

# ifndef CONTROL_SPSEL_Pos
#  define CONTROL_SPSEL_Pos 1u
#  define CONTROL_SPSEL_Msk (1ul << CONTROL_SPSEL_Pos)
# endif
#endif

/*lint -save -esym(526,task_switch)*/
// Declare task switching function.
extern void task_switch(void);
/*lint -restore*/

/**@brief Idle Task ID */
#define IDLE_TASK_ID            TASK_MANAGER_CONFIG_MAX_TASKS
#define TASK_STACK_MAGIC_WORD   0xDEADD00E
#define TASK_FLAG_SIGNAL_MASK   0x00FFFFFF
#define TASK_FLAG_DESTROY       0x80000000

/** @brief Total number of tasks includes user configuration and idle task. */
#define TOTAL_NUM_OF_TASKS (TASK_MANAGER_CONFIG_MAX_TASKS + 1)

/**@brief Task stack with saved task state (does not include FPU state). */
typedef struct
{
    uint32_t    r0;
    uint32_t    r4;
    uint32_t    r5;
    uint32_t    r6;
    uint32_t    r7;
    uint32_t    r8;
    uint32_t    r9;
    uint32_t    r10;
    uint32_t    r11;
    uint32_t    r12;
    uint32_t    lr;
    uint32_t    control;
} task_stack_t;

/**@brief Task State */
typedef struct
{
    void              *p_stack;      /**< Pointer to task stack. NULL if task does not exist. */
    const char        *p_task_name;
    nrf_atomic_u32_t   flags;        /**< Task flags */
} task_state_t;

/* Allocate space for task stacks:
 *
 * Layout:
 * +---------------+
 * |   Idle Task   |
 * +---------------+
 * |  Stack Guard  |
 * +---------------+
 * |    Task N     |
 * +---------------+
 * |  Stack Guard  |
 * +---------------+
 * |      ...      |
 * +---------------+
 * |    Task 0     |
 * +---------------+
 * |  Stack Guard  |
 * +---------------+
 */

typedef struct
{
#if TASK_MANAGER_CONFIG_STACK_GUARD
    uint8_t guard[STACK_GUARD_SIZE];
#endif
    uint8_t stack[TASK_MANAGER_CONFIG_STACK_SIZE];
} task_manager_stack_t;

/**@brief Stack space for tasks */
#if TASK_MANAGER_CONFIG_STACK_GUARD
/**@brief Handle to MPU region used as a guard */
static nrf_mpu_region_t s_guard_region;
__ALIGN(STACK_GUARD_SIZE)
#else
__ALIGN(8)
#endif
static task_manager_stack_t s_task_stacks[TOTAL_NUM_OF_TASKS];

/**@brief Task States
 * Addtional state reserved for idle task which is mandatory.
 * */
static task_state_t s_task_state[TOTAL_NUM_OF_TASKS];

/**@brief Mask indicating which tasks are runnable */
static nrf_atomic_u32_t s_runnable_tasks_mask;

/**@brief ID of currently executed task */
static task_id_t s_current_task_id;

/**@brief Guard page attributes: Normal memory, WBWA/WBWA, RO/RO, XN */
#define TASK_GUARD_ATTRIBUTES ((0x05 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_B_Pos) | \
                               (0x07 << MPU_RASR_AP_Pos)  | (1 << MPU_RASR_XN_Pos))


/**@brief Macro for getting pointer to bottom of stack for given task id */
#define BOTTOM_OF_TASK_STACK(_task_id)  ((void *)(&s_task_stacks[(_task_id)].stack[0]))

/**@brief Macro for getting pointer to top of stack for given task id */
#define TOP_OF_TASK_STACK(_task_id)     ((void *)(&s_task_stacks[(_task_id)].stack[TASK_MANAGER_CONFIG_STACK_SIZE]))

/**@brief Macro for getting pointer to base of stack guard for given task id */
#define TASK_STACK_GUARD_BASE(_task_id) ((void *)(&s_task_stacks[(_task_id)].guard[0]))

#define TASK_ID_TO_MASK(_task_id)   (0x80000000 >> (_task_id))

/**@brief Puts task in RUNNABLE state */
#define TASK_STATE_RUNNABLE(_task_id) \
    (void)nrf_atomic_u32_or(&s_runnable_tasks_mask, TASK_ID_TO_MASK(_task_id))

/**@brief Puts task in SUSPENDED state */
#define TASK_STATE_SUSPENDED(_task_id) \
    (void)nrf_atomic_u32_and(&s_runnable_tasks_mask, ~TASK_ID_TO_MASK(_task_id));

static void task_stack_poison(task_id_t task_id)
{
#if TASK_MANAGER_CONFIG_STACK_PROFILER_ENABLED
    unsigned int i = TASK_MANAGER_CONFIG_STACK_SIZE / sizeof(uint32_t);
    uint32_t *p_stack_top = TOP_OF_TASK_STACK(task_id);

    while (i--)
    {
        *(--p_stack_top) = TASK_STACK_MAGIC_WORD;
    }
#endif
}

static void task_stack_protect(task_id_t task_id)
{
#if TASK_MANAGER_CONFIG_STACK_GUARD
    APP_ERROR_CHECK(nrf_mpu_region_create(&s_guard_region,
                                          TASK_STACK_GUARD_BASE(task_id),
                                          STACK_GUARD_SIZE,
                                          TASK_GUARD_ATTRIBUTES));
#endif
}

PRAGMA_OPTIMIZATION_FORCE_START
void task_manager_start(task_main_t idle_task, void *p_idle_task_context)
{
    unsigned long control;

    // Idle task must be specified.
    ASSERT(idle_task != NULL);

    // Make sure that we are in privledged thread level using MSP stack.
    ASSERT((__get_IPSR() & IPSR_ISR_Msk) == 0);
    ASSERT((__get_CONTROL() & CONTROL_nPRIV_Msk) == 0);
    ASSERT((__get_CONTROL() & CONTROL_SPSEL_Msk) == 0);

    // Prepare task state structure.
    s_current_task_id = IDLE_TASK_ID;
    s_task_state[s_current_task_id].p_task_name = "Idle Task";

    // Prepare stack instrumentation and protection.
    task_stack_poison(s_current_task_id);
    task_stack_protect(s_current_task_id);

    NRF_LOG_INFO("Task %u created (name: '%s', stack: 0x%08X-0x%08X).",
                  s_current_task_id,
                  s_task_state[s_current_task_id].p_task_name,
                  (uint32_t)BOTTOM_OF_TASK_STACK(s_current_task_id),
                  (uint32_t)TOP_OF_TASK_STACK(s_current_task_id) - 1);

    // Prepare context for idle task. This must be done with all interrupts disabled.
    __disable_irq();

    // Set process and exception stacks.
    __set_PSP((uint32_t)(TOP_OF_TASK_STACK(s_current_task_id)));
    __set_MSP((uint32_t)(STACK_TOP));

    // Update CONTROL register.
    control = __get_CONTROL();
    control &= CONTROL_FPCA_Msk;    // Clear FPCA since FPU state does not need to be preserved.
    control |= CONTROL_SPSEL_Msk;   // Use MSP only for excpetions, leaving PSP for tasks.
    __set_CONTROL(control);

    // Context is ready. Enable interrupts.
    __enable_irq();

    // Perform task switch to run non-idle tasks as soon as possible.
    task_switch();

    // Jump to idle task.
    idle_task(p_idle_task_context);

    // This should be never reached.
    APP_ERROR_CHECK_BOOL(false);
}
PRAGMA_OPTIMIZATION_FORCE_END

task_id_t task_create(task_main_t task, char const * p_task_name, void *p_context)
{
    task_state_t *p_state = NULL;
    task_stack_t *p_stack;
    task_id_t task_id;

    // Check arguments.
    if (task == NULL)
    {
        return TASK_ID_INVALID;
    }

    // Find free task state structure.
    CRITICAL_REGION_ENTER();
    for (task_id = 0; task_id < TASK_MANAGER_CONFIG_MAX_TASKS; task_id++)
    {
        if (s_task_state[task_id].p_stack == NULL)
        {
            p_state = &s_task_state[task_id];
            p_state->p_stack = TOP_OF_TASK_STACK(task_id);
            break;
        }
    }
    CRITICAL_REGION_EXIT();

    // Return invalid Task ID if new task cannot be created.
    if (p_state == NULL)
    {
        return TASK_ID_INVALID;
    }

    // Prepare initial stack for the task.
    task_stack_poison(task_id);

    p_state->p_stack     = (uint8_t *)(p_state->p_stack) - sizeof(*p_stack);
    p_state->p_task_name = (char *)p_task_name;
    p_state->flags       = 0;

    p_stack = p_state->p_stack;

    p_stack->control    = CONTROL_SPSEL_Msk;
    p_stack->lr         = (uint32_t)(task);         // Start from this function.
    p_stack->r0         = (uint32_t)(p_context);    // Pass p_context as first argument.

    // Mark task as ready to run.
    TASK_STATE_RUNNABLE(task_id);

    NRF_LOG_INFO("Task %u created (name: '%s', stack: 0x%08X-0x%08X).",
                 task_id,
                 p_task_name,
                 (uint32_t)BOTTOM_OF_TASK_STACK(task_id),
                 (uint32_t)TOP_OF_TASK_STACK(task_id) - 1);

    return task_id;
}

/**@brief Task scheduler.
 *
 * @param[in]   Pointer to task stack with saved task state.
 * @return      Pointer to new task stack with saved task state.
 */
void *task_schedule(void *p_stack)
{
    uint32_t runnable_tasks_mask;

#if TASK_MANAGER_CONFIG_STACK_GUARD
    // Destroy stack guard allocated for current task.
    APP_ERROR_CHECK(nrf_mpu_region_destroy(s_guard_region));
#endif

    // Save current task state if task if switching from valid task.
    if ((s_task_state[s_current_task_id].flags & TASK_FLAG_DESTROY) == 0)
    {
        s_task_state[s_current_task_id].p_stack = p_stack;
    }
    else
    {
        TASK_STATE_SUSPENDED(s_current_task_id);
        s_task_state[s_current_task_id].p_stack = NULL;

        NRF_LOG_INFO("Task %u terminated (name: '%s').",
                 s_current_task_id,
                 s_task_state[s_current_task_id].p_task_name);
    }

    // Atomically fetch list of runnable tasks.
    runnable_tasks_mask = s_runnable_tasks_mask;

    // Check if there are any tasks to execute.
    if (runnable_tasks_mask != 0)
    {
        // Check if we could continue this round.
        if ((runnable_tasks_mask << (s_current_task_id + 1)) != 0)
        {
            // There are tasks to execute in this round. Select next runnable task:
            s_current_task_id += 1 + __CLZ((runnable_tasks_mask << (s_current_task_id + 1)));
        }
        else
        {
            // No more tasks in this round. Select first avaiable task:
            s_current_task_id = __CLZ(runnable_tasks_mask);
        }
    }
    else
    {
        // Fall back to idle task if other tasks cannot be run.
        s_current_task_id = IDLE_TASK_ID;
    }

    task_stack_protect(s_current_task_id);

    // Switch to new task.
    return s_task_state[s_current_task_id].p_stack;
}

void task_yield(void)
{
    // Make sure that we are in privledged thread level using PSP stack.
    ASSERT((__get_IPSR() & IPSR_ISR_Msk) == 0);
    ASSERT((__get_CONTROL() & CONTROL_nPRIV_Msk) == 0);
    ASSERT((__get_CONTROL() & CONTROL_SPSEL_Msk) != 0);

    // Perform task switch.
    task_switch();
}

uint32_t task_events_wait(uint32_t evt_mask)
{
    uint32_t current_events;

    ASSERT((evt_mask & ~TASK_FLAG_SIGNAL_MASK) == 0);

    for (;;)
    {
        current_events = s_task_state[s_current_task_id].flags & evt_mask;
        if (current_events != 0)
        {
            (void)nrf_atomic_u32_and(&s_task_state[s_current_task_id].flags, ~current_events);
            break;
        }

        TASK_STATE_SUSPENDED(s_current_task_id);
        task_yield();
    }

    return current_events;
}

void task_events_set(task_id_t task_id, uint32_t evt_mask)
{
    ASSERT((task_id != TASK_ID_INVALID) && (task_id < TASK_MANAGER_CONFIG_MAX_TASKS));
    ASSERT((evt_mask & ~TASK_FLAG_SIGNAL_MASK) == 0);
    ASSERT(s_task_state[task_id].p_stack != NULL);

    (void)nrf_atomic_u32_or(&s_task_state[task_id].flags, evt_mask);
    TASK_STATE_RUNNABLE(task_id);
}

void task_exit(void)
{
    // Make sure that we are in privledged thread level using PSP stack.
    ASSERT((__get_IPSR() & IPSR_ISR_Msk) == 0);
    ASSERT((__get_CONTROL() & CONTROL_nPRIV_Msk) == 0);
    ASSERT((__get_CONTROL() & CONTROL_SPSEL_Msk) != 0);

    s_task_state[s_current_task_id].flags = TASK_FLAG_DESTROY;
    task_switch();
}

task_id_t task_id_get(void)
{
    // Make sure that we are in privledged thread level using PSP stack.
    ASSERT((__get_IPSR() & IPSR_ISR_Msk) == 0);
    ASSERT((__get_CONTROL() & CONTROL_nPRIV_Msk) == 0);
    ASSERT((__get_CONTROL() & CONTROL_SPSEL_Msk) != 0);

    return s_current_task_id;
}

uint32_t task_stack_max_usage_get(task_id_t task_id)
{
#if TASK_MANAGER_CONFIG_STACK_PROFILER_ENABLED
    unsigned int stack_usage;
    uint32_t *p_stack, *p_stack_top;

    ASSERT((task_id != TASK_ID_INVALID) || (task_id < TASK_MANAGER_CONFIG_MAX_TASKS));
    ASSERT(s_task_state[task_id].p_stack != NULL);

    p_stack_top = TOP_OF_TASK_STACK(task_id);
    p_stack     = BOTTOM_OF_TASK_STACK(task_id);
    stack_usage = TASK_MANAGER_CONFIG_STACK_SIZE;

    while (p_stack < p_stack_top)
    {
        if (*(p_stack++) != TASK_STACK_MAGIC_WORD)
        {
            break;
        }

        stack_usage -= sizeof(*p_stack);
    }

    return stack_usage;
#else
    return 0;
#endif
}

#if TASK_MANAGER_CLI_CMDS
static void task_mnanager_info(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    task_id_t task_id;

    for (task_id = 0; task_id < TOTAL_NUM_OF_TASKS; task_id++)
    {
        const char *p_task_name = NULL;

        CRITICAL_REGION_ENTER();
        if (s_task_state[task_id].p_stack != NULL)
        {
            p_task_name = (s_task_state[task_id].p_task_name) ? s_task_state[task_id].p_task_name
                                                              : "<NULL>";
        }
        CRITICAL_REGION_EXIT();

        if (p_task_name)
        {
            uint32_t stack_usage = task_stack_max_usage_get(task_id);

            nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "Task %u:\r\n", task_id);
            nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\tName:\t'%s'\r\n", p_task_name);

            if (stack_usage)
            {
                nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\tStack:\t0x%08X-0x%08X used in %u%% (%u out of %u bytes)\r\n",
                                (uint32_t)BOTTOM_OF_TASK_STACK(task_id),
                                (uint32_t)TOP_OF_TASK_STACK(task_id) - 1,
                                100 * stack_usage / TASK_MANAGER_CONFIG_STACK_SIZE,
                                stack_usage,
                                TASK_MANAGER_CONFIG_STACK_SIZE);
            }
            else
            {
                nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\tStack:\t0x%08X-0x%08X\r\n",
                                (uint32_t)BOTTOM_OF_TASK_STACK(task_id),
                                (uint32_t)TOP_OF_TASK_STACK(task_id) - 1);
            }

            nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\tState:\t%s\r\n",
                (s_current_task_id == task_id) ? "Running" :
                (s_runnable_tasks_mask & TASK_ID_TO_MASK(task_id)) ? "Runnable" : "Suspended");

            nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\tFlags:\t0x%08X\r\n\r\n",
                            s_task_state[task_id].flags);

        }
    }
}

NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_task_mngr)
{
    NRF_CLI_CMD(info, NULL, "tasks info", task_mnanager_info),
    NRF_CLI_SUBCMD_SET_END
};

NRF_CLI_CMD_REGISTER(task_manager, &m_sub_task_mngr, "commands for task manager", NULL);
#endif //TASK_MANAGER_CLI_CMDS
#else //TASK_MANAGER_ENABLED
void *task_schedule(void *p_stack)
{
    return (void *)0;
}
#endif //TASK_MANAGER_ENABLED
