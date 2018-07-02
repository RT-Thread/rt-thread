/*****************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
 *
 * This software is owned and published by:
 * Huada Semiconductor Co.,Ltd ("HDSC").
 *
 * BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
 * BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
 *
 * This software contains source code for use with HDSC
 * components. This software is licensed by HDSC to be adapted only
 * for use in systems utilizing HDSC components. HDSC shall not be
 * responsible for misuse or illegal use of this software for devices not
 * supported herein. HDSC is providing this software "AS IS" and will
 * not be responsible for issues arising from incorrect user implementation
 * of the software.
 *
 * Disclaimer:
 * HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
 * REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
 * ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
 * WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
 * WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
 * WARRANTY OF NONINFRINGEMENT.
 * HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
 * LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
 * INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
 * SAVINGS OR PROFITS,
 * EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
 * INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
 * FROM, THE SOFTWARE.
 *
 * This software may be replicated in part or whole for the licensed use,
 * with the restriction that this Disclaimer and Copyright notice must be
 * included with each copy of this software, whether used in part or whole,
 * at all times.
 */
/******************************************************************************/
/** \file rtc.h
 **
 ** A detailed description is available at
 ** @link RtcGroup Rtc description @endlink
 **
 **   - 2018-03-20  1.0  yangjp First version for Device Driver Library of Rtc.
 **
 ******************************************************************************/

#ifndef __RTC_H__
#define __RTC_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f480.h"
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup RtcGroup Real-time Clock(Rtc)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
  /**
 *******************************************************************************
 ** \brief Rtc date and time format enumeration
 **
 ******************************************************************************/
typedef enum
{
    Rtc_Format_Dec = 0x00,  /*!< Decimal format */
    Rtc_Format_Bcd = 0x01   /*!< BCD format     */
}en_rtc_format_t;

/**
 *******************************************************************************
 ** \brief Rtc intrusion channel enumeration
 **
 ******************************************************************************/
typedef enum
{
    Rtc_Intrusion_Ch0 = 0x00,  /*!< RTCC0 input pin intrusion function */
    Rtc_Intrusion_Ch1 = 0x01   /*!< RTCC1 input pin intrusion function */
}en_rtc_intrusion_ch_t;

/**
 *******************************************************************************
 ** \brief Rtc 1Hz output format selection enumeration
 **
 ******************************************************************************/
typedef enum
{
    Rtc_Output_Distributed = 0x00,  /*!< Distributed Compensation 1hz output */
    Rtc_Output_Uniform     = 0x01   /*!< Uniform Compensation 1hz output     */
}en_rtc_output_format_t;

/**
 *******************************************************************************
 ** \brief Rtc time format selection enumeration
 **
 ******************************************************************************/
typedef enum
{
    Rtc_Hour_Format_12 = 0x00,  /*!< 12 hours */
    Rtc_Hour_Format_24 = 0x01   /*!< 24 hours */
}en_rtc_hour_format_t;

/**
 *******************************************************************************
 ** \brief Rtc 12 hour AM/PM selection enumeration
 **
 ******************************************************************************/
typedef enum
{
    Rtc_Hour12_AM = 0x00,  /*!< ante meridiem */
    Rtc_Hour12_PM = 0x01   /*!< post meridiem */
}en_rtc_hour12_AmPm_t;

/**
 *******************************************************************************
 ** \brief Rtc period interrupt selection enumeration
 **
 ******************************************************************************/
typedef enum
{
    Rtc_Period_Int_Disable     = 0x00,  /*!< disable period interrupt    */
    Rtc_Period_Int_OneHalf_Sec = 0x01,  /*!< 0.5 second period interrupt */
    Rtc_Period_Int_One_Sec     = 0x02,  /*!< 1 second period interrupt   */
    Rtc_Period_Int_One_Min     = 0x03,  /*!< 1 minute period interrupt   */
    Rtc_Period_Int_One_Hour    = 0x04,  /*!< 1 hour period interrupt     */
    Rtc_Period_Int_One_Day     = 0x05,  /*!< 1 day period interrupt      */
    Rtc_Period_Int_One_Mon     = 0x06   /*!< 1 month period interrupt    */
}en_rtc_period_interrupt_t;

