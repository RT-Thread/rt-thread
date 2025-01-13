/*********************************************************************************************************//**
 * @file    ht32f65xxx_66xxx_pga.c
 * @version $Rev:: 8260         $
 * @date    $Date:: 2024-11-05 #$
 * @brief   This file provides all the PGA firmware functions.
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
#include "ht32f65xxx_66xxx_pga.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup PGA PGA
  * @brief PGA driver modules
  * @{
  */

/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup PGA_Private_Define PGA private definitions
  * @{
  */
#define PGA_ENABLE                               (0x00000001ul)

#define CR_REF_POS                               10
#define CR_HVDDA_POS                             8

#define CR_OUTPUT_HIGH                           (1)
#define CR_OUTPUT_POS                            7

#define CR_GAIN_POS                              4
#define CR_GAIN_MASK                             (0x7ul << CR_GAIN_POS)

#define CR_NE_POS                                3

#define CR_PGA_POS                               2

#define CR_NUG_POS                               1

#define VOS_OFM_CALIBRATION_MODE                 (1)
#define VOS_OFM_POS                              7

#define VOS_RSP_POS                              6

#define VOS_OF_DEFAULT_VALUE                     (0x10)
#define VOS_OF_POS                               0
#define VOS_OF_MASK                              (0x1Ful << VOS_OF_POS)

#define VR_VFEN_SET                              ((u32)0x00000001)
#define VR_VFEN_RESET                            ((u32)0xFFFFFFFE)

#define PGA0_OF_WITH_CALIBRATION              0x1
#define PGA1_OF_WITH_CALIBRATION              0x2
#define PGA2_OF_WITH_CALIBRATION              0x4
#define PGA3_OF_WITH_CALIBRATION              0x8
/**
  * @}
  */
/* Private macro -------------------------------------------------------------------------------------------*/
/** @defgroup PGA_Private_Macro PGA private macros
  * @{
  */
#define IS_PGA0(x)                               (x == HT_PGA0)
#if (LIBCFG_PGA1)
#define IS_PGA1(x)                               (x == HT_PGA1)
#else
#define IS_PGA1(x)                               (0)
#endif
#if (LIBCFG_PGA2)
#define IS_PGA2(x)                               (x == HT_PGA2)
#else
#define IS_PGA2(x)                               (0)
#endif
#if (LIBCFG_PGA3)
#define IS_PGA3(x)                               (x == HT_PGA3)
#else
#define IS_PGA3(x)                               (0)
#endif
#define IS_PGA(x)                                (IS_PGA0(x) || \
                                                  IS_PGA1(x) || \
                                                  IS_PGA2(x) || \
                                                  IS_PGA3(x))

#define IS_PGA_HVDDA_OPTION(x)                   ((x == PGA_HVDDA_DISABLE) || \
                                                  (x == PGA_HVDDA_RESISTOR) || \
                                                  (x == PGA_HVDDA_POS_INPUT))

#define IS_PGA_GAIN(x)                           ((x == PGA_GAIN_LEVEL_0) || \
                                                  (x == PGA_GAIN_LEVEL_1) || \
                                                  (x == PGA_GAIN_LEVEL_2) || \
                                                  (x == PGA_GAIN_LEVEL_3) || \
                                                  (x == PGA_GAIN_LEVEL_4) || \
                                                  (x == PGA_GAIN_LEVEL_5))

#define IS_PGA_INPUT(x)                          ((x == PGA_INPUT_NEGATIVE)  || \
                                                  (x == PGA_INPUT_POSITIVE))

/**
  * @}
  */

/* Private variables ---------------------------------------------------------------------------------------*/
static u32 gPGAUnProtectKey = 0;
static vu32 gPGACaliValInit = 0;

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup PGA_Exported_Functions PGA exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the PGA peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void PGA_DeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  RSTCUReset.Bit.PGA = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);

  gPGACaliValInit = 0;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified PGA peripheral.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
