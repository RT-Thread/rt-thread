/***************************************************************************//**
 * @file    ald_qspi.h
 * @brief   Header file of QSPI module driver.
 * @version V1.0
 * @date    09 Nov 2019
 * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          09 Nov 2019     AE Team         The first version
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

#ifndef __ALD_QSPI_H_
#define __ALD_QSPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"
#include "ald_dma.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup QSPI
  * @{
  */
/** @defgroup QSPI_Public_Types QSPI Public Types
  * @{
  */
/**
  * @brief ALD QSPI state
  */
typedef enum {
	QSPI_STATE_BUSY_TX = 0x11U,	/**< Data Transmission process is ongoing */
	QSPI_STATE_BUSY_RX = 0x21U,	/**< Data Reception process is ongoing */
} qspi_state_t;

/**
  * @brief QSPI Instruction Transfer Type
  */
typedef enum {
	QSPI_XFER_SINGLE = 0x00U,	/**< Instruction shifted on DQ0 only*/
	QSPI_XFER_DUAL   = 0x01U,	/**< Instruction,Address and data sent on DQ0 and DQ1*/
	QSPI_XFER_QUAD   = 0x02U,	/**< Instruction,Address and data sent on DQ0,DQ1 and DQ2*/
} qspi_xfer_t;

/**
 * @brief QSPI Indirect Access SRAM fill level
 */	
typedef enum {
	QSPI_SRAM_RD = 0U,	/**< SRAM fill level(indirect write partition)in units of words(4bytes)*/
	QSPI_SRAM_WR = 1U,	/**< SRAM fill level(indirect read partition)in units of words(4bytes)*/
} qspi_sram_t;

/** 
  * @brief QSPI Clock Phase 
  */
typedef enum {
	QSPI_CPHA_1E = 0U,	/**< First edge*/
	QSPI_CPHA_2E = 1U,	/**< Second edge*/
} qspi_cpha_t;

/** 
  * @brief QSPI_Clock_Polarity QSPI Clock Polarity
  */
typedef enum {
	QSPI_CPOL_L = 0U,	/**< QSPI clock polarity low */
	QSPI_CPOL_H = 1U,	/**< QSPI clock polarity high */
} qspi_cpol_t;

/** 
  * @brief QSPI peripheral select decode
  */
typedef enum {
	QSPI_SINGLE_CHIP = 0x0U,	/**< Only 1 of 4 selects n_ss_out[3:0] is active */
	QSPI_MULTI_CHIP  = 0x1U,	/**< Allow external 4-to-16 decode */
} qspi_nss_decode_t;

/** 
  * @brief QSPI_Baud_Rate_Clock_Prescaler QSPI Baud Rate Clock Prescaler
  */
typedef enum {
	QSPI_DIV_2  = 0x0U,	/**< Master mode baud rate dibisor 2*/
	QSPI_DIV_4  = 0x1U,	/**< Master mode baud rate dibisor 4*/
	QSPI_DIV_6  = 0x2U,	/**< Master mode baud rate dibisor 6*/
	QSPI_DIV_8  = 0x3U,	/**< Master mode baud rate dibisor 8*/
	QSPI_DIV_10 = 0x4U,	/**< Master mode baud rate dibisor 10*/
	QSPI_DIV_12 = 0x5U,	/**< Master mode baud rate dibisor 12*/
	QSPI_DIV_14 = 0x6U,	/**< Master mode baud rate dibisor 14*/
	QSPI_DIV_16 = 0x7U,	/**< Master mode baud rate dibisor 16*/
	QSPI_DIV_18 = 0x8U,	/**< Master mode baud rate dibisor 18*/
	QSPI_DIV_20 = 0x9U,	/**< Master mode baud rate dibisor 20*/
	QSPI_DIV_22 = 0xAU,	/**< Master mode baud rate dibisor 22*/
	QSPI_DIV_24 = 0xBU,	/**< Master mode baud rate dibisor 24*/
	QSPI_DIV_26 = 0xCU,	/**< Master mode baud rate dibisor 26*/
	QSPI_DIV_28 = 0xDU,	/**< Master mode baud rate dibisor 28*/
	QSPI_DIV_30 = 0xEU,	/**< Master mode baud rate dibisor 30*/
	QSPI_DIV_32 = 0xFU,	/**< Master mode baud rate dibisor 32*/
} qspi_clk_div_t;

