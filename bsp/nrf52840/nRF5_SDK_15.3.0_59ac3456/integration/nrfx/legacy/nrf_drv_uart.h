/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef NRF_DRV_UART_H__
#define NRF_DRV_UART_H__

#include <nrfx.h>

#if defined(UARTE_PRESENT) && NRFX_CHECK(NRFX_UARTE_ENABLED)
    #define NRF_DRV_UART_WITH_UARTE
#endif
#if defined(UART_PRESENT) && NRFX_CHECK(NRFX_UART_ENABLED)
    #define NRF_DRV_UART_WITH_UART
#endif

#if defined(NRF_DRV_UART_WITH_UARTE)
    #include <nrfx_uarte.h>
    #define NRF_DRV_UART_CREATE_UARTE(id) \
        .uarte = NRFX_UARTE_INSTANCE(id),
#else
    // Compilers (at least the smart ones) will remove the UARTE related code
    // (blocks starting with "if (NRF_DRV_UART_USE_UARTE)") when it is not used,
    // but to perform the compilation they need the following definitions.
    #define nrfx_uarte_init(...)                0
    #define nrfx_uarte_uninit(...)
    #define nrfx_uarte_task_address_get(...)    0
    #define nrfx_uarte_event_address_get(...)   0
    #define nrfx_uarte_tx(...)                  0
    #define nrfx_uarte_tx_in_progress(...)      0
    #define nrfx_uarte_tx_abort(...)
    #define nrfx_uarte_rx(...)                  0
    #define nrfx_uarte_rx_ready(...)            0
    #define nrfx_uarte_rx_abort(...)
    #define nrfx_uarte_errorsrc_get(...)        0
    #define NRF_DRV_UART_CREATE_UARTE(id)
#endif

#if defined(NRF_DRV_UART_WITH_UART)
    #include <nrfx_uart.h>

    #define NRF_DRV_UART_CREATE_UART(id)   _NRF_DRV_UART_CREATE_UART(id)
    #define _NRF_DRV_UART_CREATE_UART(id)  NRF_DRV_UART_CREATE_UART_##id
    #define NRF_DRV_UART_CREATE_UART_0  \
        .uart = NRFX_UART_INSTANCE(0),
    #define NRF_DRV_UART_CREATE_UART_1  \
        .uart = { .p_reg = NULL },

