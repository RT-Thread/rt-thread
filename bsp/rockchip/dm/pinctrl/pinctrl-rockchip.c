/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pinctrl.rockchip"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "pinctrl-rockchip.h"

#define WRITE_MASK_VAL(h, l, v) \
    (RT_GENMASK(((h) + 16), ((l) + 16)) | (((v) << (l)) & RT_GENMASK((h), (l))))

/*
 * Encode variants of iomux registers into a type variable
 */
#define IOMUX_GPIO_ONLY     RT_BIT(0)
#define IOMUX_WIDTH_4BIT    RT_BIT(1)
#define IOMUX_SOURCE_PMU    RT_BIT(2)
#define IOMUX_UNROUTED      RT_BIT(3)
#define IOMUX_WIDTH_3BIT    RT_BIT(4)
#define IOMUX_WIDTH_2BIT    RT_BIT(5)
#define IOMUX_L_SOURCE_PMU  RT_BIT(6)

#define PIN_BANK_IOMUX_FLAGS(ID, PINS,      \
    LABEL, IOM0, IOM1, IOM2, IOM3)          \
{                                           \
    .bank_num   = ID,                       \
    .nr_pins    = PINS,                     \
    .name       = LABEL,                    \
    .iomux      =                           \
    {                                       \
        { .type  = IOM0, .offset = -1 },    \
        { .type  = IOM1, .offset = -1 },    \
        { .type  = IOM2, .offset = -1 },    \
        { .type  = IOM3, .offset = -1 },    \
    },                                      \
}

#define PIN_BANK_MUX_ROUTE_FLAGS(   \
    ID, PIN, FUNC, REG, VAL, FLAG)  \
{                                   \
    .bank_num   = ID,               \
    .pin        = PIN,              \
    .func       = FUNC,             \
    .route_offset   = REG,          \
    .route_val  = VAL,              \
    .route_location = FLAG,         \
}

#define PIN_BANK_IOMUX_FLAGS_PULL_FLAGS(ID, \
    PINS, LABEL, IOM0, IOM1, IOM2, IOM3,    \
    PULL0, PULL1, PULL2, PULL3)             \
{                                           \
    .bank_num   = ID,                       \
    .nr_pins    = PINS,                     \
    .name       = LABEL,                    \
    .iomux      =                           \
    {                                       \
        { .type = IOM0, .offset = -1 },     \
        { .type = IOM1, .offset = -1 },     \
        { .type = IOM2, .offset = -1 },     \
        { .type = IOM3, .offset = -1 },     \
    },                                      \
    .pull_type[0] = PULL0,                  \
    .pull_type[1] = PULL1,                  \
    .pull_type[2] = PULL2,                  \
    .pull_type[3] = PULL3,                  \
}

#define PIN_BANK_IOMUX_FLAGS_OFFSET_PULL_FLAGS( \
    ID, PINS, LABEL, IOM0, IOM1, IOM2, IOM3,    \
    OFFSET0, OFFSET1, OFFSET2, OFFSET3, PULL0,  \
    PULL1, PULL2, PULL3)                        \
{                                               \
    .bank_num   = ID,                           \
    .nr_pins    = PINS,                         \
    .name       = LABEL,                        \
    .iomux      =                               \
    {                                           \
        { .type = IOM0, .offset = OFFSET0 },    \
        { .type = IOM1, .offset = OFFSET1 },    \
        { .type = IOM2, .offset = OFFSET2 },    \
        { .type = IOM3, .offset = OFFSET3 },    \
    },                                          \
    .pull_type[0] = PULL0,                      \
    .pull_type[1] = PULL1,                      \
    .pull_type[2] = PULL2,                      \
    .pull_type[3] = PULL3,                      \
}

#define RK_MUXROUTE_SAME(ID, PIN, FUNC, REG, VAL)   \
    PIN_BANK_MUX_ROUTE_FLAGS(ID, PIN, FUNC, REG, VAL, ROCKCHIP_ROUTE_SAME)

#define RK_MUXROUTE_GRF(ID, PIN, FUNC, REG, VAL)    \
    PIN_BANK_MUX_ROUTE_FLAGS(ID, PIN, FUNC, REG, VAL, ROCKCHIP_ROUTE_GRF)

#define RK_MUXROUTE_PMU(ID, PIN, FUNC, REG, VAL)    \
    PIN_BANK_MUX_ROUTE_FLAGS(ID, PIN, FUNC, REG, VAL, ROCKCHIP_ROUTE_PMU)

#define PIN_BANK_FLAGS_IOMUX_PULL(ID, PIN, LABEL, M, P) \
    PIN_BANK_IOMUX_FLAGS_PULL_FLAGS(ID, PIN, LABEL, M, M, M, M, P, P, P, P)

#define PIN_BANK_OFFSET4(ID, LABEL, OFFSET0, OFFSET1, OFFSET2, OFFSET3) \
    PIN_BANK_IOMUX_FLAGS_OFFSET_PULL_FLAGS(ID, 32, LABEL,               \
            IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT,                         \
            IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT,                         \
            OFFSET0, OFFSET1, OFFSET2, OFFSET3,                         \
            PULL_TYPE_IO_1, PULL_TYPE_IO_1,                             \
            PULL_TYPE_IO_1, PULL_TYPE_IO_1)

#define RK_RECALCED_DATA(       \
    NUM, PIN, REG, BIT, MASK)   \
{                               \
    .num = NUM,                 \
    .pin = PIN,                 \
    .reg = REG,                 \
    .bit = BIT,                 \
    .mask = MASK,               \
}

static int rockchip_pull_list[PULL_TYPE_MAX][4] =
{
    {
        PIN_CONFIG_BIAS_DISABLE,
        PIN_CONFIG_BIAS_PULL_UP,
        PIN_CONFIG_BIAS_PULL_DOWN,
        PIN_CONFIG_BIAS_BUS_HOLD
    },
    {
        PIN_CONFIG_BIAS_DISABLE,
        PIN_CONFIG_BIAS_PULL_DOWN,
        PIN_CONFIG_BIAS_DISABLE,
        PIN_CONFIG_BIAS_PULL_UP
    },
};

static int rockchip_translate_pull_value(int type, int pull)
{
    int res = -RT_EINVAL;

    for (int i = 0; i < RT_ARRAY_SIZE(rockchip_pull_list[type]); ++i)
    {
        if (rockchip_pull_list[type][i] == pull)
        {
            res = i;
            break;
        }
    }

    return res;
}

static void rockchip_translate_recalced_mux(struct rockchip_pin_bank *pin_bank,
    int pin, int *reg, rt_uint8_t *bit, int *mask)
{
    int i;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;
    struct rockchip_pin_ctrl *pinctrl = drvdata->pinctrl;
    struct rockchip_mux_recalced_data *data;

    for (i = 0; i < pinctrl->niomux_recalced; ++i)
    {
        data = &pinctrl->iomux_recalced[i];

        if (data->num == pin_bank->bank_num && data->pin == pin)
        {
            break;
        }
    }

    if (i >= pinctrl->niomux_recalced)
    {
        return;
    }

    *reg = data->reg;
    *mask = data->mask;
    *bit = data->bit;
}

static rt_bool_t rockchip_translate_mux_route(struct rockchip_pin_bank *pin_bank,
        int pin, int mux, rt_uint32_t *loc, rt_uint32_t *reg, rt_uint32_t *value)
{
    int i;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;
    struct rockchip_pin_ctrl *pinctrl = drvdata->pinctrl;
    struct rockchip_mux_route_data *data;

    for (i = 0; i < pinctrl->niomux_routes; ++i)
    {
        data = &pinctrl->iomux_routes[i];

        if (data->bank_num == pin_bank->bank_num && data->pin == pin && data->func == mux)
        {
            break;
        }
    }

    if (i >= pinctrl->niomux_routes)
    {
        return RT_FALSE;
    }

    *loc = data->route_location;
    *reg = data->route_offset;
    *value = data->route_val;

    return RT_TRUE;
}

static struct rockchip_mux_route_data rk3308_mux_route_data[] =
{
    RK_MUXROUTE_SAME(0, RK_PC3, 1, 0x314, RT_BIT(16 + 0) | RT_BIT(0)), /* rtc_clk */
    RK_MUXROUTE_SAME(1, RK_PC6, 2, 0x314, RT_BIT(16 + 2) | RT_BIT(16 + 3)), /* uart2_rxm0 */
    RK_MUXROUTE_SAME(4, RK_PD2, 2, 0x314, RT_BIT(16 + 2) | RT_BIT(16 + 3) | RT_BIT(2)), /* uart2_rxm1 */
    RK_MUXROUTE_SAME(0, RK_PB7, 2, 0x608, RT_BIT(16 + 8) | RT_BIT(16 + 9)), /* i2c3_sdam0 */
    RK_MUXROUTE_SAME(3, RK_PB4, 2, 0x608, RT_BIT(16 + 8) | RT_BIT(16 + 9) | RT_BIT(8)), /* i2c3_sdam1 */
    RK_MUXROUTE_SAME(2, RK_PA0, 3, 0x608, RT_BIT(16 + 8) | RT_BIT(16 + 9) | RT_BIT(9)), /* i2c3_sdam2 */
    RK_MUXROUTE_SAME(1, RK_PA3, 2, 0x308, RT_BIT(16 + 3)), /* i2s-8ch-1-sclktxm0 */
    RK_MUXROUTE_SAME(1, RK_PA4, 2, 0x308, RT_BIT(16 + 3)), /* i2s-8ch-1-sclkrxm0 */
    RK_MUXROUTE_SAME(1, RK_PB5, 2, 0x308, RT_BIT(16 + 3) | RT_BIT(3)), /* i2s-8ch-1-sclktxm1 */
    RK_MUXROUTE_SAME(1, RK_PB6, 2, 0x308, RT_BIT(16 + 3) | RT_BIT(3)), /* i2s-8ch-1-sclkrxm1 */
    RK_MUXROUTE_SAME(1, RK_PA4, 3, 0x308, RT_BIT(16 + 12) | RT_BIT(16 + 13)), /* pdm-clkm0 */
    RK_MUXROUTE_SAME(1, RK_PB6, 4, 0x308, RT_BIT(16 + 12) | RT_BIT(16 + 13) | RT_BIT(12)), /* pdm-clkm1 */
    RK_MUXROUTE_SAME(2, RK_PA6, 2, 0x308, RT_BIT(16 + 12) | RT_BIT(16 + 13) | RT_BIT(13)), /* pdm-clkm2 */
    RK_MUXROUTE_SAME(2, RK_PA4, 3, 0x600, RT_BIT(16 + 2) | RT_BIT(2)), /* pdm-clkm-m2 */
    RK_MUXROUTE_SAME(3, RK_PB2, 3, 0x314, RT_BIT(16 + 9)), /* spi1_miso */
    RK_MUXROUTE_SAME(2, RK_PA4, 2, 0x314, RT_BIT(16 + 9) | RT_BIT(9)), /* spi1_miso_m1 */
    RK_MUXROUTE_SAME(0, RK_PB3, 3, 0x314, RT_BIT(16 + 10) | RT_BIT(16 + 11)), /* owire_m0 */
    RK_MUXROUTE_SAME(1, RK_PC6, 7, 0x314, RT_BIT(16 + 10) | RT_BIT(16 + 11) | RT_BIT(10)), /* owire_m1 */
    RK_MUXROUTE_SAME(2, RK_PA2, 5, 0x314, RT_BIT(16 + 10) | RT_BIT(16 + 11) | RT_BIT(11)), /* owire_m2 */
    RK_MUXROUTE_SAME(0, RK_PB3, 2, 0x314, RT_BIT(16 + 12) | RT_BIT(16 + 13)), /* can_rxd_m0 */
    RK_MUXROUTE_SAME(1, RK_PC6, 5, 0x314, RT_BIT(16 + 12) | RT_BIT(16 + 13) | RT_BIT(12)), /* can_rxd_m1 */
    RK_MUXROUTE_SAME(2, RK_PA2, 4, 0x314, RT_BIT(16 + 12) | RT_BIT(16 + 13) | RT_BIT(13)), /* can_rxd_m2 */
    RK_MUXROUTE_SAME(1, RK_PC4, 3, 0x314, RT_BIT(16 + 14)), /* mac_rxd0_m0 */
    RK_MUXROUTE_SAME(4, RK_PA2, 2, 0x314, RT_BIT(16 + 14) | RT_BIT(14)), /* mac_rxd0_m1 */
    RK_MUXROUTE_SAME(3, RK_PB4, 4, 0x314, RT_BIT(16 + 15)), /* uart3_rx */
    RK_MUXROUTE_SAME(0, RK_PC1, 3, 0x314, RT_BIT(16 + 15) | RT_BIT(15)), /* uart3_rx_m1 */
};

