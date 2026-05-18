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
 * @file n32h76x_78x_lptim.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76X_78X_LPTIM_H__
#define __N32H76X_78X_LPTIM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"
#include "n32h76x_78x_rcc.h"

/*** LPTIM Structure Definition Start ***/


/** LPTIM initialize configuration structure definition **/
typedef struct
{
  uint32_t ClockSource;    /* Specifies the source of the clock used by the LPTIM instance.
                              This parameter can be a value of LPTIM Clock Source definition.
                              This feature can be modified afterwards using unitary function LPTIM_SetClockSource().*/

  uint32_t Prescaler;      /* Specifies the prescaler division ratio.
                              This parameter can be a value of LPTIM Prescaler Value definition.
                              This feature can be modified afterwards using using unitary function LPTIM_SetPrescaler().*/

  uint32_t Waveform;       /* Specifies the waveform shape.
                              This parameter can be a value of LPTIM Output Waveform Type definition.
                              This feature can be modified afterwards using unitary function LPTIM_ConfigOutput().*/

  uint32_t Polarity;       /* Specifies waveform polarity.
                              This parameter can be a value of LPTIM Output Polarity definition.
                              This feature can be modified afterwards using unitary function LPTIM_ConfigOutput().*/
} LPTIM_InitType;

/*** LPTIM Structure Definition End ***/


/*** LPTIM Macro Definition Start ***/

/** LPTIM status definition **/
#define LPTIM_COMP_MATCH_STATUS             ((uint32_t)LPTIM_INTSTS_CMPM)   /* Compare match */
#define LPTIM_AUTO_RELOAD_STATUS            ((uint32_t)LPTIM_INTSTS_ARRM)   /* Autoreload match */
#define LPTIM_EXT_TRIG_EDGE_EVENT_STATUS    ((uint32_t)LPTIM_INTSTS_EXTRIG) /* External trigger edge event */
#define LPTIM_COMP_UPDATE_STATUS            ((uint32_t)LPTIM_INTSTS_CMPUPD) /* Compare register update OK */
#define LPTIM_AUTO_RELOAD_UPDATE_STATUS     ((uint32_t)LPTIM_INTSTS_ARRUPD) /* Autoreload register update OK */
#define LPTIM_COUNTER_DIR_UP_STATUS         ((uint32_t)LPTIM_INTSTS_UP)     /* Counter direction change down to up */
#define LPTIM_COUNTER_DIR_DOWN_STATUS       ((uint32_t)LPTIM_INTSTS_DOWN)   /* Counter direction change up to down */

/** LPTIM flag definition **/
#define LPTIM_COMP_MATCH_FLAG               ((uint32_t)LPTIM_INTCLR_CMPMCF)   /* Compare match Clear Flag */
#define LPTIM_AUTO_RELOAD_FLAG              ((uint32_t)LPTIM_INTCLR_ARRMCF)   /* Autoreload match Clear Flag */
#define LPTIM_EXT_TRIG_EDGE_EVENT_FLAG      ((uint32_t)LPTIM_INTCLR_EXTRIGCF) /* External trigger edge event Clear Flag */
#define LPTIM_COMP_UPDATE_FLAG              ((uint32_t)LPTIM_INTCLR_CMPUPDCF) /* Compare register update OK Clear Flag */
#define LPTIM_AUTO_RELOAD_UPDATE_FLAG       ((uint32_t)LPTIM_INTCLR_ARRUPDCF) /* Autoreload register update OK Clear Flag */
#define LPTIM_COUNTER_DIR_UP_FLAG           ((uint32_t)LPTIM_INTCLR_UPCF)     /* Counter direction change down to up Clear Flag */
#define LPTIM_COUNTER_DIR_DOWN_FLAG         ((uint32_t)LPTIM_INTCLR_DOWNCF)   /* Counter direction change up to down Clear Flag */

/** LPTIM interrupt definition **/
#define LPTIM_COMP_MATCH_INT                ((uint32_t)LPTIM_INTEN_CMPMIE)   /* Compare match Interrupt */
#define LPTIM_AUTO_RELOAD_INT               ((uint32_t)LPTIM_INTEN_ARRMIE)   /* Autoreload match Interrupt */
#define LPTIM_EXT_TRIG_EDGE_EVENT_INT       ((uint32_t)LPTIM_INTEN_EXTRIGIE) /* External trigger edge event Interrupt */
#define LPTIM_COMP_UPDATE_INT               ((uint32_t)LPTIM_INTEN_CMPUPDIE) /* Compare register update OK Interrupt */
#define LPTIM_AUTO_RELOAD_UPDATE_INT        ((uint32_t)LPTIM_INTEN_ARRUPDIE) /* Autoreload register update OK Interrupt */
#define LPTIM_COUNTER_DIR_UP_INT            ((uint32_t)LPTIM_INTEN_UPIE)     /* Counter direction change down to up Interrupt */
#define LPTIM_COUNTER_DIR_DOWN_INT          ((uint32_t)LPTIM_INTEN_DOWNIE)   /* Counter direction change up to down Interrupt */

/** LPTIM Operating Mode definition **/
#define LPTIM_OPERATING_MODE_CONTINUOUS     ((uint32_t)LPTIM_CTRL_TSTCM)  /* LP Timer starts in continuous mode */
#define LPTIM_OPERATING_MODE_ONESHOT        ((uint32_t)LPTIM_CTRL_SNGMST) /* LP Tilmer starts in single mode */

/** LPTIM Update Mode definition **/
#define LPTIM_UPDATE_MODE_IMMEDIATE         ((uint32_t)0x00000000U)      /* Preload is disabled: registers are updated after each APB bus write access */
#define LPTIM_UPDATE_MODE_ENDOFPERIOD       ((uint32_t)LPTIM_CFG_RELOAD) /* preload is enabled: registers are updated at the end of the current LPTIM period */

/** LPTIM Counter Mode definition **/
#define LPTIM_COUNTER_MODE_INTERNAL         ((uint32_t)0x00000000U)      /* The counter is incremented following each internal clock pulse */
#define LPTIM_COUNTER_MODE_EXTERNAL         ((uint32_t)LPTIM_CFG_CNTMEN) /* The counter is incremented following each valid clock pulse on the LPTIM external Input1 */

/** LPTIM Output Waveform Type definition **/
#define LPTIM_OUTPUT_WAVEFORM_PWM           ((uint32_t)0x00000000U)    /* LPTIM generates either a PWM waveform or a One pulse waveform depending on chosen operating mode CONTINOUS or SINGLE */
#define LPTIM_OUTPUT_WAVEFORM_SETONCE       ((uint32_t)LPTIM_CFG_WAVE) /* LPTIM generates a Set Once waveform */

/** LPTIM Output Polarity definition **/
#define LPTIM_OUTPUT_POLARITY_REGULAR       ((uint32_t)0x00000000U)       /* The LPTIM output reflects the compare results between LPTIMx_ARR and LPTIMx_CMP registers */
#define LPTIM_OUTPUT_POLARITY_INVERSE       ((uint32_t)LPTIM_CFG_WAVEPOL) /* The LPTIM output reflects the inverse of the compare results between LPTIMx_ARR and LPTIMx_CMP registers */

/** LPTIM Prescaler Value definition **/
#define LPTIM_PRESCALER_DIV1                ((uint32_t)0x00000000U)        /* Prescaler division factor is set to 1 */
#define LPTIM_PRESCALER_DIV2                ((uint32_t)LPTIM_CFG_CLKPRE_0) /* Prescaler division factor is set to 2 */
#define LPTIM_PRESCALER_DIV4                ((uint32_t)LPTIM_CFG_CLKPRE_1) /* Prescaler division factor is set to 4 */
#define LPTIM_PRESCALER_DIV8                ((uint32_t)LPTIM_CFG_CLKPRE_1 \
                                                     | LPTIM_CFG_CLKPRE_0) /* Prescaler division factor is set to 8 */
#define LPTIM_PRESCALER_DIV16               ((uint32_t)LPTIM_CFG_CLKPRE_2) /* Prescaler division factor is set to 16 */
#define LPTIM_PRESCALER_DIV32               ((uint32_t)LPTIM_CFG_CLKPRE_2 \
                                                     | LPTIM_CFG_CLKPRE_0) /* Prescaler division factor is set to 32 */
#define LPTIM_PRESCALER_DIV64               ((uint32_t)LPTIM_CFG_CLKPRE_2 \
                                                     | LPTIM_CFG_CLKPRE_1) /* Prescaler division factor is set to 64 */
#define LPTIM_PRESCALER_DIV128              ((uint32_t)LPTIM_CFG_CLKPRE)   /* Prescaler division factor is set to 128 */

