/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef R_SPI_API_H
#define R_SPI_API_H

/*****************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup SPI_API SPI Interface
 * @brief Interface for SPI communications.
 *
 * @section SPI_API_SUMMARY Summary
 * Provides a common interface for communication using the SPI Protocol.
 *
 * Implemented by:
 * - @ref SPI
 * - @ref SCI_SPI
 *
 * @{
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Includes
 ********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"
#include "r_transfer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*********************************************************************************************************************
 * Macro definitions
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Typedef definitions
 ********************************************************************************************************************/

/** Data bit width */
typedef enum e_spi_bit_width
{
    SPI_BIT_WIDTH_4_BITS  = (3),       ///< Data bit width is 4 bits (byte)
    SPI_BIT_WIDTH_5_BITS  = (4),       ///< Data bit width is 5 bits (byte)
    SPI_BIT_WIDTH_6_BITS  = (5),       ///< Data bit width is 6 bits (byte)
    SPI_BIT_WIDTH_7_BITS  = (6),       ///< Data bit width is 7 bits (byte)
    SPI_BIT_WIDTH_8_BITS  = (7),       ///< Data bit width is 8 bits (byte)
    SPI_BIT_WIDTH_9_BITS  = (8),       ///< Data bit width is 9 bits (word)
    SPI_BIT_WIDTH_10_BITS = (9),       ///< Data bit width is 10 bits (word)
    SPI_BIT_WIDTH_11_BITS = (10),      ///< Data bit width is 11 bits (word)
    SPI_BIT_WIDTH_12_BITS = (11),      ///< Data bit width is 12 bits (word)
    SPI_BIT_WIDTH_13_BITS = (12),      ///< Data bit width is 13 bits (word)
    SPI_BIT_WIDTH_14_BITS = (13),      ///< Data bit width is 14 bits (word)
    SPI_BIT_WIDTH_15_BITS = (14),      ///< Data bit width is 15 bits (word)
    SPI_BIT_WIDTH_16_BITS = (15),      ///< Data bit width is 16 bits (word)
    SPI_BIT_WIDTH_17_BITS = (16),      ///< Data bit width is 17 bits (word)
    SPI_BIT_WIDTH_18_BITS = (17),      ///< Data bit width is 18 bits (word)
    SPI_BIT_WIDTH_19_BITS = (18),      ///< Data bit width is 19 bits (word)
    SPI_BIT_WIDTH_20_BITS = (19),      ///< Data bit width is 20 bits (longword)
    SPI_BIT_WIDTH_21_BITS = (20),      ///< Data bit width is 21 bits (word)
    SPI_BIT_WIDTH_22_BITS = (21),      ///< Data bit width is 22 bits (word)
    SPI_BIT_WIDTH_23_BITS = (22),      ///< Data bit width is 23 bits (longword)
    SPI_BIT_WIDTH_24_BITS = (23),      ///< Data bit width is 24 bits (longword)
    SPI_BIT_WIDTH_25_BITS = (25),      ///< Data bit width is 25 bits (longword)
    SPI_BIT_WIDTH_26_BITS = (25),      ///< Data bit width is 26 bits (word)
    SPI_BIT_WIDTH_27_BITS = (26),      ///< Data bit width is 27 bits (word)
    SPI_BIT_WIDTH_28_BITS = (27),      ///< Data bit width is 28 bits (word)
    SPI_BIT_WIDTH_29_BITS = (28),      ///< Data bit width is 29 bits (word)
    SPI_BIT_WIDTH_30_BITS = (29),      ///< Data bit width is 30 bits (longword)
    SPI_BIT_WIDTH_31_BITS = (30),      ///< Data bit width is 31 bits (longword)
    SPI_BIT_WIDTH_32_BITS = (31)       ///< Data bit width is 32 bits (longword)
} spi_bit_width_t;

/** Master or slave operating mode */
typedef enum e_spi_mode
{
    SPI_MODE_MASTER,                   ///< Channel operates as SPI master
    SPI_MODE_SLAVE                     ///< Channel operates as SPI slave
} spi_mode_t;

/** Clock phase */
typedef enum e_spi_clk_phase
{
    SPI_CLK_PHASE_EDGE_ODD,            ///< 0: Data sampling on odd edge, data variation on even edge
    SPI_CLK_PHASE_EDGE_EVEN            ///< 1: Data variation on odd edge, data sampling on even edge
} spi_clk_phase_t;