*************************************************************************************************************/
void PGA_Cmd(HT_PGA0_X_TypeDef* HT_PGAn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  HT_PGAn->CR = gPGAUnProtectKey;

  if (NewState != DISABLE)
  {
    /* Enable the selected HT_PGAn peripheral                                                               */
    HT_PGAn->CR |= PGA_ENABLE;
  }
  else
  {
    /* Disable the selected HT_PGAn peripheral                                                              */
    HT_PGAn->CR &= ~(u32)PGA_ENABLE;
  }
}

/*********************************************************************************************************//**
 * @brief Set the unprotect key.
 * @param uUnProtectKey: protect key, shall be PGA_UNPROTECT_KEY
 * @retval None
 ************************************************************************************************************/
void PGA_SetUnProtectKey(u32 uUnProtectKey)
{
  gPGAUnProtectKey = uUnProtectKey << 16;
}

/*********************************************************************************************************//**
 * @brief Protect the selected PGA before setting the PGA Control Register.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @retval None
 ************************************************************************************************************/
void PGA_ProtectConfig(HT_PGA0_X_TypeDef* HT_PGAn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));

  /* Write any value to bit 16 ~ 31 (PROTECT) and keep the other control bit                                */
  HT_PGAn->CR = HT_PGAn->CR;
}

/*********************************************************************************************************//**
 * @brief Unprotect the selected PGA before setting the PGA Control Register.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @retval None
 ************************************************************************************************************/
void PGA_UnprotectConfig(HT_PGA0_X_TypeDef* HT_PGAn)
{
  u32 CRValue;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));

  /* Set the unlock code corresponding to selected PGA                                                      */
  CRValue = HT_PGAn->CR & 0x0000FFFF;
  HT_PGAn->CR = gPGAUnProtectKey | CRValue;
}

/*********************************************************************************************************//**
 * @brief Initialize the PGA peripheral according to the specified parameters in the PGA_InitStruct.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @param PGA_InitStruct: pointer to a PGA_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void PGA_Init(HT_PGA0_X_TypeDef* HT_PGAn, PGA_InitTypeDef* PGA_InitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));
  Assert_Param(IS_PGA_HVDDA_OPTION(PGA_InitStruct->PGA_HVDDA));

  /* According to the HT_PGAn calibration value flag, initialize the calibration value to 0x10 if needed.   */
  if((HT_PGAn == HT_PGA0) && !(gPGACaliValInit & PGA0_OF_WITH_CALIBRATION))
  {
    HT_PGA0->VOS = 0x00000090;
    HT_PGA0->VOS &= 0xFFFFFF7F;
  }
  #if (LIBCFG_PGA1)
  else if((HT_PGAn == HT_PGA1) && !(gPGACaliValInit & PGA1_OF_WITH_CALIBRATION))
  {
    HT_PGA1->VOS = 0x00000090;
    HT_PGA1->VOS &= 0xFFFFFF7F;
  }
  #endif
  #if (LIBCFG_PGA2)
  else if((HT_PGAn == HT_PGA2) && !(gPGACaliValInit & PGA2_OF_WITH_CALIBRATION))
  {
    HT_PGA2->VOS = 0x00000090;
    HT_PGA2->VOS &= 0xFFFFFF7F;
  }
  #endif
  #if (LIBCFG_PGA3)
  else if((HT_PGAn == HT_PGA3) && !(gPGACaliValInit & PGA3_OF_WITH_CALIBRATION))
  {
    HT_PGA3->VOS = 0x00000090;
    HT_PGA3->VOS &= 0xFFFFFF7F;
  }
  #endif

  HT_PGAn->CR = gPGAUnProtectKey;

  HT_PGAn->CR = (u32)PGA_InitStruct->PGA_REF   << CR_REF_POS | \
                (u32)PGA_InitStruct->PGA_NUG   << CR_NUG_POS | \
                (u32)PGA_InitStruct->PGA_NE    << CR_NE_POS  | \
                (u32)PGA_InitStruct->PGA_PGA   << CR_PGA_POS | \
                (u32)PGA_InitStruct->PGA_HVDDA << CR_HVDDA_POS;
}

