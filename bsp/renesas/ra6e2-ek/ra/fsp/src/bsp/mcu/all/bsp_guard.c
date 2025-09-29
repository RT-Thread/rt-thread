/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "bsp_guard.h"

/* Only the secure project has nonsecure callable functions. */
#if BSP_TZ_SECURE_BUILD

/* If the CGG Security Attribution is configured to secure access only. */
 #if BSP_CFG_CLOCKS_SECURE == 1

/*******************************************************************************************************************//**
 * Set the callback used by the secure project to notify the nonsecure project when the clock settings have changed.
 *
 * @retval FSP_SUCCESS              Callback set.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 **********************************************************************************************************************/
BSP_CMSE_NONSECURE_ENTRY fsp_err_t R_BSP_ClockUpdateCallbackSet (bsp_clock_update_callback_t        p_callback,
                                                                 bsp_clock_update_callback_args_t * p_callback_memory)
{
    bsp_clock_update_callback_t p_callback_checked =
        (bsp_clock_update_callback_t) cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE);

    bsp_clock_update_callback_args_t * p_callback_memory_checked =
        (bsp_clock_update_callback_args_t *) cmse_check_address_range(p_callback_memory,
                                                                      sizeof(bsp_clock_update_callback_args_t),
                                                                      CMSE_AU_NONSECURE);
    FSP_ASSERT(p_callback == p_callback_checked);
    FSP_ASSERT(p_callback_memory == p_callback_memory_checked);

    r_bsp_clock_update_callback_set(p_callback_checked, p_callback_memory_checked);

    return FSP_SUCCESS;
}

 #endif

#endif
