/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __SPACEMIT_PMIC_H__
#define __SPACEMIT_PMIC_H__

#include <rtthread.h>
#include <rtdevice.h>

struct spacemit_pmic_mfd_data;

struct spacemit_pmic
{
    int irq;
    int addr_offset;
    struct rt_device *dev;
    const struct spacemit_pmic_mfd_data *mfd_data;

    unsigned (*read)(struct spacemit_pmic *pmic, unsigned reg);
    rt_err_t (*write)(struct spacemit_pmic *pmic, unsigned reg, unsigned data);
    rt_err_t (*write_bit)(struct spacemit_pmic *pmic, unsigned reg, unsigned mask, unsigned data);
    rt_err_t (*update_bits)(struct spacemit_pmic *pmic, unsigned reg, unsigned mask, unsigned data);
};

struct spacemit_pmic_irq_map
{
    rt_uint32_t reg_offset;
    rt_uint32_t mask;
};

struct spacemit_pmic_irqchip
{
    struct rt_pic parent;

    struct spacemit_pmic *pmic;

    rt_uint32_t *irq_status;

    int num_regs;
    int reg_stride;
    int mask_base;
    int status_base;
    int ack_base;

    rt_bool_t init_ack_masked;
    rt_bool_t mask_unmask_non_inverted;

    int irqs_nr;
    const struct spacemit_pmic_irq_map *irqs_map;

    struct rt_thread *irq_thread;
};

#define raw_to_spacemit_pmic_irqchip(raw) rt_container_of(raw, struct spacemit_pmic_irqchip, parent)

struct spacemit_pmic_regmap_config
{
    rt_uint8_t reg_bits;
    rt_uint8_t val_bits;
    rt_uint16_t max_register;
};

struct spacemit_pmic_mfd_endpoint
{
    const char *ofw_name;
    const char *ofw_compatible;

    int irqs_nr;
    const int *irqs_list;
};

struct spacemit_pmic_mfd_data
{
    struct spacemit_pmic_regmap_config regmap_cfg;

    struct spacemit_pmic_mfd_endpoint *endpoint;
    rt_uint32_t endpoint_num;

    struct spacemit_pmic_irqchip *irqchip;

    /* Shutdown - reboot support */
    struct
    {
        rt_uint8_t reg;
        rt_uint8_t bit;
    } shutdown;

    struct
    {
        rt_uint32_t reg;
        rt_uint8_t bit;
    } reboot;

    /* Value will be kept in register while reset pmic  */
    struct
    {
        rt_uint32_t reg;
        rt_uint8_t bit;
    } non_reset;
};

/* Regulator */
struct spacemit_pmic_regulator_range
{
    int min;
    int min_sel;
    int max_sel;
    int step;
};

#define SPACEMIT_PMIC_REGULATOR_RANGE(UVOLT_MIN, MIN_SEL, MAX_SEL, UVOLT_STEP) \
{                       \
    .min = UVOLT_MIN,   \
    .min_sel = MIN_SEL, \
    .max_sel = MAX_SEL, \
    .step = UVOLT_STEP, \
}

struct spacemit_pmic_regulator_desc
{
    const char *name;
    const char *match;
    const char *supply_name;

    const struct rt_regulator_ops *ops;

    rt_uint32_t id;

    int voltages_nr;
    int uvolt_min;
    int uvolt_step;

    int ranges_nr;
    const struct spacemit_pmic_regulator_range *ranges;

    rt_uint32_t vsel_reg;
    rt_uint32_t vsel_mask;
    rt_uint32_t enable_reg;
    rt_uint32_t enable_mask;
    rt_uint32_t enable_val;
    rt_uint32_t disable_val;
};

