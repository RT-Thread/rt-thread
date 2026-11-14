/**************************************************************************/ /**
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
#define RX_MSG_ID_INDEX     16
#define IS_CAN_STDID(STDID) ((STDID) <= 0x7FFU)
#define IS_CAN_EXTID(EXTID) ((EXTID) <= 0x1FFFFFFFU)
#define IS_CAN_DLC(DLC)     ((DLC) <= 8U)

/* Default config for serial_configure structure */
#define NU_CAN_CONFIG_DEFAULT                          \
    {                                                  \
        CAN1MBaud,          /* 1M bits/s       */      \
        RT_CANMSG_BOX_SZ,   /* message box max size */ \
        RT_CANSND_BOX_NUM,  /* message box number   */ \
        RT_CAN_MODE_NORMAL, /* Normal mode     */      \
        0,                  /* privmode        */      \
        0,                  /* reserved        */      \
        100,                /* Timeout Tick    */      \
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
    rt_uint32_t tx_pending; /**< Accepted physical TX message objects awaiting a terminal IRQ. */
};
typedef struct nu_can *nu_can_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_can_configure(struct rt_can_device *can, struct can_configure *cfg);
static rt_err_t nu_can_control(struct rt_can_device *can, int cmd, void *arg);
static int nu_can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno);
static rt_ssize_t nu_can_sendmsg_nonblocking(struct rt_can_device *can, const void *buf, rt_uint32_t *mailbox);
static int nu_can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno);
static void nu_can_isr(int vector, void *param);

static struct nu_can nu_can_arr[] = {
#if defined(BSP_USING_CAN0)
    {
        .name = "can0",
        .base = CAN0,
        .irqn = IRQ_CAN0,
        .rstidx = CAN0RST,
        .clkidx = CAN0CKEN,
    },
#endif
#if defined(BSP_USING_CAN1)
    {
        .name = "can1",
        .base = CAN1,
        .irqn = IRQ_CAN1,
        .rstidx = CAN1RST,
        .clkidx = CAN1CKEN,
    },
#endif
}; /* struct nu_can */

/* Public functions ------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/
static const struct rt_can_ops nu_can_ops = {
    .configure = nu_can_configure,
    .control = nu_can_control,
    .sendmsg = nu_can_sendmsg,
    .sendmsg_nonblocking = nu_can_sendmsg_nonblocking,
    .recvmsg = nu_can_recvmsg,
};

static const struct can_configure nu_can_default_config = NU_CAN_CONFIG_DEFAULT;

/* Interrupt Handle Function  ----------------------------------------------------*/
/**
 * @brief Dispatch Nuvoton CAN status and per-message-object interrupts.
 * @param vector BSP interrupt vector.
 * @param param Pointer to the registered CAN instance.
 */
