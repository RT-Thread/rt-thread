/*********************************************************************************************************//**
 * @file    ht32f1xxxx_adc.h
 * @version $Rev:: 2791         $
 * @date    $Date:: 2022-11-24 #$
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
#ifndef __HT32F1XXXX_ADC_H
#define __HT32F1XXXX_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */


/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup ADC_Exported_Constants ADC exported constants
  * @{
  */
#define IS_ADC(x)                               (x == HT_ADC)

#define ONE_SHOT_MODE                           (0x00000000)
#define CONTINUOUS_MODE                         (0x00000002)
#define DISCONTINUOUS_MODE                      (0x00000003)

#define IS_ADC_CONVERSION_MODE(REGULAR_MODE)    (((REGULAR_MODE) == ONE_SHOT_MODE)   || \
                                                 ((REGULAR_MODE) == CONTINUOUS_MODE) || \
                                                 ((REGULAR_MODE) == DISCONTINUOUS_MODE))

#define IS_ADC_HP_CONVERSION_MODE(HP_MODE)      (((HP_MODE) == ONE_SHOT_MODE)   || \
                                                 ((HP_MODE) == CONTINUOUS_MODE) || \
                                                 ((HP_MODE) == DISCONTINUOUS_MODE))


#define ADC_CH_0                                (0)
#define ADC_CH_1                                (1)
#define ADC_CH_2                                (2)
#define ADC_CH_3                                (3)
#define ADC_CH_4                                (4)
#define ADC_CH_5                                (5)
#define ADC_CH_6                                (6)
#define ADC_CH_7                                (7)
#if !(LIBCFG_NO_ADC_CH8_15)
#define ADC_CH_8                                (8)
#define ADC_CH_9                                (9)
#define ADC_CH_10                               (10)
#define ADC_CH_11                               (11)
#if (LIBCFG_ADC_CH12_15)
#define ADC_CH_12                               (12)
#define ADC_CH_13                               (13)
#define ADC_CH_14                               (14)
#define ADC_CH_15                               (15)
#define IS_ADC_CHANNEL12_15(CHANNEL)            (((CHANNEL) == ADC_CH_12) || ((CHANNEL) == ADC_CH_13) || \
                                                 ((CHANNEL) == ADC_CH_14) || ((CHANNEL) == ADC_CH_15))
#else
#define IS_ADC_CHANNEL12_15(CHANNEL)            (0)
#endif
#else
#define IS_ADC_CHANNEL8_14(CHANNEL)             (0)
#define ADC_CH_IVREF                            (15)
#endif
#define ADC_CH_GND_VREF                         (16)
#define ADC_CH_VDD_VREF                         (17)

#define ADC_CH_GNDREF ADC_CH_GND_VREF
#define ADC_CH_VREF   ADC_CH_VDD_VREF


#if (LIBCFG_NO_ADC_CH8_15)
#define IS_ADC_CHANNEL(CHANNEL)                 (((CHANNEL) == ADC_CH_0)    || ((CHANNEL) == ADC_CH_1)    || \
                                                 ((CHANNEL) == ADC_CH_2)    || ((CHANNEL) == ADC_CH_3)    || \
                                                 ((CHANNEL) == ADC_CH_4)    || ((CHANNEL) == ADC_CH_5)    || \
                                                 ((CHANNEL) == ADC_CH_6)    || ((CHANNEL) == ADC_CH_7)    || \
                                                 (IS_ADC_CHANNEL8_14(CHANNEL)) || \
                                                 ((CHANNEL) == ADC_CH_IVREF) || ((CHANNEL) == ADC_CH_GND_VREF) || \
                                                 ((CHANNEL) == ADC_CH_VDD_VREF))
