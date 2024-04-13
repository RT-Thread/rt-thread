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

static void nu_echi_isr(int vector, void *param)
{
    uint8_t busid = (uint8_t)param;
    extern void USBH_IRQHandler(uint8_t busid);
    USBH_IRQHandler(busid);
}

static void nu_ochi_isr(int vector, void *param)
{
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    int timeout = 100;

    if (bus->hcd.reg_base == HSUSBH0_BASE) {
        /* Enable USBH clock */
        CLK_EnableModuleClock(HUSBH0_MODULE);
        SYS_ResetModule(HSUSBH0_RST);

        /* Clock engine clock Configuration */
        SYS->USBPMISCR &= ~(SYS_USBPMISCR_PHY0POR_Msk | SYS_USBPMISCR_PHY0COMN_Msk);
        rt_thread_mdelay(20);
        SYS->USBPMISCR |= SYS_USBPMISCR_PHY0SUSPEND_Msk | SYS_USBPMISCR_PHY0COMN_Msk;

        /* set UHOVRCURH(SYS_MISCFCR0[12]) 1 => USBH Host over-current detect is high-active */
        /*                                 0 => USBH Host over-current detect is low-active  */
        //SYS->MISCFCR0 |= SYS_MISCFCR0_UHOVRCURH_Msk;
        SYS->MISCFCR0 &= ~SYS_MISCFCR0_UHOVRCURH_Msk;
        while (1) {
            rt_thread_mdelay(1);
            if ((SYS->USBPMISCR & SYS_USBPMISCR_PHY0HSTCKSTB_Msk) &&)
                break; /* both USB PHY0 and PHY1 clock 60MHz UTMI clock stable */

            timeout--;
            if (timeout == 0) {
                rt_kprintf("USB PHY reset failed. USBPMISCR = 0x%08x\n", SYS->USBPMISCR);
                return;
            }
        }

        /* Register interrupt service routine. */
        rt_hw_interrupt_install(HSUSBH0_IRQn, nu_echi_isr, (void *)bus->hcd.hcd_id, "ehci0");

        /* Enable interrupt */
        rt_hw_interrupt_umask(HSUSBH0_IRQn);
    } else if (bus->hcd.reg_base == HSUSBH1_BASE) {
        /* Enable USBH clock */
        CLK_EnableModuleClock(HUSBH1_MODULE);
        SYS_ResetModule(HSUSBH1_RST);

        /* Clock engine clock Configuration */
        SYS->USBPMISCR &= ~(SYS_USBPMISCR_PHY1POR_Msk | SYS_USBPMISCR_PHY1COMN_Msk);
        rt_thread_mdelay(20);
        SYS->USBPMISCR |= SYS_USBPMISCR_PHY1SUSPEND_Msk | SYS_USBPMISCR_PHY1COMN_Msk;

        /* set UHOVRCURH(SYS_MISCFCR0[12]) 1 => USBH Host over-current detect is high-active */
        /*                                 0 => USBH Host over-current detect is low-active  */
        //SYS->MISCFCR0 |= SYS_MISCFCR0_UHOVRCURH_Msk;
        SYS->MISCFCR0 &= ~SYS_MISCFCR0_UHOVRCURH_Msk;
        while (1) {
            rt_thread_mdelay(1);
            if ((SYS->USBPMISCR & SYS_USBPMISCR_PHY1HSTCKSTB_Msk))
                break; /* both USB PHY0 and PHY1 clock 60MHz UTMI clock stable */

            timeout--;
            if (timeout == 0) {
                rt_kprintf("USB PHY reset failed. USBPMISCR = 0x%08x\n", SYS->USBPMISCR);
                return;
            }
        }
        /* Register interrupt service routine. */
        rt_hw_interrupt_install(HSUSBH1_IRQn, nu_echi_isr, (void *)bus->hcd.hcd_id, "ehci1");

        /* Enable interrupt */
        rt_hw_interrupt_umask(HSUSBH1_IRQn);
    }
}

void usb_hc_low_level2_init(struct usbh_bus *bus)
{
}

uint8_t usbh_get_port_speed(struct usbh_bus *bus, const uint8_t port)
{
    return USB_SPEED_HIGH;
}

#endif
