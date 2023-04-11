/***************************************************************************//**
* \file cy_smif.c
* \version 2.40
*
* \brief
*  This file provides the source code for the SMIF driver APIs.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2016-2022 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXSMIF)

#include "cy_smif.h"
#include "cy_sysclk.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
* Function Name: Cy_SMIF_Init
****************************************************************************//**
*
* This function initializes the SMIF block as a communication block. The user
* must ensure that the SMIF interrupt is disabled while this function
* is called. Enabling the interrupts can lead to triggering in the middle
* of the initialization operation, which can lead to erroneous initialization.
*
* As parameters, this function takes the SMIF register base address and a
* context structure along with the configuration needed for the SMIF block,
* stored in a config
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param config
* Passes a configuration structure that configures the SMIF block for operation.
*
* \param timeout
* A timeout in microseconds for blocking APIs in use.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \note Make sure that the interrupts are initialized and disabled.
*
* \return
*     - \ref CY_SMIF_BAD_PARAM
*     - \ref CY_SMIF_SUCCESS
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_Init(SMIF_Type *base,
                                    cy_stc_smif_config_t const *config,
                                    uint32_t timeout,
                                    cy_stc_smif_context_t *context)
{
    cy_en_smif_status_t result = CY_SMIF_BAD_PARAM;

    if((NULL != base) && (NULL != config) && (NULL != context))
    {
        uint32_t smif_ctl_vlaue = SMIF_CTL(base);

        /* Copy the base address of the SMIF and the SMIF Device block
        * registers to the context.
        */
        context->timeout = timeout;

        /* Default initialization */
        context->memReadyPollDealy = 0U;

#if(CY_IP_MXSMIF_VERSION>=2)
        /* Default initialization */
        context->preXIPDataRate = CY_SMIF_SDR;
#endif /* CY_IP_MXSMIF_VERSION */

        /* SMIF is running already in XIP/ARB mode. Do not modify register configuration */
        if ((_FLD2VAL(SMIF_CTL_ENABLED, smif_ctl_vlaue) == 0U) && (_FLD2VAL(SMIF_CTL_XIP_MODE, smif_ctl_vlaue) != 1U))
        {
            /* Configure the initial interrupt mask */
            /* Disable the TR_TX_REQ and TR_RX_REQ interrupts */
            Cy_SMIF_SetInterruptMask(base, Cy_SMIF_GetInterruptMask(base)
                        & ~(SMIF_INTR_TR_TX_REQ_Msk | SMIF_INTR_TR_RX_REQ_Msk));

            /* Check config structure */
            CY_ASSERT_L3(CY_SMIF_MODE_VALID(config->mode));
            CY_ASSERT_L3(CY_SMIF_CLOCK_SEL_VALID(config->rxClockSel));
            CY_ASSERT_L2(CY_SMIF_DESELECT_DELAY_VALID(config->deselectDelay));
            CY_ASSERT_L3(CY_SMIF_BLOCK_EVENT_VALID(config->blockEvent));

            /* Configure the SMIF interface */
            SMIF_CTL(base) = (uint32_t)(_VAL2FLD(SMIF_CTL_XIP_MODE, config->mode) |
#if (CY_IP_MXSMIF_VERSION<=3)
                           _VAL2FLD(SMIF_CTL_CLOCK_IF_RX_SEL, config->rxClockSel) |
#endif
                           _VAL2FLD(SMIF_CTL_DESELECT_DELAY, config->deselectDelay) |
                           _VAL2FLD(SMIF_CTL_BLOCK, config->blockEvent) );
        }

        result = CY_SMIF_SUCCESS;
    }

    return result;
}


/*******************************************************************************
* Function Name: Cy_SMIF_DeInit
****************************************************************************//**
*
* This function de-initializes the SMIF block to default values.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \note The SMIF must be disabled before calling the function. Call
*  \ref Cy_SMIF_Disable
*
*******************************************************************************/
void Cy_SMIF_DeInit(SMIF_Type *base)
{
    uint32_t idx;

    /* Configure the SMIF interface to default values.
    * The default value is 0.
    */
    SMIF_CTL(base) = CY_SMIF_CTL_REG_DEFAULT;
    SMIF_TX_DATA_FIFO_CTL(base) = 0U;
    SMIF_RX_DATA_FIFO_CTL(base) = 0U;
    SMIF_INTR_MASK(base) = 0U;

    for(idx = 0UL; idx < SMIF_DEVICE_NR; idx++)
    {
        SMIF_DEVICE_IDX_CTL(base, idx) = 0U;
    }
}


/*******************************************************************************
* Function Name: Cy_SMIF_SetMode
****************************************************************************//**
*
* Sets the mode of operation for the SMIF. The mode of operation can be the XIP
* mode where the slave devices are mapped as memories and are directly accessed
* from the PSoC register map. In the MMIO mode, the SMIF block acts as a simple
* SPI engine. MMIO mode and XIP modes are mutually exclusive. SMIF IP Version 3
* and above support MMIO mode transactions even when XIP mode is enabled. However,
* user has to ensure that XIP transaction is not issued during an ongoing MMIO
* transaction. Rather wait for MMIO transaction to complete since few MMIO operations
* make external flash busy and it cannot respond to XIP read transaction.
*
* \note With SMIF V1 IP, Interrupt and triggers are not working in XIP mode, see TRM for details
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param mode
* The mode of the SMIF operation.
*
*******************************************************************************/
void Cy_SMIF_SetMode(SMIF_Type *base, cy_en_smif_mode_t mode)
{
    CY_ASSERT_L3(CY_SMIF_MODE_VALID(mode));

    /*  Set the register SMIF.CTL.XIP_MODE = TRUE */
    if (CY_SMIF_NORMAL == mode)
    {
        SMIF_CTL(base) &= ~ SMIF_CTL_XIP_MODE_Msk;
    }
    else
    {
#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
        uint32_t read_cmd_data_ctl;
        uint8_t idx;

        /* Context variable is not available in this API. To make the API backward compatible
         * we search if any of the device uses XIP and pick the data rate from that device.
         * Multiple devices supporting XIP mode is not supported with the version of driver.
         */

        for(idx = 0U; idx < SMIF_DEVICE_NR; idx++)
        {
            read_cmd_data_ctl = SMIF_DEVICE_IDX_RD_DATA_CTL(base, idx);

            if ((read_cmd_data_ctl & SMIF_DEVICE_RD_DATA_CTL_DDR_MODE_Msk) != 0UL)
            {
                    uint32_t temp;
                    /* Select TX Clock mode SDR/DDR */
                    temp = SMIF_CTL(base);
                    temp &= ~(SMIF_CTL_CLOCK_IF_TX_SEL_Msk);
                    SMIF_CTL(base) =  temp | _VAL2FLD(SMIF_CTL_CLOCK_IF_TX_SEL, CY_SMIF_DDR);
                    break;
            }
        }
#endif /* CY_IP_MXSMIF_VERSION */
        SMIF_CTL(base) |= SMIF_CTL_XIP_MODE_Msk;
    }
}


/*******************************************************************************
* Function Name: Cy_SMIF_GetMode
****************************************************************************//**
*
* Reads the mode of operation for the SMIF. The mode of operation can be the
* XIP mode where the slave devices are mapped as memories and are directly
* accessed from the PSoC register map. In the MMIO mode, the SMIF block acts as
* a simple SPI engine.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \return The mode of SMIF operation (see \ref cy_en_smif_mode_t).
*
*******************************************************************************/
cy_en_smif_mode_t Cy_SMIF_GetMode(SMIF_Type const *base)
{
    cy_en_smif_mode_t result = CY_SMIF_NORMAL;

    /* Read the register SMIF.CTL.XIP_MODE */
    if (0U != (SMIF_CTL(base) & SMIF_CTL_XIP_MODE_Msk))
    {
        result = CY_SMIF_MEMORY;
    }

    return (result);
}


/*******************************************************************************
* Function Name: Cy_SMIF_SetDataSelect
****************************************************************************//**
*
* This function configures the data select option for a specific slave. The
* selection provides pre-set combinations for connecting the SMIF data lines to
* the GPIOs.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param slaveSelect
* The slave device ID. This number is either CY_SMIF_SLAVE_SELECT_0 or
* CY_SMIF_SLAVE_SELECT_1 or CY_SMIF_SLAVE_SELECT_2 or CY_SMIF_SLAVE_SELECT_3
* (\ref cy_en_smif_slave_select_t). It defines the slave select line to be used
* during the transmission.
*
* \param dataSelect
* This parameter selects the data select option. \ref cy_en_smif_data_select_t
*
*******************************************************************************/
void Cy_SMIF_SetDataSelect(SMIF_Type *base, cy_en_smif_slave_select_t slaveSelect,
                            cy_en_smif_data_select_t dataSelect)
{
    SMIF_DEVICE_Type volatile *device;

    CY_ASSERT_L3(CY_SMIF_SLAVE_SEL_VALID(slaveSelect));
    CY_ASSERT_L3(CY_SMIF_DATA_SEL_VALID(dataSelect));

    /* Connect the slave to its data lines */
    device = Cy_SMIF_GetDeviceBySlot(base, slaveSelect);

    if(NULL != device)
    {
        SMIF_DEVICE_CTL(device) = _CLR_SET_FLD32U(SMIF_DEVICE_CTL(device),
                                                  SMIF_DEVICE_CTL_DATA_SEL,
                                                  (uint32_t)dataSelect);
    }
}


