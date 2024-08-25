/*!
    \file    gd32h7xx_hpdf.c
    \brief   HPDF driver

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

#include "gd32h7xx_hpdf.h"
#include <stdlib.h>

/* HPDF register bit offset */
#define CH0CTL_CKOUTDIV_OFFSET              ((uint32_t)0x00000010U)               /*!< bit offset of CKOUTDIV in HPDf_CH0CTL */
#define CHXCFG_DTRS_OFFSET                  ((uint32_t)0x00000003U)               /*!< bit offset of DTRS in HPDF_CH0CFG */
#define CHXCFG0_CALOFF_OFFSET               ((uint32_t)0x00000008U)               /*!< bit offset of CALOFF in HPDF_CH0CFG */
#define CHXCFG1_TMFOR_OFFSET                ((uint32_t)0x00000010U)               /*!< bit offset of TMFOR in CHXCFG1 */
#define FLTYSFCFG_SFOR_OFFSET               ((uint32_t)0x00000010U)               /*!< bit offset of SFOR in FLTYSFCFG */
#define FLTYIDATAT_IDATA_OFFSET             ((uint32_t)0x00000008U)               /*!< bit offset of IDATA in FLTYIDATA */
#define FLTYRDATAT_RDATA_OFFSET             ((uint32_t)0x00000008U)               /*!< bit offset of RDATA in FLTYRDATA */
#define FLTYTMHT_HTVAL_OFFSET               ((uint32_t)0x00000008U)               /*!< bit offset of HTVAL in FLTYTMHT */
#define FLTYTMLT_LTVAL_OFFSET               ((uint32_t)0x00000008U)               /*!< bit offset of LTVAL in FLTYTMLT */
#define FLTYEMMAX_MAXVAL_OFFSET             ((uint32_t)0x00000008U)               /*!< bit offset of MAXVAL in FLTYEMMAX */
#define FLTYEMMIN_MINVAL_OFFSET             ((uint32_t)0x00000008U)               /*!< bit offset of MINVAL in FLTYEMMIN */
#define FLTYCT_CTCNT_OFFSET                 ((uint32_t)0x00000004U)               /*!< bit offset of CTCNT in FLTYCT */
#define SIGN_BIT_OFFSET                     ((uint32_t)0x00800000U)               /*!< bit offset of signed value */

#define HPDF_WRONG_HANDLE        while(1)
{}

/*!
    \brief      reset HPDF
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hpdf_deinit(void)
{
    /* reset HPDF */
    rcu_periph_reset_enable(RCU_HPDFRST);
    rcu_periph_reset_disable(RCU_HPDFRST);
}

/*!
    \brief      initialize the parameters of HPDF channel struct with the default values
    \param[in]  init_struct: the initialization data needed to initialize HPDF
                  serial_interface: EXTERNAL_CKIN, INTERNAL_CKOUT, HALF_CKOUT_FALLING_EDGE, HALF_CKOUT_RISING_EDGE
                  spi_ck_source: SPI_RISING_EDGE, SPI_FALLING_EDGE, MANCHESTER_CODE0, MANCHESTER_CODE1
                  malfunction_monitor: MM_DISABLE, MM_ENABLE
                  calibration_offset: calibration offset(-8388608 ~ 8388607)
                  right_bit_shift: data right bit-shift(0 ~ 31)
                  channel_multiplexer: SERIAL_INPUT, INTERNAL_INPUT
                  channel_pin_select: CHPINSEL_CURRENT, CHPINSEL_NEXT
                  ck_loss_detector: CLK_LOSS_DISABLE, CLK_LOSS_ENABLE
                  data_packing_mode: DPM_STANDARD_MODE, DPM_INTERLEAVED_MODE, DPM_DUAL_MODE
                  tm_filter: TM_FASTSINC, TM_SINC1, TM_SINC2, TM_SINC3
                  tm_filter_oversample: threshold monitor filter oversampling rate(0 ~ 31), AW_FLT_BYPASS=0
                  mm_break_signal: DISABLE, ENABLE
                  mm_counter_threshold: malfunction monitor counter threshold(0 ~ 255)
                  plsk_value: the number of serial input samples that will be skipped(0 ~ 63)
    \param[out] none
    \retval     none
*/
void hpdf_channel_struct_para_init(hpdf_channel_parameter_struct *init_struct)
{
    /* check whether the struct is empty */
    if(NULL == init_struct)
    {
        HPDF_WRONG_HANDLE
    }
    /* set the struct with the default values */
    init_struct->serial_interface       = SPI_RISING_EDGE;
    init_struct->spi_ck_source          = EXTERNAL_CKIN;
    init_struct->malfunction_monitor    = MM_DISABLE;
    init_struct->calibration_offset     = 0;
    init_struct->right_bit_shift        = 0U;
    init_struct->channel_multiplexer    = SERIAL_INPUT;
    init_struct->channel_pin_select     = CHPINSEL_CURRENT;
    init_struct->ck_loss_detector       = CLK_LOSS_DISABLE;
    init_struct->data_packing_mode      = DPM_STANDARD_MODE;
    init_struct->tm_filter              = TM_FASTSINC;
    init_struct->tm_filter_oversample   = TM_FLT_BYPASS;
    init_struct->mm_break_signal        = DISABLE;
    init_struct->mm_counter_threshold   = 0U;
    init_struct->plsk_value             = 0U;
}

/*!
    \brief      initialize the parameters of HPDF filter struct with the default values
    \param[in]  init_struct: the initialization data needed to initialize HPDF
                  sinc_filter: FLT_FASTSINC, FLT_SINC1, FLT_SINC2, FLT_SINC3, FLT_SINC4, FLT_SINC5
                  sinc_oversample: sinc filter oversampling rate(0 ~ 1023), FLT_SINC_BYPASS=0
                  integrator_oversample: integrator oversampling rate(0 ~ 255), INTEGRATOR_BYPASS=0
                  tm_fast_mode: TMFM_DISABLE, TMFM_ENABLE
                  tm_channel: TMCHEN_DISABLE, TMCHEN_CHANNEL0, TMCHEN_CHANNEL1, TMCHEN_CHANNEL0_1
                  tm_high_threshold: threshold monitor high threshold(-8388608 ~ 8388607)
                  tm_low_threshold: threshold monitor low threshold value(-8388608 ~ 8388607)
                  extreme_monitor_channel: EM_CHANNEL_DISABLE, EM_CHANNEL0, EM_CHANNEL1, EM_CHANNEL0_1
                  ht_break_signal: NO_TM_HT_BREAK, TM_HT_BREAK0, TM_HT_BREAK1, TM_HT_BREAK0_1
                  lt_break_signal: NO_TM_LT_BREAK, TM_LT_BREAK0, TM_LT_BREAK1, TM_LT_BREAK0_1
    \param[out] none
    \retval     none
*/
void hpdf_filter_struct_para_init(hpdf_filter_parameter_struct *init_struct)
{
    /* check whether the struct is empty */
    if(NULL == init_struct)
    {
        HPDF_WRONG_HANDLE
    }
    /* set the struct with the default values */
    init_struct->sinc_filter                = FLT_FASTSINC;
    init_struct->sinc_oversample            = FLT_SINC_BYPASS;
    init_struct->integrator_oversample      = INTEGRATOR_BYPASS;
    init_struct->tm_fast_mode               = TMFM_DISABLE;
    init_struct->tm_channel                 = TMCHEN_DISABLE;
    init_struct->tm_high_threshold          = 0;
    init_struct->tm_low_threshold           = 0;
    init_struct->extreme_monitor_channel    = EM_CHANNEL_DISABLE;
    init_struct->ht_break_signal            = NO_TM_HT_BREAK;
    init_struct->lt_break_signal            = NO_TM_LT_BREAK;
}

/*!
    \brief      initialize the parameters of regular conversion struct with the default values
    \param[in]  init_struct: the initialization data needed to initialize HPDF
    \param[out] none
    \retval     none
*/
void hpdf_rc_struct_para_init(hpdf_rc_parameter_struct *init_struct)
{
    /* check whether the struct is empty */
    if(NULL == init_struct)
    {
        HPDF_WRONG_HANDLE
    }
    /* set the struct with the default values */
    init_struct->continuous_mode        = RCCM_DISABLE;
    init_struct->fast_mode              = FAST_DISABLE;
    init_struct->rcdmaen                = RCDMAEN_DISABLE;
    init_struct->rcsyn                  = RCSYN_DISABLE;
    init_struct->rcs_channel            = RCS_CHANNEL0;
}

