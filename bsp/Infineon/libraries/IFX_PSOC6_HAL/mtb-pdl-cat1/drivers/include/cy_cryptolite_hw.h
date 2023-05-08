/***************************************************************************//**
* \file cy_cryptolite_hw.h
* \version 2.0
*
* \brief
*  This file provides common constants and macros
*  for the Cryptolite driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/
#if !defined (CY_CRYPTOLITE_HW_H)
#define CY_CRYPTOLITE_HW_H

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTOLITE)

#if defined(__cplusplus)
extern "C" {
#endif

#include "ip/cyip_cryptolite.h"

#define REG_CRYPTOLITE_CTL(base)                         (((CRYPTOLITE_Type*)(base))->CTL)
#define REG_CRYPTOLITE_STATUS(base)                      (((CRYPTOLITE_Type*)(base))->STATUS)
#define REG_CRYPTOLITE_SHA_DESCR(base)                   (((CRYPTOLITE_Type*)(base))->SHA_DESCR)
#define REG_CRYPTOLITE_SHA_INTR_ERROR(base)              (((CRYPTOLITE_Type*)(base))->INTR_ERROR)
#define REG_CRYPTOLITE_SHA_INTR_ERROR_SET(base)          (((CRYPTOLITE_Type*)(base))->INTR_ERROR_SET)
#define REG_CRYPTOLITE_SHA_INTR_ERROR_MASK(base)         (((CRYPTOLITE_Type*)(base))->INTR_ERROR_MASK)
#define REG_CRYPTOLITE_SHA_INTR_ERROR_MASKED(base)       (((CRYPTOLITE_Type*)(base))->INTR_ERROR_MASKED)

#define REG_CRYPTOLITE_DESCR(base)                      (((CRYPTOLITE_Type*)(base))->SHA_DESCR)
#define REG_CRYPTOLITE_INTR_ERROR(base)                 (((CRYPTOLITE_Type*)(base))->INTR_ERROR)
#define REG_CRYPTOLITE_INTR_ERROR_SET(base)             (((CRYPTOLITE_Type*)(base))->INTR_ERROR_SET)
#define REG_CRYPTOLITE_INTR_ERROR_MASK(base)            (((CRYPTOLITE_Type*)(base))->INTR_ERROR_MASK)
#define REG_CRYPTOLITE_INTR_ERROR_MASKED(base)          (((CRYPTOLITE_Type*)(base))->INTR_ERROR_MASKED)

#define CY_CRYPTOLITE_MSG_SCH_CTLWD                      ((uint32_t)(0UL << 28UL))
#define CY_CRYPTOLITE_PROCESS_CTLWD                      ((uint32_t)(1UL << 28UL))
/*bus error interrupt mask*/
#define CY_CRYPTOLITE_INTR_BUS_ERROR_MASK                ((uint32_t)CRYPTOLITE_INTR_ERROR_BUS_ERROR_Msk)

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTOLITE */

#endif /* #if !defined (CY_CRYPTOLITE_HW_H) */
