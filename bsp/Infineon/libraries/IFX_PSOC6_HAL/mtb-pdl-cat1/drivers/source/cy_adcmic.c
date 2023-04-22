/***************************************************************************//**
* \file cy_adcmic.c
* \version 1.0
*
* Provides an API implementation of the ADCMic driver.
*
********************************************************************************
* \copyright
* Copyright 2022 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXS40ADCMIC)

#include "cy_adcmic.h"

/** \cond */
#define CY_ADCMIC_MIC_16      ((uint32_t)CY_ADCMIC_MIC)
#define CY_ADCMIC_PDM_16      ((uint32_t)CY_ADCMIC_PDM)
#define CY_ADCMIC_SR8M        (2UL) /* The sample rate 8ksps modifier */
#define CY_ADCMIC_MIC_8       ((uint32_t)CY_ADCMIC_MIC + CY_ADCMIC_SR8M)
#define CY_ADCMIC_PDM_8       ((uint32_t)CY_ADCMIC_PDM + CY_ADCMIC_SR8M)

#define CY_ADCMIC_PD_DC       (MXS40ADCMIC_ADC_PD_CTRL_ADC_EN_VBAT_Msk | \
                               MXS40ADCMIC_ADC_PD_CTRL_ADC_PWRUP_Msk | \
                               MXS40ADCMIC_ADC_PD_CTRL_ADC_REF_PWRUP_Msk | \
                               MXS40ADCMIC_ADC_PD_CTRL_ADC_CORE_PWRUP_Msk)

#define CY_ADCMIC_PD_MIC      (CY_ADCMIC_PD_DC | \
                               MXS40ADCMIC_ADC_PD_CTRL_MIC_PWRUP_Msk | \
                               MXS40ADCMIC_ADC_PD_CTRL_MICBIAS_PWRUP_Msk | \
                               MXS40ADCMIC_ADC_PD_CTRL_ADC_MODE_Msk)

#define MXS40ADCMIC_ADCMIC_CTRL_ADC_DIV_RATIO_2             (0x02UL << MXS40ADCMIC_ADCMIC_CTRL_ADC_DIV_RATIO_Pos)   /* Default adc_div_ratio value */
#define MXS40ADCMIC_ADCMIC_CTRL_PDM_DIV_RATIO_10            (0x0AUL << MXS40ADCMIC_ADCMIC_CTRL_PDM_DIV_RATIO_Pos)   /* Default pdm_div_ratio value */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_OFF         (0x00UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_Pos) /* No clocks selected - clock is gated off */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_DIV     (0x01UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_Pos) /* clk_adc from local clk_divider is selected */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_DIV_INV (0x02UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_Pos) /* Inverted clk_adc from local clk_divider is selected */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_ADC     (0x04UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_Pos) /* clk_adc received from adc is used */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_ADC_INV (0x08UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_Pos) /* Inverted clk_adc received from adc is used */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_PDM     (0x10UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_Pos) /* clk_pdm_int is used as clk_adc */

#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_OFF         (0x0UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_Pos) /* No clocks selected - clock is gated off */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_DIV     (0x1UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_Pos) /* clk_pdm from local clk_divider is selected for external clk_pdm */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_DIV_INV (0x2UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_Pos) /* Inverted clk_pdm from local clk_divider is selected for external clk_pdm */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_ADC     (0x4UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_Pos) /* clk_pdm from local clk_divider is selected as internal clk_adc to latch pdm_data */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_ADC_INV (0x8UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_Pos) /* Inverted clk_pdm from local clk_divider is selected as internal clk_adc to latch pdm_data */

#define MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_HF              (0x1UL << MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_Pos) /* Controls clk_hf clock gate */
#define MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_ADC             (0x2UL << MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_Pos) /* Controls the clk_adc_syn from the ADC block */

#define CY_ADCMIC_MODE_VALID(mode)  ((CY_ADCMIC_DC  == (mode)) || \
                                     (CY_ADCMIC_MIC == (mode)) || \
                                     (CY_ADCMIC_PDM == (mode)))

