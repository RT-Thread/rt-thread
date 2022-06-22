/**
  *********************************************************************************
  *
  * @file    ald_sram.h
  * @brief   Header file of EBI_SRAM driver
  *
  * @version V1.0
  * @date    07 Dec 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          07 Dec 2019     AE Team         The first version
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

#ifndef __ALD_SRAM_H__
#define __ALD_SRAM_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "ald_ebi.h"
#include "ald_dma.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup SRAM
  * @{
  */

/** @defgroup SRAM_Public_Types SRAM Public Types
  * @{
  */

/** 
  * @brief  ALD SRAM State structures definition  
  */ 
typedef enum {
	ALD_SRAM_STATE_RESET     = 0x00U,	/**< SRAM not yet initialized or disabled */
	ALD_SRAM_STATE_READY     = 0x01U,	/**< SRAM initialized and ready for use */
	ALD_SRAM_STATE_BUSY      = 0x02U,	/**< SRAM internal process is ongoing */
	ALD_SRAM_STATE_ERROR     = 0x03U,	/**< SRAM error state */
	ALD_SRAM_STATE_PROTECTED = 0x04U	/**< SRAM peripheral NORSRAM device write protected */
} ald_sram_state_t;

/** 
  * @brief  SRAM handle Structure definition  
  */ 
typedef struct {
	EBI_NOR_SRAM_TypeDef *instance;		/**< Register base address */ 
	EBI_NOR_SRAM_EXTENDED_TypeDef *ext;	/**< Extended mode register base address */
	ald_ebi_nor_sram_init_t init;		/**< SRAM device control configuration parameters */
	lock_state_t lock;			/**< SRAM locking object */ 
	__IO ald_sram_state_t state;		/**< SRAM device access state */

	dma_handle_t hdma;			/**< SRAM DMA Handle parameters */
	void(*cplt_cbk)(void *arg);             /**< DMA transmit completely callback function */

} sram_handle_t;
/**
  * @}
  */

/** @addtogroup SRAM_Public_Functions
  * @{
  */
/** @addtogroup SRAM_Public_Functions_Group1
  * @{
  */
/* Initialization functions */  
ald_status_t ald_sram_init(sram_handle_t *hperh, ald_ebi_nor_sram_timing_t *timing, ald_ebi_nor_sram_timing_t *ext_timing);
ald_status_t  ald_sram_deinit(sram_handle_t *hperh);
/**
  * @}
  */
/** @addtogroup SRAM_Public_Functions_Group2
  * @{
  */
/* I/O operation functions */
ald_status_t ald_sram_read_8b(sram_handle_t *hperh, uint32_t *addr, uint8_t *buf, uint32_t size);
ald_status_t ald_sram_write_8b(sram_handle_t *hperh, uint32_t *addr, uint8_t *buf, uint32_t size);
ald_status_t ald_sram_read_16b(sram_handle_t *hperh, uint32_t *addr, uint16_t *buf, uint32_t size);
ald_status_t ald_sram_write_16b(sram_handle_t *hperh, uint32_t *addr, uint16_t *buf, uint32_t size);
ald_status_t ald_sram_read_32b(sram_handle_t *hperh, uint32_t *addr, uint32_t *buf, uint32_t size);
ald_status_t ald_sram_write_32b(sram_handle_t *hperh, uint32_t *addr, uint32_t *buf, uint32_t size);
#ifdef ALD_DMA
ald_status_t ald_sram_read_by_dma(sram_handle_t *hperh, uint16_t *addr, uint16_t *buf, uint16_t size, uint8_t ch);
ald_status_t ald_sram_write_by_dma(sram_handle_t *hperh, uint16_t *addr, uint16_t *buf, uint16_t size, uint8_t ch);
#endif
/**
  * @}
  */
/** @addtogroup SRAM_Public_Functions_Group3
  * @{
  */
/* Control functions */
ald_status_t ald_sram_write_enable(sram_handle_t *hperh);
ald_status_t ald_sram_write_disable(sram_handle_t *hperh);
/**
  * @}
  */
/** @addtogroup SRAM_Public_Functions_Group4
  * @{
  */
/* State functions */
ald_sram_state_t ald_sram_get_state(sram_handle_t *hperh);
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
#endif  /* __ALD_SRAM_H__ */
