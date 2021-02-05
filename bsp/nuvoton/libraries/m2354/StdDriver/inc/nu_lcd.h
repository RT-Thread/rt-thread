/**************************************************************************//**
 * @file     nu_lcd.h
 * @version  V3.00
 * @brief    Liquid-Crystal Display(LCD) driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_LCD_H__
#define __NU_LCD_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup LCD_Driver LCD Driver
  @{
*/

/** @addtogroup LCD_EXPORTED_CONSTANTS LCD Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  LCD Bias Voltage Level Selection Constant Definitions                                                  */
/*---------------------------------------------------------------------------------------------------------*/
#define LCD_BIAS_LV_1_2                 (1ul << LCD_PCTL_BIAS_Pos) /*!< LCD bias voltage level selection - 1/2 Bias \hideinitializer */
#define LCD_BIAS_LV_1_3                 (2ul << LCD_PCTL_BIAS_Pos) /*!< LCD bias voltage level selection - 1/3 Bias \hideinitializer */
#define LCD_BIAS_LV_1_4                 (3ul << LCD_PCTL_BIAS_Pos) /*!< LCD bias voltage level selection - 1/4 Bias \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  LCD COM Duty Ratio Selection Constant Definitions                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define LCD_COM_DUTY_1_1                (0ul << LCD_PCTL_DUTY_Pos) /*!< LCD com duty ratio selection - 1/1 Duty \hideinitializer */
#define LCD_COM_DUTY_1_2                (1ul << LCD_PCTL_DUTY_Pos) /*!< LCD com duty ratio selection - 1/2 Duty \hideinitializer */
#define LCD_COM_DUTY_1_3                (2ul << LCD_PCTL_DUTY_Pos) /*!< LCD com duty ratio selection - 1/3 Duty \hideinitializer */
#define LCD_COM_DUTY_1_4                (3ul << LCD_PCTL_DUTY_Pos) /*!< LCD com duty ratio selection - 1/4 Duty \hideinitializer */
#define LCD_COM_DUTY_1_5                (4ul << LCD_PCTL_DUTY_Pos) /*!< LCD com duty ratio selection - 1/5 Duty \hideinitializer */
#define LCD_COM_DUTY_1_6                (5ul << LCD_PCTL_DUTY_Pos) /*!< LCD com duty ratio selection - 1/6 Duty \hideinitializer */
#define LCD_COM_DUTY_1_7                (6ul << LCD_PCTL_DUTY_Pos) /*!< LCD com duty ratio selection - 1/7 Duty \hideinitializer */
#define LCD_COM_DUTY_1_8                (7ul << LCD_PCTL_DUTY_Pos) /*!< LCD com duty ratio selection - 1/8 Duty \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  LCD Waveform Attribute Selection Constant Definitions                                                  */
/*---------------------------------------------------------------------------------------------------------*/
#define LCD_WAVEFORM_TYPE_A_NORMAL      (0ul << LCD_PCTL_TYPE_Pos) /*!< LCD waveform Type-A, no inverse \hideinitializer */
#define LCD_WAVEFORM_TYPE_B_NORMAL      (1ul << LCD_PCTL_TYPE_Pos) /*!< LCD waveform Type-B, no inverse \hideinitializer */
#define LCD_WAVEFORM_TYPE_A_INVERSE     (2ul << LCD_PCTL_TYPE_Pos) /*!< LCD waveform Type-A and inverse \hideinitializer */
#define LCD_WAVEFORM_TYPE_B_INVERSE     (3ul << LCD_PCTL_TYPE_Pos) /*!< LCD waveform Type-B and inverse \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  LCD Charge Pump Voltage Selection Constant Definitions                                                 */
/*---------------------------------------------------------------------------------------------------------*/
#define LCD_CP_VOLTAGE_LV_0             (0ul << LCD_PCTL_CPVSEL_Pos) /*!< Select LCD charge pump voltage 2.6 V \hideinitializer */
#define LCD_CP_VOLTAGE_LV_1             (1ul << LCD_PCTL_CPVSEL_Pos) /*!< Select LCD charge pump voltage 2.8 V \hideinitializer */
#define LCD_CP_VOLTAGE_LV_2             (2ul << LCD_PCTL_CPVSEL_Pos) /*!< Select LCD charge pump voltage 3.0 V \hideinitializer */
#define LCD_CP_VOLTAGE_LV_3             (3ul << LCD_PCTL_CPVSEL_Pos) /*!< Select LCD charge pump voltage 3.2 V \hideinitializer */
#define LCD_CP_VOLTAGE_LV_4             (4ul << LCD_PCTL_CPVSEL_Pos) /*!< Select LCD charge pump voltage 3.4 V \hideinitializer */
#define LCD_CP_VOLTAGE_LV_5             (5ul << LCD_PCTL_CPVSEL_Pos) /*!< Select LCD charge pump voltage 3.6 V \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  LCD Interrupt Source Constant Definitions                                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define LCD_DISABLE_ALL_INT             (0ul << LCD_INTEN_FCEIEN_Pos)   /*!< Disable all LCD interrupt sources \hideinitializer */
#define LCD_FRAME_COUNTING_END_INT      (1ul << LCD_INTEN_FCEIEN_Pos)   /*!< Indicate frame count end interrupt \hideinitializer */
#define LCD_FRAME_END_INT               (1ul << LCD_INTEN_FEIEN_Pos)    /*!< Indicate frame end interrupt \hideinitializer */
#define LCD_CPTOUT_INT                  (1ul << LCD_INTEN_CTOIEN_Pos)   /*!< Indicate charge pump charging timeout interrupt \hideinitializer */
#define LCD_ENABLE_ALL_INT              (7ul << LCD_INTEN_FCEIEN_Pos)   /*!< Enable all LCD interrupt sources \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  LCD Operation Voltage Source Constant Definitions                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define LCD_VOLTAGE_SOURCE_VLCD         (0ul << LCD_DCTL_VSRC_Pos) /*!< LCD voltage source from external VLCD power \hideinitializer */
#define LCD_VOLTAGE_SOURCE_AVDD         (1ul << LCD_DCTL_VSRC_Pos) /*!< LCD voltage source from internal VDD \hideinitializer */
#define LCD_VOLTAGE_SOURCE_CP           (2ul << LCD_DCTL_VSRC_Pos) /*!< LCD voltage source from built-in charge pump \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  LCD Driving Mode Selection Constant Definitions                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#define LCD_LOW_DRIVING_AND_BUF_OFF                     (0ul << LCD_DCTL_RESMODE_Pos) /*!< LCD operates with low-drive and voltage buffer disabled \hideinitializer */
#define LCD_HIGH_DRIVING_AND_BUF_OFF                    (1ul << LCD_DCTL_RESMODE_Pos) /*!< LCD operates with high-drive and voltage buffer disabled \hideinitializer */
#define LCD_LOW_DRIVING_AND_BUF_ON                      (2ul << LCD_DCTL_RESMODE_Pos) /*!< LCD operates with low-drive and voltage buffer enabled \hideinitializer */
#define LCD_HIGH_DRIVING_AND_BUF_OFF_AND_PWR_SAVING     (5ul << LCD_DCTL_RESMODE_Pos) /*!< LCD operates with high-drive, voltage buffer disabled and power saving \hideinitializer */
#define LCD_LOW_DRIVING_AND_BUF_ON_AND_PWR_SAVING       (6ul << LCD_DCTL_RESMODE_Pos) /*!< LCD operates with low-drive, voltage buffer enabled and power saving \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  LCD Power Saving Mode Constant Definitions                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define LCD_PWR_SAVING_NORMAL_MODE              (0ul << LCD_DCTL_PSVREV_Pos) /*!< The timing of LCD power saving is normal \hideinitializer */
#define LCD_PWR_SAVING_REVERSE_MODE             (1ul << LCD_DCTL_PSVREV_Pos) /*!< The timing of LCD power saving is reverse \hideinitializer */

