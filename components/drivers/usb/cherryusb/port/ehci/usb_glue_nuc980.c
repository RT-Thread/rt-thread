/**************************************************************************/ /**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2023-8-8        Wayne            First version
*
******************************************************************************/
#include "rtthread.h"

#include "NuMicro.h"
#include "rthw.h"
#include "drv_sys.h"

#define LOG_TAG "drv.cherry"
#define DBG_ENABLE
#define DBG_SECTION_NAME LOG_TAG
#define DBG_LEVEL        DBG_LOG
#define DBG_COLOR
#include <rtdbg.h>

#if defined(PKG_CHERRYUSB_HOST)
#include "usbh_core.h"

static void nu_ehci_isr(int vector, void *param)
{
    extern void USBH_IRQHandler(uint8_t busid);
    USBH_IRQHandler(0);
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    LOG_D("%s %d", __FUNCTION__, __LINE__);

    rt_hw_interrupt_mask(IRQ_EHCI);

    /* Enable USBH clock */
    nu_sys_ipclk_enable(USBHCKEN);
    nu_sys_ip_reset(USBHRST);

    outpw(0xB0015000 + 0xC4, 0x160); //HSUSBH->USBPCR0 = 0x160;   /* enable PHY 0          */
    outpw(0xB0015000 + 0xC8, 0x520); //HSUSBH->USBPCR1 = 0x520;   /* enable PHY 1          */

    //USBH->HcMiscControl |= USBH_HcMiscControl_OCAL_Msk; /* Over-current active low  */
    //outpw(0xB0017000 + 0x204, inpw(0xB0017000 + 0x204) | (0x1ul << 3));

    //USBH->HcMiscControl &= ~USBH_HcMiscControl_OCAL_Msk; /* Over-current active high  */
    outpw(0xB0017000 + 0x204, inpw(0xB0017000 + 0x204) & (~(0x1ul << 3)));

    rt_hw_interrupt_install(IRQ_EHCI, nu_ehci_isr, NULL, "ehci-1");
    rt_hw_interrupt_set_priority(IRQ_EHCI, IRQ_LEVEL_1);
    rt_hw_interrupt_umask(IRQ_EHCI);
}

uint8_t usbh_get_port_speed(struct usbh_bus *bus, const uint8_t port)
{
    return USB_SPEED_HIGH;
}
#endif