/**
 *******************************************************************************
 ** \brief Rtc run mode enumeration
 **
 ******************************************************************************/
typedef enum
{
    Rtc_Mode_Normal_Count = 0x00,  /*!< normal count mode  */
    Rtc_Mode_Read_Write   = 0x01   /*!< write or read mode */
}en_rtc_run_mode_t;

/**
 *******************************************************************************
 ** \brief Rtc Count clock source selection enumeration
 **
 ******************************************************************************/
typedef enum
{
    Rtc_Clock_Xtal32 = 0x00,  /*!< select XTAL32 as clock source */
    Rtc_Clock_Lrc    = 0x01   /*!< select LRC as clock source    */
}en_rtc_clock_t;

/**
 *******************************************************************************
 ** \brief Rtc intrusion filtering function enumeration
 **
 ******************************************************************************/
typedef enum
{
    Rtc_Intrusion_Filter_Disable        = 0x00,  /*!< filter function invalid          */
    Rtc_Intrusion_Filter_Onethird       = 0x02,  /*!< One-third filter on input pin    */
    Rtc_Intrusion_Filter_32Div_Onethird = 0x03   /*!< One-third filter on input pin and \
                                                  clock is divided by 32 */
}en_rtc_intrusion_filter_t;

/**
 *******************************************************************************
 ** \brief Rtc intrusion valid edge selection enumeration
 **
 ******************************************************************************/
typedef enum
{
    Rtc_Intrusion_Edge_Disable        = 0x00,  /*!< RTCCx input pin disable                */
    Rtc_Intrusion_Edge_Rising         = 0x01,  /*!< Detected rising edge of RTCCx input pin is active  */
    Rtc_Intrusion_Edge_Falling        = 0x02,  /*!< Detected falling edge of RTCCx input pin is active */
    Rtc_Intrusion_Edge_Rising_Falling = 0x03   /*!< Detected rising or falling edge of RTCCx input pin is active */
}en_rtc_intrusion_edge_t;

/**
 *******************************************************************************
 ** \brief Rtc month enumeration
 **
 ******************************************************************************/
typedef enum
{
    Rtc_Month_January   = 0x01,  /*!< January   */
    Rtc_Month_February  = 0x02,  /*!< February  */
    Rtc_Month_March     = 0x03,  /*!< March     */
    Rtc_Month_April     = 0x04,  /*!< April     */
    Rtc_Month_May       = 0x05,  /*!< May       */
    Rtc_Month_June      = 0x06,  /*!< June      */
    Rtc_Month_July      = 0x07,  /*!< July      */
    Rtc_Month_August    = 0x08,  /*!< August    */
    Rtc_Month_September = 0x09,  /*!< September */
    Rtc_Month_October   = 0x10,  /*!< October   */
    Rtc_Month_November  = 0x11,  /*!< November  */
    Rtc_Month_December  = 0x12   /*!< December  */
}en_rtc_month_t;

/**
 *******************************************************************************
 ** \brief Rtc weekday enumeration
 **
 ******************************************************************************/ 
typedef enum
{
    Rtc_Weekday_Sunday    = 0x00,  /*!< Sunday    */
    Rtc_Weekday_Monday    = 0x01,  /*!< Monday    */
    Rtc_Weekday_Tuesday   = 0x02,  /*!< Tuesday   */
    Rtc_Weekday_Wednesday = 0x03,  /*!< Wednesday */
    Rtc_Weekday_Thursday  = 0x04,  /*!< Thursday  */
    Rtc_Weekday_Friday    = 0x05,  /*!< Friday    */
    Rtc_Weekday_Saturday  = 0x06   /*!< Saturday  */
}en_rtc_weekday_t;   

