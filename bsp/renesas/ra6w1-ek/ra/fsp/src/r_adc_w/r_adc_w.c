/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_adc_w_cfg.h"
#include "r_adc_w.h"
#include "../bsp/mcu/ra6w1/config/bsp_device_definitions.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define ADC_W_OPEN               (0x41444342) /* ADC_W in ascii */
#define AUX_ADC_INITIAL_VALUE    (0x1582)
#define ADC_W_12BIT_MASK         (0xFFFU)
#define ADC_W_5BIT_MASK          (0x1FU)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
#if ADC_W_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_adc_w_scan_cfg_check(adc_w_instance_ctrl_t * const p_ctrl);
static fsp_err_t r_adc_w_open_cfg_check(adc_cfg_t const * const p_cfg);
static fsp_err_t r_adc_w_SensorWakeup_cfg_check(adc_w_instance_ctrl_t * const p_ctrl);

#endif

#if ADC_W_CFG_INTERRUPT_SUPPORT_ENABLE
void adc_w_scan_end_isr(void);

#endif

static void r_adc_w_ldo_enable(adc_channel_t channel);

/***********************************************************************************************************************
 * Interrupt Service Routines
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* ADC_W Implementation of ADC. */
const adc_api_t g_adc_on_adc_w =
{
    .open           = R_ADC_W_Open,
    .scanCfg        = R_ADC_W_ScanCfg,
    .infoGet        = R_ADC_W_InfoGet,
    .scanStart      = R_ADC_W_ScanStart,
    .scanGroupStart = R_ADC_W_ScanGroupStart,
    .scanStop       = R_ADC_W_ScanStop,
    .scanStatusGet  = R_ADC_W_StatusGet,
    .read           = R_ADC_W_Read,
    .read32         = R_ADC_W_Read32,
    .close          = R_ADC_W_Close,
    .calibrate      = R_ADC_W_Calibrate,
    .offsetSet      = R_ADC_W_OffsetSet,
    .callbackSet    = R_ADC_W_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup ADC_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize the ADC_W peripheral.
 * If interrupt is enabled, the function registers a callback function for notifying the user when ADC
 * interrupt event occurrs.
 * Implements @ref adc_api_t::open.
 *
 * @retval FSP_SUCCESS                    Module is ready for use.
 * @retval FSP_ERR_ASSERTION              An input argument is invalid.
 * @retval FSP_ERR_ALREADY_OPEN           The instance control structure has already been opened.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       A callback is provided, but the interrupt is not enabled.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_Open (adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg)
{
    adc_w_instance_ctrl_t * p_instance_ctrl = (adc_w_instance_ctrl_t *) p_ctrl;
#if ADC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);

    /* Verify the configuration parameters are valid */
    fsp_err_t err = r_adc_w_open_cfg_check(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Verify this unit has not already been initialized */
    FSP_ERROR_RETURN(ADC_W_OPEN != p_instance_ctrl->opened, FSP_ERR_ALREADY_OPEN);

    /* If a callback is used, then make sure an interrupt is enabled */
    if (NULL != p_cfg->p_callback)
    {
        FSP_ERROR_RETURN(p_cfg->scan_end_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

    /* Mark driver as opened by initializing it to "ADC_W" in its ASCII equivalent for this unit. */
    p_instance_ctrl->opened = ADC_W_OPEN;
#endif

    /* Save configurations. */
    p_instance_ctrl->p_cfg      = p_cfg;
    p_instance_ctrl->p_callback = p_cfg->p_callback;
    p_instance_ctrl->p_context  = p_cfg->p_context;

    adc_w_extended_cfg_t * p_ext = (adc_w_extended_cfg_t *) p_cfg->p_extend;
    uint16_t               div   = p_ext->conversion_clockdiv;

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* The default resolution is 12 bit */
    RTC->XADC12_CNTL_REG = AUX_ADC_INITIAL_VALUE;

    if (ADC_RESOLUTION_12_BIT == p_instance_ctrl->p_cfg->resolution)
    {
        RTC->XADC12_CNTL_REG_b.AUXADC12_BITNUM = 0x0;
    }
    else if (ADC_RESOLUTION_10_BIT == p_instance_ctrl->p_cfg->resolution)
    {
        RTC->XADC12_CNTL_REG_b.AUXADC12_BITNUM = 0x1;
    }
    else if (ADC_RESOLUTION_7_BIT == p_instance_ctrl->p_cfg->resolution)
    {
        RTC->XADC12_CNTL_REG_b.AUXADC12_BITNUM = 0x2;
    }
    else if (ADC_RESOLUTION_4_BIT == p_instance_ctrl->p_cfg->resolution)
    {
        RTC->XADC12_CNTL_REG_b.AUXADC12_BITNUM = 0x3;
    }
    else
    {
        ;
    }

    CRG_TOP->CLK_AMBA_REG_b.PERI_CLK_ENABLE = 1;

    /* PLL divider enable for Aux 15Mhz */
    CRG_TOP->CLK_CTRL_REG_b.PLL_AUX_ENABLE = 0;
    CRG_TOP->CLK_AMBA_REG_b.AUX_CLK_ENABLE = 0;

    CRG_PER->RESET_CLK_COM_REG_b.AUXADC_ENABLE = 1;

    CRG_TOP->AUX_CLK_DIV_REG = (uint32_t) (div - 1);

    /* PLL divider enable for Aux 15Mhz */
    CRG_TOP->CLK_CTRL_REG_b.PLL_AUX_ENABLE   = 1;
    CRG_TOP->CLK_AMBA_REG_b.AUX_CLK_ENABLE   = 1;
    CRG_PER->SET_CLK_COM_REG_b.AUXADC_ENABLE = 1;

    FSP_CRITICAL_SECTION_EXIT;

    AUXADC->XADC12B_CTRL_REG_b.ADC12B_RESET       = 0;
    AUXADC->XADC12B_CTRL_REG_b.ADC12B_PWRDOEN     = 0;
    AUXADC->XADC12B_CTRL_REG_b.ADC12B_DATA_FORMAT = 1;

    AUXADC->XADC12B_DMA_EN_REG         = 0;
    AUXADC->XADC12B_INT_THR_OVER_REG   = 0xffff;
    AUXADC->XADC12B_INT_THR_UNDER_REG  = 0x0;
    AUXADC->XADC12B_INT_THR_DIFF_REG   = 0xfff0;
    AUXADC->XADC12B_THR_INTR_MASK_REG  = 0;
    AUXADC->XADC12B_FIFO_INTR_MASK_REG = 0;

    /* For each channel */
    uint32_t scan_mask = 0U;
    for (uint32_t i = 0U; i < BSP_FEATURE_ADC_W_MAX_NUM_CHANNELS; i++)
    {
        if (NULL != p_ext->p_channel_cfgs[i])
        {
            /* Enable conversion for the channel. */
            scan_mask |= (1U << i);
        }
    }

    p_instance_ctrl->scan_mask     = 0;
    p_instance_ctrl->scan_cfg_mask = scan_mask;

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures the enabled channels of the ADC. Channel specific settings are set in this function. Pass a pointer to
 * @ref adc_w_scan_cfg_t to p_extend.
 * Implements @ref adc_api_t::scanCfg.
 *
 * @retval FSP_SUCCESS                    Channel specific settings applied.
 * @retval FSP_ERR_ASSERTION              An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN               Unit is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_ScanCfg (adc_ctrl_t * p_ctrl, void const * const p_scan_cfg)
{
    adc_w_instance_ctrl_t  * p_instance_ctrl    = (adc_w_instance_ctrl_t *) p_ctrl;
    adc_w_scan_cfg_t const * p_channel_scan_cfg = (adc_w_scan_cfg_t const *) p_scan_cfg;

#if ADC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_channel_scan_cfg);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);

    fsp_err_t err = r_adc_w_scan_cfg_check(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Verify all channels to enable are configured. */
    FSP_ASSERT(p_instance_ctrl->scan_cfg_mask == (p_channel_scan_cfg->scan_mask | p_instance_ctrl->scan_cfg_mask));
#endif

    adc_w_extended_cfg_t * p_ext = (adc_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    uint16_t div = p_ext->conversion_clockdiv;

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* PLL divider enable for Aux 15Mhz */
    CRG_TOP->CLK_CTRL_REG_b.PLL_AUX_ENABLE = 0;
    CRG_TOP->CLK_AMBA_REG_b.AUX_CLK_ENABLE = 0;

    CRG_PER->RESET_CLK_COM_REG_b.AUXADC_ENABLE = 1;

    CRG_TOP->AUX_CLK_DIV_REG = (uint32_t) (div - 1);

    /* PLL divider enable for Aux 15Mhz */
    CRG_TOP->CLK_CTRL_REG_b.PLL_AUX_ENABLE   = 1;
    CRG_TOP->CLK_AMBA_REG_b.AUX_CLK_ENABLE   = 1;
    CRG_PER->SET_CLK_COM_REG_b.AUXADC_ENABLE = 1;

    FSP_CRITICAL_SECTION_EXIT;

    uint32_t enabled_ch_mask = p_channel_scan_cfg->scan_mask;

#if ADC_W_CFG_INTERRUPT_SUPPORT_ENABLE

    /* This feature is not available. */
    AUXADC->XADC12B_INT_THR_DIFF_REG = 0;

    for (uint8_t channel = ADC_CHANNEL_0; channel < BSP_FEATURE_ADC_W_MAX_NUM_CHANNELS; channel++)
    {
        if (enabled_ch_mask & (1U << channel))
        {
            if (p_ext->p_channel_cfgs[channel]->interrupt_mode_thd)
            {
                AUXADC->XADC12B_THR_INTR_MASK_REG |= (p_ext->p_channel_cfgs[channel]->interrupt_mode_thd << channel);

                if (ADC_W_INTERRUPT_THD_OVER == p_ext->p_channel_cfgs[channel]->interrupt_mode_thd)
                {
                    AUXADC->XADC12B_INT_THR_OVER_REG = p_ext->upper_bound_limit;
                }
                else if (ADC_W_INTERRUPT_THD_UNDER == p_ext->p_channel_cfgs[channel]->interrupt_mode_thd)
                {
                    AUXADC->XADC12B_INT_THR_UNDER_REG = p_ext->lower_bound_limit;
                }
                else
                {
                    ;
                }
            }
            else
            {
                AUXADC->XADC12B_THR_INTR_MASK_REG &=
                    (uint32_t) ~(p_ext->p_channel_cfgs[channel]->interrupt_mode_thd << channel);
            }

            if (p_ext->p_channel_cfgs[channel]->interrupt_mode_fifo)
            {
                AUXADC->XADC12B_FIFO_INTR_MASK_REG |= (p_ext->p_channel_cfgs[channel]->interrupt_mode_fifo << channel);
            }
            else
            {
                AUXADC->XADC12B_FIFO_INTR_MASK_REG &=
                    (uint32_t) ~(p_ext->p_channel_cfgs[channel]->interrupt_mode_fifo << channel);
            }
        }
    }

    AUXADC->XADC12B_THR_INTR_CLR_REG = 0xfff;

    R_BSP_IrqCfgEnable(p_instance_ctrl->p_cfg->scan_end_irq, p_instance_ctrl->p_cfg->scan_end_ipl, p_instance_ctrl);
#endif

    uint8_t used_channel_num = 0;

    for (uint8_t channel = ADC_CHANNEL_0; channel < BSP_FEATURE_ADC_W_MAX_NUM_CHANNELS; channel++)
    {
        if (enabled_ch_mask & (1U << channel))
        {
            used_channel_num++;

            r_adc_w_ldo_enable(channel);

            if (ADC_W_DMA_ENABLED == p_ext->p_channel_cfgs[channel]->dma_en)
            {
                AUXADC->XADC12B_DMA_EN_REG |= 1 << channel;
            }
            else
            {
                AUXADC->XADC12B_DMA_EN_REG &= (uint32_t) ~(1 << channel);
            }
        }
    }

    /* When using multiple channels at the same time, the ADC sample data can be stored correctly in the FIFO
     * with latency of at least 4-cycles after the channel change. */
    if (1 == used_channel_num)
    {
        AUXADC->XADC12B_ST_SAMPLE_REG_b.XADC12B_SP_INTERVAL = 0;
    }
    else
    {
        AUXADC->XADC12B_ST_SAMPLE_REG_b.XADC12B_SP_INTERVAL = 4;
    }

    /* Update the enabled channels. */
    p_instance_ctrl->scan_mask = p_channel_scan_cfg->scan_mask;

#if ADC_W_CFG_PARAM_CHECKING_ENABLE

    /* Mark driver as initialized */
    p_instance_ctrl->initialized = ADC_W_OPEN;
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback.
 * Implements adc_api_t::callbackSet
 *
 * @retval FSP_SUCCESS                  Callback updated successfully.
 * @retval FSP_ERR_NOT_OPEN             Unit is not open.
 * @retval FSP_ERR_ASSERTION            A required pointer is NULL.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_CallbackSet (adc_ctrl_t * const          p_api_ctrl,
                               void (                    * p_callback)(adc_callback_args_t *),
                               void * const                p_context,
                               adc_callback_args_t * const p_callback_memory)
{
    adc_w_instance_ctrl_t * p_ctrl = (adc_w_instance_ctrl_t *) p_api_ctrl;
    FSP_PARAMETER_NOT_USED(p_callback_memory);

#if ADC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_callback);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function starts the software triggered scan.
 *
 * @pre Call R_ADC_W_ScanCfg after R_ADC_W_Open before starting a scan.
 * @retval FSP_SUCCESS                 Scan started.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            ADC_W is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     ADC_W is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_ScanStart (adc_ctrl_t * p_ctrl)
{
    adc_w_instance_ctrl_t * p_instance_ctrl = (adc_w_instance_ctrl_t *) p_ctrl;

    /* Perform parameter checking */
#if ADC_W_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    AUXADC->SWITCHING_MODE_REG = AUXADC->SWITCHING_MODE_REG & (uint32_t) 0xff;

    for (uint8_t channel = ADC_CHANNEL_0; channel < BSP_FEATURE_ADC_W_MAX_NUM_CHANNELS; channel++)
    {
        if (p_instance_ctrl->scan_mask & (1U << channel))
        {
            AUXADC->SWITCHING_MODE_REG = AUXADC->SWITCHING_MODE_REG & (uint32_t) ~((1 << channel));
            AUXADC->SWITCHING_MODE_REG = AUXADC->SWITCHING_MODE_REG | (uint32_t) ((1 << (channel + 4)));
        }
    }

    AUXADC->SWITCHING_MODE_REG = AUXADC->SWITCHING_MODE_REG | (uint32_t) (0x100);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::scanGroupStart is not supported on the ADC_W. Use scanStart instead.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_ScanGroupStart (adc_ctrl_t * p_ctrl, adc_group_mask_t group_id)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(group_id);

    /* Return the unsupported error. */
    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Immediately stops converters.
 * This function will abort conversions.
 *
 * @retval FSP_SUCCESS                 Scan stopped.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_ScanStop (adc_ctrl_t * p_ctrl)
{
    /* Perform parameter checking */
#if ADC_W_CFG_PARAM_CHECKING_ENABLE
    adc_w_instance_ctrl_t * p_instance_ctrl = (adc_w_instance_ctrl_t *) p_ctrl;

    /* Verify the pointers are valid */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    AUXADC->SWITCHING_MODE_REG = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the status of any scan process that was started.
 *
 *
 * @retval FSP_SUCCESS                 Module status stored in the provided pointer p_status.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            ADC_W is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_StatusGet (adc_ctrl_t * p_ctrl, adc_status_t * p_status)
{
    adc_w_instance_ctrl_t * p_instance_ctrl = (adc_w_instance_ctrl_t *) p_ctrl;
#if ADC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    uint32_t status;

    status          = AUXADC->SWITCHING_MODE_REG & 0xF0;
    p_status->state = (status ? ADC_STATE_SCAN_IN_PROGRESS : ADC_STATE_IDLE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads conversion results from a channel register.
 *
 *
 * @retval FSP_SUCCESS                 Data read into provided p_data.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_Read (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data)
{
    adc_w_instance_ctrl_t * p_instance_ctrl = (adc_w_instance_ctrl_t *) p_ctrl;

#if ADC_W_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
    FSP_ERROR_RETURN(((ADC_CHANNEL_0 <= reg_id) && (reg_id <= ADC_CHANNEL_3)), FSP_ERR_ASSERTION);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    switch (reg_id)
    {
        case ADC_CHANNEL_0:
        {
            *p_data = AUXADC->FIFO0_DATA_CURR_REG_b.FIFO0_CURR_DATA;
            break;
        }

        case ADC_CHANNEL_1:
        {
            *p_data = AUXADC->FIFO1_DATA_CURR_REG_b.FIFO1_CURR_DATA;
            break;
        }

        case ADC_CHANNEL_2:
        {
            *p_data = AUXADC->FIFO2_DATA_CURR_REG_b.FIFO2_CURR_DATA;
            break;
        }

        case ADC_CHANNEL_3:
        {
            *p_data = AUXADC->FIFO3_DATA_CURR_REG_b.FIFO3_CURR_DATA;
            break;
        }

        default:
        {
            break;
        }
    }

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads conversion results from a channel register into a 32-bit result.
 *
 *
 * @retval FSP_SUCCESS                 Data read into provided p_data.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            ADC_W is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     ADC_W is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_Read32 (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data)
{
    uint16_t result = 0U;

#if ADC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_data);
#endif

    fsp_err_t err = R_ADC_W_Read(p_ctrl, reg_id, &result);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    *p_data = result;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Returns the address of the lowest number configured channel, determine the size of data that must be read.
 *
 * @retval FSP_SUCCESS                 Information stored in p_adc_info.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            ADC_W is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     ADC_W is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_InfoGet (adc_ctrl_t * p_ctrl, adc_info_t * p_adc_info)
{
    adc_w_instance_ctrl_t * p_instance_ctrl = (adc_w_instance_ctrl_t *) p_ctrl;

#if ADC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_adc_info);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    /* Retrieve the scan mask of active channels from the control block */
    uint32_t scan_mask = p_instance_ctrl->scan_mask;

    if (0U == scan_mask)
    {
        p_adc_info->length    = 0U;
        p_adc_info->p_address = NULL;
    }
    else
    {
        /* Determine the lowest channel that is configured. */
        uint32_t temp_mask      = 0U;
        int32_t  lowest_channel = -1;
        while (0U == temp_mask)
        {
            lowest_channel++;
            temp_mask = (uint32_t) (scan_mask & (1U << lowest_channel));
        }

        /* Determine the size of data that must be read to read all the channels. */
        uint32_t enabled_channel_num = 0;
        for (uint32_t temp_channel = 0; temp_channel < BSP_FEATURE_ADC_W_MAX_NUM_CHANNELS; temp_channel++)
        {
            if (scan_mask & (1U << temp_channel))
            {
                enabled_channel_num++;
            }
        }

        p_adc_info->length    = enabled_channel_num;
        p_adc_info->p_address = (uint32_t *) (ADC_CH0_DMAC_SRC_ADDR + lowest_channel);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function ends any scan or select mode in progress, disables interrupts, and removes power to the A/D peripheral.
 *
 * @retval FSP_SUCCESS                 Module closed.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            ADC_W is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_Close (adc_ctrl_t * p_ctrl)
{
    adc_w_instance_ctrl_t * p_instance_ctrl = (adc_w_instance_ctrl_t *) p_ctrl;

#if ADC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);

    /* Mark driver as closed */
    p_instance_ctrl->opened      = 0U;
    p_instance_ctrl->initialized = 0U;
#endif
#if ADC_W_CFG_INTERRUPT_SUPPORT_ENABLE

    /* Disable interrupts. */
    if (p_instance_ctrl->p_cfg->scan_end_irq > 0)
    {
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->scan_end_irq);
    }
#endif
#if !ADC_W_CFG_INTERRUPT_SUPPORT_ENABLE && !ADC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    AUXADC->XADC12B_INT_THR_OVER_REG  = 0xffff;
    AUXADC->XADC12B_INT_THR_UNDER_REG = 0x0;
    AUXADC->XADC12B_INT_THR_DIFF_REG  = 0xfff0;

    AUXADC->XADC12B_THR_INTR_MASK_REG  = 0;
    AUXADC->XADC12B_FIFO_INTR_MASK_REG = 0;

    if (p_instance_ctrl->p_callback)
    {
        p_instance_ctrl->p_callback = NULL;
    }

    AUXADC->SWITCHING_MODE_REG = 0;

    AUXADC->XADC12B_DMA_EN_REG = 0;

    AUXADC->XADC12B_CTRL_REG_b.ADC12B_RESET   = 1;
    AUXADC->XADC12B_CTRL_REG_b.ADC12B_PWRDOEN = 1;

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    RTC->LDO_ENABLE2_REG_b.EN_TST_GPIO0 = 0;
    RTC->LDO_ENABLE2_REG_b.EN_TST_GPIO1 = 0;
    RTC->LDO_ENABLE2_REG_b.EN_TST_GPIO2 = 0;
    RTC->LDO_ENABLE2_REG_b.EN_TST_GPIO3 = 0;

    CRG_TOP->CLK_AMBA_REG_b.AUX_CLK_ENABLE = 0;

    RTC->XADC12_THR01_REG = 0;
    RTC->XADC12_THR23_REG = 0;

    RTC->XADC12_TIMER_SET_REG_b.X12_CLK_TMR_CNT_SRC = 0;
    RTC->XADC12_TIMER_SET_REG_b.AX12B_TIMER_VAL     = 0xf;
    RTC->XADC12_TIMER_SET_REG_b.ASWCH_CTRL          = 0;

    RTC->XADC12_SP_NUM_REG_b.ADC_SMLP_NUM_AVR = 0;

    /* Disable sensor detection */
    RTC->XADC12_TIMER_SET_REG_b.SENSOR_DETECT_ACT = 0;

    /* Disable CLOCK for adc sensor and pulse cnt functions */
    RTC->ENABLE_CTRL_REG_b.REAL_CNT_LOAD = 0;

    FSP_CRITICAL_SECTION_EXIT;

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::calibrate is not supported on the ADC_W.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_Calibrate (adc_ctrl_t * const p_ctrl, void const * p_extend)
{
    FSP_PARAMETER_NOT_USED(p_extend);
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_ERROR_LOG(FSP_ERR_UNSUPPORTED);

    /* Return the unsupported error. */
    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::offsetSet is not supported on the ADC_W.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_OffsetSet (adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t offset)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(reg_id);
    FSP_PARAMETER_NOT_USED(offset);
    FSP_ERROR_LOG(FSP_ERR_UNSUPPORTED);

    /* Return the unsupported error. */
    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Prepare ADC_W to enter sensor wakeup mode.
 * This function must be called before entering sleep mode.
 *
 * @param[in] p_ctrl              Pointer to the ADC control block
 *
 * @retval FSP_SUCCESS            ADC is configured to request sensor wakeup mode.
 * @retval FSP_ERR_ASSERTION      An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN       ADC_W is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_SensorWakeupcfg (adc_ctrl_t * const p_ctrl)
{
    adc_w_instance_ctrl_t * p_instance_ctrl = (adc_w_instance_ctrl_t *) p_ctrl;

#if ADC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);

    /* Verify that the ADC instance is in the correct mode for requesting sensor wakeup mode. */
    fsp_err_t err = r_adc_w_SensorWakeup_cfg_check(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    R_BSP_SoftwareDelay(120, BSP_DELAY_UNITS_MICROSECONDS);
#endif

    adc_w_extended_cfg_t * p_ext = (adc_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    uint8_t aswch_reg = 0;

    for (uint8_t channel = 0U; channel < BSP_FEATURE_ADC_W_MAX_NUM_CHANNELS; channel++)
    {
        if (NULL != p_ext->p_channel_cfgs[channel])
        {
            if (ADC_W_SENSOR_WAKEUP_ENABLED == p_ext->p_channel_cfgs[channel]->sensorwakeup_en)
            {
                aswch_reg |= (1 << 4);
                aswch_reg  = aswch_reg & ((uint8_t) ~(1 << (channel)));
                aswch_reg  = aswch_reg | ((uint8_t) (1 << (channel)));

                RTC->XADC12_TIMER_SET_REG_b.ASWCH_CTRL = ADC_W_5BIT_MASK & aswch_reg;

                switch (channel)
                {
                    case ADC_CHANNEL_0:
                    {
                        RTC->XADC12_THR01_REG_b.XADC12_THR_LEVEL0_CH0 = ADC_W_12BIT_MASK &
                                                                        p_ext->p_channel_cfgs[channel]->thd_value;
                        RTC->XADC12_THR01_REG_b.XADC12_THR_CONFIG_CH0 = p_ext->p_channel_cfgs[channel]->threshold_mode;
                        r_adc_w_ldo_enable(ADC_CHANNEL_0);
                        break;
                    }

                    case ADC_CHANNEL_1:
                    {
                        RTC->XADC12_THR01_REG_b.XADC12_THR_LEVEL1_CH2 = ADC_W_12BIT_MASK &
                                                                        p_ext->p_channel_cfgs[channel]->thd_value;
                        RTC->XADC12_THR01_REG_b.XADC12_THR_CONFIG_CH1 = p_ext->p_channel_cfgs[channel]->threshold_mode;
                        r_adc_w_ldo_enable(ADC_CHANNEL_1);
                        break;
                    }

                    case ADC_CHANNEL_2:
                    {
                        RTC->XADC12_THR23_REG_b.XADC12_THR_LEVEL2_CH2 = ADC_W_12BIT_MASK &
                                                                        p_ext->p_channel_cfgs[channel]->thd_value;
                        RTC->XADC12_THR23_REG_b.XADC12_THR_CONFIG_CH2 = p_ext->p_channel_cfgs[channel]->threshold_mode;
                        r_adc_w_ldo_enable(ADC_CHANNEL_2);
                        break;
                    }

                    case ADC_CHANNEL_3:
                    {
                        RTC->XADC12_THR23_REG_b.XADC12_THR_LEVEL3_CH3 = ADC_W_12BIT_MASK &
                                                                        p_ext->p_channel_cfgs[channel]->thd_value;
                        RTC->XADC12_THR23_REG_b.XADC12_THR_CONFIG_CH3 = p_ext->p_channel_cfgs[channel]->threshold_mode;
                        r_adc_w_ldo_enable(ADC_CHANNEL_3);
                        break;
                    }

                    default:
                    {
                        break;
                    }
                }
            }
        }
    }

    /* Setting the AD conversion period */
    RTC->XADC12_TIMER_SET_REG_b.X12_CLK_TMR_CNT_SRC = p_ext->timer_count_clock_source;
    RTC->XADC12_TIMER_SET_REG_b.AX12B_TIMER_VAL     = 0xFU & p_ext->timer_value;

    RTC->XADC12_SP_NUM_REG_b.ADC_SMLP_NUM_AVR = p_ext->sample_average;

    /* Sensor detect activate */
    RTC->XADC12_TIMER_SET_REG_b.SENSOR_DETECT_ACT = 1;

    /* CLOCK enable for adc sensor and pulse cnt functions */
    RTC->ENABLE_CTRL_REG_b.REAL_CNT_LOAD = 1;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads conversion results from FIFO for the given channel.
 * When reading multiple data from the FIFO, call this function repeatedly.
 *
 * @retval FSP_SUCCESS                 Data read into provided p_data.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_W_FifoRead (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data)
{
#if ADC_W_CFG_PARAM_CHECKING_ENABLE
    adc_w_instance_ctrl_t * p_instance_ctrl = (adc_w_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_W_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
    FSP_ERROR_RETURN(((ADC_CHANNEL_0 <= reg_id) && (reg_id <= ADC_CHANNEL_3)), FSP_ERR_ASSERTION);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    switch (reg_id)
    {
        case ADC_CHANNEL_0:
        {
            *p_data = AUXADC->FIFO0_DMA_DATA_REG_b.FIFO0_DMA_DATA;
            break;
        }

        case ADC_CHANNEL_1:
        {
            *p_data = AUXADC->FIFO1_DMA_DATA_REG_b.FIFO1_DMA_DATA;
            break;
        }

        case ADC_CHANNEL_2:
        {
            *p_data = AUXADC->FIFO2_DMA_DATA_REG_b.FIFO2_DMA_DATA;
            break;
        }

        case ADC_CHANNEL_3:
        {
            *p_data = AUXADC->FIFO3_DMA_DATA_REG_b.FIFO3_DMA_DATA;
            break;
        }

        default:
        {
            break;
        }
    }

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup ADC_W)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if ADC_W_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Validate the configuration when ADC_W channel is configured
 *
 * @param[in] p_ctrl                      Pointer to instance control block
 *
 * @retval FSP_SUCCESS                    No configuration errors detected.
 * @retval FSP_ERR_ASSERTION              An input argument is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_adc_w_scan_cfg_check (adc_w_instance_ctrl_t * const p_ctrl)
{
    adc_w_instance_ctrl_t * p_instance_ctrl = p_ctrl;
    adc_w_extended_cfg_t  * p_extend        = (adc_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

 #if ADC_W_CFG_INTERRUPT_SUPPORT_ENABLE
    FSP_ERROR_RETURN(((0x0U <= p_extend->upper_bound_limit) && (p_extend->upper_bound_limit <= 0xFFFFU)),
                     FSP_ERR_ASSERTION);
    FSP_ERROR_RETURN(((0x0U <= p_extend->lower_bound_limit) && (p_extend->lower_bound_limit <= 0xFFFFU)),
                     FSP_ERR_ASSERTION);

    /* Currently ADC_W_INTERRUPT_FIFO_FULL is not supported. */
    for (uint8_t channel = ADC_CHANNEL_0; channel < BSP_FEATURE_ADC_W_MAX_NUM_CHANNELS; channel++)
    {
        if (NULL != p_extend->p_channel_cfgs[channel])
        {
            FSP_ERROR_RETURN(((ADC_W_INTERRUPT_FIFO_NONE == p_extend->p_channel_cfgs[channel]->interrupt_mode_fifo) ||
                              (ADC_W_INTERRUPT_FIFO_HALF == p_extend->p_channel_cfgs[channel]->interrupt_mode_fifo)),
                             FSP_ERR_ASSERTION);
        }
    }
 #endif

    /* Get the frequency of the clock supplying the ADC */
    uint32_t clock_frequency_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_AUX_ADC);

    if (clock_frequency_hz == 40000000)
    {
        FSP_ERROR_RETURN(((3 <= p_extend->conversion_clockdiv) && (p_extend->conversion_clockdiv <= 1024)),
                         FSP_ERR_ASSERTION);
    }
    else
    {
        FSP_ERROR_RETURN(((1 <= p_extend->conversion_clockdiv) && (p_extend->conversion_clockdiv <= 1024)),
                         FSP_ERR_ASSERTION);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Validates the configuration arguments for illegal combinations or options.
 *
 * @param[in] p_cfg                        Pointer to configuration structure.
 *
 * @retval FSP_SUCCESS                     No configuration errors detected.
 * @retval FSP_ERR_ASSERTION               An input argument is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_adc_w_open_cfg_check (adc_cfg_t const * const p_cfg)
{
    /* Check if p_cfg is NULL. */
    FSP_ASSERT(NULL != p_cfg);

    adc_w_extended_cfg_t const * p_extend = (adc_w_extended_cfg_t const *) p_cfg->p_extend;

    /* Get the frequency of the clock supplying the ADC */
    uint32_t clock_frequency_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_AUX_ADC);

    if (clock_frequency_hz == 40000000)
    {
        FSP_ERROR_RETURN(((3 <= p_extend->conversion_clockdiv) && (p_extend->conversion_clockdiv <= 1024)),
                         FSP_ERR_ASSERTION);
    }
    else
    {
        FSP_ERROR_RETURN(((1 <= p_extend->conversion_clockdiv) && (p_extend->conversion_clockdiv <= 1024)),
                         FSP_ERR_ASSERTION);
    }

    FSP_ERROR_RETURN(((ADC_RESOLUTION_12_BIT <= p_cfg->resolution) && (p_cfg->resolution <= ADC_RESOLUTION_4_BIT)),
                     FSP_ERR_ASSERTION);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Validates the configuration arguments for illegal combinations or options.
 *
 * @param[in] p_ctrl                      Pointer to instance control block
 *
 * @retval FSP_SUCCESS                    No configuration errors detected.
 * @retval FSP_ERR_ASSERTION              An input argument is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_adc_w_SensorWakeup_cfg_check (adc_w_instance_ctrl_t * const p_ctrl)
{
    adc_w_instance_ctrl_t * p_instance_ctrl = p_ctrl;
    adc_w_extended_cfg_t  * p_ext           = (adc_w_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    for (uint32_t channel = 0U; channel < BSP_FEATURE_ADC_W_MAX_NUM_CHANNELS; channel++)
    {
        if (NULL != p_ext->p_channel_cfgs[channel])
        {
            if (ADC_W_SENSOR_WAKEUP_ENABLED == p_ext->p_channel_cfgs[channel]->sensorwakeup_en)
            {
                FSP_ERROR_RETURN((p_ext->p_channel_cfgs[channel]->thd_value <= 0xFFFU), FSP_ERR_ASSERTION);
            }
        }
    }

    FSP_ERROR_RETURN(((1 <= p_ext->timer_value) && (p_ext->timer_value <= 0xF)), FSP_ERR_ASSERTION);

    return FSP_SUCCESS;
}

#endif

#if ADC_W_CFG_INTERRUPT_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * This function implements the interrupt handler for trigger scan complete.
 **********************************************************************************************************************/
void adc_w_scan_end_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    adc_w_instance_ctrl_t * p_instance_ctrl = (adc_w_instance_ctrl_t *) R_FSP_IsrContextGet(R_FSP_CurrentIrqGet());

    uint32_t interrupt_flag = AUXADC->XADC12B_INTR_STATUS_REG;

    /* Clear the interrupt status */
    AUXADC->XADC12B_THR_INTR_CLR_REG = (interrupt_flag >> 8);

    /* If a callback was provided, call it with the argument */
    if (NULL != p_instance_ctrl->p_callback)
    {
        adc_callback_args_t args;
        uint32_t            interrupt_ch_flag =
            ((ADC_W_INTERRUPT_THD_OVER | ADC_W_INTERRUPT_THD_UNDER | ADC_W_INTERRUPT_THD_DIFF) << 8) |
            ADC_W_INTERRUPT_FIFO_HALF | ADC_W_INTERRUPT_FIFO_FULL;

        /* Store the unit number into the callback argument */
        args.unit = p_instance_ctrl->p_cfg->unit;

        /* Populate the context field. */
        args.p_context = p_instance_ctrl->p_context;

        /* Not used */
        args.channel_mask = 0;
        args.group_mask   = 0;

        for (uint8_t channel = ADC_CHANNEL_0; channel < BSP_FEATURE_ADC_W_MAX_NUM_CHANNELS; channel++)
        {
            if (interrupt_flag & (interrupt_ch_flag << channel))
            {
                /* Return the channel */
                args.channel = channel;

                /* fifo_half and thd_over/under interrupts can occur simultaneously */
                if (interrupt_flag & (ADC_W_INTERRUPT_FIFO_HALF << channel))
                {
                    args.event = ADC_EVENT_FIFO_READ_REQUEST;

                    /* Call the callback. */
                    p_instance_ctrl->p_callback(&args);
                }

                if (interrupt_flag & ((ADC_W_INTERRUPT_THD_OVER << 8) << channel))
                {
                    args.event = ADC_EVENT_THD_OVER;

                    /* Call the callback. */
                    p_instance_ctrl->p_callback(&args);
                }
                else if (interrupt_flag & ((ADC_W_INTERRUPT_THD_UNDER << 8) << channel))
                {
                    args.event = ADC_EVENT_THD_UNDER;

                    /* Call the callback. */
                    p_instance_ctrl->p_callback(&args);
                }
                else
                {
                    ;
                }
            }
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#endif

static void r_adc_w_ldo_enable (adc_channel_t channel)
{
    FSP_CRITICAL_SECTION_DEFINE;

    if (bsp_is_chip_revision_a())
    {
        FSP_CRITICAL_SECTION_ENTER;

        switch (channel)
        {
            case ADC_CHANNEL_0:
            {
                RTC->LDO_ENABLE2_REG_b.EN_TST_GPIO3 = 1;
                break;
            }

            case ADC_CHANNEL_1:
            {
                RTC->LDO_ENABLE2_REG_b.EN_TST_GPIO0 = 1;
                break;
            }

            case ADC_CHANNEL_2:
            {
                RTC->LDO_ENABLE2_REG_b.EN_TST_GPIO1 = 1;
                break;
            }

            case ADC_CHANNEL_3:
            {
                RTC->LDO_ENABLE2_REG_b.EN_TST_GPIO2 = 1;
                break;
            }

            default:
            {
                break;
            }
        }

        FSP_CRITICAL_SECTION_EXIT;
    }
    else                               /* revision B or later */
    {
        FSP_CRITICAL_SECTION_ENTER;

        switch (channel)
        {
            case ADC_CHANNEL_0:
            {
                RTC->LDO_ENABLE2_REG_b.EN_TST_GPIO0 = 1;
                break;
            }

            case ADC_CHANNEL_1:
            {
                RTC->LDO_ENABLE2_REG_b.EN_TST_GPIO1 = 1;
                break;
            }

            case ADC_CHANNEL_2:
            {
                RTC->LDO_ENABLE2_REG_b.EN_TST_GPIO2 = 1;
                break;
            }

            case ADC_CHANNEL_3:
            {
                RTC->LDO_ENABLE2_REG_b.EN_TST_GPIO3 = 1;
                break;
            }

            default:
            {
                break;
            }
        }

        FSP_CRITICAL_SECTION_EXIT;
    }
}

/* End of file R_ADC_W. */
