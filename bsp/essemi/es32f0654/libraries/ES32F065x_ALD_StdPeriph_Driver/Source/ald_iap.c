/**
  *********************************************************************************
  *
  * @file    ald_iap.c
  * @brief   IAP module driver.
  *
  * @version V1.0
  * @date    04 Dec 2017
  * @author  AE Team
  * @note
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
  *
  *********************************************************************************
  */

#include "ald_iap.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup IAP IAP
  * @brief IAP module driver
  * @{
  */
#ifdef ALD_IAP


/** @defgroup IAP_Public_Functions IAP Public Functions
  *
  * @verbatim
  ==============================================================================
              #####  Erase and Program flash functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Erase flash.
      (+) Program flash.

    @endverbatim
  * @{
  */

/**
  * @brief  Erases a specified page.
  * @param  addr: The beginning address of the page to be erased.
  * @retval The result:
  *           - 0: SUCCESS
  *           - 1: ERROR
  */
uint32_t ald_iap_erase_page(uint32_t addr)
{
	uint32_t status;
	IAP_PE iap_pe = (IAP_PE)(*(uint32_t *)IAP_PE_ADDR);

	__disable_irq();
	status = (*iap_pe)(addr);
	__enable_irq();

	return !status;
}

/**
  * @brief  Programs a word at a specified address.
  * @param  addr: Specifies the address to be programmed.
  *         Bit0-1 must be zero.
  * @param  data: Specifies the data to be programmed.
  * @retval The result:
  *           - 0: SUCCESS
  *           - 1: ERROR
  */
uint32_t ald_iap_program_word(uint32_t addr, uint32_t data)
{
	uint32_t status;
	IAP_WP iap_wp = (IAP_WP)(*(uint32_t *)IAP_WP_ADDR);

	if (addr & 0x3)
		return 1;

	__disable_irq();
	status = (*iap_wp)(addr, data);
	__enable_irq();

	return !status;
}

/**
  * @brief  Programs double words at a specified address.
  * @param  addr: Specifies the address to be programmed.
  *         Bit0-1 must be zero.
  * @param  data_l: Specifies the LSB data to be programmed.
  * @param  data_h: Specifies the MSB data to be programmed.
  * @retval The result:
  *           - 0: SUCCESS
  *           - 1: ERROR
  */
uint32_t ald_iap_program_dword(uint32_t addr, uint32_t data_l, uint32_t data_h)
{
	uint32_t status;
	IAP_DWP iap_dwp = (IAP_DWP)(*(uint32_t *)IAP_DWP_ADDR);

	if (addr & 0x3)
		return 1;

	__disable_irq();
	status = (*iap_dwp)(addr, data_l, data_h);
	__enable_irq();

	return !status;
}

/**
  * @brief  Programs datas at a specified address.
  * @param  addr: Specifies the address to be programmed.
  *         Bit0-1 must be zero.
  * @param  data: Specifies the data to be programmed.
  * @param  len: Specifies the data length to be programmed.
  *         Bit0-1 must be zero.
  * @param  erase: Erase page flag before programming.
  * @retval The result:
  *           - 0: SUCCESS
  *           - 1: ERROR
  */
uint32_t ald_iap_program_words(uint32_t addr, uint8_t *data, uint32_t len, uint32_t erase)
{
	uint32_t status;
	IAP_WSP iap_wsp = (IAP_WSP)(*(uint32_t *)IAP_WSP_ADDR);

	if ((addr & 0x3) || (len & 0x3))
		return 1;

	__disable_irq();
	status = (*iap_wsp)(addr, data, len, erase);
	__enable_irq();

	return !status;
}
/**
  * @}
  */
#endif /* ALD_IAP */
/**
  * @}
  */

/**
  * @}
  */
