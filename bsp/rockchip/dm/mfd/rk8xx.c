/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "mfd.rk8xx"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rk8xx.h"

struct rk8xx_reg_data
{
    int addr;
    int mask;
    int value;
};

struct rk8xx_endpoint
{
    const char *name;
    const char *ofw_name;
    const char *ofw_compatible;

    int irqs_nr;
    const int *irqs_list;
};

struct rk8xx_irq_map
{
    rt_uint32_t reg_offset;
    rt_uint32_t mask;
};

#define RK8XX_IRQ_REG(IRQ, OFF, MASK) \
    [IRQ] = { .reg_offset = (OFF), .mask = (MASK) }

#define RK8XX_IRQ_REG_LINE(ID, REG_BITS) \
    [ID] = { .reg_offset = (ID) / (REG_BITS), .mask = RT_BIT((ID) % (REG_BITS)), }

struct rk8xx_irqchip
{
    struct rt_pic parent;

    struct rk8xx *rk8xx;

#define RK8XX_IRQCHIP_NUM_REGS_MAX 3
    int num_regs;
    int reg_stride;
    int mask_base;
    int status_base;
    int ack_base;

    int irqs_nr;
    const struct rk8xx_irq_map *irqs_map;

    struct rt_thread *irq_thread;
};

#define raw_to_rk8xx_irqchip(raw) rt_container_of(raw, struct rk8xx_irqchip, parent)

struct rk8xx_power
{
    struct rt_device parent;

    struct rk8xx *rk8xx;
};

#define raw_to_rk8xx_power(raw) rt_container_of(raw, struct rk8xx_power, parent)

static void rk8xx_irq_mask(struct rt_pic_irq *pirq)
{
    rt_uint16_t base;
    struct rk8xx_irqchip *rk8xx_ic = raw_to_rk8xx_irqchip(pirq->pic);
    const struct rk8xx_irq_map *irq_map = &rk8xx_ic->irqs_map[pirq->hwirq];

    base = rk8xx_ic->mask_base + (irq_map->reg_offset / rk8xx_ic->reg_stride);

    rk8xx_update_bits(rk8xx_ic->rk8xx, base, irq_map->mask, irq_map->mask);
}

static void rk8xx_irq_unmask(struct rt_pic_irq *pirq)
{
    rt_uint16_t base;
    struct rk8xx_irqchip *rk8xx_ic = raw_to_rk8xx_irqchip(pirq->pic);
    const struct rk8xx_irq_map *irq_map = &rk8xx_ic->irqs_map[pirq->hwirq];

    base = rk8xx_ic->mask_base + (irq_map->reg_offset / rk8xx_ic->reg_stride);

    rk8xx_update_bits(rk8xx_ic->rk8xx, base, irq_map->mask, 0);
}

static int rk8xx_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    int irq = -1;
    struct rt_pic_irq *pirq = rt_pic_find_irq(pic, hwirq);

    if (pirq)
    {
        struct rk8xx_irqchip *rk8xx_ic = raw_to_rk8xx_irqchip(pic);

        irq = rt_pic_config_irq(pic, hwirq, hwirq);
        pirq->mode = mode;
        rt_pic_cascade(pirq, rk8xx_ic->rk8xx->irq);
    }

    return irq;
}

static rt_err_t rk8xx_irq_parse(struct rt_pic *pic, struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    struct rk8xx_irqchip *rk8xx_ic = raw_to_rk8xx_irqchip(pic);

    if (args->args_count != 1)
    {
        return -RT_EINVAL;
    }

    out_pirq->mode = rt_pic_irq_get_triger_mode(rk8xx_ic->rk8xx->irq);
    out_pirq->hwirq = args->args[0];

    return RT_EOK;
}

const static struct rt_pic_ops rk8xx_irq_ops =
{
    .name = "RK8XX",
    .irq_mask = rk8xx_irq_mask,
    .irq_unmask = rk8xx_irq_unmask,
    .irq_map = rk8xx_irq_map,
    .irq_parse = rk8xx_irq_parse,
};

static void rk8xx_pmic_thread_isr(void *param)
{
    rt_uint32_t status[RK8XX_IRQCHIP_NUM_REGS_MAX];
    rt_uint16_t base, reg;
    struct rk8xx *rk8xx;
    struct rt_pic_irq *pirq;
    struct rk8xx_irqchip *rk8xx_ic = param;

    rk8xx = rk8xx_ic->rk8xx;

    while (RT_TRUE)
    {
        rt_thread_suspend(rk8xx_ic->irq_thread);
        rt_schedule();

        base = rk8xx_ic->status_base;
        rt_memset(status, 0, sizeof(status));

        for (int i = 0; i < rk8xx_ic->num_regs; ++i)
        {
            reg = base + i * rk8xx_ic->reg_stride;
            status[i] = rk8xx_read(rk8xx, reg);

            if ((rt_err_t)status[i] < 0)
            {
                LOG_E("Read IRQ status failed error = %s", rt_strerror(status[i]));

                goto _end;
            }
        }

        base = rk8xx_ic->ack_base;

        for (int i = 0; i < rk8xx_ic->num_regs; ++i)
        {
            rt_err_t err;

            reg = base + i * rk8xx_ic->reg_stride;
            err = rk8xx_write(rk8xx, reg, status[i]);

            if (err)
            {
                LOG_E("ACK IRQ failed error = %s", rt_strerror(err));

                goto _end;
            }
        }

        for (int i = 0; i < rk8xx_ic->irqs_nr; ++i)
        {
            base = rk8xx_ic->irqs_map[i].reg_offset / rk8xx_ic->reg_stride;

            if (status[base] & rk8xx_ic->irqs_map[i].mask)
            {
                pirq = rt_pic_find_irq(&rk8xx_ic->parent, i);

                if (pirq && pirq->pic)
                {
                    rt_pic_handle_isr(pirq);
                }
            }
        }
    _end:
        rt_hw_interrupt_umask(rk8xx->irq);
    }
}

static void rk8xx_pmic_isr(int irqno, void *param)
{
    struct rk8xx_irqchip *rk8xx_ic = param;

    rt_hw_interrupt_mask(rk8xx_ic->rk8xx->irq);

    rt_thread_resume(rk8xx_ic->irq_thread);
}

static const struct rk8xx_irq_map rk805_irqs[] =
{
    RK8XX_IRQ_REG(RK805_IRQ_PWRON_RISE, 0, RK805_IRQ_PWRON_RISE_MSK),
    RK8XX_IRQ_REG(RK805_IRQ_VB_LOW, 0, RK805_IRQ_VB_LOW_MSK),
    RK8XX_IRQ_REG(RK805_IRQ_PWRON, 0, RK805_IRQ_PWRON_MSK),
    RK8XX_IRQ_REG(RK805_IRQ_PWRON_LP, 0, RK805_IRQ_PWRON_LP_MSK),
    RK8XX_IRQ_REG(RK805_IRQ_HOTDIE, 0, RK805_IRQ_HOTDIE_MSK),
    RK8XX_IRQ_REG(RK805_IRQ_RTC_ALARM, 0, RK805_IRQ_RTC_ALARM_MSK),
    RK8XX_IRQ_REG(RK805_IRQ_RTC_PERIOD, 0, RK805_IRQ_RTC_PERIOD_MSK),
    RK8XX_IRQ_REG(RK805_IRQ_PWRON_FALL, 0, RK805_IRQ_PWRON_FALL_MSK),
};

static const struct rk8xx_irq_map rk806_irqs[] =
{
    /* INT_STS0 IRQs */
    RK8XX_IRQ_REG(RK806_IRQ_PWRON_FALL, 0, RK806_INT_STS_PWRON_FALL),
    RK8XX_IRQ_REG(RK806_IRQ_PWRON_RISE, 0, RK806_INT_STS_PWRON_RISE),
    RK8XX_IRQ_REG(RK806_IRQ_PWRON, 0, RK806_INT_STS_PWRON),
    RK8XX_IRQ_REG(RK806_IRQ_PWRON_LP, 0, RK806_INT_STS_PWRON_LP),
    RK8XX_IRQ_REG(RK806_IRQ_HOTDIE, 0, RK806_INT_STS_HOTDIE),
    RK8XX_IRQ_REG(RK806_IRQ_VDC_RISE, 0, RK806_INT_STS_VDC_RISE),
    RK8XX_IRQ_REG(RK806_IRQ_VDC_FALL, 0, RK806_INT_STS_VDC_FALL),
    RK8XX_IRQ_REG(RK806_IRQ_VB_LO, 0, RK806_INT_STS_VB_LO),
    /* INT_STS1 IRQs */
    RK8XX_IRQ_REG(RK806_IRQ_REV0, 1, RK806_INT_STS_REV0),
    RK8XX_IRQ_REG(RK806_IRQ_REV1, 1, RK806_INT_STS_REV1),
    RK8XX_IRQ_REG(RK806_IRQ_REV2, 1, RK806_INT_STS_REV2),
    RK8XX_IRQ_REG(RK806_IRQ_CRC_ERROR, 1, RK806_INT_STS_CRC_ERROR),
    RK8XX_IRQ_REG(RK806_IRQ_SLP3_GPIO, 1, RK806_INT_STS_SLP3_GPIO),
    RK8XX_IRQ_REG(RK806_IRQ_SLP2_GPIO, 1, RK806_INT_STS_SLP2_GPIO),
    RK8XX_IRQ_REG(RK806_IRQ_SLP1_GPIO, 1, RK806_INT_STS_SLP1_GPIO),
    RK8XX_IRQ_REG(RK806_IRQ_WDT, 1, RK806_INT_STS_WDT),
};

static const struct rk8xx_irq_map rk808_irqs[] =
{
    /* INT_STS */
    RK8XX_IRQ_REG(RK808_IRQ_VOUT_LO, 0, RK808_IRQ_VOUT_LO_MSK),
    RK8XX_IRQ_REG(RK808_IRQ_VB_LO, 0, RK808_IRQ_VB_LO_MSK),
    RK8XX_IRQ_REG(RK808_IRQ_PWRON, 0, RK808_IRQ_PWRON_MSK),
    RK8XX_IRQ_REG(RK808_IRQ_PWRON_LP, 0, RK808_IRQ_PWRON_LP_MSK),
    RK8XX_IRQ_REG(RK808_IRQ_HOTDIE, 0, RK808_IRQ_HOTDIE_MSK),
    RK8XX_IRQ_REG(RK808_IRQ_RTC_ALARM, 0, RK808_IRQ_RTC_ALARM_MSK),
    RK8XX_IRQ_REG(RK808_IRQ_RTC_PERIOD, 0, RK808_IRQ_RTC_PERIOD_MSK),
    /* INT_STS2 */
    RK8XX_IRQ_REG(RK808_IRQ_PLUG_IN_INT, 1, RK808_IRQ_PLUG_IN_INT_MSK),
    RK8XX_IRQ_REG(RK808_IRQ_PLUG_OUT_INT, 1, RK808_IRQ_PLUG_OUT_INT_MSK),
};

static const struct rk8xx_irq_map rk818_irqs[] =
{
    /* INT_STS */
    RK8XX_IRQ_REG(RK818_IRQ_VOUT_LO, 0, RK818_IRQ_VOUT_LO_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_VB_LO, 0, RK818_IRQ_VB_LO_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_PWRON, 0, RK818_IRQ_PWRON_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_PWRON_LP, 0, RK818_IRQ_PWRON_LP_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_HOTDIE, 0, RK818_IRQ_HOTDIE_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_RTC_ALARM, 0, RK818_IRQ_RTC_ALARM_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_RTC_PERIOD, 0, RK818_IRQ_RTC_PERIOD_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_USB_OV, 0, RK818_IRQ_USB_OV_MSK),
    /* INT_STS2 */
    RK8XX_IRQ_REG(RK818_IRQ_PLUG_IN, 1, RK818_IRQ_PLUG_IN_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_PLUG_OUT, 1, RK818_IRQ_PLUG_OUT_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_CHG_OK, 1, RK818_IRQ_CHG_OK_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_CHG_TE, 1, RK818_IRQ_CHG_TE_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_CHG_TS1, 1, RK818_IRQ_CHG_TS1_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_TS2, 1, RK818_IRQ_TS2_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_CHG_CVTLIM, 1, RK818_IRQ_CHG_CVTLIM_MSK),
    RK8XX_IRQ_REG(RK818_IRQ_DISCHG_ILIM, 1, RK818_IRQ_DISCHG_ILIM_MSK),
};

static const struct rk8xx_irq_map rk817_irqs[] =
{
    RK8XX_IRQ_REG_LINE(RK817_IRQ_PWRON_FALL, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_PWRON_RISE, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_PWRON, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_PWMON_LP, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_HOTDIE, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_RTC_ALARM, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_RTC_PERIOD, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_VB_LO, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_PLUG_IN, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_PLUG_OUT, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_CHRG_TERM, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_CHRG_TIME, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_CHRG_TS, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_USB_OV, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_CHRG_IN_CLMP, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_BAT_DIS_ILIM, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_GATE_GPIO, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_TS_GPIO, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_CODEC_PD, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_CODEC_PO, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_CLASSD_MUTE_DONE, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_CLASSD_OCP, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_BAT_OVP, 8),
    RK8XX_IRQ_REG_LINE(RK817_IRQ_CHRG_BAT_HI, 8)
};

static const int rk808_rtc_irqs[] =
{
    RK808_IRQ_RTC_ALARM,
};

static const int rk817_rtc_irqs[] =
{
    RK817_IRQ_RTC_ALARM,
};

static const int rk805_pwrkey_irqs[] =
{
    RK805_IRQ_PWRON_RISE,
    RK805_IRQ_PWRON_FALL,
};

static const int rk806_pwrkey_irqs[] =
{
    RK806_IRQ_PWRON_FALL,
    RK806_IRQ_PWRON_RISE,
};

static const int rk817_pwrkey_irqs[] =
{
    RK817_IRQ_PWRON_RISE,
    RK817_IRQ_PWRON_FALL,
};

static const int rk817_battery_irqs[] =
{
    RK817_IRQ_VB_LO,
};

static const int rk818_battery_irqs[] =
{
    RK818_IRQ_VB_LO,
};

static const int rk805_charger_irqs[] =
{
    RK805_IRQ_VB_LOW,
};

static const int rk817_charger_irqs[] =
{
    RK817_IRQ_PLUG_IN,
    RK817_IRQ_PLUG_OUT,
};

static const int rk818_charger_irqs[] =
{
    RK818_IRQ_PLUG_IN,
    RK818_IRQ_PLUG_OUT,
};

static const int rk817_codec_irqs[] =
{
    RK817_IRQ_CODEC_PD,
    RK817_IRQ_CODEC_PO,
};

static const int rk806_watchdog_irqs[] =
{
    RK806_IRQ_WDT,
};

static const struct rk8xx_reg_data rk805_pre_init_regs[] =
{
    { RK805_BUCK1_CONFIG_REG, RK805_BUCK1_2_ILMAX_MASK, RK805_BUCK1_2_ILMAX_4000MA },
    { RK805_BUCK2_CONFIG_REG, RK805_BUCK1_2_ILMAX_MASK, RK805_BUCK1_2_ILMAX_4000MA },
    { RK805_BUCK3_CONFIG_REG, RK805_BUCK3_4_ILMAX_MASK, RK805_BUCK3_ILMAX_3000MA },
    { RK805_BUCK4_CONFIG_REG, RK805_BUCK3_4_ILMAX_MASK, RK805_BUCK4_ILMAX_3500MA },
    { RK805_BUCK4_CONFIG_REG, BUCK_ILMIN_MASK, BUCK_ILMIN_400MA },
    { RK805_THERMAL_REG, TEMP_HOTDIE_MSK, TEMP115C },
};

static const struct rk8xx_reg_data rk806_pre_init_regs[] =
{
    { RK806_GPIO_INT_CONFIG, RK806_INT_POL_MSK, RK806_INT_POL_L },
    { RK806_SYS_CFG3, RK806_SLAVE_RESTART_FUN_MSK, RK806_SLAVE_RESTART_FUN_EN },
    { RK806_SYS_OPTION, RK806_SYS_ENB2_2M_MSK, RK806_SYS_ENB2_2M_EN },
};

static const struct rk8xx_reg_data rk808_pre_init_regs[] =
{
    { RK808_BUCK3_CONFIG_REG, BUCK_ILMIN_MASK, BUCK_ILMIN_150MA },
    { RK808_BUCK4_CONFIG_REG, BUCK_ILMIN_MASK, BUCK_ILMIN_200MA },
    { RK808_BOOST_CONFIG_REG, BOOST_ILMIN_MASK, BOOST_ILMIN_100MA },
    { RK808_BUCK1_CONFIG_REG, BUCK1_RATE_MASK, BUCK_ILMIN_200MA },
    { RK808_BUCK2_CONFIG_REG, BUCK2_RATE_MASK, BUCK_ILMIN_200MA },
    { RK808_DCDC_UV_ACT_REG, BUCK_UV_ACT_MASK, BUCK_UV_ACT_DISABLE},
    { RK808_VB_MON_REG, MASK_ALL, VB_LO_ACT | VB_LO_SEL_3500MV },
};