/** 
  * @brief QSPI Peripheral chip select decode
  */
typedef enum {
	QSPI_CS_NSS0 = 0x0U,	/**< NSS0 active*/
	QSPI_CS_NSS1 = 0x1U,	/**< NSS1 active*/ 
	QSPI_CS_NSS2 = 0x3U,	/**< NSS2 active*/
	QSPI_CS_NSS3 = 0x7U,	/**< NSS3 active*/
} qspi_nss_t;

/** 
  *@brief Size of flash connected to CS[x](x = 0 ~ 3)pin
  */
typedef enum {
	QSPI_NSS_512M = 0x0U,	/**< size of 512Mb*/
        QSPI_NSS_1G   = 0x1U,	/**< size of 1Gb*/
        QSPI_NSS_2G   = 0x2U,	/**< size of 2Gb*/
        QSPI_NSS_4G   = 0x3U,	/**< size of 3Gb*/
} qspi_nss_size_t;

/** 
  *@brief Qspi external flash device configuration
  */
typedef struct {
	uint8_t addr;          /**< Peripheral address */
	uint16_t page;         /**< Flash page size */
	uint16_t blk;          /**< Flash block size */
	qspi_nss_size_t cs0;   /**< NSS0 flash size */
	qspi_nss_size_t cs1;   /**< NSS1 flash size */
	qspi_nss_size_t cs2;   /**< NSS2 flash size */
	qspi_nss_size_t cs3;   /**< NSS3 flash size */
} qspi_device_size_t;

/** 
  * @brief QSPI Sample Edge Selection
  */
typedef enum {
	QSPI_FALLING_E = 0x0U,	/**< Data outputs from flash are sampled on falling edge of the ref_clk*/
	QSPI_RISING_E  = 0x1U,	/**< Data outputs from flash are sampled on rising edge of the ref_clk*/
} qspi_data_sampled_t;

/**
  * @brief Flash write-protected blocks configuration.
  */  
typedef struct {
	uint32_t lowblk;	/**< the lower block in the range of blocks that is to be locked from writing*/
	uint32_t upblk;		/**< upper block in the range of blocks that is to be locked from writing*/
} qspi_wr_protect_t;

/**
  * @brief  QSPI STIG Command Structure. 
  */
typedef struct {
	uint32_t code;		/**< command op-code*/
	uint32_t rd_len;	/**< Number of Read Data Bytes*/
	uint32_t addr_len;	/**< Number of Address Bytes*/
	uint32_t wr_len;	/**< Number of Write Data Bytes*/
	uint32_t d_sycle;	/**< Number of dummy cycles*/
	type_func_t mode_bit;	/**< Mode Bit Configuration register are sent following the address bytes*/
	type_func_t op_addr;	/**< If opcde requires an address*/
	uint32_t val;		/**< Mode bits,sent to device following the address*/
	uint32_t addr;		/**< Flash opcde address*/
	void *rd_buf;		/**< Buffer for read data*/
	void *wr_buf;		/**< Buffer with data to write*/
} qspi_stig_cmd_t;

/**
  * @brief QSPI base initialization structure. 
  */
typedef struct {
	qspi_clk_div_t clkdiv;		/**< QSPI Baud Rate Clock Prescaler*/
	type_func_t wrppin;		/**< QSPI Set Write Protect Pin*/
	qspi_nss_decode_t nssdcode;	/**< QSPI Peripheral Select Decode*/
	qspi_nss_t chipsel;		/**< QSPI Peripheral Select Line*/
	qspi_cpol_t cpol;               /**< QSPI polarity */
	qspi_cpha_t chpa;               /**< QSPI phase */
} qspi_init_t;

/**
  * @brief QSPI legacy initialization structure.
  */
typedef struct {
	uint8_t	tx_thrd; /**< Tx FIFO threshhold */
	uint8_t	rx_thrd; /**< Rx FIFO threshhold */ 
} qspi_legacy_cfg_t;

/**
  * @brief QSPI Device Read Instruction Configuration structure. 
  */
