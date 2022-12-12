/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef BSP_POWER_H
#define BSP_POWER_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA2L1
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#if BSP_FEATURE_BSP_HAS_DCDC_REGULATOR
 #define BSP_PRV_POWER_USE_DCDC       (BSP_CFG_DCDC_ENABLE)
#else
 #define BSP_PRV_POWER_USE_DCDC       (0)
#endif

#define BSP_PRV_POWER_DCDC_DISABLE    (0)
#define BSP_PRV_POWER_DCDC_MANUAL     (1)
#define BSP_PRV_POWER_DCDC_STARTUP    (2)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Voltage regulator mode */
typedef enum e_bsp_power_mode_t
{
    BSP_POWER_MODE_DCDC_2V4_TO_2V7 = 3, ///< DCDC mode; 2.4V to 2.7V supply
    BSP_POWER_MODE_DCDC_2V7_TO_3V6 = 0, ///< DCDC mode; 2.7V to 3.6V supply
    BSP_POWER_MODE_DCDC_3V6_TO_4V5 = 1, ///< DCDC mode; 3.6V to 4.5V supply
    BSP_POWER_MODE_DCDC_4V5_TO_5V5 = 2, ///< DCDC mode; 4.5V to 5.5V supply

    BSP_POWER_MODE_LDO       = 0x90,    ///< LDO mode
    BSP_POWER_MODE_LDO_BOOST = 0xB0     // Alternate DCDCCTL value for entering subclock and low-power modes
                                        // (see RA2L1 User's Manual (R01UH0853EJ0100) Section 10.5.1 (5))
} bsp_power_mode_t;

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

bsp_power_mode_t R_BSP_PowerModeSet(bsp_power_mode_t mode);

/*******************************************************************************************************************//**
 * @} (end addtogroup BSP_MCU_RA2L1)
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