/**@}*/ /* end of group LCD_EXPORTED_CONSTANTS */


/** @addtogroup LCD_EXPORTED_STRUCTS LCD Exported Structs
  @{
*/
/**
  * @details    LCD Configuration Data Struct
  */
typedef struct
{
    uint32_t u32SrcFreq;        /*!< LCD clock source frequency */
    uint32_t u32ComDuty;        /*!< COM duty */
    uint32_t u32BiasLevel;      /*!< Bias level */
    uint32_t u32Framerate;      /*!< Operation frame rate */
    uint32_t u32WaveformType;   /*!< Waveform type */
    uint32_t u32IntSrc;         /*!< Interrupt source */
    uint32_t u32DrivingMode;    /*!< Driving mode */
    uint32_t u32VSrc;           /*!< Voltage source */
} S_LCD_CFG_T;

/**@}*/ /* end of group LCD_EXPORTED_STRUCTS */


/** @addtogroup LCD_EXPORTED_FUNCTIONS LCD Exported Functions
  @{
*/

/**
  * @brief      Enable LCD Display
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to enable LCD display.
  */
#define LCD_ENABLE_DISPLAY()        do{ LCD->CTL |= LCD_CTL_EN_Msk; while(LCD->CTL & LCD_CTL_SYNC_Msk) {} }while(0)

