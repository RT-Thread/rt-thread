/**
  *********************************************************************************
  *
  * @file    ald_ebi.h
  * @brief   Header file of EBI module driver.
  *
  * @version V1.0
  * @date    20 Nov 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */


#ifndef __ALD_EBI_H__
#define __ALD_EBI_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup EBI
  * @{
  */

/**
  * @defgroup EBI_Public_Macros EBI Public Macros
  * @{
  */
#define EBI_NOR_SRAM_TypeDef		EBI_Bank1_TypeDef
#define EBI_NOR_SRAM_EXTENDED_TypeDef	EBI_Bank1E_TypeDef
#define EBI_NAND_TypeDef		EBI_Bank2_3_TypeDef
#define EBI_LCD_TypeDef			EBI_Bank1_LCD_TypeDef
#define EBI_NOR_SRAM_DEVICE		EBI_Bank1
#define EBI_NOR_SRAM_EXTENDED_DEVICE	EBI_Bank1E
#define EBI_NAND_DEVICE			EBI_Bank2_3
#define EBI_LCD_DEVICE			EBI_Bank1_LCD
#define EBI_NAND_BANK2			0x00000010U
#define EBI_NAND_BANK3			0x00000100U

/* PCTRLR register clear mask */
#define PCTRLR_CLEAR_MASK    ((uint32_t)(EBI_PCTRLRx_WAITEN_MSK | EBI_PCTRLRx_MEMBKEN_MSK   | \
                                      EBI_PCTRLRx_MEMTYP_MSK    | EBI_PCTRLRx_DATBUSWID_MSK | \
                                      EBI_PCTRLRx_ECCEN_MSK     | EBI_PCTRLRx_CRDLY_MSK     | \
                                      EBI_PCTRLRx_ARDLY_MSK     | EBI_PCTRLRx_ECCPSIZE_MSK))

/* PMEMR register clear mask */
#define PMEMR_CLEAR_MASK   ((uint32_t)(EBI_PMEMRx_MEMSETUP_MSK  | EBI_PMEMRx_MEMWAIT_MSK | \
                                       EBI_PMEMRx_MEMHOLD_MSK   | EBI_PMEMRx_MEMHIZT_MSK))

/* PATTR register clear mask */
#define PATTR_CLEAR_MASK   ((uint32_t)(EBI_PATTRx_ATTSETUP_MSK  | EBI_PATTRx_ATTWAIT_MSK | \
                                       EBI_PATTRx_ATTHOLD_MSK   | EBI_PATTRx_ATTHIZT_MSK))

/* BCTRLR register clear mask */
#define BCTRLR_CLEAR_MASK		((uint32_t)(EBI_BCTRLRx_FLASHACCEN_MSK  | EBI_BCTRLRx_MUXEN_MSK  | \
                                                   EBI_BCTRLRx_MEMTYP_MSK    | EBI_BCTRLRx_MEMWID_MSK    | \
                                                   EBI_BCTRLRx_BURSTEN_MSK   | EBI_BCTRLRx_WAITPOL_MSK   | \
                                                   EBI_BCTRLRx_WRAPMODE_MSK  | EBI_BCTRLRx_WAITCFG_MSK   | \
                                                   EBI_BCTRLRx_WREN_MSK      | EBI_BCTRLRx_WAITEN_MSK    | \
                                                   EBI_BCTRLRx_EXTMODEN_MSK  | EBI_BCTRLRx_ASYNCWAIT_MSK | \
                                                   EBI_BCTRLRx_RWCBURSTEN_MSK))
/* BTR register clear mask */
#define BTR_CLEAR_MASK                 ((uint32_t)(EBI_BTRx_ADDATASETUP_MSK | EBI_BTRx_ADDHOLD_MSK  | \
                                                   EBI_BTRx_DATAHOLD_MSK    | EBI_BTRx_BUSTURN_MSK  | \
                                                   EBI_BTRx_CLKDIV_MSK      | EBI_BTRx_DATALAT_MSK  | \
                                                   EBI_BTRx_ACCMODE_MSK))

