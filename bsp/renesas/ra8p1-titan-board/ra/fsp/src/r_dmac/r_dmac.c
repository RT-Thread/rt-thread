/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_dmac.h"
#include "r_dmac_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Driver ID (DMAC in ASCII) */
#define DMAC_ID                         (0x444d4143)

/** Length limited to 1024 transfers for repeat and block mode */
#define DMAC_REPEAT_BLOCK_MAX_LENGTH    (0x400)

#define DMAC_PRV_MASK_ALIGN_2_BYTES     (0x1U)
#define DMAC_PRV_MASK_ALIGN_4_BYTES     (0x3U)

/* Calculate the mask bits for byte alignment from the transfer_size_t. */
#define DMAC_PRV_MASK_ALIGN_N_BYTES(x)    ((1U << (x)) - 1U)

#define DMAC_PRV_REG(ch)                  ((R_DMAC0_Type *) (((uint32_t) R_DMAC1 - (uint32_t) R_DMAC0) * ch + \
                                                             (uint32_t) R_DMAC0))

/* Transfer Count Register A Bit Field Definitions */
#define DMAC_PRV_DMCRA_LOW_OFFSET        (0U)
#define DMAC_PRV_DMCRA_LOW_MASK          (0x3FFU << DMAC_PRV_DMCRA_LOW_OFFSET)
#define DMAC_PRV_DMCRA_HIGH_OFFSET       (16U)
#define DMAC_PRV_DMCRA_HIGH_MASK         (0x3FFU << DMAC_PRV_DMCRA_HIGH_OFFSET)

/* Transfer Mode Register Bit Field Definitions */
#define DMAC_PRV_DMTMD_DCTG_OFFSET       (0U)
#define DMAC_PRV_DMTMD_DCTG_MASK         (3U << DMAC_PRV_DMTMD_DCTG_OFFSET)
#define DMAC_PRV_DMTMD_SZ_OFFSET         (8U)
#define DMAC_PRV_DMTMD_SZ_MASK           (3U << DMAC_PRV_DMTMD_SZ_OFFSET)
#define DMAC_PRV_DMTMD_DTS_OFFSET        (12U)
#define DMAC_PRV_DMTMD_DTS_MASK          (3U << DMAC_PRV_DMTMD_DTS_OFFSET)
#define DMAC_PRV_DMTMD_MD_OFFSET         (14U)
#define DMAC_PRV_DMTMD_MD_MASK           (3U << DMAC_PRV_DMTMD_MD_OFFSET)

/* Interrupt Setting Register Bit Field Definitions */
#define DMAC_PRV_DMINT_DARIE_OFFSET      (0U)
#define DMAC_PRV_DMINT_DARIE_MASK        (1U << DMAC_PRV_DMINT_DARIE_OFFSET)
#define DMAC_PRV_DMINT_SARIE_OFFSET      (1U)
#define DMAC_PRV_DMINT_SARIE_MASK        (1U << DMAC_PRV_DMINT_SARIE_OFFSET)
#define DMAC_PRV_DMINT_RPTIE_OFFSET      (2U)
#define DMAC_PRV_DMINT_RPTIE_MASK        (1U << DMAC_PRV_DMINT_RPTIE_OFFSET)
#define DMAC_PRV_DMINT_ESIE_OFFSET       (3U)
#define DMAC_PRV_DMINT_ESIE_MASK         (1U << DMAC_PRV_DMINT_ESIE_OFFSET)
#define DMAC_PRV_DMINT_DTIE_OFFSET       (4U)
#define DMAC_PRV_DMINT_DTIE_MASK         (1U << DMAC_PRV_DMINT_DTIE_OFFSET)

