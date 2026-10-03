/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-05     Xeon Xu      the first version
 * 2019-01-22     YLZ          port from stm324xx-HAL to bsp stm3210x-HAL
 * 2019-02-19     YLZ          add support EXTID RTR Frame. modify send, recv functions.
 *                             fix bug.port to BSP [stm32]
 * 2019-03-27     YLZ          support double can channels, support stm32F4xx (only Legacy mode).
 * 2019-06-17     YLZ          port to new STM32F1xx HAL V1.1.3.
 * 2021-02-02     YuZhe XU     fix bug in filter config
 * 2021-8-25      SVCHAO       The baud rate is configured according to the different APB1 frequencies.
                               f4-series only.
 * 2025-09-20     wdfk_prog    Implemented sendmsg_nonblocking op to support framework's async TX.
 * 2026-02-02     wdfk_prog    Drain multiple RX frames per ISR with a bounded limit.
 * 2026-08-30     wdfk_prog    Advertise ISR-safe TX and publish error state before TX terminal events.
 * 2026-08-30     wdfk_prog    Add bxCAN hardware mailbox abort support.
 */

/*
 * STM32 bxCAN integration contract
 * --------------------------------
 *
 * This BSP stays hardware-focused; Generic CAN owns thread/ISR synchronization,
 * blocking wait policy and runtime lifetime. Only the following TX requirements
 * are implemented here:
 *
 * - sendmsg(can, frame, mailbox) performs one immediate submit to the selected
 *   hardware mailbox. Busy or terminal-pending mailboxes return -RT_EBUSY.
 * - sendmsg_nonblocking() scans hardware mailboxes once and never sleeps, retries
 *   later or enqueues a software copy.
 * - RQCPx is kept asserted until TX_DONE/TX_FAIL has been published through
 *   rt_hw_can_isr(); a completed mailbox is therefore not reused prematurely.
 * - bxCAN TSR mixes request bits with write-one-to-clear completion bits. RQCPx
 *   and ABRQx updates use direct WRITE_REG writes instead of read-modify-write
 *   SET_BIT operations, which could accidentally clear another pending terminal.
 *
 * SET_FILTER keeps the existing BSP loop/ID conversion. The only Generic-facing
 * additions are mirroring filter_cfg->actived into FilterActivation and returning
 * HAL failures so the Generic shadow is committed only after hardware accepts it.
 * Other RX/configuration code keeps the existing BSP structure and HAL flow; the
 * framework must not push Generic scheduling/lifecycle state into this driver.
 */

#include "drv_can.h"

#ifdef BSP_USING_CAN

#define LOG_TAG "drv_can"
#include <drv_log.h>

#ifndef CAN_ISR_DRAIN_LIMIT
/*
 * bxCAN FIFO depth is 3 (FMP[1:0]=0..3). Draining up to 3 frames can clear the FIFO in one ISR,
 * reducing FULL/OVERRUN without letting ISR time grow unbounded.
 */
#define CAN_ISR_DRAIN_LIMIT 3
#endif

/* attention !!! baud calculation example: Tclk / ((ss + bs1 + bs2) * brp) = 36 / ((1 + 8 + 3) * 3) = 1MHz*/
#if defined(SOC_SERIES_STM32F1)/* APB1 36MHz(max) */
static const struct stm32_baud_rate_tab can_baud_rate_tab[] = {
    { CAN1MBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ | CAN_BS2_3TQ | 3) },
    { CAN800kBaud, (CAN_SJW_2TQ | CAN_BS1_5TQ | CAN_BS2_3TQ | 5) },
    { CAN500kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ | CAN_BS2_3TQ | 6) },
    { CAN250kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ | CAN_BS2_3TQ | 12) },
    { CAN125kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ | CAN_BS2_3TQ | 24) },
    { CAN100kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ | CAN_BS2_3TQ | 30) },
    { CAN50kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ | CAN_BS2_3TQ | 60) },
    { CAN20kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ | CAN_BS2_3TQ | 150) },
    { CAN10kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ | CAN_BS2_3TQ | 300) }
};
#elif defined(SOC_SERIES_STM32F4)  /* 42MHz or 45MHz */
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F401xC) || defined(STM32F401xE) /* 42MHz(max) */
static const struct stm32_baud_rate_tab can_baud_rate_tab[] = {
    { CAN1MBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_4TQ | 3) },
    { CAN800kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ | CAN_BS2_4TQ | 4) },
    { CAN500kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_4TQ | 6) },
    { CAN250kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_4TQ | 12) },
    { CAN125kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_4TQ | 24) },
    { CAN100kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_4TQ | 30) },
    { CAN50kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_4TQ | 60) },
    { CAN20kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_4TQ | 150) },
    { CAN10kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_4TQ | 300) }
};
#else  /* APB1 45MHz(max) */
static const struct stm32_baud_rate_tab can_baud_rate_tab[] = {
#ifdef BSP_USING_CAN168M
    { CAN1MBaud, (CAN_SJW_1TQ | CAN_BS1_3TQ | CAN_BS2_3TQ | 6) },
#else
    { CAN1MBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_5TQ | 3) },
