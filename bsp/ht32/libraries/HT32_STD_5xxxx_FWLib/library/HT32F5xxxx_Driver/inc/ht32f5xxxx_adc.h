/*********************************************************************************************************//**
 * @file    ht32f5xxxx_adc.h
 * @version $Rev:: 7265         $
 * @date    $Date:: 2023-10-02 #$
 * @brief   The header file of the ADC library.
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
#ifndef __ht32f5XXXX_ADC_H
#define __ht32f5XXXX_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */


/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup ADC_Exported_Constants ADC exported constants
  * @{
  */
#define IS_ADC(x)                               (x == HT_ADC0)

#define ONE_SHOT_MODE                           (0x00000000)
#define CONTINUOUS_MODE                         (0x00000002)
#if (LIBCFG_ADC_NO_DISCON_MODE)
#define IS_DISCONTINUOUS_MODE(x)                (0)
#else
#define DISCONTINUOUS_MODE                      (0x00000003)
#define IS_DISCONTINUOUS_MODE(x)                (x == DISCONTINUOUS_MODE)
#endif

#define IS_ADC_CONVERSION_MODE(REGULAR_MODE)    ((REGULAR_MODE == ONE_SHOT_MODE)   || \
                                                 (REGULAR_MODE == CONTINUOUS_MODE) || \
                                                 (IS_DISCONTINUOUS_MODE(REGULAR_MODE)))

#define ADC_CH_0                                (0)
#define ADC_CH_1                                (1)
#define ADC_CH_2                                (2)
#define ADC_CH_3                                (3)
#define ADC_CH_4                                (4)
#define ADC_CH_5                                (5)
#define ADC_CH_6                                (6)
#define ADC_CH_7                                (7)

#define IS_ADC_CHANNEL1(CHANNEL)                (((CHANNEL) == ADC_CH_0) || ((CHANNEL) == ADC_CH_1) || \
                                                 ((CHANNEL) == ADC_CH_2) || ((CHANNEL) == ADC_CH_3) || \
                                                 ((CHANNEL) == ADC_CH_4) || ((CHANNEL) == ADC_CH_5) || \
                                                 ((CHANNEL) == ADC_CH_6) || ((CHANNEL) == ADC_CH_7))

#if (LIBCFG_ADC_CH8_9)
#define ADC_CH_8                                (8)
#define ADC_CH_9                                (9)
#define IS_ADC_CHANNEL2(CHANNEL)                (((CHANNEL) == ADC_CH_8) || ((CHANNEL) == ADC_CH_9))
#elif (LIBCFG_ADC_CH8_11)
#define ADC_CH_8                                (8)
#define ADC_CH_9                                (9)
#define ADC_CH_10                               (10)
#define ADC_CH_11                               (11)
#define IS_ADC_CHANNEL2(CHANNEL)                (((CHANNEL) == ADC_CH_8) || ((CHANNEL) == ADC_CH_9) || \
                                                 ((CHANNEL) == ADC_CH_10) || ((CHANNEL) == ADC_CH_11))
#else
#define IS_ADC_CHANNEL2(CHANNEL)                (0)
#endif

#if (LIBCFG_ADC_CH12_15)
#define ADC_CH_12                               (12)
#define ADC_CH_13                               (13)
#define ADC_CH_14                               (14)
#define ADC_CH_15                               (15)
#define IS_ADC_CHANNEL3(CHANNEL)                (((CHANNEL) == ADC_CH_12) || ((CHANNEL) == ADC_CH_13) || \
                                                 ((CHANNEL) == ADC_CH_14) || ((CHANNEL) == ADC_CH_15))
#else
#define IS_ADC_CHANNEL3(CHANNEL)                (0)
#endif

#if defined(USE_HT32F50020_30)
#define ADC_CH_BANDGAP                          (12)
#define ADC_CH_MVDDA                            (13)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_BANDGAP) || ((CH) == ADC_CH_MVDDA))
#endif

