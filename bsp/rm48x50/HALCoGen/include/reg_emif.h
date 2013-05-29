/** @file reg_emif.h
*   @brief EMIF Register Layer Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the EMIF driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __REG_EMIF_H__
#define __REG_EMIF_H__

#include "sys_common.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Emif Register Frame Definition */
/** @struct emifBASE_t
*   @brief emifBASE Register Definition
*
*   This structure is used to access the EMIF module registers.
*/
typedef volatile struct emifBase
{
    uint32 MIDR;          /**< 0x0000 Module ID Register */
    uint32 AWCC;          /**< 0x0004 Asynchronous wait cycle register*/
    uint32 SDCR;          /**< 0x0008 SDRAM configuration register */
    uint32 SDRCR ;        /**< 0x000C Set Interrupt Enable Register */
    uint32 CE2CFG;        /**< 0x0010 Asynchronous 1 Configuration Register */
    uint32 CE3CFG;        /**< 0x0014 Asynchronous 2 Configuration Register */
    uint32 CE4CFG;        /**< 0x0018 Asynchronous 3 Configuration Register */
    uint32 CE5CFG;        /**< 0x001C Asynchronous 4 Configuration Register */
    uint32 SDTIMR;        /**< 0x0020 SDRAM Timing Register */
    uint32 dummy1[6];     /** reserved **/
    uint32 SDSRETR;       /**< 0x003c SDRAM Self Refresh Exit Timing Register */
    uint32 INTRAW;        /**< 0x0040 0x0020 Interrupt Vector Offset*/
    uint32 INTMSK;        /**< 0x0044 EMIF Interrupt Mask Register */
    uint32 INTMSKSET;     /**< 48 EMIF Interrupt Mask Set Register */
    uint32 INTMSKCLR;     /**< 0x004c EMIF Interrupt Mask Register */
    uint32 dummy2[6];     /** reserved **/
    uint32 PMCR;          /**< 0x0068 Page Mode Control Register*/

} emifBASE_t;

#define emifREG ((emifBASE_t *)0xFCFFE800U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
