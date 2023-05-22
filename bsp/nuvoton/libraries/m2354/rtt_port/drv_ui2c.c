/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-6-31       Hphuang          First version
*
******************************************************************************/

#include <rtconfig.h>

#if (defined(BSP_USING_UI2C) && defined(RT_USING_I2C))

#include <rtdevice.h>
#include "NuMicro.h"

/* Private define ---------------------------------------------------------------*/
#define LOG_TAG          "drv.ui2c"
#define DBG_ENABLE
#define DBG_SECTION_NAME LOG_TAG
#define DBG_LEVEL        DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

#define SLV_10BIT_ADDR (0x1E<<2)             //1111+0xx+r/w

/* Private typedef --------------------------------------------------------------*/
typedef struct nu_ui2c_bus
{
    struct rt_i2c_bus_device ui2c_dev;
    struct rt_i2c_msg *msg;
    UI2C_T *ui2c_base;
    char *dev_name;
} nu_ui2c_bus_t;

/* Private functions ------------------------------------------------------------*/
static rt_ssize_t nu_ui2c_mst_xfer(struct rt_i2c_bus_device *ui2c_dev,
                                  struct rt_i2c_msg msgs[],
                                  rt_uint32_t num);

static const struct rt_i2c_bus_device_ops nu_ui2c_ops =
{
    .master_xfer        = nu_ui2c_mst_xfer,
    .slave_xfer         = NULL,
    .i2c_bus_control    = NULL,
};

/* Private variables ------------------------------------------------------------*/
#ifdef BSP_USING_UI2C0
#define UI2C0BUS_NAME  "ui2c0"
static nu_ui2c_bus_t nu_ui2c0 =
{
    .ui2c_base = UI2C0,
    .dev_name = UI2C0BUS_NAME,
};
#endif /* BSP_USING_UI2C0 */

#ifdef BSP_USING_UI2C1
#define UI2C1BUS_NAME  "ui2c1"
static nu_ui2c_bus_t nu_ui2c1 =
{
    .ui2c_base = UI2C1,
    .dev_name = UI2C1BUS_NAME,
};
#endif /* BSP_USING_UI2C1 */

/* Functions define ------------------------------------------------------------*/
#if (defined(BSP_USING_UI2C0) || defined(BSP_USING_UI2C1))

static inline rt_err_t nu_ui2c_wait_ready_with_timeout(nu_ui2c_bus_t *nu_ui2c)
{
    rt_tick_t start = rt_tick_get();
    while (!(UI2C_GET_PROT_STATUS(nu_ui2c->ui2c_base) & (UI2C_PROTSTS_STARIF_Msk | UI2C_PROTSTS_ACKIF_Msk | UI2C_PROTSTS_NACKIF_Msk | UI2C_PROTSTS_STORIF_Msk)))
    {
        if ((rt_tick_get() - start) > nu_ui2c->ui2c_dev.timeout)
        {
            LOG_E("\nui2c: timeout!\n");
            return -RT_ETIMEOUT;
        }
    }

    return RT_EOK;
}

static inline rt_err_t nu_ui2c_send_data(nu_ui2c_bus_t *nu_ui2c, rt_uint8_t data)
{
    UI2C_SET_DATA(nu_ui2c->ui2c_base, data);
    UI2C_SET_CONTROL_REG(nu_ui2c->ui2c_base, UI2C_CTL_PTRG);
    return nu_ui2c_wait_ready_with_timeout(nu_ui2c);
}

static rt_err_t nu_ui2c_send_address(nu_ui2c_bus_t *nu_ui2c,
                                     struct rt_i2c_msg  *msg)
{
    rt_uint16_t flags = msg->flags;
    rt_uint16_t ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;
    rt_uint8_t addr1, addr2;
    rt_err_t ret;

