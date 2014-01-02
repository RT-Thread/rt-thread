/**********************************************************************
* $Id$      lpc_bod.h           2011-12-09
*//**
* @file     lpc_bod.h
* @brief    Contain definitions & functions related to BOD.
* @version  1.0
* @date     09 December. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup BOD BOD (Brown-Out Detector)
 * @ingroup LPC_CMSIS_FwLib_Drivers
 * @{
 */#ifndef __LPC_BOD_H 
#define __LPC_BOD_H
#include "lpc_types.h"
/** @defgroup BOD_Private_Macros BOD Private Macros
 * @{
 */

/* --------------------- BIT DEFINITIONS -------------------------------------- */
/**********************************************************************
** Power Mode Control register definitions
**********************************************************************/
#define BOD_PCON_BODRPM    (0x01 << 2)
#define BOD_PCON_BOGD      (0x01 << 3)
#define BOD_PCON_BORD      (0x01 << 4)

/**********************************************************************
** Reset Source Identification Register definitions
**********************************************************************/
#define BOD_RSID_POR              (0x01 << 0)
#define BOD_RSID_BODR      (0x01 << 3)

/**
 * @}
 */

 /** @defgroup BOD_Public_Types BOD Public Types
 * @{
 */

/**
 * @brief The field to configurate BOD
 */

typedef struct 
{
    uint8_t Enabled;            /**< Enable BOD Circuit */
    uint8_t PowerReduced;       /**< if ENABLE, BOD will be turned off in Power-down mode or Deep Sleep mode */
                                /**< So, BOD can't be used to wake-up from these mode. */
    uint8_t ResetOnVoltageDown;     /**< if ENABLE, reset the device when the VDD(REG)(3V3) voltage < the BOD reset trip level */
}BOD_Config_Type;

/**
 * @}
 */

/* Public Functions ----------------------------------------------------------- */
/** @defgroup BOD_Public_Functions BOD Public Functions
 * @{
 */
void BOD_Init( BOD_Config_Type* pConfig );
int32_t BOD_ResetSourceStatus(void);
void BOD_ResetSourceClr(void);
/**
 * @}
 */
#endif /* end __LPC_BOD_H */
/**
 * @}
 */

/*****************************************************************************
**                            End Of File
******************************************************************************/
