/**
  *********************************************************************************
  *
  * @file    ald_flash.h
  * @brief   Header file of FLASH driver
  *
  * @version V1.0
  * @date    17 Jun 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#ifndef __ALD_FLASH_H__
#define __ALD_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/**
  * @defgroup FLASH_Private_Macros FLASH Private Macros
  * @{
  */
#define FLASH_REG_UNLOCK()				\
do {							\
	if (op_cmd == OP_FLASH)	 {			\
		WRITE_REG(MSC->FLASHKEY, 0x8ACE0246);	\
		WRITE_REG(MSC->FLASHKEY, 0x9BDF1357);	\
	}						\
	else {						\
		WRITE_REG(MSC->INFOKEY, 0x7153BFD9);	\
		WRITE_REG(MSC->INFOKEY, 0x0642CEA8);	\
	}						\
} while (0)
#define FLASH_REQ()			(SET_BIT(MSC->FLASHCR, MSC_FLASHCR_FLASHREQ_MSK))
#define FLASH_REQ_FIN()			(CLEAR_BIT(MSC->FLASHCR, MSC_FLASHCR_FLASHREQ_MSK))
#define FLASH_IAP_ENABLE()		(SET_BIT(MSC->FLASHCR, MSC_FLASHCR_IAPEN_MSK))
#define FLASH_IAP_DISABLE()		(CLEAR_BIT(MSC->FLASHCR, MSC_FLASHCR_IAPEN_MSK))
#define FLASH_BASE_ADDR			0x00000000
#define	FLASH_PAGE_SIZE			1024UL
#define FLASH_WORD_SIZE			8UL
#define FLASH_TOTAL_SIZE		512UL
#define FLASH_PAGE_MASK			(FLASH_PAGE_SIZE - 1)
#define FLASH_WORD_MASK			(FLASH_WORD_SIZE - 1)
#define IS_FLASH_ADDRESS(ADDR)		((ADDR) < (FLASH_BASE_ADDR + FLASH_PAGE_SIZE * FLASH_TOTAL_SIZE))
#define IS_4BYTES_ALIGN(ADDR)		(((uint32_t)(ADDR) & 0x3) == 0 ? 1 : 0)
#define FLASH_PAGE_ADDR(ADDR)		((ADDR) & (~FLASH_PAGE_MASK))
#define FLASH_PAGEEND_ADDR(ADDR)	((ADDR) | FLASH_PAGE_MASK)
#define FLASH_WORD_ADDR(ADDR)		((ADDR) & (~FLASH_WORD_MASK))
#define FLASH_WORDEND_ADDR(ADDR)	((ADDR) | FLASH_WORD_MASK)
#define INFO_PAGE_SIZE			1024UL
#define INFO_PAGE_MASK			(INFO_PAGE_SIZE - 1)
#define INFO_PAGE_ADDR(ADDR)		((ADDR) & (~INFO_PAGE_MASK))

#ifdef USE_FLASH_FIFO
	#define	FLASH_FIFO 1
#else
	#define	FLASH_FIFO 0
#endif
/**
  * @}
  */

/** @defgroup FLASH_Private_Types FLASH Private Types
  * @{
  */
typedef enum {
	FLASH_CMD_AE          = 0x000051AE,	/**< Program area erase all */
	FLASH_CMD_PE          = 0x00005EA1,	/**< Page erase  */
	FLASH_CMD_WP          = 0x00005DA2,	/**< Word program */
	FLASH_CMD_WP_FAST     = 0x00005CA3, 	/**< Flash quickly program */
	FLASH_CMD_DATAPE      = 0x00005BA4,	/**< Data flash page page erase */
	FLASH_CMD_DATAWP      = 0x00005AA5,	/**< Data flash word program */
	FLASH_CMD_DATAWP_FAST = 0x000059A6,	/**< Data flash quickly program */
	FLASH_CMD_NP_AE       = 0x000050AF,	/**< No-private area erase all */
} flash_cmd_type;

typedef enum {
	OP_FLASH = 0,	/**< Operate Pragram area */
	OP_INFO  = 1,	/**< Operate info area */
} op_cmd_type;

/**
  * @}
  */ 
/** @addtogroup Flash_Private_Functions
  * @{
  */
ald_status_t flash_page_erase(uint32_t addr);
ald_status_t flash_word_program(uint32_t addr, uint32_t *data, uint32_t len, uint32_t fifo);
/**
  * @}
  */

/** @addtogroup Flash_Public_Functions
  * @{
  */
ald_status_t ald_flash_read(uint32_t *ram_addr, uint32_t addr, uint16_t len);
ald_status_t ald_flash_write(uint32_t addr, uint8_t *buf, uint16_t len);
ald_status_t ald_flash_erase(uint32_t addr, uint16_t len);
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

#endif /* __ALD_FLASH_H__ */
