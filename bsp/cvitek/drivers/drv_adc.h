/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/02/22     flyingcys    first version
 */
#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include "pinctrl.h"
#include "mmio.h"

#define SARADC_BASE                         0x030F0000
#define SARADC_CH_MAX                       3

#define SARADC_CTRL_OFFSET                  0x04
#define SARADC_CTRL_START                   (1 << 0)
#define SARADC_CTRL_SEL_POS                 0x04

#define SARADC_STATUS_OFFSET                0x08
#define SARADC_STATUS_BUSY                  (1 << 0)

#define SARADC_CYC_SET_OFFSET               0x0C
#define SARADC_CYC_CLKDIV_DIV_POS           (12U)
#define SARADC_CYC_CLKDIV_DIV_MASK          (0xF << SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_1             (0U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_2             (1U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_3             (2U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_4             (3U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_5             (4U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_6             (5U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_7             (6U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_8             (7U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_9             (8U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_10            (9U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_11            (10U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_12            (11U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_13            (12U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_14            (13U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_15            (14U<< SARADC_CYC_CLKDIV_DIV_POS)
#define SARADC_CYC_CLKDIV_DIV_16            (15U<< SARADC_CYC_CLKDIV_DIV_POS)

#define SARADC_RESULT_OFFSET                0x014
#define SARADC_RESULT(n)                    (SARADC_RESULT_OFFSET + (n) * 4)
#define SARADC_RESULT_MASK                  0x0FFF
#define SARADC_RESULT_VALID                 (1 << 15)

#define SARADC_TEST_OFFSET                  0x030
#define SARADC_TEST_VREFSEL_BIT             2

#define SARADC_TRIM_OFFSET                  0x034

rt_inline void cvi_set_saradc_ctrl(unsigned long reg_base, rt_uint32_t value)
{
    value |= mmio_read_32(reg_base + SARADC_CTRL_OFFSET);
    mmio_write_32(reg_base + SARADC_CTRL_OFFSET, value);
}

rt_inline void cvi_reset_saradc_ctrl(unsigned long reg_base, rt_uint32_t value)
{
    value = mmio_read_32(reg_base + SARADC_CTRL_OFFSET) & ~value;
    mmio_write_32(reg_base + SARADC_CTRL_OFFSET, value);
}

rt_inline rt_uint32_t cvi_get_saradc_status(unsigned long reg_base)
{
    return((rt_uint32_t)mmio_read_32(reg_base + SARADC_STATUS_OFFSET));
}

rt_inline void cvi_set_cyc(unsigned long reg_base)
{
    rt_uint32_t value;

    value = mmio_read_32(reg_base + SARADC_CYC_SET_OFFSET);

    value &= ~SARADC_CYC_CLKDIV_DIV_16;
    mmio_write_32(reg_base + SARADC_CYC_SET_OFFSET, value);

    value |= SARADC_CYC_CLKDIV_DIV_16;                                                               //set saradc clock cycle=840ns
    mmio_write_32(reg_base + SARADC_CYC_SET_OFFSET, value);
}

rt_inline void cvi_do_calibration(unsigned long reg_base)
{
    rt_uint32_t val;

    val = mmio_read_32(reg_base + SARADC_TEST_OFFSET);
    val |= 1 << SARADC_TEST_VREFSEL_BIT;
    mmio_write_32(reg_base + SARADC_TEST_OFFSET, val);

    val = mmio_read_32(reg_base + SARADC_TRIM_OFFSET);
    val |= 0x4;
    mmio_write_32(reg_base + SARADC_TRIM_OFFSET, val);
}

int rt_hw_adc_init(void);

#endif /* __DRV_ADC_H__ */