#if defined(USE_HT32F50220_30)
#define ADC_CH_GND_VREF                         (12)
#define ADC_CH_VDD_VREF                         (13)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_GND_VREF) || ((CH) == ADC_CH_VDD_VREF))
#endif

#if defined(USE_HT32F50231_41)
#define ADC_CH_GND_VREF                         (12)
#define ADC_CH_VDD_VREF                         (13)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_GND_VREF) || ((CH) == ADC_CH_VDD_VREF))
#endif

#if defined(USE_HT32F52220_30)
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_VDD_VREF                         (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_GND_VREF) || ((CH) == ADC_CH_VDD_VREF))
#endif

#if defined(USE_HT32F52231_41)
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_VDD_VREF                         (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_GND_VREF) || ((CH) == ADC_CH_VDD_VREF))
#endif

#if defined(USE_HT32F52243_53)
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_VDD_VREF                         (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_GND_VREF) || ((CH) == ADC_CH_VDD_VREF))
#endif

#if defined(USE_HT32F52331_41)
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_VDD_VREF                         (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_GND_VREF) || ((CH) == ADC_CH_VDD_VREF))
#endif

#if defined(USE_HT32F52342_52)
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_VDD_VREF                         (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_GND_VREF) || ((CH) == ADC_CH_VDD_VREF))
#endif

#if defined(USE_HT32F52344_54)
#define ADC_CH_IVREF                            (15)
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_MVDDA                            (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_IVREF) || \
                                                 ((CH) == ADC_CH_GND_VREF) || \
                                                 ((CH) == ADC_CH_MVDDA))
#endif

#if defined(USE_HT32F52357_67)
#define ADC_CH_VDD_VREF                         (12)
#define ADC_CH_DAC0_CH1                         (13)
#define ADC_CH_DAC0_CH0                         (14)
#define ADC_CH_IVREF                            (15)
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_MVDDA                            (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_VDD_VREF) || \
                                                 ((CH) == ADC_CH_DAC0_CH1) || \
                                                 ((CH) == ADC_CH_DAC0_CH0) || \
                                                 ((CH) == ADC_CH_IVREF) || \
                                                 ((CH) == ADC_CH_GND_VREF) || \
                                                 ((CH) == ADC_CH_MVDDA))
#endif

#if defined(USE_HT32F57331_41)
#define ADC_CH_VDD_VREF                         (12)
#define ADC_CH_IVREF                            (15)
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_MVDDA                            (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_VDD_VREF) || \
                                                 ((CH) == ADC_CH_IVREF) || \
                                                 ((CH) == ADC_CH_GND_VREF) || \
                                                 ((CH) == ADC_CH_MVDDA))
#endif

#if defined(USE_HT32F57342_52)
#define ADC_CH_VDD_VREF                         (12)
#define ADC_CH_DAC0_CH1                         (13)
#define ADC_CH_DAC0_CH0                         (14)
#define ADC_CH_IVREF                            (15)
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_MVDDA                            (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_VDD_VREF) || \
                                                 ((CH) == ADC_CH_DAC0_CH1) || \
                                                 ((CH) == ADC_CH_DAC0_CH0) || \
                                                 ((CH) == ADC_CH_IVREF) || \
                                                 ((CH) == ADC_CH_GND_VREF) || \
                                                 ((CH) == ADC_CH_MVDDA))
#endif

#if defined(USE_HT32F0006)
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_VDD_VREF                         (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_GND_VREF) || ((CH) == ADC_CH_VDD_VREF))
#endif

#if defined(USE_HT32F61244_45)
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_VDD_VREF                         (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_GND_VREF) || ((CH) == ADC_CH_VDD_VREF))
#endif

#if defined(USE_HT32F50343)
#define ADC_CH_MVDDA                            (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_MVDDA))
#endif

#if defined(USE_HT32F5826)
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_VDD_VREF                         (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_GND_VREF) || ((CH) == ADC_CH_VDD_VREF))
#endif

