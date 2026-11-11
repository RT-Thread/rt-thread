/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_spi_w.h"

#if CFG_PMGR
 #include "rm_pmgr_w_instance.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "SPIW" in ASCII, used to determine if channel is open. */
#define SPI_W_OPEN        (0x53504957ULL)

/** Channel is sleeping. */
#define SPI_W_SLEEPING    (0x5ULL)

/** SPI base register access macro.  */
#define SPI_W_REG(channel)                           ((SPI_Type *) ((uint32_t) SPI + \
                                                                    ((uint32_t) SPI2 - (uint32_t) SPI) * (channel)))

/** SPI enable register access macros.  */
#if defined(CRG_COM_CLK_COM_REG_SPI_ENABLE_Msk)
 #define SPI_W_SET_CLK_COM_REG_SPI1_ENABLE(val)      CRG_COM->SET_CLK_COM_REG_b.SPI_ENABLE  = (val)
 #define SPI_W_SET_CLK_COM_REG_SPI2_ENABLE(val)      CRG_COM->SET_CLK_COM_REG_b.SPI2_ENABLE = (val)
 #define SPI_W_SET_CLK_COM_REG_SPI3_ENABLE(val)      CRG_COM->SET_CLK_COM_REG_b.SPI3_ENABLE = (val)
#elif defined(CRG_PER_CLK_COM_REG_SPI_ENABLE_Msk)
 #define SPI_W_SET_CLK_COM_REG_SPI1_ENABLE(val)      CRG_PER->SET_CLK_COM_REG_b.SPI_ENABLE  = (val)
 #define SPI_W_SET_CLK_COM_REG_SPI2_ENABLE(val)      CRG_PER->SET_CLK_COM_REG_b.SPI2_ENABLE = (val)
 #define SPI_W_SET_CLK_COM_REG_SPI3_ENABLE(val)      CRG_PER->SET_CLK_COM_REG_b.SPI3_ENABLE = (val)
#endif

/** SPI reset register access macros.  */
#if defined(CRG_COM_RESET_CLK_COM_REG_SPI_ENABLE_Msk)
 #define SPI_W_RESET_CLK_COM_REG_SPI1_ENABLE(val)    CRG_COM->RESET_CLK_COM_REG_b.SPI_ENABLE  = (val)
 #define SPI_W_RESET_CLK_COM_REG_SPI2_ENABLE(val)    CRG_COM->RESET_CLK_COM_REG_b.SPI2_ENABLE = (val)
 #define SPI_W_RESET_CLK_COM_REG_SPI3_ENABLE(val)    CRG_COM->RESET_CLK_COM_REG_b.SPI3_ENABLE = (val)
#elif defined(CRG_PER_RESET_CLK_COM_REG_SPI_ENABLE_Msk)
 #define SPI_W_RESET_CLK_COM_REG_SPI1_ENABLE(val)    CRG_PER->RESET_CLK_COM_REG_b.SPI_ENABLE  = (val)
 #define SPI_W_RESET_CLK_COM_REG_SPI2_ENABLE(val)    CRG_PER->RESET_CLK_COM_REG_b.SPI2_ENABLE = (val)
 #define SPI_W_RESET_CLK_COM_REG_SPI3_ENABLE(val)    CRG_PER->RESET_CLK_COM_REG_b.SPI3_ENABLE = (val)
#endif

/** SPI clock control register access macros.  */
#if defined(CRG_TOP_SPI_CLK_CTRL_REG_SPI_CLK_EN_Msk)
 #define SPI_W_SPI_CLK_CTRL_REG_SPI1_CLK_EN(val)     CRG_TOP->SPI_CLK_CTRL_REG_b.SPI_CLK_EN  = (val)
 #define SPI_W_SPI_CLK_CTRL_REG_SPI2_CLK_EN(val)     CRG_TOP->SPI_CLK_CTRL_REG_b.SPI2_CLK_EN = (val)
 #define SPI_W_SPI_CLK_CTRL_REG_SPI3_CLK_EN(val)     CRG_TOP->SPI_CLK_CTRL_REG_b.SPI3_CLK_EN = (val)
#else
 #define SPI_W_SPI_CLK_CTRL_REG_SPI1_CLK_EN(val)     do {} while (0)
 #define SPI_W_SPI_CLK_CTRL_REG_SPI2_CLK_EN(val)     do {} while (0)
 #define SPI_W_SPI_CLK_CTRL_REG_SPI3_CLK_EN(val)     do {} while (0)
#endif

#if (1 == SPI_W_CFG_TRANSFER_API_SUPPORT)
 #define SPI_W_TRANSFER_MAX_LENGTH       (0x10000)
#elif (2 == SPI_W_CFG_TRANSFER_API_SUPPORT)
 #define SPI_W_TRANSFER_MAX_LENGTH       (0xFFFF)
#endif

