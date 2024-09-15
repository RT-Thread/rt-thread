/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_sci_uart.h"
#include <string.h>

#if SCI_UART_CFG_DMAC_SUPPORTED
 #include "r_dmac.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#ifndef SCI_UART_CFG_RX_ENABLE
 #define SCI_UART_CFG_RX_ENABLE             1
#endif
#ifndef SCI_UART_CFG_TX_ENABLE
 #define SCI_UART_CFG_TX_ENABLE             1
#endif

/** Number of divisors in the data table used for baud rate calculation. */
#define SCI_UART_NUM_DIVISORS_ASYNC         (13U)

/** Valid range of values for the modulation duty register is 128 - 256 (256 = modulation disabled). */
#define SCI_UART_MDDR_MIN                   (128U)
#define SCI_UART_MDDR_MAX                   (256U)

/** The bit rate register is 8-bits, so the maximum value is 255. */
#define SCI_UART_BRR_MAX                    (255U)

/** No limit to the number of bytes to read or write if DMAC is not used. */
#define SCI_UART_MAX_READ_WRITE_NO_DMAC     (0xFFFFFFFFU)

/** Mask of invalid data bits in 9-bit mode. */
#define SCI_UART_ALIGN_2_BYTES              (0x1U)

/** Clock frequency 96MHz. */
#define SCI_UART_CLOCK_96MHZ                (96000000)

/** "SCIU" in ASCII.  Used to determine if the control block is open. */
#define SCI_UART_OPEN                       (0x53434955U)

#define SCI_UART_BRR_DEFAULT_VALUE          (0xFFU)
#define SCI_UART_MDDR_DEFAULT_VALUE         (0xFFU)
#define SCI_UART_FCR_DEFAULT_VALUE          (0x1F1F0000)

#define SCI_UART_CCR0_DEFAULT_VALUE         (0x00000000)
#define SCI_UART_CCR1_DEFAULT_VALUE         (0x00000010)
#define SCI_UART_CCR2_DEFAULT_VALUE         (0xFF00FF04)
#define SCI_UART_CCR3_DEFAULT_VALUE         (0x00001203)
#define SCI_UART_CCR4_DEFAULT_VALUE         (0x00000000)

#define SCI_UART_CFCLR_ALL_FLAG_CLEAR       (0xBD070010)
#define SCI_UART_FFCLR_ALL_FLAG_CLEAR       (0x00000001)

/** SCI CCR0 register bit masks */
#define SCI_UART_CCR0_IDSEL_MASK            (0x00000400)
#define SCI_UART_CCR0_TEIE_MASK             (0x00200000)
#define SCI_UART_CCR0_RE_MASK               (0x00000001)
#define SCI_UART_CCR0_TE_MASK               (0x00000010)
#define SCI_UART_CCR0_RIE_MASK              (0x00010000)
#define SCI_UART_CCR0_TIE_MASK              (0x00100000)

/** SCI CCR1 register bit offsets */
#define SCI_UART_CCR1_CTSE_OFFSET           (0U)
#define SCI_UART_CCR1_SPB2DT_BIT            (4U)
#define SCI_UART_CCR1_OUTPUT_ENABLE_MASK    (0x00000020)
#define SCI_UART_CCR1_PARITY_OFFSET         (8U)
#define SCI_UART_CCR1_PARITY_MASK           (0x00000300U)
#define SCI_UART_CCR1_FLOW_CTSRTS_MASK      (0x00000003U)
#define SCI_UART_CCR1_NFCS_OFFSET           (24U)
#define SCI_UART_CCR1_NFCS_VALUE_MASK       (0x07U)
#define SCI_UART_CCR1_NFEN_OFFSET           (28U)

/** SCI CCR2 register bit offsets */
#define SCI_UART_CCR2_BRME_OFFSET           (16U)
#define SCI_UART_CCR2_ABCSE_OFFSET          (6U)
#define SCI_UART_CCR2_ABCS_OFFSET           (5U)
#define SCI_UART_CCR2_BDGM_OFFSET           (4U)
#define SCI_UART_CCR2_CKS_OFFSET            (20U)
#define SCI_UART_CCR2_CKS_VALUE_MASK        (0x03U) ///< CKS: 2 bits
#define SCI_UART_CCR2_BRR_OFFSET            (8U)
#define SCI_UART_CCR2_BRR_VALUE_MASK        (0xFFU) ///< BRR: 8bits
#define SCI_UART_CCR2_MDDR_OFFSET           (24U)
#define SCI_UART_CCR2_MDDR_VALUE_MASK       (0xFFU) ///< MDDR: 8bits

#define SCI_UART_CCR2_BAUD_SETTING_MASK     ((1U << SCI_UART_CCR2_BRME_OFFSET) |                          \
                                             (1U << SCI_UART_CCR2_ABCSE_OFFSET) |                         \
                                             (1U << SCI_UART_CCR2_ABCS_OFFSET) |                          \
                                             (1U << SCI_UART_CCR2_BDGM_OFFSET) |                          \
                                             (SCI_UART_CCR2_CKS_VALUE_MASK << SCI_UART_CCR2_CKS_OFFSET) | \
                                             (SCI_UART_CCR2_BRR_VALUE_MASK << SCI_UART_CCR2_BRR_OFFSET) | \
                                             (SCI_UART_CCR2_MDDR_VALUE_MASK << SCI_UART_CCR2_MDDR_OFFSET))

/** SCI CCR3 register bit masks */
#define SCI_UART_CCR3_BPEN_OFFSET           (7U)
#define SCI_UART_CCR3_CHR_OFFSET            (8U)
#define SCI_UART_CCR3_STP_OFFSET            (14U)
#define SCI_UART_CCR3_RxDSEL_OFFSET         (15U)
#define SCI_UART_CCR3_FM_OFFSET             (20U)
#define SCI_UART_CCR3_CKE_OFFSET            (24U)
#define SCI_UART_CCR3_CKE_MASK              (0x03000000U)
#define SCI_UART_CCR3_CKE_VALUE_MASK        (0x03U)

/** SCI CSR register receiver error bit masks */
#define SCI_UART_CSR_ORER_MASK              (0x01000000)
#define SCI_UART_CSR_FER_MASK               (0x10000000)
#define SCI_UART_CSR_PER_MASK               (0x08000000)
#define SCI_UART_RCVR_ERR_MASK              (SCI_UART_CSR_ORER_MASK | SCI_UART_CSR_FER_MASK | SCI_UART_CSR_PER_MASK)

/** SCI CFCLR register receiver clear error bit masks */
#define SCI_UART_CFCLR_ORERC_MASK           (0x01000000)
#define SCI_UART_CFCLR_FERC_MASK            (0x10000000)
#define SCI_UART_CFCLE_PERC_MASK            (0x08000000)
#define SCI_UART_RCVR_ERRCLR_MASK           (SCI_UART_CFCLR_ORERC_MASK | SCI_UART_CFCLR_FERC_MASK | \
                                             SCI_UART_CFCLE_PERC_MASK)

#define SCI_REG_SIZE                        (R_SCI1_BASE - R_SCI0_BASE)

#define SCI_UART_INVALID_8BIT_PARAM         (0xFFU)
#define SCI_UART_INVALID_16BIT_PARAM        (0xFFFFU)

#define SCI_UART_TDR_9BIT_MASK              (0x1FFU)

#define SCI_UART_FCR_TRIGGER_MASK           (0xF)
#define SCI_UART_FCR_RSTRG_OFFSET           (24U)
#define SCI_UART_FCR_RTRG_OFFSET            (16U)
#define SCI_UART_FCR_TTRG_OFFSET            (8U)
#define SCI_UART_FCR_TTRG_DMAC_VALUE        (0x0F)
#define SCI_UART_FCR_RESET_TX_RX            (0x00808000)

#define SCI_UART_DMAC_MAX_TRANSFER          (0xFFFFFFFFU)

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

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)

static fsp_err_t r_sci_read_write_param_check(sci_uart_instance_ctrl_t const * const p_instance_ctrl,
                                              uint8_t const * const                  addr,
                                              uint32_t const                         bytes);

#endif

static void r_sci_uart_config_set(sci_uart_instance_ctrl_t * const p_instance_ctrl, uart_cfg_t const * const p_cfg);

#if SCI_UART_CFG_DMAC_SUPPORTED
static fsp_err_t r_sci_uart_transfer_configure(sci_uart_instance_ctrl_t * const p_instance_ctrl,
                                               transfer_instance_t const      * p_transfer,
                                               uint32_t                       * p_transfer_reg,
                                               uint32_t                         address);

static fsp_err_t r_sci_uart_transfer_open(sci_uart_instance_ctrl_t * const p_instance_ctrl,
                                          uart_cfg_t const * const         p_cfg);

