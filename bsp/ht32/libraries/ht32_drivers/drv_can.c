/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-22     QT-one       first version
 * 2026-11-12     wdfk-prog    Adapt CAN driver to Generic CAN framework
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
/** @brief Physical CAN Message Object 32 reserved exclusively for Generic TX slot 0. */
#define HT32_CAN_TX_MSG_NUM MSG_OBJ_TOTAL_NUM
/** @brief Bit 15 of the upper 16-bit object registers (IPR1/TRR1/NDR1), for object 32. */
#define HT32_CAN_TX_MSG_BIT (1UL << 15)
/** @brief Maximum number of individual RX objects; object 32 is reserved for TX. */
#define HT32_CAN_RX_MSG_NUM (MSG_OBJ_TOTAL_NUM - 1U)

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
    .device         = {0},
    .filter_cfg     = {0},
};
/**
 * @brief Enable or disable one Message Object IRQ without changing its filter or data.
 * The caller must mask CAN0 NVIC because the ISR shares the IF registers.
 * @param can_x HT32 CAN controller registers.
 * @param msg_num Physical Message Object number, 1 through 32.
 * @param irq_bit Message control bit, CAN_IF_MCR_RXIE or CAN_IF_MCR_TXIE.
 * @param enable Enable the selected object interrupt when true.
 */
static void ht32_can_set_msg_irq(HT_CAN_TypeDef *can_x, rt_uint32_t msg_num,
                                 rt_uint32_t irq_bit, rt_bool_t enable)
{
    /* IF0 and IF1 can still be committing SDK Message RAM transfers. */
    HT_CANIF_TypeDef *ifx = &can_x->IF0;

    while ((can_x->IF0.CREQ & CAN_FLAG_IF_BUSY) != 0U ||
           (can_x->IF1.CREQ & CAN_FLAG_IF_BUSY) != 0U)
    {
    }
    /* Read only the control word, then write it back without clearing pending data. */
    ifx->CMASK = CAN_IF_CMASK_CONTROL;
    ifx->CREQ = msg_num;
    while ((ifx->CREQ & CAN_FLAG_IF_BUSY) != 0U)
    {
    }
    if (enable)
    {
        ifx->MCR |= irq_bit;
    }
    else
    {
        ifx->MCR &= ~irq_bit;
    }
    ifx->CMASK = CAN_IF_CMASK_WRRD | CAN_IF_CMASK_CONTROL;
    ifx->CREQ = msg_num;
    while ((ifx->CREQ & CAN_FLAG_IF_BUSY) != 0U)
    {
    }
}

/**
 * @brief Program a receive object and keep its IRQ masked while Generic RX is paused.
 * @param can_instance HT32 controller and Generic CAN device state.
 * @param rx_msg Saved receive filter descriptor to program.
 * @return RT_EOK when the SDK accepts the receive filter, or -RT_ERROR otherwise.
 */
static rt_err_t ht32_can_program_rx_filter(struct ht32_can *can_instance, CAN_MSG_TypeDef *rx_msg)
{
    /* Save the existing CAN0 NVIC state; the SDK always sets RXIE on programming. */
    rt_uint32_t nvic_enabled = NVIC_GetEnableIRQ(CAN0_IRQn);
    /* Result of programming the selected receive Message Object. */
    rt_err_t result = RT_EOK;

    NVIC_DisableIRQ(CAN0_IRQn);
    if (CAN_SetRxMsg(can_instance->can_x, rx_msg, 0) != SUCCESS)
    {
        result = -RT_ERROR;
    }
    else if ((can_instance->device.parent.open_flag & RT_DEVICE_FLAG_INT_RX) == 0U)
    {
        ht32_can_set_msg_irq(can_instance->can_x, rx_msg->MsgNum,
                             CAN_IF_MCR_RXIE, RT_FALSE);
    }
    if (nvic_enabled != 0U)
    {
        NVIC_EnableIRQ(CAN0_IRQn);
    }
    return result;
}