typedef struct {
	uint8_t rdcde;		/**< Read opcode in non-xip mode*/		
	uint8_t dcyles;		/**< Number of dummy read clock cycles*/
	uint8_t mbitval;	/**< Mode bits,sent to device following the address bytes*/
	type_func_t ddrbit;	/**< Opcode from bit 7 to 0 is compliant with DDR command*/
	type_func_t modebit;	/**< Enable mode bit*/
	qspi_xfer_t addxfer;	/**< Transfer type used for address*/
	qspi_xfer_t datxfer;	/**< Transfer type used for data*/
	qspi_xfer_t instxfer;	/**< Transfer type used for instruction*/
} qspi_read_cfg_t;

/**
  * @brief QSPI Device Write Instruction Configuration structure. 
  */
typedef struct {
	uint8_t wrcde;		/**< Write opcode*/
	uint8_t dcyles;		/**< Number of dummy read clock cycles*/
	qspi_xfer_t addxfer;	/**< Transfer type used for address*/
	qspi_xfer_t datxfer;	/**< Transfer type used for data*/
	qspi_xfer_t instxfer;	/**< Transfer type used for instruction*/	 
	type_func_t autowel;	/**< Turn off automatic*/
} qspi_write_cfg_t;

/**
  * @brief  QSPI Indirect Configuration structure.involatile parameters 
  */
typedef struct {
	uint32_t saddr;		/**< Flash start address, commence write operation*/
	uint32_t wrlen;		/**< Number of indirect write bytes*/
} qspi_indac_wr_cfg_t;

typedef struct {
	uint32_t saddr;		/**< FLASH start address, commence read operation*/
	uint32_t rdlen;		/**< Number of indirect read bytes*/ 
} qspi_indac_rd_cfg_t;

typedef struct {
	uint32_t srampt;	/**< Defines the size of the indirect read partion in the SRAM*/
	uint32_t trgaddr;	/**< Indirect trigger address which is used by AHB controller*/
	uint32_t trgrng;	/**< The offset of indirect trigger address*/
	uint32_t wrwmark;	/**< Maximum fill level of SRAM before a DMA, 0xFFFFFFFF disable the function*/
	uint32_t rdwmark;	/**< Fill level passes watermark, an interrupt generated*/
} qspi_indac_cfg_t;

/**
  * @brief QSPI DAC configuration.
  */ 
typedef struct {
	type_func_t dtrprtcol;		/**< DTR protocol*/
	type_func_t ahbdecoder;		/**< AHB decoder, direct access mode only*/
	type_func_t xipimmed;		/**< QSPI Enter XIP Immediately*/
	type_func_t xipnextrd;		/**< QSPI Enter XIP Next Read*/
	type_func_t addrremap;		/**< Enable AHB address re-mapping*/ 
	uint32_t remapaddr;		/**< Remap incoming AHB address to different address*/ 
	type_func_t dmaperh;		/**< QSPI dma interface*/
	qspi_read_cfg_t rdinit;		/**< QSPI read instruction configuration*/
	qspi_write_cfg_t wrinit;	/**< QSPI write instruction configuration*/
} qspi_dac_cfg_t;

/** 
  * @brief  QSPI Handle Structure definition  
  */  
typedef struct {
	QSPI_TypeDef *perh;	/**< QSPI registers base address*/
	qspi_init_t init;	/**< QSPI communication parameters*/
	uint8_t *tx_buf;	/**< Pointer to QSPI transfer buffer */
	uint16_t tx_size;       /**< QSPI transfer size */
	uint16_t tx_cnt;        /**< QSPI transfer counter */
	uint8_t *rx_buf;	/**< Pointer to QSPI receive buffer */
	uint16_t rx_size;       /**< QSPI receive size */
	uint16_t rx_cnt;        /**< QSPI receive counter */

	dma_handle_t hdma;	/**< QSPI Rx/Tx DMA Handle parameters*/

	qspi_state_t state;	/**< QSPI communication state */
	__IO lock_state_t lock;	/**< Locking object*/
} qspi_handle_t;

/**
  * @brief Defines command to be executed using STIG mechanism. 
  */
typedef struct {
	uint32_t ccsot;		/**< range [0 ~ 255]*/
	uint32_t cseot;		/**< range [0 ~ 255]*/
	uint32_t csdads;	/**< range [0 ~ 255]*/
	uint32_t csda;		/**< range [0 ~ 255]*/
} qspi_dly_cfg_t;

/**
  * @brief QSPI Read Data Capture Configuration. 
  */
