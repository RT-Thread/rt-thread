/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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
 */

#include "drv_can.h"

#ifdef RT_USING_CAN

static void drv_rx_isr(struct rt_can_device *can, rt_uint32_t fifo);

#if defined (SOC_SERIES_STM32F1)
static const struct stm_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 3)},
    {CAN800kBaud, (CAN_SJW_2TQ | CAN_BS1_5TQ  | CAN_BS2_3TQ | 5)},
    {CAN500kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 6)},
    {CAN250kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 12)},
    {CAN125kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 24)},
    {CAN100kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 30)},
    {CAN50kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 60)},
    {CAN20kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 150)},
    {CAN10kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 300)}
};
#elif defined (SOC_STM32F429IG)
static const struct stm_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_5TQ | 3)},
    {CAN800kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_5TQ | 4)},
    {CAN500kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_5TQ | 6)},
    {CAN250kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_5TQ | 12)},
    {CAN125kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_5TQ | 24)},
    {CAN100kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_5TQ | 30)},
    {CAN50kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_5TQ | 60)},
    {CAN20kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_5TQ | 150)},
    {CAN10kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_5TQ | 300)}
};
#elif defined (SOC_SERIES_STM32F4)
static const struct stm_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 3)},
    {CAN800kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_4TQ | 4)},
    {CAN500kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 6)},
    {CAN250kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 12)},
    {CAN125kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 24)},
    {CAN100kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 30)},
    {CAN50kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 60)},
    {CAN20kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 150)},
    {CAN10kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 300)}
};
#endif

#define BAUD_DATA(TYPE,NO)                              \
    ((can_baud_rate_tab[NO].confdata & TYPE##MASK))

static rt_uint32_t get_can_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index, default_index;

    len = sizeof(can_baud_rate_tab) / sizeof(can_baud_rate_tab[0]);
    default_index = len;

    for (index = 0; index < len; index++)
    {
        if (can_baud_rate_tab[index].baud_rate == baud)
            return index;

        if (can_baud_rate_tab[index].baud_rate == 1000UL * 250)
            default_index = index;
    }

    if (default_index != len)
        return default_index;

    return 0;
}

#ifdef BSP_USING_CAN1
static struct stm32_drv_can drv_can1;
struct rt_can_device dev_can1;
/**
 * @brief This function handles CAN1 TX interrupts.
 */
void CAN1_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    CAN_HandleTypeDef *hcan;
    hcan = &drv_can1.CanHandle;
    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_RQCP0))
    {
        if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK0))
        {
            rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_TX_DONE | 0 << 8);
        }
        else
        {
            rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        SET_BIT(hcan->Instance->TSR, CAN_TSR_RQCP0);
    }
    else if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_RQCP1))
    {
        if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK1))
        {
            rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_TX_DONE | 1 << 8);
        }
        else
        {
            rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        SET_BIT(hcan->Instance->TSR, CAN_TSR_RQCP1);
    }
    else if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_RQCP2))
    {
        if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK2))
        {
            rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_TX_DONE | 2 << 8);
        }
        else
        {
            rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        SET_BIT(hcan->Instance->TSR, CAN_TSR_RQCP2);
    }
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX0 interrupts.
 */
