/*!
    \file    gd32f20x_adc.h
    \brief   definitions for the ADC

    \version 2015-07-15, V1.0.0, firmware for GD32F20x
    \version 2017-06-05, V2.0.0, firmware for GD32F20x
    \version 2018-10-31, V2.1.0, firmware for GD32F20x
    \version 2020-09-30, V2.2.0, firmware for GD32F20x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32F20X_ADC_H
#define GD32F20X_ADC_H

#include "gd32f20x.h"

/* ADC definitions */
#define ADC0                             ADC_BASE
#define ADC1                             (ADC_BASE + 0x400U)
#define ADC2                             (ADC_BASE + 0x1800U)

/* registers definitions */
#define ADC_STAT(adcx)                   REG32((adcx) + 0x00U)            /*!< ADC status register */
#define ADC_CTL0(adcx)                   REG32((adcx) + 0x04U)            /*!< ADC control register 0 */
#define ADC_CTL1(adcx)                   REG32((adcx) + 0x08U)            /*!< ADC control register 1 */
#define ADC_SAMPT0(adcx)                 REG32((adcx) + 0x0CU)            /*!< ADC sampling time register 0 */
#define ADC_SAMPT1(adcx)                 REG32((adcx) + 0x10U)            /*!< ADC sampling time register 1 */
#define ADC_IOFF0(adcx)                  REG32((adcx) + 0x14U)            /*!< ADC inserted channel data offset register 0 */
#define ADC_IOFF1(adcx)                  REG32((adcx) + 0x18U)            /*!< ADC inserted channel data offset register 1 */
#define ADC_IOFF2(adcx)                  REG32((adcx) + 0x1CU)            /*!< ADC inserted channel data offset register 2 */
#define ADC_IOFF3(adcx)                  REG32((adcx) + 0x20U)            /*!< ADC inserted channel data offset register 3 */
#define ADC_WDHT(adcx)                   REG32((adcx) + 0x24U)            /*!< ADC watchdog high threshold register */
#define ADC_WDLT(adcx)                   REG32((adcx) + 0x28U)            /*!< ADC watchdog low threshold register */
#define ADC_RSQ0(adcx)                   REG32((adcx) + 0x2CU)            /*!< ADC regular sequence register 0 */
#define ADC_RSQ1(adcx)                   REG32((adcx) + 0x30U)            /*!< ADC regular sequence register 1 */
#define ADC_RSQ2(adcx)                   REG32((adcx) + 0x34U)            /*!< ADC regular sequence register 2 */
#define ADC_ISQ(adcx)                    REG32((adcx) + 0x38U)            /*!< ADC inserted sequence register */
#define ADC_IDATA0(adcx)                 REG32((adcx) + 0x3CU)            /*!< ADC inserted data register 0 */
#define ADC_IDATA1(adcx)                 REG32((adcx) + 0x40U)            /*!< ADC inserted data register 1 */
#define ADC_IDATA2(adcx)                 REG32((adcx) + 0x44U)            /*!< ADC inserted data register 2 */
#define ADC_IDATA3(adcx)                 REG32((adcx) + 0x48U)            /*!< ADC inserted data register 3 */
#define ADC_RDATA(adcx)                  REG32((adcx) + 0x4CU)            /*!< ADC regular data register */
#define ADC_OVSAMPCTL(adcx)              REG32((adcx) + 0x80U)            /*!< ADC oversampling control register */

/* bits definitions */
/* ADC_STAT */
#define ADC_STAT_WDE                     BIT(0)                           /*!< analog watchdog event flag */
#define ADC_STAT_EOC                     BIT(1)                           /*!< end of conversion */
#define ADC_STAT_EOIC                    BIT(2)                           /*!< inserted channel end of conversion */
#define ADC_STAT_STIC                    BIT(3)                           /*!< inserted channel start flag */
#define ADC_STAT_STRC                    BIT(4)                           /*!< regular channel start flag */

/* ADC_CTL0 */
#define ADC_CTL0_WDCHSEL                 BITS(0,4)                        /*!< analog watchdog channel select bits */
#define ADC_CTL0_EOCIE                   BIT(5)                           /*!< interrupt enable for EOC */
#define ADC_CTL0_WDEIE                   BIT(6)                           /*!< analog watchdog interrupt enable */
#define ADC_CTL0_EOICIE                  BIT(7)                           /*!< interrupt enable for inserted channels */
#define ADC_CTL0_SM                      BIT(8)                           /*!< scan mode */
#define ADC_CTL0_WDSC                    BIT(9)                           /*!< when in scan mode, analog watchdog is effective on a single channel */
#define ADC_CTL0_ICA                     BIT(10)                          /*!< automatic inserted group conversion */
#define ADC_CTL0_DISRC                   BIT(11)                          /*!< discontinuous mode on regular channels */
#define ADC_CTL0_DISIC                   BIT(12)                          /*!< discontinuous mode on inserted channels */
#define ADC_CTL0_DISNUM                  BITS(13,15)                      /*!< discontinuous mode channel count */
#define ADC_CTL0_SYNCM                   BITS(16,19)                      /*!< sync mode selection */
#define ADC_CTL0_IWDEN                   BIT(22)                          /*!< analog watchdog enable on inserted channels */
#define ADC_CTL0_RWDEN                   BIT(23)                          /*!< analog watchdog enable on regular channels */

/* ADC_CTL1 */
#define ADC_CTL1_ADCON                   BIT(0)                           /*!< ADC converter on */
#define ADC_CTL1_CTN                     BIT(1)                           /*!< continuous conversion */
#define ADC_CTL1_CLB                     BIT(2)                           /*!< ADC calibration */
#define ADC_CTL1_RSTCLB                  BIT(3)                           /*!< reset calibration */
#define ADC_CTL1_DMA                     BIT(8)                           /*!< direct memory access mode */
#define ADC_CTL1_DAL                     BIT(11)                          /*!< data alignment */
#define ADC_CTL1_ETSIC                   BITS(12,14)                      /*!< external trigger select for inserted channel */
#define ADC_CTL1_ETEIC                   BIT(15)                          /*!< external trigger enable for inserted channel */
#define ADC_CTL1_ETSRC                   BITS(17,19)                      /*!< external trigger select for regular channel */
#define ADC_CTL1_ETERC                   BIT(20)                          /*!< external trigger enable for regular channel */
#define ADC_CTL1_SWICST                  BIT(21)                          /*!< start on inserted channel */
#define ADC_CTL1_SWRCST                  BIT(22)                          /*!< start on regular channel */
#define ADC_CTL1_TSVREN                  BIT(23)                          /*!< channel 16 and 17 enable of ADC0 */

/* ADC_SAMPTx  x=0,1 */
#define ADC_SAMPTX_SPTN                  BITS(0,2)                        /*!< channel n sample time selection */

/* ADC_IOFFx x=0..3 */
#define ADC_IOFFX_IOFF                   BITS(0,11)                       /*!< data offset for inserted channel x */

/* ADC_WDHT */
#define ADC_WDHT_WDHT                    BITS(0,11)                       /*!< analog watchdog high threshold */

/* ADC_WDLT */
#define ADC_WDLT_WDLT                    BITS(0,11)                       /*!< analog watchdog low threshold */

/* ADC_RSQx x=0..2 */
#define ADC_RSQX_RSQN                    BITS(0,4)                        /*!< x conversion in regular sequence */
#define ADC_RSQ0_RL                      BITS(20,23)                      /*!< regular channel sequence length */

/* ADC_ISQ */
#define ADC_ISQ_ISQN                     BITS(0,4)                        /*!< n conversion in regular sequence */
#define ADC_ISQ_IL                       BITS(20,21)                      /*!< inserted sequence length */

/* ADC_IDATAx x=0..3*/
#define ADC_IDATAX_IDATAN                BITS(0,15)                       /*!< inserted channel x conversion data  */

/* ADC_RDATA */
#define ADC_RDATA_RDATA                  BITS(0,15)                       /*!< regular channel data */
#define ADC_RDATA_ADC1RDTR               BITS(16,31)                      /*!< ADC1 regular channel data */