/**
 *******************************************************************************
 ** \brief Rtc alarm weekday enumeration
 **
 ******************************************************************************/ 
typedef enum
{
    Rtc_Alarm_Weekday_Sunday    = 0x01,  /*!< Sunday    */
    Rtc_Alarm_Weekday_Monday    = 0x02,  /*!< Monday    */
    Rtc_Alarm_Weekday_Tuesday   = 0x04,  /*!< Tuesday   */
    Rtc_Alarm_Weekday_Wednesday = 0x08,  /*!< Wednesday */
    Rtc_Alarm_Weekday_Thursday  = 0x10,  /*!< Thursday  */
    Rtc_Alarm_Weekday_Friday    = 0x20,  /*!< Friday    */
    Rtc_Alarm_Weekday_Saturday  = 0x40   /*!< Saturday  */
}en_rtc_alarm_weekday_t; 

/**
 *******************************************************************************
 ** \brief Rtc interrupt type definition
 **
 **
 ******************************************************************************/
typedef enum
{
    Rtc_Int_Intrusion_Ch0 = 0x00,  /*!< rtc intrusion detection interrupt channel 0 */
    Rtc_Int_Intrusion_Ch1 = 0x01,  /*!< rtc intrusion detection interrupt channel 1 */
    Rtc_Int_Alarm         = 0x02,  /*!< rtc alarm interrupt               */
    Rtc_Int_Period_Count  = 0x03,  /*!< rtc period count interrupt        */
    Rtc_Int_Compensation  = 0x04   /*!< rtc clock compensation interrupt  */
} en_rtc_interrupt_t;

/**
 *******************************************************************************
 ** \brief Rtc event flag enumeration
 **
 ******************************************************************************/
typedef enum
{
    Rtc_Flag_Intrusion_Flag0    = 0x00,  /*!< RTCC0 Pin trigger intrusion event flag */
    Rtc_Flag_Intrusion_Flag1    = 0x01,  /*!< RTCC1 Pin trigger intrusion event flag */
    Rtc_Flag_Intrusion_Overflow = 0x02,  /*!< trigger intrusion overflow flag        */
    Rtc_Falg_Alarm_Clock        = 0x03,  /*!< alarm clock match flag                 */
    Rtc_Flag_Period             = 0x04   /*!< rtc count period flag                  */
}en_rtc_flag_t;

/**
 *******************************************************************************
 ** \brief Rtc date and Time structure definition
 **
 ******************************************************************************/
typedef struct
{
    uint8_t  u8Year;        /*!< Year (range 0-99)             */
    uint8_t  u8Month;       /*!< Month (range 1-12)            */
    uint8_t  u8Day;         /*!< Day (range 1-31)              */
    uint8_t  u8Hour;        /*!< Hours (if Rtc_Hour_Format_12,range 1-12; if Rtc_Hour_Format_24,range 0-23) */
    uint8_t  u8Minute;      /*!< Minutes (range 0-59)          */
    uint8_t  u8Second;      /*!< Seconds (range 0-59)          */
    uint8_t  u8Weekday;     /*!< Weekday (range 0-6)           */
    uint8_t  u8AmPm;        /*!< 12-hour mode setting is valid */
}stc_rtc_time_t;

/**
 *******************************************************************************
 ** \brief Rtc alarm Time structure definition
 **
 ******************************************************************************/
typedef struct
{
    uint8_t  u8Minute;      /*!< Minutes (range 0-59)                        */
    uint8_t  u8Hour;        /*!< Hours (Hours (if Rtc_Hour_Format_12,range 1-12; if Rtc_Hour_Format_24,range 0-23) */
    uint8_t  u8Weekday;     /*!< Weekday (range bit0-bit6 = Sunday-Saturday) */
    uint8_t  u8AmPm;        /*!< 12-hour mode setting is valid */
}stc_rtc_alarm_t;

/**
 *******************************************************************************
 ** \brief Rtc intrusion detection structure definition
 **
 ******************************************************************************/