static struct rockchip_mux_recalced_data rk3308_mux_recalced_data[] =
{
    RK_RECALCED_DATA(1, 14, 0x28, 12, 0xf), /* gpio1b6_sel */
    RK_RECALCED_DATA(1, 15, 0x2c,  0, 0x3), /* gpio1b7_sel */
    RK_RECALCED_DATA(1, 18, 0x30,  4, 0xf), /* gpio1c2_sel */
    RK_RECALCED_DATA(1, 19, 0x30,  8, 0xf), /* gpio1c3_sel */
    RK_RECALCED_DATA(1, 20, 0x30, 12, 0xf), /* gpio1c4_sel */
    RK_RECALCED_DATA(1, 21, 0x34,  0, 0xf), /* gpio1c5_sel */
    RK_RECALCED_DATA(1, 22, 0x34,  4, 0xf), /* gpio1c6_sel */
    RK_RECALCED_DATA(1, 23, 0x34,  8, 0xf), /* gpio1c7_sel */
    RK_RECALCED_DATA(2, 2,  0x40,  4, 0x3), /* gpio2a2_sel */
    RK_RECALCED_DATA(2, 3,  0x40,  6, 0x3), /* gpio2a3_sel */
    RK_RECALCED_DATA(2, 16, 0x50,  0, 0x3), /* gpio2c0_sel */
    RK_RECALCED_DATA(3, 10, 0x68,  4, 0x3), /* gpio3b2_sel */
    RK_RECALCED_DATA(3, 11, 0x68,  6, 0x3), /* gpio3b3_sel */
    RK_RECALCED_DATA(3, 12, 0x68,  8, 0xf), /* gpio3b4_sel */
    RK_RECALCED_DATA(3, 13, 0x68, 12, 0xf), /* gpio3b5_sel */
};

static rt_err_t rk3308_set_mux(struct rockchip_pin_bank *pin_bank, int pin, int mux)
{
    rt_uint8_t bit;
    rt_uint32_t data;
    int iomux_num = (pin / 8), reg, mask;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    if ((pin_bank->iomux[iomux_num].type & IOMUX_SOURCE_PMU))
    {
        regmap = drvdata->regmap_pmu;
    }
    else
    {
        regmap = drvdata->regmap_base;
    }

    reg = pin_bank->iomux[iomux_num].offset;
    if (pin_bank->iomux[iomux_num].type & IOMUX_WIDTH_4BIT)
    {
        if ((pin % 8) >= 4)
        {
            reg += 0x4;
        }
        bit = (pin % 4) * 4;
        mask = 0xf;
    }
    else
    {
        bit = (pin % 8) * 2;
        mask = 0x3;
    }

    if (pin_bank->recalced_mask & RT_BIT(pin))
    {
        rockchip_translate_recalced_mux(pin_bank, pin, &reg, &bit, &mask);
    }

    data = (mask << (bit + 16));
    data |= (mux & mask) << bit;

    return rt_syscon_write(regmap, reg, data);
}

#define RK3308_PULL_OFFSET          0xa0
#define RK3308_PULL_BITS_PER_PIN    2
#define RK3308_PULL_PINS_PER_REG    8
#define RK3308_PULL_BANK_STRIDE     16

static rt_err_t rk3308_set_pull(struct rockchip_pin_bank *pin_bank, int pin, int pull)
{
    int reg, pull_value;
    rt_uint32_t data;
    rt_uint8_t bit, type;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    if (pull == PIN_CONFIG_BIAS_PULL_PIN_DEFAULT)
    {
        return -RT_ENOSYS;
    }

    regmap = drvdata->regmap_base;
    reg = RK3308_PULL_OFFSET;
    reg += pin_bank->bank_num * RK3308_PULL_BANK_STRIDE;
    reg += ((pin / RK3308_PULL_PINS_PER_REG) * 4);

    bit = (pin % RK3308_PULL_PINS_PER_REG);
    bit *= RK3308_PULL_BITS_PER_PIN;

    type = pin_bank->pull_type[pin / 8];
    pull_value = rockchip_translate_pull_value(type, pull);

    if (pull_value < 0)
    {
        LOG_E("Not supported pull = %d, fixup the code or firmware", pull);

        return pull_value;
    }

    /* enable the write to the equivalent lower bits */
    data = ((1 << ROCKCHIP_PULL_BITS_PER_PIN) - 1) << (bit + 16);
    data |= (pull_value << bit);

    return rt_syscon_write(regmap, reg, data);
}

#define RK3308_DRV_GRF_OFFSET   0x100
#define RK3308_DRV_BITS_PER_PIN 2
#define RK3308_DRV_PINS_PER_REG 8
#define RK3308_DRV_BANK_STRIDE  16

static rt_err_t rk3308_set_drive(struct rockchip_pin_bank *pin_bank, int pin, int strength)
{
    int reg;
    rt_uint8_t bit;
    rt_uint32_t data;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    regmap = drvdata->regmap_base;
    reg = RK3308_DRV_GRF_OFFSET;
    reg += pin_bank->bank_num * RK3308_DRV_BANK_STRIDE;
    reg += ((pin / RK3308_DRV_PINS_PER_REG) * 4);

    bit = (pin % RK3308_DRV_PINS_PER_REG);
    bit *= RK3308_DRV_BITS_PER_PIN;

    /* enable the write to the equivalent lower bits */
    data = ((1 << ROCKCHIP_DRV_BITS_PER_PIN) - 1) << (bit + 16);
    data |= (strength << bit);

    return rt_syscon_write(regmap, reg, data);
}

#define RK3308_SCHMITT_PINS_PER_REG 8
#define RK3308_SCHMITT_BANK_STRIDE  16
#define RK3308_SCHMITT_GRF_OFFSET   0x1a0

static rt_err_t rk3308_set_schmitt(struct rockchip_pin_bank *pin_bank, int pin, int enable)
{
    int reg;
    rt_uint8_t bit;
    rt_uint32_t data;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    regmap = drvdata->regmap_base;
    reg = RK3308_SCHMITT_GRF_OFFSET;

    reg += pin_bank->bank_num * RK3308_SCHMITT_BANK_STRIDE;
    reg += ((pin / RK3308_SCHMITT_PINS_PER_REG) * 4);
    bit = pin % RK3308_SCHMITT_PINS_PER_REG;

    /* enable the write to the equivalent lower bits */
    data = RT_BIT(bit + 16) | (enable << bit);

    return rt_syscon_write(regmap, reg, data);
}

static struct rockchip_pin_bank rk3308_pin_banks[] =
{
    PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT),
    PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT),
    PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT),
    PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3", IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT),
    PIN_BANK_IOMUX_FLAGS(4, 32, "gpio4", IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT, IOMUX_WIDTH_2BIT),
};

static struct rockchip_pin_ctrl rk3308_pin_ctrl =
{
    .pin_banks          = rk3308_pin_banks,
    .banks_nr           = RT_ARRAY_SIZE(rk3308_pin_banks),
    .label              = "RK3308-GPIO",
    .type               = RK3308,
    .grf_mux_offset     = 0x0,
    .grf_drv_offset     = RK3308_DRV_GRF_OFFSET,
    .iomux_recalced     = rk3308_mux_recalced_data,
    .niomux_recalced    = RT_ARRAY_SIZE(rk3308_mux_recalced_data),
    .iomux_routes       = rk3308_mux_route_data,
    .niomux_routes      = RT_ARRAY_SIZE(rk3308_mux_route_data),
    .set_mux            = rk3308_set_mux,
    .set_pull           = rk3308_set_pull,
    .set_drive          = rk3308_set_drive,
    .set_schmitt        = rk3308_set_schmitt,
};

