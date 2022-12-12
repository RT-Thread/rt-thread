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
    uint32_t int_flag;
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
    nu_can_t psNuCAN  = (nu_can_t)param;

    /* Get base address of CAN register */
    CAN_T *base = psNuCAN->base;

    /* Get interrupt event */
    uint32_t u32IIDRstatus = CAN_GET_INT_PENDING_STATUS(base) & CAN_IIDR_INTID_Msk;

    /* Check Status Interrupt Flag (Error status Int and Status change Int) */
    if (u32IIDRstatus == 0x00008000)
    {
        /**************************/
        /* Status Change interrupt*/
        /**************************/
        if (base->STATUS & CAN_STATUS_TXOK_Msk)
        {
            base->STATUS &= ~CAN_STATUS_TXOK_Msk;    /* Clear Tx Ok status*/
#ifndef RT_CAN_USING_HDR
            if (psNuCAN->int_flag & RT_DEVICE_FLAG_INT_TX)
            {
                /*Using as Lisen,Loopback,Loopback+Lisen mode*/
                rt_hw_can_isr(&psNuCAN->dev, RT_CAN_EVENT_TX_DONE);
            }
#endif
        }

        if (base->STATUS & CAN_STATUS_RXOK_Msk)
        {
            base->STATUS &= ~CAN_STATUS_RXOK_Msk;   /* Clear Rx Ok status*/
#ifndef RT_CAN_USING_HDR
            if (psNuCAN->int_flag & RT_DEVICE_FLAG_INT_RX)
            {
                /*Using as Lisen,Loopback,Loopback+Lisen mode*/
                rt_hw_can_isr(&psNuCAN->dev, RT_CAN_EVENT_RX_IND);
            }
#endif
        }

        /**************************/
        /* Error Status interrupt */
        /**************************/
        if (base->STATUS & CAN_STATUS_EWARN_Msk)
        {
            rt_kprintf("[%s]EWARN INT\n", psNuCAN->name) ;
        }

        if (base->STATUS & CAN_STATUS_BOFF_Msk)
        {
            rt_kprintf("[%s]BUSOFF INT\n", psNuCAN->name) ;

            /* To release busoff pin */
            CAN_EnterInitMode(base, CAN_CON_INIT_Msk | CAN_CON_CCE_Msk);
            CAN_LeaveInitMode(base);
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
        if ((psNuCAN->int_flag & RT_DEVICE_FLAG_INT_TX) &&
                (u32IIDRstatus <= RX_MSG_ID_INDEX))
        {
            /*Message RAM 0~RX_MSG_ID_INDEX for CAN Tx using*/
            rt_hw_can_isr(&psNuCAN->dev, RT_CAN_EVENT_TX_DONE);
        }
        else if (psNuCAN->int_flag & RT_DEVICE_FLAG_INT_RX)
        {
            /*Message RAM RX_MSG_ID_INDEX~31 for CAN Rx using*/
            rt_hw_can_isr(&psNuCAN->dev, (RT_CAN_EVENT_RX_IND | ((u32IIDRstatus - 1) << 8)));
        }
        CAN_CLR_INT_PENDING_BIT(base, (u32IIDRstatus - 1));     /* Clear Interrupt Pending */
    }
#endif
}

static void nu_can_ie(nu_can_t psNuCAN)
{
    uint32_t u32CanIE = CAN_CON_IE_Msk;

    if (psNuCAN->int_flag & (RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX))
    {
        u32CanIE |= CAN_CON_SIE_Msk;
    }
    else
    {
        u32CanIE &= ~CAN_CON_SIE_Msk;
    }

    if (psNuCAN->int_flag & RT_DEVICE_CAN_INT_ERR)
    {
        u32CanIE |= CAN_CON_EIE_Msk;
    }
    else
    {
        u32CanIE &= ~CAN_CON_EIE_Msk;
    }

    if (u32CanIE & (CAN_CON_SIE_Msk | CAN_CON_EIE_Msk))
    {
        CAN_EnableInt(psNuCAN->base, u32CanIE);

        /* Enable interrupt. */
        rt_hw_interrupt_umask(psNuCAN->irqn);
    }
    else
    {
        u32CanIE |= (CAN_CON_IE_Msk | CAN_CON_SIE_Msk);
        CAN_DisableInt(psNuCAN->base, u32CanIE);

        /* Disable interrupt. */
        rt_hw_interrupt_mask(psNuCAN->irqn);
    }
}

