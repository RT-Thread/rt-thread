/***************************************************************************//**
* \file cy_usbfs_dev_drv_io.c
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

/* The time to wait (in milliseconds) for completion of a BULK or INTERRUPT transfer (max packet 64 bytes).
* The transfer takes 48.5 us = (1/ 12) * (32 (IN/OUT) + (64 * 8 + 32) (DATA) + 16 (ACK) + 6 (EOPs)), used 50 us.
*/
#define WAIT_TRANSFER_COMPLETE     (50U)

/* Dedicated IN and OUT endpoints buffer: 32 bytes (2^5) */
#define ENDPOINTS_BUFFER_SIZE   (0x55UL)

/* The number of bytes transferred by 1 Y-loop */
#define DMA_YLOOP_INCREMENT     (32UL)

/* All arbiter interrupt sources */
#define ENDPOINT_ARB_INTR_SOURCES_ALL    (USBFS_USBDEV_ARB_EP_IN_BUF_FULL_Msk | \
                                          USBFS_USBDEV_ARB_EP_DMA_GNT_Msk     | \
                                          USBFS_USBDEV_ARB_EP_BUF_OVER_Msk    | \
                                          USBFS_USBDEV_ARB_EP_BUF_UNDER_Msk   | \
                                          USBFS_USBDEV_ARB_EP_ERR_Msk         | \
                                          USBFS_USBDEV_ARB_EP_DMA_TERMIN_Msk)

/* Arbiter interrupt sources for OUT and IN endpoints when mode is
* CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO.
*/
#define ENDPOINT_ARB_INTR_SOURCES_CPU       (USBFS_USBDEV_ARB_EP_ERR_Msk)

#define OUT_ENDPOINT_ARB_INTR_SOURCES_CPU   (USBFS_USBDEV_ARB_EP_ERR_Msk)

#define IN_ENDPOINT_ARB_INTR_SOURCES_DMA    (USBFS_USBDEV_ARB_EP_IN_BUF_FULL_Msk | \
                                             USBFS_USBDEV_ARB_EP_ERR_Msk)

#define OUT_ENDPOINT_ARB_INTR_SOURCES_DMA   (USBFS_USBDEV_ARB_EP_DMA_GNT_Msk | \
                                             USBFS_USBDEV_ARB_EP_ERR_Msk)


/*******************************************************************************
*                        Internal Functions Prototypes
*******************************************************************************/
static void DisableEndpoint(USBFS_Type *base, uint32_t endpoint, cy_stc_usbfs_dev_drv_context_t *context);


/*******************************************************************************
* Function Name: DisableEndpoint
****************************************************************************//**
*
* Disables the endpoint operation.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* The data endpoint number.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
static void DisableEndpoint(USBFS_Type *base, uint32_t endpoint, cy_stc_usbfs_dev_drv_context_t *context)
{
    /* Disables endpoint SIE mode and sets the appropriate state */
    Cy_USBFS_Dev_Drv_SetSieEpMode(base, endpoint, CY_USBFS_DEV_DRV_EP_CR_DISABLE);
    context->epPool[endpoint].state = CY_USB_DEV_EP_DISABLED;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_ConfigDevice
****************************************************************************//**
*
* Sets the basic device configuration (clears previous configuration).
* Call this function after the endpoints were configured to complete the
* device configuration.
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
void Cy_USBFS_Dev_Drv_ConfigDevice(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context)
{
    if (CY_USBFS_DEV_DRV_EP_MANAGEMENT_CPU != context->mode)
    {
        uint32_t autoMemMask = 0U;

        if (CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO == context->mode)
        {
            autoMemMask = USBFS_USBDEV_ARB_CFG_AUTO_MEM_Msk;

            /* Configure DMA burst size */
            USBFS_DEV_DMA_THRES16(base) = DMA_YLOOP_INCREMENT;
            USBFS_DEV_BUF_SIZE(base)    = ENDPOINTS_BUFFER_SIZE;

            /* USBFS_DEV_EP_ACTIVE and USBFS_DEV_EP_TYPE are set when endpoint is added */
        }

        /* The configuration completes: Generates a rising edge for the USBDEV_ARB_CFG.CFG_CMP bit */
        USBFS_DEV_ARB_CFG(base)  = _VAL2FLD(USBFS_USBDEV_ARB_CFG_DMA_CFG, context->mode) |
                                   autoMemMask;
        /* Read the register to ensure that the write is flushed out to the hardware */
        (void) USBFS_DEV_ARB_CFG(base);
        USBFS_DEV_ARB_CFG(base) |= USBFS_USBDEV_ARB_CFG_CFG_CMP_Msk;
        (void) USBFS_DEV_ARB_CFG(base);
    }
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_UnConfigureDevice
****************************************************************************//**
*
* Clears device configuration.
* Call this function before setting a configuration or a configuration failure
* to set the configuration into the default state.
* Alternately, call \ref Cy_USBFS_Dev_Drv_RemoveEndpoint for each active endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
void Cy_USBFS_Dev_Drv_UnConfigureDevice(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context)
{
    uint32_t endpoint;

    /* Clears the buffer pointer */
    context->curBufAddr = 0U;

    /* Removes all active endpoints */
    context->activeEpMask = 0U;

    /* Disables the SIE and Arbiter interrupts */
    USBFS_DEV_SIE_EP_INT_EN(base) = 0UL;
    USBFS_DEV_ARB_INT_EN(base)    = 0UL;

    /* Clear endpoints configuration */
    for (endpoint = 0U; endpoint <  CY_USBFS_DEV_DRV_NUM_EPS_MAX; ++endpoint)
    {
        /* Disable endpoint operation */
        DisableEndpoint(base, endpoint, context);
    }
}


/*******************************************************************************
* Function Name: GetEndpointBuffer
****************************************************************************//**
*
* Returns a start position in the allocated buffer for the data endpoint.
*
* \param size
* The data endpoint buffer size.
*
* \param idx
* The start position of the allocated endpoint buffer.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return
* The status code of the function execution \ref cy_en_usbfs_dev_drv_status_t.
*
*******************************************************************************/
cy_en_usbfs_dev_drv_status_t GetEndpointBuffer(uint32_t size, uint32_t *idx, cy_stc_usbfs_dev_drv_context_t *context)
{
    cy_en_usbfs_dev_drv_status_t retStatus = CY_USBFS_DEV_DRV_BUF_ALLOC_FAILED;
    uint32_t bufSize;
    uint32_t nextBufAddr;

    /* Get max buffer size */
    bufSize = (CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO != context->mode) ?
                CY_USBFS_DEV_DRV_HW_BUFFER_SIZE :
                context->epSharedBufSize;

    /* Gets a next buffer address. Note: the end buffer size must be even for the 16-bit access. */
    nextBufAddr  = (context->curBufAddr + size);
    nextBufAddr += (context->useReg16) ? (size & 0x01U) : 0U;

    /* Checks whether there is enough space in the buffer. */
    if (nextBufAddr <= bufSize)
    {
        /* Updates the pointers */
        *idx = context->curBufAddr;
        context->curBufAddr = (uint16_t) nextBufAddr;

        retStatus = CY_USBFS_DEV_DRV_SUCCESS;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: RestoreEndpointHwBuffer
****************************************************************************//**
*
* Restores the endpoint active configuration for
* \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_CPU and
* \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA modes.
*
* \param base
* The pointer to the USBFS instance.
*
* \param mode
* Endpoints management mode.
*
* \param endpointData
* The pointer to the endpoint data structure.
*
*******************************************************************************/
void RestoreEndpointHwBuffer(USBFS_Type *base,
                             cy_en_usbfs_dev_drv_ep_management_mode_t mode,
                             cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData)
{
    bool inDirection  = IS_EP_DIR_IN(endpointData->address);
    uint32_t endpoint = EPADDR2PHY(endpointData->address);

    /* Clears the  state: MEM_DATA is not non-retention */
    endpointData->state = CY_USB_DEV_EP_IDLE;

    /* Sets the Arbiter read and write pointers */
    Cy_USBFS_Dev_Drv_SetArbWriteAddr(base, endpoint, (uint32_t) endpointData->startBuf);
    Cy_USBFS_Dev_Drv_SetArbReadAddr (base, endpoint, (uint32_t) endpointData->startBuf);

    /* Enables the endpoint Arbiter interrupt sources */
    if (CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA == mode)
    {
        /* Enables the Arbiter interrupt sources for endpoint */
        Cy_USBFS_Dev_Drv_SetArbEpInterruptMask(base, endpoint, (inDirection ?
                                                                IN_ENDPOINT_ARB_INTR_SOURCES_DMA :
                                                                OUT_ENDPOINT_ARB_INTR_SOURCES_DMA));

        /* Enables the Arbiter interrupt for endpoint */
        Cy_USBFS_Dev_Drv_EnableArbEpInterrupt(base, endpoint);

        /* Enables the DMA channel */
         Cy_DMA_Channel_Enable(endpointData->base, endpointData->chNum);
    }
    else
    {
        /* Enables the error interrupt triggered by SIE */
        Cy_USBFS_Dev_Drv_SetArbEpInterruptMask(base, endpoint, ENDPOINT_ARB_INTR_SOURCES_CPU);
    }

    /* Enables the SIE interrupt for the endpoint */
    Cy_USBFS_Dev_Drv_EnableSieEpInterrupt(base, endpoint);

    /* Sets an arbiter configuration */
    Cy_USBFS_Dev_Drv_SetArbEpConfig(base, endpoint, (USBFS_USBDEV_ARB_EP1_CFG_CRC_BYPASS_Msk |
                                                     USBFS_USBDEV_ARB_EP1_CFG_RESET_PTR_Msk));

    /* Set endpoint mode to not respond to host */
    Cy_USBFS_Dev_Drv_SetSieEpMode(base, endpoint, GetEndpointInactiveMode((uint32_t) endpointData->sieMode));
}


/*******************************************************************************
* Function Name: AddEndpointHwBuffer
****************************************************************************//**
*
* Implements \ref Cy_USBFS_Dev_Drv_AddEndpoint for
* \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_CPU and
* \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA modes.
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
* The status code of the function execution \ref cy_en_usbfs_dev_drv_status_t.
*
*******************************************************************************/
cy_en_usbfs_dev_drv_status_t AddEndpointHwBuffer(USBFS_Type *base,
                                                 cy_stc_usb_dev_ep_config_t const *config,
                                                 cy_stc_usbfs_dev_drv_context_t   *context)
{
    uint32_t endpoint = EPADDR2PHY(config->endpointAddr);

    /* Gets a pointer to the endpoint data */
    cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData = &context->epPool[endpoint];

    /* Gets a buffer for the endpoint using the hardware buffer */
    if (config->allocBuffer)
    {
        uint32_t bufOffset;

        /* Gets a buffer for the endpoint */
        cy_en_usbfs_dev_drv_status_t retStatus = GetEndpointBuffer((uint32_t) config->bufferSize, &bufOffset, context);
        if (CY_USBFS_DEV_DRV_SUCCESS != retStatus)
        {
            return retStatus;
        }

        /* Sets the Arbiter read and write pointers */
        endpointData->startBuf = (uint16_t) bufOffset;
        Cy_USBFS_Dev_Drv_SetArbWriteAddr(base, endpoint, bufOffset);
        Cy_USBFS_Dev_Drv_SetArbReadAddr (base, endpoint, bufOffset);
    }

    /* Enables the endpoint for the operation */
    if (config->enableEndpoint)
    {
        bool inDirection = IS_EP_DIR_IN(config->endpointAddr);

        /* Configures the endpoint */
        endpointData->state   = CY_USB_DEV_EP_IDLE;
        endpointData->address = config->endpointAddr;
        endpointData->toggle  = 0U;
        endpointData->bufferSize = config->maxPacketSize;
        endpointData->sieMode = GetEndpointActiveMode(inDirection, config->attributes);
        endpointData->isPending = false;

        /* Sets an arbiter configuration (clears DMA requests) */
        Cy_USBFS_Dev_Drv_SetArbEpConfig(base, endpoint, (USBFS_USBDEV_ARB_EP1_CFG_CRC_BYPASS_Msk |
                                                         USBFS_USBDEV_ARB_EP1_CFG_RESET_PTR_Msk));

        /* Flushes the IN endpoint buffer to discard the loaded data.
        * It happens when: an alternate settings change is requested and the IN
        * endpoint buffer is full (not read by the Host).
        */
        if (inDirection)
        {
            Cy_USBFS_Dev_Drv_FlushInBuffer(base, endpoint);
        }

        /* Enables the endpoint arbiter interrupt sources */
        if (CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA == context->mode)
        {
            /* Configures the DMA based on the endpoint direction */
            cy_en_usbfs_dev_drv_status_t retStatus = DmaEndpointInit(base, context->mode, context->useReg16, &context->epPool[endpoint]);
            if (CY_USBFS_DEV_DRV_SUCCESS != retStatus)
            {
                return retStatus;
            }

            /* Enables the arbiter interrupt sources for the endpoint */
            Cy_USBFS_Dev_Drv_SetArbEpInterruptMask(base, endpoint, (inDirection ?
                                                                    IN_ENDPOINT_ARB_INTR_SOURCES_DMA :
                                                                    OUT_ENDPOINT_ARB_INTR_SOURCES_DMA));

            /* Enables the arbiter interrupt for the endpoint */
            Cy_USBFS_Dev_Drv_EnableArbEpInterrupt(base, endpoint);
        }
        else
        {
            /* Enables the error interrupt triggered by SIE */
            Cy_USBFS_Dev_Drv_SetArbEpInterruptMask(base, endpoint, ENDPOINT_ARB_INTR_SOURCES_CPU);
        }

        /* Enables the SIE interrupt for the endpoint */
        Cy_USBFS_Dev_Drv_EnableSieEpInterrupt(base, endpoint);

        /* Sets endpoint mode to not respond to the host */
        Cy_USBFS_Dev_Drv_SetSieEpMode(base, endpoint, GetEndpointInactiveMode((uint32_t) endpointData->sieMode));
    }

    return CY_USBFS_DEV_DRV_SUCCESS;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_RemoveEndpoint
****************************************************************************//**
*
* Removes a data endpoint (release hardware resources allocated by data endpoint).
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpointAddr
* The data endpoint address (7 bit - direction, 3-0 bits - endpoint number).
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
cy_en_usbfs_dev_drv_status_t Cy_USBFS_Dev_Drv_RemoveEndpoint(USBFS_Type *base,
                                                             uint32_t    endpointAddr,
                                                             cy_stc_usbfs_dev_drv_context_t *context)
{
    uint32_t endpoint = EPADDR2EP(endpointAddr);

    /* Checks if the endpoint is supported by the driver */
    if (false == IS_EP_VALID(endpoint))
    {
        return CY_USBFS_DEV_DRV_BAD_PARAM;
    }

    endpoint = EP2PHY(endpoint);

    /* Disable endpoint operation */
    DisableEndpoint(base, endpoint, context);

    /* Disable SIE and Arbiter interrupt for endpoint */
    Cy_USBFS_Dev_Drv_DisableSieEpInterrupt(base, endpoint);
    Cy_USBFS_Dev_Drv_DisableArbEpInterrupt(base, endpoint);

    /* Clear SIE and Arbiter interrupt for endpoint */
    Cy_USBFS_Dev_Drv_ClearSieEpInterrupt(base, endpoint);
    Cy_USBFS_Dev_Drv_ClearArbEpInterrupt(base, endpoint, ENDPOINT_ARB_INTR_SOURCES_ALL);

    /* Removes the active endpoint */
    context->activeEpMask &= (uint8_t) ~EP2MASK(endpoint);

    /* Clear abort mask for endpoint */
    context->epAbortMask &= (uint8_t) ~EP2MASK(endpoint);

    return CY_USBFS_DEV_DRV_SUCCESS;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_EnableOutEndpoint
****************************************************************************//**
*
* Enables the OUT data endpoint to be read by the Host.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* The OUT data endpoint number.
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
* \note
* The OUT endpoints are not enabled by default. The endpoints must be enabled
* before calling \ref Cy_USBFS_Dev_Drv_ReadOutEndpoint to read data from an endpoint.
*
*******************************************************************************/
void Cy_USBFS_Dev_Drv_EnableOutEndpoint(USBFS_Type *base,
                                        uint32_t    endpoint,
                                        cy_stc_usbfs_dev_drv_context_t *context)
{
    CY_ASSERT_L1(IS_EP_VALID(endpoint));

    endpoint = EP2PHY(endpoint);
    CY_ASSERT_L1(IS_EP_DIR_OUT(context->epPool[endpoint].address));

    /* Get pointer to endpoint data */
    cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData = &context->epPool[endpoint];

    /* Clear abort mask for the endpoint (there is no transfer during abort) */
    context->epAbortMask &= (uint8_t) ~EP2MASK(endpoint);

    /* Endpoint pending: Waits for the host write data after exiting this function */
    endpointData->state = CY_USB_DEV_EP_PENDING;

    /* Arm endpoint: Host is allowed to write data */
    Cy_USBFS_Dev_Drv_SetSieEpMode(base, endpoint, (uint32_t) endpointData->sieMode);
}


/*******************************************************************************
* Function Name: LoadInEndpointCpu
****************************************************************************//**
*
* Implements \ref Cy_USBFS_Dev_Drv_LoadInEndpoint for
* \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_CPU mode.
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
* This value must be less than or equal to endpoint maximum packet size.
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
cy_en_usbfs_dev_drv_status_t LoadInEndpointCpu(USBFS_Type   *base,
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

    /* Clear abort mask for the endpoint (there is no transfer during abort) */
    context->epAbortMask &= (uint8_t) ~EP2MASK(endpoint);

    /* Endpoint pending: Waits for the host read data after exiting this function */
    endpointData->state = CY_USB_DEV_EP_PENDING;

    /* Set count and data toggle */
    Cy_USBFS_Dev_Drv_SetSieEpCount(base, endpoint, size, (uint32_t) endpointData->toggle);

    if (0U == size)
    {
        /* Arm endpoint: endpoint ACK Host request */
        Cy_USBFS_Dev_Drv_SetSieEpMode(base, endpoint, (uint32_t) endpointData->sieMode);
    }
    else
    {
        uint32_t idx;

        if (context->useReg16)
        {
            /* Get pointer to the buffer */
            CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3', 'Cast buffer parameter is safe. User must use special macro to allocate buffer, which handles alignment issues.');
            uint16_t const *ptr = (uint16_t const *) buffer;

            /* Get number of writes into the 16-bit register */
            size = GET_SIZE16(size);

            /* Copy data from the user buffer into the hardware buffer */
            for (idx = 0U; idx < size; ++idx)
            {
                Cy_USBFS_Dev_Drv_WriteData16(base, endpoint, ptr[idx]);
            }
        }
        else
        {

            /* Copy data from the user buffer into the hardware buffer */
            for (idx = 0U; idx < size; ++idx)
            {
                Cy_USBFS_Dev_Drv_WriteData(base, endpoint, buffer[idx]);
            }
        }

        /* Arm endpoint: endpoint ACK host request */
        Cy_USBFS_Dev_Drv_SetSieEpMode(base, endpoint, (uint32_t) endpointData->sieMode);
    }

    return CY_USBFS_DEV_DRV_SUCCESS;
}


/*******************************************************************************
* Function Name: ReadOutEndpointCpu
****************************************************************************//**
*
* Implements \ref Cy_USBFS_Dev_Drv_ReadOutEndpoint for
* \ref CY_USBFS_DEV_DRV_EP_MANAGEMENT_CPU mode.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* The OUT data endpoint number.
*
* \param buffer
* Pointer to the buffer that stores data that was read.
*
* \param size
* The number of bytes to read from endpoint.
* This value must be less than or equal to endpoint maximum packet size.
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
cy_en_usbfs_dev_drv_status_t ReadOutEndpointCpu(USBFS_Type *base,
                                                uint32_t   endpoint,
                                                uint8_t    *buffer,
                                                uint32_t   size,
                                                uint32_t   *actSize,
                                                cy_stc_usbfs_dev_drv_context_t *context)
{
    uint32_t idx;
    uint32_t numToCopy;

    /* Suppress a compiler warning about unused variables */
    (void) context;

    /* Get number of received bytes */
    numToCopy = Cy_USBFS_Dev_Drv_GetSieEpCount(base, endpoint);

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

    /* Update number of copied bytes */
    *actSize = numToCopy;

    if (context->useReg16)
    {
        /* Get pointer to the buffer */
        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3', 'Cast buffer parameter is safe. User must use special macro to xallocate buffer, which handles alignment issues.');
        uint16_t *ptr = (uint16_t *) buffer;

        /* Get number of reads from 16-bit register */
        numToCopy = GET_SIZE16(numToCopy);

        /* Copy data from the hardware buffer into user buffer */
        for (idx = 0U; idx < numToCopy; ++idx)
        {
            ptr[idx] = Cy_USBFS_Dev_Drv_ReadData16(base, endpoint);
        }
    }
    else
    {
        /* Copy data from the hardware buffer into the user buffer */
        for (idx = 0U; idx < numToCopy; ++idx)
        {
            buffer[idx] = Cy_USBFS_Dev_Drv_ReadData(base, endpoint);
        }
    }

    return CY_USBFS_DEV_DRV_SUCCESS;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_Abort
****************************************************************************//**
*
* Abort operation for data endpoint.
* If there is any bus activity after the abort operation requested, the function
* waits for its completion or a timeout. A timeout is the time to transfer the
* bulk or an interrupt packet of the maximum playload size. If this bus activity is
* a transfer to the aborting endpoint, the received data is lost and the endpoint
* transfer completion callbacks are not invoked.
* After the function returns a new read or write, the endpoint operation can be submitted.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* The data endpoint number.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return
* Data endpoint state \ref cy_en_usb_dev_ep_state_t after abort was applied.
*
* \note
* - This abort operation is not supported for the ISOC endpoints because
*   these endpoints do not have a handshake and are always accessible to the
*   USB Host. Therefore, an abort can cause unexpected behavior.
* - The function uses the critical section to protect from the endpoint transfer
*   complete interrupt.
*
*******************************************************************************/
cy_en_usbfs_dev_drv_status_t Cy_USBFS_Dev_Drv_Abort(USBFS_Type *base,
                                                    uint32_t   endpoint,
                                                    cy_stc_usbfs_dev_drv_context_t *context)
{
    cy_en_usbfs_dev_drv_status_t retStatus = CY_USBFS_DEV_DRV_BAD_PARAM;
    cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData;
    bool flushBuffer = true;
    uint32_t intrState;

    /* Checks if the endpoint is supported by the driver */
    if (false == IS_EP_VALID(endpoint))
    {
        return retStatus;
    }

    endpoint = EP2PHY(endpoint);
    endpointData = &context->epPool[endpoint];

    /* Locks from the context modification by the endpoint completion interrupt */
    intrState = Cy_SysLib_EnterCriticalSection();

    /* Checks whether the endpoint is configured */
    if (CY_USB_DEV_EP_DISABLED == endpointData->state)
    {
        return retStatus;
    }
    else if (CY_USB_DEV_EP_STALLED == endpointData->state)
    {
        /* Aborts a pending transfer if the endpoint is stalled */
        context->epAbortMask |= (uint8_t) EP2MASK(endpoint);
        endpointData->isPending = false;
    }
    else if (CY_USB_DEV_EP_PENDING == endpointData->state)
    {
        bool isocEp = false;

        /* Sets an abort mask to discard the completion events */
        context->epAbortMask |= (uint8_t) EP2MASK(endpoint);
        endpointData->state   = CY_USB_DEV_EP_IDLE;

        /* Clears the bus busy activity */
        (void) Cy_USBFS_Dev_Drv_CheckActivity(base);

        if (endpointData->sieMode == CY_USBFS_DEV_DRV_EP_CR_ACK_IN)
        {
            Cy_USBFS_Dev_Drv_SetSieEpMode(base, endpoint, CY_USBFS_DEV_DRV_EP_CR_NAK_IN);
        }
        else if (endpointData->sieMode == CY_USBFS_DEV_DRV_EP_CR_ACK_OUT)
        {
            Cy_USBFS_Dev_Drv_SetSieEpMode(base, endpoint, CY_USBFS_DEV_DRV_EP_CR_NAK_OUT);
        }
        else
        {
            /* Does not wait for the ISOC endpoint */
            isocEp = true;
        }

        if (false == isocEp)
        {
            /* If there is a bus activity, it could be a transfer to the aborted endpoint */
            if (Cy_USBFS_Dev_Drv_CheckActivity(base))
            {
                /* Releases the lock */
                Cy_SysLib_ExitCriticalSection(intrState);

                uint32_t timeout = WAIT_TRANSFER_COMPLETE;

                /* Waits for BULK or INTERRUPT transfer completion or a NACK interrupt */
                while ( (timeout != 0U) &&
                        (0U != (context->epAbortMask & EP2MASK(endpoint))) )
                {
                    if (false == Cy_USBFS_Dev_Drv_CheckActivity(base))
                    {
                        break;
                    }

                    Cy_SysLib_DelayUs(1U);
                    --timeout;
                }
            }
        }

        /* The abort mask is cleared in the endpoint completion interrupt OR
        *  on a following call of the endpoint Remove, LoadIn or EnableOut function.
        */
    }
    else
    {
        /* Does nothing for all other states: CY_USB_DEV_EP_IDLE or CY_USB_DEV_EP_COMPLETED */
        flushBuffer = false;
        retStatus = CY_USBFS_DEV_DRV_SUCCESS;
    }

    /* Releases the lock */
    Cy_SysLib_ExitCriticalSection(intrState);

    if (flushBuffer)
    {
        bool inDirection = IS_EP_DIR_IN(endpointData->address);

        /* Initializes the pointers to functions that work with the data endpoint */
        switch(context->mode)
        {
            case CY_USBFS_DEV_DRV_EP_MANAGEMENT_CPU:
            case CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA:
            {
                /* IN endpoint: Flushes the buffer to discard the loaded data.
                *  OUT endpoint: Leaves the written data in the buffer.
                */
                if (inDirection)
                {
                    Cy_USBFS_Dev_Drv_FlushInBuffer(base, endpoint);
                }

                retStatus = CY_USBFS_DEV_DRV_SUCCESS;
            }
            break;

            case CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO:
            {
                /* IN endpoint: Flushes the buffer to discard the loaded data.
                *  OUT endpoint: Waits for DMA to complete if a transfer has been started.
                */
                retStatus = DynamicEndpointReConfiguration(base, inDirection, endpoint);
            }
            break;

            default:
                /* Unknown mode */
                break;
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_StallEndpoint
****************************************************************************//**
*
* Configures data endpoint to STALL any request intended for it.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* The data endpoint number.
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
cy_en_usbfs_dev_drv_status_t Cy_USBFS_Dev_Drv_StallEndpoint(USBFS_Type *base,
                                                            uint32_t    endpoint,
                                                            cy_stc_usbfs_dev_drv_context_t *context)
{
    cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData;

    /* Check if endpoint is supported by driver */
    if (false == IS_EP_VALID(endpoint))
    {
        return CY_USBFS_DEV_DRV_BAD_PARAM;
    }

    endpoint = EP2PHY(endpoint);
    endpointData = &context->epPool[endpoint];

    /* Check whether endpoint is configured */
    if (CY_USB_DEV_EP_DISABLED == endpointData->state)
    {
        return CY_USBFS_DEV_DRV_BAD_PARAM;
    }

    /* Store current endpoint state to restore it after Stall clear */
    endpointData->isPending = (CY_USB_DEV_EP_PENDING == endpointData->state);

    /* Stall endpoint */
    Cy_USBFS_Dev_Drv_SetSieEpStall(base, IS_EP_DIR_IN(endpointData->address), endpoint);
    endpointData->state = CY_USB_DEV_EP_STALLED;

    return CY_USBFS_DEV_DRV_SUCCESS;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_UnStallEndpoint
****************************************************************************//**
*
* Release data endpoint STALL condition and clears data toggle bit.
* The endpoint is returned to the same state as it was before STALL request.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* The data endpoint number.
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
cy_en_usbfs_dev_drv_status_t Cy_USBFS_Dev_Drv_UnStallEndpoint(USBFS_Type *base,
                                                              uint32_t    endpoint,
                                                              cy_stc_usbfs_dev_drv_context_t *context)
{
    cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData;

    /* Check whether the endpoint is supported by the driver */
    if (false == IS_EP_VALID(endpoint))
    {
        return CY_USBFS_DEV_DRV_BAD_PARAM;
    }

    endpoint = EP2PHY(endpoint);
    endpointData = &context->epPool[endpoint];

    /* Check whether the endpoint is configured */
    if (CY_USB_DEV_EP_DISABLED == endpointData->state)
    {
        return CY_USBFS_DEV_DRV_BAD_PARAM;
    }

    /* Clear toggle bit */
    endpointData->toggle = 0U;

    if (endpointData->isPending)
    {
        /* Restore pending state */
        endpointData->state = CY_USB_DEV_EP_PENDING;

        /* Clear toggle and enable endpoint to respond to host */
        Cy_USBFS_Dev_Drv_ClearSieEpToggle(base, endpoint);
        Cy_USBFS_Dev_Drv_ClearSieEpStall (base, endpoint, (uint32_t) endpointData->sieMode);
    }
    else
    {
        /* Endpoint is ready for operation */
        context->epPool[endpoint].state = CY_USB_DEV_EP_IDLE;

        /* Set endpoint inactive mode */
        Cy_USBFS_Dev_Drv_ClearSieEpToggle(base, endpoint);
        Cy_USBFS_Dev_Drv_ClearSieEpStall (base, endpoint, GetEndpointInactiveMode((uint32_t) endpointData->sieMode));
    }

    return CY_USBFS_DEV_DRV_SUCCESS;
}

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXUSBFS */


/* [] END OF FILE */