/*******************************************************************************
* Function Name: Cy_SMIF_TransmitCommand()
****************************************************************************//**
*
* This function transmits a command byte followed by a parameter which is
* typically an address field. The transfer is implemented using the TX FIFO.
* This function also asserts the slave select line.
* A command to a memory device generally starts with a command byte
* transmission. This function sets up the slave lines for the rest of the
* command structure. The \ref Cy_SMIF_TransmitCommand is called before \ref
* Cy_SMIF_TransmitData or \ref Cy_SMIF_ReceiveData is called. When enabled, the
* completeTxfr parameter in the function will de-assert the slave select line at
* the end of the function execution.
*
* \note This function blocks until all the command and associated parameters
* have been transmitted over the SMIF block or timeout expire.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param cmd
* The command byte to be transmitted.
*
* \param cmdTxfrWidth
* The width of command byte transfer \ref cy_en_smif_txfr_width_t.
*
* \param cmdParam
* This is the pointer to an array that has bytes to be transmitted
* after the command byte. Typically, this field has the address bytes
* associated with the memory command.
*
* \param paramSize
* The size of the cmdParam array.
*
* \param paramTxfrWidth
* The width of parameter transfer \ref cy_en_smif_txfr_width_t.
*
* \param slaveSelect
* Denotes the number of the slave device to which the transfer is made.
* (0, 1, 2 or 4 - the bit defines which slave to enable) Two-bit enable is
* possible only for the double quad SPI mode.
*
* \param completeTxfr
* Specifies if the slave select line must be de-asserted after transferring
* the last byte in the parameter array. Typically, this field is set to 0 when
* this function succeed through \ref Cy_SMIF_TransmitData or \ref
* Cy_SMIF_ReceiveData.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \return A status of the command transmit.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*
* \note Check \ref group_smif_usage_rules for any usage restriction
*
*******************************************************************************/
cy_en_smif_status_t  Cy_SMIF_TransmitCommand(SMIF_Type *base,
                                uint8_t cmd,
                                cy_en_smif_txfr_width_t cmdTxfrWidth,
                                uint8_t const cmdParam[],
                                uint32_t paramSize,
                                cy_en_smif_txfr_width_t paramTxfrWidth,
                                cy_en_smif_slave_select_t  slaveSelect,
                                uint32_t completeTxfr,
                                cy_stc_smif_context_t const *context)
{
#if (CY_IP_MXSMIF_VERSION>=2)
   return Cy_SMIF_TransmitCommand_Ext(base,
                                      (uint16_t)cmd,
                                      false,
                                      cmdTxfrWidth,
                                      CY_SMIF_SDR,
                                      cmdParam,
                                      paramSize,
                                      paramTxfrWidth,
                                      CY_SMIF_SDR,
                                      slaveSelect,
                                      completeTxfr,
                                      context);
#else
        /* The return variable */
        cy_en_smif_status_t result = CY_SMIF_SUCCESS;

        /* Check input values */
        CY_ASSERT_L3(CY_SMIF_TXFR_WIDTH_VALID(cmdTxfrWidth));
        CY_ASSERT_L3(CY_SMIF_TXFR_WIDTH_VALID(paramTxfrWidth));
        CY_ASSERT_L3(CY_SMIF_SLAVE_SEL_VALID(slaveSelect));
        CY_ASSERT_L1(CY_SMIF_CMD_PARAM_VALID(cmdParam, paramSize));
        CY_ASSERT_L1(CY_SMIF_WIDTH_NA_VALID(paramTxfrWidth, paramSize));

        uint8_t bufIndex = 0U;
        /* The common part of a command and parameter transfer */
        uint32_t const constCmdPart = (
            _VAL2FLD(CY_SMIF_CMD_FIFO_WR_MODE, CY_SMIF_CMD_FIFO_TX_MODE) |
            _VAL2FLD(CY_SMIF_CMD_FIFO_WR_SS, slaveSelect));
        uint32_t timeoutUnits = context->timeout;

        /* Send the command byte */
        SMIF_TX_CMD_FIFO_WR(base) = constCmdPart |
            _VAL2FLD(CY_SMIF_CMD_FIFO_WR_WIDTH, (uint32_t) cmdTxfrWidth) |
            _VAL2FLD(CY_SMIF_CMD_FIFO_WR_TXDATA, (uint32_t) cmd) |
            _VAL2FLD(CY_SMIF_CMD_FIFO_WR_LAST_BYTE,
                ((0UL == paramSize) ? completeTxfr : 0UL)) ;

        /* Send the command parameters (usually address) in the blocking mode */
        while ((bufIndex < paramSize) && (CY_SMIF_EXCEED_TIMEOUT != result))
        {
            /* Check if there is at least one free entry in TX_CMD_FIFO */
            if  (Cy_SMIF_GetCmdFifoStatus(base) < CY_SMIF_TX_CMD_FIFO_STATUS_RANGE)
            {
                SMIF_TX_CMD_FIFO_WR(base) = constCmdPart|
                    _VAL2FLD(CY_SMIF_CMD_FIFO_WR_TXDATA,
                            (uint32_t) cmdParam[bufIndex]) |
                    _VAL2FLD(CY_SMIF_CMD_FIFO_WR_WIDTH,
                            (uint32_t) paramTxfrWidth) |
                    _VAL2FLD(CY_SMIF_CMD_FIFO_WR_LAST_BYTE,
                                ((((uint32_t)bufIndex + 1UL) < paramSize) ?
                                0UL : completeTxfr));

                bufIndex++;
            }
            result = Cy_SMIF_TimeoutRun(&timeoutUnits);
        }

        return (result);
#endif /* CY_IP_MXSMIF_VERSION */
}


/*******************************************************************************
* Function Name: Cy_SMIF_TransmitData
****************************************************************************//**
*
* This function is used to transmit data using the SMIF interface. This
* function uses the TX Data FIFO to implement the transmit functionality. The
* function sets up an interrupt to trigger the TX Data FIFO and uses that
* interrupt to fill the TX Data FIFO until all the data is transmitted. At the
* end of the transmission, the TxCompleteCb is executed.
*
* \note  This function is to be preceded by \ref Cy_SMIF_TransmitCommand where
* the slave select is selected. The slave is de-asserted at the end of a
* transmit. The function triggers the transfer and the transfer itself utilizes
* the interrupt for FIFO operations in the background. Thus, frequent
* interrupts will be executed after this function is triggered.
* Since this API is non-blocking and sets up the interrupt to act on the data
* FIFO, ensure there will be no another instance of the function called
* before the current instance has completed execution.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param txBuffer
* The pointer to the data to be transferred. If this pointer is a NULL, then the
* function does not enable the interrupt. This use case is typically used when
* the FIFO is handled outside the interrupt and is managed in either a
* polling-based code or a DMA. The user would handle the FIFO management in a
* DMA or a polling-based code.
*
* \note If the user provides a NULL pointer in this function and does not handle
* the FIFO transaction, this could either stall or timeout the operation.
* The transfer statuses returned by \ref Cy_SMIF_GetTransferStatus are no longer
* valid.
*
* \param size
* The size of txBuffer. Must be > 0 and not greater than 65536.
*
* \param transferWidth
* The width of transfer \ref cy_en_smif_txfr_width_t.
*
* \param TxCompleteCb
* The callback executed at the end of a transmission. NULL interpreted as no
* callback.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \return A status of a transmission.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_FIFO_FULL
*
*******************************************************************************/
cy_en_smif_status_t  Cy_SMIF_TransmitData(SMIF_Type *base,
                            uint8_t const *txBuffer,
                            uint32_t size,
                            cy_en_smif_txfr_width_t transferWidth,
                            cy_smif_event_cb_t TxCompleteCb,
                            cy_stc_smif_context_t *context)
{

#if (CY_IP_MXSMIF_VERSION>=2)
    return Cy_SMIF_TransmitData_Ext(base,
                                    txBuffer,
                                    size,
                                    transferWidth,
                                    CY_SMIF_SDR,
                                    TxCompleteCb,
                                    context);
#else
    /* The return variable */
    cy_en_smif_status_t result = CY_SMIF_CMD_FIFO_FULL;

    /* Check input values */
    CY_ASSERT_L3(CY_SMIF_TXFR_WIDTH_VALID(transferWidth));
    CY_ASSERT_L2(CY_SMIF_BUF_SIZE_VALID(size));

    /* Check if there are enough free entries in TX_CMD_FIFO */
    if  (Cy_SMIF_GetCmdFifoStatus(base) < CY_SMIF_TX_CMD_FIFO_STATUS_RANGE)
    {
        /* Enter the transmitting mode */
        SMIF_TX_CMD_FIFO_WR(base) =
            _VAL2FLD(CY_SMIF_CMD_FIFO_WR_MODE, CY_SMIF_CMD_FIFO_TX_COUNT_MODE) |
            _VAL2FLD(CY_SMIF_CMD_FIFO_WR_WIDTH, (uint32_t)transferWidth)    |
            _VAL2FLD(CY_SMIF_CMD_FIFO_WR_TX_COUNT, (size - 1UL));

        if (NULL != txBuffer)
        {
            /* Move the parameters to the global variables */
            context->txBufferAddress = txBuffer;
            context->txBufferSize = size;
            context->txBufferCounter = size;
            context->txCompleteCb = TxCompleteCb;
            context->transferStatus = (uint32_t) CY_SMIF_SEND_BUSY;

            /* Enable the TR_TX_REQ interrupt */
            Cy_SMIF_SetInterruptMask(base,
                                     Cy_SMIF_GetInterruptMask(base) |
                                     SMIF_INTR_TR_TX_REQ_Msk);
        }
        result = CY_SMIF_SUCCESS;
    }

    return (result);
#endif /* CY_IP_MXSMIF_VERSION */
}


/*******************************************************************************
* Function Name: Cy_SMIF_TransmitDataBlocking
****************************************************************************//**
*
* This function implements the transmit data phase in the memory command. The
* data is transmitted using the Tx Data FIFO and the TX_COUNT command. This
* function blocks until completion. The function does not use the interrupts and
* will use CPU to monitor the FIFO status and move data accordingly. The
* function returns only on completion.
*
* \note  Since this API is blocking, ensure that other transfers finished and it
* will not be called during non-blocking transfer.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param txBuffer
* The pointer to the data to be transferred. If this pointer is a NULL, then the
* function does not fill TX_FIFO. The user would handle the FIFO management in a
* DMA or a polling-based code.
*
* \note If the user provides a NULL pointer in this function and does not handle
* the FIFO transaction, this could either stall or timeout the operation.
* The transfer statuses returned by \ref Cy_SMIF_GetTransferStatus are no longer
* valid.
*
* \param size
* The size of txBuffer. Must be > 0 and not greater than 65536.
*
* \param transferWidth
* The width of transfer \ref cy_en_smif_txfr_width_t.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \return A status of a transmission.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_FIFO_FULL
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_BAD_PARAM
*
*******************************************************************************/
cy_en_smif_status_t  Cy_SMIF_TransmitDataBlocking(SMIF_Type *base,
                            uint8_t const *txBuffer,
                            uint32_t size,
                            cy_en_smif_txfr_width_t transferWidth,
                            cy_stc_smif_context_t const *context)
{
#if (CY_IP_MXSMIF_VERSION>=2)
     return Cy_SMIF_TransmitDataBlocking_Ext(base,
                                             txBuffer,
                                             size,
                                             transferWidth,
                                             CY_SMIF_SDR,
                                             context);
#else
    /* The return variable */
    cy_en_smif_status_t result = CY_SMIF_BAD_PARAM;

    /* Check input values */
    CY_ASSERT_L3(CY_SMIF_TXFR_WIDTH_VALID(transferWidth));

    if(size > 0U)
    {
        result = CY_SMIF_CMD_FIFO_FULL;
        /* Check if there are enough free entries in TX_CMD_FIFO */
        if  (Cy_SMIF_GetCmdFifoStatus(base) < CY_SMIF_TX_CMD_FIFO_STATUS_RANGE)
        {
            /* Enter the transmitting mode */
            SMIF_TX_CMD_FIFO_WR(base) =
                _VAL2FLD(CY_SMIF_CMD_FIFO_WR_MODE, CY_SMIF_CMD_FIFO_TX_COUNT_MODE) |
                _VAL2FLD(CY_SMIF_CMD_FIFO_WR_WIDTH, (uint32_t)transferWidth)    |
                _VAL2FLD(CY_SMIF_CMD_FIFO_WR_TX_COUNT, (size - 1UL));

            result = CY_SMIF_SUCCESS;

            if (NULL != txBuffer)
            {
                uint32_t timeoutUnits = context->timeout;
                cy_stc_smif_context_t contextLoc;

                /* initialize parameters for Cy_SMIF_PushTxFifo */
                contextLoc.txBufferAddress = txBuffer;
                contextLoc.txBufferCounter = size;
                contextLoc.txCompleteCb = NULL;
                contextLoc.transferStatus = (uint32_t) CY_SMIF_SEND_BUSY;

                while (((uint32_t) CY_SMIF_SEND_BUSY == contextLoc.transferStatus) &&
                        (CY_SMIF_EXCEED_TIMEOUT != result))
                {
                    Cy_SMIF_PushTxFifo(base, &contextLoc);
                    result = Cy_SMIF_TimeoutRun(&timeoutUnits);
                }
            }
        }
    }

    return (result);
#endif /* CY_IP_MXSMIF_VERSION */
}


