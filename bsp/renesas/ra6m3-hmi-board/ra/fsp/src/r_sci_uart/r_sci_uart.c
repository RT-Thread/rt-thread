/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_sci_uart.h"
#include <string.h>

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#ifndef SCI_UART_CFG_RX_ENABLE
 #define SCI_UART_CFG_RX_ENABLE                 1
#endif
#ifndef SCI_UART_CFG_TX_ENABLE
 #define SCI_UART_CFG_TX_ENABLE                 1
#endif

/* Number of divisors in the data table used for baud rate calculation. */
#define SCI_UART_NUM_DIVISORS_ASYNC             (13U)

/* Valid range of values for the modulation duty register is 128 - 256 (256 = modulation disabled). */
#define SCI_UART_MDDR_MIN                       (128U)
#define SCI_UART_MDDR_MAX                       (256U)

/* The bit rate register is 8-bits, so the maximum value is 255. */
#define SCI_UART_BRR_MAX                        (255U)

/* No limit to the number of bytes to read or write if DTC is not used. */
#define SCI_UART_MAX_READ_WRITE_NO_DTC          (0xFFFFFFFFU)

/* Mask of invalid data bits in 9-bit mode. */
#define SCI_UART_ALIGN_2_BYTES                  (0x1U)

/* "SCIU" in ASCII.  Used to determine if the control block is open. */
#define SCI_UART_OPEN                           (0x53434955U)

#define SCI_UART_SCMR_DEFAULT_VALUE             (0xF2U)
#define SCI_UART_BRR_DEFAULT_VALUE              (0xFFU)
#define SCI_UART_MDDR_DEFAULT_VALUE             (0xFFU)
#define SCI_UART_FCR_DEFAULT_VALUE              (0xF800)
#define SCI_UART_DCCR_DEFAULT_VALUE             (0x40U)

#define SCI_UART_FIFO_DAT_MASK                  (0x1FFU)

#define FRDR_TDAT_MASK_9BITS                    (0x01FFU)
#define SPTR_SPB2D_BIT                          (1U)
#define SPTR_OUTPUT_ENABLE_MASK                 (0x04U)

#define SCI_UART_SSR_FIFO_DR_RDF                (0x41)

#define SCI_UART_SPMR_CTSE_OFFSET               (1U)

/* SCI SCR register bit masks */
#define SCI_SCR_TEIE_MASK                       (0x04U) ///< Transmit End Interrupt Enable
#define SCI_SCR_RE_MASK                         (0x10U) ///< Receive Enable
#define SCI_SCR_TE_MASK                         (0x20U) ///< Transmit Enable
#define SCI_SCR_RIE_MASK                        (0x40U) ///< Receive Interrupt Enable
#define SCI_SCR_TIE_MASK                        (0x80U) ///< Transmit Interrupt Enable

/* SCI SEMR register bit offsets */
#define SCI_UART_SEMR_BRME_OFFSET               (2U)
#define SCI_UART_SEMR_ABCSE_OFFSET              (3U)
#define SCI_UART_SEMR_ABCS_OFFSET               (4U)
#define SCI_UART_SEMR_BGDM_OFFSET               (6U)
#define SCI_UART_SEMR_BAUD_SETTING_MASK         ((1U << SCI_UART_SEMR_BRME_OFFSET) |  \
                                                 (1U << SCI_UART_SEMR_ABCSE_OFFSET) | \
                                                 (1U << SCI_UART_SEMR_ABCS_OFFSET) | (1U << SCI_UART_SEMR_BGDM_OFFSET))

/* SCI SMR register bit masks */
#define SCI_SMR_CKS_VALUE_MASK                  (0x03U) ///< CKS: 2 bits

/* SCI SSR register receiver error bit masks */
#define SCI_SSR_ORER_MASK                       (0x20U) ///< overflow error
#define SCI_SSR_FER_MASK                        (0x10U) ///< framing error
#define SCI_SSR_PER_MASK                        (0x08U) ///< parity err
#define SCI_SSR_FIFO_RESERVED_MASK              (0x02U) ///< Reserved bit mask for SSR_FIFO register
#define SCI_RCVR_ERR_MASK                       (SCI_SSR_ORER_MASK | SCI_SSR_FER_MASK | SCI_SSR_PER_MASK)

#define SCI_REG_SIZE                            (R_SCI1_BASE - R_SCI0_BASE)

#define SCI_UART_INVALID_8BIT_PARAM             (0xFFU)
#define SCI_UART_INVALID_16BIT_PARAM            (0xFFFFU)

#define SCI_UART_DTC_MAX_TRANSFER               (0x10000U)

#define SCI_UART_FCR_TRIGGER_MASK               (0xF)
#define SCI_UART_FCR_RSTRG_OFFSET               (12)
#define SCI_UART_FCR_RTRG_OFFSET                (8)
#define SCI_UART_FCR_TTRG_OFFSET                (4)
#define SCI_UART_FCR_RESET_TX_RX                (0x6)

#define SCI_UART_9BIT_TRANSFER_BUFFER_OFFSET    (0xB)
#define SCI_UART_FIFO_TRANSFER_BUFFER_OFFSET    (0xC)