/*********************************************************************************************************//**
 * @brief Fill each PGA_InitStruct member with its default value.
 * @param PGA_InitStruct: pointer to an PGA_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void PGA_StructInit(PGA_InitTypeDef* PGA_InitStruct)
{
  /* PGA_InitStruct members default value                                                                   */
  PGA_InitStruct->PGA_REF   = DISABLE;
  PGA_InitStruct->PGA_NUG   = DISABLE;
  PGA_InitStruct->PGA_NE    = DISABLE;
  PGA_InitStruct->PGA_PGA   = DISABLE;
  PGA_InitStruct->PGA_HVDDA = PGA_HVDDA_DISABLE;
}

/*********************************************************************************************************//**
 * @brief Configure the Gain for the selected PGA Control Register.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @param PGA_GAIN_LEVEL_x: Where PGA_GAIN_LEVEL_x is the Gain for PGA resistor.
 *   This parameter can be one of the following values:
 *     @arg PGA_GAIN_LEVEL_0
 *     @arg PGA_GAIN_LEVEL_1
 *     @arg PGA_GAIN_LEVEL_2
 *     @arg PGA_GAIN_LEVEL_3
 *     @arg PGA_GAIN_LEVEL_4
 *     @arg PGA_GAIN_LEVEL_5
 * @retval None
 ************************************************************************************************************/
void PGA_GainConfig(HT_PGA0_X_TypeDef* HT_PGAn, u32 PGA_GAIN_LEVEL_x)
{
  u32 CRValue;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));
  Assert_Param(IS_PGA_GAIN(PGA_GAIN_LEVEL_x));

  CRValue = HT_PGAn->CR & 0x0000FFFF;
  CRValue &= ~CR_GAIN_MASK;

  HT_PGAn->CR = gPGAUnProtectKey;
  HT_PGAn->CR = ((u32)PGA_GAIN_LEVEL_x << CR_GAIN_POS) | CRValue;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the PGAHVDDA Voltage Follower.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
*************************************************************************************************************/
void PGA_HVDDACmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if(NewState != DISABLE)
  {
    /* Enable the selected HT_PGAn peripheral                                                               */
    HT_PGA->VR |= (u32)VR_VFEN_SET;
  }
  else
  {
    /* Disable the selected HT_PGAn peripheral                                                              */
    HT_PGA->VR &= (u32)VR_VFEN_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the Calibration mode.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
*************************************************************************************************************/
void PGA_CalibrationCmd(HT_PGA0_X_TypeDef* HT_PGAn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if(NewState != DISABLE)
  {
    HT_PGAn->VOS |= (u32)VOS_OFM_CALIBRATION_MODE << VOS_OFM_POS;
    /*
       Set the HT_PGAn calibration value flag to true to ensure that the calibration value does not change
       after executing calibration.
    */
    if(HT_PGAn == HT_PGA0)
    {
      gPGACaliValInit |= PGA0_OF_WITH_CALIBRATION;
    }
    #if (LIBCFG_PGA1)
    else if(HT_PGAn == HT_PGA1)
    {
      gPGACaliValInit |= PGA1_OF_WITH_CALIBRATION;
    }
    #endif
    #if (LIBCFG_PGA2)
    else if(HT_PGAn == HT_PGA2)
    {
      gPGACaliValInit |= PGA2_OF_WITH_CALIBRATION;
    }
    #endif
    #if (LIBCFG_PGA3)
    else if(HT_PGAn == HT_PGA3)
    {
      gPGACaliValInit |= PGA3_OF_WITH_CALIBRATION;
    }
    #endif
  }
  else
  {
    HT_PGAn->VOS &= ~((u32)VOS_OFM_CALIBRATION_MODE << VOS_OFM_POS);
  }
}

/*********************************************************************************************************//**
 * @brief Configure the direction of Calibration reference pins.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @param PGA_INPUT_x: where PGA_INPUT_x is the calibration reference.
 *   This parameter can be one of the following values:
 *     @arg PGA_INPUT_NEGATIVE
 *     @arg PGA_INPUT_POSITIVE
 * @retval None
*************************************************************************************************************/
void PGA_SetCalibrationInput(HT_PGA0_X_TypeDef* HT_PGAn, PGA_CALIBRATION_INPUT_Enum PGA_INPUT_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));
  Assert_Param(IS_PGA_INPUT(PGA_INPUT_x));

  if(PGA_INPUT_x == PGA_CALIBRATION_INPUT_NEGATIVE)
  {
    PGA_UnprotectConfig(HT_PGAn);
    HT_PGAn->CR  |= (u32)ENABLE << CR_NE_POS;
    HT_PGAn->VOS &= ~((u32)ENABLE << VOS_RSP_POS);
  }
  else
  {
    HT_PGAn->VOS |= (u32)ENABLE << VOS_RSP_POS;
  }
}

