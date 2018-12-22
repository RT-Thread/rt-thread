/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

#include "fsl_sdif.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Typedef for interrupt handler. */
typedef void (*sdif_isr_t)(SDIF_Type *base, sdif_handle_t *handle);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the instance.
 *
 * @param base SDIF peripheral base address.
 * @return Instance number.
 */
static uint32_t SDIF_GetInstance(SDIF_Type *base);

/*
* @brief config the SDIF interface before transfer between the card and host
* @param SDIF base address
* @param transfer config structure
*/
static status_t SDIF_TransferConfig(SDIF_Type *base, sdif_transfer_t *transfer);

/*
* @brief wait the command done function and check error status
* @param SDIF base address
* @param command config structure
*/
static status_t SDIF_WaitCommandDone(SDIF_Type *base, sdif_command_t *command);

/*
* @brief transfer data in a blocking way
* @param SDIF base address
* @param data config structure
* @param indicate current transfer mode:DMA or polling
*/
static status_t SDIF_TransferDataBlocking(SDIF_Type *base, sdif_data_t *data, bool isDMA);

/*
* @brief read the command response
* @param SDIF base address
* @param sdif command pointer
*/
static status_t SDIF_ReadCommandResponse(SDIF_Type *base, sdif_command_t *command);

/*
* @brief handle transfer command interrupt
* @param SDIF base address
* @param sdif handle
* @param interrupt mask flags
*/
static void SDIF_TransferHandleCommand(SDIF_Type *base, sdif_handle_t *handle, uint32_t interruptFlags);

/*
* @brief handle transfer data interrupt
* @param SDIF base address
* @param sdif handle
* @param interrupt mask flags
*/
static void SDIF_TransferHandleData(SDIF_Type *base, sdif_handle_t *handle, uint32_t interruptFlags);

/*
* @brief handle DMA transfer
* @param SDIF base address
* @param sdif handle
* @param interrupt mask flag
*/
static void SDIF_TransferHandleDMA(SDIF_Type *base, sdif_handle_t *handle, uint32_t interruptFlags);

/*
* @brief driver IRQ handler
* @param SDIF base address
* @param sdif handle
*/
static void SDIF_TransferHandleIRQ(SDIF_Type *base, sdif_handle_t *handle);

/*
* @brief read data port
* @param SDIF base address
* @param sdif data
* @param the number of data been transferred
*/
static uint32_t SDIF_ReadDataPort(SDIF_Type *base, sdif_data_t *data, uint32_t transferredWords);

/*
* @brief write data port
* @param SDIF base address
* @param sdif data
* @param the number of data been transferred
*/
static uint32_t SDIF_WriteDataPort(SDIF_Type *base, sdif_data_t *data, uint32_t transferredWords);

/*
* @brief read data by blocking way
* @param SDIF base address
* @param sdif data
*/
static status_t SDIF_ReadDataPortBlocking(SDIF_Type *base, sdif_data_t *data);

/*
* @brief write data by blocking way
* @param SDIF base address
* @param sdif data
*/
static status_t SDIF_WriteDataPortBlocking(SDIF_Type *base, sdif_data_t *data);

/*
* @brief handle sdio interrupt
* This function will call the SDIO interrupt callback
* @param SDIF handle
*/
static void SDIF_TransferHandleSDIOInterrupt(sdif_handle_t *handle);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief SDIF internal handle pointer array */
static sdif_handle_t *s_sdifHandle[FSL_FEATURE_SOC_SDIF_COUNT];

/*! @brief SDIF base pointer array */
static SDIF_Type *const s_sdifBase[] = SDIF_BASE_PTRS;

/*! @brief SDIF IRQ name array */
static const IRQn_Type s_sdifIRQ[] = SDIF_IRQS;

/* SDIF ISR for transactional APIs. */
static sdif_isr_t s_sdifIsr;

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t SDIF_GetInstance(SDIF_Type *base)
{
    uint8_t instance = 0U;

    while ((instance < ARRAY_SIZE(s_sdifBase)) && (s_sdifBase[instance] != base))
    {
        instance++;
    }

    assert(instance < ARRAY_SIZE(s_sdifBase));

    return instance;
}

static status_t SDIF_TransferConfig(SDIF_Type *base, sdif_transfer_t *transfer)
{
    sdif_command_t *command = transfer->command;
    sdif_data_t *data = transfer->data;

    if ((command == NULL) || (data && (data->blockSize > SDIF_BLKSIZ_BLOCK_SIZE_MASK)))
    {
        return kStatue_SDIF_InvalidArgument;
    }

    if (data != NULL)
    {
        /* config the block size register ,the block size maybe smaller than FIFO
         depth, will test on the board */
        base->BLKSIZ = SDIF_BLKSIZ_BLOCK_SIZE(data->blockSize);
        /* config the byte count register */
        base->BYTCNT = SDIF_BYTCNT_BYTE_COUNT(data->blockSize * data->blockCount);

        command->flags |= kSDIF_DataExpect; /* need transfer data flag */

        if (data->txData != NULL)
        {
            command->flags |= kSDIF_DataWriteToCard; /* data transfer direction */
        }
        else
        {
            /* config the card read threshold,enable the card read threshold */
            if (data->blockSize <= (SDIF_FIFO_COUNT * sizeof(uint32_t)))
            {
                base->CARDTHRCTL = SDIF_CARDTHRCTL_CARDRDTHREN_MASK | SDIF_CARDTHRCTL_CARDTHRESHOLD(data->blockSize);
            }
            else
            {
                base->CARDTHRCTL &= ~SDIF_CARDTHRCTL_CARDRDTHREN_MASK;
            }
        }

        if (data->streamTransfer)
        {
            command->flags |= kSDIF_DataStreamTransfer; /* indicate if use stream transfer or block transfer  */
        }

        if ((data->enableAutoCommand12) &&
            (data->blockCount > 1U)) /* indicate if auto stop will send after the data transfer done */
        {
            command->flags |= kSDIF_DataTransferAutoStop;
        }
    }
    /* R2 response length long */
    if (command->responseType == kCARD_ResponseTypeR2)
    {
        command->flags |= (kSDIF_CmdCheckResponseCRC | kSDIF_CmdResponseLengthLong | kSDIF_CmdResponseExpect);
    }
    else if ((command->responseType == kCARD_ResponseTypeR3) || (command->responseType == kCARD_ResponseTypeR4))
    {
        command->flags |= kSDIF_CmdResponseExpect; /* response R3 do not check Response CRC */
    }
    else
    {
        if (command->responseType != kCARD_ResponseTypeNone)
        {
            command->flags |= (kSDIF_CmdCheckResponseCRC | kSDIF_CmdResponseExpect);
        }
    }

    if (command->type == kCARD_CommandTypeAbort)
    {
        command->flags |= kSDIF_TransferStopAbort;
    }

    /* wait pre-transfer complete */
    command->flags |= kSDIF_WaitPreTransferComplete | kSDIF_CmdDataUseHoldReg;

    return kStatus_Success;
}

