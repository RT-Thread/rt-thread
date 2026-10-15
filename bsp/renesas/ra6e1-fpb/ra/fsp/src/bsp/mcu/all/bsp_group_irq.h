/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_GROUP_IRQ_H
#define BSP_GROUP_IRQ_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#ifndef BSP_OVERRIDE_GROUP_IRQ_T

/** Which interrupts can have callbacks registered. */
typedef enum e_bsp_grp_irq
{
    BSP_GRP_IRQ_IWDT_ERROR      = 0,   ///< IWDT underflow/refresh error has occurred
    BSP_GRP_IRQ_WDT_ERROR       = 1,   ///< WDT underflow/refresh error has occurred
    BSP_GRP_IRQ_LVD1            = 2,   ///< Voltage monitoring 1 interrupt
    BSP_GRP_IRQ_LVD2            = 3,   ///< Voltage monitoring 2 interrupt
    BSP_GRP_IRQ_VBATT           = 4,   ///< VBATT monitor interrupt
    BSP_GRP_IRQ_OSC_STOP_DETECT = 6,   ///< Oscillation stop is detected
    BSP_GRP_IRQ_NMI_PIN         = 7,   ///< NMI Pin interrupt
    BSP_GRP_IRQ_RAM_PARITY      = 8,   ///< RAM Parity Error
    BSP_GRP_IRQ_RAM_ECC         = 9,   ///< RAM ECC Error
    BSP_GRP_IRQ_MPU_BUS_SLAVE   = 10,  ///< MPU Bus Slave Error
    BSP_GRP_IRQ_MPU_BUS_MASTER  = 11,  ///< MPU Bus Master Error
    BSP_GRP_IRQ_MPU_STACK       = 12,  ///< MPU Stack Error
    BSP_GRP_IRQ_TRUSTZONE       = 13,  ///< MPU Stack Error
    BSP_GRP_IRQ_CACHE_PARITY    = 15,  ///< MPU Stack Error
} bsp_grp_irq_t;

#endif

/* Callback type. */
typedef void (* bsp_grp_irq_cb_t)(bsp_grp_irq_t irq);

/** @} (end addtogroup BSP_MCU) */

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/* Public functions defined in bsp.h */
void bsp_group_interrupt_open(void);   // Used internally by BSP

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