#define SPI_W_RX_TRANSFER_SETTINGS       ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |         \
                                          (TRANSFER_SIZE_1_BYTE << TRANSFER_SETTINGS_SIZE_BITS) |         \
                                          (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                          (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |              \
                                          (TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_DEST_ADDR_BITS))

#define SPI_W_TX_TRANSFER_SETTINGS       ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |               \
                                          (TRANSFER_SIZE_1_BYTE << TRANSFER_SETTINGS_SIZE_BITS) |               \
                                          (TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                          (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |                    \
                                          (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_DEST_ADDR_BITS))

#define SPI_W_CLK_DIV_SETTING_MASK       (0x7FU)       ///< Bit mask for SPI_CLK_DIV setting.
#define SPI_W_CLK_DIV_SETTING_MIN_DIV    (127U)        ///< SPI_CLK_DIV setting for Minimum SPI CLK divider.
#define SPI_W_CLK_MAX_DIV                (254U)        ///< Maximum SPI CLK divider.
#define SPI_W_CLK_MIN_DIV                (1UL)         ///< Minimum SPI CLK divider.

/* SPI_CONFIG_REG Bit Field Definitions */
#define SPI_W_CONFIG_REG_CPHA_POS        (0U)          ///< Clock Phase setting offset.
#define SPI_W_CONFIG_REG_CPOL_POS        (1U)          ///< Clock Polarity setting offset.

#define SPI_W_1_WORD                     (0x000000FFU) ///< Mask value for 8-bit width.
#define SPI_W_2_WORDS                    (0x0000FFFFU) ///< Mask value for 16-bit width.
#define SPI_W_4_WORDS                    (0xFFFFFFFFU) ///< Mask value for 32-bit width.

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * spi_w_prv_ns_callback)(spi_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile spi_w_prv_ns_callback)(spi_callback_args_t * p_args);
#endif

#if CFG_PMGR

/** SPI sleep context required by PMGR */

typedef struct st_spi_w_pmgr_context
{
    pmgr_instance_info_t     pmgr_info;
    pmgr_callback_args_t     clbk_args;
    pmgr_w_notifier_extend_t pmgr_notifier_ext;
    spi_w_instance_ctrl_t  * p_ctrl;
} spi_w_pmgr_context_t;
#endif

/***********************************************************************************************************************
 * Private function declarations
 **********************************************************************************************************************/
static fsp_err_t r_spi_w_transfer_config(spi_cfg_t const * const p_cfg);
static void      r_spi_w_hw_config(spi_w_instance_ctrl_t * p_ctrl);
static void      r_spi_w_nvic_config(spi_w_instance_ctrl_t * p_ctrl);
static void      r_spi_w_bit_width_config(spi_w_instance_ctrl_t * p_ctrl);
static fsp_err_t r_spi_w_start_transfer(spi_w_instance_ctrl_t * p_ctrl);
static fsp_err_t r_spi_w_write_read_common(spi_ctrl_t * const    p_api_ctrl,
                                           void const          * p_src,
                                           void                * p_dest,
                                           uint32_t const        length,
                                           spi_bit_width_t const bit_width,
                                           uint32_t const        fast_max_count);

static void r_spi_w_receive(spi_w_instance_ctrl_t * p_ctrl);
static void r_spi_w_transmit(spi_w_instance_ctrl_t * p_ctrl);

#if (2 == SPI_W_CFG_TRANSFER_API_SUPPORT) || !BSP_MCU_GROUP_RA6W1
static void r_spi_w_transfer_zero_pad_restore(spi_w_instance_ctrl_t * p_ctrl);

#endif
static void r_spi_w_transfer_end(spi_w_instance_ctrl_t * p_ctrl);
static void r_spi_w_call_callback(spi_w_instance_ctrl_t * p_ctrl, spi_event_t event);

#if CFG_PMGR
static fsp_err_t r_spi_w_subscribe_for_pmgr_notifications(spi_w_instance_ctrl_t * const p_ctrl);
static fsp_err_t r_spi_w_unsubscribe_from_pmgr_notifications(spi_w_instance_ctrl_t * const p_ctrl);

#endif

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
#if (2 == SPI_W_CFG_TRANSFER_API_SUPPORT)
extern void spi_w_rx_dmac_callback(spi_w_instance_ctrl_t * p_ctrl);
extern void spi_w_tx_dmac_callback(spi_w_instance_ctrl_t const * const p_ctrl);

#endif

void spi_w_gen_isr(void);

#if !BSP_MCU_GROUP_RA6W1
void spi_w_txi_isr(void);
void spi_w_rxi_isr(void);
void spi_w_tei_isr(void);
void spi_w_eri_isr(void);

#endif

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/* SPI implementation of SPI interface. */
const spi_api_t g_spi_on_spi_w =
{
    .open        = R_SPI_W_Open,
    .read        = R_SPI_W_Read,
    .write       = R_SPI_W_Write,
    .writeRead   = R_SPI_W_WriteRead,
    .close       = R_SPI_W_Close,
    .callbackSet = R_SPI_W_CallbackSet
};

#if CFG_PMGR

/* Keep SPI PMGR context here */
static spi_w_pmgr_context_t g_spi_pmgr_context[BSP_FEATURE_SPI_MAX_CHANNEL];
#endif

/*******************************************************************************************************************//**
 * @addtogroup SPI_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This functions initializes a channel for SPI communication mode. Implements @ref spi_api_t::open.
 *
 * This function performs the following tasks:
 * - Performs parameter checking and processes error conditions.
 * - Configures the peripheral registers according to the configuration.
 * - Initialize the control structure for use in other @ref SPI_API functions.
 *
 * @param[in]  p_api_ctrl                      Pointer to the instance control structure.
 * @param[in]  p_cfg                           Configuration structure which contains all the user provided configurations.
 *
 * @retval     FSP_SUCCESS                     Channel initialized successfully.
 * @retval     FSP_ERR_ALREADY_OPEN            Instance was already initialized.
 * @retval     FSP_ERR_ASSERTION               An invalid argument was given in the configuration structure.
 * @retval     FSP_ERR_UNSUPPORTED             A requested setting is not possible on this device with the current build
 *                                             configuration.
 * @retval     FSP_ERR_IP_CHANNEL_NOT_PRESENT  The channel number is invalid.
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls: @ref transfer_api_t::open
 * @note       This function is reentrant.
 **********************************************************************************************************************/
fsp_err_t R_SPI_W_Open (spi_ctrl_t * p_api_ctrl, spi_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    spi_w_instance_ctrl_t * p_ctrl = (spi_w_instance_ctrl_t *) p_api_ctrl;

#if SPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SPI_W_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_callback);
    FSP_ASSERT(NULL != p_cfg->p_extend);

    spi_w_extended_cfg_t * p_extend = (spi_w_extended_cfg_t *) p_cfg->p_extend;

 #if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1
    FSP_ASSERT(bsp_pd_is_up_check(BSP_PD_COM));
 #endif

    FSP_ERROR_RETURN(BSP_FEATURE_SPI_MAX_CHANNEL > p_cfg->channel, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    FSP_ERROR_RETURN(BSP_FEATURE_SPI_VALID_CHANNEL_MASK & (1 << (p_cfg->channel + SPI_W_CHANNEL_OFFSET)),
                     FSP_ERR_IP_CHANNEL_NOT_PRESENT);

 #if !BSP_FEATURE_TRANSFER_HAS_DTC
    FSP_ASSERT(1 != SPI_W_CFG_TRANSFER_API_SUPPORT);
 #endif

    FSP_ASSERT(0 <= p_extend->gen_irq);

 #if !BSP_MCU_GROUP_RA6W1
    if (SPI_MODE_MASTER == p_cfg->operating_mode)
    {
        FSP_ASSERT(0 <= p_cfg->tei_irq);
    }

  #if (1 == SPI_W_CFG_TRANSFER_API_SUPPORT)
    if (p_cfg->p_transfer_rx)
    {
        FSP_ASSERT(0 <= p_cfg->rxi_irq);
    }

    if (p_cfg->p_transfer_tx)
    {
        FSP_ASSERT(0 <= p_cfg->txi_irq);
    }
  #endif
 #endif

 #if SPI_W_CFG_TRANSMIT_FROM_RXI_ISR

    /* When the TXI Interrupt is handled in the RXI ISR, a TX DTC instance must be present if there is a
     * RX DTC instance present otherwise the TXI Interrupts will not be processed. */
    if (p_cfg->p_transfer_rx)
    {
        FSP_ERROR_RETURN(NULL != p_cfg->p_transfer_tx, FSP_ERR_UNSUPPORTED);
    }
 #endif

 #if BSP_MCU_GROUP_RA6W1

    /* When TX DMAC is used, RX DMAC must be used because the reception process cannot be completed in time. */
    if (p_cfg->p_transfer_tx)
    {
        FSP_ASSERT(NULL != p_cfg->p_transfer_rx);
    }
 #endif

    /* Checking for unsupported configurations. */
    if (SPI_MODE_SLAVE == p_cfg->operating_mode)
    {
        FSP_ASSERT(SPI_W_CS_SELECT_CS0 == p_extend->cs_select);
        FSP_ASSERT(SPI_W_CAPTURE_CURRENT_EDGE == p_extend->cap_edge);
    }
#endif

    /* Configure transfers if they are provided in p_cfg. */
    err = r_spi_w_transfer_config(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Get the register address of the channel. */
    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    p_ctrl->p_regs = SPI_W_REG(p_ctrl->p_cfg->channel);

    /* Configure hardware registers according to the r_spi_api configuration structure. */
    r_spi_w_hw_config(p_ctrl);

    /* Enable interrupts in NVIC. */
    r_spi_w_nvic_config(p_ctrl);

#if CFG_PMGR
    r_spi_w_subscribe_for_pmgr_notifications(p_ctrl);
#endif

    p_ctrl->open = SPI_W_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * This function receives data from a SPI device. Implements @ref spi_api_t::read.
 *
 * The function performs the following tasks:
 * - Performs parameter checking and processes error conditions.
 * - Sets up the instance to complete a SPI read operation.
 *
 * @param[in]  p_api_ctrl                 Pointer to the instance control structure.
 * @param[out] p_dest                     Reference to receiving buffer.
 * @param[in]  length                     No of transfers.
 * @param[in]  bit_width                  Data frame width.
 *
 * @retval     FSP_SUCCESS                Read operation successfully completed.
 * @retval     FSP_ERR_ASSERTION          NULL pointer to control or destination parameters or transfer length is zero.
 * @retval     FSP_ERR_NOT_OPEN           The channel has not been opened. Open channel first.
 * @retval     FSP_ERR_IN_USE             A transfer is already in progress.
 **********************************************************************************************************************/
fsp_err_t R_SPI_W_Read (spi_ctrl_t * const    p_api_ctrl,
                        void                * p_dest,
                        uint32_t const        length,
                        spi_bit_width_t const bit_width)
{
#if SPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_dest);
#endif

    return r_spi_w_write_read_common(p_api_ctrl, NULL, p_dest, length, bit_width, 0);
}

/*******************************************************************************************************************//**
 * This function transmits data to a SPI device. Implements @ref spi_api_t::write.
 *
 * The function performs the following tasks:
 * - Performs parameter checking and processes error conditions.
 * - Sets up the instance to complete a SPI write operation.
 *
 * @param[in]  p_api_ctrl                   Pointer to the instance control structure.
 * @param[in]  p_src                        Reference to transmitting buffer.
 * @param[in]  length                       No of transfers.
 * @param[in]  bit_width                    Data frame width.
 *
 * @retval     FSP_SUCCESS                  Write operation successfully completed.
 * @retval     FSP_ERR_ASSERTION            NULL pointer to control or source parameters or transfer length is zero.
 * @retval     FSP_ERR_NOT_OPEN             The channel has not been opened. Open the channel first.
 * @retval     FSP_ERR_IN_USE               A transfer is already in progress.
 **********************************************************************************************************************/
fsp_err_t R_SPI_W_Write (spi_ctrl_t * const    p_api_ctrl,
                         void const          * p_src,
                         uint32_t const        length,
                         spi_bit_width_t const bit_width)
{
#if SPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_src);
#endif

    return r_spi_w_write_read_common(p_api_ctrl, p_src, NULL, length, bit_width, 0);
}

/*******************************************************************************************************************//**
 * This function simultaneously transmits and receive data. Implements @ref spi_api_t::writeRead.
 *
 * The function performs the following tasks:
 * - Performs parameter checking and processes error conditions.
 * - Sets up the instance to complete a SPI writeRead operation.
 *
 * @param[in]  p_api_ctrl                 Pointer to the instance control structure.
 * @param[in]  p_src                      Reference to transmitting buffer.
 * @param[out] p_dest                     Reference to receiving buffer.
 * @param[in]  length                     No of transfers.
 * @param[in]  bit_width                  Data frame width.
 *
 * @retval     FSP_SUCCESS                WriteRead operation successfully completed.
 * @retval     FSP_ERR_ASSERTION          NULL pointer to control, source or destination parameters or
 *                                        transfer length is zero.
 * @retval     FSP_ERR_NOT_OPEN           The channel has not been opened. Open the channel first.
 * @retval     FSP_ERR_IN_USE             A transfer is already in progress.
 *********************************************************************************************************************/
fsp_err_t R_SPI_W_WriteRead (spi_ctrl_t * const    p_api_ctrl,
                             void const          * p_src,
                             void                * p_dest,
                             uint32_t const        length,
                             spi_bit_width_t const bit_width)
{
#if SPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);
#endif

    return r_spi_w_write_read_common(p_api_ctrl, p_src, p_dest, length, bit_width, 0);
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements spi_api_t::callbackSet
 *
 * @param[in]  p_api_ctrl                   Pointer to the instance control structure.
 * @param[in]  p_callback                   Pointer to user callback function.
 * @param[in]  p_context                    User defined context passed to callback function.
 * @param[in]  p_callback_memory            Pointer to volatile memory where callback structure can be allocated.
 *
 * @retval     FSP_SUCCESS                  Callback updated successfully.
 * @retval     FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval     FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_SPI_W_CallbackSet (spi_ctrl_t * const          p_api_ctrl,
                               void (                    * p_callback)(spi_callback_args_t *),
                               void * const                p_context,
                               spi_callback_args_t * const p_callback_memory)
{
    spi_w_instance_ctrl_t * p_ctrl = (spi_w_instance_ctrl_t *) p_api_ctrl;

#if SPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(SPI_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_ctrl->p_callback        = p_callback;
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function manages the closing of a channel by the following task. Implements @ref spi_api_t::close.
 *
 * Disables SPI operations by disabling the SPI bus.
 * - Disables the SPI peripheral.
 * - Disables all the associated interrupts.
 * - Update control structure so it will not work with @ref SPI_API functions.
 *
 * @param[in]  p_api_ctrl               Pointer to the instance control structure.
 *
 * @retval     FSP_SUCCESS              Channel successfully closed.
 * @retval     FSP_ERR_ASSERTION        A required pointer argument is NULL.
 * @retval     FSP_ERR_NOT_OPEN         The channel has not been opened. Open the channel first.
 **********************************************************************************************************************/
fsp_err_t R_SPI_W_Close (spi_ctrl_t * const p_api_ctrl)
{
    spi_w_instance_ctrl_t * p_ctrl = (spi_w_instance_ctrl_t *) p_api_ctrl;

#if SPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SPI_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_ctrl->p_cfg);
    FSP_ASSERT(NULL != p_ctrl->p_cfg->p_extend);
#endif

    spi_w_extended_cfg_t * p_extend = ((spi_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend);

    p_ctrl->open = 0U;

#if CFG_PMGR
    r_spi_w_unsubscribe_from_pmgr_notifications(p_ctrl);
#endif

#if (1 == SPI_W_CFG_TRANSFER_API_SUPPORT) || (2 == SPI_W_CFG_TRANSFER_API_SUPPORT)
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_ctrl->p_cfg->p_transfer_rx->p_api->close(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }

    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_ctrl->p_cfg->p_transfer_tx->p_api->close(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
    }
#endif

    /* Disable interrupts in NVIC. */
    R_BSP_IrqDisable(p_extend->gen_irq);

#if !BSP_MCU_GROUP_RA6W1
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);
    if (BSP_IRQ_DISABLED != p_ctrl->p_cfg->eri_ipl)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);
    }

 #if (1 == SPI_W_CFG_TRANSFER_API_SUPPORT)
    if (p_ctrl->p_cfg->p_transfer_rx)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    }

    if (p_ctrl->p_cfg->p_transfer_tx)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
    }
 #endif
#endif

    /* Disable the SPI Transfer. */
    p_ctrl->p_regs->SPI_CTRL_REG = 0U;

    /* Disable the Clock for SPI */
    if (0U == p_ctrl->p_cfg->channel)
    {
        SPI_W_RESET_CLK_COM_REG_SPI1_ENABLE(1U);
        SPI_W_SPI_CLK_CTRL_REG_SPI1_CLK_EN(0U);
    }
    else if (1U == p_ctrl->p_cfg->channel)
    {
        SPI_W_RESET_CLK_COM_REG_SPI2_ENABLE(1U);
        SPI_W_SPI_CLK_CTRL_REG_SPI2_CLK_EN(0U);
    }

#if !BSP_MCU_GROUP_RA6W1
    else if (2U == p_ctrl->p_cfg->channel)
    {
        SPI_W_RESET_CLK_COM_REG_SPI3_ENABLE(1U);
        SPI_W_SPI_CLK_CTRL_REG_SPI3_CLK_EN(0U);
    }
#endif
    else
    {
        /* Nothing TODO */
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Calculates the SPI_CLOCK_REG register value (the closest quantized value) for a desired bitrate.
 * If the desired bitrate is faster than the maximum bitrate, then the bitrate is set to the
 * maximum bitrate. If the desired bitrate is slower than the minimum bitrate, an error is returned.
 *
 * @param[in]  bitrate                Desired bitrate.
 * @param[out] spck_div               Memory location to store bitrate register settings.
 * @param[in]  channel                Selected channel.
 *
 * @retval     FSP_SUCCESS            Valid clkdiv value was calculated.
 * @retval     FSP_ERR_UNSUPPORTED    Bitrate is not achievable.
 **********************************************************************************************************************/
fsp_err_t R_SPI_W_CalculateBitrate (uint32_t bitrate, uint8_t * spck_div, uint8_t channel)
{
#if !BSP_MCU_GROUP_RA6W3
    FSP_PARAMETER_NOT_USED(channel);
#endif
    fsp_err_t err = FSP_SUCCESS;

#if SPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != spck_div);
 #if BSP_MCU_GROUP_RA6W3
    FSP_ASSERT(BSP_FEATURE_SPI_MAX_CHANNEL > channel);
 #endif
#endif

    /* Checking for division by zero. */
    if (0U == bitrate)
    {
        err = FSP_ERR_UNSUPPORTED;

        return err;
    }

#if BSP_MCU_GROUP_RA6W3

    /* desired_divider = Smallest integer greater than or equal to DIV1 / (SPIx_CORE_CLK_DIV + (1 or 2)) / bitrate. */
    uint32_t sys_clk            = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_SYS_CLK);
    uint32_t spi_core_clock_div = (CRG_TOP->SPI_CLK_CTRL_REG >> (channel * 4)) & 0x7;
    spi_core_clock_div = (spi_core_clock_div <= 1) ? (spi_core_clock_div + 1) : (spi_core_clock_div + 2);
    uint32_t desired_divider = sys_clk / (bitrate * spi_core_clock_div);
#elif BSP_MCU_GROUP_RA6W1

    /* desired_divider = Smallest integer greater than or equal to SPI_CLK / bitrate. */
    uint32_t spi_clk         = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_SPI);
    uint32_t desired_divider = spi_clk / bitrate;
#else

    /* desired_divider = Smallest integer greater than or equal to BSP_DIVN_FREQ_HZ(32Mhz) / bitrate. */
    uint32_t desired_divider = BSP_DIVN_FREQ_HZ / bitrate;
#endif

    /* Can't achieve bitrate slower than desired. */
    if (SPI_W_CLK_MAX_DIV < desired_divider)
    {
        err = FSP_ERR_UNSUPPORTED;
    }
    else if (SPI_W_CLK_MIN_DIV >= desired_divider)
    {
        /* Configure max bitrate. */
        *spck_div = SPI_W_CLK_DIV_SETTING_MIN_DIV;
    }
    else
    {
        *spck_div = ((uint8_t) ((desired_divider >> 1U) - 1U)) & SPI_W_CLK_DIV_SETTING_MASK;
    }

    return err;
}

#if SPI_W_CFG_FAST_MODE_ENABLE

/*******************************************************************************************************************//**
 * This function receives data from a SPI device in fast mode.
 *
 * The function performs the following tasks:
 * - Performs parameter checking and processes error conditions.
 * - Sets up the instance to complete a SPI read operation.
 *
 * @retval  FSP_SUCCESS                   Read operation successfully completed.
 * @retval  FSP_ERR_ASSERTION             NULL pointer to control or destination parameters or transfer length is zero.
 * @retval  FSP_ERR_NOT_OPEN              The channel has not been opened. Open channel first.
 * @retval  FSP_ERR_IN_USE                A transfer is already in progress.
 **********************************************************************************************************************/
fsp_err_t R_SPI_W_FastRead (spi_ctrl_t * const    p_api_ctrl,
                            void                * p_dest,
                            uint32_t const        length,
                            uint32_t const        max_count,
                            spi_bit_width_t const bit_width)
{
 #if SPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_dest);
    FSP_ASSERT(0U != max_count);
 #endif

    return r_spi_w_write_read_common(p_api_ctrl, NULL, p_dest, length, bit_width, max_count);
}

#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup SPI_W)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configure the given transfer instances for receiving and transmitting data without CPU intervention.
 *
 * @param[in]  p_cfg           Configuration structure with references to receive and transmit transfer instances.
 *
 * @retval     FSP_SUCCESS     The given transfer instances were configured successfully.
 * @return     See @ref RENESAS_ERROR_CODES for other possible return codes. This function internally calls
 *             @ref transfer_api_t::open.
 **********************************************************************************************************************/
static fsp_err_t r_spi_w_transfer_config (spi_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

#if (1 == SPI_W_CFG_TRANSFER_API_SUPPORT) || (2 == SPI_W_CFG_TRANSFER_API_SUPPORT)
    const transfer_instance_t * p_transfer_tx = p_cfg->p_transfer_tx;
    void * p_spdr_tx = (void *) &(SPI_W_REG(p_cfg->channel)->SPI_FIFO_WRITE_REG);
    if (NULL != p_transfer_tx)
    {
        p_transfer_tx->p_cfg->p_info->transfer_settings_word = SPI_W_TX_TRANSFER_SETTINGS;
        p_transfer_tx->p_cfg->p_info->p_dest                 = p_spdr_tx;
        p_transfer_tx->p_cfg->p_info->length                 = 1U;

        err = p_transfer_tx->p_api->open(p_transfer_tx->p_ctrl, p_transfer_tx->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    const transfer_instance_t * p_transfer_rx = p_cfg->p_transfer_rx;
    void * p_spdr_rx = (void *) &(SPI_W_REG(p_cfg->channel)->SPI_FIFO_READ_REG);
    if (NULL != p_transfer_rx)
    {
        p_transfer_rx->p_cfg->p_info->transfer_settings_word = SPI_W_RX_TRANSFER_SETTINGS;
        p_transfer_rx->p_cfg->p_info->p_src  = p_spdr_rx;
        p_transfer_rx->p_cfg->p_info->length = 1U;

        err = p_transfer_rx->p_api->open(p_transfer_rx->p_ctrl, p_transfer_rx->p_cfg);

        if ((FSP_SUCCESS != err) && p_transfer_tx)
        {
            p_transfer_tx->p_api->close(p_transfer_tx->p_ctrl);
        }
    }

#else
    FSP_PARAMETER_NOT_USED(p_cfg);
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Hardware configuration for settings given by the configuration structure.
 *
 * @param[in]  p_ctrl          Pointer to control structure.
 **********************************************************************************************************************/
static void r_spi_w_hw_config (spi_w_instance_ctrl_t * p_ctrl)
{
    uint32_t ctrl_reg        = 0U;
    uint32_t config_reg      = 0U;
    uint32_t clock_reg       = 0U;
    uint32_t fifo_config_reg = 0U;

    /* Configure operating mode setting. */
    config_reg |= (uint32_t) ((SPI_MODE_SLAVE == p_ctrl->p_cfg->operating_mode) << SPI_SPI_CONFIG_REG_SPI_SLAVE_EN_Pos);

    /* Configure Clock Phase setting. */
    config_reg |= (uint32_t) ((SPI_CLK_PHASE_EDGE_EVEN == p_ctrl->p_cfg->clk_phase) << SPI_W_CONFIG_REG_CPHA_POS);

    /* Configure Clock Polarity setting. */
    config_reg |= (uint32_t) ((SPI_CLK_POLARITY_HIGH == p_ctrl->p_cfg->clk_polarity) << SPI_W_CONFIG_REG_CPOL_POS);

    spi_w_extended_cfg_t * p_extend = ((spi_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend);

    /* Configure Full Duplex Setting. */
    ctrl_reg |= (SPI_SPI_CTRL_REG_SPI_RX_EN_Msk | SPI_SPI_CTRL_REG_SPI_TX_EN_Msk);

#if (2 == SPI_W_CFG_TRANSFER_API_SUPPORT)
    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        /* Configure DMA TX Enable Setting. */
        ctrl_reg |= SPI_SPI_CTRL_REG_SPI_DMA_TX_EN_Msk;
    }

    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        /* Configure DMA RX Enable Setting. */
        ctrl_reg |= SPI_SPI_CTRL_REG_SPI_DMA_RX_EN_Msk;
    }
#endif

    /* Configure byte swapping for 16/32-Bit mode. */
    ctrl_reg |= (uint32_t) ((SPI_W_BYTE_SWAP_ENABLE == p_extend->byte_swap) << SPI_SPI_CTRL_REG_SPI_SWAP_BYTES_Pos);

    /* Configure capture clock edge. */
    ctrl_reg |= (uint32_t) ((SPI_W_CAPTURE_NEXT_EDGE == p_extend->cap_edge) <<
                            SPI_SPI_CTRL_REG_SPI_CAPTURE_AT_NEXT_EDGE_Pos);

    /* Configure the Bitrate Division Setting */
    clock_reg |= (uint32_t) (p_extend->spck_div << SPI_SPI_CLOCK_REG_SPI_CLK_DIV_Pos);

    /* Power up the SPI module. */

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Enable the Clock for SPI */
#if BSP_MCU_GROUP_RA6W1
    CRG_TOP->CLK_AMBA_REG |= CRG_TOP_CLK_AMBA_REG_SPI_CLK_ENABLE_Msk;
    CRG_TOP->CLK_CTRL_REG |= CRG_TOP_CLK_CTRL_REG_PLL_SPI_ENABLE_Msk;
#endif

    if (0U == p_ctrl->p_cfg->channel)
    {
        SPI_W_SET_CLK_COM_REG_SPI1_ENABLE(1U);
        SPI_W_SPI_CLK_CTRL_REG_SPI1_CLK_EN(1U);
    }
    else if (1U == p_ctrl->p_cfg->channel)
    {
        SPI_W_SET_CLK_COM_REG_SPI2_ENABLE(1U);
        SPI_W_SPI_CLK_CTRL_REG_SPI2_CLK_EN(1U);
    }

#if !BSP_MCU_GROUP_RA6W1
    else if (2U == p_ctrl->p_cfg->channel)
    {
        SPI_W_SET_CLK_COM_REG_SPI3_ENABLE(1U);
        SPI_W_SPI_CLK_CTRL_REG_SPI3_CLK_EN(1U);
    }
#endif
    else
    {
        /* Nothing TODO */
    }

    FSP_CRITICAL_SECTION_EXIT;

    /* Configure RX/TX FIFO threshold level. */
    fifo_config_reg =
        ((p_extend->rx_fifo_lvl_thres << SPI_SPI_FIFO_CONFIG_REG_SPI_RX_TL_Pos) &
         SPI_SPI_FIFO_CONFIG_REG_SPI_RX_TL_Msk);
    fifo_config_reg |=
        ((p_extend->tx_fifo_lvl_thres << SPI_SPI_FIFO_CONFIG_REG_SPI_TX_TL_Pos) &
         SPI_SPI_FIFO_CONFIG_REG_SPI_TX_TL_Msk);

    /* Clear the status and disable SPI. */
    p_ctrl->p_regs->SPI_CTRL_REG = SPI_SPI_CTRL_REG_SPI_FIFO_RESET_Msk;

    /* Write registers */
    p_ctrl->p_regs->SPI_CONFIG_REG      = config_reg;
    p_ctrl->p_regs->SPI_CLOCK_REG       = clock_reg;
    p_ctrl->p_regs->SPI_FIFO_CONFIG_REG = fifo_config_reg;
    p_ctrl->p_regs->SPI_IRQ_MASK_REG    = 0U;
    p_ctrl->p_regs->SPI_CS_CONFIG_REG   = 0U;
    p_ctrl->p_regs->SPI_CTRL_REG        = ctrl_reg;
}

/*******************************************************************************************************************//**
 * Enable Interrupts in the NVIC.
 *
 * @param[in]  p_ctrl          Pointer to control structure.
 **********************************************************************************************************************/
static void r_spi_w_nvic_config (spi_w_instance_ctrl_t * p_ctrl)
{
    spi_w_extended_cfg_t * p_extend = ((spi_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend);

    R_BSP_IrqCfgEnable(p_extend->gen_irq, p_extend->gen_ipl, p_ctrl);

#if !BSP_MCU_GROUP_RA6W1
    if (BSP_IRQ_DISABLED != p_ctrl->p_cfg->tei_ipl)
    {
        /* Note tei_irq is not enabled until the last data frame is transferred. */
        R_BSP_IrqCfg(p_ctrl->p_cfg->tei_irq, p_ctrl->p_cfg->tei_ipl, p_ctrl);
    }
    if (BSP_IRQ_DISABLED != p_ctrl->p_cfg->eri_ipl)
    {
        R_BSP_IrqCfgEnable(p_ctrl->p_cfg->eri_irq, p_ctrl->p_cfg->eri_ipl, p_ctrl);
    }

 #if (1 == SPI_W_CFG_TRANSFER_API_SUPPORT)
    if (p_ctrl->p_cfg->p_transfer_rx)
    {
        R_BSP_IrqCfgEnable(p_ctrl->p_cfg->rxi_irq, p_ctrl->p_cfg->rxi_ipl, p_ctrl);
    }

    if (p_ctrl->p_cfg->p_transfer_tx)
    {
        R_BSP_IrqCfgEnable(p_ctrl->p_cfg->txi_irq, p_ctrl->p_cfg->txi_ipl, p_ctrl);
    }
 #endif
#endif
}

/*******************************************************************************************************************//**
 * Setup the bit width configuration for a transfer.
 *
 * @param[in]  p_ctrl          Pointer to control structure.
 **********************************************************************************************************************/
static void r_spi_w_bit_width_config (spi_w_instance_ctrl_t * p_ctrl)
{
    uint32_t ctrl_reg = p_ctrl->p_regs->SPI_CTRL_REG;

    /* Disable SPI. */
    p_ctrl->p_regs->SPI_CTRL_REG = 0U;             /* SPI_EN = 0 */

    /* Configure data length based on the selected bit width. */
    p_ctrl->p_regs->SPI_CONFIG_REG_b.SPI_WORD_LENGTH = p_ctrl->bit_width;
    if (SPI_BIT_WIDTH_16_BITS < p_ctrl->bit_width) /* Bit Widths > 16 bits */
    {
        p_ctrl->mask_width = (SPI_W_4_WORDS >> (SPI_BIT_WIDTH_32_BITS - p_ctrl->bit_width));
        p_ctrl->wordsize   = 4;
    }
    else if (SPI_BIT_WIDTH_8_BITS >= p_ctrl->bit_width) /* Bit Width <= 8 bits */
    {
        p_ctrl->mask_width = (SPI_W_1_WORD >> (SPI_BIT_WIDTH_8_BITS - p_ctrl->bit_width));
        p_ctrl->wordsize   = 1;
    }
    else                               /* 8 bits < Bit Width <= 16 bits */
    {
        p_ctrl->mask_width = (SPI_W_2_WORDS >> (SPI_BIT_WIDTH_16_BITS - p_ctrl->bit_width));
        p_ctrl->wordsize   = 2;
    }

    /* Restore SPI_EN. */
    p_ctrl->p_regs->SPI_CTRL_REG = ctrl_reg;
}

#if (2 == SPI_W_CFG_TRANSFER_API_SUPPORT) || !BSP_MCU_GROUP_RA6W1

/*******************************************************************************************************************//**
 * A helper function to assist on cleaning up data by masking them.
 *
 * @param[in]  p_ctrl          Pointer to control structure.
 **********************************************************************************************************************/
static void r_spi_w_transfer_zero_pad_restore (spi_w_instance_ctrl_t * p_ctrl)
{
    if ((SPI_BIT_WIDTH_8_BITS != p_ctrl->bit_width) && (SPI_BIT_WIDTH_16_BITS != p_ctrl->bit_width) &&
        (SPI_BIT_WIDTH_32_BITS != p_ctrl->bit_width) && (NULL != p_ctrl->p_rx_data))
    {
        uint16_t rx_count;
        for (rx_count = 0U; rx_count < p_ctrl->count; rx_count++)
        {
            if (SPI_BIT_WIDTH_16_BITS < p_ctrl->bit_width) /* Bit Widths > 16 bits */
            {
                uint32_t * p32 = p_ctrl->p_rx_data;
                *(p32 + rx_count) &= (uint32_t) p_ctrl->mask_width;
            }
            else if (SPI_BIT_WIDTH_8_BITS >= p_ctrl->bit_width) /* Bit Width <= 8 bits */
            {
                uint8_t * p8 = p_ctrl->p_rx_data;
                *(p8 + rx_count) &= (uint8_t) p_ctrl->mask_width;
            }
            else                       /* 8 bits < Bit Width <= 16 bits */
            {
                uint16_t * p16 = p_ctrl->p_rx_data;
                *(p16 + rx_count) &= (uint16_t) p_ctrl->mask_width;
            }
        }
    }
}

#endif

/*******************************************************************************************************************//**
 * A helper function to assist on deasserting slave, disabling SPI and call callback to signal the end of the transfer.
 *
 * @param[in]  p_ctrl          Pointer to control structure.
 **********************************************************************************************************************/
static void r_spi_w_transfer_end (spi_w_instance_ctrl_t * p_ctrl)
{
    /* Deassert the Slave Select. */
    p_ctrl->p_regs->SPI_CS_CONFIG_REG = 0U;

    /* Disable the SPI Transfer. */
#if SPI_W_CFG_FAST_MODE_ENABLE
    if (!((spi_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->skip_disable)
    {
        p_ctrl->p_regs->SPI_CTRL_REG_b.SPI_EN = 0U;
    }

#else
    p_ctrl->p_regs->SPI_CTRL_REG_b.SPI_EN = 0U;
#endif

    /* Signal that a transfer has completed. */
    r_spi_w_call_callback((spi_w_instance_ctrl_t *) p_ctrl, SPI_EVENT_TRANSFER_COMPLETE);
}

/*******************************************************************************************************************//**
 * Initiates a SPI transfer by setting the SPI_EN bit in SPI_CTRL_REG.
 *
 * @param[in]  p_ctrl            Pointer to control structure.
 *
 * @retval     FSP_SUCCESS       Transfer was started successfully.
 * @retval     FSP_ERR_ASSERTION An argument is invalid.
 * @retval     FSP_ERR_NOT_OPEN  The instance has not been initialized.
 * @retval     FSP_ERR_IN_USE    A transfer is already in progress.
 * @return     See @ref RENESAS_ERROR_CODES for other possible return codes. This function internally calls
 *             @ref transfer_api_t::reconfigure.
 * Note: When not using the DMAC to transmit, this function pre-loads the SPI shift-register and shift-register-buffer
 * instead of waiting for the transmit buffer empty interrupt. This is required when transmitting from the
 * Receive Buffer Full interrupt, but it does not interfere with transmitting when using the transmit buffer empty
 * interrupt.
 **********************************************************************************************************************/
static fsp_err_t r_spi_w_start_transfer (spi_w_instance_ctrl_t * p_ctrl)
{
    fsp_err_t              err          = FSP_SUCCESS;
    uint32_t               irq_mask_reg = 0U;
    uint32_t               tx_data;
    spi_w_extended_cfg_t * p_extend = ((spi_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend);

    /* Clear the status. */
    p_ctrl->p_regs->SPI_CTRL_REG_b.SPI_FIFO_RESET = 1U;
    p_ctrl->p_regs->SPI_CTRL_REG_b.SPI_FIFO_RESET = 0U;

#if !BSP_MCU_GROUP_RA6W1

    /* Enable Receive dedicated interrupt. */
    irq_mask_reg = SPI_SPI_IRQ_MASK_REG_SPI_RX_IRQ_MASK_Msk;

    /* Enable Transmit end dedicated interrupt (TX FIFO empty). */
    irq_mask_reg |= SPI_SPI_IRQ_MASK_REG_SPI_TXE_IRQ_MASK_Msk;

    /* Enable Error dedicated interrupt (RX FIFO overflow). */
    irq_mask_reg |= SPI_SPI_IRQ_MASK_REG_SPI_IRQ_MASK_RX_FIFO_OVFL_Msk;

    /* Unmask Idle decicated interrupt (transastion completion for Master). */
    /* Note: Idle Interrupt (tei_irq) is not enabled until the last data frame is transferred. */
    irq_mask_reg |= SPI_SPI_IRQ_MASK_REG_SPI_TXR_IRQ_MASK_Msk;
#endif

    if (NULL == p_ctrl->p_cfg->p_transfer_rx)
    {
        /* Enable Receive Buffer Full interrupt. */
        irq_mask_reg |= SPI_SPI_IRQ_MASK_REG_SPI_IRQ_MASK_RX_FULL_Msk;
    }

    if (SPI_MODE_MASTER == p_ctrl->p_cfg->operating_mode)
    {
        /* Assert the Slave Select. */
        p_ctrl->p_regs->SPI_CS_CONFIG_REG = (uint32_t) p_extend->cs_select;
    }

    if (NULL == p_ctrl->p_cfg->p_transfer_tx)
    {
        /* Only the first word of the Slave transmission data must be set to SPI_TXBUFFER_FORCE_REG register,
         * otherwise the transmission will be delayed. */
        if (SPI_MODE_SLAVE == p_ctrl->p_cfg->operating_mode)
        {
            if (NULL == p_ctrl->p_tx_data)
            {
                /* Transmit zero if no tx buffer present. */
                tx_data = 0U;
            }
            else
            {
                if (SPI_BIT_WIDTH_16_BITS < p_ctrl->bit_width)      /* Bit Widths > 16 bits */
                {
                    tx_data = *((uint32_t *) p_ctrl->p_tx_data);
                }
                else if (SPI_BIT_WIDTH_8_BITS >= p_ctrl->bit_width) /* Bit Width <= 8 bits */
                {
                    tx_data = (uint32_t) (*((uint8_t *) p_ctrl->p_tx_data));
                }
                else                                                /* 8 bits < Bit Width <= 16 bits */
                {
                    tx_data = (uint32_t) (*((uint16_t *) p_ctrl->p_tx_data));
                }

                p_ctrl->p_tx_data = (void *) ((uint8_t *) p_ctrl->p_tx_data + p_ctrl->wordsize);
            }

            p_ctrl->p_regs->SPI_TXBUFFER_FORCE_REG = tx_data;
            p_ctrl->tx_count++;
        }
    }

    /* Must call transmit to kick off transfer when transmitting.
     * Multiple transmits significantly improves slave mode performance in high bitrate. */
    if (NULL == p_ctrl->p_cfg->p_transfer_tx)
    {
        r_spi_w_transmit(p_ctrl);
    }

#if SPI_W_CFG_TRANSMIT_FROM_RXI_ISR

    if (NULL == p_ctrl->p_cfg->p_transfer_tx)
    {
        /* Set IRQ Mask */
        p_ctrl->p_regs->SPI_IRQ_MASK_REG = irq_mask_reg;
            
        /* Enable the SPI Transfer. */
        p_ctrl->p_regs->SPI_CTRL_REG_b.SPI_EN = 1U;

        return err;
    }
#endif

    if (((NULL != p_ctrl->p_tx_data) || (SPI_MODE_MASTER == p_ctrl->p_cfg->operating_mode)) &&
        (NULL == p_ctrl->p_cfg->p_transfer_tx))
    {
        /* Enable the TX buffer empty interrupt. */
        irq_mask_reg |= SPI_SPI_IRQ_MASK_REG_SPI_IRQ_MASK_TX_EMPTY_Msk;
    }

#if (1 == SPI_W_CFG_TRANSFER_API_SUPPORT) || (2 == SPI_W_CFG_TRANSFER_API_SUPPORT)

    /* Only the first word of the Slave transmission data must be set to SPI_TXBUFFER_FORCE_REG register,
     * otherwise the transmission will be delayed. */
    if ((NULL != p_ctrl->p_cfg->p_transfer_tx) && (NULL != p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_src))
    {
        if (SPI_MODE_SLAVE == p_ctrl->p_cfg->operating_mode)
        {
            if (SPI_BIT_WIDTH_16_BITS < p_ctrl->bit_width)
            {
                tx_data = *((uint32_t *) p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_src);
            }
            else if (SPI_BIT_WIDTH_8_BITS >= p_ctrl->bit_width)
            {
                tx_data = (uint32_t) (*((uint8_t *) p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_src));
            }
            else
            {
                tx_data = (uint32_t) (*((uint16_t *) p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_src));
            }

            if (TRANSFER_ADDR_MODE_FIXED !=
                p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->transfer_settings_word_b.src_addr_mode)
            {
                p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_src =
                    (void *) ((uint8_t *) p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_src + p_ctrl->wordsize);
            }

            p_ctrl->p_regs->SPI_TXBUFFER_FORCE_REG = tx_data;
            p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->length--;
        }

        if (0U != p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->length)
        {
            err = p_ctrl->p_cfg->p_transfer_tx->p_api->reconfigure(p_ctrl->p_cfg->p_transfer_tx->p_ctrl,
                                                                   p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            err = p_ctrl->p_cfg->p_transfer_tx->p_api->enable(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        }
    }
#endif

    /* Set IRQ Mask */
    p_ctrl->p_regs->SPI_IRQ_MASK_REG = irq_mask_reg;

    /* Enable the SPI Transfer. */
    p_ctrl->p_regs->SPI_CTRL_REG_b.SPI_EN = 1U;

    return err;
}

/*******************************************************************************************************************//**
 * Configures the driver state and initiates a SPI transfer for all modes of operation.
 *
 * @param[in]  p_api_ctrl           Pointer to control structure.
 * @param[in]  p_src                Buffer to transmit data from.
 * @param[out] p_dest               Buffer to store received data in.
 * @param[in]  length               Number of transfers.
 * @param[in]  bit_width            Data frame size (8-Bit, 16-Bit, 32-Bit).
 * @param[in]  fast_max_count       Maximum read count used only for R_SPI_W_FastRead.
 *
 * @retval     FSP_SUCCESS          Transfer was started successfully.
 * @retval     FSP_ERR_ASSERTION    An argument is invalid.
 * @retval     FSP_ERR_NOT_OPEN     The instance has not been initialized.
 * @retval     FSP_ERR_IN_USE       A transfer is already in progress.
 * @return     See @ref RENESAS_ERROR_CODES for other possible return codes. This function internally calls
 *             @ref transfer_api_t::reconfigure.
 **********************************************************************************************************************/
static fsp_err_t r_spi_w_write_read_common (spi_ctrl_t * const    p_api_ctrl,
                                            void const          * p_src,
                                            void                * p_dest,
                                            uint32_t const        length,
                                            spi_bit_width_t const bit_width,
                                            uint32_t const        fast_max_count)
{
    spi_w_instance_ctrl_t * p_ctrl = (spi_w_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t               err    = FSP_SUCCESS;
#if !SPI_W_CFG_FAST_MODE_ENABLE
    FSP_PARAMETER_NOT_USED(fast_max_count);
#endif

#if SPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SPI_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(0U != length);

 #if (1 == SPI_W_CFG_TRANSFER_API_SUPPORT) || (2 == SPI_W_CFG_TRANSFER_API_SUPPORT)
    if ((NULL != p_ctrl->p_cfg->p_transfer_rx) || (NULL != p_ctrl->p_cfg->p_transfer_tx))
    {
        FSP_ASSERT(SPI_W_TRANSFER_MAX_LENGTH >= length);
    }
 #endif
#endif

#if SPI_W_CFG_FAST_MODE_ENABLE
    if (0 != fast_max_count)
    {
        p_ctrl->fast_mode_st   = SPI_W_FAST_MODE_ON;
        p_ctrl->fast_max_count = fast_max_count;
    }
    else
    {
        p_ctrl->fast_mode_st = SPI_W_FAST_MODE_OFF;
    }

    if (!((spi_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->skip_disable)
    {
        FSP_ERROR_RETURN(0U == (p_ctrl->p_regs->SPI_CTRL_REG & SPI_SPI_CTRL_REG_SPI_EN_Msk), FSP_ERR_IN_USE);
    }

#else
    if (!((spi_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->skip_busy_check)
    {
        FSP_ERROR_RETURN(0U == (p_ctrl->p_regs->SPI_CTRL_REG & SPI_SPI_CTRL_REG_SPI_EN_Msk), FSP_ERR_IN_USE);
    }
#endif

    p_ctrl->p_tx_data = p_src;
    p_ctrl->p_rx_data = p_dest;
    p_ctrl->tx_count  = 0U;
    p_ctrl->rx_count  = 0U;
    p_ctrl->count     = length;
    p_ctrl->bit_width = bit_width;

#if (1 == SPI_W_CFG_TRANSFER_API_SUPPORT) || (2 == SPI_W_CFG_TRANSFER_API_SUPPORT)
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        /* When the rxi interrupt is called, all transfers will be finished. */
        p_ctrl->rx_count = length;

        /* Configure the receive DMA instance. */
        if (SPI_BIT_WIDTH_16_BITS < p_ctrl->bit_width)
        {
            p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->transfer_settings_word_b.size = TRANSFER_SIZE_4_BYTE;
        }
        else if (SPI_BIT_WIDTH_8_BITS >= p_ctrl->bit_width)
        {
            p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->transfer_settings_word_b.size = TRANSFER_SIZE_1_BYTE;
        }
        else
        {
            p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->transfer_settings_word_b.size = TRANSFER_SIZE_2_BYTE;
        }

        p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->transfer_settings_word_b.dest_addr_mode =
            TRANSFER_ADDR_MODE_INCREMENTED;
        p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->length = (uint16_t) length;
        p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->p_dest = p_dest;

        if (NULL == p_dest)
        {
            static uint32_t dummy_rx;
            p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->transfer_settings_word_b.dest_addr_mode =
                TRANSFER_ADDR_MODE_FIXED;
            p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->p_dest = &dummy_rx;
        }

        err = p_ctrl->p_cfg->p_transfer_rx->p_api->reconfigure(p_ctrl->p_cfg->p_transfer_rx->p_ctrl,
                                                               p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err = p_ctrl->p_cfg->p_transfer_rx->p_api->enable(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        /* When the txi interrupt is called, all transfers will be finished. */
        p_ctrl->tx_count = length;

        /* Configure the transmit DMA instance. */
        if (SPI_BIT_WIDTH_16_BITS < p_ctrl->bit_width)
        {
            p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->transfer_settings_word_b.size = TRANSFER_SIZE_4_BYTE;
        }
        else if (SPI_BIT_WIDTH_8_BITS >= p_ctrl->bit_width)
        {
            p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->transfer_settings_word_b.size = TRANSFER_SIZE_1_BYTE;
        }
        else
        {
            p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->transfer_settings_word_b.size = TRANSFER_SIZE_2_BYTE;
        }

        p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->transfer_settings_word_b.src_addr_mode =
            TRANSFER_ADDR_MODE_INCREMENTED;
        p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->length = (uint16_t) length;
        p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_src  = p_src;

        if (NULL == p_src)
        {
            static uint32_t dummy_tx = 0U;
            p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->transfer_settings_word_b.src_addr_mode =
                TRANSFER_ADDR_MODE_FIXED;
            p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_src = &dummy_tx;
        }
    }
#endif

    r_spi_w_bit_width_config(p_ctrl);
    err = r_spi_w_start_transfer(p_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * Copy configured bit width from the SPI data register to the current rx data location.
 * If the receive buffer is NULL, just read the SPI data register.
 * If the total transfer length has already been received then do nothing.
 *
 * @param[in]  p_ctrl          Pointer to control structure.
 **********************************************************************************************************************/
static void r_spi_w_receive (spi_w_instance_ctrl_t * p_ctrl)
{
    uint32_t    data;
#if SPI_W_CFG_FAST_MODE_ENABLE
    uint8_t   * p_fast_data = p_ctrl->fast_mode_buffer + p_ctrl->rx_count;
#endif

    while ((p_ctrl->rx_count < p_ctrl->count) && p_ctrl->p_regs->SPI_FIFO_STATUS_REG_b.SPI_RX_FIFO_LEVEL)
    {
        data = p_ctrl->p_regs->SPI_FIFO_READ_REG;
        p_ctrl->rx_count++;

        if (NULL != p_ctrl->p_rx_data)
        {
            data &= p_ctrl->mask_width;
 
            if (SPI_BIT_WIDTH_8_BITS >= p_ctrl->bit_width)      /* Bit Width <= 8 bits */
            {
                *((uint8_t *) p_ctrl->p_rx_data) = (uint8_t) data;

#if SPI_W_CFG_FAST_MODE_ENABLE
                if ((SPI_W_FAST_MODE_ON == p_ctrl->fast_mode_st) && (SPI_W_FAST_READ_HEADER_SIZE > p_ctrl->rx_count))
                {
                    *p_fast_data++ = (uint8_t ) data;
                }
#endif
            }
            else if (SPI_BIT_WIDTH_16_BITS < p_ctrl->bit_width) /* Bit Widths > 16 bits */
            {
                *((uint32_t *) p_ctrl->p_rx_data)  = (uint32_t) data;
            }
            else                                                /* 8 bits < Bit Width <= 16 bits */
            {
                *((uint16_t *) p_ctrl->p_rx_data)  = (uint16_t) data;
            }

            p_ctrl->p_rx_data = (void *) ((uint8_t *) p_ctrl->p_rx_data + p_ctrl->wordsize);
        }
    }
}

/*******************************************************************************************************************//**
 * Copy configured bit width from the current tx data location into the SPI data register.
 * If the transmit buffer is NULL, then write zero to the SPI data register.
 * If the total transfer length has already been transmitted then do nothing.
 *
 * @param[in]  p_ctrl          Pointer to control structure.
 **********************************************************************************************************************/
static void r_spi_w_transmit (spi_w_instance_ctrl_t * p_ctrl)
{
    uint32_t fifo_lvl_rem;
    uint32_t tx_data       = 0U;  /* Transmit zero if no tx buffer present. */

#if BSP_MCU_GROUP_RA6W3
    if (0U == p_ctrl->p_cfg->channel)
    {
        fifo_lvl_rem = (SPI_W_TX_FIFO_MAX_SIZE_BYTE_SPI1 - p_ctrl->p_regs->SPI_FIFO_STATUS_REG_b.SPI_TX_FIFO_LEVEL);
    }
    else
    {
        fifo_lvl_rem = (SPI_W_TX_FIFO_MAX_SIZE_BYTE - p_ctrl->p_regs->SPI_FIFO_STATUS_REG_b.SPI_TX_FIFO_LEVEL);
    }

#else
    fifo_lvl_rem = (SPI_W_RX_FIFO_MAX_SIZE_BYTE - p_ctrl->p_regs->SPI_FIFO_STATUS_REG_b.SPI_TX_FIFO_LEVEL);
#endif

    fifo_lvl_rem /= p_ctrl->wordsize;

    while ((p_ctrl->tx_count < p_ctrl->count) && fifo_lvl_rem--)
    {
        if (NULL != p_ctrl->p_tx_data)
        {
            if (SPI_BIT_WIDTH_16_BITS < p_ctrl->bit_width)      /* Bit Widths > 16 bits */
            {
                tx_data = *((uint32_t *) p_ctrl->p_tx_data);
            }
            else if (SPI_BIT_WIDTH_8_BITS >= p_ctrl->bit_width) /* Bit Width <= 8 bits */
            {
                tx_data = (uint32_t) (*((uint8_t *) p_ctrl->p_tx_data));
            }
            else                                                /* 8 bits < Bit Width <= 16 bits */
            {
                tx_data = (uint32_t) (*((uint16_t *) p_ctrl->p_tx_data));
            }

            p_ctrl->p_tx_data = (void *) ((uint8_t *) p_ctrl->p_tx_data + p_ctrl->wordsize);
        }

        p_ctrl->p_regs->SPI_FIFO_WRITE_REG = tx_data;
        p_ctrl->tx_count++;
    }
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to SPI instance control block.
 * @param[in]     event      Event code.
 **********************************************************************************************************************/
static void r_spi_w_call_callback (spi_w_instance_ctrl_t * p_ctrl, spi_event_t event)
{
    spi_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    spi_callback_args_t * p_args = p_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    p_args->channel   = p_ctrl->p_cfg->channel;
    p_args->event     = event;
    p_args->p_context = p_ctrl->p_context;

    p_ctrl->p_callback(p_args);

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

#if (2 == SPI_W_CFG_TRANSFER_API_SUPPORT)

/*******************************************************************************************************************//**
 * Callback that must be called after an RX DMAC transfer completes.
 *
 * @param[in]     p_ctrl     Pointer to SPI instance control block
 **********************************************************************************************************************/
void spi_w_rx_dmac_callback (spi_w_instance_ctrl_t * p_ctrl)
{
#if !BSP_MCU_GROUP_RA6W1
    if (SPI_MODE_MASTER == p_ctrl->p_cfg->operating_mode)
    {
        /* If Generic ISR is too slow to keep up at high bitrates,
         * the hardware will generate Idle Interrupt before all of the transfers are completed.
         * By enabling Idle Interrupt here, all of the transfers are guaranteed to be completed. */
        R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->tei_irq);
    }
    else
#endif
    {
        r_spi_w_transfer_zero_pad_restore(p_ctrl);

        r_spi_w_transfer_end(p_ctrl);
    }
}

/*******************************************************************************************************************//**
 * Callback that must be called after a TX DMAC transfer completes.
 *
 * @param[in]     p_ctrl     Pointer to SPI instance control block
 **********************************************************************************************************************/
void spi_w_tx_dmac_callback (spi_w_instance_ctrl_t const * const p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
}

#endif

/*******************************************************************************************************************//**
 * Generic ISR for SPI.
 **********************************************************************************************************************/
void spi_w_gen_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

#if !BSP_MCU_GROUP_RA6W1
    R_BSP_IrqStatusClear(irq);
#endif

    spi_w_instance_ctrl_t * p_ctrl = (spi_w_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
#if BSP_MCU_GROUP_RA6W1
    uint32_t status_reg = p_ctrl->p_regs->SPI_STATUS_REG;
#endif

    /* Rx Overflow error interrupt. */
    if (1U == p_ctrl->p_regs->SPI_FIFO_STATUS_REG_b.SPI_RX_FIFO_OVFL)
    {
        /* Disable SPI interrupt. */
        p_ctrl->p_regs->SPI_IRQ_MASK_REG = 0U;

        /* Deassert the Slave Select. */
        p_ctrl->p_regs->SPI_CS_CONFIG_REG = 0U;

        /* Disable the SPI Transfer. */
        p_ctrl->p_regs->SPI_CTRL_REG_b.SPI_EN = 0U;

        /* Reset FIFO. */
        p_ctrl->p_regs->SPI_CTRL_REG_b.SPI_FIFO_RESET = 1U;

        if (NULL != p_ctrl->p_cfg->p_transfer_rx)
        {
            /* Disable Rx DMA/DTC */
            p_ctrl->p_cfg->p_transfer_rx->p_api->disable(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
        }

        /* Receive Buffer Overflow Error. */
        r_spi_w_call_callback(p_ctrl, SPI_EVENT_ERR_READ_OVERFLOW);
    }

    /* FIFO RX full interrupt. */
#if BSP_MCU_GROUP_RA6W1
    if ((0U != (status_reg & SPI_SPI_STATUS_REG_SPI_STATUS_RX_FULL_Msk)) &&
        (1U == p_ctrl->p_regs->SPI_IRQ_MASK_REG_b.SPI_IRQ_MASK_RX_FULL))
#else
    if (1U == p_ctrl->p_regs->SPI_IRQ_MASK_REG_b.SPI_IRQ_MASK_RX_FULL)
#endif
    {
        r_spi_w_receive(p_ctrl);

#if SPI_W_CFG_FAST_MODE_ENABLE
        if (SPI_W_FAST_MODE_ON == p_ctrl->fast_mode_st)
        {
            if (SPI_W_FAST_READ_HEADER_SIZE == p_ctrl->rx_count)
            {
                uint32_t inc_length = (uint32_t) (p_ctrl->fast_mode_buffer[5] << 16) |
                                      (p_ctrl->fast_mode_buffer[6] << 8) |
                                      (p_ctrl->fast_mode_buffer[7]);

                p_ctrl->count = SPI_W_FAST_READ_HEADER_SIZE + inc_length;
                p_ctrl->count = (p_ctrl->count <= p_ctrl->fast_max_count) ? p_ctrl->count : p_ctrl->fast_max_count;
            }
            else if ((SPI_W_FAST_READ_HEADER_SIZE < p_ctrl->rx_count) && (p_ctrl->rx_count == p_ctrl->count))
            {
                /* Disable Receive Buffer Full interrupt. */
                p_ctrl->p_regs->SPI_IRQ_MASK_REG_b.SPI_IRQ_MASK_RX_FULL = 0U;

                /* Deassert the Slave Select. */
                p_ctrl->p_regs->SPI_CS_CONFIG_REG = 0U;

                /* Disable the SPI Transfer. */
                if (!((spi_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->skip_disable)
                {
                    p_ctrl->p_regs->SPI_CTRL_REG_b.SPI_EN = 0U;
                }

                /* Signal that a transfer has completed. */
                r_spi_w_call_callback(p_ctrl, SPI_EVENT_TRANSFER_COMPLETE);

                p_ctrl->fast_mode_st = SPI_W_FAST_MODE_OFF;
            }
        }
        else
#endif
        {
            if (p_ctrl->rx_count == p_ctrl->count)
            {
                /* Disable Receive Buffer Full interrupt. */
                p_ctrl->p_regs->SPI_IRQ_MASK_REG_b.SPI_IRQ_MASK_RX_FULL = 0U;

#if BSP_MCU_GROUP_RA6W1
                r_spi_w_transfer_end(p_ctrl);
#else
                if (SPI_MODE_MASTER == p_ctrl->p_cfg->operating_mode)
                {
                    /* If Generic ISR is too slow to keep up at high bitrates,
                     * the hardware will generate Idle Interrupt before all of the transfers are completed.
                     * By enabling Idle Interrupt here, all of the transfers are guaranteed to be completed. */
                    R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->tei_irq);
                }
                else
                {
                    r_spi_w_transfer_end(p_ctrl);
                }    
#endif
            }
        }

#if SPI_W_CFG_TRANSMIT_FROM_RXI_ISR
        if (NULL == p_ctrl->p_cfg->p_transfer_tx)
        {
            r_spi_w_transmit(p_ctrl);
        }
#endif
    }

#if !SPI_W_CFG_TRANSMIT_FROM_RXI_ISR

    /*  FIFO TX empty interrupt. */
 #if BSP_MCU_GROUP_RA6W1
    if ((0U != (status_reg & SPI_SPI_STATUS_REG_SPI_STATUS_TX_EMPTY_Msk)) &&
        (1U == p_ctrl->p_regs->SPI_IRQ_MASK_REG_b.SPI_IRQ_MASK_TX_EMPTY))
 #else
    if (1U == p_ctrl->p_regs->SPI_IRQ_MASK_REG_b.SPI_IRQ_MASK_TX_EMPTY)
 #endif
    {
        r_spi_w_transmit(p_ctrl);

        if (p_ctrl->tx_count == p_ctrl->count)
        {
            /* Disable the TX buffer empty interrupt. */
            p_ctrl->p_regs->SPI_IRQ_MASK_REG_b.SPI_IRQ_MASK_TX_EMPTY = 0U;
        }
    }
#endif

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#if !BSP_MCU_GROUP_RA6W1

/*******************************************************************************************************************//**
 * ISR called when the SPI peripheral transitions from the transferring state to the IDLE state.
 **********************************************************************************************************************/
void spi_w_tei_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    R_BSP_IrqStatusClear(irq);

    spi_w_instance_ctrl_t * p_ctrl = R_FSP_IsrContextGet(irq);

    if (p_ctrl->p_cfg->p_transfer_rx)
    {
        r_spi_w_transfer_zero_pad_restore(p_ctrl);
    }

    r_spi_w_transfer_end(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * ISR called when data is copied from the SPI data register into the SPI shift register.
 **********************************************************************************************************************/
void spi_w_txi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * ISR called when data is loaded into SPI data register from the shift register.
 **********************************************************************************************************************/
void spi_w_rxi_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    /* Handle interrupt for a channel associated with received IRQn. */
    spi_w_instance_ctrl_t * p_ctrl = R_FSP_IsrContextGet(irq);

    if (SPI_MODE_MASTER == p_ctrl->p_cfg->operating_mode)
    {
        /* If Generic ISR is too slow to keep up at high bitrates,
         * the hardware will generate Idle Interrupt before all of the transfers are completed.
         * By enabling Idle Interrupt here, all of the transfers are guaranteed to be completed. */
        R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->tei_irq);
    }
    else
    {
        r_spi_w_transfer_zero_pad_restore(p_ctrl);

        r_spi_w_transfer_end(p_ctrl);
    } 

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * ISR called in the event that an error occurs (Ex: RX_OVERFLOW).
 **********************************************************************************************************************/
void spi_w_eri_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    R_BSP_IrqStatusClear(irq);

    /* Handle interrupt for a channel associated with received IRQn. */
    spi_w_instance_ctrl_t * p_ctrl = R_FSP_IsrContextGet(irq);

    /* Disable SPI interrupt. */
    p_ctrl->p_regs->SPI_IRQ_MASK_REG = 0U;

    /* Deassert the Slave Select. */
    p_ctrl->p_regs->SPI_CS_CONFIG_REG = 0U;

    /* Disable the SPI Transfer. */
    p_ctrl->p_regs->SPI_CTRL_REG_b.SPI_EN = 0U;

    /* Reset FIFO. */
    p_ctrl->p_regs->SPI_CTRL_REG_b.SPI_FIFO_RESET = 1U;

    /* Restore context if RTOS is used. */
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        /* Disable Rx DMA */
        p_ctrl->p_cfg->p_transfer_rx->p_api->disable(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }

    /* Receive Buffer Overflow Error. */
    r_spi_w_call_callback(p_ctrl, SPI_EVENT_ERR_READ_OVERFLOW);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#endif

#if CFG_PMGR

/*******************************************************************************************************************/ /**
 * Prepare SPI for sleep mode 4/5
 *
 * @param[in] p_context Pointer to PMGR interface of SPI instance
 **********************************************************************************************************************/
static fsp_err_t spi_w_enter_sleep (spi_w_pmgr_context_t * p_context)
{
    fsp_err_t err = FSP_SUCCESS;
 #if SPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_context);
 #endif

    spi_w_instance_ctrl_t * p_ctrl = (spi_w_instance_ctrl_t *) p_context->p_ctrl;

    p_ctrl->open = SPI_W_SLEEPING;

    return err;
}

/*******************************************************************************************************************/ /**
 * Restore SPI from wakeup
 *
 * @param[in] p_context Pointer to PMGR interface of SPI instance
 **********************************************************************************************************************/
static fsp_err_t spi_w_wakeup (spi_w_pmgr_context_t * p_context)
{
    fsp_err_t err = FSP_SUCCESS;
 #if SPI_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_context);
 #endif

    spi_w_instance_ctrl_t * p_ctrl = (spi_w_instance_ctrl_t *) p_context->p_ctrl;

    /* Configure hardware registers according to the r_spi_api configuration structure. */
    r_spi_w_hw_config(p_ctrl);

    /* Enable interrupts in NVIC. */
    r_spi_w_nvic_config(p_ctrl);

    p_ctrl->open = SPI_W_OPEN;

    return err;
}

static void spi_w_pmgr_callback (pmgr_callback_args_t * p_args)
{
    pmgr_instance_info_t * p_pmgr_info = (pmgr_instance_info_t *) p_args->p_instance_info;

    if (PMGR_LLD_POWER_MODE_SLEEP4 == p_pmgr_info->power_mode)
    {
        if (PMGR_EVENT_ENTERING_SLEEP == p_args->event)
        {
            /* Entering sleep 4/5 - close SPI */
            spi_w_enter_sleep((spi_w_pmgr_context_t *) p_args->p_context);
        }
        else if (PMGR_EVENT_EXITING_SLEEP == p_args->event)
        {
            /* Open SPI with previous settings */
            spi_w_wakeup((spi_w_pmgr_context_t *) p_args->p_context);
        }
    }
}

static fsp_err_t r_spi_w_subscribe_for_pmgr_notifications (spi_w_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t     err       = FSP_SUCCESS;
    pmgr_ctrl_t * pmgr_ctrl = NULL;

    spi_w_pmgr_context_t * context = &g_spi_pmgr_context[p_ctrl->p_cfg->channel];

    context->pmgr_info.power_mode    = PMGR_LLD_POWER_MODE_SLEEP4;
    context->pmgr_info.wake_source   = PMGR_WAKE_SOURCE_NONE,
    context->pmgr_notifier_ext.order = PMGR_W_NOTIFIER_ORDER_SYS_HIGH;
    context->p_ctrl = p_ctrl;

    context->clbk_args.constraints     = PMGR_CONSTRAINT_NONE;
    context->clbk_args.event           = PMGR_EVENT_NOT_SET;
    context->clbk_args.p_context       = (void *) context;
    context->clbk_args.p_instance_info = (void *) &context->pmgr_info;

    pmgr_ctrl = RM_PMGR_W_get_ctrl();
    FSP_ASSERT(NULL != pmgr_ctrl);

    err = RM_PMGR_W_notifier_register(pmgr_ctrl, spi_w_pmgr_callback, &context->clbk_args, &context->pmgr_notifier_ext);
    FSP_ASSERT(FSP_SUCCESS == err);

    return FSP_SUCCESS;
}

static fsp_err_t r_spi_w_unsubscribe_from_pmgr_notifications (spi_w_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t     err       = FSP_SUCCESS;
    pmgr_ctrl_t * pmgr_ctrl = NULL;

    pmgr_ctrl = RM_PMGR_W_get_ctrl();
    FSP_ASSERT(NULL != pmgr_ctrl);

    spi_w_pmgr_context_t * context = &g_spi_pmgr_context[p_ctrl->p_cfg->channel];
    err = RM_PMGR_W_notifier_unregister(pmgr_ctrl, context->pmgr_notifier_ext.notifier_id);
    FSP_ASSERT(FSP_SUCCESS == err);

    return FSP_SUCCESS;
}

#endif