/*!
    \brief      initialize the parameters of inserted conversion struct with the default values
    \param[in]  init_struct: the initialization data needed to initialize HPDF
    \param[out] none
    \retval     none
*/
void hpdf_ic_struct_para_init(hpdf_ic_parameter_struct *init_struct)
{
    /* check whether the struct is empty */
    if(NULL == init_struct)
    {
        HPDF_WRONG_HANDLE
    }
    /* set the struct with the default values */
    init_struct->scmod              = SCMOD_DISABLE;
    init_struct->icdmaen            = ICDMAEN_DISABLE;
    init_struct->ic_channel_group   = ICGSEL_CHANNEL0;
    init_struct->icsyn              = ICSYN_DISABLE;
    init_struct->trigger_edge       = TRG_DISABLE;
    init_struct->trigger_signal     = HPDF_ITRG0;
}

/*!
    \brief      enable the HPDF module globally
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hpdf_enable(void)
{
    /* enable the HPDF module globally */
    HPDF_CHXCTL(CHANNEL0) |= HPDF_CH0CTL_HPDFEN;
}

/*!
    \brief      disable the HPDF module globally
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hpdf_disable(void)
{
    /* disable the HPDF module globally */
    HPDF_CHXCTL(CHANNEL0) &= ~HPDF_CH0CTL_HPDFEN;
}

/*!
    \brief      initialize the HPDF channel
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  init_struct: the initialization data needed to initialize HPDF channel
                  serial_interface: EXTERNAL_CKIN, INTERNAL_CKOUT, HALF_CKOUT_FALLING_EDGE, HALF_CKOUT_RISING_EDGE
                  spi_ck_source: SPI_RISING_EDGE, SPI_FALLING_EDGE, MANCHESTER_CODE0, MANCHESTER_CODE1
                  malfunction_monitor: MM_DISABLE, MM_ENABLE
                  calibration_offset: calibration offset(-8388608 ~ 8388607)
                  right_bit_shift: data right bit-shift(0 ~ 31)
                  channel_multiplexer: SERIAL_INPUT, INTERNAL_INPUT
                  channel_pin_select: CHPINSEL_CURRENT, CHPINSEL_NEXT
                  ck_loss_detector: CLK_LOSS_DISABLE, CLK_LOSS_ENABLE
                  data_packing_mode: DPM_STANDARD_MODE, DPM_INTERLEAVED_MODE, DPM_DUAL_MODE
                  tm_filter: TM_FASTSINC, TM_SINC1, TM_SINC2, TM_SINC3
                  tm_filter_oversample: threshold monitor filter oversampling rate(1 ~ 32), TM_FLT_BYPASS=0
                  mm_break_signal: DISABLE, ENABLE
                  mm_counter_threshold: malfunction monitor counter threshold(0 ~ 255)
                  plsk_value: the number of serial input samples that will be skipped(0 ~ 63)
    \param[out] none
    \retval     none
*/
void hpdf_channel_init(hpdf_channel_enum channelx, hpdf_channel_parameter_struct *init_struct)
{
    uint32_t reg;
    /* configure the HPDF_CHXCTL */
    reg = HPDF_CHXCTL(channelx);
    reg &= ~(HPDF_CHXCTL_SPICKSS | HPDF_CHXCTL_SITYP | HPDF_CHXCTL_MMEN | HPDF_CHXCTL_CKLEN | HPDF_CHXCTL_CHPINSEL | \
             HPDF_CHXCTL_CMSD | HPDF_CHXCTL_DPM);
    reg |= (init_struct->spi_ck_source | init_struct->serial_interface | init_struct->malfunction_monitor | \
            init_struct->channel_multiplexer | init_struct->channel_pin_select | init_struct->ck_loss_detector | \
            init_struct->data_packing_mode);
    HPDF_CHXCTL(channelx) = reg;
    /* configure the HPDF_CHXCFG0 */
    reg = HPDF_CHXCFG0(channelx);
    reg &= ~(HPDF_CHXCFG0_CALOFF | HPDF_CHXCFG0_DTRS);
    reg |= (((uint32_t)init_struct-> calibration_offset << CHXCFG0_CALOFF_OFFSET) | (init_struct->right_bit_shift << CHXCFG_DTRS_OFFSET));
    HPDF_CHXCFG0(channelx) = reg;
    /* configure the HPDF_CHXCFG1 */
    reg = HPDF_CHXCFG1(channelx);
    reg &= ~(HPDF_CHXCFG1_TMSFO | HPDF_CHXCFG1_TMFOR | HPDF_CHXCFG1_MMBSD | HPDF_CHXCFG1_MMCT);
    reg |= (init_struct->tm_filter | ((init_struct->tm_filter_oversample - 1U) << CHXCFG1_TMFOR_OFFSET) | init_struct->mm_break_signal | \
            init_struct->mm_counter_threshold);
    HPDF_CHXCFG1(channelx) = reg;
    /* configure the HPDF_CHXPS */
    reg = HPDF_CHXPS(channelx);
    reg &= ~(HPDF_CHXPS_PLSK);
    reg |= init_struct->plsk_value;
    HPDF_CHXPS(channelx) = reg;
}

/*!
    \brief      initialize the HPDF filter
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  init_struct: the initialization data needed to initialize HPDF filter
                  sinc_filter: FLT_FASTSINC, FLT_SINC1, FLT_SINC2, FLT_SINC3, FLT_SINC4, FLT_SINC5
                  sinc_oversample: sinc filter oversampling rate(1 ~ 1024), FLT_SINC_BYPASS=0
                  integrator_oversample: integrator oversampling rate(1 ~ 256), INTEGRATOR_BYPASS=0
                  tm_fast_mode: TMFM_DISABLE, TMFM_ENABLE
                  tm_channel: TMCHEN_DISABLE, TMCHEN_CHANNELx(x=0..7)
                  tm_high_threshold: threshold monitor high threshold(-8388608 ~ 8388607)
                  tm_low_threshold: threshold monitor low threshold value(-8388608 ~ 8388607)
                  extreme_monitor_channel: EM_CHANNEL_DISABLE, EM_CHANNELx(x=0..7)
                  ht_break_signal: NO_TM_HT_BREAK, TM_HT_BREAKx(x=0..3)
                  lt_break_signal: NO_TM_LT_BREAK, TM_LT_BREAKx(x=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_filter_init(hpdf_filter_enum filtery, hpdf_filter_parameter_struct *init_struct)
{
    uint32_t reg;
    /* configure the HPDF_FLTYCTL0 */
    HPDF_FLTYCTL0(filtery) |= init_struct->tm_fast_mode;
    /* configure the HPDF_FLTYCTL1 */
    reg = HPDF_FLTYCTL1(filtery);
    reg &= ~(HPDF_FLTYCTL1_TMCHEN | HPDF_FLTYCTL1_EMCS);
    reg |= (init_struct->tm_channel | init_struct->extreme_monitor_channel);
    HPDF_FLTYCTL1(filtery) = reg;
    /* configure the HPDF_FLTYSFCTL*/
    reg = HPDF_FLTYSFCFG(filtery);
    reg &= ~(HPDF_FLTYSFCFG_SFO | HPDF_FLTYSFCFG_SFOR | HPDF_FLTYSFCFG_IOR);
    reg |= (init_struct->sinc_filter | ((init_struct->sinc_oversample - 1U) << FLTYSFCFG_SFOR_OFFSET) | (init_struct->integrator_oversample - 1U));
    HPDF_FLTYSFCFG(filtery) = reg;
    /* configure the HPDF_FLTYTMHT */
    reg = HPDF_FLTYTMHT(filtery);
    reg &= ~(HPDF_FLTYTMHT_HTVAL | HPDF_FLTYTMHT_HTBSD);
    reg |= (((uint32_t)init_struct->tm_high_threshold << FLTYTMHT_HTVAL_OFFSET) | init_struct->ht_break_signal);
    HPDF_FLTYTMHT(filtery) = reg;
    /* configure the HPDF_FLTYTMLT */
    reg = HPDF_FLTYTMLT(filtery);
    reg &= ~(HPDF_FLTYTMLT_LTVAL | HPDF_FLTYTMLT_LTBSD);
    reg |= (((uint32_t)init_struct->tm_low_threshold << FLTYTMLT_LTVAL_OFFSET) | init_struct->lt_break_signal);
    HPDF_FLTYTMLT(filtery) = reg;
}

