/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_dmac_w.h"
#include "r_dmac_w_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Driver ID (DMAC in ASCII) */
#define DMAC_ID    (0x444d4143)

/* Calculate the mask bits for byte alignment from the transfer_size_t. */
#define DMAC_PRV_MASK_ALIGN_N_BYTES(x)    ((1U << (x)) - 1U)

#define DMAC_PRV_REG(ch)                  (DMA_Type *) (&DMA->DMA0_A_START_REG + \
                                                        (&DMA->DMA1_A_START_REG - &DMA->DMA0_A_START_REG) * (ch))

#define DMAC_PRV_MUX_SEL_MASK            (DMA_DMA_REQ_MUX_REG_DMA0_SEL_Msk)

#define DMAC_PRV_MUX_SEL_BITS            (DMA_DMA_REQ_MUX_REG_DMA1_SEL_Pos - DMA_DMA_REQ_MUX_REG_DMA0_SEL_Pos)

#define DMAC_PRV_MUX_CH_OFFSET           (4)

#define DMAC_PRV_CHANNEL_PRIO_HIGHEST    (7)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void dmac_w_int_isr(void);

static void      r_dmac_w_config_transfer_info(dmac_instance_ctrl_t * p_ctrl, transfer_info_t * p_info);
static fsp_err_t r_dmac_w_channel_enable(dmac_instance_ctrl_t * p_ctrl);
static void      r_dmac_w_peripherals_map(dmac_instance_ctrl_t * const p_ctrl);
static void      r_dmac_w_peripherals_unmap(uint8_t channel);
static void      r_dmac_w_interrupt_handle(dmac_instance_ctrl_t * const p_ctrl);
static void      r_dmac_w_irq_enable(dmac_instance_ctrl_t * const p_ctrl);
static void      r_dmac_w_irq_disable(dmac_instance_ctrl_t * const p_ctrl);
static void      r_dmac_w_dma_mux_reg_set(uint8_t channel, bsp_dmac_trig_t periph_trigger);

#if DMAC_W_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_dma_open_parameter_checking(dmac_instance_ctrl_t * const p_ctrl, transfer_cfg_t const * const p_cfg);
static fsp_err_t r_dmac_w_reconfigure_parameter_checking(transfer_info_t const * const p_info);
static fsp_err_t r_dmac_w_enable_parameter_checking(dmac_instance_ctrl_t * const p_ctrl);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