void CAN1_RX0_IRQHandler(void)
{
    rt_interrupt_enter();
    drv_rx_isr(&dev_can1, CAN_RX_FIFO0);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX1 interrupts.
 */
void CAN1_RX1_IRQHandler(void)
{
    rt_interrupt_enter();
    drv_rx_isr(&dev_can1, CAN_RX_FIFO1);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 SCE interrupts.
 */
void CAN1_SCE_IRQHandler(void)
{
    rt_uint32_t errtype;
    CAN_HandleTypeDef *hcan;

    hcan = &drv_can1.CanHandle;
    errtype = hcan->Instance->ESR;

    rt_interrupt_enter();
    HAL_CAN_IRQHandler(hcan);

    if (errtype & 0x70 && dev_can1.status.lasterrtype == (errtype & 0x70))
    {
        switch ((errtype & 0x70) >> 4)
        {
        case RT_CAN_BUS_BIT_PAD_ERR:
            dev_can1.status.bitpaderrcnt++;
            break;
        case RT_CAN_BUS_FORMAT_ERR:
            dev_can1.status.formaterrcnt++;
            break;
        case RT_CAN_BUS_ACK_ERR:
            dev_can1.status.ackerrcnt++;
            break;
        case RT_CAN_BUS_IMPLICIT_BIT_ERR:
        case RT_CAN_BUS_EXPLICIT_BIT_ERR:
            dev_can1.status.biterrcnt++;
            break;
        case RT_CAN_BUS_CRC_ERR:
            dev_can1.status.crcerrcnt++;
            break;
        }
        dev_can1.status.lasterrtype = errtype & 0x70;
        hcan->Instance->ESR &= ~0x70;
    }
    dev_can1.status.rcverrcnt = errtype >> 24;
    dev_can1.status.snderrcnt = (errtype >> 16 & 0xFF);
    dev_can1.status.errcode = errtype & 0x07;
    hcan->Instance->MSR |= CAN_MSR_ERRI;
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
static struct stm32_drv_can drv_can2;
struct rt_can_device dev_can2;
/**
 * @brief This function handles CAN2 TX interrupts.
 */
void CAN2_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    CAN_HandleTypeDef *hcan;
    hcan = &drv_can2.CanHandle;
    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_RQCP0))
    {
        if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK0))
        {
            rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_TX_DONE | 0 << 8);
        }
        else
        {
            rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        SET_BIT(hcan->Instance->TSR, CAN_TSR_RQCP0);
    }
    else if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_RQCP1))
    {
        if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK1))
        {
            rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_TX_DONE | 1 << 8);
        }
        else
        {
            rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        SET_BIT(hcan->Instance->TSR, CAN_TSR_RQCP1);
    }
    else if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_RQCP2))
    {
        if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK2))
        {
            rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_TX_DONE | 2 << 8);
        }
        else
        {
            rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        }
        /* Write 0 to Clear transmission status flag RQCPx */
        SET_BIT(hcan->Instance->TSR, CAN_TSR_RQCP2);
    }
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 RX0 interrupts.
 */