#define CY_ADCMIC_SAMPLE_RATE_VALID(sr) ((CY_ADCMIC_8KSPS   == (sr)) || \
                                         (CY_ADCMIC_16KSPS  == (sr)))

#define CY_ADCMIC_DC_CHAN_VALID(dc)     ((CY_ADCMIC_REFGND == (dc)) || \
                                         (CY_ADCMIC_BGREF  == (dc)) || \
                                         (CY_ADCMIC_VDDC   == (dc)) || \
                                         (CY_ADCMIC_VDDIO  == (dc)) || \
                                         (CY_ADCMIC_GPIO7  == (dc)) || \
                                         (CY_ADCMIC_GPIO6  == (dc)) || \
                                         (CY_ADCMIC_GPIO5  == (dc)) || \
                                         (CY_ADCMIC_GPIO4  == (dc)) || \
                                         (CY_ADCMIC_GPIO3  == (dc)) || \
                                         (CY_ADCMIC_GPIO2  == (dc)) || \
                                         (CY_ADCMIC_GPIO1  == (dc)) || \
                                         (CY_ADCMIC_GPIO0  == (dc)))

#define CY_ADCMIC_RETMODE_VALID(retMode) ((CY_ADCMIC_RETURN_STATUS   == (retMode)) || \
                                          (CY_ADCMIC_WAIT_FOR_RESULT == (retMode)))

#define CY_ADCMIC_DC_RANGE(base) (_FLD2BOOL(MXS40ADCMIC_ADC_CORE_CTRL_ADC_DCINPUT_RANGE, (base)->ADC_CORE_CTRL) ? CY_ADCMIC_DC_RANGE_1_8V : CY_ADCMIC_DC_RANGE_3_6V)
#define CY_ADCMIC_DC_GAIN(base)  ((CY_ADCMIC_DC_RANGE_3_6V == CY_ADCMIC_DC_RANGE(base)) ? CY_ADCMIC_DC_3_6_GAIN : CY_ADCMIC_DC_1_8_GAIN)
#define CY_ADCMIC_INST(base)     ((CY_IP_MXS40ADCMIC_INSTANCES == 1U) ? 0U : (MXS40ADCMIC0 == (base)) ? 0U : 1U)
#define CY_ADCMIC_MV  (1000L)      /* 1 Volt in millivolts */
#define CY_ADCMIC_UV  (1000000L)   /* 1 Volt in microvolts */
/** \endcond */