/* BWRTR register clear mask */
#define BWTR_CLEAR_MASK                ((uint32_t)(EBI_BWRTRx_ADDATASETUP_MSK | EBI_BWRTRx_ADDHOLD_MSK | \
                                                   EBI_BWRTRx_DATAHOLD_MSK | EBI_BWRTRx_BUSTURN_MSK    | \
                                                   EBI_BWRTRx_ACCMODE_MSK))

#define LCDCTRL_CLEAR_MASK		((uint32_t)(EBI_LCDCTRLx_HSYNCPOL_POS | EBI_LCDCTRLx_VSYNCPOL_MSK | \
						    EBI_LCDCTRLx_DENPOL_MSK   | EBI_LCDCTRLx_LCDEN_MSK	  | \
						    EBI_LCDCTRLx_LCDINT_MSK   | EBI_LCDCTRLx_DCLKPOL_MSK  | \
						    EBI_LCDCTRLx_DATASETUP_MSK))
/**
  * @}
  */  

/** @defgroup EBI_Public_Types EBI Public Types
  * @{
  */  

/** 
  * @brief EBI Access Mode
  */
typedef enum {
	EBI_ACCESS_MODE_A = 0x0U,		/**< EBI access mode A */
	EBI_ACCESS_MODE_B = (0x1U << 28),	/**< EBI access mode B */
	EBI_ACCESS_MODE_C = (0x2U << 28),	/**< EBI access mode C */
	EBI_ACCESS_MODE_D = (0x3U << 28),	/**< EBI access mode D */
} ebi_access_mode_t;

/**
  * @brief EBI NORSRAM Timing parameters structure definition
  */
typedef struct {
	uint32_t addr_setup;	/**< Address setup HCLK cycles number, the value between 0 and 15 */
	uint32_t addr_hold;	/**< Address hold HCLK cycles number, the value between 0 and 15 */ 
	uint32_t data_setup;	/**< Data setup HCLK cycles number, the value between 1 and 255 */ 
	uint32_t bus_dur;	/**< Bus turnaround duration HCLK cycles, the value between 0 and 15 */
	uint32_t div;		/**< Defines the period of CLK clock signal, the value between 2 and 16 */
	uint32_t latency;	/**< Issue clock cycles before getting the first data, the value between  2 and 17 */
	ebi_access_mode_t mode;	/**< Specifies the asynchronous access mode */
} ald_ebi_nor_sram_timing_t;

/** 
  * @brief EBI_Wait_feature EBI Wait feature
  */
typedef enum {
	EBI_NAND_WAIT_FEATURE_DISABLE = 0x0U,		/**< NAND wait feature disable */
	EBI_NAND_WAIT_FEATURE_ENABLE  = (0x1U << 1),	/**< NAND wait feature enable */
} ebi_nand_wait_feature_t;

/** 
  * @brief EBI NAND Data Width
  */
typedef enum {
	EBI_NAND_MEM_BUS_WIDTH_8  = 0x0U,		/**< NAND mem bus width 8-bits */
	EBI_NAND_MEM_BUS_WIDTH_16 = (0x3U << 4),	/**< NAND mem bus width 16-bits */
} ebi_nand_mem_bus_width_t;

/** 
  * @brief EBI NAND ECC STATE
  */
typedef enum {
	EBI_NAND_ECC_DISABLE = 0U,		/**< NAND ecc disable */
	EBI_NAND_ECC_ENABLE  = (0x1U << 6),	/**< NAND ecc enable */
} ebi_nand_ecc_t;

/** 
  * @brief EBI ECC Page Size
  */
typedef enum {
	EBI_NAND_ECC_PAGE_SIZE_256BYTE  = 0U,		/**< NAND ecc page size 256 bytes */
	EBI_NAND_ECC_PAGE_SIZE_512BYTE  = (0x1U << 17),	/**< NAND ecc page size 512 bytes */
	EBI_NAND_ECC_PAGE_SIZE_1024BYTE = (0x2U << 17),	/**< NAND ecc page size 1024 bytes */
	EBI_NAND_ECC_PAGE_SIZE_2048BYTE = (0x3U << 17),	/**< NAND ecc page size 2048 bytes */
	EBI_NAND_ECC_PAGE_SIZE_4096BYTE = (0x4U << 17),	/**< NAND ecc page size 4096 bytes */
	EBI_NAND_ECC_PAGE_SIZE_8192BYTE = (0x5U << 17),	/**< NAND ecc page size 8192 bytes */
} ebi_md_ecc_page_size_t;

/**
  * @brief EBI NAND Configuration Structure definition
  */
typedef struct {
	uint32_t bank;			/**< Specifies the NAND memory device that will be used */
	ebi_nand_wait_feature_t wait;	/**< Enables or disables the Wait feature for the NAND Memory device */
	ebi_nand_mem_bus_width_t width;	/**< Specifies the external memory device width */
	ebi_nand_ecc_t ecc;		/**< Enables or disables the ECC computation */
	ebi_md_ecc_page_size_t size;	/**< Defines the page size for the extended ECC */
	uint32_t cle_time;		/**< Number of HCLK cycles between CLE low and RE low, the value between 0 and 255 */
	uint32_t ale_time;		/**< Number of HCLK cycles between ALE low and RE low */
} ald_ebi_nand_init_t;

/**
  * @brief EBI NAND Timing parameters structure definition
  */
typedef struct {
	uint32_t time;		/**< Number of cycles to setup address, the value between 0 and 255 */
	uint32_t wait_time;	/**< Number of HCLK cycles to assert the command ,the value between 0 and 255 */
	uint32_t hold_time;	/**< Number of HCLK cycles to hold address or data, the value between 0 and 255 */
	uint32_t hiz_time;	/**< Number of HCLK cycles data bus is kept in HiZ, the value between 0 and 255 */
} ald_ebi_nand_timing_t;

/** 
  * @brief EBI Data Address Bus Multiplexing
  */
typedef enum {
	EBI_DATA_ADDRESS_MUX_DISABLE = 0x0U,		/**< Data address mux disable */
	EBI_DATA_ADDRESS_MUX_ENABLE  = (0x1U << 1),	/**< Data address mux enable */
} ebi_data_address_mux_t;

/** 
  * @brief EBI NOR/SRAM Bank
  */
typedef enum {
	EBI_NORSRAM_BANK1 = 0x0U,	/**< Norsram bank 1 */
	EBI_NORSRAM_BANK2 = 0x2U,	/**< Norsram bank 2 */
	EBI_NORSRAM_BANK3 = 0x4U,	/**< Norsram bank 3 */
	EBI_NORSRAM_BANK4 = 0x6U,	/**< Norsram bank 4 */
} ebi_norsram_bank_t;

/** 
  * @brief EBI Memory Type
  */
typedef enum {
	EBI_MEMORY_TYPE_SRAM  = 0x0U,		/**< Memory tyepe SRAM */
	EBI_MEMORY_TYPE_PSRAM = (0x1U << 2),	/**< Memory tyepe PSRAM */
	EBI_MEMORY_TYPE_NOR   = (0x2U << 2),	/**< Memory tyepe NOR */
} ebi_memory_type_t;

/** 
  * @brief EBI NOR/SRAM Data Width
  */
typedef enum {
	EBI_NORSRAM_MEM_BUS_WIDTH_8  = 0x0U,		/**< Norsram Memory width 8-bits */
	EBI_NORSRAM_MEM_BUS_WIDTH_16 = (0x1U << 4),	/**< Norsram Memory width 16-bits */
	EBI_NORSRAM_MEM_BUS_WIDTH_32 = (0x2U << 4),	/**< Norsram Memory width 32-bits */
} ebi_norsram_mem_bus_width_t;

/** 
  * @brief  EBI NOR/SRAM Flash Access
  */
typedef enum {
	EBI_NORSRAM_FLASH_ACCESS_DISABLE = 0x0U,	/**< Norsram flash access disable */
	EBI_NORSRAM_FLASH_ACCESS_ENABLE  = (0x1U << 6),	/**< Norsram flash access enable */
} ebi_norsram_flash_access_t;

/** 
  * @brief EBI Burst Access Mode
  */
typedef enum {
	EBI_BURST_ACCESS_MODE_DISABLE = 0x0U,		/**< Burst access disable */
	EBI_BURST_ACCESS_MODE_ENABLE  = (0x1U << 8),	/**< Burst access enable */	
} ebi_burst_access_mode_t;