/* ADC_OVSAMPCTL */
#define ADC_OVSAMPCTL_OVSEN              BIT(0)                           /*!< oversampling enable */
#define ADC_OVSAMPCTL_OVSR               BITS(2,4)                        /*!< oversampling ratio */
#define ADC_OVSAMPCTL_OVSS               BITS(5,8)                        /*!< oversampling shift */
#define ADC_OVSAMPCTL_TOVS               BIT(9)                           /*!< triggered oversampling */
#define ADC_OVSAMPCTL_DRES               BITS(12,13)                      /*!< oversampling shift */

/* constants definitions */
/* adc_stat register value */
#define ADC_FLAG_WDE                     ADC_STAT_WDE                                /*!< analog watchdog event flag */
#define ADC_FLAG_EOC                     ADC_STAT_EOC                                /*!< end of group conversion flag */
#define ADC_FLAG_EOIC                    ADC_STAT_EOIC                               /*!< end of inserted channel group conversion flag */
#define ADC_FLAG_STIC                    ADC_STAT_STIC                               /*!< inserted channel start flag */
#define ADC_FLAG_STRC                    ADC_STAT_STRC                               /*!< regular channel start flag */

/* adc_ctl0 register value */
#define CTL0_DISNUM(regval)             (BITS(13,15) & ((uint32_t)(regval) << 13))   /*!< write value to ADC_CTL0_DISNUM bit field */

/* scan mode */
#define ADC_SCAN_MODE                   ADC_CTL0_SM                                  /*!< scan mode */

/* inserted channel group convert automatically */
#define ADC_INSERTED_CHANNEL_AUTO       ADC_CTL0_ICA                                 /*!< inserted channel group convert automatically */

/* ADC sync mode */
#define CTL0_SYNCM(regval)              (BITS(16,19) & ((uint32_t)(regval) << 16))   /*!< write value to ADC_CTL0_SYNCM bit field */
#define ADC_MODE_FREE                                        CTL0_SYNCM(0)           /*!< all the ADCs work independently */
#define ADC_DAUL_REGULAL_PARALLEL_INSERTED_PARALLEL          CTL0_SYNCM(1)           /*!< ADC0 and ADC1 work in combined regular parallel + inserted parallel mode */
#define ADC_DAUL_REGULAL_PARALLEL_INSERTED_ROTATION          CTL0_SYNCM(2)           /*!< ADC0 and ADC1 work in combined regular parallel + trigger rotation mode */
#define ADC_DAUL_INSERTED_PARALLEL_REGULAL_FOLLOWUP_FAST     CTL0_SYNCM(3)           /*!< ADC0 and ADC1 work in combined inserted parallel + follow-up fast mode */
#define ADC_DAUL_INSERTED_PARALLEL_REGULAL_FOLLOWUP_SLOW     CTL0_SYNCM(4)           /*!< ADC0 and ADC1 work in combined inserted parallel + follow-up slow mode */
#define ADC_DAUL_INSERTED_PARALLEL                           CTL0_SYNCM(5)           /*!< ADC0 and ADC1 work in inserted parallel mode only */
#define ADC_DAUL_REGULAL_PARALLEL                            CTL0_SYNCM(6)           /*!< ADC0 and ADC1 work in regular parallel mode only */
#define ADC_DAUL_REGULAL_FOLLOWUP_FAST                       CTL0_SYNCM(7)           /*!< ADC0 and ADC1 work in follow-up fast mode only */
#define ADC_DAUL_REGULAL_FOLLOWUP_SLOW                       CTL0_SYNCM(8)           /*!< ADC0 and ADC1 work in follow-up slow mode only */
#define ADC_DAUL_INSERTED_TRIGGER_ROTATION                   CTL0_SYNCM(9)           /*!< ADC0 and ADC1 work in trigger rotation mode only */

/* adc_ctl1 register value */
#define ADC_DATAALIGN_RIGHT              ((uint32_t)0x00000000U)                     /*!< LSB alignment */
#define ADC_DATAALIGN_LEFT               ADC_CTL1_DAL                                /*!< MSB alignment */

