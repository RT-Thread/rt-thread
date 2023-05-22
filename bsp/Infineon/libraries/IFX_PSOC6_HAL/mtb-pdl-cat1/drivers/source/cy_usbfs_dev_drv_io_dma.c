/***************************************************************************//**
* \file cy_usbfs_dev_drv_io_dma.c
* \version 2.20.3
*
* Provides data transfer API implementation of the USBFS driver.
*
********************************************************************************
* \copyright
* Copyright 2018-2020 Cypress Semiconductor Corporation
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

#if defined (CY_IP_MXUSBFS) && defined (CY_IP_MXPERI)

#include <string.h>
#include "cy_usbfs_dev_drv_pvt.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
*                        Internal Constants
*******************************************************************************/

/* Invalid channel */
#define DMA_INVALID_CHANNEL     ((uint32_t) (-1))

/* Arbiter interrupt sources for OUT and IN endpoints when mode is
* CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO.
*/
#define IN_ENDPOINT_ARB_INTR_SOURCES    (USBFS_USBDEV_ARB_EP_IN_BUF_FULL_Msk | \
                                         USBFS_USBDEV_ARB_EP_BUF_OVER_Msk    | \
                                         USBFS_USBDEV_ARB_EP_BUF_UNDER_Msk   | \
                                         USBFS_USBDEV_ARB_EP_ERR_Msk)

#define OUT_ENDPOINT_ARB_INTR_SOURCES   (USBFS_USBDEV_ARB_EP_DMA_TERMIN_Msk | \
                                         USBFS_USBDEV_ARB_EP_BUF_OVER_Msk   | \
                                         USBFS_USBDEV_ARB_EP_BUF_UNDER_Msk  | \
                                         USBFS_USBDEV_ARB_EP_ERR_Msk)

/* DMA configuration defines */
#define DMA_XLOOP_INCREMENT    (1)
#define DMA_YLOOP_INCREMENT    (32)
#define DMA_NO_INCREMENT       (0)

/* Timeout for dynamic reconfiguration */
#define DYN_RECONFIG_ONE_TICK   (1U)        /* 1 tick = 1 us */
#define DYN_RECONFIG_TIMEOUT    (25000UL)   /* (25000 * tick)us = 25 ms ( TDRQCMPLTND / 2 ) */

/* Timeout for DMA read operation */
#define DMA_READ_REQUEST_ONE_TICK   (1U)      /* 1 tick = 1 us */
#define DMA_READ_REQUEST_TIMEOUT    (25000UL) /* (25000 * tick)us = 25 ms ( TDRQCMPLTND / 2 ) */

#define DMA_WRITE_REQUEST_ONE_TICK   (1U)      /* 1 tick = 1 us */
#define DMA_WRITE_REQUEST_TIMEOUT    (25000UL) /* (25000 * tick)us = 25 ms ( TDRQCMPLTND / 2 ) */


/*******************************************************************************
*                        Internal Functions Prototypes
*******************************************************************************/

static void DmaEndpointInit1D(cy_stc_dma_descriptor_t *descr,
                              bool inDirection,
                              cy_en_dma_data_size_t dataSize,
                              volatile uint32_t const *dataReg);

static void DmaEndpointInit2D(cy_stc_dma_descriptor_t *descr,
                              bool inDirection,
                              int32_t numElements);

static void DmaEndpointSetLength(bool inDirection,
                                 uint32_t size,
                                 cy_stc_usbfs_dev_drv_endpoint_data_t *endpoint);


/*******************************************************************************
*                            Internal Constants
*******************************************************************************/

/* Used for getting data in X loops */
#define DMA_DESCR_1D_CFG \
{                        \
    /* .retrigger      = */ CY_DMA_RETRIG_IM,        \
    /* .interruptType  = */ CY_DMA_DESCR,            \
    /* .triggerOutType = */ CY_DMA_DESCR,            \
    /* .channelState   = */ CY_DMA_CHANNEL_DISABLED, \
    /* .triggerInType  = */ CY_DMA_DESCR,            \
    /* .dataSize        = */ CY_DMA_BYTE,               \
    /* .srcTransferSize = */ CY_DMA_TRANSFER_SIZE_WORD, \
    /* .dstTransferSize = */ CY_DMA_TRANSFER_SIZE_WORD, \
    /* .descriptorType  = */ CY_DMA_1D_TRANSFER,        \
    /* .srcAddress     = */ NULL, \
    /* .dstAddress     = */ NULL, \
    /* .srcXincrement  = */ 0,    \
    /* .dstXincrement  = */ 0,    \
    /* .xCount         = */ 1UL,  \
    /* .srcYincrement  = */ 0,    \
    /* .dstYincrement  = */ 0,    \
    /* .yCount         = */ 1UL,  \
    /* .nextDescriptor = */ NULL, \
}