typedef struct {
	uint32_t dlytd;			/**< Delay transmitted data [0 ~ 15]*/
	uint32_t dlydcl;		/**< Delay the read data capturing logic [0 ~ 15]*/
	qspi_data_sampled_t smpledge;	/**< Sample edge selection(of the flash data outputs) @ref qspi_data_sampled_t*/
} qspi_data_capture_cfg_t;

/**
  * @brief QSPI Indirect Write Progress Status. 
  */
typedef enum {
	QSPI_INDWR_PROGRESS = (1U << 2),	/**< Indirect write operation in progress*/
	QSPI_INDWR_CPLT     = (1U << 5),	/**< Indirect write completion*/
} qspi_indwr_status_t;

/**
  * @brief QSPI Indirect Read Progress Status. 
  */
typedef enum {
	QSPI_INDRD_PROGRESS = (1U << 2),	/**< Indirect read operation in progress*/
	QSPI_RD_CPLT        = (1U << 5),	/**< Indirect read completion*/
} qspi_indrd_flag_t;

/**
  * @brief QSPI Auto Poll Configuration Struction. 
  */
typedef struct {
	uint32_t opcode;	/**< Automatically poll operation code */
	uint32_t indx;		/**< Polling bit index */
	uint32_t polarity;	/**< Defines polling polarity */
	uint32_t validcnt;	/**< Expect true result times */
	uint32_t repdly;	/**< Defines additional delay for maintain de-assert during auto-polling phase */
	uint32_t polexpcnt;	/**< Poll cycles,which polling expiration interrupt is generated*/
} qspi_auto_poll_t;

/**
  *@brief QSPI_Interrupt_definition QSPI Interrupt Definition
  */
typedef enum {
	QSPI_IT_POLLF   = (1U << 13),	/**< Programmed polls cycles expired flag */		  		  
	QSPI_IT_INDRSFF = (1U << 12),	/**< Indirect read partition of SRAM is full flag */
	QSPI_IT_SRFFF   = (1U << 11),	/**< Small rx FIFO full flag */
	QSPI_IT_SRFNEF  = (1U << 10),	/**< Small rx FIFO not empty flag */
	QSPI_IT_STFFF   = (1U << 9),	/**< Small tx FIFO full flag */
	QSPI_IT_STFNFF  = (1U << 8),	/**< Small tx FIFO not full flag */
	QSPI_IT_ROVF    = (1U << 7),	/**< Receive overflow flag */
	QSPI_IT_INDTWF  = (1U << 6),	/**< Indirect transfer watermark level breached flag */
	QSPI_IT_AHBAEF  = (1U << 5),	/**< Illegal AHB access detected flag */
	QSPI_IT_WPAF    = (1U << 4),	/**< Write to protected area was rejected flag */
	QSPI_IT_INDRRF  = (1U << 3),	/**< Indirect operation could not be accepted flag */
	QSPI_IT_INDCF   = (1U << 2),	/**< Controller has completed last triggered indirect operation flag */
	QSPI_IT_UDFF    = (1U << 1),	/**< Underflow detected flag */
	QSPI_IT_MODFF   = (1U << 0),	/**< Mode fail M flag */
} qspi_it_t;
/**
  * @brief QSPI_Flag_definition QSPI Flag Definition
  */
typedef enum {
	QSPI_IF_POLLF   = (1U << 13),	/**< Programmed polls cycles expired flag */		  
	QSPI_IF_INDRSFF = (1U << 12),	/**< Indirect read partition of SRAM is full flag */
	QSPI_IF_SRFFF   = (1U << 11),	/**< Small rx FIFO full flag */
	QSPI_IF_SRFNEF  = (1U << 10),	/**< Small rx FIFO not empty flag */
	QSPI_IF_STFFF   = (1U << 9),	/**< Small tx FIFO full flag */
	QSPI_IF_STFNFF  = (1U << 8),	/**< Small tx FIFO not full flag */
	QSPI_IF_ROVF    = (1U << 7),	/**< Receive overflow flag */
	QSPI_IF_INDTWF  = (1U << 6),	/**< Indirect transfer watermark level breached flag */
	QSPI_IF_AHBAEF  = (1U << 5),	/**< Illegal AHB access detected flag */
	QSPI_IF_WPAF    = (1U << 4),	/**< Write to protected area was rejected flag */
	QSPI_IF_INDRRF  = (1U << 3),	/**< Indirect operation could not be accepted flag */
	QSPI_IF_INDCF   = (1U << 2),	/**< Controller has completed last triggered indirect operation flag */
	QSPI_IF_UDFF    = (1U << 1),	/**< Underflow detected flag */
	QSPI_IF_MODFF   = (1U << 0),	/**< Mode fail M flag */
} qspi_flag_t;
/**
  * @}
  */

/** @defgroup QSPI_Private_Macros   QSPI Private Macros
  * @{
  */
#define IS_QSPI_SRAM_PARTITION(x)	((x) < 255)
#define IS_QSPI_INDIRECT_TRIGGER_RANGE(x)	(((x) < 16))
#define IS_QSPI_INDIRECT_READ_WATERMARK(x)      ((x) < 512)
#define IS_QSPI_INDIRECT_SRAM_FILL_TYPE(x)	(((x) == QSPI_SRAM_RD) || ((x) == QSPI_SRAM_WR))
#define IS_QSPI_INDIRECT_READ_STATUS(x)		(((x) == QSPI_INDRD_PROGRESS) || ((x) == QSPI_RD_CPLT))
#define IS_QSPI_INDIRECT_WRITE_STATUS(x)	(((x) == QSPI_INDWR_PROGRESS) || ((x) == QSPI_INDWR_CPLT))
#define IS_QSPI_DEVICE_DELAY_CCSOT(x)	((x) < 256)
#define IS_QSPI_DEVICE_DELAY_CSEOT(x)	((x) < 256)
#define IS_QSPI_DEVICE_DELAY_CSDADS(x)	((x) < 256)
#define IS_QSPI_DEVICE_DELAY_CSDA(x)	((x) < 256)

#define IS_QSPI_READ_DATA_CAPTURE_DELAY_READ(x)		((x) < 16)
#define IS_QSPI_READ_DATA_SAMPLE_EDGE(x)	(((x) == QSPI_FALLING_E) || \
						((x) == QSPI_RISING_E))
#define IS_QSPI_READ_DATA_DELAY_TRANSMIT(x)	((x) < 16)
#define IS_QSPI_ALL(x)	((x) == QSPI)
#define IS_QSPI_DCYLES(x)		((x) <= 31)

#define IS_QSPI_ADDR_SIZE(x)	((x) <= 15)
#define IS_QSPI_PAGE_SIZE(x)	((x) <= 0xfff)
#define IS_QSPI_BLOCK_SIZE(x)	((x) <= 0x1f)
#define IS_QSPI_NSS_SIZE(x)	((x) <= 3)

#define IS_QSPI_XFER_TYPE(x)	(((x) == QSPI_XFER_SINGLE)  || \
				((x) == QSPI_XFER_DUAL) || \
				((x) == QSPI_XFER_QUAD))
#define IS_QSPI_DDR_BIT_ENABLE(x)	(((x) == QSPI_READ_DDR_BIT_DISABLE) || \
					((x) == QSPI_READ_DDR_BIT_ENABLE))
#define IS_QSPI_MODE_BIT_ENABLE(x)	(((x) == QSPI_READ_INST_MODE_BIT_DISABLE) || \
					((x) == QSPI_READ_INST_MODE_BIT_ENABLE))
#define IS_QSPI_RD_OPCODE(x)		(((x) < 0xFF))
#define IS_QSPI_WR_OPCODE(x)		(((x) < 0xFF))
#define IS_QSPI_CLOCK_PRESCALER(x)	(((x) == QSPI_DIV_2)  || \
					((x) == QSPI_DIV_4)  || \
					((x) == QSPI_DIV_6)  || \
					((x) == QSPI_DIV_8)  || \
					((x) == QSPI_DIV_10) || \
					((x) == QSPI_DIV_12) || \
					((x) == QSPI_DIV_14) || \
					((x) == QSPI_DIV_16) || \
					((x) == QSPI_DIV_18) || \
					((x) == QSPI_DIV_20) || \
					((x) == QSPI_DIV_22) || \
					((x) == QSPI_DIV_24) || \
					((x) == QSPI_DIV_26) || \
					((x) == QSPI_DIV_28) || \
					((x) == QSPI_DIV_30) || \
					((x) == QSPI_DIV_32))