#define SCI_UART_DTC_RX_TRANSFER_SETTINGS       ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |         \
                                                 (TRANSFER_SIZE_1_BYTE << TRANSFER_SETTINGS_SIZE_BITS) |         \
                                                 (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                                 (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |              \
                                                 (TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_DEST_ADDR_BITS))
#define SCI_UART_DTC_TX_TRANSFER_SETTINGS       ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |               \
                                                 (TRANSFER_SIZE_1_BYTE << TRANSFER_SETTINGS_SIZE_BITS) |               \
                                                 (TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                                 (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |                    \
                                                 (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_DEST_ADDR_BITS))
#ifndef SCI_UART_FLOW_CONTROL_ACTIVE
 #define SCI_UART_FLOW_CONTROL_ACTIVE           BSP_IO_LEVEL_HIGH
#endif

#ifndef SCI_UART_FLOW_CONTROL_INACTIVE
 #define SCI_UART_FLOW_CONTROL_INACTIVE         BSP_IO_LEVEL_LOW
#endif

/***********************************************************************************************************************
 * Private constants
 **********************************************************************************************************************/
static const int32_t SCI_UART_100_PERCENT_X_1000 = 100000;
static const int32_t SCI_UART_MDDR_DIVISOR       = 256;

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
static const uint32_t SCI_UART_MAX_BAUD_RATE_ERROR_X_1000 = 15000;
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef struct st_baud_setting_const_t
{
    uint8_t bgdm  : 1;                 /**< BGDM value to get divisor */
    uint8_t abcs  : 1;                 /**< ABCS value to get divisor */
    uint8_t abcse : 1;                 /**< ABCSE value to get divisor */
    uint8_t cks   : 2;                 /**< CKS  value to get divisor (CKS = N) */
} baud_setting_const_t;

/* Noise filter setting definition */
typedef enum e_noise_cancel_lvl
{
    NOISE_CANCEL_LVL1,                 /**< Noise filter level 1(weak) */
    NOISE_CANCEL_LVL2,                 /**< Noise filter level 2 */
    NOISE_CANCEL_LVL3,                 /**< Noise filter level 3 */
    NOISE_CANCEL_LVL4                  /**< Noise filter level 4(strong) */
} noise_cancel_lvl_t;

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * sci_uart_prv_ns_callback)(uart_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile sci_uart_prv_ns_callback)(uart_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static void r_sci_negate_de_pin(sci_uart_instance_ctrl_t const * const p_ctrl);

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)

static fsp_err_t r_sci_read_write_param_check(sci_uart_instance_ctrl_t const * const p_ctrl,
                                              uint8_t const * const                  addr,
                                              uint32_t const                         bytes);

#endif

static void r_sci_uart_config_set(sci_uart_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg);

#if SCI_UART_CFG_DTC_SUPPORTED
static fsp_err_t r_sci_uart_transfer_configure(sci_uart_instance_ctrl_t * const p_ctrl,
                                               transfer_instance_t const      * p_transfer,
                                               uint32_t                       * p_transfer_reg,
                                               uint32_t                         address);

static fsp_err_t r_sci_uart_transfer_open(sci_uart_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg);

static void r_sci_uart_transfer_close(sci_uart_instance_ctrl_t * p_ctrl);

#endif

static void r_sci_uart_baud_set(R_SCI0_Type * p_sci_reg, baud_setting_t const * const p_baud_setting);
static void r_sci_uart_call_callback(sci_uart_instance_ctrl_t * p_ctrl, uint32_t data, uart_event_t event);

#if SCI_UART_CFG_FIFO_SUPPORT
static void r_sci_uart_fifo_cfg(sci_uart_instance_ctrl_t * const p_ctrl);

#endif

static void r_sci_irq_cfg(sci_uart_instance_ctrl_t * const p_ctrl, uint8_t const ipl, IRQn_Type const p_irq);

static void r_sci_irqs_cfg(sci_uart_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg);

#if (SCI_UART_CFG_TX_ENABLE)
void r_sci_uart_write_no_transfer(sci_uart_instance_ctrl_t * const p_ctrl);

#endif

#if (SCI_UART_CFG_RX_ENABLE)
void r_sci_uart_rxi_read_no_transfer(sci_uart_instance_ctrl_t * const p_ctrl);

void sci_uart_rxi_isr(void);

void r_sci_uart_read_data(sci_uart_instance_ctrl_t * const p_ctrl, uint32_t * const p_data);

void sci_uart_eri_isr(void);

#endif

#if (SCI_UART_CFG_TX_ENABLE)
void sci_uart_txi_isr(void);
void sci_uart_tei_isr(void);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Name of module used by error logger macro */
#if BSP_CFG_ERROR_LOG != 0
static const char g_module_name[] = "sci_uart";
#endif

/* Baud rate divisor information (UART mode) */
static const baud_setting_const_t g_async_baud[SCI_UART_NUM_DIVISORS_ASYNC] =
{
    {0U, 0U, 1U, 0U},                  /* BGDM, ABCS, ABCSE, n */
    {1U, 1U, 0U, 0U},
    {1U, 0U, 0U, 0U},
    {0U, 0U, 1U, 1U},
    {0U, 0U, 0U, 0U},
    {1U, 0U, 0U, 1U},
    {0U, 0U, 1U, 2U},
    {0U, 0U, 0U, 1U},
    {1U, 0U, 0U, 2U},
    {0U, 0U, 1U, 3U},
    {0U, 0U, 0U, 2U},
    {1U, 0U, 0U, 3U},
    {0U, 0U, 0U, 3U}
};

static const uint16_t g_div_coefficient[SCI_UART_NUM_DIVISORS_ASYNC] =
{
    6U,
    8U,
    16U,
    24U,
    32U,
    64U,
    96U,
    128U,
    256U,
    384U,
    512U,
    1024U,
    2048U,
};

/* UART on SCI HAL API mapping for UART interface */
const uart_api_t g_uart_on_sci =
{
    .open               = R_SCI_UART_Open,
    .close              = R_SCI_UART_Close,
    .write              = R_SCI_UART_Write,
    .read               = R_SCI_UART_Read,
    .infoGet            = R_SCI_UART_InfoGet,
    .baudSet            = R_SCI_UART_BaudSet,
    .communicationAbort = R_SCI_UART_Abort,
    .callbackSet        = R_SCI_UART_CallbackSet,
    .readStop           = R_SCI_UART_ReadStop,
};

/*******************************************************************************************************************//**
 * @addtogroup SCI_UART
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
 * @retval  FSP_ERR_INVALID_ARGUMENT       Flow control is enabled but flow control pin is not defined or selected channel
 *                                         does not support "Hardware CTS and Hardware RTS" flow control.
 * @retval  FSP_ERR_ALREADY_OPEN           Control block has already been opened or channel is being used by another
 *                                         instance. Call close() then open() to reconfigure.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::open
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_Open (uart_ctrl_t * const p_api_ctrl, uart_cfg_t const * const p_cfg)
{
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) p_api_ctrl;

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)

    /* Check parameters. */
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_cfg);

    FSP_ASSERT(p_cfg->p_extend);
    FSP_ASSERT(((sci_uart_extended_cfg_t *) p_cfg->p_extend)->p_baud_setting);
    FSP_ERROR_RETURN(SCI_UART_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Make sure this channel exists. */
    FSP_ERROR_RETURN(BSP_FEATURE_SCI_CHANNELS & (1U << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    if (((sci_uart_extended_cfg_t *) p_cfg->p_extend)->flow_control == SCI_UART_FLOW_CONTROL_CTSRTS)
    {
        FSP_ERROR_RETURN(
            ((sci_uart_extended_cfg_t *) p_cfg->p_extend)->flow_control_pin != SCI_UART_INVALID_16BIT_PARAM,
            FSP_ERR_INVALID_ARGUMENT);
    }

    if (((sci_uart_extended_cfg_t *) p_cfg->p_extend)->flow_control == SCI_UART_FLOW_CONTROL_HARDWARE_CTSRTS)
    {
        FSP_ERROR_RETURN((0U != (((1U << (p_cfg->channel)) & BSP_FEATURE_SCI_UART_CSTPEN_CHANNELS))),
                         FSP_ERR_INVALID_ARGUMENT);
    }

 #if (SCI_UART_CFG_RS485_SUPPORT)
    if (((sci_uart_extended_cfg_t *) p_cfg->p_extend)->rs485_setting.enable == SCI_UART_RS485_ENABLE)
    {
        FSP_ERROR_RETURN(
            ((sci_uart_extended_cfg_t *) p_cfg->p_extend)->rs485_setting.de_control_pin != SCI_UART_INVALID_16BIT_PARAM,
            FSP_ERR_INVALID_ARGUMENT);
    }
 #endif

    FSP_ASSERT(p_cfg->rxi_irq >= 0);
    FSP_ASSERT(p_cfg->txi_irq >= 0);
    FSP_ASSERT(p_cfg->tei_irq >= 0);
    FSP_ASSERT(p_cfg->eri_irq >= 0);
#endif

    p_ctrl->p_reg = ((R_SCI0_Type *) (R_SCI0_BASE + (SCI_REG_SIZE * p_cfg->channel)));

    p_ctrl->fifo_depth = 0U;
#if SCI_UART_CFG_FIFO_SUPPORT

    /* Check if the channel supports fifo */
    if (BSP_FEATURE_SCI_UART_FIFO_CHANNELS & (1U << p_cfg->channel))
    {
        p_ctrl->fifo_depth = BSP_FEATURE_SCI_UART_FIFO_DEPTH;
    }
#endif

    p_ctrl->p_cfg = p_cfg;

    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    p_ctrl->data_bytes = 1U;
    if (UART_DATA_BITS_9 == p_cfg->data_bits)
    {
        p_ctrl->data_bytes = 2U;
    }

    /* Configure the interrupts. */
    r_sci_irqs_cfg(p_ctrl, p_cfg);

#if SCI_UART_CFG_DTC_SUPPORTED

    /* Configure the transfer interface for transmission and reception if provided. */
    fsp_err_t err = r_sci_uart_transfer_open(p_ctrl, p_cfg);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Negate driver enable if RS-485 mode is enabled. */
    r_sci_negate_de_pin(p_ctrl);

    /* Enable the SCI channel and reset the registers to their initial state. */
    R_BSP_MODULE_START(FSP_IP_SCI, p_cfg->channel);

    /* Initialize registers as defined in section 34.3.7 "SCI Initialization in Asynchronous Mode" in the RA6M3 manual
     * R01UH0886EJ0100 or the relevant section for the MCU being used. */
    p_ctrl->p_reg->SCR   = 0U;
    p_ctrl->p_reg->SSR   = 0U;
    p_ctrl->p_reg->SIMR1 = 0U;
    p_ctrl->p_reg->SIMR2 = 0U;
    p_ctrl->p_reg->SIMR3 = 0U;
    p_ctrl->p_reg->CDR   = 0U;

    /* Check if the channel supports address matching */
    if (BSP_FEATURE_SCI_ADDRESS_MATCH_CHANNELS & (1U << p_cfg->channel))
    {
        p_ctrl->p_reg->DCCR = SCI_UART_DCCR_DEFAULT_VALUE;
    }

    /* Set the default level of the TX pin to 1. */
    p_ctrl->p_reg->SPTR = (uint8_t) (1U << SPTR_SPB2D_BIT) | SPTR_OUTPUT_ENABLE_MASK;

    /* Set the UART configuration settings provided in ::uart_cfg_t and ::sci_uart_extended_cfg_t. */
    r_sci_uart_config_set(p_ctrl, p_cfg);

    p_ctrl->p_tx_src      = NULL;
    p_ctrl->tx_src_bytes  = 0U;
    p_ctrl->p_rx_dest     = NULL;
    p_ctrl->rx_dest_bytes = 0;

    sci_uart_extended_cfg_t * p_extend = (sci_uart_extended_cfg_t *) p_cfg->p_extend;

    uint32_t scr = ((uint8_t) p_extend->clock) & 0x3U;
#if (SCI_UART_CFG_RX_ENABLE)

    /* If reception is enabled at build time, enable reception. */
    /* NOTE: Transmitter and its interrupt are enabled in R_SCI_UART_Write(). */
    scr |= SCI_SCR_RE_MASK;
    R_BSP_IrqEnable(p_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqEnable(p_ctrl->p_cfg->eri_irq);

    scr |= SCI_SCR_RIE_MASK;
#endif

#if (SCI_UART_CFG_TX_ENABLE)
    R_BSP_IrqEnable(p_ctrl->p_cfg->txi_irq);
    R_BSP_IrqEnable(p_ctrl->p_cfg->tei_irq);
    scr |= SCI_SCR_TE_MASK;
#endif
    p_ctrl->p_reg->SCR = (uint8_t) scr;

    p_ctrl->flow_pin = p_extend->flow_control_pin;

#if SCI_UART_CFG_FLOW_CONTROL_SUPPORT
    if (p_ctrl->flow_pin != SCI_UART_INVALID_16BIT_PARAM)
    {
        R_BSP_PinAccessEnable();
        R_BSP_PinWrite(p_ctrl->flow_pin, SCI_UART_FLOW_CONTROL_INACTIVE);
        R_BSP_PinAccessDisable();
    }
#endif

    p_ctrl->open = SCI_UART_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Aborts any in progress transfers. Disables interrupts, receiver, and transmitter.  Closes lower level transfer
 * drivers if used. Removes power. Implements @ref uart_api_t::close
 *
 * @retval  FSP_SUCCESS              Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION        Pointer to UART control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_Close (uart_ctrl_t * const p_api_ctrl)
{
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) p_api_ctrl;
#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Mark the channel not open so other APIs cannot use it. */
    p_ctrl->open = 0U;

    /* Disable interrupts, receiver, and transmitter. Disable baud clock output.*/
    p_ctrl->p_reg->SCR = 0U;

#if (SCI_UART_CFG_RX_ENABLE)

    /* If reception is enabled at build time, disable reception irqs. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);
#endif
#if (SCI_UART_CFG_TX_ENABLE)

    /* If transmission is enabled at build time, disable transmission irqs. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);
#endif

#if SCI_UART_CFG_DTC_SUPPORTED

    /* Close the lower level transfer instances. */
    r_sci_uart_transfer_close(p_ctrl);
#endif

    /* Remove power to the channel. */
    R_BSP_MODULE_STOP(FSP_IP_SCI, p_ctrl->p_cfg->channel);

    /* Negate driver enable if RS-485 mode is enabled. */
    r_sci_negate_de_pin(p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Receives user specified number of bytes into destination buffer pointer. Implements @ref uart_api_t::read
 *
 * @retval  FSP_SUCCESS                  Data reception successfully ends.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 *                                       Number of transfers outside the max or min boundary when transfer instance used
 * @retval  FSP_ERR_INVALID_ARGUMENT     Destination address or data size is not valid for 9-bit mode.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_IN_USE               A previous read operation is still in progress.
 * @retval  FSP_ERR_UNSUPPORTED          SCI_UART_CFG_RX_ENABLE is set to 0
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::reset
 *
 * @note If 9-bit data length is specified at R_SCI_UART_Open call, p_dest must be aligned 16-bit boundary.
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_Read (uart_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
#if (SCI_UART_CFG_RX_ENABLE)
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_SUCCESS;

 #if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    err = r_sci_read_write_param_check(p_ctrl, p_dest, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN(0U == p_ctrl->rx_dest_bytes, FSP_ERR_IN_USE);
 #endif

 #if SCI_UART_CFG_DTC_SUPPORTED

    /* Configure transfer instance to receive the requested number of bytes if transfer is used for reception. */
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        uint32_t size = bytes >> (p_ctrl->data_bytes - 1);
  #if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)

        /* Check that the number of transfers is within the 16-bit limit. */
        FSP_ASSERT(size <= SCI_UART_DTC_MAX_TRANSFER);
  #endif
        err =
            p_ctrl->p_cfg->p_transfer_rx->p_api->reset(p_ctrl->p_cfg->p_transfer_rx->p_ctrl, NULL, (void *) p_dest,
                                                       (uint16_t) size);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif

    /* Save the destination address and size for use in rxi_isr. */
    p_ctrl->p_rx_dest     = p_dest;
    p_ctrl->rx_dest_bytes = bytes;

    return err;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(bytes);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Transmits user specified number of bytes from the source buffer pointer. Implements @ref uart_api_t::write
 *
 * @retval  FSP_SUCCESS                  Data transmission finished successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 *                                       Number of transfers outside the max or min boundary when transfer instance used
 * @retval  FSP_ERR_INVALID_ARGUMENT     Source address or data size is not valid for 9-bit mode.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_IN_USE               A UART transmission is in progress
 * @retval  FSP_ERR_UNSUPPORTED          SCI_UART_CFG_TX_ENABLE is set to 0
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::reset
 *
 * @note If 9-bit data length is specified at R_SCI_UART_Open call, p_src must be aligned on a 16-bit boundary.
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_Write (uart_ctrl_t * const p_api_ctrl, uint8_t const * const p_src, uint32_t const bytes)
{
#if (SCI_UART_CFG_TX_ENABLE)
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) p_api_ctrl;
 #if SCI_UART_CFG_PARAM_CHECKING_ENABLE || SCI_UART_CFG_DTC_SUPPORTED
    fsp_err_t err = FSP_SUCCESS;
 #endif

 #if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    err = r_sci_read_write_param_check(p_ctrl, p_src, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN(0U == p_ctrl->tx_src_bytes, FSP_ERR_IN_USE);
 #endif

 #if (SCI_UART_CFG_RS485_SUPPORT)
    sci_uart_extended_cfg_t * p_extend = (sci_uart_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* If RS-485 is enabled, then assert the driver enable pin at the start of a write transfer. */
    if (p_extend->rs485_setting.enable)
    {
        R_BSP_PinAccessEnable();

        bsp_io_level_t level = SCI_UART_RS485_DE_POLARITY_HIGH ==
                               p_extend->rs485_setting.polarity ? BSP_IO_LEVEL_HIGH : BSP_IO_LEVEL_LOW;
        R_BSP_PinWrite(p_extend->rs485_setting.de_control_pin, level);

        R_BSP_PinAccessDisable();
    }
 #endif

    /* Transmit interrupts must be disabled to start with. */
    p_ctrl->p_reg->SCR &= (uint8_t) ~(SCI_SCR_TIE_MASK | SCI_SCR_TEIE_MASK);

    /* If the fifo is not used the first write will be done from this function. Subsequent writes will be done
     * from txi_isr. */
 #if SCI_UART_CFG_FIFO_SUPPORT
    if (p_ctrl->fifo_depth > 0U)
    {
        p_ctrl->tx_src_bytes = bytes;
        p_ctrl->p_tx_src     = p_src;
    }
    else
 #endif
    {
        p_ctrl->tx_src_bytes = bytes - p_ctrl->data_bytes;
        p_ctrl->p_tx_src     = p_src + p_ctrl->data_bytes;
    }

 #if SCI_UART_CFG_DTC_SUPPORTED

    /* If a transfer instance is used for transmission, reset the transfer instance to transmit the requested
     * data. */
    if ((NULL != p_ctrl->p_cfg->p_transfer_tx) && p_ctrl->tx_src_bytes)
    {
        uint32_t data_bytes    = p_ctrl->data_bytes;
        uint32_t num_transfers = p_ctrl->tx_src_bytes >> (data_bytes - 1);
        p_ctrl->tx_src_bytes = 0U;
  #if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)

        /* Check that the number of transfers is within the 16-bit limit. */
        FSP_ASSERT(num_transfers <= SCI_UART_DTC_MAX_TRANSFER);
  #endif

        err = p_ctrl->p_cfg->p_transfer_tx->p_api->reset(p_ctrl->p_cfg->p_transfer_tx->p_ctrl,
                                                         (void const *) p_ctrl->p_tx_src,
                                                         NULL,
                                                         (uint16_t) num_transfers);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif

    /* Trigger a TXI interrupt. This triggers the transfer instance or a TXI interrupt if the transfer instance is
     * not used. */
    p_ctrl->p_reg->SCR |= SCI_SCR_TIE_MASK;
 #if SCI_UART_CFG_FIFO_SUPPORT
    if (p_ctrl->fifo_depth == 0U)
 #endif
    {
        /* On channels with no FIFO, the first byte is sent from this function to trigger the first TXI event.  This
         * method is used instead of setting TE and TIE at the same time as recommended in the hardware manual to avoid
         * the one frame delay that occurs when the TE bit is set. */
        if (2U == p_ctrl->data_bytes)
        {
            p_ctrl->p_reg->FTDRHL = *((uint16_t *) (p_src)) | (uint16_t) ~(SCI_UART_FIFO_DAT_MASK);
        }
        else
        {
            p_ctrl->p_reg->TDR = *(p_src);
        }
    }

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_src);
    FSP_PARAMETER_NOT_USED(bytes);

    return FSP_ERR_UNSUPPORTED;
#endif
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
fsp_err_t R_SCI_UART_CallbackSet (uart_ctrl_t * const          p_api_ctrl,
                                  void (                     * p_callback)(uart_callback_args_t *),
                                  void const * const           p_context,
                                  uart_callback_args_t * const p_callback_memory)
{
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) p_api_ctrl;

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if SCI_UART_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    uart_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                       CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(uart_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the baud rate using the clock selected in Open. p_baud_setting is a pointer to a baud_setting_t structure.
 * Implements @ref uart_api_t::baudSet
 *
 * @warning This terminates any in-progress transmission.
 *
 * @retval  FSP_SUCCESS                  Baud rate was successfully changed.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL or the UART is not configured to use the
 *                                       internal clock.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_BaudSet (uart_ctrl_t * const p_api_ctrl, void const * const p_baud_setting)
{
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) p_api_ctrl;

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Verify that the On-Chip baud rate generator is currently selected. */
    FSP_ASSERT((p_ctrl->p_reg->SCR_b.CKE & 0x2) == 0U);
#endif

    /* Save SCR configurations except transmit interrupts. Resuming transmission after reconfiguring baud settings is
     * not supported. */
    uint8_t preserved_scr = p_ctrl->p_reg->SCR & (uint8_t) ~(SCI_SCR_TIE_MASK | SCI_SCR_TEIE_MASK);

    /* Disables transmitter and receiver. This terminates any in-progress transmission. */
    p_ctrl->p_reg->SCR = preserved_scr & (uint8_t) ~(SCI_SCR_TE_MASK | SCI_SCR_RE_MASK | SCI_SCR_RIE_MASK);
    p_ctrl->p_tx_src   = NULL;

    /* Apply new baud rate register settings. */
    r_sci_uart_baud_set(p_ctrl->p_reg, p_baud_setting);

    /* Restore all settings except transmit interrupts. */
    p_ctrl->p_reg->SCR = preserved_scr;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the driver information, including the maximum number of bytes that can be received or transmitted at a time.
 * Implements @ref uart_api_t::infoGet
 *
 * @retval  FSP_SUCCESS                  Information stored in provided p_info.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_InfoGet (uart_ctrl_t * const p_api_ctrl, uart_info_t * const p_info)
{
#if SCI_UART_CFG_PARAM_CHECKING_ENABLE || SCI_UART_CFG_DTC_SUPPORTED
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) p_api_ctrl;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_info);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_info->read_bytes_max  = SCI_UART_MAX_READ_WRITE_NO_DTC;
    p_info->write_bytes_max = SCI_UART_MAX_READ_WRITE_NO_DTC;

#if (SCI_UART_CFG_RX_ENABLE)

    /* Store number of bytes that can be read at a time. */
 #if SCI_UART_CFG_DTC_SUPPORTED
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_info->read_bytes_max = SCI_UART_DTC_MAX_TRANSFER;
    }
 #endif
#endif

#if (SCI_UART_CFG_TX_ENABLE)

    /* Store number of bytes that can be written at a time. */
 #if SCI_UART_CFG_DTC_SUPPORTED
    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_info->write_bytes_max = SCI_UART_DTC_MAX_TRANSFER;
    }
 #endif
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides API to abort ongoing transfer. Transmission is aborted after the current character is transmitted.
 * Reception is still enabled after abort(). Any characters received after abort() and before the transfer
 * is reset in the next call to read(), will arrive via the callback function with event UART_EVENT_RX_CHAR.
 * Implements @ref uart_api_t::communicationAbort
 *
 * @retval  FSP_SUCCESS                  UART transaction aborted successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_UNSUPPORTED          The requested Abort direction is unsupported.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::disable
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_Abort (uart_ctrl_t * const p_api_ctrl, uart_dir_t communication_to_abort)
{
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_ERR_UNSUPPORTED;

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if (SCI_UART_CFG_TX_ENABLE)
    if (UART_DIR_TX & communication_to_abort)
    {
        err                 = FSP_SUCCESS;
        p_ctrl->p_reg->SCR &= (uint8_t) ~(SCI_SCR_TIE_MASK | SCI_SCR_TEIE_MASK);
 #if SCI_UART_CFG_DTC_SUPPORTED
        if (NULL != p_ctrl->p_cfg->p_transfer_tx)
        {
            err = p_ctrl->p_cfg->p_transfer_tx->p_api->disable(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
        }
 #endif

 #if SCI_UART_CFG_FIFO_SUPPORT
        if (0U != p_ctrl->fifo_depth)
        {
            /* Reset the transmit fifo */
            p_ctrl->p_reg->FCR_b.TFRST = 1U;

            /* Wait until TFRST cleared after 1 PCLK according to section 34.2.26 "FIFO Control Register (FCR) in the
             * RA6M3 manual R01UH0886EJ0100 or the relevant section for the MCU being used.*/
            FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->FCR_b.TFRST, 0U);
        }
 #endif
        p_ctrl->tx_src_bytes = 0U;

        /* Negate driver enable if RS-485 mode is enabled. */
        r_sci_negate_de_pin(p_ctrl);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif
#if (SCI_UART_CFG_RX_ENABLE)
    if (UART_DIR_RX & communication_to_abort)
    {
        err = FSP_SUCCESS;

        p_ctrl->rx_dest_bytes = 0U;
 #if SCI_UART_CFG_DTC_SUPPORTED
        if (NULL != p_ctrl->p_cfg->p_transfer_rx)
        {
            err = p_ctrl->p_cfg->p_transfer_rx->p_api->disable(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
        }
 #endif
 #if SCI_UART_CFG_FIFO_SUPPORT
        if (0U != p_ctrl->fifo_depth)
        {
            /* Reset the receive fifo */
            p_ctrl->p_reg->FCR_b.RFRST = 1U;

            /* Wait until RFRST cleared after 1 PCLK according to section 34.2.26 "FIFO Control Register (FCR) in the
             * RA6M3 manual R01UH0886EJ0100 or the relevant section for the MCU being used.*/
            FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->FCR_b.RFRST, 0U);
        }
 #endif
    }
#endif

    return err;
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
 * @retval  FSP_ERR_UNSUPPORTED          The requested Abort direction is unsupported.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::disable
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_ReadStop (uart_ctrl_t * const p_api_ctrl, uint32_t * remaining_bytes)
{
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) p_api_ctrl;

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if (SCI_UART_CFG_RX_ENABLE)
    *remaining_bytes      = p_ctrl->rx_dest_bytes;
    p_ctrl->rx_dest_bytes = 0U;
 #if SCI_UART_CFG_DTC_SUPPORTED
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        fsp_err_t err = p_ctrl->p_cfg->p_transfer_rx->p_api->disable(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        transfer_properties_t transfer_info;
        err = p_ctrl->p_cfg->p_transfer_rx->p_api->infoGet(p_ctrl->p_cfg->p_transfer_rx->p_ctrl, &transfer_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        *remaining_bytes = transfer_info.transfer_length_remaining;
    }
 #endif
#else

    return FSP_ERR_UNSUPPORTED;
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Calculates baud rate register settings. Evaluates and determines the best possible settings set to the baud rate
 * related registers.
 *
 * @param[in]  baudrate                  Baud rate [bps]. For example, 19200, 57600, 115200, etc.
 * @param[in]  bitrate_modulation        Enable bitrate modulation
 * @param[in]  baud_rate_error_x_1000    Max baud rate error. At most &lt;baud_rate_percent_error&gt; x 1000 required
 *                                       for module to function. Absolute max baud_rate_error is 15000 (15%).
 * @param[out] p_baud_setting            Baud setting information stored here if successful
 *
 * @retval     FSP_SUCCESS               Baud rate is set successfully
 * @retval     FSP_ERR_ASSERTION         Null pointer
 * @retval     FSP_ERR_INVALID_ARGUMENT  Baud rate is '0', error in calculated baud rate is larger than requested
 *                                       max error, or requested max error in baud rate is larger than 15%.
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_BaudCalculate (uint32_t               baudrate,
                                    bool                   bitrate_modulation,
                                    uint32_t               baud_rate_error_x_1000,
                                    baud_setting_t * const p_baud_setting)
{
#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_baud_setting);
    FSP_ERROR_RETURN(SCI_UART_MAX_BAUD_RATE_ERROR_X_1000 >= baud_rate_error_x_1000, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((0U != baudrate), FSP_ERR_INVALID_ARGUMENT);
#endif

    p_baud_setting->brr = SCI_UART_BRR_MAX;
    p_baud_setting->semr_baudrate_bits_b.brme = 0U;
    p_baud_setting->mddr = SCI_UART_MDDR_MIN;

    /* Find the best BRR (bit rate register) value.
     *  In table g_async_baud, divisor values are stored for BGDM, ABCS, ABCSE and N values.  Each set of divisors
     *  is tried, and the settings with the lowest bit rate error are stored. The formula to calculate BRR is as
     *  follows and it must be 255 or less:
     *  BRR = (PCLK / (div_coefficient * baud)) - 1
     */
    int32_t  hit_bit_err = SCI_UART_100_PERCENT_X_1000;
    uint8_t  hit_mddr    = 0U;
    uint32_t divisor     = 0U;

    uint32_t freq_hz = R_FSP_SystemClockHzGet(BSP_FEATURE_SCI_CLOCK);

    for (uint32_t select_16_base_clk_cycles = 0U;
         select_16_base_clk_cycles <= 1U && (hit_bit_err > ((int32_t) baud_rate_error_x_1000));
         select_16_base_clk_cycles++)
    {
        for (uint32_t i = 0U; i < SCI_UART_NUM_DIVISORS_ASYNC; i++)
        {
            /* if select_16_base_clk_cycles == true:  Skip this calculation for divisors that are not acheivable with 16 base clk cycles per bit.
             *  if select_16_base_clk_cycles == false: Skip this calculation for divisors that are only acheivable without 16 base clk cycles per bit.
             */
            if (((uint8_t) select_16_base_clk_cycles) ^ (g_async_baud[i].abcs | g_async_baud[i].abcse))
            {
                continue;
            }

            divisor = (uint32_t) g_div_coefficient[i] * baudrate;
            uint32_t temp_brr = freq_hz / divisor;

            if (temp_brr <= (SCI_UART_BRR_MAX + 1U))
            {
                while (temp_brr > 0U)
                {
                    temp_brr -= 1U;

                    /* Calculate the bit rate error. The formula is as follows:
                     *  bit rate error[%] = {(PCLK / (baud * div_coefficient * (BRR + 1)) - 1} x 100
                     *  calculates bit rate error[%] to three decimal places
                     */
                    int32_t err_divisor = (int32_t) (divisor * (temp_brr + 1U));

                    /* Promoting to 64 bits for calculation, but the final value can never be more than 32 bits, as
                     * described below, so this cast is safe.
                     *    1. (temp_brr + 1) can be off by an upper limit of 1 due to rounding from the calculation:
                     *       freq_hz / divisor, or:
                     *       freq_hz / divisor <= (temp_brr + 1) < (freq_hz / divisor) + 1
                     *    2. Solving for err_divisor:
                     *       freq_hz <= err_divisor < freq_hz + divisor
                     *    3. Solving for bit_err:
                     *       0 >= bit_err >= (freq_hz * 100000 / (freq_hz + divisor)) - 100000
                     *    4. freq_hz >= divisor (or temp_brr would be -1 and we would never enter this while loop), so:
                     *       0 >= bit_err >= 100000 / freq_hz - 100000
                     *    5. Larger frequencies yield larger bit errors (absolute value).  As the frequency grows,
                     *       the bit_err approaches -100000, so:
                     *       0 >= bit_err >= -100000
                     *    6. bit_err is between -100000 and 0.  This entire range fits in an int32_t type, so the cast
                     *       to (int32_t) is safe.
                     */
                    int32_t bit_err = (int32_t) (((((int64_t) freq_hz) * SCI_UART_100_PERCENT_X_1000) /
                                                  err_divisor) - SCI_UART_100_PERCENT_X_1000);

                    uint8_t mddr = 0U;
                    if (bitrate_modulation)
                    {
                        /* Calculate the MDDR (M) value if bit rate modulation is enabled,
                         * The formula to calculate MBBR (from the M and N relationship given in the hardware manual) is as follows
                         * and it must be between 128 and 255.
                         * MDDR = ((div_coefficient * baud * 256) * (BRR + 1)) / PCLK */
                        mddr = (uint8_t) ((uint32_t) err_divisor / (freq_hz / SCI_UART_MDDR_MAX));

                        /* MDDR value must be greater than or equal to SCI_UART_MDDR_MIN. */
                        if (mddr < SCI_UART_MDDR_MIN)
                        {
                            break;
                        }

                        /* Adjust bit rate error for bit rate modulation. The following formula is used:
                         *  bit rate error [%] = ((bit rate error [%, no modulation] + 100) * MDDR / 256) - 100
                         */
                        bit_err = (((bit_err + SCI_UART_100_PERCENT_X_1000) * (int32_t) mddr) /
                                   SCI_UART_MDDR_DIVISOR) - SCI_UART_100_PERCENT_X_1000;
                    }

                    /* Take the absolute value of the bit rate error. */
                    if (bit_err < 0)
                    {
                        bit_err = -bit_err;
                    }

                    /* If the absolute value of the bit rate error is less than the previous lowest absolute value of
                     *  bit rate error, then store these settings as the best value.
                     */
                    if (bit_err < hit_bit_err)
                    {
                        p_baud_setting->semr_baudrate_bits_b.bgdm  = g_async_baud[i].bgdm;
                        p_baud_setting->semr_baudrate_bits_b.abcs  = g_async_baud[i].abcs;
                        p_baud_setting->semr_baudrate_bits_b.abcse = g_async_baud[i].abcse;
                        p_baud_setting->cks = g_async_baud[i].cks;
                        p_baud_setting->brr = (uint8_t) temp_brr;
                        hit_bit_err         = bit_err;
                        hit_mddr            = mddr;
                    }

                    if (bitrate_modulation)
                    {
                        p_baud_setting->semr_baudrate_bits_b.brme = 1U;
                        p_baud_setting->mddr = hit_mddr;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }

    /* Return an error if the percent error is larger than the maximum percent error allowed for this instance */
    FSP_ERROR_RETURN((hit_bit_err <= (int32_t) baud_rate_error_x_1000), FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SCI_UART)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Negate the DE pin if it is enabled.
 *
 * @param[in] p_ctrl Pointer to the control block for the channel.
 **********************************************************************************************************************/
static void r_sci_negate_de_pin (sci_uart_instance_ctrl_t const * const p_ctrl)
{
#if (SCI_UART_CFG_RS485_SUPPORT)
    sci_uart_extended_cfg_t * p_extend = (sci_uart_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* If RS-485 is enabled, then negate the driver enable pin at the end of a write transfer. */
    if (p_extend->rs485_setting.enable)
    {
        R_BSP_PinAccessEnable();

        bsp_io_level_t level = SCI_UART_RS485_DE_POLARITY_HIGH ==
                               p_extend->rs485_setting.polarity ? BSP_IO_LEVEL_LOW : BSP_IO_LEVEL_HIGH;
        R_BSP_PinWrite(p_extend->rs485_setting.de_control_pin, level);

        R_BSP_PinAccessDisable();
    }

#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif
}

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)

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
 * @retval  FSP_ERR_INVALID_ARGUMENT Address is not aligned to 2-byte boundary or size is the odd number when the data
 *                                   length is 9-bit
 **********************************************************************************************************************/
static fsp_err_t r_sci_read_write_param_check (sci_uart_instance_ctrl_t const * const p_ctrl,
                                               uint8_t const * const                  addr,
                                               uint32_t const                         bytes)
{
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(addr);
    FSP_ASSERT(0U != bytes);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    if (2U == p_ctrl->data_bytes)
    {
        /* Do not allow odd buffer address if data length is 9 bits. */
        FSP_ERROR_RETURN((0U == ((uint32_t) addr & SCI_UART_ALIGN_2_BYTES)), FSP_ERR_INVALID_ARGUMENT);

        /* Do not allow odd number of data bytes if data length is 9 bits. */
        FSP_ERROR_RETURN(0U == (bytes % 2U), FSP_ERR_INVALID_ARGUMENT);
    }

    return FSP_SUCCESS;
}

#endif
#if SCI_UART_CFG_DTC_SUPPORTED

/*******************************************************************************************************************//**
 * Subroutine to apply common UART transfer settings.
 *
 * @param[in]  p_cfg              Pointer to UART specific configuration structure
 * @param[in]  p_transfer         Pointer to transfer instance to configure
 *
 * @retval     FSP_SUCCESS        UART transfer drivers successfully configured
 * @retval     FSP_ERR_ASSERTION  Invalid pointer
 **********************************************************************************************************************/
static fsp_err_t r_sci_uart_transfer_configure (sci_uart_instance_ctrl_t * const p_ctrl,
                                                transfer_instance_t const      * p_transfer,
                                                uint32_t                       * p_transfer_reg,
                                                uint32_t                         sci_buffer_address)
{
    /* Configure the transfer instance, if enabled. */
 #if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_transfer->p_api);
    FSP_ASSERT(NULL != p_transfer->p_ctrl);
    FSP_ASSERT(NULL != p_transfer->p_cfg);
    FSP_ASSERT(NULL != p_transfer->p_cfg->p_info);
    FSP_ASSERT(NULL != p_transfer->p_cfg->p_extend);
 #endif
    transfer_info_t * p_info = p_transfer->p_cfg->p_info;

    /* Casting for compatibility with 7 or 8 bit mode. */
    *p_transfer_reg = sci_buffer_address;

 #if SCI_UART_CFG_FIFO_SUPPORT
    if (p_ctrl->fifo_depth > 0U)
    {
        /* Casting for compatibility with 7 or 8 bit mode. */
        *p_transfer_reg = sci_buffer_address + SCI_UART_FIFO_TRANSFER_BUFFER_OFFSET;
    }
 #endif

    if (UART_DATA_BITS_9 == p_ctrl->p_cfg->data_bits)
    {
        p_info->transfer_settings_word_b.size = TRANSFER_SIZE_2_BYTE;

        /* Casting for compatibility with 7 or 8 bit mode. */
        *p_transfer_reg = sci_buffer_address + SCI_UART_9BIT_TRANSFER_BUFFER_OFFSET;
    }

    fsp_err_t err = p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

#endif

#if SCI_UART_CFG_DTC_SUPPORTED

/*******************************************************************************************************************//**
 * Configures UART related transfer drivers (if enabled).
 *
 * @param[in]     p_ctrl  Pointer to UART control structure
 * @param[in]     p_cfg   Pointer to UART specific configuration structure
 *
 * @retval        FSP_SUCCESS        UART transfer drivers successfully configured
 * @retval        FSP_ERR_ASSERTION  Invalid pointer or required interrupt not enabled in vector table
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::open
 **********************************************************************************************************************/
static fsp_err_t r_sci_uart_transfer_open (sci_uart_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

 #if (SCI_UART_CFG_RX_ENABLE)

    /* If a transfer instance is used for reception, apply UART specific settings and open the transfer instance. */
    if (NULL != p_cfg->p_transfer_rx)
    {
        transfer_info_t * p_info = p_cfg->p_transfer_rx->p_cfg->p_info;

        p_info->transfer_settings_word = SCI_UART_DTC_RX_TRANSFER_SETTINGS;

        err =
            r_sci_uart_transfer_configure(p_ctrl, p_cfg->p_transfer_rx, (uint32_t *) &p_info->p_src,
                                          (uint32_t) &(p_ctrl->p_reg->RDR));
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif
 #if (SCI_UART_CFG_TX_ENABLE)

    /* If a transfer instance is used for transmission, apply UART specific settings and open the transfer instance. */
    if (NULL != p_cfg->p_transfer_tx)
    {
        transfer_info_t * p_info = p_cfg->p_transfer_tx->p_cfg->p_info;

        p_info->transfer_settings_word = SCI_UART_DTC_TX_TRANSFER_SETTINGS;

        err = r_sci_uart_transfer_configure(p_ctrl,
                                            p_cfg->p_transfer_tx,
                                            (uint32_t *) &p_info->p_dest,
                                            (uint32_t) &p_ctrl->p_reg->TDR);

  #if (SCI_UART_CFG_RX_ENABLE)
        if ((err != FSP_SUCCESS) && (NULL != p_cfg->p_transfer_rx))
        {
            p_cfg->p_transfer_rx->p_api->close(p_cfg->p_transfer_rx->p_ctrl);
        }
  #endif
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif

    return err;
}

#endif

/*******************************************************************************************************************//**
 * Configures UART related registers based on user configurations.
 *
 * @param[in]     p_ctrl  Pointer to UART control structure
 * @param[in]     p_cfg   Pointer to UART specific configuration structure
 **********************************************************************************************************************/
static void r_sci_uart_config_set (sci_uart_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg)
{
#if SCI_UART_CFG_FIFO_SUPPORT

    /* Configure FIFO related registers. */
    r_sci_uart_fifo_cfg(p_ctrl);
#else

    /* If fifo support is disabled and the current channel supports fifo make sure it's disabled. */
    if (BSP_FEATURE_SCI_UART_FIFO_CHANNELS & (1U << p_cfg->channel))
    {
        p_ctrl->p_reg->FCR = SCI_UART_FCR_DEFAULT_VALUE;
    }
#endif

    /* Configure parity and stop bits. */
    uint32_t smr  = (((uint32_t) p_cfg->parity << 4U) | ((uint32_t) p_cfg->stop_bits << 3U));
    uint32_t scmr = SCI_UART_SCMR_DEFAULT_VALUE;

    /* Configure data size. */
    if (UART_DATA_BITS_7 == p_cfg->data_bits)
    {
        /* Set the SMR.CHR bit & SCMR.CHR1 bit as selected (Character Length)
         *  Character Length
         *  (CHR1,CHR)
         *  (1, 1) Transmit/receive in 7-bit data length*3
         */
        smr |= (1U << 6);
    }
    else if (UART_DATA_BITS_9 == p_cfg->data_bits)
    {
        /* Set the SMR.CHR bit & SCMR.CHR1 bit as selected (Character Length)
         *  Character Length
         *  (CHR1,CHR)
         *  (0, 0) Transmit/receive in 9-bit data length
         */
        scmr &= ~(1U << 4);
    }
    else
    {
        /* Do nothing.  Default is 8-bit mode. */
    }

    /* Write to the SMR register. */
    p_ctrl->p_reg->SMR = (uint8_t) smr;

    /* Write to the SCMR register. */
    p_ctrl->p_reg->SCMR = (uint8_t) scmr;

    sci_uart_extended_cfg_t * p_extend = (sci_uart_extended_cfg_t *) p_cfg->p_extend;

    /* Configure flow control if CTS/RTS flow control is enabled. */
#if BSP_FEATURE_SCI_UART_CSTPEN_CHANNELS
    if (p_extend->flow_control == SCI_UART_FLOW_CONTROL_HARDWARE_CTSRTS)
    {
        p_ctrl->p_reg->SPMR = R_SCI0_SPMR_CSTPEN_Msk | R_SCI0_SPMR_CTSE_Msk;
    }
    else
#endif
    {
        p_ctrl->p_reg->SPMR = ((uint8_t) (p_extend->flow_control << R_SCI0_SPMR_CTSE_Pos) & R_SCI0_SPMR_CTSE_Msk);
    }

    uint32_t semr = 0;

    /* Starts reception on falling edge of RXD if enabled in extension (otherwise reception starts at low level
     * of RXD). */
    semr |= (p_extend->rx_edge_start & 1U) << 7;

    /* Enables the noise cancellation, fixed to the minimum level, if enabled in the extension. */
    semr |= (p_extend->noise_cancel & 1U) << 5;

    p_ctrl->p_reg->SNFR = NOISE_CANCEL_LVL1;

    if ((SCI_UART_CLOCK_EXT8X == p_extend->clock) || (SCI_UART_CLOCK_EXT16X == p_extend->clock))
    {
        /* Use external clock for baud rate */
        p_ctrl->p_reg->BRR = SCI_UART_BRR_DEFAULT_VALUE;

        if (SCI_UART_CLOCK_EXT8X == p_extend->clock)
        {
            /* Set baud rate as (external clock / 8) */
            semr |= 1U << SCI_UART_SEMR_ABCS_OFFSET;
        }

        p_ctrl->p_reg->SEMR = (uint8_t) semr;
    }
    else
    {
        p_ctrl->p_reg->SEMR = (uint8_t) semr;

        /* Set the baud rate settings for the internal baud rate generator. */
        r_sci_uart_baud_set(p_ctrl->p_reg, p_extend->p_baud_setting);
    }
}

#if SCI_UART_CFG_FIFO_SUPPORT

/*******************************************************************************************************************//**
 * Resets FIFO related registers.
 *
 * @param[in] p_ctrl  Pointer to UART instance control
 * @param[in] p_cfg   Pointer to UART configuration structure
 **********************************************************************************************************************/
static void r_sci_uart_fifo_cfg (sci_uart_instance_ctrl_t * const p_ctrl)
{
    if (0U != p_ctrl->fifo_depth)
    {
        /* Enable the fifo and set the tx and rx reset bits */
        uint32_t fcr = 1U;

 #if (SCI_UART_CFG_RX_ENABLE)
  #if SCI_UART_CFG_DTC_SUPPORTED

        /* If DTC is used keep the receive trigger at the default level of 0. */
        if (NULL == p_ctrl->p_cfg->p_transfer_rx)
  #endif
        {
            /* Otherwise, set receive trigger number as configured by the user. */
            sci_uart_extended_cfg_t const * p_extend = p_ctrl->p_cfg->p_extend;

            /* RTRG(Receive FIFO Data Trigger Number) controls when the RXI interrupt will be generated. If data is
             * received but the trigger number is not met the RXI interrupt will be generated after 15 ETUs from
             * the last stop bit in asynchronous mode. For more information see the FIFO Selected section of "Serial
             * Data Reception in Asynchronous Mode" in the RA6M3 manual R01UH0886EJ0100 or the relevant section for
             * the MCU being used. */
            fcr |= (((p_ctrl->fifo_depth - 1U) & p_extend->rx_fifo_trigger) & SCI_UART_FCR_TRIGGER_MASK) <<
                   SCI_UART_FCR_RTRG_OFFSET;
        }

        /* RTS asserts when the amount of received data stored in the fifo is equal or less than this value. */
        fcr |= ((p_ctrl->fifo_depth - 1U) & SCI_UART_FCR_TRIGGER_MASK) << SCI_UART_FCR_RSTRG_OFFSET;
 #endif

        /* Set the FCR and reset the fifos. */
        p_ctrl->p_reg->FCR = (uint16_t) (fcr | SCI_UART_FCR_RESET_TX_RX);

        /* Wait for the fifo reset to complete after 1 PCLK according to section 34.2.26 "FIFO Control Register (FCR)
         * in the RA6M3 manual R01UH0886EJ0100 or the relevant section for the MCU being used.*/
        FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->FCR, fcr);
    }
}

#endif

/*******************************************************************************************************************//**
 * Sets interrupt priority and initializes vector info.
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 * @param[in]  ipl                       Interrupt priority level
 * @param[in]  irq                       IRQ number for this interrupt
 **********************************************************************************************************************/
static void r_sci_irq_cfg (sci_uart_instance_ctrl_t * const p_ctrl, uint8_t const ipl, IRQn_Type const irq)
{
    /* Disable interrupts, set priority, and store control block in the vector information so it can be accessed
     * from the callback. */
    R_BSP_IrqDisable(irq);
    R_BSP_IrqStatusClear(irq);
    R_BSP_IrqCfg(irq, ipl, p_ctrl);
}

/*******************************************************************************************************************//**
 * Sets interrupt priority and initializes vector info for all interrupts.
 *
 * @param[in]  p_ctrl                    Pointer to UART instance control block
 * @param[in]  p_cfg                     Pointer to UART specific configuration structure
 **********************************************************************************************************************/
static void r_sci_irqs_cfg (sci_uart_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg)
{
#if (SCI_UART_CFG_RX_ENABLE)

    /* ERI is optional. */
    r_sci_irq_cfg(p_ctrl, p_cfg->eri_ipl, p_cfg->eri_irq);
    r_sci_irq_cfg(p_ctrl, p_cfg->rxi_ipl, p_cfg->rxi_irq);
#endif
#if (SCI_UART_CFG_TX_ENABLE)
    r_sci_irq_cfg(p_ctrl, p_cfg->txi_ipl, p_cfg->txi_irq);

    r_sci_irq_cfg(p_ctrl, p_cfg->tei_ipl, p_cfg->tei_irq);
#endif
}

#if SCI_UART_CFG_DTC_SUPPORTED

/*******************************************************************************************************************//**
 * Closes transfer interfaces.
 *
 * @param[in]     p_ctrl     Pointer to UART instance control block
 **********************************************************************************************************************/
static void r_sci_uart_transfer_close (sci_uart_instance_ctrl_t * p_ctrl)
{
 #if (SCI_UART_CFG_RX_ENABLE)
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_ctrl->p_cfg->p_transfer_rx->p_api->close(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }
 #endif
 #if (SCI_UART_CFG_TX_ENABLE)
    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_ctrl->p_cfg->p_transfer_tx->p_api->close(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
    }
 #endif
}

#endif

/*******************************************************************************************************************//**
 * Changes baud rate based on predetermined register settings.
 *
 * @param[in]  p_sci_reg       Base pointer for SCI registers
 * @param[in]  p_baud_setting  Pointer to other divisor related settings
 *
 * @note       The transmitter and receiver (TE and RE bits in SCR) must be disabled prior to calling this function.
 **********************************************************************************************************************/
static void r_sci_uart_baud_set (R_SCI0_Type * p_sci_reg, baud_setting_t const * const p_baud_setting)
{
    /* Set BRR register value. */
    p_sci_reg->BRR = p_baud_setting->brr;

    /* Set clock source for the on-chip baud rate generator. */
    p_sci_reg->SMR_b.CKS = (uint8_t) (SCI_SMR_CKS_VALUE_MASK & p_baud_setting->cks);

    /* Set MDDR register value. */
    p_sci_reg->MDDR = p_baud_setting->mddr;

    /* Set clock divisor settings. */
    p_sci_reg->SEMR = (uint8_t) ((p_sci_reg->SEMR & ~(SCI_UART_SEMR_BAUD_SETTING_MASK)) |
                                 (p_baud_setting->semr_baudrate_bits & SCI_UART_SEMR_BAUD_SETTING_MASK));
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to UART instance control block
 * @param[in]     data       See uart_callback_args_t in r_uart_api.h
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_sci_uart_call_callback (sci_uart_instance_ctrl_t * p_ctrl, uint32_t data, uart_event_t event)
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

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        sci_uart_prv_ns_callback p_callback = (sci_uart_prv_ns_callback) (p_ctrl->p_callback);
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

#if (SCI_UART_CFG_TX_ENABLE)

/*******************************************************************************************************************//**
 * TXI interrupt processing for UART mode. TXI interrupt fires when the data in the data register or FIFO register has
 * been transferred to the data shift register, and the next data can be written.  This interrupt writes the next data.
 * After the last data byte is written, this interrupt disables the TXI interrupt and enables the TEI (transmit end)
 * interrupt.
 **********************************************************************************************************************/
void sci_uart_txi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    if ((NULL == p_ctrl->p_cfg->p_transfer_tx) && (0U != p_ctrl->tx_src_bytes))
    {
        /* Write the data to the FIFO if the channel has a FIFO.  Otherwise write data based on size to the transmit
         * register.  Write to 16-bit TDRHL for 9-bit data, or 8-bit TDR otherwise. */
 #if SCI_UART_CFG_FIFO_SUPPORT
        if (0U != p_ctrl->fifo_depth)
        {
            uint32_t fifo_count = (uint32_t) p_ctrl->p_reg->FDR_b.T;
            for (uint32_t cnt = fifo_count; (cnt < p_ctrl->fifo_depth) && p_ctrl->tx_src_bytes; cnt++)
            {
                if (2U == p_ctrl->data_bytes)
                {
                    p_ctrl->p_reg->FTDRHL =
                        (uint16_t) (*((uint16_t *) p_ctrl->p_tx_src) | (uint16_t) ~(SCI_UART_FIFO_DAT_MASK));
                }
                else
                {
                    p_ctrl->p_reg->FTDRL = *p_ctrl->p_tx_src;
                }

                p_ctrl->tx_src_bytes -= p_ctrl->data_bytes;
                p_ctrl->p_tx_src     += p_ctrl->data_bytes;
            }

            /* Clear TDFE flag */
            /* Don't acess the flag via bit fields because bit 1 is reserved. It must be written as '1' and has an */
            /* undefined read value. Bit fields will attempt to do a read-modify-write which could have unintended */
            /* side effects provided the undefined read behavior. */
            uint8_t ssr_fifo =
                (uint8_t) ((p_ctrl->p_reg->SSR_FIFO | SCI_SSR_FIFO_RESERVED_MASK) & ~R_SCI0_SSR_FIFO_TDFE_Msk);
            p_ctrl->p_reg->SSR_FIFO = ssr_fifo;
        }
        else
 #endif
        {
            if ((2U == p_ctrl->data_bytes))
            {
                /* Write 16-bit data to TDRHL register */
                p_ctrl->p_reg->TDRHL = *((uint16_t *) (p_ctrl->p_tx_src)) | (uint16_t) ~(SCI_UART_FIFO_DAT_MASK);
            }
            else
            {
                /* Write 1byte (uint8_t) data to (uint8_t) data register */
                p_ctrl->p_reg->TDR = *(p_ctrl->p_tx_src);
            }

            /* Update pointer to the next data and number of remaining bytes in the control block. */
            p_ctrl->tx_src_bytes -= p_ctrl->data_bytes;
            p_ctrl->p_tx_src     += p_ctrl->data_bytes;
        }
    }

    if (0U == p_ctrl->tx_src_bytes)
    {
        /* After all data has been transmitted, disable transmit interrupts and enable the transmit end interrupt. */
        uint8_t scr_temp = p_ctrl->p_reg->SCR;
        scr_temp          |= SCI_SCR_TEIE_MASK;
        scr_temp          &= (uint8_t) ~SCI_SCR_TIE_MASK;
        p_ctrl->p_reg->SCR = scr_temp;

        p_ctrl->p_tx_src = NULL;

        /* If a callback was provided, call it with the argument */
        if (NULL != p_ctrl->p_callback)
        {
            r_sci_uart_call_callback(p_ctrl, 0U, UART_EVENT_TX_DATA_EMPTY);
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#endif

#if (SCI_UART_CFG_RX_ENABLE)

/*******************************************************************************************************************//**
 * RXI interrupt processing for UART mode. RXI interrupt happens when data arrives to the data register or the FIFO
 * register.  This function calls callback function when it meets conditions below.
 *  - UART_EVENT_RX_COMPLETE: The number of data which has been read reaches to the number specified in R_SCI_UART_Read()
 *    if a transfer instance is used for reception.
 *  - UART_EVENT_RX_CHAR: Data is received asynchronously (read has not been called)
 *
 * This interrupt also calls the callback function for RTS pin control if it is registered in R_SCI_UART_Open(). This is
 * special functionality to expand SCI hardware capability and make RTS/CTS hardware flow control possible. If macro
 * 'SCI_UART_CFG_FLOW_CONTROL_SUPPORT' is set, it is called at the beginning in this function to set the RTS pin high,
 * then it is called again just before leaving this function to set the RTS pin low.
 * @retval    none
 **********************************************************************************************************************/
void sci_uart_rxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

 #if SCI_UART_CFG_DTC_SUPPORTED
    if ((p_ctrl->p_cfg->p_transfer_rx == NULL) || (0 == p_ctrl->rx_dest_bytes))
 #endif
    {
 #if (SCI_UART_CFG_FLOW_CONTROL_SUPPORT)
        if (p_ctrl->flow_pin != SCI_UART_INVALID_16BIT_PARAM)
        {
            R_BSP_PinAccessEnable();

            /* Pause the transmission of data from the other device. */
            R_BSP_PinWrite(p_ctrl->flow_pin, SCI_UART_FLOW_CONTROL_ACTIVE);
        }
 #endif

        uint32_t data;
 #if SCI_UART_CFG_FIFO_SUPPORT
        do
        {
            if ((p_ctrl->fifo_depth > 0U))
            {
                if (p_ctrl->p_reg->FDR_b.R > 0U)
                {
                    data = p_ctrl->p_reg->FRDRHL & FRDR_TDAT_MASK_9BITS;
                }
                else
                {
                    break;
                }
            }
            else if (2U == p_ctrl->data_bytes)
 #else
        {
            if (2U == p_ctrl->data_bytes)
 #endif
            {
                data = p_ctrl->p_reg->RDRHL & FRDR_TDAT_MASK_9BITS;
            }
            else
            {
                data = p_ctrl->p_reg->RDR;
            }

            if (0 == p_ctrl->rx_dest_bytes)
            {
                /* If a callback was provided, call it with the argument */
                if (NULL != p_ctrl->p_callback)
                {
                    /* Call user callback with the data. */
                    r_sci_uart_call_callback(p_ctrl, data, UART_EVENT_RX_CHAR);
                }
            }
            else
            {
                memcpy((void *) p_ctrl->p_rx_dest, &data, p_ctrl->data_bytes);
                p_ctrl->p_rx_dest     += p_ctrl->data_bytes;
                p_ctrl->rx_dest_bytes -= p_ctrl->data_bytes;

                if (0 == p_ctrl->rx_dest_bytes)
                {
                    /* If a callback was provided, call it with the argument */
                    if (NULL != p_ctrl->p_callback)
                    {
                        r_sci_uart_call_callback(p_ctrl, 0U, UART_EVENT_RX_COMPLETE);
                    }
                }
            }

 #if SCI_UART_CFG_FIFO_SUPPORT
        } while ((p_ctrl->fifo_depth > 0U) && ((p_ctrl->p_reg->FDR_b.R) > 0U));

        if (p_ctrl->fifo_depth > 0U)
        {
            p_ctrl->p_reg->SSR_FIFO = (uint8_t) ~(SCI_UART_SSR_FIFO_DR_RDF);
        }

 #else
        }
 #endif
 #if (SCI_UART_CFG_FLOW_CONTROL_SUPPORT)
        if (p_ctrl->flow_pin != SCI_UART_INVALID_16BIT_PARAM)
        {
            /* Resume the transmission of data from the other device. */
            R_BSP_PinWrite(p_ctrl->flow_pin, SCI_UART_FLOW_CONTROL_INACTIVE);
            R_BSP_PinAccessDisable();
        }
 #endif
    }

 #if SCI_UART_CFG_DTC_SUPPORTED
    else
    {
        p_ctrl->rx_dest_bytes = 0;

        p_ctrl->p_rx_dest = NULL;

        /* If a callback was provided, call it with the argument */
        if (NULL != p_ctrl->p_callback)
        {
            /* Call callback */
            r_sci_uart_call_callback(p_ctrl, 0U, UART_EVENT_RX_COMPLETE);
        }
    }
 #endif

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#endif

#if (SCI_UART_CFG_TX_ENABLE)

/*******************************************************************************************************************//**
 * TEI interrupt processing for UART mode. The TEI interrupt fires after the last byte is transmitted on the TX pin.
 * The user callback function is called with the UART_EVENT_TX_COMPLETE event code (if it is registered in
 * R_SCI_UART_Open()).
 **********************************************************************************************************************/
void sci_uart_tei_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Receiving TEI(transmit end interrupt) means the completion of transmission, so call callback function here. */
    p_ctrl->p_reg->SCR &= (uint8_t) ~(SCI_SCR_TIE_MASK | SCI_SCR_TEIE_MASK);

    /* Negate driver enable if RS-485 mode is enabled. */
    r_sci_negate_de_pin(p_ctrl);

    /* If a callback was provided, call it with the argument */
    if (NULL != p_ctrl->p_callback)
    {
        r_sci_uart_call_callback(p_ctrl, 0U, UART_EVENT_TX_COMPLETE);
    }

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#endif

#if (SCI_UART_CFG_RX_ENABLE)

/*******************************************************************************************************************//**
 * ERI interrupt processing for UART mode. When an ERI interrupt fires, the user callback function is called if it is
 * registered in R_SCI_UART_Open() with the event code that triggered the interrupt.
 **********************************************************************************************************************/
void sci_uart_eri_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_uart_instance_ctrl_t * p_ctrl = (sci_uart_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    uint32_t     data = 0U;
    uart_event_t event;

    /* Read data. */
    if (
 #if SCI_UART_CFG_FIFO_SUPPORT
        (p_ctrl->fifo_depth > 0U) ||
 #endif
        (2U == p_ctrl->data_bytes))
    {
        {
            data = p_ctrl->p_reg->RDRHL & SCI_UART_FIFO_DAT_MASK;
        }
    }
    else
    {
        data = p_ctrl->p_reg->RDR;
    }

    /* Determine cause of error. */
    event = (uart_event_t) (p_ctrl->p_reg->SSR & SCI_RCVR_ERR_MASK);

    /* Check if there is a break detected. */
    if ((UART_EVENT_ERR_FRAMING == (event & UART_EVENT_ERR_FRAMING)) && (0U == p_ctrl->p_reg->SPTR_b.RXDMON))
    {
        event |= UART_EVENT_BREAK_DETECT;
    }

    /* Clear error condition. */
    p_ctrl->p_reg->SSR &= (uint8_t) (~SCI_RCVR_ERR_MASK);

    /* Negate driver enable if RS-485 mode is enabled. */
    r_sci_negate_de_pin(p_ctrl);

    /* If a callback was provided, call it with the argument */
    if (NULL != p_ctrl->p_callback)
    {
        /* Call callback. */
        r_sci_uart_call_callback(p_ctrl, data, event);
    }

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#endif
