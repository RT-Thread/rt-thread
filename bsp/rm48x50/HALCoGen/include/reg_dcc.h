/** @file reg_dcc.h
*   @brief DCC Register Layer Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the DCC driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __REG_DCC_H__
#define __REG_DCC_H__

#include "sys_common.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Dcc Register Frame Definition */
/** @struct dccBase
*   @brief DCC Base Register Definition
*
*   This structure is used to access the DCC module registers.
*/
/** @typedef dccBASE_t
*   @brief DCC Register Frame Type Definition
*
*   This type is used to access the DCC Registers.
*/
typedef volatile struct dccBase
{
    uint32 GCTRL;      	/**< 0x0000: DCC Control Register		*/
    uint32 REV;      		/**< 0x0004: DCC Revision Id Register 	*/
    uint32 CNT0SEED;    	/**< 0x0008: DCC Counter0 Seed Register	*/
    uint32 VALID0SEED;    /**< 0x000C: DCC Valid0 Seed Register 	*/
    uint32 CNT1SEED;		/**< 0x0010: DCC Counter1 Seed Register 	*/
    uint32 STAT; 			/**< 0x0014: DCC Status Register 		*/
    uint32 CNT0;    		/**< 0x0018: DCC Counter0 Value Register 	*/
    uint32 VALID0;    	/**< 0x001C: DCC Valid0 Value Register 	*/
    uint32 CNT1;      	/**< 0x0020: DCC Counter1 Value Register	*/
    uint32 CLKSRC1;   	/**< 0x0024: DCC Counter1 Clock Source Selection Register 	*/
    uint32 CLKSRC0;   	/**< 0x0028: DCC Counter0 Clock Source Selection Register 	*/
} dccBASE_t;


/** @def dccREG1
*   @brief DCC1 Register Frame Pointer
*
*   This pointer is used by the DCC driver to access the dcc2 module registers.
*/
#define dccREG1   ((dccBASE_t *)0xFFFFEC00U)


/** @def dccREG2
*   @brief DCC2 Register Frame Pointer
*
*   This pointer is used by the DCC driver to access the dcc2 module registers.
*/
#define dccREG2   ((dccBASE_t *)0xFFFFF400U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
