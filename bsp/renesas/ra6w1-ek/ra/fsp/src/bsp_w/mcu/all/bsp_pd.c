/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#ifdef UNIT_TESTING
 #include "fake_regs.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

// Check if the RTC power domain exists in the MCU
#if (BSP_MCU_GROUP_RA6B1) || (BSP_MCU_GROUP_RA6U1) || (BSP_MCU_GROUP_RA6B2) || (BSP_MCU_GROUP_RA6W3)
 #define PD_RTC_CHECK    (BSP_PD_RTC == power_domain) // All power domains use PMU_CTRL_REG, except RTC which uses PMU_AON_CTRL_REG
#elif (BSP_MCU_GROUP_RA6W1)
 #define PD_RTC_CHECK    0
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef void (* power_domain_ctrl_func)(uint32_t mask, bool is_aon);

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
TESTABLE_STATIC uint8_t bsp_prv_pd_ref_cnt[BSP_PD_ID_COUNT];

__STATIC_FORCEINLINE bool valid_pd_check (uint32_t pd_id)
{
    return pd_id < BSP_PD_ID_COUNT;
}

#ifdef UNIT_TESTING
BSP_WEAK_REFERENCE void hook_for_testable_busy_register_check(uintptr_t reg, uint32_t mask);

BSP_WEAK_REFERENCE void hook_for_testable_busy_register_check (uintptr_t reg, uint32_t mask)
{
    /* Do nothing. */
    (void) reg;
    (void) mask;
}

#endif

__STATIC_FORCEINLINE bool pd_is_up_check (uint32_t is_up_mask)
{
    if (0 == is_up_mask)
    {
        return true;
    }

    return bsp_prv_pd_is_up_check(is_up_mask);
}

__STATIC_FORCEINLINE bool nonzero_cnt_check (uint32_t pd_id)
{
    return bsp_prv_pd_ref_cnt[pd_id] > 0;
}

__STATIC_FORCEINLINE void atomic_use_pd (bsp_power_domain_t power_domain, uint32_t mask)
{
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    if ((0 == bsp_prv_pd_ref_cnt[power_domain]++) && (mask != 0))
    {
        bsp_prv_pd_enable(mask, PD_RTC_CHECK);
    }

    FSP_CRITICAL_SECTION_EXIT;
}

__STATIC_FORCEINLINE void atomic_unuse_pd (bsp_power_domain_t power_domain, uint32_t mask)
{
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    if ((0 == --bsp_prv_pd_ref_cnt[power_domain]) && (mask != 0))
    {
        bsp_prv_pd_disable(mask, PD_RTC_CHECK);
    }

    FSP_CRITICAL_SECTION_EXIT;
}

__STATIC_FORCEINLINE void enable_with_counter (uint32_t pd_id)
{
    // compute masks before turning off interrupts
    uint32_t sleep_mask;
    uint32_t is_up_mask;

    bsp_prv_pd_masks_get((bsp_power_domain_t) pd_id, &sleep_mask, &is_up_mask);
    atomic_use_pd((bsp_power_domain_t) pd_id, sleep_mask);

    while (!pd_is_up_check(is_up_mask))
    {
#ifdef UNIT_TESTING
        hook_for_testable_busy_register_check((uintptr_t) &CRG_TOP->SYS_STAT_REG, is_up_mask);
#endif
    }
}

__STATIC_FORCEINLINE void disable_with_counter (bsp_power_domain_t power_domain)
{
    // compute masks before turning off interrupts
    uint32_t sleep_mask;
    uint32_t is_up_mask;

    bsp_prv_pd_masks_get(power_domain, &sleep_mask, &is_up_mask);
    atomic_unuse_pd(power_domain, sleep_mask);
}

__STATIC_FORCEINLINE void atomic_control (power_domain_ctrl_func func, bsp_power_domain_t power_domain)
{
    // compute masks before turning off interrupts
    uint32_t sleep_mask;
    uint32_t is_up_mask;
    bool     is_aon = PD_RTC_CHECK;

    bsp_prv_pd_masks_get(power_domain, &sleep_mask, &is_up_mask);

    if (0 == sleep_mask)
    {
        return;
    }

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    func(sleep_mask, is_aon);

    FSP_CRITICAL_SECTION_EXIT;
}

