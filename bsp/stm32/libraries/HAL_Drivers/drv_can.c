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
 */

#include "drv_can.h"

#ifdef RT_USING_CAN

#if defined (SOC_SERIES_STM32F1)
static const struct stm_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud  , (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 3)},
    {CAN800kBaud, (CAN_SJW_2TQ | CAN_BS1_5TQ  | CAN_BS2_3TQ | 5)},
    {CAN500kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 6)},
    {CAN250kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 12)},
    {CAN125kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 24)},
    {CAN100kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 30)},
    {CAN50kBaud , (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 60)},
    {CAN20kBaud , (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 150)},
    {CAN10kBaud , (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_3TQ | 300)}
};
#elif defined (SOC_SERIES_STM32F4)
static const struct stm_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud  , (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 3)},
    {CAN800kBaud, (CAN_SJW_2TQ | CAN_BS1_8TQ  | CAN_BS2_4TQ | 4)},
    {CAN500kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 6)},
    {CAN250kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 12)},
    {CAN125kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 24)},
    {CAN100kBaud, (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 30)},
    {CAN50kBaud , (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 60)},
    {CAN20kBaud , (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 150)},
    {CAN10kBaud , (CAN_SJW_2TQ | CAN_BS1_9TQ  | CAN_BS2_4TQ | 300)}
};
#endif

#define BAUD_DATA(TYPE,NO)                              \
    ((can_baud_rate_tab[NO].confdata & TYPE##MASK))

static rt_uint32_t get_can_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index, default_index;

    len = sizeof(can_baud_rate_tab) / sizeof(can_baud_rate_tab[0]);
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
    
    if (__HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_0))
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

    else if (__HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_1))
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
    
    else if (__HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_2))
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
    
    CanRxMsgTypeDef* pRxMsg = NULL;
    CAN_HandleTypeDef *hcan;
    hcan = &drv_can1.CanHandle;
    /* check FMP0 and get data */
    while (__HAL_CAN_MSG_PENDING(hcan, CAN_FIFO0) != RESET && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FMP0) != RESET)
    {
        /* beigin get data */
        
        /* Set RxMsg pointer */
        pRxMsg = hcan->pRxMsg;
         /* Get the Id */
        pRxMsg->IDE = (uint8_t)0x04U & hcan->Instance->sFIFOMailBox[CAN_FIFO0].RIR;
        if (pRxMsg->IDE == CAN_ID_STD)
        {
            pRxMsg->StdId = 0x000007FFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RIR >> 21U);
        }
        else
        {
            pRxMsg->ExtId = 0x1FFFFFFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RIR >> 3U);
        }
  
        pRxMsg->RTR = (uint8_t)0x02U & hcan->Instance->sFIFOMailBox[CAN_FIFO0].RIR;
        /* Get the DLC */
        pRxMsg->DLC = (uint8_t)0x0FU & hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDTR;
        /* Get the FIFONumber */
        pRxMsg->FIFONumber = CAN_FIFO0;
        /* Get the FMI */
        pRxMsg->FMI = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDTR >> 8U);
        /* Get the data field */
        pRxMsg->Data[0] = (uint8_t)0xFFU & hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDLR;
        pRxMsg->Data[1] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDLR >> 8U);
        pRxMsg->Data[2] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDLR >> 16U);
        pRxMsg->Data[3] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDLR >> 24U);
        pRxMsg->Data[4] = (uint8_t)0xFFU & hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDHR;
        pRxMsg->Data[5] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDHR >> 8U);
        pRxMsg->Data[6] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDHR >> 16U);
        pRxMsg->Data[7] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDHR >> 24U);
        
        /* Release FIFO0 */
        __HAL_CAN_FIFO_RELEASE(hcan, CAN_FIFO0);
        
        /* end get data */

        /* save to user fifo */
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_RX_IND | 0 << 8);
    }
    
    /* Check Overrun flag for FIFO0 */
    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FF0) != RESET && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FF0) != RESET)
    {
        /* Clear FIFO0 FULL Flag */
        __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FF0);
    }
    
    /* Check Overrun flag for FIFO0 */
    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FOV0) != RESET && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FOV0) != RESET)
    {
        /* Clear FIFO0 Overrun Flag */
        __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FOV0);
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_RXOF_IND | 0 << 8);
    }
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX1 interrupts.
 */
