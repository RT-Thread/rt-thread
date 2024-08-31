/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "usb.h"
#include "fsl_device_registers.h"

#include "usb_phy.h"

void *USB_EhciPhyGetBase(uint8_t controllerId)
{
    void *usbPhyBase = NULL;
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
#if defined(USBPHY_STACK_BASE_ADDRS)
    uint32_t usbphy_base[] = USBPHY_STACK_BASE_ADDRS;
#else
    uint32_t usbphy_base[] = USBPHY_BASE_ADDRS;
#endif
    uint32_t *temp;
    if (controllerId < (uint8_t)kUSB_ControllerEhci0)
    {
        return NULL;
    }

    if ((controllerId == (uint8_t)kUSB_ControllerEhci0) || (controllerId == (uint8_t)kUSB_ControllerEhci1))
    {
        controllerId = controllerId - (uint8_t)kUSB_ControllerEhci0;
    }
    else if ((controllerId == (uint8_t)kUSB_ControllerLpcIp3511Hs0) ||
             (controllerId == (uint8_t)kUSB_ControllerLpcIp3511Hs1))
    {
        controllerId = controllerId - (uint8_t)kUSB_ControllerLpcIp3511Hs0;
    }
    else if ((controllerId == (uint8_t)kUSB_ControllerIp3516Hs0) || (controllerId == (uint8_t)kUSB_ControllerIp3516Hs1))
    {
        controllerId = controllerId - (uint8_t)kUSB_ControllerIp3516Hs0;
    }
    else
    {
        return NULL;
    }

    if (controllerId < (sizeof(usbphy_base) / sizeof(usbphy_base[0])))
    {
        temp       = (uint32_t *)usbphy_base[controllerId];
        usbPhyBase = (void *)temp;
    }
    else
    {
        return NULL;
    }
#endif
    return usbPhyBase;
}

/*!
 * @brief ehci phy initialization.
 *
 * This function initialize ehci phy IP.
 *
 * @param[in] controllerId   ehci controller id, please reference to #usb_controller_index_t.
 * @param[in] freq            the external input clock.
 *                            for example: if the external input clock is 16M, the parameter freq should be 16000000.
 *
 * @retval kStatus_USB_Success      cancel successfully.
 * @retval kStatus_USB_Error        the freq value is incorrect.
 */
uint32_t USB_EhciPhyInit(uint8_t controllerId, uint32_t freq, usb_phy_config_struct_t *phyConfig)
{
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
    USBPHY_Type *usbPhyBase;

    usbPhyBase = (USBPHY_Type *)USB_EhciPhyGetBase(controllerId);
    if (NULL == usbPhyBase)
    {
        return (uint8_t)kStatus_USB_Error;
    }

#if ((defined FSL_FEATURE_SOC_ANATOP_COUNT) && (FSL_FEATURE_SOC_ANATOP_COUNT > 0U))
    ANATOP->HW_ANADIG_REG_3P0.RW =
        (ANATOP->HW_ANADIG_REG_3P0.RW &
         (~(ANATOP_HW_ANADIG_REG_3P0_OUTPUT_TRG(0x1F) | ANATOP_HW_ANADIG_REG_3P0_ENABLE_ILIMIT_MASK))) |
        ANATOP_HW_ANADIG_REG_3P0_OUTPUT_TRG(0x17) | ANATOP_HW_ANADIG_REG_3P0_ENABLE_LINREG_MASK;
    ANATOP->HW_ANADIG_USB2_CHRG_DETECT.SET =
        ANATOP_HW_ANADIG_USB2_CHRG_DETECT_CHK_CHRG_B_MASK | ANATOP_HW_ANADIG_USB2_CHRG_DETECT_EN_B_MASK;
#endif

#if (defined USB_ANALOG)
    USB_ANALOG->INSTANCE[controllerId - (uint8_t)kUSB_ControllerEhci0].CHRG_DETECT_SET =
        USB_ANALOG_CHRG_DETECT_CHK_CHRG_B(1) | USB_ANALOG_CHRG_DETECT_EN_B(1);
#endif

#if ((!(defined FSL_FEATURE_SOC_CCM_ANALOG_COUNT)) && (!(defined FSL_FEATURE_SOC_ANATOP_COUNT)))

    usbPhyBase->TRIM_OVERRIDE_EN = 0x001fU; /* override IFR value */
#endif
    usbPhyBase->CTRL |= USBPHY_CTRL_SET_ENUTMILEVEL2_MASK; /* support LS device. */
    usbPhyBase->CTRL |= USBPHY_CTRL_SET_ENUTMILEVEL3_MASK; /* support external FS Hub with LS device connected. */
    /* PWD register provides overall control of the PHY power state */
    usbPhyBase->PWD = 0U;
    if (((uint8_t)kUSB_ControllerIp3516Hs0 == controllerId) || ((uint8_t)kUSB_ControllerIp3516Hs1 == controllerId) ||
        ((uint8_t)kUSB_ControllerLpcIp3511Hs0 == controllerId) ||
        ((uint8_t)kUSB_ControllerLpcIp3511Hs1 == controllerId))
    {
        usbPhyBase->CTRL_SET = USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE_MASK;
        usbPhyBase->CTRL_SET = USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD_MASK;
    }
    if (NULL != phyConfig)
    {
        /* Decode to trim the nominal 17.78mA current source for the High Speed TX drivers on USB_DP and USB_DM. */
        usbPhyBase->TX =
            ((usbPhyBase->TX & (~(USBPHY_TX_D_CAL_MASK | USBPHY_TX_TXCAL45DM_MASK | USBPHY_TX_TXCAL45DP_MASK))) |
             (USBPHY_TX_D_CAL(phyConfig->D_CAL) | USBPHY_TX_TXCAL45DP(phyConfig->TXCAL45DP) |
              USBPHY_TX_TXCAL45DM(phyConfig->TXCAL45DM)));
    }
#endif

    return (uint8_t)kStatus_USB_Success;
}