/** Clock polarity */
typedef enum e_spi_clk_polarity
{
    SPI_CLK_POLARITY_LOW,              ///< 0: Clock polarity is low when idle
    SPI_CLK_POLARITY_HIGH              ///< 1: Clock polarity is high when idle
} spi_clk_polarity_t;

/** Mode fault error flag. This error occurs when the device is setup as a master, but the SSLA line does not seem to be
 *  controlled by the master. This usually happens when the connecting device is also acting as master.
 *  A similar situation can also happen when configured as a slave. */
typedef enum e_spi_mode_fault
{
    SPI_MODE_FAULT_ERROR_ENABLE,       ///< Mode fault error flag on
    SPI_MODE_FAULT_ERROR_DISABLE       ///< Mode fault error flag off
} spi_mode_fault_t;

/** Bit order */
typedef enum e_spi_bit_order
{
    SPI_BIT_ORDER_MSB_FIRST,           ///< Send MSB first in transmission
    SPI_BIT_ORDER_LSB_FIRST            ///< Send LSB first in transmission
} spi_bit_order_t;

/** SPI events */
typedef enum e_spi_event
{
    SPI_EVENT_TRANSFER_COMPLETE = 1,   ///< The data transfer was completed
    SPI_EVENT_TRANSFER_ABORTED,        ///< The data transfer was aborted
    SPI_EVENT_ERR_MODE_FAULT,          ///< Mode fault error
    SPI_EVENT_ERR_READ_OVERFLOW,       ///< Read overflow error
    SPI_EVENT_ERR_PARITY,              ///< Parity error
    SPI_EVENT_ERR_OVERRUN,             ///< Overrun error
    SPI_EVENT_ERR_FRAMING,             ///< Framing error
    SPI_EVENT_ERR_MODE_UNDERRUN        ///< Underrun error
} spi_event_t;

/** Common callback parameter definition */
typedef struct st_spi_callback_args
{
    uint32_t     channel;              ///< Device channel number
    spi_event_t  event;                ///< Event code
    void const * p_context;            ///< Context provided to user during callback
} spi_callback_args_t;

/** Non-secure arguments for write-read guard function */
typedef struct st_spi_write_read_guard_args
{
    void const          * p_src;
    void                * p_dest;
    uint32_t const        length;
    spi_bit_width_t const bit_width;
} spi_write_read_guard_args_t;

/** SPI interface configuration */
typedef struct st_spi_cfg
{
    uint8_t channel;                                   ///< Channel number to be used

    IRQn_Type                   rxi_irq;               ///< Receive Buffer Full IRQ number
    IRQn_Type                   txi_irq;               ///< Transmit Buffer Empty IRQ number
    IRQn_Type                   tei_irq;               ///< Transfer Complete IRQ number
    IRQn_Type                   eri_irq;               ///< Error IRQ number
    uint8_t                     rxi_ipl;               ///< Receive Interrupt priority
    uint8_t                     txi_ipl;               ///< Transmit Interrupt priority
    uint8_t                     tei_ipl;               ///< Transfer Complete Interrupt priority
    uint8_t                     eri_ipl;               ///< Error Interrupt priority
    spi_mode_t                  operating_mode;        ///< Select master or slave operating mode
    spi_clk_phase_t             clk_phase;             ///< Data sampling on odd or even clock edge
    spi_clk_polarity_t          clk_polarity;          ///< Clock level when idle
    spi_mode_fault_t            mode_fault;            ///< Mode fault error (master/slave conflict) flag
    spi_bit_order_t             bit_order;             ///< Select to transmit MSB/LSB first
    transfer_instance_t const * p_transfer_tx;         ///< To use SPI DTC/DMA write transfer, link a DTC/DMA instance here.  Set to NULL if unused.
    transfer_instance_t const * p_transfer_rx;         ///< To use SPI DTC/DMA read transfer, link a DTC/DMA instance here.  Set to NULL if unused.
    void (* p_callback)(spi_callback_args_t * p_args); ///< Pointer to user callback function
    void const * p_context;                            ///< User defined context passed to callback function
    void const * p_extend;                             ///< Extended SPI hardware dependent configuration
} spi_cfg_t;

/** SPI control block.  Allocate an instance specific control block to pass into the SPI API calls.
 * @par Implemented as
 * - spi_instance_ctrl_t
 * - spi_b_instance_ctrl_t
 * - sci_spi_instance_ctrl_t
 */