static status_t SDIF_ReadCommandResponse(SDIF_Type *base, sdif_command_t *command)
{
    /* check if command exsit,if not, do not read the response */
    if (NULL != command)
    {
        /* read reponse */
        command->response[0U] = base->RESP[0U];
        if (command->responseType == kCARD_ResponseTypeR2)
        {
            command->response[1U] = base->RESP[1U];
            command->response[2U] = base->RESP[2U];
            command->response[3U] = base->RESP[3U];
        }

        if ((command->responseErrorFlags != 0U) &&
            ((command->responseType == kCARD_ResponseTypeR1) || (command->responseType == kCARD_ResponseTypeR1b) ||
             (command->responseType == kCARD_ResponseTypeR6) || (command->responseType == kCARD_ResponseTypeR5)))
        {
            if (((command->responseErrorFlags) & (command->response[0U])) != 0U)
            {
                return kStatus_SDIF_ResponseError;
            }
        }
    }

    return kStatus_Success;
}

static status_t SDIF_WaitCommandDone(SDIF_Type *base, sdif_command_t *command)
{
    uint32_t status = 0U;

    do
    {
        status = SDIF_GetInterruptStatus(base);
        if ((status &
             (kSDIF_ResponseError | kSDIF_ResponseCRCError | kSDIF_ResponseTimeout | kSDIF_HardwareLockError)) != 0u)
        {
            SDIF_ClearInterruptStatus(base, status & (kSDIF_ResponseError | kSDIF_ResponseCRCError |
                                                      kSDIF_ResponseTimeout | kSDIF_HardwareLockError));
            return kStatus_SDIF_SendCmdFail;
        }
    } while ((status & kSDIF_CommandDone) != kSDIF_CommandDone);

    /* clear the command done bit */
    SDIF_ClearInterruptStatus(base, status & kSDIF_CommandDone);

    return SDIF_ReadCommandResponse(base, command);
}

status_t SDIF_ReleaseDMADescriptor(SDIF_Type *base, sdif_dma_config_t *dmaConfig)
{
    assert(NULL != dmaConfig);
    assert(NULL != dmaConfig->dmaDesBufferStartAddr);

    sdif_dma_descriptor_t *dmaDesAddr;
    uint32_t *tempDMADesBuffer = dmaConfig->dmaDesBufferStartAddr;
    uint32_t dmaDesBufferSize = 0U;

    dmaDesAddr = (sdif_dma_descriptor_t *)tempDMADesBuffer;

    /* chain descriptor mode */
    if (dmaConfig->mode == kSDIF_ChainDMAMode)
    {
        while (((dmaDesAddr->dmaDesAttribute & kSDIF_DMADescriptorDataBufferEnd) != kSDIF_DMADescriptorDataBufferEnd) &&
               (dmaDesBufferSize < dmaConfig->dmaDesBufferLen * sizeof(uint32_t)))
        {
            /* set the OWN bit */
            dmaDesAddr->dmaDesAttribute |= kSDIF_DMADescriptorOwnByDMA;
            dmaDesAddr++;
            dmaDesBufferSize += sizeof(sdif_dma_descriptor_t);
        }
        /* if access dma des address overflow, return fail */
        if (dmaDesBufferSize > dmaConfig->dmaDesBufferLen * sizeof(uint32_t))
        {
            return kStatus_Fail;
        }
        dmaDesAddr->dmaDesAttribute |= kSDIF_DMADescriptorOwnByDMA;
    }
    /* dual descriptor mode */
    else
    {
        while (((dmaDesAddr->dmaDesAttribute & kSDIF_DMADescriptorEnd) != kSDIF_DMADescriptorEnd) &&
               (dmaDesBufferSize < dmaConfig->dmaDesBufferLen * sizeof(uint32_t)))
        {
            dmaDesAddr = (sdif_dma_descriptor_t *)tempDMADesBuffer;
            dmaDesAddr->dmaDesAttribute |= kSDIF_DMADescriptorOwnByDMA;
            tempDMADesBuffer += dmaConfig->dmaDesSkipLen;
        }
        /* if access dma des address overflow, return fail */
        if (dmaDesBufferSize > dmaConfig->dmaDesBufferLen * sizeof(uint32_t))
        {
            return kStatus_Fail;
        }
        dmaDesAddr->dmaDesAttribute |= kSDIF_DMADescriptorOwnByDMA;
    }
    /* reload DMA descriptor */
    base->PLDMND = SDIF_POLL_DEMAND_VALUE;

    return kStatus_Success;
}

