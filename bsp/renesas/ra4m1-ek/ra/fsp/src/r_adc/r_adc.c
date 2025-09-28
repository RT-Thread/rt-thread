/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include "bsp_api.h"

/* Configuration for this package. */
#include "r_adc_cfg.h"

/* Private header file for this package. */
#include "r_adc.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define ADC_PRV_USEC_PER_SEC                        (1000000U)
#define ADC_PRV_MIN_ADCLK_HZ                        (1000000U)
#define ADC_MAX_CALIBRATION_CLOCKS_MILLISECS        (780U)

#define ADC_PRV_HZ_PER_KHZ                          (1000U)

#define ADC_SHIFT_LEFT_ALIGNED_32_BIT               (16U)

#define ADC_OPEN                                    (0x52414443U)

#define ADC_ADADC_AVEE_BIT                          (0x80U)

/* Sample and hold bypass applies to these channels. */
#define ADC_MASK_SAMPLE_HOLD_BYPASS_CHANNELS        (0x7U)

/* Sample and hold bypass starts at bit 8. */
#define ADC_MASK_SAMPLE_HOLD_BYPASS_SHIFT           (8U)

/* Value for ADPGADCR0 to disable PGA */
#define ADC_ADPGADCR0_DISABLE_PGA                   (0x0000)

/* Value for ADPGACR to disable PGA */
#define ADC_ADPGACR_DISABLE_PGA                     (0x9999)

/* Position of ADCALEXE to start calibration-CALEXE bit */
#define ADC_ADCALEXE_SET_CALEXE                     (0x80U)

/* Position of ADCALEXE calibration-CALMON bit */
#define ADC_ADCALEXE_CALIBRATION_STATUS             (0x40U)

/* Value of ADICR with interrupt at end of calibration */
#define ADC_ADICR_CALIBRATION_INTERRUPT_ENABLED     (0x03U)

/* Value of ADICR with no interrupt at end of calibration */
#define ADC_ADICR_CALIBRATION_INTERRUPT_DISABLED    (0x00U)

/* Stabilization time when BGR is enabled */
#define ADC_BGR_STABILIZATION_DELAY_US              (150U)

/* Bit set in adc_vref_control if the internal voltage reference is used for VREFH. */
#define ADC_PRV_ADHVREFCNT_VREF_INTERNAL_BIT_1      (1U << 1)

#define ADC_PRV_ADCSR_ADST_TRGE_MASK                (R_ADC0_ADCSR_ADST_Msk | R_ADC0_ADCSR_TRGE_Msk)
#define ADC_PRV_ADCSR_CLEAR_ADST_TRGE               (~ADC_PRV_ADCSR_ADST_TRGE_MASK)

#define ADC_PRV_TSCR_TSN_ENABLE                     (R_TSN_CTRL_TSCR_TSEN_Msk | R_TSN_CTRL_TSCR_TSOE_Msk)

#define ADC_PRV_ADBUF_ENABLED                       (1U)

#define ADC_MASK_FIRST_SENSOR_BIT                   (29U)

#if 1U == BSP_FEATURE_TSN_CALIBRATION32_AVAILABLE
 #define R_TSN                                      (R_TSN_CAL)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * adc_prv_ns_callback)(adc_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile adc_prv_ns_callback)(adc_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
#if ADC_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_adc_open_cfg_check(adc_cfg_t const * const p_cfg);
static fsp_err_t r_adc_open_cfg_resolution_check(adc_cfg_t const * const p_cfg);
static fsp_err_t r_adc_sample_state_cfg_check(adc_instance_ctrl_t * p_instance_ctrl, adc_sample_state_t * p_sample);

static fsp_err_t r_adc_scan_cfg_check_sample_hold(adc_instance_ctrl_t * const     p_instance_ctrl,
                                                  adc_channel_cfg_t const * const p_channel_cfg);

static fsp_err_t r_adc_scan_cfg_check_sensors(adc_instance_ctrl_t * const     p_instance_ctrl,
                                              adc_channel_cfg_t const * const p_channel_cfg);

#endif

static void r_adc_open_sub(adc_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg);

static void r_adc_sensor_cfg(adc_instance_ctrl_t * const     p_instance_ctrl,
                             adc_channel_cfg_t const * const p_channel_cfg);

#if ADC_CFG_PARAM_CHECKING_ENABLE

static fsp_err_t r_adc_scan_cfg_check(adc_instance_ctrl_t * const     p_instance_ctrl,
                                      adc_channel_cfg_t const * const p_channel_cfg);

#endif

static void r_adc_scan_cfg(adc_instance_ctrl_t * const     p_instance_ctrl,
                           adc_channel_cfg_t const * const p_channel_cfg);
static void     r_adc_sensor_sample_state_calculation(uint32_t * const p_sample_states);
void            adc_scan_end_b_isr(void);
void            adc_scan_end_isr(void);
void            adc_window_compare_isr(void);
static void     r_adc_irq_enable(IRQn_Type irq, uint8_t ipl, void * p_context);
static void     r_adc_irq_disable(IRQn_Type irq);
static uint32_t r_adc_lowest_channel_get(uint32_t adc_mask);
static void     r_adc_scan_end_common_isr(adc_event_t event);

#if ADC_CFG_PARAM_CHECKING_ENABLE