#endif
    { CAN800kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ | CAN_BS2_5TQ | 4) },
    { CAN500kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_5TQ | 6) },
    { CAN250kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_5TQ | 12) },
    { CAN125kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_5TQ | 24) },
    { CAN100kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_5TQ | 30) },
    { CAN50kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_5TQ | 60) },
    { CAN20kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_5TQ | 150) },
    { CAN10kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_5TQ | 300) }
};
#endif
#elif defined(SOC_SERIES_STM32F7)/* APB1 54MHz(max) */
static const struct stm32_baud_rate_tab can_baud_rate_tab[] = {
    { CAN1MBaud, (CAN_SJW_2TQ | CAN_BS1_10TQ | CAN_BS2_7TQ | 3) },
    { CAN800kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ | CAN_BS2_7TQ | 4) },
    { CAN500kBaud, (CAN_SJW_2TQ | CAN_BS1_10TQ | CAN_BS2_7TQ | 6) },
    { CAN250kBaud, (CAN_SJW_2TQ | CAN_BS1_10TQ | CAN_BS2_7TQ | 12) },
    { CAN125kBaud, (CAN_SJW_2TQ | CAN_BS1_10TQ | CAN_BS2_7TQ | 24) },
    { CAN100kBaud, (CAN_SJW_2TQ | CAN_BS1_10TQ | CAN_BS2_7TQ | 30) },
    { CAN50kBaud, (CAN_SJW_2TQ | CAN_BS1_10TQ | CAN_BS2_7TQ | 60) },
    { CAN20kBaud, (CAN_SJW_2TQ | CAN_BS1_10TQ | CAN_BS2_7TQ | 150) },
    { CAN10kBaud, (CAN_SJW_2TQ | CAN_BS1_10TQ | CAN_BS2_7TQ | 300) }
};
#elif defined(SOC_SERIES_STM32L4)/* APB1 80MHz(max) */
static const struct stm32_baud_rate_tab can_baud_rate_tab[] = {
    { CAN1MBaud, (CAN_SJW_2TQ | CAN_BS1_5TQ | CAN_BS2_2TQ | 10) },
    { CAN800kBaud, (CAN_SJW_2TQ | CAN_BS1_14TQ | CAN_BS2_5TQ | 5) },
    { CAN500kBaud, (CAN_SJW_2TQ | CAN_BS1_7TQ | CAN_BS2_2TQ | 16) },
    { CAN250kBaud, (CAN_SJW_2TQ | CAN_BS1_13TQ | CAN_BS2_2TQ | 20) },
    { CAN125kBaud, (CAN_SJW_2TQ | CAN_BS1_13TQ | CAN_BS2_2TQ | 40) },
    { CAN100kBaud, (CAN_SJW_2TQ | CAN_BS1_13TQ | CAN_BS2_2TQ | 50) },
    { CAN50kBaud, (CAN_SJW_2TQ | CAN_BS1_13TQ | CAN_BS2_2TQ | 100) },
    { CAN20kBaud, (CAN_SJW_2TQ | CAN_BS1_13TQ | CAN_BS2_2TQ | 250) },
    { CAN10kBaud, (CAN_SJW_2TQ | CAN_BS1_13TQ | CAN_BS2_2TQ | 500) }
};
#endif

#ifdef BSP_USING_CAN1
static struct stm32_can drv_can1 = {
    .name = "can1",
    .CanHandle.Instance = CAN1,
};
#endif

#ifdef BSP_USING_CAN2
static struct stm32_can drv_can2 = {
    "can2",
    .CanHandle.Instance = CAN2,
};
#endif

static rt_uint32_t get_can_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index;

    len = sizeof(can_baud_rate_tab) / sizeof(can_baud_rate_tab[0]);
    for (index = 0; index < len; index++)
    {
        if (can_baud_rate_tab[index].baud_rate == baud)
        {
            return index;
        }
    }

    return 0; /* default baud is CAN1MBaud */
}

