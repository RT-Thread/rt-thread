/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_assert.h"
#ifdef UNIT_TESTING
 #include "fake_regs.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#ifdef UNIT_TESTING

void disable_irqs_mock(void);

 #define DISABLE_IRQS    disable_irqs_mock()

BSP_WEAK_REFERENCE void disable_irqs_mock (void)
{
    /* Do nothing. */
}

BSP_WEAK_REFERENCE void indicate_infinite_wait_hook(void);

 #define WAIT_FOREVER    indicate_infinite_wait_hook()

BSP_WEAK_REFERENCE void indicate_infinite_wait_hook (void)
{
    /* Do nothing. */
}

#else
 #define DISABLE_IRQS        __disable_irq()
 #define WAIT_FOREVER        do { /* Wait. */} while (1)

 #define MTB_MASTER_REG      *((volatile uint32_t *) 0xE0043004)
#endif

#define MTB_MASTER_EN_Pos    31        /* NOLINT(modernize-macro-to-enum) */

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Pointer to the current handler of BSP_CHECK_DEBUG() and BSP_CHECK_FATAL().
 * It should end up halting execution, which might then be escalated to a system reset by the system watchdog.
 *
 * @note It is placed in the ".noinit" section, so that its value is controlled solely by
 *       bsp_prv_halt_implementation_early_set() and bsp_prv_halt_implementation_normal_set().
 **********************************************************************************************************************/
bsp_on_error_cb_t g_halt_impl BSP_PLACE_IN_SECTION(BSP_SECTION_NOINIT);

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

TESTABLE_STATIC volatile uint32_t bsp_prv_scratch_registers[4];

__STATIC_FORCEINLINE void store_scratch_regs (const uint32_t * regs)
{
    bsp_prv_scratch_registers[0] = *regs++;
    bsp_prv_scratch_registers[1] = *regs++;
    bsp_prv_scratch_registers[2] = *regs++;
    bsp_prv_scratch_registers[3] = *regs;
}

__STATIC_FORCEINLINE void disable_tracing (void)
{
    MTB_MASTER_REG &= ~(1 << MTB_MASTER_EN_Pos);
}

TESTABLE_STATIC void bsp_prv_early_halt (uintptr_t args)
{
    DISABLE_IRQS;

    store_scratch_regs((uint32_t *) args);

    disable_tracing();

    R_BSP_PeripheralFreeze(BSP_FREEZE_PERIPHERAL_SYS_WDOG);

    // TODO add GPIO debugging (EXCEPTION_DEBUG == 1)

    WAIT_FOREVER;
}

BSP_PLACE_CODE_IN_RAM
TESTABLE_STATIC void bsp_prv_normal_halt (uintptr_t args)
{
    DISABLE_IRQS;

    store_scratch_regs((uint32_t *) args);

    disable_tracing();

    R_BSP_PeripheralFreeze(BSP_FREEZE_PERIPHERAL_SYS_WDOG);

    // TODO add GPIO debugging (EXCEPTION_DEBUG == 1)

    WAIT_FOREVER;
}

/*******************************************************************************************************************//**
 * @internal
 * @addtogroup BSP_MCU_PRV Internal BSP Documentation
 * @ingroup RENESAS_INTERNAL
 * @{
 **********************************************************************************************************************/

/**
 * @brief Set up the halt capability to use an implementation that is valid "early", i.e. before the C runtime is ready.
 *
 * Before the C runtime is ready, the halt implementation must be located in the default code storage, close to the
 * Reset_Handler(), so that it can be safely called.
 */
void bsp_prv_halt_implementation_early_set (void)
{
    g_halt_impl = bsp_prv_early_halt;
}

/**
 * @brief Set up the halt capability to use an implementation that is optimized for the normal case, i.e. after the C
 *        runtime is ready.
 *
 * In the normal case, it's better for the halt implementation to be located in RAM, so that it's always usable.
 */
void bsp_prv_halt_implementation_normal_set (void)
{
    g_halt_impl = bsp_prv_normal_halt;
}

/** @} (end addtogroup BSP_MCU_PRV) */
