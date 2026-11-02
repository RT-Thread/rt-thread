/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pinctrl.rp1"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <bitmap.h>
#include <dev_pin_dm.h>

#define RP1_NUM_GPIOS                   54
#define RP1_NUM_BANKS                   3

#define RP1_RW_OFFSET                   0x0000
#define RP1_XOR_OFFSET                  0x1000
#define RP1_SET_OFFSET                  0x2000
#define RP1_CLR_OFFSET                  0x3000

#define RP1_GPIO_STATUS                 0x0000
#define RP1_GPIO_CTRL                   0x0004

#define RP1_GPIO_PCIE_INTE              0x011c
#define RP1_GPIO_PCIE_INTS              0x0124

#define RP1_GPIO_EVENTS_SHIFT_RAW       20
#define RP1_GPIO_STATUS_FALLING         RT_BIT(20)
#define RP1_GPIO_STATUS_RISING          RT_BIT(21)
#define RP1_GPIO_STATUS_LOW             RT_BIT(22)
#define RP1_GPIO_STATUS_HIGH            RT_BIT(23)

#define RP1_GPIO_EVENTS_SHIFT_FILTERED  24
#define RP1_GPIO_STATUS_F_FALLING       RT_BIT(24)
#define RP1_GPIO_STATUS_F_RISING        RT_BIT(25)
#define RP1_GPIO_STATUS_F_LOW           RT_BIT(26)
#define RP1_GPIO_STATUS_F_HIGH          RT_BIT(27)

#define RP1_GPIO_CTRL_FUNCSEL_LSB       0
#define RP1_GPIO_CTRL_FUNCSEL_MASK      0x0000001f
#define RP1_GPIO_CTRL_OUTOVER_LSB       12
#define RP1_GPIO_CTRL_OUTOVER_MASK      0x00003000
#define RP1_GPIO_CTRL_OEOVER_LSB        14
#define RP1_GPIO_CTRL_OEOVER_MASK       0x0000c000
#define RP1_GPIO_CTRL_INOVER_LSB        16
#define RP1_GPIO_CTRL_INOVER_MASK       0x00030000
#define RP1_GPIO_CTRL_IRQEN_FALLING     RT_BIT(20)
#define RP1_GPIO_CTRL_IRQEN_RISING      RT_BIT(21)
#define RP1_GPIO_CTRL_IRQEN_LOW         RT_BIT(22)
#define RP1_GPIO_CTRL_IRQEN_HIGH        RT_BIT(23)
#define RP1_GPIO_CTRL_IRQEN_F_FALLING   RT_BIT(24)
#define RP1_GPIO_CTRL_IRQEN_F_RISING    RT_BIT(25)
#define RP1_GPIO_CTRL_IRQEN_F_LOW       RT_BIT(26)
#define RP1_GPIO_CTRL_IRQEN_F_HIGH      RT_BIT(27)
#define RP1_GPIO_CTRL_IRQRESET          RT_BIT(28)
#define RP1_GPIO_CTRL_IRQOVER_LSB       30
#define RP1_GPIO_CTRL_IRQOVER_MASK      0xc0000000

#define RP1_INT_EDGE_FALLING            RT_BIT(0)
#define RP1_INT_EDGE_RISING             RT_BIT(1)
#define RP1_INT_LEVEL_LOW               RT_BIT(2)
#define RP1_INT_LEVEL_HIGH              RT_BIT(3)
#define RP1_INT_MASK                    0xf

#define RP1_INT_EDGE_BOTH               (RP1_INT_EDGE_FALLING | RP1_INT_EDGE_RISING)
#define RP1_PUD_OFF                     0
#define RP1_PUD_DOWN                    1
#define RP1_PUD_UP                      2

#define RP1_FSEL_COUNT                  9

#define RP1_FSEL_ALT0                   0x00
#define RP1_FSEL_GPIO                   0x05
#define RP1_FSEL_NONE                   0x09
#define RP1_FSEL_NONE_HW                0x1f

#define RP1_DIR_OUTPUT                  0
#define RP1_DIR_INPUT                   1

#define RP1_OUTOVER_PERI                0
#define RP1_OUTOVER_INVPERI             1
#define RP1_OUTOVER_LOW                 2
#define RP1_OUTOVER_HIGH                3

#define RP1_OEOVER_PERI                 0
#define RP1_OEOVER_INVPERI              1
#define RP1_OEOVER_DISABLE              2
#define RP1_OEOVER_ENABLE               3