/* Used for getting data in Y loops */
#define DMA_DESCR_2D_CFG \
{                        \
    /* .retrigger      = */ CY_DMA_RETRIG_IM,       \
    /* .interruptType  = */ CY_DMA_X_LOOP,          \
    /* .triggerOutType = */ CY_DMA_X_LOOP,          \
    /* .channelState   = */ CY_DMA_CHANNEL_ENABLED, \
    /* .triggerInType  = */ CY_DMA_X_LOOP,          \
    /* .dataSize        = */ CY_DMA_BYTE,               \
    /* .srcTransferSize = */ CY_DMA_TRANSFER_SIZE_WORD, \
    /* .dstTransferSize = */ CY_DMA_TRANSFER_SIZE_WORD, \
    /* .descriptorType  = */ CY_DMA_2D_TRANSFER,        \
    /* .srcAddress     = */ NULL, \
    /* .dstAddress     = */ NULL, \
    /* .srcXincrement  = */ 0,    \
    /* .dstXincrement  = */ 0,    \
    /* .xCount         = */ 1UL,  \
    /* .srcYincrement  = */ 0,    \
    /* .dstYincrement  = */ 0,    \
    /* .yCount         = */ 1UL,  \
    /* .nextDescriptor = */ NULL, \
}


/*******************************************************************************
* Function Name: DmaInit
****************************************************************************//**
*
* Initializes all DMA channels used by the USBFS Device.
*
* \param config
* The pointer to the driver configuration structure \ref cy_stc_usbfs_dev_drv_config_t.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return
* Status code of the function execution \ref cy_en_usbfs_dev_drv_status_t.
*
*******************************************************************************/
cy_en_usbfs_dev_drv_status_t DmaInit(cy_stc_usbfs_dev_drv_config_t const *config, cy_stc_usbfs_dev_drv_context_t *context)
{
    cy_en_usbfs_dev_drv_status_t retStatus = CY_USBFS_DEV_DRV_DMA_CFG_FAILED;

    uint32_t endpoint;

    /* Configure DMA descriptors and channels for data endpoints */
    for (endpoint = 0UL; endpoint < CY_USBFS_DEV_DRV_NUM_EPS_MAX; ++endpoint)
    {
        /* DMA configuration status for endpoint */
        retStatus = CY_USBFS_DEV_DRV_DMA_CFG_FAILED;

        /* Get pointer to endpoint data */
        cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData = &context->epPool[endpoint];

        if (config->dmaConfig[endpoint] != NULL)
        {
            cy_en_usbfs_dev_drv_status_t locStatus = CY_USBFS_DEV_DRV_DMA_CFG_FAILED;

            cy_stc_dma_channel_config_t chConfig;

            /* Descriptors configurations */
            const cy_stc_dma_descriptor_config_t DmaDescr1DCfg = DMA_DESCR_1D_CFG;
            const cy_stc_dma_descriptor_config_t DmaDescr2DCfg = DMA_DESCR_2D_CFG;

            /* Store DMA configuration required for operation */
            endpointData->base   = config->dmaConfig[endpoint]->base;
            endpointData->chNum  = config->dmaConfig[endpoint]->chNum;
            endpointData->descr0 = config->dmaConfig[endpoint]->descr0;
            endpointData->descr1 = config->dmaConfig[endpoint]->descr1;
            endpointData->outTrigMux = config->dmaConfig[endpoint]->outTrigMux;
            endpointData->copyData   = NULL;

            if (CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA == context->mode)
            {
                if (NULL != endpointData->descr0)
                {
                    /* Initialize DMA descriptor 0 for 1D operation.
                    * Discard return because descriptor configuration (defined in driver) is valid.
                    */
                    (void) Cy_DMA_Descriptor_Init(endpointData->descr0, &DmaDescr1DCfg);

                    locStatus = CY_USBFS_DEV_DRV_SUCCESS;
                }
            }
            else
            {
                if ((NULL != endpointData->descr0) && (NULL != endpointData->descr1))
                {
                    /* Initialize DMA descriptor 0 for 2D operation.
                    * Discard return because descriptor configuration (defined in driver) is valid.
                    */
                    (void) Cy_DMA_Descriptor_Init(endpointData->descr0, &DmaDescr2DCfg);


                    /* Initialize DMA descriptor 0 for 1D operation.
                    * Discard return because descriptor configuration (defined in driver) is valid.
                    */
                    (void)Cy_DMA_Descriptor_Init(endpointData->descr1, &DmaDescr1DCfg);

                    locStatus = CY_USBFS_DEV_DRV_SUCCESS;
                }
            }

            /* Set DMA channel configuration */
            chConfig.enable      = false;
            chConfig.bufferable  = false;
            chConfig.descriptor  = config->dmaConfig[endpoint]->descr0;
            chConfig.preemptable = config->dmaConfig[endpoint]->preemptable;
            chConfig.priority    = config->dmaConfig[endpoint]->priority;

            /* Initialize DMA channel */
            if ((CY_DMA_SUCCESS != Cy_DMA_Channel_Init(endpointData->base, endpointData->chNum, &chConfig)) ||
                (CY_USBFS_DEV_DRV_SUCCESS != locStatus))
            {
                break;
            }

            /* Enable DMA block */
            Cy_DMA_Enable(endpointData->base);
        }
        else
        {
            endpointData->chNum = DMA_INVALID_CHANNEL;
        }

        /* Configuration complete successfully */
        retStatus = CY_USBFS_DEV_DRV_SUCCESS;
    }

    /* Disable all DMAs if any configuration failed */
    if (CY_USBFS_DEV_DRV_SUCCESS != retStatus)
    {
        DmaDisable(context);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: DmaDisable
****************************************************************************//**
*
* Disables all DMA channels used by the USBFS Device.
* The channel state is not verified before being disabled.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
void DmaDisable(cy_stc_usbfs_dev_drv_context_t *context)
{
    uint32_t endpoint;

    /* Disable DMA channels for data endpoints */
    for (endpoint = 0UL; endpoint < CY_USBFS_DEV_DRV_NUM_EPS_MAX; ++endpoint)
    {
        /* Get pointer to endpoint data */
        cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData = &context->epPool[endpoint];

        if (endpointData->chNum != DMA_INVALID_CHANNEL)
        {
            Cy_DMA_Channel_Disable(endpointData->base, endpointData->chNum);
        }
    }
}


/*******************************************************************************
* Function Name: DmaEndpointInit1D
****************************************************************************//**
*
* Configures DMA 1D descriptor used in DMA modes.
*
* \param descr
* The pointer to the DMA descriptor.
*
* \param inDirection
* Endpoint direction associated with DMA descriptor.
*
* \param dataSize
* The DMA transfer data size \ref cy_en_dma_data_size_t.
*
* \param dataReg
* The pointer to the data endpoint data register.
*
*******************************************************************************/
static void DmaEndpointInit1D(cy_stc_dma_descriptor_t *descr, bool inDirection,
                              cy_en_dma_data_size_t dataSize, volatile uint32_t const *dataReg)
{
    Cy_DMA_Descriptor_SetDataSize(descr, dataSize);

    if (inDirection)
    {
        Cy_DMA_Descriptor_SetSrcTransferSize(descr, CY_DMA_TRANSFER_SIZE_DATA);
        Cy_DMA_Descriptor_SetDstTransferSize(descr, CY_DMA_TRANSFER_SIZE_WORD);

        Cy_DMA_Descriptor_SetXloopSrcIncrement(descr, DMA_XLOOP_INCREMENT);
        Cy_DMA_Descriptor_SetXloopDstIncrement(descr, DMA_NO_INCREMENT);

        Cy_DMA_Descriptor_SetDstAddress(descr, (void const *) dataReg);
    }
    else
    {
        Cy_DMA_Descriptor_SetSrcTransferSize(descr, CY_DMA_TRANSFER_SIZE_WORD);
        Cy_DMA_Descriptor_SetDstTransferSize(descr, CY_DMA_TRANSFER_SIZE_DATA);

        Cy_DMA_Descriptor_SetXloopSrcIncrement(descr, DMA_NO_INCREMENT);
        Cy_DMA_Descriptor_SetXloopDstIncrement(descr, DMA_XLOOP_INCREMENT);

        Cy_DMA_Descriptor_SetSrcAddress(descr, (void const *) dataReg);
    }

    /* Link descriptor to itself */
    Cy_DMA_Descriptor_SetNextDescriptor(descr, descr);
}


/*******************************************************************************
* Function Name: DmaEndpointInit2D
****************************************************************************//**
*
* Configures DMA 2D descriptor used in the DMA Automatic mode.
*
* \param descr
* The pointer to the DMA descriptor.
*
* \param inDirection
* Endpoint direction associated with DMA descriptor.
*
* \param numElements
* Number of elements to transfer.
*
*******************************************************************************/
static void DmaEndpointInit2D(cy_stc_dma_descriptor_t *descr, bool inDirection,
                              int32_t numElements)
{
    /* Descriptor 0 (2D): it transfers number of data elements (X loop count)
    * and increments source/destination (depends on direction) by this amount
    * (Y loop increment).
    */
    Cy_DMA_Descriptor_SetXloopDataCount(descr, (uint32_t) numElements);

    if (inDirection)
    {
        Cy_DMA_Descriptor_SetYloopSrcIncrement(descr, numElements);
        Cy_DMA_Descriptor_SetYloopDstIncrement(descr, DMA_NO_INCREMENT);
    }
    else
    {
        Cy_DMA_Descriptor_SetYloopSrcIncrement(descr, DMA_NO_INCREMENT);
        Cy_DMA_Descriptor_SetYloopDstIncrement(descr, numElements);
    }
}


/*******************************************************************************
* Function Name: DmaEndpointSetLength
****************************************************************************//**
*
* Completes DMA initialization for the OUT data endpoint.
* Applicable only when mode is \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO.
*
* \param inDirection
* Endpoint direction associated with DMA descriptor.
*
* \param size
* The number of bytes to load into endpoint.
* This value must be less than or equal to the endpoint maximum packet size.
*
* \param endpoint
* The pointer to the structure that stores endpoint information.
*
*******************************************************************************/
static void DmaEndpointSetLength(bool inDirection, uint32_t size,
                                 cy_stc_usbfs_dev_drv_endpoint_data_t *endpoint)
{
    uint8_t *buf = endpoint->buffer;

    /*
    * Descriptor 0: get number of Y loops. It transfers data in multiples of 32 bytes.
    * Descriptor 1: get number of X loops. It transfers data what was left 1-31 bytes.
    */
    uint32_t numYloops = size / (uint32_t) DMA_YLOOP_INCREMENT;
    uint32_t numXloops = size % (uint32_t) DMA_YLOOP_INCREMENT;

    /* Configure */
    if (inDirection)
    {
        endpoint->startBuf = (uint16_t) size;  /* Store DMA transfer size */
        Cy_DMA_Descriptor_SetSrcAddress(endpoint->descr0, buf);
        Cy_DMA_Descriptor_SetSrcAddress(endpoint->descr1, &buf[size - numXloops]);
    }
    else
    {
        endpoint->startBuf = (numYloops > 0U) ? 1U : 0U; /* Store 1st DMA descriptor to execute */
        Cy_DMA_Descriptor_SetDstAddress(endpoint->descr0, buf);
        Cy_DMA_Descriptor_SetDstAddress(endpoint->descr1, &buf[size - numXloops]);
    }

    /* Configure loop length */
    if (numYloops > 0UL)
    {
        Cy_DMA_Descriptor_SetYloopDataCount(endpoint->descr0, numYloops);
    }

    if (numXloops > 0UL)
    {
        Cy_DMA_Descriptor_SetXloopDataCount(endpoint->descr1, numXloops);
    }

    /* Chain descriptors to operate */
    if (numYloops == 0UL)
    {
        /* (Size < 32): only Descriptor 1 transfers data */
        Cy_DMA_Descriptor_SetNextDescriptor(endpoint->descr1, endpoint->descr1);
    }
    else if (numXloops == 0UL)
    {
        /* Size multiple of 32: only Descriptor 0 transfers data */
        Cy_DMA_Descriptor_SetNextDescriptor(endpoint->descr0, endpoint->descr0);
    }
    else
    {
        /* (Size > 32): both Descriptor 0 and 1 transfer data */
        Cy_DMA_Descriptor_SetNextDescriptor(endpoint->descr0, endpoint->descr1);
        Cy_DMA_Descriptor_SetNextDescriptor(endpoint->descr1, endpoint->descr0);
    }

    /* Keep channel enabled after execution of Descriptor 0 to execute Descriptor 1 */
    Cy_DMA_Descriptor_SetChannelState(endpoint->descr0,
                                        ((numYloops > 0UL) && (numXloops > 0UL)) ?
                                            CY_DMA_CHANNEL_ENABLED : CY_DMA_CHANNEL_DISABLED);

    /* Start execution from Descriptor 0 (length >= 32) or Descriptor 1 (length < 32) */
    Cy_DMA_Channel_SetDescriptor(endpoint->base, endpoint->chNum,
                                    ((numYloops > 0UL) ? endpoint->descr0 : endpoint->descr1));

    /* Configuration complete: enable channel */
    Cy_DMA_Channel_Enable(endpoint->base, endpoint->chNum);
}


/*******************************************************************************
* Function Name: DmaOutEndpointRestore
****************************************************************************//**
*
* Restores the DMA channel after transfer is completed for the the OUT data endpoint.
* Applicable only when mode is \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO.
*
* \param endpoint
* The pointer to the structure that stores endpoint information.
*
*******************************************************************************/
void DmaOutEndpointRestore(cy_stc_usbfs_dev_drv_endpoint_data_t *endpoint)
{
    /* Number of clocks for DMA completion pulse */
    const uint32_t CY_USBFS_DEV_DRV_TRIG_CYCLES = 2UL;

    /* Define which descriptor is 1st in the chain */
    bool setDescr0 = (0U != endpoint->startBuf);

    /* Channel disable aborts on-going transfer */
    Cy_DMA_Channel_Disable(endpoint->base, endpoint->chNum);

    /* Send pulse to UBSFS IP to indicate end of DMA transfer */
    (void) Cy_TrigMux_SwTrigger(endpoint->outTrigMux, CY_USBFS_DEV_DRV_TRIG_CYCLES);

    /* Set 1st DMA descriptor for the following transfer */
    Cy_DMA_Channel_SetDescriptor(endpoint->base, endpoint->chNum,
                                                (setDescr0 ? endpoint->descr0 : endpoint->descr1));

    Cy_DMA_Channel_Enable(endpoint->base, endpoint->chNum);
}


/*******************************************************************************
* Function Name: DmaEndpointInit
****************************************************************************//**
*
* Initializes DMA descriptor for a certain data endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param mode
*
* \param useReg16
* Defines which endpoint registers to use: 8-bits or 16-bits.
*
* \param endpointData
* The pointer to the endpoint data structure.
*
* \return
* Status code of the function execution \ref cy_en_usbfs_dev_drv_status_t.
*
*******************************************************************************/
cy_en_usbfs_dev_drv_status_t DmaEndpointInit(USBFS_Type *base,
                                             cy_en_usbfs_dev_drv_ep_management_mode_t mode,
                                             bool useReg16,
                                             cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData)
{
    cy_en_dma_data_size_t regSize;
    int32_t numElements;
    uint32_t volatile *dataReg;

    /* Get direction and endpoint number */
    bool inDirection  = IS_EP_DIR_IN(endpointData->address);
    uint32_t endpoint = EPADDR2PHY(endpointData->address);

    if (DMA_INVALID_CHANNEL == endpointData->chNum)
    {
        return CY_USBFS_DEV_DRV_DMA_CFG_FAILED;
    }

    /* Set configuration variables depending on access type */
    if (useReg16)
    {
        dataReg     = Cy_USBFS_Dev_Drv_GetDataReg16Addr(base, endpoint);
        regSize     = CY_DMA_HALFWORD;
        numElements = (DMA_YLOOP_INCREMENT / 2);
    }
    else
    {
        dataReg     = Cy_USBFS_Dev_Drv_GetDataRegAddr(base, endpoint);
        regSize     = CY_DMA_BYTE;
        numElements = DMA_YLOOP_INCREMENT;
    }

    /* Disable channel before configuration */
    Cy_DMA_Channel_Disable(endpointData->base, endpointData->chNum);

    /* Configure Descriptor 0 for 1D operation */
    DmaEndpointInit1D(endpointData->descr0, inDirection, regSize, dataReg);

    if (CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO == mode)
    {
        /* Configure Descriptor 0 for 2D operation */
        DmaEndpointInit2D(endpointData->descr0, inDirection, numElements);

        /* Configure Descriptor 1 for 1D operation */
        DmaEndpointInit1D(endpointData->descr1, inDirection, regSize, dataReg);

        /* Configure descriptors to access buffer */
        DmaEndpointSetLength(inDirection, (uint32_t) endpointData->bufferSize, endpointData);
    }

    return CY_USBFS_DEV_DRV_SUCCESS;
}


/*******************************************************************************
* Function Name: DynamicEndpointReConfiguration
****************************************************************************//**
*
* Changes endpoint direction (IN -> OUT or OUT -> IN).
* This function is also used to flush IN or OUT endpoint buffer.
* Applicable only when mode is \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO.
*
* \param base
* The pointer to the USBFS instance.
*
* \param inDirection
* True - endpoint direction is IN; False - endpoint direction is OUT.
*
* \param endpoint
* The data endpoint number.
*
* \return
* Status code of the function execution \ref cy_en_usbfs_dev_drv_status_t.
*
*******************************************************************************/
cy_en_usbfs_dev_drv_status_t DynamicEndpointReConfiguration(USBFS_Type *base,
                                                            bool        inDirection,
                                                            uint32_t    endpoint)
{
    cy_en_usbfs_dev_drv_status_t retStatus = CY_USBFS_DEV_DRV_EP_DYN_RECONFIG_TIMEOUT;

    uint32_t timeout = DYN_RECONFIG_TIMEOUT;

    /* Only enabled endpoint can be re-configured */
    if (0U == (USBFS_DEV_EP_ACTIVE(base) & EP2MASK(endpoint)))
    {
        return CY_USBFS_DEV_DRV_BUF_ALLOC_FAILED;
    }

    /* Request reconfiguration for endpoint */
    USBFS_DEV_DYN_RECONFIG(base) = (USBFS_USBDEV_DYN_RECONFIG_EN_Msk |
                                    _VAL2FLD(USBFS_USBDEV_DYN_RECONFIG_EPNO, endpoint));

    /* Cypress ID#295549: execute dummy read */
    (void) USBFS_DEV_DYN_RECONFIG(base);

    /* Wait for dynamic re-configuration completion */
    while ((0U == (USBFS_DEV_DYN_RECONFIG(base) & USBFS_USBDEV_DYN_RECONFIG_RDY_STS_Msk)) &&
           (timeout > 0U))
    {
        Cy_SysLib_DelayUs(DYN_RECONFIG_ONE_TICK);
        --timeout;
    }

    /* Verify operation result */
    if (timeout > 0U)
    {
        Cy_USBFS_Dev_Drv_SetEpType(base, inDirection, endpoint);
        retStatus = CY_USBFS_DEV_DRV_SUCCESS;
    }

    /* Complete endpoint reconfiguration: clear request */
    USBFS_DEV_DYN_RECONFIG(base) &= ~USBFS_USBDEV_DYN_RECONFIG_EN_Msk;
    (void) USBFS_DEV_DYN_RECONFIG(base);

    /* Clear register for next re-configuration */
    USBFS_DEV_DYN_RECONFIG(base) = 0U;

    return retStatus;
}


/*******************************************************************************
* Function Name: AddEndpointRamBuffer
****************************************************************************//**
*
* Implements \ref Cy_USBFS_Dev_Drv_AddEndpoint for
* \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO mode.
*
* \param base
* The pointer to the USBFS instance.
*
* \param config
* The pointer to data endpoint configuration \ref cy_stc_usb_dev_ep_config_t.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return
* Status code of the function execution \ref cy_en_usbfs_dev_drv_status_t.
*
*******************************************************************************/
cy_en_usbfs_dev_drv_status_t AddEndpointRamBuffer(USBFS_Type *base,
                                                  cy_stc_usb_dev_ep_config_t const *config,
                                                  cy_stc_usbfs_dev_drv_context_t   *context)
{
    cy_en_usbfs_dev_drv_status_t retStatus = CY_USBFS_DEV_DRV_BAD_PARAM;

    uint32_t endpoint = EPADDR2PHY(config->endpointAddr);

    /* Get pointer to endpoint data */
    cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData = &context->epPool[endpoint];

    /* Get buffer for endpoint using buffer allocated by the user */
    if (config->allocBuffer)
    {
        uint32_t startBufIdx;

        /* Configure active endpoint */
        context->activeEpMask    |= (uint8_t) EP2MASK(endpoint);
        USBFS_DEV_EP_ACTIVE(base) = context->activeEpMask;

        /* Allocate buffer for endpoint */
        retStatus = GetEndpointBuffer((uint32_t) config->bufferSize, &startBufIdx, context);
        if (CY_USBFS_DEV_DRV_SUCCESS != retStatus)
        {
            return retStatus;
        }

        /* Store pointer to buffer for this endpoint */
        endpointData->buffer = &context->epSharedBuf[startBufIdx];
    }

    /* Enable endpoint for operation */
    if (config->enableEndpoint)
    {
        bool inDirection = IS_EP_DIR_IN(config->endpointAddr);

        /* Clear variables related to endpoint */
        endpointData->state   = CY_USB_DEV_EP_IDLE;
        endpointData->address = config->endpointAddr;
        endpointData->toggle  = 0U;
        endpointData->bufferSize = config->maxPacketSize;
        endpointData->sieMode    = GetEndpointActiveMode(inDirection, config->attributes);
        endpointData->isPending  = false;

        /* Set arbiter configuration (clears DMA requests) */
        Cy_USBFS_Dev_Drv_SetArbEpConfig(base, endpoint, (USBFS_USBDEV_ARB_EP1_CFG_CRC_BYPASS_Msk |
                                                         USBFS_USBDEV_ARB_EP1_CFG_RESET_PTR_Msk));

        /* Performs dynamic reconfiguration to make sure that the DMA has completed the data transfer.
        * Also it flushes endpoint pre-fetch buffer (useful for IN endpoints).
        */
        retStatus = DynamicEndpointReConfiguration(base, inDirection, endpoint);
        if (CY_USBFS_DEV_DRV_SUCCESS != retStatus)
        {
            return retStatus;
        }

        /* Configure DMA for endpoint */
        retStatus = DmaEndpointInit(base, context->mode, context->useReg16, endpointData);
        if (CY_USBFS_DEV_DRV_SUCCESS != retStatus)
        {
            return retStatus;
        }

        /* Enable Arbiter interrupt sources for endpoint */
        Cy_USBFS_Dev_Drv_SetArbEpInterruptMask(base, endpoint,(inDirection ?
                                                             IN_ENDPOINT_ARB_INTR_SOURCES :
                                                             OUT_ENDPOINT_ARB_INTR_SOURCES));

        /* Enable SIE and arbiter interrupt for endpoint */
        Cy_USBFS_Dev_Drv_EnableSieEpInterrupt(base, endpoint);
        Cy_USBFS_Dev_Drv_EnableArbEpInterrupt(base, endpoint);

        /* Set SIE mode to respond to host */
        Cy_USBFS_Dev_Drv_SetSieEpMode(base, endpoint, GetEndpointInactiveMode((uint32_t) endpointData->sieMode));
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: RestoreEndpointRamBuffer
****************************************************************************//**
*
* Restores endpoint active configuration for
* \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO mode.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpointData
* The pointer to the endpoint data structure.
*
*******************************************************************************/
void RestoreEndpointRamBuffer(USBFS_Type *base,
                              cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData)
{
    bool inDirection  = IS_EP_DIR_IN(endpointData->address);
    uint32_t endpoint = EPADDR2PHY(endpointData->address);

    /* Clear state */
    endpointData->state = CY_USB_DEV_EP_IDLE;

    /* Configure active endpoint */
    USBFS_DEV_EP_ACTIVE(base) |= EP2MASK(endpoint);

    /* Configure endpoint type: OUT - 1, IN - 0 */
    Cy_USBFS_Dev_Drv_SetEpType(base, inDirection, endpoint);

    /* Enable Arbiter interrupt sources for endpoint */
    Cy_USBFS_Dev_Drv_SetArbEpInterruptMask(base, endpoint, (inDirection ?
                                                            IN_ENDPOINT_ARB_INTR_SOURCES :
                                                            OUT_ENDPOINT_ARB_INTR_SOURCES));

    /* Enable SIE and arbiter interrupt for endpoint */
    Cy_USBFS_Dev_Drv_EnableSieEpInterrupt(base, endpoint);
    Cy_USBFS_Dev_Drv_EnableArbEpInterrupt(base, endpoint);

    if (false == inDirection)
    {
        /* OUT Endpoint: enable DMA channel endpoint ready for operation.
        * IN Endpoint: keep disabled, it is enabled in LoadInEndpointDmaAuto.
        */
        Cy_DMA_Channel_Enable(endpointData->base, endpointData->chNum);
    }

    /* Sets an arbiter configuration */
    Cy_USBFS_Dev_Drv_SetArbEpConfig(base, endpoint, (USBFS_USBDEV_ARB_EP1_CFG_CRC_BYPASS_Msk |
                                                     USBFS_USBDEV_ARB_EP1_CFG_RESET_PTR_Msk));

    /* Set SIE mode to respond to host */
    Cy_USBFS_Dev_Drv_SetSieEpMode(base, endpoint, GetEndpointInactiveMode((uint32_t) endpointData->sieMode));
}


/*******************************************************************************
* Function Name: LoadInEndpointDma
****************************************************************************//**
*
* Implements \ref Cy_USBFS_Dev_Drv_LoadInEndpoint for
* \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA mode.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* The IN data endpoint number.
*
* \param buffer
* The pointer to the buffer containing data bytes to load.
*
* \param size
* The number of bytes to load into the endpoint.
* This value must be less than or equal to the endpoint maximum packet size.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return
* Status code of the function execution \ref cy_en_usbfs_dev_drv_status_t.
*
*******************************************************************************/
cy_en_usbfs_dev_drv_status_t LoadInEndpointDma(USBFS_Type    *base,
                                               uint32_t      endpoint,
                                               uint8_t const *buffer,
                                               uint32_t      size,
                                               cy_stc_usbfs_dev_drv_context_t *context)
{
    cy_en_usbfs_dev_drv_status_t retStatus = CY_USBFS_DEV_DRV_EP_DMA_WRITE_TIMEOUT;

    /* Get pointer to endpoint data */
    cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData = &context->epPool[endpoint];

    /* Request to load more bytes than endpoint buffer */
    if (size > endpointData->bufferSize)
    {
        return CY_USBFS_DEV_DRV_BAD_PARAM;
    }

    /* Clears the abort mask for the endpoint (there is no transfer during abort) */
    context->epAbortMask &= (uint8_t) ~EP2MASK(endpoint);

    /* Set count and data toggle */
    Cy_USBFS_Dev_Drv_SetSieEpCount(base, endpoint, size, (uint32_t) endpointData->toggle);

    if (0U == size)
    {
        /* Endpoint pending: Waits for the host read data after exiting this function */
        endpointData->state = CY_USB_DEV_EP_PENDING;

        /* Arm endpoint: Host is allowed to read data */
        Cy_USBFS_Dev_Drv_SetSieEpMode(base, endpoint, (uint32_t) endpointData->sieMode);

        retStatus = CY_USBFS_DEV_DRV_SUCCESS;
    }
    else
    {
        /* Channel is disabled after initialization or descriptor completion  */

        uint32_t timeout = DMA_WRITE_REQUEST_TIMEOUT;

        /* Get number of data elements to transfer */
        size = context->useReg16 ? GET_SIZE16(size) : size;

        /* 1D descriptor: configure source address and length */
        Cy_DMA_Descriptor_SetSrcAddress    (endpointData->descr0, (const void*) buffer);
        Cy_DMA_Descriptor_SetXloopDataCount(endpointData->descr0, size);

        /* Enable DMA channel: configuration complete */
        Cy_DMA_Channel_Enable(endpointData->base, endpointData->chNum);

        /* Generate DMA request: the endpoint will be armed when the DMA is
        * finished in the Arbiter interrupt
        */
        Cy_USBFS_Dev_Drv_TriggerArbCfgEpDmaReq(base, endpoint);

        /* Waits until DMA completes the write operation. The current endpoint state is
        * idle or completed and DMA completion interrupt changes state to pending
        * (endpoint waits for the host read data).
        */
        while ((CY_USB_DEV_EP_PENDING != endpointData->state) &&
               (timeout > 0U))
        {
            Cy_SysLib_DelayUs(DMA_WRITE_REQUEST_ONE_TICK);
            --timeout;
        }

        /* Check timeout */
        if (timeout > 0U)
        {
            retStatus = CY_USBFS_DEV_DRV_SUCCESS;
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: ReadOutEndpointDma
****************************************************************************//**
*
* Implements \ref Cy_USBFS_Dev_Drv_ReadOutEndpoint for
* \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA mode.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* The OUT data endpoint number.
*
* \param buffer
* Pointer to buffer that stores data that was read.
*
* \param size
* The number of bytes to read from endpoint.
* This value must be less than or equal to the endpoint maximum packet size.
*
* \param actSize
* The number of bytes that were actually read.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return
* Status code of the function execution \ref cy_en_usbfs_dev_drv_status_t.
*
*******************************************************************************/
cy_en_usbfs_dev_drv_status_t ReadOutEndpointDma(USBFS_Type *base,
                                                uint32_t   endpoint,
                                                uint8_t    *buffer,
                                                uint32_t   size,
                                                uint32_t   *actSize,
                                                cy_stc_usbfs_dev_drv_context_t *context)
{
    cy_en_usbfs_dev_drv_status_t retStatus = CY_USBFS_DEV_DRV_EP_DMA_READ_TIMEOUT;

    /* Get pointer to endpoint data */
    cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData = &context->epPool[endpoint];

    uint32_t timeout = DMA_READ_REQUEST_TIMEOUT;

    /* Get number of received bytes */
    uint32_t numToCopy = Cy_USBFS_Dev_Drv_GetSieEpCount(base, endpoint);
    uint32_t actCopied = numToCopy;

    /* Initialize actual number of copied bytes */
    *actSize = 0U;

    /* Endpoint received more bytes than provided buffer */
    if (numToCopy > size)
    {
        return CY_USBFS_DEV_DRV_BAD_PARAM;
    }

    /* Nothing to copy; return success */
    if (0U == numToCopy)
    {
        return CY_USBFS_DEV_DRV_SUCCESS;
    }

    /* Channel is disabled after initialization or descriptor completion  */

    /* Get number of data elements to transfer */
    numToCopy = context->useReg16 ? GET_SIZE16(numToCopy) : numToCopy;

    /* 1D descriptor: configure destination address and length */
    Cy_DMA_Descriptor_SetDstAddress    (endpointData->descr0, buffer);
    Cy_DMA_Descriptor_SetXloopDataCount(endpointData->descr0, numToCopy);

    /* Enable DMA channel: configuration complete */
    Cy_DMA_Channel_Enable(endpointData->base, endpointData->chNum);

    /* The current endpoint state is completed, changes the state to pending to
    * track DMA read completion.
    */
    endpointData->state = CY_USB_DEV_EP_PENDING;

    /* Generate DMA request to read data from hardware buffer */
    Cy_USBFS_Dev_Drv_TriggerArbCfgEpDmaReq(base, endpoint);

    /* Waits until DMA completes the read operation */
    while ((CY_USB_DEV_EP_COMPLETED != endpointData->state) &&
           (timeout > 0U))
    {
        Cy_SysLib_DelayUs(DMA_READ_REQUEST_ONE_TICK);
        --timeout;
    }

    /* Check timeout */
    if (timeout > 0U)
    {
        /* Update number of copied bytes */
        *actSize = actCopied;
        retStatus = CY_USBFS_DEV_DRV_SUCCESS;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: LoadInEndpointDmaAuto
****************************************************************************//**
*
* Implements \ref Cy_USBFS_Dev_Drv_LoadInEndpoint for
* \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO mode.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* The IN data endpoint number.
*
* \param buffer
* The pointer to the buffer containing data bytes to load.
*
* \param size
* The number of bytes to load into endpoint.
* This value must be less than or equal to the endpoint maximum packet size.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return
* Status code of the function execution \ref cy_en_usbfs_dev_drv_status_t.
*
*******************************************************************************/
cy_en_usbfs_dev_drv_status_t LoadInEndpointDmaAuto(USBFS_Type    *base,
                                                   uint32_t      endpoint,
                                                   uint8_t const *buffer,
                                                   uint32_t      size,
                                                   cy_stc_usbfs_dev_drv_context_t *context)
{
    /* Get pointer to endpoint data */
    cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData = &context->epPool[endpoint];

    /* Request to load more bytes than endpoint buffer */
    if (size > endpointData->bufferSize)
    {
        return CY_USBFS_DEV_DRV_BAD_PARAM;
    }

    /* Clears the abort mask for the endpoint (there is no transfer during abort) */
    context->epAbortMask &= (uint8_t) ~EP2MASK(endpoint);

    /* Endpoint pending: Waits for the host read data after exiting this function */
    endpointData->state = CY_USB_DEV_EP_PENDING;

    /* Set count and data toggle */
    Cy_USBFS_Dev_Drv_SetSieEpCount(base, endpoint, size, (uint32_t) endpointData->toggle);

    if (0U == size)
    {
        /* Arm endpoint: Host is allowed to read data */
        Cy_USBFS_Dev_Drv_SetSieEpMode(base, endpoint, (uint32_t) endpointData->sieMode);
    }
    else
    {
        /* Copy data from user buffer to internal endpoint buffer */
        if (NULL != endpointData->copyData)
        {
            (void) endpointData->copyData(endpointData->buffer, buffer, size);
        }
        else
        {
            (void) memcpy(endpointData->buffer, buffer, size);
        }

        /* Configure transfer length */
        if (size != endpointData->startBuf)
        {
            /* Update transfer length, endpoint startBuf and enables DMA */
            DmaEndpointSetLength(true, size, &context->epPool[endpoint]);
        }
        else
        {
            /* Reset DMA channel indexes, they keep value after Resume or Abort */
            Cy_DMA_Channel_SetDescriptor(endpointData->base, endpointData->chNum,
                                            (endpointData->startBuf >= (uint32_t) DMA_YLOOP_INCREMENT) ?
                                                endpointData->descr0 : endpointData->descr1);

            /* Enable channel: configuration complete */
            Cy_DMA_Channel_Enable(endpointData->base, endpointData->chNum);
        }

        /* Generate DMA request to pre-load data into endpoint buffer */
        Cy_USBFS_Dev_Drv_SetArbCfgEpInReady(base, endpoint);

        /* IN endpoint will be armed in the Arbiter interrupt (source: IN_BUF_FULL)
        * after DMA pre-load data buffer.
        */
    }

    return CY_USBFS_DEV_DRV_SUCCESS;
}


/*******************************************************************************
* Function Name: ReadOutEndpointDmaAuto
****************************************************************************//**
*
* Implements \ref Cy_USBFS_Dev_Drv_ReadOutEndpoint for
* \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO mode.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* The OUT data endpoint number.
*
* \param buffer
* Pointer to buffer that stores data that was read.
*
* \param size
* The number of bytes to read from the endpoint.
* This value must be less than or equal to the endpoint maximum packet size.
*
* \param actSize
* The number of bytes which were actually read.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return
* Status code of the function execution \ref cy_en_usbfs_dev_drv_status_t.
*
*******************************************************************************/
cy_en_usbfs_dev_drv_status_t ReadOutEndpointDmaAuto(USBFS_Type *base,
                                                    uint32_t   endpoint,
                                                    uint8_t    *buffer,
                                                    uint32_t   size,
                                                    uint32_t   *actSize,
                                                    cy_stc_usbfs_dev_drv_context_t *context)
{
    /* Get pointer to endpoint data */
    cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData = &context->epPool[endpoint];

    /* Get number of received bytes */
    uint32_t numToCopy = Cy_USBFS_Dev_Drv_GetSieEpCount(base, endpoint);

    /* Initialize actual number of copied bytes */
    *actSize = 0U;

    /* Endpoint received more bytes than provided buffer */
    if (numToCopy > size)
    {
        return CY_USBFS_DEV_DRV_BAD_PARAM;
    }

    /* Nothing to copy (zero length packet) return success */
    if (0U == numToCopy)
    {
        return CY_USBFS_DEV_DRV_SUCCESS;
    }

    /* Copy data from user buffer to internal endpoint buffer */
    if (NULL != endpointData->copyData)
    {
        (void) endpointData->copyData(buffer, endpointData->buffer, numToCopy);
    }
    else
    {
        (void) memcpy(buffer, endpointData->buffer, numToCopy);
    }

    /* Update number of copied bytes */
    *actSize = numToCopy;

    return CY_USBFS_DEV_DRV_SUCCESS;
}


#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXUSBFS */


/* [] END OF FILE */
