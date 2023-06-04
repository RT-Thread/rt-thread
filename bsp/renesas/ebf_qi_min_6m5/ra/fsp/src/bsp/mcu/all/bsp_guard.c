/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#include "bsp_guard.h"

/* Only the secure project has nonsecure callable functions. */
#if BSP_TZ_SECURE_BUILD

/* If the CGG Security Attribution is configured to secure access only. */
 #if BSP_TZ_CFG_CGFSAR != 0xFFFFFFFFU

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