#define RP1_INOVER_PERI                 0
#define RP1_INOVER_INVPERI              1
#define RP1_INOVER_LOW                  2
#define RP1_INOVER_HIGH                 3

#define RP1_RIO_OUT                     0x00
#define RP1_RIO_OE                      0x04
#define RP1_RIO_IN                      0x08

#define RP1_PAD_SLEWFAST_MASK           0x00000001
#define RP1_PAD_SLEWFAST_LSB            0
#define RP1_PAD_SCHMITT_MASK            0x00000002
#define RP1_PAD_SCHMITT_LSB             1
#define RP1_PAD_PULL_MASK               0x0000000c
#define RP1_PAD_PULL_LSB                2
#define RP1_PAD_DRIVE_MASK              0x00000030
#define RP1_PAD_DRIVE_LSB               4
#define RP1_PAD_IN_ENABLE_MASK          0x00000040
#define RP1_PAD_IN_ENABLE_LSB           6
#define RP1_PAD_OUT_DISABLE_MASK        0x00000080
#define RP1_PAD_OUT_DISABLE_LSB         7

#define RP1_PAD_DRIVE_2MA               0x00000000
#define RP1_PAD_DRIVE_4MA               0x00000010
#define RP1_PAD_DRIVE_8MA               0x00000020
#define RP1_PAD_DRIVE_12MA              0x00000030

#define FLD_GET(r, f)                   (((r) & (f ## _MASK)) >> (f ## _LSB))
#define FLD_SET(r, f, v)                r = (((r) & ~(f ## _MASK)) | ((v) << (f ## _LSB)))

enum rp1_funcs
{
    func_alt0,
    func_alt1,
    func_alt2,
    func_alt3,
    func_alt4,
    func_gpio,
    func_alt6,
    func_alt7,
    func_alt8,
    func_none,
    func_aaud,
    func_dcd0,
    func_dpi,
    func_dsi0_te_ext,
    func_dsi1_te_ext,
    func_dsr0,
    func_dtr0,
    func_gpclk0,
    func_gpclk1,
    func_gpclk2,
    func_gpclk3,
    func_gpclk4,
    func_gpclk5,
    func_i2c0,
    func_i2c1,
    func_i2c2,
    func_i2c3,
    func_i2c4,
    func_i2c5,
    func_i2c6,
    func_i2s0,
    func_i2s1,
    func_i2s2,
    func_ir,
    func_mic,
    func_pcie_clkreq_n,
    func_pio,
    func_proc_rio,
    func_pwm0,
    func_pwm1,
    func_ri0,
    func_sd0,
    func_sd1,
    func_spi0,
    func_spi1,
    func_spi2,
    func_spi3,
    func_spi4,
    func_spi5,
    func_spi6,
    func_spi7,
    func_spi8,
    func_uart0,
    func_uart1,
    func_uart2,
    func_uart3,
    func_uart4,
    func_uart5,
    func_vbus0,
    func_vbus1,
    func_vbus2,
    func_vbus3,
    func__,
    func_count = func__,
};

struct rp1_pin_funcs
{
#define PIN(i, f0, f1, f2, f3, f4, f5, f6, f7, f8) \
    [i] = { \
        .funcs = { \
            func_##f0, \
            func_##f1, \
            func_##f2, \
            func_##f3, \
            func_##f4, \
            func_##f5, \
            func_##f6, \
            func_##f7, \
            func_##f8, \
        }, \
    }
    rt_uint8_t funcs[RP1_FSEL_COUNT];
};

struct rp1_pin_desc
{
    rt_uint32_t number;
    const char *name;
};

struct rp1_iobank_desc
{
    int min_gpio;
    int num_gpios;
    int gpio_offset;
    int inte_offset;
    int ints_offset;
    int rio_offset;
    int pads_offset;
};

struct rp1_pinctrl;

struct rp1_pin_info
{
    rt_uint8_t num;
    rt_uint8_t bank;
    rt_uint8_t offset;
    rt_uint8_t fsel;
    rt_uint8_t irq_type;

    void *gpio;
    void *rio;
    void *inte;
    void *ints;
    void *pad;
};

struct rp1_pinctrl
{
    struct rt_device_pin parent;

    void *gpio_base;
    void *rio_base;
    void *pads_base;
    int irqs[RP1_NUM_BANKS];
    struct rp1_pin_info pins[RP1_NUM_GPIOS];
    struct rt_spinlock irq_lock[RP1_NUM_BANKS];
};

