/**
  *********************************************************************************
  *
  * @file    ald_syscfg.h
  * @brief   SYSCFG module driver.
  *
  * @version V1.0
  * @date    31 Jan. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          31 Jan. 2023    Lisq            The first version
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
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
  **********************************************************************************
  */

#ifndef __ALD_SYSCFG_H__
#define __ALD_SYSCFG_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "ald_utils.h"


/** @addtogroup ALD
  * @{
  */

/** @defgroup SYSCFG SYSCFG
  * @brief SYSCFG module driver
  * @{
  */

/** @defgroup SYSCFG_Public_Macros SYSCFG Public Macros
  * @{
  */
#define SYSCFG_LOCK()       WRITE_REG(SYSCFG->PROT, 0x0U)
#define SYSCFG_UNLOCK()     WRITE_REG(SYSCFG->PROT, 0x55AA6996U)
#define GET_SYSCFG_LOCK()   READ_BIT(SYSCFG->PROT, SYSCFG_PROT_PROT_MSK)

/**
  * @brief PIS IO Select
  */
typedef enum {
    ALD_SYSCFG_PISIOCFG_PA = 0x0U,
    ALD_SYSCFG_PISIOCFG_PB = 0x1U,
    ALD_SYSCFG_PISIOCFG_PC = 0x2U,
    ALD_SYSCFG_PISIOCFG_PD = 0x3U,
} ald_syscfg_pisiocfg_t;
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __ALD_SYSCFG_H__ */
