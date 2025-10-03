/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include "r_dac.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* D/A Control Register Mask */
/** Driver ID (DAC in ASCII), used to identify Digital to Analog Converter (DAC) configuration  */
#define DAC_OPEN                                     (0x44414300)
#define DAC_DAADSCR_REG_DAADST_BIT_POS               (0x07U)
#define DAC_DAADUSR_REG_MASK                         BSP_FEATURE_DAC_AD_SYNC_UNIT_MASK
#define DAC_DADPR_REG_DPSEL_BIT_POS                  (0x07U)
#define DAC_DAAMPCR_AMP_CTRL_BITS                    (0x06U) /* 6th bit for channel 0; 7th bit for channel 1 */
#define DAC_DACR_DAOE_BITS                           (0x06U) /* 6th bit for channel 0; 7th bit for channel 1 */
#define DAC_DAASWCR_DAASW0_MASK                      (0x40)
#define DAC_DAASWCR_DAASW1_MASK                      (0x80)
#if 0x01U == BSP_FEATURE_DAC_AD_SYNC_UNIT_MASK
 #define DAC_ADC_UNIT                                (0)
#elif 0x02U == BSP_FEATURE_DAC_AD_SYNC_UNIT_MASK
 #define DAC_ADC_UNIT                                (1)
#endif

/* Conversion time with Output Amplifier. See hardware manual (see Table 60.44
 *'D/A conversion characteristics' of the RA6M3 manual R01UH0886EJ0100). */
#define DAC_CONVERSION_TIME_WITH_OUTPUT_AMPLIFIER    (0x04U) /* Unit: Microseconds. */

#define DAC_VREF_DISCHARGING_DELAY_US                (10)
#define DAC_INTERNAL_VREF_WAIT_TIME_US               (5)
#define DAC12_CHANNEL_COUNT                          (BSP_FEATURE_DAC12_CHANNELS_PER_UNIT * \
                                                      BSP_FEATURE_DAC12_UNIT_COUNT)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const dac_api_t g_dac_on_dac =
{
    .open  = R_DAC_Open,
    .write = R_DAC_Write,
    .start = R_DAC_Start,
    .stop  = R_DAC_Stop,
    .close = R_DAC_Close,
};

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup DAC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * Perform required initialization described in hardware manual.  Implements @ref dac_api_t::open.
 * Configures a single DAC channel, starts the channel, and provides a handle for use with the
 * DAC API Write and Close functions.  Must be called once prior to calling any other DAC API
 * functions.  After a channel is opened, Open should not be called again for the same channel
 * without calling Close first.
 *
 * @retval FSP_SUCCESS                     The channel was successfully opened.
 * @retval FSP_ERR_ASSERTION               Parameter check failure due to one or more reasons below:
 *                                         1. One or both of the following parameters may be NULL: p_api_ctrl or p_cfg
 *                                         2. data_format value in p_cfg is out of range.
 *                                         3. Extended configuration structure is set to NULL for
 *                                            MCU supporting charge pump.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT  Channel ID requested in p_cfg may not available on the devices.
 * @retval FSP_ERR_ALREADY_OPEN            The control structure is already opened.
 *
 **********************************************************************************************************************/
fsp_err_t R_DAC_Open (dac_ctrl_t * p_api_ctrl, dac_cfg_t const * const p_cfg)
{
    dac_instance_ctrl_t * p_ctrl = (dac_instance_ctrl_t *) p_api_ctrl;

    /* Validate the input parameter. */
#if DAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_cfg->channel < (uint8_t) DAC12_CHANNEL_COUNT, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    FSP_ERROR_RETURN(false == p_ctrl->channel_opened, FSP_ERR_ALREADY_OPEN);
 #if (BSP_FEATURE_DAC_HAS_CHARGEPUMP || BSP_FEATURE_DAC_HAS_DAVREFCR)
    FSP_ASSERT(NULL != p_cfg->p_extend)
 #endif
#endif

#if (DAC12_CHANNEL_COUNT > 2U)
    uint8_t unit = p_cfg->channel / BSP_FEATURE_DAC12_CHANNELS_PER_UNIT;
    p_ctrl->p_reg = (R_DAC_Type *) ((uint32_t) R_DAC0 + (unit * ((uint32_t) R_DAC1 - (uint32_t) R_DAC0)));
#else
    p_ctrl->p_reg = R_DAC;
#endif

    p_ctrl->channel_index = p_cfg->channel % BSP_FEATURE_DAC12_CHANNELS_PER_UNIT;

    /* Power on the DAC device. */
    uint8_t dac_unit = p_cfg->channel / BSP_FEATURE_DAC12_CHANNELS_PER_UNIT;
    R_BSP_MODULE_START(FSP_IP_DAC, dac_unit);

    /* Added this to a separate block to avoid redeclaration of
     * critical section variable under module start macro. */
    {
        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;

        /* Stop the channel. */
        (0U == p_ctrl->channel_index) ? (p_ctrl->p_reg->DACR_b.DAOE0 = 0U) : (p_ctrl->p_reg->DACR_b.DAOE1 = 0U);

        FSP_CRITICAL_SECTION_EXIT;
    }

    dac_extended_cfg_t * p_extend = (dac_extended_cfg_t *) p_cfg->p_extend;

    /* Configure data format: left or right justified. */
    p_ctrl->p_reg->DADPR = (uint8_t) ((uint8_t) p_extend->data_format << (uint8_t) DAC_DADPR_REG_DPSEL_BIT_POS);

#if BSP_FEATURE_DAC_HAS_DA_AD_SYNCHRONIZE
 #if BSP_FEATURE_DAC_AD_SYNC_UNIT_MASK

    /* DA/AD Synchronization. Described in hardware manual (see Section 48.2.7
     * 'D/A A/D Synchronous Unit Select Register (DAADUSR)' and Section 48.2.4
     * 'D/A A/D Synchronous Start Control Register (DAADSCR)'of the RA6M3 manual R01UH0886EJ0100). */

    /* D/A A/D Synchronous Unit Select Register: Select ADC Unit for synchronization with this DAC channel */
    if ((0U == p_ctrl->p_reg->DAADSCR) && (p_cfg->ad_da_synchronized))
    {
        /* For correctly writing to this register:
         * 1. ADC module stop bit must be cleared.
         * 2. DAADSCR.DAADST must be cleared.
         *
         * If ADC module is started, this will have no effect.
         *
         * If ADC module is not started yet, this will start it for enabling write to DAADUSR.
         * Since the ad_da_synchronized is set to true in the configuration structure
         * the ADC module is believed to be started at a later point in the application.
         */
        R_BSP_MODULE_START(FSP_IP_ADC, (uint16_t) DAC_ADC_UNIT);

        p_ctrl->p_reg->DAADUSR = (uint8_t) BSP_FEATURE_DAC_AD_SYNC_UNIT_MASK;

        /* Configure D/A-A/D Synchronous Start Control Register(DAADSCR). */
        p_ctrl->p_reg->DAADSCR = (uint8_t) (1U << (uint8_t) DAC_DAADSCR_REG_DAADST_BIT_POS);
    }
 #else

    /* Configure D/A-A/D Synchronous Start Control Register(DAADSCR). */
    p_ctrl->p_reg->DAADSCR = (uint8_t) (p_cfg->ad_da_synchronized << (uint8_t) DAC_DAADSCR_REG_DAADST_BIT_POS);
 #endif
#endif

#if BSP_FEATURE_DAC_HAS_OUTPUT_AMPLIFIER
    p_ctrl->output_amplifier_enabled = p_extend->output_amplifier_enabled;
#endif

#if BSP_FEATURE_DAC_HAS_DAASWCR_INTERNAL_OUTPUT_CONTROL
    p_ctrl->internal_output_enabled = p_extend->internal_output_enabled;
#endif

    /* Set the reference voltage. */
#if BSP_FEATURE_DAC_HAS_DAVREFCR

    /* D/A Reference Voltage Select. Described in hardware manual (see Section 36.2.5
     * 'D/A VREF Control Register (DAVREFCR) and Section 36.3.2
     * 'Notes on Using the Internal Reference Voltage as the Reference Voltage of the RA4M1 manual R01UH0887EJ0110). */

    /* Clear REF bits before changing the value of these bits. */
    p_ctrl->p_reg->DAVREFCR = 0x00;
    if (DAC_VREF_IVREF_AVSS0 == p_extend->ref_volt_sel)
    {
        p_ctrl->p_reg->DADR[0] = 0x00U;

        /* Discharge for 10 us. */
        R_BSP_SoftwareDelay(DAC_VREF_DISCHARGING_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
        p_ctrl->p_reg->DAVREFCR     = (uint8_t) p_extend->ref_volt_sel;
        p_ctrl->p_reg->DACR_b.DAOE0 = 1U;

        /* Wait 5 us, the stabilization wait time of the internal reference voltage. */
        R_BSP_SoftwareDelay(DAC_INTERNAL_VREF_WAIT_TIME_US, BSP_DELAY_UNITS_MICROSECONDS);
    }
    else
    {
        p_ctrl->p_reg->DAVREFCR = (uint8_t) p_extend->ref_volt_sel;
    }
    FSP_REGISTER_READ(p_ctrl->p_reg->DAVREFCR)
#endif

#if (1U == BSP_FEATURE_DAC_HAS_CHARGEPUMP)
    p_ctrl->p_reg->DAPC = (uint8_t) p_extend->enable_charge_pump;
#endif

    /* Initialize the channel state information. */
    p_ctrl->channel        = p_cfg->channel;
    p_ctrl->channel_opened = DAC_OPEN;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Write data to the D/A converter and enable the output if it has not been enabled.
 *
 * @retval   FSP_SUCCESS           Data is successfully written to the D/A Converter.
 * @retval   FSP_ERR_ASSERTION     p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN      Channel associated with p_ctrl has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_DAC_Write (dac_ctrl_t * p_api_ctrl, uint16_t value)
{
    dac_instance_ctrl_t * p_ctrl = (dac_instance_ctrl_t *) p_api_ctrl;

#if DAC_CFG_PARAM_CHECKING_ENABLE

    /* Validate the handle parameter */
    FSP_ASSERT(NULL != p_ctrl);

    /* Validate that the channel is opened. */
    FSP_ERROR_RETURN(p_ctrl->channel_opened, FSP_ERR_NOT_OPEN);
#endif

    /* Write the value to D/A converter. */
    p_ctrl->p_reg->DADR[p_ctrl->channel_index] = value;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Start the D/A conversion output if it has not been started.
 *
 * @retval   FSP_SUCCESS           The channel is started successfully.
 * @retval   FSP_ERR_ASSERTION     p_api_ctrl is NULL.
 * @retval   FSP_ERR_IN_USE        Attempt to re-start a channel.
 * @retval   FSP_ERR_NOT_OPEN      Channel associated with p_ctrl has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_DAC_Start (dac_ctrl_t * p_api_ctrl)
{
    dac_instance_ctrl_t * p_ctrl = (dac_instance_ctrl_t *) p_api_ctrl;

#if DAC_CFG_PARAM_CHECKING_ENABLE

    /* Validate the handle parameter */
    FSP_ASSERT(NULL != p_ctrl);

    /* Validate that the channel is opened. */
    FSP_ERROR_RETURN(p_ctrl->channel_opened, FSP_ERR_NOT_OPEN);

    /* Check if the channel is not already started */
    bool channel_started = false;

    channel_started =
        ((0U == p_ctrl->channel_index) ? ((bool) p_ctrl->p_reg->DACR_b.DAOE0) : (bool) (p_ctrl->p_reg->DACR_b.DAOE1));

    FSP_ERROR_RETURN(!channel_started, FSP_ERR_IN_USE);
#endif

#if BSP_FEATURE_DAC_HAS_OUTPUT_AMPLIFIER

    /* Initialize output amplifier. Described in hardware manual (see Section 48.6.5
     * 'Initialization Procedure with the Output Amplifier' of the RA6M3 manual R01UH0878EJ0100). */
    if (p_ctrl->output_amplifier_enabled)
    {
        /* Store value intended to be amplified during DAC output */
        uint16_t value = p_ctrl->p_reg->DADR[p_ctrl->channel_index];

        /* Clear the D/A Data Register for the requested channel. */
        p_ctrl->p_reg->DADR[p_ctrl->channel_index] = 0x00U;

        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;

        if (0U == p_ctrl->channel_index)
        {
            p_ctrl->p_reg->DACR_b.DAOE0     = 0U; /* Disable channel 0 */
            p_ctrl->p_reg->DAASWCR_b.DAASW0 = 1U; /* Enable D/A Amplifier Stabilization Wait for channel 0 */
            p_ctrl->p_reg->DAAMPCR_b.DAAMP0 = 1U; /* Enable amplifier control for channel 0 */
            p_ctrl->p_reg->DACR_b.DAOE0     = 1U; /* Enable channel 0 to start D/A conversion of 0x00 */
        }
        else
        {
            p_ctrl->p_reg->DACR_b.DAOE1     = 0U; /* Disable channel 1 */
            p_ctrl->p_reg->DAASWCR_b.DAASW1 = 1U; /* Enable D/A Amplifier Stabilization Wait for channel 1 */
            p_ctrl->p_reg->DAAMPCR_b.DAAMP1 = 1U; /* Enable amplifier control for channel 1 */
            p_ctrl->p_reg->DACR_b.DAOE1     = 1U; /* Enable channel 1 to start D/A conversion of 0x00 */
        }

        FSP_CRITICAL_SECTION_EXIT;

        /* The System clock will be running at this point. It is safe to use this function. */
        R_BSP_SoftwareDelay((uint32_t) DAC_CONVERSION_TIME_WITH_OUTPUT_AMPLIFIER, BSP_DELAY_UNITS_MICROSECONDS);

        FSP_CRITICAL_SECTION_ENTER;

        /* Disable D/A Amplifier Stabilization Wait for channel 0 or 1 */
        (0U ==
         p_ctrl->channel_index) ? (p_ctrl->p_reg->DAASWCR_b.DAASW0 = 0U) : (p_ctrl->p_reg->DAASWCR_b.DAASW1 = 0U);

        FSP_CRITICAL_SECTION_EXIT;

        /* Revert value intended to be amplified during DAC output. */
        p_ctrl->p_reg->DADR[p_ctrl->channel_index] = value;
    }
    else
#endif
    {
        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;

        if (0U == p_ctrl->channel_index)
        {
#if BSP_FEATURE_DAC_HAS_DAASWCR_INTERNAL_OUTPUT_CONTROL
            p_ctrl->p_reg->DACR_b.DAOE0     = 0U;                              /* Disable channel 0 */
            p_ctrl->p_reg->DAASWCR_b.DAASW0 = p_ctrl->internal_output_enabled; /* Disable channel 0 internal output. */
#endif

            /* Enable channel 0 to start D/A conversion of 0x00 */
            p_ctrl->p_reg->DACR_b.DAOE0 = 1U;
        }
        else
        {
#if BSP_FEATURE_DAC_HAS_DAASWCR_INTERNAL_OUTPUT_CONTROL
            p_ctrl->p_reg->DACR_b.DAOE1     = 0U;                              /* Disable channel 1 */
            p_ctrl->p_reg->DAASWCR_b.DAASW1 = p_ctrl->internal_output_enabled; /* Disable channel 1 internal output. */
#endif

            /* Enable channel 1 to start D/A conversion of 0x00 */
            p_ctrl->p_reg->DACR_b.DAOE1 = 1U;
        }

        FSP_CRITICAL_SECTION_EXIT;
    }

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Stop the D/A conversion and disable the output signal.
 *
 * @retval  FSP_SUCCESS           The control is successfully stopped.
 * @retval  FSP_ERR_ASSERTION     p_api_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN      Channel associated with p_ctrl has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_DAC_Stop (dac_ctrl_t * p_api_ctrl)
{
    dac_instance_ctrl_t * p_ctrl = (dac_instance_ctrl_t *) p_api_ctrl;

#if DAC_CFG_PARAM_CHECKING_ENABLE

    /* Validate the handle parameter */
    FSP_ASSERT(NULL != p_ctrl);

    /* Validate that the channel is opened. */
    FSP_ERROR_RETURN(p_ctrl->channel_opened, FSP_ERR_NOT_OPEN);
#endif

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Stop the channel */
    (0U == p_ctrl->channel_index) ? (p_ctrl->p_reg->DACR_b.DAOE0 = 0U) : (p_ctrl->p_reg->DACR_b.DAOE1 = 0U);

    FSP_CRITICAL_SECTION_EXIT;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Stop the D/A conversion, stop output, and close the DAC channel.
 *
 * @retval   FSP_SUCCESS           The channel is successfully closed.
 * @retval   FSP_ERR_ASSERTION     p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN      Channel associated with p_ctrl has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_DAC_Close (dac_ctrl_t * p_api_ctrl)
{
    dac_instance_ctrl_t * p_ctrl = (dac_instance_ctrl_t *) p_api_ctrl;

#if DAC_CFG_PARAM_CHECKING_ENABLE

    /* Validate the handle parameter */
    FSP_ASSERT(NULL != p_ctrl);

    /* Validate that the channel is opened. */
    FSP_ERROR_RETURN(p_ctrl->channel_opened, FSP_ERR_NOT_OPEN);
#endif

    /* Module Stop is not needed here as this module does not have channel specific Start/Stop control.
     * For more than 1 channels used (on selected MCUs), a module stop will disable both the channels. */

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Stop the channel, clear the amplifier stabilization wait bit and
     * clear the output amplifier control register for the associated channel. */
    if (0U == p_ctrl->channel_index)
    {
        p_ctrl->p_reg->DACR_b.DAOE0     = 0U; /* Disable channel 0 */
        p_ctrl->p_reg->DAAMPCR_b.DAAMP0 = 0U; /* Disable amplifier control for channel 0 */
    }
    else
    {
        p_ctrl->p_reg->DACR_b.DAOE1     = 0U; /* Disable channel 1 */
        p_ctrl->p_reg->DAAMPCR_b.DAAMP1 = 0U; /* Disable amplifier control for channel 1 */
    }

    FSP_CRITICAL_SECTION_EXIT;

    /* Update the channel state information. */
    p_ctrl->channel_opened = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup DAC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
