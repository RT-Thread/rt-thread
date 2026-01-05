/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "thermal.rk-tsadc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/*
 * TSADC Sensor Register description:
 *
 * TSADCV2_* are used for RK3288 SoCs, the other chips can reuse it.
 * TSADCV3_* are used for newer SoCs than RK3288. (e.g: RK3228, RK3399)
 */
#define TSADCV2_USER_CON                    0x00
#define TSADCV2_AUTO_CON                    0x04
#define TSADCV2_INT_EN                      0x08
#define TSADCV2_INT_PD                      0x0c
#define TSADCV3_AUTO_SRC_CON                0x0c
#define TSADCV3_HT_INT_EN                   0x14
#define TSADCV3_HSHUT_GPIO_INT_EN           0x18
#define TSADCV3_HSHUT_CRU_INT_EN            0x1c
#define TSADCV3_INT_PD                      0x24
#define TSADCV3_HSHUT_PD                    0x28
#define TSADCV2_DATA(chn)                   (0x20 + (chn) * 0x04)
#define TSADCV2_COMP_INT(chn)               (0x30 + (chn) * 0x04)
#define TSADCV2_COMP_SHUT(chn)              (0x40 + (chn) * 0x04)
#define TSADCV3_DATA(chn)                   (0x2c + (chn) * 0x04)
#define TSADCV3_COMP_INT(chn)               (0x6c + (chn) * 0x04)
#define TSADCV3_COMP_SHUT(chn)              (0x10c + (chn) * 0x04)
#define TSADCV2_HIGHT_INT_DEBOUNCE          0x60
#define TSADCV2_HIGHT_TSHUT_DEBOUNCE        0x64
#define TSADCV3_HIGHT_INT_DEBOUNCE          0x14c
#define TSADCV3_HIGHT_TSHUT_DEBOUNCE        0x150
#define TSADCV2_AUTO_PERIOD                 0x68
#define TSADCV2_AUTO_PERIOD_HT              0x6c
#define TSADCV3_AUTO_PERIOD                 0x154
#define TSADCV3_AUTO_PERIOD_HT              0x158

#define TSADCV2_AUTO_EN                     RT_BIT(0)
#define TSADCV2_AUTO_EN_MASK                RT_BIT(16)
#define TSADCV2_AUTO_SRC_EN(chn)            RT_BIT(4 + (chn))
#define TSADCV3_AUTO_SRC_EN(chn)            RT_BIT(chn)
#define TSADCV3_AUTO_SRC_EN_MASK(chn)       RT_BIT(16 + chn)
#define TSADCV2_AUTO_TSHUT_POLARITY_HIGH    RT_BIT(8)
#define TSADCV2_AUTO_TSHUT_POLARITY_MASK    RT_BIT(24)

#define TSADCV3_AUTO_Q_SEL_EN               RT_BIT(1)

#define TSADCV2_INT_SRC_EN(chn)             RT_BIT(chn)
#define TSADCV2_INT_SRC_EN_MASK(chn)        RT_BIT(16 + (chn))
#define TSADCV2_SHUT_2GPIO_SRC_EN(chn)      RT_BIT(4 + (chn))
#define TSADCV2_SHUT_2CRU_SRC_EN(chn)       RT_BIT(8 + (chn))

#define TSADCV2_INT_PD_CLEAR_MASK           (~RT_BIT(8))
#define TSADCV3_INT_PD_CLEAR_MASK           (~RT_BIT(16))
#define TSADCV4_INT_PD_CLEAR_MASK           0xffffffff

#define TSADCV2_DATA_MASK                   0xfff
#define TSADCV3_DATA_MASK                   0x3ff
#define TSADCV4_DATA_MASK                   0x1ff

#define TSADCV2_HIGHT_INT_DEBOUNCE_COUNT    4
#define TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT  4
#define TSADCV2_AUTO_PERIOD_TIME            250  /* 250ms */
#define TSADCV2_AUTO_PERIOD_HT_TIME         50   /* 50ms */
#define TSADCV3_AUTO_PERIOD_TIME            1875 /* 2.5ms */
#define TSADCV3_AUTO_PERIOD_HT_TIME         1875 /* 2.5ms */

#define TSADCV5_AUTO_PERIOD_TIME            1622 /* 2.5ms */
#define TSADCV5_AUTO_PERIOD_HT_TIME         1622 /* 2.5ms */
#define TSADCV6_AUTO_PERIOD_TIME            5000 /* 2.5ms */
#define TSADCV6_AUTO_PERIOD_HT_TIME         5000 /* 2.5ms */

#define TSADCV2_USER_INTER_PD_SOC           0x340 /* 13 clocks */
#define TSADCV5_USER_INTER_PD_SOC           0xfc0 /* 97us, at least 90us */

#define GRF_SARADC_TESTBIT                  0x0e644
#define GRF_TSADC_TESTBIT_L                 0x0e648
#define GRF_TSADC_TESTBIT_H                 0x0e64c

#define PX30_GRF_SOC_CON2                   0x0408

#define RK3568_GRF_TSADC_CON                0x0600
#define RK3568_GRF_TSADC_ANA_REG0           (0x10001 << 0)
#define RK3568_GRF_TSADC_ANA_REG1           (0x10001 << 1)
#define RK3568_GRF_TSADC_ANA_REG2           (0x10001 << 2)
#define RK3568_GRF_TSADC_TSEN               (0x10001 << 8)

#define RK3588_GRF0_TSADC_CON               0x0100

#define RK3588_GRF0_TSADC_TRM               (0xff0077 << 0)
#define RK3588_GRF0_TSADC_SHUT_2CRU         (0x30003 << 10)
#define RK3588_GRF0_TSADC_SHUT_2GPIO        (0x70007 << 12)

#define GRF_SARADC_TESTBIT_ON               (0x10001 << 2)
#define GRF_TSADC_TESTBIT_H_ON              (0x10001 << 2)
#define GRF_TSADC_VCM_EN_L                  (0x10001 << 7)
#define GRF_TSADC_VCM_EN_H                  (0x10001 << 7)

#define GRF_CON_TSADC_CH_INV                (0x10001 << 1)

#define TEMP_INVALID                        ((int)(RT_UINT32_MAX >> 1))
#define TEMP_SCALE                          1000

/*
 * If the temperature over a period of time High,
 * the resulting TSHUT gave CRU module,let it reset the entire chip,
 * or via GPIO give PMIC.
 */
enum tshut_mode
{
    TSHUT_MODE_CRU = 0,
    TSHUT_MODE_OTP,
    TSHUT_MODE_GPIO,
};

/* The system Temperature Sensors tshut(tshut) polarity */
enum tshut_polarity
{
    TSHUT_LOW_ACTIVE = 0,
    TSHUT_HIGH_ACTIVE,
};

/* The conversion table has the adc value and temperature. */
enum adc_sort_mode
{
    ADC_DECREMENT = 0,  /* the adc value is of diminishing.(e.g. rk3288_code_table) */
    ADC_INCREMENT,      /* the adc value is incremental.(e.g. rk3368_code_table) */
};

struct chip_tsadc_table
{
    const struct tsadc_table *id;
    rt_size_t length;

    rt_uint32_t data_mask;
    enum adc_sort_mode mode;
};

struct rockchip_tsadc_chip
{
    /* The sensor id of chip correspond to the ADC channel */
    int chn_offset;
    int chn_num;
    const char * const *chn_name;

    /* The hardware-controlled tshut property */
    int tshut_temp;
    enum tshut_mode tshut_mode;
    enum tshut_polarity tshut_polarity;