#if defined(USE_HT32F54231_41)
#define ADC_CH_GND_VREF                         (10)
#define ADC_CH_VDD_VREF                         (11)
#define ADC_CH_IVREF                            (12)
#define ADC_CH_MVDDA                            (13)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_GND_VREF) || \
                                                 ((CH) == ADC_CH_VDD_VREF) || \
                                                 ((CH) == ADC_CH_IVREF) || \
                                                 ((CH) == ADC_CH_MVDDA))
#endif

#if defined(USE_HT32F54243_53)
#define ADC_CH_GND_VREF                         (10)
#define ADC_CH_VDD_VREF                         (11)
#define ADC_CH_IVREF                            (12)
#define ADC_CH_MVDDA                            (13)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_GND_VREF) || \
                                                 ((CH) == ADC_CH_VDD_VREF) || \
                                                 ((CH) == ADC_CH_IVREF) || \
                                                 ((CH) == ADC_CH_MVDDA))
#endif

#if defined(USE_HT32F67041_51)
#define ADC_CH_IVREF                            (15)
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_MVDDA                            (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_IVREF) || \
                                                 ((CH) == ADC_CH_GND_VREF) || \
                                                 ((CH) == ADC_CH_MVDDA))
#endif

#if defined(USE_HT32F52234_44)
#define ADC_CH_DAC0_CH0                         (12)
#define ADC_CH_DAC0_CH1                         (13)
#define ADC_CH_DAC1_CH0                         (14)
#define ADC_CH_DAC1_CH1                         (15)
#define ADC_CH_IVREF                            (16)
#define ADC_CH_MVDDA                            (17)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_DAC0_CH0) || \
                                                 ((CH) == ADC_CH_DAC0_CH1) || \
                                                 ((CH) == ADC_CH_DAC1_CH0) || \
                                                 ((CH) == ADC_CH_DAC1_CH1) || \
                                                 ((CH) == ADC_CH_IVREF) || \
                                                 ((CH) == ADC_CH_MVDDA))
#endif

#if defined(USE_HT32F53231_41)
#define ADC_CH_IVREF                            (12)
#define ADC_CH_MVDDA                            (13)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_IVREF) || \
                                                 ((CH) == ADC_CH_MVDDA))
#endif

#if defined(USE_HT32F53242_52)
#define ADC_CH_IVREF                            (12)
#define ADC_CH_MVDDA                            (13)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_IVREF) || \
                                                 ((CH) == ADC_CH_MVDDA))
#endif

#if defined(USE_HT32F50431_41)
#define ADC_CH_IVREF                            (12)
#define ADC_CH_MVDDA                            (13)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_IVREF) || \
                                                 ((CH) == ADC_CH_MVDDA))
#endif

#if defined(USE_HT32F50442_52)
#define ADC_CH_IVREF                            (12)
#define ADC_CH_MVDDA                            (13)
#define IS_ADC_CH_INTERNAL1(CH)                 (((CH) == ADC_CH_IVREF) || \
                                                 ((CH) == ADC_CH_MVDDA))
#endif

#define IS_ADC_CHANNEL(CHANNEL)                  (IS_ADC_CHANNEL1(CHANNEL) || \
                                                  IS_ADC_CHANNEL2(CHANNEL) || \
                                                  IS_ADC_CHANNEL3(CHANNEL) || \
                                                  IS_ADC_CH_INTERNAL1(CHANNEL))

#define IS_ADC_INPUT_CHANNEL(CHANNEL)           (IS_ADC_CHANNEL1(CHANNEL) || IS_ADC_CHANNEL2(CHANNEL) || IS_ADC_CHANNEL3(CHANNEL))


#define ADC_TRIG_SOFTWARE                       (1UL << 0)

#if (LIBCFG_ADC_SW_TRIGGER_ONLY)
#define IS_ADC_TRIG(REGTRIG)                    ((REGTRIG) == ADC_TRIG_SOFTWARE)
#else
/* ((ADCTCR[4] << 4) | (ADCTSR[20] << 20))                                                                  */
#if (LIBCFG_CMP)
#define ADC_TRIG_CMP0                           ((1UL << 4) | (0UL << 20))
#define ADC_TRIG_CMP1                           ((1UL << 4) | (1UL << 20))
#endif

