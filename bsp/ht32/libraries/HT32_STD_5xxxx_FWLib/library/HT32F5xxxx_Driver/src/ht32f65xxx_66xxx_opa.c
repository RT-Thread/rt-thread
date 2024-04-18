  /*********************************************************************************************************//**
 * @file    ht32f65xxx_66xxx_opa.c
 * @version $Rev:: 6932         $
 * @date    $Date:: 2023-05-11 #$
 * @brief   This file provides all the OPA firmware functions.
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
#include "ht32f65xxx_66xxx_opa.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup  OPA OPA
  * @brief OPA driver modules
  * @{
  */


/* Private define ------------------------------------------------------------------------------------------*/
/** @defgroup OPA_Private_Define OPA private definitions
  * @{
  */
#define OPA_ENABLE                    (0x00000001ul)
/**
  * @}
  */

/* Private variables ---------------------------------------------------------------------------------------*/
static u32 gOPAUnProtectKey = 0;

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup OPA_Exported_Functions OPA exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the OPA peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void OPA_DeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  RSTCUReset.Bit.OPA = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified OPA peripheral.
 * @param HT_OPAn: where HT_OPAn is the selected OPA from the OPA peripherals, x can be 0 or 1.
 * @param  NewState: new state of the HT_OPAn peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
************************************************************************************************************/
void OPA_Cmd(HT_OPA_TypeDef* HT_OPAn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_OPA(HT_OPAn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  HT_OPAn->CR = gOPAUnProtectKey;

  if (NewState != DISABLE)
  {
    /* Enable the selected HT_OPAn peripheral                                                               */
    HT_OPAn->CR |= OPA_ENABLE;
  }
  else
  {
    /* Disable the selected HT_OPAn peripheral                                                              */
    HT_OPAn->CR &= ~(u32)OPA_ENABLE;
  }
}

/*********************************************************************************************************//**
 * @brief Set the unprotect key.
 * @param uUnProtectKey: protect key, shall be OPA_UNPROTECT_KEY
 * @retval None
 ************************************************************************************************************/
void OPA_SetUnProtectKey(u32 uUnProtectKey)
{
  gOPAUnProtectKey = uUnProtectKey << 16;
}

/*********************************************************************************************************//**
 * @brief Protect the selected OPA before setting the OPA Control Register.
 * @param HT_OPAn: where HT_OPAn is the selected OPA from the OPA peripherals.
 * @retval None
 ************************************************************************************************************/
void OPA_ProtectConfig(HT_OPA_TypeDef* HT_OPAn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_OPA(HT_OPAn));

  /* Write any value to bit 16 ~ 31 (PROTECT) and keep the other control bir                                */
  HT_OPAn->CR = HT_OPAn->CR;
}

/*********************************************************************************************************//**
 * @brief Unprotect the selected OPA before setting the OPA Control Register.
 * @param HT_OPAn: where HT_OPAn is the selected OPA from the OPA peripherals.
 * @retval None
 ************************************************************************************************************/
void OPA_UnprotectConfig(HT_OPA_TypeDef* HT_OPAn)
{
  u32 CRValue;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_OPA(HT_OPAn));

  /* Set the unlock code corresponding to selected OPA                                                      */
  CRValue = HT_OPAn->CR & 0x0000FFFF;
  HT_OPAn->CR = gOPAUnProtectKey | CRValue;
}

#if (LIBCFG_OPA_V2)
/*********************************************************************************************************//**
 * @brief Initialize the OPA peripheral according to the specified parameters in the OPA_InitStruct.
 * @param HT_OPAn: where HT_OPAn is the selected OPA from the OPA peripherals.
 * @param OPA_InitStruct: pointer to a OPA_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void OPA_Init(HT_OPA_TypeDef* HT_OPAn, OPA_InitTypeDef* OPA_InitStruct)
{
  /* !!! NOTICE !!!
     Must call the following functions first.
       OPA_SetUnProtectKey(OPA_UNPROTECT_KEY);
       OPA_UnprotectConfig();
  */

  /* Check the parameters                                                                                   */
  Assert_Param(IS_OPA(HT_OPAn));
  Assert_Param(IS_OPA_ScalerEnable(OPA_InitStruct->OPA_ScalerEnable));
  Assert_Param(IS_OPA_ExtPinEnable(OPA_InitStruct->OPA_ExternalPinEnable));
  #if (LIBCFG_OPA_PGA)
  Assert_Param(IS_OPA_PGAEnable(OPA_InitStruct->OPA_PGAEnable));
  Assert_Param(IS_OPA_UnitGainEnable(OPA_InitStruct->OPA_UnitGainEnable));
  Assert_Param(IS_OPA_PGA_SEL(OPA_InitStruct->OPA_PGAGain));
  #endif

  #if (LIBCFG_OPA_PGA)
  /* avoid both PGA and unit gain active at the same time                                                   */
  if (OPA_InitStruct->OPA_UnitGainEnable == OPA_UNITGAIN_ENABLE)
  {
    OPA_InitStruct->OPA_PGAEnable = OPA_PGA_DISABLE;
  }
  #endif

  #if (LIBCFG_OPA_PGA)
  HT_OPAn->CR = OPA_InitStruct->OPA_ScalerEnable | OPA_InitStruct->OPA_PGAGain | \
                OPA_InitStruct->OPA_ExternalPinEnable | OPA_InitStruct->OPA_PGAEnable | \
                OPA_InitStruct->OPA_UnitGainEnable;
  #else
  HT_OPAn->CR = OPA_InitStruct->OPA_ScalerEnable | \
                OPA_InitStruct->OPA_ExternalPinEnable;
  #endif
}

