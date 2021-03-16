/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-12      Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_CAN)

#include <rtdevice.h>
#include <rthw.h>
#include "NuMicro.h"
#include <drv_sys.h>

/* Private Define ---------------------------------------------------------------*/
#define RX_MSG_ID_INDEX        16
#define IS_CAN_STDID(STDID)   ((STDID) <= 0x7FFU)
#define IS_CAN_EXTID(EXTID)   ((EXTID) <= 0x1FFFFFFFU)
#define IS_CAN_DLC(DLC)       ((DLC) <= 8U)

/* Default config for serial_configure structure */
#define NU_CAN_CONFIG_DEFAULT                  \
{                                              \
    CAN1MBaud,           /* 1M bits/s       */ \
    RT_CANMSG_BOX_SZ,    /* message box max size */ \
    RT_CANSND_BOX_NUM,   /* message box number   */ \
    RT_CAN_MODE_NORMAL,  /* Normal mode     */ \
    0,                   /* privmode        */ \
    0,                   /* reserved        */ \
    100,                 /* Timeout Tick    */ \
}

enum
{
    CAN_START = -1,
#if defined(BSP_USING_CAN0)
    CAN0_IDX,
#endif
#if defined(BSP_USING_CAN1)
    CAN1_IDX,
#endif
#if defined(BSP_USING_CAN2)
    CAN2_IDX,
#endif
#if defined(BSP_USING_CAN3)
    CAN3_IDX,
#endif
    CAN_CNT,
};

/* Private Typedef --------------------------------------------------------------*/
struct nu_can
{
    struct rt_can_device dev;
    char *name;
    CAN_T *base;
    IRQn_Type irqn;
    E_SYS_IPRST rstidx;
    E_SYS_IPCLK clkidx;
};
typedef struct nu_can *nu_can_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_can_configure(struct rt_can_device *can, struct can_configure *cfg);
static rt_err_t nu_can_control(struct rt_can_device *can, int cmd, void *arg);
static int nu_can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno);
static int nu_can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno);
static void nu_can_isr(int vector, void *param);

static struct nu_can nu_can_arr[] =
{
#if defined(BSP_USING_CAN0)
    {
        .name = "can0",
        .base = CAN0,
        .irqn =  IRQ_CAN0,
        .rstidx = CAN0RST,
        .clkidx = CAN0CKEN,
    },
#endif
#if defined(BSP_USING_CAN1)
    {
        .name = "can1",
        .base = CAN1,
        .irqn =  IRQ_CAN1,
        .rstidx = CAN1RST,
        .clkidx = CAN1CKEN,
    },
#endif
#if defined(BSP_USING_CAN2)
    {
        .name = "can2",
        .base = CAN2,
        .irqn =  IRQ_CAN2,
        .rstidx = CAN2RST,
        .clkidx = CAN2CKEN,
    },
#endif
#if defined(BSP_USING_CAN3)
    {
        .name = "can3",
        .base = CAN3,
        .irqn =  IRQ_CAN3,
        .rstidx = CAN3RST,
        .clkidx = CAN3CKEN,
    },
#endif
}; /* struct nu_can */

