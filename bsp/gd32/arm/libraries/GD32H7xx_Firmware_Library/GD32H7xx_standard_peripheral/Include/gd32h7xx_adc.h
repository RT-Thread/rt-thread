/*!
    \file    gd32h7xx_adc.h
    \brief   definitions for the ADC

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

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

#ifndef GD32H7XX_ADC_H
#define GD32H7XX_ADC_H

#include "gd32h7xx.h"

/* ADC definitions */
#define ADC0                               ADC_BASE                                     /*!< ADC0 base address */
#define ADC1                               (ADC_BASE + 0x00000400U)                     /*!< ADC1 base address */
#define ADC2                               (ADC_BASE + 0x00000800U)                     /*!< ADC2 base address */

/* registers definitions */
#define ADC_STAT(adcx)                     REG32((adcx) + 0x00000000U)                  /*!< ADC status register */
#define ADC_CTL0(adcx)                     REG32((adcx) + 0x00000004U)                  /*!< ADC control register 0 */
#define ADC_CTL1(adcx)                     REG32((adcx) + 0x00000008U)                  /*!< ADC control register 1 */
#define ADC_IOFF0(adcx)                    REG32((adcx) + 0x0000000CU)                  /*!< ADC inserted channel data offset register 0 */
#define ADC_IOFF1(adcx)                    REG32((adcx) + 0x00000010U)                  /*!< ADC inserted channel data offset register 1 */
#define ADC_IOFF2(adcx)                    REG32((adcx) + 0x00000014U)                  /*!< ADC inserted channel data offset register 2 */
#define ADC_IOFF3(adcx)                    REG32((adcx) + 0x00000018U)                  /*!< ADC inserted channel data offset register 3 */
#define ADC_WDHT0(adcx)                    REG32((adcx) + 0x0000001CU)                  /*!< ADC watchdog high threshold register 0 */
#define ADC_WDLT0(adcx)                    REG32((adcx) + 0x00000020U)                  /*!< ADC watchdog low threshold register 0 */
#define ADC_RSQ0(adcx)                     REG32((adcx) + 0x00000024U)                  /*!< ADC regular sequence register 0 */
#define ADC_RSQ1(adcx)                     REG32((adcx) + 0x00000028U)                  /*!< ADC regular sequence register 1 */
#define ADC_RSQ2(adcx)                     REG32((adcx) + 0x0000002CU)                  /*!< ADC regular sequence register 2 */
#define ADC_RSQ3(adcx)                     REG32((adcx) + 0x00000030U)                  /*!< ADC regular sequence register 3 */
#define ADC_RSQ4(adcx)                     REG32((adcx) + 0x00000034U)                  /*!< ADC regular sequence register 4 */
#define ADC_RSQ5(adcx)                     REG32((adcx) + 0x00000038U)                  /*!< ADC regular sequence register 5 */
#define ADC_RSQ6(adcx)                     REG32((adcx) + 0x0000003CU)                  /*!< ADC regular sequence register 6 */
#define ADC_RSQ7(adcx)                     REG32((adcx) + 0x00000040U)                  /*!< ADC regular sequence register 7 */
#define ADC_RSQ8(adcx)                     REG32((adcx) + 0x00000044U)                  /*!< ADC regular sequence register 8 */
#define ADC_ISQ0(adcx)                     REG32((adcx) + 0x00000048U)                  /*!< ADC inserted sequence register 0 */
#define ADC_ISQ1(adcx)                     REG32((adcx) + 0x0000004CU)                  /*!< ADC inserted sequence register 1 */
#define ADC_ISQ2(adcx)                     REG32((adcx) + 0x00000050U)                  /*!< ADC inserted sequence register 2 */
#define ADC_IDATA0(adcx)                   REG32((adcx) + 0x00000054U)                  /*!< ADC inserted data register 0 */
#define ADC_IDATA1(adcx)                   REG32((adcx) + 0x00000058U)                  /*!< ADC inserted data register 1 */
#define ADC_IDATA2(adcx)                   REG32((adcx) + 0x0000005CU)                  /*!< ADC inserted data register 2 */
#define ADC_IDATA3(adcx)                   REG32((adcx) + 0x00000060U)                  /*!< ADC inserted data register 3 */
#define ADC_RDATA(adcx)                    REG32((adcx) + 0x00000064U)                  /*!< ADC regular data register */
#define ADC_OVSAMPCTL(adcx)                REG32((adcx) + 0x00000080U)                  /*!< ADC oversampling control register */
#define ADC_WD1SR(adcx)                    REG32((adcx) + 0x000000A0U)                  /*!< ADC watchdog 1 channel selection register */
#define ADC_WD2SR(adcx)                    REG32((adcx) + 0x000000A4U)                  /*!< ADC watchdog 2 channel selection register */
#define ADC_WDHT1(adcx)                    REG32((adcx) + 0x000000A8U)                  /*!< ADC watchdog high threshold register 1 */
#define ADC_WDLT1(adcx)                    REG32((adcx) + 0x000000ACU)                  /*!< ADC watchdog low threshold register 1 */
#define ADC_WDHT2(adcx)                    REG32((adcx) + 0x000000B0U)                  /*!< ADC watchdog high threshold register 2 */
#define ADC_WDLT2(adcx)                    REG32((adcx) + 0x000000B4U)                  /*!< ADC watchdog low threshold register 2 */
#define ADC_DIFCTL(adcx)                   REG32((adcx) + 0x000000B8U)                  /*!< ADC differential mode control register */
#define ADC_SSTAT                          REG32((ADC0) + 0x00000300U)                  /*!< ADC summary status register */
#define ADC_SYNCCTL(adcx)                  REG32((adcx) + 0x00000304U)                  /*!< ADC sync control register */
#define ADC_SYNCDATA0                      REG32((ADC0) + 0x00000308U)                  /*!< ADC sync regular data register 0 */
#define ADC_SYNCDATA1                      REG32((ADC0) + 0x0000030CU)                  /*!< ADC sync regular data register 1 */

/* bits definitions */
/* ADC_STAT */
#define ADC_STAT_WDE0                      BIT(0)                      /*!< analog watchdog 0 event flag */
#define ADC_STAT_EOC                       BIT(1)                      /*!< end of group conversion flag */
#define ADC_STAT_EOIC                      BIT(2)                      /*!< end of inserted group conversion flag */
#define ADC_STAT_STIC                      BIT(3)                      /*!< start flag of inserted channel group */
#define ADC_STAT_STRC                      BIT(4)                      /*!< start flag of regular channel group */
#define ADC_STAT_ROVF                      BIT(5)                      /*!< regular data register overflow */
#define ADC_STAT_WDE1                      BIT(30)                     /*!< analog watchdog 1 event flag */
#define ADC_STAT_WDE2                      BIT(31)                     /*!< analog watchdog 2 event flag */

/* ADC_CTL0 */
#define ADC_CTL0_WD0CHSEL                  BITS(0,4)                   /*!< analog watchdog channel select */
#define ADC_CTL0_EOCIE                     BIT(5)                      /*!< interrupt enable for EOC */
#define ADC_CTL0_WDE0IE                    BIT(6)                      /*!< interrupt enable for WDE0 */
#define ADC_CTL0_EOICIE                    BIT(7)                      /*!< interrupt enable for EOIC */
#define ADC_CTL0_SM                        BIT(8)                      /*!< scan mode */
#define ADC_CTL0_WD0SC                     BIT(9)                      /*!< when in scan mode, analog watchdog 0 is effective on a single channel */
#define ADC_CTL0_ICA                       BIT(10)                     /*!< inserted channel group convert automatically */
#define ADC_CTL0_DISRC                     BIT(11)                     /*!< discontinuous mode on regular channels */
#define ADC_CTL0_DISIC                     BIT(12)                     /*!< discontinuous mode on inserted channels */
#define ADC_CTL0_DISNUM                    BITS(13,15)                 /*!< number of conversions in discontinuous mode */
#define ADC_CTL0_IWD0EN                    BIT(22)                     /*!< inserted channel analog watchdog 0 enable */
#define ADC_CTL0_RWD0EN                    BIT(23)                     /*!< regular channel analog watchdog 0 enable */
#define ADC_CTL0_DRES                      BITS(24,25)                 /*!< ADC data resolution */
#define ADC_CTL0_ROVFIE                    BIT(26)                     /*!< interrupt enable for ROVF */
#define ADC_CTL0_WDE1IE                    BIT(30)                     /*!< interrupt enable for WDE1 */
#define ADC_CTL0_WDE2IE                    BIT(31)                     /*!< interrupt enable for WDE2 */

/* ADC_CTL1 */
#define ADC_CTL1_ADCON                     BIT(0)                      /*!< ADC on */
#define ADC_CTL1_CTN                       BIT(1)                      /*!< continuous mode */
#define ADC_CTL1_CLB                       BIT(2)                      /*!< ADC calibration */
#define ADC_CTL1_RSTCLB                    BIT(3)                      /*!< reset calibration */
#define ADC_CTL1_CALNUM                    BITS(4,6)                   /*!< ADC calibration times */
#define ADC_CTL1_DMA                       BIT(8)                      /*!< DMA request enable */
#define ADC_CTL1_DDM                       BIT(9)                      /*!< DMA disable mode */
#define ADC_CTL1_EOCM                      BIT(10)                     /*!< end of conversion mode */
#define ADC_CTL1_DAL                       BIT(11)                     /*!< data alignment */
#define ADC_CTL1_HPDFCFG                   BIT(12)                     /*!< HPDF mode configuration */
#define ADC_CTL1_ETMIC                     BITS(20,21)                 /*!< external trigger mode for inserted channels */
#define ADC_CTL1_SWICST                    BIT(22)                     /*!< software start on inserted channel */
#define ADC_CTL1_TSVEN1                    BIT(23)                     /*!< temperature sensor channel enable */
#define ADC_CTL1_INREFEN                   BIT(24)                     /*!< vrefint channel enable */
#define ADC_CTL1_VBATEN                    BIT(25)                     /*!< vbat channel enable */
#define ADC_CTL1_CALMOD                    BIT(27)                     /*!< ADC calibration mode */
#define ADC_CTL1_ETMRC                     BITS(28,29)                 /*!< external trigger mode for regular channels */
#define ADC_CTL1_SWRCST                    BIT(30)                     /*!< software start on regular channel. */
#define ADC_CTL1_TSVEN2                    BIT(31)                     /*!< high-precision temperature sensor channel enable */

/* ADC_IOFFx x=0..3 */
#define ADC_IOFFX_IOFF                     BITS(0,23)                  /*!< data offset for inserted channel x */

/* ADC_WDHT0 */
#define ADC_WDHT0_WDHT0                    BITS(0,23)                  /*!< high threshold for analog watchdog 0 */

/* ADC_WDLT0 */
#define ADC_WDLT0_WDLT0                    BITS(0,23)                  /*!< low threshold for analog watchdog 0 */

/* ADC_RSQx x=0..8 */
#define ADC_RSQX_RSQN                      BITS(0,4)                   /*!< nth conversion channel number in the regular channel group */
#define ADC_RSQX_RSMPN                     BITS(5,14)                  /*!< nth conversion sample time in the regular channel group */
#define ADC_RSQ0_RL                        BITS(20,23)                 /*!< regular channel group length */

/* ADC_ISQx x=0..2 */
#define ADC_ISQX_ISQN                      BITS(0,4)                   /*!< nth conversion channel number in the inserted channel group */
#define ADC_ISQX_ISMPN                     BITS(5,14)                  /*!< nth conversion sample time in the inserted channel group */
#define ADC_ISQ0_IL                        BITS(20,21)                 /*!< inserted channel group length */

/* ADC_IDATAx x=0..3 */
#define ADC_IDATAX_IDATAN                  BITS(0,31)                  /*!< Inserted number n conversion data */

/* ADC_RDATA */
#define ADC_RDATA_RDATA                    BITS(0,31)                  /*!< regular channel data */

/* ADC_OVSAMPCTL */
#define ADC_OVSAMPCTL_OVSEN                BIT(0)                      /*!< oversampling enable */
#define ADC_OVSAMPCTL_OVSS                 BITS(5,8)                   /*!< oversampling shift */
#define ADC_OVSAMPCTL_TOVS                 BIT(9)                      /*!< triggered oversampling */
#define ADC_OVSAMPCTL_OVSR                 BITS(16,25)                 /*!< oversampling ratio */

/* ADC_WD1SR */
#define ADC_WD1SR_AWD1CS                   BITS(0,21)                  /*!< analog watchdog 1 channel selection */

/* ADC_WD2SR */
#define ADC_WD2SR_AWD2CS                   BITS(0,21)                  /*!< analog watchdog 2 channel selection */

/* ADC_WDHT1 */
#define ADC_WDHT1_WDHT1                    BITS(0,23)                  /*!< high threshold for analog watchdog 1 */

/* ADC_WDHT1 */
#define ADC_WDLT1_WDLT1                    BITS(0,23)                  /*!< low threshold for analog watchdog 1 */

/* ADC_WDHT2 */
#define ADC_WDHT2_WDHT2                    BITS(0,23)                  /*!< high threshold for analog watchdog 2 */

/* ADC_WDHT2 */
#define ADC_WDLT2_WDLT2                    BITS(0,23)                  /*!< low threshold for analog watchdog 2 */

/* ADC_DIFCTL */
#define ADC_DIFCTL_DIFCTL                  BITS(0,21)                  /*!< Differential mode for channel 0..21 */

/* ADC_SSTAT */
#define ADC_SSTAT_ADC0_WDE0                BIT(0)                      /*!< the bit is mirror image of the WDE0 bit of ADC0 */
#define ADC_SSTAT_ADC0_WDE1                BIT(1)                      /*!< the bit is mirror image of the WDE1 bit of ADC0 */
#define ADC_SSTAT_ADC0_WDE2                BIT(2)                      /*!< the bit is mirror image of the WDE2 bit of ADC0 */
#define ADC_SSTAT_ADC0_EOC                 BIT(3)                      /*!< the bit is mirror image of the EOC bit of ADC0 */
#define ADC_SSTAT_ADC0_EOIC                BIT(4)                      /*!< the bit is mirror image of the EOIC bit of ADC0 */
#define ADC_SSTAT_ADC0_STIC                BIT(5)                      /*!< the bit is mirror image of the STIC bit of ADC0 */
#define ADC_SSTAT_ADC0_STRC                BIT(6)                      /*!< the bit is mirror image of the STRC bit of ADC0 */
#define ADC_SSTAT_ADC0_ROVF                BIT(7)                      /*!< the bit is mirror image of the ROVF bit of ADC0 */
#define ADC_SSTAT_ADC1_WDE0                BIT(8)                      /*!< the bit is mirror image of the WDE0 bit of ADC1 */
#define ADC_SSTAT_ADC1_WDE1                BIT(9)                      /*!< the bit is mirror image of the WDE1 bit of ADC1 */
#define ADC_SSTAT_ADC1_WDE2                BIT(10)                     /*!< the bit is mirror image of the WDE2 bit of ADC1 */
#define ADC_SSTAT_ADC1_EOC                 BIT(11)                     /*!< the bit is mirror image of the EOC bit of ADC1 */
#define ADC_SSTAT_ADC1_EOIC                BIT(12)                     /*!< the bit is mirror image of the EOIC bit of ADC1 */
#define ADC_SSTAT_ADC1_STIC                BIT(13)                     /*!< the bit is mirror image of the STIC bit of ADC1 */
#define ADC_SSTAT_ADC1_STRC                BIT(14)                     /*!< the bit is mirror image of the STRC bit of ADC1 */
#define ADC_SSTAT_ADC1_ROVF                BIT(15)                     /*!< the bit is mirror image of the ROVF bit of ADC1 */
#define ADC_SSTAT_ADC2_WDE0                BIT(16)                     /*!< the bit is mirror image of the WDE0 bit of ADC2 */
#define ADC_SSTAT_ADC2_WDE1                BIT(17)                     /*!< the bit is mirror image of the WDE1 bit of ADC2 */
#define ADC_SSTAT_ADC2_WDE2                BIT(18)                     /*!< the bit is mirror image of the WDE2 bit of ADC2 */
#define ADC_SSTAT_ADC2_EOC                 BIT(19)                     /*!< the bit is mirror image of the EOC bit of ADC2 */
#define ADC_SSTAT_ADC2_EOIC                BIT(20)                     /*!< the bit is mirror image of the EOIC bit of ADC2 */
#define ADC_SSTAT_ADC2_STIC                BIT(21)                     /*!< the bit is mirror image of the STIC bit of ADC2 */
#define ADC_SSTAT_ADC2_STRC                BIT(22)                     /*!< the bit is mirror image of the STRC bit of ADC2 */
#define ADC_SSTAT_ADC2_ROVF                BIT(23)                     /*!< the bit is mirror image of the ROVF bit of ADC2 */

/* ADC_SYNCCTL */
#define ADC_SYNCCTL_SYNCM                  BITS(0,3)                   /*!< ADC sync mode */
#define ADC_SYNCCTL_SYNCDLY                BITS(8,11)                  /*!< ADC sync delay */
#define ADC_SYNCCTL_SYNCDDM                BIT(13)                     /*!< ADC sync DMA disable mode */
#define ADC_SYNCCTL_SYNCDMA                BITS(14,15)                 /*!< ADC sync DMA mode selection */
#define ADC_SYNCCTL_ADCSCK                 BITS(16,19)                 /*!< ADC sync clock mode */
#define ADC_SYNCCTL_ADCCK                  BITS(20,23)                 /*!< ADC clock prescaler */

/* ADC_SYNCDATA0 */
#define ADC_SYNCDATA0_SYNCDATA0            BITS(0,15)                  /*!< ADC0 regular data in ADC synchronization mode */
#define ADC_SYNCDATA0_SYNCDATA1            BITS(16,31)                 /*!< ADC1 regular data in ADC synchronization mode */

/* constants definitions */
/* ADC status flag */
#define ADC_FLAG_WDE0                      ADC_STAT_WDE0               /*!< analog watchdog 0 event flag */
#define ADC_FLAG_EOC                       ADC_STAT_EOC                /*!< end of group conversion flag */
#define ADC_FLAG_EOIC                      ADC_STAT_EOIC               /*!< end of inserted group conversion flag */
#define ADC_FLAG_STIC                      ADC_STAT_STIC               /*!< start flag of inserted channel group */
#define ADC_FLAG_STRC                      ADC_STAT_STRC               /*!< start flag of regular channel group */
#define ADC_FLAG_ROVF                      ADC_STAT_ROVF               /*!< regular data register overflow */
#define ADC_FLAG_WDE1                      ADC_STAT_WDE1               /*!< analog watchdog 1 event flag */
#define ADC_FLAG_WDE2                      ADC_STAT_WDE2               /*!< analog watchdog 2 event flag */

/* ADC interrupt */
#define ADC_INT_WDE0                       ADC_CTL0_WDE0IE             /*!< interrupt enable for WDE0 */
#define ADC_INT_EOC                        ADC_CTL0_EOCIE              /*!< interrupt enable for EOC */
#define ADC_INT_EOIC                       ADC_CTL0_EOICIE             /*!< interrupt enable for EOIC */
#define ADC_INT_ROVF                       ADC_CTL0_ROVFIE             /*!< interrupt enable for ROVF */
#define ADC_INT_WDE1                       ADC_CTL0_WDE1IE             /*!< interrupt enable for WDE1 */
#define ADC_INT_WDE2                       ADC_CTL0_WDE2IE             /*!< interrupt enable for WDE2 */

/* ADC interrupt flag */
#define ADC_INT_FLAG_WDE0                  ADC_STAT_WDE0               /*!< analog watchdog 0 event interrupt flag */
#define ADC_INT_FLAG_EOC                   ADC_STAT_EOC                /*!< end of group conversion interrupt flag */
#define ADC_INT_FLAG_EOIC                  ADC_STAT_EOIC               /*!< end of inserted group conversion interrupt flag */
#define ADC_INT_FLAG_ROVF                  ADC_STAT_ROVF               /*!< regular data register overflow interrupt flag */
#define ADC_INT_FLAG_WDE1                  ADC_STAT_WDE1               /*!< analog watchdog 1 event interrupt flag */
#define ADC_INT_FLAG_WDE2                  ADC_STAT_WDE2               /*!< analog watchdog 2 event interrupt flag */

/* number of conversions in discontinuous mode */
#define CTL0_DISNUM(regval)                (BITS(13,15) & ((uint32_t)(regval) << 13U))  /*!< write value to ADC_CTL0_DISNUM bit field */

/* ADC special function definitions */
#define ADC_SCAN_MODE                      ADC_CTL0_SM                                  /*!< scan mode */
#define ADC_INSERTED_CHANNEL_AUTO          ADC_CTL0_ICA                                 /*!< inserted channel group convert automatically */
#define ADC_CONTINUOUS_MODE                ADC_CTL1_CTN                                 /*!< continuous mode */

/* ADC calibration mode */
#define ADC_CALIBRATION_OFFSET_MISMATCH    ((uint32_t)0x00000000U)                      /*!< ADC calibration offset and mismatch mode */
#define ADC_CALIBRATION_OFFSET             ADC_CTL1_CALMOD                              /*!< ADC calibration mode */

/* ADC calibration times */
#define CTL1_CALNUM(regval)                (BITS(4,6) & ((uint32_t)(regval) << 4U))     /*!< write value to ADC_CTL1_CLBNUM bit field */
#define ADC_CALIBRATION_NUM1               CTL1_CALNUM(0)                               /*!< ADC calibration 1 time */
#define ADC_CALIBRATION_NUM2               CTL1_CALNUM(1)                               /*!< ADC calibration 2 times */
#define ADC_CALIBRATION_NUM4               CTL1_CALNUM(2)                               /*!< ADC calibration 4 times */
#define ADC_CALIBRATION_NUM8               CTL1_CALNUM(3)                               /*!< ADC calibration 8 times */
#define ADC_CALIBRATION_NUM16              CTL1_CALNUM(4)                               /*!< ADC calibration 16 times */
#define ADC_CALIBRATION_NUM32              CTL1_CALNUM(5)                               /*!< ADC calibration 32 times */

/* ADC data alignment */
#define ADC_DATAALIGN_RIGHT                ((uint32_t)0x00000000U)                      /*!< LSB alignment */
#define ADC_DATAALIGN_LEFT                 ADC_CTL1_DAL                                 /*!< MSB alignment */

/* end of conversion mode */
#define ADC_EOC_SET_SEQUENCE               ((uint32_t)0x00000000U)                      /*!< only at the end of a sequence of regular conversions, the EOC bit is set */
#define ADC_EOC_SET_CONVERSION             ADC_CTL1_EOCM                                /*!< at the end of each regular conversion, the EOC bit is set */

/* ADC internal channel definitions */
#define ADC_CHANNEL_INTERNAL_TEMPSENSOR            ADC_CTL1_TSVEN1                      /*!< temperature sensor channel */
#define ADC_CHANNEL_INTERNAL_VREFINT               ADC_CTL1_INREFEN                     /*!< vrefint channel */
#define ADC_CHANNEL_INTERNAL_VBAT                  ADC_CTL1_VBATEN                      /*!< vbat channel */
#define ADC_CHANNEL_INTERNAL_HP_TEMPSENSOR         ADC_CTL1_TSVEN2                      /*!< high-precision temperature sensor channel */

/* ADC data offset for inserted channel x */
#define IOFFX_IOFF(regval)                 (BITS(0,23) & ((uint32_t)(regval) << 0U))    /*!< write value to ADC_IOFFX_IOFF bit field */

/* ADC high threshold for analog watchdog 0 */
#define WDHT0_WDHT0(regval)                (BITS(0,23) & ((uint32_t)(regval) << 0U))    /*!< write value to ADC_WDHT0_WDHT0 bit field */

/* ADC low threshold for analog watchdog 0 */
#define WDLT0_WDLT0(regval)                (BITS(0,23) & ((uint32_t)(regval) << 0U))    /*!< write value to ADC_WDLT0_WDLT0 bit field */

/* ADC high threshold for analog watchdog 1 */
#define WDHT1_WDHT1(regval)                (BITS(0,23) & ((uint32_t)(regval) << 0U))    /*!< write value to ADC_WDHT1_WDHT1 bit field */

/* ADC low threshold for analog watchdog 1 */
#define WDLT1_WDLT1(regval)                (BITS(0,23) & ((uint32_t)(regval) << 0U))    /*!< write value to ADC_WDLT1_WDLT1 bit field */

/* ADC high threshold for analog watchdog 2 */
#define WDHT2_WDHT2(regval)                (BITS(0,23) & ((uint32_t)(regval) << 0U))    /*!< write value to ADC_WDHT2_WDHT2 bit field */

/* ADC low threshold for analog watchdog 2 */
#define WDLT2_WDLT2(regval)                (BITS(0,23) & ((uint32_t)(regval) << 0U))    /*!< write value to ADC_WDLT2_WDLT2 bit field */

/* ADC sequence sample time */
#define SQX_SMP(regval)                    (BITS(5,14) & ((uint32_t)(regval) << 5U))    /*!< write value to RSQX_SMPn or ISQX_SMPn bit field */

/* ADC regular channel group length */
#define RSQ0_RL(regval)                    (BITS(20,23) & ((uint32_t)(regval) << 20U))  /*!< write value to ADC_RSQ0_RL bit field */

/* ADC inserted channel group length */
#define ISQ0_IL(regval)                    (BITS(20,21) & ((uint32_t)(regval) << 20U))  /*!< write value to ADC_ISQ0_IL bit field */

/* ADC resolution */
#define CTL0_DRES(regval)                  (BITS(24,25) & ((uint32_t)(regval) << 24U))  /*!< write value to ADC_CTL0_DRES bit field */
#define ADC_RESOLUTION_14B                 ((uint8_t)0x00U)                             /*!< 14-bit ADC resolution */
#define ADC_RESOLUTION_12B                 ((uint8_t)0x01U)                             /*!< 12-bit ADC resolution */
#define ADC_RESOLUTION_10B                 ((uint8_t)0x02U)                             /*!< 10-bit ADC resolution */
#define ADC_RESOLUTION_8B                  ((uint8_t)0x03U)                             /*!< 8-bit ADC resolution */
#define ADC_RESOLUTION_6B                  ((uint8_t)0x04U)                             /*!< 6-bit ADC resolution */

