/*********************************************************************************************************//**
 * @file    ht32f5xxxx_lcd.h
 * @version V1.00
 * @date    11/15/2017
 * @brief   The header file of the LCD library.
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

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F5XXXX_LCD_H
#define __HT32F5XXXX_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup LCD
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup LCD_Exported_Types LCD exported types
  * @{
  */
/**
 * @brief Enumeration of LCD mask time.
 */
typedef enum {
  LCD_MaskTime_25ns = (0x00 << 24), /*!< MCONT mask time = 25 ns                                            */
  LCD_MaskTime_40ns = (0x01 << 24), /*!< MCONT mask time = 40 ns                                            */
} LCD_MaskTime_Enum;

/**
 * @brief Enumeration of LCD STATIC switch.
 */
typedef enum {
  LCD_StaticSwitch_Close = (0x00 << 14), /*!< STATIC switch is closed during dead time                      */
  LCD_StaticSwitch_Open  = (0x01 << 14), /*!< STATIC switch is open during dead time                        */
} LCD_StaticSwitch_Enum;

/**
 * @brief Enumeration of LCD MUXCOM7.
 */
typedef enum
{
  /*!< 57341: SEG28/COM7                                                                                    */
  /*!< 57352: SEG36/COM7                                                                                    */
  LCD_MUXCOM7_IS_COM7  = (0x00 << 11),
  LCD_MUXCOM7_IS_SEGx = (0x01 << 11),
} LCD_MUXCOM7_Enum;

/**
 * @brief Enumeration of LCD MUXCOM6.
 */
typedef enum
{
  /*!< 57341: SEG27/COM6                                                                                    */
  /*!< 57352: SEG35/COM6                                                                                    */
  LCD_MUXCOM6_IS_COM6  = (0x00 << 10),
  LCD_MUXCOM6_IS_SEGx = (0x01 << 10),
} LCD_MUXCOM6_Enum;

/**
 * @brief Enumeration of LCD MUXCOM5.
 */
typedef enum
{
  /*!< 57341: SEG26/COM5                                                                                    */
  /*!< 57352: SEG34/COM5                                                                                    */
  LCD_MUXCOM5_IS_COM5  = (0x00 << 9),
  LCD_MUXCOM5_IS_SEGx = (0x01 << 9),
} LCD_MUXCOM5_Enum;

/**
 * @brief Enumeration of LCD MUXCOM4.
 */
typedef enum
{
  /*!< 57341: SEG25/COM4                                                                                    */
  /*!< 57352: SEG33/COM4                                                                                    */
  LCD_MUXCOM4_IS_COM4  = (0x00 << 8),
  LCD_MUXCOM4_IS_SEGx = (0x01 << 8),
} LCD_MUXCOM4_Enum;

/**
 * @brief Enumeration of LCD waveform.
 */
typedef enum
{
  LCD_Type_A_Waveform = (0x00 << 7), /*!< Type A waveform                                                   */
  LCD_Type_B_Waveform = (0x01 << 7), /*!< Type B waveform                                                   */
} LCD_Waveform_Enum;

/**
 * @brief Enumeration of LCD bias.
 */
typedef enum {
  LCD_Bias_1_4    = (0x00 << 5), /*!< 1/4 bias                                                              */
  LCD_Bias_1_2    = (0x01 << 5), /*!< 1/2 bias                                                              */
  LCD_Bias_1_3    = (0x02 << 5), /*!< 1/3 bias                                                              */
  LCD_Bias_Static = (0x03 << 5), /*!< Static bias                                                           */
} LCD_Bias_Enum;

/**
 * @brief Enumeration of LCD duty.
 */
typedef enum {
  LCD_Duty_Static = (0x00 << 2), /*!< Static duty                                                           */
  LCD_Duty_1_2    = (0x01 << 2), /*!< 1/2 duty                                                              */
  LCD_Duty_1_3    = (0x02 << 2), /*!< 1/3 duty                                                              */
  LCD_Duty_1_4    = (0x03 << 2), /*!< 1/4 duty                                                              */
  LCD_Duty_1_6    = (0x04 << 2), /*!< 1/6 duty                                                              */
  LCD_Duty_1_8    = (0x05 << 2), /*!< 1/8 duty                                                              */
} LCD_Duty_Enum;

/**
 * @brief Enumeration of LCD voltage source.
 */
typedef enum {
  LCD_VoltageSource_External = (0x00 << 1), /*!< External voltage source                                    */
  LCD_VoltageSource_Internal = (0x01 << 1), /*!< Internal voltage source                                    */
} LCD_VoltageSource_Enum;

