/***************************************************************************//**
* \file cy_sar2.c
* \version 1.0
*
* Provides API implementation of the SAR2 Driver.
*
*******************************************************************************
* \copyright
* (c) (2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cy_sar2.h"

#if defined (CY_IP_MXS40EPASS_ESAR)

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.8', 6, \
'Checked manually. Type cast to int8_t made intentionally.');

#define GET_SFLASH_VALUE(x)                     CY_GET_REG16(x)
#define GET_TRIM_VALUE(x)                       (GET_SFLASH_VALUE(x) & 0xFFFFu)

#define CY_SAR2_DIODE_COLD(t)  (((t) == CY_SAR2_VDDA_2_7V_TO_4_5V) ? \
 (SFLASH->EPASS_TEMP_TRIM_DIODE_COLDSORT) : (SFLASH->EPASS_TEMP_TRIM_DIODE_COLDSORT_5V))

#define CY_SAR2_DIODE_ROOM(t)  (((t) == CY_SAR2_VDDA_2_7V_TO_4_5V) ? \
 (SFLASH->EPASS_TEMP_TRIM_DIODE_ROOMSORT) : (SFLASH->EPASS_TEMP_TRIM_DIODE_ROOMSORT_5V))

#define CY_SAR2_DIODE_HOT(t)  (((t) == CY_SAR2_VDDA_2_7V_TO_4_5V) ? \
 (SFLASH->EPASS_TEMP_TRIM_DIODE_HOTCLASS) : (SFLASH->EPASS_TEMP_TRIM_DIODE_HOTCLASS_5V))

 #define CY_SAR2_VBG_COLD(t)  (((t) == CY_SAR2_VDDA_2_7V_TO_4_5V) ? \
 (SFLASH->EPASS_TEMP_TRIM_VBG_COLDSORT) : (SFLASH->EPASS_TEMP_TRIM_VBG_COLDSORT_5V))

 #define CY_SAR2_VBG_ROOM(t)  (((t) == CY_SAR2_VDDA_2_7V_TO_4_5V) ? \
 (SFLASH->EPASS_TEMP_TRIM_VBG_ROOMSORT) : (SFLASH->EPASS_TEMP_TRIM_VBG_ROOMSORT_5V))

 #define CY_SAR2_VBG_HOT(t)  (((t) == CY_SAR2_VDDA_2_7V_TO_4_5V) ? \
 (SFLASH->EPASS_TEMP_TRIM_VBG_HOTCLASS) : (SFLASH->EPASS_TEMP_TRIM_VBG_HOTCLASS_5V))

typedef struct {
    double      hotValue;   /**< The PASS hot temperature reading */
    double      roomValue;  /**< The PASS  room temperature reading */
    double      coldValue;  /**< The PASS  cold temperature reading */
} cy_stc_sar2_temp_sflash_data_t;


