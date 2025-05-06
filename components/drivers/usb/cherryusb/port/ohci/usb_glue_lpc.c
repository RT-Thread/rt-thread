/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "fsl_device_registers.h"
#include "fsl_power.h"
#include "usbh_core.h"

#if defined(CONFIG_USB_EHCI_WITH_OHCI)
#error "lpc does not have ehci"
#endif

void usb_hc_low_level_init(struct usbh_bus *bus)
{
#if ((defined FSL_FEATURE_SOC_SYSMPU_COUNT) && (FSL_FEATURE_SOC_SYSMPU_COUNT))
    SYSMPU_Enable(SYSMPU, 0);
#endif /* FSL_FEATURE_SOC_SYSMPU_COUNT */

    NVIC_ClearPendingIRQ(USB0_IRQn);
    NVIC_ClearPendingIRQ(USB0_NEEDCLK_IRQn);

    POWER_DisablePD(kPDRUNCFG_PD_USB0_PHY); /*< Turn on USB0 Phy */

    RESET_PeripheralReset(kUSB0D_RST_SHIFT_RSTn);
    RESET_PeripheralReset(kUSB0HSL_RST_SHIFT_RSTn);
    RESET_PeripheralReset(kUSB0HMR_RST_SHIFT_RSTn);

    CLOCK_EnableUsbfs0HostClock(kCLOCK_UsbfsSrcPll1, 48000000U);

    NVIC_SetPriority(USB0_IRQn, 3);
    EnableIRQ(USB0_IRQn);
}


void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    DisableIRQ(USB0_IRQn);
}

void USB0_IRQHandler(void)
{
    extern void USBH_IRQHandler(uint8_t busid);
    USBH_IRQHandler(0);
}