/**
 * @brief Enumeration of LCD clock prescaler.
 */
typedef enum {
  LCD_Prescaler_1     = (0x00 << 22), /*!< CK_PS = CK_LCD / 1                                               */
  LCD_Prescaler_2     = (0x01 << 22), /*!< CK_PS = CK_LCD / 2                                               */
  LCD_Prescaler_4     = (0x02 << 22), /*!< CK_PS = CK_LCD / 4                                               */
  LCD_Prescaler_8     = (0x03 << 22), /*!< CK_PS = CK_LCD / 8                                               */
  LCD_Prescaler_16    = (0x04 << 22), /*!< CK_PS = CK_LCD / 16                                              */
  LCD_Prescaler_32    = (0x05 << 22), /*!< CK_PS = CK_LCD / 32                                              */
  LCD_Prescaler_64    = (0x06 << 22), /*!< CK_PS = CK_LCD / 64                                              */
  LCD_Prescaler_128   = (0x07 << 22), /*!< CK_PS = CK_LCD / 128                                             */
  LCD_Prescaler_256   = (0x08 << 22), /*!< CK_PS = CK_LCD / 256                                             */
  LCD_Prescaler_512   = (0x09 << 22), /*!< CK_PS = CK_LCD / 512                                             */
  LCD_Prescaler_1024  = (0x0A << 22), /*!< CK_PS = CK_LCD / 1024                                            */
  LCD_Prescaler_2048  = (0x0B << 22), /*!< CK_PS = CK_LCD / 2048                                            */
  LCD_Prescaler_4096  = (0x0C << 22), /*!< CK_PS = CK_LCD / 4096                                            */
  LCD_Prescaler_8192  = (0x0D << 22), /*!< CK_PS = CK_LCD / 8192                                            */
  LCD_Prescaler_16384 = (0x0E << 22), /*!< CK_PS = CK_LCD / 16384                                           */
  LCD_Prescaler_32768 = (0x0F << 22)  /*!< CK_PS = CK_LCD / 32768                                           */
} LCD_Prescaler_Enum;

/**
 * @brief Enumeration of LCD clock divider.
 */
typedef enum {
  LCD_Divider_16 = (0x00 << 18), /*!< CK_DIV = CK_PS / 16                                                   */
  LCD_Divider_17 = (0x01 << 18), /*!< CK_DIV = CK_PS / 17                                                   */
  LCD_Divider_18 = (0x02 << 18), /*!< CK_DIV = CK_PS / 18                                                   */
  LCD_Divider_19 = (0x03 << 18), /*!< CK_DIV = CK_PS / 19                                                   */
  LCD_Divider_20 = (0x04 << 18), /*!< CK_DIV = CK_PS / 20                                                   */
  LCD_Divider_21 = (0x05 << 18), /*!< CK_DIV = CK_PS / 21                                                   */
  LCD_Divider_22 = (0x06 << 18), /*!< CK_DIV = CK_PS / 22                                                   */
  LCD_Divider_23 = (0x07 << 18), /*!< CK_DIV = CK_PS / 23                                                   */
  LCD_Divider_24 = (0x08 << 18), /*!< CK_DIV = CK_PS / 24                                                   */
  LCD_Divider_25 = (0x09 << 18), /*!< CK_DIV = CK_PS / 25                                                   */
  LCD_Divider_26 = (0x0A << 18), /*!< CK_DIV = CK_PS / 26                                                   */
  LCD_Divider_27 = (0x0B << 18), /*!< CK_DIV = CK_PS / 27                                                   */
  LCD_Divider_28 = (0x0C << 18), /*!< CK_DIV = CK_PS / 28                                                   */
  LCD_Divider_29 = (0x0D << 18), /*!< CK_DIV = CK_PS / 29                                                   */
  LCD_Divider_30 = (0x0E << 18), /*!< CK_DIV = CK_PS / 30                                                   */
  LCD_Divider_31 = (0x0F << 18), /*!< CK_DIV = CK_PS / 31                                                   */
} LCD_Divider_Enum;

/**
 * @brief Enumeration of LCD blink mode.
 */
typedef enum {
  LCD_BlinkMode_Off           = (0x00 << 16), /*!< Blink inactive                                           */
  LCD_BlinkMode_SEG0_COM0     = (0x01 << 16), /*!< SEG0 on COM0 blink                                       */
  LCD_BlinkMode_SEG0_AllCOM   = (0x02 << 16), /*!< SEG0 on All COM blink                                    */
  LCD_BlinkMode_AllSEG_AllCOM = (0x03 << 16), /*!< All SEG on All COM blink                                 */
} LCD_BlinkMode_Enum;