#define raw_to_rp1_pinctrl(raw) rt_container_of(raw, struct rp1_pinctrl, parent)

/* Pins are just named GPIO0..GPIO53 */
static struct rp1_pin_desc rp1_gpio_pins[] =
{
#define RP1_GPIO_PIN(a) { a, "gpio" #a }
    RP1_GPIO_PIN(0),
    RP1_GPIO_PIN(1),
    RP1_GPIO_PIN(2),
    RP1_GPIO_PIN(3),
    RP1_GPIO_PIN(4),
    RP1_GPIO_PIN(5),
    RP1_GPIO_PIN(6),
    RP1_GPIO_PIN(7),
    RP1_GPIO_PIN(8),
    RP1_GPIO_PIN(9),
    RP1_GPIO_PIN(10),
    RP1_GPIO_PIN(11),
    RP1_GPIO_PIN(12),
    RP1_GPIO_PIN(13),
    RP1_GPIO_PIN(14),
    RP1_GPIO_PIN(15),
    RP1_GPIO_PIN(16),
    RP1_GPIO_PIN(17),
    RP1_GPIO_PIN(18),
    RP1_GPIO_PIN(19),
    RP1_GPIO_PIN(20),
    RP1_GPIO_PIN(21),
    RP1_GPIO_PIN(22),
    RP1_GPIO_PIN(23),
    RP1_GPIO_PIN(24),
    RP1_GPIO_PIN(25),
    RP1_GPIO_PIN(26),
    RP1_GPIO_PIN(27),
    RP1_GPIO_PIN(28),
    RP1_GPIO_PIN(29),
    RP1_GPIO_PIN(30),
    RP1_GPIO_PIN(31),
    RP1_GPIO_PIN(32),
    RP1_GPIO_PIN(33),
    RP1_GPIO_PIN(34),
    RP1_GPIO_PIN(35),
    RP1_GPIO_PIN(36),
    RP1_GPIO_PIN(37),
    RP1_GPIO_PIN(38),
    RP1_GPIO_PIN(39),
    RP1_GPIO_PIN(40),
    RP1_GPIO_PIN(41),
    RP1_GPIO_PIN(42),
    RP1_GPIO_PIN(43),
    RP1_GPIO_PIN(44),
    RP1_GPIO_PIN(45),
    RP1_GPIO_PIN(46),
    RP1_GPIO_PIN(47),
    RP1_GPIO_PIN(48),
    RP1_GPIO_PIN(49),
    RP1_GPIO_PIN(50),
    RP1_GPIO_PIN(51),
    RP1_GPIO_PIN(52),
    RP1_GPIO_PIN(53),
#undef RP1_GPIO_PIN
};

static const char * const rp1_func_names[] =
{
#define FUNC_NAME(name) [func_##name] = #name
    FUNC_NAME(alt0),
    FUNC_NAME(alt1),
    FUNC_NAME(alt2),
    FUNC_NAME(alt3),
    FUNC_NAME(alt4),
    FUNC_NAME(gpio),
    FUNC_NAME(alt6),
    FUNC_NAME(alt7),
    FUNC_NAME(alt8),
    FUNC_NAME(none),
    FUNC_NAME(aaud),
    FUNC_NAME(dcd0),
    FUNC_NAME(dpi),
    FUNC_NAME(dsi0_te_ext),
    FUNC_NAME(dsi1_te_ext),
    FUNC_NAME(dsr0),
    FUNC_NAME(dtr0),
    FUNC_NAME(gpclk0),
    FUNC_NAME(gpclk1),
    FUNC_NAME(gpclk2),
    FUNC_NAME(gpclk3),
    FUNC_NAME(gpclk4),
    FUNC_NAME(gpclk5),
    FUNC_NAME(i2c0),
    FUNC_NAME(i2c1),
    FUNC_NAME(i2c2),
    FUNC_NAME(i2c3),
    FUNC_NAME(i2c4),
    FUNC_NAME(i2c5),
    FUNC_NAME(i2c6),
    FUNC_NAME(i2s0),
    FUNC_NAME(i2s1),
    FUNC_NAME(i2s2),
    FUNC_NAME(ir),
    FUNC_NAME(mic),
    FUNC_NAME(pcie_clkreq_n),
    FUNC_NAME(pio),
    FUNC_NAME(proc_rio),
    FUNC_NAME(pwm0),
    FUNC_NAME(pwm1),
    FUNC_NAME(ri0),
    FUNC_NAME(sd0),
    FUNC_NAME(sd1),
    FUNC_NAME(spi0),
    FUNC_NAME(spi1),
    FUNC_NAME(spi2),
    FUNC_NAME(spi3),
    FUNC_NAME(spi4),
    FUNC_NAME(spi5),
    FUNC_NAME(spi6),
    FUNC_NAME(spi7),
    FUNC_NAME(spi8),
    FUNC_NAME(uart0),
    FUNC_NAME(uart1),
    FUNC_NAME(uart2),
    FUNC_NAME(uart3),
    FUNC_NAME(uart4),
    FUNC_NAME(uart5),
    FUNC_NAME(vbus0),
    FUNC_NAME(vbus1),
    FUNC_NAME(vbus2),
    FUNC_NAME(vbus3),
#undef FUNC_NAME
};