/**
 * @brief Program the default receive filter without occupying the reserved TX object.
 * Leave its RX interrupt masked until Generic resumes RX admission.
 * @param can_instance HT32 controller and RX-filter metadata.
 * @return RT_EOK when programmed, -RT_EINVAL for a reserved filter bank, or -RT_ERROR on SDK failure.
 */
static rt_err_t cfg_can_default_filter(struct ht32_can *can_instance)
{
    uint8_t filter_num = BSP_USING_CAN_MSG_NUM;
    if (filter_num >= HT32_CAN_RX_MSG_NUM)
    {
        return -RT_EINVAL;
    }
    can_instance->filter_cfg.filter_flag |= 1UL << filter_num;
    can_instance->filter_cfg.filter_mag[filter_num].MsgNum = filter_num + 1;
    can_instance->filter_cfg.filter_mag[filter_num].IdType = (CAN_IdType_Enum)BSP_USING_CAN_ID_MODE;
    can_instance->filter_cfg.filter_mag[filter_num].IdMask = BSP_USING_CAN_MASK;
    can_instance->filter_cfg.filter_mag[filter_num].FrameType = (CAN_FrameType_Enum)BSP_USING_CAN_FRAME_MODE;
    can_instance->filter_cfg.filter_mag[filter_num].Id = BSP_USING_CAN_ID;
    /* This SDK programs FifoDepth + 1 objects; zero selects only this RX object. */
    return ht32_can_program_rx_filter(can_instance, &can_instance->filter_cfg.filter_mag[filter_num]);
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
 * @brief Configure HT32 CAN while no TX request is owned by Generic CAN.
 * Reapply stored RX filters after reset, preserving Generic's RX interrupt pause.
 * @param can RT-Thread CAN device.
 * @param cfg Requested CAN bitrate, operating mode and hardware TX slot count.
 * @return RT_EOK on success or a negative configuration/SDK error.
 */
static rt_err_t ht32_can_configure(struct rt_can_device *can, struct can_configure *cfg)
{
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    struct ht32_can *can_instance = RT_NULL;
    rt_uint32_t can_baud = 0;
    rt_uint8_t can_mode = 0;
    /* Hardware error-interrupt bits retained across the local CAN controller reset. */
    rt_uint32_t error_irqs;
    /* Saved receive-filter bank iterator. */
    rt_uint32_t i;
    CAN_InitTypeDef CAN_InitStruct = {0};

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    if (cfg->sndboxnumber != 1U || BSP_USING_CAN_MSG_NUM >= HT32_CAN_RX_MSG_NUM)
    {
        return -RT_EINVAL;
    }
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
    /* RX/TX admission is held by Generic; error-source selection lives in hardware. */
    error_irqs = can_instance->can_x->CR & (CAN_INT_EIE | CAN_INT_SIE);
    /* Reset CAN only after Generic has drained TX and paused RX. */
    NVIC_DisableIRQ(CAN0_IRQn);
    CAN_DeInit(can_instance->can_x);
    CAN_Init(can_instance->can_x, &CAN_InitStruct);
    if (can_instance->filter_cfg.filter_flag == 0U)
    {
        if (cfg_can_default_filter(can_instance) != RT_EOK)
        {
            return -RT_ERROR;
        }
    }
    else
    {
        /* Rebuild every previously configured object; the SDK resets Message RAM. */
        for (i = 0; i < HT32_CAN_RX_MSG_NUM; i++)
        {
            if ((can_instance->filter_cfg.filter_flag & (1UL << i)) == 0U)
            {
                continue;
            }
            if (ht32_can_program_rx_filter(can_instance, &can_instance->filter_cfg.filter_mag[i]) != RT_EOK)
            {
                return -RT_ERROR;
            }
        }
    }

    /* Restore error IRQ hardware policy and Generic RX/TX admission after reset. */
    can_instance->can_x->CR &= ~CAN_INT_ALL;
    can_instance->can_x->CR |= error_irqs;
    NVIC_ClearPendingIRQ(CAN0_IRQn);
    if (error_irqs != 0U ||
        (can->parent.open_flag & (RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX)) != 0U)
    {
        can_instance->can_x->CR |= CAN_INT_IE;
        NVIC_EnableIRQ(CAN0_IRQn);
    }
    /* A failed hardware reconfiguration must not overwrite the last applied settings. */
    can_instance->cfg = *cfg;
    return RT_EOK;
}
/**
 * @brief Apply HT32 CAN interrupt, filter, controller and status operations.
 * RX/TX interrupt control updates each Message Object without changing filters.
 * @param can RT-Thread CAN device.
 * @param cmd Generic CAN control operation.
 * @param arg Command-specific integer value or pointer.
 * @return RT_EOK on success; -RT_ENOSYS for unsupported abort; a negative error otherwise.
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
    case RT_DEVICE_CTRL_CLR_INT:
    case RT_DEVICE_CTRL_SET_INT:
    {
        /* RX filter-bank iterator; only configured objects are modified. */
        rt_uint32_t i;
        argval = (rt_uint32_t)(rt_ubase_t)arg;
        if (argval != RT_DEVICE_FLAG_INT_RX &&
            argval != RT_DEVICE_FLAG_INT_TX &&
            argval != RT_DEVICE_CAN_INT_ERR)
        {
            return -RT_EINVAL;
        }
        /* CAN_INT_IE is shared by RX, TX and error sources; avoid CAN_IntConfig()
         * entering controller INIT mode while a frame is being transmitted. */
        NVIC_DisableIRQ(CAN0_IRQn);
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            for (i = 0; i < HT32_CAN_RX_MSG_NUM; i++)
            {
                if ((can_instance->filter_cfg.filter_flag & (1UL << i)) != 0U)
                {
                    ht32_can_set_msg_irq(can_instance->can_x, i + 1U,
                                         CAN_IF_MCR_RXIE, cmd == RT_DEVICE_CTRL_SET_INT);
                }
            }
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            ht32_can_set_msg_irq(can_instance->can_x, HT32_CAN_TX_MSG_NUM,
                                 CAN_IF_MCR_TXIE, cmd == RT_DEVICE_CTRL_SET_INT);
        }
        else if (cmd == RT_DEVICE_CTRL_SET_INT)
        {
            can_instance->can_x->CR |= CAN_INT_EIE | CAN_INT_SIE;
        }
        else
        {
            can_instance->can_x->CR &= ~(CAN_INT_EIE | CAN_INT_SIE);
        }
        /* Generic owns RX/TX admission. Exclude the source being disabled
         * because its open_flag is updated after this BSP control call. */
        if (cmd == RT_DEVICE_CTRL_SET_INT ||
            (can_instance->can_x->CR & (CAN_INT_EIE | CAN_INT_SIE)) != 0U ||
            (can->parent.open_flag & (RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX) & ~argval) != 0U)
        {
            can_instance->can_x->CR |= CAN_INT_IE;
            NVIC_EnableIRQ(CAN0_IRQn);
        }
        else
        {
            can_instance->can_x->CR &= ~CAN_INT_IE;
            NVIC_ClearPendingIRQ(CAN0_IRQn);
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
            return cfg_can_default_filter(can_instance);
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            if (filter_cfg->count > HT32_CAN_RX_MSG_NUM ||
                (filter_cfg->count != 0 && filter_cfg->items == RT_NULL))
            {
                return -RT_EINVAL;
            }
            /* Validate the entire request before writing any hardware object. */
            for (i = 0; i < filter_cfg->count; i++)
            {
                /* Requested logical bank; -1 means allocation by request order. */
                rt_int32_t bank = filter_cfg->items[i].hdr_bank;
                if (bank < -1 || bank >= (rt_int32_t)HT32_CAN_RX_MSG_NUM ||
                    (bank == -1 && i >= HT32_CAN_RX_MSG_NUM))
                {
                    return -RT_EINVAL;
                }
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
                    filter_num = filter_cfg->items[i].hdr_bank;
                }
                if (can_instance->filter_cfg.filter_flag & (1UL << filter_num))
                {
                    LOG_W("This filter channel will be changed(num:%d)!", filter_num);
                    rt_kprintf("This filter channel will be changed(num:%d)!", filter_num);
                }
                can_instance->filter_cfg.filter_flag |= 1UL << filter_num;
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
                if (ht32_can_program_rx_filter(can_instance,
                                               &can_instance->filter_cfg.filter_mag[filter_num]) != RT_EOK)
                {
                    return -RT_ERROR;
                }
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
            /* next_cfg stages the request; result controls whether to publish it. */
            struct can_configure next_cfg = can->config;
            rt_err_t result;

            next_cfg.baud_rate = argval;
            result = ht32_can_configure(can, &next_cfg);
            if (result == RT_EOK)
            {
                can->config.baud_rate = argval;
            }
            return result;
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
            /* next_cfg stages the request; result controls whether to publish it. */
            struct can_configure next_cfg = can->config;
            rt_err_t result;

            next_cfg.mode = argval;
            result = ht32_can_configure(can, &next_cfg);
            if (result == RT_EOK)
            {
                can->config.mode = argval;
            }
            return result;
        }
        break;
    }
    case RT_CAN_CMD_SET_PRIV:
        if ((rt_ubase_t)arg != RT_CAN_MODE_PRIV && (rt_ubase_t)arg != RT_CAN_MODE_NOPRIV)
        {
            return -RT_EINVAL;
        }
        break;
    case RT_CAN_CMD_ABORT_TX:
        return -RT_ENOSYS;
    case RT_CAN_CMD_START:
        if ((rt_ubase_t)arg == 0U)
        {
            NVIC_DisableIRQ(CAN0_IRQn);
            can_instance->can_x->CR &= ~CAN_INT_ALL;
            CAN_DeInit(can_instance->can_x);
            NVIC_ClearPendingIRQ(CAN0_IRQn);
            return RT_EOK;
        }
        return ht32_can_configure(can, &can->config);
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
 * @brief Submit one Classic CAN frame to HT32 object 32 without waiting for a terminal.
 * @param can RT-Thread CAN device; Generic serializes TX submission with IRQs masked.
 * @param buf Classic CAN frame to submit immediately.
 * @param boxno Generic hardware mailbox index; only slot 0 is supported.
 * @return RT_EOK when hardware accepts the request, -RT_EBUSY if owned or IF busy,
 *         -RT_EINVAL for invalid input, or -RT_ERROR for a hardware submission failure.
 */
rt_ssize_t ht32_can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    struct ht32_can *can_instance;
    const struct rt_can_msg *pmsg = (const struct rt_can_msg *)buf;
    struct ht32_can_msg_type tx_msg = {0};

    RT_ASSERT(can != RT_NULL);
    can_instance = (struct ht32_can *)can->parent.user_data;
    RT_ASSERT(can_instance != RT_NULL);

    if (boxno != 0U || pmsg == RT_NULL || pmsg->len > 8U)
    {
        return -RT_EINVAL;
    }
    if ((can->status.sndchange & 1UL) != 0U ||
        (can_instance->can_x->IPR1 & HT32_CAN_TX_MSG_BIT) != 0U ||
        (can_instance->can_x->TRR1 & HT32_CAN_TX_MSG_BIT) != 0U)
    {
        return -RT_EBUSY;
    }
    /* The SDK uses IF0 then IF0/IF1 and otherwise spins waiting for a free IF. */
    if ((can_instance->can_x->IF0.CREQ & CAN_FLAG_IF_BUSY) != 0U ||
        (can_instance->can_x->IF1.CREQ & CAN_FLAG_IF_BUSY) != 0U)
    {
        return -RT_EBUSY;
    }

    tx_msg.cfg_msg.MsgNum = HT32_CAN_TX_MSG_NUM;
    if (pmsg->ide == RT_CAN_STDID)
    {
        tx_msg.cfg_msg.IdType = CAN_STD_ID;
    }
    else if (pmsg->ide == RT_CAN_EXTID)
    {
        tx_msg.cfg_msg.IdType = CAN_EXT_ID;
    }
    else
    {
        return -RT_EINVAL;
    }
    tx_msg.cfg_msg.Id = pmsg->id;

    if (pmsg->rtr == RT_CAN_RTR)
    {
        tx_msg.cfg_msg.FrameType = CAN_REMOTE_FRAME;
    }
    else if (pmsg->rtr == RT_CAN_DTR)
    {
        tx_msg.cfg_msg.FrameType = CAN_DATA_FRAME;
    }
    else
    {
        return -RT_EINVAL;
    }

    tx_msg.data_len = pmsg->len;
    rt_memcpy(tx_msg.data, pmsg->data, sizeof(tx_msg.data));
    if (CAN_Transmit(can_instance->can_x, &tx_msg.cfg_msg,
                     tx_msg.data, tx_msg.data_len) != SUCCESS)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * @brief Try one immediate submission and publish Generic mailbox zero on success.
 * @param can RT-Thread CAN device.
 * @param buf Classic CAN frame to submit.
 * @param mailbox Receives zero only when the hardware accepts the frame.
 * @return RT_EOK, -RT_EBUSY, or another negative submission/argument error.
 */
static rt_ssize_t ht32_can_sendmsg_nonblocking(struct rt_can_device *can,
                                                const void *buf, rt_uint32_t *mailbox)
{
    /* Immediate hardware submission result; not a bus-completion result. */
    rt_ssize_t result;

    if (mailbox == RT_NULL)
    {
        return -RT_EINVAL;
    }
    result = ht32_can_sendmsg(can, buf, 0U);
    if (result == RT_EOK)
    {
        *mailbox = 0U;
    }
    return result;
}
/**
 * @brief Receive one frame from an enabled HT32 RX message object.
 * SDK output is stored separately from the saved receive-filter description.
 * @param can RT-Thread CAN device.
 * @param buf Receives frame ID, IDE, RTR, DLC, data and optional filter index.
 * @param boxno Generic RX FIFO index, unused by this driver.
 * @return RT_EOK on success, or a negative status when no frame is available.
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
            /* CAN_Receive updates ID and frame type; keep the saved filter intact. */
            rx_msg.cfg_msg = can_instance->filter_cfg.filter_mag[i];
            rx_status = CAN_Receive(can_instance->can_x, &rx_msg.cfg_msg, rx_msg.data, &rx_msg.data_len);
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

                if (rx_msg.cfg_msg.IdType == CAN_EXT_ID)
                {
                    pmsg->id = rx_msg.cfg_msg.Id;
                    pmsg->ide = RT_CAN_EXTID;
                }
                else if (rx_msg.cfg_msg.IdType == CAN_STD_ID)
                {
                    pmsg->id = rx_msg.cfg_msg.Id;
                    pmsg->ide = RT_CAN_STDID;
                }
