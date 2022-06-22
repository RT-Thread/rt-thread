/**
  *********************************************************************************
  *
  * @file    ald_crypt.h
  * @brief   Header file of CRYPT module driver.
  *
  * @version V1.0
  * @date    7 Dec 2017
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

#ifndef __ALD_CRYPT_H__
#define __ALD_CRYPT_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "utils.h"
#include "ald_dma.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup CRYPT
  * @{
  */

/** @defgroup CRYPT_Public_Types CRYPT Public Types
  * @{
  */

/**
  * @brief CRYPT encrypt or decrypt select
  */
typedef enum {
	CRYPT_DECRYPT = 0U,	/**< Decrypt */
	CRYPT_ENCRYPT = 1U,	/**< Encrypt */
} crypt_encs_t;

/**
  * @brief CRYPT mode select
  */
typedef enum {
	CRYPT_MODE_ECB = 0U,	/**< ECB */
	CRYPT_MODE_CBC = 1U,	/**< CBC */
	CRYPT_MODE_CTR = 2U,	/**< CTR */
} crypt_mode_t;

/**
  * @brief CRYPT data type
  */
typedef enum {
	CRYPT_DATA_CHANGE_NO = 0U,	/**< No exchange */
	CRYPT_DATA_CHANGE_16 = 1U,	/**< 16bit exchange */
	CRYPT_DATA_CHANGE_8  = 2U,	/**< 8bit exchange */
	CRYPT_DATA_CHANGE_1  = 3U,	/**< 1bit exchange */
} crypt_datatype_t;

/**
  * @brief CRYPT interrupt
  */
typedef enum {
	CRYPT_IT_IT = 0x80U,	/**< Interrupt */
} crypt_it_t;

/**
  * @brief CRYPT interrupt flag
  */
typedef enum {
	CRYPT_FLAG_AESIF = 0x1U,  	/**< Aes flag */
	CRYPT_FLAG_DONE  = 0x100U,	/**< Complete flag */
} crypt_flag_t;

/**
  * @brief CRYPT state structures definition
  */
typedef enum {
	CRYPT_STATE_RESET = 0x0U,	/**< Peripheral is not initialized */
	CRYPT_STATE_READY = 0x1U,	/**< Peripheral Initialized and ready for use */
	CRYPT_STATE_BUSY  = 0x2U,	/**< An internal process is ongoing */
	CRYPT_STATE_ERROR = 0x4U,	/**< Error */
} crypt_state_t;

/**
  * @brief CRYPT data type
  */
typedef enum {
	DATA_32_BIT = 0U,	/**< 32 bit data,don't swap */
	DATA_16_BIT = 1U,	/**< 16 bit data,swap */
	DATA_8_BIT  = 2U,	/**< 8 bit data,swap */
	DATA_1_BIT  = 3U,	/**< 1 bit data, swap */
} crypt_data_t;

/**
  * @brief CRYPT init structure definition
  */
typedef struct {
	crypt_mode_t mode;    	/**< Crypt mode */
	crypt_data_t type;    	/**< Data type select */
} crypt_init_t;

/**
  * @brief  CRYPT Handle Structure definition
  */
typedef struct crypt_handle_s {
	CRYPT_TypeDef *perh;	/**< Register base address */
	crypt_init_t init;  	/**< CRYPT required parameters */
#ifdef ALD_DMA
	dma_handle_t hdma_m2p;	/**< CRYPT DMA handle parameters memory to crypt module */
	dma_handle_t hdma_p2m;	/**< CRYPT DMA handle parameters crypt module to memory */
#endif
	uint8_t *plain_text; 	/**< Pointer to plain text */
	uint8_t *cipher_text;	/**< Pointer to cipher text */
	uint32_t size;       	/**< The size of crypt data buf */
	uint32_t count;      	/**< The count of crypt data buf */
	uint32_t step;       	/**< The step of once crypt 4(aes) */
	uint32_t dir;        	/**< ENCRYPT or DECRYPT */
	uint32_t iv[4];     	/**< The iv of crypt */
	uint32_t key[4];     	/**< The key of crypt */
	lock_state_t lock;   	/**< Locking object */
	crypt_state_t state; 	/**< CRYPT operation state */

	void (*crypt_cplt_cbk)(struct crypt_handle_s *arg);	/**< Crypt completed callback */
	void (*err_cplt_cbk)(struct crypt_handle_s *arg);  	/**< Crypt error callback */
} crypt_handle_t;
/**
  * @}
  */

/** @defgroup CRYPT_Public_Macros CRYPT Public Macros
  * @{
  */