static const struct rp1_pin_funcs rp1_gpio_pin_funcs[] =
{
    PIN(0, spi0, dpi, uart1, i2c0, _, gpio, proc_rio, pio, spi2),
    PIN(1, spi0, dpi, uart1, i2c0, _, gpio, proc_rio, pio, spi2),
    PIN(2, spi0, dpi, uart1, i2c1, ir, gpio, proc_rio, pio, spi2),
    PIN(3, spi0, dpi, uart1, i2c1, ir, gpio, proc_rio, pio, spi2),
    PIN(4, gpclk0, dpi, uart2, i2c2, ri0, gpio, proc_rio, pio, spi3),
    PIN(5, gpclk1, dpi, uart2, i2c2, dtr0, gpio, proc_rio, pio, spi3),
    PIN(6, gpclk2, dpi, uart2, i2c3, dcd0, gpio, proc_rio, pio, spi3),
    PIN(7, spi0, dpi, uart2, i2c3, dsr0, gpio, proc_rio, pio, spi3),
    PIN(8, spi0, dpi, uart3, i2c0, _, gpio, proc_rio, pio, spi4),
    PIN(9, spi0, dpi, uart3, i2c0, _, gpio, proc_rio, pio, spi4),
    PIN(10, spi0, dpi, uart3, i2c1, _, gpio, proc_rio, pio, spi4),
    PIN(11, spi0, dpi, uart3, i2c1, _, gpio, proc_rio, pio, spi4),
    PIN(12, pwm0, dpi, uart4, i2c2, aaud, gpio, proc_rio, pio, spi5),
    PIN(13, pwm0, dpi, uart4, i2c2, aaud, gpio, proc_rio, pio, spi5),
    PIN(14, pwm0, dpi, uart4, i2c3, uart0, gpio, proc_rio, pio, spi5),
    PIN(15, pwm0, dpi, uart4, i2c3, uart0, gpio, proc_rio, pio, spi5),
    PIN(16, spi1, dpi, dsi0_te_ext, _, uart0, gpio, proc_rio, pio, _),
    PIN(17, spi1, dpi, dsi1_te_ext, _, uart0, gpio, proc_rio, pio, _),
    PIN(18, spi1, dpi, i2s0, pwm0, i2s1, gpio, proc_rio, pio, gpclk1),
    PIN(19, spi1, dpi, i2s0, pwm0, i2s1, gpio, proc_rio, pio, _),
    PIN(20, spi1, dpi, i2s0, gpclk0, i2s1, gpio, proc_rio, pio, _),
    PIN(21, spi1, dpi, i2s0, gpclk1, i2s1, gpio, proc_rio, pio, _),
    PIN(22, sd0, dpi, i2s0, i2c3, i2s1, gpio, proc_rio, pio, _),
    PIN(23, sd0, dpi, i2s0, i2c3, i2s1, gpio, proc_rio, pio, _),
    PIN(24, sd0, dpi, i2s0, _, i2s1, gpio, proc_rio, pio, spi2),
    PIN(25, sd0, dpi, i2s0, mic, i2s1, gpio, proc_rio, pio, spi3),
    PIN(26, sd0, dpi, i2s0, mic, i2s1, gpio, proc_rio, pio, spi5),
    PIN(27, sd0, dpi, i2s0, mic, i2s1, gpio, proc_rio, pio, spi1),
    PIN(28, sd1, i2c4, i2s2, spi6, vbus0, gpio, proc_rio, _, _),
    PIN(29, sd1, i2c4, i2s2, spi6, vbus0, gpio, proc_rio, _, _),
    PIN(30, sd1, i2c5, i2s2, spi6, uart5, gpio, proc_rio, _, _),
    PIN(31, sd1, i2c5, i2s2, spi6, uart5, gpio, proc_rio, _, _),
    PIN(32, sd1, gpclk3, i2s2, spi6, uart5, gpio, proc_rio, _, _),
    PIN(33, sd1, gpclk4, i2s2, spi6, uart5, gpio, proc_rio, _, _),
    PIN(34, pwm1, gpclk3, vbus0, i2c4, mic, gpio, proc_rio, _, _),
    PIN(35, spi8, pwm1, vbus0, i2c4, mic, gpio, proc_rio, _, _),
    PIN(36, spi8, uart5, pcie_clkreq_n, i2c5, mic, gpio, proc_rio, _, _),
    PIN(37, spi8, uart5, mic, i2c5, pcie_clkreq_n, gpio, proc_rio, _, _),
    PIN(38, spi8, uart5, mic, i2c6, aaud, gpio, proc_rio, dsi0_te_ext, _),
    PIN(39, spi8, uart5, mic, i2c6, aaud, gpio, proc_rio, dsi1_te_ext, _),
    PIN(40, pwm1, uart5, i2c4, spi6, aaud, gpio, proc_rio, _, _),
    PIN(41, pwm1, uart5, i2c4, spi6, aaud, gpio, proc_rio, _, _),
    PIN(42, gpclk5, uart5, vbus1, spi6, i2s2, gpio, proc_rio, _, _),
    PIN(43, gpclk4, uart5, vbus1, spi6, i2s2, gpio, proc_rio, _, _),
    PIN(44, gpclk5, i2c5, pwm1, spi6, i2s2, gpio, proc_rio, _, _),
    PIN(45, pwm1, i2c5, spi7, spi6, i2s2, gpio, proc_rio, _, _),
    PIN(46, gpclk3, i2c4, spi7, mic, i2s2, gpio, proc_rio, dsi0_te_ext, _),
    PIN(47, gpclk5, i2c4, spi7, mic, i2s2, gpio, proc_rio, dsi1_te_ext, _),
    PIN(48, pwm1, pcie_clkreq_n, spi7, mic, uart5, gpio, proc_rio, _, _),
    PIN(49, spi8, spi7, i2c5, aaud, uart5, gpio, proc_rio, _, _),
    PIN(50, spi8, spi7, i2c5, aaud, vbus2, gpio, proc_rio, _, _),
    PIN(51, spi8, spi7, i2c6, aaud, vbus2, gpio, proc_rio, _, _),
    PIN(52, spi8, _, i2c6, aaud, vbus3, gpio, proc_rio, _, _),
    PIN(53, spi8, spi7, _, pcie_clkreq_n, vbus3, gpio, proc_rio, _, _),
};