cy_en_adcmic_status_t Cy_ADCMic_Init(MXS40ADCMIC_Type * base, cy_stc_adcmic_config_t const * config, cy_en_adcmic_mode_t mode)
{
    cy_en_adcmic_status_t retVal = CY_ADCMIC_BAD_PARAM;

    if ((NULL != base) &&
        (NULL != config) &&
        CY_ADCMIC_MODE_VALID(mode))
    {
        base->ADCMIC_PAD_CTRL = 0UL;
        base->ADC_PD_CTRL = 0UL;
        CY_REG32_CLR_SET(base->AUXADC_CTRL, MXS40ADCMIC_AUXADC_CTRL_DFMODE, mode);

        switch (mode)
        {
            case CY_ADCMIC_MIC:
                if (NULL != config->micConfig)
                {
                    cy_stc_adcmic_mic_config_t const * locMicCgf = config->micConfig;

                    base->ADCMIC_CTRL = MXS40ADCMIC_ADCMIC_CTRL_ADC_DIV_RATIO_2 |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_ADC |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_ADC |
                                        MXS40ADCMIC_ADCMIC_CTRL_ADC_RESET_Msk |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_HF |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_DIV |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_ADC;
                    base->ADC_MIC_BIAS_PGA_CTRL = _VAL2FLD(MXS40ADCMIC_ADC_MIC_BIAS_PGA_CTRL_MIC_BIAS_CTRL, locMicCgf->micBias) |
                                                 _BOOL2FLD(MXS40ADCMIC_ADC_MIC_BIAS_PGA_CTRL_MIC_BIAS_LZ, locMicCgf->micBiasLz) |
                                                  _VAL2FLD(MXS40ADCMIC_ADC_MIC_BIAS_PGA_CTRL_MIC_PGA_GAIN_CTRL, locMicCgf->pgaGain) |
                                                  _VAL2FLD(MXS40ADCMIC_ADC_MIC_BIAS_PGA_CTRL_MIC_PGA_INCM_CTRL, locMicCgf->pgaInCm) |
                                                  _VAL2FLD(MXS40ADCMIC_ADC_MIC_BIAS_PGA_CTRL_MIC_PGA_OUTCM_CTRL, locMicCgf->pgaOutCm);
                    base->ADC_PD_CTRL = _BOOL2FLD(MXS40ADCMIC_ADC_PD_CTRL_MIC_CLAMP_EN, locMicCgf->micClamp);
                    base->AUXADC_CIC_STATUS = 0UL;
                    base->ADCMIC_TRIGGER_MASK = _BOOL2FLD(MXS40ADCMIC_ADCMIC_TRIGGER_TR_DATA, locMicCgf->fifoTrigger);
                    base->ADCMIC_FIFO_CTRL = MXS40ADCMIC_ADCMIC_FIFO_CTRL_FIFO_RESET_Msk |
                                    _VAL2FLD(MXS40ADCMIC_ADCMIC_FIFO_CTRL_PGMBLE_FULL,  locMicCgf->fifoFull) |
                                    _VAL2FLD(MXS40ADCMIC_ADCMIC_FIFO_CTRL_PGMBLE_EMPTY, locMicCgf->fifoEmpty);
                    base->ADC_CLK_CTRL = MXS40ADCMIC_ADC_CLK_CTRL_ADC_CLK_GATE_EN_Msk;

                    if (NULL != locMicCgf->biQuadConfig)
                    {
                        Cy_ADCMic_InitBiquad(base, locMicCgf->biQuadConfig);
                        Cy_ADCMic_BiquadBypass(base, false); /* Unbypass the biquad filter */
                    }
                    else
                    {
                        Cy_ADCMic_BiquadBypass(base, true); /* Bypass the biquad filter */
                    }

                    retVal = Cy_ADCMic_SetSampleRate(base, locMicCgf->sampleRate);
                }
                break;

            case CY_ADCMIC_PDM:
                if (NULL != config->pdmConfig)
                {
                    cy_stc_adcmic_pdm_config_t const * locPdmCgf = config->pdmConfig;

                    base->ADCMIC_CTRL = MXS40ADCMIC_ADCMIC_CTRL_ADC_DIV_RATIO_2 |
                                        MXS40ADCMIC_ADCMIC_CTRL_PDM_DIV_RATIO_10 |
                              _BOOL2FLD(MXS40ADCMIC_ADCMIC_CTRL_PDM_LATCH_NEG_EDGE, locPdmCgf->clockInv) |
                               _VAL2FLD(MXS40ADCMIC_ADCMIC_CTRL_PDM_LATCH_DELAY,    locPdmCgf->latchDelay) |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_DIV |
                                        MXS40ADCMIC_ADCMIC_CTRL_ADC_RESET_Msk |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_HF |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_DIV |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_ADC;
                    base->AUXADC_CIC_STATUS = 0UL;
                    base->ADCMIC_TRIGGER_MASK = _BOOL2FLD(MXS40ADCMIC_ADCMIC_TRIGGER_TR_DATA, locPdmCgf->fifoTrigger);
                    base->ADCMIC_FIFO_CTRL = MXS40ADCMIC_ADCMIC_FIFO_CTRL_FIFO_RESET_Msk |
                                    _VAL2FLD(MXS40ADCMIC_ADCMIC_FIFO_CTRL_PGMBLE_FULL,  locPdmCgf->fifoFull) |
                                    _VAL2FLD(MXS40ADCMIC_ADCMIC_FIFO_CTRL_PGMBLE_EMPTY, locPdmCgf->fifoEmpty);
                    base->ADC_CLK_CTRL = 0UL;
                    base->ADCMIC_PAD_CTRL = MXS40ADCMIC_ADCMIC_PAD_CTRL_CLK_PDM_OE_Msk;

                    if (NULL != locPdmCgf->biQuadConfig)
                    {
                        Cy_ADCMic_InitBiquad(base, locPdmCgf->biQuadConfig);
                        Cy_ADCMic_BiquadBypass(base, false); /* Unbypass the biquad filter */
                    }
                    else
                    {
                        Cy_ADCMic_BiquadBypass(base, true); /* Bypass the biquad filter */
                    }

                    retVal = Cy_ADCMic_SetSampleRate(base, locPdmCgf->sampleRate);
                }
                break;

            default: /* CY_ADCMIC_DC */
                if (NULL != config->dcConfig)
                {
                    cy_stc_adcmic_dc_config_t const * locDcCgf = config->dcConfig;

                    base->ADCMIC_CTRL = MXS40ADCMIC_ADCMIC_CTRL_ADC_DIV_RATIO_2 |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_ADC |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_ADC |
                                        MXS40ADCMIC_ADCMIC_CTRL_ADC_RESET_Msk |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_HF |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_DIV |
                                        MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_ADC;
                    base->ADC_CORE_CTRL = _VAL2FLD(MXS40ADCMIC_ADC_CORE_CTRL_ADC_DCINPUT_RANGE, locDcCgf->range);
                    base->ADC_GPIO_CTRL = _VAL2FLD(MXS40ADCMIC_ADC_GPIO_CTRL_ADC_DCIN_MUX, locDcCgf->channel);

                    base->AUXADC_CIC_STATUS = MXS40ADCMIC_AUXADC_CIC_STATUS_LATCH_ON_TIMER_Msk;
                    base->ADCMIC_TRIGGER_MASK = MXS40ADCMIC_ADCMIC_TRIGGER_TR_DC_Msk;
                    base->ADCMIC_FIFO_CTRL &= ~MXS40ADCMIC_ADCMIC_FIFO_CTRL_FIFO_RESET_Msk;
                    base->ADCMIC_TRIG_INTRPT_TIMER_CTRL = MXS40ADCMIC_ADCMIC_TRIG_INTRPT_TIMER_CTRL_TIMER_CLR_Msk |
                                                 _VAL2FLD(MXS40ADCMIC_ADCMIC_TRIG_INTRPT_TIMER_CTRL_TIMER_LIMIT, locDcCgf->timerPeriod) |
                                                 _VAL2FLD(MXS40ADCMIC_ADCMIC_TRIG_INTRPT_TIMER_CTRL_TIMER_INC,   locDcCgf->timerInput);
                    base->ADC_CLK_CTRL = MXS40ADCMIC_ADC_CLK_CTRL_ADC_CLK_GATE_EN_Msk;

                    Cy_ADCMic_SetDcOffset(CY_ADCMIC_DC_OFFSET, locDcCgf->context);
                    Cy_ADCMic_SetDcGain(CY_ADCMIC_DC_GAIN(base), locDcCgf->context);

                    retVal = CY_ADCMIC_SUCCESS;
                }
                break;
        }

        if (CY_ADCMIC_SUCCESS == retVal)
        {

        }
    }

    return (retVal);
}

