/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_RSIP_H
#define BSP_RSIP_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
#if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1

/**
 * \brief Retrieve key ring and shared key index values from NVR.
 */
BSP_PLACE_CODE_IN_RAM void bsp_prv_rsip_fetch_KeyIndex(void);

/**
 * \brief Get rsip_install_key_ring_index value.
 */
__STATIC_FORCEINLINE uint32_t R_BSP_InstallKeyRingIndexGet (void)
{
    extern volatile uint32_t rsip_install_key_ring_index;

    return rsip_install_key_ring_index;
}

/**
 * \brief Get rsip_SharedKeyIndex value.
 */
__STATIC_FORCEINLINE uint32_t R_BSP_SharedKeyIndexGet (void)
{
    extern volatile uint32_t rsip_SharedKeyIndex;

    return rsip_SharedKeyIndex;
}

#endif

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