static rt_err_t nu_can_configure(struct rt_can_device *can, struct can_configure *cfg)
{
    nu_can_t psNuCAN  = (nu_can_t)can;
    uint32_t u32CANMode;

    RT_ASSERT(can);
    RT_ASSERT(cfg);

    /* Get base address of CAN register */
    CAN_T *base = psNuCAN->base;

    /* Reset this module */
    nu_sys_ip_reset(psNuCAN->rstidx);

    u32CANMode = (cfg->mode == RT_CAN_MODE_NORMAL) ? CAN_NORMAL_MODE : CAN_BASIC_MODE;

    /*Set the CAN Bit Rate and Operating mode*/
    if (CAN_Open(base, cfg->baud_rate, u32CANMode) != cfg->baud_rate)
        goto exit_nu_can_configure;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
#ifdef RT_CAN_USING_HDR
        CAN_LeaveTestMode(base);
#else
        CAN_EnterTestMode(base, CAN_TEST_BASIC_Msk);
#endif
        break;
    case RT_CAN_MODE_LISTEN:
        CAN_EnterTestMode(base, CAN_TEST_BASIC_Msk | CAN_TEST_SILENT_Msk);
        break;
    case RT_CAN_MODE_LOOPBACK:
        CAN_EnterTestMode(base, CAN_TEST_BASIC_Msk | CAN_TEST_LBACK_Msk);
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        CAN_EnterTestMode(base, CAN_TEST_BASIC_Msk | CAN_TEST_SILENT_Msk | CAN_TEST_LBACK_Msk);
        break;
    default:
        rt_kprintf("Unsupported Operating mode");
        goto exit_nu_can_configure;
    }

    nu_can_ie(psNuCAN);

    return RT_EOK;

exit_nu_can_configure:

    CAN_Close(base);

    return -(RT_ERROR);
}

