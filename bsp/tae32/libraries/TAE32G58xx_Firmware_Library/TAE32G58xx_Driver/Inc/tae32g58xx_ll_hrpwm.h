/**
  ******************************************************************************
  * @file    tae32g58xx_ll_hrpwm.h
  * @author  MCD Application Team
  * @brief   Header file for HRPWM LL module
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
#ifndef _TAE32G58XX_LL_HRPWM_H_
#define _TAE32G58XX_LL_HRPWM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup HRPWM_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup HRPWM_LL_Exported_Constants HRPWM LL Exported Constants
  * @brief    HRPWM LL Exported Constants
  * @{
  */

#define HRPWM_COM_DLLCR_DLLTHRES0_Pos   (11UL)                  /*!< DLLTHRES0 (Bit 11)                                     */
#define HRPWM_COM_DLLCR_DLLTHRES0_Msk   (0xf800UL)              /*!< DLLTHRES0 (Bitfield-Mask: 0x1f)                        */
#define HRPWM_COM_DLLCR_DLLTHRES1_Pos   (6UL)                   /*!< DLLTHRES1 (Bit 6)                                      */
#define HRPWM_COM_DLLCR_DLLTHRES1_Msk   (0x7c0UL)               /*!< DLLTHRES1 (Bitfield-Mask: 0x1f)                        */


/**
  * @brief  Bit Long Long Type left shift definition
  * @param  pos left shift position
  * @return Bit Long Long Type left shift value
  */
#define BITLL(pos)                              (1ULL << (pos))


/**
  * @brief HRPWM Common ADC0/2 Trigger Event Source Definition
  */
#define HRPWM_Comm_ADC02TrigEvtSrcETypeDef

#define HRPWM_COMM_ADC02_TRIG_EVT_NONE              (0)                     /*!< ADC0/2 Trigger Event Source None                   */
#define HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPA      BITLL(0)                /*!< ADC0/2 Trigger Event Source Master PWM Compare A   */
#define HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPB      BITLL(1)                /*!< ADC0/2 Trigger Event Source Master PWM Compare B   */
#define HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPC      BITLL(2)                /*!< ADC0/2 Trigger Event Source Master PWM Compare C   */
#define HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_CMPD      BITLL(3)                /*!< ADC0/2 Trigger Event Source Master PWM Compare D   */
#define HRPWM_COMM_ADC02_TRIG_EVT_MST_PWM_PRD       BITLL(4)                /*!< ADC0/2 Trigger Event Source Master PWM Period      */

#define HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_0         BITLL(5)                /*!< ADC0/2 Trigger Event Source External Event 0       */
#define HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_1         BITLL(6)                /*!< ADC0/2 Trigger Event Source External Event 1       */
#define HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_2         BITLL(7)                /*!< ADC0/2 Trigger Event Source External Event 2       */
#define HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_3         BITLL(8)                /*!< ADC0/2 Trigger Event Source External Event 3       */
#define HRPWM_COMM_ADC02_TRIG_EVT_EXT_EVT_4         BITLL(9)                /*!< ADC0/2 Trigger Event Source External Event 4       */

#define HRPWM_COMM_ADC02_TRIG_EVT_PWM0_CMPC         BITLL(10)               /*!< ADC0/2 Trigger Event Source PWM0 Compare C         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM0_CMPD         BITLL(11)               /*!< ADC0/2 Trigger Event Source PWM0 Compare D         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM0_PRD          BITLL(12)               /*!< ADC0/2 Trigger Event Source PWM0 Period            */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM0_RST_ROLLOVER BITLL(13)               /*!< ADC0/2 Trigger Event Source PWM0 Reset/Roll-Over   */

#define HRPWM_COMM_ADC02_TRIG_EVT_PWM1_CMPC         BITLL(14)               /*!< ADC0/2 Trigger Event Source PWM1 Compare C         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM1_CMPD         BITLL(15)               /*!< ADC0/2 Trigger Event Source PWM1 Compare D         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM1_PRD          BITLL(16)               /*!< ADC0/2 Trigger Event Source PWM1 Period            */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM1_RST_ROLLOVE  BITLL(17)               /*!< ADC0/2 Trigger Event Source PWM1 Reset/Roll-Over   */

#define HRPWM_COMM_ADC02_TRIG_EVT_PWM2_CMPC         BITLL(18)               /*!< ADC0/2 Trigger Event Source PWM2 Compare C         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM2_CMPD         BITLL(19)               /*!< ADC0/2 Trigger Event Source PWM2 Compare D         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM2_PRD          BITLL(20)               /*!< ADC0/2 Trigger Event Source PWM2 Period            */

#define HRPWM_COMM_ADC02_TRIG_EVT_PWM3_CMPC         BITLL(21)               /*!< ADC0/2 Trigger Event Source PWM3 Compare C         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM3_CMPD         BITLL(22)               /*!< ADC0/2 Trigger Event Source PWM3 Compare D         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM3_PRD          BITLL(23)               /*!< ADC0/2 Trigger Event Source PWM3 Period            */

#define HRPWM_COMM_ADC02_TRIG_EVT_PWM4_CMPC         BITLL(24)               /*!< ADC0/2 Trigger Event Source PWM4 Compare C         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM4_CMPD         BITLL(25)               /*!< ADC0/2 Trigger Event Source PWM4 Compare D         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM4_PRD          BITLL(26)               /*!< ADC0/2 Trigger Event Source PWM4 Period            */

#define HRPWM_COMM_ADC02_TRIG_EVT_PWM5_CMPB         BITLL(27)               /*!< ADC0/2 Trigger Event Source PWM5 Compare B         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM5_CMPC         BITLL(28)               /*!< ADC0/2 Trigger Event Source PWM5 Compare C         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM5_CMPD         BITLL(29)               /*!< ADC0/2 Trigger Event Source PWM5 Compare D         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM5_PRD          BITLL(30)               /*!< ADC0/2 Trigger Event Source PWM5 Period            */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM5_RST_ROLLOVER ((uint64_t)BITLL(31))   /*!< ADC0/2 Trigger Event Source PWM5 Reset/Roll-Over   */

#define HRPWM_COMM_ADC02_TRIG_EVT_PWM6_CMPC         ((uint64_t)BITLL(32))   /*!< ADC0/2 Trigger Event Source PWM6 Compare C         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM6_CMPD         ((uint64_t)BITLL(33))   /*!< ADC0/2 Trigger Event Source PWM6 Compare D         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM6_PRD          ((uint64_t)BITLL(34))   /*!< ADC0/2 Trigger Event Source PWM6 Period            */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM6_RST_ROLLOVER ((uint64_t)BITLL(35))   /*!< ADC0/2 Trigger Event Source PWM6 Reset/Roll-Over   */

#define HRPWM_COMM_ADC02_TRIG_EVT_PWM7_CMPC         ((uint64_t)BITLL(36))   /*!< ADC0/2 Trigger Event Source PWM7 Compare C         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM7_CMPD         ((uint64_t)BITLL(37))   /*!< ADC0/2 Trigger Event Source PWM7 Compare D         */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM7_PRD          ((uint64_t)BITLL(38))   /*!< ADC0/2 Trigger Event Source PWM7 Period            */
#define HRPWM_COMM_ADC02_TRIG_EVT_PWM7_RST_ROLLOVER ((uint64_t)BITLL(39))   /*!< ADC0/2 Trigger Event Source PWM7 Reset/Roll-Over   */

/**
  * @brief HRPWM Common ADC1/3 Trigger Event Definition
  */
#define HRPWM_Comm_ADC13TrigEvtSrcETypeDef

#define HRPWM_COMM_ADC13_TRIG_EVT_NONE              (0)                     /*!< ADC1/3 Trigger Event Source None                   */
#define HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPA      BITLL(0)                /*!< ADC1/3 Trigger Event Source Master PWM Compare A   */
#define HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPB      BITLL(1)                /*!< ADC1/3 Trigger Event Source Master PWM Compare B   */
#define HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPC      BITLL(2)                /*!< ADC1/3 Trigger Event Source Master PWM Compare C   */
#define HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_CMPD      BITLL(3)                /*!< ADC1/3 Trigger Event Source Master PWM Compare D   */
#define HRPWM_COMM_ADC13_TRIG_EVT_MST_PWM_PRD       BITLL(4)                /*!< ADC1/3 Trigger Event Source Master PWM Period      */

#define HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_5         BITLL(5)                /*!< ADC1/3 Trigger Event Source External Event 5       */
#define HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_6         BITLL(6)                /*!< ADC1/3 Trigger Event Source External Event 6       */
#define HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_7         BITLL(7)                /*!< ADC1/3 Trigger Event Source External Event 7       */
#define HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_8         BITLL(8)                /*!< ADC1/3 Trigger Event Source External Event 8       */
#define HRPWM_COMM_ADC13_TRIG_EVT_EXT_EVT_9         BITLL(9)                /*!< ADC1/3 Trigger Event Source External Event 9       */

#define HRPWM_COMM_ADC13_TRIG_EVT_PWM0_CMPB         BITLL(10)               /*!< ADC1/3 Trigger Event Source PWM0 Compare B         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM0_CMPD         BITLL(11)               /*!< ADC1/3 Trigger Event Source PWM0 Compare D         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM0_PRD          BITLL(12)               /*!< ADC1/3 Trigger Event Source PWM0 Period            */

#define HRPWM_COMM_ADC13_TRIG_EVT_PWM1_CMPB         BITLL(13)               /*!< ADC1/3 Trigger Event Source PWM1 Compare B         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM1_CMPD         BITLL(14)               /*!< ADC1/3 Trigger Event Source PWM1 Compare D         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM1_PRD          BITLL(15)               /*!< ADC1/3 Trigger Event Source PWM1 Period            */

#define HRPWM_COMM_ADC13_TRIG_EVT_PWM2_CMPB         BITLL(16)               /*!< ADC1/3 Trigger Event Source PWM2 Compare B         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM2_CMPD         BITLL(17)               /*!< ADC1/3 Trigger Event Source PWM2 Compare D         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM2_PRD          BITLL(18)               /*!< ADC1/3 Trigger Event Source PWM2 Period            */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM2_RST_ROLLOVER BITLL(19)               /*!< ADC1/3 Trigger Event Source PWM2 Reset/Roll-Over   */

#define HRPWM_COMM_ADC13_TRIG_EVT_PWM3_CMPB         BITLL(20)               /*!< ADC1/3 Trigger Event Source PWM3 Compare B         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM3_CMPD         BITLL(21)               /*!< ADC1/3 Trigger Event Source PWM3 Compare D         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM3_PRD          BITLL(22)               /*!< ADC1/3 Trigger Event Source PWM3 Period            */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM3_RST_ROLLOVER BITLL(23)               /*!< ADC1/3 Trigger Event Source PWM3 Reset/Roll-Over   */

#define HRPWM_COMM_ADC13_TRIG_EVT_PWM4_CMPB         BITLL(24)               /*!< ADC1/3 Trigger Event Source PWM4 Compare B         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM4_CMPC         BITLL(25)               /*!< ADC1/3 Trigger Event Source PWM4 Compare C         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM4_CMPD         BITLL(26)               /*!< ADC1/3 Trigger Event Source PWM4 Compare D         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM4_RST_ROLLOVER BITLL(27)               /*!< ADC1/3 Trigger Event Source PWM4 Reset/Roll-Over   */

#define HRPWM_COMM_ADC13_TRIG_EVT_PWM5_CMPB         BITLL(28)               /*!< ADC1/3 Trigger Event Source PWM5 Compare B         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM5_CMPC         BITLL(29)               /*!< ADC1/3 Trigger Event Source PWM5 Compare C         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM5_CMPD         BITLL(30)               /*!< ADC1/3 Trigger Event Source PWM5 Compare D         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM5_PRD          ((uint64_t)BITLL(31))   /*!< ADC1/3 Trigger Event Source PWM5 Period            */

#define HRPWM_COMM_ADC13_TRIG_EVT_PWM6_CMPB         ((uint64_t)BITLL(32))   /*!< ADC1/3 Trigger Event Source PWM6 Compare B         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM6_CMPD         ((uint64_t)BITLL(33))   /*!< ADC1/3 Trigger Event Source PWM6 Compare D         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM6_PRD          ((uint64_t)BITLL(34))   /*!< ADC1/3 Trigger Event Source PWM6 Period            */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM6_RST_ROLLOVER ((uint64_t)BITLL(35))   /*!< ADC1/3 Trigger Event Source PWM6 Reset/Roll-Over   */

#define HRPWM_COMM_ADC13_TRIG_EVT_PWM7_CMPB         ((uint64_t)BITLL(36))   /*!< ADC1/3 Trigger Event Source PWM7 Compare B         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM7_CMPD         ((uint64_t)BITLL(37))   /*!< ADC1/3 Trigger Event Source PWM7 Compare D         */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM7_PRD          ((uint64_t)BITLL(38))   /*!< ADC1/3 Trigger Event Source PWM7 Period            */
#define HRPWM_COMM_ADC13_TRIG_EVT_PWM7_RST_ROLLOVER ((uint64_t)BITLL(39))   /*!< ADC1/3 Trigger Event Source PWM7 Reset/Roll-Over   */


/**
  * @brief HRPWM Slave0 Counter Reset Event Definition
  */
#define HRPWM_Slv0_CntrRstEvtETypeDef

#define HRPWM_SLV0_CNTR_RST_EVT_NONE            (0)                 /*!< Slave0 Counter Reset Event None                    */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM5_CMPA       BITLL(0)            /*!< Slave0 Counter Reset Event PWM5 Compare A          */

#define HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave0 Counter Reset Event Master PWM Compare A    */
#define HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave0 Counter Reset Event Master PWM Compare B    */
#define HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave0 Counter Reset Event Master PWM Compare C    */
#define HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave0 Counter Reset Event Master PWM Compare D    */
#define HRPWM_SLV0_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave0 Counter Reset Event Master PWM Period       */

#define HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave0 Counter Reset Event PWMx Event 0            */
#define HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave0 Counter Reset Event PWMx Event 1            */
#define HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave0 Counter Reset Event PWMx Event 2            */
#define HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave0 Counter Reset Event PWMx Event 3            */
#define HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave0 Counter Reset Event PWMx Event 4            */
#define HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave0 Counter Reset Event PWMx Event 5            */
#define HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave0 Counter Reset Event PWMx Event 6            */
#define HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave0 Counter Reset Event PWMx Event 7            */
#define HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave0 Counter Reset Event PWMx Event 8            */
#define HRPWM_SLV0_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave0 Counter Reset Event PWMx Event 9            */
#define HRPWM_SLV0_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave0 Counter Reset Event PWMx Update             */

#define HRPWM_SLV0_CNTR_RST_EVT_PWM0_CMPB       BITLL(17)           /*!< Slave0 Counter Reset Event PWM0 Compare B          */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM0_CMPD       BITLL(18)           /*!< Slave0 Counter Reset Event PWM0 Compare D          */

#define HRPWM_SLV0_CNTR_RST_EVT_PWM1_CMPA       BITLL(19)           /*!< Slave0 Counter Reset Event PWM1 Compare A          */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM1_CMPB       BITLL(20)           /*!< Slave0 Counter Reset Event PWM1 Compare B          */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM1_CMPD       BITLL(21)           /*!< Slave0 Counter Reset Event PWM1 Compare D          */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave0 Counter Reset Event PWM2 Compare A          */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave0 Counter Reset Event PWM2 Compare B          */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM2_CMPD       BITLL(24)           /*!< Slave0 Counter Reset Event PWM2 Compare D          */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM3_CMPA       BITLL(25)           /*!< Slave0 Counter Reset Event PWM3 Compare A          */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM3_CMPB       BITLL(26)           /*!< Slave0 Counter Reset Event PWM3 Compare B          */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM3_CMPD       BITLL(27)           /*!< Slave0 Counter Reset Event PWM3 Compare D          */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM4_CMPA       BITLL(28)           /*!< Slave0 Counter Reset Event PWM4 Compare A          */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM4_CMPB       BITLL(29)           /*!< Slave0 Counter Reset Event PWM4 Compare B          */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM4_CMPD       BITLL(30)           /*!< Slave0 Counter Reset Event PWM4 Compare D          */

#define HRPWM_SLV0_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31)))  /*!< Slave0 Counter Reset Event PWM5 Compare B     */

#define HRPWM_SLV0_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(32)))  /*!< Slave0 Counter Reset Event PWM6 Compare A     */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(33)))  /*!< Slave0 Counter Reset Event PWM6 Compare B     */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(34)))  /*!< Slave0 Counter Reset Event PWM6 Compare D     */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35)))  /*!< Slave0 Counter Reset Event PWM7 Compare A     */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36)))  /*!< Slave0 Counter Reset Event PWM7 Compare B     */
#define HRPWM_SLV0_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37)))  /*!< Slave0 Counter Reset Event PWM7 Compare D     */

/**
  * @brief HRPWM Slave1 Counter Reset Event Definition
  */
#define HRPWM_Slv1_CntrRstEvtETypeDef

#define HRPWM_SLV1_CNTR_RST_EVT_NONE            (0)                 /*!< Slave1 Counter Reset Event None                    */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM5_CMPA       BITLL(0)            /*!< Slave1 Counter Reset Event PWM5 Compare A          */

#define HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave1 Counter Reset Event Master PWM Compare A    */
#define HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave1 Counter Reset Event Master PWM Compare B    */
#define HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave1 Counter Reset Event Master PWM Compare C    */
#define HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave1 Counter Reset Event Master PWM Compare D    */
#define HRPWM_SLV1_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave1 Counter Reset Event Master PWM Period       */

#define HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave1 Counter Reset Event PWMx Event 0            */
#define HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave1 Counter Reset Event PWMx Event 1            */
#define HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave1 Counter Reset Event PWMx Event 2            */
#define HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave1 Counter Reset Event PWMx Event 3            */
#define HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave1 Counter Reset Event PWMx Event 4            */
#define HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave1 Counter Reset Event PWMx Event 5            */
#define HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave1 Counter Reset Event PWMx Event 6            */
#define HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave1 Counter Reset Event PWMx Event 7            */
#define HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave1 Counter Reset Event PWMx Event 8            */
#define HRPWM_SLV1_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave1 Counter Reset Event PWMx Event 9            */
#define HRPWM_SLV1_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave1 Counter Reset Event PWMx Update             */

#define HRPWM_SLV1_CNTR_RST_EVT_PWM1_CMPB       BITLL(17)           /*!< Slave1 Counter Reset Event PWM1 Compare B          */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM1_CMPD       BITLL(18)           /*!< Slave1 Counter Reset Event PWM1 Compare D          */

#define HRPWM_SLV1_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave1 Counter Reset Event PWM0 Compare A          */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave1 Counter Reset Event PWM0 Compare B          */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave1 Counter Reset Event PWM0 Compare D          */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave1 Counter Reset Event PWM2 Compare A          */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave1 Counter Reset Event PWM2 Compare B          */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM2_CMPD       BITLL(24)           /*!< Slave1 Counter Reset Event PWM2 Compare D          */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM3_CMPA       BITLL(25)           /*!< Slave1 Counter Reset Event PWM3 Compare A          */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM3_CMPB       BITLL(26)           /*!< Slave1 Counter Reset Event PWM3 Compare B          */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM3_CMPD       BITLL(27)           /*!< Slave1 Counter Reset Event PWM3 Compare D          */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM4_CMPA       BITLL(28)           /*!< Slave1 Counter Reset Event PWM4 Compare A          */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM4_CMPB       BITLL(29)           /*!< Slave1 Counter Reset Event PWM4 Compare B          */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM4_CMPD       BITLL(30)           /*!< Slave1 Counter Reset Event PWM4 Compare D          */

#define HRPWM_SLV1_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave1 Counter Reset Event PWM5 Compare B      */

#define HRPWM_SLV1_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(32))) /*!< Slave1 Counter Reset Event PWM6 Compare A      */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(33))) /*!< Slave1 Counter Reset Event PWM6 Compare B      */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(34))) /*!< Slave1 Counter Reset Event PWM6 Compare D      */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35))) /*!< Slave1 Counter Reset Event PWM7 Compare A      */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36))) /*!< Slave1 Counter Reset Event PWM7 Compare B      */
#define HRPWM_SLV1_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37))) /*!< Slave1 Counter Reset Event PWM7 Compare D      */

/**
  * @brief HRPWM Slave2 Counter Reset Event Definition
  */
#define HRPWM_Slv2_CntrRstEvtETypeDef

#define HRPWM_SLV2_CNTR_RST_EVT_NONE            (0)                 /*!< Slave2 Counter Reset Event None                    */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM5_CMPA       BITLL(0)            /*!< Slave2 Counter Reset Event PWM5 Compare A          */

#define HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave2 Counter Reset Event Master PWM Compare A    */
#define HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave2 Counter Reset Event Master PWM Compare B    */
#define HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave2 Counter Reset Event Master PWM Compare C    */
#define HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave2 Counter Reset Event Master PWM Compare D    */
#define HRPWM_SLV2_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave2 Counter Reset Event Master PWM Period       */

#define HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave2 Counter Reset Event PWMx Event 0            */
#define HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave2 Counter Reset Event PWMx Event 1            */
#define HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave2 Counter Reset Event PWMx Event 2            */
#define HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave2 Counter Reset Event PWMx Event 3            */
#define HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave2 Counter Reset Event PWMx Event 4            */
#define HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave2 Counter Reset Event PWMx Event 5            */
#define HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave2 Counter Reset Event PWMx Event 6            */
#define HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave2 Counter Reset Event PWMx Event 7            */
#define HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave2 Counter Reset Event PWMx Event 8            */
#define HRPWM_SLV2_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave2 Counter Reset Event PWMx Event 9            */
#define HRPWM_SLV2_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave2 Counter Reset Event PWMx Update             */

#define HRPWM_SLV2_CNTR_RST_EVT_PWM2_CMPB       BITLL(17)           /*!< Slave2 Counter Reset Event PWM2 Compare B          */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM2_CMPD       BITLL(18)           /*!< Slave2 Counter Reset Event PWM2 Compare D          */

#define HRPWM_SLV2_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave2 Counter Reset Event PWM0 Compare A          */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave2 Counter Reset Event PWM0 Compare B          */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave2 Counter Reset Event PWM0 Compare D          */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM1_CMPA       BITLL(22)           /*!< Slave2 Counter Reset Event PWM1 Compare A          */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM1_CMPB       BITLL(23)           /*!< Slave2 Counter Reset Event PWM1 Compare B          */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM1_CMPD       BITLL(24)           /*!< Slave2 Counter Reset Event PWM1 Compare D          */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM3_CMPA       BITLL(25)           /*!< Slave2 Counter Reset Event PWM3 Compare A          */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM3_CMPB       BITLL(26)           /*!< Slave2 Counter Reset Event PWM3 Compare B          */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM3_CMPD       BITLL(27)           /*!< Slave2 Counter Reset Event PWM3 Compare D          */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM4_CMPA       BITLL(28)           /*!< Slave2 Counter Reset Event PWM4 Compare A          */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM4_CMPB       BITLL(29)           /*!< Slave2 Counter Reset Event PWM4 Compare B          */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM4_CMPD       BITLL(30)           /*!< Slave2 Counter Reset Event PWM4 Compare D          */

#define HRPWM_SLV2_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave2 Counter Reset Event PWM5 Compare B      */

#define HRPWM_SLV2_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(32))) /*!< Slave2 Counter Reset Event PWM6 Compare A      */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(33))) /*!< Slave2 Counter Reset Event PWM6 Compare B      */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(34))) /*!< Slave2 Counter Reset Event PWM6 Compare D      */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35))) /*!< Slave2 Counter Reset Event PWM7 Compare A      */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36))) /*!< Slave2 Counter Reset Event PWM7 Compare B      */
#define HRPWM_SLV2_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37))) /*!< Slave2 Counter Reset Event PWM7 Compare D      */

/**
  * @brief HRPWM Slave3 Counter Reset Event Definition
  */
#define HRPWM_Slv3_CntrRstEvtETypeDef

#define HRPWM_SLV3_CNTR_RST_EVT_NONE            (0)                 /*!< Slave3 Counter Reset Event None                    */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM5_CMPA       BITLL(0)            /*!< Slave3 Counter Reset Event PWM5 Compare A          */

#define HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave3 Counter Reset Event Master PWM Compare A    */
#define HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave3 Counter Reset Event Master PWM Compare B    */
#define HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave3 Counter Reset Event Master PWM Compare C    */
#define HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave3 Counter Reset Event Master PWM Compare D    */
#define HRPWM_SLV3_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave3 Counter Reset Event Master PWM Period       */

#define HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave3 Counter Reset Event PWMx Event 0            */
#define HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave3 Counter Reset Event PWMx Event 1            */
#define HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave3 Counter Reset Event PWMx Event 2            */
#define HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave3 Counter Reset Event PWMx Event 3            */
#define HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave3 Counter Reset Event PWMx Event 4            */
#define HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave3 Counter Reset Event PWMx Event 5            */
#define HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave3 Counter Reset Event PWMx Event 6            */
#define HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave3 Counter Reset Event PWMx Event 7            */
#define HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave3 Counter Reset Event PWMx Event 8            */
#define HRPWM_SLV3_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave3 Counter Reset Event PWMx Event 9            */
#define HRPWM_SLV3_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave3 Counter Reset Event PWMx Update             */

#define HRPWM_SLV3_CNTR_RST_EVT_PWM3_CMPB       BITLL(17)           /*!< Slave3 Counter Reset Event PWM3 Compare B          */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM3_CMPD       BITLL(18)           /*!< Slave3 Counter Reset Event PWM3 Compare D          */

#define HRPWM_SLV3_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave3 Counter Reset Event PWM0 Compare A          */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave3 Counter Reset Event PWM0 Compare B          */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave3 Counter Reset Event PWM0 Compare D          */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM1_CMPA       BITLL(22)           /*!< Slave3 Counter Reset Event PWM1 Compare A          */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM1_CMPB       BITLL(23)           /*!< Slave3 Counter Reset Event PWM1 Compare B          */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM1_CMPD       BITLL(24)           /*!< Slave3 Counter Reset Event PWM1 Compare D          */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM2_CMPA       BITLL(25)           /*!< Slave3 Counter Reset Event PWM2 Compare A          */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM2_CMPB       BITLL(26)           /*!< Slave3 Counter Reset Event PWM2 Compare B          */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM2_CMPD       BITLL(27)           /*!< Slave3 Counter Reset Event PWM2 Compare D          */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM4_CMPA       BITLL(28)           /*!< Slave3 Counter Reset Event PWM4 Compare A          */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM4_CMPB       BITLL(29)           /*!< Slave3 Counter Reset Event PWM4 Compare B          */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM4_CMPD       BITLL(30)           /*!< Slave3 Counter Reset Event PWM4 Compare D          */

#define HRPWM_SLV3_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave3 Counter Reset Event PWM5 Compare B      */

#define HRPWM_SLV3_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(32))) /*!< Slave3 Counter Reset Event PWM6 Compare A      */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(33))) /*!< Slave3 Counter Reset Event PWM6 Compare B      */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(34))) /*!< Slave3 Counter Reset Event PWM6 Compare D      */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35))) /*!< Slave3 Counter Reset Event PWM7 Compare A      */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36))) /*!< Slave3 Counter Reset Event PWM7 Compare B      */
#define HRPWM_SLV3_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37))) /*!< Slave3 Counter Reset Event PWM7 Compare D      */

/**
  * @brief HRPWM Slave4 Counter Reset Event Definition
  */
#define HRPWM_Slv4_CntrRstEvtETypeDef

#define HRPWM_SLV4_CNTR_RST_EVT_NONE            (0)                 /*!< Slave4 Counter Reset Event None                    */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM5_CMPA       BITLL(0)            /*!< Slave4 Counter Reset Event PWM5 Compare A          */

#define HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave4 Counter Reset Event Master PWM Compare A    */
#define HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave4 Counter Reset Event Master PWM Compare B    */
#define HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave4 Counter Reset Event Master PWM Compare C    */
#define HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave4 Counter Reset Event Master PWM Compare D    */
#define HRPWM_SLV4_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave4 Counter Reset Event Master PWM Period       */

#define HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave4 Counter Reset Event PWMx Event 0            */
#define HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave4 Counter Reset Event PWMx Event 1            */
#define HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave4 Counter Reset Event PWMx Event 2            */
#define HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave4 Counter Reset Event PWMx Event 3            */
#define HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave4 Counter Reset Event PWMx Event 4            */
#define HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave4 Counter Reset Event PWMx Event 5            */
#define HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave4 Counter Reset Event PWMx Event 6            */
#define HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave4 Counter Reset Event PWMx Event 7            */
#define HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave4 Counter Reset Event PWMx Event 8            */
#define HRPWM_SLV4_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave4 Counter Reset Event PWMx Event 9            */
#define HRPWM_SLV4_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave4 Counter Reset Event PWMx Update             */

#define HRPWM_SLV4_CNTR_RST_EVT_PWM4_CMPB       BITLL(17)           /*!< Slave4 Counter Reset Event PWM4 Compare B          */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM4_CMPD       BITLL(18)           /*!< Slave4 Counter Reset Event PWM4 Compare D          */

#define HRPWM_SLV4_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave4 Counter Reset Event PWM0 Compare A          */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave4 Counter Reset Event PWM0 Compare B          */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave4 Counter Reset Event PWM0 Compare D          */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM1_CMPA       BITLL(22)           /*!< Slave4 Counter Reset Event PWM1 Compare A          */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM1_CMPB       BITLL(23)           /*!< Slave4 Counter Reset Event PWM1 Compare B          */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM1_CMPD       BITLL(24)           /*!< Slave4 Counter Reset Event PWM1 Compare D          */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM2_CMPA       BITLL(25)           /*!< Slave4 Counter Reset Event PWM2 Compare A          */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM2_CMPB       BITLL(26)           /*!< Slave4 Counter Reset Event PWM2 Compare B          */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM2_CMPD       BITLL(27)           /*!< Slave4 Counter Reset Event PWM2 Compare D          */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM3_CMPA       BITLL(28)           /*!< Slave4 Counter Reset Event PWM3 Compare A          */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM3_CMPB       BITLL(29)           /*!< Slave4 Counter Reset Event PWM3 Compare B          */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM3_CMPD       BITLL(30)           /*!< Slave4 Counter Reset Event PWM3 Compare D          */

#define HRPWM_SLV4_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31)))  /*!< Slave4 Counter Reset Event PWM5 Compare B     */

#define HRPWM_SLV4_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(32)))  /*!< Slave4 Counter Reset Event PWM6 Compare A     */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(33)))  /*!< Slave4 Counter Reset Event PWM6 Compare B     */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(34)))  /*!< Slave4 Counter Reset Event PWM6 Compare D     */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35)))  /*!< Slave4 Counter Reset Event PWM7 Compare A     */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36)))  /*!< Slave4 Counter Reset Event PWM7 Compare B     */
#define HRPWM_SLV4_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37)))  /*!< Slave4 Counter Reset Event PWM7 Compare D     */

/**
  * @brief HRPWM Slave5 Counter Reset Event Definition
  */
#define HRPWM_Slv5_CntrRstEvtETypeDef

#define HRPWM_SLV5_CNTR_RST_EVT_NONE            (0)                 /*!< Slave5 Counter Reset Event None                    */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM4_CMPA       BITLL(0)            /*!< Slave5 Counter Reset Event PWM4 Compare A          */

#define HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave5 Counter Reset Event Master PWM Compare A    */
#define HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave5 Counter Reset Event Master PWM Compare B    */
#define HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave5 Counter Reset Event Master PWM Compare C    */
#define HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave5 Counter Reset Event Master PWM Compare D    */
#define HRPWM_SLV5_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave5 Counter Reset Event Master PWM Period       */

#define HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave5 Counter Reset Event PWMx Event 0            */
#define HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave5 Counter Reset Event PWMx Event 1            */
#define HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave5 Counter Reset Event PWMx Event 2            */
#define HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave5 Counter Reset Event PWMx Event 3            */
#define HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave5 Counter Reset Event PWMx Event 4            */
#define HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave5 Counter Reset Event PWMx Event 5            */
#define HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave5 Counter Reset Event PWMx Event 6            */
#define HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave5 Counter Reset Event PWMx Event 7            */
#define HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave5 Counter Reset Event PWMx Event 8            */
#define HRPWM_SLV5_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave5 Counter Reset Event PWMx Event 9            */
#define HRPWM_SLV5_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave5 Counter Reset Event PWMx Update             */

#define HRPWM_SLV5_CNTR_RST_EVT_PWM5_CMPB       BITLL(17)           /*!< Slave5 Counter Reset Event PWM5 Compare B          */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM5_CMPD       BITLL(18)           /*!< Slave5 Counter Reset Event PWM5 Compare D          */

#define HRPWM_SLV5_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave5 Counter Reset Event PWM0 Compare A          */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave5 Counter Reset Event PWM0 Compare B          */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave5 Counter Reset Event PWM0 Compare D          */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM1_CMPA       BITLL(22)           /*!< Slave5 Counter Reset Event PWM1 Compare A          */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM1_CMPB       BITLL(23)           /*!< Slave5 Counter Reset Event PWM1 Compare B          */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM1_CMPD       BITLL(24)           /*!< Slave5 Counter Reset Event PWM1 Compare D          */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM2_CMPA       BITLL(25)           /*!< Slave5 Counter Reset Event PWM2 Compare A          */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM2_CMPB       BITLL(26)           /*!< Slave5 Counter Reset Event PWM2 Compare B          */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM2_CMPD       BITLL(27)           /*!< Slave5 Counter Reset Event PWM2 Compare D          */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM3_CMPA       BITLL(28)           /*!< Slave5 Counter Reset Event PWM3 Compare A          */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM3_CMPB       BITLL(29)           /*!< Slave5 Counter Reset Event PWM3 Compare B          */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM3_CMPD       BITLL(30)           /*!< Slave5 Counter Reset Event PWM3 Compare D          */

#define HRPWM_SLV5_CNTR_RST_EVT_PWM4_CMPB       ((uint64_t)(BITLL(31)))  /*!< Slave5 Counter Reset Event PWM4 Compare B     */

#define HRPWM_SLV5_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(32)))  /*!< Slave5 Counter Reset Event PWM6 Compare A     */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(33)))  /*!< Slave5 Counter Reset Event PWM6 Compare B     */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(34)))  /*!< Slave5 Counter Reset Event PWM6 Compare D     */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35)))  /*!< Slave5 Counter Reset Event PWM7 Compare A     */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36)))  /*!< Slave5 Counter Reset Event PWM7 Compare B     */
#define HRPWM_SLV5_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37)))  /*!< Slave5 Counter Reset Event PWM7 Compare D     */

/**
  * @brief HRPWM Slave6 Counter Reset Event Definition
  */
#define HRPWM_Slv6_CntrRstEvtETypeDef

#define HRPWM_SLV6_CNTR_RST_EVT_NONE            (0)                 /*!< Slave6 Counter Reset Event None                    */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM4_CMPA       BITLL(0)            /*!< Slave6 Counter Reset Event PWM4 Compare A          */

#define HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave6 Counter Reset Event Master PWM Compare A    */
#define HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave6 Counter Reset Event Master PWM Compare B    */
#define HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave6 Counter Reset Event Master PWM Compare C    */
#define HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave6 Counter Reset Event Master PWM Compare D    */
#define HRPWM_SLV6_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave6 Counter Reset Event Master PWM Period       */

#define HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave6 Counter Reset Event PWMx Event 0            */
#define HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave6 Counter Reset Event PWMx Event 1            */
#define HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave6 Counter Reset Event PWMx Event 2            */
#define HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave6 Counter Reset Event PWMx Event 3            */
#define HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave6 Counter Reset Event PWMx Event 4            */
#define HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave6 Counter Reset Event PWMx Event 5            */
#define HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave6 Counter Reset Event PWMx Event 6            */
#define HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave6 Counter Reset Event PWMx Event 7            */
#define HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave6 Counter Reset Event PWMx Event 8            */
#define HRPWM_SLV6_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave6 Counter Reset Event PWMx Event 9            */
#define HRPWM_SLV6_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave6 Counter Reset Event PWMx Update             */

#define HRPWM_SLV6_CNTR_RST_EVT_PWM6_CMPB       BITLL(17)           /*!< Slave6 Counter Reset Event PWM6 Compare B          */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM6_CMPD       BITLL(18)           /*!< Slave6 Counter Reset Event PWM6 Compare D          */

#define HRPWM_SLV6_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave6 Counter Reset Event PWM0 Compare A          */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave6 Counter Reset Event PWM0 Compare B          */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave6 Counter Reset Event PWM0 Compare D          */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM1_CMPA       BITLL(22)           /*!< Slave6 Counter Reset Event PWM1 Compare A          */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM1_CMPB       BITLL(23)           /*!< Slave6 Counter Reset Event PWM1 Compare B          */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM1_CMPD       BITLL(24)           /*!< Slave6 Counter Reset Event PWM1 Compare D          */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM2_CMPA       BITLL(25)           /*!< Slave6 Counter Reset Event PWM2 Compare A          */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM2_CMPB       BITLL(26)           /*!< Slave6 Counter Reset Event PWM2 Compare B          */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM2_CMPD       BITLL(27)           /*!< Slave6 Counter Reset Event PWM2 Compare D          */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM3_CMPA       BITLL(28)           /*!< Slave6 Counter Reset Event PWM3 Compare A          */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM3_CMPB       BITLL(29)           /*!< Slave6 Counter Reset Event PWM3 Compare B          */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM3_CMPD       BITLL(30)           /*!< Slave6 Counter Reset Event PWM3 Compare D          */

#define HRPWM_SLV6_CNTR_RST_EVT_PWM4_CMPB       ((uint64_t)(BITLL(31)))  /*!< Slave6 Counter Reset Event PWM4 Compare B     */

#define HRPWM_SLV6_CNTR_RST_EVT_PWM5_CMPA       ((uint64_t)(BITLL(32)))  /*!< Slave6 Counter Reset Event PWM5 Compare A     */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(33)))  /*!< Slave6 Counter Reset Event PWM5 Compare B     */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM5_CMPD       ((uint64_t)(BITLL(34)))  /*!< Slave6 Counter Reset Event PWM5 Compare D     */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM7_CMPA       ((uint64_t)(BITLL(35)))  /*!< Slave6 Counter Reset Event PWM7 Compare A     */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM7_CMPB       ((uint64_t)(BITLL(36)))  /*!< Slave6 Counter Reset Event PWM7 Compare B     */
#define HRPWM_SLV6_CNTR_RST_EVT_PWM7_CMPD       ((uint64_t)(BITLL(37)))  /*!< Slave6 Counter Reset Event PWM7 Compare D     */

/**
  * @brief HRPWM Slave7 Counter Reset Event Definition
  */
#define HRPWM_Slv7_CntrRstEvtETypeDef

#define HRPWM_SLV7_CNTR_RST_EVT_NONE            (0)                 /*!< Slave7 Counter Reset Event None                    */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM4_CMPA       BITLL(0)            /*!< Slave7 Counter Reset Event PWM4 Compare A          */

#define HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPA    BITLL(1)            /*!< Slave7 Counter Reset Event Master PWM Compare A    */
#define HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPB    BITLL(2)            /*!< Slave7 Counter Reset Event Master PWM Compare B    */
#define HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPC    BITLL(3)            /*!< Slave7 Counter Reset Event Master PWM Compare C    */
#define HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_CMPD    BITLL(4)            /*!< Slave7 Counter Reset Event Master PWM Compare D    */
#define HRPWM_SLV7_CNTR_RST_EVT_MST_PWM_PRD     BITLL(5)            /*!< Slave7 Counter Reset Event Master PWM Period       */

#define HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT0       BITLL(6)            /*!< Slave7 Counter Reset Event PWMx Event 0            */
#define HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT1       BITLL(7)            /*!< Slave7 Counter Reset Event PWMx Event 1            */
#define HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT2       BITLL(8)            /*!< Slave7 Counter Reset Event PWMx Event 2            */
#define HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT3       BITLL(9)            /*!< Slave7 Counter Reset Event PWMx Event 3            */
#define HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT4       BITLL(10)           /*!< Slave7 Counter Reset Event PWMx Event 4            */
#define HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT5       BITLL(11)           /*!< Slave7 Counter Reset Event PWMx Event 5            */
#define HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT6       BITLL(12)           /*!< Slave7 Counter Reset Event PWMx Event 6            */
#define HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT7       BITLL(13)           /*!< Slave7 Counter Reset Event PWMx Event 7            */
#define HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT8       BITLL(14)           /*!< Slave7 Counter Reset Event PWMx Event 8            */
#define HRPWM_SLV7_CNTR_RST_EVT_PWMx_EVT9       BITLL(15)           /*!< Slave7 Counter Reset Event PWMx Event 9            */
#define HRPWM_SLV7_CNTR_RST_EVT_PWMx_UPD        BITLL(16)           /*!< Slave7 Counter Reset Event PWMx Update             */

#define HRPWM_SLV7_CNTR_RST_EVT_PWM7_CMPB       BITLL(17)           /*!< Slave7 Counter Reset Event PWM7 Compare B          */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM7_CMPD       BITLL(18)           /*!< Slave7 Counter Reset Event PWM7 Compare D          */

#define HRPWM_SLV7_CNTR_RST_EVT_PWM0_CMPA       BITLL(19)           /*!< Slave7 Counter Reset Event PWM0 Compare A          */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM0_CMPB       BITLL(20)           /*!< Slave7 Counter Reset Event PWM0 Compare B          */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM0_CMPD       BITLL(21)           /*!< Slave7 Counter Reset Event PWM0 Compare D          */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM1_CMPA       BITLL(22)           /*!< Slave7 Counter Reset Event PWM1 Compare A          */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM1_CMPB       BITLL(23)           /*!< Slave7 Counter Reset Event PWM1 Compare B          */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM1_CMPD       BITLL(24)           /*!< Slave7 Counter Reset Event PWM1 Compare D          */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM2_CMPA       BITLL(25)           /*!< Slave7 Counter Reset Event PWM2 Compare A          */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM2_CMPB       BITLL(26)           /*!< Slave7 Counter Reset Event PWM2 Compare B          */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM2_CMPD       BITLL(27)           /*!< Slave7 Counter Reset Event PWM2 Compare D          */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM3_CMPA       BITLL(28)           /*!< Slave7 Counter Reset Event PWM3 Compare A          */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM3_CMPB       BITLL(29)           /*!< Slave7 Counter Reset Event PWM3 Compare B          */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM3_CMPD       BITLL(30)           /*!< Slave7 Counter Reset Event PWM3 Compare D          */

#define HRPWM_SLV7_CNTR_RST_EVT_PWM4_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave7 Counter Reset Event PWM4 Compare B      */

#define HRPWM_SLV7_CNTR_RST_EVT_PWM5_CMPA       ((uint64_t)(BITLL(32))) /*!< Slave7 Counter Reset Event PWM5 Compare A      */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM5_CMPB       ((uint64_t)(BITLL(33))) /*!< Slave7 Counter Reset Event PWM5 Compare B      */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM5_CMPD       ((uint64_t)(BITLL(34))) /*!< Slave7 Counter Reset Event PWM5 Compare D      */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM6_CMPA       ((uint64_t)(BITLL(35))) /*!< Slave7 Counter Reset Event PWM6 Compare A      */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM6_CMPB       ((uint64_t)(BITLL(36))) /*!< Slave7 Counter Reset Event PWM6 Compare B      */
#define HRPWM_SLV7_CNTR_RST_EVT_PWM6_CMPD       ((uint64_t)(BITLL(37))) /*!< Slave7 Counter Reset Event PWM6 Compare D      */


/**
  * @brief HRPWM Slave0 Capture A/B Trigger Event Definition
  */
#define HRPWM_Slv0_CapTrigEvtETypeDef

#define HRPWM_SLV0_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave0 Capture A/B Trigger Event None              */
#define HRPWM_SLV0_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave0 Capture A/B Trigger Event Software Capture  */

#define HRPWM_SLV0_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave0 Capture A/B Trigger Event PWMx Update       */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 0      */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 1      */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 2      */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 3      */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 4      */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 5      */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 6      */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave0 Capture A/B Trigger Event PWMx Event 7      */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave0 Capture A/B Trigger Event PWMx Event 8      */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave0 Capture A/B Trigger Event PWMx Event 9      */

#define HRPWM_SLV0_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(12)           /*!< Slave0 Capture A/B Trigger Event PWM1 OutA Set     */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(13)           /*!< Slave0 Capture A/B Trigger Event PWM1 OutA Clear   */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM1_CMPA       BITLL(14)           /*!< Slave0 Capture A/B Trigger Event PWM1 Compare A    */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM1_CMPB       BITLL(15)           /*!< Slave0 Capture A/B Trigger Event PWM1 Compare B    */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(16)           /*!< Slave0 Capture A/B Trigger Event PWM2 OutA Set     */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(17)           /*!< Slave0 Capture A/B Trigger Event PWM2 OutA Clear   */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM2_CMPA       BITLL(18)           /*!< Slave0 Capture A/B Trigger Event PWM2 Compare A    */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM2_CMPB       BITLL(19)           /*!< Slave0 Capture A/B Trigger Event PWM2 Compare B    */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(20)           /*!< Slave0 Capture A/B Trigger Event PWM3 OutA Set     */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(21)           /*!< Slave0 Capture A/B Trigger Event PWM3 OutA Clear   */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM3_CMPA       BITLL(22)           /*!< Slave0 Capture A/B Trigger Event PWM3 Compare A    */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM3_CMPB       BITLL(23)           /*!< Slave0 Capture A/B Trigger Event PWM3 Compare B    */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(24)           /*!< Slave0 Capture A/B Trigger Event PWM4 OutA Set     */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(25)           /*!< Slave0 Capture A/B Trigger Event PWM4 OutA Clear   */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM4_CMPA       BITLL(26)           /*!< Slave0 Capture A/B Trigger Event PWM4 Compare A    */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM4_CMPB       BITLL(27)           /*!< Slave0 Capture A/B Trigger Event PWM4 Compare B    */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM5_OUTA_SET   BITLL(28)           /*!< Slave0 Capture A/B Trigger Event PWM5 OutA Set     */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM5_OUTA_CLR   BITLL(29)           /*!< Slave0 Capture A/B Trigger Event PWM5 OutA Clear   */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM5_CMPA       BITLL(30)           /*!< Slave0 Capture A/B Trigger Event PWM5 Compare A    */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31)))  /*!< Slave0 Capture A/B Trigger Event PWM5 Compare B   */

#define HRPWM_SLV0_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(32)))  /*!< Slave0 Capture A/B Trigger Event PWM6 OutA Set    */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(33)))  /*!< Slave0 Capture A/B Trigger Event PWM6 OutA Clear  */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(34)))  /*!< Slave0 Capture A/B Trigger Event PWM6 Compare A   */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(35)))  /*!< Slave0 Capture A/B Trigger Event PWM6 Compare B   */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36)))  /*!< Slave0 Capture A/B Trigger Event PWM7 OutA Set    */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37)))  /*!< Slave0 Capture A/B Trigger Event PWM7 OutA Clear  */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38)))  /*!< Slave0 Capture A/B Trigger Event PWM7 Compare A   */
#define HRPWM_SLV0_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39)))  /*!< Slave0 Capture A/B Trigger Event PWM7 Compare B   */

/**
  * @brief HRPWM Slave1 Capture A/B Trigger Event Definition
  */
#define HRPWM_Slv1_CapTrigEvtETypeDef

#define HRPWM_SLV1_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave1 Capture A/B Trigger Event None              */
#define HRPWM_SLV1_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave1 Capture A/B Trigger Event Software Capture  */

#define HRPWM_SLV1_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave1 Capture A/B Trigger Event PWMx Update       */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 0      */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 1      */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 2      */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 3      */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 4      */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 5      */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 6      */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave1 Capture A/B Trigger Event PWMx Event 7      */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave1 Capture A/B Trigger Event PWMx Event 8      */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave1 Capture A/B Trigger Event PWMx Event 9      */

#define HRPWM_SLV1_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave1 Capture A/B Trigger Event PWM0 OutA Set     */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave1 Capture A/B Trigger Event PWM0 OutA Clear   */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave1 Capture A/B Trigger Event PWM0 Compare A    */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave1 Capture A/B Trigger Event PWM0 Compare B    */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(16)           /*!< Slave1 Capture A/B Trigger Event PWM2 OutA Set     */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(17)           /*!< Slave1 Capture A/B Trigger Event PWM2 OutA Clear   */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM2_CMPA       BITLL(18)           /*!< Slave1 Capture A/B Trigger Event PWM2 Compare A    */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM2_CMPB       BITLL(19)           /*!< Slave1 Capture A/B Trigger Event PWM2 Compare B    */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(20)           /*!< Slave1 Capture A/B Trigger Event PWM3 OutA Set     */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(21)           /*!< Slave1 Capture A/B Trigger Event PWM3 OutA Clear   */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM3_CMPA       BITLL(22)           /*!< Slave1 Capture A/B Trigger Event PWM3 Compare A    */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM3_CMPB       BITLL(23)           /*!< Slave1 Capture A/B Trigger Event PWM3 Compare B    */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(24)           /*!< Slave1 Capture A/B Trigger Event PWM4 OutA Set     */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(25)           /*!< Slave1 Capture A/B Trigger Event PWM4 OutA Clear   */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM4_CMPA       BITLL(26)           /*!< Slave1 Capture A/B Trigger Event PWM4 Compare A    */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM4_CMPB       BITLL(27)           /*!< Slave1 Capture A/B Trigger Event PWM4 Compare B    */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM5_OUTA_SET   BITLL(28)           /*!< Slave1 Capture A/B Trigger Event PWM5 OutA Set     */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM5_OUTA_CLR   BITLL(29)           /*!< Slave1 Capture A/B Trigger Event PWM5 OutA Clear   */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM5_CMPA       BITLL(30)           /*!< Slave1 Capture A/B Trigger Event PWM5 Compare A    */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave1 Capture A/B Trigger Event PWM5 Compare B    */

#define HRPWM_SLV1_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(32))) /*!< Slave1 Capture A/B Trigger Event PWM6 OutA Set     */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(33))) /*!< Slave1 Capture A/B Trigger Event PWM6 OutA Clear   */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(34))) /*!< Slave1 Capture A/B Trigger Event PWM6 Compare A    */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(35))) /*!< Slave1 Capture A/B Trigger Event PWM6 Compare B    */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36))) /*!< Slave1 Capture A/B Trigger Event PWM7 OutA Set     */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37))) /*!< Slave1 Capture A/B Trigger Event PWM7 OutA Clear   */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38))) /*!< Slave1 Capture A/B Trigger Event PWM7 Compare A    */
#define HRPWM_SLV1_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39))) /*!< Slave1 Capture A/B Trigger Event PWM7 Compare B    */

/**
  * @brief HRPWM Slave2 Capture A/B Trigger Event Definition
  */
#define HRPWM_Slv2_CapTrigEvtETypeDef

#define HRPWM_SLV2_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave2 Capture A/B Trigger Event None              */
#define HRPWM_SLV2_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave2 Capture A/B Trigger Event Software Capture  */

#define HRPWM_SLV2_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave2 Capture A/B Trigger Event PWMx Update       */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 0      */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 1      */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 2      */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 3      */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 4      */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 5      */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 6      */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave2 Capture A/B Trigger Event PWMx Event 7      */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave2 Capture A/B Trigger Event PWMx Event 8      */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave2 Capture A/B Trigger Event PWMx Event 9      */

#define HRPWM_SLV2_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave2 Capture A/B Trigger Event PWM0 OutA Set     */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave2 Capture A/B Trigger Event PWM0 OutA Clear   */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave2 Capture A/B Trigger Event PWM0 Compare A    */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave2 Capture A/B Trigger Event PWM0 Compare B    */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(16)           /*!< Slave2 Capture A/B Trigger Event PWM1 OutA Set     */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(17)           /*!< Slave2 Capture A/B Trigger Event PWM1 OutA Clear   */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM1_CMPA       BITLL(18)           /*!< Slave2 Capture A/B Trigger Event PWM1 Compare A    */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM1_CMPB       BITLL(19)           /*!< Slave2 Capture A/B Trigger Event PWM1 Compare B    */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(20)           /*!< Slave2 Capture A/B Trigger Event PWM3 OutA Set     */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(21)           /*!< Slave2 Capture A/B Trigger Event PWM3 OutA Clear   */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM3_CMPA       BITLL(22)           /*!< Slave2 Capture A/B Trigger Event PWM3 Compare A    */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM3_CMPB       BITLL(23)           /*!< Slave2 Capture A/B Trigger Event PWM3 Compare B    */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(24)           /*!< Slave2 Capture A/B Trigger Event PWM4 OutA Set     */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(25)           /*!< Slave2 Capture A/B Trigger Event PWM4 OutA Clear   */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM4_CMPA       BITLL(26)           /*!< Slave2 Capture A/B Trigger Event PWM4 Compare A    */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM4_CMPB       BITLL(27)           /*!< Slave2 Capture A/B Trigger Event PWM4 Compare B    */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM5_OUTA_SET   BITLL(28)           /*!< Slave2 Capture A/B Trigger Event PWM5 OutA Set     */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM5_OUTA_CLR   BITLL(29)           /*!< Slave2 Capture A/B Trigger Event PWM5 OutA Clear   */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM5_CMPA       BITLL(30)           /*!< Slave2 Capture A/B Trigger Event PWM5 Compare A    */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave2 Capture A/B Trigger Event PWM5 Compare B    */

#define HRPWM_SLV2_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(32))) /*!< Slave2 Capture A/B Trigger Event PWM6 OutA Set     */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(33))) /*!< Slave2 Capture A/B Trigger Event PWM6 OutA Clear   */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(34))) /*!< Slave2 Capture A/B Trigger Event PWM6 Compare A    */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(35))) /*!< Slave2 Capture A/B Trigger Event PWM6 Compare B    */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36))) /*!< Slave2 Capture A/B Trigger Event PWM7 OutA Set     */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37))) /*!< Slave2 Capture A/B Trigger Event PWM7 OutA Clear   */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38))) /*!< Slave2 Capture A/B Trigger Event PWM7 Compare A    */
#define HRPWM_SLV2_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39))) /*!< Slave2 Capture A/B Trigger Event PWM7 Compare B    */

/**
  * @brief HRPWM Slave3 Capture A/B Trigger Event Definition
  */
#define HRPWM_Slv3_CapTrigEvtETypeDef

#define HRPWM_SLV3_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave3 Capture A/B Trigger Event None              */
#define HRPWM_SLV3_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave3 Capture A/B Trigger Event Software Capture  */

#define HRPWM_SLV3_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave3 Capture A/B Trigger Event PWMx Update       */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 0      */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 1      */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 2      */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 3      */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 4      */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 5      */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 6      */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave3 Capture A/B Trigger Event PWMx Event 7      */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave3 Capture A/B Trigger Event PWMx Event 8      */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave3 Capture A/B Trigger Event PWMx Event 9      */

#define HRPWM_SLV3_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave3 Capture A/B Trigger Event PWM0 OutA Set     */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave3 Capture A/B Trigger Event PWM0 OutA Clear   */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave3 Capture A/B Trigger Event PWM0 Compare A    */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave3 Capture A/B Trigger Event PWM0 Compare B    */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(16)           /*!< Slave3 Capture A/B Trigger Event PWM1 OutA Set     */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(17)           /*!< Slave3 Capture A/B Trigger Event PWM1 OutA Clear   */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM1_CMPA       BITLL(18)           /*!< Slave3 Capture A/B Trigger Event PWM1 Compare A    */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM1_CMPB       BITLL(19)           /*!< Slave3 Capture A/B Trigger Event PWM1 Compare B    */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(20)           /*!< Slave3 Capture A/B Trigger Event PWM2 OutA Set     */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(21)           /*!< Slave3 Capture A/B Trigger Event PWM2 OutA Clear   */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave3 Capture A/B Trigger Event PWM2 Compare A    */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave3 Capture A/B Trigger Event PWM2 Compare B    */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(24)           /*!< Slave3 Capture A/B Trigger Event PWM4 OutA Set     */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(25)           /*!< Slave3 Capture A/B Trigger Event PWM4 OutA Clear   */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM4_CMPA       BITLL(26)           /*!< Slave3 Capture A/B Trigger Event PWM4 Compare A    */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM4_CMPB       BITLL(27)           /*!< Slave3 Capture A/B Trigger Event PWM4 Compare B    */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM5_OUTA_SET   BITLL(28)           /*!< Slave3 Capture A/B Trigger Event PWM5 OutA Set     */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM5_OUTA_CLR   BITLL(29)           /*!< Slave3 Capture A/B Trigger Event PWM5 OutA Clear   */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM5_CMPA       BITLL(30)           /*!< Slave3 Capture A/B Trigger Event PWM5 Compare A    */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave3 Capture A/B Trigger Event PWM5 Compare B    */

#define HRPWM_SLV3_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(32))) /*!< Slave3 Capture A/B Trigger Event PWM6 OutA Set     */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(33))) /*!< Slave3 Capture A/B Trigger Event PWM6 OutA Clear   */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(34))) /*!< Slave3 Capture A/B Trigger Event PWM6 Compare A    */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(35))) /*!< Slave3 Capture A/B Trigger Event PWM6 Compare B    */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36))) /*!< Slave3 Capture A/B Trigger Event PWM7 OutA Set     */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37))) /*!< Slave3 Capture A/B Trigger Event PWM7 OutA Clear   */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38))) /*!< Slave3 Capture A/B Trigger Event PWM7 Compare A    */
#define HRPWM_SLV3_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39))) /*!< Slave3 Capture A/B Trigger Event PWM7 Compare B    */

/**
  * @brief HRPWM Slave4 Capture A/B Trigger Event Definition
  */
#define HRPWM_Slv4_CapTrigEvtETypeDef

#define HRPWM_SLV4_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave4 Capture A/B Trigger Event None              */
#define HRPWM_SLV4_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave4 Capture A/B Trigger Event Software Capture  */

#define HRPWM_SLV4_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave4 Capture A/B Trigger Event PWMx Update       */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 0      */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 1      */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 2      */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 3      */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 4      */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 5      */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 6      */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave4 Capture A/B Trigger Event PWMx Event 7      */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave4 Capture A/B Trigger Event PWMx Event 8      */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave4 Capture A/B Trigger Event PWMx Event 9      */

#define HRPWM_SLV4_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave4 Capture A/B Trigger Event PWM0 OutA Set     */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave4 Capture A/B Trigger Event PWM0 OutA Clear   */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave4 Capture A/B Trigger Event PWM0 Compare A    */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave4 Capture A/B Trigger Event PWM0 Compare B    */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(16)           /*!< Slave4 Capture A/B Trigger Event PWM1 OutA Set     */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(17)           /*!< Slave4 Capture A/B Trigger Event PWM1 OutA Clear   */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM1_CMPA       BITLL(18)           /*!< Slave4 Capture A/B Trigger Event PWM1 Compare A    */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM1_CMPB       BITLL(19)           /*!< Slave4 Capture A/B Trigger Event PWM1 Compare B    */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(20)           /*!< Slave4 Capture A/B Trigger Event PWM2 OutA Set     */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(21)           /*!< Slave4 Capture A/B Trigger Event PWM2 OutA Clear   */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave4 Capture A/B Trigger Event PWM2 Compare A    */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave4 Capture A/B Trigger Event PWM2 Compare B    */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(24)           /*!< Slave4 Capture A/B Trigger Event PWM3 OutA Set     */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(25)           /*!< Slave4 Capture A/B Trigger Event PWM3 OutA Clear   */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM3_CMPA       BITLL(26)           /*!< Slave4 Capture A/B Trigger Event PWM3 Compare A    */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM3_CMPB       BITLL(27)           /*!< Slave4 Capture A/B Trigger Event PWM3 Compare B    */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM5_OUTA_SET   BITLL(28)           /*!< Slave4 Capture A/B Trigger Event PWM5 OutA Set     */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM5_OUTA_CLR   BITLL(29)           /*!< Slave4 Capture A/B Trigger Event PWM5 OutA Clear   */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM5_CMPA       BITLL(30)           /*!< Slave4 Capture A/B Trigger Event PWM5 Compare A    */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave4 Capture A/B Trigger Event PWM5 Compare B    */

#define HRPWM_SLV4_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(32))) /*!< Slave4 Capture A/B Trigger Event PWM6 OutA Set     */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(33))) /*!< Slave4 Capture A/B Trigger Event PWM6 OutA Clear   */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(34))) /*!< Slave4 Capture A/B Trigger Event PWM6 Compare A    */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(35))) /*!< Slave4 Capture A/B Trigger Event PWM6 Compare B    */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36))) /*!< Slave4 Capture A/B Trigger Event PWM7 OutA Set     */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37))) /*!< Slave4 Capture A/B Trigger Event PWM7 OutA Clear   */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38))) /*!< Slave4 Capture A/B Trigger Event PWM7 Compare A    */
#define HRPWM_SLV4_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39))) /*!< Slave4 Capture A/B Trigger Event PWM7 Compare B    */

/**
  * @brief HRPWM Slave5 Capture A/B Trigger Event Definition
  */
#define HRPWM_Slv5_CapTrigEvtETypeDef

#define HRPWM_SLV5_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave5 Capture A/B Trigger Event None              */
#define HRPWM_SLV5_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave5 Capture A/B Trigger Event Software Capture  */

#define HRPWM_SLV5_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave5 Capture A/B Trigger Event PWMx Update       */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 0      */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 1      */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 2      */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 3      */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 4      */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 5      */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 6      */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave5 Capture A/B Trigger Event PWMx Event 7      */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave5 Capture A/B Trigger Event PWMx Event 8      */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave5 Capture A/B Trigger Event PWMx Event 9      */

#define HRPWM_SLV5_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave5 Capture A/B Trigger Event PWM0 OutA Set     */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave5 Capture A/B Trigger Event PWM0 OutA Clear   */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave5 Capture A/B Trigger Event PWM0 Compare A    */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave5 Capture A/B Trigger Event PWM0 Compare B    */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(16)           /*!< Slave5 Capture A/B Trigger Event PWM1 OutA Set     */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(17)           /*!< Slave5 Capture A/B Trigger Event PWM1 OutA Clear   */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM1_CMPA       BITLL(18)           /*!< Slave5 Capture A/B Trigger Event PWM1 Compare A    */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM1_CMPB       BITLL(19)           /*!< Slave5 Capture A/B Trigger Event PWM1 Compare B    */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(20)           /*!< Slave5 Capture A/B Trigger Event PWM2 OutA Set     */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(21)           /*!< Slave5 Capture A/B Trigger Event PWM2 OutA Clear   */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave5 Capture A/B Trigger Event PWM2 Compare A    */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave5 Capture A/B Trigger Event PWM2 Compare B    */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(24)           /*!< Slave5 Capture A/B Trigger Event PWM3 OutA Set     */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(25)           /*!< Slave5 Capture A/B Trigger Event PWM3 OutA Clear   */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM3_CMPA       BITLL(26)           /*!< Slave5 Capture A/B Trigger Event PWM3 Compare A    */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM3_CMPB       BITLL(27)           /*!< Slave5 Capture A/B Trigger Event PWM3 Compare B    */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(28)           /*!< Slave5 Capture A/B Trigger Event PWM4 OutA Set     */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(29)           /*!< Slave5 Capture A/B Trigger Event PWM4 OutA Clear   */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM4_CMPA       BITLL(30)           /*!< Slave5 Capture A/B Trigger Event PWM4 Compare A    */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM4_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave5 Capture A/B Trigger Event PWM4 Compare B    */

#define HRPWM_SLV5_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(32)))  /*!< Slave5 Capture A/B Trigger Event PWM6 OutA Set    */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(33)))  /*!< Slave5 Capture A/B Trigger Event PWM6 OutA Clear  */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(34)))  /*!< Slave5 Capture A/B Trigger Event PWM6 Compare A   */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(35)))  /*!< Slave5 Capture A/B Trigger Event PWM6 Compare B   */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36)))  /*!< Slave5 Capture A/B Trigger Event PWM7 OutA Set    */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37)))  /*!< Slave5 Capture A/B Trigger Event PWM7 OutA Clear  */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38)))  /*!< Slave5 Capture A/B Trigger Event PWM7 Compare A   */
#define HRPWM_SLV5_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39)))  /*!< Slave5 Capture A/B Trigger Event PWM7 Compare B   */

/**
  * @brief HRPWM Slave6 Capture A/B Trigger Event Definition
  */
#define HRPWM_Slv6_CapTrigEvtETypeDef

#define HRPWM_SLV6_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave6 Capture A/B Trigger Event None              */
#define HRPWM_SLV6_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave6 Capture A/B Trigger Event Software Capture  */

#define HRPWM_SLV6_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave6 Capture A/B Trigger Event PWMx Update       */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 0      */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 1      */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 2      */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 3      */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 4      */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 5      */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 6      */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave6 Capture A/B Trigger Event PWMx Event 7      */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave6 Capture A/B Trigger Event PWMx Event 8      */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave6 Capture A/B Trigger Event PWMx Event 9      */

#define HRPWM_SLV6_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave6 Capture A/B Trigger Event PWM0 OutA Set     */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave6 Capture A/B Trigger Event PWM0 OutA Clear   */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave6 Capture A/B Trigger Event PWM0 Compare A    */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave6 Capture A/B Trigger Event PWM0 Compare B    */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(16)           /*!< Slave6 Capture A/B Trigger Event PWM1 OutA Set     */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(17)           /*!< Slave6 Capture A/B Trigger Event PWM1 OutA Clear   */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM1_CMPA       BITLL(18)           /*!< Slave6 Capture A/B Trigger Event PWM1 Compare A    */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM1_CMPB       BITLL(19)           /*!< Slave6 Capture A/B Trigger Event PWM1 Compare B    */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(20)           /*!< Slave6 Capture A/B Trigger Event PWM2 OutA Set     */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(21)           /*!< Slave6 Capture A/B Trigger Event PWM2 OutA Clear   */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave6 Capture A/B Trigger Event PWM2 Compare A    */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave6 Capture A/B Trigger Event PWM2 Compare B    */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(24)           /*!< Slave6 Capture A/B Trigger Event PWM3 OutA Set     */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(25)           /*!< Slave6 Capture A/B Trigger Event PWM3 OutA Clear   */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM3_CMPA       BITLL(26)           /*!< Slave6 Capture A/B Trigger Event PWM3 Compare A    */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM3_CMPB       BITLL(27)           /*!< Slave6 Capture A/B Trigger Event PWM3 Compare B    */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(28)           /*!< Slave6 Capture A/B Trigger Event PWM4 OutA Set     */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(29)           /*!< Slave6 Capture A/B Trigger Event PWM4 OutA Clear   */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM4_CMPA       BITLL(30)           /*!< Slave6 Capture A/B Trigger Event PWM4 Compare A    */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM4_CMPB       ((uint64_t)(BITLL(31))) /*!< Slave6 Capture A/B Trigger Event PWM4 Compare B    */

#define HRPWM_SLV6_CAP_TRIG_EVT_PWM5_OUTA_SET   ((uint64_t)(BITLL(32))) /*!< Slave6 Capture A/B Trigger Event PWM5 OutA Set     */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM5_OUTA_CLR   ((uint64_t)(BITLL(33))) /*!< Slave6 Capture A/B Trigger Event PWM5 OutA Clear   */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM5_CMPA       ((uint64_t)(BITLL(34))) /*!< Slave6 Capture A/B Trigger Event PWM5 Compare A    */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(35))) /*!< Slave6 Capture A/B Trigger Event PWM5 Compare B    */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM7_OUTA_SET   ((uint64_t)(BITLL(36))) /*!< Slave6 Capture A/B Trigger Event PWM7 OutA Set     */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM7_OUTA_CLR   ((uint64_t)(BITLL(37))) /*!< Slave6 Capture A/B Trigger Event PWM7 OutA Clear   */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM7_CMPA       ((uint64_t)(BITLL(38))) /*!< Slave6 Capture A/B Trigger Event PWM7 Compare A    */
#define HRPWM_SLV6_CAP_TRIG_EVT_PWM7_CMPB       ((uint64_t)(BITLL(39))) /*!< Slave6 Capture A/B Trigger Event PWM7 Compare B    */

/**
  * @brief HRPWM Slave7 Capture A/B Trigger Event Definition
  */
#define HRPWM_Slv7_CapTrigEvtETypeDef

#define HRPWM_SLV7_CAP_TRIG_EVT_NONE            (0)                 /*!< Slave7 Capture A/B Trigger Event None              */
#define HRPWM_SLV7_CAP_TRIG_EVT_SW_CAP          BITLL(0)            /*!< Slave7 Capture A/B Trigger Event Software Capture  */

#define HRPWM_SLV7_CAP_TRIG_EVT_PWMx_UPD        BITLL(1)            /*!< Slave7 Capture A/B Trigger Event PWMx Update       */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT0       BITLL(2)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 0      */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT1       BITLL(3)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 1      */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT2       BITLL(4)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 2      */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT3       BITLL(5)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 3      */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT4       BITLL(6)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 4      */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT5       BITLL(7)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 5      */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT6       BITLL(8)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 6      */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT7       BITLL(9)            /*!< Slave7 Capture A/B Trigger Event PWMx Event 7      */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT8       BITLL(10)           /*!< Slave7 Capture A/B Trigger Event PWMx Event 8      */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWMx_EVT9       BITLL(11)           /*!< Slave7 Capture A/B Trigger Event PWMx Event 9      */

#define HRPWM_SLV7_CAP_TRIG_EVT_PWM0_OUTA_SET   BITLL(12)           /*!< Slave7 Capture A/B Trigger Event PWM0 OutA Set     */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM0_OUTA_CLR   BITLL(13)           /*!< Slave7 Capture A/B Trigger Event PWM0 OutA Clear   */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM0_CMPA       BITLL(14)           /*!< Slave7 Capture A/B Trigger Event PWM0 Compare A    */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM0_CMPB       BITLL(15)           /*!< Slave7 Capture A/B Trigger Event PWM0 Compare B    */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM1_OUTA_SET   BITLL(16)           /*!< Slave7 Capture A/B Trigger Event PWM1 OutA Set     */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM1_OUTA_CLR   BITLL(17)           /*!< Slave7 Capture A/B Trigger Event PWM1 OutA Clear   */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM1_CMPA       BITLL(18)           /*!< Slave7 Capture A/B Trigger Event PWM1 Compare A    */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM1_CMPB       BITLL(19)           /*!< Slave7 Capture A/B Trigger Event PWM1 Compare B    */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM2_OUTA_SET   BITLL(20)           /*!< Slave7 Capture A/B Trigger Event PWM2 OutA Set     */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM2_OUTA_CLR   BITLL(21)           /*!< Slave7 Capture A/B Trigger Event PWM2 OutA Clear   */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM2_CMPA       BITLL(22)           /*!< Slave7 Capture A/B Trigger Event PWM2 Compare A    */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM2_CMPB       BITLL(23)           /*!< Slave7 Capture A/B Trigger Event PWM2 Compare B    */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM3_OUTA_SET   BITLL(24)           /*!< Slave7 Capture A/B Trigger Event PWM3 OutA Set     */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM3_OUTA_CLR   BITLL(25)           /*!< Slave7 Capture A/B Trigger Event PWM3 OutA Clear   */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM3_CMPA       BITLL(26)           /*!< Slave7 Capture A/B Trigger Event PWM3 Compare A    */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM3_CMPB       BITLL(27)           /*!< Slave7 Capture A/B Trigger Event PWM3 Compare B    */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM4_OUTA_SET   BITLL(28)           /*!< Slave7 Capture A/B Trigger Event PWM4 OutA Set     */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM4_OUTA_CLR   BITLL(29)           /*!< Slave7 Capture A/B Trigger Event PWM4 OutA Clear   */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM4_CMPA       BITLL(30)           /*!< Slave7 Capture A/B Trigger Event PWM4 Compare A    */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM4_CMPB       ((uint64_t)(BITLL(31)))/*!< Slave7 Capture A/B Trigger Event PWM4 Compare B     */

#define HRPWM_SLV7_CAP_TRIG_EVT_PWM5_OUTA_SET   ((uint64_t)(BITLL(32))) /*!< Slave7 Capture A/B Trigger Event PWM5 OutA Set     */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM5_OUTA_CLR   ((uint64_t)(BITLL(33))) /*!< Slave7 Capture A/B Trigger Event PWM5 OutA Clear   */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM5_CMPA       ((uint64_t)(BITLL(34))) /*!< Slave7 Capture A/B Trigger Event PWM5 Compare A    */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM5_CMPB       ((uint64_t)(BITLL(35))) /*!< Slave7 Capture A/B Trigger Event PWM5 Compare B    */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM6_OUTA_SET   ((uint64_t)(BITLL(36))) /*!< Slave7 Capture A/B Trigger Event PWM6 OutA Set     */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM6_OUTA_CLR   ((uint64_t)(BITLL(37))) /*!< Slave7 Capture A/B Trigger Event PWM6 OutA Clear   */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM6_CMPA       ((uint64_t)(BITLL(38))) /*!< Slave7 Capture A/B Trigger Event PWM6 Compare A    */
#define HRPWM_SLV7_CAP_TRIG_EVT_PWM6_CMPB       ((uint64_t)(BITLL(39))) /*!< Slave7 Capture A/B Trigger Event PWM6 Compare B    */


/**
  * @brief HRPWM Common Burst Mode Trigger Event Definition
  */
#define HRPWM_Comm_BurstTrigEvtETypeDef

#define HRPWM_COMM_BURST_TRIG_EVT_NONE                  (0)         /*!< Common Burst Mode Trigger Event None                       */
#define HRPWM_COMM_BURST_TRIG_EVT_SW                    BITLL(0)    /*!< Common Burst Mode Trigger Event Software                   */

#define HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_RST_ROLLOVER  BITLL(1)    /*!< Common Burst Mode Trigger Event Master PWM Reset Roll-Over */
#define HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_REP           BITLL(2)    /*!< Common Burst Mode Trigger Event Master PWM Repetition      */
#define HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_CMPA          BITLL(3)    /*!< Common Burst Mode Trigger Event Master PWM Compare A       */
#define HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_CMPB          BITLL(4)    /*!< Common Burst Mode Trigger Event Master PWM Compare B       */
#define HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_CMPC          BITLL(5)    /*!< Common Burst Mode Trigger Event Master PWM Compare C       */
#define HRPWM_COMM_BURST_TRIG_EVT_MST_PWM_CMPD          BITLL(6)    /*!< Common Burst Mode Trigger Event Master PWM Compare D       */

#define HRPWM_COMM_BURST_TRIG_EVT_PWM0_RST_ROLLOVER     BITLL(7)    /*!< Common Burst Mode Trigger Event PWM0 Reset Roll-Over       */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM0_REP              BITLL(8)    /*!< Common Burst Mode Trigger Event PWM0 Repetition            */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM0_CMPA             BITLL(9)    /*!< Common Burst Mode Trigger Event PWM0 Compare A             */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM0_CMPB             BITLL(10)   /*!< Common Burst Mode Trigger Event PWM0 Compare B             */

#define HRPWM_COMM_BURST_TRIG_EVT_PWM1_RST_ROLLOVER     BITLL(11)   /*!< Common Burst Mode Trigger Event PWM1 Reset Roll-Over       */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM1_REP              BITLL(12)   /*!< Common Burst Mode Trigger Event PWM1 Repetition            */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM1_CMPA             BITLL(13)   /*!< Common Burst Mode Trigger Event PWM1 Compare A             */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM1_CMPB             BITLL(14)   /*!< Common Burst Mode Trigger Event PWM1 Compare B             */

#define HRPWM_COMM_BURST_TRIG_EVT_PWM2_RST_ROLLOVER     BITLL(15)   /*!< Common Burst Mode Trigger Event PWM2 Reset Roll-Over       */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM2_REP              BITLL(16)   /*!< Common Burst Mode Trigger Event PWM2 Repetition            */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM2_CMPA             BITLL(17)   /*!< Common Burst Mode Trigger Event PWM2 Compare A             */

#define HRPWM_COMM_BURST_TRIG_EVT_PWM3_RST_ROLLOVER     BITLL(18)   /*!< Common Burst Mode Trigger Event PWM3 Reset Roll-Over       */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM3_REP              BITLL(19)   /*!< Common Burst Mode Trigger Event PWM3 Repetition            */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM3_CMPB             BITLL(20)   /*!< Common Burst Mode Trigger Event PWM3 Compare B             */

#define HRPWM_COMM_BURST_TRIG_EVT_PWM4_REP              BITLL(21)   /*!< Common Burst Mode Trigger Event PWM4 Repetition            */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM4_CMPA             BITLL(22)   /*!< Common Burst Mode Trigger Event PWM4 Compare A             */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM4_CMPB             BITLL(23)   /*!< Common Burst Mode Trigger Event PWM4 Compare B             */

#define HRPWM_COMM_BURST_TRIG_EVT_PWM5_RST_ROLLOVER     BITLL(24)   /*!< Common Burst Mode Trigger Event PWM5 Reset Roll-Over       */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM5_REP              BITLL(25)   /*!< Common Burst Mode Trigger Event PWM5 Repetition            */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM5_CMPA             BITLL(26)   /*!< Common Burst Mode Trigger Event PWM5 Compare A             */

#define HRPWM_COMM_BURST_TRIG_EVT_PWM0_PRD_EVT7         BITLL(27)   /*!< Common Burst Mode Trigger Event PWM0 Event 7 after Period  */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM4_PRD_EVT8         BITLL(28)   /*!< Common Burst Mode Trigger Event PWM4 Event 8 after Period  */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM0_EVT7             BITLL(29)   /*!< Common Burst Mode Trigger Event PWM0 Event 7               */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM4_EVT8             BITLL(30)   /*!< Common Burst Mode Trigger Event PWM4 Event 8               */

#define HRPWM_COMM_BURST_TRIG_EVT_HRPWM_BM_IN2      ((uint64_t)(BITLL(31)))  /*!< Common Burst Mode Trigger Event hrpwm_bm_in2          */

#define HRPWM_COMM_BURST_TRIG_EVT_PWM6_RST_ROLLOVER ((uint64_t)(BITLL(32))) /*!< Common Burst Mode Trigger Event PWM6 Reset Roll-Over  */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM6_REP          ((uint64_t)(BITLL(33)))  /*!< Common Burst Mode Trigger Event PWM6 Repetition       */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM6_CMPA         ((uint64_t)(BITLL(34)))  /*!< Common Burst Mode Trigger Event PWM6 Compare A        */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM6_CMPB         ((uint64_t)(BITLL(35)))  /*!< Common Burst Mode Trigger Event PWM6 Compare B        */

#define HRPWM_COMM_BURST_TRIG_EVT_PWM7_RST_ROLLOVER ((uint64_t)(BITLL(36))) /*!< Common Burst Mode Trigger Event PWM7 Reset Roll-Over  */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM7_REP          ((uint64_t)(BITLL(37)))  /*!< Common Burst Mode Trigger Event PWM7 Repetition       */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM7_CMPA         ((uint64_t)(BITLL(38)))  /*!< Common Burst Mode Trigger Event PWM7 Compare A        */
#define HRPWM_COMM_BURST_TRIG_EVT_PWM7_CMPB         ((uint64_t)(BITLL(39)))  /*!< Common Burst Mode Trigger Event PWM7 Compare B        */

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup HRPWM_LL_Exported_Macros HRPWM LL Exported Macros
  * @brief    HRPWM LL Exported Macros
  * @{
  */

/**
  * @brief  HRPWM 32bits Register offset
  * @note   Register must be 32bits
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Numbers of register to Offset
  * @return Register value after offset
  */
#define __LL_HRPWM_REG_OFFSET(__REG__, offset)            \
    (*((__IO uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((offset) << 2UL)))))



/**
  * @brief  Master PWM Update Gate Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  gate Master PWM Update Gate
  * @return None
  */
#define __LL_HRPWM_Mst_UpdateGate_Set(__HRPWM__, gate)      \
        MODIFY_REG((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_BRSTDMA_Msk, (((gate) & 0x3UL) << HRPWM_MST_MCR0_BRSTDMA_Pos))

/**
  * @brief  Master PWM Repetition Trigger PWM Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_RepTrigUpd_En(__HRPWM__)             SET_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_MREPU_Msk)

/**
  * @brief  Master PWM Repetition Trigger PWM Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_RepTrigUpd_Dis(__HRPWM__)            CLEAR_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_MREPU_Msk)

/**
  * @brief  Master PWM Reset/RollOver Trigger PWM Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_RstRollOverTrigUpd_En(__HRPWM__)     SET_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_MRSTU_Msk)

/**
  * @brief  Master PWM Reset/RollOver Trigger PWM Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_RstRollOverTrigUpd_Dis(__HRPWM__)    CLEAR_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_MRSTU_Msk)

/**
  * @brief  Master Preload Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Preload_En(__HRPWM__)                SET_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_PREEN_Msk)

/**
  * @brief  Master Preload Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Preload_Dis(__HRPWM__)               CLEAR_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_PREEN_Msk)

/**
  * @brief  Master DAC Trigger Sync Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src Master DAC Trigger Sync Source
  * @return None
  */
#define __LL_HRPWM_Mst_DACSyncSrc_Set(__HRPWM__, src)       \
        MODIFY_REG((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_DACSYNC_Msk, (((src) & 0x3UL) << HRPWM_MST_MCR0_DACSYNC_Pos))

/**
  * @brief  Master Sync Event Output Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src Master Sync Event Output Source
  * @return None
  */
#define __LL_HRPWM_Mst_SyncEvtOutputSrc_Set(__HRPWM__, src) \
        MODIFY_REG((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_SYNCOUTSRC_Msk, (((src) & 0x3UL) << HRPWM_MST_MCR0_SYNCOUTSRC_Pos))

/**
  * @brief  Master Sync Event Output Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_SyncEvtOutput_En(__HRPWM__)          SET_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_SYNCOUTEN_Msk)

/**
  * @brief  Master Sync Event Output Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_SyncEvtOutput_Dis(__HRPWM__)         CLEAR_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_SYNCOUTEN_Msk)

/**
  * @brief  Master Sync Event Output Polarity Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pol Master Sync Event Output Polarity
  * @return None
  */
#define __LL_HRPWM_Mst_SyncEvtOutputPol_Set(__HRPWM__, pol) \
        MODIFY_REG((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_SYNCOUTPOL_Msk, (((pol) & 0x1UL) << HRPWM_MST_MCR0_SYNCOUTPOL_Pos))

/**
  * @brief  Master Sync Event Start Master PWM Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_SyncEvtStartMstPWM_En(__HRPWM__)     SET_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_SYNCSTRTM_Msk)

/**
  * @brief  Master Sync Event Start Master PWM Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_SyncEvtStartMstPWM_Dis(__HRPWM__)    CLEAR_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_SYNCSTRTM_Msk)

/**
  * @brief  Master Sync Event Reset Master PWM Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_SyncEvtRstMstPWM_En(__HRPWM__)       SET_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_SYNCRSTM_Msk)

/**
  * @brief  Master Sync Event Reset Master PWM Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_SyncEvtRstMstPWM_Dis(__HRPWM__)      CLEAR_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_SYNCRSTM_Msk)

/**
  * @brief  Master Sync Event Input Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_SyncEvtInput_En(__HRPWM__)           SET_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_SYNCINEN_Msk)

/**
  * @brief  Master Sync Event Input Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_SyncEvtInput_Dis(__HRPWM__)          CLEAR_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_SYNCINEN_Msk)

/**
  * @brief  Master Sync Event Input Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src Master Sync Event Input Source
  * @return None
  */
#define __LL_HRPWM_Mst_SyncEvtInputSrc_Set(__HRPWM__, src)  \
        MODIFY_REG((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_SYNCINSRC_Msk, (((src) & 0x1UL) << HRPWM_MST_MCR0_SYNCINSRC_Pos))

/**
  * @brief  Master PWM Interleaved Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  mode Master PWM Interleaved Mode @ref HRPWM_IntlvdModeETypeDef
  * @return None
  */
#define __LL_HRPWM_Mst_IntlvdMode_Set(__HRPWM__, mode)      \
        MODIFY_REG((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_INTLVD_Msk, (((mode) & 0x3UL) << HRPWM_MST_MCR0_INTLVD_Pos))

/**
  * @brief  Master PWM Half Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_HalfMode_En(__HRPWM__)               SET_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_HALF_Msk)

/**
  * @brief  Master PWM Half Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_HalfMode_Dis(__HRPWM__)              CLEAR_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_HALF_Msk)

/**
  * @brief  Master PWM Repeat Trigger Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_ReTrigMode_En(__HRPWM__)             SET_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_RETRIG_Msk)

/**
  * @brief  Master PWM Repeat Trigger Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_ReTrigMode_Dis(__HRPWM__)            CLEAR_BIT((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_RETRIG_Msk)

/**
  * @brief  Master PWM Work Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  mode Master PWM Work Mode
  * @return None
  */
#define __LL_HRPWM_Mst_WorkMode_Set(__HRPWM__, mode)        \
        MODIFY_REG((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_CONT_Msk, (((mode) & 0x1UL) << HRPWM_MST_MCR0_CONT_Pos))

/**
  * @brief  Master PWM Clock Division Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  div Master PWM Clock Division
  * @return None
  */
#define __LL_HRPWM_Mst_ClkDiv_Set(__HRPWM__, div)           \
        MODIFY_REG((__HRPWM__)->Master.MCR0, HRPWM_MST_MCR0_CKPSC_Msk, (((div) & 0x7UL) << HRPWM_MST_MCR0_CKPSC_Pos))


/**
  * @brief  Master PWM Burst DMA Disable Assert
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_BurstDMADis_Assert(__HRPWM__)        SET_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_BDMADIS_Msk)

/**
  * @brief  Master PWM Burst DMA Disable Release
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_BurstDMADis_Release(__HRPWM__)       CLEAR_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_BDMADIS_Msk)

/**
  * @brief  Master PWM Burst DMA Disable Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_BurstDMADis_Get(__HRPWM__)           \
        READ_BIT_SHIFT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_BDMADIS_Msk, HRPWM_MST_MCR1_BDMADIS_Pos)

/**
  * @brief  Master PWM7 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM7_En(__HRPWM__)                   SET_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN7_Msk)

/**
  * @brief  Master PWM7 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM7_Dis(__HRPWM__)                  CLEAR_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN7_Msk)

/**
  * @brief  Master PWM6 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM6_En(__HRPWM__)                   SET_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN6_Msk)

/**
  * @brief  Master PWM6 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM6_Dis(__HRPWM__)                  CLEAR_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN6_Msk)

/**
  * @brief  Master PWM5 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM5_En(__HRPWM__)                   SET_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN5_Msk)

/**
  * @brief  Master PWM5 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM5_Dis(__HRPWM__)                  CLEAR_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN5_Msk)

/**
  * @brief  Master PWM4 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM4_En(__HRPWM__)                   SET_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN4_Msk)

/**
  * @brief  Master PWM4 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM4_Dis(__HRPWM__)                  CLEAR_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN4_Msk)

/**
  * @brief  Master PWM3 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM3_En(__HRPWM__)                   SET_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN3_Msk)

/**
  * @brief  Master PWM3 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM3_Dis(__HRPWM__)                  CLEAR_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN3_Msk)

/**
  * @brief  Master PWM2 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM2_En(__HRPWM__)                   SET_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN2_Msk)

/**
  * @brief  Master PWM2 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM2_Dis(__HRPWM__)                  CLEAR_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN2_Msk)

/**
  * @brief  Master PWM1 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM1_En(__HRPWM__)                   SET_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN1_Msk)

/**
  * @brief  Master PWM1 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM1_Dis(__HRPWM__)                  CLEAR_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN1_Msk)

/**
  * @brief  Master PWM0 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM0_En(__HRPWM__)                   SET_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN0_Msk)

/**
  * @brief  Master PWM0 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM0_Dis(__HRPWM__)                  CLEAR_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_CEN0_Msk)

/**
  * @brief  Master PWMx Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Mst_PWMx_En(__HRPWM__, pwmx)             \
    SET_BIT((__HRPWM__)->Master.MCR1, BIT(((pwmx) % PWMx_NUMS) + HRPWM_MST_MCR1_CEN0_Pos))

/**
  * @brief  Master PWMx Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Mst_PWMx_Dis(__HRPWM__, pwmx)            \
    CLEAR_BIT((__HRPWM__)->Master.MCR1, BIT(((pwmx) % PWMx_NUMS) + HRPWM_MST_MCR1_CEN0_Pos))

/**
  * @brief  Master PWM Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM_En(__HRPWM__)                    SET_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_MCEN_Msk)

/**
  * @brief  Master PWM Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PWM_Dis(__HRPWM__)                   CLEAR_BIT((__HRPWM__)->Master.MCR1, HRPWM_MST_MCR1_MCEN_Msk)

/**
  * @brief  Master Multi PWM Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmxs Multi PWMx Mask, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return None
  */
#define __LL_HRPWM_Mst_MultiPWMx_En(__HRPWM__, pwmxs)       SET_BIT((__HRPWM__)->Master.MCR1, ((pwmxs) & 0x1ffUL) << HRPWM_MST_MCR1_MCEN_Pos)

/**
  * @brief  Master Multi PWM Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmxs Multi PWMx Mask, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return None
  */
#define __LL_HRPWM_Mst_MultiPWMx_Dis(__HRPWM__, pwmxs)      CLEAR_BIT((__HRPWM__)->Master.MCR1, ((pwmxs) & 0x1ffUL) << HRPWM_MST_MCR1_MCEN_Pos)

/**
  * @brief  PWM Enable Register Write
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  val Register Value
  * @return None
  */
#define __LL_HRPWM_PWMEnReg_Write(__HRPWM__, val)           WRITE_REG((__HRPWM__)->Master.MCR1, val)


/**
  * @brief  Judge is Master Repetition Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Master Repetition Interrupt Pending
  * @retval 1 is Master Repetition Interrupt Pending
  */
#define __LL_HRPWM_Mst_IsRepIntPnd(__HRPWM__)               \
        READ_BIT_SHIFT((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MREP_Msk, HRPWM_MST_MISR_MREP_Pos)

/**
  * @brief  Master Repetition Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_RepIntPnd_Clr(__HRPWM__)             WRITE_REG((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MREP_Msk)

/**
  * @brief  Judge is Master Reset Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Master Reset Interrupt Pending
  * @retval 1 is Master Reset Interrupt Pending
  */
#define __LL_HRPWM_Mst_IsRstIntPnd(__HRPWM__)               \
        READ_BIT_SHIFT((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MRST_Msk, HRPWM_MST_MISR_MRST_Pos)

/**
  * @brief  Master Reset Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_RstIntPnd_Clr(__HRPWM__)             WRITE_REG((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MRST_Msk)

/**
  * @brief  Judge is Master Update Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Master Update Interrupt Pending
  * @retval 1 is Master Update Interrupt Pending
  */
#define __LL_HRPWM_Mst_IsUpdateIntPnd(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MUPD_Msk, HRPWM_MST_MISR_MUPD_Pos)

/**
  * @brief  Master Update Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_UpdateIntPnd_Clr(__HRPWM__)          WRITE_REG((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MUPD_Msk)

/**
  * @brief  Judge is Master Sync Input Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Master Sync Input Interrupt Pending
  * @retval 1 is Master Sync Input Interrupt Pending
  */
#define __LL_HRPWM_Mst_IsSyncInputIntPnd(__HRPWM__)         \
        READ_BIT_SHIFT((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_SYNC_Msk, HRPWM_MST_MISR_SYNC_Pos)

/**
  * @brief  Master Sync Input Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_SyncInputIntPnd_Clr(__HRPWM__)       WRITE_REG((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_SYNC_Msk)

/**
  * @brief  Judge is Master Period Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Master Period Interrupt Pending
  * @retval 1 is Master Period Interrupt Pending
  */
#define __LL_HRPWM_Mst_IsPeriodIntPnd(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MPER_Msk, HRPWM_MST_MISR_MPER_Pos)

/**
  * @brief  Master Period Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_PeriodIntPnd_Clr(__HRPWM__)          WRITE_REG((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MPER_Msk)

/**
  * @brief  Judge is Master Compare D Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Master Compare D Interrupt Pending
  * @retval 1 is Master Compare D Interrupt Pending
  */
#define __LL_HRPWM_Mst_IsCmpDIntPnd(__HRPWM__)              \
        READ_BIT_SHIFT((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MCMPD_Msk, HRPWM_MST_MISR_MCMPD_Pos)

/**
  * @brief  Master Compare D Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpDIntPnd_Clr(__HRPWM__)            WRITE_REG((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MCMPD_Msk)

/**
  * @brief  Judge is Master Compare C Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Master Compare C Interrupt Pending
  * @retval 1 is Master Compare C Interrupt Pending
  */
#define __LL_HRPWM_Mst_IsCmpCIntPnd(__HRPWM__)              \
        READ_BIT_SHIFT((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MCMPC_Msk, HRPWM_MST_MISR_MCMPC_Pos)

/**
  * @brief  Master Compare C Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpCIntPnd_Clr(__HRPWM__)            WRITE_REG((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MCMPC_Msk)

/**
  * @brief  Judge is Master Compare B Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Master Compare B Interrupt Pending
  * @retval 1 is Master Compare B Interrupt Pending
  */
#define __LL_HRPWM_Mst_IsCmpBIntPnd(__HRPWM__)              \
        READ_BIT_SHIFT((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MCMPB_Msk, HRPWM_MST_MISR_MCMPB_Pos)

/**
  * @brief  Master Compare B Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpBIntPnd_Clr(__HRPWM__)            WRITE_REG((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MCMPB_Msk)

/**
  * @brief  Judge is Master Compare A Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Master Compare A Interrupt Pending
  * @retval 1 is Master Compare A Interrupt Pending
  */
#define __LL_HRPWM_Mst_IsCmpAIntPnd(__HRPWM__)              \
        READ_BIT_SHIFT((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MCMPA_Msk, HRPWM_MST_MISR_MCMPA_Pos)

/**
  * @brief  Master Compare A Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpAIntPnd_Clr(__HRPWM__)            WRITE_REG((__HRPWM__)->Master.MISR, HRPWM_MST_MISR_MCMPA_Msk)

/**
  * @brief  HRPWM Master PWM All Interrupt Pending Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return HRPWM Master PWM All Interrupt Pending
  */
#define __LL_HRPWM_Mst_AllIntPnd_Get(__HRPWM__)             READ_REG((__HRPWM__)->Master.MISR)


/**
  * @brief  Master Repetition DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Rep_DMA_En(__HRPWM__)                SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MREPDE_Msk)

/**
  * @brief  Master Repetition DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Rep_DMA_Dis(__HRPWM__)               CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MREPDE_Msk)

/**
  * @brief  Master Reset DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Rst_DMA_En(__HRPWM__)                SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MRSTDE_Msk)

/**
  * @brief  Master Reset DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Rst_DMA_Dis(__HRPWM__)               CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MRSTDE_Msk)

/**
  * @brief  Master Update DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Update_DMA_En(__HRPWM__)             SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MUPDDE_Msk)

/**
  * @brief  Master Update DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Update_DMA_Dis(__HRPWM__)            CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MUPDDE_Msk)

/**
  * @brief  Master Sync Input DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_SyncInput_DMA_En(__HRPWM__)          SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_SYNCDE_Msk)

/**
  * @brief  Master Sync Input DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_SyncInput_DMA_Dis(__HRPWM__)         CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_SYNCDE_Msk)

/**
  * @brief  Master Period DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Period_DMA_En(__HRPWM__)             SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MPERDE_Msk)

/**
  * @brief  Master Period DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Period_DMA_Dis(__HRPWM__)            CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MPERDE_Msk)

/**
  * @brief  Master Compare D DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpD_DMA_En(__HRPWM__)               SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPDDE_Msk)

/**
  * @brief  Master Compare D DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpD_DMA_Dis(__HRPWM__)              CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPDDE_Msk)

/**
  * @brief  Master Compare C DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpC_DMA_En(__HRPWM__)               SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPCDE_Msk)

/**
  * @brief  Master Compare C DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpC_DMA_Dis(__HRPWM__)              CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPCDE_Msk)

/**
  * @brief  Master Compare B DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpB_DMA_En(__HRPWM__)               SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPBDE_Msk)

/**
  * @brief  Master Compare B DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpB_DMA_Dis(__HRPWM__)              CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPBDE_Msk)

/**
  * @brief  Master Compare A DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpA_DMA_En(__HRPWM__)               SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPADE_Msk)

/**
  * @brief  Master Compare A DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpA_DMA_Dis(__HRPWM__)              CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPADE_Msk)

/**
  * @brief  Master DMA Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  dma_msk DMA Mask Combination @ref HRPWM_Mst_DMAETypeDef
  * @return None
  */
#define __LL_HRPWM_Mst_DMA_En_Cfg(__HRPWM__, dma_msk)       \
        MODIFY_REG((__HRPWM__)->Master.MDIER, 0x1ff0000UL, ((dma_msk) & 0x1ff0000UL))

/**
  * @brief  Master Repetition Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Rep_INT_En(__HRPWM__)                SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MREPIE_Msk)

/**
  * @brief  Master Repetition Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Rep_INT_Dis(__HRPWM__)               CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MREPIE_Msk)

/**
  * @brief  Master Reset Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Rst_INT_En(__HRPWM__)                SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MRSTIE_Msk)

/**
  * @brief  Master Reset Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Rst_INT_Dis(__HRPWM__)               CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MRSTIE_Msk)

/**
  * @brief  Master Update Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Update_INT_En(__HRPWM__)             SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MUPDIE_Msk)

/**
  * @brief  Master Update Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Update_INT_Dis(__HRPWM__)            CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MUPDIE_Msk)

/**
  * @brief  Master Sync Input Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_SyncInput_INT_En(__HRPWM__)          SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_SYNCIE_Msk)

/**
  * @brief  Master Sync Input Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_SyncInput_INT_Dis(__HRPWM__)         CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_SYNCIE_Msk)

/**
  * @brief  Master Period Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Period_INT_En(__HRPWM__)             SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MPERIE_Msk)

/**
  * @brief  Master Period Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_Period_INT_Dis(__HRPWM__)            CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MPERIE_Msk)

/**
  * @brief  Master Compare D Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpD_INT_En(__HRPWM__)               SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPDIE_Msk)

/**
  * @brief  Master Compare D Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpD_INT_Dis(__HRPWM__)              CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPDIE_Msk)

/**
  * @brief  Master Compare C Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpC_INT_En(__HRPWM__)               SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPCIE_Msk)

/**
  * @brief  Master Compare C Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpC_INT_Dis(__HRPWM__)              CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPCIE_Msk)

/**
  * @brief  Master Compare B Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpB_INT_En(__HRPWM__)               SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPBIE_Msk)

/**
  * @brief  Master Compare B Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpB_INT_Dis(__HRPWM__)              CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPBIE_Msk)

/**
  * @brief  Master Compare A Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpA_INT_En(__HRPWM__)               SET_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPAIE_Msk)

/**
  * @brief  Master Compare A Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CmpA_INT_Dis(__HRPWM__)              CLEAR_BIT((__HRPWM__)->Master.MDIER, HRPWM_MST_MDIER_MCMPAIE_Msk)

/**
  * @brief  Master Interrupt Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  int_msk Interrupt Mask Combination @ref HRPWM_Mst_IntETypeDef
  * @return None
  */
#define __LL_HRPWM_Mst_INT_En_Cfg(__HRPWM__, int_msk)       MODIFY_REG((__HRPWM__)->Master.MDIER, 0x1ffUL, ((int_msk) & 0x1ffUL))

/**
  * @brief  HRPWM Master PWM All Interrupt Enable Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return HRPWM Master PWM All Interrupt Enable Status
  */
#define __LL_HRPWM_Mst_AllIntEn_Get(__HRPWM__)              READ_BIT((__HRPWM__)->Master.MDIER, 0x1ffUL)


/**
  * @brief  Master PWM Counter Write
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  cnt Master PWM Counter
  * @return None
  */
#define __LL_HRPWM_Mst_Counter_Wrtie(__HRPWM__, cnt)                                                                    \
        do {                                                                                                            \
            WRITE_REG((__HRPWM__)->Master.MCNTR, HRPWM_MST_MCNTR_CNTWR_Msk | ((cnt) & 0xffffUL));                       \
            while (READ_BIT_SHIFT((__HRPWM__)->Master.MCNTR, HRPWM_MST_MCNTR_CNTWR_Msk, HRPWM_MST_MCNTR_CNTWR_Pos));    \
        } while (0)

/**
  * @brief  Master PWM Counter Read Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Mst_CounterRead_En(__HRPWM__)                                                                        \
        do {                                                                                                            \
            WRITE_REG((__HRPWM__)->Master.MCNTR, HRPWM_MST_MCNTR_CNTRD_Msk);                                            \
            while (READ_BIT_SHIFT((__HRPWM__)->Master.MCNTR, HRPWM_MST_MCNTR_CNTRD_Msk, HRPWM_MST_MCNTR_CNTRD_Pos));    \
        } while (0)

/**
  * @brief  Master PWM Counter Read
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return Master PWM Counter
  */
#define __LL_HRPWM_Mst_Counter_Read(__HRPWM__)              \
        READ_BIT_SHIFT((__HRPWM__)->Master.MCNTR, HRPWM_MST_MCNTR_MCNT_Msk, HRPWM_MST_MCNTR_MCNT_Pos)


/**
  * @brief  Master PWM Counter Period Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  prd Master PWM Counter Period
  * @return None
  */
#define __LL_HRPWM_Mst_CntrPeriod_Set(__HRPWM__, prd)       WRITE_REG((__HRPWM__)->Master.MPER, ((prd) & 0xffffUL))

/**
  * @brief  Master PWM Counter Period Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return Master PWM Counter Period
  */
#define __LL_HRPWM_Mst_CntrPeriod_Get(__HRPWM__)            READ_REG((__HRPWM__)->Master.MPER)


/**
  * @brief  Master PWM Repetition Period Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  prd Master PWM Repetition Period
  * @return None
  */
#define __LL_HRPWM_Mst_RepPeriod_Set(__HRPWM__, prd)        WRITE_REG((__HRPWM__)->Master.MREP, ((prd) & 0xffUL))

/**
  * @brief  Master PWM Repetition Period Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return Master PWM Repetition Period
  */
#define __LL_HRPWM_Mst_RepPeriod_Get(__HRPWM__)             READ_REG((__HRPWM__)->Master.MREP)


/**
  * @brief  Master PWM Compare A Value Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  val Master PWM Compare A Value
  * @return None
  */
#define __LL_HRPWM_Mst_CmpAVal_Set(__HRPWM__, val)          WRITE_REG((__HRPWM__)->Master.MCMPAR, ((val) & 0xffffUL))

/**
  * @brief  Master PWM Compare A Value Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return Master PWM Compare A Value
  */
#define __LL_HRPWM_Mst_CmpAVal_Get(__HRPWM__)               READ_REG((__HRPWM__)->Master.MCMPAR)


/**
  * @brief  Master PWM Compare B Value Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  val Master PWM Compare B Value
  * @return None
  */
#define __LL_HRPWM_Mst_CmpBVal_Set(__HRPWM__, val)          WRITE_REG((__HRPWM__)->Master.MCMPBR, ((val) & 0xffffUL))

/**
  * @brief  Master PWM Compare B Value Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return Master PWM Compare B Value
  */
#define __LL_HRPWM_Mst_CmpBVal_Get(__HRPWM__)               READ_REG((__HRPWM__)->Master.MCMPBR)


/**
  * @brief  Master PWM Compare C Value Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  val Master PWM Compare C Value
  * @return None
  */
#define __LL_HRPWM_Mst_CmpCVal_Set(__HRPWM__, val)          WRITE_REG((__HRPWM__)->Master.MCMPCR, ((val) & 0xffffUL))

/**
  * @brief  Master PWM Compare C Value Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return Master PWM Compare C Value
  */
#define __LL_HRPWM_Mst_CmpCVal_Get(__HRPWM__)               READ_REG((__HRPWM__)->Master.MCMPCR)


/**
  * @brief  Master PWM Compare D Value Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  val Master PWM Compare D Value
  * @return None
  */
#define __LL_HRPWM_Mst_CmpDVal_Set(__HRPWM__, val)          WRITE_REG((__HRPWM__)->Master.MCMPDR, ((val) & 0xffffUL))

/**
  * @brief  Master PWM Compare D Value Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return Master PWM Compare D Value
  */
#define __LL_HRPWM_Mst_CmpDVal_Get(__HRPWM__)               READ_REG((__HRPWM__)->Master.MCMPDR)


/**
  * @brief  Master PWM Register Support that System DMA Write into MDMADR and Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  reg Register Type Mask @ref HRPWM_Comm_BurstDMAMstRegUpdETypeDef
  * @return None
  */
#define __LL_HRPWM_Mst_SysDMAWriteUpd_Set(__HRPWM__, reg)   SET_BIT((__HRPWM__)->Master.MDMAUR, reg)

/**
  * @brief  Master PWM Register Support that System DMA Write into MDMADR and Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  reg Register Type Mask @ref HRPWM_Comm_BurstDMAMstRegUpdETypeDef
  * @return None
  */
#define __LL_HRPWM_Mst_SysDMAWriteUpd_Reset(__HRPWM__, reg) CLEAR_BIT((__HRPWM__)->Master.MDMAUR, reg)

/**
  * @brief  Get Master PWM Register Support Update Register
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return Register Type Mask @ref HRPWM_Comm_BurstDMAMstRegUpdETypeDef
  */
#define __LL_HRPWM_Mst_SysDMAWriteUpd_Get(__HRPWM__)        READ_BIT_SHIFT((__HRPWM__)->Master.MDMAUR, 0x7ffUL, 0)


/**
  * @brief  Master PWMx System DMA Address Write
  * @note   Reserved, please do not use (WO)
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  addr Master PWMx System DMA Address
  * @return None
  */
#define __LL_HRPWM_Mst_SysDMAAddr_Write(__HRPWM__, addr)    WRITE_REG((__HRPWM__)->Master.MDMADR, addr & 0xffffffffUL)

/**
  * @brief  Master PWMx System DMA Address Read
  * @note   Reserved, please do not use (WO)
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return Master PWMx System DMA Address
  */
#define __LL_HRPWM_Mst_SysDMAAddr_Read(__HRPWM__)           READ_REG((__HRPWM__)->Master.MDMADR)


/**
  * @brief  Slave PWMx Update Gate Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  gate Slave PWMx Update Gate
  * @return None
  */
#define __LL_HRPWM_Slv_UpdateGate_Set(__HRPWM__, pwmx, gate)    MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, \
        HRPWM_SLV0_PWMCR0_UPDGAT_Msk, (((gate) & 0xfUL) << HRPWM_SLV0_PWMCR0_UPDGAT_Pos))

/**
  * @brief  Slave PWMx Repetition Trigger PWM Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_RepTrigUpd_En(__HRPWM__, pwmx)           \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_UPDREP_Msk)

/**
  * @brief  Slave PWMx Repetition Trigger PWM Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_RepTrigUpd_Dis(__HRPWM__, pwmx)          \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_UPDREP_Msk)

/**
  * @brief  Slave PWMx Reset/RollOver Trigger PWM Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_RstRollOverTrigUpd_En(__HRPWM__, pwmx)   \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_UPDRST_Msk)

/**
  * @brief  Slave PWMx Reset/RollOver Trigger PWM Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_RstRollOverTrigUpd_Dis(__HRPWM__, pwmx)  \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_UPDRST_Msk)

/**
  * @brief  Slave Preload Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Preload_En(__HRPWM__, pwmx)              \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_PREEN_Msk)

/**
  * @brief  Slave Preload Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Preload_Dis(__HRPWM__, pwmx)             \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_PREEN_Msk)

/**
  * @brief  Slave DAC Trigger Sync Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  src Slave DAC Trigger Sync Source
  * @return None
  */
#define __LL_HRPWM_Slv_DACSyncSrc_Set(__HRPWM__, pwmx, src)     MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, \
        HRPWM_SLV0_PWMCR0_DACSYNC_Msk, (((src) & 0x3UL) << HRPWM_SLV0_PWMCR0_DACSYNC_Pos))

/**
  * @brief  Slave PWMx CMPC Greater Than Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpCGreaterThanMode_En(__HRPWM__, pwmx)  \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_GTCMPC_Msk)

/**
  * @brief  Slave PWMx CMPC Greater Than Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpCGreaterThanMode_Dis(__HRPWM__, pwmx) \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_GTCMPC_Msk)

/**
  * @brief  Slave PWMx CMPA Greater Than Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpAGreaterThanMode_En(__HRPWM__, pwmx)  \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_GTCMPA_Msk)

/**
  * @brief  Slave PWMx CMPA Greater Than Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpAGreaterThanMode_Dis(__HRPWM__, pwmx) \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_GTCMPA_Msk)

/**
  * @brief  Slave PWMx Triggered Half Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_TrigHalfMode_En(__HRPWM__, pwmx)         \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_TRGHLF_Msk)

/**
  * @brief  Slave PWMx Triggered Half Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_TrigHalfMode_Dis(__HRPWM__, pwmx)        \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_TRGHLF_Msk)

/**
  * @brief  Slave PWMx CMPD Auto Delayed Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mode CMPD Auto Delayed Mode
  * @return None
  */
#define __LL_HRPWM_Slv_CmpDAutoDlyMode_Set(__HRPWM__, pwmx, mode)   MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, \
        HRPWM_SLV0_PWMCR0_DELCMPD_Msk, (((mode) & 0x3UL) << HRPWM_SLV0_PWMCR0_DELCMPD_Pos))

/**
  * @brief  Slave PWMx CMPB Auto Delayed Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mode PWMx CMPB Auto Delayed Mode
  * @return None
  */
#define __LL_HRPWM_Slv_CmpBAutoDlyMode_Set(__HRPWM__, pwmx, mode)   MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, \
        HRPWM_SLV0_PWMCR0_DELCMPB_Msk, (((mode) & 0x3UL) << HRPWM_SLV0_PWMCR0_DELCMPB_Pos))

/**
  * @brief  Slave PWMx Sync Event Start PWMx Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_SyncEvtStartPWMx_En(__HRPWM__, pwmx)     \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_SYNCSTRT_Msk)

/**
  * @brief  Slave PWMx Sync Event Start PWMx Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_SyncEvtStartPWMx_Dis(__HRPWM__, pwmx)    \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_SYNCSTRT_Msk)

/**
  * @brief  Slave PWMx Sync Event Reset PWMx Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_SyncEvtRstPWMx_En(__HRPWM__, pwmx)       \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_SYNCRST_Msk)

/**
  * @brief  Slave PWMx Sync Event Reset PWMx Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_SyncEvtRstPWMx_Dis(__HRPWM__, pwmx)      \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_SYNCRST_Msk)

/**
  * @brief  Slave PWMx ReSync Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mode PWMx ReSync Mode
  * @return None
  */
#define __LL_HRPWM_Slv_ReSyncMode_Set(__HRPWM__, pwmx, mode)    MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, \
        HRPWM_SLV0_PWMCR0_RSYNCU_Msk, (((mode) & 0x1UL) << HRPWM_SLV0_PWMCR0_RSYNCU_Pos))

/**
  * @brief  Slave PWMx Push-Pull Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PushPullMode_En(__HRPWM__, pwmx)         \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_PSHPLL_Msk)

/**
  * @brief  Slave PWMx Push-Pull Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PushPullMode_Dis(__HRPWM__, pwmx)        \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_PSHPLL_Msk)

/**
  * @brief  Slave PWMx Interleaved Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mode PWMx Interleaved Mode @ref HRPWM_IntlvdModeETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_IntlvdMode_Set(__HRPWM__, pwmx, mode)    MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, \
        HRPWM_SLV0_PWMCR0_INTLVD_Msk, (((mode) & 0x3UL) << HRPWM_SLV0_PWMCR0_INTLVD_Pos))

/**
  * @brief  Slave PWMx Half Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_HalfMode_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_HALF_Msk)

/**
  * @brief  Slave PWMx Half Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_HalfMode_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_HALF_Msk)

/**
  * @brief  Slave PWMx Repeat Trigger Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_ReTrigMode_En(__HRPWM__, pwmx)           \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_RETRIG_Msk)

/**
  * @brief  Slave PWMx Repeat Trigger Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_ReTrigMode_Dis(__HRPWM__, pwmx)          \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, HRPWM_SLV0_PWMCR0_RETRIG_Msk)

/**
  * @brief  Slave PWMx Work Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param mode Slave PWMx Work Mode
  * @return None
  */
#define __LL_HRPWM_Slv_WorkMode_Set(__HRPWM__, pwmx, mode)      MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, \
        HRPWM_SLV0_PWMCR0_CONT_Msk, (((mode) & 0x1UL) << HRPWM_SLV0_PWMCR0_CONT_Pos))

/**
  * @brief  Slave PWMx Clock Division Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param div Slave PWMx Clock Division
  * @return None
  */
#define __LL_HRPWM_Slv_ClkDiv_Set(__HRPWM__, pwmx, div)         MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR0, \
        HRPWM_SLV0_PWMCR0_CKPSC_Msk, (((div) & 0x7UL) << HRPWM_SLV0_PWMCR0_CKPSC_Pos))


/**
  * @brief  Slave PWMx Burst DMA Disable Assert
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWMxBurstDMADis_Assert(__HRPWM__, pwmx)      \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_BDMADIS_Msk)

/**
  * @brief  Slave PWMx Burst DMA Disable Release
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWMxBurstDMADis_Release(__HRPWM__, pwmx)     \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_BDMADIS_Msk)

/**
  * @brief  Slave PWM Burst DMA Disable Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWMxBurstDMADis_Get(__HRPWM__, pwmx)         \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_BDMADIS_Msk, HRPWM_SLV0_PWMCR1_BDMADIS_Pos)

/**
  * @brief  Slave PWM7 Update Event Trigger PWMx Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM7UpdEvtTrigPWMxUpd_En(__HRPWM__, pwmx)    \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD7_Msk)

/**
  * @brief  Slave PWM7 Update Event Trigger PWMx Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM7UpdEvtTrigPWMxUpd_Dis(__HRPWM__, pwmx)   \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD7_Msk)

/**
  * @brief  Slave PWM6 Update Event Trigger PWMx Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM6UpdEvtTrigPWMxUpd_En(__HRPWM__, pwmx)    \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD6_Msk)

/**
  * @brief  Slave PWM6 Update Event Trigger PWMx Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM6UpdEvtTrigPWMxUpd_Dis(__HRPWM__, pwmx)   \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD6_Msk)

/**
  * @brief  Slave PWM5 Update Event Trigger PWMx Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM5UpdEvtTrigPWMxUpd_En(__HRPWM__, pwmx)    \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD5_Msk)

/**
  * @brief  Slave PWM5 Update Event Trigger PWMx Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM5UpdEvtTrigPWMxUpd_Dis(__HRPWM__, pwmx)   \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD5_Msk)

/**
  * @brief  Slave PWM4 Update Event Trigger PWMx Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM4UpdEvtTrigPWMxUpd_En(__HRPWM__, pwmx)    \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD4_Msk)

/**
  * @brief  Slave PWM4 Update Event Trigger PWMx Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM4UpdEvtTrigPWMxUpd_Dis(__HRPWM__, pwmx)   \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD4_Msk)

/**
  * @brief  Slave PWM3 Update Event Trigger PWMx Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM3UpdEvtTrigPWMxUpd_En(__HRPWM__, pwmx)    \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD3_Msk)

/**
  * @brief  Slave PWM3 Update Event Trigger PWMx Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM3UpdEvtTrigPWMxUpd_Dis(__HRPWM__, pwmx)   \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD3_Msk)

/**
  * @brief  Slave PWM2 Update Event Trigger PWMx Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM2UpdEvtTrigPWMxUpd_En(__HRPWM__, pwmx)    \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD2_Msk)

/**
  * @brief  Slave PWM2 Update Event Trigger PWMx Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM2UpdEvtTrigPWMxUpd_Dis(__HRPWM__, pwmx)   \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD2_Msk)

/**
  * @brief  Slave PWM1 Update Event Trigger PWMx Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM1UpdEvtTrigPWMxUpd_En(__HRPWM__, pwmx)    \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD1_Msk)

/**
  * @brief  Slave PWM1 Update Event Trigger PWMx Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM1UpdEvtTrigPWMxUpd_Dis(__HRPWM__, pwmx)   \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD1_Msk)

/**
  * @brief  Slave PWM0 Update Event Trigger PWMx Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM0UpdEvtTrigPWMxUpd_En(__HRPWM__, pwmx)    \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD0_Msk)

/**
  * @brief  Slave PWM0 Update Event Trigger PWMx Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PWM0UpdEvtTrigPWMxUpd_Dis(__HRPWM__, pwmx)   \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_UPD0_Msk)

/**
  * @brief  Slave Master PWM Update Event Trigger PWMx Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_MstPWMUpdEvtTrigPWMxUpd_En(__HRPWM__, pwmx)  \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_MUPD_Msk)

/**
  * @brief  Slave Master PWM Update Event Trigger PWMx Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_MstPWMUpdEvtTrigPWMxUpd_Dis(__HRPWM__, pwmx) \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_MUPD_Msk)

/**
  * @brief  Slave PWMx Fault Roll-Over Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mode PWMx Fault Roll-Over Mode
  * @return None
  */
#define __LL_HRPWM_Slv_FltRollOverMode_Set(__HRPWM__, pwmx, mode)   MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, \
        HRPWM_SLV0_PWMCR1_FLTROM_Msk, (((mode) & 0x3UL) << HRPWM_SLV0_PWMCR1_FLTROM_Pos))

/**
  * @brief  Slave PWMx Event Roll-Over Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mode PWMx Event Roll-Over Mode
  * @return None
  */
#define __LL_HRPWM_Slv_EvtRollOverMode_Set(__HRPWM__, pwmx, mode)   MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, \
        HRPWM_SLV0_PWMCR1_EEVROM_Msk, (((mode) & 0x3UL) << HRPWM_SLV0_PWMCR1_EEVROM_Pos))

/**
  * @brief  Slave PWMx ADC Roll-Over Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mode PWMx ADC Roll-Over Mode
  * @return None
  */
#define __LL_HRPWM_Slv_ADCRollOverMode_Set(__HRPWM__, pwmx, mode)   MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, \
        HRPWM_SLV0_PWMCR1_ADROM_Msk, (((mode) & 0x3UL) << HRPWM_SLV0_PWMCR1_ADROM_Pos))

/**
  * @brief  Slave PWMx Output Roll-Over Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mode PWMx Output Roll-Over Mode
  * @return None
  */
#define __LL_HRPWM_Slv_OutputRollOverMode_Set(__HRPWM__, pwmx, mode)    MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, \
        HRPWM_SLV0_PWMCR1_OUTROM_Msk, (((mode) & 0x3UL) << HRPWM_SLV0_PWMCR1_OUTROM_Pos))

/**
  * @brief  Slave PWMx Counter Roll-Over Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mode PWMx Counter Roll-Over Mode
  * @return None
  */
#define __LL_HRPWM_Slv_CntrRollOverMode_Set(__HRPWM__, pwmx, mode)  MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, \
        HRPWM_SLV0_PWMCR1_ROM_Msk, (((mode) & 0x3UL) << HRPWM_SLV0_PWMCR1_ROM_Pos))

/**
  * @brief  Slave PWMx Capture B Mode Set
  * @note   The function is independent of the Auto-Delayed mode and the DELCMPD/DELCMPB configuration
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mode PWMx Capture B Mode @ref HRPWM_Slv_CapModeETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CapBMode_Set(__HRPWM__, pwmx, mode)          MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, \
        HRPWM_SLV0_PWMCR1_CAPBM_Msk, (((mode) & 0x1UL) << HRPWM_SLV0_PWMCR1_CAPBM_Pos))

/**
  * @brief  Slave PWMx Capture B Mode Get
  * @note   The function is independent of the Auto-Delayed mode and the DELCMPD/DELCMPB configuration
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return PWMx Capture B Mode @ref HRPWM_Slv_CapModeETypeDef
  */
#define __LL_HRPWM_Slv_CapBMode_Get(__HRPWM__, pwmx)                \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_CAPBM_Msk, HRPWM_SLV0_PWMCR1_CAPBM_Pos)

/**
  * @brief  Slave PWMx Counter Direction Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mode PWMx Counter Direction Mode
  * @return None
  */
#define __LL_HRPWM_SLV_CntrDirMode_Set(__HRPWM__, pwmx, mode)       MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, \
        HRPWM_SLV0_PWMCR1_UDM_Msk, (((mode) & 0x1UL) << HRPWM_SLV0_PWMCR1_UDM_Pos))

/**
  * @brief  Slave PWMx Capture A Mode Set
  * @note   The function is independent of the Auto-Delayed mode and the DELCMPD/DELCMPB configuration
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mode PWMx Capture A Mode @ref HRPWM_Slv_CapModeETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CapAMode_Set(__HRPWM__, pwmx, mode)          MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, \
        HRPWM_SLV0_PWMCR1_CAPAM_Msk, (((mode) & 0x1UL) << HRPWM_SLV0_PWMCR1_CAPAM_Pos))

/**
  * @brief  Slave PWMx Capture A Mode Get
  * @note   The function is independent of the Auto-Delayed mode and the DELCMPD/DELCMPB configuration
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return PWMx Capture A Mode @ref HRPWM_Slv_CapModeETypeDef
  */
#define __LL_HRPWM_Slv_CapAMode_Get(__HRPWM__, pwmx)                \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_CAPAM_Msk, HRPWM_SLV0_PWMCR1_CAPAM_Pos)

/**
  * @brief  Slave PWMx DAC Reset Trigger Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  src PWMx DAC Reset Trigger Source
  * @return None
  */
#define __LL_HRPWM_Slv_DACRstTrigSrc_Set(__HRPWM__, pwmx, src)      MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, \
        HRPWM_SLV0_PWMCR1_DCDR_Msk, (((src) & 0x1UL) << HRPWM_SLV0_PWMCR1_DCDR_Pos))

/**
  * @brief  Slave PWMx DAC Step Trigger Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  src PWMx DAC Step Trigger Source
  * @return None
  */
#define __LL_HRPWM_Slv_DACStepTrigSrc_Set(__HRPWM__, pwmx, src)     MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, \
        HRPWM_SLV0_PWMCR1_DCDS_Msk, (((src) & 0x1UL) << HRPWM_SLV0_PWMCR1_DCDS_Pos))

/**
  * @brief  Slave PWMx DAC Reset/Step Trigger Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_DACRstStepTrig_En(__HRPWM__, pwmx)           \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_DCDE_Msk)

/**
  * @brief  Slave PWMx DAC Reset/Step Trigger Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_DACRstStepTrig_Dis(__HRPWM__, pwmx)          \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMCR1, HRPWM_SLV0_PWMCR1_DCDE_Msk)


/**
  * @brief  Slave PWMx OUTB Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return PWMx OUTB Level
  */
#define __LL_HRPWM_Slv_OutB_Get(__HRPWM__, pwmx)                \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_OUTB_Msk, HRPWM_SLV0_PWMISR_OUTB_Pos)

/**
  * @brief  Slave PWMx OUTA Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return PWMx OUTA Level
  */
#define __LL_HRPWM_Slv_OutA_Get(__HRPWM__, pwmx)                \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_OUTA_Msk, HRPWM_SLV0_PWMISR_OUTA_Pos)

/**
  * @brief  Slave PWMx OUTB Protection Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return PWMx OUTB Protection Level
  */
#define __LL_HRPWM_Slv_OutBProt_Get(__HRPWM__, pwmx)            \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_OUTBSTA_Msk, HRPWM_SLV0_PWMISR_OUTBSTA_Pos)

/**
  * @brief  Slave PWMx OUTA Protection Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return PWMx OUTA Protection Level
  */
#define __LL_HRPWM_Slv_OutAProt_Get(__HRPWM__, pwmx)            \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_OUTASTA_Msk, HRPWM_SLV0_PWMISR_OUTASTA_Pos)

/**
  * @brief  Slave PWMx Push-Pull Output Status Protection Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 OUTA Push-Pull Output, OUTB Force Invalid
  * @retval 1 OUTB Push-Pull Output, OUTA Force Invalid
  */
#define __LL_HRPWM_Slv_PushPullOutputStaProt_Get(__HRPWM__, pwmx)   \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_IPPSTA_Msk, HRPWM_SLV0_PWMISR_IPPSTA_Pos)

/**
  * @brief  Slave PWMx Push-Pull Output Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 OUTA Push-Pull Output, OUTB Force Invalid
  * @retval 1 OUTB Push-Pull Output, OUTA Force Invalid
  */
#define __LL_HRPWM_Slv_PushPullOutputSta_Get(__HRPWM__, pwmx)   \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CPPSTA_Msk, HRPWM_SLV0_PWMISR_CPPSTA_Pos)

/**
  * @brief  Judge is Slave PWMx Delayed Protection Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx Delayed Protection Interrupt Pending
  * @retval 1 is Slave PWMx Delayed Protection Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsDlyProtIntPnd(__HRPWM__, pwmx)         \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_DLYPRT_Msk, HRPWM_SLV0_PWMISR_DLYPRT_Pos)

/**
  * @brief  Slave PWMx Delayed Protection Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_DlyProtIntPnd_Clr(__HRPWM__, pwmx)       \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_DLYPRT_Msk)

/**
  * @brief  Judge is Slave PWMx Capture B Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx Capture B Interrupt Pending
  * @retval 1 is Slave PWMx Capture B Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsCapBIntPnd(__HRPWM__, pwmx)            \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CAPB_Msk, HRPWM_SLV0_PWMISR_CAPB_Pos)

/**
  * @brief  Slave PWMx Capture B Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CapBIntPnd_Clr(__HRPWM__, pwmx)          \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CAPB_Msk)

/**
  * @brief  Judge is Slave PWMx Capture A Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx Capture A Interrupt Pending
  * @retval 1 is Slave PWMx Capture A Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsCapAIntPnd(__HRPWM__, pwmx)            \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CAPA_Msk, HRPWM_SLV0_PWMISR_CAPA_Pos)

/**
  * @brief  Slave PWMx Capture A Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CapAIntPnd_Clr(__HRPWM__, pwmx)          \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CAPA_Msk)

/**
  * @brief  Judge is Slave PWMx Repetition Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx Repetition Interrupt Pending
  * @retval 1 is Slave PWMx Repetition Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsRepIntPnd(__HRPWM__, pwmx)             \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_REP_Msk, HRPWM_SLV0_PWMISR_REP_Pos)

/**
  * @brief  Slave PWMx Repetition Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_RepIntPnd_Clr(__HRPWM__, pwmx)           \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_REP_Msk)

/**
  * @brief  Judge is Slave PWMx Reset Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx Reset Interrupt Pending
  * @retval 1 is Slave PWMx Reset Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsRstIntPnd(__HRPWM__, pwmx)             \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_RST_Msk, HRPWM_SLV0_PWMISR_RST_Pos)

/**
  * @brief  Slave PWMx Reset Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_RstIntPnd_Clr(__HRPWM__, pwmx)           \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_RST_Msk)

/**
  * @brief  Judge is Slave PWMx OutB Clear Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx OutB Clear Interrupt Pending
  * @retval 1 is Slave PWMx OutB Clear Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsOutBClrIntPnd(__HRPWM__, pwmx)         \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CLRB_Msk, HRPWM_SLV0_PWMISR_CLRB_Pos)

/**
  * @brief  Slave PWMx OutB Clear Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBClrIntPnd_Clr(__HRPWM__, pwmx)       \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CLRB_Msk)

/**
  * @brief  Judge is Slave PWMx OutB Set Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx OutB Set Interrupt Pending
  * @retval 1 is Slave PWMx OutB Set Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsOutBSetIntPnd(__HRPWM__, pwmx)         \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_SETB_Msk, HRPWM_SLV0_PWMISR_SETB_Pos)

/**
  * @brief  Slave PWMx OutB Set Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBSetIntPnd_Clr(__HRPWM__, pwmx)       \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_SETB_Msk)

/**
  * @brief  Judge is Slave PWMx OutA Clear Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx OutA Clear Interrupt Pending
  * @retval 1 is Slave PWMx OutA Clear Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsOutAClrIntPnd(__HRPWM__, pwmx)         \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CLRA_Msk, HRPWM_SLV0_PWMISR_CLRA_Pos)

/**
  * @brief  Slave PWMx OutA Clear Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutAClrIntPnd_Clr(__HRPWM__, pwmx)       \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CLRA_Msk)

/**
  * @brief  Judge is Slave PWMx OutA Set Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx OutA Set Interrupt Pending
  * @retval 1 is Slave PWMx OutA Set Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsOutASetIntPnd(__HRPWM__, pwmx)         \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_SETA_Msk, HRPWM_SLV0_PWMISR_SETA_Pos)

/**
  * @brief  Slave PWMx OutA Set Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutASetIntPnd_Clr(__HRPWM__, pwmx)       \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_SETA_Msk)

/**
  * @brief  Judge is Slave PWMx Update Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx Update Interrupt Pending
  * @retval 1 is Slave PWMx Update Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsUpdateIntPnd(__HRPWM__, pwmx)          \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_UPD_Msk, HRPWM_SLV0_PWMISR_UPD_Pos)

/**
  * @brief  Slave PWMx Update Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_UpdateIntPnd_Clr(__HRPWM__, pwmx)        \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_UPD_Msk)

/**
  * @brief  Judge is Slave PWMx Period/Roll-Over Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx Period/Roll-Over Interrupt Pending
  * @retval 1 is Slave PWMx Period/Roll-Over Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsPrdRollOverIntPnd(__HRPWM__, pwmx)     \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_PER_Msk, HRPWM_SLV0_PWMISR_PER_Pos)

/**
  * @brief  Slave PWMx Period/Roll-Over Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PrdRollOverIntPnd_Clr(__HRPWM__, pwmx)   \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_PER_Msk)

/**
  * @brief  Judge is Slave PWMx Compare D Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx Compare D Interrupt Pending
  * @retval 1 is Slave PWMx Compare D Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsCmpDIntPnd(__HRPWM__, pwmx)            \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPD_Msk, HRPWM_SLV0_PWMISR_CMPD_Pos)

/**
  * @brief  Slave PWMx Compare D Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpDIntPnd_Clr(__HRPWM__, pwmx)          \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPD_Msk)

/**
  * @brief  Judge is Slave PWMx Compare C Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx Compare C Interrupt Pending
  * @retval 1 is Slave PWMx Compare C Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsCmpCIntPnd(__HRPWM__, pwmx)            \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPC_Msk, HRPWM_SLV0_PWMISR_CMPC_Pos)

/**
  * @brief  Slave PWMx Compare C Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpCIntPnd_Clr(__HRPWM__, pwmx)          \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPC_Msk)

/**
  * @brief  Judge is Slave PWMx Compare B Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx Compare B Interrupt Pending
  * @retval 1 is Slave PWMx Compare B Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsCmpBIntPnd(__HRPWM__, pwmx)            \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPB_Msk, HRPWM_SLV0_PWMISR_CMPB_Pos)

/**
  * @brief  Slave PWMx Compare B Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpBIntPnd_Clr(__HRPWM__, pwmx)          \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPB_Msk)

/**
  * @brief  Judge is Slave PWMx Compare A Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 isn't Slave PWMx Compare A Interrupt Pending
  * @retval 1 is Slave PWMx Compare A Interrupt Pending
  */
#define __LL_HRPWM_Slv_IsCmpAIntPnd(__HRPWM__, pwmx)            \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPA_Msk, HRPWM_SLV0_PWMISR_CMPA_Pos)

/**
  * @brief  Slave PWMx Compare A Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpAIntPnd_Clr(__HRPWM__, pwmx)          \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR, HRPWM_SLV0_PWMISR_CMPA_Msk)

/**
  * @brief  HRPWM Slave PWMx All Interrupt Pending Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return HRPWM Slave PWMx All Interrupt Pending
  */
#define __LL_HRPWM_Slv_AllIntPnd_Get(__HRPWM__, pwmx)           READ_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMISR)


/**
  * @brief  Slave PWMx Delayed Protection DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_DlyProt_DMA_En(__HRPWM__, pwmx)          \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_DLYPRTDE_Msk)

/**
  * @brief  Slave PWMx Delayed Protection DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_DlyProt_DMA_Dis(__HRPWM__, pwmx)         \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_DLYPRTDE_Msk)

/**
  * @brief  Slave PWMx Capture B DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CapB_DMA_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPBDE_Msk)

/**
  * @brief  Slave PWMx Capture B DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CapB_DMA_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPBDE_Msk)

/**
  * @brief  Slave PWMx Capture A DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CapA_DMA_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPADE_Msk)

/**
  * @brief  Slave PWMx Capture A DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CapA_DMA_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPADE_Msk)

/**
  * @brief  Slave PWMx Repetition DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Rep_DMA_En(__HRPWM__, pwmx)              \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_REPDE_Msk)

/**
  * @brief  Slave PWMx Repetition DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Rep_DMA_Dis(__HRPWM__, pwmx)             \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_REPDE_Msk)

/**
  * @brief  Slave PWMx Reset DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Rst_DMA_En(__HRPWM__, pwmx)              \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_RSTDE_Msk)

/**
  * @brief  Slave PWMx Reset DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Rst_DMA_Dis(__HRPWM__, pwmx)             \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_RSTDE_Msk)

/**
  * @brief  Slave PWMx OutB Clear DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBClr_DMA_En(__HRPWM__, pwmx)          \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRBDE_Msk)

/**
  * @brief  Slave PWMx OutB Clear DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBClr_DMA_Dis(__HRPWM__, pwmx)         \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRBDE_Msk)

/**
  * @brief  Slave PWMx OutB Set DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBSet_DMA_En(__HRPWM__, pwmx)          \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETBDE_Msk)

/**
  * @brief  Slave PWMx OutB Set DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBSet_DMA_Dis(__HRPWM__, pwmx)         \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETBDE_Msk)

/**
  * @brief  Slave PWMx OutA Clear DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutAClr_DMA_En(__HRPWM__, pwmx)          \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRADE_Msk)

/**
  * @brief  Slave PWMx OutA Clear DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutAClr_DMA_Dis(__HRPWM__, pwmx)         \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRADE_Msk)

/**
  * @brief  Slave PWMx OutA Set DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutASet_DMA_En(__HRPWM__, pwmx)          \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETADE_Msk)

/**
  * @brief  Slave PWMx OutA Set DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutASet_DMA_Dis(__HRPWM__, pwmx)         \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETADE_Msk)

/**
  * @brief  Slave PWMx Update DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Update_DMA_En(__HRPWM__, pwmx)           \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_UPDDE_Msk)

/**
  * @brief  Slave PWMx Update DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Update_DMA_Dis(__HRPWM__, pwmx)          \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_UPDDE_Msk)

/**
  * @brief  Slave PWMx Period/Roll-Over DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PrdRollOver_DMA_En(__HRPWM__, pwmx)      \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_PERDE_Msk)

/**
  * @brief  Slave PWMx Period/Roll-Over DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PrdRollOver_DMA_Dis(__HRPWM__, pwmx)     \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_PERDE_Msk)

/**
  * @brief  Slave PWMx Compare D DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpD_DMA_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPDDE_Msk)

/**
  * @brief  Slave PWMx Compare D DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpD_DMA_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPDDE_Msk)

/**
  * @brief  Slave PWMx Compare C DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpC_DMA_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPCDE_Msk)

/**
  * @brief  Slave PWMx Compare C DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpC_DMA_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPCDE_Msk)

/**
  * @brief  Slave PWMx Compare B DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpB_DMA_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPBDE_Msk)

/**
  * @brief  Slave PWMx Compare B DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpB_DMA_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPBDE_Msk)

/**
  * @brief  Slave PWMx Compare A DMA Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpA_DMA_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPADE_Msk)

/**
  * @brief  Slave PWMx Compare A DMA Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpA_DMA_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPADE_Msk)

/**
  * @brief  Slave PWMx DMA Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  dma_msk DMA Mask Combination @ref HRPWM_Slv_DMAETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_DMA_En_Cfg(__HRPWM__, pwmx, dma_msk)     \
        MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, 0x7fff0000UL, ((dma_msk) & 0x7fff0000UL))

/**
  * @brief  Slave PWMx Delayed Protection Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_DlyProt_INT_En(__HRPWM__, pwmx)          \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_DLYPRTIE_Msk)

/**
  * @brief  Slave PWMx Delayed Protection Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_DlyProt_INT_Dis(__HRPWM__, pwmx)         \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_DLYPRTIE_Msk)

/**
  * @brief  Slave PWMx Capture B Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CapB_INT_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPBIE_Msk)

/**
  * @brief  Slave PWMx Capture B Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CapB_INT_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPBIE_Msk)

/**
  * @brief  Slave PWMx Capture A Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CapA_INT_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPAIE_Msk)

/**
  * @brief  Slave PWMx Capture A Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CapA_INT_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CAPAIE_Msk)

/**
  * @brief  Slave PWMx Repetition Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Rep_INT_En(__HRPWM__, pwmx)              \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_REPIE_Msk)

/**
  * @brief  Slave PWMx Repetition Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Rep_INT_Dis(__HRPWM__, pwmx)             \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_REPIE_Msk)

/**
  * @brief  Slave PWMx Reset Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Rst_INT_En(__HRPWM__, pwmx)              \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_RSTIE_Msk)

/**
  * @brief  Slave PWMx Reset Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Rst_INT_Dis(__HRPWM__, pwmx)             \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_RSTIE_Msk)

/**
  * @brief  Slave PWMx OutB Clear Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBClr_INT_En(__HRPWM__, pwmx)          \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRBIE_Msk)

/**
  * @brief  Slave PWMx OutB Clear Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBClr_INT_Dis(__HRPWM__, pwmx)         \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRBIE_Msk)

/**
  * @brief  Slave PWMx OutB Set Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBSet_INT_En(__HRPWM__, pwmx)          \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETBIE_Msk)

/**
  * @brief  Slave PWMx OutB Set Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBSet_INT_Dis(__HRPWM__, pwmx)         \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETBIE_Msk)

/**
  * @brief  Slave PWMx OutA Clear Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutAClr_INT_En(__HRPWM__, pwmx)          \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRAIE_Msk)

/**
  * @brief  Slave PWMx OutA Clear Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutAClr_INT_Dis(__HRPWM__, pwmx)         \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CLRAIE_Msk)

/**
  * @brief  Slave PWMx OutA Set Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutASet_INT_En(__HRPWM__, pwmx)          \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETAIE_Msk)

/**
  * @brief  Slave PWMx OutA Set Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutASet_INT_Dis(__HRPWM__, pwmx)         \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_SETAIE_Msk)

/**
  * @brief  Slave PWMx Update Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Update_INT_En(__HRPWM__, pwmx)           \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_UPDIE_Msk)

/**
  * @brief  Slave PWMx Update Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Update_INT_Dis(__HRPWM__, pwmx)          \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_UPDIE_Msk)

/**
  * @brief  Slave PWMx Period/Roll-Over Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PrdRollOver_INT_En(__HRPWM__, pwmx)      \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_PERIE_Msk)

/**
  * @brief  Slave PWMx Period/Roll-Over Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_PrdRollOver_INT_Dis(__HRPWM__, pwmx)     \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_PERIE_Msk)

/**
  * @brief  Slave PWMx Compare D Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpD_INT_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPDIE_Msk)

/**
  * @brief  Slave PWMx Compare D Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpD_INT_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPDIE_Msk)

/**
  * @brief  Slave PWMx Compare C Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpC_INT_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPCIE_Msk)

/**
  * @brief  Slave PWMx Compare C Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpC_INT_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPCIE_Msk)

/**
  * @brief  Slave PWMx Compare B Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpB_INT_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPBIE_Msk)

/**
  * @brief  Slave PWMx Compare B Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpB_INT_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPBIE_Msk)

/**
  * @brief  Slave PWMx Compare A Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpA_INT_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPAIE_Msk)

/**
  * @brief  Slave PWMx Compare A Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CmpA_INT_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, HRPWM_SLV0_PWMDIER_CMPAIE_Msk)

/**
  * @brief  Slave PWMx Interrupt Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  int_msk Interrupt Mask Combination @ref HRPWM_Slv_IntETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_INT_En_Cfg(__HRPWM__, pwmx, int_msk)     \
        MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, 0x7fffUL, ((int_msk) & 0x7fffUL))

/**
  * @brief  HRPWM Slave PWMx All Interrupt Enable Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return HRPWM Slave PWMx All Interrupt Enable Status
  */
#define __LL_HRPWM_Slv_AllIntEn_Get(__HRPWM__, pwmx)            READ_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PWMDIER, 0x7fffUL)


/**
  * @brief  Slave PWMx Counter Write
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  cnt Slave PWMx Counter
  * @return None
  */
#define __LL_HRPWM_Slv_Counter_Wrtie(__HRPWM__, pwmx, cnt)                                                                               \
        do {                                                                                                                             \
            WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CNTR, HRPWM_SLV0_CNTR_CNTWR_Msk | ((cnt) & 0xffffUL));                    \
            while (READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CNTR, HRPWM_SLV0_CNTR_CNTWR_Msk, HRPWM_SLV0_CNTR_CNTWR_Pos));\
        } while (0)

/**
  * @brief  Slave PWMx Counter Read Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_CounterRead_En(__HRPWM__, pwmx)                                                                                   \
        do {                                                                                                                             \
            WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CNTR, HRPWM_SLV0_CNTR_CNTRD_Msk);                                         \
            while (READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CNTR, HRPWM_SLV0_CNTR_CNTRD_Msk, HRPWM_SLV0_CNTR_CNTRD_Pos));\
        } while (0)

/**
  * @brief  Slave PWMx Counter Read
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return Slave PWMx Counter
  */
#define __LL_HRPWM_Slv_Counter_Read(__HRPWM__, pwmx)            \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CNTR, HRPWM_SLV0_CNTR_CNT_Msk, HRPWM_SLV0_CNTR_CNT_Pos)


/**
  * @brief  Slave PWMx Counter Period Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  prd Slave PWMx Counter Period
  * @return None
  */
#define __LL_HRPWM_Slv_CntrPeriod_Set(__HRPWM__, pwmx, prd)     \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PERR, ((prd) & 0xffffUL))

/**
  * @brief  Slave PWMx Counter Period Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return Slave PWMx Counter Period
  */
#define __LL_HRPWM_Slv_CntrPeriod_Get(__HRPWM__, pwmx)          READ_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.PERR)


/**
  * @brief  Slave PWMx Repetition Period Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  prd Slave PWMx Repetition Period
  * @return None
  */
#define __LL_HRPWM_Slv_RepPeriod_Set(__HRPWM__, pwmx, prd)      \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.REPR, ((prd) & 0xffUL))

/**
  * @brief  Slave PWMx Repetition Period Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return Slave PWMx Repetition Period
  */
#define __LL_HRPWM_Slv_RepPeriod_Get(__HRPWM__, pwmx)           READ_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.REPR)


/**
  * @brief  Slave PWMx Compare A Value Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  val Slave PWMx Compare A Value
  * @return None
  */
#define __LL_HRPWM_Slv_CmpAVal_Set(__HRPWM__, pwmx, val)        \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CMPAR, ((val) & 0xffffUL))

/**
  * @brief  Slave PWMx Compare A Value Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return Slave PWMx Compare A Value
  */
#define __LL_HRPWM_Slv_CmpAVal_Get(__HRPWM__, pwmx)             READ_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CMPAR)


/**
  * @brief  Slave PWMx Compare B Value Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  val Slave PWMx Compare B Value
  * @return None
  */
#define __LL_HRPWM_Slv_CmpBVal_Set(__HRPWM__, pwmx, val)        \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CMPBR, ((val) & 0xffffUL))

/**
  * @brief  Slave PWMx Compare B Value Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return Slave PWMx Compare B Value
  */
#define __LL_HRPWM_Slv_CmpBVal_Get(__HRPWM__, pwmx)             READ_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CMPBR)


/**
  * @brief  Slave PWMx Compare C Value Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  val Slave PWMx Compare C Value
  * @return None
  */
#define __LL_HRPWM_Slv_CmpCVal_Set(__HRPWM__, pwmx, val)        \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CMPCR, ((val) & 0xffffUL))

/**
  * @brief  Slave PWMx Compare C Value Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return Slave PWMx Compare C Value
  */
#define __LL_HRPWM_Slv_CmpCVal_Get(__HRPWM__, pwmx)             READ_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CMPCR)


/**
  * @brief  Slave PWMx Compare D Value Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  val Slave PWMx Compare D Value
  * @return None
  */
#define __LL_HRPWM_Slv_CmpDVal_Set(__HRPWM__, pwmx, val)        \
        WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CMPDR, ((val) & 0xffffUL))

/**
  * @brief  Slave PWMx Compare D Value Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return Slave PWMx Compare D Value
  */
#define __LL_HRPWM_Slv_CmpDVal_Get(__HRPWM__, pwmx)             READ_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CMPDR)


/**
  * @brief  Slave PWMx Capture A Counter Direction Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 Capture A Counter Direction Up
  * @retval 1 Capture A Counter Direction Down
  */
#define __LL_HRPWM_Slv_CapACntrDir_Get(__HRPWM__, pwmx)         \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CAPAR, HRPWM_SLV0_CAPAR_DIR_Msk, HRPWM_SLV0_CAPAR_DIR_Pos)

/**
  * @brief  Slave PWMx Capture A Counter Value Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return Capture A Counter Value
  */
#define __LL_HRPWM_Slv_CapACntrVal_Get(__HRPWM__, pwmx)         \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CAPAR, HRPWM_SLV0_CAPAR_CAPA_Msk, HRPWM_SLV0_CAPAR_CAPA_Pos)


/**
  * @brief  Slave PWMx Capture B Counter Direction Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 Capture B Counter Direction Up
  * @retval 1 Capture B Counter Direction Down
  */
#define __LL_HRPWM_Slv_CapBCntrDir_Get(__HRPWM__, pwmx)         \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CAPBR, HRPWM_SLV0_CAPBR_DIR_Msk, HRPWM_SLV0_CAPBR_DIR_Pos)

/**
  * @brief  Slave PWMx Capture B Counter Value Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return Capture B Counter Value
  */
#define __LL_HRPWM_Slv_CapBCntrVal_Get(__HRPWM__, pwmx)         \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CAPBR, HRPWM_SLV0_CAPBR_CAPB_Msk, HRPWM_SLV0_CAPBR_CAPB_Pos)


/**
  * @brief  Slave PWMx Falling Edge DeadTime Direction Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  dir PWMx Falling Edge DeadTime Direction
  * @return None
  */
#define __LL_HRPWM_Slv_FallingDtDir_Set(__HRPWM__, pwmx, dir)   MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.DTR, \
        HRPWM_SLV0_DTR_SDTF_Msk, (((dir) & 0x1UL) << HRPWM_SLV0_DTR_SDTF_Pos))

/**
  * @brief  Slave PWMx Falling Edge DeadTime Time Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  time PWMx Falling Edge DeadTime Time
  * @return None
  */
#define __LL_HRPWM_Slv_FallingDtTime_Set(__HRPWM__, pwmx, time)  MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.DTR, \
        HRPWM_SLV0_DTR_DTF_Msk, (((time) & 0xfffUL) << HRPWM_SLV0_DTR_DTF_Pos))

/**
  * @brief  Slave PWMx Rising Edge DeadTime Direction Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  dir PWMx Rising Edge DeadTime Direction
  * @return None
  */
#define __LL_HRPWM_Slv_RisingDtDir_Set(__HRPWM__, pwmx, dir)    MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.DTR, \
        HRPWM_SLV0_DTR_SDTR_Msk, (((dir) & 0x1UL) << HRPWM_SLV0_DTR_SDTR_Pos))

/**
  * @brief  Slave PWMx Rising Edge DeadTime Time Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  time PWMx Rising Edge DeadTime Time
  * @return None
  */
#define __LL_HRPWM_Slv_RisingDtTime_Set(__HRPWM__, pwmx, time)  MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.DTR, \
        HRPWM_SLV0_DTR_DTR_Msk, (((time) & 0xfffUL) << HRPWM_SLV0_DTR_DTR_Pos))


/**
  * @brief  Slave PWMx OUTA Set Event Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  evt PWMx OUTA Set Event @ref HRPWM_Slv_OutCtrlEvtETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutASetEvtEn_Cfg(__HRPWM__, pwmx, evt)   WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.SETAR, evt)


/**
  * @brief  Slave PWMx OUTA Clear Event Enable  Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  evt PWMx OUTA Clear Event @ref HRPWM_Slv_OutCtrlEvtETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutAClrEvtEn_Cfg(__HRPWM__, pwmx, evt)   WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CLRAR, evt)


/**
  * @brief  Slave PWMx OUTB Set Event Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  evt PWMx OUTB Set Event @ref HRPWM_Slv_OutCtrlEvtETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBSetEvtEn_Cfg(__HRPWM__, pwmx, evt)   WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.SETBR, evt)


/**
  * @brief  Slave PWMx OUTB Clear Event Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  evt PWMx OUTB Clear Event @ref HRPWM_Slv_OutCtrlEvtETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBClrEvtEn_Cfg(__HRPWM__, pwmx, evt)   WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CLRBR, evt)


/**
  * @brief  Slave PWMx External Event x Filter Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  evt_x PWMx External Event Number @ref HRPWM_ExtEvtNumETypeDef
  * @param  fil PWMx External Event x Filter @ref HRPWM_Slv_ExtEvtFilETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_ExtEvtFil_Set(__HRPWM__, pwmx, evt_x, fil)                                                                           \
        MODIFY_REG(__LL_HRPWM_REG_OFFSET((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.EEFR0, (evt_x) / 5 % ((HRPWM_EXT_EVT_NUMS + 4) / 5)), \
        0xfUL << (1 + ((evt_x) % 5) * 5), (((fil) & 0xfUL) << (1 + ((evt_x) % 5) * 5)))

/**
  * @brief  Slave PWMx External Event x Blank Latch Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  evt_x PWMx External Event Number @ref HRPWM_ExtEvtNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_ExtEvtBlkLatch_En(__HRPWM__, pwmx, evt_x)                                                                      \
        SET_BIT(__LL_HRPWM_REG_OFFSET((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.EEFR0, (evt_x) / 5 % ((HRPWM_EXT_EVT_NUMS + 4) / 5)),\
            BIT(((evt_x) % 5) * 5))

/**
  * @brief  Slave PWMx External Event x Blank Latch Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  evt_x PWMx External Event Number @ref HRPWM_ExtEvtNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_ExtEvtBlkLatch_Dis(__HRPWM__, pwmx, evt_x)                                                                       \
        CLEAR_BIT(__LL_HRPWM_REG_OFFSET((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.EEFR0, (evt_x) / 5 % ((HRPWM_EXT_EVT_NUMS + 4) / 5)),\
            BIT(((evt_x) % 5) * 5))


/**
  * @brief  Slave PWMx External Event A Counter Threshold Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  thres PWMx External Event A Count Threshold
  * @return None
  */
#define __LL_HRPWM_Slv_EvtACntrThres_Set(__HRPWM__, pwmx, thres)    MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.EEFR2, \
        HRPWM_SLV0_EEFR2_EEVACNT_Msk, (((thres) & 0x3fUL) << HRPWM_SLV0_EEFR2_EEVACNT_Pos))

/**
  * @brief  Slave PWMx External Event A Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  src PWMx External Event A Source @ref HRPWM_ExtEvtNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_EvtASrc_Set(__HRPWM__, pwmx, src)            MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.EEFR2, \
        HRPWM_SLV0_EEFR2_EEVASEL_Msk, (((src) & 0xfUL) << HRPWM_SLV0_EEFR2_EEVASEL_Pos))

/**
  * @brief  Slave PWMx External Event A Counter Reset Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mode PWMx External Event A Counter Reset Mode @ref HRPWM_Slv_EvtACntrRstModeETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_EvtACntrRstMode_Set(__HRPWM__, pwmx, mode)    MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.EEFR2, \
        HRPWM_SLV0_EEFR2_EEVARSTM_Msk, (((mode) & 0x1UL) << HRPWM_SLV0_EEFR2_EEVARSTM_Pos))

/**
  * @brief  Slave PWMx External Event A Counter Reset
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_EvtACntr_Rst(__HRPWM__, pwmx)            \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.EEFR2, HRPWM_SLV0_EEFR2_EEVACRES_Msk)

/**
  * @brief  Slave PWMx External Event A Counter Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_EvtACntr_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.EEFR2, HRPWM_SLV0_EEFR2_EEVACE_Msk)

/**
  * @brief  Slave PWMx External Event A Counter Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_EvtACntr_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.EEFR2, HRPWM_SLV0_EEFR2_EEVACE_Msk)


/**
  * @brief  Slave PWMx Counter Reset Event Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  evt PWMx Counter Reset Event @ref HRPWM_SlvX_CntrRstEvtETypeDef (X = 0 ~ HRPWM_SLV_PWM_NUMS-1)
  * @return None
  */
#define __LL_HRPWM_Slv_CntrRstEvtEn_Cfg(__HRPWM__, pwmx, evt)                                   \
        do {                                                                                    \
            WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.RSTR, ((evt) & 0xFFFFFFFFUL));   \
            WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.RSTER, ((evt) >> 32ULL));        \
        } while(0)


/**
  * @brief  Slave PWMx Chopper Start Pulse Width Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  width PWMx Chopper Start Pulse Width
  * @return None
  */
#define __LL_HRPWM_Slv_ChopStartPulseWidth_Set(__HRPWM__, pwmx, width)  MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CHPR, \
        HRPWM_SLV0_CHPR_STRPW_Msk, (((width) & 0xfUL) << HRPWM_SLV0_CHPR_STRPW_Pos))

/**
  * @brief  Slave PWMx Chopper Duty Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  duty PWMx Chopper Duty
  * @return None
  */
#define __LL_HRPWM_Slv_ChopDuty_Set(__HRPWM__, pwmx, duty)              MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CHPR, \
        HRPWM_SLV0_CHPR_CARDTY_Msk, (((duty) & 0x7UL) << HRPWM_SLV0_CHPR_CARDTY_Pos))

/**
  * @brief  Slave PWMx Chopper Frequency Division Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  div PWMx Chopper Frequency Division
  * @return None
  */
#define __LL_HRPWM_Slv_ChopFreqDiv_Set(__HRPWM__, pwmx, div)            MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CHPR, \
        HRPWM_SLV0_CHPR_CARFRQ_Msk, (((div) & 0xfUL) << HRPWM_SLV0_CHPR_CARFRQ_Pos))


/**
  * @brief  Slave PWMx Capture A Event Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  evt PWMx Capture A Event @ref HRPWM_SlvX_CapTrigEvtETypeDef (X = 0 ~ HRPWM_SLV_PWM_NUMS-1)
  * @return None
  */
#define __LL_HPRWM_Slv_CapAEvtEn_Cfg(__HRPWM__, pwmx, evt)                                       \
        do {                                                                                     \
            WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CAPACR, ((evt) & 0xFFFFFFFFUL));  \
            WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CAPACER, ((evt) >> 32ULL));       \
        } while (0)


/**
  * @brief  Slave PWMx Capture B Event Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  evt PWMx Capture B Event @ref HRPWM_SlvX_CapTrigEvtETypeDef (X = 0 ~ HRPWM_SLV_PWM_NUMS-1)
  * @return None
  */
#define __LL_HPRWM_Slv_CapBEvtEn_Cfg(__HRPWM__, pwmx, evt)                                       \
        do {                                                                                     \
            WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CAPBCR, ((evt) & 0xFFFFFFFFUL)); \
            WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.CAPBCER, ((evt) >> 32ULL));       \
        } while (0)


/**
  * @brief  Slave PWMx DeadTime Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_DeadTime_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DTEN_Msk)

/**
  * @brief  Slave PWMx DeadTime Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_DeadTime_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DTEN_Msk)

/**
  * @brief  Slave PWMx Delay Protection Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_DlyProt_En(__HRPWM__, pwmx)              \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DLYPRTEN_Msk)

/**
  * @brief  Slave PWMx Delay Protection Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_DlyProt_Dis(__HRPWM__, pwmx)             \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DLYPRTEN_Msk)

/**
  * @brief  Slave PWMx Delay Protection Mechanism Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  mech PWMx Delay Protection Mechanism
  * @return None
  */
#define __LL_HRPWM_Slv_DlyProtMech_Set(__HRPWM__, pwmx, mech)   MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, \
        HRPWM_SLV0_OUTR_DLYPRT_Msk, (((mech) & 0x7UL) << HRPWM_SLV0_OUTR_DLYPRT_Pos))

/**
  * @brief  Slave PWMx Balance Idle Auto Recover Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_BalIdleAutoRcvr_En(__HRPWM__, pwmx)      \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_BIAR_Msk)

/**
  * @brief  Slave PWMx Balance Idle Auto Recover Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_BalIdleAutoRcvr_Dis(__HRPWM__, pwmx)     \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_BIAR_Msk)

/**
  * @brief  Slave PWMx OutB Idle DeadTime Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBIdleDeadTime_En(__HRPWM__, pwmx)     \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DIDLB_Msk)

/**
  * @brief  Slave PWMx OutB Idle DeadTime Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBIdleDeadTime_Dis(__HRPWM__, pwmx)    \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DIDLB_Msk)

/**
  * @brief  Slave PWMx OutB Burst Mode Idle Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBBurstModeIdle_En(__HRPWM__, pwmx)    \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_IDLEMB_Msk)

/**
  * @brief  Slave PWMx OutB Burst Mode Idle Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBBurstModeIdle_Dis(__HRPWM__, pwmx)   \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_IDLEMB_Msk)

/**
  * @brief  Slave PWMx OutB Chopper Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBChop_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_CHPB_Msk)

/**
  * @brief  Slave PWMx OutB Chopper Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutBChop_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_CHPB_Msk)

/**
  * @brief  Slave PWMx OutB Idle Status Level Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  lvl PWMx OutB Idle Status Level
  * @return None
  */
#define __LL_HRPWM_Slv_OutBIdleLvl_Set(__HRPWM__, pwmx, lvl)    MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, \
        HRPWM_SLV0_OUTR_IDLESB_Msk, (((lvl) & 0x1UL) << HRPWM_SLV0_OUTR_IDLESB_Pos))

/**
  * @brief  Slave PWMx OutB Fault Status Level Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  lvl PWMx OutB Fault Status Level
  * @return None
  */
#define __LL_HRPWM_Slv_OutBFltLvl_Set(__HRPWM__, pwmx, lvl)     MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, \
        HRPWM_SLV0_OUTR_FAULTB_Msk, (((lvl) & 0x3UL) << HRPWM_SLV0_OUTR_FAULTB_Pos))

/**
  * @brief  Slave PWMx OutB Polarity Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  pol PWMx OutB Polarity
  * @return None
  */
#define __LL_HRPWM_Slv_OutBPol_Set(__HRPWM__, pwmx, pol)        MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, \
        HRPWM_SLV0_OUTR_POLB_Msk, (((pol) & 0x1UL) << HRPWM_SLV0_OUTR_POLB_Pos))

/**
  * @brief  Slave PWMx OutA Idle DeadTime Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutAIdleDeadTime_En(__HRPWM__, pwmx)     \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DIDLA_Msk)

/**
  * @brief  Slave PWMx OutA Idle DeadTime Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutAIdleDeadTime_Dis(__HRPWM__, pwmx)    \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_DIDLA_Msk)

/**
  * @brief  Slave PWMx OutA Burst Mode Idle Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutABurstModeIdle_En(__HRPWM__, pwmx)    \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_IDLEMA_Msk)

/**
  * @brief  Slave PWMx OutA Burst Mode Idle Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutABurstModeIdle_Dis(__HRPWM__, pwmx)   \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_IDLEMA_Msk)

/**
  * @brief  Slave PWMx OutA Chopper Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutAChop_En(__HRPWM__, pwmx)             \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_CHPA_Msk)

/**
  * @brief  Slave PWMx OutA Chopper Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_OutAChop_Dis(__HRPWM__, pwmx)            \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, HRPWM_SLV0_OUTR_CHPA_Msk)

/**
  * @brief  Slave PWMx OutA Idle Status Level Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  lvl PWMx OutA Idle Status Level
  * @return None
  */
#define __LL_HRPWM_Slv_OutAIdleLvl_Set(__HRPWM__, pwmx, lvl)    MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, \
        HRPWM_SLV0_OUTR_IDLESA_Msk, (((lvl) & 0x1UL) << HRPWM_SLV0_OUTR_IDLESA_Pos))

/**
  * @brief  Slave PWMx OutA Fault Status Level Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  lvl PWMx OutA Fault Status Level
  * @return None
  */
#define __LL_HRPWM_Slv_OutAFltLvl_Set(__HRPWM__, pwmx, lvl)     MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, \
        HRPWM_SLV0_OUTR_FAULTA_Msk, (((lvl) & 0x3UL) << HRPWM_SLV0_OUTR_FAULTA_Pos))

/**
  * @brief  Slave PWMx OutA Polarity Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  pol PWMx OutA Polarity
  * @return None
  */
#define __LL_HRPWM_Slv_OutAPol_Set(__HRPWM__, pwmx, pol)        MODIFY_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.OUTR, \
        HRPWM_SLV0_OUTR_POLA_Msk, (((pol) & 0x1UL) << HRPWM_SLV0_OUTR_POLA_Pos))


/**
  * @brief  Slave PWMx Fault 7 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt7_En(__HRPWM__, pwmx)                 \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT7EN_Msk)

/**
  * @brief  Slave PWMx Fault 7 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt7_Dis(__HRPWM__, pwmx)                \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT7EN_Msk)

/**
  * @brief  Slave PWMx Fault 6 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt6_En(__HRPWM__, pwmx)                 \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT6EN_Msk)

/**
  * @brief  Slave PWMx Fault 6 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt6_Dis(__HRPWM__, pwmx)                \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT6EN_Msk)

/**
  * @brief  Slave PWMx Fault 5 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt5_En(__HRPWM__, pwmx)                 \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT5EN_Msk)

/**
  * @brief  Slave PWMx Fault 5 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt5_Dis(__HRPWM__, pwmx)                \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT5EN_Msk)

/**
  * @brief  Slave PWMx Fault 4 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt4_En(__HRPWM__, pwmx)                 \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT4EN_Msk)

/**
  * @brief  Slave PWMx Fault 4 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt4_Dis(__HRPWM__, pwmx)                \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT4EN_Msk)

/**
  * @brief  Slave PWMx Fault 3 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt3_En(__HRPWM__, pwmx)                 \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT3EN_Msk)

/**
  * @brief  Slave PWMx Fault 3 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt3_Dis(__HRPWM__, pwmx)                \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT3EN_Msk)

/**
  * @brief  Slave PWMx Fault 2 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt2_En(__HRPWM__, pwmx)                 \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT2EN_Msk)

/**
  * @brief  Slave PWMx Fault 2 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt2_Dis(__HRPWM__, pwmx)                \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT2EN_Msk)

/**
  * @brief  Slave PWMx Fault 1 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt1_En(__HRPWM__, pwmx)                 \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT1EN_Msk)

/**
  * @brief  Slave PWMx Fault 1 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt1_Dis(__HRPWM__, pwmx)                \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT1EN_Msk)

/**
  * @brief  Slave PWMx Fault 0 Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt0_En(__HRPWM__, pwmx)                 \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT0EN_Msk)

/**
  * @brief  Slave PWMx Fault 0 Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_Flt0_Dis(__HRPWM__, pwmx)                \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, HRPWM_SLV0_FLTR_FLT0EN_Msk)

/**
  * @brief  Slave PWMx Fault x Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  fltx PWMx Fault Number @ref HRPWM_FltNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_FltX_En(__HRPWM__, pwmx, fltx)           \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, BIT((fltx) % HRPWM_FLT_NUMS))

/**
  * @brief  Slave PWMx Fault x Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  fltx PWMx Fault Number @ref HRPWM_FltNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_FltX_Dis(__HRPWM__, pwmx, fltx)          \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.FLTR, BIT((fltx) % HRPWM_FLT_NUMS))


/**
  * @brief  Slave PWMx Register Support that System DMA Write into DMADR and Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  reg Register Type Mask @ref HRPWM_Comm_BurstDMASlvRegUpdETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_SysDMAWriteUpd_Set(__HRPWM__, pwmx, reg)                               \
        SET_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.DMAUR, reg)

/**
  * @brief  Slave PWMx Register Support that System DMA Write into DMADR and Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  reg Register Type Mask @ref HRPWM_Comm_BurstDMASlvRegUpdETypeDef
  * @return None
  */
#define __LL_HRPWM_Slv_SysDMAWriteUpd_Reset(__HRPWM__, pwmx, reg)                             \
        CLEAR_BIT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.DMAUR, reg)

/**
  * @brief  Get Slave PWMx Register Support Update Register
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return Register Type Mask @ref HRPWM_Comm_BurstDMASlvRegUpdETypeDef
  */
#define __LL_HRPWM_Slv_SysDMAWriteUpd_Get(__HRPWM__, pwmx)                              \
        READ_BIT_SHIFT((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.DMAUR, 0x3fffffffUL, 0)


/**
  * @brief  Slave PWMx System DMA Address Write
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  addr Slave PWMx System DMA Address
  * @return None
  */
#define __LL_HRPWM_Slv_SysDMAAddr_Write(__HRPWM__, pwmx, addr)  WRITE_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.DMADR, addr)

/**
  * @brief  Slave PWMx System DMA Address Read
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return Slave PWMx System DMA Address
  */
#define __LL_HRPWM_Slv_SysDMAAddr_Read(__HRPWM__, pwmx)         READ_REG((__HRPWM__)->PWM[(pwmx) % PWMx_NUMS].REG.DMADR)


/**
  * @brief  Common ADC Trigger 3 Update Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src ADC Trigger 3 Update Source @ref HRPWM_Comm_ADCTrigUpdSrcETypeDEF
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig3UpdSrc_Set(__HRPWM__, src)      \
        MODIFY_REG((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_USRC3_Msk, (((src) & 0xfUL) << HRPWM_COM_CR0_USRC3_Pos))

/**
  * @brief  Common ADC Trigger 2 Update Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src ADC Trigger 2 Update Source @ref HRPWM_Comm_ADCTrigUpdSrcETypeDEF
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig2UpdSrc_Set(__HRPWM__, src)      \
        MODIFY_REG((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_USRC2_Msk, (((src) & 0xfUL) << HRPWM_COM_CR0_USRC2_Pos))

/**
  * @brief  Common ADC Trigger 1 Update Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src ADC Trigger 1 Update Source @ref HRPWM_Comm_ADCTrigUpdSrcETypeDEF
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig1UpdSrc_Set(__HRPWM__, src)      \
        MODIFY_REG((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_USRC1_Msk, (((src) & 0xfUL) << HRPWM_COM_CR0_USRC1_Pos))

/**
  * @brief  Common ADC Trigger 0 Update Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src ADC Trigger 0 Update Source @ref HRPWM_Comm_ADCTrigUpdSrcETypeDEF
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig0UpdSrc_Set(__HRPWM__, src)      \
        MODIFY_REG((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_USRC0_Msk, (((src) & 0xfUL) << HRPWM_COM_CR0_USRC0_Pos))

/**
  * @brief  Common ADC Trigger X Update Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  trigx ADC Trigger Number @ref HRPWM_ADCTrigNumETypeDef (X=0~3)
  * @param  src ADC Trigger X Update Source @ref HRPWM_Comm_ADCTrigUpdSrcETypeDEF
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrigX0To3UpdSrc_Set(__HRPWM__, trigx, src)                          \
        MODIFY_REG((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_USRC0_Msk << (((trigx) % 4) * 4), \
        (((src) & 0xfUL) << (HRPWM_COM_CR0_USRC0_Pos + ((trigx) % 4) * 4)))

/**
  * @brief  Common Burst Mode Register Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModeRegUpd_En(__HRPWM__)           CLEAR_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_BMUDIS_Msk)

/**
  * @brief  Common Burst Mode Register Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModeRegUpd_Dis(__HRPWM__)          SET_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_BMUDIS_Msk)

/**
  * @brief  Common PWM7 Register Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM7RegUpd_En(__HRPWM__)                CLEAR_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS7_Msk)

/**
  * @brief  Common PWM7 Register Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM7RegUpd_Dis(__HRPWM__)               SET_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS7_Msk)

/**
  * @brief  Common PWM6 Register Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM6RegUpd_En(__HRPWM__)                CLEAR_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS6_Msk)

/**
  * @brief  Common PWM6 Register Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM6RegUpd_Dis(__HRPWM__)               SET_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS6_Msk)

/**
  * @brief  Common PWM5 Register Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM5RegUpd_En(__HRPWM__)                CLEAR_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS5_Msk)

/**
  * @brief  Common PWM5 Register Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM5RegUpd_Dis(__HRPWM__)               SET_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS5_Msk)

/**
  * @brief  Common PWM4 Register Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM4RegUpd_En(__HRPWM__)                CLEAR_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS4_Msk)

/**
  * @brief  Common PWM4 Register Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM4RegUpd_Dis(__HRPWM__)               SET_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS4_Msk)

/**
  * @brief  Common PWM3 Register Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM3RegUpd_En(__HRPWM__)                CLEAR_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS3_Msk)

/**
  * @brief  Common PWM3 Register Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM3RegUpd_Dis(__HRPWM__)               SET_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS3_Msk)

/**
  * @brief  Common PWM2 Register Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM2RegUpd_En(__HRPWM__)                CLEAR_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS2_Msk)

/**
  * @brief  Common PWM2 Register Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM2RegUpd_Dis(__HRPWM__)               SET_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS2_Msk)

/**
  * @brief  Common PWM1 Register Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM1RegUpd_En(__HRPWM__)                CLEAR_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS1_Msk)

/**
  * @brief  Common PWM1 Register Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM1RegUpd_Dis(__HRPWM__)               SET_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS1_Msk)

/**
  * @brief  Common PWM0 Register Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM0RegUpd_En(__HRPWM__)                CLEAR_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS0_Msk)

/**
  * @brief  Common PWM0 Register Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM0RegUpd_Dis(__HRPWM__)               SET_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_UDIS0_Msk)

/**
  * @brief  Common PWMx Register Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_PWMxRegUpd_En(__HRPWM__, pwmx)          \
        CLEAR_BIT((__HRPWM__)->Common.CR0, BIT(((pwmx) % PWMx_NUMS) + HRPWM_COM_CR0_UDIS0_Pos))

/**
  * @brief  Common PWMx Register Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_PWMxRegUpd_Dis(__HRPWM__, pwmx)         \
        SET_BIT((__HRPWM__)->Common.CR0, BIT(((pwmx) % PWMx_NUMS) + HRPWM_COM_CR0_UDIS0_Pos))

/**
  * @brief  Common Master PWM Register Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_MstPWMRegUpd_En(__HRPWM__)              CLEAR_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_MUDIS_Msk)

/**
  * @brief  Common Master PWM Register Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_MstPWMRegUpd_Dis(__HRPWM__)             SET_BIT((__HRPWM__)->Common.CR0, HRPWM_COM_CR0_MUDIS_Msk)

/**
  * @brief  Common Multi PWM Register Update Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmxs Multi PWMx Mask, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_MultiPWMRegUpd_En(__HRPWM__, pwmxs)     CLEAR_BIT((__HRPWM__)->Common.CR0, ((pwmxs) & 0x1ffUL))

/**
  * @brief  Common Multi PWM Register Update Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmxs Multi PWMx Mask, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_MultiPWMRegUpd_Dis(__HRPWM__, pwmxs)    SET_BIT((__HRPWM__)->Common.CR0, ((pwmxs) & 0x1ffUL))


/**
  * @brief  Common ADC Trigger 3 Event Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  len ADC Trigger 3 Event Length @ref HRPWM_Comm_ADCTrigEvtLenETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig3EvtLen_Set(__HRPWM__, len)      \
        MODIFY_REG((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_TLEN3_Msk, (((len) & 0xfUL) << HRPWM_COM_CR1_TLEN3_Pos))

/**
  * @brief  Common ADC Trigger 2 Event Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  len ADC Trigger 2 Event Length @ref HRPWM_Comm_ADCTrigEvtLenETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig2EvtLen_Set(__HRPWM__, len)      \
        MODIFY_REG((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_TLEN2_Msk, (((len) & 0xfUL) << HRPWM_COM_CR1_TLEN2_Pos))

/**
  * @brief  Common ADC Trigger 1 Event Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  len ADC Trigger 1 Event Length @ref HRPWM_Comm_ADCTrigEvtLenETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig1EvtLen_Set(__HRPWM__, len)      \
        MODIFY_REG((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_TLEN1_Msk, (((len) & 0xfUL) << HRPWM_COM_CR1_TLEN1_Pos))

/**
  * @brief  Common ADC Trigger 0 Event Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  len ADC Trigger 0 Event Length @ref HRPWM_Comm_ADCTrigEvtLenETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig0EvtLen_Set(__HRPWM__, len)      \
        MODIFY_REG((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_TLEN0_Msk, (((len) & 0xfUL) << HRPWM_COM_CR1_TLEN0_Pos))

/**
  * @brief  Common ADC Trigger X Event Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  trigx ADC Trigger X Number @ref HRPWM_ADCTrigNumETypeDef (X=0~3)
  * @param  len ADC Trigger X Event Length @ref HRPWM_Comm_ADCTrigEvtLenETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrigX0To3EvtLen_Set(__HRPWM__, trigx, len)                           \
        MODIFY_REG((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_TLEN0_Msk << (((trigx) % 4) * 4), \
        (((len) & 0xfUL) << (HRPWM_COM_CR1_TLEN0_Pos + ((trigx) % 4) * 4)))

/**
  * @brief  Common PWM7 Output Swap Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM7OutputSwap_En(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP7_Msk)

/**
  * @brief  Common PWM7 Output Swap Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM7OutputSwap_Dis(__HRPWM__)           CLEAR_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP7_Msk)

/**
  * @brief  Common PWM6 Output Swap Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM6OutputSwap_En(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP6_Msk)

/**
  * @brief  Common PWM6 Output Swap Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM6OutputSwap_Dis(__HRPWM__)           CLEAR_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP6_Msk)

/**
  * @brief  Common PWM5 Output Swap Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM5OutputSwap_En(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP5_Msk)

/**
  * @brief  Common PWM5 Output Swap Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM5OutputSwap_Dis(__HRPWM__)           CLEAR_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP5_Msk)

/**
  * @brief  Common PWM4 Output Swap Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM4OutputSwap_En(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP4_Msk)

/**
  * @brief  Common PWM4 Output Swap Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM4OutputSwap_Dis(__HRPWM__)           CLEAR_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP4_Msk)

/**
  * @brief  Common PWM3 Output Swap Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM3OutputSwap_En(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP3_Msk)

/**
  * @brief  Common PWM3 Output Swap Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM3OutputSwap_Dis(__HRPWM__)           CLEAR_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP3_Msk)

/**
  * @brief  Common PWM2 Output Swap Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM2OutputSwap_En(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP2_Msk)

/**
  * @brief  Common PWM2 Output Swap Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM2OutputSwap_Dis(__HRPWM__)           CLEAR_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP2_Msk)

/**
  * @brief  Common PWM1 Output Swap Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM1OutputSwap_En(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP1_Msk)

/**
  * @brief  Common PWM1 Output Swap Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM1OutputSwap_Dis(__HRPWM__)           CLEAR_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP1_Msk)

/**
  * @brief  Common PWM0 Output Swap Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM0OutputSwap_En(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP0_Msk)

/**
  * @brief  Common PWM0 Output Swap Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM0OutputSwap_Dis(__HRPWM__)           CLEAR_BIT((__HRPWM__)->Common.CR1, HRPWM_COM_CR1_SWP0_Msk)

/**
  * @brief  Common PWMx Output Swap Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_PWMxOutputSwap_En(__HRPWM__, pwmx)      \
        SET_BIT((__HRPWM__)->Common.CR1, BIT(((pwmx) % PWMx_NUMS) + HRPWM_COM_CR1_SWP0_Pos))

/**
  * @brief  Common PWMx Output Swap Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_PWMxOutputSwap_Dis(__HRPWM__, pwmx)     \
        CLEAR_BIT((__HRPWM__)->Common.CR1, BIT(((pwmx) % PWMx_NUMS) + HRPWM_COM_CR1_SWP0_Pos))

/**
  * @brief  Common Multi PWMx Output Swap Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmxs Multi PWMx Mask, not include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_MultiPWMxOutputSwap_En(__HRPWM__, pwmxs)    SET_BIT((__HRPWM__)->Common.CR1, ((pwmxs) & 0x1ffUL) >> 1)

/**
  * @brief  Common Multi PWMx Output Swap Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmxs Multi PWMx Mask, not include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_MultiPWMxOutputSwap_Dis(__HRPWM__, pwmxs)   CLEAR_BIT((__HRPWM__)->Common.CR1, ((pwmxs) & 0x1ffUL) >> 1)


/**
  * @brief  Common PWM7 Software Reset Counter Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM7SwRstCntr_Set(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_RST7_Msk)

/**
  * @brief  Common PWM6 Software Reset Counter Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM6SwRstCntr_Set(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_RST6_Msk)

/**
  * @brief  Common PWM5 Software Reset Counter Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM5SwRstCntr_Set(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_RST5_Msk)

/**
  * @brief  Common PWM4 Software Reset Counter Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM4SwRstCntr_Set(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_RST4_Msk)

/**
  * @brief  Common PWM3 Software Reset Counter Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM3SwRstCntr_Set(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_RST3_Msk)

/**
  * @brief  Common PWM2 Software Reset Counter Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM2SwRstCntr_Set(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_RST2_Msk)

/**
  * @brief  Common PWM1 Software Reset Counter Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM1SwRstCntr_Set(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_RST1_Msk)

/**
  * @brief  Common PWM0 Software Reset Counter Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM0SwRstCntr_Set(__HRPWM__)            SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_RST0_Msk)

/**
  * @brief  Common PWMx Software Reset Counter Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_PWMxSwRstCntr_Set(__HRPWM__, pwmx)      \
        SET_BIT((__HRPWM__)->Common.CR2, BIT(((pwmx) % PWMx_NUMS) + HRPWM_COM_CR2_RST0_Pos))

/**
  * @brief  Common PWMx Software Reset Counter Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 Reset has completed
  * @retval 1 Reset hasn't completed
  */
#define __LL_HRPWM_Comm_PWMxSwRstCntr_Get(__HRPWM__, pwmx)                                            \
        READ_BIT_SHIFT((__HRPWM__)->Common.CR2, BIT(((pwmx) % PWMx_NUMS) + HRPWM_COM_CR2_RST0_Pos), \
        (((pwmx) % PWMx_NUMS) + HRPWM_COM_CR2_RST0_Pos))

/**
  * @brief  Common Master PWM Software Reset Counter Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_MstPWMSwRstCntr_Set(__HRPWM__)          SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_MRST_Msk)

/**
  * @brief  Common Master PWM Software Reset Counter Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Reset has completed
  * @retval 1 Reset hasn't completed
  */
#define __LL_HRPWM_Comm_MstPWMSwRstCntr_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_MRST_Msk, HRPWM_COM_CR2_MRST_Pos)

/**
  * @brief  Common Multi PWMx Software Reset Counter Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmxs Multi PWMx Mask, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_MultiPWMxSwRstCntr_Set(__HRPWM__, pwmxs)    \
        SET_BIT((__HRPWM__)->Common.CR2, ((pwmxs) & 0x1ffUL) << HRPWM_COM_CR2_MRST_Pos)

/**
  * @brief  Common Multi PWMx Software Reset Counter Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmxs Multi PWMx Mask, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @retval 0 Reset has completed
  * @retval 1 Reset hasn't completed
  */
#define __LL_HRPWM_Comm_MultiPWMxSwRstCntr_Get(__HRPWM__, pwmxs)    \
        (!!READ_BIT_SHIFT((__HRPWM__)->Common.CR2, ((pwmxs) & 0x1ffUL) << HRPWM_COM_CR2_MRST_Pos, HRPWM_COM_CR2_MRST_Pos))

/**
  * @brief  Common PWM7 Software Update Register Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM7SwUpdReg_Set(__HRPWM__)             SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU7_Msk)

/**
  * @brief  Common PWM7 Software Update Register Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
#define __LL_HRPWM_Comm_PWM7SwUpdReg_Get(__HRPWM__)             \
        READ_BIT_SHIFT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU7_Msk, HRPWM_COM_CR2_SWU7_Pos)

/**
  * @brief  Common PWM6 Software Update Register Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM6SwUpdReg_Set(__HRPWM__)             SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU6_Msk)

/**
  * @brief  Common PWM6 Software Update Register Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
#define __LL_HRPWM_Comm_PWM6SwUpdReg_Get(__HRPWM__)             \
        READ_BIT_SHIFT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU6_Msk, HRPWM_COM_CR2_SWU6_Pos)

/**
  * @brief  Common PWM5 Software Update Register Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM5SwUpdReg_Set(__HRPWM__)             SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU5_Msk)

/**
  * @brief  Common PWM5 Software Update Register Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
#define __LL_HRPWM_Comm_PWM5SwUpdReg_Get(__HRPWM__)             \
        READ_BIT_SHIFT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU5_Msk, HRPWM_COM_CR2_SWU5_Pos)

/**
  * @brief  Common PWM4 Software Update Register Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM4SwUpdReg_Set(__HRPWM__)             SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU4_Msk)

/**
  * @brief  Common PWM4 Software Update Register Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
#define __LL_HRPWM_Comm_PWM4SwUpdReg_Get(__HRPWM__)             \
        READ_BIT_SHIFT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU4_Msk, HRPWM_COM_CR2_SWU4_Pos)

/**
  * @brief  Common PWM3 Software Update Register Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM3SwUpdReg_Set(__HRPWM__)             SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU3_Msk)

/**
  * @brief  Common PWM3 Software Update Register Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
#define __LL_HRPWM_Comm_PWM3SwUpdReg_Get(__HRPWM__)             \
        READ_BIT_SHIFT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU3_Msk, HRPWM_COM_CR2_SWU3_Pos)

/**
  * @brief  Common PWM2 Software Update Register Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM2SwUpdReg_Set(__HRPWM__)             SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU2_Msk)

/**
  * @brief  Common PWM2 Software Update Register Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
#define __LL_HRPWM_Comm_PWM2SwUpdReg_Get(__HRPWM__)             \
        READ_BIT_SHIFT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU2_Msk, HRPWM_COM_CR2_SWU2_Pos)

/**
  * @brief  Common PWM1 Software Update Register Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM1SwUpdReg_Set(__HRPWM__)             SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU1_Msk)

/**
  * @brief  Common PWM1 Software Update Register Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
#define __LL_HRPWM_Comm_PWM1SwUpdReg_Get(__HRPWM__)             \
        READ_BIT_SHIFT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU1_Msk, HRPWM_COM_CR2_SWU1_Pos)

/**
  * @brief  Common PWM0 Software Update Register Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM0SwUpdReg_Set(__HRPWM__)             SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU0_Msk)

/**
  * @brief  Common PWM0 Software Update Register Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
#define __LL_HRPWM_Comm_PWM0SwUpdReg_Get(__HRPWM__)             \
        READ_BIT_SHIFT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_SWU0_Msk, HRPWM_COM_CR2_SWU0_Pos)

/**
  * @brief  Common PWMx Software Update Register Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_PWMxSwUpdReg_Set(__HRPWM__, pwmx)       \
        SET_BIT((__HRPWM__)->Common.CR2, BIT(((pwmx) % PWMx_NUMS) + HRPWM_COM_CR2_SWU0_Pos))

/**
  * @brief  Common PWMx Software Update Register Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
#define __LL_HRPWM_Comm_PWMxSwUpdReg_Get(__HRPWM__, pwmx)       READ_BIT_SHIFT((__HRPWM__)->Common.CR2, \
        BIT(((pwmx) % PWMx_NUMS) + HRPWM_COM_CR2_SWU0_Pos), (((pwmx) % PWMx_NUMS) + HRPWM_COM_CR2_SWU0_Pos))

/**
  * @brief  Common Master PWM Software Update Register Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_MstPWMSwUpdReg_Set(__HRPWM__)           SET_BIT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_MSWU_Msk)

/**
  * @brief  Common Master PWM Software Update Register Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
#define __LL_HRPWM_Comm_MstPWMSwUpdReg_Get(__HRPWM__)           \
        READ_BIT_SHIFT((__HRPWM__)->Common.CR2, HRPWM_COM_CR2_MSWU_Msk, HRPWM_COM_CR2_MSWU_Pos)

/**
  * @brief  Common Multi PWMx Software Update Register Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmxs Multi PWMx Mask, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_MultiPWMxSwUpdReg_Set(__HRPWM__, pwmxs) SET_BIT((__HRPWM__)->Common.CR2, ((pwmxs) & 0x1ffUL))

/**
  * @brief  Common Multi PWMx Software Update Register Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmxs Multi PWMx Mask, include Master PWM, combination of HRPWM_PWMMaskETypeDef
  * @retval 0 Update has completed
  * @retval 1 Update hasn't completed
  */
#define __LL_HRPWM_Comm_MultiPWMxSwUpdReg_Get(__HRPWM__, pwmxs) (!!READ_BIT((__HRPWM__)->Common.CR2, ((pwmxs) & 0x1ffUL)))

/**
  * @brief  Common Software Update Register Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  val Software Update Register Value
  * @return None
  */
#define __LL_HRPWM_PWMSwUpdReg_Set(__HRPWM__, val)              MODIFY_REG((__HRPWM__)->Common.CR2, 0x1ff, ((val) & 0x1ff))


/**
  * @brief  Judge is Common Burst Mode Period Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Common Burst Mode Period Interrupt Pending
  * @retval 1 is Common Burst Mode Period Interrupt Pending
  */
#define __LL_HRPWM_Comm_IsBurstModePrdIntPnd(__HRPWM__)         \
        READ_BIT_SHIFT((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_BMPER_Msk, HRPWM_COM_ISR_BMPER_Pos)

/**
  * @brief  Common Burst Mode Period Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModePrdIntPnd_Clr(__HRPWM__)       WRITE_REG((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_BMPER_Msk)

/**
  * @brief  Judge is Common Fault 7 Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 7 Interrupt Pending
  * @retval 1 is Common Fault 7 Interrupt Pending
  */
#define __LL_HRPWM_Comm_IsFlt7IntPnd(__HRPWM__)                 \
        READ_BIT_SHIFT((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT7_Msk, HRPWM_COM_ISR_FLT7_Pos)

/**
  * @brief  Common Fault 7 Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt7IntPnd_Clr(__HRPWM__)               WRITE_REG((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT7_Msk)

/**
  * @brief  Judge is Common Fault 6 Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 6 Interrupt Pending
  * @retval 1 is Common Fault 6 Interrupt Pending
  */
#define __LL_HRPWM_Comm_IsFlt6IntPnd(__HRPWM__)                 \
        READ_BIT_SHIFT((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT6_Msk, HRPWM_COM_ISR_FLT6_Pos)

/**
  * @brief  Common Fault 6 Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt6IntPnd_Clr(__HRPWM__)               WRITE_REG((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT6_Msk)

/**
  * @brief  Judge is Common Fault 5 Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 5 Interrupt Pending
  * @retval 1 is Common Fault 5 Interrupt Pending
  */
#define __LL_HRPWM_Comm_IsFlt5IntPnd(__HRPWM__)                 \
        READ_BIT_SHIFT((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT5_Msk, HRPWM_COM_ISR_FLT5_Pos)

/**
  * @brief  Common Fault 5 Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt5IntPnd_Clr(__HRPWM__)               WRITE_REG((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT5_Msk)

/**
  * @brief  Judge is Common Fault 4 Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 4 Interrupt Pending
  * @retval 1 is Common Fault 4 Interrupt Pending
  */
#define __LL_HRPWM_Comm_IsFlt4IntPnd(__HRPWM__)                 \
        READ_BIT_SHIFT((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT4_Msk, HRPWM_COM_ISR_FLT4_Pos)

/**
  * @brief  Common Fault 4 Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt4IntPnd_Clr(__HRPWM__)               WRITE_REG((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT4_Msk)

/**
  * @brief  Judge is Common Fault 3 Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 3 Interrupt Pending
  * @retval 1 is Common Fault 3 Interrupt Pending
  */
#define __LL_HRPWM_Comm_IsFlt3IntPnd(__HRPWM__)                 \
        READ_BIT_SHIFT((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT3_Msk, HRPWM_COM_ISR_FLT3_Pos)

/**
  * @brief  Common Fault 3 Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt3IntPnd_Clr(__HRPWM__)               WRITE_REG((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT3_Msk)

/**
  * @brief  Judge is Common Fault 2 Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 2 Interrupt Pending
  * @retval 1 is Common Fault 2 Interrupt Pending
  */
#define __LL_HRPWM_Comm_IsFlt2IntPnd(__HRPWM__)                 \
        READ_BIT_SHIFT((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT2_Msk, HRPWM_COM_ISR_FLT2_Pos)

/**
  * @brief  Common Fault 2 Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt2IntPnd_Clr(__HRPWM__)               WRITE_REG((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT2_Msk)

/**
  * @brief  Judge is Common Fault 1 Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 1 Interrupt Pending
  * @retval 1 is Common Fault 1 Interrupt Pending
  */
#define __LL_HRPWM_Comm_IsFlt1IntPnd(__HRPWM__)                 \
        READ_BIT_SHIFT((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT1_Msk, HRPWM_COM_ISR_FLT1_Pos)

/**
  * @brief  Common Fault 1 Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt1IntPnd_Clr(__HRPWM__)               WRITE_REG((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT1_Msk)

/**
  * @brief  Judge is Common Fault 0 Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Common Fault 0 Interrupt Pending
  * @retval 1 is Common Fault 0 Interrupt Pending
  */
#define __LL_HRPWM_Comm_IsFlt0IntPnd(__HRPWM__)                 \
        READ_BIT_SHIFT((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT0_Msk, HRPWM_COM_ISR_FLT0_Pos)

/**
  * @brief  Common Fault 0 Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt0IntPnd_Clr(__HRPWM__)               WRITE_REG((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_FLT0_Msk)

/**
  * @brief  Judge is Common Fault X Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx PWMx Fault Number @ref HRPWM_FltNumETypeDef
  * @retval 0 isn't Common Fault X Interrupt Pending
  * @retval 1 is Common Fault X Interrupt Pending
  */
#define __LL_HRPWM_Comm_IsFltXIntPnd(__HRPWM__, fltx)           READ_BIT_SHIFT((__HRPWM__)->Common.ISR,\
        BIT(((fltx) % HRPWM_FLT_NUMS) + HRPWM_COM_ISR_FLT0_Pos), (((fltx) % HRPWM_FLT_NUMS) + HRPWM_COM_ISR_FLT0_Pos))

/**
  * @brief  Common Fault X Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx PWMx Fault Number @ref HRPWM_FltNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_FltXIntPnd_Clr(__HRPWM__, fltx)         \
        WRITE_REG((__HRPWM__)->Common.ISR, BIT(((fltx) % HRPWM_FLT_NUMS) + HRPWM_COM_ISR_FLT0_Pos))

/**
  * @brief  Judge is Common System Fault Interrupt Pending or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 isn't Common System Fault Interrupt Pending
  * @retval 1 is Common System Fault Interrupt Pending
  */
#define __LL_HRPWM_Comm_IsSysFltIntPnd(__HRPWM__)               \
        READ_BIT_SHIFT((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_SYSFLT_Msk, HRPWM_COM_ISR_SYSFLT_Pos)

/**
  * @brief  Common System Fault Interrupt Pending Clear
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_SysFltIntPnd_Clr(__HRPWM__)             WRITE_REG((__HRPWM__)->Common.ISR, HRPWM_COM_ISR_SYSFLT_Msk)

/**
  * @brief  HRPWM Common All Interrupt Pending Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return HRPWM Common All Interrupt Pending
  */
#define __LL_HRPWM_Comm_AllIntPnd_Get(__HRPWM__)                READ_REG((__HRPWM__)->Common.ISR)


/**
  * @brief  Common Burst Mode Period Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModePrd_INT_En(__HRPWM__)          SET_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_BMPERIE_Msk)

/**
  * @brief  Common Burst Mode Period Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModePrd_INT_Dis(__HRPWM__)         CLEAR_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_BMPERIE_Msk)

/**
  * @brief  Common Fault 7 Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt7_INT_En(__HRPWM__)                  SET_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT7IE_Msk)

/**
  * @brief  Common Fault 7 Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt7_INT_Dis(__HRPWM__)                 CLEAR_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT7IE_Msk)

/**
  * @brief  Common Fault 6 Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt6_INT_En(__HRPWM__)                  SET_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT6IE_Msk)

/**
  * @brief  Common Fault 6 Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt6_INT_Dis(__HRPWM__)                 CLEAR_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT6IE_Msk)

/**
  * @brief  Common Fault 5 Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt5_INT_En(__HRPWM__)                  SET_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT5IE_Msk)

/**
  * @brief  Common Fault 5 Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt5_INT_Dis(__HRPWM__)                 CLEAR_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT5IE_Msk)

/**
  * @brief  Common Fault 4 Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt4_INT_En(__HRPWM__)                  SET_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT4IE_Msk)

/**
  * @brief  Common Fault 4 Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt4_INT_Dis(__HRPWM__)                 CLEAR_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT4IE_Msk)

/**
  * @brief  Common Fault 3 Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt3_INT_En(__HRPWM__)                  SET_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT3IE_Msk)

/**
  * @brief  Common Fault 3 Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt3_INT_Dis(__HRPWM__)                 CLEAR_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT3IE_Msk)

/**
  * @brief  Common Fault 2 Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt2_INT_En(__HRPWM__)                  SET_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT2IE_Msk)

/**
  * @brief  Common Fault 2 Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt2_INT_Dis(__HRPWM__)                 CLEAR_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT2IE_Msk)

/**
  * @brief  Common Fault 1 Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt1_INT_En(__HRPWM__)                  SET_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT1IE_Msk)

/**
  * @brief  Common Fault 1 Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt1_INT_Dis(__HRPWM__)                 CLEAR_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT1IE_Msk)

/**
  * @brief  Common Fault 0 Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt0_INT_En(__HRPWM__)                  SET_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT0IE_Msk)

/**
  * @brief  Common Fault 0 Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_Flt0_INT_Dis(__HRPWM__)                 CLEAR_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_FLT0IE_Msk)

/**
  * @brief  Common Fault X Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx PWMx Fault Number @ref HRPWM_FltNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_FltX_INT_En(__HRPWM__, fltx)            \
        SET_BIT((__HRPWM__)->Common.IER, BIT(((fltx) % HRPWM_FLT_NUMS) + HRPWM_COM_IER_FLT0IE_Pos))

/**
  * @brief  Common Fault X Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx PWMx Fault Number @ref HRPWM_FltNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_FltX_INT_Dis(__HRPWM__, fltx)           \
        CLEAR_BIT((__HRPWM__)->Common.IER, BIT(((fltx) % HRPWM_FLT_NUMS) + HRPWM_COM_IER_FLT0IE_Pos))

/**
  * @brief  Common System Fault Interrupt Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_SysFlt_INT_En(__HRPWM__)                SET_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_SYSFLTIE_Msk)

/**
  * @brief  Common System Fault Interrupt Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_SysFlt_INT_Dis(__HRPWM__)               CLEAR_BIT((__HRPWM__)->Common.IER, HRPWM_COM_IER_SYSFLTIE_Msk)

/**
  * @brief  HRPWM Common All Interrupt Enable Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return HRPWM Common All Interrupt Enable Status
  */
#define __LL_HRPWM_Comm_AllIntEn_Get(__HRPWM__)                 READ_REG((__HRPWM__)->Common.IER)


/**
  * @brief  Common PWM7 OutB Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM7OutB_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN7B_Msk)

/**
  * @brief  Judge is Common PWM7 OutB Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM7 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM7 OutB is Running
  */
#define __LL_HRPWM_Comm_IsPWM7OutBRunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN7B_Msk, HRPWM_COM_OENR_OEN7B_Pos)

/**
  * @brief  Common PWM7 OutA Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM7OutA_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN7A_Msk)

/**
  * @brief  Judge is Common PWM7 OutA Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM7 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM7 OutA is Running
  */
#define __LL_HRPWM_Comm_IsPWM7OutARunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN7A_Msk, HRPWM_COM_OENR_OEN7A_Pos)

/**
  * @brief  Common PWM6 OutB Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM6OutB_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN6B_Msk)

/**
  * @brief  Judge is Common PWM6 OutB Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM6 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM6 OutB is Running
  */
#define __LL_HRPWM_Comm_IsPWM6OutBRunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN6B_Msk, HRPWM_COM_OENR_OEN6B_Pos)

/**
  * @brief  Common PWM6 OutA Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM6OutA_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN6A_Msk)

/**
  * @brief  Judge is Common PWM6 OutA Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM6 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM6 OutA is Running
  */
#define __LL_HRPWM_Comm_IsPWM6OutARunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN6A_Msk, HRPWM_COM_OENR_OEN6A_Pos)

/**
  * @brief  Common PWM5 OutB Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM5OutB_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN5B_Msk)

/**
  * @brief  Judge is Common PWM5 OutB Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM5 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM5 OutB is Running
  */
#define __LL_HRPWM_Comm_IsPWM5OutBRunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN5B_Msk, HRPWM_COM_OENR_OEN5B_Pos)

/**
  * @brief  Common PWM5 OutA Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM5OutA_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN5A_Msk)

/**
  * @brief  Judge is Common PWM5 OutA Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM5 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM5 OutA is Running
  */
#define __LL_HRPWM_Comm_IsPWM5OutARunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN5A_Msk, HRPWM_COM_OENR_OEN5A_Pos)

/**
  * @brief  Common PWM4 OutB Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM4OutB_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN4B_Msk)

/**
  * @brief  Judge is Common PWM4 OutB Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM4 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM4 OutB is Running
  */
#define __LL_HRPWM_Comm_IsPWM4OutBRunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN4B_Msk, HRPWM_COM_OENR_OEN4B_Pos)

/**
  * @brief  Common PWM4 OutA Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM4OutA_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN4A_Msk)

/**
  * @brief  Judge is Common PWM4 OutA Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM4 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM4 OutA is Running
  */
#define __LL_HRPWM_Comm_IsPWM4OutARunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN4A_Msk, HRPWM_COM_OENR_OEN4A_Pos)

/**
  * @brief  Common PWM3 OutB Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM3OutB_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN3B_Msk)

/**
  * @brief  Judge is Common PWM3 OutB Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM3 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM3 OutB is Running
  */
#define __LL_HRPWM_Comm_IsPWM3OutBRunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN3B_Msk, HRPWM_COM_OENR_OEN3B_Pos)

/**
  * @brief  Common PWM3 OutA Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM3OutA_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN3A_Msk)

/**
  * @brief  Judge is Common PWM3 OutA Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM3 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM3 OutA is Running
  */
#define __LL_HRPWM_Comm_IsPWM3OutARunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN3A_Msk, HRPWM_COM_OENR_OEN3A_Pos)

/**
  * @brief  Common PWM2 OutB Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM2OutB_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN2B_Msk)

/**
  * @brief  Judge is Common PWM2 OutB Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM2 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM2 OutB is Running
  */
#define __LL_HRPWM_Comm_IsPWM2OutBRunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN2B_Msk, HRPWM_COM_OENR_OEN2B_Pos)

/**
  * @brief  Common PWM2 OutA Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM2OutA_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN2A_Msk)

/**
  * @brief  Judge is Common PWM2 OutA Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM2 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM2 OutA is Running
  */
#define __LL_HRPWM_Comm_IsPWM2OutARunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN2A_Msk, HRPWM_COM_OENR_OEN2A_Pos)

/**
  * @brief  Common PWM1 OutB Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM1OutB_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN1B_Msk)

/**
  * @brief  Judge is Common PWM1 OutB Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM1 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM1 OutB is Running
  */
#define __LL_HRPWM_Comm_IsPWM1OutBRunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN1B_Msk, HRPWM_COM_OENR_OEN1B_Pos)

/**
  * @brief  Common PWM1 OutA Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM1OutA_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN1A_Msk)

/**
  * @brief  Judge is Common PWM1 OutA Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM1 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM1 OutA is Running
  */
#define __LL_HRPWM_Comm_IsPWM1OutARunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN1A_Msk, HRPWM_COM_OENR_OEN1A_Pos)

/**
  * @brief  Common PWM0 OutB Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM0OutB_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN0B_Msk)

/**
  * @brief  Judge is Common PWM0 OutB Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM0 OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM0 OutB is Running
  */
#define __LL_HRPWM_Comm_IsPWM0OutBRunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN0B_Msk, HRPWM_COM_OENR_OEN0B_Pos)

/**
  * @brief  Common PWM0 OutA Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM0OutA_Start(__HRPWM__)               SET_BIT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN0A_Msk)

/**
  * @brief  Judge is Common PWM0 OutA Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM0 OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWM0 OutA is Running
  */
#define __LL_HRPWM_Comm_IsPWM0OutARunning(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.OENR, HRPWM_COM_OENR_OEN0A_Msk, HRPWM_COM_OENR_OEN0A_Pos)

/**
  * @brief  Common PWMx OutB Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_PWMxOutB_Start(__HRPWM__, pwmx)         \
        SET_BIT((__HRPWM__)->Common.OENR, BIT(((pwmx) % PWMx_NUMS) * 2 + HRPWM_COM_OENR_OEN0B_Pos))

/**
  * @brief  Judge is Common PWMx OutB Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 Common PWMx OutB isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWMx OutB is Running
  */
#define __LL_HRPWM_Comm_IsPWMxOutBRunning(__HRPWM__, pwmx)      READ_BIT_SHIFT((__HRPWM__)->Common.OENR,\
        BIT(((pwmx) % PWMx_NUMS) * 2 + HRPWM_COM_OENR_OEN0B_Pos), (((pwmx) % PWMx_NUMS) * 2 + HRPWM_COM_OENR_OEN0B_Pos))

/**
  * @brief  Common PWMx OutA Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_PWMxOutA_Start(__HRPWM__, pwmx)         \
        SET_BIT((__HRPWM__)->Common.OENR, BIT(((pwmx) % PWMx_NUMS) * 2 + HRPWM_COM_OENR_OEN0A_Pos))

/**
  * @brief  Judge is Common PWMx OutA Running or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 Common PWMx OutA isn't Running (Maybe Fault or Idle)
  * @retval 1 Common PWMx OutA is Running
  */
#define __LL_HRPWM_Comm_IsPWMxOutARunning(__HRPWM__, pwmx)      READ_BIT_SHIFT((__HRPWM__)->Common.OENR,\
        BIT(((pwmx) % PWMx_NUMS) * 2 + HRPWM_COM_OENR_OEN0A_Pos), (((pwmx) % PWMx_NUMS) * 2 + HRPWM_COM_OENR_OEN0A_Pos))

/**
  * @brief  Common Multi PWMx Output Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  mask Multi PWMx Output Start Mask, combination of HRPWM_PWMOutputMaskETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_MultiPWMxOutput_Start(__HRPWM__, mask)  SET_BIT((__HRPWM__)->Common.OENR, ((mask) & 0xffffUL))

/**
  * @brief  Common PWM Output Enable Register Write
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  val Common PWM Output Enable Register value
  * @return None
  */
#define __LL_HRPWM_Comm_PWMOutEnReg_Write(__HRPWM__, val)       WRITE_REG((__HRPWM__)->Common.OENR, val)


/**
  * @brief  Common PWM7 OutB Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM7OutB_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS7B_Msk)

/**
  * @brief  Common PWM7 OutB Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM7 OutB is Idle
  * @retval 1 Common PWM7 OutB is Fault
  */
#define __LL_HRPWM_Comm_PWM7OutBStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS7B_Msk, HRPWM_COM_ODISR_ODIS7B_Pos)

/**
  * @brief  Common PWM7 OutA Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM7OutA_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS7A_Msk)

/**
  * @brief  Common PWM7 OutA Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM7 OutA is Idle
  * @retval 1 Common PWM7 OutA is Fault
  */
#define __LL_HRPWM_Comm_PWM7OutAStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS7A_Msk, HRPWM_COM_ODISR_ODIS7A_Pos)

/**
  * @brief  Common PWM6 OutB Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM6OutB_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS6B_Msk)

/**
  * @brief  Common PWM6 OutB Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM6 OutB is Idle
  * @retval 1 Common PWM6 OutB is Fault
  */
#define __LL_HRPWM_Comm_PWM6OutBStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS6B_Msk, HRPWM_COM_ODISR_ODIS6B_Pos)

/**
  * @brief  Common PWM6 OutA Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM6OutA_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS6A_Msk)

/**
  * @brief  Common PWM6 OutA Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM6 OutA is Idle
  * @retval 1 Common PWM6 OutA is Fault
  */
#define __LL_HRPWM_Comm_PWM6OutAStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS6A_Msk, HRPWM_COM_ODISR_ODIS6A_Pos)

/**
  * @brief  Common PWM5 OutB Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM5OutB_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS5B_Msk)

/**
  * @brief  Common PWM5 OutB Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM5 OutB is Idle
  * @retval 1 Common PWM5 OutB is Fault
  */
#define __LL_HRPWM_Comm_PWM5OutBStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS5B_Msk, HRPWM_COM_ODISR_ODIS5B_Pos)

/**
  * @brief  Common PWM5 OutA Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM5OutA_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS5A_Msk)

/**
  * @brief  Common PWM5 OutA Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM5 OutA is Idle
  * @retval 1 Common PWM5 OutA is Fault
  */
#define __LL_HRPWM_Comm_PWM5OutAStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS5A_Msk, HRPWM_COM_ODISR_ODIS5A_Pos)

/**
  * @brief  Common PWM4 OutB Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM4OutB_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS4B_Msk)

/**
  * @brief  Common PWM4 OutB Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM4 OutB is Idle
  * @retval 1 Common PWM4 OutB is Fault
  */
#define __LL_HRPWM_Comm_PWM4OutBStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS4B_Msk, HRPWM_COM_ODISR_ODIS4B_Pos)

/**
  * @brief  Common PWM4 OutA Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM4OutA_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS4A_Msk)

/**
  * @brief  Common PWM4 OutA Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM4 OutA is Idle
  * @retval 1 Common PWM4 OutA is Fault
  */
#define __LL_HRPWM_Comm_PWM4OutAStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS4A_Msk, HRPWM_COM_ODISR_ODIS4A_Pos)

/**
  * @brief  Common PWM3 OutB Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM3OutB_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS3B_Msk)

/**
  * @brief  Common PWM3 OutB Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM3 OutB is Idle
  * @retval 1 Common PWM3 OutB is Fault
  */
#define __LL_HRPWM_Comm_PWM3OutBStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS3B_Msk, HRPWM_COM_ODISR_ODIS3B_Pos)

/**
  * @brief  Common PWM3 OutA Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM3OutA_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS3A_Msk)

/**
  * @brief  Common PWM3 OutA Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM3 OutA is Idle
  * @retval 1 Common PWM3 OutA is Fault
  */
#define __LL_HRPWM_Comm_PWM3OutAStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS3A_Msk, HRPWM_COM_ODISR_ODIS3A_Pos)

/**
  * @brief  Common PWM2 OutB Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM2OutB_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS2B_Msk)

/**
  * @brief  Common PWM2 OutB Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM2 OutB is Idle
  * @retval 1 Common PWM2 OutB is Fault
  */
#define __LL_HRPWM_Comm_PWM2OutBStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS2B_Msk, HRPWM_COM_ODISR_ODIS2B_Pos)

/**
  * @brief  Common PWM2 OutA Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM2OutA_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS2A_Msk)

/**
  * @brief  Common PWM2 OutA Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM2 OutA is Idle
  * @retval 1 Common PWM2 OutA is Fault
  */
#define __LL_HRPWM_Comm_PWM2OutAStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS2A_Msk, HRPWM_COM_ODISR_ODIS2A_Pos)

/**
  * @brief  Common PWM1 OutB Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM1OutB_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS1B_Msk)

/**
  * @brief  Common PWM1 OutB Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM1 OutB is Idle
  * @retval 1 Common PWM1 OutB is Fault
  */
#define __LL_HRPWM_Comm_PWM1OutBStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS1B_Msk, HRPWM_COM_ODISR_ODIS1B_Pos)

/**
  * @brief  Common PWM1 OutA Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM1OutA_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS1A_Msk)

/**
  * @brief  Common PWM1 OutA Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM1 OutA is Idle
  * @retval 1 Common PWM1 OutA is Fault
  */
#define __LL_HRPWM_Comm_PWM1OutAStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS1A_Msk, HRPWM_COM_ODISR_ODIS1A_Pos)

/**
  * @brief  Common PWM0 OutB Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM0OutB_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS0B_Msk)

/**
  * @brief  Common PWM0 OutB Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM0 OutB is Idle
  * @retval 1 Common PWM0 OutB is Fault
  */
#define __LL_HRPWM_Comm_PWM0OutBStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS0B_Msk, HRPWM_COM_ODISR_ODIS0B_Pos)

/**
  * @brief  Common PWM0 OutA Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM0OutA_Stop(__HRPWM__)                SET_BIT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS0A_Msk)

/**
  * @brief  Common PWM0 OutA Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common PWM0 OutA is Idle
  * @retval 1 Common PWM0 OutA is Fault
  */
#define __LL_HRPWM_Comm_PWM0OutAStopSta_Get(__HRPWM__)          \
        READ_BIT_SHIFT((__HRPWM__)->Common.ODISR, HRPWM_COM_ODISR_ODIS0A_Msk, HRPWM_COM_ODISR_ODIS0A_Pos)

/**
  * @brief  Common PWMx OutB Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_PWMxOutB_Stop(__HRPWM__, pwmx)          \
        SET_BIT((__HRPWM__)->Common.ODISR, BIT(((pwmx) % PWMx_NUMS) * 2 + HRPWM_COM_ODISR_ODIS0B_Pos))

/**
  * @brief  Common PWMx OutB Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 Common PWMx OutB is Idle
  * @retval 1 Common PWMx OutB is Fault
  */
#define __LL_HRPWM_Comm_PWMxOutBStopSta_Get(__HRPWM__, pwmx)    READ_BIT_SHIFT((__HRPWM__)->Common.ODISR,\
        BIT(((pwmx) % PWMx_NUMS) * 2 + HRPWM_COM_ODISR_ODIS0B_Pos), (((pwmx) % PWMx_NUMS) * 2 + HRPWM_COM_ODISR_ODIS0B_Pos))

/**
  * @brief  Common PWMx OutA Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_PWMxOutA_Stop(__HRPWM__, pwmx)          \
        SET_BIT((__HRPWM__)->Common.ODISR, BIT(((pwmx) % PWMx_NUMS) * 2 + HRPWM_COM_ODISR_ODIS0A_Pos))

/**
  * @brief  Common PWMx OutA Stop Status Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @retval 0 Common PWMx OutA is Idle
  * @retval 1 Common PWMx OutA is Fault
  */
#define __LL_HRPWM_Comm_PWMxOutAStopSta_Get(__HRPWM__, pwmx)    READ_BIT_SHIFT((__HRPWM__)->Common.ODISR,\
        BIT(((pwmx) % PWMx_NUMS) * 2 + HRPWM_COM_ODISR_ODIS0A_Pos), (((pwmx) % PWMx_NUMS) * 2 + HRPWM_COM_ODISR_ODIS0A_Pos))

/**
  * @brief  Common Multi PWMx Output Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  mask Multi PWMx Output Stop Mask, combination of HRPWM_PWMOutputMaskETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_MultiPWMxOutput_Stop(__HRPWM__, mask)   SET_BIT((__HRPWM__)->Common.ODISR, ((mask) & 0xffffUL))

/**
  * @brief  Common PWM Output Disable Register Write
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  val Common PWM Output Disable Register value
  * @return None
  */
#define __LL_HRPWM_Comm_PWMOutDisReg_Write(__HRPWM__, val)      WRITE_REG((__HRPWM__)->Common.ODISR, val)


/**
  * @brief  Common External Event X Fast Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt_x External Event Number @ref HRPWM_ExtEvtNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ExtEvtXFastMode_En(__HRPWM__, evt_x)                                                      \
        SET_BIT(__LL_HRPWM_REG_OFFSET((__HRPWM__)->Common.EECR0, (evt_x) / 5 % ((HRPWM_EXT_EVT_NUMS + 4) / 5)), \
        BIT(((evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0FAST_Pos))

/**
  * @brief  Common External Event X Fast Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt_x External Event Number @ref HRPWM_ExtEvtNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ExtEvtXFastMode_Dis(__HRPWM__, evt_x)                                                       \
        CLEAR_BIT(__LL_HRPWM_REG_OFFSET((__HRPWM__)->Common.EECR0, (evt_x) / 5 % ((HRPWM_EXT_EVT_NUMS + 4) / 5)), \
        BIT(((evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0FAST_Pos))

/**
  * @brief  Common External Event X Input Active Edge Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt_x External Event Number @ref HRPWM_ExtEvtNumETypeDef
  * @param  edge External Event X Input Active Edge
  * @return None
  */
#define __LL_HRPWM_Comm_ExtEvtXInputActEdge_Set(__HRPWM__, evt_x, edge)                                                \
        MODIFY_REG(__LL_HRPWM_REG_OFFSET((__HRPWM__)->Common.EECR0, (evt_x) / 5 % ((HRPWM_EXT_EVT_NUMS + 4) / 5)),  \
        0x3UL << (((evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SNS_Pos), (((edge) & 0x3UL) << (((evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SNS_Pos)))

/**
  * @brief  Common External Event X Input Polarity Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt_x External Event Number @ref HRPWM_ExtEvtNumETypeDef
  * @param  pol External Event X Input Polarity
  * @return None
  */
#define __LL_HRPWM_Comm_ExtEvtXInputPol_Set(__HRPWM__, evt_x, pol)                                                     \
        MODIFY_REG(__LL_HRPWM_REG_OFFSET((__HRPWM__)->Common.EECR0, (evt_x) / 5 % ((HRPWM_EXT_EVT_NUMS + 4) / 5)),  \
        0x1UL << (((evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0POL_Pos), (((pol) & 0x1UL) << (((evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0POL_Pos)))

/**
  * @brief  Common External Event X Input Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt_x External Event Number @ref HRPWM_ExtEvtNumETypeDef
  * @param  src External Event X Input Source
  * @return None
  */
#define __LL_HRPWM_Comm_ExtEvtXInputSrc_Set(__HRPWM__, evt_x, src)                                                     \
        MODIFY_REG(__LL_HRPWM_REG_OFFSET((__HRPWM__)->Common.EECR0, (evt_x) / 5 % ((HRPWM_EXT_EVT_NUMS + 4) / 5)),  \
        0x3UL << (((evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SRC_Pos), (((src) & 0x3UL) << (((evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SRC_Pos)))


/**
  * @brief  Common External Event Sample Clock Division Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  div External Event Sample Clock Division
  * @return None
  */
#define __LL_HRPWM_Comm_ExtEvtSampClkDiv_Set(__HRPWM__, div)        \
        MODIFY_REG((__HRPWM__)->Common.EECR2, HRPWM_COM_EECR2_EEVSD_Msk, (((div) & 0x3UL) << HRPWM_COM_EECR2_EEVSD_Pos))

/**
  * @brief  Common External Event X Filter Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt_x External Event Number @ref HRPWM_ExtEvtNumETypeDef
  * @param  len External Event X Filter Length
  * @return None
  */
#define __LL_HRPWM_Comm_ExtEvtXFilLen_Set(__HRPWM__, evt_x, len)                                                        \
        MODIFY_REG(__LL_HRPWM_REG_OFFSET((__HRPWM__)->Common.EECR2, (evt_x) / 5 % ((HRPWM_EXT_EVT_NUMS + 4) / 5)),   \
        0xfUL << (((evt_x) % 5) * 4 + HRPWM_COM_EECR2_EE0F_Pos), (((len) & 0xfUL) << (((evt_x) % 5) * 4 + HRPWM_COM_EECR2_EE0F_Pos)))


/**
  * @brief  Common ADC Trigger 0 Event Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt ADC Trigger 0 Event, combination of @ref HRPWM_Comm_ADC02TrigEvtSrcETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig0EvtSrcEn_Cfg(__HRPWM__, evt)                    \
        do {                                                                    \
            WRITE_REG((__HRPWM__)->Common.ADC0R, ((evt) & 0xFFFFFFFFUL));       \
            WRITE_REG((__HRPWM__)->Common.ADC0ER, ((evt) >> 32ULL));            \
        } while(0)


/**
  * @brief  Common ADC Trigger 1 Event Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt ADC Trigger 1 Event, combination of @ref HRPWM_Comm_ADC13TrigEvtSrcETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig1EvtSrcEn_Cfg(__HRPWM__, evt)                    \
        do {                                                                    \
            WRITE_REG((__HRPWM__)->Common.ADC1R, ((evt) & 0xFFFFFFFFUL));       \
            WRITE_REG((__HRPWM__)->Common.ADC1ER, ((evt) >> 32ULL));            \
        } while(0)


/**
  * @brief  Common ADC Trigger 2 Event Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt ADC Trigger 2 Event, combination of @ref HRPWM_Comm_ADC02TrigEvtSrcETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig2EvtSrcEn_Cfg(__HRPWM__, evt)                    \
        do {                                                                    \
            WRITE_REG((__HRPWM__)->Common.ADC2R, ((evt) & 0xFFFFFFFFUL));       \
            WRITE_REG((__HRPWM__)->Common.ADC2ER, ((evt) >> 32ULL));            \
        } while(0)


/**
  * @brief  Common ADC Trigger 3 Event Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt ADC Trigger 3 Event, combination of @ref HRPWM_Comm_ADC13TrigEvtSrcETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig3EvtSrcEn_Cfg(__HRPWM__, evt)                    \
        do {                                                                    \
            WRITE_REG((__HRPWM__)->Common.ADC3R, ((evt) & 0xFFFFFFFFUL));       \
            WRITE_REG((__HRPWM__)->Common.ADC3ER, ((evt) >> 32ULL));            \
        } while(0)


/**
  * @brief  Common ADC Trigger 4 Event Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt ADC Trigger 4 Event @ref HRPWM_Comm_ADC468TrigEvtSrcETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig4EvtSrc_Set(__HRPWM__, evt)      MODIFY_REG((__HRPWM__)->Common.ADC4R, HRPWM_COM_ADC4R_ADC4TRG_Msk,\
        (((evt) & (HRPWM_COM_ADC4R_ADC4TRG_Msk >> HRPWM_COM_ADC4R_ADC4TRG_Pos)) << HRPWM_COM_ADC4R_ADC4TRG_Pos))

/**
  * @brief  Common ADC Trigger 5 Event Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt ADC Trigger 5 Event @ref HRPWM_Comm_ADC579TrigEvtSrcETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig5EvtSrc_Set(__HRPWM__, evt)      MODIFY_REG((__HRPWM__)->Common.ADC4R, HRPWM_COM_ADC4R_ADC5TRG_Msk,\
        (((evt) & (HRPWM_COM_ADC4R_ADC5TRG_Msk >> HRPWM_COM_ADC4R_ADC5TRG_Pos)) << HRPWM_COM_ADC4R_ADC5TRG_Pos))

/**
  * @brief  Common ADC Trigger 6 Event Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt ADC Trigger 6 Event @ref HRPWM_Comm_ADC468TrigEvtSrcETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig6EvtSrc_Set(__HRPWM__, evt)      MODIFY_REG((__HRPWM__)->Common.ADC4R, HRPWM_COM_ADC4R_ADC6TRG_Msk,\
        (((evt) & (HRPWM_COM_ADC4R_ADC6TRG_Msk >> HRPWM_COM_ADC4R_ADC6TRG_Pos)) << HRPWM_COM_ADC4R_ADC6TRG_Pos))


/**
  * @brief  Common ADC Trigger 7 Event Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt ADC Trigger 7 Event @ref HRPWM_Comm_ADC579TrigEvtSrcETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig7EvtSrc_Set(__HRPWM__, evt)      MODIFY_REG((__HRPWM__)->Common.ADC5R, HRPWM_COM_ADC5R_ADC7TRG_Msk,\
        (((evt) & (HRPWM_COM_ADC5R_ADC7TRG_Msk >> HRPWM_COM_ADC5R_ADC7TRG_Pos)) << HRPWM_COM_ADC5R_ADC7TRG_Pos))

/**
  * @brief  Common ADC Trigger 8 Event Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt ADC Trigger 8 Event @ref HRPWM_Comm_ADC468TrigEvtSrcETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig8EvtSrc_Set(__HRPWM__, evt)      MODIFY_REG((__HRPWM__)->Common.ADC5R, HRPWM_COM_ADC5R_ADC8TRG_Msk,\
        (((evt) & (HRPWM_COM_ADC5R_ADC8TRG_Msk >> HRPWM_COM_ADC5R_ADC8TRG_Pos)) << HRPWM_COM_ADC5R_ADC8TRG_Pos))

/**
  * @brief  Common ADC Trigger 9 Event Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt ADC Trigger 9 Event @ref HRPWM_Comm_ADC579TrigEvtSrcETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig9EvtSrc_Set(__HRPWM__, evt)      MODIFY_REG((__HRPWM__)->Common.ADC5R, HRPWM_COM_ADC5R_ADC9TRG_Msk,\
        (((evt) & (HRPWM_COM_ADC5R_ADC9TRG_Msk >> HRPWM_COM_ADC5R_ADC9TRG_Pos)) << HRPWM_COM_ADC5R_ADC9TRG_Pos))


/**
  * @brief  Common ADC Trigger X Update Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  trigx ADC Trigger X Number @ref HRPWM_ADCTrigNumETypeDef (X=4~9)
  * @param  src ADC Trigger X Update Source @ref HRPWM_Comm_ADCTrigUpdSrcETypeDEF
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrigX4To9UpdSrc_Set(__HRPWM__, trigx, src)                                                        \
        MODIFY_REG((__HRPWM__)->Common.ADCUR, HRPWM_COM_ADCUR_USRC4_Msk << ((((trigx) % HRPWM_ADC_TRIG_NUMS) - 4) * 4), \
        (((src) & 0xfUL) << (HRPWM_COM_ADCUR_USRC4_Pos + (((trigx) % HRPWM_ADC_TRIG_NUMS) - 4) * 4)))

/**
  * @brief  Common ADC Trigger 4 Update Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src ADC Trigger 4 Update Source @ref HRPWM_Comm_ADCTrigUpdSrcETypeDEF
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig4UpdSrc_Set(__HRPWM__, src)      \
        MODIFY_REG((__HRPWM__)->Common.ADCUR, HRPWM_COM_ADCUR_USRC4_Msk, (((src) & 0xfUL) << HRPWM_COM_ADCUR_USRC4_Pos))

/**
  * @brief  Common ADC Trigger 5 Update Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src ADC Trigger 5 Update Source @ref HRPWM_Comm_ADCTrigUpdSrcETypeDEF
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig5UpdSrc_Set(__HRPWM__, src)      \
        MODIFY_REG((__HRPWM__)->Common.ADCUR, HRPWM_COM_ADCUR_USRC5_Msk, (((src) & 0xfUL) << HRPWM_COM_ADCUR_USRC5_Pos))

/**
  * @brief  Common ADC Trigger 6 Update Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src ADC Trigger 6 Update Source @ref HRPWM_Comm_ADCTrigUpdSrcETypeDEF
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig6UpdSrc_Set(__HRPWM__, src)      \
        MODIFY_REG((__HRPWM__)->Common.ADCUR, HRPWM_COM_ADCUR_USRC6_Msk, (((src) & 0xfUL) << HRPWM_COM_ADCUR_USRC6_Pos))

/**
  * @brief  Common ADC Trigger 7 Update Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src ADC Trigger 7 Update Source @ref HRPWM_Comm_ADCTrigUpdSrcETypeDEF
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig7UpdSrc_Set(__HRPWM__, src)      \
        MODIFY_REG((__HRPWM__)->Common.ADCUR, HRPWM_COM_ADCUR_USRC7_Msk, (((src) & 0xfUL) << HRPWM_COM_ADCUR_USRC7_Pos))

/**
  * @brief  Common ADC Trigger 8 Update Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src ADC Trigger 8 Update Source @ref HRPWM_Comm_ADCTrigUpdSrcETypeDEF
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig8UpdSrc_Set(__HRPWM__, src)      \
        MODIFY_REG((__HRPWM__)->Common.ADCUR, HRPWM_COM_ADCUR_USRC8_Msk, (((src) & 0xfUL) << HRPWM_COM_ADCUR_USRC8_Pos))

/**
  * @brief  Common ADC Trigger 9 Update Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src ADC Trigger 9 Update Source @ref HRPWM_Comm_ADCTrigUpdSrcETypeDEF
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig9UpdSrc_Set(__HRPWM__, src)      \
        MODIFY_REG((__HRPWM__)->Common.ADCUR, HRPWM_COM_ADCUR_USRC9_Msk, (((src) & 0xfUL) << HRPWM_COM_ADCUR_USRC9_Pos))


/**
  * @brief  Common ADC Trigger X Event Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  trigx ADC Trigger X Number @ref HRPWM_ADCTrigNumETypeDef (X=4~9)
  * @param  len ADC Trigger X Event Length @ref HRPWM_Comm_ADCTrigEvtLenETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrigX4To9EvtLen_Set(__HRPWM__, trigx, len)                                                          \
        MODIFY_REG((__HRPWM__)->Common.ADCLR, HRPWM_COM_ADCLR_TLEN4_Msk << ((((trigx) % HRPWM_ADC_TRIG_NUMS) - 4) * 4), \
        (((len) & 0xfUL) << (HRPWM_COM_ADCLR_TLEN4_Pos + ((((trigx) % HRPWM_ADC_TRIG_NUMS) - 4) * 4))))

/**
  * @brief  Common ADC Trigger 4 Event Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  len ADC Trigger 4 Event Length @ref HRPWM_Comm_ADCTrigEvtLenETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig4EvtLen_Set(__HRPWM__, len)      \
        MODIFY_REG((__HRPWM__)->Common.ADCLR, HRPWM_COM_ADCLR_TLEN4_Msk, (((len) & 0xfUL) << HRPWM_COM_ADCLR_TLEN4_Pos))

/**
  * @brief  Common ADC Trigger 5 Event Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  len ADC Trigger 5 Event Length @ref HRPWM_Comm_ADCTrigEvtLenETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig5EvtLen_Set(__HRPWM__, len)      \
        MODIFY_REG((__HRPWM__)->Common.ADCLR, HRPWM_COM_ADCLR_TLEN5_Msk, (((len) & 0xfUL) << HRPWM_COM_ADCLR_TLEN5_Pos))

/**
  * @brief  Common ADC Trigger 6 Event Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  len ADC Trigger 6 Event Length @ref HRPWM_Comm_ADCTrigEvtLenETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig6EvtLen_Set(__HRPWM__, len)      \
        MODIFY_REG((__HRPWM__)->Common.ADCLR, HRPWM_COM_ADCLR_TLEN6_Msk, (((len) & 0xfUL) << HRPWM_COM_ADCLR_TLEN6_Pos))

/**
  * @brief  Common ADC Trigger 7 Event Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  len ADC Trigger 7 Event Length @ref HRPWM_Comm_ADCTrigEvtLenETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig7EvtLen_Set(__HRPWM__, len)      \
        MODIFY_REG((__HRPWM__)->Common.ADCLR, HRPWM_COM_ADCLR_TLEN7_Msk, (((len) & 0xfUL) << HRPWM_COM_ADCLR_TLEN7_Pos))

/**
  * @brief  Common ADC Trigger 8 Event Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  len ADC Trigger 8 Event Length @ref HRPWM_Comm_ADCTrigEvtLenETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig8EvtLen_Set(__HRPWM__, len)      \
        MODIFY_REG((__HRPWM__)->Common.ADCLR, HRPWM_COM_ADCLR_TLEN8_Msk, (((len) & 0xfUL) << HRPWM_COM_ADCLR_TLEN8_Pos))

/**
  * @brief  Common ADC Trigger 9 Event Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  len ADC Trigger 9 Event Length @ref HRPWM_Comm_ADCTrigEvtLenETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrig9EvtLen_Set(__HRPWM__, len)      \
        MODIFY_REG((__HRPWM__)->Common.ADCLR, HRPWM_COM_ADCLR_TLEN9_Msk, (((len) & 0xfUL) << HRPWM_COM_ADCLR_TLEN9_Pos))


/**
  * @brief  Common ADC Trigger X Post Scaler Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  tirgx ADC Trigger Number @ref HRPWM_ADCTrigNumETypeDef
  * @param  scl ADC Trigger X Post Scaler
  * @return None
  */
#define __LL_HRPWM_Comm_ADCTrigXPostScaler_Set(__HRPWM__, tirgx, scl)                                                                   \
        MODIFY_REG(__LL_HRPWM_REG_OFFSET((__HRPWM__)->Common.ADPSR0, (tirgx) / 5 % ((HRPWM_ADC_TRIG_NUMS + 4) / 5)),                    \
        HRPWM_COM_ADPSR0_PSC0_Msk << (((tirgx) % 5) * 6), (((scl) & 0x1fUL) << (((tirgx) % 5) * 6 + HRPWM_COM_ADPSR0_PSC0_Pos)))


/**
  * @brief  Common DLL Start
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_DLL_Start(__HRPWM__)                    SET_BIT((__HRPWM__)->Common.DLLCR, HRPWM_COM_DLLCR_DLLSTART_Msk)

/**
  * @brief  Common DLL Stop
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_DLL_Stop(__HRPWM__)                     CLEAR_BIT((__HRPWM__)->Common.DLLCR, HRPWM_COM_DLLCR_DLLSTART_Msk)

/**
  * @brief  Common DLL Current Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  cur DLL Current
  * @return None
  */
#define __LL_HRPWM_Comm_DLLCur_Set(__HRPWM__, cur)              \
        MODIFY_REG((__HRPWM__)->Common.DLLCR, HRPWM_COM_DLLCR_DLLGCP_Msk, (((cur) & 0x3UL) << HRPWM_COM_DLLCR_DLLGCP_Pos))

/**
  * @brief  Common DLL Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_DLL_En(__HRPWM__)                       SET_BIT((__HRPWM__)->Common.DLLCR, HRPWM_COM_DLLCR_DLLEN_Msk)

/**
  * @brief  Common DLL Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_DLL_Dis(__HRPWM__)                      CLEAR_BIT((__HRPWM__)->Common.DLLCR, HRPWM_COM_DLLCR_DLLEN_Msk)


/**
  * @brief  Common PWMx EventX Source Extended Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt_x PWMx External Event Number @ref HRPWM_ExtEvtNumETypeDef
  * @param  src PWMx EventX Source @ref HRPWM_Comm_ExtEvtXInputSrcETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_ExtEvtXInputSrcEx_Set(__HRPWM__, evt_x, src)            \
        do {                                                                    \
                MODIFY_REG(__LL_HRPWM_REG_OFFSET((__HRPWM__)->Common.EECR0, (evt_x) / 5 % ((HRPWM_EXT_EVT_NUMS + 4) / 5)),    \
                    0x3UL << (((evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SRC_Pos),                                                \
                    (((src) & 0x3UL) << (((evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SRC_Pos)));                                   \
                MODIFY_REG((__HRPWM__)->Common.EECER, 0x3UL << (((evt_x) % 10) * 2),                                          \
                    ((((src) & 0xcUL) >> 0x2UL) << (((evt_x) % 10) * 2)));                                                    \
        } while(0)
        

/**
  * @brief  Common PWMx EventX Source Extended Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt_x PWMx External Event Number @ref HRPWM_ExtEvtNumETypeDef
  * @return PWMx EventX Source @ref HRPWM_Comm_ExtEvtXInputSrcETypeDef
  */
#define __LL_HRPWM_Comm_ExtEvtXInputSrcEx_Get(__HRPWM__, evt_x)                 \
        (((READ_BIT_SHIFT((__HRPWM__)->Common.EECER, 0x3UL << (((evt_x) % 10) * 2), (((evt_x) % 10) * 2))) << 2UL) |       \
         ((READ_BIT_SHIFT(__LL_HRPWM_REG_OFFSET((__HRPWM__)->Common.EECR0, (evt_x) / 5 % ((HRPWM_EXT_EVT_NUMS + 4) / 5)),   \
              0x3UL << (((evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SRC_Pos), (((evt_x) % 5) * 6 + HRPWM_COM_EECR0_EE0SRC_Pos))) & 0x3UL))

/**
  * @brief  Common Fault X Input Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx PWMx Fault Number @ref HRPWM_FltNumETypeDef
  * @param  src Common Fault X Input Source @ref HRPWM_Comm_FltXInputSrcETypeDef (X = 0 ~ HRPWM_FLT_NUMS-1)
  * @return None
  */
#define __LL_HRPWM_Comm_FltXInputSrc_Set(__HRPWM__, fltx, src)                                                          \
        MODIFY_REG((__HRPWM__)->Common.FLTINR0, HRPWM_COM_FLTINR0_FLT0SRC_Msk << (((fltx) % HRPWM_FLT_NUMS) * 4),   \
        (((src) & 0x3UL) << (((fltx) % HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR0_FLT0SRC_Pos)))

/**
  * @brief  Common Fault X Input Polarity Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx PWMx Fault Number @ref HRPWM_FltNumETypeDef
  * @param  pol Common Fault X Input Polarity @ref HRPWM_Comm_FltInputPolETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_FltXInputPol_Set(__HRPWM__, fltx, pol)                                                      \
        MODIFY_REG((__HRPWM__)->Common.FLTINR0, HRPWM_COM_FLTINR0_FLT0P_Msk << (((fltx) % HRPWM_FLT_NUMS) * 4), \
        (((pol) & 0x1UL) << (((fltx) % HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR0_FLT0P_Pos)))

/**
  * @brief  Common Fault X Input Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx PWMx Fault Number @ref HRPWM_FltNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_FltXInput_En(__HRPWM__, fltx)           \
        SET_BIT((__HRPWM__)->Common.FLTINR0, BIT((((fltx) % HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR0_FLT0E_Pos)))

/**
  * @brief  Common Fault X Input Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx PWMx Fault Number @ref HRPWM_FltNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_FltXInput_Dis(__HRPWM__, fltx)          \
        CLEAR_BIT((__HRPWM__)->Common.FLTINR0, BIT((((fltx) % HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR0_FLT0E_Pos)))


/**
  * @brief  Common Fault Sample Clock Division Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  div Fault Sample Clock Division
  * @return None
  */
#define __LL_HRPWM_Comm_FltSampClkDiv_Set(__HRPWM__, div)       \
        MODIFY_REG((__HRPWM__)->Common.FLTINR1, HRPWM_COM_FLTINR1_FLTSD_Msk, (((div) & 0x3UL) << HRPWM_COM_FLTINR1_FLTSD_Pos))

/**
  * @brief  Common Fault X Filter Length Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx Fault Number @ref HRPWM_FltNumETypeDef
  * @param  len Fault X Filter Length
  * @return None
  */
#define __LL_HRPWM_Comm_FltXFilLen_Set(__HRPWM__, fltx, len)                                                                            \
        MODIFY_REG(__LL_HRPWM_REG_OFFSET((__HRPWM__)->Common.FLTINR1, (fltx) / 6 % ((HRPWM_FLT_NUMS + 5) / 6)),                         \
        HRPWM_COM_FLTINR1_FLT0F_Msk << (((fltx) % 6) * 4), (((len) & 0xfUL) << (((fltx) % 6) * 4 + HRPWM_COM_FLTINR1_FLT0F_Pos)))


/**
  * @brief  Common Fault X Counter Reset Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx Fault Number @ref HRPWM_FltNumETypeDef
  * @param  mode Fault X Counter Reset Mode
  * @return None
  */
#define __LL_HRPWM_Comm_FltXCntrRstMode_Set(__HRPWM__, fltx, mode)                                                      \
        MODIFY_REG((__HRPWM__)->Common.FLTINR2, HRPWM_COM_FLTINR2_FLT0RSTM_Msk << (((fltx) % HRPWM_FLT_NUMS) * 4),  \
        (((mode) & 0x1UL) << (((fltx) % HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0RSTM_Pos)))

/**
  * @brief  Common Fault X Counter Reset
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx Fault Number @ref HRPWM_FltNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_FltXCntr_Rst(__HRPWM__, fltx)           \
        SET_BIT((__HRPWM__)->Common.FLTINR2, BIT((((fltx) % HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0CRES_Pos)))

/**
  * @brief  Judge is Common Fault X Counter Resetting or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx Fault Number @ref HRPWM_FltNumETypeDef
  * @retval 0 Common Fault X Counter isn't Resetting
  * @retval 1 Common Fault X Counter is Resetting
  */
#define __LL_HRPWM_Comm_IsFltXCntrReseting(__HRPWM__, fltx)                                                                    \
        READ_BIT_SHIFT((__HRPWM__)->Common.FLTINR2, BIT((((fltx) % HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0CRES_Pos)),  \
        (((fltx) % HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0CRES_Pos))

/**
  * @brief  Common Fault X Blank Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx Fault Number @ref HRPWM_FltNumETypeDef
  * @param  src Fault X Blank Source
  * @return None
  */
#define __LL_HRPWM_Comm_FltXBlkSrc_Set(__HRPWM__, fltx, src)                                                            \
        MODIFY_REG((__HRPWM__)->Common.FLTINR2, HRPWM_COM_FLTINR2_FLT0BLKS_Msk << (((fltx) % HRPWM_FLT_NUMS) * 4),  \
        (((src) & 0x1UL) << (((fltx) % HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0BLKS_Pos)))

/**
  * @brief  Common Fault X Blank Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx Fault Number @ref HRPWM_FltNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_FltXBlk_En(__HRPWM__, fltx)             \
        SET_BIT((__HRPWM__)->Common.FLTINR2, BIT((((fltx) % HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0BLKE_Pos)))

/**
  * @brief  Common Fault X Blank Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx Fault Number @ref HRPWM_FltNumETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_FltXBlk_Dis(__HRPWM__, fltx)            \
        CLEAR_BIT((__HRPWM__)->Common.FLTINR2, BIT((((fltx) % HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR2_FLT0BLKE_Pos)))


/**
  * @brief  Common Fault X Counter Threshold Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  fltx Fault Number @ref HRPWM_FltNumETypeDef
  * @param  thres Fault X Counter Threshold
  * @return None
  */
#define __LL_HRPWM_Comm_FltXCntrThres_Set(__HRPWM__, fltx, thres)                                                       \
        MODIFY_REG((__HRPWM__)->Common.FLTINR3, HRPWM_COM_FLTINR3_FLT0CNT_Msk << (((fltx) % HRPWM_FLT_NUMS) * 4),   \
        (((thres) & 0xfUL) << (((fltx) % HRPWM_FLT_NUMS) * 4 + HRPWM_COM_FLTINR3_FLT0CNT_Pos)))


/**
  * @brief  Judge is Common Burst Mode Active or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common Burst Mode is Inactive
  * @retval 1 Common Burst Mode is Active
  */
#define __LL_HRPWM_Comm_IsBurstModeActive(__HRPWM__)            \
        READ_BIT_SHIFT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMSTAT_Msk, HRPWM_COM_BMCR_BMSTAT_Pos)

/**
  * @brief  Common Burst Mode Force Exit
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModeFrcExit(__HRPWM__)             SET_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMEXIT_Msk)

/**
  * @brief  Judge is Common Burst Mode Exiting or not
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @retval 0 Common Burst Mode isn't Exiting
  * @retval 1 Common Burst Mode is Exiting
  */
#define __LL_HRPWM_Comm_IsBurstModeExiting(__HRPWM__)           \
        READ_BIT_SHIFT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMEXIT_Msk, HRPWM_COM_BMCR_BMEXIT_Pos)

/**
  * @brief  Common PWM7 Counter Stop In Burst Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM7CntrStopInBurstMode_En(__HRPWM__)   SET_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS7_Msk)

/**
  * @brief  Common PWM7 Counter Stop In Burst Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM7CntrStopInBurstMode_Dis(__HRPWM__)  CLEAR_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS7_Msk)

/**
  * @brief  Common PWM6 Counter Stop In Burst Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM6CntrStopInBurstMode_En(__HRPWM__)   SET_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS6_Msk)

/**
  * @brief  Common PWM6 Counter Stop In Burst Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM6CntrStopInBurstMode_Dis(__HRPWM__)  CLEAR_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS6_Msk)

/**
  * @brief  Common PWM5 Counter Stop In Burst Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM5CntrStopInBurstMode_En(__HRPWM__)   SET_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS5_Msk)

/**
  * @brief  Common PWM5 Counter Stop In Burst Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM5CntrStopInBurstMode_Dis(__HRPWM__)  CLEAR_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS5_Msk)

/**
  * @brief  Common PWM4 Counter Stop In Burst Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM4CntrStopInBurstMode_En(__HRPWM__)   SET_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS4_Msk)

/**
  * @brief  Common PWM4 Counter Stop In Burst Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM4CntrStopInBurstMode_Dis(__HRPWM__)  CLEAR_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS4_Msk)

/**
  * @brief  Common PWM3 Counter Stop In Burst Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM3CntrStopInBurstMode_En(__HRPWM__)   SET_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS3_Msk)

/**
  * @brief  Common PWM3 Counter Stop In Burst Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM3CntrStopInBurstMode_Dis(__HRPWM__)  CLEAR_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS3_Msk)

/**
  * @brief  Common PWM2 Counter Stop In Burst Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM2CntrStopInBurstMode_En(__HRPWM__)   SET_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS2_Msk)

/**
  * @brief  Common PWM2 Counter Stop In Burst Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM2CntrStopInBurstMode_Dis(__HRPWM__)  CLEAR_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS2_Msk)

/**
  * @brief  Common PWM1 Counter Stop In Burst Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM1CntrStopInBurstMode_En(__HRPWM__)   SET_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS1_Msk)

/**
  * @brief  Common PWM1 Counter Stop In Burst Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM1CntrStopInBurstMode_Dis(__HRPWM__)  CLEAR_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS1_Msk)

/**
  * @brief  Common PWM0 Counter Stop In Burst Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM0CntrStopInBurstMode_En(__HRPWM__)   SET_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS0_Msk)

/**
  * @brief  Common PWM0 Counter Stop In Burst Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_PWM0CntrStopInBurstMode_Dis(__HRPWM__)  CLEAR_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMDIS0_Msk)

/**
  * @brief  Common PWMx Counter Stop In Burst Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_PWMxCntrStopInBurstMode_En(__HRPWM__, pwmx)     \
        SET_BIT((__HRPWM__)->Common.BMCR, BIT(((pwmx) % PWMx_NUMS) + HRPWM_COM_BMCR_BMDIS0_Pos))

/**
  * @brief  Common PWMx Counter Stop In Burst Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_PWMxCntrStopInBurstMode_Dis(__HRPWM__, pwmx)    \
        CLEAR_BIT((__HRPWM__)->Common.BMCR, BIT(((pwmx) % PWMx_NUMS) + HRPWM_COM_BMCR_BMDIS0_Pos))

/**
  * @brief  Common Master PWM Counter Stop In Burst Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_MstPWMCntrStopInBurstMode_En(__HRPWM__)   SET_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_MBMDIS_Msk)

/**
  * @brief  Common Master PWM Counter Stop In Burst Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_MstPWMCntrStopInBurstMode_Dis(__HRPWM__)  CLEAR_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_MBMDIS_Msk)

/**
  * @brief  Common Burst Mode Trigger Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  mode Burst Mode Trigger Mode @ref HRPWM_Comm_BurstTrigModeETypeDef
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModeTrigMode_Set(__HRPWM__, mode)  \
        MODIFY_REG((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMTM_Msk, (((mode) & 0x1UL) << HRPWM_COM_BMCR_BMTM_Pos))

/**
  * @brief  Common Burst Mode Trigger Mode Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return Burst Mode Trigger Mode @ref HRPWM_Comm_BurstTrigModeETypeDef
  */
#define __LL_HRPWM_Comm_BurstModeTrigMode_Get(__HRPWM__)        \
        READ_BIT_SHIFT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMTM_Msk, HRPWM_COM_BMCR_BMTM_Pos)

/**
  * @brief  Common Burst Mode Preload Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModePreload_En(__HRPWM__)          SET_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMPREN_Msk)

/**
  * @brief  Common Burst Mode Preload Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModePreload_Dis(__HRPWM__)         CLEAR_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMPREN_Msk)

/**
  * @brief  Common Burst Mode Clock Prescaler Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  scl Burst Mode Clock Prescaler
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModeClkPrescl_Set(__HRPWM__, scl)  \
        MODIFY_REG((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMPRSC_Msk, (((scl) & 0xfUL) << HRPWM_COM_BMCR_BMPRSC_Pos))

/**
  * @brief  Common Burst Mode Clock Source Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  src Burst Mode Clock Source
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModeClkSrc_Set(__HRPWM__, src)     \
        MODIFY_REG((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMCLK_Msk, (((src) & 0xfUL) << HRPWM_COM_BMCR_BMCLK_Pos))

/**
  * @brief  Common Burst Work Mode Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  mode Burst Work Mode
  * @return None
  */
#define __LL_HRPWM_Comm_BurstWorkMode_Set(__HRPWM__, mode)      \
        MODIFY_REG((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BMOM_Msk, (((mode) & 0x1UL) << HRPWM_COM_BMCR_BMOM_Pos))

/**
  * @brief  Common Burst Mode Enable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_BurstMode_En(__HRPWM__)                 SET_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BME_Msk)

/**
  * @brief  Common Burst Mode Disable
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return None
  */
#define __LL_HRPWM_Comm_BurstMode_Dis(__HRPWM__)                CLEAR_BIT((__HRPWM__)->Common.BMCR, HRPWM_COM_BMCR_BME_Msk)


/**
  * @brief  Common Burst Mode Trigger Event Enable Config
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  evt Burst Mode Trigger Event
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModeTrigEvtEn_Cfg(__HRPWM__, evt)                      \
        do {                                                                        \
            WRITE_REG((__HRPWM__)->Common.BMTRGR0, ((evt) & 0xFFFFFFFFUL));         \
            WRITE_REG((__HRPWM__)->Common.BMTRGR1, ((evt) >> 32ULL));               \
        } while(0)


/**
  * @brief  Common Burst Mode Period Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  prd Burst Mode Period
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModePrd_Set(__HRPWM__, prd)        WRITE_REG((__HRPWM__)->Common.BMPER, ((prd) & 0xffffUL))


/**
  * @brief  Common Burst Mode Compare Value Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  val Burst Mode Compare Value
  * @return None
  */
#define __LL_HRPWM_Comm_BurstModeCmpVal_Set(__HRPWM__, val)     WRITE_REG((__HRPWM__)->Common.BMCMPR, ((val) & 0xffffUL))


/**
  * @brief  Common Burst DMA Master PWM Register Update Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  reg_upd Master PWM Register Update Mask
  * @return None
  */
#define __LL_HRPWM_Comm_BurstDMAMstPWMRegUpd_Set(__HRPWM__, reg_upd)        WRITE_REG((__HRPWM__)->Common.BDMUPR, reg_upd)


/**
  * @brief  Common Burst DMA Slave PWMx Register Update Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  pwmx PWMx Number @ref HRPWM_PWMETypeDef
  * @param  reg_upd Slave PWMx Register Update Mask
  * @return None
  */
#define __LL_HRPWM_Comm_BurstDMASlvPWMxRegUpd_Set(__HRPWM__, pwmx, reg_upd) \
        WRITE_REG(__LL_HRPWM_REG_OFFSET((__HRPWM__)->Common.BDUPR0, (pwmx) % PWMx_NUMS), reg_upd)

/**
  * @brief  Common Burst DMA Write Address Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  addr Burst DMA Write Address
  * @return None
  */
#define __LL_HRPWM_Comm_BurstDMAWriteAddr_Set(__HRPWM__, addr)  WRITE_REG((__HRPWM__)->Common.BDMWADR, addr)

/**
  * @brief  Common Burst DMA Write Address Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return Burst DMA Write Address
  */
#define __LL_HRPWM_Comm_BurstDMAWriteAddr_Get(__HRPWM__)        \
        READ_BIT_SHIFT((__HRPWM__)->Common.BDMWADR, HRPWM_COM_BDMWADR_BDMADR_Msk, HRPWM_COM_BDMWADR_BDMADR_Pos)

/**
  * @brief  Common Burst DMA Read Address Set
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @param  addr Burst DMA Read Address
  * @return None
  */
#define __LL_HRPWM_Comm_BurstDMAAddr_Set(__HRPWM__, addr)       WRITE_REG((__HRPWM__)->Common.BDMADR, addr)

/**
  * @brief  Common Burst DMA Read Address Get
  * @param  __HRPWM__ Specifies HRPWM peripheral
  * @return Burst DMA Write Address
  */
#define __LL_HRPWM_Comm_BurstDMAReadAddr_Get(__HRPWM__)         \
        READ_BIT_SHIFT((__HRPWM__)->Common.BDMADR, HRPWM_COM_BDMADR_BDMADR_Msk, HRPWM_COM_BDMADR_BDMADR_Pos)

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup HRPWM_LL_Exported_Types HRPWM LL Exported Types
  * @brief    HRPWM LL Exported Types
  * @{
  */

/**
  * @brief HRPWM PWM Definition
  */
typedef enum {
    HRPWM_SLV_PWM_0 = 0,                        /*!< HRPWM Slave PWM  0         */
    HRPWM_SLV_PWM_1,                            /*!< HRPWM Slave PWM  1         */
    HRPWM_SLV_PWM_2,                            /*!< HRPWM Slave PWM  2         */
    HRPWM_SLV_PWM_3,                            /*!< HRPWM Slave PWM  3         */
    HRPWM_SLV_PWM_4,                            /*!< HRPWM Slave PWM  4         */
    HRPWM_SLV_PWM_5,                            /*!< HRPWM Slave PWM  5         */
    HRPWM_SLV_PWM_6,                            /*!< HRPWM Slave PWM  6         */
    HRPWM_SLV_PWM_7,                            /*!< HRPWM Slave PWM  7         */
    HRPWM_SLV_PWM_NUMS,                         /*!< HRPWM Slave PWM Numbers    */
    PWMx_NUMS = HRPWM_SLV_PWM_NUMS,             /*!< PWMx_NUMS                  */

    HRPWM_MST_PWM,                              /*!< HRPWM Master PWM           */
} HRPWM_PWMETypeDef;

/**
  * @brief HRPWM PWM Mask Definition
  */
typedef enum {
    HRPWM_MST_PWM_MASK   = BIT(0),              /*!< HRPWM Master PWM Mask      */
    HRPWM_SLV_PWM_0_MASK = BIT(1),              /*!< HRPWM Slave PWM  0 Mask    */
    HRPWM_SLV_PWM_1_MASK = BIT(2),              /*!< HRPWM Slave PWM  1 Mask    */
    HRPWM_SLV_PWM_2_MASK = BIT(3),              /*!< HRPWM Slave PWM  2 Mask    */
    HRPWM_SLV_PWM_3_MASK = BIT(4),              /*!< HRPWM Slave PWM  3 Mask    */
    HRPWM_SLV_PWM_4_MASK = BIT(5),              /*!< HRPWM Slave PWM  4 Mask    */
    HRPWM_SLV_PWM_5_MASK = BIT(6),              /*!< HRPWM Slave PWM  5 Mask    */
    HRPWM_SLV_PWM_6_MASK = BIT(7),              /*!< HRPWM Slave PWM  6 Mask    */
    HRPWM_SLV_PWM_7_MASK = BIT(8),              /*!< HRPWM Slave PWM  7 Mask    */
} HRPWM_PWMMaskETypeDef;

/**
  * @brief HRPWM PWM Output Mask Definition
  */
typedef enum {
    HRPWM_SLV_PWM_0_OUT_A_MASK = BIT(0),        /*!< HRPWM Slave PWM 0 Out A Mask   */
    HRPWM_SLV_PWM_0_OUT_B_MASK = BIT(1),        /*!< HRPWM Slave PWM 0 Out B Mask   */
    HRPWM_SLV_PWM_1_OUT_A_MASK = BIT(2),        /*!< HRPWM Slave PWM 1 Out A Mask   */
    HRPWM_SLV_PWM_1_OUT_B_MASK = BIT(3),        /*!< HRPWM Slave PWM 1 Out B Mask   */
    HRPWM_SLV_PWM_2_OUT_A_MASK = BIT(4),        /*!< HRPWM Slave PWM 2 Out A Mask   */
    HRPWM_SLV_PWM_2_OUT_B_MASK = BIT(5),        /*!< HRPWM Slave PWM 2 Out B Mask   */
    HRPWM_SLV_PWM_3_OUT_A_MASK = BIT(6),        /*!< HRPWM Slave PWM 3 Out A Mask   */
    HRPWM_SLV_PWM_3_OUT_B_MASK = BIT(7),        /*!< HRPWM Slave PWM 3 Out B Mask   */
    HRPWM_SLV_PWM_4_OUT_A_MASK = BIT(8),        /*!< HRPWM Slave PWM 4 Out A Mask   */
    HRPWM_SLV_PWM_4_OUT_B_MASK = BIT(9),        /*!< HRPWM Slave PWM 4 Out B Mask   */
    HRPWM_SLV_PWM_5_OUT_A_MASK = BIT(10),       /*!< HRPWM Slave PWM 5 Out A Mask   */
    HRPWM_SLV_PWM_5_OUT_B_MASK = BIT(11),       /*!< HRPWM Slave PWM 5 Out B Mask   */
    HRPWM_SLV_PWM_6_OUT_A_MASK = BIT(12),       /*!< HRPWM Slave PWM 6 Out A Mask   */
    HRPWM_SLV_PWM_6_OUT_B_MASK = BIT(13),       /*!< HRPWM Slave PWM 6 Out B Mask   */
    HRPWM_SLV_PWM_7_OUT_A_MASK = BIT(14),       /*!< HRPWM Slave PWM 7 Out A Mask   */
    HRPWM_SLV_PWM_7_OUT_B_MASK = BIT(15),       /*!< HRPWM Slave PWM 7 Out B Mask   */
} HRPWM_PWMOutputMaskETypeDef;

/**
  * @brief HRPWM External Event Number Definition
  */
typedef enum {
    HRPWM_EXT_EVT_NUM_0 = 0,                    /*!< HRPWM External Event Number 0  */
    HRPWM_EXT_EVT_NUM_1,                        /*!< HRPWM External Event Number 1  */
    HRPWM_EXT_EVT_NUM_2,                        /*!< HRPWM External Event Number 2  */
    HRPWM_EXT_EVT_NUM_3,                        /*!< HRPWM External Event Number 3  */
    HRPWM_EXT_EVT_NUM_4,                        /*!< HRPWM External Event Number 4  */
    HRPWM_EXT_EVT_NUM_5,                        /*!< HRPWM External Event Number 5  */
    HRPWM_EXT_EVT_NUM_6,                        /*!< HRPWM External Event Number 6  */
    HRPWM_EXT_EVT_NUM_7,                        /*!< HRPWM External Event Number 7  */
    HRPWM_EXT_EVT_NUM_8,                        /*!< HRPWM External Event Number 8  */
    HRPWM_EXT_EVT_NUM_9,                        /*!< HRPWM External Event Number 9  */
    HRPWM_EXT_EVT_NUMS,                         /*!< HRPWM External Event Numbers   */
} HRPWM_ExtEvtNumETypeDef;

/**
  * @brief HRPWM Fault Number Definition
  */
typedef enum {
    HRPWM_FLT_NUM_0 = 0,                        /*!< HRPWM Fault Number 0   */
    HRPWM_FLT_NUM_1,                            /*!< HRPWM Fault Number 1   */
    HRPWM_FLT_NUM_2,                            /*!< HRPWM Fault Number 2   */
    HRPWM_FLT_NUM_3,                            /*!< HRPWM Fault Number 3   */
    HRPWM_FLT_NUM_4,                            /*!< HRPWM Fault Number 4   */
    HRPWM_FLT_NUM_5,                            /*!< HRPWM Fault Number 5   */
    HRPWM_FLT_NUM_6,                            /*!< HRPWM Fault Number 6   */
    HRPWM_FLT_NUM_7,                            /*!< HRPWM Fault Number 7   */
    HRPWM_FLT_NUMS,                             /*!< HRPWM Fault Numbers    */
} HRPWM_FltNumETypeDef;

/**
  * @brief HRPWM ADC Trigger Number Definition
  */
typedef enum {
    HRPWM_ADC_TRIG_NUM_0 = 0,                   /*!< HRPWM ADC Trigger Number 0 */
    HRPWM_ADC_TRIG_NUM_1,                       /*!< HRPWM ADC Trigger Number 1 */
    HRPWM_ADC_TRIG_NUM_2,                       /*!< HRPWM ADC Trigger Number 2 */
    HRPWM_ADC_TRIG_NUM_3,                       /*!< HRPWM ADC Trigger Number 3 */
    HRPWM_ADC_TRIG_NUM_4,                       /*!< HRPWM ADC Trigger Number 4 */
    HRPWM_ADC_TRIG_NUM_5,                       /*!< HRPWM ADC Trigger Number 5 */
    HRPWM_ADC_TRIG_NUM_6,                       /*!< HRPWM ADC Trigger Number 6 */
    HRPWM_ADC_TRIG_NUM_7,                       /*!< HRPWM ADC Trigger Number 7 */
    HRPWM_ADC_TRIG_NUM_8,                       /*!< HRPWM ADC Trigger Number 8 */
    HRPWM_ADC_TRIG_NUM_9,                       /*!< HRPWM ADC Trigger Number 9 */
    HRPWM_ADC_TRIG_NUMS,                        /*!< HRPWM ADC Trigger Numbers  */
} HRPWM_ADCTrigNumETypeDef;

/**
  * @brief HRPWM PWM Work Mode Definition
  */
typedef enum {
    HRPWM_WORK_MODE_SINGLE = 0,                 /*!< PWM Work Mode Single   */
    HRPWM_WORK_MODE_CONTINUE,                   /*!< PWM Work Mode Continue */
} HRPWM_WorkModeETypeDef;

/**
  * @brief HRPWM DAC Sync Source Definition
  */
typedef enum {
    HRPWM_DAC_SYNC_SRC_NONE = 0,                /*!< DAC Sync Source None   */
    HRPWM_DAC_SYNC_SRC_TRIG0,                   /*!< DAC Sync Source Trig0  */
    HRPWM_DAC_SYNC_SRC_TRIG1,                   /*!< DAC Sync Source Trig1  */
    HRPWM_DAC_SYNC_SRC_TRIG2,                   /*!< DAC Sync Source Trig2  */
} HRPWM_DACSyncSrcETypeDef;

/**
  * @brief HRPWM Clock Prescaler Definition
  */
typedef enum {
    HRPWM_CLK_PRESCL_MUL_32 = 0,                /*!< Clock Prescaler Multi 32   */
    HRPWM_CLK_PRESCL_MUL_16,                    /*!< Clock Prescaler Multi 16   */
    HRPWM_CLK_PRESCL_MUL_8,                     /*!< Clock Prescaler Multi 8    */
    HRPWM_CLK_PRESCL_MUL_4,                     /*!< Clock Prescaler Multi 4    */
    HRPWM_CLK_PRESCL_MUL_2,                     /*!< Clock Prescaler Multi 2    */

    HRPWM_CLK_PRESCL_DIV_1,                     /*!< Clock Prescaler Division 1 */
    HRPWM_CLK_PRESCL_DIV_2,                     /*!< Clock Prescaler Division 2 */
    HRPWM_CLK_PRESCL_DIV_4,                     /*!< Clock Prescaler Division 4 */
} HRPWM_ClkPresclETypeDef;

/**
  * @brief HRPWM PWM Interleaved Mode Definition
  */
typedef enum {
    HRPWM_INTLVD_MODE_CLOSE = 0,                /*!< PWM Interleaved Mode Close */
    HRPWM_INTLVD_MODE_1_3,                      /*!< PWM Interleaved Mode 1/3   */
    HRPWM_INTLVD_MODE_1_4,                      /*!< PWM Interleaved Mode 1/4   */
} HRPWM_IntlvdModeETypeDef;



/**
  * @brief HRPWM Master Update Gate Definition
  */
typedef enum {
    HRPWM_MST_UPD_GATE_BST_DMA_INDEPEND = 0,        /*!< Master Update Gate Burst DMA Done Independent          */
    HRPWM_MST_UPD_GATE_BST_DMA_DONE     = 2,        /*!< Master Update Gate Burst DMA Done Done                 */
    HRPWM_MST_UPD_GATE_BST_DMA_NEXT,                /*!< Master Update Gate Burst DMA Done Next Update Event    */
} HRPWM_Mst_UpdGateETypeDef;

/**
  * @brief HRPWM Master Sync Mode Definition
  */
typedef enum {
    HRPWM_MST_SYNC_MODE_DIS     = 0,                /*!< Master Sync Mode Disable       */
    HRPWM_MST_SYNC_MODE_MST     = BIT(0),           /*!< Master Sync Mode Master        */
    HRPWM_MST_SYNC_MODE_SLV     = BIT(1),           /*!< Master Sync Mode Slave         */
    HRPWM_MST_SYNC_MODE_MST_SLV = BIT(0) | BIT(1),  /*!< Master Sync Mode Master&Slave  */
} HRPWM_Mst_SyncModeETypeDef;

/**
  * @brief HRPWM Master Sync Output Source Definition
  */
typedef enum {
    HRPWM_MST_SYNC_OUT_SRC_MST_PWM_START = 0,   /*!< Master Sync Output Source Master PWM Start     */
    HRPWM_MST_SYNC_OUT_SRC_MST_PWM_CMPA,        /*!< Master Sync Output Source Master PWM Compare A */
    HRPWM_MST_SYNC_OUT_SRC_PWM0_START_RST,      /*!< Master Sync Output Source PWM0 Start/Reset     */
    HRPWM_MST_SYNC_OUT_SRC_PWM0_CMPA,           /*!< Master Sync Output Source PWM0 Compare A       */
} HRPWM_Mst_SyncOutSrcETypeDef;

/**
  * @brief HRPWM Master Sync Output Polarity Definition
  */
typedef enum {
    HRPWM_MST_SYNC_OUT_POL_ACT_HIGH = 0,        /*!< Master Sync Output Polarity Active High    */
    HRPWM_MST_SYNC_OUT_POL_ACT_LOW,             /*!< Master Sync Output Polarity Active Low     */
} HRPWM_Mst_SyncOutPolETypeDef;

/**
  * @brief HRPWM Master Sync Input Source Definition
  */
typedef enum {
    HRPWM_MST_SYNC_IN_SRC_TMR9_TRGO = 0,        /*!< Master Sync Input Source TMR9_TRGO     */
    HRPWM_MST_SYNC_IN_SRC_HRPWM_SCIN,           /*!< Master Sync Input Source HRPWM SCIN    */
} HRPWM_Mst_SyncInSrcETypeDef;

/**
  * @brief HRPWM Master PWM Interrupt Definition
  */
typedef enum {
    HRPWM_MST_INT_NONE   = 0,                   /*!< Master Interrupt None          */

    HRPWM_MST_INT_CMPA   = BIT(0),              /*!< Master Interrupt Compare A     */
    HRPWM_MST_INT_CMPB   = BIT(1),              /*!< Master Interrupt Compare B     */
    HRPWM_MST_INT_CMPC   = BIT(2),              /*!< Master Interrupt Compare C     */
    HRPWM_MST_INT_CMPD   = BIT(3),              /*!< Master Interrupt Compare D     */
    HRPWM_MST_INT_PRD    = BIT(4),              /*!< Master Interrupt Period        */
    HRPWM_MST_INT_SYNCIN = BIT(5),              /*!< Master Interrupt Sync In       */
    HRPWM_MST_INT_UPD    = BIT(6),              /*!< Master Interrupt Update        */
    HRPWM_MST_INT_RST    = BIT(7),              /*!< Master Interrupt Reset         */
    HRPWM_MST_INT_REP    = BIT(8),              /*!< Master Interrupt Repetition    */
} HRPWM_Mst_IntETypeDef;

/**
  * @brief HRPWM Master PWM DMA Definition
  */
typedef enum {
    HRPWM_MST_DMA_NONE   = 0,                   /*!< Master DMA None        */

    HRPWM_MST_DMA_CMPA   = BIT(16),             /*!< Master DMA Compare A   */
    HRPWM_MST_DMA_CMPB   = BIT(17),             /*!< Master DMA Compare B   */
    HRPWM_MST_DMA_CMPC   = BIT(18),             /*!< Master DMA Compare C   */
    HRPWM_MST_DMA_CMPD   = BIT(19),             /*!< Master DMA Compare D   */
    HRPWM_MST_DMA_PRD    = BIT(20),             /*!< Master DMA Period      */
    HRPWM_MST_DMA_SYNCIN = BIT(21),             /*!< Master DMA Sync In     */
    HRPWM_MST_DMA_UPD    = BIT(22),             /*!< Master DMA Update      */
    HRPWM_MST_DMA_RST    = BIT(23),             /*!< Master DMA Reset       */
    HRPWM_MST_DMA_REP    = BIT(24),             /*!< Master DMA Repetition  */
} HRPWM_Mst_DMAETypeDef;


/**
  * @brief HRPWM Slave PWM Interrupt Definition
  */
typedef enum {
    HRPWM_SLV_INT_NONE     = 0,                 /*!< Slave Interrupt None              */

    HRPWM_SLV_INT_CMPA     = BIT(0),            /*!< Slave Interrupt Compare A          */
    HRPWM_SLV_INT_CMPB     = BIT(1),            /*!< Slave Interrupt Compare B          */
    HRPWM_SLV_INT_CMPC     = BIT(2),            /*!< Slave Interrupt Compare C          */
    HRPWM_SLV_INT_CMPD     = BIT(3),            /*!< Slave Interrupt Compare D          */
    HRPWM_SLV_INT_PRD_RO   = BIT(4),            /*!< Slave Interrupt Period/Roll-Over   */
    HRPWM_SLV_INT_UPD      = BIT(5),            /*!< Slave Interrupt Update             */
    HRPWM_SLV_INT_OUTA_SET = BIT(6),            /*!< Slave Interrupt OutA Set           */
    HRPWM_SLV_INT_OUTA_CLR = BIT(7),            /*!< Slave Interrupt OutA Clear         */
    HRPWM_SLV_INT_OUTB_SET = BIT(8),            /*!< Slave Interrupt OutB Set           */
    HRPWM_SLV_INT_OUTB_CLR = BIT(9),            /*!< Slave Interrupt OutB Clear         */
    HRPWM_SLV_INT_RST      = BIT(10),           /*!< Slave Interrupt Reset              */
    HRPWM_SLV_INT_REP      = BIT(11),           /*!< Slave Interrupt Repetition         */
    HRPWM_SLV_INT_CAPA     = BIT(12),           /*!< Slave Interrupt Capture A          */
    HRPWM_SLV_INT_CAPB     = BIT(13),           /*!< Slave Interrupt Capture B          */
    HRPWM_SLV_INT_DLY_PROT = BIT(14),           /*!< Slave Interrupt Delay Protection   */
} HRPWM_Slv_IntETypeDef;

/**
  * @brief HRPWM Slave PWM DMA Definition
  */
typedef enum {
    HRPWM_SLV_DMA_NONE     = 0,                 /*!< Slave DMA None              */

    HRPWM_SLV_DMA_CMPA     = BIT(16),           /*!< Slave DMA Compare A          */
    HRPWM_SLV_DMA_CMPB     = BIT(17),           /*!< Slave DMA Compare B          */
    HRPWM_SLV_DMA_CMPC     = BIT(18),           /*!< Slave DMA Compare C          */
    HRPWM_SLV_DMA_CMPD     = BIT(19),           /*!< Slave DMA Compare D          */
    HRPWM_SLV_DMA_PRD_RO   = BIT(20),           /*!< Slave DMA Period/Roll-Over   */
    HRPWM_SLV_DMA_UPD      = BIT(21),           /*!< Slave DMA Update             */
    HRPWM_SLV_DMA_OUTA_SET = BIT(22),           /*!< Slave DMA OutA Set           */
    HRPWM_SLV_DMA_OUTA_CLR = BIT(23),           /*!< Slave DMA OutA Clear         */
    HRPWM_SLV_DMA_OUTB_SET = BIT(24),           /*!< Slave DMA OutB Set           */
    HRPWM_SLV_DMA_OUTB_CLR = BIT(25),           /*!< Slave DMA OutB Clear         */
    HRPWM_SLV_DMA_RST      = BIT(26),           /*!< Slave DMA Reset              */
    HRPWM_SLV_DMA_REP      = BIT(27),           /*!< Slave DMA Repetition         */
    HRPWM_SLV_DMA_CAPA     = BIT(28),           /*!< Slave DMA Capture A          */
    HRPWM_SLV_DMA_CAPB     = BIT(29),           /*!< Slave DMA Capture B          */
    HRPWM_SLV_DMA_DLY_PROT = BIT(30),           /*!< Slave DMA Delay Protection   */
} HRPWM_Slv_DMAETypeDef;

/**
  * @brief HRPWM Slave Update Gate Definition
  */
typedef enum {
    HRPWM_SLV_UPD_GATE_BST_DMA_INDEPEND = 0,    /*!< Slave Update Gate Burst DMA Done Independent                           */

    HRPWM_SLV_UPD_GATE_IN0_RISING = 2,          /*!< Slave Update Gate hrpwm_upd_in[0] Rising Egde                          */
    HRPWM_SLV_UPD_GATE_IN1_RISING,              /*!< Slave Update Gate hrpwm_upd_in[1] Rising Egde                          */
    HRPWM_SLV_UPD_GATE_IN2_RISING,              /*!< Slave Update Gate hrpwm_upd_in[2] Rising Egde                          */
    HRPWM_SLV_UPD_GATE_IN0_RISING_NEXT,         /*!< Slave Update Gate Next Update Event after hrpwm_upd_in[0] Rising Egde  */
    HRPWM_SLV_UPD_GATE_IN1_RISING_NEXT,         /*!< Slave Update Gate Next Update Event after hrpwm_upd_in[1] Rising Egde  */
    HRPWM_SLV_UPD_GATE_IN2_RISING_NEXT,         /*!< Slave Update Gate Next Update Event after hrpwm_upd_in[2] Rising Egde  */

    HRPWM_SLV_UPD_GATE_BST_DMA_DONE = 8,        /*!< Slave Update Gate Burst DMA Done Done                                  */
    HRPWM_SLV_UPD_GATE_BST_DMA_NEXT = 12,       /*!< Slave Update Gate Burst DMA Done Next Update Event                     */
} HRPWM_Slv_UpdGateETypeDef;

/**
  * @brief HRPWM Slave CMPD Auto Delayed Mode Definition
  */
typedef enum {
    HRPWM_SLV_CMPD_AUTO_DLY_ALWAYS = 0,         /*!< Slave CMPD Auto Delayd Mode Always             */
    HRPWM_SLV_CMPD_AUTO_DLY_AFTER_CAPB,         /*!< Slave CMPD Auto Delayd Mode After CAPB         */
    HRPWM_SLV_CMPD_AUTO_DLY_AFTER_CAPB_CMPA,    /*!< Slave CMPD Auto Delayd Mode After CAPB/CMPA    */
    HRPWM_SLV_CMPD_AUTO_DLY_AFTER_CAPB_CMPC,    /*!< Slave CMPD Auto Delayd Mode After CAPB/CMPC    */
} HRPWM_Slv_CmpDAutoDlyETypeDef;

/**
  * @brief HRPWM Slave CMPB Auto Delayed Mode Definition
  */
typedef enum {
    HRPWM_SLV_CMPB_AUTO_DLY_ALWAYS = 0,         /*!< Slave CMPB Auto Delayd Mode Always             */
    HRPWM_SLV_CMPB_AUTO_DLY_AFTER_CAPA,         /*!< Slave CMPB Auto Delayd Mode After CAPA         */
    HRPWM_SLV_CMPB_AUTO_DLY_AFTER_CAPA_CMPA,    /*!< Slave CMPB Auto Delayd Mode After CAPA/CMPA    */
    HRPWM_SLV_CMPB_AUTO_DLY_AFTER_CAPA_CMPC,    /*!< Slave CMPB Auto Delayd Mode After CAPA/CMPC    */
} HRPWM_Slv_CmpBAutoDlyETypeDef;

/**
  * @brief HRPWM Slave ReSync Mode Definition
  * @note  The functions are subject to the meanings expressed in the annotations
  */
typedef enum {
    HRPWM_SLV_RESYNC_NEXT_RST_ROLLOVER  = 0,    /*!< Slave ReSync Mode Immediately                          */
    HRPWM_SLV_RESYNC_IMDT               = 1,    /*!< Slave ReSync Mode Wait for Next Reset/Roll-Over Event  */
} HRPWM_Slv_ReSyncModeETypeDef;

/**
  * @brief HRPWM Slave Roll-Over Mode Definition
  */
typedef enum {
    HRPWM_SLV_ROLL_OVER_0_PERIOD = 0,           /*!< Slave Roll-Over Mode Generate at O/Period  */
    HRPWM_SLV_ROLL_OVER_0,                      /*!< Slave Roll-Over Mode Generate at O         */
    HRPWM_SLV_ROLL_OVER_PERIOD,                 /*!< Slave Roll-Over Mode Generate at Period    */
} HRPWM_Slv_RollOverModeETypeDef;

/**
  * @brief HRPWM Slave Capture Mode Definition
  */
typedef enum {
    HRPWM_SLV_CAP_MODE_NORMAL = 0,              /*!< Slave Capture Mode Normal  */
    HRPWM_SLV_CAP_MODE_TIMEOUT,                 /*!< Slave Capture Mode Timeout */
} HRPWM_Slv_CapModeETypeDef;

/**
  * @brief HRPWM Slave Direction Mode Definition
  */
typedef enum {
    HRPWM_SLV_DIR_UP = 0,                       /*!< Slave Direction Mode Up        */
    HRPWM_SLV_DIR_UP_DOWN,                      /*!< Slave Direction Mode Up-Down   */
} HRPWM_Slv_DirModeETypeDef;

/**
  * @brief HRPWM Slave DAC Reset Trigger Source Definition
  */
typedef enum {
    HRPWM_SLV_DAC_RST_TRIG_SRC_RST = 0,         /*!< Slave DAC Reset Trigger Source RST Event   */
    HRPWM_SLV_DAC_RST_TRIG_SRC_SETA,            /*!< Slave DAC Reset Trigger Source SETA Event  */
} HRPWM_Slv_DACRstTrigSrcETypeDef;

/**
  * @brief HRPWM Slave DAC Step Trigger Source Definition
  */
typedef enum {
    HRPWM_SLV_DAC_STEP_TRIG_SRC_CMPD = 0,       /*!< Slave DAC Step Trigger Source CMPD Event   */
    HRPWM_SLV_DAC_STEP_TRIG_SRC_CLRA,           /*!< Slave DAC Step Trigger Source CLRA Event   */
} HRPWM_Slv_DACStepTrigSrcETypeDef;

/**
  * @brief HRPWM Slave DeadTime Direction Definition
  */
typedef enum {
    HRPWM_SLV_DT_DIR_POSITIVE = 0,              /*!< Slave DeadTime Direction Positive  */
    HRPWM_SLV_DT_DIR_NEGATIVE,                  /*!< Slave DeadTime Direction Negative  */
} HRPWM_Slv_DtDirETypeDef;

/**
  * @brief HRPWM Slave Output Control Event Definition
  */
typedef enum {
    HRPWM_SLV_OUT_CTRL_EVT_NONE           = 0,              /*!< Slave Output Control Event None                    */

    HRPWM_SLV_OUT_CTRL_EVT_SW_TRIG        = BIT(0),         /*!< Slave Output Control Event Software Set Trigger    */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPA      = BIT(1),         /*!< Slave Output Control Event PWMx Compare A          */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPB      = BIT(2),         /*!< Slave Output Control Event PWMx Compare B          */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPC      = BIT(3),         /*!< Slave Output Control Event PWMx Compare C          */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_CMPD      = BIT(4),         /*!< Slave Output Control Event PWMx Compare D          */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_ROLL_OVER = BIT(5),         /*!< Slave Output Control Event PWMx Roll Over          */
    HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPA   = BIT(6),         /*!< Slave Output Control Event Master PWM Compare A    */
    HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPB   = BIT(7),         /*!< Slave Output Control Event Master PWM Compare B    */
    HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPC   = BIT(8),         /*!< Slave Output Control Event Master PWM Compare C    */
    HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_CMPD   = BIT(9),         /*!< Slave Output Control Event Master PWM Compare D    */
    HRPWM_SLV_OUT_CTRL_EVT_MST_PWM_PERIOD = BIT(10),        /*!< Slave Output Control Event Master PWM Period       */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT0      = BIT(11),        /*!< Slave Output Control Event PWMx Event 0            */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT1      = BIT(12),        /*!< Slave Output Control Event PWMx Event 1            */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT2      = BIT(13),        /*!< Slave Output Control Event PWMx Event 2            */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT3      = BIT(14),        /*!< Slave Output Control Event PWMx Event 3            */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT4      = BIT(15),        /*!< Slave Output Control Event PWMx Event 4            */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT5      = BIT(16),        /*!< Slave Output Control Event PWMx Event 5            */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT6      = BIT(17),        /*!< Slave Output Control Event PWMx Event 6            */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT7      = BIT(18),        /*!< Slave Output Control Event PWMx Event 7            */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT8      = BIT(19),        /*!< Slave Output Control Event PWMx Event 8            */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_EVT9      = BIT(20),        /*!< Slave Output Control Event PWMx Event 9            */
    HRPWM_SLV_OUT_CTRL_EVT_SYNC_INPUT_EVT = BIT(21),        /*!< Slave Output Control Event Sync Input Event        */
    HRPWM_SLV_OUT_CTRL_EVT_PWMx_UPDATE    = BIT(22),        /*!< Slave Output Control Event PWMx Update             */
} HRPWM_Slv_OutCtrlEvtETypeDef;

/**
  * @brief HRPWM Slave External Event Filter Definition
  */
typedef enum {
    //Filter Blank/Window Disable
    HRPWM_SLV_EXT_EVT_FIL_DIS = 0,              /*!< Slave External Event Filter Disable                                        */

    //Filter Blank
    HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPA,       /*!< Slave External Event Filter Blank from Reset/Roll-Over to Compare A        */
    HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPB,       /*!< Slave External Event Filter Blank from Reset/Roll-Over to Compare B        */
    HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPC,       /*!< Slave External Event Filter Blank from Reset/Roll-Over to Compare C        */
    HRPWM_SLV_EXT_EVT_FIL_BLK_RSTRO_CMPD,       /*!< Slave External Event Filter Blank from Reset/Roll-Over to Compare D        */
    HRPWM_SLV_EXT_EVT_FIL_BLK_UP_CMPA_CMPB,     /*!< Slave External Event Filter Blank from Up Compare A to Up Compare B        */
    HRPWM_SLV_EXT_EVT_FIL_BLK_UP_CMPC_CMPD,     /*!< Slave External Event Filter Blank from Up Compare C to Up Compare D        */
    HRPWM_SLV_EXT_EVT_FIL_BLK_DOWN_CMPA_CMPB,   /*!< Slave External Event Filter Blank from Down Compare A to Down Compare B    */
    HRPWM_SLV_EXT_EVT_FIL_BLK_DOWN_CMPC_CMPD,   /*!< Slave External Event Filter Blank from Down Compare C to Down Compare D    */

    //Filter Window
    HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPA,       /*!< Slave External Event Filter Window from Reset/Roll-Over to Compare A       */
    HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPB,       /*!< Slave External Event Filter Window from Reset/Roll-Over to Compare B       */
    HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPC,       /*!< Slave External Event Filter Window from Reset/Roll-Over to Compare C       */
    HRPWM_SLV_EXT_EVT_FIL_WIN_RSTRO_CMPD,       /*!< Slave External Event Filter Window from Reset/Roll-Over to Compare D       */
    HRPWM_SLV_EXT_EVT_FIL_WIN_UP_CMPB_CMPC,     /*!< Slave External Event Filter Window from Up Compare B to Up Compare C       */
    HRPWM_SLV_EXT_EVT_FIL_WIN_DOWN_CMPB_CMPC,   /*!< Slave External Event Filter Window from Dowm Compare B to Dowm Compare C   */
    HRPWM_SLV_EXT_EVT_FIL_WIN_UP_CMPB_DOWN_CMPC,/*!< Slave External Event Filter Window from Up Compare B to Down Compare C     */
} HRPWM_Slv_ExtEvtFilETypeDef;

/**
  * @brief HRPWM Slave External Event A Counter Reset Mode Definition
  */
typedef enum {
    HRPWM_SLV_EVTA_CNTR_RST_RSTRO_ALWAYS = 0,   /*!< Slave Event A Counter Reset at Reset/Roll-Over Event Always                */
    HRPWM_SLV_EVTA_CNTR_RST_RSTRO_LAST_NO_EVT,  /*!< Slave Event A Counter Reset at Reset/Roll-Over Event Only Last No Event    */
} HRPWM_Slv_EvtACntrRstModeETypeDef;

/**
  * @brief HRPWM Slave Chopper Start Pulse Width Definition
  */
typedef enum {
    HRPWM_SLV_PC_PULSE_WIDH_16 = 0,             /*!< HRPWM Slave Chopper Start Pulse Width 16   */
    HRPWM_SLV_PC_PULSE_WIDH_32,                 /*!< HRPWM Slave Chopper Start Pulse Width 32   */
    HRPWM_SLV_PC_PULSE_WIDH_48,                 /*!< HRPWM Slave Chopper Start Pulse Width 48   */
    HRPWM_SLV_PC_PULSE_WIDH_64,                 /*!< HRPWM Slave Chopper Start Pulse Width 64   */
    HRPWM_SLV_PC_PULSE_WIDH_80,                 /*!< HRPWM Slave Chopper Start Pulse Width 80   */
    HRPWM_SLV_PC_PULSE_WIDH_96,                 /*!< HRPWM Slave Chopper Start Pulse Width 96   */
    HRPWM_SLV_PC_PULSE_WIDH_112,                /*!< HRPWM Slave Chopper Start Pulse Width 112  */
    HRPWM_SLV_PC_PULSE_WIDH_128,                /*!< HRPWM Slave Chopper Start Pulse Width 128  */
    HRPWM_SLV_PC_PULSE_WIDH_144,                /*!< HRPWM Slave Chopper Start Pulse Width 144  */
    HRPWM_SLV_PC_PULSE_WIDH_160,                /*!< HRPWM Slave Chopper Start Pulse Width 160  */
    HRPWM_SLV_PC_PULSE_WIDH_176,                /*!< HRPWM Slave Chopper Start Pulse Width 176  */
    HRPWM_SLV_PC_PULSE_WIDH_192,                /*!< HRPWM Slave Chopper Start Pulse Width 192  */
    HRPWM_SLV_PC_PULSE_WIDH_208,                /*!< HRPWM Slave Chopper Start Pulse Width 208  */
    HRPWM_SLV_PC_PULSE_WIDH_224,                /*!< HRPWM Slave Chopper Start Pulse Width 224  */
    HRPWM_SLV_PC_PULSE_WIDH_240,                /*!< HRPWM Slave Chopper Start Pulse Width 240  */
    HRPWM_SLV_PC_PULSE_WIDH_256,                /*!< HRPWM Slave Chopper Start Pulse Width 256  */
} HRWPM_Slv_PC_PulseWidthETypeDef;

/**
  * @brief HRPWM Slave Chopper Duty Definition
  */
typedef enum {
    HRPWM_SLV_PC_DUTY_8_0 = 0,                  /*!< HRPWM Slave Chopper Duty 0/8   */
    HRPWM_SLV_PC_DUTY_8_1,                      /*!< HRPWM Slave Chopper Duty 1/8   */
    HRPWM_SLV_PC_DUTY_8_2,                      /*!< HRPWM Slave Chopper Duty 2/8   */
    HRPWM_SLV_PC_DUTY_8_3,                      /*!< HRPWM Slave Chopper Duty 3/8   */
    HRPWM_SLV_PC_DUTY_8_4,                      /*!< HRPWM Slave Chopper Duty 4/8   */
    HRPWM_SLV_PC_DUTY_8_5,                      /*!< HRPWM Slave Chopper Duty 5/8   */
    HRPWM_SLV_PC_DUTY_8_6,                      /*!< HRPWM Slave Chopper Duty 6/8   */
    HRPWM_SLV_PC_DUTY_8_7,                      /*!< HRPWM Slave Chopper Duty 7/8   */
} HRPWM_Slv_PC_DutyETypeDef;

/**
  * @brief HRPWM Slave Chopper Frequency Division Definition
  */
typedef enum {
    HRPWM_SLV_PC_FREQ_DIV_16 = 0,               /*!< HRPWM Slave Chopper Frequency Division 16  */
    HRPWM_SLV_PC_FREQ_DIV_32,                   /*!< HRPWM Slave Chopper Frequency Division 32  */
    HRPWM_SLV_PC_FREQ_DIV_48,                   /*!< HRPWM Slave Chopper Frequency Division 48  */
    HRPWM_SLV_PC_FREQ_DIV_64,                   /*!< HRPWM Slave Chopper Frequency Division 64  */
    HRPWM_SLV_PC_FREQ_DIV_80,                   /*!< HRPWM Slave Chopper Frequency Division 80  */
    HRPWM_SLV_PC_FREQ_DIV_96,                   /*!< HRPWM Slave Chopper Frequency Division 96  */
    HRPWM_SLV_PC_FREQ_DIV_112,                  /*!< HRPWM Slave Chopper Frequency Division 112 */
    HRPWM_SLV_PC_FREQ_DIV_128,                  /*!< HRPWM Slave Chopper Frequency Division 128 */
    HRPWM_SLV_PC_FREQ_DIV_144,                  /*!< HRPWM Slave Chopper Frequency Division 144 */
    HRPWM_SLV_PC_FREQ_DIV_160,                  /*!< HRPWM Slave Chopper Frequency Division 160 */
    HRPWM_SLV_PC_FREQ_DIV_176,                  /*!< HRPWM Slave Chopper Frequency Division 176 */
    HRPWM_SLV_PC_FREQ_DIV_192,                  /*!< HRPWM Slave Chopper Frequency Division 192 */
    HRPWM_SLV_PC_FREQ_DIV_208,                  /*!< HRPWM Slave Chopper Frequency Division 208 */
    HRPWM_SLV_PC_FREQ_DIV_224,                  /*!< HRPWM Slave Chopper Frequency Division 224 */
    HRPWM_SLV_PC_FREQ_DIV_240,                  /*!< HRPWM Slave Chopper Frequency Division 240 */
    HRPWM_SLV_PC_FREQ_DIV_256,                  /*!< HRPWM Slave Chopper Frequency Division 256 */
} HRPWM_Slv_PC_FreqDivETypeDef;

/**
  * @brief HRPWM Slave Delay Protection Mechanism Definition
  * @note  x = 6, y = 5 for PWM0~3; x = 8, y = 7 for PWM4~7
  */
typedef enum {
    HRPWM_SLV_DLY_PROT_MECH_OUTA_EVTy_IDLE = 0, /*!< Slave Delay Protection Mechanism OutA Delay Idle on Ext Event y        */
    HRPWM_SLV_DLY_PROT_MECH_OUTB_EVTy_IDLE,     /*!< Slave Delay Protection Mechanism OutB Delay Idle on Ext Event y        */
    HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTy_IDLE,    /*!< Slave Delay Protection Mechanism OutAB Delay Idle on Ext Event y       */
    HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTy_BAL,     /*!< Slave Delay Protection Mechanism OutAB Delay Balance on Ext Event y    */

    HRPWM_SLV_DLY_PROT_MECH_OUTA_EVTx_IDLE,     /*!< Slave Delay Protection Mechanism OutA Delay Idle on Ext Event x        */
    HRPWM_SLV_DLY_PROT_MECH_OUTB_EVTx_IDLE,     /*!< Slave Delay Protection Mechanism OutB Delay Idle on Ext Event x        */
    HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTx_IDLE,    /*!< Slave Delay Protection Mechanism OutAB Delay Idle on Ext Event x       */
    HRPWM_SLV_DLY_PROT_MECH_OUTAB_EVTx_BAL,     /*!< Slave Delay Protection Mechanism OutAB Delay Balance on Ext Event x    */
} HRPWM_Slv_DlyProtMechETypeDef;

/**
  * @brief HRPWM Slave Out Idle Status Level Definition
  */
typedef enum {
    HRPWM_SLV_OUT_IDLE_LVL_INVLD = 0,           /*!< Slave Out Idle Status Level Invalid    */
    HRPWM_SLV_OUT_IDLE_LVL_VLD,                 /*!< Slave Out Idle Status Level Valid      */
} HRPWM_Slv_OutIdleLvlETypeDef;

/**
  * @brief HRPWM Slave Out Fault Status Level Definition
  */
typedef enum {
    HRPWM_SLV_OUT_FAULT_LVL_NO_ACTION = 0,      /*!< Slave Out Fault Status Level No Action   */
    HRPWM_SLV_OUT_FAULT_LVL_VLD,                /*!< Slave Out Fault Status Level Valid     */
    HRPWM_SLV_OUT_FAULT_LVL_INVLD,              /*!< Slave Out Fault Status Level Invalid   */
    HRPWM_SLV_OUT_FAULT_LVL_HZ,                 /*!< Slave Out Fault Status Level High-Z    */
} HRPWM_Slv_OutFaultLvlETypeDef;

/**
  * @brief HRPWM Slave Out Polarity Definition
  */
typedef enum {
    HRPWM_SLV_OUT_POL_ACT_HITH = 0,             /*!< Slave Out Polarity Active High */
    HRPWM_SLV_OUT_POL_ACT_LOW,                  /*!< Slave Out Polarity Active Low  */
} HRPWM_Slv_OutPolETypeDef;


/**
  * @brief HRPWM Common ADC Trigger x Update Source Definition
  */
typedef enum {
    HRPWM_COMM_ADC_TRIG_UPD_SRC_MST_PWM = 0,    /*!< Common ADC Trigger x Update Source Master PWM  */
    HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM0,           /*!< Common ADC Trigger x Update Source PWM0        */
    HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM1,           /*!< Common ADC Trigger x Update Source PWM1        */
    HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM2,           /*!< Common ADC Trigger x Update Source PWM2        */
    HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM3,           /*!< Common ADC Trigger x Update Source PWM3        */
    HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM4,           /*!< Common ADC Trigger x Update Source PWM4        */
    HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM5,           /*!< Common ADC Trigger x Update Source PWM5        */
    HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM6,           /*!< Common ADC Trigger x Update Source PWM6        */
    HRPWM_COMM_ADC_TRIG_UPD_SRC_PWM7,           /*!< Common ADC Trigger x Update Source PWM7        */
} HRPWM_Comm_ADCTrigUpdSrcETypeDEF;

/**
  * @brief HRPWM Common ADC Trigger x Event Length Definition
  */
typedef enum {
    HRPWM_COMM_ADC_TRIG_EVT_LEN_16CLK = 0,      /*!< Common ADC Trigger x Event Length 16 hrpwm_clk    */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_15CLK,          /*!< Common ADC Trigger x Event Length 15 hrpwm_clk    */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_14CLK,          /*!< Common ADC Trigger x Event Length 14 hrpwm_clk    */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_13CLK,          /*!< Common ADC Trigger x Event Length 13 hrpwm_clk    */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_12CLK,          /*!< Common ADC Trigger x Event Length 12 hrpwm_clk    */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_11CLK,          /*!< Common ADC Trigger x Event Length 11 hrpwm_clk    */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_10CLK,          /*!< Common ADC Trigger x Event Length 10 hrpwm_clk    */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_9CLK,           /*!< Common ADC Trigger x Event Length 9 hrpwm_clk     */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_8CLK,           /*!< Common ADC Trigger x Event Length 8 hrpwm_clk     */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_7CLK,           /*!< Common ADC Trigger x Event Length 7 hrpwm_clk     */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_6CLK,           /*!< Common ADC Trigger x Event Length 6 hrpwm_clk     */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_5CLK,           /*!< Common ADC Trigger x Event Length 5 hrpwm_clk     */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_4CLK,           /*!< Common ADC Trigger x Event Length 4 hrpwm_clk     */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_3CLK,           /*!< Common ADC Trigger x Event Length 3 hrpwm_clk     */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_2CLK,           /*!< Common ADC Trigger x Event Length 2 hrpwm_clk     */
    HRPWM_COMM_ADC_TRIG_EVT_LEN_1CLK,           /*!< Common ADC Trigger x Event Length 1 hrpwm_clk     */
} HRPWM_Comm_ADCTrigEvtLenETypeDef;

/**
  * @brief HRPWM Common External Event Input Active Edge Definition
  */
typedef enum {
    HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_LVL = 0,  /*!< Common External Event Input Edge Active Level          */
    HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_RISING,   /*!< Common External Event Input Edge Active Rising         */
    HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_FALLING,  /*!< Common External Event Input Edge Active Falling        */
    HRPWM_COMM_EXT_EVT_INPUT_EDGE_ACT_BOTH,     /*!< Common External Event Input Edge Active Rising/Falling */
} HRPWM_Comm_ExtEvtInputEdgeETypeDef;

/**
  * @brief HRPWM Common External Event Input Polarity Definition
  */
typedef enum {
    HRPWM_COMM_EXT_EVT_INPUT_POL_ACT_HIGH = 0,  /*!< Common External Event Input Polarity Active High   */
    HRPWM_COMM_EXT_EVT_INPUT_POL_ACT_LOW,       /*!< Common External Event Input Polarity Active Low    */
} HRPWM_Comm_ExtEvtInputPolETypeDef;

/**
  * @brief HRPWM Common External Event X Input Source Definition
  */
typedef enum {
    HRPWM_COMM_EXT_EVT0_INPUT_SRC_HRPWM_EVT0 = 0,   /*!< Common External Event0 Input Source HRPWM_EVT0     */
    HRPWM_COMM_EXT_EVT0_INPUT_SRC_CMP1_OUT,         /*!< Common External Event0 Input Source CMP1_OUT       */
    HRPWM_COMM_EXT_EVT0_INPUT_SRC_TMR9_TRGO,        /*!< Common External Event0 Input Source TMR9_TRGO      */
    HRPWM_COMM_EXT_EVT0_INPUT_SRC_ADC0_AWD0,        /*!< Common External Event0 Input Source ADC0_AWD0      */

    HRPWM_COMM_EXT_EVT1_INPUT_SRC_HRPWM_EVT1 = 0,   /*!< Common External Event1 Input Source HRPWM_EVT1     */
    HRPWM_COMM_EXT_EVT1_INPUT_SRC_CMP3_OUT,         /*!< Common External Event1 Input Source CMP3_OUT       */
    HRPWM_COMM_EXT_EVT1_INPUT_SRC_TMR3_TRGO,        /*!< Common External Event1 Input Source TMR3_TRGO      */
    HRPWM_COMM_EXT_EVT1_INPUT_SRC_ADC0_AWD1,        /*!< Common External Event1 Input Source ADC0_AWD1      */

    HRPWM_COMM_EXT_EVT2_INPUT_SRC_HRPWM_EVT2 = 0,   /*!< Common External Event2 Input Source HRPWM_EVT2     */
    HRPWM_COMM_EXT_EVT2_INPUT_SRC_CMP5_OUT,         /*!< Common External Event2 Input Source CMP5_OUT       */
    HRPWM_COMM_EXT_EVT2_INPUT_SRC_TMR4_TRGO,        /*!< Common External Event2 Input Source TMR4_TRGO      */
    HRPWM_COMM_EXT_EVT2_INPUT_SRC_CMP7_OUT,         /*!< Common External Event2 Input Source CMP7_OUT       */

    HRPWM_COMM_EXT_EVT3_INPUT_SRC_HRPWM_EVT3 = 0,   /*!< Common External Event3 Input Source HRPWM_EVT3     */
    HRPWM_COMM_EXT_EVT3_INPUT_SRC_CMP0_OUT,         /*!< Common External Event3 Input Source CMP0_OUT       */
    HRPWM_COMM_EXT_EVT3_INPUT_SRC_CMP4_OUT,         /*!< Common External Event3 Input Source CMP4_OUT       */
    HRPWM_COMM_EXT_EVT3_INPUT_SRC_ADC1_AWD0,        /*!< Common External Event3 Input Source ADC1_AWD0      */

    HRPWM_COMM_EXT_EVT4_INPUT_SRC_HRPWM_EVT4 = 0,   /*!< Common External Event4 Input Source HRPWM_EVT4     */
    HRPWM_COMM_EXT_EVT4_INPUT_SRC_CMP2_OUT,         /*!< Common External Event4 Input Source CMP2_OUT       */
    HRPWM_COMM_EXT_EVT4_INPUT_SRC_CMP6_OUT,         /*!< Common External Event4 Input Source CMP6_OUT       */
    HRPWM_COMM_EXT_EVT4_INPUT_SRC_ADC1_AWD1,        /*!< Common External Event4 Input Source ADC1_AWD1      */

    HRPWM_COMM_EXT_EVT5_INPUT_SRC_HRPWM_EVT5 = 0,   /*!< Common External Event5 Input Source HRPWM_EVT5     */
    HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP1_OUT,         /*!< Common External Event5 Input Source CMP1_OUT       */
    HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP0_OUT,         /*!< Common External Event5 Input Source CMP0_OUT       */
    HRPWM_COMM_EXT_EVT5_INPUT_SRC_CMP8_OUT,         /*!< Common External Event5 Input Source CMP8_OUT       */

    HRPWM_COMM_EXT_EVT6_INPUT_SRC_HRPWM_EVT6 = 0,   /*!< Common External Event6 Input Source HRPWM_EVT6     */
    HRPWM_COMM_EXT_EVT6_INPUT_SRC_CMP3_OUT,         /*!< Common External Event6 Input Source CMP3_OUT       */
    HRPWM_COMM_EXT_EVT6_INPUT_SRC_TMR8_TRGO,        /*!< Common External Event6 Input Source TMR8_TRGO      */
    HRPWM_COMM_EXT_EVT6_INPUT_SRC_ADC2_AWD0,        /*!< Common External Event6 Input Source ADC2_AWD0      */

    HRPWM_COMM_EXT_EVT7_INPUT_SRC_HRPWM_EVT7 = 0,   /*!< Common External Event7 Input Source HRPWM_EVT7     */
    HRPWM_COMM_EXT_EVT7_INPUT_SRC_CMP5_OUT,         /*!< Common External Event7 Input Source CMP5_OUT       */
    HRPWM_COMM_EXT_EVT7_INPUT_SRC_CMP2_OUT,         /*!< Common External Event7 Input Source CMP2_OUT       */
    HRPWM_COMM_EXT_EVT7_INPUT_SRC_ADC3_AWD0,        /*!< Common External Event7 Input Source ADC3_AWD0      */

    HRPWM_COMM_EXT_EVT8_INPUT_SRC_HRPWM_EVT8 = 0,   /*!< Common External Event8 Input Source HRPWM_EVT8     */
    HRPWM_COMM_EXT_EVT8_INPUT_SRC_CMP4_OUT,         /*!< Common External Event8 Input Source CMP4_OUT       */
    HRPWM_COMM_EXT_EVT8_INPUT_SRC_TMR0_TRGO,        /*!< Common External Event8 Input Source TMR0_TRGO      */
    HRPWM_COMM_EXT_EVT8_INPUT_SRC_CMP3_OUT,         /*!< Common External Event8 Input Source CMP3_OUT       */

    HRPWM_COMM_EXT_EVT9_INPUT_SRC_HRPWM_EVT9 = 0,   /*!< Common External Event9 Input Source HRPWM_EVT9     */
    HRPWM_COMM_EXT_EVT9_INPUT_SRC_CMP6_OUT,         /*!< Common External Event9 Input Source CMP6_OUT       */
    HRPWM_COMM_EXT_EVT9_INPUT_SRC_TMR7_TRGO,        /*!< Common External Event9 Input Source TMR7_TRGO      */
    HRPWM_COMM_EXT_EVT9_INPUT_SRC_PDM0_CMPH,        /*!< Common External Event9 Input Source PDM0_CMPH      */

    HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT0 = 4,   /*!< External Event X Input Source HRPWM_EVT0           */
    HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT1,       /*!< External Event X Input Source HRPWM_EVT1           */
    HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT2,       /*!< External Event X Input Source HRPWM_EVT2           */
    HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT3,       /*!< External Event X Input Source HRPWM_EVT3           */
    HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT4,       /*!< External Event X Input Source HRPWM_EVT4           */
    HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT5,       /*!< External Event X Input Source HRPWM_EVT5           */
    HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT6,       /*!< External Event X Input Source HRPWM_EVT6           */
    HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT7,       /*!< External Event X Input Source HRPWM_EVT7           */
    HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT8,       /*!< External Event X Input Source HRPWM_EVT8           */
    HRPWM_COMM_EXT_EVTX_INPUT_SRC_HRPWM_EVT9,       /*!< External Event X Input Source HRPWM_EVT9           */
} HRPWM_Comm_ExtEvtXInputSrcETypeDef;

/**
  * @brief HRPWM Common External Event Sample Clock Division Definition
  */
typedef enum {
    HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_1 = 0,      /*!< Common External Event Sample Clock Division 1  */
    HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_2,          /*!< Common External Event Sample Clock Division 2  */
    HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_4,          /*!< Common External Event Sample Clock Division 4  */
    HRPWM_COMM_EXT_EVT_SAMP_CLK_DIV_8,          /*!< Common External Event Sample Clock Division 8  */
} HRPWM_Comm_ExtEvtSampClkDivETypeDef;

/**
  * @brief HRPWM Common ADC4/6/8 Trigger Event Source Definition
  */
typedef enum {
    HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPA = 0,    /*!< ADC4/6/8 Trigger Event Source Master PWM Compare A  */
    HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPB,        /*!< ADC4/6/8 Trigger Event Source Master PWM Compare B  */
    HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPC,        /*!< ADC4/6/8 Trigger Event Source Master PWM Compare C  */
    HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_CMPD,        /*!< ADC4/6/8 Trigger Event Source Master PWM Compare D  */
    HRPWM_COMM_ADC468_TRIG_EVT_MST_PWM_PRD,         /*!< ADC4/6/8 Trigger Event Source Master PWM Period     */

    HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_0,           /*!< ADC4/6/8 Trigger Event Source External Event 0      */
    HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_1,           /*!< ADC4/6/8 Trigger Event Source External Event 1      */
    HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_2,           /*!< ADC4/6/8 Trigger Event Source External Event 2      */
    HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_3,           /*!< ADC4/6/8 Trigger Event Source External Event 3      */
    HRPWM_COMM_ADC468_TRIG_EVT_EXT_EVT_4,           /*!< ADC4/6/8 Trigger Event Source External Event 4      */

    HRPWM_COMM_ADC468_TRIG_EVT_PWM0_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM0 Compare C        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM0_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM0 Compare D        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM0_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM0 Period           */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM0_RST_ROLLOVER,   /*!< ADC4/6/8 Trigger Event Source PWM0 Reset/Roll-Over  */

    HRPWM_COMM_ADC468_TRIG_EVT_PWM1_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM1 Compare C        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM1_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM1 Compare D        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM1_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM1 Period           */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM1_RST_ROLLOVE,    /*!< ADC4/6/8 Trigger Event Source PWM1 Reset/Roll-Over  */

    HRPWM_COMM_ADC468_TRIG_EVT_PWM2_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM2 Compare C        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM2_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM2 Compare D        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM2_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM2 Period           */

    HRPWM_COMM_ADC468_TRIG_EVT_PWM3_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM3 Compare C        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM3_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM3 Compare D        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM3_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM3 Period           */

    HRPWM_COMM_ADC468_TRIG_EVT_PWM4_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM4 Compare C        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM4_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM4 Compare D        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM4_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM4 Period           */

    HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPB,           /*!< ADC4/6/8 Trigger Event Source PWM5 Compare B        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM5 Compare C        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM5_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM5 Compare D        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM5_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM5 Period           */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM5_RST_ROLLOVER,   /*!< ADC4/6/8 Trigger Event Source PWM5 Reset/Roll-Over  */

    HRPWM_COMM_ADC468_TRIG_EVT_PWM6_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM6 Compare C        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM6_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM6 Compare D        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM6_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM6 Period           */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM6_RST_ROLLOVER,   /*!< ADC4/6/8 Trigger Event Source PWM6 Reset/Roll-Over  */

    HRPWM_COMM_ADC468_TRIG_EVT_PWM7_CMPC,           /*!< ADC4/6/8 Trigger Event Source PWM7 Compare C        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM7_CMPD,           /*!< ADC4/6/8 Trigger Event Source PWM7 Compare D        */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM7_PRD,            /*!< ADC4/6/8 Trigger Event Source PWM7 Period           */
    HRPWM_COMM_ADC468_TRIG_EVT_PWM7_RST_ROLLOVER,   /*!< ADC4/6/8 Trigger Event Source PWM7 Reset/Roll-Over  */
} HRPWM_Comm_ADC468TrigEvtSrcETypeDef;

/**
  * @brief HRPWM Common ADC5/7/9 Trigger Event Definition
  */
typedef enum {
    HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPA = 0,    /*!< ADC5/7/9 Trigger Event Source Master PWM Compare A   */
    HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPB,        /*!< ADC5/7/9 Trigger Event Source Master PWM Compare B   */
    HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPC,        /*!< ADC5/7/9 Trigger Event Source Master PWM Compare C   */
    HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_CMPD,        /*!< ADC5/7/9 Trigger Event Source Master PWM Compare D   */
    HRPWM_COMM_ADC579_TRIG_EVT_MST_PWM_PRD,         /*!< ADC5/7/9 Trigger Event Source Master PWM Period      */

    HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_5,           /*!< ADC5/7/9 Trigger Event Source External Event 5       */
    HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_6,           /*!< ADC5/7/9 Trigger Event Source External Event 6       */
    HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_7,           /*!< ADC5/7/9 Trigger Event Source External Event 7       */
    HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_8,           /*!< ADC5/7/9 Trigger Event Source External Event 8       */
    HRPWM_COMM_ADC579_TRIG_EVT_EXT_EVT_9,           /*!< ADC5/7/9 Trigger Event Source External Event 9       */

    HRPWM_COMM_ADC579_TRIG_EVT_PWM0_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM0 Compare B         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM0_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM0 Compare D         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM0_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM0 Period            */

    HRPWM_COMM_ADC579_TRIG_EVT_PWM1_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM1 Compare B         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM1_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM1 Compare D         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM1_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM1 Period            */

    HRPWM_COMM_ADC579_TRIG_EVT_PWM2_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM2 Compare B         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM2_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM2 Compare D         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM2_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM2 Period            */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM2_RST_ROLLOVER,   /*!< ADC5/7/9 Trigger Event Source PWM2 Reset/Roll-Over   */

    HRPWM_COMM_ADC579_TRIG_EVT_PWM3_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM3 Compare B         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM3_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM3 Compare D         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM3_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM3 Period            */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM3_RST_ROLLOVER,   /*!< ADC5/7/9 Trigger Event Source PWM3 Reset/Roll-Over   */

    HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM4 Compare B         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPC,           /*!< ADC5/7/9 Trigger Event Source PWM4 Compare C         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM4_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM4 Compare D         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM4_RST_ROLLOVER,   /*!< ADC5/7/9 Trigger Event Source PWM4 Reset/Roll-Over   */

    HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM5 Compare B         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPC,           /*!< ADC5/7/9 Trigger Event Source PWM5 Compare C         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM5_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM5 Compare D         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM5_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM5 Period            */

    HRPWM_COMM_ADC579_TRIG_EVT_PWM6_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM6 Compare B         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM6_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM6 Compare D         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM6_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM6 Period            */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM6_RST_ROLLOVER,   /*!< ADC5/7/9 Trigger Event Source PWM6 Reset/Roll-Over   */

    HRPWM_COMM_ADC579_TRIG_EVT_PWM7_CMPB,           /*!< ADC5/7/9 Trigger Event Source PWM7 Compare B         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM7_CMPD,           /*!< ADC5/7/9 Trigger Event Source PWM7 Compare D         */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM7_PRD,            /*!< ADC5/7/9 Trigger Event Source PWM7 Period            */
    HRPWM_COMM_ADC579_TRIG_EVT_PWM7_RST_ROLLOVER,   /*!< ADC5/7/9 Trigger Event Source PWM7 Reset/Roll-Over   */
} HRPWM_Comm_ADC579TrigEvtSrcETypeDef;

/**
  * @brief HRPWM Common DLL Current Definition
  */
typedef enum {
    HRPWM_COMM_DLL_CUR_4uA = 0,                 /*!< Common DLL Current 4uA */
    HRPWM_COMM_DLL_CUR_6uA,                     /*!< Common DLL Current 6uA */
    HRPWM_COMM_DLL_CUR_8uA = 3,                 /*!< Common DLL Current 8uA */
} HRPWM_Comm_DLLCurETypeDef;

/**
  * @brief HRPWM Common Fault X Input Source Definition
  */
typedef enum {
    HRPWM_COMM_FLT_INPUT_SRC_HRPWM_FLT = 0,     /*!< Common Fault Input Source HRPWM Fault          */
    HRPWM_COMM_FLT_INPUT_SRC_HRPWM_EVT = 2,     /*!< Common Fault Input Source HRPWM Event          */

    HRPWM_COMM_FLT0_INPUT_SRC_CMP1_OUT = 1,     /*!< Common Fault 0 Input Source HRPWM CMP 1 Out    */
    HRPWM_COMM_FLT1_INPUT_SRC_CMP3_OUT = 1,     /*!< Common Fault 1 Input Source HRPWM CMP 3 Out    */
    HRPWM_COMM_FLT2_INPUT_SRC_CMP5_OUT = 1,     /*!< Common Fault 2 Input Source HRPWM CMP 5 Out    */
    HRPWM_COMM_FLT3_INPUT_SRC_CMP0_OUT = 1,     /*!< Common Fault 3 Input Source HRPWM CMP 0 Out    */
    HRPWM_COMM_FLT4_INPUT_SRC_CMP2_OUT = 1,     /*!< Common Fault 4 Input Source HRPWM CMP 2 Out    */
    HRPWM_COMM_FLT5_INPUT_SRC_CMP4_OUT = 1,     /*!< Common Fault 5 Input Source HRPWM CMP 4 Out    */
    HRPWM_COMM_FLT6_INPUT_SRC_CMP7_OUT = 1,     /*!< Common Fault 6 Input Source HRPWM CMP 7 Out    */
    HRPWM_COMM_FLT7_INPUT_SRC_CMP8_OUT = 1,     /*!< Common Fault 7 Input Source HRPWM CMP 8 Out    */

#if 0
    HRPWM_COMM_FLT0_INPUT_SRC_HRPWM_FLT0 = 0,   /*!< Common Fault 0 Input Source HRPWM Fault 0      */
    HRPWM_COMM_FLT0_INPUT_SRC_CMP1_OUT,         /*!< Common Fault 0 Input Source HRPWM CMP 1 Out    */
    HRPWM_COMM_FLT0_INPUT_SRC_HRPWM_EVT0,       /*!< Common Fault 0 Input Source HRPWM Event 0      */

    HRPWM_COMM_FLT1_INPUT_SRC_HRPWM_FLT1 = 0,   /*!< Common Fault 1 Input Source HRPWM Fault 1      */
    HRPWM_COMM_FLT1_INPUT_SRC_CMP3_OUT,         /*!< Common Fault 1 Input Source HRPWM CMP 3 Out    */
    HRPWM_COMM_FLT1_INPUT_SRC_HRPWM_EVT1,       /*!< Common Fault 1 Input Source HRPWM Event 1      */

    HRPWM_COMM_FLT2_INPUT_SRC_HRPWM_FLT2 = 0,   /*!< Common Fault 2 Input Source HRPWM Fault 2      */
    HRPWM_COMM_FLT2_INPUT_SRC_CMP5_OUT,         /*!< Common Fault 2 Input Source HRPWM CMP 5 Out    */
    HRPWM_COMM_FLT2_INPUT_SRC_HRPWM_EVT2,       /*!< Common Fault 2 Input Source HRPWM Event 2      */

    HRPWM_COMM_FLT3_INPUT_SRC_HRPWM_FLT3 = 0,   /*!< Common Fault 3 Input Source HRPWM Fault 3      */
    HRPWM_COMM_FLT3_INPUT_SRC_CMP0_OUT,         /*!< Common Fault 3 Input Source HRPWM CMP 0 Out    */
    HRPWM_COMM_FLT3_INPUT_SRC_HRPWM_EVT3,       /*!< Common Fault 3 Input Source HRPWM Event 3      */

    HRPWM_COMM_FLT4_INPUT_SRC_HRPWM_FLT4 = 0,   /*!< Common Fault 4 Input Source HRPWM Fault 4      */
    HRPWM_COMM_FLT4_INPUT_SRC_CMP2_OUT,         /*!< Common Fault 4 Input Source HRPWM CMP 2 Out    */
    HRPWM_COMM_FLT4_INPUT_SRC_HRPWM_EVT4,       /*!< Common Fault 4 Input Source HRPWM Event 4      */

    HRPWM_COMM_FLT5_INPUT_SRC_HRPWM_FLT5 = 0,   /*!< Common Fault 5 Input Source HRPWM Fault 5      */
    HRPWM_COMM_FLT5_INPUT_SRC_CMP4_OUT,         /*!< Common Fault 5 Input Source HRPWM CMP 4 Out    */
    HRPWM_COMM_FLT5_INPUT_SRC_HRPWM_EVT5,       /*!< Common Fault 5 Input Source HRPWM Event 5      */

    HRPWM_COMM_FLT6_INPUT_SRC_HRPWM_FLT6 = 0,   /*!< Common Fault 6 Input Source HRPWM Fault 6      */
    HRPWM_COMM_FLT6_INPUT_SRC_CMP7_OUT,         /*!< Common Fault 6 Input Source HRPWM CMP 7 Out    */
    HRPWM_COMM_FLT6_INPUT_SRC_HRPWM_EVT6,       /*!< Common Fault 6 Input Source HRPWM Event 6      */

    HRPWM_COMM_FLT7_INPUT_SRC_HRPWM_FLT7 = 0,   /*!< Common Fault 7 Input Source HRPWM Fault 7      */
    HRPWM_COMM_FLT7_INPUT_SRC_CMP8_OUT,         /*!< Common Fault 7 Input Source HRPWM CMP 8 Out    */
    HRPWM_COMM_FLT7_INPUT_SRC_HRPWM_EVT7,       /*!< Common Fault 7 Input Source HRPWM Event 7      */
#endif
} HRPWM_Comm_FltXInputSrcETypeDef;

/**
  * @brief HRPWM Common Fault x Input Polarity Definition
  */
typedef enum {
    HRPWM_COMM_FLT_INPUT_POL_ACT_HIGH = 0,      /*!< Common Fault x Input Polarity Active High  */
    HRPWM_COMM_FLT_INPUT_POL_ACT_LOW,           /*!< Common Fault x Input Polarity Active Low   */
} HRPWM_Comm_FltInputPolETypeDef;

/**
  * @brief HRPWM Common Fault Sample Clock Division Definition
  */
typedef enum {
    HRPWM_COMM_FLT_SAMP_CLK_DIV_1 = 0,          /*!< Common Fault Sample Clock Division 1   */
    HRPWM_COMM_FLT_SAMP_CLK_DIV_2,              /*!< Common Fault Sample Clock Division 2   */
    HRPWM_COMM_FLT_SAMP_CLK_DIV_4,              /*!< Common Fault Sample Clock Division 4   */
    HRPWM_COMM_FLT_SAMP_CLK_DIV_8,              /*!< Common Fault Sample Clock Division 8   */
} HRPWM_Comm_FltSampClkDivETypeDef;

/**
  * @brief HRPWM Common Fault X Blank Source Definition
  */
typedef enum {
    HRPWM_COMM_FLT_BLK_SRC_FIXED_WIN = 0,       /*!< Common Fault X Blank Source Fixed Window   */
    HRPWM_COMM_FLT_BLK_SRC_MOVED_WIN,           /*!< Common Fault X Blank Source Moved Window   */
} HRPWM_Comm_FltBlkSrcETypeDef;

/**
  * @brief HRPWM Common Fault X Counter Reset Mode Definition
  */
typedef enum {
    HRPWM_COMM_FLT_CNTR_RST_RSTRO_ALWAYS = 0,   /*!< Common Fault Counter Reset at Reset/Roll-Over Event Always             */
    HRPWM_COMM_FLT_CNTR_RST_RSTRO_LAST_NO_EVT,  /*!< Common Fault Counter Reset at Reset/Roll-Over Event Only Last No Event */
} HRPWM_Comm_FltCntrRstModeETypeDef;

/**
  * @brief HRPWM Common Burst Mode Clock Prescaler Definition
  */
typedef enum {
    HRPWM_COMM_BURST_CLK_PRESCL_1 = 0,          /*!< Common Burst Mode Clock Prescaler 1        */
    HRPWM_COMM_BURST_CLK_PRESCL_2,              /*!< Common Burst Mode Clock Prescaler 2        */
    HRPWM_COMM_BURST_CLK_PRESCL_4,              /*!< Common Burst Mode Clock Prescaler 4        */
    HRPWM_COMM_BURST_CLK_PRESCL_8,              /*!< Common Burst Mode Clock Prescaler 8        */
    HRPWM_COMM_BURST_CLK_PRESCL_16,             /*!< Common Burst Mode Clock Prescaler 16       */
    HRPWM_COMM_BURST_CLK_PRESCL_32,             /*!< Common Burst Mode Clock Prescaler 32       */
    HRPWM_COMM_BURST_CLK_PRESCL_64,             /*!< Common Burst Mode Clock Prescaler 64       */
    HRPWM_COMM_BURST_CLK_PRESCL_128,            /*!< Common Burst Mode Clock Prescaler 128      */
    HRPWM_COMM_BURST_CLK_PRESCL_256,            /*!< Common Burst Mode Clock Prescaler 256      */
    HRPWM_COMM_BURST_CLK_PRESCL_512,            /*!< Common Burst Mode Clock Prescaler 512      */
    HRPWM_COMM_BURST_CLK_PRESCL_1024,           /*!< Common Burst Mode Clock Prescaler 1024     */
    HRPWM_COMM_BURST_CLK_PRESCL_2048,           /*!< Common Burst Mode Clock Prescaler 2048     */
    HRPWM_COMM_BURST_CLK_PRESCL_4096,           /*!< Common Burst Mode Clock Prescaler 4096     */
    HRPWM_COMM_BURST_CLK_PRESCL_8192,           /*!< Common Burst Mode Clock Prescaler 8192     */
    HRPWM_COMM_BURST_CLK_PRESCL_16384,          /*!< Common Burst Mode Clock Prescaler 16384    */
    HRPWM_COMM_BURST_CLK_PRESCL_32768,          /*!< Common Burst Mode Clock Prescaler 32768    */
} HRPWM_Comm_BurstClkPresclETypeDef;

/**
  * @brief HRPWM Common Burst Mode Trigger Mode Definition
  */
typedef enum {
    HRPWM_COMM_BURST_TRIG_MODE_ASYNC = 0,       /*!< Common Burst Mode Asynchronous Trigger Mode */
    HRPWM_COMM_BURST_TRIG_MODE_SYNC,            /*!< Common Burst Mode Synchronous Trigger Mode  */
} HRPWM_Comm_BurstTrigModeETypeDef;

/**
  * @brief HRPWM Common Burst Mode Clock Source Definition
  */
typedef enum {
    HRPWM_COMM_BURST_CLK_SRC_MST_PWM_RST_ROLLOVER = 0,  /*!< Common Burst Mode Clock Source Master PWM Reset/Roll-Over  */

    HRPWM_COMM_BURST_CLK_SRC_PWM0_RST_ROLLOVER,         /*!< Common Burst Mode Clock Source PWM0 Reset/Roll-Over        */
    HRPWM_COMM_BURST_CLK_SRC_PWM1_RST_ROLLOVER,         /*!< Common Burst Mode Clock Source PWM1 Reset/Roll-Over        */
    HRPWM_COMM_BURST_CLK_SRC_PWM2_RST_ROLLOVER,         /*!< Common Burst Mode Clock Source PWM2 Reset/Roll-Over        */
    HRPWM_COMM_BURST_CLK_SRC_PWM3_RST_ROLLOVER,         /*!< Common Burst Mode Clock Source PWM3 Reset/Roll-Over        */
    HRPWM_COMM_BURST_CLK_SRC_PWM4_RST_ROLLOVER,         /*!< Common Burst Mode Clock Source PWM4 Reset/Roll-Over        */
    HRPWM_COMM_BURST_CLK_SRC_PWM5_RST_ROLLOVER,         /*!< Common Burst Mode Clock Source PWM5 Reset/Roll-Over        */
    HRPWM_COMM_BURST_CLK_SRC_PWM6_RST_ROLLOVER,         /*!< Common Burst Mode Clock Source PWM6 Reset/Roll-Over        */
    HRPWM_COMM_BURST_CLK_SRC_PWM7_RST_ROLLOVER,         /*!< Common Burst Mode Clock Source PWM7 Reset/Roll-Over        */

    HRPWM_COMM_BURST_CLK_SRC_HRPWM_BM_IN0 = 12,         /*!< Common Burst Mode Clock Source hrpwm_bm_in0                */
    HRPWM_COMM_BURST_CLK_SRC_HRPWM_BM_IN1,              /*!< Common Burst Mode Clock Source hrpwm_bm_in1                */
    HRPWM_COMM_BURST_CLK_SRC_HRPWM_BM_IN2,              /*!< Common Burst Mode Clock Source hrpwm_bm_in2                */
    HRPWM_COMM_BURST_CLK_SRC_HRPWM_FUNC_CLK,            /*!< Common Burst Mode Clock Source HRPWM Function Clock        */
} HRPWM_Comm_BurstClkSrcETypeDef;

/**
  * @brief HRPWM Common Burst DMA Master PWM Register Update Definition
  */
typedef enum {
    HRPWM_COMM_BURST_DMA_MST_REG_UPD_NONE   = 0,        /*!< Common Burst DMA Master PWM Register Update None   */

    HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCR0   = BIT(0),   /*!< Common Burst DMA Master PWM Register Update MCR0   */
    HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCR1   = BIT(1),   /*!< Common Burst DMA Master PWM Register Update MCR1   */
    HRPWM_COMM_BURST_DMA_MST_REG_UPD_MISR   = BIT(2),   /*!< Common Burst DMA Master PWM Register Update MISR   */
    HRPWM_COMM_BURST_DMA_MST_REG_UPD_MDIER  = BIT(3),   /*!< Common Burst DMA Master PWM Register Update MDIER  */
    HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCNTR  = BIT(4),   /*!< Common Burst DMA Master PWM Register Update MCNTR  */
    HRPWM_COMM_BURST_DMA_MST_REG_UPD_MPER   = BIT(5),   /*!< Common Burst DMA Master PWM Register Update MPER   */
    HRPWM_COMM_BURST_DMA_MST_REG_UPD_MREP   = BIT(6),   /*!< Common Burst DMA Master PWM Register Update MREP   */
    HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCMPAR = BIT(7),   /*!< Common Burst DMA Master PWM Register Update MCMPAR */
    HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCMPBR = BIT(8),   /*!< Common Burst DMA Master PWM Register Update MCMPBR */
    HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCMPCR = BIT(9),   /*!< Common Burst DMA Master PWM Register Update MCMPCR */
    HRPWM_COMM_BURST_DMA_MST_REG_UPD_MCMPDR = BIT(10),  /*!< Common Burst DMA Master PWM Register Update MCMPDR */

    HRPWM_COMM_BURST_DMA_MST_REG_UPD_ALL    = 0x7FF,    /*!< Common Burst DMA Master PWM Register Update All    */
} HRPWM_Comm_BurstDMAMstRegUpdETypeDef;

/**
  * @brief HRPWM Common Burst DMA Slave PWMx Register Update Definition
  */
typedef enum {
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_NONE    = 0,       /*!< Common Burst DMA Slave PWM Register Update None    */

    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CR0     = BIT(0),  /*!< Common Burst DMA Slave PWM Register Update CR0     */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CR1     = BIT(1),  /*!< Common Burst DMA Slave PWM Register Update CR1     */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_ISR     = BIT(2),  /*!< Common Burst DMA Slave PWM Register Update ISR     */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_DIER    = BIT(3),  /*!< Common Burst DMA Slave PWM Register Update DIER    */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CNTR    = BIT(4),  /*!< Common Burst DMA Slave PWM Register Update CNTR    */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_PERR    = BIT(5),  /*!< Common Burst DMA Slave PWM Register Update PERR    */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_REPR    = BIT(6),  /*!< Common Burst DMA Slave PWM Register Update REPR    */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CMPAR   = BIT(7),  /*!< Common Burst DMA Slave PWM Register Update CMPAR   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CMPBR   = BIT(8),  /*!< Common Burst DMA Slave PWM Register Update CMPBR   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CMPCR   = BIT(9),  /*!< Common Burst DMA Slave PWM Register Update CMPCR   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CMPDR   = BIT(10), /*!< Common Burst DMA Slave PWM Register Update CMPDR   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPAR   = BIT(11), /*!< Common Burst DMA Slave PWM Register Update CAPAR   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPBR   = BIT(12), /*!< Common Burst DMA Slave PWM Register Update CAPBR   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_DTR     = BIT(13), /*!< Common Burst DMA Slave PWM Register Update DTR     */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_SETAR   = BIT(14), /*!< Common Burst DMA Slave PWM Register Update SETAR   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CLRAR   = BIT(15), /*!< Common Burst DMA Slave PWM Register Update CLRAR   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_SETBR   = BIT(16), /*!< Common Burst DMA Slave PWM Register Update SETBR   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CLRBR   = BIT(17), /*!< Common Burst DMA Slave PWM Register Update CLRBR   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_EEFR0   = BIT(18), /*!< Common Burst DMA Slave PWM Register Update EEFR0   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_EEFR1   = BIT(19), /*!< Common Burst DMA Slave PWM Register Update EEFR1   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_EEFR2   = BIT(20), /*!< Common Burst DMA Slave PWM Register Update EEFR2   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_RSTR    = BIT(21), /*!< Common Burst DMA Slave PWM Register Update RSTR    */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_RSTER   = BIT(22), /*!< Common Burst DMA Slave PWM Register Update RSTER   */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CHPR    = BIT(23), /*!< Common Burst DMA Slave PWM Register Update CHPR    */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPACR  = BIT(24), /*!< Common Burst DMA Slave PWM Register Update CAPACR  */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPACER = BIT(25), /*!< Common Burst DMA Slave PWM Register Update CAPACER */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPBCR  = BIT(26), /*!< Common Burst DMA Slave PWM Register Update CAPBCR  */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_CAPBCER = BIT(27), /*!< Common Burst DMA Slave PWM Register Update CAPBCER */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_OUTR    = BIT(28), /*!< Common Burst DMA Slave PWM Register Update OUTR    */
    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_FLTR    = BIT(29), /*!< Common Burst DMA Slave PWM Register Update FLTR    */

    HRPWM_COMM_BURST_DMA_SLV_REG_UPD_ALL     = 0x3FFFFFFF, /*!< Common Burst DMA Slave PWM Register Update All  */
} HRPWM_Comm_BurstDMASlvRegUpdETypeDef;


/**
  * @brief HRPWM Master Sync Config Structure Definition
  */
typedef struct __HRPWM_Mst_SyncCfgTypeDef {
    HRPWM_Mst_SyncModeETypeDef mode;                    /*!< Master Sync Mode               */

    //Sync Master Config
    HRPWM_Mst_SyncOutSrcETypeDef out_src;               /*!< Master Sync Output Source      */
    HRPWM_Mst_SyncOutPolETypeDef out_pol;               /*!< Master Sync Output Polarity    */

    //Sync Slave Config
    HRPWM_Mst_SyncInSrcETypeDef in_src;                 /*!< Master Sync Input Source       */
} HRPWM_Mst_SyncCfgTypeDef;


/**
  * @brief HRPWM Master/Slave Timer Base Config Structure Definition
  * @note  int_en_msk   is Combination of HRPWM_Mst_IntETypeDef/HRPWM_Slv_IntETypeDef
  *        dma_en_msk   is Combination of HRPWM_Mst_DMAETypeDef/HRPWM_Slv_DMAETypeDef
  *        cntr_rst_evt is Combination of HRPWM_SlvX_CntrRstEvtETypeDef (X = 0 ~ HRPWM_SLV_PWM_NUMS-1)
  */
typedef struct __HRPWM_TmrBaseCfgTypeDef {
    //Master Config
    HRPWM_Mst_UpdGateETypeDef mst_upd_gate;             /*!< Master PWM Update Gate         */

    //Master/Slave Common Config
    bool sync_start_en;                                 /*!< Start on Sync Input Enable     */
    bool sync_rst_en;                                   /*!< Reset on Sync Input Enable     */
    bool single_retrig_en;                              /*!< Single Mode ReTrigger Enalbe   */
    bool burst_cnt_stop_en;                             /*!< Burst Mode Counter Stop Enable */
    uint8_t  rep_prd;                                   /*!< Repetition Period              */
    uint16_t cntr_prd;                                  /*!< Counter Period                 */
    uint32_t int_en_msk;                                /*!< Interrutp Enable Mask          */
    uint32_t dma_en_msk;                                /*!< DMA Enable Mask                */
    HRPWM_ClkPresclETypeDef clk_prescl;                 /*!< Clock Prescaler                */
    HRPWM_WorkModeETypeDef  work_mode;                  /*!< Work Mode: Single/Continue     */

    bool half_mode_en;                                  /*!< PWM Half Mode Enable           */
    HRPWM_IntlvdModeETypeDef intlvd_mode;               /*!< PWM Interleaved Mode           */

    //Slave Config
    uint64_t cntr_rst_evt;                              /*!< Slave Counter Reset Event      */
    HRPWM_Slv_ReSyncModeETypeDef resync_mode;           /*!< Slave ReSync Mode              */

    bool push_pull_en;                                  /*!< Push-pull Mode Enable          */
    bool trig_half_en;                                  /*!< Trigger Half Mode Enable       */
    bool cmpA_greatr_than_en;                           /*!< Cmp A Greater Than mode Enable */
    bool cmpC_greatr_than_en;                           /*!< Cmp C Greater Than mode Enable */
    HRPWM_Slv_UpdGateETypeDef upd_gate;                 /*!< PWM Update Gate                */
    HRPWM_Slv_CmpBAutoDlyETypeDef cmpB_auto_dly_mode;   /*!< Cmp B Auto Delay Mode          */
    HRPWM_Slv_CmpDAutoDlyETypeDef cmpD_auto_dly_mode;   /*!< Cmp D Auto Delay Mode          */
} HRPWM_TmrBaseCfgTypeDef;

/**
  * @brief HRPWM Master/Slave Timer Compare Config Structure Definition
  */
typedef struct __HRPWM_TmrCmpCfgTypeDef {
    //Master/Slave Common Config
    bool pre_load_en;                                   /*!< Preload Enable         */
    uint16_t cmp_a_val;                                 /*!< Compare A Value        */
    uint16_t cmp_b_val;                                 /*!< Compare B Value        */
    uint16_t cmp_c_val;                                 /*!< Compare C Value        */
    uint16_t cmp_d_val;                                 /*!< Compare D Value        */

    bool rep_upd_en;                                    /*!< Repetition Event Trigger Update Enable         */
    bool rst_ro_upd_en;                                 /*!< Reset/Roll-Over Event Trigger Update Enable    */

    //Slave Config
    bool mst_pwm_upd_en;                                /*!< Master PWM Update Event Trigger Update Enable  */
    bool pwm0_upd_en;                                   /*!< PWM0 Update Event Trigger Update Enable        */
    bool pwm1_upd_en;                                   /*!< PWM1 Update Event Trigger Update Enable        */
    bool pwm2_upd_en;                                   /*!< PWM2 Update Event Trigger Update Enable        */
    bool pwm3_upd_en;                                   /*!< PWM3 Update Event Trigger Update Enable        */
    bool pwm4_upd_en;                                   /*!< PWM4 Update Event Trigger Update Enable        */
    bool pwm5_upd_en;                                   /*!< PWM5 Update Event Trigger Update Enable        */
    bool pwm6_upd_en;                                   /*!< PWM6 Update Event Trigger Update Enable        */
    bool pwm7_upd_en;                                   /*!< PWM7 Update Event Trigger Update Enable        */
} HRPWM_TmrCmpCfgTypeDef;

/**
  * @brief HRPWM Master/Slave DAC Trigger Config Structure Definition
  */
typedef struct __HRPWM_DACTrigCfgTypeDef {
    //Master/Slave Common Config
    HRPWM_DACSyncSrcETypeDef sync_src;                  /*!< DAC Trigger Sync Source    */

    //Slave Config
    bool trig_en;                                       /*!< DAC Trigger Enable         */
    HRPWM_Slv_DACRstTrigSrcETypeDef  rst_trig_src;      /*!< DAC Reset Trigger Source   */
    HRPWM_Slv_DACStepTrigSrcETypeDef step_trig_src;     /*!< DAC Step Trigger Source    */
} HRPWM_DACTrigCfgTypeDef;

/**
  * @brief HRPWM Master/Slave System DMA Config Structure Definition
  */
typedef struct __HRPWM_SysDMACfgTypeDef {
    bool write_upd_en;                                  /*!< System DMA Write Register Data Enable            */
    uint32_t sys_dma_buf_addr;                          /*!< System DMA Write Register Data Buff Address      */
    uint32_t sys_dma_buf_size;                          /*!< System DMA Write Register Data Buff Size (Bytes) */
    HRPWM_Comm_BurstDMAMstRegUpdETypeDef mst_reg_upd;   /*!< System DMA Updata Master Register Type           */
    HRPWM_Comm_BurstDMASlvRegUpdETypeDef slv_reg_upd;   /*!< System DMA Updata Slave Register Type            */
} HRPWM_SysDMACfgTypeDef;


/**
  * @brief HRPWM Slave Timer Roll-Over Config Structure Definition
  */
typedef struct __HRPWM_Slv_TmrRollOverCfgTypeDef {
    HRPWM_Slv_DirModeETypeDef      dir_mode;            /*!< Timer Counter Direction Mode   */

    HRPWM_Slv_RollOverModeETypeDef cntr_ro_mode;        /*!< Timer Counter Roll-Over Mode   */
    HRPWM_Slv_RollOverModeETypeDef out_ro_mode;         /*!< Output Roll-Over Mode          */
    HRPWM_Slv_RollOverModeETypeDef adc_ro_mode;         /*!< ADC Roll-Over Mode             */
    HRPWM_Slv_RollOverModeETypeDef evt_ro_mode;         /*!< Event Roll-Over Mode           */
    HRPWM_Slv_RollOverModeETypeDef flt_ro_mode;         /*!< Fault Roll-Over Mode           */
} HRPWM_Slv_TmrRollOverCfgTypeDef;

/**
  * @brief HRPWM Slave Timer Event Filter Config Structure Definition
  */
typedef struct __HRPWM_Slv_TmrEvtFilCfgTypeDef {
    bool blk_latch_en;                                  /*!< Event Blank Latch Enable   */
    HRPWM_Slv_ExtEvtFilETypeDef fil;                    /*!< Event Filter               */
} HRPWM_Slv_TmrEvtFilCfgTypeDef;

/**
  * @brief HRPWM Slave Timer Event A Config Structure Definition
  */
typedef struct __HRPWM_Slv_TmrEvtACfgTypeDef {
    bool enable;                                        /*!< Event A Enable             */

    uint8_t thres;                                      /*!< Event A Threshold          */
    HRPWM_ExtEvtNumETypeDef src;                        /*!< Event A Source             */
    HRPWM_Slv_EvtACntrRstModeETypeDef rst_mode;         /*!< Event A Counter Reset Mode */
} HRPWM_Slv_TmrEvtACfgTypeDef;

/**
  * @brief HRPWM Slave Output Config Structure Definition
  * @note  Xout_set_evt_msk/Xout_clr_evt_msk is combination of HRPWM_Slv_OutCtrlEvtETypeDef
  */
typedef struct __HRPWM_Slv_OutputCfgTypeDef {
    //Common Config
    bool flt_en[HRPWM_FLT_NUMS];                        /*!< Output Fault Enable                */
    bool swap_en;                                       /*!< Output Swap Enable                 */
    bool dly_prot_en;                                   /*!< Delay Protect Enable               */
    bool bal_idle_auto_rcvr_en;                         /*!< Balance Idle Auto Recover Enable   */
    HRPWM_Slv_DlyProtMechETypeDef dly_prot_mode;        /*!< Delay Protect Mode                 */

    //OutA Config
    bool     Aidle_deadtime_en;                         /*!< OutA Idle DeadTime Enable      */
    bool     Aburst_idle_en;                            /*!< OutA Burst Mode Idle Enable    */
    uint32_t Aout_set_evt_msk;                          /*!< OutA Set Event Mask            */
    uint32_t Aout_clr_evt_msk;                          /*!< OutA Clear Event Mask          */
    HRPWM_Slv_OutPolETypeDef      Aout_pol;             /*!< OutA Polarity                  */
    HRPWM_Slv_OutIdleLvlETypeDef  Aout_idle_lvl;        /*!< OutA Idle Level                */
    HRPWM_Slv_OutFaultLvlETypeDef Aout_flt_lvl;         /*!< OutA Fault Level               */

    //OutB Config
    bool     Bidle_deadtime_en;                         /*!< OutB Idle DeadTime Enable      */
    bool     Bburst_idle_en;                            /*!< OutB Burst Mode Idle Enable    */
    uint32_t Bout_set_evt_msk;                          /*!< OutB Set Event Mask            */
    uint32_t Bout_clr_evt_msk;                          /*!< OutB Clear Event Mask          */
    HRPWM_Slv_OutPolETypeDef      Bout_pol;             /*!< OutB Polarity                  */
    HRPWM_Slv_OutIdleLvlETypeDef  Bout_idle_lvl;        /*!< OutB Idle Level                */
    HRPWM_Slv_OutFaultLvlETypeDef Bout_flt_lvl;         /*!< OutB Fault Level               */
} HRPWM_Slv_OutputCfgTypeDef;

/**
  * @brief HRPWM Slave Dead Time Config Structure Definition
  */
typedef struct __HRPWM_Slv_DeadTimeCfgTypeDef {
    bool enable;                                        /*!< Dead Time Enable               */

    uint16_t rising_time;                               /*!< Dead Time Rising Time          */
    uint16_t falling_time;                              /*!< Dead Time Falling Time         */

    HRPWM_Slv_DtDirETypeDef rising_dir;                 /*!< Dead Time Rising Direction     */
    HRPWM_Slv_DtDirETypeDef falling_dir;                /*!< Dead Time Falling Direction    */
} HRPWM_Slv_DeadTimeCfgTypeDef;

/**
  * @brief HRPWM Slave Chopper Config Structure Definition
  */
typedef struct __HRPWM_Slv_ChopCfgTypeDef {
    bool Aout_chop_en;                                  /*!< OutA Chopper Enable        */
    bool Bout_chop_en;                                  /*!< OutB Chopper Enable        */

    HRPWM_Slv_PC_DutyETypeDef       duty;               /*!< Chopper Duty               */
    HRPWM_Slv_PC_FreqDivETypeDef    freq_div;           /*!< Chopper Frequency Division */
    HRWPM_Slv_PC_PulseWidthETypeDef start_pulse_width;  /*!< Chopper Start Pulse Width  */
} HRPWM_Slv_ChopCfgTypeDef;

/**
  * @brief HRPWM Slave Capture Config Structure Definition
  * @note  capA_trig_evt/capB_trig_evt is combination of HRPWM_SlvX_CapTrigEvtETypeDef (X = [0, HRPWM_SLV_PWM_NUMS-1])
  */
typedef struct __HRPWM_Slv_CapCfgTypeDef {
    bool capA_int_en;                                   /*!< Capture A Interrupt Enable */
    bool capB_int_en;                                   /*!< Capture B Interrupt Enable */

    uint64_t capA_trig_evt;                             /*!< Capture A Trigger Event    */
    uint64_t capB_trig_evt;                             /*!< Capture B Trigger Event    */

    HRPWM_Slv_CapModeETypeDef capA_mode;                /*!< HRPWM Slave Capture A Mode */
    HRPWM_Slv_CapModeETypeDef capB_mode;                /*!< HRPWM Slave Capture B Mode */
} HRPWM_Slv_CapCfgTypeDef;


/**
  * @brief HRPWM Common External Event Config Structure Definition
  */
typedef struct __HRPWM_Comm_ExtEvtCfgTypeDef {
    //Common Config
    HRPWM_Comm_ExtEvtSampClkDivETypeDef samp_clk_div;   /*!< External Event Sample Clock Div    */

    //Each Event Config
    bool    fast_mode_en;                               /*!< External Event Fast Mode Enable    */
    uint8_t fil_len;                                    /*!< External Event Filter Length       */
    HRPWM_Comm_ExtEvtXInputSrcETypeDef src;             /*!< External Event Input Source        */
    HRPWM_Comm_ExtEvtInputPolETypeDef  pol;             /*!< External Event Input Polarity      */
    HRPWM_Comm_ExtEvtInputEdgeETypeDef act_edge;        /*!< External Event Input Active Edge   */
} HRPWM_Comm_ExtEvtCfgTypeDef;

/**
  * @brief HRPWM Common Fault Config Structure Definition
  */
typedef struct __HRPWM_Comm_FltCfgTypeDef {
    //Common Config
    bool sys_flt_int_en;                                /*!< System Fault Interrupt Enable      */
    bool burst_prd_int_en;                              /*!< Burst Mode Period Interrupt Enable */
    HRPWM_Comm_FltSampClkDivETypeDef samp_clk_div;      /*!< Fault Sample Clock Div             */

    //Each Fault Config
    bool    input_en;                                   /*!< Fault Input Enable                 */
    bool    int_en;                                     /*!< Fault Interrupt Enable             */
    uint8_t fil_len;                                    /*!< Fault Filter Length                */
    uint8_t thres;                                      /*!< Fault Counter Threshold            */
    HRPWM_Comm_FltInputPolETypeDef    pol;              /*!< Fault Input Polarity               */
    HRPWM_Comm_FltXInputSrcETypeDef   src;              /*!< Fault Input Source                 */
    HRPWM_Comm_FltCntrRstModeETypeDef rst_mode;         /*!< Fault Counter Reset Mode           */

    bool blk_en;                                        /*!< Fault Blank Enable                 */
    HRPWM_Comm_FltBlkSrcETypeDef blk_src;               /*!< Fault Blank Source                 */
} HRPWM_Comm_FltCfgTypeDef;

/**
  * @brief HRPWM Common ADC Trigger Config Structure Definition
  * @note  trig_evt param config guide:
  *        ADC Trig0/2:   combination of @ref HRPWM_Comm_ADC02TrigEvtSrcETypeDef;
  *        ADC Trig1/3:   combination of @ref HRPWM_Comm_ADC13TrigEvtSrcETypeDef;
  *        ADC Trig4/6/8: @ref HRPWM_Comm_ADC468TrigEvtSrcETypeDef;
  *        ADC Trig5/7/9: @ref HRPWM_Comm_ADC579TrigEvtSrcETypeDef;
  */
typedef struct __HRPWM_Comm_ADCTrigCfgTypeDef {
    uint64_t trig_evt;                                  /*!< ADC Trigger Event          */
    uint8_t  post_scaler;                               /*!< ADC Trigger Post Scaler    */

    HRPWM_Comm_ADCTrigEvtLenETypeDef trig_len;          /*!< ADC Trigger Length         */
    HRPWM_Comm_ADCTrigUpdSrcETypeDEF upd_src;           /*!< ADC Trigger Update Source  */
} HRPWM_Comm_ADCTrigCfgTypeDef;

/**
  * @brief HRPWM Common DLL Config Structure Definition
  */
typedef struct __HRPWM_Comm_DLLCfgTypeDef {
    HRPWM_Comm_DLLCurETypeDef cur;                      /*!< DLL Current Select             */
} HRPWM_Comm_DLLCfgTypeDef;

/**
  * @brief HRPWM Common Burst Mode Config Structure Definition
  * @note  trig_evt    is combination of HRPWM_Comm_BurstTrigEvtETypeDef
  *        mst_reg_upd is combination of HRPWM_Comm_BurstDMAMstRegUpdETypeDef
  *        slv_reg_upd is combination of HRPWM_Comm_BurstDMASlvRegUpdETypeDef
  */
typedef struct __HRPWM_Comm_BurstModeCfgTypeDef {
    bool     enable;                                    /*!< Burst Mode Enable                      */
    bool     pre_load_en;                               /*!< Burst Mode Preload Enable              */
    uint16_t cntr_prd;                                  /*!< Burst Mode Counter Period              */
    uint16_t cmp_val;                                   /*!< Burst Mode Compare Value               */
    uint32_t mst_reg_upd;                               /*!< Burst DMA Master PWM Register Update   */
    uint32_t slv_reg_upd[HRPWM_SLV_PWM_NUMS];           /*!< Burst DMA Slave PWMx Register Update   */
    uint32_t reg_upd_addr;                              /*!< Burst DMA Register Update Address      */
    uint64_t trig_evt;                                  /*!< Burst Mode Trigger Event Mask          */

    HRPWM_WorkModeETypeDef            work_mode;        /*!< Burst Mode Work Mode                   */
    HRPWM_Comm_BurstClkSrcETypeDef    clk_src;          /*!< Burst Mode Clock Source                */
    HRPWM_Comm_BurstClkPresclETypeDef clk_prescl;       /*!< Burst Mode Clock Prescaler             */

    bool     mst_burst_dma_dis;                         /*!< Master PWM Disable Burst DMA           */
    bool     slv_burst_dma_dis[HRPWM_SLV_PWM_NUMS];     /*!< Slave PWMx Disable Burst DMA           */ 
    uint32_t reg_write_addr;                            /*!< Burst DMA Register Write Address       */       
    HRPWM_Comm_BurstTrigModeETypeDef  trig_mode;        /*!< Burst Mode Trigger Mode                */
} HRPWM_Comm_BurstModeCfgTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup HRPMW_LL_Exported_Functions
  * @{
  */

/** @addtogroup HRPMW_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_HRPWM_Init(HRPWM_TypeDef *Instance);
LL_StatusETypeDef LL_HRPWM_DeInit(HRPWM_TypeDef *Instance);
void LL_HRPWM_MspInit(HRPWM_TypeDef *Instance);
void LL_HRPWM_MspDeInit(HRPWM_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup HRPMW_LL_Exported_Functions_Group2
  * @{
  */
//Master PWM Config
LL_StatusETypeDef LL_HRPWM_Mst_SyncCfg(HRPWM_TypeDef *Instance, HRPWM_Mst_SyncCfgTypeDef *cfg);

//Master/Slave PWM Public Config
LL_StatusETypeDef LL_HRPWM_TmrBaseCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_TmrBaseCfgTypeDef *cfg);
LL_StatusETypeDef LL_HRPWM_TmrCmpCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_TmrCmpCfgTypeDef *cfg);
LL_StatusETypeDef LL_HRPWM_DACTrigCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_DACTrigCfgTypeDef *cfg);
LL_StatusETypeDef LL_HRPWM_SysDMACfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_SysDMACfgTypeDef *cfg);

//Slave PWMx Config
LL_StatusETypeDef LL_HRPWM_Slv_TmrRollOverCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_Slv_TmrRollOverCfgTypeDef *cfg);
LL_StatusETypeDef LL_HRPWM_Slv_TmrEvtFilCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_ExtEvtNumETypeDef evtx, HRPWM_Slv_TmrEvtFilCfgTypeDef *cfg);
LL_StatusETypeDef LL_HRPWM_Slv_TmrEvtACfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx,
        HRPWM_Slv_TmrEvtACfgTypeDef *cfg, HRPWM_Slv_TmrEvtFilCfgTypeDef *evt_fil);
LL_StatusETypeDef LL_HRPWM_Slv_OutputCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_OutputCfgTypeDef *cfg);
LL_StatusETypeDef LL_HRPWM_Slv_DeadTimeCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_DeadTimeCfgTypeDef *cfg);
LL_StatusETypeDef LL_HRPWM_Slv_ChopCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_ChopCfgTypeDef *cfg);
LL_StatusETypeDef LL_HRPWM_Slv_CapCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, HRPWM_Slv_CapCfgTypeDef *cfg);

//Common Config
LL_StatusETypeDef LL_HRPWM_Comm_ExtEvtCfg(HRPWM_TypeDef *Instance, HRPWM_ExtEvtNumETypeDef evtx,
        HRPWM_Comm_ExtEvtCfgTypeDef *cfg);
LL_StatusETypeDef LL_HRPWM_Comm_FltCfg(HRPWM_TypeDef *Instance, HRPWM_FltNumETypeDef fltx, HRPWM_Comm_FltCfgTypeDef *cfg);
LL_StatusETypeDef LL_HRPWM_Comm_ADCTrigCfg(HRPWM_TypeDef *Instance, HRPWM_ADCTrigNumETypeDef adc_trigx,
        HRPWM_Comm_ADCTrigCfgTypeDef *cfg);
LL_StatusETypeDef LL_HRPWM_Comm_DLLCfg(HRPWM_TypeDef *Instance, HRPWM_Comm_DLLCfgTypeDef *cfg);
LL_StatusETypeDef LL_HRPWM_Comm_BurstModeCfg(HRPWM_TypeDef *Instance, HRPWM_Comm_BurstModeCfgTypeDef *cfg);
LL_StatusETypeDef LL_HRPWM_Comm_OutputSwapCfg(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx, bool swap_en);
LL_StatusETypeDef LL_HRPWM_Comm_MultiOutputSwap_En(HRPWM_TypeDef *Instance, uint32_t pwmxs);
LL_StatusETypeDef LL_HRPWM_Comm_MultiOutputSwap_Dis(HRPWM_TypeDef *Instance, uint32_t pwmxs);
/**
  * @}
  */


/** @addtogroup HRPMW_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_HRPWM_TmrCntr_Start(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
LL_StatusETypeDef LL_HRPWM_TmrCntr_Stop(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
LL_StatusETypeDef LL_HRPWM_TmrCntr_Rst(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
LL_StatusETypeDef LL_HRPWM_MultiTmrCntr_Start(HRPWM_TypeDef *Instance, uint32_t pwmxs);
LL_StatusETypeDef LL_HRPWM_MultiTmrCntr_Stop(HRPWM_TypeDef *Instance, uint32_t pwmxs);
LL_StatusETypeDef LL_HRPWM_MultiTmrCntr_Rst(HRPWM_TypeDef *Instance, uint32_t pwmxs);

LL_StatusETypeDef LL_HRPWM_Slv_Output_Start(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
LL_StatusETypeDef LL_HRPWM_Slv_Output_Stop(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
LL_StatusETypeDef LL_HRPWM_MultiSlv_Output_Start(HRPWM_TypeDef *Instance, uint32_t output_start_mask);
LL_StatusETypeDef LL_HRPWM_MultiSlv_Output_Stop(HRPWM_TypeDef *Instance, uint32_t output_stop_mask);

LL_StatusETypeDef LL_HRPWM_RegUpd_En(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
LL_StatusETypeDef LL_HRPWM_RegUpd_Dis(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
LL_StatusETypeDef LL_HRPWM_RegUpd_Frc(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
LL_StatusETypeDef LL_HRPWM_MultiRegUpd_En(HRPWM_TypeDef *Instance, uint32_t pwmxs);
LL_StatusETypeDef LL_HRPWM_MultiRegUpd_Dis(HRPWM_TypeDef *Instance, uint32_t pwmxs);
LL_StatusETypeDef LL_HRPWM_MultiRegUpd_Frc(HRPWM_TypeDef *Instance, uint32_t pwmxs);

LL_StatusETypeDef LL_HRPWM_Comm_DLL_Start(HRPWM_TypeDef *Instance);
LL_StatusETypeDef LL_HRPWM_Comm_DLL_Stop(HRPWM_TypeDef *Instance);
LL_StatusETypeDef LL_HRPWM_Comm_FltCntrRst(HRPWM_TypeDef *Instance, HRPWM_FltNumETypeDef fltx);
/**
  * @}
  */


/** @addtogroup HRPMW_LL_Exported_Functions_Interrupt
  * @{
  */
//Master PWM Interrrupt Handler
void LL_HRPWM_Mst_IRQHandler(HRPWM_TypeDef *Instance);
void LL_HRPWM_Mst_CmpACallback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Mst_CmpBCallback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Mst_CmpCCallback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Mst_CmpDCallback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Mst_PeriodCallback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Mst_SyncInputCallback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Mst_UpdateCallback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Mst_RstCallback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Mst_RepCallback(HRPWM_TypeDef *Instance);

//Slave PWMx Interrupt Handler
void LL_HRPWM_Slv_IRQHandler(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_CmpACallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_CmpBCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_CmpCCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_CmpDCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_PrdRollOverCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_UpdateCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_OutASetCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_OutAClrCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_OutBSetCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_OutBClrCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_RstCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_RepCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_CapACallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_CapBCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);
void LL_HRPWM_Slv_DlyProtCallback(HRPWM_TypeDef *Instance, HRPWM_PWMETypeDef pwmx);

//Common Interrupt Handler
void LL_HRPWM_Comm_IRQHandler(HRPWM_TypeDef *Instance);
void LL_HRPWM_Comm_Flt0Callback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Comm_Flt1Callback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Comm_Flt2Callback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Comm_Flt3Callback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Comm_Flt4Callback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Comm_Flt5Callback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Comm_Flt6Callback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Comm_Flt7Callback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Comm_SysFltCallback(HRPWM_TypeDef *Instance);
void LL_HRPWM_Comm_BurstPrdCallback(HRPWM_TypeDef *Instance);
/**
  * @}
  */

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
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_HRPWM_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

