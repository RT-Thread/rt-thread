/**
  *********************************************************************************
  *
  * @file    ald_crc.h
  * @brief   Header file of CRC module driver.
  *
  * @version V1.0
  * @date    18 Jun 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          18 Jun 2019     AE Team         The first version
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

#ifndef __ALD_CRC_H__
#define __ALD_CRC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "utils.h"
#include "ald_dma.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup CRC
  * @{
  */

/** @defgroup CRC_Public_Types CRC Public Types
  * @{
  */

/**
  * @brief CRC mode
  */
typedef enum {
	CRC_MODE_CCITT = 0U,	/**< Ccitt */
	CRC_MODE_8     = 1U,	/**< Crc8 */
	CRC_MODE_16    = 2U,	/**< Crc16 */
	CRC_MODE_32    = 3U,	/**< Crc32 */
} crc_mode_t;

/**
  * @brief CRC input length
  */
typedef enum {
	CRC_LEN_AUTO    = 0U,	/**< Auto */
	CRC_DATASIZE_8  = 1U,	/**< Byte */
	CRC_DATASIZE_16 = 2U,	/**< Half word */
	CRC_DATASIZE_32 = 3U,	/**< Word */
} crc_datasize_t;

/**
  * @brief CRC whether write error or no
  */
typedef enum {
	CRC_WERR_NO  = 0U,	/**< No error */
	CRC_WERR_ERR = 1U,	/**< Error */
} crc_werr_t;

/**
  * @brief CRC state structures definition
  */
typedef enum {
	CRC_STATE_RESET = 0x0U,	/**< Peripheral is not initialized */
	CRC_STATE_READY = 0x1U,	/**< Peripheral Initialized and ready for use */
	CRC_STATE_BUSY  = 0x2U,	/**< An internal process is ongoing */
	CRC_STATE_ERROR = 0x4U,	/**< Error */
} crc_state_t;

/**
  * @brief CRC init structure definition
  */
typedef struct {
	crc_mode_t mode;	/**< CRC mode */
	type_func_t data_rev;	/**< CRC data reverse or no */
	type_func_t data_inv;	/**< CRC data inverse or no */
	type_func_t chs_rev; 	/**< CRC check sum reverse or no */
	type_func_t chs_inv; 	/**< CRC check sum inverse or no */
	uint32_t seed;		/**< CRC seed */
} crc_init_t;

/**
  * @brief  CRC Handle Structure definition
  */
typedef struct crc_handle_s {
	CRC_TypeDef *perh;	/**< Register base address */
	crc_init_t init;  	/**< CRC required parameters */
	uint8_t *cal_buf; 	/**< The pointer of preparing buffer */
	uint32_t *cal_res;	/**< The pointer of result */

	dma_handle_t hdma;	/**< CRC DMA handle parameters */

	lock_state_t lock;	/**< Locking object */
	crc_state_t state;	/**< CRC operation state */

	void (*cal_cplt_cbk)(struct crc_handle_s *arg);	/**< Calculate completed callback */
	void (*err_cplt_cbk)(struct crc_handle_s *arg);	/**< Calculate error callback */
} crc_handle_t;
/**
  * @}
  */

/** @defgroup CRC_Public_Macros CRC Public Macros
  * @{
  */
#define CRC_ENABLE(handle)		(SET_BIT((handle)->perh->CR, CRC_CR_EN_MSK))
#define CRC_DISABLE(handle)		(CLEAR_BIT((handle)->perh->CR, CRC_CR_EN_MSK))
#define CRC_RESET(handle)		(SET_BIT((handle)->perh->CR, CRC_CR_RST_MSK))
#define CRC_DMA_ENABLE(handle) 		(SET_BIT((handle)->perh->CR, CRC_CR_DMAEN_MSK))
#define CRC_DMA_DISABLE(handle) 	(CLEAR_BIT((handle)->perh->CR, CRC_CR_DMAEN_MSK))
#define CRC_CLEAR_ERROR_FLAG(handle)	(SET_BIT((handle)->perh->CR, CRC_CR_WERR_MSK))
/**
  * @}
  */

/** @defgroup CRC_Private_Macros   CRC Private Macros
  * @{
  */
#define IS_CRC(x) 	((x) == CRC)
#define IS_CRC_MODE(x) 	(((x) == CRC_MODE_CCITT) || \
			 ((x) == CRC_MODE_8)     || \
			 ((x) == CRC_MODE_16)    || \
			 ((x) == CRC_MODE_32))
/**
  * @}
  */

/** @addtogroup CRC_Public_Functions
  * @{
  */

/** @addtogroup CRC_Public_Functions_Group1
  * @{
  */
ald_status_t ald_crc_init(crc_handle_t *hperh);
void ald_crc_reset(crc_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup CRC_Public_Functions_Group2
  * @{
  */
uint32_t ald_crc_calculate(crc_handle_t *hperh, uint8_t *buf, uint32_t size);
uint32_t ald_crc_calculate_halfword(crc_handle_t *hperh, uint16_t *buf, uint32_t size);
uint32_t ald_crc_calculate_word(crc_handle_t *hperh, uint32_t *buf, uint32_t size);
/**
  * @}
  */


/** @addtogroup CRC_Public_Functions_Group3
  * @{
  */
ald_status_t ald_crc_calculate_by_dma(crc_handle_t *hperh, uint8_t *buf, uint32_t *res, uint16_t size, uint8_t channel);
ald_status_t ald_crc_calculate_halfword_by_dma(crc_handle_t *hperh, uint16_t *buf, uint32_t *res, uint16_t size, uint8_t channel);
ald_status_t ald_crc_calculate_word_by_dma(crc_handle_t *hperh, uint32_t *buf, uint32_t *res, uint16_t size, uint8_t channel);
ald_status_t ald_crc_dma_pause(crc_handle_t *hperh);
ald_status_t ald_crc_dma_resume(crc_handle_t *hperh);
ald_status_t ald_crc_dma_stop(crc_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup CRC_Public_Functions_Group4
  * @{
  */
crc_state_t ald_crc_get_state(crc_handle_t *hperh);
/**
  * @}
  */

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

#endif /* __ALD_CRC_H__ */