void CAN1_RX1_IRQHandler(void)
{
    rt_interrupt_enter();
    
    CanRxMsgTypeDef* pRxMsg = NULL;
    CAN_HandleTypeDef *hcan;
    hcan = &drv_can1.CanHandle;
    /* check FMP1 and get data */
    while (__HAL_CAN_MSG_PENDING(hcan, CAN_FIFO1) != RESET && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FMP1) != RESET)
    {
        /* beigin get data */
          
        /* Set RxMsg pointer */
        pRxMsg = hcan->pRx1Msg;
         /* Get the Id */
        pRxMsg->IDE = (uint8_t)0x04U & hcan->Instance->sFIFOMailBox[CAN_FIFO1].RIR;
        if (pRxMsg->IDE == CAN_ID_STD)
        {
            pRxMsg->StdId = 0x000007FFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RIR >> 21U);
        }
        else
        {
            pRxMsg->ExtId = 0x1FFFFFFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RIR >> 3U);
        }
  
        pRxMsg->RTR = (uint8_t)0x02U & hcan->Instance->sFIFOMailBox[CAN_FIFO1].RIR;
        /* Get the DLC */
        pRxMsg->DLC = (uint8_t)0x0FU & hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDTR;
        /* Get the FIFONumber */
        pRxMsg->FIFONumber = CAN_FIFO1;
        /* Get the FMI */
        pRxMsg->FMI = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDTR >> 8U);
        /* Get the data field */
        pRxMsg->Data[0] = (uint8_t)0xFFU & hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDLR;
        pRxMsg->Data[1] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDLR >> 8U);
        pRxMsg->Data[2] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDLR >> 16U);
        pRxMsg->Data[3] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDLR >> 24U);
        pRxMsg->Data[4] = (uint8_t)0xFFU & hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDHR;
        pRxMsg->Data[5] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDHR >> 8U);
        pRxMsg->Data[6] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDHR >> 16U);
        pRxMsg->Data[7] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDHR >> 24U);
        
        /* Release FIFO1 */
        __HAL_CAN_FIFO_RELEASE(hcan, CAN_FIFO1);
        
        /* end get data */

        /* save to user fifo */
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_RX_IND | 1 << 8);
    }
    
    /* Check Overrun flag for FIFO1 */
    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FF1) != RESET && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FF1) != RESET)
    {
        /* Clear FIFO1 FULL Flag */
        __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FF1);
    }
    
    /* Check Overrun flag for FIFO1 */
    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FOV1) != RESET && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FOV1) != RESET)
    {
        /* Clear FIFO1 Overrun Flag */
        __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FOV1);
        rt_hw_can_isr(&dev_can1, RT_CAN_EVENT_RXOF_IND | 1 << 8);
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
    
    if (__HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_0))
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

    else if (__HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_1))
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
    
    else if (__HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_2))
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
    
    CanRxMsgTypeDef* pRxMsg = NULL;
    CAN_HandleTypeDef *hcan;
    hcan = &drv_can2.CanHandle;
    /* check FMP0 and get data */
    while (__HAL_CAN_MSG_PENDING(hcan, CAN_FIFO0) != RESET && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FMP0) != RESET)
    {
        /* beigin get data */
        
        /* Set RxMsg pointer */
        pRxMsg = hcan->pRxMsg;
         /* Get the Id */
        pRxMsg->IDE = (uint8_t)0x04U & hcan->Instance->sFIFOMailBox[CAN_FIFO0].RIR;
        if (pRxMsg->IDE == CAN_ID_STD)
        {
            pRxMsg->StdId = 0x000007FFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RIR >> 21U);
        }
        else
        {
            pRxMsg->ExtId = 0x1FFFFFFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RIR >> 3U);
        }
  
        pRxMsg->RTR = (uint8_t)0x02U & hcan->Instance->sFIFOMailBox[CAN_FIFO0].RIR;
        /* Get the DLC */
        pRxMsg->DLC = (uint8_t)0x0FU & hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDTR;
        /* Get the FIFONumber */
        pRxMsg->FIFONumber = CAN_FIFO0;
        /* Get the FMI */
        pRxMsg->FMI = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDTR >> 8U);
        /* Get the data field */
        pRxMsg->Data[0] = (uint8_t)0xFFU & hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDLR;
        pRxMsg->Data[1] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDLR >> 8U);
        pRxMsg->Data[2] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDLR >> 16U);
        pRxMsg->Data[3] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDLR >> 24U);
        pRxMsg->Data[4] = (uint8_t)0xFFU & hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDHR;
        pRxMsg->Data[5] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDHR >> 8U);
        pRxMsg->Data[6] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDHR >> 16U);
        pRxMsg->Data[7] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO0].RDHR >> 24U);
        
        /* Release FIFO0 */
        __HAL_CAN_FIFO_RELEASE(hcan, CAN_FIFO0);
        
        /* end get data */

        /* save to user fifo */
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_RX_IND | 0 << 8);
    }
    
    /* Check Overrun flag for FIFO0 */
    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FF0) != RESET && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FF0) != RESET)
    {
        /* Clear FIFO0 FULL Flag */
        __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FF0);
    }
    
    /* Check Overrun flag for FIFO0 */
    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FOV0) != RESET && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FOV0) != RESET)
    {
        /* Clear FIFO0 Overrun Flag */
        __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FOV0);
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_RXOF_IND | 0 << 8);
    }
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN2 RX1 interrupts.
 */
