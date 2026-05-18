/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_rtc.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76X_78X_RTC_H__
#define __N32H76X_78X_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"

/** RTC Init structure definition **/
typedef struct
{
    uint32_t RTC_HourFormat;    /* Specifies the RTC Hour Format. */

    uint32_t RTC_AsynchPrediv;  /* Specifies the RTC Asynchronous Predivider value */

    uint32_t RTC_SynchPrediv;   /* Specifies the RTC Synchronous Predivider value */
} RTC_InitType;


/** RTC Time structure definition **/
typedef struct
{
    uint8_t Hours;      /* Specifies the RTC Time Hour */

    uint8_t Minutes;    /* Specifies the RTC Time Minutes */

    uint8_t Seconds;    /* Specifies the RTC Time Seconds */

    uint8_t H12;        /* Specifies the RTC AM/PM Time */
} RTC_TimeType;

/** RTC Date structure definition **/
typedef struct
{
    uint8_t WeekDay;    /* Specifies the RTC Date WeekDay */

    uint8_t Month;      /* Specifies the RTC Date Month (in BCD format) */

    uint8_t Date;       /* Specifies the RTC Date */

    uint8_t Year;       /* Specifies the RTC Date Year */
} RTC_DateType;

/** RTC Alarm structure definition **/
typedef struct
{
    RTC_TimeType AlarmTime; /* Specifies the RTC Alarm Time members. */

    uint32_t AlarmMask;     /* Specifies the RTC Alarm Masks */

    uint32_t DateWeekMode;  /* Specifies the RTC Alarm is on Date or WeekDay */

    uint8_t DateWeekValue;  /* Specifies the RTC Alarm Date/WeekDay */
} RTC_AlarmType;


#define RTC_REG_BIT_MASK                        ((uint32_t)0x00000000)

/** RTC_Hour_Formats **/
#define RTC_24HOUR_FORMAT                        (RTC_REG_BIT_MASK)
#define RTC_12HOUR_FORMAT                        (RTC_CTRL_HFMT)

/** Masks Definition **/
#define RTC_TR_RESERVED_MASK                     ((uint32_t)0x007F7F7FU)
#define RTC_DATE_RESERVED_MASK                   ((uint32_t)0x00FFFF3FU)

#define RTC_RSF_MASK                             ((uint32_t)0xFFFFFFDFU)
#define RTC_FLAGS_MASK                           ((uint32_t)(0x1FFFF7F))

/** RTC_TIMEOUT_Definitions**/
#define INITMODE_TIMEOUT                         ((uint32_t)0x00020000)
#define SYNCHRO_TIMEOUT                          ((uint32_t)0x00080000)
#define RECALPF_TIMEOUT                          ((uint32_t)0x00010000)
#define SHPF_TIMEOUT                             ((uint32_t)0x00020000)

/** RTC_AM_PM_Definitions **/
#define RTC_AM_H12                               ((uint8_t)0x00)
#define RTC_PM_H12                               (RTC_CTRL_HFMT)

/** Coded in BCD format **/
#define RTC_MONTH_JANUARY                        ((uint8_t)0x01)
#define RTC_MONTH_FEBRURY                        ((uint8_t)0x02)
#define RTC_MONTH_MARCH                          ((uint8_t)0x03)
#define RTC_MONTH_APRIL                          ((uint8_t)0x04)
#define RTC_MONTH_MAY                            ((uint8_t)0x05)
#define RTC_MONTH_JUNE                           ((uint8_t)0x06)
#define RTC_MONTH_JULY                           ((uint8_t)0x07)
#define RTC_MONTH_AUGUST                         ((uint8_t)0x08)
#define RTC_MONTH_SEPTEMBER                      ((uint8_t)0x09)
#define RTC_MONTH_OCTOBER                        ((uint8_t)0x10)
#define RTC_MONTH_NOVEMBER                       ((uint8_t)0x11)
#define RTC_MONTH_DECEMBER                       ((uint8_t)0x12)

/** RTC_WeekDay_Definitions **/
#define RTC_WEEKDAY_MONDAY                       ((uint8_t)0x01)
#define RTC_WEEKDAY_TUESDAY                      ((uint8_t)0x02)
#define RTC_WEEKDAY_WEDNESDAY                    ((uint8_t)0x03)
#define RTC_WEEKDAY_THURSDAY                     ((uint8_t)0x04)
#define RTC_WEEKDAY_FRIDAY                       ((uint8_t)0x05)
#define RTC_WEEKDAY_SATURDAY                     ((uint8_t)0x06)
#define RTC_WEEKDAY_SUNDAY                       ((uint8_t)0x07)

/** RTC_AlarmDateWeekDay_Definitions **/
#define RTC_ALARM_SEL_WEEKDAY_DATE               (RTC_REG_BIT_MASK)
#define RTC_ALARM_SEL_WEEKDAY_WEEKDAY            (RTC_ALARMA_WKDSEL)

/** RTC_AlarmMask_Definitions **/
#define RTC_ALARMMASK_NONE                       (RTC_REG_BIT_MASK)
#define RTC_ALARMMASK_WEEKDAY                    (RTC_ALARMA_MASK4)
#define RTC_ALARMMASK_HOURS                      (RTC_ALARMA_MASK3)
#define RTC_ALARMMASK_MINUTES                    (RTC_ALARMA_MASK2)
#define RTC_ALARMMASK_SECONDS                    (RTC_ALARMA_MASK1)
#define RTC_ALARMMASK_ALL                        (RTC_ALARMA_MASK4 | RTC_ALARMA_MASK3 | RTC_ALARMA_MASK2 | RTC_ALARMA_MASK1)

/** RTC_Alarms_Definitions **/
#define RTC_A_ALARM                              (RTC_CTRL_ALAEN)
#define RTC_B_ALARM                              (RTC_CTRL_ALBEN)

/** RTC_Bypass_Definitions **/
#define RTC_BYPASS_UPDATE                        (RTC_CTRL_BYPS)

/* RTC_Alarm_Sub_Seconds_Masks_Definitions */
#define RTC_SUBS_MASK_ALL       (RTC_REG_BIT_MASK)        /* All Alarm SS fields are masked There is no comparison on sub seconds for Alarm */
#define RTC_SUBS_MASK_SS14_1    (RTC_ALRMASS_MASKSSB_0)   /* SS[14:1] are don't care in Alarm comparison. Only SS[0] is compared */
#define RTC_SUBS_MASK_SS14_2    (RTC_ALRMASS_MASKSSB_1)   /* SS[14:2] are don't care in Alarm comparison. Only SS[1:0] are compared */
#define RTC_SUBS_MASK_SS14_3    (RTC_ALRMASS_MASKSSB_0 | RTC_ALRMASS_MASKSSB_1)  /* SS[14:3] are don't care in Alarm comparison. Only SS[2:0] are compared */
#define RTC_SUBS_MASK_SS14_4    (RTC_ALRMASS_MASKSSB_2)   /* SS[14:4] are don't care in Alarm comparison. Only SS[3:0] are compared */
#define RTC_SUBS_MASK_SS14_5    (RTC_ALRMASS_MASKSSB_2 | RTC_ALRMASS_MASKSSB_0)  /* SS[14:5] are don't care in Alarm comparison. Only SS[4:0] are compared */
#define RTC_SUBS_MASK_SS14_6    (RTC_ALRMASS_MASKSSB_2 | RTC_ALRMASS_MASKSSB_1)  /* SS[14:6] are don't care in Alarm comparison. Only SS[5:0] are compared */
#define RTC_SUBS_MASK_SS14_7    (RTC_ALRMASS_MASKSSB_2 | RTC_ALRMASS_MASKSSB_1 | RTC_ALRMASS_MASKSSB_0)  /* SS[14:7] are don't care in Alarm comparison. Only SS[6:0] are compared */
#define RTC_SUBS_MASK_SS14_8    (RTC_ALRMASS_MASKSSB_3)   /* SS[14:8] are don't care in Alarm comparison. Only SS[7:0] are compared */
#define RTC_SUBS_MASK_SS14_9    (RTC_ALRMASS_MASKSSB_3 | RTC_ALRMASS_MASKSSB_0)  /* SS[14:9] are don't care in Alarm comparison. Only SS[8:0] are compared */
#define RTC_SUBS_MASK_SS14_10   (RTC_ALRMASS_MASKSSB_3 | RTC_ALRMASS_MASKSSB_1)  /* SS[14:10] are don't care in Alarm comparison. Only SS[9:0] are compared */
#define RTC_SUBS_MASK_SS14_11   (RTC_ALRMASS_MASKSSB_3 | RTC_ALRMASS_MASKSSB_1 | RTC_ALRMASS_MASKSSB_0)  /* SS[14:11] are don't care in Alarm comparison. Only SS[10:0] are compared */
#define RTC_SUBS_MASK_SS14_12   (RTC_ALRMASS_MASKSSB_3 | RTC_ALRMASS_MASKSSB_2)  /* SS[14:12] are don't care in Alarm comparison.Only SS[11:0] are compared */
#define RTC_SUBS_MASK_SS14_13   (RTC_ALRMASS_MASKSSB_3 | RTC_ALRMASS_MASKSSB_2 | RTC_ALRMASS_MASKSSB_0)  /* SS[14:13] are don't care in Alarm comparison. Only SS[12:0] are compared */
#define RTC_SUBS_MASK_SS14_14   (RTC_ALRMASS_MASKSSB_3 | RTC_ALRMASS_MASKSSB_2 | RTC_ALRMASS_MASKSSB_1)  /* SS[14] is don't care in Alarm comparison.Only SS[13:0] are compared */
#define RTC_SUBS_MASK_NONE      (RTC_ALRMASS_MASKSSB_3 | RTC_ALRMASS_MASKSSB_2 | RTC_ALRMASS_MASKSSB_1 | RTC_ALRMASS_MASKSSB_0)  /* SS[14:0] are compared and must match to activate alarm */


