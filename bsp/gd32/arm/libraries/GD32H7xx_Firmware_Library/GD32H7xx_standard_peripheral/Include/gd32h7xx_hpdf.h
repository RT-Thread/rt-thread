/*!
    \file    gd32h7xx_hpdf.h
    \brief   definitions for the HPDF

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

#ifndef GD32H7XX_HPDF_H
#define GD32H7XX_HPDF_H

#include "gd32h7xx.h"

/* HPDF definitions */
#define HPDF                            HPDF_BASE                                               /*!< HPDF base address */

/* registers definitions */
#define HPDF_CHXCTL(chx)                REG32((HPDF) + 0x00000000U + ((chx) * 0x00000020U))     /*!< HPDF Channel x control register */
#define HPDF_CHXCFG0(chx)               REG32((HPDF) + 0x00000004U + ((chx) * 0x00000020U))     /*!< HPDF Channel x configuration register 0 */
#define HPDF_CHXCFG1(chx)               REG32((HPDF) + 0x00000008U + ((chx) * 0x00000020U))     /*!< HPDF Channel x configuration register 1 */
#define HPDF_CHXTMFDT(chx)              REG32((HPDF) + 0x0000000CU + ((chx) * 0x00000020U))     /*!< HPDF Channel x threshold monitor filter data register */
#define HPDF_CHXPDI(chx)                REG32((HPDF) + 0x00000010U + ((chx) * 0x00000020U))     /*!< HPDF Channel x parallel data input register */
#define HPDF_CHXPS(chx)                 REG32((HPDF) + 0x00000014U + ((chx) * 0x00000020U))     /*!< HPDF Channel x pulse skip register */
#define HPDF_FLTYCTL0(flty)             REG32((HPDF) + 0x00000100U + ((flty) * 0x00000080U))    /*!< HPDF Filter y control register 0 */
#define HPDF_FLTYCTL1(flty)             REG32((HPDF) + 0x00000104U + ((flty) * 0x00000080U))    /*!< HPDF Filter y control register 1 */
#define HPDF_FLTYSTAT(flty)             REG32((HPDF) + 0x00000108U + ((flty) * 0x00000080U))    /*!< HPDF Filter y status register */
#define HPDF_FLTYINTC(flty)             REG32((HPDF) + 0x0000010CU + ((flty) * 0x00000080U))    /*!< HPDF Filter y interrupt flag clear register */
#define HPDF_FLTYICGS(flty)             REG32((HPDF) + 0x00000110U + ((flty) * 0x00000080U))    /*!< HPDF Filter y inserted channel group selection register */
#define HPDF_FLTYSFCFG(flty)            REG32((HPDF) + 0x00000114U + ((flty) * 0x00000080U))    /*!< HPDF Filter y sinc filter configuration register */
#define HPDF_FLTYIDATA(flty)            REG32((HPDF) + 0x00000118U + ((flty) * 0x00000080U))    /*!< HPDF Filter y inserted group conversion data register */
#define HPDF_FLTYRDATA(flty)            REG32((HPDF) + 0x0000011CU + ((flty) * 0x00000080U))    /*!< HPDF Filter y regular channel conversion data register */
#define HPDF_FLTYTMHT(flty)             REG32((HPDF) + 0x00000120U + ((flty) * 0x00000080U))    /*!< HPDF Filter y threshold monitor high threshold register */
#define HPDF_FLTYTMLT(flty)             REG32((HPDF) + 0x00000124U + ((flty) * 0x00000080U))    /*!< HPDF Filter y threshold monitor low threshold register */
#define HPDF_FLTYTMSTAT(flty)           REG32((HPDF) + 0x00000128U + ((flty) * 0x00000080U))    /*!< HPDF Filter y threshold monitor status register */
#define HPDF_FLTYTMFC(flty)             REG32((HPDF) + 0x0000012CU + ((flty) * 0x00000080U))    /*!< HPDF Filter y threshold monitor flag clear register */
#define HPDF_FLTYEMMAX(flty)            REG32((HPDF) + 0x00000130U + ((flty) * 0x00000080U))    /*!< HPDF Filter y extremes monitor maximum register */
#define HPDF_FLTYEMMIN(flty)            REG32((HPDF) + 0x00000134U + ((flty) * 0x00000080U))    /*!< HPDF Filter y extremes monitor minimum register */
#define HPDF_FLTYCT(flty)               REG32((HPDF) + 0x00000138U + ((flty) * 0x00000080U))    /*!< HPDF Filter y conversion timer register */

/* bits definitions */
/* HPDF_CHXCTL */
#define HPDF_CHXCTL_SITYP               BITS(0,1)                       /*!< serial interface type */
#define HPDF_CHXCTL_SPICKSS             BITS(2,3)                       /*!< SPI clock source select */
#define HPDF_CHXCTL_MMEN                BIT(5)                          /*!< malfunction monitor detector enable */
#define HPDF_CHXCTL_CKLEN               BIT(6)                          /*!< clock loss detector enable */
#define HPDF_CHXCTL_CHEN                BIT(7)                          /*!< channel enable */
#define HPDF_CHXCTL_CHPINSEL            BIT(8)                          /*!< channel inputs pins selection */
#define HPDF_CHXCTL_CMSD                BITS(12,13)                     /*!< channel multiplexer select input data source */
#define HPDF_CHXCTL_DPM                 BITS(14,15)                     /*!< data packing mode for HPDF_CHXPDI register */
/* only available in HPDF_CH0CTL */
#define HPDF_CH0CTL_CKOUTDIV            BITS(16,23)                     /*!< serial clock output divider */
#define HPDF_CH0CTL_CKOUTDM             BIT(29)                         /*!< serial clock output duty mode */
#define HPDF_CH0CTL_CKOUTSEL            BIT(30)                         /*!< serial clock output source selection */
#define HPDF_CH0CTL_HPDFEN              BIT(31)                         /*!< HPDF peripheral enable */

/* HPDF_CHXCFG0 */
#define HPDF_CHXCFG0_DTRS               BITS(3,7)                       /*!< data right bit-shift */
#define HPDF_CHXCFG0_CALOFF             BITS(8,31)                      /*!< 24-bit calibration offset */

/* HPDF_CHXCFG1 */
#define HPDF_CHXCFG1_MMCT               BITS(0,7)                       /*!< malfunction monitor counter threshold */
#define HPDF_CHXCFG1_MMBSD              BITS(12,15)                     /*!< malfunction monitor break signal distribution */
#define HPDF_CHXCFG1_TMFOR              BITS(16,20)                     /*!< threshold monitor filter oversampling rate */
#define HPDF_CHXCFG1_TMSFO              BITS(22,23)                     /*!< threshold monitor Sinc filter order selection */

/* HPDF_CHXTMFDT */
#define HPDF_CHXTMFDT_TMDATA            BITS(0,15)                      /*!< threshold monitor data */

/* HPDF_CHXPDI */
#define HPDF_CHXPDI_DATAIN0             BITS(0,15)                      /*!< data input for channel x or channel x+1 */
#define HPDF_CHXPDI_DATAIN1             BITS(16,31)                     /*!< data input for channel x */

/* HPDF_CHXPS */
#define HPDF_CHXPS_PLSK                 BITS(0,5)                       /*!< pulses to skip for input data skipping function */

