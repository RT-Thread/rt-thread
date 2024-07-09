/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "bflb_core.h"
#include "usbh_core.h"
#include "hardware/usb_v2_reg.h"

#ifndef CONFIG_USB_EHCI_HCOR_RESERVED_DISABLE
#error "usb host must enable CONFIG_USB_EHCI_HCOR_RESERVED_DISABLE"
#endif

#define BLFB_USB_BASE ((uint32_t)0x20072000)
#define BFLB_PDS_BASE ((uint32_t)0x2000e000)

#define PDS_USB_CTL_OFFSET      (0x500) /* usb_ctl */
#define PDS_USB_PHY_CTRL_OFFSET (0x504) /* usb_phy_ctrl */

/* 0x500 : usb_ctl */
#define PDS_REG_USB_SW_RST_N   (1 << 0U)
#define PDS_REG_USB_EXT_SUSP_N (1 << 1U)
#define PDS_REG_USB_WAKEUP     (1 << 2U)
#define PDS_REG_USB_L1_WAKEUP  (1 << 3U)
#define PDS_REG_USB_DRVBUS_POL (1 << 4U)
#define PDS_REG_USB_IDDIG      (1 << 5U)

/* 0x504 : usb_phy_ctrl */
#define PDS_REG_USB_PHY_PONRST       (1 << 0U)
#define PDS_REG_USB_PHY_OSCOUTEN     (1 << 1U)
#define PDS_REG_USB_PHY_XTLSEL_SHIFT (2U)
#define PDS_REG_USB_PHY_XTLSEL_MASK  (0x3 << PDS_REG_USB_PHY_XTLSEL_SHIFT)
#define PDS_REG_USB_PHY_OUTCLKSEL    (1 << 4U)
#define PDS_REG_USB_PHY_PLLALIV      (1 << 5U)
#define PDS_REG_PU_USB20_PSW         (1 << 6U)

#define USB_SOF_TIMER_MASK_AFTER_RESET_HS (0x44C)
#define USB_SOF_TIMER_MASK_AFTER_RESET_FS (0x2710)

extern void USBH_IRQHandler(uint8_t busid);

void USBH_IRQ(int irq, void *arg) {
    USBH_IRQHandler(0);
}

static void bflb_usb_phy_init(void)
{
    uint32_t regval;

    /* USB_PHY_CTRL[3:2] reg_usb_phy_xtlsel=0                             */
    /* 2000e504 = 0x40; #100; USB_PHY_CTRL[6] reg_pu_usb20_psw=1 (VCC33A) */
    /* 2000e504 = 0x41; #500; USB_PHY_CTRL[0] reg_usb_phy_ponrst=1        */
    /* 2000e500 = 0x20; #100; USB_CTL[0] reg_usb_sw_rst_n=0               */
    /* 2000e500 = 0x22; #500; USB_CTL[1] reg_usb_ext_susp_n=1             */
    /* 2000e500 = 0x23; #100; USB_CTL[0] reg_usb_sw_rst_n=1               */
    /* #1.2ms; wait UCLK                                                  */
    /* wait(soc616_b0.usb_uclk);                                          */

    regval = getreg32(BFLB_PDS_BASE + PDS_USB_PHY_CTRL_OFFSET);
    regval &= ~PDS_REG_USB_PHY_XTLSEL_MASK;
    putreg32(regval, BFLB_PDS_BASE + PDS_USB_PHY_CTRL_OFFSET);

    regval = getreg32(BFLB_PDS_BASE + PDS_USB_PHY_CTRL_OFFSET);
    regval |= PDS_REG_PU_USB20_PSW;
    putreg32(regval, BFLB_PDS_BASE + PDS_USB_PHY_CTRL_OFFSET);

    regval = getreg32(BFLB_PDS_BASE + PDS_USB_PHY_CTRL_OFFSET);
    regval |= PDS_REG_USB_PHY_PONRST;
    putreg32(regval, BFLB_PDS_BASE + PDS_USB_PHY_CTRL_OFFSET);

    /* greater than 5T */
    bflb_mtimer_delay_us(1);

    regval = getreg32(BFLB_PDS_BASE + PDS_USB_CTL_OFFSET);
    regval &= ~PDS_REG_USB_SW_RST_N;
    putreg32(regval, BFLB_PDS_BASE + PDS_USB_CTL_OFFSET);

    /* greater than 5T */
    bflb_mtimer_delay_us(1);

    regval = getreg32(BFLB_PDS_BASE + PDS_USB_CTL_OFFSET);
    regval |= PDS_REG_USB_EXT_SUSP_N;
    putreg32(regval, BFLB_PDS_BASE + PDS_USB_CTL_OFFSET);

    /* wait UCLK 1.2ms */
    bflb_mtimer_delay_ms(3);

    regval = getreg32(BFLB_PDS_BASE + PDS_USB_CTL_OFFSET);
    regval |= PDS_REG_USB_SW_RST_N;
    putreg32(regval, BFLB_PDS_BASE + PDS_USB_CTL_OFFSET);

    bflb_mtimer_delay_ms(2);
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    uint32_t regval;

    bflb_usb_phy_init();

    bflb_irq_attach(37, USBH_IRQ, NULL);
    bflb_irq_enable(37);

    /* enable device-A for host */
    regval = getreg32(BFLB_PDS_BASE + PDS_USB_CTL_OFFSET);
    regval &= ~PDS_REG_USB_IDDIG;
    putreg32(regval, BFLB_PDS_BASE + PDS_USB_CTL_OFFSET);

    regval = getreg32(BLFB_USB_BASE + USB_OTG_CSR_OFFSET);
    regval |= USB_A_BUS_DROP_HOV;
    regval &= ~USB_A_BUS_REQ_HOV;
    putreg32(regval, BLFB_USB_BASE + USB_OTG_CSR_OFFSET);

    bflb_mtimer_delay_ms(10);

    /* enable vbus and bus control */
    regval = getreg32(BLFB_USB_BASE + USB_OTG_CSR_OFFSET);
    regval &= ~USB_A_BUS_DROP_HOV;
    regval |= USB_A_BUS_REQ_HOV;
    putreg32(regval, BLFB_USB_BASE + USB_OTG_CSR_OFFSET);

    regval = getreg32(BLFB_USB_BASE + USB_GLB_INT_OFFSET);
    regval |= USB_MDEV_INT;
    regval |= USB_MOTG_INT;
    regval &= ~USB_MHC_INT;
    putreg32(regval, BLFB_USB_BASE + USB_GLB_INT_OFFSET);
}

uint8_t usbh_get_port_speed(struct usbh_bus *bus, const uint8_t port)
{
    uint8_t speed = 3;

    speed = (getreg32(BLFB_USB_BASE + USB_OTG_CSR_OFFSET) & USB_SPD_TYP_HOV_POV_MASK) >> USB_SPD_TYP_HOV_POV_SHIFT;

    if (speed == 0) {
        return USB_SPEED_FULL;
    } else if (speed == 1) {
        return USB_SPEED_LOW;
    } else if (speed == 2) {
        return USB_SPEED_HIGH;
    }
    return USB_SPEED_HIGH;
}