static const struct rp1_iobank_desc rp1_iobanks[RP1_NUM_BANKS] =
{
    /*         gpio   inte    ints     rio    pads */
    {  0, 28, 0x0000, 0x011c, 0x0124, 0x0000, 0x0004 },
    { 28,  6, 0x4000, 0x411c, 0x4124, 0x4000, 0x4004 },
    { 34, 20, 0x8000, 0x811c, 0x8124, 0x8000, 0x8004 },
};

static void rp1_pad_update(struct rp1_pin_info *pin, rt_uint32_t clr, rt_uint32_t set)
{
    rt_uint32_t padctrl = HWREG32(pin->pad);

    padctrl &= ~clr;
    padctrl |= set;

    HWREG32(pin->pad) = padctrl;
}

static void rp1_input_enable(struct rp1_pin_info *pin, int value)
{
    rp1_pad_update(pin, RP1_PAD_IN_ENABLE_MASK, value ? RP1_PAD_IN_ENABLE_MASK : 0);
}

static void rp1_output_enable(struct rp1_pin_info *pin, int value)
{
    rp1_pad_update(pin, RP1_PAD_OUT_DISABLE_MASK, value ? 0 : RP1_PAD_OUT_DISABLE_MASK);
}

static void rp1_set_fsel(struct rp1_pin_info *pin, rt_uint32_t fsel)
{
    rt_uint32_t ctrl = HWREG32(pin->gpio + RP1_GPIO_CTRL);

    if (fsel >= RP1_FSEL_COUNT)
    {
        fsel = RP1_FSEL_NONE_HW;
    }

    rp1_input_enable(pin, 1);
    rp1_output_enable(pin, 1);

    if (fsel == RP1_FSEL_NONE)
    {
        FLD_SET(ctrl, RP1_GPIO_CTRL_OEOVER, RP1_OEOVER_DISABLE);
    }
    else
    {
        FLD_SET(ctrl, RP1_GPIO_CTRL_OUTOVER, RP1_OUTOVER_PERI);
        FLD_SET(ctrl, RP1_GPIO_CTRL_OEOVER, RP1_OEOVER_PERI);
    }

    FLD_SET(ctrl, RP1_GPIO_CTRL_FUNCSEL, fsel);
    HWREG32(pin->gpio + RP1_GPIO_CTRL) = ctrl;
}

