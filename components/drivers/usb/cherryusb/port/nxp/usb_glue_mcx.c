/*
 * Copyright (c) 2024 ~ 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbh_core.h"
#include "fsl_common.h"
#include "fsl_cache.h"
#include "usb_chipidea_reg.h"

__WEAK void USBD_IRQHandler(uint8_t busid)
{
}

__WEAK void USBH_IRQHandler(uint8_t busid)
{
}

#if !defined(CONFIG_USB_EHCI_NXP)
#error "mcx ehci must config CONFIG_USB_EHCI_NXP"
#endif

#if !defined(CONFIG_USB_EHCI_HCCR_OFFSET) || CONFIG_USB_EHCI_HCCR_OFFSET != 0x100
#error "mcx ehci must config CONFIG_USB_EHCI_HCCR_OFFSET to 0x100"
#endif

#define USB_DEVICE_CONFIG_EHCI 1

/*! @brief USB controller ID */
typedef enum _usb_controller_index {
    kUSB_ControllerKhci0 = 0U, /*!< KHCI 0U */
    kUSB_ControllerKhci1 = 1U, /*!< KHCI 1U, Currently, there are no platforms which have two KHCI IPs, this is reserved
                                  to be used in the future. */
    kUSB_ControllerEhci0 = 2U, /*!< EHCI 0U */
    kUSB_ControllerEhci1 = 3U, /*!< EHCI 1U, Currently, there are no platforms which have two EHCI IPs, this is reserved
                                  to be used in the future. */

    kUSB_ControllerLpcIp3511Fs0 = 4U, /*!< LPC USB IP3511 FS controller 0 */
    kUSB_ControllerLpcIp3511Fs1 = 5U, /*!< LPC USB IP3511 FS controller 1, there are no platforms which have two IP3511
                                        IPs, this is reserved to be used in the future. */

    kUSB_ControllerLpcIp3511Hs0 = 6U, /*!< LPC USB IP3511 HS controller 0 */
    kUSB_ControllerLpcIp3511Hs1 = 7U, /*!< LPC USB IP3511 HS controller 1, there are no platforms which have two IP3511
                                        IPs, this is reserved to be used in the future. */

    kUSB_ControllerOhci0 = 8U, /*!< OHCI 0U */
    kUSB_ControllerOhci1 = 9U, /*!< OHCI 1U, Currently, there are no platforms which have two OHCI IPs, this is reserved
                                  to be used in the future. */

    kUSB_ControllerIp3516Hs0 = 10U, /*!< IP3516HS 0U */
    kUSB_ControllerIp3516Hs1 = 11U, /*!< IP3516HS 1U, Currently, there are no platforms which have two IP3516HS IPs,
                                  this is reserved to be used in the future. */
    kUSB_ControllerDwc30 = 12U,     /*!< DWC3 0U */
    kUSB_ControllerDwc31 = 13U,     /*!< DWC3 1U Currently, there are no platforms which have two Dwc IPs, this is reserved
                              to be used in the future.*/
} usb_controller_index_t;

/* USB PHY condfiguration */
#define BOARD_USB_PHY_D_CAL     (0x04U)
#define BOARD_USB_PHY_TXCAL45DP (0x07U)
#define BOARD_USB_PHY_TXCAL45DM (0x07U)
#define BOARD_XTAL0_CLK_HZ      24000000U /*!< Board xtal0 frequency in Hz */

