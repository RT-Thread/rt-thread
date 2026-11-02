/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_uart_w.h"
#if UART_W_DMA_SUPPORT_ENABLE == 1
 #include "r_dmac_w.h"
#endif
#if BSP_MCU_GROUP_RA6W1
 #if (CFG_PMGR == 1)
  #include "rm_pmgr_w_instance.h"
 #endif
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* UART number */
#define UART_W_INDEX_MAX                (2U)
#define UART_W_MASK_9BITS               (0x01FFU)
#define COEFFICIENT_10                  (10U)
#define COEFFICIENT_1000                (1000U)
#if !BSP_MCU_GROUP_RA6W1
 #define UART_W_DATA_BITS_9             0
#endif

/* UART interrupt ID */
#define UART_W_INTR_ID_NO_PEND          (0x00)
#define UART_W_INTR_MDM_STATUS          (UART_UART_MIS_REG_RIMMIS_Msk | UART_UART_MIS_REG_CTSMMIS_Msk | \
                                         UART_UART_MIS_REG_DCDMMIS_Msk | UART_UART_MIS_REG_DSRMMIS_Msk)
#define UART_W_INTR_ID_TI               (UART_UART_MIS_REG_TXMIS_Msk)
#define UART_W_INTR_ID_RDI              (UART_UART_MIS_REG_RXMIS_Msk)
#define UART_W_INTR_ID_RLSI             (UART_UART_MIS_REG_FEMIS_Msk | UART_UART_MIS_REG_PEMIS_Msk | \
                                         UART_UART_MIS_REG_BEMIS_Msk | UART_UART_MIS_REG_OEMIS_Msk)
#define UART_W_INTR_ID_TIMEOUT          (UART_UART_MIS_REG_RTMIS_Msk)

#define UART_W_INTR_MASK                (UART_UART_MIS_REG_RIMMIS_Msk | UART_UART_MIS_REG_CTSMMIS_Msk |  \
                                         UART_UART_MIS_REG_DCDMMIS_Msk | UART_UART_MIS_REG_DSRMMIS_Msk | \
                                         UART_UART_MIS_REG_RXMIS_Msk | UART_UART_MIS_REG_TXMIS_Msk |     \
                                         UART_UART_MIS_REG_RTMIS_Msk | UART_UART_MIS_REG_FEMIS_Msk |     \
                                         UART_UART_MIS_REG_PEMIS_Msk | UART_UART_MIS_REG_BEMIS_Msk |     \
                                         UART_UART_MIS_REG_OEMIS_Msk)

#define UART_W_INTR_CLEAR_MASK          (UART_UART_ICR_REG_RIMIC_Msk | UART_UART_ICR_REG_CTSMIC_Msk |  \
                                         UART_UART_ICR_REG_DCDMIC_Msk | UART_UART_ICR_REG_DSRMIC_Msk | \
                                         UART_UART_ICR_REG_RXIC_Msk | UART_UART_ICR_REG_TXIC_Msk |     \
                                         UART_UART_ICR_REG_RTIC_Msk | UART_UART_ICR_REG_FEIC_Msk |     \
                                         UART_UART_ICR_REG_PEIC_Msk | UART_UART_ICR_REG_BEIC_Msk |     \
                                         UART_UART_ICR_REG_OEIC_Msk)

#define UART_W_EVENT_NO_EVENT           (0)

/* No limit to the number of bytes to read or write if DMA is not used. */
#define UART_W_MAX_READ_WRITE_NO_DMA    (0xFFFFFFFFU)

/* "UART" in ASCII.  Used to determine if the control block is open. */
#define UART_W_OPEN                     (0x55655A5AU)
#if BSP_MCU_GROUP_RA6W1
 #if CFG_PMGR == 1
  #define UART_W_SLEEP                  (0xAAAAAAAAU)
 #endif
#endif

#define UART_W_INT_MASK                 (0xFFFU)
#define UART_W_FRA_MASK                 (0x3FU)

#define UART_W_REG_SIZE                 (UART2_BASE - UART_BASE)

