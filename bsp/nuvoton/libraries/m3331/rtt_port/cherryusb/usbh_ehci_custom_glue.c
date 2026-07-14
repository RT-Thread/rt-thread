/* Includes ------------------------------------------------------------------*/
#include "rtthread.h"
#include "NuMicro.h"
#include "usb_config.h"
#include "usbh_core.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.usbh.ehci.custom.glue"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

/* Functions Implementation --------------------------------------------------*/
/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(PKG_CHERRYUSB_HOST) && defined(PKG_CHERRYUSB_HOST_EHCI_CUSTOM) && defined(BSP_USING_HSUSBH)

void HSUSBH_EHCI_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    void USBH_IRQHandler(uint8_t busid);
    USBH_IRQHandler(0);

    /* leave interrupt */
    rt_interrupt_leave();
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    if (bus->hcd.reg_base == HSUSBH_BASE)
    {
#if !defined(BSP_USING_HSOTG)
        /* Enable USBH clock */
        void nutool_modclkcfg_init_usbh(void);
        nutool_modclkcfg_init_usbh();

        /* Set USB Host role */
        SYS->USBPHY = (SYS->USBPHY & ~SYS_USBPHY_HSUSBROLE_Msk) | (0x1u << SYS_USBPHY_HSUSBROLE_Pos);
        SYS->USBPHY |= SYS_USBPHY_HSUSBEN_Msk | SYS_USBPHY_SBO_Msk;
        rt_thread_mdelay(1);
        SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;

        HSUSBH->USBPCR0 = 0x160;         /* EHCI: CLKSEL=10b, refclk=1b, SUSPEND=1b */
        //HSUSBH->USBPCR1 = 0x520;         /* OHCI: CLKSEL=10b, NEGTX=1b, SUSPEND=1b */
#endif
    }
}

void usb_hc_low_level2_init(struct usbh_bus *bus)
{
    if (bus->hcd.reg_base == HSUSBH_BASE)
    {
        HSUSBH->UPSCR[0] = HSUSBH_UPSCR_PP_Msk;      /* enable port 1 port power               */

        USBH->HcMiscControl |= USBH_HcMiscControl_OCAL_Msk; /* Over-current active low  */
        //USBH->HcMiscControl &= ~USBH_HcMiscControl_OCAL_Msk; /* Over-current active high  */

        /* Enable interrupt */
        NVIC_EnableIRQ(HSUSBH_EHCI_IRQn);
    }
}

uint8_t usbh_get_port_speed(struct usbh_bus *bus, const uint8_t port)
{
    return USB_SPEED_HIGH;
}

int rt_usbh_initialize(void)
{
    int bus_id = 0;

    usbh_initialize(bus_id, HSUSBH_BASE);

    return 0;
}
INIT_ENV_EXPORT(rt_usbh_initialize);
#endif