/* Address Mode Register Bit Field Definitions */
#define DMAC_PRV_DMAMD_DARA_OFFSET       (0U)
#define DMAC_PRV_DMAMD_DARA_MASK         (0x1FU << DMAC_PRV_DMAMD_DARA_OFFSET)
#define DMAC_PRV_DMAMD_DM_OFFSET         (6U)
#define DMAC_PRV_DMAMD_DM_MASK           (3U << DMAC_PRV_DMAMD_DM_OFFSET)
#define DMAC_PRV_DMAMD_SARA_OFFSET       (8U)
#define DMAC_PRV_DMAMD_SARA_MASK         (0x1FU << DMAC_PRV_DMAMD_SARA_OFFSET)
#define DMAC_PRV_DMAMD_SM_OFFSET         (14U)
#define DMAC_PRV_DMAMD_SM_MASK           (3U << DMAC_PRV_DMAMD_SM_OFFSET)

/* Software Start Register Bit Field Definitions */
#define DMAC_PRV_DMREQ_SWREQ_OFFSET      (0U)
#define DMAC_PRV_DMREQ_SWREQ_MASK        (1U << DMAC_PRV_DMREQ_SWREQ_OFFSET)
#define DMAC_PRV_DMREQ_CLRS_OFFSET       (4U)
#define DMAC_PRV_DMREQ_CLRS_MASK         (1U << DMAC_PRV_DMREQ_CLRS_OFFSET)

#ifndef DMAC_CFG_ERROR_CHANNEL_CLEAR
 #define DMAC_CFG_ERROR_CHANNEL_CLEAR    (0)
#endif

#ifndef DMAC_CFG_PRIORITY_MODE
 #define DMAC_CFG_PRIORITY_MODE          (0)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Internal driver storage for p_callback, used by ISRs. */
typedef struct st_dmac_callback
{
    /** Callback for transfer end interrupt. Set to NULL for no CPU interrupt. */
    void (* p_callback)(dmac_callback_args_t * cb_data);

    /** Placeholder for user data.  Passed to the user p_callback in ::transfer_callback_args_t. */
    void * p_context;
} dmac_callback_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void dmac_int_isr(void);

static fsp_err_t r_dmac_prv_enable(dmac_instance_ctrl_t * p_ctrl);
static void      r_dmac_prv_disable(dmac_instance_ctrl_t * p_ctrl);
static void      r_dmac_config_transfer_info(dmac_instance_ctrl_t * p_ctrl, transfer_info_t * p_info);

