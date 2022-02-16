/**
  *********************************************************************************
  *
  * @file    ald_calc.c
  * @brief   CALC module driver.
  *
  * @version V1.0
  * @date    26 Jun 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          26 Jun 2019     AE Team         The first version
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

#include "ald_conf.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup CALC CALC
  * @brief CALC module driver
  * @{
  */
#ifdef ALD_CALC

/** @defgroup CALC_Public_Functions CALC Public Functions
  * @brief    Accelerating calculate functions
  *
  * @verbatim
  ==============================================================================
              ##### Accelerating calculate functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Square root operation.

    @endverbatim
  * @{
  */

/**
  * @brief  Square root operation.
  * @param  data: The  radicand.
  * @retval The value of square root.
  */
uint32_t ald_calc_sqrt(uint32_t data)
{
	WRITE_REG(CALC->RDCND, data);
	while (READ_BIT(CALC->SQRTSR, CALC_SQRTSR_BUSY_MSK));

	return READ_REG(CALC->SQRTRES);
}
/**
  * @}
  */
#endif /* ALD_CALC */
/**
  * @}
  */
/**
  * @}
  */