static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    struct stm32_can *drv_can;
    rt_uint32_t baud_index;

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    drv_can = (struct stm32_can *)can->parent.user_data;
    RT_ASSERT(drv_can);

    drv_can->CanHandle.Init.TimeTriggeredMode = DISABLE;
    drv_can->CanHandle.Init.AutoBusOff = DISABLE;
    drv_can->CanHandle.Init.AutoWakeUp = DISABLE;
    drv_can->CanHandle.Init.AutoRetransmission = ENABLE;
    drv_can->CanHandle.Init.ReceiveFifoLocked = DISABLE;
    drv_can->CanHandle.Init.TransmitFifoPriority = ENABLE;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        drv_can->CanHandle.Init.Mode = CAN_MODE_NORMAL;
        break;
    case RT_CAN_MODE_LISTEN:
        drv_can->CanHandle.Init.Mode = CAN_MODE_SILENT;
        break;
    case RT_CAN_MODE_LOOPBACK:
        drv_can->CanHandle.Init.Mode = CAN_MODE_LOOPBACK;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        drv_can->CanHandle.Init.Mode = CAN_MODE_SILENT_LOOPBACK;
        break;
    }

    baud_index = get_can_baud_index(cfg->baud_rate);
    drv_can->CanHandle.Init.SyncJumpWidth = BAUD_DATA(SJW, baud_index);
    drv_can->CanHandle.Init.TimeSeg1 = BAUD_DATA(BS1, baud_index);
    drv_can->CanHandle.Init.TimeSeg2 = BAUD_DATA(BS2, baud_index);
    drv_can->CanHandle.Init.Prescaler = BAUD_DATA(RRESCL, baud_index);
    /* init can */
    if (HAL_CAN_Init(&drv_can->CanHandle) != HAL_OK)
    {
        return -RT_ERROR;
    }

    /* default filter config */
    if (HAL_CAN_ConfigFilter(&drv_can->CanHandle, &drv_can->FilterConfig) != HAL_OK)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval;
    struct stm32_can *drv_can;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can != RT_NULL);
    drv_can = (struct stm32_can *)can->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t)arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            if (CAN1 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
                HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
                HAL_NVIC_DisableIRQ(CAN2_RX1_IRQn);
            }
#endif
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_RX_FIFO0_MSG_PENDING);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_RX_FIFO0_FULL);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_RX_FIFO0_OVERRUN);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_RX_FIFO1_MSG_PENDING);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_RX_FIFO1_FULL);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_RX_FIFO1_OVERRUN);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            if (CAN1 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_DisableIRQ(CAN2_TX_IRQn);
            }
#endif
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_TX_MAILBOX_EMPTY);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            if (CAN1 == drv_can->CanHandle.Instance)
            {
                NVIC_DisableIRQ(CAN1_SCE_IRQn);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CanHandle.Instance)
            {
                NVIC_DisableIRQ(CAN2_SCE_IRQn);
            }
#endif
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_ERROR_WARNING);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_ERROR_PASSIVE);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_BUSOFF);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_LAST_ERROR_CODE);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_ERROR);
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t)arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_RX_FIFO0_MSG_PENDING);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_RX_FIFO0_FULL);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_RX_FIFO0_OVERRUN);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_RX_FIFO1_MSG_PENDING);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_RX_FIFO1_FULL);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_RX_FIFO1_OVERRUN);

            if (CAN1 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
                HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
                HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
            }
#endif
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_TX_MAILBOX_EMPTY);

            if (CAN1 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_SetPriority(CAN1_TX_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_SetPriority(CAN2_TX_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN2_TX_IRQn);
            }
#endif
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_ERROR_WARNING);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_ERROR_PASSIVE);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_BUSOFF);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_LAST_ERROR_CODE);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_ERROR);

            if (CAN1 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
            }
#ifdef CAN2
            if (CAN2 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_SetPriority(CAN2_SCE_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN2_SCE_IRQn);
            }