#else
    // Compilers (at least the smart ones) will remove the UART related code
    // (blocks starting with "if (NRF_DRV_UART_USE_UART)") when it is not used,
    // but to perform the compilation they need the following definitions.
    #define nrfx_uart_init(...)                 0
    #define nrfx_uart_uninit(...)
    #define nrfx_uart_task_address_get(...)     0
    #define nrfx_uart_event_address_get(...)    0
    #define nrfx_uart_tx(...)                   0
    #define nrfx_uart_tx_in_progress(...)       0
    #define nrfx_uart_tx_abort(...)
    #define nrfx_uart_rx(...)                   0
    #define nrfx_uart_rx_enable(...)
    #define nrfx_uart_rx_disable(...)
    #define nrfx_uart_rx_ready(...)             0
    #define nrfx_uart_rx_abort(...)
    #define nrfx_uart_errorsrc_get(...)         0
    #define NRF_DRV_UART_CREATE_UART(id)

    // This part is for old modules that use directly UART HAL definitions
    // (to make them compilable for chips that have only UARTE).
    #define NRF_UART_BAUDRATE_1200      NRF_UARTE_BAUDRATE_1200
    #define NRF_UART_BAUDRATE_2400      NRF_UARTE_BAUDRATE_2400
    #define NRF_UART_BAUDRATE_4800      NRF_UARTE_BAUDRATE_4800
    #define NRF_UART_BAUDRATE_9600      NRF_UARTE_BAUDRATE_9600
    #define NRF_UART_BAUDRATE_14400     NRF_UARTE_BAUDRATE_14400
    #define NRF_UART_BAUDRATE_19200     NRF_UARTE_BAUDRATE_19200
    #define NRF_UART_BAUDRATE_28800     NRF_UARTE_BAUDRATE_28800
    #define NRF_UART_BAUDRATE_38400     NRF_UARTE_BAUDRATE_38400
    #define NRF_UART_BAUDRATE_57600     NRF_UARTE_BAUDRATE_57600
    #define NRF_UART_BAUDRATE_76800     NRF_UARTE_BAUDRATE_76800
    #define NRF_UART_BAUDRATE_115200    NRF_UARTE_BAUDRATE_115200
    #define NRF_UART_BAUDRATE_230400    NRF_UARTE_BAUDRATE_230400
    #define NRF_UART_BAUDRATE_250000    NRF_UARTE_BAUDRATE_250000
    #define NRF_UART_BAUDRATE_460800    NRF_UARTE_BAUDRATE_460800
    #define NRF_UART_BAUDRATE_921600    NRF_UARTE_BAUDRATE_921600
    #define NRF_UART_BAUDRATE_1000000   NRF_UARTE_BAUDRATE_1000000
    typedef nrf_uarte_baudrate_t        nrf_uart_baudrate_t;
    #define NRF_UART_ERROR_OVERRUN_MASK NRF_UARTE_ERROR_OVERRUN_MASK
    #define NRF_UART_ERROR_PARITY_MASK  NRF_UARTE_ERROR_PARITY_MASK
    #define NRF_UART_ERROR_FRAMING_MASK NRF_UARTE_ERROR_PARITY_MASK
    #define NRF_UART_ERROR_BREAK_MASK   NRF_UARTE_ERROR_BREAK_MASK
    typedef nrf_uarte_error_mask_t      nrf_uart_error_mask_t;
    #define NRF_UART_HWFC_DISABLED      NRF_UARTE_HWFC_DISABLED
    #define NRF_UART_HWFC_ENABLED       NRF_UARTE_HWFC_ENABLED
    typedef nrf_uarte_hwfc_t            nrf_uart_hwfc_t;
    #define NRF_UART_PARITY_EXCLUDED    NRF_UARTE_PARITY_EXCLUDED
    #define NRF_UART_PARITY_INCLUDED    NRF_UARTE_PARITY_INCLUDED
    typedef nrf_uarte_parity_t          nrf_uart_parity_t;
    typedef nrf_uarte_task_t            nrf_uart_task_t;
    typedef nrf_uarte_event_t           nrf_uart_event_t;
    #define NRF_UART_PSEL_DISCONNECTED  NRF_UARTE_PSEL_DISCONNECTED
    #define nrf_uart_event_clear(...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_uart UART driver - legacy layer
 * @{
 * @ingroup  nrf_uart
 * @brief    Layer providing compatibility with the former API.
 */

/**
 * @brief Structure for the UART driver instance.
 */
typedef struct
{
    uint8_t inst_idx;
#if defined(NRF_DRV_UART_WITH_UARTE)
    nrfx_uarte_t uarte;
#endif
#if defined(NRF_DRV_UART_WITH_UART)
    nrfx_uart_t uart;
#endif
} nrf_drv_uart_t;

/**
 * @brief Macro for creating an UART driver instance.
 */
#define NRF_DRV_UART_INSTANCE(id) \
{                                 \
    .inst_idx = id,               \
    NRF_DRV_UART_CREATE_UARTE(id) \
    NRF_DRV_UART_CREATE_UART(id)  \
}

/**
 * @brief Types of UART driver events.
 */
typedef enum
{
    NRF_DRV_UART_EVT_TX_DONE, ///< Requested TX transfer completed.
    NRF_DRV_UART_EVT_RX_DONE, ///< Requested RX transfer completed.
    NRF_DRV_UART_EVT_ERROR,   ///< Error reported by UART peripheral.
} nrf_drv_uart_evt_type_t;

/**@brief Structure for UART configuration. */
typedef struct
{
    uint32_t            pseltxd;            ///< TXD pin number.
    uint32_t            pselrxd;            ///< RXD pin number.
    uint32_t            pselcts;            ///< CTS pin number.
    uint32_t            pselrts;            ///< RTS pin number.
    void *              p_context;          ///< Context passed to interrupt handler.
    nrf_uart_hwfc_t     hwfc;               ///< Flow control configuration.
    nrf_uart_parity_t   parity;             ///< Parity configuration.
    nrf_uart_baudrate_t baudrate;           ///< Baudrate.
    uint8_t             interrupt_priority; ///< Interrupt priority.
#if defined(NRF_DRV_UART_WITH_UARTE) && defined(NRF_DRV_UART_WITH_UART)
    bool                use_easy_dma;
#endif
} nrf_drv_uart_config_t;

#if defined(NRF_DRV_UART_WITH_UARTE) && defined(NRF_DRV_UART_WITH_UART)
extern uint8_t nrf_drv_uart_use_easy_dma[];
#define NRF_DRV_UART_DEFAULT_CONFIG_USE_EASY_DMA  .use_easy_dma = true,
#else
#define NRF_DRV_UART_DEFAULT_CONFIG_USE_EASY_DMA
#endif

/**@brief UART default configuration. */
#define NRF_DRV_UART_DEFAULT_CONFIG                                          \
{                                                                            \
    .pseltxd            = NRF_UART_PSEL_DISCONNECTED,                        \
    .pselrxd            = NRF_UART_PSEL_DISCONNECTED,                        \
    .pselcts            = NRF_UART_PSEL_DISCONNECTED,                        \
    .pselrts            = NRF_UART_PSEL_DISCONNECTED,                        \
    .p_context          = NULL,                                              \
    .hwfc               = (nrf_uart_hwfc_t)UART_DEFAULT_CONFIG_HWFC,         \
    .parity             = (nrf_uart_parity_t)UART_DEFAULT_CONFIG_PARITY,     \
    .baudrate           = (nrf_uart_baudrate_t)UART_DEFAULT_CONFIG_BAUDRATE, \
    .interrupt_priority = UART_DEFAULT_CONFIG_IRQ_PRIORITY,                  \
    NRF_DRV_UART_DEFAULT_CONFIG_USE_EASY_DMA                                 \
}

/**@brief Structure for UART transfer completion event. */
typedef struct
{
    uint8_t * p_data; ///< Pointer to memory used for transfer.
    uint8_t   bytes;  ///< Number of bytes transfered.
} nrf_drv_uart_xfer_evt_t;

/**@brief Structure for UART error event. */
typedef struct
{
    nrf_drv_uart_xfer_evt_t rxtx;      ///< Transfer details includes number of bytes transfered.
    uint32_t                error_mask;///< Mask of error flags that generated the event.
} nrf_drv_uart_error_evt_t;

/**@brief Structure for UART event. */
typedef struct
{
    nrf_drv_uart_evt_type_t type;      ///< Event type.
    union
    {
        nrf_drv_uart_xfer_evt_t  rxtx; ///< Data provided for transfer completion events.
        nrf_drv_uart_error_evt_t error;///< Data provided for error event.
    } data;
} nrf_drv_uart_event_t;

/**
 * @brief UART interrupt event handler.
 *
 * @param[in] p_event    Pointer to event structure. Event is allocated on the stack so it is available
 *                       only within the context of the event handler.
 * @param[in] p_context  Context passed to interrupt handler, set on initialization.
 */
typedef void (*nrf_uart_event_handler_t)(nrf_drv_uart_event_t * p_event, void * p_context);

/**
 * @brief Function for initializing the UART driver.
 *
 * This function configures and enables UART. After this function GPIO pins are controlled by UART.
 *
 * @param[in] p_instance    Pointer to the driver instance structure.
 * @param[in] p_config      Initial configuration.
 * @param[in] event_handler Event handler provided by the user. If not provided driver works in
 *                          blocking mode.
 *
 * @retval    NRFX_SUCCESS             If initialization was successful.
 * @retval    NRFX_ERROR_INVALID_STATE If driver is already initialized.
 */
ret_code_t nrf_drv_uart_init(nrf_drv_uart_t const *        p_instance,
                             nrf_drv_uart_config_t const * p_config,
                             nrf_uart_event_handler_t      event_handler);

/**
 * @brief Function for uninitializing  the UART driver.
 * @param[in] p_instance Pointer to the driver instance structure.
 */
__STATIC_INLINE
void nrf_drv_uart_uninit(nrf_drv_uart_t const * p_instance);

/**
 * @brief Function for getting the address of a specific UART task.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] task       Task.
 *
 * @return    Task address.
 */
__STATIC_INLINE
uint32_t nrf_drv_uart_task_address_get(nrf_drv_uart_t const * p_instance,
                                       nrf_uart_task_t        task);

/**
 * @brief Function for getting the address of a specific UART event.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] event      Event.
 *
 * @return    Event address.
 */
__STATIC_INLINE
uint32_t nrf_drv_uart_event_address_get(nrf_drv_uart_t const * p_instance,
                                        nrf_uart_event_t       event);

/**
 * @brief Function for sending data over UART.
 *
 * If an event handler was provided in nrf_drv_uart_init() call, this function
 * returns immediately and the handler is called when the transfer is done.
 * Otherwise, the transfer is performed in blocking mode, i.e. this function
 * returns when the transfer is finished. Blocking mode is not using interrupt so
 * there is no context switching inside the function.
 *
 * @note Peripherals using EasyDMA (i.e. UARTE) require that the transfer buffers
 *       are placed in the Data RAM region. If they are not and UARTE instance is
 *       used, this function will fail with error code NRFX_ERROR_INVALID_ADDR.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] p_data     Pointer to data.
 * @param[in] length     Number of bytes to send.
 *
 * @retval    NRFX_SUCCESS            If initialization was successful.
 * @retval    NRFX_ERROR_BUSY         If driver is already transferring.
 * @retval    NRFX_ERROR_FORBIDDEN    If the transfer was aborted from a different context
 *                                    (blocking mode only, also see @ref nrf_drv_uart_rx_disable).
 * @retval    NRFX_ERROR_INVALID_ADDR If p_data does not point to RAM buffer (UARTE only).
 */
__STATIC_INLINE
ret_code_t nrf_drv_uart_tx(nrf_drv_uart_t const * p_instance,
                           uint8_t const * const  p_data,
                           uint8_t                length);

/**
 * @brief Function for checking if UART is currently transmitting.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @retval true  If UART is transmitting.
 * @retval false If UART is not transmitting.
 */
__STATIC_INLINE
bool nrf_drv_uart_tx_in_progress(nrf_drv_uart_t const * p_instance);

/**
 * @brief Function for aborting any ongoing transmission.
 * @note @ref NRF_DRV_UART_EVT_TX_DONE event will be generated in non-blocking mode. Event will
 *       contain number of bytes sent until abort was called. If Easy DMA is not used event will be
 *       called from the function context. If Easy DMA is used it will be called from UART interrupt
 *       context.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
__STATIC_INLINE
void nrf_drv_uart_tx_abort(nrf_drv_uart_t const * p_instance);

/**
 * @brief Function for receiving data over UART.
 *
 * If an event handler was provided in the nrf_drv_uart_init() call, this function
 * returns immediately and the handler is called when the transfer is done.
 * Otherwise, the transfer is performed in blocking mode, i.e. this function
 * returns when the transfer is finished. Blocking mode is not using interrupt so
 * there is no context switching inside the function.
 * The receive buffer pointer is double buffered in non-blocking mode. The secondary
 * buffer can be set immediately after starting the transfer and will be filled
 * when the primary buffer is full. The double buffering feature allows
 * receiving data continuously.
 *
 * @note Peripherals using EasyDMA (i.e. UARTE) require that the transfer buffers
 *       are placed in the Data RAM region. If they are not and UARTE driver instance
 *       is used, this function will fail with error code NRFX_ERROR_INVALID_ADDR.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] p_data     Pointer to data.
 * @param[in] length     Number of bytes to receive.
 *
 * @retval    NRFX_SUCCESS If initialization was successful.
 * @retval    NRFX_ERROR_BUSY If the driver is already receiving
 *                            (and the secondary buffer has already been set
 *                            in non-blocking mode).
 * @retval    NRFX_ERROR_FORBIDDEN If the transfer was aborted from a different context
 *                                (blocking mode only, also see @ref nrf_drv_uart_rx_disable).
 * @retval    NRFX_ERROR_INTERNAL If UART peripheral reported an error.
 * @retval    NRFX_ERROR_INVALID_ADDR If p_data does not point to RAM buffer (UARTE only).
 */
__STATIC_INLINE
ret_code_t nrf_drv_uart_rx(nrf_drv_uart_t const * p_instance,
                           uint8_t *              p_data,
                           uint8_t                length);



/**
 * @brief Function for testing the receiver state in blocking mode.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @retval true  If the receiver has at least one byte of data to get.
 * @retval false If the receiver is empty.
 */
__STATIC_INLINE
bool nrf_drv_uart_rx_ready(nrf_drv_uart_t const * p_instance);

/**
 * @brief Function for enabling the receiver.
 *
 * UART has a 6-byte-long RX FIFO and it is used to store incoming data. If a user does not call the
 * UART receive function before the FIFO is filled, an overrun error will appear. Enabling the receiver
 * without specifying an RX buffer is supported only in UART mode (without Easy DMA). The receiver must be
 * explicitly closed by the user @sa nrf_drv_uart_rx_disable. This function asserts if the mode is wrong.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
__STATIC_INLINE
void nrf_drv_uart_rx_enable(nrf_drv_uart_t const * p_instance);

/**
 * @brief Function for disabling the receiver.
 *
 * This function must be called to close the receiver after it has been explicitly enabled by
 * @sa nrf_drv_uart_rx_enable. The feature is supported only in UART mode (without Easy DMA). The function
 * asserts if mode is wrong.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
__STATIC_INLINE
void nrf_drv_uart_rx_disable(nrf_drv_uart_t const * p_instance);

/**
 * @brief Function for aborting any ongoing reception.
 * @note @ref NRF_DRV_UART_EVT_RX_DONE event will be generated in non-blocking mode. The event will
 *       contain the number of bytes received until abort was called. The event is called from UART interrupt
 *       context.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
__STATIC_INLINE
void nrf_drv_uart_rx_abort(nrf_drv_uart_t const * p_instance);

/**
 * @brief Function for reading error source mask. Mask contains values from @ref nrf_uart_error_mask_t.
 * @note Function should be used in blocking mode only. In case of non-blocking mode, an error event is
 *       generated. Function clears error sources after reading.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @retval    Mask of reported errors.
 */
__STATIC_INLINE
uint32_t nrf_drv_uart_errorsrc_get(nrf_drv_uart_t const * p_instance);


#ifndef SUPPRESS_INLINE_IMPLEMENTATION

#if defined(NRF_DRV_UART_WITH_UARTE) && defined(NRF_DRV_UART_WITH_UART)
    #define NRF_DRV_UART_USE_UARTE  (nrf_drv_uart_use_easy_dma[p_instance->inst_idx])
#elif defined(NRF_DRV_UART_WITH_UARTE)
    #define NRF_DRV_UART_USE_UARTE  true
#else
    #define NRF_DRV_UART_USE_UARTE  false
#endif
#define NRF_DRV_UART_USE_UART  (!NRF_DRV_UART_USE_UARTE)

__STATIC_INLINE
void nrf_drv_uart_uninit(nrf_drv_uart_t const * p_instance)
{
    if (NRF_DRV_UART_USE_UARTE)
    {
        nrfx_uarte_uninit(&p_instance->uarte);
    }
    else if (NRF_DRV_UART_USE_UART)
    {
        nrfx_uart_uninit(&p_instance->uart);
    }
}

__STATIC_INLINE
uint32_t nrf_drv_uart_task_address_get(nrf_drv_uart_t const * p_instance,
                                       nrf_uart_task_t task)
{
    uint32_t result = 0;
    if (NRF_DRV_UART_USE_UARTE)
    {
        result = nrfx_uarte_task_address_get(&p_instance->uarte,
                                             (nrf_uarte_task_t)task);
    }
    else if (NRF_DRV_UART_USE_UART)
    {
        result = nrfx_uart_task_address_get(&p_instance->uart, task);
    }
    return result;
}

__STATIC_INLINE
uint32_t nrf_drv_uart_event_address_get(nrf_drv_uart_t const * p_instance,
                                        nrf_uart_event_t event)
{
    uint32_t result = 0;
    if (NRF_DRV_UART_USE_UARTE)
    {
        result = nrfx_uarte_event_address_get(&p_instance->uarte,
                                              (nrf_uarte_event_t)event);
    }
    else if (NRF_DRV_UART_USE_UART)
    {
        result = nrfx_uart_event_address_get(&p_instance->uart, event);
    }
    return result;
}

__STATIC_INLINE
ret_code_t nrf_drv_uart_tx(nrf_drv_uart_t const * p_instance,
                           uint8_t const *        p_data,
                           uint8_t                length)
{
    uint32_t result = 0;
    if (NRF_DRV_UART_USE_UARTE)
    {
        result = nrfx_uarte_tx(&p_instance->uarte,
                               p_data,
                               length);
    }
    else if (NRF_DRV_UART_USE_UART)
    {
        result = nrfx_uart_tx(&p_instance->uart,
                              p_data,
                              length);
    }
    return result;
}

__STATIC_INLINE
bool nrf_drv_uart_tx_in_progress(nrf_drv_uart_t const * p_instance)
{
    bool result = 0;
    if (NRF_DRV_UART_USE_UARTE)
    {
        result = nrfx_uarte_tx_in_progress(&p_instance->uarte);
    }
    else if (NRF_DRV_UART_USE_UART)
    {
        result = nrfx_uart_tx_in_progress(&p_instance->uart);
    }
    return result;
}

__STATIC_INLINE
void nrf_drv_uart_tx_abort(nrf_drv_uart_t const * p_instance)
{
    if (NRF_DRV_UART_USE_UARTE)
    {
        nrfx_uarte_tx_abort(&p_instance->uarte);
    }
    else if (NRF_DRV_UART_USE_UART)
    {
        nrfx_uart_tx_abort(&p_instance->uart);
    }
}

__STATIC_INLINE
ret_code_t nrf_drv_uart_rx(nrf_drv_uart_t const * p_instance,
                           uint8_t *              p_data,
                           uint8_t                length)
{
    uint32_t result = 0;
    if (NRF_DRV_UART_USE_UARTE)
    {
        result = nrfx_uarte_rx(&p_instance->uarte,
                               p_data,
                               length);
    }
    else if (NRF_DRV_UART_USE_UART)
    {
        result = nrfx_uart_rx(&p_instance->uart,
                              p_data,
                              length);
    }
    return result;
}

__STATIC_INLINE
bool nrf_drv_uart_rx_ready(nrf_drv_uart_t const * p_instance)
{
    bool result = 0;
    if (NRF_DRV_UART_USE_UARTE)
    {
        result = nrfx_uarte_rx_ready(&p_instance->uarte);
    }
    else if (NRF_DRV_UART_USE_UART)
    {
        result = nrfx_uart_rx_ready(&p_instance->uart);
    }
    return result;
}

__STATIC_INLINE
void nrf_drv_uart_rx_enable(nrf_drv_uart_t const * p_instance)
{
    if (NRF_DRV_UART_USE_UARTE)
    {
        NRFX_ASSERT(false); // not supported
    }
    else if (NRF_DRV_UART_USE_UART)
    {
        nrfx_uart_rx_enable(&p_instance->uart);
    }
}

__STATIC_INLINE
void nrf_drv_uart_rx_disable(nrf_drv_uart_t const * p_instance)
{
    if (NRF_DRV_UART_USE_UARTE)
    {
        NRFX_ASSERT(false); // not supported
    }
    else if (NRF_DRV_UART_USE_UART)
    {
        nrfx_uart_rx_disable(&p_instance->uart);
    }
}

__STATIC_INLINE
void nrf_drv_uart_rx_abort(nrf_drv_uart_t const * p_instance)
{
    if (NRF_DRV_UART_USE_UARTE)
    {
        nrfx_uarte_rx_abort(&p_instance->uarte);
    }
    else if (NRF_DRV_UART_USE_UART)
    {
        nrfx_uart_rx_abort(&p_instance->uart);
    }
}

__STATIC_INLINE
uint32_t nrf_drv_uart_errorsrc_get(nrf_drv_uart_t const * p_instance)
{
    uint32_t result = 0;
    if (NRF_DRV_UART_USE_UARTE)
    {
        result = nrfx_uarte_errorsrc_get(&p_instance->uarte);
    }
    else if (NRF_DRV_UART_USE_UART)
    {
        nrf_uart_event_clear(p_instance->uart.p_reg, NRF_UART_EVENT_ERROR);
        result = nrfx_uart_errorsrc_get(&p_instance->uart);
    }
    return result;
}

#endif // SUPPRESS_INLINE_IMPLEMENTATION

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_UART_H__