typedef enum
{
    RTC_WKUPCLK_RTCCLK_DIV16   = (RTC_REG_BIT_MASK),
    RTC_WKUPCLK_RTCCLK_DIV8    = (RTC_CTRL_WKUPSEL_0),
    RTC_WKUPCLK_RTCCLK_DIV4    = (RTC_CTRL_WKUPSEL_1),
    RTC_WKUPCLK_RTCCLK_DIV2    = (RTC_CTRL_WKUPSEL_0 | RTC_CTRL_WKUPSEL_1),
    RTC_WKUPCLK_CK_SPRE_16BITS = (RTC_CTRL_WKUPSEL_2),
    RTC_WKUPCLK_CK_SPRE_17BITS = (RTC_CTRL_WKUPSEL_1 | RTC_CTRL_WKUPSEL_2),
}RTC_WAKE_UP_CLOCK;


/** RTC_Time_Stamp_Edges_definitions **/
#define RTC_TIMESTAMP_EDGE_RISING                (RTC_REG_BIT_MASK)
#define RTC_TIMESTAMP_EDGE_FALLING               (RTC_CTRL_TEDGE)

/** RTC_Reference_Detection_definitions **/
#define RTC_REFERENCE_DETECT_DISABLE             (RTC_REG_BIT_MASK)
#define RTC_REFERENCE_DETECT_ENABLE              (RTC_CTRL_REFCLKEN)

/** RTC_Output_selection_Definitions **/
#define RTC_OUTPUT_DIS                           (RTC_REG_BIT_MASK)
#define RTC_OUTPUT_ALA                           (RTC_CTRL_OUTSEL_0)
#define RTC_OUTPUT_ALB                           (RTC_CTRL_OUTSEL_1)
#define RTC_OUTPUT_WKUP                          (RTC_CTRL_OUTSEL_0 | RTC_CTRL_OUTSEL_1)

#define RTC_OUTPUT_TAMP                          (RTC_CTRL_TAMPOE)
#define RTC_OUTPUT2_EN                           (RTC_CTRL_OUT2EN)

/** RTC_Output_Polarity_Definitions **/
#define RTC_OUTPOL_HIGH                          (RTC_REG_BIT_MASK)
#define RTC_OUTPOL_LOW                           (RTC_CTRL_OPOL)

/** RTC_Calib_Output_selection_Definitions **/
#define RTC_CALIB_OUTPUT_256HZ                   (RTC_REG_BIT_MASK)
#define RTC_CALIB_OUTPUT_1HZ                     (RTC_CTRL_CALOSEL)

/** if RTCCLK = 32768 Hz, Smooth calibation period is 32s,  else 2exp20 RTCCLK seconds **/
#define SMOOTH_CALIB_32SEC                       (RTC_REG_BIT_MASK)

/** if RTCCLK = 32768 Hz, Smooth calibation period is 16s, else 2exp19 RTCCLK seconds **/
#define SMOOTH_CALIB_16SEC                       (RTC_CALIB_CW16) 

/** if RTCCLK = 32768 Hz, Smooth calibation period is 8s, else 2exp18 RTCCLK seconds **/
#define SMOOTH_CALIB_8SEC                        (RTC_CALIB_CW8) 

/** The number of RTCCLK pulses added during a X -second window = Y - CALM[8:0]  with Y = 512, 256, 128 when X = 32, 16, 8 **/
#define RTC_SMOOTH_CALIB_PLUS_PULSES_SET         (RTC_CALIB_CP)

/** The number of RTCCLK pulses subbstited during a 32-second window =   CALM[8:0] **/
#define RTC_SMOOTH_CALIB_PLUS_PULSES_RESET       (RTC_REG_BIT_MASK) 

/** RTC_DayLightSaving_Definitions **/
#define RTC_DAYLIGHT_SAVING_SUB1H                (RTC_CTRL_SU1H)
#define RTC_DAYLIGHT_SAVING_ADD1H                (RTC_CTRL_AD1H)

#define RTC_STORE_OPERATION_RESET                (RTC_REG_BIT_MASK)
#define RTC_STORE_OPERATION_SET                  (RTC_CTRL_BAKP)

/** RTC_Output_Type_ALARM_OUT **/
#define RTC_OUTPUT_PUSHPULL                      (RTC_REG_BIT_MASK)
#define RTC_OUTPUT_OPENDRAIN                     (RTC_OPT_TYPE)

/** RTC_PWR_SIGNAL_TYPE **/
#define RTC_PWR_SIGNAL_PULSE                     (RTC_REG_BIT_MASK)
#define RTC_PWR_SIGNAL_LEVEL                     (RTC_OPT_PWREST)

/** RTC_Output_Duty_Cycle **/
#define RTC_Output_Duty_50                       (RTC_REG_BIT_MASK)
#define RTC_Output_Duty_DIV                      (RTC_OPT_OPDC)

/** RTC_Add_Fraction_Of_Second_Value **/
#define RTC_SHIFT_SUB1S_DISABLE                  (RTC_REG_BIT_MASK)
#define RTC_SHIFT_SUB1S_ENABLE                   (RTC_SCTRL_AD1S)

/** RTC_Input_parameter_format_definitions **/
#define RTC_FORMAT_BIN                           (RTC_REG_BIT_MASK)     //BIN format
#define RTC_FORMAT_BCD                           (0x00000001)           //register format

/** RTC_Flags_Definitions **/
#define RTC_INT_FLAG_RESERVED_MASK               ((uint32_t)0x01FFFFFF)

#define RTC_FLAG_BPRAM_ERF                       (RTC_INITSTS_BKSRAMREF)
#define RTC_FLAG_ITISF                           (RTC_INITSTS_IETSF)
#define RTC_FLAG_CALOVF                          (RTC_INITSTS_CAOVF)
#define RTC_FLAG_TAMP8F                          (RTC_INITSTS_TAM8F)
#define RTC_FLAG_TAMP7F                          (RTC_INITSTS_TAM7F)
#define RTC_FLAG_TAMP6F                          (RTC_INITSTS_TAM6F)
#define RTC_FLAG_TAMP5F                          (RTC_INITSTS_TAM5F)
#define RTC_FLAG_TAMP4F                          (RTC_INITSTS_TAM4F)
#define RTC_FLAG_RECPF                           (RTC_INITSTS_RECPF)
#define RTC_FLAG_TAMP3F                          (RTC_INITSTS_TAM3F)
#define RTC_FLAG_TAMP2F                          (RTC_INITSTS_TAM2F)
#define RTC_FLAG_TAMP1F                          (RTC_INITSTS_TAM1F)
#define RTC_FLAG_TISOVF                          (RTC_INITSTS_TISOVF)
#define RTC_FLAG_TISF                            (RTC_INITSTS_TISF)
#define RTC_FLAG_WTF                             (RTC_INITSTS_WTF)
#define RTC_FLAG_ALBF                            (RTC_INITSTS_ALBF)
#define RTC_FLAG_ALAF                            (RTC_INITSTS_ALAF)
#define RTC_FLAG_INITM                           (RTC_INITSTS_INITM)
#define RTC_FLAG_INITF                           (RTC_INITSTS_INITF)
#define RTC_FLAG_RSYF                            (RTC_INITSTS_RSYF)
#define RTC_FLAG_INITSF                          (RTC_INITSTS_INITSF)
#define RTC_FLAG_SHOPF                           (RTC_INITSTS_SHOPF)
#define RTC_FLAG_WTWF                            (RTC_INITSTS_WTWF)
#define RTC_FLAG_ALBWF                           (RTC_INITSTS_ALBWF)
#define RTC_FLAG_ALAWF                           (RTC_INITSTS_ALAWF)