#define CRYPT_GO(handle) 		(SET_BIT((handle)->perh->CON, CRYPT_CON_GO_MSK))
#define CRYPT_FIFOEN_ENABLE(handle) 	(SET_BIT((handle)->perh->CON, CRYPT_CON_FIFOEN_MSK))
#define CRYPT_FIFOEN_DISABLE(handle) 	(CLEAR_BIT((handle)->perh->CON, CRYPT_CON_FIFOEN_MSK))
#define CRYPT_IVEN_ENABLE(handle) 	(SET_BIT((handle)->perh->CON, CRYPT_CON_IVEN_MSK))
#define CRYPT_IVEN_DISABLE(handle) 	(CLEAR_BIT((handle)->perh->CON, CRYPT_CON_IVEN_MSK))
#define CRYPT_IE_ENABLE(handle)		(SET_BIT((handle)->perh->CON, CRYPT_CON_IE_MSK))
#define CRYPT_IE_DISABLE(handle)	(CLEAR_BIT((handle)->perh->CON, CRYPT_CON_IE_MSK))
#define CRYPT_DMA_ENABLE(handle)	(SET_BIT((handle)->perh->CON, CRYPT_CON_DMAEN_MSK))
#define CRYPT_DMA_DISABLE(handle)	(CLEAR_BIT((handle)->perh->CON, CRYPT_CON_DMAEN_MSK))
#define CRYPT_SETDIR(handle, dir)	do {(handle)->perh->CON &= ~(0x1 << CRYPT_CON_ENCS_POS);	\
					   (handle)->perh->CON |= (dir << CRYPT_CON_ENCS_POS);} while (0)
#define CRYPT_WRITE_FIFO(handle, data)  ((handle)->perh->FIFO = (data))
#define CRYPT_READ_FIFO(handle)		((handle)->perh->FIFO)
/**
  * @}
  */

/** @defgroup CRYPT_Private_Macros   CRYPT Private Macros
  * @{
  */
#define IS_CRYPT(x)		((x) == CRYPT)
#define IS_CRYPT_MODE(x) 	(((x) == CRYPT_MODE_ECB) ||   \
				 ((x) == CRYPT_MODE_CBC) ||   \
				 ((x) == CRYPT_MODE_CTR))
#define IS_CRYPT_IT(x)		((x) == CRYPT_IT_IT)
#define IS_CRYPT_FLAG(x) 	(((x) == CRYPT_FLAG_AESIF) || \
				 ((x) == CRYPT_FLAG_DONE))
#define IS_CRYPT_IV_LEN(x)	(((x) == IV_2_LEN) || \
				 ((x) == IV_4_LEN))
/**
  * @}
  */

/** @addtogroup CRYPT_Public_Functions
  * @{
  */

/** @addtogroup CRYPT_Public_Functions_Group1
  * @{
  */
ald_status_t ald_crypt_init(crypt_handle_t *hperh);
ald_status_t ald_crypt_write_key(crypt_handle_t *hperh, uint32_t *key);
ald_status_t ald_crypt_read_key(crypt_handle_t *hperh, uint32_t *key);
ald_status_t ald_crypt_write_ivr(crypt_handle_t *hperh, uint32_t *iv);
ald_status_t ald_crypt_read_ivr(crypt_handle_t *hperh, uint32_t *iv);
/**
  * @}
  */

/** @addtogroup CRYPT_Public_Functions_Group2
  * @{
  */
ald_status_t ald_crypt_encrypt(crypt_handle_t *hperh, uint8_t *plain_text, uint8_t *cipher_text, uint32_t size);
ald_status_t ald_crypt_decrypt(crypt_handle_t *hperh, uint8_t *cipher_text, uint8_t *plain_text, uint32_t size);
ald_status_t ald_crypt_gcm_verify(crypt_handle_t *hperh, uint8_t *cipher_text, uint32_t size, uint8_t *aadata, uint32_t alen, uint8_t *tag);
ald_status_t ald_crypt_encrypt_by_it(crypt_handle_t *hperh, uint8_t *plain_text, uint8_t *cipher_text, uint32_t size);
ald_status_t ald_crypt_decrypt_by_it(crypt_handle_t *hperh, uint8_t *cipher_text, uint8_t *plain_text, uint32_t size);
#ifdef ALD_DMA
ald_status_t ald_crypt_encrypt_by_dma(crypt_handle_t *hperh, uint8_t *plain_text,
             uint8_t *cipher_text, uint32_t size, uint8_t channel_m2p, uint8_t channel_p2m);
ald_status_t ald_crypt_decrypt_by_dma(crypt_handle_t *hperh, uint8_t *cipher_text,
               uint8_t *plain_text, uint32_t size, uint8_t channel_m2p, uint8_t channel_p2m);
#endif
/**
  * @}
  */

/** @addtogroup CRYPT_Public_Functions_Group3
  * @{
  */
#ifdef ALD_DMA
ald_status_t ald_crypt_dma_pause(crypt_handle_t *hperh);
ald_status_t ald_crypt_dma_resume(crypt_handle_t *hperh);
ald_status_t ald_crypt_dma_stop(crypt_handle_t *hperh);
#endif
void ald_crypt_irq_handler(crypt_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup CRYPT_Public_Functions_Group4
  * @{
  */
void ald_crypt_interrupt_config(crypt_handle_t *hperh, crypt_it_t it, type_func_t state);
flag_status_t ald_crypt_get_flag_status(crypt_handle_t *hperh, crypt_flag_t flag);
void ald_crypt_clear_flag_status(crypt_handle_t *hperh, crypt_flag_t flag);
it_status_t ald_crypt_get_it_status(crypt_handle_t *hperh, crypt_it_t it);
/**
  * @}
  */

/** @addtogroup CRYPT_Public_Functions_Group5
  * @{
  */
crypt_state_t ald_crypt_get_state(crypt_handle_t *hperh);
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

#endif
