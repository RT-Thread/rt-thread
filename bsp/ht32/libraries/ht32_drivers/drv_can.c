/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-22     QT-one       first version
 */

#include <rtdbg.h>
#include "drv_can.h"
#include "ht32_can_config.h"

#ifdef BSP_USING_CAN
#if !defined(BSP_USING_CAN)
    #error "Please define at least one BSP_USING_CAN"
#endif

#define CAN_UMASK_MODE      0
#define CAN_MASK_MODE       1

struct ht32_can_msg_type
{
    CAN_MSG_TypeDef cfg_msg;
    uint32_t data_len;
    uint8_t data[8];
};

/* Baud rate mapping structure */
struct ht32_baud_rate
{
    enum CANBAUD rt_baud_rate;
    uint32_t us_baus_rate;
};
/* CAN Filter Table Configuration Structure */
struct ht32_can_filter_config
{
    /* Each bit represents a message;1: the message is occupied;0: the message is not occupied */
    uint32_t filter_flag;
    /* Filter table configuration information */
    CAN_MSG_TypeDef filter_mag[MSG_OBJ_TOTAL_NUM];
};
/* CAN Object Structures */
struct ht32_can
{
    char *name;                                 /* Equipment name */
    HT_CAN_TypeDef *can_x;                      /* peripheral base address */
    struct can_configure cfg;                   /* CAN Configuration Structure */
    struct rt_can_device device;                /* Inherited device options */
    struct ht32_can_filter_config filter_cfg;   /* Filter Table Configuration */
};
/* CAN Baud Rate Mapping Table */
static const struct ht32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud, 1000000},
    {CAN800kBaud, 800000},
    {CAN500kBaud, 500000},
    {CAN250kBaud, 250000},
    {CAN125kBaud, 125000},
    {CAN100kBaud, 100000},
    {CAN50kBaud, 50000},
    {CAN20kBaud, 20000},
    {CAN10kBaud, 10000},
};
/* CAN Object Information */
static struct ht32_can ht32_can_config =
{
    .name           = BSP_USING_CAN_NAME,
    .can_x          = HT_CAN0,
    .cfg            = {0},
    .device         = RT_NULL,
    .filter_cfg     = {0},
};
/**
  * @brief Default Filter Table Configuration
  * @param can_instance:CAN object
  * @retval
  */
static rt_uint32_t cfg_can_default_filter(struct ht32_can *can_instance)
{
    uint8_t filter_num = BSP_USING_CAN_MSG_NUM;
    can_instance->filter_cfg.filter_flag |= 1 << filter_num;
    can_instance->filter_cfg.filter_mag[filter_num].MsgNum = filter_num + 1;
    can_instance->filter_cfg.filter_mag[filter_num].IdType = (CAN_IdType_Enum)BSP_USING_CAN_ID_MODE;
    can_instance->filter_cfg.filter_mag[filter_num].IdMask = BSP_USING_CAN_MASK;
    can_instance->filter_cfg.filter_mag[filter_num].FrameType = (CAN_FrameType_Enum)BSP_USING_CAN_FRAME_MODE;
    can_instance->filter_cfg.filter_mag[filter_num].Id = BSP_USING_CAN_ID;
    CAN_SetRxMsg(can_instance->can_x, &can_instance->filter_cfg.filter_mag[filter_num], 1);
    return RT_EOK;
}
/**
  * @brief Get baud rate mapping parameters for CAN
  * @info This function is mainly used to convert the baud rate of RTT format to HT32 format baud rate
  * @param baud:CAN baud rate in RTT format
  * @retval Returns the CAN baud rate in HT32 format.
  */
static rt_uint32_t get_can_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index;

    len = sizeof(can_baud_rate_tab) / sizeof(can_baud_rate_tab[0]);
    for (index = 0; index < len; index++)
    {
        if (can_baud_rate_tab[index].rt_baud_rate == baud)
            return can_baud_rate_tab[index].us_baus_rate;
    }
    return 0;
}
/**
  * @brief Configuring CAN Structures
  * @info This function depends on the ht32_can_config.h file
  * @param can_ck:System clock for CAN
  * @param can_buad:CAN baud rate to be configured
  * @param mode:Modes of CAN
  * @param nart:enable or disable the no automatic retransmission
  * @param CAN_InitStruct:Structures to be configured
  * @retval 1:success;0:error
  */