/*******************************************************************************
* Function Name: Cy_SMIF_ReceiveData
****************************************************************************//**
*
* This function implements the receive data phase in the memory command. The
* data is received into the RX Data FIFO using the RX_COUNT command. This
* function sets up the interrupt to trigger on the RX Data FIFO level, and the
* data is fetched from the RX Data FIFO to the rxBuffer as it gets filled. This
* function does not block until completion. The completion will trigger the call
* back function.
*
* \note This function is to be preceded by \ref Cy_SMIF_TransmitCommand. The
* slave select is de-asserted at the end of the receive.
* The function triggers the transfer and the transfer itself utilizes the
* interrupt for FIFO operations in the background. Thus, frequent
* interrupts will be executed after this function is triggered.
* This API is non-blocking and sets up the interrupt to act on the data
* FIFO, ensure there will be no another instance of the function called
* before the current instance has completed execution.
*
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param rxBuffer
* The pointer to the variable where the receive data is stored. If this pointer
* is a NULL, then the function does not enable the interrupt. This use case is
* typically used when the FIFO is handled outside the interrupt and is managed
* in either a polling-based code or a DMA. The user would handle the FIFO
* management in a DMA or a polling-based code.
*
* \note If the user provides a NULL pointer in this function and does not handle
* the FIFO transaction, this could either stall or timeout the operation.
* The transfer statuses returned by \ref Cy_SMIF_GetTransferStatus are no longer
* valid.
*
* \param size
* The size of data to be received. Must be > 0 and not greater than 65536.
*
* \param transferWidth
* The width of transfer \ref cy_en_smif_txfr_width_t.
*
* \param RxCompleteCb
* The callback executed at the end of a reception. NULL interpreted as no
* callback.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \return A status of a reception.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_FIFO_FULL
*       - \ref CY_SMIF_BAD_PARAM
*
* \note Check \ref group_smif_usage_rules for any usage restriction
*
*******************************************************************************/
cy_en_smif_status_t  Cy_SMIF_ReceiveData(SMIF_Type *base,
                            uint8_t *rxBuffer,
                            uint32_t size,
                            cy_en_smif_txfr_width_t transferWidth,
                            cy_smif_event_cb_t RxCompleteCb,
                            cy_stc_smif_context_t *context)
{
#if (CY_IP_MXSMIF_VERSION>=2)
    return Cy_SMIF_ReceiveData_Ext(base,
                                   rxBuffer,
                                   size,
                                   transferWidth,
                                   CY_SMIF_SDR,
                                   RxCompleteCb,
                                   context);
#else
    /* The return variable */
    cy_en_smif_status_t result = CY_SMIF_BAD_PARAM;

    /* Check input values */
    CY_ASSERT_L3(CY_SMIF_TXFR_WIDTH_VALID(transferWidth));

    if(size > 0U)
    {
        result = CY_SMIF_CMD_FIFO_FULL;
        /* Check if there are enough free entries in TX_CMD_FIFO */
        if  (Cy_SMIF_GetCmdFifoStatus(base) < CY_SMIF_TX_CMD_FIFO_STATUS_RANGE)
        {
            /* Enter the receiving mode */
            SMIF_TX_CMD_FIFO_WR(base) =
                _VAL2FLD(CY_SMIF_CMD_FIFO_WR_MODE, CY_SMIF_CMD_FIFO_RX_COUNT_MODE) |
                _VAL2FLD(CY_SMIF_CMD_FIFO_WR_WIDTH, (uint32_t)transferWidth)    |
                _VAL2FLD(CY_SMIF_CMD_FIFO_WR_RX_COUNT, (size - 1UL));

            if (NULL != rxBuffer)
            {
                /* Move the parameters to the global variables */
                context->rxBufferAddress = (uint8_t*)rxBuffer;
                context->rxBufferSize = size;
                context->rxBufferCounter = size;
                context->rxCompleteCb = RxCompleteCb;
                context->transferStatus =  (uint32_t) CY_SMIF_RX_BUSY;

                /* Enable the TR_RX_REQ interrupt */
                Cy_SMIF_SetInterruptMask(base,
                    Cy_SMIF_GetInterruptMask(base) | SMIF_INTR_TR_RX_REQ_Msk);
            }
            result = CY_SMIF_SUCCESS;
        }
    }

    return (result);
#endif /* CY_IP_MXSMIF_VERSION */
}


/*******************************************************************************
* Function Name: Cy_SMIF_ReceiveDataBlocking
****************************************************************************//**
*
* This function implements the receive data phase in the memory command. The
* data is received into the RX Data FIFO using the RX_COUNT command. This
* function blocks until completion. The function does not use the interrupts and
* will use CPU to monitor the FIFO status and move data accordingly. The
* function returns only on completion.
*
* \note This function is to be preceded by \ref Cy_SMIF_TransmitCommand. The
* slave select is de-asserted at the end of the receive. Ensure there is
* no another transfers.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param rxBuffer
* The pointer to the variable where the receive data is stored. If this pointer
* is a NULL, then the function does not enable the interrupt. This use case is
* typically used when the FIFO is handled outside the interrupt and is managed
* in either a polling-based code or a DMA. The user would handle the FIFO
* management in a DMA or a polling-based code.
*
* \note If the user provides a NULL pointer in this function and does not handle
* the FIFO transaction, this could either stall or timeout the operation.
* The transfer statuses returned by \ref Cy_SMIF_GetTransferStatus are no longer
* valid.
*
* \param size
* The size of data to be received. Must be > 0 and not greater than 65536.
*
* \param transferWidth
* The width of transfer \ref cy_en_smif_txfr_width_t.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \return A status of a reception.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_FIFO_FULL
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_BAD_PARAM
*
* \note Check \ref group_smif_usage_rules for any usage restriction
*
*******************************************************************************/
cy_en_smif_status_t  Cy_SMIF_ReceiveDataBlocking(SMIF_Type *base,
                            uint8_t *rxBuffer,
                            uint32_t size,
                            cy_en_smif_txfr_width_t transferWidth,
                            cy_stc_smif_context_t const *context)
{
#if(CY_IP_MXSMIF_VERSION>=2)
     return Cy_SMIF_ReceiveDataBlocking_Ext(base,
                            rxBuffer,
                            size,
                            transferWidth,
                            CY_SMIF_SDR,
                            context);
#else
    /* The return variable */
    cy_en_smif_status_t result = CY_SMIF_BAD_PARAM;

    /* Check input values */
    CY_ASSERT_L3(CY_SMIF_TXFR_WIDTH_VALID(transferWidth));

    if(size > 0U)
    {
        result = CY_SMIF_CMD_FIFO_FULL;
        /* Check if there are enough free entries in TX_CMD_FIFO */
        if  (Cy_SMIF_GetCmdFifoStatus(base) < CY_SMIF_TX_CMD_FIFO_STATUS_RANGE)
        {
            /* Enter the receiving mode */
            SMIF_TX_CMD_FIFO_WR(base) =
                _VAL2FLD(CY_SMIF_CMD_FIFO_WR_MODE, CY_SMIF_CMD_FIFO_RX_COUNT_MODE) |
                _VAL2FLD(CY_SMIF_CMD_FIFO_WR_WIDTH, (uint32_t)transferWidth)    |
                _VAL2FLD(CY_SMIF_CMD_FIFO_WR_RX_COUNT, (size - 1UL));
            result = CY_SMIF_SUCCESS;

            if (NULL != rxBuffer)
            {
                uint32_t timeoutUnits = context->timeout;
                cy_stc_smif_context_t contextLoc;

                /* initialize parameters for Cy_SMIF_PushTxFifo */
                contextLoc.rxBufferAddress = (uint8_t*)rxBuffer;
                contextLoc.rxBufferCounter = size;
                contextLoc.rxCompleteCb = NULL;
                contextLoc.transferStatus = (uint32_t) CY_SMIF_RX_BUSY;

                while (((uint32_t) CY_SMIF_RX_BUSY == contextLoc.transferStatus) &&
                        (CY_SMIF_EXCEED_TIMEOUT != result))
                {
                    Cy_SMIF_PopRxFifo(base, &contextLoc);
                    result = Cy_SMIF_TimeoutRun(&timeoutUnits);
                }
            }
        }
    }
    return (result);
#endif /* CY_IP_MXSMIF_VERSION */
}


/*******************************************************************************
* Function Name: Cy_SMIF_SendDummyCycles()
****************************************************************************//**
*
* This function sends dummy-clock cycles. The data lines are tri-stated during
* the dummy cycles.
*
* \note This function is to be preceded by \ref Cy_SMIF_TransmitCommand.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param cycles
* The number of dummy cycles. Must be > 0 and not greater than 65536.
*
* \return A status of dummy cycles sending.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_FIFO_FULL
*       - \ref CY_SMIF_BAD_PARAM
*
*******************************************************************************/
cy_en_smif_status_t  Cy_SMIF_SendDummyCycles(SMIF_Type *base,
                                uint32_t cycles)
{
#if(CY_IP_MXSMIF_VERSION>=2)
    return Cy_SMIF_SendDummyCycles_Ext(base,
                                       CY_SMIF_WIDTH_SINGLE,
                                       CY_SMIF_SDR,
                                       cycles);
#else
    /* The return variable */
    cy_en_smif_status_t result = CY_SMIF_BAD_PARAM;

    if (cycles > 0U)
    {
        result = CY_SMIF_CMD_FIFO_FULL;
        /* Check if there are enough free entries in TX_CMD_FIFO */
        if  (Cy_SMIF_GetCmdFifoStatus(base) < CY_SMIF_TX_CMD_FIFO_STATUS_RANGE)
        {
            /* Send the dummy bytes */
            SMIF_TX_CMD_FIFO_WR(base) =
                _VAL2FLD(CY_SMIF_CMD_FIFO_WR_MODE, CY_SMIF_CMD_FIFO_DUMMY_COUNT_MODE) |
                _VAL2FLD(CY_SMIF_CMD_FIFO_WR_DUMMY, (cycles-1UL));

            result = CY_SMIF_SUCCESS;
        }
    }

    return (result);
#endif /* CY_IP_MXSMIF_VERSION */
}


/*******************************************************************************
* Function Name: Cy_SMIF_GetTransferStatus
****************************************************************************//**
*
* This function provides the status of the transfer. This function is used to
* poll for the status of the TransmitData or receiveData function. When this
* function is called to determine the status of ongoing
* \ref Cy_SMIF_ReceiveData() or \ref Cy_SMIF_TransmitData(), the returned status
* is only valid if the functions passed a non-NULL buffer to transmit or
* receive respectively. If the pointer passed to \ref Cy_SMIF_ReceiveData()
* or \ref Cy_SMIF_TransmitData() is a NULL, then the code/DMA outside this
* driver will take care of the transfer and the Cy_GetTxfrStatus() will return
* an erroneous result.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \return Returns the transfer status. \ref cy_en_smif_txfr_status_t
*
*******************************************************************************/
uint32_t Cy_SMIF_GetTransferStatus(SMIF_Type const *base, cy_stc_smif_context_t const *context)
{
    (void)base; /* Suppress warning */
    return (context->transferStatus);
}


/*******************************************************************************
* Function Name: Cy_SMIF_Enable
****************************************************************************//**
*
* Enables the operation of the SMIF block.
*
* \note This function only enables the SMIF IP. The interrupts associated with
* the SMIF will need to be separately enabled using the interrupt driver.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
*******************************************************************************/
void Cy_SMIF_Enable(SMIF_Type *base, cy_stc_smif_context_t *context)
{
    /* Global variables initialization */
    context->txBufferAddress = NULL;
    context->txBufferSize = 0U;
    context->txBufferCounter = 0U;
    context->rxBufferAddress = NULL;
    context->rxBufferSize = 0U;
    context->rxBufferCounter = 0U;
    context->transferStatus = (uint32_t)CY_SMIF_STARTED;

    SMIF_CTL(base) |= SMIF_CTL_ENABLED_Msk;

}

