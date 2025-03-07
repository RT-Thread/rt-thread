/*
 * Copyright (c) 2022, Artinchip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <aic_core.h>
#include <aic_hal.h>
#include <hal_syscfg.h>
#include "usbd_core.h"
#include "usb_dc_aic_reg.h"

extern irqreturn_t USBD_IRQHandler(int irq, void * data);

uint32_t usbd_clk;

void usb_dc_low_level_init(void)
{
    /* set usb0 phy switch: Host/Device */
#ifdef AIC_USING_USB0_DEVICE
    syscfg_usb_phy0_sw_host(0);
#endif
    /* set pin-mux */

    /* enable clock */
    hal_clk_enable(CONFIG_USB_AIC_DC_PHY_CLK);
    hal_clk_enable(CONFIG_USB_AIC_DC_CLK);
    aicos_udelay(300);
    hal_reset_assert(CONFIG_USB_AIC_DC_PHY_RESET);
    hal_reset_assert(CONFIG_USB_AIC_DC_RESET);
    aicos_udelay(300);
    hal_reset_deassert(CONFIG_USB_AIC_DC_PHY_RESET);
    hal_reset_deassert(CONFIG_USB_AIC_DC_RESET);
    aicos_udelay(300);

    usbd_clk = hal_clk_get_freq(CONFIG_USB_AIC_DC_CLK);

    /* register interrupt callback */
    aicos_request_irq(CONFIG_USB_AIC_DC_IRQ_NUM, USBD_IRQHandler,
                      0, "usb_device", NULL);
    aicos_irq_enable(CONFIG_USB_AIC_DC_IRQ_NUM);
}

