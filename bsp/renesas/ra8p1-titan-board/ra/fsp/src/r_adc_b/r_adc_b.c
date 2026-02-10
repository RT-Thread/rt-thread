/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include "r_adc_b_cfg.h"
#include "r_adc_b.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define ADC_B_OPEN                                (0x41444348) /* ADC_B in ascii */
#define ADC_B_CHANNEL_IS_EXTERNAL(channel)      (ADC_CHANNEL_LAST_EXTERNAL >= channel)
#define ADC_B_CHANNEL_IS_INTERNAL(channel)      ((ADC_CHANNEL_FIRST_INTERNAL <= channel) && \
                                                 (ADC_CHANNEL_LAST_INTERNAL >= channel))

#define ADC_B_FIFO_STAGE_COUNT                    (8)
#define ADC_B_GROUP_MASK_5678                     (adc_group_mask_t) (ADC_GROUP_MASK_5 | ADC_GROUP_MASK_6 | \
                                                                      ADC_GROUP_MASK_7 | ADC_GROUP_MASK_8)
#define ADC_B_REG_ADDRESS(base, idx, offset)    ((uint32_t *) (((uint8_t *) &base) + ((uint32_t) offset) * (idx)))

#define ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_012       (ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_0 | \
                                                   ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_1 | \
                                                   ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_2)
#define ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_456       (ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_4 | \
                                                   ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_5 | \
                                                   ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_6)
#if BSP_FEATURE_ADC_B_PGA_SUPPORTED
 #define ADC_B_PGA_INVALID_GAIN                   (0xF)
#endif

#define R_ADC_B_ADCALSTR_ADC_0_CAL_Msk            (0x01UL)
#define R_ADC_B_ADCALSTR_GAIN_OFFSET_0_CAL_Msk    (0x02UL)
#define R_ADC_B_ADCALSTR_SAMPLE_HOLD_0_CAL_Msk    (0x04UL)
#define R_ADC_B_ADCALSTR_ADC_1_CAL_Msk            (0x100UL)
#define R_ADC_B_ADCALSTR_GAIN_OFFSET_1_CAL_Msk    (0x200UL)
#define R_ADC_B_ADCALSTR_SAMPLE_HOLD_1_CAL_Msk    (0x400UL)

#define R_ADC_B_ADGSPCR_GRP_PRI_CTRL_123_Msk      (0x7)
#define R_ADC_B_ADGSPCR_GRP_PRI_CTRL_4_Msk        (0x8)

#define ADC_B_PCR_PRKEY                           (0xA500U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * adc_b_prv_ns_callback)(adc_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile adc_b_prv_ns_callback)(adc_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
static void adc_b_call_callback(adc_b_instance_ctrl_t * p_ctrl, adc_callback_args_t * p_args);
static void adc_b_disable_interrupts(adc_b_instance_ctrl_t * p_instance_ctrl);
static void adc_b_enable_interrupts(adc_b_instance_ctrl_t * p_instance_ctrl);

#if BSP_FEATURE_ADC_B_PGA_SUPPORTED
static void adc_b_open_pga(adc_b_extended_cfg_t * p_extend);

#endif
static void      adc_b_calculate_wait_time(adc_b_instance_ctrl_t * p_instance_ctrl, adc_b_scan_cfg_t * p_scan_data);
static uint32_t  adc_b_update_calibrate_state(adc_b_instance_ctrl_t * p_instance_ctrl);
static void      adc_b_force_stop(adc_b_instance_ctrl_t * p_instance_ctrl);
static void      adc_b_isr_enable(adc_b_instance_ctrl_t * p_instance_ctrl, IRQn_Type irq, uint8_t ipl);
static IRQn_Type adc_b_isr_handler(adc_event_t          event,
                                   adc_group_mask_t     group_mask,
                                   adc_b_channel_mask_t channel_mask,
                                   adc_b_unit_mask_t    unit);

#if (ADC_B_CFG_PARAM_CHECKING_ENABLE)
static bool adc_channel_is_sample_hold_enabled(adc_channel_t channel, uint8_t sample_and_hold_enable_mask);

#endif

/***********************************************************************************************************************
 * Interrupt Service Routines
 **********************************************************************************************************************/