/*********************************************************************************************************//**
 * @brief Fill each OPA_InitStruct member with its default value.
 * @param OPA_InitStruct: pointer to an OPA_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void OPA_StructInit(OPA_InitTypeDef* OPA_InitStruct)
{
  /* OPA_InitStruct members default value                                                                   */
  OPA_InitStruct->OPA_ScalerEnable = OPA_SCALER_DISABLE;
  OPA_InitStruct->OPA_ExternalPinEnable = OPA_ExternalPin_DISABLE;
  #if (LIBCFG_OPA_PGA)
  OPA_InitStruct->OPA_PGAEnable = OPA_PGA_DISABLE;
  OPA_InitStruct->OPA_UnitGainEnable = OPA_UNITGAIN_DISABLE;
  OPA_InitStruct->OPA_PGAGain = PGA_GAIN_6;
  #endif
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the OPA External Input.
 * @param HT_OPAn: where HT_OPAn is the selected OPA from the OPA peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void OPA_ExternalInputCmd(HT_OPA_TypeDef* HT_OPAn, ControlStatus NewState)
{
  u32 OPA_CR = (u32)(&HT_OPAn->CR);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_OPA(HT_OPAn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  HT_OPAn->CR = gOPAUnProtectKey;

  if (NewState != DISABLE)
  {
    SetBit_BB(OPA_CR, 3);
  }
  else
  {
    ResetBit_BB(OPA_CR, 3);
  }
}

#if (LIBCFG_OPA_PGA)
/*********************************************************************************************************//**
 * @brief Enable or Disable the Unit Gain.
 * @param HT_OPAn: where HT_OPAn is the selected OPA from the OPA peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void OPA_UnitGainCmd(HT_OPA_TypeDef* HT_OPAn, ControlStatus NewState)
{
  u32 OPA_CR = (u32)(&HT_OPAn->CR);
  u32 CRValue;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_OPA(HT_OPAn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  CRValue = HT_OPAn->CR & (~(0x06UL)); // reset unit gain & PGA

  if (NewState == ENABLE)
  {
    CRValue |= 0x2;
  }

  HT_OPAn->CR = gOPAUnProtectKey;
  HT_OPAn->CR = CRValue;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the PGA.
 * @param HT_OPAn: where HT_OPAn is the selected OPA from the OPA peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void OPA_PGACmd(HT_OPA_TypeDef* HT_OPAn, ControlStatus NewState)
{
  u32 OPA_CR = (u32)(&HT_OPAn->CR);
  u32 CRValue;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_OPA(HT_OPAn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  CRValue = HT_OPAn->CR & (~(0x06UL)); // reset unit gain & PGA

  if (NewState == ENABLE)
  {
    CRValue |= 0x4; // set PGA
  }

   HT_OPAn->CR = gOPAUnProtectKey;
   HT_OPAn->CR = CRValue;
}

/*********************************************************************************************************//**
 * @brief  Configure the Gain Selection for the PGA.
 * @param  HT_OPAn: where HT_OPAn is the selected OPA from the OPA peripherals.
 * @param  GAIN_SEL :
 *   This parameter can be one of the following value:
 *     @arg PGA_GAIN_6 :
 *     @arg PGA_GAIN_8 :
 *     @arg PGA_GAIN_12 :
 *     @arg PGA_GAIN_16 :
 *     @arg PGA_GAIN_24 :
 *     @arg PGA_GAIN_32 :
 *     @arg PGA_GAIN_48 :
 *     @arg PGA_GAIN_64 :
 *     @arg PGA_GAIN_5 :
 *     @arg PGA_GAIN_7 :
 *     @arg PGA_GAIN_11 :
 *     @arg PGA_GAIN_15 :
 *     @arg PGA_GAIN_23 :
 *     @arg PGA_GAIN_31 :
 *     @arg PGA_GAIN_47 :
 *     @arg PGA_GAIN_63 :
 * @retval None
 ************************************************************************************************************/
void OPA_PGAGain(HT_OPA_TypeDef* HT_OPAn, u8 bGAIN_SEL)
{
  u32 CRValue;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_OPA(HT_OPAn));
  Assert_Param(IS_OPA_PGA_SEL(bGAIN_SEL));

  CRValue = HT_OPAn->CR & (~0x70UL);
  CRValue |= (u32)bGAIN_SEL << 4;

  HT_OPAn->CR = gOPAUnProtectKey;
  HT_OPAn->CR = CRValue;
}
#endif