/** RTC_Interrupts_Definitions **/
#define RTC_INT_CAOV                             (RTC_CTRL_CAOVIEN)
#define RTC_INT_TAMP8                            ((uint32_t)0x02000000)
#define RTC_INT_TAMP7                            ((uint32_t)0x01000000)
#define RTC_INT_TAMP6                            ((uint32_t)0x00800000)
#define RTC_INT_TAMP5                            ((uint32_t)0x00400000)
#define RTC_INT_TAMP4                            ((uint32_t)0x00200000)
#define RTC_INT_TAMP3                            ((uint32_t)0x00080000)
#define RTC_INT_TAMP2                            ((uint32_t)0x00040000)
#define RTC_INT_TAMP1                            ((uint32_t)0x00020000)
#define RTC_INT_TS                               (RTC_CTRL_TSIEN)
#define RTC_INT_WUT                              (RTC_CTRL_WTIEN)
#define RTC_INT_ALRB                             (RTC_CTRL_ALBIEN)
#define RTC_INT_ALRA                             (RTC_CTRL_ALAIEN)


/** RTC_Tamper_Trigger_Definitions **/ 
#define RTC_TamperTrigger_RisingEdge            (RTC_REG_BIT_MASK)
#define RTC_TamperTrigger_FallingEdge           ((uint32_t)0x00000002)
#define RTC_TamperTrigger_HighLevel             (RTC_REG_BIT_MASK)
#define RTC_TamperTrigger_LowLevel              ((uint32_t)0x00000002)

/** RTC_Tamper_Filter_Definitions **/ 
#define RTC_TamperFilter_Disable                (RTC_REG_BIT_MASK)      /* Tamper filter is disabled */
#define RTC_TamperFilter_2Sample                (RTC_TMPCFG_TPFLT_0)    /* Tamper is activated after 2 consecutive samples at the active level */
#define RTC_TamperFilter_4Sample                (RTC_TMPCFG_TPFLT_1)    /* Tamper is activated after 4 consecutive samples at the active level */
#define RTC_TamperFilter_8Sample                (RTC_TMPCFG_TPFLT_0 | RTC_TMPCFG_TPFLT_1) /* Tamper is activated after 8 consecutive samples at the active leve */