static void nu_can_isr(int vector, void *param)
{
    nu_can_t psNuCAN = (nu_can_t)param;

    /* Get base address of CAN register */
    CAN_T *base = psNuCAN->base;

    /* Get interrupt event */
    uint32_t u32IIDRstatus = CAN_GET_INT_PENDING_STATUS(base) & CAN_IIDR_INTID_Msk;
    /* BASIC uses IF0/IF1 and has a global TXOK indication, not a message-object index. */
    rt_bool_t basic = ((base->CON & CAN_CON_TEST_Msk) != 0U) &&
                      ((base->TEST & CAN_TEST_BASIC_Msk) != 0U);

    /* Check Status Interrupt Flag (Error status Int and Status change Int) */
    if (u32IIDRstatus == 0x00008000)
    {
        /**************************/
        /* Status Change interrupt*/
        /**************************/
        if (base->STATUS & CAN_STATUS_TXOK_Msk)
        {
            base->STATUS &= ~CAN_STATUS_TXOK_Msk; /* Clear Tx Ok status*/
            if (basic && (psNuCAN->int_flag & RT_DEVICE_FLAG_INT_TX) &&
                (psNuCAN->tx_pending & 1U))
            {
                psNuCAN->tx_pending &= ~1U;
                rt_hw_can_isr(&psNuCAN->dev, RT_CAN_EVENT_TX_DONE);
            }
        }

        if (base->STATUS & CAN_STATUS_RXOK_Msk)
        {
            base->STATUS &= ~CAN_STATUS_RXOK_Msk; /* Clear Rx Ok status*/
            if (basic && (psNuCAN->int_flag & RT_DEVICE_FLAG_INT_RX))
            {
                rt_hw_can_isr(&psNuCAN->dev, RT_CAN_EVENT_RX_IND);
            }
        }

        /**************************/
        /* Error Status interrupt */
        /**************************/
        if (base->STATUS & CAN_STATUS_EWARN_Msk)
        {
            rt_kprintf("[%s]EWARN INT\n", psNuCAN->name);
        }

        if (base->STATUS & CAN_STATUS_BOFF_Msk)
        {
            rt_kprintf("[%s]BUSOFF INT\n", psNuCAN->name);

            /* To release busoff pin */
            CAN_EnterInitMode(base, CAN_CON_INIT_Msk | CAN_CON_CCE_Msk);
            CAN_LeaveInitMode(base);
        }

        if (base->STATUS & CAN_STATUS_LEC_Msk)
        {
            rt_kprintf("[%s] Last Error Code %03x\n", psNuCAN->name, base->STATUS & CAN_STATUS_LEC_Msk);
        }
    }
#ifdef RT_CAN_USING_HDR
    /*IntId: 0x0001-0x0020, Number of Message Object which caused the interrupt.*/
    else if (u32IIDRstatus > 0 && u32IIDRstatus <= 32)
    {
        /* IIDR object numbers are one-based; Generic mailbox indices are zero-based. */
        rt_uint32_t boxno = u32IIDRstatus - 1U;
        if (boxno < RX_MSG_ID_INDEX)
        {
            /* Acknowledge this object before publishing its terminal to Generic. */
            CAN_CLR_INT_PENDING_BIT(base, boxno);
            if ((psNuCAN->int_flag & RT_DEVICE_FLAG_INT_TX) &&
                (psNuCAN->tx_pending & (1UL << boxno)))
            {
                psNuCAN->tx_pending &= ~(1UL << boxno);
                rt_hw_can_isr(&psNuCAN->dev, RT_CAN_EVENT_TX_DONE | (boxno << 8));
            }
        }
        else
        {
            if (psNuCAN->int_flag & RT_DEVICE_FLAG_INT_RX)
            {
                rt_hw_can_isr(&psNuCAN->dev, RT_CAN_EVENT_RX_IND | (boxno << 8));
            }
            CAN_CLR_INT_PENDING_BIT(base, boxno);
        }
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

/**
 * @brief Configure CAN hardware only after all accepted TX requests have retired.
 * @param can RT-Thread CAN device.
 * @param cfg Requested CAN bit timing and operating mode.
 * @return RT_EOK, -RT_EBUSY for in-flight TX, or a hardware configuration error.
 */
static rt_err_t nu_can_configure(struct rt_can_device *can, struct can_configure *cfg)
{
    nu_can_t psNuCAN = (nu_can_t)can;
    uint32_t u32CANMode;

    RT_ASSERT(can);
    RT_ASSERT(cfg);

    /* Get base address of CAN register */
    CAN_T *base = psNuCAN->base;

    /* Reinitialization must not erase a mailbox still owned by Generic. */
    if (psNuCAN->tx_pending != 0U)
    {
        return -RT_EBUSY;
    }

    /* Reset this module */
    nu_sys_ip_reset(psNuCAN->rstidx);

    u32CANMode = (cfg->mode == RT_CAN_MODE_NORMAL) ? CAN_NORMAL_MODE : CAN_BASIC_MODE;

    /*Set the CAN Bit Rate and Operating mode*/
    if (CAN_Open(base, cfg->baud_rate, u32CANMode) != cfg->baud_rate)
    {
        goto exit_nu_can_configure;
    }

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

/**
 * @brief Submit one classic CAN frame without waiting for a CAN IF transfer or a bus terminal.
 * @param can RT-Thread device whose Generic TX ownership is held by the caller.
 * @param buf CAN frame to submit.
 * @param boxno Physical message object (normal mode); only zero in BASIC mode.
 * @return RT_EOK if the hardware request is issued, -RT_EBUSY if unavailable,
 *         or -RT_ERROR/-RT_EINVAL for invalid input.
 */
static int nu_can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    /* Every IF data register is written even when the payload DLC is short. */
    STR_CANMSG_T tMsg = { 0 };
    const struct rt_can_msg *pmsg;
    nu_can_t psNuCAN = (nu_can_t)can;
    /* One controller owns the hardware message objects and their IF shadow. */
    CAN_T *base;
    /* A successful request retains this message object until the corresponding IRQ. */
    rt_uint32_t pending_bit;
    /* BASIC mode uses a single IF0 slot, unlike the normal message object bank. */
    rt_bool_t basic;

    RT_ASSERT(can);
    RT_ASSERT(buf);

    base = psNuCAN->base;
    pmsg = (const struct rt_can_msg *)buf;

    if (boxno >= can->config.sndboxnumber || boxno >= RX_MSG_ID_INDEX)
    {
        return -RT_EINVAL;
    }

    basic = ((base->CON & CAN_CON_TEST_Msk) != 0U) &&
            ((base->TEST & CAN_TEST_BASIC_Msk) != 0U);
    if (basic && boxno != 0U)
    {
        return -RT_EBUSY;
    }
    if (basic && (base->TEST & CAN_TEST_SILENT_Msk) != 0U &&
        (base->TEST & CAN_TEST_LBACK_Msk) == 0U)
    {
        return -RT_EBUSY;
    }

    pending_bit = 1UL << boxno;
    if ((psNuCAN->tx_pending & pending_bit) != 0U ||
        (base->IF[0].CREQ & CAN_IF_CREQ_BUSY_Msk) != 0U)
    {
        return -RT_EBUSY;
    }

    if (pmsg->ide == RT_CAN_STDID && IS_CAN_STDID(pmsg->id))
    {
        tMsg.IdType = CAN_STD_ID;
    }
    else if (pmsg->ide == RT_CAN_EXTID && IS_CAN_EXTID(pmsg->id))
    {
        tMsg.IdType = CAN_EXT_ID;
    }
    else
    {
        return -RT_ERROR;
    }
    tMsg.Id = pmsg->id;

    if (pmsg->rtr == RT_CAN_DTR)
    {
        tMsg.FrameType = CAN_DATA_FRAME;
    }
    else if (pmsg->rtr == RT_CAN_RTR)
    {
        tMsg.FrameType = CAN_REMOTE_FRAME;
    }
    else
    {
        return -RT_ERROR;
    }

    if (!IS_CAN_DLC(pmsg->len))
    {
        return -RT_ERROR;
    }
    tMsg.DLC = pmsg->len;
    if (tMsg.FrameType == CAN_DATA_FRAME && tMsg.DLC != 0U)
    {
        rt_memcpy(tMsg.Data, pmsg->data, tMsg.DLC);
    }

    /* Mirror the vendor frame encoding, but merge SetTxMsg and TriggerTxMsg
       into one IF write request (CMASK.TxRqst/NewDat) without their busy loops. */
    if (!basic)
    {
        base->IF[0].CMASK = CAN_IF_CMASK_WRRD_Msk | CAN_IF_CMASK_MASK_Msk |
                            CAN_IF_CMASK_ARB_Msk | CAN_IF_CMASK_CONTROL_Msk |
                            CAN_IF_CMASK_DATAA_Msk | CAN_IF_CMASK_DATAB_Msk |
                            CAN_IF_CMASK_TXRQSTNEWDAT_Msk;
    }

    if (tMsg.IdType == CAN_STD_ID)
    {
        base->IF[0].ARB1 = 0U;
        base->IF[0].ARB2 = ((tMsg.Id & 0x7FFU) << 2);
    }
    else
    {
        base->IF[0].ARB1 = tMsg.Id & 0xFFFFU;
        base->IF[0].ARB2 = ((tMsg.Id & 0x1FFF0000U) >> 16) | CAN_IF_ARB2_XTD_Msk;
    }
    if (!basic)
    {
        base->IF[0].ARB2 |= CAN_IF_ARB2_MSGVAL_Msk;
    }
    if (tMsg.FrameType == CAN_DATA_FRAME)
    {
        base->IF[0].ARB2 |= CAN_IF_ARB2_DIR_Msk;
    }
    else
    {
        base->IF[0].ARB2 &= ~CAN_IF_ARB2_DIR_Msk;
    }

    if (basic)
    {
        base->IF[0].MCON = (base->IF[0].MCON & ~CAN_IF_MCON_DLC_Msk) | tMsg.DLC;
    }
    else
    {
        base->IF[0].MCON = CAN_IF_MCON_NEWDAT_Msk | tMsg.DLC |
                           CAN_IF_MCON_TXIE_Msk | CAN_IF_MCON_EOB_Msk;
    }
    base->IF[0].DAT_A1 = ((uint32_t)tMsg.Data[1] << 8) | tMsg.Data[0];
    base->IF[0].DAT_A2 = ((uint32_t)tMsg.Data[3] << 8) | tMsg.Data[2];
    base->IF[0].DAT_B1 = ((uint32_t)tMsg.Data[5] << 8) | tMsg.Data[4];
    base->IF[0].DAT_B2 = ((uint32_t)tMsg.Data[7] << 8) | tMsg.Data[6];

    base->STATUS &= ~CAN_STATUS_TXOK_Msk;
    if (basic)
    {
        base->IF[0].CREQ |= CAN_IF_CREQ_BUSY_Msk;
    }
    else
    {
        base->IF[0].CREQ = MSG(boxno) + 1U;
    }
    psNuCAN->tx_pending |= pending_bit;
    return RT_EOK;
}

/**
 * @brief Submit through an available physical message object without sleeping.
 * @param can RT-Thread CAN device.
 * @param buf CAN frame to submit.
 * @param mailbox Receives the physical message object index only on success.
 * @return RT_EOK on acceptance, -RT_EBUSY if none available, or an input error.
 */
static rt_ssize_t nu_can_sendmsg_nonblocking(struct rt_can_device *can, const void *buf, rt_uint32_t *mailbox)
{
    /* Generic reports the selected message object in TX_DONE/TX_FAIL events. */
    rt_uint32_t boxno;
    /* Preserve invalid input errors instead of reporting mailbox exhaustion. */
    rt_ssize_t result;

    RT_ASSERT(can);
    RT_ASSERT(buf);
    RT_ASSERT(mailbox);

    for (boxno = 0; boxno < can->config.sndboxnumber; boxno++)
    {
        result = nu_can_sendmsg(can, buf, boxno);
        if (result == RT_EOK)
        {
            *mailbox = boxno;
            return RT_EOK;
        }
        if (result != -RT_EBUSY)
        {
            return result;
        }
    }
    return -RT_EBUSY;
}

/**
 * @brief Read one classic CAN frame and map its hardware RX filter if present.
 * @param can RT-Thread CAN device.
 * @param buf Output CAN message.
 * @param boxno Hardware RX message object or BASIC-mode zero.
 * @return RT_EOK on valid RX data, or a negative hardware read error.
 */
static int nu_can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    STR_CANMSG_T tMsg;
    struct rt_can_msg *pmsg;
    nu_can_t psNuCAN = (nu_can_t)can;

    RT_ASSERT(can);
    RT_ASSERT(buf);

    pmsg = (struct rt_can_msg *)buf;

    /* get data */
    if (CAN_Receive(psNuCAN->base, boxno, &tMsg) == FALSE)
    {
        rt_kprintf("No available RX Msg.\n");
        return -(RT_ERROR);
    }

#ifdef RT_CAN_USING_HDR
    /* BASIC RX is not associated with a hardware message-object filter. */
    if ((psNuCAN->base->CON & CAN_CON_TEST_Msk) != 0U &&
        (psNuCAN->base->TEST & CAN_TEST_BASIC_Msk) != 0U)
    {
        pmsg->hdr_index = -1;
    }
    else
    {
        pmsg->hdr_index = boxno - RX_MSG_ID_INDEX;
        can->hdr[pmsg->hdr_index].connected = 1;
    }
#endif

    pmsg->ide = (tMsg.IdType == CAN_STD_ID) ? RT_CAN_STDID : RT_CAN_EXTID;
    pmsg->rtr = (tMsg.FrameType == CAN_DATA_FRAME) ? RT_CAN_DTR : RT_CAN_RTR;
    pmsg->id = tMsg.Id;
    pmsg->len = tMsg.DLC;
    if (pmsg->len > sizeof(tMsg.Data))
    {
        pmsg->len = sizeof(tMsg.Data);
    }

    if (pmsg->data && pmsg->len)
    {
        rt_memcpy(pmsg->data, &tMsg.Data[0], pmsg->len);
    }

    return RT_EOK;
}

/**
 * @brief Register CAN controllers with physically valid Generic TX capacities.
 * @return Result of CAN device registration.
 */
static int rt_hw_can_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (CAN_START + 1); i < CAN_CNT; i++)
    {
        nu_can_arr[i].dev.config = nu_can_default_config;
#ifdef RT_CAN_USING_HDR
        /* Object indices [0, RX_MSG_ID_INDEX) are reserved for TX. */
        if (nu_can_arr[i].dev.config.sndboxnumber > RX_MSG_ID_INDEX)
        {
            nu_can_arr[i].dev.config.sndboxnumber = RX_MSG_ID_INDEX;
        }
#else
        /* When hardware filtering is disabled the BSP uses BASIC mode. */
        nu_can_arr[i].dev.config.sndboxnumber = 1U;
#endif /* RT_CAN_USING_HDR */

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
#endif //#if defined(BSP_USING_CAN)
