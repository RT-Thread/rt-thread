/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_RTC_RA6W1_H
#define BSP_RTC_RA6W1_H

#include "bsp_api.h"
#ifdef UNIT_TESTING
 #include "fake_regs.h"
#endif
/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_PRV_RTC_CLOCK_TO_SEC(clk)    (((unsigned long long) clk) >> 15ULL)
#define __uptime()                       BSP_PRV_RTC_CLOCK_TO_SEC(R_BSP_SystemRtcCountGet()) // Get elapsed time after system power up(for 64bit)

// TIN-TODO: This macro was located in bsp_common and guarded with the same features as the RTC function.
// Consider moving this under a header file of the power manager.

/* Alias name of BSP_WAKEUP_RESET_WITH_RETENTION */
#define BSP_WAKEUP_RETENTION    (BSP_WAKEUP_RESET_WITH_RETENTION)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Gets the clock count of RTC.
 *
 * @return     The value of the RTC free running counter.
 **********************************************************************************************************************/
static inline uint64_t R_BSP_SystemRtcCountGet (void)
{
    volatile uint64_t ret_time = 0;

    /* Check RTC register mirror done */
    if (RTC->RTC_IRQ_STATUS_REG_b.RTC_IRQ_STATUS == 0x01)
    {
        /* faster to access register on rtc thourgh mirror.*/
        ret_time |= RTC->RTC_MR_FRC0_REG;
        ret_time |= (uint64_t) (RTC->RTC_MR_FRC1_REG) << 32;
    }
    else
    {
        /* direct to access register on rtc */
        ret_time |= RTC->FRC_CNT_0_REG;
        ret_time |= (uint64_t) RTC->FRC_CNT_1_REG << 32;
    }

    return ret_time;
}

/*******************************************************************************************************************//**
 * Calculate difference between two RTC values. Both values are assumed to be 36 bits wide.
 *
 * @param [in] from    The first 36-bit value.
 * @param [in] to      The second 36-bit value.
 *
 * @return     The RTC difference between the two values.
 **********************************************************************************************************************/
static inline uint64_t R_BSP_SystemRtcDiff (uint64_t from, uint64_t to)
{
    const int64_t full_range = (1LL << 36);
    const int64_t half_range = full_range >> 1;
    const int64_t diff       = (int64_t) to - (int64_t) from;

    if (diff >= 0)
    {
        /* 'from' comes after 'to', but it wrapped : 'to' comes after 'from', no wrapping */
        return diff >= half_range ? 0 : (uint64_t) (diff);
    }
    else
    {
        /* 'from' comes after 'to', no wrapping : 'to' comes after 'from', but it wrapped */
        return diff >= -half_range ? 0 : (uint64_t) (diff + full_range);
    }
}

/*******************************************************************************************************************//**
 * Busy wait function based on the RTC clock.
 *
 * @param [in] delay_clk    The number of RTC clock cycles that this function will block for.
 **********************************************************************************************************************/
static inline void R_BSP_SystemRtcWaitClk (int32_t delay_clk)
{
    uint64_t prev_clk = R_BSP_SystemRtcCountGet();
    do
    {
        uint64_t curr_clk = R_BSP_SystemRtcCountGet();

        if (prev_clk != curr_clk)
        {
            delay_clk--;
            prev_clk = curr_clk;
        }
    } while (delay_clk > 0);
}

#endif
