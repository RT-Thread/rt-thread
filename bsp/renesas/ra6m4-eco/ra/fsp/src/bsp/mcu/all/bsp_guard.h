/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_GUARD_H
#define BSP_GUARD_H

#include "bsp_api.h"

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 *
 * @{
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#if BSP_TZ_SECURE_BUILD || BSP_TZ_NONSECURE_BUILD
BSP_CMSE_NONSECURE_ENTRY fsp_err_t R_BSP_ClockUpdateCallbackSet(bsp_clock_update_callback_t        p_callback,
                                                                bsp_clock_update_callback_args_t * p_callback_memory);

#endif

/** @} (end addtogroup BSP_MCU) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
