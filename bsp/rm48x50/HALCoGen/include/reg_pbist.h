/** @file reg_pbist.h
*   @brief PBIST Register Layer Header File
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

#ifndef __REG_PBIST_H__
#define __REG_PBIST_H__

#include "sys_common.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* PBIST Register Frame Definition */
/** @struct pbistBase
*   @brief PBIST Base Register Definition
*
*   This structure is used to access the PBIST module registers.
*/
/** @typedef pbistBASE_t
*   @brief PBIST Register Frame Type Definition
*
*   This type is used to access the PBIST Registers.
*/
typedef volatile struct pbistBase
{
    uint32 RAMT;			/* 0x0160: RAM Configuration Register */
    uint32 DLR;			/* 0x0164: Datalogger Register */
    uint32   rsvd1[6U];	/* 0x0168 */
    uint32 PACT;			/* 0x0180: PBIST Activate Register */
    uint32 PBISTID;		/* 0x0184: PBIST ID Register */
    uint32 OVER;			/* 0x0188: Override Register */
    uint32   rsvd2;		/* 0x018C */
    uint32 FSRF0;			/* 0x0190: Fail Status Fail Register 0 */
	uint32 FSRF1;			/* 0x0194: Fail Status Fail Register 1 */
    uint32 FSRC0;			/* 0x0198: Fail Status Count Register 0 */
    uint32 FSRC1;			/* 0x019C: Fail Status Count Register 1 */
    uint32 FSRA0;			/* 0x01A0: Fail Status Address 0 Register */
    uint32 FSRA1;			/* 0x01A4: Fail Status Address 1 Register */
    uint32 FSRDL0;		/* 0x01A8: Fail Status Data Register 0 */
    uint32   rsvd3;		/* 0x01AC */
    uint32 FSRDL1;		/* 0x01B0: Fail Status Data Register 1 */
    uint32   rsvd4[3U];	/* 0x01B4 */
    uint32 ROM;			/* 0x01C0: ROM Mask Register */
    uint32 ALGO;			/* 0x01C4: Algorithm Mask Register */
    uint32 RINFOL;		/* 0x01C8: RAM Info Mask Lower Register */
    uint32 RINFOU;		/* 0x01CC: RAM Info Mask Upper Register */
} pbistBASE_t;

#define pbistREG   ((pbistBASE_t *)0xFFFFE560U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