void Cy_ADCMic_InitBiquad(MXS40ADCMIC_Type * base, cy_stc_adcmic_biquad_config_t const * biQuadConfig)
{
    base->AUXADC_BIQUAD0_COEFF_0 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD0_COEFF_0_BQ0_NUM1_COEFF, biQuadConfig->bq0_num1_coeff) |
                                   _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD0_COEFF_0_BQ0_NUM2_COEFF, biQuadConfig->bq0_num2_coeff);
    base->AUXADC_BIQUAD0_COEFF_1 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD0_COEFF_1_BQ0_NUM3_COEFF, biQuadConfig->bq0_num3_coeff);
    base->AUXADC_BIQUAD0_COEFF_2 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD0_COEFF_2_BQ0_DEN2_COEFF, biQuadConfig->bq0_den2_coeff) |
                                   _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD0_COEFF_2_BQ0_DEN3_COEFF, biQuadConfig->bq0_den3_coeff);
    base->AUXADC_BIQUAD1_COEFF_0 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD1_COEFF_0_BQ1_NUM1_COEFF, biQuadConfig->bq1_num1_coeff) |
                                   _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD1_COEFF_0_BQ1_NUM2_COEFF, biQuadConfig->bq1_num2_coeff);
    base->AUXADC_BIQUAD1_COEFF_1 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD1_COEFF_1_BQ1_NUM3_COEFF, biQuadConfig->bq1_num3_coeff);
    base->AUXADC_BIQUAD1_COEFF_2 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD1_COEFF_2_BQ1_DEN2_COEFF, biQuadConfig->bq1_den2_coeff) |
                                   _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD1_COEFF_2_BQ1_DEN3_COEFF, biQuadConfig->bq1_den3_coeff);
    base->AUXADC_BIQUAD2_COEFF_0 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD2_COEFF_0_BQ2_NUM1_COEFF, biQuadConfig->bq2_num1_coeff) |
                                   _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD2_COEFF_0_BQ2_NUM2_COEFF, biQuadConfig->bq2_num2_coeff);
    base->AUXADC_BIQUAD2_COEFF_1 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD2_COEFF_1_BQ2_NUM3_COEFF, biQuadConfig->bq2_num3_coeff);
    base->AUXADC_BIQUAD2_COEFF_2 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD2_COEFF_2_BQ2_DEN2_COEFF, biQuadConfig->bq2_den2_coeff) |
                                   _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD2_COEFF_2_BQ2_DEN3_COEFF, biQuadConfig->bq2_den3_coeff);
    base->AUXADC_BIQUAD3_COEFF_0 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD3_COEFF_0_BQ3_NUM1_COEFF, biQuadConfig->bq3_num1_coeff) |
                                   _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD3_COEFF_0_BQ3_NUM2_COEFF, biQuadConfig->bq3_num2_coeff);
    base->AUXADC_BIQUAD3_COEFF_1 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD3_COEFF_1_BQ3_NUM3_COEFF, biQuadConfig->bq3_num3_coeff);
    base->AUXADC_BIQUAD3_COEFF_2 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD3_COEFF_2_BQ3_DEN2_COEFF, biQuadConfig->bq3_den2_coeff) |
                                   _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD3_COEFF_2_BQ3_DEN3_COEFF, biQuadConfig->bq3_den3_coeff);
    base->AUXADC_BIQUAD4_COEFF_0 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD4_COEFF_0_BQ4_NUM1_COEFF, biQuadConfig->bq4_num1_coeff) |
                                   _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD4_COEFF_0_BQ4_NUM2_COEFF, biQuadConfig->bq4_num2_coeff);
    base->AUXADC_BIQUAD4_COEFF_1 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD4_COEFF_1_BQ4_NUM3_COEFF, biQuadConfig->bq4_num3_coeff);
    base->AUXADC_BIQUAD4_COEFF_2 = _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD4_COEFF_2_BQ4_DEN2_COEFF, biQuadConfig->bq4_den2_coeff) |
                                   _VAL2FLD(MXS40ADCMIC_AUXADC_BIQUAD4_COEFF_2_BQ4_DEN3_COEFF, biQuadConfig->bq4_den3_coeff);
}