static rt_uint32_t config_can_struct(uint32_t can_ck,
                                     uint32_t can_buad,
                                     uint8_t mode,
                                     ControlStatus nart,
                                     CAN_InitTypeDef* CAN_InitStruct)
{
    uint8_t cf0_nbt = 0;
    uint32_t nominal_bit_time = 0;

    for (cf0_nbt = 25; cf0_nbt > 8; cf0_nbt--)
    {
        if ((can_ck / can_buad / cf0_nbt) > 0)
        {
            if (((can_ck / (can_ck / can_buad / cf0_nbt)) / cf0_nbt) <= can_buad)
            {
                nominal_bit_time = cf0_nbt;
                break;
            }
        }
    }
    if (cf0_nbt < 8)
    {
        return 0;
    }
    CAN_InitStruct->CAN_BRPrescaler     = (can_ck / (can_buad * nominal_bit_time));
    CAN_InitStruct->CAN_SJW             = HTCFG_CAN_CF0_BIT_TIME_SJW;
    CAN_InitStruct->CAN_TSEG1           = (nominal_bit_time - (nominal_bit_time * HTCFG_CAN_CF0_SAMPLE_POINT) / 100);
    CAN_InitStruct->CAN_TSEG0           = (nominal_bit_time - 1 - CAN_InitStruct->CAN_TSEG1);
    CAN_InitStruct->CAN_NART            = nart;
    CAN_InitStruct->CAN_Mode            = mode;
    return 1;
}
/**
  * @brief CAN Configuration Functions
  * @param
  * @retval
  */
static rt_err_t ht32_can_configure(struct rt_can_device *can, struct can_configure *cfg)
{
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    struct ht32_can *can_instance = RT_NULL;
    rt_uint32_t can_baud = 0;
    rt_uint8_t can_mode = 0;
    CAN_InitTypeDef CAN_InitStruct = {0};

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    can_instance = (struct ht32_can *)can->parent.user_data;
    RT_ASSERT(can_instance != RT_NULL);

    CKCUClock.Bit.AFIO             = 1;
    CKCUClock.Bit.CAN0             = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    ht32_can_gpio_init(can_instance->can_x);

    /* Get baud rate */
    can_baud = get_can_baud_index(cfg->baud_rate);
    if (can_baud == 0)
    {
        return -RT_ERROR;
    }

    can_instance->cfg.baud_rate = cfg->baud_rate;
    can_instance->cfg.mode = cfg->mode;

    /* Configuring the operating mode of CAN */
    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        can_mode = CAN_MODE_NORMAL;
        break;
    case RT_CAN_MODE_LISTEN:
        can_mode = CAN_MODE_SILENT;
        break;
    case RT_CAN_MODE_LOOPBACK:
        can_mode = CAN_MODE_LBACK;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        can_mode = CAN_MODE_SILENT | CAN_MODE_LBACK;
        break;
    default:
        return -RT_ERROR;
    }

    if (0 == (config_can_struct(_HTCFG_CF0_CK_CAN, can_baud, can_mode, DISABLE, &CAN_InitStruct)))
    {
        return -RT_ERROR;
    }
    /* Reset CAN */
    CAN_DeInit(can_instance->can_x);
    /* Initialising CAN */
    CAN_Init(can_instance->can_x, &CAN_InitStruct);

    /* Configuring the Default Filter for CAN */
    cfg_can_default_filter(can_instance);

    return RT_EOK;
}
/**
  * @brief CAN Control Functions
  * @param
  * @retval
  */
rt_err_t ht32_can_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval;
    struct ht32_can *can_instance;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can != RT_NULL);
    can_instance = (struct ht32_can *)can->parent.user_data;
    RT_ASSERT(can_instance != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:/* Clear Interrupt */
    {
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)        /* receive interruptions */
        {
            if (CAN_GetFlagStatus(can_instance->can_x, CAN_FLAG_RXOK))
            {
                /* Clear RXOK Flag */
                CAN_ClearFlag(can_instance->can_x, CAN_FLAG_RXOK);
            }
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)   /* Send Interrupt */
        {
            if (CAN_GetFlagStatus(can_instance->can_x, CAN_FLAG_TXOK))
            {
                /* Clear TXOK flag*/
                CAN_ClearFlag(can_instance->can_x, CAN_FLAG_TXOK);
            }
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)   /* false interruption */
        {
            /* Error Process*/
            CAN_LastErrorCode_TypeDef lec = CAN_GetLastErrorCode(can_instance->can_x);
            if (lec != NO_ERROR)
            {
                LOG_W("LEC: %d\r\n", lec);
            }
            if (CAN_GetFlagStatus(can_instance->can_x, CAN_FLAG_BOFF))
            {
                /* Recover from Bus off state.*/
                CAN_BusOffRecovery(can_instance->can_x);
            }
        }
        break;
    }
    case RT_DEVICE_CTRL_SET_INT:/* Setting Up Interruptions */
    {
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)        /* interrupt receive mode */
        {
            LOG_W("Configuring Receive Interrupts!\r\n");
            CAN_IntConfig(can_instance->can_x, CAN_INT_EIE | CAN_INT_SIE | CAN_INT_IE, ENABLE);
            NVIC_EnableIRQ(CAN0_IRQn);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)   /* interrupt transmission mode */
        {
            LOG_W("Configuring Transmit Interrupts!\r\n");
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)   /* false interruption */
        {
            LOG_W("Configuration error interrupt!\r\n");
        }
        break;
    }
    case RT_CAN_CMD_SET_FILTER:/* Configuring the Hardware Filter Table */
    {
        int i = 0;
        uint8_t filter_num = 0;
        uint32_t idmask = 0;
        if (RT_NULL == arg)
        {
            /* default filter config */
            cfg_can_default_filter(can_instance);
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            if (filter_cfg->count > MSG_OBJ_TOTAL_NUM)
            {
                LOG_W("Filter list length exceeds the limit(max 32)!");
                return -RT_ERROR;
            }
            for (i = 0; i < filter_cfg->count; i++)
            {
                /* Specify the filter table number or no */
                if (filter_cfg->items[i].hdr_bank == -1)
                {
                    filter_num = i;
                }
                else
                {
                    if (filter_cfg->items[i].hdr_bank > MSG_OBJ_TOTAL_NUM)
                    {
                        LOG_W("Filter List Number Out of Limits(1-32)!");
                        return -RT_ERROR;
                    }
                    else
                    {
                        filter_num = filter_cfg->items[i].hdr_bank;
                    }
                }
                if (can_instance->filter_cfg.filter_flag & (1 << filter_num))
                {
                    LOG_W("This filter channel will be changed(num:%d)!", filter_num);
                    rt_kprintf("This filter channel will be changed(num:%d)!", filter_num);
                }
                can_instance->filter_cfg.filter_flag |= 1 << filter_num;
                can_instance->filter_cfg.filter_mag[filter_num].MsgNum = filter_num + 1;

                /* Standard or Extended Frames */
                if (filter_cfg->items[i].ide == RT_CAN_STDID)
                {
                    can_instance->filter_cfg.filter_mag[filter_num].IdType = CAN_STD_ID;
                    idmask = 0x7FF;
                }
                else if (filter_cfg->items[i].ide == RT_CAN_EXTID)
                {
                    can_instance->filter_cfg.filter_mag[filter_num].IdType = CAN_EXT_ID;
                    idmask = 0x1FFFFFFF;
                }
                else
                {
                    LOG_W("Frame pattern error(CAN_STD_ID/CAN_EXT_ID)!");
                    return -RT_ERROR;
                }
                /* Whether to use MASK mode */
                if (filter_cfg->items[i].mode == CAN_UMASK_MODE)
                {
                    can_instance->filter_cfg.filter_mag[filter_num].IdMask = idmask;
                }
                else if (filter_cfg->items[i].mode == CAN_MASK_MODE)
                {
                    can_instance->filter_cfg.filter_mag[filter_num].IdMask = filter_cfg->items[i].mask;
                }
                else
                {
                    LOG_W("MASK mode error(CAN_UMASK_MODE/CAN_MASK_MODE)!");
                    return -RT_ERROR;
                }

                /* Remote frames or data frames */
                if (filter_cfg->items[i].rtr == RT_CAN_RTR)
                {
                    can_instance->filter_cfg.filter_mag[filter_num].FrameType = CAN_REMOTE_FRAME;
                }
                else if (filter_cfg->items[i].rtr == RT_CAN_DTR)
                {
                    can_instance->filter_cfg.filter_mag[filter_num].FrameType = CAN_DATA_FRAME;
                }
                /* Setting ID */
                can_instance->filter_cfg.filter_mag[filter_num].Id = filter_cfg->items[i].id;
                /* Setting up the CAN filter table */
                CAN_SetRxMsg(can_instance->can_x, &can_instance->filter_cfg.filter_mag[filter_num], 1);
            }
        }
        break;
    }
    case RT_CAN_CMD_SET_BAUD:/* Setting the baud rate */
    {
        argval = (rt_uint32_t) arg;
        if (argval != CAN1MBaud   &&
                argval != CAN800kBaud &&
                argval != CAN500kBaud &&
                argval != CAN250kBaud &&
                argval != CAN125kBaud &&
                argval != CAN100kBaud &&
                argval != CAN50kBaud  &&
                argval != CAN20kBaud  &&
                argval != CAN10kBaud)
        {
            return -RT_ERROR;
        }
        if (argval != can_instance->cfg.baud_rate)
        {
            can_instance->cfg.baud_rate = argval;
            return ht32_can_configure(&can_instance->device, &can_instance->cfg);
        }
        break;
    }
    case RT_CAN_CMD_SET_MODE:/* Setting the CAN Operating Mode */
    {
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL &&
                argval != RT_CAN_MODE_LISTEN &&
                argval != RT_CAN_MODE_LOOPBACK &&
                argval != RT_CAN_MODE_LOOPBACKANLISTEN)
        {
            return -RT_ERROR;
        }
        if (argval != can_instance->cfg.mode)
        {
            can_instance->cfg.mode = argval;
            return ht32_can_configure(&can_instance->device, &can_instance->cfg);
        }
        break;
    }
    case RT_CAN_CMD_GET_STATUS:/* Get CAN device status */
    {
        rt_uint32_t errtype;

        errtype = can_instance->can_x->ECR;
        can_instance->device.status.rcverrcnt    = ((errtype >> 8) & 0x7f);
        can_instance->device.status.snderrcnt    = (errtype & 0xff);

        errtype = can_instance->can_x->SR;
        can_instance->device.status.lasterrtype  = (errtype & 0x07);
        can_instance->device.status.errcode      = ((errtype >> 5) & 0x07);

        rt_memcpy(arg, &can_instance->device.status, sizeof(can_instance->device.status));
        break;
    }
    default:
        return -RT_ERROR;
    }
    return RT_EOK;
}
/**
  * @brief CAN sends data
  * @param
  * @retval
  */