/* oversampling shift */
#define OVSCR_OVSS(regval)                 (BITS(5,8) & ((uint32_t)(regval) << 5U))     /*!< write value to ADC_OVSAMPCTL_OVSS bit field */
#define ADC_OVERSAMPLING_SHIFT_NONE        OVSCR_OVSS(0)                                /*!< no oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_1B          OVSCR_OVSS(1)                                /*!< 1-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_2B          OVSCR_OVSS(2)                                /*!< 2-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_3B          OVSCR_OVSS(3)                                /*!< 3-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_4B          OVSCR_OVSS(4)                                /*!< 4-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_5B          OVSCR_OVSS(5)                                /*!< 5-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_6B          OVSCR_OVSS(6)                                /*!< 6-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_7B          OVSCR_OVSS(7)                                /*!< 7-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_8B          OVSCR_OVSS(8)                                /*!< 8-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_9B          OVSCR_OVSS(9)                                /*!< 9-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_10B         OVSCR_OVSS(10)                               /*!< 10-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_11B         OVSCR_OVSS(11)                               /*!< 11-bit oversampling shift */

/* oversampling ratio */
#define OVSCR_OVSR(regval)                 (BITS(16,25) & ((uint32_t)(regval) << 16U))  /*!< write value to ADC_OVSAMPCTL_OVSR bit field */

/* triggered oversampling */
#define ADC_OVERSAMPLING_ALL_CONVERT       ((uint32_t)0x00000000U)                      /*!< all oversampled conversions for a channel are done consecutively after a trigger */
#define ADC_OVERSAMPLING_ONE_CONVERT       ADC_OVSAMPCTL_TOVS                           /*!< each oversampled conversion for a channel needs a trigger */

/* configure the ADC clock */
#define SYNCCTL_ADCSCK(regval)              (BITS(16,19) & ((uint32_t)(regval) << 16U)) /*!< write value to ADC_SYNCCTL_ADCSCK bit field */
#define SYNCCTL_ADCCK(regval)              (BITS(20,23) & ((uint32_t)(regval) << 20U))  /*!< write value to ADC_SYNCCTL_ADCCK bit field */
#define ADC_CLK_SYNC_HCLK_DIV2             (SYNCCTL_ADCCK(0) | SYNCCTL_ADCSCK(8))       /*!< ADC sync clock mode HCLK div2 */
#define ADC_CLK_SYNC_HCLK_DIV4             (SYNCCTL_ADCCK(0) | SYNCCTL_ADCSCK(9))       /*!< ADC sync clock mode HCLK div4 */
#define ADC_CLK_SYNC_HCLK_DIV6             (SYNCCTL_ADCCK(0) | SYNCCTL_ADCSCK(10))      /*!< ADC sync clock mode HCLK div6 */
#define ADC_CLK_SYNC_HCLK_DIV8             (SYNCCTL_ADCCK(0) | SYNCCTL_ADCSCK(11))      /*!< ADC sync clock mode HCLK div8 */
#define ADC_CLK_SYNC_HCLK_DIV10            (SYNCCTL_ADCCK(0) | SYNCCTL_ADCSCK(12))      /*!< ADC sync clock mode HCLK div10 */
#define ADC_CLK_SYNC_HCLK_DIV12            (SYNCCTL_ADCCK(0) | SYNCCTL_ADCSCK(13))      /*!< ADC sync clock mode HCLK div12 */
#define ADC_CLK_SYNC_HCLK_DIV14            (SYNCCTL_ADCCK(0) | SYNCCTL_ADCSCK(14))      /*!< ADC sync clock mode HCLK div14 */
#define ADC_CLK_SYNC_HCLK_DIV16            (SYNCCTL_ADCCK(0) | SYNCCTL_ADCSCK(15))      /*!< ADC sync clock mode HCLK div16 */
#define ADC_CLK_ASYNC_DIV1                 (SYNCCTL_ADCCK(0) | SYNCCTL_ADCSCK(0))       /*!< ADC async clock mode div1 */
#define ADC_CLK_ASYNC_DIV2                 (SYNCCTL_ADCCK(1) | SYNCCTL_ADCSCK(0))       /*!< ADC async clock mode div2 */
#define ADC_CLK_ASYNC_DIV4                 (SYNCCTL_ADCCK(2) | SYNCCTL_ADCSCK(0))       /*!< ADC async clock mode div4 */
#define ADC_CLK_ASYNC_DIV6                 (SYNCCTL_ADCCK(3) | SYNCCTL_ADCSCK(0))       /*!< ADC async clock mode div6 */
#define ADC_CLK_ASYNC_DIV8                 (SYNCCTL_ADCCK(4) | SYNCCTL_ADCSCK(0))       /*!< ADC async clock mode div8 */
#define ADC_CLK_ASYNC_DIV10                (SYNCCTL_ADCCK(5) | SYNCCTL_ADCSCK(0))       /*!< ADC async clock mode div10 */
#define ADC_CLK_ASYNC_DIV12                (SYNCCTL_ADCCK(6) | SYNCCTL_ADCSCK(0))       /*!< ADC async clock mode div12 */
#define ADC_CLK_ASYNC_DIV16                (SYNCCTL_ADCCK(7) | SYNCCTL_ADCSCK(0))       /*!< ADC async clock mode div16 */
#define ADC_CLK_ASYNC_DIV32                (SYNCCTL_ADCCK(8) | SYNCCTL_ADCSCK(0))       /*!< ADC async clock mode div32 */
#define ADC_CLK_ASYNC_DIV64                (SYNCCTL_ADCCK(9) | SYNCCTL_ADCSCK(0))       /*!< ADC async clock mode div64 */
#define ADC_CLK_ASYNC_DIV128               (SYNCCTL_ADCCK(10) | SYNCCTL_ADCSCK(0))      /*!< ADC async clock mode div128 */
#define ADC_CLK_ASYNC_DIV256               (SYNCCTL_ADCCK(11) | SYNCCTL_ADCSCK(0))      /*!< ADC async clock mode div256 */

/* ADC sync DMA mode selection */
#define SYNCCTL_SYNCDMA(regval)            (BITS(14,15) & ((uint32_t)(regval) << 14U))  /*!< write value to ADC_SYNCCTL_SYNCDMA bit field */
#define ADC_SYNC_DMA_DISABLE               SYNCCTL_SYNCDMA(0)                           /*!< ADC sync DMA disabled */
#define ADC_SYNC_DMA_MODE0                 SYNCCTL_SYNCDMA(1)                           /*!< ADC sync DMA mode 0 */
#define ADC_SYNC_DMA_MODE1                 SYNCCTL_SYNCDMA(2)                           /*!< ADC sync DMA mode 1 */

/* ADC sync delay */
#define SYNCCTL_SYNCDLY(regval)            (BITS(8,11) & ((uint32_t)(regval) << 8U))    /*!< write value to ADC_SYNCCTL_SYNCDLY bit field */
#define ADC_SYNC_DELAY_5CYCLE              SYNCCTL_SYNCDLY(0)                           /*!< the delay between 2 sampling phases in ADC synchronization modes to 5 ADC clock cycles. */
#define ADC_SYNC_DELAY_6CYCLE              SYNCCTL_SYNCDLY(1)                           /*!< the delay between 2 sampling phases in ADC synchronization modes to 6 ADC clock cycles. */
#define ADC_SYNC_DELAY_7CYCLE              SYNCCTL_SYNCDLY(2)                           /*!< the delay between 2 sampling phases in ADC synchronization modes to 7 ADC clock cycles. */
#define ADC_SYNC_DELAY_8CYCLE              SYNCCTL_SYNCDLY(3)                           /*!< the delay between 2 sampling phases in ADC synchronization modes to 8 ADC clock cycles. */
#define ADC_SYNC_DELAY_9CYCLE              SYNCCTL_SYNCDLY(4)                           /*!< the delay between 2 sampling phases in ADC synchronization modes to 9 ADC clock cycles. */
#define ADC_SYNC_DELAY_10CYCLE             SYNCCTL_SYNCDLY(5)                           /*!< the delay between 2 sampling phases in ADC synchronization modes to 10 ADC clock cycles. */
#define ADC_SYNC_DELAY_11CYCLE             SYNCCTL_SYNCDLY(6)                           /*!< the delay between 2 sampling phases in ADC synchronization modes to 11 ADC clock cycles. */
#define ADC_SYNC_DELAY_12CYCLE             SYNCCTL_SYNCDLY(7)                           /*!< the delay between 2 sampling phases in ADC synchronization modes to 12 ADC clock cycles. */
#define ADC_SYNC_DELAY_13CYCLE             SYNCCTL_SYNCDLY(8)                           /*!< the delay between 2 sampling phases in ADC synchronization modes to 13 ADC clock cycles. */
#define ADC_SYNC_DELAY_14CYCLE             SYNCCTL_SYNCDLY(9)                           /*!< the delay between 2 sampling phases in ADC synchronization modes to 14 ADC clock cycles. */
#define ADC_SYNC_DELAY_15CYCLE             SYNCCTL_SYNCDLY(10)                          /*!< the delay between 2 sampling phases in ADC synchronization modes to 15 ADC clock cycles. */
#define ADC_SYNC_DELAY_16CYCLE             SYNCCTL_SYNCDLY(11)                          /*!< the delay between 2 sampling phases in ADC synchronization modes to 16 ADC clock cycles. */
#define ADC_SYNC_DELAY_17CYCLE             SYNCCTL_SYNCDLY(12)                          /*!< the delay between 2 sampling phases in ADC synchronization modes to 17 ADC clock cycles. */
#define ADC_SYNC_DELAY_18CYCLE             SYNCCTL_SYNCDLY(13)                          /*!< the delay between 2 sampling phases in ADC synchronization modes to 18 ADC clock cycles. */
#define ADC_SYNC_DELAY_19CYCLE             SYNCCTL_SYNCDLY(14)                          /*!< the delay between 2 sampling phases in ADC synchronization modes to 19 ADC clock cycles. */
#define ADC_SYNC_DELAY_20CYCLE             SYNCCTL_SYNCDLY(15)                          /*!< the delay between 2 sampling phases in ADC synchronization modes to 20 ADC clock cycles. */

/* ADC sync mode */
#define SYNCCTL_SYNCM(regval)              (BITS(0,3) & ((uint32_t)(regval) << 0U))     /*!< write value to ADC_SYNCCTL_SYNCM bit field */
#define ADC_SYNC_MODE_INDEPENDENT                           SYNCCTL_SYNCM(0)            /*!< ADC synchronization mode disabled.All the ADCs work independently */
#define ADC_DAUL_REGULAL_PARALLEL_INSERTED_PARALLEL         SYNCCTL_SYNCM(1)            /*!< combined regular parallel & inserted parallel mode */
#define ADC_DAUL_REGULAL_PARALLEL_INSERTED_ROTATION         SYNCCTL_SYNCM(2)            /*!< combined regular parallel & trigger rotation mode */
#define ADC_DAUL_INSERTED_PARALLEL                          SYNCCTL_SYNCM(5)            /*!< inserted parallel mode */
#define ADC_DAUL_REGULAL_PARALLEL                           SYNCCTL_SYNCM(6)            /*!< regular parallel mode */
#define ADC_DAUL_REGULAL_FOLLOW_UP                          SYNCCTL_SYNCM(7)            /*!< follow-up mode */
#define ADC_DAUL_INSERTED_TRIGGER_ROTATION                  SYNCCTL_SYNCM(9)            /*!< trigger rotation mode */

/* external trigger mode for regular and inserted  channel */
#define EXTERNAL_TRIGGER_DISABLE           ((uint32_t)0x00000000U)                      /*!< external trigger disable */
#define EXTERNAL_TRIGGER_RISING            ((uint32_t)0x00000001U)                      /*!< rising edge of external trigger */
#define EXTERNAL_TRIGGER_FALLING           ((uint32_t)0x00000002U)                      /*!< falling edge of external trigger */
#define EXTERNAL_TRIGGER_RISING_FALLING    ((uint32_t)0x00000003U)                      /*!< rising and falling edge of external trigger */

/* ADC channel group definitions */
#define ADC_REGULAR_CHANNEL                ((uint8_t)0x01U)                             /*!< ADC regular channel group */
#define ADC_INSERTED_CHANNEL               ((uint8_t)0x02U)                             /*!< ADC inserted channel group */
#define ADC_REGULAR_INSERTED_CHANNEL       ((uint8_t)0x03U)                             /*!< both regular and inserted channel group */
#define ADC_CHANNEL_DISCON_DISABLE         ((uint8_t)0x04U)                             /*!< disable discontinuous mode of regular & inserted channel */

/* ADC inserted channel definitions */
#define ADC_INSERTED_CHANNEL_0             ((uint8_t)0x00U)                             /*!< ADC inserted channel 0 */
#define ADC_INSERTED_CHANNEL_1             ((uint8_t)0x01U)                             /*!< ADC inserted channel 1 */
#define ADC_INSERTED_CHANNEL_2             ((uint8_t)0x02U)                             /*!< ADC inserted channel 2 */
#define ADC_INSERTED_CHANNEL_3             ((uint8_t)0x03U)                             /*!< ADC inserted channel 3 */