/* continuous mode */
#define ADC_CONTINUOUS_MODE              ADC_CTL1_CTN                                /*!< continuous mode */

/* external trigger select for regular channel */
#define CTL1_ETSRC(regval)               (BITS(17,19) & ((uint32_t)(regval) << 17))  /*!< write value to ADC_CTL1_ETSRC bit field */
/* for ADC0 and ADC1 regular channel */
#define ADC0_1_EXTTRIG_REGULAR_T0_CH0    CTL1_ETSRC(0)                               /*!< TIMER0 CH0 event select */
#define ADC0_1_EXTTRIG_REGULAR_T0_CH1    CTL1_ETSRC(1)                               /*!< TIMER0 CH1 event select */
#define ADC0_1_EXTTRIG_REGULAR_T0_CH2    CTL1_ETSRC(2)                               /*!< TIMER0 CH2 event select */
#define ADC0_1_EXTTRIG_REGULAR_T1_CH1    CTL1_ETSRC(3)                               /*!< TIMER1 CH1 event select */
#define ADC0_1_EXTTRIG_REGULAR_T2_TRGO   CTL1_ETSRC(4)                               /*!< TIMER2 TRGO event select */
#define ADC0_1_EXTTRIG_REGULAR_T3_CH3    CTL1_ETSRC(5)                               /*!< TIMER3 CH3 event select */
#define ADC0_1_EXTTRIG_REGULAR_T7_TRGO   CTL1_ETSRC(6)                               /*!< TIMER7 TRGO event select */
#define ADC0_1_EXTTRIG_REGULAR_EXTI_11   CTL1_ETSRC(6)                               /*!< external interrupt line 11 */
#define ADC0_1_2_EXTTRIG_REGULAR_NONE    CTL1_ETSRC(7)                               /*!< software trigger */
/* for ADC2 regular channel */
#define ADC2_EXTTRIG_REGULAR_T2_CH0      CTL1_ETSRC(0)                               /*!< TIMER2 CH0 event select */
#define ADC2_EXTTRIG_REGULAR_T1_CH2      CTL1_ETSRC(1)                               /*!< TIMER1 CH2 event select */
#define ADC2_EXTTRIG_REGULAR_T0_CH2      CTL1_ETSRC(2)                               /*!< TIMER0 CH2 event select */
#define ADC2_EXTTRIG_REGULAR_T7_CH0      CTL1_ETSRC(3)                               /*!< TIMER7 CH0 event select */
#define ADC2_EXTTRIG_REGULAR_T7_TRGO     CTL1_ETSRC(4)                               /*!< TIMER7 TRGO event select */
#define ADC2_EXTTRIG_REGULAR_T4_CH0      CTL1_ETSRC(5)                               /*!< TIMER4 CH0 event select */
#define ADC2_EXTTRIG_REGULAR_T4_CH2      CTL1_ETSRC(6)                               /*!< TIMER4 CH2 event select */