/**
  * @brief      Disable LCD Display
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to disable LCD display.
  */
#define LCD_DISABLE_DISPLAY()       do{ LCD->CTL &= ~LCD_CTL_EN_Msk; while(LCD->CTL & LCD_CTL_SYNC_Msk) {} }while(0)

/**
  * @brief      Set LCD Waveform Type
  *
  * @param[in]  type       The LCD waveform type. It could be one of the following type
  *                             - \ref LCD_WAVEFORM_TYPE_A_NORMAL
  *                             - \ref LCD_WAVEFORM_TYPE_B_NORMAL
  *                             - \ref LCD_WAVEFORM_TYPE_A_INVERSE
  *                             - \ref LCD_WAVEFORM_TYPE_B_INVERSE
  *
  * @return     None
  *
  * @details    This macro is used to set the attribute of LCD output waveform.
  */
#define LCD_WAVEFORM_TYPE(type)     (LCD->PCTL = (LCD->PCTL & ~LCD_PCTL_TYPE_Msk) | (type))

/**
  * @brief      Set LCD Source Clock Divider
  *
  * @param[in]  div         The frequency divider, valid value is between 1 to 1024.
  *
  * @return     None
  *
  * @details    This macro is used to set the LCD operarion frequency is (LCD source frequency / div).
  */
#define LCD_SET_FREQDIV(div)        (LCD->PCTL = (LCD->PCTL & ~LCD_PCTL_FREQDIV_Msk) | (((div)-1) << LCD_PCTL_FREQDIV_Pos))

/**
  * @brief      Set Charge Pump Voltage
  *
  * @param[in]  voltage     The target charge pump voltage. It could be one of the following voltage level
  *                             - \ref LCD_CP_VOLTAGE_LV_0, 2.6 V
  *                             - \ref LCD_CP_VOLTAGE_LV_1, 2.8 V
  *                             - \ref LCD_CP_VOLTAGE_LV_2, 3.0 V
  *                             - \ref LCD_CP_VOLTAGE_LV_3, 3.2 V
  *                             - \ref LCD_CP_VOLTAGE_LV_4, 3.4 V
  *                             - \ref LCD_CP_VOLTAGE_LV_5, 3.6 V
  *
  * @return     None
  *
  * @details    This macro is used to set charge pump voltage for VLCD.
  */
#define LCD_SET_CP_VOLTAGE(voltage) (LCD->PCTL = (LCD->PCTL & ~LCD_PCTL_CPVSEL_Msk) | (voltage))

/**
  * @brief      Decrease Charge Pump Voltage
  *
  * @param[in]  unit        The tuning units, valid value is between 0 to 7.
  *                         One unit of voltage is about 0.03V, and the charge pump voltage is decreased (unit * 0.03)V.
  *
  * @return     None
  *
  * @details    This macro is used to decrease charge pump voltage by specific units.
  */