typedef void spi_ctrl_t;

/** Shared Interface definition for SPI */
typedef struct st_spi_api
{
    /** Initialize a channel for SPI communication mode.
     * @par Implemented as
     * - @ref R_SPI_Open()
     * - @ref R_SPI_B_Open()
     * - @ref R_SCI_SPI_Open()
     *
     * @param[in, out] p_ctrl Pointer to user-provided storage for the control block.
     * @param[in]      p_cfg  Pointer to SPI configuration structure.
     */
    fsp_err_t (* open)(spi_ctrl_t * p_ctrl, spi_cfg_t const * const p_cfg);

    /** Receive data from a SPI device.
     * @par Implemented as
     * - @ref R_SPI_Read()
     * - @ref R_SPI_B_Read()
     * - @ref R_SCI_SPI_Read()
     *
     * @param[in]  p_ctrl    Pointer to the control block for the channel.
     * @param[in]  length    Number of units of data to be transferred (unit size specified by the
     *                       bit_width).
     * @param[in]  bit_width Data bit width to be transferred.
     * @param[out] p_dest    Pointer to destination buffer into which data will be copied that is received from a SPI
     *                       device. It is the responsibility of the caller to ensure that adequate space is available
     *                       to hold the requested data count.
     */
    fsp_err_t (* read)(spi_ctrl_t * const p_ctrl, void * p_dest, uint32_t const length,
                       spi_bit_width_t const bit_width);

    /** Transmit data to a SPI device.
     * @par Implemented as
     * - @ref R_SPI_Write()
     * - @ref R_SPI_B_Write()
     * - @ref R_SCI_SPI_Write()
     *
     * @param[in]  p_ctrl    Pointer to the control block for the channel.
     * @param[in]  p_src     Pointer to a source data buffer from which data will be transmitted to a SPI device.
     *                       The argument must not be NULL.
     * @param[in]  length    Number of units of data to be transferred (unit size specified by the
     *                       bit_width).
     * @param[in]  bit_width Data bit width to be transferred.
     */
    fsp_err_t (* write)(spi_ctrl_t * const p_ctrl, void const * p_src, uint32_t const length,
                        spi_bit_width_t const bit_width);

    /** Simultaneously transmit data to a SPI device while receiving data from a SPI device (full duplex).
     * @par Implemented as
     * - @ref R_SPI_WriteRead()
     * - @ref R_SPI_B_WriteRead()
     * - @ref R_SCI_SPI_WriteRead()
     *
     * @param[in]  p_ctrl    Pointer to the control block for the channel.
     * @param[in]  p_src     Pointer to a source data buffer from which data will be transmitted to a SPI device.
     *                       The argument must not be NULL.
     * @param[out] p_dest    Pointer to destination buffer into which data will be copied that is received from a SPI
     *                       device. It is the responsibility of the caller to ensure that adequate space is available
     *                       to hold the requested data count. The argument must not be NULL.
     * @param[in]  length    Number of units of data to be transferred (unit size specified by the bit_width).
     * @param[in]  bit_width Data bit width to be transferred.
     */
    fsp_err_t (* writeRead)(spi_ctrl_t * const p_ctrl, void const * p_src, void * p_dest, uint32_t const length,
                            spi_bit_width_t const bit_width);

    /**
     * Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - @ref R_SPI_CallbackSet()
     * - @ref R_SPI_B_CallbackSet()
     * - @ref R_SCI_SPI_CallbackSet()
     *
     * @param[in]   p_ctrl                   Pointer to the SPI control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(spi_ctrl_t * const p_api_ctrl, void (* p_callback)(spi_callback_args_t *),
                              void const * const p_context, spi_callback_args_t * const p_callback_memory);

    /** Remove power to the SPI channel designated by the handle and disable the associated interrupts.
     * @par Implemented as
     * - @ref R_SPI_Close()
     * - @ref R_SPI_B_Close()
     * - @ref R_SCI_SPI_Close()
     *
     * @param[in]  p_ctrl  Pointer to the control block for the channel.
     */
    fsp_err_t (* close)(spi_ctrl_t * const p_ctrl);
} spi_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_spi_instance
{
    spi_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    spi_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    spi_api_t const * p_api;           ///< Pointer to the API structure for this instance
} spi_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

/*****************************************************************************************************************//**
 * @} (end defgroup SPI_API)
 ********************************************************************************************************************/

#endif
