/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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


#include <string.h>
#include "fsl_flexio_camera_edma_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_edma_request.h"

#if FSL_FEATURE_SOC_FLEXIO_COUNT &&  FSL_FEATURE_SOC_EDMA_COUNT

/*FUNCTION*********************************************************************
 *
 * Function Name : FLEXIO_Camera_DRV_InitEdmaRx
 * Description   : Configures the FLEXIO working as a CPI interface, the indicated
 * EDMA channel moving data from flexio interface to user defined memory.
 * With this function, a image of camera sensor can be mapped into user defined
 * memory, then user can read the mapped memory anytime in application.
 *
 *END*************************************************************************/
flexio_camera_status_t FLEXIO_Camera_DRV_InitEdmaRx(
                flexio_camera_edma_handler_t *handler,                   /* Output. */
                flexio_camera_user_config_t  *userFlexioCameraConfigPtr, /* Input. */
                camera_edma_user_config_t    *userEdmaConfigPtr )        /* Input. */
                
{
    flexio_camera_dev_t *flexioCameraHwConfigPtr;
    edma_transfer_config_t rxEdmeConfigStruct;
    edma_software_tcd_t rxEdmaChnStcd[2];
    uint32_t ret;
    
    if ( (!handler) || (!userFlexioCameraConfigPtr) || (!userEdmaConfigPtr) )
    {
        return kStatus_FlexIO_Camera_InvalidArgument;
    }

    memset(handler, 0, sizeof(flexio_camera_edma_handler_t)); /* Reset the handler's memory. */

    flexioCameraHwConfigPtr = &(handler->flexioCameraHwConfig);
    flexioCameraHwConfigPtr->flexioBase     = g_flexioBase[userFlexioCameraConfigPtr->flexioInstance];
    flexioCameraHwConfigPtr->datPinStartIdx = userFlexioCameraConfigPtr->datPinStartIdx;
    flexioCameraHwConfigPtr->pclkPinIdx     = userFlexioCameraConfigPtr->pclkPinIdx;
    flexioCameraHwConfigPtr->hrefPinIdx     = userFlexioCameraConfigPtr->hrefPinIdx;
    flexioCameraHwConfigPtr->shifterStartIdx= userFlexioCameraConfigPtr->shifterStartIdx;
    flexioCameraHwConfigPtr->shifterCount   = FSL_FLEXIO_CAMERA_USING_SHIFTER_COUNT;
    flexioCameraHwConfigPtr->timerIdx       = userFlexioCameraConfigPtr->timerIdx;
    
    handler->userEdmaChn    = userEdmaConfigPtr->userEdmaChn;
    handler->userBufAddr    = userEdmaConfigPtr->userBufAddr;
    handler->userBufLenByte = userEdmaConfigPtr->userBufLenByte;
    
    /* Fill the edma channel configuration. */
    rxEdmeConfigStruct.srcAddr            = FLEXIO_Camera_HAL_GetRxBufferAddr(flexioCameraHwConfigPtr);
    rxEdmeConfigStruct.destAddr           = handler->userBufAddr;
    rxEdmeConfigStruct.srcTransferSize    = kEDMATransferSize_32Bytes;/* Using FSL_FLEXIO_CAMERA_USING_SHIFTER_COUNT = 8U. */
    rxEdmeConfigStruct.destTransferSize   = kEDMATransferSize_32Bytes; 
    rxEdmeConfigStruct.srcOffset          = 0;
    rxEdmeConfigStruct.destOffset         = 4U * flexioCameraHwConfigPtr->shifterCount; /* 4 byte per shifter, typically 32 byte for 8 shifters. */
    rxEdmeConfigStruct.srcLastAddrAdjust  = 0;
    rxEdmeConfigStruct.destLastAddrAdjust = -(int32_t)(handler->userBufLenByte);
    rxEdmeConfigStruct.srcModulo          = kEDMAModuloDisable;
    rxEdmeConfigStruct.destModulo         = kEDMAModuloDisable;
    rxEdmeConfigStruct.minorLoopCount     = rxEdmeConfigStruct.destOffset; /* the minor loop would read all the data in shifters one time per trigger. */
    rxEdmeConfigStruct.majorLoopCount     = handler->userBufLenByte/rxEdmeConfigStruct.minorLoopCount;    

    /* Pre-configure the edma. */
    /* 1. Request channel. */
    ret = EDMA_DRV_RequestChannel(  handler->userEdmaChn, 
                                    (dma_request_source_t)(kDmaRequestMux0Group1FlexIO0Channel0 + flexioCameraHwConfigPtr->shifterStartIdx),
                                   &(handler->rxEdmaChnState)     );
    
    if (ret == kEDMAInvalidChannel)
    {
        return kStatus_FlexIO_Camera_Failed;
    }
    /* 2. Install callback. */
    ret = EDMA_DRV_PrepareDescriptorTransfer( 
                                &handler->rxEdmaChnState,
                                rxEdmaChnStcd,
                                &rxEdmeConfigStruct,
                                false, /* always disable EDMA transfer done interrupt. */ //enIntOnEdmaTransferLoop,
                                false  /* always disable auto shutdown Req when transfer done. *///enDisableReqAfterTransferLoop
                                );
    if (ret == kEDMAInvalidChannel)
    {
        return kStatus_FlexIO_Camera_Failed;
    }

    ret = EDMA_DRV_PushDescriptorToReg( &handler->rxEdmaChnState, rxEdmaChnStcd);
    if (ret == kEDMAInvalidChannel)
    {
        return kStatus_FlexIO_Camera_Failed;
    }

    /* Configure the flexio_camera. */
    if (kStatus_FLEXIO_Success != FLEXIO_Camera_HAL_Configure(flexioCameraHwConfigPtr) )
    {
        return kStatus_FlexIO_Camera_Failed;
    }
    
    return kStatus_FlexIO_Camera_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : FLEXIO_Camera_DRV_DeinitEdmaRx
 * Description   : Shotdowns the flexio_camera_edma device. It would release
 * the EDMA channel used in flexio_camera_edma device and stop to generate
 * DMA trigger from flexio_camera interface.
 *
 *END*************************************************************************/
flexio_camera_status_t FLEXIO_Camera_DRV_DeinitEdmaRx(
        flexio_camera_edma_handler_t *handler)
{
    uint32_t ret;

    ret = EDMA_DRV_ReleaseChannel(&handler->rxEdmaChnState);
    if (ret == kEDMAInvalidChannel)
    {
        return kStatus_FlexIO_Camera_Failed;
    }
    memset(&handler, 0, sizeof(flexio_camera_edma_handler_t)); /* Reset the handler. */

    return kStatus_FlexIO_Camera_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : FLEXIO_Camera_DRV_ResetEdmaRx
 * Description   : Reset the EDMA transfer loop's destination address and loop
 * counter, which means the EDMA transfer would be reset to the initialized state.
 * This API would be called when VSYNC event happenned to make sure the data
 * from camera would not be misplaced. However, if there is other application
 * configuration can do the same thing, this API would not be necessary.
 *
 *END*************************************************************************/
flexio_camera_status_t FLEXIO_Camera_DRV_ResetEdmaRx(
        flexio_camera_edma_handler_t *handler)
{

    uint32_t ret;
    edma_transfer_config_t rxEdmeConfigStruct;
    edma_software_tcd_t rxEdmaChnStcd[2];
    flexio_camera_dev_t *flexioCameraHwConfigPtr = &(handler->flexioCameraHwConfig);

    EDMA_DRV_StopChannel(&handler->rxEdmaChnState);
    
    /* 3. Configure the channel. */
    rxEdmeConfigStruct.srcAddr            = FLEXIO_Camera_HAL_GetRxBufferAddr(flexioCameraHwConfigPtr);
    rxEdmeConfigStruct.destAddr           = handler->userBufAddr;
    rxEdmeConfigStruct.srcTransferSize    = kEDMATransferSize_32Bytes;
    rxEdmeConfigStruct.destTransferSize   = kEDMATransferSize_32Bytes; 
    rxEdmeConfigStruct.srcOffset          = 0;
    rxEdmeConfigStruct.destOffset         = 4U * (flexioCameraHwConfigPtr->shifterCount); /* 4 byte per shifter, typically 32 byte for 8 shifters. */
    rxEdmeConfigStruct.srcLastAddrAdjust  = 0;
    rxEdmeConfigStruct.destLastAddrAdjust = -(int32_t)(handler->userBufLenByte);
    rxEdmeConfigStruct.srcModulo          = kEDMAModuloDisable;
    rxEdmeConfigStruct.destModulo         = kEDMAModuloDisable;
    rxEdmeConfigStruct.minorLoopCount     = rxEdmeConfigStruct.destOffset; /* the minor loop would read all the data in shifters one time per trigger. */
    rxEdmeConfigStruct.majorLoopCount     = (handler->userBufLenByte)/(rxEdmeConfigStruct.minorLoopCount);

    ret = EDMA_DRV_PrepareDescriptorTransfer( 
                                &handler->rxEdmaChnState,
                                rxEdmaChnStcd,
                                &rxEdmeConfigStruct,
                                false, /* Always disable transfer done interrupt. */
                                false  /* Always disable auto shutdown req. */ 
                                  );
    if (ret == kEDMAInvalidChannel)
    {
        return kStatus_FlexIO_Camera_Failed;
    }

    ret = EDMA_DRV_PushDescriptorToReg( &handler->rxEdmaChnState, rxEdmaChnStcd);
    if (ret == kEDMAInvalidChannel)
    {
        return kStatus_FlexIO_Camera_Failed;
    }
    EDMA_DRV_StartChannel(&handler->rxEdmaChnState);

    return kStatus_FlexIO_Camera_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : FLEXIO_Camera_DRV_StartEdmaRx
 * Description   : Start the flexio_camera_edma device. After the initializatioin,
 * the EDMA would be triggered and start the tranfer by calling this API. Then
 * the memory mapping can be executed.
 *
 *END*************************************************************************/
flexio_camera_status_t FLEXIO_Camera_DRV_StartEdmaRx(
        flexio_camera_edma_handler_t *handler)
{
    uint32_t ret;
    flexio_camera_dev_t *flexioCameraHwConfigPtr = &(handler->flexioCameraHwConfig);
    
    /* Clear the flexio flags. */
    FLEXIO_Camera_HAL_ClearRxBufferFullFlag(flexioCameraHwConfigPtr);
    /* Enable the DMA trigger of the first shifter. */
    FLEXIO_Camera_HAL_SetRxBufferDmaCmd(flexioCameraHwConfigPtr, 0x01, true);

    ret = EDMA_DRV_StartChannel(&handler->rxEdmaChnState);
    if (ret == kEDMAInvalidChannel)
    {
        return kStatus_FlexIO_Camera_Failed;
    }

    return kStatus_FlexIO_Camera_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : FLEXIO_Camera_DRV_SetBufferTriggerForExtEdma
 * Description   : Set the flexio_camera's DMA trigger if need to trigger
 * more DMA in application. For some case, another DMA channel need to be
 * triggered to do things like moving data from user-defined memory to other
 * device, like LCD screen. This function would provide to generate a synchronous
 * trigger from flexio_camera interface's buffer.
 *
 *END*************************************************************************/
void FLEXIO_Camera_DRV_SetBufferTriggerForExtEdma(
                flexio_camera_edma_handler_t *handler, uint32_t syncMsk, bool enable)
{
    flexio_camera_dev_t *flexioCameraHwConfigPtr = &(handler->flexioCameraHwConfig);
    FLEXIO_Camera_HAL_SetRxBufferDmaCmd(
            flexioCameraHwConfigPtr, syncMsk, enable);
}

#endif /* FSL_FEATURE_SOC_FLEXIO_COUNT && FSL_FEATURE_SOC_DMA_COUNT */

/* EOF. */