rt_ssize_t ht32_can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    struct ht32_can *can_instance = RT_NULL;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    struct ht32_can_msg_type tx_msg = {0};

    RT_ASSERT(can != RT_NULL);
    can_instance = (struct ht32_can *)can->parent.user_data;
    RT_ASSERT(can_instance != RT_NULL);

    /* Standard and Extended Frames */
    if (CAN_STD_ID == pmsg->ide)
    {
        tx_msg.cfg_msg.IdType = CAN_STD_ID;
        tx_msg.cfg_msg.Id = pmsg->id;
    }
    else if (CAN_EXT_ID == pmsg->ide)
    {
        tx_msg.cfg_msg.IdType = CAN_EXT_ID;
        tx_msg.cfg_msg.Id = pmsg->id;
    }
    else
    {
        LOG_W("Frame pattern error(CAN_STD_ID/CAN_EXT_ID)!");
        return -RT_ERROR;
    }

    /* Teleframes and data frames */
    if (RT_CAN_RTR == pmsg->rtr)
    {
        tx_msg.cfg_msg.FrameType = CAN_REMOTE_FRAME;
    }
    else if (RT_CAN_DTR == pmsg->rtr)
    {
        tx_msg.cfg_msg.FrameType = CAN_DATA_FRAME;
    }
    else
    {
        LOG_W("Remote frame setting error(CAN_REMOTE_FRAME/CAN_DATA_FRAME)!");
        return -RT_ERROR;
    }

    /* Length of sent data */
    tx_msg.data_len = pmsg->len & 0x0FU;
    /* data being sent */
    tx_msg.data[0] = pmsg->data[0];
    tx_msg.data[1] = pmsg->data[1];
    tx_msg.data[2] = pmsg->data[2];
    tx_msg.data[3] = pmsg->data[3];
    tx_msg.data[4] = pmsg->data[4];
    tx_msg.data[5] = pmsg->data[5];
    tx_msg.data[6] = pmsg->data[6];
    tx_msg.data[7] = pmsg->data[7];

    /* Waiting tx Msg idle */
    while (CAN_TransmitStatus(can_instance->can_x, &tx_msg.cfg_msg) == 0);
    /* Loopback data */
    CAN_Transmit(can_instance->can_x, &tx_msg.cfg_msg, tx_msg.data, tx_msg.data_len);

    return RT_EOK;
}
/**
  * @brief CAN receive data
  * @param
  * @retval
  */