static struct rockchip_mux_route_data rk3568_mux_route_data[] =
{
    RK_MUXROUTE_PMU(0, RK_PB7, 1, 0x0110, WRITE_MASK_VAL(1, 0, 0)), /* PWM0 IO mux M0 */
    RK_MUXROUTE_PMU(0, RK_PC7, 2, 0x0110, WRITE_MASK_VAL(1, 0, 1)), /* PWM0 IO mux M1 */
    RK_MUXROUTE_PMU(0, RK_PC0, 1, 0x0110, WRITE_MASK_VAL(3, 2, 0)), /* PWM1 IO mux M0 */
    RK_MUXROUTE_PMU(0, RK_PB5, 4, 0x0110, WRITE_MASK_VAL(3, 2, 1)), /* PWM1 IO mux M1 */
    RK_MUXROUTE_PMU(0, RK_PC1, 1, 0x0110, WRITE_MASK_VAL(5, 4, 0)), /* PWM2 IO mux M0 */
    RK_MUXROUTE_PMU(0, RK_PB6, 4, 0x0110, WRITE_MASK_VAL(5, 4, 1)), /* PWM2 IO mux M1 */
    RK_MUXROUTE_GRF(0, RK_PB3, 2, 0x0300, WRITE_MASK_VAL(0, 0, 0)), /* CAN0 IO mux M0 */
    RK_MUXROUTE_GRF(2, RK_PA1, 4, 0x0300, WRITE_MASK_VAL(0, 0, 1)), /* CAN0 IO mux M1 */
    RK_MUXROUTE_GRF(1, RK_PA1, 3, 0x0300, WRITE_MASK_VAL(2, 2, 0)), /* CAN1 IO mux M0 */
    RK_MUXROUTE_GRF(4, RK_PC3, 3, 0x0300, WRITE_MASK_VAL(2, 2, 1)), /* CAN1 IO mux M1 */
    RK_MUXROUTE_GRF(4, RK_PB5, 3, 0x0300, WRITE_MASK_VAL(4, 4, 0)), /* CAN2 IO mux M0 */
    RK_MUXROUTE_GRF(2, RK_PB2, 4, 0x0300, WRITE_MASK_VAL(4, 4, 1)), /* CAN2 IO mux M1 */
    RK_MUXROUTE_GRF(4, RK_PC4, 1, 0x0300, WRITE_MASK_VAL(6, 6, 0)), /* HPDIN IO mux M0 */
    RK_MUXROUTE_GRF(0, RK_PC2, 2, 0x0300, WRITE_MASK_VAL(6, 6, 1)), /* HPDIN IO mux M1 */
    RK_MUXROUTE_GRF(3, RK_PB1, 3, 0x0300, WRITE_MASK_VAL(8, 8, 0)), /* GMAC1 IO mux M0 */
    RK_MUXROUTE_GRF(4, RK_PA7, 3, 0x0300, WRITE_MASK_VAL(8, 8, 1)), /* GMAC1 IO mux M1 */
    RK_MUXROUTE_GRF(4, RK_PD1, 1, 0x0300, WRITE_MASK_VAL(10, 10, 0)), /* HDMITX IO mux M0 */
    RK_MUXROUTE_GRF(0, RK_PC7, 1, 0x0300, WRITE_MASK_VAL(10, 10, 1)), /* HDMITX IO mux M1 */
    RK_MUXROUTE_GRF(0, RK_PB6, 1, 0x0300, WRITE_MASK_VAL(14, 14, 0)), /* I2C2 IO mux M0 */
    RK_MUXROUTE_GRF(4, RK_PB4, 1, 0x0300, WRITE_MASK_VAL(14, 14, 1)), /* I2C2 IO mux M1 */
    RK_MUXROUTE_GRF(1, RK_PA0, 1, 0x0304, WRITE_MASK_VAL(0, 0, 0)), /* I2C3 IO mux M0 */
    RK_MUXROUTE_GRF(3, RK_PB6, 4, 0x0304, WRITE_MASK_VAL(0, 0, 1)), /* I2C3 IO mux M1 */
    RK_MUXROUTE_GRF(4, RK_PB2, 1, 0x0304, WRITE_MASK_VAL(2, 2, 0)), /* I2C4 IO mux M0 */
    RK_MUXROUTE_GRF(2, RK_PB1, 2, 0x0304, WRITE_MASK_VAL(2, 2, 1)), /* I2C4 IO mux M1 */
    RK_MUXROUTE_GRF(3, RK_PB4, 4, 0x0304, WRITE_MASK_VAL(4, 4, 0)), /* I2C5 IO mux M0 */
    RK_MUXROUTE_GRF(4, RK_PD0, 2, 0x0304, WRITE_MASK_VAL(4, 4, 1)), /* I2C5 IO mux M1 */
    RK_MUXROUTE_GRF(3, RK_PB1, 5, 0x0304, WRITE_MASK_VAL(14, 14, 0)), /* PWM8 IO mux M0 */
    RK_MUXROUTE_GRF(1, RK_PD5, 4, 0x0304, WRITE_MASK_VAL(14, 14, 1)), /* PWM8 IO mux M1 */
    RK_MUXROUTE_GRF(3, RK_PB2, 5, 0x0308, WRITE_MASK_VAL(0, 0, 0)), /* PWM9 IO mux M0 */
    RK_MUXROUTE_GRF(1, RK_PD6, 4, 0x0308, WRITE_MASK_VAL(0, 0, 1)), /* PWM9 IO mux M1 */
    RK_MUXROUTE_GRF(3, RK_PB5, 5, 0x0308, WRITE_MASK_VAL(2, 2, 0)), /* PWM10 IO mux M0 */
    RK_MUXROUTE_GRF(2, RK_PA1, 2, 0x0308, WRITE_MASK_VAL(2, 2, 1)), /* PWM10 IO mux M1 */
    RK_MUXROUTE_GRF(3, RK_PB6, 5, 0x0308, WRITE_MASK_VAL(4, 4, 0)), /* PWM11 IO mux M0 */
    RK_MUXROUTE_GRF(4, RK_PC0, 3, 0x0308, WRITE_MASK_VAL(4, 4, 1)), /* PWM11 IO mux M1 */
    RK_MUXROUTE_GRF(3, RK_PB7, 2, 0x0308, WRITE_MASK_VAL(6, 6, 0)), /* PWM12 IO mux M0 */
    RK_MUXROUTE_GRF(4, RK_PC5, 1, 0x0308, WRITE_MASK_VAL(6, 6, 1)), /* PWM12 IO mux M1 */
    RK_MUXROUTE_GRF(3, RK_PC0, 2, 0x0308, WRITE_MASK_VAL(8, 8, 0)), /* PWM13 IO mux M0 */
    RK_MUXROUTE_GRF(4, RK_PC6, 1, 0x0308, WRITE_MASK_VAL(8, 8, 1)), /* PWM13 IO mux M1 */
    RK_MUXROUTE_GRF(3, RK_PC4, 1, 0x0308, WRITE_MASK_VAL(10, 10, 0)), /* PWM14 IO mux M0 */
    RK_MUXROUTE_GRF(4, RK_PC2, 1, 0x0308, WRITE_MASK_VAL(10, 10, 1)), /* PWM14 IO mux M1 */
    RK_MUXROUTE_GRF(3, RK_PC5, 1, 0x0308, WRITE_MASK_VAL(12, 12, 0)), /* PWM15 IO mux M0 */
    RK_MUXROUTE_GRF(4, RK_PC3, 1, 0x0308, WRITE_MASK_VAL(12, 12, 1)), /* PWM15 IO mux M1 */
    RK_MUXROUTE_GRF(3, RK_PD2, 3, 0x0308, WRITE_MASK_VAL(14, 14, 0)), /* SDMMC2 IO mux M0 */
    RK_MUXROUTE_GRF(3, RK_PA5, 5, 0x0308, WRITE_MASK_VAL(14, 14, 1)), /* SDMMC2 IO mux M1 */
    RK_MUXROUTE_GRF(0, RK_PB5, 2, 0x030c, WRITE_MASK_VAL(0, 0, 0)), /* SPI0 IO mux M0 */
    RK_MUXROUTE_GRF(2, RK_PD3, 3, 0x030c, WRITE_MASK_VAL(0, 0, 1)), /* SPI0 IO mux M1 */
    RK_MUXROUTE_GRF(2, RK_PB5, 3, 0x030c, WRITE_MASK_VAL(2, 2, 0)), /* SPI1 IO mux M0 */
    RK_MUXROUTE_GRF(3, RK_PC3, 3, 0x030c, WRITE_MASK_VAL(2, 2, 1)), /* SPI1 IO mux M1 */
    RK_MUXROUTE_GRF(2, RK_PC1, 4, 0x030c, WRITE_MASK_VAL(4, 4, 0)), /* SPI2 IO mux M0 */
    RK_MUXROUTE_GRF(3, RK_PA0, 3, 0x030c, WRITE_MASK_VAL(4, 4, 1)), /* SPI2 IO mux M1 */
    RK_MUXROUTE_GRF(4, RK_PB3, 4, 0x030c, WRITE_MASK_VAL(6, 6, 0)), /* SPI3 IO mux M0 */
    RK_MUXROUTE_GRF(4, RK_PC2, 2, 0x030c, WRITE_MASK_VAL(6, 6, 1)), /* SPI3 IO mux M1 */
    RK_MUXROUTE_GRF(2, RK_PB4, 2, 0x030c, WRITE_MASK_VAL(8, 8, 0)), /* UART1 IO mux M0 */
    RK_MUXROUTE_GRF(3, RK_PD6, 4, 0x030c, WRITE_MASK_VAL(8, 8, 1)), /* UART1 IO mux M1 */
    RK_MUXROUTE_GRF(0, RK_PD1, 1, 0x030c, WRITE_MASK_VAL(10, 10, 0)), /* UART2 IO mux M0 */
    RK_MUXROUTE_GRF(1, RK_PD5, 2, 0x030c, WRITE_MASK_VAL(10, 10, 1)), /* UART2 IO mux M1 */
    RK_MUXROUTE_GRF(1, RK_PA1, 2, 0x030c, WRITE_MASK_VAL(12, 12, 0)), /* UART3 IO mux M0 */
    RK_MUXROUTE_GRF(3, RK_PB7, 4, 0x030c, WRITE_MASK_VAL(12, 12, 1)), /* UART3 IO mux M1 */
    RK_MUXROUTE_GRF(1, RK_PA6, 2, 0x030c, WRITE_MASK_VAL(14, 14, 0)), /* UART4 IO mux M0 */
    RK_MUXROUTE_GRF(3, RK_PB2, 4, 0x030c, WRITE_MASK_VAL(14, 14, 1)), /* UART4 IO mux M1 */
    RK_MUXROUTE_GRF(2, RK_PA2, 3, 0x0310, WRITE_MASK_VAL(0, 0, 0)), /* UART5 IO mux M0 */
    RK_MUXROUTE_GRF(3, RK_PC2, 4, 0x0310, WRITE_MASK_VAL(0, 0, 1)), /* UART5 IO mux M1 */
    RK_MUXROUTE_GRF(2, RK_PA4, 3, 0x0310, WRITE_MASK_VAL(2, 2, 0)), /* UART6 IO mux M0 */
    RK_MUXROUTE_GRF(1, RK_PD5, 3, 0x0310, WRITE_MASK_VAL(2, 2, 1)), /* UART6 IO mux M1 */
    RK_MUXROUTE_GRF(2, RK_PA6, 3, 0x0310, WRITE_MASK_VAL(5, 4, 0)), /* UART7 IO mux M0 */
    RK_MUXROUTE_GRF(3, RK_PC4, 4, 0x0310, WRITE_MASK_VAL(5, 4, 1)), /* UART7 IO mux M1 */
    RK_MUXROUTE_GRF(4, RK_PA2, 4, 0x0310, WRITE_MASK_VAL(5, 4, 2)), /* UART7 IO mux M2 */
    RK_MUXROUTE_GRF(2, RK_PC5, 3, 0x0310, WRITE_MASK_VAL(6, 6, 0)), /* UART8 IO mux M0 */
    RK_MUXROUTE_GRF(2, RK_PD7, 4, 0x0310, WRITE_MASK_VAL(6, 6, 1)), /* UART8 IO mux M1 */
    RK_MUXROUTE_GRF(2, RK_PB0, 3, 0x0310, WRITE_MASK_VAL(9, 8, 0)), /* UART9 IO mux M0 */
    RK_MUXROUTE_GRF(4, RK_PC5, 4, 0x0310, WRITE_MASK_VAL(9, 8, 1)), /* UART9 IO mux M1 */
    RK_MUXROUTE_GRF(4, RK_PA4, 4, 0x0310, WRITE_MASK_VAL(9, 8, 2)), /* UART9 IO mux M2 */
    RK_MUXROUTE_GRF(1, RK_PA2, 1, 0x0310, WRITE_MASK_VAL(11, 10, 0)), /* I2S1 IO mux M0 */
    RK_MUXROUTE_GRF(3, RK_PC6, 4, 0x0310, WRITE_MASK_VAL(11, 10, 1)), /* I2S1 IO mux M1 */
    RK_MUXROUTE_GRF(2, RK_PD0, 5, 0x0310, WRITE_MASK_VAL(11, 10, 2)), /* I2S1 IO mux M2 */
    RK_MUXROUTE_GRF(2, RK_PC1, 1, 0x0310, WRITE_MASK_VAL(12, 12, 0)), /* I2S2 IO mux M0 */
    RK_MUXROUTE_GRF(4, RK_PB6, 5, 0x0310, WRITE_MASK_VAL(12, 12, 1)), /* I2S2 IO mux M1 */
    RK_MUXROUTE_GRF(3, RK_PA2, 4, 0x0310, WRITE_MASK_VAL(14, 14, 0)), /* I2S3 IO mux M0 */
    RK_MUXROUTE_GRF(4, RK_PC2, 5, 0x0310, WRITE_MASK_VAL(14, 14, 1)), /* I2S3 IO mux M1 */
    RK_MUXROUTE_GRF(1, RK_PA4, 3, 0x0314, WRITE_MASK_VAL(1, 0, 0)), /* PDM IO mux M0 */
    RK_MUXROUTE_GRF(1, RK_PA6, 3, 0x0314, WRITE_MASK_VAL(1, 0, 0)), /* PDM IO mux M0 */
    RK_MUXROUTE_GRF(3, RK_PD6, 5, 0x0314, WRITE_MASK_VAL(1, 0, 1)), /* PDM IO mux M1 */
    RK_MUXROUTE_GRF(4, RK_PA0, 4, 0x0314, WRITE_MASK_VAL(1, 0, 1)), /* PDM IO mux M1 */
    RK_MUXROUTE_GRF(3, RK_PC4, 5, 0x0314, WRITE_MASK_VAL(1, 0, 2)), /* PDM IO mux M2 */
    RK_MUXROUTE_GRF(0, RK_PA5, 3, 0x0314, WRITE_MASK_VAL(3, 2, 0)), /* PCIE20 IO mux M0 */
    RK_MUXROUTE_GRF(2, RK_PD0, 4, 0x0314, WRITE_MASK_VAL(3, 2, 1)), /* PCIE20 IO mux M1 */
    RK_MUXROUTE_GRF(1, RK_PB0, 4, 0x0314, WRITE_MASK_VAL(3, 2, 2)), /* PCIE20 IO mux M2 */
    RK_MUXROUTE_GRF(0, RK_PA4, 3, 0x0314, WRITE_MASK_VAL(5, 4, 0)), /* PCIE30X1 IO mux M0 */
    RK_MUXROUTE_GRF(2, RK_PD2, 4, 0x0314, WRITE_MASK_VAL(5, 4, 1)), /* PCIE30X1 IO mux M1 */
    RK_MUXROUTE_GRF(1, RK_PA5, 4, 0x0314, WRITE_MASK_VAL(5, 4, 2)), /* PCIE30X1 IO mux M2 */
    RK_MUXROUTE_GRF(0, RK_PA6, 2, 0x0314, WRITE_MASK_VAL(7, 6, 0)), /* PCIE30X2 IO mux M0 */
    RK_MUXROUTE_GRF(2, RK_PD4, 4, 0x0314, WRITE_MASK_VAL(7, 6, 1)), /* PCIE30X2 IO mux M1 */
    RK_MUXROUTE_GRF(4, RK_PC2, 4, 0x0314, WRITE_MASK_VAL(7, 6, 2)), /* PCIE30X2 IO mux M2 */
};