/*!
 * @brief ehci phy initialization for suspend and resume.
 *
 * This function initialize ehci phy IP for suspend and resume.
 *
 * @param[in] controllerId   ehci controller id, please reference to #usb_controller_index_t.
 * @param[in] freq            the external input clock.
 *                            for example: if the external input clock is 16M, the parameter freq should be 16000000.
 *
 * @retval kStatus_USB_Success      cancel successfully.
 * @retval kStatus_USB_Error        the freq value is incorrect.
 */
uint32_t USB_EhciLowPowerPhyInit(uint8_t controllerId, uint32_t freq, usb_phy_config_struct_t *phyConfig)
{
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
    USBPHY_Type *usbPhyBase;

    usbPhyBase = (USBPHY_Type *)USB_EhciPhyGetBase(controllerId);
    if (NULL == usbPhyBase)
    {
        return (uint8_t)kStatus_USB_Error;
    }

#if ((!(defined FSL_FEATURE_SOC_CCM_ANALOG_COUNT)) && (!(defined FSL_FEATURE_SOC_ANATOP_COUNT)))
    usbPhyBase->TRIM_OVERRIDE_EN = 0x001fU; /* override IFR value */
#endif

#if ((defined USBPHY_CTRL_AUTORESUME_EN_MASK) && (USBPHY_CTRL_AUTORESUME_EN_MASK > 0U))
    usbPhyBase->CTRL_CLR |= USBPHY_CTRL_AUTORESUME_EN_MASK;
#else
    usbPhyBase->CTRL |= USBPHY_CTRL_ENAUTO_PWRON_PLL_MASK;
#endif
    usbPhyBase->CTRL |= USBPHY_CTRL_ENAUTOCLR_CLKGATE_MASK | USBPHY_CTRL_ENAUTOCLR_PHY_PWD_MASK;
    usbPhyBase->CTRL |= USBPHY_CTRL_SET_ENUTMILEVEL2_MASK; /* support LS device. */
    usbPhyBase->CTRL |= USBPHY_CTRL_SET_ENUTMILEVEL3_MASK; /* support external FS Hub with LS device connected. */
    /* PWD register provides overall control of the PHY power state */
    usbPhyBase->PWD = 0U;
#if (defined USBPHY_ANACTRL_PFD_CLKGATE_MASK)
    /* now the 480MHz USB clock is up, then configure fractional divider after PLL with PFD
     * pfd clock = 480MHz*18/N, where N=18~35
     * Please note that USB1PFDCLK has to be less than 180MHz for RUN or HSRUN mode
     */
    usbPhyBase->ANACTRL |= USBPHY_ANACTRL_PFD_FRAC(24);   /* N=24 */
    usbPhyBase->ANACTRL |= USBPHY_ANACTRL_PFD_CLK_SEL(1); /* div by 4 */

    usbPhyBase->ANACTRL &= ~USBPHY_ANACTRL_DEV_PULLDOWN_MASK;
    usbPhyBase->ANACTRL &= ~USBPHY_ANACTRL_PFD_CLKGATE_MASK;
    while (0U == (usbPhyBase->ANACTRL & USBPHY_ANACTRL_PFD_STABLE_MASK))
    {
    }
#endif
    if (NULL != phyConfig)
    {
        /* Decode to trim the nominal 17.78mA current source for the High Speed TX drivers on USB_DP and USB_DM. */
        usbPhyBase->TX =
            ((usbPhyBase->TX & (~(USBPHY_TX_D_CAL_MASK | USBPHY_TX_TXCAL45DM_MASK | USBPHY_TX_TXCAL45DP_MASK))) |
             (USBPHY_TX_D_CAL(phyConfig->D_CAL) | USBPHY_TX_TXCAL45DP(phyConfig->TXCAL45DP) |
              USBPHY_TX_TXCAL45DM(phyConfig->TXCAL45DM)));
    }
#endif

    return (uint8_t)kStatus_USB_Success;
}