/*********************************************************************************************************//**
 * @brief Configure the calibration value.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @param Value: the calibration value.
 * @retval None
*************************************************************************************************************/
void PGA_SetCalibrationValue(HT_PGA0_X_TypeDef* HT_PGAn, u32 Value)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));

  HT_PGAn->VOS = (HT_PGAn->VOS & ~(u32)(VOS_OF_MASK)) | Value;
}

/*********************************************************************************************************//**
 * @brief Check whether the specified PID flag has been set.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @retval None
*************************************************************************************************************/
FlagStatus PGA_ReadOutputBit(HT_PGA0_X_TypeDef* HT_PGAn)
{
  FlagStatus Status;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));

  if ((HT_PGAn->CR & ((u32)CR_OUTPUT_HIGH << CR_OUTPUT_POS)) != RESET)
  {
    Status = SET;
  }
  else
  {
    Status = RESET;
  }

  return Status;
}

/*********************************************************************************************************//**
 * @brief Set Inverting Amplifier Mode of the specified HT_PGAn.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @param PGA_GAIN_x: Where PGA_GAIN_x is the Gain for PGA resistor.
 *   This parameter can be one of the following values:
 *     @arg PGA_GAIN_6
 *     @arg PGA_GAIN_8
 *     @arg PGA_GAIN_12
 *     @arg PGA_GAIN_16
 *     @arg PGA_GAIN_24
 *     @arg PGA_GAIN_32
 * @retval None
 * @note Model configuration must follow the rules below:
 *       Inverting Amplifier Mode : The positive input must be grounded.
 ************************************************************************************************************/
void PGA_SetModeInverting(HT_PGA0_X_TypeDef* HT_PGAn, PGA_GAIN_TYPE1_Enum PGA_GAIN_x)
{
  PGA_InitTypeDef PGA_InitStruct;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));
  Assert_Param(IS_PGA_GAIN(PGA_GAIN_x));

  PGA_InitStruct.PGA_REF   = ENABLE;
  PGA_InitStruct.PGA_NUG   = DISABLE;
  PGA_InitStruct.PGA_NE    = DISABLE;
  PGA_InitStruct.PGA_PGA   = ENABLE;
  PGA_InitStruct.PGA_HVDDA = PGA_HVDDA_DISABLE;

  PGA_Init(HT_PGAn, &PGA_InitStruct);
  PGA_GainConfig(HT_PGAn, PGA_GAIN_x);
}

/*********************************************************************************************************//**
 * @brief Set the Differentiator Mode of the specified HT_PGAn.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @param PGA_GAIN_LEVEL_x: Where PGA_GAIN_LEVEL_x is the Gain for PGA resistor.
 *   This parameter can be one of the following values:
 *     @arg PGA_GAIN_LEVEL_0
 *     @arg PGA_GAIN_LEVEL_1
 *     @arg PGA_GAIN_LEVEL_2
 *     @arg PGA_GAIN_LEVEL_3
 *     @arg PGA_GAIN_LEVEL_4
 *     @arg PGA_GAIN_LEVEL_5
 * @retval None
 * @note Model configuration must follow the rules below:
 *       Differentiator           : The positive input must have an external capacitor and be grounded.
 ************************************************************************************************************/
void PGA_SetModeDifferentiator(HT_PGA0_X_TypeDef* HT_PGAn, u32 PGA_GAIN_LEVEL_x)
{
  PGA_InitTypeDef PGA_InitStruct;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));
  Assert_Param(IS_PGA_GAIN(PGA_GAIN_LEVEL_x));

  PGA_InitStruct.PGA_REF   = ENABLE;
  PGA_InitStruct.PGA_NUG   = DISABLE;
  PGA_InitStruct.PGA_NE    = DISABLE;
  PGA_InitStruct.PGA_PGA   = ENABLE;
  PGA_InitStruct.PGA_HVDDA = PGA_HVDDA_DISABLE;

  PGA_Init(HT_PGAn, &PGA_InitStruct);
  PGA_GainConfig(HT_PGAn, PGA_GAIN_LEVEL_x);
}