static uint32_t SDIF_ReadDataPort(SDIF_Type *base, sdif_data_t *data, uint32_t transferredWords)
{
    uint32_t i;
    uint32_t totalWords;
    uint32_t wordsCanBeRead; /* The words can be read at this time. */
    uint32_t readWatermark = ((base->FIFOTH & SDIF_FIFOTH_RX_WMARK_MASK) >> SDIF_FIFOTH_RX_WMARK_SHIFT);

    if (data->blockSize % sizeof(uint32_t) != 0U)
    {
        data->blockSize +=
            sizeof(uint32_t) - (data->blockSize % sizeof(uint32_t)); /* make the block size as word-aligned */
    }

    totalWords = ((data->blockCount * data->blockSize) / sizeof(uint32_t));

    /* If watermark level is equal or bigger than totalWords, transfers totalWords data. */
    if (readWatermark >= totalWords)
    {
        wordsCanBeRead = totalWords;
    }
    /* If watermark level is less than totalWords and left words to be sent is equal or bigger than readWatermark,
    transfers watermark level words. */
    else if ((readWatermark < totalWords) && ((totalWords - transferredWords) >= readWatermark))
    {
        wordsCanBeRead = readWatermark;
    }
    /* If watermark level is less than totalWords and left words to be sent is less than readWatermark, transfers left
    words. */
    else
    {
        wordsCanBeRead = (totalWords - transferredWords);
    }

    i = 0U;
    while (i < wordsCanBeRead)
    {
        data->rxData[transferredWords++] = base->FIFO[i];
        i++;
    }

    return transferredWords;
}

static uint32_t SDIF_WriteDataPort(SDIF_Type *base, sdif_data_t *data, uint32_t transferredWords)
{
    uint32_t i;
    uint32_t totalWords;
    uint32_t wordsCanBeWrite; /* The words can be read at this time. */
    uint32_t writeWatermark = ((base->FIFOTH & SDIF_FIFOTH_TX_WMARK_MASK) >> SDIF_FIFOTH_TX_WMARK_SHIFT);

    if (data->blockSize % sizeof(uint32_t) != 0U)
    {
        data->blockSize +=
            sizeof(uint32_t) - (data->blockSize % sizeof(uint32_t)); /* make the block size as word-aligned */
    }

    totalWords = ((data->blockCount * data->blockSize) / sizeof(uint32_t));

    /* If watermark level is equal or bigger than totalWords, transfers totalWords data. */
    if (writeWatermark >= totalWords)
    {
        wordsCanBeWrite = totalWords;
    }
    /* If watermark level is less than totalWords and left words to be sent is equal or bigger than writeWatermark,
    transfers watermark level words. */
    else if ((writeWatermark < totalWords) && ((totalWords - transferredWords) >= writeWatermark))
    {
        wordsCanBeWrite = writeWatermark;
    }
    /* If watermark level is less than totalWords and left words to be sent is less than writeWatermark, transfers left
    words. */
    else
    {
        wordsCanBeWrite = (totalWords - transferredWords);
    }

    i = 0U;
    while (i < wordsCanBeWrite)
    {
        base->FIFO[i] = data->txData[transferredWords++];
        i++;
    }

    return transferredWords;
}

static status_t SDIF_ReadDataPortBlocking(SDIF_Type *base, sdif_data_t *data)
{
    uint32_t totalWords;
    uint32_t transferredWords = 0U;
    status_t error = kStatus_Success;
    uint32_t status;
    bool transferOver = false;

    if (data->blockSize % sizeof(uint32_t) != 0U)
    {
        data->blockSize +=
            sizeof(uint32_t) - (data->blockSize % sizeof(uint32_t)); /* make the block size as word-aligned */
    }

    totalWords = ((data->blockCount * data->blockSize) / sizeof(uint32_t));

    while ((transferredWords < totalWords) && (error == kStatus_Success))
    {
        /* wait data transfer complete or reach RX watermark */
        do
        {
            status = SDIF_GetInterruptStatus(base);
            if (status & kSDIF_DataTransferError)
            {
                if (!(data->enableIgnoreError))
                {
                    error = kStatus_Fail;
                }
            }
        } while (((status & (kSDIF_DataTransferOver | kSDIF_ReadFIFORequest)) == 0U) && (!transferOver));

        if ((status & kSDIF_DataTransferOver) == kSDIF_DataTransferOver)
        {
            transferOver = true;
        }

        if (error == kStatus_Success)
        {
            transferredWords = SDIF_ReadDataPort(base, data, transferredWords);
        }

        /* clear interrupt status */
        SDIF_ClearInterruptStatus(base, status);
    }

    return error;
}

static status_t SDIF_WriteDataPortBlocking(SDIF_Type *base, sdif_data_t *data)
{
    uint32_t totalWords;
    uint32_t transferredWords = 0U;
    status_t error = kStatus_Success;
    uint32_t status;

    if (data->blockSize % sizeof(uint32_t) != 0U)
    {
        data->blockSize +=
            sizeof(uint32_t) - (data->blockSize % sizeof(uint32_t)); /* make the block size as word-aligned */
    }

    totalWords = ((data->blockCount * data->blockSize) / sizeof(uint32_t));

    while ((transferredWords < totalWords) && (error == kStatus_Success))
    {
        /* wait data transfer complete or reach RX watermark */
        do
        {
            status = SDIF_GetInterruptStatus(base);
            if (status & kSDIF_DataTransferError)
            {
                if (!(data->enableIgnoreError))
                {
                    error = kStatus_Fail;
                }
            }
        } while ((status & kSDIF_WriteFIFORequest) == 0U);

        if (error == kStatus_Success)
        {
            transferredWords = SDIF_WriteDataPort(base, data, transferredWords);
        }

        /* clear interrupt status */
        SDIF_ClearInterruptStatus(base, status);
    }

    while ((SDIF_GetInterruptStatus(base) & kSDIF_DataTransferOver) != kSDIF_DataTransferOver)
    {
    }

    if (SDIF_GetInterruptStatus(base) & kSDIF_DataTransferError)
    {
        if (!(data->enableIgnoreError))
        {
            error = kStatus_Fail;
        }
    }
    SDIF_ClearInterruptStatus(base, (kSDIF_DataTransferOver | kSDIF_DataTransferError));

    return error;
}

bool SDIF_Reset(SDIF_Type *base, uint32_t mask, uint32_t timeout)
{
    base->CTRL |= mask;

    /* check software DMA reset here for DMA reset also need to check this bit */
    while ((base->CTRL & mask) != 0U)
    {
        if (!timeout)
        {
            break;
        }
        timeout--;
    }

    return timeout ? true : false;
}

