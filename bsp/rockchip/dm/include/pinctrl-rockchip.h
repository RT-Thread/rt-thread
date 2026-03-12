/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __ROCKCHIP_PINCTRL_H__
#define __ROCKCHIP_PINCTRL_H__

#include <rthw.h>
#include <rtdef.h>

#include <rockchip.h>
#include <dt-bindings/pinctrl/rockchip.h>

#define ROCKCHIP_PULL_BITS_PER_PIN  2
#define ROCKCHIP_PULL_PINS_PER_REG  8
#define ROCKCHIP_PULL_BANK_STRIDE   16
#define ROCKCHIP_DRV_BITS_PER_PIN   2
#define ROCKCHIP_DRV_PINS_PER_REG   8
#define ROCKCHIP_DRV_BANK_STRIDE    16
#define ROCKCHIP_DRV_3BITS_PER_PIN  3

enum rockchip_pin_drv_type
{
    DRV_TYPE_IO_DEFAULT = 0,
    DRV_TYPE_IO_1V8_OR_3V0,
    DRV_TYPE_IO_1V8_ONLY,
    DRV_TYPE_IO_1V8_3V0_AUTO,
    DRV_TYPE_IO_3V3_ONLY,
    DRV_TYPE_MAX
};

enum rockchip_pin_pull_type
{
    PULL_TYPE_IO_DEFAULT = 0,
    PULL_TYPE_IO_1V8_ONLY,
    PULL_TYPE_IO_1 = 1,
    PULL_TYPE_MAX
};

enum rockchip_pinctrl_type
{
    RK3308,
    RK3568,
    RK3588,
};

struct rockchip_gpio_regs
{
    rt_uint32_t port_dr;        /* Data register */
    rt_uint32_t port_ddr;       /* Data direction register */
    rt_uint32_t int_en;         /* Interrupt enable */
    rt_uint32_t int_mask;       /* Interrupt mask */
    rt_uint32_t int_type;       /* Interrupt trigger type, such as high, low, edge trriger type. */
    rt_uint32_t int_polarity;   /* Interrupt polarity enable register */
    rt_uint32_t int_bothedge;   /* Interrupt bothedge enable register */
    rt_uint32_t int_status;     /* Interrupt status register */
    rt_uint32_t int_rawstatus;  /* Int_status = int_rawstatus & int_mask */
    rt_uint32_t debounce;       /* Enable debounce for interrupt signal */
    rt_uint32_t dbclk_div_en;   /* Enable divider for debounce clock */
    rt_uint32_t dbclk_div_con;  /* Setting for divider of debounce clock */
    rt_uint32_t port_eoi;       /* End of interrupt of the port */
    rt_uint32_t ext_port;       /* Port data from external */
    rt_uint32_t version_id;     /* Controller version register */
};

struct rockchip_iomux
{
    int type;
    int offset;
};

struct rockchip_drv
{
    enum rockchip_pin_drv_type drv_type;
    int offset;
};

struct rockchip_pin_data
{
    struct rt_syscon *regmap_base;
    struct rt_syscon *regmap_pmu;
    rt_size_t reg_size;

    struct rockchip_pin_ctrl *pinctrl;
};

struct rockchip_pin_bank
{
    struct rt_device_pin parent;

    const char *name;

    int irq;
    void *reg_base;
    struct rt_clk *clk;
    struct rt_clk *db_clk;

    rt_uint8_t nr_pins;
    rt_uint8_t bank_num;
    rt_uint32_t gpio_type;
    rt_uint32_t mask_cache;
    rt_uint32_t toggle_edge_mode;
    struct rockchip_pin_data *drvdata;
    const struct rockchip_gpio_regs *gpio_regs;

    struct rockchip_iomux iomux[4];
    struct rockchip_drv drv[4];
    enum rockchip_pin_pull_type pull_type[4];
    struct rt_spinlock spinlock;

    rt_uint32_t route_mask;
    rt_uint32_t recalced_mask;
};

#define raw_pin_to_bank(raw)    rt_container_of(raw, struct rockchip_pin_bank, parent)

struct rockchip_mux_recalced_data
{
    rt_uint8_t num;
    rt_uint8_t pin;
    rt_uint32_t reg;
    rt_uint8_t bit;
    rt_uint8_t mask;
};

enum rockchip_mux_route_location
{
    ROCKCHIP_ROUTE_SAME = 0,
    ROCKCHIP_ROUTE_PMU,
    ROCKCHIP_ROUTE_GRF,
};

struct rockchip_mux_route_data
{
    rt_uint8_t bank_num;
    rt_uint8_t pin;
    rt_uint8_t func;
    enum rockchip_mux_route_location route_location;
    rt_uint32_t route_offset;
    rt_uint32_t route_val;
};

struct rockchip_pin_ctrl
{
    char *label;
    enum rockchip_pinctrl_type type;

    struct rockchip_pin_bank *pin_banks;
    rt_uint32_t banks_nr;
    rt_uint32_t pins_nr;

    int grf_mux_offset;
    int pmu_mux_offset;
    int grf_drv_offset;
    int pmu_drv_offset;

    struct rockchip_mux_recalced_data *iomux_recalced;
    rt_uint32_t niomux_recalced;

    struct rockchip_mux_route_data *iomux_routes;
    rt_uint32_t niomux_routes;

    rt_err_t (*set_mux)(struct rockchip_pin_bank *pin_bank, int pin, int mux);
    rt_err_t (*set_pull)(struct rockchip_pin_bank *pin_bank, int pin, int pull);
    rt_err_t (*set_drive)(struct rockchip_pin_bank *pin_bank, int pin, int strength);
    rt_err_t (*set_schmitt)(struct rockchip_pin_bank *pin_bank, int pin, int enable);
};

struct rockchip_pinctrl_device
{
    struct rt_device_pin parent;

    struct rockchip_pin_data drvdata;
    struct rockchip_pin_ctrl *pinctrl;
};

#endif /* __ROCKCHIP_PINCTRL_H__ */