#else
#define IS_ADC_CHANNEL(CHANNEL)                 (((CHANNEL) == ADC_CH_0)  || ((CHANNEL) == ADC_CH_1)  || \
                                                 ((CHANNEL) == ADC_CH_2)  || ((CHANNEL) == ADC_CH_3)  || \
                                                 ((CHANNEL) == ADC_CH_4)  || ((CHANNEL) == ADC_CH_5)  || \
                                                 ((CHANNEL) == ADC_CH_6)  || ((CHANNEL) == ADC_CH_7)  || \
                                                 ((CHANNEL) == ADC_CH_8)  || ((CHANNEL) == ADC_CH_9)  || \
                                                 ((CHANNEL) == ADC_CH_10) || ((CHANNEL) == ADC_CH_11) || \
                                                 (IS_ADC_CHANNEL12_15(CHANNEL)) || \
                                                 ((CHANNEL) == ADC_CH_GND_VREF) || ((CHANNEL) == ADC_CH_VDD_VREF))
#endif

#if (LIBCFG_NO_ADC_CH8_15)
#define IS_ADC_INPUT_CHANNEL(CHANNEL)           (((CHANNEL) == ADC_CH_0)  || ((CHANNEL) == ADC_CH_1)  || \
                                                 ((CHANNEL) == ADC_CH_2)  || ((CHANNEL) == ADC_CH_3)  || \
                                                 ((CHANNEL) == ADC_CH_4)  || ((CHANNEL) == ADC_CH_5)  || \
                                                 ((CHANNEL) == ADC_CH_6)  || ((CHANNEL) == ADC_CH_7))
#else
#define IS_ADC_INPUT_CHANNEL(CHANNEL)           (((CHANNEL) == ADC_CH_0)  || ((CHANNEL) == ADC_CH_1)  || \
                                                 ((CHANNEL) == ADC_CH_2)  || ((CHANNEL) == ADC_CH_3)  || \
                                                 ((CHANNEL) == ADC_CH_4)  || ((CHANNEL) == ADC_CH_5)  || \
                                                 ((CHANNEL) == ADC_CH_6)  || ((CHANNEL) == ADC_CH_7)  || \
                                                 ((CHANNEL) == ADC_CH_8)  || ((CHANNEL) == ADC_CH_9)  || \
                                                 ((CHANNEL) == ADC_CH_10) || ((CHANNEL) == ADC_CH_11) || \
                                                 (IS_ADC_CHANNEL12_15(CHANNEL)))
#endif

#define ADC_TRIG_SOFTWARE                       (1UL << 0)

/* ((ADCTCR[4] << 4) | (ADCTSR[20] << 20))                                                                  */
#if (!LIBCFG_NO_CMP_TRIG_ADC)
#define ADC_TRIG_CMP0                           ((1UL << 4) | (0UL << 20))
#define ADC_TRIG_CMP1                           ((1UL << 4) | (1UL << 20))
#endif

#if (!LIBCFG_NO_CMP_HPTRIG_ADC)
#define ADC_HPTRIG_CMP0                         ADC_TRIG_CMP0
#define ADC_HPTRIG_CMP1                         ADC_TRIG_CMP1
#endif

/* ((ADCTCR[3] << 3) | (ADCTSR[23:22] << 22) | (ADCTSR[19] << 19))                                          */
#define ADC_TRIG_BFTM0                          ((1UL << 3) | (0UL << 22) | (0UL << 19))
#define ADC_TRIG_BFTM1                          ((1UL << 3) | (0UL << 22) | (1UL << 19))

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
#if (!LIBCFG_NO_MCTM0)
#define ADC_TRIG_MCTM0_MTO                      ((1UL << 2) | (0UL << 24) | (0UL << 16))
#define ADC_TRIG_MCTM0_CH0O                     ((1UL << 2) | (1UL << 24) | (0UL << 16))
#define ADC_TRIG_MCTM0_CH1O                     ((1UL << 2) | (2UL << 24) | (0UL << 16))
#define ADC_TRIG_MCTM0_CH2O                     ((1UL << 2) | (3UL << 24) | (0UL << 16))
#define ADC_TRIG_MCTM0_CH3O                     ((1UL << 2) | (4UL << 24) | (0UL << 16))
#endif