#define LCD_CP_VOLTAGE_DECREASE(unit)   (LCD->PCTL = (LCD->PCTL & ~LCD_PCTL_CPVTUNE_Msk) | ((unit) << LCD_PCTL_CPVTUNE_Pos))

/**
  * @brief      Increase Charge Pump Voltage
  *
  * @param[in]  unit        The tuning units, valid value is between 1 to 8.
  *                         One unit of voltage is about 0.03V, and the charge pump voltage is increased (unit * 0.03)V.
  *
  * @return     None
  *
  * @details    This macro is used to increase charge pump voltage by specific units.
  */
#define LCD_CP_VOLTAGE_INCREASE(unit)   (LCD->PCTL = (LCD->PCTL & ~LCD_PCTL_CPVTUNE_Msk) | ((16-(unit)) << LCD_PCTL_CPVTUNE_Pos))

/**
  * @brief      Set LCD Blinking ON
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to enable LCD blinking.
  */
#define LCD_BLINKING_ON()       (LCD->FCTL |= LCD_FCTL_BLINK_Msk)

/**
  * @brief      Set LCD Blinking OFF
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to disable LCD blinking.
  */
#define LCD_BLINKING_OFF()      (LCD->FCTL &= ~LCD_FCTL_BLINK_Msk)

/**
  * @brief      Set LCD Frame Counting Value
  *
  * @param[in]  value       Frame counting value. Valid value is between 1 to 1024.
  *
  * @return     None
  *
  * @details    This macro is used to set the LCD frame counting value to configure the blink interval.
  * @note       For type-B waveform, the frame counter increases at the end of odd frames, not even frames.
  */
#define LCD_SET_FRAME_COUNTING_VALUE(value)     (LCD->FCTL = (LCD->FCTL & ~LCD_FCTL_FCV_Msk) | (((value)-1) << LCD_FCTL_FCV_Pos))

/**
  * @brief      Set Null Frame Time
  *
  * @param[in]  unit        The unit parameter is used to determine the null frame time, valid value is between 0 to 15.
  *                         And one unit time is one LCD operation clock period.
  *
  * @return     None
  *
  * @details    This macro is used to set the one null frame time.
  * @note       All COM and SEG output voltages will keep at 0V during a null frame.
  */
#define LCD_SET_NULL_FRAME_TIME(unit)       (LCD->FCTL = (LCD->FCTL & ~LCD_FCTL_NFTIME_Msk) | ((unit) << LCD_FCTL_NFTIME_Pos))

/**
  * @brief      Set Continuous Frames
  *
  * @param[in]  frame       The continuous frames, valid setting is between 1 to 16 frames.
  *
  * @return     None
  *
  * @details    This macro is used to specify the number of continuous frames reached to insert one null frame.
  */
#define LCD_SET_CONTINUOUS_FRAME(frame)     (LCD->FCTL = (LCD->FCTL & ~LCD_FCTL_NFNUM_Msk) | (((frame)-1) << LCD_FCTL_NFNUM_Pos))

/**
  * @brief      Select LCD Voltage Source
  *
  * @param[in]  mode        The LCD operation voltage source. It could be one of the following source
  *                             - \ref LCD_VOLTAGE_SOURCE_VLCD
  *                             - \ref LCD_VOLTAGE_SOURCE_AVDD
  *                             - \ref LCD_VOLTAGE_SOURCE_CP
  *
  * @return     None
  *
  * @details    This macro is used to select LCD operation voltage source.
  */
#define LCD_VOLTAGE_SOURCE(source)  (LCD->DCTL = (LCD->DCTL & ~LCD_DCTL_VSRC_Msk) | (source))