/* external trigger mode for inserted channel */
#define CTL1_ETSIC(regval)               (BITS(12,14) & ((uint32_t)(regval) << 12))  /*!< write value to ADC_CTL1_ETSIC bit field */
/* for ADC0 and ADC1 inserted channel */
#define ADC0_1_EXTTRIG_INSERTED_T0_TRGO  CTL1_ETSIC(0)                               /*!< TIMER0 TRGO event select */
#define ADC0_1_EXTTRIG_INSERTED_T0_CH3   CTL1_ETSIC(1)                               /*!< TIMER0 CH3 event select */
#define ADC0_1_EXTTRIG_INSERTED_T1_TRGO  CTL1_ETSIC(2)                               /*!< TIMER1 TRGO event select */
#define ADC0_1_EXTTRIG_INSERTED_T1_CH0   CTL1_ETSIC(3)                               /*!< TIMER1 CH0 event select */
#define ADC0_1_EXTTRIG_INSERTED_T2_CH3   CTL1_ETSIC(4)                               /*!< TIMER2 CH3 event select */
#define ADC0_1_EXTTRIG_INSERTED_T3_TRGO  CTL1_ETSIC(5)                               /*!< TIMER3 TRGO event select */
#define ADC0_1_EXTTRIG_INSERTED_EXTI_15  CTL1_ETSIC(6)                               /*!< external interrupt line 15 */
#define ADC0_1_EXTTRIG_INSERTED_T7_CH3   CTL1_ETSIC(6)                               /*!< TIMER7 CH3 event select */
#define ADC0_1_2_EXTTRIG_INSERTED_NONE   CTL1_ETSIC(7)                               /*!< software trigger */
/* for ADC2 inserted channel */
#define ADC2_EXTTRIG_INSERTED_T0_TRGO    CTL1_ETSIC(0)                               /*!< TIMER0 TRGO event select */
#define ADC2_EXTTRIG_INSERTED_T0_CH3     CTL1_ETSIC(1)                               /*!< TIMER0 CH3 event select */
#define ADC2_EXTTRIG_INSERTED_T3_CH2     CTL1_ETSIC(2)                               /*!< TIMER3 CH2 event select */
#define ADC2_EXTTRIG_INSERTED_T7_CH1     CTL1_ETSIC(3)                               /*!< TIMER7 CH1 event select */
#define ADC2_EXTTRIG_INSERTED_T7_CH3     CTL1_ETSIC(4)                               /*!< TIMER7 CH3 event select */
#define ADC2_EXTTRIG_INSERTED_T4_TRGO    CTL1_ETSIC(5)                               /*!< TIMER4 TRGO event select */
#define ADC2_EXTTRIG_INSERTED_T4_CH3     CTL1_ETSIC(6)                               /*!< TIMER4 CH3 event select */

/* adc_samptx register value */
#define SAMPTX_SPT(regval)               (BITS(0,2) & ((uint32_t)(regval) << 0))     /*!< write value to ADC_SAMPTX_SPT bit field */
#define ADC_SAMPLETIME_1POINT5           SAMPTX_SPT(0)                               /*!< 1.5 sampling cycles */
#define ADC_SAMPLETIME_7POINT5           SAMPTX_SPT(1)                               /*!< 7.5 sampling cycles */
#define ADC_SAMPLETIME_13POINT5          SAMPTX_SPT(2)                               /*!< 13.5 sampling cycles */
#define ADC_SAMPLETIME_28POINT5          SAMPTX_SPT(3)                               /*!< 28.5 sampling cycles */
#define ADC_SAMPLETIME_41POINT5          SAMPTX_SPT(4)                               /*!< 41.5 sampling cycles */
#define ADC_SAMPLETIME_55POINT5          SAMPTX_SPT(5)                               /*!< 55.5 sampling cycles */
#define ADC_SAMPLETIME_71POINT5          SAMPTX_SPT(6)                               /*!< 71.5 sampling cycles */
#define ADC_SAMPLETIME_239POINT5         SAMPTX_SPT(7)                               /*!< 239.5 sampling cycles */

/* adc_ioffx register value */
#define IOFFX_IOFF(regval)               (BITS(0,11) & ((uint32_t)(regval) << 0))    /*!< write value to ADC_IOFFX_IOFF bit field */

/* adc_wdht register value */
#define WDHT_WDHT(regval)                (BITS(0,11) & ((uint32_t)(regval) << 0))    /*!< write value to ADC_WDHT_WDHT bit field */

/* adc_wdlt register value */
#define WDLT_WDLT(regval)                (BITS(0,11) & ((uint32_t)(regval) << 0))    /*!< write value to ADC_WDLT_WDLT bit field */

/* adc_rsqx register value */
#define RSQ0_RL(regval)                  (BITS(20,23) & ((uint32_t)(regval) << 20))  /*!< write value to ADC_RSQ0_RL bit field */

/* adc_isq register value */
#define ISQ_IL(regval)                   (BITS(20,21) & ((uint32_t)(regval) << 20))  /*!< write value to ADC_ISQ_IL bit field */