void CAN2_RX0_IRQHandler(void)
{
    rt_interrupt_enter();
    drv_rx_isr(&dev_can2, CAN_RX_FIFO0);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 RX1 interrupts.
 */
void CAN2_RX1_IRQHandler(void)
{
    rt_interrupt_enter();
    drv_rx_isr(&dev_can2, CAN_RX_FIFO1);
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 SCE interrupts.
 */
void CAN2_SCE_IRQHandler(void)
{
    rt_uint32_t errtype;
    CAN_HandleTypeDef *hcan;

    hcan = &drv_can2.CanHandle;
    errtype = hcan->Instance->ESR;

    rt_interrupt_enter();
    HAL_CAN_IRQHandler(hcan);

    if (errtype & 0x70 && dev_can2.status.lasterrtype == (errtype & 0x70))
    {
        switch ((errtype & 0x70) >> 4)
        {
        case RT_CAN_BUS_BIT_PAD_ERR:
            dev_can2.status.bitpaderrcnt++;
            break;
        case RT_CAN_BUS_FORMAT_ERR:
            dev_can2.status.formaterrcnt++;
            break;
        case RT_CAN_BUS_ACK_ERR:
            dev_can2.status.ackerrcnt++;
            break;
        case RT_CAN_BUS_IMPLICIT_BIT_ERR:
        case RT_CAN_BUS_EXPLICIT_BIT_ERR:
            dev_can2.status.biterrcnt++;
            break;
        case RT_CAN_BUS_CRC_ERR:
            dev_can2.status.crcerrcnt++;
            break;
        }
        dev_can2.status.lasterrtype = errtype & 0x70;
        hcan->Instance->ESR &= ~0x70;
    }
    dev_can2.status.rcverrcnt = errtype >> 24;
    dev_can2.status.snderrcnt = (errtype >> 16 & 0xFF);
    dev_can2.status.errcode = errtype & 0x07;
    hcan->Instance->MSR |= CAN_MSR_ERRI;
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN2 */

/**
 * @brief  Error CAN callback.
 * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
    __HAL_CAN_ENABLE_IT(hcan,  CAN_IT_ERROR_WARNING |
                               CAN_IT_ERROR_PASSIVE |
                               CAN_IT_BUSOFF |
                               CAN_IT_LAST_ERROR_CODE |
                               CAN_IT_ERROR |
                               CAN_IT_RX_FIFO0_MSG_PENDING|
                               CAN_IT_RX_FIFO0_OVERRUN|
                               CAN_IT_RX_FIFO1_MSG_PENDING|
                               CAN_IT_RX_FIFO1_OVERRUN|
                               CAN_IT_TX_MAILBOX_EMPTY);
}




static rt_err_t drv_configure(struct rt_can_device *dev_can,
                              struct can_configure *cfg)
{
    struct stm32_drv_can *drv_can;
    rt_uint32_t baud_index;
    CAN_InitTypeDef *drv_init;

    RT_ASSERT(dev_can);
    RT_ASSERT(cfg);

    drv_can = (struct stm32_drv_can *)dev_can->parent.user_data;
    drv_init = &drv_can->CanHandle.Init;

    drv_init->TimeTriggeredMode = DISABLE;
    drv_init->AutoBusOff = ENABLE;
    drv_init->AutoWakeUp = DISABLE;
    drv_init->AutoRetransmission = DISABLE;
    drv_init->ReceiveFifoLocked = DISABLE;
    drv_init->TransmitFifoPriority = ENABLE;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        drv_init->Mode = CAN_MODE_NORMAL;
        break;
    case RT_CAN_MODE_LISEN:
        drv_init->Mode = CAN_MODE_SILENT;
        break;
    case RT_CAN_MODE_LOOPBACK:
        drv_init->Mode = CAN_MODE_LOOPBACK;
        break;
    case RT_CAN_MODE_LOOPBACKANLISEN:
        drv_init->Mode = CAN_MODE_SILENT_LOOPBACK;
        break;
    }

    baud_index = get_can_baud_index(cfg->baud_rate);
    drv_init->SyncJumpWidth = BAUD_DATA(SJW, baud_index);
    drv_init->TimeSeg1 = BAUD_DATA(BS1, baud_index);
    drv_init->TimeSeg2 = BAUD_DATA(BS2, baud_index);
    drv_init->Prescaler = BAUD_DATA(RRESCL, baud_index);
    if (HAL_CAN_Init(&drv_can->CanHandle) != HAL_OK)
    {
        return RT_ERROR;
    }
    
    /* Filter conf */
    HAL_CAN_ConfigFilter(&drv_can->CanHandle, &drv_can->FilterConfig);
    /* can start */
    HAL_CAN_Start(&drv_can->CanHandle);
    return RT_EOK;
}

static rt_err_t drv_control(struct rt_can_device *can, int cmd, void *arg)
{
    struct stm32_drv_can *drv_can = RT_NULL;
    rt_uint32_t argval;
    struct rt_can_filter_config *filter_cfg = RT_NULL;
    CAN_FilterTypeDef can_filter;
    drv_can = (struct stm32_drv_can *) can->parent.user_data;
    assert_param(drv_can != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            if (CAN1 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
                HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
            }
            #ifdef CAN2
            else
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
            else
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
            else
            {
                NVIC_DisableIRQ(CAN2_SCE_IRQn);
            }
            #endif
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_BUSOFF);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_LAST_ERROR_CODE);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_ERROR);
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
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
            else
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
            else
            {
                HAL_NVIC_SetPriority(CAN2_TX_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN2_TX_IRQn);
            }
            #endif
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_BUSOFF);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_LAST_ERROR_CODE);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_ERROR);

            if (CAN1 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
            }
            #ifdef CAN2
            else
            {
                HAL_NVIC_SetPriority(CAN2_SCE_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN2_SCE_IRQn);
            }
            #endif
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
        if (RT_NULL == arg)
        {
            /* default Filter conf */
            HAL_CAN_ConfigFilter(&drv_can->CanHandle, &drv_can->FilterConfig);
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            /* get default filter */
            can_filter = drv_can->FilterConfig;
            for (int i = 0; i < filter_cfg->count; ++i)
            {
                can_filter.FilterBank = filter_cfg->items[i].hdr;
                can_filter.FilterIdHigh = (filter_cfg->items[i].id >> 13) & 0xFFFF;
                can_filter.FilterIdLow = ((filter_cfg->items[i].id << 3) | 
                                         (filter_cfg->items[i].ide << 2) | 
                                         (filter_cfg->items[i].rtr << 1)) & 0xFFFF;
                can_filter.FilterMaskIdHigh = (filter_cfg->items[i].mask >> 16) & 0xFFFF;
                can_filter.FilterMaskIdLow = filter_cfg->items[i].mask & 0xFFFF;
                can_filter.FilterMode = filter_cfg->items[i].mode;
                /* Filter conf */
                HAL_CAN_ConfigFilter(&drv_can->CanHandle, &can_filter);
            }
        }
        break;
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL ||
            argval != RT_CAN_MODE_LISEN ||
            argval != RT_CAN_MODE_LOOPBACK ||
            argval != RT_CAN_MODE_LOOPBACKANLISEN)
        {
            return RT_ERROR;
        }
        if (argval != can->config.mode)
        {
            can->config.mode = argval;
            return drv_configure(can, &can->config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t) arg;
        if (argval != CAN1MBaud &&
            argval != CAN800kBaud &&
            argval != CAN500kBaud &&
            argval != CAN250kBaud &&
            argval != CAN125kBaud &&
            argval != CAN100kBaud &&
            argval != CAN50kBaud  &&
            argval != CAN20kBaud  &&
            argval != CAN10kBaud)
        {
            return RT_ERROR;
        }
        if (argval != can->config.baud_rate)
        {
            can->config.baud_rate = argval;
            return drv_configure(can, &can->config);
        }
        break;
    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_PRIV ||
            argval != RT_CAN_MODE_NOPRIV)
        {
            return RT_ERROR;
        }
        if (argval != can->config.privmode)
        {
            can->config.privmode = argval;
            return drv_configure(can, &can->config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
    {
        rt_uint32_t errtype;
        errtype = drv_can->CanHandle.Instance->ESR;
        can->status.rcverrcnt = errtype >> 24;
        can->status.snderrcnt = (errtype >> 16 & 0xFF);
        can->status.errcode = errtype & 0x07;
        if (arg != &can->status)
        {
            rt_memcpy(arg, &can->status, sizeof(can->status));
        }
    }
    break;
    }

    return RT_EOK;
}