static rt_err_t rk3568_set_mux(struct rockchip_pin_bank *pin_bank, int pin, int mux)
{
    rt_uint8_t bit;
    rt_uint32_t data;
    rt_uint32_t route_location, route_reg, route_val;
    int iomux_num = (pin / 8), reg, mask;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    if ((pin_bank->iomux[iomux_num].type & IOMUX_SOURCE_PMU))
    {
        regmap = drvdata->regmap_pmu;
    }
    else
    {
        regmap = drvdata->regmap_base;
    }

    reg = pin_bank->iomux[iomux_num].offset;
    if ((pin % 8) >= 4)
    {
        reg += 0x4;
    }
    bit = (pin % 4) * 4;
    mask = 0xf;

    if (pin_bank->route_mask & RT_BIT(pin))
    {
        if (rockchip_translate_mux_route(pin_bank, pin, mux, &route_location,
                &route_reg, &route_val))
        {
            rt_err_t err;
            struct rt_syscon *route_regmap;

            /* handle special locations */
            switch (route_location)
            {
            case ROCKCHIP_ROUTE_PMU:
                route_regmap = drvdata->regmap_pmu;
                break;

            case ROCKCHIP_ROUTE_GRF:
                route_regmap = drvdata->regmap_base;
                break;

            default:
                route_regmap = regmap;
                break;
            }

            if ((err = rt_syscon_write(route_regmap, route_reg, route_val)))
            {
                return err;
            }
        }
    }

    data = (mask << (bit + 16));
    data |= (mux & mask) << bit;

    return rt_syscon_write(regmap, reg, data);
}

#define RK3568_PULL_PMU_OFFSET      0x20
#define RK3568_PULL_GRF_OFFSET      0x80
#define RK3568_PULL_BITS_PER_PIN    2
#define RK3568_PULL_PINS_PER_REG    8
#define RK3568_PULL_BANK_STRIDE     0x10

static rt_err_t rk3568_set_pull(struct rockchip_pin_bank *pin_bank, int pin, int pull)
{
    int reg, pull_value;
    rt_uint32_t data;
    rt_uint8_t bit, type;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    if (pull == PIN_CONFIG_BIAS_PULL_PIN_DEFAULT)
    {
        return -RT_ENOSYS;
    }

    if (pin_bank->bank_num == 0)
    {
        regmap = drvdata->regmap_pmu;
        reg = RK3568_PULL_PMU_OFFSET;
        reg += pin_bank->bank_num * RK3568_PULL_BANK_STRIDE;
    }
    else
    {
        regmap = drvdata->regmap_base;
        reg = RK3568_PULL_GRF_OFFSET;
        reg += (pin_bank->bank_num - 1) * RK3568_PULL_BANK_STRIDE;
    }

    reg += ((pin / RK3568_PULL_PINS_PER_REG) * 4);
    bit = (pin % RK3568_PULL_PINS_PER_REG);
    bit *= RK3568_PULL_BITS_PER_PIN;

    type = pin_bank->pull_type[pin / 8];
    pull_value = rockchip_translate_pull_value(type, pull);

    /*
     * pull-up being 1 for everything except the GPIO0_D3-D6,
     * where that pull up value becomes 3
     */
    if (pin_bank->bank_num == 0 && pin >= RK_GPIO0_D3 && pin <= RK_GPIO0_D6)
    {
        if (pull_value == 1)
        {
            pull_value = 3;
        }
    }

    if (pull_value < 0)
    {
        LOG_E("Not supported pull = %d, fixup the code or firmware", pull);

        return pull_value;
    }

    /* enable the write to the equivalent lower bits */
    data = ((1 << ROCKCHIP_PULL_BITS_PER_PIN) - 1) << (bit + 16);
    data |= (pull_value << bit);

    return rt_syscon_write(regmap, reg, data);
}

#define RK3568_DRV_PMU_OFFSET   0x70
#define RK3568_DRV_GRF_OFFSET   0x200
#define RK3568_DRV_BITS_PER_PIN 8
#define RK3568_DRV_PINS_PER_REG 2
#define RK3568_DRV_BANK_STRIDE  0x40

#define RK3568_GRF_GPIO1C5_DS   0x840
#define RK3568_GRF_GPIO2A2_DS   0x844
#define RK3568_GRF_GPIO2B0_DS   0x848
#define RK3568_GRF_GPIO3A0_DS   0x84c
#define RK3568_GRF_GPIO3A6_DS   0x850
#define RK3568_GRF_GPIO4A0_DS   0x854

static rt_err_t rk3568_set_drive(struct rockchip_pin_bank *pin_bank, int pin, int strength)
{
    rt_err_t err;
    rt_uint8_t bit;
    rt_uint32_t data;
    int reg, drv = (1 << (strength + 1)) - 1;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    if (pin_bank->bank_num == 0)
    {
        regmap = drvdata->regmap_pmu;
        reg = RK3568_DRV_PMU_OFFSET;
    }
    else
    {
        regmap = drvdata->regmap_base;
        reg = RK3568_DRV_GRF_OFFSET;
        reg += (pin_bank->bank_num - 1) * RK3568_DRV_BANK_STRIDE;
    }

    reg += ((pin / RK3568_DRV_PINS_PER_REG) * 4);
    bit = (pin % RK3568_DRV_PINS_PER_REG);
    bit *= RK3568_DRV_BITS_PER_PIN;

    /* enable the write to the equivalent lower bits */
    data = ((1 << RK3568_DRV_BITS_PER_PIN) - 1) << (bit + 16);
    data |= (drv << bit);

    if ((err = rt_syscon_write(regmap, reg, data)))
    {
        return err;
    }

    if (pin_bank->bank_num == RK_GPIO1 && pin == RK_PC5)
    {
        reg = RK3568_GRF_GPIO1C5_DS;
    }
    else if (pin_bank->bank_num == RK_GPIO2 && pin == RK_PA2)
    {
        reg = RK3568_GRF_GPIO2A2_DS;
    }
    else if (pin_bank->bank_num == RK_GPIO2 && pin == RK_PB0)
    {
        reg = RK3568_GRF_GPIO2B0_DS;
    }
    else if (pin_bank->bank_num == RK_GPIO3 && pin == RK_PA0)
    {
        reg = RK3568_GRF_GPIO3A0_DS;
    }
    else if (pin_bank->bank_num == RK_GPIO3 && pin == RK_PA6)
    {
        reg = RK3568_GRF_GPIO3A6_DS;
    }
    else if (pin_bank->bank_num == RK_GPIO4 && pin == RK_PA0)
    {
        reg = RK3568_GRF_GPIO4A0_DS;
    }
    else
    {
        return RT_EOK;
    }

    data = ((1 << RK3568_DRV_BITS_PER_PIN) - 1) << 16;
    data |= drv;

    return rt_syscon_write(regmap, reg, data);
}

#define RK3568_SCHMITT_BITS_PER_PIN     2
#define RK3568_SCHMITT_PINS_PER_REG     8
#define RK3568_SCHMITT_BANK_STRIDE      0x10
#define RK3568_SCHMITT_GRF_OFFSET       0xc0
#define RK3568_SCHMITT_PMUGRF_OFFSET    0x30

static rt_err_t rk3568_set_schmitt(struct rockchip_pin_bank *pin_bank, int pin, int enable)
{
    int reg;
    rt_uint8_t bit;
    rt_uint32_t data;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    if (pin_bank->bank_num == 0)
    {
        regmap = drvdata->regmap_pmu;
        reg = RK3568_SCHMITT_PMUGRF_OFFSET;
    }
    else
    {
        regmap = drvdata->regmap_base;
        reg = RK3568_SCHMITT_GRF_OFFSET;
        reg += (pin_bank->bank_num - 1) * RK3568_SCHMITT_BANK_STRIDE;
    }

    reg += ((pin / RK3568_SCHMITT_PINS_PER_REG) * 4);
    bit = pin % RK3568_SCHMITT_PINS_PER_REG;
    bit *= RK3568_SCHMITT_BITS_PER_PIN;

    /* enable the write to the equivalent lower bits */
    data = ((1 << RK3568_SCHMITT_BITS_PER_PIN) - 1) << (bit + 16);
    data |= (enable << bit);

    return rt_syscon_write(regmap, reg, data);
}

static struct rockchip_pin_bank rk3568_pin_banks[] =
{
    PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_SOURCE_PMU | IOMUX_WIDTH_4BIT, IOMUX_SOURCE_PMU | IOMUX_WIDTH_4BIT,
            IOMUX_SOURCE_PMU | IOMUX_WIDTH_4BIT, IOMUX_SOURCE_PMU | IOMUX_WIDTH_4BIT),
    PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT),
    PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT),
    PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3", IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT),
    PIN_BANK_IOMUX_FLAGS(4, 32, "gpio4", IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT, IOMUX_WIDTH_4BIT),
};

static struct rockchip_pin_ctrl rk3568_pin_ctrl =
{
    .pin_banks          = rk3568_pin_banks,
    .banks_nr           = RT_ARRAY_SIZE(rk3568_pin_banks),
    .label              = "RK3568-GPIO",
    .type               = RK3568,
    .grf_mux_offset     = 0x0,
    .pmu_mux_offset     = 0x0,
    .grf_drv_offset     = RK3568_DRV_GRF_OFFSET,
    .pmu_drv_offset     = RK3568_DRV_PMU_OFFSET,
    .iomux_routes       = rk3568_mux_route_data,
    .niomux_routes      = RT_ARRAY_SIZE(rk3568_mux_route_data),
    .set_mux            = rk3568_set_mux,
    .set_pull           = rk3568_set_pull,
    .set_drive          = rk3568_set_drive,
    .set_schmitt        = rk3568_set_schmitt,
};

static rt_err_t rk3576_set_mux(struct rockchip_pin_bank *pin_bank, int pin, int mux)
{
    rt_uint8_t bit;
    rt_uint32_t data;
    int iomux_num = (pin / 8), reg, mask;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    regmap = drvdata->regmap_base;
    reg = pin_bank->iomux[iomux_num].offset;

    if ((pin % 8) >= 4)
    {
        reg += 0x4;
    }

    bit = (pin % 4) * 4;
    mask = 0xf;

    data = (mask << (bit + 16));
    data |= (mux & mask) << bit;

    if (pin_bank->bank_num == 0 && pin >= RK_PB4 && pin <= RK_PB7)
    {
        /* GPIO0_IOC_GPIO0B_IOMUX_SEL_H */
        reg += 0x1ff4;
    }

    return rt_syscon_write(regmap, reg, data);
}

#define RK3576_DRV_BITS_PER_PIN     4
#define RK3576_DRV_PINS_PER_REG     4
#define RK3576_DRV_GPIO0_AL_OFFSET  0x10
#define RK3576_DRV_GPIO0_BH_OFFSET  0x2014
#define RK3576_DRV_GPIO1_OFFSET     0x6020
#define RK3576_DRV_GPIO2_OFFSET     0x6040
#define RK3576_DRV_GPIO3_OFFSET     0x6060
#define RK3576_DRV_GPIO4_AL_OFFSET  0x6080
#define RK3576_DRV_GPIO4_CL_OFFSET  0xa090
#define RK3576_DRV_GPIO4_DL_OFFSET  0xb098

static rt_err_t rk3576_set_drive(struct rockchip_pin_bank *pin_bank, int pin_num, int strength)
{
    rt_uint8_t bit;
    rt_uint32_t data;
    int reg, drv = ((strength & RT_BIT(2)) >> 2) | ((strength & RT_BIT(0)) << 2) | (strength & RT_BIT(1));
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    regmap = drvdata->regmap_base;

    if (pin_bank->bank_num == 0 && pin_num < 12)
    {
        reg = RK3576_DRV_GPIO0_AL_OFFSET;
    }
    else if (pin_bank->bank_num == 0)
    {
        reg = RK3576_DRV_GPIO0_BH_OFFSET - 0xc;
    }
    else if (pin_bank->bank_num == 1)
    {
        reg = RK3576_DRV_GPIO1_OFFSET;
    }
    else if (pin_bank->bank_num == 2)
    {
        reg = RK3576_DRV_GPIO2_OFFSET;
    }
    else if (pin_bank->bank_num == 3)
    {
        reg = RK3576_DRV_GPIO3_OFFSET;
    }
    else if (pin_bank->bank_num == 4 && pin_num < 16)
    {
        reg = RK3576_DRV_GPIO4_AL_OFFSET;
    }
    else if (pin_bank->bank_num == 4 && pin_num < 24)
    {
        reg = RK3576_DRV_GPIO4_CL_OFFSET - 0x10;
    }
    else if (pin_bank->bank_num == 4)
    {
        reg = RK3576_DRV_GPIO4_DL_OFFSET - 0x18;
    }
    else
    {
        reg = 0;
        LOG_E("Unsupported bank_num %d", pin_bank->bank_num);
    }

    reg += ((pin_num / RK3576_DRV_PINS_PER_REG) * 4);
    bit = pin_num % RK3576_DRV_PINS_PER_REG;
    bit *= RK3576_DRV_BITS_PER_PIN;

    /* enable the write to the equivalent lower bits */
    data = ((1 << RK3576_DRV_BITS_PER_PIN) - 1) << (bit + 16);
    data |= (drv << bit);

    return rt_syscon_write(regmap, reg, data);
}

#define RK3576_PULL_BITS_PER_PIN    2
#define RK3576_PULL_PINS_PER_REG    8
#define RK3576_PULL_GPIO0_AL_OFFSET 0x20
#define RK3576_PULL_GPIO0_BH_OFFSET 0x2028
#define RK3576_PULL_GPIO1_OFFSET    0x6110
#define RK3576_PULL_GPIO2_OFFSET    0x6120
#define RK3576_PULL_GPIO3_OFFSET    0x6130
#define RK3576_PULL_GPIO4_AL_OFFSET 0x6140
#define RK3576_PULL_GPIO4_CL_OFFSET 0xa148
#define RK3576_PULL_GPIO4_DL_OFFSET 0xb14c

static rt_err_t rk3576_set_pull(struct rockchip_pin_bank *pin_bank, int pin_num, int pull)
{
    int reg, pull_value;
    rt_uint32_t data;
    rt_uint8_t bit, type;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    if (pull == PIN_CONFIG_BIAS_PULL_PIN_DEFAULT)
    {
        return -RT_ENOSYS;
    }

    regmap = drvdata->regmap_base;

    if (pin_bank->bank_num == 0 && pin_num < 12)
    {
        reg = RK3576_PULL_GPIO0_AL_OFFSET;
    }
    else if (pin_bank->bank_num == 0)
    {
        reg = RK3576_PULL_GPIO0_BH_OFFSET - 0x4;
    }
    else if (pin_bank->bank_num == 1)
    {
        reg = RK3576_PULL_GPIO1_OFFSET;
    }
    else if (pin_bank->bank_num == 2)
    {
        reg = RK3576_PULL_GPIO2_OFFSET;
    }
    else if (pin_bank->bank_num == 3)
    {
        reg = RK3576_PULL_GPIO3_OFFSET;
    }
    else if (pin_bank->bank_num == 4 && pin_num < 16)
    {
        reg = RK3576_PULL_GPIO4_AL_OFFSET;
    }
    else if (pin_bank->bank_num == 4 && pin_num < 24)
    {
        reg = RK3576_PULL_GPIO4_CL_OFFSET - 0x8;
    }
    else if (pin_bank->bank_num == 4)
    {
        reg = RK3576_PULL_GPIO4_DL_OFFSET - 0xc;
    }
    else
    {
        reg = 0;
        LOG_E("Unsupported bank_num %d", pin_bank->bank_num);
    }

    reg += ((pin_num / RK3576_PULL_PINS_PER_REG) * 4);
    bit = pin_num % RK3576_PULL_PINS_PER_REG;
    bit *= RK3576_PULL_BITS_PER_PIN;

    type = pin_bank->pull_type[pin_num / 8];
    pull_value = rockchip_translate_pull_value(type, pull);

    if (pull_value < 0)
    {
        LOG_E("Not supported pull = %d, fixup the code or firmware", pull);

        return pull_value;
    }

    /* enable the write to the equivalent lower bits */
    data = ((1 << RK3576_PULL_BITS_PER_PIN) - 1) << (bit + 16);
    data |= (pull_value << bit);

    return rt_syscon_write(regmap, reg, data);
}