/* adc_ovsampctl register value */
#define OVSAMPCTL_DRES(regval)           (BITS(12,13) & ((uint32_t)(regval) << 12))  /*!< write value to ADC_OVSAMPCTL_DRES bit field */
#define ADC_RESOLUTION_12B               OVSAMPCTL_DRES(0)                           /*!< 12-bit ADC resolution */
#define ADC_RESOLUTION_10B               OVSAMPCTL_DRES(1)                           /*!< 10-bit ADC resolution */
#define ADC_RESOLUTION_8B                OVSAMPCTL_DRES(2)                           /*!< 8-bit ADC resolution */
#define ADC_RESOLUTION_6B                OVSAMPCTL_DRES(3)                           /*!< 6-bit ADC resolution */

#define OVSAMPCTL_OVSS(regval)           (BITS(5,8) & ((uint32_t)(regval) << 5))     /*!< write value to ADC_OVSAMPCTL_OVSS bit field */
#define ADC_OVERSAMPLING_SHIFT_NONE      OVSAMPCTL_OVSS(0)                           /*!< no oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_1B        OVSAMPCTL_OVSS(1)                           /*!< 1-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_2B        OVSAMPCTL_OVSS(2)                           /*!< 2-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_3B        OVSAMPCTL_OVSS(3)                           /*!< 3-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_4B        OVSAMPCTL_OVSS(4)                           /*!< 4-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_5B        OVSAMPCTL_OVSS(5)                           /*!< 5-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_6B        OVSAMPCTL_OVSS(6)                           /*!< 6-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_7B        OVSAMPCTL_OVSS(7)                           /*!< 7-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_8B        OVSAMPCTL_OVSS(8)                           /*!< 8-bit oversampling shift */

#define OVSAMPCTL_OVSR(regval)           (BITS(2,4) & ((uint32_t)(regval) << 2))     /*!< write value to ADC_OVSAMPCTL_OVSR bit field */
#define ADC_OVERSAMPLING_RATIO_MUL2      OVSAMPCTL_OVSR(0)                           /*!< oversampling ratio multiple 2 */
#define ADC_OVERSAMPLING_RATIO_MUL4      OVSAMPCTL_OVSR(1)                           /*!< oversampling ratio multiple 4 */
#define ADC_OVERSAMPLING_RATIO_MUL8      OVSAMPCTL_OVSR(2)                           /*!< oversampling ratio multiple 8 */
#define ADC_OVERSAMPLING_RATIO_MUL16     OVSAMPCTL_OVSR(3)                           /*!< oversampling ratio multiple 16 */
#define ADC_OVERSAMPLING_RATIO_MUL32     OVSAMPCTL_OVSR(4)                           /*!< oversampling ratio multiple 32 */
#define ADC_OVERSAMPLING_RATIO_MUL64     OVSAMPCTL_OVSR(5)                           /*!< oversampling ratio multiple 64 */
#define ADC_OVERSAMPLING_RATIO_MUL128    OVSAMPCTL_OVSR(6)                           /*!< oversampling ratio multiple 128 */
#define ADC_OVERSAMPLING_RATIO_MUL256    OVSAMPCTL_OVSR(7)                           /*!< oversampling ratio multiple 256 */

#define ADC_OVERSAMPLING_ALL_CONVERT     0U                                          /*!< all oversampled conversions for a channel are done consecutively after a trigger */
#define ADC_OVERSAMPLING_ONE_CONVERT     1U                                          /*!< each oversampled conversion for a channel needs a trigger */

/* ADC channel group definitions */
#define ADC_REGULAR_CHANNEL              ((uint8_t)0x01U)                            /*!< ADC regular channel group */
#define ADC_INSERTED_CHANNEL             ((uint8_t)0x02U)                            /*!< ADC inserted channel group */
#define ADC_REGULAR_INSERTED_CHANNEL     ((uint8_t)0x03U)                            /*!< both regular and inserted channel group */

#define ADC_CHANNEL_DISCON_DISABLE       ((uint8_t)0x04U)                            /*!< disable discontinuous mode of regular & inserted channel */

