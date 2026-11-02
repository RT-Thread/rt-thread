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

#define DBG_TAG "i2c.brcmstb"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>
#include <drivers/dev_i2c_dm.h>

#define N_DATA_REGS                     8

/*
 * PER_I2C/BSC count register mask depends on 1 byte/4 byte data register
 * size. Cable modem and DSL SoCs with Peripheral i2c cores use 1 byte per
 * data register whereas STB SoCs use 4 byte per data register transfer,
 * account for this difference in total count per transaction and mask to use.
 */
#define BSC_CNT_REG1_MASK(nb)           (nb == 1 ? RT_GENMASK(3, 0) : RT_GENMASK(5, 0))
#define BSC_CNT_REG1_SHIFT              0

/* BSC CTL register field definitions */
#define BSC_CTL_REG_DTF_MASK            0x00000003
#define BSC_CTL_REG_SCL_SEL_MASK        0x00000030
#define BSC_CTL_REG_SCL_SEL_SHIFT       4
#define BSC_CTL_REG_INT_EN_MASK         0x00000040
#define BSC_CTL_REG_INT_EN_SHIFT        6
#define BSC_CTL_REG_DIV_CLK_MASK        0x00000080

/* BSC_IIC_ENABLE r/w enable and interrupt field definitions */
#define BSC_IIC_EN_RESTART_MASK         0x00000040
#define BSC_IIC_EN_NOSTART_MASK         0x00000020
#define BSC_IIC_EN_NOSTOP_MASK          0x00000010
#define BSC_IIC_EN_NOACK_MASK           0x00000004
#define BSC_IIC_EN_INTRP_MASK           0x00000002
#define BSC_IIC_EN_ENABLE_MASK          0x00000001

/* BSC_CTLHI control register field definitions */
#define BSC_CTLHI_REG_DATAREG_SIZE_MASK 0x00000040
#define BSC_CTLHI_REG_IGNORE_ACK_MASK   0x00000002
#define BSC_CTLHI_REG_WAIT_DIS_MASK     0x00000001

#define I2C_TIMEOUT                     100 /* msecs */

/* Condition mask used for non combined transfer */
#define COND_RESTART                    BSC_IIC_EN_RESTART_MASK
#define COND_NOSTART                    BSC_IIC_EN_NOSTART_MASK
#define COND_NOSTOP                     BSC_IIC_EN_NOSTOP_MASK
#define COND_START_STOP                 (COND_RESTART | COND_NOSTART | COND_NOSTOP)

/* BSC data transfer direction */
#define DTF_WR_MASK                     0x00000000
#define DTF_RD_MASK                     0x00000001
/* BSC data transfer direction combined format */
#define DTF_RD_WR_MASK                  0x00000002
#define DTF_WR_RD_MASK                  0x00000003

#define AUTOI2C_CTRL0                   0x26c
#define AUTOI2C_CTRL0_RELEASE_BSC       RT_BIT(1)

/* BSC block register map structure to cache fields to be written */
struct bsc_regs
{
    rt_uint32_t chip_address;           /* slave address */
    rt_uint32_t data_in[N_DATA_REGS];   /* tx data buffer*/
    rt_uint32_t cnt_reg;                /* rx/tx data length */
    rt_uint32_t ctl_reg;                /* control register */
    rt_uint32_t iic_enable;             /* xfer enable and status */
    rt_uint32_t data_out[N_DATA_REGS];  /* rx data buffer */
    rt_uint32_t ctlhi_reg;              /* more control fields */
    rt_uint32_t scl_param;              /* reserved */
};

struct bsc_clk_param
{
    rt_uint32_t hz;
    rt_uint32_t scl_mask;
    rt_uint32_t div_mask;
};

enum bsc_xfer_cmd
{
    CMD_WR,
    CMD_RD,
    CMD_WR_NOACK,
    CMD_RD_NOACK,
};

enum bus_speeds
{
    SPD_375K,
    SPD_390K,
    SPD_187K,
    SPD_200K,
    SPD_93K,
    SPD_97K,
    SPD_46K,
    SPD_50K,
};