/* HPDF_FLTYCTL0 */
#define HPDF_FLTYCTL0_FLTEN             BIT(0)                          /*!< HPDF_FLTy enable */
#define HPDF_FLTYCTL0_SICC              BIT(1)                          /*!< start inserted group channel conversion */
#define HPDF_FLTYCTL0_ICSYN             BIT(3)                          /*!< inserted conversion synchronously with the HPDF_FLT0 SICC trigger */
#define HPDF_FLTYCTL0_SCMOD             BIT(4)                          /*!< scan conversion mode of inserted conversions */
#define HPDF_FLTYCTL0_ICDMAEN           BIT(5)                          /*!< DMA channel enabled to read data for the inserted channel group */
#define HPDF_FLTYCTL0_ICTSSEL           BITS(8,12)                      /*!< inserted conversions trigger signal selection */
#define HPDF_FLTYCTL0_ICTEEN            BITS(13,14)                     /*!< inserted conversions trigger edge enable */
#define HPDF_FLTYCTL0_SRCS              BIT(17)                         /*!< start regular channel conversion by software */
#define HPDF_FLTYCTL0_RCCM              BIT(18)                         /*!< regular conversions continuous mode */
#define HPDF_FLTYCTL0_RCSYN             BIT(19)                         /*!< regular conversion synchronously with HPDF_FLT0 */
#define HPDF_FLTYCTL0_RCDMAEN           BIT(21)                         /*!< DMA channel enabled to read data for the regular conversion */
#define HPDF_FLTYCTL0_RCS               BITS(24,26)                     /*!< regular conversion channel selection*/
#define HPDF_FLTYCTL0_FAST              BIT(29)                         /*!< fast conversion mode enable for regular conversions */
#define HPDF_FLTYCTL0_TMFM              BIT(30)                         /*!< threshold monitor fast mode */

/* HPDF_FLTYCTL1 */
#define HPDF_FLTYCTL1_ICEIE             BIT(0)                          /*!< inserted conversion end interrupt enable */
#define HPDF_FLTYCTL1_RCEIE             BIT(1)                          /*!< regular conversion end interrupt enable */
#define HPDF_FLTYCTL1_ICDOIE            BIT(2)                          /*!< inserted conversion data overflow interrupt enable */
#define HPDF_FLTYCTL1_RCDOIE            BIT(3)                          /*!< regular conversion data overflow interrupt enable */
#define HPDF_FLTYCTL1_TMIE              BIT(4)                          /*!< threshold monitor interrupt enable */
#define HPDF_FLTYCTL1_EMCS              BITS(8,15)                      /*!< extremes monitor channel selection */
#define HPDF_FLTYCTL1_TMCHEN            BITS(16,23)                     /*!< threshold monitor channel enable */
/* only available in HPDF_FLT0CTL1 */
#define HPDF_FLT0CTL1_MMIE              BIT(5)                          /*!< malfunction monitor detector interrupt enable */
#define HPDF_FLT0CTL1_CKLIE             BIT(6)                          /*!< clock loss interrupt enable */

/* HPDF_FLTYSTAT */
#define HPDF_FLTYSTAT_ICEF              BIT(0)                          /*!< inserted conversion end flag */
#define HPDF_FLTYSTAT_RCEF              BIT(1)                          /*!< regular conversion end flag */
#define HPDF_FLTYSTAT_ICDOF             BIT(2)                          /*!< inserted conversion data overflow flag */
#define HPDF_FLTYSTAT_RCDOF             BIT(3)                          /*!< regular conversion data overflow flag */
#define HPDF_FLTYSTAT_TMEOF             BIT(4)                          /*!< threshold monitor event occurred flag */
#define HPDF_FLTYSTAT_ICPF              BIT(13)                         /*!< inserted conversion in progress flag */
#define HPDF_FLTYSTAT_RCPF              BIT(14)                         /*!< regular conversion in progress flag */
/* only available in HPDF_FLT0STAT */
#define HPDF_FLT0STAT_CKLF              BITS(16,23)                     /*!< clock loss flag */
#define HPDF_FLT0STAT_MMF               BITS(24,31)                     /*!< malfunction monitor detection flag */

/* HPDF_FLTYINTC */
#define HPDF_FLTYINTC_ICDOFC            BIT(2)                          /*!< clear the inserted conversion data overflow flag */
#define HPDF_FLTYINTC_RCDOFC            BIT(3)                          /*!< clear the regular conversion data overflow flag */
/* only available in HPDF_FLT0INTC */
#define HPDF_FLT0INTC_CKLFC             BITS(16,23)                     /*!< clear the clock loss flag */
#define HPDF_FLT0INTC_MMFC              BITS(24,31)                     /*!< clear the malfunction monitor detection flag */

/* HPDF_FLTYICGS */
#define HPDF_FLTYICGS_ICGSEL            BITS(0,7)                       /*!< inserted channel group selection */

/* HPDF_FLTYSFCFG */
#define HPDF_FLTYSFCFG_IOR              BITS(0,7)                       /*!< integrator oversampling ratio */
#define HPDF_FLTYSFCFG_SFOR             BITS(16,25)                     /*!< Sinc filter oversampling rate (decimation rate) */
#define HPDF_FLTYSFCFG_SFO              BITS(29,31)                     /*!< Sinc filter order */

/* HPDF_FLTYIDATA */
#define HPDF_FLTYIDATA_ICCH             BITS(0,2)                       /*!< inserted channel most recently converted */
#define HPDF_FLTYIDATA_IDTAT            BITS(8,31)                      /*!< inserted group conversion data */

/* HPDF_FLTYRDATA */
#define HPDF_FLTYRDATA_RCCH             BITS(0,2)                       /*!< regular channel most recently converted */
#define HPDF_FLTYRDATA_RCHPDT           BIT(4)                          /*!< regular channel pending data*/
#define HPDF_FLTYRDATA_RDATA            BITS(8,31)                      /*!< regular channel conversion data */

/* HPDF_FLTYTMHT */
#define HPDF_FLTYTMHT_HTBSD             BITS(0,3)                       /*!< high threshold event break signal distribution */
#define HPDF_FLTYTMHT_HTVAL             BITS(8,31)                      /*!< threshold monitor high threshold value */

/* HPDF_FLTYTMLT */
#define HPDF_FLTYTMLT_LTBSD             BITS(0,3)                       /*!< low threshold event break signal distribution */
#define HPDF_FLTYTMLT_LTVAL             BITS(8,31)                      /*!< threshold monitor low threshold value */

/* HPDF_FLTYTMSTAT */
#define HPDF_FLTYTMSTAT_LTF             BITS(0,7)                       /*!< threshold monitor low threshold flag */
#define HPDF_FLTYTMSTAT_HTF             BITS(8,15)                      /*!< threshold monitor high threshold flag */

/* HPDF_FLTYTMFC */
#define HPDF_FLTYTMFC_LTFC              BITS(0,7)                       /*!< clear the threshold monitor low threshold flag */
#define HPDF_FLTYTMFC_HTFC              BITS(8,15)                      /*!< clear the threshold monitor high threshold flag */

/* HPDF_FLTYEMMAX */
#define HPDF_FLTYEMMAX_MAXDC            BIT(0,2)                        /*!< extremes monitor maximum data channel */
#define HPDF_FLTYEMMAX_MAXVAL           BITS(8,31)                      /*!< extremes monitor maximum value */

/* HPDF_FLTYEMMIN */
#define HPDF_FLTYEMMIN_MINDC            BIT(0,2)                        /*!< extremes monitor minimum data channel */
#define HPDF_FLTYEMMIN_MINVAL           BITS(8,31)                      /*!< extremes monitor minimum value */

/* HPDF_FLTYCT */
#define HPDF_FLTYCT_CTCNT               BIT(4,31)                       /*!< conversion time measured by HPDFCLK */

/* register offset */
#define FLTYCTL1_REG_OFFSET                                   ((uint16_t)0x0004U)        /*!< the offset of FLTYCTL1 register */
#define FLTYSTAT_REG_OFFSET                                   ((uint16_t)0x0008U)        /*!< the offset of FLTYSTAT register */
#define FLTYRDATA_REG_OFFSET                                  ((uint16_t)0x001CU)        /*!< the offset of FLTYRDATA register */
#define FLTYTMSTAT_REG_OFFSET                                 ((uint16_t)0x0028U)        /*!< the offset of FLTYTMSTAT register */

/* HPDF flags and interrupt definitions */
/* define the HPDF bit position and its register index offset */
#define HPDF_FLT0                                             (HPDF + 0x00000100U)
#define HPDF_FLT1                                             (HPDF + 0x00000180U)
#define HPDF_FLT2                                             (HPDF + 0x00000200U)
#define HPDF_FLT3                                             (HPDF + 0x00000280U)
#define HPDF_REGIDX_BIT(regidx, bitpos)                       (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define HPDF_REG_VAL(regidx, offset)                          (REG32((regidx) + (((uint32_t)(offset) & 0x0000FFC0U) >> 6)))
#define HPDF_BIT_POS(val)                                     ((uint32_t)(val) & 0x0000001FU)
#define HPDF_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)    (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                              | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define HPDF_REG_VAL2(regidx, offset)                         (REG32((regidx) + ((uint32_t)(offset) >> 22)))
#define HPDF_BIT_POS2(val)                                    (((uint32_t)(val) & 0x001F0000U) >> 16)

/* constants definitions */
/* parameter struct definitions */
/* channel configuration params */
typedef struct {
    uint32_t data_packing_mode;                 /*!< data packing mode for HPDF_CHXPDI register */
    uint32_t channel_multiplexer;               /*!< channel multiplexer select input data source */
    uint32_t channel_pin_select;                /*!< channel inputs pins selection */
    uint32_t ck_loss_detector;                  /*!< clock loss detector */
    uint32_t malfunction_monitor;               /*!< malfunction monitor */
    uint32_t spi_ck_source;                     /*!< SPI clock source select */
    uint32_t serial_interface;                  /*!< serial interface type */
    int32_t  calibration_offset;                /*!< 24-bit calibration offset */
    uint32_t right_bit_shift;                   /*!< data right bit-shift */
    uint32_t tm_filter;                         /*!< threshold monitor Sinc filter order selection */
    uint32_t tm_filter_oversample;              /*!< threshold monitor filter oversampling rate */
    uint32_t mm_break_signal;                   /*!< malfunction monitor break signal distribution */
    uint32_t mm_counter_threshold;              /*!< malfunction monitor counter threshold */
    uint32_t plsk_value;                        /*!< the number of serial input samples that will be skipped */
} hpdf_channel_parameter_struct;

/* filter configuration params */
typedef struct {
    uint32_t tm_fast_mode;                      /*!< threshold monitor fast mode */
    uint32_t tm_channel;                        /*!< threshold monitor channel */
    int32_t  tm_high_threshold;                 /*!< threshold monitor high threshold */
    int32_t  tm_low_threshold;                  /*!< threshold monitor low threshold value */
    uint32_t extreme_monitor_channel;           /*!< extremes monitor channel */
    uint32_t sinc_filter;                       /*!< sinc filter order */
    uint32_t sinc_oversample;                   /*!< sinc filter oversampling rate */
    uint32_t integrator_oversample;             /*!< integrator oversampling rate */
    uint32_t ht_break_signal;                   /*!< high threshold event break signal distribution */
    uint32_t lt_break_signal;                   /*!< low threshold event break signal distribution */
} hpdf_filter_parameter_struct;

/* regular conversions configuration params */
typedef struct {
    uint32_t fast_mode;                         /*!< fast conversion mode enable for regular conversions */
    uint32_t rcs_channel;                       /*!< regular conversion channel */
    uint32_t rcdmaen;                           /*!< DMA channel enabled to read data for the regular conversion */
    uint32_t rcsyn;                             /*!< regular conversion synchronously */
    uint32_t continuous_mode;                   /*!< regular conversions continuous mode */
} hpdf_rc_parameter_struct;

/* inserted conversions configuration params */
typedef struct {
    uint32_t trigger_edge;                      /*!< inserted conversions trigger edge */
    uint32_t trigger_signal;                    /*!< inserted conversions trigger signal */
    uint32_t icdmaen;                           /*!< DMA channel enabled to read data for the inserted channel group */
    uint32_t scmod;                             /*!< scan conversion mode of inserted conversions */
    uint32_t icsyn;                             /*!< inserted conversion synchronously */
    uint32_t ic_channel_group;                  /*!< inserted channel group selection */
} hpdf_ic_parameter_struct;

/* enum definitions */
/* HPDF channel */
typedef enum {
    CHANNEL0 = 0,                               /*!< HPDF channel0 */
    CHANNEL1,                                   /*!< HPDF channel1 */
    CHANNEL2,                                   /*!< HPDF channel2 */
    CHANNEL3,                                   /*!< HPDF channel3 */
    CHANNEL4,                                   /*!< HPDF channel4 */
    CHANNEL5,                                   /*!< HPDF channel5 */
    CHANNEL6,                                   /*!< HPDF channel6 */
    CHANNEL7                                    /*!< HPDF channel7 */
} hpdf_channel_enum;

/* HPDF filter */
typedef enum {
    FLT0 = 0,                                   /*!< HPDF filter0 */
    FLT1,                                       /*!< HPDF filter1 */
    FLT2,                                       /*!< HPDF filter2 */
    FLT3                                        /*!< HPDF filter3 */
} hpdf_filter_enum;

/* HPDF flags */
typedef enum {
    /* flags in FLTYSTAT register */
    HPDF_FLAG_FLTY_ICEF      = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 0U),                 /*!< inserted conversion end flag */
    HPDF_FLAG_FLTY_RCEF      = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 1U),                 /*!< regular conversion end flag */
    HPDF_FLAG_FLTY_ICDOF     = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 2U),                 /*!< inserted conversion overflow flag */
    HPDF_FLAG_FLTY_RCDOF     = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 3U),                 /*!< regular conversion overflow flag */
    HPDF_FLAG_FLTY_TMEOF     = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 4U),                 /*!< threshold monitor event occurred flag */
    HPDF_FLAG_FLTY_ICPF      = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 13U),                /*!< inserted conversion in progress flag */
    HPDF_FLAG_FLTY_RCPF      = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 14U),                /*!< regular conversion in progress flag */
    HPDF_FLAG_FLT0_CKLF0     = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 16U),                /*!< clock loss on channel 0 flag */
    HPDF_FLAG_FLT0_CKLF1     = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 17U),                /*!< clock loss on channel 1 flag */
    HPDF_FLAG_FLT0_CKLF2     = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 18U),                /*!< clock loss on channel 2 flag */
    HPDF_FLAG_FLT0_CKLF3     = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 19U),                /*!< clock loss on channel 3 flag */
    HPDF_FLAG_FLT0_CKLF4     = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 20U),                /*!< clock loss on channel 4 flag */
    HPDF_FLAG_FLT0_CKLF5     = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 21U),                /*!< clock loss on channel 5 flag */
    HPDF_FLAG_FLT0_CKLF6     = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 22U),                /*!< clock loss on channel 6 flag */
    HPDF_FLAG_FLT0_CKLF7     = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 23U),                /*!< clock loss on channel 7 flag */
    HPDF_FLAG_FLT0_MMF0      = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 24U),                /*!< malfunction event occurred on channel 0 flag */
    HPDF_FLAG_FLT0_MMF1      = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 25U),                /*!< malfunction event occurred on channel 1 flag */
    HPDF_FLAG_FLT0_MMF2      = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 26U),                /*!< malfunction event occurred on channel 2 flag */
    HPDF_FLAG_FLT0_MMF3      = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 27U),                /*!< malfunction event occurred on channel 3 flag */
    HPDF_FLAG_FLT0_MMF4      = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 28U),                /*!< malfunction event occurred on channel 4 flag */
    HPDF_FLAG_FLT0_MMF5      = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 29U),                /*!< malfunction event occurred on channel 5 flag */
    HPDF_FLAG_FLT0_MMF6      = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 30U),                /*!< malfunction event occurred on channel 6 flag */
    HPDF_FLAG_FLT0_MMF7      = HPDF_REGIDX_BIT(FLTYSTAT_REG_OFFSET, 31U),                /*!< malfunction event occurred on channel 7 flag */
    /* flags in FLT0RDATA register */
    HPDF_FLAG_FLTY_RCHPDT    = HPDF_REGIDX_BIT(FLTYRDATA_REG_OFFSET, 4U),                /*!< regular channel pending data */
    /* flags in FLTYTMSTAT register */
    HPDF_FLAG_FLTY_LTF0      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 0U),               /*!< threshold monitor low threshold on channel 0 flag */
    HPDF_FLAG_FLTY_LTF1      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 1U),               /*!< threshold monitor low threshold on channel 1 flag */
    HPDF_FLAG_FLTY_LTF2      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 2U),               /*!< threshold monitor low threshold on channel 2 flag */
    HPDF_FLAG_FLTY_LTF3      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 3U),               /*!< threshold monitor low threshold on channel 3 flag */
    HPDF_FLAG_FLTY_LTF4      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 4U),               /*!< threshold monitor low threshold on channel 4 flag */
    HPDF_FLAG_FLTY_LTF5      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 5U),               /*!< threshold monitor low threshold on channel 5 flag */
    HPDF_FLAG_FLTY_LTF6      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 6U),               /*!< threshold monitor low threshold on channel 6 flag */
    HPDF_FLAG_FLTY_LTF7      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 7U),               /*!< threshold monitor low threshold on channel 7 flag */
    HPDF_FLAG_FLTY_HTF0      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 8U),               /*!< threshold monitor high threshold on channel 0 flag */
    HPDF_FLAG_FLTY_HTF1      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 9U),               /*!< threshold monitor high threshold on channel 1 flag */
    HPDF_FLAG_FLTY_HTF2      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 10U),              /*!< threshold monitor high threshold on channel 2 flag */
    HPDF_FLAG_FLTY_HTF3      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 11U),              /*!< threshold monitor high threshold on channel 3 flag */
    HPDF_FLAG_FLTY_HTF4      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 12U),              /*!< threshold monitor high threshold on channel 4 flag */
    HPDF_FLAG_FLTY_HTF5      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 13U),              /*!< threshold monitor high threshold on channel 5 flag */
    HPDF_FLAG_FLTY_HTF6      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 14U),              /*!< threshold monitor high threshold on channel 6 flag */
    HPDF_FLAG_FLTY_HTF7      = HPDF_REGIDX_BIT(FLTYTMSTAT_REG_OFFSET, 15U)               /*!< threshold monitor high threshold on channel 7 flag */
} hpdf_flag_enum;

/* HPDF interrput flags */
typedef enum {
    /* interrput flags in FLTYSTAT register */
    HPDF_INT_FLAG_FLTY_ICEF      = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 0U, FLTYSTAT_REG_OFFSET, 0U),      /*!< inserted conversion end interrupt flag */
    HPDF_INT_FLAG_FLTY_RCEF      = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 1U, FLTYSTAT_REG_OFFSET, 1U),      /*!< regular conversion end interruptflag */
    HPDF_INT_FLAG_FLTY_ICDOF     = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 2U, FLTYSTAT_REG_OFFSET, 2U),      /*!< inserted conversion overflow interrupt flag */
    HPDF_INT_FLAG_FLTY_RCDOF     = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 3U, FLTYSTAT_REG_OFFSET, 3U),      /*!< regular conversion overflow interrupt flag */
    HPDF_INT_FLAG_FLTY_TMEOF     = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 4U, FLTYSTAT_REG_OFFSET, 4U),      /*!< threshold monitor event occurred interrupt flag */
    HPDF_INT_FLAG_FLT0_CKLF0     = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 6U, FLTYSTAT_REG_OFFSET, 16U),     /*!< clock loss on channel 0 interrupt flag */
    HPDF_INT_FLAG_FLT0_CKLF1     = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 6U, FLTYSTAT_REG_OFFSET, 17U),     /*!< clock loss on channel 1 interrupt flag */
    HPDF_INT_FLAG_FLT0_CKLF2     = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 6U, FLTYSTAT_REG_OFFSET, 18U),     /*!< clock loss on channel 2 interrupt flag */
    HPDF_INT_FLAG_FLT0_CKLF3     = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 6U, FLTYSTAT_REG_OFFSET, 19U),     /*!< clock loss on channel 3 interrupt flag */
    HPDF_INT_FLAG_FLT0_CKLF4     = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 6U, FLTYSTAT_REG_OFFSET, 20U),     /*!< clock loss on channel 4 interrupt flag */
    HPDF_INT_FLAG_FLT0_CKLF5     = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 6U, FLTYSTAT_REG_OFFSET, 21U),     /*!< clock loss on channel 5 interrupt flag */
    HPDF_INT_FLAG_FLT0_CKLF6     = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 6U, FLTYSTAT_REG_OFFSET, 22U),     /*!< clock loss on channel 6 interrupt flag */
    HPDF_INT_FLAG_FLT0_CKLF7     = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 6U, FLTYSTAT_REG_OFFSET, 23U),     /*!< clock loss on channel 7 interrupt flag */
    HPDF_INT_FLAG_FLT0_MMF0      = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 5U, FLTYSTAT_REG_OFFSET, 24U),     /*!< malfunction monitor detection on channel 0 interrupt flag */
    HPDF_INT_FLAG_FLT0_MMF1      = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 5U, FLTYSTAT_REG_OFFSET, 25U),     /*!< malfunction monitor detection on channel 1 interrupt flag */
    HPDF_INT_FLAG_FLT0_MMF2      = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 5U, FLTYSTAT_REG_OFFSET, 26U),     /*!< malfunction monitor detection on channel 2 interrupt flag */
    HPDF_INT_FLAG_FLT0_MMF3      = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 5U, FLTYSTAT_REG_OFFSET, 27U),     /*!< malfunction monitor detection on channel 3 interrupt flag */
    HPDF_INT_FLAG_FLT0_MMF4      = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 5U, FLTYSTAT_REG_OFFSET, 28U),     /*!< malfunction monitor detection on channel 4 interrupt flag */
    HPDF_INT_FLAG_FLT0_MMF5      = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 5U, FLTYSTAT_REG_OFFSET, 29U),     /*!< malfunction monitor detection on channel 5 interrupt flag */
    HPDF_INT_FLAG_FLT0_MMF6      = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 5U, FLTYSTAT_REG_OFFSET, 30U),     /*!< malfunction monitor detection on channel 6 interrupt flag */
    HPDF_INT_FLAG_FLT0_MMF7      = HPDF_REGIDX_BIT2(FLTYCTL1_REG_OFFSET, 5U, FLTYSTAT_REG_OFFSET, 31U)      /*!< malfunction monitor detection on channel 7 interrupt flag */
} hpdf_interrput_flag_enum;