static int drv_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    CAN_HandleTypeDef *hcan = RT_NULL;
    hcan = &((struct stm32_drv_can *) can->parent.user_data)->CanHandle;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    CAN_TxHeaderTypeDef txheader = {0};
    
    /*check Select mailbox  is empty */
    switch (1 << boxno)
    {
        case CAN_TX_MAILBOX0:   
            if (HAL_IS_BIT_SET(hcan->Instance->TSR, CAN_TSR_TME0) != SET) 
            {    
                /* Change CAN state */
                hcan->State = HAL_CAN_STATE_ERROR;
                /* Return function status */
                return -RT_ERROR;
            }
            break;
        case CAN_TX_MAILBOX1:
            if (HAL_IS_BIT_SET(hcan->Instance->TSR, CAN_TSR_TME1) != SET) 
            {    
                /* Change CAN state */
                hcan->State = HAL_CAN_STATE_ERROR;
                /* Return function status */
                return -RT_ERROR;
            }
            break;
        case CAN_TX_MAILBOX2:
            if (HAL_IS_BIT_SET(hcan->Instance->TSR, CAN_TSR_TME2) != SET) 
            {    
                /* Change CAN state */
                hcan->State = HAL_CAN_STATE_ERROR;
                /* Return function status */
                return -RT_ERROR;
            }
            break;
        default:
            RT_ASSERT(0);
            break;
    }
    
    if (RT_CAN_STDID == pmsg->ide)
    {
        txheader.IDE = CAN_ID_STD;
        txheader.StdId = pmsg->id;
    }
    else
    {
        txheader.IDE = CAN_ID_EXT;
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
    hcan->Instance->sTxMailBox[boxno].TIR &= CAN_TI0R_TXRQ;
    /* Set up the Id */
    if (RT_CAN_STDID == pmsg->ide)
    {
        hcan->Instance->sTxMailBox[boxno].TIR |= (txheader.StdId << CAN_TI0R_STID_Pos) | txheader.IDE | txheader.RTR;
    }
    else
    {
        hcan->Instance->sTxMailBox[boxno].TIR |= (txheader.ExtId << CAN_TI0R_EXID_Pos) | txheader.IDE | txheader.RTR;
    }
    /* Set up the DLC */
    hcan->Instance->sTxMailBox[boxno].TDTR = pmsg->len & 0x0FU;
    /* Set up the data field */
    WRITE_REG(hcan->Instance->sTxMailBox[boxno].TDHR,
            ((uint32_t)pmsg->data[7] << CAN_TDH0R_DATA7_Pos) |
            ((uint32_t)pmsg->data[6] << CAN_TDH0R_DATA6_Pos) |
            ((uint32_t)pmsg->data[5] << CAN_TDH0R_DATA5_Pos) |
            ((uint32_t)pmsg->data[4] << CAN_TDH0R_DATA4_Pos));
    WRITE_REG(hcan->Instance->sTxMailBox[boxno].TDLR,
            ((uint32_t)pmsg->data[3] << CAN_TDL0R_DATA3_Pos) |
            ((uint32_t)pmsg->data[2] << CAN_TDL0R_DATA2_Pos) |
            ((uint32_t)pmsg->data[1] << CAN_TDL0R_DATA1_Pos) |
            ((uint32_t)pmsg->data[0] << CAN_TDL0R_DATA0_Pos));
    /* Request transmission */
    SET_BIT(hcan->Instance->sTxMailBox[boxno].TIR, CAN_TI0R_TXRQ);
    return RT_EOK;
}