#endif
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
    {
        rt_uint32_t id_h = 0;
        rt_uint32_t id_l = 0;
        rt_uint32_t mask_h = 0;
        rt_uint32_t mask_l = 0;
        rt_uint32_t mask_l_tail = 0;  /*CAN_FxR2 bit [2:0]*/

        if (RT_NULL == arg)
        {
            /* default filter config */
            if (HAL_CAN_ConfigFilter(&drv_can->CanHandle, &drv_can->FilterConfig) != HAL_OK)
            {
                return -RT_ERROR;
            }
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            if (!IS_CAN_FILTER_BANK_DUAL(drv_can->FilterConfig.SlaveStartFilterBank))
            {
                LOG_W("can%s invalid SlaveStartFilterBank=%d", drv_can->name, drv_can->FilterConfig.SlaveStartFilterBank);
            }
            /* get default filter */
            for (int i = 0; i < filter_cfg->count; i++)
            {
                if (filter_cfg->items[i].hdr_bank == -1)
                {
                    /* use default filter bank settings */
                    if (rt_strcmp(drv_can->name, "can1") == 0)
                    {
                        /* can1 banks 0~13 */
                        drv_can->FilterConfig.FilterBank = i;
                    }
                    else if (rt_strcmp(drv_can->name, "can2") == 0)
                    {
                        /* can2 banks 14~27 */
                        drv_can->FilterConfig.FilterBank = i + 14;
                    }
                }
                else
                {
                    /* use user-defined filter bank settings */
                    drv_can->FilterConfig.FilterBank = filter_cfg->items[i].hdr_bank;
                }
                if (!IS_CAN_FILTER_BANK_DUAL(drv_can->FilterConfig.FilterBank))
                {
                    LOG_W("can%s invalid FilterBank=%d, skip item %d", drv_can->name, drv_can->FilterConfig.FilterBank, i);
                    continue;
                }
                 /**
                 * ID     | CAN_FxR1[31:24] | CAN_FxR1[23:16] | CAN_FxR1[15:8] | CAN_FxR1[7:0]       |
                 * MASK   | CAN_FxR2[31:24] | CAN_FxR2[23:16] | CAN_FxR2[15:8] | CAN_FxR2[7:0]       |
                 * STD ID |     STID[10:3]  | STDID[2:0] |<-                21bit                  ->|
                 * EXT ID |    EXTID[28:21] | EXTID[20:13]    | EXTID[12:5]    | EXTID[4:0] IDE RTR 0|
                 * @note the 32bit STD ID must << 21 to fill CAN_FxR1[31:21] and EXT ID must << 3,
                 *       -> but the id bit of struct rt_can_filter_item is 29,
                 *       -> so STD id << 18 and EXT id Don't need << 3, when get the high 16bit.
                 *       -> FilterIdHigh : (((STDid << 18) or (EXT id)) >> 13) & 0xFFFF,
                 *       -> FilterIdLow:   ((STDid << 18) or (EXT id << 3)) & 0xFFFF.
                 * @note the mask bit of struct rt_can_filter_item is 32,
                 *       -> FilterMaskIdHigh: (((STD mask << 21) or (EXT mask <<3)) >> 16) & 0xFFFF
                 *       -> FilterMaskIdLow: ((STD mask << 21) or (EXT mask <<3)) & 0xFFFF
                 */
                if (filter_cfg->items[i].mode == CAN_FILTERMODE_IDMASK)
                {
                    /* make sure the CAN_FxR1[2:0](IDE RTR) work */
                    mask_l_tail = 0x06;
                }
                else if (filter_cfg->items[i].mode == CAN_FILTERMODE_IDLIST)
                {
                    /* same as CAN_FxR1 */
                    mask_l_tail = (filter_cfg->items[i].ide << 2) |
                                  (filter_cfg->items[i].rtr << 1);
                }
                if (filter_cfg->items[i].ide == RT_CAN_STDID)
                {
                    id_h = ((filter_cfg->items[i].id << 18) >> 13) & 0xFFFF;
                    id_l = ((filter_cfg->items[i].id << 18) |
                            (filter_cfg->items[i].ide << 2) |
                            (filter_cfg->items[i].rtr << 1)) &
                           0xFFFF;
                    mask_h = ((filter_cfg->items[i].mask << 21) >> 16) & 0xFFFF;
                    mask_l = ((filter_cfg->items[i].mask << 21) | mask_l_tail) & 0xFFFF;
                }
                else if (filter_cfg->items[i].ide == RT_CAN_EXTID)
                {
                    id_h = (filter_cfg->items[i].id >> 13) & 0xFFFF;
                    id_l = ((filter_cfg->items[i].id << 3) |
                            (filter_cfg->items[i].ide << 2) |
                            (filter_cfg->items[i].rtr << 1)) &
                           0xFFFF;
                    mask_h = ((filter_cfg->items[i].mask << 3) >> 16) & 0xFFFF;
                    mask_l = ((filter_cfg->items[i].mask << 3) | mask_l_tail) & 0xFFFF;
                }
                drv_can->FilterConfig.FilterIdHigh = id_h;
                drv_can->FilterConfig.FilterIdLow = id_l;
                drv_can->FilterConfig.FilterMaskIdHigh = mask_h;
                drv_can->FilterConfig.FilterMaskIdLow = mask_l;

                drv_can->FilterConfig.FilterMode = filter_cfg->items[i].mode;
                drv_can->FilterConfig.FilterFIFOAssignment = filter_cfg->items[i].rxfifo;/*rxfifo = CAN_RX_FIFO0/CAN_RX_FIFO1*/
                /* Keep hardware activation aligned with the Generic HDR shadow transaction. */
                drv_can->FilterConfig.FilterActivation = filter_cfg->actived ? ENABLE : DISABLE;
                /* Filter conf */
                if (HAL_CAN_ConfigFilter(&drv_can->CanHandle, &drv_can->FilterConfig) != HAL_OK)
                {
                    return -RT_ERROR;
                }
            }
        }
        break;
    }
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t)arg;
        if (argval != RT_CAN_MODE_NORMAL &&
            argval != RT_CAN_MODE_LISTEN &&
            argval != RT_CAN_MODE_LOOPBACK &&
            argval != RT_CAN_MODE_LOOPBACKANLISTEN)
        {
            return -RT_ERROR;
        }
        if (argval != drv_can->device.config.mode)
        {
            drv_can->device.config.mode = argval;
            return _can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t)arg;
        if (argval != CAN1MBaud &&
            argval != CAN800kBaud &&
            argval != CAN500kBaud &&
            argval != CAN250kBaud &&
            argval != CAN125kBaud &&
            argval != CAN100kBaud &&
            argval != CAN50kBaud &&
            argval != CAN20kBaud &&
            argval != CAN10kBaud)
        {
            return -RT_ERROR;
        }
        if (argval != drv_can->device.config.baud_rate)
        {
            drv_can->device.config.baud_rate = argval;
            return _can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t)arg;
        if (argval != RT_CAN_MODE_PRIV &&
            argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        if (argval != drv_can->device.config.privmode)
        {
            drv_can->device.config.privmode = argval;
            return _can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_ABORT_TX:
    {
        rt_uint32_t tx_mailbox;

        argval = (rt_uint32_t)(rt_ubase_t)arg;
        switch (argval)
        {
        case 0:
            tx_mailbox = CAN_TSR_ABRQ0;
            break;
        case 1:
            tx_mailbox = CAN_TSR_ABRQ1;
            break;
        case 2:
            tx_mailbox = CAN_TSR_ABRQ2;
            break;
        default:
            return -RT_EINVAL;
        }

        /*
         * TSR completion flags are W1C. Write only ABRQx so aborting one mailbox
         * cannot accidentally consume another mailbox's unreported RQCPx terminal.
         */
        WRITE_REG(drv_can->CanHandle.Instance->TSR, tx_mailbox);
        break;
    }
    case RT_CAN_CMD_GET_STATUS:
    {
        rt_uint32_t errtype;
        errtype = drv_can->CanHandle.Instance->ESR;
        drv_can->device.status.rcverrcnt = errtype >> 24;
        drv_can->device.status.snderrcnt = (errtype >> 16 & 0xFF);
        drv_can->device.status.lasterrtype = errtype & 0x70;
        drv_can->device.status.errcode = errtype & 0x07;

        rt_memcpy(arg, &drv_can->device.status, sizeof(drv_can->device.status));
        break;
    }
    case RT_CAN_CMD_START:
    {
        argval = (rt_uint32_t)(rt_ubase_t)arg;

        if (argval == 0U)
        {
            /*
            * Final stop/deinit.
            * Generic final close will clear RT_DEVICE_FLAG_ACTIVATED.
            */
            if (HAL_CAN_DeInit(&drv_can->CanHandle) != HAL_OK)
            {
                LOG_E("CAN deinitialization failed");
                return -RT_ERROR;
            }
        }
        else
        {
            /*
            * Normal rt_device_open() has already called configure()
            * and left the controller in READY.
            *
            * Keep RESET recovery for direct START(0) -> START(1)
            * control usage.
            */
            if (drv_can->CanHandle.State == HAL_CAN_STATE_RESET)
            {
                rt_err_t result;

                result = _can_config(&drv_can->device,
                                     &drv_can->device.config);
                if (result != RT_EOK)
                {
                    return result;
                }
            }

            if (drv_can->CanHandle.State == HAL_CAN_STATE_LISTENING)
            {
                break;
            }

            if (drv_can->CanHandle.State != HAL_CAN_STATE_READY)
            {
                LOG_E("CAN start invalid state: %d",
                      (int)drv_can->CanHandle.State);
                return -RT_ERROR;
            }

            if (HAL_CAN_Start(&drv_can->CanHandle) != HAL_OK)
            {
                LOG_E("CAN start failed: state=%d error=0x%08lx",
                      (int)drv_can->CanHandle.State,
                      (unsigned long)drv_can->CanHandle.ErrorCode);
                return -RT_ERROR;
            }
        }
    }

    break;
    }

    return RT_EOK;
}

