/*
 * Copyright 2019-2021,2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexio_mculcd_smartdma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexio_mculcd_smartdma"
#endif

#define FLEXIO_MCULCD_SMARTDMA_TX_START_SHIFTER 0U
#define FLEXIO_MCULCD_SMARTDMA_TX_END_SHIFTER   7U
#define FLEXIO_MCULCD_SMARTDMA_TX_SHIFTER_NUM \
    (FLEXIO_MCULCD_SMARTDMA_TX_END_SHIFTER - FLEXIO_MCULCD_SMARTDMA_TX_START_SHIFTER + 1)

enum _MCULCD_transfer_state
{
    kFLEXIO_MCULCD_StateIdle,           /*!< No transfer in progress. */
    kFLEXIO_MCULCD_StateReadArray,      /*!< Reading array in progress. */
    kFLEXIO_MCULCD_StateWriteArray,     /*!< Writing array in progress. */
    kFLEXIO_MCULCD_StateWriteSameValue, /*!< Writing the same value in progress.
                                         */
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the TX chunk size.
 *
 * The SMARTDMA TX transfer memory must be 4Byte aligned, the transfer size must
 * be multiple of 64Byte. So the transfer data is devided in to three part:
 * part1 + part2 + part3.
 * The part2 is transfered using SMARTDMA, it should be 4Byte aligned, multiple
 * of 64Byte.
 * The part1 and part3 are transfered using blocking method, each of them is
 * less than 64Byte, and total of them is less than (64 + 4) bytes.
 *
 * This function gets the size of each part.
 *
 * @param totalLen The total TX size in byte.
 * @param startAddr The start address of the TX data.
 * @param part1Len Length of the part 1 in byte.
 * @param part2Len Length of the part 2 in byte.
 * @param part3Len Length of the part 3 in byte.
 */
static void FLEXIO_MCULCD_SMARTDMA_GetTxChunkLen(
    uint32_t totalLen, uint32_t startAddr, uint32_t *part1Len, uint32_t *part2Len, uint32_t *part3Len);

/*!
 * @brief Convert RGB565 to RGB888.
 *
 * @param rgb565 Input RGB565.
 * @param pixelCount Pixel count.
 * @param rgb888 Output RGB888.
 */
static void FLEXIO_MCULCD_RGB656ToRGB888(const uint16_t *rgb565, uint32_t pixelCount, uint8_t *rgb888);

/*!
 * @brief Callback function registered to SMARTDMA driver.
 */
static void FLEXIO_MCULCD_SMARTDMA_Callback(void *param);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void FLEXIO_MCULCD_SMARTDMA_GetTxChunkLen(
    uint32_t totalLen, uint32_t startAddr, uint32_t *part1Len, uint32_t *part2Len, uint32_t *part3Len)
{
    if (totalLen < FLEXIO_MCULCD_SMARTDMA_TX_LEN_ALIGN)
    {
        *part1Len = totalLen;
        *part2Len = 0;
        *part3Len = 0;
    }
    else
    {
        *part3Len = (startAddr + totalLen) & (FLEXIO_MCULCD_SMARTDMA_TX_ADDR_ALIGN - 1U);
        *part2Len = ((uint32_t)(totalLen - *part3Len)) & (~(FLEXIO_MCULCD_SMARTDMA_TX_LEN_ALIGN - 1U));

        if (FLEXIO_MCULCD_SMARTDMA_TX_LEN_ALIGN > *part2Len)
        {
            *part1Len = totalLen;
            *part2Len = 0;
            *part3Len = 0;
        }
        else
        {
            *part1Len = totalLen - *part2Len - *part3Len;
        }
    }
}

static void FLEXIO_MCULCD_RGB656ToRGB888(const uint16_t *rgb565, uint32_t pixelCount, uint8_t *rgb888)
{
    while ((pixelCount--) != 0U)
    {
        *rgb888 = (uint8_t)(((*rgb565) & 0x001FU) << 3U);
        rgb888++;
        *rgb888 = (uint8_t)(((*rgb565) & 0x07E0U) >> 3U);
        rgb888++;
        *rgb888 = (uint8_t)(((*rgb565) & 0xF800U) >> 8U);
        rgb888++;

        rgb565++;
    }
}

