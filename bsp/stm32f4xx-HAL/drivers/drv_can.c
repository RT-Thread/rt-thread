/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-05     Xeon Xu      the first version
 */

/* Includes ------------------------------------------------------------------*/
#include "drv_can.h"
#include "board.h"
#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>

#define BS1SHIFT 16
#define BS2SHIFT 20
#define RRESCLSHIFT 0
#define SJWSHIFT 24
#define BS1MASK ( (0x0F) << BS1SHIFT )
#define BS2MASK ( (0x07) << BS2SHIFT )
#define RRESCLMASK ( 0x3FF << RRESCLSHIFT )
#define SJWMASK ( 0x3 << SJWSHIFT )

struct stm_baud_rate_tab
{
    rt_uint32_t baud_rate;
    rt_uint32_t confdata;
};

/* STM32 can driver */
struct stm32_drv_can
{
    CAN_HandleTypeDef CanHandle;
    CanTxMsgTypeDef TxMessage;
    CanRxMsgTypeDef RxMessage;
    CAN_FilterConfTypeDef FilterConfig;
};

static const struct stm_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud  , (CAN_SJW_1TQ | CAN_BS1_2TQ  | CAN_BS2_4TQ | 6)},
    {CAN800kBaud, (CAN_SJW_1TQ | CAN_BS1_5TQ  | CAN_BS2_7TQ | 4)},
    {CAN500kBaud, (CAN_SJW_1TQ | CAN_BS1_14TQ | CAN_BS2_6TQ | 4)},
    {CAN250kBaud, (CAN_SJW_1TQ | CAN_BS1_1TQ  | CAN_BS2_2TQ | 42)},
    {CAN125kBaud, (CAN_SJW_1TQ | CAN_BS1_1TQ  | CAN_BS2_2TQ | 84)},
    {CAN100kBaud, (CAN_SJW_1TQ | CAN_BS1_1TQ  | CAN_BS2_1TQ | 140)},
    {CAN50kBaud , (CAN_SJW_1TQ | CAN_BS1_1TQ  | CAN_BS2_1TQ | 280)},
    {CAN20kBaud , (CAN_SJW_1TQ | CAN_BS1_1TQ  | CAN_BS2_1TQ | 700)},
    {CAN10kBaud , (CAN_SJW_1TQ | CAN_BS1_3TQ  | CAN_BS2_4TQ | 525)}
};

#define BAUD_DATA(TYPE,NO)                              \
    ((can_baud_rate_tab[NO].confdata & TYPE##MASK))

static rt_uint32_t get_can_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index, default_index;

    len = sizeof(can_baud_rate_tab)/sizeof(can_baud_rate_tab[0]);
    default_index = len;

    for(index = 0; index < len; index++)
    {
        if(can_baud_rate_tab[index].baud_rate == baud)
            return index;

        if(can_baud_rate_tab[index].baud_rate == 1000UL * 250)
            default_index = index;
    }

    if(default_index != len)
        return default_index;

    return 0;
}

#ifdef USING_BXCAN1
static struct stm32_drv_can drv_can1;
struct rt_can_device dev_can1;
void CAN1_TX_IRQHandler(void)
{
    CAN_HandleTypeDef *hcan;

    rt_interrupt_enter();
    hcan = &drv_can1.CanHandle;

    HAL_CAN_IRQHandler(hcan);

    if (__HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_0))
    {
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_TX_DONE | 0 << 8);
    }
    else
    {
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_TX_FAIL | 0 << 8);
    }

    if (__HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_1))
    {
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_TX_DONE | 1 << 8);
    }
    else
    {
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_TX_FAIL | 1 << 8);
    }

    if (__HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_2))
    {
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_TX_DONE | 2 << 8);
    }
    else
    {
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_TX_FAIL | 2 << 8);
    }

    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX0 interrupts.
 */
void CAN1_RX0_IRQHandler(void)
{
    CAN_HandleTypeDef *hcan;

    hcan = &drv_can1.CanHandle;

    rt_interrupt_enter();
    HAL_CAN_IRQHandler(hcan);

    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FOV0))
    {
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_RXOF_IND | 0 << 8);
    }
    else
    {
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_RX_IND | 0 << 8);
    }

    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX1 interrupts.
 */
