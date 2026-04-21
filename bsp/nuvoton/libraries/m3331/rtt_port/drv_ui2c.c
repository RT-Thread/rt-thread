/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if defined(BSP_USING_UI2C) && defined(RT_USING_I2C)

#include "NuMicro.h"
#include "rtdevice.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.ui2c"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

#define SLV_10BIT_ADDR (0x1E << 2)
#define DEFINE_NU_UI2C(_idx, _rst)    \
    {                                 \
        .base = UI2C##_idx,           \
        .name = "ui2c" #_idx,        \
        .rst = _rst,                  \
    }

/* Types / Structures ---------------------------------------------------------*/
enum
{
    UI2C_START = -1,
#if defined(BSP_USING_UI2C0)
    UI2C0_IDX,
#endif
#if defined(BSP_USING_UI2C1)
    UI2C1_IDX,
#endif
    UI2C_CNT
};

struct nu_ui2c
{
    struct rt_i2c_bus_device parent;
    char *name;
    UI2C_T *base;
    uint32_t rst;
    struct rt_i2c_msg *msg;
};
typedef struct nu_ui2c *nu_ui2c_t;

/* Static Function Prototypes ------------------------------------------------*/
static rt_size_t nu_ui2c_mst_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num);
static rt_err_t nu_ui2c_control(struct rt_i2c_bus_device *bus, rt_uint32_t u32Cmd, rt_uint32_t u32Value);

/* Static Variables ----------------------------------------------------------*/
static struct nu_ui2c nu_ui2c_arr [ ] =
{
#if defined(BSP_USING_UI2C0)
    DEFINE_NU_UI2C(0, USCI0_RST),
#endif
#if defined(BSP_USING_UI2C1)
    DEFINE_NU_UI2C(1, USCI1_RST),
#endif
};

static const struct rt_i2c_bus_device_ops nu_ui2c_ops =
{
    .master_xfer        = nu_ui2c_mst_xfer,
    .slave_xfer         = NULL,
    .i2c_bus_control    = nu_ui2c_control,
};

/* Functions Implementation --------------------------------------------------*/
static rt_err_t nu_ui2c_control(struct rt_i2c_bus_device *bus, rt_uint32_t u32Cmd, rt_uint32_t u32Value)
{
    nu_ui2c_t psNuUi2c = (nu_ui2c_t) bus;
    RT_ASSERT(bus);

    switch (u32Cmd)
    {
    case RT_I2C_DEV_CTRL_CLK:
        UI2C_SetBusClockFreq(psNuUi2c->base, u32Value);
        break;
    default:
        return -RT_EIO;
    }

    return RT_EOK;
}

static rt_err_t nu_ui2c_wait_ready_with_timeout(nu_ui2c_t psNuUi2c)
{
    rt_tick_t start = rt_tick_get();
    uint32_t u32ProtSts;
    while ((u32ProtSts = UI2C_GET_PROT_STATUS(psNuUi2c->base) &
                         (UI2C_PROTSTS_STARIF_Msk |
                          UI2C_PROTSTS_ACKIF_Msk |
                          UI2C_PROTSTS_NACKIF_Msk |
                          UI2C_PROTSTS_STORIF_Msk)) == 0)
                          {
        if ((rt_tick_get() - start) > psNuUi2c->parent.timeout)
        {
            LOG_E("timeout! (%d - %d > %d) ProtSts=0x%08x",  rt_tick_get(), start, psNuUi2c->parent.timeout, u32ProtSts);
            return -RT_ETIMEOUT;
        }
    }

    return RT_EOK;
}

static rt_err_t nu_ui2c_send_data(nu_ui2c_t psNuUi2c, rt_uint8_t data)
{
    UI2C_SET_DATA(psNuUi2c->base, data);
    UI2C_SET_CONTROL_REG(psNuUi2c->base, UI2C_CTL_PTRG);

    return nu_ui2c_wait_ready_with_timeout(psNuUi2c);
}