#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SMIF_TransmitCommand_Ext()
****************************************************************************//**
*
* This function transmits a command byte followed by a parameter which is
* typically an address field. The transfer is implemented using the TX FIFO.
* This function also asserts the slave select line.
* A command to a memory device generally starts with a command byte
* transmission. This function sets up the slave lines for the rest of the
* command structure. The \ref Cy_SMIF_TransmitCommand_Ext is called before \ref
* Cy_SMIF_TransmitData_Ext or \ref Cy_SMIF_ReceiveData_Ext is called. When enabled, the
* completeTxfr parameter in the function will de-assert the slave select line at
* the end of the function execution.
*
* \note This function blocks until all the command and associated parameters
* have been transmitted over the SMIF block or timeout expire.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param cmd
* The command byte to be transmitted.
*
* \param isCommand2byte
* isCommand2byte
*
* \param cmdTxfrWidth
* The width of command byte transfer \ref cy_en_smif_txfr_width_t.
*
* \param cmdDataRate
* cmdDataRate
*
* \param cmdParam
* This is the pointer to an array that has bytes to be transmitted
* after the command byte. Typically, this field has the address bytes
* associated with the memory command.
*
* \param paramSize
* The size of the cmdParam array.
*
* \param paramTxfrWidth
* The width of parameter transfer \ref cy_en_smif_txfr_width_t.
*
* \param paramDataRate
* paramDataRate
*
* \param slaveSelect
* Denotes the number of the slave device to which the transfer is made.
* (0, 1, 2 or 4 - the bit defines which slave to enable) Two-bit enable is
* possible only for the Double Quad SPI mode.
*
* \param completeTxfr
* Specifies if the slave select line must be de-asserted after transferring
* the last byte in the parameter array. Typically, this field is set to 0 when
* this function succeed through \ref Cy_SMIF_TransmitData_Ext or \ref
* Cy_SMIF_ReceiveData_Ext.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \return A status of the command transmit.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_TransmitCommand_Ext(SMIF_Type *base,
                                                 uint16_t cmd,
                                                 bool isCommand2byte,
                                                 cy_en_smif_txfr_width_t cmdTxfrWidth,
                                                 cy_en_smif_data_rate_t cmdDataRate,
                                                 uint8_t const cmdParam[],
                                                 uint32_t paramSize,
                                                 cy_en_smif_txfr_width_t paramTxfrWidth,
                                                 cy_en_smif_data_rate_t paramDataRate,
                                                 cy_en_smif_slave_select_t slaveSelect,
                                                 uint32_t completeTxfr,
                                                 cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t result = CY_SMIF_SUCCESS;
#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
    uint32_t temp = 0;
#endif

    /* Check input values */
     CY_ASSERT_L3(CY_SMIF_TXFR_WIDTH_VALID(cmdTxfrWidth));
     CY_ASSERT_L3(CY_SMIF_TXFR_WIDTH_VALID(paramTxfrWidth));
     CY_ASSERT_L3(CY_SMIF_SLAVE_SEL_VALID(slaveSelect));
     CY_ASSERT_L3(CY_SMIF_CMD_DATA_RATE_VALID(cmdDataRate));
     CY_ASSERT_L3(CY_SMIF_CMD_PARAM_DATA_RATE_VALID(paramDataRate));
     CY_ASSERT_L1(CY_SMIF_CMD_PARAM_VALID(cmdParam, paramSize));
     CY_ASSERT_L1(CY_SMIF_WIDTH_NA_VALID(paramTxfrWidth, paramSize));

     uint8_t bufIndex = 0U;
     /* The common part of a command and parameter transfer */
     uint32_t const constCmdPart = (
         _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_MODE, CY_SMIF_CMD_FIFO_TX_MODE) |
         _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_SS, slaveSelect));
     uint32_t timeoutUnits = context->timeout;

#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
     /* Select TX Clock mode SDR/DDR for COMMAND */
     temp = SMIF_CTL(base);
     temp &= ~(SMIF_CTL_CLOCK_IF_TX_SEL_Msk);
     SMIF_CTL(base) =  temp | _VAL2FLD(SMIF_CTL_CLOCK_IF_TX_SEL, cmdDataRate);
#endif

    /* Prepare a cmd fifo data */
        if(isCommand2byte == true)
    {
        if((cmdTxfrWidth == CY_SMIF_WIDTH_OCTAL) && (cmdDataRate == CY_SMIF_DDR))
        {
             /* 2byte for each one command */
             SMIF_TX_CMD_MMIO_FIFO_WR(base) = constCmdPart |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_WIDTH, (uint32_t) cmdTxfrWidth) |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_DATA_RATE, (uint32_t) cmdDataRate) |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_1, (uint8_t)(cmd & 0x00FFU)) |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_2, (uint8_t)((cmd >> 8U) & 0x00FFU)) |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_LAST_BYTE,
                     ((0UL == paramSize) ? completeTxfr : 0UL)) ;
         }
         else
         {
             /* 1byte for each one command. need to send two command to send a command of 2byte.*/
             SMIF_TX_CMD_MMIO_FIFO_WR(base) = constCmdPart |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_WIDTH, (uint32_t) cmdTxfrWidth) |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_DATA_RATE, (uint32_t) cmdDataRate) |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_1, (uint8_t)((cmd >> 8U) & 0x00FFU)) |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_2, 0U) |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_LAST_BYTE,
                     ((0UL == paramSize) ? completeTxfr : 0UL)) ;

             SMIF_TX_CMD_MMIO_FIFO_WR(base) = constCmdPart |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_WIDTH, (uint32_t) cmdTxfrWidth) |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_DATA_RATE, (uint32_t) cmdDataRate) |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_1, (uint8_t)(cmd & 0x00FFU)) |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_2, 0U) |
                 _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_LAST_BYTE,
                     ((0UL == paramSize) ? completeTxfr : 0UL)) ;
         }
     }
     else
     {
         /* Send the command byte */
         SMIF_TX_CMD_MMIO_FIFO_WR(base) = constCmdPart |
             _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_WIDTH, (uint32_t) cmdTxfrWidth) |
             _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_DATA_RATE, (uint32_t) cmdDataRate) |
             _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_1, (uint8_t) cmd) |
             _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_2, (uint8_t) 0) |
             _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_LAST_BYTE,
                 ((0UL == paramSize) ? completeTxfr : 0UL)) ;
     }

#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
        /* Select TX Clock mode SDR/DDR for ADDRESS */
        temp = SMIF_CTL(base);
        temp &= ~(SMIF_CTL_CLOCK_IF_TX_SEL_Msk);
        SMIF_CTL(base) =  temp | _VAL2FLD(SMIF_CTL_CLOCK_IF_TX_SEL, paramDataRate);
#endif

    if((paramTxfrWidth == CY_SMIF_WIDTH_OCTAL) && (paramDataRate == CY_SMIF_DDR))
    {
            // 2 byte transmission for each one command.
            while ((bufIndex < paramSize) && (CY_SMIF_EXCEED_TIMEOUT != result))
            {
                /* Check if there is at least one free entry in TX_CMD_FIFO */
                if    (Cy_SMIF_GetCmdFifoStatus(base) < CY_SMIF_TX_CMD_FIFO_STATUS_RANGE)
                {
                                SMIF_TX_CMD_MMIO_FIFO_WR(base) = constCmdPart|
                    _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_1, (uint32_t) cmdParam[bufIndex+1U]) |
                    _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_2, (uint32_t) cmdParam[bufIndex])|
                    _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_WIDTH, (uint32_t) paramTxfrWidth) |
                    _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_DATA_RATE, (uint32_t) paramDataRate) |
                    _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_LAST_BYTE,
                            ((((uint32_t)bufIndex + 2UL) < paramSize) ?  0UL : completeTxfr));
                    bufIndex += 2U;
                }
                result = Cy_SMIF_TimeoutRun(&timeoutUnits);
            }
    }
    else
    {
        /* Send the command parameters (usually address) in the blocking mode */
        while ((bufIndex < paramSize) && (CY_SMIF_EXCEED_TIMEOUT != result))
        {
            /* Check if there is at least one free entry in TX_CMD_FIFO */
            if  (Cy_SMIF_GetCmdFifoStatus(base) < CY_SMIF_TX_CMD_FIFO_STATUS_RANGE)
            {
                SMIF_TX_CMD_MMIO_FIFO_WR(base) = constCmdPart|
                    _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_1, (uint32_t) cmdParam[bufIndex]) |
                    _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_2, 0)|
                    _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_WIDTH, (uint32_t) paramTxfrWidth) |
                    _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_DATA_RATE, (uint32_t) paramDataRate) |
                    _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_LAST_BYTE,
                            ((((uint32_t)bufIndex + 1UL) < paramSize) ?  0UL : completeTxfr));

                bufIndex++;
            }
            result = Cy_SMIF_TimeoutRun(&timeoutUnits);
        }
    }

#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
    /* Switch back to preferred XIP mode data rate */
    temp = SMIF_CTL(base);
    temp &= ~(SMIF_CTL_CLOCK_IF_TX_SEL_Msk);
    SMIF_CTL(base) =  temp | _VAL2FLD(SMIF_CTL_CLOCK_IF_TX_SEL, context->preXIPDataRate);
#endif
    return (result);
}

/*******************************************************************************
* Function Name: Cy_SMIF_TransmitData_Ext
****************************************************************************//**
*
* This function is used to transmit data using the SMIF interface. This
* function uses the TX Data FIFO to implement the transmit functionality. The
* function sets up an interrupt to trigger the TX Data FIFO and uses that
* interrupt to fill the TX Data FIFO until all the data is transmitted. At the
* end of the transmission, the TxCmpltCb is executed.
*
* \note  This function is to be preceded by \ref Cy_SMIF_TransmitCommand_Ext where
* the slave select is selected. The slave is de-asserted at the end of a
* transmit. The function triggers the transfer and the transfer itself utilizes
* the interrupt for FIFO operations in the background. Thus, frequent
* interrupts will be executed after this function is triggered.
* Since this API is non-blocking and sets up the interrupt to act on the data
* FIFO, ensure there will be no another instance of the function called
* before the current instance has completed execution.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param txBuffer
* The pointer to the data to be transferred. If this pointer is a NULL, then the
* function does not enable the interrupt. This use case is typically used when
* the FIFO is handled outside the interrupt and is managed in either a
* polling-based code or a DMA. The user would handle the FIFO management in a
* DMA or a polling-based code.
*
* \note If the user provides a NULL pointer in this function and does not handle
* the FIFO transaction, this could either stall or timeout the operation.
* The transfer statuses returned by \ref Cy_SMIF_GetTransferStatus are no longer
* valid.
*
* \param size
* The size of txBuffer. Must be > 0 and not greater than 65536.
*
* \param transferWidth
* The width of transfer \ref cy_en_smif_txfr_width_t.
*
* \param dataDataRate
* dataDataRate
*
* \param TxCmpltCb
* The callback executed at the end of a transmission. NULL interpreted as no
* callback.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \return A status of a transmission.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_FIFO_FULL
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_TransmitData_Ext(SMIF_Type *base,
                                                uint8_t const *txBuffer,
                                                uint32_t size,
                                                cy_en_smif_txfr_width_t transferWidth,
                                                cy_en_smif_data_rate_t dataDataRate,
                                                cy_smif_event_cb_t TxCmpltCb,
                                                cy_stc_smif_context_t *context)
{
    /* The return variable */
    cy_en_smif_status_t result = CY_SMIF_CMD_FIFO_FULL;
    uint32_t trUnitNum;
#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
    uint32_t temp = 0;
#endif

    /* Check input values */
    CY_ASSERT_L3(CY_SMIF_TXFR_WIDTH_VALID(transferWidth));
    CY_ASSERT_L2(CY_SMIF_BUF_SIZE_VALID(size));

#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
    /* Select TX Clock mode SDR/DDR */
    temp = SMIF_CTL(base);
    temp &= ~(SMIF_CTL_CLOCK_IF_TX_SEL_Msk);
    SMIF_CTL(base) =  temp | _VAL2FLD(SMIF_CTL_CLOCK_IF_TX_SEL, dataDataRate);