/**
 * @internal
 * @brief Low-level function to send a CAN message to a specific hardware mailbox.
 *
 * The generic framework has already reserved @p box_num before this callback.
 * This implementation only programs bxCAN registers and returns immediately; it
 * does not sleep or wait for transmission completion.
 *
 * @param[in] can     A pointer to the CAN device structure.
 * @param[in] buf     A pointer to the `rt_can_msg` to be sent.
 * @param[in] box_num The specific hardware mailbox index (0, 1, or 2) to use for this tran
 *
 * @return `RT_EOK` on success, or an error code on failure.
 */
static rt_ssize_t _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    CAN_HandleTypeDef *hcan;
    hcan = &((struct stm32_can *)can->parent.user_data)->CanHandle;
    struct rt_can_msg *pmsg = (struct rt_can_msg *)buf;
    CAN_TxHeaderTypeDef txheader = { 0 };
    HAL_CAN_StateTypeDef state = hcan->State;

    /* Check the parameters */
    RT_ASSERT(IS_CAN_DLC(pmsg->len));

    if ((state == HAL_CAN_STATE_READY) ||
        (state == HAL_CAN_STATE_LISTENING))
    {
        /*check select mailbox  is empty */
        /*
         * CAN_TX_MAILBOXx selects the mailbox; CAN_TSR_TME/RQCPx are
         * status bits in TSR for that mailbox and are not interchangeable.
         */
        uint32_t tme_flag;
        uint32_t rqcp_flag;

        switch (1 << box_num)
        {
        case CAN_TX_MAILBOX0:
            tme_flag = CAN_TSR_TME0;
            rqcp_flag = CAN_TSR_RQCP0;
            break;
        case CAN_TX_MAILBOX1:
            tme_flag = CAN_TSR_TME1;
            rqcp_flag = CAN_TSR_RQCP1;
            break;
        case CAN_TX_MAILBOX2:
            tme_flag = CAN_TSR_TME2;
            rqcp_flag = CAN_TSR_RQCP2;
            break;
        default:
            return -RT_EINVAL;
        }

        /*
         * Keep a completed mailbox unavailable until its previous terminal has
         * been published. Otherwise a stale RQCP could complete a new Generic owner.
         */
        if (HAL_IS_BIT_SET(hcan->Instance->TSR, tme_flag) != SET ||
            HAL_IS_BIT_SET(hcan->Instance->TSR, rqcp_flag) == SET)
        {
            return -RT_EBUSY;
        }

        if (RT_CAN_STDID == pmsg->ide)
        {
            txheader.IDE = CAN_ID_STD;
            RT_ASSERT(IS_CAN_STDID(pmsg->id));
            txheader.StdId = pmsg->id;
        }
        else
        {
            txheader.IDE = CAN_ID_EXT;
            RT_ASSERT(IS_CAN_EXTID(pmsg->id));
            txheader.ExtId = pmsg->id;
        }

        if (RT_CAN_DTR == pmsg->rtr)
        {
            txheader.RTR = CAN_RTR_DATA;
        }
        else
        {
            txheader.RTR = CAN_RTR_REMOTE;
        }
        /* clear TIR */
        hcan->Instance->sTxMailBox[box_num].TIR &= CAN_TI0R_TXRQ;
        /* Set up the Id */
        if (RT_CAN_STDID == pmsg->ide)
        {
            hcan->Instance->sTxMailBox[box_num].TIR |= (txheader.StdId << CAN_TI0R_STID_Pos) | txheader.RTR;
        }
        else
        {
            hcan->Instance->sTxMailBox[box_num].TIR |= (txheader.ExtId << CAN_TI0R_EXID_Pos) | txheader.IDE | txheader.RTR;
        }
        /* Set up the DLC */
        hcan->Instance->sTxMailBox[box_num].TDTR = pmsg->len & 0x0FU;
        /* Set up the data field */
        WRITE_REG(hcan->Instance->sTxMailBox[box_num].TDHR,
                  ((uint32_t)pmsg->data[7] << CAN_TDH0R_DATA7_Pos) |
                      ((uint32_t)pmsg->data[6] << CAN_TDH0R_DATA6_Pos) |
                      ((uint32_t)pmsg->data[5] << CAN_TDH0R_DATA5_Pos) |
                      ((uint32_t)pmsg->data[4] << CAN_TDH0R_DATA4_Pos));
        WRITE_REG(hcan->Instance->sTxMailBox[box_num].TDLR,
                  ((uint32_t)pmsg->data[3] << CAN_TDL0R_DATA3_Pos) |
                      ((uint32_t)pmsg->data[2] << CAN_TDL0R_DATA2_Pos) |
                      ((uint32_t)pmsg->data[1] << CAN_TDL0R_DATA1_Pos) |
                      ((uint32_t)pmsg->data[0] << CAN_TDL0R_DATA0_Pos));
        /* Request transmission */
        SET_BIT(hcan->Instance->sTxMailBox[box_num].TIR, CAN_TI0R_TXRQ);

        return RT_EOK;
    }
    else
    {
        /* Update error code */
        hcan->ErrorCode |= HAL_CAN_ERROR_NOT_INITIALIZED;

        return -RT_ERROR;
    }
}

