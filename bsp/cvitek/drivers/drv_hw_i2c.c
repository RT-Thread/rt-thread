/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-14     ShichengChu  first version
 */
#include "drv_hw_i2c.h"
#include <rtdevice.h>
#include <board.h>
#include "drv_pinmux.h"
#include "drv_ioremap.h"

#define DBG_TAG              "drv.i2c"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

struct dw_iic_bus
{
    struct rt_i2c_bus_device parent;
    dw_iic_regs_t *iic_base;
    rt_uint32_t irq;
    char *device_name;
};

static struct dw_iic_bus _i2c_obj[] =
{
#ifdef BSP_USING_I2C0
    {
        .iic_base       = (dw_iic_regs_t *)I2C0_BASE,
        .device_name    = "i2c0",
        .irq            = I2C0_IRQ,
    },
#endif /* BSP_USING_I2C0 */
#ifdef BSP_USING_I2C1
    {
        .iic_base       = (dw_iic_regs_t *)I2C1_BASE,
        .device_name    = "i2c1",
        .irq            = I2C1_IRQ,
    },
#endif /* BSP_USING_I2C1 */
#ifdef BSP_USING_I2C2
    {
        .iic_base       = (dw_iic_regs_t *)I2C2_BASE,
        .device_name    = "i2c2",
        .irq            = I2C2_IRQ,
    },
#endif /* BSP_USING_I2C2 */
#ifdef BSP_USING_I2C3
    {
        .iic_base       = (dw_iic_regs_t *)I2C3_BASE,
        .device_name    = "i2c3",
        .irq            = I2C3_IRQ,
    },
#endif /* BSP_USING_I2C3 */
#ifdef BSP_USING_I2C4
    {
        .iic_base       = (dw_iic_regs_t *)I2C4_BASE,
        .device_name    = "i2c4",
        .irq            = I2C4_IRQ,
    },
#endif /* BSP_USING_I2C4 */
};

static rt_uint32_t dw_iic_wait_for_bb(dw_iic_regs_t *iic_base)
{
    uint16_t    timeout = 0;
    while ((iic_base->IC_STATUS & DW_IIC_MST_ACTIVITY_STATE) || !(iic_base->IC_STATUS & DW_IIC_TXFIFO_EMPTY_STATE))
    {
        /* Evaluate timeout */
        rt_hw_us_delay(5);
        timeout ++;
        if (timeout > 200)
        {
            /* exceed 1 ms */
            LOG_E("Timed out waiting for bus busy");
            return 1;
        }
    }

    return 0;
}

void dw_iic_set_reg_address(dw_iic_regs_t *iic_base, rt_uint32_t addr, uint8_t addr_len)
{
    while (addr_len)
    {
        addr_len --;
        /* high byte address going out first */
        dw_iic_transmit_data(iic_base, (addr >> (addr_len * 8)) & 0xff);
    }
}

static void dw_iic_set_target_address(dw_iic_regs_t *iic_base, rt_uint32_t address)
{
    rt_uint32_t i2c_status;
    i2c_status = dw_iic_get_iic_status(iic_base);
    dw_iic_disable(iic_base);
    iic_base->IC_TAR = (iic_base->IC_TAR & ~0x3ff) | address; /* this register can be written only when the I2C is disabled*/

    if (i2c_status == DW_IIC_EN)
    {
        dw_iic_enable(iic_base);
    }
}

static int dw_iic_xfer_init(dw_iic_regs_t *iic_base, rt_uint32_t dev_addr)
{
    if (dw_iic_wait_for_bb(iic_base))
        return -RT_ERROR;

    dw_iic_set_target_address(iic_base, dev_addr);
    dw_iic_enable(iic_base);

    return RT_EOK;
}

