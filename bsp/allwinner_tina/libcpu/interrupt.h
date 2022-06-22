/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 * 2020-03-2      Howard Su    Define same regsiters as an array
 */
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

/* Max number of interruptions */
#define INTERRUPTS_MAX       (64)
/* a group num */
#define GROUP_NUM            (32)
/* Interrupt Source */
#define NMI_INTERRUPT              (0)
#define UART0_INTERRUPT            (1)
#define UART1_INTERRUPT            (2)
#define UART2_INTERRUPT            (3)
#define OWA_INTERRUPT              (5)
#define CIR_INTERRUPT              (6)
#define TWI0_INTERRUPT             (7)
#define TWI1_INTERRUPT             (8)
#define TWI2_INTERRUPT             (9)
#define SPI0_INTERRUPT             (10)
#define SPI1_INTERRUPT             (11)
#define TIMER0_INTERRUPT           (13)
#define TIMER1_INTERRUPT           (14)
#define TIMER2_INTERRUPT           (15)
#define WATCHDOG_INTERRUPT         (16)
#define RSB_INTERRUPT              (17)
#define DMA_INTERRUPT              (18)
#define TOUCHPANEL_INTERRUPT       (20)
#define AUDIOCODEC_INTERRUPT       (21)
#define KEYADC_INTERRUPT           (22)
#define SDC0_INTERRUPT             (23)
#define SDC1_INTERRUPT             (24)
#define USB_OTG_INTERRUPT          (26)
#define TVD_INTERRUPT              (27)
#define TVE_INTERRUPT              (28)
#define TCON_INTERRUPT             (29)
#define DE_FE_INTERRUPT            (30)
#define DE_BE_INTERRUPT            (31)
#define CSI_INTERRUPT              (32)
#define DE_INTERLACER_INTERRUPT    (33)
#define VE_INTERRUPT               (34)
#define DAUDIO_INTERRUPT           (35)
#define PIOD_INTERRUPT             (38)
#define PIOE_INTERRUPT             (39)
#define PIOF_INTERRUPT             (40)

/* intc  register address */
#define INTC_BASE_ADDR     (0x01C20400)

struct tina_intc
{
    volatile rt_uint32_t vector_reg;       /* 0x00 */
    volatile rt_uint32_t base_addr_reg;    /* 0x04 */
    volatile rt_uint32_t reserved0;
    volatile rt_uint32_t nmi_ctrl_reg;     /* 0x0C */
    volatile rt_uint32_t pend_reg[2];        /* 0x10, 0x14 */
    volatile rt_uint32_t reserved1[2];
    volatile rt_uint32_t en_reg[2];          /* 0x20, 0x24 */
    volatile rt_uint32_t reserved2[2];
    volatile rt_uint32_t mask_reg[2];        /* 0x30, 0x34 */
    volatile rt_uint32_t reserved3[2];
    volatile rt_uint32_t resp_reg[2];        /* 0x40, 0x44 */
    volatile rt_uint32_t reserved4[2];
    volatile rt_uint32_t ff_reg[2];          /* 0x50, 0x54 */
    volatile rt_uint32_t reserved5[2];
    volatile rt_uint32_t prio_reg[4];        /* 0x60 - 0x6c */
} ;

typedef struct tina_intc *tina_intc_t;

#define INTC ((tina_intc_t)INTC_BASE_ADDR)

#endif /* __INTERRUPT_H__ */