/*********************************************************************************************************//**
 * @brief Set the Non-Inverting Amplifier Mode of the specified HT_PGAn.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @param PGA_GAIN_x: Where PGA_GAIN_x is the Gain for PGA resistor.
 *   This parameter can be one of the following values:
 *     @arg PGA_GAIN_6
 *     @arg PGA_GAIN_8
 *     @arg PGA_GAIN_12
 *     @arg PGA_GAIN_16
 *     @arg PGA_GAIN_24
 *     @arg PGA_GAIN_32
 * @retval None
 ************************************************************************************************************/
void PGA_SetModeNonInverting(HT_PGA0_X_TypeDef* HT_PGAn, PGA_GAIN_TYPE1_Enum PGA_GAIN_x)
{
  PGA_InitTypeDef PGA_InitStruct;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));
  Assert_Param(IS_PGA_GAIN(PGA_GAIN_x));

  PGA_InitStruct.PGA_REF   = DISABLE;
  PGA_InitStruct.PGA_NUG   = DISABLE;
  PGA_InitStruct.PGA_NE    = DISABLE;
  PGA_InitStruct.PGA_PGA   = ENABLE;
  PGA_InitStruct.PGA_HVDDA = PGA_HVDDA_DISABLE;

  PGA_Init(HT_PGAn, &PGA_InitStruct);
  PGA_GainConfig(HT_PGAn, PGA_GAIN_x);
}

/*********************************************************************************************************//**
 * @brief Set the Inverting Adder Mode of the specified HT_PGAn.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @param PGA_GAIN_LEVEL_x: Where PGA_GAIN_LEVEL_x is the Gain for PGA resistor.
 *   This parameter can be one of the following values:
 *     @arg PGA_GAIN_LEVEL_0
 *     @arg PGA_GAIN_LEVEL_1
 *     @arg PGA_GAIN_LEVEL_2
 *     @arg PGA_GAIN_LEVEL_3
 *     @arg PGA_GAIN_LEVEL_4
 *     @arg PGA_GAIN_LEVEL_5
 * @retval None
 * @note Model configuration must follow the rules below:
 *       Inverting Adder Mode    : The positive input must be grounded.
 *                                 The negative input must be voltage divider.
 ************************************************************************************************************/
void PGA_SetModeInvertingAdder(HT_PGA0_X_TypeDef* HT_PGAn, u32 PGA_GAIN_LEVEL_x)
{
  PGA_InitTypeDef PGA_InitStruct;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));
  Assert_Param(IS_PGA_GAIN(PGA_GAIN_LEVEL_x));

  PGA_InitStruct.PGA_REF   = ENABLE;
  PGA_InitStruct.PGA_NUG   = DISABLE;
  PGA_InitStruct.PGA_NE    = ENABLE;
  PGA_InitStruct.PGA_PGA   = ENABLE;
  PGA_InitStruct.PGA_HVDDA = PGA_HVDDA_DISABLE;

  PGA_Init(HT_PGAn, &PGA_InitStruct);
  PGA_GainConfig(HT_PGAn, PGA_GAIN_LEVEL_x);
}

/*********************************************************************************************************//**
 * @brief Set the Exponent Amplifier Mode of the specified HT_PGAn.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @param PGA_GAIN_LEVEL_x: Where PGA_GAIN_LEVEL_x is the Gain for PGA resistor.
 *   This parameter can be one of the following values:
 *     @arg PGA_GAIN_LEVEL_0
 *     @arg PGA_GAIN_LEVEL_1
 *     @arg PGA_GAIN_LEVEL_2
 *     @arg PGA_GAIN_LEVEL_3
 *     @arg PGA_GAIN_LEVEL_4
 *     @arg PGA_GAIN_LEVEL_5
 * @retval None
 * @note Model configuration must follow the rules below:
 *       Exponent Amplifier Mode : The positive input must be grounded.
 *                                 The negative input must have an external diode.
 ************************************************************************************************************/