#endif

    /* If the mode is octal SPI with DDR data unit is a 2-byte */
    if((transferWidth == CY_SMIF_WIDTH_OCTAL) && (dataDataRate == CY_SMIF_DDR))
    {
        if(size % 2U != 0U)
        {
            return CY_SMIF_BAD_PARAM;
        }
        trUnitNum = size / 2U;
    }
    else
    {
        trUnitNum = size;
    }

    /* Check if there are enough free entries in TX_CMD_FIFO */
    if  (Cy_SMIF_GetCmdFifoStatus(base) < CY_SMIF_TX_CMD_FIFO_STATUS_RANGE)
    {
        /* Enter the transmitting mode */
        SMIF_TX_CMD_MMIO_FIFO_WR(base) =
            _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_MODE, CY_SMIF_CMD_FIFO_TX_COUNT_MODE) |
            _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_WIDTH, (uint32_t)transferWidth)    |
            _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_DATA_RATE, (uint32_t) dataDataRate) |
            _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TX_COUNT, (trUnitNum - 1UL))|
            _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_LAST_BYTE, 1U);

        if (NULL != txBuffer)
        {
            /* Move the parameters to the global variables */
            context->txBufferAddress = (uint8_t*)txBuffer;
            context->txBufferSize = size;
            context->txBufferCounter = size;
            context->txCompleteCb = TxCmpltCb;
            context->transferStatus = (uint32_t) CY_SMIF_SEND_BUSY;
            context->preCmdDataRate        = dataDataRate;
            context->preCmdWidth           = transferWidth;

            /* Enable the TR_TX_REQ interrupt */
            Cy_SMIF_SetInterruptMask(base,
                                     Cy_SMIF_GetInterruptMask(base) |
                                     SMIF_INTR_TR_TX_REQ_Msk);
        }
        result = CY_SMIF_SUCCESS;
    }

#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
    /* Switch back to preferred XIP mode data rate */
    temp = SMIF_CTL(base);
    temp &= ~(SMIF_CTL_CLOCK_IF_TX_SEL_Msk);
    SMIF_CTL(base) =  temp | _VAL2FLD(SMIF_CTL_CLOCK_IF_TX_SEL, context->preXIPDataRate);
#endif

    return (result);
}

/*******************************************************************************
* Function Name: Cy_SMIF_TransmitDataBlocking_Ext
****************************************************************************//**
*
* This function implements the transmit data phase in the memory command. The
* data is transmitted using the Tx Data FIFO and the TX_COUNT command. This
* function blocks until completion. The function does not use the interrupts and
* will use CPU to monitor the FIFO status and move data accordingly. The
* function returns only on completion.
*
* \note  Since this API is blocking, ensure that other transfers finished and it
* will not be called during non-blocking transfer.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param txBuffer
* The pointer to the data to be transferred. If this pointer is a NULL, then the
* function does not fill TX_FIFO. The user would handle the FIFO management in a
* DMA or a polling-based code.
*
* \note If the user provides a NULL pointer in this function and does not handle
* the FIFO transaction, this could either stall or timeout the operation.
* The transfer statuses returned by \ref Cy_SMIF_GetTransferStatus are no longer
* valid.
*
* \param size
* The size of txBuffer. Must be > 0 and not greater than 65536.
*
* \param transferWidth
* The width of transfer \ref cy_en_smif_txfr_width_t.
*
* \param dataDataRate
* dataDataRate
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \return A status of a transmission.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_FIFO_FULL
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_BAD_PARAM
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_TransmitDataBlocking_Ext(SMIF_Type *base,
                            uint8_t const *txBuffer,
                            uint32_t size,
                            cy_en_smif_txfr_width_t transferWidth,
                            cy_en_smif_data_rate_t  dataDataRate,
                            cy_stc_smif_context_t const *context)
{
    /* The return variable */
    cy_en_smif_status_t result = CY_SMIF_BAD_PARAM;
    uint32_t trUnitNum;
#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
    uint32_t temp = 0;
#endif

    /* Check input values */
    CY_ASSERT_L3(CY_SMIF_TXFR_WIDTH_VALID(transferWidth));

    if(size > 0U)
    {
        result = CY_SMIF_CMD_FIFO_FULL;
        /* Check if there are enough free entries in TX_CMD_FIFO */
        if  (Cy_SMIF_GetCmdFifoStatus(base) < CY_SMIF_TX_CMD_FIFO_STATUS_RANGE)
        {
            /* If the mode is octal SPI with DDR or Hyperbus, data unit is a 2-byte */
            if((transferWidth == CY_SMIF_WIDTH_OCTAL) && (dataDataRate == CY_SMIF_DDR))
            {
                if(size % 2U != 0U)
                {
                    return CY_SMIF_BAD_PARAM;
                }
                trUnitNum = size / 2U;
            }
            else
            {
                trUnitNum = size;
            }

#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
            /* Select TX Clock mode SDR/DDR */
            temp = SMIF_CTL(base);
            temp &= ~(SMIF_CTL_CLOCK_IF_TX_SEL_Msk);
            SMIF_CTL(base) =  temp | _VAL2FLD(SMIF_CTL_CLOCK_IF_TX_SEL, dataDataRate);
#endif
            /* Enter the transmitting mode */
            SMIF_TX_CMD_MMIO_FIFO_WR(base) =
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_MODE, CY_SMIF_CMD_FIFO_TX_COUNT_MODE) |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_DATA_RATE, (uint32_t) dataDataRate) |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_WIDTH, (uint32_t)transferWidth)    |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_TX_COUNT, (trUnitNum - 1U)) |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_LAST_BYTE, 1U);

            result = CY_SMIF_SUCCESS;

            if (NULL != txBuffer)
            {
                uint32_t timeoutUnits = context->timeout;
                cy_stc_smif_context_t contextLoc = *context;

                /* initialize parameters for Cy_SMIF_PushTxFifo */
                contextLoc.txBufferAddress = (uint8_t*)txBuffer;
                contextLoc.txBufferCounter = size;
                contextLoc.txCompleteCb = NULL;
                contextLoc.transferStatus = (uint32_t) CY_SMIF_SEND_BUSY;
                contextLoc.preCmdDataRate      = dataDataRate;
                contextLoc.preCmdWidth         = transferWidth;

                while (((uint32_t) CY_SMIF_SEND_BUSY == contextLoc.transferStatus) &&
                        (CY_SMIF_EXCEED_TIMEOUT != result))
                {
                    Cy_SMIF_PushTxFifo(base, &contextLoc);
                    result = Cy_SMIF_TimeoutRun(&timeoutUnits);
                }
            }
        }
    }

#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
    /* Switch back to preferred XIP mode data rate */
    temp = SMIF_CTL(base);
    temp &= ~(SMIF_CTL_CLOCK_IF_TX_SEL_Msk);
    SMIF_CTL(base) =  temp | _VAL2FLD(SMIF_CTL_CLOCK_IF_TX_SEL, context->preXIPDataRate);
#endif

    return (result);
}

/*******************************************************************************
* Function Name: Cy_SMIF_ReceiveData_Ext
****************************************************************************//**
*
* This function implements the receive data phase in the memory command. The
* data is received into the RX Data FIFO using the RX_COUNT command. This
* function sets up the interrupt to trigger on the RX Data FIFO level, and the
* data is fetched from the RX Data FIFO to the rxBuffer as it gets filled. This
* function does not block until completion. The completion will trigger the call
* back function.
*
* \note This function is to be preceded by \ref Cy_SMIF_TransmitCommand. The
* slave select is de-asserted at the end of the receive.
* The function triggers the transfer and the transfer itself utilizes the
* interrupt for FIFO operations in the background. Thus, frequent
* interrupts will be executed after this function is triggered.
* This API is non-blocking and sets up the interrupt to act on the data
* FIFO, ensure there will be no another instance of the function called
* before the current instance has completed execution.
*
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param rxBuffer
* The pointer to the variable where the receive data is stored. If this pointer
* is a NULL, then the function does not enable the interrupt. This use case is
* typically used when the FIFO is handled outside the interrupt and is managed
* in either a polling-based code or a DMA. The user would handle the FIFO
* management in a DMA or a polling-based code.
*
* \note If the user provides a NULL pointer in this function and does not handle
* the FIFO transaction, this could either stall or timeout the operation.
* The transfer statuses returned by \ref Cy_SMIF_GetTransferStatus are no longer
* valid.
*
* \param size
* The size of data to be received. Must be > 0 and not greater than 65536.
*
* \param transferWidth
* The width of transfer \ref cy_en_smif_txfr_width_t.
*
* \param dataRate
* dataRate
*
* \param RxCmpltCb
* The callback executed at the end of a reception. NULL interpreted as no
* callback.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \return A status of a reception.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_FIFO_FULL
*       - \ref CY_SMIF_BAD_PARAM
*
* \note Check \ref group_smif_usage_rules for any usage restriction
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_ReceiveData_Ext(SMIF_Type *base,
                                                uint8_t *rxBuffer,
                                                uint32_t size,
                                                cy_en_smif_txfr_width_t transferWidth,
                                                cy_en_smif_data_rate_t dataRate,
                                                cy_smif_event_cb_t RxCmpltCb,
                                                cy_stc_smif_context_t *context)
{
    /* The return variable */
    cy_en_smif_status_t result = CY_SMIF_BAD_PARAM;
    uint32_t rxUnitNum;
#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
    uint32_t temp = 0;
#endif

    /* Check input values */
    CY_ASSERT_L3(CY_SMIF_TXFR_WIDTH_VALID(transferWidth));

    if(size > 0U)
    {
        result = CY_SMIF_CMD_FIFO_FULL;
        /* Check if there are enough free entries in TX_CMD_FIFO */
        if  (Cy_SMIF_GetCmdFifoStatus(base) < CY_SMIF_TX_CMD_FIFO_STATUS_RANGE)
        {
            /* If the mode is octal SPI with DDR or Hyperbus, data unit is a 2-byte */
            if((transferWidth == CY_SMIF_WIDTH_OCTAL) && (dataRate == CY_SMIF_DDR))
            {
                if(size % 2U != 0U)
                {
                    return CY_SMIF_BAD_PARAM;
                }
                rxUnitNum = size / 2U;
            }
            else
            {
                rxUnitNum = size;
            }

#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
            /* Select TX Clock mode SDR/DDR */
            temp = SMIF_CTL(base);
            temp &= ~(SMIF_CTL_CLOCK_IF_TX_SEL_Msk);
            SMIF_CTL(base) =  temp | _VAL2FLD(SMIF_CTL_CLOCK_IF_TX_SEL, dataRate);
#endif
            /* Enter the receiving mode */
            SMIF_TX_CMD_MMIO_FIFO_WR(base) =
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_MODE, CY_SMIF_CMD_FIFO_RX_COUNT_MODE) |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_WIDTH, (uint32_t)transferWidth)    |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_DATA_RATE, (uint32_t) dataRate) |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_RX_COUNT, (rxUnitNum - 1UL)) |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_LAST_BYTE, 1U);

            if (NULL != rxBuffer)
            {
                /* Move the parameters to the global variables */
                context->rxBufferAddress = (uint8_t*)rxBuffer;
                context->rxBufferSize = size;
                context->rxBufferCounter = size;
                context->rxCompleteCb = RxCmpltCb;
                context->transferStatus =  (uint32_t) CY_SMIF_REC_BUSY;

                /* Enable the TR_RX_REQ interrupt */
                Cy_SMIF_SetInterruptMask(base,
                    Cy_SMIF_GetInterruptMask(base) | SMIF_INTR_TR_RX_REQ_Msk);
            }
            result = CY_SMIF_SUCCESS;
        }
    }

    return (result);
}