/** 
  * @brief EBI Wait Signal Polarity
  */
typedef enum {
	EBI_WAIT_SIGNAL_POLARITY_LOW  = 0x0U,		/**< Wait signal polarity low */
	EBI_WAIT_SIGNAL_POLARITY_HIGH = (0x1U << 9),	/**< Wait signal polarity high */
} ebi_wait_signal_polarity_t;

/** 
  * @brief EBI Wrap Mode
  */
typedef enum {
	EBI_WRAP_MODE_DISABLE = 0x0U,		/**< Wrap mode disable */
	EBI_WRAP_MODE_ENABLE  = (0x1U << 10),	/**< Wrap mode enable */
} ebi_wrap_mode_t;

/** 
  * @brief EBI Wait Timing
  */
typedef enum {
	EBI_WAIT_TIMING_BEFORE_WS = 0x0U,		/**< Wait timing before ws */
	EBI_WAIT_TIMING_DURING_WS = (0x1U << 11),	/**< Wait timing during ws */
} ebi_wait_timing_t;

/** 
  * @brief EBI Write Operation State
  */
typedef enum {
	EBI_WRITE_OPERATION_DISABLE = 0x0U,		/**< Write operation disable */
	EBI_WRITE_OPERATION_ENABLE  = (0x1U << 12),	/**< Write operation enable */
} ebi_write_operation_t;

/** 
  * @brief EBI Wait Signal
  */
typedef enum {
	EBI_WAIT_SIGNAL_DISABLE	= 0x0U,		/**< Wait signal disable */
	EBI_WAIT_SIGNAL_ENABLE	= (0x1U << 13),	/**< Wait signal enable */
} ebi_wait_signal_t;

/** 
  * @brief EBI Extended Mode
  */
typedef enum {
	EBI_EXTENDED_MODE_DISABLE = 0x0U,		/**< EBI extended mode disable */
	EBI_EXTENDED_MODE_ENABLE  = (0x1U << 14),	/**< EBI extended mode enable */
} ebi_extended_mode_t;

/** 
  * @brief EBI Asynchronous Wait
  */
typedef enum {
	EBI_ASYNCHRONOUS_WAIT_DISABLE = 0x0U,		/**< Asynchronous wait disable */
	EBI_ASYNCHRONOUS_WAIT_ENABLE  = (0x1U << 15),	/**< Asynchronous wait enable */
} ebi_asynchronous_wait_t;

/** 
  * @brief EBI Write Burst
  */
typedef enum {
	EBI_WRITE_BURST_DISABLE = 0x0U,		/**<  Write burst disable */
	EBI_WRITE_BURST_ENABLE  = (0x1U << 19),	/**<  Write burst enable */
} ebi_write_burst_t;

/** 
  * @brief  EBI PCR Memory Type
  */
typedef enum {
	EBI_PCTRLR_MEMORY_TYPE_None = 0x0U,		/**<  PCR memory type none */
	EBI_PCTRLR_MEMORY_TYPE_NAND = (0x1U << 3),	/**<  PCR memory type nand */
} ebi_pctrlr_memory_type_t;

/** 
  * @brief EBI Interrupt definition
  */
typedef enum {
	EBI_IT_RISING_EDGE  = (1U << 3),	/**<  Rising edge trigger interrupt */
	EBI_IT_LEVEL        = (1U << 4),	/**<  Level trigger interrupt */
	EBI_IT_FALLING_EDGE = (1U << 5),	/**<  Falling edge trigger interrupt */
} ebi_it_t;

/** 
  * @brief EBI Flag definition
  */
typedef enum {
	EBI_FLAG_RISING_EDGE  = (1U << 0),	/**<  Rising edge flag */
	EBI_FLAG_LEVEL        = (1U << 1),	/**<  Level flag */
	EBI_FLAG_FALLING_EDGE = (1U << 2),	/**<  Falling edge flag */
	EBI_FLAG_FEMPT        = (1U << 6),	/**<  Rising edge trigger interrupt */
} ebi_flag_t;

/** 
  * @brief EBI LCD_Horizontal Synch Polarity definition 
  */