rt_ssize_t ht32_can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    uint8_t i = 0;
    uint32_t msgnum = 0;
    CAN_RxStatus_TypeDef rx_status;
    struct ht32_can_msg_type rx_msg = {0};
    struct ht32_can *can_instance = RT_NULL;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(pmsg != RT_NULL);
    can_instance = (struct ht32_can *)can->parent.user_data;
    RT_ASSERT(can_instance != RT_NULL);

    msgnum = can_instance->filter_cfg.filter_flag;
    for (i = 0; i < MSG_OBJ_TOTAL_NUM; i++)
    {
        if ((msgnum & 1) == 1)
        {
            rx_status = CAN_Receive(can_instance->can_x, &can_instance->filter_cfg.filter_mag[i], rx_msg.data, &rx_msg.data_len);
            if (rx_status == MSG_OVER_RUN)
            {
                LOG_W("ID[%X] rx message over run\r\n", can_instance->filter_cfg.filter_mag[i].Id);
            }
            else if (rx_status == MSG_OBJ_NOT_SET)
            {
                LOG_W("rx message not set  \r\n");
            }
            else if (rx_status == MSG_RX_FINISH)
            {
                LOG_W("rx ok \r\n");
                pmsg->data[0] = rx_msg.data[0];
                pmsg->data[1] = rx_msg.data[1];
                pmsg->data[2] = rx_msg.data[2];
                pmsg->data[3] = rx_msg.data[3];
                pmsg->data[4] = rx_msg.data[4];
                pmsg->data[5] = rx_msg.data[5];
                pmsg->data[6] = rx_msg.data[6];
                pmsg->data[7] = rx_msg.data[7];
                pmsg->len = rx_msg.data_len;

                if (can_instance->filter_cfg.filter_mag[i].IdType == CAN_EXT_ID)
                {
                    pmsg->id = can_instance->filter_cfg.filter_mag[i].Id;
                    pmsg->ide = RT_CAN_EXTID;
                }
                else if (can_instance->filter_cfg.filter_mag[i].IdType == CAN_STD_ID)
                {
                    pmsg->id = can_instance->filter_cfg.filter_mag[i].Id;
                    pmsg->ide = RT_CAN_EXTID;
                }

                if (can_instance->filter_cfg.filter_mag[i].FrameType == CAN_DATA_FRAME)
                {
                    pmsg->rtr = RT_CAN_DTR;
                }
                else if (can_instance->filter_cfg.filter_mag[i].FrameType == CAN_REMOTE_FRAME)
                {
                    pmsg->rtr = RT_CAN_RTR;
                }
                return RT_EOK;
            }
        }
        msgnum = msgnum >> 1;
        if (msgnum == 0)
        {
            return -1;
        }
    }
    return -1;
}
/* Mapping CAN interfaces */
static const struct rt_can_ops ht32_can_ops =
{
    .configure          = ht32_can_configure,       /* CAN Configuration Functions */
    .control            = ht32_can_control,         /* CAN Control Functions */
    .sendmsg            = ht32_can_sendmsg,         /* CAN Transmit Data */
    .recvmsg            = ht32_can_recvmsg,         /* CAN Receive Data */
};