#if (!LIBCFG_NO_MCTM1)
#define ADC_TRIG_MCTM1_MTO                      ((1UL << 2) | (0UL << 24) | (1UL << 16))
#define ADC_TRIG_MCTM1_CH0O                     ((1UL << 2) | (1UL << 24) | (1UL << 16))
#define ADC_TRIG_MCTM1_CH1O                     ((1UL << 2) | (2UL << 24) | (1UL << 16))
#define ADC_TRIG_MCTM1_CH2O                     ((1UL << 2) | (3UL << 24) | (1UL << 16))
#define ADC_TRIG_MCTM1_CH3O                     ((1UL << 2) | (4UL << 24) | (1UL << 16))
#endif

#define ADC_TRIG_GPTM0_MTO                      ((1UL << 2) | (0UL << 24) | (2UL << 16))
#define ADC_TRIG_GPTM0_CH0O                     ((1UL << 2) | (1UL << 24) | (2UL << 16))
#define ADC_TRIG_GPTM0_CH1O                     ((1UL << 2) | (2UL << 24) | (2UL << 16))
#define ADC_TRIG_GPTM0_CH2O                     ((1UL << 2) | (3UL << 24) | (2UL << 16))
#define ADC_TRIG_GPTM0_CH3O                     ((1UL << 2) | (4UL << 24) | (2UL << 16))

#if (!LIBCFG_NO_GPTM1)
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

#define IS_ADC_HPTRIG(REGTRIG)                  (IS_ADC_TRIG1(REGTRIG) || \
                                                 IS_ADC_TRIG2(REGTRIG) || \
                                                 IS_ADC_TRIG3(REGTRIG) || \
                                                 IS_ADC_TRIG4(REGTRIG) || \
                                                 IS_ADC_TRIG5(REGTRIG) || \
                                                 IS_ADC_TRIG6(REGTRIG) || \
                                                 IS_ADC_HPTRIG7(REGTRIG))

#define IS_ADC_TRIG1(REGTRIG)                   (((REGTRIG) == ADC_TRIG_GPTM0_MTO)  || \
                                                 ((REGTRIG) == ADC_TRIG_GPTM0_CH0O) || \
                                                 ((REGTRIG) == ADC_TRIG_GPTM0_CH1O) || \
                                                 ((REGTRIG) == ADC_TRIG_GPTM0_CH2O) || \
                                                 ((REGTRIG) == ADC_TRIG_GPTM0_CH3O) || \
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

#define IS_ADC_TRIG2(REGTRIG)                   ((REGTRIG) == ADC_TRIG_BFTM1)

#if (!LIBCFG_NO_MCTM0)
#define IS_ADC_TRIG3(REGTRIG)                   (((REGTRIG) == ADC_TRIG_MCTM0_MTO)  || \
                                                 ((REGTRIG) == ADC_TRIG_MCTM0_CH0O) || \
                                                 ((REGTRIG) == ADC_TRIG_MCTM0_CH1O) || \
                                                 ((REGTRIG) == ADC_TRIG_MCTM0_CH2O) || \
                                                 ((REGTRIG) == ADC_TRIG_MCTM0_CH3O) || \
                                                 ((REGTRIG) == ADC_TRIG_BFTM1))
#else
#define IS_ADC_TRIG3(REGTRIG)                   (0)
#endif

#if (!LIBCFG_NO_MCTM1)
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

#if (!LIBCFG_NO_CMP_TRIG_ADC)
#define IS_ADC_TRIG7(REGTRIG)                   (((REGTRIG) == ADC_TRIG_CMP0) || \
                                                 ((REGTRIG) == ADC_TRIG_CMP1))
#else
#define IS_ADC_TRIG7(REGTRIG)                   (0)
#endif

#if (!LIBCFG_NO_CMP_HPTRIG_ADC)
#define IS_ADC_HPTRIG7(REGTRIG)                  (((REGTRIG) == ADC_HPTRIG_CMP0) || \
                                                  ((REGTRIG) == ADC_HPTRIG_CMP1))
#else
#define IS_ADC_HPTRIG7(REGTRIG)                 (0)
#endif


