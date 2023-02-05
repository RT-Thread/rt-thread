/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author         Notes
* 2021-04-20      Wayne          First version
******************************************************************************/


#include <rtconfig.h>

#if defined( BSP_USING_I2C)

#include <rtdevice.h>
#include "NuMicro.h"
//#include <drv_i2c.h>
#include <drv_sys.h>

/* Private define ---------------------------------------------------------------*/
#define LOG_TAG    "drv.i2c"
#define DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL DBG_ERROR
#define DBG_COLOR
#include <rtdbg.h>

#define I2C_REG_WRITE(dev, addr, byte)        outpw(dev->base + addr, byte)
#define I2C_REG_READ(dev, addr)               inpw(dev->base + addr)

#define I2C_DISABLE(dev)     I2C_REG_WRITE(dev, I2C_CSR, 0x00)  /* Disable i2c core and interrupt */
#define I2C_ENABLE(dev)      I2C_REG_WRITE(dev, I2C_CSR, 0x3)    /* Enable i2c core and interrupt  */
#define I2C_ISBUSFREE(dev)   (((I2C_REG_READ(dev, I2C_SWR) & 0x18) == 0x18 && (I2C_REG_READ(dev, I2C_CSR) & 0x0400) == 0) ? 1 : 0)

#define I2C_SIGNAL_TIMEOUT   5000

enum
{
    I2C_START = -1,
#if defined(BSP_USING_I2C0)
    I2C0_IDX,
#endif
#if defined(BSP_USING_I2C1)
    I2C1_IDX,
#endif
    I2C_CNT
};

/* Private typedef --------------------------------------------------------------*/
typedef struct
{
    int32_t base;       /* i2c bus number */
    volatile int32_t state;
    int32_t addr;
    uint32_t last_error;
    int32_t bNackValid;

    uint32_t subaddr;
    int32_t subaddr_len;

    volatile uint32_t pos;
    volatile uint32_t len;
    uint8_t *buffer;

    struct rt_completion signal;
} nu_i2c_dev;
typedef nu_i2c_dev *nu_i2c_dev_t;

typedef struct
{
    struct rt_i2c_bus_device parent;
    char *name;
    IRQn_Type irqn;
    E_SYS_IPRST rstidx;
    E_SYS_IPCLK clkidx;

    struct rt_i2c_msg *cur_i2c_msg;

    nu_i2c_dev dev;
} nu_i2c_bus ;
typedef nu_i2c_bus *nu_i2c_bus_t;
/* Private variables ------------------------------------------------------------*/

static nu_i2c_bus nu_i2c_arr [ ] =
{
#if defined(BSP_USING_I2C0)
    {
        .dev =
        {
            .base = I2C0_BA,
        },
        .name = "i2c0",
        .irqn = IRQ_I2C0,
        .rstidx = I2C0RST,
        .clkidx = I2C0CKEN,
    },
#endif
#if defined(BSP_USING_I2C1)
    {
        .dev =
        {
            .base = I2C1_BA,
        },
        .name = "i2c1",
        .irqn = IRQ_I2C1,
        .rstidx = I2C1RST,
        .clkidx = I2C1CKEN,
    },
#endif
};

/* Private functions ------------------------------------------------------------*/
/**
  * @brief  Set i2c interface speed
  * @param[in] dev i2c device structure pointer
  * @param[in] sp i2c speed
  * @return 0 or I2C_ERR_NOTTY
  */
static int32_t nu_i2c_set_speed(nu_i2c_dev_t psNuI2cDev, int32_t sp)
{
    uint32_t d;

    if ((sp != 100) && (sp != 400))
        return (I2C_ERR_NOTTY);

    d = (sysGetClock(SYS_PCLK) * 1000) / (sp * 5) - 1;

    I2C_REG_WRITE(psNuI2cDev, I2C_DIVIDER, d & 0xffff);

    return 0;
}

/**
  * @brief  Configure i2c command
  * @param[in] dev i2c device structure pointer
  * @param[in] cmd command
  * @return None
  */