/**
 * @internal
 * @brief Low-level, hardware-specific non-blocking function to send a CAN message.
 *
 * This function performs one immediate hardware attempt and returns without
 * waiting, retrying, or placing the frame in a software queue.
 *
 * @param[in] can   A pointer to the CAN device structure.
 * @param[in] buf   A pointer to the `rt_can_msg` to be sent.
 *
 * @return
 * - `RT_EOK` if the message was accepted by a hardware mailbox.
 * - `-RT_EBUSY` if all reusable hardware mailboxes are busy.
 * - Other negative errors from the selected-mailbox submit path.
 */
static rt_ssize_t _can_sendmsg_nonblocking(struct rt_can_device *can, const void *buf)
{
    rt_uint32_t mailbox;

    for (mailbox = 0; mailbox < can->config.sndboxnumber && mailbox < 3U; mailbox++)
    {
        rt_ssize_t result = _can_sendmsg(can, buf, mailbox);

        if (result == RT_EOK)
        {
            return RT_EOK;
        }
        if (result != -RT_EBUSY)
        {
            return result;
        }
    }

    return -RT_EBUSY;
}

static rt_ssize_t _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    HAL_StatusTypeDef status;
    CAN_HandleTypeDef *hcan;
    struct rt_can_msg *pmsg;
    CAN_RxHeaderTypeDef rxheader = { 0 };

    RT_ASSERT(can);

    hcan = &((struct stm32_can *)can->parent.user_data)->CanHandle;
    pmsg = (struct rt_can_msg *)buf;

    /* get data */
    status = HAL_CAN_GetRxMessage(hcan, fifo, &rxheader, pmsg->data);
    if (HAL_OK != status)
    {
        return -RT_ERROR;
    }
    /* get id */
    if (CAN_ID_STD == rxheader.IDE)
    {
        pmsg->ide = RT_CAN_STDID;
        pmsg->id = rxheader.StdId;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
        pmsg->id = rxheader.ExtId;
    }
    /* get type */
    if (CAN_RTR_DATA == rxheader.RTR)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else
    {
        pmsg->rtr = RT_CAN_RTR;
    }
    /*get rxfifo = CAN_RX_FIFO0/CAN_RX_FIFO1*/
    pmsg->rxfifo = fifo;

    /* get len */
    pmsg->len = rxheader.DLC;
    /* get hdr_index */
    if (hcan->Instance == CAN1)
    {
        pmsg->hdr_index = rxheader.FilterMatchIndex;
    }