/* HPDF interrput */
typedef enum {
    /* interrput in FLTYCTL1 register */
    HPDF_INT_FLTY_ICEIE      = HPDF_REGIDX_BIT(FLTYCTL1_REG_OFFSET, 0U),            /*!< inserted conversion end interrupt enable */
    HPDF_INT_FLTY_RCEIE      = HPDF_REGIDX_BIT(FLTYCTL1_REG_OFFSET, 1U),            /*!< regular conversion end interrupt enable */
    HPDF_INT_FLTY_ICDOIE     = HPDF_REGIDX_BIT(FLTYCTL1_REG_OFFSET, 2U),            /*!< inserted conversion data overflow interrupt enable */
    HPDF_INT_FLTY_RCDOIE     = HPDF_REGIDX_BIT(FLTYCTL1_REG_OFFSET, 3U),            /*!< regular conversion data overflow interrupt enable */
    HPDF_INT_FLTY_TMIE       = HPDF_REGIDX_BIT(FLTYCTL1_REG_OFFSET, 4U),            /*!< threshold monitor interrupt enable */
    HPDF_INT_FLT0_MMIE       = HPDF_REGIDX_BIT(FLTYCTL1_REG_OFFSET, 5U),            /*!< malfunction monitor interrupt enable */
    HPDF_INT_FLT0_CKLIE      = HPDF_REGIDX_BIT(FLTYCTL1_REG_OFFSET, 6U)             /*!< clock loss interrupt enable */
} hpdf_interrput_enum;

/* HPDF channel definitions */
/* serial clock output source definitions */
#define SERIAL_SYSTEM_CLK               ((uint32_t)0x00000000U)                         /*!< serial clock output source is from system clock */
#define SERIAL_AUDIO_CLK                HPDF_CH0CTL_CKOUTSEL                            /*!< serial clock output source is from audio clock */

/* serial clock output duty mode definitions */
#define CKOUTDM_DISABLE                 ((uint32_t)0x00000000U)                         /*!< serial clock output duty mode disable */
#define CKOUTDM_ENABLE                  HPDF_CH0CTL_CKOUTDM                             /*!< serial clock output duty mode enable */

/* data packing mode definitions */
#define DPM(regval)                     (BITS(14,15) & ((uint32_t)(regval) << 14))      /*!< select data packing mode */
#define DPM_STANDARD_MODE               DPM(0)                                          /*!< standard mode */
#define DPM_INTERLEAVED_MODE            DPM(1)                                          /*!< interleaved mode */
#define DPM_DUAL_MODE                   DPM(2)                                          /*!< dual mode */

/* input data source for channel definitions */
#define IDATASEL(regval)                (BITS(12,13) & ((uint32_t)(regval) << 12))      /*!< select channel y multiplexer input data source */
#define SERIAL_INPUT                    IDATASEL(0)                                     /*!< input data source for channel is taken from serial inputs */
#define ADC_INPUT                       IDATASEL(1)                                     /*!< input data source for channel is taken from  ADC output register */
#define INTERNAL_INPUT                  IDATASEL(2)                                     /*!< input data source for channel is taken from internal HPDF_CHXPDI register */

/* channel inputs pins definitions */
#define CHPINSEL_CURRENT                ((uint32_t)0x00000000U)                         /*!< channel inputs select pins of the current channel */
#define CHPINSEL_NEXT                   HPDF_CHXCTL_CHPINSEL                            /*!< channel inputs select pins of the next channel */

/* clock loss detector definitions */
#define CLK_LOSS_DISABLE                ((uint32_t)0x00000000U)                         /*!< clock loss detector disable */
#define CLK_LOSS_ENABLE                 HPDF_CHXCTL_CKLEN                               /*!< clock loss detector enable */

/* SPI clock source definitions */
#define SPICKSS(regval)                 (BITS(2,3) & ((uint32_t)(regval) << 2))         /*!< select SPI clock source */
#define EXTERNAL_CKIN                   SPICKSS(0)                                      /*!< external CKINy input */
#define INTERNAL_CKOUT                  SPICKSS(1)                                      /*!< internal CKOUT output */
#define HALF_CKOUT_FALLING_EDGE         SPICKSS(2)                                      /*!< internal CKOUT output, sampling point on each second CKOUT falling edge. */
#define HALF_CKOUT_RISING_EDGE          SPICKSS(3)                                      /*!< internal CKOUT output, sampling point on each second CKOUT rising edge */

/* serial interface type definitions */
#define SITYP(regval)                   (BITS(0,1) & ((uint32_t)(regval)))              /*!< select serial interface type */
#define SPI_RISING_EDGE                 SITYP(0)                                        /*!< SPI interface, sample data on rising edge */
#define SPI_FALLING_EDGE                SITYP(1)                                        /*!< SPI interface, sample data on rising edge */
#define MANCHESTER_CODE0                SITYP(2)                                        /*!< manchester coded input: rising edge = logic 0, falling edge = logic 1 */
#define MANCHESTER_CODE1                SITYP(3)                                        /*!< manchester coded input: rising edge = logic 1, falling edge = logic 0 */

/* malfunction monitor detector definitions */
#define MM_DISABLE                      ((uint32_t)0x00000000U)                         /*!< malfunction monitor disable */
#define MM_ENABLE                       HPDF_CHXCTL_MMEN                                /*!< malfunction monitor enable */

/* malfunction monitor detector break signal definitions */
#define MMBSD(regval)                   (BITS(12,15) & ((uint32_t)(regval)<< 12))      /*!< select break signal on channel */
#define NO_MM_BREAK                     MMBSD(0)                                        /*!< break signal is not distributed to malfunction monitor on channel */
#define MM_BREAK0                       MMBSD(1)                                        /*!< break signal 0 is distributed to malfunction monitor on channel */
#define MM_BREAK1                       MMBSD(2)                                        /*!< break signal 1 is distributed to malfunction monitor on channel */
#define MM_BREAK2                       MMBSD(4)                                        /*!< break signal 2 is distributed to malfunction monitor on channel */
#define MM_BREAK3                       MMBSD(8)                                        /*!< break signal 3 is distributed to malfunction monitor on channel */

/* threshold monitor fast mode definitions */
#define TMFM_DISABLE                    ((uint32_t)0x00000000U)                         /*!< threshold monitor fast mode disable */
#define TMFM_ENABLE                     HPDF_FLTYCTL0_TMFM                              /*!< threshold monitor fast mode enable */

/* regular conversions configuration definitions */
/* fast conversion mode definitions */
#define FAST_DISABLE                    ((uint32_t)0x00000000U)                         /*!< fast conversion mode disable */
#define FAST_ENABLE                     HPDF_FLTYCTL0_FAST                              /*!< fast conversion mode enable */

/* regular conversion channel selection definitions */
#define RCS(regval)                     (BITS(24,26) & ((uint32_t)(regval)<< 24 ))      /*!< select regular conversion channel */
#define RCS_CHANNEL0                    RCS(0)                                          /*!< channel 0 is selected as the regular conversion channel */
#define RCS_CHANNEL1                    RCS(1)                                          /*!< channel 1 is selected as the regular conversion channel */
#define RCS_CHANNEL2                    RCS(2)                                          /*!< channel 2 is selected as the regular conversion channel */
#define RCS_CHANNEL3                    RCS(3)                                          /*!< channel 3 is selected as the regular conversion channel */
#define RCS_CHANNEL4                    RCS(4)                                          /*!< channel 4 is selected as the regular conversion channel */
#define RCS_CHANNEL5                    RCS(5)                                          /*!< channel 5 is selected as the regular conversion channel */
#define RCS_CHANNEL6                    RCS(6)                                          /*!< channel 6 is selected as the regular conversion channel */
#define RCS_CHANNEL7                    RCS(7)                                          /*!< channel 7 is selected as the regular conversion channel */