typedef enum {
	EBI_LCD_HSYNCPOL_LOW  = 0x0U,		/**<  Horizontal synch polarity low */
	EBI_LCD_HSYNCPOL_HIGH = (0x1U << 29),	/**<  Horizontal synch polarity high */
} ebi_lcd_hsyncpol_t;

/** 
  * @brief EBI LCD Vertical Synch Polarity definition 
  */
typedef enum {
	EBI_LCD_VSYNCPOL_LOW  = 0x0U,		/**<  Vertical synch polarity low */
	EBI_LCD_VSYNCPOL_HIGH = (0x1U << 28),	/**<  Vertical synch polarity high */
} ebi_lcd_vsyncpol_t;

/** 
  * @brief EBI LCD Data Enable Polarity definition 
  */
typedef enum {
	EBI_LCD_DENPOL_LOW  = 0x0U,		/**<  LCD data enable polarity low */
	EBI_LCD_DENPOL_HIGH = (0x1U << 27),	/**<  LCD data enable polarity high */
} ebi_lcd_denpol_t;

/** 
  * @brief EBI LCD Enable definition
  */
typedef enum {
	EBI_LCD_LCDEN_DISABLE = 0x0U,		/**<  LCD disable */
	EBI_LCD_LCDEN_ENABLE  = (0x1U << 26),	/**<  LCD data enable polarity low */
} ebi_lcd_lcden_t;

/** 
  * @brief EBI LCD Init Enable definition 
  */
typedef enum {
	EBI_LCD_LCDINT_DISABLE = 0x0U,		/**<  LCD init disable */
	EBI_LCD_LCDINT_ENABLE  = (0x1 << 25),	/**<  LCD init enable */
} ebi_lcd_lcdint_t;

/** 
  * @brief EBI LCD Data Clock definition
  */
typedef enum {
	EBI_LCD_DCLKPOL_FALLING = 0x0U,		/**<  LCD data clock falling edge */
	EBI_LCD_DCLKPOL_RISING  = (0x1U << 24),	/**<  LCD data clock rising edge */
} ebi_lcd_dclkpol_t;

/**
  * @brief EBI LCD parameters structure definition
  */
typedef struct {
	uint8_t bank;			/**< Specifies the NORSRAM memory device */	
	ebi_lcd_hsyncpol_t h_polarity;	/**< Horizontal sync polarity */
	ebi_lcd_vsyncpol_t v_polarity;	/**< Vertical sync polarity */
	ebi_lcd_denpol_t data_polarity;	/**< Data enable polarity */
	ebi_lcd_lcden_t enable;		/**< LCD enable */
	ebi_lcd_dclkpol_t clk_polarity;	/**< Data clock polarity */
	ebi_lcd_lcdint_t reset;		/**< LCD Reset */
	uint8_t setup;			/**< Data setup time */
	uint8_t v_width;		/**< Vsync pulse width */
	uint8_t h_width;		/**< Hsync puluse width */
	uint16_t nr_line;		/**< Frame line number */
	uint16_t nr_pixel;		/**< Frame pixel number */
} ebi_lcd_init_t;

/** 
  * @brief  NOR LCD handle Structure definition  
  */
typedef struct {
	EBI_LCD_TypeDef *inst;
	ebi_lcd_init_t init;
} ebi_lcd_handle_t;

/**
  * @brief EBI NORSRAM Configuration Structure definition
  */
typedef struct {
	uint32_t bank;				/**< Specifies the NORSRAM memory device, the value can be one of 0 ~ 3 */
	ebi_data_address_mux_t mux;		/**< Address and data values are multiplexed or not */
	ebi_memory_type_t type;			/**< Specifies the type of external memory */ 
	ebi_norsram_mem_bus_width_t width;	/**< Specifies the external memory device width */
	ebi_burst_access_mode_t acc_mode;	/**< Enables or disables the burst access mode for Flash memory */
	ebi_wait_signal_polarity_t polarity;	/**< Wait signal polarity, valid only in burst mode */
	ebi_wrap_mode_t wrap_mode;		/**< Enables or disables the Wrapped burst access mode, only in burst mode */
	ebi_wait_timing_t active;		/**< Specifies if the wait signal is asserted, only in burst mode */
	ebi_write_operation_t write;		/**< Enables or disables the write operation */
	ebi_wait_signal_t signal;		/**< Enables or disables the wait state insertion, only in burst mode */
	ebi_extended_mode_t ext_mode;		/**< Enables or disables the extended mode */
	ebi_asynchronous_wait_t wait;		/**< Enables or disables wait signal during asynchronous transfers */
	ebi_write_burst_t burst;		/**< Enables or disables the write burst operation */
} ald_ebi_nor_sram_init_t;