void CAN1_RX1_IRQHandler(void)
{
    CAN_HandleTypeDef *hcan;

    hcan = &drv_can1.CanHandle;

    rt_interrupt_enter();
    HAL_CAN_IRQHandler(hcan);

    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FOV1))
    {
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_RXOF_IND | 1 << 8);
    }
    else
    {
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_RX_IND | 1 << 8);
    }

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
#endif // USING_BXCAN1

#ifdef USING_BXCAN2
static struct stm32_drv_can drv_can2;
struct rt_can_device dev_can2;
/**
 * @brief This function handles CAN2 TX interrupts.
 */
void CAN2_TX_IRQHandler(void)
{
    CAN_HandleTypeDef *hcan;

    rt_interrupt_enter();
    hcan = &drv_can2.CanHandle;

    HAL_CAN_IRQHandler(hcan);

    if (__HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_0))
    {
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_TX_DONE | 0 << 8);
    }
    else
    {
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_TX_FAIL | 0 << 8);
    }

    if (__HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_1))
    {
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_TX_DONE | 1 << 8);
    }
    else
    {
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_TX_FAIL | 1 << 8);
    }

    if (__HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_2))
    {
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_TX_DONE | 2 << 8);
    }
    else
    {
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_TX_FAIL | 2 << 8);
    }

    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 RX0 interrupts.
 */
void CAN2_RX0_IRQHandler(void)
{
    CAN_HandleTypeDef *hcan;

    hcan = &drv_can2.CanHandle;

    rt_interrupt_enter();
    HAL_CAN_IRQHandler(hcan);

    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FOV0))
    {
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_RXOF_IND | 0 << 8);
    }
    else
    {
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_RX_IND | 0 << 8);
    }

    rt_interrupt_leave();

}

/**
 * @brief This function handles CAN2 RX1 interrupts.
 */
void CAN2_RX1_IRQHandler(void)
{
    CAN_HandleTypeDef *hcan;

    hcan = &drv_can2.CanHandle;

    rt_interrupt_enter();
    HAL_CAN_IRQHandler(hcan);

    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FOV1))
    {
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_RXOF_IND | 1 << 8);
    }
    else
    {
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_RX_IND | 1 << 8);
    }

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

#endif // USING_BXCAN2

/**
 * @brief  Error CAN callback.
 * @param  hcan pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
    __HAL_CAN_ENABLE_IT(hcan, CAN_IT_EWG |
                               CAN_IT_EPV |
                               CAN_IT_BOF |
                               CAN_IT_LEC |
                               CAN_IT_ERR |
                               CAN_IT_FMP0|
                               CAN_IT_FOV0|
                               CAN_IT_FMP1|
                               CAN_IT_FOV1|
                               CAN_IT_TME);
}

/**
 * @brief  Transmission  complete callback in non blocking mode
 * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void HAL_CAN_TxCpltCallback(CAN_HandleTypeDef* hcan)
{
    switch((int)hcan->Instance)
    {
    case (int)CAN1:
        /* User define */
        break;
    case (int)CAN2:
        /* User define */
        break;
    }
}

/**
 * @brief  Transmission  complete callback in non blocking mode
 * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
{
    HAL_CAN_Receive_IT(hcan, CAN_FIFO0);
    HAL_CAN_Receive_IT(hcan, CAN_FIFO1);
}

static rt_err_t drv_configure(struct rt_can_device *dev_can,
                              struct can_configure *cfg)
{
    struct stm32_drv_can *drv_can;
    rt_uint32_t baud_index;
    CAN_InitTypeDef *drv_init;
    CAN_FilterConfTypeDef *filterConf;

    RT_ASSERT(dev_can);
    RT_ASSERT(cfg);

    drv_can = (struct stm32_drv_can *)dev_can->parent.user_data;
    drv_init = &drv_can->CanHandle.Init;

    drv_init->TTCM = DISABLE;
    drv_init->ABOM = DISABLE;
    drv_init->AWUM = DISABLE;
    drv_init->NART = DISABLE;
    drv_init->RFLM = DISABLE;
    drv_init->TXFP = DISABLE;

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
    drv_init->SJW = BAUD_DATA(SJW, baud_index);
    drv_init->BS1 = BAUD_DATA(BS1, baud_index);
    drv_init->BS2 = BAUD_DATA(BS2, baud_index);
    drv_init->Prescaler = BAUD_DATA(RRESCL, baud_index);
    if (HAL_CAN_Init(&drv_can->CanHandle) != HAL_OK)
    {
        return RT_ERROR;
    }

    /* Filter conf */
    filterConf = &drv_can->FilterConfig;
    filterConf->FilterNumber = 0;
    filterConf->FilterMode = CAN_FILTERMODE_IDMASK;
    filterConf->FilterScale = CAN_FILTERSCALE_32BIT;
    filterConf->FilterIdHigh = 0x0000;
    filterConf->FilterIdLow = 0x0000;
    filterConf->FilterMaskIdHigh = 0x0000;
    filterConf->FilterMaskIdLow = 0x0000;
    filterConf->FilterFIFOAssignment = 0;
    filterConf->FilterActivation = ENABLE;
    filterConf->BankNumber = 14;
    HAL_CAN_ConfigFilter(&drv_can->CanHandle, filterConf);

    return RT_EOK;
}