static void r_sci_uart_transfer_close(sci_uart_instance_ctrl_t * p_instance_ctrl);

#endif

static void r_sci_uart_baud_set(R_SCI0_Type * p_sci_reg, sci_baud_setting_t const * const p_baud_setting);
static void r_sci_uart_call_callback(sci_uart_instance_ctrl_t * p_instance_ctrl, uint32_t data, uart_event_t event);

#if SCI_UART_CFG_FIFO_SUPPORT
static void r_sci_uart_fifo_cfg(sci_uart_instance_ctrl_t * const p_instance_ctrl);

#endif

static void r_sci_irq_cfg(sci_uart_instance_ctrl_t * const p_instance_ctrl, uint8_t const ipl, IRQn_Type const p_irq);

static void r_sci_irqs_cfg(sci_uart_instance_ctrl_t * const p_instance_ctrl, uart_cfg_t const * const p_cfg);

#if (SCI_UART_CFG_TX_ENABLE)
void r_sci_uart_write_no_transfer(sci_uart_instance_ctrl_t * const p_instance_ctrl);

#endif

#if (SCI_UART_CFG_RX_ENABLE)
void r_sci_uart_rxi_read_no_transfer(sci_uart_instance_ctrl_t * const p_instance_ctrl);

static void sci_uart_rxi_common(sci_uart_instance_ctrl_t * p_instance_ctrl);

void sci_uart_rxi_isr(void);

void sci_uart_rx_dmac_callback(sci_uart_instance_ctrl_t * p_instance_ctrl);

void r_sci_uart_read_data(sci_uart_instance_ctrl_t * const p_instance_ctrl, uint32_t * const p_data);

void sci_uart_eri_isr(void);

#endif

#if (SCI_UART_CFG_TX_ENABLE)
static void sci_uart_txi_common(sci_uart_instance_ctrl_t * p_instance_ctrl);

void sci_uart_txi_isr(void);

void sci_uart_tx_dmac_callback(sci_uart_instance_ctrl_t * p_instance_ctrl);

void sci_uart_tei_isr(void);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Name of module used by error logger macro */
#if BSP_CFG_ERROR_LOG != 0
static const char g_module_name[] = "sci_uart";
#endif

/** Baud rate divisor information (UART mode) */
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

/** UART on SCI HAL API mapping for UART interface */
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
 * @retval  FSP_ERR_ALREADY_OPEN           Control block has already been opened or channel is being used by another
 *                                         instance. Call close() then open() to reconfigure.
 * @retval  FSP_ERR_INVALID_ARGUMENT       Invalid input parameter.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::open
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_Open (uart_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg)
{
    sci_uart_instance_ctrl_t * p_instance_ctrl = (sci_uart_instance_ctrl_t *) p_ctrl;

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)

    /* Check parameters. */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_cfg);
    FSP_ASSERT(p_cfg->p_callback);
    FSP_ASSERT(p_cfg->p_extend);
    FSP_ASSERT(((sci_uart_extended_cfg_t *) p_cfg->p_extend)->p_baud_setting);
    FSP_ERROR_RETURN(SCI_UART_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Make sure this channel exists. */
    FSP_ERROR_RETURN(BSP_FEATURE_SCI_CHANNELS & (1U << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

 #if SCI_UART_CFG_DMAC_SUPPORTED
  #if (SCI_UART_CFG_RX_ENABLE)
    if (NULL != p_cfg->p_transfer_rx)
    {
        /* DMAC activation is not available for safety channel. */
        FSP_ERROR_RETURN(BSP_FEATURE_SCI_SAFETY_CHANNEL != p_cfg->channel, FSP_ERR_INVALID_ARGUMENT);
    }
  #endif
  #if (SCI_UART_CFG_TX_ENABLE)
    if (NULL != p_cfg->p_transfer_tx)
    {
        /* DMAC activation is not available for safety channel. */
        FSP_ERROR_RETURN(BSP_FEATURE_SCI_SAFETY_CHANNEL != p_cfg->channel, FSP_ERR_INVALID_ARGUMENT);
    }
  #endif
 #endif

    if (SCI_UART_FLOW_CONTROL_CTSRTS == ((sci_uart_extended_cfg_t *) p_cfg->p_extend)->flow_control)
    {
        FSP_ERROR_RETURN(
            ((sci_uart_extended_cfg_t *) p_cfg->p_extend)->flow_control_pin != (bsp_io_port_pin_t) SCI_UART_INVALID_16BIT_PARAM,
            FSP_ERR_INVALID_ARGUMENT);
    }

    if (SCI_UART_FLOW_CONTROL_HARDWARE_CTSRTS == ((sci_uart_extended_cfg_t *) p_cfg->p_extend)->flow_control)
    {
        FSP_ERROR_RETURN((0U != (((1U << (p_cfg->channel)) & BSP_FEATURE_SCI_UART_CSTPEN_CHANNELS))),
                         FSP_ERR_INVALID_ARGUMENT);
    }

    FSP_ASSERT(UART_PARITY_ZERO != p_cfg->parity);
    FSP_ASSERT(p_cfg->rxi_irq >= 0);
    FSP_ASSERT(p_cfg->txi_irq >= 0);
    FSP_ASSERT(p_cfg->tei_irq >= 0);
    FSP_ASSERT(p_cfg->eri_irq >= 0);
#endif

    p_instance_ctrl->fifo_depth = 0U;
#if SCI_UART_CFG_FIFO_SUPPORT

    /* Check if the channel supports fifo */
    if (BSP_FEATURE_SCI_UART_FIFO_CHANNELS & (1U << p_cfg->channel))
    {
        p_instance_ctrl->fifo_depth = BSP_FEATURE_SCI_UART_FIFO_DEPTH;
    }
#endif

    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;
    sci_uart_extended_cfg_t * p_extend = (sci_uart_extended_cfg_t *) p_cfg->p_extend;

    p_instance_ctrl->data_bytes = 1U;
    if (UART_DATA_BITS_9 == p_cfg->data_bits)
    {
        p_instance_ctrl->data_bytes = 2U;
    }

    /* Configure the interrupts. */
    r_sci_irqs_cfg(p_instance_ctrl, p_cfg);

    /* Enable the SCI channel and reset the registers to their initial state. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_SCI, p_cfg->channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    if (p_cfg->channel != BSP_FEATURE_SCI_SAFETY_CHANNEL)
    {
        /* Non-Safety Peripheral */
        p_instance_ctrl->p_reg =
            (R_SCI0_Type *) ((uint32_t) R_SCI0 + (p_cfg->channel * ((uint32_t) R_SCI1 - (uint32_t) R_SCI0)));
    }
    else
    {
        /* Safety Peripheral */
        p_instance_ctrl->p_reg = (R_SCI0_Type *) BSP_FEATURE_SCI_SAFETY_CHANNEL_BASE_ADDRESS;
    }

#if SCI_UART_CFG_DMAC_SUPPORTED

    /* Configure the transfer interface for transmission and reception if provided. */
    fsp_err_t err = r_sci_uart_transfer_open(p_instance_ctrl, p_cfg);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    p_instance_ctrl->p_reg->CCR0 = SCI_UART_CCR0_DEFAULT_VALUE;
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->CCR0_b.RE, 0);
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->CCR0_b.TE, 0);
    p_instance_ctrl->p_reg->CCR1 = SCI_UART_CCR1_DEFAULT_VALUE;
    p_instance_ctrl->p_reg->CCR2 = SCI_UART_CCR2_DEFAULT_VALUE;
    p_instance_ctrl->p_reg->CCR3 = SCI_UART_CCR3_DEFAULT_VALUE;
    p_instance_ctrl->p_reg->CCR4 = SCI_UART_CCR4_DEFAULT_VALUE;

    /* Set the UART configuration settings provided in ::uart_cfg_t and ::sci_uart_extended_cfg_t. */
    r_sci_uart_config_set(p_instance_ctrl, p_cfg);

    p_instance_ctrl->p_reg->CFCLR = SCI_UART_CFCLR_ALL_FLAG_CLEAR;

#if SCI_UART_CFG_FIFO_SUPPORT
    p_instance_ctrl->p_reg->FFCLR = SCI_UART_FFCLR_ALL_FLAG_CLEAR;
#endif

    p_instance_ctrl->p_tx_src      = NULL;
    p_instance_ctrl->tx_src_bytes  = 0U;
    p_instance_ctrl->p_rx_dest     = NULL;
    p_instance_ctrl->rx_dest_bytes = 0;

    uint32_t ccr0 = SCI_UART_CCR0_IDSEL_MASK;