/* ADC inserted channel definitions */
#define ADC_INSERTED_CHANNEL_0           ((uint8_t)0x00U)                            /*!< ADC inserted channel 0 */
#define ADC_INSERTED_CHANNEL_1           ((uint8_t)0x01U)                            /*!< ADC inserted channel 1 */
#define ADC_INSERTED_CHANNEL_2           ((uint8_t)0x02U)                            /*!< ADC inserted channel 2 */
#define ADC_INSERTED_CHANNEL_3           ((uint8_t)0x03U)                            /*!< ADC inserted channel 3 */

/* ADC channel definitions */
#define ADC_CHANNEL_0                    ((uint8_t)0x00U)                            /*!< ADC channel 0 */
#define ADC_CHANNEL_1                    ((uint8_t)0x01U)                            /*!< ADC channel 1 */
#define ADC_CHANNEL_2                    ((uint8_t)0x02U)                            /*!< ADC channel 2 */
#define ADC_CHANNEL_3                    ((uint8_t)0x03U)                            /*!< ADC channel 3 */
#define ADC_CHANNEL_4                    ((uint8_t)0x04U)                            /*!< ADC channel 4 */
#define ADC_CHANNEL_5                    ((uint8_t)0x05U)                            /*!< ADC channel 5 */
#define ADC_CHANNEL_6                    ((uint8_t)0x06U)                            /*!< ADC channel 6 */
#define ADC_CHANNEL_7                    ((uint8_t)0x07U)                            /*!< ADC channel 7 */
#define ADC_CHANNEL_8                    ((uint8_t)0x08U)                            /*!< ADC channel 8 */
#define ADC_CHANNEL_9                    ((uint8_t)0x09U)                            /*!< ADC channel 9 */
#define ADC_CHANNEL_10                   ((uint8_t)0x0AU)                            /*!< ADC channel 10 */
#define ADC_CHANNEL_11                   ((uint8_t)0x0BU)                            /*!< ADC channel 11 */
#define ADC_CHANNEL_12                   ((uint8_t)0x0CU)                            /*!< ADC channel 12 */
#define ADC_CHANNEL_13                   ((uint8_t)0x0DU)                            /*!< ADC channel 13 */
#define ADC_CHANNEL_14                   ((uint8_t)0x0EU)                            /*!< ADC channel 14 */
#define ADC_CHANNEL_15                   ((uint8_t)0x0FU)                            /*!< ADC channel 15 */
#define ADC_CHANNEL_16                   ((uint8_t)0x10U)                            /*!< ADC channel 16 */
#define ADC_CHANNEL_17                   ((uint8_t)0x11U)                            /*!< ADC channel 17 */

/* ADC interrupt */
#define ADC_INT_WDE                      ADC_STAT_WDE                                /*!< analog watchdog event interrupt */
#define ADC_INT_EOC                      ADC_STAT_EOC                                /*!< end of group conversion interrupt */
#define ADC_INT_EOIC                     ADC_STAT_EOIC                               /*!< end of inserted group conversion interrupt */

/* ADC interrupt flag */
#define ADC_INT_FLAG_WDE                 ADC_STAT_WDE                                /*!< analog watchdog event interrupt flag */
#define ADC_INT_FLAG_EOC                 ADC_STAT_EOC                                /*!< end of group conversion interrupt flag */
#define ADC_INT_FLAG_EOIC                ADC_STAT_EOIC                               /*!< end of inserted group conversion interrupt flag */

/* function declarations */
/* initialization configure */
/* reset ADC */
void adc_deinit(uint32_t adc_periph);
/* configure the ADC sync mode */
void adc_mode_config(uint32_t mode);
/* enable or disable ADC special function */
void adc_special_function_config(uint32_t adc_periph, uint32_t function, ControlStatus new_value);
/* configure ADC data alignment */
void adc_data_alignment_config(uint32_t adc_periph, uint32_t data_alignment);
/* enable ADC interface */
void adc_enable(uint32_t adc_periph);
/* disable ADC interface */
void adc_disable(uint32_t adc_periph);
/* ADC calibration and reset calibration */
void adc_calibration_enable(uint32_t adc_periph);
/* enable the temperature sensor and Vrefint channel */
void adc_tempsensor_vrefint_enable(void);
/* disable the temperature sensor and Vrefint channel */
void adc_tempsensor_vrefint_disable(void);

/* function configuration */
/* DMA configure */
/* enable DMA request */
void adc_dma_mode_enable(uint32_t adc_periph);
/* disable DMA request */
void adc_dma_mode_disable(uint32_t adc_periph);

/* regular group and inserted group configure */
/* configure ADC discontinuous mode */
void adc_discontinuous_mode_config(uint32_t adc_periph, uint8_t adc_channel_group, uint8_t length);

/* configure the length of regular channel group or inserted channel group */
void adc_channel_length_config(uint32_t adc_periph, uint8_t adc_channel_group, uint32_t length);
/* configure ADC regular channel */
void adc_regular_channel_config(uint32_t adc_periph, uint8_t rank, uint8_t adc_channel, uint32_t sample_time);
/* configure ADC inserted channel */
void adc_inserted_channel_config(uint32_t adc_periph, uint8_t rank, uint8_t adc_channel, uint32_t sample_time);
/* configure ADC inserted channel offset */
void adc_inserted_channel_offset_config(uint32_t adc_periph, uint8_t inserted_channel, uint16_t offset);

/* configure ADC external trigger source */
void adc_external_trigger_source_config(uint32_t adc_periph, uint8_t adc_channel_group, uint32_t external_trigger_source);
/* configure ADC external trigger */
void adc_external_trigger_config(uint32_t adc_periph, uint8_t adc_channel_group, ControlStatus newvalue);
/* enable ADC software trigger */
void adc_software_trigger_enable(uint32_t adc_periph, uint8_t adc_channel_group);

/* get channel data */
/* read ADC regular group data register */
uint16_t adc_regular_data_read(uint32_t adc_periph);
/* read ADC inserted group data register */
uint16_t adc_inserted_data_read(uint32_t adc_periph, uint8_t inserted_channel);
/* read the last ADC0 and ADC1 conversion result data in sync mode */
uint32_t adc_sync_mode_convert_value_read(void);

/* watchdog configure */
/* configure ADC analog watchdog single channel */
void adc_watchdog_single_channel_enable(uint32_t adc_periph, uint8_t adc_channel);
/* configure ADC analog watchdog group channel */
void adc_watchdog_group_channel_enable(uint32_t adc_periph, uint8_t adc_channel_group);
/* disable ADC analog watchdog */
void adc_watchdog_disable(uint32_t adc_periph);
/* configure ADC analog watchdog threshold */
void adc_watchdog_threshold_config(uint32_t adc_periph, uint16_t low_threshold, uint16_t high_threshold);

/* interrupt & flag functions */
/* get the ADC flag bits */
FlagStatus adc_flag_get(uint32_t adc_periph, uint32_t adc_flag);
/* clear the ADC flag bits */
void adc_flag_clear(uint32_t adc_periph, uint32_t adc_flag);
/* get the ADC interrupt flag */
FlagStatus adc_interrupt_flag_get(uint32_t adc_periph, uint32_t adc_interrupt);
/* clear the ADC interrupt flag */
void adc_interrupt_flag_clear(uint32_t adc_periph, uint32_t adc_interrupt);
/* enable ADC interrupt */
void adc_interrupt_enable(uint32_t adc_periph, uint32_t adc_interrupt);
/* disable ADC interrupt */
void adc_interrupt_disable(uint32_t adc_periph, uint32_t adc_interrupt);

/* configure ADC resolution */
void adc_resolution_config(uint32_t adc_periph, uint32_t resolution);
/* configure ADC oversample mode */
void adc_oversample_mode_config(uint32_t adc_periph, uint8_t mode, uint16_t shift, uint8_t ratio);
/* enable ADC oversample mode */
void adc_oversample_mode_enable(uint32_t adc_periph);
/* disable ADC oversample mode */
void adc_oversample_mode_disable(uint32_t adc_periph);

#endif /* GD32F20X_ADC_H */