static void nu_i2c_command(nu_i2c_dev_t psNuI2cDev, int32_t cmd)
{
    psNuI2cDev->bNackValid = (cmd & I2C_CMD_WRITE) ? 1 : 0;
    I2C_REG_WRITE(psNuI2cDev, I2C_CMDR,  cmd);
}

/**
  * @brief Configure slave address data
  * @param[in] dev i2c device structure pointer
  * @param[in] mode could be write or read
  * @return None
  */
static void nu_i2c_calculate_address(nu_i2c_dev_t psNuI2cDev, int32_t mode)
{
    int32_t i;
    uint32_t subaddr = psNuI2cDev->subaddr;

    psNuI2cDev->buffer[0] = (((psNuI2cDev->addr << 1) & 0xfe) | I2C_WRITE) & 0xff;

    for (i = psNuI2cDev->subaddr_len; i > 0; i--)
    {
        psNuI2cDev->buffer[i] = subaddr & 0xff;
        subaddr >>= 8;
    }

    if (mode == I2C_STATE_READ)
    {
        i = psNuI2cDev->subaddr_len + 1;
        psNuI2cDev->buffer[i] = (((psNuI2cDev->addr << 1) & 0xfe)) | I2C_READ;
    }
}

/**
  * @brief Reset some variables
  * @param[in] dev i2c device structure pointer
  * @return None
  */
static void nu_i2c_reset(nu_i2c_dev_t psNuI2cDev)
{
    psNuI2cDev->addr = -1;
    psNuI2cDev->last_error = 0;
    psNuI2cDev->subaddr = 0;
    psNuI2cDev->subaddr_len = 0;
}

static void nu_i2c_isr(int vector, void *param)
{
    nu_i2c_bus_t psNuI2CBus = (nu_i2c_bus_t)param;
    nu_i2c_dev_t psNuI2CDev = (nu_i2c_dev_t)&psNuI2CBus->dev;
    struct rt_i2c_msg *pmsg = psNuI2CBus->cur_i2c_msg;
    uint32_t msg_flag = pmsg->flags;

    uint32_t csr, val;

    csr = I2C_REG_READ(psNuI2CDev, I2C_CSR);
    csr |= 0x04;

    /* Clear interrupt flag */
    I2C_REG_WRITE(psNuI2CDev, I2C_CSR, csr);

    if (psNuI2CDev->state == I2C_STATE_NOP)
        return;

    /* NACK only valid in WRITE */
    if ((csr & 0x800) && psNuI2CDev->bNackValid && !(msg_flag & RT_I2C_IGNORE_NACK))
    {
        rt_kprintf("I2C W/ NACK\n");
        psNuI2CDev->last_error = I2C_ERR_NACK;
        nu_i2c_command(psNuI2CDev, I2C_CMD_STOP);
        psNuI2CDev->state = I2C_STATE_NOP;
        rt_completion_done(&psNuI2CDev->signal);
    }
    /* Arbitration lost */
    else if (csr & 0x200)
    {
        rt_kprintf("Arbitration lost\n");
        psNuI2CDev->last_error = I2C_ERR_LOSTARBITRATION;
        psNuI2CDev->state = I2C_STATE_NOP;
        rt_completion_done(&psNuI2CDev->signal);
    }
    /* Transmit complete */
    else if (!(csr & 0x100))
    {
        /* Send address state */
        if (psNuI2CDev->pos < psNuI2CDev->subaddr_len + 1)
        {
            val = psNuI2CDev->buffer[psNuI2CDev->pos++] & 0xff;
            I2C_REG_WRITE(psNuI2CDev, I2C_TxR, val);
            nu_i2c_command(psNuI2CDev, I2C_CMD_WRITE);
        }
        else if (psNuI2CDev->state == I2C_STATE_READ)
        {

            /* Sub-address send over, begin restart a read command */
            if (psNuI2CDev->pos == psNuI2CDev->subaddr_len + 1)
            {
                val = psNuI2CDev->buffer[psNuI2CDev->pos++];
                I2C_REG_WRITE(psNuI2CDev, I2C_TxR, val);
                nu_i2c_command(psNuI2CDev, I2C_CMD_START | I2C_CMD_WRITE);
            }
            else
            {
                psNuI2CDev->buffer[psNuI2CDev->pos++] = I2C_REG_READ(psNuI2CDev, I2C_RxR) & 0xff;
                if (psNuI2CDev->pos < psNuI2CDev->len)
                {
                    /* Last character */
                    if (psNuI2CDev->pos == psNuI2CDev->len - 1)
                        nu_i2c_command(psNuI2CDev, I2C_CMD_READ | I2C_CMD_STOP | I2C_CMD_NACK);
                    else
                        nu_i2c_command(psNuI2CDev, I2C_CMD_READ);
                }
                else
                {
                    psNuI2CDev->state = I2C_STATE_NOP;
                    rt_completion_done(&psNuI2CDev->signal);
                }
            }
        }
        /* Write data */
        else if (psNuI2CDev->state == I2C_STATE_WRITE)
        {

            if (psNuI2CDev->pos < psNuI2CDev->len)
            {
                val = psNuI2CDev->buffer[psNuI2CDev->pos];

                I2C_REG_WRITE(psNuI2CDev, I2C_TxR, val);

                /* Last character */
                if (psNuI2CDev->pos == psNuI2CDev->len - 1)
                    nu_i2c_command(psNuI2CDev, I2C_CMD_WRITE | I2C_CMD_STOP);
                else
                    nu_i2c_command(psNuI2CDev, I2C_CMD_WRITE);

                psNuI2CDev->pos ++;
            }
            else
            {
                psNuI2CDev->state = I2C_STATE_NOP;
                rt_completion_done(&psNuI2CDev->signal);
            }
        }
    }

}