/*******************************************************************************
* Function Name: Cy_SAR2_Init
****************************************************************************//**
*
* Initializes the SAR2 block.
*
* \param base
* The pointer to the SAR ADC block instance.
*
* \param config
* The pointer to the configuration structure \ref cy_stc_sar2_config_t.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_Init(PASS_SAR_Type * base, const cy_stc_sar2_config_t * config)
{
    cy_en_sar2_status_t ret = CY_SAR2_SUCCESS;

    if ((NULL != config) && (NULL != base))
    {
        base->PRECOND_CTL = _VAL2FLD(PASS_SAR_PRECOND_CTL_PRECOND_TIME, config->preconditionTime);

        base->CTL = (_VAL2FLD(PASS_SAR_CTL_PWRUP_TIME, config->powerupTime) |
                    _BOOL2FLD(PASS_SAR_CTL_IDLE_PWRDWN, config->enableIdlePowerDown) |
                    _BOOL2FLD(PASS_SAR_CTL_MSB_STRETCH, config->msbStretchMode) |
                    _BOOL2FLD(PASS_SAR_CTL_HALF_LSB, config->enableHalfLsbConv) |
                    _BOOL2FLD(PASS_SAR_CTL_SARMUX_EN, config->sarMuxEnable) |
                    _BOOL2FLD(PASS_SAR_CTL_ADC_EN, config->adcEnable) |
                    _BOOL2FLD(PASS_SAR_CTL_ENABLED, config->sarIpEnable));

        for (uint8_t chan = 0u; chan < CY_SAR2_CHAN_NUM(base); chan++)
        {
            const cy_stc_sar2_channel_config_t * locChanCfg = config->channelConfig[chan];

            if (NULL != locChanCfg)
            {
                (void) Cy_SAR2_Channel_Init(base, chan, locChanCfg);
            }
        }
    }
    else
    {
        ret = CY_SAR2_BAD_PARAM;
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_Init
****************************************************************************//**
*
* Initializes an SAR channel.
*
* \param base
* The pointer to the SAR instance.
*
* \param channel
* The channel number.
*
* \param channelConfig
* The pointer to the configuration structure \ref cy_stc_sar2_channel_config_t.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_Channel_Init(PASS_SAR_Type * base, uint32_t channel,
                                                                     const cy_stc_sar2_channel_config_t * channelConfig)
{
    cy_en_sar2_status_t ret = CY_SAR2_SUCCESS;

    CY_ASSERT_L1(NULL != channelConfig);
    CY_ASSERT_L1(CY_SAR2_CHAN_NUM_VALID(base, channel));

    if (CY_SAR2_CHAN_NUM_VALID(base, channel))
    {
        /* First, disable the channel */
        Cy_SAR2_Channel_Disable(base, channel);

        /* Clear the whole interrupt flags */
        Cy_SAR2_Channel_ClearInterrupt(base, channel, CY_SAR2_INTR);

        SAR2_CH_TR_CTL(base, channel) =
                        (_VAL2FLD(PASS_SAR_CH_TR_CTL_SEL, channelConfig->triggerSelection) |
                        _VAL2FLD(PASS_SAR_CH_TR_CTL_PRIO, channelConfig->channelPriority) |
                        _VAL2FLD(PASS_SAR_CH_TR_CTL_PREEMPT_TYPE, channelConfig->preenptionType) |
                        _BOOL2FLD(PASS_SAR_CH_TR_CTL_GROUP_END, channelConfig->isGroupEnd) |
                        _BOOL2FLD(PASS_SAR_CH_TR_CTL_DONE_LEVEL, channelConfig->doneLevel));

        SAR2_CH_SAMPLE_CTL(base, channel) =
                            (_VAL2FLD(PASS_SAR_CH_SAMPLE_CTL_PIN_ADDR, channelConfig->pinAddress) |
                            _VAL2FLD(PASS_SAR_CH_SAMPLE_CTL_PORT_ADDR, channelConfig->portAddress) |
                            _VAL2FLD(PASS_SAR_CH_SAMPLE_CTL_EXT_MUX_SEL, channelConfig->extMuxSelect) |
                            _BOOL2FLD(PASS_SAR_CH_SAMPLE_CTL_EXT_MUX_EN, channelConfig->extMuxEnable) |
                            _VAL2FLD(PASS_SAR_CH_SAMPLE_CTL_PRECOND_MODE, channelConfig->preconditionMode) |
                            _VAL2FLD(PASS_SAR_CH_SAMPLE_CTL_OVERLAP_DIAG, channelConfig->overlapDiagMode) |
                            _VAL2FLD(PASS_SAR_CH_SAMPLE_CTL_SAMPLE_TIME, channelConfig->sampleTime) |
                            _VAL2FLD(PASS_SAR_CH_SAMPLE_CTL_ALT_CAL, channelConfig->calibrationValueSelect));

        SAR2_CH_POST_CTL(base, channel) =
                            (_VAL2FLD(PASS_SAR_CH_POST_CTL_POST_PROC, channelConfig->postProcessingMode) |
                            _VAL2FLD(PASS_SAR_CH_POST_CTL_LEFT_ALIGN, channelConfig->resultAlignment) |
                            _VAL2FLD(PASS_SAR_CH_POST_CTL_SIGN_EXT, channelConfig->signExtention) |
                            _VAL2FLD(PASS_SAR_CH_POST_CTL_RANGE_MODE, channelConfig->rangeDetectionMode));

        if((channelConfig->postProcessingMode == CY_SAR2_POST_PROCESSING_MODE_AVG) ||
            (channelConfig->postProcessingMode == CY_SAR2_POST_PROCESSING_MODE_AVG_RANGE))
        {
            SAR2_CH_POST_CTL(base, channel) |=
                            (_VAL2FLD(PASS_SAR_CH_POST_CTL_AVG_CNT, (channelConfig->averageCount - 1UL)) |
                            _VAL2FLD(PASS_SAR_CH_POST_CTL_SHIFT_R, channelConfig->rightShift));
        }
        else if (channelConfig->postProcessingMode == CY_SAR2_POST_PROCESSING_MODE_RANGE_PULSE)
        {
            SAR2_CH_POST_CTL(base, channel) |=
                            (_VAL2FLD(PASS_SAR_CH_POST_CTL_AVG_CNT, channelConfig->positiveReload) |
                            _VAL2FLD(PASS_SAR_CH_POST_CTL_SHIFT_R, channelConfig->negativeReload));
        }
        else if (channelConfig->postProcessingMode == CY_SAR2_POST_PROCESSING_MODE_NONE)
        {
            SAR2_CH_POST_CTL(base, channel) |=
                            (_VAL2FLD(PASS_SAR_CH_POST_CTL_SHIFT_R, channelConfig->rightShift));
        }
        else
        {
            /* Do not configure post processing options */
        }

        SAR2_CH_RANGE_CTL(base, channel) =
                            (_VAL2FLD(PASS_SAR_CH_RANGE_CTL_RANGE_LO, channelConfig->rangeDetectionLoThreshold) |
                            _VAL2FLD(PASS_SAR_CH_RANGE_CTL_RANGE_HI, channelConfig->rangeDetectionHiThreshold));

        if (channelConfig->channelHwEnable)
        {
            Cy_SAR2_Channel_Enable(base, channel);
        }

        Cy_SAR2_Channel_SetInterruptMask(base, channel, channelConfig->interruptMask);
    }
    else
    {
        ret = CY_SAR2_BAD_PARAM;
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_DeInit
****************************************************************************//**
*
* Stops and de-initializes the SAR channel register.
*
* \param base
* The pointer to the SAR instance.
*
* \param channel
* The channel number.
*
*******************************************************************************/
void Cy_SAR2_Channel_DeInit(PASS_SAR_Type * base, uint32_t channel)
{
    CY_ASSERT_L1(CY_SAR2_CHAN_NUM_VALID(base, channel));

    SAR2_CH_TR_CTL(base, channel) = 0x800UL; /* TR_CTL default value */
    Cy_SAR2_Channel_Disable(base, channel);

    /* Clear interrupt mask */
    Cy_SAR2_Channel_SetInterruptMask(base, channel, 0UL);
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_GetResult
****************************************************************************//**
*
* Returns the conversion result and status.
*
* \param base
* The pointer to an SAR instance.
*
* \param channel
* The channel number.
*
* \param status
* The pointer that will return measurement status bits ORed. The pointer can be
* NULL, then, s status is not returned.
*
* \return Conversion result.
*
*******************************************************************************/
uint16_t Cy_SAR2_Channel_GetResult(PASS_SAR_Type * base, uint32_t channel, uint32_t * status)
{
    CY_ASSERT_L1(CY_SAR2_CHAN_NUM_VALID(base, channel));

    uint32_t value = base->CH[channel].RESULT;

    if (NULL != status)
    {
        *status = value & (PASS_SAR_CH_RESULT_ABOVE_HI_MIR_Msk |
                          PASS_SAR_CH_RESULT_RANGE_INTR_MIR_Msk |
                          PASS_SAR_CH_RESULT_PULSE_INTR_MIR_Msk |
                          PASS_SAR_CH_RESULT_VALID_MIR_Msk);
    }

    return (uint16_t)_FLD2VAL(PASS_SAR_CH_RESULT_RESULT, value);
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_GetWorkingData
****************************************************************************//**
*
* Returns the working data and status.
*
* \param base
* The pointer to the SAR instance.
*
* \param channel
* The channel number.
*
* \param status
* The pointer that will return measurement status bits ORed. The pointer can be
* NULL, then, a status is not returned.
*
* \return Conversion result.
*
*******************************************************************************/
uint16_t Cy_SAR2_Channel_GetWorkingData(PASS_SAR_Type * base, uint32_t channel, uint32_t * status)
{
    CY_ASSERT_L1(CY_SAR2_CHAN_NUM_VALID(base, channel));

    uint32_t value = base->CH[channel].WORK;

    if (NULL != status)
    {
        *status = value & (PASS_SAR_CH_RESULT_ABOVE_HI_MIR_Msk |
                          PASS_SAR_CH_RESULT_RANGE_INTR_MIR_Msk |
                          PASS_SAR_CH_RESULT_PULSE_INTR_MIR_Msk |
                          PASS_SAR_CH_RESULT_VALID_MIR_Msk);
    }

    return (uint16_t)_FLD2VAL(PASS_SAR_CH_RESULT_RESULT, value);
}

/*******************************************************************************
* Function Name: Cy_SAR2_Diag_Init
****************************************************************************//**
*
* Initializes the diagnosis function.
*
* \param base
* The pointer to the SAR instance.
*
* \param diagConfig
* The pointer to the configuration structure \ref cy_stc_sar2_diag_config_t.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_Diag_Init(PASS_SAR_Type * base, const cy_stc_sar2_diag_config_t * diagConfig)
{
    cy_en_sar2_status_t ret = CY_SAR2_SUCCESS;

    if (NULL != diagConfig)
    {
        base->DIAG_CTL = _CLR_SET_FLD32U(base->DIAG_CTL, PASS_SAR_DIAG_CTL_DIAG_SEL, diagConfig->referenceSelect);
    }
    else
    {
        ret = CY_SAR2_BAD_PARAM;
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_SetDigitalCalibrationValue
****************************************************************************//**
*
* Configure SAR ADC digital calibration value.
*
* \param base
* The pointer to the SAR instance.
*
* \param digCalibConfig
* The pointer to the configuration structure
* \ref cy_stc_sar2_digital_calibration_config_t.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_SetDigitalCalibrationValue(PASS_SAR_Type * base,
                                                      const cy_stc_sar2_digital_calibration_config_t * digCalibConfig)
{
    cy_en_sar2_status_t ret = CY_SAR2_BAD_PARAM;

    if (NULL != digCalibConfig)
    {
        base->DIG_CAL = (_VAL2FLD(PASS_SAR_DIG_CAL_DOFFSET, digCalibConfig->offset) |
                         _VAL2FLD(PASS_SAR_DIG_CAL_DGAIN, digCalibConfig->gain));
        ret = CY_SAR2_SUCCESS;
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_GetDigitalCalibrationValue
****************************************************************************//**
*
* Gets the SAR ADC digital calibration value.
*
* \param base
* The pointer to the SAR instance.
*
* \param digCalibConfig
* The pointer to the output configuration structure
* \ref cy_stc_sar2_digital_calibration_config_t.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_GetDigitalCalibrationValue(PASS_SAR_Type * base,
                                                      cy_stc_sar2_digital_calibration_config_t * digCalibConfig)
{
    cy_en_sar2_status_t ret = CY_SAR2_SUCCESS;

    uint32_t digCal = base->DIG_CAL;
    if (NULL != digCalibConfig)
    {
        digCalibConfig->offset = (uint16_t) _FLD2VAL(PASS_SAR_DIG_CAL_DOFFSET, digCal);
        digCalibConfig->gain   = (int8_t) _FLD2VAL(PASS_SAR_DIG_CAL_DGAIN, digCal);
    }
    else
    {
        ret = CY_SAR2_BAD_PARAM;
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_SetAltDigitalCalibrationValue
****************************************************************************//**
*
* Configures an alternate SAR digital calibration value.
*
* \param base
* The pointer to the SAR instance.
*
* \param altDigCalibConfig
* The pointer to the configuration structure
* \ref cy_stc_sar2_digital_calibration_config_t.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_SetAltDigitalCalibrationValue(PASS_SAR_Type * base,
                                                     const cy_stc_sar2_digital_calibration_config_t * altDigCalibConfig)
{
    cy_en_sar2_status_t ret = CY_SAR2_SUCCESS;

    if (NULL != altDigCalibConfig)
    {
        base->DIG_CAL_ALT = (_VAL2FLD(PASS_SAR_DIG_CAL_ALT_DOFFSET, altDigCalibConfig->offset) |
                         _VAL2FLD(PASS_SAR_DIG_CAL_ALT_DGAIN, altDigCalibConfig->gain));
    }
    else
    {
        ret = CY_SAR2_BAD_PARAM;
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_GetAltDigitalCalibrationValue
****************************************************************************//**
*
* Gets an alternate SAR digital calibration value.
*
* \param base
* The pointer to the SAR instance.
*
* \param altDigCalibConfig
* The utput pointer to the configuration structure
* \ref cy_stc_sar2_digital_calibration_config_t.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_GetAltDigitalCalibrationValue(PASS_SAR_Type * base,
                                                         cy_stc_sar2_digital_calibration_config_t * altDigCalibConfig)
{
    cy_en_sar2_status_t ret = CY_SAR2_SUCCESS;

    uint32_t digCalAlt = base->DIG_CAL_ALT;
    if (NULL != altDigCalibConfig)
    {
        altDigCalibConfig->offset = (uint16_t) _FLD2VAL(PASS_SAR_DIG_CAL_ALT_DOFFSET, digCalAlt);
        altDigCalibConfig->gain   = (int8_t) _FLD2VAL(PASS_SAR_DIG_CAL_ALT_DGAIN, digCalAlt);
    }
    else
    {
        ret = CY_SAR2_BAD_PARAM;
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_SetAnalogCalibrationValue
****************************************************************************//**
*
* Configures an SAR analog calibration value.
*
* \param base
* The pointer to the SAR instance.
*
* \param analogCalibConfig
* The pointer to the configuration structure
* \ref cy_stc_sar2_analog_calibration_conifg_t.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_SetAnalogCalibrationValue(PASS_SAR_Type * base,
                                                     cy_stc_sar2_analog_calibration_conifg_t * analogCalibConfig)
{
    cy_en_sar2_status_t ret = CY_SAR2_SUCCESS;

    if (NULL != analogCalibConfig)
    {
        base->ANA_CAL = (_VAL2FLD(PASS_SAR_ANA_CAL_AOFFSET, analogCalibConfig->offset) |
                         _VAL2FLD(PASS_SAR_ANA_CAL_AGAIN, analogCalibConfig->gain));
    }
    else
    {
        ret = CY_SAR2_BAD_PARAM;
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_GetAnalogCalibrationValue
****************************************************************************//**
*
* Gets an SAR analog calibration value.
*
* \param base
* The pointer to the SAR instance.
*
* \param analogCalibConfig
* The utput pointer to the configuration structure
* \ref cy_stc_sar2_analog_calibration_conifg_t.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_GetAnalogCalibrationValue(PASS_SAR_Type * base,
                                                     cy_stc_sar2_analog_calibration_conifg_t * analogCalibConfig)
{
    cy_en_sar2_status_t ret = CY_SAR2_SUCCESS;

    uint32_t anaCal = base->ANA_CAL;
    if (NULL != analogCalibConfig)
    {
        analogCalibConfig->offset = (int8_t) _FLD2VAL(PASS_SAR_ANA_CAL_AOFFSET, anaCal);
        analogCalibConfig->gain   = (int8_t) _FLD2VAL(PASS_SAR_ANA_CAL_AGAIN, anaCal);
    }
    else
    {
        ret = CY_SAR2_BAD_PARAM;
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_SetAltAnalogCalibrationValue
****************************************************************************//**
*
* Configures an alternate SAR analog calibration value.
*
* \param base
* The pointer to the SAR instance.
*
* \param altAnalogCalibConfig
* The pointer to the configuration structure
* \ref cy_stc_sar2_analog_calibration_conifg_t.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_SetAltAnalogCalibrationValue(PASS_SAR_Type * base,
                                                        cy_stc_sar2_analog_calibration_conifg_t * altAnalogCalibConfig)
{
    cy_en_sar2_status_t ret = CY_SAR2_SUCCESS;

    if (NULL != altAnalogCalibConfig)
    {
        base->ANA_CAL_ALT = (_VAL2FLD(PASS_SAR_ANA_CAL_ALT_AOFFSET, altAnalogCalibConfig->offset) |
                             _VAL2FLD(PASS_SAR_ANA_CAL_ALT_AGAIN, altAnalogCalibConfig->gain));
    }
    else
    {
        ret = CY_SAR2_BAD_PARAM;
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_GetAltAnalogCalibrationValue
****************************************************************************//**
*
* Gets an alternate SAR analog calibration value.
*
* \param base
* The pointer to the SAR instance.
*
* \param altAnalogCalibConfig
* The utput pointer to the configuration structure
* \ref cy_stc_sar2_analog_calibration_conifg_t.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_GetAltAnalogCalibrationValue(PASS_SAR_Type * base,
                                                        cy_stc_sar2_analog_calibration_conifg_t * altAnalogCalibConfig)
{
    cy_en_sar2_status_t ret = CY_SAR2_SUCCESS;

    uint32_t altAnaCal = base->ANA_CAL_ALT;
    if (NULL != altAnalogCalibConfig)
    {
        altAnalogCalibConfig->offset = (int8_t) _FLD2VAL(PASS_SAR_ANA_CAL_AOFFSET, altAnaCal);
        altAnalogCalibConfig->gain   = (int8_t) _FLD2VAL(PASS_SAR_ANA_CAL_AGAIN, altAnaCal);
    }
    else
    {
        ret = CY_SAR2_BAD_PARAM;
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_SetDebugFreezeMode
****************************************************************************//**
*
* Configures the debug pause feature.
*
* \param base
* The pointer to the PASS instance.
*
* \param debConfig
* The utput pointer to the configuration structure
* \ref cy_stc_sar2_debug_freeze_config_t.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_SetDebugFreezeMode(PASS_EPASS_MMIO_Type * base,
                                              const cy_stc_sar2_debug_freeze_config_t * debConfig)
{
    cy_en_sar2_status_t ret = CY_SAR2_SUCCESS;

    uint32_t temp = 0UL;
    if (NULL != debConfig)
    {
        temp |= (debConfig->enableFreezeAdc0) ? 1UL : 0UL;
        temp |= (debConfig->enableFreezeAdc1) ? 2UL : 0UL;
        temp |= (debConfig->enableFreezeAdc2) ? 4UL : 0UL;
        temp |= (debConfig->enableFreezeAdc3) ? 8UL : 0UL;
        base->PASS_CTL = _CLR_SET_FLD32U(base->PASS_CTL, PASS_EPASS_MMIO_PASS_CTL_DBG_FREEZE_EN, temp);
    }
    else
    {
        ret = CY_SAR2_BAD_PARAM;
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_SetGenericTriggerInput
****************************************************************************//**
*
* Configures the generic trigger input selection.
*
* \param base
* The pointer to the PASS instance.
*
* \param numOfAdc
* The ADC channel number.
*
* \param triggerInputNumber
* The generic input trigger number to be set up.
*
* \param genericTriggerValue
* The generic input trigger to be used as a corresponding trigger input #.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_SetGenericTriggerInput(PASS_EPASS_MMIO_Type * base, uint8_t numOfAdc,
                                                  uint8_t triggerInputNumber, uint8_t genericTriggerValue)
{
    cy_en_sar2_status_t ret = CY_SAR2_SUCCESS;

    if ((numOfAdc > PASS_SAR_ADC_NR) ||
        (triggerInputNumber >= CY_SAR2_TR_IN_NUM) ||
        (genericTriggerValue >= CY_SAR2_GEN_TR_IN_NUM))
    {
        ret = CY_SAR2_BAD_PARAM;
    }
    else
    {
        switch(triggerInputNumber)
        {
        case 0U:
            base->SAR_TR_IN_SEL[numOfAdc] = _CLR_SET_FLD32U(base->SAR_TR_IN_SEL[numOfAdc],
                  PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN0_SEL, genericTriggerValue);
            break;
        case 1U:
            base->SAR_TR_IN_SEL[numOfAdc] = _CLR_SET_FLD32U(base->SAR_TR_IN_SEL[numOfAdc],
                  PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN1_SEL, genericTriggerValue);
            break;
        case 2U:
            base->SAR_TR_IN_SEL[numOfAdc] = _CLR_SET_FLD32U(base->SAR_TR_IN_SEL[numOfAdc],
                  PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN2_SEL, genericTriggerValue);
            break;
        case 3U:
            base->SAR_TR_IN_SEL[numOfAdc] = _CLR_SET_FLD32U(base->SAR_TR_IN_SEL[numOfAdc],
                  PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN3_SEL, genericTriggerValue);
            break;
        case 4U:
            base->SAR_TR_IN_SEL[numOfAdc] = _CLR_SET_FLD32U(base->SAR_TR_IN_SEL[numOfAdc],
                  PASS_EPASS_MMIO_SAR_TR_IN_SEL_IN4_SEL, genericTriggerValue);
            break;
        default:
            /* Do nothing. */
            break;
        }
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_SetGenericTriggerOutput
****************************************************************************//**
*
* Configures the generic output trigger selection.
*
* \param base
* The pointer to the PASS instance.
*
* \param numOfAdc
* The ADC channel number
*
* \param triggerOutputNumber
* The generic input trigger number to be set up.
*
* \param genericTriggerValue
* The generic input trigger to be used as a corresponding trigger input number.
*
* \return
* \ref cy_en_sar2_status_t
*
*******************************************************************************/
cy_en_sar2_status_t Cy_SAR2_SetGenericTriggerOutput(PASS_EPASS_MMIO_Type * base, uint8_t numOfAdc,
                                                  uint8_t triggerOutputNumber, uint8_t genericTriggerValue)
{
    cy_en_sar2_status_t ret = CY_SAR2_SUCCESS;

    if ((numOfAdc > PASS_SAR_ADC_NR) ||
        (triggerOutputNumber >= CY_SAR2_TR_OUT_NUM) ||
        (genericTriggerValue >= CY_SAR2_GEN_TR_OUT_NUM))
    {
        ret = CY_SAR2_BAD_PARAM;
    }
    else
    {
        switch(triggerOutputNumber)
        {
        case 0U:
            base->SAR_TR_OUT_SEL[numOfAdc] = _CLR_SET_FLD32U(base->SAR_TR_OUT_SEL[numOfAdc],
                  PASS_EPASS_MMIO_SAR_TR_OUT_SEL_OUT0_SEL, genericTriggerValue);
            break;
        case 1U:
            base->SAR_TR_OUT_SEL[numOfAdc] = _CLR_SET_FLD32U(base->SAR_TR_OUT_SEL[numOfAdc],
                  PASS_EPASS_MMIO_SAR_TR_OUT_SEL_OUT1_SEL, genericTriggerValue);
            break;
        default:
            /* Do nothing. */
            break;
        }
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_SAR2_CalculateDieTemperature
****************************************************************************//**
*
* Calculates the internal temperature from ADC core using Vtemp.
* The API is implemented to calculate the temperature from the 2nd order
* equation of sort data with corrected class data. The API will convert sort data
* into [3][3] matrix and class data into [2][2] matrix.
*
* \param VDDARange
* VDDA voltage range, \ref cy_en_sar2_vdda_range_t.
*
* \param adcVtempRawValue
* The ADC counts the raw value of the temperature diode.
*
* \param adcVbgRawValue
* The ADC counts raw value of the Vbg voltage.
*
* \return
* Temperature Value
*
*******************************************************************************/
double Cy_SAR2_CalculateDieTemperature(cy_en_sar2_vdda_range_t VDDARange, uint16_t adcVtempRawValue,
                                                                                                uint16_t adcVbgRawValue)
{
    double tempInDegreeC = 0.0;
    cy_stc_sar2_temp_sflash_data_t adcTempValues;

    /* Note: Temperature data read from sFLASH is multiple of 10. */
    adcTempValues.coldValue = (((double)(-((float)(SFLASH->EPASS_TEMP_TRIM_TEMP_COLDSORT)))) / 10.0);
    adcTempValues.roomValue = ((double)(SFLASH->EPASS_TEMP_TRIM_TEMP_ROOMSORT) / 10.0);
    adcTempValues.hotValue = ((double)(SFLASH->EPASS_TEMP_TRIM_TEMP_HOTCLASS) / 10.0);

    double determinant = 0.0;
    double coefficientMatrixForSort[3][3] = {{0.0},{0.0},{0.0}};

    double sortTempMatrixA[CY_SAR2_TEMP_MATRIX_SIZE][CY_SAR2_TEMP_MATRIX_SIZE];
    double sortTempValueMatrixB[CY_SAR2_TEMP_MATRIX_SIZE][1];
    double sortTempCoefficeintsX[CY_SAR2_TEMP_MATRIX_SIZE] = {0.0};

    double coeffA;
    double coeffB;
    double coeffC;
    double bSqrMin4ac = 0.0;
    double tempRefValue = 0.0;
    double tempScaleValue = 0.0;
    double correctionFactor = 0.0;
    double tempRootPos;
    double tempRootNeg = 0.0;
    double tempRangeOffset = (double) 10; /* relate to +/- 10 degC */
    bool recalculate;

    /***************************************************************************
     * Updates the class and sorts the matrix from the sFLASH values
     **************************************************************************/

    /* Update the sort temperature value matrix A */
    sortTempMatrixA[0][0] = 1.0;
    sortTempMatrixA[0][1] = adcTempValues.coldValue;
    sortTempMatrixA[0][2] = pow(adcTempValues.coldValue, 2.0);
    sortTempMatrixA[1][0] = 1.0;
    sortTempMatrixA[1][1] = adcTempValues.roomValue;
    sortTempMatrixA[1][2] = pow(adcTempValues.roomValue, 2.0);
    sortTempMatrixA[2][0] = 1.0;
    sortTempMatrixA[2][1] = adcTempValues.hotValue;
    sortTempMatrixA[2][2] = pow(adcTempValues.hotValue, 2.0);

    /* Update the sort temperature adc value matrix B */
    sortTempValueMatrixB[0][0] = (double)CY_SAR2_DIODE_COLD(VDDARange);
    sortTempValueMatrixB[1][0] = (double)CY_SAR2_DIODE_ROOM(VDDARange);
    sortTempValueMatrixB[2][0] = (double)CY_SAR2_DIODE_HOT(VDDARange);

    /***************************************************************************
     * Gets the 2nd order coefficient for the sort value matrix
     **************************************************************************/

    /* Get the determinant of sort temperature matrix A */
    for(uint8_t i = 0U; i < CY_SAR2_TEMP_MATRIX_SIZE; i++)
    {
        determinant = determinant + (sortTempMatrixA[0][i]*(sortTempMatrixA[1U][(i+1U)%3U]*sortTempMatrixA[2U][(i+2U)%3U] -
                                                            sortTempMatrixA[1U][(i+2U)%3U]*sortTempMatrixA[2U][(i+1U)%3U]));
    }

    /* Get the inverse of sort temperature matrix A */
    for(uint8_t i = 0U; i < CY_SAR2_TEMP_MATRIX_SIZE; i++)
    {
        for(uint8_t j = 0U; j < CY_SAR2_TEMP_MATRIX_SIZE; j++)
        {
            coefficientMatrixForSort[i][j] = ((sortTempMatrixA[(i+1U)%3U][(j+1U)%3U] * sortTempMatrixA[(i+2U)%3U][(j+2U)%3U]) -
                                    (sortTempMatrixA[(i+1U)%3U][(j+2U)%3U]*sortTempMatrixA[(i+2U)%3U][(j+1U)%3U]))/ determinant;
        }
    }
    for(uint8_t i = 0U; i < CY_SAR2_TEMP_MATRIX_SIZE; i++)
    {
        for(uint8_t j = 0U; j < CY_SAR2_TEMP_MATRIX_SIZE; j++)
        {
            sortTempMatrixA[i][j] = coefficientMatrixForSort[j][i];
        }
    }

    /* Calculate sort temperature coefficient matrix X = (invA)*B */
    for(uint8_t i = 0U; i < CY_SAR2_TEMP_MATRIX_SIZE; i++)
    {
        for(uint8_t j = 0U; j < CY_SAR2_TEMP_MATRIX_SIZE; j++)
        {
            sortTempCoefficeintsX[i] += (sortTempValueMatrixB[j][0]*sortTempMatrixA[i][j]);
        }
    }

    /***************************************************************************
     * Gets the temperature value from the 2nd order equation
     **************************************************************************/

    /* Rearrange the coefficients for the predicted temperature formula */
    coeffA = sortTempCoefficeintsX[2];
    coeffB = sortTempCoefficeintsX[1];
    coeffC = sortTempCoefficeintsX[0];

    /* -40degC -- SORT2, 27degC -- SORT3, 130degC -- CHI and by default reference value is SORT3 */
    tempRefValue = (double)(CY_SAR2_VBG_ROOM(VDDARange));

    do {
        recalculate = false;

        /* Calculate the correction factor (k) to remove the dependency of the ADC on the reference voltage */
        correctionFactor = (tempRefValue) / ((double)(adcVbgRawValue));

        /* Scale the data in raw with k */
        tempScaleValue = (correctionFactor) * ((double)(adcVtempRawValue));

        /* Calculate the predicted temperature */
        bSqrMin4ac = (double) ( pow(coeffB, 2.0)) - (((4.0)*(coeffA))*(coeffC - tempScaleValue));
        CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.3', 2, 'Intentional typecast of bSqrMin4ac to uint32_t ');
        tempRootNeg = ((-coeffB)-((double)sqrtf(bSqrMin4ac))) / ((2.0)*(coeffA));
        tempRootPos = ((-coeffB)+((double)sqrtf(bSqrMin4ac))) / ((2.0)*(coeffA));
        CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.3');
        /* Select the root that lies between the Hot and Cold temperature sort values [-40 degC, 150 degC] */
        if((tempRootPos < (adcTempValues.hotValue)) && (tempRootPos > (adcTempValues.coldValue)))
        {
            /* The temperature value is positive root of the curve */
            tempInDegreeC = tempRootPos;
        }
        else if((tempRootNeg < (adcTempValues.hotValue)) && (tempRootNeg > (adcTempValues.coldValue)))
        {
            /* The temperature value is the negative root of the curve */
            tempInDegreeC = tempRootNeg;
        }
        else
        {
            /* The Apt value is not found */
            tempInDegreeC = 0.0;
        }

        /* Check for the close proximity of calculated temperature with the reference temperature values */
        if (tempInDegreeC <= ((adcTempValues.coldValue) + tempRangeOffset))
        {
            /* Use the SORT2 value to scale the measured temperature */
            tempRefValue = (double)(CY_SAR2_VBG_COLD(VDDARange));
            recalculate = true;
        }
        else if (tempInDegreeC >= ((adcTempValues.hotValue) - tempRangeOffset))
        {
            /* Use the CHI value to scale the measured temperature */
            tempRefValue = (double)(CY_SAR2_VBG_HOT(VDDARange));
            recalculate = true;
        }
        else if ((tempInDegreeC <= ((adcTempValues.roomValue) + tempRangeOffset))
            && (tempInDegreeC >= ((adcTempValues.roomValue) - tempRangeOffset)))
        {
            /* Use the SORT3 value to scale the measured temperature */
            tempRefValue = (double)(CY_SAR2_VBG_ROOM(VDDARange));
        }
        else
        {
            /* Do nothing */
        }
    } while (recalculate == true);

    return tempInDegreeC;
}

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.8');

#endif /* CY_IP_MXS40EPASS_ESAR */