int rt_hw_can_init(void)
{

    struct can_configure config = CANDEFAULTCONFIG;
    config.mode = BSP_USING_CAN_MODE;
    config.baud_rate = BSP_USING_CAN_BAUD;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;

#ifdef RT_CAN_USING_HDR
    config.maxhdr = 14;
#endif
    ht32_can_config.device.config = config;
    /* Registration of CAN devices */
    rt_hw_can_register(&ht32_can_config.device,
                       ht32_can_config.name,
                       &ht32_can_ops,
                       &ht32_can_config);
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_can_init);

void CAN0_IRQHandler(void)
{
    CAN_LastErrorCode_TypeDef lec;
    rt_interrupt_enter();
    /* Recover from Bus off state. */
    if (CAN_GetFlagStatus(ht32_can_config.can_x, CAN_FLAG_BOFF))
    {
        CAN_BusOffRecovery(ht32_can_config.can_x);
    }
    /* Transmit message finished */
    if (CAN_GetFlagStatus(ht32_can_config.can_x, CAN_FLAG_TXOK))
    {
        rt_hw_can_isr(&ht32_can_config.device, RT_CAN_EVENT_TX_DONE);
        CAN_ClearFlag(ht32_can_config.can_x, CAN_FLAG_TXOK);
    }
    /* Message received. */
    if (CAN_GetFlagStatus(ht32_can_config.can_x, CAN_FLAG_RXOK))
    {
        /* Clear all message objects' interrupt pending flag */
        CAN_ClearAllMsgPendingFlag(ht32_can_config.can_x);
        rt_hw_can_isr(&ht32_can_config.device, RT_CAN_EVENT_RX_IND);
        CAN_ClearFlag(ht32_can_config.can_x, CAN_FLAG_RXOK);
    }
    lec = CAN_GetLastErrorCode(ht32_can_config.can_x);
    if (lec != NO_ERROR)
    {
        switch (lec)
        {
        case NO_ERROR:
            break;
        case STUFF_ERROR:
            ht32_can_config.device.status.bitpaderrcnt++;
            break;
        case FORM_ERROR:
            ht32_can_config.device.status.formaterrcnt++;
            break;
        case ACK_ERROR:
            ht32_can_config.device.status.ackerrcnt++;
            break;
        case BIT1_EROR:
        case BIT0_ERROR:
            ht32_can_config.device.status.biterrcnt++;
            break;
        case CRC_ERROR:
            ht32_can_config.device.status.crcerrcnt++;
            break;
        case NO_CHANGE:
            break;
        }
        ht32_can_config.device.status.lasterrtype = lec;
        ht32_can_config.device.status.rcverrcnt = CAN_GetReceiveErrorCounter(ht32_can_config.can_x);
        ht32_can_config.device.status.snderrcnt = CAN_GetLSBTransmitErrorCounter(ht32_can_config.can_x);
        ht32_can_config.device.status.errcode = lec;
    }

    rt_interrupt_leave();
}

#endif /* BSP_USING_CAN */