/*******************************************************************************
* Function Name: Cy_SMIF_ReceiveDataBlocking_Ext
****************************************************************************//**
*
* This function implements the receive data phase in the memory command. The
* data is received into the RX Data FIFO using the RX_COUNT command. This
* function blocks until completion. The function does not use the interrupts and
* will use CPU to monitor the FIFO status and move data accordingly. The
* function returns only on completion.
*
* \note This function is to be preceded by \ref Cy_SMIF_TransmitCommand. The
* slave select is de-asserted at the end of the receive. Ensure there is
* no another transfers.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param rxBuffer
* The pointer to the variable where the receive data is stored. If this pointer
* is a NULL, then the function does not enable the interrupt. This use case is
* typically used when the FIFO is handled outside the interrupt and is managed
* in either a polling-based code or a DMA. The user would handle the FIFO
* management in a DMA or a polling-based code.
*
* \note If the user provides a NULL pointer in this function and does not handle
* the FIFO transaction, this could either stall or timeout the operation.
* The transfer statuses returned by \ref Cy_SMIF_GetTransferStatus are no longer
* valid.
*
* \param size
* The size of data to be received. Must be > 0 and not greater than 65536.
*
* \param transferWidth
* The width of transfer \ref cy_en_smif_txfr_width_t.
*
* \param dataRate
* dataRate
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \return A status of a reception.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_FIFO_FULL
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_BAD_PARAM
*
* \note Check \ref group_smif_usage_rules for any usage restriction
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_ReceiveDataBlocking_Ext(SMIF_Type *base,
                            uint8_t *rxBuffer,
                            uint32_t size,
                            cy_en_smif_txfr_width_t transferWidth,
                            cy_en_smif_data_rate_t dataRate,
                            cy_stc_smif_context_t const *context)
{
    /* The return variable */
    cy_en_smif_status_t result = CY_SMIF_BAD_PARAM;
    uint32_t rxUnitNum;
#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
    uint32_t temp = 0;
#endif

    /* Check input values */
    CY_ASSERT_L3(CY_SMIF_TXFR_WIDTH_VALID(transferWidth));

    if(size > 0U)
    {
        result = CY_SMIF_CMD_FIFO_FULL;
        /* Check if there are enough free entries in TX_CMD_FIFO */
        if  (Cy_SMIF_GetCmdFifoStatus(base) < CY_SMIF_TX_CMD_FIFO_STATUS_RANGE)
        {
              /* If the mode is octal SPI with DDR or Hyperbus, data unit is a 2-byte */
            if((transferWidth == CY_SMIF_WIDTH_OCTAL) && (dataRate == CY_SMIF_DDR))
            {
                if(size % 2U != 0U)
                {
                    return CY_SMIF_BAD_PARAM;
                }
                rxUnitNum = size / 2U;
            }
            else
            {
                rxUnitNum = size;
            }

#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
            /* Select TX Clock mode SDR/DDR */
            temp = SMIF_CTL(base);
            temp &= ~(SMIF_CTL_CLOCK_IF_TX_SEL_Msk);
            SMIF_CTL(base) =  temp | _VAL2FLD(SMIF_CTL_CLOCK_IF_TX_SEL, dataRate);
#endif
            /* Enter the receiving mode */
            SMIF_TX_CMD_MMIO_FIFO_WR(base) =
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_MODE, CY_SMIF_CMD_FIFO_RX_COUNT_MODE) |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_WIDTH, (uint32_t)transferWidth)    |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_RX_COUNT, (rxUnitNum - 1UL)) |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_DATA_RATE, (uint32_t) dataRate) |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_LAST_BYTE, 1U);

            result = CY_SMIF_SUCCESS;

            if (NULL != rxBuffer)
            {
                uint32_t timeoutUnits = context->timeout;
                cy_stc_smif_context_t contextLoc;

                /* initialize parameters for Cy_SMIF_PushTxFifo */
                contextLoc.rxBufferAddress = (uint8_t*)rxBuffer;
                contextLoc.rxBufferCounter = size;
                contextLoc.rxCompleteCb = NULL;
                contextLoc.transferStatus = (uint32_t) CY_SMIF_REC_BUSY;

                while (((uint32_t) CY_SMIF_REC_BUSY == contextLoc.transferStatus) &&
                        (CY_SMIF_EXCEED_TIMEOUT != result))
                {
                    Cy_SMIF_PopRxFifo(base, &contextLoc);
                    result = Cy_SMIF_TimeoutRun(&timeoutUnits);
                }
            }
        }
    }

#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
    /* Switch back to preferred XIP mode data rate */
    temp = SMIF_CTL(base);
    temp &= ~(SMIF_CTL_CLOCK_IF_TX_SEL_Msk);
    SMIF_CTL(base) =  temp | _VAL2FLD(SMIF_CTL_CLOCK_IF_TX_SEL, context->preXIPDataRate);
#endif

    return (result);
}


/*******************************************************************************
* Function Name: Cy_SMIF_SendDummyCycles_Ext()
****************************************************************************//**
*
* This function sends dummy-clock cycles. The data lines are tri-stated during
* the dummy cycles.
*
* \note This function is to be preceded by \ref Cy_SMIF_TransmitCommand.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param transferWidth
*
* \param dataRate
*
* \param cycles
* The number of dummy cycles. Must be > 0 and not greater than 65536.
*
* \return A status of dummy cycles sending.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_CMD_FIFO_FULL
*       - \ref CY_SMIF_BAD_PARAM
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_SendDummyCycles_Ext(SMIF_Type *base,
                                                cy_en_smif_txfr_width_t transferWidth,
                                                cy_en_smif_data_rate_t dataRate,
                                                uint32_t cycles)
{
    /* The return variable */
    cy_en_smif_status_t result = CY_SMIF_BAD_PARAM;
#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
    uint32_t temp = 0;
#endif
    if (cycles > 0U)
    {
        result = CY_SMIF_CMD_FIFO_FULL;

#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
        /* Select TX Clock mode SDR/DDR */
        temp = SMIF_CTL(base);
        temp &= ~(SMIF_CTL_CLOCK_IF_TX_SEL_Msk);
        SMIF_CTL(base) =  temp | _VAL2FLD(SMIF_CTL_CLOCK_IF_TX_SEL, dataRate);
#endif

        /* Check if there are enough free entries in TX_CMD_FIFO */
        if  (Cy_SMIF_GetCmdFifoStatus(base) < CY_SMIF_TX_CMD_FIFO_STATUS_RANGE)
        {
            /* Send the dummy bytes */
            SMIF_TX_CMD_MMIO_FIFO_WR(base) =
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_MODE, CY_SMIF_CMD_FIFO_DUMMY_COUNT_MODE) |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_DUMMY, (cycles-1UL)) |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_WIDTH, (uint32_t)transferWidth)    |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_DATA_RATE, (uint32_t) dataRate) |
                _VAL2FLD(CY_SMIF_CMD_MMIO_FIFO_WR_LAST_BYTE, 0);

            result = CY_SMIF_SUCCESS;
        }
    }

    return (result);
}
#endif /* CY_IP_MXSMIF_VERSION */


/*******************************************************************************
* Function Name: Cy_SMIF_SetCryptoKey
****************************************************************************//**
*
* Sets the AES-128 encryption key into SMIF crypto registers.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param key
* An array containing 128 bit crypto key: uint32_t key[4].
* The least significant word first.
*
*******************************************************************************/
void Cy_SMIF_SetCryptoKey(SMIF_Type *base, uint32_t *key)
{
    SMIF_CRYPTO_KEY0(base) = key[0U];
    SMIF_CRYPTO_KEY1(base) = key[1U];
    SMIF_CRYPTO_KEY2(base) = key[2U];
    SMIF_CRYPTO_KEY3(base) = key[3U];
}

/*******************************************************************************
* Function Name: Cy_SMIF_SetCryptoIV
****************************************************************************//**
*
* Sets the 96 bit initialization vector (nonce) into SMIF crypto registers.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param nonce
* An array containing 96 bit initialization vector (nonce)
*
*******************************************************************************/
void Cy_SMIF_SetCryptoIV(SMIF_Type *base, uint32_t *nonce)
{
    /* SMIF_CRYPTO_INPUT0 is a counter, the rest 3 registers are nonce */
    SMIF_CRYPTO_INPUT1(base) = nonce[0U];
    SMIF_CRYPTO_INPUT2(base) = nonce[1U];
    SMIF_CRYPTO_INPUT3(base) = nonce[2U];
}

/*******************************************************************************
* Function Name: Cy_SMIF_ConvertSlaveSlotToIndex
****************************************************************************//**
*
* Converts Slave Select enum to the device index.
*
* \param ss
* Slave Select enum.
*
* \param device_idx
* A pointer to device index to be returned.
*
* \return \ref cy_en_smif_status_t.
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_ConvertSlaveSlotToIndex(cy_en_smif_slave_select_t ss, uint32_t *device_idx)
{
    cy_en_smif_status_t ret = CY_SMIF_BAD_PARAM;

    switch (ss)
    {
        case CY_SMIF_SLAVE_SELECT_0:
            *device_idx = 0U;
            ret = CY_SMIF_SUCCESS;
            break;
        case CY_SMIF_SLAVE_SELECT_1:
            *device_idx = 1U;
            ret = CY_SMIF_SUCCESS;
            break;
        case CY_SMIF_SLAVE_SELECT_2:
            *device_idx = 2U;
            ret = CY_SMIF_SUCCESS;
            break;
        case CY_SMIF_SLAVE_SELECT_3:
            *device_idx = 3U;
            ret = CY_SMIF_SUCCESS;
            break;
        default:
            /* The switch statement must have a non-empty default clause. MISRA 16.4 */
            ret = CY_SMIF_BAD_PARAM;
            break;
    }
    return ret;
}