    /* Chip-wide methods */
    void (*initialize)(struct rt_syscon *grf, void *reg, enum tshut_polarity p);
    void (*irq_ack)(void *reg);
    void (*control)(void *reg, rt_bool_t on);

    /* Per-sensor methods */
    rt_err_t (*get_temp)(const struct chip_tsadc_table *table, int chn, void *reg, int *temp);
    rt_err_t (*set_alarm_temp)(const struct chip_tsadc_table *table, int chn, void *reg, int temp);
    rt_err_t (*set_tshut_temp)(const struct chip_tsadc_table *table, int chn, void *reg, int temp);
    void (*set_tshut_mode)(int chn, void *reg, enum tshut_mode m);

    /* Per-table methods */
    struct chip_tsadc_table table;
};

struct tsadc_table
{
    rt_uint32_t code;   /* the value of adc channel */
    int temp;           /* the temperature */
};

struct rockchip_tsadc;

struct rockchip_tsadc_channel
{
    struct rt_thermal_zone_device parent;

    int id;
    struct rockchip_tsadc *rk_tsadc;
};
#define raw_to_rockchip_tsadc_channel(raw) rt_container_of(raw, struct rockchip_tsadc_channel, parent)

struct rockchip_tsadc
{
    int irq;
    void *regs;
    struct rt_syscon *grf;

    struct rt_clk *clk;
    struct rt_clk *pclk;

    struct rt_reset_control *rstc;

    int tshut_temp;
    enum tshut_mode tshut_mode;
    enum tshut_polarity tshut_polarity;

    const struct rockchip_tsadc_chip *chip;
    struct rockchip_tsadc_channel channels[0];
};

static rt_uint32_t rk_tsadcv2_temp_to_code(const struct chip_tsadc_table *table,
        int temp)
{
    rt_ubase_t num;
    rt_uint32_t denom, error = table->data_mask;
    int high = (table->length - 1) - 1, low = 0, mid = (high + low) / 2;

    /* Return mask code data when the temp is over table range */
    if (temp < table->id[low].temp || temp > table->id[high].temp)
    {
        goto _exit;
    }

    while (low <= high)
    {
        if (temp == table->id[mid].temp)
        {
            return table->id[mid].code;
        }
        else if (temp < table->id[mid].temp)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }

        mid = (low + high) / 2;
    }

    /*
     * The conversion code granularity provided by the table. Let's
     * assume that the relationship between temperature and
     * analog value between 2 table entries is linear and interpolate
     * to produce less granular result.
     */
    num = rt_abs(table->id[mid + 1].code - table->id[mid].code);
    num *= temp - table->id[mid].temp;
    denom = table->id[mid + 1].temp - table->id[mid].temp;

    switch (table->mode)
    {
    case ADC_DECREMENT:
        return table->id[mid].code - (num / denom);

    case ADC_INCREMENT:
        return table->id[mid].code + (num / denom);

    default:
        LOG_E("Temp to Code: unknown table mode: %d", table->mode);

        return error;
    }

_exit:
    LOG_E("Temp to Code: invalid temperature, temp = %d error = %d", temp, error);

    return error;
}

static rt_err_t rk_tsadcv2_code_to_temp(const struct chip_tsadc_table *table,
                   rt_uint32_t code, int *temp)
{
    rt_ubase_t denom;
    rt_uint32_t low = 1, high = table->length - 1, mid = (low + high) / 2, num;

    switch (table->mode)
    {
    case ADC_DECREMENT:
        code &= table->data_mask;

        if (code <= table->id[high].code)
        {
            return -RT_ERROR;
        }

        while (low <= high)
        {
            if (code >= table->id[mid].code && code < table->id[mid - 1].code)
            {
                break;
            }
            else if (code < table->id[mid].code)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }

            mid = (low + high) / 2;
        }
        break;

    case ADC_INCREMENT:
        code &= table->data_mask;

        if (code < table->id[low].code)
        {
            return -RT_ERROR;
        }

        while (low <= high)
        {
            if (code <= table->id[mid].code && code > table->id[mid - 1].code)
            {
                break;
            }
            else if (code > table->id[mid].code)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }

            mid = (low + high) / 2;
        }
        break;

    default:
        LOG_E("Code to Temp: unknown table mode: %d", table->mode);

        return -RT_EINVAL;
    }

    /*
     * The 5C granularity provided by the table is too much. Let's
     * assume that the relationship between sensor readings and
     * temperature between 2 table entries is linear and interpolate
     * to produce less granular result.
     */
    num = table->id[mid].temp - table->id[mid - 1].temp;
    num *= rt_abs(table->id[mid - 1].code - code);
    denom = rt_abs(table->id[mid - 1].code - table->id[mid].code);
    *temp = table->id[mid - 1].temp + (num / denom);

    return 0;
}

/*
 * Initialize TASDC Controller.
 *
 * (1) Set TSADC_V2_AUTO_PERIOD:
 *     Configure the interleave between every two accessing of
 *     TSADC in normal operation.
 *
 * (2) Set TSADCV2_AUTO_PERIOD_HT:
 *     Configure the interleave between every two accessing of
 *     TSADC after the temperature is higher than COM_SHUT or COM_INT.
 *
 * (3) Set TSADCV2_HIGH_INT_DEBOUNCE and TSADC_HIGHT_TSHUT_DEBOUNCE:
 *     If the temperature is higher than COMP_INT or COMP_SHUT for
 *     "debounce" times, TSADC controller will generate interrupt or TSHUT.
 */
static void rk_tsadcv2_initialize(struct rt_syscon *grf, void *regs,
        enum tshut_polarity tshut_polarity)
{
    if (tshut_polarity == TSHUT_HIGH_ACTIVE)
    {
        HWREG32(regs + TSADCV2_AUTO_CON) = 0U | TSADCV2_AUTO_TSHUT_POLARITY_HIGH;
    }
    else
    {
        HWREG32(regs + TSADCV2_AUTO_CON) = 0U & ~TSADCV2_AUTO_TSHUT_POLARITY_HIGH;
    }

    HWREG32(regs + TSADCV2_AUTO_PERIOD) = TSADCV2_AUTO_PERIOD_TIME;
    HWREG32(regs + TSADCV2_HIGHT_INT_DEBOUNCE) = TSADCV2_HIGHT_INT_DEBOUNCE_COUNT;
    HWREG32(regs + TSADCV2_AUTO_PERIOD_HT) = TSADCV2_AUTO_PERIOD_HT_TIME;
    HWREG32(regs + TSADCV2_HIGHT_TSHUT_DEBOUNCE) = TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT;
}

/*
 * Initialize TASDC Controller.
 * (1) The tsadc control power sequence.
 *
 * (2) Set TSADC_V2_AUTO_PERIOD:
 *     Configure the interleave between every two accessing of
 *     TSADC in normal operation.
 *
 * (2) Set TSADCV2_AUTO_PERIOD_HT:
 *     Configure the interleave between every two accessing of
 *     TSADC after the temperature is higher than COM_SHUT or COM_INT.
 *
 * (3) Set TSADCV2_HIGH_INT_DEBOUNCE and TSADC_HIGHT_TSHUT_DEBOUNCE:
 *     If the temperature is higher than COMP_INT or COMP_SHUT for
 *     "debounce" times, TSADC controller will generate interrupt or TSHUT.
 */