/** LPTIM Trigger Source definition **/
#define LPTIM_TRIG_SOURCE_GPIO              ((uint32_t)0x00000000U)        /* External input trigger is connected to TIMx_ETR input */
#define LPTIM_TRIG_SOURCE_RTCALARMA         ((uint32_t)LPTIM_CFG_TRGSEL_0) /* External input trigger is connected to RTC Alarm A */
#define LPTIM_TRIG_SOURCE_RTCALARMB         ((uint32_t)LPTIM_CFG_TRGSEL_1) /* External input trigger is connected to RTC Alarm B */
#define LPTIM_TRIG_SOURCE_RTCTAMP1          ((uint32_t)LPTIM_CFG_TRGSEL_1 \
                                                     | LPTIM_CFG_TRGSEL_0) /* External input trigger is connected to RTC Tamper 1 */
#define LPTIM_TRIG_SOURCE_RTCTAMP2          ((uint32_t)LPTIM_CFG_TRGSEL_2) /* External input trigger is connected to RTC Tamper 2 */
#define LPTIM_TRIG_SOURCE_RTCTAMP3          ((uint32_t)LPTIM_CFG_TRGSEL_2 \
                                                     | LPTIM_CFG_TRGSEL_0) /* External input trigger is connected to RTC Tamper 3 */
#define LPTIM_TRIG_SOURCE_COMP1             ((uint32_t)LPTIM_CFG_TRGSEL_2 \
                                                     | LPTIM_CFG_TRGSEL_1) /* External input trigger is connected to COMP1 output */
#define LPTIM_TRIG_SOURCE_COMP2             ((uint32_t)LPTIM_CFG_TRGSEL_2 \
                                                     | LPTIM_CFG_TRGSEL_1 \
                                                     | LPTIM_CFG_TRGSEL_0) /* External input trigger is connected to COMP2 output */
#define LPTIM_TRIG_SOURCE_COMP3             ((uint32_t)LPTIM_CFG_TRGSEL_3) /* External input trigger is connected to COMP3 output */
#define LPTIM_TRIG_SOURCE_COMP4             ((uint32_t)LPTIM_CFG_TRGSEL_3 \
                                                     | LPTIM_CFG_TRGSEL_0) /* External input trigger is connected to COMP4 output */

/** LPTIM Trigger Filter definition **/
#define LPTIM_TRIG_FILTER_NONE              ((uint32_t)0x00000000U)         /* Any trigger active level change is considered as a valid trigger */
#define LPTIM_TRIG_FILTER_2                 ((uint32_t)LPTIM_CFG_TRIGFLT_0) /* Trigger active level change must be stable for at least 2 clock periods before it is considered as valid trigger */
#define LPTIM_TRIG_FILTER_4                 ((uint32_t)LPTIM_CFG_TRIGFLT_1) /* Trigger active level change must be stable for at least 4 clock periods before it is considered as valid trigger */
#define LPTIM_TRIG_FILTER_8                 ((uint32_t)LPTIM_CFG_TRIGFLT)   /* Trigger active level change must be stable for at least 8 clock periods before it is considered as valid trigger */

/** LPTIM Trigger Polarity definition **/
#define LPTIM_TRIG_POLARITY_RISING          ((uint32_t)LPTIM_CFG_TRGEN_0) /* LPTIM counter starts when a rising edge is detected */
#define LPTIM_TRIG_POLARITY_FALLING         ((uint32_t)LPTIM_CFG_TRGEN_1) /* LPTIM counter starts when a falling edge is detected */
#define LPTIM_TRIG_POLARITY_RISING_FALLING  ((uint32_t)LPTIM_CFG_TRGEN)   /* LPTIM counter starts when a rising or a falling edge is detected */

/** LPTIM Clock Source definition **/
#define LPTIM_CLK_SOURCE_INTERNAL           ((uint32_t)0x00000000U)      /* LPTIM is clocked by internal clock source ((uint32_t)APB clock or any of the embedded oscillators) */
#define LPTIM_CLK_SOURCE_EXTERNAL           ((uint32_t)LPTIM_CFG_CLKSEL) /* LPTIM is clocked by an external clock source through the LPTIM external Input1 */

/** LPTIM Clock Filter definition **/
#define LPTIM_CLK_FILTER_NONE               ((uint32_t)0x00000000U)        /* Any external clock signal level change is considered as a valid transition */
#define LPTIM_CLK_FILTER_2                  ((uint32_t)LPTIM_CFG_CLKFLT_0) /* External clock signal level change must be stable for at least 2 clock periods before it is considered as valid transition */
#define LPTIM_CLK_FILTER_4                  ((uint32_t)LPTIM_CFG_CLKFLT_1) /* External clock signal level change must be stable for at least 4 clock periods before it is considered as valid transition */
#define LPTIM_CLK_FILTER_8                  ((uint32_t)LPTIM_CFG_CLKFLT)   /* External clock signal level change must be stable for at least 8 clock periods before it is considered as valid transition */