/* ((ADCTCR[3] << 3) | (ADCTSR[23:22] << 22) | (ADCTSR[19] << 19))                                          */
#define ADC_TRIG_BFTM0                          ((1UL << 3) | (0UL << 22) | (0UL << 19))
#if (LIBCFG_BFTM1)
#define ADC_TRIG_BFTM1                          ((1UL << 3) | (0UL << 22) | (1UL << 19))
#endif

/* ((ADCTCR[3] << 3) | (ADCTSR[29:27]) << 27) | (ADCTSR[23:22] << 22) | (ADCTSR[19] << 19))                 */
#if (LIBCFG_PWM0)
#define ADC_TRIG_PWM0_MTO                       ((1UL << 3) | (0UL << 27) | (1UL << 22) | (0UL << 19))
#define ADC_TRIG_PWM0_CH0O                      ((1UL << 3) | (1UL << 27) | (1UL << 22) | (0UL << 19))
#define ADC_TRIG_PWM0_CH1O                      ((1UL << 3) | (2UL << 27) | (1UL << 22) | (0UL << 19))
#define ADC_TRIG_PWM0_CH2O                      ((1UL << 3) | (3UL << 27) | (1UL << 22) | (0UL << 19))
#define ADC_TRIG_PWM0_CH3O                      ((1UL << 3) | (4UL << 27) | (1UL << 22) | (0UL << 19))
#endif
#if (LIBCFG_PWM1)
#define ADC_TRIG_PWM1_MTO                       ((1UL << 3) | (0UL << 27) | (1UL << 22) | (1UL << 19))
#define ADC_TRIG_PWM1_CH0O                      ((1UL << 3) | (1UL << 27) | (1UL << 22) | (1UL << 19))
#define ADC_TRIG_PWM1_CH1O                      ((1UL << 3) | (2UL << 27) | (1UL << 22) | (1UL << 19))
#define ADC_TRIG_PWM1_CH2O                      ((1UL << 3) | (3UL << 27) | (1UL << 22) | (1UL << 19))
#define ADC_TRIG_PWM1_CH3O                      ((1UL << 3) | (4UL << 27) | (1UL << 22) | (1UL << 19))
#endif

/* ((ADCTCR[2] << 2) | (ADCTSR[26:24] << 24) | (ADCTSR[18:16] << 16))                                       */
#if (LIBCFG_MCTM0)
#define ADC_TRIG_MCTM0_MTO                      ((1UL << 2) | (0UL << 24) | (0UL << 16))
#define ADC_TRIG_MCTM0_CH0O                     ((1UL << 2) | (1UL << 24) | (0UL << 16))
#define ADC_TRIG_MCTM0_CH1O                     ((1UL << 2) | (2UL << 24) | (0UL << 16))
#define ADC_TRIG_MCTM0_CH2O                     ((1UL << 2) | (3UL << 24) | (0UL << 16))
#define ADC_TRIG_MCTM0_CH3O                     ((1UL << 2) | (4UL << 24) | (0UL << 16))
#endif

#if (LIBCFG_NO_GPTM0)
#define IS_ADC_TRIG_GPTM0(x)                    (0)
#else
#define ADC_TRIG_GPTM0_MTO                      ((1UL << 2) | (0UL << 24) | (2UL << 16))
#define ADC_TRIG_GPTM0_CH0O                     ((1UL << 2) | (1UL << 24) | (2UL << 16))
#define ADC_TRIG_GPTM0_CH1O                     ((1UL << 2) | (2UL << 24) | (2UL << 16))
#define ADC_TRIG_GPTM0_CH2O                     ((1UL << 2) | (3UL << 24) | (2UL << 16))
#define ADC_TRIG_GPTM0_CH3O                     ((1UL << 2) | (4UL << 24) | (2UL << 16))