static void rk_tsadcv3_initialize(struct rt_syscon *grf, void *regs,
        enum tshut_polarity tshut_polarity)
{
    /* The tsadc control power sequence */
    if (!grf)
    {
        /* Set interleave value to workround ic time sync issue */
        HWREG32(regs + TSADCV2_USER_CON) = TSADCV2_USER_INTER_PD_SOC;
        HWREG32(regs + TSADCV2_AUTO_PERIOD) = TSADCV2_AUTO_PERIOD_TIME;
        HWREG32(regs + TSADCV2_HIGHT_INT_DEBOUNCE) = TSADCV2_HIGHT_INT_DEBOUNCE_COUNT;
        HWREG32(regs + TSADCV2_AUTO_PERIOD_HT) = TSADCV2_AUTO_PERIOD_HT_TIME;
        HWREG32(regs + TSADCV2_HIGHT_TSHUT_DEBOUNCE) = TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT;

    }
    else
    {
        /* Enable the voltage common mode feature */
        rt_syscon_write(grf, GRF_TSADC_TESTBIT_L, GRF_TSADC_VCM_EN_L);
        rt_syscon_write(grf, GRF_TSADC_TESTBIT_H, GRF_TSADC_VCM_EN_H);
        rt_hw_us_delay(15);

        rt_syscon_write(grf, GRF_SARADC_TESTBIT, GRF_SARADC_TESTBIT_ON);
        rt_syscon_write(grf, GRF_TSADC_TESTBIT_H, GRF_TSADC_TESTBIT_H_ON);
        rt_hw_us_delay(90);

        HWREG32(regs + TSADCV2_AUTO_PERIOD) = TSADCV3_AUTO_PERIOD_TIME;
        HWREG32(regs + TSADCV2_HIGHT_INT_DEBOUNCE) = TSADCV2_HIGHT_INT_DEBOUNCE_COUNT;
        HWREG32(regs + TSADCV2_AUTO_PERIOD_HT) = TSADCV3_AUTO_PERIOD_HT_TIME;
        HWREG32(regs + TSADCV2_HIGHT_TSHUT_DEBOUNCE) = TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT;
    }

    if (tshut_polarity == TSHUT_HIGH_ACTIVE)
    {
        HWREG32(regs + TSADCV2_AUTO_CON) = 0U | TSADCV2_AUTO_TSHUT_POLARITY_HIGH;
    }
    else
    {
        HWREG32(regs + TSADCV2_AUTO_CON) = 0U & ~TSADCV2_AUTO_TSHUT_POLARITY_HIGH;
    }
}

static void rk_tsadcv4_initialize(struct rt_syscon *grf, void *regs,
        enum tshut_polarity tshut_polarity)
{
    rk_tsadcv2_initialize(grf, regs, tshut_polarity);

    rt_syscon_write(grf, PX30_GRF_SOC_CON2, GRF_CON_TSADC_CH_INV);
}

static void rk_tsadcv7_initialize(struct rt_syscon *grf, void *regs,
        enum tshut_polarity tshut_polarity)
{
    HWREG32(regs + TSADCV2_USER_CON) = TSADCV5_USER_INTER_PD_SOC;
    HWREG32(regs + TSADCV2_AUTO_PERIOD) = TSADCV5_AUTO_PERIOD_TIME;
    HWREG32(regs + TSADCV2_HIGHT_INT_DEBOUNCE) = TSADCV2_HIGHT_INT_DEBOUNCE_COUNT;
    HWREG32(regs + TSADCV2_AUTO_PERIOD_HT) = TSADCV5_AUTO_PERIOD_HT_TIME;
    HWREG32(regs + TSADCV2_HIGHT_TSHUT_DEBOUNCE) = TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT;

    if (tshut_polarity == TSHUT_HIGH_ACTIVE)
    {
        HWREG32(regs + TSADCV2_AUTO_CON) = 0U | TSADCV2_AUTO_TSHUT_POLARITY_HIGH;
    }
    else
    {
        HWREG32(regs + TSADCV2_AUTO_CON) = 0U & ~TSADCV2_AUTO_TSHUT_POLARITY_HIGH;
    }

    /* The general register file will is optional and might not be available. */
    if (grf)
    {
        rt_syscon_write(grf, RK3568_GRF_TSADC_CON, RK3568_GRF_TSADC_TSEN);
        rt_hw_us_delay(15);

        rt_syscon_write(grf, RK3568_GRF_TSADC_CON, RK3568_GRF_TSADC_ANA_REG0);
        rt_syscon_write(grf, RK3568_GRF_TSADC_CON, RK3568_GRF_TSADC_ANA_REG1);
        rt_syscon_write(grf, RK3568_GRF_TSADC_CON, RK3568_GRF_TSADC_ANA_REG2);
        rt_hw_us_delay(100);
    }
}

static void rk_tsadcv8_initialize(struct rt_syscon *grf, void *regs,
        enum tshut_polarity tshut_polarity)
{
    HWREG32(regs + TSADCV3_AUTO_PERIOD) = TSADCV6_AUTO_PERIOD_TIME;
    HWREG32(regs + TSADCV3_AUTO_PERIOD_HT) = TSADCV6_AUTO_PERIOD_HT_TIME;
    HWREG32(regs + TSADCV3_HIGHT_INT_DEBOUNCE) = TSADCV2_HIGHT_INT_DEBOUNCE_COUNT;
    HWREG32(regs + TSADCV3_HIGHT_TSHUT_DEBOUNCE) = TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT;

    if (tshut_polarity == TSHUT_HIGH_ACTIVE)
    {
        HWREG32(regs + TSADCV2_AUTO_CON) = TSADCV2_AUTO_TSHUT_POLARITY_HIGH |
                TSADCV2_AUTO_TSHUT_POLARITY_MASK;
    }
    else
    {
        HWREG32(regs + TSADCV2_AUTO_CON) = TSADCV2_AUTO_TSHUT_POLARITY_MASK;
    }
}

static void rk_tsadcv2_irq_ack(void *regs)
{
    rt_uint32_t val;

    val = HWREG32(regs + TSADCV2_INT_PD);
    HWREG32(regs + TSADCV2_INT_PD) = val & TSADCV2_INT_PD_CLEAR_MASK;
}

static void rk_tsadcv3_irq_ack(void *regs)
{
    rt_uint32_t val;

    val = HWREG32(regs + TSADCV2_INT_PD);
    HWREG32(regs + TSADCV2_INT_PD) = val & TSADCV3_INT_PD_CLEAR_MASK;
}

static void rk_tsadcv4_irq_ack(void *regs)
{
    rt_uint32_t val;

    val = HWREG32(regs + TSADCV3_INT_PD);
    HWREG32(regs + TSADCV3_INT_PD) = val & TSADCV4_INT_PD_CLEAR_MASK;

    val = HWREG32(regs + TSADCV3_HSHUT_PD);
    HWREG32(regs + TSADCV3_HSHUT_PD) = val & TSADCV3_INT_PD_CLEAR_MASK;
}

static void rk_tsadcv2_control(void *regs, rt_bool_t enable)
{
    rt_uint32_t val = HWREG32(regs + TSADCV2_AUTO_CON);

    if (enable)
    {
        val |= TSADCV2_AUTO_EN;
    }
    else
    {
        val &= ~TSADCV2_AUTO_EN;
    }

    HWREG32(regs + TSADCV2_AUTO_CON) = val;
}

/*
 * The tsadc controller is enabled or disabled.
 * NOTE: TSADC controller works at auto mode, and some SoCs need set the
 * tsadc_q_sel bit on TSADCV2_AUTO_CON[1]. The (1024 - tsadc_q) as output
 * adc value if setting this bit to enable.
 */
static void rk_tsadcv3_control(void *regs, rt_bool_t enable)
{
    rt_uint32_t val = HWREG32(regs + TSADCV2_AUTO_CON);

    if (enable)
    {
        val |= TSADCV2_AUTO_EN | TSADCV3_AUTO_Q_SEL_EN;
    }
    else
    {
        val &= ~TSADCV2_AUTO_EN;
    }

    HWREG32(regs + TSADCV2_AUTO_CON) = val;
}

