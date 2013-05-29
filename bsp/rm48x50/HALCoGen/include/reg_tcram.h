/** @file reg_tcram.h
*   @brief TCRAM Register Layer Header File
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

#ifndef __REG_TCRAM_H__
#define __REG_TCRAM_H__

#include "sys_common.h"

/* Tcram Register Frame Definition */
/** @struct tcramBase
*   @brief TCRAM Wrapper Register Frame Definition
*
*   This type is used to access the TCRAM Wrapper Registers.
*/
/** @typedef tcramBASE_t
*   @brief TCRAM Wrapper Register Frame Type Definition
*
*   This type is used to access the TCRAM Wrapper Registers.
*/

typedef volatile struct tcramBase
{
    uint32 RAMCTRL;		    /* 0x0000 */
    uint32 RAMTHRESHOLD;      /* 0x0004 */
    uint32 RAMOCCUR;			/* 0x0008 */
    uint32 RAMINTCTRL;		/* 0x000C */
    uint32 RAMERRSTATUS;		/* 0x0010 */
    uint32 RAMSERRADDR;		/* 0x0014 */
    uint32   rsvd1;			/* 0x0018 */
    uint32 RAMUERRADDR;		/* 0x001C */
    uint32   rsvd2[4U];		/* 0x0020 */
    uint32 RAMTEST;			/* 0x0030 */
    uint32   rsvd3;			/* 0x0034 */
    uint32 RAMADDRDECVECT;	/* 0x0038 */
    uint32 RAMPERADDR;        /* 0x003C */
} tcramBASE_t;

#define tcram1REG ((tcramBASE_t *)(0xFFFFF800U))
#define tcram2REG ((tcramBASE_t *)(0xFFFFF900U))

#endif