void CAN2_RX1_IRQHandler(void)
{
    rt_interrupt_enter();
    
    CanRxMsgTypeDef* pRxMsg = NULL;
    CAN_HandleTypeDef *hcan;
    hcan = &drv_can2.CanHandle;
    /* check FMP1 and get data */
    while (__HAL_CAN_MSG_PENDING(hcan, CAN_FIFO1) != RESET && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FMP1) != RESET)
    {
        /* beigin get data */
          
        /* Set RxMsg pointer */
        pRxMsg = hcan->pRx1Msg;
         /* Get the Id */
        pRxMsg->IDE = (uint8_t)0x04U & hcan->Instance->sFIFOMailBox[CAN_FIFO1].RIR;
        if (pRxMsg->IDE == CAN_ID_STD)
        {
            pRxMsg->StdId = 0x000007FFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RIR >> 21U);
        }
        else
        {
            pRxMsg->ExtId = 0x1FFFFFFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RIR >> 3U);
        }
  
        pRxMsg->RTR = (uint8_t)0x02U & hcan->Instance->sFIFOMailBox[CAN_FIFO1].RIR;
        /* Get the DLC */
        pRxMsg->DLC = (uint8_t)0x0FU & hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDTR;
        /* Get the FIFONumber */
        pRxMsg->FIFONumber = CAN_FIFO1;
        /* Get the FMI */
        pRxMsg->FMI = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDTR >> 8U);
        /* Get the data field */
        pRxMsg->Data[0] = (uint8_t)0xFFU & hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDLR;
        pRxMsg->Data[1] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDLR >> 8U);
        pRxMsg->Data[2] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDLR >> 16U);
        pRxMsg->Data[3] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDLR >> 24U);
        pRxMsg->Data[4] = (uint8_t)0xFFU & hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDHR;
        pRxMsg->Data[5] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDHR >> 8U);
        pRxMsg->Data[6] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDHR >> 16U);
        pRxMsg->Data[7] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[CAN_FIFO1].RDHR >> 24U);
        
        /* Release FIFO1 */
        __HAL_CAN_FIFO_RELEASE(hcan, CAN_FIFO1);
        
        /* end get data */

        /* save to user fifo */
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_RX_IND | 1 << 8);
    }
    
    /* Check Overrun flag for FIFO1 */
    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FF1) != RESET && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FF1) != RESET)
    {
        /* Clear FIFO1 FULL Flag */
        __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FF1);
    }
    
    /* Check Overrun flag for FIFO1 */
    if (__HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FOV1) != RESET && __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FOV1) != RESET)
    {
        /* Clear FIFO1 Overrun Flag */
        __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FOV1);
        rt_hw_can_isr(&dev_can2, RT_CAN_EVENT_RXOF_IND | 1 << 8);
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
#endif /* BSP_USING_CAN2 */

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
    filterConf->FilterFIFOAssignment = CAN_FIFO0;
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
            #ifdef CAN2
            else
            {
                HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
                HAL_NVIC_DisableIRQ(CAN2_RX1_IRQn);
            }
            #endif
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
            #ifdef CAN2
            else
            {
                HAL_NVIC_DisableIRQ(CAN2_TX_IRQn);
            }
            #endif
            __HAL_CAN_DISABLE_IT(&drv_can->CanHandle, CAN_IT_TME);
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
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_TME);

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
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_BOF);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_LEC);
            __HAL_CAN_ENABLE_IT(&drv_can->CanHandle, CAN_IT_ERR);

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
    CAN_HandleTypeDef *hcan = RT_NULL;
    hcan = &((struct stm32_drv_can *) can->parent.user_data)->CanHandle;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    
    /*check Select mailbox  is empty */
    switch (boxno)
    {
        case CAN_TXMAILBOX_0:   
            if (HAL_IS_BIT_SET(hcan->Instance->TSR, CAN_TSR_TME0) != SET) 
            {    
                /* Change CAN state */
                hcan->State = HAL_CAN_STATE_ERROR;
                /* Return function status */
                return -RT_ERROR;
            }
            break;
        case CAN_TXMAILBOX_1:
            if (HAL_IS_BIT_SET(hcan->Instance->TSR, CAN_TSR_TME1) != SET) 
            {    
                /* Change CAN state */
                hcan->State = HAL_CAN_STATE_ERROR;
                /* Return function status */
                return -RT_ERROR;
            }
            break;
        case CAN_TXMAILBOX_2:
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
    
    /* check id type */
    if (RT_CAN_STDID == pmsg->ide)
    {
        hcan->pTxMsg->IDE = CAN_ID_STD;
        hcan->pTxMsg->StdId = pmsg->id;
        hcan->pTxMsg->ExtId = 0xFFFFFFFFU;
    }
    else if (RT_CAN_EXTID == pmsg->ide)
    {
        hcan->pTxMsg->IDE = CAN_ID_EXT;
        hcan->pTxMsg->StdId = 0xFFFFFFFFU;
        hcan->pTxMsg->ExtId = pmsg->id;
    }
       
    /* check frame type */
    if (RT_CAN_DTR == pmsg->rtr)
    {
        hcan->pTxMsg->RTR = CAN_RTR_DATA;
    }
    else if (RT_CAN_RTR == pmsg->rtr)
    {
        hcan->pTxMsg->RTR = CAN_RTR_REMOTE;
    }

    hcan->pTxMsg->DLC = pmsg->len;
    /* copy user data to hcan */
    hcan->pTxMsg->Data[0] = pmsg->data[0];
    hcan->pTxMsg->Data[1] = pmsg->data[1];
    hcan->pTxMsg->Data[2] = pmsg->data[2];
    hcan->pTxMsg->Data[3] = pmsg->data[3];
    hcan->pTxMsg->Data[4] = pmsg->data[4];
    hcan->pTxMsg->Data[5] = pmsg->data[5];
    hcan->pTxMsg->Data[6] = pmsg->data[6];
    hcan->pTxMsg->Data[7] = pmsg->data[7];
    
    /* clear TIR */
    hcan->Instance->sTxMailBox[boxno].TIR &= CAN_TI0R_TXRQ;
    /* Set up the Id */
    if (hcan->pTxMsg->IDE == CAN_ID_STD)
    {
      assert_param(IS_CAN_STDID(hcan->pTxMsg->StdId));
      hcan->Instance->sTxMailBox[boxno].TIR |= ((hcan->pTxMsg->StdId << CAN_TI0R_STID_Pos) | \
                                                           hcan->pTxMsg->RTR);
    }
    else
    {
      assert_param(IS_CAN_EXTID(hcan->pTxMsg->ExtId));
      hcan->Instance->sTxMailBox[boxno].TIR |= ((hcan->pTxMsg->ExtId << CAN_TI0R_EXID_Pos) | \
                                                           hcan->pTxMsg->IDE |
                                                           hcan->pTxMsg->RTR);
    }
    /* Set up the DLC */
    hcan->pTxMsg->DLC &= (uint8_t)0x0000000FU;
    hcan->Instance->sTxMailBox[boxno].TDTR &= 0xFFFFFFF0U;
    hcan->Instance->sTxMailBox[boxno].TDTR |= hcan->pTxMsg->DLC;

    /* Set up the data field */
    WRITE_REG(hcan->Instance->sTxMailBox[boxno].TDLR, ((uint32_t)hcan->pTxMsg->Data[3U] << CAN_TDL0R_DATA3_Pos) |
                                                                ((uint32_t)hcan->pTxMsg->Data[2U] << CAN_TDL0R_DATA2_Pos) |
                                                                ((uint32_t)hcan->pTxMsg->Data[1U] << CAN_TDL0R_DATA1_Pos) |
                                                                ((uint32_t)hcan->pTxMsg->Data[0U] << CAN_TDL0R_DATA0_Pos));
    WRITE_REG(hcan->Instance->sTxMailBox[boxno].TDHR, ((uint32_t)hcan->pTxMsg->Data[7U] << CAN_TDL0R_DATA3_Pos) |
                                                                ((uint32_t)hcan->pTxMsg->Data[6U] << CAN_TDL0R_DATA2_Pos) |
                                                                ((uint32_t)hcan->pTxMsg->Data[5U] << CAN_TDL0R_DATA1_Pos) |
                                                                ((uint32_t)hcan->pTxMsg->Data[4U] << CAN_TDL0R_DATA0_Pos));

    /* Request transmission */
    hcan->Instance->sTxMailBox[boxno].TIR |= CAN_TI0R_TXRQ;
    
    return RT_EOK;
}

