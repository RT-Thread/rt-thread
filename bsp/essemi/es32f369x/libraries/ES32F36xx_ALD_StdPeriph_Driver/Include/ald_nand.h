/**
  *********************************************************************************
  *
  * @file    ald_nand.h
  * @brief   Header file of EBI_NAND module driver
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

#ifndef __ALD_NAND_H_
#define __ALD_NAND_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "ald_ebi.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup NAND 
  * @{
  */

/** @defgroup NAND_Public_Types NAND Public Types
  * @{
  */

/** 
  * @brief NAND State structures definition
  */
typedef enum {
	ALD_NAND_STATE_RESET = 0x00U,	/**< NAND not yet initialized or disabled */
	ALD_NAND_STATE_READY = 0x01U,	/**< NAND initialized and ready for use */
	ALD_NAND_STATE_BUSY  = 0x02U,	/**< NAND internal process is ongoing */
	ALD_NAND_STATE_ERROR = 0x03U	/**< NAND error state */
} ald_nand_state_t;

/** 
  * @brief  NAND Memory electronic signature Structure definition
  */
typedef struct {
	uint8_t maker_id;	/**< Maker id */
	uint8_t device_id;	/**< Device id */
	uint8_t third_id;	/**< Third id */
	uint8_t fourth_id;	/**< Fourth id */
} nand_id_t;

/** 
  * @brief  NAND Memory address Structure definition
  */
typedef struct
{
	uint16_t page;	/**< NAND memory Page address */
	uint16_t plane;	/**< NAND memory Plane address */	
	uint16_t block;	/**< NAND memory Block address */
} nand_address_t;

/** 
  * @brief  NAND Memory info Structure definition
  */ 
typedef struct
{
	uint32_t page_size;	/**< NAND memory page (without spare area) size measured in bytes */
	uint32_t spare_size;	/**< NAND memory spare area size measured in bytes */
	uint32_t block_size;	/**< NAND memory block size measured in number of pages */
	uint32_t block_nbr;     /**< NAND memory number of total block */
	uint32_t plane_nbr;	/**< NAND memory number of planes */	
	uint32_t plane_size;	/**< NAND memory plane size measured in number of blocks */
	type_func_t extra_cmd;	/**< NAND extra command needed for Page reading mode */                                        
} nand_device_cfg_t;

/** 
  * @brief  NAND handle Structure definition
  */   
typedef struct
{
	EBI_NAND_TypeDef *instance;	/**< Register base address */
	ald_ebi_nand_init_t init;	/**< NAND device control configuration parameters */
	lock_state_t lock;		/**< NAND locking object */
	__IO ald_nand_state_t state;	/**< NAND device access state */
	nand_device_cfg_t config;	/**< NAND phusical characteristic information structure */	
} nand_handle_t;

/**
  * @}
  */

/**
  * @defgroup Nand_Private_Constants Nand Private Constants
  * @{
  */

#define NAND_DEVICE1               EBI_BANK2
#define NAND_DEVICE2               EBI_BANK3
#define NAND_WRITE_TIMEOUT         1000U
#define CMD_AREA                   (1U<<16U)	/* A16 = CLE high */
#define ADDR_AREA                  (1U<<17U)	/* A17 = ALE high */
#define NAND_CMD_AREA_A            ((uint8_t)0x00U)
#define NAND_CMD_AREA_B            ((uint8_t)0x01U)
#define NAND_CMD_AREA_C            ((uint8_t)0x50U)
#define NAND_CMD_AREA_TRUE1        ((uint8_t)0x30U)
#define NAND_CMD_WRITE0            ((uint8_t)0x80U)
#define NAND_CMD_WRITE_TRUE1       ((uint8_t)0x10U)
#define NAND_CMD_ERASE0            ((uint8_t)0x60U)
#define NAND_CMD_ERASE1            ((uint8_t)0xD0U)
#define NAND_CMD_READID            ((uint8_t)0x90U)
#define NAND_CMD_STATUS            ((uint8_t)0x70U)
#define NAND_CMD_LOCK_STATUS       ((uint8_t)0x7AU)
#define NAND_CMD_RESET             ((uint8_t)0xFFU)
/* NAND memory status */
#define NAND_VALID_ADDRESS         0x00000100U
#define NAND_INVALID_ADDRESS       0x00000200U
#define NAND_TIMEOUT_ERROR         0x00000400U
#define NAND_BUSY                  0x00000000U
#define NAND_ERROR                 0x00000001U
#define NAND_READY                 0x00000040U
/**
  * @}
  */