static void rk_tsadcv4_control(void *regs, rt_bool_t enable)
{
    rt_uint32_t val;

    if (enable)
    {
        val = TSADCV2_AUTO_EN | TSADCV2_AUTO_EN_MASK;
    }
    else
    {
        val = TSADCV2_AUTO_EN_MASK;
    }

    HWREG32(regs + TSADCV2_AUTO_CON) = val;
}

static rt_err_t rk_tsadcv2_get_temp(const struct chip_tsadc_table *table,
        int chn, void *regs, int *temp)
{
    rt_uint32_t val = HWREG32(regs + TSADCV2_DATA(chn));

    return rk_tsadcv2_code_to_temp(table, val, temp);
}

static rt_err_t rk_tsadcv4_get_temp(const struct chip_tsadc_table *table,
        int chn, void *regs, int *temp)
{
    rt_uint32_t val = HWREG32(regs + TSADCV3_DATA(chn));

    return rk_tsadcv2_code_to_temp(table, val, temp);
}

static rt_err_t rk_tsadcv2_alarm_temp(const struct chip_tsadc_table *table,
        int chn, void *regs, int temp)
{
    rt_uint32_t alarm_value;
    rt_uint32_t int_en, int_clr;

    /*
     * In some cases, some sensors didn't need the trip points, the
     * set_trips will pass {-INT_MAX, INT_MAX} to trigger tsadc alarm
     * in the end, ignore this case and disable the high temperature
     * interrupt.
     */
    if (temp == TEMP_INVALID)
    {
        int_clr = HWREG32(regs + TSADCV2_INT_EN);
        int_clr &= ~TSADCV2_INT_SRC_EN(chn);
        HWREG32(regs + TSADCV2_INT_EN) = int_clr;

        return RT_EOK;
    }

    alarm_value = rk_tsadcv2_temp_to_code(table, temp);

    if (alarm_value == table->data_mask)
    {
        return -RT_EINVAL;
    }

    HWREG32(regs + TSADCV2_COMP_INT(chn)) = alarm_value & table->data_mask;
    int_en = HWREG32(regs + TSADCV2_INT_EN);
    int_en |= TSADCV2_INT_SRC_EN(chn);
    HWREG32(regs + TSADCV2_INT_EN) = int_en;

    return RT_EOK;
}

static rt_err_t rk_tsadcv3_alarm_temp(const struct chip_tsadc_table *table,
        int chn, void *regs, int temp)
{
    rt_uint32_t alarm_value;

    /*
     * In some cases, some sensors didn't need the trip points, the
     * set_trips will pass {-INT_MAX, INT_MAX} to trigger tsadc alarm
     * in the end, ignore this case and disable the high temperature
     * interrupt.
     */
    if (temp == TEMP_INVALID)
    {
        HWREG32(regs + TSADCV3_HT_INT_EN) = TSADCV2_INT_SRC_EN_MASK(chn);

        return RT_EOK;
    }

    alarm_value = rk_tsadcv2_temp_to_code(table, temp);

    if (alarm_value == table->data_mask)
    {
        return -RT_EINVAL;
    }

    HWREG32(regs + TSADCV3_COMP_INT(chn)) = alarm_value & table->data_mask;
    HWREG32(regs + TSADCV3_HT_INT_EN) =
            TSADCV2_INT_SRC_EN(chn) | TSADCV2_INT_SRC_EN_MASK(chn);

    return RT_EOK;
}

static rt_err_t rk_tsadcv2_tshut_temp(const struct chip_tsadc_table *table,
        int chn, void *regs, int temp)
{
    rt_uint32_t val, tshut_value = rk_tsadcv2_temp_to_code(table, temp);

    if (tshut_value == table->data_mask)
    {
        return -RT_EINVAL;
    }

    HWREG32(regs + TSADCV2_COMP_SHUT(chn)) = tshut_value;
    val = HWREG32(regs + TSADCV2_AUTO_CON);
    HWREG32(regs + TSADCV2_AUTO_CON) = val | TSADCV2_AUTO_SRC_EN(chn);

    return RT_EOK;
}

static rt_err_t rk_tsadcv3_tshut_temp(const struct chip_tsadc_table *table,
        int chn, void *regs, int temp)
{
    rt_uint32_t tshut_value = rk_tsadcv2_temp_to_code(table, temp);

    if (tshut_value == table->data_mask)
    {
        return -RT_EINVAL;
    }

    HWREG32(regs + TSADCV3_COMP_SHUT(chn)) = tshut_value;
    HWREG32(regs + TSADCV3_AUTO_SRC_CON) =
            TSADCV3_AUTO_SRC_EN(chn) | TSADCV3_AUTO_SRC_EN_MASK(chn);

    return RT_EOK;
}

static void rk_tsadcv2_tshut_mode(int chn, void *regs, enum tshut_mode mode)
{
    rt_uint32_t val = HWREG32(regs + TSADCV2_INT_EN);

    if (mode == TSHUT_MODE_GPIO)
    {
        val &= ~TSADCV2_SHUT_2CRU_SRC_EN(chn);
        val |= TSADCV2_SHUT_2GPIO_SRC_EN(chn);
    }
    else
    {
        val &= ~TSADCV2_SHUT_2GPIO_SRC_EN(chn);
        val |= TSADCV2_SHUT_2CRU_SRC_EN(chn);
    }

    HWREG32(regs + TSADCV2_INT_EN) = val;
}

static void rk_tsadcv3_tshut_mode(int chn, void *regs, enum tshut_mode mode)
{
    rt_uint32_t val_gpio, val_cru;

    if (mode == TSHUT_MODE_GPIO)
    {
        val_gpio = TSADCV2_INT_SRC_EN(chn) | TSADCV2_INT_SRC_EN_MASK(chn);
        val_cru = TSADCV2_INT_SRC_EN_MASK(chn);
    }
    else
    {
        val_cru = TSADCV2_INT_SRC_EN(chn) | TSADCV2_INT_SRC_EN_MASK(chn);
        val_gpio = TSADCV2_INT_SRC_EN_MASK(chn);
    }

    HWREG32(regs + TSADCV3_HSHUT_GPIO_INT_EN) = val_gpio;
    HWREG32(regs + TSADCV3_HSHUT_CRU_INT_EN) = val_cru;
}

static void rk_tsadcv4_tshut_mode(int chn, void *regs, enum tshut_mode mode)
{
    rt_uint32_t val_gpio, val_cru;

    if (mode == TSHUT_MODE_OTP)
    {
        val_gpio = TSADCV2_INT_SRC_EN(chn) | TSADCV2_INT_SRC_EN_MASK(chn);
        val_cru = TSADCV2_INT_SRC_EN_MASK(chn);
    }
    else
    {
        val_cru = TSADCV2_INT_SRC_EN(chn) | TSADCV2_INT_SRC_EN_MASK(chn);
        val_gpio = TSADCV2_INT_SRC_EN_MASK(chn);
    }

    HWREG32(regs + TSADCV3_HSHUT_GPIO_INT_EN) = val_gpio;
    HWREG32(regs + TSADCV3_HSHUT_CRU_INT_EN) = val_cru;
}

