/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
/**@file
 * @addtogroup nrf_uart UART driver and HAL
 * @ingroup nrf_drivers
 * @brief UART API.
 * @details The UART driver provides APIs for utilizing the UART peripheral.
 *
 * @defgroup nrf_drv_uart UART driver
 * @{
 * @ingroup  nrf_uart
 *
 * @brief    UART driver.
 */

#ifndef NRF_DRV_UART_H
#define NRF_DRV_UART_H

#include "nrf_uart.h"
#ifdef UARTE_PRESENT
#include "nrf_uarte.h"
#endif

#include "sdk_errors.h"
#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef UART1_ENABLED
#define UART1_ENABLED 0
#endif

#ifndef UART0_ENABLED
#define UART0_ENABLED 0
#endif

#define UART0_INSTANCE_INDEX 0
#define UART1_INSTANCE_INDEX UART0_ENABLED
#define UART_ENABLED_COUNT UART0_ENABLED + UART1_ENABLED

#if defined(UARTE_PRESENT)
    #define NRF_DRV_UART_PERIPHERAL(id)           \
        (CONCAT_3(UART, id, _CONFIG_USE_EASY_DMA) == 1 ? \
            (void *)CONCAT_2(NRF_UARTE, id)       \
          : (void *)CONCAT_2(NRF_UART, id))
#else
    #define NRF_DRV_UART_PERIPHERAL(id)  (void *)CONCAT_2(NRF_UART, id)
#endif

// This set of macros makes it possible to exclude parts of code, when one type
// of supported peripherals is not used.

#if defined(UARTE_PRESENT)

#if (UART_EASY_DMA_SUPPORT == 1)
#define UARTE_IN_USE
#endif

#if (UART_LEGACY_SUPPORT == 1)
#define UART_IN_USE
#endif

#if (UART_ENABLED == 1) && ((!defined(UARTE_IN_USE) && !defined(UART_IN_USE)) || ((UART_EASY_DMA_SUPPORT == 0) && (UART_LEGACY_SUPPORT == 0)))
#error "Illegal settings in uart module!"
#endif

#elif defined(UART_PRESENT)
#define UART_IN_USE
#endif

/**
 * @brief Structure for the UART driver instance.
 */
typedef struct
{
    union
    {
#if (defined(UARTE_IN_USE))
    NRF_UARTE_Type * p_uarte; ///< Pointer to a structure with UARTE registers.
#endif
#if (defined(UART_IN_USE) || (UART_ENABLED == 0))
    NRF_UART_Type * p_uart;   ///< Pointer to a structure with UART registers.
#endif
    } reg;
    uint8_t drv_inst_idx;     ///< Driver instance index.
} nrf_drv_uart_t;

/**
 * @brief Macro for creating an UART driver instance.
 */
#define NRF_DRV_UART_INSTANCE(id)                            \
{                                                            \
    .reg          = {NRF_DRV_UART_PERIPHERAL(id)},           \
    .drv_inst_idx = CONCAT_3(UART, id, _INSTANCE_INDEX),\
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
#ifdef UARTE_PRESENT
    bool                use_easy_dma;
#endif
} nrf_drv_uart_config_t;

/**@brief UART default configuration. */
#ifdef UARTE_PRESENT
#if !UART_LEGACY_SUPPORT
#define DEFAULT_CONFIG_USE_EASY_DMA true
#elif !UART_EASY_DMA_SUPPORT
#define DEFAULT_CONFIG_USE_EASY_DMA false
#else
#define DEFAULT_CONFIG_USE_EASY_DMA UART0_USE_EASY_DMA
#endif
#define NRF_DRV_UART_DEFAULT_CONFIG                                                   \
    {                                                                                 \
        .pseltxd            = NRF_UART_PSEL_DISCONNECTED,                             \
        .pselrxd            = NRF_UART_PSEL_DISCONNECTED,                             \
        .pselcts            = NRF_UART_PSEL_DISCONNECTED,                             \
        .pselrts            = NRF_UART_PSEL_DISCONNECTED,                             \
        .p_context          = NULL,                                                   \
        .hwfc               = (nrf_uart_hwfc_t)UART_DEFAULT_CONFIG_HWFC,              \
        .parity             = (nrf_uart_parity_t)UART_DEFAULT_CONFIG_PARITY,          \
        .baudrate           = (nrf_uart_baudrate_t)UART_DEFAULT_CONFIG_BAUDRATE,      \
        .interrupt_priority = UART_DEFAULT_CONFIG_IRQ_PRIORITY,                       \
        .use_easy_dma       = true                                                    \
    }
#else
#define NRF_DRV_UART_DEFAULT_CONFIG                                                   \
    {                                                                                 \
        .pseltxd            = NRF_UART_PSEL_DISCONNECTED,                             \
        .pselrxd            = NRF_UART_PSEL_DISCONNECTED,                             \
        .pselcts            = NRF_UART_PSEL_DISCONNECTED,                             \
        .pselrts            = NRF_UART_PSEL_DISCONNECTED,                             \
        .p_context          = NULL,                                                   \
        .hwfc               = (nrf_uart_hwfc_t)UART_DEFAULT_CONFIG_HWFC,              \
        .parity             = (nrf_uart_parity_t)UART_DEFAULT_CONFIG_PARITY,          \
        .baudrate           = (nrf_uart_baudrate_t)UART_DEFAULT_CONFIG_BAUDRATE,      \
        .interrupt_priority = UART_DEFAULT_CONFIG_IRQ_PRIORITY,                       \
    }
