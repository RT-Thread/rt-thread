/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_adc16_hal.h"
#if FSL_FEATURE_SOC_ADC16_COUNT

/*FUNCTION*********************************************************************
 *
 * Function Name : ADC16_HAL_Init
 * Description   :Reset all the registers into a known state for ADC
 * module. This known state is the default value indicated by the Reference
 * manual. It is strongly recommended to call this API before any operations
 * when initializing the ADC module. Note registers for calibration would not
 * be cleared in this function.
 *
 *END*************************************************************************/
void ADC16_HAL_Init(ADC_Type * base)
{
    ADC_WR_CFG1(base, 0U);
    ADC_WR_CFG2(base, 0U);
    ADC_WR_CV1(base, 0U);
    ADC_WR_CV2(base, 0U);
    ADC_WR_SC2(base, 0U);
    ADC_WR_SC3(base, 0U);
#if FSL_FEATURE_ADC16_HAS_PGA
    ADC_WR_PGA(base, 0U);
#endif /* FSL_FEATURE_ADC16_HAS_PGA */
}

#if FSL_FEATURE_ADC16_HAS_CALIBRATION

/*FUNCTION*********************************************************************
 *
 * Function Name : ADC16_HAL_GetAutoPlusSideGainValue
 * Description   :  Get the values of CLP0 - CLP4 and CLPS internally,
 * accumulate them, and return the value that can be used to be set in PG
 * register directly. Note that this API should be called after the process of
 * auto calibration has been done.
 *
 *END*************************************************************************/
uint16_t ADC16_HAL_GetAutoPlusSideGainValue(ADC_Type * base)
{
    uint16_t cal_var;

    /* Calculate plus-side calibration */
    cal_var = 0U;
    cal_var += ADC_BRD_CLP0_CLP0(base);
    cal_var += ADC_BRD_CLP1_CLP1(base);
    cal_var += ADC_BRD_CLP2_CLP2(base);
    cal_var += ADC_BRD_CLP3_CLP3(base);
    cal_var += ADC_BRD_CLP4_CLP4(base);
    cal_var += ADC_BRD_CLPS_CLPS(base);
    cal_var = 0x8000U | (cal_var>>1U);

    return cal_var;
}

#if FSL_FEATURE_ADC16_HAS_DIFF_MODE

/*FUNCTION*********************************************************************
 *
 * Function Name : ADC16_HAL_GetAutoMinusSideGainValue
 * Description   : Get the values of CLM0 - CLM4 and CLMS internally,
 * accumulate them, and return the value that can be used to be set in MG
 * register directly. Note that this API should be called after the process of
 * auto calibration has been done.
 *
 *END*************************************************************************/
uint16_t ADC16_HAL_GetAutoMinusSideGainValue(ADC_Type * base)
{
    uint16_t cal_var;

    /* Calculate minus-side calibration. */
    cal_var = 0U;
    cal_var += ADC_BRD_CLM0_CLM0(base);
    cal_var += ADC_BRD_CLM1_CLM1(base);
    cal_var += ADC_BRD_CLM2_CLM2(base);
    cal_var += ADC_BRD_CLM3_CLM3(base);
    cal_var += ADC_BRD_CLM4_CLM4(base);
    cal_var += ADC_BRD_CLMS_CLMS(base);
    cal_var = 0x8000U | (cal_var>>1U);

    return cal_var;
}

#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

/*FUNCTION*********************************************************************
 *
 * Function Name : ADC16_HAL_ConfigChn
 * Description   : Configures the channel for the ADC16 module. At any point,
 * only one of the configuration groups takes effect. The other channel mux of
 * the first group (group A, 0) is only for the hardware trigger. Both software and
 * hardware trigger can be used to the first group. When in software trigger
 * mode, once the available channel is set, the conversion begins to execute.
 *
 *END*************************************************************************/