#define ADC_INT_SINGLE_EOC                      (0x00000001)
#define ADC_INT_SUB_GROUP_EOC                   (0x00000002)
#define ADC_INT_CYCLE_EOC                       (0x00000004)
#define ADC_INT_HP_SINGLE_EOC                   (0x00000100)
#define ADC_INT_HP_SUB_GROUP_EOC                (0x00000200)
#define ADC_INT_HP_CYCLE_EOC                    (0x00000400)
#define ADC_INT_AWD_LOWER                       (0x00010000)
#define ADC_INT_AWD_UPPER                       (0x00020000)
#define ADC_INT_DATA_OVERWRITE                  (0x01000000)
#define ADC_INT_HP_DATA_OVERWRITE               (0x02000000)

#define IS_ADC_INT(INT)                         ((((INT) & 0xFCFCF8F8) == 0) && ((INT) != 0))


#define ADC_FLAG_SINGLE_EOC                     (0x00000001)
#define ADC_FLAG_SUB_GROUP_EOC                  (0x00000002)
#define ADC_FLAG_CYCLE_EOC                      (0x00000004)
#define ADC_FLAG_HP_SINGLE_EOC                  (0x00000100)
#define ADC_FLAG_HP_SUB_GROUP_EOC               (0x00000200)
#define ADC_FLAG_HP_CYCLE_EOC                   (0x00000400)
#define ADC_FLAG_AWD_LOWER                      (0x00010000)
#define ADC_FLAG_AWD_UPPER                      (0x00020000)
#define ADC_FLAG_DATA_OVERWRITE                 (0x01000000)
#define ADC_FLAG_HP_DATA_OVERWRITE              (0x02000000)

#define IS_ADC_FLAG(FLAG)                       ((((FLAG) & 0xFCFCF8F8) == 0) && ((FLAG) != 0))


#define ADC_REGULAR_DATA0                       (0)
#define ADC_REGULAR_DATA1                       (1)
#define ADC_REGULAR_DATA2                       (2)
#define ADC_REGULAR_DATA3                       (3)
#define ADC_REGULAR_DATA4                       (4)
#define ADC_REGULAR_DATA5                       (5)
#define ADC_REGULAR_DATA6                       (6)
#define ADC_REGULAR_DATA7                       (7)
#define ADC_REGULAR_DATA8                       (8)
#define ADC_REGULAR_DATA9                       (9)
#define ADC_REGULAR_DATA10                      (10)
#define ADC_REGULAR_DATA11                      (11)
#define ADC_REGULAR_DATA12                      (12)
#define ADC_REGULAR_DATA13                      (13)
#define ADC_REGULAR_DATA14                      (14)
#define ADC_REGULAR_DATA15                      (15)

#define IS_ADC_REGULAR_DATA(DATA)               ((DATA) < 16)


#define ADC_HP_DATA0                            (0)
#define ADC_HP_DATA1                            (1)
#define ADC_HP_DATA2                            (2)
#define ADC_HP_DATA3                            (3)

#define IS_ADC_HP_DATA(DATA)                    ((DATA) < 4)


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

#define ADC_PDMA_REGULAR_SINGLE                 (0x00000001)
#define ADC_PDMA_REGULAR_SUBGROUP               (0x00000002)
#define ADC_PDMA_REGULAR_CYCLE                  (0x00000004)

#define ADC_PDMA_HP_SINGLE                      (0x00000100)
#define ADC_PDMA_HP_SUBGROUP                    (0x00000200)
#define ADC_PDMA_HP_CYCLE                       (0x00000400)

#define IS_ADC_PDMA(PDMA)                       (((PDMA) == ADC_PDMA_REGULAR_SINGLE)   || \
                                                 ((PDMA) == ADC_PDMA_REGULAR_SUBGROUP) || \
                                                 ((PDMA) == ADC_PDMA_REGULAR_CYCLE)    || \
                                                 ((PDMA) == ADC_PDMA_HP_SINGLE)        || \
                                                 ((PDMA) == ADC_PDMA_HP_SUBGROUP)      || \
                                                 ((PDMA) == ADC_PDMA_HP_CYCLE))


#define IS_ADC_INPUT_SAMPLING_TIME(TIME)        ((TIME) <= 255)

#define IS_ADC_OFFSET(OFFSET)                   ((OFFSET) < 4096)

#define IS_ADC_REGULAR_RANK(RANK)               ((RANK) < 16)

#define IS_ADC_HP_RANK(RANK)                    ((RANK) < 4)

#define IS_ADC_REGULAR_LENGTH(LENGTH)           (((LENGTH) >= 1) && ((LENGTH) <= 16))
#define IS_ADC_REGULAR_SUB_LENGTH(SUB_LENGTH)   (((SUB_LENGTH) >= 1) && ((SUB_LENGTH) <= 16))

#define IS_ADC_HP_LENGTH(LENGTH)                (((LENGTH) >= 1) && ((LENGTH) <= 4))
#define IS_ADC_HP_SUB_LENGTH(SUB_LENGTH)        (((SUB_LENGTH) >= 1) && ((SUB_LENGTH) <= 4))

#define ADC_VREF_1V215                          (0ul << 4)
#define ADC_VREF_2V0                            (1ul << 4)
#define ADC_VREF_2V5                            (2ul << 4)
#define ADC_VREF_2V7                            (3ul << 4)

#define IS_ADC_VREF_SEL(SEL)                    ((SEL == ADC_VREF_1V215) || \
                                                 (SEL == ADC_VREF_2V0)   || \
                                                 (SEL == ADC_VREF_2V5)   || \
                                                 (SEL == ADC_VREF_2V7))

typedef enum
{
  ADC_ALIGN_RIGHT = (0 << 14),
  ADC_ALIGN_LEFT  = (1 << 14),
} ADC_ALIGN_Enum;

#define IS_ADC_ALIGN(ALIGN)                     (((ALIGN) == ADC_ALIGN_RIGHT) || ((ALIGN) == ADC_ALIGN_LEFT))
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

void ADC_SamplingTimeConfig(HT_ADC_TypeDef* HT_ADCn, u8 SampleClock); // Apply for the specific model only
void ADC_RegularChannelConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n, u8 Rank, u8 SampleClock);
void ADC_RegularGroupConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_MODE, u8 Length, u8 SubLength);
void ADC_RegularTrigConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_TRIG_x);

void ADC_HPChannelConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n, u8 Rank, u8 SampleClock);
void ADC_HPGroupConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_MODE, u8 Length, u8 SubLength);
void ADC_HPTrigConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_TRIG_x);

void ADC_ChannelDataAlign(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n, ADC_ALIGN_Enum ADC_ALIGN_x);
void ADC_ChannelOffsetValue(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n, u16 OffsetValue);
void ADC_ChannelOffsetCmd(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n, ControlStatus NewState);

void ADC_SoftwareStartConvCmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState);
void ADC_HPSoftwareStartConvCmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState);

u16 ADC_GetConversionData(HT_ADC_TypeDef* HT_ADCn, u8 ADC_REGULAR_DATAn);
u16 ADC_GetHPConversionData(HT_ADC_TypeDef* HT_ADCn, u8 ADC_HP_DATAn);

void ADC_IntConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_INT_x, ControlStatus NewState);
FlagStatus ADC_GetIntStatus(HT_ADC_TypeDef* HT_ADCn, u32 ADC_INT_x);
void ADC_ClearIntPendingBit(HT_ADC_TypeDef* HT_ADCn, u32 ADC_INT_x);
FlagStatus ADC_GetFlagStatus(HT_ADC_TypeDef* HT_ADCn, u32 ADC_FLAG_x);

void ADC_AWDConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_AWD_x);
void ADC_AWDSingleChannelConfig(HT_ADC_TypeDef* HT_ADCn, u8 ADC_CH_n);
void ADC_AWDThresholdsConfig(HT_ADC_TypeDef* HT_ADCn, u16 UPPER, u16 LOWER);

void ADC_PDMAConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_PDMA_x, ControlStatus NewState);

void ADC_VREFCmd(HT_ADC_TypeDef* HT_ADCn, ControlStatus NewState);
void ADC_VREFConfig(HT_ADC_TypeDef* HT_ADCn, u32 ADC_VREF_x);
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