static status_t SDIF_TransferDataBlocking(SDIF_Type *base, sdif_data_t *data, bool isDMA)
{
    assert(NULL != data);

    uint32_t dmaStatus = 0U;
    status_t error = kStatus_Success;

    /* in DMA mode, only need to wait the complete flag and check error */
    if (isDMA)
    {
        do
        {
            dmaStatus = SDIF_GetInternalDMAStatus(base);
            if ((dmaStatus & kSDIF_DMAFatalBusError) == kSDIF_DMAFatalBusError)
            {
                SDIF_ClearInternalDMAStatus(base, kSDIF_DMAFatalBusError | kSDIF_AbnormalInterruptSummary);
                error = kStatus_SDIF_DMATransferFailWithFBE; /* in this condition,need reset */
            }
            /* Card error summary, include EBE,SBE,Data CRC,RTO,DRTO,Response error */
            if ((dmaStatus & kSDIF_DMACardErrorSummary) == kSDIF_DMACardErrorSummary)
            {
                SDIF_ClearInternalDMAStatus(base, kSDIF_DMACardErrorSummary | kSDIF_AbnormalInterruptSummary);
                if (!(data->enableIgnoreError))
                {
                    error = kStatus_SDIF_DataTransferFail;
                }

                /* if error occur, then return */
                break;
            }
        } while ((dmaStatus & (kSDIF_DMATransFinishOneDescriptor | kSDIF_DMARecvFinishOneDescriptor)) == 0U);

        /* clear the corresponding status bit */
        SDIF_ClearInternalDMAStatus(base, (kSDIF_DMATransFinishOneDescriptor | kSDIF_DMARecvFinishOneDescriptor |
                                           kSDIF_NormalInterruptSummary));

        SDIF_ClearInterruptStatus(base, SDIF_GetInterruptStatus(base));
    }
    else
    {
        if (data->rxData != NULL)
        {
            error = SDIF_ReadDataPortBlocking(base, data);
        }
        else
        {
            error = SDIF_WriteDataPortBlocking(base, data);
        }
    }

    return error;
}

status_t SDIF_SendCommand(SDIF_Type *base, sdif_command_t *cmd, uint32_t timeout)
{
    assert(NULL != cmd);

    base->CMDARG = cmd->argument;
    base->CMD = SDIF_CMD_CMD_INDEX(cmd->index) | SDIF_CMD_START_CMD_MASK | (cmd->flags & (~SDIF_CMD_CMD_INDEX_MASK));

    /* wait start_cmd bit auto clear within timeout */
    while ((base->CMD & SDIF_CMD_START_CMD_MASK) == SDIF_CMD_START_CMD_MASK)
    {
        if (!timeout)
        {
            break;
        }

        --timeout;
    }

    return timeout ? kStatus_Success : kStatus_Fail;
}

bool SDIF_SendCardActive(SDIF_Type *base, uint32_t timeout)
{
    bool enINT = false;
    sdif_command_t command;

    memset(&command, 0U, sizeof(sdif_command_t));

    /* add for confict with interrupt mode,close the interrupt temporary */
    if ((base->CTRL & SDIF_CTRL_INT_ENABLE_MASK) == SDIF_CTRL_INT_ENABLE_MASK)
    {
        enINT = true;
        base->CTRL &= ~SDIF_CTRL_INT_ENABLE_MASK;
    }

    command.flags = SDIF_CMD_SEND_INITIALIZATION_MASK;

    if (SDIF_SendCommand(base, &command, timeout) == kStatus_Fail)
    {
        return false;
    }

    /* wait command done */
    while ((SDIF_GetInterruptStatus(base) & kSDIF_CommandDone) != kSDIF_CommandDone)
    {
    }

    /* clear status */
    SDIF_ClearInterruptStatus(base, kSDIF_CommandDone);

    /* add for confict with interrupt mode */
    if (enINT)
    {
        base->CTRL |= SDIF_CTRL_INT_ENABLE_MASK;
    }

    return true;
}

void SDIF_ConfigClockDelay(uint32_t target_HZ, uint32_t divider)
{
    /*config the clock delay and pharse shift
     *should config the clk_in_drv,
     *clk_in_sample to meet the min hold and
     *setup time
     */
    if (target_HZ <= kSDIF_Freq400KHZ)
    {
        /*min hold time:5ns
        * min setup time: 5ns
        * delay = (x+1)*250ps
        */
        SYSCON->SDIOCLKCTRL = SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY_ACTIVE_MASK |
                              SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY(SDIF_INDENTIFICATION_MODE_SAMPLE_DELAY) |
                              SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY_ACTIVE_MASK |
                              SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY(SDIF_INDENTIFICATION_MODE_DRV_DELAY);
    }
    else if (target_HZ >= kSDIF_Freq50MHZ)
    {
        /*
        * user need to pay attention to this parameter
        * can be change the setting for you card and board
        * min hold time:2ns
        * min setup time: 6ns
        * delay = (x+1)*250ps
        */
        SYSCON->SDIOCLKCTRL = SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY_ACTIVE_MASK |
                              SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY(SDIF_HIGHSPEED_50MHZ_SAMPLE_DELAY) |
                              SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY_ACTIVE_MASK |
                              SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY(SDIF_HIGHSPEED_50MHZ_DRV_DELAY);
        /* means the input clock = 2 * card clock,
        * can use clock pharse shift tech
        */
        if (divider == 1U)
        {
            SYSCON->SDIOCLKCTRL |= SYSCON_SDIOCLKCTRL_PHASE_ACTIVE_MASK |
                                   SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_PHASE(kSDIF_ClcokPharseShift90) |
                                   SYSCON_SDIOCLKCTRL_CCLK_DRV_PHASE(kSDIF_ClcokPharseShift180);
        }
    }
    else
    {
        /*
        * user need to pay attention to this parameter
        * can be change the setting for you card and board
        * min hold time:5ns
        * min setup time: 5ns
        * delay = (x+1)*250ps
        */
        SYSCON->SDIOCLKCTRL = SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY_ACTIVE_MASK |
                              SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY(SDIF_HIGHSPEED_25MHZ_SAMPLE_DELAY) |
                              SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY_ACTIVE_MASK |
                              SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY(SDIF_HIGHSPEED_25MHZ_DRV_DELAY);
        /* means the input clock = 2 * card clock,
        * can use clock pharse shift tech
        */
        if (divider == 1U)
        {
            SYSCON->SDIOCLKCTRL |= SYSCON_SDIOCLKCTRL_PHASE_ACTIVE_MASK |
                                   SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_PHASE(kSDIF_ClcokPharseShift90) |
                                   SYSCON_SDIOCLKCTRL_CCLK_DRV_PHASE(kSDIF_ClcokPharseShift90);
        }
    }
}