static const struct bsc_clk_param bsc_clk[] =
{
    [SPD_375K] =
    {
        .hz = 375000,
        .scl_mask = SPD_375K << BSC_CTL_REG_SCL_SEL_SHIFT,
        .div_mask = 0,
    },
    [SPD_390K] =
    {
        .hz = 390000,
        .scl_mask = SPD_390K << BSC_CTL_REG_SCL_SEL_SHIFT,
        .div_mask = 0,
    },
    [SPD_187K] =
    {
        .hz = 187500,
        .scl_mask = SPD_187K << BSC_CTL_REG_SCL_SEL_SHIFT,
        .div_mask = 0,
    },
    [SPD_200K] =
    {
        .hz = 200000,
        .scl_mask = SPD_200K << BSC_CTL_REG_SCL_SEL_SHIFT,
        .div_mask = 0,
    },
    [SPD_93K] =
    {
        .hz = 93750,
        .scl_mask = SPD_375K << BSC_CTL_REG_SCL_SEL_SHIFT,
        .div_mask = BSC_CTL_REG_DIV_CLK_MASK,
    },
    [SPD_97K] =
    {
        .hz = 97500,
        .scl_mask = SPD_390K << BSC_CTL_REG_SCL_SEL_SHIFT,
        .div_mask = BSC_CTL_REG_DIV_CLK_MASK,
    },
    [SPD_46K] =
    {
        .hz = 46875,
        .scl_mask = SPD_187K << BSC_CTL_REG_SCL_SEL_SHIFT,
        .div_mask = BSC_CTL_REG_DIV_CLK_MASK,
    },
    [SPD_50K] =
    {
        .hz = 50000,
        .scl_mask = SPD_200K << BSC_CTL_REG_SCL_SEL_SHIFT,
        .div_mask = BSC_CTL_REG_DIV_CLK_MASK,
    }
};

struct brcmstb_i2c
{
    struct rt_i2c_bus_device parent;

    int irq;
    void *base;
    struct bsc_regs bsc_regmap;

    int data_regsz;
    rt_uint32_t clk_freq_hz;
    struct rt_completion done;
};

#define raw_to_brcmstb_i2c(raw) rt_container_of(raw, struct brcmstb_i2c, parent)

#define bsc_readl(i2c, reg)         HWREG32((i2c)->base + rt_offsetof(struct bsc_regs, reg))
#define bsc_writel(i2c, reg, val)   HWREG32((i2c)->base + rt_offsetof(struct bsc_regs, reg)) = (val)

rt_inline int brcmstb_i2c_get_xfersz(struct brcmstb_i2c *i2c)
{
    return (N_DATA_REGS * i2c->data_regsz);
}

rt_inline int brcmstb_i2c_get_data_regsz(struct brcmstb_i2c *i2c)
{
    return i2c->data_regsz;
}

static void brcmstb_i2c_enable_disable_irq(struct brcmstb_i2c *i2c, rt_bool_t int_en)
{
    if (int_en)
    {
        /* Enable BSC  CTL interrupt line */
        i2c->bsc_regmap.ctl_reg |= BSC_CTL_REG_INT_EN_MASK;
    }
    else
    {
        /* Disable BSC CTL interrupt line */
        i2c->bsc_regmap.ctl_reg &= ~BSC_CTL_REG_INT_EN_MASK;
    }

    rt_hw_barrier();
    bsc_writel(i2c, ctl_reg, i2c->bsc_regmap.ctl_reg);
}

/* Wait for device to be ready */
static rt_err_t brcmstb_i2c_wait_if_busy(struct brcmstb_i2c *i2c)
{
    rt_tick_t timeout;

    timeout = rt_tick_from_millisecond(I2C_TIMEOUT);
    timeout += rt_tick_get();

    while ((bsc_readl(i2c, iic_enable) & BSC_IIC_EN_INTRP_MASK))
    {
        if (rt_tick_get() > timeout)
        {
            return -RT_ETIMEOUT;
        }

        rt_hw_cpu_relax();
    }

    return RT_EOK;
}

