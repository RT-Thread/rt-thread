/**************************************************************************//**
 * @file     cmsis_xcc.h
 * @brief    CMSIS DSP Core Peripheral Access Layer Header File
 * @version  V1.0
 * @date     20. January 2019
 ******************************************************************************/
/*
 * Copyright (c) 2009-2019 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __CORE_DSP_H_GENERIC
#define __CORE_DSP_H_GENERIC

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

/* IO definitions (access restrictions to peripheral registers) */
/**
    \defgroup CMSIS_glob_defs CMSIS Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.
*/
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

#define __STATIC_INLINE static inline

#define __BKPT(value) do {} while(0)
#define __NOP() do {} while(0)

#define NVIC_SetPriorityGrouping(value) do {} while(0)
#define NVIC_GetPriorityGrouping() do {} while(0)
#define NVIC_EnableIRQ(value) do {} while(0)
#define NVIC_GetEnableIRQ(value) do {} while(0)
#define NVIC_DisableIRQ(value) do {} while(0)
#define NVIC_GetPendingIRQ(value) do {} while(0)
#define NVIC_SetPendingIRQ(value) do {} while(0)
#define NVIC_ClearPendingIRQ(value) do {} while(0)
#define NVIC_GetActive(value) do {} while(0)

#ifdef __cplusplus
}
#endif

#endif /* __CORE_DSP_H_GENERIC */