typedef struct
{
    en_rtc_intrusion_edge_t enEdge;      /*!< valid input edges */
    en_rtc_intrusion_filter_t enFilter;  /*!< input filter function */
    boolean_t bTimeStampEn;              /*!< enable/disable timestamp */
    boolean_t bIntrusionResetEn;         /*!< enablle/disable intrusion trigger backup register reset */
}stc_rtc_intrusion_t;

/**
 *******************************************************************************
 ** \brief Rtc timestamp structure definition
 **
 ******************************************************************************/
typedef struct
{
    uint8_t  u8Month;       /*!< Month (range 1-12)            */
    uint8_t  u8Day;         /*!< Day (range 1-31)              */
    uint8_t  u8Hour;        /*!< Hours (if Rtc_Hour_Format_12,range 1-12; if Rtc_Hour_Format_24,range 0-23) */
    uint8_t  u8Minute;      /*!< Minutes (range 0-59)          */
    uint8_t  u8Second;      /*!< Seconds (range 0-59)          */
    uint8_t  u8AmPm;        /*!< 12-hour mode setting is valid */
}stc_rtc_timestamp_t;

/**
 *******************************************************************************
 ** \brief Rtc init structure definition
 **
 ******************************************************************************/
typedef struct
{
   en_rtc_clock_t enClk;               /*!< rtc clock source  */
   en_rtc_hour_format_t enHourFormat;  /*!< rtc hour format   */
}stc_rtc_init_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/* Initialization Configuration functions *************************************/
en_result_t Rtc_Init(stc_rtc_init_t *stcRtcInit);
en_result_t Rtc_DeInit(void);
void Rtc_CountCmd(boolean_t bCountEn);
en_result_t Rtc_EnterRwMode(void);
en_result_t Rtc_ExitRwMode(void);

/* switch low power mode functions ********************************************/
en_result_t Rtc_LowPowerSwitch(void);

/* date and time configuration function ***************************************/
en_result_t Rtc_SetDateTime(en_rtc_format_t enFormat, stc_rtc_time_t *stcRtcDateTime,
                            boolean_t bUpdateDate, boolean_t bUpdateTime);
en_result_t Rtc_GetDateTime(en_rtc_format_t enFormat, stc_rtc_time_t *stcRtcDateTime);

/* alarm clock time configuration function ************************************/
void Rtc_SetAlarmTime(en_rtc_format_t enFormat, stc_rtc_alarm_t *stcRtcAlarmTime);
void Rtc_GetAlarmTime(en_rtc_format_t enFormat, stc_rtc_alarm_t *stcRtcAlarmTime);
void Rtc_AlarmCmd(boolean_t bAlarmEn);

/* period interrupt configuration function ************************************/
void Rtc_PeriodIntConfig(en_rtc_period_interrupt_t enIntSel);

/* one hz output configuration function ***************************************/
void Rtc_OutputConfig(en_rtc_output_format_t enSel, boolean_t bOutputEn);

/* clock compensation configuration function **********************************/
void Rtc_ClockCompenConfig(uint16_t u16Val, boolean_t bClockCompenEn);

/* intrusion event detection configuration function ***************************/
void Rtc_IntrusionInit(en_rtc_intrusion_ch_t enChannel, stc_rtc_intrusion_t *stcRtcIntrusionInit);
void Rtc_IntrusionCmd(en_rtc_intrusion_ch_t enChannel, boolean_t bIntrusionEn);
void Rtc_GetTimeStamp(en_rtc_format_t enFormat, stc_rtc_timestamp_t *stcRtcTimestamp);

/* status flags management functions ******************************************/
void Rtc_IntConfig(en_rtc_interrupt_t enIntSel, boolean_t bIntEn);
en_stat_flag_t Rtc_GetFlagStatus(en_rtc_flag_t enFlag);
void Rtc_ClearFlag(en_rtc_flag_t enFlag);


//@} // RtcGroup

#ifdef __cplusplus
}
#endif

#endif /* __RTC_H_ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