__STATIC_FORCEINLINE void atomic_enable (bsp_power_domain_t power_domain)
{
    atomic_control(bsp_prv_pd_enable, power_domain);
}

__STATIC_FORCEINLINE void atomic_disable (bsp_power_domain_t power_domain)
{
    atomic_control(bsp_prv_pd_disable, power_domain);
}

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/**
 * Initialize (zero) the reference counters of all power domains
 */
void bsp_pd_init (void)
{
    for (bsp_power_domain_t pd = (bsp_power_domain_t) 0; pd < BSP_PD_ID_COUNT; pd++)
    {
        bsp_prv_pd_ref_cnt[pd] = 0;
    }
}

/**
 * Denote starting the use of a power domain
 *
 * If the power domain \p pd_id was previously unused, it will be enabled.
 * A per-power-domain reference counter is used to allow for nested calls of this function.
 *
 * @param [in] pd_id   ID of the power domain to start using
 *
 * @sa bsp_pd_unuse
 */
BSP_PLACE_CODE_IN_RAM void bsp_pd_use (uint32_t pd_id)
{
    BSP_CHECK_DEBUG(valid_pd_check(pd_id));

    enable_with_counter(pd_id);

    /* detect overflow */
    BSP_CHECK_FATAL(nonzero_cnt_check(pd_id));
}

/**
 * Denote ending the use of a power domain
 *
 * A per-power-domain reference counter is used to allow for nested calls of this function.
 * If the reference counter of the power domain \p pd_id reaches zero, the power domain will be disabled.
 *
 * @param [in] pd_id   ID of the power domain to stop using
 *
 * @sa bsp_pd_use
 */
BSP_PLACE_CODE_IN_RAM void bsp_pd_unuse (uint32_t pd_id)
{
    BSP_CHECK_DEBUG(valid_pd_check(pd_id));

    /* detect imminent underflow */
    BSP_CHECK_FATAL(nonzero_cnt_check(pd_id));

    disable_with_counter((bsp_power_domain_t) pd_id);
}

/**
 * Check is a power domain is denoted as used (i.e. its reference counter is non-zero)
 *
 * @param [in] pd_id    ID of the power domain to check
 */
BSP_PLACE_CODE_IN_RAM bool bsp_pd_used_check (uint32_t pd_id)
{
    return nonzero_cnt_check(pd_id);
}

/**
 * Return the "IS_UP" status of a power domain
 *
 * @param [in] pd_id    ID of the power domain to check
 *
 * @retval true         if the power domain is up (activated)
 * @retval false        if the power domain is down (deactivated)
 */
bool bsp_pd_is_up_check (uint32_t pd_id)
{
    uint32_t sleep_mask;
    uint32_t is_up_mask;

    bsp_prv_pd_masks_get((bsp_power_domain_t) pd_id, &sleep_mask, &is_up_mask);

    return pd_is_up_check(is_up_mask);
}

/**
 * Enable (i.e. take out of power-down) a power domain
 *
 * @param [in] pd_id    ID of the power domain to enable
 */
BSP_PLACE_CODE_IN_RAM void bsp_pd_enable (uint32_t pd_id)
{
    BSP_CHECK_DEBUG(valid_pd_check(pd_id));

    atomic_enable((bsp_power_domain_t) pd_id);
}

/**
 * Disable (i.e. put in power-down) a power domain
 *
 * @param [in] pd_id    ID of the power domain to disable
 */
BSP_PLACE_CODE_IN_RAM void bsp_pd_disable (uint32_t pd_id)
{
    BSP_CHECK_DEBUG(valid_pd_check(pd_id));

    atomic_disable((bsp_power_domain_t) pd_id);
}

/** @} (end addtogroup BSP_MCU) */
