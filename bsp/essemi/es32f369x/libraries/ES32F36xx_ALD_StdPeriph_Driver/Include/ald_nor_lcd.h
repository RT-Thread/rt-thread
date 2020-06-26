/**
  *********************************************************************************
  *
  * @file    ald_nor_lcd.h
  * @brief   Header file of EBI_NOR_LCD module driver
  *
  * @version V1.0
  * @date    07 Dec 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#ifndef __ALD_NOR_LCD_H_
#define __ALD_NOR_LCD_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "ald_ebi.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup NOR_LCD
  * @{
  */ 

/**
  * @defgroup NOR_LCD_Private_Constants NOR LCD Private Constants
  * @{
  */

/* NOR device IDs addresses */
#define MC_ADDRESS               ((uint16_t)0x0000)
#define DEVICE_CODE1_ADDR        ((uint16_t)0x0001)
#define DEVICE_CODE2_ADDR        ((uint16_t)0x000E)
#define DEVICE_CODE3_ADDR        ((uint16_t)0x000F)

/* NOR CFI IDs addresses */
#define CFI1_ADDRESS             ((uint16_t)0x10)
#define CFI2_ADDRESS             ((uint16_t)0x11)
#define CFI3_ADDRESS             ((uint16_t)0x12)
#define CFI4_ADDRESS             ((uint16_t)0x13)

/* NOR operation wait timeout */
#define NOR_TMEOUT               ((uint16_t)0xFFFF)

/* NOR memory data width */
#define NOR_MEMORY_8B            ((uint8_t)0x0)
#define NOR_MEMORY_16B           ((uint8_t)0x1)

/* NOR memory device read/write start address */
#define NOR_MEMORY_ADRESS1       EBI_BANK1_1
#define NOR_MEMORY_ADRESS2       EBI_BANK1_2
#define NOR_MEMORY_ADRESS3       EBI_BANK1_3
#define NOR_MEMORY_ADRESS4       EBI_BANK1_4

#define NOR_CMD_ADDRESS_FIRST                 (uint16_t)0x0555
#define NOR_CMD_ADDRESS_FIRST_CFI             (uint16_t)0x0055
#define NOR_CMD_ADDRESS_SECOND                (uint16_t)0x02AA
#define NOR_CMD_ADDRESS_THIRD                 (uint16_t)0x0555
#define NOR_CMD_ADDRESS_FOURTH                (uint16_t)0x0555
#define NOR_CMD_ADDRESS_FIFTH                 (uint16_t)0x02AA
#define NOR_CMD_ADDRESS_SIXTH                 (uint16_t)0x0555

#define NOR_CMD_DATA_READ_RESET               (uint16_t)0x00F0
#define NOR_CMD_DATA_FIRST                    (uint16_t)0x00AA
#define NOR_CMD_DATA_SECOND                   (uint16_t)0x0055
#define NOR_CMD_DATA_AUTO_SELECT              (uint16_t)0x0090
#define NOR_CMD_DATA_PROGRAM                  (uint16_t)0x00A0
#define NOR_CMD_DATA_CHIP_BLOCK_ERASE_THIRD   (uint16_t)0x0080
#define NOR_CMD_DATA_CHIP_BLOCK_ERASE_FOURTH  (uint16_t)0x00AA
#define NOR_CMD_DATA_CHIP_BLOCK_ERASE_FIFTH   (uint16_t)0x0055
#define NOR_CMD_DATA_CHIP_ERASE               (uint16_t)0x0010
#define NOR_CMD_DATA_CFI                      (uint16_t)0x0098
#define NOR_CMD_DATA_BUFFER_AND_PROG          (uint8_t)0x25
#define NOR_CMD_DATA_BUFFER_AND_PROG_CONFIRM  (uint8_t)0x29
#define NOR_CMD_DATA_BLOCK_ERASE              (uint8_t)0x30
#define NOR_MASK_STATUS_DQ5                   (uint16_t)0x0020
#define NOR_MASK_STATUS_DQ6                   (uint16_t)0x0040
/**
  * @}
  */

/** @defgroup NOR_LCD_Private_Macros NOR_LCD Private Macros
  * @{
  */
#define NOR_ADDR_SHIFT(NOR_ADDR, NOR_MEMORY_WIDTH_, ADDRESS)	\
	((uint32_t)(((NOR_MEMORY_WIDTH_) == NOR_MEMORY_16B) ? 	\
	((uint32_t)((NOR_ADDR) + (2U * (ADDRESS)))):		\
	((uint32_t)((NOR_ADDR) + (ADDRESS)))))
#define NOR_WRITE(ADDR, DATA)  (*(__IO uint16_t *)((uint32_t)(ADDR)) = (DATA))
/**
  * @}
  */

