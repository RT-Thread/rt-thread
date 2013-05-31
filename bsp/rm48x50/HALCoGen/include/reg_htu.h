/** @file reg_htu.h
*   @brief HTU Register Layer Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the HTU driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __REG_HTU_H__
#define __REG_HTU_H__

#include "sys_common.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* htu Register Frame Definition */
/** @struct htuBase
*   @brief HTU Base Register Definition
*
*   This structure is used to access the HTU module registers.
*/
/** @typedef htuBASE_t
*   @brief HTU Register Frame Type Definition
*
*   This type is used to access the HTU Registers.
*/
typedef volatile struct htuBase
{
    uint32 GC;				/** 0x00 */ 
    uint32 CPENA;			/** 0x04 */ 
    uint32 BUSY0;			/** 0x08 */ 
    uint32 BUSY1;			/** 0x0C */ 
    uint32 BUSY2;			/** 0x10 */ 
    uint32 BUSY3;			/** 0x14 */ 
	uint32 ACPE;			/** 0x18 */ 
    uint32 rsvd1;    		/** 0x1C */ 
    uint32 RLBECTRL;		/** 0x20 */ 
    uint32 BFINTS;			/** 0x24 */ 
    uint32 BFINTC;			/** 0x28 */ 
    uint32 INTMAP;			/** 0x2C */ 
    uint32 rsvd2;  			/** 0x30 */ 
    uint32 INTOFF0;			/** 0x34 */ 
    uint32 INTOFF1;			/** 0x38 */ 
    uint32 BIM;				/** 0x3C */ 
    uint32 RLOSTFL;			/** 0x40 */ 
    uint32 BFINTFL;			/** 0x44 */ 
    uint32 BERINTFL;		/** 0x48 */ 
    uint32 MP1S;			/** 0x4C */ 
    uint32 MP1E;			/** 0x50 */ 
    uint32 DCTRL;			/** 0x54 */ 
    uint32 WPR;				/** 0x58 */ 
    uint32 WMR;				/** 0x5C */ 
    uint32 ID;				/** 0x60 */ 
    uint32 PCR;				/** 0x64 */ 
    uint32 PAR;				/** 0x68 */ 
    uint32 rsvd3; 			/** 0x6C */ 
    uint32 MPCS;			/** 0x70 */ 
    uint32 MP0S;			/** 0x74 */ 
    uint32 MP0E;			/** 0x78 */ 
} htuBASE_t;                        
                                    
typedef volatile struct htudcp      
{                                   
    uint32 IFADDRA;			 
    uint32 IFADDRB;			
    uint32 IHADDRCT;		
    uint32 ITCOUNT;			
} htudcp_t;                         
                                    
typedef volatile struct htucdcp     
{     
    uint32 CFADDRA;			
    uint32 CFADDRB;			
    uint32 CFCOUNT;			
    uint32 rsvd4; 			
} htucdcp_t;

#define htuREG1   ((htuBASE_t *)0xFFF7A400U)
#define htuREG2   ((htuBASE_t *)0xFFF7A500U)

#define htuDCP1   ((htudcp_t *)0xFF4E0000U)
#define htuDCP2   ((htudcp_t *)0xFF4C0000U)

#define htuCDCP1   ((htucdcp_t *)0xFF4E0100U)
#define htuCDCP2   ((htucdcp_t *)0xFF4C0100U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