static void rp1_pull_config_set(struct rp1_pin_info *pin, unsigned int arg)
{
    rt_uint32_t padctrl = HWREG32(pin->pad);

    FLD_SET(padctrl, RP1_PAD_PULL, arg & 0x3);

    HWREG32(pin->pad) = padctrl;
}

static const struct rt_pin_ctrl_conf_params rp1_conf_params[] =
{
    { "bias-disable", PIN_CONFIG_BIAS_DISABLE, 0 },
    { "bias-pull-up", PIN_CONFIG_BIAS_PULL_UP, 1 },
    { "bias-pull-down", PIN_CONFIG_BIAS_PULL_DOWN, 1 },
};

static rt_err_t rp1_pinctrl_confs_apply_once(struct rp1_pinctrl *pc, struct rt_ofw_node *np)
{
    rt_err_t err = RT_EOK;
    const char *string;
    rt_uint32_t pin, fsel, strength, slew;
    struct rt_ofw_prop *prop;
    struct rp1_pin_info *pini;
    enum rp1_funcs func = func_count;
    const struct rt_pin_ctrl_conf_params *conf = RT_NULL;

    if (rt_ofw_prop_read_string(np, "function", &string))
    {
        return -RT_EINVAL;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(rp1_func_names); ++i)
    {
        if (!rt_strcmp(string, rp1_func_names[i]))
        {
            func = (enum rp1_funcs)i;
            break;
        }
    }

    if (func == func_count)
    {
        return -RT_EINVAL;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(rp1_conf_params); ++i)
    {
        if (rt_ofw_prop_read_bool(np, rp1_conf_params[i].propname))
        {
            conf = &rp1_conf_params[i];
            break;
        }
    }

    strength = RT_UINT32_MAX;
    if (!rt_ofw_prop_read_u32(np, "drive-strength", &strength))
    {
        switch (strength)
        {
        case  2: strength = RP1_PAD_DRIVE_2MA;  break;
        case  4: strength = RP1_PAD_DRIVE_4MA;  break;
        case  8: strength = RP1_PAD_DRIVE_8MA;  break;
        case 12: strength = RP1_PAD_DRIVE_12MA; break;
        default:
            return -RT_ENOSYS;
        }
    }

    slew = RT_UINT32_MAX;
    rt_ofw_prop_read_u32(np, "slew-rate", &slew);

    rt_ofw_foreach_prop_string(np, "pins", prop, string)
    {
        pini = RT_NULL;

        for (int i = 0; i < RT_ARRAY_SIZE(rp1_gpio_pins); ++i)
        {
            if (!rt_strcmp(rp1_gpio_pins[i].name, string))
            {
                pin = rp1_gpio_pins[i].number;
                pini = &pc->pins[pin];
                break;
            }
        }

        if (!pini)
        {
            err = -RT_EINVAL;
            break;
        }

        /* IOMUX */
        for (fsel = 0; fsel < RP1_FSEL_COUNT; ++fsel)
        {
            if (func == rp1_gpio_pin_funcs[pin].funcs[fsel])
            {
                break;
            }
        }

        if (fsel == RP1_FSEL_COUNT)
        {
            err = -RT_EINVAL;
            break;
        }

        rp1_set_fsel(pini, fsel);

        /* PULL */
        if (conf)
        {
            switch (conf->param)
            {
            case PIN_CONFIG_BIAS_DISABLE:
                rp1_pull_config_set(pini, RP1_PUD_OFF);
                break;

            case PIN_CONFIG_BIAS_PULL_DOWN:
                rp1_pull_config_set(pini, RP1_PUD_DOWN);
                break;

            case PIN_CONFIG_BIAS_PULL_UP:
                rp1_pull_config_set(pini, RP1_PUD_UP);
                break;

            default:
                err = -RT_ENOSYS;
                break;
            }
        }

        if (strength != RT_UINT32_MAX)
        {
            rp1_pad_update(pini, RP1_PAD_DRIVE_MASK, strength);
        }

        if (slew != RT_UINT32_MAX)
        {
            rp1_pad_update(pini, RP1_PAD_SLEWFAST_MASK, slew ? RP1_PAD_SLEWFAST_MASK : 0);
        }
    }

    return err;
}

static void rp1_pinctrl_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    struct rp1_pinctrl *pc = raw_to_rp1_pinctrl(device);
    struct rp1_pin_info *pini = &pc->pins[pin];

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        HWREG32(pini->rio + RP1_RIO_OE + RP1_SET_OFFSET) = 1 << pini->offset;
        rp1_set_fsel(pini, RP1_FSEL_GPIO);
        break;

    case PIN_MODE_INPUT:
        HWREG32(pini->rio + RP1_RIO_OE + RP1_CLR_OFFSET) = 1 << pini->offset;
        rp1_set_fsel(pini, RP1_FSEL_GPIO);
        break;

    default:
        break;
    }
}

static void rp1_pinctrl_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    struct rp1_pinctrl *pc = raw_to_rp1_pinctrl(device);
    struct rp1_pin_info *pini = &pc->pins[pin];

    /* Assume the pin is already an output */
    HWREG32(pini->rio + RP1_RIO_OUT + (value ? RP1_SET_OFFSET : RP1_CLR_OFFSET)) =
            1 << pini->offset;
}

static rt_ssize_t rp1_pinctrl_read(struct rt_device *device, rt_base_t pin)
{
    struct rp1_pinctrl *pc = raw_to_rp1_pinctrl(device);
    struct rp1_pin_info *pini = &pc->pins[pin];

    return !!(HWREG32(pini->rio + RP1_RIO_IN) & (1 << pini->offset));
}

static rt_err_t rp1_pinctrl_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    struct rp1_pinctrl *pc = raw_to_rp1_pinctrl(device);
    struct rp1_pin_info *pini = &pc->pins[pin];

    HWREG32(pini->inte + (enabled ? RP1_SET_OFFSET : RP1_CLR_OFFSET)) = 1 << pini->offset;

    if (!enabled)
    {
        /* Clear any latched events */
        HWREG32(pini->gpio + RP1_SET_OFFSET + RP1_GPIO_CTRL) = RP1_GPIO_CTRL_IRQRESET;
    }

    return RT_EOK;
}

static rt_err_t rp1_pinctrl_irq_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    rt_ubase_t level;
    rt_uint32_t irq_flags;
    struct rp1_pinctrl *pc = raw_to_rp1_pinctrl(device);
    struct rp1_pin_info *pini = &pc->pins[pin];

    level = rt_spin_lock_irqsave(&pc->irq_lock[pini->bank]);

    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        irq_flags = RP1_INT_EDGE_RISING;
        break;

    case PIN_IRQ_MODE_FALLING:
        irq_flags = RP1_INT_EDGE_FALLING;
        break;

    case PIN_IRQ_MODE_RISING_FALLING:
        irq_flags = RP1_INT_EDGE_RISING | RP1_INT_EDGE_FALLING;
        break;

    case PIN_IRQ_MODE_HIGH_LEVEL:
        irq_flags = RP1_INT_LEVEL_HIGH;
        break;

    case PIN_IRQ_MODE_LOW_LEVEL:
        irq_flags = RP1_INT_LEVEL_LOW;
        break;

    default:
        rt_spin_unlock_irqrestore(&pc->irq_lock[pini->bank], level);
        return -RT_EINVAL;
    }

    /* Clear them all */
    HWREG32(pini->gpio + RP1_CLR_OFFSET + RP1_GPIO_CTRL) =
            RP1_INT_MASK << RP1_GPIO_EVENTS_SHIFT_RAW;

    /* Set those that are needed */
    HWREG32(pini->gpio + RP1_SET_OFFSET + RP1_GPIO_CTRL) =
            irq_flags << RP1_GPIO_EVENTS_SHIFT_RAW;

    pini->irq_type = mode;

    rt_spin_unlock_irqrestore(&pc->irq_lock[pini->bank], level);

    return RT_EOK;
}

static rt_err_t rp1_pinctrl_confs_apply(struct rt_device *device, void *fw_conf_np)
{
    rt_err_t err;
    rt_bool_t stage2 = RT_FALSE;
    struct rt_ofw_node *conf_np = fw_conf_np, *child;
    struct rp1_pinctrl *pc = raw_to_rp1_pinctrl(device);

    rt_ofw_foreach_child_node(conf_np, child)
    {
        stage2 = RT_TRUE;

        if ((err = rp1_pinctrl_confs_apply_once(pc, child)))
        {
            return err;
        }
    }

    if (!stage2)
    {
        err = rp1_pinctrl_confs_apply_once(pc, conf_np);
    }

    return err;
}