static int dw_iic_xfer_finish(dw_iic_regs_t *iic_base)
{
    rt_uint32_t timeout = 0;

    while (1)
    {
        if (iic_base->IC_RAW_INTR_STAT & DW_IIC_RAW_STOP_DET)
        {
            iic_base->IC_CLR_STOP_DET;
            break;
        }
        else
        {
            timeout ++;
            rt_hw_us_delay(5);
            if (timeout > 10000)
            {
                LOG_E("xfer finish tiemout");
                break;
            }
        }
    }

    if (dw_iic_wait_for_bb(iic_base))
    {
        return -RT_ERROR;
    }

    dw_iic_flush_rxfifo(iic_base);

    return RT_EOK;
}

static void dw_iic_set_slave_mode(dw_iic_regs_t *iic_base)
{
    rt_uint32_t i2c_status;
    i2c_status = dw_iic_get_iic_status(iic_base);
    dw_iic_disable(iic_base);
    rt_uint32_t val = DW_IIC_CON_MASTER_EN | DW_IIC_CON_SLAVE_EN;
    iic_base->IC_CON &= ~val;  ///< set 0 to disabled master mode; set 0 to enabled slave mode

    if (i2c_status == DW_IIC_EN)
    {
        dw_iic_enable(iic_base);
    }
}

static void dw_iic_set_master_mode(dw_iic_regs_t *iic_base)
{
    rt_uint32_t i2c_status;
    i2c_status = dw_iic_get_iic_status(iic_base);
    dw_iic_disable(iic_base);
    rt_uint32_t val = DW_IIC_CON_MASTER_EN | DW_IIC_CON_SLAVE_EN; ///< set 1 to enabled master mode; set 1 to disabled slave mode
    iic_base->IC_CON |= val;

    if (i2c_status == DW_IIC_EN)
    {
        dw_iic_enable(iic_base);
    }
}

static rt_err_t dw_iic_recv(dw_iic_regs_t *iic_base, rt_uint32_t devaddr, rt_uint8_t *data, rt_uint32_t size, rt_uint32_t timeout)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t timecount = 0;

    RT_ASSERT(data != RT_NULL);

    if (dw_iic_xfer_init(iic_base, devaddr))
    {
        ret = -RT_EIO;
        goto ERR_EXIT;
    }

    timecount = timeout + rt_tick_get_millisecond();

    for (int i = 0 ; i < size; i ++)
    {
        if(i != (size - 1))
        {
            dw_iic_transmit_data(iic_base, DW_IIC_DATA_CMD);
        }
        else
        {
            dw_iic_transmit_data(iic_base, DW_IIC_DATA_CMD | DW_IIC_DATA_STOP);
        }
    }

    while (size > 0)
    {
        if (iic_base->IC_STATUS & DW_IIC_RXFIFO_NOT_EMPTY_STATE)
        {
            *data ++ = dw_iic_receive_data(iic_base);
            -- size;
        }
        else if (rt_tick_get_millisecond() >= timecount)
        {
            LOG_E("Timed out read ic_cmd_data");
            ret = -RT_ETIMEOUT;
            goto ERR_EXIT;
        }
    }

    if (dw_iic_xfer_finish(iic_base))
    {
        ret = -RT_EIO;
        goto ERR_EXIT;
    }

ERR_EXIT:
    dw_iic_disable(iic_base);

    return ret;
}

static rt_err_t dw_iic_send(dw_iic_regs_t *iic_base, rt_uint32_t devaddr, const uint8_t *data, rt_uint32_t size, rt_uint32_t timeout)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t timecount;

    RT_ASSERT(data != RT_NULL);

    if (dw_iic_xfer_init(iic_base, devaddr))
    {
        ret = -RT_EIO;
        goto ERR_EXIT;
    }

    timecount = timeout + rt_tick_get_millisecond();

    while (size > 0)
    {
        if (iic_base->IC_STATUS & DW_IIC_TXFIFO_NOT_FULL_STATE)
        {
            if (-- size == 0)
            {
                dw_iic_transmit_data(iic_base, *data ++ | DW_IIC_DATA_STOP);
            }
            else
            {
                dw_iic_transmit_data(iic_base, *data ++);
            }
        }
        else if (rt_tick_get_millisecond() >= timecount)
        {
            LOG_D("ic status is not TFNF\n");
            ret = -RT_ETIMEOUT;
            goto ERR_EXIT;
        }
    }

    LOG_D("dw_iic_xfer_finish");

    if (dw_iic_xfer_finish(iic_base))
    {
        ret = -RT_EIO;
        goto ERR_EXIT;
    }