cy_en_adcmic_status_t Cy_ADCMic_IsEndConversion(MXS40ADCMIC_Type * base, cy_en_adcmic_return_mode_t retMode)
{
    CY_ASSERT_L3(CY_ADCMIC_RETMODE_VALID(retMode));

    cy_en_adcmic_status_t result;

    uint32_t wdt = 0x1555555UL; /* Watchdog timer for blocking while loop */
    uint32_t mask = CY_ADCMIC_INTR_DC;
    uint32_t intr = mask & Cy_ADCMic_GetInterruptStatus(base);

    if (CY_ADCMIC_WAIT_FOR_RESULT == retMode)
    {
        while ((0UL == intr) && (0UL != wdt))
        {
            intr = mask & Cy_ADCMic_GetInterruptStatus(base);
            wdt--;
        }
    }

    /* Clear the EOS bit */
    if (mask == intr)
    {
        result = CY_ADCMIC_SUCCESS;
        Cy_ADCMic_ClearInterrupt(base, mask);
    }
    else if (0UL == wdt)
    {
        result = CY_ADCMIC_TIMEOUT;
    }
    else
    {
        result = CY_ADCMIC_CONVERSION_NOT_COMPLETE;
    }

    return result;
}

void Cy_ADCMic_EnableInterrupt(MXS40ADCMIC_Type * base, uint32_t intrMask)
{
    uint32_t interruptState = Cy_SysLib_EnterCriticalSection();
    Cy_ADCMic_SetInterruptMask(base, (intrMask & CY_ADCMIC_INTR) | Cy_ADCMic_GetInterruptMask(base));
    Cy_SysLib_ExitCriticalSection(interruptState);
}