/**
  * @brief Enumeration of LCD blink frequency.
  */
typedef enum
{
  LCD_BlinkFrequency_Div8    = (0x00 << 13), /*!< Blink frequency = frame rate / 8                          */
  LCD_BlinkFrequency_Div16   = (0x01 << 13), /*!< Blink frequency = frame rate / 16                         */
  LCD_BlinkFrequency_Div32   = (0x02 << 13), /*!< Blink frequency = frame rate / 32                         */
  LCD_BlinkFrequency_Div64   = (0x03 << 13), /*!< Blink frequency = frame rate / 64                         */
  LCD_BlinkFrequency_Div128  = (0x04 << 13), /*!< Blink frequency = frame rate / 128                        */
  LCD_BlinkFrequency_Div256  = (0x05 << 13), /*!< Blink frequency = frame rate / 256                        */
  LCD_BlinkFrequency_Div512  = (0x06 << 13), /*!< Blink frequency = frame rate / 512                        */
  LCD_BlinkFrequency_Div1024 = (0x07 << 13), /*!< Blink frequency = frame rate / 1024                       */
} LCD_BlinkFrequency_Enum;

/**
  * @brief Enumeration of LCD charge pump.
  */
typedef enum
{
  LCD_ChargePump_2V65 = (0x00 << 10), /*!< Charge pump voltage = 2.65 V                                     */
  LCD_ChargePump_2V75 = (0x01 << 10), /*!< Charge pump voltage = 2.75 V                                     */
  LCD_ChargePump_2V85 = (0x02 << 10), /*!< Charge pump voltage = 2.85 V                                     */
  LCD_ChargePump_2V95 = (0x03 << 10), /*!< Charge pump voltage = 2.95 V                                     */
  LCD_ChargePump_3V10 = (0x04 << 10), /*!< Charge pump voltage = 3.10 V                                     */
  LCD_ChargePump_3V25 = (0x05 << 10), /*!< Charge pump voltage = 3.25 V                                     */
  LCD_ChargePump_3V40 = (0x06 << 10), /*!< Charge pump voltage = 3.40 V                                     */
  LCD_ChargePump_3V55 = (0x07 << 10), /*!< Charge pump voltage = 3.55 V                                     */
} LCD_ChargePump_Enum;

/**
  * @brief Enumeration of LCD dead time.
  */
typedef enum
{
  LCD_Deadtime_0 = (0x00 << 7), /*!< No dead time                                                           */
  LCD_Deadtime_1 = (0x01 << 7), /*!< Type A: 1/2 phase period; Type B: 1 phase period                       */
  LCD_Deadtime_2 = (0x02 << 7), /*!< Type A: 2/2 phase period; Type B: 2 phase period                       */
  LCD_Deadtime_3 = (0x03 << 7), /*!< Type A: 3/2 phase period; Type B: 3 phase period                       */
  LCD_Deadtime_4 = (0x04 << 7), /*!< Type A: 4/2 phase period; Type B: 4 phase period                       */
  LCD_Deadtime_5 = (0x05 << 7), /*!< Type A: 5/2 phase period; Type B: 5 phase period                       */
  LCD_Deadtime_6 = (0x06 << 7), /*!< Type A: 6/2 phase period; Type B: 6 phase period                       */
  LCD_Deadtime_7 = (0x07 << 7), /*!< Type A: 7/2 phase period; Type B: 7 phase period                       */
} LCD_DeadTime_Enum;

/**
  * @brief Enumeration of LCD high drive.
  */
typedef enum
{
  LCD_HighDrive_0 = (0x00 << 4), /*!< No high drive                                                         */
  LCD_HighDrive_1 = (0x01 << 4), /*!< High drive duration = 1 CK_PS pulses                                  */
  LCD_HighDrive_2 = (0x02 << 4), /*!< High drive duration = 2 CK_PS pulses                                  */
  LCD_HighDrive_3 = (0x03 << 4), /*!< High drive duration = 3 CK_PS pulses                                  */
  LCD_HighDrive_4 = (0x04 << 4), /*!< High drive duration = 4 CK_PS pulses                                  */
  LCD_HighDrive_5 = (0x05 << 4), /*!< High drive duration = 5 CK_PS pulses                                  */
  LCD_HighDrive_6 = (0x06 << 4), /*!< High drive duration = 6 CK_PS pulses                                  */
  LCD_HighDrive_7 = (0x07 << 4), /*!< High drive duration = 7 CK_PS pulses                                  */
  LCD_HighDrive_Static = (0xff), /*!< Static high drive                                                     */
} LCD_HighDrive_Enum;