/** RTC_Tamper_Sampling_Frequencies_Definitions **/ 
#define RTC_TamperSamplingFreq_RTCCLK_Div32768  (RTC_REG_BIT_MASK)  /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 32768 */
#define RTC_TamperSamplingFreq_RTCCLK_Div16384  (RTC_TMPCFG_TPFREQ_0)   /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 16384 */
#define RTC_TamperSamplingFreq_RTCCLK_Div8192   (RTC_TMPCFG_TPFREQ_1)   /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 8192  */
#define RTC_TamperSamplingFreq_RTCCLK_Div4096   (RTC_TMPCFG_TPFREQ_0 | RTC_TMPCFG_TPFREQ_1)     /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 4096  */
#define RTC_TamperSamplingFreq_RTCCLK_Div2048   (RTC_TMPCFG_TPFREQ_2)   /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 2048  */
#define RTC_TamperSamplingFreq_RTCCLK_Div1024   (RTC_TMPCFG_TPFREQ_0 | RTC_TMPCFG_TPFREQ_2)     /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 1024  */
#define RTC_TamperSamplingFreq_RTCCLK_Div512    (RTC_TMPCFG_TPFREQ_1 | RTC_TMPCFG_TPFREQ_2)     /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 512   */
#define RTC_TamperSamplingFreq_RTCCLK_Div256    (RTC_TMPCFG_TPFREQ_0 | RTC_TMPCFG_TPFREQ_1 | RTC_TMPCFG_TPFREQ_2)   /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 256   */
#define RTC_TAMPCR_TAMPFREQ                     (RTC_TMPCFG_TPFREQ_0 | RTC_TMPCFG_TPFREQ_1 | RTC_TMPCFG_TPFREQ_2)   /* Clear TAMPFREQ[2:0] bits in the RTC_TAMPCR register */

/** RTC_Tamper_Pin_Precharge_Duration_Definitions **/ 
#define RTC_TamperPrechargeDuration_1RTCCLK     (RTC_REG_BIT_MASK)      	/* Tamper pins are pre-charged before sampling during 1 RTCCLK cycle */
#define RTC_TamperPrechargeDuration_2RTCCLK     (RTC_TMPCFG_TPPRCH_0)       /* Tamper pins are pre-charged before sampling during 2 RTCCLK cycles */
#define RTC_TamperPrechargeDuration_4RTCCLK     (RTC_TMPCFG_TPPRCH_1)       /* Tamper pins are pre-charged before sampling during 4 RTCCLK cycles */
#define RTC_TamperPrechargeDuration_8RTCCLK     (RTC_TMPCFG_TPPRCH_0 | RTC_TMPCFG_TPPRCH_1)  /* Tamper pins are pre-charged before sampling during 8 RTCCLK cycles */

/** @defgroup RTC_Tamper_Pins_Definitions **/ 
/** @defgroup RTC Tamper Source Definitions **/ 
#define RTC_TAMPER_1            (0)    /* Tamper 1 */
#define RTC_TAMPER_2            (1)    /* Tamper 2 */
#define RTC_TAMPER_3            (2)    /* Tamper 3 */
#define RTC_TAMPER_4            (3)    /* Tamper 4 */
#define RTC_TAMPER_5            (4)    /* Tamper 5 */
#define RTC_TAMPER_6            (5)    /* Tamper 6 */
#define RTC_TAMPER_7            (6)    /* Tamper 7 */
#define RTC_TAMPER_8            (7)    /* Tamper 8 */

/** Function used to set the RTC configuration to the default reset state **/
ErrorStatus RTC_DeInit(void);

/** Initialization and Configuration functions **/
ErrorStatus RTC_Init(RTC_InitType* RTC_InitStruct);
void RTC_StructInit(RTC_InitType* RTC_InitStruct);
void RTC_EnableWriteProtection(FunctionalState Cmd);
ErrorStatus RTC_EnterInitMode(void);
void RTC_ExitInitMode(void);
ErrorStatus RTC_WaitForSynchro(void);
ErrorStatus RTC_EnableRefClock(FunctionalState Cmd);
void RTC_EnableBypassShadow(FunctionalState Cmd);

/** Time and Date configuration functions **/
void RTC_TimeStructInit(RTC_TimeType* RTC_TimeStruct);
ErrorStatus RTC_ConfigTime(uint32_t RTC_Format, RTC_TimeType* RTC_TimeStruct);
void RTC_GetTime(uint32_t RTC_Format, RTC_TimeType* RTC_TimeStruct);
uint32_t RTC_GetSubSecond(void);
void RTC_DateStructInit(RTC_DateType* RTC_DateStruct);
ErrorStatus RTC_SetDate(uint32_t RTC_Format, RTC_DateType* RTC_DateStruct);
void RTC_GetDate(uint32_t RTC_Format, RTC_DateType* RTC_DateStruct);

/** RTC output configuration **/
void RTC_EnableOutput2(FunctionalState Cmd);
void RTC_ConfigOutputType(uint32_t RTC_OutputType);
void RTC_ConfigOutputDuty(uint32_t duty_cycle);
void RTC_ConfigOutputPullUp(FunctionalState Cmd);

