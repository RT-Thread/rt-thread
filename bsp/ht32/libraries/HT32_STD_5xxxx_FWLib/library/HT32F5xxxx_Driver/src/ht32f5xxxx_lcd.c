/*********************************************************************************************************//**
 * @file    ht32f5xxxx_lcd.c
 * @version $Rev:: 1704         $
 * @date    $Date:: 2017-08-17 #$
 * @brief   This file provides all the LCD firmware functions.
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
#include "ht32f5xxxx_lcd.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup LCD LCD
  * @brief LCD driver modules
  * @{
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup LCD_Exported_Functions LCD exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the LCD peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void LCD_DriverDeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};
  RSTCUReset.Bit.LCD = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initializes the LCD peripheral according to the specified parameters in the LCD_InitStruct.
 * @param LCD_InitStruct: pointer to a LCD_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void LCD_DriverInit(LCD_InitTypeDef* LCD_InitStruct)
{
  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD control register.
  */
  #if 0
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);
  #endif

  HT_LCD->FCR = (u32)(LCD_InitStruct->LCD_Prescaler) |
                (u32)(LCD_InitStruct->LCD_Divider);

  HT_LCD->CR = (u32)(LCD_InitStruct->LCD_Waveform) |
               (u32)(LCD_InitStruct->LCD_Bias) |
               (u32)(LCD_InitStruct->LCD_Duty) |
               (u32)(LCD_InitStruct->LCD_VoltageSource);
}

/*********************************************************************************************************//**
 * @brief Configure the MCONT mask time.
 * @param Sel: specify the mask time.
 *   This parameter can be:
 *     @arg LCD_MaskTime_25ns : MCONT mask time is 25 ns
 *     @arg LCD_MaskTime_40ns : MCONT mask time is 40 ns
 * @retval None
 ************************************************************************************************************/
void LCD_MaskTimeConfig(LCD_MaskTime_Enum Sel)
{
  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD control register.
  */
  #if 0
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);
  #endif

  HT_LCD->CR = (HT_LCD->CR & ~(1ul << 24)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable half of the low value resistor (HRLEN).
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void LCD_HalfRLCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_LCD->CR |= (1ul << 15);
  }
  else
  {
    HT_LCD->CR &= ~(1ul << 15);
  }
}

/*********************************************************************************************************//**
 * @brief Configure the STATIC switch.
 * @param Sel: specify the STATIC switch status.
 *   This parameter can be:
 *     @arg LCD_Static_Switch_Open  : STATIC switch is open during dead time.
 *     @arg LCD_Static_Switch_close : STATIC switch is closed during dead time.
 * @retval None
 ************************************************************************************************************/