static const struct tsadc_table rk3328_code_table[] =
{
    {   0, -40000 },
    { 296, -40000 },
    { 304, -35000 },
    { 313, -30000 },
    { 331, -20000 },
    { 340, -15000 },
    { 349, -10000 },
    { 359,  -5000 },
    { 368,      0 },
    { 378,   5000 },
    { 388,  10000 },
    { 398,  15000 },
    { 408,  20000 },
    { 418,  25000 },
    { 429,  30000 },
    { 440,  35000 },
    { 451,  40000 },
    { 462,  45000 },
    { 473,  50000 },
    { 485,  55000 },
    { 496,  60000 },
    { 508,  65000 },
    { 521,  70000 },
    { 533,  75000 },
    { 546,  80000 },
    { 559,  85000 },
    { 572,  90000 },
    { 586,  95000 },
    { 600, 100000 },
    { 614, 105000 },
    { 629, 110000 },
    { 644, 115000 },
    { 659, 120000 },
    { 675, 125000 },
    { TSADCV2_DATA_MASK, 125000 },
};

static const char * const chn_name_common[] =
{
    "CPU", "GPU",
};

static const struct rockchip_tsadc_chip px30_tsadc_data =
{
    /* cpu, gpu */
    .chn_offset = 0,
    .chn_num = 2, /* 2 channels for tsadc */
    .chn_name = chn_name_common,

    .tshut_mode = TSHUT_MODE_CRU, /* default TSHUT via CRU */
    .tshut_temp = 95000,

    .initialize = rk_tsadcv4_initialize,
    .irq_ack = rk_tsadcv3_irq_ack,
    .control = rk_tsadcv3_control,
    .get_temp = rk_tsadcv2_get_temp,
    .set_alarm_temp = rk_tsadcv2_alarm_temp,
    .set_tshut_temp = rk_tsadcv2_tshut_temp,
    .set_tshut_mode = rk_tsadcv2_tshut_mode,

    .table =
    {
        .id = rk3328_code_table,
        .length = RT_ARRAY_SIZE(rk3328_code_table),
        .data_mask = TSADCV2_DATA_MASK,
        .mode = ADC_INCREMENT,
    },
};

static const struct tsadc_table rv1108_table[] =
{
    {   0, -40000 },
    { 374, -40000 },
    { 382, -35000 },
    { 389, -30000 },
    { 397, -25000 },
    { 405, -20000 },
    { 413, -15000 },
    { 421, -10000 },
    { 429,  -5000 },
    { 436,      0 },
    { 444,   5000 },
    { 452,  10000 },
    { 460,  15000 },
    { 468,  20000 },
    { 476,  25000 },
    { 483,  30000 },
    { 491,  35000 },
    { 499,  40000 },
    { 507,  45000 },
    { 515,  50000 },
    { 523,  55000 },
    { 531,  60000 },
    { 539,  65000 },
    { 547,  70000 },
    { 555,  75000 },
    { 562,  80000 },
    { 570,  85000 },
    { 578,  90000 },
    { 586,  95000 },
    { 594, 100000 },
    { 602, 105000 },
    { 610, 110000 },
    { 618, 115000 },
    { 626, 120000 },
    { 634, 125000 },
    { TSADCV2_DATA_MASK, 125000 },
};

static const struct rockchip_tsadc_chip rv1108_tsadc_data =
{
    /* cpu */
    .chn_offset = 0,
    .chn_num = 1, /* one channel for tsadc */
    .chn_name = chn_name_common,

    .tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
    .tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
    .tshut_temp = 95000,

    .initialize = rk_tsadcv2_initialize,
    .irq_ack = rk_tsadcv3_irq_ack,
    .control = rk_tsadcv3_control,
    .get_temp = rk_tsadcv2_get_temp,
    .set_alarm_temp = rk_tsadcv2_alarm_temp,
    .set_tshut_temp = rk_tsadcv2_tshut_temp,
    .set_tshut_mode = rk_tsadcv2_tshut_mode,

    .table =
    {
        .id = rv1108_table,
        .length = RT_ARRAY_SIZE(rv1108_table),
        .data_mask = TSADCV2_DATA_MASK,
        .mode = ADC_INCREMENT,
    },
};

static const struct tsadc_table rk3228_code_table[] =
{
    {   0, -40000 },
    { 588, -40000 },
    { 593, -35000 },
    { 598, -30000 },
    { 603, -25000 },
    { 608, -20000 },
    { 613, -15000 },
    { 618, -10000 },
    { 623,  -5000 },
    { 629,      0 },
    { 634,   5000 },
    { 639,  10000 },
    { 644,  15000 },
    { 649,  20000 },
    { 654,  25000 },
    { 660,  30000 },
    { 665,  35000 },
    { 670,  40000 },
    { 675,  45000 },
    { 681,  50000 },
    { 686,  55000 },
    { 691,  60000 },
    { 696,  65000 },
    { 702,  70000 },
    { 707,  75000 },
    { 712,  80000 },
    { 717,  85000 },
    { 723,  90000 },
    { 728,  95000 },
    { 733, 100000 },
    { 738, 105000 },
    { 744, 110000 },
    { 749, 115000 },
    { 754, 120000 },
    { 760, 125000 },
    { TSADCV2_DATA_MASK, 125000 },
};

static const struct rockchip_tsadc_chip rk3228_tsadc_data =
{
    /* cpu */
    .chn_offset = 0,
    .chn_num = 1, /* one channel for tsadc */
    .chn_name = chn_name_common,

    .tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
    .tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
    .tshut_temp = 95000,

    .initialize = rk_tsadcv2_initialize,
    .irq_ack = rk_tsadcv3_irq_ack,
    .control = rk_tsadcv3_control,
    .get_temp = rk_tsadcv2_get_temp,
    .set_alarm_temp = rk_tsadcv2_alarm_temp,
    .set_tshut_temp = rk_tsadcv2_tshut_temp,
    .set_tshut_mode = rk_tsadcv2_tshut_mode,

    .table =
    {
        .id = rk3228_code_table,
        .length = RT_ARRAY_SIZE(rk3228_code_table),
        .data_mask = TSADCV3_DATA_MASK,
        .mode = ADC_INCREMENT,
    },
};

static const struct tsadc_table rk3288_code_table[] =
{
    { TSADCV2_DATA_MASK, -40000 },
    { 3800, -40000 },
    { 3792, -35000 },
    { 3783, -30000 },
    { 3774, -25000 },
    { 3765, -20000 },
    { 3756, -15000 },
    { 3747, -10000 },
    { 3737,  -5000 },
    { 3728,      0 },
    { 3718,   5000 },
    { 3708,  10000 },
    { 3698,  15000 },
    { 3688,  20000 },
    { 3678,  25000 },
    { 3667,  30000 },
    { 3656,  35000 },
    { 3645,  40000 },
    { 3634,  45000 },
    { 3623,  50000 },
    { 3611,  55000 },
    { 3600,  60000 },
    { 3588,  65000 },
    { 3575,  70000 },
    { 3563,  75000 },
    { 3550,  80000 },
    { 3537,  85000 },
    { 3524,  90000 },
    { 3510,  95000 },
    { 3496, 100000 },
    { 3482, 105000 },
    { 3467, 110000 },
    { 3452, 115000 },
    { 3437, 120000 },
    { 3421, 125000 },
    {    0, 125000 },
};

static const struct rockchip_tsadc_chip rk3288_tsadc_data =
{
    /* cpu, gpu */
    .chn_offset = 1,
    .chn_num = 2, /* two channels for tsadc */
    .chn_name = chn_name_common,

    .tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
    .tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
    .tshut_temp = 95000,

    .initialize = rk_tsadcv2_initialize,
    .irq_ack = rk_tsadcv2_irq_ack,
    .control = rk_tsadcv2_control,
    .get_temp = rk_tsadcv2_get_temp,
    .set_alarm_temp = rk_tsadcv2_alarm_temp,
    .set_tshut_temp = rk_tsadcv2_tshut_temp,
    .set_tshut_mode = rk_tsadcv2_tshut_mode,

    .table =
    {
        .id = rk3288_code_table,
        .length = RT_ARRAY_SIZE(rk3288_code_table),
        .data_mask = TSADCV2_DATA_MASK,
        .mode = ADC_DECREMENT,
    },
};