#define IS_ADC_TRIG_GPTM0(x)                    (((x) == ADC_TRIG_GPTM0_MTO)  || \
                                                 ((x) == ADC_TRIG_GPTM0_CH0O) || \
                                                 ((x) == ADC_TRIG_GPTM0_CH1O) || \
                                                 ((x) == ADC_TRIG_GPTM0_CH2O) || \
                                                 ((x) == ADC_TRIG_GPTM0_CH3O))
#endif

#if (LIBCFG_GPTM1)
#define ADC_TRIG_GPTM1_MTO                      ((1UL << 2) | (0UL << 24) | (3UL << 16))
#define ADC_TRIG_GPTM1_CH0O                     ((1UL << 2) | (1UL << 24) | (3UL << 16))
#define ADC_TRIG_GPTM1_CH1O                     ((1UL << 2) | (2UL << 24) | (3UL << 16))
#define ADC_TRIG_GPTM1_CH2O                     ((1UL << 2) | (3UL << 24) | (3UL << 16))
#define ADC_TRIG_GPTM1_CH3O                     ((1UL << 2) | (4UL << 24) | (3UL << 16))
#endif

/* (ADCTCR[1] << 1) | (ADCTSR[11:8] << 8)                                                                   */
#define ADC_TRIG_EXTI_0                         ((1UL << 1) | ( 0UL << 8))
#define ADC_TRIG_EXTI_1                         ((1UL << 1) | ( 1UL << 8))
#define ADC_TRIG_EXTI_2                         ((1UL << 1) | ( 2UL << 8))
#define ADC_TRIG_EXTI_3                         ((1UL << 1) | ( 3UL << 8))
#define ADC_TRIG_EXTI_4                         ((1UL << 1) | ( 4UL << 8))
#define ADC_TRIG_EXTI_5                         ((1UL << 1) | ( 5UL << 8))
#define ADC_TRIG_EXTI_6                         ((1UL << 1) | ( 6UL << 8))
#define ADC_TRIG_EXTI_7                         ((1UL << 1) | ( 7UL << 8))
#define ADC_TRIG_EXTI_8                         ((1UL << 1) | ( 8UL << 8))
#define ADC_TRIG_EXTI_9                         ((1UL << 1) | ( 9UL << 8))
#define ADC_TRIG_EXTI_10                        ((1UL << 1) | (10UL << 8))
#define ADC_TRIG_EXTI_11                        ((1UL << 1) | (11UL << 8))
#define ADC_TRIG_EXTI_12                        ((1UL << 1) | (12UL << 8))
#define ADC_TRIG_EXTI_13                        ((1UL << 1) | (13UL << 8))
#define ADC_TRIG_EXTI_14                        ((1UL << 1) | (14UL << 8))
#define ADC_TRIG_EXTI_15                        ((1UL << 1) | (15UL << 8))

#define IS_ADC_TRIG(REGTRIG)                    (IS_ADC_TRIG1(REGTRIG) || \
                                                 IS_ADC_TRIG2(REGTRIG) || \
                                                 IS_ADC_TRIG3(REGTRIG) || \
                                                 IS_ADC_TRIG4(REGTRIG) || \
                                                 IS_ADC_TRIG5(REGTRIG) || \
                                                 IS_ADC_TRIG6(REGTRIG) || \
                                                 IS_ADC_TRIG7(REGTRIG))

#define IS_ADC_TRIG1(REGTRIG)                   (IS_ADC_TRIG_GPTM0(REGTRIG)         || \
                                                 ((REGTRIG) == ADC_TRIG_BFTM0)      || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_0)     || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_1)     || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_2)     || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_3)     || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_4)     || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_5)     || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_6)     || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_7)     || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_8)     || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_9)     || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_10)    || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_11)    || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_12)    || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_13)    || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_14)    || \
                                                 ((REGTRIG) == ADC_TRIG_EXTI_15)    || \
                                                 ((REGTRIG) == ADC_TRIG_SOFTWARE))

