/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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

#ifndef NRF_DRV_USBD_H__
#define NRF_DRV_USBD_H__

#include "sdk_errors.h"
#include "nrf_usbd.h"
#include <stdint.h>
#include <stdbool.h>
#include "app_util.h"
#include "nrf_drv_usbd_errata.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_usbd USB Device HAL and driver
 * @ingroup nrf_drivers
 * @brief @tagAPI52840 USB Device APIs.
 * @details The USB Device  HAL provides basic APIs for accessing
 * the registers of the USBD.
 * The USB Device driver provides APIs on a higher level.
 *
 * @{
 */

/**
 * @name Possible schemes of DMA scheduling
 *
 * Definition of available configuration constants used by DMA scheduler
 * @{
 */
    /**
     * @brief Highly prioritized access
     *
     * Endpoint with lower number has always higher priority and its data would
     * be transfered first.
     * OUT endpoints ale processed before IN endpoints
     */
    #define NRF_DRV_USBD_DMASCHEDULER_PRIORITIZED 0

    /**
     * @brief Round robin scheme
     *
     * All endpoints are processed in round-robin scheme.
     * It means that when one endpoint is processed next in order would be
     * the nearest with lower number.
     * When no endpoints with lower number requires processing - then
     * all endpoints from 0 are tested.
     */
    #define NRF_DRV_USBD_DMASCHEDULER_ROUNDROBIN  1

/** @} */

/**
 * @brief Number of bytes in the endpoint
 *
 * Constant that informs about endpoint size
 */
#define NRF_DRV_USBD_EPSIZE 64

/**
 * @brief Number of bytes for isochronous endpoints
 *
 * Number of bytes for isochronous endpoints in total.
 * This number would be shared between IN and OUT endpoint.
 * It may be also assigned totaly to one endpoint.
 * @sa nrf_usbd_isosplit_set
 * @sa nrf_usbd_isosplit_get
 */
#define NRF_DRV_USBD_ISOSIZE 1024

/**
 * @brief The size of internal feeder buffer.
 *
 * @sa nrf_drv_usbd_feeder_buffer_get
 */
#define NRF_DRV_USBD_FEEDER_BUFFER_SIZE NRF_DRV_USBD_EPSIZE

/**
 * @name Macros for creating endpoint identifiers
 *
 * Auxiliary macros to be used to create Endpoint identifier that is compatible
 * with USB specification.
 * @{
 */

    /**
     * @brief Create identifier for IN endpoint
     *
     * Simple macro to create IN endpoint identifier for given endpoint number.
     *
     * @param[in] n Endpoint number.
     *
     * @return Endpoint identifier that connects endpoint number and endpoint direction.
     */
    #define NRF_DRV_USBD_EPIN(n)   ((nrf_drv_usbd_ep_t)NRF_USBD_EPIN(n))
    /**
     * @brief Create identifier for OUT endpoint
     *
     * Simple macro to create OUT endpoint identifier for given endpoint number.
     *
     * @param[in] n Endpoint number.
     *
     * @return Endpoint identifier that connects endpoint number and endpoint direction.
     */
    #define NRF_DRV_USBD_EPOUT(n)  ((nrf_drv_usbd_ep_t)NRF_USBD_EPOUT(n))

/** @} */

/**
 * @brief Endpoint identifier
 *
 * Endpoint identifier used in the driver.
 * This endpoint number is consistent with USB 2.0 specification.
 */
typedef enum
{
    NRF_DRV_USBD_EPOUT0 = NRF_USBD_EPOUT(0), /**< Endpoint OUT 0 */
    NRF_DRV_USBD_EPOUT1 = NRF_USBD_EPOUT(1), /**< Endpoint OUT 1 */
    NRF_DRV_USBD_EPOUT2 = NRF_USBD_EPOUT(2), /**< Endpoint OUT 2 */
    NRF_DRV_USBD_EPOUT3 = NRF_USBD_EPOUT(3), /**< Endpoint OUT 3 */
    NRF_DRV_USBD_EPOUT4 = NRF_USBD_EPOUT(4), /**< Endpoint OUT 4 */
    NRF_DRV_USBD_EPOUT5 = NRF_USBD_EPOUT(5), /**< Endpoint OUT 5 */
    NRF_DRV_USBD_EPOUT6 = NRF_USBD_EPOUT(6), /**< Endpoint OUT 6 */
    NRF_DRV_USBD_EPOUT7 = NRF_USBD_EPOUT(7), /**< Endpoint OUT 7 */
    NRF_DRV_USBD_EPOUT8 = NRF_USBD_EPOUT(8), /**< Endpoint OUT 8 */

    NRF_DRV_USBD_EPIN0  = NRF_USBD_EPIN(0), /**< Endpoint IN 0 */
    NRF_DRV_USBD_EPIN1  = NRF_USBD_EPIN(1), /**< Endpoint IN 1 */
    NRF_DRV_USBD_EPIN2  = NRF_USBD_EPIN(2), /**< Endpoint IN 2 */
    NRF_DRV_USBD_EPIN3  = NRF_USBD_EPIN(3), /**< Endpoint IN 3 */
    NRF_DRV_USBD_EPIN4  = NRF_USBD_EPIN(4), /**< Endpoint IN 4 */
    NRF_DRV_USBD_EPIN5  = NRF_USBD_EPIN(5), /**< Endpoint IN 5 */
    NRF_DRV_USBD_EPIN6  = NRF_USBD_EPIN(6), /**< Endpoint IN 6 */
    NRF_DRV_USBD_EPIN7  = NRF_USBD_EPIN(7), /**< Endpoint IN 7 */
    NRF_DRV_USBD_EPIN8  = NRF_USBD_EPIN(8), /**< Endpoint IN 8 */
}nrf_drv_usbd_ep_t;

/**
 * @brief Events generated by the library
 *
 * Enumeration of possible events that may be generated by the library.
 */
typedef enum
{
    NRF_DRV_USBD_EVT_SOF,        /**< Start Of Frame event on USB bus detected */
    NRF_DRV_USBD_EVT_RESET,      /**< Reset condition on USB bus detected */
    NRF_DRV_USBD_EVT_SUSPEND,    /**< This device should go to suspend mode now */
    NRF_DRV_USBD_EVT_RESUME,     /**< This device should resume from suspend now */
    NRF_DRV_USBD_EVT_WUREQ,      /**< Wakeup request - the USBD peripheral is ready to generate WAKEUP signal after exiting low power mode. */
    NRF_DRV_USBD_EVT_SETUP,      /**< Setup frame received and decoded */
    NRF_DRV_USBD_EVT_EPTRANSFER, /**<
                                  * For Rx (OUT: Host->Device):
                                  * 1. The packet has been received but there is no buffer prepared for transfer already.
                                  * 2. Whole transfer has been finished
                                  *
                                  * For Tx (IN: Device->Host):
                                  * The last packet from requested transfer has been transfered over USB bus and acknowledged
                                  */
    NRF_DRV_USBD_EVT_CNT         /**< Number of defined events */
}nrf_drv_usbd_event_type_t;

/**
 * @brief Possible endpoint error codes
 *
 * Error codes that may be returned with @ref NRF_DRV_USBD_EVT_EPTRANSFER
 */
typedef enum
{
    NRF_USBD_EP_OK,       /**< No error */
    NRF_USBD_EP_WAITING,  /**< Data received, no buffer prepared already - waiting for configured transfer */
    NRF_USBD_EP_OVERLOAD, /**< Received number of bytes cannot fit given buffer
                           *   This error would also be returned when next_transfer function has been defined
                           *   but currently received data cannot fit completely in current buffer.
                           *   No data split from single endpoint transmission is supported.
                           *
                           *   When this error is reported - data is left inside endpoint buffer.
                           *   Clear endpoint or prepare new buffer and read it.
                           */
    NRF_USBD_EP_ABORTED,  /**< EP0 transfer can be aborted when new setup comes.
                           *   Any other transfer can be aborted by USB reset or library stopping.
                           */
}nrf_drv_usbd_ep_status_t;


/**
 * @brief Event structure
 *
 * Structure passed to event handler
 */
typedef struct
{
    nrf_drv_usbd_event_type_t type;
    union
    {
        struct{
            uint16_t framecnt; //!< Current value of frame counter
        }sof; //!< Data aviable for @ref NRF_DRV_USBD_EVT_SOF
        struct{
            nrf_drv_usbd_ep_t        ep;     //!< Endpoint number
        }isocrc;
        struct{
            nrf_drv_usbd_ep_t        ep;     //!< Endpoint number
            nrf_drv_usbd_ep_status_t status; //!< Status for the endpoint
        }eptransfer;
    }data;
}nrf_drv_usbd_evt_t;

/**
 * @brief USBD event callback function type.
 *
 * @param[in] p_event Event information structure.
 */
typedef void (*nrf_drv_usbd_event_handler_t)(nrf_drv_usbd_evt_t const * const p_event);

/**
 * @brief Universal data pointer.
 *
 * Universal data pointer that can be used for any type of transfer.
 */
typedef union
{
    void const * tx; //!< Constant TX buffer pointer.
    void * rx;       //!< Writable RX buffer pointer.
    uint32_t ptr;    //!< Numeric value used internally by the library.
}nrf_drv_usbd_data_ptr_t;

/**
 * @brief Structure to be filled with information about the next transfer.
 *
 * This is used mainly for transfer feeders and consumers.
 * It describes a single endpoint transfer and therefore the size of the buffer
 * can never be higher than the endpoint size.
 */
typedef struct
{
    nrf_drv_usbd_data_ptr_t p_data; //!< Union with available data pointers used by the library.
    size_t size;                    //!< Size of the requested transfer.
}nrf_drv_usbd_ep_transfer_t;

/**
 * @brief Flags for the current transfer.
 *
 * Flags configured for the transfer that can be merged using the bitwise 'or' operator (|).
 */
typedef enum
{
    NRF_DRV_USBD_TRANSFER_ZLP_FLAG = 1U << 0, //!< Add a zero-length packet.
}nrf_drv_usbd_transfer_flags_t;

/**
 * @brief Total transfer configuration.
 *
 * This structure is used to configure total transfer information.
 * It is used by internal built-in feeders and consumers.
 */
typedef struct
{
    nrf_drv_usbd_data_ptr_t p_data; //!< Union with available data pointers used by the library.
    size_t size;                    //!< Total size of the requested transfer.
    uint32_t flags;                 //!< Transfer flags.
                                    /**< Use the @ref nrf_drv_usbd_transfer_flags_t values. */
}nrf_drv_usbd_transfer_t;


/**
 * @brief Auxiliary macro for declaring IN transfer description with flags.
 *
 * The base macro for creating transfers with any configuration option.
 *
 * @param name     Instance name.
 * @param tx_buff  Buffer to transfer.
 * @param tx_size  Transfer size.
 * @param tx_flags Flags for the transfer (see @ref nrf_drv_usbd_transfer_flags_t).
 *
 * @return Configured variable with total transfer description.
 */
#define NRF_DRV_USBD_TRANSFER_IN_FLAGS(name, tx_buff, tx_size, tx_flags) \
    const nrf_drv_usbd_transfer_t name = {                               \
       .p_data = { .tx = (tx_buff)  },                                   \
       .size = (tx_size),                                                \
       .flags = (tx_flags)                                               \
    }

/**
 * @brief Helper macro for declaring IN transfer description
 *
 * Normal transfer mode, no ZLP would be automatically generated.
 *
 * @sa nrf_drv_usbd_transfer_t
 * @sa NRF_DRV_USBD_TRANSFER_IN_ZLP
 *
 * @param name    Instance name
 * @param tx_buff Buffer to transfer
 * @param tx_size Transfer size
 *
 * @return Configured variable with total transfer description
 *
 */
#define NRF_DRV_USBD_TRANSFER_IN(name, tx_buff, tx_size) \
    NRF_DRV_USBD_TRANSFER_IN_FLAGS(name, tx_buff, tx_size, 0)

/**
 * @brief Helper macro for declaring IN transfer description
 *
 * ZLP mode - Zero Length Packet would be generated on the end of the transfer
 * (always!).
 *
 * @sa nrf_drv_usbd_transfer_t
 * @sa NRF_DRV_USBD_TRANSFER_IN
 *
 * @param name    Instance name
 * @param tx_buff Buffer to transfer
 * @param tx_size Transfer size
 *
 * @return Configured variable with total transfer description
 */
#define NRF_DRV_USBD_TRANSFER_IN_ZLP(name, tx_buff, tx_size) \
    NRF_DRV_USBD_TRANSFER_IN_FLAGS(                          \
        name,                                                \
        tx_buff,                                             \
        tx_size,                                             \
        NRF_DRV_USBD_TRANSFER_ZLP_FLAG)

/**
 * @brief Helper macro for declaring OUT transfer item (@ref nrf_drv_usbd_transfer_t)
 *
 * @param name    Instance name
 * @param rx_buff Buffer to transfer
 * @param rx_size Transfer size
 * */
#define NRF_DRV_USBD_TRANSFER_OUT(name, rx_buff, rx_size)       \
    const nrf_drv_usbd_transfer_t name = {                      \
       .p_data = { .rx = (rx_buff)  },                          \
       .size = (rx_size),                                       \
       .flags = 0                                               \
    }

/**
 * @brief USBD transfer feeder.
 *
 * Pointer for a transfer feeder.
 * Transfer feeder is a feedback function used to prepare a single
 * TX (Device->Host) endpoint transfer.
 *
 * The transfers provided by the feeder must be simple:
 * - The size of the transfer provided by this function is limited to a single endpoint buffer.
 *   Bigger transfers are not handled automatically in this case.
 * - Flash transfers are not automatically supported- you must copy them to the RAM buffer before.
 *
 * @note
 * This function may use @ref nrf_drv_usbd_feeder_buffer_get to gain a temporary buffer
 * that can be used to prepare transfer.
 *
 * @param[out]    p_next    Structure with the data for the next transfer to be filled.
 *                          Required only if the function returns true.
 * @param[in,out] p_context Context variable configured with the transfer.
 * @param[in]     ep_size   The endpoint size.
 *
 * @retval false The current transfer is the last one - you do not need to call
 *               the function again.
 * @retval true  There is more data to be prepared and when the current transfer
 *               finishes, the feeder function is expected to be called again.
 */
typedef bool (*nrf_drv_usbd_feeder_t)(
    nrf_drv_usbd_ep_transfer_t * p_next,
    void * p_context,
    size_t ep_size);

/**
 * @brief USBD transfer consumer.
 *
 * Pointer for a transfer consumer.
 * Transfer consumer is a feedback function used to prepare a single
 * RX (Host->Device) endpoint transfer.
 *
 * The transfer must provide a buffer big enough to fit the whole data from the endpoint.
 * Otherwise, the NRF_USBD_EP_OVERLOAD event is generated.
 *
 * @param[out]    p_next    Structure with the data for the next transfer to be filled.
 *                          Required only if the function returns true.
 * @param[in,out] p_context Context variable configured with the transfer.
 * @param[in]     ep_size   The endpoint size.
 * @param[in]     data_size Number of received bytes in the endpoint buffer.
 *
 * @retval false Current transfer is the last one - you do not need to call
 *               the function again.
 * @retval true  There is more data to be prepared and when current transfer
 *               finishes, the feeder function is expected to be called again.
 */
typedef bool (*nrf_drv_usbd_consumer_t)(
    nrf_drv_usbd_ep_transfer_t * p_next,
    void * p_context,
    size_t ep_size,
    size_t data_size);

/**
 * @brief Universal transfer handler.
 *
 * Union with feeder and consumer function pointer.
 */
typedef union
{
    nrf_drv_usbd_feeder_t   feeder;   //!< Feeder function pointer.
    nrf_drv_usbd_consumer_t consumer; //!< Consumer function pointer.
}nrf_drv_usbd_handler_t;

/**
 * @brief USBD transfer descriptor.
 *
 * Universal structure that may hold the setup for callback configuration for
 * IN or OUT type of the transfer.
 */
typedef struct
{
    nrf_drv_usbd_handler_t   handler;   //!< Handler for the current transfer, function pointer.
    void                   * p_context; //!< Context for the transfer handler.
}nrf_drv_usbd_handler_desc_t;

/**
 * @brief Setup packet structure
 *
 * Structure that contains interpreted SETUP packet.
 */
typedef struct
{
    uint8_t  bmRequestType; //!< byte 0
    uint8_t  bmRequest;     //!< byte 1
    uint16_t wValue;        //!< byte 2
    uint16_t wIndex;        //!< byte 4, 5
    uint16_t wLength;       //!< byte 6, 7
}nrf_drv_usbd_setup_t;

/**
 * @brief Library initialization
 *
 * @param[in] event_handler Event handler provided by the user.
 */
ret_code_t nrf_drv_usbd_init(nrf_drv_usbd_event_handler_t const event_handler);

/**
 * @brief Library deinitialization
 */
ret_code_t nrf_drv_usbd_uninit(void);

/**
 * @brief Enable the USBD port
 *
 * After calling this function USBD peripheral would be enabled.
 * The USB LDO would be enabled.
 * Enabled USBD peripheral would request HFCLK.
 * This function does not enable external oscillator, so if it is not enabled by other part of the
 * program after enabling USBD driver HFINT would be used for the USBD peripheral.
 * It is perfectly fine until USBD is started. See @ref nrf_drv_usbd_start.
 *
 * In normal situation this function should be called in reaction to USBDETECTED
 * event from POWER peripheral.
 *
 * Interrupts and USB pins pull-up would stay disabled until @ref nrf_drv_usbd_start
 * function is called.
 */
void nrf_drv_usbd_enable(void);

/**
 * @brief Disable the USBD port
 *
 * After calling this function USBD peripheral would be disabled.
 * No events would be detected or processed by the library.
 * Clock for the peripheral would be disconnected.
 */
void nrf_drv_usbd_disable(void);

/**
 * @brief Start USB functionality
 *
 * After calling this function USBD peripheral should be fully functional
 * and all new incoming events / interrupts would be processed by the library.
 *
 * Also only after calling this function host sees new connected device.
 *
 * Call this function when USBD power LDO regulator is ready - on USBPWRRDY event
 * from POWER peripheral.
 *
 * Before USBD interrupts are enabled, external HFXO is requested.
 *
 * @param enable_sof The flag that is used to enable SOF processing.
 *                   If it is false, SOF interrupt is left disabled and will not be generated.
 *                   This improves power saving if SOF is not required.
 *
 * @note If the isochronous endpoints are going to be used,
 *       it is required to enable the SOF.
 *       In other case any isochronous endpoint would stay busy
 *       after first transmission.
 */
void nrf_drv_usbd_start(bool enable_sof);

/**
 * @brief Stop USB functionality
 *
 * This function disables USBD pull-up and interrupts.
 *
 * The HFXO request is released in this function.
 *
 * @note
 * This function can also be used to logically disconnect USB from the HOST that
 * would force it to enumerate device after calling @ref nrf_drv_usbd_start.
 */
void nrf_drv_usbd_stop(void);

/**
 * @brief Check if driver is initialized
 *
 * @retval false Driver is not initialized
 * @retval true Driver is initialized
 */
bool nrf_drv_usbd_is_initialized(void);

/**
 * @brief Check if driver is enabled
 *
 * @retval false Driver is disabled
 * @retval true  Driver is enabled
 */
bool nrf_drv_usbd_is_enabled(void);

/**
 * @brief Check if driver is started
 *
 * @retval false Driver is not started
 * @retval true Driver is started (fully functional)
 * @note The USBD peripheral interrupt state is checked
 */
bool nrf_drv_usbd_is_started(void);

/**
 * @brief Suspend USBD operation
 *
 * The USBD peripheral is forced to go into the low power mode.
 * The function has to be called in the reaction to @ref NRF_DRV_USBD_EVT_SUSPEND event
 * when the firmware is ready.
 *
 * After successful call of this function most of the USBD registers would be unavailable.
 *
 * @note Check returned value for the feedback if suspending was successful.
 *
 * @retval true  USBD peripheral successfully suspended
 * @retval false USBD peripheral was not suspended due to resume detection.
 *
 */
bool nrf_drv_usbd_suspend(void);

/**
 * @brief Start wake up procedure
 *
 * The USBD peripheral is forced to quit the low power mode.
 * After calling this function all the USBD registers would be available.
 *
 * The hardware starts measuring time when wake up is possible.
 * This may take 0-5&nbsp;ms depending on how long the SUSPEND state was kept on the USB line.

 * When NRF_DRV_USBD_EVT_WUREQ event is generated it means that Wake Up signaling has just been
 * started on the USB lines.
 *
 * @note Do not expect only @ref NRF_DRV_USBD_EVT_WUREQ event.
 *       There always may appear @ref NRF_DRV_USBD_EVT_RESUME event.
 * @note NRF_DRV_USBD_EVT_WUREQ event means that Remote WakeUp signal
 *       has just begun to be generated.
 *       This may take up to 20&nbsp;ms for the bus to become active.
 *
 * @retval true WakeUp procedure started.
 * @retval false No WakeUp procedure started - bus is already active.
 */
bool nrf_drv_usbd_wakeup_req(void);

/**
 * @brief Check if USBD is in SUSPEND mode
 *
 * @note This is the information about peripheral itself, not about the bus state.
 *
 * @retval true  USBD peripheral is suspended
 * @retval false USBD peripheral is active
 */
bool nrf_drv_usbd_suspend_check(void);

/**
 * @brief Enable only interrupts that should be processed in SUSPEND mode
 *
 * Auxiliary function to help with SUSPEND mode integration.
 * It enables only the interrupts that can be properly processed without stable HFCLK.
 *
 * Normally all the interrupts are enabled.
 * Use this function to suspend interrupt processing that may require stable HFCLK until the
 * clock is enabled.
 *
 * @sa nrf_drv_usbd_active_irq_config
 */
void nrf_drv_usbd_suspend_irq_config(void);

/**
 * @brief Default active interrupt configuration
 *
 * Default interrupt configuration.
 * Use in a pair with @ref nrf_drv_usbd_active_irq_config.
 *
 * @sa nrf_drv_usbd_suspend_irq_config
 */
void nrf_drv_usbd_active_irq_config(void);

/**
 * @brief Check the bus state
 *
 * This function checks if the bus state is suspended
 *
 * @note The value returned by this function changes on SUSPEND and RESUME event processing.
 *
 * @retval true  USBD bus is suspended
 * @retval false USBD bus is active
 */
bool nrf_drv_usbd_bus_suspend_check(void);

/**
 * @brief Configure packet size that should be supported by the endpoint
 *
 * The real endpoint buffer size is always the same.
 * This value sets max packet size that would be transmitted over the endpoint.
 * This is required by the library
 *
 * @param[in] ep   Endpoint number
 * @param[in] size Required maximum packet size
 *
 * @note Endpoint size is always set to @ref NRF_DRV_USBD_EPSIZE or @ref NRF_DRV_USBD_ISOSIZE / 2
 *       when @ref nrf_drv_usbd_ep_enable function is called.
 */
void nrf_drv_usbd_ep_max_packet_size_set(nrf_drv_usbd_ep_t ep, uint16_t size);

/**
 * @brief Get configured endpoint packet size
 *
 * Function to get configured endpoint size on the buffer.
 *
 * @param[in] ep Endpoint number
 *
 * @return Maximum pocket size configured on selected endpoint
 */
uint16_t nrf_drv_usbd_ep_max_packet_size_get(nrf_drv_usbd_ep_t ep);

/**
 * @brief Check if the selected endpoint is enabled.
 *
 * @param ep Endpoint number to check.
 *
 * @retval true  Endpoint is enabled.
 * @retval false Endpoint is disabled.
 */
bool nrf_drv_usbd_ep_enable_check(nrf_drv_usbd_ep_t ep);

/**
 * @brief Enable selected endpoint
 *
 * This function enables endpoint itself and its interrupts.
 * @param ep Endpoint number to enable
 *
 * @note
 * Max packet size is set to endpoint default maximum value.
 *
 * @sa nrf_drv_usbd_ep_max_packet_size_set
 */
void nrf_drv_usbd_ep_enable(nrf_drv_usbd_ep_t ep);

/**
 * @brief Disable selected endpoint
 *
 * This function disables endpoint itself and its interrupts.
 * @param ep Endpoint number to disable
 */
void nrf_drv_usbd_ep_disable(nrf_drv_usbd_ep_t ep);

/**
 * @brief Disable all endpoints except for EP0
 *
 * Disable all endpoints that can be disabled in USB device while it is still active.
 */
void nrf_drv_usbd_ep_default_config(void);

/**
 * @brief Start sending data over endpoint
 *
 * Function initializes endpoint transmission.
 * This is asynchronous function - it finishes immediately after configuration
 * for transmission is prepared.
 *
 * @note Data buffer pointed by p_data have to be kept active till
 *       @ref NRF_DRV_USBD_EVT_EPTRANSFER event is generated.
 *
 * @param[in] ep         Endpoint number.
 *                       For IN endpoint sending would be initiated.
 *                       For OUT endpoint receiving would be initiated.
 * @param[in] p_transfer
 *
 * @retval NRF_ERROR_BUSY          Selected endpoint is pending.
 * @retval NRF_ERROR_INVALID_ADDR  Unexpected transfer on EPIN0 or EPOUT0.
 * @retval NRF_ERROR_FORBIDDEN     Endpoint stalled.
 * @retval NRF_SUCCESS             Transfer queued or started.
 */
ret_code_t nrf_drv_usbd_ep_transfer(
    nrf_drv_usbd_ep_t                                  ep,
    nrf_drv_usbd_transfer_t              const * const p_transfer);

/**
 * @brief Start sending data over the endpoint using the transfer handler function.
 *
 * This function initializes an endpoint transmission.
 * Just before data is transmitted, the transfer handler
 * is called and it prepares a data chunk.
 *
 * @param[in] ep    Endpoint number.
 *                  For an IN endpoint, sending is initiated.
 *                  For an OUT endpoint, receiving is initiated.
 * @param p_handler Transfer handler - feeder for IN direction and consumer for
 *                  OUT direction.
 *
 * @retval NRF_ERROR_BUSY          Selected endpoint is pending.
 * @retval NRF_ERROR_INVALID_ADDR  Unexpected transfer on EPIN0 or EPOUT0.
 * @retval NRF_ERROR_FORBIDDEN     Endpoint stalled.
 * @retval NRF_SUCCESS             Transfer queued or started.
 */
ret_code_t nrf_drv_usbd_ep_handled_transfer(
    nrf_drv_usbd_ep_t                         ep,
    nrf_drv_usbd_handler_desc_t const * const p_handler);

/**
 * @brief Get the temporary buffer to be used by the feeder.
 *
 * This buffer is used for TX transfers and it can be reused automatically
 * when the transfer is finished.
 * Use it for transfer preparation.
 *
 * May be used inside the feeder configured in @ref nrf_drv_usbd_ep_handled_transfer.
 *
 * @return Pointer to the buffer that can be used temporarily.
 *
 * @sa NRF_DRV_USBD_FEEDER_BUFFER_SIZE
 */
void * nrf_drv_usbd_feeder_buffer_get(void);

/**
 * @brief Get the information about last finished or current transfer
 *
 * Function returns the status of the last buffer set for transfer on selected endpoint.
 * The status considers last buffer set by @ref nrf_drv_usbd_ep_transfer function or
 * by transfer callback function.
 *
 * @param[in]  ep     Endpoint number.
 * @param[out] p_size Information about the current/last transfer size.
 *
 * @retval NRF_SUCCESS         Transfer already finished
 * @retval NRF_ERROR_BUSY      Ongoing transfer
 * @retval NRF_ERROR_DATA_SIZE Too much of data received that cannot fit into buffer and cannot be splited into chunks.
 *                             This may happen if buffer size is not a multiplication of endpoint buffer size.
 */
ret_code_t nrf_drv_usbd_ep_status_get(nrf_drv_usbd_ep_t ep, size_t * p_size);

/**
 * @brief Get number of received bytes
 *
 * Get the number of received bytes.
 * The function behavior is undefined when called on IN endpoint.
 *
 * @param ep Endpoint number.
 *
 * @return Number of received bytes
 */
size_t nrf_drv_usbd_epout_size_get(nrf_drv_usbd_ep_t ep);

/**
 * @brief Check if endpoint buffer is ready or is under USB IP control
 *
 * Function to test if endpoint is busy.
 * Endpoint that is busy cannot be accessed by MCU.
 * It means that:
 * - OUT (TX) endpoint: Last uploaded data is still in endpoint and is waiting
 *                      to be received by the host.
 * - IN  (RX) endpoint: Endpoint is ready to receive data from the host
 *                      and the endpoint does not have any data.
 * When endpoint is not busy:
 * - OUT (TX) endpoint: New data can be uploaded.
 * - IN  (RX) endpoint: New data can be downloaded using @ref nrf_drv_usbd_ep_transfer
 *                      function.
 */
bool nrf_drv_usbd_ep_is_busy(nrf_drv_usbd_ep_t ep);

/**
 * @brief Stall endpoint
 *
 * Stall endpoit to send error information during next transfer request from
 * the host.
 *
 * @note To stall endpoint it is safer to use @ref nrf_drv_usbd_setup_stall
 * @note Stalled endpoint would not be cleared when DMA transfer finishes.
 *
 * @param ep Endpoint number to stall
 *
 */
void nrf_drv_usbd_ep_stall(nrf_drv_usbd_ep_t ep);

/**
 * @brief Clear stall flag on endpoint
 *
 * This function clears endpoint that is stalled.
 * @note
 * If it is OUT endpoint (receiving) it would be also prepared for reception.
 * It means that busy flag would be set.
 * @note
 * In endpoint (transmitting) would not be cleared - it gives possibility to
 * write new data before transmitting.
 */
void nrf_drv_usbd_ep_stall_clear(nrf_drv_usbd_ep_t ep);

/**
 * @brief Check if endpoint is stalled
 *
 * This function gets stall state of selected endpoint
 *
 * @param ep Endpoint number to check
 */
bool nrf_drv_usbd_ep_stall_check(nrf_drv_usbd_ep_t ep);

/**
 * @brief Clear current endpoint data toggle
 *
 * @param ep Endpoint number to clear
 */
void nrf_drv_usbd_ep_dtoggle_clear(nrf_drv_usbd_ep_t ep);

/**
 * @brief Get parsed setup data
 *
 * Function fills the parsed setup data structure.
 *
 * @param[out] p_setup Pointer to data structure that would be filled by
 *                     parsed data.
 */
void nrf_drv_usbd_setup_get(nrf_drv_usbd_setup_t * const p_setup);

/**
 * @brief Clear only for data transmission on setup endpoint
 *
 * This function may be called if any more data in control write transfer is expected.
 * Clears only OUT endpoint to be able to take another OUT data token.
 * It does not allow STATUS stage.
 * @sa nrf_drv_usbd_setup_clear
 */
void nrf_drv_usbd_setup_data_clear(void);

/**
 * @brief Clear setup endpoint
 *
 * This function acknowledges setup when SETUP command was received and processed.
 * It has to be called if no data respond for the SETUP command is sent.
 */
void nrf_drv_usbd_setup_clear(void);

/**
 * @brief Stall setup endpoint
 *
 * Mark and error on setup endpoint.
 */
void nrf_drv_usbd_setup_stall(void);

/**
* @note
* This function locks interrupts that may be costly.
* It is good idea to test if the endpoint is still busy before calling this function:
* @code
  (m_ep_dma_waiting & (1U << ep2bit(ep)))
* @endcode
* This function would check it again, but it makes it inside critical section.
*/
void nrf_drv_usbd_ep_abort(nrf_drv_usbd_ep_t ep);

/**
 * @brief Get the information about expected transfer SETUP data direction
 *
 * Function returns the information about last expected transfer direction.
 *
 * @retval NRF_DRV_USBD_EPOUT0 Expecting OUT (Host->Device) direction or no data
 * @retval NRF_DRV_USBD_EPIN0  Expecting IN (Device->Host) direction
 */
nrf_drv_usbd_ep_t nrf_drv_usbd_last_setup_dir_get(void);

/**
 * @brief Drop transfer on OUT endpoint
 *
 * @param[in] ep  OUT endpoint ID
 */
void nrf_drv_usbd_transfer_out_drop(nrf_drv_usbd_ep_t ep);

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* NRF_DRV_USBD_H__ */