void adc_b_calend0_isr(void);
void adc_b_calend1_isr(void);
void adc_b_limclpi_isr(void);
void adc_b_err0_isr(void);
void adc_b_err1_isr(void);
void adc_b_resovf0_isr(void);
void adc_b_resovf1_isr(void);
void adc_b_adi0_isr(void);
void adc_b_adi1_isr(void);
void adc_b_adi2_isr(void);
void adc_b_adi3_isr(void);
void adc_b_adi4_isr(void);
void adc_b_adi5_isr(void);
void adc_b_adi6_isr(void);
void adc_b_adi7_isr(void);
void adc_b_adi8_isr(void);
void adc_b_adi5678_isr(void);
void adc_b_fifoovf_isr(void);
void adc_b_fiforeq0_isr(void);
void adc_b_fiforeq1_isr(void);
void adc_b_fiforeq2_isr(void);
void adc_b_fiforeq3_isr(void);
void adc_b_fiforeq4_isr(void);
void adc_b_fiforeq5_isr(void);
void adc_b_fiforeq6_isr(void);
void adc_b_fiforeq7_isr(void);
void adc_b_fiforeq8_isr(void);
void adc_b_fiforeq5678_isr(void);

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** ADC_B Implementation of ADC. */
const adc_api_t g_adc_on_adc_b =
{
    .open           = R_ADC_B_Open,
    .scanCfg        = R_ADC_B_ScanCfg,
    .infoGet        = R_ADC_B_InfoGet,
    .scanStart      = R_ADC_B_ScanStart,
    .scanGroupStart = R_ADC_B_ScanGroupStart,
    .scanStop       = R_ADC_B_ScanStop,
    .scanStatusGet  = R_ADC_B_StatusGet,
    .read           = R_ADC_B_Read,
    .read32         = R_ADC_B_Read32,
    .close          = R_ADC_B_Close,
    .calibrate      = R_ADC_B_Calibrate,
    .offsetSet      = R_ADC_B_OffsetSet,
    .callbackSet    = R_ADC_B_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup ADC_B
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Sets the operational mode, trigger sources, interrupt priority, and configurations for the peripheral as a whole.
 * If provided, the function registers a callback function pointer for notifying the user whenever a scan has completed,
 * error has occurred, FIFO read request is generated, or other ADC interrupt event occurrs.
 * Implements @ref adc_api_t::open.
 *
 * @retval FSP_SUCCESS              Module is ready for use.
 * @retval FSP_ERR_ASSERTION        An input argument is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     The instance control structure has already been opened.
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_Open (adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg)
{
    adc_b_instance_ctrl_t * p_instance_ctrl = (adc_b_instance_ctrl_t *) p_ctrl;
    uint32_t                adgspcr_value   = 0;
#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(ADC_B_OPEN != p_instance_ctrl->opened, FSP_ERR_ALREADY_OPEN);
#endif

    /* Save configurations. */
    p_instance_ctrl->p_cfg             = p_cfg;
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;
    p_instance_ctrl->adc_state         = ADC_B_CONVERTER_STATE_NONE;

    adc_b_extended_cfg_t * p_extend = (adc_b_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Module Stop release: ADC */
    R_BSP_MODULE_START(FSP_IP_ADC, 0);

    if (ADC_B_CLOCK_SOURCE_GPT == p_extend->clock_control_bits.source_selection)
    {
        R_BSP_MODULE_START(FSP_IP_GPT, 0);
    }

    /*  Set synchronous operation period and Enable/Disable for ADC 0/1 */
    R_ADC_B->ADSYCR = p_extend->sync_operation_control;

    /* Configure the ADC clock. See Step 4 of "Initial setup procedure" in the A/D Converter section of the relevant hardware manual */
    R_ADC_B->ADCLKENR = 0x00;
    FSP_HARDWARE_REGISTER_WAIT(R_ADC_B->ADCLKSR, 0x00);
    R_ADC_B->ADCLKCR  = p_extend->clock_control_data;
    R_ADC_B->ADCLKENR = 0x01;
    FSP_HARDWARE_REGISTER_WAIT(R_ADC_B->ADCLKSR, 0x01);

    /* Set ADC unit scan modes
     *  - ADC Converter Background Continuous Mode only valid for Hybrid mode */
#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_extend->adc_b_converter_mode[0].mode != ADC_B_CONVERTER_MODE_BACKGROUND_SCAN ||
               p_extend->adc_b_converter_mode[0].method == ADC_B_CONVERSION_METHOD_HYBRID);
    FSP_ASSERT(p_extend->adc_b_converter_mode[1].mode != ADC_B_CONVERTER_MODE_BACKGROUND_SCAN ||
               p_extend->adc_b_converter_mode[1].method == ADC_B_CONVERSION_METHOD_HYBRID);
#endif
    R_ADC_B->ADMDR = p_extend->adc_b_mode;

    /* Configure Group Scan Priority for units 0 and 1 */
    for (uint8_t i = 0; i < 2; i++)
    {
        if (ADC_B_CONVERSION_METHOD_SAR == p_extend->adc_b_converter_mode[i].method)
        {
            /* PGS, RSCN and LGRRS bit are set 1 in SAR mode. */
            adgspcr_value |= (uint32_t) R_ADC_B_ADGSPCR_GRP_PRI_CTRL_123_Msk << (i * 8);
            if (ADC_B_CONVERTER_MODE_CONTINUOUS_SCAN == p_extend->adc_b_converter_mode[i].mode)
            {
                /* GRP bit is set 1 in Continuous Scan mode. */
                adgspcr_value |= (uint32_t) R_ADC_B_ADGSPCR_GRP_PRI_CTRL_4_Msk << (i * 8);
            }
        }
    }

    R_ADC_B->ADGSPCR = adgspcr_value;

    /* Configure A/D conversion state */
    R_ADC_B->ADCNVSTR = p_extend->conversion_state;
    R_ADC_B->ADSHCR0  = p_extend->sample_and_hold_enable_mask & ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_012;
    R_ADC_B->ADSHCR1  = (p_extend->sample_and_hold_enable_mask & ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_456) >> 4;
    R_ADC_B->ADSHSTR0 = p_extend->sample_and_hold_config_012;
    R_ADC_B->ADSHSTR1 = p_extend->sample_and_hold_config_456;

    /* Configure Digital filters */
    R_ADC_B->ADDFSR0 = p_extend->adc_filter_selection[0].bits;
    R_ADC_B->ADDFSR1 = p_extend->adc_filter_selection[1].bits;

#if BSP_FEATURE_ADC_B_PGA_SUPPORTED
    adc_b_open_pga(p_extend);
#endif

    /* Set ADC calibration sampling and conversion times */
    R_ADC_B->ADCALSTCR = p_extend->calibration_adc_state;

    /* Set Sample and Hold calibration sampling and hold times */
    R_ADC_B->ADCALSHCR = p_extend->calibration_sample_and_hold;

    /* Set user offset, user gain and limiter clip tables */
    for (uint8_t i = 0; i < 8; i++)
    {
        *ADC_B_REG_ADDRESS(R_ADC_B->ADUOFTR0, i, 0x4) = (uint32_t) p_extend->user_offset_tables[i];
        *ADC_B_REG_ADDRESS(R_ADC_B->ADUGTR0, i, 0x4)  = p_extend->user_gain_tables[i];
        *ADC_B_REG_ADDRESS(R_ADC_B->ADLIMTR0, i, 0x4) = p_extend->limiter_clip_tables[i];
    }

    /* Enable interrupts for Limiter clipping, if desired */
    R_ADC_B->ADLIMINTCR = p_extend->limiter_clip_interrupt_enable_mask;

    /* Disable compare match functionality */
    R_ADC_B->ADCMPENR = 0;

    /* Disable compare match interrupts */
    R_ADC_B->ADCMPINTCR = 0;

    /* Do not use compare match tables */
    R_ADC_B->ADCCMPCR0 = 0;
    R_ADC_B->ADCCMPCR1 = 0;

    /* Set FIFO configuration */
    R_ADC_B->ADFIFOCR     = p_extend->fifo_enable_mask;
    R_ADC_B->ADFIFOINTCR  = p_extend->fifo_interrupt_enable_mask;
    R_ADC_B->ADFIFOINTLR0 = p_extend->fifo_interrupt_level0;
    R_ADC_B->ADFIFOINTLR1 = p_extend->fifo_interrupt_level1;
    R_ADC_B->ADFIFOINTLR2 = p_extend->fifo_interrupt_level2;
    R_ADC_B->ADFIFOINTLR3 = p_extend->fifo_interrupt_level3;
    R_ADC_B->ADFIFOINTLR4 = p_extend->fifo_interrupt_level4;

    /* Clear FIFO registers */
    R_ADC_B->ADFIFODCR = R_ADC_B0_ADFIFODCR_FIFODCn_Msk;

    /* Configure interrupts for application use */
    adc_b_enable_interrupts(p_instance_ctrl);

    /* Enable Calibration Request / End Interrupts */
    R_ADC_B->ADCALINTCR = R_ADC_B0_ADCALINTCR_CALENDIE0_Msk | R_ADC_B0_ADCALINTCR_CALENDIE1_Msk;

    /* Enable converter error interrupts */
    R_ADC_B->ADERINTCR = R_ADC_B0_ADERINTCR_ADEIE0_Msk | R_ADC_B0_ADERINTCR_ADEIE1_Msk;

    /* Enable overflow Interrupts */
    R_ADC_B->ADOVFINTCR = R_ADC_B0_ADOVFINTCR_ADOVFIE0_Msk | R_ADC_B0_ADOVFINTCR_ADOVFIE1_Msk;

    /* Mark driver as opened */
    p_instance_ctrl->opened = ADC_B_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures the ADC_B scan parameters. Channel specific settings are set in this function. Pass a pointer to
 * @ref adc_b_scan_cfg_t to p_channel_cfg.
 * Implements @ref adc_api_t::scanCfg.
 *
 * @note This starts group B scans if adc_b_scan_cfg_t::priority_group_a is set to ADC_B_GROUP_A_GROUP_B_CONTINUOUS_SCAN.
 *
 * @retval FSP_SUCCESS                 Channel specific settings applied.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_INVALID_STATE       Invalid Scan Configuration.
 * @retval FSP_ERR_INVALID_CHANNEL     Invalid configured channel for group converter id.
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_ScanCfg (adc_ctrl_t * p_ctrl, void const * const p_scan_cfg)
{
    adc_b_scan_cfg_t      * p_scan_data               = (adc_b_scan_cfg_t *) p_scan_cfg;
    adc_b_instance_ctrl_t * p_instance_ctrl           = (adc_b_instance_ctrl_t *) p_ctrl;
    uint32_t                scan_group_enable_mask    = 0;
    uint32_t                scan_group_end_interrupts = 0;

#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_scan_cfg);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    adc_b_extended_cfg_t * p_extend = (adc_b_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Clear any previous channel configuration, specifically group selections */
    p_instance_ctrl->adc_state = ADC_B_CONVERTER_STATE_NONE;
    for (uint8_t channel = 0; channel < ADC_B_VIRTUAL_CHANNEL_COUNT; channel++)
    {
        *ADC_B_REG_ADDRESS(R_ADC_B->ADCHCR0, channel, 0x10) = 0;
    }

    /* Assign scan groups to selected converters */
    R_ADC_B->ADSGCR0 = p_extend->converter_selection_0;
    R_ADC_B->ADSGCR1 = p_extend->converter_selection_1;
    R_ADC_B->ADSGCR2 = p_extend->converter_selection_2;

    /* Configure start trigger delay */
    R_ADC_B->ADTRGDLR0 = p_extend->start_trigger_delay_0;
    R_ADC_B->ADTRGDLR1 = p_extend->start_trigger_delay_1;
    R_ADC_B->ADTRGDLR2 = p_extend->start_trigger_delay_2;
    R_ADC_B->ADTRGDLR3 = p_extend->start_trigger_delay_3;
    R_ADC_B->ADTRGDLR4 = p_extend->start_trigger_delay_4;

    /* Configure sampling state tables */
    for (uint8_t i = 0; i < 8; i++)
    {
        *ADC_B_REG_ADDRESS(R_ADC_B->ADSSTR0, i, 0x4) = p_extend->sampling_state_tables[i];
    }

#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    uint32_t adsycyc = (p_extend->sync_operation_control & R_ADC_B0_ADSYCR_ADSYCYC_Msk) >>
                       R_ADC_B0_ADSYCR_ADSYCYC_Pos;
    uint32_t adcnvstr = p_extend->conversion_state;
    uint32_t cst0     = (adcnvstr & R_ADC_B0_ADCNVSTR_CST0_Msk) >> R_ADC_B0_ADCNVSTR_CST0_Pos;
    uint32_t cst1     = (adcnvstr & R_ADC_B0_ADCNVSTR_CST1_Msk) >> R_ADC_B0_ADCNVSTR_CST1_Pos;

    /*============================================================================================================
     *  Constraints to check while Synchronous Mode is enabled
     *   - See "Restrictions on Synchronous Operation", in the A/D converter section of the relevant hardware manual
     *============================================================================================================*/
    bool sync_operation_enabled = !p_extend->sync_operation_control_bits.adc_0_disable_sync ||
                                  !p_extend->sync_operation_control_bits.adc_1_disable_sync;
    if (sync_operation_enabled)
    {
        /* Set the Synchronous Operation Period to a value larger than successive approximation time at Self-Calibration. */
        uint32_t caladcst = (p_extend->calibration_adc_state & R_ADC_B0_ADCALSTCR_CALADCST_Msk) >>
                            R_ADC_B0_ADCALSTCR_CALADCST_Pos;
        FSP_ERROR_RETURN(adsycyc >= caladcst, FSP_ERR_INVALID_STATE);

        /* Set the sampling time and successive approximation time at Self-Calibration to be integral multiples of the Synchronous Operation Period. */
        uint32_t caladsst = (p_extend->calibration_adc_state & R_ADC_B0_ADCALSTCR_CALADSST_Msk) >>
                            R_ADC_B0_ADCALSTCR_CALADSST_Pos;
        FSP_ERROR_RETURN((caladsst + caladcst) % adsycyc == 0, FSP_ERR_INVALID_STATE);
    }
#endif
    p_instance_ctrl->cached_adsystr  = ADC_GROUP_MASK_NONE;
    p_instance_ctrl->cached_adtrgenr = ADC_GROUP_MASK_NONE;

    for (uint8_t group = 0; group < p_scan_data->group_count; group++)
    {
        const adc_b_group_cfg_t * p_adc_group = p_scan_data->p_adc_groups[group];
#if ADC_B_CFG_PARAM_CHECKING_ENABLE

        /*============================================================================================================
         *  Constraints to check while Synchronous Mode is enabled
         *   - See "Restrictions on Synchronous Operation", in the A/D converter section of the relevant hardware manual
         *============================================================================================================*/
        adc_b_unit_id_t converter_selection = p_adc_group->converter_selection;
        uint32_t        cst                 = (converter_selection ? cst0 : cst1);
        if (sync_operation_enabled)
        {
            /* Set the Synchronous Operation Period to a value larger than successive approximation time of ADCm (m = 0, 1) */
            FSP_ERROR_RETURN(adsycyc >= cst + 1, FSP_ERR_INVALID_STATE);
        }
#endif
        adc_group_mask_t adc_group_mask = (adc_group_mask_t) (1 << p_adc_group->scan_group_id);
        scan_group_enable_mask    |= (uint32_t) adc_group_mask;
        scan_group_end_interrupts |= (uint32_t) (p_adc_group->scan_end_interrupt_enable << p_adc_group->scan_group_id);

        if (p_adc_group->external_trigger_enable_mask ||
            p_adc_group->elc_trigger_enable_mask ||
            p_adc_group->gpt_trigger_enable_mask)
        {
            p_instance_ctrl->cached_adtrgenr |= adc_group_mask;
        }
        else
        {
            p_instance_ctrl->cached_adsystr |= adc_group_mask;
        }

        /* Configure External Triggers, ELC Triggers, GPT Triggers, Self-diagnosis / Disconnect detect */
        *ADC_B_REG_ADDRESS(R_ADC_B->ADTRGEXT0, p_adc_group->scan_group_id,
                           0x10) = p_adc_group->external_trigger_enable_mask;
        *ADC_B_REG_ADDRESS(R_ADC_B->ADTRGELC0, p_adc_group->scan_group_id, 0x10) = p_adc_group->elc_trigger_enable_mask;
        *ADC_B_REG_ADDRESS(R_ADC_B->ADTRGGPT0, p_adc_group->scan_group_id, 0x10) = p_adc_group->gpt_trigger_enable_mask;
        *ADC_B_REG_ADDRESS(R_ADC_B->ADSGDCR0, p_adc_group->scan_group_id, 0x04)  = p_adc_group->self_diagnosis_mask;

        for (uint8_t channel = 0; channel < p_adc_group->virtual_channel_count; channel++)
        {
            adc_b_virtual_channel_cfg_t * p_virtual_channel_cfg = p_adc_group->p_virtual_channels[channel];
            adc_b_virtual_channel_t       virtual_channel_id    = p_virtual_channel_cfg->channel_id;
#if ADC_B_CFG_PARAM_CHECKING_ENABLE

            /* Check that channel is valid for configured unit */
            adc_channel_t        channel_id    = (adc_channel_t) p_virtual_channel_cfg->channel_cfg_bits.channel;
            adc_b_channel_mask_t extended_mask =
                (adc_b_channel_mask_t) (1ULL <<
                                        (channel_id - ADC_CHANNEL_FIRST_INTERNAL + ADC_B_CHANNEL_MASK_EXT_OFFSET));
            adc_b_channel_mask_t physical_mask = (adc_b_channel_mask_t) (1 << channel_id);
            adc_b_channel_mask_t channel_mask  =
                (channel_id > ADC_CHANNEL_LAST_EXTERNAL) ? extended_mask : physical_mask;
            FSP_ERROR_RETURN(ADC_B_CHANNEL_VALID_FOR_UNIT(channel_mask, converter_selection), FSP_ERR_INVALID_CHANNEL);

            /* Check synchronous operation */
            if (sync_operation_enabled)
            {
                /* Set so that the sum of the sampling times of the analog channels and successive approximation time of ADCm (m = 0, 1) is an integral multiple of the Synchronous Operation Period */
                uint16_t sst = p_extend->sampling_state_table[virtual_channel_id];
                FSP_ERROR_RETURN((sst + cst) % adsycyc == 0, FSP_ERR_INVALID_STATE);

                /*============================================================================================================
                 * Constraints to check while Synchronous Mode is enabled and Sample and Hold is enabled
                 *   - See "Restrictions on Synchronous Operation", in the A/D converter section of the relevant hardware manual
                 *============================================================================================================*/
                adc_channel_t an_channel_id = (adc_channel_t) p_virtual_channel_cfg->channel_cfg_bits.channel;
                if (adc_channel_is_sample_hold_enabled(an_channel_id, p_extend->sample_and_hold_enable_mask))
                {
                    uint32_t config_012 = p_extend->sample_and_hold_config_012;
                    uint32_t config_456 = p_extend->sample_and_hold_config_456;

                    uint32_t shsst_012 = (config_012 & R_ADC_B0_ADSHSTR0_SHSST_Msk) >> R_ADC_B0_ADSHSTR0_SHSST_Pos;
                    uint32_t shsst_456 = (config_456 & R_ADC_B0_ADSHSTR1_SHSST_Msk) >> R_ADC_B0_ADSHSTR1_SHSST_Pos;
                    uint32_t shsst     = (an_channel_id / 6) ? shsst_456 : shsst_012;

                    uint32_t shhst_012 = (config_012 & R_ADC_B0_ADSHSTR0_SHHST_Msk) >> R_ADC_B0_ADSHSTR0_SHHST_Pos;
                    uint32_t shhst_456 = (config_456 & R_ADC_B0_ADSHSTR1_SHHST_Msk) >> R_ADC_B0_ADSHSTR1_SHHST_Pos;
                    uint32_t shhst     = (an_channel_id / 6) ? shhst_456 : shhst_012;

                    /* Set the Synchronous Operation Period to a value greater than the hold mode switching time of Channel-dedicated sample-and-hold circuit. */
                    FSP_ERROR_RETURN(adsycyc >= shhst, FSP_ERR_INVALID_STATE);

                    /* Set the sum of the sampling time and the hold time of the channel-dedicated sample-and-hold circuit to be an integer multiple of the A/D conversion synchronous period. */
                    FSP_ERROR_RETURN((shsst + shhst) % adsycyc == 0, FSP_ERR_INVALID_STATE);

                    /* Set the hold time of the channel-dedicated sample-and-hold circuits to be the same as the successive conversion time of the A/D converter Unit m (m=0, 1). */
                    FSP_ERROR_RETURN(shhst == cst, FSP_ERR_INVALID_STATE);

                    /* Set the A/D conversion synchronization cycle to a value larger than the hold time in the calibration operation of the channel-dedicated sample-and-hold circuit. */
                    uint32_t adcalshcr = p_extend->calibration_sample_and_hold;
                    uint8_t  calshhst  = (adcalshcr & R_ADC_B0_ADCALSHCR_CALSHHST_Msk) >>
                                         R_ADC_B0_ADCALSHCR_CALSHHST_Pos;
                    FSP_ERROR_RETURN(adsycyc >= calshhst, FSP_ERR_INVALID_STATE);

                    /* Set the sum of the sampling time and the hold time of the channel-dedicated sample-and-hold circuit in calibration operation to be an integer multiple of the A/D conversion synchronous period. */
                    uint8_t calshsst = (adcalshcr & R_ADC_B0_ADCALSHCR_CALSHSST_Msk) >>
                                       R_ADC_B0_ADCALSHCR_CALSHSST_Pos;
                    FSP_ERROR_RETURN(calshsst + calshhst == adsycyc, FSP_ERR_INVALID_STATE);
                }
            }
#endif

            /* Configure Virtual Channels, Gain/Offset tables, Add/Avg and Compare, Limit Clip Tbl / Data format */
            *ADC_B_REG_ADDRESS(R_ADC_B->ADCHCR0, virtual_channel_id, 0x10)   = p_virtual_channel_cfg->channel_cfg;
            *ADC_B_REG_ADDRESS(R_ADC_B->ADDOPCRA0, virtual_channel_id, 0x10) = p_virtual_channel_cfg->channel_control_a;
            *ADC_B_REG_ADDRESS(R_ADC_B->ADDOPCRB0, virtual_channel_id, 0x10) = p_virtual_channel_cfg->channel_control_b;
            *ADC_B_REG_ADDRESS(R_ADC_B->ADDOPCRC0, virtual_channel_id, 0x10) = p_virtual_channel_cfg->channel_control_c;

            /* Enable temperature sensor if configured. */
            uint32_t channel_selection = (p_virtual_channel_cfg->channel_cfg & R_ADC_B0_ADCHCR0_CNVCS_Msk) >>
                                         R_ADC_B0_ADCHCR0_CNVCS_Pos;
            switch (channel_selection)
            {
                case ADC_CHANNEL_TEMPERATURE:
                {
                    if (!R_TSN_CTRL->TSCR_b.TSEN)
                    {
                        R_BSP_MODULE_START(FSP_IP_TSN, 0);
#if defined(R_SYSTEM_TEMPRCR_TSNKEEP_Msk)

                        /* Follow procedure listed in Figure "Setting procedure for temperature monitor sensor" in the Resets section of the relevant hardware manual
                         *  - TEMPRLR accepts only accepts write-access twice per reset. This is currently its only use. New use will require re-evaluation of design. */
                        if (!R_SYSTEM->TEMPRCR_b.TSNKEEP)
                        {
                            R_SYSTEM->PRCR              = (ADC_B_PCR_PRKEY | R_SYSTEM_PRCR_PRC5_Msk); // Enable TEMPRLR and TEMPRCR
                            R_SYSTEM->TEMPRLR_b.LOCK    = 0;                                          // Unlock TEMPRCR
                            R_SYSTEM->TEMPRCR_b.TSNKEEP = 1;                                          // Enable TSN
                            R_SYSTEM->TEMPRLR_b.LOCK    = 1;                                          // Lock TEMPRCR
                            R_SYSTEM->PRCR              = (ADC_B_PCR_PRKEY);                          // Disable TEMPRLR and TEMPRCR
                        }
#endif
                        R_TSN_CTRL->TSCR_b.TSEN = 1;
                        R_BSP_SoftwareDelay(30, BSP_DELAY_UNITS_MICROSECONDS);                        // Wait for stabilization. See "Procedure example for using the TSN" in the TSN section of the relevant hardware manual.

                        R_TSN_CTRL->TSCR_b.TSOE = 1;
                    }

                    break;
                }

                case ADC_CHANNEL_VOLT:
                {
                    /* Enable internal reference voltage */
                    R_ADC_B->ADREFCR = 0x01;
                    break;
                }

                default:
                {
                    break;
                }
            }
        }
    }

    /* Recalculate ADC Stop wait time */
    adc_b_calculate_wait_time(p_instance_ctrl, p_scan_data);

    /* Enable/Disable scan groups according to configuration */
    R_ADC_B->ADSGER = scan_group_enable_mask;

    /* Configure scan end interrupts */
    R_ADC_B->ADINTCR = scan_group_end_interrupts;

    /* Mark driver as opened */
    p_instance_ctrl->initialized = ADC_B_OPEN;

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements @ref adc_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_CallbackSet (adc_ctrl_t * const          p_api_ctrl,
                               void (                    * p_callback)(adc_callback_args_t *),
                               void * const                p_context,
                               adc_callback_args_t * const p_callback_memory)
{
    adc_b_instance_ctrl_t * p_ctrl = (adc_b_instance_ctrl_t *) p_api_ctrl;

#if (ADC_B_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if ADC_B_CFG_PARAM_CHECKING_ENABLE

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
 * Enables the hardware trigger for a scan depending on how the triggers were configured in the R_ADC_B_ScanCfg call.
 * If the unit was configured for ELC, GPT, or external hardware triggering, then this function allows the trigger
 * signal to get to the ADC unit. The function is not able to control the generation of the trigger itself.
 * If the unit was configured for software triggering, This function was added to this ADC version for compatibility
 * with r_adc driver. For additional flexibility, it is recommended to use R_ADC_B_ScanGroupStart.
 *
 * @pre Call R_ADC_B_ScanCfg after R_ADC_B_Open before starting a scan.
 * @pre Call R_ADC_B_Calibrate and wait for calibration to complete before starting a scan.
 *
 * @retval FSP_SUCCESS                 Scan started (software trigger) or hardware triggers enabled.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_INVALID_ARGUMENT    No hardware triggers configured for groups.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit not initialized.
 * @retval FSP_ERR_INVALID_STATE       Calibration required.
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_ScanStart (adc_ctrl_t * p_ctrl)
{
    adc_b_instance_ctrl_t * p_instance_ctrl = (adc_b_instance_ctrl_t *) p_ctrl;
#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);

    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);

    adc_group_mask_t configured_channels =
        (adc_group_mask_t) (p_instance_ctrl->cached_adtrgenr | p_instance_ctrl->cached_adsystr);
    FSP_ERROR_RETURN(configured_channels, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((ADC_B_CONVERTER_STATE_READY == p_instance_ctrl->adc_state), FSP_ERR_INVALID_STATE);
#endif

    R_ADC_B->ADTRGENR = p_instance_ctrl->cached_adtrgenr;
    R_ADC_B->ADSYSTR  = p_instance_ctrl->cached_adsystr;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts a software scan or enables the hardware trigger for a scan depending on how triggers were configured. If the
 * group was configured for ELC, GPT, or external hardware triggering then this function allows the trigger signal to
 * get to the ADC unit. The function itself is not able to control the generation of peripheral triggers. If the unit
 * was configured for software triggering, then this function starts the software triggered scan.
 *
 * @note Except for Group Priority Operation, if ADC0 or ADC1 are currently performing an A/D conversion operation,
 * attempting to start another scan group that uses the same A/D converter will be ignored. This also applies to
 * starting multiple groups at one time. When Group Priority Operation is not enabled, only the lowest numbered group
 * will be started (for each ADC converter), other groups will be ignored.
 *
 * @pre Call R_ADC_B_ScanCfg after R_ADC_B_Open before starting a scan.
 * @pre Call R_ADC_B_Calibrate and wait for calibration to complete before starting a scan.
 *
 * @retval FSP_SUCCESS                 Scan started (software trigger) or hardware triggers enabled.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_INVALID_ARGUMENT    An invalid group has been provided.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit not initialized.
 * @retval FSP_ERR_INVALID_STATE       Calibration required.
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_ScanGroupStart (adc_ctrl_t * p_ctrl, adc_group_mask_t group_mask)
{
    adc_b_instance_ctrl_t * p_instance_ctrl = (adc_b_instance_ctrl_t *) p_ctrl;

#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);

    adc_group_mask_t configured_groups =
        (adc_group_mask_t) (p_instance_ctrl->cached_adtrgenr | p_instance_ctrl->cached_adsystr);
    FSP_ERROR_RETURN(0 != (configured_groups & group_mask), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((ADC_B_CONVERTER_STATE_READY == p_instance_ctrl->adc_state), FSP_ERR_INVALID_STATE);
#endif

    R_ADC_B->ADTRGENR |= (group_mask & p_instance_ctrl->cached_adtrgenr);
    R_ADC_B->ADSYSTR  |= (group_mask & p_instance_ctrl->cached_adsystr);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables the hardware trigger for a scan and immediately stops all active converters. This function will abortall
 * active conversions.
 *
 * @retval FSP_SUCCESS                 All scans stopped.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_INVALID_ARGUMENT    No hardware triggers configured for groups.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_ScanStop (adc_ctrl_t * p_ctrl)
{
    adc_b_instance_ctrl_t * p_instance_ctrl = (adc_b_instance_ctrl_t *) p_ctrl;
#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);

    uint32_t configured_channels = (p_instance_ctrl->cached_adtrgenr | p_instance_ctrl->cached_adsystr);
    FSP_ERROR_RETURN(configured_channels, FSP_ERR_INVALID_ARGUMENT);
#endif

    adc_b_force_stop(p_instance_ctrl);

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
fsp_err_t R_ADC_B_StatusGet (adc_ctrl_t * p_ctrl, adc_status_t * p_status)
{
    adc_b_instance_ctrl_t * p_instance_ctrl = (adc_b_instance_ctrl_t *) p_ctrl;

#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Calibration status is based on the internal state machine.
     * CALACTn cannot be used because the ADC will enter and exit calibration several times before completing */
    bool calibration_in_progress = ((p_instance_ctrl->adc_state > ADC_B_CONVERTER_STATE_NONE) &&
                                    (p_instance_ctrl->adc_state < ADC_B_CONVERTER_STATE_READY));

    /* A scan is active if any scan group is being processed */
    bool scan_in_progress = (bool) R_ADC_B->ADSR;

    p_status->state = (calibration_in_progress ? ADC_STATE_CALIBRATION_IN_PROGRESS :
                       scan_in_progress ? ADC_STATE_SCAN_IN_PROGRESS : ADC_STATE_IDLE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads conversion results from a single channel or sensor.
 *
 * @retval FSP_SUCCESS                 Data read into provided p_data.
 * @retval FSP_ERR_INVALID_DATA        Accuracy of data cannot be guaranteed. ADC requires calibration or SAR timing settings are irregular.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit not initialized.
 * @retval FSP_ERR_INVALID_CHANNEL     Invalid channel provided.
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_Read (adc_ctrl_t * p_ctrl, adc_channel_t const channel_id, uint16_t * const p_data)
{
#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    adc_b_instance_ctrl_t * p_instance_ctrl = (adc_b_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
    FSP_ERROR_RETURN(ADC_B_CHANNEL_IS_EXTERNAL(channel_id) || ADC_B_CHANNEL_IS_INTERNAL(channel_id),
                     FSP_ERR_INVALID_CHANNEL);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    uint32_t register_data = R_ADC_B0_ADDR_ERR_Msk;
    if (ADC_B_CHANNEL_IS_EXTERNAL(channel_id))
    {
        register_data = *(uint32_t *) &R_ADC_B->ADDR[channel_id];
    }
    else
    {
        /* Read data from extended register from converted offset. */
        register_data = *(uint32_t *) &R_ADC_B->ADEXDR[(channel_id - ADC_CHANNEL_FIRST_INTERNAL)];
    }

    /* Extract error code from converted value */
    bool data_err = (R_ADC_B0_ADDR_ERR_Msk & register_data);
    *p_data = (uint16_t) (~R_ADC_B0_ADDR_ERR_Msk & register_data);

    fsp_err_t err = data_err ? FSP_ERR_INVALID_DATA : FSP_SUCCESS;
    FSP_ERROR_LOG(err);

    return err;
}

/*******************************************************************************************************************//**
 * Reads conversion results from a single channel or sensor register into a 32-bit result.
 *
 * @retval FSP_SUCCESS               Data read into provided p_data.
 * @retval FSP_ERR_INVALID_DATA      Accuracy of data cannot be guaranteed. ADC requires calibration or SAR timing settings are irregular.
 * @retval FSP_ERR_ASSERTION         An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN          Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED   Unit not initialized.
 * @retval FSP_ERR_INVALID_CHANNEL   Invalid channel provided.
 * @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                   return codes. This function calls:
 *                                       * @ref adc_api_t::read
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_Read32 (adc_ctrl_t * p_ctrl, adc_channel_t const channel_id, uint32_t * const p_data)
{
#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_data);
#endif

    uint16_t  result_16 = 0U;
    fsp_err_t err       = R_ADC_B_Read(p_ctrl, channel_id, &result_16);
    FSP_ERROR_RETURN((FSP_SUCCESS == err) || (FSP_ERR_INVALID_DATA == err), err);

    *p_data = result_16;

    return err;
}

/*******************************************************************************************************************//**
 * Reads conversion results from FIFO for the given group mask.
 *
 * @retval FSP_SUCCESS                 Data read into provided p_data.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit not initialized.
 * @retval FSP_ERR_INVALID_ARGUMENT    Invalid group provided.
 * @retval FSP_ERR_UNDERFLOW           FIFO empty.
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_FifoRead (adc_ctrl_t * p_ctrl, adc_group_mask_t const group_mask, adc_b_fifo_read_t * const p_data)
{
    uint8_t group_id = (uint8_t) __CLZ(__RBIT(group_mask));
#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    adc_b_instance_ctrl_t * p_instance_ctrl = (adc_b_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
    FSP_ERROR_RETURN(0 == ((uint32_t) ~ADC_GROUP_MASK_ALL & group_mask), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((group_id < 32) && (group_mask == (1 << group_id)), FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    uint32_t * p_fifo_data     = ADC_B_REG_ADDRESS(R_ADC_B->ADFIFODR0, group_id, sizeof(R_ADC_B->ADFIFODR0));
    uint32_t * p_fifo_status   = ADC_B_REG_ADDRESS(R_ADC_B->ADFIFOSR0, group_id / 2U, sizeof(R_ADC_B->ADFIFOSR0));
    uint32_t   remaining_count = *p_fifo_status & (R_ADC_B0_ADFIFOSR0_FIFOST0_Msk | R_ADC_B0_ADFIFOSR0_FIFOST1_Msk);

    remaining_count >>= ((group_id % 2) ? R_ADC_B0_ADFIFOSR0_FIFOST1_Pos : R_ADC_B0_ADFIFOSR0_FIFOST0_Pos);
    uint8_t count = (ADC_B_FIFO_STAGE_COUNT - (uint8_t) remaining_count);
    p_data->count = count;
    volatile adc_b_fifo_data_t * p_data_dest = &p_data->fifo_data[0];
    for (uint8_t i = 0; i < count; i++)
    {
        p_data_dest[i] = *(adc_b_fifo_data_t *) p_fifo_data;
    }

    fsp_err_t err = (count ? FSP_SUCCESS : FSP_ERR_UNDERFLOW);
    FSP_ERROR_LOG(err);

    /* Clear FIFO full flag */
    R_ADC_B->ADFIFOERSCR_b.FIFOFLCn = group_mask;

    return err;
}

/*******************************************************************************************************************//**
 * Provides the temperature sensor slope and the calibration data for the sensor if available on this MCU.
 * Otherwise, invalid calibration data of 0xFFFFFFFF will be returned.
 *
 * @retval FSP_SUCCESS               Info is read into p_adc_info.
 * @retval FSP_ERR_ASSERTION         An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN          Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED   Unit not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_InfoGet (adc_ctrl_t * p_ctrl, adc_info_t * p_adc_info)
{
#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    adc_b_instance_ctrl_t * p_instance_ctrl = (adc_b_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_adc_info);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Preset data to invalid value */
    p_adc_info->p_address        = NULL;
    p_adc_info->length           = 0;
    p_adc_info->transfer_size    = (transfer_size_t) UINT32_MAX;
    p_adc_info->elc_peripheral   = (elc_peripheral_t) UINT32_MAX;
    p_adc_info->elc_event        = ELC_EVENT_NONE;
    p_adc_info->calibration_data = UINT32_MAX;
    p_adc_info->slope_microvolts = 0;

    /* Update Temp Sensor calibration data if it is available */
    if (R_TSN_CTRL->TSCR_b.TSEN)
    {
        uint32_t data = R_TSN_CAL->TSCDR;
        p_adc_info->calibration_data = (data & BSP_FEATURE_TSN_CALIBRATION32_MASK);
    }

    /* Provide the previously retrieved slope information */
    p_adc_info->slope_microvolts = BSP_FEATURE_TSN_SLOPE;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function ends any scan in progress, disables interrupts, and removes power to the A/D peripheral.
 *
 * @retval FSP_SUCCESS                 Module closed.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_Close (adc_ctrl_t * p_ctrl)
{
    adc_b_instance_ctrl_t * p_instance_ctrl = (adc_b_instance_ctrl_t *) p_ctrl;
#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Force stop any active scans */
    adc_b_force_stop(p_instance_ctrl);

    /* Mark driver as closed   */
    p_instance_ctrl->opened          = 0U;
    p_instance_ctrl->initialized     = 0U;
    p_instance_ctrl->cached_adtrgenr = ADC_GROUP_MASK_NONE;
    p_instance_ctrl->cached_adsystr  = ADC_GROUP_MASK_NONE;

    /* Disable internal reference voltage */
    R_ADC_B->ADREFCR = 0x00;

#if BSP_FEATURE_ADC_B_PGA_SUPPORTED

    /* Disable PGA, to release pins for use as GPIO */
    for (uint8_t i = 0; i < 4; i++)
    {
        R_ADC_B->ADPGACR[i] &= 0;
    }
#endif

    /* Disable interrupts */
    adc_b_disable_interrupts(p_instance_ctrl);

    /* Disable temperature sensor if configured. See "Procedure example for using the TSN" in the TSN section of the relevant hardware manual. */
    if (R_TSN_CTRL->TSCR_b.TSEN)
    {
        R_TSN_CTRL->TSCR_b.TSOE = 0;
        R_TSN_CTRL->TSCR_b.TSEN = 0;
        R_BSP_MODULE_STOP(FSP_IP_TSN, 0);
    }

    /* Module Stop set: ADC */
    R_BSP_MODULE_STOP(FSP_IP_ADC, 0);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initiates calibration of the ADC_B.  This function must be called before starting a scan and again whenever ADC_B
 * configuration or state is changed.
 *
 * @note Self-calibration is a non-blocking operation. The application must wait for calibration to complete before
 * using other ADC_B functionality.
 *
 * @note The self-calibration process will disable hardware triggers that were previously enabled.
 *
 * @param[in]  p_ctrl    Pointer to the instance control structure
 * @param[in]  p_extend  Unused argument.
 *
 * @retval FSP_SUCCESS                     Calibration successfully initiated.
 * @retval FSP_ERR_ASSERTION               An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN                Unit is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_Calibrate (adc_ctrl_t * const p_ctrl, void const * p_extend)
{
#if defined(R_ADC_B0_ADOVFEXSCR_OVFEXC2_Msk)
 #define R_ADC_B_EXTENDED_OVERFLOW_FLAG_CLEAR_Msk    (R_ADC_B0_ADOVFEXSCR_OVFEXC0_Msk | \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC1_Msk | \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC2_Msk | \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC5_Msk | \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC6_Msk | \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC7_Msk | \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC8_Msk);
#else
 #define R_ADC_B_EXTENDED_OVERFLOW_FLAG_CLEAR_Msk    (R_ADC_B0_ADOVFEXSCR_OVFEXC0_Msk |  \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC1_Msk |  \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC4_Msk |  \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC5_Msk |  \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC6_Msk |  \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC8_Msk |  \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC9_Msk |  \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC16_Msk | \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC17_Msk | \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC18_Msk | \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC20_Msk | \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC21_Msk | \
                                                      R_ADC_B0_ADOVFEXSCR_OVFEXC22_Msk)
#endif

    adc_b_instance_ctrl_t * p_instance_ctrl = (adc_b_instance_ctrl_t *) p_ctrl;
#if ADC_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif
    FSP_PARAMETER_NOT_USED(p_extend);

    p_instance_ctrl->adc_state = ADC_B_CONVERTER_STATE_NONE;

    adc_b_force_stop(p_instance_ctrl); // This step ensures ADC is not operating

    /* Clear the error status flags */
    R_ADC_B->ADERSCR     = R_ADC_B0_ADERSCR_ADERCLR0_Msk | R_ADC_B0_ADERSCR_ADERCLR1_Msk;
    R_ADC_B->ADOVFERSCR  = R_ADC_B0_ADOVFERSCR_ADOVFEC0_Msk | R_ADC_B0_ADOVFERSCR_ADOVFEC1_Msk;
    R_ADC_B->ADOVFCHSCR0 = R_ADC_B0_ADOVFCHSCR0_OVFCHCn_Msk;
    R_ADC_B->ADOVFEXSCR  = R_ADC_B_EXTENDED_OVERFLOW_FLAG_CLEAR_Msk;

    uint32_t adcalstr = adc_b_update_calibrate_state(p_instance_ctrl);
    R_ADC_B->ADCALSTR = adcalstr;      // Initiate calibration

    return FSP_SUCCESS;

#undef R_ADC_B_EXTENDED_OVERFLOW_FLAG_CLEAR_Msk
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::offsetSet is not supported on the ADC_B.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_ADC_B_OffsetSet (adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t offset)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(reg_id);
    FSP_PARAMETER_NOT_USED(offset);

    /* Return the unsupported error. */
    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup ADC_B)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * @brief Helper function - Pre-calculate wait time for use when stopping ADC
 * @param p_instance_ctrl - Pointer to adc_b instance configuration
 * @return None
 **********************************************************************************************************************/
static void adc_b_calculate_wait_time (adc_b_instance_ctrl_t * p_instance_ctrl, adc_b_scan_cfg_t * p_scan_data)
{
    adc_b_extended_cfg_t * p_extend = (adc_b_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    bool sync_enabled_lut[]         =
    {
        !p_extend->sync_operation_control_bits.adc_0_disable_sync,
        !p_extend->sync_operation_control_bits.adc_1_disable_sync
    };
    uint16_t sync_cycles = p_extend->sync_operation_control_bits.period_cycle;

    uint32_t wait_cycles = 0;
    for (uint8_t group = 0; (group < p_scan_data->group_count) && p_instance_ctrl->cached_adtrgenr; group++)
    {
        const adc_b_group_cfg_t * p_adc_group = p_scan_data->p_adc_groups[group];
        bool     sync_enabled                 = sync_enabled_lut[p_adc_group->converter_selection];
        uint32_t trigger_delay                = p_extend->start_trigger_delay_table[group];

        uint32_t calculated_cycles = 0;
        if (sync_enabled)
        {
            calculated_cycles = trigger_delay + sync_cycles * 2;
        }
        else
        {
            calculated_cycles = trigger_delay + 4;
        }

        if (wait_cycles < calculated_cycles)
        {
            wait_cycles = calculated_cycles;
        }
    }

    p_instance_ctrl->trigger_disable_wait_cycles = wait_cycles + 1;
}

/***************************************************************************************************************************************************************
 * @brief Helper function - Perform ADC calibration according to "Procedure for self-calibration" in the A/D converter section of the relevant hardware manual
 * @param p_instance_ctrl - Pointer to adc_b instance configuration
 * @return uint32_t       - Next ADCCALSR register bits
 ***************************************************************************************************************************************************************/
static uint32_t adc_b_update_calibrate_state (adc_b_instance_ctrl_t * p_instance_ctrl)
{
    /* Converters must be calibrated sequentially.
     * Converter calibration must be performed before Sample-and-Hold calibration. */
    uint32_t adcalstr = 0;
    switch (p_instance_ctrl->adc_state)
    {
        case ADC_B_CONVERTER_STATE_NONE:
        {
            p_instance_ctrl->adc_state = ADC_B_CONVERTER_STATE_ADC_0_CALIBRATING;
            adcalstr = (uint32_t) (R_ADC_B_ADCALSTR_ADC_0_CAL_Msk | R_ADC_B_ADCALSTR_GAIN_OFFSET_0_CAL_Msk);

            break;
        }

        case ADC_B_CONVERTER_STATE_ADC_0_CALIBRATING:
        {
            p_instance_ctrl->adc_state = ADC_B_CONVERTER_STATE_SH_0_2_CALIBRATING;
            if (R_ADC_B->ADSHCR0 & ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_012)
            {
                adcalstr = R_ADC_B_ADCALSTR_SAMPLE_HOLD_0_CAL_Msk;

                /* Enable configured Sample-and-Hold settings
                 * - See Note 2 of table "Procedure for self-calibration" in the A/D converter section of the relevant hardware manual. */
                R_ADC_B->ADSHCR0 = ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_012;
            }
            else
            {
                /* Advance to next phase if no Sample-and-Hold units are enabled */
                adcalstr = adc_b_update_calibrate_state(p_instance_ctrl);
            }

            break;
        }

        case ADC_B_CONVERTER_STATE_SH_0_2_CALIBRATING:
        {
            p_instance_ctrl->adc_state = ADC_B_CONVERTER_STATE_ADC_1_CALIBRATING;
            adcalstr = (uint32_t) (R_ADC_B_ADCALSTR_ADC_1_CAL_Msk | R_ADC_B_ADCALSTR_GAIN_OFFSET_1_CAL_Msk);
            break;
        }

        case ADC_B_CONVERTER_STATE_ADC_1_CALIBRATING:
        {
            p_instance_ctrl->adc_state = ADC_B_CONVERTER_STATE_SH_4_6_CALIBRATING;

            /* Skip Sample-and-Hold if not enabled
             * - See Note 1 of table "Procedure for self-calibration" in the A/D converter section of the relevant hardware manual */
            if (R_ADC_B->ADSHCR1 & (ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_456 >> 4))
            {
                adcalstr = R_ADC_B_ADCALSTR_SAMPLE_HOLD_1_CAL_Msk;

                /* Enable configured Sample-and-Hold settings
                 * - See Note 2 of table "Procedure for self-calibration" in the A/D converter section of the relevant hardware manual */
                R_ADC_B->ADSHCR1 = ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_456 >> 4;
            }
            else
            {
                /* Advance to next phase if no Sample-and-Hold units are enabled */
                adcalstr = adc_b_update_calibrate_state(p_instance_ctrl);
            }

            break;
        }

        /* Do nothing. Calibration is complete */
        case ADC_B_CONVERTER_STATE_SH_4_6_CALIBRATING:
        case ADC_B_CONVERTER_STATE_READY:
        {
            /* Reset Sample-and-hold configuration */
            adc_b_extended_cfg_t * p_extend = (adc_b_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
            R_ADC_B->ADSHCR0 = p_extend->sample_and_hold_enable_mask & ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_012;
            R_ADC_B->ADSHCR1 =
                (p_extend->sample_and_hold_enable_mask & ADC_B_SAMPLE_AND_HOLD_MASK_UNIT_456) >> 4;
            p_instance_ctrl->adc_state = ADC_B_CONVERTER_STATE_READY;
            break;
        }

        default:
        case ADC_B_CONVERTER_STATE_CALIBRATION_FAIL:
        {
            break;                     // Do nothing
        }
    }

    return adcalstr;
}

/***********************************************************************************************************************
 * @brief Helper function - Force stop ADC operation
 * @param p_instance_ctrl - Pointer to adc_b instance configuration
 * @return None
 **********************************************************************************************************************/
static void adc_b_force_stop (adc_b_instance_ctrl_t * p_instance_ctrl)
{
    /* Clear ADC Start Trigger Enable */
    R_ADC_B->ADTRGENR = ADC_GROUP_MASK_NONE;

    /* Perform delay according to "Waiting Time after Disabling Trigger Input for Forced Stop Processing" in
     * the A/D converter section of the relevant hardware manual. */
    for (uint32_t i = p_instance_ctrl->trigger_disable_wait_cycles; i > 0; i--)
    {
        FSP_REGISTER_READ(R_ADC_B->ADSR);
    }

    /* Force stop if ADC is still running */
    if (R_ADC_B->ADSR)
    {
        R_ADC_B->ADSTOPR = R_ADC_B0_ADSTOPR_ADSTOP0_Msk | R_ADC_B0_ADSTOPR_ADSTOP1_Msk;

        /* Wait for converter to stop */
        FSP_HARDWARE_REGISTER_WAIT(R_ADC_B->ADSR, 0)
    }
}

#if BSP_FEATURE_ADC_B_PGA_SUPPORTED

/***********************************************************************************************************************
 * @brief Helper function - Initialize PGA settings during call to open
 * @param p_extend        - Pointer to adc_b extended configuration
 * @return None
 **********************************************************************************************************************/
static void adc_b_open_pga (adc_b_extended_cfg_t * p_extend)
{
    /* Configure PGA */
    for (uint8_t i = 0; i < 4; i++)
    {
        R_ADC_B->ADPGACR[i] = p_extend->pga_gain[i] | R_ADC_B0_ADPGACR_PGAGEN_Msk;
    }

    R_ADC_B->ADPGAMONCR = (uint32_t) (((0 != p_extend->pga_debug_monitor_mask) << R_ADC_B0_ADPGAMONCR_PGAMON_Pos) |
                                      (p_extend->pga_debug_monitor_mask << R_ADC_B0_ADPGAMONCR_MONSEL0_Pos));
}

#endif

/***********************************************************************************************************************
 * @brief Disable all adc_b interrupts
 * @param p_instance_ctrl - pointer to adc_b instance control structure
 * @return None
 **********************************************************************************************************************/
static void adc_b_disable_interrupts (adc_b_instance_ctrl_t * p_instance_ctrl)
{
    adc_b_extended_cfg_t  * p_extend  = (adc_b_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    const adc_b_isr_cfg_t * p_isr_cfg = p_extend->p_isr_cfg;

    /* Code-coupled data */
    const IRQn_Type * p_first_irq = &p_isr_cfg->calibration_end_irq_adc_0;
    const IRQn_Type * p_last_irq  = &p_isr_cfg->scan_end_irq_group_5678;
    for (const IRQn_Type * p_irq = p_first_irq; p_irq <= p_last_irq; p_irq++)
    {
        if (*p_irq >= 0)
        {
            R_BSP_IrqDisable(*p_irq);
        }
    }
}

/***********************************************************************************************************************
 * @brief Enable all configured adc_b interrupts
 * @param p_instance_ctrl - pointer to adc_b instance control structure
 * @return None
 **********************************************************************************************************************/
static void adc_b_enable_interrupts (adc_b_instance_ctrl_t * p_instance_ctrl)
{
    adc_b_extended_cfg_t  * p_extend  = (adc_b_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    const adc_b_isr_cfg_t * p_isr_cfg = p_extend->p_isr_cfg;

    const uint8_t   * p_first_ipl = &p_isr_cfg->calibration_end_ipl_adc_0;
    const uint8_t   * p_last_ipl  = &p_isr_cfg->scan_end_ipl_group_5678;
    const IRQn_Type * p_first_irq = &p_isr_cfg->calibration_end_irq_adc_0;

    const uint8_t   * p_ipl = p_first_ipl;
    const IRQn_Type * p_irq = p_first_irq;
    while (p_ipl <= p_last_ipl)
    {
        adc_b_isr_enable(p_instance_ctrl, *p_irq++, *p_ipl++);
    }
}

/***********************************************************************************************************************
 * @brief Helper function to enable configured interrupts
 * @param p_instance_ctrl - pointer to adc_b instance control structure
 * @param irq             - Configured interrupt vector table allocation
 * @param ipl             - Configured interrupt priority level
 * @return None
 **********************************************************************************************************************/
static void adc_b_isr_enable (adc_b_instance_ctrl_t * p_instance_ctrl, IRQn_Type irq, uint8_t ipl)
{
    if (irq >= 0)
    {
        R_BSP_IrqCfgEnable(irq, ipl, p_instance_ctrl);
    }
}

/***********************************************************************************************************************
 * @brief Common ISR processing wrapper.
 * @param p_instance_ctrl - pointer to adc_b instance control structure
 * @param event           -  ISR event to process
 * @param group_mask      - ADC groups related to ISR event
 * @param channel_mask    - ADC channels related to ISR event
 * @param unit            - ADC unit related to event
 * @return None
 **********************************************************************************************************************/
static IRQn_Type adc_b_isr_handler (adc_event_t          event,
                                    adc_group_mask_t     group_mask,
                                    adc_b_channel_mask_t channel_mask,
                                    adc_b_unit_mask_t    unit)
{
    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    adc_b_instance_ctrl_t * p_instance_ctrl = (adc_b_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    if (p_instance_ctrl->p_callback)
    {
        adc_callback_args_t args;
        args.event        = event;
        args.channel      = (adc_channel_t) UINT8_MAX;
        args.channel_mask = (uint64_t) channel_mask;
        args.group_mask   = group_mask;
        args.p_context    = p_instance_ctrl->p_context;
        args.unit         = (uint8_t) unit;

        adc_b_call_callback(p_instance_ctrl, &args);
    }

    return irq;
}

/***********************************************************************************************************************
 * @brief Common ISR callback wrapper. Manages callback argument memory and security context.
 * @param p_ctrl - pointer to adc_b instance control structure
 * @param p_args -  Pointer to callback arguments
 * @return None
 **********************************************************************************************************************/
static void adc_b_call_callback (adc_b_instance_ctrl_t * p_ctrl, adc_callback_args_t * p_args)
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
        adc_b_prv_ns_callback p_callback = (adc_b_prv_ns_callback) (p_ctrl->p_callback);
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

#if (ADC_B_CFG_PARAM_CHECKING_ENABLE)

/***********************************************************************************************************************
 * @brief Check if sample and hold is enabled for given channel
 * @param channel                     - Channel to check
 * @param sample_and_hold_enable_mask - Enable mask from configuration structure
 * @return None
 **********************************************************************************************************************/
static bool adc_channel_is_sample_hold_enabled (adc_channel_t channel, uint8_t sample_and_hold_enable_mask)
{
    /* sample and hold connected to channels in pairs from 0/1 to 10/11, corresponding to Sample and Hold IDs 0-2 and 4-6 */
    bool sh_available = (channel <= ADC_CHANNEL_11);
    bool sh_enabled   = 1 << (channel / 2) & (sample_and_hold_enable_mask >> (channel / 6));

    return sh_available && sh_enabled;
}

#endif

/***********************************************************************************************************************
 * Interrupt Service Routines
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * @brief Calibration end ISR for A/D converter unit 0
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_calend0_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    adc_event_t          event        = ADC_EVENT_CALIBRATION_COMPLETE;
    adc_b_channel_mask_t channel_mask = ADC_B_CHANNEL_MASK_NONE;

    if (R_ADC_B->ADERSR_b.ADERF0)
    {
        event |= ADC_EVENT_CONVERSION_ERROR;
    }

    if (R_ADC_B->ADOVFERSR_b.ADOVFEF0)
    {
        event |= ADC_EVENT_OVERFLOW;
        uint32_t physical_channels = R_ADC_B->ADOVFCHSR0;
        uint32_t extended_channels = R_ADC_B->ADOVFEXSR;
        uint64_t extended_mask     = ((uint64_t) extended_channels) << ADC_B_CHANNEL_MASK_EXT_OFFSET;
        channel_mask |= (adc_b_channel_mask_t) (physical_channels | extended_mask);
    }

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    adc_b_instance_ctrl_t * p_instance_ctrl = (adc_b_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    uint32_t                adcalstr        = adc_b_update_calibrate_state(p_instance_ctrl);
    if (event & (adc_event_t) ~ADC_EVENT_CALIBRATION_COMPLETE)
    {
        p_instance_ctrl->adc_state = ADC_B_CONVERTER_STATE_CALIBRATION_FAIL;
        adcalstr = 0;
    }

    /* End calibration sequence if complete or failed */
    if (ADC_B_CONVERTER_STATE_READY <= p_instance_ctrl->adc_state)
    {
        adc_b_isr_handler(event, ADC_GROUP_MASK_NONE, channel_mask, ADC_B_UNIT_MASK_UNDEFINED);
    }

    R_ADC_B->ADCALENDSCR = R_ADC_B0_ADCALENDSCR_CALENDC0_Msk;
    R_BSP_IrqStatusClear(irq);

    /* Wait for converter stopped to initiate next calibration step
     * - See table "Forced Stop Procedure" in the A/D converter section of the relevant hardware manual. */
    FSP_HARDWARE_REGISTER_WAIT(R_ADC_B->ADSR, 0x00);
    R_ADC_B->ADCALSTR = adcalstr;

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief Calibration end ISR for A/D converter unit 1
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_calend1_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    adc_event_t          event        = ADC_EVENT_CALIBRATION_COMPLETE;
    adc_b_channel_mask_t channel_mask = ADC_B_CHANNEL_MASK_NONE;

    if (R_ADC_B->ADERSR_b.ADERF1)
    {
        event |= ADC_EVENT_CONVERSION_ERROR;
    }

    if (R_ADC_B->ADOVFERSR_b.ADOVFEF1)
    {
        event |= ADC_EVENT_OVERFLOW;
        uint32_t physical_channels = R_ADC_B->ADOVFCHSR0;
        uint32_t extended_channels = R_ADC_B->ADOVFEXSR;
        uint64_t extended_mask     = ((uint64_t) extended_channels) << ADC_B_CHANNEL_MASK_EXT_OFFSET;
        channel_mask |= (adc_b_channel_mask_t) (physical_channels | extended_mask);
    }

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    adc_b_instance_ctrl_t * p_instance_ctrl = (adc_b_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    uint32_t                adcalstr        = adc_b_update_calibrate_state(p_instance_ctrl);
    if (event & (adc_event_t) ~ADC_EVENT_CALIBRATION_COMPLETE)
    {
        p_instance_ctrl->adc_state = ADC_B_CONVERTER_STATE_CALIBRATION_FAIL;
        adcalstr = 0;
    }

    /* End calibration sequence if complete or failed */
    if (ADC_B_CONVERTER_STATE_READY <= p_instance_ctrl->adc_state)
    {
        adc_b_isr_handler(event, ADC_GROUP_MASK_NONE, channel_mask, ADC_B_UNIT_MASK_UNDEFINED);
    }

    R_ADC_B->ADCALENDSCR = R_ADC_B0_ADCALENDSCR_CALENDC1_Msk;
    R_BSP_IrqStatusClear(irq);

    /* Wait for converter stopped to initiate next calibration step
     * - See table "Forced Stop Procedure" in the A/D converter section of the relevant hardware manual. */
    FSP_HARDWARE_REGISTER_WAIT(R_ADC_B->ADSR, 0x00);
    R_ADC_B->ADCALSTR = adcalstr;

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief Limiter Clip ISR
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_limclpi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    adc_group_mask_t     group_mask        = (adc_group_mask_t) R_ADC_B->ADLIMGRSR;
    uint32_t             physical_channels = R_ADC_B->ADLIMCHSR0;
    uint64_t             extended_channels = ((uint64_t) R_ADC_B->ADLIMEXSR) << ADC_B_CHANNEL_MASK_EXT_OFFSET;
    adc_b_channel_mask_t channel_mask      = (adc_b_channel_mask_t) (physical_channels | extended_channels);

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_LIMIT_CLIP, group_mask, channel_mask, ADC_B_UNIT_MASK_UNDEFINED);

    R_ADC_B->ADLIMGRSCR  = group_mask;
    R_ADC_B->ADLIMCHSCR0 = physical_channels;
    R_ADC_B->ADLIMEXSCR  = (uint32_t) (extended_channels >> ADC_B_CHANNEL_MASK_EXT_OFFSET);
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter error ISR for unit 0
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_err0_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_CONVERSION_ERROR,
                                      ADC_GROUP_MASK_NONE,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_0);

    R_ADC_B->ADERSCR = R_ADC_B0_ADERSCR_ADERCLR0_Msk;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter error ISR for unit 1
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_err1_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_CONVERSION_ERROR,
                                      ADC_GROUP_MASK_NONE,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_1);

    R_ADC_B->ADERSCR = R_ADC_B0_ADERSCR_ADERCLR1_Msk;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter overflow ISR for unit 0
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_resovf0_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    uint32_t             physical_channels = R_ADC_B->ADOVFCHSR0;
    uint32_t             extended_channels = R_ADC_B->ADOVFEXSR;
    uint64_t             extended_mask     = ((uint64_t) extended_channels) << ADC_B_CHANNEL_MASK_EXT_OFFSET;
    adc_b_channel_mask_t channel_mask      = (adc_b_channel_mask_t) (physical_channels | extended_mask);

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_OVERFLOW, ADC_GROUP_MASK_NONE, channel_mask, ADC_B_UNIT_MASK_0);

    R_ADC_B->ADOVFCHSCR0 = physical_channels;
    R_ADC_B->ADOVFEXSCR  = extended_channels;
    R_ADC_B->ADOVFERSCR  = R_ADC_B0_ADOVFERSCR_ADOVFEC0_Msk;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter overflow ISR for unit 1
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_resovf1_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    uint32_t             physical_channels = R_ADC_B->ADOVFCHSR0;
    uint32_t             extended_channels = R_ADC_B->ADOVFEXSR;
    uint64_t             extended_mask     = ((uint64_t) extended_channels) << ADC_B_CHANNEL_MASK_EXT_OFFSET;
    adc_b_channel_mask_t channel_mask      = (adc_b_channel_mask_t) (physical_channels | extended_mask);

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_OVERFLOW, ADC_GROUP_MASK_NONE, channel_mask, ADC_B_UNIT_MASK_1);

    R_ADC_B->ADOVFCHSCR0 = physical_channels;
    R_ADC_B->ADOVFEXSCR  = extended_channels;
    R_ADC_B->ADOVFERSCR  = R_ADC_B0_ADOVFERSCR_ADOVFEC1_Msk;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter complete ISR for group 0
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_adi0_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_SCAN_COMPLETE,
                                      ADC_GROUP_MASK_0,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);

    R_ADC_B->ADSCANENDSCR = ADC_GROUP_MASK_0;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter complete ISR for group 1
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_adi1_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_SCAN_COMPLETE,
                                      ADC_GROUP_MASK_1,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);

    R_ADC_B->ADSCANENDSCR = ADC_GROUP_MASK_1;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter complete ISR for group 2
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_adi2_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_SCAN_COMPLETE,
                                      ADC_GROUP_MASK_2,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);

    R_ADC_B->ADSCANENDSCR = ADC_GROUP_MASK_2;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter complete ISR for group 3
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_adi3_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_SCAN_COMPLETE,
                                      ADC_GROUP_MASK_3,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);

    R_ADC_B->ADSCANENDSCR = ADC_GROUP_MASK_3;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter complete ISR for group 4
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_adi4_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_SCAN_COMPLETE,
                                      ADC_GROUP_MASK_4,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);

    R_ADC_B->ADSCANENDSCR = ADC_GROUP_MASK_4;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter complete ISR for groups 5
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_adi5_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_SCAN_COMPLETE,
                                      ADC_GROUP_MASK_5,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);

    R_ADC_B->ADSCANENDSCR = ADC_GROUP_MASK_5;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter complete ISR for groups 6
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_adi6_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_SCAN_COMPLETE,
                                      ADC_GROUP_MASK_6,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);

    R_ADC_B->ADSCANENDSCR = ADC_GROUP_MASK_6;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter complete ISR for groups 7
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_adi7_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_SCAN_COMPLETE,
                                      ADC_GROUP_MASK_7,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);

    R_ADC_B->ADSCANENDSCR = ADC_GROUP_MASK_7;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter complete ISR for groups 8
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_adi8_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_SCAN_COMPLETE,
                                      ADC_GROUP_MASK_8,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);

    R_ADC_B->ADSCANENDSCR = ADC_GROUP_MASK_8;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief A/D converter complete ISR for groups 5, 6, 7, and 8
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_adi5678_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    uint8_t          group_id   = (uint8_t) __CLZ(__RBIT(ADC_B_GROUP_MASK_5678 & R_ADC_B->ADSCANENDSR));
    adc_group_mask_t group_mask =
        (adc_group_mask_t) ((group_id > 31) ? ADC_GROUP_MASK_NONE : (1U << group_id));

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_SCAN_COMPLETE,
                                      group_mask,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);

    R_ADC_B->ADSCANENDSCR = group_mask;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief FIFO overflow ISR
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_fifoovf_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    adc_group_mask_t group_mask = (adc_group_mask_t) R_ADC_B->ADFIFOERSR_b.FIFOOVFn;

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_FIFO_OVERFLOW,
                                      group_mask,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);

    R_ADC_B->ADFIFODCR               = group_mask;
    R_ADC_B->ADFIFOERSCR_b.FIFOOVFCn = group_mask;
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief FIFO data threshold read ISR for group 0
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_fiforeq0_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_FIFO_READ_REQUEST,
                                      ADC_GROUP_MASK_0,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief FIFO data threshold read ISR for group 1
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_fiforeq1_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_FIFO_READ_REQUEST,
                                      ADC_GROUP_MASK_1,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief FIFO data threshold read ISR for group 2
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_fiforeq2_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_FIFO_READ_REQUEST,
                                      ADC_GROUP_MASK_2,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief FIFO data threshold read ISR for group 3
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_fiforeq3_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_FIFO_READ_REQUEST,
                                      ADC_GROUP_MASK_3,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief FIFO data threshold read ISR for group 4
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_fiforeq4_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_FIFO_READ_REQUEST,
                                      ADC_GROUP_MASK_4,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief FIFO data threshold read ISR for group 5
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_fiforeq5_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_FIFO_READ_REQUEST,
                                      ADC_GROUP_MASK_5,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief FIFO data threshold read ISR for group 6
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_fiforeq6_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_FIFO_READ_REQUEST,
                                      ADC_GROUP_MASK_6,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief FIFO data threshold read ISR for groups 7
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_fiforeq7_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_FIFO_READ_REQUEST,
                                      ADC_GROUP_MASK_7,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief FIFO data threshold read ISR for group 8
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_fiforeq8_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = adc_b_isr_handler(ADC_EVENT_FIFO_READ_REQUEST,
                                      ADC_GROUP_MASK_8,
                                      ADC_B_CHANNEL_MASK_NONE,
                                      ADC_B_UNIT_MASK_UNDEFINED);
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * @brief FIFO data threshold read ISR for groups 5, 6, 7, and 8
 * @param  None
 * @return None
 **********************************************************************************************************************/
void adc_b_fiforeq5678_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    /* Get groups with less data available than threshold */
    adc_group_mask_t group = (adc_group_mask_t) (ADC_B_GROUP_MASK_5678 & R_ADC_B->ADFIFOERSR_b.FIFOFLFn);
    IRQn_Type        irq   = adc_b_isr_handler(ADC_EVENT_FIFO_READ_REQUEST,
                                               group,
                                               ADC_B_CHANNEL_MASK_NONE,
                                               ADC_B_UNIT_MASK_UNDEFINED);
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
