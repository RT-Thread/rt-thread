/**********************************************************************
* $Id$      lpc_bod.c           2011-12-09
*//**
* @file     lpc_bod.c
* @brief    Contain functions related to BOD.
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
/** @addtogroup BOD
 * @{
 */
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc_libcfg.h"
#else
#include "lpc_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */
#ifdef _BOD
#include "LPC407x_8x_177x_8x.h"         /* LPC407x_8x_177x_8x Peripheral Registers */
#include "lpc_bod.h"

/* Public Functions ----------------------------------------------------------- */
/** @addtogroup BOD_Public_Functions
 * @{
 */
/*********************************************************************//**
 * @brief       Initialize BOD control register
 * @param[in]   pConfig    BOD Configuration
 * @return      None
 **********************************************************************/
void BOD_Init( BOD_Config_Type* pConfig )
{
  /* Turn on/off BOD. */
  if(pConfig->Enabled == DISABLE)
  {
    LPC_SC->PCON |= BOD_PCON_BOGD;
    return;
  }
  LPC_SC->PCON &= ~BOD_PCON_BOGD;

  /* Brown-Out Reduced Power Mode */
  if(pConfig->PowerReduced == ENABLE)
  {
       LPC_SC->PCON |= BOD_PCON_BODRPM;
  }
  else
  {
        LPC_SC->PCON &= ~BOD_PCON_BODRPM;
  }

  /* Brown-Out Reset */
  if(pConfig->ResetOnVoltageDown == DISABLE)
  {
       LPC_SC->PCON |= BOD_PCON_BORD;
  }
  else
  {
        LPC_SC->PCON &= ~BOD_PCON_BORD;
  }

  /* Enable the BOD Interrupt */
  NVIC_EnableIRQ(BOD_IRQn);

  return;
}


/*********************************************************************//**
 * @brief       Get BOD reset source status
 * @param[in]   None
 * @return      TRUE/FALSE
 **********************************************************************/
int32_t BOD_ResetSourceStatus( void )
{
   if((LPC_SC->RSID & BOD_RSID_POR) == 1)
    return DISABLE;
   return ((LPC_SC->RSID & BOD_RSID_BODR)? ENABLE:DISABLE);
}
/*********************************************************************//**
 * @brief       Clear BOD reset source bit
 * @param[in]   None
 * @return      None
 **********************************************************************/
void BOD_ResetSourceClr( void )
{
   LPC_SC->RSID |= BOD_RSID_BODR;
}
/**
 * @}
 */
#endif /*_BOD */
/**
 * @}
 */
/******************************************************************************
**                            End Of File
******************************************************************************/
