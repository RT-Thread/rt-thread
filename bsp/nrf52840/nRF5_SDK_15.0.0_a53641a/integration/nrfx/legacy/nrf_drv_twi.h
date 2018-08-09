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

#ifndef NRF_DRV_TWI_H__
#define NRF_DRV_TWI_H__

#include <nrfx.h>
#ifdef TWIM_PRESENT
    #include <nrfx_twim.h>
#else
    // Compilers (at least the smart ones) will remove the TWIM related code
    // (blocks starting with "if (NRF_DRV_TWI_USE_TWIM)") when it is not used,
    // but to perform the compilation they need the following definitions.
    #define nrfx_twim_init(...)                 0
    #define nrfx_twim_uninit(...)
    #define nrfx_twim_enable(...)
    #define nrfx_twim_disable(...)
    #define nrfx_twim_tx(...)                   0
    #define nrfx_twim_rx(...)                   0
    #define nrfx_twim_is_busy(...)              0
    #define nrfx_twim_start_task_get(...)       0
    #define nrfx_twim_stopped_event_get(...)    0
#endif

#ifdef TWI_PRESENT
    #include <nrfx_twi.h>
#else
    // Compilers (at least the smart ones) will remove the TWI related code
    // (blocks starting with "if (NRF_DRV_TWI_USE_TWI)") when it is not used,
    // but to perform the compilation they need the following definitions.
    #define nrfx_twi_init(...)                  0
    #define nrfx_twi_uninit(...)
    #define nrfx_twi_enable(...)
    #define nrfx_twi_disable(...)
    #define nrfx_twi_tx(...)                    0
    #define nrfx_twi_rx(...)                    0
    #define nrfx_twi_is_busy(...)               0
    #define nrfx_twi_data_count_get(...)        0
    #define nrfx_twi_stopped_event_get(...)     0

    // This part is for old modules that use directly TWI HAL definitions
    // (to make them compilable for chips that have only TWIM).
    #define NRF_TWI_ERROR_ADDRESS_NACK  NRF_TWIM_ERROR_ADDRESS_NACK
    #define NRF_TWI_ERROR_DATA_NACK     NRF_TWIM_ERROR_DATA_NACK
    #define NRF_TWI_FREQ_100K           NRF_TWIM_FREQ_100K
    #define NRF_TWI_FREQ_250K           NRF_TWIM_FREQ_250K
    #define NRF_TWI_FREQ_400K           NRF_TWIM_FREQ_400K
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_twi TWI driver - legacy layer
 * @{
 * @ingroup  nrf_twi
 * @brief    Layer providing compatibility with the former API.
 */

/**
 * @brief Structure for the TWI master driver instance.
 */
typedef struct
{
    uint8_t inst_idx;
    union
    {
#ifdef TWIM_PRESENT
        nrfx_twim_t twim;
#endif
#ifdef TWI_PRESENT
        nrfx_twi_t  twi;
#endif
    } u;
    bool    use_easy_dma;
} nrf_drv_twi_t;

/**
 * @brief Macro for creating a TWI master driver instance.
 */
#define NRF_DRV_TWI_INSTANCE(id)    NRF_DRV_TWI_INSTANCE_(id)
#define NRF_DRV_TWI_INSTANCE_(id)   NRF_DRV_TWI_INSTANCE_ ## id
#if NRFX_CHECK(NRFX_TWIM0_ENABLED)
    #define NRF_DRV_TWI_INSTANCE_0 \
        { 0, { .twim = NRFX_TWIM_INSTANCE(0) }, true }
#elif NRFX_CHECK(NRFX_TWI0_ENABLED)
    #define NRF_DRV_TWI_INSTANCE_0 \
        { 0, { .twi = NRFX_TWI_INSTANCE(0) }, false }
#endif
#if NRFX_CHECK(NRFX_TWIM1_ENABLED)
    #define NRF_DRV_TWI_INSTANCE_1 \
        { 1, { .twim = NRFX_TWIM_INSTANCE(1) }, true }
#elif NRFX_CHECK(NRFX_TWI1_ENABLED)
    #define NRF_DRV_TWI_INSTANCE_1 \
        { 1, { .twi = NRFX_TWI_INSTANCE(1) }, false }
#endif

/**
 * @brief TWI master clock frequency.
 */
typedef enum
{
    NRF_DRV_TWI_FREQ_100K = NRF_TWI_FREQ_100K , ///< 100 kbps.
    NRF_DRV_TWI_FREQ_250K = NRF_TWI_FREQ_250K , ///< 250 kbps.
    NRF_DRV_TWI_FREQ_400K = NRF_TWI_FREQ_400K   ///< 400 kbps.
} nrf_drv_twi_frequency_t;

/**
 * @brief Structure for the TWI master driver instance configuration.
 */
typedef struct
{
    uint32_t                scl;                 ///< SCL pin number.
    uint32_t                sda;                 ///< SDA pin number.
    nrf_drv_twi_frequency_t frequency;           ///< TWI frequency.
    uint8_t                 interrupt_priority;  ///< Interrupt priority.
    bool                    clear_bus_init;      ///< Clear bus during init.
    bool                    hold_bus_uninit;     ///< Hold pull up state on gpio pins after uninit.
} nrf_drv_twi_config_t;

/**
 * @brief TWI master driver instance default configuration.
 */
#define NRF_DRV_TWI_DEFAULT_CONFIG                                               \
{                                                                                \
    .frequency          = (nrf_drv_twi_frequency_t)TWI_DEFAULT_CONFIG_FREQUENCY, \
    .scl                = 31,                                                    \
    .sda                = 31,                                                    \
    .interrupt_priority = TWI_DEFAULT_CONFIG_IRQ_PRIORITY,                       \
    .clear_bus_init     = TWI_DEFAULT_CONFIG_CLR_BUS_INIT,                       \
    .hold_bus_uninit    = TWI_DEFAULT_CONFIG_HOLD_BUS_UNINIT,                    \
}

#define NRF_DRV_TWI_FLAG_TX_POSTINC          (1UL << 0) /**< TX buffer address incremented after transfer. */
#define NRF_DRV_TWI_FLAG_RX_POSTINC          (1UL << 1) /**< RX buffer address incremented after transfer. */
#define NRF_DRV_TWI_FLAG_NO_XFER_EVT_HANDLER (1UL << 2) /**< Interrupt after each transfer is suppressed, and the event handler is not called. */
#define NRF_DRV_TWI_FLAG_HOLD_XFER           (1UL << 3) /**< Set up the transfer but do not start it. */
#define NRF_DRV_TWI_FLAG_REPEATED_XFER       (1UL << 4) /**< Flag indicating that the transfer will be executed multiple times. */
#define NRF_DRV_TWI_FLAG_TX_NO_STOP          (1UL << 5) /**< Flag indicating that the TX transfer will not end with a stop condition. */

/**
 * @brief TWI master driver event types.
 */
typedef enum
{
    NRF_DRV_TWI_EVT_DONE,         ///< Transfer completed event.
    NRF_DRV_TWI_EVT_ADDRESS_NACK, ///< Error event: NACK received after sending the address.
    NRF_DRV_TWI_EVT_DATA_NACK     ///< Error event: NACK received after sending a data byte.
} nrf_drv_twi_evt_type_t;

/**
 * @brief TWI master driver transfer types.
 */
typedef enum
{
    NRF_DRV_TWI_XFER_TX,          ///< TX transfer.
    NRF_DRV_TWI_XFER_RX,          ///< RX transfer.
    NRF_DRV_TWI_XFER_TXRX,        ///< TX transfer followed by RX transfer with repeated start.
    NRF_DRV_TWI_XFER_TXTX         ///< TX transfer followed by TX transfer with repeated start.
} nrf_drv_twi_xfer_type_t;

/**
 * @brief Structure for a TWI transfer descriptor.
 */
typedef struct
{
    nrf_drv_twi_xfer_type_t type;             ///< Type of transfer.
    uint8_t                 address;          ///< Slave address.
    uint8_t                 primary_length;   ///< Number of bytes transferred.
    uint8_t                 secondary_length; ///< Number of bytes transferred.
    uint8_t *               p_primary_buf;    ///< Pointer to transferred data.
    uint8_t *               p_secondary_buf;  ///< Pointer to transferred data.
} nrf_drv_twi_xfer_desc_t;


/**@brief Macro for setting the TX transfer descriptor. */
#define NRF_DRV_TWI_XFER_DESC_TX(addr, p_data, length)                 \
    {                                                                  \
        .type = NRF_DRV_TWI_XFER_TX,                                   \
        .address = addr,                                               \
        .primary_length = length,                                      \
        .p_primary_buf  = p_data,                                      \
    }

/**@brief Macro for setting the RX transfer descriptor. */
#define NRF_DRV_TWI_XFER_DESC_RX(addr, p_data, length)                 \
    {                                                                  \
        .type = NRF_DRV_TWI_XFER_RX,                                   \
        .address = addr,                                               \
        .primary_length = length,                                      \
        .p_primary_buf  = p_data,                                      \
    }

/**@brief Macro for setting the TXRX transfer descriptor. */
#define NRF_DRV_TWI_XFER_DESC_TXRX(addr, p_tx, tx_len, p_rx, rx_len)   \
    {                                                                  \
        .type = NRF_DRV_TWI_XFER_TXRX,                                 \
        .address = addr,                                               \
        .primary_length   = tx_len,                                    \
        .secondary_length = rx_len,                                    \
        .p_primary_buf    = p_tx,                                      \
        .p_secondary_buf  = p_rx,                                      \
    }

/**@brief Macro for setting the TXTX transfer descriptor. */
#define NRF_DRV_TWI_XFER_DESC_TXTX(addr, p_tx, tx_len, p_tx2, tx_len2) \
    {                                                                  \
        .type = NRF_DRV_TWI_XFER_TXTX,                                 \
        .address = addr,                                               \
        .primary_length   = tx_len,                                    \
        .secondary_length = tx_len2,                                   \
        .p_primary_buf    = p_tx,                                      \
        .p_secondary_buf  = p_tx2,                                     \
    }

/**
 * @brief Structure for a TWI event.
 */
typedef struct
{
    nrf_drv_twi_evt_type_t  type;      ///< Event type.
    nrf_drv_twi_xfer_desc_t xfer_desc; ///< Transfer details.
} nrf_drv_twi_evt_t;

/**
 * @brief TWI event handler prototype.
 */
typedef void (* nrf_drv_twi_evt_handler_t)(nrf_drv_twi_evt_t const * p_event,
                                           void *                    p_context);

/**
 * @brief Function for initializing the TWI driver instance.
 *
 * @param[in] p_instance      Pointer to the driver instance structure.
 * @param[in] p_config        Initial configuration.
 * @param[in] event_handler   Event handler provided by the user. If NULL, blocking mode is enabled.
 * @param[in] p_context       Context passed to event handler.
 *
 * @retval NRF_SUCCESS             If initialization was successful.
 * @retval NRF_ERROR_INVALID_STATE If the driver is in invalid state.
 * @retval NRF_ERROR_BUSY          If some other peripheral with the same
 *                                 instance ID is already in use. This is
 *                                 possible only if PERIPHERAL_RESOURCE_SHARING_ENABLED
 *                                 is set to a value other than zero.
 */
ret_code_t nrf_drv_twi_init(nrf_drv_twi_t const *        p_instance,
                            nrf_drv_twi_config_t const * p_config,
                            nrf_drv_twi_evt_handler_t    event_handler,
                            void *                       p_context);

/**
 * @brief Function for uninitializing the TWI instance.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
__STATIC_INLINE
void nrf_drv_twi_uninit(nrf_drv_twi_t const * p_instance);

/**
 * @brief Function for enabling the TWI instance.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
__STATIC_INLINE
void nrf_drv_twi_enable(nrf_drv_twi_t const * p_instance);

/**
 * @brief Function for disabling the TWI instance.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
__STATIC_INLINE
void nrf_drv_twi_disable(nrf_drv_twi_t const * p_instance);

/**
 * @brief Function for sending data to a TWI slave.
 *
 * The transmission will be stopped when an error occurs. If a transfer is ongoing,
 * the function returns the error code @ref NRF_ERROR_BUSY.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] address    Address of a specific slave device (only 7 LSB).
 * @param[in] p_data     Pointer to a transmit buffer.
 * @param[in] length     Number of bytes to send.
 * @param[in] no_stop    If set, the stop condition is not generated on the bus
 *                       after the transfer has completed successfully (allowing
 *                       for a repeated start in the next transfer).
 *
 * @retval NRF_SUCCESS                  If the procedure was successful.
 * @retval NRF_ERROR_BUSY               If the driver is not ready for a new transfer.
 * @retval NRF_ERROR_INTERNAL           If an error was detected by hardware.
 * @retval NRF_ERROR_INVALID_ADDR       If the EasyDMA is used and memory adress in not in RAM.
 * @retval NRF_ERROR_DRV_TWI_ERR_ANACK  If NACK received after sending the address in polling mode.
 * @retval NRF_ERROR_DRV_TWI_ERR_DNACK  If NACK received after sending a data byte in polling mode.
 */
__STATIC_INLINE
ret_code_t nrf_drv_twi_tx(nrf_drv_twi_t const * p_instance,
                          uint8_t               address,
                          uint8_t const *       p_data,
                          uint8_t               length,
                          bool                  no_stop);

/**
 * @brief Function for reading data from a TWI slave.
 *
 * The transmission will be stopped when an error occurs. If a transfer is ongoing,
 * the function returns the error code @ref NRF_ERROR_BUSY.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] address    Address of a specific slave device (only 7 LSB).
 * @param[in] p_data     Pointer to a receive buffer.
 * @param[in] length     Number of bytes to be received.
 *
 * @retval NRF_SUCCESS                    If the procedure was successful.
 * @retval NRF_ERROR_BUSY                 If the driver is not ready for a new transfer.
 * @retval NRF_ERROR_INTERNAL             If an error was detected by hardware.
 * @retval NRF_ERROR_DRV_TWI_ERR_OVERRUN  If the unread data was replaced by new data
 * @retval NRF_ERROR_DRV_TWI_ERR_ANACK    If NACK received after sending the address in polling mode.
 * @retval NRF_ERROR_DRV_TWI_ERR_DNACK    If NACK received after sending a data byte in polling mode.
 */
__STATIC_INLINE
ret_code_t nrf_drv_twi_rx(nrf_drv_twi_t const * p_instance,
                          uint8_t               address,
                          uint8_t *             p_data,
                          uint8_t               length);

/**
 * @brief Function for preparing a TWI transfer.
 *
 * The following transfer types can be configured (@ref nrf_drv_twi_xfer_desc_t::type):
 * - @ref NRF_DRV_TWI_XFER_TXRX<span></span>: Write operation followed by a read operation (without STOP condition in between).
 * - @ref NRF_DRV_TWI_XFER_TXTX<span></span>: Write operation followed by a write operation (without STOP condition in between).
 * - @ref NRF_DRV_TWI_XFER_TX<span></span>:   Write operation (with or without STOP condition).
 * - @ref NRF_DRV_TWI_XFER_RX<span></span>:   Read operation  (with STOP condition).
 *
 * Additional options are provided using the flags parameter:
 * - @ref NRF_DRV_TWI_FLAG_TX_POSTINC and @ref NRF_DRV_TWI_FLAG_RX_POSTINC<span></span>: Post-incrementation of buffer addresses. Supported only by TWIM.
 * - @ref NRF_DRV_TWI_FLAG_NO_XFER_EVT_HANDLER<span></span>: No user event handler after transfer completion. In most cases, this also means no interrupt at the end of the transfer.
 * - @ref NRF_DRV_TWI_FLAG_HOLD_XFER<span></span>: Driver is not starting the transfer. Use this flag if the transfer is triggered externally by PPI. Supported only by TWIM.
 *   Use @ref nrf_drv_twi_start_task_get to get the address of the start task.
 * - @ref NRF_DRV_TWI_FLAG_REPEATED_XFER<span></span>: Prepare for repeated transfers. You can set up a number of transfers that will be triggered externally (for example by PPI).
 *   An example is a TXRX transfer with the options @ref NRF_DRV_TWI_FLAG_RX_POSTINC, @ref NRF_DRV_TWI_FLAG_NO_XFER_EVT_HANDLER, and @ref NRF_DRV_TWI_FLAG_REPEATED_XFER.
 *   After the transfer is set up, a set of transfers can be triggered by PPI that will read, for example, the same register of an
 *   external component and put it into a RAM buffer without any interrupts. @ref nrf_drv_twi_stopped_event_get can be used to get the
 *   address of the STOPPED event, which can be used to count the number of transfers. If @ref NRF_DRV_TWI_FLAG_REPEATED_XFER is used,
 *   the driver does not set the driver instance into busy state, so you must ensure that the next transfers are set up
 *   when TWIM is not active. Supported only by TWIM.
 * - @ref NRF_DRV_TWI_FLAG_TX_NO_STOP<span></span>: No stop condition after TX transfer.
 *
 * @note
 * Some flag combinations are invalid:
 * - @ref NRF_DRV_TWI_FLAG_TX_NO_STOP with @ref nrf_drv_twi_xfer_desc_t::type different than @ref NRF_DRV_TWI_XFER_TX
 * - @ref NRF_DRV_TWI_FLAG_REPEATED_XFER with @ref nrf_drv_twi_xfer_desc_t::type set to @ref NRF_DRV_TWI_XFER_TXTX
 *
 * If @ref nrf_drv_twi_xfer_desc_t::type is set to @ref NRF_DRV_TWI_XFER_TX and the @ref NRF_DRV_TWI_FLAG_TX_NO_STOP and @ref NRF_DRV_TWI_FLAG_REPEATED_XFER
 * flags are set, two tasks must be used to trigger a transfer: TASKS_RESUME followed by TASKS_STARTTX. If no stop condition is generated,
 * TWIM is in SUSPENDED state. Therefore, it must be resumed before the transfer can be started.
 *
 * @note
 * This function should be used only if the instance is configured to work in non-blocking mode. If the function is used in blocking mode, the driver asserts.
 * @note If you are using this function with TWI, the only supported flag is @ref NRF_DRV_TWI_FLAG_TX_NO_STOP. All other flags require TWIM.
  *
 * @param[in] p_instance        Pointer to the driver instance structure.
 * @param[in] p_xfer_desc       Pointer to the transfer descriptor.
 * @param[in] flags             Transfer options (0 for default settings).
 *
 * @retval NRF_SUCCESS                    If the procedure was successful.
 * @retval NRF_ERROR_BUSY                 If the driver is not ready for a new transfer.
 * @retval NRF_ERROR_NOT_SUPPORTED        If the provided parameters are not supported.
 * @retval NRF_ERROR_INTERNAL             If an error was detected by hardware.
 * @retval NRF_ERROR_INVALID_ADDR         If the EasyDMA is used and memory adress in not in RAM
 * @retval NRF_ERROR_DRV_TWI_ERR_OVERRUN  If the unread data was replaced by new data (TXRX and RX)
 * @retval NRF_ERROR_DRV_TWI_ERR_ANACK    If NACK received after sending the address.
 * @retval NRF_ERROR_DRV_TWI_ERR_DNACK    If NACK received after sending a data byte.
 */
__STATIC_INLINE
ret_code_t nrf_drv_twi_xfer(nrf_drv_twi_t           const * p_instance,
                            nrf_drv_twi_xfer_desc_t const * p_xfer_desc,
                            uint32_t                        flags);

/**
 * @brief Function for checking the TWI driver state.
 *
 * @param[in] p_instance TWI instance.
 *
 * @retval true  If the TWI driver is currently busy performing a transfer.
 * @retval false If the TWI driver is ready for a new transfer.
 */
__STATIC_INLINE
bool nrf_drv_twi_is_busy(nrf_drv_twi_t const * p_instance);

/**
 * @brief Function for getting the transferred data count.
 *
 * This function provides valid results only in legacy mode.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @return     Data count.
 */
__STATIC_INLINE
uint32_t nrf_drv_twi_data_count_get(nrf_drv_twi_t const * const p_instance);

/**
 * @brief Function for returning the address of a TWI/TWIM start task.
 *
 * This function should be used if @ref nrf_drv_twi_xfer was called with the flag @ref NRF_DRV_TWI_FLAG_HOLD_XFER.
 * In that case, the transfer is not started by the driver, but it must be started externally by PPI.
 *
 * @param[in]  p_instance Pointer to the driver instance structure.
 * @param[in]  xfer_type  Transfer type used in the last call of the @ref nrf_drv_twi_xfer function.
 *
 * @return     Start task address (TX or RX) depending on the value of xfer_type.
 */
__STATIC_INLINE
uint32_t nrf_drv_twi_start_task_get(nrf_drv_twi_t const * p_instance, nrf_drv_twi_xfer_type_t xfer_type);

/**
 * @brief Function for returning the address of a STOPPED TWI/TWIM event.
 *
 * A STOPPED event can be used to detect the end of a transfer if the @ref NRF_DRV_TWI_FLAG_NO_XFER_EVT_HANDLER
 * option is used.
 *
 * @param[in]  p_instance Pointer to the driver instance structure.
 *
 * @return     STOPPED event address.
 */
__STATIC_INLINE
uint32_t nrf_drv_twi_stopped_event_get(nrf_drv_twi_t const * p_instance);


#ifndef SUPPRESS_INLINE_IMPLEMENTATION

#if defined(TWI_PRESENT) && !defined(TWIM_PRESENT)
#define NRF_DRV_TWI_WITH_TWI
#elif !defined(TWI_PRESENT) && defined(TWIM_PRESENT)
#define NRF_DRV_TWI_WITH_TWIM
#else
#if (NRFX_CHECK(TWI0_ENABLED) &&  NRFX_CHECK(TWI0_USE_EASY_DMA)) || \
    (NRFX_CHECK(TWI1_ENABLED) &&  NRFX_CHECK(TWI1_USE_EASY_DMA))
    #define NRF_DRV_TWI_WITH_TWIM
#endif
#if (NRFX_CHECK(TWI0_ENABLED) && !NRFX_CHECK(TWI0_USE_EASY_DMA)) || \
    (NRFX_CHECK(TWI1_ENABLED) && !NRFX_CHECK(TWI1_USE_EASY_DMA))
    #define NRF_DRV_TWI_WITH_TWI
#endif
#endif
#if defined(NRF_DRV_TWI_WITH_TWIM) && defined(NRF_DRV_TWI_WITH_TWI)
    #define NRF_DRV_TWI_USE_TWIM  (p_instance->use_easy_dma)
#elif defined(NRF_DRV_TWI_WITH_TWIM)
    #define NRF_DRV_TWI_USE_TWIM  true
#else
    #define NRF_DRV_TWI_USE_TWIM  false
#endif
#define NRF_DRV_TWI_USE_TWI  (!NRF_DRV_TWI_USE_TWIM)

__STATIC_INLINE
void nrf_drv_twi_uninit(nrf_drv_twi_t const * p_instance)
{
    if (NRF_DRV_TWI_USE_TWIM)
    {
        nrfx_twim_uninit(&p_instance->u.twim);
    }
    else if (NRF_DRV_TWI_USE_TWI)
    {
        nrfx_twi_uninit(&p_instance->u.twi);
    }
}

__STATIC_INLINE
void nrf_drv_twi_enable(nrf_drv_twi_t const * p_instance)
{
    if (NRF_DRV_TWI_USE_TWIM)
    {
        nrfx_twim_enable(&p_instance->u.twim);
    }
    else if (NRF_DRV_TWI_USE_TWI)
    {
        nrfx_twi_enable(&p_instance->u.twi);
    }
}

__STATIC_INLINE
void nrf_drv_twi_disable(nrf_drv_twi_t const * p_instance)
{
    if (NRF_DRV_TWI_USE_TWIM)
    {
        nrfx_twim_disable(&p_instance->u.twim);
    }
    else if (NRF_DRV_TWI_USE_TWI)
    {
        nrfx_twi_disable(&p_instance->u.twi);
    }
}

__STATIC_INLINE
ret_code_t nrf_drv_twi_tx(nrf_drv_twi_t const * p_instance,
                          uint8_t               address,
                          uint8_t const *       p_data,
                          uint8_t               length,
                          bool                  no_stop)
{
    ret_code_t result = 0;
    if (NRF_DRV_TWI_USE_TWIM)
    {
        result = nrfx_twim_tx(&p_instance->u.twim,
                                address, p_data, length, no_stop);
    }
    else if (NRF_DRV_TWI_USE_TWI)
    {
        result = nrfx_twi_tx(&p_instance->u.twi,
                               address, p_data, length, no_stop);
    }
    return result;
}

__STATIC_INLINE
ret_code_t nrf_drv_twi_rx(nrf_drv_twi_t const * p_instance,
                          uint8_t               address,
                          uint8_t *             p_data,
                          uint8_t               length)
{
    ret_code_t result = 0;
    if (NRF_DRV_TWI_USE_TWIM)
    {
        result = nrfx_twim_rx(&p_instance->u.twim,
                                address, p_data, length);
    }
    else if (NRF_DRV_TWI_USE_TWI)
    {
        result = nrfx_twi_rx(&p_instance->u.twi,
                               address, p_data, length);
    }
    return result;
}

__STATIC_INLINE
ret_code_t nrf_drv_twi_xfer(nrf_drv_twi_t           const * p_instance,
                            nrf_drv_twi_xfer_desc_t const * p_xfer_desc,
                            uint32_t                        flags)
{
    ret_code_t result = 0;
    if (NRF_DRV_TWI_USE_TWIM)
    {
    #ifdef TWIM_PRESENT
        nrfx_twim_xfer_desc_t const twim_xfer_desc =
        {
            .type             = (nrfx_twim_xfer_type_t)p_xfer_desc->type,
            .address          = p_xfer_desc->address,
            .primary_length   = p_xfer_desc->primary_length,
            .secondary_length = p_xfer_desc->secondary_length,
            .p_primary_buf    = p_xfer_desc->p_primary_buf,
            .p_secondary_buf  = p_xfer_desc->p_secondary_buf,
        };
        result = nrfx_twim_xfer(&p_instance->u.twim, &twim_xfer_desc, flags);
    #endif
    }
    else if (NRF_DRV_TWI_USE_TWI)
    {
    #ifdef TWI_PRESENT
        nrfx_twi_xfer_desc_t const twi_xfer_desc =
        {
            .type             = (nrfx_twi_xfer_type_t)p_xfer_desc->type,
            .address          = p_xfer_desc->address,
            .primary_length   = p_xfer_desc->primary_length,
            .secondary_length = p_xfer_desc->secondary_length,
            .p_primary_buf    = p_xfer_desc->p_primary_buf,
            .p_secondary_buf  = p_xfer_desc->p_secondary_buf,
        };
        result = nrfx_twi_xfer(&p_instance->u.twi, &twi_xfer_desc, flags);
    #endif
    }
    return result;
}

__STATIC_INLINE
bool nrf_drv_twi_is_busy(nrf_drv_twi_t const * p_instance)
{
    bool result = 0;
    if (NRF_DRV_TWI_USE_TWIM)
    {
        result = nrfx_twim_is_busy(&p_instance->u.twim);
    }
    else if (NRF_DRV_TWI_USE_TWI)
    {
        result = nrfx_twi_is_busy(&p_instance->u.twi);
    }
    return result;
}

__STATIC_INLINE
uint32_t nrf_drv_twi_data_count_get(nrf_drv_twi_t const * const p_instance)
{
    uint32_t result = 0;
    if (NRF_DRV_TWI_USE_TWIM)
    {
        NRFX_ASSERT(false); // not supported
        result = 0;
    }
    else if (NRF_DRV_TWI_USE_TWI)
    {
        result = nrfx_twi_data_count_get(&p_instance->u.twi);
    }
    return result;
}

__STATIC_INLINE
uint32_t nrf_drv_twi_start_task_get(nrf_drv_twi_t const * p_instance,
                                    nrf_drv_twi_xfer_type_t xfer_type)
{
    uint32_t result = 0;
    if (NRF_DRV_TWI_USE_TWIM)
    {
        result = nrfx_twim_start_task_get(&p_instance->u.twim,
                                          (nrfx_twim_xfer_type_t)xfer_type);
    }
    else if (NRF_DRV_TWI_USE_TWI)
    {
        NRFX_ASSERT(false); // not supported
        result = 0;
    }
    return result;
}

__STATIC_INLINE
uint32_t nrf_drv_twi_stopped_event_get(nrf_drv_twi_t const * p_instance)
{
    uint32_t result = 0;
    if (NRF_DRV_TWI_USE_TWIM)
    {
        result = nrfx_twim_stopped_event_get(&p_instance->u.twim);
    }
    else if (NRF_DRV_TWI_USE_TWI)
    {
        result = nrfx_twi_stopped_event_get(&p_instance->u.twi);
    }
    return result;
}

#endif // SUPPRESS_INLINE_IMPLEMENTATION

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_TWI_H__