#define SPACEMIT_PMIC_REGULATOR_DESC(ID, NAME,  \
        SUPPLY_NAME, OPS,                       \
        VOLTAGES_NR, UVOLT_MIN, UVOLT_STEP,     \
        RANGES_NR, RANGES,                      \
        VSEL_REG, VSEL_MASK, ENABLE_REG,        \
        ENABLE_MASK, ENABLE_VAL, DISABLE_VAL)   \
{                                               \
    .name = NAME,                               \
    .supply_name = SUPPLY_NAME,                 \
    .ops = &OPS,                                \
    .id = ID,                                   \
    .voltages_nr = VOLTAGES_NR,                 \
    .uvolt_min = UVOLT_MIN,                     \
    .uvolt_step = UVOLT_STEP,                   \
    .ranges_nr = RANGES_NR,                     \
    .ranges = RANGES,                           \
    .vsel_reg = VSEL_REG,                       \
    .vsel_mask = VSEL_MASK,                     \
    .enable_reg = ENABLE_REG,                   \
    .enable_mask = ENABLE_MASK,                 \
    .enable_val = ENABLE_VAL,                   \
    .disable_val = DISABLE_VAL,                 \
}

#define SPACEMIT_PMIC_REGULATOR_DESC_COMMON(ID, \
    NAME, SUPPLY_NAME, VOLTAGES_NR, VSEL_REG,   \
    VSEL_MASK, ENABLE_REG, ENABLE_MASK, RANGES, \
    OPS)                                        \
    SPACEMIT_PMIC_REGULATOR_DESC(ID, NAME,      \
            SUPPLY_NAME, OPS,                   \
            VOLTAGES_NR, 0, 0,                  \
            RT_ARRAY_SIZE(RANGES), RANGES,      \
            VSEL_REG, VSEL_MASK, ENABLE_REG,    \
            ENABLE_MASK, 0, 0)

#define SPACEMIT_PMIC_REGULATOR_DESC_SWITCH_COM(\
    ID, NAME, SUPPLY_NAME,                      \
    ENABLE_REG, ENABLE_MASK,                    \
    ENABLE_VAL, DISABLE_VAL, OPS)               \
    SPACEMIT_PMIC_REGULATOR_DESC(ID, NAME,      \
            SUPPLY_NAME, OPS,                   \
            0, 0, 0,                            \
            0, RT_NULL,                         \
            0, 0, ENABLE_REG,                   \
            ENABLE_MASK, ENABLE_VAL, DISABLE_VAL)

struct spacemit_pmic_regulator_data
{
    const struct spacemit_pmic_regulator_desc *desc;
    rt_uint32_t desc_nr;
    int sleep_reg_offset;
};

/* Pinctrl */
struct spacemit_pmic_pin_func_desc
{
    const char *name;
    rt_uint8_t pin_id;
    rt_uint8_t func_reg;
    rt_uint8_t func_mask;
    rt_uint8_t en_val;
    rt_uint8_t ha_sub;
    rt_uint8_t sub_reg;
    rt_uint8_t sub_mask;
    rt_uint8_t sube_val;
};

#define SPM8XX_DESC_PIN_FUNC_COM(_pin_id, _match,   \
        _ereg, _emask, _enval,                      \
        _hsub, _subreg, _submask, _subenval)        \
{                                                   \
    .name           = (_match),                     \
    .pin_id         = (_pin_id),                    \
    .func_reg       = (_ereg),                      \
    .func_mask      = (_emask),                     \
    .en_val         = (_enval),                     \
    .ha_sub         = (_hsub),                      \
    .sub_reg        = (_subreg),                    \
    .sub_mask       = (_submask),                   \
    .sube_val       = (_subenval),                  \
}

struct spacemit_pmic_pin_config_desc
{
    rt_uint32_t pin_id;
    /* Input config desc */
    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } input;

    /* Output config desc */
    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } output;

    /* Pull-down desc */
    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } pup;

    /* Deb */
    struct
    {
        rt_uint8_t reg;
        rt_uint8_t timemsk;

        struct
        {
            rt_uint8_t msk;
        } en;
    } deb;

    /* OD */
    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } od;

    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } itype;
};