/*!
 * brief Initializes the FLEXO MCULCD master SMARTDMA handle.
 *
 * This function initializes the FLEXO MCULCD master SMARTDMA handle which can be
 * used for other FLEXO MCULCD transactional APIs. For a specified FLEXO MCULCD
 * instance, call this API once to get the initialized handle.
 *
 * param base Pointer to FLEXIO_MCULCD_Type structure.
 * param handle Pointer to flexio_mculcd_smartdma_handle_t structure to store the
 * transfer state.
 * param config Pointer to the configuration.
 * param callback MCULCD transfer complete callback, NULL means no callback.
 * param userData callback function parameter.
 * retval kStatus_Success Successfully create the handle.
 */
status_t FLEXIO_MCULCD_TransferCreateHandleSMARTDMA(FLEXIO_MCULCD_Type *base,
                                                    flexio_mculcd_smartdma_handle_t *handle,
                                                    const flexio_mculcd_smartdma_config_t *config,
                                                    flexio_mculcd_smartdma_transfer_callback_t callback,
                                                    void *userData)
{
    assert(handle != NULL);

    /* The SMARTDMA firmware only support TX using shifter 0 to shifter 7 */
    if (base->txShifterStartIndex != FLEXIO_MCULCD_SMARTDMA_TX_START_SHIFTER)
    {
        return kStatus_InvalidArgument;
    }

    if (base->txShifterEndIndex != FLEXIO_MCULCD_SMARTDMA_TX_END_SHIFTER)
    {
        return kStatus_InvalidArgument;
    }

    /* Zero the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    if (NULL == config)
    {
        handle->smartdmaApi = (uint8_t)kSMARTDMA_FlexIO_DMA;
    }
    else
    {
        if (config->inputPixelFormat == config->outputPixelFormat)
        {
            handle->smartdmaApi = (uint8_t)kSMARTDMA_FlexIO_DMA;
        }
        else if (((config->inputPixelFormat == kFLEXIO_MCULCD_RGB565) &&
                  (config->outputPixelFormat == kFLEXIO_MCULCD_RGB888)) ||
                 ((config->inputPixelFormat == kFLEXIO_MCULCD_BGR565) &&
                  (config->outputPixelFormat == kFLEXIO_MCULCD_BGR888)))
        {
            handle->smartdmaApi      = (uint8_t)kSMARTDMA_FlexIO_DMA_RGB565To888;
            handle->needColorConvert = true;
        }
        else
        {
            return kStatus_InvalidArgument;
        }
    }

    /* Initialize the state. */
    handle->state = (uint32_t)kFLEXIO_MCULCD_StateIdle;

    /* Register callback and userData. */
    handle->completionCallback = callback;
    handle->userData           = userData;
    handle->base               = base;

    SMARTDMA_InstallFirmware(SMARTDMA_DISPLAY_MEM_ADDR, s_smartdmaDisplayFirmware, SMARTDMA_DISPLAY_FIRMWARE_SIZE);

    SMARTDMA_InstallCallback(FLEXIO_MCULCD_SMARTDMA_Callback, handle);

    /* The shifter interrupt is used by the SMARTDMA. */
    FLEXIO_EnableShifterStatusInterrupts(base->flexioBase, (1UL << FLEXIO_MCULCD_SMARTDMA_TX_END_SHIFTER));

#if (defined(SMARTDMA_USE_FLEXIO_SHIFTER_DMA) && SMARTDMA_USE_FLEXIO_SHIFTER_DMA)
    FLEXIO_EnableShifterStatusDMA(base->flexioBase, 1UL, true);
#endif

    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking FlexIO MCULCD transfer using SMARTDMA.
 *
 * This function returns immediately after transfer initiates. Use the callback
 * function to check whether the transfer is completed.
 *
 * param base pointer to FLEXIO_MCULCD_Type structure.
 * param handle pointer to flexio_mculcd_smartdma_handle_t structure to store the
 * transfer state.
 * param xfer Pointer to FlexIO MCULCD transfer structure.
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_FLEXIO_MCULCD_Busy FlexIO MCULCD is not idle, it is running another
 * transfer.
 */
status_t FLEXIO_MCULCD_TransferSMARTDMA(FLEXIO_MCULCD_Type *base,
                                        flexio_mculcd_smartdma_handle_t *handle,
                                        flexio_mculcd_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(xfer != NULL);

    uint32_t part1Len, part2Len, part3Len;

    /* Check if the device is busy. */
    if ((uint32_t)kFLEXIO_MCULCD_StateIdle != handle->state)
    {
        return kStatus_FLEXIO_MCULCD_Busy;
    }

    /* Only support write array. */
    if (kFLEXIO_MCULCD_WriteArray != xfer->mode)
    {
        return kStatus_InvalidArgument;
    }

    FLEXIO_MCULCD_SMARTDMA_GetTxChunkLen(xfer->dataSize, xfer->dataAddrOrSameValue, &part1Len, &part2Len, &part3Len);

    handle->state = (uint32_t)kFLEXIO_MCULCD_StateWriteArray;

    /* Start transfer. */
    handle->remainingCount      = xfer->dataSize;
    handle->dataCount           = xfer->dataSize;
    handle->dataAddrOrSameValue = xfer->dataAddrOrSameValue;

    /* Assert the nCS. */
    FLEXIO_MCULCD_StartTransfer(base);

    if (!xfer->dataOnly)
    {
        /* Send the command. */
        FLEXIO_MCULCD_WriteCommandBlocking(base, xfer->command);
    }

    if (part1Len > 0U)
    {
        if (handle->needColorConvert)
        {
            FLEXIO_MCULCD_RGB656ToRGB888((uint16_t *)xfer->dataAddrOrSameValue, part1Len >> 1U,
                                         handle->blockingXferBuffer);
            FLEXIO_MCULCD_WriteDataArrayBlocking(base, handle->blockingXferBuffer, (part1Len >> 1U) * 3U);
        }
        else
        {
            FLEXIO_MCULCD_WriteDataArrayBlocking(base, (void *)(uint8_t *)xfer->dataAddrOrSameValue, (size_t)part1Len);
        }
        handle->remainingCount -= part1Len;
        handle->dataAddrOrSameValue += part1Len;
    }

    if (0U == part2Len)
    {
        /* In this case, all data are sent out as part 1. Only notify upper layer here. */
        FLEXIO_MCULCD_StopTransfer(base);
        handle->state = (uint32_t)kFLEXIO_MCULCD_StateIdle;

        /* Callback to inform upper layer. */
        if (NULL != handle->completionCallback)
        {
            handle->completionCallback(base, handle, kStatus_FLEXIO_MCULCD_Idle, handle->userData);
        }
    }
    else
    {
        /* For 6800, de-assert the RDWR pin. */
        if (kFLEXIO_MCULCD_6800 == base->busType)
        {
            base->setRDWRPin(false);
        }

        FLEXIO_MCULCD_SetMultiBeatsWriteConfig(base);

        /* Save the part 3 information. */
        handle->dataCountUsingEzh = part2Len;
        handle->dataAddrOrSameValue += part2Len;

        /* The part 3 is transfered using blocking method in ISR, convert the color
           to save time in ISR. */
        if ((0U != part3Len) && (handle->needColorConvert))
        {
            FLEXIO_MCULCD_RGB656ToRGB888((uint16_t *)xfer->dataAddrOrSameValue, part3Len >> 1U,
                                         handle->blockingXferBuffer);
        }

        handle->smartdmaParam.p_buffer       = (uint32_t *)(xfer->dataAddrOrSameValue + part1Len);
        handle->smartdmaParam.buffersize     = part2Len;
        handle->smartdmaParam.smartdma_stack = handle->smartdmaStack;

        SMARTDMA_Reset();
        SMARTDMA_Boot(handle->smartdmaApi, &(handle->smartdmaParam), 0);
    }

    return kStatus_Success;
}

/*!
 * brief Aborts a FlexIO MCULCD transfer using SMARTDMA.
 *
 * param base pointer to FLEXIO_MCULCD_Type structure.
 * param handle FlexIO MCULCD SMARTDMA handle pointer.
 */
void FLEXIO_MCULCD_TransferAbortSMARTDMA(FLEXIO_MCULCD_Type *base, flexio_mculcd_smartdma_handle_t *handle)
{
    assert(handle != NULL);

    SMARTDMA_Reset();

    /* Set the handle state. */
    handle->state     = (uint32_t)kFLEXIO_MCULCD_StateIdle;
    handle->dataCount = 0;
}

/*!
 * brief Gets the remaining bytes for FlexIO MCULCD SMARTDMA transfer.
 *
 * param base pointer to FLEXIO_MCULCD_Type structure.
 * param handle FlexIO MCULCD SMARTDMA handle pointer.
 * param count Number of count transferred so far by the SMARTDMA transaction.
 * retval kStatus_Success Get the transferred count Successfully.
 * retval kStatus_NoTransferInProgress No transfer in process.
 */
status_t FLEXIO_MCULCD_TransferGetCountSMARTDMA(FLEXIO_MCULCD_Type *base,
                                                flexio_mculcd_smartdma_handle_t *handle,
                                                size_t *count)
{
    assert(handle != NULL);
    assert(count != NULL);

    uint32_t state = handle->state;

    if ((uint32_t)kFLEXIO_MCULCD_StateIdle == state)
    {
        return kStatus_NoTransferInProgress;
    }
    else
    {
        *count = handle->dataCount - handle->remainingCount;
    }

    return kStatus_Success;
}

static void FLEXIO_MCULCD_SMARTDMA_Callback(void *param)
{
    flexio_mculcd_smartdma_handle_t *flexioMculcdSmartDmaHandle = (flexio_mculcd_smartdma_handle_t *)param;

    FLEXIO_MCULCD_Type *flexioLcdMcuBase = flexioMculcdSmartDmaHandle->base;

    FLEXIO_MCULCD_WaitTransmitComplete();

    /* Disable the TX shifter and the timer. */
    FLEXIO_MCULCD_ClearMultiBeatsWriteConfig(flexioLcdMcuBase);

    flexioMculcdSmartDmaHandle->remainingCount -= flexioMculcdSmartDmaHandle->dataCountUsingEzh;

    /* Send the part 3 */
    if (0U != flexioMculcdSmartDmaHandle->remainingCount)
    {
        if (flexioMculcdSmartDmaHandle->needColorConvert)
        {
            FLEXIO_MCULCD_WriteDataArrayBlocking(flexioLcdMcuBase, flexioMculcdSmartDmaHandle->blockingXferBuffer,
                                                 (flexioMculcdSmartDmaHandle->remainingCount >> 1U) * 3U);
        }
        else
        {
            FLEXIO_MCULCD_WriteDataArrayBlocking(flexioLcdMcuBase,
                                                 (void *)(uint8_t *)flexioMculcdSmartDmaHandle->dataAddrOrSameValue,
                                                 flexioMculcdSmartDmaHandle->remainingCount);
        }
    }

    flexioMculcdSmartDmaHandle->remainingCount = 0;
    FLEXIO_MCULCD_StopTransfer(flexioLcdMcuBase);
    flexioMculcdSmartDmaHandle->state = (uint32_t)kFLEXIO_MCULCD_StateIdle;

    /* Callback to inform upper layer. */
    if (NULL != flexioMculcdSmartDmaHandle->completionCallback)
    {
        flexioMculcdSmartDmaHandle->completionCallback(flexioLcdMcuBase, flexioMculcdSmartDmaHandle,
                                                       kStatus_FLEXIO_MCULCD_Idle,
                                                       flexioMculcdSmartDmaHandle->userData);
    }
}