/* i2c xfer completion function, handles both irq and polling mode */
static rt_err_t brcmstb_i2c_wait_for_completion(struct brcmstb_i2c *i2c)
{
    rt_tick_t timeout;
    rt_err_t err = RT_EOK;

    timeout = rt_tick_from_millisecond(I2C_TIMEOUT);
    timeout += rt_tick_get();

    if (i2c->irq >= 0)
    {
        err = rt_completion_wait(&i2c->done, timeout);
    }
    else
    {
        /* Polling mode */
        rt_uint32_t bsc_intrp;

        do {
            bsc_intrp = bsc_readl(i2c, iic_enable) & BSC_IIC_EN_INTRP_MASK;

            if (rt_tick_get() > timeout)
            {
                err = -RT_ETIMEOUT;
                break;
            }

            rt_hw_cpu_relax();
        } while (!bsc_intrp);
    }

    if (i2c->irq < 0 || err == -RT_ETIMEOUT)
    {
        brcmstb_i2c_enable_disable_irq(i2c, RT_FALSE);
    }

    return err;
}

/* Set xfer START/STOP conditions for subsequent transfer */
static void brcmstb_set_i2c_start_stop(struct brcmstb_i2c *i2c, rt_uint32_t cond_flag)
{
    rt_uint32_t regval = i2c->bsc_regmap.iic_enable;

    i2c->bsc_regmap.iic_enable = (regval & ~COND_START_STOP) | cond_flag;
}

/* Send I2C request check completion */
static rt_err_t brcmstb_send_i2c_cmd(struct brcmstb_i2c *i2c, enum bsc_xfer_cmd cmd)
{
    rt_err_t err;
    struct bsc_regs *pi2creg = &i2c->bsc_regmap;

    /* Make sure the hardware is ready */
    if ((err = brcmstb_i2c_wait_if_busy(i2c)))
    {
        return err;
    }

    /* Enable BSC CTL interrupt line */
    brcmstb_i2c_enable_disable_irq(i2c, RT_TRUE);

    /* Initiate transfer by setting iic_enable */
    pi2creg->iic_enable |= BSC_IIC_EN_ENABLE_MASK;
    bsc_writel(i2c, iic_enable, pi2creg->iic_enable);

    /* Wait for transaction to finish or timeout */
    if ((err = brcmstb_i2c_wait_for_completion(i2c)))
    {
        goto _cmd_out;
    }

    if ((cmd == CMD_RD || cmd == CMD_WR) && bsc_readl(i2c, iic_enable) & BSC_IIC_EN_NOACK_MASK)
    {
        err = -RT_EIO;
    }

_cmd_out:
    bsc_writel(i2c, cnt_reg, 0);
    bsc_writel(i2c, iic_enable, 0);

    return err;
}

/* Actual data transfer through the BSC master */
static rt_err_t brcmstb_i2c_xfer_bsc_data(struct brcmstb_i2c *i2c,
        rt_uint8_t *buf, rt_size_t len, struct rt_i2c_msg *msg)
{
    rt_err_t err;
    int data_regsz;
    rt_uint32_t ctl_reg;
    enum bsc_xfer_cmd cmd;
    struct bsc_regs *pi2creg = &i2c->bsc_regmap;

    data_regsz = brcmstb_i2c_get_data_regsz(i2c);

    if (msg->flags & RT_I2C_IGNORE_NACK)
    {
        cmd = (msg->flags & RT_I2C_RD) ? CMD_RD_NOACK : CMD_WR_NOACK;
        pi2creg->ctlhi_reg |= BSC_CTLHI_REG_IGNORE_ACK_MASK;
    }
    else
    {
        cmd = (msg->flags & RT_I2C_RD) ? CMD_RD : CMD_WR;
        pi2creg->ctlhi_reg &= ~BSC_CTLHI_REG_IGNORE_ACK_MASK;
    }
    bsc_writel(i2c, ctlhi_reg, pi2creg->ctlhi_reg);

    /* Set data transfer direction */
    ctl_reg = pi2creg->ctl_reg & ~BSC_CTL_REG_DTF_MASK;

    if (cmd == CMD_WR || cmd == CMD_WR_NOACK)
    {
        pi2creg->ctl_reg = ctl_reg | DTF_WR_MASK;
    }
    else
    {
        pi2creg->ctl_reg = ctl_reg | DTF_RD_MASK;
    }

    /* Set the read/write length */
    bsc_writel(i2c, cnt_reg, BSC_CNT_REG1_MASK(data_regsz) & (len << BSC_CNT_REG1_SHIFT));

    /* Write data into data_in register */
    if (cmd == CMD_WR || cmd == CMD_WR_NOACK)
    {
        for (int cnt = 0, i = 0; cnt < len; cnt += data_regsz, ++i)
        {
            rt_uint32_t word = 0;

            for (int byte = 0; byte < data_regsz; ++byte)
            {
                word >>= RT_BITS_PER_BYTE;

                if ((cnt + byte) < len)
                {
                    word |= buf[cnt + byte] << (RT_BITS_PER_BYTE * (data_regsz - 1));
                }
            }

            bsc_writel(i2c, data_in[i], word);
        }
    }

    /* Initiate xfer, the function will return on completion */
    if ((err = brcmstb_send_i2c_cmd(i2c, cmd)))
    {
        return err;
    }

    /* Read data from data_out register */
    if (cmd == CMD_RD || cmd == CMD_RD_NOACK)
    {
        for (int cnt = 0, i = 0; cnt < len; cnt += data_regsz, ++i)
        {
            rt_uint32_t data = bsc_readl(i2c, data_out[i]);

            for (int byte = 0; byte < data_regsz && byte + cnt < len; ++byte)
            {
                buf[cnt + byte] = data & 0xff;
                data >>= RT_BITS_PER_BYTE;
            }
        }
    }

    return RT_EOK;
}

/* Write a single byte of data to the i2c bus */
static rt_err_t brcmstb_i2c_write_data_byte(struct brcmstb_i2c *i2c,
        rt_uint32_t *buf, rt_uint32_t nak_expected)
{
    enum bsc_xfer_cmd cmd = nak_expected ? CMD_WR : CMD_WR_NOACK;

    bsc_writel(i2c, cnt_reg, 1);
    bsc_writel(i2c, data_in, *buf);

    return brcmstb_send_i2c_cmd(i2c, cmd);
}

/* Send i2c address */
static rt_err_t brcmstb_i2c_do_addr(struct brcmstb_i2c *i2c, struct rt_i2c_msg *msg)
{
    rt_err_t err;
    rt_uint8_t addr;

    if (msg->flags & RT_I2C_ADDR_10BIT)
    {
        /* First byte is 11110XX0 where XX is upper 2 bits */
        addr = 0xf0 | ((msg->addr & 0x300) >> 7);
        bsc_writel(i2c, chip_address, addr);

        /* Second byte is the remaining 8 bits */
        addr = msg->addr & 0xff;
        if ((err = brcmstb_i2c_write_data_byte(i2c, (void *)&addr, 0)))
        {
            return err;
        }

        if (msg->flags & RT_I2C_RD)
        {
            /* For read, send restart without stop condition */
            brcmstb_set_i2c_start_stop(i2c, COND_RESTART | COND_NOSTOP);

            /* Then re-send the first byte with the read bit set */
            addr = 0xf0 | ((msg->addr & 0x300) >> 7) | 0x01;
            if ((err = brcmstb_i2c_write_data_byte(i2c, (void *)&addr, 0)))
            {
                return err;
            }
        }
    }
    else
    {
        /* 8bit addr from msg */
        addr = (msg->addr << 1) | (msg->flags & RT_I2C_RD ? 1 : 0);;
        bsc_writel(i2c, chip_address, addr);
    }

    return RT_EOK;
}

