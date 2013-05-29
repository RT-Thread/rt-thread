/** @file reg_pmm.h
*   @brief PMM Register Layer Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   .
*   which are relevant for the PMM driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __REG_PMM_H__
#define __REG_PMM_H__

#include "sys_common.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Pmm Register Frame Definition */
/** @struct pmmBase
*   @brief Pmm Register Frame Definition
*
*   This type is used to access the Pmm Registers.
*/
/** @typedef pmmBase_t
*   @brief Pmm Register Frame Type Definition
*
*   This type is used to access the Pmm Registers.
*/
typedef volatile struct pmmBase
{
	uint32 LOGICPDPWRCTRL0;		/**< 0x0000: Logic Power Domain Control Register 0 */	
    uint32   rsvd1[3U];			/**< 0x0004: Reserved*/
	uint32 MEMPDPWRCTRL0;		/**< 0x0010: Memory Power Domain Control Register 0 */
    uint32   rsvd2[3U];			/**< 0x0014: Reserved*/
    uint32 PDCLKDISREG;			/**< 0x0020: Power Domain Clock Disable Register */
    uint32 PDCLKDISSETREG;		/**< 0x0024: Power Domain Clock Disable Set Register */
    uint32 PDCLKDISCLRREG;		/**< 0x0028: Power Domain Clock Disable Clear Register */
    uint32   rsvd3[5U];			/**< 0x002C: Reserved */
    uint32 LOGICPDPWRSTAT[4U]; 	/**< 0x0040, 0x0044, 0x0048, 0x004C: Logic Power Domain Power Status Register 
										- 0: PD2
										- 1: PD3
										- 2: PD4
										- 3: PD5 */
    uint32   rsvd4[12U];		/**< 0x0050: Reserved*/
    uint32 MEMPDPWRSTAT[3U];	/**< 0x0080, 0x0084, 0x0088: Memory Power Domain Power Status Register 
										- 0: RAM_PD1
										- 1: RAM_PD2
										- 2: RAM_PD3 */
    uint32   rsvd5[5U];			/**< 0x008C: Reserved */
    uint32 GLOBALCTRL1;			/**< 0x00A0: Global Control Register 1 */
    uint32   rsvd6;				/**< 0x00A4: Reserved */
    uint32 GLOBALSTAT;			/**< 0x00A8: Global Status Register */
    uint32 PRCKEYREG;			/**< 0x00AC: PSCON Diagnostic Compare Key Register */
    uint32 LPDDCSTAT1;			/**< 0x00B0: LogicPD PSCON Diagnostic Compare Status Register 1 */
    uint32 LPDDCSTAT2;			/**< 0x00B4: LogicPD PSCON Diagnostic Compare Status Register 2 */
    uint32 MPDDCSTAT1;			/**< 0x00B8: Memory PD PSCON Diagnostic Compare Status Register 1 */
    uint32 MPDDCSTAT2;			/**< 0x00BC: Memory PD PSCON Diagnostic Compare Status Register 2 */
    uint32 ISODIAGSTAT;			/**< 0x00C0: Isolation Diagnostic Status Register */
}pmmBase_t;


/** @def pmmREG
*   @brief Pmm Register Frame Pointer
*
*   This pointer is used by the Pmm driver to access the Pmm registers.
*/
#define pmmREG ((pmmBase_t *)0xFFFF0000U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
