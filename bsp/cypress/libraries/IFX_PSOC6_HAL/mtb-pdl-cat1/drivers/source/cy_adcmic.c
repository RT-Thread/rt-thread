/***************************************************************************//**
* \file cy_adcmic.c
* \version 0.1
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


#define CY_ADCMIC_SR8M        (2UL) /* The sample rate 8ksps modifier */

#define CY_ADCMIC_DC_480_FAST ((uint32_t)CY_ADCMIC_DC_CONV_TIME_10_US)
#define CY_ADCMIC_DC_480_MED  ((uint32_t)CY_ADCMIC_DC_CONV_TIME_15_US)
#define CY_ADCMIC_DC_480_SLOW ((uint32_t)CY_ADCMIC_DC_CONV_TIME_20_US)
#define CY_ADCMIC_MIC_16      ((uint32_t)CY_ADCMIC_MIC)
#define CY_ADCMIC_PDM_16      ((uint32_t)CY_ADCMIC_PDM)
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

#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_OFF         (0x00UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_Pos) /* No clocks selected - clock is gated off */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_DIV     (0x01UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_Pos) /* clk_adc from local clk_divder is selected */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_DIV_INV (0x02UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_Pos) /* Inverted clk_adc from local clk_divder is selected */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_ADC     (0x04UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_Pos) /* clk_adc received from adc is used */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_ADC_INV (0x08UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_Pos) /* Inverted clk_adc received from adc is used */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_PDM     (0x10UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_Pos) /* clk_pdm_int is used as clk_adc */

#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_OFF         (0x0UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_Pos) /* No clocks selected - clock is gated off */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_DIV     (0x1UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_Pos) /* clk_pdm from local clk_divder is selected for external clk_pdm */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_DIV_INV (0x2UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_Pos) /* Inverted clk_pdm from local clk_divder is selected for external clk_pdm */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_ADC     (0x4UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_Pos) /* clk_pdm from local clk_divder is selected as internal clk_adc to latch pdm_data */
#define MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_ADC_INV (0x8UL << MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_Pos) /* Inverted clk_pdm from local clk_divder is selected as internal clk_adc to latch pdm_data */

#define MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_HF              (0x1UL << MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_Pos) /* Controls clk_hf clock gate */
#define MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_ADC             (0x2UL << MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_Pos) /* Controls the clk_adc_syn from the ADC block */

#define CY_ADCMIC_SOURCE_VALID(src) ((CY_ADCMIC_DC  == (src)) || \
                                     (CY_ADCMIC_MIC == (src)) || \
                                     (CY_ADCMIC_PDM == (src)))

#define CY_ADCMIC_SAMPLE_RATE_VALID(sr) ((CY_ADCMIC_8KSPS   == (sr)) || \
                                         (CY_ADCMIC_16KSPS  == (sr)) || \
                                         (CY_ADCMIC_480KSPS == (sr)))

#define CY_ADCMIC_CONV_TIME_VALID(time) ((CY_ADCMIC_DC_480_FAST == (uint32_t)(time)) || \
                                         (CY_ADCMIC_DC_480_MED  == (uint32_t)(time)) || \
                                         (CY_ADCMIC_DC_480_SLOW == (uint32_t)(time)))