/*!
    \brief      initialize the regular conversion
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  init_struct: the initialization data needed to initialize regular conversion
                  continuous_mode: RCCM_DISABLE, RCCM_ENABLE
                  fast_mode: FAST_DISABLE, FAST_ENABLE
                  rcdmaen: RCDMAEN_DISABLE, RCDMAEN_ENABLE
                  rcsyn: RCSYN_DISABLE, RCSYN_ENABLE
                  rcs_channel: RCS_CHANNELx(x=0..7)
    \param[out] none
    \retval     none
*/
void hpdf_rc_init(hpdf_filter_enum filtery, hpdf_rc_parameter_struct *init_struct)
{
    uint32_t reg;
    /* configure the HPDF_FLTYCTL0 */
    reg = HPDF_FLTYCTL0(filtery);
    reg &= ~(HPDF_FLTYCTL0_FAST | HPDF_FLTYCTL0_RCS | HPDF_FLTYCTL0_RCDMAEN | HPDF_FLTYCTL0_RCSYN | HPDF_FLTYCTL0_RCCM);
    reg |= (init_struct->continuous_mode | init_struct->fast_mode | init_struct->rcdmaen | init_struct->rcsyn | \
            init_struct->rcs_channel);
    HPDF_FLTYCTL0(filtery) = reg;
}

/*!
    \brief      initialize the inserted conversion
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  init_struct: the initialization data needed to initialize inserted conversion
                  scmod: SCMOD_DISABLE, SCMOD_ENABLE
                  icdmaen: ICDMAEN_DISABLE, ICDMAEN_ENABLE
                  ic_channel_group: ICGSEL_CHANNELx(x=0..7)
                  icsyn: ICSYN_DISABLE, ICSYN_ENABLE
                  trigger_dege: TRG_DISABLE, RISING_EDGE_TRG, FALLING_EDGE_TRG, EDGE_TRG
                  trigger_signal: HPDF_ITRGx(x=0..8), HPDF_ITRG11, HPDF_ITRG12, HPDF_ITRG24, HPDF_ITRG25, HPDF_ITRG31
    \param[out] none
    \retval     none
*/
void hpdf_ic_init(hpdf_filter_enum filtery, hpdf_ic_parameter_struct *init_struct)
{
    uint32_t reg;
    /* configure the HPDF_FLTYCTL0 */
    reg = HPDF_FLTYCTL0(filtery);
    reg &= ~(HPDF_FLTYCTL0_ICTEEN | HPDF_FLTYCTL0_ICTSSEL | HPDF_FLTYCTL0_ICDMAEN | HPDF_FLTYCTL0_SCMOD | \
             HPDF_FLTYCTL0_ICSYN);
    reg |= (init_struct->trigger_edge | init_struct->trigger_signal | init_struct->icdmaen | init_struct->scmod | \
            init_struct->icsyn);
    HPDF_FLTYCTL0(filtery) = reg;
    /* configure the HPDF_FLTYICGS */
    reg = HPDF_FLTYICGS(filtery);
    reg &= ~HPDF_FLTYICGS_ICGSEL;
    reg |= init_struct->ic_channel_group;
    HPDF_FLTYICGS(filtery) = reg;
}

/*!
    \brief      configure serial output clock
    \param[in]  source: the HPDF serial clock output source
                only one parameter can be selected which is shown as below:
      \arg        SERIAL_SYSTEM_CLK: serial clock output source is from system clock
      \arg        SERIAL_AUDIO_CLK: serial clock output source is from audio clock
    \param[in]  divider: serial clock output divider 0-255
    \param[in]  mode: serial clock output duty mode
                only one parameter can be selected which is shown as below:
      \arg        CKOUTDM_DISABLE: disable serial clock output duty mode
      \arg        CKOUTDM_ENABLE: enable serial clock output duty mode
    \param[out] none
    \retval     none
*/
void hpdf_clock_output_config(uint32_t source, uint8_t divider, uint32_t mode)
{
    uint32_t reg;
    reg = HPDF_CHXCTL(CHANNEL0);
    reg &= ~(HPDF_CH0CTL_CKOUTSEL | HPDF_CH0CTL_CKOUTSEL | HPDF_CH0CTL_CKOUTDM);
    /* configure serial output clock */
    reg |= (source | ((uint32_t)divider << CH0CTL_CKOUTDIV_OFFSET) | mode);
    HPDF_CHXCTL(CHANNEL0) = reg;
}

/*!
    \brief      configure serial clock output source
    \param[in]  source: the HPDF serial clock output source
      \arg        SERIAL_SYSTEM_CLK: serial clock output source is from system clock
      \arg        SERIAL_AUDIO_CLK: serial clock output source is from audio clock
    \param[out] none
    \retval     none
*/
void hpdf_clock_output_source_config(uint32_t source)
{
    uint32_t reg;
    reg = HPDF_CHXCTL(CHANNEL0);
    reg &= ~HPDF_CH0CTL_CKOUTSEL;
    reg |= source;
    HPDF_CHXCTL(CHANNEL0) = reg;
}

/*!
    \brief      disable serial clock output duty mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hpdf_clock_output_duty_mode_disable(void)
{
    /* make sure the HPDF_CH0CTL_HPDFEN=0 */
    if(RESET == (HPDF_CHXCTL(CHANNEL0) & HPDF_CH0CTL_HPDFEN))
    {
        HPDF_CHXCTL(CHANNEL0) &= ~CKOUTDM_ENABLE;
    }
}

/*!
    \brief      enable serial clock output duty mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hpdf_clock_output_duty_mode_enable(void)
{
    /* make sure the HPDF_CH0CTL_HPDFEN=0 */
    if(RESET == (HPDF_CHXCTL(CHANNEL0) & HPDF_CH0CTL_HPDFEN))
    {
        HPDF_CHXCTL(CHANNEL0) |= CKOUTDM_ENABLE;
    }
}

/*!
    \brief      configure serial clock output divider
    \param[in]  divider: serial clock output divider 0-255
    \param[out] none
    \retval     none
*/
void hpdf_clock_output_divider_config(uint8_t divider)
{
    uint32_t reg;
    /* make sure the HPDF_CH0CTL_HPDFEN=0 */
    if(RESET == (HPDF_CHXCTL(CHANNEL0) & HPDF_CH0CTL_HPDFEN))
    {
        reg = HPDF_CHXCTL(CHANNEL0);
        reg &= ~HPDF_CH0CTL_CKOUTDIV;
        reg |= ((uint32_t)divider << CH0CTL_CKOUTDIV_OFFSET);
        HPDF_CHXCTL(CHANNEL0) = reg;
    }
}

/*!
    \brief      enable the HPDF channel
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[out] none
    \retval     none
*/
void hpdf_channel_enable(hpdf_channel_enum channelx)
{
    HPDF_CHXCTL(channelx) |= HPDF_CHXCTL_CHEN;
}

/*!
    \brief      disable the HPDF channel
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[out] none
    \retval     none
*/
void hpdf_channel_disable(hpdf_channel_enum channelx)
{
    HPDF_CHXCTL(channelx) &= ~HPDF_CHXCTL_CHEN;
}

/*!
    \brief      configure SPI clock source
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  clock_source: SPI clock source
                only one parameter can be selected which is shown as below:
      \arg        EXTERNAL_CKIN: external input clock
      \arg        INTERNAL_CKOUT: internal CKOUT clock
      \arg        HALF_CKOUT_FALLING_EDGE: internal CKOUT clock, sampling point on each second CKOUT falling edge
      \arg        HALF_CKOUT_RISING_EDGE: internal CKOUT clock, sampling point on each second CKOUT rising edge
    \param[out] none
    \retval     none
*/
void hpdf_spi_clock_source_config(hpdf_channel_enum channelx, uint32_t clock_source)
{
    uint32_t reg;
    reg = HPDF_CHXCTL(channelx);
    /* make sure the CHEN=0 */
    if(RESET == (reg & HPDF_CHXCTL_CHEN))
    {
        reg &= ~HPDF_CHXCTL_SPICKSS;
        reg |= clock_source;
        HPDF_CHXCTL(channelx) = reg;
    }
}

/*!
    \brief      configure serial interface type
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  type: serial interface type
                only one parameter can be selected which is shown as below:
      \arg        SPI_RISING_EDGE: SPI interface, sample data on rising edge
      \arg        SPI_FALLING_EDGE: SPI interface, sample data on rising edge
      \arg        MANCHESTER_CODE0: Manchester coded input: rising edge = logic 0, falling edge = logic 1
      \arg        MANCHESTER_CODE1: Manchester coded input: rising edge = logic 1, falling edge = logic 0
    \param[out] none
    \retval     none
*/
void hpdf_serial_interface_type_config(hpdf_channel_enum channelx, uint32_t type)
{
    uint32_t reg;
    reg = HPDF_CHXCTL(channelx);
    /* make sure the CHEN=0 */
    if(RESET == (reg & HPDF_CHXCTL_CHEN))
    {
        reg &= ~HPDF_CHXCTL_SITYP;
        reg |= type;
        HPDF_CHXCTL(channelx) = reg;
    }
}