ERR_EXIT:
    dw_iic_disable(iic_base);

    return ret;
}

static rt_ssize_t dw_iic_master_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    rt_ssize_t ret = -RT_ERROR;
    rt_uint32_t timeout;

    struct dw_iic_bus *i2c_bus = (struct dw_iic_bus *)bus;
    dw_iic_regs_t *iic_base = i2c_bus->iic_base;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_ADDR_10BIT)
        {
            dw_iic_set_master_10bit_addr_mode(iic_base);
            dw_iic_set_slave_10bit_addr_mode(iic_base);
        }
        else
        {
            dw_iic_set_master_7bit_addr_mode(iic_base);
            dw_iic_set_slave_7bit_addr_mode(iic_base);
        }

        if (msg->flags & RT_I2C_RD)
        {
            timeout = 1000;
            ret = dw_iic_recv(iic_base, msg->addr, msg->buf, msg->len, timeout);
            if (ret != RT_EOK)
                LOG_E("dw_iic_recv error: %d", ret);
        }
        else
        {
            timeout = 100;
            ret = dw_iic_send(iic_base, msg->addr, msg->buf, msg->len, timeout);
            if (ret != RT_EOK)
                LOG_E("dw_iic_send error: %d", ret);
        }
    }

    return ret == RT_EOK ? num : ret;
}

static void dw_iic_set_transfer_speed_high(dw_iic_regs_t *iic_base)
{
    rt_uint32_t speed_config = iic_base->IC_CON;
    speed_config &= ~(DW_IIC_CON_SPEEDL_EN | DW_IIC_CON_SPEEDH_EN);
    speed_config |= DW_IIC_CON_SPEEDL_EN | DW_IIC_CON_SPEEDH_EN;
    iic_base->IC_CON = speed_config;
}

static void dw_iic_set_transfer_speed_fast(dw_iic_regs_t *iic_base)
{
    rt_uint32_t speed_config = iic_base->IC_CON;
    speed_config &= ~(DW_IIC_CON_SPEEDL_EN | DW_IIC_CON_SPEEDH_EN);
    speed_config |= DW_IIC_CON_SPEEDH_EN;
    iic_base->IC_CON = speed_config;
}

static void dw_iic_set_transfer_speed_standard(dw_iic_regs_t *iic_base)
{
    rt_uint32_t speed_config = iic_base->IC_CON;
    speed_config &= ~(DW_IIC_CON_SPEEDL_EN | DW_IIC_CON_SPEEDH_EN);
    speed_config |= DW_IIC_CON_SPEEDL_EN;
    iic_base->IC_CON = speed_config;
}

static rt_err_t dw_iic_bus_control(struct rt_i2c_bus_device *bus, int cmd, void *args)
{
    struct dw_iic_bus *i2c_bus = (struct dw_iic_bus *)bus;

    RT_ASSERT(bus != RT_NULL);

    dw_iic_regs_t *iic_base = i2c_bus->iic_base;

    switch (cmd)
    {
        case RT_I2C_DEV_CTRL_CLK:
        {
            rt_uint32_t speed = *(rt_uint32_t *)args;
            if (speed == 100 * 1000)
            {
                dw_iic_set_transfer_speed_standard(iic_base);
                dw_iic_set_standard_scl_hcnt(iic_base, (((IC_CLK * 4000U) / 1000U) - 7U));
                dw_iic_set_standard_scl_lcnt(iic_base, (((IC_CLK * 4700) / 1000U) - 1U));
            }
            else if (speed == 400 * 1000)
            {
                dw_iic_set_transfer_speed_fast(iic_base);
                dw_iic_set_fast_scl_hcnt(iic_base, (((IC_CLK * 600U) / 1000U) - 7U));
                dw_iic_set_fast_scl_lcnt(iic_base, (((IC_CLK * 1300U) / 1000U) - 1U));
            }
            else if (speed == 4 * 1000 * 1000)
            {
                dw_iic_set_transfer_speed_high(iic_base);
                dw_iic_set_high_scl_hcnt(iic_base, 6U);
                dw_iic_set_high_scl_lcnt(iic_base, 8U);
            }
            else
            {
                return -RT_EIO;
            }
        }
        break;

        case RT_I2C_DEV_CTRL_10BIT:
            dw_iic_set_master_10bit_addr_mode(iic_base);
            dw_iic_set_slave_10bit_addr_mode(iic_base);
        break;

        default:
            return -RT_EIO;
        break;
    }

    return RT_EOK;
}