/**
  * @brief      Set LCD Driving Mode
  *
  * @param[in]  mode        The LCD operation driving mode. It could be one of the following mode
  *                             - \ref LCD_LOW_DRIVING_AND_BUF_OFF
  *                             - \ref LCD_HIGH_DRIVING_AND_BUF_OFF
  *                             - \ref LCD_LOW_DRIVING_AND_BUF_ON
  *                             - \ref LCD_HIGH_DRIVING_AND_BUF_OFF_AND_PWR_SAVING
  *                             - \ref LCD_LOW_DRIVING_AND_BUF_ON_AND_PWR_SAVING
  *
  * @return     None
  *
  * @details    This macro is used to set LCD operation drivig mode.
  */
#define LCD_DRIVING_MODE(mode)      (LCD->DCTL = (LCD->DCTL & ~(LCD_DCTL_RESMODE_Msk | LCD_DCTL_BUFEN_Msk | LCD_DCTL_PSVEN_Msk)) | (mode))

/**
  * @brief      Select Power Saving Mode
  *
  * @param[in]  mode        The LCD power saving mode selection. It could be one of the following constant definition
  *                             - \ref LCD_PWR_SAVING_NORMAL_MODE
  *                             - \ref LCD_PWR_SAVING_REVERSE_MODE
  *
  * @return     None
  *
  * @details    This macro is used to set the LCD power saving mode.
  *             When the timing of power saving mode is reversed, the original power saving period becomes no power saving,
  *             and the original no power saving period becomes power saving.
  */
#define LCD_PWR_SAVING_MODE(mode)   (LCD->DCTL = (LCD->DCTL & ~LCD_DCTL_PSVREV_Msk) | (mode))

/**
  * @brief      Set Power Saving T1 Period
  *
  * @param[in]  t1      The number of t1 to determine T1 period, valid value is between 1 to 16.
  *                     And one unit of t1 period is half of LCD operation clock period.
  *
  * @return     None
  *
  * @details    This macro is used to configure the T1 (Enable Time) period of power saving.
  */
#define LCD_PWR_SAVING_T1_PERIOD(t1)    (LCD->DCTL = (LCD->DCTL & ~LCD_DCTL_PSVT1_Msk) | (((t1)-1) << LCD_DCTL_PSVT1_Pos))

/**
  * @brief      Set Power Saving T2 Period
  *
  * @param[in]  t2      The number of t2 to determine T2 period, valid value is between 1 to 16.
  *                     And one unit of t1 period is half of LCD operation clock period.
  *
  * @return     None
  *
  * @details    This macro is used to configure the T2 (On Time) period of power saving.
  */
#define LCD_PWR_SAVING_T2_PERIOD(t2)    (LCD->DCTL = (LCD->DCTL & ~LCD_DCTL_PSVT2_Msk) | (((t2)-1) << LCD_DCTL_PSVT2_Pos))

/**
  * @brief      Set Charging Timeout Time
  *
  * @param[in]  value   The maximum timeout value, valid value is between 1 to 8192.
  *                     And one unit of timeout value is one LCD operation clock period.
  *
  * @return     None
  *
  * @details    This macro is used to set maximum timeout time of charge pump charging timer.
  */
#define LCD_SET_CHARGE_TIMEOUT_TIME(value)  (LCD->DCTL = (LCD->DCTL & ~LCD_DCTL_CTOTIME_Msk) | (((value)-1) << LCD_DCTL_CTOTIME_Pos))

/**
  * @brief      Select Device Package Type
  *
  * @param[in]  pak     Select device package type.
  *                     0 for 128-pin package, and 1 for 64-pin package.
  *
  * @return     None
  *
  * @details    This macro is used to select device output pins for LCD controller with different package type.
  */
#define LCD_SELECT_PACKAGE_TYPE(pkg)    (LCD->PKGSEL = (LCD->PKGSEL & ~LCD_PKGSEL_PKG_Msk) | ((pkg) << LCD_PKGSEL_PKG_Pos))

/**
  * @brief      Enable LCD Frame Counting End Interrupt
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to enable frame count end interrupt function.
  */
#define LCD_ENABLE_FRAME_COUNTING_END_INT()     (LCD->INTEN |= LCD_INTEN_FCEIEN_Msk)

/**
  * @brief      Disable LCD Frame Counting End Interrupt
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to disable frame count end interrupt function.
  */