#ifdef CAN2
    else if (hcan->Instance == CAN2)
    {
        pmsg->hdr_index = rxheader.FilterMatchIndex;
    }
#endif

    return RT_EOK;
}


static const struct rt_can_ops _can_ops = {
    .configure = _can_config,
    .control = _can_control,
    .sendmsg = _can_sendmsg,
    .recvmsg = _can_recvmsg,
    .sendmsg_nonblocking = _can_sendmsg_nonblocking,
};

static void _can_rx_isr(struct rt_can_device *can, rt_uint32_t fifo)
{
    CAN_HandleTypeDef *hcan;
    RT_ASSERT(can);
    hcan = &((struct stm32_can *)can->parent.user_data)->CanHandle;

    switch (fifo)
    {
    case CAN_RX_FIFO0:
        /* save to user list: drain multiple frames per ISR to reduce FULL/OVERRUN */
        if (__HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_RX_FIFO0_MSG_PENDING))
        {
            for (rt_uint32_t i = 0; i < CAN_ISR_DRAIN_LIMIT; i++)
            {
                if (HAL_CAN_GetRxFifoFillLevel(hcan, CAN_RX_FIFO0) == 0)
                {
                    break;
                }
                else
                {
                    rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
                }
            }
        }
        /* Check FULL flag for FIFO0 */
        if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FF0) && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_RX_FIFO0_FULL))
        {
            /* Clear FIFO0 FULL Flag */
            __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FF0);
        }

        /* Check Overrun flag for FIFO0 */
        if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FOV0) && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_RX_FIFO0_OVERRUN))
        {
            /* Clear FIFO0 Overrun Flag */
            __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FOV0);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        break;
    case CAN_RX_FIFO1:
        /* save to user list: drain multiple frames per ISR to reduce FULL/OVERRUN */
        if (__HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_RX_FIFO1_MSG_PENDING))
        {
            for (rt_uint32_t i = 0; i < CAN_ISR_DRAIN_LIMIT; i++)
            {
                if (HAL_CAN_GetRxFifoFillLevel(hcan, CAN_RX_FIFO1) == 0)
                {
                    break;
                }
                else
                {
                    rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
                }
            }
        }
        /* Check FULL flag for FIFO1 */
        if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FF1) && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_RX_FIFO1_FULL))
        {
            /* Clear FIFO1 FULL Flag */
            __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FF1);
        }

        /* Check Overrun flag for FIFO1 */
        if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FOV1) && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_RX_FIFO1_OVERRUN))
        {
            /* Clear FIFO1 Overrun Flag */
            __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FOV1);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        break;
    }
}

static void _can_check_tx_complete(struct rt_can_device *can)
{
    CAN_HandleTypeDef *hcan;
    RT_ASSERT(can);
    hcan = &((struct stm32_can *)can->parent.user_data)->CanHandle;

    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_RQCP0) &&
        !__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK0))
    {
        rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        WRITE_REG(hcan->Instance->TSR, CAN_TSR_RQCP0);
    }

    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_RQCP1) &&
        !__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK1))
    {
        rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        WRITE_REG(hcan->Instance->TSR, CAN_TSR_RQCP1);
    }

    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_RQCP2) &&
        !__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK2))
    {
        rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        WRITE_REG(hcan->Instance->TSR, CAN_TSR_RQCP2);
    }

    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TERR0))/*IF AutoRetransmission = ENABLE,ACK ERR handler*/
    {
        WRITE_REG(hcan->Instance->TSR, CAN_TSR_ABRQ0);/*Abort the send request, trigger the TX interrupt,release completion quantity*/
    }

    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TERR1))
    {
        WRITE_REG(hcan->Instance->TSR, CAN_TSR_ABRQ1);
    }

    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TERR2))
    {
        WRITE_REG(hcan->Instance->TSR, CAN_TSR_ABRQ2);
    }
}

static void _can_sce_isr(struct rt_can_device *can)
{
    CAN_HandleTypeDef *hcan;
    RT_ASSERT(can);
    hcan = &((struct stm32_can *)can->parent.user_data)->CanHandle;
    rt_uint32_t errtype = hcan->Instance->ESR;

    switch ((errtype & 0x70) >> 4)
    {
    case RT_CAN_BUS_BIT_PAD_ERR:
        can->status.bitpaderrcnt++;
        break;
    case RT_CAN_BUS_FORMAT_ERR:
        can->status.formaterrcnt++;
        break;
    case RT_CAN_BUS_ACK_ERR:/* attention !!! test ack err's unit is transmit unit */
        can->status.ackerrcnt++;
        break;
    case RT_CAN_BUS_IMPLICIT_BIT_ERR:
    case RT_CAN_BUS_EXPLICIT_BIT_ERR:
        can->status.biterrcnt++;
        break;
    case RT_CAN_BUS_CRC_ERR:
        can->status.crcerrcnt++;
        break;
    }
    _can_check_tx_complete(can);

    can->status.lasterrtype = errtype & 0x70;
    can->status.rcverrcnt = errtype >> 24;
    can->status.snderrcnt = (errtype >> 16 & 0xFF);
    can->status.errcode = errtype & 0x07;
    hcan->Instance->MSR |= CAN_MSR_ERRI;
}