typedef struct _usb_phy_config_struct {
    uint8_t D_CAL;     /* Decode to trim the nominal 17.78mA current source */
    uint8_t TXCAL45DP; /* Decode to trim the nominal 45-Ohm series termination resistance to the USB_DP output pin */
    uint8_t TXCAL45DM; /* Decode to trim the nominal 45-Ohm series termination resistance to the USB_DM output pin */
} usb_phy_config_struct_t;

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
    if (controllerId < (uint8_t)kUSB_ControllerEhci0) {
        return NULL;
    }

    if ((controllerId == (uint8_t)kUSB_ControllerEhci0) || (controllerId == (uint8_t)kUSB_ControllerEhci1)) {
        controllerId = controllerId - (uint8_t)kUSB_ControllerEhci0;
    } else if ((controllerId == (uint8_t)kUSB_ControllerLpcIp3511Hs0) ||
               (controllerId == (uint8_t)kUSB_ControllerLpcIp3511Hs1)) {
        controllerId = controllerId - (uint8_t)kUSB_ControllerLpcIp3511Hs0;
    } else if ((controllerId == (uint8_t)kUSB_ControllerIp3516Hs0) || (controllerId == (uint8_t)kUSB_ControllerIp3516Hs1)) {
        controllerId = controllerId - (uint8_t)kUSB_ControllerIp3516Hs0;
    } else {
        return NULL;
    }

    if (controllerId < (sizeof(usbphy_base) / sizeof(usbphy_base[0]))) {
        temp = (uint32_t *)usbphy_base[controllerId];
        usbPhyBase = (void *)temp;
    } else {
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
 * @retval 0      cancel successfully.
 * @retval -1        the freq value is incorrect.
 */
uint32_t USB_EhciPhyInit(uint8_t controllerId, uint32_t freq, usb_phy_config_struct_t *phyConfig)
{
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
    USBPHY_Type *usbPhyBase;

    usbPhyBase = (USBPHY_Type *)USB_EhciPhyGetBase(controllerId);
    if (NULL == usbPhyBase) {
        return (uint8_t)-1;
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
        ((uint8_t)kUSB_ControllerLpcIp3511Hs1 == controllerId)) {
        usbPhyBase->CTRL_SET = USBPHY_CTRL_SET_ENAUTOCLR_CLKGATE_MASK;
        usbPhyBase->CTRL_SET = USBPHY_CTRL_SET_ENAUTOCLR_PHY_PWD_MASK;
    }
    if (NULL != phyConfig) {
        /* Decode to trim the nominal 17.78mA current source for the High Speed TX drivers on USB_DP and USB_DM. */
        usbPhyBase->TX =
            ((usbPhyBase->TX & (~(USBPHY_TX_D_CAL_MASK | USBPHY_TX_TXCAL45DM_MASK | USBPHY_TX_TXCAL45DP_MASK))) |
             (USBPHY_TX_D_CAL(phyConfig->D_CAL) | USBPHY_TX_TXCAL45DP(phyConfig->TXCAL45DP) |
              USBPHY_TX_TXCAL45DM(phyConfig->TXCAL45DM)));
    }
#endif

    return (uint8_t)0;
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
 * @retval 0      cancel successfully.
 * @retval -1        the freq value is incorrect.
 */
uint32_t USB_EhciLowPowerPhyInit(uint8_t controllerId, uint32_t freq, usb_phy_config_struct_t *phyConfig)
{
#if ((defined FSL_FEATURE_SOC_USBPHY_COUNT) && (FSL_FEATURE_SOC_USBPHY_COUNT > 0U))
    USBPHY_Type *usbPhyBase;

    usbPhyBase = (USBPHY_Type *)USB_EhciPhyGetBase(controllerId);
    if (NULL == usbPhyBase) {
        return (uint8_t)-1;
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
    while (0U == (usbPhyBase->ANACTRL & USBPHY_ANACTRL_PFD_STABLE_MASK)) {
    }
#endif
    if (NULL != phyConfig) {
        /* Decode to trim the nominal 17.78mA current source for the High Speed TX drivers on USB_DP and USB_DM. */
        usbPhyBase->TX =
            ((usbPhyBase->TX & (~(USBPHY_TX_D_CAL_MASK | USBPHY_TX_TXCAL45DM_MASK | USBPHY_TX_TXCAL45DP_MASK))) |
             (USBPHY_TX_D_CAL(phyConfig->D_CAL) | USBPHY_TX_TXCAL45DP(phyConfig->TXCAL45DP) |
              USBPHY_TX_TXCAL45DM(phyConfig->TXCAL45DM)));
    }
#endif

    return (uint8_t)0;
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
    if (NULL == usbPhyBase) {
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
    if (NULL == usbPhyBase) {
        return;
    }

    if (0U != enable) {
        usbPhyBase->CTRL |= USBPHY_CTRL_ENHOSTDISCONDETECT_MASK;
    } else {
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
    if (NULL == usbPhyBase) {
        return;
    }

    if (0U != enable) {
        uint32_t delay = 1000000;
        usbPhyBase->DEBUG0_CLR = USBPHY_DEBUG0_CLKGATE_MASK;
        while ((0U != (usbPhyBase->USB1_VBUS_DET_STAT & USBPHY_USB1_VBUS_DET_STAT_VBUS_VALID_3V_MASK)) && (0U != delay)) {
            delay--;
        }
        usbPhyBase->USB1_LOOPBACK_SET = USBPHY_USB1_LOOPBACK_UTMI_TESTSTART_MASK;
    } else {
        usbPhyBase->DEBUG0_CLR = USBPHY_DEBUG0_CLKGATE_MASK;
        usbPhyBase->USB1_LOOPBACK_CLR = USBPHY_USB1_LOOPBACK_UTMI_TESTSTART_MASK;
    }
}
#endif
#endif

void USB_ClockInit(void)
{
    usb_phy_config_struct_t phyConfig = {
        BOARD_USB_PHY_D_CAL,
        BOARD_USB_PHY_TXCAL45DP,
        BOARD_USB_PHY_TXCAL45DM,
    };

    SPC0->ACTIVE_VDELAY = 0x0500;
    /* Change the power DCDC to 1.8v (By deafult, DCDC is 1.8V), CORELDO to 1.1v (By deafult, CORELDO is 1.0V) */
    SPC0->ACTIVE_CFG &= ~SPC_ACTIVE_CFG_CORELDO_VDD_DS_MASK;
    SPC0->ACTIVE_CFG |= SPC_ACTIVE_CFG_DCDC_VDD_LVL(0x3) | SPC_ACTIVE_CFG_CORELDO_VDD_LVL(0x3) |
                        SPC_ACTIVE_CFG_SYSLDO_VDD_DS_MASK | SPC_ACTIVE_CFG_DCDC_VDD_DS(0x2u);
    /* Wait until it is done */
    while (SPC0->SC & SPC_SC_BUSY_MASK)
        ;
    if (0u == (SCG0->LDOCSR & SCG_LDOCSR_LDOEN_MASK)) {
        SCG0->TRIM_LOCK = 0x5a5a0001U;
        SCG0->LDOCSR |= SCG_LDOCSR_LDOEN_MASK;
        /* wait LDO ready */
        while (0U == (SCG0->LDOCSR & SCG_LDOCSR_VOUT_OK_MASK))
            ;
    }
    SYSCON->AHBCLKCTRLSET[2] |= SYSCON_AHBCLKCTRL2_USB_HS_MASK | SYSCON_AHBCLKCTRL2_USB_HS_PHY_MASK;
    SCG0->SOSCCFG &= ~(SCG_SOSCCFG_RANGE_MASK | SCG_SOSCCFG_EREFS_MASK);
    /* xtal = 20 ~ 30MHz */
    SCG0->SOSCCFG = (1U << SCG_SOSCCFG_RANGE_SHIFT) | (1U << SCG_SOSCCFG_EREFS_SHIFT);
    SCG0->SOSCCSR |= SCG_SOSCCSR_SOSCEN_MASK;
    while (1) {
        if (SCG0->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK) {
            break;
        }
    }
    SYSCON->CLOCK_CTRL |= SYSCON_CLOCK_CTRL_CLKIN_ENA_MASK | SYSCON_CLOCK_CTRL_CLKIN_ENA_FM_USBH_LPT_MASK;
    CLOCK_EnableClock(kCLOCK_UsbHs);
    CLOCK_EnableClock(kCLOCK_UsbHsPhy);
    CLOCK_EnableUsbhsPhyPllClock(kCLOCK_Usbphy480M, 24000000U);
    CLOCK_EnableUsbhsClock();
    USB_EhciPhyInit(kUSB_ControllerEhci0, BOARD_XTAL0_CLK_HZ, &phyConfig);
}

void (*g_usb_nxp_irq)(uint8_t busid);

void usb_dc_low_level_init(uint8_t busid)
{
    USB_ClockInit();

    g_usb_nxp_irq = USBD_IRQHandler;

    /* Install isr, set priority, and enable IRQ. */
    NVIC_SetPriority((IRQn_Type)USB1_HS_IRQn, 3);
    EnableIRQ((IRQn_Type)USB1_HS_IRQn);
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    DisableIRQ((IRQn_Type)USB1_HS_IRQn);
}

static void usb_host_mode_init(CHIPIDEA_TypeDef *ptr)
{
    /* Set mode to host, must be set immediately after reset */
    ptr->USBMODE &= ~USB_USBMODE_CM_MASK;
    ptr->USBMODE |= USB_USBMODE_CM_SET(3);

    /* Set the endian */
    ptr->USBMODE &= ~USB_USBMODE_ES_MASK;

    /* Set parallel interface signal */
    ptr->PORTSC1 &= ~USB_PORTSC1_STS_MASK;

    /* Set parallel transceiver width */
    ptr->PORTSC1 &= ~USB_PORTSC1_PTW_MASK;

    /* Not use interrupt threshold. */
    ptr->USBCMD &= ~USB_USBCMD_ITC_MASK;
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    USB_ClockInit();

    g_usb_nxp_irq = USBH_IRQHandler;

    /* Install isr, set priority, and enable IRQ. */
    NVIC_SetPriority((IRQn_Type)USB1_HS_IRQn, 3);
    EnableIRQ((IRQn_Type)USB1_HS_IRQn);
}

void usb_hc_low_level2_init(struct usbh_bus *bus)
{
    usb_host_mode_init((CHIPIDEA_TypeDef *)(bus->hcd.reg_base));
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    DisableIRQ((IRQn_Type)USB1_HS_IRQn);
}

uint8_t usbh_get_port_speed(struct usbh_bus *bus, const uint8_t port)
{
    (void)port;
    uint8_t speed;

    CHIPIDEA_TypeDef *ptr = (CHIPIDEA_TypeDef *)bus->hcd.reg_base;

    speed = USB_PORTSC1_PSPD_GET(ptr->PORTSC1);

    if (speed == 0x00) {
        return USB_SPEED_FULL;
    }
    if (speed == 0x01) {
        return USB_SPEED_LOW;
    }
    if (speed == 0x02) {
        USB_EhcihostPhyDisconnectDetectCmd(kUSB_ControllerEhci0, 1);
        return USB_SPEED_HIGH;
    }

    return 0;
}

void USB1_HS_IRQHandler(void)
{
    g_usb_nxp_irq(0);
}

#ifdef CONFIG_USB_DCACHE_ENABLE
void usb_dcache_clean(uintptr_t addr, size_t size)
{
    DCACHE_CleanByRange(addr, size);
}

void usb_dcache_invalidate(uintptr_t addr, size_t size)
{
    DCACHE_InvalidateByRange(addr, size);
}

void usb_dcache_flush(uintptr_t addr, size_t size)
{
    DCACHE_CleanInvalidateByRange(addr, size);
}
#endif