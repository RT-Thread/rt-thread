/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024/03/02     ShichengChu    first version
 */
#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include "pinctrl.h"
#include "mmio.h"

struct cvi_wdt_regs_t {
    uint32_t CR;
    uint32_t TORR;
    uint32_t CCVR;
    uint32_t CRR;
    uint32_t STAT;
    uint32_t EOI;
};

static struct cvi_wdt_regs_t cv182x_wdt_reg = {
    .CR = 0x0,
    .TORR = 0x4,
    .CCVR = 0x8,
    .CRR = 0xc,
    .STAT = 0x10,
    .EOI = 0x14,
};

static struct cvi_wdt_regs_t *cvi_wdt_reg = &cv182x_wdt_reg;

#define CVI_WDT0_BASE                0x03010000
#define CVI_WDT1_BASE                0x03011000
#define CVI_WDT2_BASE                0x03012000

#define WDT_CR(reg_base)        *((volatile uint32_t *)(reg_base + cvi_wdt_reg->CR))
#define WDT_TORR(reg_base)      *((volatile uint32_t *)(reg_base + cvi_wdt_reg->TORR))
#define WDT_CCVR(reg_base)      *((volatile const uint32_t *)(reg_base + cvi_wdt_reg->CCVR))
#define WDT_CRR(reg_base)       *((volatile uint32_t *)(reg_base + cvi_wdt_reg->CRR))
#define WDT_STAT(reg_base)      *((volatile const uint32_t *)(reg_base + cvi_wdt_reg->STAT))
#define WDT_EOI(reg_base)       *((volatile const uint32_t *)(reg_base + cvi_wdt_reg->EOI))

#define CVI_WDT_TORR_WDT_TORR_Pos                   (0U)
#define CVI_WDT_TORR_WDT_TORR_Msk                   (0xf << CVI_WDT_TORR_WDT_TORR_Pos)
#define CVI_WDT_TORR_WDT_ITORR_Pos                  (4U)
#define CVI_WDT_TORR_WDT_ITORR_Msk                  (0xf << CVI_WDT_TORR_WDT_ITORR_Pos)

#define CVI_WDT_CR_WDT_ENABLE_Pos                   (0U)
#define CVI_WDT_CR_WDT_ENABLE_Msk                   (1U << CVI_WDT_CR_WDT_ENABLE_Pos)
#define CVI_WDT_CR_WDT_ENABLE_En                    CVI_WDT_CR_WDT_ENABLE_Msk

#define CVI_WDT_CR_WDT_RESPOND_Pos                   (1U)
#define CVI_WDT_CR_WDT_RESPOND_Msk                   (1U << CVI_WDT_CR_WDT_RESPOND_Pos)
#define CVI_WDT_CR_WDT_RESPOND_IRQ_THEN_RST          CVI_WDT_CR_WDT_RESPOND_Msk

#define CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Pos           (2U)
#define CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Msk           (7U << CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Pos)
#define CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_2_PCLK        (0U << CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Pos)
#define CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_4_PCLK        (1U << CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Pos)
#define CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_8_PCLK        (2U << CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Pos)
#define CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_16_PCLK       (3U << CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Pos)
#define CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_32_PCLK       (4U << CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Pos)
#define CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_64_PCLK       (5U << CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Pos)
#define CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_128_PCLK      (6U << CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Pos)
#define CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_256_PCLK      CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Msk

#define CVI_WDT_CRR_FEED_Value                       0x76
#define CVI_WDT_CRR_FEED_Pos                         (0U)
#define CVI_WDT_CRR_FEED_Msk                         (0xff << CVI_WDT_CRR_FEED_Pos)
#define CVI_WDT_CRR_FEED_En                          CVI_WDT_CRR_FEED_Value

#define CVI_WDT_CCVR_COUNTER_Pos                     (0U)
#define CVI_WDT_CCVR_COUNTER_Msk                     (0xffffffff << CVI_WDT_CCVR_COUNTER_Pos)