#define RK3576_SMT_BITS_PER_PIN     1
#define RK3576_SMT_PINS_PER_REG     8
#define RK3576_SMT_GPIO0_AL_OFFSET  0x30
#define RK3576_SMT_GPIO0_BH_OFFSET  0x2040
#define RK3576_SMT_GPIO1_OFFSET     0x6210
#define RK3576_SMT_GPIO2_OFFSET     0x6220
#define RK3576_SMT_GPIO3_OFFSET     0x6230
#define RK3576_SMT_GPIO4_AL_OFFSET  0x6240
#define RK3576_SMT_GPIO4_CL_OFFSET  0xA248
#define RK3576_SMT_GPIO4_DL_OFFSET  0xB24C

static rt_err_t rk3576_set_schmitt(struct rockchip_pin_bank *pin_bank, int pin_num, int enable)
{
    int reg;
    rt_uint8_t bit;
    rt_uint32_t data;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    regmap = drvdata->regmap_base;

    if (pin_bank->bank_num == 0 && pin_num < 12)
    {
        reg = RK3576_SMT_GPIO0_AL_OFFSET;
    }
    else if (pin_bank->bank_num == 0)
    {
        reg = RK3576_SMT_GPIO0_BH_OFFSET - 0x4;
    }
    else if (pin_bank->bank_num == 1)
    {
        reg = RK3576_SMT_GPIO1_OFFSET;
    }
    else if (pin_bank->bank_num == 2)
    {
        reg = RK3576_SMT_GPIO2_OFFSET;
    }
    else if (pin_bank->bank_num == 3)
    {
        reg = RK3576_SMT_GPIO3_OFFSET;
    }
    else if (pin_bank->bank_num == 4 && pin_num < 16)
    {
        reg = RK3576_SMT_GPIO4_AL_OFFSET;
    }
    else if (pin_bank->bank_num == 4 && pin_num < 24)
    {
        reg = RK3576_SMT_GPIO4_CL_OFFSET - 0x8;
    }
    else if (pin_bank->bank_num == 4)
    {
        reg = RK3576_SMT_GPIO4_DL_OFFSET - 0xc;
    }
    else
    {
        reg = 0;
        LOG_E("Unsupported bank_num %d", pin_bank->bank_num);
    }

    reg += ((pin_num / RK3576_SMT_PINS_PER_REG) * 4);
    bit = pin_num % RK3576_SMT_PINS_PER_REG;
    bit *= RK3576_SMT_BITS_PER_PIN;

    /* enable the write to the equivalent lower bits */
    data = ((1 << RK3576_SMT_BITS_PER_PIN) - 1) << (bit + 16);
    data |= (enable << bit);

    return rt_syscon_write(regmap, reg, data);
}

static struct rockchip_pin_bank rk3576_pin_banks[] =
{
    PIN_BANK_OFFSET4(0, "gpio0", 0, 0x8, 0x2004, 0x200C),
    PIN_BANK_OFFSET4(1, "gpio1", 0x4020, 0x4028, 0x4030, 0x4038),
    PIN_BANK_OFFSET4(2, "gpio2", 0x4040, 0x4048, 0x4050, 0x4058),
    PIN_BANK_OFFSET4(3, "gpio3", 0x4060, 0x4068, 0x4070, 0x4078),
    PIN_BANK_OFFSET4(4, "gpio4", 0x4080, 0x4088, 0xA390, 0xB398),
};

static const struct rockchip_pin_ctrl rk3576_pin_ctrl =
{
    .pin_banks      = rk3576_pin_banks,
    .banks_nr       = RT_ARRAY_SIZE(rk3576_pin_banks),
    .pins_nr        = 160,
    .grf_mux_offset = 0x0,
    .set_mux        = rk3576_set_mux,
    .set_pull       = rk3576_set_pull,
    .set_drive      = rk3576_set_drive,
    .set_schmitt    = rk3576_set_schmitt,
};

static rt_err_t rk3588_set_mux(struct rockchip_pin_bank *pin_bank, int pin, int mux)
{
    rt_err_t err;
    rt_uint8_t bit;
    rt_uint32_t data;
    int iomux_num = (pin / 8), reg, mask;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    regmap = drvdata->regmap_base;
    reg = pin_bank->iomux[iomux_num].offset;
    if (pin % 8 >= 4)
    {
        reg += 0x4;
    }
    bit = (pin % 4) * 4;
    mask = 0xf;

    if (pin_bank->bank_num == 0)
    {
        if (pin >= RK_PB4 && pin <= RK_PD7)
        {
            rt_uint32_t reg0 = 0;

            if (mux < 8)
            {
                /* PMU2_IOC_BASE */
                reg0 = reg + 0x4000 - 0xc;
                data = mask << (bit + 16);
                data |= (mux & mask) << bit;
                err = rt_syscon_write(regmap, reg0, data);

                /* BUS_IOC_BASE */
                reg0 = reg + 0x8000;
                data = (mask << (bit + 16));
                rt_syscon_write(regmap, reg0, data);
            }
            else
            {
                /* PMU2_IOC_BASE */
                reg0 = reg + 0x4000 - 0xc;
                data = mask << (bit + 16);
                data |= 8 << bit;
                err = rt_syscon_write(regmap, reg0, data);

                /* BUS_IOC_BASE */
                reg0 = reg + 0x8000;
                data = mask << (bit + 16);
                data |= mux << bit;
                rt_syscon_write(regmap, reg0, data);
            }
        }
        else
        {
            data = mask << (bit + 16);
            data |= (mux & mask) << bit;
            err = rt_syscon_write(regmap, reg, data);
        }

        return err;
    }
    else if (pin_bank->bank_num > 0)
    {
        /* BUS_IOC_BASE */
        reg += 0x8000;
    }

    data = mask << (bit + 16);
    data |= (mux & mask) << bit;

    return rt_syscon_write(regmap, reg, data);
}

#define RK3588_PMU1_IOC_REG     0x0000
#define RK3588_PMU2_IOC_REG     0x4000
#define RK3588_BUS_IOC_REG      0x8000
#define RK3588_VCCIO1_4_IOC_REG 0x9000
#define RK3588_VCCIO3_5_IOC_REG 0xa000
#define RK3588_VCCIO2_IOC_REG   0xb000
#define RK3588_VCCIO6_IOC_REG   0xc000
#define RK3588_EMMC_IOC_REG     0xd000

#define RK3588_PULL_BITS_PER_PIN 2
#define RK3588_PULL_PINS_PER_REG 8

static const rt_uint32_t rk3588_pull_regs[][2] =
{
    { RK_GPIO0_A0, RK3588_PMU1_IOC_REG + 0x0020 },
    { RK_GPIO0_B0, RK3588_PMU1_IOC_REG + 0x0024 },
    { RK_GPIO0_B5, RK3588_PMU2_IOC_REG + 0x0028 },
    { RK_GPIO0_C0, RK3588_PMU2_IOC_REG + 0x002c },
    { RK_GPIO0_D0, RK3588_PMU2_IOC_REG + 0x0030 },
    { RK_GPIO1_A0, RK3588_VCCIO1_4_IOC_REG + 0x0110 },
    { RK_GPIO1_B0, RK3588_VCCIO1_4_IOC_REG + 0x0114 },
    { RK_GPIO1_C0, RK3588_VCCIO1_4_IOC_REG + 0x0118 },
    { RK_GPIO1_D0, RK3588_VCCIO1_4_IOC_REG + 0x011c },
    { RK_GPIO2_A0, RK3588_EMMC_IOC_REG + 0x0120 },
    { RK_GPIO2_A6, RK3588_VCCIO3_5_IOC_REG + 0x0120 },
    { RK_GPIO2_B0, RK3588_VCCIO3_5_IOC_REG + 0x0124 },
    { RK_GPIO2_C0, RK3588_VCCIO3_5_IOC_REG + 0x0128 },
    { RK_GPIO2_D0, RK3588_EMMC_IOC_REG + 0x012c },
    { RK_GPIO3_A0, RK3588_VCCIO3_5_IOC_REG + 0x0130 },
    { RK_GPIO3_B0, RK3588_VCCIO3_5_IOC_REG + 0x0134 },
    { RK_GPIO3_C0, RK3588_VCCIO3_5_IOC_REG + 0x0138 },
    { RK_GPIO3_D0, RK3588_VCCIO3_5_IOC_REG + 0x013c },
    { RK_GPIO4_A0, RK3588_VCCIO6_IOC_REG + 0x0140 },
    { RK_GPIO4_B0, RK3588_VCCIO6_IOC_REG + 0x0144 },
    { RK_GPIO4_C0, RK3588_VCCIO6_IOC_REG + 0x0148 },
    { RK_GPIO4_C2, RK3588_VCCIO3_5_IOC_REG + 0x0148 },
    { RK_GPIO4_D0, RK3588_VCCIO2_IOC_REG + 0x014c },
};

static rt_err_t rk3588_set_pull(struct rockchip_pin_bank *pin_bank, int pin, int pull)
{
    int reg, pull_value;
    rt_uint32_t data;
    rt_uint8_t bit, type;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    if (pull == PIN_CONFIG_BIAS_PULL_PIN_DEFAULT)
    {
        return -RT_ENOSYS;
    }

    for (int i = RT_ARRAY_SIZE(rk3588_pull_regs) - 1; i >= 0; --i)
    {
        if (pin >= rk3588_pull_regs[i][0])
        {
            reg = rk3588_pull_regs[i][1];
            reg += ((pin - rk3588_pull_regs[i][0]) / RK3588_PULL_PINS_PER_REG) * 4;
            bit = ((pin % 32) % RK3588_PULL_PINS_PER_REG) * RK3588_PULL_BITS_PER_PIN;

            goto _find;
        }
    }

    return -RT_EINVAL;

_find:
    regmap = drvdata->regmap_base;

    type = pin_bank->pull_type[pin / 8];
    pull_value = rockchip_translate_pull_value(type, pull);

    if (pull_value < 0)
    {
        LOG_E("Not supported pull = %d, fixup the code or firmware", pull);

        return pull_value;
    }

    /* enable the write to the equivalent lower bits */
    data = ((1 << ROCKCHIP_PULL_BITS_PER_PIN) - 1) << (bit + 16);
    data |= pull_value << bit;

    return rt_syscon_write(regmap, reg, data);
}

#define RK3588_DRV_BITS_PER_PIN 4
#define RK3588_DRV_PINS_PER_REG 4