#define CY_ADCMIC_DC_CHAN_VALID(dc)     ((CY_ADCMIC_REFGND == (dc)) || \
                                         (CY_ADCMIC_BGREF  == (dc)) || \
                                         (CY_ADCMIC_VDDC   == (dc)) || \
                                         (CY_ADCMIC_VDDIO  == (dc)) || \
                                         (CY_ADCMIC_GPIO27 == (dc)) || \
                                         (CY_ADCMIC_GPIO26 == (dc)) || \
                                         (CY_ADCMIC_GPIO25 == (dc)) || \
                                         (CY_ADCMIC_GPIO24 == (dc)) || \
                                         (CY_ADCMIC_GPIO23 == (dc)) || \
                                         (CY_ADCMIC_GPIO22 == (dc)) || \
                                         (CY_ADCMIC_GPIO21 == (dc)) || \
                                         (CY_ADCMIC_GPIO20 == (dc)) || \
                                         (CY_ADCMIC_GPIO19 == (dc)) || \
                                         (CY_ADCMIC_GPIO18 == (dc)) || \
                                         (CY_ADCMIC_GPIO17 == (dc)) || \
                                         (CY_ADCMIC_GPIO16 == (dc)) || \
                                         (CY_ADCMIC_GPIO15 == (dc)) || \
                                         (CY_ADCMIC_GPIO14 == (dc)) || \
                                         (CY_ADCMIC_GPIO13 == (dc)) || \
                                         (CY_ADCMIC_GPIO12 == (dc)) || \
                                         (CY_ADCMIC_GPIO11 == (dc)) || \
                                         (CY_ADCMIC_GPIO10 == (dc)) || \
                                         (CY_ADCMIC_GPIO9  == (dc)) || \
                                         (CY_ADCMIC_GPIO8  == (dc)) || \
                                         (CY_ADCMIC_GPIO7  == (dc)) || \
                                         (CY_ADCMIC_GPIO6  == (dc)) || \
                                         (CY_ADCMIC_GPIO5  == (dc)) || \
                                         (CY_ADCMIC_GPIO4  == (dc)) || \
                                         (CY_ADCMIC_GPIO3  == (dc)) || \
                                         (CY_ADCMIC_GPIO2  == (dc)) || \
                                         (CY_ADCMIC_GPIO1  == (dc)) || \
                                         (CY_ADCMIC_GPIO0  == (dc)))

#define CY_ADCMIC_DC_RANGE(base) (_FLD2BOOL(MXS40ADCMIC_ADC_CORE_CTRL_ADC_DCINPUT_RANGE, (base)->ADC_CORE_CTRL) ? CY_ADCMIC_DC_RANGE_1_8V : CY_ADCMIC_DC_RANGE_3_6V)
#define CY_ADCMIC_DC_GAIN(base)  ((CY_ADCMIC_DC_RANGE_3_6V == CY_ADCMIC_DC_RANGE(base)) ? CY_ADCMIC_DC_3_6_GAIN : CY_ADCMIC_DC_1_8_GAIN)
#define CY_ADCMIC_INST(base)     ((CY_IP_MXS40ADCMIC_INSTANCES == 1U) ? 0U : (MXS40ADCMIC0 == (base)) ? 0U : 1U)
#define CY_ADCMIC_MV  (1000L)      /* 1 Volt in millivolts */
#define CY_ADCMIC_UV  (1000000L)   /* 1 Volt in microvolts */
/** \endcond */