/**
  * @brief Read data from I2C slave.
  * @param[in] psNuI2cDev is interface structure pointer.
  * @param[in] pmsg is pointer of rt i2c message structure.
  * @return read status.
  * @retval >0 length when success.
  * @retval I2C_ERR_BUSY Interface busy.
  * @retval I2C_ERR_IO Interface not opened.
  * @retval I2C_ERR_NODEV No such device.
  * @retval I2C_ERR_NACK Slave returns an erroneous ACK.
  * @retval I2C_ERR_LOSTARBITRATION arbitration lost happen.
  */
static int32_t nu_i2c_read(nu_i2c_dev_t psNuI2cDev, struct rt_i2c_msg *pmsg)
{
    uint8_t *buf = pmsg->buf;
    uint32_t len = pmsg->len;

    RT_ASSERT(len);
    RT_ASSERT(buf);

    if (len > I2C_MAX_BUF_LEN - 10)
        len = I2C_MAX_BUF_LEN - 10;

    psNuI2cDev->state = I2C_STATE_READ;
    psNuI2cDev->pos = 1;

    /* Current ISR design will get one garbage byte */
    /* plus 1 unused char */
    psNuI2cDev->len = psNuI2cDev->subaddr_len + 1 + len + 2;
    psNuI2cDev->last_error = 0;

    /* Get slave address */
    nu_i2c_calculate_address(psNuI2cDev, I2C_STATE_READ);

    /* Enable I2C-EN */
    I2C_ENABLE(psNuI2cDev);

    /* Send first byte to transfer the message. */
    I2C_REG_WRITE(psNuI2cDev, I2C_TxR, psNuI2cDev->buffer[0] & 0xff);

    if (!I2C_ISBUSFREE(psNuI2cDev))
        return (I2C_ERR_BUSY);

    rt_completion_init(&psNuI2cDev->signal);

    nu_i2c_command(psNuI2cDev, I2C_CMD_START | I2C_CMD_WRITE);

    if ((RT_EOK == rt_completion_wait(&psNuI2cDev->signal, I2C_SIGNAL_TIMEOUT)))
    {
        rt_memcpy(buf, psNuI2cDev->buffer + psNuI2cDev->subaddr_len + 3, len);

        psNuI2cDev->subaddr += len;
    }
    else
    {
        rt_kprintf("[%s]Wait signal timeout.\n", __func__);

        len = 0;
    }

    /* Disable I2C-EN */
    I2C_DISABLE(psNuI2cDev);

    if (psNuI2cDev->last_error)
        return (psNuI2cDev->last_error);

    return len;
}

