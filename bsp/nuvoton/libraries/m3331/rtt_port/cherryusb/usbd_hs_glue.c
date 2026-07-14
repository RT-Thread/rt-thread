/* Includes ------------------------------------------------------------------*/
#include "rtthread.h"
#include "NuMicro.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.usbd.hs.glue"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

/* Functions Implementation --------------------------------------------------*/
/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(PKG_CHERRYUSB_DEVICE_HS) && defined(BSP_USING_HSUSBD)

void HSUSBD_IRQHandler(void)
{
    rt_interrupt_enter();

    void CherryUSB_USBD_IRQHandler(uint8_t busid);
    CherryUSB_USBD_IRQHandler(0);

    rt_interrupt_leave();
}

void usb_dc_low_level_init(void)
{
#if !defined(BSP_USING_HSOTG)
    void nutool_modclkcfg_init_hsusbd(void);
    nutool_modclkcfg_init_hsusbd();

    {
        /* Set PHY*/
        SYS->USBPHY  = (SYS->USBPHY & ~(SYS_USBPHY_HSUSBROLE_Msk));  // Select HSUSBD
        SYS->USBPHY &= ~SYS_USBPHY_HSUSBACT_Msk;
        SYS->USBPHY |= (SYS_USBPHY_HSUSBEN_Msk);
        rt_thread_delay(20);
        SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;
    }
#endif

    SYS_ResetModule(HSUSBD_RST);
}

void usb_dc_low_level_deinit(void)
{
#if !defined(BSP_USING_HSOTG)

    SYS->USBPHY &= ~(SYS_USBPHY_HSUSBACT_Msk | SYS_USBPHY_HSUSBEN_Msk);

    void nutool_modclkcfg_deinit_hsusbd(void);
    nutool_modclkcfg_deinit_hsusbd();

#endif
}
#endif
