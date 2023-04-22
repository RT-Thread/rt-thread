/***************************************************************************//**
* \file cy_usbfs_dev_drv_pvt.h
* \version 2.20.3
*
* Provides API declarations of the USBFS driver.
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

/** \cond INTERNAL */

#if !defined(CY_USBFS_DEV_DRV_PVT_H)
#define CY_USBFS_DEV_DRV_PVT_H

#include "cy_usbfs_dev_drv.h"

#if defined (CY_IP_MXUSBFS) && defined (CY_IP_MXPERI)

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
*                              Function Prototypes
*******************************************************************************/

__STATIC_INLINE uint8_t  GetEndpointActiveMode(bool inDirection, uint8_t attributes);
__STATIC_INLINE uint32_t GetEndpointInactiveMode(uint32_t mode);

/* DMA configuration functions */
cy_en_usbfs_dev_drv_status_t DmaInit(cy_stc_usbfs_dev_drv_config_t const *config,
                                     cy_stc_usbfs_dev_drv_context_t      *context);

void DmaDisable(cy_stc_usbfs_dev_drv_context_t *context);

cy_en_usbfs_dev_drv_status_t DmaEndpointInit(USBFS_Type *base,
                                             cy_en_usbfs_dev_drv_ep_management_mode_t mode,
                                             bool useReg16,
                                             cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData);

void DmaOutEndpointRestore(cy_stc_usbfs_dev_drv_endpoint_data_t *endpoint);

cy_en_usbfs_dev_drv_status_t GetEndpointBuffer(uint32_t size,
                                               uint32_t *idx,
                                               cy_stc_usbfs_dev_drv_context_t *context);

/* Endpoint restore functions (driver specific) */
void RestoreEndpointHwBuffer(USBFS_Type *base,
                             cy_en_usbfs_dev_drv_ep_management_mode_t mode,
                             cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData);

void RestoreEndpointRamBuffer(USBFS_Type *base,
                              cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData);

/* Endpoint buffer allocation functions (driver specific) */
cy_en_usbfs_dev_drv_status_t AddEndpointHwBuffer(USBFS_Type *base,
                                                 cy_stc_usb_dev_ep_config_t const *config,
                                                 cy_stc_usbfs_dev_drv_context_t   *context);

cy_en_usbfs_dev_drv_status_t AddEndpointRamBuffer(USBFS_Type *base,
                                                  cy_stc_usb_dev_ep_config_t const *config,
                                                  cy_stc_usbfs_dev_drv_context_t   *context);

/* Endpoint buffer allocation functions (driver specific) */
cy_en_usbfs_dev_drv_status_t LoadInEndpointCpu(USBFS_Type    *base,
                                               uint32_t      endpoint,
                                               uint8_t const *buffer,
                                               uint32_t      size,
                                               cy_stc_usbfs_dev_drv_context_t *context);

cy_en_usbfs_dev_drv_status_t LoadInEndpointDma(USBFS_Type    *base,
                                               uint32_t      endpoint,
                                               uint8_t const *buffer,
                                               uint32_t      size,
                                               cy_stc_usbfs_dev_drv_context_t *context);

cy_en_usbfs_dev_drv_status_t LoadInEndpointDmaAuto(USBFS_Type    *base,
                                                   uint32_t      endpoint,
                                                   uint8_t const *buffer,
                                                   uint32_t      size,
                                                   cy_stc_usbfs_dev_drv_context_t *context);

cy_en_usbfs_dev_drv_status_t ReadOutEndpointCpu(USBFS_Type *base,
                                                uint32_t   endpoint,
                                                uint8_t    *buffer,
                                                uint32_t   size,
                                                uint32_t   *actSize,
                                                           cy_stc_usbfs_dev_drv_context_t *context);

cy_en_usbfs_dev_drv_status_t ReadOutEndpointDma(USBFS_Type *base,
                                                uint32_t   endpoint,
                                                uint8_t    *buffer,
                                                uint32_t   size,
                                                uint32_t   *actSize,
                                                cy_stc_usbfs_dev_drv_context_t *context);

cy_en_usbfs_dev_drv_status_t ReadOutEndpointDmaAuto(USBFS_Type *base,
                                                    uint32_t   endpoint,
                                                    uint8_t    *buffer,
                                                    uint32_t   size,
                                                    uint32_t   *actSize,
                                                    cy_stc_usbfs_dev_drv_context_t *context);