/*********************************************************************************************************//**
 * @brief Enable or Disable the 10bit Scaler.
 * @param HT_OPAn: where HT_OPAn is the selected OPA from the OPA peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void OPA_ScalerCmd(HT_OPA_TypeDef* HT_OPAn, ControlStatus NewState)
{
  u32 OPA_CR = (u32)(&HT_OPAn->CR);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_OPA(HT_OPAn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  HT_OPAn->CR = gOPAUnProtectKey;

  if (NewState != DISABLE)
  {
    SetBit_BB(OPA_CR, 8);
  }
  else
  {
    ResetBit_BB(OPA_CR, 8);
  }
}

/*********************************************************************************************************//**
 * @brief  Set the specified reference value in the data register of the scaler.
 * @param  HT_OPAn: where HT_OPAn is the selected OPA from the OPA peripherals.
 * @param  Scaler_Value: value to be loaded in the selected data register.
 * @retval None
 ************************************************************************************************************/
void OPA_SetScalerValue(HT_OPA_TypeDef* HT_OPAn, u32 Scaler_Value)
{
   /* Check the parameters                                                                                  */
  Assert_Param(IS_OPA(HT_OPAn));
  Assert_Param(IS_OPA_SCALER_VALUE(Scaler_Value));

  HT_OPAn->DAC = Scaler_Value;
}

/*********************************************************************************************************//**
 * @brief Get the output status of the specified HT_OPAn.
 * @param HT_OPAn: where CMPx is the selected OPA from the OPA peripherals.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus OPA_GetOutputStatus(HT_OPA_TypeDef* HT_OPAn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_OPA(HT_OPAn));

  if ((HT_OPAn-> CR & OPA_OUTPUT_HIGH) != 0)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Select OPA Operation Mode.
 * @param HT_OPAn: where HT_OPAn is the selected OPA from the OPA peripherals.
 * @param MODE:
 *   This parameter can be one of the following value:
 *     @arg OPA_OFFSET_CALIBRATION_MODE :
 *     @arg OPA_NORMAL_MODE :
 * @retval None
 ************************************************************************************************************/
void OPA_OFMMode(HT_OPA_TypeDef* HT_OPAn, u8 MODE)
{
  u32 OPA_VOS = (u32)(&HT_OPAn->VOS);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_OPA(HT_OPAn));
  Assert_Param(IS_OPA_OFMMODE(MODE));

  if (MODE != OPA_NORMAL_MODE)
  {
    SetBit_BB(OPA_VOS, 7);
  }
  else
  {
    ResetBit_BB(OPA_VOS, 7);
  }
}

/*********************************************************************************************************//**
 * @brief Select OPA Operation Mode.
 * @param HT_OPAn: where HT_OPAn is the selected OPA from the OPA peripherals.
 * @param SEL:
 *   This parameter can be one of the following value:
 *     @arg OPA_INPUT_OFFSET_INN :
 *     @arg OPA_INPUT_OFFSET_INP :
 * @retval None
 ************************************************************************************************************/
void OPA_OFM_InputOffsetReferenceSelect(HT_OPA_TypeDef* HT_OPAn, u8 SEL)
{
  u32 OPA_VOS = (u32)(&HT_OPAn->VOS);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_OPA(HT_OPAn));
  Assert_Param(IS_OPA_INPUTOFFSET_SEL(SEL));

  if (SEL != OPA_INPUT_OFFSET_INN)
  {
    SetBit_BB(OPA_VOS, 6);
  }
  else
  {
    ResetBit_BB(OPA_VOS, 6);
  }
}

/*********************************************************************************************************//**
 * @brief  Configure the input offset calibration voltage for the OPA.
 * @param  HT_OPAn: where HT_OPAn is the selected OPA from the OPA peripherals.
 * @param  Data: Set the input offset calibration voltage value.
 * @retval None
 ************************************************************************************************************/
void OPA_SetInputOffsetVoltage(HT_OPA_TypeDef* HT_OPAn, u8 Data)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_OPA(HT_OPAn));
  Assert_Param(IS_OPA_INPUTOFFSET_VALUE(Data));

  HT_OPAn->VOS = (HT_OPAn->VOS & 0xFFFFFF70) | (Data & 0x1F);
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