/* ADC channel definitions */
#define ADC_CHANNEL_0                      ((uint8_t)0x00U)                             /*!< ADC channel 0 */
#define ADC_CHANNEL_1                      ((uint8_t)0x01U)                             /*!< ADC channel 1 */
#define ADC_CHANNEL_2                      ((uint8_t)0x02U)                             /*!< ADC channel 2 */
#define ADC_CHANNEL_3                      ((uint8_t)0x03U)                             /*!< ADC channel 3 */
#define ADC_CHANNEL_4                      ((uint8_t)0x04U)                             /*!< ADC channel 4 */
#define ADC_CHANNEL_5                      ((uint8_t)0x05U)                             /*!< ADC channel 5 */
#define ADC_CHANNEL_6                      ((uint8_t)0x06U)                             /*!< ADC channel 6 */
#define ADC_CHANNEL_7                      ((uint8_t)0x07U)                             /*!< ADC channel 7 */
#define ADC_CHANNEL_8                      ((uint8_t)0x08U)                             /*!< ADC channel 8 */
#define ADC_CHANNEL_9                      ((uint8_t)0x09U)                             /*!< ADC channel 9 */
#define ADC_CHANNEL_10                     ((uint8_t)0x0AU)                             /*!< ADC channel 10 */
#define ADC_CHANNEL_11                     ((uint8_t)0x0BU)                             /*!< ADC channel 11 */
#define ADC_CHANNEL_12                     ((uint8_t)0x0CU)                             /*!< ADC channel 12 */
#define ADC_CHANNEL_13                     ((uint8_t)0x0DU)                             /*!< ADC channel 13 */
#define ADC_CHANNEL_14                     ((uint8_t)0x0EU)                             /*!< ADC channel 14 */
#define ADC_CHANNEL_15                     ((uint8_t)0x0FU)                             /*!< ADC channel 15 */
#define ADC_CHANNEL_16                     ((uint8_t)0x10U)                             /*!< ADC channel 16 */
#define ADC_CHANNEL_17                     ((uint8_t)0x11U)                             /*!< ADC channel 17 */
#define ADC_CHANNEL_18                     ((uint8_t)0x12U)                             /*!< ADC channel 18 */
#define ADC_CHANNEL_19                     ((uint8_t)0x13U)                             /*!< ADC channel 19 */
#define ADC_CHANNEL_20                     ((uint8_t)0x14U)                             /*!< ADC channel 20 */

/* analog watchdog 1/2 channel selection for channel n(n=0..20) */
#define ADC_AWD1_2_SELECTION_CHANNEL_0             ((uint32_t)0x00000001U)              /*!< ADC channel 0 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_1             ((uint32_t)0x00000002U)              /*!< ADC channel 1 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_2             ((uint32_t)0x00000004U)              /*!< ADC channel 2 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_3             ((uint32_t)0x00000008U)              /*!< ADC channel 3 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_4             ((uint32_t)0x00000010U)              /*!< ADC channel 4 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_5             ((uint32_t)0x00000020U)              /*!< ADC channel 5 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_6             ((uint32_t)0x00000040U)              /*!< ADC channel 6 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_7             ((uint32_t)0x00000080U)              /*!< ADC channel 7 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_8             ((uint32_t)0x00000100U)              /*!< ADC channel 8 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_9             ((uint32_t)0x00000200U)              /*!< ADC channel 9 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_10            ((uint32_t)0x00000400U)              /*!< ADC channel 10 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_11            ((uint32_t)0x00000800U)              /*!< ADC channel 11 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_12            ((uint32_t)0x00001000U)              /*!< ADC channel 12 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_13            ((uint32_t)0x00002000U)              /*!< ADC channel 13 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_14            ((uint32_t)0x00004000U)              /*!< ADC channel 14 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_15            ((uint32_t)0x00008000U)              /*!< ADC channel 15 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_16            ((uint32_t)0x00010000U)              /*!< ADC channel 16 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_17            ((uint32_t)0x00020000U)              /*!< ADC channel 17 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_18            ((uint32_t)0x00040000U)              /*!< ADC channel 18 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_19            ((uint32_t)0x00080000U)              /*!< ADC channel 19 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_20            ((uint32_t)0x00100000U)              /*!< ADC channel 20 analog watchdog 1/2 selection */
#define ADC_AWD1_2_SELECTION_CHANNEL_ALL           ((uint32_t)0x003FFFFFU)              /*!< all ADC channels analog watchdog 1/2 selection */

/* Differential mode for channel n(n=0..21) */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_0            ((uint32_t)0x00000001U)              /*!< ADC channel 0 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_1            ((uint32_t)0x00000002U)              /*!< ADC channel 1 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_2            ((uint32_t)0x00000004U)              /*!< ADC channel 2 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_3            ((uint32_t)0x00000008U)              /*!< ADC channel 3 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_4            ((uint32_t)0x00000010U)              /*!< ADC channel 4 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_5            ((uint32_t)0x00000020U)              /*!< ADC channel 5 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_6            ((uint32_t)0x00000040U)              /*!< ADC channel 6 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_7            ((uint32_t)0x00000080U)              /*!< ADC channel 7 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_8            ((uint32_t)0x00000100U)              /*!< ADC channel 8 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_9            ((uint32_t)0x00000200U)              /*!< ADC channel 9 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_10           ((uint32_t)0x00000400U)              /*!< ADC channel 10 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_11           ((uint32_t)0x00000800U)              /*!< ADC channel 11 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_12           ((uint32_t)0x00001000U)              /*!< ADC channel 12 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_13           ((uint32_t)0x00002000U)              /*!< ADC channel 13 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_14           ((uint32_t)0x00004000U)              /*!< ADC channel 14 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_15           ((uint32_t)0x00008000U)              /*!< ADC channel 15 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_16           ((uint32_t)0x00010000U)              /*!< ADC channel 16 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_17           ((uint32_t)0x00020000U)              /*!< ADC channel 17 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_18           ((uint32_t)0x00040000U)              /*!< ADC channel 18 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_19           ((uint32_t)0x00080000U)              /*!< ADC channel 19 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_20           ((uint32_t)0x00100000U)              /*!< ADC channel 20 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_21           ((uint32_t)0x00200000U)              /*!< ADC channel 21 differential mode */
#define ADC_DIFFERENTIAL_MODE_CHANNEL_ALL          ((uint32_t)0x003FFFFFU)              /*!< all ADC channels differential mode */

