/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#include "rtdevice.h"
#include "NuMicro.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.usb.hs.otg"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

/* Functions Implementation --------------------------------------------------*/
/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(BSP_USING_HSOTG)

/* Check current usb role */
static void usb_role(void)
{
    uint32_t status = (HSOTG->STATUS) & (HSOTG_STATUS_ASHOST_Msk | HSOTG_STATUS_ASPERI_Msk | HSOTG_STATUS_IDSTS_Msk);

    if (status == (HSOTG_STATUS_IDSTS_Msk | HSOTG_STATUS_ASPERI_Msk))
    {
        LOG_I("usb frame acts as peripheral\n");
    }
    else if (status == HSOTG_STATUS_ASHOST_Msk)
    {
        LOG_I("usb frame acts as host\n");
    }
    else
    {
        LOG_I("usb frame is unknown state: 0x%x\n", status);
    }

    return;
}
MSH_CMD_EXPORT_ALIAS(usb_role, usb_role, check usb role);

static int hsotg_init(void)
{
    void nutool_modclkcfg_init_hsusbd(void);
    nutool_modclkcfg_init_hsusbd();

    void nutool_modclkcfg_init_usbh(void);
    nutool_modclkcfg_init_usbh();

    SYS->USBPHY = (SYS_USBPHY_HSUSBEN_Msk) |
                  (0x2ul << SYS_USBPHY_HSUSBROLE_Pos) |
                  (SYS_USBPHY_SBO_Msk);

    void rt_hw_us_delay(rt_uint32_t us);
    rt_hw_us_delay(40);

    /* user should keep HSUSB PHY at reset mode at lease 10 us before changing to active mode */
    SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;//Set HSUSB PHY Active.

    /* Enable OTG and ID detection function */
    HSOTG_ENABLE_PHY();
    HSOTG_ENABLE_ID_DETECT();
    NVIC_EnableIRQ(HSOTG_IRQn);

    /* clear interrupt and enable relative interrupts */
    HSOTG_ENABLE_INT(HSOTG_INTEN_IDCHGIEN_Msk | HSOTG_INTEN_HOSTIEN_Msk | HSOTG_INTEN_PDEVIEN_Msk |
                     HSOTG_INTEN_BVLDCHGIEN_Msk | HSOTG_INTEN_AVLDCHGIEN_Msk);

    return (int)RT_EOK;
}
INIT_PREV_EXPORT(hsotg_init);

/* HSOTG interrupt entry */
void HSOTG_IRQHandler(void)
{
    __IO uint32_t reg = HSOTG->INTSTS;

    /* usb id pin status change */
    if (reg & HSOTG_INTSTS_IDCHGIF_Msk)
    {
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_IDCHGIF_Msk);
        //LOG_D("usb id change");
    }
    if (reg & HSOTG_INTSTS_HOSTIF_Msk)
    {
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_HOSTIF_Msk);
        //LOG_D("usb acts as host");
    }
    if (reg & HSOTG_INTSTS_PDEVIF_Msk)
    {
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_PDEVIF_Msk);
        //LOG_D("usb acts as peripheral");
    }
    if (reg & HSOTG_INTSTS_AVLDCHGIF_Msk)
    {
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_AVLDCHGIF_Msk);
        //LOG_D("usb a-device session valid state change");
    }
    if (reg & HSOTG_INTSTS_BVLDCHGIF_Msk)
    {
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_BVLDCHGIF_Msk);
        //LOG_D("usb b-device session valid state change");
    }
}

#endif /* defined(BSP_USING_HSOTG) */