static rt_ssize_t brcmstb_i2c_master_xfer(struct rt_i2c_bus_device *bus,
        struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    rt_err_t err;
    rt_uint8_t *tmp_buf;
    int bytes_to_xfer, xfersz, len;
    rt_uint32_t cond, cond_per_msg;
    struct rt_i2c_msg *pmsg;
    struct brcmstb_i2c *i2c = raw_to_brcmstb_i2c(bus);

    xfersz = brcmstb_i2c_get_xfersz(i2c);

    /* Loop through all messages */
    for (int i = 0; i < num; ++i)
    {
        pmsg = &msgs[i];
        len = pmsg->len;
        tmp_buf = pmsg->buf;

        if (i < num - 1 && (msgs[i + 1].flags & RT_I2C_NO_START))
        {
            cond = ~COND_START_STOP;
        }
        else
        {
            cond = COND_RESTART | COND_NOSTOP;
        }

        brcmstb_set_i2c_start_stop(i2c, cond);

        /* Send slave address */
        if (!(pmsg->flags & RT_I2C_NO_START))
        {
            if ((err = brcmstb_i2c_do_addr(i2c, pmsg)))
            {
                return err;
            }
        }

        cond_per_msg = cond;

        /* Perform data transfer */
        while (len)
        {
            bytes_to_xfer = rt_min(len, xfersz);

            if (len <= xfersz)
            {
                if (i == num - 1)
                {
                    cond_per_msg = cond_per_msg & ~(COND_RESTART | COND_NOSTOP);
                }
                else
                {
                    cond_per_msg = cond;
                }
            }
            else
            {
                cond_per_msg = (cond_per_msg & ~COND_RESTART) | COND_NOSTOP;
            }

            brcmstb_set_i2c_start_stop(i2c, cond_per_msg);

            if ((err = brcmstb_i2c_xfer_bsc_data(i2c, tmp_buf, bytes_to_xfer, pmsg)))
            {
                return err;
            }

            len -=  bytes_to_xfer;
            tmp_buf += bytes_to_xfer;

            cond_per_msg = COND_NOSTART | COND_NOSTOP;
        }
    }

    return num;
}

const static struct rt_i2c_bus_device_ops brcmstb_i2c_ops =
{
    .master_xfer = brcmstb_i2c_master_xfer,
};

static void brcmstb_i2c_isr(int irq, void *param)
{
    rt_uint32_t status_bsc_ctl;
    struct brcmstb_i2c *i2c = param;

    status_bsc_ctl = bsc_readl(i2c, ctl_reg);

    if (!(status_bsc_ctl & BSC_CTL_REG_INT_EN_MASK))
    {
        return;
    }

    brcmstb_i2c_enable_disable_irq(i2c, RT_FALSE);
    rt_completion_done(&i2c->done);
}

static void brcmstb_i2c_set_bsc_reg_defaults(struct brcmstb_i2c *i2c)
{
    int i, num_speeds = RT_ARRAY_SIZE(bsc_clk);
    rt_uint32_t clk_freq_hz = i2c->clk_freq_hz;

    if (brcmstb_i2c_get_data_regsz(i2c) == sizeof(rt_uint32_t))
    {
        i2c->bsc_regmap.ctlhi_reg = BSC_CTLHI_REG_DATAREG_SIZE_MASK;
    }
    else
    {
        i2c->bsc_regmap.ctlhi_reg &= ~BSC_CTLHI_REG_DATAREG_SIZE_MASK;
    }

    bsc_writel(i2c, ctlhi_reg, i2c->bsc_regmap.ctlhi_reg);

    /* Set bus speed */
    for (i = 0; i < num_speeds; ++i)
    {
        if (bsc_clk[i].hz == clk_freq_hz)
        {
            i2c->bsc_regmap.ctl_reg &= ~(BSC_CTL_REG_SCL_SEL_MASK | BSC_CTL_REG_DIV_CLK_MASK);
            i2c->bsc_regmap.ctl_reg |= bsc_clk[i].scl_mask | bsc_clk[i].div_mask;
            bsc_writel(i2c, ctl_reg, i2c->bsc_regmap.ctl_reg);
            break;
        }
    }

    /* in case we did not get find a valid speed */
    if (i == num_speeds)
    {
        i = (bsc_readl(i2c, ctl_reg) & BSC_CTL_REG_SCL_SEL_MASK) >> BSC_CTL_REG_SCL_SEL_SHIFT;
    }
}