uint32_t SDIF_SetCardClock(SDIF_Type *base, uint32_t srcClock_Hz, uint32_t target_HZ)
{
    assert(srcClock_Hz <= FSL_FEATURE_SDIF_MAX_SOURCE_CLOCK);

    sdif_command_t cmd = {0U};
    uint32_t divider = 0U, targetFreq = target_HZ;

    /* if target freq bigger than the source clk, set the target_HZ to
     src clk, this interface can run up to 52MHZ with card */
    if (srcClock_Hz < targetFreq)
    {
        targetFreq = srcClock_Hz;
    }

    /* disable the clock first,need sync to CIU*/
    SDIF_EnableCardClock(base, false);

    /* update the clock register and wait the pre-transfer complete */
    cmd.flags = kSDIF_CmdUpdateClockRegisterOnly | kSDIF_WaitPreTransferComplete;
    SDIF_SendCommand(base, &cmd, SDIF_TIMEOUT_VALUE);

    /*calucate the divider*/
    if (targetFreq != srcClock_Hz)
    {
        divider = (srcClock_Hz / targetFreq + 1U) / 2U;
    }
    /* load the clock divider */
    base->CLKDIV = SDIF_CLKDIV_CLK_DIVIDER0(divider);

    /* update the divider to CIU */
    cmd.flags = kSDIF_CmdUpdateClockRegisterOnly | kSDIF_WaitPreTransferComplete;
    SDIF_SendCommand(base, &cmd, SDIF_TIMEOUT_VALUE);

    /* enable the card clock and sync to CIU */
    SDIF_EnableCardClock(base, true);
    SDIF_SendCommand(base, &cmd, SDIF_TIMEOUT_VALUE);

    /* config the clock delay to meet the hold time and setup time */
    SDIF_ConfigClockDelay(target_HZ, divider);

    /* return the actual card clock freq */

    return (divider != 0U) ? (srcClock_Hz / (divider * 2U)) : srcClock_Hz;
}

bool SDIF_AbortReadData(SDIF_Type *base, uint32_t timeout)
{
    /* assert this bit to reset the data machine to abort the read data */
    base->CTRL |= SDIF_CTRL_ABORT_READ_DATA_MASK;
    /* polling the bit self clear */
    while ((base->CTRL & SDIF_CTRL_ABORT_READ_DATA_MASK) == SDIF_CTRL_ABORT_READ_DATA_MASK)
    {
        if (!timeout)
        {
            break;
        }
        timeout--;
    }

    return base->CTRL & SDIF_CTRL_ABORT_READ_DATA_MASK ? false : true;
}

