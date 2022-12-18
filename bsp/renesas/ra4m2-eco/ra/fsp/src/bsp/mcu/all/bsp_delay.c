/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "bsp_delay.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_DELAY_NS_PER_SECOND    (1000000000)
#define BSP_DELAY_NS_PER_US        (1000)

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
 *              For example:@n
 *              At 1 MHz one cycle takes 1 microsecond (.000001 seconds).@n
 *              At 12 MHz one cycle takes 1/12 microsecond or 83 nanoseconds.@n
 *              Therefore one run through bsp_prv_software_delay_loop() takes:
 *              ~ (83 * BSP_DELAY_LOOP_CYCLES) or 332 ns.
 *              A delay of 2 us therefore requires 2000ns/332ns or 6 loops.
 *
 *              The 'theoretical' maximum delay that may be obtained is determined by a full 32 bit loop count and the system clock rate.
 *              @120MHz:  ((0xFFFFFFFF loops * 4 cycles /loop) / 120000000) = 143 seconds.
 *              @32MHz:  ((0xFFFFFFFF loops * 4 cycles /loop) / 32000000) = 536 seconds
 *
 *              Note that requests for very large delays will be affected by rounding in the calculations and the actual delay
 *              achieved may be slightly longer. @32 MHz, for example, a request for 532 seconds will be closer to 536 seconds.
 *
 *              Note also that if the calculations result in a loop_cnt of zero, the bsp_prv_software_delay_loop() function is not called
 *              at all. In this case the requested delay is too small (nanoseconds) to be carried out by the loop itself, and the
 *              overhead associated with executing the code to just get to this point has certainly satisfied the requested delay.
 *
 * @note This function calls bsp_cpu_clock_get() which ultimately calls R_CGC_SystemClockFreqGet() and therefore requires
 *       that the BSP has already initialized the CGC (which it does as part of the Sysinit).
 *       Care should be taken to ensure this remains the case if in the future this function were to be called as part
 *       of the BSP initialization.
 *
 * @note This function will delay for **at least** the specified duration. Due to overhead in calculating the correct number
 *       of loops to delay, very small delay values (generally 1-5 microseconds) may be significantly longer than specified.
 *       Approximate overhead for this function is as follows:
 *           - CM4: 20-50 cycles
 *           - CM33: 10-60 cycles
 *           - CM23: 75-200 cycles
 *
 * @note If more accurate microsecond timing must be performed in software it is recommended to use
 *       bsp_prv_software_delay_loop() directly. In this case, use BSP_DELAY_LOOP_CYCLES or BSP_DELAY_LOOPS_CALCULATE()
 *       to convert a calculated delay cycle count to a number of software delay loops.
 *
 * @note Delays may be longer than expected when compiler optimization is turned off.
 *
 * @warning The delay will be longer than specified on CM23 devices when the core clock is greater than 32 MHz. Setting
 *          BSP_DELAY_LOOP_CYCLES to 6 will improve accuracy at 48 MHz but will result in shorter than expected delays
 *          at lower speeds.
 **********************************************************************************************************************/

void R_BSP_SoftwareDelay (uint32_t delay, bsp_delay_units_t units)
{
    uint32_t iclk_hz;
    uint32_t cycles_requested;
    uint32_t ns_per_cycle;
    uint32_t loops_required = 0;
    uint32_t total_us       = (delay * units);                        /** Convert the requested time to microseconds. */
    uint64_t ns_64bits;

    iclk_hz = SystemCoreClock;                                        /** Get the system clock frequency in Hz. */

    /* Running on the Sub-clock (32768 Hz) there are 30517 ns/cycle. This means one cycle takes 31 us. One execution
     * loop of the delay_loop takes 6 cycles which at 32768 Hz is 180 us. That does not include the overhead below prior to even getting
     * to the delay loop. Given this, at this frequency anything less then a delay request of 122 us will not even generate a single
     * pass through the delay loop.  For this reason small delays (<=~200 us) at this slow clock rate will not be possible and such a request
     * will generate a minimum delay of ~200 us.*/
    ns_per_cycle = BSP_DELAY_NS_PER_SECOND / iclk_hz;                 /** Get the # of nanoseconds/cycle. */

    /* We want to get the time in total nanoseconds but need to be conscious of overflowing 32 bits. We also do not want to do 64 bit */
    /* division as that pulls in a division library. */
    ns_64bits = (uint64_t) total_us * (uint64_t) BSP_DELAY_NS_PER_US; // Convert to ns.

    /* Have we overflowed 32 bits? */
    if (ns_64bits <= UINT32_MAX)
    {
        /* No, we will not overflow. */
        cycles_requested = ((uint32_t) ns_64bits / ns_per_cycle);
        loops_required   = cycles_requested / BSP_DELAY_LOOP_CYCLES;
    }
    else
    {
        /* We did overflow. Try dividing down first. */
        total_us  = (total_us / (ns_per_cycle * BSP_DELAY_LOOP_CYCLES));
        ns_64bits = (uint64_t) total_us * (uint64_t) BSP_DELAY_NS_PER_US; // Convert to ns.

        /* Have we overflowed 32 bits? */
        if (ns_64bits <= UINT32_MAX)
        {
            /* No, we will not overflow. */
            loops_required = (uint32_t) ns_64bits;
        }
        else
        {
            /* We still overflowed, use the max count for cycles */
            loops_required = UINT32_MAX;
        }
    }

    /** Only delay if the supplied parameters constitute a delay. */
    if (loops_required > (uint32_t) 0)
    {
        bsp_prv_software_delay_loop(loops_required);
    }
}

/** @} (end addtogroup BSP_MCU) */

/*******************************************************************************************************************//**
 *        This assembly language routine takes roughly 4 cycles per loop. 2 additional cycles
 *        occur when the loop exits. The 'naked' attribute  indicates that the specified function does not need
 *        prologue/epilogue sequences generated by the compiler.
 * @param[in]     loop_cnt  The number of loops to iterate.
 **********************************************************************************************************************/
BSP_ATTRIBUTE_STACKLESS void bsp_prv_software_delay_loop (__attribute__(
                                                              (unused)) uint32_t loop_cnt)
{
    __asm volatile (
#if defined(RENESAS_CORTEX_M85) && (defined(__ARMCC_VERSION) || defined(__GNUC__))

        /* Optimize inner loop execution time on CM85 cores (Alignment allows for instruction fusion). */
        ".align 8\n"
#endif
        "sw_delay_loop:         \n"
#if defined(__ICCARM__) || defined(__ARMCC_VERSION)
        "   subs r0, #1         \n"    ///< 1 cycle
#elif defined(__GNUC__)
        "   sub r0, r0, #1      \n"    ///< 1 cycle
#endif

        "   cmp r0, #0          \n"    ///< 1 cycle

/* CM0 and CM23 have a different instruction set */
#if defined(__CORE_CM0PLUS_H_GENERIC) || defined(__CORE_CM23_H_GENERIC)
        "   bne sw_delay_loop   \n"    ///< 2 cycles
#else
        "   bne.n sw_delay_loop \n"    ///< 2 cycles
#endif
        "   bx lr               \n");  ///< 2 cycles
}