/**
  * @}
  */

/** @defgroup EBI_Private_Macros EBI Private Macros
  * @{
  */
#define IS_EBI_NORSRAM_BANK(x)	(((x) == EBI_NORSRAM_BANK1) || \
				((x) == EBI_NORSRAM_BANK2) || \
				((x) == EBI_NORSRAM_BANK3) || \
				((x) == EBI_NORSRAM_BANK4))
#define IS_EBI_MUX(x)	(((x) == EBI_DATA_ADDRESS_MUX_DISABLE) || \
			((x) == EBI_DATA_ADDRESS_MUX_ENABLE))
#define IS_EBI_MEMORY(x)	(((x) == EBI_MEMORY_TYPE_SRAM) || \
				((x) == EBI_MEMORY_TYPE_PSRAM) || \
				((x) == EBI_MEMORY_TYPE_NOR))
#define IS_EBI_NORSRAM_MEMORY_WIDTH(x)	(((x) == EBI_NORSRAM_MEM_BUS_WIDTH_8)  || \
					((x) == EBI_NORSRAM_MEM_BUS_WIDTH_16) || \
					((x) == EBI_NORSRAM_MEM_BUS_WIDTH_32))
#define IS_EBI_WRITE_BURST(x)	(((x) == EBI_WRITE_BURST_DISABLE) || \
				((x) == EBI_WRITE_BURST_ENABLE))
#define IS_EBI_ACCESS_MODE(x)	(((x) == EBI_ACCESS_MODE_A) || \
				((x) == EBI_ACCESS_MODE_B) || \
				((x) == EBI_ACCESS_MODE_C) || \
				((x) == EBI_ACCESS_MODE_D))
#define IS_EBI_NAND_BANK(x)	(((x) == EBI_NAND_BANK2) || \
				((x) == EBI_NAND_BANK3))
#define IS_EBI_WAIT_FEATURE(x)	(((x) == EBI_NAND_WAIT_FEATURE_DISABLE) || \
				((x) == EBI_NAND_WAIT_FEATURE_ENABLE))
#define IS_EBI_NAND_MEMORY_WIDTH(x)	(((x) == EBI_NAND_MEM_BUS_WIDTH_8) || \
					((x) == EBI_NAND_MEM_BUS_WIDTH_16))
#define IS_EBI_ECC_STATE(x)		(((x) == EBI_NAND_ECC_DISABLE) || \
					((x) == EBI_NAND_ECC_ENABLE))
#define IS_EBI_ECCPAGE_SIZE(x)	(((x) == EBI_NAND_ECC_PAGE_SIZE_256BYTE)  || \
				((x) == EBI_NAND_ECC_PAGE_SIZE_512BYTE)  || \
				((x) == EBI_NAND_ECC_PAGE_SIZE_1024BYTE) || \
				((x) == EBI_NAND_ECC_PAGE_SIZE_2048BYTE) || \
				((x) == EBI_NAND_ECC_PAGE_SIZE_4096BYTE) || \
				((x) == EBI_NAND_ECC_PAGE_SIZE_8192BYTE))
#define IS_EBI_LCD_DEVICE(x)	((x) == EBI_LCD_DEVICE)
#define IS_EBI_HORIZONTAL_SYNCH(x)	(((x) == EBI_LCD_HSYNCPOL_LOW) || \
					((x) == EBI_LCD_HSYNCPOL_HIGH))
#define IS_EBI_VERTICAL_SYNCH(x)	(((x) == EBI_LCD_VSYNCPOL_LOW) || \
					((x) == EBI_LCD_VSYNCPOL_HIGH))
#define IS_EBI_DATA_ENABLE(x)		(((x) == EBI_LCD_DENPOL_LOW) || \
					((x) == EBI_LCD_DENPOL_HIGH))
#define IS_EBI_LCD_ENABLE(x)		(((x) == EBI_LCD_LCDEN_DISABLE) || \
					((x) == EBI_LCD_LCDEN_ENABLE))
#define IS_EBI_LCD_RESET(x)		(((x) == EBI_LCD_LCDINT_DISABLE) || \
					((x) == EBI_LCD_LCDINT_ENABLE))
#define IS_EBI_DATA_CLOCK(x)		(((x) == EBI_LCD_DCLKPOL_FALLING) || \
					((x) == EBI_LCD_DCLKPOL_RISING))
#define IS_EBI_LCD_DATASETUP_TIME(x)	((x) < 255U)
#define IS_EBI_HYSNC_PULSE_WIDTH(x)	((x) < 255U)
#define IS_EBI_VSYNC_PULSE_WIDTH(x)	((x) < 255U)
#define IS_EBI_FRAME_LINE_NUMBER(x)	(((x) >= 1U) && ((x) < 65535))
#define IS_EBI_FRAME_PIXEL_NUMBER(x)	(((x) >= 1U) && ((x) < 65535))

#define IS_EBI_TCLR_TIME(x)	((x) <= 255U)
#define IS_EBI_TAR_TIME(x)	((x) <= 255U)
#define IS_EBI_SETUP_TIME(x)	((x) <= 255U)
#define IS_EBI_WAIT_TIME(x)	((x) <= 255U)
#define IS_EBI_HOLD_TIME(x)	((x) <= 255U)
#define IS_EBI_HIZ_TIME(x)	((x) <= 255U)
#define IS_EBI_NORSRAM_DEVICE(x)	((x) == EBI_NOR_SRAM_DEVICE)
#define IS_EBI_NORSRAM_EXTENDED_DEVICE(x)	((x) == EBI_NOR_SRAM_EXTENDED_DEVICE)
#define IS_EBI_NAND_DEVICE(x)	((x) == EBI_NAND_DEVICE)
#define IS_EBI_BURSTMODE(x)	(((x) == EBI_BURST_ACCESS_MODE_DISABLE) || \
				((x) == EBI_BURST_ACCESS_MODE_ENABLE))
#define IS_EBI_WAIT_POLARITY(x) (((x) == EBI_WAIT_SIGNAL_POLARITY_LOW) || \
				((x) == EBI_WAIT_SIGNAL_POLARITY_HIGH))
#define IS_EBI_WRAP_MODE(x)	(((x) == EBI_WRAP_MODE_DISABLE) || \
				((x) == EBI_WRAP_MODE_ENABLE))
#define IS_EBI_WAIT_SIGNAL_ACTIVE(x)	(((x) == EBI_WAIT_TIMING_BEFORE_WS) || \
					((x) == EBI_WAIT_TIMING_DURING_WS))
#define IS_EBI_WRITE_OPERATION(x)	(((x) == EBI_WRITE_OPERATION_DISABLE) || \
					((x) == EBI_WRITE_OPERATION_ENABLE))
#define IS_EBI_WAITE_SIGNAL(x)	(((x) == EBI_WAIT_SIGNAL_DISABLE) || \
				((x) == EBI_WAIT_SIGNAL_ENABLE))
#define IS_EBI_EXTENDED_MODE(x)	(((x) == EBI_EXTENDED_MODE_DISABLE) || \
				((x) == EBI_EXTENDED_MODE_ENABLE))
#define IS_EBI_ASYNWAIT(x)	(((x) == EBI_ASYNCHRONOUS_WAIT_DISABLE) || \
				((x) == EBI_ASYNCHRONOUS_WAIT_ENABLE))
#define IS_EBI_CLK_DIV(x)	(((x) >= 1U) && ((x) <= 16U))
#define IS_EBI_DATA_LATENCY(x)	(((x) >= 1U) && ((x) <= 17U))
#define IS_EBI_ADDRESS_SETUP_TIME(x)	((x) <= 15U)
#define IS_EBI_ADDRESS_HOLD_TIME(x)	(((x) > 0U) && ((x) <= 15U))
#define IS_EBI_DATASETUP_TIME(x)	(((x) > 0U) && ((x) <= 255U))
#define IS_EBI_TURNAROUND_TIME(x)	((x) <= 15U)
#define IS_EBI_BANK_NUMBER(x)	(((x) > 0U) && ((x) <= 4U))
/**
  * @}
  */

