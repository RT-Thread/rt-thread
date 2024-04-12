/*********************************************************************************************************//**
 * @file    ht32f5xxxx_mctm.c
 * @version $Rev:: 6421         $
 * @date    $Date:: 2022-11-03 #$
 * @brief   This file provides all the MCTM firmware functions.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f5xxxx_mctm.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup MCTM MCTM
  * @brief MCTM driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup MCTM_Private_Define MCTM private definitions
  * @{
  */
#define CTR_COMPRE          0x00000100ul
#define CTR_COMUS           0x00000200ul

#define CHBRKCTR_CHMOE      0x00000010ul
/**
  * @}
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup MCTM_Exported_Functions MCTM exported functions
  * @{
  */

/*********************************************************************************************************//**
 * @brief Configure polarity of the MCTMx channel N.
 * @param MCTMx: where MCTMx is the selected MCTM from the MCTM peripheral.
 * @param Channel: Specify the MCTM channel.
 *        This parameter can be one of the following values:
 *        @arg MCTM_CH_0 : MCTM channel 0
 *        @arg MCTM_CH_1 : MCTM channel 1
 *        @arg MCTM_CH_2 : MCTM channel 2
 *        @arg MCTM_CH_3 : MCTM channel 3
 * @param Pol: Specify the polarity of channel N.
 *        This parameter can be one of the following values:
 *        @arg MCTM_CHP_NONINVERTED : active high
 *        @arg MCTM_CHP_INVERTED    : active low
 * @retval None
 ************************************************************************************************************/
void MCTM_ChNPolarityConfig(HT_TM_TypeDef* MCTMx, TM_CH_Enum Channel, TM_CHP_Enum Pol)
{
  u32 wChpolr;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_MCTM(MCTMx));
  Assert_Param(IS_MCTM_COMPLEMENTARY_CH(Channel));
  Assert_Param(IS_TM_CHP(Pol));

  /* Set or reset the CHxN polarity                                                                         */
  wChpolr = MCTMx->CHPOLR & (~(u32)(0x2 << (Channel << 1)));
  MCTMx->CHPOLR = wChpolr | ((Pol << 1) << (Channel << 1));
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the MCTMx channel N.
 * @param MCTMx: where MCTMx is the selected MCTM from the MCTM peripheral.
 * @param Channel: Specify the MCTM channel.
 *        This parameter can be one of the following values:
 *        @arg MCTM_CH_0 : MCTM channel 0
 *        @arg MCTM_CH_1 : MCTM channel 1
 *        @arg MCTM_CH_2 : MCTM channel 2
 *        @arg MCTM_CH_3 : MCTM channel 3
 * @param Control: This parameter can be TM_CHCTL_ENABLE or TM_CHCTL_DISABLE.
 * @retval None
 ************************************************************************************************************/
void MCTM_ChannelNConfig(HT_TM_TypeDef* MCTMx, TM_CH_Enum Channel, TM_CHCTL_Enum Control)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MCTM(MCTMx));
  Assert_Param(IS_MCTM_COMPLEMENTARY_CH(Channel));
  Assert_Param(IS_TM_CHCTL(Control));

  /* Reset the CHxNE Bit                                                                                    */
  MCTMx->CHCTR &= ~(u32)(0x2 << (Channel << 1));

  /* Set or reset the CHxNE Bit                                                                             */
  MCTMx->CHCTR |= (u32)(Control << 1) << (Channel << 1);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the channels main output of the MCTMx.
 * @param MCTMx: where MCTMx is the selected MCTM from the MCTM peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void MCTM_CHMOECmd(HT_TM_TypeDef* MCTMx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MCTM(MCTMx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the MCTM Main Output                                                                          */
    MCTMx->CHBRKCTR |= CHBRKCTR_CHMOE;
  }
  else
  {
    /* Disable the MCTM Main Output                                                                         */
    MCTMx->CHBRKCTR &= ~CHBRKCTR_CHMOE;
  }
}