status_t SDIF_InternalDMAConfig(SDIF_Type *base, sdif_dma_config_t *config, const uint32_t *data, uint32_t dataSize)
{
    assert(NULL != config);
    assert(NULL != data);

    uint32_t dmaEntry = 0U, i, dmaBufferSize = 0U, dmaBuffer1Size = 0U;
    uint32_t *tempDMADesBuffer = config->dmaDesBufferStartAddr;
    const uint32_t *dataBuffer = data;
    sdif_dma_descriptor_t *descriptorPoniter = NULL;
    uint32_t maxDMABuffer = FSL_FEATURE_SDIF_INTERNAL_DMA_MAX_BUFFER_SIZE * (config->mode);

    /* check the dma descriptor buffer length , it is user's responsibility to make sure the DMA descriptor table
    size is bigger enough to hold the transfer descriptor */
    if (config->dmaDesBufferLen * sizeof(uint32_t) < sizeof(sdif_dma_descriptor_t))
    {
        return kStatus_SDIF_DescriptorBufferLenError;
    }

    /* check the read/write data size,must be a multiple of 4 */
    if (dataSize % sizeof(uint32_t) != 0U)
    {
        dataSize += sizeof(uint32_t) - (dataSize % sizeof(uint32_t));
    }

    /*config the bus mode*/
    if (config->enableFixBurstLen)
    {
        base->BMOD |= SDIF_BMOD_FB_MASK;
    }

    /* calucate the dma descriptor entry due to DMA buffer size limit */
    /* if datasize smaller than one descriptor buffer size */
    if (dataSize > maxDMABuffer)
    {
        dmaEntry = dataSize / maxDMABuffer + (dataSize % maxDMABuffer ? 1U : 0U);
    }
    else /* need one dma descriptor */
    {
        dmaEntry = 1U;
    }

    /* check the DMA descriptor buffer len one more time,it is user's responsibility to make sure the DMA descriptor
    table
    size is bigger enough to hold the transfer descriptor */
    if (config->dmaDesBufferLen * sizeof(uint32_t) < (dmaEntry * sizeof(sdif_dma_descriptor_t) + config->dmaDesSkipLen))
    {
        return kStatus_SDIF_DescriptorBufferLenError;
    }

    switch (config->mode)
    {
        case kSDIF_DualDMAMode:
            base->BMOD |= SDIF_BMOD_DSL(config->dmaDesSkipLen); /* config the distance between the DMA descriptor */
            for (i = 0U; i < dmaEntry; i++)
            {
                if (dataSize > FSL_FEATURE_SDIF_INTERNAL_DMA_MAX_BUFFER_SIZE)
                {
                    dmaBufferSize = FSL_FEATURE_SDIF_INTERNAL_DMA_MAX_BUFFER_SIZE;
                    dataSize -= dmaBufferSize;
                    dmaBuffer1Size = dataSize > FSL_FEATURE_SDIF_INTERNAL_DMA_MAX_BUFFER_SIZE ?
                                         FSL_FEATURE_SDIF_INTERNAL_DMA_MAX_BUFFER_SIZE :
                                         dataSize;
                    dataSize -= dmaBuffer1Size;
                }
                else
                {
                    dmaBufferSize = dataSize;
                    dmaBuffer1Size = 0U;
                }

                descriptorPoniter = (sdif_dma_descriptor_t *)tempDMADesBuffer;
                if (i == 0U)
                {
                    descriptorPoniter->dmaDesAttribute = kSDIF_DMADescriptorDataBufferStart;
                }
                descriptorPoniter->dmaDesAttribute |= kSDIF_DMADescriptorOwnByDMA | kSDIF_DisableCompleteInterrupt;
                descriptorPoniter->dmaDataBufferSize =
                    SDIF_DMA_DESCRIPTOR_BUFFER1_SIZE(dmaBufferSize) | SDIF_DMA_DESCRIPTOR_BUFFER2_SIZE(dmaBuffer1Size);

                descriptorPoniter->dmaDataBufferAddr0 = dataBuffer;
                descriptorPoniter->dmaDataBufferAddr1 = dataBuffer + dmaBufferSize / sizeof(uint32_t);
                dataBuffer += (dmaBufferSize + dmaBuffer1Size) / sizeof(uint32_t);

                /* descriptor skip length */
                tempDMADesBuffer += config->dmaDesSkipLen + sizeof(sdif_dma_descriptor_t) / sizeof(uint32_t);
            }
            /* enable the completion interrupt when reach the last descriptor */
            descriptorPoniter->dmaDesAttribute &= ~kSDIF_DisableCompleteInterrupt;
            descriptorPoniter->dmaDesAttribute |= kSDIF_DMADescriptorDataBufferEnd | kSDIF_DMADescriptorEnd;
            break;

        case kSDIF_ChainDMAMode:
            for (i = 0U; i < dmaEntry; i++)
            {
                if (dataSize > FSL_FEATURE_SDIF_INTERNAL_DMA_MAX_BUFFER_SIZE)
                {
                    dmaBufferSize = FSL_FEATURE_SDIF_INTERNAL_DMA_MAX_BUFFER_SIZE;
                    dataSize -= FSL_FEATURE_SDIF_INTERNAL_DMA_MAX_BUFFER_SIZE;
                }
                else
                {
                    dmaBufferSize = dataSize;
                }

                descriptorPoniter = (sdif_dma_descriptor_t *)tempDMADesBuffer;
                if (i == 0U)
                {
                    descriptorPoniter->dmaDesAttribute = kSDIF_DMADescriptorDataBufferStart;
                }
                descriptorPoniter->dmaDesAttribute |=
                    kSDIF_DMADescriptorOwnByDMA | kSDIF_DMASecondAddrChained | kSDIF_DisableCompleteInterrupt;
                descriptorPoniter->dmaDataBufferSize =
                    SDIF_DMA_DESCRIPTOR_BUFFER1_SIZE(dmaBufferSize); /* use only buffer 1 for data buffer*/
                descriptorPoniter->dmaDataBufferAddr0 = dataBuffer;
                dataBuffer += dmaBufferSize / sizeof(uint32_t);
                tempDMADesBuffer +=
                    sizeof(sdif_dma_descriptor_t) / sizeof(uint32_t); /* calucate the next descriptor address */
                /* this descriptor buffer2 pointer to the next descriptor address */
                descriptorPoniter->dmaDataBufferAddr1 = tempDMADesBuffer;
            }
            /* enable the completion interrupt when reach the last descriptor */
            descriptorPoniter->dmaDesAttribute &= ~kSDIF_DisableCompleteInterrupt;
            descriptorPoniter->dmaDesAttribute |= kSDIF_DMADescriptorDataBufferEnd;
            break;

        default:
            break;
    }

    /* use internal DMA interface */
    base->CTRL |= SDIF_CTRL_USE_INTERNAL_DMAC_MASK;
    /* enable the internal SD/MMC DMA */
    base->BMOD |= SDIF_BMOD_DE_MASK;
    /* enable DMA status check */
    base->IDINTEN |= kSDIF_DMAAllStatus;
    /* clear write/read FIFO request interrupt in DMA mode, DMA will handle the data transfer*/
    SDIF_DisableInterrupt(base, kSDIF_WriteFIFORequest | kSDIF_ReadFIFORequest | kSDIF_DataTransferOver);
    /* load DMA descriptor buffer address */
    base->DBADDR = (uint32_t)config->dmaDesBufferStartAddr;

    return kStatus_Success;
}

void SDIF_Init(SDIF_Type *base, sdif_config_t *config)
{
    assert(NULL != config);

    uint32_t timeout;

    /* enable SDIF clock */
    CLOCK_EnableClock(kCLOCK_Sdio);

    /* do software reset */
    base->BMOD |= SDIF_BMOD_SWR_MASK;

    /* reset all */
    SDIF_Reset(base, kSDIF_ResetAll, SDIF_TIMEOUT_VALUE);

    /*config timeout register */
    timeout = base->TMOUT;
    timeout &= ~(SDIF_TMOUT_RESPONSE_TIMEOUT_MASK | SDIF_TMOUT_DATA_TIMEOUT_MASK);
    timeout |= SDIF_TMOUT_RESPONSE_TIMEOUT(config->responseTimeout) | SDIF_TMOUT_DATA_TIMEOUT(config->dataTimeout);

    base->TMOUT = timeout;

    /* config the card detect debounce clock count */
    base->DEBNCE = SDIF_DEBNCE_DEBOUNCE_COUNT(config->cardDetDebounce_Clock);

    /*config the watermark/burst transfer value */
    base->FIFOTH =
        SDIF_FIFOTH_TX_WMARK(SDIF_TX_WATERMARK) | SDIF_FIFOTH_RX_WMARK(SDIF_RX_WATERMARK) | SDIF_FIFOTH_DMA_MTS(1U);

    /* enable the interrupt status  */
    SDIF_EnableInterrupt(base, kSDIF_AllInterruptStatus);

    /* clear all interrupt/DMA status */
    SDIF_ClearInterruptStatus(base, kSDIF_AllInterruptStatus);
    SDIF_ClearInternalDMAStatus(base, kSDIF_DMAAllStatus);
}

