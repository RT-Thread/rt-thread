/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author         Notes
* 2020-11-11      Wayne          First version
******************************************************************************/


#include <rtconfig.h>

#if defined( BSP_USING_I2C)

#include <rtdevice.h>
#include "NuMicro.h"
#include <drv_i2c.h>
#include <drv_sys.h>

/* Private define ---------------------------------------------------------------*/
#define LOG_TAG    "drv.i2c"
#define DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

enum
{
    I2C_START = -1,
#if defined(BSP_USING_I2C0)
    I2C0_IDX,
#endif
#if defined(BSP_USING_I2C1)
    I2C1_IDX,
#endif
#if defined(BSP_USING_I2C2)
    I2C2_IDX,
#endif
#if defined(BSP_USING_I2C3)
    I2C3_IDX,
#endif
#if defined(BSP_USING_I2C4)
    I2C4_IDX,
#endif
#if defined(BSP_USING_I2C5)
    I2C5_IDX,
#endif
    I2C_CNT
};

/* Private typedef --------------------------------------------------------------*/
typedef struct _nu_i2c_bus
{
    struct rt_i2c_bus_device parent;
    I2C_T *I2C;
    struct rt_i2c_msg *msg;
    char *device_name;
} nu_i2c_bus_t;

/* Private variables ------------------------------------------------------------*/


static nu_i2c_bus_t nu_i2c_arr [ ] =
{
#if defined(BSP_USING_I2C0)
    {
        .I2C = I2C0, .device_name = "i2c0",
    },
#endif
#if defined(BSP_USING_I2C1)
    {
        .I2C = I2C1, .device_name = "i2c1",
    },
#endif
#if defined(BSP_USING_I2C2)
    {
        .I2C = I2C2, .device_name = "i2c2",
    },
#endif
#if defined(BSP_USING_I2C3)
    {
        .I2C = I2C3, .device_name = "i2c3",
    },
#endif
#if defined(BSP_USING_I2C4)
    {
        .I2C = I2C4, .device_name = "i2c4",
    },
#endif
#if defined(BSP_USING_I2C5)
    {
        .I2C = I2C5, .device_name = "i2c5",
    },
#endif
};

/* Private functions ------------------------------------------------------------*/
#if defined(BSP_USING_I2C)
static rt_ssize_t nu_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                 struct rt_i2c_msg msgs[],
                                 rt_uint32_t num);
static rt_err_t nu_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                   rt_uint32_t u32Cmd,
                                   rt_uint32_t u32Value);

static const struct rt_i2c_bus_device_ops nu_i2c_ops =
{
    .master_xfer        = nu_i2c_mst_xfer,
    .slave_xfer         = NULL,
    .i2c_bus_control    = nu_i2c_bus_control
};

static rt_err_t nu_i2c_bus_control(struct rt_i2c_bus_device *bus, rt_uint32_t u32Cmd, rt_uint32_t u32Value)
{
    nu_i2c_bus_t *nu_i2c;

    RT_ASSERT(bus != RT_NULL);
    nu_i2c = (nu_i2c_bus_t *) bus;

    switch (u32Cmd)
    {
    case RT_I2C_DEV_CTRL_CLK:
        I2C_SetBusClockFreq(nu_i2c->I2C, u32Value);
        break;
    default:
        return -RT_EIO;
    }

    return RT_EOK;
}

static inline rt_err_t nu_i2c_wait_ready_with_timeout(nu_i2c_bus_t *bus)
{
    rt_tick_t start = rt_tick_get();
    while (!(bus->I2C->CTL0 & I2C_CTL0_SI_Msk))
    {
        if ((rt_tick_get() - start) > bus->parent.timeout)
        {
            LOG_E("\ni2c: timeout!\n");
            return -RT_ETIMEOUT;
        }
    }

    return RT_EOK;
}

static inline rt_err_t nu_i2c_send_data(nu_i2c_bus_t *nu_i2c, rt_uint8_t data)
{
    I2C_SET_DATA(nu_i2c->I2C, data);
    I2C_SET_CONTROL_REG(nu_i2c->I2C, I2C_CTL_SI);
    return nu_i2c_wait_ready_with_timeout(nu_i2c);
}