/*********************************************************************************************************//**
 * @brief Configure the break feature, dead time, Lock level, the OSSI, the OSSR State
 *        and the CHAOE(automatic output enable).
 * @param MCTMx: where MCTMx is the selected MCTM from the MCTM peripherals.
 * @param CHBRKCTRInit: Point to a MCTM_CHBRKCTRInitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void MCTM_CHBRKCTRConfig(HT_TM_TypeDef* MCTMx, MCTM_CHBRKCTRInitTypeDef *CHBRKCTRInit)
{
  u32 wTmpReg;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_MCTM(MCTMx));
  Assert_Param(IS_MCTM_OSSR_STATE(CHBRKCTRInit->OSSRState));
  Assert_Param(IS_MCTM_OSSI_STATE(CHBRKCTRInit->OSSIState));
  Assert_Param(IS_MCTM_LOCK_LEVEL(CHBRKCTRInit->LockLevel));
  Assert_Param(IS_MCTM_BREAK_STATE(CHBRKCTRInit->Break0));
  Assert_Param(IS_MCTM_BREAK_POLARITY(CHBRKCTRInit->Break0Polarity));
  Assert_Param(IS_MCTM_CHAOE_STATE(CHBRKCTRInit->AutomaticOutput));
  Assert_Param(IS_TM_FILTER(CHBRKCTRInit->BreakFilter));

  wTmpReg = MCTMx->CHBRKCTR & 0x00000010; // Keep CHMOE
  wTmpReg |= (u32)CHBRKCTRInit->BreakFilter << 8;
  wTmpReg |= (u32)CHBRKCTRInit->DeadTime << 24;
  wTmpReg |= CHBRKCTRInit->LockLevel | CHBRKCTRInit->OSSRState | CHBRKCTRInit->OSSIState;
  wTmpReg |= CHBRKCTRInit->Break0 | CHBRKCTRInit->Break0Polarity | CHBRKCTRInit->AutomaticOutput;

  MCTMx->CHBRKCTR = wTmpReg;
}

/*********************************************************************************************************//**
 * @brief Configure the break feature, dead time, Lock level, the OSSI, the OSSR State
 *        and the CHAOE(automatic output enable).
 * @param MCTMx: where MCTMx is the selected MCTM from the MCTM peripherals.
 * @param CHBRKCTRInit: Point to a MCTM_CHBRKCTRTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void MCTM_CHBRKCTRConfig2(HT_TM_TypeDef* MCTMx, MCTM_CHBRKCTRTypeDef *CHBRKCTRInit)
{
  u32 wTmpReg;

  wTmpReg = MCTMx->CHBRKCTR & 0x00000010; // Keep CHMOE

  wTmpReg |= CHBRKCTRInit->Reg;

  MCTMx->CHBRKCTR = wTmpReg;
}

/*********************************************************************************************************//**
 * @brief Fill each CHBRKCTRInitStruct member with its default value.
 * @param CHBRKCTRInitStruct: Point to a MCTM_CHBRKCTRInitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void MCTM_CHBRKCTRStructInit(MCTM_CHBRKCTRInitTypeDef* CHBRKCTRInitStruct)
{
  /* Set the default configuration                                                                          */
  CHBRKCTRInitStruct->OSSRState = MCTM_OSSR_STATE_DISABLE;
  CHBRKCTRInitStruct->OSSIState = MCTM_OSSI_STATE_DISABLE;
  CHBRKCTRInitStruct->LockLevel = MCTM_LOCK_LEVEL_OFF;
  CHBRKCTRInitStruct->DeadTime = 0x00;
  CHBRKCTRInitStruct->Break0 = MCTM_BREAK_DISABLE;
  CHBRKCTRInitStruct->Break0Polarity = MCTM_BREAK_POLARITY_LOW;
  CHBRKCTRInitStruct->BreakFilter = 0;
  CHBRKCTRInitStruct->AutomaticOutput = MCTM_CHAOE_DISABLE;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable MCTMx COMPRE function.
 * @param MCTMx: where MCTMx is the selected MCTM from the MCTM peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void MCTM_COMPRECmd(HT_TM_TypeDef* MCTMx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MCTM(MCTMx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the MCTM COMPRE                                                                               */
    MCTMx->CTR |= CTR_COMPRE;
  }
  else
  {
    /* Disable the MCTM COMPRE                                                                              */
    MCTMx->CTR &= ~CTR_COMPRE;
  }
}

/*********************************************************************************************************//**
 * @brief Configure the MCTMx COMUS function.
 * @param MCTMx: where MCTMx is the selected MCTM from the MCTM peripherals.
 * @param Sel: Specify the COMUS value.
 *   This parameter can be one of the following values:
 *     @arg MCTM_COMUS_STIOFF : MCTM capture/compare control bits are updated by setting the UEV2G bit only
 *     @arg MCTM_COMUS_STION  : MCTM capture/compare control bits are updated by both setting the UEV2G bit
 *                              or when a rising edge occurs on STI
 * @retval None
 ************************************************************************************************************/
void MCTM_COMUSConfig(HT_TM_TypeDef* MCTMx, MCTM_COMUS_Enum Sel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MCTM(MCTMx));
  Assert_Param(IS_MCTM_COMUS(Sel));

  if (Sel != MCTM_COMUS_STIOFF)
  {
    /* Set the MCTM COMUS bit                                                                               */
    MCTMx->CTR |= CTR_COMUS;
  }
  else
  {
    /* Clear the MCTM COMUS bit                                                                             */
    MCTMx->CTR &= ~CTR_COMUS;
  }
}

#if (LIBCFG_MCTM_UEV1DIS)
/*********************************************************************************************************//**
 * @brief Enable or Disable Overflow/Underflow update event(does not contain interrupt) of the MCTMx.
 * @param MCTMx: where MCTMx is the selected MCTM from the MCTM peripherals.
 * @param MCTM_UEV1x: MCTM_UEV1UD or MCTM_UEV1OD. Overflow/underflow request disable control.
 * @param NewState: This parameter can be SET or RESET.
 * @retval None
 ************************************************************************************************************/
void MCTM_UpdateEventDisable(HT_TM_TypeDef* MCTMx, MCTM_UEV1DIS_Enum MCTM_UEV1x, FlagStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MCTM(MCTMx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != RESET)
  {
    /* Set the update disable bit                                                                           */
    MCTMx->CNTCFR |= MCTM_UEV1x;
  }
  else
  {
    /* Reset the update disable bit                                                                         */
    MCTMx->CNTCFR &= ~MCTM_UEV1x;
  }
}
#endif
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */
