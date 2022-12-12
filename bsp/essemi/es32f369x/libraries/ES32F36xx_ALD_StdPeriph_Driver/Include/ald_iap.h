/**
  *********************************************************************************
  *
  * @file    ald_iap.h
  * @brief   Header file of IAP module driver.
  *
  * @version V1.0
  * @date    04 Dec 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          04 Dec 2019     AE Team         The first version
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

#ifndef __ALD_IAP_H__
#define __ALD_IAP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup IAP
  * @{
  */

/**
  * @defgroup IAP_Private_Macros IAP Private Macros
  * @{
  */
#define IAP_WSP_ADDR	    0x10000000U
#define IAP_PE_ADDR	    0x10000004U
#define IAP_WP_ADDR	    0x10000008U
#define IAP_DWP_ADDR	    0x1000000cU
#define IAP_WordsProgram_DF 0x10000010U
#define IAP_PageErase_DF    0x10000014U
#define IAP_WordProgram_DF  0x10000018U
#define IAP_DWordProgram_DF 0x1000001cU
/**
  * @}
  */

/** @defgroup IAP_Private_Types IAP Private Types
  * @{
  */
typedef uint32_t (*IAP_PE)(uint32_t addr);
typedef uint32_t (*IAP_WP)(uint32_t addr, uint32_t data);
typedef uint32_t (*IAP_DWP)(uint32_t addr, uint32_t data_l, uint32_t data_h);
typedef uint32_t (*IAP_WSP)(uint32_t addr, uint8_t *data, uint32_t len, uint32_t erase);
/**
  * @}
  */

/** @addtogroup IAP_Public_Functions
  * @{
  */
uint32_t ald_iap_erase_page(uint32_t addr);
uint32_t ald_iap_program_word(uint32_t addr, uint32_t data);
uint32_t ald_iap_program_dword(uint32_t addr, uint32_t data_l, uint32_t data_h);
uint32_t ald_iap_program_words(uint32_t addr, uint8_t *data, uint32_t len, uint32_t erase);
uint32_t ald_iap_erase_page_df(uint32_t addr);
uint32_t ald_iap_program_word_df(uint32_t addr, uint32_t data);
uint32_t ald_iap_program_dword_df(uint32_t addr, uint32_t data_l, uint32_t data_h);
uint32_t ald_iap_program_words_df(uint32_t addr, uint8_t *data, uint32_t len, uint32_t erase);
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
#endif

#endif /* __ALD_IAP_H__ */