static const rt_uint32_t rk3588_drive_regs[][2] =
{
    { RK_GPIO0_A0, RK3588_PMU1_IOC_REG + 0x0010 },
    { RK_GPIO0_A4, RK3588_PMU1_IOC_REG + 0x0014 },
    { RK_GPIO0_B0, RK3588_PMU1_IOC_REG + 0x0018 },
    { RK_GPIO0_B4, RK3588_PMU2_IOC_REG + 0x0014 },
    { RK_GPIO0_C0, RK3588_PMU2_IOC_REG + 0x0018 },
    { RK_GPIO0_C4, RK3588_PMU2_IOC_REG + 0x001c },
    { RK_GPIO0_D0, RK3588_PMU2_IOC_REG + 0x0020 },
    { RK_GPIO0_D4, RK3588_PMU2_IOC_REG + 0x0024 },
    { RK_GPIO1_A0, RK3588_VCCIO1_4_IOC_REG + 0x0020 },
    { RK_GPIO1_A4, RK3588_VCCIO1_4_IOC_REG + 0x0024 },
    { RK_GPIO1_B0, RK3588_VCCIO1_4_IOC_REG + 0x0028 },
    { RK_GPIO1_B4, RK3588_VCCIO1_4_IOC_REG + 0x002c },
    { RK_GPIO1_C0, RK3588_VCCIO1_4_IOC_REG + 0x0030 },
    { RK_GPIO1_C4, RK3588_VCCIO1_4_IOC_REG + 0x0034 },
    { RK_GPIO1_D0, RK3588_VCCIO1_4_IOC_REG + 0x0038 },
    { RK_GPIO1_D4, RK3588_VCCIO1_4_IOC_REG + 0x003c },
    { RK_GPIO2_A0, RK3588_EMMC_IOC_REG + 0x0040 },
    { RK_GPIO2_A4, RK3588_VCCIO3_5_IOC_REG + 0x0044 },
    { RK_GPIO2_B0, RK3588_VCCIO3_5_IOC_REG + 0x0048 },
    { RK_GPIO2_B4, RK3588_VCCIO3_5_IOC_REG + 0x004c },
    { RK_GPIO2_C0, RK3588_VCCIO3_5_IOC_REG + 0x0050 },
    { RK_GPIO2_C4, RK3588_VCCIO3_5_IOC_REG + 0x0054 },
    { RK_GPIO2_D0, RK3588_EMMC_IOC_REG + 0x0058 },
    { RK_GPIO2_D4, RK3588_EMMC_IOC_REG + 0x005c },
    { RK_GPIO3_A0, RK3588_VCCIO3_5_IOC_REG + 0x0060 },
    { RK_GPIO3_A4, RK3588_VCCIO3_5_IOC_REG + 0x0064 },
    { RK_GPIO3_B0, RK3588_VCCIO3_5_IOC_REG + 0x0068 },
    { RK_GPIO3_B4, RK3588_VCCIO3_5_IOC_REG + 0x006c },
    { RK_GPIO3_C0, RK3588_VCCIO3_5_IOC_REG + 0x0070 },
    { RK_GPIO3_C4, RK3588_VCCIO3_5_IOC_REG + 0x0074 },
    { RK_GPIO3_D0, RK3588_VCCIO3_5_IOC_REG + 0x0078 },
    { RK_GPIO3_D4, RK3588_VCCIO3_5_IOC_REG + 0x007c },
    { RK_GPIO4_A0, RK3588_VCCIO6_IOC_REG + 0x0080 },
    { RK_GPIO4_A4, RK3588_VCCIO6_IOC_REG + 0x0084 },
    { RK_GPIO4_B0, RK3588_VCCIO6_IOC_REG + 0x0088 },
    { RK_GPIO4_B4, RK3588_VCCIO6_IOC_REG + 0x008c },
    { RK_GPIO4_C0, RK3588_VCCIO6_IOC_REG + 0x0090 },
    { RK_GPIO4_C2, RK3588_VCCIO3_5_IOC_REG + 0x0090 },
    { RK_GPIO4_C4, RK3588_VCCIO3_5_IOC_REG + 0x0094 },
    { RK_GPIO4_D0, RK3588_VCCIO2_IOC_REG + 0x0098 },
    { RK_GPIO4_D4, RK3588_VCCIO2_IOC_REG + 0x009c },
};

static rt_err_t rk3588_set_drive(struct rockchip_pin_bank *pin_bank, int pin, int strength)
{
    int reg;
    rt_uint8_t bit;
    rt_uint32_t data;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    for (int i = RT_ARRAY_SIZE(rk3588_drive_regs) - 1; i >= 0; --i)
    {
        if (pin >= rk3588_drive_regs[i][0])
        {
            reg = rk3588_drive_regs[i][1];
            reg += ((pin - rk3588_drive_regs[i][0]) / RK3588_DRV_PINS_PER_REG) * 4;
            bit = ((pin % 32) % RK3588_DRV_PINS_PER_REG) * RK3588_DRV_BITS_PER_PIN;

            goto _find;
        }
    }

    return -RT_EINVAL;

_find:
    regmap = drvdata->regmap_base;

    /* enable the write to the equivalent lower bits */
    data = ((1 << ROCKCHIP_DRV_BITS_PER_PIN) - 1) << (bit + 16);
    data |= (strength << bit);

    return rt_syscon_write(regmap, reg, data);
}

#define RK3588_SMT_BITS_PER_PIN 1
#define RK3588_SMT_PINS_PER_REG 8

static const rt_uint32_t rk3588_schmitt_regs[][2] =
{
    { RK_GPIO0_A0, RK3588_PMU1_IOC_REG + 0x0030 },
    { RK_GPIO0_B0, RK3588_PMU1_IOC_REG + 0x0034 },
    { RK_GPIO0_B5, RK3588_PMU2_IOC_REG + 0x0040 },
    { RK_GPIO0_C0, RK3588_PMU2_IOC_REG + 0x0044 },
    { RK_GPIO0_D0, RK3588_PMU2_IOC_REG + 0x0048 },
    { RK_GPIO1_A0, RK3588_VCCIO1_4_IOC_REG + 0x0210 },
    { RK_GPIO1_B0, RK3588_VCCIO1_4_IOC_REG + 0x0214 },
    { RK_GPIO1_C0, RK3588_VCCIO1_4_IOC_REG + 0x0218 },
    { RK_GPIO1_D0, RK3588_VCCIO1_4_IOC_REG + 0x021c },
    { RK_GPIO2_A0, RK3588_EMMC_IOC_REG + 0x0220 },
    { RK_GPIO2_A6, RK3588_VCCIO3_5_IOC_REG + 0x0220 },
    { RK_GPIO2_B0, RK3588_VCCIO3_5_IOC_REG + 0x0224 },
    { RK_GPIO2_C0, RK3588_VCCIO3_5_IOC_REG + 0x0228 },
    { RK_GPIO2_D0, RK3588_EMMC_IOC_REG + 0x022c },
    { RK_GPIO3_A0, RK3588_VCCIO3_5_IOC_REG + 0x0230 },
    { RK_GPIO3_B0, RK3588_VCCIO3_5_IOC_REG + 0x0234 },
    { RK_GPIO3_C0, RK3588_VCCIO3_5_IOC_REG + 0x0238 },
    { RK_GPIO3_D0, RK3588_VCCIO3_5_IOC_REG + 0x023c },
    { RK_GPIO4_A0, RK3588_VCCIO6_IOC_REG + 0x0240 },
    { RK_GPIO4_B0, RK3588_VCCIO6_IOC_REG + 0x0244 },
    { RK_GPIO4_C0, RK3588_VCCIO6_IOC_REG + 0x0248 },
    { RK_GPIO4_C2, RK3588_VCCIO3_5_IOC_REG + 0x0248 },
    { RK_GPIO4_D0, RK3588_VCCIO2_IOC_REG + 0x024c },
};

static rt_err_t rk3588_set_schmitt(struct rockchip_pin_bank *pin_bank, int pin, int enable)
{
    int reg;
    rt_uint8_t bit;
    rt_uint32_t data;
    struct rt_syscon *regmap;
    struct rockchip_pin_data *drvdata = pin_bank->drvdata;

    for (int i = RT_ARRAY_SIZE(rk3588_schmitt_regs) - 1; i >= 0; --i)
    {
        if (pin >= rk3588_schmitt_regs[i][0])
        {
            reg = rk3588_schmitt_regs[i][1];
            reg += ((pin - rk3588_schmitt_regs[i][0]) / RK3588_SMT_PINS_PER_REG) * 4;
            bit = ((pin % 32) % RK3588_SMT_PINS_PER_REG) * RK3588_SMT_BITS_PER_PIN;

            goto _find;
        }
    }

    return -RT_EINVAL;

_find:
    regmap = drvdata->regmap_base;

    /* enable the write to the equivalent lower bits */
    data = ((1 << RK3588_SMT_BITS_PER_PIN) - 1) << (bit + 16);
    data |= (enable << bit);

    return rt_syscon_write(regmap, reg, data);
}

static struct rockchip_pin_bank rk3588_pin_banks[] =
{
    PIN_BANK_FLAGS_IOMUX_PULL(0, 32, "gpio0", IOMUX_WIDTH_4BIT, PULL_TYPE_IO_1V8_ONLY),
    PIN_BANK_FLAGS_IOMUX_PULL(1, 32, "gpio1", IOMUX_WIDTH_4BIT, PULL_TYPE_IO_1V8_ONLY),
    PIN_BANK_FLAGS_IOMUX_PULL(2, 32, "gpio2", IOMUX_WIDTH_4BIT, PULL_TYPE_IO_1V8_ONLY),
    PIN_BANK_FLAGS_IOMUX_PULL(3, 32, "gpio3", IOMUX_WIDTH_4BIT, PULL_TYPE_IO_1V8_ONLY),
    PIN_BANK_FLAGS_IOMUX_PULL(4, 32, "gpio4", IOMUX_WIDTH_4BIT, PULL_TYPE_IO_1V8_ONLY),
};

static struct rockchip_pin_ctrl rk3588_pin_ctrl =
{
    .pin_banks      = rk3588_pin_banks,
    .banks_nr       = RT_ARRAY_SIZE(rk3588_pin_banks),
    .label          = "RK3588-GPIO",
    .type           = RK3588,
    .set_mux        = rk3588_set_mux,
    .set_pull       = rk3588_set_pull,
    .set_drive      = rk3588_set_drive,
    .set_schmitt    = rk3588_set_schmitt,
};