static const struct rt_pin_ops rp1_pinctrl_ops =
{
    .pin_mode = rp1_pinctrl_mode,
    .pin_write = rp1_pinctrl_write,
    .pin_read = rp1_pinctrl_read,
    .pin_irq_enable = rp1_pinctrl_irq_enable,
    .pin_irq_mode = rp1_pinctrl_irq_mode,
    .pin_ctrl_confs_apply = rp1_pinctrl_confs_apply,
};

static void rp1_pinctrl_isr(int irq, void *param)
{
    rt_ubase_t pin;
    rt_bitmap_t ints;
    struct rp1_pin_info *pini;
    struct rp1_pinctrl *pc = param;
    const struct rp1_iobank_desc *bank;

    if (pc->irqs[0] == irq)
    {
        bank = &rp1_iobanks[0];
    }
    else if (pc->irqs[1] == irq)
    {
        bank = &rp1_iobanks[1];
    }
    else
    {
        bank = &rp1_iobanks[2];
    }

    ints = HWREG32(pc->gpio_base + bank->ints_offset);

    rt_bitmap_for_each_set_bit(&ints, pin, 32)
    {
        pini = &pc->pins[pin];

        /* Clear any latched events */
        HWREG32(pini->gpio + RP1_SET_OFFSET + RP1_GPIO_CTRL) = RP1_GPIO_CTRL_IRQRESET;

        pin_pic_handle_isr(&pc->parent, pin);
    }
}

static rt_err_t rp1_pinctrl_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rp1_pinctrl *pc = rt_calloc(1, sizeof(*pc));

    if (!pc)
    {
        return -RT_ENOMEM;
    }

    if (!(pc->gpio_base = rt_dm_dev_iomap(dev, 0)))
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (!(pc->rio_base = rt_dm_dev_iomap(dev, 1)))
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (!(pc->pads_base = rt_dm_dev_iomap(dev, 2)))
    {
        err = -RT_EIO;
        goto _fail;
    }

    for (int i = 0; i < RP1_NUM_BANKS; ++i)
    {
        const struct rp1_iobank_desc *bank = &rp1_iobanks[i];

        for (int j = 0; j < bank->num_gpios; ++j)
        {
            struct rp1_pin_info *pini = &pc->pins[bank->min_gpio + j];

            pini->num = bank->min_gpio + j;
            pini->bank = i;
            pini->offset = j;

            pini->gpio = pc->gpio_base + bank->gpio_offset + j * sizeof(rt_uint32_t) * 2;
            pini->inte = pc->gpio_base + bank->inte_offset;
            pini->ints = pc->gpio_base + bank->ints_offset;
            pini->rio  = pc->rio_base + bank->rio_offset;
            pini->pad  = pc->pads_base + bank->pads_offset + j * sizeof(rt_uint32_t);
        }

        rt_spin_lock_init(&pc->irq_lock[i]);
    }

    for (int i = 0; i < RP1_NUM_BANKS; ++i)
    {
        int irq = rt_dm_dev_get_irq(dev, i);

        pc->irqs[i] = irq;

        if (irq < 0)
        {
            break;
        }

        rt_hw_interrupt_install(irq, rp1_pinctrl_isr, pc, "rp1-pinctrl");
        rt_hw_interrupt_umask(irq);
    }

    pc->parent.ops = pdev->id->data;
    pin_api_init(&pc->parent, RP1_NUM_GPIOS);
    pin_pic_init(&pc->parent, pc->irqs[0]);

    rt_ofw_data(dev->ofw_node) = &pc->parent;

    return RT_EOK;

_fail:
    rt_free(pc);

    return err;
}

static const struct rt_ofw_node_id rp1_pinctrl_ofw_ids[] =
{
    { .compatible = "raspberrypi,rp1-gpio", .data = &rp1_pinctrl_ops },
    { /* sentinel */ }
};

static struct rt_platform_driver rp1_pinctrl_driver =
{
    .name = "pinctrl-rp1",
    .ids = rp1_pinctrl_ofw_ids,

    .probe = rp1_pinctrl_probe,
};

static int rp1_pinctrl_register(void)
{
    rt_platform_driver_register(&rp1_pinctrl_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(rp1_pinctrl_register);