#if BSP_FEATURE_DMAC_HAS_SHARED_IRQ
static dmac_instance_ctrl_t * volatile gp_dmac_ctrls[BSP_FEATURE_DMAC_MAX_CHANNEL];
#endif

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** DMAC implementation of transfer API. */
const transfer_api_t g_transfer_on_dmac_w =
{
    .open          = R_DMAC_W_Open,
    .reconfigure   = R_DMAC_W_Reconfigure,
    .reset         = R_DMAC_W_Reset,
    .infoGet       = R_DMAC_W_InfoGet,
    .softwareStart = R_DMAC_W_SoftwareStart,
    .softwareStop  = R_DMAC_W_SoftwareStop,
    .enable        = R_DMAC_W_Enable,
    .disable       = R_DMAC_W_Disable,
    .reload        = R_DMAC_W_Reload,
    .callbackSet   = R_DMAC_W_CallbackSet,
    .close         = R_DMAC_W_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup DMAC_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configure a DMAC channel.
 *
 * Example:
 * @snippet r_dmac_w_example.c R_DMAC_W_Open
 *
 * @retval FSP_SUCCESS                    Successful open.
 * @retval FSP_ERR_ASSERTION              An input parameter is invalid.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The configured channel is invalid.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       The IRQ associated with the activation source is not enabled in the BSP.
 * @retval FSP_ERR_ALREADY_OPEN           The control structure is already opened.
 * @retval FSP_ERR_UNSUPPORTED            A Selected setting is not supported by this API.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_W_Open (transfer_ctrl_t * const p_api_ctrl, transfer_cfg_t const * const p_cfg)
{
#if DMAC_W_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = FSP_SUCCESS;
    err = r_dma_open_parameter_checking(p_api_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    dmac_instance_ctrl_t * p_ctrl   = (dmac_instance_ctrl_t *) p_api_ctrl;
    dmac_extended_cfg_t  * p_extend = (dmac_extended_cfg_t *) p_cfg->p_extend;

    p_ctrl->p_cfg = p_cfg;
    p_ctrl->p_reg = (DMA_Type *) DMAC_PRV_REG(p_extend->channel);

    /* Set callback and context pointers, if configured */
    p_ctrl->p_callback        = p_extend->p_callback;
    p_ctrl->p_context         = p_extend->p_context;
    p_ctrl->p_callback_memory = NULL;

    /* Configure the transfer settings. */
    r_dmac_w_config_transfer_info(p_ctrl, p_cfg->p_info);

    /* Mark driver as open by initializing "DMAC" in its ASCII equivalent.*/
    p_ctrl->open = DMAC_ID;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reconfigure the transfer with new transfer info.
 *
 * @retval FSP_SUCCESS              Transfer is configured and will start when R_DMAC_W_Enable() is called.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_UNSUPPORTED      A Selected setting is not supported by this API.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_W_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_W_Reconfigure (transfer_ctrl_t * const p_api_ctrl, transfer_info_t * p_info)
{
    fsp_err_t              err;
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;

#if DMAC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(DMAC_ID == p_ctrl->open, FSP_ERR_NOT_OPEN);
    err = r_dmac_w_reconfigure_parameter_checking(p_info);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(err);
#endif

    /* Reconfigure the transfer settings. */
    r_dmac_w_config_transfer_info(p_ctrl, p_info);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reset transfer source and destination.
 *
 * @retval FSP_ERR_UNSUPPORTED      This feature is not supported.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_W_Reset (transfer_ctrl_t * const p_api_ctrl,
                          void const * volatile   p_src,
                          void * volatile         p_dest,
                          uint16_t const          num_transfers)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_src);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(num_transfers);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * If the mode is TRANSFER_START_MODE_SINGLE initiate a single transfer with software. If the mode is
 * TRANSFER_START_MODE_REPEAT continue triggering transfers until all of the transfers are completed.
 *
 * @retval FSP_ERR_UNSUPPORTED      This feature is not supported.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_W_SoftwareStart (transfer_ctrl_t * const p_api_ctrl, transfer_start_mode_t mode)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(mode);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Stop software transfers if they were started with TRANSFER_START_MODE_REPEAT.
 *
 * @retval FSP_ERR_UNSUPPORTED      This feature is not supported.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_W_SoftwareStop (transfer_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Enable a DMAC channel.
 *
 * Example:
 * @snippet r_dmac_w_example.c R_DMAC_W_Enable
 *
 * @retval FSP_SUCCESS              DMAC channel activated successfully.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_W_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_W_Enable (transfer_ctrl_t * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(DMAC_ID == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    fsp_err_t err = r_dmac_w_channel_enable(p_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * Disable a Dmac channel.
 *
 * @retval FSP_SUCCESS              DMAC channel disabled successfully.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_W_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_W_Disable (transfer_ctrl_t * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(DMAC_ID == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    p_ctrl->p_reg->DMA0_CTRL_REG_b.DMA_ON = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set driver specific information in provided pointer.
 *
 * @retval FSP_SUCCESS              Information has been written to p_info.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_W_Open to initialize the control block.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_W_InfoGet (transfer_ctrl_t * const p_api_ctrl, transfer_properties_t * const p_info)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(DMAC_ID == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_info);
#endif

    p_info->block_count_remaining = 0U;
    p_info->block_count_max       = 0U;
    p_info->transfer_length_max   = DMAC_MAX_NORMAL_TRANSFER_LENGTH;

    if ((p_ctrl->p_reg->DMA0_LEN_REG == p_ctrl->p_reg->DMA0_IDX_REG) && (0U != p_ctrl->p_reg->DMA0_LEN_REG))
    {
        p_info->transfer_length_remaining = 0U;
    }
    else
    {
        p_info->transfer_length_remaining = (p_ctrl->p_reg->DMA0_LEN_REG + 1) - p_ctrl->p_reg->DMA0_IDX_REG;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * To update next transfer information without interruption during transfer.
 *
 * @retval FSP_ERR_UNSUPPORTED        This feature is not supported.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_W_Reload (transfer_ctrl_t * const p_api_ctrl,
                           void const            * p_src,
                           void                  * p_dest,
                           uint32_t const          num_transfers)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_src);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(num_transfers);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_IRQ_BSP_DISABLED     The IRQ associated with the activation source is not enabled in the BSP.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_W_CallbackSet (transfer_ctrl_t * const      p_api_ctrl,
                                void (                     * p_callback)(dmac_callback_args_t *),
                                void * const                 p_context,
                                dmac_callback_args_t * const p_callback_memory)
{
    FSP_PARAMETER_NOT_USED(p_callback_memory);

    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;

#if DMAC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    FSP_ERROR_RETURN(p_extend->irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
#endif

    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable transfer and clean up internal data. Implements @ref transfer_api_t::close.
 *
 * @retval FSP_SUCCESS           Successful close.
 * @retval FSP_ERR_ASSERTION     An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN      Handle is not initialized.  Call R_DMAC_W_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_W_Close (transfer_ctrl_t * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(DMAC_ID == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    p_ctrl->p_reg->DMA0_CTRL_REG_b.DMA_ON = 0U;

    r_dmac_w_peripherals_unmap(p_extend->channel);

    if (NULL != p_ctrl->p_callback)
    {
        r_dmac_w_irq_disable(p_ctrl);

        R_BSP_DMAC_ChannelInterruptsDisable(p_extend->channel);

#if BSP_FEATURE_DMAC_HAS_SHARED_IRQ
        gp_dmac_ctrls[p_extend->channel] = NULL;
#endif
    }

    /* Clear ID so control block can be reused. */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Temporarily freeze/unfreeze all channels of the DMAC controller.
 *
 * Example:
 * @snippet r_dmac_w_example.c R_DMAC_W_Freeze
 *
 * @retval FSP_SUCCESS           Successful freeze.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_W_Freeze (bool freeze)
{
    if (freeze)
    {
        R_BSP_PeripheralFreeze(BSP_FREEZE_PERIPHERAL_DMA);
    }
    else
    {
        R_BSP_PeripheralUnFreeze(BSP_FREEZE_PERIPHERAL_DMA);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup DMAC_W)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Write the transfer info to the hardware registers.
 *
 * @param[in]   p_ctrl         Pointer to control structure.
 * @param       p_info         Pointer to transfer info.
 **********************************************************************************************************************/
static void r_dmac_w_config_transfer_info (dmac_instance_ctrl_t * p_ctrl, transfer_info_t * p_info)
{
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    p_ctrl->p_reg->DMA0_CTRL_REG_b.DMA_ON = 0U;

    uint32_t a_inc = ((TRANSFER_ADDR_MODE_INCREMENTED == p_info->transfer_settings_word_b.src_addr_mode) ? 1 : 0);
    uint32_t b_inc = ((TRANSFER_ADDR_MODE_INCREMENTED == p_info->transfer_settings_word_b.dest_addr_mode) ? 1 : 0);

    p_ctrl->p_reg->DMA0_CTRL_REG =
        (p_info->transfer_settings_word_b.size << DMA_DMA0_CTRL_REG_BW_Pos) |
        ((uint32_t) p_extend->start_mode << DMA_DMA0_CTRL_REG_DREQ_MODE_Pos) |
        (a_inc << DMA_DMA0_CTRL_REG_AINC_Pos) |
        (b_inc << DMA_DMA0_CTRL_REG_BINC_Pos) |
        (p_info->transfer_settings_word_b.mode << DMA_DMA0_CTRL_REG_CIRCULAR_Pos) |
        (p_extend->channel_prio << DMA_DMA0_CTRL_REG_DMA_PRIO_Pos) |
        (p_extend->idle_mode << DMA_DMA0_CTRL_REG_DMA_IDLE_Pos) |
        (p_extend->init_mode << DMA_DMA0_CTRL_REG_DMA_INIT_Pos) |
        (p_extend->burst_mode << DMA_DMA0_CTRL_REG_BURST_MODE_Pos) |
        (DMA_DMA0_CTRL_REG_BUS_ERROR_DETECT_Msk);

    if (NULL != p_ctrl->p_callback)
    {
#if BSP_FEATURE_DMAC_HAS_SHARED_IRQ
        gp_dmac_ctrls[p_extend->channel] = p_ctrl;
#endif
        R_BSP_DMAC_ChannelInterruptsEnable(p_extend->channel);

        r_dmac_w_irq_enable(p_ctrl);
    }
    else
    {
        R_BSP_DMAC_ChannelInterruptsDisable(p_extend->channel);
    }

    r_dmac_w_peripherals_map(p_ctrl);

    if (R_BSP_DMAC_IsEdgeSensitiveTrigger(p_extend->periph_trigger))
    {
        p_ctrl->p_reg->DMA0_CTRL_REG_b.REQ_SENSE = 1U;
    }

    p_ctrl->p_reg->DMA0_A_START_REG = (uint32_t) p_info->p_src;
    p_ctrl->p_reg->DMA0_B_START_REG = (uint32_t) p_info->p_dest;

    if (p_extend->irq_num_of_trans > 0)
    {
        p_ctrl->p_reg->DMA0_INT_REG = (uint32_t) (p_extend->irq_num_of_trans - 1);
    }
    else
    {
        p_ctrl->p_reg->DMA0_INT_REG = (uint32_t) (p_info->length - 1);
    }

    p_ctrl->p_reg->DMA0_LEN_REG = (uint32_t) (p_info->length - 1);
}

/*******************************************************************************************************************//**
 * Enable transfers for the channel.
 *
 * @param[in]  p_ctrl             Pointer to control structure.
 *
 * @retval     FSP_SUCCESS        Successful enable.
 * @retval     FSP_ERR_ASSERTION  An input parameter is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_dmac_w_channel_enable (dmac_instance_ctrl_t * p_ctrl)
{
#if DMAC_W_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_dmac_w_enable_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    p_ctrl->p_reg->DMA0_CTRL_REG_b.DMA_ON = 1U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set DMA MUX mapping for the requested channel / trigger combination.
 *
 * @param[in]  channel            DMA channel.
 * @param[in]  periph_trigger     The peripheral trigger to map on the DMAC channel.
 **********************************************************************************************************************/
static void r_dmac_w_dma_mux_reg_set (uint8_t channel, bsp_dmac_trig_t periph_trigger)
{
    uint8_t             mux_index          = (uint8_t) (channel / DMAC_PRV_MUX_CH_OFFSET);
    uint8_t             mux_sel            = (uint8_t) (channel % DMAC_PRV_MUX_CH_OFFSET);
    volatile uint32_t * p_dma_req_mux_regs = &DMA->DMA_REQ_MUX_REG;

    /* DMAC MUX registers are placed in the memory one after another.
     * We can access every MUX register as an array element. */

    p_dma_req_mux_regs[mux_index] = ((p_dma_req_mux_regs[mux_index] &
                                      ~(DMAC_PRV_MUX_SEL_MASK << (mux_sel * DMAC_PRV_MUX_SEL_BITS))) |
                                     ((uint32_t) periph_trigger << (mux_sel * DMAC_PRV_MUX_SEL_BITS)));
}

/*******************************************************************************************************************//**
 * Map DMAC channel to specific peripheral trigger.
 *
 * @param[in]  p_ctrl             Pointer to control structure.
 **********************************************************************************************************************/
static void r_dmac_w_peripherals_map (dmac_instance_ctrl_t * const p_ctrl)
{
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    FSP_CRITICAL_SECTION_DEFINE;

    FSP_CRITICAL_SECTION_ENTER;
    r_dmac_w_dma_mux_reg_set(p_extend->channel, p_extend->periph_trigger);
    FSP_CRITICAL_SECTION_EXIT;
}

/*******************************************************************************************************************//**
 * Disable peripheral mapping on the DMAC channel.
 *
 * @param[in]  channel            DMAC channel.
 **********************************************************************************************************************/
static void r_dmac_w_peripherals_unmap (uint8_t channel)
{
    FSP_CRITICAL_SECTION_DEFINE;

    FSP_CRITICAL_SECTION_ENTER;
    r_dmac_w_dma_mux_reg_set(channel, BSP_DMAC_TRIG_NONE);
    FSP_CRITICAL_SECTION_EXIT;
}

#if DMAC_W_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Parameter checking of R_DMAC_W_Open.
 *
 * @param[in]   p_ctrl                    Pointer to control structure.
 * @param[in]   p_cfg                     Pointer to configuration structure. All elements of the structure must be
 *                                        set by user.
 *
 * @retval FSP_SUCCESS                    Input Parameters are Valid.
 * @retval FSP_ERR_ASSERTION              An input parameter is invalid.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The configured channel is invalid.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       Callback is not NULL but the DMAC IRQ is not enabled.
 * @retval FSP_ERR_ALREADY_OPEN           The control structure is already opened.
 * @retval FSP_ERR_UNSUPPORTED            A Selected setting is not supported by this API.
 **********************************************************************************************************************/
static fsp_err_t r_dma_open_parameter_checking (dmac_instance_ctrl_t * const p_ctrl, transfer_cfg_t const * const p_cfg)
{
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(DMAC_ID != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_cfg->p_extend;
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(DMAC_PRV_CHANNEL_PRIO_HIGHEST >= p_extend->channel_prio);
    FSP_ERROR_RETURN(BSP_FEATURE_DMAC_MAX_CHANNEL > p_extend->channel, FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    if (NULL != p_extend->p_callback)
    {
        FSP_ERROR_RETURN(p_extend->irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

    fsp_err_t err = r_dmac_w_reconfigure_parameter_checking(p_cfg->p_info);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Checks for errors in the transfer into structure.
 *
 * @param[in]   p_info              Pointer transfer info.
 *
 * @retval FSP_SUCCESS              The transfer info is valid.
 * @retval FSP_ERR_ASSERTION        A transfer info setting is invalid.
 * @retval FSP_ERR_UNSUPPORTED      A Selected setting is not supported by this API.
 **********************************************************************************************************************/
static fsp_err_t r_dmac_w_reconfigure_parameter_checking (transfer_info_t const * const p_info)
{
    FSP_ASSERT(NULL != p_info);
    FSP_ASSERT(0 < p_info->length);

    FSP_ERROR_RETURN((TRANSFER_ADDR_MODE_FIXED == p_info->transfer_settings_word_b.src_addr_mode) ||
                     (TRANSFER_ADDR_MODE_INCREMENTED == p_info->transfer_settings_word_b.src_addr_mode),
                     FSP_ERR_UNSUPPORTED);

    FSP_ERROR_RETURN((TRANSFER_ADDR_MODE_FIXED == p_info->transfer_settings_word_b.dest_addr_mode) ||
                     (TRANSFER_ADDR_MODE_INCREMENTED == p_info->transfer_settings_word_b.dest_addr_mode),
                     FSP_ERR_UNSUPPORTED);

    FSP_ERROR_RETURN((TRANSFER_MODE_NORMAL == p_info->transfer_settings_word_b.mode) ||
                     (TRANSFER_MODE_REPEAT == p_info->transfer_settings_word_b.mode),
                     FSP_ERR_UNSUPPORTED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Parameter checking for transfer configuration.
 *
 * @param[in]   p_ctrl                 Pointer to control structure.
 *
 * @retval      FSP_SUCCESS            Alignment on source and destination pointers is valid.
 * @retval      FSP_ERR_ASSERTION      The current configuration is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_dmac_w_enable_parameter_checking (dmac_instance_ctrl_t * const p_ctrl)
{
    FSP_ASSERT(0U == p_ctrl->p_reg->DMA0_CTRL_REG_b.DMA_ON);

    void const * p_src  = (void const *) p_ctrl->p_reg->DMA0_A_START_REG;
    void const * p_dest = (void const *) p_ctrl->p_reg->DMA0_B_START_REG;

    transfer_size_t size = (transfer_size_t) p_ctrl->p_reg->DMA0_CTRL_REG_b.BW;
    transfer_mode_t mode = (transfer_mode_t) p_ctrl->p_reg->DMA0_CTRL_REG_b.CIRCULAR;

    /* The source and destination pointers cannot be NULL. */
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);

    /* The source and destination pointers must be aligned to the transfer size. */

    FSP_ASSERT(0U == ((uint32_t) p_dest & DMAC_PRV_MASK_ALIGN_N_BYTES(size)));
    FSP_ASSERT(0U == ((uint32_t) p_src & DMAC_PRV_MASK_ALIGN_N_BYTES(size)));

    if (TRANSFER_MODE_REPEAT == mode)
    {
        FSP_ASSERT(1U == p_ctrl->p_reg->DMA0_CTRL_REG_b.DREQ_MODE);
    }

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Enable IRQ for DMA channel.
 *
 * @param[in]  p_ctrl             Pointer to control structure.
 **********************************************************************************************************************/
static void r_dmac_w_irq_enable (dmac_instance_ctrl_t * const p_ctrl)
{
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

#if BSP_FEATURE_DMAC_HAS_SHARED_IRQ
    for (uint8_t channel = 0; BSP_FEATURE_DMAC_MAX_CHANNEL > channel; channel++)
    {
        if ((NULL != gp_dmac_ctrls[channel]) && (channel != p_extend->channel))
        {

            /* If we have registered channel previously. No need to enable DMA IRQ again. */
            return;
        }
    }
#endif

    R_BSP_IrqCfgEnable(p_extend->irq, p_extend->ipl, p_ctrl);
}

/*******************************************************************************************************************//**
 * Disable IRQ for DMA channel.
 *
 * @param[in]  p_ctrl             Pointer to control structure.
 **********************************************************************************************************************/
static void r_dmac_w_irq_disable (dmac_instance_ctrl_t * const p_ctrl)
{
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

#if BSP_FEATURE_DMAC_HAS_SHARED_IRQ
    for (uint8_t channel = 0; BSP_FEATURE_DMAC_MAX_CHANNEL > channel; channel++)
    {
        if ((NULL != gp_dmac_ctrls[channel]) && (channel != p_extend->channel))
        {

            /* It isn't last registered channel. No need to disable DMA IRQ just yet. */
            return;
        }
    }
#endif

    R_BSP_IrqDisable(p_extend->irq);
    R_FSP_IsrContextSet(p_extend->irq, NULL);
}

/*******************************************************************************************************************//**
 * Process interrupt on specific DMA channel.
 *
 * @param[in]  p_ctrl             Pointer to control structure.
 **********************************************************************************************************************/
static void r_dmac_w_interrupt_handle (dmac_instance_ctrl_t * const p_ctrl)
{
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    DMA->DMA_CLEAR_INT_REG = 1 << p_extend->channel;

    /* Call user callback */
    dmac_callback_args_t args;
    args.p_context = p_ctrl->p_context;
    p_ctrl->p_callback(&args);
}

/*******************************************************************************************************************//**
 * DMAC ISR
 **********************************************************************************************************************/
void dmac_w_int_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

#if BSP_FEATURE_BSP_HAS_ICU || BSP_FEATURE_DMAC_HAS_SHARED_IRQ == 0
    IRQn_Type irq = R_FSP_CurrentIrqGet();

 #if BSP_FEATURE_BSP_HAS_ICU

    /* Clear IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);
 #endif
#endif

#if BSP_FEATURE_DMAC_HAS_SHARED_IRQ
    uint32_t channel_interrupts = DMA->DMA_INT_STATUS_REG;

    /* Go over all the DMA channels. Check for interrupt events */
    for (uint8_t channel = 0;
         0 != channel_interrupts && BSP_FEATURE_DMAC_MAX_CHANNEL > channel;
         channel_interrupts >>= 1, channel++)
    {
        if (0 != (channel_interrupts & 1))
        {
            if (NULL != gp_dmac_ctrls[channel])
            {
                r_dmac_w_interrupt_handle(gp_dmac_ctrls[channel]);
            }
        }
    }

#else

    /* Handle interrupt for a channel associated with received IRQn */
    dmac_instance_ctrl_t * p_ctrl = R_FSP_IsrContextGet(irq);

    r_dmac_w_interrupt_handle(p_ctrl);
#endif

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE;
}
