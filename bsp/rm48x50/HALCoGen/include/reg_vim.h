/** @file reg_vim.h
*   @brief VIM Register Layer Header File
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

#ifndef __REG_VIM_H__
#define __REG_VIM_H__

#include "sys_common.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Vim Register Frame Definition */
/** @struct vimBase
*   @brief Vim Register Frame Definition
*
*   This type is used to access the Vim Registers.
*/
/** @typedef vimBASE_t
*   @brief VIM Register Frame Type Definition
*
*   This type is used to access the VIM Registers.
*/
typedef volatile struct vimBase
{
    uint32      IRQINDEX;         /* 0x0000        */
    uint32      FIQINDEX;         /* 0x0004        */	
    uint32        rsvd1;          /* 0x0008        */
    uint32        rsvd2;          /* 0x000C        */
    uint32      FIRQPR0;          /* 0x0010        */
    uint32      FIRQPR1;          /* 0x0014        */
    uint32      FIRQPR2;          /* 0x0018        */
    uint32      FIRQPR3;          /* 0x001C        */
    uint32      INTREQ0;          /* 0x0020        */
    uint32      INTREQ1;          /* 0x0024        */
    uint32      INTREQ2;          /* 0x0028        */
    uint32      INTREQ3;          /* 0x002C        */
    uint32      REQMASKSET0;      /* 0x0030        */
    uint32      REQMASKSET1;      /* 0x0034        */
    uint32      REQMASKSET2;      /* 0x0038        */
    uint32      REQMASKSET3;      /* 0x003C        */
    uint32      REQMASKCLR0;      /* 0x0040        */
    uint32      REQMASKCLR1;      /* 0x0044        */
    uint32      REQMASKCLR2;      /* 0x0048        */
    uint32      REQMASKCLR3;      /* 0x004C        */
    uint32      WAKEMASKSET0;     /* 0x0050        */
    uint32      WAKEMASKSET1;     /* 0x0054        */
    uint32      WAKEMASKSET2;     /* 0x0058        */
    uint32      WAKEMASKSET3;     /* 0x005C        */
    uint32      WAKEMASKCLR0;     /* 0x0060        */
    uint32      WAKEMASKCLR1;     /* 0x0064        */
    uint32      WAKEMASKCLR2;     /* 0x0068        */
    uint32      WAKEMASKCLR3;     /* 0x006C        */
    uint32      IRQVECREG;        /* 0x0070        */
    uint32      FIQVECREG;        /* 0x0074        */
    uint32      CAPEVT;           /* 0x0078        */	
    uint32        rsvd3;          /* 0x007C        */
    uint32      CHANCTRL[24U];    /* 0x0080-0x017C */
} vimBASE_t;

#define vimREG ((vimBASE_t *)0xFFFFFE00U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