static rt_err_t drv_control(struct rt_can_device *can, int cmd, void *arg)
{
    struct stm32_drv_can *drv_can;
    rt_uint32_t argval;

    drv_can = (struct stm32_drv_can *) can->parent.user_data;
    assert_param(drv_can != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            if (CAN1 == drv_can->CanHandle.Instance) {
                HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
                HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
            }
            else
            {
                HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
                HAL_NVIC_DisableIRQ(CAN2_RX1_IRQn);
            }
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_FMP0);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_FF0 );
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_FOV0);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_FMP1);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_FF1 );
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_FOV1);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            if (CAN1 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
            }
            else
            {
                HAL_NVIC_DisableIRQ(CAN2_TX_IRQn);
            }
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_TME);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            if (CAN1 == drv_can->CanHandle.Instance)
            {
                NVIC_DisableIRQ(CAN1_SCE_IRQn);
            }
            else
            {
                NVIC_DisableIRQ(CAN2_SCE_IRQn);
            }
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_BOF);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_LEC);
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_ERR);
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_FMP0);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_FF0);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_FOV0);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_FMP1);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_FF1);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_FOV1);

            if (CAN1 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
                HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
            }
            else
            {
                HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
                HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
            }
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_TME);

            if (CAN1 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_SetPriority(CAN1_TX_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
            }
            else
            {
                HAL_NVIC_SetPriority(CAN2_TX_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN2_TX_IRQn);
            }
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_BOF);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_LEC);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_ERR);

            if (CAN1 == drv_can->CanHandle.Instance)
            {
                HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
            }
            else
            {
                HAL_NVIC_SetPriority(CAN2_SCE_IRQn, 1, 0);
                HAL_NVIC_EnableIRQ(CAN2_SCE_IRQn);
            }
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
        /* TODO: filter*/
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
            if (HAL_CAN_Init(&drv_can->CanHandle) != HAL_OK)
            {
                return RT_ERROR;
            }
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
            CAN_InitTypeDef *drv_init;
            rt_uint32_t baud_index;

            can->config.baud_rate = argval;

            drv_init = &drv_can->CanHandle.Init;

            drv_init->TTCM = DISABLE;
            drv_init->ABOM = DISABLE;
            drv_init->AWUM = DISABLE;
            drv_init->NART = DISABLE;
            drv_init->RFLM = DISABLE;
            drv_init->TXFP = DISABLE;
            baud_index = get_can_baud_index(can->config.baud_rate);
            drv_init->SJW = BAUD_DATA(SJW, baud_index);
            drv_init->BS1 = BAUD_DATA(BS1, baud_index);
            drv_init->BS2 = BAUD_DATA(BS2, baud_index);
            drv_init->Prescaler = BAUD_DATA(RRESCL, baud_index);

            if (HAL_CAN_Init(&drv_can->CanHandle) != HAL_OK)
            {
                return RT_ERROR;
            }
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
            if (HAL_CAN_Init(&drv_can->CanHandle) != HAL_OK)
            {
                return RT_ERROR;
            }
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
    CAN_HandleTypeDef *hcan;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;

    hcan = &((struct stm32_drv_can *) can->parent.user_data)->CanHandle;
    hcan->pTxMsg->StdId = pmsg->id;
    hcan->pTxMsg->RTR = pmsg->rtr;
    hcan->pTxMsg->IDE = pmsg->ide;
    hcan->pTxMsg->DLC = pmsg->len;
    rt_memset(&hcan->pTxMsg->Data, 0x00, 8);
    /* rt_memcpy(&hcan->pTxMsg->Data, &pmsg->data, 8); */
    hcan->pTxMsg->Data[0] = pmsg->data[0];
    hcan->pTxMsg->Data[1] = pmsg->data[1];
    hcan->pTxMsg->Data[2] = pmsg->data[2];
    hcan->pTxMsg->Data[3] = pmsg->data[3];
    hcan->pTxMsg->Data[4] = pmsg->data[4];
    hcan->pTxMsg->Data[5] = pmsg->data[5];
    hcan->pTxMsg->Data[6] = pmsg->data[6];
    hcan->pTxMsg->Data[7] = pmsg->data[7];
    HAL_CAN_Transmit_IT(hcan);

    return RT_EOK;
}