#if DMAC_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_dma_open_parameter_checking(dmac_instance_ctrl_t * const p_ctrl, transfer_cfg_t const * const p_cfg);
static fsp_err_t r_dmac_reconfigure_parameter_checking(transfer_info_t const * const p_info);
static fsp_err_t r_dmac_enable_parameter_checking(dmac_instance_ctrl_t * const p_ctrl);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** DMAC implementation of transfer API. */
const transfer_api_t g_transfer_on_dmac =
{
    .open          = R_DMAC_Open,
    .reconfigure   = R_DMAC_Reconfigure,
    .reset         = R_DMAC_Reset,
    .infoGet       = R_DMAC_InfoGet,
    .softwareStart = R_DMAC_SoftwareStart,
    .softwareStop  = R_DMAC_SoftwareStop,
    .enable        = R_DMAC_Enable,
    .disable       = R_DMAC_Disable,
    .reload        = R_DMAC_Reload,
    .callbackSet   = R_DMAC_CallbackSet,
    .close         = R_DMAC_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup DMAC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configure a DMAC channel.
 *
 * @retval FSP_SUCCESS                    Successful open.
 * @retval FSP_ERR_ASSERTION              An input parameter is invalid.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The configured channel is invalid.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       The IRQ associated with the activation source is not enabled in the BSP.
 * @retval FSP_ERR_ALREADY_OPEN           The control structure is already opened.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Open (transfer_ctrl_t * const p_api_ctrl, transfer_cfg_t const * const p_cfg)
{
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = FSP_SUCCESS;
    err = r_dma_open_parameter_checking(p_api_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    dmac_instance_ctrl_t * p_ctrl   = (dmac_instance_ctrl_t *) p_api_ctrl;
    dmac_extended_cfg_t  * p_extend = (dmac_extended_cfg_t *) p_cfg->p_extend;

    p_ctrl->p_cfg = p_cfg;
    p_ctrl->p_reg = DMAC_PRV_REG(p_extend->channel);

    /* Set callback and context pointers, if configured */
    p_ctrl->p_callback        = p_extend->p_callback;
    p_ctrl->p_context         = p_extend->p_context;
    p_ctrl->p_callback_memory = NULL;

    /* Enable DMAC Operation. */
    R_BSP_MODULE_START(FSP_IP_DMAC, p_extend->channel);

    R_DMA->DMAST = 1;

#if BSP_FEATURE_DMAC_HAS_DMCTL
    R_DMA->DMCTL = (DMAC_CFG_PRIORITY_MODE << R_DMA_DMCTL_PR_Pos) |
                   (DMAC_CFG_ERROR_CHANNEL_CLEAR << R_DMA_DMCTL_ERCH_Pos);
#endif

    /* Configure the transfer settings. */
    r_dmac_config_transfer_info(p_ctrl, p_cfg->p_info);

    /* Mark driver as open by initializing "DMAC" in its ASCII equivalent.*/
    p_ctrl->open = DMAC_ID;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reconfigure the transfer with new transfer info.
 *
 * @retval FSP_SUCCESS              Transfer is configured and will start when trigger occurs.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_ENABLED      DMAC is not enabled. The current configuration must not be valid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Reconfigure (transfer_ctrl_t * const p_api_ctrl, transfer_info_t * p_info)
{
    fsp_err_t              err;
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;

#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
    err = r_dmac_reconfigure_parameter_checking(p_info);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Reconfigure the transfer settings. */
    r_dmac_config_transfer_info(p_ctrl, p_info);

    /* Enable the transfer configuration. */
    err = r_dmac_prv_enable(p_api_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_NOT_ENABLED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reset transfer source, destination, and number of transfers.
 *
 * @retval FSP_SUCCESS              Transfer reset successfully.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_ENABLED      DMAC is not enabled. The current configuration must not be valid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Reset (transfer_ctrl_t * const p_api_ctrl,
                        void const * volatile   p_src,
                        void * volatile         p_dest,
                        uint16_t const          num_transfers)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t              err    = FSP_SUCCESS;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
#endif

    /* Disable transfers if they are currently enabled. */
    r_dmac_prv_disable(p_ctrl);

    if (NULL != p_src)
    {
        /* Configure the DMAC source pointer if it is provided. */
        p_ctrl->p_reg->DMSAR = (uint32_t) p_src;
    }

    if (NULL != p_dest)
    {
        /* Configure the DMAC destination pointer if it is provided. */
        p_ctrl->p_reg->DMDAR = (uint32_t) p_dest;
    }

    if ((TRANSFER_MODE_NORMAL != (transfer_mode_t) p_ctrl->p_reg->DMTMD_b.MD))
    {
        /* Reset the block/repeat count if it is not normal mode. */
        p_ctrl->p_reg->DMCRB = num_transfers;
    }
    else
    {
        /* Reset the transfer count if it is normal mode. */
        p_ctrl->p_reg->DMCRA = num_transfers;
    }

    /* Enable the transfer configuration. */
    err = r_dmac_prv_enable(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_NOT_ENABLED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * If the mode is TRANSFER_START_MODE_SINGLE initiate a single transfer with software. If the mode is
 * TRANSFER_START_MODE_REPEAT continue triggering transfers until all of the transfers are completed.
 *
 * @retval FSP_SUCCESS              Transfer started written successfully.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 * @retval FSP_ERR_UNSUPPORTED      Handle was not configured for software activation.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_SoftwareStart (transfer_ctrl_t * const p_api_ctrl, transfer_start_mode_t mode)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);

    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    FSP_ERROR_RETURN(ELC_EVENT_NONE == p_extend->activation_source, FSP_ERR_UNSUPPORTED);
#endif

    /* Set auto clear bit and software start bit. */
    p_ctrl->p_reg->DMREQ = (uint8_t) (((uint32_t) mode << DMAC_PRV_DMREQ_CLRS_OFFSET) | DMAC_PRV_DMREQ_SWREQ_MASK);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stop software transfers if they were started with TRANSFER_START_MODE_REPEAT.
 *
 * @retval FSP_SUCCESS              Transfer stopped written successfully.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_SoftwareStop (transfer_ctrl_t * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
#endif

    /* Reset auto clear bit and clear software start bit. */
    p_ctrl->p_reg->DMREQ = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable transfers for the configured activation source.
 *
 * @retval FSP_SUCCESS              Counter value written successfully.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Enable (transfer_ctrl_t * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
#endif

    return r_dmac_prv_enable(p_ctrl);
}

/*******************************************************************************************************************//**
 * Disable transfers so that they are no longer triggered by the activation source.
 *
 * @retval FSP_SUCCESS              Counter value written successfully.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Disable (transfer_ctrl_t * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
#endif

    r_dmac_prv_disable(p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set driver specific information in provided pointer.
 *
 * @retval FSP_SUCCESS              Information has been written to p_info.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_InfoGet (transfer_ctrl_t * const p_api_ctrl, transfer_properties_t * const p_info)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_info);
#endif

    p_info->transfer_length_max = DMAC_MAX_BLOCK_TRANSFER_LENGTH;
    p_info->block_count_max     = DMAC_MAX_BLOCK_COUNT;

    transfer_mode_t mode = (transfer_mode_t) p_ctrl->p_reg->DMTMD_b.MD;

    p_info->block_count_remaining     = p_ctrl->p_reg->DMCRB;
    p_info->transfer_length_remaining = p_ctrl->p_reg->DMCRA_b.DMCRAL;

    if (TRANSFER_MODE_NORMAL == mode)
    {
        p_info->transfer_length_max = DMAC_MAX_NORMAL_TRANSFER_LENGTH;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * To update next transfer information without interruption during transfer.
 *
 * @retval FSP_ERR_UNSUPPORTED        This feature is not supported.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Reload (transfer_ctrl_t * const p_api_ctrl,
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
 **********************************************************************************************************************/
fsp_err_t R_DMAC_CallbackSet (transfer_ctrl_t * const      p_api_ctrl,
                              void (                     * p_callback)(dmac_callback_args_t *),
                              void * const                 p_context,
                              dmac_callback_args_t * const p_callback_memory)
{
    FSP_PARAMETER_NOT_USED(p_callback_memory);

    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;

#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
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
 * @retval FSP_ERR_NOT_OPEN      Handle is not initialized.  Call R_DMAC_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Close (transfer_ctrl_t * const p_api_ctrl)
{
    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) p_api_ctrl;
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DMAC_ID, FSP_ERR_NOT_OPEN);
#endif

    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Disable DMAC transfers on this channel. */
#if !BSP_FEATURE_DMAC_HAS_DELSR
    R_ICU->DELSR[p_extend->channel] = ELC_EVENT_NONE;
#else
    R_DMA->DELSR[p_extend->channel] = ELC_EVENT_NONE;
#endif
    p_ctrl->p_reg->DMCNT = 0;

    if (NULL != p_extend->p_callback)
    {
        R_BSP_IrqDisable(p_extend->irq);
        R_FSP_IsrContextSet(p_extend->irq, NULL);
    }

    /* Clear ID so control block can be reused. */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup DMAC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enable transfers for the channel.
 *
 * @param[in]  p_ctrl             Pointer to control structure.
 *
 * @retval     FSP_SUCCESS        Successful close.
 * @retval     FSP_ERR_ASSERTION  An input parameter is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_dmac_prv_enable (dmac_instance_ctrl_t * p_ctrl)
{
#if DMAC_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_dmac_enable_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /** Enable transfer. */
    p_ctrl->p_reg->DMCNT = 1;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable transfers for the channel.
 *
 * @param      p_ctrl          Pointer to the control structure
 **********************************************************************************************************************/
static void r_dmac_prv_disable (dmac_instance_ctrl_t * p_ctrl)
{
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Disable the transfers. See table "Register setting procedure" in the DMAC section of the relevant
     * hardware manual. */
#if !BSP_FEATURE_DMAC_HAS_DELSR
    R_ICU->DELSR[p_extend->channel] = ELC_EVENT_NONE;
#else
    R_DMA->DELSR[p_extend->channel] = ELC_EVENT_NONE;
#endif

    p_ctrl->p_reg->DMCNT = 0;

    /* Configure the activation source. */
#if !BSP_FEATURE_DMAC_HAS_DELSR
    R_ICU->DELSR[p_extend->channel] = p_extend->activation_source;
#else
    R_DMA->DELSR[p_extend->channel] = p_extend->activation_source;
#endif

    /* Disable software start. */
    p_ctrl->p_reg->DMREQ = 0;
}

/*******************************************************************************************************************//**
 * Write the transfer info to the hardware registers.
 *
 * @param[in]   p_ctrl         Pointer to control structure.
 * @param       p_info         Pointer to transfer info.
 **********************************************************************************************************************/
static void r_dmac_config_transfer_info (dmac_instance_ctrl_t * p_ctrl, transfer_info_t * p_info)
{
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    uint32_t dmcra = 0;
    uint32_t dmcrb = 0;
    uint32_t dmtmd = 0;
    uint32_t dmint = 0;
    uint32_t dmamd = 0;

    /* Disable transfers if they are currently enabled. */
    r_dmac_prv_disable(p_ctrl);

    /* Configure the Transfer Data Size (1,2,4) bytes. */
    dmtmd |= (uint32_t) (p_info->transfer_settings_word_b.size << DMAC_PRV_DMTMD_SZ_OFFSET);

    /* Configure source and destination address mode. */
    dmamd |= (uint32_t) (p_info->transfer_settings_word_b.src_addr_mode << DMAC_PRV_DMAMD_SM_OFFSET);
    dmamd |= (uint32_t) (p_info->transfer_settings_word_b.dest_addr_mode << DMAC_PRV_DMAMD_DM_OFFSET);

    /* Configure the transfer mode. */
    dmtmd |= (uint32_t) p_info->transfer_settings_word_b.mode << DMAC_PRV_DMTMD_MD_OFFSET;

    /* Configure the transfer count. */
    dmcra = p_info->length;

    if ((TRANSFER_MODE_BLOCK == p_info->transfer_settings_word_b.mode) ||
        (TRANSFER_MODE_REPEAT == p_info->transfer_settings_word_b.mode) ||
        (TRANSFER_MODE_REPEAT_BLOCK == p_info->transfer_settings_word_b.mode))
    {
        /* Configure the reload count. */
        dmcra |= dmcra << DMAC_PRV_DMCRA_HIGH_OFFSET;
        dmcra &= (DMAC_PRV_DMCRA_HIGH_MASK | DMAC_PRV_DMCRA_LOW_MASK);

        /* Configure the block count. */
        dmcrb = p_info->num_blocks;

        if ((TRANSFER_MODE_BLOCK == p_info->transfer_settings_word_b.mode) ||
            (TRANSFER_MODE_REPEAT == p_info->transfer_settings_word_b.mode))
        {
            /* Configure the repeat area */
            dmtmd |= (uint32_t) (p_info->transfer_settings_word_b.repeat_area << DMAC_PRV_DMTMD_DTS_OFFSET);
        }
    }
    else                               /* TRANSFER_MODE_NORMAL */
    {
        /* Configure no repeat area. */
        dmtmd |= 2U << DMAC_PRV_DMTMD_DTS_OFFSET;
    }

    if (ELC_EVENT_NONE != p_extend->activation_source)
    {
        /* DMAC will be triggered by interrupts (ELC Events). */
        dmtmd |= 1U << DMAC_PRV_DMTMD_DCTG_OFFSET;
    }

    if (NULL != p_ctrl->p_callback)
    {
        /* Enable transfer end interrupt requests. */
        dmint |= DMAC_PRV_DMINT_DTIE_MASK;

        /* Enable the transfer end escape interrupt requests.
         * Repeat size end and Extended Repeat area overflow requests are not
         * used with Repeat-Block mode. Reference section 16.2.9 "DMINT : DMA Interrupt Setting Register"
         * description in the DMAC section of the relevant hardware manual. */
        if ((TRANSFER_IRQ_EACH == p_info->transfer_settings_word_b.irq) &&
            (TRANSFER_MODE_REPEAT_BLOCK != p_info->transfer_settings_word_b.mode))
        {
            /* Enable the transfer end escape interrupt requests
             * (Repeat size end and Extended Repeat area overflow requests). */
            dmint |= (DMAC_PRV_DMINT_RPTIE_MASK | DMAC_PRV_DMINT_ESIE_MASK);
        }

        /* Enable the IRQ in the NVIC. */
        R_BSP_IrqCfgEnable(p_extend->irq, p_extend->ipl, p_ctrl);
    }

#if BSP_FEATURE_DMAC_HAS_REPEAT_BLOCK_MODE
    uint32_t dmsbs = 0;
    uint32_t dmdbs = 0;

    if (TRANSFER_MODE_REPEAT_BLOCK == p_info->transfer_settings_word_b.mode)
    {
        uint16_t num_of_blocks = p_info->num_blocks;
        uint16_t size_of_block;
        size_of_block = p_info->length;
        uint16_t src_buffer_size;
        uint16_t dest_buffer_size;
        if (TRANSFER_ADDR_MODE_OFFSET == p_info->transfer_settings_word_b.src_addr_mode)
        {
            src_buffer_size = num_of_blocks;
            dmamd          |= R_DMAC0_DMAMD_SADR_Msk;
        }
        else
        {
            src_buffer_size = p_extend->src_buffer_size;
        }

        if (TRANSFER_ADDR_MODE_OFFSET == p_info->transfer_settings_word_b.dest_addr_mode)
        {
            dest_buffer_size = num_of_blocks;
            dmamd           |= R_DMAC0_DMAMD_DADR_Msk;
        }
        else
        {
            dest_buffer_size = (uint16_t) (num_of_blocks * size_of_block);
        }

        dmsbs  = src_buffer_size;
        dmsbs |= dmsbs << R_DMAC0_DMSBS_DMSBSH_Pos;

        dmdbs  = dest_buffer_size;
        dmdbs |= dmdbs << R_DMAC0_DMDBS_DMDBSH_Pos;

        p_ctrl->p_reg->DMSRR = (uint32_t) p_info->p_src;
        p_ctrl->p_reg->DMDRR = (uint32_t) p_info->p_dest;
    }

    p_ctrl->p_reg->DMSBS = dmsbs;
    p_ctrl->p_reg->DMDBS = dmdbs;
#endif

    /* Write register settings. */
    p_ctrl->p_reg->DMAMD = (uint16_t) dmamd;
    p_ctrl->p_reg->DMTMD = (uint16_t) dmtmd;
    p_ctrl->p_reg->DMSAR = (uint32_t) p_info->p_src;
    p_ctrl->p_reg->DMDAR = (uint32_t) p_info->p_dest;
    p_ctrl->p_reg->DMCRA = dmcra;
    p_ctrl->p_reg->DMCRB = (uint16_t) dmcrb;
    p_ctrl->p_reg->DMOFR = (uint32_t) p_extend->offset;
    p_ctrl->p_reg->DMINT = (uint8_t) dmint;
}

#if DMAC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Parameter checking of R_DMAC_Open.
 *
 * @param[in]   p_ctrl                    Pointer to control structure.
 * @param[in]   p_cfg                     Pointer to configuration structure. All elements of the structure must be
 *                                        set by user.
 *
 * @retval FSP_SUCCESS                    Input Parameters are Valid.
 * @retval FSP_ERR_ASSERTION              An input parameter is invalid.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The configured channel is invalid.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       Callback is NULL and the DMAC IRQ is not enabled.
 * @retval FSP_ERR_ALREADY_OPEN           The control structure is already opened.
 **********************************************************************************************************************/
static fsp_err_t r_dma_open_parameter_checking (dmac_instance_ctrl_t * const p_ctrl, transfer_cfg_t const * const p_cfg)
{
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open != DMAC_ID, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    dmac_extended_cfg_t * p_extend = (dmac_extended_cfg_t *) p_cfg->p_extend;
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(p_extend->channel < BSP_FEATURE_DMAC_NUM_CHANNELS, FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    if (NULL != p_extend->p_callback)
    {
        FSP_ERROR_RETURN(p_extend->irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

    fsp_err_t err = r_dmac_reconfigure_parameter_checking(p_cfg->p_info);
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
 **********************************************************************************************************************/
static fsp_err_t r_dmac_reconfigure_parameter_checking (transfer_info_t const * const p_info)
{
    FSP_ASSERT(p_info != NULL);

    if (TRANSFER_MODE_NORMAL != p_info->transfer_settings_word_b.mode)
    {
        FSP_ASSERT(p_info->length <= DMAC_REPEAT_BLOCK_MAX_LENGTH);
    }

    FSP_ASSERT((TRANSFER_MODE_REPEAT_BLOCK != p_info->transfer_settings_word_b.mode) ||
               (TRANSFER_IRQ_EACH != p_info->transfer_settings_word_b.irq));

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Parameter checking for r_dmac_prv_enable.
 *
 * @param[in]   p_ctrl                 Pointer to control structure.
 *
 * @retval      FSP_SUCCESS            Alignment on source and destination pointers is valid.
 * @retval      FSP_ERR_ASSERTION      The current configuration is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_dmac_enable_parameter_checking (dmac_instance_ctrl_t * const p_ctrl)
{
    void const    * p_src  = (void const *) p_ctrl->p_reg->DMSAR;
    void const    * p_dest = (void const *) p_ctrl->p_reg->DMDAR;
    transfer_size_t size   = (transfer_size_t) p_ctrl->p_reg->DMTMD_b.SZ;
    transfer_mode_t mode   = (transfer_mode_t) p_ctrl->p_reg->DMTMD_b.MD;

    /* The source and destination pointers cannot be NULL. */
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);

    /* The source and destination pointers must be aligned to the transfer size. */
    FSP_ASSERT(0U == ((uint32_t) p_dest & DMAC_PRV_MASK_ALIGN_N_BYTES(size)));
    FSP_ASSERT(0U == ((uint32_t) p_src & DMAC_PRV_MASK_ALIGN_N_BYTES(size)));

    if (TRANSFER_MODE_NORMAL == mode)
    {
        /* Setting transfer count to 0 in normal mode means transfer forever. This feature is not supported. */
        FSP_ASSERT(0 != p_ctrl->p_reg->DMCRA);
    }

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * DMAC ISR
 **********************************************************************************************************************/
void dmac_int_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    dmac_instance_ctrl_t * p_ctrl = (dmac_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Call the callback routine if one is available */
    dmac_callback_args_t args;
    args.p_context = p_ctrl->p_context;

    /* Call user callback */
    p_ctrl->p_callback(&args);

    /* Transfers are disabled during the interrupt if an interrupt is requested after each block or after each repeat
     * length. If not all transfers are complete, reenable transfer here. See "Transfer End by Repeat
     * Size End Interrupt" in the DMAC section of the relevant hardware manual. */
    if (p_ctrl->p_reg->DMCRB > 0U)
    {
        p_ctrl->p_reg->DMCNT = 1;
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