#if (SCI_UART_CFG_RX_ENABLE)

    /* If reception is enabled at build time, enable reception. */
    /* NOTE: Transmitter and its interrupt are enabled in R_SCI_UART_Write(). */
    R_BSP_IrqEnable(p_instance_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqEnable(p_instance_ctrl->p_cfg->eri_irq);

    ccr0 |= (SCI_UART_CCR0_RIE_MASK | SCI_UART_CCR0_RE_MASK);
#endif

#if (SCI_UART_CFG_TX_ENABLE)
    R_BSP_IrqEnable(p_instance_ctrl->p_cfg->txi_irq);
    R_BSP_IrqEnable(p_instance_ctrl->p_cfg->tei_irq);

    ccr0 |= SCI_UART_CCR0_TE_MASK;
#endif
    p_instance_ctrl->p_reg->CCR0 = ccr0;

    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->CCR0_b.RE, 1);
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->CCR0_b.TE, 1);

    /* Set flow control pins. */
    p_instance_ctrl->flow_pin = p_extend->flow_control_pin;

#if SCI_UART_CFG_FLOW_CONTROL_SUPPORT
    if (p_instance_ctrl->flow_pin != (bsp_io_port_pin_t) SCI_UART_INVALID_16BIT_PARAM)
    {
        R_BSP_PinAccessEnable();
        R_BSP_PinClear(R_BSP_IoRegionGet(p_instance_ctrl->flow_pin), p_instance_ctrl->flow_pin);
        R_BSP_PinAccessDisable();
    }
#endif

    p_instance_ctrl->open = SCI_UART_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Aborts any in progress transfers. Disables interrupts, receiver, and transmitter. Closes lower level transfer
 * drivers if used. Removes power. Implements @ref uart_api_t::close
 *
 * @retval  FSP_SUCCESS              Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION        Pointer to UART control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_Close (uart_ctrl_t * const p_ctrl)
{
    sci_uart_instance_ctrl_t * p_instance_ctrl = (sci_uart_instance_ctrl_t *) p_ctrl;
#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Mark the channel not open so other APIs cannot use it. */
    p_instance_ctrl->open = 0U;

    /* Disable interrupts, receiver, and transmitter. Disable baud clock output.*/
    p_instance_ctrl->p_reg->CCR0 = SCI_UART_CCR0_DEFAULT_VALUE;
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->CCR0_b.RE, 0);
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->CCR0_b.TE, 0);
    p_instance_ctrl->p_reg->CCR3 &= ~(SCI_UART_CCR3_CKE_MASK);

#if (SCI_UART_CFG_RX_ENABLE)

    /* If reception is enabled at build time, disable reception irqs. */
    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->eri_irq);
#endif
#if (SCI_UART_CFG_TX_ENABLE)

    /* If transmission is enabled at build time, disable transmission irqs. */
    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->txi_irq);
    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->tei_irq);
#endif
#if SCI_UART_CFG_DMAC_SUPPORTED

    /* Close the lower level transfer instances. */
    r_sci_uart_transfer_close(p_instance_ctrl);