#define CVI_WDT_STAT_IRQ_STAT_Pos                    (0U)
#define CVI_WDT_STAT_IRQ_STAT_Msk                    (1U << CVI_WDT_STAT_IRQ_STAT_Pos)

#define CVI_WDT_STAT_IRQ_CLR_Pos                     (0U)
#define CVI_WDT_STAT_IRQ_CLR_Msk                     (1U << CVI_WDT_STAT_IRQ_STAT_Pos)
#define CVI_WDT_STAT_IRQ_CLR_En                      CVI_WDT_STAT_IRQ_CLR_Msk

#define CV_TOP      0x03000000
#define CV_TOP_WDT_OFFSET   0x8
#define CV_TOP_WDT_VAL  0x100
#define CV_RST_REG      (CV_TOP + 0x3004)
#define CV_RST_WDT      (1U << 16)

rt_inline void cvi_wdt_top_setting()
{
    uint32_t val;

    mmio_write_32(CV_TOP + CV_TOP_WDT_OFFSET, CV_TOP_WDT_VAL);

    val = mmio_read_32(CV_RST_REG);
    mmio_write_32(CV_RST_REG, val & ~CV_RST_WDT);
    rt_hw_us_delay(10);
    mmio_write_32(CV_RST_REG, val | CV_RST_WDT);
}

rt_inline void cvi_wdt_start_en(unsigned long reg_base)
{
    WDT_CR(reg_base) |= CVI_WDT_CR_WDT_ENABLE_En;
}

rt_inline void cvi_wdt_start_dis(unsigned long reg_base)
{
    WDT_CR(reg_base) &= ~CVI_WDT_CR_WDT_ENABLE_En;
}

rt_inline uint32_t cvi_wdt_get_start(unsigned long reg_base)
{
    return (WDT_CR(reg_base) & CVI_WDT_CR_WDT_ENABLE_Msk);
}

rt_inline void cvi_wdt_set_timeout(unsigned long reg_base, uint32_t value)
{
    WDT_TORR(reg_base) &= ~CVI_WDT_TORR_WDT_TORR_Pos;
    WDT_TORR(reg_base) = ((value << CVI_WDT_TORR_WDT_ITORR_Pos) | (value << CVI_WDT_TORR_WDT_TORR_Pos));
}

rt_inline void cvi_wdt_set_respond_system_reset(unsigned long reg_base)
{
    WDT_CR(reg_base) &= ~CVI_WDT_CR_WDT_RESPOND_IRQ_THEN_RST;
}

rt_inline void cvi_wdt_set_respond_irq_then_reset(unsigned long reg_base)
{
    WDT_CR(reg_base) |= CVI_WDT_CR_WDT_RESPOND_IRQ_THEN_RST;
}

rt_inline void cvi_wdt_set_reset_pulse_width(unsigned long reg_base, uint32_t value)
{
    WDT_CR(reg_base) &= ~CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Msk;
    WDT_CR(reg_base) |= (value << CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Pos);
}

rt_inline void cvi_wdt_feed_en(unsigned long reg_base)
{
    WDT_CRR(reg_base) = CVI_WDT_CRR_FEED_En;
}

rt_inline uint32_t cvi_wdt_get_counter_value(unsigned long reg_base)
{
    return (WDT_CCVR(reg_base) & CVI_WDT_CCVR_COUNTER_Msk);
}

rt_inline uint32_t cvi_wdt_get_irq_stat(unsigned long reg_base)
{
    return (WDT_STAT(reg_base) & CVI_WDT_STAT_IRQ_STAT_Msk);
}

rt_inline void cvi_wdt_clr_irq_en(unsigned long reg_base)
{
    WDT_EOI(reg_base);
}


int rt_hw_wdt_init(void);

#endif /* __DRV_ADC_H__ */
