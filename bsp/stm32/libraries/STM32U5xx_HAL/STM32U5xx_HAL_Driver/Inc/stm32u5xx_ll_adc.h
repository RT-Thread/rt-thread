/**
  ******************************************************************************
  * @file    stm32u5xx_ll_adc.h
  * @author  MCD Application Team
  * @brief   Header file of ADC LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_LL_ADC_H
#define STM32U5xx_LL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (ADC1) || defined (ADC2) || defined (ADC4)

/** @defgroup ADC_LL ADC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Constants ADC Private Constants
  * @{
  */

/* Internal mask for ADC calibration:                                         */
/* Internal register offset for ADC calibration factors configuration */

/* To select into literals LL_ADC_CALIB_OFFSET, LL_ADC_CALIB_LINEARITY, ...   */
/* the relevant bits for:                                                     */
/* (concatenation of multiple bits used in different registers)               */
/* - ADC calibration configuration: configuration before calibration start    */
/* - ADC calibration factors: register offset                                 */
#define ADC_CALIB_FACTOR_OFFSET_REGOFFSET    (0x00000000UL) /* Register CALFACT defined as reference register */
#define ADC_CALIB_FACTOR_LINEARITY_REGOFFSET (0x00000001UL) /* Register CALFACT2 offset vs register CALFACT */
#define ADC_CALIB_FACTOR_REGOFFSET_MASK      (ADC_CALIB_FACTOR_OFFSET_REGOFFSET | ADC_CALIB_FACTOR_LINEARITY_REGOFFSET)
#define ADC_CALIB_MODE_MASK                  (ADC_CR_ADCALLIN)
#define ADC_CALIB_MODE_BINARY_MASK           (ADC_CALIB_FACTOR_REGOFFSET_MASK) /* Mask to get binary value of
                                                                                  calibration mode: 0 for offset,
                                                                                                    1 for linearity */


/* Internal mask for ADC group regular sequencer:                             */
/* To select into literal LL_ADC_REG_RANK_x the relevant bits for:            */
/* - sequencer register offset                                                */
/* - sequencer rank bits position into the selected register                  */

/* Internal register offset for ADC group regular sequencer configuration */
/* (offset placed into a spare area of literal definition) */
#define ADC_SQR1_REGOFFSET              (0x00000000UL)
#define ADC_SQR2_REGOFFSET              (0x00000100UL)
#define ADC_SQR3_REGOFFSET              (0x00000200UL)
#define ADC_SQR4_REGOFFSET              (0x00000300UL)

#define ADC_REG_SQRX_REGOFFSET_MASK     (ADC_SQR1_REGOFFSET\
                                         | ADC_SQR2_REGOFFSET | ADC_SQR3_REGOFFSET | ADC_SQR4_REGOFFSET)
#define ADC_SQRX_REGOFFSET_POS          (8UL) /* Position of bits ADC_SQRx_REGOFFSET in ADC_REG_SQRX_REGOFFSET_MASK */
#define ADC_REG_RANK_ID_SQRX_MASK       (ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0)

/* Definition of ADC group regular sequencer bits information to be inserted  */
/* into ADC group regular sequencer ranks literals definition.                */
#define ADC_REG_RANK_1_SQRX_BITOFFSET_POS  ( 6UL) /* Equivalent to bitfield "ADC_SQR1_SQ1" position in register    */
#define ADC_REG_RANK_2_SQRX_BITOFFSET_POS  (12UL) /* Equivalent to bitfield "ADC_SQR1_SQ2" position in register    */
#define ADC_REG_RANK_3_SQRX_BITOFFSET_POS  (18UL) /* Equivalent to bitfield "ADC_SQR1_SQ3" position in register    */
#define ADC_REG_RANK_4_SQRX_BITOFFSET_POS  (24UL) /* Equivalent to bitfield "ADC_SQR1_SQ4" position in register    */
#define ADC_REG_RANK_5_SQRX_BITOFFSET_POS  ( 0UL) /* Equivalent to bitfield "ADC_SQR2_SQ5" position in register    */
#define ADC_REG_RANK_6_SQRX_BITOFFSET_POS  ( 6UL) /* Equivalent to bitfield "ADC_SQR2_SQ6" position in register    */
#define ADC_REG_RANK_7_SQRX_BITOFFSET_POS  (12UL) /* Equivalent to bitfield "ADC_SQR2_SQ7" position in register    */
#define ADC_REG_RANK_8_SQRX_BITOFFSET_POS  (18UL) /* Equivalent to bitfield "ADC_SQR2_SQ8" position in register    */
#define ADC_REG_RANK_9_SQRX_BITOFFSET_POS  (24UL) /* Equivalent to bitfield "ADC_SQR2_SQ9" position in register    */
#define ADC_REG_RANK_10_SQRX_BITOFFSET_POS ( 0UL) /* Equivalent to bitfield "ADC_SQR3_SQ10" position in register   */
#define ADC_REG_RANK_11_SQRX_BITOFFSET_POS ( 6UL) /* Equivalent to bitfield "ADC_SQR3_SQ11" position in register   */
#define ADC_REG_RANK_12_SQRX_BITOFFSET_POS (12UL) /* Equivalent to bitfield "ADC_SQR3_SQ12" position in register   */
#define ADC_REG_RANK_13_SQRX_BITOFFSET_POS (18UL) /* Equivalent to bitfield "ADC_SQR3_SQ13" position in register   */
#define ADC_REG_RANK_14_SQRX_BITOFFSET_POS (24UL) /* Equivalent to bitfield "ADC_SQR3_SQ14" position in register   */
#define ADC_REG_RANK_15_SQRX_BITOFFSET_POS ( 0UL) /* Equivalent to bitfield "ADC_SQR4_SQ15" position in register   */
#define ADC_REG_RANK_16_SQRX_BITOFFSET_POS ( 6UL) /* Equivalent to bitfield "ADC_SQR4_SQ16" position in register   */

#define ADC4_REG_RANK_1_SQRX_BITOFFSET_POS ( 0UL) /* Equivalent to bitfield "ADC4_CHSELR_SQ1" position in register */
#define ADC4_REG_RANK_2_SQRX_BITOFFSET_POS ( 4UL) /* Equivalent to bitfield "ADC4_CHSELR_SQ2" position in register */
#define ADC4_REG_RANK_3_SQRX_BITOFFSET_POS ( 8UL) /* Equivalent to bitfield "ADC4_CHSELR_SQ3" position in register */
#define ADC4_REG_RANK_4_SQRX_BITOFFSET_POS (12UL) /* Equivalent to bitfield "ADC4_CHSELR_SQ4" position in register */
#define ADC4_REG_RANK_5_SQRX_BITOFFSET_POS (16UL) /* Equivalent to bitfield "ADC4_CHSELR_SQ5" position in register */
#define ADC4_REG_RANK_6_SQRX_BITOFFSET_POS (20UL) /* Equivalent to bitfield "ADC4_CHSELR_SQ6" position in register */
#define ADC4_REG_RANK_7_SQRX_BITOFFSET_POS (24UL) /* Equivalent to bitfield "ADC4_CHSELR_SQ7" position in register */
#define ADC4_REG_RANK_8_SQRX_BITOFFSET_POS (28UL) /* Equivalent to bitfield "ADC4_CHSELR_SQ8" position in register */

/* Internal mask for ADC group injected sequencer:                            */
/* To select into literal LL_ADC_INJ_RANK_x the relevant bits for:            */
/* - data register offset                                                     */
/* - sequencer rank bits position into the selected register                  */

/* Internal register offset for ADC group injected data register */
/* (offset placed into a spare area of literal definition) */
#define ADC_JDR1_REGOFFSET             (0x00000000UL)
#define ADC_JDR2_REGOFFSET             (0x00000100UL)
#define ADC_JDR3_REGOFFSET             (0x00000200UL)
#define ADC_JDR4_REGOFFSET             (0x00000300UL)

#define ADC_INJ_JDRX_REGOFFSET_MASK    (ADC_JDR1_REGOFFSET\
                                        | ADC_JDR2_REGOFFSET | ADC_JDR3_REGOFFSET | ADC_JDR4_REGOFFSET)
#define ADC_INJ_RANK_ID_JSQR_MASK      (ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0)
#define ADC_JDRX_REGOFFSET_POS         (8UL) /* Position of bits ADC_JDRx_REGOFFSET in ADC_INJ_JDRX_REGOFFSET_MASK */

/* Definition of ADC group injected sequencer bits information to be inserted */
/* into ADC group injected sequencer ranks literals definition.               */
#define ADC_INJ_RANK_1_JSQR_BITOFFSET_POS  (ADC_JSQR_JSQ1_Pos)
#define ADC_INJ_RANK_2_JSQR_BITOFFSET_POS  (ADC_JSQR_JSQ2_Pos)
#define ADC_INJ_RANK_3_JSQR_BITOFFSET_POS  (ADC_JSQR_JSQ3_Pos)
#define ADC_INJ_RANK_4_JSQR_BITOFFSET_POS  (ADC_JSQR_JSQ4_Pos)

#define ADC_TR1_HT1_BITOFFSET_POS         (16UL) /* Equivalent to bitfield "ADC4_TR1_HT1" position in register        */
#define ADC4_CHSELR_CHSEL0_BITOFFSET_POS  ( 0UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL0" position in register  */
#define ADC4_CHSELR_CHSEL1_BITOFFSET_POS  ( 1UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL1" position in register  */
#define ADC4_CHSELR_CHSEL2_BITOFFSET_POS  ( 2UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL2" position in register  */
#define ADC4_CHSELR_CHSEL3_BITOFFSET_POS  ( 3UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL3" position in register  */
#define ADC4_CHSELR_CHSEL4_BITOFFSET_POS  ( 4UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL4" position in register  */
#define ADC4_CHSELR_CHSEL5_BITOFFSET_POS  ( 5UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL5" position in register  */
#define ADC4_CHSELR_CHSEL6_BITOFFSET_POS  ( 6UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL6" position in register  */
#define ADC4_CHSELR_CHSEL7_BITOFFSET_POS  ( 7UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL7" position in register  */
#define ADC4_CHSELR_CHSEL8_BITOFFSET_POS  ( 8UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL8" position in register  */
#define ADC4_CHSELR_CHSEL9_BITOFFSET_POS  ( 9UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL9" position in register  */
#define ADC4_CHSELR_CHSEL10_BITOFFSET_POS (10UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL10" position in register */
#define ADC4_CHSELR_CHSEL11_BITOFFSET_POS (11UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL11" position in register */
#define ADC4_CHSELR_CHSEL12_BITOFFSET_POS (12UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL12" position in register */
#define ADC4_CHSELR_CHSEL13_BITOFFSET_POS (13UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL13" position in register */
#define ADC4_CHSELR_CHSEL14_BITOFFSET_POS (14UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL14" position in register */
#define ADC4_CHSELR_CHSEL15_BITOFFSET_POS (15UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL15" position in register */
#define ADC4_CHSELR_CHSEL16_BITOFFSET_POS (16UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL16" position in register */
#define ADC4_CHSELR_CHSEL17_BITOFFSET_POS (17UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL17" position in register */
#define ADC4_CHSELR_CHSEL18_BITOFFSET_POS (18UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL18" position in register */
#define ADC4_CHSELR_CHSEL19_BITOFFSET_POS (19UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL19" position in register */
#define ADC4_CHSELR_CHSEL20_BITOFFSET_POS (20UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL20" position in register */
#define ADC4_CHSELR_CHSEL21_BITOFFSET_POS (21UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL21" position in register */
#define ADC4_CHSELR_CHSEL22_BITOFFSET_POS (22UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL22" position in register */
#define ADC4_CHSELR_CHSEL23_BITOFFSET_POS (23UL) /* Equivalent to bitfield "ADC4_CHSELR_CHSEL23" position in register */
#define ADC4_SMPR_SMP1_BITOFFSET_POS      ( 0UL) /* Equivalent to bitfield "ADC4_SMPR_SMP1" position in register      */
#define ADC4_SMPR_SMP2_BITOFFSET_POS      ( 4UL) /* Equivalent to bitfield "ADC4_SMPR_SMP2" position in register      */
#define ADC4_SMPR_SMPSEL0_BITOFFSET_POS   ( 8UL) /* Equivalent to bitfield "ADC4_SMPR_SMPSEL0" position in register   */

/* Internal mask for ADC group regular trigger:                               */
/* To select into literal LL_ADC_REG_TRIG_x the relevant bits for:            */
/* - regular trigger source                                                   */
/* - regular trigger edge                                                     */
#define ADC_REG_TRIG_EXT_EDGE_DEFAULT   (ADC_CFGR1_EXTEN_0) /* Trigger edge set to rising edge (default setting
                                                               for compatibility with some ADC on other STM32
                                                               families having this setting set by HW default value) */

/* Mask containing trigger source masks for each of possible                  */
/* trigger edge selection duplicated with shifts [0; 4; 8; 12]                */
/* corresponding to {SW start; ext trigger; ext trigger; ext trigger}.        */
#define ADC_REG_TRIG_SOURCE_MASK            (((LL_ADC_REG_TRIG_SOFTWARE & ADC_CFGR1_EXTSEL) << (4U * 0UL)) | \
                                             ((ADC_CFGR1_EXTSEL)                            << (4U * 1UL)) | \
                                             ((ADC_CFGR1_EXTSEL)                            << (4U * 2UL)) | \
                                             ((ADC_CFGR1_EXTSEL)                            << (4U * 3UL))  )

#define ADC4_REG_TRIG_SOURCE_MASK            (((LL_ADC_REG_TRIG_SOFTWARE & ADC4_CFGR1_EXTSEL) << (4U * 0UL)) | \
                                              ((ADC4_CFGR1_EXTSEL)                            << (4U * 1UL)) | \
                                              ((ADC4_CFGR1_EXTSEL)                            << (4U * 2UL)) | \
                                              ((ADC4_CFGR1_EXTSEL)                            << (4U * 3UL))  )

/* Mask containing trigger edge masks for each of possible                    */
/* trigger edge selection duplicated with shifts [0; 4; 8; 12]                */
/* corresponding to {SW start; ext trigger; ext trigger; ext trigger}.        */
#define ADC_REG_TRIG_EDGE_MASK              (((LL_ADC_REG_TRIG_SOFTWARE & ADC_CFGR1_EXTEN) << (4U * 0UL)) | \
                                             ((ADC_REG_TRIG_EXT_EDGE_DEFAULT)             << (4U * 1UL)) | \
                                             ((ADC_REG_TRIG_EXT_EDGE_DEFAULT)             << (4U * 2UL)) | \
                                             ((ADC_REG_TRIG_EXT_EDGE_DEFAULT)             << (4U * 3UL))  )

/* Definition of ADC group regular trigger bits information.                  */
#define ADC_REG_TRIG_EXTSEL_BITOFFSET_POS   ( 6UL) /* Value equivalent to bitfield "ADC_CFGR1_EXTSEL"
                                                      position in register */
#define ADC_REG_TRIG_EXTEN_BITOFFSET_POS    (10UL) /* Value equivalent to bitfield "ADC_CFGR1_EXTEN"
                                                      position in register */

/* Internal mask for ADC group injected trigger:                              */
/* To select into literal LL_ADC_INJ_TRIG_x the relevant bits for:            */
/* - injected trigger source                                                  */
/* - injected trigger edge                                                    */
#define ADC_INJ_TRIG_EXT_EDGE_DEFAULT      (ADC_JSQR_JEXTEN_0) /* Trigger edge set to rising edge (default setting for
                                                                  compatibility with some ADC on other STM32 families
                                                                  having this setting set by HW default value) */

/* Mask containing trigger source masks for each of possible                  */
/* trigger edge selection duplicated with shifts [0; 4; 8; 12]                */
/* corresponding to {SW start; ext trigger; ext trigger; ext trigger}.        */
#define ADC_INJ_TRIG_SOURCE_MASK            (((LL_ADC_INJ_TRIG_SOFTWARE & ADC_JSQR_JEXTSEL) << (4U * 0UL)) | \
                                             ((ADC_JSQR_JEXTSEL)                             << (4U * 1UL)) | \
                                             ((ADC_JSQR_JEXTSEL)                             << (4U * 2UL)) | \
                                             ((ADC_JSQR_JEXTSEL)                             << (4U * 3UL))  )

/* Mask containing trigger edge masks for each of possible                    */
/* trigger edge selection duplicated with shifts [0; 4; 8; 12]                */
/* corresponding to {SW start; ext trigger; ext trigger; ext trigger}.        */
#define ADC_INJ_TRIG_EDGE_MASK              (((LL_ADC_INJ_TRIG_SOFTWARE & ADC_JSQR_JEXTEN) << (4U * 0UL)) | \
                                             ((ADC_INJ_TRIG_EXT_EDGE_DEFAULT)              << (4U * 1UL)) | \
                                             ((ADC_INJ_TRIG_EXT_EDGE_DEFAULT)              << (4U * 2UL)) | \
                                             ((ADC_INJ_TRIG_EXT_EDGE_DEFAULT)              << (4U * 3UL))  )

/* Definition of ADC group injected trigger bits information.                 */
#define ADC_INJ_TRIG_EXTSEL_BITOFFSET_POS  ( 2UL) /* Value equivalent to bitfield "ADC_JSQR_JEXTSEL"
                                                     position in register */
#define ADC_INJ_TRIG_EXTEN_BITOFFSET_POS   ( 6UL) /* Value equivalent to bitfield "ADC_JSQR_JEXTEN"
                                                     position in register */

/* Internal mask for ADC channel:                                             */
/* To select into literal LL_ADC_CHANNEL_x the relevant bits for:             */
/* - channel identifier defined by number                                     */
/* - channel identifier defined by bitfield                                   */
/* - channel differentiation between external channels (connected to          */
/*   GPIO pins) and internal channels (connected to internal paths)           */
/* - channel sampling time defined by SMPRx register offset                   */
/*   and SMPx bits positions into SMPRx register                              */
#define ADC_CHANNEL_ID_NUMBER_MASK         (ADC_CFGR1_AWD1CH)
#define ADC_CHANNEL_ID_BITFIELD_MASK       (ADC_AWD2CR_AWD2CH)
#define ADC_CHANNEL_ID_OFFSET_NUMBER_MASK  (ADC_OFR1_OFFSET1_CH)
#define ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS (26UL)  /* Value equivalent to bitfield "ADC_CHANNEL_ID_NUMBER_MASK"
                                                       position in register                                       */
#define ADC_CHANNEL_ID_MASK    (ADC_CHANNEL_ID_NUMBER_MASK | ADC_CHANNEL_ID_BITFIELD_MASK \
                                | ADC_CHANNEL_ID_INTERNAL_CH_MASK) /* Equivalent mask of ADC_CHANNEL_NUMBER_MASK
                                                                      aligned on register LSB (bit 0) */
#define ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0 (ADC_SQR2_SQ5) /* Equivalent to shift: (ADC_CHANNEL_NUMBER_MASK >>
                                                            [Position of bitfield "ADC_CHANNEL_NUMBER_MASK"
                                                             in register])                                    */

/* Channel differentiation between external and internal channels */
#define ADC_CHANNEL_ID_INTERNAL_CH         (0x80000000UL) /* Marker of internal channel */
#define ADC_CHANNEL_ID_INTERNAL_CH_MASK    (ADC_CHANNEL_ID_INTERNAL_CH)

/* Internal register offset for ADC channel sampling time configuration */
/* (offset placed into a spare area of literal definition) */
#define ADC_SMPR1_REGOFFSET                (0x00000000UL)
#define ADC_SMPR2_REGOFFSET                (0x02000000UL)
#define ADC_CHANNEL_SMPRX_REGOFFSET_MASK   (ADC_SMPR1_REGOFFSET | ADC_SMPR2_REGOFFSET)
#define ADC_SMPRX_REGOFFSET_POS            (25UL) /* Position of bits ADC_SMPRx_REGOFFSET in
                                                     ADC_CHANNEL_SMPRX_REGOFFSET_MASK */

#define ADC4_CHANNEL_ID_BITFIELD_MASK   (ADC_CHSELR_CHSEL)
#define ADC4_SAMPLING_TIME_CH_MASK      (ADC4_CHANNEL_ID_BITFIELD_MASK << ADC4_SMPR_SMPSEL0_BITOFFSET_POS)
#define ADC4_CHANNEL_ID_NUMBER_MASK_SEQ (ADC_CHSELR_SQ1 \
                                         << ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS) /* Value equivalent to
                                                                                    ADC_CHANNEL_ID_NUMBER_MASK with
                                                                                    reduced range: on this STM32 series,
                                                                                    ADC group regular sequencer, if set
                                                                                    to mode "fully configurable", can
                                                                                    contain channels with a restricted
                                                                                    channel number. */

/* Definition of channels ID number information to be inserted into           */
/* channels literals definition.                                              */
#define ADC_CHANNEL_0_NUMBER      (0x00000000UL)
#define ADC_CHANNEL_1_NUMBER      (ADC_CFGR1_AWD1CH_0)
#define ADC_CHANNEL_2_NUMBER      (ADC_CFGR1_AWD1CH_1)
#define ADC_CHANNEL_3_NUMBER      (ADC_CFGR1_AWD1CH_1 | ADC_CFGR1_AWD1CH_0)
#define ADC_CHANNEL_4_NUMBER      (ADC_CFGR1_AWD1CH_2)
#define ADC_CHANNEL_5_NUMBER      (ADC_CFGR1_AWD1CH_2 | ADC_CFGR1_AWD1CH_0)
#define ADC_CHANNEL_6_NUMBER      (ADC_CFGR1_AWD1CH_2 | ADC_CFGR1_AWD1CH_1)
#define ADC_CHANNEL_7_NUMBER      (ADC_CFGR1_AWD1CH_2 | ADC_CFGR1_AWD1CH_1 | ADC_CFGR1_AWD1CH_0)
#define ADC_CHANNEL_8_NUMBER      (ADC_CFGR1_AWD1CH_3)
#define ADC_CHANNEL_9_NUMBER      (ADC_CFGR1_AWD1CH_3 | ADC_CFGR1_AWD1CH_0)
#define ADC_CHANNEL_10_NUMBER     (ADC_CFGR1_AWD1CH_3 | ADC_CFGR1_AWD1CH_1)
#define ADC_CHANNEL_11_NUMBER     (ADC_CFGR1_AWD1CH_3 | ADC_CFGR1_AWD1CH_1 | ADC_CFGR1_AWD1CH_0)
#define ADC_CHANNEL_12_NUMBER     (ADC_CFGR1_AWD1CH_3 | ADC_CFGR1_AWD1CH_2)
#define ADC_CHANNEL_13_NUMBER     (ADC_CFGR1_AWD1CH_3 | ADC_CFGR1_AWD1CH_2 | ADC_CFGR1_AWD1CH_0)
#define ADC_CHANNEL_14_NUMBER     (ADC_CFGR1_AWD1CH_3 | ADC_CFGR1_AWD1CH_2 | ADC_CFGR1_AWD1CH_1)
#define ADC_CHANNEL_15_NUMBER     (ADC_CFGR1_AWD1CH_3 | ADC_CFGR1_AWD1CH_2 | ADC_CFGR1_AWD1CH_1 | ADC_CFGR1_AWD1CH_0)
#define ADC_CHANNEL_16_NUMBER     (ADC_CFGR1_AWD1CH_4)
#define ADC_CHANNEL_17_NUMBER     (ADC_CFGR1_AWD1CH_4 | ADC_CFGR1_AWD1CH_0)
#define ADC_CHANNEL_18_NUMBER     (ADC_CFGR1_AWD1CH_4 | ADC_CFGR1_AWD1CH_1)
#define ADC_CHANNEL_19_NUMBER     (ADC_CFGR1_AWD1CH_4 | ADC_CFGR1_AWD1CH_1 | ADC_CFGR1_AWD1CH_0)
#if defined(ADC4)
#define ADC_CHANNEL_20_NUMBER     (ADC_CFGR1_AWD1CH_4 | ADC_CFGR1_AWD1CH_2 )
#define ADC_CHANNEL_21_NUMBER     (ADC_CFGR1_AWD1CH_4 | ADC_CFGR1_AWD1CH_2 | ADC_CFGR1_AWD1CH_0)
#define ADC_CHANNEL_22_NUMBER     (ADC_CFGR1_AWD1CH_4 | ADC_CFGR1_AWD1CH_2 | ADC_CFGR1_AWD1CH_1)
#define ADC_CHANNEL_23_NUMBER     (ADC_CFGR1_AWD1CH_4 | ADC_CFGR1_AWD1CH_2 | ADC_CFGR1_AWD1CH_1 | ADC_CFGR1_AWD1CH_0)
#endif /* ADC4 */
/* Definition of channels ID bitfield information to be inserted into         */
/* channels literals definition.                                              */
#define ADC_CHANNEL_0_BITFIELD             (ADC_AWD2CR_AWD2CH_0)
#define ADC_CHANNEL_1_BITFIELD             (ADC_AWD2CR_AWD2CH_1)
#define ADC_CHANNEL_2_BITFIELD             (ADC_AWD2CR_AWD2CH_2)
#define ADC_CHANNEL_3_BITFIELD             (ADC_AWD2CR_AWD2CH_3)
#define ADC_CHANNEL_4_BITFIELD             (ADC_AWD2CR_AWD2CH_4)
#define ADC_CHANNEL_5_BITFIELD             (ADC_AWD2CR_AWD2CH_5)
#define ADC_CHANNEL_6_BITFIELD             (ADC_AWD2CR_AWD2CH_6)
#define ADC_CHANNEL_7_BITFIELD             (ADC_AWD2CR_AWD2CH_7)
#define ADC_CHANNEL_8_BITFIELD             (ADC_AWD2CR_AWD2CH_8)
#define ADC_CHANNEL_9_BITFIELD             (ADC_AWD2CR_AWD2CH_9)
#define ADC_CHANNEL_10_BITFIELD            (ADC_AWD2CR_AWD2CH_10)
#define ADC_CHANNEL_11_BITFIELD            (ADC_AWD2CR_AWD2CH_11)
#define ADC_CHANNEL_12_BITFIELD            (ADC_AWD2CR_AWD2CH_12)
#define ADC_CHANNEL_13_BITFIELD            (ADC_AWD2CR_AWD2CH_13)
#define ADC_CHANNEL_14_BITFIELD            (ADC_AWD2CR_AWD2CH_14)
#define ADC_CHANNEL_15_BITFIELD            (ADC_AWD2CR_AWD2CH_15)
#define ADC_CHANNEL_16_BITFIELD            (ADC_AWD2CR_AWD2CH_16)
#define ADC_CHANNEL_17_BITFIELD            (ADC_AWD2CR_AWD2CH_17)
#define ADC_CHANNEL_18_BITFIELD            (ADC_AWD2CR_AWD2CH_18)
#define ADC_CHANNEL_19_BITFIELD            (ADC_AWD2CR_AWD2CH_19)
#define ADC_CHANNEL_20_BITFIELD            (ADC_AWD2CR_AWD2CH_20)
#define ADC_CHANNEL_21_BITFIELD            (ADC_AWD2CR_AWD2CH_21)
#define ADC_CHANNEL_22_BITFIELD            (ADC_AWD2CR_AWD2CH_22)
#define ADC_CHANNEL_23_BITFIELD            (ADC_AWD2CR_AWD2CH_23)

#define ADC4_CHANNEL_0_BITFIELD             (ADC_CHSELR_CHSEL0)
#define ADC4_CHANNEL_1_BITFIELD             (ADC_CHSELR_CHSEL1)
#define ADC4_CHANNEL_2_BITFIELD             (ADC_CHSELR_CHSEL2)
#define ADC4_CHANNEL_3_BITFIELD             (ADC_CHSELR_CHSEL3)
#define ADC4_CHANNEL_4_BITFIELD             (ADC_CHSELR_CHSEL4)
#define ADC4_CHANNEL_5_BITFIELD             (ADC_CHSELR_CHSEL5)
#define ADC4_CHANNEL_6_BITFIELD             (ADC_CHSELR_CHSEL6)
#define ADC4_CHANNEL_7_BITFIELD             (ADC_CHSELR_CHSEL7)
#define ADC4_CHANNEL_8_BITFIELD             (ADC_CHSELR_CHSEL8)
#define ADC4_CHANNEL_9_BITFIELD             (ADC_CHSELR_CHSEL9)
#define ADC4_CHANNEL_10_BITFIELD            (ADC_CHSELR_CHSEL10)
#define ADC4_CHANNEL_11_BITFIELD            (ADC_CHSELR_CHSEL11)
#define ADC4_CHANNEL_12_BITFIELD            (ADC_CHSELR_CHSEL12)
#define ADC4_CHANNEL_13_BITFIELD            (ADC_CHSELR_CHSEL13)
#define ADC4_CHANNEL_14_BITFIELD            (ADC_CHSELR_CHSEL14)
#define ADC4_CHANNEL_15_BITFIELD            (ADC_CHSELR_CHSEL15)
#define ADC4_CHANNEL_16_BITFIELD            (ADC_CHSELR_CHSEL16)
#define ADC4_CHANNEL_17_BITFIELD            (ADC_CHSELR_CHSEL17)
#define ADC4_CHANNEL_18_BITFIELD            (ADC_CHSELR_CHSEL18)
#define ADC4_CHANNEL_19_BITFIELD            (ADC_CHSELR_CHSEL19)
#define ADC4_CHANNEL_20_BITFIELD            (ADC_CHSELR_CHSEL20)
#define ADC4_CHANNEL_21_BITFIELD            (ADC_CHSELR_CHSEL21)
#define ADC4_CHANNEL_22_BITFIELD            (ADC_CHSELR_CHSEL22)
#define ADC4_CHANNEL_23_BITFIELD            (ADC_CHSELR_CHSEL23)

/* Definition of channels sampling time information to be inserted into       */
/* channels literals definition.                                              */
#define ADC_CHANNEL_0_SMP    (ADC_SMPR1_REGOFFSET ) /* Channel is with "ADC_SMPR1_SMP0" register  */
#define ADC_CHANNEL_1_SMP    (ADC_SMPR1_REGOFFSET ) /* Channel is with "ADC_SMPR1_SMP1" register  */
#define ADC_CHANNEL_2_SMP    (ADC_SMPR1_REGOFFSET ) /* Channel is with "ADC_SMPR1_SMP2" register  */
#define ADC_CHANNEL_3_SMP    (ADC_SMPR1_REGOFFSET ) /* Channel is with "ADC_SMPR1_SMP3" register  */
#define ADC_CHANNEL_4_SMP    (ADC_SMPR1_REGOFFSET ) /* Channel is with "ADC_SMPR1_SMP4" register  */
#define ADC_CHANNEL_5_SMP    (ADC_SMPR1_REGOFFSET ) /* Channel is with "ADC_SMPR1_SMP5" register  */
#define ADC_CHANNEL_6_SMP    (ADC_SMPR1_REGOFFSET ) /* Channel is with "ADC_SMPR1_SMP6" register  */
#define ADC_CHANNEL_7_SMP    (ADC_SMPR1_REGOFFSET ) /* Channel is with "ADC_SMPR1_SMP7" register  */
#define ADC_CHANNEL_8_SMP    (ADC_SMPR1_REGOFFSET ) /* Channel is with "ADC_SMPR1_SMP8" register  */
#define ADC_CHANNEL_9_SMP    (ADC_SMPR1_REGOFFSET ) /* Channel is with "ADC_SMPR1_SMP9" register  */
#define ADC_CHANNEL_10_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP10" register */
#define ADC_CHANNEL_11_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP11" register */
#define ADC_CHANNEL_12_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP12" register */
#define ADC_CHANNEL_13_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP13" register */
#define ADC_CHANNEL_14_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP14" register */
#define ADC_CHANNEL_15_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP15" register */
#define ADC_CHANNEL_16_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP16" register */
#define ADC_CHANNEL_17_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP17" register */
#define ADC_CHANNEL_18_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP18" register */
#define ADC_CHANNEL_19_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP19" register */
#define ADC_CHANNEL_20_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP20" register */
#define ADC_CHANNEL_21_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP21" register */
#define ADC_CHANNEL_22_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP22" register */
#define ADC_CHANNEL_23_SMP   (ADC_SMPR2_REGOFFSET ) /* Channel is with "ADC_SMPR2_SMP23" register */

/* Internal mask for ADC mode single or differential ended:                   */
/* To select into literals LL_ADC_SINGLE_ENDED or LL_ADC_SINGLE_DIFFERENTIAL  */
/* the relevant bits for:                                                     */
/* (concatenation of multiple bits used in different registers)               */
/* - ADC calibration: calibration start, calibration factor get or set        */
/* - ADC channels: set each ADC channel ending mode                           */
#define ADC_SINGLEDIFF_CALIB_FACTOR_MASK   (ADC_CALFACT2_CALFACT)
#define ADC_CALFACT2_CALFACT_S   (0x0000FFFFUL)
#define ADC_CALFACT2_CALFACT_D   (0xFFFF0000UL)
#define ADC_SINGLEDIFF_CHANNEL_MASK        (ADC_CHANNEL_ID_BITFIELD_MASK) /* Equivalent to ADC_DIFSEL_DIFSEL          */
#define ADC_SINGLEDIFF_CHANNEL_SHIFT_MASK  (ADC_CALFACT_I_APB_ADDR_4   \
                                            | ADC_CALFACT_I_APB_ADDR_3)  /* Bits chosen to perform of shift when single
                                                                            mode is selected, shift value out of
                                                                            channels bits range. */
#define ADC_SINGLEDIFF_CALIB_F_BIT_D_MASK   (0x00010000UL)   /* Selection of 1 bit to discriminate differential mode:
                                                                mask of bit                                           */
#define ADC_SINGLEDIFF_CALIB_F_BIT_D_POS    (16UL)           /* Selection of 1 bit to discriminate differential mode:
                                                                position of bit                                       */
#define ADC_SINGLEDIFF_CALIB_F_BIT_D_SHIFT4 (ADC_SINGLEDIFF_CALIB_F_BIT_D_POS - 4UL) /* Shift of bit
                                                                                        ADC_SINGLEDIFF_CALIB_F_BIT_D
                                                                                        to position to perform a shift
                                                                                        of 4 ranks */

/* Internal mask for ADC analog watchdog:                                     */
/* To select into literals LL_ADC_AWD_CHANNELx_xxx the relevant bits for:     */
/* (concatenation of multiple bits used in different analog watchdogs,        */
/* (feature of several watchdogs not available on all STM32 families)).       */
/* - analog watchdog 1: monitored channel defined by number,                  */
/*   selection of ADC group (ADC groups regular and-or injected).             */
/* - analog watchdog 2 and 3: monitored channel defined by bitfield, no       */
/*   selection on groups.                                                     */

/* Internal register offset for ADC analog watchdog channel configuration */
#define ADC_AWD_CR1_REGOFFSET          (0x00000000UL)
#define ADC_AWD_CR2_REGOFFSET          (0x01000000UL)
#define ADC_AWD_CR3_REGOFFSET          (0x02000000UL)

/* Register offset gap between AWD1 and AWD2-AWD3 configuration registers */
/* (Set separately as ADC_AWD_CRX_REGOFFSET to spare 32 bits space */
#define ADC_AWD_CR12_REGOFFSETGAP_MASK (ADC_AWD2CR_AWD2CH_0)
#define ADC_AWD_CR12_REGOFFSETGAP_VAL  (0x00000024UL)

#define ADC_AWD_CRX_REGOFFSET_MASK     (ADC_AWD_CR1_REGOFFSET | ADC_AWD_CR2_REGOFFSET | ADC_AWD_CR3_REGOFFSET)

#define ADC_AWD_CR1_CHANNEL_MASK       (ADC_CFGR1_AWD1CH | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)
#define ADC_AWD_CHANNEL_MASK           (ADC_CHANNEL_ID_NUMBER_MASK)
#define ADC_AWD_CR23_CHANNEL_MASK      (ADC_AWD2CR_AWD2CH)
#define ADC_AWD_CR_ALL_CHANNEL_MASK    (ADC_AWD_CR1_CHANNEL_MASK | ADC_AWD_CR23_CHANNEL_MASK)

#define ADC_AWD_CRX_REGOFFSET_POS      (24UL) /* Position of bits ADC_AWD_CRx_REGOFFSET in ADC_AWD_CRX_REGOFFSET_MASK*/

/* Internal register offset for ADC analog watchdog threshold configuration */
#define ADC_AWD_TR1_REGOFFSET          (ADC_AWD_CR1_REGOFFSET)
#define ADC_AWD_TR2_REGOFFSET          (ADC_AWD_CR2_REGOFFSET)
#define ADC_AWD_TR3_REGOFFSET          (ADC_AWD_CR3_REGOFFSET)
#define ADC_AWD_TRX_REGOFFSET_MASK     (ADC_AWD_TR1_REGOFFSET | ADC_AWD_TR2_REGOFFSET | ADC_AWD_TR3_REGOFFSET)
#define ADC_AWD_TRX_REGOFFSET_POS      (ADC_AWD_CRX_REGOFFSET_POS)   /* Position of bits ADC_TRx_REGOFFSET in
                                                                        ADC_AWD_TRX_REGOFFSET_MASK                   */

#define ADC_AWD_TRX_BIT_HIGH_MASK      (0x00010000UL)                   /* Selection of 1 bit to discriminate
                                                                           threshold high: mask of bit               */
#define ADC_AWD_TRX_BIT_HIGH_POS       (16UL)                           /* Selection of 1 bit to discriminate
                                                                           threshold high: position of bit           */
#define ADC_AWD_TRX_BIT_HIGH_SHIFT4    (ADC_AWD_TRX_BIT_HIGH_POS - 4UL) /* Shift of bit ADC_AWD_TRX_BIT_HIGH
                                                                           to position to perform a shift of 4 ranks */
#define ADC_AWD_TRX_REGOFFSET_BITOFFSET_POS (20UL)

/* Register offset gap between AWD1 and AWD2-AWD3 thresholds registers */
/* (Set separately as ADC_AWD_TRX_REGOFFSET to spare 32 bits space */
#define ADC_AWD_TR12_REGOFFSETGAP_MASK     (ADC_AWD2CR_AWD2CH_0)
#define ADC_AWD_TR12_REGOFFSETGAP_VAL      (0x00000022UL)

/* Legacy literals */
#define LL_ADC_AWD1_TR                      LL_ADC_AWD1
#define LL_ADC_AWD2_TR                      LL_ADC_AWD2
#define LL_ADC_AWD3_TR                      LL_ADC_AWD3

/* Internal mask for ADC offset:                                              */
/* Internal register offset for ADC offset number configuration */
#define ADC_OFR1_REGOFFSET                 (0x00000000UL)
#define ADC_OFR2_REGOFFSET                 (0x00000001UL)
#define ADC_OFR3_REGOFFSET                 (0x00000002UL)
#define ADC_OFR4_REGOFFSET                 (0x00000003UL)
#define ADC_OFRx_REGOFFSET_MASK            (ADC_OFR1_REGOFFSET\
                                            | ADC_OFR2_REGOFFSET | ADC_OFR3_REGOFFSET | ADC_OFR4_REGOFFSET)

/* ADC registers bits positions */
#define ADC_CFGR_RES_BITOFFSET_POS     (ADC_CFGR1_RES_Pos)
#define ADC_CFGR_AWD1SGL_BITOFFSET_POS (ADC_CFGR1_AWD1SGL_Pos)
#define ADC_CFGR_AWD1EN_BITOFFSET_POS  (ADC_CFGR1_AWD1EN_Pos)
#define ADC_CFGR_JAWD1EN_BITOFFSET_POS (ADC_CFGR1_JAWD1EN_Pos)

/* ADC registers bits groups */
#define ADC_CR_BITS_PROPERTY_RS     ( ADC_CR_ADCAL | ADC_CR_JADSTP | ADC_CR_ADSTP | ADC_CR_JADSTART | ADC_CR_ADSTART \
                                      | ADC_CR_ADDIS | ADC_CR_ADEN) /* ADC register CR bits with HW property "rs":
                                                                       Software can read as well as set this bit.
                                                                       Writing '0' has no effect on the bit value. */

/* ADC internal channels related definitions */
/* Internal voltage reference VrefInt */
#define VREFINT_CAL_ADDR            ((uint16_t*) (0x0BFA07A5UL)) /* Internal voltage reference, address of parameter
                                                                    VREFINT_CAL: VrefInt ADC raw data acquired at
                                                                    temperature 30 DegC (tolerance: +-5 DegC),
                                                                    Vref+ = 3.0 V (tolerance: +-10 mV).              */
#define VREFINT_CAL_VREF            (3000UL)                     /* Analog voltage reference (Vref+) value with which
                                                                    VrefInt has been calibrated in production
                                                                    (tolerance: +-10 mV) (unit: mV).      */
/* Temperature sensor */
#define TEMPSENSOR_CAL1_ADDR        ((uint16_t*) (0x0BFA0710UL)) /* Internal temperature sensor, address of parameter
                                                                    TS_CAL1: On STM32U5, temperature sensor ADC raw
                                                                             data acquired at temperature  30 DegC
                                                                             (tolerance: +-5 DegC),Vref+ = 3.0 V
                                                                             (tolerance: +-10 mV).                   */
#define TEMPSENSOR_CAL2_ADDR        ((uint16_t*) (0x0BFA0742UL)) /* Internal temperature sensor, address of parameter
                                                                    TS_CAL2: On STM32U5, temperature sensor ADC raw
                                                                             data acquired at temperature 110 DegC
                                                                             (tolerance: +-5 DegC), Vref+ = 3.0 V
                                                                             (tolerance: +-10 mV).                   */
#define TEMPSENSOR_CAL1_TEMP        (30L)                        /* Internal temperature sensor, temperature at which
                                                                    temperature sensor has been calibrated in
                                                                    production for data into TEMPSENSOR_CAL1_ADDR
                                                                    (tolerance: +-5 DegC) (unit: DegC).              */
#define TEMPSENSOR_CAL2_TEMP        (130L)                       /* Internal temperature sensor, temperature at which
                                                                    temperature sensor has been calibrated in
                                                                    production for data into TEMPSENSOR_CAL2_ADDR
                                                                    (tolerance: +-5 DegC) (unit: DegC).             */
#define TEMPSENSOR_CAL_VREFANALOG   (3000UL)                     /* Analog voltage reference (Vref+) voltage with
                                                                    which temperature sensor has been calibrated in
                                                                    production (+-10 mV) (unit: mV).                */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Macros ADC Private Macros
  * @{
  */

/**
  * @brief  Driver macro reserved for internal use: isolate bits with the
  *         selected mask and shift them to the register LSB
  *         (shift mask on register position bit 0).
  * @param  __BITS__ Bits in register 32 bits
  * @param  __MASK__ Mask in register 32 bits
  * @retval Bits in register 32 bits
  */
#define __ADC_MASK_SHIFT(__BITS__, __MASK__)                                   \
  (((__BITS__) & (__MASK__)) >> POSITION_VAL((__MASK__)))

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  __REG__ Register basis from which the offset is applied.
  * @param  __REG_OFFFSET__ Offset to be applied (unit: number of registers).
  * @retval Pointer to register address
  */
#define __ADC_PTR_REG_OFFSET(__REG__, __REG_OFFFSET__)                         \
  ((__IO uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFFSET__) << 2UL))))

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup ADC_LL_ES_INIT ADC Exported Init structure
  * @{
  */

/**
  * @brief  Structure definition of some features of ADC common parameters
  *         and multimode
  *         (all ADC instances belonging to the same ADC common instance).
  * @note   The setting of these parameters by function @ref LL_ADC_CommonInit()
  *         is conditioned to ADC instances state (all ADC instances
  *         sharing the same ADC common instance):
  *         All ADC instances sharing the same ADC common instance must be
  *         disabled.
  */
typedef struct
{
  uint32_t CommonClock;  /*!< Set parameter common to several ADC: Clock source and prescaler.
                              This parameter can be a value of @ref ADC_LL_EC_COMMON_CLOCK_SOURCE
                              This feature can be modified afterwards using unitary function
                              @ref LL_ADC_SetCommonClock(). */

} LL_ADC_CommonInitTypeDef;

/**
  * @brief  Structure definition of some features of ADC instance.
  * @note   These parameters have an impact on ADC scope: ADC instance.
  *         Affects both group regular and group injected (availability
  *         of ADC group injected depends on STM32 families).
  *         Refer to corresponding unitary functions into
  *         @ref ADC_LL_EF_Configuration_ADC_Instance .
  * @note   The setting of these parameters by function @ref LL_ADC_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  *         This condition is applied to all ADC features, for efficiency
  *         and compatibility over all STM32 families. However, the different
  *         features can be set under different ADC state conditions
  *         (setting possible with ADC enabled without conversion on going,
  *         ADC enabled with conversion on going, ...)
  *         Each feature can be updated afterwards with a unitary function
  *         and potentially with ADC in a different state than disabled,
  *         refer to description of each function for setting
  *         conditioned to ADC state.
  */
typedef struct
{
  uint32_t Resolution;      /*!< Set ADC resolution.
                                 This parameter can be a value of @ref ADC_LL_EC_RESOLUTION
                                 This feature can be modified afterwards using unitary function
                                 @ref LL_ADC_SetResolution(). */

  uint32_t LeftBitShift;    /*!< Configures the left shifting applied to the final result with or without oversampling.
                                 This parameter can be a value of @ref ADC_LL_EC_LEFT_BIT_SHIFT. */

  uint32_t DataAlignment;   /*!< Set ADC conversion data alignment.
                                 This parameter can be a value of @ref ADC_LL_EC_DATA_ALIGN
                                 This feature can be modified afterwards using unitary function
                                 @ref LL_ADC_SetDataAlignment(). */

  uint32_t LowPowerMode;    /*!< Set ADC low power mode.
                                 This parameter can be a value of @ref ADC_LL_EC_LP_MODE
                                 This feature can be modified afterwards using unitary function
                                 @ref LL_ADC_SetLowPowerMode(). */

} LL_ADC_InitTypeDef;

/**
  * @brief  Structure definition of some features of ADC group regular.
  * @note   These parameters have an impact on ADC scope: ADC group regular.
  *         Refer to corresponding unitary functions into
  *         @ref ADC_LL_EF_Configuration_ADC_Group_Regular
  *         (functions with prefix "REG").
  * @note   The setting of these parameters by function @ref LL_ADC_REG_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  *         This condition is applied to all ADC features, for efficiency
  *         and compatibility over all STM32 families. However, the different
  *         features can be set under different ADC state conditions
  *         (setting possible with ADC enabled without conversion on going,
  *         ADC enabled with conversion on going, ...)
  *         Each feature can be updated afterwards with a unitary function
  *         and potentially with ADC in a different state than disabled,
  *         refer to description of each function for setting
  *         conditioned to ADC state.
  */
typedef struct
{
  uint32_t TriggerSource;               /*!< Set ADC group regular conversion trigger source: internal (SW start)
                                             or from external peripheral (timer event, external interrupt line).
                                             This parameter can be a value of @ref ADC_LL_EC_REG_TRIGGER_SOURCE
                                             @note On this STM32 series, setting trigger source to external trigger
                                                   also set trigger polarity to rising edge (default setting for
                                                   compatibility with some ADC on other STM32 families having this
                                                   setting set by HW default value).
                                                   In case of need to modify trigger edge, use function
                                                   @ref LL_ADC_REG_SetTriggerEdge().
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_REG_SetTriggerSource(). */

  uint32_t SequencerLength;             /*!< Set ADC group regular sequencer length.
                                             This parameter can be a value of @ref ADC_LL_EC_REG_SEQ_SCAN_LENGTH
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_REG_SetSequencerLength(). */

  uint32_t SequencerDiscont;            /*!< Set ADC group regular sequencer discontinuous mode: sequence subdivided
                                             and scan conversions interrupted every selected number of ranks.
                                             This parameter can be a value of @ref ADC_LL_EC_REG_SEQ_DISCONT_MODE
                                             @note This parameter has an effect only if group regular sequencer is
                                                   enabled (scan length of 2 ranks or more).
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_REG_SetSequencerDiscont(). */

  uint32_t ContinuousMode;              /*!< Set ADC continuous conversion mode on ADC group regular,
                                             whether ADC conversions are performed in single mode (one conversion per
                                             trigger) or in continuous mode (after the first trigger, following
                                             conversions launched successively automatically).
                                             This parameter can be a value of @ref ADC_LL_EC_REG_CONTINUOUS_MODE
                                             Note: It is not possible to enable both ADC group regular continuous
                                                   mode and discontinuous mode.
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_REG_SetContinuousMode(). */

  uint32_t DataTransferMode;            /*!< Set ADC group regular conversion data transfer mode: no transfer,
                                             transfer by DMA (Limited/Unlimited) or MDF.
                                             This parameter can be a value of @ref ADC_LL_EC_REG_DATA_TRANSFER_MODE
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_REG_SetDataTransferMode(). */

  uint32_t DMATransfer;                 /*!< Set ADC group regular conversion data transfer: no transfer or transfer
                                             by DMA, and DMA requests mode.
                                             This parameter can be a value of @ref ADC_LL_EC_REG_DMA_TRANSFER
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_REG_SetDMATransfer(). */

  uint32_t Overrun;                     /*!< Set ADC group regular behavior in case of overrun:
                                             data preserved or overwritten.
                                             This parameter can be a value of @ref ADC_LL_EC_REG_OVR_DATA_BEHAVIOR
                                             This feature can be modified afterwards using unitary function
                                             @ref LL_ADC_REG_SetOverrun(). */

} LL_ADC_REG_InitTypeDef;

/**
  * @brief  Structure definition of some features of ADC group injected.
  * @note   These parameters have an impact on ADC scope: ADC group injected.
  *         Refer to corresponding unitary functions into
  *         @ref ADC_LL_EF_Configuration_ADC_Group_Regular
  *         (functions with prefix "INJ").
  * @note   The setting of these parameters by function @ref LL_ADC_INJ_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  *         This condition is applied to all ADC features, for efficiency
  *         and compatibility over all STM32 families. However, the different
  *         features can be set under different ADC state conditions
  *         (setting possible with ADC enabled without conversion on going,
  *         ADC enabled with conversion on going, ...)
  *         Each feature can be updated afterwards with a unitary function
  *         and potentially with ADC in a different state than disabled,
  *         refer to description of each function for setting
  *         conditioned to ADC state.
  */
typedef struct
{
  uint32_t TriggerSource;        /*!< Set ADC group injected conversion trigger source: internal (SW start)
                                      or from external peripheral (timer event, external interrupt line).
                                      This parameter can be a value of @ref ADC_LL_EC_INJ_TRIGGER_SOURCE
                                      @note On this STM32 series, setting trigger source to external trigger
                                            also set trigger polarity to rising edge (default setting for
                                            compatibility with some ADC on other STM32 families having this
                                            setting set by HW default value).
                                            In case of need to modify trigger edge, use function
                                            @ref LL_ADC_INJ_SetTriggerEdge().
                                      This feature can be modified afterwards using unitary function
                                      @ref LL_ADC_INJ_SetTriggerSource(). */

  uint32_t SequencerLength;      /*!< Set ADC group injected sequencer length.
                                      This parameter can be a value of @ref ADC_LL_EC_INJ_SEQ_SCAN_LENGTH
                                      This feature can be modified afterwards using unitary function
                                      @ref LL_ADC_INJ_SetSequencerLength(). */

  uint32_t SequencerDiscont;     /*!< Set ADC group injected sequencer discontinuous mode: sequence subdivided
                                      and scan conversions interrupted every selected number of ranks.
                                      This parameter can be a value of @ref ADC_LL_EC_INJ_SEQ_DISCONT_MODE
                                      @note This parameter has an effect only if group injected sequencer
                                            is enabled (scan length of 2 ranks or more).
                                      This feature can be modified afterwards using unitary function
                                      @ref LL_ADC_INJ_SetSequencerDiscont(). */

  uint32_t TrigAuto;             /*!< Set ADC group injected conversion trigger: independent or from ADC group regular.
                                      This parameter can be a value of @ref ADC_LL_EC_INJ_TRIG_AUTO
                                      Note: This parameter must be set to set to independent trigger if injected
                                            trigger source is set to an external trigger.
                                      This feature can be modified afterwards using unitary function
                                      @ref LL_ADC_INJ_SetTrigAuto(). */

} LL_ADC_INJ_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Constants ADC Exported Constants
  * @{
  */

/** @defgroup ADC_LL_EC_FLAG ADC flags
  * @brief    Flags defines which can be used with LL_ADC_ReadReg function
  * @{
  */
#define LL_ADC_FLAG_ADRDY            ADC_ISR_ADRDY      /*!< ADC flag ADC instance ready */
#define LL_ADC_FLAG_EOC              ADC_ISR_EOC        /*!< ADC flag ADC group regular end of unitary conversion */
#define LL_ADC_FLAG_EOS              ADC_ISR_EOS        /*!< ADC flag ADC group regular end of sequence conversions */
#define LL_ADC_FLAG_OVR              ADC_ISR_OVR        /*!< ADC flag ADC group regular overrun */
#define LL_ADC_FLAG_EOSMP            ADC_ISR_EOSMP      /*!< ADC flag ADC group regular end of sampling phase */
#define LL_ADC_FLAG_JEOC             ADC_ISR_JEOC       /*!< ADC flag ADC group injected end of unitary conversion */
#define LL_ADC_FLAG_JEOS             ADC_ISR_JEOS       /*!< ADC flag ADC group injected end of sequence conversions */
#define LL_ADC_FLAG_JQOVF            ADC_ISR_JQOVF      /*!< ADC flag ADC group injected contexts queue overflow */
#define LL_ADC_FLAG_AWD1             ADC_ISR_AWD1       /*!< ADC flag ADC analog watchdog 1 */
#define LL_ADC_FLAG_AWD2             ADC_ISR_AWD2       /*!< ADC flag ADC analog watchdog 2 */
#define LL_ADC_FLAG_AWD3             ADC_ISR_AWD3       /*!< ADC flag ADC analog watchdog 3 */
#define LL_ADC_FLAG_EOCAL            ADC_ISR_EOCAL      /*!< ADC flag end of calibration */
#define LL_ADC_FLAG_LDORDY           ADC_ISR_LDORDY     /*!< ADC flag Voltage Regulator (LDO) Ready */

#define LL_ADC_FLAG_ADRDY_MST        ADC_CSR_ADRDY_MST  /*!< ADC flag ADC multimode master instance ready */
#define LL_ADC_FLAG_ADRDY_SLV        ADC_CSR_ADRDY_SLV  /*!< ADC flag ADC multimode slave instance ready */
#define LL_ADC_FLAG_EOC_MST          ADC_CSR_EOC_MST    /*!< ADC flag ADC multimode master group regular end
                                                             of unitary conversion */
#define LL_ADC_FLAG_EOC_SLV          ADC_CSR_EOC_SLV    /*!< ADC flag ADC multimode slave group regular end
                                                             of unitary conversion */
#define LL_ADC_FLAG_EOS_MST          ADC_CSR_EOS_MST    /*!< ADC flag ADC multimode master group regular end
                                                             of sequence conversions */
#define LL_ADC_FLAG_EOS_SLV          ADC_CSR_EOS_SLV    /*!< ADC flag ADC multimode slave group regular end
                                                             of sequence conversions */
#define LL_ADC_FLAG_OVR_MST          ADC_CSR_OVR_MST    /*!< ADC flag ADC multimode master group regular overrun */
#define LL_ADC_FLAG_OVR_SLV          ADC_CSR_OVR_SLV    /*!< ADC flag ADC multimode slave group regular overrun */
#define LL_ADC_FLAG_EOSMP_MST        ADC_CSR_EOSMP_MST  /*!< ADC flag ADC multimode master group regular end
                                                             of sampling phase */
#define LL_ADC_FLAG_EOSMP_SLV        ADC_CSR_EOSMP_SLV  /*!< ADC flag ADC multimode slave group regular end
                                                             of sampling phase */
#define LL_ADC_FLAG_JEOC_MST         ADC_CSR_JEOC_MST   /*!< ADC flag ADC multimode master group injected end
                                                             of unitary conversion */
#define LL_ADC_FLAG_JEOC_SLV         ADC_CSR_JEOC_SLV   /*!< ADC flag ADC multimode slave group injected end
                                                             of unitary conversion */
#define LL_ADC_FLAG_JEOS_MST         ADC_CSR_JEOS_MST   /*!< ADC flag ADC multimode master group injected end
                                                             of sequence conversions */
#define LL_ADC_FLAG_JEOS_SLV         ADC_CSR_JEOS_SLV   /*!< ADC flag ADC multimode slave group injected end
                                                             of sequence conversions */
#define LL_ADC_FLAG_JQOVF_MST        ADC_CSR_JQOVF_MST  /*!< ADC flag ADC multimode master group injected
                                                             contexts queue overflow */
#define LL_ADC_FLAG_JQOVF_SLV        ADC_CSR_JQOVF_SLV  /*!< ADC flag ADC multimode slave group injected
                                                             contexts queue overflow */
#define LL_ADC_FLAG_AWD1_MST         ADC_CSR_AWD1_MST   /*!< ADC flag ADC multimode master analog watchdog 1
                                                             of the ADC master */
#define LL_ADC_FLAG_AWD1_SLV         ADC_CSR_AWD1_SLV   /*!< ADC flag ADC multimode slave analog watchdog 1
                                                             of the ADC slave */
#define LL_ADC_FLAG_AWD2_MST         ADC_CSR_AWD2_MST   /*!< ADC flag ADC multimode master analog watchdog 2
                                                             of the ADC master */
#define LL_ADC_FLAG_AWD2_SLV         ADC_CSR_AWD2_SLV   /*!< ADC flag ADC multimode slave analog watchdog 2
                                                             of the ADC slave */
#define LL_ADC_FLAG_AWD3_MST         ADC_CSR_AWD3_MST   /*!< ADC flag ADC multimode master analog watchdog 3
                                                             of the ADC master */
#define LL_ADC_FLAG_AWD3_SLV         ADC_CSR_AWD3_SLV   /*!< ADC flag ADC multimode slave analog watchdog 3
                                                             of the ADC slave */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_IT ADC interruptions for configuration (interruption enable or disable)
  * @brief    IT defines which can be used with LL_ADC_ReadReg and  LL_ADC_WriteReg functions
  * @{
  */
#define LL_ADC_IT_ADRDY                 ADC_IER_ADRDYIE    /*!< ADC interruption ADC instance ready */
#define LL_ADC_IT_EOC                   ADC_IER_EOCIE      /*!< ADC interruption ADC group regular end of
                                                                unitary conversion */
#define LL_ADC_IT_EOS                   ADC_IER_EOSIE      /*!< ADC interruption ADC group regular end of
                                                                sequence conversions */
#define LL_ADC_IT_OVR                   ADC_IER_OVRIE      /*!< ADC interruption ADC group regular overrun */
#define LL_ADC_IT_EOSMP                 ADC_IER_EOSMPIE    /*!< ADC interruption ADC group regular end of
                                                                sampling phase */
#define LL_ADC_IT_JEOC                  ADC_IER_JEOCIE     /*!< ADC interruption ADC group injected end of
                                                                unitary conversion */
#define LL_ADC_IT_JEOS                  ADC_IER_JEOSIE     /*!< ADC interruption ADC group injected end of
                                                                sequence conversions */
#define LL_ADC_IT_JQOVF                 ADC_IER_JQOVFIE    /*!< ADC interruption ADC group injected contexts
                                                                queue overflow */
#define LL_ADC_IT_AWD1                  ADC_IER_AWD1IE     /*!< ADC interruption ADC analog watchdog 1 */
#define LL_ADC_IT_AWD2                  ADC_IER_AWD2IE     /*!< ADC interruption ADC analog watchdog 2 */
#define LL_ADC_IT_AWD3                  ADC_IER_AWD3IE     /*!< ADC interruption ADC analog watchdog 3 */
#define LL_ADC_IT_EOCAL                 ADC_IER_EOCALIE    /*!< ADC interruption ADC end of calibration */
#define LL_ADC_IT_LDORDY                ADC_IER_LDORDYIE   /*!< ADC interruption ADC Voltage Regulator (LDO) Ready */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REGISTERS  ADC registers compliant with specific purpose
  * @{
  */
/* List of ADC registers intended to be used (most commonly) with             */
/* DMA transfer.                                                              */
/* Refer to function @ref LL_ADC_DMA_GetRegAddr().                            */
#define LL_ADC_DMA_REG_REGULAR_DATA       (0x00000000UL) /* ADC group regular conversion data register
                                                            (corresponding to register DR) to be used with ADC
                                                             configured in independent mode. Without DMA transfer,
                                                             register accessed by LL function
                                                             @ref LL_ADC_REG_ReadConversionData32() and
                                                             other functions @ref LL_ADC_REG_ReadConversionDatax() */
#if defined(ADC_MULTIMODE_SUPPORT)
#define LL_ADC_DMA_REG_REGULAR_DATA_MULTI    (0x00000001UL) /* ADC group regular conversion data register
                                                               (corresponding to register CDR) to be used with
                                                               ADC configured in multimode (available on STM32 devices
                                                               with several ADC instances). Without DMA transfer,
                                                               register accessed by LL function
                                                               @ref LL_ADC_REG_ReadMultiConversionData32() */
#endif /* ADC_MULTIMODE_SUPPORT */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_COMMON_CLOCK_SOURCE  ADC common - Clock source
  * @{
  */
#define LL_ADC_CLOCK_ASYNC_DIV1    (0x00000000UL)                                        /*!< ADC asynchronous clock
                                                                                              without prescaler */
#define LL_ADC_CLOCK_ASYNC_DIV2    (ADC_CCR_PRESC_0)                                     /*!< ADC asynchronous clock
                                                                                              with prescaler division
                                                                                              by 2   */
#define LL_ADC_CLOCK_ASYNC_DIV4    (ADC_CCR_PRESC_1)                                     /*!< ADC asynchronous clock
                                                                                              with prescaler division
                                                                                              by 4   */
#define LL_ADC_CLOCK_ASYNC_DIV6    (ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0)                   /*!< ADC asynchronous clock
                                                                                              with prescaler division
                                                                                               by 6   */
#define LL_ADC_CLOCK_ASYNC_DIV8    (ADC_CCR_PRESC_2)                                     /*!< ADC asynchronous clock
                                                                                              with prescaler division
                                                                                              by 8   */
#define LL_ADC_CLOCK_ASYNC_DIV10   (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_0)                   /*!< ADC asynchronous clock
                                                                                              with prescaler division
                                                                                              by 10  */
#define LL_ADC_CLOCK_ASYNC_DIV12   (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_1)                   /*!< ADC asynchronous clock
                                                                                              with prescaler division
                                                                                              by 12  */
#define LL_ADC_CLOCK_ASYNC_DIV16   (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0) /*!< ADC asynchronous clock
                                                                                              with prescaler division
                                                                                              by 16  */
#define LL_ADC_CLOCK_ASYNC_DIV32   (ADC_CCR_PRESC_3)                                     /*!< ADC asynchronous clock
                                                                                              with prescaler division
                                                                                              by 32  */
#define LL_ADC_CLOCK_ASYNC_DIV64   (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_0)                   /*!< ADC asynchronous clock
                                                                                              with prescaler division
                                                                                              by 64  */
#define LL_ADC_CLOCK_ASYNC_DIV128  (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_1)                   /*!< ADC asynchronous clock
                                                                                              with prescaler division
                                                                                              by 128 */
#define LL_ADC_CLOCK_ASYNC_DIV256  (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0) /*!< ADC asynchronous clock
                                                                                              with prescaler division
                                                                                              by 256 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_COMMON_PATH_INTERNAL  ADC common - Measurement path to internal channels
  * @{
  */
/* Note: Other measurement paths to internal channels may be available        */
/*       (connections to other peripherals).                                  */
/*       If they are not listed below, they do not require any specific       */
/*       path enable. In this case, Access to measurement path is done        */
/*       only by selecting the corresponding ADC internal channel.            */
#define LL_ADC_PATH_INTERNAL_NONE        (0x00000000UL)     /*!< ADC measurement paths all disabled */
#define LL_ADC_PATH_INTERNAL_VREFINT     (ADC_CCR_VREFEN)   /*!< ADC measurement path to internal channel VrefInt */
#define LL_ADC_PATH_INTERNAL_TEMPSENSOR  (ADC_CCR_VSENSEEN) /*!< ADC measurement path to internal channel
                                                              temperature sensor */
#define LL_ADC_PATH_INTERNAL_VBAT        (ADC_CCR_VBATEN)   /*!< ADC measurement path to internal channel Vbat */

#define LL_ADC_PATH_INTERNAL_VCORE       (LL_ADC_PATH_INTERNAL_VREFINT \
                                          | LL_ADC_CHANNEL_DIFFERENCIATION_VREFINT_VCORE)  /*!< ADC measurement path
to internal channel VCore */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CALIBRATION_OFFSET_LINEARITY  ADC instance - Calibration mode for offset and linearity
  * @{
  */
#define LL_ADC_CALIB_OFFSET          (ADC_CALIB_FACTOR_OFFSET_REGOFFSET)   /*!< Calibration of ADC offset.
                                                                                Duration of calibration of offset
                                                                                duration: 1280 ADC clock cycles.
                                                                                For devices with differential mode
                                                                                available: Calibration of offset
                                                                                is specific to each of single-ended
                                                                                and differential modes. */
#define LL_ADC_CALIB_LINEARITY       (ADC_CALIB_FACTOR_LINEARITY_REGOFFSET)/*!< Calibration of ADC linearity.
                                                                                Duration of calibration of
                                                                                linearity: 15104 ADC clock cycles.
                                                                                For devices with differential mode
                                                                                available: Calibration of linearity
                                                                                is common to both single-ended and
                                                                                differential modes. */
#define LL_ADC_CALIB_OFFSET_LINEARITY (ADC_CALIB_FACTOR_LINEARITY_REGOFFSET \
                                       | ADC_CR_ADCALLIN)                  /*!< Calibration of ADC offset and
                                                                                linearity. Duration of calibration
                                                                                of offset and linearity: 16384 ADC
                                                                                clock cycles. For devices with
                                                                                differential mode available:
                                                                                Calibration of offset is specific
                                                                                to each of single-ended and
                                                                                differential modes, calibration of
                                                                                linearity is common to both
single-ended and differential modes. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CALIBRATION_LINEARITY_INDEX ADC indexes for linear calibration
  * @{
  */
#define LL_ADC_CALIB_OFFSET_INDEX        (0x00000000UL)                          /*!< Offset Calibration Index */
#define LL_ADC_CALIB_LINEARITY_INDEX1    (ADC_CR_CALINDEX0)                      /*!< Linearity Calibration Index 1*/
#define LL_ADC_CALIB_LINEARITY_INDEX2    (ADC_CR_CALINDEX1)                      /*!< Linearity Calibration Index 2*/
#define LL_ADC_CALIB_LINEARITY_INDEX3    (ADC_CR_CALINDEX1 | ADC_CR_CALINDEX0)   /*!< Linearity Calibration Index 3*/
#define LL_ADC_CALIB_LINEARITY_INDEX4    (ADC_CR_CALINDEX2)                      /*!< Linearity Calibration Index 4*/
#define LL_ADC_CALIB_LINEARITY_INDEX5    (ADC_CR_CALINDEX2 | ADC_CR_CALINDEX0)   /*!< Linearity Calibration Index 5*/
#define LL_ADC_CALIB_LINEARITY_INDEX6    (ADC_CR_CALINDEX2 | ADC_CR_CALINDEX1)   /*!< Linearity Calibration Index 6*/
#define LL_ADC_CALIB_LINEARITY_INDEX7    (ADC_CR_CALINDEX2 | ADC_CR_CALINDEX1 \
                                          | ADC_CR_CALINDEX0)                    /*!< Linearity Calibration Index 7*/
#define LL_ADC_CALIB_INTEROFFSET_INDEX   (ADC_CR_CALINDEX3)                      /*!< Linearity Calibration Index 8*/
/**
  * @}
  */

/** @defgroup ADC_LL_EC_RESOLUTION  ADC instance - Resolution
  * @{
  */
#define LL_ADC_RESOLUTION_14B       (0x00000000UL)                      /*!< ADC resolution 14 bits */
#define LL_ADC_RESOLUTION_12B       (                  ADC_CFGR1_RES_0) /*!< ADC resolution 12 bits */
#define LL_ADC_RESOLUTION_10B       (ADC_CFGR1_RES_1                  ) /*!< ADC resolution 10 bits */
#define LL_ADC_RESOLUTION_8B        (ADC_CFGR1_RES_1 | ADC_CFGR1_RES_0) /*!< ADC resolution 8 bits */
#define LL_ADC_RESOLUTION_6B        (0x0000FFFFUL)                      /*!< ADC resolution 6 bits, Internal value
                                                                             used to differentiate 8B to 6B resolutions
                                                                             for ADC1 and ADC4 respectively */

/* Internal values only, please do not use */
#define LL_ADC_RESOLUTION_12B_ADC4  (0x00000000UL)                      /*!< ADC resolution 12 bits */
#define LL_ADC_RESOLUTION_10B_ADC4  (                  ADC_CFGR1_RES_0) /*!< ADC resolution 10 bits */
#define LL_ADC_RESOLUTION_8B_ADC4   (ADC_CFGR1_RES_1                  ) /*!< ADC resolution 8 bits */
#define LL_ADC_RESOLUTION_6B_ADC4   (ADC_CFGR1_RES_1 | ADC_CFGR1_RES_0) /*!< ADC resolution  6 bits */

/**
  * @}
  */
/** @defgroup ADC_LL_EC_DATA_ALIGN  ADC instance - Data alignment
  * @{
  */
#define LL_ADC_DATA_ALIGN_RIGHT            (0x00000000UL)         /*!< ADC conversion data alignment: right aligned
                                                                      (alignment on data register LSB bit 0)*/
#define LL_ADC_DATA_ALIGN_LEFT             (ADC4_CFGR1_ALIGN)      /*!< ADC conversion data alignment: left aligned
                                                                       (alignment on data register MSB bit 15)*/
/**
  * @}
  */

/** @defgroup ADC_LL_EC_LEFT_BIT_SHIFT   ADC left Shift
  * @{
  */
#define LL_ADC_LEFT_BIT_SHIFT_NONE  (0x00000000UL)                                                                       /*!< ADC no bit shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_1     (ADC_CFGR2_LSHIFT_0)                                                                 /*!< ADC 1 bit shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_2     (ADC_CFGR2_LSHIFT_1)                                                                 /*!< ADC 2 bits shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_3     (ADC_CFGR2_LSHIFT_1 | ADC_CFGR2_LSHIFT_0)                                            /*!< ADC 3 bits shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_4     (ADC_CFGR2_LSHIFT_2)                                                                 /*!< ADC 4 bits shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_5     (ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_0)                                            /*!< ADC 5 bits shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_6     (ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_1)                                            /*!< ADC 6 bits shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_7     (ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_1 | ADC_CFGR2_LSHIFT_0)                       /*!< ADC 7 bits shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_8     (ADC_CFGR2_LSHIFT_3)                                                                 /*!< ADC 8 bits shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_9     (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_0)                                            /*!< ADC 9 bits shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_10    (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_1)                                            /*!< ADC 10 bits shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_11    (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_1 | ADC_CFGR2_LSHIFT_0)                       /*!< ADC 11 bits shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_12    (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_2)                                            /*!< ADC 12 bits shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_13    (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_0)                       /*!< ADC 13 bits shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_14    (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_1)                       /*!< ADC 14 bits shift left applied on the final ADC conversion data */
#define LL_ADC_LEFT_BIT_SHIFT_15    (ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_1 | ADC_CFGR2_LSHIFT_0)  /*!< ADC 15 bits shift left applied on the final ADC conversion data */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_LP_MODE  ADC instance - Low power mode
  * @{
  */
#define LL_ADC_LP_MODE_NONE                (0x00000000UL)                      /*!< No ADC low power mode activated */
#define LL_ADC_LP_AUTOWAIT                 (ADC_CFGR1_AUTDLY)                   /*!< ADC low power mode auto delay: Dynamic low power mode, ADC conversions are performed only when necessary (when previous ADC conversion data is read). See description with function @ref LL_ADC_SetLowPowerMode(). */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_AUTOPOWEROFF_MODE  ADC instance - Low power mode auto power-off
  * @{
  */
#define LL_ADC_LP_AUTOPOWEROFF_DISABLE      (0x00000000UL)                    /*!< ADC low power mode auto power-off disabled */
#define LL_ADC_LP_AUTOPOWEROFF_ENABLE       (ADC4_PW_AUTOFF)                  /*!< ADC low power mode auto power-off enabled: the ADC automatically powers-off after a ADC conversion and automatically wakes up when a new ADC conversion is triggered (with startup time between trigger and start of sampling). See description with function @ref LL_ADC_SetLPModeAutoPowerOff(). It can be combined with mode low power mode auto wait. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_AUTONOMOUS_DEEP_POWER_DOWN_MODE  ADC instance - Autonomous deep power down mode
  * @{
  */
#define LL_ADC_LP_AUTONOMOUS_DPD_DISABLE      (0x00000000UL)      /*!< ADC deep power down in autonomous mode disabled */
#define LL_ADC_LP_AUTONOMOUS_DPD_ENABLE       (ADC4_PW_DPD)       /*!< ADC deep power down in autonomous mode enabled */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OFFSET_NB  ADC instance - Offset number
  * @{
  */
#define LL_ADC_OFFSET_1                    ADC_OFR1_REGOFFSET /*!< ADC offset number 1: ADC channel and offset level to which the offset programmed will be applied (independently of channel mapped on ADC group regular or group injected) */
#define LL_ADC_OFFSET_2                    ADC_OFR2_REGOFFSET /*!< ADC offset number 2: ADC channel and offset level to which the offset programmed will be applied (independently of channel mapped on ADC group regular or group injected) */
#define LL_ADC_OFFSET_3                    ADC_OFR3_REGOFFSET /*!< ADC offset number 3: ADC channel and offset level to which the offset programmed will be applied (independently of channel mapped on ADC group regular or group injected) */
#define LL_ADC_OFFSET_4                    ADC_OFR4_REGOFFSET /*!< ADC offset number 4: ADC channel and offset level to which the offset programmed will be applied (independently of channel mapped on ADC group regular or group injected) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OFFSET_SIGNED_SATURATION ADC instance - Offset signed saturation mode
  * @{
  */
#define LL_ADC_OFFSET_SIGNED_SATURATION_DISABLE   (0x00000000UL)   /*!< ADC offset signed saturation is disabled (among ADC selected offset number 1, 2, 3 or 4) */
#define LL_ADC_OFFSET_SIGNED_SATURATION_ENABLE    (ADC_OFR1_SSAT) /*!< ADC offset signed saturation is enabled (among ADC selected offset number 1, 2, 3 or 4) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OFFSET_UNSIGNED_SATURATION ADC instance - Offset unsigned saturation mode
  * @{
  */
#define LL_ADC_OFFSET_UNSIGNED_SATURATION_DISABLE   (0x00000000UL)   /*!< ADC offset unsigned saturation is disabled (among ADC selected offset number 1, 2, 3 or 4) */
#define LL_ADC_OFFSET_UNSIGNED_SATURATION_ENABLE    (ADC_OFR1_USAT) /*!< ADC offset unsigned saturation is enabled (among ADC selected offset number 1, 2, 3 or 4) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OFFSET_SIGN ADC instance - Offset sign
  * @{
  */
#define LL_ADC_OFFSET_SIGN_NEGATIVE        (0x00000000UL)       /*!< ADC offset is negative (among ADC selected offset number 1, 2, 3 or 4) */
#define LL_ADC_OFFSET_SIGN_POSITIVE        (ADC_OFR1_OFFSETPOS) /*!< ADC offset is positive (among ADC selected offset number 1, 2, 3 or 4) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_GROUPS  ADC instance - Groups
  * @{
  */
#define LL_ADC_GROUP_REGULAR               (0x00000001UL) /*!< ADC group regular (available on all STM32 devices) */
#define LL_ADC_GROUP_INJECTED              (0x00000002UL) /*!< ADC group injected (not available on all STM32 devices)*/
#define LL_ADC_GROUP_REGULAR_INJECTED      (0x00000003UL) /*!< ADC both groups regular and injected */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_SAMPLINGTIME_COMMON  ADC instance - Sampling time common to a group of channels
  * @{
  */
#define LL_ADC_SAMPLINGTIME_COMMON_1       (ADC4_SMPR_SMP1_BITOFFSET_POS)                             /*!< Set sampling time common to a group of channels: sampling time nb 1 */
#define LL_ADC_SAMPLINGTIME_COMMON_2       (ADC4_SMPR_SMP2_BITOFFSET_POS | ADC4_SAMPLING_TIME_CH_MASK) /*!< Set sampling time common to a group of channels: sampling time nb 2 */
/* Internal mask for ADC channel sampling time:                               */
/* To select into literals LL_ADC_SAMPLINGTIME_x                              */
/* the relevant bits for:                                                     */
/* (concatenation of multiple bits used in register SMPR)                     */
/* - ADC channels sampling time: setting channel wise, to map each channel    */
/*   on one of the common sampling time available.                            */
/* - ADC channels common sampling time: set a sampling time into one of the   */
/*   common sampling time available.                                          */
#define ADC4_SAMPLING_TIME_SMP_MASK         (ADC4_SMPR_SMP2 | ADC4_SMPR_SMP1)
#define ADC4_SAMPLING_TIME_SMP_SHIFT_MASK   (ADC4_SMPR_SMP2_BITOFFSET_POS | ADC4_SMPR_SMP1_BITOFFSET_POS)

/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_TRIGGER_FREQ  ADC group regular - Trigger frequency mode
  * @{
  */
#define LL_ADC_TRIGGER_FREQ_HIGH           (0x00000000UL)            /*!< ADC trigger frequency mode set to high frequency. Note: ADC trigger frequency mode must be set to low frequency when a duration is exceeded before ADC conversion start trigger event (between ADC enable and ADC conversion start trigger event or between two ADC conversion start trigger event). Duration value: Refer to device datasheet, parameter "tIdle". */
#define LL_ADC_TRIGGER_FREQ_LOW            (ADC4_CFGR2_LFTRIG)        /*!< ADC trigger frequency mode set to low frequency. Note: ADC trigger frequency mode must be set to low frequency when a duration is exceeded before ADC conversion start trigger event (between ADC enable and ADC conversion start trigger event or between two ADC conversion start trigger event). Duration value: Refer to device datasheet, parameter "tIdle". */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CHANNEL  ADC instance - Channel number
  * @{
  */
#define LL_ADC_CHANNEL_0                   (ADC_CHANNEL_0_NUMBER  | ADC_CHANNEL_0_SMP  | ADC_CHANNEL_0_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN0  */
#define LL_ADC_CHANNEL_1                   (ADC_CHANNEL_1_NUMBER  | ADC_CHANNEL_1_SMP  | ADC_CHANNEL_1_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN1  */
#define LL_ADC_CHANNEL_2                   (ADC_CHANNEL_2_NUMBER  | ADC_CHANNEL_2_SMP  | ADC_CHANNEL_2_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN2  */
#define LL_ADC_CHANNEL_3                   (ADC_CHANNEL_3_NUMBER  | ADC_CHANNEL_3_SMP  | ADC_CHANNEL_3_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN3  */
#define LL_ADC_CHANNEL_4                   (ADC_CHANNEL_4_NUMBER  | ADC_CHANNEL_4_SMP  | ADC_CHANNEL_4_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN4  */
#define LL_ADC_CHANNEL_5                   (ADC_CHANNEL_5_NUMBER  | ADC_CHANNEL_5_SMP  | ADC_CHANNEL_5_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN5  */
#define LL_ADC_CHANNEL_6                   (ADC_CHANNEL_6_NUMBER  | ADC_CHANNEL_6_SMP  | ADC_CHANNEL_6_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN6  */
#define LL_ADC_CHANNEL_7                   (ADC_CHANNEL_7_NUMBER  | ADC_CHANNEL_7_SMP  | ADC_CHANNEL_7_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN7  */
#define LL_ADC_CHANNEL_8                   (ADC_CHANNEL_8_NUMBER  | ADC_CHANNEL_8_SMP  | ADC_CHANNEL_8_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN8  */
#define LL_ADC_CHANNEL_9                   (ADC_CHANNEL_9_NUMBER  | ADC_CHANNEL_9_SMP  | ADC_CHANNEL_9_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN9  */
#define LL_ADC_CHANNEL_10                  (ADC_CHANNEL_10_NUMBER | ADC_CHANNEL_10_SMP | ADC_CHANNEL_10_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN10 */
#define LL_ADC_CHANNEL_11                  (ADC_CHANNEL_11_NUMBER | ADC_CHANNEL_11_SMP | ADC_CHANNEL_11_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN11 */
#define LL_ADC_CHANNEL_12                  (ADC_CHANNEL_12_NUMBER | ADC_CHANNEL_12_SMP | ADC_CHANNEL_12_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN12 */
#define LL_ADC_CHANNEL_13                  (ADC_CHANNEL_13_NUMBER | ADC_CHANNEL_13_SMP | ADC_CHANNEL_13_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN13 */
#define LL_ADC_CHANNEL_14                  (ADC_CHANNEL_14_NUMBER | ADC_CHANNEL_14_SMP | ADC_CHANNEL_14_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN14 */
#define LL_ADC_CHANNEL_15                  (ADC_CHANNEL_15_NUMBER | ADC_CHANNEL_15_SMP | ADC_CHANNEL_15_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN15 */
#define LL_ADC_CHANNEL_16                  (ADC_CHANNEL_16_NUMBER | ADC_CHANNEL_16_SMP | ADC_CHANNEL_16_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN16 */
#define LL_ADC_CHANNEL_17                  (ADC_CHANNEL_17_NUMBER | ADC_CHANNEL_17_SMP | ADC_CHANNEL_17_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN17 */
#define LL_ADC_CHANNEL_18                  (ADC_CHANNEL_18_NUMBER | ADC_CHANNEL_18_SMP | ADC_CHANNEL_18_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN18 */
#define LL_ADC_CHANNEL_19                  (ADC_CHANNEL_19_NUMBER | ADC_CHANNEL_19_SMP | ADC_CHANNEL_19_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN19 */
#define LL_ADC_CHANNEL_20                  (ADC_CHANNEL_20_NUMBER | ADC_CHANNEL_20_SMP | ADC_CHANNEL_20_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN20 */
#define LL_ADC_CHANNEL_21                  (ADC_CHANNEL_21_NUMBER | ADC_CHANNEL_21_SMP | ADC_CHANNEL_21_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN21 */
#define LL_ADC_CHANNEL_22                  (ADC_CHANNEL_22_NUMBER | ADC_CHANNEL_22_SMP | ADC_CHANNEL_22_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN22 */
#define LL_ADC_CHANNEL_23                  (ADC_CHANNEL_23_NUMBER | ADC_CHANNEL_23_SMP | ADC_CHANNEL_23_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN23 */

#define LL_ADC_CHANNEL_VREFINT             (LL_ADC_CHANNEL_0 | ADC_CHANNEL_ID_INTERNAL_CH) /*!< ADC internal channel connected to VrefInt: Internal voltage reference. . */
#define LL_ADC_CHANNEL_TEMPSENSOR          (LL_ADC_CHANNEL_19 | ADC_CHANNEL_ID_INTERNAL_CH) /*!< ADC internal channel connected to Temperature sensor. */
#define LL_ADC_CHANNEL_VBAT                (LL_ADC_CHANNEL_18 | ADC_CHANNEL_ID_INTERNAL_CH) /*!< ADC internal channel connected to Vbat/4: Vbat voltage through a divider ladder of factor 1/4 to have Vbat always below Vdda.  */

#define LL_ADC_CHANNEL_VCORE               (LL_ADC_CHANNEL_12 | ADC_CHANNEL_ID_INTERNAL_CH) /*!< ADC internal channel connected to Vcore. On STM32U5, ADC channel available only on ADC instance: ADC4. */
#define LL_ADC_CHANNEL_TEMPSENSOR_ADC4     (LL_ADC_CHANNEL_13 | ADC_CHANNEL_ID_INTERNAL_CH) /*!< ADC internal channel connected to Temperature sensor. On STM32U5, ADC channel available only on ADC instance: ADC4. */
#define LL_ADC_CHANNEL_VBAT_ADC4           (LL_ADC_CHANNEL_14 | ADC_CHANNEL_ID_INTERNAL_CH) /*!< ADC internal channel connected to Vbat/4: Vbat voltage through a divider ladder of factor 1/4 to have Vbat always below Vdda. On STM32U5, ADC channel available only on ADC instance: ADC4. */
#define LL_ADC_CHANNEL_DAC1CH1_ADC4        (LL_ADC_CHANNEL_21 | ADC_CHANNEL_ID_INTERNAL_CH) /*!< ADC internal channel connected to DAC1 channel 1, channel specific to ADC4 */
#define LL_ADC_CHANNEL_DAC1CH2_ADC4        (LL_ADC_CHANNEL_DAC1CH1_ADC4 | LL_ADC_CHANNEL_DIFFERENCIATION_VREFINT_VCORE) /*!< ADC internal channel connected to DAC1 channel 2, channel specific to ADC4 */

#define LL_ADC_CHANNEL_DIFFERENCIATION_VREFINT_VCORE (0x01000000UL)                 /*!< Dummy bit for driver internal usage, not used in ADC channel setting registers CHSELR or SQRx */

/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_TRIGGER_SOURCE  ADC group regular - Trigger source
  * @{
  */
#define LL_ADC_REG_TRIG_SOFTWARE        (0x00000000UL)                                                                                                      /*!< ADC group regular conversion trigger internal: SW start. */
#define LL_ADC_REG_TRIG_EXT_TIM1_CH1    (ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                                                     /*!< ADC group regular conversion trigger from external peripheral: TIM1 channel 1 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM1_CH2    (ADC_CFGR1_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                                /*!< ADC group regular conversion trigger from external peripheral: TIM1 channel 2 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM1_CH3    (ADC_CFGR1_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                                /*!< ADC group regular conversion trigger from external peripheral: TIM1 channel 3 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM2_CH2    (ADC_CFGR1_EXTSEL_1 | ADC_CFGR1_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group regular conversion trigger from external peripheral: TIM2 channel 2 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM3_TRGO   (ADC_CFGR1_EXTSEL_2 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                                /*!< ADC group regular conversion trigger from external peripheral: TIM3 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM4_CH4    (ADC_CFGR1_EXTSEL_2 | ADC_CFGR1_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group regular conversion trigger from external peripheral: TIM4 channel 4 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_EXTI_LINE11 (ADC_CFGR1_EXTSEL_2 | ADC_CFGR1_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group regular conversion trigger from external peripheral: external interrupt line 11 event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM8_TRGO   (ADC_CFGR1_EXTSEL_2 | ADC_CFGR1_EXTSEL_1 | ADC_CFGR1_EXTSEL_0               \
                                         | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                                                   /*!< ADC group regular conversion trigger from external peripheral: TIM8 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM8_TRGO2  (ADC_CFGR1_EXTSEL_3 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                                /*!< ADC group regular conversion trigger from external peripheral: TIM8 TRGO2 event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM1_TRGO   (ADC_CFGR1_EXTSEL_3 | ADC_CFGR1_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group regular conversion trigger from external peripheral: TIM1 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM1_TRGO2  (ADC_CFGR1_EXTSEL_3 | ADC_CFGR1_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group regular conversion trigger from external peripheral: TIM1 TRGO2 event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM2_TRGO   (ADC_CFGR1_EXTSEL_3 | ADC_CFGR1_EXTSEL_1 | ADC_CFGR1_EXTSEL_0               \
                                         | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                                                   /*!< ADC group regular conversion trigger from external peripheral: TIM2 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM4_TRGO   (ADC_CFGR1_EXTSEL_3 | ADC_CFGR1_EXTSEL_2 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group regular conversion trigger from external peripheral: TIM4 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM6_TRGO   (ADC_CFGR1_EXTSEL_3 | ADC_CFGR1_EXTSEL_2 | ADC_CFGR1_EXTSEL_0               \
                                         | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                                                   /*!< ADC group regular conversion trigger from external peripheral: TIM6 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM15_TRGO  (ADC_CFGR1_EXTSEL_3 | ADC_CFGR1_EXTSEL_2 | ADC_CFGR1_EXTSEL_1               \
                                         | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                                                   /*!< ADC group regular conversion trigger from external peripheral: TIM15 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM3_CH4    (ADC_CFGR1_EXTSEL_3 | ADC_CFGR1_EXTSEL_2 | ADC_CFGR1_EXTSEL_1               \
                                         | ADC_CFGR1_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                              /*!< ADC group regular conversion trigger from external peripheral: TIM3 channel 4 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_EXTI_LINE15 (ADC_CFGR1_EXTSEL_4 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                                /*!< ADC group regular conversion trigger from external peripheral: HRTIM TRG1 event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_LPTIM1_CH1  (ADC_CFGR1_EXTSEL_4 | ADC_CFGR1_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group regular conversion trigger from external peripheral: LPTIM1 CH1 event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_LPTIM2_CH1  (ADC_CFGR1_EXTSEL_4 | ADC_CFGR1_EXTSEL_1 | ADC_CFGR1_EXTSEL_0               \
                                         | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                                                   /*!< ADC group regular conversion trigger from external peripheral: LPTIM2 CH1 event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_LPTIM3_CH1  (ADC_CFGR1_EXTSEL_4 | ADC_CFGR1_EXTSEL_2 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group regular conversion trigger from external peripheral: LPTIM3 CH1 event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_LPTIM4_OUT  (ADC_CFGR1_EXTSEL_4 | ADC_CFGR1_EXTSEL_2 | ADC_CFGR1_EXTSEL_0               \
                                         | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                                                   /*!< ADC group regular conversion trigger from external peripheral: LPTIM4 event OUT. Trigger edge set to rising edge (default setting). */

#define LL_ADC_REG_TRIG_EXT_TIM1_TRGO2_ADC4     (ADC_REG_TRIG_EXT_EDGE_DEFAULT)                        /*!< ADC group regular conversion trigger from external IP: TIM1 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM1_CH4_ADC4       (ADC4_CFGR1_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)  /*!< ADC group regular conversion trigger from external IP: TIM1 channel 4 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#if defined(TIM2)
#define LL_ADC_REG_TRIG_EXT_TIM2_TRGO_ADC4      (ADC4_CFGR1_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)  /*!< ADC group regular conversion trigger from external IP: TIM2 TRGO. Trigger edge set to rising edge (default setting). */
#endif /* TIM2 */
#if defined(TIM15)
#define LL_ADC_REG_TRIG_EXT_TIM15_TRGO_ADC4     (ADC4_CFGR1_EXTSEL_1 | ADC4_CFGR1_EXTSEL_0         \
                                                 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                      /*!< ADC group regular conversion trigger from external IP: TIM15 TRGO. Trigger edge set to rising edge (default setting). */
#endif /* TIM5 */
#if defined(TIM6)
#define LL_ADC_REG_TRIG_EXT_TIM6_TRGO_ADC4      (ADC4_CFGR1_EXTSEL_2 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)  /*!< ADC group regular conversion trigger from external IP: TIM6 TRGO. Trigger edge set to rising edge (default setting). */
#endif  /* TIM6 */
#if defined(LPTIM1)
#define LL_ADC_REG_TRIG_EXT_LPTIM1_CH1_ADC4    (ADC4_CFGR1_EXTSEL_2 | ADC4_CFGR1_EXTSEL_0          \
                                                | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                       /*!< ADC group regular conversion trigger from external IP: LPTIM1 CH1. Trigger edge set to rising edge (default setting). */
#endif /* LPTIM1 */
#if defined(LPTIM3)
#define LL_ADC_REG_TRIG_EXT_LPTIM3_CH2_ADC4    (ADC4_CFGR1_EXTSEL_2 | ADC4_CFGR1_EXTSEL_1          \
                                                | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                       /*!< ADC group regular conversion trigger from external IP: LPTIM3 CH2. Trigger edge set to rising edge (default setting). */
#endif  /* LPTIM3 */
#define LL_ADC_REG_TRIG_EXT_EXTI_LINE15_ADC4   (ADC4_CFGR1_EXTSEL_2 | ADC4_CFGR1_EXTSEL_1          \
                                                | ADC4_CFGR1_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT) /*!< ADC group regular conversion trigger from external IP: external interrupt line 15. Trigger edge set to rising edge (default setting). */

/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_TRIGGER_EDGE  ADC group regular - Trigger edge
  * @{
  */
#define LL_ADC_REG_TRIG_EXT_RISING         (                   ADC_CFGR1_EXTEN_0)   /*!< ADC group regular conversion trigger polarity set to rising edge */
#define LL_ADC_REG_TRIG_EXT_FALLING        (ADC_CFGR1_EXTEN_1                   )   /*!< ADC group regular conversion trigger polarity set to falling edge */
#define LL_ADC_REG_TRIG_EXT_RISINGFALLING  (ADC_CFGR1_EXTEN_1 | ADC_CFGR1_EXTEN_0)   /*!< ADC group regular conversion trigger polarity set to both rising and falling edges */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_CONTINUOUS_MODE  ADC group regular - Continuous mode
  * @{
  */
#define LL_ADC_REG_CONV_SINGLE             (0x00000000UL)          /*!< ADC conversions are performed in single mode: one conversion per trigger */
#define LL_ADC_REG_CONV_CONTINUOUS         (ADC_CFGR1_CONT)         /*!< ADC conversions are performed in continuous mode: after the first trigger, following conversions launched successively automatically */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_DATA_TRANSFER_MODE  ADC group regular - Data transfer mode of ADC conversion data
  * @{
  */
#define LL_ADC_REG_DR_TRANSFER             (0x00000000UL)                          /*!< ADC conversions are transferred to DR rigister */
#define LL_ADC_REG_DMA_TRANSFER_NONE       (0x00000000UL)                          /*!< ADC conversion data are not transferred by DMA but to DR register */
#define LL_ADC_REG_DMA_TRANSFER_LIMITED    (                    ADC_CFGR1_DMNGT_0) /*!< ADC conversion data are transferred by DMA, in limited mode (one shot mode): DMA transfer requests are stopped when number of DMA data transfers (number of ADC conversions) is reached. This ADC mode is intended to be used with DMA mode non-circular. */
#define LL_ADC_REG_DMA_TRANSFER_UNLIMITED  (ADC_CFGR1_DMNGT_1 | ADC_CFGR1_DMNGT_0) /*!< ADC conversion data are transferred by DMA, in unlimited mode: DMA transfer requests are unlimited, whatever number of DMA data transferred (number of ADC conversions). This ADC mode is intended to be used with DMA mode circular. */
#define LL_ADC_REG_MDF_TRANSFER            (ADC_CFGR1_DMNGT_1                    ) /*!< ADC conversion data are transferred to DFSDM */
/**
  * @}
  */
/** @defgroup ADC_LL_EC_REG_DMA_TRANSFER  ADC group regular - DMA transfer of ADC conversion data
  * @{
  */
#define LL_ADC_REG_DMA_TRANSFER_NONE_ADC4       (0x00000000UL)                        /*!< ADC conversions are not transferred by DMA */
#define LL_ADC_REG_DMA_TRANSFER_LIMITED_ADC4    (                   ADC4_CFGR1_DMAEN)  /*!< ADC conversion data are transferred by DMA, in limited mode (one shot mode): DMA transfer requests are stopped when number of DMA data transfers (number of ADC conversions) is reached. This ADC mode is intended to be used with DMA mode non-circular. */
#define LL_ADC_REG_DMA_TRANSFER_UNLIMITED_ADC4  (ADC4_CFGR1_DMACFG | ADC4_CFGR1_DMAEN)  /*!< ADC conversion data are transferred by DMA, in unlimited mode: DMA transfer requests are unlimited, whatever number of DMA data transferred (number of ADC conversions). This ADC mode is intended to be used with DMA mode circular. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_OVR_DATA_BEHAVIOR  ADC group regular - Overrun behavior on conversion data
  * @{
  */
#define LL_ADC_REG_OVR_DATA_PRESERVED      (0x00000000UL)         /*!< ADC group regular behavior in case of overrun: data preserved */
#define LL_ADC_REG_OVR_DATA_OVERWRITTEN    (ADC_CFGR1_OVRMOD)      /*!< ADC group regular behavior in case of overrun: data overwritten */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_MODE  ADC group regular - Sequencer configuration flexibility
  * @{
  */
#define LL_ADC_REG_SEQ_FIXED               (0x00000000UL)         /*!< Sequencer configured to not fully configurable: sequencer length and each rank affectation to a channel are fixed by channel HW number. Refer to description of function @ref LL_ADC_REG_SetSequencerChannels(). */
#define LL_ADC_REG_SEQ_CONFIGURABLE        (ADC4_CFGR1_CHSELRMOD)  /*!< Sequencer configured to fully configurable: sequencer length and each rank affectation to a channel are configurable. Refer to description of function @ref LL_ADC_REG_SetSequencerLength(). */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_SCAN_LENGTH  ADC group regular - Sequencer scan length
  * @{
  */
#define LL_ADC_REG_SEQ_SCAN_DISABLE        (0x00000000UL)                                              /*!< ADC group regular sequencer disable (equivalent to sequencer of 1 rank: ADC conversion on only 1 channel) */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS  (                                             ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 2 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS  (                              ADC_SQR1_L_1               ) /*!< ADC group regular sequencer enable with 3 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS  (                              ADC_SQR1_L_1 | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 4 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS  (               ADC_SQR1_L_2                              ) /*!< ADC group regular sequencer enable with 5 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS  (               ADC_SQR1_L_2                | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 6 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS  (               ADC_SQR1_L_2 | ADC_SQR1_L_1               ) /*!< ADC group regular sequencer enable with 7 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS  (               ADC_SQR1_L_2 | ADC_SQR1_L_1 | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 8 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS  (ADC_SQR1_L_3                                             ) /*!< ADC group regular sequencer enable with 9 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS (ADC_SQR1_L_3                               | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 10 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS (ADC_SQR1_L_3                | ADC_SQR1_L_1               ) /*!< ADC group regular sequencer enable with 11 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS (ADC_SQR1_L_3                | ADC_SQR1_L_1 | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 12 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_2                              ) /*!< ADC group regular sequencer enable with 13 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_2                | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 14 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_2 | ADC_SQR1_L_1               ) /*!< ADC group regular sequencer enable with 15 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_2 | ADC_SQR1_L_1 | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 16 ranks in the sequence */
/**
  * @}
  */
/** @defgroup ADC_LL_EC_REG_SEQ_SCAN_LENGTH  ADC group regular - Sequencer scan length
  * @{
  */
#define LL_ADC4_REG_SEQ_SCAN_DISABLE        (ADC_CHSELR_SQ2)       /*!< ADC group regular sequencer disable (equivalent to sequencer of 1 rank: ADC conversion on only 1 channel) */
#define LL_ADC4_REG_SEQ_SCAN_ENABLE_2RANKS  (ADC_CHSELR_SQ3)       /*!< ADC group regular sequencer enable with 2 ranks in the sequence */
#define LL_ADC4_REG_SEQ_SCAN_ENABLE_3RANKS  (ADC_CHSELR_SQ4)       /*!< ADC group regular sequencer enable with 3 ranks in the sequence */
#define LL_ADC4_REG_SEQ_SCAN_ENABLE_4RANKS  (ADC_CHSELR_SQ5)       /*!< ADC group regular sequencer enable with 4 ranks in the sequence */
#define LL_ADC4_REG_SEQ_SCAN_ENABLE_5RANKS  (ADC_CHSELR_SQ6)       /*!< ADC group regular sequencer enable with 5 ranks in the sequence */
#define LL_ADC4_REG_SEQ_SCAN_ENABLE_6RANKS  (ADC_CHSELR_SQ7)       /*!< ADC group regular sequencer enable with 6 ranks in the sequence */
#define LL_ADC4_REG_SEQ_SCAN_ENABLE_7RANKS  (ADC_CHSELR_SQ8)       /*!< ADC group regular sequencer enable with 7 ranks in the sequence */
#define LL_ADC4_REG_SEQ_SCAN_ENABLE_8RANKS  (0x00000000UL)         /*!< ADC group regular sequencer enable with 8 ranks in the sequence */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_DISCONT_MODE  ADC group regular - Sequencer discontinuous mode
  * @{
  */
#define LL_ADC_REG_SEQ_DISCONT_DISABLE     (0x00000000UL)                                                               /*!< ADC group regular sequencer discontinuous mode disable */
#define LL_ADC_REG_SEQ_DISCONT_1RANK       (ADC_CFGR1_DISCEN)                                                           /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every rank */
#define LL_ADC_REG_SEQ_DISCONT_2RANKS      (ADC_CFGR1_DISCNUM_0 | ADC_CFGR1_DISCEN)                                     /*!< ADC group regular sequencer discontinuous mode enabled with sequence interruption every 2 ranks */
#define LL_ADC_REG_SEQ_DISCONT_3RANKS      (ADC_CFGR1_DISCNUM_1 | ADC_CFGR1_DISCEN)                                     /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 3 ranks */
#define LL_ADC_REG_SEQ_DISCONT_4RANKS      (ADC_CFGR1_DISCNUM_1 | ADC_CFGR1_DISCNUM_0 | ADC_CFGR1_DISCEN)               /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 4 ranks */
#define LL_ADC_REG_SEQ_DISCONT_5RANKS      (ADC_CFGR1_DISCNUM_2 | ADC_CFGR1_DISCEN)                                     /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 5 ranks */
#define LL_ADC_REG_SEQ_DISCONT_6RANKS      (ADC_CFGR1_DISCNUM_2 | ADC_CFGR1_DISCNUM_0 | ADC_CFGR1_DISCEN)               /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 6 ranks */
#define LL_ADC_REG_SEQ_DISCONT_7RANKS      (ADC_CFGR1_DISCNUM_2 | ADC_CFGR1_DISCNUM_1 | ADC_CFGR1_DISCEN)               /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 7 ranks */
#define LL_ADC_REG_SEQ_DISCONT_8RANKS      (ADC_CFGR1_DISCNUM_2 | ADC_CFGR1_DISCNUM_1 | ADC_CFGR1_DISCNUM_0          \
                                            | ADC_CFGR1_DISCEN)                                                         /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 8 ranks */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_SCAN_DIRECTION  ADC group regular - Sequencer scan direction
  * @{
  */
#define LL_ADC_REG_SEQ_SCAN_DIR_FORWARD    (0x00000000UL)         /*!< On this STM32 series, parameter relevant only is sequencer set to mode not fully configurable, refer to function @ref LL_ADC_REG_SetSequencerConfigurable(). ADC group regular sequencer scan direction forward: from lowest channel number to highest channel number (scan of all ranks, ADC conversion of ranks with channels enabled in sequencer). On some other STM32 families, this setting is not available and the default scan direction is forward. */
#define LL_ADC_REG_SEQ_SCAN_DIR_BACKWARD   (ADC4_CFGR1_SCANDIR)   /*!< On this STM32 series, parameter relevant only is sequencer set to mode not fully configurable, refer to function @ref LL_ADC_REG_SetSequencerConfigurable(). ADC group regular sequencer scan direction backward: from highest channel number to lowest channel number (scan of all ranks, ADC conversion of ranks with channels enabled in sequencer) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_RANKS  ADC group regular - Sequencer ranks
  * @{
  */
#define LL_ADC_REG_RANK_1                  (ADC_SQR1_REGOFFSET | ADC_REG_RANK_1_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 1 */
#define LL_ADC_REG_RANK_2                  (ADC_SQR1_REGOFFSET | ADC_REG_RANK_2_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 2 */
#define LL_ADC_REG_RANK_3                  (ADC_SQR1_REGOFFSET | ADC_REG_RANK_3_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 3 */
#define LL_ADC_REG_RANK_4                  (ADC_SQR1_REGOFFSET | ADC_REG_RANK_4_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 4 */
#define LL_ADC_REG_RANK_5                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_5_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 5 */
#define LL_ADC_REG_RANK_6                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_6_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 6 */
#define LL_ADC_REG_RANK_7                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_7_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 7 */
#define LL_ADC_REG_RANK_8                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_8_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 8 */
#define LL_ADC_REG_RANK_9                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_9_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 9 */
#define LL_ADC_REG_RANK_10                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_10_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 10 */
#define LL_ADC_REG_RANK_11                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_11_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 11 */
#define LL_ADC_REG_RANK_12                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_12_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 12 */
#define LL_ADC_REG_RANK_13                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_13_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 13 */
#define LL_ADC_REG_RANK_14                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_14_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 14 */
#define LL_ADC_REG_RANK_15                 (ADC_SQR4_REGOFFSET | ADC_REG_RANK_15_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 15 */
#define LL_ADC_REG_RANK_16                 (ADC_SQR4_REGOFFSET | ADC_REG_RANK_16_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 16 */

#define LL_ADC_REG_RANK_1_ADC4              (ADC4_REG_RANK_1_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 1 */
#define LL_ADC_REG_RANK_2_ADC4              (ADC4_REG_RANK_2_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 2 */
#define LL_ADC_REG_RANK_3_ADC4              (ADC4_REG_RANK_3_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 3 */
#define LL_ADC_REG_RANK_4_ADC4              (ADC4_REG_RANK_4_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 4 */
#define LL_ADC_REG_RANK_5_ADC4              (ADC4_REG_RANK_5_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 5 */
#define LL_ADC_REG_RANK_6_ADC4              (ADC4_REG_RANK_6_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 6 */
#define LL_ADC_REG_RANK_7_ADC4              (ADC4_REG_RANK_7_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 7 */
#define LL_ADC_REG_RANK_8_ADC4              (ADC4_REG_RANK_8_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 8 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_TRIGGER_SOURCE  ADC group injected - Trigger source
  * @{
  */
#define LL_ADC_INJ_TRIG_SOFTWARE           (0x00000000UL)                                                                                                         /*!< ADC group injected conversion trigger internal: SW start. */
#define LL_ADC_INJ_TRIG_EXT_TIM1_TRGO      (ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                                        /*!< ADC group injected conversion trigger from external peripheral: TIM1 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM1_CH4       (ADC_JSQR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                   /*!< ADC group injected conversion trigger from external peripheral: TIM1 channel 4 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM2_TRGO      (ADC_JSQR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                   /*!< ADC group injected conversion trigger from external peripheral: TIM2 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM2_CH1       (ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                              /*!< ADC group injected conversion trigger from external peripheral: TIM2 channel 1 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM3_CH4       (ADC_JSQR_JEXTSEL_2 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                   /*!< ADC group injected conversion trigger from external peripheral: TIM3 channel 4 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM4_TRGO      (ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                              /*!< ADC group injected conversion trigger from external peripheral: TIM4 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_EXTI_LINE15    (ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                              /*!< ADC group injected conversion trigger from external peripheral: external interrupt line 15. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM8_CH4       (ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0             \
                                            | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                                      /*!< ADC group injected conversion trigger from external peripheral: TIM8 channel 4 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM1_TRGO2     (ADC_JSQR_JEXTSEL_3 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                   /*!< ADC group injected conversion trigger from external peripheral: TIM1 TRGO2 event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM8_TRGO      (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                              /*!< ADC group injected conversion trigger from external peripheral: TIM8 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM8_TRGO2     (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                              /*!< ADC group injected conversion trigger from external peripheral: TIM8 TRGO2 event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM3_CH3       (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0             \
                                            | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                                      /*!< ADC group injected conversion trigger from external peripheral: TIM3 channel 3 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM3_TRGO      (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                            /*!< ADC group injected conversion trigger from external peripheral: TIM3 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM3_CH1       (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0             \
                                            | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                                      /*!< ADC group injected conversion trigger from external peripheral: TIM3 channel 1 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM6_TRGO      (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1             \
                                            | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                                      /*!< ADC group injected conversion trigger from external peripheral: TIM6 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM15_TRGO     (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1             \
                                            | ADC_JSQR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                 /*!< ADC group injected conversion trigger from external peripheral: TIM15 TRGO event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_LPTIM1_CH2     (ADC_JSQR_JEXTSEL_4 | ADC_JSQR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                              /*!< ADC group injected conversion trigger from external peripheral: LPTIM1 OUT event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_LPTIM2_CH2     (ADC_JSQR_JEXTSEL_4 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0             \
                                            | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                                      /*!< ADC group injected conversion trigger from external peripheral: LPTIM2 OUT event. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_LPTIM3_CH1     (ADC_JSQR_JEXTSEL_4 | ADC_JSQR_JEXTSEL_2 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                              /*!< ADC group injected conversion trigger from external peripheral: LPTIM3 OUT event. 4 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_LPTIM4_OUT     (ADC_JSQR_JEXTSEL_4 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0             \
                                            | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                                      /*!< ADC group injected conversion trigger from external peripheral: LPTIM3 OUT event. 4 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */

/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_TRIGGER_EDGE  ADC group injected - Trigger edge
  * @{
  */
#define LL_ADC_INJ_TRIG_EXT_RISING         (                    ADC_JSQR_JEXTEN_0) /*!< ADC group injected conversion trigger polarity set to rising edge */
#define LL_ADC_INJ_TRIG_EXT_FALLING        (ADC_JSQR_JEXTEN_1                    ) /*!< ADC group injected conversion trigger polarity set to falling edge */
#define LL_ADC_INJ_TRIG_EXT_RISINGFALLING  (ADC_JSQR_JEXTEN_1 | ADC_JSQR_JEXTEN_0) /*!< ADC group injected conversion trigger polarity set to both rising and falling edges */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_TRIG_AUTO  ADC group injected - Automatic trigger mode
  * @{
  */
#define LL_ADC_INJ_TRIG_INDEPENDENT        (0x00000000UL)         /*!< ADC group injected conversion trigger independent. Setting mandatory if ADC group injected injected trigger source is set to an external trigger. */
#define LL_ADC_INJ_TRIG_FROM_GRP_REGULAR   (ADC_CFGR1_JAUTO)       /*!< ADC group injected conversion trigger from ADC group regular. Setting compliant only with group injected trigger source set to SW start, without any further action on  ADC group injected conversion start or stop: in this case, ADC group injected is controlled only from ADC group regular. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SAMPLING_MODE  ADC group regular - Sampling mode
  * @{
  */
#define LL_ADC_REG_SAMPLING_MODE_NORMAL             (0x00000000UL)     /*!< ADC conversions sampling phase duration is defined using  @ref ADC_LL_EC_CHANNEL_SAMPLINGTIME. */
#define LL_ADC_REG_SAMPLING_MODE_BULB               (ADC_CFGR2_BULB)   /*!< ADC conversions sampling phase starts immediately after end of conversion, and stops upon trigger event.
                                                                            Note: First conversion is using minimal
                                                                                  sampling time (see @ref
                                                                                  ADC_LL_EC_CHANNEL_SAMPLINGTIME). */
#define LL_ADC_REG_SAMPLING_MODE_TRIGGER_CONTROLED  (ADC_CFGR2_SMPTRIG)/*!< ADC conversions sampling phase is controlled by trigger events:
                                                                            Trigger rising edge  = start sampling
                                                                            Trigger falling edge = stop sampling and
                                                                            start conversion. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_SEQ_SCAN_LENGTH  ADC group injected - Sequencer scan length
  * @{
  */
#define LL_ADC_INJ_SEQ_SCAN_DISABLE        (0x00000000UL)                  /*!< ADC group injected sequencer disable (equivalent to sequencer of 1 rank: ADC conversion on only 1 channel) */
#define LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS  (                ADC_JSQR_JL_0) /*!< ADC group injected sequencer enable with 2 ranks in the sequence */
#define LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS  (ADC_JSQR_JL_1                ) /*!< ADC group injected sequencer enable with 3 ranks in the sequence */
#define LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS  (ADC_JSQR_JL_1 | ADC_JSQR_JL_0) /*!< ADC group injected sequencer enable with 4 ranks in the sequence */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_SEQ_DISCONT_MODE  ADC group injected - Sequencer discontinuous mode
  * @{
  */
#define LL_ADC_INJ_SEQ_DISCONT_DISABLE     (0x00000000UL)         /*!< ADC group injected sequencer discontinuous mode disable */
#define LL_ADC_INJ_SEQ_DISCONT_1RANK       (ADC_CFGR1_JDISCEN)     /*!< ADC group injected sequencer discontinuous mode enable with sequence interruption every rank */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_SEQ_RANKS  ADC group injected - Sequencer ranks
  * @{
  */
#define LL_ADC_INJ_RANK_1                  (ADC_JDR1_REGOFFSET | ADC_INJ_RANK_1_JSQR_BITOFFSET_POS) /*!< ADC group injected sequencer rank 1 */
#define LL_ADC_INJ_RANK_2                  (ADC_JDR2_REGOFFSET | ADC_INJ_RANK_2_JSQR_BITOFFSET_POS) /*!< ADC group injected sequencer rank 2 */
#define LL_ADC_INJ_RANK_3                  (ADC_JDR3_REGOFFSET | ADC_INJ_RANK_3_JSQR_BITOFFSET_POS) /*!< ADC group injected sequencer rank 3 */
#define LL_ADC_INJ_RANK_4                  (ADC_JDR4_REGOFFSET | ADC_INJ_RANK_4_JSQR_BITOFFSET_POS) /*!< ADC group injected sequencer rank 4 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CHANNEL_SAMPLINGTIME  Channel - Sampling time
  * @{
  */
#define LL_ADC_SAMPLINGTIME_5CYCLE       (0x00000000UL)                                              /*!< Sampling time 5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_6CYCLES      (                                        ADC_SMPR2_SMP10_0) /*!< Sampling time 6 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_12CYCLES     (                    ADC_SMPR2_SMP10_1                    ) /*!< Sampling time 12 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_20CYCLES     (                    ADC_SMPR2_SMP10_1 | ADC_SMPR2_SMP10_0) /*!< Sampling time 20 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_36CYCLES     (ADC_SMPR2_SMP10_2                                        ) /*!< Sampling time 36 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_68CYCLES     (ADC_SMPR2_SMP10_2                     | ADC_SMPR2_SMP10_0) /*!< Sampling time 68 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_391CYCLES_5  (ADC_SMPR2_SMP10_2 | ADC_SMPR2_SMP10_1                    ) /*!< Sampling time 391.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_814CYCLES    (ADC_SMPR2_SMP10_2 | ADC_SMPR2_SMP10_1 | ADC_SMPR2_SMP10_0) /*!< Sampling time 814 ADC clock cycles */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CHANNEL_SAMPLINGTIME  Channel - Sampling time
  * @{
  */
#define LL_ADC4_SAMPLINGTIME_1CYCLE_5       (0x00000000UL)                                        /*!< Sampling time 1.5 ADC clock cycle */
#define LL_ADC4_SAMPLINGTIME_3CYCLES_5      (ADC4_SMPR_SMP1_0)                                     /*!< Sampling time 3.5 ADC clock cycles */
#define LL_ADC4_SAMPLINGTIME_7CYCLES_5      (ADC4_SMPR_SMP1_1)                                     /*!< Sampling time 7.5 ADC clock cycles */
#define LL_ADC4_SAMPLINGTIME_12CYCLES_5     (ADC4_SMPR_SMP1_1 | ADC4_SMPR_SMP1_0)                   /*!< Sampling time 12.5 ADC clock cycles */
#define LL_ADC4_SAMPLINGTIME_19CYCLES_5     (ADC4_SMPR_SMP1_2)                                     /*!< Sampling time 19.5 ADC clock cycles */
#define LL_ADC4_SAMPLINGTIME_39CYCLES_5     (ADC4_SMPR_SMP1_2 | ADC4_SMPR_SMP1_0)                   /*!< Sampling time 39.5 ADC clock cycles */
#define LL_ADC4_SAMPLINGTIME_79CYCLES_5     (ADC4_SMPR_SMP1_2 | ADC4_SMPR_SMP1_1)                   /*!< Sampling time 79.5 ADC clock cycles */
#define LL_ADC4_SAMPLINGTIME_160CYCLES_5    (ADC4_SMPR_SMP1_2 | ADC4_SMPR_SMP1_1 | ADC4_SMPR_SMP1_0) /*!< Sampling time 160.5 ADC clock cycles */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CHANNEL_SINGLE_DIFF_ENDING  Channel - Single or differential ending
  * @{
  */
#define LL_ADC_SINGLE_ENDED                (0x0000FFFFUL)                                    /*!< ADC channel ending set to single ended (literal also used to set calibration mode) */
#define LL_ADC_DIFFERENTIAL_ENDED          (0xFFFF0000UL)                                    /*!< ADC channel ending set to differential (literal also used to set calibration mode) */
#define LL_ADC_BOTH_SINGLE_DIFF_ENDED      (LL_ADC_SINGLE_ENDED | LL_ADC_DIFFERENTIAL_ENDED) /*!< ADC channel ending set to both single ended and differential (literal used only to set calibration factors) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_AWD_NUMBER Analog watchdog - Analog watchdog number
  * @{
  */
#define LL_ADC_AWD1                        (ADC_AWD_CR1_CHANNEL_MASK  | ADC_AWD_CR1_REGOFFSET) /*!< ADC analog watchdog number 1 */
#define LL_ADC_AWD2                        (ADC_AWD_CR23_CHANNEL_MASK | ADC_AWD_CR2_REGOFFSET) /*!< ADC analog watchdog number 2 */
#define LL_ADC_AWD3                        (ADC_AWD_CR23_CHANNEL_MASK | ADC_AWD_CR3_REGOFFSET) /*!< ADC analog watchdog number 3 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_AWD_CHANNELS  Analog watchdog - Monitored channels
  * @{
  */
#define LL_ADC_AWD_DISABLE                 (0x00000000UL)                                                                                      /*!< ADC analog watchdog monitoring disabled */
#define LL_ADC_AWD_ALL_CHANNELS_REG        ((0x000FFFFFUL) | ADC_CFGR1_AWD1EN)                                                                 /*!< ADC analog watchdog monitoring of all channels, converted by group regular only */
#define LL_ADC_AWD_ALL_CHANNELS_INJ        ((0x000FFFFFUL) | ADC_CFGR1_JAWD1EN)                                                                /*!< ADC analog watchdog monitoring of all channels, converted by group injected only */
#define LL_ADC_AWD_ALL_CHANNELS_REG_INJ    ((0x000FFFFFUL) | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN)                                             /*!< ADC analog watchdog monitoring of all channels, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_0_REG           ((LL_ADC_CHANNEL_0  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN0, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_0_INJ           ((LL_ADC_CHANNEL_0  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN0, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_0_REG_INJ       ((LL_ADC_CHANNEL_0  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN0, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_1_REG           ((LL_ADC_CHANNEL_1  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN1, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_1_INJ           ((LL_ADC_CHANNEL_1  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN1, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_1_REG_INJ       ((LL_ADC_CHANNEL_1  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN1, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_2_REG           ((LL_ADC_CHANNEL_2  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN2, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_2_INJ           ((LL_ADC_CHANNEL_2  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN2, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_2_REG_INJ       ((LL_ADC_CHANNEL_2  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN2, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_3_REG           ((LL_ADC_CHANNEL_3  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN3, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_3_INJ           ((LL_ADC_CHANNEL_3  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN3, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_3_REG_INJ       ((LL_ADC_CHANNEL_3  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN3, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_4_REG           ((LL_ADC_CHANNEL_4  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN4, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_4_INJ           ((LL_ADC_CHANNEL_4  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN4, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_4_REG_INJ       ((LL_ADC_CHANNEL_4  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN4, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_5_REG           ((LL_ADC_CHANNEL_5  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN5, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_5_INJ           ((LL_ADC_CHANNEL_5  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN5, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_5_REG_INJ       ((LL_ADC_CHANNEL_5  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN5, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_6_REG           ((LL_ADC_CHANNEL_6  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN6, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_6_INJ           ((LL_ADC_CHANNEL_6  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN6, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_6_REG_INJ       ((LL_ADC_CHANNEL_6  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN6, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_7_REG           ((LL_ADC_CHANNEL_7  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN7, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_7_INJ           ((LL_ADC_CHANNEL_7  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN7, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_7_REG_INJ       ((LL_ADC_CHANNEL_7  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN7, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_8_REG           ((LL_ADC_CHANNEL_8  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN8, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_8_INJ           ((LL_ADC_CHANNEL_8  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN8, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_8_REG_INJ       ((LL_ADC_CHANNEL_8  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN8, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_9_REG           ((LL_ADC_CHANNEL_9  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN9, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_9_INJ           ((LL_ADC_CHANNEL_9  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN9, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_9_REG_INJ       ((LL_ADC_CHANNEL_9  & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN9, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_10_REG          ((LL_ADC_CHANNEL_10 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN10, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_10_INJ          ((LL_ADC_CHANNEL_10 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN10, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_10_REG_INJ      ((LL_ADC_CHANNEL_10 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN10, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_11_REG          ((LL_ADC_CHANNEL_11 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN11, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_11_INJ          ((LL_ADC_CHANNEL_11 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN11, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_11_REG_INJ      ((LL_ADC_CHANNEL_11 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN11, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_12_REG          ((LL_ADC_CHANNEL_12 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN12, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_12_INJ          ((LL_ADC_CHANNEL_12 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN12, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_12_REG_INJ      ((LL_ADC_CHANNEL_12 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN12, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_13_REG          ((LL_ADC_CHANNEL_13 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN13, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_13_INJ          ((LL_ADC_CHANNEL_13 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN13, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_13_REG_INJ      ((LL_ADC_CHANNEL_13 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN13, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_14_REG          ((LL_ADC_CHANNEL_14 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN14, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_14_INJ          ((LL_ADC_CHANNEL_14 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN14, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_14_REG_INJ      ((LL_ADC_CHANNEL_14 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN14, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_15_REG          ((LL_ADC_CHANNEL_15 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN15, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_15_INJ          ((LL_ADC_CHANNEL_15 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN15, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_15_REG_INJ      ((LL_ADC_CHANNEL_15 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN15, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_16_REG          ((LL_ADC_CHANNEL_16 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN16, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_16_INJ          ((LL_ADC_CHANNEL_16 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN16, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_16_REG_INJ      ((LL_ADC_CHANNEL_16 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN16, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_17_REG          ((LL_ADC_CHANNEL_17 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN17, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_17_INJ          ((LL_ADC_CHANNEL_17 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN17, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_17_REG_INJ      ((LL_ADC_CHANNEL_17 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN17, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_18_REG          ((LL_ADC_CHANNEL_18 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN18, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_18_INJ          ((LL_ADC_CHANNEL_18 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN18, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_18_REG_INJ      ((LL_ADC_CHANNEL_18 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN18, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_19_REG          ((LL_ADC_CHANNEL_19 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_19_INJ          ((LL_ADC_CHANNEL_19 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_19_REG_INJ      ((LL_ADC_CHANNEL_19 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_20_REG          ((LL_ADC_CHANNEL_20 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_20_INJ          ((LL_ADC_CHANNEL_20 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_20_REG_INJ      ((LL_ADC_CHANNEL_20 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_21_REG          ((LL_ADC_CHANNEL_21 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_21_INJ          ((LL_ADC_CHANNEL_21 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_21_REG_INJ      ((LL_ADC_CHANNEL_21 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_22_REG          ((LL_ADC_CHANNEL_22 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_22_INJ          ((LL_ADC_CHANNEL_22 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_22_REG_INJ      ((LL_ADC_CHANNEL_22 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_23_REG          ((LL_ADC_CHANNEL_23 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_AWD1EN      \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_23_INJ          ((LL_ADC_CHANNEL_23 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1SGL)                                                                               /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_23_REG_INJ      ((LL_ADC_CHANNEL_23 & ADC_CHANNEL_ID_NUMBER_MASK) | ADC_CFGR1_JAWD1EN     \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN19, converted by either group regular or injected */
#define LL_ADC_AWD_CH_VREFINT_REG          ((LL_ADC_CHANNEL_VREFINT          & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC internal channel connected to VrefInt: Internal voltage reference, converted by group regular only */
#define LL_ADC_AWD_CH_VREFINT_INJ          ((LL_ADC_CHANNEL_VREFINT          & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1SGL)                                                           /*!< ADC analog watchdog monitoring of ADC internal channel connected to VrefInt: Internal voltage reference, converted by group injected only */
#define LL_ADC_AWD_CH_VREFINT_REG_INJ      ((LL_ADC_CHANNEL_VREFINT          & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                        /*!< ADC analog watchdog monitoring of ADC internal channel connected to VrefInt: Internal voltage reference, converted by either group regular or injected */
#define LL_ADC_AWD_CH_TEMPSENSOR_REG       ((LL_ADC_CHANNEL_TEMPSENSOR       & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC internal channel connected to Temperature sensor, converted by group regular only */
#define LL_ADC_AWD_CH_TEMPSENSOR_INJ       ((LL_ADC_CHANNEL_TEMPSENSOR       & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1SGL)                                                           /*!< ADC analog watchdog monitoring of ADC internal channel connected to Temperature sensor, converted by group injected only */
#define LL_ADC_AWD_CH_TEMPSENSOR_REG_INJ   ((LL_ADC_CHANNEL_TEMPSENSOR       & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                        /*!< ADC analog watchdog monitoring of ADC internal channel connected to Temperature sensor, converted by either group regular or injected */
#define LL_ADC_AWD_CH_VBAT_REG             ((LL_ADC_CHANNEL_VBAT             & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC internal channel connected to Vbat/4: Vbat voltage through a divider ladder of factor 1/4 to have Vbat always below Vdda, converted by group regular only */
#define LL_ADC_AWD_CH_VBAT_INJ             ((LL_ADC_CHANNEL_VBAT             & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1SGL)                                                           /*!< ADC analog watchdog monitoring of ADC internal channel connected to Vbat/4: Vbat voltage through a divider ladder of factor 1/4 to have Vbat always below Vdda, converted by group injected only */
#define LL_ADC_AWD_CH_VBAT_REG_INJ         ((LL_ADC_CHANNEL_VBAT             & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                        /*!< ADC analog watchdog monitoring of ADC internal channel connected to Vbat/4: Vbat voltage through a divider ladder of factor 1/4 to have Vbat always below Vdda */
#define LL_ADC_AWD_CH_VCORE_REG            ((LL_ADC_CHANNEL_VCORE            & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC internal channel connected to VrefInt: Internal voltage reference, converted by group regular only */
#define LL_ADC_AWD_CH_VCORE_INJ            ((LL_ADC_CHANNEL_VCORE            & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_JAWD1EN  | ADC_CFGR1_AWD1SGL)                                                          /*!< ADC analog watchdog monitoring of ADC internal channel connected to VrefInt: Internal voltage reference, converted by group injected only */
#define LL_ADC_AWD_CH_VCORE_REG_INJ        ((LL_ADC_CHANNEL_VCORE            & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                        /*!< ADC analog watchdog monitoring of ADC internal channel connected to VrefInt: Internal voltage reference, converted by either group regular or injected */

#define LL_ADC_AWD_CH_DAC1CH1_ADC4_REG     ((LL_ADC_CHANNEL_DAC1CH1_ADC4     & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 1, channel specific to ADC4, converted by group regular only */
#define LL_ADC_AWD_CH_DAC1CH2_ADC4_REG     ((LL_ADC_CHANNEL_DAC1CH2_ADC4     & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 2, channel specific to ADC4, converted by group regular only */
#define LL_ADC_AWD_CH_TEMPSENSOR_ADC4_REG  ((LL_ADC_CHANNEL_TEMPSENSOR_ADC4  & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC internal channel connected to emperature sensor, channel specific to ADC4, converted by group regular only */
#define LL_ADC_AWD_CH_VBAT_ADC4_REG        ((LL_ADC_CHANNEL_VBAT_ADC4        & ADC_CHANNEL_ID_NUMBER_MASK)           \
                                            | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                                                            /*!< ADC analog watchdog monitoring of ADC internal channel connected to Vbat/4: Vbat voltage through a divider ladder of factor 1/4 to have Vbat always below Vdda, channel specific to ADC4, converted by group regular only */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_AWD_THRESHOLDS  Analog watchdog - Thresholds
  * @{
  */
#define LL_ADC_AWD_THRESHOLD_HIGH          (0x1UL)                     /*!< ADC analog watchdog threshold high */
#define LL_ADC_AWD_THRESHOLD_LOW           (0x0UL)                     /*!< ADC analog watchdog threshold low */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_AWD_FILTERING_CONFIG  Analog watchdog - filtering config
  * @{
  */
#define LL_ADC_AWD_FILTERING_NONE          (0x00000000UL)                                              /*!< ADC analog wathdog no filtering, one out-of-window sample is needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_2SAMPLES      (                                        ADC_HTR_AWDFILT_0) /*!< ADC analog wathdog 2 consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_3SAMPLES      (                    ADC_HTR_AWDFILT_1                    ) /*!< ADC analog wathdog 3 consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_4SAMPLES      (                    ADC_HTR_AWDFILT_1 | ADC_HTR_AWDFILT_0) /*!< ADC analog wathdog 4 consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_5SAMPLES      (ADC_HTR_AWDFILT_2                                        ) /*!< ADC analog wathdog 5 consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_6SAMPLES      (ADC_HTR_AWDFILT_2 |                     ADC_HTR_AWDFILT_0) /*!< ADC analog wathdog 6 consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_7SAMPLES      (ADC_HTR_AWDFILT_2 | ADC_HTR_AWDFILT_1                    ) /*!< ADC analog wathdog 7 consecutives out-of-window samples are needed to raise flag or interrupt */
#define LL_ADC_AWD_FILTERING_8SAMPLES      (ADC_HTR_AWDFILT_2 | ADC_HTR_AWDFILT_1 | ADC_HTR_AWDFILT_0) /*!< ADC analog wathdog 8 consecutives out-of-window samples are needed to raise flag or interrupt */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OVS_SCOPE  Oversampling - Oversampling scope
  * @{
  */
#define LL_ADC_OVS_DISABLE                 (0x00000000UL)                                        /*!< ADC oversampling disabled. */
#define LL_ADC_OVS_GRP_REGULAR_CONTINUED   (                                    ADC_CFGR2_ROVSE) /*!< ADC oversampling on conversions of ADC group regular. If group injected interrupts group regular: when ADC group injected is triggered, the oversampling on ADC group regular is temporary stopped and continued afterwards. */
#define LL_ADC_OVS_GRP_REGULAR_RESUMED     (ADC_CFGR2_ROVSM |                   ADC_CFGR2_ROVSE) /*!< ADC oversampling on conversions of ADC group regular. If group injected interrupts group regular: when ADC group injected is triggered, the oversampling on ADC group regular is resumed from start (oversampler buffer reset). */
#define LL_ADC_OVS_GRP_INJECTED            (                  ADC_CFGR2_JOVSE                  ) /*!< ADC oversampling on conversions of ADC group injected. */
#define LL_ADC_OVS_GRP_INJ_REG_RESUMED     (                  ADC_CFGR2_JOVSE | ADC_CFGR2_ROVSE) /*!< ADC oversampling on conversions of both ADC groups regular and injected. If group injected interrupting group regular: when ADC group injected is triggered, the oversampling on ADC group regular is resumed from start (oversampler buffer reset). */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OVS_DISCONT_MODE  Oversampling - Discontinuous mode
  * @{
  */
#define LL_ADC_OVS_REG_CONT                (0x00000000UL)         /*!< ADC oversampling discontinuous mode: continuous mode (all conversions of oversampling ratio are done from 1 trigger) */
#define LL_ADC_OVS_REG_DISCONT             (ADC_CFGR2_TROVS)      /*!< ADC oversampling discontinuous mode: discontinuous mode (each conversion of oversampling ratio needs a trigger) */
/**
  * @}
  */
/** @defgroup ADC_LL_EC_OVS_RATIO  Oversampling - Ratio
  * @{
  */
#define LL_ADC_OVS_RATIO_2                 (0x00000000UL)                                           /*!< ADC oversampling ratio of 2 (2 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_4                 (                                       ADC4_CFGR2_OVSR_0) /*!< ADC oversampling ratio of 4 (4 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_8                 (                    ADC4_CFGR2_OVSR_1                    ) /*!< ADC oversampling ratio of 8 (8 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_16                (                    ADC4_CFGR2_OVSR_1 | ADC4_CFGR2_OVSR_0) /*!< ADC oversampling ratio of 16 (16 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_32                (ADC4_CFGR2_OVSR_2                                      ) /*!< ADC oversampling ratio of 32 (32 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_64                (ADC4_CFGR2_OVSR_2                     | ADC4_CFGR2_OVSR_0) /*!< ADC oversampling ratio of 64 (64 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_128               (ADC4_CFGR2_OVSR_2 | ADC4_CFGR2_OVSR_1                   ) /*!< ADC oversampling ratio of 128 (128 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_256               (ADC4_CFGR2_OVSR_2 | ADC4_CFGR2_OVSR_1 | ADC4_CFGR2_OVSR_0) /*!< ADC oversampling ratio of 256 (256 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OVS_SHIFT  Oversampling - Data shift
  * @{
  */
#define LL_ADC_OVS_SHIFT_NONE              (0x00000000UL)                                                              /*!< ADC oversampling no shift (sum of the ADC conversions data is not divided to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_SHIFT_RIGHT_1           (                                                         ADC_CFGR2_OVSS_0) /*!< ADC oversampling shift of 1 (sum of the ADC conversions data is divided by 2 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_SHIFT_RIGHT_2           (                                      ADC_CFGR2_OVSS_1                   ) /*!< ADC oversampling shift of 2 (sum of the ADC conversions data is divided by 4 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_SHIFT_RIGHT_3           (                                      ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0) /*!< ADC oversampling shift of 3 (sum of the ADC conversions data is divided by 8 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_SHIFT_RIGHT_4           (                   ADC_CFGR2_OVSS_2                                      ) /*!< ADC oversampling shift of 4 (sum of the ADC conversions data is divided by 16 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_SHIFT_RIGHT_5           (                   ADC_CFGR2_OVSS_2                    | ADC_CFGR2_OVSS_0) /*!< ADC oversampling shift of 5 (sum of the ADC conversions data is divided by 32 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_SHIFT_RIGHT_6           (                   ADC_CFGR2_OVSS_2 | ADC_CFGR2_OVSS_1                   ) /*!< ADC oversampling shift of 6 (sum of the ADC conversions data is divided by 64 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_SHIFT_RIGHT_7           (                   ADC_CFGR2_OVSS_2 | ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0) /*!< ADC oversampling shift of 7 (sum of the ADC conversions data is divided by 128 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_SHIFT_RIGHT_8           (ADC_CFGR2_OVSS_3                                                         ) /*!< ADC oversampling shift of 8 (sum of the ADC conversions data is divided by 256 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_SHIFT_RIGHT_9           (ADC_CFGR2_OVSS_3                                       | ADC_CFGR2_OVSS_0) /*!< ADC oversampling shift of 9 (sum of the ADC conversions data is divided by 512 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_SHIFT_RIGHT_10          (ADC_CFGR2_OVSS_3                    | ADC_CFGR2_OVSS_1                   ) /*!< ADC oversampling shift of 10 (sum of the ADC conversions data is divided by 1024 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_SHIFT_RIGHT_11          (ADC_CFGR2_OVSS_3                    | ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0) /*!< ADC oversampling shift of 11 (sum of the ADC conversions data is divided by 2048 to result as the ADC oversampling conversion data) */
/**
  * @}
  */

#if defined(ADC_MULTIMODE_SUPPORT)
/** @defgroup ADC_LL_EC_MULTI_MODE  Multimode - Mode
  * @{
  */
#define LL_ADC_MULTI_INDEPENDENT           (0x00000000UL)                                                      /*!< ADC dual mode disabled (ADC independent mode) */
#define LL_ADC_MULTI_DUAL_REG_SIMULT       (                 ADC_CCR_DUAL_2 | ADC_CCR_DUAL_1                 ) /*!< ADC dual mode enabled: group regular simultaneous */
#define LL_ADC_MULTI_DUAL_REG_INTERL       (                 ADC_CCR_DUAL_2 | ADC_CCR_DUAL_1 | ADC_CCR_DUAL_0) /*!< ADC dual mode enabled: Combined group regular interleaved */
#define LL_ADC_MULTI_DUAL_INJ_SIMULT       (                 ADC_CCR_DUAL_2                  | ADC_CCR_DUAL_0) /*!< ADC dual mode enabled: group injected simultaneous */
#define LL_ADC_MULTI_DUAL_INJ_ALTERN       (ADC_CCR_DUAL_3                                   | ADC_CCR_DUAL_0) /*!< ADC dual mode enabled: group injected alternate trigger. Works only with external triggers (not internal SW start) */
#define LL_ADC_MULTI_DUAL_REG_SIM_INJ_SIM  (                                                   ADC_CCR_DUAL_0) /*!< ADC dual mode enabled: Combined group regular simultaneous + group injected simultaneous */
#define LL_ADC_MULTI_DUAL_REG_SIM_INJ_ALT  (                                  ADC_CCR_DUAL_1                 ) /*!< ADC dual mode enabled: Combined group regular simultaneous + group injected alternate trigger */
#define LL_ADC_MULTI_DUAL_REG_INT_INJ_SIM  (                                  ADC_CCR_DUAL_1 | ADC_CCR_DUAL_0) /*!< ADC dual mode enabled: Combined group regular interleaved + group injected simultaneous */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_MULTI_DMA_TRANSFER  Multimode - DMA transfer
  * @{
  */
#define LL_ADC_MULTI_REG_DMA_EACH_ADC        (0x00000000UL)                      /*!< ADC multimode group regular conversions are transferred by DMA: each ADC uses its own DMA channel, with its individual DMA transfer settings */
#define LL_ADC_MULTI_REG_DMA_RES_32_10B      (ADC_CCR_DAMDF_1                  ) /*!< ADC multimode group regular conversions are transferred by DMA, one DMA channel for both ADC (DMA of ADC master). Setting for ADC resolution of 32 (16x2) down to 10 bits */
#define LL_ADC_MULTI_REG_DMA_RES_8B          (ADC_CCR_DAMDF_1 | ADC_CCR_DAMDF_0) /*!< ADC multimode group regular conversions are transferred by DMA, one DMA channel for both ADC (DMA of ADC master). Setting for ADC resolution of 8 bits */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_MULTI_TWOSMP_DELAY  Multimode - Delay between two sampling phases
  * @{
  */
#define LL_ADC_MULTI_TWOSMP_DELAY_1CYCLE_5          (0x00000000UL)                                                    /*!< ADC multimode delay between two sampling phases: 1.5 ADC clock cycle for all resolution                    */
#define LL_ADC_MULTI_TWOSMP_DELAY_2CYCLES_5         (                                                ADC_CCR_DELAY_0) /*!< ADC multimode delay between two sampling phases: 2.5 ADC clock cycles for all resolution                   */
#define LL_ADC_MULTI_TWOSMP_DELAY_3CYCLES_5         (                                ADC_CCR_DELAY_1                ) /*!< ADC multimode delay between two sampling phases: 3.5 ADC clock cycles for all resolution                   */
#define LL_ADC_MULTI_TWOSMP_DELAY_4CYCLES_5         (                                ADC_CCR_DELAY_1|ADC_CCR_DELAY_0) /*!< ADC multimode delay between two sampling phases: 4.5 ADC clock cycles for 16, 14, 12 or 10 bits resolution */
#define LL_ADC_MULTI_TWOSMP_DELAY_4CYCLES_5_8_BITS  (                ADC_CCR_DELAY_2|ADC_CCR_DELAY_1|ADC_CCR_DELAY_0) /*!< ADC multimode delay between two sampling phases: 4.5 ADC clock cycles  for 8 bits resolution               */
#define LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES_5         (                ADC_CCR_DELAY_2                                ) /*!< ADC multimode delay between two sampling phases: 5.5 ADC clock cycles for 16, 14, 12 bits resolution       */
#define LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES_5_10_BITS (                ADC_CCR_DELAY_2|ADC_CCR_DELAY_1|ADC_CCR_DELAY_0) /*!< ADC multimode delay between two sampling phases: 5.5 ADC clock cycles for 10 bits resolution               */
#define LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES           (ADC_CCR_DELAY_3                                                ) /*!< ADC multimode delay between two sampling phases: 6 ADC clock cycles for 10 or 8 bits resolution            */
#define LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES_5         (                ADC_CCR_DELAY_2                |ADC_CCR_DELAY_0) /*!< ADC multimode delay between two sampling phases: 6.5 ADC clock cycles for 16 or 14 bits resolution         */
#define LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES_5_12_BITS (                ADC_CCR_DELAY_2|ADC_CCR_DELAY_1|ADC_CCR_DELAY_0) /*!< ADC multimode delay between two sampling phases: 6.5 ADC clock cycles for 12 bits resolution               */
#define LL_ADC_MULTI_TWOSMP_DELAY_7CYCLES_5         (                ADC_CCR_DELAY_2|ADC_CCR_DELAY_1|ADC_CCR_DELAY_0) /*!< ADC multimode delay between two sampling phases: 7.5 ADC clock cycles for 16 bits resolution               */
#define LL_ADC_MULTI_TWOSMP_DELAY_8CYCLES           (ADC_CCR_DELAY_3                                                ) /*!< ADC multimode delay between two sampling phases: 8 ADC clock cycles for 12 bits resolution                 */
#define LL_ADC_MULTI_TWOSMP_DELAY_9CYCLES           (ADC_CCR_DELAY_3                                                ) /*!< ADC multimode delay between two sampling phases: 9 ADC clock cycles for 16 or 14 bits resolution           */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_MULTI_MASTER_SLAVE  Multimode - ADC master or slave
  * @{
  */
#define LL_ADC_MULTI_MASTER                (                    ADC_CDR_RDATA_MST) /*!< In multimode, selection among several ADC instances: ADC master */
#define LL_ADC_MULTI_SLAVE                 (ADC_CDR_RDATA_SLV                    ) /*!< In multimode, selection among several ADC instances: ADC slave */
#define LL_ADC_MULTI_MASTER_SLAVE          (ADC_CDR_RDATA_SLV | ADC_CDR_RDATA_MST) /*!< In multimode, selection among several ADC instances: both ADC master and ADC slave */
/**
  * @}
  */

#endif /* ADC_MULTIMODE_SUPPORT */

/** @defgroup ADC_LL_EC_HW_DELAYS  Definitions of ADC hardware constraints delays
  * @note   Only ADC peripheral HW delays are defined in ADC LL driver driver,
  *         not timeout values.
  *         For details on delays values, refer to descriptions in source code
  *         above each literal definition.
  * @{
  */

/* Note: Only ADC peripheral HW delays are defined in ADC LL driver driver,   */
/*       not timeout values.                                                  */
/*       Timeout values for ADC operations are dependent to device clock      */
/*       configuration (system clock versus ADC clock),                       */
/*       and therefore must be defined in user application.                   */
/*       Indications for estimation of ADC timeout delays, for this           */
/*       STM32 series:                                                        */
/*       - ADC calibration time: maximum delay is 16384/fADC.                 */
/*         (refer to device datasheet, parameter "tCAL")                      */
/*       - ADC enable time: maximum delay is 1 conversion cycle.              */
/*         (refer to device datasheet, parameter "tSTAB")                     */
/*       - ADC disable time: maximum delay should be a few ADC clock cycles   */
/*       - ADC stop conversion time: maximum delay should be a few ADC clock  */
/*         cycles                                                             */
/*       - ADC conversion time: duration depending on ADC clock and ADC       */
/*         configuration.                                                     */
/*         (refer to device reference manual, section "Timing")               */

/* Delay for ADC stabilization time (ADC voltage regulator start-up time)     */
/* Delay set to maximum value (refer to device datasheet,                     */
/* parameter "tADCVREG_STUP").                                                */
/* Unit: us                                                                   */
#define LL_ADC_DELAY_INTERNAL_REGUL_STAB_US ( 20UL)  /*!< Delay for ADC stabilization time (ADC voltage regulator start-up time) */

/* Delay for internal voltage reference stabilization time.                   */
/* Delay set to maximum value (refer to device datasheet,                     */
/* parameter "ts_vrefint").                                                   */
/* Unit: us                                                                   */
#define LL_ADC_DELAY_VREFINT_STAB_US       (5UL)  /*!< Delay for internal voltage reference stabilization time */

/* Delay for temperature sensor stabilization time.                           */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART_RUN").                                                   */
/* Unit: us                                                                   */
#define LL_ADC_DELAY_TEMPSENSOR_STAB_US    ( 26UL)  /*!< Delay for temperature sensor stabilization time */

/* Delay required between ADC end of calibration and ADC enable.              */
/* Note: On this STM32 series, a minimum number of ADC clock cycles           */
/*       are required between ADC end of calibration and ADC enable.          */
/*       Wait time can be computed in user application by waiting for the     */
/*       equivalent number of CPU cycles, by taking into account              */
/*       ratio of CPU clock versus ADC clock prescalers.                      */
/* Unit: ADC clock cycles.                                                    */
#define LL_ADC_DELAY_CALIB_ENABLE_ADC_CYCLES (  4UL)  /*!< Delay required between ADC end of calibration and ADC enable */

/* Fixed timeout value for ADC linearity word bit set/clear delay.                         */
/* Values defined to be higher than worst cases: low clock frequency,                      */
/* maximum prescalers.                                                                     */
/* Ex of profile low frequency : f_ADC at 4,577 Khz (minimum value                         */
/* according to Data sheet), linearity set/clear bit delay MAX = 6 / f_ADC + 3 cycles AHB  */
/*           6 / 4577 = 1,311ms                                                            */
/* At maximum CPU speed (400 MHz), this means                                              */
/*    3.58 * 400 MHz = 524400 CPU cycles                                                   */
#define ADC_LINEARITY_BIT_TOGGLE_TIMEOUT         (524400UL)      /*!< ADC linearity set/clear bit delay */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Macros ADC Exported Macros
  * @{
  */

/** @defgroup ADC_LL_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in ADC register
  * @param  __INSTANCE__ ADC Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_ADC_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in ADC register
  * @param  __INSTANCE__ ADC Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_ADC_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/** @defgroup ADC_LL_EM_HELPER_MACRO ADC helper macro
  * @{
  */

/**
  * @brief  Helper macro to get ADC channel number in decimal format
  *         from literals LL_ADC_CHANNEL_x.
  * @note   Example:
  *           __LL_ADC_CHANNEL_TO_DECIMAL_NB(LL_ADC_CHANNEL_4)
  *           will return decimal number "4".
  * @note   The input can be a value from functions where a channel
  *         number is returned, either defined with number
  *         or with bitfield (only one bit must be set).
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT         (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR      (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT            (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4    (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4    (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4       (2)
  *         @arg @ref LL_ADC_CHANNEL_VCORE           (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/ADC2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  * @retval Value between Min_Data=0 and Max_Data=18
  */
#define __LL_ADC_CHANNEL_TO_DECIMAL_NB(__CHANNEL__)                                          \
  ((((__CHANNEL__) & ADC_CHANNEL_ID_BITFIELD_MASK) == 0UL)                                   \
   ? ( ((__CHANNEL__) & ADC_CHANNEL_ID_NUMBER_MASK) >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS ) \
   : ( (uint32_t)POSITION_VAL((__CHANNEL__)) )                                               \
  )

/**
  * @brief  Helper macro to get ADC channel in literal format LL_ADC_CHANNEL_x
  *         from number in decimal format.
  * @note   Example:
  *           __LL_ADC_DECIMAL_NB_TO_CHANNEL(4)
  *           will return a data equivalent to "LL_ADC_CHANNEL_4".
  * @param  __DECIMAL_NB__ Value between Min_Data=0 and Max_Data=18
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT         (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR      (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT            (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4    (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4    (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4       (2)
  *         @arg @ref LL_ADC_CHANNEL_VCORE           (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/ADC2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  *         (1, 2) For ADC channel read back from ADC register,
  *                comparison with internal channel parameter to be done
  *                using helper macro @ref __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  */
#define __LL_ADC_DECIMAL_NB_TO_CHANNEL(__DECIMAL_NB__)                                                  \
  (((__DECIMAL_NB__) <= 9UL)                                                                            \
   ? (((__DECIMAL_NB__) << ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)                              |          \
      (ADC_AWD2CR_AWD2CH_0 << (__DECIMAL_NB__))                                              |          \
      (ADC_SMPR1_REGOFFSET))                                                                            \
   : (((__DECIMAL_NB__) << ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)                              |          \
      (ADC_AWD2CR_AWD2CH_0 << (__DECIMAL_NB__))                                              |          \
      (ADC_SMPR2_REGOFFSET))                                                                            \
  )

/**
  * @brief  Helper macro to convert ADC1 resolution to ADC4 resolution bit values.
  * @note   Example 1:
  *           __LL_ADC_RESOLUTION_ADC1_TO_ADC4(LL_ADC_RESOLUTION_6B)
  *           will return a data equivalent to "(ADC_CFGR1_RES_1 | ADC_CFGR1_RES_0)".
  * @note   Example 2:
  *           __LL_ADC_RESOLUTION_ADC1_TO_ADC4(LL_ADC_RESOLUTION_10B)
  *           will return a data equivalent to "(ADC_CFGR1_RES_0)".
  * @param  __RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @retval Returned value can be one of the following values:
  *         @arg 0x00000000UL                                     (value correspodning to ADC4 12 bits)
  *         @arg ADC_CFGR1_RES_0 = 0x00000004UL                   (value correspodning to ADC4 10 bits)
  *         @arg ADC_CFGR1_RES_1 = 0x00000008UL                   (value corresponding to ADC4  8 bits)
  *         @arg ADC_CFGR1_RES_1 | ADC_CFGR1_RES_0 = 0x0000000CUL (value corresponding to ADC4  6 bits)
  */

#define __LL_ADC_RESOLUTION_ADC1_TO_ADC4(__RESOLUTION__)                                        \
  (((__RESOLUTION__)  == LL_ADC_RESOLUTION_6B)                                                  \
   ? ((LL_ADC_RESOLUTION_8B))                                                                   \
   : ((((__RESOLUTION__)-1UL) & ADC_CFGR1_RES_Msk))                                             \
  )

/**
  * @brief  Helper macro to convert ADC4 resolution bit values to ADC1 resolution.
  * @note   Example 1:
  *           __LL_ADC_RESOLUTION_ADC4_TO_ADC1((ADC_CFGR1_RES_1 | ADC_CFGR1_RES_0))
  *           will return a data equivalent to "LL_ADC_RESOLUTION_6B".
  * @note   Example 2:
  *           __LL_ADC_RESOLUTION_ADC1_TO_ADC4((ADC_CFGR1_RES_0))
  *           will return a data equivalent to "LL_ADC_RESOLUTION_10B".
  * @param  __RESOLUTION__ This parameter can be one of the following values:
  *         @arg 0x00000000UL                                     (value correspodning to ADC4 12 bits)
  *         @arg ADC_CFGR1_RES_0 = 0x00000004UL                   (value correspodning to ADC4 10 bits)
  *         @arg ADC_CFGR1_RES_1 = 0x00000008UL                   (value corresponding to ADC4  8 bits)
  *         @arg ADC_CFGR1_RES_1 | ADC_CFGR1_RES_0 = 0x0000000CUL (value corresponding to ADC4  6 bits)
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  */

#define __LL_ADC_RESOLUTION_ADC4_TO_ADC1(__RESOLUTION__)                                              \
  (((__RESOLUTION__)  == LL_ADC_RESOLUTION_8B)                                                        \
   ? ((LL_ADC_RESOLUTION_6B))                                                                         \
   : ((((((__RESOLUTION__) >> ADC_CFGR1_RES_Pos) + 1UL)  << ADC_CFGR1_RES_Pos) & ADC_CFGR1_RES_Msk))  \
  )
/**
  * @brief  Helper macro to determine whether the selected channel
  *         corresponds to literal definitions of driver.
  * @note   The different literal definitions of ADC channels are:
  *         - ADC internal channel:
  *           LL_ADC_CHANNEL_VREFINT, LL_ADC_CHANNEL_TEMPSENSOR, ...
  *         - ADC external channel (channel connected to a GPIO pin):
  *           LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...
  * @note   The channel parameter must be a value defined from literal
  *         definition of a ADC internal channel (LL_ADC_CHANNEL_VREFINT,
  *         LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         ADC external channel (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...),
  *         must not be a value from functions where a channel number is
  *         returned from ADC registers,
  *         because internal and external channels share the same channel
  *         number in ADC registers. The differentiation is made only with
  *         parameters definitions of driver.
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT         (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR      (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT            (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4    (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4    (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4       (2)
  *         @arg @ref LL_ADC_CHANNEL_VCORE           (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/ADC2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  * @retval Value "0" if the channel corresponds to a parameter definition of a ADC external channel
   *        (channel connected to a GPIO pin).
  *         Value "1" if the channel corresponds to a parameter definition of a ADC internal channel.
  */
#define __LL_ADC_IS_CHANNEL_INTERNAL(__CHANNEL__)                              \
  (((__CHANNEL__) & ADC_CHANNEL_ID_INTERNAL_CH_MASK) != 0UL)

/**
  * @brief  Helper macro to convert a channel defined from parameter
  *         definition of a ADC internal channel (LL_ADC_CHANNEL_VREFINT,
  *         LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         to its equivalent parameter definition of a ADC external channel
  *         (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...).
  * @note   The channel parameter can be, additionally to a value
  *         defined from parameter definition of a ADC internal channel
  *         (LL_ADC_CHANNEL_VREFINT, LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         a value defined from parameter definition of
  *         ADC external channel (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...)
  *         or a value from functions where a channel number is returned
  *         from ADC registers.
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT         (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR      (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT            (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4    (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4    (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4       (2)
  *         @arg @ref LL_ADC_CHANNEL_VCORE           (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/ADC2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  */
#define __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL(__CHANNEL__)                     \
  ((__CHANNEL__) & ~ADC_CHANNEL_ID_INTERNAL_CH_MASK)

/**
  * @brief  Helper macro to determine whether the internal channel
  *         selected is available on the ADC instance selected.
  * @note   The channel parameter must be a value defined from parameter
  *         definition of a ADC internal channel (LL_ADC_CHANNEL_VREFINT,
  *         LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         must not be a value defined from parameter definition of
  *         ADC external channel (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...)
  *         or a value from functions where a channel number is
  *         returned from ADC registers,
  *         because internal and external channels share the same channel
  *         number in ADC registers. The differentiation is made only with
  *         parameters definitions of driver.
  * @param  __ADC_INSTANCE__ ADC instance
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_VREFINT         (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR      (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT            (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4    (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4    (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4       (2)
  *         @arg @ref LL_ADC_CHANNEL_VCORE           (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/ADC2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  * @retval Value "0" if the internal channel selected is not available on the ADC instance selected.
  *         Value "1" if the internal channel selected is available on the ADC instance selected.
  */
#if defined(ADC2)
#define __LL_ADC_IS_CHANNEL_INTERNAL_AVAILABLE(__ADC_INSTANCE__, __CHANNEL__)  \
  ((((__ADC_INSTANCE__) == ADC4) &&( ((__CHANNEL__) == LL_ADC_CHANNEL_DAC1CH1_ADC4)    ||                    \
                                     ((__CHANNEL__) == LL_ADC_CHANNEL_DAC1CH2_ADC4)    ||                    \
                                     ((__CHANNEL__) == LL_ADC_CHANNEL_TEMPSENSOR_ADC4) ||                    \
                                     ((__CHANNEL__) == LL_ADC_CHANNEL_VBAT_ADC4) )                           \
   )                                                                           \
   ||                                                                          \
   (((__ADC_INSTANCE__) == ADC1) ||  ((__ADC_INSTANCE__) == ADC2)              \
    &&(((__CHANNEL__) == LL_ADC_CHANNEL_TEMPSENSOR)   ||                       \
       ((__CHANNEL__) == LL_ADC_CHANNEL_VBAT)         ||                       \
       ((__CHANNEL__) == LL_ADC_CHANNEL_VREFINT) )                             \
   )                                                                           \
  )
#else
#define __LL_ADC_IS_CHANNEL_INTERNAL_AVAILABLE(__ADC_INSTANCE__, __CHANNEL__)  \
  ((((__ADC_INSTANCE__) == ADC4)                                               \
    &&(((__CHANNEL__) == LL_ADC_CHANNEL_DAC1CH1_ADC4)    ||                    \
       ((__CHANNEL__) == LL_ADC_CHANNEL_DAC1CH2_ADC4)    ||                    \
       ((__CHANNEL__) == LL_ADC_CHANNEL_TEMPSENSOR_ADC4) ||                    \
       ((__CHANNEL__) == LL_ADC_CHANNEL_VBAT_ADC4) )                           \
   )                                                                           \
   ||                                                                          \
   (((__ADC_INSTANCE__) == ADC1)                                               \
    &&(((__CHANNEL__) == LL_ADC_CHANNEL_TEMPSENSOR)   ||                       \
       ((__CHANNEL__) == LL_ADC_CHANNEL_VBAT)         ||                       \
       ((__CHANNEL__) == LL_ADC_CHANNEL_VREFINT)  )                            \
   )                                                                           \
  )
#endif /* ADC2 */
/**
  * @brief  Helper macro to define ADC analog watchdog parameter:
  *         define a single channel to monitor with analog watchdog
  *         from sequencer channel and groups definition.
  * @note   To be used with function @ref LL_ADC_SetAnalogWDMonitChannels().
  *         Example:
  *           LL_ADC_SetAnalogWDMonitChannels(
  *             ADC1, LL_ADC_AWD1,
  *             __LL_ADC_ANALOGWD_CHANNEL_GROUP(LL_ADC_CHANNEL4, LL_ADC_GROUP_REGULAR))
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT         (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR      (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT            (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4    (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4    (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4       (2)
  *         @arg @ref LL_ADC_CHANNEL_VCORE           (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/ADC2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  *         (1, 2) For ADC channel read back from ADC register,
  *                comparison with internal channel parameter to be done
  *                using helper macro @ref __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  * @param  __GROUP__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_GROUP_REGULAR
  *         @arg @ref LL_ADC_GROUP_INJECTED
  *         @arg @ref LL_ADC_GROUP_REGULAR_INJECTED
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_AWD_DISABLE
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG        (0)
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_INJ        (0)
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_19_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_19_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_19_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG          (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_INJ          (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG_INJ         (1)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG       (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_INJ       (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG_INJ      (1)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_REG             (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_INJ             (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_REG_INJ            (1)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC4_REG     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC4_REG     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_ADC4_REG  (2)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_ADC4_REG        (2)
  *         @arg @ref LL_ADC_AWD_CH_VCORE_REG            (2)
  *
  *         (0) On STM32U5, parameter available only on analog watchdog number: AWD1.
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  */
#define __LL_ADC_ANALOGWD_CHANNEL_GROUP(__CHANNEL__, __GROUP__)                                           \
  (((__GROUP__) == LL_ADC_GROUP_REGULAR)                                                                  \
   ? (((__CHANNEL__) & ADC_AWD_CHANNEL_MASK) | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)                      \
   :                                                                                                      \
   ((__GROUP__) == LL_ADC_GROUP_INJECTED)                                                                 \
   ? (((__CHANNEL__) & ADC_AWD_CHANNEL_MASK) | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1SGL)                     \
   :                                                                                                      \
   (((__CHANNEL__) & ADC_AWD_CHANNEL_MASK) | ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)   \
  )

/**
  * @brief  Helper macro to set the value of ADC analog watchdog threshold high
  *         or low in function of ADC resolution, when ADC resolution is
  *         different of 14 bits in case of ADC1 and 12 bits in case of ADC4.
  * @note   To be used with function @ref LL_ADC_SetAnalogWDThresholds().
  *         Example, with a ADC resolution of 8 bits, to set the value of
  *         analog watchdog threshold high (on 8 bits):
  *           LL_ADC_SetAnalogWDThresholds
  *            (< ADCx param >,
  *             __LL_ADC_ANALOGWD_SET_THRESHOLD_RESOLUTION(LL_ADC_RESOLUTION_8B, <threshold_value_8_bits>)
  *            );
  * @param  __ADC_INSTANCE__ ADC instance
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_14B   (1)
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B    (2)
  * @param  __AWD_THRESHOLD__ Value between Min_Data=0x000000 and Max_Data=0x1FFFFFF, In case of ADC1 insatnce
  *         __AWD_THRESHOLD__ Value between Min_Data=0x000 and Max_Data=0xFFF, In case of ADC4 insatnce
  * @retval In case of ADC1 insatnce, Value between Min_Data=0x000000 and Max_Data=0x1FFFFFF
  *         In case of ADC4 insatnce, Value between Min_Data=0x000 and Max_Data=0xFFF
  *
  *         (1): Only for ADC1 instance
  *         (2): Only for ADC4 insatnce
  */
#define __LL_ADC_ANALOGWD_SET_THRESHOLD_RESOLUTION(__ADC_INSTANCE__, __ADC_RESOLUTION__, __AWD_THRESHOLD__)           \
  (((__ADC_INSTANCE__) == ADC1)                                                                                       \
   ? ((__AWD_THRESHOLD__) << ((__ADC_RESOLUTION__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1U )))                            \
   :                                                                                                                  \
   ((__AWD_THRESHOLD__) << ((__LL_ADC_RESOLUTION_ADC1_TO_ADC4(__ADC_RESOLUTION__))                                    \
                            >> (ADC_CFGR_RES_BITOFFSET_POS - 1U )))                                                   \
  )

/**
  * @brief  Helper macro to get the value of ADC analog watchdog threshold high
  *         or low in function of ADC resolution, when ADC resolution is
  *         different of 14 bits in case of ADC1 and 12 bits in case of ADC4.
  * @note   To be used with function @ref LL_ADC_GetAnalogWDThresholds().
  *         Example, with a ADC resolution of 8 bits, to get the value of
  *         analog watchdog threshold high (on 8 bits):
  *           < threshold_value_8_bits > = __LL_ADC_ANALOGWD_GET_THRESHOLD_RESOLUTION
  *            (LL_ADC_RESOLUTION_8B,
  *             LL_ADC_GetAnalogWDThresholds(<ADCx param>, LL_ADC_AWD_THRESHOLD_HIGH)
  *            );
  * @param  __ADC_INSTANCE__ ADC instance
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_14B   (1)
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B    (2)
  * @param  __AWD_THRESHOLD__ Value between Min_Data=0x000000 and Max_Data=0x1FFFFFF, In case of ADC1 insatnce
  *         __AWD_THRESHOLD__ Value between Min_Data=0x000 and Max_Data=0xFFF, In case of ADC4 insatnce
  * @retval In case of ADC1 insatnce, Value between Min_Data=0x000000 and Max_Data=0x1FFFFFF
  *         In case of ADC4 insatnce, Value between Min_Data=0x000 and Max_Data=0xFFF
  *
  *         (1): Only for ADC1 instance
  *         (2): Only for ADC4 insatnce
  */
#define __LL_ADC_ANALOGWD_GET_THRESHOLD_RESOLUTION(__ADC_INSTANCE__, __ADC_RESOLUTION__, __AWD_THRESHOLD__)           \
  (((__ADC_INSTANCE__) == ADC1)                                                                                       \
   ? ((__AWD_THRESHOLD__) >> ((__ADC_RESOLUTION__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1U )))                            \
   :                                                                                                                  \
   ((__AWD_THRESHOLD__) >> ((__LL_ADC_RESOLUTION_ADC1_TO_ADC4(__ADC_RESOLUTION__))                                    \
                            >> (ADC_CFGR_RES_BITOFFSET_POS - 1U )))                                                   \
  )

/**
  * @brief  Helper macro to set the ADC calibration value with both single ended
  *         and differential modes calibration factors concatenated.
  * @note   To be used with function @ref LL_ADC_SetCalibrationOffsetFactor().
  *         Example, to set calibration factors single ended to 0x55
  *         and differential ended to 0x2A:
  *           LL_ADC_SetCalibrationOffsetFactor(
  *             ADC1,
  *             __LL_ADC_CALIB_FACTOR_SINGLE_DIFF(0x55, 0x2A))
  * @param  __CALIB_FACTOR_SINGLE_ENDED__ Value between Min_Data=0x00 and Max_Data=0x7F
  * @param  __CALIB_FACTOR_DIFFERENTIAL__ Value between Min_Data=0x00 and Max_Data=0x7F
  * @retval Value between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF
  */
#define __LL_ADC_CALIB_FACTOR_SINGLE_DIFF(__CALIB_FACTOR_SINGLE_ENDED__, __CALIB_FACTOR_DIFFERENTIAL__)        \
  (((__CALIB_FACTOR_DIFFERENTIAL__) << ADC_SINGLEDIFF_CALIB_F_BIT_D_POS) | (__CALIB_FACTOR_SINGLE_ENDED__))

#if defined(ADC_MULTIMODE_SUPPORT)
/**
  * @brief  Helper macro to get the ADC multimode conversion data of ADC master
  *         or ADC slave from raw value with both ADC conversion data concatenated.
  * @note   This macro is intended to be used when multimode transfer by DMA
  *         is enabled: refer to function @ref LL_ADC_SetMultiDMATransfer().
  *         In this case the transferred data need to processed with this macro
  *         to separate the conversion data of ADC master and ADC slave.
  * @param  __ADC_MULTI_MASTER_SLAVE__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_MASTER
  *         @arg @ref LL_ADC_MULTI_SLAVE
  * @param  __ADC_MULTI_CONV_DATA__ Value between Min_Data=0x000 and Max_Data=0xFFF
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFF
  */
#define __LL_ADC_MULTI_CONV_DATA_MASTER_SLAVE(__ADC_MULTI_MASTER_SLAVE__, __ADC_MULTI_CONV_DATA__) \
  (((__ADC_MULTI_CONV_DATA__) >> ((ADC_CDR_RDATA_SLV_Pos) & ~(__ADC_MULTI_MASTER_SLAVE__))) & ADC_CDR_RDATA_MST)
#endif /* ADC_MULTIMODE_SUPPORT */

/**
  * @brief  Helper macro to select, from a ADC instance, to which ADC instance
  *         it has a dependence in multimode (ADC master of the corresponding
  *         ADC common instance).
  * @note   In case of device with multimode available and a mix of
  *         ADC instances compliant and not compliant with multimode feature,
  *         ADC instances not compliant with multimode feature are
  *         considered as master instances (do not depend to
  *         any other ADC instance).
  * @param  __ADCx__ ADC instance
  * @retval __ADCx__ ADC instance master of the corresponding ADC common instance
  */
#if defined(ADC2)
#define __LL_ADC_MULTI_INSTANCE_MASTER(__ADCx__) \
  (((__ADCx__) == ADC2) ? (ADC1) : (__ADCx__))
#else
#define __LL_ADC_MULTI_INSTANCE_MASTER(__ADCx__) (__ADCx__)
#endif /* ADC2 */
/**
  * @brief  Helper macro to select the ADC common instance
  *         to which is belonging the selected ADC instance.
  * @note   ADC common register instance can be used for:
  *         - Set parameters common to several ADC instances
  *         - Multimode (for devices with several ADC instances)
  *         Refer to functions having argument "ADCxy_COMMON" as parameter.
  * @param  __ADCx__ ADC instance
  * @retval ADC common register instance
  */
#define __LL_ADC_COMMON_INSTANCE(__ADCx__)                                     \
  (((__ADCx__) == ADC1) ? (ADC12_COMMON) : (ADC4_COMMON))

/**
  * @brief  Helper macro to check if all ADC instances sharing the same
  *         ADC common instance are disabled.
  * @note   This check is required by functions with setting conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  *         Refer to functions having argument "ADCxy_COMMON" as parameter.
  * @note   On devices with only 1 ADC common instance, parameter of this macro
  *         is useless and can be ignored (parameter kept for compatibility
  *         with devices featuring several ADC common instances).
  * @param  __ADCXY_COMMON__ ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval Value "0" if all ADC instances sharing the same ADC common instance
  *         are disabled.
  *         Value "1" if at least one ADC instance sharing the same ADC common instance
  *         is enabled.
  */
#if defined(ADC2)
#define __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE(__ADCXY_COMMON__)              \
  (((__ADCXY_COMMON__) == ADC12_COMMON) ? (LL_ADC_IsEnabled(ADC1) | LL_ADC_IsEnabled(ADC2)) : (LL_ADC_IsEnabled(ADC4)))
#else
#define __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE(__ADCXY_COMMON__)              \
  (((__ADCXY_COMMON__) == ADC12_COMMON) ? (LL_ADC_IsEnabled(ADC1)) : (LL_ADC_IsEnabled(ADC4)))
#endif /* ADC2 */

/**
  * @brief  Helper macro to define the ADC conversion data full-scale digital
  *         value corresponding to the selected ADC resolution.
  * @note   ADC conversion data full-scale corresponds to voltage range
  *         determined by analog voltage references Vref+ and Vref-
  *         (refer to reference manual).
  * @param  __ADC_INSTANCE__ ADC instance
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_14B
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @retval ADC conversion data full-scale digital value (unit: digital value of ADC conversion data)
  */
#define __LL_ADC_DIGITAL_SCALE(__ADC_INSTANCE__, __ADC_RESOLUTION__)                                  \
  (((__ADC_INSTANCE__) == ADC1)                                                                       \
   ?((0x3FFFUL) >> (((__ADC_RESOLUTION__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1UL)) & 0x6UL))            \
   :                                                                                                  \
   ((0xFFFUL) >> ((__LL_ADC_RESOLUTION_ADC1_TO_ADC4(__ADC_RESOLUTION__)                               \
                   >> (ADC_CFGR_RES_BITOFFSET_POS - 1UL)) & 0x6UL))                                   \
  )

/**
  * @brief  Helper macro to convert the ADC conversion data from
  *         a resolution to another resolution.
  * @param  __ADC_INSTANCE__ ADC instance
  * @param  __DATA__ ADC conversion data to be converted
  * @param  __ADC_RESOLUTION_CURRENT__ Resolution of the data to be converted
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_14B (1)
  *         @arg @ref LL_ADC_RESOLUTION_12B (2)
  *         @arg @ref LL_ADC_RESOLUTION_10B (2)
  *         @arg @ref LL_ADC_RESOLUTION_8B  (2)
  * @param  __ADC_RESOLUTION_TARGET__ Resolution of the data after conversion
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_14B (1)
  *         @arg @ref LL_ADC_RESOLUTION_12B (2)
  *         @arg @ref LL_ADC_RESOLUTION_10B (2)
  *         @arg @ref LL_ADC_RESOLUTION_8B  (2)
  *               (1): Specific to ADC1 instance
  *               (2): Common to all instances but different bits positions
  * @retval ADC conversion data to the requested resolution
  */
#define __LL_ADC_CONVERT_DATA_RESOLUTION(__ADC_INSTANCE__, __DATA__,\
                                         __ADC_RESOLUTION_CURRENT__,\
                                         __ADC_RESOLUTION_TARGET__)                                            \
(((__ADC_INSTANCE__) == ADC1)                                                                                  \
 ?((__DATA__)                                                                                                  \
   << ((__ADC_RESOLUTION_CURRENT__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1UL)))                                    \
 >> ((__ADC_RESOLUTION_TARGET__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1UL))                                        \
 :                                                                                                             \
 ((__DATA__)                                                                                                   \
  << ((__LL_ADC_RESOLUTION_ADC1_TO_ADC4(__ADC_RESOLUTION_CURRENT__)) >> (ADC_CFGR_RES_BITOFFSET_POS - 1UL)))   \
 >> ((__LL_ADC_RESOLUTION_ADC1_TO_ADC4(__ADC_RESOLUTION_TARGET__)) >> (ADC_CFGR_RES_BITOFFSET_POS - 1UL))      \
)

/**
  * @brief  Helper macro to calculate the voltage (unit: mVolt)
  *         corresponding to a ADC conversion data (unit: digital value).
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref __LL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @param  __VREFANALOG_VOLTAGE__ Analog reference voltage (unit: mV)
  * @param  __ADC_DATA__ ADC conversion data (resolution 16 bits)
  *                       (unit: digital value).
  * @param  __ADC_INSTANCE__ ADC instance
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_14B (1)
  *         @arg @ref LL_ADC_RESOLUTION_12B (3)
  *         @arg @ref LL_ADC_RESOLUTION_10B (3)
  *         @arg @ref LL_ADC_RESOLUTION_8B  (3)
  *         @arg @ref LL_ADC_RESOLUTION_6B  (2)
  *               (1): Specific to ADC1 instance
  *               (2): Specific to ADC4 instance
  *               (3): Common to all instances but different bits positions
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define __LL_ADC_CALC_DATA_TO_VOLTAGE(__ADC_INSTANCE__, __VREFANALOG_VOLTAGE__,\
                                      __ADC_DATA__,                            \
                                      __ADC_RESOLUTION__)                      \
((__ADC_DATA__) * (__VREFANALOG_VOLTAGE__)                                   \
 / __LL_ADC_DIGITAL_SCALE(__ADC_INSTANCE__, __ADC_RESOLUTION__)              \
)

/**
  * @brief  Helper macro to calculate analog reference voltage (Vref+)
  *         (unit: mVolt) from ADC conversion data of internal voltage
  *         reference VrefInt.
  * @note   Computation is using VrefInt calibration value
  *         stored in system memory for each device during production.
  * @note   This voltage depends on user board environment: voltage level
  *         connected to pin Vref+.
  *         On devices with small package, the pin Vref+ is not present
  *         and internally bonded to pin Vdda.
  * @note   On this STM32 series, calibration data of internal voltage reference
  *         VrefInt corresponds to a resolution of 16 bits,
  *         this is the recommended ADC resolution to convert voltage of
  *         internal voltage reference VrefInt.
  *         Otherwise, this macro performs the processing to scale
  *         ADC conversion data to 14 bits.
  * @param  __ADC_INSTANCE__ ADC instance
  * @param  __VREFINT_ADC_DATA__ ADC conversion data (resolution 16 bits)
  *         of internal voltage reference VrefInt (unit: digital value).
  * @param  __ADC_RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_14B (1)
  *         @arg @ref LL_ADC_RESOLUTION_12B (3)
  *         @arg @ref LL_ADC_RESOLUTION_10B (3)
  *         @arg @ref LL_ADC_RESOLUTION_8B  (3)
  *         @arg @ref LL_ADC_RESOLUTION_6B  (2)
  *               (1): Specific to ADC1 instance
  *               (2): Specific to ADC4 instance
  *               (3): Common to all instances but different bits positions
  * @retval Analog reference voltage (unit: mV)
  */
#define __LL_ADC_CALC_VREFANALOG_VOLTAGE(__ADC_INSTANCE__, __VREFINT_ADC_DATA__,    \
                                         __ADC_RESOLUTION__)                        \
(((__ADC_INSTANCE__) == ADC1)                                                     \
 ?((uint32_t)(*VREFINT_CAL_ADDR) * VREFINT_CAL_VREF)                              \
 / __LL_ADC_CONVERT_DATA_RESOLUTION((__ADC_INSTANCE__), (__VREFINT_ADC_DATA__),\
                                    (__ADC_RESOLUTION__),                      \
                                    LL_ADC_RESOLUTION_14B)                     \
 :                                                                              \
 ((uint32_t)(*VREFINT_CAL_ADDR) * VREFINT_CAL_VREF)                              \
 / __LL_ADC_CONVERT_DATA_RESOLUTION((__ADC_INSTANCE__), (__VREFINT_ADC_DATA__),\
                                    (__ADC_RESOLUTION__),                      \
                                    LL_ADC_RESOLUTION_12B)                     \
)

/**
  * @brief  Helper macro to calculate the temperature (unit: degree Celsius)
  *         from ADC conversion data of internal temperature sensor.
  * @note   Computation is using temperature sensor calibration values
  *         stored in system memory for each device during production.
  * @note   Calculation formula:
  *           Temperature = ((TS_ADC_DATA - TS_CAL1)
  *                           * (TS_CAL2_TEMP - TS_CAL1_TEMP))
  *                         / (TS_CAL2 - TS_CAL1) + TS_CAL1_TEMP
  *           with TS_ADC_DATA = temperature sensor raw data measured by ADC
  *                Avg_Slope = (TS_CAL2 - TS_CAL1)
  *                            / (TS_CAL2_TEMP - TS_CAL1_TEMP)
  *                TS_CAL1   = equivalent TS_ADC_DATA at temperature
  *                            TEMP_DEGC_CAL1 (calibrated in factory)
  *                TS_CAL2   = equivalent TS_ADC_DATA at temperature
  *                            TEMP_DEGC_CAL2 (calibrated in factory)
  *         Caution: Calculation relevancy under reserve that calibration
  *                  parameters are correct (address and data).
  *                  To calculate temperature using temperature sensor
  *                  datasheet typical values (generic values less, therefore
  *                  less accurate than calibrated values),
  *                  use helper macro @ref __LL_ADC_CALC_TEMPERATURE_TYP_PARAMS().
  * @note   As calculation input, the analog reference voltage (Vref+) must be
  *         defined as it impacts the ADC LSB equivalent voltage.
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref __LL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @note   On this STM32 series, calibration data of temperature sensor
  *         corresponds to a resolution of 14 bits,
  *         this is the recommended ADC resolution to convert voltage of
  *         temperature sensor.
  *         Otherwise, this macro performs the processing to scale
  *         ADC conversion data to 14 bits.
  * @param  __ADC_INSTANCE__ ADC instance
  * @param  __VREFANALOG_VOLTAGE__  Analog reference voltage (unit: mV)
  * @param  __TEMPSENSOR_ADC_DATA__ ADC conversion data of internal
  *                                 temperature sensor (unit: digital value).
  * @param  __ADC_RESOLUTION__      ADC resolution at which internal temperature
  *                                 sensor voltage has been measured.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_14B (1)
  *         @arg @ref LL_ADC_RESOLUTION_12B (3)
  *         @arg @ref LL_ADC_RESOLUTION_10B (3)
  *         @arg @ref LL_ADC_RESOLUTION_8B  (3)
  *         @arg @ref LL_ADC_RESOLUTION_6B  (2)
  *               (1): Specific to ADC1 instance
  *               (2): Specific to ADC4 instance
  *               (3): Common to all instances but different bits positions
  * @retval Temperature (unit: degree Celsius)
  */
#define __LL_ADC_CALC_TEMPERATURE(__ADC_INSTANCE__, __VREFANALOG_VOLTAGE__,                          \
                                  __TEMPSENSOR_ADC_DATA__,                                           \
                                  __ADC_RESOLUTION__)                                                \
(((__ADC_INSTANCE__) == ADC1)                                                                        \
 ?(((( ((int32_t)((__LL_ADC_CONVERT_DATA_RESOLUTION((__ADC_INSTANCE__), (__TEMPSENSOR_ADC_DATA__),   \
                                                    (__ADC_RESOLUTION__),                            \
                                                    LL_ADC_RESOLUTION_14B)                           \
                   * (__VREFANALOG_VOLTAGE__))                                                       \
                  / TEMPSENSOR_CAL_VREFANALOG)                                                       \
        - (int32_t) *TEMPSENSOR_CAL1_ADDR)                                                           \
     ) * (int32_t)(TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP)                                      \
    ) / (int32_t)((int32_t)*TEMPSENSOR_CAL2_ADDR - (int32_t)*TEMPSENSOR_CAL1_ADDR)                   \
   ) + TEMPSENSOR_CAL1_TEMP                                                                          \
  )                                                                                                  \
 :                                                                                                   \
 (((( ((int32_t)((__LL_ADC_CONVERT_DATA_RESOLUTION((__ADC_INSTANCE__), (__TEMPSENSOR_ADC_DATA__),    \
                                                   (__ADC_RESOLUTION__),                             \
                                                   LL_ADC_RESOLUTION_12B)                            \
                  * (__VREFANALOG_VOLTAGE__))                                                        \
                 / TEMPSENSOR_CAL_VREFANALOG)                                                        \
       - (int32_t) (*TEMPSENSOR_CAL1_ADDR >> 2 ))                                                    \
    ) * (int32_t)(TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP)                                       \
   ) / (int32_t)((int32_t)(*TEMPSENSOR_CAL2_ADDR >> 2 ) - (int32_t)(*TEMPSENSOR_CAL1_ADDR >> 2) )    \
  ) + TEMPSENSOR_CAL1_TEMP                                                                           \
 )                                                                                                   \
)

/**
  * @brief  Helper macro to calculate the temperature (unit: degree Celsius)
  *         from ADC conversion data of internal temperature sensor.
  * @note   Computation is using temperature sensor typical values
  *         (refer to device datasheet).
  * @note   Calculation formula:
  *           Temperature = (TS_TYP_CALx_VOLT(uV) - TS_ADC_DATA * Conversion_uV)
  *                         / Avg_Slope + CALx_TEMP
  *           with TS_ADC_DATA      = temperature sensor raw data measured by ADC
  *                                   (unit: digital value)
  *                Avg_Slope        = temperature sensor slope
  *                                   (unit: uV/Degree Celsius)
  *                TS_TYP_CALx_VOLT = temperature sensor digital value at
  *                                   temperature CALx_TEMP (unit: mV)
  *         Caution: Calculation relevancy under reserve the temperature sensor
  *                  of the current device has characteristics in line with
  *                  datasheet typical values.
  *                  If temperature sensor calibration values are available on
  *                  on this device (presence of macro __LL_ADC_CALC_TEMPERATURE()),
  *                  temperature calculation will be more accurate using
  *                  helper macro @ref __LL_ADC_CALC_TEMPERATURE().
  * @note   As calculation input, the analog reference voltage (Vref+) must be
  *         defined as it impacts the ADC LSB equivalent voltage.
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref __LL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @note   ADC measurement data must correspond to a resolution of 14 bits
  *         (full scale digital value 4095). If not the case, the data must be
  *         preliminarily rescaled to an equivalent resolution of 14 bits.
  * @param  __ADC_INSTANCE__ ADC instance
  * @param  __TEMPSENSOR_TYP_AVGSLOPE__  Device datasheet data: Temperature sensor slope typical value
  *                                      (unit: uV/DegCelsius).
  *                                      On STM32U5, refer to device datasheet parameter "Avg_Slope".
  * @param  __TEMPSENSOR_TYP_CALX_V__    Device datasheet data: Temperature sensor voltage typical value
  *                                      (at temperature and Vref+ defined in parameters below) (unit: mV).
  *                                      On STM32U5, refer to device datasheet parameter "V30"
  *                                      (corresponding to TS_CAL1).
  * @param  __TEMPSENSOR_CALX_TEMP__     Device datasheet data: Temperature at which temperature sensor voltage
  *                                      see parameter above) is corresponding (unit: mV)
  * @param  __VREFANALOG_VOLTAGE__       Analog voltage reference (Vref+) voltage (unit: mV)
  * @param  __TEMPSENSOR_ADC_DATA__      ADC conversion data of internal temperature sensor (unit: digital value).
  * @param  __ADC_RESOLUTION__           ADC resolution at which internal temperature sensor voltage has been measured.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_14B (1)
  *         @arg @ref LL_ADC_RESOLUTION_12B (3)
  *         @arg @ref LL_ADC_RESOLUTION_10B (3)
  *         @arg @ref LL_ADC_RESOLUTION_8B  (3)
  *         @arg @ref LL_ADC_RESOLUTION_6B  (2)
  *               (1): Specific to ADC1 instance
  *               (2): Specific to ADC4 instance
  *               (3): Common to all instances but different bits positions
  * @retval Temperature (unit: degree Celsius)
  */
#define __LL_ADC_CALC_TEMPERATURE_TYP_PARAMS(__ADC_INSTANCE__, __TEMPSENSOR_TYP_AVGSLOPE__,   \
                                             __TEMPSENSOR_TYP_CALX_V__,                       \
                                             __TEMPSENSOR_CALX_TEMP__,                        \
                                             __VREFANALOG_VOLTAGE__,                          \
                                             __TEMPSENSOR_ADC_DATA__,                         \
                                             __ADC_RESOLUTION__)                              \
((( ((int32_t)((((__TEMPSENSOR_ADC_DATA__) * (__VREFANALOG_VOLTAGE__))                        \
                / __LL_ADC_DIGITAL_SCALE(__ADC_INSTANCE__, __ADC_RESOLUTION__))               \
               * 1000UL)                                                                      \
     -                                                                                       \
     (int32_t)(((__TEMPSENSOR_TYP_CALX_V__))                                                  \
               * 1000UL)                                                                      \
    )                                                                                         \
  ) / (int32_t)(__TEMPSENSOR_TYP_AVGSLOPE__)                                                  \
 ) + (int32_t)(__TEMPSENSOR_CALX_TEMP__)                                                      \
)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Functions ADC Exported Functions
  * @{
  */

/** @defgroup ADC_LL_EF_DMA_Management ADC DMA management
  * @{
  */
#if defined(ADC_MULTIMODE_SUPPORT)
/**
  * @brief  Function to help to configure DMA transfer from ADC: retrieve the
  *         ADC register address from ADC instance and a list of ADC registers
  *         intended to be used (most commonly) with DMA transfer.
  * @note   These ADC registers are data registers:
  *         when ADC conversion data is available in ADC data registers,
  *         ADC generates a DMA transfer request.
  * @note   This macro is intended to be used with LL DMA driver, refer to
  *         function "LL_DMA_ConfigAddresses()".
  *         Example:
  *           LL_DMA_ConfigAddresses(DMA1,
  *                                  LL_DMA_CHANNEL_1,
  *                                  LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),
  *                                  (uint32_t)&< array or variable >,
  *                                  LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
  * @note   For devices with several ADC: in multimode, some devices
  *         use a different data register outside of ADC instance scope
  *         (common data register). This macro manages this register difference,
  *         only ADC instance has to be set as parameter.
  * @rmtoll DR       RDATA          LL_ADC_DMA_GetRegAddr
  *         CDR      RDATA_MST      LL_ADC_DMA_GetRegAddr
  *         CDR      RDATA_SLV      LL_ADC_DMA_GetRegAddr
  * @param  ADCx ADC instance
  * @param  RegisterValue This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DMA_REG_REGULAR_DATA
  *         @arg @ref LL_ADC_DMA_REG_REGULAR_DATA_MULTI (1)
  *
  *         (1) Available on devices with several ADC instances.
  * @retval ADC register address
  */
__STATIC_INLINE uint32_t LL_ADC_DMA_GetRegAddr(ADC_TypeDef *ADCx, uint32_t RegisterValue)
{
  uint32_t data_reg_addr;

  if (RegisterValue == LL_ADC_DMA_REG_REGULAR_DATA)
  {
    /* Retrieve address of register DR */
    data_reg_addr = (uint32_t) &(ADCx->DR);
  }
  else /* (RegisterValue == LL_ADC_DMA_REG_REGULAR_DATA_MULTI) */
  {
    /* Retrieve address of register CDR */
    data_reg_addr = (uint32_t) &((__LL_ADC_COMMON_INSTANCE(ADCx))->CDR);
  }

  return data_reg_addr;
}
#else
/**
  * @brief  Function to help to configure DMA transfer from ADC: retrieve the
  *         ADC register address from ADC instance and a list of ADC registers
  *         intended to be used (most commonly) with DMA transfer.
  * @note   These ADC registers are data registers:
  *         when ADC conversion data is available in ADC data registers,
  *         ADC generates a DMA transfer request.
  * @note   This macro is intended to be used with LL DMA driver, refer to
  *         function "LL_DMA_ConfigAddresses()".
  *         Example:
  *           LL_DMA_ConfigAddresses(DMA1,
  *                                  LL_DMA_CHANNEL_1,
  *                                  LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),
  *                                  (uint32_t)&< array or variable >,
  *                                  LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
  * @note   For devices with several ADC: in multimode, some devices
  *         use a different data register outside of ADC instance scope
  *         (common data register). This macro manages this register difference,
  *         only ADC instance has to be set as parameter.
  * @rmtoll DR       RDATA          LL_ADC_DMA_GetRegAddr
  * @param  ADCx ADC instance
  * @param  RegisterValue This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DMA_REG_REGULAR_DATA
  * @retval ADC register address
  */
__STATIC_INLINE uint32_t LL_ADC_DMA_GetRegAddr(ADC_TypeDef *ADCx, uint32_t RegisterValue)
{
  /* Prevent unused argument(s) compilation warning */
  (void)(RegisterValue);

  /* Retrieve address of register DR */
  return (uint32_t) &(ADCx->DR);
}
#endif /* ADC_MULTIMODE_SUPPORT */

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Common Configuration of ADC hierarchical scope:
  *           common to several ADC instances
  * @{
  */

/**
  * @brief  Set parameter common to several ADC: Clock source and prescaler.
  * @note   On this STM32 series, if ADC group injected is used, some
  *         clock ratio constraints between ADC clock and AHB clock
  *         must be respected.
  *         Refer to reference manual.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  *         This check can be done with function @ref LL_ADC_IsEnabled() for each
  *         ADC instance or by using helper macro helper macro
  *         @ref __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE().
  * @rmtoll CCR      CKMODE         LL_ADC_SetCommonClock
  *         CCR      PRESC          LL_ADC_SetCommonClock
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  CommonClock This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV1
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV2
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV4
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV6
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV8
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV10
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV12
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV16
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV32
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV64
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV128
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV256
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCommonClock(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t CommonClock)
{
  MODIFY_REG(ADCxy_COMMON->CCR, ADC_CCR_PRESC, CommonClock);
}

/**
  * @brief  Get parameter common to several ADC: Clock source and prescaler.
  * @rmtoll CCR      CKMODE         LL_ADC_GetCommonClock
  *         CCR      PRESC          LL_ADC_GetCommonClock
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV1
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV2
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV4
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV6
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV8
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV10
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV12
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV16
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV32
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV64
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV128
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV256
  */
__STATIC_INLINE uint32_t LL_ADC_GetCommonClock(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(READ_BIT(ADCxy_COMMON->CCR, ADC_CCR_PRESC));
}

/**
  * @brief  Set parameter common to several ADC: measurement path to
  *         internal channels (VrefInt, temperature sensor, ...).
  *         Add paths to the current configuration.
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_PATH_INTERNAL_VREFINT |
  *                   LL_ADC_PATH_INTERNAL_TEMPSENSOR)
  * @note   Stabilization time of measurement path to internal channel:
  *         After enabling internal paths, before starting ADC conversion,
  *         a delay is required for internal voltage reference and
  *         temperature sensor stabilization time.
  *         Refer to device datasheet.
  *         Refer to literal @ref LL_ADC_DELAY_VREFINT_STAB_US.
  *         Refer to literals @ref LL_ADC_DELAY_TEMPSENSOR_STAB_US,
  * @note   ADC internal channel sampling time constraint:
  *         For ADC conversion of internal channels,
  *         a sampling time minimum value is required.
  *         Refer to device datasheet.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  *         This check can be done with function @ref LL_ADC_IsEnabled() for each
  *         ADC instance or by using helper macro helper macro
  *         @ref __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE().
  * @rmtoll CCR      VREFEN         LL_ADC_SetCommonPathInternalChAdd
  *         CCR      VSENSESEL      LL_ADC_SetCommonPathInternalChAdd
  *         CCR      VBATEN         LL_ADC_SetCommonPathInternalChAdd
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  PathInternal This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VREFINT
  *         @arg @ref LL_ADC_PATH_INTERNAL_TEMPSENSOR
  *         @arg @ref LL_ADC_PATH_INTERNAL_VBAT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCommonPathInternalChAdd(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t PathInternal)
{
  SET_BIT(ADCxy_COMMON->CCR, PathInternal);
}

/**
  * @brief  Set parameter common to several ADC: measurement path to
  *         internal channels (VrefInt, temperature sensor, ...).
  *         Remove paths to the current configuration.
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_PATH_INTERNAL_VREFINT |
  *                   LL_ADC_PATH_INTERNAL_TEMPSENSOR)
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  *         This check can be done with function @ref LL_ADC_IsEnabled() for each
  *         ADC instance or by using helper macro helper macro
  *         @ref __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE().
  * @rmtoll CCR      VREFEN         LL_ADC_SetCommonPathInternalChRem
  *         CCR      VSENSESEL      LL_ADC_SetCommonPathInternalChRem
  *         CCR      VBATEN         LL_ADC_SetCommonPathInternalChRem
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  PathInternal This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VREFINT
  *         @arg @ref LL_ADC_PATH_INTERNAL_TEMPSENSOR
  *         @arg @ref LL_ADC_PATH_INTERNAL_VBAT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCommonPathInternalChRem(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t PathInternal)
{
  CLEAR_BIT(ADCxy_COMMON->CCR, PathInternal);
}

/**
  * @brief  Set parameter common to several ADC: measurement path to internal
  *         channels (VrefInt, temperature sensor, ...).
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_PATH_INTERNAL_VREFINT |
  *                   LL_ADC_PATH_INTERNAL_TEMPSENSOR)
  * @note   Stabilization time of measurement path to internal channel:
  *         After enabling internal paths, before starting ADC conversion,
  *         a delay is required for internal voltage reference and
  *         temperature sensor stabilization time.
  *         Refer to device datasheet.
  *         Refer to literal @ref LL_ADC_DELAY_VREFINT_STAB_US.
  *         Refer to literal @ref LL_ADC_DELAY_TEMPSENSOR_STAB_US.
  * @note   ADC internal channel sampling time constraint:
  *         For ADC conversion of internal channels,
  *         a sampling time minimum value is required.
  *         Refer to device datasheet.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  *         This check can be done with function @ref LL_ADC_IsEnabled() for each
  *         ADC instance or by using helper macro helper macro
  *         @ref __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE().
  * @rmtoll CCR      VREFEN         LL_ADC_SetCommonPathInternalCh
  *         CCR      VSENSESEL      LL_ADC_SetCommonPathInternalCh
  *         CCR      VBATEN         LL_ADC_SetCommonPathInternalCh
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  PathInternal This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VREFINT
  *         @arg @ref LL_ADC_PATH_INTERNAL_TEMPSENSOR
  *         @arg @ref LL_ADC_PATH_INTERNAL_VBAT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCommonPathInternalCh(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t PathInternal)
{
  MODIFY_REG(ADCxy_COMMON->CCR, ADC_CCR_VREFEN | ADC_CCR_VSENSEEN | ADC_CCR_VBATEN, PathInternal);
}

/**
  * @brief  Get parameter common to several ADC: measurement path to internal
  *         channels (VrefInt, temperature sensor, ...).
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_PATH_INTERNAL_VREFINT |
  *                   LL_ADC_PATH_INTERNAL_TEMPSENSOR)
  * @rmtoll CCR      VREFEN         LL_ADC_GetCommonPathInternalCh
  *         CCR      VSENSESEL      LL_ADC_GetCommonPathInternalCh
  *         CCR      VBATEN         LL_ADC_GetCommonPathInternalCh
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VREFINT
  *         @arg @ref LL_ADC_PATH_INTERNAL_TEMPSENSOR
  *         @arg @ref LL_ADC_PATH_INTERNAL_VBAT
  */
__STATIC_INLINE uint32_t LL_ADC_GetCommonPathInternalCh(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(READ_BIT(ADCxy_COMMON->CCR, ADC_CCR_VREFEN | ADC_CCR_VSENSEEN | ADC_CCR_VBATEN));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Instance Configuration of ADC hierarchical scope: ADC instance
  * @{
  */

/**
  * @brief  Set ADC calibration factor in the mode single-ended
  *         or differential (for devices with differential mode available).
  * @note   This function is intended to set calibration parameters
  *         without having to perform a new calibration using
  *         @ref LL_ADC_StartCalibration().
  * @note   For devices with differential mode available:
  *         Calibration of offset is specific to each of
  *         single-ended and differential modes
  *         (calibration factor must be specified for each of these
  *         differential modes, if used afterwards and if the application
  *         requires their calibration).
  *         Calibration of linearity is common to both
  *         single-ended and differential modes
  *         (calibration factor can be specified only once).
  * @note   In case of setting calibration factors of both modes single ended
  *         and differential (parameter LL_ADC_BOTH_SINGLE_DIFF_ENDED):
  *         both calibration factors must be concatenated.
  *         To perform this processing, use helper macro
  *         @ref __LL_ADC_CALIB_FACTOR_SINGLE_DIFF().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled, without calibration on going, without conversion
  *         on going on group regular.
  * @param  ADCx ADC instance
  * @param  SingleDiff This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SINGLE_ENDED
  *         @arg @ref LL_ADC_DIFFERENTIAL_ENDED
  *         @arg @ref LL_ADC_BOTH_SINGLE_DIFF_ENDED
  * @param  CalibrationFactor Value between Min_Data=0x0000 and Max_Data=0xFFFF
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibrationOffsetFactor(ADC_TypeDef *ADCx, uint32_t SingleDiff,
                                                       uint32_t CalibrationFactor)
{
  if (ADCx == ADC1)
  {
    CLEAR_BIT(ADCx->CALFACT, ADC_CALFACT_LATCH_COEF | ADC_CALFACT_CAPTURE_COEF);
    MODIFY_REG(ADCx->CR, ADC_CR_ADCALLIN, (0UL << ADC_CR_CALINDEX0_Pos));  /* CalibIndex == 0*/
    MODIFY_REG(ADCx->CALFACT2,
               SingleDiff & ADC_SINGLEDIFF_CALIB_FACTOR_MASK,
               CalibrationFactor << (((SingleDiff & ADC_SINGLEDIFF_CALIB_F_BIT_D_MASK)    \
                                      >> ADC_SINGLEDIFF_CALIB_F_BIT_D_SHIFT4)             \
                                     & ~(SingleDiff & ADC_CALFACT2_CALFACT_S)));
    SET_BIT(ADCx->CALFACT, ADC_CALFACT_LATCH_COEF);
    CLEAR_BIT(ADCx->CALFACT, ADC_CALFACT_CAPTURE_COEF);
  }
  else
  {
    MODIFY_REG(ADCx->CALFACT,  ADC4_CALFACT_CALFACT, CalibrationFactor);
  }
}

/**
  * @brief  Get ADC calibration factor in the mode single-ended
  *         or differential (for devices with differential mode available).
  * @note   Calibration factors are set by hardware after performing
  *         a calibration run using function @ref LL_ADC_StartCalibration().
  * @note   For devices with differential mode available:
  *         Calibration of offset is specific to each of
  *         single-ended and differential modes
  *         Calibration of linearity is common to both
  *         single-ended and differential modes
  * @param  ADCx ADC instance
  * @param  SingleDiff This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SINGLE_ENDED
  *         @arg @ref LL_ADC_DIFFERENTIAL_ENDED
  * @retval Value between Min_Data=0x0000 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibrationOffsetFactor(ADC_TypeDef *ADCx, uint32_t SingleDiff)
{
  /* Retrieve bits with position in register depending on parameter           */
  /* "SingleDiff".                                                            */
  /* Parameter used with mask "ADC_SINGLEDIFF_CALIB_FACTOR_MASK" because      */
  /* containing other bits reserved for other purpose.                        */
  if (ADCx == ADC1)
  {
    uint32_t temp_CalibOffset;
    MODIFY_REG(ADCx->CALFACT, ADC_CALFACT_LATCH_COEF, ADC_CALFACT_CAPTURE_COEF);
    MODIFY_REG(ADCx->CR, ADC_CR_ADCALLIN, (0UL << ADC_CR_CALINDEX0_Pos));  /* CalibIndex == 0*/
    temp_CalibOffset = (READ_BIT(ADCx->CALFACT2, (SingleDiff & ADC_SINGLEDIFF_CALIB_FACTOR_MASK)) \
                        >> ((SingleDiff & ADC_SINGLEDIFF_CALIB_F_BIT_D_MASK) >> ADC_SINGLEDIFF_CALIB_F_BIT_D_SHIFT4));
    CLEAR_BIT(ADCx->CALFACT, ADC_CALFACT_CAPTURE_COEF);
    return temp_CalibOffset;
  }
  else
  {
    return (uint32_t)(READ_BIT(ADCx->CALFACT, ADC4_CALFACT_CALFACT));
  }
}

/**
  * @brief  Set ADC Linear calibration factor in the mode single-ended.
  * @note   This function is intended to set linear calibration parameters
  *         without having to perform a new calibration using
  *         @ref LL_ADC_StartCalibration().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled, without calibration on going, without conversion
  *         on going on group regular.
  * @rmtoll CALFACT2  LINCALFACT      LL_ADC_SetCalibrationLinearFactor
  *         CALFACT2  LINCALFACT      LL_ADC_SetCalibrationLinearFactor
  * @param  ADCx ADC instance
  * @param  LinearityWord This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX1
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX2
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX3
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX4
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX5
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX6
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX7
  * @param  CalibrationFactor Value between Min_Data=0x00 and Max_Data=0x3FFFFFFF
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibrationLinearFactor(ADC_TypeDef *ADCx, uint32_t LinearityWord,
                                                       uint32_t CalibrationFactor)
{
  /* Before using this!
     Make sure ADEN = 1, ADSTART = 0 and JADSTART = 0 (ADC enabled and no conversion is ongoing).
     --> This should be checked by application.
  */
  CLEAR_BIT(ADCx->CALFACT, ADC_CALFACT_LATCH_COEF | ADC_CALFACT_CAPTURE_COEF);
  MODIFY_REG(ADCx->CR, (ADC_CR_CALINDEX3 | ADC_CR_CALINDEX2 | ADC_CR_CALINDEX1 | ADC_CR_CALINDEX0),
             LinearityWord);   /* LinearityWord == CalibIndex (1 to 8 for linearity reading)*/
  MODIFY_REG(ADCx->CALFACT2, ADC_CALFACT2_CALFACT, CalibrationFactor);
  SET_BIT(ADCx->CALFACT, ADC_CALFACT_LATCH_COEF);
  CLEAR_BIT(ADCx->CALFACT, ADC_CALFACT_CAPTURE_COEF);
}

/**
  * @brief  Get ADC Linear calibration factor in the mode single-ended.
  * @note   Calibration factors are set by hardware after performing
  *         a calibration run using function @ref LL_ADC_StartCalibration().
  * @rmtoll CALFACT2  LINCALFACT      LL_ADC_GetCalibrationLinearFactor
  *         CALFACT2  LINCALFACT      LL_ADC_GetCalibrationLinearFactor
  * @param  ADCx ADC instance
  * @param  LinearityWord This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX1
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX2
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX3
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX4
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX5
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX6
  *         @arg @ref LL_ADC_CALIB_LINEARITY_INDEX7
  * @retval Value between Min_Data=0x00 and Max_Data=0x3FFFFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibrationLinearFactor(ADC_TypeDef *ADCx, uint32_t LinearityWord)
{
  uint32_t temp_calib_linearity;
  SET_BIT(ADCx->CALFACT, ADC_CALFACT_CAPTURE_COEF);
  CLEAR_BIT(ADCx->CALFACT, ADC_CALFACT_LATCH_COEF);
  MODIFY_REG(ADCx->CR, (ADC_CR_CALINDEX3 | ADC_CR_CALINDEX2 | ADC_CR_CALINDEX1 | ADC_CR_CALINDEX0),
             LinearityWord);   /* LinearityWord == CalibIndex (1 to 8 for linearity reading)*/
  temp_calib_linearity = (uint32_t)(READ_BIT(ADCx->CALFACT2, ADC_CALFACT2_CALFACT_Msk));
  CLEAR_BIT(ADCx->CALFACT, ADC_CALFACT_CAPTURE_COEF);
  return temp_calib_linearity;
}
/**
  * @brief  Set ADC resolution.
  *         Refer to reference manual for alignments formats
  *         dependencies to ADC resolutions.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @note   if ADC4 instance __LL_ADC_RESOLUTION_ADC1_TO_ADC4() is used to
  *         convert ADC1 to ADC4 resolution
  * @rmtoll CFGR     RES            LL_ADC_SetResolution
  * @param  ADCx ADC instance
  * @param  Resolution This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_14B (1)
  *         @arg @ref LL_ADC_RESOLUTION_12B (3)
  *         @arg @ref LL_ADC_RESOLUTION_10B (3)
  *         @arg @ref LL_ADC_RESOLUTION_8B  (3)
  *         @arg @ref LL_ADC_RESOLUTION_6B  (2)
  *               (1): Specific to ADC1 instance
  *               (2): Specific to ADC4 instance
  *               (3): Common to all instances but different bits positions
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetResolution(ADC_TypeDef *ADCx, uint32_t Resolution)
{
  if (ADCx == ADC1)
  {
    MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_RES, Resolution);
  }
  else /* ADCx == ADC4 */
  {
    MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_RES, __LL_ADC_RESOLUTION_ADC1_TO_ADC4(Resolution));
  }
}

/**
  * @brief  Get ADC resolution.
  *         Refer to reference manual for alignments formats
  *         dependencies to ADC resolutions.
  * @rmtoll CFGR     RES            LL_ADC_GetResolution
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_14B (1)
  *         @arg @ref LL_ADC_RESOLUTION_12B (3)
  *         @arg @ref LL_ADC_RESOLUTION_10B (3)
  *         @arg @ref LL_ADC_RESOLUTION_8B  (3)
  *         @arg @ref LL_ADC_RESOLUTION_6B  (2)
  *               (1): Specific to ADC1 instance
  *               (2): Specific to ADC4 instance
  *               (3): Common to all instances but different bits positions
  */
__STATIC_INLINE uint32_t LL_ADC_GetResolution(ADC_TypeDef *ADCx)
{
  if (ADCx == ADC1)
  {
    return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_RES));
  }
  else /* ADCx == ADC4 */
  {
    uint32_t temp_Resolution;
    temp_Resolution = (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_RES));
    if (temp_Resolution == (ADC_CFGR1_RES_1 | ADC_CFGR1_RES_0))
    {
      return LL_ADC_RESOLUTION_6B;
    }
    else
    {
      return __LL_ADC_RESOLUTION_ADC4_TO_ADC1(temp_Resolution);
    }
  }
}

/**
  * @brief  Set ADC conversion data alignment.
  * @note   Refer to reference manual for alignments formats
  *         dependencies to ADC resolutions.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR1    ALIGN          LL_ADC_SetDataAlignment
  * @param  ADCx ADC instance
  * @param  DataAlignment This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DATA_ALIGN_RIGHT
  *         @arg @ref LL_ADC_DATA_ALIGN_LEFT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetDataAlignment(ADC_TypeDef *ADCx, uint32_t DataAlignment)
{
  MODIFY_REG(ADCx->CFGR1, ADC4_CFGR1_ALIGN, DataAlignment);
}

/**
  * @brief  Get ADC conversion data alignment.
  * @note   Refer to reference manual for alignments formats
  *         dependencies to ADC resolutions.
  * @rmtoll CFGR1    ALIGN          LL_ADC_GetDataAlignment
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DATA_ALIGN_RIGHT
  *         @arg @ref LL_ADC_DATA_ALIGN_LEFT
  */
__STATIC_INLINE uint32_t LL_ADC_GetDataAlignment(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC4_CFGR1_ALIGN));
}

/**
  * @brief  Set ADC low power mode.
  * @note   Description of ADC low power modes:
  *         - ADC low power mode "auto wait": Dynamic low power mode,
  *           ADC conversions occurrences are limited to the minimum necessary
  *           in order to reduce power consumption.
  *           New ADC conversion starts only when the previous
  *           unitary conversion data (for ADC group regular)
  *           or previous sequence conversions data (for ADC group injected)
  *           has been retrieved by user software.
  *           In the meantime, ADC remains idle: does not performs any
  *           other conversion.
  *           This mode allows to automatically adapt the ADC conversions
  *           triggers to the speed of the software that reads the data.
  *           Moreover, this avoids risk of overrun for low frequency
  *           applications.
  *           How to use this low power mode:
  *           - It is not recommended to use with interruption or DMA
  *             since these modes have to clear immediately the EOC flag
  *             (by CPU to free the IRQ pending event or by DMA).
  *             Auto wait will work but fort a very short time, discarding
  *             its intended benefit (except specific case of high load of CPU
  *             or DMA transfers which can justify usage of auto wait).
  *           - Do use with polling: 1. Start conversion,
  *             2. Later on, when conversion data is needed: poll for end of
  *             conversion  to ensure that conversion is completed and
  *             retrieve ADC conversion data. This will trig another
  *             ADC conversion start.
  *         - ADC low power mode "auto power-off" (feature available on
  *           this device if parameter LL_ADC_LP_AUTOPOWEROFF is available):
  *           the ADC automatically powers-off after a conversion and
  *           automatically wakes up when a new conversion is triggered
  *           (with startup time between trigger and start of sampling).
  *           This feature can be combined with low power mode "auto wait".
  * @note   With ADC low power mode "auto wait", the ADC conversion data read
  *         is corresponding to previous ADC conversion start, independently
  *         of delay during which ADC was idle.
  *         Therefore, the ADC conversion data may be outdated: does not
  *         correspond to the current voltage level on the selected
  *         ADC channel.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     AUTDLY         LL_ADC_SetLowPowerMode
  * @param  ADCx ADC instance
  * @param  LowPowerMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_LP_MODE_NONE
  *         @arg @ref LL_ADC_LP_AUTOWAIT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetLowPowerMode(ADC_TypeDef *ADCx, uint32_t LowPowerMode)
{
  if (ADCx != ADC4) /* ADC1 or ADC2 */
  {
    MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_AUTDLY, LowPowerMode);
  }
  else
  {
    MODIFY_REG(ADCx->CFGR1, ADC4_CFGR1_WAIT, LowPowerMode);
    MODIFY_REG(ADCx->PW, ADC4_PW_AUTOFF, LowPowerMode);
  }
}

/**
  * @brief  Get ADC low power mode:
  * @note   Description of ADC low power modes:
  *         - ADC low power mode "auto wait": Dynamic low power mode,
  *           ADC conversions occurrences are limited to the minimum necessary
  *           in order to reduce power consumption.
  *           New ADC conversion starts only when the previous
  *           unitary conversion data (for ADC group regular)
  *           or previous sequence conversions data (for ADC group injected)
  *           has been retrieved by user software.
  *           In the meantime, ADC remains idle: does not performs any
  *           other conversion.
  *           This mode allows to automatically adapt the ADC conversions
  *           triggers to the speed of the software that reads the data.
  *           Moreover, this avoids risk of overrun for low frequency
  *           applications.
  *           How to use this low power mode:
  *           - It is not recommended to use with interruption or DMA
  *             since these modes have to clear immediately the EOC flag
  *             (by CPU to free the IRQ pending event or by DMA).
  *             Auto wait will work but fort a very short time, discarding
  *             its intended benefit (except specific case of high load of CPU
  *             or DMA transfers which can justify usage of auto wait).
  *           - Do use with polling: 1. Start conversion,
  *             2. Later on, when conversion data is needed: poll for end of
  *             conversion  to ensure that conversion is completed and
  *             retrieve ADC conversion data. This will trig another
  *             ADC conversion start.
  *         - ADC low power mode "auto power-off" (feature available on
  *           this device if parameter LL_ADC_LP_AUTOPOWEROFF is available):
  *           the ADC automatically powers-off after a conversion and
  *           automatically wakes up when a new conversion is triggered
  *           (with startup time between trigger and start of sampling).
  *           This feature can be combined with low power mode "auto wait".
  * @note   With ADC low power mode "auto wait", the ADC conversion data read
  *         is corresponding to previous ADC conversion start, independently
  *         of delay during which ADC was idle.
  *         Therefore, the ADC conversion data may be outdated: does not
  *         correspond to the current voltage level on the selected
  *         ADC channel.
  * @rmtoll CFGR     AUTDLY         LL_ADC_GetLowPowerMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_LP_MODE_NONE
  *         @arg @ref LL_ADC_LP_AUTOWAIT
  */
__STATIC_INLINE uint32_t LL_ADC_GetLowPowerMode(ADC_TypeDef *ADCx)
{
  if (ADCx != ADC4) /* ADC1 or ADC2 */
  {
    return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_AUTDLY));
  }
  else
  {
    return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC4_CFGR1_WAIT));
  }

}

/**
  * @brief  Set ADC selected offset number 1, 2, 3 or 4.
  * @note   This function set the 2 items of offset configuration:
  *         - ADC channel to which the offset programmed will be applied
  *           (independently of channel mapped on ADC group regular
  *           or group injected)
  *         - Offset level (offset to be subtracted from the raw
  *           converted data).
  * @note   Caution: Offset format is dependent to ADC resolution:
  *         offset has to be left-aligned on bit 11, the LSB (right bits)
  *         are set to 0.
  * @note   This function enables the offset, by default. It can be forced
  *         to disable state using function LL_ADC_SetOffsetState().
  * @note   If a channel is mapped on several offsets numbers, only the offset
  *         with the lowest value is considered for the subtraction.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @note   On STM32U5, some fast channels are available: fast analog inputs
  *         coming from GPIO pads (ADC_IN0..5).
  * @rmtoll OFR1     OFFSET1_CH     LL_ADC_SetOffset
  *         OFR1     OFFSET1        LL_ADC_SetOffset
  *         OFR1     OFFSET1_EN     LL_ADC_SetOffset
  *         OFR2     OFFSET2_CH     LL_ADC_SetOffset
  *         OFR2     OFFSET2        LL_ADC_SetOffset
  *         OFR2     OFFSET2_EN     LL_ADC_SetOffset
  *         OFR3     OFFSET3_CH     LL_ADC_SetOffset
  *         OFR3     OFFSET3        LL_ADC_SetOffset
  *         OFR3     OFFSET3_EN     LL_ADC_SetOffset
  *         OFR4     OFFSET4_CH     LL_ADC_SetOffset
  *         OFR4     OFFSET4        LL_ADC_SetOffset
  *         OFR4     OFFSET4_EN     LL_ADC_SetOffset
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4  (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4        (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  * @param  OffsetLevel Value between Min_Data=0x000 and Max_Data=0x1FFFFFF
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOffset(ADC_TypeDef *ADCx, uint32_t Offsety, uint32_t Channel, uint32_t OffsetLevel)
{
  __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->OFR1, Offsety);

  MODIFY_REG(*preg,
             ADC_OFR1_OFFSET1_CH | ADC_OFR1_OFFSET1,
             ((Channel & ADC_CHANNEL_ID_NUMBER_MASK) << 1UL) | OffsetLevel);
}

/**
  * @brief  Get for the ADC selected offset number 1, 2, 3 or 4:
  *         Channel to which the offset programmed will be applied
  *         (independently of channel mapped on ADC group regular
  *         or group injected)
  * @note   Usage of the returned channel number:
  *         - To reinject this channel into another function LL_ADC_xxx:
  *           the returned channel number is only partly formatted on definition
  *           of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *           with parts of literals LL_ADC_CHANNEL_x or using
  *           helper macro @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  *           Then the selected literal LL_ADC_CHANNEL_x can be used
  *           as parameter for another function.
  *         - To get the channel number in decimal format:
  *           process the returned value with the helper macro
  *           @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  * @note   On STM32U5, some fast channels are available: fast analog inputs
  *         coming from GPIO pads (ADC_IN0..5).
  * @rmtoll OFR1     OFFSET1_CH     LL_ADC_GetOffsetChannel
  *         OFR2     OFFSET2_CH     LL_ADC_GetOffsetChannel
  *         OFR3     OFFSET3_CH     LL_ADC_GetOffsetChannel
  *         OFR4     OFFSET4_CH     LL_ADC_GetOffsetChannel
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4  (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4        (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  *         (1, 2) For ADC channel read back from ADC register,
  *                comparison with internal channel parameter to be done
  *                using helper macro @ref __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  */
__STATIC_INLINE uint32_t LL_ADC_GetOffsetChannel(ADC_TypeDef *ADCx, uint32_t Offsety)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->OFR1, Offsety);

  return (uint32_t) READ_BIT(*preg, ADC_OFR1_OFFSET1_CH);
}

/**
  * @brief  Get for the ADC selected offset number 1, 2, 3 or 4:
  *         Offset level (offset to be subtracted from the raw
  *         converted data).
  * @note   Caution: Offset format is dependent to ADC resolution:
  *         offset has to be left-aligned on bit 11, the LSB (right bits)
  *         are set to 0.
  * @rmtoll OFR1     OFFSET1        LL_ADC_GetOffsetLevel
  *         OFR2     OFFSET2        LL_ADC_GetOffsetLevel
  *         OFR3     OFFSET3        LL_ADC_GetOffsetLevel
  *         OFR4     OFFSET4        LL_ADC_GetOffsetLevel
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @retval Value between Min_Data=0x000 and Max_Data=0x1FFFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_GetOffsetLevel(ADC_TypeDef *ADCx, uint32_t Offsety)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->OFR1, Offsety);

  return (uint32_t) READ_BIT(*preg, ADC_OFR1_OFFSET1);
}

/**
  * @brief  Set for the ADC selected offset number 1, 2, 3 or 4:
  *         choose offset sign.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll OFR1     OFFSETPOS      LL_ADC_SetOffsetSign
  *         OFR2     OFFSETPOS      LL_ADC_SetOffsetSign
  *         OFR3     OFFSETPOS      LL_ADC_SetOffsetSign
  *         OFR4     OFFSETPOS      LL_ADC_SetOffsetSign
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @param  OffsetSign This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_SIGN_NEGATIVE
  *         @arg @ref LL_ADC_OFFSET_SIGN_POSITIVE
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOffsetSign(ADC_TypeDef *ADCx, uint32_t Offsety, uint32_t OffsetSign)
{
  __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->OFR1, Offsety);

  MODIFY_REG(*preg, ADC_OFR1_OFFSETPOS, OffsetSign);
}

/**
  * @brief  Get for the ADC selected offset number 1, 2, 3 or 4:
  *         offset sign if positive or negative.
  * @rmtoll OFR1     OFFSETPOS      LL_ADC_GetOffsetSign
  *         OFR2     OFFSETPOS      LL_ADC_GetOffsetSign
  *         OFR3     OFFSETPOS      LL_ADC_GetOffsetSign
  *         OFR4     OFFSETPOS      LL_ADC_GetOffsetSign
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_SIGN_NEGATIVE
  *         @arg @ref LL_ADC_OFFSET_SIGN_POSITIVE
  */
__STATIC_INLINE uint32_t LL_ADC_GetOffsetSign(ADC_TypeDef *ADCx, uint32_t Offsety)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->OFR1, Offsety);

  return (uint32_t) READ_BIT(*preg, ADC_OFR1_OFFSETPOS);
}

/**
  * @brief  Set Signed saturation for the ADC selected offset number 1, 2, 3 or 4:
  *         signed offset saturation if enabled or disabled.
  * @rmtoll OFR1     SSAT          LL_ADC_SetOffsetSignedSaturation
  *         OFR2     SSAT          LL_ADC_SetOffsetSignedSaturation
  *         OFR3     SSAT          LL_ADC_SetOffsetSignedSaturation
  *         OFR4     SSAT          LL_ADC_SetOffsetSignedSaturation
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @param  OffsetSignedSaturation This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_SIGNED_SATURATION_ENABLE
  *         @arg @ref LL_ADC_OFFSET_SIGNED_SATURATION_DISABLE
  * @retval Returned None
  */
__STATIC_INLINE void LL_ADC_SetOffsetSignedSaturation(ADC_TypeDef *ADCx, uint32_t Offsety,
                                                      uint32_t OffsetSignedSaturation)
{
  __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->OFR1, Offsety);
  MODIFY_REG(*preg, ADC_OFR1_SSAT, OffsetSignedSaturation);
}

/**
  * @brief  Get Signed saturation for the ADC selected offset number 1, 2, 3 or 4:
  *         signed offset saturation if enabled or disabled.
  * @rmtoll OFR1     SSAT          LL_ADC_GetOffsetSignedSaturation
  *         OFR2     SSAT          LL_ADC_GetOffsetSignedSaturation
  *         OFR3     SSAT          LL_ADC_GetOffsetSignedSaturation
  *         OFR4     SSAT          LL_ADC_GetOffsetSignedSaturation
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_SIGNED_SATURATION_ENABLE
  *         @arg @ref LL_ADC_OFFSET_SIGNED_SATURATION_DISABLE
  */
__STATIC_INLINE uint32_t LL_ADC_GetOffsetSignedSaturation(ADC_TypeDef *ADCx, uint32_t Offsety)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->OFR1, Offsety);
  return (uint32_t) READ_BIT(*preg, ADC_OFR1_SSAT);
}

/**
  * @brief  Set Unsigned saturation for the ADC selected offset number 1, 2, 3 or 4:
  *         signed offset saturation if enabled or disabled.
  * @rmtoll OFR1     USAT          LL_ADC_SetOffsetUnsignedSaturation
  *         OFR2     USAT          LL_ADC_SetOffsetUnsignedSaturation
  *         OFR3     USAT          LL_ADC_SetOffsetUnsignedSaturation
  *         OFR4     USAT          LL_ADC_SetOffsetUnsignedSaturation
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @param  OffsetUnsignedSaturation This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_UNSIGNED_SATURATION_ENABLE
  *         @arg @ref LL_ADC_OFFSET_UNSIGNED_SATURATION_DISABLE
  * @retval Returned None
  */
__STATIC_INLINE void LL_ADC_SetOffsetUnsignedSaturation(ADC_TypeDef *ADCx, uint32_t Offsety,
                                                        uint32_t OffsetUnsignedSaturation)
{
  __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->OFR1, Offsety);
  MODIFY_REG(*preg, ADC_OFR1_USAT, OffsetUnsignedSaturation);
}

/**
  * @brief  Get Unsigned saturation for the ADC selected offset number 1, 2, 3 or 4:
  *         signed offset saturation if enabled or disabled.
  * @rmtoll OFR1     USAT          LL_ADC_GetOffsetUnsignedSaturation
  *         OFR2     USAT          LL_ADC_GetOffsetUnsignedSaturation
  *         OFR3     USAT          LL_ADC_GetOffsetUnsignedSaturation
  *         OFR4     USAT          LL_ADC_GetOffsetUnsignedSaturation
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_UNSIGNED_SATURATION_ENABLE
  *         @arg @ref LL_ADC_OFFSET_UNSIGNED_SATURATION_DISABLE
  */
__STATIC_INLINE uint32_t LL_ADC_GetOffsetUnsignedSaturation(ADC_TypeDef *ADCx, uint32_t Offsety)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->OFR1, Offsety);
  return (uint32_t) READ_BIT(*preg, ADC_OFR1_USAT);
}

/**
  * @brief  Set ADC gain compensation.
  * @note   This function set the gain compensation coefficient
  *         that is applied to raw converted data using the formula:
  *           DATA = DATA(raw) * (gain compensation coef) / 4096
  * @note   This function enables the gain compensation if given
  *         coefficient is above 0, otherwise it disables it.
  * @note   Gain compensation when enabled is applied to all channels.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll GCOMP    GCOMPCOEFF     LL_ADC_SetGainCompensation
  *         CFGR2    GCOMP          LL_ADC_SetGainCompensation
  * @param  ADCx ADC instance
  * @param  GainCompensation This parameter can be:
  *         0           Gain compensation will be disabled and value set to 0
  *         1 -> 16393  Gain compensation will be enabled with specified value
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetGainCompensation(ADC_TypeDef *ADCx, uint32_t GainCompensation)
{
  MODIFY_REG(ADCx->GCOMP, ADC_GCOMP_GCOMPCOEFF, GainCompensation);
  MODIFY_REG(ADCx->GCOMP, ADC_GCOMP_GCOMP, ((GainCompensation == 0UL) ? 0UL : 1UL) << ADC_GCOMP_GCOMP_Pos);
}

/**
  * @brief  Get the ADC gain compensation value
  * @rmtoll GCOMP    GCOMPCOEFF     LL_ADC_GetGainCompensation
  *         CFGR2    GCOMP          LL_ADC_GetGainCompensation
  * @param  ADCx ADC instance
  * @retval Returned value can be:
  *         0           Gain compensation is disabled
  *         1 -> 16393  Gain compensation is enabled with returned value
  */
__STATIC_INLINE uint32_t LL_ADC_GetGainCompensation(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->GCOMP, ADC_GCOMP_GCOMP) == ADC_GCOMP_GCOMP)   \
          ? READ_BIT(ADCx->GCOMP, ADC_GCOMP_GCOMPCOEFF) : 0UL);
}

/**
  * @}
  */

/**
  * @brief  Set sampling time common to a group of channels.
  * @note   Unit: ADC clock cycles.
  * @note   On this STM32 series, sampling time scope is on ADC instance:
  *         Sampling time common to all channels.
  *         (on some other STM32 families, sampling time is channel wise)
  * @note   In case of internal channel (VrefInt, TempSensor, ...) to be
  *         converted:
  *         sampling time constraints must be respected (sampling time can be
  *         adjusted in function of ADC clock frequency and sampling time
  *         setting).
  *         Refer to device datasheet for timings values (parameters TS_vrefint,
  *         TS_temp, ...).
  * @note   Conversion time is the addition of sampling time and processing time.
  *         On this STM32 series, ADC processing time is:
  *         - 12.5 ADC clock cycles at ADC resolution 12 bits
  *         - 10.5 ADC clock cycles at ADC resolution 10 bits
  *         - 8.5 ADC clock cycles at ADC resolution 8 bits
  *         - 6.5 ADC clock cycles at ADC resolution 6 bits
  * @note   In case of ADC conversion of internal channel (VrefInt,
  *         temperature sensor, ...), a sampling time minimum value
  *         is required.
  *         Refer to device datasheet.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @note   Applicable only on ADC4 instance
  * @rmtoll SMPR     SMP1           LL_ADC_SetSamplingTimeCommonChannels
  * @rmtoll SMPR     SMP2           LL_ADC_SetSamplingTimeCommonChannels
  * @param  ADCx ADC instance
  * @param  SamplingTimeY This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLINGTIME_COMMON_1
  *         @arg @ref LL_ADC_SAMPLINGTIME_COMMON_2
  * @param  SamplingTime This parameter can be one of the following values:
  *         @arg @ref LL_ADC4_SAMPLINGTIME_1CYCLE_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_3CYCLES_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_7CYCLES_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_12CYCLES_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_19CYCLES_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_39CYCLES_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_79CYCLES_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_160CYCLES_5
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetSamplingTimeCommonChannels(ADC_TypeDef *ADCx, uint32_t SamplingTimeY,
                                                          uint32_t SamplingTime)
{
  MODIFY_REG(ADCx->SMPR1,
             ADC4_SMPR_SMP1 << (SamplingTimeY & ADC4_SAMPLING_TIME_SMP_SHIFT_MASK),
             SamplingTime << (SamplingTimeY & ADC4_SAMPLING_TIME_SMP_SHIFT_MASK));
}

/**
  * @brief  Get sampling time common to a group of channels.
  * @note   Unit: ADC clock cycles.
  * @note   On this STM32 series, sampling time scope is on ADC instance:
  *         Sampling time common to all channels.
  *         (on some other STM32 families, sampling time is channel wise)
  * @note   Conversion time is the addition of sampling time and processing time.
  *         Refer to reference manual for ADC processing time of
  *         this STM32 series.
  * @rmtoll SMPR     SMP1           LL_ADC_GetSamplingTimeCommonChannels
  * @rmtoll SMPR     SMP2           LL_ADC_GetSamplingTimeCommonChannels
  * @param  ADCx ADC instance (ADC4 for this device)
  * @param  SamplingTimeY This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLINGTIME_COMMON_1
  *         @arg @ref LL_ADC_SAMPLINGTIME_COMMON_2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC4_SAMPLINGTIME_1CYCLE_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_3CYCLES_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_7CYCLES_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_12CYCLES_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_19CYCLES_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_39CYCLES_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_79CYCLES_5
  *         @arg @ref LL_ADC4_SAMPLINGTIME_160CYCLES_5
  */
__STATIC_INLINE uint32_t LL_ADC_GetSamplingTimeCommonChannels(ADC_TypeDef *ADCx, uint32_t SamplingTimeY)
{
  return (uint32_t)((READ_BIT(ADCx->SMPR1, ADC4_SMPR_SMP1 << (SamplingTimeY & ADC4_SAMPLING_TIME_SMP_SHIFT_MASK)))
                    >> (SamplingTimeY & ADC4_SAMPLING_TIME_SMP_SHIFT_MASK));
}

/** @defgroup ADC_LL_EF_Configuration_ADC_Group_Regular Configuration of ADC hierarchical scope: group regular
  * @{
  */

/**
  * @brief  Set ADC group regular conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         external interrupt line).
  * @note   On this STM32 series, setting trigger source to external trigger
  *         also set trigger polarity to rising edge
  *         (default setting for compatibility with some ADC on other
  *         STM32 families having this setting set by HW default value).
  *         In case of need to modify trigger edge, use
  *         function @ref LL_ADC_REG_SetTriggerEdge().
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     EXTSEL         LL_ADC_REG_SetTriggerSource
  *         CFGR     EXTEN          LL_ADC_REG_SetTriggerSource
  * @param  ADCx ADC instance
  * @param  TriggerSource This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_SOFTWARE
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_CH1
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_CH2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_CH3
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM2_CH2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM3_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM4_CH4
  *         @arg @ref LL_ADC_REG_TRIG_EXT_EXTI_LINE11
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM8_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM8_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM2_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM4_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM6_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM15_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM3_CH4
  *         @arg @ref LL_ADC_REG_TRIG_EXT_LPTIM1_CH1
  *         @arg @ref LL_ADC_REG_TRIG_EXT_LPTIM2_CH1
  *         @arg @ref LL_ADC_REG_TRIG_EXT_LPTIM3_CH1
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetTriggerSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
  if (ADCx == ADC1)
  {
    MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_EXTEN | ADC_CFGR1_EXTSEL, TriggerSource);
  }
  else /* ADCx == ADC4 */
  {
    MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_EXTEN | ADC4_CFGR1_EXTSEL, TriggerSource);
  }
}

/**
  * @brief  Get ADC group regular conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         external interrupt line).
  * @note   To determine whether group regular trigger source is
  *         internal (SW start) or external, without detail
  *         of which peripheral is selected as external trigger,
  *         (equivalent to
  *         "if(LL_ADC_REG_GetTriggerSource(ADC1) == LL_ADC_REG_TRIG_SOFTWARE)")
  *         use function @ref LL_ADC_REG_IsTriggerSourceSWStart.
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @rmtoll CFGR     EXTSEL         LL_ADC_REG_GetTriggerSource
  *         CFGR     EXTEN          LL_ADC_REG_GetTriggerSource
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_SOFTWARE
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_CH1
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_CH2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_CH3
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM2_CH2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM3_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM4_CH4
  *         @arg @ref LL_ADC_REG_TRIG_EXT_EXTI_LINE11
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM8_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM8_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM2_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM4_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM6_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM15_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM3_CH4
  *         @arg @ref LL_ADC_REG_TRIG_EXT_LPTIM1_CH1
  *         @arg @ref LL_ADC_REG_TRIG_EXT_LPTIM2_CH1
  *         @arg @ref LL_ADC_REG_TRIG_EXT_LPTIM3_CH1
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetTriggerSource(ADC_TypeDef *ADCx)
{
  if (ADCx == ADC1)
  {
    __IO uint32_t trigger_source = READ_BIT(ADCx->CFGR1, ADC_CFGR1_EXTSEL | ADC_CFGR1_EXTEN);

    /* Value for shift of {0; 4; 8; 12} depending on value of bitfield          */
    /* corresponding to ADC_CFGR_EXTEN {0; 1; 2; 3}.                            */
    uint32_t shift_exten = ((trigger_source & ADC_CFGR1_EXTEN) >> (ADC_REG_TRIG_EXTEN_BITOFFSET_POS - 2UL));

    /* Set bitfield corresponding to ADC_CFGR_EXTEN and ADC_CFGR_EXTSEL         */
    /* to match with triggers literals definition.                              */
    return ((trigger_source
             & (ADC_REG_TRIG_SOURCE_MASK >> shift_exten) & ADC_CFGR1_EXTSEL)
            | ((ADC_REG_TRIG_EDGE_MASK >> shift_exten) & ADC_CFGR1_EXTEN)
           );
  }
  else /* ADCx == ADC4 */
  {
    __IO uint32_t trigger_source = READ_BIT(ADCx->CFGR1, ADC4_CFGR1_EXTSEL | ADC_CFGR1_EXTEN);

    /* Value for shift of {0; 4; 8; 12} depending on value of bitfield          */
    /* corresponding to ADC_CFGR_EXTEN {0; 1; 2; 3}.                            */
    uint32_t shift_exten = ((trigger_source & ADC_CFGR1_EXTEN) >> (ADC_REG_TRIG_EXTEN_BITOFFSET_POS - 2UL));

    /* Set bitfield corresponding to ADC_CFGR_EXTEN and ADC_CFGR_EXTSEL         */
    /* to match with triggers literals definition.                              */
    return ((trigger_source
             & (ADC_REG_TRIG_SOURCE_MASK >> shift_exten) & ADC4_CFGR1_EXTSEL)
            | ((ADC_REG_TRIG_EDGE_MASK >> shift_exten) & ADC_CFGR1_EXTEN)
           );
  }
}

/**
  * @brief  Get ADC group regular conversion trigger source internal (SW start)
  *         or external.
  * @note   In case of group regular trigger source set to external trigger,
  *         to determine which peripheral is selected as external trigger,
  *         use function @ref LL_ADC_REG_GetTriggerSource().
  * @rmtoll CFGR     EXTEN          LL_ADC_REG_IsTriggerSourceSWStart
  * @param  ADCx ADC instance
  * @retval Value "0" if trigger source external trigger
  *         Value "1" if trigger source SW start.
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsTriggerSourceSWStart(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CFGR1, ADC_CFGR1_EXTEN) == (LL_ADC_REG_TRIG_SOFTWARE & ADC_CFGR1_EXTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set ADC group regular conversion trigger polarity.
  * @note   Applicable only for trigger source set to external trigger.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     EXTEN          LL_ADC_REG_SetTriggerEdge
  * @param  ADCx ADC instance
  * @param  ExternalTriggerEdge This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_REG_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_REG_TRIG_EXT_RISINGFALLING
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetTriggerEdge(ADC_TypeDef *ADCx, uint32_t ExternalTriggerEdge)
{
  MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_EXTEN, ExternalTriggerEdge);
}

/**
  * @brief  Get ADC group regular conversion trigger polarity.
  * @note   Applicable only for trigger source set to external trigger.
  * @rmtoll CFGR     EXTEN          LL_ADC_REG_GetTriggerEdge
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_REG_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_REG_TRIG_EXT_RISINGFALLING
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetTriggerEdge(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_EXTEN));
}

/**
  * @brief  Set ADC trigger frequency mode.
  * @note   ADC trigger frequency mode must be set to low frequency when
  *         a duration is exceeded before ADC conversion start trigger event
  *         (between ADC enable and ADC conversion start trigger event
  *         or between two ADC conversion start trigger event).
  *         Duration value: Refer to device datasheet, parameter "tIdle".
  * @note   When ADC trigger frequency mode is set to low frequency,
  *         some rearm cycles are inserted before performing ADC conversion
  *         start, inducing a delay of 2 ADC clock cycles.
  * @note   Usage of ADC trigger frequency mode with ADC low power mode:
  *         - Low power mode auto wait: Only the first ADC conversion
  *           start trigger inserts the rearm delay.
  *         - Low power mode auto power-off: ADC trigger frequency mode
  *           is discarded.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR2    LFTRIG         LL_ADC_SetTriggerFrequencyMode
  * @param  ADCx ADC instance
  * @param  TriggerFrequencyMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_TRIGGER_FREQ_HIGH
  *         @arg @ref LL_ADC_TRIGGER_FREQ_LOW
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetTriggerFrequencyMode(ADC_TypeDef *ADCx, uint32_t TriggerFrequencyMode)
{
  if (ADCx == ADC1)
  {
    MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_LFTRIG, (TriggerFrequencyMode >> 2U));
  }
  else /* ADCx == ADC4 */
  {
    MODIFY_REG(ADCx->CFGR2, ADC4_CFGR2_LFTRIG, TriggerFrequencyMode);
  }
}

/**
  * @brief  Get ADC trigger frequency mode.
  * @rmtoll CFGR2    LFTRIG         LL_ADC_GetTriggerFrequencyMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_TRIGGER_FREQ_HIGH
  *         @arg @ref LL_ADC_TRIGGER_FREQ_LOW
  */
__STATIC_INLINE uint32_t LL_ADC_GetTriggerFrequencyMode(ADC_TypeDef *ADCx)
{
  if (ADCx == ADC1)
  {
    return (uint32_t)((READ_BIT(ADCx->CFGR2, ADC_CFGR2_LFTRIG)) << 2U);
  }
  else /* ADCx == ADC4 */
  {
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC4_CFGR2_LFTRIG));
  }
}

/**
  * @brief  Set ADC sampling mode.
  * @note   This function set the ADC conversion sampling mode
  * @note   This mode applies to regular group only.
  * @note   Set sampling mode is applied to all conversion of regular group.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR2    BULB           LL_ADC_REG_SetSamplingMode
  *         CFGR2    SMPTRIG        LL_ADC_REG_SetSamplingMode
  * @param  ADCx ADC instance
  * @param  SamplingMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_SAMPLING_MODE_NORMAL
  *         @arg @ref LL_ADC_REG_SAMPLING_MODE_BULB
  *         @arg @ref LL_ADC_REG_SAMPLING_MODE_TRIGGER_CONTROLED
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSamplingMode(ADC_TypeDef *ADCx, uint32_t SamplingMode)
{
  MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_BULB | ADC_CFGR2_SMPTRIG, SamplingMode);
}

/**
  * @brief  Get the ADC sampling mode
  * @rmtoll CFGR2    BULB           LL_ADC_REG_GetSamplingMode
  *         CFGR2    SMPTRIG        LL_ADC_REG_GetSamplingMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_SAMPLING_MODE_NORMAL
  *         @arg @ref LL_ADC_REG_SAMPLING_MODE_BULB
  *         @arg @ref LL_ADC_REG_SAMPLING_MODE_TRIGGER_CONTROLED
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSamplingMode(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_BULB | ADC_CFGR2_SMPTRIG));
}

/**
  * @brief  Start ADC sampling phase for sampling time trigger mode
  * @note   This function is relevant only when
  *         - @ref LL_ADC_REG_SAMPLING_MODE_TRIGGER_CONTROLED has been set
  *           using @ref LL_ADC_REG_SetSamplingMode
  *         - @ref LL_ADC_REG_TRIG_SOFTWARE is used as trigger source
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion on going on group regular,
  *         without conversion stop command on going on group regular,
  *         without ADC disable command on going.
  * @rmtoll CFGR2    SWTRIG         LL_ADC_REG_StartSamplingPhase
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_StartSamplingPhase(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CFGR2, ADC_CFGR2_SWTRIG);
}

/**
  * @brief  Stop ADC sampling phase for sampling time trigger mode and start conversion
  * @note   This function is relevant only when
  *         - @ref LL_ADC_REG_SAMPLING_MODE_TRIGGER_CONTROLED has been set
  *           using @ref LL_ADC_REG_SetSamplingMode
  *         - @ref LL_ADC_REG_TRIG_SOFTWARE is used as trigger source
  *         - @ref LL_ADC_REG_StartSamplingPhase has been called to start
  *           the sampling phase
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion on going on group regular,
  *         without conversion stop command on going on group regular,
  *         without ADC disable command on going.
  * @rmtoll CFGR2    SWTRIG         LL_ADC_REG_StopSamplingPhase
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_StopSamplingPhase(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CFGR2, ADC_CFGR2_SWTRIG);
}

/**
  * @brief  Set ADC group regular sequencer configuration flexibility.
  * @note   On this STM32 series, ADC group regular sequencer both modes
  *         "fully configurable" or "not fully configurable" are
  *         available:
  *         - sequencer configured to fully configurable:
  *           sequencer length and each rank
  *           affectation to a channel are configurable.
  *           Refer to description of function
  *           @ref LL_ADC_REG_SetSequencerLength().
  *         - sequencer configured to not fully configurable:
  *           sequencer length and each rank affectation to a channel
  *           are fixed by channel HW number.
  *           Refer to description of function
  *           @ref LL_ADC_REG_SetSequencerChannels().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     CHSELRMOD      LL_ADC_REG_SetSequencerConfigurable
  * @param  ADCx ADC instance
  * @param  Configurability This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_FIXED
  *         @arg @ref LL_ADC_REG_SEQ_CONFIGURABLE
  * @retval None
  * @note   On this STM32U5 series, this is applicable on ADC4 only.
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerConfigurable(ADC_TypeDef *ADCx, uint32_t Configurability)
{
  MODIFY_REG(ADCx->CFGR1, ADC4_CFGR1_CHSELRMOD, Configurability);
}

/**
  * @brief  Get ADC group regular sequencer configuration flexibility.
  * @note   On this STM32 series, ADC group regular sequencer both modes
  *         "fully configurable" or "not fully configurable" are
  *         available:
  *         - sequencer configured to fully configurable:
  *           sequencer length and each rank
  *           affectation to a channel are configurable.
  *           Refer to description of function
  *           @ref LL_ADC_REG_SetSequencerLength().
  *         - sequencer configured to not fully configurable:
  *           sequencer length and each rank affectation to a channel
  *           are fixed by channel HW number.
  *           Refer to description of function
  *           @ref LL_ADC_REG_SetSequencerChannels().
  * @rmtoll CFGR     CHSELRMOD      LL_ADC_REG_SetSequencerConfigurable
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_FIXED
  *         @arg @ref LL_ADC_REG_SEQ_CONFIGURABLE
  * @note   On this STM32U5 series, this is applicable on ADC4 only.
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerConfigurable(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC4_CFGR1_CHSELRMOD));
}

/**
  * @brief  Set ADC group regular sequencer length and scan direction.
  * @note   Description of ADC group regular sequencer features:
  *         - For devices with sequencer fully configurable
  *           (function "LL_ADC_REG_SetSequencerRanks()" available):
  *           sequencer length and each rank affectation to a channel
  *           are configurable.
  *           This function performs configuration of:
  *           - Sequence length: Number of ranks in the scan sequence.
  *           - Sequence direction: Unless specified in parameters, sequencer
  *             scan direction is forward (from rank 1 to rank n).
  *           Sequencer ranks are selected using
  *           function "LL_ADC_REG_SetSequencerRanks()".
  *         - For devices with sequencer not fully configurable
  *           (function "LL_ADC_REG_SetSequencerChannels()" available):
  *           sequencer length and each rank affectation to a channel
  *           are defined by channel number.
  *           This function performs configuration of:
  *           - Sequence length: Number of ranks in the scan sequence is
  *             defined by number of channels set in the sequence,
  *             rank of each channel is fixed by channel HW number.
  *             (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
  *           - Sequence direction: Unless specified in parameters, sequencer
  *             scan direction is forward (from lowest channel number to
  *             highest channel number).
  *           Sequencer ranks are selected using
  *           function "LL_ADC_REG_SetSequencerChannels()".
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll SQR1     L              LL_ADC_REG_SetSequencerLength
  * @param  ADCx ADC instance
  * @param  SequencerNbRanks This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  if (ADCx != ADC4) /* ADC1 or ADC2 */
  {
    MODIFY_REG(ADCx->SQR1, ADC_SQR1_L, SequencerNbRanks);
  }
  else
  {
    SET_BIT(ADCx->CHSELR, SequencerNbRanks);
  }
}

/**
  * @brief  Get ADC group regular sequencer length and scan direction.
  * @note   Description of ADC group regular sequencer features:
  *         - For devices with sequencer fully configurable
  *           (function "LL_ADC_REG_SetSequencerRanks()" available):
  *           sequencer length and each rank affectation to a channel
  *           are configurable.
  *           This function retrieves:
  *           - Sequence length: Number of ranks in the scan sequence.
  *           - Sequence direction: Unless specified in parameters, sequencer
  *             scan direction is forward (from rank 1 to rank n).
  *           Sequencer ranks are selected using
  *           function "LL_ADC_REG_SetSequencerRanks()".
  *         - For devices with sequencer not fully configurable
  *           (function "LL_ADC_REG_SetSequencerChannels()" available):
  *           sequencer length and each rank affectation to a channel
  *           are defined by channel number.
  *           This function retrieves:
  *           - Sequence length: Number of ranks in the scan sequence is
  *             defined by number of channels set in the sequence,
  *             rank of each channel is fixed by channel HW number.
  *             (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
  *           - Sequence direction: Unless specified in parameters, sequencer
  *             scan direction is forward (from lowest channel number to
  *             highest channel number).
  *           Sequencer ranks are selected using
  *           function "LL_ADC_REG_SetSequencerChannels()".
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @rmtoll SQR1     L              LL_ADC_REG_GetSequencerLength
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerLength(ADC_TypeDef *ADCx)
{
  if (ADCx != ADC4) /* ADC1 or ADC2 */
  {
    return (uint32_t)(READ_BIT(ADCx->SQR1, ADC_SQR1_L));
  }
  else
  {
    uint32_t channels_ranks = READ_BIT(ADCx->CHSELR, ADC_CHSELR_SQ_ALL);
    uint32_t sequencer_length = LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS;
    uint32_t rank_index;
    uint32_t rank_shifted;

    /* Parse register for end of sequence identifier */
    /* Note: Value "0xF0UL" corresponds to bitfield of sequencer 2nd rank
             (ADC_CHSELR_SQ2), value "4" to length of end of sequence
             identifier (0xF)*/
    for (rank_index = 0UL; rank_index <= (28U - 4U); rank_index += 4U)
    {
      rank_shifted = (uint32_t)(0xF0UL << rank_index);
      if ((channels_ranks & rank_shifted) == rank_shifted)
      {
        sequencer_length = rank_shifted;
        break;
      }
    }

    return sequencer_length;
  }
}

/**
  * @brief  Set ADC group regular sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @note   It is not possible to enable both ADC group regular
  *         continuous mode and sequencer discontinuous mode.
  * @note   It is not possible to enable both ADC auto-injected mode
  *         and ADC group regular sequencer discontinuous mode.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     DISCEN         LL_ADC_REG_SetSequencerDiscont
  *         CFGR     DISCNUM        LL_ADC_REG_SetSequencerDiscont
  * @param  ADCx ADC instance
  * @param  SeqDiscont This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_1RANK
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_8RANKS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerDiscont(ADC_TypeDef *ADCx, uint32_t SeqDiscont)
{
  MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_DISCEN | ADC_CFGR1_DISCNUM, SeqDiscont);
}

/**
  * @brief  Get ADC group regular sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @rmtoll CFGR     DISCEN         LL_ADC_REG_GetSequencerDiscont
  *         CFGR     DISCNUM        LL_ADC_REG_GetSequencerDiscont
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_1RANK
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_8RANKS
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerDiscont(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_DISCEN | ADC_CFGR1_DISCNUM));
}

/**
  * @brief  Set ADC group regular sequence: channel on the selected
  *         scan sequence rank.
  * @note   This function performs configuration of:
  *         - Channels ordering into each rank of scan sequence:
  *           whatever channel can be placed into whatever rank.
  * @note   On this STM32 series, ADC group regular sequencer is
  *         fully configurable: sequencer length and each rank
  *         affectation to a channel are configurable.
  *         Refer to description of function @ref LL_ADC_REG_SetSequencerLength().
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   On this STM32 series, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll SQR1     SQ1            LL_ADC_REG_SetSequencerRanks
  *         SQR1     SQ2            LL_ADC_REG_SetSequencerRanks
  *         SQR1     SQ3            LL_ADC_REG_SetSequencerRanks
  *         SQR1     SQ4            LL_ADC_REG_SetSequencerRanks
  *         SQR2     SQ5            LL_ADC_REG_SetSequencerRanks
  *         SQR2     SQ6            LL_ADC_REG_SetSequencerRanks
  *         SQR2     SQ7            LL_ADC_REG_SetSequencerRanks
  *         SQR2     SQ8            LL_ADC_REG_SetSequencerRanks
  *         SQR2     SQ9            LL_ADC_REG_SetSequencerRanks
  *         SQR3     SQ10           LL_ADC_REG_SetSequencerRanks
  *         SQR3     SQ11           LL_ADC_REG_SetSequencerRanks
  *         SQR3     SQ12           LL_ADC_REG_SetSequencerRanks
  *         SQR3     SQ13           LL_ADC_REG_SetSequencerRanks
  *         SQR3     SQ14           LL_ADC_REG_SetSequencerRanks
  *         SQR4     SQ15           LL_ADC_REG_SetSequencerRanks
  *         SQR4     SQ16           LL_ADC_REG_SetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_RANK_1
  *         @arg @ref LL_ADC_REG_RANK_2
  *         @arg @ref LL_ADC_REG_RANK_3
  *         @arg @ref LL_ADC_REG_RANK_4
  *         @arg @ref LL_ADC_REG_RANK_5
  *         @arg @ref LL_ADC_REG_RANK_6
  *         @arg @ref LL_ADC_REG_RANK_7
  *         @arg @ref LL_ADC_REG_RANK_8
  *         @arg @ref LL_ADC_REG_RANK_9
  *         @arg @ref LL_ADC_REG_RANK_10
  *         @arg @ref LL_ADC_REG_RANK_11
  *         @arg @ref LL_ADC_REG_RANK_12
  *         @arg @ref LL_ADC_REG_RANK_13
  *         @arg @ref LL_ADC_REG_RANK_14
  *         @arg @ref LL_ADC_REG_RANK_15
  *         @arg @ref LL_ADC_REG_RANK_16
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4  (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4        (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
  /* Set bits with content of parameter "Channel" with bits position          */
  /* in register and register position depending on parameter "Rank".         */
  /* Parameters "Rank" and "Channel" are used with masks because containing   */
  /* other bits reserved for other purpose.                                   */
  if (ADCx != ADC4) /* ADC1 or ADC2 */
  {
    __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SQR1, ((Rank & ADC_REG_SQRX_REGOFFSET_MASK)     \
                                                            >> ADC_SQRX_REGOFFSET_POS));

    MODIFY_REG(*preg,
               ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0 << (Rank & ADC_REG_RANK_ID_SQRX_MASK),
               ((Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS) \
               << (Rank & ADC_REG_RANK_ID_SQRX_MASK));
  }
  else
  {
    MODIFY_REG(ADCx->CHSELR,
               ADC_CHSELR_SQ1 << (Rank & ADC_REG_RANK_ID_SQRX_MASK),
               (__LL_ADC_CHANNEL_TO_DECIMAL_NB(Channel) << (Rank & ADC_REG_RANK_ID_SQRX_MASK)));
  }
}

/**
  * @brief  Get ADC group regular sequence: channel on the selected
  *         scan sequence rank.
  * @note   On this STM32 series, ADC group regular sequencer is
  *         fully configurable: sequencer length and each rank
  *         affectation to a channel are configurable.
  *         Refer to description of function @ref LL_ADC_REG_SetSequencerLength().
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   Usage of the returned channel number:
  *         - To reinject this channel into another function LL_ADC_xxx:
  *           the returned channel number is only partly formatted on definition
  *           of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *           with parts of literals LL_ADC_CHANNEL_x or using
  *           helper macro @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  *           Then the selected literal LL_ADC_CHANNEL_x can be used
  *           as parameter for another function.
  *         - To get the channel number in decimal format:
  *           process the returned value with the helper macro
  *           @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  * @rmtoll SQR1     SQ1            LL_ADC_REG_GetSequencerRanks
  *         SQR1     SQ2            LL_ADC_REG_GetSequencerRanks
  *         SQR1     SQ3            LL_ADC_REG_GetSequencerRanks
  *         SQR1     SQ4            LL_ADC_REG_GetSequencerRanks
  *         SQR2     SQ5            LL_ADC_REG_GetSequencerRanks
  *         SQR2     SQ6            LL_ADC_REG_GetSequencerRanks
  *         SQR2     SQ7            LL_ADC_REG_GetSequencerRanks
  *         SQR2     SQ8            LL_ADC_REG_GetSequencerRanks
  *         SQR2     SQ9            LL_ADC_REG_GetSequencerRanks
  *         SQR3     SQ10           LL_ADC_REG_GetSequencerRanks
  *         SQR3     SQ11           LL_ADC_REG_GetSequencerRanks
  *         SQR3     SQ12           LL_ADC_REG_GetSequencerRanks
  *         SQR3     SQ13           LL_ADC_REG_GetSequencerRanks
  *         SQR3     SQ14           LL_ADC_REG_GetSequencerRanks
  *         SQR4     SQ15           LL_ADC_REG_GetSequencerRanks
  *         SQR4     SQ16           LL_ADC_REG_GetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_RANK_1
  *         @arg @ref LL_ADC_REG_RANK_2
  *         @arg @ref LL_ADC_REG_RANK_3
  *         @arg @ref LL_ADC_REG_RANK_4
  *         @arg @ref LL_ADC_REG_RANK_5
  *         @arg @ref LL_ADC_REG_RANK_6
  *         @arg @ref LL_ADC_REG_RANK_7
  *         @arg @ref LL_ADC_REG_RANK_8
  *         @arg @ref LL_ADC_REG_RANK_9
  *         @arg @ref LL_ADC_REG_RANK_10
  *         @arg @ref LL_ADC_REG_RANK_11
  *         @arg @ref LL_ADC_REG_RANK_12
  *         @arg @ref LL_ADC_REG_RANK_13
  *         @arg @ref LL_ADC_REG_RANK_14
  *         @arg @ref LL_ADC_REG_RANK_15
  *         @arg @ref LL_ADC_REG_RANK_16
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4  (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4        (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  *         (1, 2) For ADC channel read back from ADC register,
  *                comparison with internal channel parameter to be done
  *                using helper macro @ref __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank)
{
  if (ADCx != ADC4) /* ADC1 or ADC2 */
  {
    const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SQR1, ((Rank & ADC_REG_SQRX_REGOFFSET_MASK)       \
                                                                  >> ADC_SQRX_REGOFFSET_POS));

    return (uint32_t)((READ_BIT(*preg,
                                ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0 << (Rank & ADC_REG_RANK_ID_SQRX_MASK))
                       >> (Rank & ADC_REG_RANK_ID_SQRX_MASK)) << ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS
                     );
  }
  else
  {
    return (uint32_t)((READ_BIT(ADCx->CHSELR,
                                ADC_CHSELR_SQ1 << (Rank & ADC_REG_RANK_ID_SQRX_MASK))
                       >> (Rank & ADC_REG_RANK_ID_SQRX_MASK)
                      ) << (ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)
                     );
  }
}

/**
  * @brief  Set ADC group regular sequencer scan direction.
  * @note   On this STM32 series, parameter relevant only is sequencer is set
  *         to mode not fully configurable,
  *         refer to function @ref LL_ADC_REG_SetSequencerConfigurable().
  * @note   On some other STM32 families, this setting is not available and
  *         the default scan direction is forward.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR1    SCANDIR        LL_ADC_REG_SetSequencerScanDirection
  * @param  ADCx ADC instance
  * @param  ScanDirection This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DIR_FORWARD
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DIR_BACKWARD
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerScanDirection(ADC_TypeDef *ADCx, uint32_t ScanDirection)
{
  MODIFY_REG(ADCx->CFGR1, ADC4_CFGR1_SCANDIR, ScanDirection);
}

/**
  * @brief  Get ADC group regular sequencer scan direction.
  * @note   On this STM32 series, parameter relevant only is sequencer is set
  *         to mode not fully configurable,
  *         refer to function @ref LL_ADC_REG_SetSequencerConfigurable().
  * @note   On some other STM32 families, this setting is not available and
  *         the default scan direction is forward.
  * @rmtoll CFGR1    SCANDIR        LL_ADC_REG_GetSequencerScanDirection
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DIR_FORWARD
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DIR_BACKWARD
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerScanDirection(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC4_CFGR1_SCANDIR));
}

/**
  * @brief  Set ADC group regular sequence: channel on rank corresponding to
  *         channel number.
  * @note   This function performs:
  *         - Channels ordering into each rank of scan sequence:
  *           rank of each channel is fixed by channel HW number
  *           (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
  *         - Set channels selected by overwriting the current sequencer
  *           configuration.
  * @note   On this STM32 series, ADC group regular sequencer both modes
  *         "fully configurable" or "not fully configurable"
  *         are available, they can be chosen using
  *         function @ref LL_ADC_REG_SetSequencerConfigurable().
  *         This function can be used with setting "not fully configurable".
  *         Refer to description of functions @ref LL_ADC_REG_SetSequencerConfigurable()
  *         and @ref LL_ADC_REG_SetSequencerLength().
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   On this STM32 series, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_CHANNEL_4 | LL_ADC_CHANNEL_12 | ...)
  * @rmtoll CHSELR   CHSEL0         LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL1         LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL2         LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL3         LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL4         LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL5         LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL6         LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL7         LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL8         LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL9         LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL10        LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL11        LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL12        LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL13        LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL14        LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL15        LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL16        LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL17        LL_ADC_REG_SetSequencerChannels
  *         CHSELR   CHSEL18        LL_ADC_REG_SetSequencerChannels
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15         (1)
  *         @arg @ref LL_ADC_CHANNEL_16         (1)
  *         @arg @ref LL_ADC_CHANNEL_17         (1)
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR
  *         @arg @ref LL_ADC_CHANNEL_VBAT
  *
  *         (1) On STM32U5, parameter can be set in ADC group sequencer
  *             only if sequencer is set in mode "not fully configurable",
  *             refer to function @ref LL_ADC_REG_SetSequencerConfigurable().
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerChannels(ADC_TypeDef *ADCx, uint32_t Channel)
{
  /* Parameter "Channel" is used with masks because containing                */
  /* other bits reserved for other purpose.                                   */
  WRITE_REG(ADCx->CHSELR, (Channel & ADC_CHANNEL_ID_BITFIELD_MASK));
}

/**
  * @brief  Add channel to ADC group regular sequence: channel on rank corresponding to
  *         channel number.
  * @note   This function performs:
  *         - Channels ordering into each rank of scan sequence:
  *           rank of each channel is fixed by channel HW number
  *           (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
  *         - Set channels selected by adding them to the current sequencer
  *           configuration.
  * @note   On this STM32 series, ADC group regular sequencer both modes
  *         "fully configurable" or "not fully configurable"
  *         are available, they can be chosen using
  *         function @ref LL_ADC_REG_SetSequencerConfigurable().
  *         This function can be used with setting "not fully configurable".
  *         Refer to description of functions @ref LL_ADC_REG_SetSequencerConfigurable()
  *         and @ref LL_ADC_REG_SetSequencerLength().
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   On this STM32 series, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_CHANNEL_4 | LL_ADC_CHANNEL_12 | ...)
  * @rmtoll CHSELR   CHSEL0         LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL1         LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL2         LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL3         LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL4         LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL5         LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL6         LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL7         LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL8         LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL9         LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL10        LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL11        LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL12        LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL13        LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL14        LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL15        LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL16        LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL17        LL_ADC_REG_SetSequencerChAdd
  *         CHSELR   CHSEL18        LL_ADC_REG_SetSequencerChAdd
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15         (1)
  *         @arg @ref LL_ADC_CHANNEL_16         (1)
  *         @arg @ref LL_ADC_CHANNEL_17         (1)
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR
  *         @arg @ref LL_ADC_CHANNEL_VBAT
  *
  *         (1) On STM32U5, parameter can be set in ADC group sequencer
  *             only if sequencer is set in mode "not fully configurable",
  *             refer to function @ref LL_ADC_REG_SetSequencerConfigurable().
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerChAdd(ADC_TypeDef *ADCx, uint32_t Channel)
{
  /* Parameter "Channel" is used with masks because containing                */
  /* other bits reserved for other purpose.                                   */
  SET_BIT(ADCx->CHSELR, (1UL << ((__LL_ADC_CHANNEL_TO_DECIMAL_NB(Channel) & ADC_CHSELR_CHSEL) & 0x1FUL)));
}

/**
  * @brief  Remove channel to ADC group regular sequence: channel on rank corresponding to
  *         channel number.
  * @note   This function performs:
  *         - Channels ordering into each rank of scan sequence:
  *           rank of each channel is fixed by channel HW number
  *           (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
  *         - Set channels selected by removing them to the current sequencer
  *           configuration.
  * @note   On this STM32 series, ADC group regular sequencer both modes
  *         "fully configurable" or "not fully configurable"
  *         are available, they can be chosen using
  *         function @ref LL_ADC_REG_SetSequencerConfigurable().
  *         This function can be used with setting "not fully configurable".
  *         Refer to description of functions @ref LL_ADC_REG_SetSequencerConfigurable()
  *         and @ref LL_ADC_REG_SetSequencerLength().
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   On this STM32 series, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_CHANNEL_4 | LL_ADC_CHANNEL_12 | ...)
  * @rmtoll CHSELR   CHSEL0         LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL1         LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL2         LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL3         LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL4         LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL5         LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL6         LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL7         LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL8         LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL9         LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL10        LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL11        LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL12        LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL13        LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL14        LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL15        LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL16        LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL17        LL_ADC_REG_SetSequencerChRem
  *         CHSELR   CHSEL18        LL_ADC_REG_SetSequencerChRem
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15         (1)
  *         @arg @ref LL_ADC_CHANNEL_16         (1)
  *         @arg @ref LL_ADC_CHANNEL_17         (1)
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR
  *         @arg @ref LL_ADC_CHANNEL_VBAT
  *
  *         (1) On STM32U5, parameter can be set in ADC group sequencer
  *             only if sequencer is set in mode "not fully configurable",
  *             refer to function @ref LL_ADC_REG_SetSequencerConfigurable().
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerChRem(ADC_TypeDef *ADCx, uint32_t Channel)
{
  /* Parameter "Channel" is used with masks because containing                */
  /* other bits reserved for other purpose.                                   */
  CLEAR_BIT(ADCx->CHSELR, (1UL << ((Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)));
}

/**
  * @brief  Get ADC group regular sequence: channel on rank corresponding to
  *         channel number.
  * @note   This function performs:
  *         - Channels order reading into each rank of scan sequence:
  *           rank of each channel is fixed by channel HW number
  *           (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
  * @note   On this STM32 series, ADC group regular sequencer both modes
  *         "fully configurable" or "not fully configurable"
  *         are available, they can be chosen using
  *         function @ref LL_ADC_REG_SetSequencerConfigurable().
  *         This function can be used with setting "not fully configurable".
  *         Refer to description of functions @ref LL_ADC_REG_SetSequencerConfigurable()
  *         and @ref LL_ADC_REG_SetSequencerLength().
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   On this STM32 series, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @note   One or several values can be retrieved.
  *         Example: (LL_ADC_CHANNEL_4 | LL_ADC_CHANNEL_12 | ...)
  * @rmtoll CHSELR   CHSEL0         LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL1         LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL2         LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL3         LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL4         LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL5         LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL6         LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL7         LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL8         LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL9         LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL10        LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL11        LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL12        LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL13        LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL14        LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL15        LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL16        LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL17        LL_ADC_REG_GetSequencerChannels
  *         CHSELR   CHSEL18        LL_ADC_REG_GetSequencerChannels
  * @param  ADCx ADC instance
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15         (1)
  *         @arg @ref LL_ADC_CHANNEL_16         (1)
  *         @arg @ref LL_ADC_CHANNEL_17         (1)
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR
  *         @arg @ref LL_ADC_CHANNEL_VBAT
  *
  *         (1) On STM32U5, parameter can be set in ADC group sequencer
  *             only if sequencer is set in mode "not fully configurable",
  *             refer to function @ref LL_ADC_REG_SetSequencerConfigurable().
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerChannels(ADC_TypeDef *ADCx)
{
  uint32_t channels_bitfield = READ_BIT(ADCx->CHSELR, ADC_CHSELR_CHSEL);

  return ((((channels_bitfield & ADC_CHSELR_CHSEL0) >> ADC4_CHSELR_CHSEL0_BITOFFSET_POS) * LL_ADC_CHANNEL_0)
          | (((channels_bitfield & ADC_CHSELR_CHSEL1) >> ADC4_CHSELR_CHSEL1_BITOFFSET_POS) * LL_ADC_CHANNEL_1)
          | (((channels_bitfield & ADC_CHSELR_CHSEL2) >> ADC4_CHSELR_CHSEL2_BITOFFSET_POS) * LL_ADC_CHANNEL_2)
          | (((channels_bitfield & ADC_CHSELR_CHSEL3) >> ADC4_CHSELR_CHSEL3_BITOFFSET_POS) * LL_ADC_CHANNEL_3)
          | (((channels_bitfield & ADC_CHSELR_CHSEL4) >> ADC4_CHSELR_CHSEL4_BITOFFSET_POS) * LL_ADC_CHANNEL_4)
          | (((channels_bitfield & ADC_CHSELR_CHSEL5) >> ADC4_CHSELR_CHSEL5_BITOFFSET_POS) * LL_ADC_CHANNEL_5)
          | (((channels_bitfield & ADC_CHSELR_CHSEL6) >> ADC4_CHSELR_CHSEL6_BITOFFSET_POS) * LL_ADC_CHANNEL_6)
          | (((channels_bitfield & ADC_CHSELR_CHSEL7) >> ADC4_CHSELR_CHSEL7_BITOFFSET_POS) * LL_ADC_CHANNEL_7)
          | (((channels_bitfield & ADC_CHSELR_CHSEL8) >> ADC4_CHSELR_CHSEL8_BITOFFSET_POS) * LL_ADC_CHANNEL_8)
          | (((channels_bitfield & ADC_CHSELR_CHSEL9) >> ADC4_CHSELR_CHSEL9_BITOFFSET_POS) * LL_ADC_CHANNEL_9)
          | (((channels_bitfield & ADC_CHSELR_CHSEL10) >> ADC4_CHSELR_CHSEL10_BITOFFSET_POS) * LL_ADC_CHANNEL_10)
          | (((channels_bitfield & ADC_CHSELR_CHSEL11) >> ADC4_CHSELR_CHSEL11_BITOFFSET_POS) * LL_ADC_CHANNEL_11)
          | (((channels_bitfield & ADC_CHSELR_CHSEL12) >> ADC4_CHSELR_CHSEL12_BITOFFSET_POS) * LL_ADC_CHANNEL_12)
          | (((channels_bitfield & ADC_CHSELR_CHSEL13) >> ADC4_CHSELR_CHSEL13_BITOFFSET_POS) * LL_ADC_CHANNEL_13)
          | (((channels_bitfield & ADC_CHSELR_CHSEL14) >> ADC4_CHSELR_CHSEL14_BITOFFSET_POS) * LL_ADC_CHANNEL_14)
          | (((channels_bitfield & ADC_CHSELR_CHSEL15) >> ADC4_CHSELR_CHSEL15_BITOFFSET_POS) * LL_ADC_CHANNEL_15)
          | (((channels_bitfield & ADC_CHSELR_CHSEL16) >> ADC4_CHSELR_CHSEL16_BITOFFSET_POS) * LL_ADC_CHANNEL_16)
          | (((channels_bitfield & ADC_CHSELR_CHSEL17) >> ADC4_CHSELR_CHSEL17_BITOFFSET_POS) * LL_ADC_CHANNEL_17)
          | (((channels_bitfield & ADC_CHSELR_CHSEL18) >> ADC4_CHSELR_CHSEL18_BITOFFSET_POS) * LL_ADC_CHANNEL_18)
          | (((channels_bitfield & ADC_CHSELR_CHSEL19) >> ADC4_CHSELR_CHSEL19_BITOFFSET_POS) * LL_ADC_CHANNEL_19)
          | (((channels_bitfield & ADC_CHSELR_CHSEL20) >> ADC4_CHSELR_CHSEL20_BITOFFSET_POS) * LL_ADC_CHANNEL_20)
          | (((channels_bitfield & ADC_CHSELR_CHSEL21) >> ADC4_CHSELR_CHSEL21_BITOFFSET_POS) * LL_ADC_CHANNEL_21)
          | (((channels_bitfield & ADC_CHSELR_CHSEL22) >> ADC4_CHSELR_CHSEL22_BITOFFSET_POS) * LL_ADC_CHANNEL_22)
          | (((channels_bitfield & ADC_CHSELR_CHSEL23) >> ADC4_CHSELR_CHSEL23_BITOFFSET_POS) * LL_ADC_CHANNEL_23)

         );
}

/**
  * @brief  Set ADC Channel Preselection to LL_ADC_CHANNEL_x, x = 0 to 19.
  * @note   This function set the the value for the channel preselection register
  *         corresponding to ADC channel to be selected.
  * @note   Caution: This is not valid for ADC4.
  * @param  ADCx ADC instance.
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR
  *         @arg @ref LL_ADC_CHANNEL_VBAT
  *
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelPreselection(ADC_TypeDef *ADCx, uint32_t Channel)
{
  __IO uint32_t channel_preselectione = READ_REG(ADCx->PCSEL);
  WRITE_REG(ADCx->PCSEL,
            channel_preselectione | (1UL << (__LL_ADC_CHANNEL_TO_DECIMAL_NB((uint32_t)Channel) & 0x1FUL)));
}

/**
  * @brief  Get ADC Channel Preselection register value.
  * @note   This function set the the value for the channel preselection register
  *         corresponding to ADC channel to be selected.
  * @note   Caution: This is not valid for ADC4.
  * @param  ADCx ADC instance.
  *
  * @retval Returned decimal value that can correspend to one or multiple channels:
  * @rmtoll PCSEL   PCSEL0         LL_ADC_CHANNEL_0
  *         PCSEL   PCSEL1         LL_ADC_CHANNEL_1
  *         PCSEL   PCSEL2         LL_ADC_CHANNEL_2
  *         PCSEL   PCSEL3         LL_ADC_CHANNEL_3
  *         PCSEL   PCSEL4         LL_ADC_CHANNEL_4
  *         PCSEL   PCSEL5         LL_ADC_CHANNEL_5
  *         PCSEL   PCSEL6         LL_ADC_CHANNEL_6
  *         PCSEL   PCSEL7         LL_ADC_CHANNEL_7
  *         PCSEL   PCSEL8         LL_ADC_CHANNEL_8
  *         PCSEL   PCSEL9         LL_ADC_CHANNEL_9
  *         PCSEL   PCSEL10        LL_ADC_CHANNEL_10
  *         PCSEL   PCSEL11        LL_ADC_CHANNEL_11
  *         PCSEL   PCSEL12        LL_ADC_CHANNEL_12
  *         PCSEL   PCSEL13        LL_ADC_CHANNEL_13
  *         PCSEL   PCSEL14        LL_ADC_CHANNEL_14
  *         PCSEL   PCSEL15        LL_ADC_CHANNEL_15
  *         PCSEL   PCSEL16        LL_ADC_CHANNEL_16
  *         PCSEL   PCSEL17        LL_ADC_CHANNEL_17
  *         PCSEL   PCSEL18        LL_ADC_CHANNEL_18
  *         PCSEL   PCSEL19        LL_ADC_CHANNEL_19
  *
  * @note   User helper macro @ref __LL_ADC_DECIMAL_NB_TO_CHANNEL().
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelPreselection(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->PCSEL, ADC_PCSEL_PCSEL));
}

/**
  * @brief  Set ADC low power mode.
  * @note   Description of ADC low power mode:
  *         - ADC low power mode "auto power-off":
  *           the ADC automatically powers-off after a conversion and
  *           automatically wakes up when a new conversion is triggered
  *           (with startup time between trigger and start of sampling).
  *           This feature can be combined with low power mode "auto wait".
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled.
  * @rmtoll PWRR     AUTOFF         LL_ADC_SetLPModeAutoPowerOff
  * @param  ADCx ADC instance
  * @param  LowPowerMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_LP_AUTOPOWEROFF_DISABLE
  *         @arg @ref LL_ADC_LP_AUTOPOWEROFF_ENABLE
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetLPModeAutoPowerOff(ADC_TypeDef *ADCx, uint32_t LowPowerMode)
{
  MODIFY_REG(ADCx->PW, ADC4_PW_AUTOFF, LowPowerMode);
}

/**
  * @brief  Get ADC low power mode.
  * @note   Description of ADC low power mode:
  *         - ADC low power mode "auto power-off":
  *           the ADC automatically powers-off after a conversion and
  *           automatically wakes up when a new conversion is triggered
  *           (with startup time between trigger and start of sampling).
  *           This feature can be combined with low power mode "auto wait".
  * @rmtoll PW     AUTOFF         LL_ADC_GetLPModeAutoPowerOff
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_LP_AUTOPOWEROFF_DISABLE
  *         @arg @ref LL_ADC_LP_AUTOPOWEROFF_ENABLE
  */
__STATIC_INLINE uint32_t LL_ADC_GetLPModeAutoPowerOff(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->PW, ADC4_PW_AUTOFF));
}

/**
  * @brief  Set ADC low power mode: deep power down in autonomous mode
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled.
  * @rmtoll PWRR     DPD            LL_ADC_SetLPModeAutonomousDPD
  * @param  ADCx ADC instance
  * @param  LowPowerMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_LP_AUTONOMOUS_DPD_DISABLE
  *         @arg @ref LL_ADC_LP_AUTONOMOUS_DPD_ENABLE
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetLPModeAutonomousDPD(ADC_TypeDef *ADCx, uint32_t LowPowerMode)
{
  MODIFY_REG(ADCx->PW, ADC4_PW_DPD, LowPowerMode);
}

/**
  * @brief  Get ADC low power mode: deep power down in autonomous mode
  * @rmtoll PWRR     DPD            LL_ADC_GetLPModeAutonomousDPD
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_LP_AUTONOMOUS_DPD_DISABLE
  *         @arg @ref LL_ADC_LP_AUTONOMOUS_DPD_ENABLE
  */
__STATIC_INLINE uint32_t LL_ADC_GetLPModeAutonomousDPD(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->PW, ADC4_PW_DPD));
}

/**
  * @brief  Set ADC continuous conversion mode on ADC group regular.
  * @note   Description of ADC continuous conversion mode:
  *         - single mode: one conversion per trigger
  *         - continuous mode: after the first trigger, following
  *           conversions launched successively automatically.
  * @note   It is not possible to enable both ADC group regular
  *         continuous mode and sequencer discontinuous mode.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     CONT           LL_ADC_REG_SetContinuousMode
  * @param  ADCx ADC instance
  * @param  Continuous This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_CONV_SINGLE
  *         @arg @ref LL_ADC_REG_CONV_CONTINUOUS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetContinuousMode(ADC_TypeDef *ADCx, uint32_t Continuous)
{
  MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_CONT, Continuous);
}

/**
  * @brief  Get ADC continuous conversion mode on ADC group regular.
  * @note   Description of ADC continuous conversion mode:
  *         - single mode: one conversion per trigger
  *         - continuous mode: after the first trigger, following
  *           conversions launched successively automatically.
  * @rmtoll CFGR     CONT           LL_ADC_REG_GetContinuousMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_CONV_SINGLE
  *         @arg @ref LL_ADC_REG_CONV_CONTINUOUS
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetContinuousMode(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_CONT));
}
/**
  * @brief  Set ADC data transfer mode
  * @note   Conversion data can be either:
  *            - Available in Data Register
  *            - Transferred by DMA in one shot mode
  *            - Transferred by DMA in circular mode
  *            - Transferred to MDF data register
  * @rmtoll CFGR     DMNGT           LL_ADC_REG_SetDataTransferMode
  * @param  ADCx ADC instance
  * @param  DataTransferMode Select Data Management configuration
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetDataTransferMode(ADC_TypeDef *ADCx, uint32_t DataTransferMode)
{
  MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_DMNGT, DataTransferMode);
}

/**
  * @brief  Get ADC data transfer mode
  * @note   Conversion data can be either:
  *            - Available in Data Register
  *            - Transferred by DMA in one shot mode
  *            - Transferred by DMA in circular mode
  *            - Transferred to DFSDM data register
  * @rmtoll CFGR     DMNGT           LL_ADC_REG_GetDataTransferMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_DR_TRANSFER
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_LIMITED
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_UNLIMITED
  *         @arg @ref LL_ADC_REG_MDF_TRANSFER
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetDataTransferMode(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_DMNGT));
}

/**
  * @brief  Set ADC group regular conversion data transfer: no transfer or
  *         transfer by DMA, and DMA requests mode.
  * @note   If transfer by DMA selected, specifies the DMA requests
  *         mode:
  *         - Limited mode (One shot mode): DMA transfer requests are stopped
  *           when number of DMA data transfers (number of
  *           ADC conversions) is reached.
  *           This ADC mode is intended to be used with DMA mode non-circular.
  *         - Unlimited mode: DMA transfer requests are unlimited,
  *           whatever number of DMA data transfers (number of
  *           ADC conversions).
  *           This ADC mode is intended to be used with DMA mode circular.
  * @note   If ADC DMA requests mode is set to unlimited and DMA is set to
  *         mode non-circular:
  *         when DMA transfers size will be reached, DMA will stop transfers of
  *         ADC conversions data ADC will raise an overrun error
  *        (overrun flag and interruption if enabled).
  * @note   To configure DMA source address (peripheral address),
  *         use function @ref LL_ADC_DMA_GetRegAddr().
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR1    DMAEN          LL_ADC_REG_SetDMATransfer
  *         CFGR1    DMACFG         LL_ADC_REG_SetDMATransfer
  * @param  ADCx ADC instance
  * @param  DMATransfer This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_NONE
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_LIMITED
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_UNLIMITED
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetDMATransfer(ADC_TypeDef *ADCx, uint32_t DMATransfer)
{
  MODIFY_REG(ADCx->CFGR1, ADC4_CFGR1_DMAEN | ADC4_CFGR1_DMACFG, DMATransfer);
}

/**
  * @brief  Get ADC group regular conversion data transfer: no transfer or
  *         transfer by DMA, and DMA requests mode.
  * @note   If transfer by DMA selected, specifies the DMA requests
  *         mode:
  *         - Limited mode (One shot mode): DMA transfer requests are stopped
  *           when number of DMA data transfers (number of
  *           ADC conversions) is reached.
  *           This ADC mode is intended to be used with DMA mode non-circular.
  *         - Unlimited mode: DMA transfer requests are unlimited,
  *           whatever number of DMA data transfers (number of
  *           ADC conversions).
  *           This ADC mode is intended to be used with DMA mode circular.
  * @note   If ADC DMA requests mode is set to unlimited and DMA is set to
  *         mode non-circular:
  *         when DMA transfers size will be reached, DMA will stop transfers of
  *         ADC conversions data ADC will raise an overrun error
  *         (overrun flag and interruption if enabled).
  * @note   To configure DMA source address (peripheral address),
  *         use function @ref LL_ADC_DMA_GetRegAddr().
  * @rmtoll CFGR1    DMAEN          LL_ADC_REG_GetDMATransfer
  *         CFGR1    DMACFG         LL_ADC_REG_GetDMATransfer
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_NONE
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_LIMITED
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_UNLIMITED
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetDMATransfer(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC4_CFGR1_DMAEN | ADC4_CFGR1_DMACFG));
}

/**
  * @brief  Set ADC group regular behavior in case of overrun:
  *         data preserved or overwritten.
  * @note   Compatibility with devices without feature overrun:
  *         other devices without this feature have a behavior
  *         equivalent to data overwritten.
  *         The default setting of overrun is data preserved.
  *         Therefore, for compatibility with all devices, parameter
  *         overrun should be set to data overwritten.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     OVRMOD         LL_ADC_REG_SetOverrun
  * @param  ADCx ADC instance
  * @param  Overrun This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_OVR_DATA_PRESERVED
  *         @arg @ref LL_ADC_REG_OVR_DATA_OVERWRITTEN
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetOverrun(ADC_TypeDef *ADCx, uint32_t Overrun)
{
  MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_OVRMOD, Overrun);
}

/**
  * @brief  Get ADC group regular behavior in case of overrun:
  *         data preserved or overwritten.
  * @rmtoll CFGR     OVRMOD         LL_ADC_REG_GetOverrun
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_OVR_DATA_PRESERVED
  *         @arg @ref LL_ADC_REG_OVR_DATA_OVERWRITTEN
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetOverrun(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_OVRMOD));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Group_Injected Configuration of ADC hierarchical scope: group injected
  * @{
  */

/**
  * @brief  Set ADC group injected conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         external interrupt line).
  * @note   On this STM32 series, setting trigger source to external trigger
  *         also set trigger polarity to rising edge
  *         (default setting for compatibility with some ADC on other
  *         STM32 families having this setting set by HW default value).
  *         In case of need to modify trigger edge, use
  *         function @ref LL_ADC_INJ_SetTriggerEdge().
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JEXTSEL        LL_ADC_INJ_SetTriggerSource
  *         JSQR     JEXTEN         LL_ADC_INJ_SetTriggerSource
  * @param  ADCx ADC instance
  * @param  TriggerSource This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_SOFTWARE
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_CH4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM2_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM2_CH1
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CH4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM4_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_EXTI_LINE15
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_CH4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CH3
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CH1
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM6_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM15_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_LPTIM1_CH2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_LPTIM2_CH2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_LPTIM3_CH1
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetTriggerSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
  MODIFY_REG(ADCx->JSQR, ADC_JSQR_JEXTSEL | ADC_JSQR_JEXTEN, TriggerSource);
}

/**
  * @brief  Get ADC group injected conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         external interrupt line).
  * @note   To determine whether group injected trigger source is
  *         internal (SW start) or external, without detail
  *         of which peripheral is selected as external trigger,
  *         (equivalent to
  *         "if(LL_ADC_INJ_GetTriggerSource(ADC1) == LL_ADC_INJ_TRIG_SOFTWARE)")
  *         use function @ref LL_ADC_INJ_IsTriggerSourceSWStart.
  * @note   Availability of parameters of trigger sources from timer
  *         depends on timers availability on the selected device.
  * @rmtoll JSQR     JEXTSEL        LL_ADC_INJ_GetTriggerSource
  *         JSQR     JEXTEN         LL_ADC_INJ_GetTriggerSource
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_SOFTWARE
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_CH4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM2_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM2_CH1
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CH4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM4_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_EXTI_LINE15
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_CH4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CH3
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CH1
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM6_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM15_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_LPTIM1_CH2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_LPTIM2_CH2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_LPTIM3_CH1
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTriggerSource(ADC_TypeDef *ADCx)
{
  __IO uint32_t trigger_source = READ_BIT(ADCx->JSQR, ADC_JSQR_JEXTSEL | ADC_JSQR_JEXTEN);

  /* Value for shift of {0; 4; 8; 12} depending on value of bitfield          */
  /* corresponding to ADC_JSQR_JEXTEN {0; 1; 2; 3}.                           */
  uint32_t shift_jexten = ((trigger_source & ADC_JSQR_JEXTEN) >> (ADC_INJ_TRIG_EXTEN_BITOFFSET_POS - 2UL));

  /* Set bitfield corresponding to ADC_JSQR_JEXTEN and ADC_JSQR_JEXTSEL       */
  /* to match with triggers literals definition.                              */
  return ((trigger_source
           & (ADC_INJ_TRIG_SOURCE_MASK >> shift_jexten) & ADC_JSQR_JEXTSEL)
          | ((ADC_INJ_TRIG_EDGE_MASK >> shift_jexten) & ADC_JSQR_JEXTEN)
         );
}

/**
  * @brief  Get ADC group injected conversion trigger source internal (SW start)
            or external
  * @note   In case of group injected trigger source set to external trigger,
  *         to determine which peripheral is selected as external trigger,
  *         use function @ref LL_ADC_INJ_GetTriggerSource.
  * @rmtoll JSQR     JEXTEN         LL_ADC_INJ_IsTriggerSourceSWStart
  * @param  ADCx ADC instance
  * @retval Value "0" if trigger source external trigger
  *         Value "1" if trigger source SW start.
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsTriggerSourceSWStart(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->JSQR, ADC_JSQR_JEXTEN) == (LL_ADC_INJ_TRIG_SOFTWARE & ADC_JSQR_JEXTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set ADC group injected conversion trigger polarity.
  *         Applicable only for trigger source set to external trigger.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JEXTEN         LL_ADC_INJ_SetTriggerEdge
  * @param  ADCx ADC instance
  * @param  ExternalTriggerEdge This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISINGFALLING
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetTriggerEdge(ADC_TypeDef *ADCx, uint32_t ExternalTriggerEdge)
{
  MODIFY_REG(ADCx->JSQR, ADC_JSQR_JEXTEN, ExternalTriggerEdge);
}

/**
  * @brief  Get ADC group injected conversion trigger polarity.
  *         Applicable only for trigger source set to external trigger.
  * @rmtoll JSQR     JEXTEN         LL_ADC_INJ_GetTriggerEdge
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISINGFALLING
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTriggerEdge(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->JSQR, ADC_JSQR_JEXTEN));
}

/**
  * @brief  Set ADC group injected sequencer length and scan direction.
  * @note   This function performs configuration of:
  *         - Sequence length: Number of ranks in the scan sequence.
  *         - Sequence direction: Unless specified in parameters, sequencer
  *           scan direction is forward (from rank 1 to rank n).
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JL             LL_ADC_INJ_SetSequencerLength
  * @param  ADCx ADC instance
  * @param  SequencerNbRanks This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  MODIFY_REG(ADCx->JSQR, ADC_JSQR_JL, SequencerNbRanks);
}

/**
  * @brief  Get ADC group injected sequencer length and scan direction.
  * @note   This function retrieves:
  *         - Sequence length: Number of ranks in the scan sequence.
  *         - Sequence direction: Unless specified in parameters, sequencer
  *           scan direction is forward (from rank 1 to rank n).
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @rmtoll JSQR     JL             LL_ADC_INJ_GetSequencerLength
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerLength(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->JSQR, ADC_JSQR_JL));
}

/**
  * @brief  Set ADC group injected sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @note   It is not possible to enable both ADC group injected
  *         auto-injected mode and sequencer discontinuous mode.
  * @rmtoll CFGR     JDISCEN        LL_ADC_INJ_SetSequencerDiscont
  * @param  ADCx ADC instance
  * @param  SeqDiscont This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_1RANK
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerDiscont(ADC_TypeDef *ADCx, uint32_t SeqDiscont)
{
  MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_JDISCEN, SeqDiscont);
}

/**
  * @brief  Get ADC group injected sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @rmtoll CFGR     JDISCEN        LL_ADC_INJ_GetSequencerDiscont
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_1RANK
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerDiscont(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_JDISCEN));
}

/**
  * @brief  Set ADC group injected sequence: channel on the selected
  *         sequence rank.
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   On this STM32 series, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On STM32U5, some fast channels are available: fast analog inputs
  *         coming from GPIO pads (ADC_IN0..5).
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JSQ1           LL_ADC_INJ_SetSequencerRanks
  *         JSQR     JSQ2           LL_ADC_INJ_SetSequencerRanks
  *         JSQR     JSQ3           LL_ADC_INJ_SetSequencerRanks
  *         JSQR     JSQ4           LL_ADC_INJ_SetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4  (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4        (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
  /* Set bits with content of parameter "Channel" with bits position          */
  /* in register depending on parameter "Rank".                               */
  /* Parameters "Rank" and "Channel" are used with masks because containing   */
  /* other bits reserved for other purpose.                                   */
  MODIFY_REG(ADCx->JSQR,
             (ADC_CHANNEL_ID_NUMBER_MASK >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS) << (Rank & ADC_INJ_RANK_ID_JSQR_MASK),
             ((Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)                          \
             << (Rank & ADC_INJ_RANK_ID_JSQR_MASK));
}

/**
  * @brief  Get ADC group injected sequence: channel on the selected
  *         sequence rank.
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   Usage of the returned channel number:
  *         - To reinject this channel into another function LL_ADC_xxx:
  *           the returned channel number is only partly formatted on definition
  *           of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *           with parts of literals LL_ADC_CHANNEL_x or using
  *           helper macro @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  *           Then the selected literal LL_ADC_CHANNEL_x can be used
  *           as parameter for another function.
  *         - To get the channel number in decimal format:
  *           process the returned value with the helper macro
  *           @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  * @rmtoll JSQR     JSQ1           LL_ADC_INJ_GetSequencerRanks
  *         JSQR     JSQ2           LL_ADC_INJ_GetSequencerRanks
  *         JSQR     JSQ3           LL_ADC_INJ_GetSequencerRanks
  *         JSQR     JSQ4           LL_ADC_INJ_GetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4  (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4        (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  *         (1, 2) For ADC channel read back from ADC register,
  *                comparison with internal channel parameter to be done
  *                using helper macro @ref __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank)
{
  return (uint32_t)((READ_BIT(ADCx->JSQR,
                              (ADC_CHANNEL_ID_NUMBER_MASK >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)         \
                              << (Rank & ADC_INJ_RANK_ID_JSQR_MASK))
                     >> (Rank & ADC_INJ_RANK_ID_JSQR_MASK)) << ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS
                   );
}

/**
  * @brief  Set ADC group injected conversion trigger:
  *         independent or from ADC group regular.
  * @note   This mode can be used to extend number of data registers
  *         updated after one ADC conversion trigger and with data
  *         permanently kept (not erased by successive conversions of scan of
  *         ADC sequencer ranks), up to 5 data registers:
  *         1 data register on ADC group regular, 4 data registers
  *         on ADC group injected.
  * @note   If ADC group injected injected trigger source is set to an
  *         external trigger, this feature must be must be set to
  *         independent trigger.
  *         ADC group injected automatic trigger is compliant only with
  *         group injected trigger source set to SW start, without any
  *         further action on  ADC group injected conversion start or stop:
  *         in this case, ADC group injected is controlled only
  *         from ADC group regular.
  * @note   It is not possible to enable both ADC group injected
  *         auto-injected mode and sequencer discontinuous mode.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     JAUTO          LL_ADC_INJ_SetTrigAuto
  * @param  ADCx ADC instance
  * @param  TrigAuto This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_INDEPENDENT
  *         @arg @ref LL_ADC_INJ_TRIG_FROM_GRP_REGULAR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetTrigAuto(ADC_TypeDef *ADCx, uint32_t TrigAuto)
{
  MODIFY_REG(ADCx->CFGR1, ADC_CFGR1_JAUTO, TrigAuto);
}

/**
  * @brief  Get ADC group injected conversion trigger:
  *         independent or from ADC group regular.
  * @rmtoll CFGR     JAUTO          LL_ADC_INJ_GetTrigAuto
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_INDEPENDENT
  *         @arg @ref LL_ADC_INJ_TRIG_FROM_GRP_REGULAR
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTrigAuto(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR1, ADC_CFGR1_JAUTO));
}

/**
  * @brief  Set one context on ADC group injected that will be checked in
  *         contexts queue.
  * @note   A context is a setting of group injected sequencer:
  *         - group injected trigger
  *         - sequencer length
  *         - sequencer ranks
  *         This function is intended to be used when contexts queue is enabled,
  *         because the sequence must be fully configured in one time
  *         (functions to set separately injected trigger and sequencer channels
  *         cannot be used):
  * @note   In the contexts queue, only the active context can be read.
  *         The parameters of this function can be read using functions:
  *         @arg @ref LL_ADC_INJ_GetTriggerSource()
  *         @arg @ref LL_ADC_INJ_GetTriggerEdge()
  *         @arg @ref LL_ADC_INJ_GetSequencerRanks()
  * @note   On this STM32 series, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On STM32U5, some fast channels are available: fast analog inputs
  *         coming from GPIO pads (ADC_IN0..5).
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JEXTSEL        LL_ADC_INJ_ConfigQueueContext
  *         JSQR     JEXTEN         LL_ADC_INJ_ConfigQueueContext
  *         JSQR     JL             LL_ADC_INJ_ConfigQueueContext
  *         JSQR     JSQ1           LL_ADC_INJ_ConfigQueueContext
  *         JSQR     JSQ2           LL_ADC_INJ_ConfigQueueContext
  *         JSQR     JSQ3           LL_ADC_INJ_ConfigQueueContext
  *         JSQR     JSQ4           LL_ADC_INJ_ConfigQueueContext
  * @param  ADCx ADC instance
  * @param  TriggerSource This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_SOFTWARE
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_CH4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM2_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM2_CH1
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CH4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM4_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_EXTI_LINE15
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_CH4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CH3
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CH1
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM6_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM15_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_LPTIM1_CH2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_LPTIM2_CH2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_LPTIM3_CH1
  * @param  ExternalTriggerEdge This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISINGFALLING
  *
  *         Note: This parameter is discarded in case of SW start:
  *               parameter "TriggerSource" set to "LL_ADC_INJ_TRIG_SOFTWARE".
  * @param  SequencerNbRanks This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS
  * @param  Rank1_Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4 (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  * @param  Rank2_Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4  (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4        (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  * @param  Rank3_Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4  (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4        (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  * @param  Rank4_Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4  (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4        (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_ConfigQueueContext(ADC_TypeDef *ADCx,
                                                   uint32_t TriggerSource,
                                                   uint32_t ExternalTriggerEdge,
                                                   uint32_t SequencerNbRanks,
                                                   uint32_t Rank1_Channel,
                                                   uint32_t Rank2_Channel,
                                                   uint32_t Rank3_Channel,
                                                   uint32_t Rank4_Channel)
{
  /* Set bits with content of parameter "Rankx_Channel" with bits position    */
  /* in register depending on literal "LL_ADC_INJ_RANK_x".                    */
  /* Parameters "Rankx_Channel" and "LL_ADC_INJ_RANK_x" are used with masks   */
  /* because containing other bits reserved for other purpose.                */
  /* If parameter "TriggerSource" is set to SW start, then parameter          */
  /* "ExternalTriggerEdge" is discarded.                                      */
  /* "TriggerSource" is define dwith default edge (rising):                   */
  /* So we need to discard the default edge else the edge will not as expected*/
  uint32_t is_trigger_not_sw = (uint32_t)((TriggerSource != LL_ADC_INJ_TRIG_SOFTWARE) ? 1UL : 0UL);
  MODIFY_REG(ADCx->JSQR,
             ADC_JSQR_JEXTSEL |
             ADC_JSQR_JEXTEN  |
             ADC_JSQR_JSQ4    |
             ADC_JSQR_JSQ3    |
             ADC_JSQR_JSQ2    |
             ADC_JSQR_JSQ1    |
             ADC_JSQR_JL,
             (TriggerSource & ADC_JSQR_JEXTSEL)       |
             (ExternalTriggerEdge * (is_trigger_not_sw)) |
             (((Rank4_Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)     \
              << (LL_ADC_INJ_RANK_4 & ADC_INJ_RANK_ID_JSQR_MASK)) |
             (((Rank3_Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)     \
              << (LL_ADC_INJ_RANK_3 & ADC_INJ_RANK_ID_JSQR_MASK)) |
             (((Rank2_Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)     \
              << (LL_ADC_INJ_RANK_2 & ADC_INJ_RANK_ID_JSQR_MASK)) |
             (((Rank1_Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)     \
              << (LL_ADC_INJ_RANK_1 & ADC_INJ_RANK_ID_JSQR_MASK)) |
             SequencerNbRanks
            );
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_Channels Configuration of ADC hierarchical scope: channels
  * @{
  */

/**
  * @brief  Set sampling time of the selected ADC channel
  *         Unit: ADC clock cycles.
  * @note   On this device, sampling time is on channel scope: independently
  *         of channel mapped on ADC group regular or injected.
  * @note   In case of internal channel (VrefInt, TempSensor, ...) to be
  *         converted:
  *         sampling time constraints must be respected (sampling time can be
  *         adjusted in function of ADC clock frequency and sampling time
  *         setting).
  *         Refer to device datasheet for timings values (parameters TS_vrefint,
  *         TS_temp, ...).
  * @note   Conversion time is the addition of sampling time and processing time.
  *         On this STM32 series, ADC processing time is:
  *         - 12.5 ADC clock cycles at ADC resolution 12 bits
  *         - 10.5 ADC clock cycles at ADC resolution 10 bits
  *         - 8.5 ADC clock cycles at ADC resolution 8 bits
  *         - 6.5 ADC clock cycles at ADC resolution 6 bits
  * @note   In case of ADC conversion of internal channel (VrefInt,
  *         temperature sensor, ...), a sampling time minimum value
  *         is required.
  *         Refer to device datasheet.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll SMPR1    SMP0           LL_ADC_SetChannelSamplingTime
  *         SMPR1    SMP1           LL_ADC_SetChannelSamplingTime
  *         SMPR1    SMP2           LL_ADC_SetChannelSamplingTime
  *         SMPR1    SMP3           LL_ADC_SetChannelSamplingTime
  *         SMPR1    SMP4           LL_ADC_SetChannelSamplingTime
  *         SMPR1    SMP5           LL_ADC_SetChannelSamplingTime
  *         SMPR1    SMP6           LL_ADC_SetChannelSamplingTime
  *         SMPR1    SMP7           LL_ADC_SetChannelSamplingTime
  *         SMPR1    SMP8           LL_ADC_SetChannelSamplingTime
  *         SMPR1    SMP9           LL_ADC_SetChannelSamplingTime
  *         SMPR2    SMP10          LL_ADC_SetChannelSamplingTime
  *         SMPR2    SMP11          LL_ADC_SetChannelSamplingTime
  *         SMPR2    SMP12          LL_ADC_SetChannelSamplingTime
  *         SMPR2    SMP13          LL_ADC_SetChannelSamplingTime
  *         SMPR2    SMP14          LL_ADC_SetChannelSamplingTime
  *         SMPR2    SMP15          LL_ADC_SetChannelSamplingTime
  *         SMPR2    SMP16          LL_ADC_SetChannelSamplingTime
  *         SMPR2    SMP17          LL_ADC_SetChannelSamplingTime
  *         SMPR2    SMP18          LL_ADC_SetChannelSamplingTime
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4  (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4        (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  * @param  SamplingTime This parameter can be one of the following values, In case of ADC1 instance:
  *         @arg @ref LL_ADC_SAMPLINGTIME_5CYCLE
  *         @arg @ref LL_ADC_SAMPLINGTIME_6CYCLES
  *         @arg @ref LL_ADC_SAMPLINGTIME_12CYCLES
  *         @arg @ref LL_ADC_SAMPLINGTIME_20CYCLES
  *         @arg @ref LL_ADC_SAMPLINGTIME_36CYCLES
  *         @arg @ref LL_ADC_SAMPLINGTIME_68CYCLES
  *         @arg @ref LL_ADC_SAMPLINGTIME_391CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_814CYCLES
  * @param  SamplingTime This parameter can be one of the following values, In case of ADC4 instance:
  *         @arg @ref LL_ADC_SAMPLINGTIME_COMMON_1
  *         @arg @ref LL_ADC_SAMPLINGTIME_COMMON_2
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSamplingTime(ADC_TypeDef *ADCx, uint32_t Channel, uint32_t SamplingTime)
{
  if (ADCx != ADC4) /* ADC1 or ADC2 */
  {
    /* Set bits with content of parameter "SamplingTime" with bits position     */
    /* in register and register position depending on parameter "Channel".      */
    /* Parameter "Channel" is used with masks because containing                */
    /* other bits reserved for other purpose.                                   */
    uint32_t shift_value = ((__LL_ADC_CHANNEL_TO_DECIMAL_NB(Channel) - (10UL * ((Channel                             \
                                                                                 & ADC_CHANNEL_SMPRX_REGOFFSET_MASK) \
                                                                                >> ADC_SMPRX_REGOFFSET_POS))) * 3UL);
    __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SMPR1, ((Channel & ADC_CHANNEL_SMPRX_REGOFFSET_MASK)            \
                                                             >> ADC_SMPRX_REGOFFSET_POS));

    MODIFY_REG(*preg, ADC_SMPR1_SMP0 << shift_value, SamplingTime   << shift_value);

  }
  else
  {
    /* Parameter "Channel" is used with masks because containing                  */
    /* other bits reserved for other purpose. It needs to be converted to decimal */
    /* to select the bit position */
    MODIFY_REG(ADCx->SMPR1,
               ADC4_SAMPLING_TIME_CH_MASK,
               ((1UL << __LL_ADC_CHANNEL_TO_DECIMAL_NB(Channel)) << ADC4_SMPR_SMPSEL0_BITOFFSET_POS)                  \
               & (SamplingTime & ADC4_SAMPLING_TIME_CH_MASK)
              );
  }
}

/**
  * @brief  Get sampling time of the selected ADC channel
  *         Unit: ADC clock cycles.
  * @note   On this device, sampling time is on channel scope: independently
  *         of channel mapped on ADC group regular or injected.
  * @note   Conversion time is the addition of sampling time and processing time.
  *         On this STM32 series, ADC processing time is:
  *         - 12.5 ADC clock cycles at ADC resolution 12 bits
  *         - 10.5 ADC clock cycles at ADC resolution 10 bits
  *         - 8.5 ADC clock cycles at ADC resolution 8 bits
  *         - 6.5 ADC clock cycles at ADC resolution 6 bits
  * @rmtoll SMPR1    SMP0           LL_ADC_GetChannelSamplingTime
  *         SMPR1    SMP1           LL_ADC_GetChannelSamplingTime
  *         SMPR1    SMP2           LL_ADC_GetChannelSamplingTime
  *         SMPR1    SMP3           LL_ADC_GetChannelSamplingTime
  *         SMPR1    SMP4           LL_ADC_GetChannelSamplingTime
  *         SMPR1    SMP5           LL_ADC_GetChannelSamplingTime
  *         SMPR1    SMP6           LL_ADC_GetChannelSamplingTime
  *         SMPR1    SMP7           LL_ADC_GetChannelSamplingTime
  *         SMPR1    SMP8           LL_ADC_GetChannelSamplingTime
  *         SMPR1    SMP9           LL_ADC_GetChannelSamplingTime
  *         SMPR2    SMP10          LL_ADC_GetChannelSamplingTime
  *         SMPR2    SMP11          LL_ADC_GetChannelSamplingTime
  *         SMPR2    SMP12          LL_ADC_GetChannelSamplingTime
  *         SMPR2    SMP13          LL_ADC_GetChannelSamplingTime
  *         SMPR2    SMP14          LL_ADC_GetChannelSamplingTime
  *         SMPR2    SMP15          LL_ADC_GetChannelSamplingTime
  *         SMPR2    SMP16          LL_ADC_GetChannelSamplingTime
  *         SMPR2    SMP17          LL_ADC_GetChannelSamplingTime
  *         SMPR2    SMP18          LL_ADC_GetChannelSamplingTime
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0           (3)
  *         @arg @ref LL_ADC_CHANNEL_1           (3)
  *         @arg @ref LL_ADC_CHANNEL_2           (3)
  *         @arg @ref LL_ADC_CHANNEL_3           (3)
  *         @arg @ref LL_ADC_CHANNEL_4           (3)
  *         @arg @ref LL_ADC_CHANNEL_5           (3)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (1)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (1)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC4 (2)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR_ADC4  (2)
  *         @arg @ref LL_ADC_CHANNEL_VBAT_ADC4        (2)
  *
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  *         (3) On STM32U5, fast channel (0.125 us for 14-bit resolution (ADC conversion rate up to 8 Ms/s)).
  *             Other channels are slow channels (conversion rate: refer to reference manual).
  * @retval In case of ADC1 insatnace, Returned value can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLINGTIME_5CYCLE
  *         @arg @ref LL_ADC_SAMPLINGTIME_6CYCLES
  *         @arg @ref LL_ADC_SAMPLINGTIME_12CYCLES
  *         @arg @ref LL_ADC_SAMPLINGTIME_20CYCLES
  *         @arg @ref LL_ADC_SAMPLINGTIME_36CYCLES
  *         @arg @ref LL_ADC_SAMPLINGTIME_68CYCLES
  *         @arg @ref LL_ADC_SAMPLINGTIME_391CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_814CYCLES
  * @retval In case of ADC4 insatnce, Returned value can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLINGTIME_COMMON_1
  *         @arg @ref LL_ADC_SAMPLINGTIME_COMMON_2
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSamplingTime(ADC_TypeDef *ADCx, uint32_t Channel)
{
  if (ADCx != ADC4) /* (ADCx == ADC1) || (ADCx == ADC2) */
  {
    uint32_t shift_value = ((__LL_ADC_CHANNEL_TO_DECIMAL_NB(Channel) - (10UL * ((Channel                              \
                                                                                 & ADC_CHANNEL_SMPRX_REGOFFSET_MASK)  \
                                                                                >> ADC_SMPRX_REGOFFSET_POS))) * 3UL);
    const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SMPR1, ((Channel & ADC_CHANNEL_SMPRX_REGOFFSET_MASK)       \
                                                                   >> ADC_SMPRX_REGOFFSET_POS));

    return (uint32_t)(READ_BIT(*preg, ADC_SMPR1_SMP0 << shift_value) >> shift_value);
  }
  else  /* ADCx == ADC4 */
  {
    uint32_t smpr = READ_REG(ADCx->SMPR1);

    /* Retrieve sampling time bit corresponding to the selected channel            */
    /* and shift it to position 0.                                                 */
    uint32_t smp_channel_posbit0 = ((smpr & ADC4_SAMPLING_TIME_CH_MASK)
                                    >> ((((Channel & ADC_CHANNEL_ID_NUMBER_MASK)        \
                                          >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS)       \
                                         + ADC4_SMPR_SMPSEL0_BITOFFSET_POS)
                                        & 0x1FUL));

    /* Select sampling time bitfield depending on sampling time bit value 0 or 1.  */
    return ((~(smp_channel_posbit0) * LL_ADC_SAMPLINGTIME_COMMON_1)
            | (smp_channel_posbit0 * LL_ADC_SAMPLINGTIME_COMMON_2));
  }
}

/**
  * @brief  Set mode single-ended or differential input of the selected
  *         ADC channel.
  * @note   Channel ending is on channel scope: independently of channel mapped
  *         on ADC group regular or injected.
  *         In differential mode: Differential measurement is carried out
  *         between the selected channel 'i' (positive input) and
  *         channel 'i+1' (negative input). Only channel 'i' has to be
  *         configured, channel 'i+1' is configured automatically.
  * @note   Refer to Reference Manual to ensure the selected channel is
  *         available in differential mode.
  *         For example, internal channels (VrefInt, TempSensor, ...) are
  *         not available in differential mode.
  * @note   When configuring a channel 'i' in differential mode,
  *         the channel 'i+1' is not usable separately.
  * @note   On STM32U5, some channels are internally fixed to single-ended inputs
  *         configuration:
  *         - ADC1: Channels 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 and 17
  *         - ADC2: Channels 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 and 17
  *         - ADC4: None
  * @note   For ADC channels configured in differential mode, both inputs
  *         should be biased at (Vref+)/2 +/-200mV.
  *         (Vref+ is the analog voltage reference)
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_CHANNEL_4 | LL_ADC_CHANNEL_12 | ...)
  * @rmtoll DIFSEL   DIFSEL         LL_ADC_SetChannelSingleDiff
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  * @param  SingleDiff This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_SINGLE_ENDED
  *         @arg @ref LL_ADC_DIFFERENTIAL_ENDED
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSingleDiff(ADC_TypeDef *ADCx, uint32_t Channel, uint32_t SingleDiff)
{
  /* Bits of channels in single or differential mode are set only for         */
  /* differential mode (for single mode, mask of bits allowed to be set is    */
  /* shifted out of range of bits of channels in single or differential mode. */
  MODIFY_REG(ADCx->DIFSEL,
             Channel & ADC_SINGLEDIFF_CHANNEL_MASK,
             (Channel & ADC_SINGLEDIFF_CHANNEL_MASK) & (ADC_DIFSEL_DIFSEL >> (SingleDiff                              \
                                                                              & ADC_SINGLEDIFF_CHANNEL_SHIFT_MASK)));
}

/**
  * @brief  Get mode single-ended or differential input of the selected
  *         ADC channel.
  * @note   When configuring a channel 'i' in differential mode,
  *         the channel 'i+1' is not usable separately.
  *         Therefore, to ensure a channel is configured in single-ended mode,
  *         the configuration of channel itself and the channel 'i-1' must be
  *         read back (to ensure that the selected channel channel has not been
  *         configured in differential mode by the previous channel).
  * @note   Refer to Reference Manual to ensure the selected channel is
  *         available in differential mode.
  *         For example, internal channels (VrefInt, TempSensor, ...) are
  *         not available in differential mode.
  * @note   When configuring a channel 'i' in differential mode,
  *         the channel 'i+1' is not usable separately.
  * @note   On STM32U5, some channels are internally fixed to single-ended inputs
  *         configuration:
  *         - ADC1: Channels 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 and 17
  *         - ADC2: Channels 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 and 17
  *         - ADC4: None
  * @note   One or several values can be selected. In this case, the value
  *         returned is null if all channels are in single ended-mode.
  *         Example: (LL_ADC_CHANNEL_4 | LL_ADC_CHANNEL_12 | ...)
  * @rmtoll DIFSEL   DIFSEL         LL_ADC_GetChannelSingleDiff
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_19
  * @retval 0: channel in single-ended mode, else: channel in differential mode
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSingleDiff(ADC_TypeDef *ADCx, uint32_t Channel)
{
  return (uint32_t)(READ_BIT(ADCx->DIFSEL, (Channel & ADC_SINGLEDIFF_CHANNEL_MASK)));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_AnalogWatchdog Configuration of ADC transversal scope: analog watchdog
  * @{
  */

/**
  * @brief  Set ADC analog watchdog monitored channels:
  *         a single channel, multiple channels or all channels,
  *         on ADC groups regular and-or injected.
  * @note   Once monitored channels are selected, analog watchdog
  *         is enabled.
  * @note   In case of need to define a single channel to monitor
  *         with analog watchdog from sequencer channel definition,
  *         use helper macro @ref __LL_ADC_ANALOGWD_CHANNEL_GROUP().
  * @note   On this STM32 series, there are 2 kinds of analog watchdog
  *         instance:
  *         - AWD standard (instance AWD1):
  *           - channels monitored: can monitor 1 channel or all channels.
  *           - groups monitored: ADC groups regular and-or injected.
  *           - resolution: resolution is not limited (corresponds to
  *             ADC resolution configured).
  *         - AWD flexible (instances AWD2, AWD3):
  *           - channels monitored: flexible on channels monitored, selection is
  *             channel wise, from from 1 to all channels.
  *             Specificity of this analog watchdog: Multiple channels can
  *             be selected. For example:
  *             (LL_ADC_AWD_CHANNEL4_REG_INJ | LL_ADC_AWD_CHANNEL5_REG_INJ | ...)
  *           - groups monitored: not selection possible (monitoring on both
  *             groups regular and injected).
  *             Channels selected are monitored on groups regular and injected:
  *             LL_ADC_AWD_CHANNELxx_REG_INJ (do not use parameters
  *             LL_ADC_AWD_CHANNELxx_REG and LL_ADC_AWD_CHANNELxx_INJ)
  *           - resolution: resolution is limited to 8 bits: if ADC resolution is
  *             12 bits the 4 LSB are ignored, if ADC resolution is 10 bits
  *             the 2 LSB are ignored.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     AWD1CH         LL_ADC_SetAnalogWDMonitChannels
  *         CFGR     AWD1SGL        LL_ADC_SetAnalogWDMonitChannels
  *         CFGR     AWD1EN         LL_ADC_SetAnalogWDMonitChannels
  *         CFGR     JAWD1EN        LL_ADC_SetAnalogWDMonitChannels
  *         AWD2CR   AWD2CH         LL_ADC_SetAnalogWDMonitChannels
  *         AWD3CR   AWD3CH         LL_ADC_SetAnalogWDMonitChannels
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  *         @arg @ref LL_ADC_AWD2
  *         @arg @ref LL_ADC_AWD3
  * @param  AWDChannelGroup This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_DISABLE
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG        (0)
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_INJ        (0)
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_19_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_19_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_19_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG          (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_INJ          (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG_INJ         (1)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG       (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_INJ       (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG_INJ      (1)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_REG             (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_INJ             (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_REG_INJ            (1)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC4_REG     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC4_REG     (0)(2)
  *
  *         (0) On STM32U5, parameter available only on analog watchdog number: AWD1.
  *         (1) On STM32U5, parameter available only on ADC instance: ADC1/2.
  *         (2) On STM32U5, parameter available only on ADC instance: ADC4.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDMonitChannels(ADC_TypeDef *ADCx, uint32_t AWDy, uint32_t AWDChannelGroup)
{
  /* Set bits with content of parameter "AWDChannelGroup" with bits position  */
  /* in register and register position depending on parameter "AWDy".         */
  /* Parameters "AWDChannelGroup" and "AWDy" are used with masks because      */
  /* containing other bits reserved for other purpose.                        */

  __IO uint32_t *preg;
  uint32_t channel_monitored;

  if (AWDy == LL_ADC_AWD1)
  {
    /* Set pointer to register of selected analog watchdog */
    preg = __ADC_PTR_REG_OFFSET(ADCx->CFGR1, 0UL);

    /* Compute channel monitored as number */
    channel_monitored = (AWDChannelGroup & ADC_AWD_CR1_CHANNEL_MASK);
  }
  else
  {
    /* Set pointer to register of selected analog watchdog */
    preg = __ADC_PTR_REG_OFFSET(ADCx->AWD2CR, ((AWDy & ADC_AWD_CR3_REGOFFSET)) >> (ADC_AWD_CRX_REGOFFSET_POS + 1UL));

    /* Compute channel monitored as bitfield */
    channel_monitored = (1UL << ((AWDChannelGroup & ADC_CHANNEL_ID_NUMBER_MASK)                                       \
                                 >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS));
    /* Case of all channels monitored */
    channel_monitored |= ((1UL - ((AWDChannelGroup & ADC_CFGR1_AWD1SGL) >> ADC_CFGR1_AWD1SGL_Pos)) * 0x00FFFFFFUL);
    /* Case of no channel monitored */
    channel_monitored *= ((((AWDChannelGroup & (ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN)) == 0UL) ? 0UL : 1UL));
  }

  MODIFY_REG(*preg, (AWDy & ADC_AWD_CR_ALL_CHANNEL_MASK), channel_monitored);
}

/**
  * @brief  Get ADC analog watchdog monitored channel.
  * @note   Usage of the returned channel number:
  *         - To reinject this channel into another function LL_ADC_xxx:
  *           the returned channel number is only partly formatted on definition
  *           of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *           with parts of literals LL_ADC_CHANNEL_x or using
  *           helper macro @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  *           Then the selected literal LL_ADC_CHANNEL_x can be used
  *           as parameter for another function.
  *         - To get the channel number in decimal format:
  *           process the returned value with the helper macro
  *           @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  *           Applicable only when the analog watchdog is set to monitor
  *           one channel.
  * @note   On this STM32 series, there are 2 kinds of analog watchdog
  *         instance:
  *         - AWD standard (instance AWD1):
  *           - channels monitored: can monitor 1 channel or all channels.
  *           - groups monitored: ADC groups regular and-or injected.
  *           - resolution: resolution is not limited (corresponds to
  *             ADC resolution configured).
  *         - AWD flexible (instances AWD2, AWD3):
  *           - channels monitored: flexible on channels monitored, selection is
  *             channel wise, from from 1 to all channels.
  *             Specificity of this analog watchdog: Multiple channels can
  *             be selected. For example:
  *             (LL_ADC_AWD_CHANNEL4_REG_INJ | LL_ADC_AWD_CHANNEL5_REG_INJ | ...)
  *           - groups monitored: not selection possible (monitoring on both
  *             groups regular and injected).
  *             Channels selected are monitored on groups regular and injected:
  *             LL_ADC_AWD_CHANNELxx_REG_INJ (do not use parameters
  *             LL_ADC_AWD_CHANNELxx_REG and LL_ADC_AWD_CHANNELxx_INJ)
  *           - resolution: resolution is limited to 8 bits: if ADC resolution is
  *             12 bits the 4 LSB are ignored, if ADC resolution is 10 bits
  *             the 2 LSB are ignored.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     AWD1CH         LL_ADC_GetAnalogWDMonitChannels
  *         CFGR     AWD1SGL        LL_ADC_GetAnalogWDMonitChannels
  *         CFGR     AWD1EN         LL_ADC_GetAnalogWDMonitChannels
  *         CFGR     JAWD1EN        LL_ADC_GetAnalogWDMonitChannels
  *         AWD2CR   AWD2CH         LL_ADC_GetAnalogWDMonitChannels
  *         AWD3CR   AWD3CH         LL_ADC_GetAnalogWDMonitChannels
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  *         @arg @ref LL_ADC_AWD2 (1)
  *         @arg @ref LL_ADC_AWD3 (1)
  *
  *         (1) On this AWD number, monitored channel can be retrieved
  *             if only 1 channel is programmed (or none or all channels).
  *             This function cannot retrieve monitored channel if
  *             multiple channels are programmed simultaneously
  *             by bitfield.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_AWD_DISABLE
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG        (0)
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_INJ        (0)
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_19_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_19_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_19_REG_INJ
  *
  *         (0) On STM32U5, parameter available only on analog watchdog number: AWD1.
  */
__STATIC_INLINE uint32_t LL_ADC_GetAnalogWDMonitChannels(ADC_TypeDef *ADCx, uint32_t AWDy)
{
  const __IO uint32_t *preg;

  if (AWDy == LL_ADC_AWD1)
  {
    /* Set pointer to register of selected analog watchdog */
    preg = __ADC_PTR_REG_OFFSET(ADCx->CFGR1, 0UL);
  }
  else
  {
    /* Set pointer to register of selected analog watchdog */
    preg = __ADC_PTR_REG_OFFSET(ADCx->AWD2CR, ((AWDy & ADC_AWD_CRX_REGOFFSET_MASK))                                   \
                                >> (ADC_AWD_CRX_REGOFFSET_POS + 1UL));
  }

  uint32_t analog_wd_monit_channels = (READ_BIT(*preg, AWDy) & AWDy & ADC_AWD_CR_ALL_CHANNEL_MASK);

  /* If "analog_wd_monit_channels" == 0, then the selected AWD is disabled       */
  /* (parameter value LL_ADC_AWD_DISABLE).                                    */
  /* Else, the selected AWD is enabled and is monitoring a group of channels  */
  /* or a single channel.                                                     */
  if (analog_wd_monit_channels != 0UL)
  {
    if (AWDy == LL_ADC_AWD1)
    {
      if ((analog_wd_monit_channels & ADC_CFGR1_AWD1SGL) == 0UL)
      {
        /* AWD monitoring a group of channels */
        analog_wd_monit_channels = ((analog_wd_monit_channels | (0x000FFFFFUL)) & (~(ADC_CFGR1_AWD1CH)));
      }
      else
      {
        /* AWD monitoring a single channel */
        analog_wd_monit_channels = analog_wd_monit_channels;
      }
    }
    else
    {
      if (ADCx == ADC1)
      {
        if ((analog_wd_monit_channels & 0x000FFFFFUL) == 0x000FFFFFUL)
        {
          /* AWD monitoring a group of channels */
          analog_wd_monit_channels = (0x000FFFFFUL | ((ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN)));
        }
        else
        {
          /* AWD monitoring a single channel */
          /* AWD monitoring a group of channels */
          analog_wd_monit_channels = ((ADC_CFGR1_JAWD1EN | ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)
                                      | (__LL_ADC_CHANNEL_TO_DECIMAL_NB(analog_wd_monit_channels) \
                                         << ADC_CFGR1_AWD1CH_Pos));
        }
      }
      else
      {
        if ((analog_wd_monit_channels & ADC_AWD_CR23_CHANNEL_MASK) == ADC_AWD_CR23_CHANNEL_MASK)
        {
          /* AWD monitoring a group of channels */
          analog_wd_monit_channels = (0x000FFFFFUL | (ADC_CFGR1_AWD1EN));
        }
        else
        {
          /* AWD monitoring a single channel */
          /* AWD monitoring a group of channels */
          analog_wd_monit_channels = ((ADC_CFGR1_AWD1EN | ADC_CFGR1_AWD1SGL)
                                      | (__LL_ADC_CHANNEL_TO_DECIMAL_NB(analog_wd_monit_channels) \
                                         << ADC_CFGR1_AWD1CH_Pos));
        }
      }
    }
  }

  return analog_wd_monit_channels;
}

/**
  * @brief  Set ADC analog watchdog threshold value of threshold
  *         high or low.
  * @note   In case of ADC resolution different of 12 bits,
  *         analog watchdog thresholds data require a specific shift.
  *         Use helper macro @ref __LL_ADC_ANALOGWD_SET_THRESHOLD_RESOLUTION().
  * @note   On this STM32 series, there are 2 kinds of analog watchdog
  *         instance:
  *         - AWD standard (instance AWD1):
  *           - channels monitored: can monitor 1 channel or all channels.
  *           - groups monitored: ADC groups regular and-or injected.
  *           - resolution: resolution is not limited (corresponds to
  *             ADC resolution configured).
  *         - AWD flexible (instances AWD2, AWD3):
  *           - channels monitored: flexible on channels monitored, selection is
  *             channel wise, from from 1 to all channels.
  *             Specificity of this analog watchdog: Multiple channels can
  *             be selected. For example:
  *             (LL_ADC_AWD_CHANNEL4_REG_INJ | LL_ADC_AWD_CHANNEL5_REG_INJ | ...)
  *           - groups monitored: not selection possible (monitoring on both
  *             groups regular and injected).
  *             Channels selected are monitored on groups regular and injected:
  *             LL_ADC_AWD_CHANNELxx_REG_INJ (do not use parameters
  *             LL_ADC_AWD_CHANNELxx_REG and LL_ADC_AWD_CHANNELxx_INJ)
  *           - resolution: resolution is limited to 8 bits: if ADC resolution is
  *             12 bits the 4 LSB are ignored, if ADC resolution is 10 bits
  *             the 2 LSB are ignored.
  * @note   If ADC oversampling is enabled, ADC analog watchdog thresholds are
  *         impacted: the comparison of analog watchdog thresholds is done
  *         on oversampling intermediate computation (after ratio, before shift
  *         application): intermediate register bitfield [32:7]
  *         (26 most significant bits).
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either ADC groups regular or injected.
  * @rmtoll TR1      HT1            LL_ADC_SetAnalogWDThresholds
  *         TR2      HT2            LL_ADC_SetAnalogWDThresholds
  *         TR3      HT3            LL_ADC_SetAnalogWDThresholds
  *         TR1      LT1            LL_ADC_SetAnalogWDThresholds
  *         TR2      LT2            LL_ADC_SetAnalogWDThresholds
  *         TR3      LT3            LL_ADC_SetAnalogWDThresholds
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  *         @arg @ref LL_ADC_AWD2
  *         @arg @ref LL_ADC_AWD3
  * @param  AWDThresholdsHighLow This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_THRESHOLD_HIGH
  *         @arg @ref LL_ADC_AWD_THRESHOLD_LOW
  * @param  AWDThresholdValue Value between Min_Data=0x000 and Max_Data=0xFFF
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDThresholds(ADC_TypeDef *ADCx, uint32_t AWDy, uint32_t AWDThresholdsHighLow,
                                                  uint32_t AWDThresholdValue)
{
  __IO uint32_t *preg;
  /* Set bits with content of parameter "AWDThresholdValue" with bits         */
  /* position in register and register position depending on parameters       */
  /* "AWDThresholdsHighLow" and "AWDy".                                       */
  /* Parameters "AWDy" and "AWDThresholdValue" are used with masks because    */
  /* containing other bits reserved for other purpose.                        */
  if (ADCx == ADC1)
  {
    if (AWDy == LL_ADC_AWD1)
    {
      preg = __ADC_PTR_REG_OFFSET(ADCx->LTR1, (AWDThresholdsHighLow));
    }
    else
    {
      preg = __ADC_PTR_REG_OFFSET(ADCx->LTR1, (((AWDy & ADC_AWD_TRX_REGOFFSET_MASK)                                   \
                                                >> ADC_AWD_TRX_REGOFFSET_POS) * 2UL)
                                  + (AWDThresholdsHighLow));
    }

    MODIFY_REG(*preg, ADC_LTR_LT, AWDThresholdValue);
  }
  else  /* ADCx == ADC4 */
  {
    if (AWDy == LL_ADC_AWD1)
    {
      preg = __ADC_PTR_REG_OFFSET(ADCx->AWD1TR, 0UL);
    }
    else
    {
      preg = __ADC_PTR_REG_OFFSET(ADCx->AWD1TR, (((AWDy & ADC_AWD_TRX_REGOFFSET_MASK)) >> (ADC_AWD_TRX_REGOFFSET_POS))\
                                  + ((ADC_AWD_CR3_REGOFFSET & AWDy) >> (ADC_AWD_CRX_REGOFFSET_POS + 1UL)));
    }

    MODIFY_REG(*preg,
               ADC_AWD1TR_LT1 << (AWDThresholdsHighLow * ADC_AWD1TR_HT1_Pos),
               AWDThresholdValue << (((AWDThresholdsHighLow << ADC_AWD1TR_HT1_Pos) & ADC_AWD_TRX_BIT_HIGH_MASK)        \
                                     >> ADC_AWD_TRX_BIT_HIGH_SHIFT4));

  }
}

/**
  * @brief  Get ADC analog watchdog threshold value of threshold high,
  *         threshold low or raw data with ADC thresholds high and low
  *         concatenated.
  * @note   In case of ADC resolution different of 12 bits,
  *         analog watchdog thresholds data require a specific shift.
  *         Use helper macro @ref __LL_ADC_ANALOGWD_GET_THRESHOLD_RESOLUTION().
  * @rmtoll TR1      HT1            LL_ADC_GetAnalogWDThresholds
  *         TR2      HT2            LL_ADC_GetAnalogWDThresholds
  *         TR3      HT3            LL_ADC_GetAnalogWDThresholds
  *         TR1      LT1            LL_ADC_GetAnalogWDThresholds
  *         TR2      LT2            LL_ADC_GetAnalogWDThresholds
  *         TR3      LT3            LL_ADC_GetAnalogWDThresholds
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  *         @arg @ref LL_ADC_AWD2
  *         @arg @ref LL_ADC_AWD3
  * @param  AWDThresholdsHighLow This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_THRESHOLD_HIGH
  *         @arg @ref LL_ADC_AWD_THRESHOLD_LOW
  * @retval In case of ADC1 instance, Value between Min_Data=0x000 and Max_Data=0x1FFFFFF
  * @retval In case of ADC1 instance, Value between Min_Data=0x000 and Max_Data=0xFFF
  */
__STATIC_INLINE uint32_t LL_ADC_GetAnalogWDThresholds(ADC_TypeDef *ADCx, uint32_t AWDy, uint32_t AWDThresholdsHighLow)
{
  const __IO uint32_t *preg;
  if (ADCx == ADC1)
  {
    if (AWDy == LL_ADC_AWD1)
    {
      preg = __ADC_PTR_REG_OFFSET(ADCx->LTR1, (AWDThresholdsHighLow));
    }
    else
    {
      preg = __ADC_PTR_REG_OFFSET(ADCx->LTR1, (((AWDy & ADC_AWD_TRX_REGOFFSET_MASK) >> ADC_AWD_TRX_REGOFFSET_POS) * 2UL)
                                  + (AWDThresholdsHighLow));
    }

    return (uint32_t)(READ_BIT(*preg, ADC_LTR_LT));
  }
  else
  {
    if (AWDy == LL_ADC_AWD1)
    {
      preg = __ADC_PTR_REG_OFFSET(ADCx->AWD1TR, 0UL);

    }
    else
    {
      preg = __ADC_PTR_REG_OFFSET(ADCx->AWD1TR, (((AWDy & ADC_AWD_TRX_REGOFFSET_MASK)) >> (ADC_AWD_TRX_REGOFFSET_POS))\
                                  + ((ADC_AWD_CR3_REGOFFSET & AWDy) >> (ADC_AWD_CRX_REGOFFSET_POS + 1UL)));
    }

    return (uint32_t)(READ_BIT(*preg,
                               (ADC_AWD1TR_LT1 << (AWDThresholdsHighLow * ADC_AWD1TR_HT1_Pos)))
                      >> (((AWDThresholdsHighLow << ADC_AWD1TR_HT1_Pos) & ADC_AWD_TRX_BIT_HIGH_MASK) \
                          >> ADC_AWD_TRX_BIT_HIGH_SHIFT4)
                     );
  }
}

/**
  * @brief  Set ADC analog watchdog thresholds value of both thresholds
  *         high and low.
  * @note   If value of only one threshold high or low must be set,
  *         use function @ref LL_ADC_SetAnalogWDThresholds().
  * @note   In case of ADC resolution different of 12 bits,
  *         analog watchdog thresholds data require a specific shift.
  *         Use helper macro @ref __LL_ADC_ANALOGWD_SET_THRESHOLD_RESOLUTION().
  * @note   On this STM32 series, there are 2 kinds of analog watchdog
  *         instance:
  *         - AWD standard (instance AWD1):
  *           - channels monitored: can monitor 1 channel or all channels.
  *           - groups monitored: ADC group regular.
  *           - resolution: resolution is not limited (corresponds to
  *             ADC resolution configured).
  *         - AWD flexible (instances AWD2, AWD3):
  *           - channels monitored: flexible on channels monitored, selection is
  *             channel wise, from from 1 to all channels.
  *             Specificity of this analog watchdog: Multiple channels can
  *             be selected. For example:
  *             (LL_ADC_AWD_CHANNEL4_REG_INJ | LL_ADC_AWD_CHANNEL5_REG_INJ | ...)
  *           - groups monitored: not selection possible (monitoring on both
  *             groups regular and injected).
  *             Channels selected are monitored on groups regular and injected:
  *             LL_ADC_AWD_CHANNELxx_REG_INJ (do not use parameters
  *             LL_ADC_AWD_CHANNELxx_REG and LL_ADC_AWD_CHANNELxx_INJ)
  *           - resolution: resolution is not limited (corresponds to
  *             ADC resolution configured).
  * @note   If ADC oversampling is enabled, ADC analog watchdog thresholds are
  *         impacted: the comparison of analog watchdog thresholds is done on
  *         oversampling final computation (after ratio and shift application):
  *         ADC data register bitfield [15:4] (12 most significant bits).
  *         Examples:
  *         - Oversampling ratio and shift selected to have ADC conversion data
  *           on 12 bits (ratio 16 and shift 4, or ratio 32 and shift 5, ...):
  *           ADC analog watchdog thresholds must be divided by 16.
  *         - Oversampling ratio and shift selected to have ADC conversion data
  *           on 14 bits (ratio 16 and shift 2, or ratio 32 and shift 3, ...):
  *           ADC analog watchdog thresholds must be divided by 4.
  *         - Oversampling ratio and shift selected to have ADC conversion data
  *           on 16 bits (ratio 16 and shift none, or ratio 32 and shift 1, ...):
  *           ADC analog watchdog thresholds match directly to ADC data register.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll TR1      HT1            LL_ADC_ConfigAnalogWDThresholds
  *         TR2      HT2            LL_ADC_ConfigAnalogWDThresholds
  *         TR3      HT3            LL_ADC_ConfigAnalogWDThresholds
  *         TR1      LT1            LL_ADC_ConfigAnalogWDThresholds
  *         TR2      LT2            LL_ADC_ConfigAnalogWDThresholds
  *         TR3      LT3            LL_ADC_ConfigAnalogWDThresholds
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  *         @arg @ref LL_ADC_AWD2
  *         @arg @ref LL_ADC_AWD3
  * @param  AWDThresholdHighValue Value between Min_Data=0x000 and Max_Data=0xFFF
  * @param  AWDThresholdLowValue Value between Min_Data=0x000 and Max_Data=0xFFF
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigAnalogWDThresholds(ADC_TypeDef *ADCx, uint32_t AWDy, uint32_t AWDThresholdHighValue,
                                                     uint32_t AWDThresholdLowValue)
{
  __IO uint32_t *preg;
  __IO uint32_t *preg2;
  /* Set bits with content of parameter "AWDThresholdxxxValue" with bits      */
  /* position in register and register position depending on parameter        */
  /* "AWDy".                                                                  */
  /* Parameters "AWDy" and "AWDThresholdxxxValue" are used with masks because */
  /* containing other bits reserved for other purpose.                        */
  if (ADCx != ADC4) /* ADC1 or ADC2 */
  {
    if (AWDy == LL_ADC_AWD1)
    {
      preg = __ADC_PTR_REG_OFFSET(ADCx->LTR1, (LL_ADC_AWD_THRESHOLD_LOW));
      preg2 = __ADC_PTR_REG_OFFSET(ADCx->LTR1, (LL_ADC_AWD_THRESHOLD_HIGH));
    }
    else
    {
      preg = __ADC_PTR_REG_OFFSET(ADCx->LTR1, (((AWDy & ADC_AWD_TRX_REGOFFSET_MASK)                                   \
                                                >> (ADC_AWD_TRX_REGOFFSET_POS - 1UL)))
                                  + (LL_ADC_AWD_THRESHOLD_LOW));
      preg2 = __ADC_PTR_REG_OFFSET(ADCx->LTR1, (((AWDy & ADC_AWD_TRX_REGOFFSET_MASK)                                  \
                                                 >> (ADC_AWD_TRX_REGOFFSET_POS - 1UL)))
                                   + (LL_ADC_AWD_THRESHOLD_HIGH));
    }

    MODIFY_REG(*preg, ADC_LTR_LT, AWDThresholdLowValue);
    MODIFY_REG(*preg2, ADC_HTR_HT, AWDThresholdHighValue);
  }
  else
  {
    if (AWDy == LL_ADC_AWD1)
    {
      preg = __ADC_PTR_REG_OFFSET(ADCx->AWD1TR, 0UL);
    }
    else
    {
      preg = __ADC_PTR_REG_OFFSET(ADCx->AWD1TR, (((AWDy & ADC_AWD_TRX_REGOFFSET_MASK)) >> (ADC_AWD_TRX_REGOFFSET_POS)) \
                                  + ((ADC_AWD_CR3_REGOFFSET & AWDy) >> (ADC_AWD_CRX_REGOFFSET_POS + 1UL)));
    }

    MODIFY_REG(*preg,
               ADC_AWD1TR_HT1 | ADC_AWD1TR_LT1,
               (AWDThresholdHighValue << ADC_TR1_HT1_BITOFFSET_POS) | AWDThresholdLowValue);
  }
}

/**
  * @brief  Set ADC analog watchdog filtering configuration
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  *  @note  On this STM32 series, this feature is only available on first
  *         analog watchdog (AWD1)
  * @rmtoll TR1      AWDFILT        LL_ADC_SetAWDFilteringConfiguration
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  * @param  FilteringConfig This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_FILTERING_NONE
  *         @arg @ref LL_ADC_AWD_FILTERING_2SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_3SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_4SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_5SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_6SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_7SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_8SAMPLES
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetAWDFilteringConfiguration(ADC_TypeDef *ADCx, uint32_t AWDy, uint32_t FilteringConfig)
{
  /* Prevent unused argument(s) compilation warning */
  (void)(AWDy);
  MODIFY_REG(ADCx->HTR1, ADC_HTR_AWDFILT, FilteringConfig);
}

/**
  * @brief  Get ADC analog watchdog filtering configuration
  *  @note  On this STM32 series, this feature is only available on first
  *         analog watchdog (AWD1)
  * @rmtoll TR1      AWDFILT        LL_ADC_GetAWDFilteringConfiguration
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  * @retval Returned value can be:
  *         @arg @ref LL_ADC_AWD_FILTERING_NONE
  *         @arg @ref LL_ADC_AWD_FILTERING_2SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_3SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_4SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_5SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_6SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_7SAMPLES
  *         @arg @ref LL_ADC_AWD_FILTERING_8SAMPLES
  */
__STATIC_INLINE uint32_t LL_ADC_GetAWDFilteringConfiguration(ADC_TypeDef *ADCx, uint32_t AWDy)
{
  /* Prevent unused argument(s) compilation warning */
  (void)(AWDy);
  return (uint32_t)(READ_BIT(ADCx->HTR1, ADC_HTR_AWDFILT));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_oversampling Configuration of ADC transversal scope: oversampling
  * @{
  */

/**
  * @brief  Set ADC oversampling scope: ADC groups regular and-or injected
  *         (availability of ADC group injected depends on STM32 families).
  * @note   If both groups regular and injected are selected,
  *         specify behavior of ADC group injected interrupting
  *         group regular: when ADC group injected is triggered,
  *         the oversampling on ADC group regular is either
  *         temporary stopped and continued, or resumed from start
  *         (oversampler buffer reset).
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR2    ROVSE          LL_ADC_SetOverSamplingScope
  *         CFGR2    JOVSE          LL_ADC_SetOverSamplingScope
  *         CFGR2    ROVSM          LL_ADC_SetOverSamplingScope
  * @param  ADCx ADC instance
  * @param  OvsScope This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_DISABLE
  *         @arg @ref LL_ADC_OVS_GRP_REGULAR_CONTINUED
  *         @arg @ref LL_ADC_OVS_GRP_REGULAR_RESUMED
  *         @arg @ref LL_ADC_OVS_GRP_INJECTED
  *         @arg @ref LL_ADC_OVS_GRP_INJ_REG_RESUMED
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOverSamplingScope(ADC_TypeDef *ADCx, uint32_t OvsScope)
{
  if (ADCx == ADC1)
  {
    MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_ROVSE | ADC_CFGR2_JOVSE | ADC_CFGR2_ROVSM, OvsScope);
  }
  else
  {
    MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_ROVSE, OvsScope);
  }
}

/**
  * @brief  Get ADC oversampling scope: ADC groups regular and-or injected
  *         (availability of ADC group injected depends on STM32 families).
  * @note   If both groups regular and injected are selected,
  *         specify behavior of ADC group injected interrupting
  *         group regular: when ADC group injected is triggered,
  *         the oversampling on ADC group regular is either
  *         temporary stopped and continued, or resumed from start
  *         (oversampler buffer reset).
  * @rmtoll CFGR2    ROVSE          LL_ADC_GetOverSamplingScope
  *         CFGR2    JOVSE          LL_ADC_GetOverSamplingScope
  *         CFGR2    ROVSM          LL_ADC_GetOverSamplingScope
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OVS_DISABLE
  *         @arg @ref LL_ADC_OVS_GRP_REGULAR_CONTINUED
  *         @arg @ref LL_ADC_OVS_GRP_REGULAR_RESUMED
  *         @arg @ref LL_ADC_OVS_GRP_INJECTED
  *         @arg @ref LL_ADC_OVS_GRP_INJ_REG_RESUMED
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingScope(ADC_TypeDef *ADCx)
{
  if (ADCx == ADC1)
  {
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_ROVSE | ADC_CFGR2_JOVSE | ADC_CFGR2_ROVSM));
  }
  else
  {
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_ROVSE));
  }
}

/**
  * @brief  Set ADC oversampling discontinuous mode (triggered mode)
  *         on the selected ADC group.
  * @note   Number of oversampled conversions are done either in:
  *         - continuous mode (all conversions of oversampling ratio
  *           are done from 1 trigger)
  *         - discontinuous mode (each conversion of oversampling ratio
  *           needs a trigger)
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @note   On this STM32 series, oversampling discontinuous mode
  *         (triggered mode) can be used only when oversampling is
  *         set on group regular only and in resumed mode.
  * @rmtoll CFGR2    TROVS          LL_ADC_SetOverSamplingDiscont
  * @param  ADCx ADC instance
  * @param  OverSamplingDiscont This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_REG_CONT
  *         @arg @ref LL_ADC_OVS_REG_DISCONT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOverSamplingDiscont(ADC_TypeDef *ADCx, uint32_t OverSamplingDiscont)
{
  MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_TROVS, OverSamplingDiscont);
}

/**
  * @brief  Get ADC oversampling discontinuous mode (triggered mode)
  *         on the selected ADC group.
  * @note   Number of oversampled conversions are done either in:
  *         - continuous mode (all conversions of oversampling ratio
  *           are done from 1 trigger)
  *         - discontinuous mode (each conversion of oversampling ratio
  *           needs a trigger)
  * @rmtoll CFGR2    TROVS          LL_ADC_GetOverSamplingDiscont
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OVS_REG_CONT
  *         @arg @ref LL_ADC_OVS_REG_DISCONT
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingDiscont(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_TROVS));
}

/**
  * @brief  Set ADC oversampling
  *         (impacting both ADC groups regular and injected)
  * @note   This function set the 2 items of oversampling configuration:
  *         - ratio
  *         - shift
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR2    OVSS           LL_ADC_ConfigOverSamplingRatioShift
  *         CFGR2    OVSR           LL_ADC_ConfigOverSamplingRatioShift
  * @param  ADCx ADC instance
  * @param  Ratio This parameter can be in the range from 1 to 1024 in case of ADC1 instance.
  * @param  Ratio This parameter can be one of the following values, in case of ADC4 :
  *         @arg @ref LL_ADC_OVS_RATIO_2
  *         @arg @ref LL_ADC_OVS_RATIO_4
  *         @arg @ref LL_ADC_OVS_RATIO_8
  *         @arg @ref LL_ADC_OVS_RATIO_16
  *         @arg @ref LL_ADC_OVS_RATIO_32
  *         @arg @ref LL_ADC_OVS_RATIO_64
  *         @arg @ref LL_ADC_OVS_RATIO_128
  *         @arg @ref LL_ADC_OVS_RATIO_256
  * @param  Shift This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_SHIFT_NONE
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_1
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_2
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_3
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_4
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_5
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_6
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_7
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_8
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_9  (1)
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_10 (1)
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_11 (1)
  *
  *        (1): Only for ADC1 instance.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigOverSamplingRatioShift(ADC_TypeDef *ADCx, uint32_t Ratio, uint32_t Shift)
{
  if (ADCx == ADC1)
  {
    MODIFY_REG(ADCx->CFGR2, (ADC_CFGR2_OVSS | ADC_CFGR2_OVSR), (Shift | (((Ratio - 1UL) << ADC_CFGR2_OVSR_Pos))));
  }
  else /* ADCx == ADC4 */
  {
    MODIFY_REG(ADCx->CFGR2, (ADC_CFGR2_OVSS | ADC4_CFGR2_OVSR), (Shift | Ratio));
  }
}

/**
  * @brief  Get ADC oversampling ratio
  *        (impacting both ADC groups regular and injected)
  * @rmtoll CFGR2    OVSR           LL_ADC_GetOverSamplingRatio
  * @param  ADCx ADC instance
  * @retval Ratio This parameter can be in the from 1 to 1024.
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingRatio(ADC_TypeDef *ADCx)
{
  if (ADCx == ADC1)
  {
    return (((uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_OVSR)) + (1UL << ADC_CFGR2_OVSR_Pos)) >> ADC_CFGR2_OVSR_Pos);
  }
  else /* ADCx == ADC4 */
  {
    return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC4_CFGR2_OVSR));
  }
}

/**
  * @brief  Get ADC oversampling shift
  *        (impacting both ADC groups regular and injected)
  * @rmtoll CFGR2    OVSS           LL_ADC_GetOverSamplingShift
  * @param  ADCx ADC instance
  * @retval Shift This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_SHIFT_NONE
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_1
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_2
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_3
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_4
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_5
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_6
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_7
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_8
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_9   (1)
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_10  (1)
  *         @arg @ref LL_ADC_OVS_SHIFT_RIGHT_11  (1)
  *
  *        (1): Only for ADC1 instance.
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingShift(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_OVSS));
}


/**
  * @}
  */
/** @defgroup ADC_LL_EF_Operation_ADC_Instance Operation on ADC hierarchical scope: ADC instance
  * @{
  */

/**
  * @brief  Put ADC instance in deep power down state.
  * @note   In case of ADC calibration necessary: When ADC is in deep-power-down
  *         state, the internal analog calibration is lost. After exiting from
  *         deep power down, calibration must be relaunched or calibration factor
  *         (preliminarily saved) must be set back into calibration register.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @rmtoll CR       DEEPPWD        LL_ADC_EnableDeepPowerDown
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableDeepPowerDown(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR, ADC_CR_BITS_PROPERTY_RS, ADC_CR_DEEPPWD);
}

/**
  * @brief  Disable ADC deep power down mode.
  * @note   In case of ADC calibration necessary: When ADC is in deep-power-down
  *         state, the internal analog calibration is lost. After exiting from
  *         deep power down, calibration must be relaunched or calibration factor
  *         (preliminarily saved) must be set back into calibration register.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @rmtoll CR       DEEPPWD        LL_ADC_DisableDeepPowerDown
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableDeepPowerDown(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  CLEAR_BIT(ADCx->CR, (ADC_CR_DEEPPWD | ADC_CR_BITS_PROPERTY_RS));
}

/**
  * @brief  Get the selected ADC instance deep power down state.
  * @rmtoll CR       DEEPPWD        LL_ADC_IsDeepPowerDownEnabled
  * @param  ADCx ADC instance
  * @retval 0: deep power down is disabled, 1: deep power down is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsDeepPowerDownEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_DEEPPWD) == (ADC_CR_DEEPPWD)) ? 1UL : 0UL);
}

/**
  * @brief  Enable ADC instance internal voltage regulator.
  * @note   On this STM32 series, after ADC internal voltage regulator enable,
  *         a delay for ADC internal voltage regulator stabilization
  *         is required before performing a ADC calibration or ADC enable.
  *         Refer to device datasheet, parameter tADCVREG_STUP.
  *         Refer to literal @ref LL_ADC_DELAY_INTERNAL_REGUL_STAB_US.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @rmtoll CR       ADVREGEN       LL_ADC_EnableInternalRegulator
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableInternalRegulator(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR, ADC_CR_BITS_PROPERTY_RS, ADC_CR_ADVREGEN);
}

/**
  * @brief  Disable ADC internal voltage regulator.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @rmtoll CR       ADVREGEN       LL_ADC_DisableInternalRegulator
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableInternalRegulator(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CR, (ADC_CR_ADVREGEN | ADC_CR_BITS_PROPERTY_RS));
}

/**
  * @brief  Get the selected ADC instance internal voltage regulator state.
  * @rmtoll CR       ADVREGEN       LL_ADC_IsInternalRegulatorEnabled
  * @param  ADCx ADC instance
  * @retval 0: internal regulator is disabled, 1: internal regulator is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsInternalRegulatorEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_ADVREGEN) == (ADC_CR_ADVREGEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the selected ADC instance.
  * @note   On this STM32 series, after ADC enable, a delay for
  *         ADC internal analog stabilization is required before performing a
  *         ADC conversion start.
  *         Refer to device datasheet, parameter tSTAB.
  * @note   On this STM32 series, flag LL_ADC_FLAG_ADRDY is raised when the ADC
  *         is enabled and when conversion clock is active.
  *         (not only core clock: this ADC has a dual clock domain)
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled and ADC internal voltage regulator enabled.
  * @rmtoll CR       ADEN           LL_ADC_Enable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_Enable(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR, ADC_CR_BITS_PROPERTY_RS, ADC_CR_ADEN);
}

/**
  * @brief  Disable the selected ADC instance.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be not disabled. Must be enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CR       ADDIS          LL_ADC_Disable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_Disable(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR, ADC_CR_BITS_PROPERTY_RS, ADC_CR_ADDIS);
}

/**
  * @brief  Get the selected ADC instance enable state.
  * @note   On this STM32 series, flag LL_ADC_FLAG_ADRDY is raised when the ADC
  *         is enabled and when conversion clock is active.
  *         (not only core clock: this ADC has a dual clock domain)
  * @rmtoll CR       ADEN           LL_ADC_IsEnabled
  * @param  ADCx ADC instance
  * @retval 0: ADC is disabled, 1: ADC is enabled.
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabled(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_ADEN) == (ADC_CR_ADEN)) ? 1UL : 0UL);
}

/**
  * @brief  Get the selected ADC instance disable state.
  * @rmtoll CR       ADDIS          LL_ADC_IsDisableOngoing
  * @param  ADCx ADC instance
  * @retval 0: no ADC disable command on going.
  */
__STATIC_INLINE uint32_t LL_ADC_IsDisableOngoing(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_ADDIS) == (ADC_CR_ADDIS)) ? 1UL : 0UL);
}

/**
  * @brief  Start ADC calibration in the mode single-ended
  *         or differential (for devices with differential mode available).
  * @note   On this STM32 series, a minimum number of ADC clock cycles
  *         are required between ADC end of calibration and ADC enable.
  *         Refer to literal @ref LL_ADC_DELAY_CALIB_ENABLE_ADC_CYCLES.
  * @note   Calibration duration:
  *         - Calibration of offset: 520 ADC clock cycles
  *         - Calibration of linearity: 131072 ADC clock cycles
  * @note   For devices with differential mode available:
  *         Calibration of offset is specific to each of
  *         single-ended and differential modes
  *         (calibration run must be performed for each of these
  *         differential modes, if used afterwards and if the application
  *         requires their calibration).
  *         Calibration of linearity is common to both
  *         single-ended and differential modes
  *         (calibration run can be performed only once).
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @rmtoll CR       ADCAL          LL_ADC_StartCalibration
  *         CR       ADCALDIF       LL_ADC_StartCalibration
  *         CR       ADCALLIN       LL_ADC_StartCalibration
  * @param  ADCx ADC instance
  * @param  CalibrationMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CALIB_OFFSET
  *         @arg @ref LL_ADC_CALIB_OFFSET_LINEARITY
  * @retval None
  */
__STATIC_INLINE void LL_ADC_StartCalibration(ADC_TypeDef *ADCx, uint32_t CalibrationMode)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  if (ADCx != ADC4) /* ADC1 or ADC2 */
  {
    MODIFY_REG(ADCx->CR,
               ADC_CR_ADCALLIN | ADC_CR_BITS_PROPERTY_RS,
               ADC_CR_ADCAL | (CalibrationMode & ADC_CALIB_MODE_MASK));
  }
  else
  {
    MODIFY_REG(ADCx->CR,  ADC_CR_BITS_PROPERTY_RS,    ADC_CR_ADCAL);
  }
}

/**
  * @brief  Get ADC calibration state.
  * @rmtoll CR       ADCAL          LL_ADC_IsCalibrationOnGoing
  * @param  ADCx ADC instance
  * @retval 0: calibration complete, 1: calibration in progress.
  */
__STATIC_INLINE uint32_t LL_ADC_IsCalibrationOnGoing(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_ADCAL) == (ADC_CR_ADCAL)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Operation_ADC_Group_Regular Operation on ADC hierarchical scope: group regular
  * @{
  */

/**
  * @brief  Start ADC group regular conversion.
  * @note   On this STM32 series, this function is relevant for both
  *         internal trigger (SW start) and external trigger:
  *         - If ADC trigger has been set to software start, ADC conversion
  *           starts immediately.
  *         - If ADC trigger has been set to external trigger, ADC conversion
  *           will start at next trigger event (on the selected trigger edge)
  *           following the ADC start conversion command.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion on going on group regular,
  *         without conversion stop command on going on group regular,
  *         without ADC disable command on going.
  * @rmtoll CR       ADSTART        LL_ADC_REG_StartConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_StartConversion(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR, ADC_CR_BITS_PROPERTY_RS, ADC_CR_ADSTART);
}

/**
  * @brief  Stop ADC group regular conversion.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled with conversion on going on group regular,
  *         without ADC disable command on going.
  * @rmtoll CR       ADSTP          LL_ADC_REG_StopConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_StopConversion(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_ADSTP);
}

/**
  * @brief  Get ADC group regular conversion state.
  * @rmtoll CR       ADSTART        LL_ADC_REG_IsConversionOngoing
  * @param  ADCx ADC instance
  * @retval 0: no conversion is on going on ADC group regular.
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsConversionOngoing(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_ADSTART) == (ADC_CR_ADSTART)) ? 1UL : 0UL);
}

/**
  * @brief  Get ADC group regular command of conversion stop state
  * @rmtoll CR       ADSTP          LL_ADC_REG_IsStopConversionOngoing
  * @param  ADCx ADC instance
  * @retval 0: no command of conversion stop is on going on ADC group regular.
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsStopConversionOngoing(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_ADSTP) == (ADC_CR_ADSTP)) ? 1UL : 0UL);
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         all ADC configurations: all ADC resolutions and
  *         all oversampling increased data width (for devices
  *         with feature oversampling).
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData32
  * @param  ADCx ADC instance
  * @retval Value between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_REG_ReadConversionData32(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         ADC resolution 16 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_REG_ReadConversionData32.
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData16
  * @param  ADCx ADC instance
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint16_t LL_ADC_REG_ReadConversionData16(ADC_TypeDef *ADCx)
{
  return (uint16_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         ADC resolution 14 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_REG_ReadConversionData32.
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData14
  * @param  ADCx ADC instance
  * @retval Value between Min_Data=0x00 and Max_Data=0x3FF
  */
__STATIC_INLINE uint16_t LL_ADC_REG_ReadConversionData14(ADC_TypeDef *ADCx)
{
  return (uint16_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         ADC resolution 12 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_REG_ReadConversionData32.
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData12
  * @param  ADCx ADC instance
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFF
  */
__STATIC_INLINE uint16_t LL_ADC_REG_ReadConversionData12(ADC_TypeDef *ADCx)
{
  return (uint16_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         ADC resolution 10 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_REG_ReadConversionData32.
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData10
  * @param  ADCx ADC instance
  * @retval Value between Min_Data=0x000 and Max_Data=0x3FF
  */
__STATIC_INLINE uint16_t LL_ADC_REG_ReadConversionData10(ADC_TypeDef *ADCx)
{
  return (uint16_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         ADC resolution 8 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_REG_ReadConversionData32.
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData8
  * @param  ADCx ADC instance
  * @retval Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint8_t LL_ADC_REG_ReadConversionData8(ADC_TypeDef *ADCx)
{
  return (uint8_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

#if defined(ADC_MULTIMODE_SUPPORT)
/**
  * @brief  Get ADC multimode conversion data of ADC master, ADC slave
  *         or raw data with ADC master and slave concatenated.
  * @note   If raw data with ADC master and slave concatenated is retrieved,
  *         a macro is available to get the conversion data of
  *         ADC master or ADC slave: see helper macro
  *         @ref __LL_ADC_MULTI_CONV_DATA_MASTER_SLAVE().
  *         (however this macro is mainly intended for multimode
  *         transfer by DMA, because this function can do the same
  *         by getting multimode conversion data of ADC master or ADC slave
  *         separately).
  * @rmtoll CDR      RDATA_MST      LL_ADC_REG_ReadMultiConversionData32
  *         CDR      RDATA_SLV      LL_ADC_REG_ReadMultiConversionData32
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  ConversionData This parameter can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_MASTER
  *         @arg @ref LL_ADC_MULTI_SLAVE
  *         @arg @ref LL_ADC_MULTI_MASTER_SLAVE
  * @retval Value between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_REG_ReadMultiConversionData32(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t ConversionData)
{
  return (uint32_t)(READ_BIT(ADCxy_COMMON->CDR, ConversionData) >> (POSITION_VAL(ConversionData) & 0x1FUL));
}
#endif /* ADC_MULTIMODE_SUPPORT */
/**
  * @}
  */

/** @defgroup ADC_LL_EF_Operation_ADC_Group_Injected Operation on ADC hierarchical scope: group injected
  * @{
  */

/**
  * @brief  Start ADC group injected conversion.
  * @note   On this STM32 series, this function is relevant for both
  *         internal trigger (SW start) and external trigger:
  *         - If ADC trigger has been set to software start, ADC conversion
  *           starts immediately.
  *         - If ADC trigger has been set to external trigger, ADC conversion
  *           will start at next trigger event (on the selected trigger edge)
  *           following the ADC start conversion command.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion on going on group injected,
  *         without conversion stop command on going on group injected,
  *         without ADC disable command on going.
  * @rmtoll CR       JADSTART       LL_ADC_INJ_StartConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_StartConversion(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR, ADC_CR_BITS_PROPERTY_RS, ADC_CR_JADSTART);
}

/**
  * @brief  Stop ADC group injected conversion.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled with conversion on going on group injected,
  *         without ADC disable command on going.
  * @rmtoll CR       JADSTP         LL_ADC_INJ_StopConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_StopConversion(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR, ADC_CR_BITS_PROPERTY_RS, ADC_CR_JADSTP);
}

/**
  * @brief  Get ADC group injected conversion state.
  * @rmtoll CR       JADSTART       LL_ADC_INJ_IsConversionOngoing
  * @param  ADCx ADC instance
  * @retval 0: no conversion is on going on ADC group injected.
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsConversionOngoing(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_JADSTART) == (ADC_CR_JADSTART)) ? 1UL : 0UL);
}

/**
  * @brief  Get ADC group injected command of conversion stop state
  * @rmtoll CR       JADSTP         LL_ADC_INJ_IsStopConversionOngoing
  * @param  ADCx ADC instance
  * @retval 0: no command of conversion stop is on going on ADC group injected.
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsStopConversionOngoing(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CR, ADC_CR_JADSTP) == (ADC_CR_JADSTP)) ? 1UL : 0UL);
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         all ADC configurations: all ADC resolutions and
  *         all oversampling increased data width (for devices
  *         with feature oversampling).
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData32
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData32
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData32
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData32
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Value between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_ReadConversionData32(ADC_TypeDef *ADCx, uint32_t Rank)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1, ((Rank & ADC_INJ_JDRX_REGOFFSET_MASK)                  \
                                                                >> ADC_JDRX_REGOFFSET_POS));

  return (uint32_t)(READ_BIT(*preg, ADC_JDR1_JDATA));
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         ADC resolution 16 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_INJ_ReadConversionData32.
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData16
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData16
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData16
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData16
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint16_t LL_ADC_INJ_ReadConversionData16(ADC_TypeDef *ADCx, uint32_t Rank)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1, ((Rank & ADC_INJ_JDRX_REGOFFSET_MASK)                  \
                                                                >> ADC_JDRX_REGOFFSET_POS));

  return (uint16_t)(READ_BIT(*preg, ADC_JDR1_JDATA));
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         ADC resolution 14 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_INJ_ReadConversionData32.
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData14
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData14
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData14
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData14
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Value between Min_Data=0x000 and Max_Data=0x3FFF
  */
__STATIC_INLINE uint16_t LL_ADC_INJ_ReadConversionData14(ADC_TypeDef *ADCx, uint32_t Rank)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1, ((Rank & ADC_INJ_JDRX_REGOFFSET_MASK)                  \
                                                                >> ADC_JDRX_REGOFFSET_POS));

  return (uint16_t)(READ_BIT(*preg, ADC_JDR1_JDATA));
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         ADC resolution 12 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_INJ_ReadConversionData32.
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData12
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData12
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData12
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData12
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Value between Min_Data=0x000 and Max_Data=0xFFF
  */
__STATIC_INLINE uint16_t LL_ADC_INJ_ReadConversionData12(ADC_TypeDef *ADCx, uint32_t Rank)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1, ((Rank & ADC_INJ_JDRX_REGOFFSET_MASK)                  \
                                                                >> ADC_JDRX_REGOFFSET_POS));

  return (uint16_t)(READ_BIT(*preg, ADC_JDR1_JDATA));
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         ADC resolution 10 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_INJ_ReadConversionData32.
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData10
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData10
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData10
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData10
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Value between Min_Data=0x000 and Max_Data=0x3FF
  */
__STATIC_INLINE uint16_t LL_ADC_INJ_ReadConversionData10(ADC_TypeDef *ADCx, uint32_t Rank)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1, ((Rank & ADC_INJ_JDRX_REGOFFSET_MASK)                  \
                                                                >> ADC_JDRX_REGOFFSET_POS));

  return (uint16_t)(READ_BIT(*preg, ADC_JDR1_JDATA));
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         ADC resolution 8 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_INJ_ReadConversionData32.
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData8
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData8
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData8
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData8
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint8_t LL_ADC_INJ_ReadConversionData8(ADC_TypeDef *ADCx, uint32_t Rank)
{
  const __IO uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1, ((Rank & ADC_INJ_JDRX_REGOFFSET_MASK)                  \
                                                                >> ADC_JDRX_REGOFFSET_POS));

  return (uint8_t)(READ_BIT(*preg, ADC_JDR1_JDATA));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_FLAG_Management ADC flag management
  * @{
  */

/**
  * @brief  Get flag ADC ready.
  * @note   On this STM32 series, flag LL_ADC_FLAG_ADRDY is raised when the ADC
  *         is enabled and when conversion clock is active.
  *         (not only core clock: this ADC has a dual clock domain)
  * @rmtoll ISR      ADRDY          LL_ADC_IsActiveFlag_ADRDY
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_ADRDY(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_ADRDY) == (LL_ADC_FLAG_ADRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group regular end of unitary conversion.
  * @rmtoll ISR      EOC            LL_ADC_IsActiveFlag_EOC
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOC(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, ADC_ISR_EOC) == (ADC_ISR_EOC)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group regular end of sequence conversions.
  * @rmtoll ISR      EOS            LL_ADC_IsActiveFlag_EOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOS(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_EOS) == (LL_ADC_FLAG_EOS)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group regular overrun.
  * @rmtoll ISR      OVR            LL_ADC_IsActiveFlag_OVR
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_OVR(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_OVR) == (LL_ADC_FLAG_OVR)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group regular end of sampling phase.
  * @rmtoll ISR      EOSMP          LL_ADC_IsActiveFlag_EOSMP
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOSMP(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_EOSMP) == (LL_ADC_FLAG_EOSMP)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group injected end of unitary conversion.
  * @rmtoll ISR      JEOC           LL_ADC_IsActiveFlag_JEOC
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_JEOC(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_JEOC) == (LL_ADC_FLAG_JEOC)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group injected end of sequence conversions.
  * @rmtoll ISR      JEOS           LL_ADC_IsActiveFlag_JEOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_JEOS(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_JEOS) == (LL_ADC_FLAG_JEOS)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC group injected contexts queue overflow.
  * @rmtoll ISR      JQOVF          LL_ADC_IsActiveFlag_JQOVF
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_JQOVF(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_JQOVF) == (LL_ADC_FLAG_JQOVF)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC analog watchdog 1 flag
  * @rmtoll ISR      AWD1           LL_ADC_IsActiveFlag_AWD1
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD1(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_AWD1) == (LL_ADC_FLAG_AWD1)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC analog watchdog 2.
  * @rmtoll ISR      AWD2           LL_ADC_IsActiveFlag_AWD2
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD2(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_AWD2) == (LL_ADC_FLAG_AWD2)) ? 1UL : 0UL);
}

/**
  * @brief  Get flag ADC analog watchdog 3.
  * @rmtoll ISR      AWD3           LL_ADC_IsActiveFlag_AWD3
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD3(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->ISR, LL_ADC_FLAG_AWD3) == (LL_ADC_FLAG_AWD3)) ? 1UL : 0UL);
}

/**
  * @brief  Clear flag ADC ready.
  * @note   On this STM32 series, flag LL_ADC_FLAG_ADRDY is raised when the ADC
  *         is enabled and when conversion clock is active.
  *         (not only core clock: this ADC has a dual clock domain)
  * @rmtoll ISR      ADRDY          LL_ADC_ClearFlag_ADRDY
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_ADRDY(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_ADRDY);
}

/**
  * @brief  Clear flag ADC group regular end of unitary conversion.
  * @rmtoll ISR      EOC            LL_ADC_ClearFlag_EOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOC(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_EOC);
}

/**
  * @brief  Clear flag ADC group regular end of sequence conversions.
  * @rmtoll ISR      EOS            LL_ADC_ClearFlag_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOS(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_EOS);
}

/**
  * @brief  Clear flag ADC group regular overrun.
  * @rmtoll ISR      OVR            LL_ADC_ClearFlag_OVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_OVR(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_OVR);
}

/**
  * @brief  Clear flag ADC group regular end of sampling phase.
  * @rmtoll ISR      EOSMP          LL_ADC_ClearFlag_EOSMP
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOSMP(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_EOSMP);
}

/**
  * @brief  Clear flag ADC group injected end of unitary conversion.
  * @rmtoll ISR      JEOC           LL_ADC_ClearFlag_JEOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_JEOC(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_JEOC);
}

/**
  * @brief  Clear flag ADC group injected end of sequence conversions.
  * @rmtoll ISR      JEOS           LL_ADC_ClearFlag_JEOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_JEOS(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_JEOS);
}

/**
  * @brief  Clear flag ADC group injected contexts queue overflow.
  * @rmtoll ISR      JQOVF          LL_ADC_ClearFlag_JQOVF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_JQOVF(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_JQOVF);
}

/**
  * @brief  Clear flag ADC analog watchdog 1.
  * @rmtoll ISR      AWD1           LL_ADC_ClearFlag_AWD1
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD1(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_AWD1);
}

/**
  * @brief  Clear flag ADC analog watchdog 2.
  * @rmtoll ISR      AWD2           LL_ADC_ClearFlag_AWD2
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD2(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_AWD2);
}

/**
  * @brief  Clear flag ADC analog watchdog 3.
  * @rmtoll ISR      AWD3           LL_ADC_ClearFlag_AWD3
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD3(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, LL_ADC_FLAG_AWD3);
}


/**
  * @}
  */

/** @defgroup ADC_LL_EF_IT_Management ADC IT management
  * @{
  */

/**
  * @brief  Enable ADC ready.
  * @rmtoll IER      ADRDYIE        LL_ADC_EnableIT_ADRDY
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_ADRDY(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_ADRDY);
}

/**
  * @brief  Enable interruption ADC group regular end of unitary conversion.
  * @rmtoll IER      EOCIE          LL_ADC_EnableIT_EOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOC(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_EOC);
}

/**
  * @brief  Enable interruption ADC group regular end of sequence conversions.
  * @rmtoll IER      EOSIE          LL_ADC_EnableIT_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOS(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_EOS);
}

/**
  * @brief  Enable ADC group regular interruption overrun.
  * @rmtoll IER      OVRIE          LL_ADC_EnableIT_OVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_OVR(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_OVR);
}

/**
  * @brief  Enable interruption ADC group regular end of sampling.
  * @rmtoll IER      EOSMPIE        LL_ADC_EnableIT_EOSMP
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOSMP(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_EOSMP);
}

/**
  * @brief  Enable interruption ADC group injected end of unitary conversion.
  * @rmtoll IER      JEOCIE         LL_ADC_EnableIT_JEOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_JEOC(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_JEOC);
}

/**
  * @brief  Enable interruption ADC group injected end of sequence conversions.
  * @rmtoll IER      JEOSIE         LL_ADC_EnableIT_JEOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_JEOS(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_JEOS);
}

/**
  * @brief  Enable interruption ADC group injected context queue overflow.
  * @rmtoll IER      JQOVFIE        LL_ADC_EnableIT_JQOVF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_JQOVF(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_JQOVF);
}

/**
  * @brief  Enable interruption ADC analog watchdog 1.
  * @rmtoll IER      AWD1IE         LL_ADC_EnableIT_AWD1
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWD1(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_AWD1);
}

/**
  * @brief  Enable interruption ADC analog watchdog 2.
  * @rmtoll IER      AWD2IE         LL_ADC_EnableIT_AWD2
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWD2(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_AWD2);
}

/**
  * @brief  Enable interruption ADC analog watchdog 3.
  * @rmtoll IER      AWD3IE         LL_ADC_EnableIT_AWD3
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWD3(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_AWD3);
}

/**
  * @brief  Enable interruption ADC end of calibration.
  * @rmtoll IER      EOCALIE        LL_ADC_EnableIT_EOCAL
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOCAL(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, LL_ADC_IT_EOCAL);
}

/**
  * @brief  Disable interruption ADC ready.
  * @rmtoll IER      ADRDYIE        LL_ADC_DisableIT_ADRDY
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_ADRDY(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_ADRDY);
}

/**
  * @brief  Disable interruption ADC group regular end of unitary conversion.
  * @rmtoll IER      EOCIE          LL_ADC_DisableIT_EOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOC(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_EOC);
}

/**
  * @brief  Disable interruption ADC group regular end of sequence conversions.
  * @rmtoll IER      EOSIE          LL_ADC_DisableIT_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOS(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_EOS);
}

/**
  * @brief  Disable interruption ADC group regular overrun.
  * @rmtoll IER      OVRIE          LL_ADC_DisableIT_OVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_OVR(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_OVR);
}

/**
  * @brief  Disable interruption ADC group regular end of sampling.
  * @rmtoll IER      EOSMPIE        LL_ADC_DisableIT_EOSMP
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOSMP(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_EOSMP);
}

/**
  * @brief  Disable interruption ADC group regular end of unitary conversion.
  * @rmtoll IER      JEOCIE         LL_ADC_DisableIT_JEOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_JEOC(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_JEOC);
}

/**
  * @brief  Disable interruption ADC group injected end of sequence conversions.
  * @rmtoll IER      JEOSIE         LL_ADC_DisableIT_JEOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_JEOS(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_JEOS);
}

/**
  * @brief  Disable interruption ADC group injected context queue overflow.
  * @rmtoll IER      JQOVFIE        LL_ADC_DisableIT_JQOVF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_JQOVF(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_JQOVF);
}

/**
  * @brief  Disable interruption ADC analog watchdog 1.
  * @rmtoll IER      AWD1IE         LL_ADC_DisableIT_AWD1
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWD1(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_AWD1);
}

/**
  * @brief  Disable interruption ADC analog watchdog 2.
  * @rmtoll IER      AWD2IE         LL_ADC_DisableIT_AWD2
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWD2(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_AWD2);
}

/**
  * @brief  Disable interruption ADC analog watchdog 3.
  * @rmtoll IER      AWD3IE         LL_ADC_DisableIT_AWD3
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWD3(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_AWD3);
}

/**
  * @brief  Disable interruption ADC end of calibration.
  * @rmtoll IER      EOCALIE        LL_ADC_DisableIT_EOCAL
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOCAL(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, LL_ADC_IT_EOCAL);
}

/**
  * @brief  Get state of interruption ADC ready
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      ADRDYIE        LL_ADC_IsEnabledIT_ADRDY
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_ADRDY(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_ADRDY) == (LL_ADC_IT_ADRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group regular end of unitary conversion
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      EOCIE          LL_ADC_IsEnabledIT_EOC
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOC(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_EOC) == (LL_ADC_IT_EOC)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group regular end of sequence conversions
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      EOSIE          LL_ADC_IsEnabledIT_EOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOS(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_EOS) == (LL_ADC_IT_EOS)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group regular overrun
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      OVRIE          LL_ADC_IsEnabledIT_OVR
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_OVR(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_OVR) == (LL_ADC_IT_OVR)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group regular end of sampling
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      EOSMPIE        LL_ADC_IsEnabledIT_EOSMP
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOSMP(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_EOSMP) == (LL_ADC_IT_EOSMP)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group injected end of unitary conversion
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      JEOCIE         LL_ADC_IsEnabledIT_JEOC
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_JEOC(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_JEOC) == (LL_ADC_IT_JEOC)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group injected end of sequence conversions
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      JEOSIE         LL_ADC_IsEnabledIT_JEOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_JEOS(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_JEOS) == (LL_ADC_IT_JEOS)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC group injected context queue overflow interrupt state
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      JQOVFIE        LL_ADC_IsEnabledIT_JQOVF
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_JQOVF(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_JQOVF) == (LL_ADC_IT_JQOVF)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC analog watchdog 1
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      AWD1IE         LL_ADC_IsEnabledIT_AWD1
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_AWD1(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_AWD1) == (LL_ADC_IT_AWD1)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption Get ADC analog watchdog 2
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      AWD2IE         LL_ADC_IsEnabledIT_AWD2
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_AWD2(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_AWD2) == (LL_ADC_IT_AWD2)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption Get ADC analog watchdog 3
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      AWD3IE         LL_ADC_IsEnabledIT_AWD3
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_AWD3(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_AWD3) == (LL_ADC_IT_AWD3)) ? 1UL : 0UL);
}

/**
  * @brief  Get state of interruption ADC end of calibration
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @rmtoll IER      EOCALIE        LL_ADC_IsEnabledIT_EOCAL
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOCAL(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->IER, LL_ADC_IT_EOCAL) == (LL_ADC_IT_EOCAL)) ? 1UL : 0UL);
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup ADC_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

/* Initialization of some features of ADC common parameters and multimode */
ErrorStatus LL_ADC_CommonDeInit(ADC_Common_TypeDef *pADCxyCOMMON);
ErrorStatus LL_ADC_CommonInit(ADC_Common_TypeDef *pADCxyCOMMON, LL_ADC_CommonInitTypeDef *pADC_CommonInit);
void        LL_ADC_CommonStructInit(LL_ADC_CommonInitTypeDef *pADC_CommonInit);

/* De-initialization of ADC instance, ADC group regular and ADC group injected */
/* (availability of ADC group injected depends on STM32 families) */
ErrorStatus LL_ADC_DeInit(ADC_TypeDef *pADCx);

/* Initialization of some features of ADC instance */
ErrorStatus LL_ADC_Init(ADC_TypeDef *pADCx, LL_ADC_InitTypeDef *pADC_InitStruct);
void        LL_ADC_StructInit(ADC_TypeDef *pADCx, LL_ADC_InitTypeDef *pADC_InitStruct);

/* Initialization of some features of ADC instance and ADC group regular */
ErrorStatus LL_ADC_REG_Init(ADC_TypeDef *pADCx, LL_ADC_REG_InitTypeDef *pADC_RegInitStruct);
void        LL_ADC_REG_StructInit(ADC_TypeDef *pADCx, LL_ADC_REG_InitTypeDef *pADC_RegInitStruct);

/* Initialization of some features of ADC instance and ADC group injected */
ErrorStatus LL_ADC_INJ_Init(ADC_TypeDef *pADCx, LL_ADC_INJ_InitTypeDef *pADC_InjInitStruct);
void        LL_ADC_INJ_StructInit(LL_ADC_INJ_InitTypeDef *pADC_InjInitStruct);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* ADC1 || ADC2 || ADC3 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_LL_ADC_H */