/** @defgroup Nand_Private_Macros Nand Private Macros
  * @{
  */
#define ARRAY_ADDRESS(x , y)	((x)->page +   \
		(((x)->block + (((x)->plane) * \
		((y)->config.plane_size))) * ((y)->config.block_size)))
#define COLUMN_ADDRESS( x)	((x)->config.page_size)
#define ADDR_1ST_CYCLE(x)	(uint8_t)(x)		/* 1st addressing cycle */
#define ADDR_2ND_CYCLE(x)	(uint8_t)((x) >> 8U)	/* 2nd addressing cycle */
#define ADDR_3RD_CYCLE(x)	(uint8_t)((x) >> 16U)	/* 3rd addressing cycle */
#define ADDR_4TH_CYCLE(x)	(uint8_t)((x) >> 24U)	/* 4th addressing cycle */
#define COLUMN_1ST_CYCLE(x)	(uint8_t)(x)		/* 1st Column addressing cycle */
#define COLUMN_2ND_CYCLE(x)	(uint8_t)((x) >> 8U)	/* 2nd Column addressing cycle */
/**
  * @}
  */

/** @addtogroup Nand_Public_Functions
 *  @{
 */
/** @addtogroup Nand_Public_Functions_Group1
 *  @{
 */
/* Initialization/de-initialization functions */
ald_status_t ald_nand_init(nand_handle_t *hperh, ald_ebi_nand_timing_t *ctiming, ald_ebi_nand_timing_t *atiming);
ald_status_t ald_nand_deinit(nand_handle_t *hperh);
ald_status_t ald_nand_reset(nand_handle_t *hperh);
void nand_config_device(nand_handle_t *hperh, nand_device_cfg_t *pdcfg);
/**
  * @}
  */
/** @addtogroup Nand_Public_Functions_Group2
 *  @{
 */
/* IO operation functions */
ald_status_t ald_nand_read_id(nand_handle_t *hperh, nand_id_t *id);
ald_status_t ald_nand_read_page_8b(nand_handle_t *hperh, nand_address_t *addr, uint8_t *buf, uint32_t nr);
ald_status_t ald_nand_write_page_8b(nand_handle_t *hperh, nand_address_t *addr, uint8_t *buf, uint32_t nr);
ald_status_t ald_nand_read_sparearea_8b(nand_handle_t *hperh, nand_address_t *addr, uint8_t *buf, uint32_t nr);
ald_status_t ald_nand_write_sparearea_8b(nand_handle_t *hperh, nand_address_t *addr, uint8_t *buf, uint32_t nr);
ald_status_t ald_nand_read_page_16b(nand_handle_t *hperh, nand_address_t *addr, uint16_t *buf, uint32_t nr);
ald_status_t ald_nand_write_page_16b(nand_handle_t *hperh, nand_address_t *addr, uint16_t *buf, uint32_t nr);
ald_status_t ald_nand_read_sparearea_16b(nand_handle_t *hperh, nand_address_t *addr, uint16_t *buf, uint32_t nr);
ald_status_t ald_nand_write_sparearea_16b(nand_handle_t *hperh, nand_address_t *addr, uint16_t *buf, uint32_t nr);
ald_status_t ald_nand_erase_block(nand_handle_t *hperh, nand_address_t *addr);
/**
  * @}
  */
/** @addtogroup Nand_Public_Functions_Group3
 *  @{
 */
/* NAND Control functions */
void ald_nand_irq_handler(nand_handle_t *hperh);
void ald_nand_irq_cbk(nand_handle_t *hperh);
uint32_t ald_nand_address_inc(nand_handle_t *hperh, nand_address_t *addr);
uint32_t ald_nand_read_status(nand_handle_t *hperh);
ald_nand_state_t ald_nand_get_state(nand_handle_t *hperh);
ald_status_t ald_nand_ecc_enable(nand_handle_t *hperh);
ald_status_t ald_nand_ecc_disable(nand_handle_t *hperh);
ald_status_t ald_nand_get_ecc(nand_handle_t *hperh, uint32_t *val, uint32_t timeout);
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