/*******************************************************************************
* Function Name: Cy_SMIF_SetCryptoEnable
****************************************************************************//**
*
* Enables SMIF encryption
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param slaveId
* salve select line to indicate the device on which encryption should be enabled.
*
* \return \ref cy_en_smif_status_t.
*
* \note Please ensure cache is disabled using \ref Cy_SMIF_CacheDisable or
* invalidated using \ref Cy_SMIF_CacheInvalidate or any other system level cache to
* be cleared so that the next read/execute from flash operation results in correct data.
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_SetCryptoEnable(SMIF_Type *base, cy_en_smif_slave_select_t slaveId)
{
    uint32_t device_idx;
    cy_en_smif_status_t ret = CY_SMIF_BAD_PARAM;

    if (CY_SMIF_SUCCESS == Cy_SMIF_ConvertSlaveSlotToIndex(slaveId, &device_idx))
    {
        SMIF_DEVICE_IDX_CTL(base, device_idx) |= SMIF_DEVICE_CTL_CRYPTO_EN_Msk;
        ret = CY_SMIF_SUCCESS;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SMIF_SetCryptoDisable
****************************************************************************//**
*
* Disables SMIF encryption.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param slaveId
* salve select line to indicate the device on which encryption should be disabled.
*
* \return \ref cy_en_smif_status_t.
*
* \note Please ensure cache is disabled using \ref Cy_SMIF_CacheDisable or
* invalidated using \ref Cy_SMIF_CacheInvalidate or any other system level cache to
* be cleared so that the next read/execute from flash operation results in correct data.
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_SetCryptoDisable(SMIF_Type *base, cy_en_smif_slave_select_t slaveId)
{
    cy_en_smif_status_t ret = CY_SMIF_BAD_PARAM;
    uint32_t device_idx;

    if (CY_SMIF_SUCCESS == Cy_SMIF_ConvertSlaveSlotToIndex(slaveId, &device_idx))
    {
        SMIF_DEVICE_IDX_CTL(base, device_idx) &= ~SMIF_DEVICE_CTL_CRYPTO_EN_Msk;
        ret = CY_SMIF_SUCCESS;
    }
    return ret;
}

/*******************************************************************************
* Function Name: Cy_SMIF_Encrypt()
****************************************************************************//**
*
* Uses the Encryption engine to create an encrypted result when the input, key
* and data arrays are provided. The AES-128 encryption of the address with the
* key, fetching the result and XOR with the data array are all done in the
* function. The operational scheme is the following:
*                   data = XOR(AES128(address, key), data)
* Decryption is done using the input data-array identically to the encryption.
* In the XIP mode, encryption and decryption are done without calling this
* function. The operational scheme in the XIP mode is the same. The address
* parameter in the XIP mode equals the actual address in the PSoC memory map.
* The SMIF encryption engine is designed for code storage.
* For data storage, the encryption key can be changed.
* For sensitive data, the Crypto block is used.
*
* \note The API does not have access to the encryption key. The key must be
* placed in the register using \ref Cy_SMIF_SetCryptoKey() before calling this API.
* The crypto routine that can access the key storage area is recommended.
* This crypto routine is typically a protection context 0 function.
*
* \note This is a blocking API. The API waits for encryption completion. Will
* exit if a timeout is set (not equal to 0) and expired.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param address
* The address that gets encrypted is a masked 16-byte block address. The 32-bit
* address with the last 4 bits masked is placed as the last 4 bytes in the
* 128-bit input. The rest of the higher bit for the 128 bits are padded zeros by default.
* PA[127:0]:
* PA[3:0] = 0
* PA[7:4] = ADDR[7:4].
* PA[15:8] = ADDR[15:8].
* PA[23:16] = ADDR[23:16].
* PA[31:24] = ADDR[31:24].
* The other twelve of the sixteen plain text address bytes of PA[127:0] are "0" by default.
* User can initialize PA[127:32] with \ref Cy_SMIF_SetCryptoIV().
*
* \param data
* This is the location where the input data-array is passed while the function
* is called. This array gets populated with the result after encryption is
* completed.
*
* \param size
* Provides a size of the array.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \return A status of the command transmit.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_EXCEED_TIMEOUT
*       - \ref CY_SMIF_BAD_PARAM
*
* \funcusage
* \snippet smif/snippet/main.c snippet_Cy_SMIF_Encrypt
*
*******************************************************************************/
cy_en_smif_status_t  Cy_SMIF_Encrypt(SMIF_Type *base,
                                        uint32_t address,
                                        uint8_t data[],
                                        uint32_t size,
                                        cy_stc_smif_context_t const *context)
{
    uint32_t bufIndex;
    cy_en_smif_status_t status = CY_SMIF_BAD_PARAM;
    uint32_t timeoutUnits = context->timeout;

    CY_ASSERT_L2(size > 0U);

    if((NULL != data) && ((address & (~CY_SMIF_CRYPTO_ADDR_MASK)) == 0UL) )
    {
        status = CY_SMIF_SUCCESS;
        /* Fill the output array */
        for(bufIndex = 0U; bufIndex < (size / CY_SMIF_AES128_BYTES); bufIndex++)
        {
            uint32_t dataIndex = bufIndex * CY_SMIF_AES128_BYTES;
            uint8_t  cryptoOut[CY_SMIF_AES128_BYTES];
            uint32_t  outIndex;

            /* Fill the input field */
            SMIF_CRYPTO_INPUT0(base) = (uint32_t) (address +
                ((bufIndex * CY_SMIF_AES128_BYTES) & CY_SMIF_CRYPTO_ADDR_MASK));

            /* Start the encryption */
            SMIF_CRYPTO_CMD(base) &= ~SMIF_CRYPTO_CMD_START_Msk;
            SMIF_CRYPTO_CMD(base) = (uint32_t)(_VAL2FLD(SMIF_CRYPTO_CMD_START,
                                                    CY_SMIF_CRYPTO_START));

            while((CY_SMIF_CRYPTO_COMPLETED != _FLD2VAL(SMIF_CRYPTO_CMD_START,
                                                    SMIF_CRYPTO_CMD(base))) &&
                                                    (CY_SMIF_EXCEED_TIMEOUT != status))
            {
                /* Wait until the encryption is completed and check the
                * timeout
                */
                status = Cy_SMIF_TimeoutRun(&timeoutUnits);
            }

            if (CY_SMIF_EXCEED_TIMEOUT == status)
            {
                break;
            }

            Cy_SMIF_UnPackByteArray(SMIF_CRYPTO_OUTPUT0(base),
                                &cryptoOut[CY_SMIF_CRYPTO_FIRST_WORD] , true);
            Cy_SMIF_UnPackByteArray(SMIF_CRYPTO_OUTPUT1(base),
                                &cryptoOut[CY_SMIF_CRYPTO_SECOND_WORD], true);
            Cy_SMIF_UnPackByteArray(SMIF_CRYPTO_OUTPUT2(base),
                                &cryptoOut[CY_SMIF_CRYPTO_THIRD_WORD] , true);
            Cy_SMIF_UnPackByteArray(SMIF_CRYPTO_OUTPUT3(base),
                                &cryptoOut[CY_SMIF_CRYPTO_FOURTH_WORD], true);

            for(outIndex = 0U; outIndex < CY_SMIF_AES128_BYTES; outIndex++)
            {
                data[dataIndex + outIndex] ^= cryptoOut[outIndex];
            }
        }
    }
    return (status);
}


/*******************************************************************************
* Function Name: Cy_SMIF_CacheEnable
****************************************************************************//**
*
* This function is used to enable the fast cache, the slow cache or both.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param cacheType
* Holds the type of the cache to be modified. \ref cy_en_smif_cache_t
*
* \return A status of function completion.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_BAD_PARAM
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_CacheEnable(SMIF_Type *base,
                                        cy_en_smif_cache_t cacheType)
{
    cy_en_smif_status_t status = CY_SMIF_SUCCESS;
    switch (cacheType)
    {
        case CY_SMIF_CACHE_SLOW:
            SMIF_SLOW_CA_CTL(base) |= SMIF_SLOW_CA_CTL_ENABLED_Msk;
            break;
        case CY_SMIF_CACHE_FAST:
            SMIF_FAST_CA_CTL(base) |= SMIF_FAST_CA_CTL_ENABLED_Msk;
            break;
        case CY_SMIF_CACHE_BOTH:
            SMIF_SLOW_CA_CTL(base) |= SMIF_SLOW_CA_CTL_ENABLED_Msk;
            SMIF_FAST_CA_CTL(base) |= SMIF_FAST_CA_CTL_ENABLED_Msk;
            break;
        default:
            /* A user error */
            status = CY_SMIF_BAD_PARAM;
            break;
    }
    return (status);
}


/*******************************************************************************
* Function Name: Cy_SMIF_CacheDisable
****************************************************************************//**
*
* This function is used to disable the fast cache, the slow cache or both
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param cacheType
* Holds the type of the cache to be modified. \ref cy_en_smif_cache_t
*
* \return A status of function completion.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_BAD_PARAM
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_CacheDisable(SMIF_Type *base,
                                            cy_en_smif_cache_t cacheType)
{
    cy_en_smif_status_t status = CY_SMIF_SUCCESS;
    switch (cacheType)
    {
        case CY_SMIF_CACHE_SLOW:
            SMIF_SLOW_CA_CTL(base) &= ~SMIF_SLOW_CA_CTL_ENABLED_Msk;
            break;
        case CY_SMIF_CACHE_FAST:
            SMIF_FAST_CA_CTL(base) &= ~SMIF_FAST_CA_CTL_ENABLED_Msk;
            break;
        case CY_SMIF_CACHE_BOTH:
            SMIF_SLOW_CA_CTL(base) &= ~SMIF_SLOW_CA_CTL_ENABLED_Msk;
            SMIF_FAST_CA_CTL(base) &= ~SMIF_FAST_CA_CTL_ENABLED_Msk;
            break;
        default:
            /* User error */
            status = CY_SMIF_BAD_PARAM;
            break;
    }
    return (status);
}


/*******************************************************************************
* Function Name: Cy_SMIF_CachePrefetchingEnable
****************************************************************************//**
*
* This function is used to enable pre-fetching for the fast cache, the slow
* cache or both.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param cacheType
* Holds the type of the cache to be modified. \ref cy_en_smif_cache_t
*
* \return A status of function completion.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_BAD_PARAM
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_CachePrefetchingEnable(SMIF_Type *base,
                                                    cy_en_smif_cache_t cacheType)
{
    cy_en_smif_status_t status = CY_SMIF_SUCCESS;
    switch (cacheType)
    {
        case CY_SMIF_CACHE_SLOW:
            SMIF_SLOW_CA_CTL(base) |= SMIF_SLOW_CA_CTL_PREF_EN_Msk;
            break;
        case CY_SMIF_CACHE_FAST:
            SMIF_FAST_CA_CTL(base) |= SMIF_FAST_CA_CTL_PREF_EN_Msk;
            break;
        case CY_SMIF_CACHE_BOTH:
            SMIF_SLOW_CA_CTL(base) |= SMIF_SLOW_CA_CTL_PREF_EN_Msk;
            SMIF_FAST_CA_CTL(base) |= SMIF_FAST_CA_CTL_PREF_EN_Msk;
            break;
        default:
            /* A user error */
            status = CY_SMIF_BAD_PARAM;
            break;
    }
    return (status);
}


/*******************************************************************************
* Function Name: Cy_SMIF_CachePrefetchingDisable
****************************************************************************//**
*
* This function is used to disable pre-fetching for the fast cache, the slow
* cache or both
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param cacheType
* Holds the type of the cache to be modified. \ref cy_en_smif_cache_t
*
* \return A status of function completion.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_BAD_PARAM
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_CachePrefetchingDisable(SMIF_Type *base,
                                                    cy_en_smif_cache_t cacheType)
{
    cy_en_smif_status_t status = CY_SMIF_SUCCESS;
    switch (cacheType)
    {
        case CY_SMIF_CACHE_SLOW:
            SMIF_SLOW_CA_CTL(base) &= ~SMIF_SLOW_CA_CTL_PREF_EN_Msk;
            break;
        case CY_SMIF_CACHE_FAST:
            SMIF_FAST_CA_CTL(base) &= ~SMIF_FAST_CA_CTL_PREF_EN_Msk;
            break;
        case CY_SMIF_CACHE_BOTH:
            SMIF_SLOW_CA_CTL(base) &= ~SMIF_SLOW_CA_CTL_PREF_EN_Msk;
            SMIF_FAST_CA_CTL(base) &= ~SMIF_FAST_CA_CTL_PREF_EN_Msk;
            break;
        default:
            /* A user error */
            status = CY_SMIF_BAD_PARAM;
            break;
    }
    return (status);
}


/*******************************************************************************
* Function Name: Cy_SMIF_CacheInvalidate
****************************************************************************//**
*
* This function is used to invalidate/clear the fast cache, the slow cache or
* both
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param cacheType
* Holds the type of the cache to be modified. \ref cy_en_smif_cache_t
*
* \return A status of function completion.
*       - \ref CY_SMIF_SUCCESS
*       - \ref CY_SMIF_BAD_PARAM
*
*******************************************************************************/
cy_en_smif_status_t Cy_SMIF_CacheInvalidate(SMIF_Type *base,
                                            cy_en_smif_cache_t cacheType)
{
    cy_en_smif_status_t status = CY_SMIF_SUCCESS;
    switch (cacheType)
    {
        case CY_SMIF_CACHE_SLOW:
            SMIF_SLOW_CA_CMD(base) |= SMIF_SLOW_CA_CMD_INV_Msk;
            break;
        case CY_SMIF_CACHE_FAST:
            SMIF_FAST_CA_CMD(base) |= SMIF_FAST_CA_CMD_INV_Msk;
            break;
        case CY_SMIF_CACHE_BOTH:
            SMIF_SLOW_CA_CMD(base) |= SMIF_SLOW_CA_CMD_INV_Msk;
            SMIF_FAST_CA_CMD(base) |= SMIF_FAST_CA_CMD_INV_Msk;
            break;
        default:
            /* A user error */
            status = CY_SMIF_BAD_PARAM;
            break;
    }
    return (status);
}