/*!
    \brief      disable malfunction monitor
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[out] none
    \retval     none
*/
void hpdf_malfunction_monitor_disable(hpdf_channel_enum channelx)
{
    HPDF_CHXCTL(channelx) &= ~HPDF_CHXCTL_MMEN;
}

/*!
    \brief      enable malfunction monitor
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[out] none
    \retval     none
*/
void hpdf_malfunction_monitor_enable(hpdf_channel_enum channelx)
{
    HPDF_CHXCTL(channelx) |= HPDF_CHXCTL_MMEN;
}

/*!
    \brief      disable clock loss detector
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[out] none
    \retval     none
*/
void hpdf_clock_loss_disable(hpdf_channel_enum channelx)
{
    HPDF_CHXCTL(channelx) &= ~HPDF_CHXCTL_CKLEN;
}

/*!
    \brief      enable clock loss detector
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[out] none
    \retval     none
*/
void hpdf_clock_loss_enable(hpdf_channel_enum channelx)
{
    HPDF_CHXCTL(channelx) |= HPDF_CHXCTL_CKLEN;
}

/*!
    \brief      disable channel inputs pins redirection
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[out] none
    \retval     none
*/
void hpdf_channel_pin_redirection_disable(hpdf_channel_enum channelx)
{
    /* make sure the CHEN=0 */
    if(RESET == (HPDF_CHXCTL(channelx) & HPDF_CHXCTL_CHEN))
    {
        HPDF_CHXCTL(channelx) &= ~HPDF_CHXCTL_CHPINSEL;
    }
}

/*!
    \brief      enable channel inputs pins redirection
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[out] none
    \retval     none
*/
void hpdf_channel_pin_redirection_enable(hpdf_channel_enum channelx)
{
    /* make sure the CHEN=0 */
    if(RESET == (HPDF_CHXCTL(channelx) & HPDF_CHXCTL_CHEN))
    {
        HPDF_CHXCTL(channelx) |= HPDF_CHXCTL_CHPINSEL;
    }
}

/*!
    \brief      configure channel multiplexer select input data source
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  data_source: input data source
                only one parameter can be selected which is shown as below:
      \arg        SERIAL_INPUT: input data source is taken from serial inputs
      \arg        ADC_INPUT: input data source is taken from ADC output register
      \arg        INTERNAL_INPUT: input data source is taken from internal HPDF_CHXPDI register
    \param[out] none
    \retval     none
*/
void hpdf_channel_multiplexer_config(hpdf_channel_enum channelx, uint32_t data_source)
{
    uint32_t reg;
    reg = HPDF_CHXCTL(channelx);
    /* make sure the CHEN=0 */
    if(RESET == (reg & HPDF_CHXCTL_CHEN))
    {
        reg &= ~HPDF_CHXCTL_CMSD;
        /* configure the input data source */
        reg |= data_source;
        HPDF_CHXCTL(channelx) = reg;
    }
}

/*!
    \brief      configure data packing mode
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  mode: parallel data packing mode
                only one parameter can be selected which is shown as below:
      \arg        DPM_STANDARD_MODE : standard mode
      \arg        DPM_INTERLEAVED_MODE: interleaved mode
      \arg        DPM_DUAL_MODE: dual mode
    \param[out] none
    \retval     none
*/
void hpdf_data_pack_mode_config(hpdf_channel_enum channelx, uint32_t mode)
{
    uint32_t reg;
    reg = HPDF_CHXCTL(channelx);
    /* make sure the CHEN=0 */
    if(RESET == (reg & HPDF_CHXCTL_CHEN))
    {
        reg &= ~HPDF_CHXCTL_DPM;
        /* configure the data packing mode */
        reg |= mode;
        HPDF_CHXCTL(channelx) = reg;
    }
}

/*!
    \brief      configure data right bit-shift
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  right_shift: the number of bits that determine the right shift(0-31)
    \param[out] none
    \retval     none
*/
void hpdf_data_right_bit_shift_config(hpdf_channel_enum channelx, uint8_t right_shift)
{
    uint32_t reg;
    /* make sure the CHEN=0 */
    if(RESET == (HPDF_CHXCTL(channelx) & HPDF_CHXCTL_CHEN))
    {
        reg = HPDF_CHXCFG0(channelx);
        reg &= ~HPDF_CHXCFG0_DTRS;
        /* configure the right shift */
        reg |= ((uint32_t)right_shift << CHXCFG_DTRS_OFFSET);
        HPDF_CHXCFG0(channelx) = reg;
    }
}

/*!
    \brief      configure calibration offset
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  offset: 24-bit calibration offset, must be in (-8388608~8388607)
    \param[out] none
    \retval     none
*/
void hpdf_calibration_offset_config(hpdf_channel_enum channelx, int32_t offset)
{
    uint32_t reg;
    reg = HPDF_CHXCFG0(channelx);
    reg &= ~HPDF_CHXCFG0_CALOFF;
    /* configure the calibration offset */
    reg |= ((uint32_t)offset << CHXCFG0_CALOFF_OFFSET);
    HPDF_CHXCFG0(channelx) = reg;
}

/*!
    \brief      configure malfunction monitor break signal
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  break_signal: malfunction monitor break signal distribution
                one or more parameters can be selected which is shown as below:
      \arg        NO_MM_BREAK: break signal is not distributed to malfunction monitor on channel
      \arg        MM_BREAK0: break signal 0 is distributed to malfunction monitor on channel
      \arg        MM_BREAK1: break signal 1 is distributed to malfunction monitor on channel
      \arg        MM_BREAK2: break signal 2 is distributed to malfunction monitor on channel
      \arg        MM_BREAK3: break signal 3 is distributed to malfunction monitor on channel
    \param[out] none
    \retval     none
*/
void hpdf_malfunction_break_signal_config(hpdf_channel_enum channelx, uint32_t break_signal)
{
    uint32_t reg;
    reg = HPDF_CHXCFG1(channelx);
    reg &= ~HPDF_CHXCFG1_MMBSD;
    /* configure the break signal */
    reg |= break_signal;
    HPDF_CHXCFG1(channelx) = reg;
}

/*!
    \brief      configure malfunction monitor counter threshold
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  threshold: malfunction monitor counter threshold(0-255)
    \param[out] none
    \retval     none
*/
void hpdf_malfunction_counter_config(hpdf_channel_enum channelx, uint8_t threshold)
{
    uint32_t reg;
    reg = HPDF_CHXCFG1(channelx);
    reg &= ~HPDF_CHXCFG1_MMCT;
    /* configure the malfunction monitor counter threshold */
    reg |= threshold;
    HPDF_CHXCFG1(channelx) = reg;
}

/*!
    \brief      write the parallel data on standard mode of data packing
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  data: the parallel data
    \param[out] none
    \retval     none
*/
void hpdf_write_parallel_data_standard_mode(hpdf_channel_enum channelx, int16_t data)
{
    /* make sure HPDF channel is used receive parallel data */
    if(INTERNAL_INPUT == (HPDF_CHXCTL(channelx) & INTERNAL_INPUT))
    {
        /* make sure the data pack of HPDF_CHXPDI register is standard mode */
        if(DPM_STANDARD_MODE == (HPDF_CHXCTL(channelx) & DPM_STANDARD_MODE))
        {
            HPDF_CHXPDI(channelx) = (uint16_t)data;
        }
    }
}

/*!
    \brief      write the parallel data on interleaved mode of data packing
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  data: the parallel data
    \param[out] none
    \retval     none
*/
void hpdf_write_parallel_data_interleaved_mode(hpdf_channel_enum channelx, int32_t data)
{
    /* make sure HPDF channel is used receive parallel data */
    if(INTERNAL_INPUT == (HPDF_CHXCTL(channelx) & INTERNAL_INPUT))
    {
        /* make sure the data pack of HPDF_CH0PDI register is interleaved mode */
        if(DPM_INTERLEAVED_MODE == (HPDF_CHXCTL(channelx) & DPM_INTERLEAVED_MODE))
        {
            HPDF_CHXPDI(channelx) = (uint32_t)data;
        }
    }
}

/*!
    \brief      write the parallel data on dual mode of data packing
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  data: the parallel data
    \param[out] none
    \retval     none
*/
void hpdf_write_parallel_data_dual_mode(hpdf_channel_enum channelx, int32_t data)
{
    /* make sure HPDF channel is used receive parallel data */
    if(INTERNAL_INPUT == (HPDF_CHXCTL(channelx) & INTERNAL_INPUT))
    {
        /* make sure the data pack of HPDF_CH0PDI register is dual mode */
        if(DPM_DUAL_MODE == (HPDF_CHXCTL(channelx) & DPM_DUAL_MODE))
        {
            HPDF_CHXPDI(channelx) = (uint32_t)data;
        }
    }
}