/* Public functions ------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/
static const struct rt_can_ops nu_can_ops =
{
    .configure = nu_can_configure,
    .control = nu_can_control,
    .sendmsg = nu_can_sendmsg,
    .recvmsg = nu_can_recvmsg,
};

static const struct can_configure nu_can_default_config = NU_CAN_CONFIG_DEFAULT;

/* Interrupt Handle Function  ----------------------------------------------------*/
static void nu_can_isr(int vector, void *param)
{
    uint32_t u32IIDRstatus;
    nu_can_t psNuCAN  = (nu_can_t)param;

    /* Get base address of CAN register */
    CAN_T *base = psNuCAN->base;

    /* Get interrupt event */
    u32IIDRstatus = CAN_GET_INT_PENDING_STATUS(base);

    if (u32IIDRstatus == 0x00008000)       /* Check Status Interrupt Flag (Error status Int and Status change Int) */
    {
        /**************************/
        /* Status Change interrupt*/
        /**************************/
        if (base->STATUS & CAN_STATUS_TXOK_Msk)
        {
            base->STATUS &= ~CAN_STATUS_TXOK_Msk;    /* Clear Tx Ok status*/
            //rt_kprintf("%s: TX\n", psNuCAN->name) ;
#ifndef RT_CAN_USING_HDR
            /* Using as Lisen,Loopback,Loopback+Lisen mode*/
            rt_hw_can_isr(&psNuCAN->dev, RT_CAN_EVENT_TX_DONE);
#endif
        }

        if (base->STATUS & CAN_STATUS_RXOK_Msk)
        {
            base->STATUS &= ~CAN_STATUS_RXOK_Msk;   /* Clear Rx Ok status*/
            //rt_kprintf("%s: RX\n", psNuCAN->name) ;
#ifndef RT_CAN_USING_HDR
            /* Using as Lisen,Loopback,Loopback+Lisen mode*/
            rt_hw_can_isr(&psNuCAN->dev, RT_CAN_EVENT_RX_IND);
#endif
        }

        /**************************/
        /* Error Status interrupt */
        /**************************/
        if (base->STATUS & CAN_STATUS_EWARN_Msk)
        {
            rt_kprintf("%s: EWARN\n", psNuCAN->name) ;
        }

        if (base->STATUS & CAN_STATUS_BOFF_Msk)
        {
            rt_kprintf("%s: BUSOFF\n", psNuCAN->name) ;

            /* Do Init to release busoff pin */
            base->CON = (CAN_CON_INIT_Msk | CAN_CON_CCE_Msk);
            base->CON &= (~(CAN_CON_INIT_Msk | CAN_CON_CCE_Msk));
            while (base->CON & CAN_CON_INIT_Msk);
        }

        if (base->STATUS & CAN_STATUS_LEC_Msk)
        {
            rt_kprintf("[%s] Last Error Code %03x\n", psNuCAN->name, base->STATUS & CAN_STATUS_LEC_Msk) ;
        }

    }
#ifdef RT_CAN_USING_HDR
    /*IntId: 0x0001-0x0020, Number of Message Object which caused the interrupt.*/
    else if (u32IIDRstatus > 0 && u32IIDRstatus <= 32)
    {
        /*Message RAM 0~RX_MSG_ID_INDEX for CAN Tx using*/
        if (u32IIDRstatus <= RX_MSG_ID_INDEX)
        {
            //rt_kprintf("[%s-Tx]IntId = %d\n", psNuCAN->name, u32IIDRstatus);
            rt_hw_can_isr(&psNuCAN->dev, RT_CAN_EVENT_TX_DONE);
        }
        else /*Message RAM RX_MSG_ID_INDEX~31 for CAN Rx using*/
        {
            //rt_kprintf("[%s-Rx]IntId = %d\n",  psNuCAN->name, u32IIDRstatus);
            rt_hw_can_isr(&psNuCAN->dev, (RT_CAN_EVENT_RX_IND | ((u32IIDRstatus - 1) << 8)));
        }
        CAN_CLR_INT_PENDING_BIT(base, (u32IIDRstatus - 1));     /* Clear Interrupt Pending */
    }
#endif

}


static rt_err_t nu_can_configure(struct rt_can_device *can, struct can_configure *cfg)
{
    nu_can_t psNuCAN  = (nu_can_t)can;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    /* Get base address of CAN register */
    CAN_T *base = psNuCAN->base;

    RT_ASSERT(base != RT_NULL);

    switch (cfg->mode)
    {
    /* CAN default Normal mode */
    case RT_CAN_MODE_NORMAL:
        can->config.mode = CAN_NORMAL_MODE;
        break;
    case RT_CAN_MODE_LISEN:
        can->config.mode = RT_CAN_MODE_LISEN;
        break;
    case RT_CAN_MODE_LOOPBACK:
        can->config.mode = RT_CAN_MODE_LOOPBACK;
        break;
    case RT_CAN_MODE_LOOPBACKANLISEN:
        can->config.mode = RT_CAN_MODE_LOOPBACKANLISEN;
        break;
    default:
        rt_kprintf("Unsupported Operating mode");
        goto exit_nu_can_configure;
    }

    nu_sys_ip_reset(psNuCAN->rstidx);

    /*Set the CAN Bit Rate and Operating mode*/
    if (CAN_Open(base, can->config.baud_rate, can->config.mode) < 1)
        return -(RT_ERROR);


    switch (cfg->mode)
    {
    /* CAN default Normal mode */
    case RT_CAN_MODE_NORMAL:
#ifdef RT_CAN_USING_HDR
        CAN_LeaveTestMode(base);
#else
        CAN_EnterTestMode(base, CAN_TEST_BASIC_Msk);
#endif
        break;
    case RT_CAN_MODE_LISEN:
        CAN_EnterTestMode(base, CAN_TEST_BASIC_Msk | CAN_TEST_SILENT_Msk);
        break;
    case RT_CAN_MODE_LOOPBACK:
        CAN_EnterTestMode(base, CAN_TEST_BASIC_Msk | CAN_TEST_LBACK_Msk);
        break;
    case RT_CAN_MODE_LOOPBACKANLISEN:
        CAN_EnterTestMode(base, CAN_TEST_BASIC_Msk | CAN_TEST_SILENT_Msk | CAN_TEST_LBACK_Msk);
        break;
    default:
        rt_kprintf("Unsupported Operating mode");
        goto exit_nu_can_configure;
    }


    return RT_EOK;

exit_nu_can_configure:

    CAN_Close(base);

    return -(RT_ERROR);
}

static rt_err_t nu_can_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval;
    nu_can_t psNuCAN  = (nu_can_t)can;

#ifdef RT_CAN_USING_HDR
    struct rt_can_filter_config *filter_cfg;
#endif
    /* Get base address of CAN register */
    CAN_T *base = psNuCAN->base;

    RT_ASSERT(base != RT_NULL);
    /* Check baud rate */
    RT_ASSERT(can->config.baud_rate != 0);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if ((argval == RT_DEVICE_FLAG_INT_RX) || (argval == RT_DEVICE_FLAG_INT_TX))
        {
            /* Disable NVIC interrupt. */
            rt_hw_interrupt_mask(psNuCAN->irqn);

            /* Disable Status Change Interrupt  */
            CAN_DisableInt(base, CAN_CON_IE_Msk | CAN_CON_SIE_Msk);

        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            /* Disable interrupt. */
            rt_hw_interrupt_mask(psNuCAN->irqn);

            /* Disable Error Interrupt */
            CAN_DisableInt(base, CAN_CON_EIE_Msk);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX || (argval == RT_DEVICE_FLAG_INT_TX))
        {
            /* Enable Status Change Interrupt  */
            CAN_EnableInt(base, CAN_CON_IE_Msk | CAN_CON_SIE_Msk);

            /* Enable interrupt. */
            rt_hw_interrupt_umask(psNuCAN->irqn);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            /* Enable Error Status and Status Change Interrupt  */
            CAN_EnableInt(base, CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk);

            /* Enable interrupt. */
            rt_hw_interrupt_umask(psNuCAN->irqn);
        }
        break;

#ifdef RT_CAN_USING_HDR
    case RT_CAN_CMD_SET_FILTER:
        filter_cfg = (struct rt_can_filter_config *)arg;

        for (int i = 0; i < filter_cfg->count; i++)
        {

            /*set the filter message object*/
            if (filter_cfg->items[i].mode == 1)
            {
                if (CAN_SetRxMsgObjAndMsk(base, MSG(filter_cfg->items[i].hdr + RX_MSG_ID_INDEX), filter_cfg->items[i].ide, filter_cfg->items[i].id, filter_cfg->items[i].mask, FALSE) == FALSE)
                {
                    return -(RT_ERROR);
                }
            }
            else
            {
                /*set the filter message object*/
                if (CAN_SetRxMsgAndMsk(base, MSG(filter_cfg->items[i].hdr + RX_MSG_ID_INDEX), filter_cfg->items[i].ide, filter_cfg->items[i].id, filter_cfg->items[i].mask) == FALSE)
                {
                    return -(RT_ERROR);
                }
            }
        }
        break;
#endif

    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL && argval != RT_CAN_MODE_LISEN &&
                argval != RT_CAN_MODE_LOOPBACK && argval != RT_CAN_MODE_LOOPBACKANLISEN)
        {
            return -(RT_ERROR);
        }
        if (argval != can->config.mode)
        {
            can->config.mode = argval;
            return nu_can_configure(can, &can->config);
        }
        break;

    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t) arg;
        if (argval != CAN1MBaud && argval != CAN800kBaud && argval != CAN500kBaud && argval != CAN250kBaud &&
                argval != CAN125kBaud && argval != CAN100kBaud && argval != CAN50kBaud  && argval != CAN20kBaud  && argval != CAN10kBaud)
        {
            return -(RT_ERROR);
        }
        if (argval != can->config.baud_rate)
        {
            can->config.baud_rate = argval;
            return nu_can_configure(can, &can->config);
        }
        break;

    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_PRIV && argval != RT_CAN_MODE_NOPRIV)
        {
            return -(RT_ERROR);
        }
        if (argval != can->config.privmode)
        {
            can->config.privmode = argval;
            return nu_can_configure(can, &can->config);
        }
        break;

    case RT_CAN_CMD_GET_STATUS:
    {
        rt_uint32_t errtype;
        errtype = base->ERR;
        /*Receive Error Counter*/
        can->status.rcverrcnt = (errtype >> 8);
        /*Transmit Error Counter*/
        can->status.snderrcnt = ((errtype >> 24) & 0xFF);
        can->status.lasterrtype = CAN_GET_INT_STATUS(base) & 0x8000;
        /*status error code*/
        can->status.errcode = CAN_GET_INT_STATUS(base) & 0x07;
        rt_memcpy(arg, &can->status, sizeof(can->status));
    }
    break;

    default:
        return -(RT_EINVAL);

    }

    return RT_EOK;
}

static int nu_can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    STR_CANMSG_T tMsg;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;

    /* Get base address of CAN register */
    CAN_T *base = ((nu_can_t)can)->base;

    RT_ASSERT(base != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    /* Check the parameters */
    RT_ASSERT(IS_CAN_DLC(pmsg->len));

    /* Standard ID (11 bits)*/
    if (pmsg->ide == RT_CAN_STDID)
    {
        tMsg.IdType = CAN_STD_ID;
        RT_ASSERT(IS_CAN_STDID(pmsg->id))
        tMsg.Id  = pmsg->id ;
    }
    else
    {
        /* Extended ID (29 bits)*/
        tMsg.IdType = CAN_EXT_ID;
        RT_ASSERT(IS_CAN_EXTID(pmsg->id));
        tMsg.Id = pmsg->id ;
    }

    if (pmsg->rtr == RT_CAN_DTR)
    {
        /* Data frame */
        tMsg.FrameType = CAN_DATA_FRAME;
    }
    else
    {
        /* Remote frame */
        tMsg.FrameType = CAN_REMOTE_FRAME;
    }
    tMsg.DLC = pmsg->len;
    rt_memcpy(tMsg.Data, pmsg->data, pmsg->len);

    if (CAN_Transmit(base, MSG(boxno), &tMsg) == FALSE) // Configure Msg RAM and send the Msg in the RAM
    {
        return -(RT_ERROR);
    }

    return RT_EOK;
}
static int nu_can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    STR_CANMSG_T tMsg;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    /* Get base address of CAN register */
    CAN_T *base = ((nu_can_t)can)->base;

    RT_ASSERT(base != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    /* get data */
    if (CAN_Receive(base, boxno, &tMsg) == FALSE)
    {
        rt_kprintf("No available RX Msg.\n");
        return -(RT_ERROR);
    }

#ifdef RT_CAN_USING_HDR
    /* Hardware filter messages are valid */
    pmsg->hdr = boxno - RX_MSG_ID_INDEX;
    can->hdr[pmsg->hdr].connected = 1;
#endif

    /* Standard ID (11 bits)*/
    if (tMsg.IdType == CAN_STD_ID)
    {
        pmsg->ide = RT_CAN_STDID;
        pmsg->id  = tMsg.Id;
    }
    else /* Extended ID (29 bits)*/
    {
        pmsg->ide = RT_CAN_EXTID;
        pmsg->id  = tMsg.Id;
    }

    if (tMsg.FrameType == CAN_DATA_FRAME)
    {
        /* Data frame */
        pmsg->rtr = RT_CAN_DTR;
    }
    else
    {
        /* Remote frame */
        pmsg->rtr = RT_CAN_RTR;
    }

    pmsg->len = tMsg.DLC ;

    rt_memcpy(pmsg->data, tMsg.Data, pmsg->len);

    return RT_EOK;
}

/**
 * Hardware CAN Initialization
 */
static int rt_hw_can_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (CAN_START + 1); i < CAN_CNT; i++)
    {
        nu_can_arr[i].dev.config = nu_can_default_config;

#ifdef RT_CAN_USING_HDR
        nu_can_arr[i].dev.config.maxhdr = RT_CANMSG_BOX_SZ;
#endif

        /* Register CAN ISR */
        rt_hw_interrupt_install(nu_can_arr[i].irqn, nu_can_isr, &nu_can_arr[i], nu_can_arr[i].name);

        /* Enable IP engine clock */
        nu_sys_ipclk_enable(nu_can_arr[i].clkidx);

        /* Register can device */
        ret = rt_hw_can_register(&nu_can_arr[i].dev, nu_can_arr[i].name, &nu_can_ops, NULL);
        RT_ASSERT(ret == RT_EOK);
    }

    return (int)ret;
}
INIT_DEVICE_EXPORT(rt_hw_can_init);

#endif  //#if defined(BSP_USING_CAN)
