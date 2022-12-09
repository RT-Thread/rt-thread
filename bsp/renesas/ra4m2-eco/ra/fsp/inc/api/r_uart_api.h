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

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup UART_API UART Interface
 * @brief Interface for UART communications.
 *
 * @section UART_INTERFACE_SUMMARY Summary
 * The UART interface provides common APIs for UART HAL drivers. The UART interface supports the following features:
 * - Full-duplex UART communication
 * - Interrupt driven transmit/receive processing
 * - Callback function with returned event code
 * - Runtime baud-rate change
 * - Hardware resource locking during a transaction
 * - CTS/RTS hardware flow control support (with an associated IOPORT pin)
 *
 * Implemented by:
 * - @ref SCI_UART
 * - @ref SCI_B_UART
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_UART_API_H
#define R_UART_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"
#include "r_transfer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** UART Event codes */
typedef enum e_sf_event
{
    UART_EVENT_RX_COMPLETE   = (1UL << 0), ///< Receive complete event
    UART_EVENT_TX_COMPLETE   = (1UL << 1), ///< Transmit complete event
    UART_EVENT_RX_CHAR       = (1UL << 2), ///< Character received
    UART_EVENT_ERR_PARITY    = (1UL << 3), ///< Parity error event
    UART_EVENT_ERR_FRAMING   = (1UL << 4), ///< Mode fault error event
    UART_EVENT_ERR_OVERFLOW  = (1UL << 5), ///< FIFO Overflow error event
    UART_EVENT_BREAK_DETECT  = (1UL << 6), ///< Break detect error event
    UART_EVENT_TX_DATA_EMPTY = (1UL << 7), ///< Last byte is transmitting, ready for more data
} uart_event_t;

/** UART Data bit length definition */
typedef enum e_uart_data_bits
{
    UART_DATA_BITS_9 = 0U,             ///< Data bits 9-bit
    UART_DATA_BITS_8 = 2U,             ///< Data bits 8-bit
    UART_DATA_BITS_7 = 3U,             ///< Data bits 7-bit
} uart_data_bits_t;

/** UART Parity definition */
typedef enum e_uart_parity
{
    UART_PARITY_OFF  = 0U,             ///< No parity
    UART_PARITY_EVEN = 2U,             ///< Even parity
    UART_PARITY_ODD  = 3U,             ///< Odd parity
} uart_parity_t;

/** UART Stop bits definition */
typedef enum e_uart_stop_bits
{
    UART_STOP_BITS_1 = 0U,             ///< Stop bit 1-bit
    UART_STOP_BITS_2 = 1U,             ///< Stop bits 2-bit
} uart_stop_bits_t;

/** UART transaction definition */
typedef enum e_uart_dir
{
    UART_DIR_RX_TX = 3U,               ///< Both RX and TX
    UART_DIR_RX    = 1U,               ///< Only RX
    UART_DIR_TX    = 2U,               ///< Only TX
} uart_dir_t;

/** UART driver specific information */
typedef struct st_uart_info
{
    /** Maximum bytes that can be written at this time.  Only applies if uart_cfg_t::p_transfer_tx is not NULL. */
    uint32_t write_bytes_max;

    /** Maximum bytes that are available to read at one time.  Only applies if uart_cfg_t::p_transfer_rx is not NULL. */
    uint32_t read_bytes_max;
} uart_info_t;

/** UART Callback parameter definition */
typedef struct st_uart_callback_arg
{
    uint32_t     channel;              ///< Device channel number
    uart_event_t event;                ///< Event code

    /** Contains the next character received for the events UART_EVENT_RX_CHAR, UART_EVENT_ERR_PARITY,
     * UART_EVENT_ERR_FRAMING, or UART_EVENT_ERR_OVERFLOW.  Otherwise unused. */
    uint32_t     data;
    void const * p_context;            ///< Context provided to user during callback
} uart_callback_args_t;

/** UART Configuration */
typedef struct st_uart_cfg
{
    /* UART generic configuration */
    uint8_t          channel;          ///< Select a channel corresponding to the channel number of the hardware.
    uart_data_bits_t data_bits;        ///< Data bit length (8 or 7 or 9)
    uart_parity_t    parity;           ///< Parity type (none or odd or even)
    uart_stop_bits_t stop_bits;        ///< Stop bit length (1 or 2)
    uint8_t          rxi_ipl;          ///< Receive interrupt priority
    IRQn_Type        rxi_irq;          ///< Receive interrupt IRQ number
    uint8_t          txi_ipl;          ///< Transmit interrupt priority
    IRQn_Type        txi_irq;          ///< Transmit interrupt IRQ number
    uint8_t          tei_ipl;          ///< Transmit end interrupt priority
    IRQn_Type        tei_irq;          ///< Transmit end interrupt IRQ number
    uint8_t          eri_ipl;          ///< Error interrupt priority
    IRQn_Type        eri_irq;          ///< Error interrupt IRQ number

    /** Optional transfer instance used to receive multiple bytes without interrupts.  Set to NULL if unused.
     * If NULL, the number of bytes allowed in the read API is limited to one byte at a time. */
    transfer_instance_t const * p_transfer_rx;

    /** Optional transfer instance used to send multiple bytes without interrupts.  Set to NULL if unused.
     * If NULL, the number of bytes allowed in the write APIs is limited to one byte at a time. */
    transfer_instance_t const * p_transfer_tx;

    /* Configuration for UART Event processing */
    void (* p_callback)(uart_callback_args_t * p_args); ///< Pointer to callback function
    void const * p_context;                             ///< User defined context passed into callback function

    /* Pointer to UART peripheral specific configuration */
    void const * p_extend;                              ///< UART hardware dependent configuration
} uart_cfg_t;

