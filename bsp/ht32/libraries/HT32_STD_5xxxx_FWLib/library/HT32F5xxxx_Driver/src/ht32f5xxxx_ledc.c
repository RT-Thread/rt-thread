/*********************************************************************************************************//**
 * @file    ht32f5xxxx_ledc.c
 * @version $Rev:: 6374         $
 * @date    $Date:: 2022-10-25 #$
 * @brief   This file provides all the LEDC firmware functions.
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
#include "ht32f5xxxx_ledc.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup LEDC LEDC
  * @brief LEDC driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup LEDC_Private_Define LEDC private definitions
  * @{
  */
#define RPRE_MASK     0xF000FFFF

/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup LEDC_Exported_Functions LEDC exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the LEDC peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void LEDC_DeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};
  RSTCUReset.Bit.LEDC = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initialize the LEDC peripheral according to the specified parameters in the LEDC_InitStruct.
 * @param LEDC_InitStruct: Pointer to a LEDC_InitTypeDef structure. Please note the following.
          1. When LEDC is started, the LEDC_ClockSource, LEDC_ClockPrescaler and LEDC_DeadTime can't
                     be changed, so LEDC_Init() will turn off the LED first.You need to restart LEDC by
                     LEDC_Cmd(ENABEL).
          2. The LEDC_DeadTime number must be less than the LEDC_Prescaler.
             Example:
             If LEDC_DutyClockNumber selects LEDC_DTYNUM_8, the valid LEDC_DeadTime ranges from 0 to 7.
             If LEDC_DutyClockNumber selects LEDC_DTYNUM_16, the valid LEDC_DeadTime ranges from 0 to 15.
             If LEDC_DutyClockNumber selects LEDC_DTYNUM_32, the valid LEDC_DeadTime ranges from 0 to 31.
             If LEDC_DutyClockNumber selects LEDC_DTYNUM_64, the valid LEDC_DeadTime ranges from 0 to 63.
 * @retval None
 ************************************************************************************************************/
void LEDC_Init(LEDC_InitTypeDef* LEDC_InitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_LEDC_SRC(LEDC_InitStruct->LEDC_ClockSource));
  Assert_Param(IS_LEDC_DTYNUM(LEDC_InitStruct->LEDC_DutyClockNumber));
  Assert_Param(IS_LEDC_PSC(LEDC_InitStruct->LEDC_ClockPrescaler));
  Assert_Param(IS_LEDC_COMEN(LEDC_InitStruct->LEDC_COMxEN));
  Assert_Param(IS_LEDC_DTCR(LEDC_InitStruct->LEDC_DeadTime));

  /* Disable LEDC */
  HT_LEDC->CR = 0;

  /* LEDC Control Register Configuration */
  HT_LEDC->CR = LEDC_InitStruct->LEDC_ClockSource     << 8 |\
                LEDC_InitStruct->LEDC_DutyClockNumber << 12 |\
                LEDC_InitStruct->LEDC_ClockPrescaler  << 16;

  /* LEDC COM Enable Register Configuration */
  HT_LEDC->CER = LEDC_InitStruct->LEDC_COMxEN;

  /* LEDC  Dead Time Control Register Configuration */
  HT_LEDC->DTCR = LEDC_InitStruct->LEDC_DeadTime;
}

/*********************************************************************************************************//**
 * @brief Select the LEDC timer clock source.
 * @param Source: specify the clock source of LEDC.
 *   @arg LEDC_SRC_PCLK
 *   @arg LEDC_SRC_LSI  : Low speed internal clock.
 *   @arg LEDC_SRC_LSE  : Low speed external clock.
 * @retval None
 ************************************************************************************************************/
void LEDC_ClockSourceConfig(LEDC_SRC_Enum Source)
{
  Assert_Param(IS_LEDC_SRC(Source));

  HT_LEDC->CR = (HT_LEDC->CR & ~(3UL << 8)) | ((u32)Source << 8);
}

/*********************************************************************************************************//**
 * @brief Configure the LEDC prescaler.
 * @param Psc: Value of LEDC prescaler: 0~4095
 *   This parameter can be one of following values:
 * @retval None
 ************************************************************************************************************/
void LEDC_SetPrescaler(u32 Psc)
{
  Assert_Param(IS_LEDC_PSC(Psc));

  HT_LEDC->CR = (HT_LEDC->CR & RPRE_MASK) | (Psc << 16);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the LEDC.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void LEDC_Cmd(ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    HT_LEDC->CR |= (1UL);
  }
  else
  {
    HT_LEDC->CR &= ~(1UL);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable Frame interrupt.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void LEDC_IntConfig(ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    HT_LEDC->IER |= LEDC_INT_FRAME;
  }
  else
  {
    HT_LEDC->IER &= ~LEDC_INT_FRAME;
  }
}

/*********************************************************************************************************//**
 * @brief Get the LEDC flag.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus LEDC_GetFlagStatus(void)
{
  if (HT_LEDC->SR & LEDC_FLAG_FRAME)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear the LEDC graflag.
 * @retval None
 ************************************************************************************************************/
void LEDC_ClearFlagStatus(void)
{
  HT_LEDC->SR |= LEDC_FLAG_FRAME;
}

/*********************************************************************************************************//**
 * @brief Configure COMx's state of LEDC with specified pins.
 * @param LEDC_COMxEN: This parameter can be any combination of the following values:
 *        @arg LEDC_COM0EN : Set LEDC COM0
 *        @arg LEDC_COM1EN : Set LEDC COM1
 *        @arg LEDC_COM2EN : Set LEDC COM2
 *        @arg LEDC_COM3EN : Set LEDC COM3
 *        @arg LEDC_COM4EN : Set LEDC COM4
 *        @arg LEDC_COM5EN : Set LEDC COM5
 *        @arg LEDC_COM6EN : Set LEDC COM6
 *        @arg LEDC_COM7EN : Set LEDC COM7
 *        @arg LEDC_COM8EN : Set LEDC COM8(Only support 54253 )
 *        @arg LEDC_COM9EN : Set LEDC COM9(Only support 54253 )
 *        @arg LEDC_COM10EN : Set LEDC COM10(Only support 54253 )
 *        @arg LEDC_COM11EN : Set LEDC COM11(Only support 54253 )
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void LEDC_COMxConfig(u32 LEDC_COMxEN, ControlStatus Cmd)
{
    /* Check the parameters                                                                                   */
  Assert_Param(IS_LEDC_COMEN(LEDC_COMxEN));

  if (Cmd != DISABLE)
    HT_LEDC->CER |= LEDC_COMxEN;
  else
    HT_LEDC->CER &= ~LEDC_COMxEN;
}