void PGA_SetModeExponent(HT_PGA0_X_TypeDef* HT_PGAn, u32 PGA_GAIN_LEVEL_x)
{
  PGA_InitTypeDef PGA_InitStruct;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));
  Assert_Param(IS_PGA_GAIN(PGA_GAIN_LEVEL_x));

  PGA_InitStruct.PGA_REF   = ENABLE;
  PGA_InitStruct.PGA_NUG   = DISABLE;
  PGA_InitStruct.PGA_NE    = ENABLE;
  PGA_InitStruct.PGA_PGA   = ENABLE;
  PGA_InitStruct.PGA_HVDDA = PGA_HVDDA_DISABLE;

  PGA_Init(HT_PGAn, &PGA_InitStruct);
  PGA_GainConfig(HT_PGAn, PGA_GAIN_LEVEL_x);
}

/*********************************************************************************************************//**
 * @brief Set the Manual Mode of the specified HT_PGAn.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @retval None
 * @note This mode prototype is a voltage follower, and the following modes can be used
 *       with external components:
 *       Peak Detector
 *       Active Filter
 *       R-2R D/A conversion circuit (+)
 ************************************************************************************************************/
void PGA_SetModeManual(HT_PGA0_X_TypeDef* HT_PGAn)
{
  PGA_InitTypeDef PGA_InitStruct;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));

  PGA_InitStruct.PGA_REF   = ENABLE;
  PGA_InitStruct.PGA_NUG   = ENABLE;
  PGA_InitStruct.PGA_NE    = DISABLE;
  PGA_InitStruct.PGA_PGA   = DISABLE;
  PGA_InitStruct.PGA_HVDDA = PGA_HVDDA_DISABLE;

  PGA_Init(HT_PGAn, &PGA_InitStruct);
}

/*********************************************************************************************************//**
 * @brief Set the Non-Inverting Adder Mode of the specified HT_PGAn.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @param PGA_GAIN_x: Where PGA_GAIN_x is the Gain for PGA resistor.
 *   This parameter can be one of the following values:
 *     @arg PGA_GAIN_6
 *     @arg PGA_GAIN_8
 *     @arg PGA_GAIN_12
 *     @arg PGA_GAIN_16
 *     @arg PGA_GAIN_24
 *     @arg PGA_GAIN_32
 * @retval None
 * @note Model configuration must follow the rules below:
 *       Non-Inverting Adder : The positive input must be voltage divider.
 *                             The negative input must be grounded.
 ************************************************************************************************************/
void PGA_SetModeNonInvertingAdder(HT_PGA0_X_TypeDef* HT_PGAn, PGA_GAIN_TYPE1_Enum PGA_GAIN_x)
{
  PGA_InitTypeDef PGA_InitStruct;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));
  Assert_Param(IS_PGA_GAIN(PGA_GAIN_x));

  PGA_InitStruct.PGA_REF   = DISABLE;
  PGA_InitStruct.PGA_NUG   = DISABLE;
  PGA_InitStruct.PGA_NE    = DISABLE;
  PGA_InitStruct.PGA_PGA   = ENABLE;
  PGA_InitStruct.PGA_HVDDA = PGA_HVDDA_DISABLE;

  PGA_Init(HT_PGAn, &PGA_InitStruct);
  PGA_GainConfig(HT_PGAn, PGA_GAIN_x);
}

/*********************************************************************************************************//**
 * @brief Set the Comparator Mode of the specified HT_PGAn.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @retval None
 ************************************************************************************************************/
void PGA_SetModeComparator(HT_PGA0_X_TypeDef* HT_PGAn)
{
  PGA_InitTypeDef PGA_InitStruct;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PGA(HT_PGAn));

  PGA_InitStruct.PGA_REF   = DISABLE;
  PGA_InitStruct.PGA_NUG   = DISABLE;
  PGA_InitStruct.PGA_NE    = ENABLE;
  PGA_InitStruct.PGA_PGA   = DISABLE;
  PGA_InitStruct.PGA_HVDDA = PGA_HVDDA_DISABLE;

  PGA_Init(HT_PGAn, &PGA_InitStruct);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
