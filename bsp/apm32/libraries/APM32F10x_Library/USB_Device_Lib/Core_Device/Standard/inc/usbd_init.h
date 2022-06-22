/*!
 * @file        usbd_init.h
 *
 * @brief       USB initialization management head file
 *
 * @version     V1.0.0
 *
 * @date        2021-12-06
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#ifndef USBD_INIT_H_
#define USBD_INIT_H_

#include "usbd_core.h"

/**
 * @brief   Endpoint Configuration Info
 */
typedef struct
{
    USBD_EP_T      epNum;      //!< endpoint number
    USBD_EP_TYPE_T epType;     //!< endpoint type
    uint8_t        epKind;     /**
                                * Which could be ENABLE or DISABLE, it is valid only for
                                * control and bulk Endpoint. The mean of ENABLE for them like :
                                * 1. Control endpoint : Only for OUT status which is zero data.
                                * 2. Bulk endpoint : Enable the double-buffer feature
                               */
    USBD_EP_STATUS_T epStatus; //!< Endpoint status
    uint16_t epBufAddr;        //!< buffer address for the endpoint
    uint16_t maxPackSize;      //!< max packet size for the endpoint
} USBD_EPConfig_T;

/** USB init */
void USBD_Init(USBD_InitParam_T *param);
void USBD_InitParamStructInit(USBD_InitParam_T *param);

/** power */
void USBD_PowerOn(void);
void USBD_PowerOff(void);

/** Endpoint init */
void USBD_OpenOutEP(USBD_EPConfig_T *epConfig);
void USBD_OpenInEP(USBD_EPConfig_T *epConfig);

void USBD_CloseOutEP(USBD_EP_T ep);
void USBD_CloseInEP(USBD_EP_T ep);

#endif