/** Mask of valid channels on this MCU. */
static const uint32_t g_adc_valid_channels[] =
{
    BSP_FEATURE_ADC_UNIT_0_CHANNELS,
 #if BSP_FEATURE_ADC_UNIT_1_CHANNELS
    BSP_FEATURE_ADC_UNIT_1_CHANNELS
 #endif
};
#endif

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** ADC Implementation of ADC. */
const adc_api_t g_adc_on_adc =
{
    .open           = R_ADC_Open,
    .scanCfg        = R_ADC_ScanCfg,
    .infoGet        = R_ADC_InfoGet,
    .scanStart      = R_ADC_ScanStart,
    .scanGroupStart = R_ADC_ScanGroupStart,
    .scanStop       = R_ADC_ScanStop,
    .scanStatusGet  = R_ADC_StatusGet,
    .read           = R_ADC_Read,
    .read32         = R_ADC_Read32,
    .close          = R_ADC_Close,
    .calibrate      = R_ADC_Calibrate,
    .offsetSet      = R_ADC_OffsetSet,
    .callbackSet    = R_ADC_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup ADC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Sets the operational mode, trigger sources, interrupt  priority, and configurations for the peripheral as a whole.
 * If interrupt is enabled, the function registers a callback function pointer for notifying the user whenever a scan
 * has completed.
 *
 * @retval FSP_SUCCESS                     Module is ready for use.
 * @retval FSP_ERR_ASSERTION               An input argument is invalid.
 * @retval FSP_ERR_ALREADY_OPEN            The instance control structure has already been opened.
 * @retval FSP_ERR_IRQ_BSP_DISABLED        A callback is provided, but the interrupt is not enabled.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT  The requested unit does not exist on this MCU.
 * @retval FSP_ERR_INVALID_HW_CONDITION    The ADC clock must be at least 1 MHz
 **********************************************************************************************************************/
fsp_err_t R_ADC_Open (adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg)
{
    adc_instance_ctrl_t * p_instance_ctrl = (adc_instance_ctrl_t *) p_ctrl;

    /*  Perform parameter checking */
#if ADC_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(NULL != p_instance_ctrl);

    /* Verify the configuration parameters are valid   */
    fsp_err_t err = r_adc_open_cfg_check(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check for valid argument values for options that are unique to the IP */
    err = r_adc_open_cfg_resolution_check(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Verify this unit has not already been initialized   */
    FSP_ERROR_RETURN(ADC_OPEN != p_instance_ctrl->opened, FSP_ERR_ALREADY_OPEN);

    /* If a callback is used, then make sure an interrupt is enabled */
    adc_extended_cfg_t const * p_extend = (adc_extended_cfg_t const *) p_cfg->p_extend;
    if (NULL != p_cfg->p_callback)
    {
        FSP_ERROR_RETURN((p_cfg->scan_end_irq >= 0) || (p_extend->window_a_irq >= 0) || (p_extend->window_b_irq >= 0),
                         FSP_ERR_IRQ_BSP_DISABLED);

        /* Group B interrupts are never required since group B can be configured in continuous scan mode when group A
         * has priority over group B. */
    }

#else
    adc_extended_cfg_t const * p_extend = (adc_extended_cfg_t const *) p_cfg->p_extend;
#endif

    /* Save configurations. */
    p_instance_ctrl->p_cfg             = p_cfg;
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

    /* Calculate the register base address. */
    uint32_t address_gap = (uint32_t) R_ADC1 - (uint32_t) R_ADC0;
    p_instance_ctrl->p_reg = (R_ADC0_Type *) ((uint32_t) R_ADC0 + (address_gap * p_cfg->unit));

    /* Initialize the hardware based on the configuration. */
    r_adc_open_sub(p_instance_ctrl, p_cfg);

    /* Enable interrupts */
    r_adc_irq_enable(p_cfg->scan_end_irq, p_cfg->scan_end_ipl, p_instance_ctrl);
    r_adc_irq_enable(p_cfg->scan_end_b_irq, p_cfg->scan_end_b_ipl, p_instance_ctrl);
    r_adc_irq_enable(p_extend->window_a_irq, p_extend->window_a_ipl, p_instance_ctrl);
    r_adc_irq_enable(p_extend->window_b_irq, p_extend->window_b_ipl, p_instance_ctrl);

    /* Invalid scan mask (initialized for later). */
    p_instance_ctrl->scan_mask = 0U;

    /* Mark driver as opened by initializing it to "RADC" in its ASCII equivalent for this unit. */
    p_instance_ctrl->opened = ADC_OPEN;

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures the ADC scan parameters. Channel specific settings are set in this function. Pass a pointer to
 * @ref adc_channel_cfg_t to p_channel_cfg.
 *
 * @note This starts group B scans if adc_channel_cfg_t::priority_group_a is set to ADC_GROUP_A_GROUP_B_CONTINUOUS_SCAN.
 *
 * @retval FSP_SUCCESS                 Channel specific settings applied.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_ScanCfg (adc_ctrl_t * p_ctrl, void const * const p_channel_cfg)
{
    adc_channel_cfg_t const * p_adc_channel_cfg = (adc_channel_cfg_t const *) p_channel_cfg;
    adc_instance_ctrl_t     * p_instance_ctrl   = (adc_instance_ctrl_t *) p_ctrl;
    fsp_err_t                 err               = FSP_SUCCESS;

#if ADC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_adc_channel_cfg);
    FSP_ERROR_RETURN(ADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);

    err = r_adc_scan_cfg_check(p_instance_ctrl, p_adc_channel_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Configure the hardware based on the configuration */
    r_adc_scan_cfg(p_instance_ctrl, p_adc_channel_cfg);

    /* Save the scan mask locally; this is required for the infoGet function. */
    p_instance_ctrl->scan_mask = p_adc_channel_cfg->scan_mask;

    /* Return the error code */
    return err;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements adc_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_ADC_CallbackSet (adc_ctrl_t * const          p_api_ctrl,
                             void (                    * p_callback)(adc_callback_args_t *),
                             void * const                p_context,
                             adc_callback_args_t * const p_callback_memory)
{
    adc_instance_ctrl_t * p_ctrl = (adc_instance_ctrl_t *) p_api_ctrl;

#if (ADC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(ADC_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if ADC_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    adc_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif

    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(adc_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif

    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts a software scan or enables the hardware trigger for a scan depending on how the triggers were configured in
 * the R_ADC_Open call. If the unit was configured for ELC or external hardware triggering, then this function allows
 * the trigger signal to get to the ADC unit. The function is not able to control the generation of the trigger itself.
 * If the unit was configured for software triggering, then this function starts the software triggered scan.
 *
 * @pre Call R_ADC_ScanCfg after R_ADC_Open before starting a scan.
 *
 * @pre On MCUs that support calibration, call R_ADC_Calibrate and wait for calibration to complete before starting
 * a scan.
 *
 * @retval FSP_SUCCESS                 Scan started (software trigger) or hardware triggers enabled.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit is not initialized.
 * @retval FSP_ERR_IN_USE              Another scan is still in progress (software trigger).
 **********************************************************************************************************************/
fsp_err_t R_ADC_ScanStart (adc_ctrl_t * p_ctrl)
{
    adc_instance_ctrl_t * p_instance_ctrl = (adc_instance_ctrl_t *) p_ctrl;

    /* Perform parameter checking  */
#if ADC_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
    if (ADC_GROUP_A_GROUP_B_CONTINUOUS_SCAN != p_instance_ctrl->p_reg->ADGSPCR)
    {
        FSP_ERROR_RETURN(0U == p_instance_ctrl->p_reg->ADCSR_b.ADST, FSP_ERR_IN_USE);
    }
#endif

    /* Enable hardware trigger or start software scan depending on mode. */
    p_instance_ctrl->p_reg->ADCSR = p_instance_ctrl->scan_start_adcsr;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::scanStart is not supported on the ADCH. Use scanStart instead.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_ADC_ScanGroupStart (adc_ctrl_t * p_ctrl, adc_group_mask_t group_id)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(group_id);

    /* Return the unsupported error. */
    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Stops the software scan or disables the unit from being triggered by the hardware trigger (ELC or external) based on
 * what type of trigger the unit was configured for in the R_ADC_Open function. Stopping a hardware triggered scan via
 * this function does not abort an ongoing scan, but prevents the next scan from occurring. Stopping a software
 * triggered scan aborts an ongoing scan.
 *
 * @retval FSP_SUCCESS                 Scan stopped (software trigger) or hardware triggers disabled.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_ScanStop (adc_ctrl_t * p_ctrl)
{
    adc_instance_ctrl_t * p_instance_ctrl = (adc_instance_ctrl_t *) p_ctrl;

    /*  Perform parameter checking */
#if ADC_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    /* Disable hardware trigger or stop software scan depending on mode. */
    p_instance_ctrl->p_reg->ADCSR = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the status of any scan process that was started, including scans started by ELC or external triggers and
 * calibration scans on MCUs that support calibration.
 *
 * @retval FSP_SUCCESS                 Module status stored in the provided pointer p_status
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_StatusGet (adc_ctrl_t * p_ctrl, adc_status_t * p_status)
{
    adc_instance_ctrl_t * p_instance_ctrl = (adc_instance_ctrl_t *) p_ctrl;

#if ADC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(ADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Read the status of the ADST bit. ADST is set when a scan is in progress, including calibration scans. */
    p_status->state = (adc_state_t) p_instance_ctrl->p_reg->ADCSR_b.ADST;

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads conversion results from a single channel or sensor.
 *
 * @retval FSP_SUCCESS                 Data read into provided p_data.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_Read (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data)
{
    adc_instance_ctrl_t * p_instance_ctrl = (adc_instance_ctrl_t *) p_ctrl;

    /* Perform parameter checking. */
#if ADC_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(ADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);

    /* Verify that the channel is valid for this MCU */
    if ((reg_id >= ADC_CHANNEL_0) && ((uint32_t) reg_id <= 31U))
    {
        uint32_t requested_channel_mask = (1U << (uint32_t) reg_id);
        FSP_ASSERT(0 != (requested_channel_mask & g_adc_valid_channels[p_instance_ctrl->p_cfg->unit]));
    }
    else
    {
        FSP_ASSERT((reg_id == ADC_CHANNEL_TEMPERATURE) || (reg_id == ADC_CHANNEL_VOLT) ||
                   (reg_id == ADC_CHANNEL_DUPLEX) || (reg_id == ADC_CHANNEL_DUPLEX_A) ||
                   (reg_id == ADC_CHANNEL_DUPLEX_B));
    }

    /* Data is not available to be read from ADDRn registers when ADBUF is enabled. Read API cannot be used with ADBUF enabled. */
    adc_extended_cfg_t * p_extend = (adc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    FSP_ASSERT(1U != p_extend->enable_adbuf);
#endif

    /* Read the data from the requested ADC conversion register and return it */
    *p_data = p_instance_ctrl->p_reg->ADDR[reg_id];

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads conversion results from a single channel or sensor register into a 32-bit result.
 *
 * @retval FSP_SUCCESS                 Data read into provided p_data.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_Read32 (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data)
{
    uint16_t result    = 0U;
    uint32_t result_32 = 0U;

#if ADC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_data);
#endif

    fsp_err_t err = R_ADC_Read(p_ctrl, reg_id, &result);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    result_32 = result;

    /* Left shift the result into the upper 16 bits if the unit is configured for left alignment. */
    adc_instance_ctrl_t * p_instance_ctrl = (adc_instance_ctrl_t *) p_ctrl;
    if (ADC_ALIGNMENT_LEFT == p_instance_ctrl->p_cfg->alignment)
    {
        result_32 <<= ADC_SHIFT_LEFT_ALIGNED_32_BIT;
    }

    *p_data = result_32;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets the sample state count for individual channels. This only needs to be set for special use cases. Normally, use
 * the default values out of reset.
 *
 * @note The sample states for the temperature and voltage sensor are set in R_ADC_ScanCfg.
 *
 * @retval FSP_SUCCESS                 Sample state count updated.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit is not initialized.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_SampleStateCountSet (adc_ctrl_t * p_ctrl, adc_sample_state_t * p_sample)
{
    adc_instance_ctrl_t * p_instance_ctrl = (adc_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err             = FSP_SUCCESS;

    /* Perform parameter checking */
#if ADC_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_sample);
    FSP_ERROR_RETURN(ADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);

    /* Verify arguments are legal */
    err = r_adc_sample_state_cfg_check(p_instance_ctrl, p_sample);
    if (FSP_SUCCESS != err)
    {
        return err;
    }
#endif

    /* Set the sample state count for the specified register */
    p_instance_ctrl->p_reg->ADSSTR[p_sample->reg_id] = p_sample->num_states;

    /* Return the error code */
    return err;
}

/*******************************************************************************************************************//**
 * Returns the address of the lowest number configured channel and the total number of bytes to be read in order to
 * read the results of the configured channels and return the ELC Event name. If no channels are configured, then a
 * length of 0 is returned.
 *
 * Also provides the temperature sensor slope and the calibration data for the sensor if available on this MCU.
 * Otherwise, invalid calibration data of 0xFFFFFFFF will be returned.
 *
 * @note In group mode, information is returned for group A only.  Calculating information for group B is not currently
 * supported.
 *
 * @retval FSP_SUCCESS                 Information stored in p_adc_info.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_InfoGet (adc_ctrl_t * p_ctrl, adc_info_t * p_adc_info)
{
    adc_instance_ctrl_t * p_instance_ctrl = (adc_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err             = FSP_SUCCESS;
    uint32_t              adc_mask        = 0;

#if ADC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_adc_info);
    FSP_ERROR_RETURN(ADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Retrieve the scan mask of active channels from the control structure */
    adc_mask = p_instance_ctrl->scan_mask;

    /* If at least one channel is configured, determine the highest and lowest configured channels. */
    if (adc_mask != 0U)
    {
        /* Determine the lowest channel that is configured. The lowest sensor is the temperature sensor, at -3 from
         * channel 0. To get all channels in register order, shift up by 3, then add in the sensors in the bottom
         * 2 bits. */
        uint32_t adc_mask_in_order = adc_mask & ~(uint32_t) ADC_MASK_SENSORS;
        adc_mask_in_order <<= 3U;
        adc_mask_in_order  |= adc_mask >> ADC_MASK_FIRST_SENSOR_BIT;
        uint32_t lowest_channel = r_adc_lowest_channel_get(adc_mask_in_order);
        p_adc_info->p_address = &p_instance_ctrl->p_reg->ADDR[lowest_channel - 3];

        /* Determine the highest channel that is configured. */
        uint32_t highest_channel = 31 - __CLZ(adc_mask_in_order);

        /* Determine the size of data that must be read to read all the channels between and including the
         * highest and lowest channels.*/
        p_adc_info->length = (uint32_t) ((highest_channel - lowest_channel) + 1);
    }
    else
    {
        /* If no channels are configured, set the return length 0. */
        p_adc_info->length = 0U;
    }

    p_adc_info->transfer_size = TRANSFER_SIZE_2_BYTE;

#if BSP_FEATURE_ADC_UNIT_1_CHANNELS

    /* Specify the peripheral name in the ELC list */
    p_adc_info->elc_event =
        (elc_event_t) ((uint32_t) ELC_EVENT_ADC0_SCAN_END +
                       (p_instance_ctrl->p_cfg->unit *
                        ((uint32_t) ELC_EVENT_ADC1_SCAN_END - (uint32_t) ELC_EVENT_ADC0_SCAN_END)));
#else
    p_adc_info->elc_event = ELC_EVENT_ADC0_SCAN_END;
#endif

    p_adc_info->elc_peripheral = (elc_peripheral_t) (ELC_PERIPHERAL_ADC0 + (2U * p_instance_ctrl->p_cfg->unit));

    /* Set Temp Sensor calibration data to invalid value */
    p_adc_info->calibration_data = UINT32_MAX;

    /* If calibration register is available, retrieve it from the MCU */
#if 1U == BSP_FEATURE_TSN_CALIBRATION_AVAILABLE

    /* Read into memory. */
    uint32_t data = R_TSN->TSCDR;

 #if 1U == BSP_FEATURE_TSN_CALIBRATION32_AVAILABLE

    /* Read the temperature calibration data from ROM. */
    p_adc_info->calibration_data = (data & BSP_FEATURE_TSN_CALIBRATION32_MASK);
 #else

    /* Read the temperature calibration data from ROM. */
    p_adc_info->calibration_data = data;

  #if 1U == BSP_FEATURE_TSN_HAS_ROOM_TEMP_REG

    /* Read the temperature calibration data from ROM. */
    p_adc_info->room_calibration_data = R_TSN->TSCDRR;
  #endif

  #if 1U == BSP_FEATURE_TSN_HAS_LOW_TEMP_REG

    /* Read the temperature calibration data from ROM. */
    p_adc_info->low_calibration_data = R_TSN->TSCDRL;
  #endif
 #endif
#endif

    /* Provide the previously retrieved slope information */
    p_adc_info->slope_microvolts = BSP_FEATURE_TSN_SLOPE;

    return err;
}

/*******************************************************************************************************************//**
 * This function ends any scan in progress, disables interrupts, and removes power to the A/D peripheral.
 *
 * @retval FSP_SUCCESS                 Module closed.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_Close (adc_ctrl_t * p_ctrl)
{
    adc_instance_ctrl_t * p_instance_ctrl = (adc_instance_ctrl_t *) p_ctrl;

#if ADC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Mark driver as closed   */
    p_instance_ctrl->opened      = 0U;
    p_instance_ctrl->initialized = 0U;

    /* Disable interrupts. */
    adc_extended_cfg_t * p_extend = (adc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    r_adc_irq_disable(p_instance_ctrl->p_cfg->scan_end_irq);
    r_adc_irq_disable(p_instance_ctrl->p_cfg->scan_end_b_irq);
    r_adc_irq_disable(p_extend->window_a_irq);
    r_adc_irq_disable(p_extend->window_b_irq);

    /* Disable triggers. */
    p_instance_ctrl->p_reg->ADSTRGR = 0U;

    /* Stop the ADC. */
    p_instance_ctrl->p_reg->ADCSR = 0U;

#if BSP_FEATURE_ADC_HAS_SAMPLE_HOLD_REG

    /* Disable sample and hold before entering module stop state to reduce power consumption (reference section 47.6.8
     * "Available Functions and Register Settings of AN000 to AN002, AN007, AN100 to AN102, and AN107" in the RA6M3
     * manual R01UH0886EJ0100. */
    p_instance_ctrl->p_reg->ADSHCR = 0U;
#endif

#if BSP_FEATURE_ADC_HAS_VREFAMPCNT

    /* If VREFADC is selected as the high-potential reference voltage revert it to reduce power consumption. */
    p_instance_ctrl->p_reg->VREFAMPCNT = 0U;
#endif

    R_BSP_MODULE_STOP(FSP_IP_ADC, p_instance_ctrl->p_cfg->unit);

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initiates calibration of the ADC on MCUs that require calibration.  This function must be called before starting
 * a scan on MCUs that require calibration.
 *
 * Calibration is complete when the callback is called with ADC_EVENT_CALIBRATION_COMPLETE or when R_ADC_StatusGet
 * returns ADC_STATUS_IDLE. Reference Figure 32.35 "Software flow and operation example of calibration operation."
 * in the RA2A1 manual R01UH0888EJ0100.
 *
 * ADC calibration time: 12 PCLKB + 774,930 ADCLK. (Reference Table 32.16 "Required calibration time (shown
 * as the number of ADCLK and PCLKB cycles)" in the RA2A1 manual R01UH0888EJ0100. The lowest supported ADCLK
 * is 1MHz.
 *
 * Calibration will take a minimum of 24 milliseconds at 32 MHz PCLKB and ADCLK. This wait could take up to 780
 * milliseconds for a 1 MHz PCLKD (ADCLK).
 *
 * @param[in]  p_ctrl    Pointer to the instance control structure
 * @param[in]  p_extend  Unused argument. Pass NULL.
 *
 * @retval FSP_SUCCESS                     Calibration successfully initiated.
 * @retval FSP_ERR_INVALID_HW_CONDITION    A scan is in progress or hardware triggers are enabled.
 * @retval FSP_ERR_UNSUPPORTED             Calibration not supported on this MCU.
 * @retval FSP_ERR_ASSERTION               An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN                Unit is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_Calibrate (adc_ctrl_t * const p_ctrl, void const * p_extend)
{
    FSP_PARAMETER_NOT_USED(p_extend);

#if BSP_FEATURE_ADC_CALIBRATION_REG_AVAILABLE
    adc_instance_ctrl_t * p_instance_ctrl = (adc_instance_ctrl_t *) p_ctrl;
 #if ADC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
 #endif

    /* ADC Calibration can only happen if there is no ongoing scan and if the scan trigger is disabled */
    FSP_ERROR_RETURN(!(p_instance_ctrl->p_reg->ADCSR & ADC_PRV_ADCSR_ADST_TRGE_MASK), FSP_ERR_INVALID_HW_CONDITION);

    /* Set the normal mode interrupt request to occur when calibration is complete */
    p_instance_ctrl->p_reg->ADICR = ADC_ADICR_CALIBRATION_INTERRUPT_ENABLED;

    /* Initiate calibration */
    p_instance_ctrl->p_reg->ADCALEXE = ADC_ADCALEXE_SET_CALEXE;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_ERROR_LOG(FSP_ERR_UNSUPPORTED);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::offsetSet is not supported on the ADC.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_ADC_OffsetSet (adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t offset)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(reg_id);
    FSP_PARAMETER_NOT_USED(offset);

    /* Return the unsupported error. */
    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup ADC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if ADC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Checks the sample state configuration.
 *
 * @param[in]  p_instance_ctrl             Pointer to instance control structure
 * @param[in]  p_sample                    Pointer to sample state configuration
 *
 * @retval FSP_SUCCESS                     No configuration errors detected
 * @retval FSP_ERR_ASSERTION               An input argument is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_adc_sample_state_cfg_check (adc_instance_ctrl_t * p_instance_ctrl, adc_sample_state_t * p_sample)
{
    /* Used to prevent compiler warning */
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);

    adc_sample_state_reg_t reg_id = p_sample->reg_id;

    /* Verify the requested channel exists on the MCU. */
    if (reg_id >= ADC_SAMPLE_STATE_CHANNEL_0)
    {
        uint32_t requested_channel_mask = (1U << (uint32_t) reg_id);
        FSP_ASSERT(0 != (requested_channel_mask & g_adc_valid_channels[p_instance_ctrl->p_cfg->unit]));
    }

    /* Verify the requested sample states is not less than the minimum. */
    FSP_ASSERT(p_sample->num_states >= ADC_SAMPLE_STATE_COUNT_MIN);

    return FSP_SUCCESS;
}

#endif

#if ADC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Validates the configuration arguments for illegal combinations or options.
 *
 * @param[in]  p_cfg                   Pointer to configuration structure
 *
 * @retval FSP_SUCCESS                     No configuration errors detected
 * @retval FSP_ERR_ASSERTION               An input argument is invalid.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT  ADC unit not present on this MCU
 * @retval FSP_ERR_INVALID_HW_CONDITION    The ADC clock must be at least 1 MHz
 **********************************************************************************************************************/
static fsp_err_t r_adc_open_cfg_check (adc_cfg_t const * const p_cfg)
{
    FSP_ASSERT(NULL != p_cfg);

    /* Verify the unit exists on the MCU. */
    FSP_ERROR_RETURN(((1U << p_cfg->unit) & BSP_FEATURE_ADC_VALID_UNIT_MASK), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    /* Verify the ADC clock frequency is at least 1 MHz (reference "Frequency" row of table "60.5 ADC12
     * Characteristics" in the RA6M3 manual R01UH0886EJ0100. The maximum frequency is the maximum frequency supported
     * by the ADCLK, so it is not verified here. */
    uint32_t freq_hz = R_FSP_SystemClockHzGet(BSP_FEATURE_ADC_CLOCK_SOURCE);
    FSP_ERROR_RETURN(freq_hz >= ADC_PRV_MIN_ADCLK_HZ, FSP_ERR_INVALID_HW_CONDITION);

    /* Check for valid argument values for addition/averaging. Reference section 47.2.10 "A/D-Converted Value
     * Addition/Average Count Select Register (ADADC)" in the RA6M3 manual R01UH0886EJ0100 and section 32.2.11
     * "A/D-Converted Value Average Count Select Register (ADADC)" in the RA2A1 manual R01UH0888EJ0100. */
    adc_extended_cfg_t const * p_cfg_extend = (adc_extended_cfg_t const *) p_cfg->p_extend;
    if (ADC_ADD_OFF != p_cfg_extend->add_average_count)
    {
 #if BSP_FEATURE_ADC_ADDITION_SUPPORTED

        /* The ADC12 and ADC14 do not support averaging 8 or 16 samples. */
        FSP_ASSERT(p_cfg_extend->add_average_count <= ADC_ADD_AVERAGE_FOUR);
 #else

        /* The ADC16 supports averaging only, it does not support addition. */
        FSP_ASSERT(0U != (ADC_ADADC_AVEE_BIT & p_cfg_extend->add_average_count));
 #endif
    }

    /* If 16 time addition is used only 12 bit accuracy can be selected. Reference Note 1 of section 47.2.10
     * "A/D-Converted Value Addition/Average Count Select Register (ADADC)" in the RA6M3 manual R01UH0886EJ0100. */
    if (ADC_ADD_SIXTEEN == p_cfg_extend->add_average_count)
    {
        FSP_ASSERT(ADC_RESOLUTION_12_BIT == p_cfg->resolution);
    }

    /* Only synchronous triggers (ELC) allowed in group scan mode (reference TRSA documentation in section 47.2.12
     * "A/D Conversion Start Trigger Select Register (ADSTRGR)" in the RA6M3 manual R01UH0886EJ0100.  */
    if ((ADC_MODE_GROUP_SCAN == p_cfg->mode) || (ADC_DOUBLE_TRIGGER_DISABLED != p_cfg_extend->double_trigger_mode))
    {
        FSP_ASSERT((ADC_START_SOURCE_DISABLED != p_cfg_extend->trigger) &&
                   (ADC_START_SOURCE_ASYNC_EXTERNAL != p_cfg_extend->trigger));

        if ((ADC_MODE_GROUP_SCAN == p_cfg->mode))
        {
            FSP_ASSERT((ADC_START_SOURCE_DISABLED != p_cfg_extend->trigger_group_b) && \
                       (ADC_START_SOURCE_ASYNC_EXTERNAL != p_cfg_extend->trigger_group_b));
        }
    }

    return FSP_SUCCESS;
}

#endif

#if ADC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * This function validates the resolution configuration arguments for illegal combinations or options.
 *
 * @param[in]  p_cfg                   Pointer to configuration structure
 *
 * @retval FSP_SUCCESS                 No configuration errors detected
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_adc_open_cfg_resolution_check (adc_cfg_t const * const p_cfg)
{
 #if 12U == BSP_FEATURE_ADC_MAX_RESOLUTION_BITS
  #if BSP_FEATURE_ADC_HAS_ADCER_ADPRC

    /* Resolution options for ADC12 (reference section 47.2.11 "A/D Control Extended Register (ADCER)" in the RA6M3
     * manual R01UH0886EJ0100. */
    FSP_ASSERT((ADC_RESOLUTION_12_BIT == p_cfg->resolution) ||
               (ADC_RESOLUTION_10_BIT == p_cfg->resolution) ||
               (ADC_RESOLUTION_8_BIT == p_cfg->resolution));
  #else
    FSP_ASSERT(ADC_RESOLUTION_12_BIT == p_cfg->resolution);
  #endif
 #endif

 #if 14U == BSP_FEATURE_ADC_MAX_RESOLUTION_BITS

    /* Resolution options for ADC14 (reference section 35.2.11 "A/D Control Extended Register (ADCER)" in the RA4M1
     * manual R01UH0886EJ0100. */
    FSP_ASSERT((ADC_RESOLUTION_12_BIT == p_cfg->resolution) ||
               (ADC_RESOLUTION_14_BIT == p_cfg->resolution));
 #endif

 #if 16U == BSP_FEATURE_ADC_MAX_RESOLUTION_BITS

    /* ADC16 only offers 16-bit resolution (reference Table 32.1 "ADC16 specifications (1 of 2)" in the RA2A1 manual
     * R01UH0888EJ0100. */
    FSP_ASSERT(ADC_RESOLUTION_16_BIT == p_cfg->resolution);
 #endif

    return FSP_SUCCESS;
}

#endif

#if ADC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Checks the sample and hold arguments
 *
 * @param[in]  p_instance_ctrl         Pointer to instance control block
 * @param[in]  p_channel_cfg           Pointer to channel configuration
 *
 * @retval FSP_SUCCESS                 No configuration errors detected
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_adc_scan_cfg_check_sample_hold (adc_instance_ctrl_t * const     p_instance_ctrl,
                                                   adc_channel_cfg_t const * const p_channel_cfg)
{
 #if !BSP_FEATURE_ADC_HAS_SAMPLE_HOLD_REG

    /* If the MCU does not have sample and hold, verify the sample and hold feature is not used. */
    FSP_ASSERT(0U == p_channel_cfg->sample_hold_mask);
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
 #else
    if (0U != p_channel_cfg->sample_hold_mask)
    {
        /* Sample and Hold channels can only be 0, 1, 2 and must have at least minimum state count specified (reference
         * section 47.2.15 "A/D Sample and Hold Circuit Control Register (ADSHCR)" in the RA6M3 manual
         * R01UH0886EJ0100. */
        FSP_ASSERT(p_channel_cfg->sample_hold_mask <= ADC_SAMPLE_HOLD_CHANNELS);
        FSP_ASSERT(p_channel_cfg->sample_hold_states >= ADC_SAMPLE_STATE_HOLD_COUNT_MIN);

        uint32_t b_mask = p_channel_cfg->sample_hold_mask & p_channel_cfg->scan_mask_group_b;
        if (ADC_MODE_GROUP_SCAN == p_instance_ctrl->p_cfg->mode)
        {
            if (ADC_GROUP_A_PRIORITY_OFF != p_channel_cfg->priority_group_a)
            {
                /* Sample and hold channels cannot be in GroupB if GroupA priority enabled. (reference SHANS[2:0] bits
                 * in section 47.2.15 "A/D Sample and Hold Circuit Control Register (ADSHCR)" in the RA6M3 manual
                 * R01UH0886EJ0100.*/
                FSP_ASSERT(0 == b_mask);
            }
        }
    }
 #endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enforces constraints on Window Compare function usage per section 47.3.5.3 "Constraints on the compare function" in
 * the RA6M3 User's Manual (R01UH0886EJ0100)
 *
 * @param[in]  p_window_cfg            Pointer to window compare configuration
 *
 * @retval FSP_SUCCESS                 No configuration errors detected
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_adc_scan_cfg_check_window_compare (adc_window_cfg_t const * const p_window_cfg)
{
    if (p_window_cfg)
    {
        uint32_t compare_cfg = p_window_cfg->compare_cfg;
        if (0U != compare_cfg)
        {
            if ((compare_cfg & R_ADC0_ADCMPCR_CMPAE_Msk) && (compare_cfg & R_ADC0_ADCMPCR_CMPBE_Msk))
            {
                /* Ensure channels selected for Window A do not conflict with Window B */
                uint32_t compare_b_ch = p_window_cfg->compare_b_channel;
                compare_b_ch -= compare_b_ch > 31 ? 4 : 0;
                FSP_ASSERT(!(p_window_cfg->compare_mask & (uint32_t) (1 << compare_b_ch)));
            }

            if (compare_cfg & R_ADC0_ADCMPCR_WCMPE_Msk)
            {
                /* Ensure lower reference values are less than or equal to the high reference values */
                FSP_ASSERT((p_window_cfg->compare_ref_low <= p_window_cfg->compare_ref_high) &&
                           (p_window_cfg->compare_b_ref_low <= p_window_cfg->compare_b_ref_high));
            }
        }
    }

    return FSP_SUCCESS;
}

#endif

#if ADC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * This function checks the Temperature and Voltage sensor arguments
 *
 * @param[in]  p_instance_ctrl         Pointer to instance control block
 * @param[in]  p_channel_cfg           Pointer to channel configuration
 *
 * @retval  FSP_SUCCESS                No configuration errors detected
 * @retval  FSP_ERR_ASSERTION          Sensor configuration has been selected for Group B on an MCU which does not allow
 *                                     Group B configuration or sensor is used in Normal/Group A with the double trigger
 *                                     not enabled or MCU does not allow both the sensors to be used simultaneously
 **********************************************************************************************************************/
static fsp_err_t r_adc_scan_cfg_check_sensors (adc_instance_ctrl_t * const     p_instance_ctrl,
                                               adc_channel_cfg_t const * const p_channel_cfg)
{
    /* Some MCUs have nothing to check here. */
    FSP_PARAMETER_NOT_USED(p_channel_cfg);

 #if !BSP_FEATURE_ADC_GROUP_B_SENSORS_ALLOWED

    /* Sensors are not supported in Group B in some MCUs. Reference section 32.2.14 "A/D Conversion Extended Input
     * Control Register (ADEXICR)" of the RA2A1 manual R01UH0888EJ0100. */
    FSP_ASSERT(0U == (p_channel_cfg->scan_mask_group_b & ADC_MASK_SENSORS));
 #endif

 #if BSP_FEATURE_ADC_SENSORS_EXCLUSIVE
    uint32_t sensor_mask = p_channel_cfg->scan_mask & ADC_MASK_SENSORS;
    if (0U != sensor_mask)
    {
        /* If the temperature sensor or the internal voltage reference is used, then none of the channels can be used
         * at the same time. The temperature sensor and the internal voltage reference can only be used in single scan
         * mode. Reference TSSA and OCSA bits in section 35.2.13 "A/D Conversion Extended Input Control Register
         * (ADEXICR)" of the RA4M1 manual R01UH0887EJ0100. */
        FSP_ASSERT(ADC_MASK_SENSORS != sensor_mask);
        FSP_ASSERT(p_channel_cfg->scan_mask == sensor_mask);
        FSP_ASSERT(ADC_MODE_SINGLE_SCAN == p_instance_ctrl->p_cfg->mode);
    }
 #endif

    /* When using double-trigger modes the sensors must not be configured or used in Group A. */
    adc_extended_cfg_t const * p_cfg_extend = (adc_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;
    if (ADC_DOUBLE_TRIGGER_DISABLED != p_cfg_extend->double_trigger_mode)
    {
        FSP_ASSERT(0U == (p_channel_cfg->scan_mask & ADC_MASK_SENSORS));
    }

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * The Open function applies power to the A/D peripheral, sets the operational mode, trigger sources, and
 * configurations common to all channels and sensors.
 *
 * @param[in]  p_instance_ctrl         Pointer to instance control block
 * @param[in]  p_cfg                   Pointer to configuration structure
 **********************************************************************************************************************/
static void r_adc_open_sub (adc_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg)
{
    adc_extended_cfg_t const * p_cfg_extend = (adc_extended_cfg_t const *) p_cfg->p_extend;

    /* Determine the value for ADCSR:
     *   * The configured mode is set in ADCSR.ADCS.
     *   * Low-power conversion mode must be selected when internal reference voltage is selected as the high-potential
     *     reference voltage.
     *   * ADCSR.GBADIE is always set by this driver. It will only trigger an interrupt in group mode if the group B
     *     interrupt is enabled.
     *   * If double-trigger mode is selected ADCSR.DBLANS is set to the chosen double-trigger scan channel and
     *     ADCSR.DBLE is set to 1; otherwise, both are set to 0.
     *   * The configured trigger mode is set in ADCSR.EXTRG and ADCSR.TRGE.
     *   * The value to set in ADCSR to start a scan is stored in the control structure. ADCSR.ADST is set in
     *     R_ADC_ScanStart if software trigger mode is used.
     */
    uint32_t adcsr = (uint32_t) (p_cfg->mode << R_ADC0_ADCSR_ADCS_Pos);
    adcsr |= (uint32_t) (R_ADC0_ADCSR_GBADIE_Msk | R_ADC0_ADCSR_TRGE_Msk);
    adcsr |= ((uint32_t) (ADC_START_SOURCE_ASYNC_EXTERNAL == p_cfg_extend->trigger) << R_ADC0_ADCSR_EXTRG_Pos); // Only check GroupA. GroupB is never external.
    adcsr |= ((uint32_t) (ADC_START_SOURCE_DISABLED != p_cfg_extend->trigger) << R_ADC0_ADCSR_TRGE_Pos);        // Only check GroupA. GroupB is never external.

#if BSP_FEATURE_ADC_HAS_ADHVREFCNT
    if (ADC_PRV_ADHVREFCNT_VREF_INTERNAL_BIT_1 & p_cfg_extend->adc_vref_control)
    {
        adcsr |= R_ADC0_ADCSR_ADHSC_Msk;
    }
#endif

    if (ADC_DOUBLE_TRIGGER_DISABLED != p_cfg_extend->double_trigger_mode)
    {
        adcsr |= R_ADC0_ADCSR_DBLE_Msk;
    }
    else if (ADC_START_SOURCE_DISABLED == p_cfg_extend->trigger)
    {
        adcsr |= R_ADC0_ADCSR_ADST_Msk;
    }
    else
    {
        /* Do nothing. */
    }

    p_instance_ctrl->scan_start_adcsr = (uint16_t) adcsr;

    /* The default value for ADSTRGR is 0 out of reset. Update it only if the ADC is triggered on ELC events. */

    /* Set ADSTRGR per the following:
     *   Extended double-trigger mode:
     *    - Normal (Group A): ELC_PERIPHERAL_ADCn and ELC_PERIPHERAL_ADCn_B
     *    - Group B: None
     *   All other modes:
     *    - Normal (Group A): ELC_PERIPHERAL_ADCn
     *    - Group B: ELC_PERIPHERAL_ADCn_B
     */
    uint32_t adstrgr =
        ((R_ADC0_ADSTRGR_TRSA_Msk & ((uint32_t) p_cfg_extend->trigger << R_ADC0_ADSTRGR_TRSA_Pos)) | \
         (R_ADC0_ADSTRGR_TRSB_Msk & ((uint32_t) p_cfg_extend->trigger_group_b << R_ADC0_ADSTRGR_TRSB_Pos)));

    /* Determine the value for ADCER:
     *   * The resolution is set as configured in ADCER.ADPRC (on MCUs that have this bitfield).
     *   * The alignment is set as configured in ADCER.ADFMT (on MCUs that have this bitfield).
     *   * The clearing option is set as configured in ADCER.ACE.
     *   * Always select data range of 0 - 32767 in ADCER.INV (on MCUs that have this bitfield).
     *   * Always disable self-diagnosis (unsupported in this module).
     */
    uint32_t adcer = 0U;
#if BSP_FEATURE_ADC_HAS_ADCER_ADPRC
    adcer |= (uint32_t) p_cfg->resolution << R_ADC0_ADCER_ADPRC_Pos;
#endif
#if BSP_FEATURE_ADC_HAS_ADCER_ADRFMT
    adcer |= (uint32_t) p_cfg->alignment << R_ADC0_ADCER_ADRFMT_Pos;
#endif
    adcer |= (uint32_t) p_cfg_extend->clearing << R_ADC0_ADCER_ACE_Pos;

#if BSP_FEATURE_ADC_CALIBRATION_REG_AVAILABLE
    adcer |= 1U << R_ADC0_ADCER_ADINV_Pos;
#endif

    /* Determine the value for ADADC:
     *   * The addition/averaging modes are set as configured in ADADC.ADC and ADADC.AVEE.
     *   * On MCUs that do not have the ADADC.AVEE bit (addition not supported), the ADADC.AVEE bit is cleared.
     */
    uint32_t adadc = p_cfg_extend->add_average_count;
#if !BSP_FEATURE_ADC_ADDITION_SUPPORTED
    adadc &= ~ADC_ADADC_AVEE_BIT;
#endif

    /* Apply clock to peripheral. */
    R_BSP_MODULE_START(FSP_IP_ADC, p_cfg->unit);

    /* Set the predetermined values for ADCSR, ADSTRGR, ADCER, and ADADC without setting ADCSR.ADST or ADCSR.TRGE.
     * ADCSR.ADST or ADCSR.TRGE are set as configured in R_ADC_ScanStart. */
    p_instance_ctrl->p_reg->ADCSR   = (uint16_t) (adcsr & ADC_PRV_ADCSR_CLEAR_ADST_TRGE);
    p_instance_ctrl->p_reg->ADSTRGR = (uint16_t) adstrgr;
    p_instance_ctrl->p_reg->ADCER   = (uint16_t) adcer;
    p_instance_ctrl->p_reg->ADADC   = (uint8_t) adadc;

#if BSP_FEATURE_ADC_HAS_PGA

    /* Disable the unused ADC PGA feature (on MCUs where it is available) since the feature is enabled out of reset on
     * some MCUs and disabled on others and affects the operation of the normal ADC channels that are multiplexed with
     * the PGA. */
    p_instance_ctrl->p_reg->ADPGADCR0 = ADC_ADPGADCR0_DISABLE_PGA;
    p_instance_ctrl->p_reg->ADPGACR   = ADC_ADPGACR_DISABLE_PGA;
#endif

#if BSP_FEATURE_ADC_CALIBRATION_REG_AVAILABLE

    /* Use ADC in single-ended mode. */
    p_instance_ctrl->p_reg->ADANIM = 0U;
#endif

#if BSP_FEATURE_ADC_HAS_VREFAMPCNT

    /* If VREFADC is selected as the high-potential reference voltage. */
    if (ADC_VREF_CONTROL_VREFH != p_cfg_extend->adc_vref_control)
    {
        /* Configure Reference Voltage controls
         * Reference section "32.6 Selecting Reference Voltage" in the RA2A1 manual R01UH0888EJ0100. */
        p_instance_ctrl->p_reg->VREFAMPCNT =
            (uint8_t) (p_cfg_extend->adc_vref_control &
                       (R_ADC0_VREFAMPCNT_BGREN_Msk | R_ADC0_VREFAMPCNT_VREFADCG_Msk));

        R_BSP_SoftwareDelay(ADC_BGR_STABILIZATION_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);

        /* Enable Over current detection and VREFADC output */
        p_instance_ctrl->p_reg->VREFAMPCNT = (uint8_t) (p_cfg_extend->adc_vref_control);
    }
#endif

#if BSP_FEATURE_ADC_HAS_ADHVREFCNT

    /* If the internal voltage is set as VREFH, discharge the VREF node for 1 us before setting ADHVREFCNT.HVSEL to 2.
     * Reference section 35.7 "A/D Conversion Procedure when Selecting Internal Reference Voltage as High-Potential
     * Reference Voltage" in the RA4M1 manual R01UH0887EJ0100.
     *
     * Also wait 5 us before using the ADC. This wait is the responsibility of the application. */
    if (ADC_PRV_ADHVREFCNT_VREF_INTERNAL_BIT_1 & p_cfg_extend->adc_vref_control)
    {
        p_instance_ctrl->p_reg->ADHVREFCNT = (uint8_t) (p_cfg_extend->adc_vref_control | R_ADC0_ADHVREFCNT_HVSEL_Msk);

        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
    }
    p_instance_ctrl->p_reg->ADHVREFCNT = (uint8_t) p_cfg_extend->adc_vref_control;
#endif

#if BSP_FEATURE_ADC_HAS_ADBUF
    uint8_t adbuf = 0;
    if (1U == p_cfg_extend->enable_adbuf)
    {
        adbuf = R_ADC0_ADBUFEN_BUFEN_Msk;
    }
    p_instance_ctrl->p_reg->ADBUFEN = adbuf;
#endif
}

/*******************************************************************************************************************//**
 * This function set the sensor bits taking into account group inclusion and addition/average mode.
 * This function must only be called if it has been verified that sensors are used in this configuration
 *
 * @param[in]  p_instance_ctrl         Pointer to instance control block
 * @param[in]  p_channel_cfg           Pointer to channel configuration
 **********************************************************************************************************************/
static void r_adc_sensor_cfg (adc_instance_ctrl_t * const     p_instance_ctrl,
                              adc_channel_cfg_t const * const p_channel_cfg)
{
    /* Calculate sample states required for temperature and voltage sensor at the current ADCLK speed. */
    uint32_t sample_states = 0U;
    r_adc_sensor_sample_state_calculation(&sample_states);

    /* Check if the temperature sensor channel is enabled */
    uint32_t combined_scan_mask = p_channel_cfg->scan_mask | p_channel_cfg->scan_mask_group_b;
    uint32_t adexicr            = 0U;
    if (combined_scan_mask & ADC_MASK_TEMPERATURE)
    {
#if BSP_FEATURE_TSN_CONTROL_AVAILABLE

        /* Power on the temperature sensor. This is only needed for TSNs that have the control register */
        R_BSP_MODULE_START(FSP_IP_TSN, 0U);

        /* Enable the temperature sensor output to the ADC */
        R_TSN_CTRL->TSCR = ADC_PRV_TSCR_TSN_ENABLE;
#endif

        /* Set sample state register to the calculated value */
        p_instance_ctrl->p_reg->ADSSTRT = (uint8_t) sample_states;

#if BSP_FEATURE_ADC_GROUP_B_SENSORS_ALLOWED
        if (p_channel_cfg->scan_mask & ADC_MASK_TEMPERATURE)
        {
            /* Scan the temperature sensor in normal/group A. */
            adexicr |= R_ADC0_ADEXICR_TSSA_Msk;
        }
        else
        {
            /* Scan the temperature sensor in group B */
            adexicr |= R_ADC0_ADEXICR_TSSB_Msk;
        }

#else

        /* Scan the temperature sensor in normal/group A. */
        adexicr |= R_ADC0_ADEXICR_TSSA_Msk;
#endif

        /* Enable temperature addition mode if configured. */
        if (p_channel_cfg->add_mask & ADC_MASK_TEMPERATURE)
        {
            adexicr |= R_ADC0_ADEXICR_TSSAD_Msk;
        }
    }

    /* Check if the voltage sensor channel is enabled */
    if (combined_scan_mask & ADC_MASK_VOLT)
    {
        /*sample state registers are set to the calculated value */
        p_instance_ctrl->p_reg->ADSSTRO = (uint8_t) sample_states;
#if BSP_FEATURE_ADC_GROUP_B_SENSORS_ALLOWED
        if (p_channel_cfg->scan_mask & ADC_MASK_VOLT)
        {
            /* Scan the internal reference voltage in normal/group A.  */
            adexicr |= R_ADC0_ADEXICR_OCSA_Msk;
        }
        else
        {
            /* Scan the internal reference voltage in group B.  */
            adexicr |= R_ADC0_ADEXICR_OCSB_Msk;
        }

#else

        /* Scan the internal reference voltage in normal/group A.  */
        adexicr |= R_ADC0_ADEXICR_OCSA_Msk;
#endif

        /* Enable temperature addition mode if configured. */
        if (p_channel_cfg->add_mask & ADC_MASK_VOLT)
        {
            adexicr |= R_ADC0_ADEXICR_OCSAD_Msk;
        }
    }

    p_instance_ctrl->p_reg->ADEXICR = (uint16_t) adexicr;
}

/*******************************************************************************************************************//**
 * This function calculates the sample states value for the internal sensors and returns an error if the calculated
 * value is outside the limit supported by the hardware
 *
 * @param[out] p_sample_states: The calculates sample state count.
 **********************************************************************************************************************/
static void r_adc_sensor_sample_state_calculation (uint32_t * const p_sample_states)
{
    /* Calculate sample state values such that the sample time for the temperature and voltage sensor is the
     * minimum defined by the hardware manual. The minimum is 4.15 microseconds for MF3 devices and
     * 5 microseconds for RV40. The sample states will be calculated to allow sampling for this duration. */

    /* Retrieve the clock source and frequency used by the ADC peripheral and sampling time required for the sensor. */
    uint32_t freq_hz = R_FSP_SystemClockHzGet(BSP_FEATURE_ADC_CLOCK_SOURCE);

    /* Calculate sample states required for the current ADC conversion clock (reference section 47.2.14 "A/D Sampling
     * State Register n (ADSSTRn) (n = 00 to 07, L, T, O)" in the RA6M3 manual R01UH0886EJ0100.
     *
     * sample_states = required_sample_time / adclk_period
     *               = required_sample_time (nsec) * adclk_frequency (kHz) / 1000000 (usec / sec) + 1
     *                 (refactored to avoid overflowing 32 bits, 1 added to round up)
     */
    uint32_t sample_states = ((BSP_FEATURE_ADC_SENSOR_MIN_SAMPLING_TIME * (freq_hz / ADC_PRV_HZ_PER_KHZ)) /
                              ADC_PRV_USEC_PER_SEC) + 1U;

    /* The fastest ADC conversion clock is 60 MHz, and the associated sampling time is 4.15 microseconds.  The number
     * of sample states in this case is 0.00000415 / (1 / 60000000) = 249. This is the maximum number of sample states
     * required for the on chip sensors, so this calculation will never overflow 8 bits (255). */

    /* If sample states are less than the min number of states required, then set them to the minimum. */
    if (sample_states < ADC_SAMPLE_STATE_COUNT_MIN)
    {
        sample_states = ADC_SAMPLE_STATE_COUNT_MIN;
    }

    *p_sample_states = sample_states;
}

#if ADC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * This function does extensive checking on channel mask settings based upon operational mode.
 *
 * @param[in]  p_instance_ctrl         Pointer to instance control block
 * @param[in]  p_channel_cfg           Pointer to channel configuration
 *
 * @retval FSP_SUCCESS                 No configuration errors detected
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_adc_scan_cfg_check (adc_instance_ctrl_t * const     p_instance_ctrl,
                                       adc_channel_cfg_t const * const p_channel_cfg)
{
    fsp_err_t err;
    uint16_t  unit = p_instance_ctrl->p_cfg->unit;

    /* Verify at least one channel is selected for normal / group A. */
    uint32_t valid_channels = g_adc_valid_channels[unit] | ADC_MASK_TEMPERATURE | ADC_MASK_VOLT;
    FSP_ASSERT((0U != p_channel_cfg->scan_mask) && (0U == (p_channel_cfg->scan_mask & (~valid_channels))));

    if (ADC_MODE_GROUP_SCAN == p_instance_ctrl->p_cfg->mode)
    {
        /* Verify at least one channel is selected for group B. */
        FSP_ASSERT((0U != p_channel_cfg->scan_mask_group_b) &&
                   (0U == (p_channel_cfg->scan_mask_group_b & (~valid_channels))));

        /* Cannot have the same channel in both groups. */
        FSP_ASSERT(0 == (p_channel_cfg->scan_mask & p_channel_cfg->scan_mask_group_b));
    }
    else
    {
        /* If group mode is not enabled, no channels can be selected for group B. */
        FSP_ASSERT(ADC_MASK_OFF == p_channel_cfg->scan_mask_group_b);
    }

    /* Verify sensor configuration. */
    err = r_adc_scan_cfg_check_sensors(p_instance_ctrl, p_channel_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Verify that if addition is enabled, then at least one channel is selected. */
    adc_extended_cfg_t const * p_cfg_extend = (adc_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;
    if (ADC_ADD_OFF != p_cfg_extend->add_average_count)
    {
        /* Addition mask should not include bits from inactive channels.
         * This also serves as a check for valid channels in the addition mask */
        uint32_t tmp_mask = p_channel_cfg->scan_mask_group_b | p_channel_cfg->scan_mask;
        FSP_ASSERT((0U == (p_channel_cfg->add_mask & ~tmp_mask)) && (0U != p_channel_cfg->add_mask));
    }
    else
    {
        /* Channels cannot be selected for addition if addition is not used. */
        FSP_ASSERT(ADC_MASK_OFF == p_channel_cfg->add_mask);
    }

    /* Check sample and hold settings. */
    err = r_adc_scan_cfg_check_sample_hold(p_instance_ctrl, p_channel_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check window compare settings. */
    err = r_adc_scan_cfg_check_window_compare(p_channel_cfg->p_window_cfg);

    return err;
}

#endif

/*******************************************************************************************************************//**
 * This function does extensive checking on channel mask settings based upon operational mode. Mask registers are
 * initialized and interrupts enabled in peripheral. Interrupts are also enabled in ICU if corresponding priority
 * is not 0.
 *
 * @param[in]  p_instance_ctrl         Pointer to instance control block
 * @param[in]  p_channel_cfg           Pointer to channel configuration
 **********************************************************************************************************************/
static void r_adc_scan_cfg (adc_instance_ctrl_t * const p_instance_ctrl, adc_channel_cfg_t const * const p_channel_cfg)
{
    /* Set mask for Group A channels. */
    uint32_t scan_mask = p_channel_cfg->scan_mask & ~(uint32_t) ADC_MASK_SENSORS;
    adc_extended_cfg_t const * p_cfg_extend = (adc_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;

    /* Set other channel masks. */
    uint32_t scan_mask_group_b = p_channel_cfg->scan_mask_group_b & ~(uint32_t) ADC_MASK_SENSORS;
    uint32_t add_mask          = p_channel_cfg->add_mask & ~(uint32_t) ADC_MASK_SENSORS;

    p_instance_ctrl->p_reg->ADANSA[0] = (uint16_t) (scan_mask);
    p_instance_ctrl->p_reg->ADANSB[0] = (uint16_t) (scan_mask_group_b);
    p_instance_ctrl->p_reg->ADADS[0]  = (uint16_t) (add_mask);
    p_instance_ctrl->p_reg->ADANSA[1] = (uint16_t) ((scan_mask >> 16));
    p_instance_ctrl->p_reg->ADANSB[1] = (uint16_t) ((scan_mask_group_b >> 16));
    p_instance_ctrl->p_reg->ADADS[1]  = (uint16_t) ((add_mask >> 16));

    /* Configure voltage and/or temperature sensors, if used. */
    r_adc_sensor_cfg(p_instance_ctrl, p_channel_cfg);

#if BSP_FEATURE_ADC_HAS_SAMPLE_HOLD_REG

    /* Configure sample and hold. */
    uint32_t adshcr = p_channel_cfg->sample_hold_states;
    adshcr |= (p_channel_cfg->sample_hold_mask & ADC_MASK_SAMPLE_HOLD_BYPASS_CHANNELS) <<
              ADC_MASK_SAMPLE_HOLD_BYPASS_SHIFT;
    p_instance_ctrl->p_reg->ADSHCR = (uint16_t) adshcr;
#endif

    /* Get window compare configuration */
    adc_window_cfg_t * p_window_cfg = p_channel_cfg->p_window_cfg;

    uint16_t adcmpcr = 0;

    if (p_window_cfg)
    {
        /* Save window compare config */
        adcmpcr = (uint16_t) p_window_cfg->compare_cfg;

        if (p_window_cfg->compare_cfg & R_ADC0_ADCMPCR_CMPAE_Msk)
        {
            /* Set Window A boundary values */
            p_instance_ctrl->p_reg->ADCMPCR  = p_window_cfg->compare_cfg & UINT16_MAX;
            p_instance_ctrl->p_reg->ADCMPDR0 = p_window_cfg->compare_ref_low;
            p_instance_ctrl->p_reg->ADCMPDR1 = p_window_cfg->compare_ref_high;

            /* Set Window A channel mask */
            uint32_t compare_mask = p_window_cfg->compare_mask;
            p_instance_ctrl->p_reg->ADCMPANSR[0] = compare_mask & UINT16_MAX;
            p_instance_ctrl->p_reg->ADCMPANSR[1] = (uint16_t) (((uint32_t) ~ADC_MASK_SENSORS & compare_mask) >> 16);
            p_instance_ctrl->p_reg->ADCMPANSER   =
                (uint8_t) ((ADC_MASK_SENSORS & compare_mask) >> ADC_MASK_FIRST_SENSOR_BIT);

            /* Set Window A channel inequality mode mask */
            uint32_t compare_mode_mask = p_window_cfg->compare_mode_mask;
            p_instance_ctrl->p_reg->ADCMPLR[0] = compare_mode_mask & UINT16_MAX;
            p_instance_ctrl->p_reg->ADCMPLR[1] = (uint16_t) (((uint32_t) ~ADC_MASK_SENSORS & compare_mode_mask) >> 16);
            p_instance_ctrl->p_reg->ADCMPLER   =
                (uint8_t) ((ADC_MASK_SENSORS & compare_mode_mask) >> ADC_MASK_FIRST_SENSOR_BIT);
        }

        if (p_window_cfg->compare_cfg & R_ADC0_ADCMPCR_CMPBE_Msk)
        {
            /* Set Window B channel and mode */
            p_instance_ctrl->p_reg->ADCMPBNSR = (uint8_t) ((adc_window_b_mode_t) p_window_cfg->compare_b_channel |
                                                           p_window_cfg->compare_b_mode);

            /* Set Window B boundary values */
            p_instance_ctrl->p_reg->ADWINLLB = p_window_cfg->compare_b_ref_low;
            p_instance_ctrl->p_reg->ADWINULB = p_window_cfg->compare_b_ref_high;
        }
    }

    /* Set window compare config */
    p_instance_ctrl->p_reg->ADCMPCR = adcmpcr;

    /* Set group A priority action (not interrupt priority!)
     * This will also start the Group B scans if configured for ADC_GROUP_A_GROUP_B_CONTINUOUS_SCAN.
     */
    p_instance_ctrl->p_reg->ADGSPCR = (uint16_t) p_channel_cfg->priority_group_a;

    /* In double-trigger mode set the channel select bits to the highest selected channel number then return. */
    if (ADC_DOUBLE_TRIGGER_DISABLED != p_cfg_extend->double_trigger_mode)
    {
        uint32_t adcsr = p_instance_ctrl->p_reg->ADCSR;
        adcsr = (adcsr & ~R_ADC0_ADCSR_DBLANS_Msk) + (31U - __CLZ(scan_mask));

        p_instance_ctrl->p_reg->ADCSR      = (uint16_t) adcsr;
        p_instance_ctrl->scan_start_adcsr |= (uint16_t) adcsr;
    }

    p_instance_ctrl->initialized = ADC_OPEN;
}

/*******************************************************************************************************************//**
 * Disables and clears context for the requested IRQ.
 *
 * @param[in]  irq        IRQ to enable
 * @param[in]  ipl        Interrupt priority
 * @param[in]  p_context  Pointer to interrupt context
 **********************************************************************************************************************/
static void r_adc_irq_enable (IRQn_Type irq, uint8_t ipl, void * p_context)
{
    if (irq >= 0)
    {
        R_BSP_IrqCfgEnable(irq, ipl, p_context);
    }
}

/*******************************************************************************************************************//**
 * Disables and clears context for the requested IRQ.
 *
 * @param[in]  irq  IRQ to disable
 **********************************************************************************************************************/
static void r_adc_irq_disable (IRQn_Type irq)
{
    if (irq >= 0)
    {
        R_BSP_IrqDisable(irq);
        R_FSP_IsrContextSet(irq, NULL);
    }
}

/*******************************************************************************************************************//**
 * Returns the lowest channel index that is configured  in order to read the results of the configured channels.
 *
 * @param[in]  adc_mask  scan mask of active channels retrieved from the control structure
 *
 * @retval  adc_mask_count  index value of lowest channel
 **********************************************************************************************************************/
static uint32_t r_adc_lowest_channel_get (uint32_t adc_mask)
{
    /* Initialize the mask result */
    uint32_t adc_mask_result = 0U;
    int32_t  adc_mask_count  = -1;
    while (0U == adc_mask_result)
    {
        /* Increment channel until a channel is found in the mask. */
        adc_mask_count++;
        adc_mask_result = (uint32_t) (adc_mask & (1U << adc_mask_count));
    }

    return (uint32_t) adc_mask_count;
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to ADC instance control block
 * @param[in]     p_args     Pointer to arguments on stack
 **********************************************************************************************************************/
static void r_adc_call_callback (adc_instance_ctrl_t * p_ctrl, adc_callback_args_t * p_args)
{
    adc_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    adc_callback_args_t * p_args_memory = p_ctrl->p_callback_memory;
    if (NULL == p_args_memory)
    {
        /* Use provided args struct on stack */
        p_args_memory = p_args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args_memory;

        /* Copy the stacked args to callback memory */
        *p_args_memory = *p_args;
    }

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args_memory);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        adc_prv_ns_callback p_callback = (adc_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args_memory);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args_memory);
#endif

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * Clears interrupt flag and calls a callback to notify application of the event.
 *
 * @param[in]  event                   Event that triggered the ISR
 **********************************************************************************************************************/
static void r_adc_scan_end_common_isr (adc_event_t event)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    adc_instance_ctrl_t * p_instance_ctrl = (adc_instance_ctrl_t *) R_FSP_IsrContextGet(R_FSP_CurrentIrqGet());

    /* Clear the BSP IRQ Flag     */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    adc_callback_args_t args;
    args.event = event;
#if BSP_FEATURE_ADC_CALIBRATION_REG_AVAILABLE

    /* Store the correct event into the callback argument */
    if (ADC_ADICR_CALIBRATION_INTERRUPT_DISABLED != p_instance_ctrl->p_reg->ADICR)
    {
        args.event = ADC_EVENT_CALIBRATION_COMPLETE;

        /* Restore the interrupt source to disable interrupts after calibration is done. */
        p_instance_ctrl->p_reg->ADICR = 0U;
    }
#endif

    /* Store the unit number into the callback argument */
    args.unit = p_instance_ctrl->p_cfg->unit;

    /* Initialize the channel to 0.  It is not used in this implementation. */
    args.channel = ADC_CHANNEL_0;

    /* Populate the context field. */
    args.p_context = p_instance_ctrl->p_context;

    /* If a callback was provided, call it with the argument */
    if (NULL != p_instance_ctrl->p_callback)
    {
        r_adc_call_callback(p_instance_ctrl, &args);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * This function implements the unit 0 interrupt handler for normal/Group A/double trigger scan complete.
 **********************************************************************************************************************/
void adc_scan_end_isr (void)
{
    r_adc_scan_end_common_isr(ADC_EVENT_SCAN_COMPLETE);
}

/*******************************************************************************************************************//**
 * This function implements the interrupt handler for Group B scan complete.
 **********************************************************************************************************************/
void adc_scan_end_b_isr (void)
{
    r_adc_scan_end_common_isr(ADC_EVENT_SCAN_COMPLETE_GROUP_B);
}

/*******************************************************************************************************************//**
 * This function implements the interrupt handler for window compare events.
 **********************************************************************************************************************/
void adc_window_compare_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    adc_instance_ctrl_t * p_instance_ctrl = (adc_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    adc_extended_cfg_t  * p_extend        = (adc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    adc_callback_args_t args;
    args.event = (irq == p_extend->window_a_irq) ? ADC_EVENT_WINDOW_COMPARE_A : ADC_EVENT_WINDOW_COMPARE_B;

    /* Store the unit number into the callback argument */
    args.unit = p_instance_ctrl->p_cfg->unit;

    if (ADC_EVENT_WINDOW_COMPARE_A == args.event)
    {
        args.channel = (adc_channel_t) 0;

        R_ADC0_Type * p_reg = p_instance_ctrl->p_reg;

        /* Get all Window A status registers */
        uint16_t adcmpsr0 = p_reg->ADCMPSR[0];
        uint16_t adcmpsr1 = p_reg->ADCMPSR[1];
        uint8_t  adcmpser = p_reg->ADCMPSER;

        /* Get the lowest channel that meets Window A criteria */
        uint32_t lowest_channel = __CLZ(__RBIT(adcmpsr0 + (uint32_t) (adcmpsr1 << 16) + (uint32_t) (adcmpser << 29)));

        /* Clear the status flag corresponding to the lowest channel */
        if (lowest_channel < 16)
        {
            p_reg->ADCMPSR[0] = (uint16_t) (adcmpsr0 & ~(1 << (lowest_channel & 0xF)));
        }
        else if (lowest_channel < 29)
        {
            p_reg->ADCMPSR[1] = (uint16_t) (adcmpsr1 & ~(1 << (lowest_channel & 0xF)));
        }
        else
        {
            p_reg->ADCMPSER = (uint8_t) (adcmpser & ~(lowest_channel & 0x3));
        }

        args.channel = (adc_channel_t) lowest_channel;

        if (args.channel > 29)
        {
            /* Adjust sensor channels to align with the adc_channel_t enumeration */
            args.channel = (adc_channel_t) (ADC_CHANNEL_TEMPERATURE + (args.channel - 29));
        }
    }
    else
    {
        /* Get channel selected for Window B */
        args.channel = (adc_channel_t) p_instance_ctrl->p_reg->ADCMPBNSR_b.CMPCHB;

        if (args.channel > 31)
        {
            /* Adjust sensor channels to align with the adc_channel_t enumeration */
            args.channel = (adc_channel_t) (ADC_CHANNEL_TEMPERATURE + (args.channel & 0xF));
        }

        /* Clear IRQ */
        p_instance_ctrl->p_reg->ADCMPBSR_b.CMPSTB = 0;
    }

    /* Populate the context field. */
    args.p_context = p_instance_ctrl->p_context;

    /* If a callback was provided, call it with the argument */
    if (NULL != p_instance_ctrl->p_callback)
    {
        r_adc_call_callback(p_instance_ctrl, &args);
    }

    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