/**
 * @internal
 * @brief The low-level ISR for CAN TX events on STM32.
 *
 * This function's sole responsibility is to check the hardware status flags
 * to determine which mailbox completed a transmission and whether it was
 * successful or failed. It then reports the specific event to the upper
 * framework layer via `rt_hw_can_isr()`.
 *
 * @note This ISR contains NO framework-level logic (e.g., buffer handling).
 *       It is a pure hardware event reporter, ensuring a clean separation
 *       of concerns between the driver and the framework.
 *
 * @param[in] can A pointer to the CAN device structure.
 * @return void
 */
static void _can_tx_isr(struct rt_can_device *can)
{
    CAN_HandleTypeDef *hcan;
    RT_ASSERT(can);
    hcan = &((struct stm32_can *)can->parent.user_data)->CanHandle;

    /*
     * Publish the terminal before clearing RQCP. _can_sendmsg() rejects a mailbox
     * while RQCP is pending, so an old terminal cannot complete a new owner.
     */
    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_RQCP0))
    {
        if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK0))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_TX_DONE | 0 << 8);
        }
        else
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        }
        /* Write 1 to Clear transmission status flag RQCPx */
        WRITE_REG(hcan->Instance->TSR, CAN_TSR_RQCP0);
    }
    else if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_RQCP1))
    {
        if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK1))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_TX_DONE | 1 << 8);
        }
        else
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        }
        /* Write 1 to Clear transmission status flag RQCPx */
        WRITE_REG(hcan->Instance->TSR, CAN_TSR_RQCP1);
    }
    else if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_RQCP2))
    {
        if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK2))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_TX_DONE | 2 << 8);
        }
        else
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        }
        /* Write 1 to Clear transmission status flag RQCPx */
        WRITE_REG(hcan->Instance->TSR, CAN_TSR_RQCP2);
    }
}

#ifdef BSP_USING_CAN1
/**
 * @brief This function handles CAN1 TX interrupts. transmit fifo0/1/2 is empty can trigger this interrupt
 */
void CAN1_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_tx_isr(&drv_can1.device);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX0 interrupts.
 */
void CAN1_RX0_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&drv_can1.device, CAN_RX_FIFO0);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX1 interrupts.
 */
void CAN1_RX1_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&drv_can1.device, CAN_RX_FIFO1);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 SCE interrupts.
 */
void CAN1_SCE_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_sce_isr(&drv_can1.device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
/**
 * @brief This function handles CAN2 TX interrupts.
 */
void CAN2_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_tx_isr(&drv_can2.device);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 RX0 interrupts.
 */
void CAN2_RX0_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&drv_can2.device, CAN_RX_FIFO0);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 RX1 interrupts.
 */
void CAN2_RX1_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_rx_isr(&drv_can2.device, CAN_RX_FIFO1);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 SCE interrupts.
 */
void CAN2_SCE_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_sce_isr(&drv_can2.device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN2 */

int rt_hw_can_init(void)
{
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 14;
#ifdef CAN2
    config.maxhdr = 28;
#endif /* CAN2 */
#endif /* RT_CAN_USING_HDR */
    /* config default filter */
    CAN_FilterTypeDef filterConf = { 0 };
    filterConf.FilterIdHigh = 0x0000;
    filterConf.FilterIdLow = 0x0000;
    filterConf.FilterMaskIdHigh = 0x0000;
    filterConf.FilterMaskIdLow = 0x0000;
    filterConf.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    filterConf.FilterBank = 0;
    filterConf.FilterMode = CAN_FILTERMODE_IDMASK;
    filterConf.FilterScale = CAN_FILTERSCALE_32BIT;
    filterConf.FilterActivation = ENABLE;
    filterConf.SlaveStartFilterBank = 14;

#ifdef BSP_USING_CAN1
    filterConf.FilterBank = 0;

    drv_can1.FilterConfig = filterConf;
    drv_can1.device.config = config;
    /* register CAN1 device */
    rt_hw_can_register(&drv_can1.device,
                       drv_can1.name,
                       &_can_ops,
                       &drv_can1);
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
    filterConf.FilterBank = filterConf.SlaveStartFilterBank;

    drv_can2.FilterConfig = filterConf;
    drv_can2.device.config = config;
    /* register CAN2 device */
    rt_hw_can_register(&drv_can2.device,
                       drv_can2.name,
                       &_can_ops,
                       &drv_can2);
#endif /* BSP_USING_CAN2 */

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */

/************************** end of file ******************/
