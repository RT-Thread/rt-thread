/**
  *********************************************************************************
  *
  * @file    ald_crypt.h
  * @brief   Header file of CRYPT module driver.
  *
  * @version V1.0
  * @date    19 Jun 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
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
  * @brief CRYPT aes key select
  */
typedef enum {
	CRYPT_BITS_128 = 0U,	/**< 128bit key for aes */
	CRYPT_BITS_192 = 1U,	/**< 192bit key for aes */
	CRYPT_BITS_256 = 2U,	/**< 256bit key for aes */
} crypt_aesks_t;

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
  * @brief CRYPT des key select
  */
typedef enum {
	CRYPT_KEYS_2 = 0U,	/**< 2 key for des */
	CRYPT_KEYS_3 = 1U,	/**< 3 key for des */
	CRYPT_KEYS_1 = 2U,	/**< 1 key for des */
} crypt_desks_t;

/**
  * @brief CRYPT crypt select
  */
typedef enum {
	CRYPT_CRYSEL_AES = 0U,	/**< AES */
	CRYPT_CRYSEL_DES = 1U,	/**< DES */
} crypt_crysel_t;

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
	CRYPT_FLAG_DESIF = 0x2U,  	/**< Des flag */
	CRYPT_FLAG_DONE  = 0x100U,	/**< Complete flag */
} crypt_flag_t;

/**
  * @brief CRYPT key select
  */
typedef enum {
	CRYPT_AES_BITS_128 = 0x4U,	/**< 128bit key of aes */
	CRYPT_AES_BITS_192 = 0x6U,	/**< 192bit key of aes */
	CRYPT_AES_BITS_256 = 0x8U,	/**< 192bit key of ase */
	CRYPT_DES_KEYS_1   = 0x12U,	/**< 1 key of des */
	CRYPT_DES_KEYS_2   = 0x14U,	/**< 2 key of des */
	CRYPT_DES_KEYS_3   = 0x16U,	/**< 3 key of des */
} crypt_ks_t;

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
  * @brief CRYPT key length
  */
typedef enum {
	KEY_2_LEN = 2U,	/**< Key's lenth is 2 */
	KEY_4_LEN = 4U,	/**< Key's lenth is 4 */
	KEY_6_LEN = 6U,	/**< Key's lenth is 6 */
	KEY_8_LEN = 8U,	/**< Key's lenth is 8 */
} crypt_key_len_t;

/**
  * @brief CRYPT iv length
  */
typedef enum {
	IV_2_LEN = 2U,	/**< iv's lenth is 2 */
	IV_4_LEN = 4U,	/**< iv's lenth is 4 */
} crypt_ivr_len_t;

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
	crypt_ks_t key;		/**< Key select */
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
	uint32_t step;       	/**< The step of once crypt 2(des) or 4(aes) */
	uint32_t dir;        	/**< ENCRYPT or DECRYPT */
	uint32_t iv[4];     	/**< The iv of crypt */
	uint32_t iv_size;	/**< The iv size */
	uint32_t key[8];     	/**< The key of crypt */
	uint32_t key_size;	/**< The key size */
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
#define IS_CRYPT_KS(x) 		(((x) == CRYPT_AES_BITS_128) || \
				 ((x) == CRYPT_AES_BITS_192) || \
				 ((x) == CRYPT_AES_BITS_256) || \
				 ((x) == CRYPT_DES_KEYS_1)   || \
				 ((x) == CRYPT_DES_KEYS_2)   || \
				 ((x) == CRYPT_DES_KEYS_3))
#define IS_CRYPT_IT(x)		((x) == CRYPT_IT_IT)
#define IS_CRYPT_FLAG(x) 	(((x) == CRYPT_FLAG_AESIF) || \
				 ((x) == CRYPT_FLAG_DESIF) || \
				 ((x) == CRYPT_FLAG_DONE))