/**
  * @brief Write data from I2C slave.
  * @param[in] psNuI2cDev is interface structure pointer.
  * @param[in] pmsg is pointer of rt i2c message structure.
  * @return write status.
  * @retval >0 length when success.
  * @retval I2C_ERR_BUSY Interface busy.
  * @retval I2C_ERR_IO Interface not opened.
  * @retval I2C_ERR_NODEV No such device.
  * @retval I2C_ERR_NACK Slave returns an erroneous ACK.
  * @retval I2C_ERR_LOSTARBITRATION arbitration lost happen.
  */
static int32_t nu_i2c_write(nu_i2c_dev_t psNuI2cDev, struct rt_i2c_msg *pmsg)
{
    uint8_t *buf = pmsg->buf;
    uint32_t len = pmsg->len;

    RT_ASSERT(len);
    RT_ASSERT(buf);

    if (len > I2C_MAX_BUF_LEN - 10)
        len = I2C_MAX_BUF_LEN - 10;

    rt_memcpy(psNuI2cDev->buffer + psNuI2cDev->subaddr_len + 1, buf, len);

    psNuI2cDev->state = I2C_STATE_WRITE;
    psNuI2cDev->pos = 1;
    psNuI2cDev->len = psNuI2cDev->subaddr_len + 1 + len;
    psNuI2cDev->last_error = 0;

    /* Get slave address */
    nu_i2c_calculate_address(psNuI2cDev, I2C_STATE_WRITE);

    /* Enable I2C-EN */
    I2C_ENABLE(psNuI2cDev);

    /* Send first byte to transfer the message. */
    I2C_REG_WRITE(psNuI2cDev, I2C_TxR, psNuI2cDev->buffer[0] & 0xff);

    if (!I2C_ISBUSFREE(psNuI2cDev))
        return (I2C_ERR_BUSY);

    rt_completion_init(&psNuI2cDev->signal);

    nu_i2c_command(psNuI2cDev, I2C_CMD_START | I2C_CMD_WRITE);

    if ((RT_EOK == rt_completion_wait(&psNuI2cDev->signal, I2C_SIGNAL_TIMEOUT)))
    {
        psNuI2cDev->subaddr += len;
    }
    else
    {
        rt_kprintf("[%s]Wait signal timeout.\n", __func__);

        len = 0;
    }

    /* Disable I2C-EN */
    I2C_DISABLE(psNuI2cDev);

    if (psNuI2cDev->last_error)
        return (psNuI2cDev->last_error);

    return len;
}

/**
  * @brief Support some I2C driver commands for application.
  * @param[in] psNuI2cDev is interface structure pointer.
  * @param[in] cmd is command.
  * @param[in] arg0 is the first argument of command.
  * @param[in] arg1 is the second argument of command.
  * @return command status.
  * @retval 0 Success.
  * @retval I2C_ERR_IO Interface not opened.
  * @retval I2C_ERR_NODEV No such device.
  * @retval I2C_ERR_NOTTY Command not support, or parameter error.
  */
static int32_t nu_i2c_ioctl(nu_i2c_dev_t psNuI2cDev, uint32_t cmd, uint32_t arg0, uint32_t arg1)
{
    switch (cmd)
    {
    case I2C_IOC_SET_DEV_ADDRESS:
        psNuI2cDev->addr = arg0;
        break;

    case I2C_IOC_SET_SPEED:
        return nu_i2c_set_speed(psNuI2cDev, (int32_t)arg0);

    case I2C_IOC_SET_SUB_ADDRESS:
        if (arg1 > 4)
        {
            return (I2C_ERR_NOTTY);
        }

        psNuI2cDev->subaddr = arg0;
        psNuI2cDev->subaddr_len = arg1;
        break;

    default:
        return (I2C_ERR_NOTTY);
    }

    return (0);
}