#define IS_QSPI_CLOCK_PHASE(x)		(((x) == QSPI_CPHA_1E)  || \
					((x) == QSPI_CPHA_2E))
#define IS_QSPI_CLOCK_POLARITY(x)	(((x) == QSPI_CPOL_L)  || \
					((x) == QSPI_CPOL_H))
#define IS_QSPI_IF(x)	(((x) == QSPI_IF_POLLF)		|| \
			((x) == QSPI_IF_INDRSFF)	|| \
			((x) == QSPI_IF_SRFFF)		|| \
			((x) == QSPI_IF_SRFNEF)		|| \
			((x) == QSPI_IF_STFFF)		|| \
			((x) == QSPI_IF_STFNFF)		|| \
			((x) == QSPI_IF_ROVF)		|| \
			((x) == QSPI_IF_INDTWF)		|| \
			((x) == QSPI_IF_AHBAEF)		|| \
			((x) == QSPI_IF_WPAF)		|| \
			((x) == QSPI_IF_INDRRF)		|| \
			((x) == QSPI_IF_INDCF)		|| \
			((x) == QSPI_IF_UDFF)		|| \
			((x) == QSPI_IF_MODFF))
#define IS_QSPI_IT(x)	(((x) == QSPI_IT_POLLF)		|| \
			((x) == QSPI_IT_INDRSFF)	|| \
			((x) == QSPI_IT_SRFFF)		|| \
			((x) == QSPI_IT_SRFNEF)		|| \
			((x) == QSPI_IT_STFFF)		|| \
			((x) == QSPI_IT_STFNFF)		|| \
			((x) == QSPI_IT_ROVF)		|| \
			((x) == QSPI_IT_INDTWF)		|| \
			((x) == QSPI_IT_AHBAEF)		|| \
			((x) == QSPI_IT_WPAF)		|| \
			((x) == QSPI_IT_INDRRF)		|| \
			((x) == QSPI_IT_INDCF)		|| \
			((x) == QSPI_IT_UDFF)		|| \
			((x) == QSPI_IT_MODFF))

/**
  * @}
  */

/**
  * @defgroup QSPI_Public_Macros QSPI Public Macros
  * @{
  */
#define QSPI_MEMORY_ADDRESS			0x90000000U
#define QSPI_SRAM_SIZE				255U
#define QSPI_TIMEOUT_DEFAULT_VALUE		5000U /* 5s */	
#define QSPI_SRAM_DEPTH 			0xFFU
#define QSPI_DAC_ENABLE(hperh)			SET_BIT((hperh)->perh->CR, QSPI_CR_DACEN_MSK)
#define QSPI_DAC_DISABLE(hperh)			CLEAR_BIT((hperh)->perh->CR, QSPI_CR_DACEN_MSK)
#define QSPI_LEGACY_SPI_ENABLE(hperh)		SET_BIT((hperh)->perh->CR, QSPI_CR_LIMEN_MSK)
#define QSPI_LEGACY_SPI_DISABLE(hperh)		CLEAR_BIT((hperh)->perh->CR, QSPI_CR_LIMEN_MSK)
#define QSPI_WRITE_PROTECT_ENABLE(hperh)	SET_BIT((hperh)->perh->WPCR, QSPI_WPCR_WPEN_MSK);
#define QSPI_WRITE_PROTECT_DISABLE(hperh)	CLEAR_BIT((hperh)->perh->WPCR, QSPI_WPCR_WPEN_MSK);
#define QSPI_ENABLE(hperh)			SET_BIT((hperh)->perh->CR, QSPI_CR_EN_MSK)
#define QSPI_DISABLE(hperh)			CLEAR_BIT((hperh)->perh->CR, QSPI_CR_EN_MSK)
#define QSPI_AUTO_POLL_ENABLE(hperh)		CLEAR_BIT((hperh)->perh->WCR, QSPI_WCR_PDIS_MSK)
#define QSPI_AUTO_POLL_DISABLE(hperh)		SET_BIT((hperh)->perh->WCR, QSPI_WCR_PDIS_MSK)
#define QSPI_DMA_ENABLE(hperh)			SET_BIT((hperh)->perh->CR, QSPI_CR_DMAEN_MSK)
#define QSPI_DMA_DISABLE(hperh)			CLEAR_BIT((hperh)->perh->CR, QSPI_CR_DMAEN_MSK)
#define QSPI_CANCEL_INDIRECT_READ(hperh)	SET_BIT((hperh)->perh->IRTR, QSPI_IRTR_RDDIS_MSK)
/**
  * @}
  */