cy_en_adcmic_status_t Cy_ADCMic_Init(MXS40ADCMIC_Type * base, cy_stc_adcmic_config_t const * config)
{
    cy_en_adcmic_status_t retVal = CY_ADCMIC_BAD_PARAM;

    if ((NULL != base) &&
        (NULL != config) &&
        CY_ADCMIC_SOURCE_VALID(config->source) &&
        CY_ADCMIC_SAMPLE_RATE_VALID(config->sampleRate) &&
        ((NULL == config->dcConfig) || CY_ADCMIC_CONV_TIME_VALID(config->dcConfig->time)))
    {
        switch (config->source)
        {
            case CY_ADCMIC_MIC:
                if ((NULL != config->anaConfig) && (CY_ADCMIC_480KSPS != config->sampleRate))
                {
                    base->ADCMIC_CTRL = MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_ADC | MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_ADC;
                    base->ADC_MIC_BIAS_PGA_CTRL = _VAL2FLD(MXS40ADCMIC_ADC_MIC_BIAS_PGA_CTRL_MIC_BIAS_CTRL, config->anaConfig->micBias) |
                                                 _BOOL2FLD(MXS40ADCMIC_ADC_MIC_BIAS_PGA_CTRL_MIC_BIAS_LZ, config->anaConfig->micBiasLz) |
                                                  _VAL2FLD(MXS40ADCMIC_ADC_MIC_BIAS_PGA_CTRL_MIC_PGA_GAIN_CTRL, config->anaConfig->pgaGain) |
                                                  _VAL2FLD(MXS40ADCMIC_ADC_MIC_BIAS_PGA_CTRL_MIC_PGA_INCM_CTRL, config->anaConfig->pgaInCm) |
                                                  _VAL2FLD(MXS40ADCMIC_ADC_MIC_BIAS_PGA_CTRL_MIC_PGA_OUTCM_CTRL, config->anaConfig->pgaOutCm);
                    CY_REG32_CLR_SET(base->ADC_PD_CTRL, MXS40ADCMIC_ADC_PD_CTRL_ADC_MIC_PDSLT, (config->anaConfig->micPd) ? 0UL : 1UL);

                    retVal = CY_ADCMIC_SUCCESS;
                }
                break;

            case CY_ADCMIC_PDM:
                if ((NULL != config->digConfig) && (CY_ADCMIC_480KSPS != config->sampleRate))
                {
                    base->ADCMIC_CTRL = _VAL2FLD(MXS40ADCMIC_ADCMIC_CTRL_PDM_DIV_RATIO,      config->digConfig->clockDiv) |
                                       _BOOL2FLD(MXS40ADCMIC_ADCMIC_CTRL_PDM_LATCH_NEG_EDGE, config->digConfig->clockInv) |
                                        _VAL2FLD(MXS40ADCMIC_ADCMIC_CTRL_PDM_LATCH_DELAY,    config->digConfig->latchDelay) |
                                                 MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_DIV;

                    retVal = CY_ADCMIC_SUCCESS;
                }
                break;

            default: /* CY_ADCMIC_DC */
                if ((NULL != config->dcConfig) && (CY_ADCMIC_480KSPS == config->sampleRate))
                {
                    base->ADCMIC_CTRL = MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_ADC_CLK_ADC | MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_ADC;
                    base->ADC_CORE_CTRL = _VAL2FLD(MXS40ADCMIC_ADC_CORE_CTRL_ADC_DCINPUT_RANGE, config->dcConfig->range);
                    base->ADC_GPIO_CTRL = _VAL2FLD(MXS40ADCMIC_ADC_GPIO_CTRL_ADC_DCIN_MUX, config->dcConfig->input);

                    CY_REG32_CLR_SET(base->AUXADC_CIC_STATUS, MXS40ADCMIC_AUXADC_CIC_STATUS_LATCH_ON_TIMER, (config->dcConfig->tmrLatch) ? 1UL : 0UL);

                    Cy_ADCMic_SetDcOffset(base, CY_ADCMIC_DC_OFFSET);
                    Cy_ADCMic_SetDcGain(base, CY_ADCMIC_DC_GAIN(base));

                    retVal = CY_ADCMIC_SUCCESS;
                }
                break;
        }

        if (CY_ADCMIC_SUCCESS == retVal)
        {
            base->ADCMIC_CTRL |= _VAL2FLD(MXS40ADCMIC_ADCMIC_CTRL_ADC_DIV_RATIO, config->clockDiv) |
                                          MXS40ADCMIC_ADCMIC_CTRL_ADC_RESET_Msk |
                                          MXS40ADCMIC_ADCMIC_CTRL_CLK_GATE_EN_HF |
                                          MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_DIV |
                                          MXS40ADCMIC_ADCMIC_CTRL_CLKS_ACTIVE_PDM_CLK_ADC;

            (void) Cy_ADCMic_SelectSource(base, config->source);

            if (CY_ADCMIC_DC != config->source)
            {
                (void) Cy_ADCMic_SetSampleRate(base, config->sampleRate);
            }
            else
            {
                (void) Cy_ADCMic_SetDcConvTime(base, config->dcConfig->time);
            }

            if (NULL != config->biQuadConfig)
            {
                Cy_ADCMic_InitBiquad(base, config->biQuadConfig);
                Cy_ADCMic_BiquadBypass(base, false); /* Unbypass the biquad filter */
            }
            else
            {
                Cy_ADCMic_BiquadBypass(base, true); /* Bypass the biquad filter */
            }

            if (NULL != config->fifoConfig)
            {
                base->ADCMIC_FIFO_CTRL = MXS40ADCMIC_ADCMIC_FIFO_CTRL_FIFO_RESET_Msk |
                                _VAL2FLD(MXS40ADCMIC_ADCMIC_FIFO_CTRL_PGMBLE_FULL,  config->fifoConfig->full) |
                                _VAL2FLD(MXS40ADCMIC_ADCMIC_FIFO_CTRL_PGMBLE_EMPTY, config->fifoConfig->empty);
            }
            else
            {
                base->ADCMIC_FIFO_CTRL &= ~MXS40ADCMIC_ADCMIC_FIFO_CTRL_FIFO_RESET_Msk;
            }

            if (NULL != config->tmrTrgConfig)
            {
                base->ADCMIC_TRIGGER_MASK = _BOOL2FLD(MXS40ADCMIC_ADCMIC_TRIGGER_TR_DC,  config->tmrTrgConfig->timerTrigger) |
                                            _BOOL2FLD(MXS40ADCMIC_ADCMIC_TRIGGER_TR_DATA, config->tmrTrgConfig->fifoTrigger);

                base->ADCMIC_TRIG_INTRPT_TIMER_CTRL = _VAL2FLD(MXS40ADCMIC_ADCMIC_TRIG_INTRPT_TIMER_CTRL_TIMER_LIMIT, config->tmrTrgConfig->period) |
                                                      _VAL2FLD(MXS40ADCMIC_ADCMIC_TRIG_INTRPT_TIMER_CTRL_TIMER_INC,   config->tmrTrgConfig->input);
            }
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
    base->AUXADC_CTRL &= ~MXS40ADCMIC_AUXADC_CTRL_BIQUAD_BYPASS_Msk;
}


cy_en_adcmic_status_t  Cy_ADCMic_IsEndConversion (MXS40ADCMIC_Type * base, cy_en_adcmic_return_mode_t retMode)
{
    /* CY_ASSERT_L3(CY_ADCMIC_RETURN(retMode)); */

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


cy_en_adcmic_status_t Cy_ADCMic_SelectSource(MXS40ADCMIC_Type * base, cy_en_adcmic_source_t source)
{
    cy_en_adcmic_status_t retVal = CY_ADCMIC_BAD_PARAM;

    if (CY_ADCMIC_SOURCE_VALID(source))
    {
        CY_REG32_CLR_SET(base->AUXADC_CTRL, MXS40ADCMIC_AUXADC_CTRL_DFMODE, source);
        retVal = CY_ADCMIC_SUCCESS;

        switch (source)
        {
            case CY_ADCMIC_MIC:
                base->ADCMIC_PAD_CTRL = 0UL;
                base->ADC_PD_CTRL |= CY_ADCMIC_PD_MIC;
                base->ADC_CLK_CTRL |= MXS40ADCMIC_ADC_CLK_CTRL_ADC_CLK_GATE_EN_Msk;
                break;

            case CY_ADCMIC_PDM:
                base->ADCMIC_PAD_CTRL = MXS40ADCMIC_ADCMIC_PAD_CTRL_CLK_PDM_OE_Msk;
                base->ADC_PD_CTRL = 0UL;
                base->ADC_CLK_CTRL = 0UL;
                break;
                
            default: /* CY_ADCMIC_DC */
                base->ADCMIC_PAD_CTRL = 0UL;
                base->ADC_PD_CTRL &= ~CY_ADCMIC_PD_MIC;
                base->ADC_PD_CTRL |= CY_ADCMIC_PD_DC;
                base->ADC_CLK_CTRL |= MXS40ADCMIC_ADC_CLK_CTRL_ADC_CLK_GATE_EN_Msk;
                break;
        }
    }

    return (retVal);
}


static inline uint32_t Cy_ADCMic_GetDfMode(MXS40ADCMIC_Type const * base)
{
    return (_FLD2VAL(MXS40ADCMIC_AUXADC_CTRL_DFMODE, base->AUXADC_CTRL));
}


static inline void Cy_ADCMic_SetDfMode(MXS40ADCMIC_Type * base, uint32_t dfMode)
{
    CY_REG32_CLR_SET(base->AUXADC_CTRL, MXS40ADCMIC_AUXADC_CTRL_DFMODE, dfMode);
}


cy_en_adcmic_status_t Cy_ADCMic_SetSampleRate(MXS40ADCMIC_Type * base, cy_en_adcmic_sample_rate_t sampleRate)
{
    cy_en_adcmic_status_t retVal = CY_ADCMIC_BAD_PARAM;

    if (CY_ADCMIC_SAMPLE_RATE_VALID(sampleRate))
    {
        uint32_t locDfMode = Cy_ADCMic_GetDfMode(base);

        if (((uint32_t)CY_ADCMIC_DC_480_SLOW >= locDfMode) && (CY_ADCMIC_480KSPS == sampleRate))
        {
            retVal = CY_ADCMIC_SUCCESS;
        }
        else if (((uint32_t)CY_ADCMIC_DC_480_SLOW < locDfMode) && (CY_ADCMIC_480KSPS != sampleRate))
        {
            if (CY_ADCMIC_8KSPS == sampleRate)
            {
                locDfMode += CY_ADCMIC_SR8M;
            }

            Cy_ADCMic_SetDfMode(base, locDfMode);
            retVal = CY_ADCMIC_SUCCESS;
        }
        else
        {
            /* Return CY_ADCMIC_BAD_PARAM */
        }
    }

    return (retVal);
}


cy_en_adcmic_status_t Cy_ADCMic_SetDcConvTime(MXS40ADCMIC_Type * base, cy_en_adcmic_dc_conv_time_t time)
{
    cy_en_adcmic_status_t retVal = CY_ADCMIC_BAD_PARAM;

    if (CY_ADCMIC_CONV_TIME_VALID(time))
    {
        uint32_t locDfMode = Cy_ADCMic_GetDfMode(base);

        if (CY_ADCMIC_CONV_TIME_VALID(locDfMode))
        {
            if (locDfMode != (uint32_t)time)
            {
                Cy_ADCMic_SetDfMode(base, (uint32_t)time);
            }

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


void Cy_ADCMic_SelectDcChannel(MXS40ADCMIC_Type * base, cy_en_adcmic_dc_channel_t dcChannel)
{
    CY_ASSERT_L3(CY_ADCMIC_DC_CHAN_VALID(dcChannel));
    CY_REG32_CLR_SET(base->ADC_GPIO_CTRL, MXS40ADCMIC_ADC_GPIO_CTRL_ADC_DCIN_MUX, dcChannel);
}


/* DC voltage calculation / calibration */
static int16_t Cy_ADCMic_offset[CY_IP_MXS40ADCMIC_INSTANCES]; /* The storage for offset calibration values */
static int16_t Cy_ADCMic_gain[CY_IP_MXS40ADCMIC_INSTANCES];   /* The storage for gain calibration values */

void Cy_ADCMic_SetDcOffset(MXS40ADCMIC_Type const * base, int16_t offset)
{
    Cy_ADCMic_offset[CY_ADCMIC_INST(base)] = offset;
}

void Cy_ADCMic_SetDcGain(MXS40ADCMIC_Type const * base, int16_t gain)
{
    Cy_ADCMic_gain[CY_ADCMIC_INST(base)] = gain;
}

int32_t Cy_ADCMic_CountsTo_uVolts(MXS40ADCMIC_Type const * base, int16_t adcCounts)
{
    return ((int32_t)(((int64_t)adcCounts - (int64_t)Cy_ADCMic_offset[CY_ADCMIC_INST(base)]) * CY_ADCMIC_UV / (int64_t)Cy_ADCMic_gain[CY_ADCMIC_INST(base)]));
}

int16_t Cy_ADCMic_CountsTo_mVolts(MXS40ADCMIC_Type const * base, int16_t adcCounts)
{
    return ((int16_t)(((int32_t)adcCounts - (int32_t)Cy_ADCMic_offset[CY_ADCMIC_INST(base)]) * CY_ADCMIC_MV / (int32_t)Cy_ADCMic_gain[CY_ADCMIC_INST(base)]));
}

float Cy_ADCMic_CountsTo_Volts (MXS40ADCMIC_Type const * base, int16_t adcCounts)
{
    return (((float)adcCounts - (float)Cy_ADCMic_offset[CY_ADCMIC_INST(base)]) / (float)Cy_ADCMic_gain[CY_ADCMIC_INST(base)]);
}

#endif /* CY_IP_MXS40ADCMIC */