static const struct rockchip_tsadc_chip rk3308_tsadc_data =
{
    /* cpu, gpu */
    .chn_offset = 0,
    .chn_num = 2, /* two channels for tsadc */
    .chn_name = chn_name_common,

    .tshut_mode = TSHUT_MODE_CRU, /* default TSHUT via CRU */
    .tshut_temp = 95000,

    .initialize = rk_tsadcv2_initialize,
    .irq_ack = rk_tsadcv3_irq_ack,
    .control = rk_tsadcv3_control,
    .get_temp = rk_tsadcv2_get_temp,
    .set_alarm_temp = rk_tsadcv2_alarm_temp,
    .set_tshut_temp = rk_tsadcv2_tshut_temp,
    .set_tshut_mode = rk_tsadcv2_tshut_mode,

    .table =
    {
        .id = rk3328_code_table,
        .length = RT_ARRAY_SIZE(rk3328_code_table),
        .data_mask = TSADCV2_DATA_MASK,
        .mode = ADC_INCREMENT,
    },
};

static const struct rockchip_tsadc_chip rk3328_tsadc_data =
{
    /* cpu */
    .chn_offset = 0,
    .chn_num = 1, /* one channels for tsadc */
    .chn_name = chn_name_common,

    .tshut_mode = TSHUT_MODE_CRU, /* default TSHUT via CRU */
    .tshut_temp = 95000,

    .initialize = rk_tsadcv2_initialize,
    .irq_ack = rk_tsadcv3_irq_ack,
    .control = rk_tsadcv3_control,
    .get_temp = rk_tsadcv2_get_temp,
    .set_alarm_temp = rk_tsadcv2_alarm_temp,
    .set_tshut_temp = rk_tsadcv2_tshut_temp,
    .set_tshut_mode = rk_tsadcv2_tshut_mode,

    .table =
    {
        .id = rk3328_code_table,
        .length = RT_ARRAY_SIZE(rk3328_code_table),
        .data_mask = TSADCV2_DATA_MASK,
        .mode = ADC_INCREMENT,
    },
};

static const struct rockchip_tsadc_chip rk3366_tsadc_data =
{
    /* cpu, gpu */
    .chn_offset = 0,
    .chn_num = 2, /* two channels for tsadc */
    .chn_name = chn_name_common,

    .tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
    .tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
    .tshut_temp = 95000,

    .initialize = rk_tsadcv3_initialize,
    .irq_ack = rk_tsadcv3_irq_ack,
    .control = rk_tsadcv3_control,
    .get_temp = rk_tsadcv2_get_temp,
    .set_alarm_temp = rk_tsadcv2_alarm_temp,
    .set_tshut_temp = rk_tsadcv2_tshut_temp,
    .set_tshut_mode = rk_tsadcv2_tshut_mode,

    .table =
    {
        .id = rk3228_code_table,
        .length = RT_ARRAY_SIZE(rk3228_code_table),
        .data_mask = TSADCV3_DATA_MASK,
        .mode = ADC_INCREMENT,
    },
};

static const struct tsadc_table rk3368_code_table[] =
{
    {   0, -40000 },
    { 106, -40000 },
    { 108, -35000 },
    { 110, -30000 },
    { 112, -25000 },
    { 114, -20000 },
    { 116, -15000 },
    { 118, -10000 },
    { 120,  -5000 },
    { 122,      0 },
    { 124,   5000 },
    { 126,  10000 },
    { 128,  15000 },
    { 130,  20000 },
    { 132,  25000 },
    { 134,  30000 },
    { 136,  35000 },
    { 138,  40000 },
    { 140,  45000 },
    { 142,  50000 },
    { 144,  55000 },
    { 146,  60000 },
    { 148,  65000 },
    { 150,  70000 },
    { 152,  75000 },
    { 154,  80000 },
    { 156,  85000 },
    { 158,  90000 },
    { 160,  95000 },
    { 162, 100000 },
    { 163, 105000 },
    { 165, 110000 },
    { 167, 115000 },
    { 169, 120000 },
    { 171, 125000 },
    { TSADCV3_DATA_MASK, 125000 },
};

static const struct rockchip_tsadc_chip rk3368_tsadc_data =
{
    /* cpu, gpu */
    .chn_offset = 0,
    .chn_num = 2, /* two channels for tsadc */
    .chn_name = chn_name_common,

    .tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
    .tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
    .tshut_temp = 95000,

    .initialize = rk_tsadcv2_initialize,
    .irq_ack = rk_tsadcv2_irq_ack,
    .control = rk_tsadcv2_control,
    .get_temp = rk_tsadcv2_get_temp,
    .set_alarm_temp = rk_tsadcv2_alarm_temp,
    .set_tshut_temp = rk_tsadcv2_tshut_temp,
    .set_tshut_mode = rk_tsadcv2_tshut_mode,

    .table =
    {
        .id = rk3368_code_table,
        .length = RT_ARRAY_SIZE(rk3368_code_table),
        .data_mask = TSADCV3_DATA_MASK,
        .mode = ADC_INCREMENT,
    },
};

static const struct tsadc_table rk3399_code_table[] =
{
    {   0, -40000 },
    { 402, -40000 },
    { 410, -35000 },
    { 419, -30000 },
    { 427, -25000 },
    { 436, -20000 },
    { 444, -15000 },
    { 453, -10000 },
    { 461,  -5000 },
    { 470,      0 },
    { 478,   5000 },
    { 487,  10000 },
    { 496,  15000 },
    { 504,  20000 },
    { 513,  25000 },
    { 521,  30000 },
    { 530,  35000 },
    { 538,  40000 },
    { 547,  45000 },
    { 555,  50000 },
    { 564,  55000 },
    { 573,  60000 },
    { 581,  65000 },
    { 590,  70000 },
    { 599,  75000 },
    { 607,  80000 },
    { 616,  85000 },
    { 624,  90000 },
    { 633,  95000 },
    { 642, 100000 },
    { 650, 105000 },
    { 659, 110000 },
    { 668, 115000 },
    { 677, 120000 },
    { 685, 125000 },
    { TSADCV3_DATA_MASK, 125000 },
};

static const struct rockchip_tsadc_chip rk3399_tsadc_data =
{
    /* cpu, gpu */
    .chn_offset = 0,
    .chn_num = 2, /* two channels for tsadc */
    .chn_name = chn_name_common,

    .tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
    .tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
    .tshut_temp = 95000,

    .initialize = rk_tsadcv3_initialize,
    .irq_ack = rk_tsadcv3_irq_ack,
    .control = rk_tsadcv3_control,
    .get_temp = rk_tsadcv2_get_temp,
    .set_alarm_temp = rk_tsadcv2_alarm_temp,
    .set_tshut_temp = rk_tsadcv2_tshut_temp,
    .set_tshut_mode = rk_tsadcv2_tshut_mode,

    .table =
    {
        .id = rk3399_code_table,
        .length = RT_ARRAY_SIZE(rk3399_code_table),
        .data_mask = TSADCV3_DATA_MASK,
        .mode = ADC_INCREMENT,
    },
};

