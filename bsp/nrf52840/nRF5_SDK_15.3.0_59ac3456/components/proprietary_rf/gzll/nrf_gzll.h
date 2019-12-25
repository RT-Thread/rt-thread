/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
/**
 * @file
 * @brief Gazell Link Layer API.
 */

#ifndef NRF_GZLL_H__
#define NRF_GZLL_H__

#include <stdbool.h>
#include "nrf.h"
#include "nrf_gzll_constants.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
* @defgroup gzll_02_api Gazell Link Layer
* @{
* @ingroup modules_01_gzll
* @brief Gazell Link Layer Application Programming Interface (API).
*/

/**
 * @enum nrf_gzll_mode_t
 * @brief Enumerator used for selecting Gazell mode.
 */
typedef enum
{
    NRF_GZLL_MODE_DEVICE,  ///< Device mode
    NRF_GZLL_MODE_HOST,    ///< Host mode
    NRF_GZLL_MODE_SUSPEND, ///< Suspend mode ("disabled with timer running")
} nrf_gzll_mode_t;

/**
 * @enum nrf_gzll_device_channel_selection_policy_t
 * @brief Enumerator used for selecting Gazell Device channel
 * selection policy.
 */
typedef enum
{
    NRF_GZLL_DEVICE_CHANNEL_SELECTION_POLICY_USE_SUCCESSFUL, ///< Start on previous successful channel
    NRF_GZLL_DEVICE_CHANNEL_SELECTION_POLICY_USE_CURRENT,    ///< Start on channel currently monitored by Host
} nrf_gzll_device_channel_selection_policy_t;

/**
 * @enum nrf_gzll_tx_power_t
 * @brief Enumerator used for selecting the transmit (TX) power.
 */
typedef enum
{
    NRF_GZLL_TX_POWER_4_DBM,   ///<  4 dBm transmit power.
    NRF_GZLL_TX_POWER_0_DBM,   ///<  0 dBm transmit power.
    NRF_GZLL_TX_POWER_N4_DBM,  ///< -4 dBm transmit power.
    NRF_GZLL_TX_POWER_N8_DBM,  ///< -8 dBm transmit power.
    NRF_GZLL_TX_POWER_N12_DBM, ///< -12 dBm transmit power.
    NRF_GZLL_TX_POWER_N16_DBM, ///< -16 dBm transmit power.
    NRF_GZLL_TX_POWER_N20_DBM  ///< -20 dBm transmit power.
} nrf_gzll_tx_power_t;

/**
 * @enum nrf_gzll_datarate_t
 * @brief Enumerator used for selecting the radio datarate.
 */
typedef enum
{
#ifdef NRF51
    NRF_GZLL_DATARATE_250KBIT = 0, ///<  250 Kbps datarate, available only for the nRF51.
#endif
    NRF_GZLL_DATARATE_1MBIT   = 1, ///<  1 Mbps datarate.
    NRF_GZLL_DATARATE_2MBIT   = 2  ///<  2 Mbps datarate.
} nrf_gzll_datarate_t;

/**
 * @enum nrf_gzll_xosc_ctl_t
 * @brief Enumerator used for specifying whether switching the
 * external 16 MHz oscillator on/off shall be handled automatically
 * inside Gazell or manually by the application.
 */
typedef enum
{
    NRF_GZLL_XOSC_CTL_AUTO,  ///< Switch XOSC on/off automatically
    NRF_GZLL_XOSC_CTL_MANUAL ///< Switch XOSC on/off manually
} nrf_gzll_xosc_ctl_t;

/**
 * @enum nrf_gzll_error_code_t
 * @brief Enumerator used for error codes for Gazell API functions
 */
typedef enum
{
    NRF_GZLL_ERROR_CODE_NO_ERROR                            =  0, ///< No error has been detected.
    NRF_GZLL_ERROR_CODE_FAILED_TO_INITIALIZE                =  1, ///< The function NRF_GZLL_init failed.
    NRF_GZLL_ERROR_CODE_ATTEMPTED_TO_CONFIGURE_WHEN_ENABLED =  2, ///< A call to a configuration 'set' function was made while Gazell was enabled.
    NRF_GZLL_ERROR_CODE_POINTER_IS_NULL                     =  3, ///< A null pointer was given as an input to a function.
    NRF_GZLL_ERROR_CODE_INVALID_PIPE                        =  4, ///< An invalid pipe number was given as an input to a function.
    NRF_GZLL_ERROR_CODE_INVALID_MODE                        =  5, ///< An invalid value for the nrf_gzll_mode_t enumerator was given as input to a function.
    NRF_GZLL_ERROR_CODE_INVALID_PAYLOAD_LENGTH              =  6, ///< An invalid payload length was given as an input to a function.
    NRF_GZLL_ERROR_CODE_INVALID_CHANNEL_TABLE_SIZE          =  7, ///< An invalid channel table size was given as an input to a function.
    NRF_GZLL_ERROR_CODE_INSUFFICIENT_PACKETS_AVAILABLE      =  8, ///< There are insufficient packets in the Gazell memory pool to successfully execute the operation.
    NRF_GZLL_ERROR_CODE_ATTEMPTED_TO_ADD_TO_FULL_FIFO       =  9, ///< There is insufficient space in the TX FIFO for the data packet.
    NRF_GZLL_ERROR_CODE_NO_SPACE_IN_RX_FIFO_FOR_ACK         = 10, ///< There is insufficient space in the RX FIFO for the ACK.
    NRF_GZLL_ERROR_CODE_ATTEMPTED_TO_FETCH_FROM_EMPTY_FIFO  = 11, ///< Attempted to fetch a packet from an empty FIFO. Use the functions nrf_gzll_get_tx_fifo_packet_count() or nrf_gzll_get_rx_fifo_packet_count()
    NRF_GZLL_ERROR_CODE_ATTEMPTED_TO_FLUSH_WHEN_ENABLED     = 12, ///< Attempted to fetch a packet from an empty FIFO. Use the functions nrf_gzll_get_tx_fifo_packet_count() or nrf_gzll_get_rx_fifo_packet_count()
    NRF_GZLL_ERROR_CODE_INVALID_PARAMETER                   = 14, ///< Attempted to set a variable which was not valid.
    NRF_GZLL_ERROR_CODE_INTERNAL_ASSERT_OCCURRED            = 15, ///< An internal assert occurred.
    NRF_GZLL_ERROR_CODE_CALLBACK_NOT_IMPLEMENTED            = 16, ///< A callback was called but not implemented by the application.
    NRF_GZLL_ERROR_CODE_INVALID_ADDRESS                     = 17, ///< Invalid pipe 0 address detected, see Anomaly 107 at nRF52832 errata document.
    NRF_GZLL_ERROR_CODE_NUMBER_OF_ERROR_CODES               = 18, ///< Number of possible error codes.
} nrf_gzll_error_code_t;

/**
 * @struct nrf_gzll_device_tx_info_t;
 * @brief Data structure containing information about the last packet
 *        transmission.
 */
typedef struct
{
    bool     payload_received_in_ack;    ///< A payload was received in the ACK.
    uint16_t num_tx_attempts;            ///< Number of attempts used on previous Device packet transmission.
    uint16_t num_channel_switches;       ///< Number of channel switches needed during previous packet transmission.
    int8_t   rssi;                       ///< Received signal strength indicator in dBm. @sa nrf_gzll_enable_rssi().
    uint8_t  rf_channel;                 ///< Channel on which packet has been transmitted.
} nrf_gzll_device_tx_info_t;


/**
 * @struct nrf_gzll_host_rx_info_t;
 * @brief Data structure containing information about the last packet
 *        received.
 */
typedef struct
{
    bool    packet_removed_from_tx_fifo; ///< A payload was received in the ACK.
    int8_t  rssi;                        ///< Received signal strength indicator in dBm. @sa nrf_gzll_enable_rssi().
    uint8_t rf_channel;                  ///< Channel on which packet has been received.
} nrf_gzll_host_rx_info_t;


typedef struct 
{
    uint32_t packets_num;                                             ///< Number of succesfully transmitted packets 
    uint32_t timeouts_num;                                            ///< Total timeouts number 
    uint32_t channel_timeouts[NRF_GZLL_CONST_MAX_CHANNEL_TABLE_SIZE]; ///< Transmission timeouts per channel 
    uint32_t channel_packets[NRF_GZLL_CONST_MAX_CHANNEL_TABLE_SIZE];  ///< Succesfully transmitted packets per channel 
} nrf_gzll_tx_statistics_t;


/**< Transmission timeout callback function definition */
typedef void (*nrf_gzll_tx_timeout_callback)(uint32_t pipe, uint8_t rf_channel);


/**< Transmission CRC failure callback function definition */
typedef void (*nrf_gzll_crc_failure_callback)(uint32_t pipe, uint8_t rf_channel);


#if defined(NRF52_SERIES) || defined(__SDK_DOXYGEN__)
/**
 * @brief Data structure holding external front
 *        end control configuration.
 */
typedef struct
{
    bool             pa_enabled;                                     ///< Flag indicating if PA control is enabled.
    bool             pa_active_high;                                 ///< Flag indicating if PA is active in high input state.
    uint8_t          pa_gpio_pin;                                    ///< Number of output pin used for PA control.
    uint8_t          pa_gpiote_channel;                              ///< Number of GPIOTE channel used for PA control.
    bool             lna_enabled;                                    ///< Flag indicating if LNA control is enabled.
    bool             lna_active_high;                                ///< Flag indicating if LNA is active in high input state.
    uint8_t          lna_gpio_pin;                                   ///< Number of output pin used for LNA control.
    uint8_t          lna_gpiote_channel;                             ///< Number of GPIOTE channel used for LNA control.
    NRF_TIMER_Type * timer;                                          ///< Pointer to the TIMER instance.
    uint8_t          ppi_channels[NRF_GZLL_PA_LNA_PPI_CHANNELS_NUM]; ///< PPI channels used to control front end.
    uint8_t          ramp_up_time;                                   ///< Determines how early should the PA/LNA be turned one before RADIO activity. Should be less than @ref NRF_GZLL_PA_LNA_MAX_RAMP_UP_TIME.
} nrf_gzll_pa_lna_cfg_t;
#endif

/******************************************************************************/
/** @name General API functions
 *  @{ */
/******************************************************************************/

/**
 * @brief Initialize Gazell.
 *
 * @param mode The mode to initialize Gazell in.
 *
 * @retval true if Gazell initialized.
 * @retval false if Gazell failed to initialize.
 */
bool nrf_gzll_init(nrf_gzll_mode_t mode);

/**
 * @brief Enable Gazell.
 *
 * When enabled the behaviour described for the current Gazell Link Layer mode
 * will apply.
 *
 * @retval false if nrf_gzll_init has not previously been called or invalid address
 *               has been set - see Anomaly 107 at nRF52832 errata document.
 */
bool nrf_gzll_enable(void);

/**
 * @brief Disable Gazell.
 *
 * When calling this function the Gazell Link Layer will begin disabling,
 * and will be fully disabled when Gazell calls nrf_gzll_disabled().
 * If there are any pending notifications, or if any new notifications are
 * being added to the internal notification queue while Gazell is disabling,
 * these will be sent to the application before Gazell is fully disabled.
 *
 * After Gazell has been fully disabled, no more notifications will be sent to
 * the application.
 */
void nrf_gzll_disable(void);

/** Check whether Gazell is enabled or disabled.
 *
 * @retval true  If Gazell is enabled.
 * @retval false If Gazell is disabled.
 */
bool nrf_gzll_is_enabled(void);

/** @} */

/******************************************************************************/
/** @name Device mode callback functions
 *  @{ */
/******************************************************************************/

/**
 * @brief ACK received callback (Device mode only).
 *
 * This callback is made when the Device receives an ACK (acknowledgement)
 * packet.
 * @sa nrf_gzll_ack_payload_received.
 *
 * @param pipe is the pipe on which an ACK packet was received.
 * @param tx_info struct used to indicate whether a payload was received in the
 * ack, as well as the number of TX attempts and channel switches required.
 */
void nrf_gzll_device_tx_success(uint32_t pipe, nrf_gzll_device_tx_info_t tx_info);

/**
 * @brief Transmission failed callback (Device mode only).
 *
 * This callback is made when a packet does not receive an ACK after
 * nrf_gzll_max_retries is reached. The packet is deleted by Gazell.
 *
 * @param pipe is the pipe on which the transmission failed.
 * @param tx_info struct used to indicate whether a payload was received
 * in the ack, as well as RSSI and the number of TX attempts and
 * channel switches required.
 */
void nrf_gzll_device_tx_failed(uint32_t pipe, nrf_gzll_device_tx_info_t tx_info);

/** @} */

/******************************************************************************/
/** @name Host mode callback functions
 *  @{ */
/******************************************************************************/

/**
 * @brief Data packet received callback (Host mode only).
 *
 * This callback is made when a Host receives a data packet from a Device.
 *
 * @param pipe is the pipe on which the data packet was received.
 * @param rx_info struct used to indicate whether a payload was removed from the
 * pipe's TX FIFO, as well as RSSI.
 */
void nrf_gzll_host_rx_data_ready(uint32_t pipe, nrf_gzll_host_rx_info_t rx_info);

/** @} */

/******************************************************************************/
/** @name Callback functions for both Device and Host mode
 *  @{ */
/******************************************************************************/

/**
 * @brief Disabled callback.
 *
 * This is called after Gazell enters the disabled state.
 * There is no further CPU use by Gazell, the radio is disabled and the timer is
 * powered down.
 */
void nrf_gzll_disabled(void);

/**
 * @brief Mode changed callbackl.
 *
 * This function is called after the Gazell mode has been changed.
 * This function can only be called when Gazell is enabled.
 */
void nrf_gzll_mode_changed(void);

/** @} */

/******************************************************************************/
/** @name Packet transmission and receiving functions
 *  @{ */
/******************************************************************************/

/**
 * @brief Add a packet to the tail of the TX FIFO.
 *
 * In Device mode, the packet will be added.
 * In Host mode, the payload will be piggybacked onto an ACK.
 *
 * @param pipe      Pipe to which to add the payload. This value must be < NRF_GZLL_CONST_PIPE_COUNT.
 * @param p_payload Pointer to the payload.
 * @param length    Number of bytes of the payload to transmit
 *                  (0 to NRF_GZLL_CONST_MAX_PAYLOAD_LENGTH).
 *
 * @retval true  if the packet was successfully added to the TX FIFO.
 * @retval false if unsuccessful, check nrf_gzll_error_code_t for more information.
 */
bool nrf_gzll_add_packet_to_tx_fifo(uint32_t pipe, uint8_t * p_payload, uint32_t length);

/**
 * @brief Fetch a packet from the head of the RX FIFO.
 *
 * @param pipe      Pipe from which to fetch the payload. This value must be < NRF_GZLL_CONST_PIPE_COUNT.
 * @param p_payload Pointer to copy the payload to.
 * @param p_length  Length must be at least as large as the the number of bytes
 *                  in the received payload length.
 *
 * @retval true  If the fetch was successful.
 * @retval false If unsuccessful, check nrf_gzll_error_code_t for more information.
 */
bool nrf_gzll_fetch_packet_from_rx_fifo(uint32_t pipe, uint8_t * p_payload, uint32_t * p_length);

/**
 * @brief Get the number of packets in the TX FIFO on a specific pipe.
 *
 * @param pipe The pipe for which to check. This value must be < NRF_GZLL_CONST_PIPE_COUNT.
 *
 * @retval >=0 The number of packets in the TX FIFO for the pipe.
 * @retval -1  If the pipe number is invalid.
 */
int32_t nrf_gzll_get_tx_fifo_packet_count(uint32_t pipe);

/**
 * @brief Get the number of packets in the RX FIFO on a specific pipe.
 *
 * @param pipe  The pipe for which to check. This value must be < NRF_GZLL_CONST_PIPE_COUNT.
 * @retval >=0  The number of packets in the RX FIFO for the pipe.
 * @retval -1   If the pipe number is invalid.
 */
int32_t nrf_gzll_get_rx_fifo_packet_count(uint32_t pipe);

/**
 * @brief Get the total number of packets residing in all TX and RX FIFOs.
 *
 * Can be used to check against NRF_GZLL_CONST_MAX_TOTAL_PACKETS to
 * determine if there is free space in the memory pool for more packets.
 *
 * @return The number of packets residing in all TX and RX FIFOs.
 */
uint32_t nrf_gzll_get_total_allocated_packet_count(void);

/**
 * @brief Check if adding a packet to a pipe's TX FIFO should be successful.
 *
 * Checks if there is another space in the pipe's TX and RX FIFOs
 * as well as enough overall space in the packet pool.
 *
 * @param pipe The pip for which to check. This value must be < NRF_GZLL_CONST_PIPE_COUNT.
 *
 * @retval true  If there is another space.
 * @retval false If there is not enough space, or the pipe is invalid.
 */
bool nrf_gzll_ok_to_add_packet_to_tx_fifo(uint32_t pipe);

/**
 * @brief Flush the RX FIFO for a specific pipe.
 *
 * Delete all the packets and free the memory of the TX FIFO for a
 * specific pipe.
 *
 * Note that it is not allowed to flush a TX FIFO when
 * Gazell is enabled.
 *
 * @param pipe is the pipe for which to flush. This value must be < NRF_GZLL_CONST_PIPE_COUNT.
 * @retval true if the pipe was flushed.
 * @retval false if the pipe was not flushed.
 */
bool nrf_gzll_flush_tx_fifo(uint32_t pipe);

/**
 * @brief Flush the RX FIFO for a specific pipe.
 *
 * Delete all the packets and free the memory of the RX FIFO for a
 * specific pipe.
 *
 * @param pipe is the pipe for which to flush. This value must be < NRF_GZLL_CONST_PIPE_COUNT.
 * @retval true if the pipe was flushed.
 * @retval false if the pipe was not flushed.
 */
bool nrf_gzll_flush_rx_fifo(uint32_t pipe);

/**
 * @brief Function for enabling transmission statistics.
 *
 * @param p_statistics Pointer to the statistics structure.
 *
 * @return True if channel statistics has been enabled, false otherwise.
 */
bool nrf_gzll_tx_statistics_enable(nrf_gzll_tx_statistics_t * p_statistics);

/**
 * @brief Function for disabling transmission statistics.
 */
void nrf_gzll_tx_statistics_disable(void);

/**
 * @brief Function for obtaining number of transmission timeouts for specific channel.
 * 
 * @param[in]  channel_index Channel index in channel table.
 * @param[out] p_timeouts    Pointer for the result.
 *
 * @return True in case of success, false otherwise.
 */
bool nrf_gzll_get_channel_timeouts(uint8_t channel_index, uint32_t *p_timeouts);

/**
 * @brief Function for clearing transmission statistic structure.
 */
void nrf_gzll_reset_tx_statistics(void);

/** @} */

/******************************************************************************/
/** @name Configuration functions
 *
 * Configuration 'set' functions may only be called while Gazell is disabled. The
 * new parameter comes into effect when Gazell is enabled again.
 *
 * Configuration 'get' functions may be called at any time.
 *
 * @{ */
/******************************************************************************/

/**
 * @brief Function for registering callback to be called on the transmission timeout.
 */
void nrf_gzll_tx_timeout_callback_register(nrf_gzll_tx_timeout_callback callback);


/**
 * @brief Function for registering callback to be called on the packet CRC failure.
 */
void nrf_gzll_crc_failure_callback_register(nrf_gzll_crc_failure_callback callback);


/**
 * @brief Set the mode.
 *
 * @param mode The mode to be used.
 *             See nrf_gzll_mode_t for a list of valid modes.
 *
 * It is allowed to change mode when Gazell is enabled. If the mode is
 * being changed while Gazell is enabled, the mode will not change right away.
 * In this case the callback function nrf_gzll_mode_changed() will be called
 * after the mdoe has changed.
 *
 * @retval true  If the parameter was set.
 */
bool nrf_gzll_set_mode(nrf_gzll_mode_t mode);

/**
 * @brief Get function counterpart to nrf_gzll_set_mode().
 *
 * @return The current mode.
 */
nrf_gzll_mode_t nrf_gzll_get_mode(void);

/**
 * @brief Set the base address for pipe 0.
 *
 * The full on-air address for each pipe is composed of a multi-byte base address
 * prepended to a prefix byte.
 *
 * For packets to be received correctly, the most significant byte of
 * the base address should not be an alternating sequence of 0s and 1s i.e.
 * it should not be 0x55 or 0xAA.
 *
 * @param base_address The 4 byte base address. All bytes are used.
 *
 * @note Due to the nRF52 Anomaly 107, pipe 0 address should not have
 *       both prefix and two LSB of base address set to 0.
 *
 * @retval true  If the parameter was set.
 * @return false If Gazell was enabled.
 */
bool nrf_gzll_set_base_address_0(uint32_t base_address);

/**
 * @brief Get function counterpart to nrf_gzll_set_base_address_0().
 *
 * @return Base address 0.
 */
uint32_t nrf_gzll_get_base_address_0(void);

/**
 * @brief Set the base address for pipes 1-7.
 *
 * Pipes 1 through 7 share base_address_1. @sa nrf_gzll_set_base_address_0.
 *
 * @param base_address The 4 byte base address.
 *
 * @retval true  If the parameter was set.
 * @retval false If Gazell was enabled.
 */
bool nrf_gzll_set_base_address_1(uint32_t base_address);

/**
 * @brief Get function counterpart to nrf_gzll_set_base_address_1().
 *
 * @return Base address 1.
 */
uint32_t nrf_gzll_get_base_address_1(void);

/**
 * @brief Set the address prefix byte for a specific pipe.
 *
 * Each pipe should have its own unique prefix byte.
 *
 * @param pipe                The pipe that the address should apply to.
 *                            This value must be < NRF_GZLL_CONST_PIPE_COUNT.
 * @param address_prefix_byte The address prefix byte.
 *
 * @note Due to the Anomaly 107, pipe 0 address should not have
 *       both prefix and two LSB of base address set to 0.
 *
 * @retval true  If the parameter was set.
 * @retval false If Gazell was enabled, or if the pipe was invalid.
 */
bool nrf_gzll_set_address_prefix_byte(uint32_t pipe, uint8_t address_prefix_byte);

/**
 * @brief Get function counterpart to nrf_gzll_set_address_prefix_byte().
 *
 * @param pipe                      The pipe for which to get the address.
 *                                  This value must be < NRF_GZLL_CONST_PIPE_COUNT.
 * @param p_out_address_prefix_byte The pointer in which to return the
 *                                  address prefix byte.
 *
 * @retval true If the parameter was returned.
 * @retval false If Gazell was enabled, the pipe was invalid or
 *               out_address was a NULL pointer.
 */
bool nrf_gzll_get_address_prefix_byte(uint32_t pipe, uint8_t * p_out_address_prefix_byte);

/**
 * @brief Set which pipes shall listen for packets in Host mode.
 *
 * This value is a bitmap, and each bit corresponds to a given pipe number.
 * Bit 0 set to "1" enables pipes 0, bit 1 set to "1" enables pipe 1
 * and so forth.
 * The maximum number of pipes is defined by NRF_GZLL_CONST_PIPE_COUNT.
 *
 * @param pipes A bitmap specifying which pipes to monitor.
 *
 * @retval true  If the parameter was set.
 * @retval false If Gazell was enabled.
 */
bool nrf_gzll_set_rx_pipes_enabled(uint32_t pipes);

/**
 * @brief Get function counterpart to nrf_gzll_set_rx_pipes_enabled().
 *
 * @return Bitmap holding the current enabled pipes.
 */
uint32_t nrf_gzll_get_rx_pipes_enabled(void);

/**
 * @brief Set the timeslot period.
 *
 * The length in microseconds of a Gazell link layer timeslot.
 *
 * The minimum value of the timeslot period is dependent of the
 * radio data rate (@sa nrf_gzll_set_datarate()).
 *
 * - For NRF_GZLL_DATARATE_2MBIT the timeslot period must be >= 600 us.
 * - For NRF_GZLL_DATARATE_1MBIT the timeslot period must be >= 900 us.
 * - For NRF_GZLL_DATARATE_250KBIT the timeslot period must be >= 2700 us.
 *
 * @param period_us The timeslot period in microseconds.
 *
 * @retval true  If the parameter was set.
 * @retval false If Gazell was enabled.
 */
bool nrf_gzll_set_timeslot_period(uint32_t period_us);

/**
 * @brief Get function counterpart to nrf_gzll_get_timeslot_period().
 *
 * @return The current timeslot period.
 */
uint32_t nrf_gzll_get_timeslot_period(void);

/**
 * @brief Set the Device channel selection policy
 *
 * The policy determines the initial channel when starting a new packet.
 * transmission.
 *
 * @param policy The channel selection policy.
 *
 * @arg NRF_GZLL_DEVICE_CHANNEL_SELECTION_POLICY_USE_SUCCESSFUL specifies
 * that a new packet transmission always shall use the previous
 * successful channel from the channel table. If Gazell is "in sync", Gazell
 * will wait until this channel is being monitored by the Host before starting
 * the transmission.
 *
 * @arg NRF_GZLL_DEVICE_CHANNEL_SELECTION_POLICY_USE_CURRENT specifies that
 * Gazell shall transmit on the channel that is currently being monitored by the
 * Host. This parameter is only used when Gazell is "in sync". When "out of" sync,
 * Gazell will always start using the "previous successful" channel.
 *
 * @retval true  If the parameter was set.
 * @retval false If Gazell was enabled or the policy was invalid.
 */
bool nrf_gzll_set_device_channel_selection_policy(nrf_gzll_device_channel_selection_policy_t policy);

/**
 * @brief Get function counterpart to nrf_gzll_set_device_channel_selection_policy().
 *
 * @return the Device channel selection policy.
 */
nrf_gzll_device_channel_selection_policy_t nrf_gzll_get_device_channel_selection_policy(void);

/**
 * @brief Set the number of timeslots that Gazell shall
 * reside on a single channel before switching to another channel.
 *
 * This parameter applies in Host mode and for a Device that is
 * in the "in sync" state.
 *
 * Since the Device and Host can not be in perfect synchronization, a
 * transmission should overlap to adjacent timeslots on the Host.
 * Therefore this value should be at least 2.
 *
 * @sa nrf_gzll_set_timeslots_per_channel_when_device_out_of_sync
 *
 * @param timeslots The number of timeslots to reside on
 * each channel before channel switch.
 *
 * @retval true  If the parameter was set.
 * @retval false If Gazell was enabled.
 */
bool nrf_gzll_set_timeslots_per_channel(uint32_t timeslots);

/**
 * @brief Get function counterpart to nrf_gzll_set_timeslots_per_channel().
 *
 * @return The current number of timeslots.
 */
uint32_t nrf_gzll_get_timeslots_per_channel(void);

/**
 * @brief Set the number of timeslots that a Gazell shall
 * reside on a single channel before switching to another channel when
 * in the "out of sync" state.
 *
 * This value should be set so that the Device transmits on one channel
 * while the Host goes through a full channel rotation, i.e.,
 * channel_table_size*timeslots_per_channel.
 * This ensures that the channels on the Device and Host will coincide
 * at some point.
 * Further increasing the value has been observed to provide better performance
 * in the presence of interferers.
 *
 * @param timeslots The number of timeslots to reside on
 * each channel before channel switch.
 *
 * @retval true  If the parameter was set.
 * @retval false If Gazell was enabled.
 */
bool nrf_gzll_set_timeslots_per_channel_when_device_out_of_sync(uint32_t timeslots);

/**
 * @brief Get function counterpart to
 * nrf_gzll_set_timeslots_per_channel_when_device_out_of_sync().
 *
 * @return The current number of timeslots.
 */
uint32_t nrf_gzll_get_timeslots_per_channel_when_device_out_of_sync(void);

/**
 * @brief Set the number of timeslots after a successful
 * reception of a Device or Host packet that the Gazell Link Layer shall assume
 * that the link is synchronized. A value of 0 implies that the
 * link is always out of sync.
 *
 * @param lifetime The sync lifetime in number of timeslots.
 *
 * @retval true  If the sync lifetime was set.
 * @retval false If Gazell was enabled.
 */
bool nrf_gzll_set_sync_lifetime(uint32_t lifetime);

/**
 * @brief Get function counterpart to nrf_gzll_set_sync_lifetime().
 *
 * @return The sync lifetime measured in number of timeslots.
 */
uint32_t nrf_gzll_get_sync_lifetime(void);

/**
 * @brief Set the maximum number of TX attempts
 * that can be used for a single packet.
 *
 * After the maximum number of attempts have been spent without
 * receiving any ACK from the Host, the transmission will be terminated
 * and the nrf_gzll_device_tx_failed() callback will be called. A zero
 * value of the function parameter implies the infinite number of TX attempts.
 *
 * @param max_tx_attempts The maximum number of TX attempts.
 */
void nrf_gzll_set_max_tx_attempts(uint16_t max_tx_attempts);

/**
 * @brief Get function counterpart to nrf_gzll_set_max_tx_attempts().
 *
 * @return The current max Device TX attempts.
 */
uint16_t nrf_gzll_get_max_tx_attempts(void);

/**
 * @brief Set the table of Radio Frequency (RF) channels.
 *
 * The valid channels are in the range 0 <= channel <= 125, where the
 * actual centre frequency is (2400 + channel) MHz.
 * The maximum channel table size is defined by
 * NRF_GZLL_CONST_MAX_CHANNEL_TABLE_SIZE.
 *
 * @param p_channel_table Pointer to the channel table.
 * @param size            The size of the channel table.
 *
 * @retval true  If the channel table was set.
 * @retval false If Gazell was enabled, or the channel_table pointer was NULL,
 *               or the size was invalid.
 */
bool nrf_gzll_set_channel_table(uint8_t * p_channel_table, uint32_t size);

/**
 * @brief Get the table of Radio Frequency (RF) channels.
 *
 * @param p_channel_table Pointer to copy the channel table to.
 * @param p_size          Pointer to copy the size of the channel table to.
 *                        The value already at size must be at least the size
 *                        of the channel table.
 *
 * @retval true  If the channel table was copied to channel_table.
 * @retval false If the channel_table pointer was NULL,
 *               or the size was not large enough.
 */
bool nrf_gzll_get_channel_table(uint8_t * p_channel_table, uint32_t * p_size);

/**
 * @brief Get the current channel table size.
 *
 * @return The current channel table size.
 */
uint32_t nrf_gzll_get_channel_table_size(void);

/**
 * @brief Set the radio TX power.
 *
 * @param tx_power TX power.
 *
 * @retval true  If the parameter was set.
 * @retval false If the TX power was invalid.
*/
bool nrf_gzll_set_tx_power(nrf_gzll_tx_power_t tx_power);

/**
 * @brief Get function counterpart to nrf_gzll_set_tx_power().
 *
 * @return The current TX power.
 */
nrf_gzll_tx_power_t nrf_gzll_get_tx_power(void);

/**
 * @brief Set the radio datarate.
 *
 * @param data_rate Datarate.
 *
 * @retval true  If the parameter was set.
 * @retval false If Gazell was enabled or the datarate was invalid.
 */
bool nrf_gzll_set_datarate(nrf_gzll_datarate_t data_rate);

/**
 * @brief Get function counterpart to nrf_gzll_set_datarate().
 *
 * @return The current datarate.
 */
nrf_gzll_datarate_t nrf_gzll_get_datarate(void);

/**
 * @brief Set whether start/stop of external oscillator (XOSC) shall be handled
 * automatically inside Gazell or manually by the application.
 *
 * When controlling the XOSC manually from the application it is
 * required that the XOSC is started before Gazell is enabled.
 *
 * When start/stop of the XOSC is handled automatically by Gazell,
 * the XOSC will only be running when needed, that is when the radio
 * is being used or when Gazell needs to maintain synchronization.
 *
 * It is required that the XOSC is started in order for the radio to be
 * able to send or receive any packets.
 *
 * @param xosc_ctl setting for XOSC control.
 *
 * @retval true  if the parameter was set.
 * @retval false if Gazell was enabled or the xosc_ctl value was invalid.
 */
bool nrf_gzll_set_xosc_ctl(nrf_gzll_xosc_ctl_t xosc_ctl);

/**
 * Get function counterpart for nrf_gzll_set_xosc_ctl();
 *
 * @return The XOSC control setting.
 */
nrf_gzll_xosc_ctl_t nrf_gzll_get_xosc_ctl(void);

/**
 * @brief Set Gazell to disable automatically after a certain number of timeslot ticks.
 *
 * @param num_ticks Number of timeslot ticks.
 *
 */
void nrf_gzll_set_auto_disable(uint32_t num_ticks);

#if defined(NRF52_SERIES) || defined(__SDK_DOXYGEN__)
/**
 * @brief Set up external front end control.
 *
 * @param p_pa_lna_cfg Pointer to the configuration struct.
 */
bool nrf_gzll_set_pa_lna_cfg(nrf_gzll_pa_lna_cfg_t const * p_pa_lna_cfg);
#endif

/**
 * @brief Get the number of timeslot ticks that have occurred since
 *        nrf_gzll_init() was called.
 *
 * @return Number of timeslot ticks.
 *
 */
uint32_t nrf_gzll_get_tick_count(void);

/**
 * @brief Clear the internal timeslot tick count variable that is read
 * by nrf_gzll_get_tick_count().
 *
 */
void nrf_gzll_clear_tick_count(void);

/** @} */

/******************************************************************************/
/** @name Error handling functions
 * @{ */
/******************************************************************************/

/**
 * @brief Gets the Gazell error code.
 *
 * @return The current error code.
 */
nrf_gzll_error_code_t nrf_gzll_get_error_code(void);


/**
 * @brief Reset the Gazell error code.
 *
 * The error code is reset to NRF_GZLL_ERROR_CODE_NO_ERRROR.
 */
void nrf_gzll_reset_error_code(void);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif
