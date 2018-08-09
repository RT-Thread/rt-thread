/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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

#ifndef NRF_DRV_SPI_H__
#define NRF_DRV_SPI_H__

#include <nrfx.h>
#ifdef SPIM_PRESENT
    #include <nrfx_spim.h>
#else
    // Compilers (at least the smart ones) will remove the SPIM related code
    // (blocks starting with "if (NRF_DRV_SPI_USE_SPIM)") when it is not used,
    // but to perform the compilation they need the following definitions.
    #define nrfx_spim_init(...)             0
    #define nrfx_spim_uninit(...)
    #define nrfx_spim_start_task_get(...)   0
    #define nrfx_spim_end_event_get(...)    0
    #define nrfx_spim_abort(...)
#endif

#ifdef SPI_PRESENT
    #include <nrfx_spi.h>
#else
    // Compilers (at least the smart ones) will remove the SPI related code
    // (blocks starting with "if (NRF_DRV_SPI_USE_SPI)") when it is not used,
    // but to perform the compilation they need the following definitions.
    #define nrfx_spi_init(...)              0
    #define nrfx_spi_uninit(...)
    #define nrfx_spi_start_task_get(...)    0
    #define nrfx_spi_end_event_get(...)     0
    #define nrfx_spi_abort(...)

    // This part is for old modules that use directly SPI HAL definitions
    // (to make them compilable for chips that have only SPIM).
    #define NRF_SPI_FREQ_125K           NRF_SPIM_FREQ_125K
    #define NRF_SPI_FREQ_250K           NRF_SPIM_FREQ_250K
    #define NRF_SPI_FREQ_500K           NRF_SPIM_FREQ_500K
    #define NRF_SPI_FREQ_1M             NRF_SPIM_FREQ_1M
    #define NRF_SPI_FREQ_2M             NRF_SPIM_FREQ_2M
    #define NRF_SPI_FREQ_4M             NRF_SPIM_FREQ_4M
    #define NRF_SPI_FREQ_8M             NRF_SPIM_FREQ_8M
    #define NRF_SPI_MODE_0              NRF_SPIM_MODE_0
    #define NRF_SPI_MODE_1              NRF_SPIM_MODE_1
    #define NRF_SPI_MODE_2              NRF_SPIM_MODE_2
    #define NRF_SPI_MODE_3              NRF_SPIM_MODE_3
    #define NRF_SPI_BIT_ORDER_MSB_FIRST NRF_SPIM_BIT_ORDER_MSB_FIRST
    #define NRF_SPI_BIT_ORDER_LSB_FIRST NRF_SPIM_BIT_ORDER_LSB_FIRST
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_spi SPI master driver
 * @{
 * @ingroup  nrf_spi
 * @brief    Layer providing compatibility with the former API.
 */

/**
 * @brief SPI master driver instance data structure.
 */
typedef struct
{
    uint8_t inst_idx;
    union
    {
#ifdef SPIM_PRESENT
        nrfx_spim_t spim;
#endif
#ifdef SPI_PRESENT
        nrfx_spi_t  spi;
#endif
    } u;
    bool    use_easy_dma;
} nrf_drv_spi_t;

/**
 * @brief Macro for creating an SPI master driver instance.
 */
#define NRF_DRV_SPI_INSTANCE(id)    NRF_DRV_SPI_INSTANCE_(id)
#define NRF_DRV_SPI_INSTANCE_(id)   NRF_DRV_SPI_INSTANCE_ ## id
#if NRFX_CHECK(NRFX_SPIM0_ENABLED)
    #define NRF_DRV_SPI_INSTANCE_0 \
        { 0, { .spim = NRFX_SPIM_INSTANCE(0) }, true }
#elif NRFX_CHECK(NRFX_SPI0_ENABLED)
    #define NRF_DRV_SPI_INSTANCE_0 \
        { 0, { .spi = NRFX_SPI_INSTANCE(0) }, false }
#endif
#if NRFX_CHECK(NRFX_SPIM1_ENABLED)
    #define NRF_DRV_SPI_INSTANCE_1 \
        { 1, { .spim = NRFX_SPIM_INSTANCE(1) }, true }
#elif NRFX_CHECK(NRFX_SPI1_ENABLED)
    #define NRF_DRV_SPI_INSTANCE_1 \
        { 1, { .spi = NRFX_SPI_INSTANCE(1) }, false }
#endif
#if NRFX_CHECK(NRFX_SPIM2_ENABLED)
    #define NRF_DRV_SPI_INSTANCE_2 \
        { 2, { .spim = NRFX_SPIM_INSTANCE(2) }, true }
#elif NRFX_CHECK(NRFX_SPI2_ENABLED)
    #define NRF_DRV_SPI_INSTANCE_2 \
        { 2, { .spi = NRFX_SPI_INSTANCE(2) }, false }
#endif

/**
 * @brief This value can be provided instead of a pin number for signals MOSI,
 *        MISO, and Slave Select to specify that the given signal is not used and
 *        therefore does not need to be connected to a pin.
 */
#define NRF_DRV_SPI_PIN_NOT_USED  0xFF

/**
 * @brief SPI data rates.
 */
typedef enum
{
    NRF_DRV_SPI_FREQ_125K = NRF_SPI_FREQ_125K, ///< 125 kbps.
    NRF_DRV_SPI_FREQ_250K = NRF_SPI_FREQ_250K, ///< 250 kbps.
    NRF_DRV_SPI_FREQ_500K = NRF_SPI_FREQ_500K, ///< 500 kbps.
    NRF_DRV_SPI_FREQ_1M   = NRF_SPI_FREQ_1M,   ///< 1 Mbps.
    NRF_DRV_SPI_FREQ_2M   = NRF_SPI_FREQ_2M,   ///< 2 Mbps.
    NRF_DRV_SPI_FREQ_4M   = NRF_SPI_FREQ_4M,   ///< 4 Mbps.
    NRF_DRV_SPI_FREQ_8M   = NRF_SPI_FREQ_8M    ///< 8 Mbps.
} nrf_drv_spi_frequency_t;

/**
 * @brief SPI modes.
 */
typedef enum
{
    NRF_DRV_SPI_MODE_0 = NRF_SPI_MODE_0, ///< SCK active high, sample on leading edge of clock.
    NRF_DRV_SPI_MODE_1 = NRF_SPI_MODE_1, ///< SCK active high, sample on trailing edge of clock.
    NRF_DRV_SPI_MODE_2 = NRF_SPI_MODE_2, ///< SCK active low, sample on leading edge of clock.
    NRF_DRV_SPI_MODE_3 = NRF_SPI_MODE_3  ///< SCK active low, sample on trailing edge of clock.
} nrf_drv_spi_mode_t;

/**
 * @brief SPI bit orders.
 */
typedef enum
{
    NRF_DRV_SPI_BIT_ORDER_MSB_FIRST = NRF_SPI_BIT_ORDER_MSB_FIRST, ///< Most significant bit shifted out first.
    NRF_DRV_SPI_BIT_ORDER_LSB_FIRST = NRF_SPI_BIT_ORDER_LSB_FIRST  ///< Least significant bit shifted out first.
} nrf_drv_spi_bit_order_t;

/**
 * @brief SPI master driver instance configuration structure.
 */
typedef struct
{
    uint8_t sck_pin;      ///< SCK pin number.
    uint8_t mosi_pin;     ///< MOSI pin number (optional).
                          /**< Set to @ref NRF_DRV_SPI_PIN_NOT_USED
                           *   if this signal is not needed. */
    uint8_t miso_pin;     ///< MISO pin number (optional).
                          /**< Set to @ref NRF_DRV_SPI_PIN_NOT_USED
                           *   if this signal is not needed. */
    uint8_t ss_pin;       ///< Slave Select pin number (optional).
                          /**< Set to @ref NRF_DRV_SPI_PIN_NOT_USED
                           *   if this signal is not needed. The driver
                           *   supports only active low for this signal.
                           *   If the signal should be active high,
                           *   it must be controlled externally. */
    uint8_t irq_priority; ///< Interrupt priority.
    uint8_t orc;          ///< Over-run character.
                          /**< This character is used when all bytes from the TX buffer are sent,
                               but the transfer continues due to RX. */
    nrf_drv_spi_frequency_t frequency; ///< SPI frequency.
    nrf_drv_spi_mode_t      mode;      ///< SPI mode.
    nrf_drv_spi_bit_order_t bit_order; ///< SPI bit order.
} nrf_drv_spi_config_t;

/**
 * @brief SPI master instance default configuration.
 */
#define NRF_DRV_SPI_DEFAULT_CONFIG                           \
{                                                            \
    .sck_pin      = NRF_DRV_SPI_PIN_NOT_USED,                \
    .mosi_pin     = NRF_DRV_SPI_PIN_NOT_USED,                \
    .miso_pin     = NRF_DRV_SPI_PIN_NOT_USED,                \
    .ss_pin       = NRF_DRV_SPI_PIN_NOT_USED,                \
    .irq_priority = SPI_DEFAULT_CONFIG_IRQ_PRIORITY,         \
    .orc          = 0xFF,                                    \
    .frequency    = NRF_DRV_SPI_FREQ_4M,                     \
    .mode         = NRF_DRV_SPI_MODE_0,                      \
    .bit_order    = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST,         \
}

#define NRF_DRV_SPI_FLAG_TX_POSTINC          (1UL << 0) /**< TX buffer address incremented after transfer. */
#define NRF_DRV_SPI_FLAG_RX_POSTINC          (1UL << 1) /**< RX buffer address incremented after transfer. */
#define NRF_DRV_SPI_FLAG_NO_XFER_EVT_HANDLER (1UL << 2) /**< Interrupt after each transfer is suppressed, and the event handler is not called. */
#define NRF_DRV_SPI_FLAG_HOLD_XFER           (1UL << 3) /**< Set up the transfer but do not start it. */
#define NRF_DRV_SPI_FLAG_REPEATED_XFER       (1UL << 4) /**< Flag indicating that the transfer will be executed multiple times. */

/**
 * @brief Single transfer descriptor structure.
 */
typedef struct
{
    uint8_t const * p_tx_buffer; ///< Pointer to TX buffer.
    uint8_t         tx_length;   ///< TX buffer length.
    uint8_t       * p_rx_buffer; ///< Pointer to RX buffer.
    uint8_t         rx_length;   ///< RX buffer length.
}nrf_drv_spi_xfer_desc_t;

/**
 * @brief Macro for setting up single transfer descriptor.
 *
 * This macro is for internal use only.
 */
#define NRF_DRV_SPI_SINGLE_XFER(p_tx, tx_len, p_rx, rx_len)  \
    {                                                        \
    .p_tx_buffer = (uint8_t const *)(p_tx),                  \
    .tx_length = (tx_len),                                   \
    .p_rx_buffer = (p_rx),                                   \
    .rx_length = (rx_len),                                   \
    }

/**
 * @brief Macro for setting duplex TX RX transfer.
 */
#define NRF_DRV_SPI_XFER_TRX(p_tx_buf, tx_length, p_rx_buf, rx_length)                    \
        NRF_DRV_SPI_SINGLE_XFER(p_tx_buf, tx_length, p_rx_buf, rx_length)

/**
 * @brief Macro for setting TX transfer.
 */
#define NRF_DRV_SPI_XFER_TX(p_buf, length) \
        NRF_DRV_SPI_SINGLE_XFER(p_buf, length, NULL, 0)

/**
 * @brief Macro for setting RX transfer.
 */
#define NRF_DRV_SPI_XFER_RX(p_buf, length) \
        NRF_DRV_SPI_SINGLE_XFER(NULL, 0, p_buf, length)

/**
 * @brief SPI master driver event types, passed to the handler routine provided
 *        during initialization.
 */
typedef enum
{
    NRF_DRV_SPI_EVENT_DONE, ///< Transfer done.
} nrf_drv_spi_evt_type_t;

typedef struct
{
    nrf_drv_spi_evt_type_t  type;      ///< Event type.
    union
    {
        nrf_drv_spi_xfer_desc_t done;  ///< Event data for DONE event.
    } data;
} nrf_drv_spi_evt_t;

/**
 * @brief SPI master driver event handler type.
 */
typedef void (* nrf_drv_spi_evt_handler_t)(nrf_drv_spi_evt_t const * p_event,
                                           void *                    p_context);


/**
 * @brief Function for initializing the SPI master driver instance.
 *
 * This function configures and enables the specified peripheral.
 *
 * @note MISO pin has pull down enabled.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] p_config   Pointer to the structure with the initial configuration.
 *
 * @param     handler    Event handler provided by the user. If NULL, transfers
 *                       will be performed in blocking mode.
 * @param      p_context Context passed to event handler.
 *
 * @retval NRF_SUCCESS             If initialization was successful.
 * @retval NRF_ERROR_INVALID_STATE If the driver was already initialized.
 * @retval NRF_ERROR_BUSY          If some other peripheral with the same
 *                                 instance ID is already in use. This is
 *                                 possible only if PERIPHERAL_RESOURCE_SHARING_ENABLED
 *                                 is set to a value other than zero.
 */
ret_code_t nrf_drv_spi_init(nrf_drv_spi_t const * const p_instance,
                            nrf_drv_spi_config_t const * p_config,
                            nrf_drv_spi_evt_handler_t    handler,
                            void *                       p_context);

/**
 * @brief Function for uninitializing the SPI master driver instance.
 *
 * @note Configuration of pins is kept.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
__STATIC_INLINE
void nrf_drv_spi_uninit(nrf_drv_spi_t const * const p_instance);

/**
 * @brief Function for starting the SPI data transfer.
 *
 * If an event handler was provided in the @ref nrf_drv_spi_init call, this function
 * returns immediately and the handler is called when the transfer is done.
 * Otherwise, the transfer is performed in blocking mode, which means that this function
 * returns when the transfer is finished.
 *
 * @note Peripherals using EasyDMA (for example, SPIM) require the transfer buffers
 *       to be placed in the Data RAM region. If they are not and an SPIM instance is
 *       used, this function will fail with the error code NRF_ERROR_INVALID_ADDR.
 *
 * @param[in] p_instance       Pointer to the driver instance structure.
 * @param[in] p_tx_buffer      Pointer to the transmit buffer. Can be NULL
 *                             if there is nothing to send.
 * @param     tx_buffer_length Length of the transmit buffer.
 * @param[in] p_rx_buffer      Pointer to the receive buffer. Can be NULL
 *                             if there is nothing to receive.
 * @param     rx_buffer_length Length of the receive buffer.
 *
 * @retval NRF_SUCCESS            If the operation was successful.
 * @retval NRF_ERROR_BUSY         If a previously started transfer has not finished
 *                                yet.
 * @retval NRF_ERROR_INVALID_ADDR If the provided buffers are not placed in the Data
 *                                RAM region.
 */
__STATIC_INLINE
ret_code_t nrf_drv_spi_transfer(nrf_drv_spi_t const * const p_instance,
                                uint8_t const * p_tx_buffer,
                                uint8_t         tx_buffer_length,
                                uint8_t       * p_rx_buffer,
                                uint8_t         rx_buffer_length);

/**
 * @brief Function for starting the SPI data transfer with additional option flags.
 *
 * Function enables customizing the transfer by using option flags.
 *
 * Additional options are provided using the flags parameter:
 *
 * - @ref NRF_DRV_SPI_FLAG_TX_POSTINC and @ref NRF_DRV_SPI_FLAG_RX_POSTINC<span></span>:
 *   Post-incrementation of buffer addresses. Supported only by SPIM.
 * - @ref NRF_DRV_SPI_FLAG_HOLD_XFER<span></span>: Driver is not starting the transfer. Use this
 *   flag if the transfer is triggered externally by PPI. Supported only by SPIM. Use
 *   @ref nrf_drv_spi_start_task_get to get the address of the start task.
 * - @ref NRF_DRV_SPI_FLAG_NO_XFER_EVT_HANDLER<span></span>: No user event handler after transfer
 *   completion. This also means no interrupt at the end of the transfer. Supported only by SPIM.
 *   If @ref NRF_DRV_SPI_FLAG_NO_XFER_EVT_HANDLER is used, the driver does not set the instance into
 *   busy state, so you must ensure that the next transfers are set up when SPIM is not active.
 *   @ref nrf_drv_spi_end_event_get function can be used to detect end of transfer. Option can be used
 *   together with @ref NRF_DRV_SPI_FLAG_REPEATED_XFER to prepare a sequence of SPI transfers
 *   without interruptions.
 * - @ref NRF_DRV_SPI_FLAG_REPEATED_XFER<span></span>: Prepare for repeated transfers. You can set
 *   up a number of transfers that will be triggered externally (for example by PPI). An example is
 *   a TXRX transfer with the options @ref NRF_DRV_SPI_FLAG_RX_POSTINC,
 *   @ref NRF_DRV_SPI_FLAG_NO_XFER_EVT_HANDLER, and @ref NRF_DRV_SPI_FLAG_REPEATED_XFER. After the
 *   transfer is set up, a set of transfers can be triggered by PPI that will read, for example,
 *   the same register of an external component and put it into a RAM buffer without any interrupts.
 *   @ref nrf_drv_spi_end_event_get can be used to get the address of the END event, which can be
 *   used to count the number of transfers. If @ref NRF_DRV_SPI_FLAG_REPEATED_XFER is used,
 *   the driver does not set the instance into busy state, so you must ensure that the next
 *   transfers are set up when SPIM is not active. Supported only by SPIM.
 * @note Function is intended to be used only in non-blocking mode.
 *
 * @param p_instance  Pointer to the driver instance structure.
 * @param p_xfer_desc Pointer to the transfer descriptor.
 * @param flags       Transfer options (0 for default settings).
 *
 * @retval NRF_SUCCESS             If the procedure was successful.
 * @retval NRF_ERROR_BUSY          If the driver is not ready for a new transfer.
 * @retval NRF_ERROR_NOT_SUPPORTED If the provided parameters are not supported.
 * @retval NRF_ERROR_INVALID_ADDR  If the provided buffers are not placed in the Data
 *                                 RAM region.
 */
__STATIC_INLINE
ret_code_t nrf_drv_spi_xfer(nrf_drv_spi_t     const * const p_instance,
                            nrf_drv_spi_xfer_desc_t const * p_xfer_desc,
                            uint32_t                        flags);

/**
 * @brief Function for returning the address of a SPIM start task.
 *
 * This function should be used if @ref nrf_drv_spi_xfer was called with the flag @ref NRF_DRV_SPI_FLAG_HOLD_XFER.
 * In that case, the transfer is not started by the driver, but it must be started externally by PPI.
 *
 * @param[in]  p_instance Pointer to the driver instance structure.
 *
 * @return     Start task address.
 */
__STATIC_INLINE
uint32_t nrf_drv_spi_start_task_get(nrf_drv_spi_t const * p_instance);

/**
 * @brief Function for returning the address of a END SPIM event.
 *
 * A END event can be used to detect the end of a transfer if the @ref NRF_DRV_SPI_FLAG_NO_XFER_EVT_HANDLER
 * option is used.
 *
 * @param[in]  p_instance Pointer to the driver instance structure.
 *
 * @return     END event address.
 */
__STATIC_INLINE
uint32_t nrf_drv_spi_end_event_get(nrf_drv_spi_t const * p_instance);

/**
 * @brief Function for aborting ongoing transfer.
 *
 * @param[in]  p_instance Pointer to the driver instance structure.
 */
__STATIC_INLINE
void nrf_drv_spi_abort(nrf_drv_spi_t const * p_instance);


#ifndef SUPPRESS_INLINE_IMPLEMENTATION

#if defined(SPI_PRESENT) && !defined(SPIM_PRESENT)
#define NRF_DRV_SPI_WITH_SPI
#elif !defined(SPI_PRESENT) && defined(SPIM_PRESENT)
#define NRF_DRV_SPI_WITH_SPIM
#else
#if (NRFX_CHECK(SPI0_ENABLED) &&  NRFX_CHECK(SPI0_USE_EASY_DMA)) || \
    (NRFX_CHECK(SPI1_ENABLED) &&  NRFX_CHECK(SPI1_USE_EASY_DMA)) || \
    (NRFX_CHECK(SPI2_ENABLED) &&  NRFX_CHECK(SPI2_USE_EASY_DMA))
    #define NRF_DRV_SPI_WITH_SPIM
#endif
#if (NRFX_CHECK(SPI0_ENABLED) && !NRFX_CHECK(SPI0_USE_EASY_DMA)) || \
    (NRFX_CHECK(SPI1_ENABLED) && !NRFX_CHECK(SPI1_USE_EASY_DMA)) || \
    (NRFX_CHECK(SPI2_ENABLED) && !NRFX_CHECK(SPI2_USE_EASY_DMA))
    #define NRF_DRV_SPI_WITH_SPI
#endif
#endif
#if defined(NRF_DRV_SPI_WITH_SPIM) && defined(NRF_DRV_SPI_WITH_SPI)
    #define NRF_DRV_SPI_USE_SPIM  (p_instance->use_easy_dma)
#elif defined(NRF_DRV_SPI_WITH_SPIM)
    #define NRF_DRV_SPI_USE_SPIM  true
#else
    #define NRF_DRV_SPI_USE_SPIM  false
#endif
#define NRF_DRV_SPI_USE_SPI  (!NRF_DRV_SPI_USE_SPIM)

__STATIC_INLINE
void nrf_drv_spi_uninit(nrf_drv_spi_t const * p_instance)
{
    if (NRF_DRV_SPI_USE_SPIM)
    {
        nrfx_spim_uninit(&p_instance->u.spim);
    }
    else if (NRF_DRV_SPI_USE_SPI)
    {
        nrfx_spi_uninit(&p_instance->u.spi);
    }
}

__STATIC_INLINE
ret_code_t nrf_drv_spi_transfer(nrf_drv_spi_t const * const p_instance,
                                uint8_t const * p_tx_buffer,
                                uint8_t         tx_buffer_length,
                                uint8_t       * p_rx_buffer,
                                uint8_t         rx_buffer_length)
{
    ret_code_t result = 0;
    if (NRF_DRV_SPI_USE_SPIM)
    {
    #ifdef SPIM_PRESENT
        nrfx_spim_xfer_desc_t const spim_xfer_desc =
        {
            .p_tx_buffer = p_tx_buffer,
            .tx_length   = tx_buffer_length,
            .p_rx_buffer = p_rx_buffer,
            .rx_length   = rx_buffer_length,
        };
        result = nrfx_spim_xfer(&p_instance->u.spim, &spim_xfer_desc, 0);
    #endif
    }
    else if (NRF_DRV_SPI_USE_SPI)
    {
    #ifdef SPI_PRESENT
        nrfx_spi_xfer_desc_t const spi_xfer_desc =
        {
            .p_tx_buffer = p_tx_buffer,
            .tx_length   = tx_buffer_length,
            .p_rx_buffer = p_rx_buffer,
            .rx_length   = rx_buffer_length,
        };
        result = nrfx_spi_xfer(&p_instance->u.spi, &spi_xfer_desc, 0);
    #endif
    }
    return result;
}

__STATIC_INLINE
ret_code_t nrf_drv_spi_xfer(nrf_drv_spi_t     const * const p_instance,
                            nrf_drv_spi_xfer_desc_t const * p_xfer_desc,
                            uint32_t                        flags)
{
    ret_code_t result = 0;
    if (NRF_DRV_SPI_USE_SPIM)
    {
    #ifdef SPIM_PRESENT
        nrfx_spim_xfer_desc_t const spim_xfer_desc =
        {
            .p_tx_buffer = p_xfer_desc->p_tx_buffer,
            .tx_length   = p_xfer_desc->tx_length,
            .p_rx_buffer = p_xfer_desc->p_rx_buffer,
            .rx_length   = p_xfer_desc->rx_length,
        };
        result = nrfx_spim_xfer(&p_instance->u.spim, &spim_xfer_desc, flags);
    #endif
    }
    else if (NRF_DRV_SPI_USE_SPI)
    {
    #ifdef SPI_PRESENT
        nrfx_spi_xfer_desc_t const spi_xfer_desc =
        {
            .p_tx_buffer = p_xfer_desc->p_tx_buffer,
            .tx_length   = p_xfer_desc->tx_length,
            .p_rx_buffer = p_xfer_desc->p_rx_buffer,
            .rx_length   = p_xfer_desc->rx_length,
        };
        result = nrfx_spi_xfer(&p_instance->u.spi, &spi_xfer_desc, flags);
    #endif
    }
    return result;
}

__STATIC_INLINE
uint32_t nrf_drv_spi_start_task_get(nrf_drv_spi_t const * p_instance)
{
    uint32_t result = 0;
    if (NRF_DRV_SPI_USE_SPIM)
    {
        result = nrfx_spim_start_task_get(&p_instance->u.spim);
    }
    else if (NRF_DRV_SPI_USE_SPI)
    {
        NRFX_ASSERT(false); // not supported
        result = 0;
    }
    return result;
}

__STATIC_INLINE
uint32_t nrf_drv_spi_end_event_get(nrf_drv_spi_t const * p_instance)
{
    uint32_t result = 0;
    if (NRF_DRV_SPI_USE_SPIM)
    {
        result = nrfx_spim_end_event_get(&p_instance->u.spim);
    }
    else if (NRF_DRV_SPI_USE_SPI)
    {
        NRFX_ASSERT(false); // not supported
        result = 0;
    }
    return result;
}

__STATIC_INLINE
void nrf_drv_spi_abort(nrf_drv_spi_t const * p_instance)
{
    if (NRF_DRV_SPI_USE_SPIM)
    {
        nrfx_spim_abort(&p_instance->u.spim);
    }
    else if (NRF_DRV_SPI_USE_SPI)
    {
        nrfx_spi_abort(&p_instance->u.spi);
    }
}

#endif // SUPPRESS_INLINE_IMPLEMENTATION

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_SPI_H__