/*********************************************************************************************************//**
 * @brief Configure the dead time duty. The LED brightness can be adjusted by adjusting the dead duty.
 * @param LEDC_DeadTimeDuty: Deadtime Clock Numbers. The LEDC_DeadTimeDuty number must be less than the
                             LEDC_DutyClockNumber(DTYNUM).
             Example:
             If LEDC_DutyClockNumber selects LEDC_DTYNUM_8, the valid LEDC_DeadTime ranges from 0 to 7.
             If LEDC_DutyClockNumber selects LEDC_DTYNUM_16, the valid LEDC_DeadTime ranges from 0 to 15.
             If LEDC_DutyClockNumber selects LEDC_DTYNUM_32, the valid LEDC_DeadTime ranges from 0 to 31.
             If LEDC_DutyClockNumber selects LEDC_DTYNUM_64, the valid LEDC_DeadTime ranges from 0 to 63.
 * @retval None
 ************************************************************************************************************/
void LEDC_SetDeadTimeDuty(u32 LEDC_DeadTimeDuty)
{
    /* Check the parameters                                                                                 */
  Assert_Param(IS_LEDC_DTCR(LEDC_DeadTimeDuty));

  HT_LEDC->DTCR = LEDC_DeadTimeDuty;
}

/*********************************************************************************************************//**
 * @brief Set the output polarity of COM and SEG.
 * @param LEDC_COMxPOL: This parameter can be any combination of the following values:
 *        @arg LEDC_COM0POL : Set COM0 polarity
 *        @arg LEDC_COM1POL : Set COM1 polarity
 *        @arg LEDC_COM2POL : Set COM2 polarity
 *        @arg LEDC_COM3POL : Set COM3 polarity
 *        @arg LEDC_COM4POL : Set COM4 polarity
 *        @arg LEDC_COM5POL : Set COM5 polarity
 *        @arg LEDC_COM6POL : Set COM6 polarity
 *        @arg LEDC_COM7POL : Set COM7 polarity
 *        @arg LEDC_COM8POL : Set COM8 polarity(Only support 54253 )
 *        @arg LEDC_COM9POL : Set COM9 polarity(Only support 54253 )
 *        @arg LEDC_COM10POL : Set COM10 polarity(Only support 54253 )
 *        @arg LEDC_COM11POL : Set COM11 polarity(Only support 54253 )
 * @param LEDC_SEGxPOL: This parameter can be any combination of the following values:
 *        @arg LEDC_SEG0POL : Set SEG0 polarity
 *        @arg LEDC_SEG1POL : Set SEG1 polarity
 *        @arg LEDC_SEG2POL : Set SEG2 polarity
 *        @arg LEDC_SEG3POL : Set SEG3 polarity
 *        @arg LEDC_SEG4POL : Set SEG4 polarity
 *        @arg LEDC_SEG5POL : Set SEG5 polarity
 *        @arg LEDC_SEG6POL : Set SEG6 polarity
 *        @arg LEDC_SEG7POL : Set SEG7 polarity
 * @param mode: LED layout mode.
 *                                       SEG polarity   COM polarity
 *             -------------------------------------------------------
 *        @arg COMMON_CATHODE          : non-inverted   non-inverted
 *        @arg COMMON_CATHODE_WITH_NPN : non-inverted   inverted
 *        @arg COMMON_ANODE_WITH_PNP   : inverted       non-inverted
 *        @arg COMMON_ANODE_WITH_NPN   : inverted       inverted
 *        @arg @retval None
 ************************************************************************************************************/
void LEDC_SetPolarityMode(u32 LEDC_COMxPOL, u32 LEDC_SEGxPOL , LEDC_Mode mode)
{
    /* Check the parameters                                                                                 */
  Assert_Param(IS_LEDC_DTCR(mode));
  Assert_Param(IS_LEDC_COMPOL(LEDC_COMxPOL));
  Assert_Param(IS_LEDC_SEGPOL(LEDC_SEGxPOL));

  switch(mode)
  {
    case COMMON_CATHODE:
      HT_LEDC->PCR &= ~(LEDC_COMxPOL|LEDC_SEGxPOL);
    break;
    case COMMON_CATHODE_WITH_NPN:
      HT_LEDC->PCR |= LEDC_COMxPOL;
      HT_LEDC->PCR &= ~(LEDC_SEGxPOL);
    break;
    case COMMON_ANODE_WITH_PNP:
      HT_LEDC->PCR &= ~(LEDC_COMxPOL);
      HT_LEDC->PCR |= LEDC_SEGxPOL;
    break;
    case COMMON_ANODE_WITH_NPN:
      HT_LEDC->PCR |= LEDC_COMxPOL|LEDC_SEGxPOL;
    break;
  }
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
