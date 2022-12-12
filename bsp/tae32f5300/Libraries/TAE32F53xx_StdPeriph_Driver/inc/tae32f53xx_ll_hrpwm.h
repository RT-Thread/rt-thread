/**
  ******************************************************************************
  * @file    tae32f53xx_ll_hrpwm.h
  * @author  MCD Application Team
  * @brief   Header file of HRPWM LL module
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F53XX_LL_HRPWM_H_
#define _TAE32F53XX_LL_HRPWM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup HRPWM_LL
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup HRPWM_LL_Exported_Constants HRPWM LL Exported Constants
  * @brief    HRPWM LL Exported Constants
  * @{
  */

/** @defgroup HRPWM_Max_Timer HRPWM Max Timer
  * @{
  */
#define MAX_HRPWM_TIMER                 6U
/**
  * @}
  */

/** @defgroup HRPWM_Timer_Index HRPWM Index
  * @brief Constants defining the hrpwm indexes
  * @{
  */
#define HRPWM_INDEX_SLAVE_0             0x0U    /*!< Index used to access slave pwm 0 registers     */
#define HRPWM_INDEX_SLAVE_1             0x1U    /*!< Index used to access slave pwm 1 registers     */
#define HRPWM_INDEX_SLAVE_2             0x2U    /*!< Index used to access slave pwm 2 registers     */
#define HRPWM_INDEX_SLAVE_3             0x3U    /*!< Index used to access slave pwm 3 registers     */
#define HRPWM_INDEX_SLAVE_4             0x4U    /*!< Index used to access slave pwm 4 registers     */
#define HRPWM_INDEX_SLAVE_5             0x5U    /*!< Index used to access slave pwm 5 registers     */
#define HRPWM_INDEX_MASTER              0x6U    /*!< Index used to access master registers          */
#define HRPWM_INDEX_COMMON              0xFFU   /*!< Index used to access HRPWM common registers    */
/**
  * @}
  */

/** @defgroup HRPWM_Compare_Unit HRPWM Compare Unit
  * @brief Constants defining compare unit identifiers
  * @{
  */
#define HRPWM_COMPAREUNIT_A             0x00000001U     /*!< Compare unit A identifier  */
#define HRPWM_COMPAREUNIT_B             0x00000002U     /*!< Compare unit B identifier  */
#define HRPWM_COMPAREUNIT_C             0x00000004U     /*!< Compare unit C identifier  */
#define HRPWM_COMPAREUNIT_D             0x00000008U     /*!< Compare unit D identifier  */
/**
 * @}
 */

/** @defgroup HRPWM_Timer_Output_Start HRPWM Timer Output
  * @brief Constants defining timer output identifiers -- output enable,not enable cannot output wave
  * @{
  */
#define HRPWM_OUTPUT_OEN0A              0x00000001U     /*!< Timer 0 - Output A identifier  */
#define HRPWM_OUTPUT_OEN0B              0x00000002U     /*!< Timer 0 - Output B identifier  */
#define HRPWM_OUTPUT_OEN1A              0x00000004U     /*!< Timer 1 - Output A identifier  */
#define HRPWM_OUTPUT_OEN1B              0x00000008U     /*!< Timer 1 - Output B identifier  */
#define HRPWM_OUTPUT_OEN2A              0x00000010U     /*!< Timer 2 - Output A identifier  */
#define HRPWM_OUTPUT_OEN2B              0x00000020U     /*!< Timer 2 - Output B identifier  */
#define HRPWM_OUTPUT_OEN3A              0x00000040U     /*!< Timer 3 - Output A identifier  */
#define HRPWM_OUTPUT_OEN3B              0x00000080U     /*!< Timer 3 - Output B identifier  */
#define HRPWM_OUTPUT_OEN4A              0x00000100U     /*!< Timer 4 - Output A identifier  */
#define HRPWM_OUTPUT_OEN4B              0x00000200U     /*!< Timer 4 - Output B identifier  */
#define HRPWM_OUTPUT_OEN5A              0x00000400U     /*!< Timer 5 - Output A identifier  */
#define HRPWM_OUTPUT_OEN5B              0x00000800U     /*!< Timer 5 - Output B identifier  */
/**
  * @}
  */

/** @defgroup HRPWM_Timer_Output_Stop HRPWM Timer Output Disable
  * @brief Constants defining timer disable output identifiers
  * @{
  */
#define HRPWM_OUTPUT_ODIS0A             0x00000001U     /*!< Timer 0 - Disable Output A identifier  */
#define HRPWM_OUTPUT_ODIS0B             0x00000002U     /*!< Timer 0 - Disable Output B identifier  */
#define HRPWM_OUTPUT_ODIS1A             0x00000004U     /*!< Timer 1 - Disable Output A identifier  */
#define HRPWM_OUTPUT_ODIS1B             0x00000008U     /*!< Timer 1 - Disable Output B identifier  */
#define HRPWM_OUTPUT_ODIS2A             0x00000010U     /*!< Timer 2 - Disable Output A identifier  */
#define HRPWM_OUTPUT_ODIS2B             0x00000020U     /*!< Timer 2 - Disable Output B identifier  */
#define HRPWM_OUTPUT_ODIS3A             0x00000040U     /*!< Timer 3 - Disable Output A identifier  */
#define HRPWM_OUTPUT_ODIS3B             0x00000080U     /*!< Timer 3 - Disable Output B identifier  */
#define HRPWM_OUTPUT_ODIS4A             0x00000100U     /*!< Timer 4 - Disable Output A identifier  */
#define HRPWM_OUTPUT_ODIS4B             0x00000200U     /*!< Timer 4 - Disable Output B identifier  */
#define HRPWM_OUTPUT_ODIS5A             0x00000400U     /*!< Timer 5 - Disable Output A identifier  */
#define HRPWM_OUTPUT_ODIS5B             0x00000800U     /*!< Timer 5 - Disable Output B identifier  */
/**
  * @}
  */

/** @defgroup HRPWM_Synchronization_Options HRPWM Synchronization Options
  * @brief Constants defining the options for synchronizing multiple HRPWM
  *        instances, as a master unit (generating a synchronization signal)
  *        or as a slave (waiting for a trigger to be synchronized)
  * @{
  */
#define HRPWM_SYNCOPTION_NONE       0x0 /*!< HRPWM instance doesn't handle external sync signals (SYNCIN, SYNCOUT)          */
#define HRPWM_SYNCOPTION_MASTER     0x1U/*!< HRPWM instance acts as a MASTER, i.e. generates external sync output (SYNCOUT) */
#define HRPWM_SYNCOPTION_SLAVE      0x2U/*!< HRPWM instance acts as a SLAVE, i.e. it is sync by external sources (SYNCIN)   */
/**
  * @}
  */

/** @defgroup HRPWM_Timer_Update_Trigger HRPWM Timer Update Trigger
  * @brief Constants defining whether the registers update is done synchronously with any other timer or master update
  * @{
  */
#define HRPWM_UPDATETRIGGER_NONE        0x00000000U         /*!< Register update is disabled */
#define HRPWM_UPDATETRIGGER_MASTER      (HRPWM_CR0_MUPD)    /*!< Register update is triggered by the master timer update    */
#define HRPWM_UPDATETRIGGER_TIMER_0     (HRPWM_CR0_UPD0)    /*!< Register update is triggered by the timer 0 update         */
#define HRPWM_UPDATETRIGGER_TIMER_1     (HRPWM_CR0_UPD1)    /*!< Register update is triggered by the timer 1 update         */
#define HRPWM_UPDATETRIGGER_TIMER_2     (HRPWM_CR0_UPD2)    /*!< Register update is triggered by the timer 2 update         */
#define HRPWM_UPDATETRIGGER_TIMER_3     (HRPWM_CR0_UPD3)    /*!< Register update is triggered by the timer 3 update         */
#define HRPWM_UPDATETRIGGER_TIMER_4     (HRPWM_CR0_UPD4)    /*!< Register update is triggered by the timer 4 update         */
#define HRPWM_UPDATETRIGGER_TIMER_5     (HRPWM_CR0_UPD5)    /*!< Register update is triggered by the timer 5 update         */
#define HRPWM_UPDATETRIGGER_REP         (HRPWM_CR0_UPDREP)  /*!< Register update is triggered by the Repetition update      */
#define HRPWM_UPDATETRIGGER_RST         (HRPWM_CR0_UPDRST)  /*!< Register update is triggered by the reset update           */
/**
  * @}
  */

/** @defgroup HRPWM_Timer_Set_Trigger HRPWM Output Set A\B Source
  * @brief Constants defining the events that can be selected to configure the set crossbar of a timer output
  * @{
  */
#define HRPWM_OUTPUT_SET_NONE       (0x00000000U) /*!< HRPWM output set none                                                */
#define HRPWM_OUTPUT_SET_SST        (1UL << 18)   /*!< Timer reset event coming solely from software forces the output
                                                       to its active state                                                  */
#define HRPWM_OUTPUT_SET_RESYNC     (1UL << 17)   /*!< SYNC input forces the output to its active state                     */
#define HRPWM_OUTPUT_SET_EXTEVNT5   (1UL << 16)   /*!< External event 5 forces the output to its active state               */
#define HRPWM_OUTPUT_SET_EXTEVNT4   (1UL << 15)   /*!< External event 4 forces the output to its active state               */
#define HRPWM_OUTPUT_SET_EXTEVNT3   (1UL << 14)   /*!< External event 3 forces the output to its active state               */
#define HRPWM_OUTPUT_SET_EXTEVNT2   (1UL << 13)   /*!< External event 2 forces the output to its active state               */
#define HRPWM_OUTPUT_SET_EXTEVNT1   (1UL << 12)   /*!< External event 1 forces the output to its active state               */
#define HRPWM_OUTPUT_SET_EXTEVNT0   (1UL << 11)   /*!< External event 0 forces the output to its active state               */
#define HRPWM_OUTPUT_SET_MSTPRD     (1UL << 10)   /*!< The master timer period event forces the output to its active state  */
#define HRPWM_OUTPUT_SET_MSTCMPD    (1UL << 9)    /*!< Master Timer compare D event forces the output to its active state   */
#define HRPWM_OUTPUT_SET_MSTCMPC    (1UL << 8)    /*!< Master Timer compare C event forces the output to its active state   */
#define HRPWM_OUTPUT_SET_MSTCMPB    (1UL << 7)    /*!< Master Timer compare B event forces the output to its active state   */
#define HRPWM_OUTPUT_SET_MSTCMPA    (1UL << 6)    /*!< Master Timer compare A event forces the output to its active state   */
#define HRPWM_OUTPUT_SET_PRD        (1UL << 5)    /*!< Timer period event forces the output to its active state             */
#define HRPWM_OUTPUT_SET_CMPD       (1UL << 4)    /*!< Timer compare D event forces the output to its active state          */
#define HRPWM_OUTPUT_SET_CMPC       (1UL << 3)    /*!< Timer compare C event forces the output to its active state          */
#define HRPWM_OUTPUT_SET_CMPB       (1UL << 2)    /*!< Timer compare B event forces the output to its active state          */
#define HRPWM_OUTPUT_SET_CMPA       (1UL << 1)    /*!< Timer compare A event forces the output to its active state          */
#define HRPWM_OUTPUT_SET_UPDATE     (1UL << 0)    /*!< Timer register update event forces the output to its active state    */
/**
  * @}
  */

/** @defgroup HRPWM_Timer_Clear_Trigger HRPWM Output Clear A\B Source
  * @brief Constants defining the events that can be selected to configure the clear crossbar of a timer output
  * @{
  */
#define HRPWM_OUTPUT_CLEAR_NONE     (0x00000000U)   /*!< HRPWM output clear None                                                */
#define HRPWM_OUTPUT_CLEAR_SST      (1UL << 18)     /*!< Timer reset event coming solely from software forces the output
                                                         to its inactive state                                                  */
#define HRPWM_OUTPUT_CLEAR_RESYNC   (1UL << 17)     /*!< SYNC input forces the output to its inactive state                     */
#define HRPWM_OUTPUT_CLEAR_EXTEVNT5 (1UL << 16)     /*!< External event 5 forces the output to its inactive state               */
#define HRPWM_OUTPUT_CLEAR_EXTEVNT4 (1UL << 15)     /*!< External event 4 forces the output to its inactive state               */
#define HRPWM_OUTPUT_CLEAR_EXTEVNT3 (1UL << 14)     /*!< External event 3 forces the output to its inactive state               */
#define HRPWM_OUTPUT_CLEAR_EXTEVNT2 (1UL << 13)     /*!< External event 2 forces the output to its inactive state               */
#define HRPWM_OUTPUT_CLEAR_EXTEVNT1 (1UL << 12)     /*!< External event 1 forces the output to its inactive state               */
#define HRPWM_OUTPUT_CLEAR_EXTEVNT0 (1UL << 11)     /*!< External event 0 forces the output to its inactive state               */
#define HRPWM_OUTPUT_CLEAR_MSTPRD   (1UL << 10)     /*!< The master timer period event forces the output to its inactive state  */
#define HRPWM_OUTPUT_CLEAR_MSTCMPD  (1UL << 9)      /*!< Master Timer compare D event forces the output to its inactive state   */
#define HRPWM_OUTPUT_CLEAR_MSTCMPC  (1UL << 8)      /*!< Master Timer compare C event forces the output to its inactive state   */
#define HRPWM_OUTPUT_CLEAR_MSTCMPB  (1UL << 7)      /*!< Master Timer compare B event forces the output to its inactive state   */
#define HRPWM_OUTPUT_CLEAR_MSTCMPA  (1UL << 6)      /*!< Master Timer compare A event forces the output to its inactive state   */
#define HRPWM_OUTPUT_CLEAR_PRD      (1UL << 5)      /*!< Timer period event forces the output to its inactive state             */
#define HRPWM_OUTPUT_CLEAR_CMPD     (1UL << 4)      /*!< Timer compare D event forces the output to its inactive state          */
#define HRPWM_OUTPUT_CLEAR_CMPC     (1UL << 3)      /*!< Timer compare C event forces the output to its inactive state          */
#define HRPWM_OUTPUT_CLEAR_CMPB     (1UL << 2)      /*!< Timer compare B event forces the output to its inactive state          */
#define HRPWM_OUTPUT_CLEAR_CMPA     (1UL << 1)      /*!< Timer compare A event forces the output to its inactive state          */
#define HRPWM_OUTPUT_CLEAR_UPDATE   (1UL << 0)      /*!< Timer register update event forces the output to its inactive state    */
/**
  * @}
  */

/** @defgroup HRPWM_Timer_Reset_Trigger HRPWM Timer Reset Trigger
  * @brief Constants defining the events that can be selected to trigger the reset of the timer counter
  * @{
  */
#define HRPWM_RESET_TRIGGER_NONE        0x00000000U             /*!< No counter reset trigger */
#define HRPWM_RESET_TRIGGER_EXTEVT5     (HRPWM_RSTR_EXTEVT5)    /*!< The timer counter is reset upon external event 5  */
#define HRPWM_RESET_TRIGGER_EXTEVT4     (HRPWM_RSTR_EXTEVT4)    /*!< The timer counter is reset upon external event 4  */
#define HRPWM_RESET_TRIGGER_EXTEVT3     (HRPWM_RSTR_EXTEVT3)    /*!< The timer counter is reset upon external event 3 */
#define HRPWM_RESET_TRIGGER_UPD_CMPA5   (HRPWM_RSTR_UPD_CMPA5)  /*!< The timer counter is reset upon other timer 5 update and Compare A event */
#define HRPWM_RESET_TRIGGER_CMPD4       (HRPWM_RSTR_CMPD4    )  /*!< The timer counter is reset upon other timer 4 Compare D event */
#define HRPWM_RESET_TRIGGER_CMPB4       (HRPWM_RSTR_CMPB4    )  /*!< The timer counter is reset upon other timer 4 Compare B event */
#define HRPWM_RESET_TRIGGER_UPD_CMPA4   (HRPWM_RSTR_UPD_CMPA4)  /*!< The timer counter is reset upon other timer 4 update and Compare A event */
#define HRPWM_RESET_TRIGGER_CMPD3       (HRPWM_RSTR_CMPD3    )  /*!< The timer counter is reset upon other timer 3 Compare D event */
#define HRPWM_RESET_TRIGGER_CMPB3       (HRPWM_RSTR_CMPB3    )  /*!< The timer counter is reset upon other timer 3 Compare B event */
#define HRPWM_RESET_TRIGGER_UPD_CMPA3   (HRPWM_RSTR_UPD_CMPA3)  /*!< The timer counter is reset upon other timer 3 update and Compare A event */
#define HRPWM_RESET_TRIGGER_CMPD2       (HRPWM_RSTR_CMPD2    )  /*!< The timer counter is reset upon other timer 2 Compare D event */
#define HRPWM_RESET_TRIGGER_CMPB2       (HRPWM_RSTR_CMPB2    )  /*!< The timer counter is reset upon other timer 2 Compare B event */
#define HRPWM_RESET_TRIGGER_UPD_CMPA2   (HRPWM_RSTR_UPD_CMPA2)  /*!< The timer counter is reset upon other timer 2 update and Compare A event */
#define HRPWM_RESET_TRIGGER_CMPD1       (HRPWM_RSTR_CMPD1    )  /*!< The timer counter is reset upon other timer 1 Compare D event */
#define HRPWM_RESET_TRIGGER_CMPB1       (HRPWM_RSTR_CMPB1    )  /*!< The timer counter is reset upon other timer 1 Compare B event */
#define HRPWM_RESET_TRIGGER_UPD_CMPA1   (HRPWM_RSTR_UPD_CMPA1)  /*!< The timer counter is reset upon other timer 1 update and Compare A event */
#define HRPWM_RESET_TRIGGER_CMPD0       (HRPWM_RSTR_CMPD0    )  /*!< The timer counter is reset upon other timer 0 Compare D event */
#define HRPWM_RESET_TRIGGER_CMPB0       (HRPWM_RSTR_CMPB0    )  /*!< The timer counter is reset upon other timer 0 Compare B event */
#define HRPWM_RESET_TRIGGER_UPD_CMPA0   (HRPWM_RSTR_UPD_CMPA0)  /*!< The timer counter is reset upon other timer 0 update and Compare A event */
#define HRPWM_RESET_TRIGGER_CMPD5       (HRPWM_RSTR_CMPD5    )  /*!< The timer counter is reset upon other timer 5 Compare D event */
#define HRPWM_RESET_TRIGGER_CMPB5       (HRPWM_RSTR_CMPB5    )  /*!< The timer counter is reset upon other timer 5 Compare B event */
#define HRPWM_RESET_TRIGGER_EXTEVT2     (HRPWM_RSTR_EXTEVT2  )  /*!< The timer counter is reset upon external event 2 */
#define HRPWM_RESET_TRIGGER_EXTEVT1     (HRPWM_RSTR_EXTEVT1  )  /*!< The timer counter is reset upon external event 1 */
#define HRPWM_RESET_TRIGGER_EXTEVT0     (HRPWM_RSTR_EXTEVT0  )  /*!< The timer counter is reset upon external event 0 */
#define HRPWM_RESET_TRIGGER_MSTPER      (HRPWM_RSTR_MSTPER   )  /*!< The timer counter is reset upon master timer period event  */
#define HRPWM_RESET_TRIGGER_MSTCMPD     (HRPWM_RSTR_MSTCMPD  )  /*!< The timer counter is reset upon master timer Compare 1 event */
#define HRPWM_RESET_TRIGGER_MSTCMPC     (HRPWM_RSTR_MSTCMPC  )  /*!< The timer counter is reset upon master timer Compare 2 event */
#define HRPWM_RESET_TRIGGER_MSTCMPB     (HRPWM_RSTR_MSTCMPB  )  /*!< The timer counter is reset upon master timer Compare 3 event */
#define HRPWM_RESET_TRIGGER_MSTCMPA     (HRPWM_RSTR_MSTCMPA  )  /*!< The timer counter is reset upon master timer Compare 4 event */
/**
  * @}
  */

/** @defgroup HRPWM_Timer_Fault_Enabling HRPWM Timer Fault Enabling
  * @brief Constants defining whether a fault channel is enabled for a timer
  * @{
  */
#define HRPWM_FAULTEN_NONE      0x00000000U             /*!< No fault enabled   */
#define HRPWM_FAULTEN_FAULT0    (HRPWM_FLTR_FLT0EN)     /*!< Fault 0 enabled    */
#define HRPWM_FAULTEN_FAULT1    (HRPWM_FLTR_FLT1EN)     /*!< Fault 1 enabled    */
#define HRPWM_FAULTEN_FAULT2    (HRPWM_FLTR_FLT2EN)     /*!< Fault 2 enabled    */
#define HRPWM_FAULTEN_FAULT3    (HRPWM_FLTR_FLT3EN)     /*!< Fault 3 enabled    */
#define HRPWM_FAULTEN_FAULT4    (HRPWM_FLTR_FLT4EN)     /*!< Fault 4 enabled    */
#define HRPWM_FAULTEN_FAULT5    (HRPWM_FLTR_FLT5EN)     /*!< Fault 5 enabled    */
/**
  * @}
  */

/** @defgroup HRPWM_ADC_Trigger_Event HRPWM ADC Trigger Event
  * @brief constants defining the events triggering ADC conversion.
  *        HRPWM_ADCTRIGEVENT0246*: ADC Triggers 0 and 2 and 4 and 6
  *        HRPWM_ADCTRIGEVENT1357_*: ADC Triggers 1 and 3 and 5 and 7
  * @{
  */
#define HRPWM_ADCTRIGEVENT0_CMPD5       (HRPWM_ADT0R_CMPD5)     /*!< ADC Trigger on Slave Timer 5 compare D */
#define HRPWM_ADCTRIGEVENT0_CMPC5       (HRPWM_ADT0R_CMPC5)     /*!< ADC Trigger on Slave Timer 5 compare C */
#define HRPWM_ADCTRIGEVENT0_PER4        (HRPWM_ADT0R_PER4)      /*!< ADC Trigger on Slave Timer 4 period    */
#define HRPWM_ADCTRIGEVENT0_CMPD4       (HRPWM_ADT0R_CMPD4)     /*!< ADC Trigger on Slave Timer 4 compare D */
#define HRPWM_ADCTRIGEVENT0_CMPC4       (HRPWM_ADT0R_CMPC4)     /*!< ADC Trigger on Slave Timer 4 compare C */
#define HRPWM_ADCTRIGEVENT0_CMPB4       (HRPWM_ADT0R_CMPB4)     /*!< ADC Trigger on Slave Timer 4 compare B */
#define HRPWM_ADCTRIGEVENT0_RST3        (HRPWM_ADT0R_RST3)      /*!< ADC Trigger on Slave Timer 3 reset     */
#define HRPWM_ADCTRIGEVENT0_CMPD3       (HRPWM_ADT0R_CMPD3)     /*!< ADC Trigger on Slave Timer 3 compare D */
#define HRPWM_ADCTRIGEVENT0_CMPC3       (HRPWM_ADT0R_CMPC3)     /*!< ADC Trigger on Slave Timer 3 compare C */
#define HRPWM_ADCTRIGEVENT0_CMPB3       (HRPWM_ADT0R_CMPB3)     /*!< ADC Trigger on Slave Timer 3 compare B */
#define HRPWM_ADCTRIGEVENT0_PER2        (HRPWM_ADT0R_PER2)      /*!< ADC Trigger on Slave Timer 2 period    */
#define HRPWM_ADCTRIGEVENT0_CMPD2       (HRPWM_ADT0R_CMPD2)     /*!< ADC Trigger on Slave Timer 2 compare D */
#define HRPWM_ADCTRIGEVENT0_CMPC2       (HRPWM_ADT0R_CMPC2)     /*!< ADC Trigger on Slave Timer 2 compare C */
#define HRPWM_ADCTRIGEVENT0_CMPB2       (HRPWM_ADT0R_CMPB2)     /*!< ADC Trigger on Slave Timer 2 compare B */
#define HRPWM_ADCTRIGEVENT0_RST1        (HRPWM_ADT0R_RST1)      /*!< ADC Trigger on Slave Timer 1 reset     */
#define HRPWM_ADCTRIGEVENT0_CMPD1       (HRPWM_ADT0R_CMPD1)     /*!< ADC Trigger on Slave Timer 1 compare D */
#define HRPWM_ADCTRIGEVENT0_CMPC1       (HRPWM_ADT0R_CMPC1)     /*!< ADC Trigger on Slave Timer 1 compare C */
#define HRPWM_ADCTRIGEVENT0_CMPB1       (HRPWM_ADT0R_CMPB1)     /*!< ADC Trigger on Slave Timer 1 compare B */
#define HRPWM_ADCTRIGEVENT0_PER0        (HRPWM_ADT0R_PER0)      /*!< ADC Trigger on Slave Timer 0 period    */
#define HRPWM_ADCTRIGEVENT0_CMPD0       (HRPWM_ADT0R_CMPD0)     /*!< ADC Trigger on Slave Timer 0 compare D */
#define HRPWM_ADCTRIGEVENT0_CMPC0       (HRPWM_ADT0R_CMPC0)     /*!< ADC Trigger on Slave Timer 0 compare C */
#define HRPWM_ADCTRIGEVENT0_CMPB0       (HRPWM_ADT0R_CMPB0)     /*!< ADC Trigger on Slave Timer 0 compare B */
#define HRPWM_ADCTRIGEVENT0_RST5        (HRPWM_ADT0R_RST5)      /*!< ADC Trigger on Slave Timer 5 reset     */
#define HRPWM_ADCTRIGEVENT0_CMPB5       (HRPWM_ADT0R_CMPB5)     /*!< ADC Trigger on Slave Timer 5 compare B */
#define HRPWM_ADCTRIGEVENT0_EEV2        (HRPWM_ADT0R_EEV2)      /*!< ADC Trigger on external event 2        */
#define HRPWM_ADCTRIGEVENT0_EEV1        (HRPWM_ADT0R_EEV1)      /*!< ADC Trigger on external event 1        */
#define HRPWM_ADCTRIGEVENT0_EEV0        (HRPWM_ADT0R_EEV0)      /*!< ADC Trigger on external event 0        */
#define HRPWM_ADCTRIGEVENT0_MPER        (HRPWM_ADT0R_MPER)      /*!< ADC Trigger on Master Timer period     */
#define HRPWM_ADCTRIGEVENT0_MCMPD       (HRPWM_ADT0R_MCMPD)     /*!< ADC Trigger on Master Timer compare D  */
#define HRPWM_ADCTRIGEVENT0_MCMPC       (HRPWM_ADT0R_MCMPC)     /*!< ADC Trigger on Master Timer compare C  */
#define HRPWM_ADCTRIGEVENT0_MCMPB       (HRPWM_ADT0R_MCMPB)     /*!< ADC Trigger on Master Timer compare B  */
#define HRPWM_ADCTRIGEVENT0_MCMPA       (HRPWM_ADT0R_MCMPA)     /*!< ADC Trigger on Master Timer compare A  */