static const struct rk8xx_reg_data rk817_pre_init_regs[] =
{
    {RK817_RTC_CTRL_REG, RTC_STOP, RTC_STOP},
    /* Codec specific registers */
    { RK817_CODEC_DTOP_VUCTL, MASK_ALL, 0x03 },
    { RK817_CODEC_DTOP_VUCTIME, MASK_ALL, 0x00 },
    { RK817_CODEC_DTOP_LPT_SRST, MASK_ALL, 0x00 },
    { RK817_CODEC_DTOP_DIGEN_CLKE, MASK_ALL, 0x00 },
    /* from vendor driver, CODEC_AREF_RTCFG0 not defined in data sheet */
    { RK817_CODEC_AREF_RTCFG0, MASK_ALL, 0x00 },
    { RK817_CODEC_AREF_RTCFG1, MASK_ALL, 0x06 },
    { RK817_CODEC_AADC_CFG0, MASK_ALL, 0xc8 },
    /* from vendor driver, CODEC_AADC_CFG1 not defined in data sheet */
    { RK817_CODEC_AADC_CFG1, MASK_ALL, 0x00 },
    { RK817_CODEC_DADC_VOLL, MASK_ALL, 0x00 },
    { RK817_CODEC_DADC_VOLR, MASK_ALL, 0x00 },
    { RK817_CODEC_DADC_SR_ACL0, MASK_ALL, 0x00 },
    { RK817_CODEC_DADC_ALC1, MASK_ALL, 0x00 },
    { RK817_CODEC_DADC_ALC2, MASK_ALL, 0x00 },
    { RK817_CODEC_DADC_NG, MASK_ALL, 0x00 },
    { RK817_CODEC_DADC_HPF, MASK_ALL, 0x00 },
    { RK817_CODEC_DADC_RVOLL, MASK_ALL, 0xff },
    { RK817_CODEC_DADC_RVOLR, MASK_ALL, 0xff },
    { RK817_CODEC_AMIC_CFG0, MASK_ALL, 0x70 },
    { RK817_CODEC_AMIC_CFG1, MASK_ALL, 0x00 },
    { RK817_CODEC_DMIC_PGA_GAIN, MASK_ALL, 0x66 },
    { RK817_CODEC_DMIC_LMT1, MASK_ALL, 0x00 },
    { RK817_CODEC_DMIC_LMT2, MASK_ALL, 0x00 },
    { RK817_CODEC_DMIC_NG1, MASK_ALL, 0x00 },
    { RK817_CODEC_DMIC_NG2, MASK_ALL, 0x00 },
    /* from vendor driver, CODEC_ADAC_CFG0 not defined in data sheet */
    { RK817_CODEC_ADAC_CFG0, MASK_ALL, 0x00 },
    { RK817_CODEC_ADAC_CFG1, MASK_ALL, 0x07 },
    { RK817_CODEC_DDAC_POPD_DACST, MASK_ALL, 0x82 },
    { RK817_CODEC_DDAC_VOLL, MASK_ALL, 0x00 },
    { RK817_CODEC_DDAC_VOLR, MASK_ALL, 0x00 },
    { RK817_CODEC_DDAC_SR_LMT0, MASK_ALL, 0x00 },
    { RK817_CODEC_DDAC_LMT1, MASK_ALL, 0x00 },
    { RK817_CODEC_DDAC_LMT2, MASK_ALL, 0x00 },
    { RK817_CODEC_DDAC_MUTE_MIXCTL, MASK_ALL, 0xa0 },
    { RK817_CODEC_DDAC_RVOLL, MASK_ALL, 0xff },
    { RK817_CODEC_DADC_RVOLR, MASK_ALL, 0xff },
    { RK817_CODEC_AMIC_CFG0, MASK_ALL, 0x70 },
    { RK817_CODEC_AMIC_CFG1, MASK_ALL, 0x00 },
    { RK817_CODEC_DMIC_PGA_GAIN, MASK_ALL, 0x66 },
    { RK817_CODEC_DMIC_LMT1, MASK_ALL, 0x00 },
    { RK817_CODEC_DMIC_LMT2, MASK_ALL, 0x00 },
    { RK817_CODEC_DMIC_NG1, MASK_ALL, 0x00 },
    { RK817_CODEC_DMIC_NG2, MASK_ALL, 0x00 },
    /* from vendor driver, CODEC_ADAC_CFG0 not defined in data sheet */
    { RK817_CODEC_ADAC_CFG0, MASK_ALL, 0x00 },
    { RK817_CODEC_ADAC_CFG1, MASK_ALL, 0x07 },
    { RK817_CODEC_DDAC_POPD_DACST, MASK_ALL, 0x82 },
    { RK817_CODEC_DDAC_VOLL, MASK_ALL, 0x00 },
    { RK817_CODEC_DDAC_VOLR, MASK_ALL, 0x00 },
    { RK817_CODEC_DDAC_SR_LMT0, MASK_ALL, 0x00 },
    { RK817_CODEC_DDAC_LMT1, MASK_ALL, 0x00 },
    { RK817_CODEC_DDAC_LMT2, MASK_ALL, 0x00 },
    { RK817_CODEC_DDAC_MUTE_MIXCTL, MASK_ALL, 0xa0 },
    { RK817_CODEC_DDAC_RVOLL, MASK_ALL, 0xff },
    { RK817_CODEC_DDAC_RVOLR, MASK_ALL, 0xff },
    { RK817_CODEC_AHP_ANTI0, MASK_ALL, 0x00 },
    { RK817_CODEC_AHP_ANTI1, MASK_ALL, 0x00 },
    { RK817_CODEC_AHP_CFG0, MASK_ALL, 0xe0 },
    { RK817_CODEC_AHP_CFG1, MASK_ALL, 0x1f },
    { RK817_CODEC_AHP_CP, MASK_ALL, 0x09 },
    { RK817_CODEC_ACLASSD_CFG1, MASK_ALL, 0x69 },
    { RK817_CODEC_ACLASSD_CFG2, MASK_ALL, 0x44 },
    { RK817_CODEC_APLL_CFG0, MASK_ALL, 0x04 },
    { RK817_CODEC_APLL_CFG1, MASK_ALL, 0x00 },
    { RK817_CODEC_APLL_CFG2, MASK_ALL, 0x30 },
    { RK817_CODEC_APLL_CFG3, MASK_ALL, 0x19 },
    { RK817_CODEC_APLL_CFG4, MASK_ALL, 0x65 },
    { RK817_CODEC_APLL_CFG5, MASK_ALL, 0x01 },
    { RK817_CODEC_DI2S_CKM, MASK_ALL, 0x01 },
    { RK817_CODEC_DI2S_RSD, MASK_ALL, 0x00 },
    { RK817_CODEC_DI2S_RXCR1, MASK_ALL, 0x00 },
    { RK817_CODEC_DI2S_RXCR2, MASK_ALL, 0x17 },
    { RK817_CODEC_DI2S_RXCMD_TSD, MASK_ALL, 0x00 },
    { RK817_CODEC_DI2S_TXCR1, MASK_ALL, 0x00 },
    { RK817_CODEC_DI2S_TXCR2, MASK_ALL, 0x17 },
    { RK817_CODEC_DI2S_TXCR3_TXCMD, MASK_ALL, 0x00 },
    { RK817_GPIO_INT_CFG, RK817_INT_POL_MSK, RK817_INT_POL_L},
    { RK817_SYS_CFG(1), RK817_HOTDIE_TEMP_MSK | RK817_TSD_TEMP_MSK, RK817_HOTDIE_105 | RK817_TSD_140},
};