#if (LIBCFG_BFTM1)
#define IS_ADC_TRIG2(REGTRIG)                   ((REGTRIG) == ADC_TRIG_BFTM1)
#else
#define IS_ADC_TRIG2(REGTRIG)                   (0)
#endif

#if (LIBCFG_MCTM0)
#define IS_ADC_TRIG3(REGTRIG)                   (((REGTRIG) == ADC_TRIG_MCTM0_MTO)  || \
                                                 ((REGTRIG) == ADC_TRIG_MCTM0_CH0O) || \
                                                 ((REGTRIG) == ADC_TRIG_MCTM0_CH1O) || \
                                                 ((REGTRIG) == ADC_TRIG_MCTM0_CH2O) || \
                                                 ((REGTRIG) == ADC_TRIG_MCTM0_CH3O) || \
                                                 ((REGTRIG) == ADC_TRIG_BFTM1))
#else
#define IS_ADC_TRIG3(REGTRIG)                   (0)
#endif

#if (LIBCFG_GPTM1)
#define IS_ADC_TRIG4(REGTRIG)                   (((REGTRIG) == ADC_TRIG_GPTM1_MTO)  || \
                                                 ((REGTRIG) == ADC_TRIG_GPTM1_CH0O) || \
                                                 ((REGTRIG) == ADC_TRIG_GPTM1_CH1O) || \
                                                 ((REGTRIG) == ADC_TRIG_GPTM1_CH2O) || \
                                                 ((REGTRIG) == ADC_TRIG_GPTM1_CH3O))
#else
#define IS_ADC_TRIG4(REGTRIG)                   (0)
#endif

#if (LIBCFG_PWM0)
#define IS_ADC_TRIG5(REGTRIG)                   (((REGTRIG) == ADC_TRIG_PWM0_MTO)  || \
                                                 ((REGTRIG) == ADC_TRIG_PWM0_CH0O) || \
                                                 ((REGTRIG) == ADC_TRIG_PWM0_CH1O) || \
                                                 ((REGTRIG) == ADC_TRIG_PWM0_CH2O) || \
                                                 ((REGTRIG) == ADC_TRIG_PWM0_CH3O))
#else
#define IS_ADC_TRIG5(REGTRIG)                   (0)
#endif

#if (LIBCFG_PWM1)
#define IS_ADC_TRIG6(REGTRIG)                   (((REGTRIG) == ADC_TRIG_PWM1_MTO)  || \
                                                 ((REGTRIG) == ADC_TRIG_PWM1_CH0O) || \
                                                 ((REGTRIG) == ADC_TRIG_PWM1_CH1O) || \
                                                 ((REGTRIG) == ADC_TRIG_PWM1_CH2O) || \
                                                 ((REGTRIG) == ADC_TRIG_PWM1_CH3O))
#else
#define IS_ADC_TRIG6(REGTRIG)                   (0)
#endif

#if (LIBCFG_CMP)
#define IS_ADC_TRIG7(REGTRIG)                   (((REGTRIG) == ADC_TRIG_CMP0) || \
                                                 ((REGTRIG) == ADC_TRIG_CMP1))
#else
#define IS_ADC_TRIG7(REGTRIG)                   (0)
#endif
#endif

#define ADC_INT_SINGLE_EOC                      (0x00000001)
#if (LIBCFG_ADC_NO_DISCON_MODE == 0)
#define ADC_INT_SUB_GROUP_EOC                   (0x00000002)
#endif
#define ADC_INT_CYCLE_EOC                       (0x00000004)
#if (LIBCFG_ADC_NO_WDT == 0)
#define ADC_INT_AWD_LOWER                       (0x00010000)
#define ADC_INT_AWD_UPPER                       (0x00020000)
#endif
#define ADC_INT_DATA_OVERWRITE                  (0x01000000)

#define IS_ADC_INT(INT)                         ((((INT) & 0xFEFCFFF8) == 0) && ((INT) != 0))


