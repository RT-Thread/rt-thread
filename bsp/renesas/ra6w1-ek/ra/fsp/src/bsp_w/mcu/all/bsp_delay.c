/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "bsp_delay.h"
#if dg_configUSE_CLOCK_MGR
 #include "sys_clock_mgr.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_DELAY_OVERHEAD_CYCLES    (72)
#define BSP_CYCLES_PER_DELAY_REP     (4)
#define BSP_MAX_DELAY_CYCLES         (0xFFFFFFFF)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *              Delay for at least the specified duration in units and return.
 * @param[in]   delay  The number of 'units' to delay.
 * @param[in]   units  The 'base' (bsp_delay_units_t) for the units specified. Valid values are:
 *              BSP_DELAY_UNITS_SECONDS, BSP_DELAY_UNITS_MILLISECONDS, BSP_DELAY_UNITS_MICROSECONDS.@n
 *
 * @note This function calls bsp_cpu_clock_get() which ultimately calls R_CGC_SystemClockFreqGet() and therefore requires
 *       that the BSP has already initialized the CGC (which it does as part of the Sysinit).
 *       Care should be taken to ensure this remains the case if in the future this function were to be called as part
 *       of the BSP initialization.
 *
 * @note Delays may be longer than expected when compiler optimization is turned off.
 **********************************************************************************************************************/
#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#pragma GCC push_options
#pragma GCC optimize ("O3")
#endif
BSP_PLACE_CODE_IN_RAM void R_BSP_SoftwareDelay (uint32_t delay, bsp_delay_units_t units)
{
    uint32_t cpu_clk_Mhz;
    uint32_t reps     = 0;
    uint32_t total_us = (delay * units); /** Convert the requested time to microseconds. */

    static const uint8_t  OVERHEAD_REPS = BSP_DELAY_OVERHEAD_CYCLES / BSP_CYCLES_PER_DELAY_REP;

#if dg_configUSE_CLOCK_MGR
    FSP_CRITICAL_SECTION_DEFINE;

    FSP_CRITICAL_SECTION_ENTER;
    cpu_clk_Mhz = cm_cpu_clk_get_fromISR();
    FSP_CRITICAL_SECTION_EXIT;
#else
    static const uint32_t DIVIDER       = 1000000;

    cpu_clk_Mhz = SystemCoreClock / DIVIDER; /** Get the system clock frequency in Hz. */
#endif

#if BSP_FEATURE_CGC_HAS_HCLK_DIV
    uint32_t hclk_div;
    hclk_div = CRG_TOP->CLK_AMBA_REG_b.HCLK_DIV;

    cpu_clk_Mhz = cpu_clk_Mhz >> hclk_div;
#endif

    reps = cpu_clk_Mhz * total_us / BSP_CYCLES_PER_DELAY_REP;

#ifdef CLK_DELAY_SANITY_CHECKS
    BSP_CHECK_DEBUG(usec <= (BSP_MAX_DELAY_CYCLES / cpu_clk_Mhz)); // The requested delay is greater than the maximum delay this function can achieve
    BSP_CHECK_DEBUG(reps > OVERHEAD_REPS);                         // The requested delay is smaller than the minimum delay this function can achieve.
#endif

    /** Only delay if the supplied parameters constitute a delay. */
    if ((reps <= OVERHEAD_REPS) || (total_us > (BSP_MAX_DELAY_CYCLES / cpu_clk_Mhz)))
    {
        return;
    }
    __asm volatile (
        "       nop                             \n"
        "       nop                             \n"
        "       nop                             \n"
        "       nop                             \n"
        "       nop                             \n"
        "loop:  nop                             \n"
        "       subs %[reps], %[reps], #1       \n"
        "       bne loop                        \n"
        :                                  // outputs
        :[reps] "r" (reps - OVERHEAD_REPS) // inputs
        :                                  // clobbers
        );
}

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#pragma GCC pop_options
#endif

/** @} (end addtogroup BSP_MCU) */