static const struct rt_i2c_bus_device_ops i2c_ops =
{
    .master_xfer      = dw_iic_master_xfer,
    .slave_xfer       = RT_NULL,
    .i2c_bus_control  = dw_iic_bus_control,
};

static void dw_iic_init(dw_iic_regs_t *iic_base)
{
    dw_iic_disable(iic_base);
    dw_iic_clear_all_irq(iic_base);
    dw_iic_disable_all_irq(iic_base);

    iic_base->IC_SAR = 0;

    dw_iic_set_receive_fifo_threshold(iic_base, 0x1);
    dw_iic_set_transmit_fifo_threshold(iic_base, 0x0);
    dw_iic_set_sda_hold_time(iic_base, 0x1e);

    dw_iic_set_master_mode(iic_base);
    dw_iic_enable_restart(iic_base);

    dw_iic_set_transfer_speed_standard(iic_base);
    dw_iic_set_standard_scl_hcnt(iic_base, (((IC_CLK * 4000U) / 1000U) - 7U));
    dw_iic_set_standard_scl_lcnt(iic_base, (((IC_CLK * 4700) / 1000U) - 1U));
}

#if defined(BOARD_TYPE_MILKV_DUO) || defined(BOARD_TYPE_MILKV_DUO_SPINOR)

#ifdef BSP_USING_I2C0
static const char *pinname_whitelist_i2c0_scl[] = {
    "IIC0_SCL",
    NULL,
};
static const char *pinname_whitelist_i2c0_sda[] = {
    "IIC0_SDA",
    NULL,
};
#endif

#ifdef BSP_USING_I2C1
static const char *pinname_whitelist_i2c1_scl[] = {
    "SD1_D2",
    "SD1_D3",
    "PAD_MIPIRX0N",
    NULL,
};
static const char *pinname_whitelist_i2c1_sda[] = {
    "SD1_D1",
    "SD1_D0",
    "PAD_MIPIRX1P",
    NULL,
};
#endif

#ifdef BSP_USING_I2C2
// I2C2 is not ALLOWED for Duo
static const char *pinname_whitelist_i2c2_scl[] = {
    NULL,
};
static const char *pinname_whitelist_i2c2_sda[] = {
    NULL,
};
#endif

#ifdef BSP_USING_I2C3
static const char *pinname_whitelist_i2c3_scl[] = {
    "SD1_CMD",
    NULL,
};
static const char *pinname_whitelist_i2c3_sda[] = {
    "SD1_CLK",
    NULL,
};
#endif

#ifdef BSP_USING_I2C4
// I2C4 is not ALLOWED for Duo
static const char *pinname_whitelist_i2c4_scl[] = {
    NULL,
};
static const char *pinname_whitelist_i2c4_sda[] = {
    NULL,
};
#endif

#elif defined(BOARD_TYPE_MILKV_DUO256M) || defined(BOARD_TYPE_MILKV_DUO256M_SPINOR)

#ifdef BSP_USING_I2C0
// I2C0 is not ALLOWED for Duo256
static const char *pinname_whitelist_i2c0_scl[] = {
    NULL,
};
static const char *pinname_whitelist_i2c0_sda[] = {
    NULL,
};
#endif