status_t SDIF_TransferBlocking(SDIF_Type *base, sdif_dma_config_t *dmaConfig, sdif_transfer_t *transfer)
{
    assert(NULL != transfer);

    bool isDMA = false;
    sdif_data_t *data = transfer->data;

    /* config the transfer parameter */
    if (SDIF_TransferConfig(base, transfer) != kStatus_Success)
    {
        return kStatue_SDIF_InvalidArgument;
    }

    /* if need transfer data in dma mode, config the DMA descriptor first */
    if ((data != NULL) && (dmaConfig != NULL))
    {
        /* use internal DMA mode to transfer between the card and host*/
        isDMA = true;

        if (SDIF_InternalDMAConfig(base, dmaConfig, data->rxData ? data->rxData : data->txData,
                                   data->blockSize * data->blockCount) != kStatus_Success)
        {
            return kStatus_SDIF_DescriptorBufferLenError;
        }
    }

    /* send command first */
    if (SDIF_SendCommand(base, transfer->command, SDIF_TIMEOUT_VALUE) != kStatus_Success)
    {
        return kStatus_SDIF_SyncCmdTimeout;
    }

    /* wait the command transfer done and check if error occurs */
    if (SDIF_WaitCommandDone(base, transfer->command) != kStatus_Success)
    {
        return kStatus_SDIF_SendCmdFail;
    }

    /* if use DMA transfer mode ,check the corresponding status bit */
    if (data != NULL)
    {
        /* check the if has DMA descriptor featch error */
        if (isDMA &&
            ((SDIF_GetInternalDMAStatus(base) & kSDIF_DMADescriptorUnavailable) == kSDIF_DMADescriptorUnavailable))
        {
            SDIF_ClearInternalDMAStatus(base, kSDIF_DMADescriptorUnavailable | kSDIF_AbnormalInterruptSummary);

            /* release the DMA descriptor to DMA */
            SDIF_ReleaseDMADescriptor(base, dmaConfig);
        }
        /* handle data transfer */
        if (SDIF_TransferDataBlocking(base, data, isDMA) != kStatus_Success)
        {
            return kStatus_SDIF_DataTransferFail;
        }
    }

    return kStatus_Success;
}

status_t SDIF_TransferNonBlocking(SDIF_Type *base,
                                  sdif_handle_t *handle,
                                  sdif_dma_config_t *dmaConfig,
                                  sdif_transfer_t *transfer)
{
    assert(NULL != transfer);

    sdif_data_t *data = transfer->data;

    /* save the data and command before transfer */
    handle->data = transfer->data;
    handle->command = transfer->command;
    handle->transferredWords = 0U;
    handle->interruptFlags = 0U;
    handle->dmaInterruptFlags = 0U;

    /* config the transfer parameter */
    if (SDIF_TransferConfig(base, transfer) != kStatus_Success)
    {
        return kStatue_SDIF_InvalidArgument;
    }

    if ((data != NULL) && (dmaConfig != NULL))
    {
        /* use internal DMA mode to transfer between the card and host*/
        if (SDIF_InternalDMAConfig(base, dmaConfig, data->rxData ? data->rxData : data->txData,
                                   data->blockSize * data->blockCount) != kStatus_Success)
        {
            return kStatus_SDIF_DescriptorBufferLenError;
        }
    }

    /* send command first */
    if (SDIF_SendCommand(base, transfer->command, SDIF_TIMEOUT_VALUE) != kStatus_Success)
    {
        return kStatus_SDIF_SyncCmdTimeout;
    }

    return kStatus_Success;
}

void SDIF_TransferCreateHandle(SDIF_Type *base,
                               sdif_handle_t *handle,
                               sdif_transfer_callback_t *callback,
                               void *userData)
{
    assert(handle);
    assert(callback);

    /* reset the handle. */
    memset(handle, 0U, sizeof(*handle));

    /* Set the callback. */
    handle->callback.SDIOInterrupt = callback->SDIOInterrupt;
    handle->callback.DMADesUnavailable = callback->DMADesUnavailable;
    handle->callback.CommandReload = callback->CommandReload;
    handle->callback.TransferComplete = callback->TransferComplete;

    handle->userData = userData;

    /* Save the handle in global variables to support the double weak mechanism. */
    s_sdifHandle[SDIF_GetInstance(base)] = handle;

    /* save IRQ handler */
    s_sdifIsr = SDIF_TransferHandleIRQ;

    /* enable the global interrupt */
    SDIF_EnableGlobalInterrupt(base, true);

    EnableIRQ(s_sdifIRQ[SDIF_GetInstance(base)]);
}

void SDIF_GetCapability(SDIF_Type *base, sdif_capability_t *capability)
{
    assert(NULL != capability);

    capability->sdVersion = SDIF_SUPPORT_SD_VERSION;
    capability->mmcVersion = SDIF_SUPPORT_MMC_VERSION;
    capability->maxBlockLength = SDIF_BLKSIZ_BLOCK_SIZE_MASK;
    /* set the max block count = max byte conut / max block size */
    capability->maxBlockCount = SDIF_BYTCNT_BYTE_COUNT_MASK / SDIF_BLKSIZ_BLOCK_SIZE_MASK;
    capability->flags = kSDIF_SupportHighSpeedFlag | kSDIF_SupportDmaFlag | kSDIF_SupportSuspendResumeFlag |
                        kSDIF_SupportV330Flag | kSDIF_Support4BitFlag | kSDIF_Support8BitFlag;
}