static int drv_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    CAN_HandleTypeDef *hcan;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    hcan = &((struct stm32_drv_can *) can->parent.user_data)->CanHandle;
    CanRxMsgTypeDef *pRxMsg = RT_NULL;
    
    /* get FIFO */
    switch (boxno)
    {
        case CAN_FIFO0:
            pRxMsg = hcan->pRxMsg;
            break;
        case CAN_FIFO1:
            pRxMsg = hcan->pRx1Msg;
            break;
        default:
            RT_ASSERT(0);
            break;
    }
    
    /* copy data */
    /* get id */
    if (CAN_ID_STD == pRxMsg->IDE)
    {
        pmsg->ide = RT_CAN_STDID;
        pmsg->id = pRxMsg->StdId;
    }
    else if (CAN_ID_EXT == pRxMsg->IDE)
    {
        pmsg->ide = RT_CAN_EXTID;
        pmsg->id = pRxMsg->ExtId;
    }
    /* get type */
    if (CAN_RTR_DATA == pRxMsg->RTR)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else if (CAN_RTR_REMOTE == pRxMsg->RTR)
    {
        pmsg->rtr = RT_CAN_RTR;
    }
    /* get len */
    pmsg->len = pRxMsg->DLC;
    /* get hdr */
    pmsg->hdr = pRxMsg->FMI;
    /* get data */
    pmsg->data[0] = pRxMsg->Data[0];
    pmsg->data[1] = pRxMsg->Data[1];
    pmsg->data[2] = pRxMsg->Data[2];
    pmsg->data[3] = pRxMsg->Data[3];
    pmsg->data[4] = pRxMsg->Data[4];
    pmsg->data[5] = pRxMsg->Data[5];
    pmsg->data[6] = pRxMsg->Data[6];
    pmsg->data[7] = pRxMsg->Data[7];
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

#ifdef BSP_USING_CAN1
    drv_can = &drv_can1;
    drv_can->CanHandle.Instance = CAN1;
    drv_can->CanHandle.pTxMsg = &drv_can->TxMessage;
    drv_can->CanHandle.pRxMsg = &drv_can->RxMessage;
    drv_can->CanHandle.pRx1Msg = &drv_can->Rx1Message;
    dev_can1.ops    = &drv_can_ops;
    dev_can1.config = config;
    /* register CAN1 device */
    rt_hw_can_register(&dev_can1, "can1",
                       &drv_can_ops,
                       drv_can);
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
    drv_can = &drv_can2;
    drv_can->CanHandle.Instance = CAN2;
    drv_can->CanHandle.pTxMsg = &drv_can->TxMessage;
    drv_can->CanHandle.pRxMsg = &drv_can->RxMessage;
    drv_can->CanHandle.pRx1Msg = &drv_can->Rx1Message;
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