/* DMA channel of regular conversion definitions */
#define RCDMAEN_DISABLE                 ((uint32_t)0x00000000U)                         /*!< disable the DMA channel to read regular data */
#define RCDMAEN_ENABLE                  HPDF_FLTYCTL0_RCDMAEN                           /*!< enable the DMA channel to read regular data */

/* regular conversion synchronously definitions */
#define RCSYN_DISABLE                   ((uint32_t)0x00000000U)                         /*!< do not launch a regular conversion synchronously */
#define RCSYN_ENABLE                    HPDF_FLTYCTL0_RCSYN                             /*!< launch a regular conversion synchronously */

/* regular conversions continuous mode definitions */
#define RCCM_DISABLE                    ((uint32_t)0x00000000U)                         /*!< regular conversions continuous mode */
#define RCCM_ENABLE                     HPDF_FLTYCTL0_RCCM                              /*!< regular conversions continuous mode */

/* inserted conversions trigger edge definitions */
#define ICTEEN(regval)                  (BITS(13,14) & ((uint32_t)(regval)<< 13))       /*!< select inserted conversions trigger edge */
#define TRG_DISABLE                     ICTEEN(0)                                       /*!< disable trigger detection */
#define RISING_EDGE_TRG                 ICTEEN(1)                                       /*!< each rising edge on the trigger signal */
#define FALLING_EDGE_TRG                ICTEEN(2)                                       /*!< each falling edge on the trigger signal */
#define EDGE_TRG                        ICTEEN(3)                                       /*!< the edge (rising edges and falling edges) on the trigger signal */

/* inserted conversions trigger signal definitions */
#define ICTSSEL(regval)                 (BITS(8,12) & ((uint32_t)(regval)<< 8))         /*!< select inserted conversions trigger signal */
#define HPDF_ITRG0                      ICTSSEL(0)                                      /*!< HPDF_ITRG0  (TIMER0_TRGO0)  */
#define HPDF_ITRG1                      ICTSSEL(1)                                      /*!< HPDF_ITRG1  (TIMER0_TRGO1) */
#define HPDF_ITRG2                      ICTSSEL(2)                                      /*!< HPDF_ITRG2  (TIMER7_TRGO0)  */
#define HPDF_ITRG3                      ICTSSEL(3)                                      /*!< HPDF_ITRG3  (TIMER7_TRGO1) */
#define HPDF_ITRG4                      ICTSSEL(4)                                      /*!< HPDF_ITRG4  (TIMER2_TRGO0)  */
#define HPDF_ITRG5                      ICTSSEL(5)                                      /*!< HPDF_ITRG5  (TIMER3_TRGO0)  */
#define HPDF_ITRG6                      ICTSSEL(6)                                      /*!< HPDF_ITRG6  (TIMER15_CH1)  */
#define HPDF_ITRG7                      ICTSSEL(7)                                      /*!< HPDF_ITRG7  (TIMER5_TRGO0)  */
#define HPDF_ITRG8                      ICTSSEL(8)                                      /*!< HPDF_ITRG8  (TIMER6_TRGO0)  */
#define HPDF_ITRG11                     ICTSSEL(11)                                     /*!< HPDF_ITRG11 (TIMER22_TRGO0) */
#define HPDF_ITRG12                     ICTSSEL(12)                                     /*!< HPDF_ITRG12 (TIMER23_TRGO0) */
#define HPDF_ITRG24                     ICTSSEL(24)                                     /*!< HPDF_ITRG24 (EXTI11)     */
#define HPDF_ITRG25                     ICTSSEL(25)                                     /*!< HPDF_ITRG25 (EXTI15)     */
#define HPDF_ITRG31                     ICTSSEL(31)                                     /*!< HPDF_ITRG31 (HPDF_ITRG)  */

/* inserted channel DMA enable definitions */
#define ICDMAEN_DISABLE                 ((uint32_t)0x00000000U)                         /*!< disable DMA channel to read inserted conversions data */
#define ICDMAEN_ENABLE                  HPDF_FLTYCTL0_ICDMAEN                           /*!< enable DMA channel to read inserted conversions data */

/* scan conversion mode */
#define SCMOD_DISABLE                   ((uint32_t)0x00000000U)                         /*!< scan conversion mode disable */
#define SCMOD_ENABLE                    HPDF_FLTYCTL0_SCMOD                             /*!< scan conversion mode enable */

/* inserted conversion synchronously definitions */
#define ICSYN_DISABLE                   ((uint32_t)0x00000000U)                         /*!< do not launch an inserted conversion synchronously */
#define ICSYN_ENABLE                    HPDF_FLTYCTL0_ICSYN                             /*!< launch an inserted conversion synchronously */

/* inserted channel group definitions */
#define ICGSEL(regval)                  (BITS(0,7) & ((uint32_t)(regval)<< 0))          /*!< inserted channel group selection */
#define ICGSEL_CHANNEL0                 ICGSEL(0x01)                                    /*!< channel 0 belongs to the inserted group */
#define ICGSEL_CHANNEL1                 ICGSEL(0x02)                                    /*!< channel 1 belongs to the inserted group */
#define ICGSEL_CHANNEL2                 ICGSEL(0x04)                                    /*!< channel 2 belongs to the inserted group */
#define ICGSEL_CHANNEL3                 ICGSEL(0x08)                                    /*!< channel 3 belongs to the inserted group */
#define ICGSEL_CHANNEL4                 ICGSEL(0x10)                                    /*!< channel 4 belongs to the inserted group */
#define ICGSEL_CHANNEL5                 ICGSEL(0x20)                                    /*!< channel 5 belongs to the inserted group */
#define ICGSEL_CHANNEL6                 ICGSEL(0x40)                                    /*!< channel 6 belongs to the inserted group */
#define ICGSEL_CHANNEL7                 ICGSEL(0x80)                                    /*!< channel 7 belongs to the inserted group */

/* Sinc fliter definitions */
/* Sinc fliter order and type definitions */
#define SFO(regval)                     (BITS(29,31) & ((uint32_t)(regval)<< 29))       /*!< select Sinc filter order */
#define FLT_FASTSINC                    SFO(0)                                          /*!< FastSinc filter type */
#define FLT_SINC1                       SFO(1)                                          /*!< Sinc1 filter type */
#define FLT_SINC2                       SFO(2)                                          /*!< Sinc2 filter type */
#define FLT_SINC3                       SFO(3)                                          /*!< Sinc3 filter type */
#define FLT_SINC4                       SFO(4)                                          /*!< Sinc4 filter type */
#define FLT_SINC5                       SFO(5)                                          /*!< Sinc4 filter type */

/* Sinc fliter and bypass definitions */
#define FLT_SINC_BYPASS                 ((uint32_t)0x00000001U)                         /*!< the filter will be bypass. */
#define INTEGRATOR_BYPASS               ((uint32_t)0x00000001U)                         /*!< the integrator will be bypass. */

/* threshold monitor definitions */
/* threshold monitor Sinc filter order definitions */
#define TMSFO(regval)                   (BITS(22,23) & ((uint32_t)(regval)<< 22))       /*!< select threshold monitor Sinc filter order */
#define TM_FASTSINC                     TMSFO(0)                                        /*!< FastSinc filter */
#define TM_SINC1                        TMSFO(1)                                        /*!< Sinc1 filter */
#define TM_SINC2                        TMSFO(2)                                        /*!< Sinc2 filter */
#define TM_SINC3                        TMSFO(3)                                        /*!< Sinc3 filter */

