/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_REGISTER_PROTECTION_H
#define BSP_REGISTER_PROTECTION_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/** The different types of registers that can be protected. */
typedef enum e_bsp_reg_protect
{
    /** Enables writing to the registers related to the clock generation circuit. */
    BSP_REG_PROTECT_CGC = 0,

    /** Enables writing to the registers related to operating modes, low power consumption, and battery backup
     * function. */
    BSP_REG_PROTECT_OM_LPC_BATT,

    /** Enables writing to the registers related to the LVD: LVCMPCR, LVDLVLR, LVD1CR0, LVD1CR1, LVD1SR, LVD2CR0,
     * LVD2CR1, LVD2SR. */
    BSP_REG_PROTECT_LVD,

    /** Enables writing to the registers related to the security function. */
    BSP_REG_PROTECT_SAR,

    /** Enables writing to the registers related to reset control. */
    BSP_REG_PROTECT_RESET,
} bsp_reg_protect_t;

/** @} (end addtogroup BSP_MCU) */

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/* Public functions defined in bsp.h */
void bsp_register_protect_open(void);  // Used internally by BSP

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