#ifdef RT_CAN_USING_HDR
                pmsg->hdr_index = i;
#endif /* RT_CAN_USING_HDR */

                if (rx_msg.cfg_msg.FrameType == CAN_DATA_FRAME)
                {
                    pmsg->rtr = RT_CAN_DTR;
                }
                else if (rx_msg.cfg_msg.FrameType == CAN_REMOTE_FRAME)
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
    .sendmsg_nonblocking = ht32_can_sendmsg_nonblocking,
};

/**
 * @brief Register the HT32 CAN controller with one Generic hardware TX slot.
 * @return RT_EOK after registration is requested.
 */
int rt_hw_can_init(void)
{

    struct can_configure config = CANDEFAULTCONFIG;
    config.sndboxnumber = 1;
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

/**
 * @brief Retire the dedicated TX object and forward individual RX object interrupts.
 *
 * Only the physical object's terminal retires Generic TX ownership; clearing a
 * transient interrupt while TRR is set does not free the hardware request.
 * Pending flags are cleared before publishing a final terminal so the next
 * hardware submission cannot consume the previous request's event.
 */
void CAN0_IRQHandler(void)
{
    CAN_LastErrorCode_TypeDef lec;
    /* Controller registers and RX object iterator. */
    HT_CAN_TypeDef *can_x = ht32_can_config.can_x;
    rt_uint32_t i;

    rt_interrupt_enter();
    if ((can_x->CR & (CAN_INT_EIE | CAN_INT_SIE)) != 0U)
    {
        if (CAN_GetFlagStatus(can_x, CAN_FLAG_BOFF))
        {
            CAN_BusOffRecovery(can_x);
        }
    }

    /* Message Object 32 is the only TX owner visible to Generic as mailbox 0. */
    if ((can_x->IPR1 & HT32_CAN_TX_MSG_BIT) != 0U)
    {
        if ((can_x->IF0.CREQ & CAN_FLAG_IF_BUSY) == 0U ||
            (can_x->IF1.CREQ & CAN_FLAG_IF_BUSY) == 0U)
        {
            /* Descriptor for acknowledging object 32's latched interrupt. */
            CAN_MSG_TypeDef tx_msg = {0};
            tx_msg.MsgNum = HT32_CAN_TX_MSG_NUM;
            CAN_ClearMsgPendingFlag(can_x, &tx_msg);
            if ((can_x->TRR1 & HT32_CAN_TX_MSG_BIT) == 0U)
            {
                /* SDK status semantics: NDR distinguishes failure after TRR clears. */
                int event = (can_x->NDR1 & HT32_CAN_TX_MSG_BIT) != 0U ?
                            RT_CAN_EVENT_TX_FAIL : RT_CAN_EVENT_TX_DONE;
                CAN_ClearFlag(can_x, CAN_FLAG_TXOK);
                rt_hw_can_isr(&ht32_can_config.device, event);
            }
        }
    }

    /* Consume one RX Message Object per Generic notification, not all IPR bits. */
    for (i = 0; i < HT32_CAN_RX_MSG_NUM; i++)
    {
        /* Configured RX descriptor for this individual physical message object. */
        CAN_MSG_TypeDef *rx_msg;
        if ((ht32_can_config.filter_cfg.filter_flag & (1UL << i)) == 0U)
        {
            continue;
        }
        rx_msg = &ht32_can_config.filter_cfg.filter_mag[i];
        if (!CAN_GetMsgPending(can_x, rx_msg))
        {
            continue;
        }
        if ((ht32_can_config.device.parent.open_flag & RT_DEVICE_FLAG_INT_RX) != 0U &&
            CAN_NewDataReceived(can_x, rx_msg))
        {
            rt_hw_can_isr(&ht32_can_config.device, RT_CAN_EVENT_RX_IND);
        }
        else if ((can_x->IF0.CREQ & CAN_FLAG_IF_BUSY) == 0U ||
                 (can_x->IF1.CREQ & CAN_FLAG_IF_BUSY) == 0U)
        {
            CAN_ClearMsgPendingFlag(can_x, rx_msg);
        }
    }
    if (CAN_GetFlagStatus(can_x, CAN_FLAG_RXOK))
    {
        CAN_ClearFlag(can_x, CAN_FLAG_RXOK);
    }

    lec = CAN_GetLastErrorCode(ht32_can_config.can_x);
    if ((can_x->CR & (CAN_INT_EIE | CAN_INT_SIE)) != 0U && lec != NO_ERROR)
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