static rt_err_t nu_i2c_send_address(nu_i2c_bus_t *nu_i2c,
                                    struct rt_i2c_msg  *msg)
{
    rt_uint16_t flags = msg->flags;
    rt_uint16_t ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;
    rt_uint8_t addr1, addr2;
    rt_err_t ret;


    if (flags & RT_I2C_ADDR_10BIT)
    {
        nu_i2c->I2C->CTL1 |= I2C_CTL1_ADDR10EN_Msk;
        addr1 = 0xf0 | ((msg->addr >> 7) & 0x06);
        addr2 = msg->addr & 0xff;

        LOG_D("address1: %d, address2: %d\n", addr1, addr2);

        ret = nu_i2c_send_data(nu_i2c, addr1);
        if (ret != RT_EOK) /* for timeout condition */
            return -RT_EIO;

        if ((I2C_GET_STATUS(nu_i2c->I2C) != NU_I2C_MASTER_STATUS_TRANSMIT_ADDRESS_ACK) && !ignore_nack)
        {
            LOG_E("NACK: sending first address failed\n");

            return -RT_EIO;
        }

        ret = nu_i2c_send_data(nu_i2c,  addr2);
        if (ret != RT_EOK) /* for timeout condition */
            return -RT_EIO;

        if ((I2C_GET_STATUS(nu_i2c->I2C) != NU_I2C_MASTER_STATUS_TRANSMIT_ADDRESS_ACK) && !ignore_nack)
        {
            LOG_E("NACK: sending second address failed\n");

            return -RT_EIO;
        }

        if (flags & RT_I2C_RD)
        {
            LOG_D("send repeated START signal\n");

            I2C_SET_CONTROL_REG(nu_i2c->I2C, I2C_CTL_STA_SI);
            ret = nu_i2c_wait_ready_with_timeout(nu_i2c);
            if (ret != RT_EOK) /* for timeout condition */
                return -RT_EIO;

            if ((I2C_GET_STATUS(nu_i2c->I2C) != NU_I2C_MASTER_STATUS_REPEAT_START) && !ignore_nack)
            {
                //LOG_E("sending repeated START failed\n");

                return -RT_EIO;
            }

            addr1 |= 0x01;

            ret = nu_i2c_send_data(nu_i2c,  addr1);
            if (ret != RT_EOK) /* for timeout condition */
                return -RT_EIO;

            if ((I2C_GET_STATUS(nu_i2c->I2C) != NU_I2C_MASTER_STATUS_RECEIVE_ADDRESS_ACK) && !ignore_nack)
            {
                LOG_E("NACK: sending read address failed\n");

                return -RT_EIO;
            }
        }
    }
    else
    {
        /* 7-bit addr */
        addr1 = msg->addr << 1;
        if (flags & RT_I2C_RD)
            addr1 |= 1;

        /* Send device address */
        ret = nu_i2c_send_data(nu_i2c,  addr1); /* Send Address */
        if (ret != RT_EOK) /* for timeout condition */
            return -RT_EIO;

        if ((I2C_GET_STATUS(nu_i2c->I2C)
                != ((flags & RT_I2C_RD) ? NU_I2C_MASTER_STATUS_RECEIVE_ADDRESS_ACK : NU_I2C_MASTER_STATUS_TRANSMIT_ADDRESS_ACK))
                && !ignore_nack)
        {
            LOG_E("sending address failed\n");
            return -RT_EIO;
        }
    }

    return RT_EOK;
}