static int drv_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    CAN_HandleTypeDef *hcan;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    hcan = &((struct stm32_drv_can *) can->parent.user_data)->CanHandle;

    pmsg->id = hcan->pRxMsg->StdId;
    pmsg->rtr = hcan->pRxMsg->RTR;
    pmsg->ide = hcan->pRxMsg->IDE;
    pmsg->len = hcan->pRxMsg->DLC;
    /* rt_memcpy(&pmsg->data, &hcan->pRxMsg->Data, 8); */
    pmsg->data[0] = hcan->pRxMsg->Data[0];
    pmsg->data[1] = hcan->pRxMsg->Data[1];
    pmsg->data[2] = hcan->pRxMsg->Data[2];
    pmsg->data[3] = hcan->pRxMsg->Data[3];
    pmsg->data[4] = hcan->pRxMsg->Data[4];
    pmsg->data[5] = hcan->pRxMsg->Data[5];
    pmsg->data[6] = hcan->pRxMsg->Data[6];
    pmsg->data[7] = hcan->pRxMsg->Data[7];

    return RT_EOK;
}

static const struct rt_can_ops drv_can_ops =
{
    drv_configure,
    drv_control,
    drv_sendmsg,
    drv_recvmsg,
};

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if(canHandle->Instance==CAN1)
    {
        /* CAN1 clock enable */
        __HAL_RCC_CAN1_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();

        /**CAN1 GPIO Configuration
           PD0     ------> CAN1_RX
           PD1     ------> CAN1_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);


    }
    else if(canHandle->Instance==CAN2)
    {
        /* CAN2 clock enable */
        __HAL_RCC_CAN2_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        /**CAN2 GPIO Configuration
           PB12     ------> CAN2_RX
           PB6     ------> CAN2_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


    }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

    if(canHandle->Instance==CAN1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_CAN1_CLK_DISABLE();

        /**CAN1 GPIO Configuration
           PD0     ------> CAN1_RX
           PD1     ------> CAN1_TX
        */
        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_2);
        HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
        HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
        HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
    }
    else if(canHandle->Instance==CAN2)
    {
        __HAL_RCC_CAN2_CLK_DISABLE();

        /**CAN2 GPIO Configuration
           PB12     ------> CAN2_RX
           PB6     ------> CAN2_TX
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_6);

        HAL_NVIC_DisableIRQ(CAN2_TX_IRQn);
        HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
        HAL_NVIC_DisableIRQ(CAN2_RX1_IRQn);
    }
}

int hw_can_init(void)
{
    struct stm32_drv_can *drv_can;
    struct can_configure config = CANDEFAULTCONFIG;

    config.privmode = 0;
    config.ticks = 50;
    config.sndboxnumber = 3;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 28;
#endif

#ifdef USING_BXCAN1
    drv_can = &drv_can1;
    drv_can->CanHandle.Instance = CAN1;
    drv_can->CanHandle.pTxMsg = &drv_can->TxMessage;
    drv_can->CanHandle.pRxMsg = &drv_can->RxMessage;
    dev_can1.ops    = &drv_can_ops;
    dev_can1.config = config;
    /* register CAN1 device */
    rt_hw_can_register(&dev_can1, "can1",
                       &drv_can_ops,
                       drv_can);
#endif /* USING_BXCAN1 */

#ifdef USING_BXCAN2
    drv_can = &drv_can2;
    drv_can->CanHandle.Instance = CAN2;
    drv_can->CanHandle.pTxMsg = &drv_can->TxMessage;
    drv_can->CanHandle.pRxMsg = &drv_can->RxMessage;
    dev_can2.ops    = &drv_can_ops;
    dev_can2.config = config;
    /* register CAN2 device */
    rt_hw_can_register(&dev_can2, "can2",
                       &drv_can_ops,
                       drv_can);
#endif /* USING_BXCAN2 */

    return 0;
}

INIT_BOARD_EXPORT(hw_can_init);