/**
 * @brief Definition of LCD Init Structure.
 */
typedef struct
{
  LCD_Prescaler_Enum LCD_Prescaler;
  LCD_Divider_Enum LCD_Divider;
  LCD_Duty_Enum LCD_Duty;
  LCD_Bias_Enum LCD_Bias;
  LCD_Waveform_Enum LCD_Waveform;
  LCD_VoltageSource_Enum LCD_VoltageSource;
} LCD_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup LCD_Exported_Constants LCD exported constants
  * @{
  */
#define LCD_INT_UDD                          ((u32)0x00000002)
#define LCD_INT_SOF                          ((u32)0x00000001)

#define IS_LCD_INT(INT)                      ((((INT) & 0xFFFFFFFC) == 0) && ((INT) != 0))


#define LCD_FLAG_FCRSF                       ((u32)0x00000020)
#define LCD_FLAG_RDY                         ((u32)0x00000010)
#define LCD_FLAG_UDD                         ((u32)0x00000008)
#define LCD_FLAG_UDR                         ((u32)0x00000004)
#define LCD_FLAG_SOF                         ((u32)0x00000002)
#define LCD_FLAG_ENS                         ((u32)0x00000001)

#define IS_LCD_FLAG(FLAG)                    (((FLAG) == LCD_FLAG_FCRSF) || \
                                              ((FLAG) == LCD_FLAG_RDY)   || \
                                              ((FLAG) == LCD_FLAG_UDD)   || \
                                              ((FLAG) == LCD_FLAG_UDR)   || \
                                              ((FLAG) == LCD_FLAG_SOF)   || \
                                              ((FLAG) == LCD_FLAG_ENS))


#define LCD_CLR_UDD                          ((u32)0x00000002)
#define LCD_CLR_SOF                          ((u32)0x00000001)

#define IS_LCD_CLEAR(CLR)                    ((((CLR) & 0xFFFFFFFC) == 0) && ((CLR) != 0))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup LCD_Exported_Functions LCD exported functions
  * @{
  */

/* !!! NOTICE !!!
   Before using the following functions, be sure to confirm LCDENS = 0 by "LCD_GetFlagStatus(LCD_FLAG_ENS);",
   otherwise the LCD may display abnormally.
     LCD_DriverInit()
     LCD_MaskTimeConfig()
     LCD_StaticSwitchConfig()
     LCD_MuxCOM7Config()
     LCD_MuxCOM6Config()
     LCD_MuxCOM5Config()
     LCD_MuxCOM4Config()
     LCD_WaveformConfig()
     LCD_BiasConfig()
     LCD_DutyConfig()
     LCD_VoltageSourceConfig()
     LCD_ChargePumpConfig()
*/

void LCD_DriverDeInit(void);
void LCD_DriverInit(LCD_InitTypeDef* LCD_InitStruct);

void LCD_MaskTimeConfig(LCD_MaskTime_Enum Sel);
void LCD_HalfRLCmd(ControlStatus NewState);
void LCD_StaticSwitchConfig(LCD_StaticSwitch_Enum Sel);
void LCD_MuxCOM7Config(LCD_MUXCOM7_Enum Sel);
void LCD_MuxCOM6Config(LCD_MUXCOM6_Enum Sel);
void LCD_MuxCOM5Config(LCD_MUXCOM5_Enum Sel);
void LCD_MuxCOM4Config(LCD_MUXCOM4_Enum Sel);
void LCD_WaveformConfig(LCD_Waveform_Enum Sel);
void LCD_BiasConfig(LCD_Bias_Enum Sel);
void LCD_DutyConfig(LCD_Duty_Enum Sel);
void LCD_VoltageSourceConfig(LCD_VoltageSource_Enum Sel);
void LCD_Cmd(ControlStatus NewState);

void LCD_PrescalerConfig(LCD_Prescaler_Enum Sel);
void LCD_DividerConfig(LCD_Divider_Enum Sel);
void LCD_BlinkModeConfig(LCD_BlinkMode_Enum Sel);
void LCD_BlinkFreqConfig(LCD_BlinkFrequency_Enum Sel);
void LCD_ChargePumpConfig(LCD_ChargePump_Enum Sel);
void LCD_DeadTimeConfig(LCD_DeadTime_Enum Sel);
void LCD_HighDriveConfig(LCD_HighDrive_Enum Sel);

void LCD_IntConfig(u32 LCD_Int, ControlStatus NewState);
FlagStatus LCD_GetFlagStatus(u32 LCD_Flag);
void LCD_SetUpdateDisplayRequest(void);
void LCD_ClearFlag(u32 LCD_Flag);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