/*!
    \brief      update the number of pulses to skip
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  number: the number of serial input samples that will be skipped
    \param[out] none
    \retval     none
*/
void hpdf_pulse_skip_update(hpdf_channel_enum channelx, uint8_t number)
{
    /* update the number of pulses to skip */
    HPDF_CHXPS(channelx) = (uint32_t)number;
}

/*!
    \brief      read the number of pulses to skip
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[out] none
    \retval     the number of pulses to skip
*/
uint8_t hpdf_pulse_skip_read(hpdf_channel_enum channelx)
{
    uint8_t val;
    /* read the number of pulses to skip */
    val = (uint8_t)HPDF_CHXPS(channelx);
    return val;
}

/*!
    \brief      enable filter
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_filter_enable(hpdf_filter_enum filtery)
{
    HPDF_FLTYCTL0(filtery) |= HPDF_FLTYCTL0_FLTEN;
}

/*!
    \brief      disable filter
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_filter_disable(hpdf_filter_enum filtery)
{
    HPDF_FLTYCTL0(filtery) &= ~HPDF_FLTYCTL0_FLTEN;
}

/*!
    \brief      configure sinc filter order and oversample
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  order: sinc filter order
                only one parameter can be selected which is shown as below:
      \arg        FLT_FASTSINC: FastSinc filter type
      \arg        FLT_SINC1: Sinc1 filter type
      \arg        FLT_SINC2: Sinc2 filter type
      \arg        FLT_SINC3: Sinc3 filter type
      \arg        FLT_SINC4: Sinc4 filter type
      \arg        FLT_SINC5: Sinc5 filter type
    \param[in]  oversample: Sinc filter oversampling rate(1-1024)
    \param[out] none
    \retval     none
*/
void hpdf_filter_config(hpdf_filter_enum filtery, uint32_t order, uint16_t oversample)
{
    uint32_t reg;
    /* make sure the FLTEN=0 */
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        reg = HPDF_FLTYSFCFG(filtery);
        reg &= ~(HPDF_FLTYSFCFG_SFO | HPDF_FLTYSFCFG_SFOR);
        /* configure the sinc filter order and oversample */
        reg |= (order | (((uint32_t)oversample - 1U) << FLTYSFCFG_SFOR_OFFSET));
        HPDF_FLTYSFCFG(filtery) = reg;
    }
}

/*!
    \brief      configure integrator oversampling rate
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  oversample: integrator oversampling rate(1-256)
    \param[out] none
    \retval     none
*/
void hpdf_integrator_oversample(hpdf_filter_enum filtery, uint16_t oversample)
{
    uint32_t reg;
    /* make sure the FLTEN=0 */
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        reg = HPDF_FLTYSFCFG(filtery);
        reg &= ~HPDF_FLTYSFCFG_IOR;
        /* configure the integrator oversampling rate */
        reg |= (uint32_t)oversample - 1U;
        HPDF_FLTYSFCFG(filtery) = reg;
    }
}

/*!
    \brief      configure threshold monitor filter order and oversample
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[in]  order: threshold monitor Sinc filter order
                only one parameter can be selected which is shown as below:
      \arg        TM_FASTSINC: FastSinc filter type
      \arg        TM_SINC1: Sinc1 filter type
      \arg        TM_SINC2: Sinc2 filter type
      \arg        TM_SINC3: Sinc3 filter type
    \param[in]  oversample: Sinc filter oversampling rate(1-32)
    \param[out] none
    \retval     none
*/
void hpdf_threshold_monitor_filter_config(hpdf_channel_enum channelx, uint32_t order, uint8_t oversample)
{
    uint32_t reg;
    /* make sure the CHEN=0 */
    if(RESET == (HPDF_CHXCTL(channelx) & HPDF_CHXCTL_CHEN))
    {
        reg = HPDF_CHXCFG1(channelx);
        reg &= ~(HPDF_CHXCFG1_TMSFO | HPDF_CHXCFG1_TMFOR);
        /* configure the threshold monitor filter order and oversample rate */
        reg |= (order | (((uint32_t)oversample - 1U) << CHXCFG1_TMFOR_OFFSET));
        HPDF_CHXCFG1(channelx) = reg;
    }
}

/*!
    \brief      read the threshold monitor filter data
    \param[in]  channelx: CHANNELx(x=0..7)
    \param[out] none
    \retval     the threshold monitor filter data
*/
int16_t hpdf_threshold_monitor_filter_read_data(hpdf_channel_enum channelx)
{
    int16_t val;
    val = (int16_t)HPDF_CHXTMFDT(channelx);
    return val;
}

/*!
    \brief      disable threshold monitor fast mode
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_threshold_monitor_fast_mode_disable(hpdf_filter_enum filtery)
{
    HPDF_FLTYCTL0(filtery) &= ~HPDF_FLTYCTL0_TMFM;
}

/*!
    \brief      enable threshold monitor fast mode
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_threshold_monitor_fast_mode_enable(hpdf_filter_enum filtery)
{
    HPDF_FLTYCTL0(filtery) |= HPDF_FLTYCTL0_TMFM;
}

/*!
    \brief      configure threshold monitor channel
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  channel: which channel use threshold monitor y(x=0,3)
                one or more parameters can be selected which is shown as below:
      \arg        TMCHEN_DISABLE: threshold monitor y is disabled on all channel
      \arg        TMCHEN_CHANNELx(x=0..7) threshold monitor is enabled on channel x
    \param[out] none
    \retval     none
*/
void hpdf_threshold_monitor_channel(hpdf_filter_enum filtery, uint32_t channel)
{
    uint32_t reg;
    reg = HPDF_FLTYCTL1(filtery);
    reg &= ~HPDF_FLTYCTL1_TMCHEN;
    /* configure the channel which threshold monitor watch on */
    reg |= channel;
    HPDF_FLTYCTL1(filtery) = reg;
}

/*!
    \brief      configure threshold monitor high threshold value
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  value: high threshold value(-8388608~8388607)
    \param[out] none
    \retval     none
*/
void hpdf_threshold_monitor_high_threshold(hpdf_filter_enum filtery, int32_t value)
{
    uint32_t reg;
    reg = HPDF_FLTYTMHT(filtery);
    reg &= ~HPDF_FLTYTMHT_HTVAL;
    /* write the signed value */
    reg |= (uint32_t)value << FLTYTMHT_HTVAL_OFFSET;
    HPDF_FLTYTMHT(filtery) = reg;
}

/*!
    \brief      configure threshold monitor low threshold value
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  value: low threshold value(-8388608~8388607)
    \param[out] none
    \retval     none
*/
void hpdf_threshold_monitor_low_threshold(hpdf_filter_enum filtery, int32_t value)
{
    uint32_t reg;
    reg = HPDF_FLTYTMLT(filtery);
    reg &= ~HPDF_FLTYTMLT_LTVAL;
    /* write the signed value */
    reg |= (uint32_t)value << FLTYTMLT_LTVAL_OFFSET;
    HPDF_FLTYTMLT(filtery) = reg;
}

/*!
    \brief      configure threshold monitor high threshold event break signal
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  break_signal: HPDF break signal
                one or more parameters can be selected which is shown as below:
      \arg        NO_TM_HT_BREAK: break signal is not distributed to an threshold monitor high threshold event
      \arg        TM_HT_BREAKx(x=0..3): break signal x is distributed to an threshold monitor high threshold event
    \param[out] none
    \retval     none
*/
void hpdf_high_threshold_break_signal(hpdf_filter_enum filtery, uint32_t break_signal)
{
    uint32_t reg;
    reg = HPDF_FLTYTMHT(filtery);
    reg &= ~HPDF_FLTYTMHT_HTBSD;
    /* configure the break signal */
    reg |= break_signal;
    HPDF_FLTYTMHT(filtery) = reg;
}

/*!
    \brief      configure threshold monitor low threshold event break signal
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  break_signal: the HPDF break signal
                one or more parameters can be selected which is shown as below:
      \arg        NO_TM_LT_BREAK: break signal is not distributed to an threshold monitor low threshold event
      \arg        TM_LT_BREAKx(x=0..3): break signal x is distributed to an threshold monitor low threshold event
    \param[out] none
    \retval     none
*/
void hpdf_low_threshold_break_signal(hpdf_filter_enum filtery, uint32_t break_signal)
{
    uint32_t reg;
    reg = HPDF_FLTYTMLT(filtery);
    reg &= ~HPDF_FLTYTMLT_LTBSD;
    /* configure the break signal */
    reg |= break_signal;
    HPDF_FLTYTMLT(filtery) = reg;
}