#define HRPWM_ADCTRIGEVENT1_CMPD5       (HRPWM_ADT1R_CMPD5)     /*!< ADC Trigger on Slave Timer 5 compare D */
#define HRPWM_ADCTRIGEVENT1_CMPC5       (HRPWM_ADT1R_CMPC5)     /*!< ADC Trigger on Slave Timer 5 compare C */
#define HRPWM_ADCTRIGEVENT1_RST4        (HRPWM_ADT1R_RST4)      /*!< ADC Trigger on Slave Timer 4 reset     */
#define HRPWM_ADCTRIGEVENT1_CMPD4       (HRPWM_ADT1R_CMPD4)     /*!< ADC Trigger on Slave Timer 4 compare D */
#define HRPWM_ADCTRIGEVENT1_CMPC4       (HRPWM_ADT1R_CMPC4)     /*!< ADC Trigger on Slave Timer 4 compare C */
#define HRPWM_ADCTRIGEVENT1_CMPB4       (HRPWM_ADT1R_CMPB4)     /*!< ADC Trigger on Slave Timer 4 compare B */
#define HRPWM_ADCTRIGEVENT1_PER3        (HRPWM_ADT1R_PER3)      /*!< ADC Trigger on Slave Timer 3 period    */
#define HRPWM_ADCTRIGEVENT1_CMPD3       (HRPWM_ADT1R_CMPD3)     /*!< ADC Trigger on Slave Timer 3 compare D */
#define HRPWM_ADCTRIGEVENT1_CMPC3       (HRPWM_ADT1R_CMPC3)     /*!< ADC Trigger on Slave Timer 3 compare C */
#define HRPWM_ADCTRIGEVENT1_CMPB3       (HRPWM_ADT1R_CMPB3)     /*!< ADC Trigger on Slave Timer 3 compare B */
#define HRPWM_ADCTRIGEVENT1_RST2        (HRPWM_ADT1R_RST2)      /*!< ADC Trigger on Slave Timer 2 reset     */
#define HRPWM_ADCTRIGEVENT1_CMPD2       (HRPWM_ADT1R_CMPD2)     /*!< ADC Trigger on Slave Timer 2 compare D */
#define HRPWM_ADCTRIGEVENT1_CMPC2       (HRPWM_ADT1R_CMPC2)     /*!< ADC Trigger on Slave Timer 2 compare C */
#define HRPWM_ADCTRIGEVENT1_CMPB2       (HRPWM_ADT1R_CMPB2)     /*!< ADC Trigger on Slave Timer 2 compare B */
#define HRPWM_ADCTRIGEVENT1_PER1        (HRPWM_ADT1R_PER1)      /*!< ADC Trigger on Slave Timer 1 period    */
#define HRPWM_ADCTRIGEVENT1_CMPD1       (HRPWM_ADT1R_CMPD1)     /*!< ADC Trigger on Slave Timer 1 compare D */
#define HRPWM_ADCTRIGEVENT1_CMPC1       (HRPWM_ADT1R_CMPC1)     /*!< ADC Trigger on Slave Timer 1 compare C */
#define HRPWM_ADCTRIGEVENT1_CMPB1       (HRPWM_ADT1R_CMPB1)     /*!< ADC Trigger on Slave Timer 1 compare B */
#define HRPWM_ADCTRIGEVENT1_RST0        (HRPWM_ADT1R_RST0)      /*!< ADC Trigger on Slave Timer 0 reset     */
#define HRPWM_ADCTRIGEVENT1_CMPD0       (HRPWM_ADT1R_CMPD0)     /*!< ADC Trigger on Slave Timer 0 compare D */
#define HRPWM_ADCTRIGEVENT1_CMPC0       (HRPWM_ADT1R_CMPC0)     /*!< ADC Trigger on Slave Timer 0 compare C */
#define HRPWM_ADCTRIGEVENT1_CMPB0       (HRPWM_ADT1R_CMPB0)     /*!< ADC Trigger on Slave Timer 0 compare B */
#define HRPWM_ADCTRIGEVENT1_PER5        (HRPWM_ADT1R_PER5)      /*!< ADC Trigger on Slave Timer 5 period    */
#define HRPWM_ADCTRIGEVENT1_CMPB5       (HRPWM_ADT1R_CMPB5)     /*!< ADC Trigger on Slave Timer 5 compare B */
#define HRPWM_ADCTRIGEVENT1_EEV2        (HRPWM_ADT1R_EEV5)      /*!< ADC Trigger on external event 2        */
#define HRPWM_ADCTRIGEVENT1_EEV1        (HRPWM_ADT1R_EEV4)      /*!< ADC Trigger on external event 1        */
#define HRPWM_ADCTRIGEVENT1_EEV0        (HRPWM_ADT1R_EEV3)      /*!< ADC Trigger on external event 0        */
#define HRPWM_ADCTRIGEVENT1_MPER        (HRPWM_ADT1R_MPER)      /*!< ADC Trigger on Master Timer period     */
#define HRPWM_ADCTRIGEVENT1_MCMPD       (HRPWM_ADT1R_MCMPD)     /*!< ADC Trigger on Master Timer compare D  */
#define HRPWM_ADCTRIGEVENT1_MCMPC       (HRPWM_ADT1R_MCMPC)     /*!< ADC Trigger on Master Timer compare C  */
#define HRPWM_ADCTRIGEVENT1_MCMPB       (HRPWM_ADT1R_MCMPB)     /*!< ADC Trigger on Master Timer compare B  */
#define HRPWM_ADCTRIGEVENT1_MCMPA       (HRPWM_ADT1R_MCMPA)     /*!< ADC Trigger on Master Timer compare A  */
/**
  * @}
  */

/** @defgroup HRPWM_Software_Timer_Update HRPWM Software Timer Update
  * @brief Constants used to force timer registers update
  * @{
  */
#define HRPWM_UPDATE_MASTER         (HRPWM_CR1_MSWU)/*!< Force an immediate transfer from the preload to the active register in the master timer    */
#define HRPWM_UPDATE_SLAVE_0        (HRPWM_CR1_SWU0)/*!< Force an immediate transfer from the preload to the active register in the slave timer 0   */
#define HRPWM_UPDATE_SLAVE_1        (HRPWM_CR1_SWU1)/*!< Force an immediate transfer from the preload to the active register in the slave timer 1   */
#define HRPWM_UPDATE_SLAVE_2        (HRPWM_CR1_SWU2)/*!< Force an immediate transfer from the preload to the active register in the slave timer 2   */
#define HRPWM_UPDATE_SLAVE_3        (HRPWM_CR1_SWU3)/*!< Force an immediate transfer from the preload to the active register in the slave timer 3   */
#define HRPWM_UPDATE_SLAVE_4        (HRPWM_CR1_SWU4)/*!< Force an immediate transfer from the preload to the active register in the slave timer 4   */
#define HRPWM_UPDATE_SLAVE_5        (HRPWM_CR1_SWU5)/*!< Force an immediate transfer from the preload to the active register in the slave timer 5   */
/**
  * @}
  */

/** @defgroup HRPWM_Software_Timer_SwapOutput  HRPWM Software Timer swap Output
  * @brief Constants used to swap the output of the timer registers
  * @{
  */
#define HRPWM_SWAP_SLAVE_0          (HRPWM_CR1_SWP0)    /*!< Swap the output of the slave Timer 0   */
#define HRPWM_SWAP_SLAVE_1          (HRPWM_CR1_SWP1)    /*!< Swap the output of the slave Timer 1   */
#define HRPWM_SWAP_SLAVE_2          (HRPWM_CR1_SWP2)    /*!< Swap the output of the slave Timer 2   */
#define HRPWM_SWAP_SLAVE_3          (HRPWM_CR1_SWP3)    /*!< Swap the output of the slave Timer 3   */
#define HRPWM_SWAP_SLAVE_4          (HRPWM_CR1_SWP4)    /*!< Swap the output of the slave Timer 4   */
#define HRPWM_SWAP_SLAVE_5          (HRPWM_CR1_SWP5)    /*!< Swap the output of the slave Timer 5   */
/**
  * @}
  */

/** @defgroup HRPWM_Software_Timer_Reset HRPWM Software Timer Reset
  * @brief Constants used to force timer counter reset
  * @{
  */
#define HRPWM_RESET_MASTER          (HRPWM_CR1_MRST)    /*!< Reset the master timer counter     */
#define HRPWM_RESET_SLAVE_0         (HRPWM_CR1_RST0)    /*!< Reset the slave timer 0 counter    */
#define HRPWM_RESET_SLAVE_1         (HRPWM_CR1_RST1)    /*!< Reset the slave timer 1 counter    */
#define HRPWM_RESET_SLAVE_2         (HRPWM_CR1_RST2)    /*!< Reset the slave timer 2 counter    */
#define HRPWM_RESET_SLAVE_3         (HRPWM_CR1_RST3)    /*!< Reset the slave timer 3 counter    */
#define HRPWM_RESET_SLAVE_4         (HRPWM_CR1_RST4)    /*!< Reset the slave timer 4 counter    */
#define HRPWM_RESET_SLAVE_5         (HRPWM_CR1_RST5)    /*!< Reset the slave timer 5 counter    */
/**
  * @}
  */

/** @defgroup HRPWM_Software_Timer_Update_Disable HRPWM Software Timer Update Disable
  * @brief Constants used to force timer counter Update Disable
  * @{
  */
#define HRPWM_UPDISABLE_MASTER      (HRPWM_CR0_MUDIS)   /*!< Update Disable the master timer counter    */
#define HRPWM_UPDISABLE_SLAVE_0     (HRPWM_CR0_UDIS0)   /*!< Update Disable the slave timer 0 counter   */
#define HRPWM_UPDISABLE_SLAVE_1     (HRPWM_CR0_UDIS1)   /*!< Update Disable the slave timer 1 counter   */
#define HRPWM_UPDISABLE_SLAVE_2     (HRPWM_CR0_UDIS2)   /*!< Update Disable the slave timer 2 counter   */
#define HRPWM_UPDISABLE_SLAVE_3     (HRPWM_CR0_UDIS3)   /*!< Update Disable the slave timer 3 counter   */
#define HRPWM_UPDISABLE_SLAVE_4     (HRPWM_CR0_UDIS4)   /*!< Update Disable the slave timer 4 counter   */
#define HRPWM_UPDISABLE_SLAVE_5     (HRPWM_CR0_UDIS5)   /*!< Update Disable the slave timer 5 counter   */
/**
  * @}
  */

/** @defgroup HRPWM_Software_forced_update HRPWM Software forced update
  * @brief Constants used to force timer counter Software forced update
  * @{
  */
#define HRPWM_SOFT_UPDATE_MASTER    (HRPWM_CR1_MSWU)    /*!< Update Disable the master timer counter    */
#define HRPWM_SOFT_UPDATE_SLAVE_0   (HRPWM_CR1_SWU0)    /*!< Update Disable the slave timer 0 counter   */
#define HRPWM_SOFT_UPDATE_SLAVE_1   (HRPWM_CR1_SWU1)    /*!< Update Disable the slave timer 1 counter   */
#define HRPWM_SOFT_UPDATE_SLAVE_2   (HRPWM_CR1_SWU2)    /*!< Update Disable the slave timer 2 counter   */
#define HRPWM_SOFT_UPDATE_SLAVE_3   (HRPWM_CR1_SWU3)    /*!< Update Disable the slave timer 3 counter   */
#define HRPWM_SOFT_UPDATE_SLAVE_4   (HRPWM_CR1_SWU4)    /*!< Update Disable the slave timer 4 counter   */
#define HRPWM_SOFT_UPDATE_SLAVE_5   (HRPWM_CR1_SWU5)    /*!< Update Disable the slave timer 5 counter   */
/**
  * @}
  */

/** @defgroup HRPWM_Output_State HRPWM Output State
  * @brief Constants defining the state of a timer output
  * @{
  */
#define HRPWM_OUTPUTSTATE_IDLE     (0x00000001U)  /*!< Main operating mode, where the output can take the active or
                                                              inactive level as programmed in the crossbar unit                 */
#define HRPWM_OUTPUTSTATE_RUN      (0x00000002U)  /*!< Default operating state (e.g. after an HRPWM reset, when the
                                                              outputs are disabled by software or during a burst mode operation */
#define HRPWM_OUTPUTSTATE_FAULT    (0x00000003U)  /*!< Safety state, entered in case of a shut-down request on
                                                              FAULTx inputs                                                     */
/**
  * @}
  */

/** @defgroup HRPWM_Common_Interrupt_Enable HRPWM Common Interrupt Enable
  * @{
  */
#define HRPWM_IT_SRC                (0x0000003FU)
#define HRPWM_IT_NONE               (0x00000000U)       /*!< No interrupt enabled           */
#define HRPWM_IT_FLT0               HRPWM_IER_FLT0IE    /*!< Fault 0 interrupt enable       */
#define HRPWM_IT_FLT1               HRPWM_IER_FLT1IE    /*!< Fault 1 interrupt enable       */
#define HRPWM_IT_FLT2               HRPWM_IER_FLT2IE    /*!< Fault 2 interrupt enable       */
#define HRPWM_IT_FLT3               HRPWM_IER_FLT3IE    /*!< Fault 3 interrupt enable       */
#define HRPWM_IT_FLT4               HRPWM_IER_FLT4IE    /*!< Fault 4 interrupt enable       */
#define HRPWM_IT_FLT5               HRPWM_IER_FLT5IE    /*!< Fault 5 interrupt enable       */
#define HRPWM_IT_SYSFLT             HRPWM_IER_SYSFLTIE  /*!< System Fault interrupt enable  */
/**
  * @}
  */

/** @defgroup HRPWM_Common_Interrupt_Flag HRPWM Common Interrupt Flag
  * @{
  */
#define HRPWM_FLAG_FLT0             HRPWM_ISR_FLT0      /*!< Fault 0 interrupt flag         */
#define HRPWM_FLAG_FLT1             HRPWM_ISR_FLT1      /*!< Fault 1 interrupt flag         */
#define HRPWM_FLAG_FLT2             HRPWM_ISR_FLT2      /*!< Fault 2 interrupt flag         */
#define HRPWM_FLAG_FLT3             HRPWM_ISR_FLT3      /*!< Fault 3 interrupt flag         */
#define HRPWM_FLAG_FLT4             HRPWM_ISR_FLT4      /*!< Fault 4 interrupt flag         */
#define HRPWM_FLAG_FLT5             HRPWM_ISR_FLT5      /*!< Fault 5 interrupt flag         */
#define HRPWM_FLAG_SYSFLT           HRPWM_ISR_SYSFLT    /*!< System Fault interrupt flag    */
/**
  * @}
  */

/** @defgroup HRPWM_Master_Interrupt_Enable HRPWM Master Interrupt Enable
  * @{
  */
#define HRPWM_MASTER_IT_SRC         0x000000FFU         /*!< ALL interrupt enabled                  */
#define HRPWM_MASTER_IT_NONE        0x00000000U         /*!< No interrupt enabled                   */
#define HRPWM_MASTER_IT_MCMPA       HRPWM_MIER_MCMPAIE  /*!< Master compare A interrupt enable      */
#define HRPWM_MASTER_IT_MCMPB       HRPWM_MIER_MCMPBIE  /*!< Master compare B interrupt enable      */
#define HRPWM_MASTER_IT_MCMPC       HRPWM_MIER_MCMPCIE  /*!< Master compare C interrupt enable      */
#define HRPWM_MASTER_IT_MCMPD       HRPWM_MIER_MCMPDIE  /*!< Master compare D interrupt enable      */
#define HRPWM_MASTER_IT_MPER        HRPWM_MIER_MPERIE   /*!< Master Period interrupt enable         */
#define HRPWM_MASTER_IT_SYNC        HRPWM_MIER_SYNCIE   /*!< Synchronization input interrupt enable */
#define HRPWM_MASTER_IT_MUPD        HRPWM_MIER_MUPDIE   /*!< Master update interrupt enable         */
#define HRPWM_MASTER_IT_MREP        HRPWM_MIER_MREPIE   /*!< Master Repetition interrupt enable     */
/**
  * @}
  */

/** @defgroup HRPWM_Master_Interrupt_Flag HRPWM Master Interrupt flag
  * @{
  */
#define HRPWM_MASTER_FLAG_NONE      0x00000000U         /*!< No interrupt flag                      */
#define HRPWM_MASTER_FLAG_MCMPA     HRPWM_MISR_MCMPA    /*!< Master compare A interrupt flag        */
#define HRPWM_MASTER_FLAG_MCMPB     HRPWM_MISR_MCMPB    /*!< Master compare B interrupt flag        */
#define HRPWM_MASTER_FLAG_MCMPC     HRPWM_MISR_MCMPC    /*!< Master compare C interrupt flag        */
#define HRPWM_MASTER_FLAG_MCMPD     HRPWM_MISR_MCMPD    /*!< Master compare D interrupt flag        */
#define HRPWM_MASTER_FLAG_MPER      HRPWM_MISR_MPER     /*!< Master Period interrupt flag           */
#define HRPWM_MASTER_FLAG_SYNC      HRPWM_MISR_SYNC     /*!< Synchronization input interrupt flag   */
#define HRPWM_MASTER_FLAG_MUPD      HRPWM_MISR_MUPD     /*!< Master update interrupt flag           */
#define HRPWM_MASTER_FLAG_MREP      HRPWM_MISR_MREP     /*!< Master Repetition interrupt flag       */
/**
  * @}
  */

/** @defgroup HRPWM_Slave_Timer_Unit_Interrupt_Enable HRPWM Timing Unit Interrupt Enable
  * @{
  */
#define HRPWM_IT_TIMER_SRC          0x00000FFFU         /*!< ALL interrupt enabled                  */
#define HRPWM_IT_TIMER_NONE         0x00000000U         /*!< No interrupt enabled                   */
#define HRPWM_IT_CMPA               HRPWM_IER_CMPAIE    /*!< Timer compare A interrupt enable       */
#define HRPWM_IT_CMPB               HRPWM_IER_CMPBIE    /*!< Timer compare B interrupt enable       */
#define HRPWM_IT_CMPC               HRPWM_IER_CMPCIE    /*!< Timer compare C interrupt enable       */
#define HRPWM_IT_CMPD               HRPWM_IER_CMPDIE    /*!< Timer compare D interrupt enable       */
#define HRPWM_IT_PER                HRPWM_IER_PERIE     /*!< Timer period interrupt enable          */
#define HRPWM_IT_UPD                HRPWM_IER_UPDIE     /*!< Timer update interrupt enable          */
#define HRPWM_IT_SETA               HRPWM_IER_SETAIE    /*!< Timer output 1 set interrupt enable    */
#define HRPWM_IT_CLRA               HRPWM_IER_CLRAIE    /*!< Timer output 1 reset interrupt enable  */
#define HRPWM_IT_SETB               HRPWM_IER_SETBIE    /*!< Timer output 2 set interrupt enable    */
#define HRPWM_IT_CLRB               HRPWM_IER_CLRBIE    /*!< Timer output 2 reset interrupt enable  */
#define HRPWM_IT_RST                HRPWM_IER_RSTIE     /*!< Timer reset interrupt enable           */
#define HRPWM_IT_REP                HRPWM_IER_REPIE     /*!< Timer repetition interrupt enable      */
/**
  * @}
  */

/** @defgroup HRPWM_Slave_Timer_Unit_Interrupt_Flag HRPWM Timing Unit Interrupt Flag
  * @{
  */