/** LPTIM Clock Polarity definition **/
#define LPTIM_CLK_POLARITY_RISING               ((uint32_t)0x00000000U)        /* The rising edge is the active edge used for counting */
#define LPTIM_CLK_POLARITY_FALLING              ((uint32_t)LPTIM_CFG_CLKPOL_0) /* The falling edge is the active edge used for counting */
#define LPTIM_CLK_POLARITY_RISING_FALLING       ((uint32_t)LPTIM_CFG_CLKPOL_1) /* Both edges are active edges */
#define LPTIM_CLK_POLARITY_RISING_FALLING_NO    ((uint32_t)LPTIM_CFG_CLKPOL_0 \
                                                      | LPTIM_CFG_CLKPOL_1) /* Both edges are not active edges */

/** LPTIM Encoder Mode definition **/
#define LPTIM_ENCODER_MODE_RISING           ((uint32_t)0x00000000U)        /* The rising edge is the active edge used for counting */
#define LPTIM_ENCODER_MODE_FALLING          ((uint32_t)LPTIM_CFG_CLKPOL_0) /* The falling edge is the active edge used for counting */
#define LPTIM_ENCODER_MODE_RISING_FALLING   ((uint32_t)LPTIM_CFG_CLKPOL_1) /* Both edges are active edges */

/** LPTIM Input1 connected option definition **/
#define LPTIM_INPUT1_CONNECT_GPIO           ((uint32_t)0x00000000U)      /* Input1 connected to GPIO */
#define LPTIM_INPUT1_CONNECT_COMP1          ((uint32_t)LPTIM_OPT_OPT1_2) /* Input1 connected to COMP1_OUT */
#define LPTIM_INPUT1_CONNECT_COMP2          ((uint32_t)LPTIM_OPT_OPT1_2 \
                                                     | LPTIM_OPT_OPT1_0) /* Input1 connected to COMP2_OUT */
#define LPTIM_INPUT1_CONNECT_COMP3          ((uint32_t)LPTIM_OPT_OPT1_2 \
                                                     | LPTIM_OPT_OPT1_1) /* Input1 connected to COMP3_OUT */
#define LPTIM_INPUT1_CONNECT_COMP4          ((uint32_t)LPTIM_OPT_OPT1_2 \
                                                     | LPTIM_OPT_OPT1_1 \
                                                     | LPTIM_OPT_OPT1_0) /* Input1 connected to COMP4_OUT */


/** LPTIM Input2 connected option definition **/
#define LPTIM_INPUT2_CONNECT_GPIO           ((uint32_t)0x00000000U)      /* Input2 connected to GPIO */
#define LPTIM_INPUT2_CONNECT_COMP1          ((uint32_t)LPTIM_OPT_OPT2_2) /* Input2 connected to COMP1_OUT */
#define LPTIM_INPUT2_CONNECT_COMP2          ((uint32_t)LPTIM_OPT_OPT2_2 \
                                                     | LPTIM_OPT_OPT2_0) /* Input2 connected to COMP2_OUT */
#define LPTIM_INPUT2_CONNECT_COMP3          ((uint32_t)LPTIM_OPT_OPT2_2 \
                                                     | LPTIM_OPT_OPT2_1) /* Input2 connected to COMP3_OUT */
#define LPTIM_INPUT2_CONNECT_COMP4          ((uint32_t)LPTIM_OPT_OPT2_2 \
                                                     | LPTIM_OPT_OPT2_1 \
                                                     | LPTIM_OPT_OPT2_0) /* Input2 connected to COMP4_OUT */