static const struct rk8xx_reg_data rk818_pre_init_regs[] = {
    /* improve efficiency */
    { RK818_BUCK2_CONFIG_REG, BUCK2_RATE_MASK, BUCK_ILMIN_250MA },
    { RK818_BUCK4_CONFIG_REG, BUCK_ILMIN_MASK, BUCK_ILMIN_250MA },
    { RK818_BOOST_CONFIG_REG, BOOST_ILMIN_MASK, BOOST_ILMIN_100MA },
    { RK818_USB_CTRL_REG, RK818_USB_ILIM_SEL_MASK, RK818_USB_ILMIN_2000MA },
    /* close charger when usb lower then 3.4V */
    { RK818_USB_CTRL_REG, RK818_USB_CHG_SD_VSEL_MASK, (0x7 << 4) },
    /* no action when vref */
    { RK818_H5V_EN_REG, RT_BIT(1), RK818_REF_RDY_CTRL },
    /* enable HDMI 5V */
    { RK818_H5V_EN_REG, RT_BIT(0), RK818_H5V_EN },
    { RK808_VB_MON_REG, MASK_ALL, VB_LO_ACT | VB_LO_SEL_3500MV },
};

static const struct rk8xx_endpoint rk805_eps[] =
{
    { .name = "rk8xx-clkout", },
    { .name = "rk8xx-pinctrl", .ofw_name = "pinctrl_rk8xx" },
    { .name = "rk8xx-regulator", .ofw_name = "regulators" },
    {
        .name = "rk8xx-rtc",
        .irqs_nr = RT_ARRAY_SIZE(rk808_rtc_irqs),
        .irqs_list = rk808_rtc_irqs,
    },
    {
        .name = "rk8xx-pwrkey",
        .ofw_name = "pwrkey",
        .irqs_nr = RT_ARRAY_SIZE(rk805_pwrkey_irqs),
        .irqs_list = rk805_pwrkey_irqs,
    },
    {
        .name = "rk8xx-battery",
        .ofw_name = "battery",
        .irqs_nr = RT_ARRAY_SIZE(rk805_charger_irqs),
        .irqs_list = rk805_charger_irqs,
    },
};

static const struct rk8xx_endpoint rk806_eps[] =
{
    { .name = "rk8xx-pinctrl", .ofw_name = "pinctrl_rk806" },
    { .name = "rk8xx-regulator", .ofw_name = "regulators" },
    {
        .name = "rk8xx-pwrkey",
        .ofw_name = "pwrkey",
        .irqs_nr = RT_ARRAY_SIZE(rk806_pwrkey_irqs),
        .irqs_list = rk806_pwrkey_irqs,
    },
    {
        .name = "rk8xx-watchdog",
        .irqs_nr = RT_ARRAY_SIZE(rk806_watchdog_irqs),
        .irqs_list = rk806_watchdog_irqs,
    },
};

static const struct rk8xx_endpoint rk808_eps[] =
{
    { .name = "rk8xx-clkout", },
    { .name = "rk8xx-regulator", .ofw_name = "regulators" },
    {
        .name = "rk8xx-rtc",
        .irqs_nr = RT_ARRAY_SIZE(rk808_rtc_irqs),
        .irqs_list = rk808_rtc_irqs,
    },
};