static rt_err_t nu_ui2c_send_address(nu_ui2c_t psNuUi2c,
                                     struct rt_i2c_msg  *msg)
                                     {
    rt_uint16_t flags = msg->flags;
    rt_uint16_t ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;
    rt_uint8_t addr1, addr2;
    rt_err_t ret;

    if (flags & RT_I2C_ADDR_10BIT)
    {
        UI2C_ENABLE_10BIT_ADDR_MODE(psNuUi2c->base);
        /* Init Send 10-bit Addr */
        addr1 = ((msg->addr >> 8) | SLV_10BIT_ADDR) << 1;
        addr2 = msg->addr & 0xff;

        LOG_D("addr1: %d, addr2: %d\n", addr1, addr2);

        ret = nu_ui2c_send_data(psNuUi2c, addr1);
        if (ret != RT_EOK) //for timeout condition
            return -RT_EIO;

        if (((UI2C_GET_PROT_STATUS(psNuUi2c->base) & UI2C_PROTSTS_ACKIF_Msk) != UI2C_PROTSTS_ACKIF_Msk) && !ignore_nack)
        {
            LOG_E("NACK: sending first addr\n");

            return -RT_EIO;
        }
        UI2C_CLR_PROT_INT_FLAG(psNuUi2c->base, UI2C_PROTSTS_ACKIF_Msk);

        ret = nu_ui2c_send_data(psNuUi2c,  addr2);
        if (ret != RT_EOK) //for timeout condition
            return -RT_EIO;

        if (((UI2C_GET_PROT_STATUS(psNuUi2c->base) & UI2C_PROTSTS_ACKIF_Msk) != UI2C_PROTSTS_ACKIF_Msk) && !ignore_nack)
        {
            LOG_E("NACK: sending second addr\n");

            return -RT_EIO;
        }
        UI2C_CLR_PROT_INT_FLAG(psNuUi2c->base, UI2C_PROTSTS_ACKIF_Msk);

        if (flags & RT_I2C_RD)
        {
            LOG_D("send repeated start condition\n");

            UI2C_SET_CONTROL_REG(psNuUi2c->base, (UI2C_CTL_PTRG | UI2C_CTL_STA));
            ret = nu_ui2c_wait_ready_with_timeout(psNuUi2c);
            if (ret != RT_EOK) //for timeout condition
                return -RT_EIO;

            if (((UI2C_GET_PROT_STATUS(psNuUi2c->base) & UI2C_PROTSTS_STARIF_Msk) != UI2C_PROTSTS_STARIF_Msk) && !ignore_nack)
            {
                LOG_E("sending repeated START fail\n");

                return -RT_EIO;
            }
            UI2C_CLR_PROT_INT_FLAG(psNuUi2c->base, UI2C_PROTSTS_STARIF_Msk);

            addr1 |= RT_I2C_RD;

            ret = nu_ui2c_send_data(psNuUi2c,  addr1);
            if (ret != RT_EOK) //for timeout condition
                return -RT_EIO;

            if (((UI2C_GET_PROT_STATUS(psNuUi2c->base) & UI2C_PROTSTS_ACKIF_Msk) != UI2C_PROTSTS_ACKIF_Msk) && !ignore_nack)
            {
                LOG_E("NACK: sending repeated addr\n");
                return -RT_EIO;
            }
            UI2C_CLR_PROT_INT_FLAG(psNuUi2c->base, UI2C_PROTSTS_ACKIF_Msk);
        }
    }
    else
    {
        /* 7-bit addr */
        addr1 = msg->addr << 1;
        if (flags & RT_I2C_RD)
            addr1 |= RT_I2C_RD;

        /* Send device address */
        ret = nu_ui2c_send_data(psNuUi2c,  addr1); /* Send Address */
        if (ret != RT_EOK) //for timeout condition
            return -RT_EIO;

        if (((UI2C_GET_PROT_STATUS(psNuUi2c->base) & UI2C_PROTSTS_ACKIF_Msk) != UI2C_PROTSTS_ACKIF_Msk)
                && !ignore_nack)
                {
            LOG_E("sending addr fail\n");
            return -RT_EIO;
        }
        UI2C_CLR_PROT_INT_FLAG(psNuUi2c->base, UI2C_PROTSTS_ACKIF_Msk);
    }

    return RT_EOK;
}