static rt_ssize_t nu_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                 struct rt_i2c_msg msgs[],
                                 rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    nu_i2c_bus_t *nu_i2c;
    rt_size_t i;
    rt_uint32_t cnt_data;
    rt_uint16_t ignore_nack;
    rt_err_t ret;

    RT_ASSERT(bus != RT_NULL);
    nu_i2c = (nu_i2c_bus_t *) bus;

    nu_i2c->msg = msgs;

    nu_i2c->I2C->CTL0 |= I2C_CTL0_STA_Msk | I2C_CTL0_SI_Msk;
    ret = nu_i2c_wait_ready_with_timeout(nu_i2c);
    if (ret != RT_EOK) /* for timeout condition */
    {
        rt_set_errno(-RT_ETIMEOUT);
        return 0;
    }
    if (I2C_GET_STATUS(nu_i2c->I2C) != NU_I2C_MASTER_STATUS_START)
    {
        i = 0;
        LOG_E("Send START Failed");
        return i;
    }

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;

        if (!(msg->flags & RT_I2C_NO_START))
        {
            if (i)
            {
                I2C_SET_CONTROL_REG(nu_i2c->I2C, I2C_CTL_STA_SI);
                ret = nu_i2c_wait_ready_with_timeout(nu_i2c);
                if (ret != RT_EOK) /* for timeout condition */
                    break;

                if (I2C_GET_STATUS(nu_i2c->I2C) != NU_I2C_MASTER_STATUS_REPEAT_START)
                {
                    i = 0;
                    //LOG_E("Send repeat START Fail");
                    break;
                }
            }

            if ((RT_EOK != nu_i2c_send_address(nu_i2c, msg))
                    && !ignore_nack)
            {
                i = 0;
                LOG_E("Send Address Fail");
                break;
            }
        }


        if (nu_i2c->msg[i].flags & RT_I2C_RD) /* Receive Bytes */
        {
            rt_uint32_t do_rd_nack = (i == (num - 1));
            for (cnt_data = 0 ; cnt_data < (nu_i2c->msg[i].len) ; cnt_data++)
            {
                do_rd_nack += (cnt_data == (nu_i2c->msg[i].len - 1)); /* NACK after last byte  for hardware setting */
                if (do_rd_nack == 2)
                {
                    I2C_SET_CONTROL_REG(nu_i2c->I2C, I2C_CTL_SI);
                }
                else
                {
                    I2C_SET_CONTROL_REG(nu_i2c->I2C, I2C_CTL_SI_AA);
                }

                ret = nu_i2c_wait_ready_with_timeout(nu_i2c);
                if (ret != RT_EOK) /* for timeout condition */
                    break;

                if (nu_i2c->I2C->CTL0 & I2C_CTL_AA)
                {
                    if (I2C_GET_STATUS(nu_i2c->I2C) != NU_I2C_MASTER_STATUS_RECEIVE_DATA_ACK)
                    {
                        i = 0;
                        break;
                    }
                }
                else
                {
                    if (I2C_GET_STATUS(nu_i2c->I2C) != NU_I2C_MASTER_STATUS_RECEIVE_DATA_NACK)
                    {
                        i = 0;
                        break;
                    }
                }

                nu_i2c->msg[i].buf[cnt_data] = nu_i2c->I2C->DAT;
            }
        }
        else /* Send Bytes */
        {
            for (cnt_data = 0 ; cnt_data < (nu_i2c->msg[i].len) ; cnt_data++)
            {
                /* Send register number and MSB of data */
                ret = nu_i2c_send_data(nu_i2c, (uint8_t)(nu_i2c->msg[i].buf[cnt_data]));
                if (ret != RT_EOK) /* for timeout condition */
                    break;

                if (I2C_GET_STATUS(nu_i2c->I2C) != NU_I2C_MASTER_STATUS_TRANSMIT_DATA_ACK
                        && !ignore_nack
                   ) /* Send aata and get Ack */
                {
                    i = 0;
                    break;
                }
            }
        }
    }

    I2C_STOP(nu_i2c->I2C);

    RT_ASSERT(I2C_GET_STATUS(nu_i2c->I2C) == NU_I2C_MASTER_STATUS_BUS_RELEASED);
    if (I2C_GET_STATUS(nu_i2c->I2C) != NU_I2C_MASTER_STATUS_BUS_RELEASED)
    {
        i = 0;
    }

    nu_i2c->msg = RT_NULL;
    nu_i2c->I2C->CTL1 = 0; /*clear all sub modes like 10 bit mode*/
    return i;
}
#endif

/* Public functions -------------------------------------------------------------*/
int rt_hw_i2c_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (I2C_START + 1); i < I2C_CNT; i++)
    {
        /* Reset and initial IP engine. */
        I2C_Close(nu_i2c_arr[i].I2C);
        I2C_Open(nu_i2c_arr[i].I2C, 100000);

        nu_i2c_arr[i].parent.ops = &nu_i2c_ops;

        ret = rt_i2c_bus_device_register(&nu_i2c_arr[i].parent, nu_i2c_arr[i].device_name);
        RT_ASSERT(RT_EOK == ret);
    }

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* BSP_USING_I2C */