static const struct rk8xx_endpoint rk817_eps[] =
{
    { .name = "rk8xx-clkout", },
    { .name = "rk8xx-regulator", .ofw_name = "regulators" },
    {
        .name = "rk8xx-rtc",
        .irqs_nr = RT_ARRAY_SIZE(rk817_rtc_irqs),
        .irqs_list = rk817_rtc_irqs,
    },
    {
        .name = "rk8xx-pwrkey",
        .ofw_name = "pwrkey",
        .irqs_nr = RT_ARRAY_SIZE(rk817_pwrkey_irqs),
        .irqs_list = rk817_pwrkey_irqs,
    },
    {
        .name = "rk8xx-battery",
        .ofw_name = "battery",
        .ofw_compatible = "rk817,battery",
        .irqs_nr = RT_ARRAY_SIZE(rk817_battery_irqs),
        .irqs_list = rk817_battery_irqs,
    },
    {
        .name = "rk8xx-charger",
        .ofw_name = "charger",
        .ofw_compatible = "rk817,charger",
        .irqs_nr = RT_ARRAY_SIZE(rk817_charger_irqs),
        .irqs_list = rk817_charger_irqs,
    },
    {
        .name = "rk8xx-codec",
        .ofw_name = "codec",
        .ofw_compatible = "rockchip,rk817-codec",
        .irqs_nr = RT_ARRAY_SIZE(rk817_codec_irqs),
        .irqs_list = rk817_codec_irqs,
    },
};

static const struct rk8xx_endpoint rk818_eps[] =
{
    { .name = "rk8xx-clkout", },
    { .name = "rk8xx-regulator", .ofw_name = "regulators" },
    {
        .name = "rk8xx-battery",
        .ofw_name = "battery",
        .ofw_compatible = "rk818-battery",
        .irqs_nr = RT_ARRAY_SIZE(rk818_battery_irqs),
        .irqs_list = rk818_battery_irqs,
    },
    {
        .name = "rk8xx-charger",
        .ofw_name = "charger",
        .irqs_nr = RT_ARRAY_SIZE(rk818_charger_irqs),
        .irqs_list = rk818_charger_irqs,
    },
    {
        .name = "rk8xx-rtc",
        .irqs_nr = RT_ARRAY_SIZE(rk808_rtc_irqs),
        .irqs_list = rk808_rtc_irqs,
    },
};

static rt_err_t rk8xx_power_off(struct rt_device *dev)
{
    rt_uint32_t reg, bit;
    struct rk8xx_power *rk8xx_power = raw_to_rk8xx_power(dev);
    struct rk8xx *rk8xx = rk8xx_power->rk8xx;

    switch (rk8xx->variant)
    {
    case RK805_ID:
        reg = RK805_DEV_CTRL_REG;
        bit = DEV_OFF;
        break;

    case RK806_ID:
        reg = RK806_SYS_CFG3;
        bit = DEV_OFF;
        break;

    case RK808_ID:
        reg = RK808_DEVCTRL_REG,
        bit = DEV_OFF_RST;
        break;

    case RK809_ID:
    case RK817_ID:
        reg = RK817_SYS_CFG(3);
        bit = DEV_OFF;
        break;

    case RK818_ID:
        reg = RK818_DEVCTRL_REG;
        bit = DEV_OFF;
        break;

    default:
        return -RT_EEMPTY;
    }

    return rk8xx_update_bits(rk8xx, reg, bit, bit);
}

static rt_err_t rk8xx_restart(struct rt_device *dev)
{
    rt_uint32_t reg, bit;
    struct rk8xx_power *rk8xx_power = raw_to_rk8xx_power(dev);
    struct rk8xx *rk8xx = rk8xx_power->rk8xx;

    switch (rk8xx->variant)
    {
    case RK806_ID:
        reg = RK806_SYS_CFG3;
        bit = DEV_RST;
        break;

    case RK809_ID:
    case RK817_ID:
        reg = RK817_SYS_CFG(3);
        bit = DEV_RST;
        break;

    default:
        return -RT_EEMPTY;
    }

    return rk8xx_update_bits(rk8xx, reg, bit, bit);
}

static rt_err_t create_rk8xx_platform_device(rt_bus_t platform_bus,
        struct rk8xx *rk8xx,
        const char *name,
        void *ofw_node)
{
    rt_err_t err;
    struct rt_platform_device *pdev = rt_platform_device_alloc(name);

    if (!pdev)
    {
        return -RT_ENOMEM;
    }

    pdev->parent.ofw_node = ofw_node;
    pdev->priv = rk8xx;

    err = rt_bus_add_device(platform_bus, &pdev->parent);

    if (err && err != -RT_ENOSYS)
    {
        LOG_E("Add RK8XX - %s error = %s", name, rt_strerror(err));
    }

    return err;
}

static rt_err_t rk8xx_ofw_bind_irq(struct rk8xx_irqchip *rk8xx_ic,
        struct rt_ofw_node *dev_np,
        struct rt_ofw_node *np,
        const struct rk8xx_endpoint *ep)
{
    /*
     *  ic: rk8xx-interrupt-controller {
     *      #interrupt-cells = <1>;
     *
     *      rk8xx-endpoint0 {
     *          interrupts-extended = <&ic 0>;
     *      }
     *
     *      rk8xx-endpoint1 {
     *          interrupts-extended = <&ic 1>, <&ic 2>;
     *      }
     *  }
     */
    rt_err_t err;
    fdt32_t *values;
    rt_size_t irq_list_size;
    static fdt32_t irq_cell;
    static struct rt_ofw_node *ic_np = RT_NULL;

    if (!ic_np)
    {
        ic_np = rt_ofw_append_child(dev_np, "rk8xx-interrupt-controller");

        if (!ic_np)
        {
            return -RT_ENOSYS;
        }

        irq_cell = cpu_to_fdt32(1);
        err = rt_ofw_append_prop(ic_np, "#interrupt-cells", sizeof(fdt32_t), &irq_cell);

        if (err)
        {
            return err;
        }

        rt_ofw_data(ic_np) = &rk8xx_ic->parent;
    }

    irq_list_size = sizeof(fdt32_t) * 2 * ep->irqs_nr;
    values = rt_malloc(irq_list_size);

    if (!values)
    {
        return -RT_ENOMEM;
    }

    for (int i = 0; i < ep->irqs_nr; ++i)
    {
        values[i * 2] = cpu_to_fdt32(ic_np->phandle);
        values[i * 2 + 1] = cpu_to_fdt32(ep->irqs_list[i]);
    }

    if ((err = rt_ofw_append_prop(np, "interrupts-extended", irq_list_size, values)))
    {
        rt_free(values);
    }

    return err;
}