#define IS_CRYPT_IV_LEN(x)	(((x) == IV_2_LEN) || \
				 ((x) == IV_4_LEN))
#define IS_CRYPT_KEY_LEN(x)	(((x) == KEY_2_LEN) || \
				 ((x) == KEY_4_LEN) || \
				 ((x) == KEY_6_LEN) || \
				 ((x) == KEY_8_LEN))
/**
  * @}
  */

/** @addtogroup CRYPT_Public_Functions
  * @{
  */

/** @addtogroup CRYPT_Public_Functions_Group1
  * @{
  */
extern ald_status_t ald_crypt_init(crypt_handle_t *hperh);
extern ald_status_t ald_crypt_write_key(crypt_handle_t *hperh, uint32_t * key, crypt_key_len_t len);
extern ald_status_t ald_crypt_read_key(crypt_handle_t *hperh, uint32_t * key, crypt_key_len_t len);
extern ald_status_t ald_crypt_write_ivr(crypt_handle_t *hperh, uint32_t * iv, crypt_ivr_len_t len);
extern ald_status_t ald_crypt_read_ivr(crypt_handle_t *hperh, uint32_t * iv, crypt_ivr_len_t len);
/**
  * @}
  */

/** @addtogroup CRYPT_Public_Functions_Group2
  * @{
  */
extern ald_status_t ald_crypt_encrypt(crypt_handle_t *hperh, uint8_t * plain_text, uint8_t * cipher_text, uint32_t size);
extern ald_status_t ald_crypt_decrypt(crypt_handle_t *hperh, uint8_t * cipher_text, uint8_t * plain_text, uint32_t size);
extern ald_status_t ald_crypt_gcm_verify(crypt_handle_t *hperh, uint8_t *cipher_text, uint32_t size, uint8_t *aadata, uint32_t alen, uint8_t *tag);
extern ald_status_t ald_crypt_encrypt_by_it(crypt_handle_t *hperh, uint8_t *plain_text, uint8_t *cipher_text, uint32_t size);
extern ald_status_t ald_crypt_decrypt_by_it(crypt_handle_t *hperh, uint8_t *cipher_text, uint8_t *plain_text, uint32_t size);
#ifdef ALD_DMA
extern ald_status_t ald_crypt_encrypt_by_dma(crypt_handle_t *hperh, uint8_t * plain_text,
             uint8_t *cipher_text, uint32_t size, uint8_t channel_m2p, uint8_t channel_p2m);
extern ald_status_t ald_crypt_decrypt_by_dma(crypt_handle_t *hperh, uint8_t * cipher_text,
               uint8_t *plain_text, uint32_t size, uint8_t channel_m2p, uint8_t channel_p2m);
#endif
/**
  * @}
  */

/** @addtogroup CRYPT_Public_Functions_Group3
  * @{
  */
#ifdef ALD_DMA
extern ald_status_t ald_crypt_dma_pause(crypt_handle_t *hperh);
extern ald_status_t ald_crypt_dma_resume(crypt_handle_t *hperh);
extern ald_status_t ald_crypt_dma_stop(crypt_handle_t *hperh);
#endif
extern void ald_crypt_irq_handler(crypt_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup CRYPT_Public_Functions_Group4
  * @{
  */
extern void ald_crypt_interrupt_config(crypt_handle_t *hperh, crypt_it_t it, type_func_t state);
extern flag_status_t ald_crypt_get_flag_status(crypt_handle_t *hperh, crypt_flag_t flag);
extern void ald_crypt_clear_flag_status(crypt_handle_t *hperh, crypt_flag_t flag);
extern it_status_t ald_crypt_get_it_status(crypt_handle_t *hperh, crypt_it_t it);
/**
  * @}
  */

/** @addtogroup CRYPT_Public_Functions_Group5
  * @{
  */
extern crypt_state_t ald_crypt_get_state(crypt_handle_t *hperh);
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
