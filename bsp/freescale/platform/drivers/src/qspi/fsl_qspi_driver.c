/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#include "fsl_qspi_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_QuadSPIO_COUNT

/******************************************************************************
 * Variables
 *****************************************************************************/
qspi_state_t * g_qspiState[QuadSPI_INSTANCE_COUNT] = {0};

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
void QSPI_DRV_TxEdmaCallback(void *param, edma_chn_status_t status);
void QSPI_DRV_RxEdmaCallback(void *param, edma_chn_status_t status);

/******************************************************************************
 * Code
 *****************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_Init
 * Description   : Init QSPI internal state and open clock for QSPI.
 *
 *END**************************************************************************/
qspi_status_t QSPI_DRV_Init(uint32_t instance, qspi_state_t * state)
{
    if (state == NULL)
    {
        return kStatus_QSPI_Fail;
    }
    QuadSPI_Type * base = g_qspiBase[instance];
    CLOCK_SYS_EnableQspiClock(instance);
    QSPI_HAL_Init(base);
    /* Configure internal state */
    if (g_qspiState[instance])
    {
        return kStatus_QSPI_DeviceBusy;
    }
    else
    {
        g_qspiState[instance] = state;
    }
    /* Enable interrupt */
    INT_SYS_EnableIRQ(g_qspiIrqId[instance]);
    return kStatus_QSPI_Success;  
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_ConfigQspi
 * Description   : Configure QSPI settings, including the clock source, clock
 * frequency and buffer settings.
 *
 *END**************************************************************************/
qspi_status_t QSPI_DRV_ConfigQspi(uint32_t instance, qspi_config_t * config)
{
    if (config == NULL)
    {
        return kStatus_QSPI_Fail;
    }
    QuadSPI_Type * base = g_qspiBase[instance];
    uint8_t i = 0;
    uint32_t freq;
    /* Configure the QSPI clock. */
    QSPI_HAL_DisableModule(base);
    QSPI_HAL_SetClockSrc(base, config->clockSrc);
    freq = CLOCK_SYS_GetQspiFreq(instance, config->clockSrc);
    QSPI_HAL_SetSCLK(base, freq, config->sclk);
    /* Set AHB buffer size and buffer master */
    for (i = 0; i < FSL_FEATURE_QSPI_AHB_BUFFER_COUNT; i++)
    {
        QSPI_HAL_SetAHBBufferMaster(base, i, config->AHBbufferMaster[i]);
        QSPI_HAL_SetAHBBufferSize(base, i, config->AHBbufferSize[i]);
    }
    if (config->AHBbuffer3AllMaster)
    {
        QSPI_HAL_SetBuf3AllMaster(base, true);
    }
    /* Set watermark */
    QSPI_HAL_SetRxWatermark(base, config->rxWatermark);
    g_qspiState[instance]->rxWatermark = config->rxWatermark;
    QSPI_HAL_SetTxWatermark(base, config->txWatermark);
    g_qspiState[instance]->txWatermark = config->txWatermark;
    /* Set dma source */
    g_qspiState[instance]->txSource = config->txSource;
    g_qspiState[instance]->rxSource = config->rxSource;
    QSPI_HAL_EnableModule(base);
    return kStatus_QSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_ConfigQspi
 * Description   : Configure QSPI settings, including the clock source, clock
 * frequency and buffer settings.
 *
 *END**************************************************************************/
void QSPI_DRV_GetDefaultQspiConfig(qspi_config_t * config)
{
    /* Clock source from PLL */
    config->clockSrc =  kClockQspiSrcPllClk;
    config->sclk = 60000000U;
    config->AHBbufferMaster[0] = 0xE;
    config->AHBbufferMaster[1] = 0xE;
    config->AHBbufferMaster[2] = 0xE;
    config->AHBbuffer3AllMaster = true;
    config->txWatermark = 8;
    config->rxWatermark = 8;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_Deinit
 * Description   : Deinit the QSPI module, close the clock source.
 *
 *END**************************************************************************/
qspi_status_t QSPI_DRV_Deinit(uint32_t instance)
{
    QuadSPI_Type * base = g_qspiBase[instance];
    /* Disable the QSPI module */
    QSPI_HAL_DisableModule(base);
    /* If use edma, release channel*/
    if (g_qspiState[instance]->txUseDma)
    {
        EDMA_DRV_ReleaseChannel(&g_qspiState[instance]->txEdmaChn);
    }
    if (g_qspiState[instance]->rxUseDma)
    {
        EDMA_DRV_ReleaseChannel(&g_qspiState[instance]->rxEdmaChn);
    }
    g_qspiState[instance] = NULL;
    CLOCK_SYS_DisableQspiClock(instance);
    return kStatus_QSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_WriteDataInt
 * Description   : Write data into QSPI tx FIFO using interrupt way. This function
 * will open interrupt enable bit and transfer data in ISR.
 *
 *END**************************************************************************/
qspi_status_t QSPI_DRV_WriteDataInt(uint32_t instance, uint32_t *addr, uint32_t size)
{
    QuadSPI_Type * base = g_qspiBase[instance];
    /* Set state parameter. */
    g_qspiState[instance]->txSize = size;
    g_qspiState[instance]->txAddr = addr;
    g_qspiState[instance]->txFinishedBytes = 0;
    g_qspiState[instance]->isTxBusy = true;
    /* Enable interrupt flag */
    QSPI_HAL_SetIntCmd(base, kQspiTxBufferFill | kQspiTxBufferUnderrun, true);
    QSPI_HAL_EnableModule(base);
    return kStatus_QSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_WriteDataEdma
 * Description   : Write data into QSPI tx FIFO using EDMA. This function
 * will open dma enable bit and transfer data using EDMA.
 *
 *END**************************************************************************/
qspi_status_t QSPI_DRV_WriteDataEdma(uint32_t instance, uint32_t * addr, uint32_t size)
{
    QuadSPI_Type * base = g_qspiBase[instance];
    edma_transfer_config_t config = {0};
    /* Update internal state */
    g_qspiState[instance]->txSize = size;
    g_qspiState[instance]->txAddr = addr;
    g_qspiState[instance]->txFinishedBytes = 0;
    /* Request edma channel */
    if (!g_qspiState[instance]->txUseDma)
    {
        uint8_t channel = 0;
        channel = EDMA_DRV_RequestChannel(kEDMAAnyChannel, g_qspiState[instance]->txSource,
               &g_qspiState[instance]->txEdmaChn);
        if (channel == kEDMAInvalidChannel)
        {
            return kStatus_QSPI_Fail;
        }
        EDMA_DRV_InstallCallback(&g_qspiState[instance]->txEdmaChn, 
            QSPI_DRV_TxEdmaCallback, g_qspiState[instance]);
        g_qspiState[instance]->txUseDma = true;
    }
    config.srcAddr = (uint32_t)addr;
    config.destAddr = QSPI_HAL_GetTxFifoAddr(base);
    config.destTransferSize = kEDMATransferSize_4Bytes;
    config.srcTransferSize = kEDMATransferSize_4Bytes;
    config.destOffset = 0;
    config.srcOffset = 4;
    config.minorLoopCount = 4 * (FSL_FEATURE_QSPI_TXFIFO_DEPTH -g_qspiState[instance]->txWatermark);
    config.majorLoopCount = size/config.minorLoopCount;
    EDMA_DRV_PrepareDescriptorTransfer(&g_qspiState[instance]->txEdmaChn, STCD_ADDR(g_qspiState[instance]->txEdmaTCD),
            &config, true, true);
    EDMA_DRV_PushDescriptorToReg(&g_qspiState[instance]->txEdmaChn, STCD_ADDR(g_qspiState[instance]->txEdmaTCD));
    EDMA_DRV_StartChannel(&g_qspiState[instance]->txEdmaChn);
    /* Enable dma request */
    QSPI_HAL_SetDmaCmd(base, kQspiTxBufferFillDmaFlag, true);
    /* Enable interrupt to clear the underrun. */
    QSPI_HAL_SetIntCmd(base, kQspiTxBufferUnderrun, true);
    /* Enable module */
    QSPI_HAL_EnableModule(base);
    g_qspiState[instance]->isTxBusy = true;
    return kStatus_QSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_ReadDataInt
 * Description   : Read data from QSPI rx FIFO/Buffer using interrupt way. This function
 * will open interrupt enable bit and transfer data in ISR.
 *
 *END**************************************************************************/
void QSPI_DRV_ReadDataInt(uint32_t instance, uint32_t * addr, uint32_t size)
{
    QuadSPI_Type *base = g_qspiBase[instance];
    g_qspiState[instance]->rxAddr = addr;
    g_qspiState[instance]->rxSize = size;
    g_qspiState[instance]->rxFinishedBytes = 0;
    g_qspiState[instance]->isRxBusy = true;
    /* Enable Rx interrupt flag */
    QSPI_HAL_SetIntCmd(base, kQspiRxBufferDrain | kQspiRxBufferOverflow, true);
    QSPI_HAL_EnableModule(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_ReadDataEdma
 * Description   : Read data from QSPI rx FIFO/Buffer using EDMA way. This function
 * will open dma enable bit and transfer data in ISR.
 *
 *END**************************************************************************/
void QSPI_DRV_ReadDataEdma(uint32_t instance, uint32_t * addr, uint32_t size)
{
    QuadSPI_Type * base = g_qspiBase[instance]; 
    edma_transfer_config_t config = {0};
    /* Update internal state */
    g_qspiState[instance]->rxSize = size;
    g_qspiState[instance]->rxAddr = addr;
    g_qspiState[instance]->rxFinishedBytes = 0;
    if (!g_qspiState[instance]->rxUseDma)
    {
        /* Request edma channel */
        uint8_t channel = 0;
        channel = EDMA_DRV_RequestChannel(kEDMAAnyChannel, g_qspiState[instance]->rxSource,
               &g_qspiState[instance]->rxEdmaChn);
        if (channel == kEDMAInvalidChannel)
        {
            return;
        }
        EDMA_DRV_InstallCallback(&g_qspiState[instance]->rxEdmaChn, 
            QSPI_DRV_RxEdmaCallback, g_qspiState[instance]);
        g_qspiState[instance]->rxUseDma = true;
    }
    config.destAddr = (uint32_t)addr;
    config.destOffset = 4;
    config.destTransferSize = kEDMATransferSize_4Bytes;
    /* AHB buffer or ARDB */
    config.srcAddr = QSPI_HAL_GetRxFifoAddr(base);
    config.srcTransferSize = kEDMATransferSize_4Bytes;
    config.srcOffset = 0;
    config.minorLoopCount = 4 * g_qspiState[instance]->rxWatermark;
    config.majorLoopCount = size/config.minorLoopCount;
    EDMA_DRV_PrepareDescriptorTransfer(&g_qspiState[instance]->rxEdmaChn, STCD_ADDR(g_qspiState[instance]->rxEdmaTCD),
            &config, true, true);
    EDMA_DRV_PushDescriptorToReg(&g_qspiState[instance]->rxEdmaChn, STCD_ADDR(g_qspiState[instance]->rxEdmaTCD));
    EDMA_DRV_StartChannel(&g_qspiState[instance]->rxEdmaChn);
    /* Enable dma request */
    QSPI_HAL_SetDmaCmd(base, kQspiRxBufferDrainDmaFlag, true);
    /* Enable interrupt to clear the underrun. */
    QSPI_HAL_SetIntCmd(base, kQspiRxBufferOverflow, true);
    /* Enable module */
    QSPI_HAL_EnableModule(base);
    g_qspiState[instance]->isRxBusy = true;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_GetTxStatus
 * Description   : Get the tx transfer status, if busy return kStatus_QSPI_DeviceBusy.
 *
 *END**************************************************************************/
qspi_status_t QSPI_DRV_GetTxStatus(uint32_t instance)
{
    if (g_qspiState[instance]->isTxBusy)
    {
        return kStatus_QSPI_DeviceBusy;
    }
    else
    {
        return kStatus_QSPI_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_GetRxStatus
 * Description   : Get the rx transfer status, if busy return kStatus_QSPI_DeviceBusy.
 *
 *END**************************************************************************/
qspi_status_t QSPI_DRV_GetRxStatus(uint32_t instance)
{
    if (g_qspiState[instance]->isRxBusy)
    {
        return kStatus_QSPI_DeviceBusy;
    }
    else
    {
        return kStatus_QSPI_Success;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_UpdateLUT
 * Description   : Update the Look up table with input sequence. This function
 * will unlock LUT before writing into LUT, and after finished, lock the LUT.
 *
 *END**************************************************************************/
void QSPI_DRV_UpdateLUT(uint32_t instance, uint32_t index, uint32_t *cmd)
{
    QuadSPI_Type * base = g_qspiBase[instance];
    uint8_t i = 0;
    QSPI_HAL_UnlockLUT(base);
    for (i = 0; i < 4; i ++)
    {
        QSPI_HAL_SetLUT(base, index, *cmd);
        index ++;
        cmd ++;
    }
    QSPI_HAL_LockLUT(base);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_ExecuteFlashCommand
 * Description   : Execute the flash ip command. This function will trigger a 
 * new IP command.
 *
 *END**************************************************************************/
void QSPI_DRV_ExecuteFlashCommand(uint32_t instance, uint32_t index)
{
    while((QSPI_HAL_GetState(QuadSPI0, kQspiBusy)) && (QSPI_HAL_GetState(QuadSPI0, kQspiIPAccess))){}
    QSPI_HAL_ClearSeqId(QuadSPI0, kQspiIPSeq);
    QSPI_HAL_SetIPCommandSeqIndex(g_qspiBase[instance], index/4);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_ExecuteBufferCommand
 * Description   : Execute the buffer command. This function will trigger a 
 * new buffer command.
 *
 *END**************************************************************************/
void QSPI_DRV_ExecuteBufferCommand(uint32_t instance, uint32_t index)
{
    while((QSPI_HAL_GetState(QuadSPI0, kQspiBusy)) && (QSPI_HAL_GetState(QuadSPI0, kQspiAHBAccess))){}
    QSPI_HAL_ClearSeqId(QuadSPI0, kQspiBufferSeq);
    QSPI_HAL_SetBufferCommandSeqIndex(g_qspiBase[instance], index/4);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_TxIrqHandler
 * Description   : Irq handler for QSPI tx, in ISR it will handler some error flag
 * and transfer data.
 *
 *END**************************************************************************/
void QSPI_DRV_TxIrqHandler(uint32_t instance)
{
    QuadSPI_Type * base = g_qspiBase[instance];
    uint32_t * addr = g_qspiState[instance]->txAddr + g_qspiState[instance]->txFinishedBytes/4;
    uint32_t len = (g_qspiState[instance]->txSize - g_qspiState[instance]->txFinishedBytes)/4;
    uint8_t i = 0;
    if (QSPI_HAL_GetStateFlag(base,kQspiTxBufferUnderrun))
    {
        /* If underrun, clear the flag */
        QSPI_HAL_ClearStateFlag(base, kQspiTxBufferUnderrun);
        g_qspiState[instance]->err ++;
    }
    if ((QSPI_HAL_GetStateFlag(base, kQspiTxBufferFill)) && (!g_qspiState[instance]->txUseDma))
    {
        if (len >= (FSL_FEATURE_QSPI_TXFIFO_DEPTH- g_qspiState[instance]->txWatermark))
        {
            len = FSL_FEATURE_QSPI_TXFIFO_DEPTH- g_qspiState[instance]->txWatermark;
        }
        //QSPI_HAL_ClearStateFlag(base, kQspiTxBufferFill);
        for (i = 0; i < len; i ++)
        {
            QSPI_HAL_WriteData(base, *addr);
            addr ++;
            g_qspiState[instance]->txFinishedBytes += 4;
        }
        /* Check if finished */
        if (g_qspiState[instance]->txFinishedBytes == g_qspiState[instance]->txSize)
        {
            g_qspiState[instance]->isTxBusy = false;
            QSPI_HAL_SetIntCmd(base,kQspiTxBufferFill | kQspiTxBufferUnderrun,false);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_RxIrqHandler
 * Description   : Irq handler for QSPI rx, in ISR it will handler some error flag
 * and transfer data.
 *
 *END**************************************************************************/
void QSPI_DRV_RxIrqHandler(uint32_t instance)
{
    QuadSPI_Type * base = g_qspiBase[instance];
    uint32_t * addr = g_qspiState[instance]->rxAddr + g_qspiState[instance]->rxFinishedBytes/4;
    uint32_t len = (g_qspiState[instance]->rxSize - g_qspiState[instance]->rxFinishedBytes)/4;
    uint8_t i = 0;
    if (QSPI_HAL_GetStateFlag(base,kQspiRxBufferOverflow))
    {
        /* If underrun, clear the flag */
        QSPI_HAL_ClearStateFlag(base, kQspiRxBufferOverflow);
    }
    if ((QSPI_HAL_GetStateFlag(base, kQspiRxBufferDrain)) && (!g_qspiState[instance]->rxUseDma))
    {
        if (len >= g_qspiState[instance]->rxWatermark)
        {
            len = g_qspiState[instance]->rxWatermark;
        }
        for (i = 0; i < len; i ++)
        {
            *addr = QSPI_HAL_ReadData(base, i);
            addr ++;
            g_qspiState[instance]->rxFinishedBytes += 4;
        }
        /* Check if finished */
        if (g_qspiState[instance]->rxFinishedBytes == g_qspiState[instance]->rxSize)
        {
            g_qspiState[instance]->isRxBusy = false;
            QSPI_HAL_SetIntCmd(base,kQspiRxBufferDrain | kQspiRxBufferOverflow,false);
        }
    } 
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_TxEdmaCallback
 * Description   : EDMA callback function for QSPI tx, this will be called while
 * QSPI finished the transfer.
 *
 *END**************************************************************************/
void QSPI_DRV_TxEdmaCallback(void *param, edma_chn_status_t status)
{
    qspi_state_t  *state = (qspi_state_t *)param;
    EDMA_DRV_StopChannel(&state->txEdmaChn);
    state->isTxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QSPI_DRV_RxEdmaCallback
 * Description   : EDMA callback function for QSPI rx, this will be called while
 * QSPI finished the reading.
 *
 *END**************************************************************************/
void QSPI_DRV_RxEdmaCallback(void *param, edma_chn_status_t status)
{
    qspi_state_t  *state = (qspi_state_t *)param;
    EDMA_DRV_StopChannel(&state->rxEdmaChn);
    state->isRxBusy = false;
}

#endif

