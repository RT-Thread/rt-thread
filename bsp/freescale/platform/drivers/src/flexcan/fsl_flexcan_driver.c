/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_flexcan_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_FLEXCAN_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Pointer to runtime state structure.*/
flexcan_state_t * g_flexcanStatePtr[CAN_INSTANCE_COUNT] = { NULL };

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static flexcan_status_t FLEXCAN_DRV_StartSendData(
                    uint8_t instance,
                    uint32_t mb_idx,
                    flexcan_data_info_t *tx_info,
                    uint32_t msg_id,
                    uint8_t *mb_data
                    );
static flexcan_status_t FLEXCAN_DRV_StartRxMessageBufferData(
                    uint8_t instance,
                    uint32_t mb_idx,
                    flexcan_msgbuff_t *data
                    );
static flexcan_status_t FLEXCAN_DRV_StartRxMessageFifoData(
                    uint8_t instance,
                    flexcan_msgbuff_t *data
                    );
static void FLEXCAN_DRV_CompleteSendData(uint32_t instance);
static void FLEXCAN_DRV_CompleteRxMessageBufferData(uint32_t instance);
static void FLEXCAN_DRV_CompleteRxMessageFifoData(uint32_t instance);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_SetBitrate
 * Description   : Set FlexCAN baudrate.
 * This function will set up all the time segment values. Those time segment
 * values are passed in by the user and are based on the required baudrate.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_SetBitrate(uint8_t instance, flexcan_time_segment_t *bitrate)
{
    assert(instance < CAN_INSTANCE_COUNT);

    /* Set time segments*/
    FLEXCAN_HAL_SetTimeSegments(g_flexcanBase[instance], bitrate);

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_GetBitrate
 * Description   : Get FlexCAN baudrate.
 * This function will be return the current bit rate settings
 *
 *END**************************************************************************/
flexcan_status_t  FLEXCAN_DRV_GetBitrate(uint8_t instance, flexcan_time_segment_t *bitrate)
{
    assert(instance < CAN_INSTANCE_COUNT);

    /* Get the time segments*/
    FLEXCAN_HAL_GetTimeSegments(g_flexcanBase[instance], bitrate);

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_SetMasktype
 * Description   : Set RX masking type.
 * This function will set RX masking type as RX global mask or RX individual
 * mask.
 *
 *END**************************************************************************/
void  FLEXCAN_DRV_SetRxMaskType(uint8_t instance, flexcan_rx_mask_type_t type)
{
    assert(instance < CAN_INSTANCE_COUNT);

    FLEXCAN_HAL_SetRxMaskType(g_flexcanBase[instance], type);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_SetRxFifoGlobalMask
 * Description   : Set Rx FIFO global mask as the 11-bit standard mask or the
 * 29-bit extended mask.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_SetRxFifoGlobalMask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mask)
{
    assert(instance < CAN_INSTANCE_COUNT);

    CAN_Type * base = g_flexcanBase[instance];

    if (id_type == kFlexCanMsgIdStd)
    {
        /* Set standard global mask for RX FIOF*/
        FLEXCAN_HAL_SetRxFifoGlobalStdMask(base, mask);
    }
    else if (id_type == kFlexCanMsgIdExt)
    {
        /* Set extended global mask for RX FIFO*/
        FLEXCAN_HAL_SetRxFifoGlobalExtMask(base, mask);
    }
    else
    {
        return kStatus_FLEXCAN_InvalidArgument;
    }

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_SetRxMbGlobalMask
 * Description   : Set Rx Message Buffer global mask as the 11-bit standard mask
 * or the 29-bit extended mask.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_SetRxMbGlobalMask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mask)
{
    assert(instance < CAN_INSTANCE_COUNT);

    CAN_Type * base = g_flexcanBase[instance];

    if (id_type == kFlexCanMsgIdStd)
    {
        /* Set standard global mask for RX MB*/
        FLEXCAN_HAL_SetRxMsgBuffGlobalStdMask(base, mask);
    }
    else if (id_type == kFlexCanMsgIdExt)
    {
        /* Set extended global mask for RX MB*/
        FLEXCAN_HAL_SetRxMsgBuffGlobalExtMask(base, mask);
    }
    else
    {
        return kStatus_FLEXCAN_InvalidArgument;
    }

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_SetRxIndividualMask
 * Description   : Set Rx individual mask as the 11-bit standard mask or the
 * 29-bit extended mask.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_SetRxIndividualMask(
    uint8_t instance,
    flexcan_msgbuff_id_type_t id_type,
    uint32_t mb_idx,
    uint32_t mask)
{
    assert(instance < CAN_INSTANCE_COUNT);

    CAN_Type * base = g_flexcanBase[instance];

    if (id_type == kFlexCanMsgIdStd)
    {
        /* Set standard individual mask*/
        return FLEXCAN_HAL_SetRxIndividualStdMask(base, mb_idx, mask);
    }
    else if (id_type == kFlexCanMsgIdExt)
    {
        /* Set extended individual mask*/
        return FLEXCAN_HAL_SetRxIndividualExtMask(base, mb_idx, mask);
    }
    else
    {
        return kStatus_FLEXCAN_InvalidArgument;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_Init
 * Description   : Initialize FlexCAN driver.
 * This function will select a source clock, reset FlexCAN module, set maximum
 * number of message buffers, initialize all message buffers as inactive, enable
 * RX FIFO if needed, mask all mask bits, disable all MB interrupts, enable
 * FlexCAN normal mode, and enable all the error interrupts if needed.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_Init(
   uint32_t instance,
   flexcan_state_t *state,
   const flexcan_user_config_t *data)
{
    assert(instance < CAN_INSTANCE_COUNT);
    assert(state);

    flexcan_status_t result;
    CAN_Type * base = g_flexcanBase[instance];

    /* Enable clock gate to FlexCAN module */
    CLOCK_SYS_EnableFlexcanClock(instance);

    /* Select a source clock for FlexCAN*/
    result = FLEXCAN_HAL_SelectClock(base, kFlexCanClkSourceIpbus);
    if (result)
    {
        return result;
    }

    /* Enable the CAN clock */
    FLEXCAN_HAL_Enable(base);

    /* Initialize FLEXCAN device */
    result = FLEXCAN_HAL_Init(base);
    if (result)
    {
        return result;
    }

    FLEXCAN_HAL_SetMaxMsgBuffNum(base, data->max_num_mb);
    if (data->is_rx_fifo_needed)
    {
        FLEXCAN_HAL_EnableRxFifo(base, data->num_id_filters);
    }
    /* Select mode */
    result = FLEXCAN_HAL_SetOperationMode(base, data->flexcanMode);
    if (result)
    {
        return result;
    }

    /* Init the interrupt sync object.*/
    OSA_SemaCreate(&state->txIrqSync, 0);
    OSA_SemaCreate(&state->rxIrqSync, 0);
    /* Enable FlexCAN interrupts.*/
    INT_SYS_EnableIRQ(g_flexcanWakeUpIrqId[instance]);
    INT_SYS_EnableIRQ(g_flexcanErrorIrqId[instance]);
    INT_SYS_EnableIRQ(g_flexcanBusOffIrqId[instance]);
    INT_SYS_EnableIRQ(g_flexcanOredMessageBufferIrqId[instance]);

    state->isTxBusy = false;
    state->isRxBusy = false;
    state->fifo_message = NULL;
    state->rx_mb_idx = 0;
    state->tx_mb_idx = 0;
    /* Save runtime structure pointers so irq handler can point to the correct state structure */
    g_flexcanStatePtr[instance] = state;

    return (kStatus_FLEXCAN_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_ConfigTxMb
 * Description   : Configure a Tx message buffer.
 * This function will first check if RX FIFO is enabled. If RX FIFO is enabled,
 * the function will make sure if the MB requested is not occupied by RX FIFO
 * and ID filter table. Then this function will set up the message buffer fields,
 * configure the message buffer code for Tx buffer as INACTIVE, and enable the
 * Message Buffer interrupt.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_ConfigTxMb(
    uint8_t instance,
    uint32_t mb_idx,
    flexcan_data_info_t *tx_info,
    uint32_t msg_id)
{
    assert(instance < CAN_INSTANCE_COUNT);

    flexcan_msgbuff_code_status_t cs;
    CAN_Type * base = g_flexcanBase[instance];
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    state->tx_mb_idx = mb_idx;
    /* Initialize transmit mb*/
    cs.dataLen = tx_info->data_length;
    cs.msgIdType = tx_info->msg_id_type;
    cs.code = kFlexCanTXInactive;
    return FLEXCAN_HAL_SetTxMsgBuff(base, mb_idx, &cs, msg_id, NULL);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_Send_Blocking
 * Description   : Set up FlexCAN Message buffer for transmitting data.
 * This function will set the MB CODE field as DATA for Tx buffer. Then this
 * function will copy user's buffer into the message buffer data area, and wait
 * for the Message Buffer interrupt.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_SendBlocking(
    uint8_t instance,
    uint32_t mb_idx,
    flexcan_data_info_t *tx_info,
    uint32_t msg_id,
    uint8_t *mb_data,
    uint32_t timeout_ms)
{
    assert(instance < CAN_INSTANCE_COUNT);

    flexcan_status_t result;
    flexcan_state_t * state = g_flexcanStatePtr[instance];
    CAN_Type * base  = g_flexcanBase[instance];
    osa_status_t syncStatus;

    state->isTxBlocking = true;
    result = FLEXCAN_DRV_StartSendData(instance, mb_idx, tx_info, msg_id, mb_data);
    if(result == kStatus_FLEXCAN_Success)
    {
        /* Enable message buffer interrupt*/
        FLEXCAN_HAL_SetMsgBuffIntCmd(base, mb_idx, true);
		/* Enable error interrupts */
		FLEXCAN_HAL_SetErrIntCmd(base,kFlexCanIntErr,true);
        do
        {
            syncStatus = OSA_SemaWait(&state->txIrqSync, timeout_ms);
        }while(syncStatus == kStatus_OSA_Idle);

        /* Wait for the interrupt*/
        if (syncStatus != kStatus_OSA_Success)
        {
            return kStatus_FLEXCAN_TimeOut;
        }
    }
    else
    {
        return result;
    }

    return (kStatus_FLEXCAN_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_Send
 * Description   : Set up FlexCAN Message buffer for transmitting data.
 * This function will set the MB CODE field as DATA for Tx buffer. Then this
 * function will copy user's buffer into the message buffer data area.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_Send(
    uint8_t instance,
    uint32_t mb_idx,
    flexcan_data_info_t *tx_info,
    uint32_t msg_id,
    uint8_t *mb_data)
{
    assert(instance < CAN_INSTANCE_COUNT);

    flexcan_status_t result;
    flexcan_state_t * state = g_flexcanStatePtr[instance];
    CAN_Type * base = g_flexcanBase[instance];

    state->isTxBlocking = false;

    result = FLEXCAN_DRV_StartSendData(instance, mb_idx, tx_info, msg_id, mb_data);
    if(result == kStatus_FLEXCAN_Success)
    {
        /* Enable message buffer interrupt*/
        FLEXCAN_HAL_SetMsgBuffIntCmd(base, mb_idx, true);
		/* Enable error interrupts */
		FLEXCAN_HAL_SetErrIntCmd(base,kFlexCanIntErr,true);
    }
    else
    {
        return result;
    }

    return (kStatus_FLEXCAN_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_ConfigMb
 * Description   : Configure a Rx message buffer.
 * This function will first check if RX FIFO is enabled. If RX FIFO is enabled,
 * the function will make sure if the MB requested is not occupied by RX FIFO
 * and ID filter table. Then this function will set up the message buffer fields,
 * configure the message buffer code for Rx message buffer as NOT_USED, enable
 * the Message Buffer interrupt, configure the message buffer code for Rx
 * message buffer as INACTIVE, copy user's buffer into the message buffer data
 * area, and configure the message buffer code for Rx message buffer as EMPTY.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_ConfigRxMb(
    uint8_t instance,
    uint32_t mb_idx,
    flexcan_data_info_t *rx_info,
    uint32_t msg_id)
{
    assert(instance < CAN_INSTANCE_COUNT);

    flexcan_status_t result;
    flexcan_msgbuff_code_status_t cs;
    CAN_Type * base = g_flexcanBase[instance];
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    state->rx_mb_idx = mb_idx;
    cs.dataLen = rx_info->data_length;
    cs.msgIdType = rx_info->msg_id_type;

    /* Initialize rx mb*/
    cs.code = kFlexCanRXNotUsed;
    result = FLEXCAN_HAL_SetRxMsgBuff(base, mb_idx, &cs, msg_id);
    if (result)
    {
         return result;
    }

    /* Initialize receive MB*/
    cs.code = kFlexCanRXInactive;
    result = FLEXCAN_HAL_SetRxMsgBuff(base, mb_idx, &cs, msg_id);
    if (result)
    {
         return result;
    }

    /* Set up FlexCAN message buffer fields for receiving data*/
    cs.code = kFlexCanRXEmpty;
    return FLEXCAN_HAL_SetRxMsgBuff(base, mb_idx, &cs, msg_id);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_ConfigRxFifo
 * Description   : Confgure RX FIFO ID filter table elements.
 * This function will confgure RX FIFO ID filter table elements, and enable RX
 * FIFO interrupts.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_ConfigRxFifo(
    uint8_t instance,
    flexcan_rx_fifo_id_element_format_t id_format,
    flexcan_id_table_t *id_filter_table)
{
    assert(instance < CAN_INSTANCE_COUNT);

    flexcan_status_t result;
    CAN_Type * base = g_flexcanBase[instance];

    /* Initialize rx fifo*/
    result = FLEXCAN_HAL_SetRxFifoFilter(base, id_format, id_filter_table);
    if(result)
    {
         return result;
    }

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_RxMessageBufferBlocking
 * Description   : Start receive data after a Rx MB interrupt occurs.
 * This function will lock Rx MB after a Rx MB interrupt occurs.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_RxMessageBufferBlocking(
    uint8_t instance,
    uint32_t mb_idx,
    flexcan_msgbuff_t *data,
    uint32_t timeout_ms)
{
    assert(instance < CAN_INSTANCE_COUNT);
    assert(data);

    flexcan_status_t result;
    flexcan_state_t * state = g_flexcanStatePtr[instance];
    osa_status_t syncStatus;

    state->isRxBlocking = true;

    result = FLEXCAN_DRV_StartRxMessageBufferData(instance, mb_idx, data);
    if(result == kStatus_FLEXCAN_Success)
    {
        do
        {
             syncStatus = OSA_SemaWait(&state->rxIrqSync, timeout_ms);
        }while(syncStatus == kStatus_OSA_Idle);

        /* Wait for the interrupt*/
        if (syncStatus != kStatus_OSA_Success)
        {
            return kStatus_FLEXCAN_TimeOut;
        }
    }
    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_RxMessageBuffer
 * Description   : Start receive data after a Rx MB interrupt occurs.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_RxMessageBuffer(
    uint8_t instance,
    uint32_t mb_idx,
    flexcan_msgbuff_t *data)
{
    assert(instance < CAN_INSTANCE_COUNT);
    assert(data);

    flexcan_status_t result;
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    state->isRxBlocking = false;

    result = FLEXCAN_DRV_StartRxMessageBufferData(instance, mb_idx, data);

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_RxFifoBlocking
 * Description   : Start receive data after a Rx FIFO interrupt occurs.
 * This function will lock Rx FIFO after a Rx FIFO interrupt occurs
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_RxFifoBlocking(
    uint8_t instance,
    flexcan_msgbuff_t *data,
    uint32_t timeout_ms)
{
    assert(instance < CAN_INSTANCE_COUNT);
    assert(data);

    flexcan_status_t result;
    flexcan_state_t * state = g_flexcanStatePtr[instance];
    osa_status_t syncStatus;

    state->isRxBlocking = true;
    result = FLEXCAN_DRV_StartRxMessageFifoData(instance, data);
    if(result == kStatus_FLEXCAN_Success)
    {
        do
        {
            syncStatus = OSA_SemaWait(&state->rxIrqSync, timeout_ms);
        } while(syncStatus == kStatus_OSA_Idle);

        /* Wait for the interrupt*/
        if (syncStatus != kStatus_OSA_Success)
        {
            return kStatus_FLEXCAN_TimeOut;
        }
    }

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_RxFifoBlocking
 * Description   : Start receive data after a Rx FIFO interrupt occurs.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_RxFifo(
    uint8_t instance,
    flexcan_msgbuff_t *data)
{
    assert(instance < CAN_INSTANCE_COUNT);
    assert(data);

    flexcan_status_t result;
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    state->isRxBlocking = false;
    result = FLEXCAN_DRV_StartRxMessageFifoData(instance, data);

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_Deinit
 * Description   : Shutdown a FlexCAN module.
 * This function will disable all FlexCAN interrupts, and disable the FlexCAN.
 *
 *END**************************************************************************/
uint32_t FLEXCAN_DRV_Deinit(uint8_t instance)
{
    assert(instance < CAN_INSTANCE_COUNT);
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    /* Destroy FlexCAN sema. */
    OSA_SemaDestroy(&state->txIrqSync);
    OSA_SemaDestroy(&state->rxIrqSync);
    /* Disable FlexCAN interrupts.*/
    INT_SYS_DisableIRQ(g_flexcanWakeUpIrqId[instance]);
    INT_SYS_DisableIRQ(g_flexcanErrorIrqId[instance]);
    INT_SYS_DisableIRQ(g_flexcanBusOffIrqId[instance]);
    INT_SYS_DisableIRQ(g_flexcanOredMessageBufferIrqId[instance]);

    /* Disable FlexCAN.*/
    FLEXCAN_HAL_Disable(g_flexcanBase[instance]);

    /* Clear the state pointer */
    g_flexcanStatePtr[instance] = NULL;

    /* Disable clock gate to FlexCAN module */
    CLOCK_SYS_DisableFlexcanClock(instance);
    return 0;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_IRQHandler
 * Description   : Interrupt handler for FLEXCAN.
 * This handler read data from MB or FIFO, and then clear the interrupt flags.
 * This is not a public API as it is called whenever an interrupt occurs.
 *
 *END**************************************************************************/
void FLEXCAN_DRV_IRQHandler(uint8_t instance)
{
    volatile uint32_t flag_reg;
    uint32_t temp;
    CAN_Type * base = g_flexcanBase[instance];
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    /* Get the interrupts that are enabled and ready */
    flag_reg = ((FLEXCAN_HAL_GetAllMsgBuffIntStatusFlag(base)) & CAN_IMASK1_BUFLM_MASK) &
                CAN_RD_IMASK1(base);

    /* Check Tx/Rx interrupt flag and clear the interrupt */
    if(flag_reg)
    {
        if ((flag_reg & 0x20) && CAN_BRD_MCR_RFEN(base))
        {
            if (state->fifo_message != NULL)
            {
                /* Get RX FIFO field values */
                FLEXCAN_HAL_ReadRxFifo(base, state->fifo_message);
                /* Complete receive data */
                FLEXCAN_DRV_CompleteRxMessageFifoData(instance);
                FLEXCAN_HAL_ClearMsgBuffIntStatusFlag(base, flag_reg);
            }
        }
        else
        {
           /* Check mailbox completed reception*/
            temp = (1 << state->rx_mb_idx);
            if (temp & flag_reg)
            {
                /* Unlock RX message buffer and RX FIFO*/
                FLEXCAN_HAL_LockRxMsgBuff(base, state->rx_mb_idx);
                /* Get RX MB field values*/
                FLEXCAN_HAL_GetMsgBuff(base, state->rx_mb_idx, state->mb_message);
                /* Unlock RX message buffer and RX FIFO*/
                FLEXCAN_HAL_UnlockRxMsgBuff(base);

                /* Complete receive data */
                FLEXCAN_DRV_CompleteRxMessageBufferData(instance);
                FLEXCAN_HAL_ClearMsgBuffIntStatusFlag(base, temp & flag_reg);
            }
            /* Check mailbox completed transmission*/
            temp = (1 << state->tx_mb_idx);
            if (temp & flag_reg)
            {
                /* Complete transmit data */
                FLEXCAN_DRV_CompleteSendData(instance);
                FLEXCAN_HAL_ClearMsgBuffIntStatusFlag(base, temp & flag_reg);
            }
        }
        /* Check mailbox completed transmission*/
        temp = (1 << state->tx_mb_idx);
        if (flag_reg & temp)
        {
                /* Complete transmit data */
                FLEXCAN_DRV_CompleteSendData(instance);
                FLEXCAN_HAL_ClearMsgBuffIntStatusFlag(base, temp & flag_reg);
        }
    }

    /* Clear all other interrupts in ERRSTAT register (Error, Busoff, Wakeup) */
    FLEXCAN_HAL_ClearErrIntStatusFlag(base);

    return;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_GetTransmitStatus
 * Description   : This function returns whether the previous FLEXCAN receive is
 *                 completed.
 * When performing a non-blocking receive, the user can call this function to
 * ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success).
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_GetTransmitStatus(uint32_t instance)
{
    assert(instance < CAN_INSTANCE_COUNT);

    flexcan_state_t * state = g_flexcanStatePtr[instance];

    return (state->isTxBusy ? kStatus_FLEXCAN_TxBusy : kStatus_FLEXCAN_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_GetReceiveStatus
 * Description   : This function returns whether the previous FLEXCAN receive is
 *                 completed.
 * When performing a non-blocking receive, the user can call this function to
 * ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success).
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_GetReceiveStatus(uint32_t instance)
{
    assert(instance < CAN_INSTANCE_COUNT);

    flexcan_state_t * state = g_flexcanStatePtr[instance];

    return (state->isRxBusy ? kStatus_FLEXCAN_RxBusy : kStatus_FLEXCAN_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_AbortSendingData
 * Description   : This function ends a non-blocking FLEXCAN transmission early.
 * During a non-blocking FLEXCAN transmission, the user has the option to terminate
 * the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_AbortSendingData(uint32_t instance)
{
    assert(instance < CAN_INSTANCE_COUNT);

    flexcan_state_t * state = g_flexcanStatePtr[instance];

    /* Check if a transfer is running. */
    if (!state->isTxBusy)
    {
        return kStatus_FLEXCAN_NoTransmitInProgress;
    }

    /* Stop the running transfer. */
    FLEXCAN_DRV_CompleteSendData(instance);

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_AbortReceivingData
 * Description   : This function shuts down the FLEXCAN by disabling interrupts and
 *                 the transmitter/receiver.
 * This function disables the FLEXCAN interrupts, disables the transmitter and
 * receiver.
 *
 *END**************************************************************************/
flexcan_status_t FLEXCAN_DRV_AbortReceivingData(uint32_t instance)
{
    assert(instance < CAN_INSTANCE_COUNT);
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    /* Check if a transfer is running. */
    if (!state->isRxBusy)
    {
        return kStatus_FLEXCAN_NoReceiveInProgress;
    }

    /* Stop the running transfer. */
    FLEXCAN_DRV_CompleteRxMessageBufferData(instance);

    return kStatus_FLEXCAN_Success;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_StartSendData
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static flexcan_status_t FLEXCAN_DRV_StartSendData(
                    uint8_t instance,
                    uint32_t mb_idx,
                    flexcan_data_info_t *tx_info,
                    uint32_t msg_id,
                    uint8_t *mb_data
                    )
{
    flexcan_status_t result;
    flexcan_msgbuff_code_status_t cs;
    flexcan_state_t * state = g_flexcanStatePtr[instance];
    CAN_Type * base = g_flexcanBase[instance];

    if (state->isTxBusy)
    {
        return kStatus_FLEXCAN_TxBusy;
    }
    state->isTxBusy = true;

    state->tx_mb_idx = mb_idx;
    cs.dataLen = tx_info->data_length;
    cs.msgIdType = tx_info->msg_id_type;

    /* Set up FlexCAN message buffer for transmitting data*/
    cs.code = kFlexCanTXData;
    result = FLEXCAN_HAL_SetTxMsgBuff(base, mb_idx, &cs, msg_id, mb_data);
    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_StartRxMessageBufferData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static flexcan_status_t FLEXCAN_DRV_StartRxMessageBufferData(
                    uint8_t instance,
                    uint32_t mb_idx,
                    flexcan_msgbuff_t *data
                    )
{
    flexcan_status_t result;
    CAN_Type * base = g_flexcanBase[instance];
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    /* Start receiving mailbox */
    if(state->isRxBusy)
    {
        return kStatus_FLEXCAN_RxBusy;
    }
    state->isRxBusy = true;
    state->mb_message = data;

    /* Enable MB interrupt*/
    result = FLEXCAN_HAL_SetMsgBuffIntCmd(base, mb_idx, true);
	/* Enable error interrupts */
	FLEXCAN_HAL_SetErrIntCmd(base,kFlexCanIntErr,true);

    return result;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_StartRxMessageFifoData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static flexcan_status_t FLEXCAN_DRV_StartRxMessageFifoData(
                    uint8_t instance,
                    flexcan_msgbuff_t *data
                    )
{
    flexcan_status_t result;
    CAN_Type * base = g_flexcanBase[instance];
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    /* Start receiving fifo */
    if(state->isRxBusy)
    {
        return kStatus_FLEXCAN_RxBusy;
    }
    state->isRxBusy = true;

    /* This will get filled by the interrupt handler */
    state->fifo_message = data;

    /* Enable RX FIFO interrupts*/
    for (uint8_t i = 5; i <= 7; i++)
    {
        result = FLEXCAN_HAL_SetMsgBuffIntCmd(base, i, true);
        if(result)
        {
             return result;
        }
    }
	/* Enable error interrupts */
	FLEXCAN_HAL_SetErrIntCmd(base,kFlexCanIntErr,true);

    return kStatus_FLEXCAN_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_CompleteSendData
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXCAN_DRV_CompleteSendData(uint32_t instance)
{
    assert(instance < CAN_INSTANCE_COUNT);
    CAN_Type * base = g_flexcanBase[instance];
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    /* Disable the transmitter data register empty interrupt */
    FLEXCAN_HAL_SetMsgBuffIntCmd(base, state->tx_mb_idx, false);
	/* Disable error interrupts */
	FLEXCAN_HAL_SetErrIntCmd(base,kFlexCanIntErr,false);

    /* Signal the synchronous completion object. */
    if (state->isTxBlocking)
    {
        OSA_SemaPost(&state->txIrqSync);
    }

    /* Update the information of the module driver state */
    state->isTxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_CompleteRxMessageBufferData
 * Description   : Finish up a receive by completing the process of receiving
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXCAN_DRV_CompleteRxMessageBufferData(uint32_t instance)
{
    assert(instance < CAN_INSTANCE_COUNT);

    CAN_Type * base = g_flexcanBase[instance];
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    FLEXCAN_HAL_SetMsgBuffIntCmd(base, state->rx_mb_idx, false);
	/* Disable error interrupts */
	FLEXCAN_HAL_SetErrIntCmd(base,kFlexCanIntErr,false);

    /* Signal the synchronous completion object. */
    if (state->isRxBlocking)
    {
        OSA_SemaPost(&state->rxIrqSync);
    }
    /* Update the information of the module driver state */
    state->isRxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXCAN_DRV_CompleteRxMessageFifoData
 * Description   : Finish up a receive by completing the process of receiving
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXCAN_DRV_CompleteRxMessageFifoData(uint32_t instance)
{
    assert(instance < CAN_INSTANCE_COUNT);
    uint8_t i;

    CAN_Type * base = g_flexcanBase[instance];
    flexcan_state_t * state = g_flexcanStatePtr[instance];

    for (i = 5; i <= 7; i++)
    {
        FLEXCAN_HAL_SetMsgBuffIntCmd(base, i, false);
    }
	/* Disable error interrupts */
	FLEXCAN_HAL_SetErrIntCmd(base,kFlexCanIntErr,false);

    /* Clear fifo message*/
    state->fifo_message = NULL;

    /* Update status for receive by using fifo*/
    state->isRxBusy = false;

    if(state->isRxBlocking)
    {
        OSA_SemaPost(&state->rxIrqSync);
    }
}
#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/