/*!
 * @brief ehci phy de-initialization.
 *
 * This function de-initialize ehci phy IP.
 *
 * @param[in] controllerId   ehci controller id, please reference to #usb_controller_index_t.
 */
void USB_EhciPhyDeinit(uint8_t controllerId)
{
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
    USBPHY_Type *usbPhyBase;

    usbPhyBase = (USBPHY_Type *)USB_EhciPhyGetBase(controllerId);
    if (NULL == usbPhyBase)
    {
        return;
    }
#if ((!(defined FSL_FEATURE_SOC_CCM_ANALOG_COUNT)) && (!(defined FSL_FEATURE_SOC_ANATOP_COUNT)))
    usbPhyBase->PLL_SIC &= ~USBPHY_PLL_SIC_PLL_POWER_MASK;       /* power down PLL */
    usbPhyBase->PLL_SIC &= ~USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK; /* disable USB clock output from USB PHY PLL */
#endif
    usbPhyBase->CTRL |= USBPHY_CTRL_CLKGATE_MASK; /* set to 1U to gate clocks */
#endif
}

/*!
 * @brief ehci phy disconnect detection enable or disable.
 *
 * This function enable/disable host ehci disconnect detection.
 *
 * @param[in] controllerId   ehci controller id, please reference to #usb_controller_index_t.
 * @param[in] enable
 *            1U - enable;
 *            0U - disable;
 */
void USB_EhcihostPhyDisconnectDetectCmd(uint8_t controllerId, uint8_t enable)
{
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
    USBPHY_Type *usbPhyBase;

    usbPhyBase = (USBPHY_Type *)USB_EhciPhyGetBase(controllerId);
    if (NULL == usbPhyBase)
    {
        return;
    }

    if (0U != enable)
    {
        usbPhyBase->CTRL |= USBPHY_CTRL_ENHOSTDISCONDETECT_MASK;
    }
    else
    {
        usbPhyBase->CTRL &= (~USBPHY_CTRL_ENHOSTDISCONDETECT_MASK);
    }
#endif
}

#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
#if ((defined FSL_FEATURE_USBHSD_HAS_EXIT_HS_ISSUE) && (FSL_FEATURE_USBHSD_HAS_EXIT_HS_ISSUE > 0U))
void USB_PhyDeviceForceEnterFSMode(uint8_t controllerId, uint8_t enable)
{
    USBPHY_Type *usbPhyBase;

    usbPhyBase = (USBPHY_Type *)USB_EhciPhyGetBase(controllerId);
    if (NULL == usbPhyBase)
    {
        return;
    }

    if (0U != enable)
    {
        uint32_t delay         = 1000000;
        usbPhyBase->DEBUG0_CLR = USBPHY_DEBUG0_CLKGATE_MASK;
        while ((0U != (usbPhyBase->USB1_VBUS_DET_STAT & USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_3V_MASK)) && (0U != delay))
        {
            delay--;
        }
        usbPhyBase->USB1_LOOPBACK_SET = USBPHY_USB1_LOOPBACK_UTMI_TESTSTART_MASK;
    }
    else
    {
        usbPhyBase->DEBUG0_CLR        = USBPHY_DEBUG0_CLKGATE_MASK;
        usbPhyBase->USB1_LOOPBACK_CLR = USBPHY_USB1_LOOPBACK_UTMI_TESTSTART_MASK;
    }
}
#endif
#endif