/* threshold monitor channel definitions */
#define TMCHEN(regval)                  (BITS(16,23) & ((uint32_t)(regval)<< 16))       /*!< select threshold monitor channel */
#define TMCHEN_DISABLE                  TMCHEN(0)                                       /*!< threshold monitor is disabled on channel 0 and channel 1 */
#define TMCHEN_CHANNEL0                 TMCHEN(0x01)                                    /*!< threshold monitor is enabled on channel 0 */
#define TMCHEN_CHANNEL1                 TMCHEN(0x02)                                    /*!< threshold monitor is enabled on channel 1 */
#define TMCHEN_CHANNEL2                 TMCHEN(0x04)                                    /*!< threshold monitor is enabled on channel 2 */
#define TMCHEN_CHANNEL3                 TMCHEN(0x08)                                    /*!< threshold monitor is enabled on channel 3 */
#define TMCHEN_CHANNEL4                 TMCHEN(0x10)                                    /*!< threshold monitor is enabled on channel 4 */
#define TMCHEN_CHANNEL5                 TMCHEN(0x20)                                    /*!< threshold monitor is enabled on channel 5 */
#define TMCHEN_CHANNEL6                 TMCHEN(0x40)                                    /*!< threshold monitor is enabled on channel 6 */
#define TMCHEN_CHANNEL7                 TMCHEN(0x80)                                    /*!< threshold monitor is enabled on channel 7 */

/* threshold monitor high threshold event break signal definitions */
#define HTBSD(regval)                   (BITS(0,1) & ((uint32_t)(regval)<< 1))          /*!< select high threshold event break signal */
#define NO_TM_HT_BREAK                  HTBSD(0)                                        /*!< break signal is not distributed to an threshold monitor high threshold event */
#define TM_HT_BREAK0                    HTBSD(1)                                        /*!< break signal 0 is distributed to an threshold monitor high threshold event */
#define TM_HT_BREAK1                    HTBSD(2)                                        /*!< break signal 1 is distributed to an threshold monitor high threshold event */
#define TM_HT_BREAK2                    HTBSD(4)                                        /*!< break signal 2 is distributed to an threshold monitor high threshold event */
#define TM_HT_BREAK3                    HTBSD(8)                                        /*!< break signal 3 is distributed to an threshold monitor high threshold event */

/* threshold monitor low threshold event break signal definitions */
#define LTBSD(regval)                   (BITS(0,1) & ((uint32_t)(regval)<< 1))          /*!< select low threshold event break signal */
#define NO_TM_LT_BREAK                  LTBSD(0)                                        /*!< break signal is not distributed to an threshold monitor low threshold event */
#define TM_LT_BREAK0                    LTBSD(1)                                        /*!< break signal 0 is distributed to an threshold monitor low threshold event */
#define TM_LT_BREAK1                    LTBSD(2)                                        /*!< break signal 1 is distributed to an threshold monitor low threshold event */
#define TM_LT_BREAK2                    LTBSD(4)                                        /*!< break signal 2 is distributed to an threshold monitor low threshold event */
#define TM_LT_BREAK3                    LTBSD(8)                                        /*!< break signal 3 is distributed to an threshold monitor low threshold event */

/* threshold monitor bypass definitions */
#define TM_FLT_BYPASS                   ((uint32_t)0x00000001U)                         /*!< the threshold monitor filter is bypassed. */

/* extremes monitor definitions */
/* extremes monitor channel definitions */
#define EMCS(regval)                    (BITS(8,15) & ((uint32_t)(regval)<< 8))         /*!< select extremes monitor channel */
#define EM_CHANNEL_DISABLE              EMCS(0)                                         /*!< extremes monitor y does not accept data from channel 0 and channel 1 */
#define EM_CHANNEL0                     EMCS(0x01)                                      /*!< extremes monitor y accepts data from channel 0 */
#define EM_CHANNEL1                     EMCS(0x02)                                      /*!< extremes monitor y accepts data from channel 1 */
#define EM_CHANNEL2                     EMCS(0x04)                                      /*!< extremes monitor y accepts data from channel 2 */
#define EM_CHANNEL3                     EMCS(0x08)                                      /*!< extremes monitor y accepts data from channel 3 */
#define EM_CHANNEL4                     EMCS(0x10)                                      /*!< extremes monitor y accepts data from channel 4 */
#define EM_CHANNEL5                     EMCS(0x20)                                      /*!< extremes monitor y accepts data from channel 5 */
#define EM_CHANNEL6                     EMCS(0x40)                                      /*!< extremes monitor y accepts data from channel 6 */
#define EM_CHANNEL7                     EMCS(0x80)                                      /*!< extremes monitor y accepts data from channel 7 */

/* function declarations */
/* initialize HPDF channel and filter registers */
/* reset HPDF */
void hpdf_deinit(void);
/* initialize the parameters of HPDF channel struct with the default values */
void hpdf_channel_struct_para_init(hpdf_channel_parameter_struct *init_struct);
/* initialize the parameters of HPDF filter struct with the default values */
void hpdf_filter_struct_para_init(hpdf_filter_parameter_struct *init_struct);
/* initialize the parameters of regular conversion struct with the default values */
void hpdf_rc_struct_para_init(hpdf_rc_parameter_struct *init_struct);
/* initialize the parameters of inserted conversion struct with the default values */
void hpdf_ic_struct_para_init(hpdf_ic_parameter_struct *init_struct);
/* enable the HPDF module globally */
void hpdf_enable(void);
/* disable the HPDF module globally */
void hpdf_disable(void);
/* initialize the HPDF channel */
void hpdf_channel_init(hpdf_channel_enum channelx, hpdf_channel_parameter_struct *init_struct);
/* initialize the HPDF filter */
void hpdf_filter_init(hpdf_filter_enum filtery, hpdf_filter_parameter_struct *init_struct);
/* initialize the regular conversion */
void hpdf_rc_init(hpdf_filter_enum filtery, hpdf_rc_parameter_struct *init_struct);
/* initialize the inserted conversion */
void hpdf_ic_init(hpdf_filter_enum filtery, hpdf_ic_parameter_struct *init_struct);

/* configure the HPDF clock output */
/* configure serial output clock */
void hpdf_clock_output_config(uint32_t source, uint8_t divider, uint32_t mode);
/* configure serial clock output source */
void hpdf_clock_output_source_config(uint32_t source);
/* disable serial clock output duty mode */
void hpdf_clock_output_duty_mode_disable(void);
/* enable serial clock output duty mode */
void hpdf_clock_output_duty_mode_enable(void);
/* configure serial clock output divider */
void hpdf_clock_output_divider_config(uint8_t divider);

/* configure HPDF channel */
/* enable channel */
void hpdf_channel_enable(hpdf_channel_enum channelx);
/* disable channel */
void hpdf_channel_disable(hpdf_channel_enum channelx);
/* configure SPI clock source */
void hpdf_spi_clock_source_config(hpdf_channel_enum channelx, uint32_t clock_source);
/* configure serial interface type */
void hpdf_serial_interface_type_config(hpdf_channel_enum channelx, uint32_t type);
/* disable malfunction monitor */
void hpdf_malfunction_monitor_disable(hpdf_channel_enum channelx);
/* enable malfunction monitor */
void hpdf_malfunction_monitor_enable(hpdf_channel_enum channelx);
/* disable clock loss detector */
void hpdf_clock_loss_disable(hpdf_channel_enum channelx);
/* enable clock loss detector */
void hpdf_clock_loss_enable(hpdf_channel_enum channelx);
/* disable channel inputs pins redirection */
void hpdf_channel_pin_redirection_disable(hpdf_channel_enum channelx);
/* enable channel inputs pins redirection */
void hpdf_channel_pin_redirection_enable(hpdf_channel_enum channelx);
/* configure channel multiplexer select input data source */
void hpdf_channel_multiplexer_config(hpdf_channel_enum channelx, uint32_t data_source);
/* configure data packing mode */
void hpdf_data_pack_mode_config(hpdf_channel_enum channelx, uint32_t mode);
/* configure data right bit-shift */
void hpdf_data_right_bit_shift_config(hpdf_channel_enum channelx, uint8_t right_shift);
/* configure calibration offset */
void hpdf_calibration_offset_config(hpdf_channel_enum channelx, int32_t offset);
/* configure malfunction monitor break signal */
void hpdf_malfunction_break_signal_config(hpdf_channel_enum channelx, uint32_t break_signal);
/* configure malfunction monitor counter threshold */
void hpdf_malfunction_counter_config(hpdf_channel_enum channelx, uint8_t threshold);
/* write the parallel data on standard mode of data packing */
void hpdf_write_parallel_data_standard_mode(hpdf_channel_enum channelx, int16_t data);
/* write the parallel data on interleaved mode of data packing */
void hpdf_write_parallel_data_interleaved_mode(hpdf_channel_enum channelx, int32_t data);
/* write the parallel data on dual mode of data packing */
void hpdf_write_parallel_data_dual_mode(hpdf_channel_enum channelx, int32_t data);
/* update the number of pulses to skip */
void hpdf_pulse_skip_update(hpdf_channel_enum channelx, uint8_t number);
/* read the number of pulses to skip */
uint8_t hpdf_pulse_skip_read(hpdf_channel_enum channelx);