static rt_size_t nu_ui2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                  struct rt_i2c_msg msgs[],
                                  rt_uint32_t num)
                                  {
    struct rt_i2c_msg *msg;
    rt_size_t i = 0;
    rt_uint32_t cnt_data;
    rt_uint16_t ignore_nack;
    rt_err_t ret;
    nu_ui2c_t psNuUi2c = (nu_ui2c_t) bus;

    RT_ASSERT(bus);

    /* Clear status */
    (psNuUi2c->base)->PROTSTS = (psNuUi2c->base)->PROTSTS;

    UI2C_SET_CONTROL_REG(psNuUi2c->base, UI2C_CTL_STA);
    ret = nu_ui2c_wait_ready_with_timeout(psNuUi2c);
    if (ret != RT_EOK) //for timeout condition
    {
        rt_set_errno(-RT_ETIMEOUT);
        goto fail_nu_ui2c_mst_xfer;
    }
    if (((UI2C_GET_PROT_STATUS(psNuUi2c->base) & UI2C_PROTSTS_STARIF_Msk) != UI2C_PROTSTS_STARIF_Msk))
    {
        LOG_E("Send START Fail");
        goto fail_nu_ui2c_mst_xfer;
    }
    UI2C_CLR_PROT_INT_FLAG(psNuUi2c->base, UI2C_PROTSTS_STARIF_Msk);

    psNuUi2c->msg = msgs;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;

        if (!(msg->flags & RT_I2C_NO_START))
        {
            if (i > 0)
            {
                UI2C_SET_CONTROL_REG(psNuUi2c->base, (UI2C_CTL_PTRG | UI2C_CTL_STA));/* Send repeat START */
                ret = nu_ui2c_wait_ready_with_timeout(psNuUi2c);
                if (ret != RT_EOK) //for timeout condition
                    break;

                if (((UI2C_GET_PROT_STATUS(psNuUi2c->base) & UI2C_PROTSTS_STARIF_Msk) != UI2C_PROTSTS_STARIF_Msk)) /* Check Send repeat START */
                {
                    i = 0;
                    LOG_E("Send repeat START Fail");
                    break;
                }
                UI2C_CLR_PROT_INT_FLAG(psNuUi2c->base, UI2C_PROTSTS_STARIF_Msk);
            }

            if ((RT_EOK != nu_ui2c_send_address(psNuUi2c, msg))
                    && !ignore_nack)
                    {
                i = 0;
                //LOG_E("Send Address Fail");
                break;
            }
        }

        if (psNuUi2c->msg[i].flags & RT_I2C_RD) /* Receive Bytes */
        {
            rt_uint32_t do_rd_nack = (i == (num - 1));
            for (cnt_data = 0 ; cnt_data < (psNuUi2c->msg[i].len) ; cnt_data++)
            {
                /* NACK after last byte  for hardware setting */
                do_rd_nack += (cnt_data == (psNuUi2c->msg[i].len - 1));
                if (do_rd_nack == 2)
                {
                    UI2C_SET_CONTROL_REG(psNuUi2c->base, UI2C_CTL_PTRG);
                }
                else
                {
                    UI2C_SET_CONTROL_REG(psNuUi2c->base, (UI2C_CTL_PTRG | UI2C_CTL_AA));
                }
                ret = nu_ui2c_wait_ready_with_timeout(psNuUi2c);
                if (ret != RT_EOK)
                    break;

                if (psNuUi2c->base->PROTCTL & UI2C_CTL_AA)
                {
                    /*Master Receive Data ACK*/
                    if (((UI2C_GET_PROT_STATUS(psNuUi2c->base) & UI2C_PROTSTS_ACKIF_Msk) != UI2C_PROTSTS_ACKIF_Msk))
                    {
                        i = 0;
                        break;
                    }
                    UI2C_CLR_PROT_INT_FLAG(psNuUi2c->base, UI2C_PROTSTS_ACKIF_Msk);
                }
                else
                {
                    /*Master Receive Data NACK*/
                    if (((UI2C_GET_PROT_STATUS(psNuUi2c->base) & UI2C_PROTSTS_NACKIF_Msk) != UI2C_PROTSTS_NACKIF_Msk))
                    {
                        i = 0;
                        break;
                    }
                    UI2C_CLR_PROT_INT_FLAG(psNuUi2c->base, UI2C_PROTSTS_NACKIF_Msk);
                }

                psNuUi2c->msg[i].buf[cnt_data] = psNuUi2c->base->RXDAT;
            }
        }
        else /* Send Bytes */
        {
            for (cnt_data = 0 ; cnt_data < (psNuUi2c->msg[i].len) ; cnt_data++)
            {
                /* Send register number and MSB of data */
                ret = nu_ui2c_send_data(psNuUi2c, (uint8_t)(psNuUi2c->msg[i].buf[cnt_data]));
                if (ret != RT_EOK) //for timeout condition
                    break;

                if (((UI2C_GET_PROT_STATUS(psNuUi2c->base) & UI2C_PROTSTS_ACKIF_Msk) != UI2C_PROTSTS_ACKIF_Msk)
                        && !ignore_nack
                   ) /* Send data and get Ack */
                   {
                    i = 0;
                    break;
                }
                UI2C_CLR_PROT_INT_FLAG(psNuUi2c->base, UI2C_PROTSTS_ACKIF_Msk);
            }
        }
    }
    UI2C_SET_CONTROL_REG(psNuUi2c->base, (UI2C_CTL_PTRG | UI2C_CTL_STO));
    ret = nu_ui2c_wait_ready_with_timeout(psNuUi2c);
    if (ret != RT_EOK) //for timeout condition
    {
        rt_set_errno(-RT_ETIMEOUT);
        goto fail_nu_ui2c_mst_xfer;
    }
    if (((UI2C_GET_PROT_STATUS(psNuUi2c->base) & UI2C_PROTSTS_STORIF_Msk) != UI2C_PROTSTS_STORIF_Msk))
    {
        i = 0;
        LOG_E("Send STOP Fail");
    }

    UI2C_CLR_PROT_INT_FLAG(psNuUi2c->base, UI2C_PROTSTS_STORIF_Msk);
    UI2C_SET_CONTROL_REG(psNuUi2c->base, UI2C_CTL_PTRG);
    UI2C_DISABLE_10BIT_ADDR_MODE(psNuUi2c->base); /*clear all sub modes like 10 bit mode*/
    psNuUi2c->msg = RT_NULL;

    return i;

fail_nu_ui2c_mst_xfer:

    return 0;
}
int rt_hw_ui2c_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (UI2C_START + 1); i < UI2C_CNT; i++)
    {
        /* Reset and initial IP engine. */
        SYS_ResetModule(nu_ui2c_arr[i].rst);
        UI2C_Close(nu_ui2c_arr[i].base);
        UI2C_Open(nu_ui2c_arr[i].base, 100000);
        nu_ui2c_arr[i].parent.ops = &nu_ui2c_ops;

        ret = rt_i2c_bus_device_register(&nu_ui2c_arr[i].parent, nu_ui2c_arr[i].name);
        RT_ASSERT(RT_EOK == ret);
    }

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_ui2c_init);
#endif //#if defined(BSP_USING_UI2C)