static void SDIF_TransferHandleCommand(SDIF_Type *base, sdif_handle_t *handle, uint32_t interruptFlags)
{
    assert(handle->command);

    /* transfer error */
    if (interruptFlags & (kSDIF_ResponseError | kSDIF_ResponseCRCError | kSDIF_ResponseTimeout))
    {
        handle->callback.TransferComplete(base, handle, kStatus_SDIF_SendCmdFail, handle->userData);
    }
    /* cmd buffer full, in this condition user need re-send the command */
    else if (interruptFlags & kSDIF_HardwareLockError)
    {
        if (handle->callback.CommandReload)
        {
            handle->callback.CommandReload();
        }
    }
    /* transfer command success */
    else
    {
        SDIF_ReadCommandResponse(base, handle->command);
        if (((handle->data) == NULL) && (handle->callback.TransferComplete))
        {
            handle->callback.TransferComplete(base, handle, kStatus_Success, handle->userData);
        }
    }
}

static void SDIF_TransferHandleData(SDIF_Type *base, sdif_handle_t *handle, uint32_t interruptFlags)
{
    assert(handle->data);

    /* data starvation by host time out, software should read/write FIFO*/
    if (interruptFlags & kSDIF_DataStarvationByHostTimeout)
    {
        if (handle->data->rxData != NULL)
        {
            handle->transferredWords = SDIF_ReadDataPort(base, handle->data, handle->transferredWords);
        }
        else if (handle->data->txData != NULL)
        {
            handle->transferredWords = SDIF_WriteDataPort(base, handle->data, handle->transferredWords);
        }
        else
        {
            handle->callback.TransferComplete(base, handle, kStatus_SDIF_DataTransferFail, handle->userData);
        }
    }
    /* data transfer fail */
    else if (interruptFlags & kSDIF_DataTransferError)
    {
        if (!handle->data->enableIgnoreError)
        {
            handle->callback.TransferComplete(base, handle, kStatus_SDIF_DataTransferFail, handle->userData);
        }
    }
    /* need fill data to FIFO */
    else if (interruptFlags & kSDIF_WriteFIFORequest)
    {
        handle->transferredWords = SDIF_WriteDataPort(base, handle->data, handle->transferredWords);
    }
    /* need read data from FIFO */
    else if (interruptFlags & kSDIF_ReadFIFORequest)
    {
        handle->transferredWords = SDIF_ReadDataPort(base, handle->data, handle->transferredWords);
    }
    else
    {
    }

    /* data transfer over */
    if (interruptFlags & kSDIF_DataTransferOver)
    {
        while ((handle->data->rxData != NULL) && ((base->STATUS & SDIF_STATUS_FIFO_COUNT_MASK) != 0U))
        {
            handle->transferredWords = SDIF_ReadDataPort(base, handle->data, handle->transferredWords);
        }
        handle->callback.TransferComplete(base, handle, kStatus_Success, handle->userData);
    }
}

static void SDIF_TransferHandleDMA(SDIF_Type *base, sdif_handle_t *handle, uint32_t interruptFlags)
{
    if (interruptFlags & kSDIF_DMAFatalBusError)
    {
        handle->callback.TransferComplete(base, handle, kStatus_SDIF_DMATransferFailWithFBE, handle->userData);
    }
    else if (interruptFlags & kSDIF_DMADescriptorUnavailable)
    {
        if (handle->callback.DMADesUnavailable)
        {
            handle->callback.DMADesUnavailable();
        }
    }
    else if ((interruptFlags & (kSDIF_AbnormalInterruptSummary | kSDIF_DMACardErrorSummary)) &&
             (!handle->data->enableIgnoreError))
    {
        handle->callback.TransferComplete(base, handle, kStatus_SDIF_DataTransferFail, handle->userData);
    }
    /* card normal summary */
    else
    {
        handle->callback.TransferComplete(base, handle, kStatus_Success, handle->userData);
    }
}

static void SDIF_TransferHandleSDIOInterrupt(sdif_handle_t *handle)
{
    if (handle->callback.SDIOInterrupt != NULL)
    {
        handle->callback.SDIOInterrupt();
    }
}

static void SDIF_TransferHandleIRQ(SDIF_Type *base, sdif_handle_t *handle)
{
    assert(handle);

    uint32_t interruptFlags, dmaInterruptFlags;

    interruptFlags = SDIF_GetInterruptStatus(base);
    dmaInterruptFlags = SDIF_GetInternalDMAStatus(base);

    handle->interruptFlags = interruptFlags;
    handle->dmaInterruptFlags = dmaInterruptFlags;

    if ((interruptFlags & kSDIF_CommandTransferStatus) != 0U)
    {
        SDIF_TransferHandleCommand(base, handle, (interruptFlags & kSDIF_CommandTransferStatus));
    }
    if ((interruptFlags & kSDIF_DataTransferStatus) != 0U)
    {
        SDIF_TransferHandleData(base, handle, (interruptFlags & kSDIF_DataTransferStatus));
    }
    if (interruptFlags & kSDIF_SDIOInterrupt)
    {
        SDIF_TransferHandleSDIOInterrupt(handle);
    }
    if (dmaInterruptFlags & kSDIF_DMAAllStatus)
    {
        SDIF_TransferHandleDMA(base, handle, dmaInterruptFlags);
    }

    SDIF_ClearInterruptStatus(base, interruptFlags);
    SDIF_ClearInternalDMAStatus(base, dmaInterruptFlags);
}

void SDIF_Deinit(SDIF_Type *base)
{
    /* disable clock here*/
    CLOCK_DisableClock(kCLOCK_Sdio);
    /* disable the SDIOCLKCTRL */
    SYSCON->SDIOCLKCTRL &= ~(SYSCON_SDIOCLKCTRL_CCLK_SAMPLE_DELAY_ACTIVE_MASK |
                             SYSCON_SDIOCLKCTRL_CCLK_DRV_DELAY_ACTIVE_MASK | SYSCON_SDIOCLKCTRL_PHASE_ACTIVE_MASK);
    RESET_PeripheralReset(kSDIO_RST_SHIFT_RSTn);
}

#if defined(SDIF)

#include <rthw.h>
#include <rtthread.h>

void SDIF_DriverIRQHandler(void)
{
	 /* enter interrupt */
    rt_interrupt_enter();

    assert(s_sdifHandle[0]);

    s_sdifIsr(SDIF, s_sdifHandle[0]);
	
	/* leave interrupt */
    rt_interrupt_leave();
}
#endif