/* HPDF filter configuration */
/* enable filter */
void hpdf_filter_enable(hpdf_filter_enum filtery);
/* disable filter */
void hpdf_filter_disable(hpdf_filter_enum filtery);
/* configure sinc filter order and oversample */
void hpdf_filter_config(hpdf_filter_enum filtery, uint32_t order, uint16_t oversample);
/* configure integrator oversampling rate */
void hpdf_integrator_oversample(hpdf_filter_enum filtery, uint16_t oversample);

/* HPDF threshold monitor configuration */
/* configure threshold monitor filter order and oversample */
void hpdf_threshold_monitor_filter_config(hpdf_channel_enum channelx, uint32_t order, uint8_t oversample);
/* read the threshold monitor filter data */
int16_t hpdf_threshold_monitor_filter_read_data(hpdf_channel_enum channelx);
/* disable threshold monitor fast mode */
void hpdf_threshold_monitor_fast_mode_disable(hpdf_filter_enum filtery);
/* enable threshold monitor fast mode */
void hpdf_threshold_monitor_fast_mode_enable(hpdf_filter_enum filtery);
/* configure threshold monitor channel */
void hpdf_threshold_monitor_channel(hpdf_filter_enum filtery, uint32_t channel);
/* configure threshold monitor high threshold value */
void hpdf_threshold_monitor_high_threshold(hpdf_filter_enum filtery, int32_t value);
/* configure threshold monitor low threshold value */
void hpdf_threshold_monitor_low_threshold(hpdf_filter_enum filtery, int32_t value);
/* configure threshold monitor high threshold event break signal */
void hpdf_high_threshold_break_signal(hpdf_filter_enum filtery, uint32_t break_signal);
/* configure threshold monitor low threshold event break signal */
void hpdf_low_threshold_break_signal(hpdf_filter_enum filtery, uint32_t break_signal);

/* configure HPDF extremes monitor */
/* configure extremes monitor channel */
void hpdf_extremes_monitor_channel(hpdf_filter_enum filtery, uint32_t channel);
/* get the extremes monitor maximum value */
int32_t hpdf_extremes_monitor_maximum_get(hpdf_filter_enum filtery);
/* get the extremes monitor minimum value */
int32_t hpdf_extremes_monitor_minimum_get(hpdf_filter_enum filtery);

/* get the conversion timer value */
uint32_t hpdf_conversion_time_get(hpdf_filter_enum filtery);

/* configure HPDF regular conversions */
/* disable regular conversions continuous mode */
void hpdf_rc_continuous_disable(hpdf_filter_enum filtery);
/* enable regular conversions continuous mode */
void hpdf_rc_continuous_enable(hpdf_filter_enum filtery);
/* start regular channel conversion by software */
void hpdf_rc_start_by_software(hpdf_filter_enum filtery);
/* disable regular conversion synchronously */
void hpdf_rc_syn_disable(hpdf_filter_enum filtery);
/* enable regular conversion synchronously */
void hpdf_rc_syn_enable(hpdf_filter_enum filtery);
/* disable regular conversion DMA channel */
void hpdf_rc_dma_disable(hpdf_filter_enum filtery);
/* enable regular conversion DMA channel */
void hpdf_rc_dma_enable(hpdf_filter_enum filtery);
/* configure regular conversion channel */
void hpdf_rc_channel_config(hpdf_filter_enum filtery, uint32_t channel);
/* disable regular conversion fast conversion mode */
void hpdf_rc_fast_mode_disable(hpdf_filter_enum filtery);
/* enable regular conversion fast conversion mode */
void hpdf_rc_fast_mode_enable(hpdf_filter_enum filtery);
/* get the regular conversion data */
int32_t hpdf_rc_data_get(hpdf_filter_enum filtery);
/* get the channel of regular channel most recently converted */
uint8_t hpdf_rc_channel_get(hpdf_filter_enum filtery);

/* configure HPDF inserted conversions */
/* start inserted channel conversion by software */
void hpdf_ic_start_by_software(hpdf_filter_enum filtery);
/* disable inserted conversion synchronously */
void hpdf_ic_syn_disable(hpdf_filter_enum filtery);
/* enable inserted conversion synchronously */
void hpdf_ic_syn_enable(hpdf_filter_enum filtery);
/* disable inserted conversion DMA channel */
void hpdf_ic_dma_disable(hpdf_filter_enum filtery);
/* enable inserted conversion DMA channel */
void hpdf_ic_dma_enable(hpdf_filter_enum filtery);
/* disable scan conversion mode */
void hpdf_ic_scan_mode_disable(hpdf_filter_enum filtery);
/* enable scan conversion mode */
void hpdf_ic_scan_mode_enable(hpdf_filter_enum filtery);
/* disable inserted conversions trigger siganl */
void hpdf_ic_trigger_signal_disable(hpdf_filter_enum filtery);
/* configure inserted conversions trigger siganl and trigger edge */
void hpdf_ic_trigger_signal_config(hpdf_filter_enum filtery, uint32_t trigger, uint32_t trigger_edge);
/* configure inserted group conversions channel */
void hpdf_ic_channel_config(hpdf_filter_enum filtery, uint32_t channel);
/* get the inserted conversions data */
int32_t hpdf_ic_data_get(hpdf_filter_enum filtery);
/* get the channel of inserted group channel most recently converted */
uint8_t hpdf_ic_channel_get(hpdf_filter_enum filtery);

/* flag and interrupt functions */
/* get the HPDF flags */
FlagStatus hpdf_flag_get(hpdf_filter_enum filtery, hpdf_flag_enum flag);
/* clear the HPDF flags */
void hpdf_flag_clear(hpdf_filter_enum filtery, hpdf_flag_enum flag);
/* enable HPDF interrupt */
void hpdf_interrupt_enable(hpdf_filter_enum filtery, hpdf_interrput_enum interrupt);
/* disable HPDF interrupt */
void hpdf_interrupt_disable(hpdf_filter_enum filtery, hpdf_interrput_enum interrupt);
/* get the HPDF interrupt flags */
FlagStatus hpdf_interrupt_flag_get(hpdf_filter_enum filtery, hpdf_interrput_flag_enum int_flag);
/* clear the HPDF interrupt flags */
void hpdf_interrupt_flag_clear(hpdf_filter_enum filtery, hpdf_interrput_flag_enum int_flag);

#endif /* GD32H7XX_HPDF_H */