    if (flags & RT_I2C_ADDR_10BIT)
    {
        UI2C_ENABLE_10BIT_ADDR_MODE(nu_ui2c->ui2c_base);
        /* Init Send 10-bit Addr */
        addr1 = ((msg->addr >> 8) | SLV_10BIT_ADDR) << 1;
        addr2 = msg->addr & 0xff;

        LOG_D("addr1: %d, addr2: %d\n", addr1, addr2);

        ret = nu_ui2c_send_data(nu_ui2c, addr1);
        if (ret != RT_EOK) //for timeout condition
            return -RT_EIO;

        if (((UI2C_GET_PROT_STATUS(nu_ui2c->ui2c_base) & UI2C_PROTSTS_ACKIF_Msk) != UI2C_PROTSTS_ACKIF_Msk) && !ignore_nack)
        {
            LOG_E("NACK: sending first addr\n");

            return -RT_EIO;
        }
        UI2C_CLR_PROT_INT_FLAG(nu_ui2c->ui2c_base, UI2C_PROTSTS_ACKIF_Msk);

        ret = nu_ui2c_send_data(nu_ui2c,  addr2);
        if (ret != RT_EOK) //for timeout condition
            return -RT_EIO;

        if (((UI2C_GET_PROT_STATUS(nu_ui2c->ui2c_base) & UI2C_PROTSTS_ACKIF_Msk) != UI2C_PROTSTS_ACKIF_Msk) && !ignore_nack)
        {
            LOG_E("NACK: sending second addr\n");

            return -RT_EIO;
        }
        UI2C_CLR_PROT_INT_FLAG(nu_ui2c->ui2c_base, UI2C_PROTSTS_ACKIF_Msk);

        if (flags & RT_I2C_RD)
        {
            LOG_D("send repeated start condition\n");

            UI2C_SET_CONTROL_REG(nu_ui2c->ui2c_base, (UI2C_CTL_PTRG | UI2C_CTL_STA));
            ret = nu_ui2c_wait_ready_with_timeout(nu_ui2c);
            if (ret != RT_EOK) //for timeout condition
                return -RT_EIO;

            if (((UI2C_GET_PROT_STATUS(nu_ui2c->ui2c_base) & UI2C_PROTSTS_STARIF_Msk) != UI2C_PROTSTS_STARIF_Msk) && !ignore_nack)
            {
                LOG_E("sending repeated START fail\n");

                return -RT_EIO;
            }
            UI2C_CLR_PROT_INT_FLAG(nu_ui2c->ui2c_base, UI2C_PROTSTS_STARIF_Msk);

            addr1 |= RT_I2C_RD;

            ret = nu_ui2c_send_data(nu_ui2c,  addr1);
            if (ret != RT_EOK) //for timeout condition
                return -RT_EIO;

            if (((UI2C_GET_PROT_STATUS(nu_ui2c->ui2c_base) & UI2C_PROTSTS_ACKIF_Msk) != UI2C_PROTSTS_ACKIF_Msk) && !ignore_nack)
            {
                LOG_E("NACK: sending repeated addr\n");
                return -RT_EIO;
            }
            UI2C_CLR_PROT_INT_FLAG(nu_ui2c->ui2c_base, UI2C_PROTSTS_ACKIF_Msk);
        }
    }
    else
    {
        /* 7-bit addr */
        addr1 = msg->addr << 1;
        if (flags & RT_I2C_RD)
            addr1 |= RT_I2C_RD;

        /* Send device address */
        ret = nu_ui2c_send_data(nu_ui2c,  addr1); /* Send Address */
        if (ret != RT_EOK) //for timeout condition
            return -RT_EIO;

        if (((UI2C_GET_PROT_STATUS(nu_ui2c->ui2c_base) & UI2C_PROTSTS_ACKIF_Msk) != UI2C_PROTSTS_ACKIF_Msk)
                && !ignore_nack)
        {
            LOG_E("sending addr fail\n");
            return -RT_EIO;
        }
        UI2C_CLR_PROT_INT_FLAG(nu_ui2c->ui2c_base, UI2C_PROTSTS_ACKIF_Msk);
    }

    return RT_EOK;
}