/* function declarations */
/* initialization config */
/* reset ADC */
void adc_deinit(uint32_t adc_periph);
/* configure the ADC clock */
void adc_clock_config(uint32_t adc_periph, uint32_t prescaler);
/* enable or disable ADC special function */
void adc_special_function_config(uint32_t adc_periph, uint32_t function, ControlStatus newvalue);
/* configure ADC data alignment */
void adc_data_alignment_config(uint32_t adc_periph, uint32_t data_alignment);
/* enable ADC interface */
void adc_enable(uint32_t adc_periph);
/* disable ADC interface */
void adc_disable(uint32_t adc_periph);
/* configure ADC calibration mode */
void adc_calibration_mode_config(uint32_t adc_periph, uint32_t clb_mode);
/* configure ADC calibration number */
void adc_calibration_number(uint32_t adc_periph, uint32_t clb_num);
/* ADC calibration and reset calibration */
void adc_calibration_enable(uint32_t adc_periph);
/* configure ADC resolution */
void adc_resolution_config(uint32_t adc_periph, uint32_t resolution);
/* enable or disable ADC internal channels */
void adc_internal_channel_config(uint32_t internal_channel, ControlStatus newvalue);

/* DMA config */
/* enable DMA request */
void adc_dma_mode_enable(uint32_t adc_periph);
/* disable DMA request */
void adc_dma_mode_disable(uint32_t adc_periph);
/* when DMA=1, the DMA engine issues a request at end of each regular conversion */
void adc_dma_request_after_last_enable(uint32_t adc_periph);
/* the DMA engine is disabled after the end of transfer signal from DMA controller is detected */
void adc_dma_request_after_last_disable(uint32_t adc_periph);
/* enable hpdf mode */
void adc_hpdf_mode_enable(uint32_t adc_periph);
/* disable hpdf mode */
void adc_hpdf_mode_disable(uint32_t adc_periph);

/* regular group and inserted group config */
/* configure ADC discontinuous mode */
void adc_discontinuous_mode_config(uint32_t adc_periph, uint8_t adc_channel_group, uint32_t length);
/* configure the length of regular channel group or inserted channel group */
void adc_channel_length_config(uint32_t adc_periph, uint8_t adc_channel_group, uint32_t length);
/* configure ADC regular channel */
void adc_regular_channel_config(uint32_t adc_periph, uint8_t rank, uint8_t adc_channel, uint32_t sample_time);
/* configure ADC inserted channel */
void adc_inserted_channel_config(uint32_t adc_periph, uint8_t rank, uint8_t adc_channel, uint32_t sample_time);
/* configure ADC inserted channel offset */
void adc_inserted_channel_offset_config(uint32_t adc_periph, uint8_t inserted_channel, uint32_t offset);
/* configure differential mode for channel */
void adc_channel_differential_mode_config(uint32_t adc_periph, uint32_t adc_channel, ControlStatus newvalue);
/* enable ADC external trigger */
void adc_external_trigger_config(uint32_t adc_periph, uint8_t adc_channel_group, uint32_t trigger_mode);
/* enable ADC software trigger */
void adc_software_trigger_enable(uint32_t adc_periph, uint8_t adc_channel_group);
/* configure end of conversion mode */
void adc_end_of_conversion_config(uint32_t adc_periph, uint32_t end_selection);

/* get channel data */
/* read ADC regular group data register */
uint32_t adc_regular_data_read(uint32_t adc_periph);
/* read ADC inserted group data register */
uint32_t adc_inserted_data_read(uint32_t adc_periph, uint8_t inserted_channel);

/* ADC analog watchdog functions */
/* configure ADC analog watchdog 0 single channel */
void adc_watchdog0_single_channel_enable(uint32_t adc_periph, uint8_t adc_channel);
/* configure ADC analog watchdog 0 group channel */
void adc_watchdog0_group_channel_enable(uint32_t adc_periph, uint8_t adc_channel_group);
/* disable ADC analog watchdog 0 */
void adc_watchdog0_disable(uint32_t adc_periph);
/* configure ADC analog watchdog 1 channel */
void adc_watchdog1_channel_config(uint32_t adc_periph, uint32_t selection_channel, ControlStatus newvalue);
/* configure ADC analog watchdog 2 channel */
void adc_watchdog2_channel_config(uint32_t adc_periph, uint32_t selection_channel, ControlStatus newvalue);
/* disable ADC analog watchdog 1 */
void adc_watchdog1_disable(uint32_t adc_periph);
/* disable ADC analog watchdog 2 */
void adc_watchdog2_disable(uint32_t adc_periph);
/* configure ADC analog watchdog 0 threshold */
void adc_watchdog0_threshold_config(uint32_t adc_periph, uint32_t low_threshold, uint32_t high_threshold);
/* configure ADC analog watchdog 1 threshold */
void adc_watchdog1_threshold_config(uint32_t adc_periph, uint32_t low_threshold, uint32_t high_threshold);
/* configure ADC analog watchdog 2 threshold */
void adc_watchdog2_threshold_config(uint32_t adc_periph, uint32_t low_threshold, uint32_t high_threshold);

/* ADC oversample functions */
/* configure ADC oversample mode */
void adc_oversample_mode_config(uint32_t adc_periph, uint32_t mode, uint16_t shift, uint16_t ratio);
/* enable ADC oversample mode */
void adc_oversample_mode_enable(uint32_t adc_periph);
/* disable ADC oversample mode */
void adc_oversample_mode_disable(uint32_t adc_periph);

/* flag and interrupt functions */
/* get the ADC flag bits */
FlagStatus adc_flag_get(uint32_t adc_periph, uint32_t flag);
/* clear the ADC flag bits */
void adc_flag_clear(uint32_t adc_periph, uint32_t flag);
/* enable ADC interrupt */
void adc_interrupt_enable(uint32_t adc_periph, uint32_t interrupt);
/* disable ADC interrupt */
void adc_interrupt_disable(uint32_t adc_periph, uint32_t interrupt);
/* get the ADC interrupt bits */
FlagStatus adc_interrupt_flag_get(uint32_t adc_periph, uint32_t int_flag);
/* clear the ADC flag */
void adc_interrupt_flag_clear(uint32_t adc_periph, uint32_t int_flag);

/* ADC synchronization */
/* configure the ADC sync mode */
void adc_sync_mode_config(uint32_t sync_mode);
/* configure the delay between 2 sampling phases in ADC sync modes */
void adc_sync_delay_config(uint32_t sample_delay);
/* configure ADC sync DMA mode selection */
void adc_sync_dma_config(uint32_t dma_mode);
/* configure ADC sync DMA engine issues requests according to the SYNCDMA bits */
void adc_sync_dma_request_after_last_enable(void);
/* configure ADC sync DMA engine is disabled after the end of transfer signal from DMA controller is detected */
void adc_sync_dma_request_after_last_disable(void);
/* read ADC sync master adc regular data register 0 */
uint32_t adc_sync_master_adc_regular_data0_read(void);
/* read ADC sync slave adc regular data register 0 */
uint32_t adc_sync_slave_adc_regular_data0_read(void);
/* read ADC sync regular data register 1 */
uint32_t adc_sync_regular_data1_read(void);

#endif /* GD32H7XX_ADC_H */