void Cy_ADCMic_DisableInterrupt(MXS40ADCMIC_Type * base, uint32_t intrMask)
{
    uint32_t interruptState = Cy_SysLib_EnterCriticalSection();
    Cy_ADCMic_SetInterruptMask(base, (~intrMask & CY_ADCMIC_INTR) & Cy_ADCMic_GetInterruptMask(base));
    Cy_SysLib_ExitCriticalSection(interruptState);
}

cy_en_adcmic_status_t Cy_ADCMic_SetPgaGain(MXS40ADCMIC_Type *  base, cy_en_adcmic_pga_gain_t gain)
{
    cy_en_adcmic_status_t retVal = CY_ADCMIC_BAD_PARAM;

    if ((uint32_t)CY_ADCMIC_PGA_GAIN_42 >= (uint32_t)gain)
    {
        CY_REG32_CLR_SET(base->ADC_MIC_BIAS_PGA_CTRL, MXS40ADCMIC_ADC_MIC_BIAS_PGA_CTRL_MIC_PGA_GAIN_CTRL, gain);
        retVal = CY_ADCMIC_SUCCESS;
    }

    return (retVal);
}

void Cy_ADCMic_Enable (MXS40ADCMIC_Type * base)
{
    uint32_t locDfMode = _FLD2VAL(MXS40ADCMIC_AUXADC_CTRL_DFMODE, base->AUXADC_CTRL);

    base->ADC_PD_CTRL &= MXS40ADCMIC_ADC_PD_CTRL_MIC_CLAMP_EN_Msk; /* Clear all except clamp to save its value */

    if ((uint32_t)CY_ADCMIC_DC == locDfMode)
    {
        base->ADC_PD_CTRL |= CY_ADCMIC_PD_DC;
    }
    else if (((uint32_t)CY_ADCMIC_MIC_8  == locDfMode) ||
             ((uint32_t)CY_ADCMIC_MIC_16 == locDfMode))
    {
        base->ADC_PD_CTRL |= CY_ADCMIC_PD_MIC;
    }
    else /* PDM */
    {
        /* Do nothing */
    }

    base->ADCMIC_CTRL |= MXS40ADCMIC_ADCMIC_CTRL_ADCMIC_EN_Msk;
    base->AUXADC_CTRL |= MXS40ADCMIC_AUXADC_CTRL_EN_Msk;
}