/*!
    \brief      configure extremes monitor channel
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  channel: which channel use extremes monitor
                one or more parameters can be selected which is shown as below:
      \arg        EM_CHANNEL_DISABLE: extremes monitor y does not accept data from any channel
      \arg        EM_CHANNELx(x=0..7): extremes monitor accepts data from channel x
    \param[out] none
    \retval     none
*/
void hpdf_extremes_monitor_channel(hpdf_filter_enum filtery, uint32_t channel)
{
    uint32_t reg;
    reg = HPDF_FLTYCTL1(filtery);
    reg &= ~HPDF_FLTYCTL1_EMCS;
    /* configure the channel which channel use extremes monitor */
    reg |= channel;
    HPDF_FLTYCTL1(filtery) = reg;
}

/*!
    \brief      get the extremes monitor maximum value
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     the maximum value
*/
int32_t hpdf_extremes_monitor_maximum_get(hpdf_filter_enum filtery)
{
    uint32_t val;
    /* get the maximum value */
    val = HPDF_FLTYEMMAX(filtery) >> FLTYEMMAX_MAXVAL_OFFSET;
    /* get the sign of value */
    if(val & SIGN_BIT_OFFSET)
    {
        val |= 0xFF000000U;
    }
    return (int32_t)val;
}

/*!
    \brief      get the extremes monitor minimum value
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     the minimum value
*/
int32_t hpdf_extremes_monitor_minimum_get(hpdf_filter_enum filtery)
{
    uint32_t val;
    /* get the channel of maximum value */
    val = HPDF_FLTYEMMIN(filtery) >> FLTYEMMIN_MINVAL_OFFSET;
    /* get the sign of vlaue */
    if(val & SIGN_BIT_OFFSET)
    {
        val |= 0xFF000000U;
    }
    return (int32_t)val;
}

/*!
    \brief      get the conversion timer value
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     count value of conversion time
*/
uint32_t hpdf_conversion_time_get(hpdf_filter_enum filtery)
{
    uint32_t val;
    /* get the channel of maximum value */
    val = HPDF_FLTYCT(filtery) >> FLTYCT_CTCNT_OFFSET;
    return val;
}

/*!
    \brief      disable regular conversions continuous mode
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_rc_continuous_disable(hpdf_filter_enum filtery)
{
    HPDF_FLTYCTL0(filtery) &= ~HPDF_FLTYCTL0_RCCM;
}

/*!
    \brief      enable regular conversions continuous mode
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_rc_continuous_enable(hpdf_filter_enum filtery)
{
    HPDF_FLTYCTL0(filtery) |= HPDF_FLTYCTL0_RCCM;
}

/*!
    \brief      start regular channel conversion by software
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_rc_start_by_software(hpdf_filter_enum filtery)
{
    HPDF_FLTYCTL0(filtery) |= HPDF_FLTYCTL0_SRCS;
}

/*!
    \brief      disable regular conversion synchronously
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_rc_syn_disable(hpdf_filter_enum filtery)
{
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        HPDF_FLTYCTL0(filtery) &= ~HPDF_FLTYCTL0_RCSYN;
    }
}

/*!
    \brief      enable regular conversion synchronously
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_rc_syn_enable(hpdf_filter_enum filtery)
{
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        HPDF_FLTYCTL0(filtery) |= HPDF_FLTYCTL0_RCSYN;
    }
}

/*!
    \brief      disable regular conversion DMA channel
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_rc_dma_disable(hpdf_filter_enum filtery)
{
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        HPDF_FLTYCTL0(filtery) &= ~HPDF_FLTYCTL0_RCDMAEN;
    }
}

/*!
    \brief      enable regular conversion DMA channel
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_rc_dma_enable(hpdf_filter_enum filtery)
{
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        HPDF_FLTYCTL0(filtery) |= HPDF_FLTYCTL0_RCDMAEN;
    }
}

/*!
    \brief      configure regular conversion channel
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  channel: the regular conversion channel selection
                only one parameter can be selected which is shown as below:
      \arg        RCS_CHANNELx(x=0..7): regular conversion channel
    \param[out] none
    \retval     none
*/
void hpdf_rc_channel_config(hpdf_filter_enum filtery, uint32_t channel)
{
    uint32_t reg;
    reg = HPDF_FLTYCTL0(filtery);
    reg &= ~HPDF_FLTYCTL0_RCS;
    reg |= channel;
    HPDF_FLTYCTL0(filtery) = reg;
}

/*!
    \brief      disable regular conversion fast conversion mode
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_rc_fast_mode_disable(hpdf_filter_enum filtery)
{
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        HPDF_FLTYCTL0(filtery) &= ~HPDF_FLTYCTL0_FAST;
    }
}

/*!
    \brief      enable regular conversion fast conversion mode
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_rc_fast_mode_enable(hpdf_filter_enum filtery)
{
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        HPDF_FLTYCTL0(filtery) |= HPDF_FLTYCTL0_FAST;
    }
}

/*!
    \brief      get the regular conversions data
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     regular conversions data
*/
int32_t hpdf_rc_data_get(hpdf_filter_enum filtery)
{
    uint32_t val;
    /* get the signed data */
    val = HPDF_FLTYRDATA(filtery) >> FLTYRDATAT_RDATA_OFFSET;
    /* get the sign of vlaue */
    if(val & SIGN_BIT_OFFSET)
    {
        val |= 0xFF000000U;
    }
    return (int32_t)val;
}

/*!
    \brief      get the channel of regular group channel most recently converted
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     the channel
*/
uint8_t hpdf_rc_channel_get(hpdf_filter_enum filtery)
{
    uint8_t val;
    val = (uint8_t)HPDF_FLTYRDATA(filtery);
    val &= (uint8_t)HPDF_FLTYRDATA_RCCH;
    return val;
}

/*!
    \brief      start inserted channel conversion by software
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_ic_start_by_software(hpdf_filter_enum filtery)
{
    HPDF_FLTYCTL0(filtery) |= HPDF_FLTYCTL0_SICC;
}

/*!
    \brief      disable inserted conversion synchronously
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_ic_syn_disable(hpdf_filter_enum filtery)
{
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        HPDF_FLTYCTL0(filtery) &= ~HPDF_FLTYCTL0_ICSYN;
    }
}

/*!
    \brief      enable inserted conversion synchronously
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_ic_syn_enable(hpdf_filter_enum filtery)
{
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        HPDF_FLTYCTL0(filtery) |= HPDF_FLTYCTL0_ICSYN;
    }
}

/*!
    \brief      disable inserted conversion DMA channel
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_ic_dma_disable(hpdf_filter_enum filtery)
{
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        HPDF_FLTYCTL0(filtery) &= ~HPDF_FLTYCTL0_ICDMAEN;
    }
}

/*!
    \brief      enable inserted conversion DMA channel
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_ic_dma_enable(hpdf_filter_enum filtery)
{
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        HPDF_FLTYCTL0(filtery) |= HPDF_FLTYCTL0_ICDMAEN;
    }
}

/*!
    \brief      disable scan conversion mode
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_ic_scan_mode_disable(hpdf_filter_enum filtery)
{
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        HPDF_FLTYCTL0(filtery) &= ~HPDF_FLTYCTL0_SCMOD;
    }
}

/*!
    \brief      enable scan conversion mode
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_ic_scan_mode_enable(hpdf_filter_enum filtery)
{
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        HPDF_FLTYCTL0(filtery) |= HPDF_FLTYCTL0_SCMOD;
    }
}

/*!
    \brief      disable inserted conversions trigger siganl
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     none
*/
void hpdf_ic_trigger_signal_disable(hpdf_filter_enum filtery)
{
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        HPDF_FLTYCTL0(filtery) &= ~HPDF_FLTYCTL0_ICTEEN;
    }
}

/*!
    \brief      configure inserted conversions trigger siganl and trigger edge
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  trigger: inserted conversions trigger signal
                only one parameter can be selected which is shown as below:
      \arg        HPDF_ITRG0: TIMER0_TRGO0 is selected to start inserted conversion
      \arg        HPDF_ITRG1: TIMER0_TRGO1 is selected to start inserted conversion
      \arg        HPDF_ITRG2: TIMER7_TRGO0 is selected to start inserted conversion
      \arg        HPDF_ITRG3: TIMER7_TRGO1 is selected to start inserted conversion
      \arg        HPDF_ITRG4: TIMER2_TRGO0 is selected to start inserted conversion
      \arg        HPDF_ITRG5: TIMER3_TRGO0 is selected to start inserted conversion
      \arg        HPDF_ITRG6: TIMER15_CH1 is selected to start inserted conversion
      \arg        HPDF_ITRG7: TIMER5_TRGO0 is selected to start inserted conversion
      \arg        HPDF_ITRG8: TIMER6_TRGO0 is selected to start inserted conversion
      \arg        HPDF_ITRG11: TIMER22_TRGO0 is selected to start inserted conversion
      \arg        HPDF_ITRG12: TIMER23_TRGO0 is selected to start inserted conversion
      \arg        HPDF_ITRG24: EXTI11 is selected to start inserted conversion
      \arg        HPDF_ITRG25: EXTI15 is selected to start inserted conversion
      \arg        HPDF_ITRG31: HPDF_ITRG is selected to start inserted conversion
    \param[in]  trigger_edge: inserted conversions trigger edge
                only one parameter can be selected which is shown as below:
      \arg        TRG_DISABLE: disable trigger siganl
      \arg        RISING_EDGE_TRG: rising edge on the trigger signal
      \arg        FALLING_EDGE_TRG: falling edge on the trigger signal
      \arg        EDGE_TRG: edge (rising edges and falling edges) on the trigger signal
    \param[out] none
    \retval     none
*/
void hpdf_ic_trigger_signal_config(hpdf_filter_enum filtery, uint32_t trigger, uint32_t trigger_edge)
{
    uint32_t reg;
    /* make sure the FLTEN=0 */
    if(RESET == (HPDF_FLTYCTL0(filtery) & HPDF_FLTYCTL0_FLTEN))
    {
        reg = HPDF_FLTYCTL0(filtery);
        reg &= ~(HPDF_FLTYCTL0_ICTEEN | HPDF_FLTYCTL0_ICTSSEL);
        /* configure inserted conversions trigger siganl and trigger edge */
        reg |= (trigger | trigger_edge);
        HPDF_FLTYCTL0(filtery) = reg;
    }
}

/*!
    \brief      configure inserted group conversions channel
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  channel: the HPDF channel belongs to inserted group
                one or more parameters can be selected which is shown as below:
      \arg        ICGSEL_CHANNELx(x=0..7): channelx belongs to the inserted group
    \param[out] none
    \retval     none
*/
void hpdf_ic_channel_config(hpdf_filter_enum filtery, uint32_t channel)
{
    uint32_t reg;
    reg = HPDF_FLTYICGS(filtery);
    reg &= ~HPDF_FLTYICGS_ICGSEL;
    reg |= channel;
    HPDF_FLTYICGS(filtery) = reg;
}

/*!
    \brief      get the inserted conversions data
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     inserted conversions data
*/
int32_t hpdf_ic_data_get(hpdf_filter_enum filtery)
{
    uint32_t val;
    /* get the unsigned data  */
    val = HPDF_FLTYIDATA(filtery) >> FLTYIDATAT_IDATA_OFFSET;
    /* get the sign of value */
    if(val & SIGN_BIT_OFFSET)
    {
        val |= 0xFF000000U;
    }
    /* get the signed data */
    return (int32_t)val;
}

/*!
    \brief      get the channel of inserted group channel most recently converted
    \param[in]  filtery: FLTY(y=0..3)
    \param[out] none
    \retval     the channel
*/
uint8_t hpdf_ic_channel_get(hpdf_filter_enum filtery)
{
    uint8_t val;
    val = (uint8_t)HPDF_FLTYIDATA(filtery);
    val &= (uint8_t)HPDF_FLTYIDATA_ICCH;
    return val;
}

/*!
    \brief      get the HPDF flags
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  flag: HPDF flags, refer to hpdf_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        HPDF_FLAG_FLTY_ICEF: FLTY inserted conversion end flag
      \arg        HPDF_FLAG_FLTY_RCEF: FLTY regular conversion end flag
      \arg        HPDF_FLAG_FLTY_ICDOF: FLTY inserted conversion data overflow flag
      \arg        HPDF_FLAG_FLTY_RCDOF: FLTY regular conversion data overflow flag
      \arg        HPDF_FLAG_FLTY_TMEOF: FLTY threshold monitor event occurred flag
      \arg        HPDF_FLAG_FLTY_ICPF: FLTY inserted conversion in progress flag
      \arg        HPDF_FLAG_FLTY_RCPF: FLTY regular conversion in progress flag
      \arg        HPDF_FLAG_FLT0_CKLFx(x=0..7): clock signal is lost on channel x flag
      \arg        HPDF_FLAG_FLT0_MMFx(x=0..7): malfunction event occurred on channel x flag
      \arg        HPDF_FLAG_FLTY_RCHPDT: FLTY inserted channel most recently converted
      \arg        HPDF_FLAG_FLTY_LTFx(x=0..7): threshold monitor low threshold flag on channel x flag
      \arg        HPDF_FLAG_FLTY_HTFx(x=0..7): threshold monitor high threshold flag on channel x flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hpdf_flag_get(hpdf_filter_enum filtery, hpdf_flag_enum flag)
{
    FlagStatus flag_state = RESET;
    switch(filtery)
    {
    case FLT0:
        /* get the flag in FLT0 register */
        if(RESET != (HPDF_REG_VAL(HPDF_FLT0, flag) & BIT(HPDF_BIT_POS(flag))))
        {
            flag_state = SET;
        } else {
            flag_state = RESET;
        }
        break;
    case FLT1:
        /* get the flag in FLT1 register */
        if(RESET != (HPDF_REG_VAL(HPDF_FLT1, flag) & BIT(HPDF_BIT_POS(flag))))
        {
            flag_state = SET;
        } else {
            flag_state = RESET;
        }
        break;
    case FLT2:
        /* get the flag in FLT2 register */
        if(RESET != (HPDF_REG_VAL(HPDF_FLT2, flag) & BIT(HPDF_BIT_POS(flag))))
        {
            flag_state = SET;
        } else {
            flag_state = RESET;
        }
        break;
    case FLT3:
        /* get the flag in FLT3 register */
        if(RESET != (HPDF_REG_VAL(HPDF_FLT3, flag) & BIT(HPDF_BIT_POS(flag))))
        {
            flag_state = SET;
        } else {
            flag_state = RESET;
        }
        break;
    default :
        break;
    }
    return flag_state;
}

/*!
    \brief      clear the HPDF flags
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  flag: HPDF flags, refer to hpdf_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        HPDF_FLAG_FLTY_ICEF: FLTY inserted conversion end flag
      \arg        HPDF_FLAG_FLTY_RCEF: FLTY regular conversion end flag
      \arg        HPDF_FLAG_FLTY_ICDOF: FLTY inserted conversion data overflow flag
      \arg        HPDF_FLAG_FLTY_RCDOF: FLTY regular conversion data overflow flag
      \arg        HPDF_FLAG_FLTY_TMEOF: FLTY threshold monitor event occurred flag
      \arg        HPDF_FLAG_FLT0_CKLFx(x=0..7): clock signal is lost on channel x flag
      \arg        HPDF_FLAG_FLT0_MMFx(x=0..7): malfunction event occurred on channel x flag
      \arg        HPDF_FLAG_FLTY_LTFx(x=0..7): threshold monitor low threshold flag on channel x flag
      \arg        HPDF_FLAG_FLTY_HTFx(x=0..7): threshold monitor high threshold flag on channel x flag
    \param[out] none
    \retval     none
*/
void hpdf_flag_clear(hpdf_filter_enum filtery, hpdf_flag_enum flag)
{
    if(FLTYTMSTAT_REG_OFFSET == ((uint32_t)flag >> 6))
    {
        /* clear threshold monitor high threshold flag */
        HPDF_FLTYTMFC(filtery) |= BIT(HPDF_BIT_POS(flag));
    } else {
        switch(flag)
        {
        case HPDF_FLAG_FLTY_ICEF:
            /* read the inserted conversion data */
            HPDF_FLTYIDATA(filtery);
            break;
        case HPDF_FLAG_FLTY_RCEF:
            /* read the regular conversion data */
            HPDF_FLTYRDATA(filtery);
            break;
        case HPDF_FLAG_FLTY_TMEOF:
            /* clear the threshold monitor flag */
            HPDF_FLTYTMFC(filtery) |= (HPDF_FLTYTMFC_HTFC | HPDF_FLTYTMFC_LTFC);
            break;
        default :
            HPDF_FLTYINTC(filtery) |= BIT(HPDF_BIT_POS(flag));
            break;
        }
    }
}

