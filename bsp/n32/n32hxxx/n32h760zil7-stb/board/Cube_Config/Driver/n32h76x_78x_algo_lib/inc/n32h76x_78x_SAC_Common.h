/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_SAC_Common.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __SAC_Common_H
#define __SAC_Common_H
#include <stdint.h>
//#include "ns3610.h"

/** 
 * @file SAC_Common.h 
 * @brief Declaring registers related to SAC module.
 * @author Nations
 * @version V0.1
 * @date 7th Dec, 2022
 */

#define SDPU_BASE               (0x400F2000)
#define SDMA_BASE               (SDPU_BASE)//(AHB2PERIPH_BASE + 0x2000):0x400F2000
#define SAC_BASE                (SDPU_BASE + 0x1000)
#define RNG_BASE                (SDPU_BASE + 0x1080)
typedef struct
{
	 volatile uint32_t SACCR ;//0
	 volatile uint32_t SACSR;//4
	 volatile uint32_t RESERVED0;//8
	 volatile uint32_t SACSFR1;//C
}SAC_TypeDef;

typedef struct
{
	volatile  uint32_t SDMACR;//0
	 volatile uint32_t SDMACH0SRCADDR;//4
	volatile  uint32_t SDMACH1DSTADDR;//8
	volatile  uint32_t RESERVED0;//C
	 volatile uint32_t RESERVED1;//10
	 volatile uint32_t SDMACHCTRL;//14
	 volatile uint32_t SDMAINTSTATUS;//18
	 volatile uint32_t SDMAINTEN;//1C
	 volatile uint32_t SDMACRCVALUE0;//20
   volatile uint32_t SDMACRCVALUE1;//24	
}SDMA_TypeDef;

typedef struct
{
	 volatile uint32_t RNGCCTRL;//0
	 volatile uint32_t RNGSTATE;//4
	 volatile uint32_t RNGDATA1;//8
	 volatile uint32_t RNGDRNGSEED;//c	
	 volatile uint32_t RNGDRNGSEED1;//10
	 volatile uint32_t RNGINTOUTEN;//14
	
}RNG_TypeDef;

#define SAC                     ((SAC_TypeDef * ) SAC_BASE)   
#define SDMA                    ((SDMA_TypeDef * ) SDMA_BASE)
#define RNG                     ((RNG_TypeDef * ) RNG_BASE)
#define REG32( addr )			(*(volatile uint32_t *)(addr))
#define SACP1ADR                REG32(SDPU_BASE + 0x1040)
#define SACP2ADR                REG32(SDPU_BASE + 0x1044)
#define SACP3ADR                REG32(SDPU_BASE + 0x1048)
#define SACKADR                 REG32(SDPU_BASE + 0x104C)
#define SACIADR                 REG32(SDPU_BASE + 0x1050)
#define SACOADR                 REG32(SDPU_BASE + 0x1054)
#define SACCNTADR               REG32(SDPU_BASE + 0x1058)
#define RNGINTEN                REG32((SDPU_BASE + 0x1094))
#define SDPU_M7_EN              REG32 (0x580300B0)
#define RNG_En        REG32 (0x58030170)
#define AFEC_RNG      REG32 (0x58000434)


#endif