void Cy_ADCMic_Disable(MXS40ADCMIC_Type * base)
{
    base->AUXADC_CTRL &= ~MXS40ADCMIC_AUXADC_CTRL_EN_Msk;
    base->ADCMIC_CTRL &= ~MXS40ADCMIC_ADCMIC_CTRL_ADCMIC_EN_Msk;
    base->ADC_PD_CTRL &=  MXS40ADCMIC_ADC_PD_CTRL_MIC_CLAMP_EN_Msk; /* Clear all except clamp to save its value */
}

cy_en_adcmic_status_t Cy_ADCMic_SetSampleRate(MXS40ADCMIC_Type * base, cy_en_adcmic_sample_rate_t sampleRate)
{
    cy_en_adcmic_status_t retVal = CY_ADCMIC_BAD_PARAM;

    if (CY_ADCMIC_SAMPLE_RATE_VALID(sampleRate))
    {
        uint32_t locDfMode = _FLD2VAL(MXS40ADCMIC_AUXADC_CTRL_DFMODE, base->AUXADC_CTRL);

        if (CY_ADCMIC_MIC_16 <= locDfMode)
        {
            if (CY_ADCMIC_8KSPS == sampleRate)
            {
                locDfMode += CY_ADCMIC_SR8M;
            }

            CY_REG32_CLR_SET(base->AUXADC_CTRL, MXS40ADCMIC_AUXADC_CTRL_DFMODE, locDfMode);
            retVal = CY_ADCMIC_SUCCESS;
        }
    }

    return (retVal);
}

uint8_t Cy_ADCMic_ReadFifoAll(MXS40ADCMIC_Type const * base, uint16_t * data)
{
    uint8_t retVal = 0U; /* data counter */
    uint8_t locStatus = Cy_ADCMic_GetFifoStatus(base);
    while (0U == (CY_ADCMIC_FIFO_EMPTY & locStatus))
    {
        uint32_t locData = Cy_ADCMic_ReadFifo(base);
        data[retVal++] = (uint16_t)_FLD2VAL(CY_ADCMIC_FIFO_FIRST_SAMPLE, locData);
        data[retVal++] = (uint16_t)_FLD2VAL(CY_ADCMIC_FIFO_SECOND_SAMPLE, locData);
        locStatus = Cy_ADCMic_GetFifoStatus(base);
    }
    return (retVal);
}

void Cy_ADCMic_SelectDcChannel(MXS40ADCMIC_Type * base, cy_en_adcmic_dc_channel_t channel)
{
    CY_ASSERT_L3(CY_ADCMIC_DC_CHAN_VALID(channel));
    CY_REG32_CLR_SET(base->ADC_GPIO_CTRL, MXS40ADCMIC_ADC_GPIO_CTRL_ADC_DCIN_MUX, channel);
}


/* DC voltage calculation / calibration */
void Cy_ADCMic_SetDcOffset(int16_t offset, cy_stc_adcmic_context_t * context)
{
    if (NULL != context)
    {
        context->offset = offset;
    }
}

void Cy_ADCMic_SetDcGain(int16_t gain, cy_stc_adcmic_context_t * context)
{
    if (NULL != context)
    {
        context->gain = gain;
    }
}

int32_t Cy_ADCMic_CountsTo_uVolts(int16_t adcCounts, cy_stc_adcmic_context_t const * context)
{
    return ((int32_t)(((int64_t)adcCounts - (int64_t)context->offset) * CY_ADCMIC_UV / (int64_t)context->gain));
}

int16_t Cy_ADCMic_CountsTo_mVolts(int16_t adcCounts, cy_stc_adcmic_context_t const * context)
{
    return ((int16_t)(((int32_t)adcCounts - (int32_t)context->offset) * CY_ADCMIC_MV / (int32_t)context->gain));
}

float Cy_ADCMic_CountsTo_Volts (int16_t adcCounts, cy_stc_adcmic_context_t const * context)
{
    return (((float)adcCounts - (float)context->offset) / (float)context->gain);
}

#endif /* CY_IP_MXS40ADCMIC */