static const struct tsadc_table rk3568_code_table[] =
{
    {    0, -40000 },
    { 1584, -40000 },
    { 1620, -35000 },
    { 1652, -30000 },
    { 1688, -25000 },
    { 1720, -20000 },
    { 1756, -15000 },
    { 1788, -10000 },
    { 1824,  -5000 },
    { 1856,      0 },
    { 1892,   5000 },
    { 1924,  10000 },
    { 1956,  15000 },
    { 1992,  20000 },
    { 2024,  25000 },
    { 2060,  30000 },
    { 2092,  35000 },
    { 2128,  40000 },
    { 2160,  45000 },
    { 2196,  50000 },
    { 2228,  55000 },
    { 2264,  60000 },
    { 2300,  65000 },
    { 2332,  70000 },
    { 2368,  75000 },
    { 2400,  80000 },
    { 2436,  85000 },
    { 2468,  90000 },
    { 2500,  95000 },
    { 2536, 100000 },
    { 2572, 105000 },
    { 2604, 110000 },
    { 2636, 115000 },
    { 2672, 120000 },
    { 2704, 125000 },
    { TSADCV2_DATA_MASK, 125000 },
};

static const struct rockchip_tsadc_chip rk3568_tsadc_data =
{
    /* cpu, gpu */
    .chn_offset = 0,
    .chn_num = 2, /* two channels for tsadc */
    .chn_name = chn_name_common,

    .tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
    .tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
    .tshut_temp = 95000,

    .initialize = rk_tsadcv7_initialize,
    .irq_ack = rk_tsadcv3_irq_ack,
    .control = rk_tsadcv3_control,
    .get_temp = rk_tsadcv2_get_temp,
    .set_alarm_temp = rk_tsadcv2_alarm_temp,
    .set_tshut_temp = rk_tsadcv2_tshut_temp,
    .set_tshut_mode = rk_tsadcv2_tshut_mode,

    .table =
    {
        .id = rk3568_code_table,
        .length = RT_ARRAY_SIZE(rk3568_code_table),
        .data_mask = TSADCV2_DATA_MASK,
        .mode = ADC_INCREMENT,
    },
};

static const struct tsadc_table rk3588_code_table[] =
{
    {   0, -40000 },
    { 215, -40000 },
    { 285,  25000 },
    { 350,  85000 },
    { 395, 125000 },
    { TSADCV4_DATA_MASK, 125000 },
};

static const char * const chn_name_rk3588[] =
{
    "Top", "Big Core0", "Big Core1", "Little Core", "Center", "GPU", "NPU",
};

static const struct rockchip_tsadc_chip rk3588_tsadc_data =
{
    /* top, big_core0, big_core1, little_core, center, gpu, npu */
    .chn_offset = 0,
    .chn_num = 7, /* seven channels for tsadc */
    .chn_name = chn_name_rk3588,

    .tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
    .tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
    .tshut_temp = 95000,
    .initialize = rk_tsadcv8_initialize,
    .irq_ack = rk_tsadcv4_irq_ack,
    .control = rk_tsadcv4_control,
    .get_temp = rk_tsadcv4_get_temp,
    .set_alarm_temp = rk_tsadcv3_alarm_temp,
    .set_tshut_temp = rk_tsadcv3_tshut_temp,
    .set_tshut_mode = rk_tsadcv3_tshut_mode,
    .table =
    {
        .id = rk3588_code_table,
        .length = RT_ARRAY_SIZE(rk3588_code_table),
        .data_mask = TSADCV4_DATA_MASK,
        .mode = ADC_INCREMENT,
    },
};

static const char * const chn_name_rk3576[] =
{
    "Top", "Big Core", "Little Core", "DDR", "NPU", "GPU",
};

static const struct rockchip_tsadc_chip rk3576_tsadc_data =
{
    /* top, big_core, little_core, ddr, npu, gpu */
    .chn_num = 6, /* six channels for tsadc */
    .chn_name = chn_name_rk3576,

    .tshut_mode = TSHUT_MODE_OTP, /* default TSHUT via GPIO give PMIC */
    .tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
    .tshut_temp = 95000,
    .initialize = rk_tsadcv8_initialize,
    .irq_ack = rk_tsadcv4_irq_ack,
    .control = rk_tsadcv4_control,
    .get_temp = rk_tsadcv4_get_temp,
    .set_alarm_temp = rk_tsadcv3_alarm_temp,
    .set_tshut_temp = rk_tsadcv3_tshut_temp,
    .set_tshut_mode = rk_tsadcv4_tshut_mode,
    .table =
    {
        .id = rk3588_code_table,
        .length = RT_ARRAY_SIZE(rk3588_code_table),
        .data_mask = TSADCV4_DATA_MASK,
        .mode = ADC_INCREMENT,
    },
};

static rt_err_t rk_tsadc_thermal_zone_get_temp(struct rt_thermal_zone_device *zdev,
        int *out_temp)
{
    struct rockchip_tsadc *rk_tsadc;
    const struct rockchip_tsadc_chip *chip;
    struct rockchip_tsadc_channel *channel = raw_to_rockchip_tsadc_channel(zdev);

    rk_tsadc = channel->rk_tsadc;
    chip = rk_tsadc->chip;

    return chip->get_temp(&chip->table, channel->id, rk_tsadc->regs, out_temp);
}

static rt_err_t rk_tsadc_thermal_zone_set_trips(struct rt_thermal_zone_device *zdev,
        int low_temp, int high_temp)
{
    struct rockchip_tsadc *rk_tsadc;
    const struct rockchip_tsadc_chip *chip;
    struct rockchip_tsadc_channel *channel = raw_to_rockchip_tsadc_channel(zdev);

    rk_tsadc = channel->rk_tsadc;
    chip = rk_tsadc->chip;

    LOG_D("Channel[%d]<%s> set trip alarm %d ~ %d",
            zdev->zone_id,
            chip->chn_name[zdev->zone_id - chip->chn_offset],
            low_temp, high_temp);

    return chip->set_alarm_temp(&rk_tsadc->chip->table, channel->id, rk_tsadc->regs, high_temp);
}

const static struct rt_thermal_zone_ops rk_tsadc_thermal_zone_ops =
{
    .get_temp = rk_tsadc_thermal_zone_get_temp,
    .set_trips = rk_tsadc_thermal_zone_set_trips,
};

static void rk_tsadc_isr(int irqno, void *param)
{
    struct rockchip_tsadc *rk_tsadc = param;
    const struct rockchip_tsadc_chip *chip = rk_tsadc->chip;

    chip->irq_ack(rk_tsadc->regs);

    for (int i = 0; i < chip->chn_num; ++i)
    {
        struct rockchip_tsadc_channel *channel = &rk_tsadc->channels[i];

        rt_thermal_zone_device_update(&channel->parent, RT_THERMAL_MSG_EVENT_UNSPECIFIED);
    }
}

static rt_err_t rockchip_tsadc_parse_ofw(struct rt_device *dev,
        struct rockchip_tsadc *rk_tsadc)
{
    struct rt_ofw_node *np = dev->ofw_node;
    rt_uint32_t shut_temp, tshut_mode, tshut_polarity;

    if (rt_ofw_prop_read_u32(np, "rockchip,hw-tshut-temp", &shut_temp))
    {
        rk_tsadc->tshut_temp = rk_tsadc->chip->tshut_temp;
    }
    else
    {
        if (shut_temp > TEMP_INVALID)
        {
            LOG_E("Invalid tshut temperature specified: %d", shut_temp);

            return -RT_EINVAL;
        }

        rk_tsadc->tshut_temp = shut_temp;
    }

    if (rt_ofw_prop_read_u32(np, "rockchip,hw-tshut-mode", &tshut_mode))
    {
        LOG_W("Missing tshut mode property, using default (%s)",
                rk_tsadc->chip->tshut_mode == TSHUT_MODE_GPIO ? "gpio" : "cru");

        rk_tsadc->tshut_mode = rk_tsadc->chip->tshut_mode;
    }
    else
    {
        rk_tsadc->tshut_mode = tshut_mode;
    }

