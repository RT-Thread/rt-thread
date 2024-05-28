/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *2024-02-14      ShichengChu  first version
 */
#include "drv_hw_i2c.h"
#include <rtdevice.h>
#include <board.h>
#include "drv_pinmux.h"

#define DBG_TAG              "drv.i2c"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#define false 0
#define true  1
struct _i2c_bus
{
    struct rt_i2c_bus_device parent;
    uint8_t i2c_id;
    char *device_name;
};

static struct _i2c_bus _i2c_obj[] =
{
#ifdef BSP_USING_I2C0
    {
        .i2c_id = I2C0,
        .device_name = "i2c0",
    },
#endif /* BSP_USING_I2C0 */
#ifdef BSP_USING_I2C1
    {
        .i2c_id = I2C1,
        .device_name = "i2c1",
    },
#endif /* BSP_USING_I2C1 */
};

static struct i2c_regs *get_i2c_base(uint8_t i2c_id)
{
    struct i2c_regs *i2c_base = NULL;

    switch (i2c_id) {
    case I2C0:
        i2c_base = (struct i2c_regs *)I2C0_BASE;
        break;
    case I2C1:
        i2c_base = (struct i2c_regs *)I2C1_BASE;
        break;
    case I2C2:
        i2c_base = (struct i2c_regs *)I2C2_BASE;
        break;
    case I2C3:
        i2c_base = (struct i2c_regs *)I2C3_BASE;
        break;
    case I2C4:
        i2c_base = (struct i2c_regs *)I2C4_BASE;
        break;
    }

    return i2c_base;
}

static uint32_t get_i2c_intr(uint8_t i2c_id)
{
    uint32_t i2c_intr = 0;

    switch (i2c_id) {
    case I2C0:
        i2c_intr = I2C0_IRQ;
        break;
    case I2C1:
        i2c_intr = I2C1_IRQ;
        break;
    case I2C2:
        i2c_intr = I2C2_IRQ;
        break;
    case I2C3:
        i2c_intr = I2C3_IRQ;
        break;
    case I2C4:
        i2c_intr = I2C4_IRQ;
        break;
    }

    return i2c_intr;
}

void i2c_write_cmd_data(struct i2c_regs *i2c, uint16_t value)
{
    mmio_write_32((uintptr_t)&i2c->ic_cmd_data, value);
}

static void i2c_enable(struct i2c_regs *i2c, uint8_t enable)
{
    uint32_t ena = enable ? IC_ENABLE : 0;
    int timeout = 100;

    do {
        mmio_write_32((uintptr_t)&i2c->ic_enable, ena);
        if ((mmio_read_32((uintptr_t)&i2c->ic_enable_status) & IC_ENABLE) == ena)
            return;

        /*
         * Wait 10 times the signaling period of the highest I2C
         * transfer supported by the driver (for 400KHz this is
         * 25us) as described in the DesignWare I2C databook.
         */
        rt_hw_us_delay(25);
    } while (timeout--);

    LOG_I("timeout in %sabling I2C adapter\n", enable ? "en" : "dis");
}

static void i2c_disable(struct i2c_regs *i2c)
{
    int timeout = 100;

    do {
        mmio_write_32((uintptr_t)&i2c->ic_enable, 0x0);
        if ((mmio_read_32((uintptr_t)&i2c->ic_enable_status) & IC_ENABLE) == 0x0)
            return;

        /*
         * Wait 10 times the signaling period of the highest I2C
         * transfer supported by the driver (for 400KHz this is
         * 25us) as described in the DesignWare I2C databook.
         */
        rt_hw_us_delay(25);
    } while (timeout--);

    LOG_I("timeout in disabling I2C adapter\n");
}

/*
 * i2c_flush_rxfifo - Flushes the i2c RX FIFO
 *
 * Flushes the i2c RX FIFO
 */
static void i2c_flush_rxfifo(struct i2c_regs *i2c)
{
    while (mmio_read_32((uintptr_t)&i2c->ic_status) & IC_STATUS_RFNE)
        mmio_read_32((uintptr_t)&i2c->ic_cmd_data);
}

/*
 * i2c_wait_for_bb - Waits for bus busy
 *
 * Waits for bus busy
 */
static int i2c_wait_for_bb(struct i2c_regs *i2c)
{
    uint16_t    timeout = 0;

    while ((mmio_read_32((uintptr_t)&i2c->ic_status) & IC_STATUS_MA) ||
           !(mmio_read_32((uintptr_t)&i2c->ic_status) & IC_STATUS_TFE)) {

        /* Evaluate timeout */
        rt_hw_us_delay(5);
        timeout++;
        if (timeout > 200) /* exceed 1 ms */
            return 1;
    }

    return 0;
}

/*
 * i2c_setaddress - Sets the target slave address
 * @i2c_addr:    target i2c address
 *
 * Sets the target slave address.
 */
static void i2c_setaddress(struct i2c_regs *i2c, uint16_t i2c_addr)
{
    /* Disable i2c */
    i2c_enable(i2c, false);
    mmio_write_32((uintptr_t)&i2c->ic_tar, i2c_addr);
    /* Enable i2c */
    i2c_enable(i2c, true);
}


static int i2c_xfer_init(struct i2c_regs *i2c, uint16_t chip, uint16_t addr, uint16_t alen)
{
    if (i2c_wait_for_bb(i2c))
        return 1;

    i2c_setaddress(i2c, chip);

    while (alen) {
        alen--;
        /* high byte address going out first */
        i2c_write_cmd_data(i2c, (addr >> (alen * 8)) & 0xff); // TODO
        //mmio_write_32((uintptr_t)&i2c_base->ic_cmd_data, (addr >> (alen * 8)) & 0xff);
    }
    return 0;
}

static int i2c_xfer_finish(struct i2c_regs *i2c)
{
    uint16_t timeout = 0;
    while (1) {
        if ((mmio_read_32((uintptr_t)&i2c->ic_raw_intr_stat) & IC_STOP_DET)) {
            mmio_read_32((uintptr_t)&i2c->ic_clr_stop_det);
            break;
        } else {
            timeout++;
            rt_hw_us_delay(5);
            if (timeout > I2C_STOPDET_TO * 100) {
                LOG_I("%s, tiemout\n", __func__);
                break;
            }
        }
    }

    if (i2c_wait_for_bb(i2c))
        return 1;

    i2c_flush_rxfifo(i2c);

    return 0;
}

/*
 * i2c_read - Read from i2c memory
 * @chip:    target i2c address
 * @addr:    address to read from
 * @alen:
 * @buffer:    buffer for read data
 * @len:    no of bytes to be read
 *
 * Read from i2c memory.
 */
static int hal_i2c_read(uint8_t i2c_id, uint8_t dev, uint16_t addr, uint16_t alen, uint8_t *buffer, uint16_t len)
{
    unsigned int active = 0;
    unsigned int time_count = 0;
    struct i2c_regs *i2c;
    int ret = 0;

    i2c = get_i2c_base(i2c_id);

    i2c_enable(i2c, true);

    if (i2c_xfer_init(i2c, dev, addr, alen))
        return 1;

    while (len) {
        if (!active) {
            /*
             * Avoid writing to ic_cmd_data multiple times
             * in case this loop spins too quickly and the
             * ic_status RFNE bit isn't set after the first
             * write. Subsequent writes to ic_cmd_data can
             * trigger spurious i2c transfer.
             */
            i2c_write_cmd_data(i2c, (dev <<1) | BIT_I2C_CMD_DATA_READ_BIT | BIT_I2C_CMD_DATA_STOP_BIT);
            //mmio_write_32((uintptr_t)&i2c_base->ic_cmd_data, (dev <<1) | BIT_I2C_CMD_DATA_READ_BIT | BIT_I2C_CMD_DATA_STOP_BIT);
            active = 1;
        }

        if (mmio_read_32((uintptr_t)&i2c->ic_raw_intr_stat) & BIT_I2C_INT_RX_FULL) {
            *buffer++ = (uint8_t)mmio_read_32((uintptr_t)&i2c->ic_cmd_data);
            len--;
            time_count = 0;
            active = 0;
        }
        else {
            rt_hw_us_delay(5);
            time_count++;
            if (time_count  >= I2C_BYTE_TO * 100)
                return 1;
        }
    }

    ret = i2c_xfer_finish(i2c);
    i2c_disable(i2c);

    return ret;
}

/*
 * i2c_write - Write to i2c memory
 * @chip:    target i2c address
 * @addr:    address to read from
 * @alen:
 * @buffer:    buffer for read data
 * @len:    no of bytes to be read
 *
 * Write to i2c memory.
 */

static int hal_i2c_write(uint8_t i2c_id, uint8_t dev, uint16_t addr, uint16_t alen, uint8_t *buffer, uint16_t len)
{
    struct i2c_regs *i2c;
    int ret = 0;
    i2c = get_i2c_base(i2c_id);

    i2c_enable(i2c, true);

    if (i2c_xfer_init(i2c, dev, addr, alen))
        return 1;

    while (len) {
        if (i2c->ic_status & IC_STATUS_TFNF) {
            if (--len == 0) {
                i2c_write_cmd_data(i2c, *buffer | IC_STOP);
                //mmio_write_32((uintptr_t)&i2c_base->ic_cmd_data, *buffer | IC_STOP);
            } else {
                i2c_write_cmd_data(i2c, *buffer);
                //mmio_write_32((uintptr_t)&i2c_base->ic_cmd_data, *buffer);
            }
            buffer++;
        } else
            LOG_I("len=%d, ic status is not TFNF\n", len);
    }
    ret = i2c_xfer_finish(i2c);
    i2c_disable(i2c);
    return ret;
}

/*
 * hal_i2c_set_bus_speed - Set the i2c speed
 * @speed:    required i2c speed
 *
 * Set the i2c speed.
 */
static void i2c_set_bus_speed(struct i2c_regs *i2c, unsigned int speed)
{
    unsigned int cntl;
    unsigned int hcnt, lcnt;
    int i2c_spd;

    if (speed > I2C_FAST_SPEED)
        i2c_spd = IC_SPEED_MODE_MAX;
    else if ((speed <= I2C_FAST_SPEED) && (speed > I2C_STANDARD_SPEED))
        i2c_spd = IC_SPEED_MODE_FAST;
    else
        i2c_spd = IC_SPEED_MODE_STANDARD;

    /* to set speed cltr must be disabled */
    i2c_enable(i2c, false);

    cntl = (mmio_read_32((uintptr_t)&i2c->ic_con) & (~IC_CON_SPD_MSK));

    switch (i2c_spd) {
    case IC_SPEED_MODE_MAX:
        cntl |= IC_CON_SPD_HS;
            //hcnt = (u16)(((IC_CLK * MIN_HS100pF_SCL_HIGHTIME) / 1000) - 8);
            /* 7 = 6+1 == MIN LEN +IC_FS_SPKLEN */
            //lcnt = (u16)(((IC_CLK * MIN_HS100pF_SCL_LOWTIME) / 1000) - 1);
            hcnt = 6;
            lcnt = 8;

        mmio_write_32((uintptr_t)&i2c->ic_hs_scl_hcnt, hcnt);
        mmio_write_32((uintptr_t)&i2c->ic_hs_scl_lcnt, lcnt);
        break;

    case IC_SPEED_MODE_STANDARD:
        cntl |= IC_CON_SPD_SS;

        hcnt = (uint16_t)(((IC_CLK * MIN_SS_SCL_HIGHTIME) / 1000) - 7);
        lcnt = (uint16_t)(((IC_CLK * MIN_SS_SCL_LOWTIME) / 1000) - 1);

        mmio_write_32((uintptr_t)&i2c->ic_ss_scl_hcnt, hcnt);
        mmio_write_32((uintptr_t)&i2c->ic_ss_scl_lcnt, lcnt);
        break;

    case IC_SPEED_MODE_FAST:
    default:
        cntl |= IC_CON_SPD_FS;
        hcnt = (uint16_t)(((IC_CLK * MIN_FS_SCL_HIGHTIME) / 1000) - 7);
        lcnt = (uint16_t)(((IC_CLK * MIN_FS_SCL_LOWTIME) / 1000) - 1);

        mmio_write_32((uintptr_t)&i2c->ic_fs_scl_hcnt, hcnt);
        mmio_write_32((uintptr_t)&i2c->ic_fs_scl_lcnt, lcnt);
        break;
    }

    mmio_write_32((uintptr_t)&i2c->ic_con, cntl);

    /* Enable back i2c now speed set */
    i2c_enable(i2c, true);
}