#endif

    /* Remove power to the channel. */
    /* Disable the clock to the SCI channel. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_STOP(FSP_IP_SCI, p_instance_ctrl->p_cfg->channel);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Receives user specified number of bytes into destination buffer pointer. Implements @ref uart_api_t::read
 *
 * @retval  FSP_SUCCESS                  Data reception successfully ends.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT     Destination address or data size is not valid for 9-bit mode.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_IN_USE               A previous read operation is still in progress.
 * @retval  FSP_ERR_UNSUPPORTED          SCI_UART_CFG_RX_ENABLE is set to 0
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::reconfigure
 *
 * @note If 9-bit data length is specified at R_SCI_UART_Open call, p_dest must be aligned 16-bit boundary.
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_Read (uart_ctrl_t * const p_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
#if (SCI_UART_CFG_RX_ENABLE)
    sci_uart_instance_ctrl_t * p_instance_ctrl = (sci_uart_instance_ctrl_t *) p_ctrl;
    fsp_err_t err = FSP_SUCCESS;

 #if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    err = r_sci_read_write_param_check(p_instance_ctrl, p_dest, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN(0U == p_instance_ctrl->rx_dest_bytes, FSP_ERR_IN_USE);
 #endif

 #if SCI_UART_CFG_DMAC_SUPPORTED

    /* Configure transfer instance to receive the requested number of bytes if transfer is used for reception. */
    if (NULL != p_instance_ctrl->p_cfg->p_transfer_rx)
    {
        p_instance_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->p_dest = (void *) p_dest;
        p_instance_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info->length = bytes;

        /* Disable the corresponding IRQ when transferring using DMAC. */
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->rxi_irq);

        err = p_instance_ctrl->p_cfg->p_transfer_rx->p_api->reconfigure(p_instance_ctrl->p_cfg->p_transfer_rx->p_ctrl,
                                                                        p_instance_ctrl->p_cfg->p_transfer_rx->p_cfg->p_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif

    /* Save the destination address and size for use in rxi_isr. */
    p_instance_ctrl->p_rx_dest     = p_dest;
    p_instance_ctrl->rx_dest_bytes = bytes;

    return err;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
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
 * @retval  FSP_ERR_INVALID_ARGUMENT     Source address or data size is not valid for 9-bit mode.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_IN_USE               A UART transmission is in progress
 * @retval  FSP_ERR_UNSUPPORTED          SCI_UART_CFG_TX_ENABLE is set to 0
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::reconfigure
 *
 * @note If 9-bit data length is specified at R_SCI_UART_Open call, p_src must be aligned on a 16-bit boundary.
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_Write (uart_ctrl_t * const p_ctrl, uint8_t const * const p_src, uint32_t const bytes)
{
#if (SCI_UART_CFG_TX_ENABLE)
    sci_uart_instance_ctrl_t * p_instance_ctrl = (sci_uart_instance_ctrl_t *) p_ctrl;
 #if SCI_UART_CFG_PARAM_CHECKING_ENABLE || SCI_UART_CFG_DMAC_SUPPORTED
    fsp_err_t err = FSP_SUCCESS;
 #endif

 #if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    err = r_sci_read_write_param_check(p_instance_ctrl, p_src, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN(0U == p_instance_ctrl->tx_src_bytes, FSP_ERR_IN_USE);
 #endif

    /* Transmit interrupts must be disabled to start with. */
    p_instance_ctrl->p_reg->CCR0 &= (uint32_t) ~(SCI_UART_CCR0_TIE_MASK | SCI_UART_CCR0_TEIE_MASK);

    p_instance_ctrl->tx_src_bytes = bytes - p_instance_ctrl->data_bytes;
    p_instance_ctrl->p_tx_src     = p_src + p_instance_ctrl->data_bytes;

 #if SCI_UART_CFG_DMAC_SUPPORTED

    /* If a transfer instance is used for transmission, reset the transfer instance to transmit the requested
     * data. */
    if ((NULL != p_instance_ctrl->p_cfg->p_transfer_tx) && p_instance_ctrl->tx_src_bytes)
    {
        uint32_t num_transfers = p_instance_ctrl->tx_src_bytes;
        p_instance_ctrl->tx_src_bytes = 0U;

        p_instance_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->p_src  = (void const *) p_instance_ctrl->p_tx_src;
        p_instance_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info->length = num_transfers;

        /* Disable the corresponding IRQ when transferring using DMAC. */
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->txi_irq);

        err = p_instance_ctrl->p_cfg->p_transfer_tx->p_api->reconfigure(p_instance_ctrl->p_cfg->p_transfer_tx->p_ctrl,
                                                                        p_instance_ctrl->p_cfg->p_transfer_tx->p_cfg->p_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif

    /* Trigger a TXI interrupt. This triggers the transfer instance or a TXI interrupt if the transfer instance is
     * not used. */
    p_instance_ctrl->p_reg->CCR0 |= SCI_UART_CCR0_TIE_MASK;

    /* The first byte is sent from this function to trigger the first TXI event.  This
     * method is used instead of setting TE and TIE at the same time as recommended in the hardware manual to avoid
     * the one frame delay that occurs when the TE bit is set. */
    if (2U == p_instance_ctrl->data_bytes)
    {
        p_instance_ctrl->p_reg->TDR_b.TDAT = (*(uint16_t *) (p_src)) & SCI_UART_TDR_9BIT_MASK;
    }
    else
    {
        p_instance_ctrl->p_reg->TDR_b.TDAT = *(p_src);
    }

 #if SCI_UART_CFG_FIFO_SUPPORT

    /* The behavior of the TDRE flag differs between when FIFO is used and not used.
     * When using FIFO, clear the flag manually to detect the interrupt at the edge. */
    p_instance_ctrl->p_reg->CFCLR_b.TDREC = 1;
 #endif

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
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
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_CallbackSet (uart_ctrl_t * const          p_ctrl,
                                  void (                     * p_callback)(uart_callback_args_t *),
                                  void const * const           p_context,
                                  uart_callback_args_t * const p_callback_memory)
{
    sci_uart_instance_ctrl_t * p_instance_ctrl = (sci_uart_instance_ctrl_t *) p_ctrl;

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_instance_ctrl->p_callback        = p_callback;
    p_instance_ctrl->p_context         = p_context;
    p_instance_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the baud rate using the clock selected in Open. p_baud_setting is a pointer to a sci_baud_setting_t structure.
 * Implements @ref uart_api_t::baudSet
 *
 * @warning This terminates any in-progress transmission.
 *
 * @retval  FSP_SUCCESS                  Baud rate was successfully changed.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL or the UART is not configured to use the
 *                                       internal clock.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_BaudSet (uart_ctrl_t * const p_ctrl, void const * const p_baud_setting)
{
    sci_uart_instance_ctrl_t * p_instance_ctrl = (sci_uart_instance_ctrl_t *) p_ctrl;

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Verify that the On-Chip baud rate generator is currently selected. */
    FSP_ASSERT((p_instance_ctrl->p_reg->CCR3_b.CKE & 0x2) == 0U);
#endif

    /* Save CCR0 configurations except transmit interrupts. Resuming transmission after reconfiguring baud settings is
     * not supported. */
    uint32_t preserved_ccr0 = p_instance_ctrl->p_reg->CCR0 & (uint32_t) ~(R_SCI0_CCR0_TIE_Msk | R_SCI0_CCR0_TEIE_Msk);

    /* Disables transmitter and receiver. This terminates any in-progress transmission. */
    p_instance_ctrl->p_reg->CCR0 = preserved_ccr0 &
                                   (uint32_t) ~(R_SCI0_CCR0_TE_Msk | R_SCI0_CCR0_RE_Msk | R_SCI0_CCR0_RIE_Msk);
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->CCR0_b.RE, 0);
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->CCR0_b.TE, 0);
    p_instance_ctrl->p_tx_src = NULL;

    /* Apply new baud rate register settings. */
    r_sci_uart_baud_set(p_instance_ctrl->p_reg, p_baud_setting);

    /* Restore all settings except transmit interrupts. */
    p_instance_ctrl->p_reg->CCR0 = preserved_ccr0;
    FSP_HARDWARE_REGISTER_WAIT((p_instance_ctrl->p_reg->CCR0 & R_SCI0_CCR0_RE_Msk),
                               (preserved_ccr0 & R_SCI0_CCR0_RE_Msk));
    FSP_HARDWARE_REGISTER_WAIT((p_instance_ctrl->p_reg->CCR0 & R_SCI0_CCR0_TE_Msk),
                               (preserved_ccr0 & R_SCI0_CCR0_TE_Msk));

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
fsp_err_t R_SCI_UART_InfoGet (uart_ctrl_t * const p_ctrl, uart_info_t * const p_info)
{
#if SCI_UART_CFG_PARAM_CHECKING_ENABLE || SCI_UART_CFG_DMAC_SUPPORTED
    sci_uart_instance_ctrl_t * p_instance_ctrl = (sci_uart_instance_ctrl_t *) p_ctrl;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_info);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_info->read_bytes_max  = SCI_UART_MAX_READ_WRITE_NO_DMAC;
    p_info->write_bytes_max = SCI_UART_MAX_READ_WRITE_NO_DMAC;

#if (SCI_UART_CFG_RX_ENABLE)

    /* Store number of bytes that can be read at a time. */
 #if SCI_UART_CFG_DMAC_SUPPORTED
    if (NULL != p_instance_ctrl->p_cfg->p_transfer_rx)
    {
        p_info->read_bytes_max = SCI_UART_DMAC_MAX_TRANSFER;
    }
 #endif
#endif

#if (SCI_UART_CFG_TX_ENABLE)

    /* Store number of bytes that can be written at a time. */
 #if SCI_UART_CFG_DMAC_SUPPORTED
    if (NULL != p_instance_ctrl->p_cfg->p_transfer_tx)
    {
        p_info->write_bytes_max = SCI_UART_DMAC_MAX_TRANSFER;
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
fsp_err_t R_SCI_UART_Abort (uart_ctrl_t * const p_ctrl, uart_dir_t communication_to_abort)
{
    sci_uart_instance_ctrl_t * p_instance_ctrl = (sci_uart_instance_ctrl_t *) p_ctrl;
    fsp_err_t err = FSP_ERR_UNSUPPORTED;

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if (SCI_UART_CFG_TX_ENABLE)
    if (UART_DIR_TX & communication_to_abort)
    {
        err = FSP_SUCCESS;
        p_instance_ctrl->p_reg->CCR0 &= (uint32_t) ~(SCI_UART_CCR0_TIE_MASK | SCI_UART_CCR0_TEIE_MASK);

        /* Make sure no transmission is in progress. */
        FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->CSR_b.TEND, 1U);

 #if SCI_UART_CFG_DMAC_SUPPORTED
        if (NULL != p_instance_ctrl->p_cfg->p_transfer_tx)
        {
            err = p_instance_ctrl->p_cfg->p_transfer_tx->p_api->disable(p_instance_ctrl->p_cfg->p_transfer_tx->p_ctrl);

            /* Now that the transfer using DMAC is finished, enable the corresponding IRQ. */
            R_BSP_IrqEnable(p_instance_ctrl->p_cfg->txi_irq);
        }
 #endif

 #if SCI_UART_CFG_FIFO_SUPPORT
        if (0U != p_instance_ctrl->fifo_depth)
        {
            /* Reset the transmit fifo */
            p_instance_ctrl->p_reg->FCR_b.TFRST = 1U;
        }
 #endif
        p_instance_ctrl->tx_src_bytes = 0U;

        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif
#if (SCI_UART_CFG_RX_ENABLE)
    if (UART_DIR_RX & communication_to_abort)
    {
        err = FSP_SUCCESS;

        p_instance_ctrl->rx_dest_bytes = 0U;

 #if SCI_UART_CFG_DMAC_SUPPORTED
        if (NULL != p_instance_ctrl->p_cfg->p_transfer_rx)
        {
            err = p_instance_ctrl->p_cfg->p_transfer_rx->p_api->disable(p_instance_ctrl->p_cfg->p_transfer_rx->p_ctrl);

            /* Now that the transfer using DMAC is finished, enable the corresponding IRQ. */
            R_BSP_IrqEnable(p_instance_ctrl->p_cfg->rxi_irq);
        }
 #endif

 #if SCI_UART_CFG_FIFO_SUPPORT
        if (0U != p_instance_ctrl->fifo_depth)
        {
            /* Reset the receive fifo */
            p_instance_ctrl->p_reg->FCR_b.RFRST = 1U;
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
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block or remaining_bytes is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_UNSUPPORTED          The requested Abort direction is unsupported.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::disable
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_ReadStop (uart_ctrl_t * const p_ctrl, uint32_t * remaining_bytes)
{
    sci_uart_instance_ctrl_t * p_instance_ctrl = (sci_uart_instance_ctrl_t *) p_ctrl;

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(remaining_bytes);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if (SCI_UART_CFG_RX_ENABLE)
    *remaining_bytes               = p_instance_ctrl->rx_dest_bytes;
    p_instance_ctrl->rx_dest_bytes = 0U;
 #if SCI_UART_CFG_DMAC_SUPPORTED
    if (NULL != p_instance_ctrl->p_cfg->p_transfer_rx)
    {
        fsp_err_t err = p_instance_ctrl->p_cfg->p_transfer_rx->p_api->disable(
            p_instance_ctrl->p_cfg->p_transfer_rx->p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Now that the transfer using DMAC is finished, enable the corresponding IRQ. */
        R_BSP_IrqEnable(p_instance_ctrl->p_cfg->rxi_irq);

        transfer_properties_t transfer_info;
        err = p_instance_ctrl->p_cfg->p_transfer_rx->p_api->infoGet(p_instance_ctrl->p_cfg->p_transfer_rx->p_ctrl,
                                                                    &transfer_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        *remaining_bytes = transfer_info.transfer_length_remaining;
    }
 #endif
 #if SCI_UART_CFG_FIFO_SUPPORT
    if (0U != p_instance_ctrl->fifo_depth)
    {
        /* Reset the receive fifo */
        p_instance_ctrl->p_reg->FCR_b.RFRST = 1U;
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
 * @param[in]  p_baud_target             Baudrate calculation configuration.
 * @param[in]  clock_source              Clock source (PCLKM or SCInASYNCCLK) used for baudrate calculation.
 * @param[out] p_baud_setting            Baud setting information stored here if successful
 *
 * @retval     FSP_SUCCESS               Baud rate is set successfully
 * @retval     FSP_ERR_ASSERTION         Null pointer
 * @retval     FSP_ERR_INVALID_ARGUMENT  Baud rate is '0', error in calculated baud rate is larger than requested
 *                                       max error, or requested max error in baud rate is larger than 15%.
 *                                       Clock source frequency could not be get.
 **********************************************************************************************************************/
fsp_err_t R_SCI_UART_BaudCalculate (sci_uart_baud_calculation_t const * const p_baud_target,
                                    sci_uart_clock_source_t                   clock_source,
                                    sci_baud_setting_t * const                p_baud_setting)
{
#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_baud_target);
    FSP_ASSERT(p_baud_setting);
    FSP_ERROR_RETURN(SCI_UART_MAX_BAUD_RATE_ERROR_X_1000 >= p_baud_target->baud_rate_error_x_1000,
                     FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((0U != p_baud_target->baudrate), FSP_ERR_INVALID_ARGUMENT);
#endif

    p_baud_setting->baudrate_bits_b.brr  = SCI_UART_BRR_MAX;
    p_baud_setting->baudrate_bits_b.brme = 0U;
    p_baud_setting->baudrate_bits_b.mddr = SCI_UART_MDDR_MIN;

    /* Find the best BRR (bit rate register) value.
     *  In table g_async_baud, divisor values are stored for BGDM, ABCS, ABCSE and N values.  Each set of divisors
     *  is tried, and the settings with the lowest bit rate error are stored. The formula to calculate BRR is as
     *  follows and it must be 255 or less:
     *  BRR = (PCLK / (div_coefficient * baud)) - 1
     */
    int32_t  hit_bit_err = SCI_UART_100_PERCENT_X_1000;
    uint32_t hit_mddr    = 0U;
    uint32_t divisor     = 0U;

    uint32_t freq_hz = 0U;
    if (SCI_UART_CLOCK_SOURCE_PCLKM == clock_source)
    {
        freq_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKM);
    }
    else
    {
        freq_hz =
            R_FSP_SystemClockHzGet((fsp_priv_clock_t) ((uint8_t) FSP_PRIV_CLOCK_PCLKSCI0 + (uint8_t) clock_source));
    }

    FSP_ERROR_RETURN(0U != freq_hz, FSP_ERR_INVALID_ARGUMENT);

    for (uint32_t select_16_base_clk_cycles = 0U;
         select_16_base_clk_cycles <= 1U && (hit_bit_err > ((int32_t) p_baud_target->baud_rate_error_x_1000));
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

            divisor = (uint32_t) g_div_coefficient[i] * p_baud_target->baudrate;
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

                    uint32_t mddr = 0U;
                    if (p_baud_target->bitrate_modulation)
                    {
                        /* Calculate the MDDR (M) value if bit rate modulation is enabled,
                         * The formula to calculate MBBR (from the M and N relationship given in the hardware manual) is as follows
                         * and it must be between 128 and 256.
                         * MDDR = ((div_coefficient * baud * 256) * (BRR + 1)) / PCLK */
                        mddr = (uint32_t) err_divisor / (freq_hz / SCI_UART_MDDR_MAX);

                        /* The maximum value that could result from the calculation above is 256, which is a valid MDDR
                         * value, so only the lower bound is checked. */
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
                        p_baud_setting->baudrate_bits_b.bgdm  = g_async_baud[i].bgdm;
                        p_baud_setting->baudrate_bits_b.abcs  = g_async_baud[i].abcs;
                        p_baud_setting->baudrate_bits_b.abcse = g_async_baud[i].abcse;
                        p_baud_setting->baudrate_bits_b.cks   = g_async_baud[i].cks;
                        p_baud_setting->baudrate_bits_b.brr   = (uint8_t) temp_brr;
                        hit_bit_err = bit_err;
                        hit_mddr    = mddr;
                    }

                    if (p_baud_target->bitrate_modulation)
                    {
                        p_baud_setting->baudrate_bits_b.brme = 1U;
                        p_baud_setting->baudrate_bits_b.mddr = (uint8_t) hit_mddr;
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
    FSP_ERROR_RETURN((hit_bit_err <= (int32_t) p_baud_target->baud_rate_error_x_1000), FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SCI_UART)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if (SCI_UART_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * Parameter error check function for read/write.
 *
 * @param[in] p_instance_ctrl Pointer to the control block for the channel
 * @param[in] addr            Pointer to the buffer
 * @param[in] bytes           Number of bytes to read or write
 *
 * @retval  FSP_SUCCESS              No parameter error found
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened
 * @retval  FSP_ERR_ASSERTION        Pointer to UART control block or configuration structure is NULL
 * @retval  FSP_ERR_INVALID_ARGUMENT Address is not aligned to 2-byte boundary or size is the odd number when the data
 *                                   length is 9-bit
 **********************************************************************************************************************/
static fsp_err_t r_sci_read_write_param_check (sci_uart_instance_ctrl_t const * const p_instance_ctrl,
                                               uint8_t const * const                  addr,
                                               uint32_t const                         bytes)
{
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(addr);
    FSP_ASSERT(0U != bytes);
    FSP_ERROR_RETURN(SCI_UART_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    if (2U == p_instance_ctrl->data_bytes)
    {
        /* Do not allow odd buffer address if data length is 9 bits. */
        FSP_ERROR_RETURN((0U == ((uint32_t) addr & SCI_UART_ALIGN_2_BYTES)), FSP_ERR_INVALID_ARGUMENT);

        /* Do not allow odd number of data bytes if data length is 9 bits. */
        FSP_ERROR_RETURN(0U == (bytes % 2U), FSP_ERR_INVALID_ARGUMENT);
    }

    return FSP_SUCCESS;
}

#endif

#if SCI_UART_CFG_DMAC_SUPPORTED

/*******************************************************************************************************************//**
 * Subroutine to apply common UART transfer settings.
 *
 * @param[in]  p_cfg              Pointer to UART specific configuration structure
 * @param[in]  p_transfer         Pointer to transfer instance to configure
 *
 * @retval     FSP_SUCCESS        UART transfer drivers successfully configured
 * @retval     FSP_ERR_ASSERTION  Invalid pointer
 **********************************************************************************************************************/
static fsp_err_t r_sci_uart_transfer_configure (sci_uart_instance_ctrl_t * const p_instance_ctrl,
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

    /* Casting for compatibility with 7 or 8 bit mode. */
    *p_transfer_reg = sci_buffer_address;

    transfer_info_t * p_info = p_transfer->p_cfg->p_info;
    if (UART_DATA_BITS_9 == p_instance_ctrl->p_cfg->data_bits)
    {
        p_info->src_size  = TRANSFER_SIZE_2_BYTE;
        p_info->dest_size = TRANSFER_SIZE_2_BYTE;
    }
    else
    {
        p_info->src_size  = TRANSFER_SIZE_1_BYTE;
        p_info->dest_size = TRANSFER_SIZE_1_BYTE;
    }

    fsp_err_t err = p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

#endif

#if SCI_UART_CFG_DMAC_SUPPORTED

/*******************************************************************************************************************//**
 * Configures UART related transfer drivers (if enabled).
 *
 * @param[in]     p_instance_ctrl  Pointer to UART control structure
 * @param[in]     p_cfg            Pointer to UART specific configuration structure
 *
 * @retval        FSP_SUCCESS        UART transfer drivers successfully configured
 * @retval        FSP_ERR_ASSERTION  Invalid pointer or required interrupt not enabled in vector table
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::open
 **********************************************************************************************************************/
static fsp_err_t r_sci_uart_transfer_open (sci_uart_instance_ctrl_t * const p_instance_ctrl,
                                           uart_cfg_t const * const         p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

 #if (SCI_UART_CFG_RX_ENABLE)

    /* If a transfer instance is used for reception, apply UART specific settings and open the transfer instance. */
    if (NULL != p_cfg->p_transfer_rx)
    {
        transfer_info_t * p_info = p_cfg->p_transfer_rx->p_cfg->p_info;

        p_info->mode           = TRANSFER_MODE_NORMAL;
        p_info->src_addr_mode  = TRANSFER_ADDR_MODE_FIXED;
        p_info->dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;

        err =
            r_sci_uart_transfer_configure(p_instance_ctrl,
                                          p_cfg->p_transfer_rx,
                                          (uint32_t *) &p_info->p_src,
                                          (uint32_t) &(p_instance_ctrl->p_reg->RDR));
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif
 #if (SCI_UART_CFG_TX_ENABLE)

    /* If a transfer instance is used for transmission, apply UART specific settings and open the transfer instance. */
    if (NULL != p_cfg->p_transfer_tx)
    {
        transfer_info_t * p_info = p_cfg->p_transfer_tx->p_cfg->p_info;

        p_info->mode           = TRANSFER_MODE_NORMAL;
        p_info->src_addr_mode  = TRANSFER_ADDR_MODE_INCREMENTED;
        p_info->dest_addr_mode = TRANSFER_ADDR_MODE_FIXED;

        err =
            r_sci_uart_transfer_configure(p_instance_ctrl,
                                          p_cfg->p_transfer_tx,
                                          (uint32_t *) &p_info->p_dest,
                                          (uint32_t) &p_instance_ctrl->p_reg->TDR);

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
 * @param[in]     p_instance_ctrl  Pointer to UART control structure
 * @param[in]     p_cfg            Pointer to UART specific configuration structure
 **********************************************************************************************************************/
static void r_sci_uart_config_set (sci_uart_instance_ctrl_t * const p_instance_ctrl, uart_cfg_t const * const p_cfg)
{
    /* CCR3 register setting. */
    uint32_t ccr3 = SCI_UART_CCR3_DEFAULT_VALUE;

#if SCI_UART_CFG_FIFO_SUPPORT
    ccr3 |= (1U << SCI_UART_CCR3_FM_OFFSET);

    /* Configure FIFO related registers. */
    r_sci_uart_fifo_cfg(p_instance_ctrl);
#else

    /* If fifo support is disabled and the current channel supports fifo make sure it's disabled. */
    if (BSP_FEATURE_SCI_UART_FIFO_CHANNELS & (1U << p_cfg->channel))
    {
        p_instance_ctrl->p_reg->FCR = SCI_UART_FCR_DEFAULT_VALUE;
    }
#endif

    /* Configure data size. */
    if (UART_DATA_BITS_7 == p_cfg->data_bits)
    {
        ccr3 |= (1U << SCI_UART_CCR3_CHR_OFFSET);
    }
    else if (UART_DATA_BITS_9 == p_cfg->data_bits)
    {
        ccr3 &= ~(1U << (SCI_UART_CCR3_CHR_OFFSET + 1));
    }
    else
    {
        /* Do nothing.  Default is 8-bit mode. */
    }

    /* Configure stop bits. */
    ccr3 |= (uint32_t) p_cfg->stop_bits << SCI_UART_CCR3_STP_OFFSET;

    /* Configure CKE bits. */
    sci_uart_extended_cfg_t * p_extend = (sci_uart_extended_cfg_t *) p_cfg->p_extend;
    ccr3 |= (p_extend->clock & SCI_UART_CCR3_CKE_VALUE_MASK) << SCI_UART_CCR3_CKE_OFFSET;

    /* Starts reception on falling edge of RXD if enabled in extension (otherwise reception starts at low level
     * of RXD). */
    ccr3 |= (p_extend->rx_edge_start & 1U) << SCI_UART_CCR3_RxDSEL_OFFSET;

    ccr3 |= ((uint32_t) p_extend->rs485_setting.enable << R_SCI0_CCR3_DEN_Pos) & R_SCI0_CCR3_DEN_Msk;

    /* Configure SPEN bit. */
    if (SCI_UART_CLOCK_SOURCE_PCLKM == p_extend->clock_source)
    {
        ccr3 |= 1U << SCI_UART_CCR3_BPEN_OFFSET;
    }

    /* Write to the CCR3 register. */
    p_instance_ctrl->p_reg->CCR3 = ccr3;

    /* CCR1 register setting. */
    uint32_t ccr1 = SCI_UART_CCR1_DEFAULT_VALUE;

    /* Configure flow control pin. */
    ccr1 |= ((uint32_t) (p_extend->flow_control << R_SCI0_CCR1_CTSE_Pos) & SCI_UART_CCR1_FLOW_CTSRTS_MASK);

    /* Set the default level of the TX pin to 1. */
    ccr1 |= (uint32_t) (1U << SCI_UART_CCR1_SPB2DT_BIT | SCI_UART_CCR1_OUTPUT_ENABLE_MASK);

    /* Configure parity bits. */
    if (0 != p_cfg->parity)
    {
        ccr1 |=
            (((UART_PARITY_EVEN ==
               p_cfg->parity) ? 1U : 3U) << SCI_UART_CCR1_PARITY_OFFSET) & SCI_UART_CCR1_PARITY_MASK;
    }

    if (SCI_UART_NOISE_CANCELLATION_DISABLE != p_extend->noise_cancel)
    {
        /* Select noise filter clock */
        ccr1 |= (uint32_t) (((p_extend->noise_cancel & 0x07U) - 1) & SCI_UART_CCR1_NFCS_VALUE_MASK) <<
                SCI_UART_CCR1_NFCS_OFFSET;

        /* Enables the noise cancellation */
        ccr1 |= (uint32_t) 1 << SCI_UART_CCR1_NFEN_OFFSET;
    }

    p_instance_ctrl->p_reg->CCR1 = ccr1;

    if ((SCI_UART_CLOCK_EXT8X == p_extend->clock) || (SCI_UART_CLOCK_EXT16X == p_extend->clock))
    {
        /* Use external clock for baud rate */
        p_instance_ctrl->p_reg->CCR2_b.BRR = SCI_UART_BRR_DEFAULT_VALUE;

        if (SCI_UART_CLOCK_EXT8X == p_extend->clock)
        {
            /* Set baud rate as (external clock / 8) */
            p_instance_ctrl->p_reg->CCR2 |= 1U << SCI_UART_CCR2_ABCS_OFFSET;
        }
    }
    else
    {
        /* Set the baud rate settings for the internal baud rate generator. */
        r_sci_uart_baud_set(p_instance_ctrl->p_reg, p_extend->p_baud_setting);
    }

    /* Configure RS-485 DE assertion settings. */
    uint32_t dcr = ((uint32_t) (p_extend->rs485_setting.polarity << R_SCI0_DCR_DEPOL_Pos)) & R_SCI0_DCR_DEPOL_Msk;
    dcr |= ((uint32_t) p_extend->rs485_setting.assertion_time << R_SCI0_DCR_DEAST_Pos) &
           R_SCI0_DCR_DEAST_Msk;
    dcr |= ((uint32_t) p_extend->rs485_setting.negation_time << R_SCI0_DCR_DENGT_Pos) &
           R_SCI0_DCR_DENGT_Msk;
    p_instance_ctrl->p_reg->DCR = dcr;
}

#if SCI_UART_CFG_FIFO_SUPPORT

/*******************************************************************************************************************//**
 * Resets FIFO related registers.
 *
 * @param[in] p_instance_ctrl  Pointer to UART instance control
 * @param[in] p_cfg            Pointer to UART configuration structure
 **********************************************************************************************************************/
static void r_sci_uart_fifo_cfg (sci_uart_instance_ctrl_t * const p_instance_ctrl)
{
    if (0U != p_instance_ctrl->fifo_depth)
    {
        /* Set the tx and rx reset bits */
        uint32_t fcr = 0U;

 #if (SCI_UART_CFG_TX_ENABLE)
  #if SCI_UART_CFG_DMAC_SUPPORTED
        if (NULL != p_instance_ctrl->p_cfg->p_transfer_tx)
        {
            /* When DMAC transfer is used, set TTRG[4:0] = 0x0F. */
            fcr |= SCI_UART_FCR_TTRG_DMAC_VALUE << SCI_UART_FCR_TTRG_OFFSET;
        }
  #endif
 #endif

 #if (SCI_UART_CFG_RX_ENABLE)
  #if SCI_UART_CFG_DMAC_SUPPORTED

        /* If DMAC is used keep the receive trigger at the default level of 0. */
        if (NULL == p_instance_ctrl->p_cfg->p_transfer_rx)
  #endif
        {
            /* Otherwise, set receive trigger number as configured by the user. */
            sci_uart_extended_cfg_t const * p_extend = p_instance_ctrl->p_cfg->p_extend;

            /* RTRG(Receive FIFO Data Trigger Number) controls when the RXI interrupt will be generated. If data is
             * received but the trigger number is not met the RXI interrupt will be generated after 15 ETUs from
             * the last stop bit in asynchronous mode. */
            fcr |= (((p_instance_ctrl->fifo_depth - 1U) & p_extend->rx_fifo_trigger) & SCI_UART_FCR_TRIGGER_MASK) <<
                   SCI_UART_FCR_RTRG_OFFSET;
        }

        /* RTS asserts when the amount of received data stored in the fifo is equal or less than this value. */
        fcr |= ((p_instance_ctrl->fifo_depth - 1U) & SCI_UART_FCR_TRIGGER_MASK) << SCI_UART_FCR_RSTRG_OFFSET;
 #endif

        /* Set the FCR and reset the fifos. */
        p_instance_ctrl->p_reg->FCR = (uint32_t) (fcr | SCI_UART_FCR_RESET_TX_RX);
    }
}

#endif

/*******************************************************************************************************************//**
 * Sets interrupt priority and initializes vector info.
 *
 * @param[in]  p_instance_ctrl           Pointer to driver control block
 * @param[in]  ipl                       Interrupt priority level
 * @param[in]  irq                       IRQ number for this interrupt
 **********************************************************************************************************************/
static void r_sci_irq_cfg (sci_uart_instance_ctrl_t * const p_instance_ctrl, uint8_t const ipl, IRQn_Type const irq)
{
    /* Disable interrupts, set priority, and store control block in the vector information so it can be accessed
     * from the callback. */
    R_BSP_IrqDisable(irq);

    R_BSP_IrqCfg(irq, ipl, p_instance_ctrl);
}

/*******************************************************************************************************************//**
 * Sets interrupt priority and initializes vector info for all interrupts.
 *
 * @param[in]  p_instance_ctrl           Pointer to UART instance control block
 * @param[in]  p_cfg                     Pointer to UART specific configuration structure
 **********************************************************************************************************************/
static void r_sci_irqs_cfg (sci_uart_instance_ctrl_t * const p_instance_ctrl, uart_cfg_t const * const p_cfg)
{
#if (SCI_UART_CFG_RX_ENABLE)

    /* ERI is optional. */
    r_sci_irq_cfg(p_instance_ctrl, p_cfg->eri_ipl, p_cfg->eri_irq);
    r_sci_irq_cfg(p_instance_ctrl, p_cfg->rxi_ipl, p_cfg->rxi_irq);
#endif
#if (SCI_UART_CFG_TX_ENABLE)
    r_sci_irq_cfg(p_instance_ctrl, p_cfg->txi_ipl, p_cfg->txi_irq);

    r_sci_irq_cfg(p_instance_ctrl, p_cfg->tei_ipl, p_cfg->tei_irq);
#endif
}

#if SCI_UART_CFG_DMAC_SUPPORTED

/*******************************************************************************************************************//**
 * Closes transfer interfaces.
 *
 * @param[in]     p_instance_ctrl     Pointer to UART instance control block
 **********************************************************************************************************************/
static void r_sci_uart_transfer_close (sci_uart_instance_ctrl_t * p_instance_ctrl)
{
 #if (SCI_UART_CFG_RX_ENABLE)
    if (NULL != p_instance_ctrl->p_cfg->p_transfer_rx)
    {
        p_instance_ctrl->p_cfg->p_transfer_rx->p_api->close(p_instance_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }
 #endif
 #if (SCI_UART_CFG_TX_ENABLE)
    if (NULL != p_instance_ctrl->p_cfg->p_transfer_tx)
    {
        p_instance_ctrl->p_cfg->p_transfer_tx->p_api->close(p_instance_ctrl->p_cfg->p_transfer_tx->p_ctrl);
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
static void r_sci_uart_baud_set (R_SCI0_Type * p_sci_reg, sci_baud_setting_t const * const p_baud_setting)
{
    p_sci_reg->CCR2 = (uint32_t) ((p_sci_reg->CCR2 & ~(SCI_UART_CCR2_BAUD_SETTING_MASK)) |
                                  (p_baud_setting->baudrate_bits & SCI_UART_CCR2_BAUD_SETTING_MASK));
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_instance_ctrl     Pointer to UART instance control block
 * @param[in]     data                See uart_callback_args_t in r_uart_api.h
 * @param[in]     event               Event code
 **********************************************************************************************************************/
static void r_sci_uart_call_callback (sci_uart_instance_ctrl_t * p_instance_ctrl, uint32_t data, uart_event_t event)
{
    uart_callback_args_t args;

    /* Store callback arguments in memory provided by user if available. */
    uart_callback_args_t * p_args = p_instance_ctrl->p_callback_memory;
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

    p_args->channel   = p_instance_ctrl->p_cfg->channel;
    p_args->data      = data;
    p_args->event     = event;
    p_args->p_context = p_instance_ctrl->p_context;

    p_instance_ctrl->p_callback(p_args);

    if (NULL != p_instance_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_instance_ctrl->p_callback_memory = args;
    }
}

#if (SCI_UART_CFG_TX_ENABLE)

/*******************************************************************************************************************//**
 * Common processing for TXI interrupt and DMA transfer completion interrupt in UART write mode. This function writes
 * the next data. After the last data byte is written, this function disables the TXI interrupt and enables the TEI
 * (transmit end) interrupt.
 **********************************************************************************************************************/
static void sci_uart_txi_common (sci_uart_instance_ctrl_t * p_instance_ctrl)
{
    if ((NULL == p_instance_ctrl->p_cfg->p_transfer_tx) && (0U != p_instance_ctrl->tx_src_bytes))
    {
        if (2U == p_instance_ctrl->data_bytes)
        {
            p_instance_ctrl->p_reg->TDR_b.TDAT = (*(uint16_t *) (p_instance_ctrl->p_tx_src)) & SCI_UART_TDR_9BIT_MASK;
        }
        else
        {
            p_instance_ctrl->p_reg->TDR_b.TDAT = *(p_instance_ctrl->p_tx_src);
        }

        /* Update pointer to the next data and number of remaining bytes in the control block. */
        p_instance_ctrl->tx_src_bytes -= p_instance_ctrl->data_bytes;
        p_instance_ctrl->p_tx_src     += p_instance_ctrl->data_bytes;

        /* If transfer is not used, write data until FIFO is full. */
 #if SCI_UART_CFG_FIFO_SUPPORT
        if (0U != p_instance_ctrl->fifo_depth)
        {
            uint32_t fifo_count = p_instance_ctrl->p_reg->FTSR_b.T;
            for (uint32_t cnt = fifo_count; (cnt < p_instance_ctrl->fifo_depth) && p_instance_ctrl->tx_src_bytes; cnt++)
            {
                if (2U == p_instance_ctrl->data_bytes)
                {
                    p_instance_ctrl->p_reg->TDR_b.TDAT = (*(uint16_t *) (p_instance_ctrl->p_tx_src)) &
                                                         SCI_UART_TDR_9BIT_MASK;
                }
                else
                {
                    p_instance_ctrl->p_reg->TDR_b.TDAT = *(p_instance_ctrl->p_tx_src);
                }

                p_instance_ctrl->tx_src_bytes -= p_instance_ctrl->data_bytes;
                p_instance_ctrl->p_tx_src     += p_instance_ctrl->data_bytes;
            }

            /* Clear TDRE flag */
            p_instance_ctrl->p_reg->CFCLR_b.TDREC = 1;
        }
 #endif
    }

    if (0U == p_instance_ctrl->tx_src_bytes)
    {
        /* After all data has been transmitted, disable transmit interrupts and enable the transmit end interrupt. */
        uint32_t ccr0_temp = p_instance_ctrl->p_reg->CCR0;
        ccr0_temp |= SCI_UART_CCR0_TEIE_MASK;
        ccr0_temp &= (uint32_t) ~SCI_UART_CCR0_TIE_MASK;
        p_instance_ctrl->p_reg->CCR0 = ccr0_temp;

        p_instance_ctrl->p_tx_src = NULL;
        r_sci_uart_call_callback(p_instance_ctrl, 0U, UART_EVENT_TX_DATA_EMPTY);
    }
}

/*******************************************************************************************************************//**
 * TXI interrupt handler for UART mode. TXI interrupt fires when the data in the data register or FIFO register has been
 * transferred to the data shift register, and the next data can be written. This function calls sci_uart_txi_common().
 **********************************************************************************************************************/
void sci_uart_txi_isr (void)
{
    SCI_UART_CFG_MULTIPLEX_INTERRUPT_ENABLE;

    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_uart_instance_ctrl_t * p_instance_ctrl = (sci_uart_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    sci_uart_txi_common(p_instance_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;

    SCI_UART_CFG_MULTIPLEX_INTERRUPT_DISABLE;
}

/*******************************************************************************************************************//**
 * Callback that must be called after a TX DMAC transfer completes.
 *
 * @param[in]     p_instance_ctrl     Pointer to SCI_UART instance control block
 **********************************************************************************************************************/
void sci_uart_tx_dmac_callback (sci_uart_instance_ctrl_t * p_instance_ctrl)
{
    SCI_UART_CFG_MULTIPLEX_INTERRUPT_ENABLE;

    /* Now that the transfer using DMAC is finished, enable the corresponding IRQ. */
    R_BSP_IrqEnable(p_instance_ctrl->p_cfg->txi_irq);

    sci_uart_txi_common(p_instance_ctrl);

    SCI_UART_CFG_MULTIPLEX_INTERRUPT_DISABLE;
}

#endif

#if (SCI_UART_CFG_RX_ENABLE)

/*******************************************************************************************************************//**
 * Common processing for RXI interrupt and DMA transfer completion interrupt in UART read mode. This function calls
 * callback function when it meets conditions below.
 *  - UART_EVENT_RX_COMPLETE: The number of data which has been read reaches to the number specified in R_SCI_UART_Read()
 *    if a transfer instance is used for reception.
 *  - UART_EVENT_RX_CHAR: Data is received asynchronously (read has not been called)
 *
 * This function also calls the callback function for RTS pin control if it is registered in R_SCI_UART_Open(). This is
 * special functionality to expand SCI hardware capability and make RTS/CTS hardware flow control possible. If macro
 * 'SCI_UART_CFG_FLOW_CONTROL_SUPPORT' is set, it is called at the beginning in this function to set the RTS pin high,
 * then it is called again just before leaving this function to set the RTS pin low.
 * @retval    none
 **********************************************************************************************************************/
static void sci_uart_rxi_common (sci_uart_instance_ctrl_t * p_instance_ctrl)
{
 #if SCI_UART_CFG_DMAC_SUPPORTED
    if ((p_instance_ctrl->p_cfg->p_transfer_rx == NULL) || (0 == p_instance_ctrl->rx_dest_bytes))
 #endif
    {
 #if (SCI_UART_CFG_FLOW_CONTROL_SUPPORT)
        if (p_instance_ctrl->flow_pin != (bsp_io_port_pin_t) SCI_UART_INVALID_16BIT_PARAM)
        {
            R_BSP_PinAccessEnable();

            /* Pause the transmission of data from the other device. */
            R_BSP_PinSet(R_BSP_IoRegionGet(p_instance_ctrl->flow_pin), p_instance_ctrl->flow_pin);
        }
 #endif

        uint32_t data;
 #if SCI_UART_CFG_FIFO_SUPPORT
        do
        {
            if ((p_instance_ctrl->fifo_depth > 0U))
            {
                if (p_instance_ctrl->p_reg->FRSR_b.R > 0U)
                {
                    data = p_instance_ctrl->p_reg->RDR_b.RDAT;
                }
                else
                {
                    break;
                }
            }
            else
            {
                data = p_instance_ctrl->p_reg->RDR_b.RDAT;
            }

 #else
        {
            data = p_instance_ctrl->p_reg->RDR_b.RDAT;
 #endif
            if (0 == p_instance_ctrl->rx_dest_bytes)
            {
                /* Call user callback with the data. */
                r_sci_uart_call_callback(p_instance_ctrl, data, UART_EVENT_RX_CHAR);
            }
            else
            {
                memcpy((void *) p_instance_ctrl->p_rx_dest, &data, p_instance_ctrl->data_bytes);
                p_instance_ctrl->p_rx_dest     += p_instance_ctrl->data_bytes;
                p_instance_ctrl->rx_dest_bytes -= p_instance_ctrl->data_bytes;

                if (0 == p_instance_ctrl->rx_dest_bytes)
                {
                    r_sci_uart_call_callback(p_instance_ctrl, 0U, UART_EVENT_RX_COMPLETE);
                }
            }

 #if SCI_UART_CFG_FIFO_SUPPORT
        } while ((p_instance_ctrl->fifo_depth > 0U) && ((p_instance_ctrl->p_reg->FRSR_b.R) > 0U));

        if (p_instance_ctrl->fifo_depth > 0U)
        {
            p_instance_ctrl->p_reg->CFCLR_b.RDRFC = 1;
        }

 #else
        }
 #endif
 #if (SCI_UART_CFG_FLOW_CONTROL_SUPPORT)
        if (p_instance_ctrl->flow_pin != (bsp_io_port_pin_t) SCI_UART_INVALID_16BIT_PARAM)
        {
            /* Resume the transmission of data from the other device. */
            R_BSP_PinClear(R_BSP_IoRegionGet(p_instance_ctrl->flow_pin), p_instance_ctrl->flow_pin);
            R_BSP_PinAccessDisable();
        }
 #endif
    }

 #if SCI_UART_CFG_DMAC_SUPPORTED
    else
    {
        p_instance_ctrl->rx_dest_bytes = 0;
        p_instance_ctrl->p_rx_dest     = NULL;

        /* Call callback */
        r_sci_uart_call_callback(p_instance_ctrl, 0U, UART_EVENT_RX_COMPLETE);
    }
 #endif
}

/*******************************************************************************************************************//**
 * RXI interrupt handler for UART mode. RXI interrupt happens when data arrives to the data register or the FIFO
 * register. This function calls sci_uart_rxi_common().
 **********************************************************************************************************************/
void sci_uart_rxi_isr (void)
{
    SCI_UART_CFG_MULTIPLEX_INTERRUPT_ENABLE;

    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_uart_instance_ctrl_t * p_instance_ctrl = (sci_uart_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    sci_uart_rxi_common(p_instance_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;

    SCI_UART_CFG_MULTIPLEX_INTERRUPT_DISABLE;
}

/*******************************************************************************************************************//**
 * Callback that must be called after a RX DMAC transfer completes.
 *
 * @param[in]     p_instance_ctrl     Pointer to SCI_UART instance control block
 **********************************************************************************************************************/
void sci_uart_rx_dmac_callback (sci_uart_instance_ctrl_t * p_instance_ctrl)
{
    SCI_UART_CFG_MULTIPLEX_INTERRUPT_ENABLE;

    /* Now that the transfer using DMAC is finished, enable the corresponding IRQ. */
    R_BSP_IrqEnable(p_instance_ctrl->p_cfg->rxi_irq);

    sci_uart_rxi_common(p_instance_ctrl);

    SCI_UART_CFG_MULTIPLEX_INTERRUPT_DISABLE;
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
    SCI_UART_CFG_MULTIPLEX_INTERRUPT_ENABLE;

    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_uart_instance_ctrl_t * p_instance_ctrl = (sci_uart_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Receiving TEI(transmit end interrupt) means the completion of transmission, so call callback function here. */
    p_instance_ctrl->p_reg->CCR0 &= (uint32_t) ~(SCI_UART_CCR0_TIE_MASK | SCI_UART_CCR0_TEIE_MASK);

    /* Dummy read to ensure that interrupts are disabled. */
    volatile uint32_t dummy = p_instance_ctrl->p_reg->CCR0;
    FSP_PARAMETER_NOT_USED(dummy);

    r_sci_uart_call_callback(p_instance_ctrl, 0U, UART_EVENT_TX_COMPLETE);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;

    SCI_UART_CFG_MULTIPLEX_INTERRUPT_DISABLE;
}

#endif

#if (SCI_UART_CFG_RX_ENABLE)

/*******************************************************************************************************************//**
 * ERI interrupt processing for UART mode. When an ERI interrupt fires, the user callback function is called if it is
 * registered in R_SCI_UART_Open() with the event code that triggered the interrupt.
 **********************************************************************************************************************/
void sci_uart_eri_isr (void)
{
    SCI_UART_CFG_MULTIPLEX_INTERRUPT_ENABLE;

    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_uart_instance_ctrl_t * p_instance_ctrl = (sci_uart_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    uint32_t     data  = 0U;
    uart_event_t event = (uart_event_t) 0U;

    /* Read data. */
    data = p_instance_ctrl->p_reg->RDR_b.RDAT;

    /* Determine cause of error. */
    uint32_t csr = p_instance_ctrl->p_reg->CSR & SCI_UART_RCVR_ERR_MASK;

    if (csr & SCI_UART_CSR_ORER_MASK)
    {
        event |= UART_EVENT_ERR_OVERFLOW;
    }

    if (csr & SCI_UART_CSR_FER_MASK)
    {
        event |= UART_EVENT_ERR_FRAMING;
    }

    if (csr & SCI_UART_CSR_PER_MASK)
    {
        event |= UART_EVENT_ERR_PARITY;
    }

    /* Check if there is a break detected. */
    if ((UART_EVENT_ERR_FRAMING == (event & UART_EVENT_ERR_FRAMING)) && (0U == p_instance_ctrl->p_reg->CSR_b.RXDMON))
    {
        event |= UART_EVENT_BREAK_DETECT;
    }

    /* Clear error condition. */
    p_instance_ctrl->p_reg->CFCLR |= (uint32_t) (SCI_UART_RCVR_ERRCLR_MASK);

    /* Dummy read to ensure that interrupt event is cleared. */
    volatile uint32_t dummy = p_instance_ctrl->p_reg->CSR;
    FSP_PARAMETER_NOT_USED(dummy);

    /* Call callback. */
    r_sci_uart_call_callback(p_instance_ctrl, data, event);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;

    SCI_UART_CFG_MULTIPLEX_INTERRUPT_DISABLE;
}

#endif