static rt_ssize_t nu_ui2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                  struct rt_i2c_msg msgs[],
                                  rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    nu_ui2c_bus_t *nu_ui2c;
    rt_size_t i;
    rt_uint32_t cnt_data;
    rt_uint16_t ignore_nack;
    rt_err_t ret;

    RT_ASSERT(bus != RT_NULL);
    nu_ui2c = (nu_ui2c_bus_t *) bus;

    nu_ui2c->msg = msgs;

    (nu_ui2c->ui2c_base)->PROTSTS = (nu_ui2c->ui2c_base)->PROTSTS;//Clear status

    UI2C_SET_CONTROL_REG(nu_ui2c->ui2c_base, UI2C_CTL_STA);
    ret = nu_ui2c_wait_ready_with_timeout(nu_ui2c);

    if (ret != RT_EOK) //for timeout condition
    {
        rt_set_errno(-RT_ETIMEOUT);
        return 0;
    }

    if (((UI2C_GET_PROT_STATUS(nu_ui2c->ui2c_base) & UI2C_PROTSTS_STARIF_Msk) != UI2C_PROTSTS_STARIF_Msk)) /* Check Send START */
    {
        i = 0;
        LOG_E("Send START Fail");
        return i;
    }
    UI2C_CLR_PROT_INT_FLAG(nu_ui2c->ui2c_base, UI2C_PROTSTS_STARIF_Msk);

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;

        if (!(msg->flags & RT_I2C_NO_START))
        {
            if (i)
            {
                UI2C_SET_CONTROL_REG(nu_ui2c->ui2c_base, (UI2C_CTL_PTRG | UI2C_CTL_STA));/* Send repeat START */
                ret = nu_ui2c_wait_ready_with_timeout(nu_ui2c);
                if (ret != RT_EOK) //for timeout condition
                    break;

                if (((UI2C_GET_PROT_STATUS(nu_ui2c->ui2c_base) & UI2C_PROTSTS_STARIF_Msk) != UI2C_PROTSTS_STARIF_Msk)) /* Check Send repeat START */
                {
                    i = 0;
                    LOG_E("Send repeat START Fail");
                    break;
                }
                UI2C_CLR_PROT_INT_FLAG(nu_ui2c->ui2c_base, UI2C_PROTSTS_STARIF_Msk);
            }

            if ((RT_EOK != nu_ui2c_send_address(nu_ui2c, msg))
                    && !ignore_nack)
            {
                i = 0;
                LOG_E("Send Address Fail");
                break;
            }
        }

        if (nu_ui2c->msg[i].flags & RT_I2C_RD) /* Receive Bytes */
        {
            rt_uint32_t do_rd_nack = (i == (num - 1));
            for (cnt_data = 0 ; cnt_data < (nu_ui2c->msg[i].len) ; cnt_data++)
            {
                do_rd_nack += (cnt_data == (nu_ui2c->msg[i].len - 1)); /* NACK after last byte  for hardware setting */
                if (do_rd_nack == 2)
                {
                    UI2C_SET_CONTROL_REG(nu_ui2c->ui2c_base, UI2C_CTL_PTRG);
                }
                else
                {
                    UI2C_SET_CONTROL_REG(nu_ui2c->ui2c_base, (UI2C_CTL_PTRG | UI2C_CTL_AA));
                }

                ret = nu_ui2c_wait_ready_with_timeout(nu_ui2c);
                if (ret != RT_EOK) //for timeout condition
                    break;

                if (nu_ui2c->ui2c_base->PROTCTL & UI2C_CTL_AA)
                {
                    if (((UI2C_GET_PROT_STATUS(nu_ui2c->ui2c_base) & UI2C_PROTSTS_ACKIF_Msk) != UI2C_PROTSTS_ACKIF_Msk)) /*Master Receive Data ACK*/
                    {
                        i = 0;
                        break;
                    }
                    UI2C_CLR_PROT_INT_FLAG(nu_ui2c->ui2c_base, UI2C_PROTSTS_ACKIF_Msk);
                }
                else
                {
                    if (((UI2C_GET_PROT_STATUS(nu_ui2c->ui2c_base) & UI2C_PROTSTS_NACKIF_Msk) != UI2C_PROTSTS_NACKIF_Msk)) /*Master Receive Data NACK*/
                    {
                        i = 0;
                        break;
                    }
                    UI2C_CLR_PROT_INT_FLAG(nu_ui2c->ui2c_base, UI2C_PROTSTS_NACKIF_Msk);
                }

                nu_ui2c->msg[i].buf[cnt_data] = nu_ui2c->ui2c_base->RXDAT;
            }
        }
        else /* Send Bytes */
        {
            for (cnt_data = 0 ; cnt_data < (nu_ui2c->msg[i].len) ; cnt_data++)
            {
                /* Send register number and MSB of data */
                ret = nu_ui2c_send_data(nu_ui2c, (uint8_t)(nu_ui2c->msg[i].buf[cnt_data]));
                if (ret != RT_EOK) //for timeout condition
                    break;

                if (((UI2C_GET_PROT_STATUS(nu_ui2c->ui2c_base) & UI2C_PROTSTS_ACKIF_Msk) != UI2C_PROTSTS_ACKIF_Msk)
                        && !ignore_nack
                   ) /* Send data and get Ack */
                {
                    i = 0;
                    break;
                }
                UI2C_CLR_PROT_INT_FLAG(nu_ui2c->ui2c_base, UI2C_PROTSTS_ACKIF_Msk);
            }
        }
    }

    UI2C_SET_CONTROL_REG(nu_ui2c->ui2c_base, (UI2C_CTL_PTRG | UI2C_CTL_STO));            /* Send STOP signal */
    ret = nu_ui2c_wait_ready_with_timeout(nu_ui2c);
    if (ret != RT_EOK) //for timeout condition
    {
        rt_set_errno(-RT_ETIMEOUT);
        return 0;
    }

    RT_ASSERT(((UI2C_GET_PROT_STATUS(nu_ui2c->ui2c_base) & UI2C_PROTSTS_STORIF_Msk) == UI2C_PROTSTS_STORIF_Msk));
    if (((UI2C_GET_PROT_STATUS(nu_ui2c->ui2c_base) & UI2C_PROTSTS_STORIF_Msk) != UI2C_PROTSTS_STORIF_Msk)) /* Bus Free*/
    {
        i = 0;
        LOG_E("Send STOP Fail");
    }

    UI2C_CLR_PROT_INT_FLAG(nu_ui2c->ui2c_base, UI2C_PROTSTS_STORIF_Msk);
    UI2C_SET_CONTROL_REG(nu_ui2c->ui2c_base, UI2C_CTL_PTRG);
    UI2C_DISABLE_10BIT_ADDR_MODE(nu_ui2c->ui2c_base); /*clear all sub modes like 10 bit mode*/
    nu_ui2c->msg = RT_NULL;

    return i;
}