/*!
    \brief      enable HPDF interrupt
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  interrupt: HPDF interrupts, refer to hpdf_interrput_enum
                only one parameter can be selected which is shown as below:
      \arg        HPDF_INT_FLTY_ICEIE: FLTY inserted conversion end interrupt enable
      \arg        HPDF_INT_FLTY_RCEIE: FLTY regular conversion end interrupt enable
      \arg        HPDF_INT_FLTY_ICDOIE: FLTY inserted conversion data overflow interrupt enable
      \arg        HPDF_INT_FLTY_RCDOIE: FLTY regular conversion data overflow interrupt enable
      \arg        HPDF_INT_FLTY_TMIE: FLTY threshold monitor interrupt enable
      \arg        HPDF_INT_FLT0_MMIE: malfunction monitor interrupt enable
      \arg        HPDF_INT_FLT0_CKLIE: clock loss interrupt enable
    \param[out] none
    \retval     none
*/
void hpdf_interrupt_enable(hpdf_filter_enum filtery, hpdf_interrput_enum interrupt)
{
    switch(filtery)
    {
    case FLT0:
        HPDF_REG_VAL(HPDF_FLT0, interrupt) |= BIT(HPDF_BIT_POS(interrupt));
        break;
    case FLT1:
        HPDF_REG_VAL(HPDF_FLT1, interrupt) |= BIT(HPDF_BIT_POS(interrupt));
        break;
    case FLT2:
        HPDF_REG_VAL(HPDF_FLT2, interrupt) |= BIT(HPDF_BIT_POS(interrupt));
        break;
    case FLT3:
        HPDF_REG_VAL(HPDF_FLT3, interrupt) |= BIT(HPDF_BIT_POS(interrupt));
        break;
    default :
        break;
    }
}

/*!
    \brief      disable HPDF interrupt
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  interrupt: HPDF interrupts, refer to hpdf_interrput_enum
                only one parameter can be selected which is shown as below:
      \arg        HPDF_INT_FLTY_ICEIE: FLTY inserted conversion interrupt enable
      \arg        HPDF_INT_FLTY_RCEIE: FLTY regular conversion interrupt enable
      \arg        HPDF_INT_FLTY_ICDOIE: FLTY inserted conversion data overflow interrupt enable
      \arg        HPDF_INT_FLTY_RCDOIE: FLTY regular conversion data overflow interrupt enable
      \arg        HPDF_INT_FLTY_TMIE: FLTY threshold monitor interrupt enable
      \arg        HPDF_INT_FLT0_MMIE: malfunction monitor interrupt enable
      \arg        HPDF_INT_FLT0_CKLIE: clock loss interrupt enable
    \param[out] none
    \retval     none
*/
void hpdf_interrupt_disable(hpdf_filter_enum filtery, hpdf_interrput_enum interrupt)
{
    switch(filtery)
    {
    case FLT0:
        HPDF_REG_VAL(HPDF_FLT0, interrupt) &= ~BIT(HPDF_BIT_POS(interrupt));
        break;
    case FLT1:
        HPDF_REG_VAL(HPDF_FLT1, interrupt) &= ~BIT(HPDF_BIT_POS(interrupt));
        break;
    case FLT2:
        HPDF_REG_VAL(HPDF_FLT2, interrupt) &= ~BIT(HPDF_BIT_POS(interrupt));
        break;
    case FLT3:
        HPDF_REG_VAL(HPDF_FLT3, interrupt) &= ~BIT(HPDF_BIT_POS(interrupt));
        break;
    default :
        break;
    }
}

/*!
    \brief      get the HPDF interrupt flags
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  int_flag: HPDF flags, refer to hpdf_interrput_enum
                only one parameter can be selected which is shown as below:
      \arg        HPDF_INT_FLAG_FLTY_ICEF: FLTY inserted conversion end interrupt flag
      \arg        HPDF_INT_FLAG_FLTY_RCEF: FLTY regular conversion end interrupt flag
      \arg        HPDF_INT_FLAG_FLTY_ICDOF: FLTY inserted conversion data overflow interrupt flag
      \arg        HPDF_INT_FLAG_FLTY_RCDOF: FLTY regular conversion data overflow interrupt flag
      \arg        HPDF_INT_FLAG_FLTY_TMEOF: FLTY threshold monitor event occurred interrupt flag
      \arg        HPDF_INT_FLAG_FLT0_CKLFx(x=0..7): clock signal is lost on channel x interrupt flag
      \arg        HPDF_INT_FLAG_FLT0_MMFx(x=0..7): malfunction event occurred on channel x interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hpdf_interrupt_flag_get(hpdf_filter_enum filtery, hpdf_interrput_flag_enum int_flag)
{
    FlagStatus flag_state = RESET;
    uint32_t int_enable = 0U, flags = 0U;
    switch(filtery)
    {
    case FLT0:
        /* get the interrupt enable bit status */
        int_enable = (HPDF_REG_VAL(HPDF_FLT0, int_flag) & BIT(HPDF_BIT_POS(int_flag)));
        /* get the interrupt enable bit status */
        flags = (HPDF_REG_VAL2(HPDF_FLT0, int_flag) & BIT(HPDF_BIT_POS2(int_flag)));
        if(flags && int_enable)
        {
            flag_state = SET;
        } else {
            flag_state = RESET;
        }
        break;
    case FLT1:
        /* get the interrupt enable bit status */
        int_enable = (HPDF_REG_VAL(HPDF_FLT1, int_flag) & BIT(HPDF_BIT_POS(int_flag)));
        /* get the interrupt enable bit status */
        flags = (HPDF_REG_VAL2(HPDF_FLT1, int_flag) & BIT(HPDF_BIT_POS2(int_flag)));
        if(flags && int_enable)
        {
            flag_state = SET;
        } else {
            flag_state = RESET;
        }
        break;
    case FLT2:
        /* get the interrupt enable bit status */
        int_enable = (HPDF_REG_VAL(HPDF_FLT2, int_flag) & BIT(HPDF_BIT_POS(int_flag)));
        /* get the interrupt enable bit status */
        flags = (HPDF_REG_VAL2(HPDF_FLT2, int_flag) & BIT(HPDF_BIT_POS2(int_flag)));
        if(flags && int_enable)
        {
            flag_state = SET;
        } else {
            flag_state = RESET;
        }
        break;
    case FLT3:
        /* get the interrupt enable bit status */
        int_enable = (HPDF_REG_VAL(HPDF_FLT3, int_flag) & BIT(HPDF_BIT_POS(int_flag)));
        /* get the interrupt enable bit status */
        flags = (HPDF_REG_VAL2(HPDF_FLT3, int_flag) & BIT(HPDF_BIT_POS2(int_flag)));
        if(flags && int_enable)
        {
            flag_state = SET;
        } else {
            flag_state = RESET;
        }
        break;
    default :
        break;
    }
    return flag_state;
}

/*!
    \brief      clear the HPDF interrupt flags
    \param[in]  filtery: FLTY(y=0..3)
    \param[in]  int_flag: HPDF flags, refer to hpdf_interrput_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        HPDF_INT_FLAG_FLTY_ICEF: FLTY inserted conversion end interrupt flag
      \arg        HPDF_INT_FLAG_FLTY_RCEF: FLTY regular conversion end interrupt flag
      \arg        HPDF_INT_FLAG_FLTY_ICDOF: FLTY inserted conversion data overflow interrupt flag
      \arg        HPDF_INT_FLAG_FLTY_RCDOF: FLTY regular conversion data overflow interrupt flag
      \arg        HPDF_INT_FLAG_FLTY_TMEOF: FLTY threshold monitor event occurred interrupt flag
      \arg        HPDF_INT_FLAG_FLT0_CKLFx(x=0..7): clock signal is lost on channelx interrupt flag
      \arg        HPDF_INT_FLAG_FLT0_MMFx(x=0..7): malfunction event occurred on channelx interrupt flag
    \param[out] none
    \retval     none
*/
void hpdf_interrupt_flag_clear(hpdf_filter_enum filtery, hpdf_interrput_flag_enum int_flag)
{
    switch(int_flag)
    {
    case HPDF_INT_FLAG_FLTY_ICEF:
        /* read the inserted conversion data */
        HPDF_FLTYIDATA(filtery);
        break;
    case HPDF_INT_FLAG_FLTY_RCEF:
        /* read the regular conversion data */
        HPDF_FLTYRDATA(filtery);
        break;
    case HPDF_INT_FLAG_FLTY_TMEOF:
        /* clear the threshold monitor flag */
        HPDF_FLTYTMFC(filtery) |= (HPDF_FLTYTMFC_HTFC | HPDF_FLTYTMFC_LTFC);
        break;
    default :
        HPDF_FLTYINTC(filtery) |= BIT(HPDF_BIT_POS2(int_flag));
        break;
    }
}