void LCD_StaticSwitchConfig(LCD_StaticSwitch_Enum Sel)
{
  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD control register.
  */
  #if 0
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);
  #endif

  HT_LCD->CR = (HT_LCD->CR & ~(1ul << 14)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure MuxCOM7 to be COM7 or SEGx.
 * @param Sel: Specify the MuxSEG.
 *   This parameter can be one of the following values:
 *     @arg LCD_MUXCOM7_IS_COM7  :
 *     @arg LCD_MUXCOM7_IS_SEGx  :(52341: SEG28, 57352: SEG36)
 * @retval None
 ************************************************************************************************************/
void LCD_MuxCOM7Config(LCD_MUXCOM7_Enum Sel)
{
  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD control register.
  */
  #if 0
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);
  #endif

  HT_LCD->CR = (HT_LCD->CR & ~(1ul << 11)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure MuxCOM6 to be COM6 or SEGx.
 * @param Sel: Specify the MuxSEG.
 *   This parameter can be one of the following values:
 *     @arg LCD_MUXCOM7_IS_COM6  :
 *     @arg LCD_MUXCOM7_IS_SEGx  :(52341: SEG27, 57352: SEG35)
 * @retval None
 ************************************************************************************************************/
void LCD_MuxCOM6Config(LCD_MUXCOM6_Enum Sel)
{
  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD settings.
  */
  #if 0
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);
  #endif

  HT_LCD->CR = (HT_LCD->CR & ~(1ul << 10)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure MuxCOM5 to be COM5 or SEGx.
 * @param Sel: Specify the MuxSEG.
 *   This parameter can be one of the following values:
 *     @arg LCD_MUXCOM7_IS_COM5  :
 *     @arg LCD_MUXCOM7_IS_SEGx  :(52341: SEG26, 57352: SEG34)
 * @retval None
 ************************************************************************************************************/
void LCD_MuxCOM5Config(LCD_MUXCOM5_Enum Sel)
{
  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD settings.
  */
  #if 0
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);
  #endif

  HT_LCD->CR = (HT_LCD->CR & ~(1ul << 9)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure MuxCOM4 to be COM4 or SEGx.
 * @param Sel: Specify the MuxSEG.
 *   This parameter can be one of the following values:
 *     @arg LCD_MUXCOM7_IS_COM4  :
 *     @arg LCD_MUXCOM7_IS_SEGx  :(52341: SEG25, 57352: SEG33)
 * @retval None
 ************************************************************************************************************/
void LCD_MuxCOM4Config(LCD_MUXCOM4_Enum Sel)
{
  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD settings.
  */
  #if 0
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);
  #endif

  HT_LCD->CR = (HT_LCD->CR & ~(1ul << 8)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the LCD waveform type.
 * @param Sel: specify the LCD waveform type.
 *   This parameter can be one of the following values:
 *     @arg LCD_Type_A_Waveform : Type A waveform
 *     @arg LCD_Type_B_Waveform : Type B waveform
 * @retval None
 ************************************************************************************************************/
void LCD_WaveformConfig(LCD_Waveform_Enum Sel)
{
  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD settings.
  */
  #if 0
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);
  #endif

  HT_LCD->CR = (HT_LCD->CR & ~(1ul << 7)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure LCD Bias Selector.
 * @param Sel: Specify LCD Bias Selector.
 *   This parameter can be one of the following values:
 *     @arg LCD_Bias_1_4    : Bias 1/4
 *     @arg LCD_Bias_1_2    : Bias 1/2
 *     @arg LCD_Bias_1_3    : Bias 1/3
 *     @arg LCD_Bias_Static : STATIC
 * @retval None
 ************************************************************************************************************/
void LCD_BiasConfig(LCD_Bias_Enum Sel)
{
  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD settings.
  */
  #if 0
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);
  #endif

  HT_LCD->CR = (HT_LCD->CR & ~(3ul << 5)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the LCD Duty Selection.
 * @param Sel: Specify LCD Duty select.
 *   This parameter can be one of the following values:
 *     @arg LCD_Duty_Static : Static duty
 *     @arg LCD_Duty_1_2    : 1/2 duty
 *     @arg LCD_Duty_1_3    : 1/3 duty
 *     @arg LCD_Duty_1_4    : 1/4 duty
 *     @arg LCD_Duty_1_6    : 1/6 duty
 *     @arg LCD_Duty_1_8    : 1/8 duty
 ************************************************************************************************************/
void LCD_DutyConfig(LCD_Duty_Enum Sel)
{
  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD settings.
  */
  #if 0
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);
  #endif

  HT_LCD->CR = (HT_LCD->CR & ~(7ul << 2)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the LCD Power Selection.
 * @param Sel: Specify LCD Power select.
 *   This parameter can be one of the following values:
 *     @arg LCD_VoltageSource_External : External VLCD
 *     @arg LCD_VoltageSource_Internal : Internal charge pump
 * @retval None
 ************************************************************************************************************/
void LCD_VoltageSourceConfig(LCD_VoltageSource_Enum Sel)
{
  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD settings.
  */
  #if 0
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);
  #endif

  HT_LCD->CR = (HT_LCD->CR & ~(1ul << 1)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the LCD peripheral.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void LCD_Cmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_LCD->CR |= (1ul << 0);
  }
  else
  {
    HT_LCD->CR &= ~(1ul << 0);
  }
}

/*********************************************************************************************************//**
 * @brief Configure the LCD 16-bit prescaler.
 * @param Sel: specify the LCD 16-bit prescaler setting.
 *   This parameter can be one of the following values:
 *     @arg LCD_Prescaler_1     : CK_PS = CK_LCD / 1
 *     @arg LCD_Prescaler_2     : CK_PS = CK_LCD / 2
 *     @arg LCD_Prescaler_4     : CK_PS = CK_LCD / 4
 *     @arg LCD_Prescaler_8     : CK_PS = CK_LCD / 8
 *     @arg LCD_Prescaler_16    : CK_PS = CK_LCD / 16
 *     @arg LCD_Prescaler_32    : CK_PS = CK_LCD / 32
 *     @arg LCD_Prescaler_64    : CK_PS = CK_LCD / 64
 *     @arg LCD_Prescaler_128   : CK_PS = CK_LCD / 128
 *     @arg LCD_Prescaler_256   : CK_PS = CK_LCD / 256
 *     @arg LCD_Prescaler_512   : CK_PS = CK_LCD / 512
 *     @arg LCD_Prescaler_1024  : CK_PS = CK_LCD / 1024
 *     @arg LCD_Prescaler_2048  : CK_PS = CK_LCD / 2048
 *     @arg LCD_Prescaler_4096  : CK_PS = CK_LCD / 4096
 *     @arg LCD_Prescaler_8192  : CK_PS = CK_LCD / 8192
 *     @arg LCD_Prescaler_16384 : CK_PS = CK_LCD / 16384
 *     @arg LCD_Prescaler_32768 : CK_PS = CK_LCD / 32768
 * @retval None
 ************************************************************************************************************/
void LCD_PrescalerConfig(LCD_Prescaler_Enum Sel)
{
  while (LCD_GetFlagStatus(LCD_FLAG_FCRSF) == SET);
  HT_LCD->FCR = (HT_LCD->FCR & ~(15ul << 22)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the LCD clock divider.
 * @param Sel: specify the LCD clock divider setting.
 *   This parameter can be one of the following values:
 *     @arg LCD_Divider_16 : CK_DIV = CK_PS / 16
 *     @arg LCD_Divider_17 : CK_DIV = CK_PS / 17
 *     @arg LCD_Divider_18 : CK_DIV = CK_PS / 18
 *     @arg LCD_Divider_19 : CK_DIV = CK_PS / 19
 *     @arg LCD_Divider_20 : CK_DIV = CK_PS / 20
 *     @arg LCD_Divider_21 : CK_DIV = CK_PS / 21
 *     @arg LCD_Divider_22 : CK_DIV = CK_PS / 22
 *     @arg LCD_Divider_23 : CK_DIV = CK_PS / 23
 *     @arg LCD_Divider_24 : CK_DIV = CK_PS / 24
 *     @arg LCD_Divider_25 : CK_DIV = CK_PS / 25
 *     @arg LCD_Divider_26 : CK_DIV = CK_PS / 26
 *     @arg LCD_Divider_27 : CK_DIV = CK_PS / 27
 *     @arg LCD_Divider_28 : CK_DIV = CK_PS / 28
 *     @arg LCD_Divider_29 : CK_DIV = CK_PS / 29
 *     @arg LCD_Divider_30 : CK_DIV = CK_PS / 30
 *     @arg LCD_Divider_31 : CK_DIV = CK_PS / 31
 * @retval None
 ************************************************************************************************************/
void LCD_DividerConfig(LCD_Divider_Enum Sel)
{
  while (LCD_GetFlagStatus(LCD_FLAG_FCRSF) == SET);
  HT_LCD->FCR = (HT_LCD->FCR & ~(15ul << 18)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the LCD Blink Mode Selection.
 * @param Sel: Specify LCD Blink Mode Selection.
 *   This parameter can be one of the following values:
 *     @arg LCD_BlinkMode_Off           : Blink inactive
 *     @arg LCD_BlinkMode_SEG0_COM0     : SEG0 on COM0 blink
 *     @arg LCD_BlinkMode_SEG0_AllCOM   : SEG0 on All COM blink
 *     @arg LCD_BlinkMode_AllSEG_AllCOM : All SEG on All COM blink
 ************************************************************************************************************/
void LCD_BlinkModeConfig(LCD_BlinkMode_Enum Sel)
{
  while (LCD_GetFlagStatus(LCD_FLAG_FCRSF) == SET);
  HT_LCD->FCR = (HT_LCD->FCR & ~(3ul << 16)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the LCD Blink Frequency  Selection.
 * @param Sel: Specify LCD Blink Frequency  Selection.
 *   This parameter can be one of the following values:
 *     @arg LCD_BlinkFrequency_Div8    : Blink frequency = frame rate / 8
 *     @arg LCD_BlinkFrequency_Div16   : Blink frequency = frame rate / 16
 *     @arg LCD_BlinkFrequency_Div32   : Blink frequency = frame rate / 32
 *     @arg LCD_BlinkFrequency_Div64   : Blink frequency = frame rate / 64
 *     @arg LCD_BlinkFrequency_Div128  : Blink frequency = frame rate / 128
 *     @arg LCD_BlinkFrequency_Div256  : Blink frequency = frame rate / 256
 *     @arg LCD_BlinkFrequency_Div512  : Blink frequency = frame rate / 512
 *     @arg LCD_BlinkFrequency_Div1024 : Blink frequency = frame rate / 1024
 ************************************************************************************************************/
void LCD_BlinkFrequencyConfig(LCD_BlinkFrequency_Enum Sel)
{
  while (LCD_GetFlagStatus(LCD_FLAG_FCRSF) == SET);
  HT_LCD->FCR = (HT_LCD->FCR & ~(7ul << 13)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the LCD Charge Pump Voltage Selection.
 * @param Sel: Specify LCD Charge Pump Voltage Selection.
 *   This parameter can be one of the following values:
 *     @arg LCD_ChargePump_2V65 : Charge pump voltage = 2.65 V
 *     @arg LCD_ChargePump_2V75 : Charge pump voltage = 2.75 V
 *     @arg LCD_ChargePump_2V85 : Charge pump voltage = 2.85 V
 *     @arg LCD_ChargePump_2V95 : Charge pump voltage = 2.95 V
 *     @arg LCD_ChargePump_3V10 : Charge pump voltage = 3.10 V
 *     @arg LCD_ChargePump_3V25 : Charge pump voltage = 3.25 V
 *     @arg LCD_ChargePump_3V40 : Charge pump voltage = 3.40 V
 *     @arg LCD_ChargePump_3V55 : Charge pump voltage = 3.55 V
 ************************************************************************************************************/
void LCD_ChargePumpConfig(LCD_ChargePump_Enum Sel)
{
  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD settings.
  */
  #if 0
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);
  #endif

  while (LCD_GetFlagStatus(LCD_FLAG_FCRSF));
  HT_LCD->FCR = (HT_LCD->FCR & ~(7ul << 10)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the LCD Dead Time Duration Selection.
 * @param Sel: Specify LCD Dead Time Duration Selection.
     This parameter can be one of the following values:
 *     @arg LCD_Deadtime_0 : No dead time
 *     @arg LCD_Deadtime_1 : Type A: 1/2 phase period; Type B: 1 phase period
 *     @arg LCD_Deadtime_2 : Type A: 2/2 phase period; Type B: 2 phase period
 *     @arg LCD_Deadtime_3 : Type A: 3/2 phase period; Type B: 3 phase period
 *     @arg LCD_Deadtime_4 : Type A: 4/2 phase period; Type B: 4 phase period
 *     @arg LCD_Deadtime_5 : Type A: 5/2 phase period; Type B: 5 phase period
 *     @arg LCD_Deadtime_6 : Type A: 6/2 phase period; Type B: 6 phase period
 *     @arg LCD_Deadtime_7 : Type A: 7/2 phase period; Type B: 7 phase period
 ************************************************************************************************************/
void LCD_DeadTimeConfig(LCD_DeadTime_Enum Sel)
{
  while (LCD_GetFlagStatus(LCD_FLAG_FCRSF) == SET);
  HT_LCD->FCR = (HT_LCD->FCR & ~(7ul << 7)) | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure the LCD High Drive Duration Selection.
 * @param Sel: Specify LCD High Drive Duration Selection.
 *   This parameter LCD_DEAD_Enum can be one of the following values:
 *     @arg LCD_HighDrive_0      : No high drive
 *     @arg LCD_HighDrive_1      : High drive duration = 1 CK_PS pulses
 *     @arg LCD_HighDrive_2      : High drive duration = 2 CK_PS pulses
 *     @arg LCD_HighDrive_3      : High drive duration = 3 CK_PS pulses
 *     @arg LCD_HighDrive_4      : High drive duration = 4 CK_PS pulses
 *     @arg LCD_HighDrive_5      : High drive duration = 5 CK_PS pulses
 *     @arg LCD_HighDrive_6      : High drive duration = 6 CK_PS pulses
 *     @arg LCD_HighDrive_7      : High drive duration = 7 CK_PS pulses
 *     @arg LCD_HighDrive_Static : Static high drive
 ************************************************************************************************************/
void LCD_HighDriveConfig(LCD_HighDrive_Enum Sel)
{
  u32 FCR = HT_LCD->FCR;

  if (Sel == LCD_HighDrive_Static)
  {
    FCR |= (1ul << 0);
  }
  else
  {
    FCR &= ~(1ul << 0);
    FCR = (FCR & ~(7ul << 4)) | Sel;
  }

  while (LCD_GetFlagStatus(LCD_FLAG_FCRSF));
  HT_LCD->FCR = FCR;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified LCD interrupts.
 * @param LCD_INT: Specify the LCD interrupt sources that is to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg LCD_INT_UDDIE : Update Display Done Interrupt Enable
 *     @arg LCD_INT_SOFIE : Start of Frame Interrupt Enable
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void LCD_IntConfig(u32 LCD_INT, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_LCD_INT(LCD_INT));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_LCD->IER |= LCD_INT;
  }
  else
  {
    HT_LCD->IER &= ~LCD_INT;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified LCD flag has been set.
 * @param LCD_FLAG: Specify the interrupt status to check.
 *   This parameter can be any combination of the following values:
 *     @arg LCD_FLAG_FCRSF : LCD Frame Control Register Synchronization Flag
 *     @arg LCD_FLAG_RDY   : Ready Flag
 *     @arg LCD_FLAG_UDD   : Update Display Done
 *     @arg LCD_FLAG_UDR   : Update Display Request
 *     @arg LCD_FLAG_SOF   : Start of Frame Flag
 *     @arg LCD_FLAG_ENS   : LCD Enabled Status
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus LCD_GetFlagStatus(u32 LCD_FLAG)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_LCD_FLAG(LCD_FLAG));

  if ((HT_LCD->SR & LCD_FLAG) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief SET LCD Update Display Request.
 * @retval None
 ************************************************************************************************************/
void LCD_SetUpdateDisplayRequest(void)
{
  HT_LCD->SR |= LCD_FLAG_UDR;
}

/*********************************************************************************************************//**
 * @brief Clear the specified LCD flag.
 * @param LCD_Flag: specify the flag that is to be cleared.
 *   This parameter can be one of the following values:
 *     @arg LCD_CLR_UDDC : Update display done clear
 *     @arg LCD_CLR_SOFC : Start of frame flag clear
 * @retval None
 ************************************************************************************************************/
void LCD_ClearFlag(u32 LCD_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_LCD_CLEAR(LCD_Flag));

  HT_LCD->CLR = LCD_Flag;
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
