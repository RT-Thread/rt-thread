/** @file reg_stc.h
*   @brief STC Register Layer Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __REG_STC_H__
#define __REG_STC_H__

#include "sys_common.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Stc Register Frame Definition */
/** @struct stcBase
*   @brief STC Base Register Definition
*
*   This structure is used to access the STC module registers.
*/
/** @typedef stcBASE_t
*   @brief STC Register Frame Type Definition
*
*   This type is used to access the STC Registers.
*/
typedef volatile struct stcBase
{
    uint32 STCGCR0;		/**< 0x0000: STC Control Register 0	*/
    uint32 STCGCR1;		/**< 0x0004: STC Control Register 1 */
    uint32 STCTPR;		/**< 0x0008: STC Self-Test Run Timeout Counter Preload Register	*/
    uint32 STCCADDR;		/**< 0x000C: STC Self-Test Current ROM Address Register */
    uint32 STCCICR;		/**< 0x0010: STC Self-Test Current Interval Count Register */
    uint32 STCGSTAT;		/**< 0x0014: STC Self-Test Global Status Register */
	uint32 STCFSTAT;		/**< 0x0018: STC Self-Test Fail Status Register */
    uint32 CPU1_CURMISR3;	/**< 0x001C: STC CPU1 Current MISR Register */
    uint32 CPU1_CURMISR2;	/**< 0x0020: STC CPU1 Current MISR Register */
    uint32 CPU1_CURMISR1;	/**< 0x0024: STC CPU1 Current MISR Register */
    uint32 CPU1_CURMISR0;	/**< 0x0028: STC CPU1 Current MISR Register */
    uint32 CPU2_CURMISR3;	/**< 0x002C: STC CPU1 Current MISR Register */
    uint32 CPU2_CURMISR2;	/**< 0x0030: STC CPU1 Current MISR Register */
    uint32 CPU2_CURMISR1;	/**< 0x0034: STC CPU1 Current MISR Register */
    uint32 CPU2_CURMISR0;	/**< 0x0038: STC CPU1 Current MISR Register */
    uint32 STCSCSCR;		/**< 0x003C: STC Signature Compare Self-Check Register */
} stcBASE_t;

#define stcREG   ((stcBASE_t *)0xFFFFE600U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