void RTC_ConfigPWREvtSig(uint32_t signal_type);

/** Alarms (Alarm A and Alarm B) configuration functions **/
void RTC_SetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmType* RTC_AlarmStruct);
void RTC_AlarmStructInit(RTC_AlarmType* RTC_AlarmStruct);
void RTC_GetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmType* RTC_AlarmStruct);
ErrorStatus RTC_EnableAlarm(uint32_t RTC_Alarm, FunctionalState Cmd);
void RTC_ConfigAlarmSubSecond(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint32_t RTC_AlarmSubSecondMask);
uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm);

/** WakeUp Timer configuration functions **/
void RTC_ConfigWakeUpClock(uint32_t RTC_WakeUpClock);
void RTC_SetWakeUpCounter(uint32_t RTC_WakeUpCounter);
uint32_t RTC_GetWakeUpCounter(void);
ErrorStatus RTC_EnableWakeUp(FunctionalState Cmd);

/** Daylight Saving configuration functions **/
void RTC_ConfigDayLightSaving(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation);
uint32_t RTC_GetStoreOperation(void);

/** Output pin Configuration function **/
void RTC_ConfigOutput(uint32_t RTC_Output, uint32_t RTC_OutputPolarity);
void RTC_EnableTampOutput(FunctionalState Cmd);

/** Coarse and Smooth Calibration configuration functions **/
void RTC_EnableCalibOutput(FunctionalState Cmd);
void RTC_ConfigCalibOutput(uint32_t RTC_CalibOutput);
ErrorStatus RTC_ConfigSmoothCalib(uint32_t RTC_SmoothCalibPeriod,
                                  uint32_t RTC_SmoothCalibPlusPulses,
                                  uint32_t RTC_SmouthCalibMinusPulsesValue);

/** TimeStamp configuration functions **/
void RTC_EnableTimeStamp(uint32_t RTC_TimeStampEdge, FunctionalState Cmd);
void RTC_GetTimeStamp(uint32_t RTC_Format, RTC_TimeType* RTC_StampTimeStruct, RTC_DateType* RTC_StampDateStruct);
uint32_t RTC_GetTimeStampSubSecond(void);

void RTC_EnableInterEventTimeStamp(FunctionalState Cmd);

/** RTC_Shift_control_synchonisation_functions **/
ErrorStatus RTC_ConfigSynchroShift(uint32_t RTC_ShiftAdd1S, uint32_t RTC_ShiftSubFS);

/** Interrupts and flags management functions **/
void RTC_ConfigInt(uint32_t RTC_INT, FunctionalState Cmd);
FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG);
void RTC_ClrFlag(uint32_t RTC_FLAG);
INTStatus RTC_GetITStatus(uint32_t RTC_INT);
void RTC_ClrIntPendingBit(uint32_t RTC_INT);

/** Tamper configuration functions **/
void RTC_TamperTriggerConfig(uint32_t RTC_Tamper, uint32_t RTC_TamperTrigger);
void RTC_TamperCmd(uint32_t RTC_Tamper, FunctionalState NewState);
void RTC_TamperFilterConfig(uint32_t RTC_TamperFilter);
void RTC_TamperSamplingFreqConfig(uint32_t RTC_TamperSamplingFreq);
void RTC_TamperPinsPrechargeDuration(uint32_t RTC_TamperPrechargeDuration);
void RTC_TimeStampOnTamperDetectionCmd(FunctionalState NewState);
void RTC_TamperPullUpCmd(FunctionalState NewState);
void RTC_TamperMskCmd(uint32_t TAMPxMSK, FunctionalState NewState);
void RTC_TamperIECmd(uint32_t TAMPxIE, FunctionalState NewState);
void RTC_EnableTampErase(uint32_t RTC_Tamper_Erase, FunctionalState NewState);

void RTC_BKUPRgWrite(uint8_t register_num, uint32_t Data);
uint32_t RTC_BKUPRgRead(uint8_t register_num);

#ifdef __cplusplus
}
#endif

#endif /* __N32H76X_78X_RTC_H__ */

