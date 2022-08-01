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

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <stdint.h>
#include "bsp_api.h"

#if BSP_PRV_POWER_USE_DCDC

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #define BSP_PRV_LDO_STABILIZATION_TIME_US    (60U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Switch from DCDC to LDO. Requires LPM register protection and interrupts to be disabled.
 *
 * This function follows the procedure given in the RA2L1 User's Manual (R01UH0853EJ0100) Section 10.5.1 (4) "Switching
 * from High-speed/Middle-speed mode (DCDC power mode) to High-speed/Middle-speed mode (LDO power mode)"
 **********************************************************************************************************************/
static inline void bsp_power_dcdc_disable (bsp_power_mode_t mode)
{
    /* Save all module stop bits, then stop all peripherals. */
    uint32_t mstpcrb = R_MSTP->MSTPCRB;
    R_MSTP->MSTPCRB = UINT32_MAX;
    uint32_t mstpcrc = R_MSTP->MSTPCRC;
    R_MSTP->MSTPCRC = UINT32_MAX;
    uint32_t mstpcrd = R_MSTP->MSTPCRD;
    R_MSTP->MSTPCRD = UINT32_MAX;

    /* Switch to LDO. */
    R_SYSTEM->DCDCCTL = (uint8_t) mode;

    /* Wait for LDO to stabilize. */
    R_BSP_SoftwareDelay(BSP_PRV_LDO_STABILIZATION_TIME_US, BSP_DELAY_UNITS_MICROSECONDS);

    /* Restore all module stop bits. */
    R_MSTP->MSTPCRB = mstpcrb;
    R_MSTP->MSTPCRC = mstpcrc;
    R_MSTP->MSTPCRD = mstpcrd;
}

/***********************************************************************************************************************
 * Switch from LDO to DCDC. Requires LPM register protection and interrupts to be disabled.
 *
 * This function follows the procedure given in the RA2L1 User's Manual (R01UH0853EJ0100) Section 10.5.1 (3) "Switching
 * from the High-Speed/Middle-Speed mode (LDO power mode) to the High-speed/Middle speed mode (DCDC power mode)"
 **********************************************************************************************************************/
static inline void bsp_power_dcdc_enable ()
{
    /* Enable DCDC IO buffer. */
    uint8_t dcdcctl = R_SYSTEM->DCDCCTL | R_SYSTEM_DCDCCTL_STOPZA_Msk;
    R_SYSTEM->DCDCCTL = dcdcctl;

    /* Turn on DCDC Vref. */
    R_SYSTEM->DCDCCTL = dcdcctl & (uint8_t) (~R_SYSTEM_DCDCCTL_PD_Msk);

    /* Wait for Vref to stabilize. */
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);

    /* Switch DCDC Vref to low-power mode. */
    R_SYSTEM->DCDCCTL = 0x10;

    /* Wait for Vref to stabilize. */
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);

    /* Turn off LDO and turn on DCDC. */
    R_SYSTEM->DCDCCTL = 0x11;

    /* Wait for DCDC to stabilize. */
    R_BSP_SoftwareDelay(2, BSP_DELAY_UNITS_MICROSECONDS);

    /* Enable DCDC overcurrent protection. */
    R_SYSTEM->DCDCCTL = 0x13;
}

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA2L1
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Select either the LDO or DCDC regulator and/or update the MCU supply voltage range. Returns the previously selected
 * mode.
 *
 * @note DCDC mode has the following limitations:
 *         - Supply voltage must be 2.4V or greater
 *         - Low- and Subosc-speed modes are not available
 *         - Software Standby is not available
 *       Ensure these limitations are respected before entering DCDC mode. If supply voltage may drop below 2.4V during
 *       operation, configure a LVD channel to interrupt or reset the MCU near this threshold to switch back to the LDO.
 *
 * @note Switching to DCDC mode temporarily disables all interrupts and blocks for 22 microseconds; switching to LDO
 *       from DCDC temporarily disables all peripherals and interrupts and blocks for 60 microseconds.
 *
 * @note If the supply voltage falls outside the range originally specified when starting the DCDC regulator, call this
 *       function again with the updated supply voltage.
 *
 * @return  The previously selected power mode.
 **********************************************************************************************************************/
bsp_power_mode_t R_BSP_PowerModeSet (bsp_power_mode_t mode)
{
    /* Get current mode to return to caller. */
    bsp_power_mode_t previous_mode = R_SYSTEM->DCDCCTL & R_SYSTEM_DCDCCTL_DCDCON_Msk ?
                                     (bsp_power_mode_t) R_SYSTEM->VCCSEL : BSP_POWER_MODE_LDO;

    /* Enable writing to Low Power Mode registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_OM_LPC_BATT);

    /* Set VCCSEL if a DCDC mode is selected. */
    bool dcdc_mode = mode < BSP_POWER_MODE_LDO;
    if (dcdc_mode)
    {
        /* Set supply voltage range. */
        R_SYSTEM->VCCSEL = (uint8_t) mode;
    }

    /* Only change mode if the specified mode is not already set. */
    if (dcdc_mode != (previous_mode < BSP_POWER_MODE_LDO))
    {
        /* Enter critical section to prevent any peripheral or power mode changes while transitioning. */
        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;

        if (mode >= BSP_POWER_MODE_LDO)
        {
            bsp_power_dcdc_disable(mode);
        }
        else
        {
            bsp_power_dcdc_enable();
        }

        FSP_CRITICAL_SECTION_EXIT;
    }

    /* Disable writing to Low Power Mode registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_OM_LPC_BATT);

    return previous_mode;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup BSP_MCU_RA2L1)
 **********************************************************************************************************************/

#endif                                 /* BSP_PRV_POWER_USE_DCDC */