/*
 * __hal_i2c_init - Init function
 * @speed:    required i2c speed
 * @slaveaddr:    slave address for the device
 *
 * Initialization function.
 */
static void hal_i2c_init(uint8_t i2c_id)
{
    struct i2c_regs *i2c;
    uint32_t i2c_intr;

    LOG_I("%s, i2c-%d\n", __func__, i2c_id);
    /* Disable i2c */
    //Need to acquire lock here

    i2c = get_i2c_base(i2c_id);
    i2c_intr = get_i2c_intr(i2c_id);

    // request_irq(i2c_intr, i2c_dw_isr, 0, "IC2_INTR int", &dw_i2c[i2c_id]);

    i2c_enable(i2c, false);
    mmio_write_32((uintptr_t)&i2c->ic_con, (IC_CON_SD | IC_CON_SPD_FS | IC_CON_MM | IC_CON_RE));
    mmio_write_32((uintptr_t)&i2c->ic_rx_tl, IC_RX_TL);
    mmio_write_32((uintptr_t)&i2c->ic_tx_tl, IC_TX_TL);
    mmio_write_32((uintptr_t)&i2c->ic_intr_mask, 0x0);
    i2c_set_bus_speed(i2c, I2C_SPEED);
    //mmio_write_32((uintptr_t)&i2c->ic_sar, slaveaddr);
    /* Enable i2c */
    i2c_enable(i2c, false);

    //Need to release lock here
}

static rt_ssize_t _master_xfer(struct rt_i2c_bus_device *bus,
                             struct rt_i2c_msg msgs[],
                             rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    rt_ssize_t ret = -RT_ERROR;

    struct _i2c_bus *i2c = (struct _i2c_bus *)bus;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_RD)
        {
            hal_i2c_read(i2c->i2c_id, msg->addr, RT_NULL, 1, msg->buf, msg->len);
        }
        else
        {
            hal_i2c_write(i2c->i2c_id, msg->addr, RT_NULL, 1, msg->buf, msg->len);
        }
    }

    return ret;
}

static void rt_hw_i2c_isr(int irqno, void *param)
{
    uint32_t stat, enabled;
    struct i2c_regs *i2c = (struct i2c_regs *)param;

    enabled = mmio_read_32((uintptr_t)&i2c->ic_enable);
    stat = mmio_read_32((uintptr_t)&i2c->ic_intr_stat);

    LOG_I("i2c interrupt stat: 0x%08x", stat);
}

static const struct rt_i2c_bus_device_ops i2c_ops =
{
    .master_xfer      = _master_xfer,
    .slave_xfer       = RT_NULL,
    .i2c_bus_control  = RT_NULL
};


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
// I2C0 is not ALLOWED for Duo
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
// I2C4 is not ALLOWED for Duo
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

    for (rt_size_t i = 0; i < sizeof(_i2c_obj) / sizeof(struct _i2c_bus); i++)
    {
        hal_i2c_init(_i2c_obj->i2c_id);

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

        uint32_t irqno = get_i2c_intr(_i2c_obj[i].i2c_id);
        struct i2c_regs *_i2c = get_i2c_base(_i2c_obj[i].i2c_id);
        rt_hw_interrupt_install(irqno, rt_hw_i2c_isr, _i2c, _i2c_obj[i].device_name);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);