#ifdef BSP_USING_I2C1
static const char *pinname_whitelist_i2c1_scl[] = {
    "SD1_D2",
    "SD1_D3",
    NULL,
};
static const char *pinname_whitelist_i2c1_sda[] = {
    "SD1_D1",
    "SD1_D0",
    NULL,
};
#endif

#ifdef BSP_USING_I2C2
static const char *pinname_whitelist_i2c2_scl[] = {
    "PAD_MIPI_TXP1",
    NULL,
};
static const char *pinname_whitelist_i2c2_sda[] = {
    "PAD_MIPI_TXM1",
    NULL,
};
#endif

#ifdef BSP_USING_I2C3
static const char *pinname_whitelist_i2c3_scl[] = {
    "SD1_CMD",
    NULL,
};
static const char *pinname_whitelist_i2c3_sda[] = {
    "SD1_CLK",
    NULL,
};
#endif

#ifdef BSP_USING_I2C4
// I2C4 is not ALLOWED for Duo256
static const char *pinname_whitelist_i2c4_scl[] = {
    NULL,
};
static const char *pinname_whitelist_i2c4_sda[] = {
    NULL,
};
#endif

#else
    #error "Unsupported board type!"
#endif

static void rt_hw_i2c_pinmux_config()
{
#ifdef BSP_USING_I2C0
    pinmux_config(BSP_I2C0_SCL_PINNAME, IIC0_SCL, pinname_whitelist_i2c0_scl);
    pinmux_config(BSP_I2C0_SDA_PINNAME, IIC0_SDA, pinname_whitelist_i2c0_sda);
#endif /* BSP_USING_I2C0 */

#ifdef BSP_USING_I2C1
    pinmux_config(BSP_I2C1_SCL_PINNAME, IIC1_SCL, pinname_whitelist_i2c1_scl);
    pinmux_config(BSP_I2C1_SDA_PINNAME, IIC1_SDA, pinname_whitelist_i2c1_sda);
#endif /* BSP_USING_I2C1 */

#ifdef BSP_USING_I2C2
    pinmux_config(BSP_I2C2_SCL_PINNAME, IIC2_SCL, pinname_whitelist_i2c2_scl);
    pinmux_config(BSP_I2C2_SDA_PINNAME, IIC2_SDA, pinname_whitelist_i2c2_sda);
#endif /* BSP_USING_I2C2 */

#ifdef BSP_USING_I2C3
    pinmux_config(BSP_I2C3_SCL_PINNAME, IIC3_SCL, pinname_whitelist_i2c3_scl);
    pinmux_config(BSP_I2C3_SDA_PINNAME, IIC3_SDA, pinname_whitelist_i2c3_sda);
#endif /* BSP_USING_I2C3 */

#ifdef BSP_USING_I2C4
    pinmux_config(BSP_I2C4_SCL_PINNAME, IIC4_SCL, pinname_whitelist_i2c4_scl);
    pinmux_config(BSP_I2C4_SDA_PINNAME, IIC4_SDA, pinname_whitelist_i2c4_sda);
#endif /* BSP_USING_I2C4 */
}

int rt_hw_i2c_init(void)
{
    int result = RT_EOK;

    rt_hw_i2c_pinmux_config();

    for (rt_size_t i = 0; i < sizeof(_i2c_obj) / sizeof(struct dw_iic_bus); i++)
    {
        _i2c_obj->iic_base = (rt_ubase_t)DRV_IOREMAP((void *)_i2c_obj->iic_basee, 0x10000);
        dw_iic_init(_i2c_obj->iic_base);

        _i2c_obj[i].parent.ops = &i2c_ops;

        /* register i2c device */
        if (rt_i2c_bus_device_register(&_i2c_obj[i].parent, _i2c_obj[i].device_name) == RT_EOK)
        {
            LOG_D("%s init success", _i2c_obj[i].device_name);
        }
        else
        {
            LOG_E("%s register failed", _i2c_obj[i].device_name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);
