/** @file reg_esm.h
*   @brief ESM Register Layer Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the ESM driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __REG_ESM_H__
#define __REG_ESM_H__

#include "sys_common.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Esm Register Frame Definition */
/** @struct esmBase
*   @brief Esm Register Frame Definition
*
*   This type is used to access the Esm Registers.
*/
/** @typedef esmBASE_t
*   @brief Esm Register Frame Type Definition
*
*   This type is used to access the Esm Registers.
*/
typedef volatile struct esmBase
{
    uint32 EPENASET1;              /* 0x0000                 */
    uint32 EPENACLR1;              /* 0x0004                 */
    uint32 INTENASET1;             /* 0x0008                 */
    uint32 INTENACLR1;             /* 0x000C                 */
    uint32 INTLVLSET1;             /* 0x0010                 */
    uint32 INTLVLCLR1;             /* 0x0014                 */
    uint32 ESTATUS1[3U];           /* 0x0018, 0x001C, 0x0020 */
    uint32 EPSTATUS;               /* 0x0024                 */
    uint32 INTOFFH;                /* 0x0028                 */
    uint32 INTOFFL;                /* 0x002C                 */
    uint32 LTC;                    /* 0x0030                 */
    uint32 LTCPRELOAD;             /* 0x0034                 */
    uint32 KEY;                    /* 0x0038                 */
    uint32 ESTATUS2EMU;            /* 0x003C                 */
    uint32 EPENASET4;              /* 0x0040                 */
    uint32 EPENACLR4;              /* 0x0044                 */
    uint32 INTENASET4;             /* 0x0048                 */
    uint32 INTENACLR4;             /* 0x004C                 */
    uint32 INTLVLSET4;             /* 0x0050                 */
    uint32 INTLVLCLR4;             /* 0x0054                 */
    uint32 ESTATUS4[3U];           /* 0x0058, 0x005C, 0x0060 */
    uint32 ESTATUS5EMU;            /* 0x0064                 */
} esmBASE_t;

/** @def esmREG
*   @brief Esm Register Frame Pointer
*
*   This pointer is used by the Esm driver to access the Esm registers.
*/
#define esmREG ((esmBASE_t *)0xFFFFF500U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