#define SPM8XX_DESC_PIN_CONFIG_COM(_pin_id,     \
    _ireg, _imsk, _oreg, _omsk,                 \
    _pureg, _pumsk,                             \
    _debreg, _debtmsk, _debemsk,                \
    _odreg, _odmsk,                             \
    _itypereg, _itypemsk)                       \
{                                               \
    .pin_id = (_pin_id),                        \
    .input =                                    \
    {                                           \
        .reg = (_ireg),                         \
        .msk = (_imsk),                         \
    },                                          \
    .output =                                   \
    {                                           \
        .reg = (_oreg),                         \
        .msk = (_omsk),                         \
    },                                          \
    .pup =                                      \
    {                                           \
        .reg = (_pureg),                        \
        .msk = (_pumsk),                        \
    },                                          \
    .deb =                                      \
    {                                           \
        .reg = (_debreg),                       \
        .timemsk = (_debtmsk),                  \
        .en.msk = (_debemsk)                    \
    },                                          \
    .od =                                       \
    {                                           \
        .reg = (_odreg),                        \
        .msk = (_odmsk),                        \
    },                                          \
    .itype =                                    \
    {                                           \
        .reg = (_itypereg),                     \
        .msk = (_itypemsk),                     \
    },                                          \
}

struct spacemit_pmic_pin_data
{
    int pin_mux_nr;
    const char **pinmux_funcs;

    int pin_fuc_desc_nr;
    const struct spacemit_pmic_pin_func_desc *pinfunc_desc;

    int pin_conf_desc_nr;
    const struct spacemit_pmic_pin_config_desc *pinconf_desc;
};

/* RTC */
union spacemit_pmic_rtc_ctl_desc
{
    rt_uint32_t val;
    struct
    {
        rt_uint32_t crystal_en:1;
        rt_uint32_t out_32k_en:1;
        rt_uint32_t rtc_en:1;
        rt_uint32_t rtc_clk_sel:1;
        rt_uint32_t tick_type:1;
        rt_uint32_t alarm_en:1;
        rt_uint32_t tick_en:1;
        rt_uint32_t reserved:25;
    } bits;
};

struct spacemit_pmic_rtc_regdesc
{
    /* Seconds */
    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } cnt_s;

    /* Mini */
    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } cnt_mi;

    /* Hour */
    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } cnt_h;

    /* Day */
    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } cnt_d;

    /* Mounth */
    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } cnt_mo;

    /* Year */
    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } cnt_y;

    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } alarm_s;

    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } alarm_mi;

    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } alarm_h;

    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } alarm_d;

    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } alarm_mo;

    struct
    {
        rt_uint8_t reg;
        rt_uint8_t msk;
    } alarm_y;

    struct
    {
        rt_uint8_t reg;
    } rtc_ctl;
};

/* IIO */
struct spacemit_pmic_iio_chan_spec
{
    int channel;
};

struct spacemit_pmic_adc_data
{
    int iio_desc_nr;
    struct spacemit_pmic_iio_chan_spec *iio_desc;
};

#include "spm8821.h"
#include "pm853.h"
#include "sy8810l.h"

rt_inline unsigned spacemit_pmic_read(struct spacemit_pmic *pmic, unsigned reg)
{
    return pmic->read(pmic, reg);
}

rt_inline rt_err_t spacemit_pmic_write(struct spacemit_pmic *pmic, unsigned reg, unsigned data)
{
    return pmic->write(pmic, reg, data);
}

rt_inline rt_err_t spacemit_pmic_write_bit(struct spacemit_pmic *pmic, unsigned reg,
        unsigned mask, unsigned data)
{
    return pmic->write_bit(pmic, reg, mask, data);
}

rt_inline rt_err_t spacemit_pmic_update_bits(struct spacemit_pmic *pmic, unsigned reg,
        unsigned mask, unsigned data)
{
    return pmic->update_bits(pmic, reg, mask, data);
}

#endif /* __SPACEMIT_PMIC_H__ */
