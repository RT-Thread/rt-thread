/*""FILE COMMENT""*******************************************************
* System Name	: BSC API for RX62Nxx
* File Name		: r_pdl_bsc.h
* Version		: 1.02
* Contents		: BSC API header
* Customer		: 
* Model			: 
* Order			: 
* CPU			: RX
* Compiler		: RXC
* OS			: Nothing
* Programmer	: 
* Note			: 
************************************************************************
* Copyright, 2011. Renesas Electronics Corporation
* and Renesas Solutions Corporation
************************************************************************
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FILE COMMENT END""**************************************************/

#ifndef R_PDL_BSC_H
#define R_PDL_BSC_H

#include "r_pdl_common_defs_RX62Nxx.h"

/* Function prototypes */
bool R_BSC_Create(
	uint32_t,
	uint32_t,
	uint8_t,
	void *,
	uint8_t
);
bool R_BSC_CreateArea(
	uint8_t,
	uint16_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t
);
bool R_BSC_SDRAM_CreateArea(
	uint16_t,
	uint16_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint8_t,
	uint16_t
);
bool R_BSC_Destroy(
	uint8_t
);
bool R_BSC_Control(
	uint16_t
);
bool R_BSC_GetStatus(
	uint8_t *,
	uint16_t *,
	uint8_t *
);

/* R_BSC_Create parameter options */
/* Configuration1 (pin select control) */
/* Chip select pin selection */
#define PDL_BSC_CS0_A					0x00000001ul
#define PDL_BSC_CS0_B					0x00000002ul
#define PDL_BSC_CS1_A					0x00000004ul
#define PDL_BSC_CS1_B					0x00000008ul
#define PDL_BSC_CS1_C					0x00000010ul
#define PDL_BSC_CS2_A					0x00000020ul
#define PDL_BSC_CS2_B					0x00000040ul
#define PDL_BSC_CS2_C					0x00000080ul
#define PDL_BSC_CS3_A					0x00000100ul
#define PDL_BSC_CS3_B					0x00000200ul
#define PDL_BSC_CS3_C					0x00000400ul
#define PDL_BSC_CS4_A					0x00000800ul
#define PDL_BSC_CS4_B					0x00001000ul
#define PDL_BSC_CS4_C					0x00002000ul
#define PDL_BSC_CS5_A					0x00004000ul
#define PDL_BSC_CS5_B					0x00008000ul
#define PDL_BSC_CS5_C					0x00010000ul
#define PDL_BSC_CS6_A					0x00020000ul
#define PDL_BSC_CS6_B					0x00040000ul
#define PDL_BSC_CS6_C					0x00080000ul
#define PDL_BSC_CS7_A					0x00100000ul
#define PDL_BSC_CS7_B					0x00200000ul
#define PDL_BSC_CS7_C					0x00400000ul

/* Address (A23-A16) pin selection */
#define PDL_BSC_A23_A16_A				0x00800000ul
#define PDL_BSC_A23_A16_B				0x01000000ul
                                    	
/* WAIT pin selection */            	
#define PDL_BSC_WAIT_NOT_USED			0x02000000ul
#define PDL_BSC_WAIT_A					0x04000000ul
#define PDL_BSC_WAIT_B					0x08000000ul
#define PDL_BSC_WAIT_C					0x10000000ul
#define PDL_BSC_WAIT_D					0x20000000ul

/* Configuration2 (output enable control) */                                    	
/* Address output control */        	
#define PDL_BSC_A9_A0_DISABLE			0x00000001ul
#define PDL_BSC_A9_A4_DISABLE			0x00000002ul
#define PDL_BSC_A9_A8_DISABLE			0x00000004ul
#define PDL_BSC_A10_DISABLE				0x00000008ul
#define PDL_BSC_A11_DISABLE				0x00000010ul
#define PDL_BSC_A12_DISABLE				0x00000020ul
#define PDL_BSC_A13_DISABLE				0x00000040ul
#define PDL_BSC_A14_DISABLE				0x00000080ul
#define PDL_BSC_A15_DISABLE				0x00000100ul
#define PDL_BSC_A16_DISABLE				0x00000200ul
#define PDL_BSC_A17_DISABLE				0x00000400ul
#define PDL_BSC_A18_DISABLE				0x00000800ul
#define PDL_BSC_A19_DISABLE				0x00001000ul
#define PDL_BSC_A20_DISABLE				0x00002000ul
#define PDL_BSC_A21_DISABLE				0x00004000ul
#define PDL_BSC_A22_DISABLE				0x00008000ul
#define PDL_BSC_A23_DISABLE				0x00010000ul