/** @addtogroup QSPI_Public_Functions
  * @{
  */

/** @addtogroup QSPI_Public_Functions_Group1 
  * @{
  */
/* QSPI basic execution functions */
void ald_qspi_init(qspi_handle_t *hperh);
uint32_t ald_qspi_dac_rd(uint32_t addr);
void ald_qspi_dac_wr(uint32_t addr, uint32_t dat);
ald_status_t ald_qspi_read_config(qspi_handle_t* hperh, const qspi_read_cfg_t * rdcfg);
ald_status_t ald_qspi_write_config(qspi_handle_t* hperh, const qspi_write_cfg_t * wrcfg);
ald_status_t ald_qspi_device_delay_config(qspi_handle_t * hperh, qspi_dly_cfg_t *dlycfg);
ald_status_t ald_qspi_read_data_capture_config(qspi_handle_t * hperh, qspi_data_capture_cfg_t *dtcptcfg);
ald_status_t ald_qspi_device_size_config(qspi_handle_t *hperh, qspi_device_size_t * devcfg);
ald_status_t qspi_dac_config(qspi_handle_t * hperh, qspi_dac_cfg_t * dcfg);
/**
  * @}
  */
/** @addtogroup QSPI_Public_Functions_Group2
  * @{
  */
/* QSPI indirect and stig access execution functions */
ald_status_t ald_qspi_indac_config(qspi_handle_t * hperh, qspi_indac_cfg_t *indcfg);
ald_status_t ald_qspi_indac_transmit_by_it(qspi_handle_t *hperh, uint32_t saddr, uint8_t *psrc,  uint32_t size);
ald_status_t ald_qspi_indac_transmit_by_poll(qspi_handle_t *hperh, uint32_t saddr, uint8_t *psrc,  uint32_t size);
ald_status_t ald_qspi_indac_read_by_poll(qspi_handle_t *hperh, uint32_t saddr, uint8_t *desbuf, uint16_t size);
ald_status_t ald_qspi_indac_read_by_it(qspi_handle_t *hperh, uint32_t saddr, uint8_t *desbuf, uint16_t size);
ald_status_t ald_qspi_execute_stig_cmd(qspi_handle_t* hperh, const qspi_stig_cmd_t * scmd);
#ifdef ALD_DMA
ald_status_t ald_qspi_indac_transmit_by_dma(qspi_handle_t *hperh, uint32_t addr, uint8_t *psrc, uint16_t size);
ald_status_t ald_qspi_indac_read_by_dma(qspi_handle_t *hperh, uint32_t addr, uint8_t *pdbuf, uint16_t size);
#endif
/**
  * @}
  */
/** @addtogroup QSPI_Public_Functions_Group3
  * @{
  */
/* QSPI status functions */
flag_status_t qspi_get_flag_status(qspi_handle_t *hperh, qspi_flag_t flag);
void ald_qspi_clear_it_flag(qspi_handle_t *hperh, qspi_flag_t flag);
uint16_t qspi_read_sram_fill_level(qspi_handle_t * hperh, qspi_sram_t srt);
void ald_qspi_write_proect_config(qspi_handle_t * hperh, qspi_wr_protect_t* wpcfg);
void ald_qspi_write_proect_inverse(qspi_handle_t * hperh, type_func_t state);
ald_status_t ald_qspi_auto_poll(qspi_handle_t *hperh, qspi_auto_poll_t* apcfg);
void ald_qspi_irq_handler(qspi_handle_t *hperh);
void ald_qspi_interrupt_config(qspi_handle_t *hperh, qspi_it_t it, type_func_t state);
void ald_qspi_legacy_config(qspi_handle_t* hperh, const qspi_legacy_cfg_t *config);
flag_status_t qspi_indwr_get_status(qspi_handle_t *hperh, qspi_indwr_status_t status);
ald_status_t qspi_indwr_wait_flag(qspi_handle_t *hperh, qspi_indwr_status_t flag, flag_status_t status, uint32_t timeout);
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
#endif	/* __ALD_QSPI_H__ */