/** UART control block.  Allocate an instance specific control block to pass into the UART API calls.
 * @par Implemented as
 * - sci_uart_instance_ctrl_t
 */
typedef void uart_ctrl_t;

/** Shared Interface definition for UART */
typedef struct st_uart_api
{
    /** Open  UART device.
     * @par Implemented as
     * - @ref R_SCI_UART_Open()
     * - @ref R_SCI_B_UART_Open()
     *
     * @param[in,out]  p_ctrl     Pointer to the UART control block. Must be declared by user. Value set here.
     * @param[in]      uart_cfg_t Pointer to UART configuration structure. All elements of this structure must be set by
     *                            user.
     */
    fsp_err_t (* open)(uart_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg);

    /** Read from UART device.  The read buffer is used until the read is complete.  When a transfer is complete, the
     * callback is called with event UART_EVENT_RX_COMPLETE.  Bytes received outside an active transfer are received in
     * the callback function with event UART_EVENT_RX_CHAR.
     * The maximum transfer size is reported by infoGet().
     * @par Implemented as
     * - @ref R_SCI_UART_Read()
     * - @ref R_SCI_B_UART_Read()
     *
     * @param[in]   p_ctrl     Pointer to the UART control block for the channel.
     * @param[in]   p_dest     Destination address to read data from.
     * @param[in]   bytes      Read data length.
     */
    fsp_err_t (* read)(uart_ctrl_t * const p_ctrl, uint8_t * const p_dest, uint32_t const bytes);

    /** Write to UART device.  The write buffer is used until write is complete.  Do not overwrite write buffer
     * contents until the write is finished.  When the write is complete (all bytes are fully transmitted on the wire),
     * the callback called with event UART_EVENT_TX_COMPLETE.
     * The maximum transfer size is reported by infoGet().
     * @par Implemented as
     * - @ref R_SCI_UART_Write()
     * - @ref R_SCI_B_UART_Write()
     *
     * @param[in]   p_ctrl     Pointer to the UART control block.
     * @param[in]   p_src      Source address  to write data to.
     * @param[in]   bytes      Write data length.
     */
    fsp_err_t (* write)(uart_ctrl_t * const p_ctrl, uint8_t const * const p_src, uint32_t const bytes);

    /** Change baud rate.
     * @warning Calling this API aborts any in-progress transmission and disables reception until the new baud
     * settings have been applied.
     *
     * @par Implemented as
     * - @ref R_SCI_UART_BaudSet()
     * - @ref R_SCI_B_UART_BaudSet()
     *
     * @param[in]   p_ctrl          Pointer to the UART control block.
     * @param[in]   p_baudrate_info Pointer to module specific information for configuring baud rate.
     */
    fsp_err_t (* baudSet)(uart_ctrl_t * const p_ctrl, void const * const p_baudrate_info);

    /** Get the driver specific information.
     * @par Implemented as
     * - @ref R_SCI_UART_InfoGet()
     * - @ref R_SCI_B_UART_InfoGet()
     *
     * @param[in]   p_ctrl     Pointer to the UART control block.
     * @param[in]   baudrate   Baud rate in bps.
     */
    fsp_err_t (* infoGet)(uart_ctrl_t * const p_ctrl, uart_info_t * const p_info);

    /**
     * Abort ongoing transfer.
     * @par Implemented as
     * - @ref R_SCI_UART_Abort()
     * - @ref R_SCI_B_UART_Abort()
     *
     * @param[in]   p_ctrl                   Pointer to the UART control block.
     * @param[in]   communication_to_abort   Type of abort request.
     */
    fsp_err_t (* communicationAbort)(uart_ctrl_t * const p_ctrl, uart_dir_t communication_to_abort);

    /**
     * Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - R_SCI_Uart_CallbackSet()
     * - R_SCI_B_Uart_CallbackSet()
     *
     * @param[in]   p_ctrl                   Pointer to the UART control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(uart_ctrl_t * const p_api_ctrl, void (* p_callback)(uart_callback_args_t *),
                              void const * const p_context, uart_callback_args_t * const p_callback_memory);

    /** Close UART device.
     * @par Implemented as
     * - @ref R_SCI_UART_Close()
     * - @ref R_SCI_B_UART_Close()
     *
     * @param[in]   p_ctrl     Pointer to the UART control block.
     */
    fsp_err_t (* close)(uart_ctrl_t * const p_ctrl);

    /** Stop ongoing read and return the number of bytes remaining in the read.
     * @par Implemented as
     * - @ref R_SCI_UART_ReadStop()
     * - @ref R_SCI_B_UART_ReadStop()
     *
     * @param[in]   p_ctrl                  Pointer to the UART control block.
     * @param[in,out]   remaining_bytes     Pointer to location to store remaining bytes for read.
     */
    fsp_err_t (* readStop)(uart_ctrl_t * const p_ctrl, uint32_t * remaining_bytes);
} uart_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_uart_instance
{
    uart_ctrl_t      * p_ctrl;         ///< Pointer to the control structure for this instance
    uart_cfg_t const * p_cfg;          ///< Pointer to the configuration structure for this instance
    uart_api_t const * p_api;          ///< Pointer to the API structure for this instance
} uart_instance_t;

/** @} (end defgroup UART_API) */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