/* SDRAM output control */            	
#define PDL_BSC_SDRAM_PINS_DISABLE		0x00020000ul
#define PDL_BSC_SDRAM_PINS_ENABLE		0x00040000ul
#define PDL_BSC_SDRAM_DQM1_DISABLE		0x00080000ul
#define PDL_BSC_SDRAM_DQM1_ENABLE		0x00100000ul


/* Configuration3 (error control) */
/* Error monitoring */
#define PDL_BSC_ERROR_ILLEGAL_ADDRESS_ENABLE	0x01u
#define PDL_BSC_ERROR_ILLEGAL_ADDRESS_DISABLE	0x02u
#define PDL_BSC_ERROR_TIME_OUT_ENABLE			0x04u
#define PDL_BSC_ERROR_TIME_OUT_DISABLE			0x08u

/* R_BSC_CreateArea parameter options */
/* Configuration selection */
/* Bus width */
#define PDL_BSC_WIDTH_16					0x0001u
#define PDL_BSC_WIDTH_8						0x0002u
#define PDL_BSC_WIDTH_32					0x0004u
                                        	
/* Endian mode */                       	
#define PDL_BSC_ENDIAN_SAME					0x0008u
#define PDL_BSC_ENDIAN_OPPOSITE				0x0010u
                                        	
/* Write access mode */                 	
#define PDL_BSC_WRITE_BYTE					0x0020u
#define PDL_BSC_WRITE_SINGLE				0x0040u
                                        	
/* External wait control */             	
#define PDL_BSC_WAIT_DISABLE				0x0080u
#define PDL_BSC_WAIT_ENABLE					0x0100u
                                        	
/* Page access control */               	
#define PDL_BSC_PAGE_READ_DISABLE			0x0200u
#define PDL_BSC_PAGE_READ_NORMAL			0x0400u
#define PDL_BSC_PAGE_READ_CONTINUOUS		0x0800u
#define PDL_BSC_PAGE_WRITE_DISABLE			0x1000u
#define PDL_BSC_PAGE_WRITE_ENABLE			0x2000u

/* R_BSC_Control parameter options */
#define PDL_BSC_ERROR_CLEAR	 				0x0001u
#define PDL_BSC_SDRAM_INITIALIZATION		0x0002u
#define PDL_BSC_SDRAM_AUTO_REFRESH_ENABLE	0x0004u
#define PDL_BSC_SDRAM_AUTO_REFRESH_DISABLE	0x0008u
#define PDL_BSC_SDRAM_SELF_REFRESH_ENABLE	0x0010u
#define PDL_BSC_SDRAM_SELF_REFRESH_DISABLE	0x0020u
#define PDL_BSC_SDRAM_ENABLE				0x0040u
#define PDL_BSC_SDRAM_DISABLE				0x0080u
#define PDL_BSC_DISABLE_BUSERR_IRQ			0x0100u

/* R_BSC_SDRAM_CreateArea parameter options */
/* Configuration selection */
/* Bus width */
#define PDL_BSC_SDRAM_WIDTH_16				0x0001u
#define PDL_BSC_SDRAM_WIDTH_8				0x0002u
#define PDL_BSC_SDRAM_WIDTH_32				0x0004u

/* Endian mode */
#define PDL_BSC_SDRAM_ENDIAN_SAME			0x0008u
#define PDL_BSC_SDRAM_ENDIAN_OPPOSITE		0x0010u

/* Continuous access mode */
#define PDL_BSC_SDRAM_CONT_ACCESS_ENABLE	0x0020u
#define PDL_BSC_SDRAM_CONT_ACCESS_DISABLE	0x0040u

/* Address multiplex selection */
#define PDL_BSC_SDRAM_8_BIT_SHIFT			0x0080u
#define PDL_BSC_SDRAM_9_BIT_SHIFT			0x0100u
#define PDL_BSC_SDRAM_10_BIT_SHIFT			0x0200u
#define PDL_BSC_SDRAM_11_BIT_SHIFT			0x0400u

#endif
/* End of file */