#define ADC_FLAG_SINGLE_EOC                     (0x00000001)
#if (LIBCFG_ADC_NO_DISCON_MODE == 0)
#define ADC_FLAG_SUB_GROUP_EOC                  (0x00000002)
#endif
#define ADC_FLAG_CYCLE_EOC                      (0x00000004)
#if (LIBCFG_ADC_NO_WDT == 0)
#define ADC_FLAG_AWD_LOWER                      (0x00010000)
#define ADC_FLAG_AWD_UPPER                      (0x00020000)
#endif
#define ADC_FLAG_DATA_OVERWRITE                 (0x01000000)

#define IS_ADC_FLAG(FLAG)                       ((((FLAG) & 0xFEFCFFF8) == 0) && ((FLAG) != 0))


#define ADC_REGULAR_DATA0                       (0)
#define ADC_REGULAR_DATA1                       (1)
#define ADC_REGULAR_DATA2                       (2)
#define ADC_REGULAR_DATA3                       (3)
#if (LIBCFG_ADC_NO_SEQ_4_7 == 0)
#define ADC_REGULAR_DATA4                       (4)
#define ADC_REGULAR_DATA5                       (5)
#define ADC_REGULAR_DATA6                       (6)
#define ADC_REGULAR_DATA7                       (7)
#endif

#if (LIBCFG_ADC_NO_SEQ_4_7)
#define IS_ADC_REGULAR_DATA(DATA)               ((DATA) < 4)
#else
#define IS_ADC_REGULAR_DATA(DATA)               ((DATA) < 8)
#endif

#define ADC_AWD_DISABLE                         (u8)0x00
#define ADC_AWD_ALL_LOWER                       (u8)0x05
#define ADC_AWD_ALL_UPPER                       (u8)0x06
#define ADC_AWD_ALL_LOWER_UPPER                 (u8)0x07
#define ADC_AWD_SINGLE_LOWER                    (u8)0x01
#define ADC_AWD_SINGLE_UPPER                    (u8)0x02
#define ADC_AWD_SINGLE_LOWER_UPPER              (u8)0x03

#define IS_ADC_AWD(AWD)                         (((AWD) == ADC_AWD_DISABLE)         || \
                                                 ((AWD) == ADC_AWD_ALL_LOWER)       || \
                                                 ((AWD) == ADC_AWD_ALL_UPPER)       || \
                                                 ((AWD) == ADC_AWD_ALL_LOWER_UPPER) || \
                                                 ((AWD) == ADC_AWD_SINGLE_LOWER)    || \
                                                 ((AWD) == ADC_AWD_SINGLE_UPPER)    || \
                                                 ((AWD) == ADC_AWD_SINGLE_LOWER_UPPER))

#define IS_ADC_THRESHOLD(THRESHOLD)             ((THRESHOLD) < 4096)

#if (LIBCFG_PDMA)
#define ADC_PDMA_REGULAR_SINGLE                 (0x00000001)
#define ADC_PDMA_REGULAR_SUBGROUP               (0x00000002)
#define ADC_PDMA_REGULAR_CYCLE                  (0x00000004)

#define IS_ADC_PDMA(PDMA)                       (((PDMA) == ADC_PDMA_REGULAR_SINGLE)   || \
                                                 ((PDMA) == ADC_PDMA_REGULAR_SUBGROUP) || \
                                                 ((PDMA) == ADC_PDMA_REGULAR_CYCLE))
#endif

#define IS_ADC_INPUT_SAMPLING_TIME(TIME)        ((TIME) <= 255)

#define IS_ADC_OFFSET(OFFSET)                   ((OFFSET) < 4096)