#define UART_W_RX_TRANSFER_SETTINGS     ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |         \
                                         (TRANSFER_SIZE_1_BYTE << TRANSFER_SETTINGS_SIZE_BITS) |         \
                                         (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                         (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |              \
                                         (TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_DEST_ADDR_BITS))

#define UART_W_TX_TRANSFER_SETTINGS     ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |               \
                                         (TRANSFER_SIZE_1_BYTE << TRANSFER_SETTINGS_SIZE_BITS) |               \
                                         (TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                         (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |                    \
                                         (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_DEST_ADDR_BITS))

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * uart_prv_ns_callback)(uart_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile uart_prv_ns_callback)(uart_callback_args_t * p_args);
#endif
#if BSP_MCU_GROUP_RA6W1
 #if (CFG_PMGR == 1)

/** UART sleep context required by PMGR */

typedef struct st_uart_w_pre_sleep_state
{
    uint32_t UART_IBRD_REG;
    uint32_t UART_FBRD_REG;
} uart_w_pre_sleep_state_t;

typedef struct st_r_uart_w_pmgr_context
{
    pmgr_instance_info_t     pmgr_info;
    pmgr_callback_args_t     clbk_args;
    uart_w_pre_sleep_state_t state;
    pmgr_w_notifier_extend_t pmgr_notifier_ext;
    uart_w_instance_ctrl_t * p_ctrl;
} r_uart_w_pmgr_context_t;
 #endif
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if (UART_W_CFG_PARAM_CHECKING_ENABLE)
static fsp_err_t r_uart_w_read_write_param_check(uart_w_instance_ctrl_t const * const p_ctrl,
                                                 uint8_t const * const                addr,
                                                 uint32_t const                       bytes);

#endif

#if UART_W_DMA_SUPPORT_ENABLE == 1
static fsp_err_t r_uart_w_dma_config(uart_w_instance_ctrl_t * p_ctrl);
static fsp_err_t r_uart_w_dma_rx_config(uart_w_instance_ctrl_t * p_ctrl);
static fsp_err_t r_uart_w_dma_tx_config(uart_w_instance_ctrl_t * p_ctrl);

/* ISR call when interrupt is generated */
void uart_w_dma_handler(dmac_callback_args_t * p_args);

#endif

static void     r_uart_w_config_set(uart_w_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg);
static void     r_uart_w_irq_cfg(uart_w_instance_ctrl_t * const p_ctrl, uint8_t const ipl, IRQn_Type const irq);
static void     r_uart_w_clear_tx_fifo_intr(uart_w_instance_ctrl_t * const p_ctrl);
static void     r_uart_w_baud_set(UART_Type * p_uart_reg, uart_w_baud_setting_t const * const p_baud_setting);
static void     r_uart_w_fill_tx_fifo(uart_w_instance_ctrl_t * const p_ctrl, uint32_t size);
static void     r_uart_w_call_callback(uart_w_instance_ctrl_t * p_ctrl, uint32_t data, uart_event_t event);
static uint32_t r_uart_w_get_fifo_trigger_len(uart_w_instance_ctrl_t * const p_ctrl, uint32_t fifo_trigger);

static void r_uart_w_handle_incoming_data(uart_w_instance_ctrl_t * const p_ctrl);
static void r_uart_w_handle_incoming_frame(uart_w_instance_ctrl_t * const p_ctrl);
static void r_uart_w_stop_rx(uart_w_instance_ctrl_t * const p_ctrl);

#if !BSP_MCU_GROUP_RA6W1
void                      hw_clk_enable_uart_w_clk(uint8_t channel);
void                      hw_clk_disable_uart_w_clk(uint8_t channel);
static uart_w_data_bits_t r_uart_w_get_data_bits(uart_cfg_t const * const p_cfg);
static uart_event_t       r_uart_w_get_line_error(uart_w_instance_ctrl_t * const p_ctrl);

#else
static uart_event_t r_uart_w_get_line_error(uint32_t uart_intr_flag);

 #if CFG_PMGR
static fsp_err_t     r_uart_w_enter_sleep(r_uart_w_pmgr_context_t * p_context);
static fsp_err_t     r_uart_w_wakeup(r_uart_w_pmgr_context_t * p_context);
static void          r_uart_w_pmgr_callback(pmgr_callback_args_t * args); \
    static fsp_err_t r_uart_w_subscribe_for_pmgr_notifications(uart_w_instance_ctrl_t * const p_ctrl);
static fsp_err_t     r_uart_w_unsubscribe_from_pmgr_notifications(uart_w_instance_ctrl_t * const p_ctrl); \
    static void      r_uart_w_tx_done_timer_cb(TimerHandle_t xTimer);
static uint32_t      r_uart_w_get_expected_tx_time_ms(uart_w_instance_ctrl_t * p_ctrl, uint32_t tx_bytes);

 #endif
#endif

/* ISR call when interrupt is generated */
void uart_w_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* UART_W HAL API mapping for UART interface */
const uart_api_t g_uart_on_uart_w =
{
    .open               = R_UART_W_Open,
    .close              = R_UART_W_Close,
    .write              = R_UART_W_Write,
    .read               = R_UART_W_Read,
    .infoGet            = R_UART_W_InfoGet,
    .baudSet            = R_UART_W_BaudSet,
    .communicationAbort = R_UART_W_Abort,
    .callbackSet        = R_UART_W_CallbackSet,
    .readStop           = R_UART_W_ReadStop,
#if BSP_MCU_GROUP_RA6W1
    .receiveSuspend = R_UART_W_ReceiveSuspend,
    .receiveResume  = R_UART_W_ReceiveResume,
#endif
};

#if BSP_MCU_GROUP_RA6W1
 #if (CFG_PMGR == 1)
  #define R_UART_W_MAX_CHANNELS                       __builtin_popcount(BSP_FEATURE_UART_W_VALID_CHANNEL_MASK)

// Min time possible is 1 rtos tic ~ 2ms
  #define R_UART_W_TX_TIME_MIN_MS                     2

/* Keep UART PMGR context here */
static r_uart_w_pmgr_context_t g_uart_pmgr_context[R_UART_W_MAX_CHANNELS];

  #define UART_TX_DONE_TIMER_NAME                     "UART_TX_DONE"
  #define UART_TX_DONE_TIMER_DEFAULT_TIMEOUT_TICKS    pdMS_TO_TICKS(50)
 #endif
#endif

/*******************************************************************************************************************//**
 * @addtogroup UART_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures the UART driver based on the input configurations.  If reception is enabled at compile time, reception is
 * enabled at the end of this function. Implements @ref uart_api_t::open
 *
 * @retval  FSP_SUCCESS                    Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION              Pointer to UART control block or configuration structure is NULL.
 * @retval  FSP_ERR_IP_CHANNEL_NOT_PRESENT The requested channel does not exist on this MCU.
 * @retval  FSP_ERR_INVALID_ARGUMENT       Data bits specified is not supported by the driver.
 * @retval  FSP_ERR_ALREADY_OPEN           Control block has already been opened or channel is being used by another
 *                                         instance. Call close() then open() to reconfigure.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                               * @ref transfer_api_t::open
 **********************************************************************************************************************/
fsp_err_t R_UART_W_Open (uart_ctrl_t * const p_api_ctrl, uart_cfg_t const * const p_cfg)
{
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;

#if (UART_W_CFG_PARAM_CHECKING_ENABLE)

    /* Check parameters. */
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_cfg);

    FSP_ASSERT(p_cfg->p_extend);
    FSP_ASSERT(((uart_w_extended_cfg_t *) p_cfg->p_extend)->p_baud_setting);
    FSP_ERROR_RETURN(UART_W_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
 #if !BSP_MCU_GROUP_RA6W1
    FSP_ERROR_RETURN(UART_W_DATA_BITS_9 < p_cfg->data_bits, FSP_ERR_INVALID_ARGUMENT);
 #endif

    /* Make sure this channel exists. */
    FSP_ERROR_RETURN(BSP_FEATURE_UART_W_VALID_CHANNEL_MASK & (1U << (p_cfg->channel + UART_W_CHANNEL_OFFSET)),
                     FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    FSP_ASSERT(p_cfg->rxi_irq >= 0);

 #if BSP_MCU_GROUP_RA6W3
    FSP_ASSERT(p_cfg->txi_irq >= 0);
    FSP_ASSERT(((uart_w_extended_cfg_t *) p_cfg->p_extend)->gen_irq >= 0);
 #endif

 #if UART_W_DMA_SUPPORT_ENABLE == 1
    if (p_cfg->p_transfer_tx)
    {
        const dmac_extended_cfg_t * p_extend_tx = p_cfg->p_transfer_tx->p_cfg->p_extend;

        /* UART TX should occupy odd DMA channels */
        FSP_ASSERT((uint32_t) p_extend_tx->channel & 1);
    }

    if (p_cfg->p_transfer_rx)
    {
        const dmac_extended_cfg_t * p_extend_rx = p_cfg->p_transfer_rx->p_cfg->p_extend;

        /* UART RX should occupy even DMA channels */
        FSP_ASSERT(!((uint32_t) p_extend_rx->channel & 1));
    }
 #endif
#endif

    /* Get the register address of the channel. */
    p_ctrl->p_reg = (UART_Type *) (UART_BASE + (UART_W_REG_SIZE * p_cfg->channel));

    /* Initialize uart_ctrl_t  */
    p_ctrl->fifo_depth        = BSP_FEATURE_UART_W_FIFO_DEPTH;
    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;
    p_ctrl->p_tx_src          = NULL;
    p_ctrl->tx_src_bytes      = 0U;
    p_ctrl->p_rx_dest         = NULL;
    p_ctrl->rx_dest_bytes     = 0;

    /* Configure the interrupts. */
    r_uart_w_irq_cfg(p_ctrl, p_cfg->rxi_ipl, p_cfg->rxi_irq);
#if !BSP_MCU_GROUP_RA6W1
    r_uart_w_irq_cfg(p_ctrl, p_cfg->txi_ipl, p_cfg->txi_irq);
#endif

#if BSP_MCU_GROUP_RA6W3
    r_uart_w_irq_cfg(p_ctrl, ((uart_w_extended_cfg_t *) p_cfg->p_extend)->gen_ipl,
                     ((uart_w_extended_cfg_t *) p_cfg->p_extend)->gen_irq);
#endif

    hw_clk_enable_uart_w_clk(p_cfg->channel);

    /* Set the UART configuration settings provided in ::uart_cfg_t and ::uart_w_extended_cfg_t. */
    r_uart_w_config_set(p_ctrl, p_cfg);

#if UART_W_DMA_SUPPORT_ENABLE == 1

    /* Config dma rx/tx */
    r_uart_w_dma_config(p_ctrl);
#endif

#if BSP_MCU_GROUP_RA6W1
 #if (CFG_PMGR == 1)
    p_ctrl->uart_tx_done_timer = xTimerCreate(UART_TX_DONE_TIMER_NAME,
                                              UART_TX_DONE_TIMER_DEFAULT_TIMEOUT_TICKS,
                                              pdFALSE,
                                              (void *) p_ctrl,
                                              r_uart_w_tx_done_timer_cb);
    FSP_ASSERT(p_ctrl->uart_tx_done_timer);
    r_uart_w_subscribe_for_pmgr_notifications((uart_w_instance_ctrl_t *) p_ctrl);
 #endif
#endif

    p_ctrl->open = UART_W_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Aborts any in progress transfers. Disables interrupts, receiver, and transmitter.  Closes lower level transfer
 * drivers if used. Reduces power consumption. Implements @ref uart_api_t::close
 *
 * @retval  FSP_SUCCESS              Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION        Pointer to UART control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_UART_W_Close (uart_ctrl_t * const p_api_ctrl)
{
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;

#if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(UART_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Mark the channel not open so other APIs cannot use it. */
    p_ctrl->open = 0U;

    p_ctrl->fifo_depth = 0;

#if BSP_MCU_GROUP_RA6W1
 #if (CFG_PMGR == 1)
    r_uart_w_unsubscribe_from_pmgr_notifications((uart_w_instance_ctrl_t *) p_ctrl);
    xTimerDelete(p_ctrl->uart_tx_done_timer, 0);
 #endif
#endif

    /* Disable  irq. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);

#if BSP_MCU_GROUP_RA6W3
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
    R_BSP_IrqDisable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
#endif

    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->UART_FR_REG_b.BUSY, 0);

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
    p_ctrl->p_reg->UART_CR_REG_b.UARTEN = 0;
    FSP_CRITICAL_SECTION_EXIT;

    hw_clk_disable_uart_w_clk(p_ctrl->p_cfg->channel);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Transmits user specified number of bytes from the source buffer pointer. Implements @ref uart_api_t::write
 *
 * @retval  FSP_SUCCESS                  Data transmission finished successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 *                                       Number of transfers outside the max or min boundary when transfer instance used
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_IN_USE               A UART transmission is in progress
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                               * @ref transfer_api_t::reconfigure
 **********************************************************************************************************************/
fsp_err_t R_UART_W_Write (uart_ctrl_t * const p_api_ctrl, uint8_t const * const p_src, uint32_t const bytes)
{
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;
#if UART_W_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = FSP_SUCCESS;
#endif
#if BSP_MCU_GROUP_RA6W1
 #if CFG_PMGR
    uint32_t expected_tx_time_ms;
 #endif
#endif

#if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    err = r_uart_w_read_write_param_check(p_ctrl, p_src, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN(0U == p_ctrl->tx_src_bytes, FSP_ERR_IN_USE);
#endif

    p_ctrl->tx_src_bytes = bytes;
    p_ctrl->p_tx_src     = p_src;

#if UART_W_DMA_SUPPORT_ENABLE == 1

    /* DMA mode,transfer tx should be set */
    if (p_ctrl->p_cfg->p_transfer_tx)
    {
        r_uart_w_dma_tx_config(p_ctrl);
    }
    else
#endif
    {
#if BSP_MCU_GROUP_RA6W3
        R_BSP_IrqDisable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
        p_ctrl->p_reg->UART_IMSC_REG_b.TXIM = 0;
        R_BSP_IrqEnable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
#else
        R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
        p_ctrl->p_reg->UART_IMSC_REG_b.TXIM = 0;
        R_BSP_IrqEnable(p_ctrl->p_cfg->rxi_irq);
#endif

        /* If the fifo is not used the first write will be done from this function. Subsequent writes will be done
         * from uart isr. */
        uint32_t cnt = 1;

        /* Is FIFO enabled for the channel */
        if (p_ctrl->p_reg->UART_LCR_H_REG_b.FEN)
        {
            cnt = p_ctrl->tx_src_bytes > p_ctrl->fifo_depth ? p_ctrl->fifo_depth : p_ctrl->tx_src_bytes;
        }

#if BSP_MCU_GROUP_RA6W1
 #if (CFG_PMGR == 1)
        if (p_ctrl->tx_onging_flag == false)
        {
            RM_PMGR_W_add_sleep_constraint(RM_PMGR_W_get_ctrl(), PMGR_CONSTRAINT_SLEEP_PROHIBITED);
        }
        p_ctrl->tx_onging_flag = true;
 #endif
#endif
        r_uart_w_fill_tx_fifo(p_ctrl, cnt);

        if (!p_ctrl->tx_src_bytes)
        {
#if BSP_MCU_GROUP_RA6W1
 #if (CFG_PMGR == 1)
            expected_tx_time_ms = r_uart_w_get_expected_tx_time_ms(p_ctrl, bytes);
            if (xTimerIsTimerActive(p_ctrl->uart_tx_done_timer) == pdFALSE)
            {
                xTimerChangePeriod(p_ctrl->uart_tx_done_timer, pdMS_TO_TICKS(expected_tx_time_ms), portMAX_DELAY);
                xTimerStart(p_ctrl->uart_tx_done_timer, portMAX_DELAY);
            }
 #endif
#endif
            if (p_ctrl->p_callback)
            {
                r_uart_w_call_callback(p_ctrl, 0U, UART_EVENT_TX_COMPLETE);
            }
        }
        else
        {
#if BSP_MCU_GROUP_RA6W3
            R_BSP_IrqDisable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
            p_ctrl->p_reg->UART_IMSC_REG_b.TXIM = 1;
            R_BSP_IrqEnableNoClear(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
#else
            R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
            p_ctrl->p_reg->UART_IMSC_REG_b.TXIM = 1;
            R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->rxi_irq);
#endif
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Receives user specified number of bytes into destination buffer pointer. Implements @ref uart_api_t::read
 *
 * @retval  FSP_SUCCESS                  Data reception successfully ends.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 *                                       Number of transfers outside the max or min boundary when transfer instance used
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_IN_USE               A previous read operation is still in progress.
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                               * @ref transfer_api_t::reconfigure
 **********************************************************************************************************************/
fsp_err_t R_UART_W_Read (uart_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t                err    = FSP_SUCCESS;

#if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    err = r_uart_w_read_write_param_check(p_ctrl, p_dest, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN(0U == p_ctrl->rx_dest_bytes, FSP_ERR_IN_USE);
#endif

    /* Save the destination address and size for use in rxi_isr. */
    p_ctrl->p_rx_dest     = p_dest;
    p_ctrl->rx_dest_bytes = bytes;

#if UART_W_DMA_SUPPORT_ENABLE == 1

    /* DMA mode,  transfer rx  set */
    if (p_ctrl->p_cfg->p_transfer_rx)
    {
        r_uart_w_dma_rx_config(p_ctrl);
 #if BSP_MCU_GROUP_RA6W3
        R_BSP_IrqDisable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
        p_ctrl->p_reg->UART_IMSC_REG_b.RTIM = 0;
        R_BSP_IrqEnable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
 #else
        R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
        p_ctrl->p_reg->UART_IMSC_REG_b.RTIM = 0;
        R_BSP_IrqEnable(p_ctrl->p_cfg->rxi_irq);
 #endif
    }
    else
#endif
    {
        uart_w_extended_cfg_t * p_extend = (uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

        /* Is FIFO enabled for the channel */
        if (p_ctrl->p_reg->UART_LCR_H_REG_b.FEN && (r_uart_w_get_fifo_trigger_len(p_ctrl, p_extend->rx_fifo_trigger) >
                                                    p_ctrl->rx_dest_bytes))
        {
#if BSP_MCU_GROUP_RA6W3
            R_BSP_IrqDisable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
            p_ctrl->p_reg->UART_IMSC_REG_b.RTIM = 1;
            R_BSP_IrqEnableNoClear(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
#else
            R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
            p_ctrl->p_reg->UART_IMSC_REG_b.RTIM = 1;
            R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->rxi_irq);
#endif
        }
    }

    return err;
}

/*******************************************************************************************************************/ /**
 * Updates the Uart configuration. p_baud_setting is a pointer to a uart_w_baud_setting_t structure.
 *
 * @warning This terminates any in-progress transmission.
 *
 * @retval  FSP_SUCCESS                  Uart been reconfiugred was successfully changed.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL or the UART is not configured to use the
 *                                       internal clock.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_UART_W_ConfSet (uart_ctrl_t * const p_api_ctrl, uart_cfg_t const * const p_cfg)
{
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;

#if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_cfg);
#endif
    p_ctrl->p_cfg = p_cfg;

    /* Apply new baud rate register settings. */
    r_uart_w_config_set(p_ctrl, p_cfg);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the driver information, including the maximum number of bytes that can be received or transmitted at a time.
 * Implements @ref uart_api_t::infoGet
 * @retval  FSP_SUCCESS                  Information stored in provided p_info.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_UART_W_InfoGet (uart_ctrl_t * const p_api_ctrl, uart_info_t * const p_info)
{
#if UART_W_CFG_PARAM_CHECKING_ENABLE
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

#if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_info);
    FSP_ERROR_RETURN(UART_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_info->read_bytes_max  = UART_W_MAX_READ_WRITE_NO_DMA;
    p_info->write_bytes_max = UART_W_MAX_READ_WRITE_NO_DMA;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the baud rate using the clock selected in Open. p_baud_setting is a pointer to a uart_w_baud_setting_t structure.
 * Implements @ref uart_api_t::baudSet
 *
 * @warning This terminates any in-progress transmission.
 *
 * @retval  FSP_SUCCESS                  Baud rate was successfully changed.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL or the UART is not configured to use the
 *                                       internal clock.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_UART_W_BaudSet (uart_ctrl_t * const p_api_ctrl, void const * const p_baud_setting)
{
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;
    uart_w_baud_setting_t  * p_baud = (uart_w_baud_setting_t *) p_baud_setting;
#if BSP_MCU_GROUP_RA6W1
    uint32_t lcr_h_reg_b_fen;
    uint32_t RS485EN_REG;
    uint32_t UART_IFLS_REG;
    uint32_t UART_LCR_H_REG;
    uint32_t UART_CR_REG;
#endif

#if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(UART_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(p_baud);
#endif

#if BSP_MCU_GROUP_RA6W1
    p_ctrl->p_reg->UART_CR_REG_b.UARTEN = 0;
    r_uart_w_clear_tx_fifo_intr(p_ctrl);
    RS485EN_REG = p_ctrl->p_reg->UART_RS485EN_REG;
    p_ctrl->p_reg->UART_RS485EN_REG = RS485EN_REG;
    UART_IFLS_REG                = p_ctrl->p_reg->UART_IFLS_REG;
    p_ctrl->p_reg->UART_IFLS_REG = UART_IFLS_REG;

    lcr_h_reg_b_fen = p_ctrl->p_reg->UART_LCR_H_REG_b.FEN;
    p_ctrl->p_reg->UART_LCR_H_REG_b.FEN = lcr_h_reg_b_fen &
                                          (UART_UART_LCR_H_REG_FEN_Msk >> UART_UART_LCR_H_REG_FEN_Pos);
#endif

    /* Apply new baud rate register settings. */
    r_uart_w_baud_set(p_ctrl->p_reg, p_baud);
#if BSP_MCU_GROUP_RA6W1
    p_ctrl->p_reg->UART_WA_REG_b.WAE = 0;
    UART_LCR_H_REG                = p_ctrl->p_reg->UART_LCR_H_REG;
    p_ctrl->p_reg->UART_LCR_H_REG = UART_LCR_H_REG;
    UART_CR_REG                = p_ctrl->p_reg->UART_CR_REG;
    p_ctrl->p_reg->UART_CR_REG = UART_CR_REG;

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
    p_ctrl->p_reg->UART_CR_REG_b.UARTEN = 1;
    FSP_CRITICAL_SECTION_EXIT;
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides API to abort ongoing transfer. Transmission is aborted after the current character is transmitted.
 * Reception is still enabled after abort(). Any characters received after abort() and before the transfer
 * is reset in the next call to read(), will arrive via the callback function with event UART_W_EVENT_RX_CHAR.
 * Implements @ref uart_api_t::communicationAbort
 *
 * @retval  FSP_SUCCESS                  UART transaction aborted successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_UNSUPPORTED          The requested Abort direction is unsupported.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls: @ref transfer_api_t::disable
 **********************************************************************************************************************/
fsp_err_t R_UART_W_Abort (uart_ctrl_t * const p_api_ctrl, uart_dir_t communication_to_abort)
{
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t                err    = FSP_ERR_UNSUPPORTED;

#if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(UART_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (UART_DIR_TX & communication_to_abort)
    {
        err = FSP_SUCCESS;
        p_ctrl->tx_src_bytes = 0U;
#if BSP_MCU_GROUP_RA6W3
        R_BSP_IrqDisable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
        p_ctrl->p_reg->UART_IMSC_REG_b.TXIM = 0;
        R_BSP_IrqEnable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
#else
        R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
        p_ctrl->p_reg->UART_IMSC_REG_b.TXIM = 0;
        R_BSP_IrqEnable(p_ctrl->p_cfg->rxi_irq);
#endif

#if UART_W_DMA_SUPPORT_ENABLE == 1
        if (NULL != p_ctrl->p_cfg->p_transfer_rx)
        {
            p_ctrl->p_reg->UART_DMACR_REG_b.TXDMAE = 0;

            err = p_ctrl->p_cfg->p_transfer_rx->p_api->disable(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
        }
#endif
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (UART_DIR_RX & communication_to_abort)
    {
        err = FSP_SUCCESS;
        p_ctrl->rx_dest_bytes = 0U;

#if UART_W_DMA_SUPPORT_ENABLE == 1
        if (NULL != p_ctrl->p_cfg->p_transfer_tx)
        {
            p_ctrl->p_reg->UART_DMACR_REG_b.RXDMAE = 0;
 #if BSP_MCU_GROUP_RA6W3
            R_BSP_IrqDisable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
            p_ctrl->p_reg->UART_IMSC_REG_b.RXIM = 1;
            R_BSP_IrqEnableNoClear(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
 #else
            R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
            p_ctrl->p_reg->UART_IMSC_REG_b.RXIM = 1;
            R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->rxi_irq);
 #endif

            err = p_ctrl->p_cfg->p_transfer_tx->p_api->disable(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
        }
#endif
    }

    return err;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements uart_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_UART_W_CallbackSet (uart_ctrl_t * const          p_api_ctrl,
                                void (                     * p_callback)(uart_callback_args_t *),
                                void * const                 p_context,
                                uart_callback_args_t * const p_callback_memory)
{
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;

#if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(UART_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if UART_W_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    uart_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                       CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback : (void (*)(uart_callback_args_t *))cmse_nsfptr_create(
        p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides API to abort ongoing read. Reception is still enabled after abort(). Any characters received after abort()
 * and before the transfer is reset in the next call to read(), will arrive via the callback function with event
 * UART_EVENT_RX_CHAR.
 * Implements @ref uart_api_t::readStop
 *
 * @retval  FSP_SUCCESS                  UART transaction aborted successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::disable
 **********************************************************************************************************************/
fsp_err_t R_UART_W_ReadStop (uart_ctrl_t * const p_api_ctrl, uint32_t * remaining_bytes)
{
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;

#if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(UART_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    *remaining_bytes      = p_ctrl->rx_dest_bytes;
    p_ctrl->rx_dest_bytes = 0U;
#if UART_W_DMA_SUPPORT_ENABLE == 1
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_ctrl->p_reg->UART_DMACR_REG_b.RXDMAE = 0;

        R_BSP_IrqDisable(irq);
        p_ctrl->p_reg->UART_IMSC_REG_b.RXIM = 1;
        R_BSP_IrqEnable(irq);

        fsp_err_t err = p_ctrl->p_cfg->p_transfer_rx->p_api->disable(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        transfer_properties_t transfer_info;
        err = p_ctrl->p_cfg->p_transfer_rx->p_api->infoGet(p_ctrl->p_cfg->p_transfer_rx->p_ctrl, &transfer_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        *remaining_bytes = transfer_info.transfer_length_remaining;
    }
#endif

    return FSP_SUCCESS;
}

#if BSP_MCU_GROUP_RA6W1

/*******************************************************************************************************************//**
 * Provides API to stop any RX activity. Reception isn't enabled after receiveSuspend(). No UART_EVENT_RX_CHAR event is
 * generated and character reception is suspended until next call receiveResume().
 * Implements @ref uart_api_t::receiveSuspend
 *
 * @retval  FSP_SUCCESS                  UART RX activity suspended successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 * @retval  FSP_ERR_INVALID_STATE        Hardware flow control isn't enabled for this channel.
 * @retval  FSP_ERR_UNSUPPORTED          Operation isn't supported for current configuration.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes.
 **********************************************************************************************************************/
fsp_err_t R_UART_W_ReceiveSuspend (uart_ctrl_t * const p_api_ctrl)
{
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;

 #if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(UART_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    uart_w_extended_cfg_t * p_extend = (uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    FSP_ERROR_RETURN(UART_W_AUTO_FLOW_CONTROL_ENABLED == p_extend->flow_control, FSP_ERR_INVALID_STATE);
 #endif

 #if !UART_W_DMA_SUPPORT_ENABLE

    /* Enable RX interrupts */

    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    p_ctrl->p_reg->UART_IMSC_REG_b.RXIM = 0;
    p_ctrl->p_reg->UART_IMSC_REG_b.RTIM = 0;
    R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->rxi_irq);

    return FSP_SUCCESS;
 #else

    return FSP_ERR_UNSUPPORTED;
 #endif
}

/*******************************************************************************************************************//**
 * Provides API to resume receiving of data over UART. Suspended read() operation is resumed. UART_EVENT_RX_CHAR event
 * is generated upon receiving character without prior read() operation.
 * Implements @ref uart_api_t::receiveResume
 *
 * @retval  FSP_SUCCESS                  UART RX activity resumed successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 * @retval  FSP_ERR_INVALID_STATE        Hardware flow control isn't enabled for this channel.
 * @retval  FSP_ERR_UNSUPPORTED          Operation isn't supported for current configuration.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes.
 **********************************************************************************************************************/
fsp_err_t R_UART_W_ReceiveResume (uart_ctrl_t * const p_api_ctrl)
{
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;

 #if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(UART_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    uart_w_extended_cfg_t * p_extend = (uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    FSP_ERROR_RETURN(UART_W_AUTO_FLOW_CONTROL_ENABLED == p_extend->flow_control, FSP_ERR_INVALID_STATE);
 #endif

 #if !UART_W_DMA_SUPPORT_ENABLE

    /* Enable RX interrupts */

    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    p_ctrl->p_reg->UART_IMSC_REG_b.RXIM = 1;
    p_ctrl->p_reg->UART_IMSC_REG_b.RTIM = !!p_ctrl->p_reg->UART_LCR_H_REG_b.FEN;
    R_BSP_IrqEnable(p_ctrl->p_cfg->rxi_irq);

    return FSP_SUCCESS;
 #else

    return FSP_ERR_UNSUPPORTED;
 #endif
}

#endif

/*******************************************************************************************************************//**
 * Calculates baud rate register settings. Evaluates and determines the best possible settings set to the baud rate
 * related registers.
 *
 * @param[in]  baudrate                  Baud rate [bps]. For example, 19200, 57600, 115200, etc.
 * @param[out] p_baud_setting            Baud setting information stored here if successful
 *
 * @retval     FSP_SUCCESS               Baud rate is set successfully
 * @retval     FSP_ERR_ASSERTION         Null pointer
 * @retval     FSP_ERR_INVALID_ARGUMENT  Invalid baudrate
 **********************************************************************************************************************/
fsp_err_t R_UART_W_BaudCalculate (uint32_t baudrate, uart_w_baud_setting_t * const p_baud_setting)
{
#if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_baud_setting);
    FSP_ERROR_RETURN((0U != baudrate), FSP_ERR_INVALID_ARGUMENT);
#endif

#if !BSP_MCU_GROUP_RA6W3
    uint64_t frac_coeff = COEFFICIENT_1000;
#endif
    uint64_t div_fraction_part;
    uint64_t freq_hz;
    uint64_t div_integer_part;
    uint64_t frac_hz;

    freq_hz          = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_UART);
    div_integer_part = freq_hz / (16 * baudrate);
    frac_hz          = freq_hz - div_integer_part * 16 * baudrate;
#if !BSP_MCU_GROUP_RA6W3
    div_fraction_part = (((frac_hz * frac_coeff) / (16 * baudrate)) * 64 + 5 * frac_coeff / 10) / frac_coeff;
#else
    div_fraction_part = (frac_hz * 64U + (16U * baudrate) / 2U) / (16U * baudrate);
    if (div_fraction_part >= 64U)
    {
        div_fraction_part = 0U;
        div_integer_part++;
    }
#endif

    p_baud_setting->fra_baud = div_fraction_part & UART_W_FRA_MASK;
    p_baud_setting->int_baud = div_integer_part & UART_W_INT_MASK;

    return FSP_SUCCESS;
}

#if BSP_MCU_GROUP_RA6W1
bool R_UART_W_IsWritting (uart_ctrl_t * const p_api_ctrl)
{
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;

    return p_ctrl->tx_src_bytes || !p_ctrl->p_reg->UART_FR_REG_b.TXFE || p_ctrl->p_reg->UART_FR_REG_b.BUSY;
}

bool R_UART_W_IsOpened (uart_ctrl_t * const p_api_ctrl)
{
    uart_w_instance_ctrl_t * p_ctrl = (uart_w_instance_ctrl_t *) p_api_ctrl;

    return p_ctrl->open == UART_W_OPEN;
}

#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup UART_W)
 **********************************************************************************************************************/
#if !BSP_MCU_GROUP_RA6W1

/**
 * \brief Enable clock for specific UART channel
 *
 * \param[in] channel UART channel to activate clock
 */
void hw_clk_enable_uart_w_clk (uint8_t channel)
{
    // CRG_TOP->CLK_AMBA_REG_b.PERI_CLK_ENABLE = 1;

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    switch (channel)
    {
        case 0:
        {
            CRG_COM->CLK_COM_REG_b.UART_ENABLE = 1;
            break;
        }

        case 1:
        {
            CRG_COM->CLK_COM_REG_b.UART2_ENABLE = 1;
            break;
        }

        case 2:
        {
            CRG_COM->CLK_COM_REG_b.UART3_ENABLE = 1;
            break;
        }

        case 3:
        {
            CRG_COM->CLK_COM_REG_b.UART4_ENABLE = 1;
            break;
        }
    }

    FSP_CRITICAL_SECTION_EXIT;
}

/**
 * \brief Disable clock for specific UART channel
 *
 * \param[in] channel UART channel to deactivate clock
 */
void hw_clk_disable_uart_w_clk (uint8_t channel)
{
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    switch (channel)
    {
        case 0:
        {
            CRG_COM->CLK_COM_REG_b.UART_ENABLE = 0;
            break;
        }

        case 1:
        {
            CRG_COM->CLK_COM_REG_b.UART2_ENABLE = 0;
            break;
        }

        case 2:
        {
            CRG_COM->CLK_COM_REG_b.UART3_ENABLE = 0;
            break;
        }

        case 3:
        {
            CRG_COM->CLK_COM_REG_b.UART4_ENABLE = 0;
            break;
        }
    }

    FSP_CRITICAL_SECTION_EXIT;
}

#endif

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
#if (UART_W_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * Parameter error check function for read/write.
 *
 * @param[in] p_ctrl Pointer to the control block for the channel
 * @param[in] addr   Pointer to the buffer
 * @param[in] bytes  Number of bytes to read or write
 *
 * @retval  FSP_SUCCESS              No parameter error found
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened
 * @retval  FSP_ERR_ASSERTION        Pointer to UART control block or configuration structure is NULL
 **********************************************************************************************************************/
static fsp_err_t r_uart_w_read_write_param_check (uart_w_instance_ctrl_t const * const p_ctrl,
                                                  uint8_t const * const                addr,
                                                  uint32_t const                       bytes)
{
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(addr);
    FSP_ASSERT(0U != bytes);
    FSP_ERROR_RETURN(UART_W_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    return FSP_SUCCESS;
}

#endif

#if UART_W_DMA_SUPPORT_ENABLE == 1
static fsp_err_t r_uart_w_dma_config (uart_w_instance_ctrl_t * p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    const transfer_instance_t * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;
    if (p_transfer_tx)
    {
        p_transfer_tx->p_cfg->p_info->transfer_settings_word = UART_W_TX_TRANSFER_SETTINGS;
        p_transfer_tx->p_cfg->p_info->p_dest                 = (void *) &(p_ctrl->p_reg->UART_DR_REG);

        err = p_transfer_tx->p_api->open(p_transfer_tx->p_ctrl, p_transfer_tx->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    const transfer_instance_t * p_transfer_rx = p_ctrl->p_cfg->p_transfer_rx;
    if (p_transfer_rx)
    {
        p_transfer_rx->p_cfg->p_info->transfer_settings_word = UART_W_RX_TRANSFER_SETTINGS;
        p_transfer_rx->p_cfg->p_info->p_src = (void *) &(p_ctrl->p_reg->UART_DR_REG);

        err = p_transfer_rx->p_api->open(p_transfer_rx->p_ctrl, p_transfer_rx->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    return err;
}

static fsp_err_t r_uart_w_dma_rx_config (uart_w_instance_ctrl_t * p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    if (p_ctrl->p_cfg->p_transfer_rx)
    {
        /* Configure the receive DMA instance. */
        p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->length = (uint16_t) p_ctrl->rx_dest_bytes;
        p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->p_dest = (void *) p_ctrl->p_rx_dest;
        if (NULL == p_ctrl->p_rx_dest)
        {
            static uint32_t dummy_rx = 0;
            p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->transfer_settings_word_b.dest_addr_mode =
                TRANSFER_ADDR_MODE_FIXED;
            p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->p_dest = &dummy_rx;
        }

        err = p_ctrl->p_cfg->p_transfer_rx->p_api->reconfigure(p_ctrl->p_cfg->p_transfer_rx->p_ctrl,
                                                               p_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        p_ctrl->p_reg->UART_DMACR_REG_b.RXDMAE = 1;
    }

    return err;
}

static fsp_err_t r_uart_w_dma_tx_config (uart_w_instance_ctrl_t * p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    if (p_ctrl->p_cfg->p_transfer_tx)
    {
        /* Configure the transmit DMA instance. */
        p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->length = (uint16_t) p_ctrl->tx_src_bytes;
        p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_src  = p_ctrl->p_tx_src;

        if (NULL == p_ctrl->p_tx_src)
        {
            static uint32_t dummy_tx = 0;
            p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->transfer_settings_word_b.src_addr_mode =
                TRANSFER_ADDR_MODE_FIXED;
            p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_src = &dummy_tx;
        }

        err = p_ctrl->p_cfg->p_transfer_tx->p_api->reconfigure(p_ctrl->p_cfg->p_transfer_tx->p_ctrl,
                                                               p_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        p_ctrl->p_reg->UART_DMACR_REG_b.TXDMAE = 1;
    }

    return err;
}

#endif

/*******************************************************************************************************************//**
 * Sets interrupt priority and initializes vector info.
 *
 * @param[in]  p_ctrl                    Pointer to UART channel control block
 * @param[in]  ipl                       Interrupt priority level
 * @param[in]  irq                       IRQ number for this interrupt
 **********************************************************************************************************************/
static void r_uart_w_irq_cfg (uart_w_instance_ctrl_t * const p_ctrl, uint8_t const ipl, IRQn_Type const irq)
{
    /* Disable interrupts, set priority, and store control block in the vector information so it can be accessed
     * from the callback. */
    R_BSP_IrqDisable(irq);
    R_BSP_IrqCfgEnable(irq, ipl, p_ctrl);
}

static void r_uart_w_baud_set (UART_Type * p_uart_reg, uart_w_baud_setting_t const * const p_baud_setting)
{
    uint32_t uart_enabled = p_uart_reg->UART_CR_REG_b.UARTEN;

    /* Disable UART channel before changing the baud rate */
    p_uart_reg->UART_CR_REG_b.UARTEN = 0;

    p_uart_reg->UART_IBRD_REG_b.BAUD_DIVINT  = (p_baud_setting->int_baud & UART_W_INT_MASK);
    p_uart_reg->UART_FBRD_REG_b.BAUD_DIVFRAC = (p_baud_setting->fra_baud & UART_W_FRA_MASK);

    /* Clear interrupts before re-enabling the channel */
    p_uart_reg->UART_ICR_REG = UART_W_INTR_CLEAR_MASK;

    p_uart_reg->UART_CR_REG_b.UARTEN = uart_enabled & UART_UART_CR_REG_UARTEN_Msk;
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to UART channel control block
 * @param[in]     data       See uart_callback_args_t in r_uart_api.h
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_uart_w_call_callback (uart_w_instance_ctrl_t * p_ctrl, uint32_t data, uart_event_t event)
{
    uart_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    uart_callback_args_t * p_args = p_ctrl->p_callback_memory;

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
    p_args->data      = data;
    p_args->event     = event;
    p_args->p_context = p_ctrl->p_context;

#if BSP_TZ_SECURE_BUILD

    /* The p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        uart_prv_ns_callback p_callback = (uart_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args);
#endif

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * ISR called when interrupt is generated.
 **********************************************************************************************************************/
#if UART_W_DMA_SUPPORT_ENABLE == 1
void uart_w_dma_handler (dmac_callback_args_t * p_args)
{
    uart_w_instance_ctrl_t    * p_ctrl        = (uart_w_instance_ctrl_t *) p_args->p_context;
    const transfer_instance_t * p_transfer_rx = p_ctrl->p_cfg->p_transfer_rx;
    const transfer_instance_t * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;

    if (p_transfer_rx != NULL)
    {
        const dmac_extended_cfg_t * p_extend_rx = p_transfer_rx->p_cfg->p_extend;
        if ((p_args->event == DMAC_B_EVENT_TRANSFER_COMPLETE) && (p_args->channel == p_extend_rx->channel))
        {
            p_transfer_rx->p_api->disable(p_transfer_rx->p_ctrl);
            p_ctrl->rx_dest_bytes = 0;

            /* TODO Partial read */
            if (NULL != p_ctrl->p_callback)
            {
                r_uart_w_call_callback(p_ctrl, 0U, UART_EVENT_RX_COMPLETE);
            }

            p_ctrl->p_reg->UART_DMACR_REG_b.RXDMAE = 0;
 #if BSP_MCU_GROUP_RA6W3
            R_BSP_IrqDisable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
            p_ctrl->p_reg->UART_IMSC_REG_b.RXIM = 1;
            R_BSP_IrqEnableNoClear(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
 #else
            R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
            p_ctrl->p_reg->UART_IMSC_REG_b.RXIM = 1;
            R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->rxi_irq);
 #endif
        }
    }

    if (p_transfer_tx != NULL)
    {
        const dmac_extended_cfg_t * p_extend_tx = p_transfer_tx->p_cfg->p_extend;
        if ((p_args->event == DMAC_B_EVENT_TRANSFER_COMPLETE) && (p_args->channel == p_extend_tx->channel))
        {
            p_transfer_tx->p_api->disable(p_transfer_tx->p_ctrl);
            p_ctrl->tx_src_bytes = 0;
            if (NULL != p_ctrl->p_callback)
            {
                r_uart_w_call_callback(p_ctrl, 0U, UART_EVENT_TX_COMPLETE);
            }

            p_ctrl->p_reg->UART_DMACR_REG_b.TXDMAE = 0;
        }
    }
}

#endif

/*******************************************************************************************************************//**
 * ISR called when interrupt is generated.
 **********************************************************************************************************************/
void uart_w_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    uart_w_instance_ctrl_t * p_ctrl         = (uart_w_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    volatile uint32_t        uart_intr_flag = (p_ctrl->p_reg->UART_MIS_REG & UART_W_INTR_MASK);
    UART_Type              * p_uart_reg     = p_ctrl->p_reg;

#if BSP_MCU_GROUP_RA6W1
 #if CFG_PMGR
    uart_w_extended_cfg_t * p_extend = (uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    uint32_t                expected_tx_time_ms;
    BaseType_t              xHigherPriorityTaskWoken = pdFALSE;
 #endif
#endif
#if BSP_MCU_GROUP_RA6W3
    volatile uint32_t * ielsrn_reg = ICU_IELSRn_REG(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);

    /* Clear pending IRQ to make sure it doesn't fire again after exiting. */
    R_BSP_IrqStatusClear(irq);
#endif

    while (UART_W_INTR_ID_NO_PEND != uart_intr_flag)
    {
        if ((UART_W_INTR_ID_RDI | UART_W_INTR_ID_TIMEOUT) & uart_intr_flag)
        {
            r_uart_w_handle_incoming_data(p_ctrl);

            p_uart_reg->UART_ICR_REG = (UART_UART_ICR_REG_RXIC_Msk | UART_UART_ICR_REG_RTIC_Msk);
#if BSP_MCU_GROUP_RA6W3
            switch (p_ctrl->p_cfg->channel)
            {
                case UART1_CHANNEL_NUM:
                {
                    FSP_REG_VAR_FIELD_SET(ICU, ICU_IELSR0_REG, ICU_IELS, *ielsrn_reg, ICU_EVENT_UARTWB1_IRQ);
                    break;
                }

                case UART2_CHANNEL_NUM:
                {
                    FSP_REG_VAR_FIELD_SET(ICU, ICU_IELSR0_REG, ICU_IELS, *ielsrn_reg, ICU_EVENT_UARTWB2_IRQ);
                    break;
                }

                case UART3_CHANNEL_NUM:
                {
                    FSP_REG_VAR_FIELD_SET(ICU, ICU_IELSR0_REG, ICU_IELS, *ielsrn_reg, ICU_EVENT_UARTWB3_IRQ);
                    break;
                }

                case UART4_CHANNEL_NUM:
                {
                    FSP_REG_VAR_FIELD_SET(ICU, ICU_IELSR0_REG, ICU_IELS, *ielsrn_reg, ICU_EVENT_UARTWB4_IRQ);
                    break;
                }
            }
#endif
        }
        else if (UART_W_INTR_ID_TI & uart_intr_flag)
        {
            uint32_t cnt = 1;          /* The data sent should be at least 1 */

            p_uart_reg->UART_ICR_REG_b.TXIC = 1;

            /* Is FIFO enabled for the channel */
            if (p_uart_reg->UART_LCR_H_REG_b.FEN)
            {
                cnt = p_ctrl->tx_src_bytes > p_ctrl->fifo_depth / 2 ? p_ctrl->fifo_depth / 2 : p_ctrl->tx_src_bytes;
            }

            r_uart_w_fill_tx_fifo(p_ctrl, cnt);

            if (!p_ctrl->tx_src_bytes)
            {
                p_uart_reg->UART_IMSC_REG_b.TXIM = 0;
#if BSP_MCU_GROUP_RA6W1
 #if CFG_PMGR
                expected_tx_time_ms =
                    r_uart_w_get_expected_tx_time_ms(p_ctrl,
                                                     r_uart_w_get_fifo_trigger_len(p_ctrl, p_extend->rx_fifo_trigger));
                if (xTimerIsTimerActive(p_ctrl->uart_tx_done_timer) == pdFALSE)
                {
                    xTimerChangePeriodFromISR(p_ctrl->uart_tx_done_timer,
                                              pdMS_TO_TICKS(expected_tx_time_ms),
                                              &xHigherPriorityTaskWoken);
                    xTimerStartFromISR(p_ctrl->uart_tx_done_timer, &xHigherPriorityTaskWoken);
                }
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
 #endif
#endif
                if (NULL != p_ctrl->p_callback)
                {
                    r_uart_w_call_callback(p_ctrl, 0U, UART_EVENT_TX_COMPLETE);
                }
            }
        }
        else if (UART_W_INTR_ID_RLSI & uart_intr_flag)
        {
            /* Return Line status. */
#if BSP_MCU_GROUP_RA6W1
            uart_event_t error_code = r_uart_w_get_line_error(uart_intr_flag);
#else
            uart_event_t error_code = r_uart_w_get_line_error(p_ctrl);
#endif
            if (NULL != p_ctrl->p_callback)
            {
                r_uart_w_call_callback(p_ctrl, 0U, error_code);
            }

#if BSP_MCU_GROUP_RA6W1

            /* Need to pop corrupted byte from the top of the FIFO */
            if (uart_intr_flag & (UART_UART_MIS_REG_FEMIS_Msk | \
                                  UART_UART_MIS_REG_PEMIS_Msk | \
                                  UART_UART_MIS_REG_BEMIS_Msk))
            {
                (void) (*(volatile uint8_t *) &p_ctrl->p_reg->UART_DR_REG);

                /* Clear irq status register condition. */
                p_uart_reg->UART_RSR_REG = 0;
            }

#else

            /* Clear irq status register condition. */
            p_uart_reg->UART_RSR_REG = 0;
#endif
            p_uart_reg->UART_ICR_REG = (UART_UART_ICR_REG_FEIC_Msk | UART_UART_ICR_REG_PEIC_Msk | \
                                        UART_UART_ICR_REG_BEIC_Msk | UART_UART_ICR_REG_OEIC_Msk);
        }
        else if (UART_W_INTR_MDM_STATUS & uart_intr_flag)
        {
            p_uart_reg->UART_ICR_REG = (UART_UART_ICR_REG_RIMIC_Msk | UART_UART_ICR_REG_CTSMIC_Msk | \
                                        UART_UART_ICR_REG_DCDMIC_Msk | UART_UART_ICR_REG_DSRMIC_Msk);
        }
        else
        {
            /* Clear unidentified interrupts */
            p_uart_reg->UART_ICR_REG = UART_W_INTR_CLEAR_MASK;
        }

        uart_intr_flag = (p_ctrl->p_reg->UART_MIS_REG & UART_W_INTR_MASK);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * Clear pending TX FIFO interrupt.
 *
 * @param[in]     p_ctrl  Pointer to UART channel control block
 **********************************************************************************************************************/
static void r_uart_w_clear_tx_fifo_intr (uart_w_instance_ctrl_t * const p_ctrl)
{
    (void) p_ctrl->p_reg->UART_FR_REG_b.TXFE;
}

/*******************************************************************************************************************//**
 * Configures UART related registers based on user configurations.
 *
 * @param[in]     p_ctrl  Pointer to UART channel control block
 * @param[in]     p_cfg   Pointer to UART specific configuration structure
 **********************************************************************************************************************/
static void r_uart_w_config_set (uart_w_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg)
{
    uart_w_extended_cfg_t * p_extend = (uart_w_extended_cfg_t *) p_cfg->p_extend;
#if BSP_MCU_GROUP_RA6W1
    uint32_t data_bits = (uint32_t) p_cfg->data_bits;
#else
    uint32_t data_bits = (uint32_t) r_uart_w_get_data_bits(p_cfg);
#endif

    p_ctrl->p_reg->UART_CR_REG_b.UARTEN = 0;

    r_uart_w_clear_tx_fifo_intr(p_ctrl);

    /* Enable RS485 */
    p_ctrl->p_reg->UART_RS485EN_REG = ((p_ctrl->p_reg->UART_RS485EN_REG & ~UART_UART_RS485EN_REG_RS485E_Msk) |
                                       (uint32_t) p_extend->rs485_enable << UART_UART_RS485EN_REG_RS485E_Pos);

    if (!(p_ctrl->p_cfg->p_transfer_rx || p_ctrl->p_cfg->p_transfer_tx || p_extend->fifo_enable ||
          p_extend->flow_control))
    {
        p_ctrl->p_reg->UART_LCR_H_REG_b.FEN = 0;
        p_ctrl->p_reg->UART_IFLS_REG       &= ~(UART_UART_IFLS_REG_RXIFLSEL_Msk | UART_UART_IFLS_REG_TXIFLSEL_Msk);
    }
    else
    {
        p_ctrl->p_reg->UART_LCR_H_REG_b.FEN = 1;
        p_ctrl->p_reg->UART_IFLS_REG        = ((p_ctrl->p_reg->UART_IFLS_REG &
                                                ~(UART_UART_IFLS_REG_RXIFLSEL_Msk | UART_UART_IFLS_REG_TXIFLSEL_Msk)) |
                                               ((uint32_t) p_extend->rx_fifo_trigger <<
                                         UART_UART_IFLS_REG_RXIFLSEL_Pos) |
                                               ((uint32_t) p_extend->tx_fifo_trigger <<
                                         UART_UART_IFLS_REG_TXIFLSEL_Pos));
    }

    /* Set the baud rate. */
    r_uart_w_baud_set(p_ctrl->p_reg, p_extend->p_baud_setting);

    p_ctrl->p_reg->UART_CR_REG = ((p_ctrl->p_reg->UART_LCR_H_REG & ~UART_UART_CR_REG_LBE_Msk) |
                                  ((uint32_t) p_extend->loop_back_enable << UART_UART_CR_REG_LBE_Pos) |
                                  UART_UART_CR_REG_RXE_Msk | UART_UART_CR_REG_TXE_Msk);
    p_ctrl->p_reg->UART_WA_REG_b.WAE = 0;

    if (UART_PARITY_OFF != p_cfg->parity)
    {
        if (UART_PARITY_ODD == p_cfg->parity)
        {
            p_ctrl->p_reg->UART_LCR_H_REG = ((p_ctrl->p_reg->UART_LCR_H_REG & ~UART_UART_LCR_H_REG_EPS_Msk) |
                                             UART_UART_LCR_H_REG_PEN_Msk);
        }
        else
        {
            p_ctrl->p_reg->UART_LCR_H_REG |= UART_UART_LCR_H_REG_EPS_Msk | UART_UART_LCR_H_REG_PEN_Msk;
        }
    }
    else
    {
        p_ctrl->p_reg->UART_LCR_H_REG &= ~(UART_UART_LCR_H_REG_PEN_Msk | UART_UART_LCR_H_REG_EPS_Msk);
    }

    p_ctrl->p_reg->UART_LCR_H_REG = ((p_ctrl->p_reg->UART_LCR_H_REG &
                                      ~(UART_UART_LCR_H_REG_WLEN_Msk | UART_UART_LCR_H_REG_STP2_Msk)) |
                                     ((uint32_t) p_cfg->stop_bits << UART_UART_LCR_H_REG_STP2_Pos) |
                                     (data_bits << UART_UART_LCR_H_REG_WLEN_Pos));
    p_ctrl->p_reg->UART_CR_REG = ((p_ctrl->p_reg->UART_CR_REG &
                                   ~(UART_UART_CR_REG_RTSEn_Msk | UART_UART_CR_REG_CTSEn_Msk)) |
                                  ((uint32_t) p_extend->flow_control << UART_UART_CR_REG_RTSEn_Pos) |
                                  ((uint32_t) p_extend->flow_control << UART_UART_CR_REG_CTSEn_Pos));

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
    p_ctrl->p_reg->UART_CR_REG_b.UARTEN = 1;
    FSP_CRITICAL_SECTION_EXIT;

#if !UART_W_DMA_SUPPORT_ENABLE
 #if BSP_MCU_GROUP_RA6W3

    /* Enable RX and line status interrupts */
    R_BSP_IrqDisable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
    p_ctrl->p_reg->UART_IMSC_REG |= (UART_UART_IMSC_REG_FEIM_Msk | UART_UART_IMSC_REG_PEIM_Msk | \
                                     UART_UART_IMSC_REG_BEIM_Msk | UART_UART_IMSC_REG_OEIM_Msk | \
                                     UART_UART_IMSC_REG_RXIM_Msk);
    p_ctrl->p_reg->UART_IMSC_REG_b.RTIM = !!p_ctrl->p_reg->UART_LCR_H_REG_b.FEN;
    R_BSP_IrqEnable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
 #else
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    p_ctrl->p_reg->UART_IMSC_REG |= (UART_UART_IMSC_REG_FEIM_Msk | UART_UART_IMSC_REG_PEIM_Msk | \
                                     UART_UART_IMSC_REG_BEIM_Msk | UART_UART_IMSC_REG_OEIM_Msk | \
                                     UART_UART_IMSC_REG_RXIM_Msk);
    p_ctrl->p_reg->UART_IMSC_REG_b.RTIM = !!p_ctrl->p_reg->UART_LCR_H_REG_b.FEN;
    R_BSP_IrqEnable(p_ctrl->p_cfg->rxi_irq);
 #endif
#endif
}

#if !BSP_MCU_GROUP_RA6W1

/*******************************************************************************************************************//**
 * Return UART data bits configuration.
 *
 * @param[in] p_cfg   Pointer to UART specific configuration structure
 *
 * @retval            UART data bits configuration.
 **********************************************************************************************************************/
static uart_w_data_bits_t r_uart_w_get_data_bits (uart_cfg_t const * const p_cfg)
{
    uart_w_extended_cfg_t * p_extend = (uart_w_extended_cfg_t *) p_cfg->p_extend;

    if (p_extend->extended_data_bits_enable)
    {
        return p_extend->data_bits;
    }

    if (UART_DATA_BITS_7 == p_cfg->data_bits)
    {
        return UART_W_DATA_BITS_7;
    }

    return UART_W_DATA_BITS_8;
}

#endif

/*******************************************************************************************************************//**
 * Fill number of bytes from the source buffer pointer.
 *
 * @param[in]     p_ctrl  Pointer to UART channel control block
 * @param[in]     size    number of bytes
 **********************************************************************************************************************/
static void r_uart_w_fill_tx_fifo (uart_w_instance_ctrl_t * const p_ctrl, uint32_t size)
{
    for ( ; size; size--)
    {
        if (p_ctrl->p_reg->UART_FR_REG_b.TXFF)
        {

            /* FIFO buffer is full, wait for next interrupt to retry */
            return;
        }

        (*(volatile uint8_t *) &p_ctrl->p_reg->UART_DR_REG) = *p_ctrl->p_tx_src;

        p_ctrl->tx_src_bytes--;
        p_ctrl->p_tx_src++;
    }
}

/*******************************************************************************************************************//**
 * Return the number of bytes required to trigger FIFO event.
 *
 * @param[in] p_ctrl         Pointer to the control block for the channel
 * @param[in] fifo_trigger   Trigger level for FIFO operations
 *
 * @retval                   The number of bytes corresponding to specified FIFO trigger level.
 **********************************************************************************************************************/
static uint32_t r_uart_w_get_fifo_trigger_len (uart_w_instance_ctrl_t * const p_ctrl, uint32_t fifo_trigger)
{
    switch (fifo_trigger)
    {
        case UART_W_RX_FIFO_TRIGGER_EIGHTH:
        {
            return p_ctrl->fifo_depth / 8U;
        }

        case UART_W_RX_FIFO_TRIGGER_QUARTER:
        {
            return p_ctrl->fifo_depth / 4U;
        }

        case UART_W_RX_FIFO_TRIGGER_HALF:
        {
            return p_ctrl->fifo_depth / 2U;
        }

        case UART_W_RX_FIFO_TRIGGER_THREE_QUARTERS:
        {
            return p_ctrl->fifo_depth * 3U / 4U;
        }

        case UART_W_RX_FIFO_TRIGGER_SEVEN_EIGHTHS:
        {
            return p_ctrl->fifo_depth * 7U / 8U;
        }

        default:
        {
            return 1;
        }
    }
}

#if BSP_MCU_GROUP_RA6W1

/*******************************************************************************************************************/ /**
 * Return UART line status event error code.
 *
 * @retval                   UART line status event error code.
 **********************************************************************************************************************/
static uart_event_t r_uart_w_get_line_error (uint32_t uart_intr_flag)
{
    uart_event_t error_code = UART_W_EVENT_NO_EVENT;

    if (UART_UART_MIS_REG_FEMIS_Msk & uart_intr_flag)
    {
        error_code |= UART_EVENT_ERR_FRAMING;
    }

    if (UART_UART_MIS_REG_PEMIS_Msk & uart_intr_flag)
    {
        error_code |= UART_EVENT_ERR_PARITY;
    }

    if (UART_UART_MIS_REG_BEMIS_Msk & uart_intr_flag)
    {
        error_code |= UART_EVENT_BREAK_DETECT;
    }

    if (UART_UART_MIS_REG_OEMIS_Msk & uart_intr_flag)
    {
        error_code |= UART_EVENT_ERR_OVERFLOW;
    }

    return error_code;
}

#else

/*******************************************************************************************************************//**
 * Return UART line status event error code.
 *
 * @param[in] p_ctrl         Pointer to UART channel control block
 *
 * @retval                   UART line status event error code.
 **********************************************************************************************************************/
static uart_event_t r_uart_w_get_line_error (uart_w_instance_ctrl_t * const p_ctrl)
{
    uint32_t     rsr        = p_ctrl->p_reg->UART_RSR_REG;
    uart_event_t error_code = UART_W_EVENT_NO_EVENT;

    if (UART_UART_RSR_REG_RSR_FE_Msk & rsr)
    {
        error_code |= UART_EVENT_ERR_FRAMING;
    }

    if (UART_UART_RSR_REG_RSR_PE_Msk & rsr)
    {
        error_code |= UART_EVENT_ERR_PARITY;
    }

    if (UART_UART_RSR_REG_RSR_BE_Msk & rsr)
    {
        error_code |= UART_EVENT_BREAK_DETECT;
    }

    if (UART_UART_RSR_REG_RSR_OE_Msk & rsr)
    {
        error_code |= UART_EVENT_ERR_OVERFLOW;
    }

    return error_code;
}

#endif

/*******************************************************************************************************************//**
 * Handle incoming UART data.
 *
 * @param[in] p_ctrl         Pointer to UART channel control block
 **********************************************************************************************************************/
static void r_uart_w_handle_incoming_data (uart_w_instance_ctrl_t * const p_ctrl)
{
    uart_w_extended_cfg_t * p_extend = (uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Is FIFO enabled for the channel */
    if (p_ctrl->p_reg->UART_LCR_H_REG_b.FEN)
    {
        uint32_t byte;
        uint32_t cnt = r_uart_w_get_fifo_trigger_len(p_ctrl, p_extend->rx_fifo_trigger);

        for (byte = 0; byte < cnt; byte++)
        {
            if (p_ctrl->p_reg->UART_FR_REG_b.RXFE)
            {
                /* No frames left to process */
                break;
            }

            r_uart_w_handle_incoming_frame(p_ctrl);
        }
    }
    else
    {
        if (!p_ctrl->p_reg->UART_FR_REG_b.RXFE)
        {
            /* We have pending frame */
            r_uart_w_handle_incoming_frame(p_ctrl);
        }
    }

    if (p_ctrl->p_reg->UART_LCR_H_REG_b.FEN && p_ctrl->rx_dest_bytes)
    {
        if (r_uart_w_get_fifo_trigger_len(p_ctrl, p_extend->rx_fifo_trigger) > p_ctrl->rx_dest_bytes)
        {
#if BSP_MCU_GROUP_RA6W3
            R_BSP_IrqDisable(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
            p_ctrl->p_reg->UART_IMSC_REG_b.RTIM = 1;
            R_BSP_IrqEnableNoClear(((uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->gen_irq);
#else
            R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
            p_ctrl->p_reg->UART_IMSC_REG_b.RTIM = 1;
            R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->rxi_irq);
#endif
        }
    }
}

/*******************************************************************************************************************//**
 * Handle incoming UART frame.
 *
 * @param[in] p_ctrl         Pointer to UART channel control block
 **********************************************************************************************************************/
static void r_uart_w_handle_incoming_frame (uart_w_instance_ctrl_t * const p_ctrl)
{
    uint8_t data = (*(volatile uint8_t *) &p_ctrl->p_reg->UART_DR_REG);

    /* No pending RX flow. Calling user callback with  UART_EVENT_RX_CHAR code */
    if (0 == p_ctrl->rx_dest_bytes)
    {
        if (NULL != p_ctrl->p_callback)
        {
            r_uart_w_call_callback(p_ctrl, data, UART_EVENT_RX_CHAR);
        }
    }
    else
    {
        *p_ctrl->p_rx_dest = data;

        p_ctrl->p_rx_dest++;
        p_ctrl->rx_dest_bytes--;

        if (0 == p_ctrl->rx_dest_bytes)
        {
            r_uart_w_stop_rx(p_ctrl);
        }
    }
}

/*******************************************************************************************************************//**
 * Finish current UART RX flow.
 *
 * @param[in] p_ctrl         Pointer to UART channel control block
 **********************************************************************************************************************/
static void r_uart_w_stop_rx (uart_w_instance_ctrl_t * const p_ctrl)
{
    /* Trying to pull all the data remaining */
    while (p_ctrl->rx_dest_bytes)
    {
        if (p_ctrl->p_reg->UART_FR_REG_b.RXFE)
        {
            /* No frames left to process */
            break;
        }

        /* We have pending frame */
        r_uart_w_handle_incoming_frame(p_ctrl);
    }

    p_ctrl->rx_dest_bytes = 0;

    if (NULL != p_ctrl->p_callback)
    {
        r_uart_w_call_callback(p_ctrl, 0U, UART_EVENT_RX_COMPLETE);
    }
}

#if BSP_MCU_GROUP_RA6W1
 #if CFG_PMGR == 1

/*******************************************************************************************************************/ /**
 * Prepare UART for sleep mode 4/5
 *
 * @param[in] p_context Pointer to PMGR interface of UART instance
 **********************************************************************************************************************/
static fsp_err_t r_uart_w_enter_sleep (r_uart_w_pmgr_context_t * p_context)
{
    fsp_err_t err = FSP_SUCCESS;
  #if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_context);
  #endif

    uart_w_instance_ctrl_t * p_ctrl = p_context->p_ctrl;
    FSP_ERROR_RETURN(p_ctrl->open == UART_W_OPEN, FSP_ERR_INVALID_MODE);

    /* Store the baud rate and CR after reset */
    p_context->state.UART_IBRD_REG = p_ctrl->p_reg->UART_IBRD_REG;
    p_context->state.UART_FBRD_REG = p_ctrl->p_reg->UART_FBRD_REG;

    p_ctrl->p_reg->UART_CR_REG_b.UARTEN = 0;

    p_ctrl->open = UART_W_SLEEP;

    return err;
}

/*******************************************************************************************************************/ /**
 * Restore UART from wakeup
 *
 * @param[in] p_context Pointer to PMGR interface of UART instance
 **********************************************************************************************************************/
static fsp_err_t r_uart_w_wakeup (r_uart_w_pmgr_context_t * p_context)
{
    fsp_err_t err = FSP_SUCCESS;
  #if (UART_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_context);
  #endif
    uart_w_instance_ctrl_t * p_ctrl = p_context->p_ctrl;

    FSP_ERROR_RETURN(p_ctrl->open == UART_W_SLEEP, FSP_ERR_INVALID_MODE);

    r_uart_w_irq_cfg(p_ctrl, p_ctrl->p_cfg->rxi_ipl, p_ctrl->p_cfg->rxi_irq);
    hw_clk_enable_uart_w_clk(p_ctrl->p_cfg->channel);
    r_uart_w_config_set(p_ctrl, p_ctrl->p_cfg);

    /* Restore the baud rate -
     * Can be modified by setter func so can't be restored as part of r_uart_w_config_set()
     */
    p_ctrl->p_reg->UART_IBRD_REG = p_context->state.UART_IBRD_REG;
    p_ctrl->p_reg->UART_FBRD_REG = p_context->state.UART_FBRD_REG;

    p_ctrl->open = UART_W_OPEN;

    return err;
}

static void r_uart_w_pmgr_callback (pmgr_callback_args_t * p_args)
{
    pmgr_instance_info_t * p_pmgr_info = (pmgr_instance_info_t *) p_args->p_instance_info;

    if (p_pmgr_info->power_mode == PMGR_LLD_POWER_MODE_SLEEP4)
    {
        if (p_args->event == PMGR_EVENT_ENTERING_SLEEP)
        {
            /* Entering sleep 4/5 - close UART */
            r_uart_w_enter_sleep((r_uart_w_pmgr_context_t *) p_args->p_context);
        }
        else if (p_args->event == PMGR_EVENT_EXITING_SLEEP)
        {
            /* Open UART with previous settings */
            r_uart_w_wakeup((r_uart_w_pmgr_context_t *) p_args->p_context);
        }
    }
}

static fsp_err_t r_uart_w_subscribe_for_pmgr_notifications (uart_w_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t     err       = FSP_SUCCESS;
    pmgr_ctrl_t * pmgr_ctrl = NULL;

    r_uart_w_pmgr_context_t * context = &g_uart_pmgr_context[p_ctrl->p_cfg->channel];

    context->pmgr_info.power_mode    = PMGR_LLD_POWER_MODE_SLEEP4;
    context->pmgr_info.wake_source   = PMGR_WAKE_SOURCE_NONE,
    context->pmgr_notifier_ext.order = PMGR_W_NOTIFIER_ORDER_SYS_HIGH;
    context->p_ctrl = p_ctrl;

    context->clbk_args.constraints     = PMGR_CONSTRAINT_NONE;
    context->clbk_args.event           = PMGR_EVENT_NOT_SET;
    context->clbk_args.p_context       = (void *) context;
    context->clbk_args.p_instance_info = (void *) &context->pmgr_info;

    pmgr_ctrl = RM_PMGR_W_get_ctrl();
    FSP_ASSERT(pmgr_ctrl != NULL);

    err = RM_PMGR_W_notifier_register(pmgr_ctrl,
                                      r_uart_w_pmgr_callback,
                                      &context->clbk_args,
                                      &context->pmgr_notifier_ext);
    FSP_ASSERT(FSP_SUCCESS == err);

    return FSP_SUCCESS;
}

static fsp_err_t r_uart_w_unsubscribe_from_pmgr_notifications (uart_w_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t     err       = FSP_SUCCESS;
    pmgr_ctrl_t * pmgr_ctrl = NULL;

    pmgr_ctrl = RM_PMGR_W_get_ctrl();
    FSP_ASSERT(pmgr_ctrl != NULL);

    r_uart_w_pmgr_context_t * context = &g_uart_pmgr_context[p_ctrl->p_cfg->channel];
    err = RM_PMGR_W_notifier_unregister(pmgr_ctrl, context->pmgr_notifier_ext.notifier_id);
    FSP_ASSERT(FSP_SUCCESS == err);

    return FSP_SUCCESS;
}

static uint32_t r_uart_w_get_expected_tx_time_ms (uart_w_instance_ctrl_t * p_ctrl, uint32_t tx_bytes)
{
    uart_cfg_t const * const p_cfg = p_ctrl->p_cfg;
    uint8_t  bits_per_byte         = p_cfg->data_bits + p_cfg->parity + p_cfg->stop_bits + 1;
    uint32_t total_bits            = tx_bytes * bits_per_byte;
    uint64_t freq_hz               = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_UART);
    uint32_t baudrate              = 0;
    uint32_t expected_time_ms      = 0;

    if (p_ctrl->p_reg->UART_IBRD_REG_b.BAUD_DIVINT)
    {
        baudrate = (uint32_t) (freq_hz / (16 * p_ctrl->p_reg->UART_IBRD_REG_b.BAUD_DIVINT));
    }

    if (baudrate)
    {
        expected_time_ms = ((total_bits * 1000) / baudrate);
    }

    return (expected_time_ms < R_UART_W_TX_TIME_MIN_MS) ? R_UART_W_TX_TIME_MIN_MS : expected_time_ms;
}

static void r_uart_w_tx_done_timer_cb (TimerHandle_t xTimer)
{
    uart_w_instance_ctrl_t * p_ctrl   = (uart_w_instance_ctrl_t *) pvTimerGetTimerID(xTimer);
    uart_w_extended_cfg_t  * p_extend = (uart_w_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    uint32_t                 uart_expected_time_ms;

    vPortEnterCritical();
    if (R_UART_W_IsWritting(p_ctrl) == false)
    {
        if (p_ctrl->tx_onging_flag)
        {
            p_ctrl->tx_onging_flag = false;
            RM_PMGR_W_remove_sleep_constraint(RM_PMGR_W_get_ctrl(), PMGR_CONSTRAINT_SLEEP_PROHIBITED);
        }

        vPortExitCritical();
    }
    else
    {
        vPortExitCritical();

        // Uart still busy wait for next timer cb
        uart_expected_time_ms =
            r_uart_w_get_expected_tx_time_ms(p_ctrl, r_uart_w_get_fifo_trigger_len(p_ctrl, p_extend->rx_fifo_trigger));

        if (xTimerIsTimerActive(xTimer) == pdFALSE)
        {
            xTimerChangePeriod(xTimer, pdMS_TO_TICKS(uart_expected_time_ms), portMAX_DELAY);

            xTimerStart(xTimer, portMAX_DELAY);
        }
    }
}

 #endif
#endif
