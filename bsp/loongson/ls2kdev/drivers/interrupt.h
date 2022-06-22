/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-21     bigmagic     Initial version
 */

#ifndef _DRV_INTERRUPT_H__
#define _DRV_INTERRUPT_H__

#define LS2K_UART_0_1_2_3_IRQ       (0)
#define LS2K_UART_4_5_6_7_IRQ       (1)
#define LS2K_UART_8_9_10_11_IRQ     (2)
#define LS2K_EL_IRQ                 (3)
#define LS2K_HDA_IRQ                (4)
#define LS2K_I2S_IRQ                (5)
#define LS2K_RESERVED1_IRQ          (6)
#define LS2K_THSENS_IRQ             (7)
#define LS2K_TOY_TICK_IRQ           (8)
#define LS2K_RTC_TICK_IRQ           (9)
#define LS2K_CAM_TICK_IRQ           (10)
#define LS2K_RESERVED2_IRQ          (11)
#define LS2K_GMAC0_SBD_IRQ          (12)
#define LS2K_GMAC0_PMT_IRQ          (13)
#define LS2K_GMAC1_SBD_IRQ          (14)
#define LS2K_GMAC1_PMT_IRQ          (15)
#define LS2K_CANO_IRQ               (16)
#define LS2K_CAN1_IRQ               (17)
#define LS2K_BOOT_IRQ               (18)
#define LS2K_SATA_IRQ               (19)
#define LS2K_NAND_IRQ               (20)
#define LS2K_HPET_IRQ               (21)
#define LS2K_I2C0_IRQ               (21)
#define LS2K_I2C1_IRQ               (22)
#define LS2K_I2C2_IRQ               (23)
#define LS2K_PWM0_IRQ               (24)
#define LS2K_PWM1_IRQ               (25)
#define LS2K_PWM2_IRQ               (26)
#define LS2K_PWM3_IRQ               (27)
#define LS2K_DC_IRQ                 (28)
#define LS2K_GPU_IRQ                (29)
#define LS2K_VPU_IRQ                (30)
#define LS2K_SDIO_IRQ               (31)
//#define LS2K_PCIE0_IRQ              (32~35)
//#define LS2K_PCIE1_IRQ              (36~37)
#define LS2K_HPET1_IRQ              (38)
#define LS2K_HPET2_IRQ              (39)
//#define LS2K_TOY_IRQ                (40~43)
//#define LS2K_DMA_IRQ                (44~48)
#define LS2K_OTG_IRQ                (49)
#define LS2K_EHCI_IRQ               (50)
#define LS2K_OHCI_IRQ               (51)
//#define LS2K_RTC_IRQ                (52~54)
#define LS2K_RSA_IRQ                (55)
#define LS2K_AES_IRQ                (56)
#define LS2K_DES_IRQ                (57)
#define LS2K_GPIO_INTLO_IRQ         (58)
#define LS2K_GPIO_INTHI_IRQ         (59)
#define LS2K_GPIO0_INT_IRQ          (60)
#define LS2K_GPIO1_INT_IRQ          (61)
#define LS2K_GPIO2_INT_IRQ          (62)
#define LS2K_GPIO3_INT_IRQ          (63)

#define MAX_INTR                    (64)
#define LIOINTC0_IRQBASE            (0)
#define LIOINTC1_IRQBASE            (32)

#define LIOINTC_SHIFT_INTx          (4)
#define LIOINTC_COREx_INTy(x, y)    ((1 << x) | (1 << (y + LIOINTC_SHIFT_INTx)))

#define LIOINTC_INTC_CHIP_START      0x20

#define LIOINTC_REG_INTC_STATUS      (LIOINTC_INTC_CHIP_START + 0x00)
#define LIOINTC_REG_INTC_EN_STATUS   (LIOINTC_INTC_CHIP_START + 0x04)
#define LIOINTC_REG_INTC_ENABLE      (LIOINTC_INTC_CHIP_START + 0x08)
#define LIOINTC_REG_INTC_DISABLE     (LIOINTC_INTC_CHIP_START + 0x0c)
#define LIOINTC_REG_INTC_POL         (LIOINTC_INTC_CHIP_START + 0x10)
#define LIOINTC_REG_INTC_EDGE        (LIOINTC_INTC_CHIP_START + 0x14)

void liointc_set_irq_mode(int irq, int mode);

#endif