static void brcmstb_i2c_free(struct brcmstb_i2c *i2c)
{
    if (i2c->base)
    {
        rt_iounmap(i2c->base);
    }

    rt_free(i2c);
}

static rt_err_t brcmstb_i2c_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    void *autoi2c;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct brcmstb_i2c *i2c = rt_calloc(1, sizeof(*i2c));

    if (!i2c)
    {
        return -RT_ENOMEM;
    }

    i2c->base = rt_dm_dev_iomap(dev, 0);

    if (!i2c->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (rt_dm_dev_prop_read_bool(dev, "reg-names"))
    {
        if (!(autoi2c = rt_dm_dev_iomap_by_name(dev, "auto-i2c")))
        {
            err = -RT_EIO;
            goto _fail;
        }

        HWREG32(autoi2c + AUTOI2C_CTRL0) = AUTOI2C_CTRL0_RELEASE_BSC;
        rt_iounmap(autoi2c);

        i2c->bsc_regmap.iic_enable = 0;
        bsc_writel(i2c, iic_enable, i2c->bsc_regmap.iic_enable);
    }

    i2c->irq = rt_dm_dev_get_irq(dev, 0);

    brcmstb_i2c_enable_disable_irq(i2c, RT_FALSE);

    if (rt_dm_dev_prop_read_u32(dev, "clock-frequency", &i2c->clk_freq_hz))
    {
        i2c->clk_freq_hz = bsc_clk[0].hz;
    }

    if (rt_ofw_node_is_compatible(dev->ofw_node, "brcm,brcmper-i2c"))
    {
        i2c->data_regsz = sizeof(rt_uint8_t);
    }
    else
    {
        i2c->data_regsz = sizeof(rt_uint32_t);
    }

    brcmstb_i2c_set_bsc_reg_defaults(i2c);

    rt_completion_init(&i2c->done);

    rt_dm_dev_set_name_auto(&i2c->parent.parent, "i2c");
    dev_name = rt_dm_dev_get_name(&i2c->parent.parent);

    if (i2c->irq >= 0)
    {
        rt_hw_interrupt_install(i2c->irq, brcmstb_i2c_isr, i2c, dev_name);
        rt_hw_interrupt_umask(i2c->irq);
    }

    dev->user_data = i2c;

    i2c->parent.ops = &brcmstb_i2c_ops;
    i2c->parent.parent.ofw_node = dev->ofw_node;

    if ((err = rt_i2c_bus_device_register(&i2c->parent, dev_name)))
    {
        goto _free_irq;
    }

    rt_dm_dev_bind_fwdata(dev, RT_NULL, i2c);

    return RT_EOK;
_free_irq:
    if (i2c->irq >= 0)
    {
        rt_hw_interrupt_mask(i2c->irq);
        rt_pic_detach_irq(i2c->irq, i2c);
    }

_fail:
    brcmstb_i2c_free(i2c);

    return err;
}

static rt_err_t brcmstb_i2c_remove(struct rt_platform_device *pdev)
{
    struct brcmstb_i2c *i2c = pdev->parent.user_data;

    if (i2c->irq >= 0)
    {
        rt_hw_interrupt_mask(i2c->irq);
        rt_pic_detach_irq(i2c->irq, i2c);
    }

    rt_device_unregister(&i2c->parent.parent);

    brcmstb_i2c_free(i2c);

    return RT_EOK;
}

static const struct rt_ofw_node_id brcmstb_i2c_ofw_ids[] =
{
    { .compatible = "brcm,brcmstb-i2c" },
    { .compatible = "brcm,brcmper-i2c" },
    { .compatible = "brcm,bcm2711-hdmi-i2c" },
    { /* sentinel */ }
};

static struct rt_platform_driver brcmstb_i2c_driver =
{
    .name = "brcmstb-i2c",
    .ids = brcmstb_i2c_ofw_ids,

    .probe = brcmstb_i2c_probe,
    .remove = brcmstb_i2c_remove,
};
RT_PLATFORM_DRIVER_EXPORT(brcmstb_i2c_driver);