/** @addtogroup EBI_Public_Functions
  * @{
  */  

/** @addtogroup EBI_Public_Functions_Group1
  * @{
  */
/* NOR-FLASH SRAM initialize functions */    
void ald_ebi_nor_sram_init(EBI_NOR_SRAM_TypeDef *dev, ald_ebi_nor_sram_init_t *init);
void ald_ebi_nor_sram_timing_init(EBI_NOR_SRAM_TypeDef *dev, ald_ebi_nor_sram_timing_t *timing, uint32_t bank);
void ald_ebi_nor_sram_ext_timing_init(EBI_NOR_SRAM_EXTENDED_TypeDef *dev, ald_ebi_nor_sram_timing_t *timing, uint32_t bank, uint32_t mode);
ald_status_t ald_ebi_nor_sram_deinit(EBI_NOR_SRAM_TypeDef *dev, EBI_NOR_SRAM_EXTENDED_TypeDef *e_dev, uint32_t bank);
/**
  * @}
  */

/** @addtogroup EBI_Public_Functions_Group2
  * @{
  */
/* NOR/SRAM Control functions */
void ald_ebi_nor_sram_enable(EBI_NOR_SRAM_TypeDef *dev, uint32_t bank);
void ald_ebi_nor_sram_disable(EBI_NOR_SRAM_TypeDef *dev, uint32_t bank);
void ald_ebi_nor_sram_write_enable(EBI_NOR_SRAM_TypeDef *dev, uint32_t bank);
void ald_ebi_nor_sram_write_disable(EBI_NOR_SRAM_TypeDef *dev, uint32_t bank);
/**
  * @}
  */

/** @addtogroup EBI_Public_Functions_Group3
  * @{
  */
/* NAND-FLASH initialize functions */  
void ald_ebi_nand_init(EBI_NAND_TypeDef *dev, ald_ebi_nand_init_t *init);
void ald_ebi_nand_comm_timing_init(EBI_NAND_TypeDef *dev, ald_ebi_nand_timing_t *timing, uint32_t bank);
void ald_ebi_nand_attr_timing_init(EBI_NAND_TypeDef *dev, ald_ebi_nand_timing_t *timing, uint32_t bank);
void ald_ebi_nand_deinit(EBI_NAND_TypeDef *dev, uint32_t bank);
/**
  * @}
  */

/** @addtogroup EBI_Public_Functions_Group4
  * @{
  */
/* NAND-FLASH control functions */    
void ald_ebi_nand_enable(EBI_NAND_TypeDef *dev, uint32_t bank);
void ald_ebi_nand_disable(EBI_NAND_TypeDef *dev, uint32_t bank);
void ald_ebi_nand_enable_it(EBI_NAND_TypeDef *dev, uint32_t bank, ebi_it_t it);
void ald_ebi_nand_disable_it(EBI_NAND_TypeDef *dev, uint32_t bank, ebi_it_t it);
void ald_ebi_nand_ecc_enable(EBI_NAND_TypeDef *dev, uint32_t bank);
void ald_ebi_nand_ecc_disable(EBI_NAND_TypeDef *dev, uint32_t bank);
ald_status_t ald_ebi_nand_get_ecc(EBI_NAND_TypeDef *dev, uint32_t *val, uint32_t bank, uint32_t timeout);
flag_status_t ald_ebi_nand_get_flag(EBI_NAND_TypeDef *dev, uint32_t bank, ebi_flag_t flag);
void ald_ebi_nand_clear_flag(EBI_NAND_TypeDef *dev, uint32_t bank, ebi_flag_t flag);
/**
  * @}
  */

/** @addtogroup EBI_Public_Functions_Group5
  * @{
  */ 
void ald_ebi_lcd_init(ebi_lcd_handle_t *hlcd);
void ald_ebi_lcd_reset(ebi_lcd_handle_t *hlcd);
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

#endif /* __ALD_EBI_H__ */