cy_en_usbfs_dev_drv_status_t DynamicEndpointReConfiguration(USBFS_Type *base,
                                                            bool        inDirection,
                                                            uint32_t    endpoint);


/*******************************************************************************
*                              Internal Constants
*******************************************************************************/

/* Endpoint attributes */
#define ENDPOINT_ATTR_MASK    (0x03U)
#define ENDPOINT_TYPE_ISOC    (0x01U)

/* Returns size to access 16-bit registers */
#define GET_SIZE16(size)          (((size) / 2U) + ((size) & 0x01U))

/* Conversion macros */
#define IS_EP_VALID(endpoint)       CY_USBFS_DEV_DRV_IS_EP_VALID(endpoint)
#define EP2PHY(endpoint)            CY_USBFS_DEV_DRV_EP2PHY(endpoint)
#define EP2MASK(endpoint)            CY_USBFS_DEV_DRV_EP2MASK(endpoint)

#define EPADDR2EP(endpointAddr)     CY_USBFS_DEV_DRV_EPADDR2EP(endpointAddr)
#define EPADDR2PHY(endpointAddr)    CY_USBFS_DEV_DRV_EPADDR2PHY(endpointAddr)
#define IS_EP_DIR_IN(endpointAddr)  CY_USBFS_DEV_DRV_IS_EP_DIR_IN(endpointAddr)
#define IS_EP_DIR_OUT(endpointAddr) CY_USBFS_DEV_DRV_IS_EP_DIR_OUT(endpointAddr)

#define IS_EP_ISOC(mode)            ((CY_USBFS_DEV_DRV_EP_CR_ISO_IN  == (mode)) || \
                                     (CY_USBFS_DEV_DRV_EP_CR_ISO_OUT == (mode)))


/*******************************************************************************
*                         In-line Function Implementation
*******************************************************************************/

/*******************************************************************************
* Function Name: GetEndpointActiveMode
****************************************************************************//**
*
* Returns active SIE mode to be written into endpoint control register.
*
* \param inDirection
* True - endpoint direction is IN; False - endpoint direction is OUT.
*
* \param attributes
* The data endpoint type attributes.
*
* \return
* Active SIE mode.
*
*******************************************************************************/
__STATIC_INLINE uint8_t GetEndpointActiveMode(bool inDirection, uint8_t attributes)
{
    uint8_t epMode;

    if (ENDPOINT_TYPE_ISOC == (attributes & ENDPOINT_ATTR_MASK))
    {
        epMode = (inDirection) ? CY_USBFS_DEV_DRV_EP_CR_ISO_IN : CY_USBFS_DEV_DRV_EP_CR_ISO_OUT;
    }
    else
    {
        epMode = (inDirection) ? CY_USBFS_DEV_DRV_EP_CR_ACK_IN : CY_USBFS_DEV_DRV_EP_CR_ACK_OUT;
    }

    return epMode;
}


/*******************************************************************************
* Function Name: GetEndpointInactiveMode
****************************************************************************//**
*
* Returns inactive SIE mode to be written into endpoint control register.
*
* \param mode
* Active SIE mode.
*
* \return
* Inactive SIE mode.
*
*******************************************************************************/
__STATIC_INLINE uint32_t GetEndpointInactiveMode(uint32_t mode)
{
    switch(mode)
    {
    case CY_USBFS_DEV_DRV_EP_CR_ACK_IN:
        mode = CY_USBFS_DEV_DRV_EP_CR_NAK_IN;
        break;

    case CY_USBFS_DEV_DRV_EP_CR_ACK_OUT:
        mode = CY_USBFS_DEV_DRV_EP_CR_NAK_OUT;
        break;

    case CY_USBFS_DEV_DRV_EP_CR_ISO_OUT:
    case CY_USBFS_DEV_DRV_EP_CR_ISO_IN:
        /* Ignore traffic to endpoint. Wait for endpoint load or enable */
        mode = CY_USBFS_DEV_DRV_EP_CR_DISABLE;
        mode = CY_USBFS_DEV_DRV_EP_CR_DISABLE;
        break;

    default:
        /* Unknown mode: disable endpoint */
        mode = CY_USBFS_DEV_DRV_EP_CR_DISABLE;
        break;
    }

    return mode;
}


#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXUSBFS */

#endif /* (CY_USBFS_DEV_DRV_PVT_H) */

/** \endcond */

/* [] END OF FILE */