#endif //(defined(BSP_USING_UI2C0) || defined(BSP_USING_UI2C1))

/* Public functions -------------------------------------------------------------*/
int rt_hw_ui2c_init(void)
{
    rt_err_t ret = -RT_ERROR;

#if defined(BSP_USING_UI2C0)
    SYS_UnlockReg();
    SYS_ResetModule(USCI0_RST);
    SYS_LockReg();

    nu_ui2c0.ui2c_dev.ops = &nu_ui2c_ops;
    UI2C_Open(nu_ui2c0.ui2c_base, 100000);
    ret = rt_i2c_bus_device_register(&nu_ui2c0.ui2c_dev, nu_ui2c0.dev_name);
    RT_ASSERT(RT_EOK == ret);
#endif  /* BSP_USING_UI2C0 */

#if defined(BSP_USING_UI2C1)
    SYS_UnlockReg();
    SYS_ResetModule(USCI1_RST);
    SYS_LockReg();

    nu_ui2c1.ui2c_dev.ops = &nu_ui2c_ops;
    UI2C_Open(nu_ui2c1.ui2c_base, 100000);
    ret = rt_i2c_bus_device_register(&nu_ui2c1.ui2c_dev, nu_ui2c1.dev_name);
    RT_ASSERT(RT_EOK == ret);
#endif  /* BSP_USING_UI2C1 */

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_ui2c_init);

#endif //#if defined(BSP_USING_UI2C)