#if (CY_IP_MXSMIF_VERSION>=5) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SMIF_SetRxCaptureMode
****************************************************************************//**
* This function sets the Rx Capture mode setting for SMIF IP block instance
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param mode
* Rx Capture mode \ref cy_en_smif_capture_mode_t
*
* \note
* This API is available for CAT1D devices.
*******************************************************************************/
void Cy_SMIF_SetRxCaptureMode(SMIF_Type *base, cy_en_smif_capture_mode_t mode)
{
    CY_ASSERT_L1(NULL != base);

    SMIF_CTL2(base) = _VAL2FLD(SMIF_CORE_CTL2_RX_CAPTURE_MODE, (uint32_t)mode);
}
#endif

#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SMIF_DeviceTransfer_SetMergeTimeout
****************************************************************************//**
*
* This function enables merging continuous transfers over XIP so that the overhead
* of transferring command and address will not be there for reading consecutive addresses.
* User can specify a timeout value to specify how long the device would be selected waiting
* for next incremental address read.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param slave
* Holds the slave select line for which merge should be enabled.
*
* \param timeout (see \ref cy_en_smif_merge_timeout_t)
*
* \note This API is not supported on CAT1A devices.
* \note External memory should also support this mode of transfer.
*
*******************************************************************************/
void Cy_SMIF_DeviceTransfer_SetMergeTimeout(SMIF_Type *base, cy_en_smif_slave_select_t slave, cy_en_smif_merge_timeout_t timeout)
{
    SMIF_DEVICE_Type volatile * device = Cy_SMIF_GetDeviceBySlot(base, slave);
    uint32_t temp;
    temp = SMIF_DEVICE_CTL(device);
    temp &= ~(SMIF_DEVICE_CTL_MERGE_TIMEOUT_Msk);
    SMIF_DEVICE_CTL(device) = temp | _VAL2FLD(SMIF_DEVICE_CTL_MERGE_EN,  1U)  |
                          _VAL2FLD(SMIF_DEVICE_CTL_MERGE_TIMEOUT,  (uint32_t)timeout);
}

/*******************************************************************************
* Function Name: Cy_SMIF_DeviceTransfer_ClearMergeTimeout
****************************************************************************//**
*
* This function disables continuous transfer merging.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param slave
* Holds the slave select line for which merge should be disabled.
*
* \note This API is not supported on CAT1A devices.
* \note External memory should also support this mode of transfer.

*******************************************************************************/
void Cy_SMIF_DeviceTransfer_ClearMergeTimeout(SMIF_Type *base, cy_en_smif_slave_select_t slave)
{
    SMIF_DEVICE_Type volatile * device = Cy_SMIF_GetDeviceBySlot(base, slave);
    uint32_t temp;
    temp = SMIF_DEVICE_CTL(device);
    temp &= ~(SMIF_DEVICE_CTL_MERGE_EN_Msk | SMIF_DEVICE_CTL_MERGE_TIMEOUT_Msk);
    SMIF_DEVICE_CTL(device) = temp;
}
#endif

#if defined (CY_IP_MXS40SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
/*******************************************************************************
* Function Name: Cy_SMIF_DeepSleepCallback
****************************************************************************//**
*
* This function handles the transition of the SMIF into and out of Deep
* Sleep mode. It prevents the device from entering DeepSleep if SMIF is actively
* communicating, or there is any data in the TX or RX FIFOs, or SMIF is in
* memory mode.
*
* This function should be called while execution of \ref Cy_SysPm_CpuEnterDeepSleep
* therefore must be registered as a callback before the call. To register it
* call \ref Cy_SysPm_RegisterCallback and specify \ref CY_SYSPM_DEEPSLEEP
* as the callback type.
*
* \note
* This API is template and user should add code for external memory enter/exit
* low power mode.
*
* \param callbackParams
* The pointer to the structure with SMIF SysPm callback parameters (pointer to
* SMIF registers, context and call mode \ref cy_stc_syspm_callback_params_t).
*
* \param mode
* Callback mode, see \ref cy_en_syspm_callback_mode_t
*
* \return
* \ref cy_en_syspm_status_t
*
* Example setup of SysPM deep sleep and hibernate mode
* \snippet smif/snippet/main.c SMIF SysPM Callback
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SMIF_DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode)
{
    cy_en_syspm_status_t retStatus = CY_SYSPM_SUCCESS;

    CY_ASSERT_L1(NULL != callbackParams);

    SMIF_Type *locBase = (SMIF_Type *) callbackParams->base;
    cy_stc_smif_context_t *locContext = (cy_stc_smif_context_t *) callbackParams->context;

    switch(mode)
    {
        case CY_SYSPM_CHECK_READY:
        {
            /* Check if API is not busy executing transfer operation */
            /* If SPI bus is not busy, all data elements are transferred on
                * the bus from the TX FIFO and shifter and the RX FIFIOs is
                * empty - the SPI is ready enter Deep Sleep.
            */
            bool checkFail = (CY_SMIF_RX_BUSY == (cy_en_smif_txfr_status_t)
                                    Cy_SMIF_GetTransferStatus(locBase, locContext));
            checkFail = (Cy_SMIF_BusyCheck(locBase)) || checkFail;
            checkFail = (Cy_SMIF_GetMode(locBase) == CY_SMIF_MEMORY) || checkFail;

            if (checkFail)
            {
                retStatus = CY_SYSPM_FAIL;
            }
            else
            {
#if (CY_IP_MXSMIF_VERSION == 5u)
                if (locBase == SMIF0_CORE0)
                {
                    Cy_SysClk_ClkHfDisable(CY_SMIF_CORE_0_HF);
                }
                if (locBase == SMIF0_CORE1)
                {
                    Cy_SysClk_ClkHfDisable(CY_SMIF_CORE_1_HF);
                }
#endif
                Cy_SMIF_Disable(locBase);
                retStatus = CY_SYSPM_SUCCESS;
            }
            /* Add check memory that memory not in progress */
        }
        break;

        case CY_SYSPM_CHECK_FAIL:
        {
            /* Other driver is not ready for Deep Sleep. Restore Active mode
            * configuration.
            */
#if (CY_IP_MXSMIF_VERSION == 5u)
            if (locBase == SMIF0_CORE0)
            {
                Cy_SysClk_ClkHfEnable(CY_SMIF_CORE_0_HF);
            }
            if (locBase == SMIF0_CORE1)
            {
                Cy_SysClk_ClkHfEnable(CY_SMIF_CORE_1_HF);
            }
#endif
            Cy_SMIF_Enable(locBase, locContext);

        }
        break;

        case CY_SYSPM_BEFORE_TRANSITION:
        {
            /* This code executes inside critical section and enabling active
            * interrupt source makes interrupt pending in the NVIC. However
            * interrupt processing is delayed until code exists critical
            * section. The pending interrupt force WFI instruction does
            * nothing and device remains in the active mode.
            */

            /* Put external memory in low power mode */
        }
        break;

        case CY_SYSPM_AFTER_TRANSITION:
        {
#if (CY_IP_MXSMIF_VERSION == 5u)
            if (locBase == SMIF0_CORE0)
            {
                Cy_SysClk_ClkHfEnable(CY_SMIF_CORE_0_HF);
            }
            if (locBase == SMIF0_CORE1)
            {
                 Cy_SysClk_ClkHfEnable(CY_SMIF_CORE_1_HF);
            }
#endif
            /* Put external memory in active mode */
            Cy_SMIF_Enable(locBase, locContext);
        }
        break;

        default:
            retStatus = CY_SYSPM_FAIL;
            break;
    }

    return (retStatus);
}


/*******************************************************************************
* Function Name: Cy_SMIF_HibernateCallback
****************************************************************************//**
*
* This function handles the transition of the SMIF into Hibernate mode.
* It prevents the device from entering Hibernate if the SMIF
* is actively communicating, or there is any data in the TX or RX FIFO, or SMIF
* is in memory mode.
*
* This function should be called during execution of \ref Cy_SysPm_SystemEnterHibernate
* therefore it must be registered as a callback before the call. To register it
* call \ref Cy_SysPm_RegisterCallback and specify \ref CY_SYSPM_HIBERNATE
* as the callback type.
*
* \note
* This API is template and user should add code for external memory enter/exit
* low power mode.
*
* \param callbackParams
* The pointer to the structure with SMIF SysPm callback parameters (pointer to
* SMIF registers, context and call mode \ref cy_stc_syspm_callback_params_t).
*
* \param mode
* Callback mode, see \ref cy_en_syspm_callback_mode_t
*
* \return
* \ref cy_en_syspm_status_t
*
* Example setup of SysPM deep sleep and hibernate mode
* \snippet smif/snippet/main.c SMIF SysPM Callback
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SMIF_HibernateCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode)
{
    cy_en_syspm_status_t retStatus = CY_SYSPM_SUCCESS;

    CY_ASSERT_L1(NULL != callbackParams);

    SMIF_Type *locBase = (SMIF_Type *) callbackParams->base;
    cy_stc_smif_context_t *locContext = (cy_stc_smif_context_t *) callbackParams->context;

    switch(mode)
    {
        case CY_SYSPM_CHECK_READY:
        {
            /* Check if API is not busy executing transfer operation
            * If SPI bus is not busy, all data elements are transferred on
            * the bus from the TX FIFO and shifter and the RX FIFIOs is
            * empty - the SPI is ready enter Deep Sleep.
            */
            bool checkFail = (CY_SMIF_RX_BUSY == (cy_en_smif_txfr_status_t)
                                Cy_SMIF_GetTransferStatus(locBase, locContext));
            checkFail = (Cy_SMIF_BusyCheck(locBase)) || checkFail;
            checkFail = (Cy_SMIF_GetMode(locBase) == CY_SMIF_MEMORY) || checkFail;

            if (checkFail)
            {
                retStatus = CY_SYSPM_FAIL;

            }
            else
            {
                retStatus = CY_SYSPM_SUCCESS;
#if (CY_IP_MXSMIF_VERSION == 5u)
                if (locBase == SMIF0_CORE0)
                {
                    Cy_SysClk_ClkHfDisable(CY_SMIF_CORE_0_HF);
                }
                if (locBase == SMIF0_CORE1)
                {
                     Cy_SysClk_ClkHfDisable(CY_SMIF_CORE_1_HF);
                }
#endif
                Cy_SMIF_Disable(locBase);
            }
            /* Add check memory that memory not in progress */
        }
        break;

        case CY_SYSPM_CHECK_FAIL:
        {
            /* Other driver is not ready for Deep Sleep. Restore Active mode
            * configuration.
            */
#if (CY_IP_MXSMIF_VERSION == 5u)
            if (locBase == SMIF0_CORE0)
            {
                Cy_SysClk_ClkHfEnable(CY_SMIF_CORE_0_HF);
            }
            if (locBase == SMIF0_CORE1)
            {
                 Cy_SysClk_ClkHfEnable(CY_SMIF_CORE_1_HF);
            }
#endif
            Cy_SMIF_Enable(locBase, locContext);

        }
        break;

        case CY_SYSPM_BEFORE_TRANSITION:
        {
            /* Put external memory in low power mode */
        }
        break;

        case CY_SYSPM_AFTER_TRANSITION:
        {
#if (CY_IP_MXSMIF_VERSION == 5u)
            if (locBase == SMIF0_CORE0)
            {
                Cy_SysClk_ClkHfEnable(CY_SMIF_CORE_0_HF);
            }
            if (locBase == SMIF0_CORE1)
            {
                 Cy_SysClk_ClkHfEnable(CY_SMIF_CORE_1_HF);
            }
#endif

            Cy_SMIF_Enable(locBase, locContext);
            /* Put external memory in active mode */

        }
        break;

        default:
            retStatus = CY_SYSPM_FAIL;
        break;
    }

    return (retStatus);
}
#endif /* defined (CY_IP_MXS40SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXSMIF */

/* [] END OF FILE */