/** @defgroup NOR_LCD_Public_Types NOR_LCD Public Types
  * @{
  */ 
/** 
  * @brief  ALD SRAM State structures definition  
  */ 
typedef enum {
	ALD_NOR_STATE_RESET     = 0x00U,	/**< NOR not yet initialized or disabled */
	ALD_NOR_STATE_READY     = 0x01U,	/**< NOR initialized and ready for use */
	ALD_NOR_STATE_BUSY      = 0x02U,	/**< NOR internal processing is ongoing */
	ALD_NOR_STATE_ERROR     = 0x03U,	/**< NOR error state */ 
	ALD_NOR_STATE_PROTECTED = 0x04U		/**< NOR NORSRAM device write protected */
} ald_nor_state_t;

/**
  * @brief  EBI NOR Status typedef
  */
typedef enum {
	ALD_NOR_STATUS_SUCCESS = 0,   /**< NOR status success */
	ALD_NOR_STATUS_ONGOING,       /**< NOR status ongoing */
	ALD_NOR_STATUS_ERROR,         /**< NOR status error */
	ALD_NOR_STATUS_TIMEOUT,       /**< NOR status timeout */
} nor_status_t;

/**
  * @brief  EBI NOR ID typedef
  */
typedef struct {
	uint16_t m_code;	/**< Defines the device's manufacturer code used to identify the memory */
	uint16_t device_code1;	/**< DEVICE_CODE1_ADDR code1 */
	uint16_t device_code2;	/**< DEVICE_CODE1_ADDR code2 */
	uint16_t device_code3;	/**< DEVICE_CODE1_ADDR code3 */
} nor_id_t;

/**
  * @brief  EBI NOR CFI typedef
  */
typedef struct {
	uint16_t cfi_1;  /**< NOR CFI 1 */
	uint16_t cfi_2;  /**< NOR CFI 2 */
	uint16_t cfi_3;  /**< NOR CFI 3 */
	uint16_t cfi_4;  /**< NOR CFI 4 */
} nor_cfi_t;

/** 
  * @brief  NOR handle Structure definition  
  */ 
typedef struct {
	EBI_NOR_SRAM_TypeDef *instance;		/**< Register base address */ 
	EBI_NOR_SRAM_EXTENDED_TypeDef *ext;	/**< Extended mode register base address */
	ald_ebi_nor_sram_init_t init;		/**< NOR device control configuration parameters */
	lock_state_t lock;			/**< NOR locking object */ 
	__IO ald_nor_state_t state;		/**< NOR device access state */
} nor_handle_t;
/**
  * @}
  */

/** @addtogroup NOR_Public_Functions
 *  @{
 */
/** @addtogroup NOR_Public_Functions_Group1
 *  @{
 */
/* Initialization/de-initialization functions */  
ald_status_t ald_nor_init(nor_handle_t *hperh, ald_ebi_nor_sram_timing_t *timing, ald_ebi_nor_sram_timing_t *ext_timing);
ald_status_t ald_nor_deinit(nor_handle_t *hperh);
/**
  * @}
  */
/** @addtogroup NOR_LCD_Public_Functions_Group2
 *  @{
 */
/* I/O operation functions */
ald_status_t ald_nor_read_id(nor_handle_t *hperh, nor_id_t *id);
ald_status_t ald_nor_return_readmode(nor_handle_t *hperh);
ald_status_t ald_nor_read(nor_handle_t *hperh, uint32_t *addr, uint16_t *data);
ald_status_t ald_nor_program(nor_handle_t *hperh, uint32_t *addr, uint16_t *data);
ald_status_t ald_nor_read_buffer(nor_handle_t *hperh, uint32_t addr, uint16_t *data, uint32_t size);
ald_status_t ald_nor_program_buffer(nor_handle_t *hperh, uint32_t addr, uint16_t *data, uint32_t size);
ald_status_t ald_nor_erase_block(nor_handle_t *hperh, uint32_t blkaddr, uint32_t addr);
ald_status_t ald_nor_erase_chip(nor_handle_t *hperh);
ald_status_t ald_nor_read_cfi(nor_handle_t *hperh, nor_cfi_t *cfi);
/**
  * @}
  */
/** @addtogroup NOR_LCD_Public_Functions_Group3
 *  @{
 */
/* Control functions */
ald_status_t ald_nor_write_enable(nor_handle_t *hperh);
ald_status_t ald_nor_write_disable(nor_handle_t *hperh);
/**
  * @}
  */
/** @addtogroup NOR_LCD_Public_Functions_Group4
 *  @{
 */
/* State functions */
ald_nor_state_t ald_nor_get_state(nor_handle_t *hperh);
nor_status_t ald_nor_get_status(nor_handle_t *hperh, uint32_t addr, uint32_t timeout);
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

#endif /* __ALD_NOR_LCD_H__ */