/*** LPTIM Driving Functions Declaration ***/
void LPTIM_DeInit(LPTIM_Module* LPTIMx);
void LPTIM_StructInit(LPTIM_InitType* LPTIM_InitStruct);
ErrorStatus LPTIM_Init(LPTIM_Module* LPTIMx, LPTIM_InitType* LPTIM_InitStruct);
void LPTIM_Cmd(LPTIM_Module* LPTIMx, FunctionalStatus Cmd);
uint32_t LPTIM_IsEnabled(LPTIM_Module* LPTIMx);
void LPTIM_StartCounter(LPTIM_Module* LPTIMx, uint32_t OperatingMode);
void LPTIM_SetUpdateMode(LPTIM_Module* LPTIMx, uint32_t UpdateMode);
uint32_t LPTIM_GetUpdateMode(LPTIM_Module* LPTIMx);
void LPTIM_SetAutoReloadValue(LPTIM_Module* LPTIMx, uint32_t AutoReload);
uint32_t LPTIM_GetAutoReloadValue(LPTIM_Module* LPTIMx);
void LPTIM_SetCompareValue(LPTIM_Module* LPTIMx, uint32_t CompareValue);
uint32_t LPTIM_GetCompareValue(LPTIM_Module* LPTIMx);
uint32_t LPTIM_GetCounterValue(LPTIM_Module* LPTIMx);
void LPTIM_SetCounterMode(LPTIM_Module* LPTIMx, uint32_t CounterMode);
uint32_t LPTIM_GetCounterMode(LPTIM_Module* LPTIMx);
void LPTIM_ConfigOutput(LPTIM_Module* LPTIMx, uint32_t Waveform, uint32_t Polarity);
void LPTIM_SetWaveform(LPTIM_Module* LPTIMx, uint32_t Waveform);
uint32_t LPTIM_GetWaveform(LPTIM_Module* LPTIMx);
void LPTIM_SetPolarity(LPTIM_Module* LPTIMx, uint32_t Polarity);
uint32_t LPTIM_GetPolarity(LPTIM_Module* LPTIMx);
void LPTIM_SetPrescaler(LPTIM_Module* LPTIMx, uint32_t Prescaler);
uint32_t LPTIM_GetPrescaler(LPTIM_Module* LPTIMx);
void LPTIM_TimeoutCmd(LPTIM_Module* LPTIMx, FunctionalStatus Cmd);
uint32_t LPTIM_IsEnabledTimeout(LPTIM_Module* LPTIMx);
void LPTIM_SoftwareTrigger(LPTIM_Module* LPTIMx);
void LPTIM_ConfigTrigger(LPTIM_Module* LPTIMx, uint32_t Source, uint32_t Filter, uint32_t Polarity);
uint32_t LPTIM_GetTriggerSource(LPTIM_Module* LPTIMx);
uint32_t LPTIM_GetTriggerFilter(LPTIM_Module* LPTIMx);
uint32_t LPTIM_GetTriggerPolarity(LPTIM_Module* LPTIMx);
void LPTIM_SetClockSource(LPTIM_Module* LPTIMx, uint32_t ClockSource);
uint32_t LPTIM_GetClockSource(LPTIM_Module* LPTIMx);
void LPTIM_ConfigClock(LPTIM_Module* LPTIMx, uint32_t ClockFilter, uint32_t ClockPolarity);
uint32_t LPTIM_GetClockPolarity(LPTIM_Module* LPTIMx);
uint32_t LPTIM_GetClockFilter(LPTIM_Module* LPTIMx);
void LPTIM_SetEncoderModeClockPolarity(LPTIM_Module* LPTIMx, uint32_t ClockPolarity);
uint32_t LPTIM_GetEncoderModeClockPolarity(LPTIM_Module* LPTIMx);
void LPTIM_EncoderModeCmd(LPTIM_Module* LPTIMx, FunctionalStatus Cmd);
void LPTIM_NoEncoderModeCmd(LPTIM_Module* LPTIMx, FunctionalStatus Cmd);
uint32_t LPTIM_IsEnabledEncoderMode(LPTIM_Module* LPTIMx);
uint32_t LPTIM_IsEnabledNoEncoderMode(LPTIM_Module* LPTIMx);
void LPTIM_ClearIntFlag(LPTIM_Module* LPTIMx, uint32_t IntFlag);
uint32_t LPTIM_IsActiveIntStatus(LPTIM_Module* LPTIMx, uint32_t IntSts);
void LPTIM_ConfigInt(LPTIM_Module* LPTIMx, uint32_t Interrupt, FunctionalStatus Cmd);
uint32_t LPTIM_IsEnabledInt(LPTIM_Module* LPTIMx, uint32_t Interrupt);
void LPTIM_ConfigInput1(LPTIM_Module* LPTIMx, uint32_t ConnectSelect);
void LPTIM_ConfigInput2(LPTIM_Module* LPTIMx, uint32_t ConnectSelect);


/*** LPTIM Driving Functions Declaration End ***/


#ifdef __cplusplus
}
#endif

#endif /*__N32H76X_78X_LPTIM_H__ */