static rt_err_t nu_can_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval = (rt_uint32_t)arg;
    nu_can_t psNuCAN = (nu_can_t)can;

    RT_ASSERT(can);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SET_INT:
        psNuCAN->int_flag |= argval;
        nu_can_ie(psNuCAN);
        break;

    case RT_DEVICE_CTRL_CLR_INT:
        psNuCAN->int_flag &= ~argval;
        nu_can_ie(psNuCAN);
        break;

    case RT_CAN_CMD_SET_FILTER:
    {
        struct rt_can_filter_config *filter_cfg = (struct rt_can_filter_config *)arg;

        for (int i = 0; i < filter_cfg->count; i++)
        {
            /*set the filter message object*/
            if (filter_cfg->items[i].mode == 1)
            {
                if (CAN_SetRxMsgObjAndMsk(psNuCAN->base, MSG(filter_cfg->items[i].hdr_bank + RX_MSG_ID_INDEX), filter_cfg->items[i].ide, filter_cfg->items[i].id, filter_cfg->items[i].mask, FALSE) == FALSE)
                {
                    return -(RT_ERROR);
                }
            }
            else
            {
                /*set the filter message object*/
                if (CAN_SetRxMsgAndMsk(psNuCAN->base, MSG(filter_cfg->items[i].hdr_bank + RX_MSG_ID_INDEX), filter_cfg->items[i].ide, filter_cfg->items[i].id, filter_cfg->items[i].mask) == FALSE)
                {
                    return -(RT_ERROR);
                }
            }
        }
    }
    break;

    case RT_CAN_CMD_SET_MODE:
        if ((argval == RT_CAN_MODE_NORMAL) ||
                (argval == RT_CAN_MODE_LISTEN) ||
                (argval == RT_CAN_MODE_LOOPBACK) ||
                (argval == RT_CAN_MODE_LOOPBACKANLISTEN))
        {
            if (argval != can->config.mode)
            {
                can->config.mode = argval;
                return nu_can_configure(can, &can->config);
            }
        }
        else
        {
            return -(RT_ERROR);
        }
        break;

    case RT_CAN_CMD_SET_BAUD:
    {
        if ((argval == CAN1MBaud) ||
                (argval == CAN800kBaud) ||
                (argval == CAN500kBaud) ||
                (argval == CAN250kBaud) ||
                (argval == CAN125kBaud) ||
                (argval == CAN100kBaud) ||
                (argval == CAN50kBaud) ||
                (argval == CAN20kBaud) ||
                (argval == CAN10kBaud))
        {
            if (argval != can->config.baud_rate)
            {
                can->config.baud_rate = argval;
                return nu_can_configure(can, &can->config);
            }
        }
        else
        {
            return -(RT_ERROR);
        }
    }
    break;

    case RT_CAN_CMD_SET_PRIV:
        if (argval != RT_CAN_MODE_PRIV &&
                argval != RT_CAN_MODE_NOPRIV)
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
        rt_uint32_t errtype = psNuCAN->base->ERR;

        RT_ASSERT(arg);

        /*Receive Error Counter, return value is with Receive Error Passive.*/
        can->status.rcverrcnt = (errtype >> 8);

        /*Transmit Error Counter*/
        can->status.snderrcnt = (errtype & 0xFF);

        /*Last Error Type*/
        can->status.lasterrtype = CAN_GET_INT_STATUS(psNuCAN->base) & 0x8000;

        /*Status error code*/
        can->status.errcode = CAN_GET_INT_STATUS(psNuCAN->base) & 0x07;

        rt_memcpy(arg, &can->status, sizeof(struct rt_can_status));
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
    struct rt_can_msg *pmsg;
    nu_can_t psNuCAN = (nu_can_t)can;

    RT_ASSERT(can);
    RT_ASSERT(buf);

    pmsg = (struct rt_can_msg *) buf;

    if (pmsg->ide == RT_CAN_STDID && IS_CAN_STDID(pmsg->id))
    {
        /* Standard ID (11 bits)*/
        tMsg.IdType = CAN_STD_ID;
        tMsg.Id  = pmsg->id ;
    }
    else if (pmsg->ide == RT_CAN_EXTID && IS_CAN_EXTID(pmsg->id))
    {
        /* Extended ID (29 bits)*/
        tMsg.IdType = CAN_EXT_ID;
        tMsg.Id = pmsg->id ;
    }
    else
    {
        goto exit_nu_can_sendmsg;
    }

    if (pmsg->rtr == RT_CAN_DTR)
    {
        /* Data frame */
        tMsg.FrameType = CAN_DATA_FRAME;
    }
    else if (pmsg->rtr == RT_CAN_RTR)
    {
        /* Remote frame */
        tMsg.FrameType = CAN_REMOTE_FRAME;
    }
    else
    {
        goto exit_nu_can_sendmsg;
    }

    /* Check the parameters */
    if (IS_CAN_DLC(pmsg->len))
    {
        tMsg.DLC = pmsg->len;
    }
    else
    {
        goto exit_nu_can_sendmsg;
    }

    if (pmsg->data && pmsg->len)
    {
        rt_memcpy(&tMsg.Data[0], pmsg->data, pmsg->len);
    }
    else
    {
        goto exit_nu_can_sendmsg;
    }

    /* Configure Msg RAM and send the Msg in the RAM. */
    if (CAN_Transmit(psNuCAN->base, MSG(boxno), &tMsg) == FALSE)
    {
        goto exit_nu_can_sendmsg;
    }

    return RT_EOK;

exit_nu_can_sendmsg:

    return -(RT_ERROR);
}

static int nu_can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    STR_CANMSG_T tMsg;
    struct rt_can_msg *pmsg;
    nu_can_t psNuCAN = (nu_can_t)can;

    RT_ASSERT(can);
    RT_ASSERT(buf);

    pmsg = (struct rt_can_msg *) buf;

    /* get data */
    if (CAN_Receive(psNuCAN->base, boxno, &tMsg) == FALSE)
    {
        rt_kprintf("No available RX Msg.\n");
        return -(RT_ERROR);
    }

#ifdef RT_CAN_USING_HDR
    /* Hardware filter messages are valid */
    pmsg->hdr_index = boxno - RX_MSG_ID_INDEX;
    can->hdr[pmsg->hdr_index].connected = 1;
#endif

    pmsg->ide = (tMsg.IdType == CAN_STD_ID) ? RT_CAN_STDID : RT_CAN_EXTID;
    pmsg->rtr = (tMsg.FrameType == CAN_DATA_FRAME) ? RT_CAN_DTR : RT_CAN_RTR;
    pmsg->id  = tMsg.Id;
    pmsg->len = tMsg.DLC ;

    if (pmsg->data && pmsg->len)
        rt_memcpy(pmsg->data, &tMsg.Data[0], pmsg->len);

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