#define HRPWM_FLAG_CMPA             HRPWM_ISR_CMPA      /*!< Timer compare A interrupt flag         */
#define HRPWM_FLAG_CMPB             HRPWM_ISR_CMPB      /*!< Timer compare B interrupt flag         */
#define HRPWM_FLAG_CMPC             HRPWM_ISR_CMPC      /*!< Timer compare C interrupt flag         */
#define HRPWM_FLAG_CMPD             HRPWM_ISR_CMPD      /*!< Timer compare D interrupt flag         */
#define HRPWM_FLAG_PER              HRPWM_ISR_PER       /*!< Timer period interrupt flag            */
#define HRPWM_FLAG_UPD              HRPWM_ISR_UPD       /*!< Timer update interrupt flag            */
#define HRPWM_FLAG_SETA             HRPWM_ISR_SETA      /*!< Timer output 1 set interrupt flag      */
#define HRPWM_FLAG_CLRA             HRPWM_ISR_CLRA      /*!< Timer output 1 reset interrupt flag    */
#define HRPWM_FLAG_SETB             HRPWM_ISR_SETB      /*!< Timer output 2 set interrupt flag      */
#define HRPWM_FLAG_CLRB             HRPWM_ISR_CLRB      /*!< Timer output 2 reset interrupt flag    */
#define HRPWM_FLAG_RST              HRPWM_ISR_RST       /*!< Timer reset interrupt flag             */
#define HRPWM_FLAG_REP              HRPWM_ISR_REP       /*!< Timer repetition interrupt flag        */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup HRPWM_LL_Exported_Types HRPWM LL Exported Types
  * @brief    HRPWM LL Exported Types
  * @{
  */

/** @defgroup HRPWM_DLL_CURRENT HRPWM DLL CURRENT
  * @brief Constants defining dll current identifiers
  * @{
  */
typedef enum {
    HRPWM_DLLCR_DLLGCP_4 = 0x0,                                         /*!< DLL current selector bit: 4uA  */
    HRPWM_DLLCR_DLLGCP_6 = HRPWM_DLLCR_DLLGCP_0,                        /*!< DLL current selector bit: 6uA  */
    HRPWM_DLLCR_DLLGCP_8 = HRPWM_DLLCR_DLLGCP_1 | HRPWM_DLLCR_DLLGCP_0, /*!< DLL current selector bit: 8uA  */
} HRPWM_DllCurrentETypeDef;
/**
 * @}
 */

/** @defgroup HRPWM_ADC_Trigger HRPWM ADC Trigger
  * @brief Constants defining ADC triggers identifiers
  * @{
  */
typedef enum {
    HRPWM_ADCTRIGGER_0 = 0x0U,  /*!< ADC trigger 0 identifier   */
    HRPWM_ADCTRIGGER_1 = 0x1U,  /*!< ADC trigger 1 identifier   */
    HRPWM_ADCTRIGGER_2 = 0x2U,  /*!< ADC trigger 2 identifier   */
    HRPWM_ADCTRIGGER_3 = 0x3U,  /*!< ADC trigger 3 identifier   */
    HRPWM_ADCTRIGGER_4 = 0x4U,  /*!< ADC trigger 4 identifier   */
    HRPWM_ADCTRIGGER_5 = 0x5U,  /*!< ADC trigger 5 identifier   */
    HRPWM_ADCTRIGGER_6 = 0x6U,  /*!< ADC trigger 6 identifier   */
    HRPWM_ADCTRIGGER_7 = 0x7U,  /*!< ADC trigger 7 identifier   */
} HRPWM_AdcTrigGroupETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_External_Event_Channels HRPWM External Event Channels
  * @brief Constants defining external event channel identifiers
  * @{
  */
typedef enum {
    HRPWM_EVENT_NONE = 0x6U,    /*!< None Event                             */
    HRPWM_EVENT_0    = 0x0U,    /*!< External event channel 0  identifier   */
    HRPWM_EVENT_1    = 0x1U,    /*!< External event channel 1  identifier   */
    HRPWM_EVENT_2    = 0x2U,    /*!< External event channel 2  identifier   */
    HRPWM_EVENT_3    = 0x3U,    /*!< External event channel 3  identifier   */
    HRPWM_EVENT_4    = 0x4U,    /*!< External event channel 4  identifier   */
    HRPWM_EVENT_5    = 0x5U,    /*!< External event channel 5  identifier   */
} HRPWM_EventSelETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Fault_Channel HRPWM Fault Channel
  * @brief Constants defining fault channel identifiers
  * @{
  */
typedef enum {
    HRPWM_FAULT_0 = 0x00U,      /*!< Fault channel 0 identifier */
    HRPWM_FAULT_1 = 0x01U,      /*!< Fault channel 1 identifier */
    HRPWM_FAULT_2 = 0x02U,      /*!< Fault channel 2 identifier */
    HRPWM_FAULT_3 = 0x03U,      /*!< Fault channel 3 identifier */
    HRPWM_FAULT_4 = 0x04U,      /*!< Fault channel 4 identifier */
    HRPWM_FAULT_5 = 0x05U,      /*!< Fault channel 5 identifier */
    HRPWM_SYSFAULT = 0x06U,     /*!< Fault channel 5 identifier */
} HRPWM_FaultSelETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Prescaler_Ratio HRPWM Prescaler Ratio
  * @brief Constants defining timer high-resolution clock prescaler ratio.
  * @{
  */
typedef enum {
    HRPWM_PRESCALERRATIO_MUL32 = 0x0U,  /*!< fHRCK: fHRPWM x 32U = 5.12 GHz - Resolution: 195 ps    */
    HRPWM_PRESCALERRATIO_MUL16 = 0x1U,  /*!< fHRCK: fHRPWM x 16U = 2.56 GHz - Resolution: 390 ps    */
    HRPWM_PRESCALERRATIO_MUL8  = 0x2U,  /*!< fHRCK: fHRPWM x 8U = 1.28 GHz - Resolution: 781 ps     */
    HRPWM_PRESCALERRATIO_MUL4  = 0x3U,  /*!< fHRCK: fHRPWM x 4U = 640 MHz - Resolution: 1.56 ns     */
    HRPWM_PRESCALERRATIO_MUL2  = 0x4U,  /*!< fHRCK: fHRPWM x 2U = 320 MHz - Resolution: 3.125 ns    */
    HRPWM_PRESCALERRATIO_DIV1  = 0x5U,  /*!< fHRCK: fHRPWM = 160 MHz - Resolution: 6.25 ns          */
    HRPWM_PRESCALERRATIO_DIV2  = 0x6U,  /*!< fHRCK: fHRPWM / 2U = 80 MHz - Resolution: 12.5 ns      */
    HRPWM_PRESCALERRATIO_DIV4  = 0x7U,  /*!< fHRCK: fHRPWM / 4U = 40 MHz - Resolution: 25 ns        */
} HRPWM_PrescalerRatioETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Counter_Operating_Mode HRPWM Counter Operating Mode
  * @brief Constants defining timer counter operating mode.
  * @{
  */
typedef enum {
    HRPWM_MODE_CONTINUOUS               = HRPWM_CR0_CONT,   /*!< The timer operates in continuous (free-running) mode       */
    HRPWM_MODE_SINGLESHOT               = 0x0,              /*!< The timer operates in non retriggerable single-shot mode   */
    HRPWM_MODE_SINGLESHOT_RETRIGGERABLE = HRPWM_CR0_RETRIG, /*!< The timer operates in retriggerable single-shot mode       */
} HRPWM_ModeETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Half_Mode_Enable HRPWM Half Mode Enable
  * @brief Constants defining half mode enabling status.
  * @{
  */
typedef enum {
    HRPWM_HALFMODE_DISABLE = 0x0,               /*!< Half mode is disabled  */
    HRPWM_HALFMODE_ENABLE  = HRPWM_CR0_HALF,    /*!< Half mode is enabled   */
} HRPWM_HalfModeETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Interleaved_Mode HRPWM Interleaved Mode
  * @brief Constants defining interleaved mode enabling status.
  * @{
  */
typedef enum {
    HRPWM_INTERLEAVED_MODE_DISABLE = 0x0,                   /*!< HRPWM interleaved Mode is disabled */
    HRPWM_INTERLEAVED_MODE_TRIPLE  = HRPWM_CR0_INTLVD_0,    /*!< HRPWM interleaved Mode is Triple   */
    HRPWM_INTERLEAVED_MODE_QUAD    = HRPWM_CR0_INTLVD_1,    /*!< HRPWM interleaved Mode is Quad     */
} HRPWM_InterleavedModeETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_Push_Pull_Mode HRPWM Timer Push Pull Mode
  * @brief Constants defining whether or not the push-pull mode is enabled for a timer.
  * @{
  */
typedef enum {
    HRPWM_PUSHPULLMODE_DISABLE = 0x0,               /*!< Push-Pull mode disabled    */
    HRPWM_PUSHPULLMODE_ENABLE  = HRPWM_CR0_PSHPLL,  /*!< Push-Pull mode enabled     */
} HRPWM_PushpullModeETypeDef;

typedef enum {
    HRPWM_MODE_NONE                        = 0,                                     /*!< HRPWM mode none                        */
    HRPWM_MODE_HALF                        = HRPWM_CR0_HALF,                        /*!< HRPWM mode half                        */
    HRPWM_MODE_PUSHPULL                    = HRPWM_CR0_PSHPLL,                      /*!< HRPWM mode push pull                   */
    HRPWM_MODE_INTERLEAVED_TRIPLE          = HRPWM_CR0_INTLVD_0,                    /*!< HRPWM mode interleaved triple          */
    HRPWM_MODE_INTERLEAVED_QUAD            = HRPWM_CR0_INTLVD_1,                    /*!< HRPWM mode interleaved quad            */
    HRPWM_MODE_HALF_PUSHPULL               = HRPWM_CR0_HALF | HRPWM_CR0_PSHPLL,     /*!< HRPWM mode half push pull              */
    HRPWM_MODE_HALF_INTERLEAVED_TRIPLE     = HRPWM_CR0_HALF | HRPWM_CR0_INTLVD_0,   /*!< HRPWM mode half interleaved triple     */
    HRPWM_MODE_HALF_INTERLEAVED_QUAD       = HRPWM_CR0_HALF | HRPWM_CR0_INTLVD_1,   /*!< HRPWM mode half interleaved quad       */
    HRPWM_MODE_PUSHPULL_INTERLEAVED_TRIPLE = HRPWM_CR0_PSHPLL | HRPWM_CR0_INTLVD_0, /*!< HRPWM mode push pull interleaved triple*/
    HRPWM_MODE_PUSHPULL_INTERLEAVED_QUAD   = HRPWM_CR0_PSHPLL | HRPWM_CR0_INTLVD_1, /*!< HRPWM mode push pull interleaved quad  */
} HRPWM_OutputModeETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Start_On_Sync_Input_Event HRPWM Start On Sync Input Event
  * @brief Constants defining the timer behavior following the synchronization event
  * @{
  */
typedef enum {
    HRPWM_SYNCSTART_DISABLE = 0x0,                  /*!< Synchronization input event has effect on the timer    */
    HRPWM_SYNCSTART_ENABLE  = HRPWM_CR0_SYNCSTRT,   /*!< Synchronization input event starts the timer           */
} HRPWM_SyncStartETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Reset_On_Sync_Input_Event HRPWM Reset On Sync Input Event
  * @brief Constants defining the timer behavior following the synchronization event
  * @{
  */
typedef enum {
    HRPWM_SYNCRESET_DISABLE = 0x0,                  /*!< Synchronization input event has effect on the timer    */
    HRPWM_SYNCRESET_ENABLE  = HRPWM_CR0_SYNCRST,    /*!< Synchronization input event resets the timer           */
} HRPWM_SyncResetETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_Resync_Update_Enable HRPWM Re-Synchronized Update
  * @brief Constants defining whether the update source coming outside from the timing unit must be synchronized
  * @{
  */
typedef enum {
    HRPWM_RSYNCUPDATE_DISABLE = 0x0,                /*!< The update is taken into account immediately                           */
    HRPWM_RSYNCUPDATE_ENABLE  = HRPWM_CR0_RSYNCU,   /*!< The update is taken into account on the following Reset/Roll-over event*/
} HRPWM_RsyncUpdateETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Register_Preload_Enable HRPWM Register Preload Enable
  * @brief Constants defining whether a write access into a preloadable
  *        register is done into the active or the preload register.
  * @{
  */
typedef enum {
    HRPWM_PRELOAD_DISABLE = 0x0,            /*!< Preload disabled: the write access is directly done into the active register   */
    HRPWM_PRELOAD_ENABLE  = HRPWM_MCR_PREEN,/*!< Preload enabled: the write access is done into the preload register            */
} HRPWM_PreloadEnETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Synchronization_Input_Source HRPWM Synchronization Input Source
  * @brief Constants defining the synchronization input source
  * @{
  */
typedef enum {
    HRPWM_SYNCINPUTSOURCE_NONE             = 0x0,                               /*!< HRPWM Synchronization Input Source None    */
    HRPWM_SYNCINPUTSOURCE_TIM0_TRGO_EVENT  = HRPWM_MCR_SYNCIN_EN,               /*!< The HRPWM is synchronized with TIM0_TRGO   */
    HRPWM_SYNCINPUTSOURCE_EVENT            = HRPWM_MCR_SYNCIN_SRC | HRPWM_MCR_SYNCIN_EN,
    /*!< A positive pulse on SYNCIN input triggers the HRPWM */
} HRPWM_SyncInputSrcETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Synchronization_Output_Source HRPWM Synchronization Output Source
  * @brief Constants defining the source and event to be sent on the synchronization outputs
  * @{
  */
#define HRPWM_SYNCOUTPUTSOURCE_SRC             ( HRPWM_MCR_SYNCOUT_SRC_1 | HRPWM_MCR_SYNCOUT_SRC_0)
typedef enum {
    HRPWM_SYNCOUTPUTSOURCE_MASTER_START    = 0x0,
    /*!< A pulse is sent on the SYNCOUT output upon master timer start event        */
    HRPWM_SYNCOUTPUTSOURCE_MASTER_CMPA     = HRPWM_MCR_SYNCOUT_SRC_0,
    /*!< A pulse is sent on the SYNCOUT output upon master timer compare 1 event    */
    HRPWM_SYNCOUTPUTSOURCE_SLAVE0_STARTRST = HRPWM_MCR_SYNCOUT_SRC_1,
    /*!< A pulse is sent on the SYNCOUT output upon timer A start or reset events   */
    HRPWM_SYNCOUTPUTSOURCE_SLAVE0_CMPA     = HRPWM_MCR_SYNCOUT_SRC_1 | HRPWM_MCR_SYNCOUT_SRC_0,
    /*!< A pulse is sent on the SYNCOUT output upon timer A compare 1 event         */
} HRPWM_SyncOutputSrcETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Synchronization_Output_Polarity HRPWM Synchronization Output Polarity
  * @brief Constants defining the routing and conditioning of the synchronization output event
  * @{
  */
typedef enum {
    HRPWM_SYNCOUTPUTPOLARITY_NEGATIVE = HRPWM_MCR_SYNCOUT_POL,
    /*!< SCOUT pin has a low idle level and issues a positive pulse of 16 fHRPWM clock cycles length for the synchronization    */
    HRPWM_SYNCOUTPUTPOLARITY_POSITIVE = 0x0,
    /*!< SCOUT pin has a high idle level and issues a negative pulse of 16 fHRPWM clock cycles length for the synchronization   */
} HRPWM_SyncOutputPolETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Synchronization_Output_Enable HRPWM Synchronization Output Polarity
  * @brief Constants defining the routing and conditioning of the synchronization output event
  * @{
  */
typedef enum {
    HRPWM_SYNCOUTPUT_ENABLE  = HRPWM_MCR_SYNCOUT_EN,
    /*!< SCOUT pin has a low idle level and issues a positive pulse of 16 fHRPWM clock cycles length for the synchronization    */
    HRPWM_SYNCOUTPUT_DISABLE = 0x0,
    /*!< SCOUT pin has a high idle level and issues a negative pulse of 16 fHRPWM clock cycles length for the synchronization   */
} HRPWM_SyncOutputEnETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_Fault_RollOver_Mode HRPWM Timer RollOver Mode
  * @brief Constants defining when the roll-over is generated upon Timerx
  *        event generated when the counter is equal to 0  or to HRPWM_PERxR value  or BOTH
  *        This setting only applies when the UDM bit is set. It is not significant otherwise.
  * @{
  */
typedef enum {
    HRPWM_FLTROM_BOTH   = 0x0,                  /*!< The roll-over event is generated when the count is Period / 0  */
    HRPWM_FLTROM_ZERO   = HRPWM_CR1_FLTROM_0,   /*!< The roll-over event is generated when the count is 0           */
    HRPWM_FLTROM_PERIOD = HRPWM_CR1_FLTROM_1,   /*!< The roll-over event is generated when the count is Period      */
} HRPWM_FltRollOverETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_Event_RollOver_Mode HRPWM Timer RollOver Mode
  * @brief    HRPWM Timer RollOver Mode
  * @{
  */
typedef enum {
    HRPWM_EEVROM_BOTH   = 0x0,                  /*!< The roll-over event is generated when the count is Period / 0  */
    HRPWM_EEVROM_ZERO   = HRPWM_CR1_EEVROM_0,   /*!< The roll-over event is generated when the count is 0           */
    HRPWM_EEVROM_PERIOD = HRPWM_CR1_EEVROM_1,   /*!< The roll-over event is generated when the count is Period      */
} HRPWM_EventRollOverETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_ADTrig_RollOver_Mode HRPWM Timer RollOver Mode
  * @brief    HRPWM Timer RollOver Mode
  * @{
  */
typedef enum {
    HRPWM_ADROM_BOTH   = 0x0,               /*!< The roll-over event is generated when the count is Period / 0  */
    HRPWM_ADROM_ZERO   = HRPWM_CR1_ADROM_0, /*!< The roll-over event is generated when the count is 0           */
    HRPWM_ADROM_PERIOD = HRPWM_CR1_ADROM_1, /*!< The roll-over event is generated when the count is Period      */
} HRPWM_AdcRollOverETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_Output_RollOver_Mode HRPWM Timer RollOver Mode
  * @brief    HRPWM Timer RollOver Mode
  * @{
  */
typedef enum {
    HRPWM_OUTROM_BOTH   = 0x0,                  /*!< The roll-over event is generated when the count is Period / 0  */
    HRPWM_OUTROM_ZERO   = HRPWM_CR1_OUTROM_0,   /*!< The roll-over event is generated when the count is 0           */
    HRPWM_OUTROM_PERIOD = HRPWM_CR1_OUTROM_1,   /*!< The roll-over event is generated when the count is Period      */
} HRPWM_OutputRollOverETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_RollOver_Mode HRPWM Timer RollOver Mode
  * @breif    HRPWM Timer RollOver Mode
  * @{
  */
typedef enum {
    HRPWM_ROM_BOTH   = 0x0,             /*!< The roll-over event is generated when the count is Period / 0  */
    HRPWM_ROM_ZERO   = HRPWM_CR1_ROM_0, /*!< The roll-over event is generated when the count is 0           */
    HRPWM_ROM_PERIOD = HRPWM_CR1_ROM_1, /*!< The roll-over event is generated when the count is Period      */
} HRPWM_RollOverETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_UpDown_Mode HRPWM Timer UpDown Mode
  * @brief Constants defining how the timer counter operates
  * @{
  */
typedef enum {
    HRPWM_COUNT_UP     = 0x0,           /*!< Timer counter is operating in up-counting mode         */
    HRPWM_COUNT_UPDOWN = HRPWM_CR1_UDM, /*!< Timer counter is operating in up-down counting mode    */
} HRPWM_CounterModeETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_DualChannelDac_Reset HRPWM Dual Channel Dac Reset Trigger
  * @brief Constants defining when the HRPWM_dac_reset_trgx trigger is generated
  * @{
  */
typedef enum {
    HRPWM_DAC_DCDR_SETA  = 0x0,             /*!< the trigger is generated on output A set event                 */
    HRPWM_DAC_DCDR_RESET = HRPWM_CR1_DCDR,  /*!< the trigger is generated on counter reset or roll-over event   */
} HRPWM_DacResetSelETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_DualChannelDac_Step HRPWM Dual Channel Dac Step Trigger
  * @brief Constants defining when the HRPWM_dac_step_trgx trigger is generated
  * @{
  */
typedef enum {
    HRPWM_DAC_DCDS_CLEARA = 0x0,            /*!< the trigger is generated on output 1 reset event   */
    HRPWM_DAC_DCDS_CMPD   = HRPWM_CR1_DCDS, /*!< the trigger is generated on compare D event        */
} HRPWM_DacStepSelETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_DualChannelDac_Enable HRPWM Dual Channel DAC Trigger Enable
  * @brief Constants enabling the dual channel DAC triggering mechanism
  * @{
  */
typedef enum {
    HRPWM_DAC_DCDE_DISABLE = 0x0,               /*!< the Dual channel DAC trigger is disabled   */
    HRPWM_DAC_DCDE_ENABLE  = HRPWM_CR1_DCDE,    /*!< the Dual channel DAC trigger is enabled    */
} HRPWM_DacTrigEnETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Deadtime_Rising_Sign HRPWM Dead-time Rising Sign
  * @brief Constants defining whether the dead-time is positive or negative (overlapping signal) on rising edge
  * @{
  */
typedef enum {
    HRPWM_DEADTIME_RSIGN_NEGATIVE = 0x0,            /*!< Negative dead-time on rising edge  */
    HRPWM_DEADTIME_RSIGN_POSITIVE = HRPWM_DTR_SDTR, /*!< Positive dead-time on rising edge  */
} HRPWM_DeadTimeRiseSignETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Deadtime_Falling_Sign HRPWM Dead-time Falling Sign
  * @brief Constants defining whether the dead-time is positive or negative (overlapping signal) on falling edge
  * @{
  */
typedef enum {
    HRPWM_DEADTIME_FSIGN_NEGATIVE = 0x0,            /*!< Negative dead-time on falling edge */
    HRPWM_DEADTIME_FSIGN_POSITIVE = HRPWM_DTR_SDTF, /*!< Positive dead-time on falling edge */
} HRPWM_DeadTimeFallSignETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_External_Event_Filter HRPWM Timer External Event Filter
  * @brief Constants defining the event filtering applied to external events
  *        by a timer0 (5bit), the position of eventx need to left x*5bit;
  * @{
  */
typedef enum {
    HRPWM_EEVFLT_NONE                       = 0x0,
    /*!< HRPWM EEFVLT NONE                                                              */
    HRPWM_EEVFLT_BLANKING_CMPA              = HRPWM_EEFR0_EE0FLTR_0,
    /*!< Blanking from counter reset/roll-over to Compare A                             */
    HRPWM_EEVFLT_BLANKING_CMPB              = HRPWM_EEFR0_EE0FLTR_1,
    /*!< Blanking from counter reset/roll-over to Compare B                             */
    HRPWM_EEVFLT_BLANKING_CMPC              = HRPWM_EEFR0_EE0FLTR_1 | HRPWM_EEFR0_EE0FLTR_0,
    /*!< Blanking from counter reset/roll-over to Compare C                             */
    HRPWM_EEVFLT_BLANKING_CMPD              = HRPWM_EEFR0_EE0FLTR_2,
    /*!< Blanking from counter reset/roll-over to Compare D                             */
    HRPWM_EEVFLT_BLANKING_UPCMPA_UPCMPB     = HRPWM_EEFR0_EE0FLTR_2 | HRPWM_EEFR0_EE0FLTR_0,
    /*!< Blanking from counter up compare A to compare B only up_down mode valid        */
    HRPWM_EEVFLT_BLANKING_UPCMPC_UPCMPD     = HRPWM_EEFR0_EE0FLTR_2 | HRPWM_EEFR0_EE0FLTR_1,
    /*!< Blanking from counter up compare C to compare D only up_down mode valid        */
    HRPWM_EEVFLT_BLANKING_DOWNCMPA_DOWNCMPB = HRPWM_EEFR0_EE0FLTR_2 | HRPWM_EEFR0_EE0FLTR_1 | HRPWM_EEFR0_EE0FLTR_0,
    /*!< Blanking from counter down compare A to compare B only up_down mode valid      */
    HRPWM_EEVFLT_BLANKING_DOWNCMPC_DOWNCMPD = HRPWM_EEFR0_EE0FLTR_3,
    /*!< Blanking from counter down compare C to compare D only up_down mode valid      */
    HRPWM_EEVFLT_WINDOWS_BLANKING_CMPA      = HRPWM_EEFR0_EE0FLTR_3 | HRPWM_EEFR0_EE0FLTR_0,
    /*!< Windows from counter reset/roll-over to Compare A                              */
    HRPWM_EEVFLT_WINDOWS_BLANKING_CMPB      = HRPWM_EEFR0_EE0FLTR_3 | HRPWM_EEFR0_EE0FLTR_1,
    /*!< Windows from counter reset/roll-over to Compare B                              */
    HRPWM_EEVFLT_WINDOWS_BLANKING_CMPC      = HRPWM_EEFR0_EE0FLTR_3 | HRPWM_EEFR0_EE0FLTR_1 | HRPWM_EEFR0_EE0FLTR_0,
    /*!< Windows from counter reset/roll-over to Compare C                              */
    HRPWM_EEVFLT_WINDOWS_BLANKING_CMPD      = HRPWM_EEFR0_EE0FLTR_3 | HRPWM_EEFR0_EE0FLTR_2,
    /*!< Windows from counter reset/roll-over to Compare D                              */
    HRPWM_EEVFLT_WINDOWS_UPCMPB_UPCMPC      = HRPWM_EEFR0_EE0FLTR_3 | HRPWM_EEFR0_EE0FLTR_2 | HRPWM_EEFR0_EE0FLTR_0,
    /*!< Windows from counter up compare B to compare C only up_down mode valid         */
    HRPWM_EEVFLT_WINDOWS_DOWNCMPB_DOWNCMPC  = HRPWM_EEFR0_EE0FLTR_3 | HRPWM_EEFR0_EE0FLTR_2 | HRPWM_EEFR0_EE0FLTR_1,
    /*!< Windows from counter down compare B to compare C only up_down mode valid       */
    HRPWM_EEVFLT_WINDOWS_UPCMPB_DOWNCMPC    = HRPWM_EEFR0_EE0FLTR_3 | HRPWM_EEFR0_EE0FLTR_2 | HRPWM_EEFR0_EE0FLTR_1 | HRPWM_EEFR0_EE0FLTR_0,
    /*!< Windows from counter up compare B to down compare C only up_down mode valid    */
} HRPWM_EventAFilterWindowETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_External_Event_Latch HRPWM Timer External Event Latch
  * @brief Constants defining whether or not the external event is
  *        memorized (latched) and generated as soon as the blanking period
  *        is completed or the window ends, the position of eventx need to left x*5bit;
  * @{
  */
typedef enum {
    HRPWM_EVENTLATCH_DISABLE = 0x0,
    /*!< Event is ignored if it happens during a blank, or passed through during a window   */
    HRPWM_EVENTLATCH_ENABLE  = HRPWM_EEFR0_EE0LTCH,
    /*!< Event is latched and delayed till the end of the blanking or windowing period      */
} HRPWM_EventALatchETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_External_Event_Source_Select HRPWM Timer External Event Counter A source selection
  * @brief Constants defining the External Event Counter A source selection
  * @{
  */
typedef enum {
    HRPWM_EEVASEL_SOURCE_EEVENT0 = 0x00U,   /*!< External Event A selected event 0 as the source    */
    HRPWM_EEVASEL_SOURCE_EEVENT1 = 0x10U,   /*!< External Event A selected event 1 as the source    */
    HRPWM_EEVASEL_SOURCE_EEVENT2 = 0x20U,   /*!< External Event A selected event 2 as the source    */
    HRPWM_EEVASEL_SOURCE_EEVENT3 = 0x30U,   /*!< External Event A selected event 3 as the source    */
    HRPWM_EEVASEL_SOURCE_EEVENT4 = 0x40U,   /*!< External Event A selected event 4 as the source    */
    HRPWM_EEVASEL_SOURCE_EEVENT5 = 0x50U,   /*!< External Event A selected event 5 as the source    */
} HRPWM_EventASourceSelETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_External_Event_Counter HRPWM Timer External Event Counter
  * @brief Constants enabling the External Event A Counter
  * @{
  */
typedef enum {
    HRPWM_EEVACOUNTER_DISABLE = 0x0,                /*!< External Event Counter disabled    */
    HRPWM_EEVACOUNTER_ENABLE  = HRPWM_EEFR1_EEVACE, /*!< External Event Counter enabled     */
} HRPWM_EventACouterEnETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Timer_External_Event_ResetMode HRPWM Timer External Counter Reset Mode
  * @brief Constants enabling the External Event Counter A Reset Mode
  * @{
  */
typedef enum {
    HRPWM_EEVARSTM_UNCONDITIONAL   = 0x0,
    /*!< External Event Counter is reset on each reset / roll-over event                                                        */
    HRPWM_EEVARSTM_CONDITIONAL     = HRPWM_EEFR1_EEVARSTM,
    /*!< External Event Counter is reset on each reset / roll-over event only if no event occurs during last counting period    */
} HRPWM_EventARstModeETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Chopper_Frequency HRPWM Chopper Frequency
  * @brief Constants defining the frequency of the generated high frequency carrier
  * @{
  */
typedef enum {
    HRPWM_CHOPPER_CARFRQ_DIV16  = 0x0,
    /*!< fCHPFRQ = fHRPWM / 16  */
    HRPWM_CHOPPER_CARFRQ_DIV32  = HRPWM_CHPR_CARFRQ_0,
    /*!< fCHPFRQ = fHRPWM / 32  */
    HRPWM_CHOPPER_CARFRQ_DIV48  = HRPWM_CHPR_CARFRQ_1,
    /*!< fCHPFRQ = fHRPWM / 48  */
    HRPWM_CHOPPER_CARFRQ_DIV64  = HRPWM_CHPR_CARFRQ_1 | HRPWM_CHPR_CARFRQ_0,
    /*!< fCHPFRQ = fHRPWM / 64  */
    HRPWM_CHOPPER_CARFRQ_DIV80  = HRPWM_CHPR_CARFRQ_2,
    /*!< fCHPFRQ = fHRPWM / 80  */
    HRPWM_CHOPPER_CARFRQ_DIV96  = HRPWM_CHPR_CARFRQ_2 | HRPWM_CHPR_CARFRQ_0,
    /*!< fCHPFRQ = fHRPWM / 96  */
    HRPWM_CHOPPER_CARFRQ_DIV112 = HRPWM_CHPR_CARFRQ_2 | HRPWM_CHPR_CARFRQ_1,
    /*!< fCHPFRQ = fHRPWM / 112 */
    HRPWM_CHOPPER_CARFRQ_DIV128 = HRPWM_CHPR_CARFRQ_2 | HRPWM_CHPR_CARFRQ_1 | HRPWM_CHPR_CARFRQ_0,
    /*!< fCHPFRQ = fHRPWM / 128 */
    HRPWM_CHOPPER_CARFRQ_DIV144 = HRPWM_CHPR_CARFRQ_3,
    /*!< fCHPFRQ = fHRPWM / 144 */
    HRPWM_CHOPPER_CARFRQ_DIV160 = HRPWM_CHPR_CARFRQ_3 | HRPWM_CHPR_CARFRQ_0,
    /*!< fCHPFRQ = fHRPWM / 160 */
    HRPWM_CHOPPER_CARFRQ_DIV176 = HRPWM_CHPR_CARFRQ_3 | HRPWM_CHPR_CARFRQ_1,
    /*!< fCHPFRQ = fHRPWM / 176 */
    HRPWM_CHOPPER_CARFRQ_DIV192 = HRPWM_CHPR_CARFRQ_3 | HRPWM_CHPR_CARFRQ_1 | HRPWM_CHPR_CARFRQ_0,
    /*!< fCHPFRQ = fHRPWM / 192 */
    HRPWM_CHOPPER_CARFRQ_DIV208 = HRPWM_CHPR_CARFRQ_3 | HRPWM_CHPR_CARFRQ_2,
    /*!< fCHPFRQ = fHRPWM / 208 */
    HRPWM_CHOPPER_CARFRQ_DIV224 = HRPWM_CHPR_CARFRQ_3 | HRPWM_CHPR_CARFRQ_2 | HRPWM_CHPR_CARFRQ_0,
    /*!< fCHPFRQ = fHRPWM / 224 */
    HRPWM_CHOPPER_CARFRQ_DIV240 = HRPWM_CHPR_CARFRQ_3 | HRPWM_CHPR_CARFRQ_2 | HRPWM_CHPR_CARFRQ_1,
    /*!< fCHPFRQ = fHRPWM / 240 */
    HRPWM_CHOPPER_CARFRQ_DIV256 = HRPWM_CHPR_CARFRQ_3 | HRPWM_CHPR_CARFRQ_2 | HRPWM_CHPR_CARFRQ_1 | HRPWM_CHPR_CARFRQ_0,
    /*!< fCHPFRQ = fHRPWM / 256 */
} HRPWM_ChopperCarfreqETypeDef;
/**
 * @}
 */

/** @defgroup HRPWM_Chopper_Duty_Cycle HRPWM Chopper Duty Cycle
  * @brief Constants defining the duty cycle of the generated high frequency carrier
  *        Duty cycle can be adjusted by 1/8 step (from 0/8 up to 7/8)
  * @{
  */
typedef enum {
    HRPWM_CHOPPER_DUTYCYCLE_0    = 0x0,
    /*!< Only 1st pulse is present                      */
    HRPWM_CHOPPER_DUTYCYCLE_1    = HRPWM_CHPR_CARDTY_0,
    /*!< Duty cycle of the carrier signal is 12.5U %    */
    HRPWM_CHOPPER_DUTYCYCLE_2    = HRPWM_CHPR_CARDTY_1,
    /*!< Duty cycle of the carrier signal is 25U %      */
    HRPWM_CHOPPER_DUTYCYCLE_3    = HRPWM_CHPR_CARDTY_1 | HRPWM_CHPR_CARDTY_0,
    /*!< Duty cycle of the carrier signal is 37.5U %    */
    HRPWM_CHOPPER_DUTYCYCLE_4    = HRPWM_CHPR_CARDTY_2,
    /*!< Duty cycle of the carrier signal is 50U %      */
    HRPWM_CHOPPER_DUTYCYCLE_5    = HRPWM_CHPR_CARDTY_2 | HRPWM_CHPR_CARDTY_0,
    /*!< Duty cycle of the carrier signal is 62.5U %    */
    HRPWM_CHOPPER_DUTYCYCLE_6    = HRPWM_CHPR_CARDTY_2 | HRPWM_CHPR_CARDTY_1,
    /*!< Duty cycle of the carrier signal is 75U %      */
    HRPWM_CHOPPER_DUTYCYCLE_7    = HRPWM_CHPR_CARDTY_2 | HRPWM_CHPR_CARDTY_1 | HRPWM_CHPR_CARDTY_0,
    /*!< Duty cycle of the carrier signal is 87.5U %    */
} HRPWM_ChopperDutyETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Chopper_Start_Pulse_Width HRPWM Chopper Start Pulse Width
  * @brief Constants defining the pulse width of the first pulse of the generated high frequency carrier
  * @{
  */
typedef enum {
    HRPWM_CHOPPER_PULSEWIDTH_16  = 0x0,
    /*!< tSTPW = tHRPWM x 16    */
    HRPWM_CHOPPER_PULSEWIDTH_32  = HRPWM_CHPR_STRPW_0,
    /*!< tSTPW = tHRPWM x 32    */
    HRPWM_CHOPPER_PULSEWIDTH_48  = HRPWM_CHPR_STRPW_1,
    /*!< tSTPW = tHRPWM x 48    */
    HRPWM_CHOPPER_PULSEWIDTH_64  = HRPWM_CHPR_STRPW_1 | HRPWM_CHPR_STRPW_0,
    /*!< tSTPW = tHRPWM x 64    */
    HRPWM_CHOPPER_PULSEWIDTH_80  = HRPWM_CHPR_STRPW_2,
    /*!< tSTPW = tHRPWM x 80    */
    HRPWM_CHOPPER_PULSEWIDTH_96  = HRPWM_CHPR_STRPW_2 | HRPWM_CHPR_STRPW_0,
    /*!< tSTPW = tHRPWM x 96    */
    HRPWM_CHOPPER_PULSEWIDTH_112 = HRPWM_CHPR_STRPW_2 | HRPWM_CHPR_STRPW_1,
    /*!< tSTPW = tHRPWM x 112   */
    HRPWM_CHOPPER_PULSEWIDTH_128 = HRPWM_CHPR_STRPW_2 | HRPWM_CHPR_STRPW_1 | HRPWM_CHPR_STRPW_0,
    /*!< tSTPW = tHRPWM x 128   */
    HRPWM_CHOPPER_PULSEWIDTH_144 = HRPWM_CHPR_STRPW_3,
    /*!< tSTPW = tHRPWM x 144   */
    HRPWM_CHOPPER_PULSEWIDTH_160 = HRPWM_CHPR_STRPW_3 | HRPWM_CHPR_STRPW_0,
    /*!< tSTPW = tHRPWM x 160   */
    HRPWM_CHOPPER_PULSEWIDTH_176 = HRPWM_CHPR_STRPW_3 | HRPWM_CHPR_STRPW_1,
    /*!< tSTPW = tHRPWM x 176   */
    HRPWM_CHOPPER_PULSEWIDTH_192 = HRPWM_CHPR_STRPW_3 | HRPWM_CHPR_STRPW_1 | HRPWM_CHPR_STRPW_0,
    /*!< tSTPW = tHRPWM x 192   */
    HRPWM_CHOPPER_PULSEWIDTH_208 = HRPWM_CHPR_STRPW_3 | HRPWM_CHPR_STRPW_2,
    /*!< tSTPW = tHRPWM x 208   */
    HRPWM_CHOPPER_PULSEWIDTH_224 = HRPWM_CHPR_STRPW_3 | HRPWM_CHPR_STRPW_2 | HRPWM_CHPR_STRPW_0,
    /*!< tSTPW = tHRPWM x 224   */
    HRPWM_CHOPPER_PULSEWIDTH_240 = HRPWM_CHPR_STRPW_3 | HRPWM_CHPR_STRPW_2 | HRPWM_CHPR_STRPW_1,
    /*!< tSTPW = tHRPWM x 240   */
    HRPWM_CHOPPER_PULSEWIDTH_256 = HRPWM_CHPR_STRPW_3 | HRPWM_CHPR_STRPW_2 | HRPWM_CHPR_STRPW_1 | HRPWM_CHPR_STRPW_0,
    /*!< tSTPW = tHRPWM x 256   */
} HRPWM_ChopperPulseWidthETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Output_ChopperA_Mode_Enable HRPWM Output Chopper Mode Enable
  * @brief Constants defining whether or not chopper mode is enabled for a timer
           output
  * @{
  */
typedef enum {
    HRPWM_OUTPUTCHOPPERA_DISABLE = 0x0,             /*!< Output signal is not altered                   */
    HRPWM_OUTPUTCHOPPERA_ENABLE  = HRPWM_OUTR_CHPA, /*!< Output signal is chopped by a carrier signal   */
} HRPWM_ChopperAEnETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_OutputA_IDLE_Level HRPWM Output IDLE Level
  * @brief Constants defining the output level when output is in IDLE state
  * @{
  */
typedef enum {
    HRPWM_OUTPUTIDLEA_INACTIVE = 0x0,               /*!< Output at inactive level when in IDLE state    */
    HRPWM_OUTPUTIDLEA_ACTIVE   = HRPWM_OUTR_IDLESA, /*!< Output at active level when in IDLE state      */
} HRPWM_IdelALevelETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_OutputA_FAULT_Level HRPWM Output FAULT Level
  * @brief Constants defining the output level when output is in FAULT state
  * @{
  */
typedef enum {
    HRPWM_OUTPUTFAULTA_NONE     = 0x0,                                      /*!< The output is not affected by the fault input  */
    HRPWM_OUTPUTFAULTA_ACTIVE   = HRPWM_OUTR_FAULTA_0,                      /*!< Output at active level when in FAULT state     */
    HRPWM_OUTPUTFAULTA_INACTIVE = HRPWM_OUTR_FAULTA_1,                      /*!< Output at inactive level when in FAULT state   */
    HRPWM_OUTPUTFAULTA_HIGHZ    = HRPWM_OUTR_FAULTA_1 | HRPWM_OUTR_FAULTA_0,/*!< Output is tri-stated when in FAULT state       */
} HRPWM_FaultALevelETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_OutputA_Active_Polarity HRPWM Output Active_Polarity
  * @brief Constants whether the effective polarity is low level valid or high level valid
  * @{
  */
typedef enum {
    HRPWM_OUTPUT_POLA_POSITIVE = 0x0,               /*!< Positive polarity, high output efficiency  */
    HRPWM_OUTPUT_POLA_NEGATIVE = HRPWM_OUTR_POLA,   /*!< Negative polarity, low output efficiency   */
} HRPWM_OutputAPolETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Output_ChopperB_Mode_Enable HRPWM Output Chopper Mode Enable
  * @brief Constants defining whether or not chopper mode is enabled for a timer output
  * @{
  */
typedef enum {
    HRPWM_OUTPUTCHOPPERB_DISABLE = 0x0,             /*!< Output signal is not altered                   */
    HRPWM_OUTPUTCHOPPERB_ENABLE  = HRPWM_OUTR_CHPB, /*!< Output signal is chopped by a carrier signal   */
} HRPWM_ChopperBEnETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_OutputB_IDLE_Level HRPWM Output IDLE Level
  * @brief Constants defining the output level when output is in IDLE state
  * @{
  */
typedef enum {
    HRPWM_OUTPUTIDLEB_INACTIVE = 0x0,               /*!< Output at inactive level when in IDLE state    */
    HRPWM_OUTPUTIDLEB_ACTIVE   = HRPWM_OUTR_IDLESB, /*!< Output at active level when in IDLE state      */
} HRPWM_IdelBLevelETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_OutputB_FAULT_Level HRPWM Output FAULT Level
  * @brief Constants defining the output level when output is in FAULT state
  * @{
  */
typedef enum {
    HRPWM_OUTPUTFAULTB_NONE     = 0x0,                                      /*!< The output is not affected by the fault input  */
    HRPWM_OUTPUTFAULTB_ACTIVE   = HRPWM_OUTR_FAULTB_0,                      /*!< Output at active level when in FAULT state     */
    HRPWM_OUTPUTFAULTB_INACTIVE = HRPWM_OUTR_FAULTB_1,                      /*!< Output at inactive level when in FAULT state   */
    HRPWM_OUTPUTFAULTB_HIGHZ    = HRPWM_OUTR_FAULTB_1 | HRPWM_OUTR_FAULTB_0,/*!< Output is tri-stated when in FAULT state       */
} HRPWM_FaultBLevelETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_OutputB_Active_Polarity HRPWM Output Active_Polarity
  * @brief Constants whether the effective polarity is low level valid or high level valid
  * @{
  */
typedef enum {
    HRPWM_OUTPUT_POLB_POSITIVE = 0x0,               /*!< Positive polarity, high output efficiency  */
    HRPWM_OUTPUT_POLB_NEGATIVE = HRPWM_OUTR_POLB,   /*!< Negative polarity, low output efficiency   */
} HRPWM_OutputBPolETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_ADC_Trigger_PostScaler HRPWM ADC Trigger PostScaler
  * @brief constants defining the adc trigger PostScaler 0~0xf;
  * @{
  */
typedef enum {
    HRPWM_ADCTRIG_PSC_1       = 0x0,
    /*!< The PostScaler number of 1  */
    HRPWM_ADCTRIG_PSC_2       = HRPWM_ADPSR_ADPSC0_0,
    /*!< The PostScaler number of 2  */
    HRPWM_ADCTRIG_PSC_3       = HRPWM_ADPSR_ADPSC0_1,
    /*!< The PostScaler number of 3  */
    HRPWM_ADCTRIG_PSC_4       = HRPWM_ADPSR_ADPSC0_1 | HRPWM_ADPSR_ADPSC0_0,
    /*!< The PostScaler number of 4  */
    HRPWM_ADCTRIG_PSC_5       = HRPWM_ADPSR_ADPSC0_2,
    /*!< The PostScaler number of 5  */
    HRPWM_ADCTRIG_PSC_6       = HRPWM_ADPSR_ADPSC0_2 | HRPWM_ADPSR_ADPSC0_0,
    /*!< The PostScaler number of 6  */
    HRPWM_ADCTRIG_PSC_7       = HRPWM_ADPSR_ADPSC0_2 | HRPWM_ADPSR_ADPSC0_1,
    /*!< The PostScaler number of 7  */
    HRPWM_ADCTRIG_PSC_8       = HRPWM_ADPSR_ADPSC0_2 | HRPWM_ADPSR_ADPSC0_1 | HRPWM_ADPSR_ADPSC0_0,
    /*!< The PostScaler number of 8  */
    HRPWM_ADCTRIG_PSC_9       = HRPWM_ADPSR_ADPSC0_3,
    /*!< The PostScaler number of 9  */
    HRPWM_ADCTRIG_PSC_10      = HRPWM_ADPSR_ADPSC0_3 | HRPWM_ADPSR_ADPSC0_0,
    /*!< The PostScaler number of 10 */
    HRPWM_ADCTRIG_PSC_11      = HRPWM_ADPSR_ADPSC0_3 | HRPWM_ADPSR_ADPSC0_1,
    /*!< The PostScaler number of 11 */
    HRPWM_ADCTRIG_PSC_12      = HRPWM_ADPSR_ADPSC0_3 | HRPWM_ADPSR_ADPSC0_1 | HRPWM_ADPSR_ADPSC0_0,
    /*!< The PostScaler number of 12 */
    HRPWM_ADCTRIG_PSC_13      = HRPWM_ADPSR_ADPSC0_3 | HRPWM_ADPSR_ADPSC0_2,
    /*!< The PostScaler number of 13 */
    HRPWM_ADCTRIG_PSC_14      = HRPWM_ADPSR_ADPSC0_3 | HRPWM_ADPSR_ADPSC0_2 | HRPWM_ADPSR_ADPSC0_0,
    /*!< The PostScaler number of 14 */
    HRPWM_ADCTRIG_PSC_15      = HRPWM_ADPSR_ADPSC0_3 | HRPWM_ADPSR_ADPSC0_2 | HRPWM_ADPSR_ADPSC0_1,
    /*!< The PostScaler number of 15 */
    HRPWM_ADCTRIG_PSC_16      = HRPWM_ADPSR_ADPSC0_3 | HRPWM_ADPSR_ADPSC0_2 | HRPWM_ADPSR_ADPSC0_1 | HRPWM_ADPSR_ADPSC0_0,
    /*!< The PostScaler number of 16 */
} HRPWM_AdcTrigPSCETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_ADC_Trigger_Update_Source HRPWM ADC Trigger Update Source
  * @brief constants defining the source triggering the update of the
     HRPWM_ADCxR register (transfer from preload to active register). 3bit
  * @{
  */
typedef enum {
    HRPWM_ADCTRIGUPDATE_MASTER  = 0x0,                                          /*!< Master timer   */
    HRPWM_ADCTRIGUPDATE_TIMER_0 = HRPWM_CR0_ADUSRC0_0,                          /*!< Slave Timer 0  */
    HRPWM_ADCTRIGUPDATE_TIMER_1 = HRPWM_CR0_ADUSRC0_1,                          /*!< Slave Timer 1  */
    HRPWM_ADCTRIGUPDATE_TIMER_2 = HRPWM_CR0_ADUSRC0_1 | HRPWM_CR0_ADUSRC0_0,    /*!< Slave Timer 2  */
    HRPWM_ADCTRIGUPDATE_TIMER_3 = HRPWM_CR0_ADUSRC0_2,                          /*!< Slave Timer 3  */
    HRPWM_ADCTRIGUPDATE_TIMER_4 = HRPWM_CR0_ADUSRC0_2 | HRPWM_CR0_ADUSRC0_0,    /*!< Slave Timer 4  */
    HRPWM_ADCTRIGUPDATE_TIMER_5 = HRPWM_CR0_ADUSRC0_2 | HRPWM_CR0_ADUSRC0_1,    /*!< Slave Timer 5  */
} HRPWM_AdcTrigUpdateSrcETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_ADC_Trigger_Length HRPWM ADC Trigger Length
  * @brief constants defining the events triggering length. (left  x * 4bit)
  * @{
  */
typedef enum {
    HRPWM_ADCTRIG_LENGTH_1       = 0x0,
    /*!< The length of ADC trigger time is 1 clock  */
    HRPWM_ADCTRIG_LENGTH_2       = HRPWM_CR2_TLEN0_0,
    /*!< The length of ADC trigger time is 2 clock  */
    HRPWM_ADCTRIG_LENGTH_3       = HRPWM_CR2_TLEN0_1,
    /*!< The length of ADC trigger time is 3 clock  */
    HRPWM_ADCTRIG_LENGTH_4       = HRPWM_CR2_TLEN0_1 | HRPWM_CR2_TLEN0_0,
    /*!< The length of ADC trigger time is 4 clock  */
    HRPWM_ADCTRIG_LENGTH_5       = HRPWM_CR2_TLEN0_2,
    /*!< The length of ADC trigger time is 5 clock  */
    HRPWM_ADCTRIG_LENGTH_6       = HRPWM_CR2_TLEN0_2 | HRPWM_CR2_TLEN0_0,
    /*!< The length of ADC trigger time is 6 clock  */
    HRPWM_ADCTRIG_LENGTH_7       = HRPWM_CR2_TLEN0_2 | HRPWM_CR2_TLEN0_1,
    /*!< The length of ADC trigger time is 7 clock  */
    HRPWM_ADCTRIG_LENGTH_8       = HRPWM_CR2_TLEN0_2 | HRPWM_CR2_TLEN0_1 | HRPWM_CR2_TLEN0_0,
    /*!< The length of ADC trigger time is 8 clock  */
    HRPWM_ADCTRIG_LENGTH_9       = HRPWM_CR2_TLEN0_3,
    /*!< The length of ADC trigger time is 9 clock  */
    HRPWM_ADCTRIG_LENGTH_10      = HRPWM_CR2_TLEN0_3 | HRPWM_CR2_TLEN0_0,
    /*!< The length of ADC trigger time is 10 clock */
    HRPWM_ADCTRIG_LENGTH_11      = HRPWM_CR2_TLEN0_3 | HRPWM_CR2_TLEN0_1,
    /*!< The length of ADC trigger time is 11 clock */
    HRPWM_ADCTRIG_LENGTH_12      = HRPWM_CR2_TLEN0_3 | HRPWM_CR2_TLEN0_1 | HRPWM_CR2_TLEN0_0,
    /*!< The length of ADC trigger time is 12 clock */
    HRPWM_ADCTRIG_LENGTH_13      = HRPWM_CR2_TLEN0_3 | HRPWM_CR2_TLEN0_2,
    /*!< The length of ADC trigger time is 13 clock */
    HRPWM_ADCTRIG_LENGTH_14      = HRPWM_CR2_TLEN0_3 | HRPWM_CR2_TLEN0_2 | HRPWM_CR2_TLEN0_0,
    /*!< The length of ADC trigger time is 14 clock */
    HRPWM_ADCTRIG_LENGTH_15      = HRPWM_CR2_TLEN0_3 | HRPWM_CR2_TLEN0_2 | HRPWM_CR2_TLEN0_1,
    /*!< The length of ADC trigger time is 15 clock */
    HRPWM_ADCTRIG_LENGTH_16      = HRPWM_CR2_TLEN0_3 | HRPWM_CR2_TLEN0_2 | HRPWM_CR2_TLEN0_1 | HRPWM_CR2_TLEN0_0,
    /*!< The length of ADC trigger time is 16 clock */
} HRPWM_AdcTrigLengthETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_External_Event_Prescaler HRPWM External Event Prescaler
  * @brief Constants defining division ratio between the timer clock frequency
  *        fHRPWM) and the external event signal sampling clock (fEEVS)
  *        used by the digital filters
  * @{
  */
typedef enum {
    HRPWM_EEVSD_DIV1 = 0x0,                                                     /*!< fEEVS=fHRPWM       */
    HRPWM_EEVSD_DIV2 = HRPWM_EECR2_EEVSD_0,                                     /*!< fEEVS=fHRPWM / 2U  */
    HRPWM_EEVSD_DIV4 = (int32_t)HRPWM_EECR2_EEVSD_1,                            /*!< fEEVS=fHRPWM / 4U  */
    HRPWM_EEVSD_DIV8 = (int32_t)(HRPWM_EECR2_EEVSD_1 | HRPWM_EECR2_EEVSD_0),    /*!< fEEVS=fHRPWM / 8U  */
} HRPWM_EventPrescalerETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_External_Event_Filter HRPWM External Event Filter
  * @brief Constants defining the frequency used to sample an external event 6
  *        input and the length (N) of the digital filter applied
  * @{
  */
typedef enum {
    HRPWM_EVENTFILTER_NONE     = 0x0,
    /*!< Filter disabled            */
    HRPWM_EVENTFILTER_1        = HRPWM_EECR2_EE0F_0,
    /*!< fSAMPLING= fHRPWM, N=2U    */
    HRPWM_EVENTFILTER_2        = HRPWM_EECR2_EE0F_1,
    /*!< fSAMPLING= fHRPWM, N=4U    */
    HRPWM_EVENTFILTER_3        = HRPWM_EECR2_EE0F_1 | HRPWM_EECR2_EE0F_0,
    /*!< fSAMPLING= fHRPWM, N=8U    */
    HRPWM_EVENTFILTER_4        = HRPWM_EECR2_EE0F_2,
    /*!< fSAMPLING= fEEVS/2U, N=6U  */
    HRPWM_EVENTFILTER_5        = HRPWM_EECR2_EE0F_2 | HRPWM_EECR2_EE0F_0,
    /*!< fSAMPLING= fEEVS/2U, N=8U  */
    HRPWM_EVENTFILTER_6        = HRPWM_EECR2_EE0F_2 | HRPWM_EECR2_EE0F_1,
    /*!< fSAMPLING= fEEVS/4U, N=6U  */
    HRPWM_EVENTFILTER_7        = HRPWM_EECR2_EE0F_2 | HRPWM_EECR2_EE0F_1 | HRPWM_EECR2_EE0F_0,
    /*!< fSAMPLING= fEEVS/4U, N=8U  */
    HRPWM_EVENTFILTER_8        = HRPWM_EECR2_EE0F_3,
    /*!< fSAMPLING= fEEVS/8U, N=6U  */
    HRPWM_EVENTFILTER_9        = HRPWM_EECR2_EE0F_3 | HRPWM_EECR2_EE0F_0,
    /*!< fSAMPLING= fEEVS/8U, N=8U  */
    HRPWM_EVENTFILTER_10       = HRPWM_EECR2_EE0F_3 | HRPWM_EECR2_EE0F_1,
    /*!< fSAMPLING= fEEVS/16U, N=5U */
    HRPWM_EVENTFILTER_11       = HRPWM_EECR2_EE0F_3 | HRPWM_EECR2_EE0F_1 | HRPWM_EECR2_EE0F_0,
    /*!< fSAMPLING= fEEVS/16U, N=6U */
    HRPWM_EVENTFILTER_12       = HRPWM_EECR2_EE0F_3 | HRPWM_EECR2_EE0F_2,
    /*!< fSAMPLING= fEEVS/16U, N=8U */
    HRPWM_EVENTFILTER_13       = HRPWM_EECR2_EE0F_3 | HRPWM_EECR2_EE0F_2  | HRPWM_EECR2_EE0F_0,
    /*!< fSAMPLING= fEEVS/32U, N=5U */
    HRPWM_EVENTFILTER_14       = HRPWM_EECR2_EE0F_3 | HRPWM_EECR2_EE0F_2  | HRPWM_EECR2_EE0F_1,
    /*!< fSAMPLING= fEEVS/32U, N=6U */
    HRPWM_EVENTFILTER_15       = HRPWM_EECR2_EE0F_3 | HRPWM_EECR2_EE0F_2  | HRPWM_EECR2_EE0F_1 | HRPWM_EECR2_EE0F_0,
    /*!< fSAMPLING= fEEVS/32U, N=8U */
} HRPWM_EventFilterETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_External_Event_Fast_Mode HRPWM External Event Fast Mode
  * @brief Constants defining whether or not an external event is programmed in fast mode
  * @{
  */
typedef enum {
    HRPWM_EVENTFASTMODE_DISABLE = 0x0,
    /*!< External Event is re-synchronized by the HRPWM logic before acting on outputs  */
    HRPWM_EVENTFASTMODE_ENABLE  = HRPWM_EECR0_EE0FAST,
    /*!< External Event is acting asynchronously on outputs (low latency mode)          */
} HRPWM_EventFastModeETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_External_Event_Sensitivity HRPWM External Event Sensitivity
  * @brief Constants defining the sensitivity (level-sensitive or edge-sensitive)
  *        of an external event
  * @{
  */
typedef enum {
    HRPWM_EVENTSENS_LEVEL         = 0x0,
    /*!< External event is active on level                      */
    HRPWM_EVENTSENS_RISINGEDGE    = HRPWM_EECR0_EE0SNS_0,
    /*!< External event is active on Rising edge                */
    HRPWM_EVENTSENS_FALLINGEDGE   = HRPWM_EECR0_EE0SNS_1,
    /*!< External event is active on Falling edge               */
    HRPWM_EVENTSENS_BOTHEDGES     = HRPWM_EECR0_EE0SNS_1 | HRPWM_EECR0_EE0SNS_0,
    /*!< External event is active on Rising and Falling edges   */
} HRPWM_EventSensETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_External_Event_Polarity HRPWM External Event Polarity
  * @brief Constants defining the polarity of an external event
  * @{
  */
typedef enum {
    HRPWM_EVENTPOL_HIGH = 0x0,                  /*!< External event is active high  */
    HRPWM_EVENTPOL_LOW  = HRPWM_EECR0_EE0POL,   /*!< External event is active low   */
} HRPWM_EventPolETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_External_Event_Sources HRPWM External Event Sources
  * @brief Constants defining available sources associated to external events
  * @{
  */
typedef enum {
    HRPWM_EEVSRC_GPIO     = 0x0,                                            /*!< External event source 1U for External Event    */
    HRPWM_EEVSRC_COMP_OUT = HRPWM_EECR0_EE0SRC_0,                           /*!< External event source 2U for External Event    */
    HRPWM_EEVSRC_TIM_TRGO = HRPWM_EECR0_EE0SRC_1,                           /*!< External event source 3U for External Event    */
    HRPWM_EEVSRC_ADC_AWD  = HRPWM_EECR0_EE0SRC_1 | HRPWM_EECR0_EE0SRC_0,    /*!< External event source 4U for External Event    */
} HRPWM_EventSrcSelETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Fault_Enable HRPWM Fault Enable
  * @brief Constants defining the Enable of a fault event
  * @{
  */
typedef enum {
    HRPWM_FAULT_DISABLE = 0x0,                  /*!< Fault input is disable */
    HRPWM_FAULT_ENABLE  = HRPWM_FLTINR0_FLT0E,  /*!< Fault input is enable  */
} HRPWM_FaultEnETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Fault_Sources HRPWM Fault Sources
  * @brief Constants defining whether a fault is triggered by any external or internal fault source
  * @{
  */
typedef enum {
    HRPWM_FLTSRC_GPIO     = 0x0,                        /*!< The fault source 1U for External pin 0     */
    HRPWM_FLTSRC_COMP_OUT = HRPWM_FLTINR0_FLT0SRC_0,    /*!< The fault source 2U for External Event 0   */
    HRPWM_FLTSRC_EVENT    = HRPWM_FLTINR0_FLT0SRC_1,    /*!< The fault source 3U for internal Event 0   */
} HRPWM_FaultSrcSelETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Fault_Polarity HRPWM Fault Polarity
  * @brief Constants defining the polarity of a fault event
  * @{
  */
typedef enum {
    HRPWM_FAULTPOL_HIGH = 0x0,                  /*!< Fault input is active low  */
    HRPWM_FAULTPOL_LOW  = HRPWM_FLTINR0_FLT0P,  /*!< Fault input is active high */
} HRPWM_FaultPolETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Fault_Blanking HRPWM Fault Blanking Source
  * @brief Constants defining the blanking source of a fault event
  * @{
  */
typedef enum {
    HRPWM_FAULTBLKS_RSTALIGNED = 0x0,                       /*!< Fault blanking source is Reset-aligned window  */
    HRPWM_FAULTBLKS_MOVING     = HRPWM_FLTINR2_FLT0BLKS,    /*!< Fault blanking source is Moving window         */
} HRPWM_FaultBlkWindowETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Fault_ResetMode HRPWM Fault Reset Mode
  * @brief Constants defining the Counter reset mode of a fault event
  * @{
  */
typedef enum {
    HRPWM_FAULTRSTM_UNCONDITIONAL = 0x0,
    /*!< Fault counter is reset on each reset / roll-over event                                                         */
    HRPWM_FAULTRSTM_CONDITIONAL   = HRPWM_FLTINR2_FLT0RSTM,
    /*!< Fault counter is reset on each reset / roll-over event only if no fault occurred during last countingperiod.   */
} HRPWM_FaultRstModeETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Fault_Blanking_Control  HRPWM Fault Blanking Control
  * @brief Constants used to enable or disable the blanking mode of a fault channel
  * @{
  */
typedef enum {
    HRPWM_FAULTBLKEN_DISABLE = 0x0,                     /*!< No blanking on Fault   */
    HRPWM_FAULTBLKEN_ENABLE  = HRPWM_FLTINR2_FLT0BLKE,  /*!< Fault blanking mode    */
} HRPWM_FaultBlkEnETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_External_Fault_Prescaler HRPWM External Fault Prescaler
  * @brief Constants defining the division ratio between the timer clock
  *        frequency (fHRPWM) and the fault signal sampling clock (fFLTS) used
  *        by the digital filters.
  * @{
  */
typedef enum {
    HRPWM_FLTSD_DIV1 = 0x0,                                                         /*!< fFLTS=fHRPWM       */
    HRPWM_FLTSD_DIV2 = HRPWM_FLTINR1_FLTSD_0,                                       /*!< fFLTS=fHRPWM / 2U  */
    HRPWM_FLTSD_DIV4 = (int32_t)HRPWM_FLTINR1_FLTSD_1,                              /*!< fFLTS=fHRPWM / 4U  */
    HRPWM_FLTSD_DIV8 = (int32_t)(HRPWM_FLTINR1_FLTSD_1 | HRPWM_FLTINR1_FLTSD_0),    /*!< fFLTS=fHRPWM / 8U  */
} HRPWM_FaultPrescalerETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Fault_Filter HRPWM Fault Filter
  * @brief Constants defining the frequency used to sample the fault input and
  *         the length (N) of the digital filter applied
  * @{
  */
typedef enum {
    HRPWM_FAULTFILTER_NONE      = 0x0,
    /*!< Filter disabled            */
    HRPWM_FAULTFILTER_1         = HRPWM_FLTINR1_FLT0F_0,
    /*!< fSAMPLING= fHRPWM, N=2U    */
    HRPWM_FAULTFILTER_2         = HRPWM_FLTINR1_FLT0F_1,
    /*!< fSAMPLING= fHRPWM, N=4U    */
    HRPWM_FAULTFILTER_3         = HRPWM_FLTINR1_FLT0F_1 | HRPWM_FLTINR1_FLT0F_0,
    /*!< fSAMPLING= fHRPWM, N=8U    */
    HRPWM_FAULTFILTER_4         = HRPWM_FLTINR1_FLT0F_2,
    /*!< fSAMPLING= fFLTS/2U, N=6U  */
    HRPWM_FAULTFILTER_5         = HRPWM_FLTINR1_FLT0F_2 | HRPWM_FLTINR1_FLT0F_0,
    /*!< fSAMPLING= fFLTS/2U, N=8U  */
    HRPWM_FAULTFILTER_6         = HRPWM_FLTINR1_FLT0F_2 | HRPWM_FLTINR1_FLT0F_1,
    /*!< fSAMPLING= fFLTS/4U, N=6U  */
    HRPWM_FAULTFILTER_7         = HRPWM_FLTINR1_FLT0F_2 | HRPWM_FLTINR1_FLT0F_1 | HRPWM_FLTINR1_FLT0F_0,
    /*!< fSAMPLING= fFLTS/4U, N=8U  */
    HRPWM_FAULTFILTER_8         = HRPWM_FLTINR1_FLT0F_3,
    /*!< fSAMPLING= fFLTS/8U, N=6U  */
    HRPWM_FAULTFILTER_9         = HRPWM_FLTINR1_FLT0F_3 | HRPWM_FLTINR1_FLT0F_0,
    /*!< fSAMPLING= fFLTS/8U, N=8U  */
    HRPWM_FAULTFILTER_10        = HRPWM_FLTINR1_FLT0F_3 | HRPWM_FLTINR1_FLT0F_1,
    /*!< fSAMPLING= fFLTS/16U, N=5U */
    HRPWM_FAULTFILTER_11        = HRPWM_FLTINR1_FLT0F_3 | HRPWM_FLTINR1_FLT0F_1 | HRPWM_FLTINR1_FLT0F_0,
    /*!< fSAMPLING= fFLTS/16U, N=6U */
    HRPWM_FAULTFILTER_12        = HRPWM_FLTINR1_FLT0F_3 | HRPWM_FLTINR1_FLT0F_2,
    /*!< fSAMPLING= fFLTS/16U, N=8U */
    HRPWM_FAULTFILTER_13        = HRPWM_FLTINR1_FLT0F_3 | HRPWM_FLTINR1_FLT0F_2 | HRPWM_FLTINR1_FLT0F_0,
    /*!< fSAMPLING= fFLTS/32U, N=5U */
    HRPWM_FAULTFILTER_14        = HRPWM_FLTINR1_FLT0F_3 | HRPWM_FLTINR1_FLT0F_2 | HRPWM_FLTINR1_FLT0F_1,
    /*!< fSAMPLING= fFLTS/32U, N=6U */
    HRPWM_FAULTFILTER_15        = HRPWM_FLTINR1_FLT0F_3 | HRPWM_FLTINR1_FLT0F_2 | HRPWM_FLTINR1_FLT0F_1 | HRPWM_FLTINR1_FLT0F_0,
    /*!< fSAMPLING= fFLTS/32U, N=8U */
} HRPWM_FaultFilterETypeDef;
/**
  * @}
  */

/** @defgroup HRPWM_Fault_Counter HRPWM Fault counter threshold value
  * @brief Constants defining the FAULT Counter threshold (FLTCNT + 1)
  * @{
  */
typedef enum {
    HRPWM_FAULTCOUNTER_NONE    = 0x0,
    /*!< Counter threshold = 0U     */
    HRPWM_FAULTCOUNTER_1       = HRPWM_FLTINR3_FLT0CNT_0,
    /*!< Counter threshold = 1U     */
    HRPWM_FAULTCOUNTER_2       = HRPWM_FLTINR3_FLT0CNT_1,
    /*!< Counter threshold = 2U     */
    HRPWM_FAULTCOUNTER_3       = HRPWM_FLTINR3_FLT0CNT_1 | HRPWM_FLTINR3_FLT0CNT_0,
    /*!< Counter threshold = 3U     */
    HRPWM_FAULTCOUNTER_4       = HRPWM_FLTINR3_FLT0CNT_2,
    /*!< Counter threshold = 4U     */
    HRPWM_FAULTCOUNTER_5       = HRPWM_FLTINR3_FLT0CNT_2 | HRPWM_FLTINR3_FLT0CNT_0,
    /*!< Counter threshold = 5U     */
    HRPWM_FAULTCOUNTER_6       = HRPWM_FLTINR3_FLT0CNT_2 | HRPWM_FLTINR3_FLT0CNT_1,
    /*!< Counter threshold = 6U     */
    HRPWM_FAULTCOUNTER_7       = HRPWM_FLTINR3_FLT0CNT_2 | HRPWM_FLTINR3_FLT0CNT_1 | HRPWM_FLTINR3_FLT0CNT_0,
    /*!< Counter threshold = 7U     */
    HRPWM_FAULTCOUNTER_8       = HRPWM_FLTINR3_FLT0CNT_3,
    /*!< Counter threshold = 8U     */
    HRPWM_FAULTCOUNTER_9       = HRPWM_FLTINR3_FLT0CNT_3 | HRPWM_FLTINR3_FLT0CNT_0,
    /*!< Counter threshold = 9U     */
    HRPWM_FAULTCOUNTER_10      = HRPWM_FLTINR3_FLT0CNT_3 | HRPWM_FLTINR3_FLT0CNT_1,
    /*!< Counter threshold = 10U    */
    HRPWM_FAULTCOUNTER_11      = HRPWM_FLTINR3_FLT0CNT_3 | HRPWM_FLTINR3_FLT0CNT_1 | HRPWM_FLTINR3_FLT0CNT_0,
    /*!< Counter threshold = 11U    */
    HRPWM_FAULTCOUNTER_12      = HRPWM_FLTINR3_FLT0CNT_3 | HRPWM_FLTINR3_FLT0CNT_2,
    /*!< Counter threshold = 12U    */
    HRPWM_FAULTCOUNTER_13      = HRPWM_FLTINR3_FLT0CNT_3 | HRPWM_FLTINR3_FLT0CNT_2 | HRPWM_FLTINR3_FLT0CNT_0,
    /*!< Counter threshold = 13U    */
    HRPWM_FAULTCOUNTER_14      = HRPWM_FLTINR3_FLT0CNT_3 | HRPWM_FLTINR3_FLT0CNT_2 | HRPWM_FLTINR3_FLT0CNT_1,
    /*!< Counter threshold = 14U    */
    HRPWM_FAULTCOUNTER_15      = HRPWM_FLTINR3_FLT0CNT_3 | HRPWM_FLTINR3_FLT0CNT_2 | HRPWM_FLTINR3_FLT0CNT_1 | HRPWM_FLTINR3_FLT0CNT_0,
    /*!< Counter threshold = 15U    */
} HRPWM_FaultCounterETypeDef;
/**
  * @}
  */


/**
  * @brief HRPWM Master Timer Configuration Structure definition - Time base related parameters
  */
typedef struct __HRPWM_MasterSyncTypeDef {
    uint32_t                 SyncOptions;           /*!< Specifies how the HRPWM instance handles the external synchronization signals.
                                                        The HRPWM instance can be configured to act as a slave (waiting for a trigger
                                                        to be synchronized) or a master (generating a synchronization signal) or both.
                                                        This parameter can be a combination of @ref HRPWM_Synchronization_Options.          */
    HRPWM_SyncInputSrcETypeDef SyncInputSource;     /*!< Specifies the external synchronization input source (significant only when
                                                        the HRPWM instance is configured as a slave).                                       */
    HRPWM_SyncOutputSrcETypeDef SyncOutputSource;   /*!< Specifies the source and event to be sent on the external synchronization outputs
                                                        (significant only when the HRPWM instance is configured as a master).               */
    HRPWM_SyncOutputEnETypeDef SyncOutputEnable;    /*!< Specifies the source and event to be sent on the external synchronization outputs
                                                        (significant only when the HRPWM is configured as a master).*/
    HRPWM_SyncOutputPolETypeDef SyncOutputPolarity; /*!< Specifies the conditioning of the event to be sent on the external synchronization
                                                        outputs (significant only when the HRPWM instance is configured as a master).       */
} HRPWM_MasterSyncTypeDef;

/**
  * @brief  Timer configuration definition -- Timerx (x=0...5) & Master timer
  */
typedef struct __HRPWM_TimerBaseCfgTypeDef {
    uint32_t InterruptRequests;                 /*!< Relevant for all HRPWM timers, including the master.
                                                    Specifies which interrupts requests must enabled for the timer.
                                                    This parameter can be any combination of  @ref HRPWM_Master_Interrupt_Enable
                                                    or @ref HRPWM_Timing_Unit_Interrupt_Enable                                          */
    uint32_t Period;                            /*!< Specifies the timer period.
                                                    The period value must be above 3 periods of the fHRPWM clock.
                                                    Maximum value is = 0xFFFDU                                                          */
    uint32_t RepetitionCounter;                 /*!< Specifies the timer repetition period.
                                                    This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.        */
    uint32_t ResetTrigger;                      /*!< Relevant for Timer0 to Timer5. no master timer.
                                                    Specifies source(s) triggering the timer counter reset.
                                                    This parameter can be a combination of @ref HRPWM_Timer_Reset_Trigger               */
    HRPWM_PrescalerRatioETypeDef PrescalerRatio;/*!< Specifies the timer clock prescaler ratio.                                         */
    HRPWM_ModeETypeDef Mode;                    /*!< Specifies the counter operating mode. continues or single                          */
    HRPWM_SyncStartETypeDef StartOnSync;        /*!< Relevant for all HRPWM timers, including the master.Specifies whether or
                                                     not timer is reset by a rising edge on the synchronization input (when enabled).   */
    HRPWM_SyncResetETypeDef ResetOnSync;        /*!< Relevant for all HRPWM timers, including the master.Specifies whether or
                                                     not timer is reset by a rising edge on the synchronization input (when enabled).   */
    HRPWM_RsyncUpdateETypeDef ReSyncUpdate;     /*!< Relevant for Timer0 to Timer5.Specifies whether update source is coming
                                                     from the timing unit @ref HRPWM_Timer_Resync_Update_Enable                         */

} HRPWM_TimerBaseCfgTypeDef;

/**
  * @brief  Simple output compare mode configuration definition -- Timerx (x=0...5) & Master timer
  */
typedef struct __HRPWM_TimerCompareCfgTypeDef {
    HRPWM_PreloadEnETypeDef PreloadEnable;   /*!< Relevant for all HRPWM timers, including the master.
                                                  Specifies whether or not register preload is enabled.                                     */
    uint32_t UpdateTrigger;                  /*!< Relevant for Timer0 to Timer5. no Master timer update source ;
                                                  Specifies source(s) triggering the timer registers update.
                                                  This parameter can be a combination of @ref HRPWM_Timer_Update_Trigger                    */
    uint32_t CompareValueA;                  /*!< Specifies the compare A value of the timer compare unit.
                                                  The minimum value must be greater than or equal to 3 periods of the fHRPWM clock.
                                                  The maximum value must be less than or equal to 0xFFFFU - 1 periods of the fHRPWM clock   */
    uint32_t CompareValueB;                  /*!< Specifies the compare B value of the timer compare unit.
                                                  The minimum value must be greater than or equal to 3 periods of the fHRPWM clock.
                                                  The maximum value must be less than or equal to 0xFFFFU - 1 periods of the fHRPWM clock   */
    uint32_t CompareValueC;                  /*!< Specifies the compare C value of the timer compare unit.
                                                  The minimum value must be greater than or equal to 3 periods of the fHRPWM clock.
                                                  The maximum value must be less than or equal to 0xFFFFU - 1 periods of the fHRPWM clock   */
    uint32_t CompareValueD;                  /*!< Specifies the compare D value of the timer compare unit.
                                                  The minimum value must be greater than or equal to 3 periods of the fHRPWM clock.
                                                  The maximum value must be less than or equal to 0xFFFFU - 1 periods of the fHRPWM clock   */
} HRPWM_TimerCompareCfgTypeDef;

/**
  * @brief  Timer RollOver definition  -- Timerx (x=0...5)
  */
typedef struct __HRPWM_TimerRollOverCfgTypeDef {
    HRPWM_CounterModeETypeDef UpDownMode;          /*!< Relevant for Timer0 to Timer5.
                                                    Specifies whether or not counter is operating in up or up-down counting mode.               */
    HRPWM_RollOverETypeDef RollOverMode;           /*!< Relevant for Timer0 to Timer5.
                                                    Roll over mode selection Settings are only valid in up-down counting mode.                  */
    HRPWM_OutputRollOverETypeDef OutputRollOverMode;/*!< Relevant for Timer0 to Timer5.
                                                    Output roll over mode selection Settings, valid only in up-down counting mode.              */
    HRPWM_FltRollOverETypeDef FaultRollOverMode;   /*!< Relevant for Timer0 to Timer5.
                                                    The fault roll over mode selection setting is only valid in up-down counting mode.          */
    HRPWM_EventRollOverETypeDef EeventRollOverMode;/*!< Relevant for Timer0 to Timer5.
                                                    The event roll over mode selection setting is only valid in up-down counting mode.          */
    HRPWM_AdcRollOverETypeDef AdcRollOverMode;     /*!< Relevant for Timer0 to Timer5.
                                                    The ADDA trigger roll over mode selection setting is only valid in up-down counting mode.   */
} HRPWM_TimerRollOverCfgTypeDef;

/**
  * @brief  Timer Daul Channel Dac definition  -- Timerx (x=0...5)
  */
typedef struct __HRPWM_TimerDaulDacCfgTypeDef {
    HRPWM_DacResetSelETypeDef DualChannelDacReset;  /*!< Relevant for Timer0 to Timer5.
                                                        Specifies how the HRPWM_dac_reset_trgx trigger is generated.    */
    HRPWM_DacStepSelETypeDef DualChannelDacStep;    /*!< Relevant for Timer0 to Timer5.
                                                        Specifies how the HRPWM_dac_step_trgx trigger is generated.     */
    HRPWM_DacTrigEnETypeDef DualChannelDacEnable;   /*!< Relevant for Timer0 to Timer5.
                                                        Enables or not the dual channel DAC triggering mechanism.       */
} HRPWM_TimerDaulDacCfgTypeDef;

/**
  * @brief  Output configuration definition -- Timerx (x=0...5)
  */
typedef struct __HRPWM_OutputCfgTypeDef {
    HRPWM_OutputAPolETypeDef OutputAPolarity;       /*!< Specifies the output polarity.                                                 */
    HRPWM_IdelALevelETypeDef IdleALevel;            /*!< Specifies whether the output level is active or inactive when in IDLE state.   */
    HRPWM_FaultALevelETypeDef FaultALevel;           /*!< Specifies whether the output level is active or inactive when in FAULT state. */
    HRPWM_ChopperAEnETypeDef ChopperAModeEnable;    /*!< Indicates whether or not the chopper mode is enabled*/
    HRPWM_OutputBPolETypeDef  OutputBPolarity;      /*!< Specifies the output polarity.*/
    HRPWM_IdelBLevelETypeDef  IdleBLevel;           /*!< Specifies whether the output level is active or inactive when in IDLE state.   */
    HRPWM_FaultBLevelETypeDef FaultBLevel;          /*!< Specifies whether the output level is active or inactive when in FAULT state.  */
    HRPWM_ChopperBEnETypeDef  ChopperBModeEnable;   /*!< Indicates whether or not the chopper mode is enabled                           */
    uint32_t OutputASetSource;                      /*!< A channel output action set source event selection
                                                        This parameter can be combination value of @ref HRPWM_Timer_Set_Trigger         */
    uint32_t OutputAClearSource;                    /*!< A channel output action clear source event selection
                                                        This parameter can be combination value of @ref HRPWM_Timer_Clear_Trigger       */
    uint32_t OutputBSetSource;                      /*!< B channel output action set source event selection
                                                        This parameter can be combination value of @ref HRPWM_Timer_Set_Trigger         */
    uint32_t OutputBClearSource;                    /*!< B channel output action clear source event selection
                                                        This parameter can be combination value of @ref HRPWM_Timer_Clear_Trigger       */
} HRPWM_OutputCfgTypeDef;

/**
  * @brief  Dead time feature configuration definition -- Timerx (x=0...5)
  */
typedef struct __HRPWM_DeadTimeCfgTypeDef {
    LL_FuncStatusETypeDef DeadTimeEn;               /*!< Specifies the dead-time output enable                                      */

    uint32_t RisingValue;                           /*!< Specifies the dead-time following a rising edge.
                                                        This parameter can be a number between 0x0 and 0xFFFU                       */
    HRPWM_DeadTimeRiseSignETypeDef RisingSign;      /*!< Specifies whether the dead-time is positive or negative on rising edge.    */
    uint32_t FallingValue;                          /*!< Specifies the dead-time following a falling edge.
                                                        This parameter can be a number between 0x0 and 0xFFFU                       */
    HRPWM_DeadTimeFallSignETypeDef FallingSign;     /*!< Specifies whether the dead-time is positive or negative on falling edge.   */
} HRPWM_DeadTimeCfgTypeDef;

/**
  * @brief  Chopper mode configuration definition -- Timerx (x=0...5)
  */
typedef struct __HRPWM_ChopperModeCfgTypeDef {
    HRPWM_ChopperAEnETypeDef ChopperAModeEnable;    /*!< Indicates whether or not the chopper mode is enabled   */
    HRPWM_ChopperBEnETypeDef ChopperBModeEnable;    /*!< Indicates whether or not the chopper mode is enabled   */
    HRPWM_ChopperCarfreqETypeDef CarrierFreq;       /*!< Specifies the Timer carrier frequency value.           */
    HRPWM_ChopperDutyETypeDef DutyCycle;            /*!< Specifies the Timer chopper duty cycle value.          */
    HRPWM_ChopperPulseWidthETypeDef StartPulse;     /*!< Specifies the Timer pulse width value.                 */
} HRPWM_ChopperModeCfgTypeDef;

/**
  * @brief  External event filtering in timing units configuration definition -- Timerx (x=0...5)
  */
typedef struct __HRPWM_TimerEventFilteringCfgTypeDef {
    HRPWM_EventAFilterWindowETypeDef Filter;        /*!< Specifies the type of event filtering within the timing unit.  */
    HRPWM_EventALatchETypeDef Latch;                /*!< Specifies whether or not the signal is latched.                */
} HRPWM_TimerEventFilteringCfgTypeDef;

/**
  * @brief  External Event Counter A configuration definition  -- Timerx (x=0...5)
  */
typedef struct __HRPWM_ExternalEventACfgTypeDef {
    HRPWM_EventACouterEnETypeDef CounterEnable; /*!< Specifies the External Event A Counter enable.             */
    HRPWM_EventARstModeETypeDef ResetMode;      /*!< Specifies the External Event A Counte Reset Mode.          */
    HRPWM_EventASourceSelETypeDef Source;       /*!< Specifies the External Event A Counter source selection.   */
    uint32_t Counter;                           /*!< Specifies the External Event A Counter Threshold.
                                                    This parameter can be a number between 0x0 and 0x3F         */
} HRPWM_ExternalEventACfgTypeDef;

/**
  * @brief  External event channel configuration definition  -- common timer
  */
typedef struct __HRPWM_EventCfgTypeDef {
    HRPWM_EventSrcSelETypeDef Source;           /*!< Identifies the source of the external event.                                                   */
    HRPWM_EventPolETypeDef Polarity;            /*!< Specifies the polarity of the external event (in case of level sensitivity).                   */
    HRPWM_EventSensETypeDef Sensitivity;        /*!< Specifies the sensitivity of the external event.                                               */
    HRPWM_EventPrescalerETypeDef SampClockDiv;  /*!< External event sampling time frequency division ratio.                                         */
    HRPWM_EventFilterETypeDef Filter;           /*!< Defines the frequency used to sample the External Event and the length of the digital filter.  */
    HRPWM_EventFastModeETypeDef FastMode;       /*!< Indicates whether or not low latency mode is enabled for the external event.                   */
} HRPWM_EventCfgTypeDef;

/**
  * @brief  Fault channel configuration definition  -- common timer
  */
typedef struct __HRPWM_FaultCfgTypeDef {
    uint32_t InterruptEn;                       /*!< Relevant for comon timer.
                                                    Specifies which interrupts requests must enabled for comon timer.
                                                    This parameter can be any combination of @ref HRPWM_Common_Interrupt_Enable                 */
    HRPWM_FaultSrcSelETypeDef Source;           /*!< Identifies the source of the fault.                                                        */
    HRPWM_FaultPolETypeDef Polarity;            /*!< Specifies the polarity of the fault event.                                                 */
    HRPWM_FaultPrescalerETypeDef SampClockDiv;  /*!< Fault signal sampling time frequency division ratio.                                       */
    HRPWM_FaultFilterETypeDef Filter;           /*!< Defines the frequency used to sample the Fault input and the length of the digital filter. */
    HRPWM_FaultEnETypeDef Enable;               /*!< Corresponding fault sampling enablement.                                                   */
} HRPWM_FaultCfgTypeDef;

/**
  * @brief  Fault channel configuration blanking definition  -- common timer
  */
typedef struct __HRPWM_FaultBlankingCfgTypeDef {
    HRPWM_FaultCounterETypeDef Threshold;       /*!< Specifies the Fault counter Threshold.             */
    HRPWM_FaultBlkEnETypeDef BlankingEnable;    /*!< Specifies the Fault blanking enablement.           */
    HRPWM_FaultRstModeETypeDef ResetMode;       /*!< Specifies the reset mode of a fault event counter. */
    HRPWM_FaultBlkWindowETypeDef BlankingSource;/*!< Specifies the blanking source of a fault event.    */
} HRPWM_FaultBlankingCfgTypeDef;

/**
  * @brief  ADC trigger configuration definition -- common timer
  */
typedef struct __HRPWM_ADCTriggerCfgTypeDef {
    uint32_t Trigger;                           /*!< Specifies the event(s) triggering the ADC conversion.
                                                    This parameter can be a combination of @ref HRPWM_ADC_Trigger_Event        */
    HRPWM_AdcTrigGroupETypeDef TriggerGroup;    /*!< Specifies the ADC trigger group 0~7.                                      */
    HRPWM_AdcTrigUpdateSrcETypeDef UpdateSource;/*!< Specifies the ADC trigger update source.                                  */
    HRPWM_AdcTrigLengthETypeDef TriggerLength;  /*!< Specifies the event(s) triggering the ADC\DAC conversion.In practical use,
                                                     the length configuration should be greater than 3 clocks. For example, 
                                                     under a 160M clock, the minimum configuration value is 0x3;               */
    HRPWM_AdcTrigPSCETypeDef TriggerPostScaler; /*!< Specifies the event(s) triggering the ADC\DAC conversion.                 */
} HRPWM_ADCTriggerCfgTypeDef;

/**
  * @brief  HRPWM DLL start configuration definition -- common timer
  */
typedef struct __HRPWM_DLLCfgTypedef {
    HRPWM_DllCurrentETypeDef CurrentSel;/*!< Configure DLL current selection.                                                           */
    uint32_t ClockDelayThres0;          /*!< DLL Clock Delay Threshold. CLKPHASE = PULPHASE - DLLTHRES0. range : 0~0x1F                 */
    uint32_t ClockDelayThres1;          /*!< DLL Clock Delay Threshold. CLKPHASE <= DLLTHRES1 :
                                            Sample hrpwm_clk Pulse CLKPHASE >   DLLTHRES1 : Sample hrpwm_dly_clk Pulse. range : 0~0x1F  */
} HRPWM_DLLCfgTypedef;
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup HRPWM_LL_Exported_Macros HRPWM LL Exported Macros
  * @brief    HRPWM LL Exported Macros
  * @{
  */

/**
 * @brief  swap the output of the timer
 *         HRPWM_SETA1R and HRPWM_RSTAR are coding for the output B,
 *         HRPWM_SETA2R and HRPWM_RSTAR are coding for the output B
 * @note Push pull mode setting is invalid
 * @param  __TIMER__  : Timer index
 *                   This parameter can be a combination of the following values:
 *                   @arg HRPWM_SWAP_SLAVE_0
 *                   @arg HRPWM_SWAP_SLAVE_1
 *                   @arg HRPWM_SWAP_SLAVE_2
 *                   @arg HRPWM_SWAP_SLAVE_3
 *                   @arg HRPWM_SWAP_SLAVE_4
 *                   @arg HRPWM_SWAP_SLAVE_5
 * @retval none
 */
#define __LL_HRPWM_OUTPUT_SWAP(__TIMER__)           \
        MODIFY_REG(HRPWM->Common.CR1, HRPWM_CR1_SWP5 | HRPWM_CR1_SWP5 | HRPWM_CR1_SWP5 | HRPWM_CR1_SWP5 | HRPWM_CR1_SWP5, __TIMER__)

/**
 * @brief  swap the output of the timer
 *         HRPWM_SETAR and HRPWM_RSTAR are coding for the output B,
 *         HRPWM_SETAR and HRPWM_RSTAR are coding for the output B
 * @note Push pull mode setting is invalid
 * @param  __TIMER__  : Timer index
 *                   This parameter Only one of the values can be selected, not a combination:
 *                   @arg HRPWM_SWAP_SLAVE_0
 *                   @arg HRPWM_SWAP_SLAVE_1
 *                   @arg HRPWM_SWAP_SLAVE_2
 *                   @arg HRPWM_SWAP_SLAVE_3
 *                   @arg HRPWM_SWAP_SLAVE_4
 *                   @arg HRPWM_SWAP_SLAVE_5
 * @retval none
 */
#define __LL_HRPWM_TIMER_OUTPUT_SWAP(__TIMER__)     SET_BIT(HRPWM->Common.CR1, __TIMER__)

/**
 * @brief  Un-swap the output of the timer
 *         HRPWM_SETAR and HRPWM_RSTAR are coding for the output A,
 *         HRPWM_SETAR and HRPWM_RSTAR are coding for the output A
 * @note Push pull mode setting is invalid
 * @param  __TIMER__  : Timer index
 *                   This parameter Only one of the values can be selected, not a combination:
 *                   @arg HRPWM_SWAP_SLAVE_0
 *                   @arg HRPWM_SWAP_SLAVE_1
 *                   @arg HRPWM_SWAP_SLAVE_2
 *                   @arg HRPWM_SWAP_SLAVE_3
 *                   @arg HRPWM_SWAP_SLAVE_4
 *                   @arg HRPWM_SWAP_SLAVE_5
 * @retval none
 */
#define __LL_HRPWM_TIMER_OUTPUT_NOSWAP(__TIMER__)   CLEAR_BIT(HRPWM->Common.CR1, __TIMER__)

/** @brief  Enables or disables the specified HRPWM common interrupts.
  * @param  __INTERRUPT__ specifies the interrupt source to enable or disable.
  *        This parameter can be one of the following values:
  *            @arg HRPWM_IT_FLT0: Fault 0 interrupt enable
  *            @arg HRPWM_IT_FLT1: Fault 1 interrupt enable
  *            @arg HRPWM_IT_FLT2: Fault 2 interrupt enable
  *            @arg HRPWM_IT_FLT3: Fault 3 interrupt enable
  *            @arg HRPWM_IT_FLT4: Fault 4 interrupt enable
  *            @arg HRPWM_IT_FLT5: Fault 5 interrupt enable
  *            @arg HRPWM_IT_SYSFLT: System Fault interrupt enable
  * @retval None
  */
#define __LL_HRPWM_ENABLE_IT(__INTERRUPT__)         (HRPWM->Common.IER |= (__INTERRUPT__))
#define __LL_HRPWM_DISABLE_IT(__INTERRUPT__)        (HRPWM->Common.IER &= ~(__INTERRUPT__))

/** @brief  Enables or disables the specified HRPWM Master timer interrupts.
  * @param  __INTERRUPT__ specifies the interrupt source to enable or disable.
  *        This parameter can be one of the following values:
  *            @arg HRPWM_MASTER_IT_MPER: Master Period interrupt enable
  *            @arg HRPWM_MASTER_IT_MCMPA: Master compare A interrupt enable
  *            @arg HRPWM_MASTER_IT_MCMPB: Master compare B interrupt enable
  *            @arg HRPWM_MASTER_IT_MCMPC: Master compare C interrupt enable
  *            @arg HRPWM_MASTER_IT_MCMPD: Master compare D interrupt enable
  *            @arg HRPWM_MASTER_IT_MREP: Master Repetition interrupt enable
  *            @arg HRPWM_MASTER_IT_SYNC: Synchronization input interrupt enable
  *            @arg HRPWM_MASTER_IT_MUPD: Master update interrupt enable
  * @retval None
  */
#define __LL_HRPWM_MASTER_ENABLE_IT(__INTERRUPT__)      (HRPWM->Master.MIER |= (__INTERRUPT__))
#define __LL_HRPWM_MASTER_DISABLE_IT(__INTERRUPT__)     (HRPWM->Master.MIER &= ~(__INTERRUPT__))

/** @brief  Enables or disables the specified HRPWM Timerx interrupts.
  * @param  __TIMER__ specified the timing unit (Timer 0 to 5)
  * @param  __INTERRUPT__ specifies the interrupt source to enable or disable.
  *        This parameter can be one of the following values:
  *            @arg HRPWM_IT_PER: Timer Period interrupt enable
  *            @arg HRPWM_IT_CMPA: Timer compare 1 interrupt enable
  *            @arg HRPWM_IT_CMP2: Timer compare 2 interrupt enable
  *            @arg HRPWM_IT_CMP3: Timer compare 3 interrupt enable
  *            @arg HRPWM_IT_CMP4: Timer compare 4 interrupt enable
  *            @arg HRPWM_IT_SETA: Timer output 1 set interrupt enable
  *            @arg HRPWM_IT_RSTA: Timer output 1 reset interrupt enable
  *            @arg HRPWM_IT_SETB: Timer output 2 set interrupt enable
  *            @arg HRPWM_IT_RSTB: Timer output 2 reset interrupt enable
  *            @arg HRPWM_IT_RST: Timer reset interrupt enable
  *            @arg HRPWM_IT_REP: Timer repetition interrupt enable
  *            @arg HRPWM_IT_UPD: Timer update interrupt enable
  *            @arg HRPWM_IT_DLYPRT: Timer delay protection interrupt enable
  * @retval None
  */
#define __LL_HRPWM_TIMER_ENABLE_IT(__TIMER__, __INTERRUPT__)    (HRPWM->PWM[(__TIMER__)].IER |= (__INTERRUPT__))
#define __LL_HRPWM_TIMER_DISABLE_IT(__TIMER__, __INTERRUPT__)   (HRPWM->PWM[(__TIMER__)].IER &= ~(__INTERRUPT__))

/** @brief  Checks if the specified HRPWM common interrupt  source  is enabled or disabled.
  * @param  __INTERRUPT__ specifies the interrupt source to check.
  * @param  __INTERRUPT__ specifies the interrupt source to enable or disable.
  *        This parameter can be one of the following values:
  *            @arg HRPWM_IT_FLT0: Fault 0 interrupt enable
  *            @arg HRPWM_IT_FLT1: Fault 1 interrupt enable
  *            @arg HRPWM_IT_FLT2: Fault 2 interrupt enable
  *            @arg HRPWM_IT_FLT3: Fault 3 interrupt enable
  *            @arg HRPWM_IT_FLT4: Fault 4 interrupt enable
  *            @arg HRPWM_IT_FLT5: Fault 5 interrupt enable
  *            @arg HRPWM_IT_SYSFLT: System Fault interrupt enable
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __LL_HRPWM_GET_IT(__INTERRUPT__)            (((HRPWM->Common.IER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Checks if the specified HRPWM Master interrupt source  is enabled or disabled.
  * @param  __INTERRUPT__ specifies the interrupt source to check.
  *        This parameter can be one of the following values:
  *            @arg HRPWM_MASTER_IT_MPER: Master Period interrupt enable
  *            @arg HRPWM_MASTER_IT_MCMPA: Master compare A interrupt enable
  *            @arg HRPWM_MASTER_IT_MCMPB: Master compare B interrupt enable
  *            @arg HRPWM_MASTER_IT_MCMPC: Master compare C interrupt enable
  *            @arg HRPWM_MASTER_IT_MCMPD: Master compare D interrupt enable
  *            @arg HRPWM_MASTER_IT_MREP: Master Repetition interrupt enable
  *            @arg HRPWM_MASTER_IT_SYNC: Synchronization input interrupt enable
  *            @arg HRPWM_MASTER_IT_MUPD: Master update interrupt enable
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __LL_HRPWM_MASTER_GET_IT(__INTERRUPT__)     (((HRPWM->Master.MIER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Checks if the specified HRPWM Timerx interrupt source  is enabled or disabled.
  * @param  __TIMER__ specified the timing unit (Timer 0 to 5)
  * @param  __INTERRUPT__ specifies the interrupt source to enable or disable.
  *        This parameter can be one of the following values:
  *            @arg HRPWM_IT_PER: Timer Period interrupt enable
  *            @arg HRPWM_IT_CMPA: Timer compare A interrupt enable
  *            @arg HRPWM_IT_CMPB: Timer compare B interrupt enable
  *            @arg HRPWM_IT_CMPC: Timer compare C interrupt enable
  *            @arg HRPWM_IT_CMPD: Timer compare D interrupt enable
  *            @arg HRPWM_IT_SETA: Timer output A set interrupt enable
  *            @arg HRPWM_IT_RSTA: Timer output A reset interrupt enable
  *            @arg HRPWM_IT_SETB: Timer output B set interrupt enable
  *            @arg HRPWM_IT_RSTB: Timer output B reset interrupt enable
  *            @arg HRPWM_IT_RST: Timer reset interrupt enable
  *            @arg HRPWM_IT_REP: Timer repetition interrupt enable
  *            @arg HRPWM_IT_UPD: Timer update interrupt enable
  *            @arg HRPWM_IT_DLYPRT: Timer delay protection interrupt enable
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __LL_HRPWM_TIMER_GET_IT(__TIMER__, __INTERRUPT__)   \
    (((HRPWM->PWM[(__TIMER__)].IER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Get the specified HRPWM common pending flag.
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *        This parameter can be one of the following values:
  *            @arg HRPWM_FLAG_FLT0: Fault 0 flag
  *            @arg HRPWM_FLAG_FLT1: Fault 1 flag
  *            @arg HRPWM_FLAG_FLT2: Fault 2 flag
  *            @arg HRPWM_FLAG_FLT3: Fault 3 flag
  *            @arg HRPWM_FLAG_FLT4: Fault 4 flag
  *            @arg HRPWM_FLAG_FLT5: Fault 5 flag
  *            @arg HRPWM_FLAG_SYSFLT: System Fault interrupt flag
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __LL_HRPWM_GET_ITFLAG(__INTERRUPT__)    (((HRPWM->Common.ISR & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Get the specified HRPWM Master pending flag.
  * @param  __INTERRUPT__ specifies the interrupt pending bit.
  *        This parameter can be one of the following values:
  *            @arg HRPWM_MASTER_FLAG_MPER: Master Period interrupt flag
  *            @arg HRPWM_MASTER_FLAG_MCMPA: Master compare A interrupt flag
  *            @arg HRPWM_MASTER_FLAG_MCMPB: Master compare B interrupt flag
  *            @arg HRPWM_MASTER_FLAG_MCMPC: Master compare C interrupt flag
  *            @arg HRPWM_MASTER_FLAG_MCMPD: Master compare D interrupt flag
  *            @arg HRPWM_MASTER_FLAG_MREP: Master Repetition interrupt flag
  *            @arg HRPWM_MASTER_FLAG_SYNC: Synchronization input interrupt flag
  *            @arg HRPWM_MASTER_FLAG_MUPD: Master update interrupt flag
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __LL_HRPWM_MASTER_GET_ITFLAG(__INTERRUPT__)     \
        (((HRPWM->Master.MISR & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Get the specified HRPWM Timerx pending flag.
  * @param  __TIMER__ specified the timing unit (Timer 0 to 5)
  * @param  __INTERRUPT__ specifies the interrupt pending bit.
  *        This parameter can be one of the following values:
  *            @arg HRPWM_FLAG_PER: Timer Period interrupt flag
  *            @arg HRPWM_FLAG_CMPA: Timer compare A interrupt flag
  *            @arg HRPWM_FLAG_CMPB: Timer compare B interrupt flag
  *            @arg HRPWM_FLAG_CMPC: Timer compare C interrupt flag
  *            @arg HRPWM_FLAG_CMPD: Timer compare D interrupt flag
  *            @arg HRPWM_FLAG_SETA: Timer output A set interrupt flag
  *            @arg HRPWM_FLAG_RSTA: Timer output A reset interrupt flag
  *            @arg HRPWM_FLAG_SETB: Timer output B set interrupt flag
  *            @arg HRPWM_FLAG_RSTB: Timer output B reset interrupt flag
  *            @arg HRPWM_FLAG_RST: Timer reset interrupt flag
  *            @arg HRPWM_FLAG_REP: Timer repetition interrupt flag
  *            @arg HRPWM_FLAG_UPD: Timer update interrupt flag
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __LL_HRPWM_TIMER_GET_ITFLAG(__TIMER__, __INTERRUPT__)       \
        (((HRPWM->PWM[(__TIMER__)].ISR & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)


/** @brief  Clears the specified HRPWM common pending flag.
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *        This parameter can be one of the following values:
  *            @arg HRPWM_FLAG_FLT0: Fault 0 clear flag
  *            @arg HRPWM_FLAG_FLT1: Fault 1 clear flag
  *            @arg HRPWM_FLAG_FLT2: Fault 2 clear flag
  *            @arg HRPWM_FLAG_FLT3: Fault 3 clear flag
  *            @arg HRPWM_FLAG_FLT4: Fault 4 clear flag
  *            @arg HRPWM_FLAG_FLT5: Fault 5 clear flag
  *            @arg HRPWM_FLAG_SYSFLT: System Fault interrupt clear flag
  * @retval None
  */
#define __LL_HRPWM_CLEAR_ITFLAG(__INTERRUPT__)          (HRPWM->Common.ISR = (__INTERRUPT__))

/** @brief  Clears the specified HRPWM Master pending flag.
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *        This parameter can be one of the following values:
  *            @arg HRPWM_MASTER_FLAG_MPER: Master Period interrupt clear flag
  *            @arg HRPWM_MASTER_FLAG_MCMPA: Master compare A interrupt clear flag
  *            @arg HRPWM_MASTER_FLAG_MCMPB: Master compare B interrupt clear flag
  *            @arg HRPWM_MASTER_FLAG_MCMPC: Master compare C interrupt clear flag
  *            @arg HRPWM_MASTER_FLAG_MCMPD: Master compare D interrupt clear flag
  *            @arg HRPWM_MASTER_FLAG_MREP: Master Repetition interrupt clear flag
  *            @arg HRPWM_MASTER_FLAG_SYNC: Synchronization input interrupt clear flag
  *            @arg HRPWM_MASTER_FLAG_MUPD: Master update interrupt clear flag
  * @retval None
  */
#define __LL_HRPWM_MASTER_CLEAR_ITFLAG(__INTERRUPT__)   (HRPWM->Master.MISR = (__INTERRUPT__))

/** @brief  Clears the specified HRPWM Timerx pending flag.
  * @param  __TIMER__ specified the timing unit (Timer A to F)
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *        This parameter can be one of the following values:
  *            @arg HRPWM_FLAG_PER: Timer Period interrupt clear flag
  *            @arg HRPWM_FLAG_CMPA: Timer compare A interrupt clear flag
  *            @arg HRPWM_FLAG_CMPB: Timer compare B interrupt clear flag
  *            @arg HRPWM_FLAG_CMPC: Timer compare C interrupt clear flag
  *            @arg HRPWM_FLAG_CMPD: Timer compare D interrupt clear flag
  *            @arg HRPWM_FLAG_SETA: Timer output A set interrupt clear flag
  *            @arg HRPWM_FLAG_RSTA: Timer output A reset interrupt clear flag
  *            @arg HRPWM_FLAG_SETB: Timer output B set interrupt clear flag
  *            @arg HRPWM_FLAG_RSTB: Timer output B reset interrupt clear flag
  *            @arg HRPWM_FLAG_RST: Timer reset interrupt clear flag
  *            @arg HRPWM_FLAG_REP: Timer repetition interrupt clear flag
  *            @arg HRPWM_FLAG_UPD: Timer update interrupt clear flag
  * @retval None
  */
#define __LL_HRPWM_TIMER_CLEAR_ITFLAG(__TIMER__, __INTERRUPT__)     (HRPWM->PWM[(__TIMER__)].ISR = (__INTERRUPT__))

/** @brief  Sets the HRPWM timer Period value on runtime
  * @param  __TIMER__ HRPWM timer
  *        This parameter can be one of the following values:
  *            @arg HRPWM_INDEX_MASTER: Master timer identifier
  *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
  *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
  *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
  *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
  *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
  *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @param  __PERIOD__ specifies the Period Register new value.
  * @retval None
  */
#define __LL_HRPWM_SETPERIOD(__TIMER__, __PERIOD__)                                  \
        (((__TIMER__) == HRPWM_INDEX_MASTER) ? (HRPWM->Master.MPER = (__PERIOD__)) :\
        (HRPWM->PWM[(__TIMER__)].PERR = (__PERIOD__)))

/** @brief  Gets the HRPWM timer Period Register value on runtime
  * @param  __TIMER__ HRPWM timer
  *        This parameter can be one of the following values:
  *            @arg HRPWM_INDEX_MASTER: Master timer identifier
  *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
  *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
  *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
  *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
  *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
  *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @retval timer Period Register
  */
#define __LL_HRPWM_GETPERIOD(__TIMER__)     \
        (((__TIMER__) == HRPWM_INDEX_MASTER) ? (HRPWM->Master.MPER) : (HRPWM->PWM[(__TIMER__)].PERR))


/** @brief  Sets the HRPWM timer clock prescaler value on runtime
  * @param  __TIMER__ HRPWM timer
  *        This parameter can be one of the following values:
  *            @arg HRPWM_INDEX_MASTER: Master timer identifier
  *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
  *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
  *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
  *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
  *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
  *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @param  __PRESCALER__ specifies the clock prescaler new value.
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_PRESCALERRATIO_MUL32: fHRCK: fHRPWM x 32U = 5.12 GHz - Resolution: 195 ps (fHRPWM=144MHz)
  *                   @arg HRPWM_PRESCALERRATIO_MUL16: fHRCK: fHRPWM x 16U = 2.56 GHz - Resolution: 390 ps (fHRPWM=144MHz)
  *                   @arg HRPWM_PRESCALERRATIO_MUL8:  fHRCK: fHRPWM x 8U = 1.28 GHz - Resolution: 781 ps  (fHRPWM=144MHz)
  *                   @arg HRPWM_PRESCALERRATIO_MUL4:  fHRCK: fHRPWM x 4U = 640 MHz - Resolution: 1.56 ns  (fHRPWM=144MHz)
  *                   @arg HRPWM_PRESCALERRATIO_MUL2:  fHRCK: fHRPWM x 2U = 320 MHz - Resolution: 3.125 ns (fHRPWM=144MHz)
  *                   @arg HRPWM_PRESCALERRATIO_DIV1:  fHRCK: fHRPWM = 160 MHz - Resolution: 6.25 ns       (fHRPWM=144MHz)
  *                   @arg HRPWM_PRESCALERRATIO_DIV2:  fHRCK: fHRPWM / 2U = 80 MHz - Resolution: 12.5 ns   (fHRPWM=144MHz)
  *                   @arg HRPWM_PRESCALERRATIO_DIV4:  fHRCK: fHRPWM / 4U = 40 MHz - Resolution: 25 ns     (fHRPWM=144MHz)
  * @retval None
  */
#define __LL_HRPWM_SETCLOCKPRESCALER(__TIMER__, __PRESCALER__)                                                  \
    (((__TIMER__) == HRPWM_INDEX_MASTER) ? (MODIFY_REG(HRPWM->Master.MCR, HRPWM_MCR_CKPSC, (__PRESCALER__))) :\
     (MODIFY_REG(HRPWM->PWM[(__TIMER__)].CR0, HRPWM_CR0_CKPSC, (__PRESCALER__))))

/** @brief  Gets the HRPWM timer clock prescaler value on runtime
  * @param  __TIMER__ HRPWM timer
  *        This parameter can be one of the following values:
  *            @arg HRPWM_INDEX_MASTER: Master timer identifier
  *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
  *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
  *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
  *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
  *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
  *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @retval timer clock prescaler value
  */
#define __LL_HRPWM_GETCLOCKPRESCALER(__TIMER__)                                     \
    (((__TIMER__) == HRPWM_INDEX_MASTER) ? (HRPWM->Master.MCR & HRPWM_MCR_CKPSC) : \
     (HRPWM->PWM[(__TIMER__)].CR0 & HRPWM_CR0_CKPSC))

/** @brief  Sets the HRPWM timer Compare Register value on runtime
  * @param  __TIMER__ HRPWM timer (not is commmon timer)
  *        This parameter can be one of the following values:
  *            @arg HRPWM_INDEX_MASTER: Master timer identifier
  *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
  *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
  *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
  *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
  *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
  *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @param  __COMPAREUNIT__ timer compare unit
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_COMPAREUNIT_A: Compare A
  *                   @arg HRPWM_COMPAREUNIT_B: Compare B
  *                   @arg HRPWM_COMPAREUNIT_C: Compare C
  *                   @arg HRPWM_COMPAREUNIT_D: Compare D
  * @param  __COMPARE__ specifies the Compare new value.
  * @retval None
  */
#define __LL_HRPWM_SETCOMPARE(__TIMER__, __COMPAREUNIT__, __COMPARE__)                                  \
    (((__TIMER__) == HRPWM_INDEX_MASTER) ?                                                              \
     (((__COMPAREUNIT__) == HRPWM_COMPAREUNIT_A) ? (HRPWM->Master.MCMPAR = (__COMPARE__)) :             \
      ((__COMPAREUNIT__) == HRPWM_COMPAREUNIT_B) ? (HRPWM->Master.MCMPBR = (__COMPARE__)) :             \
      ((__COMPAREUNIT__) == HRPWM_COMPAREUNIT_C) ? (HRPWM->Master.MCMPCR = (__COMPARE__)) :             \
      (HRPWM->Master.MCMPDR = (__COMPARE__)))                                                           \
     :                                                                                                  \
     (((__COMPAREUNIT__) == HRPWM_COMPAREUNIT_A) ? (HRPWM->PWM[(__TIMER__)].CMPAR = (__COMPARE__)) :   \
      ((__COMPAREUNIT__) == HRPWM_COMPAREUNIT_B) ? (HRPWM->PWM[(__TIMER__)].CMPBR = (__COMPARE__)) :    \
      ((__COMPAREUNIT__) == HRPWM_COMPAREUNIT_C) ? (HRPWM->PWM[(__TIMER__)].CMPCR = (__COMPARE__)) :    \
      (HRPWM->PWM[(__TIMER__)].CMPDR = (__COMPARE__))))

/** @brief  Gets the HRPWM timer Compare Register value on runtime
  * @param  __TIMER__ HRPWM timer (not is commmon timer)
  *        This parameter can be one of the following values:
  *            @arg HRPWM_INDEX_MASTER: Master timer identifier
  *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
  *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
  *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
  *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
  *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
  *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @param  __COMPAREUNIT__ timer compare unit
  *                   This parameter can be one of the following values:
  *                   @arg HRPWM_COMPAREUNIT_A: Compare A
  *                   @arg HRPWM_COMPAREUNIT_B: Compare B
  *                   @arg HRPWM_COMPAREUNIT_C: Compare C
  *                   @arg HRPWM_COMPAREUNIT_D: Compare D
  * @retval Compare value
  */
#define __LL_HRPWM_GETCOMPARE(__TIMER__, __COMPAREUNIT__)                               \
    (((__TIMER__) == HRPWM_INDEX_MASTER) ?                                              \
     (((__COMPAREUNIT__) == HRPWM_COMPAREUNIT_A) ? (HRPWM->Master.MCMPAR) :             \
      ((__COMPAREUNIT__) == HRPWM_COMPAREUNIT_B) ? (HRPWM->Master.MCMPBR) :             \
      ((__COMPAREUNIT__) == HRPWM_COMPAREUNIT_C) ? (HRPWM->Master.MCMPCR) :             \
      (HRPWM->Master.MCMPDR))                                                           \
     :                                                                                  \
     (((__COMPAREUNIT__) == HRPWM_COMPAREUNIT_A) ? (HRPWM->PWM[(__TIMER__)].CMPAR) :   \
      ((__COMPAREUNIT__) == HRPWM_COMPAREUNIT_B) ? (HRPWM->PWM[(__TIMER__)].CMPBR) :    \
      ((__COMPAREUNIT__) == HRPWM_COMPAREUNIT_C) ? (HRPWM->PWM[(__TIMER__)].CMPCR) :    \
      (HRPWM->PWM[(__TIMER__)].CMPDR)))

/** @brief  Sets the HRPWM timer Compare A Register value on runtime
  * @param  __TIMER__ HRPWM timer (not is commmon timer)
  *        This parameter can be one of the following values:
  *            @arg HRPWM_INDEX_MASTER: Master timer identifier
  *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
  *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
  *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
  *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
  *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
  *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @param  __VALUE__ specifies the Compare new value.
  * @retval None
  */
#define __LL_HRPWM_SETCOMPARE_A(__TINER__, __VALUE__)                               \
    (((__TINER__) == HRPWM_INDEX_MASTER) ? (HRPWM->Master.MCMPAR = (__VALUE__)) :  \
     (HRPWM->PWM[(__TINER__)].CMPAR = (__VALUE__)))

/** @brief  Sets the HRPWM timer Compare B Register value on runtime
  * @param  __TIMER__ HRPWM timer (not is commmon timer)
  *        This parameter can be one of the following values:
  *            @arg HRPWM_INDEX_MASTER: Master timer identifier
  *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
  *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
  *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
  *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
  *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
  *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @param  __VALUE__ specifies the Compare new value.
  * @retval None
  */
#define __LL_HRPWM_SETCOMPARE_B(__TINER__, __VALUE__)                              \
    (((__TINER__) == HRPWM_INDEX_MASTER) ? (HRPWM->Master.MCMPBR = (__VALUE__)) : \
     (HRPWM->PWM[(__TINER__)].CMPBR = (__VALUE__)))

/** @brief  Sets the HRPWM timer Compare C Register value on runtime
  * @param  __TIMER__ HRPWM timer (not is commmon timer)
  *        This parameter can be one of the following values:
  *            @arg HRPWM_INDEX_MASTER: Master timer identifier
  *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
  *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
  *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
  *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
  *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
  *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @param  __VALUE__ specifies the Compare new value.
  * @retval None
  */
#define __LL_HRPWM_SETCOMPARE_C(__TINER__, __VALUE__)                              \
    (((__TINER__) == HRPWM_INDEX_MASTER) ? (HRPWM->Master.MCMPCR = (__VALUE__)) : \
     (HRPWM->PWM[(__TINER__)].CMPCR = (__VALUE__)))

/** @brief  Sets the HRPWM timer Compare A Register value on runtime
  * @param  __TIMER__ HRPWM timer (not is commmon timer)
    *        This parameter can be one of the following values:
    *            @arg HRPWM_INDEX_MASTER: Master timer identifier
    *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
    *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
    *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
    *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
    *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
    *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @param  __VALUE__ specifies the Compare new value.
  * @retval None
  */
#define __LL_HRPWM_SETCOMPARE_D(__TINER__, __VALUE__)                              \
    (((__TINER__) == HRPWM_INDEX_MASTER) ? (HRPWM->Master.MCMPDR = (__VALUE__)) : \
     (HRPWM->PWM[(__TINER__)].CMPDR = (__VALUE__)))


/** @brief  Gets the HRPWM timer Compare A Register value on runtime
  * @param  __TIMER__ HRPWM timer (not is commmon timer)
    *        This parameter can be one of the following values:
    *            @arg HRPWM_INDEX_MASTER: Master timer identifier
    *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
    *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
    *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
    *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
    *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
    *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @retval Compare value
  */

#define __LL_HRPWM_GETCOMPARE_A(__TINER__)  \
        (((__TINER__) == HRPWM_INDEX_MASTER) ? (HRPWM->Master.MCMPAR) :(HRPWM->PWM[(__TINER__)].CMPAR))

/** @brief  Gets the HRPWM timer Compare B Register value on runtime
  * @param  __TIMER__ HRPWM timer (not is commmon timer)
    *        This parameter can be one of the following values:
    *            @arg HRPWM_INDEX_MASTER: Master timer identifier
    *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
    *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
    *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
    *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
    *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
    *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @retval Compare value
  */

#define __LL_HRPWM_GETCOMPARE_B(__TINER__)  \
        (((__TINER__) == HRPWM_INDEX_MASTER) ? (HRPWM->Master.MCMPBR) : (HRPWM->PWM[(__TINER__)].CMPBR))

/** @brief  Gets the HRPWM timer Compare C Register value on runtime
  * @param  __TIMER__ HRPWM timer (not is commmon timer)
    *        This parameter can be one of the following values:
    *            @arg HRPWM_INDEX_MASTER: Master timer identifier
    *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
    *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
    *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
    *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
    *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
    *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @retval Compare value
  */

#define __LL_HRPWM_GETCOMPARE_C(__TINER__)  \
        (((__TINER__) == HRPWM_INDEX_MASTER) ? (HRPWM->Master.MCMPCR) : (HRPWM->PWM[(__TINER__)].CMPCR))

/** @brief  Gets the HRPWM timer Compare D Register value on runtime
  * @param  __TIMER__ HRPWM timer (not is commmon timer)
    *        This parameter can be one of the following values:
    *            @arg HRPWM_INDEX_MASTER: Master timer identifier
    *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
    *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
    *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
    *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
    *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
    *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
  * @retval Compare value
  */

#define __LL_HRPWM_GETCOMPARE_D(__TINER__)  \
        (((__TINER__) == HRPWM_INDEX_MASTER) ? (HRPWM->Master.MCMPDR) : (HRPWM->PWM[(__TINER__)].CMPDR))


/** @brief  Enables or disables the timer counter(s)
 * @param  __TIMERS__ timers to enable/disable
 *        This parameter can be any combinations of the following values:
 *            @arg HRPWM_INDEX_MASTER: Master timer identifier
 *            @arg HRPWM_INDEX_SLAVE_0: Slave pwm 0 identifier
 *            @arg HRPWM_INDEX_SLAVE_1: Slave pwm 1 identifier
 *            @arg HRPWM_INDEX_SLAVE_2: Slave pwm 2 identifier
 *            @arg HRPWM_INDEX_SLAVE_3: Slave pwm 3 identifier
 *            @arg HRPWM_INDEX_SLAVE_4: Slave pwm 4 identifier
 *            @arg HRPWM_INDEX_SLAVE_5: Slave pwm 5 identifier
 * @retval None
 */
#define __LL_HRPWM_TIMER_ENABLE(__TIMERS__)                                          \
    (((__TIMERS__) == HRPWM_INDEX_MASTER) ?  (HRPWM->Master.MCR |= HRPWM_MCR_MCEN) : \
     ((__TIMERS__) == HRPWM_INDEX_SLAVE_0) ? (HRPWM->Master.MCR |= HRPWM_MCR_CEN0) : \
     ((__TIMERS__) == HRPWM_INDEX_SLAVE_1) ? (HRPWM->Master.MCR |= HRPWM_MCR_CEN1) : \
     ((__TIMERS__) == HRPWM_INDEX_SLAVE_2) ? (HRPWM->Master.MCR |= HRPWM_MCR_CEN2) : \
     ((__TIMERS__) == HRPWM_INDEX_SLAVE_3) ? (HRPWM->Master.MCR |= HRPWM_MCR_CEN3) : \
     ((__TIMERS__) == HRPWM_INDEX_SLAVE_4) ? (HRPWM->Master.MCR |= HRPWM_MCR_CEN4) : \
     ((HRPWM->Master.MCR |= HRPWM_MCR_CEN5)))


#define __LL_HRPWM_TIMER_DISABLE(__TIMERS__)   \
    (((__TIMERS__) == HRPWM_INDEX_MASTER) ?  (HRPWM->Master.MCR &= ~(HRPWM_MCR_MCEN)) : \
     ((__TIMERS__) == HRPWM_INDEX_SLAVE_0) ? (HRPWM->Master.MCR &= ~(HRPWM_MCR_CEN0)) : \
     ((__TIMERS__) == HRPWM_INDEX_SLAVE_1) ? (HRPWM->Master.MCR &= ~(HRPWM_MCR_CEN1)) : \
     ((__TIMERS__) == HRPWM_INDEX_SLAVE_2) ? (HRPWM->Master.MCR &= ~(HRPWM_MCR_CEN2)) : \
     ((__TIMERS__) == HRPWM_INDEX_SLAVE_3) ? (HRPWM->Master.MCR &= ~(HRPWM_MCR_CEN3)) : \
     ((__TIMERS__) == HRPWM_INDEX_SLAVE_4) ? (HRPWM->Master.MCR &= ~(HRPWM_MCR_CEN4)) : \
     ((HRPWM->Master.MCR &= ~(HRPWM_MCR_CEN5))))

/** @brief  Enables ALL the timer counter(s)
 * @param  __INSTANCE__ HRPWM HANDLE
 * @retval None
 */
#define __LL_HRPWM_ALL_TIMER_ENABLE(__INSTANCE__)       \
    (SET_BIT((__INSTANCE__)->Master.MCR,                \
    HRPWM_MCR_MCEN | HRPWM_MCR_CEN0 | HRPWM_MCR_CEN1 | HRPWM_MCR_CEN2 | HRPWM_MCR_CEN3 | HRPWM_MCR_CEN4 | HRPWM_MCR_CEN5))

/** @brief  Disables the timer counter(s)
 * @param  __INSTANCE__ HRPWM HANDLE
 * @retval None
 */
#define __LL_HRPWM_ALL_TIMER_DISABLE(__INSTANCE__)      \
    (CLEAR_BIT((__INSTANCE__)->Master.MCR,              \
    HRPWM_MCR_MCEN | HRPWM_MCR_CEN0 | HRPWM_MCR_CEN1 | HRPWM_MCR_CEN2 | HRPWM_MCR_CEN3 | HRPWM_MCR_CEN4 | HRPWM_MCR_CEN5))


/** @brief  Modify the length of the dead zone
  * @param  __TIMERS__ timers to enable/disable
  *        This parameter can be any combinations of the following values:
  *            @arg HRPWM_INDEX_MASTER: Master timer identifier
  *            @arg HRPWM_INDEX_SLAVE_0: Timer 0 identifier
  *            @arg HRPWM_INDEX_SLAVE_1: Timer 1 identifier
  *            @arg HRPWM_INDEX_SLAVE_2: Timer 2 identifier
  *            @arg HRPWM_INDEX_SLAVE_3: Timer 3 identifier
  *            @arg HRPWM_INDEX_SLAVE_4: Timer 4 identifier
  *            @arg HRPWM_INDEX_SLAVE_5: Timer 5 identifier
  * @param  __VALUES__ timer dead timer value the range of value is 0 ~ 0xfff
  * @retval None
  */
#define __LL_HRPWM_DEADTIME_RISE_VALUE(__TIMERS__, __VALUES__)   \
        MODIFY_REG(HRPWM->PWM[__TIMERS__].DTR, HRPWM_DTR_DTR, (__VALUES__))

#define __LL_HRPWM_DEADTIME_FALL_VALUE(__TIMERS__, __VALUES__)   \
        MODIFY_REG(HRPWM->PWM[__TIMERS__].DTR, HRPWM_DTR_DTF, ((__VALUES__) << 16U))

/** @brief  Modify the length of the dead zone
  * @param  __TIMERS__ timers to enable/disable
  *        This parameter can be any combinations of the following values:
  *            @arg HRPWM_INDEX_MASTER: Master timer identifier
  *            @arg HRPWM_INDEX_SLAVE_0: Timer 0 identifier
  *            @arg HRPWM_INDEX_SLAVE_1: Timer 1 identifier
  *            @arg HRPWM_INDEX_SLAVE_2: Timer 2 identifier
  *            @arg HRPWM_INDEX_SLAVE_3: Timer 3 identifier
  *            @arg HRPWM_INDEX_SLAVE_4: Timer 4 identifier
  *            @arg HRPWM_INDEX_SLAVE_5: Timer 5 identifier
  * @param  __SIGN__ timer dead timer sign
  *                  HRPWM_Deadtime_Rising_Sign:  HRPWM_DEADTIME_RSIGN_NEGATIVE \ HRPWM_DEADTIME_RSIGN_POSITIVE
  *                  HRPWM_Deadtime_Falling_Sign: HRPWM_DEADTIME_FSIGN_NEGATIVE \ HRPWM_DEADTIME_FSIGN_POSITIVE
  * @retval None
  */
#define __LL_HRPWM_DEADTIME_RISE_SIGN(__TIMERS__, __SIGN__)   MODIFY_REG(HRPWM->PWM[__TIMERS__].DTR, HRPWM_DTR_SDTR, (__SIGN__))

#define __LL_HRPWM_DEADTIME_FALL_SIGN(__TIMERS__, __SIGN__)   MODIFY_REG(HRPWM->PWM[__TIMERS__].DTR, HRPWM_DTR_SDTF, (__SIGN__))


/** @brief  Start output wave
  * @param  __OUTPUT__ timers start output wave @ HRPWM_Timer_Output_Start
  *        This parameter can be any combinations of the following values:
  *        @arg HRPWM_OUTPUT_OEN0A
  *        @arg HRPWM_OUTPUT_OEN0B
  *        @arg HRPWM_OUTPUT_OEN1A
  *        @arg HRPWM_OUTPUT_OEN1B
  *        @arg HRPWM_OUTPUT_OEN2A
  *        @arg HRPWM_OUTPUT_OEN2B
  *        @arg HRPWM_OUTPUT_OEN3A
  *        @arg HRPWM_OUTPUT_OEN3B
  *        @arg HRPWM_OUTPUT_OEN4A
  *        @arg HRPWM_OUTPUT_OEN4B
  *        @arg HRPWM_OUTPUT_OEN5A
  *        @arg HRPWM_OUTPUT_OEN5B
  * @retval None
  */
#define __LL_HRPWM_OUTPUT_START(__OUTPUT__)    SET_BIT(HRPWM->Common.OENR, (__OUTPUT__))

/** @brief  Stop output wave
  * @param  __OUTPUT__ timers start output wave @ HRPWM_Timer_Output_Stop
  *        This parameter can be any combinations of the following values:
  *        @arg HRPWM_OUTPUT_ODIS0A
  *        @arg HRPWM_OUTPUT_ODIS0B
  *        @arg HRPWM_OUTPUT_ODIS1A
  *        @arg HRPWM_OUTPUT_ODIS1B
  *        @arg HRPWM_OUTPUT_ODIS2A
  *        @arg HRPWM_OUTPUT_ODIS2B
  *        @arg HRPWM_OUTPUT_ODIS3A
  *        @arg HRPWM_OUTPUT_ODIS3B
  *        @arg HRPWM_OUTPUT_ODIS4A
  *        @arg HRPWM_OUTPUT_ODIS4B
  *        @arg HRPWM_OUTPUT_ODIS5A
  *        @arg HRPWM_OUTPUT_ODIS5B
  * @retval None
  */
#define __LL_HRPWM_OUTPUT_STOP(__OUTPUT__)   SET_BIT(HRPWM->Common.ODISR, (__OUTPUT__))

/** @brief  Multiple mode combination configuration
 * @param  __TIMERS__ timers to enable/disable
 *        This parameter can be any combinations of the following values:
 *            @arg HRPWM_INDEX_MASTER: Master timer identifier
 *            @arg HRPWM_INDEX_SLAVE_0: Timer 0 identifier
 *            @arg HRPWM_INDEX_SLAVE_1: Timer 1 identifier
 *            @arg HRPWM_INDEX_SLAVE_2: Timer 2 identifier
 *            @arg HRPWM_INDEX_SLAVE_3: Timer 3 identifier
 *            @arg HRPWM_INDEX_SLAVE_4: Timer 4 identifier
 *            @arg HRPWM_INDEX_SLAVE_5: Timer 5 identifier

 * @param  __MODE__ set output mode(half \ interleaved \ pushpull)
 *        This parameter can be any combinations of the following values:
 *        @arg HRPWM_HALFMODE_DISABLE
 *        @arg HRPWM_HALFMODE_ENABLE
 *        @arg HRPWM_INTERLEAVED_MODE_DISABLE
 *        @arg HRPWM_INTERLEAVED_MODE_TRIPLE
 *        @arg HRPWM_INTERLEAVED_MODE_QUAD
 *        @arg HRPWM_PUSHPULLMODE_DISABLE
 *        @arg HRPWM_PUSHPULLMODE_ENABLE
 * @retval None
 */
#define __LL_HRPWM_OUTPUTMODE_SET(__TIMERS__, __MODE__)                                                         \
    (((__TIMERS__) == HRPWM_INDEX_MASTER) ?                                                                     \
     (MODIFY_REG(HRPWM->Master.MCR , HRPWM_MCR_HALF | HRPWM_MCR_INTLVD, __MODE__)) :                            \
     (MODIFY_REG(HRPWM->PWM[__TIMERS__].CR0 , HRPWM_CR0_HALF | HRPWM_CR0_INTLVD | HRPWM_CR0_PSHPLL, __MODE__)))

/** @brief  Select which faults are effectively configured in each slave timer
 * @param  __TIMERS__ timers to enable/disable
 *        This parameter can be any combinations of the following values:
 *            @arg HRPWM_INDEX_SLAVE_0: Timer 0 identifier
 *            @arg HRPWM_INDEX_SLAVE_1: Timer 1 identifier
 *            @arg HRPWM_INDEX_SLAVE_2: Timer 2 identifier
 *            @arg HRPWM_INDEX_SLAVE_3: Timer 3 identifier
 *            @arg HRPWM_INDEX_SLAVE_4: Timer 4 identifier
 *            @arg HRPWM_INDEX_SLAVE_5: Timer 5 identifier
 * @param  __FAULT__ timers start output wave @ HRPWM_Timer_Fault_Enabling
 *        This parameter can be any combinations of the following values:
 *        @arg HRPWM_FAULTEN_NONE
 *        @arg HRPWM_FAULTEN_FAULT0
 *        @arg HRPWM_FAULTEN_FAULT1
 *        @arg HRPWM_FAULTEN_FAULT2
 *        @arg HRPWM_FAULTEN_FAULT3
 *        @arg HRPWM_FAULTEN_FAULT4
 *        @arg HRPWM_FAULTEN_FAULT5
 * @retval None
 */
#define __LL_HRPWM_SLAVE_FAULT_VALID_SEL(__TIMERS__, __FAULT__)     MODIFY_REG(HRPWM->PWM[__TIMERS__].FLTR, 0x3F, __FAULT__)

/** @brief  The software forces the corresponding output high or low
 * @param  __TIMERS__ timers to
 *        After configuring this bit, you must reconfigure the output event in order to reoutput
 *        This parameter can be one of the following values:
 *            @arg HRPWM_INDEX_SLAVE_0: Timer 0 identifier
 *            @arg HRPWM_INDEX_SLAVE_1: Timer 1 identifier
 *            @arg HRPWM_INDEX_SLAVE_2: Timer 2 identifier
 *            @arg HRPWM_INDEX_SLAVE_3: Timer 3 identifier
 *            @arg HRPWM_INDEX_SLAVE_4: Timer 4 identifier
 *            @arg HRPWM_INDEX_SLAVE_5: Timer 5 identifier
 * @retval None
 */

#define __LL_HRPWM_OUTPUT_A_SET(__TIMERS__)                             \
        do {                                                            \
            CLEAR_REG(HRPWM->PWM[__TIMERS__].CLRAR);                    \
            WRITE_REG(HRPWM->PWM[__TIMERS__].SETAR, HRPWM_SETAR_SST);   \
        } while(0)

#define __LL_HRPWM_OUTPUT_A_CLEAR(__TIMERS__)                           \
        do {                                                            \
            CLEAR_REG(HRPWM->PWM[__TIMERS__].SETAR);                    \
            WRITE_REG(HRPWM->PWM[__TIMERS__].CLRAR, HRPWM_CLRAR_SST);   \
        } while(0)

#define __LL_HRPWM_OUTPUT_B_SET(__TIMERS__)                             \
        do {                                                            \
            CLEAR_REG(HRPWM->PWM[__TIMERS__].CLRBR);                    \
            WRITE_REG(HRPWM->PWM[__TIMERS__].SETBR, HRPWM_SETBR_SST);   \
        } while(0)

#define __LL_HRPWM_OUTPUT_B_CLEAR(__TIMERS__)                           \
        do {                                                            \
            CLEAR_REG(HRPWM->PWM[__TIMERS__].SETBR);                    \
            WRITE_REG(HRPWM->PWM[__TIMERS__].CLRBR, HRPWM_CLRBR_SST);   \
        } while(0)
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup HRPWM_LL_Exported_Functions
* @{
*/

/** @addtogroup HRPWM_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_HRPWM_Init(HRPWM_TypeDef *Instance, HRPWM_MasterSyncTypeDef *pMasterSync);
LL_StatusETypeDef LL_HRPWM_DeInit(HRPWM_TypeDef *Instance);
void LL_HRPWM_MspInit(HRPWM_TypeDef *Instance);
void LL_HRPWM_MspDeInit(HRPWM_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup HRPWM_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_HRPWM_DLLStartConfig(HRPWM_TypeDef *Instance, HRPWM_DLLCfgTypedef *DLLConfig);
LL_StatusETypeDef LL_HRPWM_DLLStart(HRPWM_TypeDef *Instance);
LL_StatusETypeDef LL_HRPWM_TimerBaseConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx, HRPWM_TimerBaseCfgTypeDef *pTimeBaseCfg);
LL_StatusETypeDef LL_HRPWM_TimerCompareConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx,
        HRPWM_TimerCompareCfgTypeDef *pTimerCompCfg);
/**
  * @}
  */


/** @addtogroup HRPWM_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_HRPWM_StopCounter(uint32_t TimerIdx);
LL_StatusETypeDef LL_HRPWM_StartCounter(uint32_t TimerIdx);
/**
  * @}
  */


/** @addtogroup HRPWM_LL_Exported_Functions_Group4
  * @{
  */
LL_StatusETypeDef LL_HRPWM_TimerUintRollOverContrl(HRPWM_TypeDef *Instance, uint32_t TimerIdx,
        HRPWM_TimerRollOverCfgTypeDef *pTimerRollOverCfg);
LL_StatusETypeDef LL_HRPWM_TimerDualChannelDacConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx,
        HRPWM_TimerDaulDacCfgTypeDef *pTimerDacCfg);
LL_StatusETypeDef  LL_HRPWM_TimerRollOverMode(HRPWM_TypeDef *Instance, uint32_t TimerIdx, uint32_t pRollOverMode);
/**
  * @}
  */


/** @addtogroup HRPWM_LL_Exported_Functions_Group5
  * @{
  */
LL_StatusETypeDef LL_HRPWM_FaultConfig(HRPWM_TypeDef *Instance, uint32_t Fault, HRPWM_FaultCfgTypeDef *pFaultCfg,
                                       HRPWM_FaultBlankingCfgTypeDef *pFaultBlkCfg);
LL_StatusETypeDef LL_HRPWM_FaultBlankingConfig(HRPWM_TypeDef *Instance, uint32_t Fault,
        HRPWM_FaultBlankingCfgTypeDef *pFaultBlkCfg);
LL_StatusETypeDef LL_HRPWM_FaultCounterConfig(HRPWM_TypeDef *Instance, uint32_t Fault,
        HRPWM_FaultBlankingCfgTypeDef *pFaultBlkCfg);
LL_StatusETypeDef LL_HRPWM_FaultCounterReset(uint32_t Fault);
LL_StatusETypeDef LL_HRPWM_ADDATriggerConfig(HRPWM_TypeDef *Instance, HRPWM_ADCTriggerCfgTypeDef *pADCTriggerCfg);
LL_StatusETypeDef LL_HRPWM_OutputConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx, HRPWM_OutputCfgTypeDef *pOutputCfg);
LL_StatusETypeDef LL_HRPWM_DeadTimeConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx,
        HRPWM_DeadTimeCfgTypeDef *pDeaTimedCfg);
LL_StatusETypeDef LL_HRPWM_ChopperConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx,
        HRPWM_ChopperModeCfgTypeDef *pChopperCfg);
LL_StatusETypeDef LL_HRPWM_EventConfig(HRPWM_TypeDef *Instance, uint32_t Event, HRPWM_EventCfgTypeDef *pEventCfg);
LL_StatusETypeDef LL_HRPWM_TimerEventAConfig(HRPWM_TypeDef *Instance, uint32_t TimerIdx,
        HRPWM_ExternalEventACfgTypeDef *pEventCfg, HRPWM_TimerEventFilteringCfgTypeDef *pEventFilter);
LL_StatusETypeDef LL_HRPWM_TimerEventAFilter(HRPWM_TypeDef *Instance, uint32_t TimerIdx, uint32_t Event,
        HRPWM_TimerEventFilteringCfgTypeDef *pEventFilter);
/**
  * @}
  */


/** @addtogroup HRPWM_LL_Exported_Functions_Group6
  * @{
  */
LL_StatusETypeDef LL_HRPWM_ForceRegistersUpdate(uint32_t TimerIdx);
LL_StatusETypeDef LL_HRPWM_DisRegisterUpdate(uint32_t TimerIdx);
LL_StatusETypeDef LL_HRPWM_EnRegUpdate(uint32_t TimerIdx);
LL_StatusETypeDef LL_HRPWM_StartOutput(uint32_t TimerIdx);
LL_StatusETypeDef LL_HRPWM_StopOutput(uint32_t TimerIdx);
LL_StatusETypeDef LL_HRPWM_SwapOutput(uint32_t TimerIdx, uint32_t swap);
LL_StatusETypeDef LL_HRPWM_ResetCounter(uint32_t TimerIdx);
/**
  * @}
  */


/** @addtogroup HRPWM_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_HRPWM_IRQHandler(uint32_t TimerIdx);

void LL_HRPWM_FLT_IRQHandler(void);
void LL_HRPWM_SLAVE_IRQHandler(uint32_t TimerIdx);
void LL_HRPWM_MSTR_IRQHandler(void);

void LL_HRPWM_Fault0Callback(void);
void LL_HRPWM_Fault1Callback(void);
void LL_HRPWM_Fault2Callback(void);
void LL_HRPWM_Fault3Callback(void);
void LL_HRPWM_Fault4Callback(void);
void LL_HRPWM_Fault5Callback(void);
void LL_HRPWM_SystemFaultCallback(void);
void LL_HRPWM_SynchronizationEventCallback(void);
void LL_HRPWM_RegistersUpdateCallback(uint32_t TimerIdx);
void LL_HRPWM_RepetitionEventCallback(uint32_t TimerIdx);
void LL_HRPWM_CompareAEventCallback(uint32_t TimerIdx);
void LL_HRPWM_CompareBEventCallback(uint32_t TimerIdx);
void LL_HRPWM_CompareCEventCallback(uint32_t TimerIdx);
void LL_HRPWM_CompareDEventCallback(uint32_t TimerIdx);
void LL_HRPWM_PeriodEventCallback(uint32_t TimerIdx);
void LL_HRPWM_CounterResetCallback(uint32_t TimerIdx);
void LL_HRPWM_OutputASetCallback(uint32_t TimerIdx);
void LL_HRPWM_OutputBSetCallback(uint32_t TimerIdx);
void LL_HRPWM_OutputAResetCallback(uint32_t TimerIdx);
void LL_HRPWM_OutputBResetCallback(uint32_t TimerIdx);
/**
  * @}
  */

/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup HRPWM_LL_Private_Macros HRPWM LL Private Macros
  * @brief    HRPWM LL Private Macros
  * @{
  */

/**
  * @brief  Judge is HRPWM index all or not
  * @param  __INDEX__ index to judge
  * @retval 0 isn't HRPWM index all
  * @retval 1 is HRPWM index all
  */
#define IS_HRPWM_INDEX_ALL(__INDEX__)             \
    (((__INDEX__) == HRPWM_INDEX_SLAVE_0) || \
     ((__INDEX__) == HRPWM_INDEX_SLAVE_1) || \
     ((__INDEX__) == HRPWM_INDEX_SLAVE_2) || \
     ((__INDEX__) == HRPWM_INDEX_SLAVE_3) || \
     ((__INDEX__) == HRPWM_INDEX_SLAVE_4) || \
     ((__INDEX__) == HRPWM_INDEX_SLAVE_5) || \
     ((__INDEX__) == HRPWM_INDEX_MASTER)  || \
     ((__INDEX__) == HRPWM_INDEX_COMMON))

/**
  * @brief  Judge is HRPWM index or not
  * @param  __INDEX__ index to judge
  * @retval 0 isn't HRPWM index
  * @retval 1 is HRPWM index
  */
#define IS_HRPWM_INDEX(__INDEX__)            \
    (((__INDEX__) == HRPWM_INDEX_SLAVE_0) || \
     ((__INDEX__) == HRPWM_INDEX_SLAVE_1) || \
     ((__INDEX__) == HRPWM_INDEX_SLAVE_2) || \
     ((__INDEX__) == HRPWM_INDEX_SLAVE_3) || \
     ((__INDEX__) == HRPWM_INDEX_SLAVE_4) || \
     ((__INDEX__) == HRPWM_INDEX_SLAVE_5) || \
     ((__INDEX__) == HRPWM_INDEX_MASTER))

/**
  * @brief  Judge is HRPWM fault interrupt or not
  * @param  __INTERRUPT__ interrupt to judge
  * @retval 0 isn't HRPWM fault interrupt
  * @retval 1 is HRPWM fault interrupt
  */
#define IS_HRPWM_FAULT_IT(__INTERRUPT__)    \
    (((__INTERRUPT__) == HRPWM_IT_NONE) || \
     (((__INTERRUPT__) & HRPWM_IT_SRC) != HRPWM_IT_NONE))

/**
  * @brief  Judge is HRPWM master interrupt or not
  * @param  __INTERRUPT__ interrupt to judge
  * @retval 0 isn't HRPWM master interrupt
  * @retval 1 is HRPWM master interrupt
  */
#define IS_HRPWM_MASTER_IT(__INTERRUPT__)          \
    (((__INTERRUPT__) == HRPWM_MASTER_IT_NONE) || \
     (((__INTERRUPT__) & HRPWM_MASTER_IT_SRC) != HRPWM_MASTER_IT_NONE))

/**
  * @brief  Judge is HRPWM timer interrupt or not
  * @param  __INTERRUPT__ interrupt to judge
  * @retval 0 isn't HRPWM timer interrupt
  * @retval 1 is HRPWM timer interrupt
  */
#define IS_HRPWM_TIMER_IT(__INTERRUPT__)          \
    (((__INTERRUPT__) == HRPWM_IT_TIMER_NONE) || \
     (((__INTERRUPT__) & HRPWM_IT_TIMER_SRC) != HRPWM_IT_TIMER_NONE))

/**
  * @brief  Judge is HRPWM sync output source or not
  * @param  __OUTPUT__ output source to judge
  * @retval 0 isn't HRPWM sync output source
  * @retval 1 is HRPWM sync output source
  */
#define IS_HRPWM_SYNCOUTPUTSOURCE(__OUTPUT__)     \
    (((__OUTPUT__) == HRPWM_SYNCOUTPUTSOURCE_MASTER_START) || \
     ((__OUTPUT__) == HRPWM_SYNCOUTPUTSOURCE_MASTER_CMPA) || \
     ((__OUTPUT__) == HRPWM_SYNCOUTPUTSOURCE_SLAVE0_STARTRST) || \
     ((__OUTPUT__) == HRPWM_SYNCOUTPUTSOURCE_SLAVE0_CMPA))

/**
  * @brief  Judge is HRPWM sync output polarity or not
  * @param  __POLARITY__ output polarity to judge
  * @retval 0 isn't HRPWM sync polarity source
  * @retval 1 is HRPWM sync polarity source
  */
#define IS_HRPWM_SYNCOUTPUTPOLARITY(__POLARITY__)  \
    (((__POLARITY__) == HRPWM_SYNCOUTPUTPOLARITY_POSITIVE) || \
     ((__POLARITY__) == HRPWM_SYNCOUTPUTPOLARITY_NEGATIVE))

/**
  * @brief  Judge is HRPWM sync input source or not
  * @param  __SOURCE__ input source to judge
  * @retval 0 isn't HRPWM sync input source
  * @retval 1 is HRPWM sync input source
  */
#define IS_HRPWM_SYNINPUTSOURCE(__SOURCE__)                     \
    (((__SOURCE__) == HRPWM_SYNCINPUTSOURCE_NONE)            || \
     ((__SOURCE__) == HRPWM_SYNCINPUTSOURCE_TIM0_TRGO_EVENT) || \
     ((__SOURCE__) == HRPWM_SYNCINPUTSOURCE_EVENT))

/**
  * @brief  Judge is HRPWM DLLGCP or not
  * @param  __CURRENT__ current to judge
  * @retval 0 isn't HRPWM DLLGCP
  * @retval 1 is HRPWM DLLGCP
  */
#define IS_HRPWM_DLLGCP(__CURRENT__)            \
    (((__CURRENT__) == HRPWM_DLLCR_DLLGCP_4) || \
     ((__CURRENT__) == HRPWM_DLLCR_DLLGCP_6) || \
     ((__CURRENT__) == HRPWM_DLLCR_DLLGCP_8))

/**
  * @brief  Judge is HRPWM prescale ratio or not
  * @param  __CLKPSC__ ratio to judge
  * @retval 0 isn't HRPWM prescale ratio
  * @retval 1 is HRPWM prescale ratio
  */
#define IS_HRPWM_PRESCALERRATIO(__CLKPSC__)          \
    (((__CLKPSC__) == HRPWM_PRESCALERRATIO_MUL32) || \
     ((__CLKPSC__) == HRPWM_PRESCALERRATIO_MUL16) || \
     ((__CLKPSC__) == HRPWM_PRESCALERRATIO_MUL8) || \
     ((__CLKPSC__) == HRPWM_PRESCALERRATIO_MUL4) || \
     ((__CLKPSC__) == HRPWM_PRESCALERRATIO_MUL2) || \
     ((__CLKPSC__) == HRPWM_PRESCALERRATIO_DIV1) || \
     ((__CLKPSC__) == HRPWM_PRESCALERRATIO_DIV2) || \
     ((__CLKPSC__) == HRPWM_PRESCALERRATIO_DIV4))

/**
  * @brief  Judge is HRPWM preload or not
  * @param  __PREEN__ preload to judge
  * @retval 0 isn't HRPWM preload
  * @retval 1 is HRPWM preload
  */
#define IS_HRPWM_PRELOAD(__PREEN__)             \
    (((__PREEN__) == HRPWM_PRELOAD_DISABLE) || \
     ((__PREEN__) == HRPWM_PRELOAD_ENABLE))


/**
  * @brief  Judge is HRPWM half mode or not
  * @param  __MODE__ mode to judge
  * @retval 0 isn't HRPWM half mode
  * @retval 1 is HRPWM half mode
  */
#define IS_HRPWM_HALFMODE(__MODE__)             \
    (((__MODE__) == HRPWM_HALFMODE_DISABLE) || \
     ((__MODE__) == HRPWM_HALFMODE_ENABLE))

/**
  * @brief  Judge is HRPWM push pull mode or not
  * @param  __SYNC__ mode to judge
  * @retval 0 isn't HRPWM push pull mode
  * @retval 1 is HRPWM push pull mode
  */
#define IS_HRPWM_PUSHPULLMODE(__SYNC__)             \
    (((__SYNC__) == HRPWM_PUSHPULLMODE_DISABLE) || \
     ((__SYNC__) == HRPWM_PUSHPULLMODE_ENABLE))

/**
  * @brief  Judge is HRPWM sync start or not
  * @param  __SYNC__ sync start to judge
  * @retval 0 isn't HRPWM sync start
  * @retval 1 is HRPWM sync start
  */
#define IS_HRPWM_SYNCSTART(__SYNC__)             \
    (((__SYNC__) == HRPWM_SYNCSTART_DISABLE) || \
     ((__SYNC__) == HRPWM_SYNCSTART_ENABLE))

/**
  * @brief  Judge is HRPWM sync reset or not
  * @param  __SYNC__ sync reset to judge
  * @retval 0 isn't HRPWM sync reset
  * @retval 1 is HRPWM sync reset
  */
#define IS_HRPWM_SYNCRESET(__SYNC__)             \
    (((__SYNC__) == HRPWM_SYNCRESET_DISABLE) || \
     ((__SYNC__) == HRPWM_SYNCRESET_ENABLE))

/**
  * @brief  Judge is HRPWM Interleaved Mode or not
  * @param  __MODE__ mode to judge
  * @retval 0 isn't HRPWM Interleaved Mode
  * @retval 1 is HRPWM Interleaved Mode
  */
#define IS_HRPWM_INTERLEAVEDMODE(__MODE__)              \
    (((__MODE__) == HRPWM_INTERLEAVED_MODE_DISABLE) || \
     ((__MODE__) == HRPWM_INTERLEAVED_MODE_TRIPLE)   || \
     ((__MODE__) == HRPWM_INTERLEAVED_MODE_QUAD))

/**
  * @brief  Judge is HRPWM fault enable or not
  * @param  __FAULT__ fault to judge
  * @retval 0 isn't HRPWM fault enable
  * @retval 1 is HRPWM fault enable
  */
#define IS_HRPWM_FAULTENABLE(__FAULT__)      \
    (((__FAULT__) == HRPWM_FAULTEN_NONE) || \
     (((__FAULT__) & 0x3f) != HRPWM_FAULTEN_NONE))

/**
  * @brief  Judge is HRPWM resync update or not
  * @param  __RESYNC__ resync to judge
  * @retval 0 isn't HRPWM resync update
  * @retval 1 is HRPWM resync update
  */
#define IS_HRPWM_RESYNCUPDATE(__RESYNC__)       \
    (((__RESYNC__) == HRPWM_RSYNCUPDATE_DISABLE) || \
     ((__RESYNC__) == HRPWM_RSYNCUPDATE_ENABLE))

/**
  * @brief  Judge is HRPWM update trigger or not
  * @param  __UPDATE__ update trigger to judge
  * @retval 0 isn't HRPWM update trigger
  * @retval 1 is HRPWM update trigger
  */
#define IS_HRPWM_UPDATETRIGGER(__UPDATE__)            \
    (((__UPDATE__) == HRPWM_UPDATETRIGGER_NONE)    || \
     ((__UPDATE__) == HRPWM_UPDATETRIGGER_MASTER)  || \
     ((__UPDATE__) == HRPWM_UPDATETRIGGER_REP)     || \
     ((__UPDATE__) == HRPWM_UPDATETRIGGER_RST)     || \
     ((__UPDATE__) == HRPWM_UPDATETRIGGER_TIMER_0) || \
     ((__UPDATE__) == HRPWM_UPDATETRIGGER_TIMER_1) || \
     ((__UPDATE__) == HRPWM_UPDATETRIGGER_TIMER_2) || \
     ((__UPDATE__) == HRPWM_UPDATETRIGGER_TIMER_3) || \
     ((__UPDATE__) == HRPWM_UPDATETRIGGER_TIMER_4) || \
     ((__UPDATE__) == HRPWM_UPDATETRIGGER_TIMER_5))

/**
  * @brief  Judge is HRPWM mode or not
  * @param  __MODE__ mode to judge
  * @retval 0 isn't HRPWM mode
  * @retval 1 is HRPWM mode
  */
#define IS_HRPWM_MODE(__MODE__)                \
    (((__MODE__) == HRPWM_MODE_CONTINUOUS) || \
     ((__MODE__) == HRPWM_MODE_SINGLESHOT) || \
     ((__MODE__) == HRPWM_MODE_SINGLESHOT_RETRIGGERABLE))

/**
  * @brief  Judge is HRPWM dual DAC reset or not
  * @param  __MODE__ mode to judge
  * @retval 0 isn't HRPWM dual DAC reset
  * @retval 1 is HRPWM dual DAC reset
  */
#define IS_HRPWM_DUALDAC_RESET(__MODE__)     \
    (((__MODE__) == HRPWM_DAC_DCDR_RESET) || \
     ((__MODE__) == HRPWM_DAC_DCDR_SETA))

/**
  * @brief  Judge is HRPWM dual DAC step or not
  * @param  __MODE__ mode to judge
  * @retval 0 isn't HRPWM dual DAC step
  * @retval 1 is HRPWM dual DAC step
  */
#define IS_HRPWM_DUALDAC_STEP(__MODE__)     \
    (((__MODE__) == HRPWM_DAC_DCDS_CMPD) || \
     ((__MODE__) == HRPWM_DAC_DCDS_CLEARA))

/**
  * @brief  Judge is HRPWM dual DAC enable or not
  * @param  __MODE__ mode to judge
  * @retval 0 isn't HRPWM dual DAC enable
  * @retval 1 is HRPWM dual DAC enable
  */
#define IS_HRPWM_DUALDAC_ENABLE(__MODE__)      \
    (((__MODE__) == HRPWM_DAC_DCDE_DISABLE) || \
     ((__MODE__) == HRPWM_DAC_DCDE_ENABLE))

/**
  * @brief  Judge is HRPWM fault or not
  * @param  __FAULT__ fault to judge
  * @retval 0 isn't HRPWM fault
  * @retval 1 is HRPWM fault
  */
#define IS_HRPWM_FAULT(__FAULT__)       \
    (((__FAULT__) == HRPWM_FAULT_0) || \
     ((__FAULT__) == HRPWM_FAULT_1) || \
     ((__FAULT__) == HRPWM_FAULT_2) || \
     ((__FAULT__) == HRPWM_FAULT_3) || \
     ((__FAULT__) == HRPWM_FAULT_4) || \
     ((__FAULT__) == HRPWM_FAULT_5))

/**
  * @brief  Judge is HRPWM fault source or not
  * @param  __SOURCE__ source to judge
  * @retval 0 isn't HRPWM fault source
  * @retval 1 is HRPWM fault source
  */
#define IS_HRPWM_FAULTSOURCE(__SOURCE__)     \
    (((__SOURCE__) == HRPWM_FLTSRC_GPIO) || \
     ((__SOURCE__) == HRPWM_FLTSRC_COMP_OUT) || \
     ((__SOURCE__) == HRPWM_FLTSRC_EVENT))

/**
  * @brief  Judge is HRPWM fault polarity or not
  * @param  __POLARITY__ polarity to judge
  * @retval 0 isn't HRPWM fault polarity
  * @retval 1 is HRPWM fault polarity
  */
#define IS_HRPWM_FAULTPOLARITY(__POLARITY__)    \
    (((__POLARITY__) == HRPWM_FAULTPOL_LOW) || \
     ((__POLARITY__) == HRPWM_FAULTPOL_HIGH))

/**
  * @brief  Judge is HRPWM fault filter or not
  * @param  __FILTER__ filter to judge
  * @retval 0 isn't HRPWM fault filter
  * @retval 1 is HRPWM fault filter
  */
#define IS_HRPWM_FAULTFILTER(__FILTER__)          \
    (((__FILTER__) == HRPWM_FAULTFILTER_NONE) || \
     (((__FILTER__) & HRPWM_FLTINR1_FLT0F) != HRPWM_FAULTFILTER_NONE))

/**
  * @brief  Judge is HRPWM fault sample clock div or not
  * @param  __CLKDIV__ clock div to judge
  * @retval 0 isn't HRPWM fault sample clock div
  * @retval 1 is HRPWM fault sample clock div
  */
#define IS_HRPWM_FAULTSAMPCLK(__CLKDIV__)   \
    (((__CLKDIV__) == HRPWM_FLTSD_DIV1) || \
     ((__CLKDIV__) == HRPWM_FLTSD_DIV2) || \
     ((__CLKDIV__) == HRPWM_FLTSD_DIV4) || \
     ((__CLKDIV__) == HRPWM_FLTSD_DIV8))

/**
  * @brief  Judge is HRPWM fault blanking enable or not
  * @param  __BLKEN__ blanking enable to judge
  * @retval 0 isn't HRPWM fault blanking enable
  * @retval 1 is HRPWM fault blanking enable
  */
#define IS_HRPWM_FAULTBLKEN(__BLKEN__)            \
    (((__BLKEN__) == HRPWM_FAULTBLKEN_DISABLE) || \
     ((__BLKEN__) == HRPWM_FAULTBLKEN_ENABLE))

/**
  * @brief  Judge is HRPWM fault blanking source or not
  * @param  __BLKSRC__ blanking source to judge
  * @retval 0 isn't HRPWM fault blanking source
  * @retval 1 is HRPWM fault blanking source
  */
#define IS_HRPWM_FAULTBLKSRC(__BLKSRC__)          \
    (((__BLKSRC__) == HRPWM_FAULTBLKS_RSTALIGNED) || \
     ((__BLKSRC__) == HRPWM_FAULTBLKS_MOVING))

/**
  * @brief  Judge is HRPWM fault reset mode or not
  * @param  __MODE__ mode to judge
  * @retval 0 isn't HRPWM fault reset mode
  * @retval 1 is HRPWM fault reset mode
  */
#define IS_HRPWM_FAULTRSTMODE(__MODE__)           \
    (((__MODE__) == HRPWM_FAULTRSTM_UNCONDITIONAL) || \
     ((__MODE__) == HRPWM_FAULTRSTM_CONDITIONAL))

/**
  * @brief  Judge is HRPWM ADC trigger or not
  * @param  __ADCTRIGGER__ trigger to judge
  * @retval 0 isn't HRPWM ADC trigger
  * @retval 1 is HRPWM ADC trigger
  */
#define IS_HRPWM_ADCTRIGGER(__ADCTRIGGER__)        \
    (((__ADCTRIGGER__) == HRPWM_ADCTRIGGER_0)   || \
     ((__ADCTRIGGER__) == HRPWM_ADCTRIGGER_1)   || \
     ((__ADCTRIGGER__) == HRPWM_ADCTRIGGER_2)   || \
     ((__ADCTRIGGER__) == HRPWM_ADCTRIGGER_3)   || \
     ((__ADCTRIGGER__) == HRPWM_ADCTRIGGER_4)   || \
     ((__ADCTRIGGER__) == HRPWM_ADCTRIGGER_5)   || \
     ((__ADCTRIGGER__) == HRPWM_ADCTRIGGER_6)   || \
     ((__ADCTRIGGER__) == HRPWM_ADCTRIGGER_7))

/**
  * @brief  Judge is HRPWM ADC trigger post scaler or not
  * @param  __PSC__ post scaler to judge
  * @retval 0 isn't HRPWM ADC trigger post scaler
  * @retval 1 is HRPWM ADC trigger post scaler
  */
#define IS_HRPWM_ADCTRIGGER_POSTSCALER(__PSC__)       \
    (((__PSC__) == HRPWM_ADCTRIG_PSC_1) || \
     (((__PSC__) & HRPWM_ADPSR_ADPSC0) != HRPWM_ADCTRIG_PSC_1))

/**
  * @brief  Judge is HRPWM ADC trigger length or not
  * @param  __LENGTH__ length to judge
  * @retval 0 isn't HRPWM ADC trigger length
  * @retval 1 is HRPWM ADC trigger length
  */
#define IS_HRPWM_ADCTRIGGER_LENGTH(__LENGTH__) \
    (((__LENGTH__) == HRPWM_ADCTRIG_LENGTH_1) || \
     (((__LENGTH__) & HRPWM_CR2_TLEN0) != HRPWM_ADCTRIG_LENGTH_1))

/**
  * @brief  Judge is HRPWM ADC trigger update source or not
  * @param  __UPDSRC__ update source to judge
  * @retval 0 isn't HRPWM ADC trigger update source
  * @retval 1 is HRPWM ADC trigger update source
  */
#define IS_HRPWM_ADCTRIGGER_UPDATESRC(__UPDSRC__)     \
    (((__UPDSRC__) == HRPWM_ADCTRIGUPDATE_MASTER) ||  \
     ((__UPDSRC__) == HRPWM_ADCTRIGUPDATE_TIMER_0) || \
     ((__UPDSRC__) == HRPWM_ADCTRIGUPDATE_TIMER_1) || \
     ((__UPDSRC__) == HRPWM_ADCTRIGUPDATE_TIMER_2) || \
     ((__UPDSRC__) == HRPWM_ADCTRIGUPDATE_TIMER_3) || \
     ((__UPDSRC__) == HRPWM_ADCTRIGUPDATE_TIMER_4) || \
     ((__UPDSRC__) == HRPWM_ADCTRIGUPDATE_TIMER_5))

/**
  * @brief  Judge is HRPWM output A active polarity or not
  * @param  __POLARITY__ polarity to judge
  * @retval 0 isn't HRPWM output A active polarity
  * @retval 1 is HRPWM output A active polarity
  */
#define IS_HRPWM_OUTPUTA_POLARITY(__POLARITY__)        \
    (((__POLARITY__) == HRPWM_OUTPUT_POLA_POSITIVE) || \
     ((__POLARITY__) == HRPWM_OUTPUT_POLA_NEGATIVE))

/**
  * @brief  Judge is HRPWM output A idel level or not
  * @param  __IDEL__ idel level to judge
  * @retval 0 isn't HRPWM output A idel level
  * @retval 1 is HRPWM output A idel level
  */
#define IS_HRPWM_OUTPUTA_IDLELEVEL(__IDEL__)       \
    (((__IDEL__) == HRPWM_OUTPUTIDLEA_INACTIVE) || \
     ((__IDEL__) == HRPWM_OUTPUTIDLEA_ACTIVE))

/**
  * @brief  Judge is HRPWM output A fault level or not
  * @param  __LEVEL__ fault level to judge
  * @retval 0 isn't HRPWM output A fault level
  * @retval 1 is HRPWM output A fault level
  */
#define IS_HRPWM_OUTPUTA_FLTLEVEL(__LEVEL__)         \
    (((__LEVEL__) == HRPWM_OUTPUTFAULTA_NONE)     || \
     ((__LEVEL__) == HRPWM_OUTPUTFAULTA_ACTIVE)   || \
     ((__LEVEL__) == HRPWM_OUTPUTFAULTA_INACTIVE) || \
     ((__LEVEL__) == HRPWM_OUTPUTFAULTA_HIGHZ))

/**
  * @brief  Judge is HRPWM output A Chopper Mode enable or not
  * @param  __CHOPPER__ Chopper Mode enable to judge
  * @retval 0 isn't HRPWM output A Chopper Mode enable
  * @retval 1 is HRPWM output A Chopper Mode enable
  */
#define IS_HRPWM_OUTPUTA_CHOPPEREN(__CHOPPER__)         \
    (((__CHOPPER__) == HRPWM_OUTPUTCHOPPERA_ENABLE) || \
     ((__CHOPPER__) == HRPWM_OUTPUTCHOPPERA_DISABLE))

/**
  * @brief  Judge is HRPWM output B active polarity or not
  * @param  __POLARITY__ polarity to judge
  * @retval 0 isn't HRPWM output B active polarity
  * @retval 1 is HRPWM output B active polarity
  */
#define IS_HRPWM_OUTPUTB_POLARITY(__POLARITY__)         \
    (((__POLARITY__) == HRPWM_OUTPUT_POLB_POSITIVE) || \
     ((__POLARITY__) == HRPWM_OUTPUT_POLB_NEGATIVE))

/**
  * @brief  Judge is HRPWM output B idel level or not
  * @param  __IDEL__ idel level to judge
  * @retval 0 isn't HRPWM output B idel level
  * @retval 1 is HRPWM output B idel level
  */
#define IS_HRPWM_OUTPUTB_IDLELEVEL(__IDEL__)        \
    (((__IDEL__) == HRPWM_OUTPUTIDLEB_INACTIVE) || \
     ((__IDEL__) == HRPWM_OUTPUTIDLEB_ACTIVE))

/**
  * @brief  Judge is HRPWM output B fault level or not
  * @param  __LEVEL__ fault level to judge
  * @retval 0 isn't HRPWM output B fault level
  * @retval 1 is HRPWM output B fault level
  */
#define IS_HRPWM_OUTPUTB_FLTLEVEL(__LEVEL__)         \
    (((__LEVEL__) == HRPWM_OUTPUTFAULTB_NONE)     || \
     ((__LEVEL__) == HRPWM_OUTPUTFAULTB_ACTIVE)   || \
     ((__LEVEL__) == HRPWM_OUTPUTFAULTB_INACTIVE) || \
     ((__LEVEL__) == HRPWM_OUTPUTFAULTB_HIGHZ))

/**
  * @brief  Judge is HRPWM output B Chopper Mode enable or not
  * @param  __CHOPPER__ Chopper Mode enable to judge
  * @retval 0 isn't HRPWM output B Chopper Mode enable
  * @retval 1 is HRPWM output B Chopper Mode enable
  */
#define IS_HRPWM_OUTPUTB_CHOPPEREN(__CHOPPER__)     \
    (((__CHOPPER__) == HRPWM_OUTPUTCHOPPERB_ENABLE) || \
     ((__CHOPPER__) == HRPWM_OUTPUTCHOPPERB_DISABLE))

/**
  * @brief  Judge is HRPWM output event or not
  * @param  __INTERRUPT__ interrupt to judge
  * @retval 0 isn't HRPWM output event
  * @retval 1 is HRPWM output event
  */
#define IS_HRPWM_OUTPUT_SET_EVENT(__INTERRUPT__)      \
    (((__INTERRUPT__) == HRPWM_OUTPUT_SET_NONE) || \
     (((__INTERRUPT__) & 0x7FFFFU) != HRPWM_OUTPUT_SET_NONE))
/**
  * @brief  Judge is HRPWM output event or not
  * @param  __INTERRUPT__ interrupt to judge
  * @retval 0 isn't HRPWM output event
  * @retval 1 is HRPWM output event
  */
#define IS_HRPWM_OUTPUT_CLEAR_EVENT(__INTERRUPT__)      \
    (((__INTERRUPT__) == HRPWM_OUTPUT_CLEAR_NONE) || \
     (((__INTERRUPT__) & 0x7FFFFU) != HRPWM_OUTPUT_CLEAR_NONE))

/**
  * @brief  Judge is HRPWM dead time rising sign or not
  * @param  __SIGN__ sign to judge
  * @retval 0 isn't HRPWM dead time rising sign
  * @retval 1 is HRPWM dead time rising sign
  */
#define IS_HRPWM_DEADTIME_SDTR(__SIGN__)          \
    (((__SIGN__) == HRPWM_DEADTIME_RSIGN_NEGATIVE) || \
     ((__SIGN__) == HRPWM_DEADTIME_RSIGN_POSITIVE))

/**
  * @brief  Judge is HRPWM dead time falling sign or not
  * @param  __SIGN__ sign to judge
  * @retval 0 isn't HRPWM dead time falling sign
  * @retval 1 is HRPWM dead time falling sign
  */
#define IS_HRPWM_DEADTIME_SDTF(__SIGN__)          \
    (((__SIGN__) == HRPWM_DEADTIME_FSIGN_NEGATIVE) || \
     ((__SIGN__) == HRPWM_DEADTIME_FSIGN_POSITIVE))

/**
  * @brief  Judge is HRPWM chopper duty cycle or not
  * @param  __CARDTY__ chopper duty cycle to judge
  * @retval 0 isn't HRPWM chopper duty cycle
  * @retval 1 is HRPWM chopper duty cycle
  */
#define IS_HRPWM_CHOPPER_CARDTY(__CARDTY__)        \
    (((__CARDTY__) == HRPWM_CHOPPER_DUTYCYCLE_0) || \
     ((__CARDTY__) == HRPWM_CHOPPER_DUTYCYCLE_1) || \
     ((__CARDTY__) == HRPWM_CHOPPER_DUTYCYCLE_2) || \
     ((__CARDTY__) == HRPWM_CHOPPER_DUTYCYCLE_3) || \
     ((__CARDTY__) == HRPWM_CHOPPER_DUTYCYCLE_4) || \
     ((__CARDTY__) == HRPWM_CHOPPER_DUTYCYCLE_5) || \
     ((__CARDTY__) == HRPWM_CHOPPER_DUTYCYCLE_6) || \
     ((__CARDTY__) == HRPWM_CHOPPER_DUTYCYCLE_7))

/**
  * @brief  Judge is HRPWM chopper start pulse width or not
  * @param  __STRPW__ start pulse width to judge
  * @retval 0 isn't HRPWM chopper start pulse width
  * @retval 1 is HRPWM chopper start pulse width
  */
#define IS_HRPWM_CHOPPER_STRPW(__STRPW__)         \
    (((__STRPW__) == HRPWM_CHOPPER_PULSEWIDTH_16) || \
     (((__STRPW__) & HRPWM_CHPR_STRPW) != HRPWM_CHOPPER_PULSEWIDTH_16))

/**
  * @brief  Judge is HRPWM chopper frequency or not
  * @param  __CARFRQ__ chopper frequency to judge
  * @retval 0 isn't HRPWM chopper frequency
  * @retval 1 is HRPWM chopper frequency
  */
#define IS_HRPWM_CHOPPER_CARFRQ(__CARFRQ__)       \
    (((__CARFRQ__) == HRPWM_CHOPPER_CARFRQ_DIV16) || \
     (((__CARFRQ__) & HRPWM_CHPR_CARFRQ) != HRPWM_CHOPPER_CARFRQ_DIV16))

/**
  * @brief  Judge is HRPWM event or not
  * @param  __EVENT__ event to judge
  * @retval 0 isn't HRPWM event
  * @retval 1 is HRPWM event
  */
#define IS_HRPWM_EVENT(__EVENT__)         \
    (((__EVENT__) == HRPWM_EVENT_NONE) || \
     ((__EVENT__) == HRPWM_EVENT_0) || \
     ((__EVENT__) == HRPWM_EVENT_1) || \
     ((__EVENT__) == HRPWM_EVENT_2) || \
     ((__EVENT__) == HRPWM_EVENT_3) || \
     ((__EVENT__) == HRPWM_EVENT_4) || \
     ((__EVENT__) == HRPWM_EVENT_5))

/**
  * @brief  Judge is HRPWM event source or not
  * @param  __SOURCE__ source to judge
  * @retval 0 isn't HRPWM event source
  * @retval 1 is HRPWM event source
  */
#define IS_HRPWM_EVENTSOURCE(__SOURCE__)        \
    (((__SOURCE__) == HRPWM_EEVSRC_GPIO)     || \
     ((__SOURCE__) == HRPWM_EEVSRC_COMP_OUT) || \
     ((__SOURCE__) == HRPWM_EEVSRC_TIM_TRGO) || \
     ((__SOURCE__) == HRPWM_EEVSRC_ADC_AWD))

/**
  * @brief  Judge is HRPWM event polarity or not
  * @param  __POLARITY__ polarity to judge
  * @retval 0 isn't HRPWM event polarity
  * @retval 1 is HRPWM event polarity
  */
#define IS_HRPWM_EVENTPOLARITY(__POLARITY__)     \
    (((__POLARITY__) == HRPWM_EVENTPOL_HIGH) || \
     ((__POLARITY__) == HRPWM_EVENTPOL_LOW))

/**
  * @brief  Judge is HRPWM event filter or not
  * @param  __FILTER__ filter to judge
  * @retval 0 isn't HRPWM event filter
  * @retval 1 is HRPWM event filter
  */
#define IS_HRPWM_EVENTFILTER(__FILTER__)          \
    (((__FILTER__) == HRPWM_EVENTFILTER_NONE) || \
     (((__FILTER__) & HRPWM_EECR2_EE0F) != HRPWM_EVENTFILTER_NONE))

/**
  * @brief  Judge is HRPWM event prescaler div or not
  * @param  __CLKDIV__ prescaler div to judge
  * @retval 0 isn't HRPWM event prescaler div
  * @retval 1 is HRPWM event prescaler div
  */
#define IS_HRPWM_EVENTSAMPCLK(__CLKDIV__)   \
    (((__CLKDIV__) == HRPWM_EEVSD_DIV1) || \
     ((__CLKDIV__) == HRPWM_EEVSD_DIV2) || \
     ((__CLKDIV__) == HRPWM_EEVSD_DIV4) || \
     ((__CLKDIV__) == HRPWM_EEVSD_DIV8))

/**
  * @brief  Judge is HRPWM event fast mode or not
  * @param  __MODE__ mode to judge
  * @retval 0 isn't HRPWM event fast mode
  * @retval 1 is HRPWM event fast mode
  */
#define IS_HRPWM_EVENTFASTMODE(__MODE__)             \
    (((__MODE__) == HRPWM_EVENTFASTMODE_DISABLE) || \
     ((__MODE__) == HRPWM_EVENTFASTMODE_ENABLE))

/**
  * @brief  Judge is HRPWM event Sensitivity or not
  * @param  __SNS__ Sensitivity to judge
  * @retval 0 isn't HRPWM event Sensitivity
  * @retval 1 is HRPWM event Sensitivity
  */
#define IS_HRPWM_EVENTSNS(__SNS__)                 \
    (((__SNS__) == HRPWM_EVENTSENS_LEVEL)       || \
     ((__SNS__) == HRPWM_EVENTSENS_RISINGEDGE)  || \
     ((__SNS__) == HRPWM_EVENTSENS_FALLINGEDGE) || \
     ((__SNS__) == HRPWM_EVENTSENS_BOTHEDGES))

/**
  * @brief  Judge is HRPWM event A filter or not
  * @param  __FILTER__ filter to judge
  * @retval 0 isn't HRPWM event filter A
  * @retval 1 is HRPWM event filter A
  */
#define IS_HRPWM_EVENTA_FILTER(__FILTER__)   \
    (((__FILTER__) == HRPWM_EEVFLT_NONE) || \
     (((__FILTER__) & HRPWM_EEFR0_EE0FLTR) != HRPWM_EEVFLT_NONE))

/**
  * @brief  Judge is HRPWM event A latch or not
  * @param  __LATCH__ latch to judge
  * @retval 0 isn't HRPWM event A latch
  * @retval 1 is HRPWM event A latch
  */
#define IS_HRPWM_EVENTA_LATCH(__LATCH__)          \
    (((__LATCH__) == HRPWM_EVENTLATCH_DISABLE) || \
     ((__LATCH__) == HRPWM_EVENTLATCH_ENABLE))

/**
  * @brief  Judge is HRPWM event A source or not
  * @param  __SOURCE__ source to judge
  * @retval 0 isn't HRPWM event A source
  * @retval 1 is HRPWM event A source
  */
#define IS_HRPWM_EVENTA_SOURCE(__SOURCE__)         \
    (((__SOURCE__) == HRPWM_EEVASEL_SOURCE_EEVENT0) ||  \
     ((__SOURCE__) == HRPWM_EEVASEL_SOURCE_EEVENT1) ||  \
     ((__SOURCE__) == HRPWM_EEVASEL_SOURCE_EEVENT2) ||  \
     ((__SOURCE__) == HRPWM_EEVASEL_SOURCE_EEVENT3) ||  \
     ((__SOURCE__) == HRPWM_EEVASEL_SOURCE_EEVENT4) ||  \
     ((__SOURCE__) == HRPWM_EEVASEL_SOURCE_EEVENT5))

/**
  * @brief  Judge is HRPWM event A reset mode or not
  * @param  __MODE__ mode to judge
  * @retval 0 isn't HRPWM event A reset mode
  * @retval 1 is HRPWM event A reset mode
  */
#define IS_HRPWM_EVENTA_RSTMODE(__MODE__)           \
    (((__MODE__) == HRPWM_EEVARSTM_CONDITIONAL) || \
     ((__MODE__) == HRPWM_EEVARSTM_UNCONDITIONAL))

/**
  * @brief  Judge is HRPWM event A counter enable or not
  * @param  __COUNTEREN__ counter enable to judge
  * @retval 0 isn't HRPWM event A counter enable
  * @retval 1 is HRPWM event A counter enable
  */
#define IS_HRPWM_EVENTA_COUNTEREN(__COUNTEREN__)   \
    (((__COUNTEREN__) == HRPWM_EEVACOUNTER_DISABLE) || \
     ((__COUNTEREN__) == HRPWM_EEVACOUNTER_ENABLE))

/**
  * @brief  Judge is HRPWM reset event or not
  * @param  __RESET__ reset event to judge
  * @retval 0 isn't HRPWM reset event
  * @retval 1 is HRPWM reset event
  */
#define IS_HRPWM_RST_EVENT(__RESET__)             \
    (((__RESET__) == HRPWM_RESET_TRIGGER_NONE) || \
     (((__RESET__) & (0x1FFFFFFF)) != 0x0U))

/**
  * @brief  Judge is HRPWM roll over mode or not
  * @param  __ROLLOVER__ mode to judge
  * @retval 0 isn't HRPWM roll over mode
  * @retval 1 is HRPWM roll over mode
  */
#define IS_HRPWM_ROLLOVERMODE(__ROLLOVER__)      \
    (((__ROLLOVER__) == HRPWM_ROM_BOTH)       || \
     ((__ROLLOVER__) == HRPWM_ROM_ZERO)       || \
     ((__ROLLOVER__) == HRPWM_ROM_PERIOD))

/**
  * @brief  Judge is HRPWM roll over mode or not
  * @param  __ROLLOVER__ mode to judge
  * @retval 0 isn't HRPWM roll over mode
  * @retval 1 is HRPWM roll over mode
  */
#define IS_HRPWM_OUTPUTROLLOVERMODE(__ROLLOVER__)      \
    (((__ROLLOVER__) == HRPWM_OUTROM_BOTH)    || \
     ((__ROLLOVER__) == HRPWM_OUTROM_ZERO)    || \
     ((__ROLLOVER__) == HRPWM_OUTROM_PERIOD))

/**
  * @brief  Judge is HRPWM roll over mode or not
  * @param  __ROLLOVER__ mode to judge
  * @retval 0 isn't HRPWM roll over mode
  * @retval 1 is HRPWM roll over mode
  */
#define IS_HRPWM_ADCROLLOVERMODE(__ROLLOVER__)      \
    (((__ROLLOVER__) == HRPWM_ADROM_BOTH)     || \
     ((__ROLLOVER__) == HRPWM_ADROM_ZERO)     || \
     ((__ROLLOVER__) == HRPWM_ADROM_PERIOD))

/**
  * @brief  Judge is HRPWM roll over mode or not
  * @param  __ROLLOVER__ mode to judge
  * @retval 0 isn't HRPWM roll over mode
  * @retval 1 is HRPWM roll over mode
  */
#define IS_HRPWM_FLTROLLOVERMODE(__ROLLOVER__)      \
    (((__ROLLOVER__) == HRPWM_FLTROM_BOTH)    || \
     ((__ROLLOVER__) == HRPWM_FLTROM_ZERO)    || \
     ((__ROLLOVER__) == HRPWM_FLTROM_PERIOD))

/**
  * @brief  Judge is HRPWM roll over mode or not
  * @param  __ROLLOVER__ mode to judge
  * @retval 0 isn't HRPWM roll over mode
  * @retval 1 is HRPWM roll over mode
  */
#define IS_HRPWM_EVTROLLOVERMODE(__ROLLOVER__)      \
    (((__ROLLOVER__) == HRPWM_EEVROM_BOTH)    || \
     ((__ROLLOVER__) == HRPWM_EEVROM_ZERO)    || \
     ((__ROLLOVER__) == HRPWM_EEVROM_PERIOD))

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_LL_HRPWM_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