static rt_ssize_t nu_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                 struct rt_i2c_msg msgs[],
                                 rt_uint32_t num)
{
    nu_i2c_bus_t psNuI2cBus;
    nu_i2c_dev_t psNuI2cDev;
    rt_size_t i;
    rt_err_t ret;
    struct rt_i2c_msg *pmsg;

    RT_ASSERT(bus);

    psNuI2cBus = (nu_i2c_bus_t) bus;
    psNuI2cDev = &psNuI2cBus->dev;

    for (i = 0; i < num; i++)
    {
        if (!I2C_ISBUSFREE(psNuI2cDev))
            break;

        pmsg = psNuI2cBus->cur_i2c_msg = &msgs[i];

        /* Not support 10bit. */
        if ((pmsg->flags & RT_I2C_ADDR_10BIT)
                || (pmsg->len == 0))
            break;

        /* Set device address */
        nu_i2c_reset(psNuI2cDev);

        nu_i2c_ioctl(psNuI2cDev, I2C_IOC_SET_DEV_ADDRESS, pmsg->addr, 0);

        if (pmsg->flags & RT_I2C_RD)
        {
            ret = nu_i2c_read(psNuI2cDev, pmsg);
        }
        else
        {
            ret = nu_i2c_write(psNuI2cDev, pmsg);
        }

        if (ret != pmsg->len) break;
    }

    return i;
}

static rt_err_t nu_i2c_bus_control(struct rt_i2c_bus_device *bus, rt_uint32_t u32Cmd, rt_uint32_t u32Value)
{
    nu_i2c_bus_t psNuI2cBus;
    nu_i2c_dev_t psNuI2cDev;

    RT_ASSERT(bus);

    psNuI2cBus = (nu_i2c_bus_t) bus;
    psNuI2cDev = &psNuI2cBus->dev;

    switch (u32Cmd)
    {
    case RT_I2C_DEV_CTRL_CLK:
        nu_i2c_set_speed(psNuI2cDev, (int32_t)u32Value);
        break;
    default:
        return -RT_EIO;
    }

    return RT_EOK;
}

static const struct rt_i2c_bus_device_ops nu_i2c_ops =
{
    .master_xfer        = nu_i2c_mst_xfer,
    .slave_xfer         = NULL,
    .i2c_bus_control    = nu_i2c_bus_control,
};


/* Public functions -------------------------------------------------------------*/
int rt_hw_i2c_init(void)
{
    int i;
    rt_err_t ret;

    for (i = (I2C_START + 1); i < I2C_CNT; i++)
    {
        nu_i2c_dev_t psNuI2cDev = &nu_i2c_arr[i].dev;

        nu_i2c_arr[i].parent.ops = &nu_i2c_ops;

        psNuI2cDev->buffer = rt_malloc(I2C_MAX_BUF_LEN);
        RT_ASSERT(psNuI2cDev->buffer);

        /* Enable I2C engine clock and reset. */
        nu_sys_ipclk_enable(nu_i2c_arr[i].clkidx);
        nu_sys_ip_reset(nu_i2c_arr[i].rstidx);

        nu_i2c_ioctl(psNuI2cDev, I2C_IOC_SET_SPEED, 100, 0);

        /* Register ISR and Respond IRQ. */
        rt_hw_interrupt_install(nu_i2c_arr[i].irqn, nu_i2c_isr, &nu_i2c_arr[i], nu_i2c_arr[i].name);
        rt_hw_interrupt_umask(nu_i2c_arr[i].irqn);

        ret = rt_i2c_bus_device_register(&nu_i2c_arr[i].parent, nu_i2c_arr[i].name);
        RT_ASSERT(RT_EOK == ret);
    }

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* BSP_USING_I2C */