    if (rk_tsadc->tshut_mode > 1)
    {
        LOG_E("Invalid tshut mode specified: %d", rk_tsadc->tshut_mode);

        return -RT_EINVAL;
    }

    if (rt_ofw_prop_read_u32(np, "rockchip,hw-tshut-polarity", &tshut_polarity))
    {
        LOG_W("Missing tshut-polarity property, using default (%s)",
                rk_tsadc->chip->tshut_polarity == TSHUT_LOW_ACTIVE ? "low" : "high");

        rk_tsadc->tshut_polarity = rk_tsadc->chip->tshut_polarity;
    }
    else
    {
        rk_tsadc->tshut_polarity = tshut_polarity;
    }

    if (rk_tsadc->tshut_polarity > 1)
    {
        LOG_E("Invalid tshut-polarity specified: %d", rk_tsadc->tshut_polarity);

        return -RT_EINVAL;
    }

    rk_tsadc->grf = rt_syscon_find_by_ofw_phandle(np, "rockchip,grf");

    if (!rk_tsadc->grf)
    {
        LOG_W("Missing %s property", "rockchip,grf");
    }

    return RT_EOK;
}

static void rockchip_tsadc_reset_controller(struct rockchip_tsadc *rk_tsadc)
{
    rt_reset_control_assert(rk_tsadc->rstc);
    rt_hw_us_delay(15);
    rt_reset_control_deassert(rk_tsadc->rstc);
}

static void rockchip_tsadc_free(struct rockchip_tsadc *rk_tsadc)
{
    if (!rt_is_err_or_null(rk_tsadc->rstc))
    {
        rt_reset_control_assert(rk_tsadc->rstc);
        rt_reset_control_put(rk_tsadc->rstc);
    }

    if (!rt_is_err_or_null(rk_tsadc->clk))
    {
        rt_clk_disable(rk_tsadc->clk);
        rt_clk_put(rk_tsadc->clk);
    }

    if (!rt_is_err_or_null(rk_tsadc->pclk))
    {
        rt_clk_disable(rk_tsadc->pclk);
        rt_clk_put(rk_tsadc->pclk);
    }

    rt_free(rk_tsadc);
}

static rt_err_t rockchip_tsadc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const struct chip_tsadc_table *table;
    struct rt_device *dev = &pdev->parent;
    const struct rockchip_tsadc_chip *chip = pdev->id->data;
    struct rockchip_tsadc *rk_tsadc = rt_calloc(1, sizeof(*rk_tsadc) +
            sizeof(rk_tsadc->channels[0]) * chip->chn_num);

    if (!rk_tsadc)
    {
        return -RT_ENOMEM;
    }

    rk_tsadc->chip = chip;
    table = &rk_tsadc->chip->table;
    rk_tsadc->irq = rt_dm_dev_get_irq(dev, 0);

    if (rk_tsadc->irq < 0)
    {
        err = rk_tsadc->irq;
        goto _fail;
    }

    rk_tsadc->regs = rt_dm_dev_iomap(dev, 0);

    if (!rk_tsadc->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rk_tsadc->rstc = rt_reset_control_get_array(dev);

    if (rt_is_err(rk_tsadc->rstc))
    {
        err = rt_ptr_err(rk_tsadc->rstc);
        goto _fail;
    }

    rockchip_tsadc_reset_controller(rk_tsadc);

    rk_tsadc->clk = rt_clk_get_by_name(dev, "tsadc");

    if (rt_is_err(rk_tsadc->clk))
    {
        err = rt_ptr_err(rk_tsadc->clk);
        goto _fail;
    }

    rk_tsadc->pclk = rt_clk_get_by_name(dev, "apb_pclk");

    if (rt_is_err(rk_tsadc->pclk))
    {
        err = rt_ptr_err(rk_tsadc->pclk);
        goto _fail;
    }

    if ((err = rt_clk_enable(rk_tsadc->clk)))
    {
        goto _fail;
    }

    if ((err = rt_clk_enable(rk_tsadc->pclk)))
    {
        goto _fail;
    }

    if ((err = rockchip_tsadc_parse_ofw(dev, rk_tsadc)))
    {
        goto _fail;
    }

    rk_tsadc->chip->initialize(rk_tsadc->grf, rk_tsadc->regs, rk_tsadc->tshut_polarity);

    for (int i = 0; i < rk_tsadc->chip->chn_num; ++i)
    {
        struct rockchip_tsadc_channel *channel = &rk_tsadc->channels[i];
        struct rt_thermal_zone_device *tz = &channel->parent;

        tz->zone_id = chip->chn_offset + i;
        channel->id = tz->zone_id;
        channel->rk_tsadc = rk_tsadc;

        chip->set_tshut_mode(channel->id, rk_tsadc->regs, rk_tsadc->tshut_mode);
        chip->set_tshut_temp(table, channel->id, rk_tsadc->regs, rk_tsadc->tshut_temp);

        tz->ops = &rk_tsadc_thermal_zone_ops;
        tz->parent.ofw_node = dev->ofw_node;

        rt_dm_dev_set_name(&tz->parent, "tsadc-%s", rk_tsadc->chip->chn_name[i]);

        rt_thermal_zone_device_register(tz);
    }

    rk_tsadc->chip->control(rk_tsadc->regs, RT_TRUE);

    rt_hw_interrupt_install(rk_tsadc->irq, rk_tsadc_isr, rk_tsadc, "tsadc");
    rt_hw_interrupt_umask(rk_tsadc->irq);

    dev->user_data = rk_tsadc;

    return RT_EOK;

_fail:
    rockchip_tsadc_free(rk_tsadc);

    return err;
}

static rt_err_t rockchip_tsadc_remove(struct rt_platform_device *pdev)
{
    struct rockchip_tsadc *rk_tsadc = pdev->parent.user_data;

    for (int i = 0; i < rk_tsadc->chip->chn_num; ++i)
    {
        struct rockchip_tsadc_channel *channel = &rk_tsadc->channels[i];

        rt_thermal_zone_device_unregister(&channel->parent);
    }

    rockchip_tsadc_free(rk_tsadc);

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_tsadc_ofw_ids[] =
{
    { .compatible = "rockchip,px30-tsadc", .data = &px30_tsadc_data, },
    { .compatible = "rockchip,rv1108-tsadc", .data = &rv1108_tsadc_data, },
    { .compatible = "rockchip,rk3228-tsadc", .data = &rk3228_tsadc_data, },
    { .compatible = "rockchip,rk3288-tsadc", .data = &rk3288_tsadc_data, },
    { .compatible = "rockchip,rk3308-tsadc", .data = &rk3308_tsadc_data, },
    { .compatible = "rockchip,rk3328-tsadc", .data = &rk3328_tsadc_data, },
    { .compatible = "rockchip,rk3366-tsadc", .data = &rk3366_tsadc_data, },
    { .compatible = "rockchip,rk3368-tsadc", .data = &rk3368_tsadc_data, },
    { .compatible = "rockchip,rk3399-tsadc", .data = &rk3399_tsadc_data, },
    { .compatible = "rockchip,rk3568-tsadc", .data = &rk3568_tsadc_data, },
    { .compatible = "rockchip,rk3576-tsadc", .data = &rk3576_tsadc_data, },
    { .compatible = "rockchip,rk3588-tsadc", .data = &rk3588_tsadc_data, },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_tsadc_driver =
{
    .name = "rockchip-tsadc",
    .ids = rockchip_tsadc_ofw_ids,

    .probe = rockchip_tsadc_probe,
    .remove = rockchip_tsadc_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_tsadc_driver);
