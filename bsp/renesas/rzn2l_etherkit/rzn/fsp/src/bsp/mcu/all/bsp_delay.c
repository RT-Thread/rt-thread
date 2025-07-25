/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "bsp_delay.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_DELAY_NS_PER_SECOND         (1000000000)
#define BSP_DELAY_NS_PER_US             (1000)
#define BSP_DELAY_SIGNIFICANT_DIGITS    (10000)

/***********************************************************************************************************************
 * Typedef definitions
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
 *              At 200 MHz one cycle takes 1/200 microsecond or 5 nanoseconds.@n
 *              At 800 MHz one cycle takes 1/800 microsecond or 1.25 nanoseconds.@n
 *              Therefore one run through bsp_prv_software_delay_loop() takes:
 *              ~ (1.25 * BSP_DELAY_LOOP_CYCLES) or 5 ns.
 *              A delay of 2 us therefore requires 2000ns/5ns or 400 loops.
 *
 *              The 'theoretical' maximum delay that may be obtained is determined by a full 32 bit loop count and the system clock rate.
 *              @200MHz:  ((0xFFFFFFFF loops * 4 cycles /loop) / 200000000) = 85 seconds.
 *              @800MHz:  ((0xFFFFFFFF loops * 4 cycles /loop) / 800000000) = 21 seconds.
 *
 *              Note that requests for very large delays will be affected by rounding in the calculations and the actual delay
 *              achieved may be slightly longer. @200 MHz, for example, a request for 85 seconds will be closer to 86 seconds.
 *
 *              Note also that if the calculations result in a loop_cnt of zero, the bsp_prv_software_delay_loop() function is not called
 *              at all. In this case the requested delay is too small (nanoseconds) to be carried out by the loop itself, and the
 *              overhead associated with executing the code to just get to this point has certainly satisfied the requested delay.
 *
 *
 * @note R_BSP_SoftwareDelay() obtains the system clock value by reading the SystemCoreClock variable.
 *       Therefore, R_BSP_SoftwareDelay() cannot be used until after the SystemCoreClock has been updated.
 *       The SystemCoreClock is updated by executing SystemCoreClockUpdate() in startup;
 *       users cannot call R_BSP_SoftwareDelay() inside R_BSP_WarmStart(BSP_WARM_START_RESET) and
 *       R_BSP_WarmStart(BSP_WARM_START_POST_CLOCK) since they are invoked before SystemCoreClockUpdate() in startup.
 *
 * @note This function will delay for **at least** the specified duration. Due to overhead in calculating the correct number
 *       of loops to delay, very small delay values (generally 1-5 microseconds) may be significantly longer than specified.
 *       Approximate overhead for this function is as follows:
 *           - CR52: 87-94 cycles
 *
 * @note If more accurate microsecond timing must be performed in software it is recommended to use
 *       bsp_prv_software_delay_loop() directly. In this case, use BSP_DELAY_LOOP_CYCLES or BSP_DELAY_LOOPS_CALCULATE()
 *       to convert a calculated delay cycle count to a number of software delay loops.
 *
 * @note Delays may be longer than expected when compiler optimization is turned off.
 **********************************************************************************************************************/

void R_BSP_SoftwareDelay (uint32_t delay, bsp_delay_units_t units)
{
    uint32_t cpu_hz;
    uint32_t cycles_requested;
    uint32_t ns_per_cycle;
    uint32_t loops_required = 0;
    uint32_t total_us       = (delay * units);                                        /** Convert the requested time to microseconds. */
    uint64_t ns_64bits;

    cpu_hz = SystemCoreClock;                                                         /** Get the system clock frequency in Hz. */

    /* BSP_DELAY_SIGNIFICANT_DIGITS to keep the decimal point. */
    ns_per_cycle = BSP_DELAY_NS_PER_SECOND / (cpu_hz / BSP_DELAY_SIGNIFICANT_DIGITS); /** Get the # of nanoseconds/cycle. */

    /* We want to get the time in total nanoseconds but need to be conscious of overflowing 32 bits. We also do not want to do 64 bit */
    /* division as that pulls in a division library. */
    ns_64bits = (uint64_t) total_us * (uint64_t) BSP_DELAY_NS_PER_US;                 // Convert to ns.

    /* Have we overflowed 32 bits? */
    if (ns_64bits <= UINT32_MAX)
    {
        ns_64bits = ns_64bits * (uint64_t) BSP_DELAY_SIGNIFICANT_DIGITS;

        /* No, we will not overflow.
         * Multiply the calculation result by BSP_DELAY_SIGNIFICANT_DIGITS to disable the retention of the decimal point.*/
        cycles_requested = (uint32_t) (ns_64bits / (uint64_t) ns_per_cycle);
        loops_required   = cycles_requested / BSP_DELAY_LOOP_CYCLES;
    }
    else
    {
        /* We did overflow. Try dividing down first.
         * Multiply the calculation result by BSP_DELAY_SIGNIFICANT_DIGITS to disable the retention of the decimal point.*/
        total_us  = (total_us / (ns_per_cycle * BSP_DELAY_LOOP_CYCLES)) * BSP_DELAY_SIGNIFICANT_DIGITS;
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
void bsp_prv_software_delay_loop (uint32_t loop_cnt)
{
    r_bsp_software_delay_loop(loop_cnt);
}