#define LCD_DISABLE_FRAME_COUNTING_END_INT()    (LCD->INTEN &= ~LCD_INTEN_FCEIEN_Msk)

/**
  * @brief      Enable LCD Frame End Interrupt
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to enable frame end interrupt function.
  */
#define LCD_ENABLE_FRAME_END_INT()      (LCD->INTEN |= LCD_INTEN_FEIEN_Msk)

/**
  * @brief      Disable LCD Frame End Interrupt
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to disable frame end interrupt function.
  */
#define LCD_DISABLE_FRAME_END_INT()     (LCD->INTEN &= ~LCD_INTEN_FEIEN_Msk)

/**
  * @brief      Enable Charging Timeout Interrupt
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to enable charge pump charging timeout interrupt function.
  */
#define LCD_ENABLE_CHARGE_TIMEOUT_INT()     (LCD->INTEN |= LCD_INTEN_CTOIEN_Msk)

/**
  * @brief      Disable Charging Timeout Interrupt
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to disable charge pump charging timeout interrupt function.
  */
#define LCD_DISABLE_CHARGE_TIMEOUT_INT()    (LCD->INTEN &= ~LCD_INTEN_CTOIEN_Msk)

/**
  * @brief      Get LCD Frame Counting End Flag
  *
  * @param      None
  *
  * @retval     0   Frame count end flag did not occur
  * @retval     1   Frame count end flag occurred
  *
  * @details    This macro gets frame count end flag.
  */
#define LCD_GET_FRAME_COUNTING_END_FLAG()   ((LCD->STS & LCD_STS_FCEF_Msk)? 1UL : 0UL)

/**
  * @brief      Clear LCD Frame Counting End Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro clears frame count end flag.
  */
#define LCD_CLEAR_FRAME_COUNTING_END_FLAG() (LCD->STS = LCD_STS_FCEF_Msk)

/**
  * @brief      Get LCD Frame End Flag
  *
  * @param      None
  *
  * @retval     0   Frame end flag did not occur
  * @retval     1   Frame end flag occurred
  *
  * @details    This macro gets frame end flag.
  */
#define LCD_GET_FRAME_END_FLAG()            ((LCD->STS & LCD_STS_FEF_Msk)? 1UL : 0UL)

/**
  * @brief      Clear LCD Frame End Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro clears frame end flag.
  */
#define LCD_CLEAR_FRAME_END_FLAG()          (LCD->STS = LCD_STS_FEF_Msk)

/**
  * @brief      Get Charging Timeout Flag
  *
  * @param      None
  *
  * @retval     0   Charge pump timer timeout flag did not occur
  * @retval     1   Charge pump timer timeout flag occurred
  *
  * @details    This macro gets charge pump charging timeout flag.
  */
#define LCD_GET_CHARGE_TIMEOUT_FLAG()       ((LCD->STS & LCD_STS_CTOF_Msk)? 1UL : 0UL)

/**
  * @brief      Clear Charging Timeout Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro clears charge pump charging timeout flag.
  */
#define LCD_CLEAR_CHARGE_TIMEOUT_FLAG()     (LCD->STS = LCD_STS_CTOF_Msk)

/**
  * @brief      Get Charging Time
  *
  * @param      None
  *
  * @return     Current 13-bit charging timer value
  *
  * @details    This macro gets charging timer value while stops charge pump charging.
  */
#define LCD_GET_CHARGE_TIME()              ((LCD->STS & LCD_STS_CTIME_Msk) >> 16)


uint32_t LCD_Open(S_LCD_CFG_T *pLCDCfg);
void LCD_Close(void);
void LCD_SetPixel(uint32_t u32Com, uint32_t u32Seg, uint32_t u32OnFlag);
void LCD_SetAllPixels(uint32_t u32OnOff);
uint32_t LCD_EnableBlink(uint32_t u32ms);
void LCD_DisableBlink(void);
void LCD_EnableInt(uint32_t u32IntSrc);
void LCD_DisableInt(uint32_t u32IntSrc);

/**@}*/ /* end of group LCD_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group LCD_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_LCD_H__ */