static void drv_rx_isr(struct rt_can_device *can, rt_uint32_t fifo)
{
    CAN_HandleTypeDef *hcan;
    hcan = &((struct stm32_drv_can *) can->parent.user_data)->CanHandle;
    
    switch (fifo)
    {
    case CAN_RX_FIFO0:
        /* save to user list */
        if (HAL_CAN_GetRxFifoFillLevel(hcan, CAN_RX_FIFO0) && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_RX_FIFO0_MSG_PENDING))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
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
        /* save to user list */
        if (HAL_CAN_GetRxFifoFillLevel(hcan, CAN_RX_FIFO1) && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_RX_FIFO1_MSG_PENDING))
        {
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
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

static int drv_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    HAL_StatusTypeDef status;
    CAN_HandleTypeDef *hcan = RT_NULL;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    hcan = &((struct stm32_drv_can *) can->parent.user_data)->CanHandle;
    CAN_RxHeaderTypeDef rxheader = {0};
    /* get data */
    status = HAL_CAN_GetRxMessage(hcan, fifo, &rxheader, pmsg->data);
    if (HAL_OK != status) return -RT_ERROR;
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
    /* get len */
    pmsg->len = rxheader.DLC;
    /* get hdr */
    pmsg->hdr = rxheader.FilterMatchIndex;
    return RT_EOK;
}

static const struct rt_can_ops drv_can_ops =
{
    drv_configure,
    drv_control,
    drv_sendmsg,
    drv_recvmsg,
};

int rt_hw_can_init(void)
{
    struct stm32_drv_can *drv_can;
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = 0;
    config.ticks = 50;
    config.sndboxnumber = 3;
    config.msgboxsz = 32;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 14;
    #ifdef CAN2
    config.maxhdr = 28;
    #endif
#endif
    /* config default filter */
    CAN_FilterTypeDef filterConf = {0};
    filterConf.FilterBank = 0;
    filterConf.FilterMode = CAN_FILTERMODE_IDMASK;
    filterConf.FilterScale = CAN_FILTERSCALE_32BIT;
    filterConf.FilterIdHigh = 0x0000;
    filterConf.FilterIdLow = 0x0000;
    filterConf.FilterMaskIdHigh = 0x0000;
    filterConf.FilterMaskIdLow = 0x0000;
    filterConf.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    filterConf.FilterActivation = ENABLE;
    filterConf.SlaveStartFilterBank = 14;
    
#ifdef BSP_USING_CAN1
    filterConf.FilterBank = 0;
    drv_can1.FilterConfig = filterConf;
    drv_can = &drv_can1;
    drv_can->CanHandle.Instance = CAN1;
    dev_can1.ops    = &drv_can_ops;
    dev_can1.config = config;
    /* register CAN1 device */
    rt_hw_can_register(&dev_can1, "can1",
                       &drv_can_ops,
                       drv_can);
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
    filterConf.FilterBank = filterConf.SlaveStartFilterBank;
    drv_can2.FilterConfig = filterConf;
    drv_can = &drv_can2;
    drv_can->CanHandle.Instance = CAN2;
    dev_can2.ops    = &drv_can_ops;
    dev_can2.config = config;
    /* register CAN2 device */
    rt_hw_can_register(&dev_can2, "can2",
                       &drv_can_ops,
                       drv_can);
#endif /* BSP_USING_CAN2 */

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_can_init);
#endif /* RT_USING_CAN */