rt_err_t rk8xx_shutdown(struct rk8xx *rk8xx)
{
    rt_err_t err;

    switch (rk8xx->variant)
    {
    case RK805_ID:
        err = rk8xx_update_bits(rk8xx, RK805_GPIO_IO_POL_REG, SLP_SD_MSK, SHUTDOWN_FUN);
        break;

    case RK809_ID:
    case RK817_ID:
        err = rk8xx_update_bits(rk8xx, RK817_SYS_CFG(3), RK817_SLPPIN_FUNC_MSK, SLPPIN_DN_FUN);
        break;

    default:
        return RT_EOK;
    }

    if (err)
    {
        LOG_W("Cannot switch to power down function");
    }

    return err;
}

rt_err_t rk8xx_probe(struct rk8xx *rk8xx)
{
    rt_err_t err;
    rt_bool_t iomux_retry;
    rt_bus_t platform_bus;
    int rk8xx_ep_nr, pre_init_regs_nr;
    struct rt_ofw_node *np, *dev_np;
    struct rk8xx_irqchip *rk8xx_ic;
    const struct rk8xx_endpoint *rk8xx_ep;
    const struct rk8xx_reg_data *pre_init_regs;

    if (!rk8xx)
    {
        return -RT_EINVAL;
    }

    platform_bus = rt_bus_find_by_name("platform");

    if (!platform_bus)
    {
        return -RT_EIO;
    }

    dev_np = rk8xx->dev->ofw_node;

    rk8xx_ic = rt_calloc(1, sizeof(*rk8xx_ic));

    if (!rk8xx_ic)
    {
        return -RT_ENOMEM;
    }

    switch (rk8xx->variant)
    {
    case RK805_ID:
        rk8xx_ic->num_regs = 1;
        rk8xx_ic->status_base = RK805_INT_STS_REG;
        rk8xx_ic->mask_base = RK805_INT_STS_MSK_REG;
        rk8xx_ic->ack_base = RK805_INT_STS_REG;
        rk8xx_ic->irqs_nr = RT_ARRAY_SIZE(rk805_irqs);
        rk8xx_ic->irqs_map = rk805_irqs;

        rk8xx_ep = rk805_eps;
        rk8xx_ep_nr = RT_ARRAY_SIZE(rk805_eps);

        pre_init_regs = rk805_pre_init_regs;
        pre_init_regs_nr = RT_ARRAY_SIZE(rk805_pre_init_regs);
        break;

    case RK806_ID:
        rk8xx_ic->num_regs = 2;
        rk8xx_ic->reg_stride = 2;
        rk8xx_ic->mask_base = RK806_INT_MSK0;
        rk8xx_ic->status_base = RK806_INT_STS0;
        rk8xx_ic->ack_base = RK806_INT_STS0;
        rk8xx_ic->irqs_nr = RT_ARRAY_SIZE(rk806_irqs);
        rk8xx_ic->irqs_map = rk806_irqs;

        rk8xx_ep = rk806_eps;
        rk8xx_ep_nr = RT_ARRAY_SIZE(rk806_eps);

        pre_init_regs = rk806_pre_init_regs;
        pre_init_regs_nr = RT_ARRAY_SIZE(rk806_pre_init_regs);
        break;

    case RK808_ID:
        rk8xx_ic->num_regs = 2;
        rk8xx_ic->reg_stride = 2;
        rk8xx_ic->status_base = RK808_INT_STS_REG1;
        rk8xx_ic->mask_base = RK808_INT_STS_MSK_REG1;
        rk8xx_ic->ack_base = RK808_INT_STS_REG1;
        rk8xx_ic->irqs_nr = RT_ARRAY_SIZE(rk808_irqs);
        rk8xx_ic->irqs_map = rk808_irqs;

        rk8xx_ep = rk808_eps;
        rk8xx_ep_nr = RT_ARRAY_SIZE(rk808_eps);

        pre_init_regs = rk808_pre_init_regs;
        pre_init_regs_nr = RT_ARRAY_SIZE(rk808_pre_init_regs);
        break;

    case RK809_ID:
    case RK817_ID:
        rk8xx_ic->num_regs = 3;
        rk8xx_ic->reg_stride = 2;
        rk8xx_ic->status_base = RK817_INT_STS_REG0;
        rk8xx_ic->mask_base = RK817_INT_STS_MSK_REG0;
        rk8xx_ic->ack_base = RK817_INT_STS_REG0;
        rk8xx_ic->irqs_nr = RT_ARRAY_SIZE(rk817_irqs);
        rk8xx_ic->irqs_map = rk817_irqs;

        rk8xx_ep = rk817_eps;
        rk8xx_ep_nr = RT_ARRAY_SIZE(rk817_eps);

        pre_init_regs = rk817_pre_init_regs;
        pre_init_regs_nr = RT_ARRAY_SIZE(rk817_pre_init_regs);
        break;

    case RK818_ID:
        rk8xx_ic->num_regs = 2;
        rk8xx_ic->reg_stride = 2;
        rk8xx_ic->status_base = RK818_INT_STS_REG1;
        rk8xx_ic->mask_base = RK818_INT_STS_MSK_REG1;
        rk8xx_ic->ack_base = RK818_INT_STS_REG1;
        rk8xx_ic->irqs_nr = RT_ARRAY_SIZE(rk818_irqs);
        rk8xx_ic->irqs_map = rk818_irqs;

        rk8xx_ep = rk818_eps;
        rk8xx_ep_nr = RT_ARRAY_SIZE(rk818_eps);

        pre_init_regs = rk818_pre_init_regs;
        pre_init_regs_nr = RT_ARRAY_SIZE(rk818_pre_init_regs);
        break;

    default:
        LOG_E("Unsupported RK8XX ID %u", rk8xx->variant);
        return -RT_EINVAL;
    }

    RT_ASSERT(rk8xx_ic->num_regs <= RK8XX_IRQCHIP_NUM_REGS_MAX);

    rk8xx_ic->rk8xx = rk8xx;
    rk8xx_ic->parent.priv_data = rk8xx_ic;
    rk8xx_ic->parent.ops = &rk8xx_irq_ops;

    err = rt_pic_linear_irq(&rk8xx_ic->parent, rk8xx_ic->irqs_nr);

    if (err)
    {
        LOG_E("Init RK8XX IRQ chip failed error = %s", rt_strerror(err));

        return err;
    }

    rt_pic_user_extends(&rk8xx_ic->parent);

    /* Clear all interrupts */
    for (int i = 0; i < rk8xx_ic->num_regs; ++i)
    {
        rk8xx_write(rk8xx, rk8xx_ic->ack_base + i * rk8xx_ic->reg_stride, 0xff);
    }

    for (int i = 0; i < pre_init_regs_nr; ++i)
    {
        err = rk8xx_update_bits(rk8xx, pre_init_regs[i].addr,
                pre_init_regs[i].mask, pre_init_regs[i].value);

        if (err)
        {
            LOG_E("Write to %x fail", pre_init_regs[i].addr);
            goto _fail;
        }
    }

    rt_pic_user_extends(&rk8xx_ic->parent);

    iomux_retry = rt_pin_ctrl_confs_apply_by_name(rk8xx->dev, RT_NULL) < 0;

    if (rt_ofw_prop_read_bool(dev_np, "rockchip,system-power-controller"))
    {
        struct rt_device *dev;
        struct rk8xx_power *rk8xx_power = rt_calloc(1, sizeof(*rk8xx_power));

        if (!rk8xx_power)
        {
            err = -RT_ENOMEM;
            goto _fail;
        }

        dev = &rk8xx_power->parent;
        rt_dm_dev_set_name(dev, "rk-sys-pm");
        rk8xx_power->rk8xx = rk8xx;

        err = rt_dm_power_off_handler(dev, RT_DM_POWER_OFF_MODE_SHUTDOWN,
                RT_DM_POWER_OFF_PRIO_PLATFORM, &rk8xx_power_off);

        if (err)
        {
            LOG_E("Add %s failed", "shutdown");
        }

        err = rt_dm_power_off_handler(dev, RT_DM_POWER_OFF_MODE_RESET,
                RT_DM_POWER_OFF_PRIO_PLATFORM, &rk8xx_restart);

        if (err)
        {
            LOG_E("Add %s failed", "reset");
        }
    }

    for (int i = 0; i < rk8xx_ep_nr; ++i, ++rk8xx_ep)
    {
        np = RT_NULL;

        if (rk8xx_ep->ofw_name)
        {
            if (!(np = rt_ofw_get_child_by_tag(dev_np, rk8xx_ep->ofw_name)))
            {
                if (rk8xx_ep->ofw_compatible)
                {
                    np = rt_ofw_get_child_by_compatible(dev_np, rk8xx_ep->ofw_compatible);
                }

                if (!np)
                {
                    LOG_D("%s not found", rk8xx_ep->ofw_name);

                    continue;
                }
            }

            if (!rt_ofw_node_is_available(np))
            {
                continue;
            }
        }

        if (rk8xx_ep->irqs_nr)
        {
            if (!np && !(np = rt_ofw_append_child(dev_np, rk8xx_ep->name)))
            {
                continue;
            }

            err = rk8xx_ofw_bind_irq(rk8xx_ic, dev_np, np, rk8xx_ep);

            if (err == -RT_ENOMEM)
            {
                goto _out_put;
            }
        }

        if (!rt_strcmp(rk8xx_ep->name, "rk8xx-clkout"))
        {
            np = rt_ofw_node_get(dev_np);
        }

        err = create_rk8xx_platform_device(platform_bus, rk8xx, rk8xx_ep->name, np);

    _out_put:
        rt_ofw_node_put(np);

        if (err == -RT_ENOMEM)
        {
            goto _fail;
        }
    }

    if (iomux_retry)
    {
        if ((err = rt_pin_ctrl_confs_apply_by_name(rk8xx->dev, RT_NULL)))
        {
            LOG_W("Pinctrl apply error = %s", rt_strerror(err));
        }
    }

    rk8xx_ic->irq_thread = rt_thread_create("rk8xx-pmic", &rk8xx_pmic_thread_isr,
            rk8xx_ic, DM_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX / 2, 10);

    if (!rk8xx_ic->irq_thread)
    {
        goto _not_irq_conf;
    }

    rt_thread_startup(rk8xx_ic->irq_thread);

    rt_hw_interrupt_install(rk8xx->irq, &rk8xx_pmic_isr, rk8xx_ic, "rk8xx-pmic");
    rt_hw_interrupt_umask(rk8xx->irq);

_not_irq_conf:
    return RT_EOK;

_fail:
    rt_pic_cancel_irq(&rk8xx_ic->parent);

    return err;
}