#endif

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
 * @param[in] p_config      Initial configuration. Default configuration used if NULL.
 * @param[in] event_handler Event handler provided by the user. If not provided driver works in
 *                          blocking mode.
 *
 * @retval    NRF_SUCCESS             If initialization was successful.
 * @retval    NRF_ERROR_INVALID_STATE If driver is already initialized.
 */
ret_code_t nrf_drv_uart_init(nrf_drv_uart_t const *        p_instance,
                             nrf_drv_uart_config_t const * p_config,
                             nrf_uart_event_handler_t      event_handler);

/**
 * @brief Function for uninitializing  the UART driver.
 * @param[in] p_instance Pointer to the driver instance structure.
 */
void nrf_drv_uart_uninit(nrf_drv_uart_t const * p_instance);

/**
 * @brief Function for getting the address of a specific UART task.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] task       Task.
 *
 * @return    Task address.
 */
__STATIC_INLINE uint32_t nrf_drv_uart_task_address_get(nrf_drv_uart_t const * p_instance,
                                                       nrf_uart_task_t task);

/**
 * @brief Function for getting the address of a specific UART event.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] event      Event.
 *
 * @return    Event address.
 */
__STATIC_INLINE uint32_t nrf_drv_uart_event_address_get(nrf_drv_uart_t const * p_instance,
                                                        nrf_uart_event_t event);

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
 *       used, this function will fail with error code NRF_ERROR_INVALID_ADDR.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] p_data     Pointer to data.
 * @param[in] length     Number of bytes to send.
 *
 * @retval    NRF_SUCCESS            If initialization was successful.
 * @retval    NRF_ERROR_BUSY         If driver is already transferring.
 * @retval    NRF_ERROR_FORBIDDEN    If the transfer was aborted from a different context
 *                                   (blocking mode only, also see @ref nrf_drv_uart_rx_disable).
 * @retval    NRF_ERROR_INVALID_ADDR If p_data does not point to RAM buffer (UARTE only).
 */
ret_code_t nrf_drv_uart_tx(nrf_drv_uart_t const * p_instance,
                           uint8_t const * const p_data, uint8_t length);

/**
 * @brief Function for checking if UART is currently transmitting.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @retval true  If UART is transmitting.
 * @retval false If UART is not transmitting.
 */
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
 *       is used, this function will fail with error code NRF_ERROR_INVALID_ADDR.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] p_data     Pointer to data.
 * @param[in] length     Number of bytes to receive.
 *
 * @retval    NRF_SUCCESS If initialization was successful.
 * @retval    NRF_ERROR_BUSY If the driver is already receiving
 *                           (and the secondary buffer has already been set
 *                           in non-blocking mode).
 * @retval    NRF_ERROR_FORBIDDEN If the transfer was aborted from a different context
 *                               (blocking mode only, also see @ref nrf_drv_uart_rx_disable).
 * @retval    NRF_ERROR_INTERNAL If UART peripheral reported an error.
 * @retval    NRF_ERROR_INVALID_ADDR If p_data does not point to RAM buffer (UARTE only).
 */
ret_code_t nrf_drv_uart_rx(nrf_drv_uart_t const * p_instance,
                           uint8_t * p_data, uint8_t length);



/**
 * @brief Function for testing the receiver state in blocking mode.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @retval true  If the receiver has at least one byte of data to get.
 * @retval false If the receiver is empty.
 */
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
void nrf_drv_uart_rx_disable(nrf_drv_uart_t const * p_instance);

/**
 * @brief Function for aborting any ongoing reception.
 * @note @ref NRF_DRV_UART_EVT_RX_DONE event will be generated in non-blocking mode. The event will
 *       contain the number of bytes received until abort was called. The event is called from UART interrupt
 *       context.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
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
uint32_t nrf_drv_uart_errorsrc_get(nrf_drv_uart_t const * p_instance);


#ifndef SUPPRESS_INLINE_IMPLEMENTATION
__STATIC_INLINE uint32_t nrf_drv_uart_task_address_get(nrf_drv_uart_t const * p_instance,
                                                       nrf_uart_task_t task)
{
#ifdef UART_IN_USE
    return nrf_uart_task_address_get(p_instance->reg.p_uart, task);
#else
    return nrf_uarte_task_address_get(p_instance->reg.p_uarte, (nrf_uarte_task_t)task);
#endif
}

__STATIC_INLINE uint32_t nrf_drv_uart_event_address_get(nrf_drv_uart_t const * p_instance,
                                                        nrf_uart_event_t event)
{
#ifdef UART_IN_USE
    return nrf_uart_event_address_get(p_instance->reg.p_uart, event);
#else
    return nrf_uarte_event_address_get(p_instance->reg.p_uarte, (nrf_uarte_event_t)event);
#endif
}
#endif //SUPPRESS_INLINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif //NRF_DRV_UART_H
/** @} */