static const struct rt_pin_ctrl_conf_params rockchip_conf_params[] =
{
    { "bias-disable", PIN_CONFIG_BIAS_DISABLE, 0 },
    { "bias-bus-hold", PIN_CONFIG_BIAS_BUS_HOLD, 0 },
    { "bias-pull-up", PIN_CONFIG_BIAS_PULL_UP, 1 },
    { "bias-pull-down", PIN_CONFIG_BIAS_PULL_DOWN, 1 },
    { "bias-pull-pin-default", PIN_CONFIG_BIAS_PULL_PIN_DEFAULT, 1 },
    { "drive-strength", PIN_CONFIG_DRIVE_STRENGTH, 0 },
    { "input-schmitt-disable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, 0 },
    { "input-schmitt-enable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, 1 },
};

static int rockchip_pinconf_prop_name_to_param(const char *propname, rt_uint32_t *default_value)
{
    const struct rt_pin_ctrl_conf_params *params = rockchip_conf_params;

    for (int i = 0; i < RT_ARRAY_SIZE(rockchip_conf_params); ++i, ++params)
    {
        if (!rt_strcmp(params->propname, propname))
        {
            *default_value = params->default_value;

            return params->param;
        }
    }

    return -RT_ENOSYS;
}

static rt_err_t rockchip_pinconf_pull_apply(struct rockchip_pin_ctrl *pinctrl,
        struct rockchip_pin_bank *pin_bank, rt_uint32_t pin, rt_uint32_t param, rt_uint32_t arg)
{
    rt_err_t err = RT_EOK;

    switch (param)
    {
    case PIN_CONFIG_BIAS_DISABLE:
    case PIN_CONFIG_BIAS_PULL_UP:
    case PIN_CONFIG_BIAS_PULL_DOWN:
    case PIN_CONFIG_BIAS_PULL_PIN_DEFAULT:
    case PIN_CONFIG_BIAS_BUS_HOLD:
        if (pinctrl->set_pull)
        {
            err = pinctrl->set_pull(pin_bank, pin, param);
        }
        else
        {
            err = -RT_ENOSYS;
        }
        break;

    case PIN_CONFIG_DRIVE_STRENGTH:
        if (pinctrl->set_drive)
        {
            err = pinctrl->set_drive(pin_bank, pin, arg);
        }
        else
        {
            err = -RT_ENOSYS;
        }
        break;

    case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
        if (pinctrl->set_schmitt)
        {
            err = pinctrl->set_schmitt(pin_bank, pin, arg);
        }
        else
        {
            err = -RT_ENOSYS;
        }
        break;

    default:
        break;
    }

    return err;
}

static rt_err_t rockchip_pinctrl_confs_apply(struct rt_device *device, void *fw_conf_np)
{
    rt_err_t err = RT_EOK;
    const fdt32_t *cell;
    int pin, function, param;
    rt_uint32_t value, default_value, arg;
    struct rt_ofw_prop *prop, *pin_prop;
    struct rt_ofw_node *pull_np, *conf_np = fw_conf_np;
    struct rockchip_pin_ctrl *pinctrl;
    struct rockchip_pin_bank *pin_bank;
    struct rockchip_pinctrl_device *pinctrl_dev;

    LOG_D("Pinctrl apply '%s'", rt_ofw_node_full_name(conf_np));

    pinctrl_dev = rt_container_of(device, struct rockchip_pinctrl_device, parent);
    pinctrl = pinctrl_dev->pinctrl;

    rt_ofw_foreach_prop_u32(conf_np, "rockchip,pins", prop, cell, value)
    {
        /* bank -> pin -> function -> pull */
        pin_bank = &pinctrl->pin_banks[value];

        cell = rt_ofw_prop_next_u32(prop, cell, &value);
        pin = value;

        cell = rt_ofw_prop_next_u32(prop, cell, &value);
        function = value;

        cell = rt_ofw_prop_next_u32(prop, cell, &value);
        pull_np = rt_ofw_find_node_by_phandle(value);

        if (!pull_np)
        {
            err = -RT_ERROR;
            LOG_E("Firmware ref error in '%s'", rt_ofw_node_full_name(conf_np));

            break;
        }

        if (pinctrl->set_mux)
        {
            LOG_D("IOMUX from GPIO%d-%c%d to function(%d)",
                    pin_bank->bank_num, 'A' + (pin % 32) / 8, pin % 8, function);

            err = pinctrl->set_mux(pin_bank, pin, function);

            if (err)
            {
                break;
            }
        }

        rt_ofw_foreach_prop(pull_np, pin_prop)
        {
            if (!rt_strcmp(pin_prop->name, "phandle"))
            {
                continue;
            }

            param = rockchip_pinconf_prop_name_to_param(pin_prop->name, &default_value);

            if (param < 0)
            {
                err = param;

                break;
            }

            if (pin_prop->length < sizeof(*cell))
            {
                arg = default_value;
            }
            else
            {
                rt_ofw_prop_next_u32(pin_prop, RT_NULL, &arg);
            }

            err = rockchip_pinconf_pull_apply(pinctrl, pin_bank, pin, param, arg);

            if (err && err != -RT_ENOSYS)
            {
                break;
            }
        }

        rt_ofw_node_put(pull_np);
    }

    return err;
}

static const struct rt_pin_ops rockchip_pinctrl_ops =
{
    .pin_ctrl_confs_apply = rockchip_pinctrl_confs_apply,
};

static rt_err_t rockchip_pinctrl_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    int grf_offs, pmu_offs, drv_grf_offs, drv_pmu_offs;
    struct rockchip_pin_data *drvdata = RT_NULL;
    struct rt_ofw_node *np = pdev->parent.ofw_node;
    struct rockchip_pin_ctrl *pinctrl = (typeof(pinctrl))pdev->id->data;
    struct rockchip_pin_bank *pin_bank = pinctrl->pin_banks;
    struct rockchip_pinctrl_device *pinctrl_dev = rt_malloc(sizeof(*pinctrl_dev));

    if (!pinctrl_dev)
    {
        return -RT_ENOMEM;
    }

    drvdata = &pinctrl_dev->drvdata;

    if (!(drvdata->regmap_base = rt_syscon_find_by_ofw_phandle(np, "rockchip,grf")))
    {
        err = -RT_EIO;
        goto _fail;
    }

    drvdata->regmap_pmu = rt_syscon_find_by_ofw_phandle(np, "rockchip,pmu");
    drvdata->pinctrl = pinctrl;

    pinctrl_dev->parent.ops = &rockchip_pinctrl_ops;
    pinctrl_dev->pinctrl = pinctrl;
    pinctrl->pins_nr = 0;

    grf_offs = pinctrl->grf_mux_offset;
    pmu_offs = pinctrl->pmu_mux_offset;
    drv_pmu_offs = pinctrl->pmu_drv_offset;
    drv_grf_offs = pinctrl->grf_drv_offset;
    pin_bank = pinctrl->pin_banks;

    for (int i = 0; i < pinctrl->banks_nr; ++i, ++pin_bank)
    {
        for (int bank_pins = 0, j = 0; j < 4; ++j)
        {
            int inc;
            struct rockchip_drv *drv = &pin_bank->drv[j];
            struct rockchip_iomux *iomux = &pin_bank->iomux[j];

            if (bank_pins >= pin_bank->nr_pins)
            {
                break;
            }

            /* Preset iomux offset value, set new start value */
            if (iomux->offset >= 0)
            {
                if ((iomux->type & IOMUX_SOURCE_PMU) || (iomux->type & IOMUX_L_SOURCE_PMU))
                {
                    pmu_offs = iomux->offset;
                }
                else
                {
                    grf_offs = iomux->offset;
                }
            }
            else
            {
                /* Set current iomux offset */
                iomux->offset = ((iomux->type & IOMUX_SOURCE_PMU) || (iomux->type & IOMUX_L_SOURCE_PMU)) ?
                        pmu_offs : grf_offs;
            }

            /* Preset drv offset value, set new start value */
            if (drv->offset >= 0)
            {
                if (iomux->type & IOMUX_SOURCE_PMU)
                {
                    drv_pmu_offs = drv->offset;
                }
                else
                {
                    drv_grf_offs = drv->offset;
                }
            }
            else
            {
                /* Set current drv offset */
                drv->offset = (iomux->type & IOMUX_SOURCE_PMU) ? drv_pmu_offs : drv_grf_offs;
            }

            /*
             * Increase offset according to iomux width.
             * 4bit iomux'es are spread over two registers.
             */
            inc = (iomux->type & (IOMUX_WIDTH_4BIT | IOMUX_WIDTH_3BIT | IOMUX_WIDTH_2BIT)) ? 8 : 4;

            /* Preset drv offset value, set new start value */
            if ((iomux->type & IOMUX_SOURCE_PMU) || (iomux->type & IOMUX_L_SOURCE_PMU))
            {
                pmu_offs += inc;
            }
            else
            {
                grf_offs += inc;
            }

            /*
             * Increase offset according to drv width.
             * 3bit drive-strenth'es are spread over two registers.
             */
            inc = ((drv->drv_type == DRV_TYPE_IO_1V8_3V0_AUTO) || (drv->drv_type == DRV_TYPE_IO_3V3_ONLY)) ? 8 : 4;

            if (iomux->type & IOMUX_SOURCE_PMU)
            {
                drv_pmu_offs += inc;
            }
            else
            {
                drv_grf_offs += inc;
            }

            bank_pins += 8;
        }

        /* calculate the per-bank recalced_mask */
        for (int pin = 0, j = 0; j < pinctrl->niomux_recalced; ++j)
        {
            if (pinctrl->iomux_recalced[j].num == pin_bank->bank_num)
            {
                pin = pinctrl->iomux_recalced[j].pin;
                pin_bank->recalced_mask |= RT_BIT(pin);
            }
        }

        /* calculate the per-bank route_mask */
        for (int pin = 0, j = 0; j < pinctrl->niomux_routes; ++j)
        {
            if (pinctrl->iomux_routes[j].bank_num == pin_bank->bank_num)
            {
                pin = pinctrl->iomux_routes[j].pin;
                pin_bank->route_mask |= RT_BIT(pin);
            }
        }

        pin_bank->drvdata = drvdata;
        rt_spin_lock_init(&pin_bank->spinlock);

        pinctrl->pins_nr += pin_bank->nr_pins;
    }

    rt_ofw_data(np) = &pinctrl_dev->parent;

    return RT_EOK;

_fail:
    rt_free(pinctrl_dev);

    return err;
}

static const struct rt_ofw_node_id rockchip_pinctrl_ofw_ids[] =
{
    { .compatible = "rockchip,rk3308-pinctrl", .data = &rk3308_pin_ctrl },
    { .compatible = "rockchip,rk3568-pinctrl", .data = &rk3568_pin_ctrl },
    { .compatible = "rockchip,rk3576-pinctrl", .data = &rk3576_pin_ctrl },
    { .compatible = "rockchip,rk3588-pinctrl", .data = &rk3588_pin_ctrl },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_pinctrl_driver =
{
    .name = "pinctrl-rockchip",
    .ids = rockchip_pinctrl_ofw_ids,

    .probe = rockchip_pinctrl_probe,
};

static int rockchip_pinctrl_register(void)
{
    rt_platform_driver_register(&rockchip_pinctrl_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(rockchip_pinctrl_register);