#if (LIBCFG_ADC_NO_SEQ_4_7)
#define IS_ADC_REGULAR_RANK(RANK)               ((RANK) < 4)
#define IS_ADC_REGULAR_LENGTH(LENGTH)           (((LENGTH) >= 1) && ((LENGTH) <= 4))
#else
#define IS_ADC_REGULAR_RANK(RANK)               ((RANK) < 8)
#define IS_ADC_REGULAR_LENGTH(LENGTH)           (((LENGTH) >= 1) && ((LENGTH) <= 8))
#endif
#define IS_ADC_REGULAR_SUB_LENGTH(SUB_LENGTH)   (((SUB_LENGTH) >= 1) && ((SUB_LENGTH) <= 8))

#if (LIBCFG_ADC_IVREF)
#if (LIBCFG_ADC_IVREF_LEVEL_TYPE2)
#define ADC_VREF_2V5                            (0ul << 4)
#define ADC_VREF_3V0                            (1ul << 4)
#define ADC_VREF_4V0                            (2ul << 4)
#define ADC_VREF_4V5                            (3ul << 4)

#define IS_ADC_VREF_SEL(SEL)                    ((SEL == ADC_VREF_2V5) || \
                                                 (SEL == ADC_VREF_3V0) || \
                                                 (SEL == ADC_VREF_4V0) || \
                                                 (SEL == ADC_VREF_4V5))
#else
  #if LIBCFG_ADC_IVREF_DEFAULT_08V
  #define ADC_VREF_0V8                            (0ul << 4)
  #define ADC_VREF_DEFAULT                        ADC_VREF_0V8
  #else
  #define ADC_VREF_1V215                          (0ul << 4)
  #define ADC_VREF_DEFAULT                        ADC_VREF_1V215
  #endif
#define ADC_VREF_2V0                            (1ul << 4)
#define ADC_VREF_2V5                            (2ul << 4)
#define ADC_VREF_2V7                            (3ul << 4)

#define IS_ADC_VREF_SEL(SEL)                    ((SEL == ADC_VREF_DEFAULT) || \
                                                 (SEL == ADC_VREF_2V0)     || \
                                                 (SEL == ADC_VREF_2V5)     || \
                                                 (SEL == ADC_VREF_2V7))
#endif
#endif

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup ADC_Exported_Functions ADC exported functions
  * @{
  */
void ADC_DeInit(HT_ADC_TypeDef* HT_ADCn);
void ADC_Reset(HT_ADC_TypeDef* HT_ADCn);
void ADC_Cmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState);

void ADC_SamplingTimeConfig(HT_ADC_TypeDef* HT_ADCn, u8 SampleClock);
void ADC_RegularChannelConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n, u8 Rank, ...);
void ADC_RegularGroupConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_MODE, u8 Length, u8 SubLength);
void ADC_RegularTrigConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_TRIG_x);

void ADC_SoftwareStartConvCmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState);

u16 ADC_GetConversionData(HT_ADC_TypeDef* HT_ADCn, u8 ADC_REGULAR_DATAn);

void ADC_IntConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_INT_x, ControlStatus NewState);
FlagStatus ADC_GetIntStatus(HT_ADC_TypeDef* HT_ADCn, u32 ADC_INT_x);
void ADC_ClearIntPendingBit(HT_ADC_TypeDef* HT_ADCn, u32 ADC_INT_x);
FlagStatus ADC_GetFlagStatus(HT_ADC_TypeDef* HT_ADCn, u32 ADC_FLAG_x);

#if (LIBCFG_ADC_NO_WDT)
#else
void ADC_AWDConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_AWD_x);
void ADC_AWDSingleChannelConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n);
void ADC_AWDThresholdsConfig(HT_ADC_TypeDef* HT_ADCn, u16 UPPER, u16 LOWER);
#endif

#if (LIBCFG_PDMA)
void ADC_PDMAConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_PDMA_x, ControlStatus NewState);
#endif

#if (LIBCFG_ADC_IVREF)
void ADC_VREFCmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState);
void ADC_VREFConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_VREF_x);
#endif

#if (LIBCFG_ADC_VREFBUF)
void ADC_VREFOutputCmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState);
#endif

#if (LIBCFG_ADC_MVDDA)
void ADC_MVDDACmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState);
#endif
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