void ADC16_HAL_ConfigChn(ADC_Type * base, uint32_t chnGroup, const adc16_chn_config_t *configPtr)
{
    assert(chnGroup < FSL_FEATURE_ADC16_CONVERSION_CONTROL_COUNT);
    uint16_t tmp = 0U;

    /* Interrupt enable. */
    if (configPtr->convCompletedIntEnable)
    {
        tmp |= ADC_SC1_AIEN_MASK;
    }

    /* Differential mode enable. */
#if FSL_FEATURE_ADC16_HAS_DIFF_MODE
    if (configPtr->diffConvEnable)
    {
        tmp |= ADC_SC1_DIFF_MASK;
    }
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */

    /* Input channel select. */
    tmp |= ADC_SC1_ADCH((uint32_t)(configPtr->chnIdx));

    ADC_WR_SC1(base, chnGroup, tmp);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : ADC16_HAL_ConfigConverter
 * Description   : Configures the sampling converter for ADC16.
 * At the most time, the configuration here are one-time setting for
 * converter's sampling condition. Usually, it would be called before
 * executing the ADC16's job.
 *
 *END*************************************************************************/
void ADC16_HAL_ConfigConverter(ADC_Type * base, const adc16_converter_config_t *configPtr)
{
    uint16_t cfg1, cfg2, sc2, sc3;

    cfg1 = ADC_RD_CFG1(base);
    cfg1 &= ~(  ADC_CFG1_ADLPC_MASK
              | ADC_CFG1_ADIV_MASK
              | ADC_CFG1_ADLSMP_MASK
              | ADC_CFG1_MODE_MASK
              | ADC_CFG1_ADICLK_MASK );

    /* Low power mode. */
    if (configPtr->lowPowerEnable)
    {
        cfg1 |= ADC_CFG1_ADLPC_MASK;
    }
    /* Clock divider. */
    cfg1 |= ADC_CFG1_ADIV(configPtr->clkDividerMode);
    /* Long sample time. */
    if (configPtr->longSampleTimeEnable)
    {
        cfg1 |= ADC_CFG1_ADLSMP_MASK;
    }
    /* Sample resolution mode. */
    cfg1 |= ADC_CFG1_MODE(configPtr->resolution);
    /* Clock source input. */
    cfg1 |= ADC_CFG1_ADICLK(configPtr->clkSrc);

    cfg2 = ADC_RD_CFG2(base);
    cfg2 &= ~( ADC_CFG2_ADACKEN_MASK
             | ADC_CFG2_ADHSC_MASK
             | ADC_CFG2_ADLSTS_MASK );
    /* Asynchronous clock output enable. */
    if (configPtr->asyncClkEnable)
    {
        cfg2 |= ADC_CFG2_ADACKEN_MASK;
    }
    /* High speed configuration. */
    if (configPtr->highSpeedEnable)
    {
        cfg2 |= ADC_CFG2_ADHSC_MASK;
    }
    /* Long sample time select. */
    cfg2 |= ADC_CFG2_ADLSTS(configPtr->longSampleCycleMode);

    sc2 = ADC_RD_SC2(base);
    sc2 &= ~( ADC_SC2_ADTRG_MASK
            | ADC_SC2_REFSEL_MASK
#if FSL_FEATURE_ADC16_HAS_DMA
            | ADC_SC2_DMAEN_MASK
#endif /* FSL_FEATURE_ADC16_HAS_DMA */
    );
    /* Conversion trigger select. */
    if (configPtr->hwTriggerEnable)
    {
        sc2 |= ADC_SC2_ADTRG_MASK;
    }
    /* Voltage reference selection. */
    sc2 |= ADC_SC2_REFSEL(configPtr->refVoltSrc);
#if FSL_FEATURE_ADC16_HAS_DMA
    /* DMA. */
    if (configPtr->dmaEnable)
    {
        sc2 |= ADC_SC2_DMAEN_MASK;
    }
#endif /* FSL_FEATURE_ADC16_HAS_DMA */

    sc3 = ADC_RD_SC3(base);
    sc3 &= ~( ADC_SC3_ADCO_MASK
            | ADC_SC3_CALF_MASK );
    /* Continuous conversion enable. */
    if (configPtr->continuousConvEnable)
    {
        sc3 |= ADC_SC3_ADCO_MASK;
    }

    ADC_WR_CFG1(base, cfg1);
    ADC_WR_CFG2(base, cfg2);
    ADC_WR_SC2(base, sc2);
    ADC_WR_SC3(base, sc3);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : ADC16_HAL_ConfigHwCompare
 * Description   : Configures the hardware compare function for ADC16.
 * The settings are mainly for the comparator inside the ADC16.
 *
 *END*************************************************************************/
void ADC16_HAL_ConfigHwCompare(ADC_Type *base, const adc16_hw_cmp_config_t *configPtr)
{
    uint16_t sc2;

    sc2 = ADC_RD_SC2(base);
    sc2 &= ~( ADC_SC2_ACFE_MASK
            | ADC_SC2_ACFGT_MASK
            | ADC_SC2_ACREN_MASK );
    /* Compare Function Enable. */
    if (configPtr->hwCmpEnable)
    {
        sc2 = ADC_SC2_ACFE_MASK;
    }
    /* Compare Function Greater Than Enable. */
    if (configPtr->hwCmpGreaterThanEnable)
    {
        sc2 |= ADC_SC2_ACFGT_MASK;
    }
    /* Compare Function Range Enable. */
    if (configPtr->hwCmpRangeEnable)
    {
        sc2 |= ADC_SC2_ACREN_MASK;
    }

    ADC_WR_SC2(base, sc2);
    ADC_BWR_CV1_CV(base, configPtr->cmpValue1);
    ADC_BWR_CV2_CV(base, configPtr->cmpValue2);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : ADC16_HAL_ConfigHwAverage
 * Description   : Configures the hardware average function for ADC16.
 * The settings are mainly for the accumulater inside the ADC16.
 *
 *END*************************************************************************/
void ADC16_HAL_ConfigHwAverage(ADC_Type *base, const adc16_hw_average_config_t *configPtr)
{
    uint16_t sc3;

    sc3 = ADC_RD_SC3(base);
    sc3 &= ~( ADC_SC3_AVGE_MASK
            | ADC_SC3_AVGS_MASK );
    /* Hardware average enable. */
    if (configPtr->hwAverageEnable)
    {
        sc3 |= ADC_SC3_AVGE_MASK;
    }
    /* Hardware average select. */
    sc3 |= ADC_SC3_AVGS(configPtr->hwAverageCountMode);

    ADC_WR_SC3(base, sc3);
}

#if FSL_FEATURE_ADC16_HAS_PGA
/*FUNCTION*********************************************************************
 *
 * Function Name : ADC16_HAL_ConfigPga
 * Description   : Configures the PGA function for ADC16.
 * The settings are mainly for the Programmable Gain Amplifier inside
 * the ADC16.
 *
 *END*************************************************************************/
void ADC16_HAL_ConfigPga(ADC_Type * base, const adc16_pga_config_t *configPtr)
{
    uint32_t pga = 0U;

    /* PGA Enable. */
    if (configPtr->pgaEnable)
    {
        pga |= ADC_PGA_PGAEN_MASK;
    }
    /* PGA chopping control. */
#if FSL_FEATURE_ADC16_HAS_PGA_CHOPPING
    if (configPtr->pgaChoppingDisable)
    {
        pga |= ADC_PGA_PGACHPb_MASK;
    }
#endif /* FSL_FEATURE_ADC16_HAS_PGA_CHOPPING */

    /* PGA low-power mode control. */
    if (configPtr->runInNormalModeEnable)
    {
        pga |= ADC_PGA_PGALPb_MASK;
    }
    /* PGA gain. */
    pga |= ADC_PGA_PGAG(configPtr->pgaGainMode);

    /* PGA Offset Measurement. */
#if FSL_FEATURE_ADC16_HAS_PGA_OFFSET_MEASUREMENT
    if (configPtr->runInOffsetMeasurementEnable)
    {
        pga |= ADC_PGA_PGAOFSM_MASK;
    }
#endif /* FSL_FEATURE_ADC16_HAS_PGA_OFFSET_MEASUREMENT */
    ADC_WR_PGA(base, pga);
}
#endif /* FSL_FEATURE_ADC16_HAS_PGA */
#endif

/******************************************************************************
 * EOF
 *****************************************************************************/

