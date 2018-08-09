/**
* \copyright
* Copyright (c) 2018, Infineon Technologies AG
* All rights reserved.                                                         
*
* This software is provided with terms and conditions as specified in OPTIGA(TM) Trust X Evaluation Kit License Agreement.
* \endcopyright
*
* \author Infineon AG
*
* \file ifx_i2c_config.h
*
* \brief   This file defines the structures and macros for the Infineon I2C Protocol.
*
* \addtogroup  grIFXI2C
* @{
*/

#ifndef _IFX_I2C_CONFIG_H_
#define _IFX_I2C_CONFIG_H_
#ifdef __cplusplus
extern "C" {
#endif
    
/***********************************************************************************************************************
* HEADER FILES
**********************************************************************************************************************/
// Protocol Stack Includes
#include <stdint.h>
#include "pal_i2c.h"
#include "pal_gpio.h"
#include "pal_os_timer.h"

/***********************************************************************************************************************
* MACROS
**********************************************************************************************************************/

/** @brief I2C slave address of the Infineon device */
#define IFX_I2C_BASE_ADDR           (0x30)

/** @brief Physical Layer: polling interval in microseconds */
#define PL_POLLING_INVERVAL_US      (1000)
/** @brief Physical layer: maximal attempts */
#define PL_POLLING_MAX_CNT          (200)
/** @brief Physical Layer: data register polling interval in microseconds */
#define PL_DATA_POLLING_INVERVAL_US (5000)
/** @brief Physical Layer: guard time interval in microseconds */
#define PL_GUARD_TIME_INTERVAL_US   (50)

/** @brief Data link layer: maximum frame size */
#define DL_MAX_FRAME_SIZE           (300)
/** @brief Data link layer: header size */
#define DL_HEADER_SIZE              (5)
/** @brief Data link layer: maximum number of retries in case of transmission error */
#define DL_TRANS_REPEAT             (3)
/** @brief Data link layer: Trans timeout in milliseconds*/
#define PL_TRANS_TIMEOUT_MS         (10)

/** @brief Transport layer: Maximum exit timeout in seconds */
#define TL_MAX_EXIT_TIMEOUT         (6)

/** @brief Reset low time for GPIO pin toggling */
#define RESET_LOW_TIME_MSEC         (2000)
/** @brief Start up time */
#define STARTUP_TIME_MSEC           (12000)

/** @brief Protocol Stack: Status codes for success */
#define IFX_I2C_STACK_SUCCESS       (0x00)
/** @brief Protocol Stack: Status codes for error */
#define IFX_I2C_STACK_ERROR         (0x01)
/** @brief Protocol Stack: Status codes busy */
#define IFX_I2C_STACK_BUSY          (0x02)
/** @brief Protocol Stack: Memory insufficient */
#define IFX_I2C_STACK_MEM_ERROR     (0x03)
/** @brief Protocol Stack: Fatal error. Used internal to IFX I2C Stack */
#define IFX_I2C_FATAL_ERROR         (0x04)

/** @brief Offset of Datalink header in tx_frame_buffer */
#define IFX_I2C_DL_HEADER_OFFSET    (0)
/** @brief Offset of Transport header in tx_frame_buffer */
#define IFX_I2C_TL_HEADER_OFFSET    (IFX_I2C_DL_HEADER_OFFSET+3)

/** @brief Protocol Stack debug switch for physical layer (set to 0 or 1) */
#define IFX_I2C_LOG_PL              0
/** @brief Protocol Stack debug switch for data link layer (set to 0 or 1) */
#define IFX_I2C_LOG_DL              0
/** @brief Protocol Stack debug switch for transport layer (set to 0 or 1) */
#define IFX_I2C_LOG_TL              0

/** @brief Log ID number for physical layer */
#define IFX_I2C_LOG_ID_PL           0x00
/** @brief Log ID number for data link layer */
#define IFX_I2C_LOG_ID_DL           0x01
/** @brief Log ID number for transport layer */
#define IFX_I2C_LOG_ID_TL           0x02
/** @brief Log ID number for platform abstraction layer */
#define IFX_I2C_LOG_ID_PAL          0x04

/***********************************************************************************************************************
* ENUMS
***********************************************************************************************************************/


/***********************************************************************************************************************
* DATA STRUCTURES
***********************************************************************************************************************/
typedef struct ifx_i2c_context ifx_i2c_context_t;

/** @brief Event handler function prototype */
typedef void (*ifx_i2c_event_handler_t)(struct ifx_i2c_context* ctx, host_lib_status_t event, const uint8_t* data, uint16_t data_len);

/** @brief Physical layer structure */
typedef struct ifx_i2c_pl
{    
    // Physical Layer low level interface variables
    
    /// Physical layer buffer
    uint8_t buffer[DL_MAX_FRAME_SIZE+1];
    /// Tx length
    uint16_t buffer_tx_len;
    /// Rx length
    uint16_t buffer_rx_len;
    /// Action on register, read/write    
    uint8_t  register_action;
    /// i2c read/i2c write
    uint8_t  i2c_cmd;
    /// Retry counter
    uint16_t retry_counter;
    
    // Physical Layer high level interface variables
    
    /// Action of frame. Tx/Rx
    uint8_t   frame_action;
    /// Frame state
    uint8_t   frame_state ;
    /// Pointer to data to be sent
    uint8_t * p_tx_frame;
    /// Length of data to be sent
    uint16_t  tx_frame_len;
    // Upper layer handler
    ifx_i2c_event_handler_t upper_layer_event_handler;
    
    // Physical Layer negotiation/soft reset variables
    
    /// Negotiation state
    uint8_t   negotiate_state;
    /// Soft reset requested
    uint8_t   request_soft_reset;
} ifx_i2c_pl_t;

/** @brief Datalink layer structure */
typedef struct ifx_i2c_dl
{  
    // Data Link layer internal state variables
    
    /// Datalink layer state
    uint8_t state;
    /// Tx sequence number
    uint8_t tx_seq_nr;
    // Rx sequence number
    uint8_t rx_seq_nr;
    /// Indicate only Rx required
    uint8_t action_rx_only;
    /// Retransmit counter
    uint8_t retransmit_counter;
    /// Error occured
    uint8_t error;
    /// Resynced
    uint8_t resynced;
    /// Timeout value
    uint32_t data_poll_timeout;
    /// Transmit buffer size
    uint16_t tx_buffer_size;
    /// Receive buffer size
    uint16_t rx_buffer_size;
    /// Pointer to main transmit buffers
    uint8_t* p_tx_frame_buffer;
    /// Pointer to main receive buffers
    uint8_t* p_rx_frame_buffer;
    ///Start time of sending frame
    uint32_t frame_start_time;
    // Upper layer Event handler
    ifx_i2c_event_handler_t upper_layer_event_handler;
} ifx_i2c_dl_t;

/** @brief Transport layer structure */
typedef struct ifx_i2c_tl
{
    // Transport Layer state and buffer
    
    /// Transport layer state
    uint8_t  state;
    /// Pointer to packet provided by user
    uint8_t* p_actual_packet;
    /// Total received data
    uint16_t total_recv_length;
    /// Actual length of user provided packet
    uint16_t actual_packet_length;
    /// Offset till which data is sent from p_actual_packet
    uint16_t packet_offset;
    /// Maximum length of packet at transport layer
    uint16_t max_packet_length;
    /// Pointer to user provided receive buffer
    uint8_t* p_recv_packet_buffer;
    /// Length of receive buffer
    uint16_t* p_recv_packet_buffer_length;
    /// Start time of the transport layer API
    uint32_t api_start_time;
	///Chaining error coutn from slave
	uint8_t chaining_error_count;
	///Chaining error count for master
	uint8_t master_chaining_error_count;
	///State to check last chaining state
	uint8_t previous_chaining;
    /// transmission done
    uint8_t transmission_completed;
	/// Error event state
	uint8_t error_event;
    
    /// Upper layer event handler
    ifx_i2c_event_handler_t upper_layer_event_handler;
} ifx_i2c_tl_t;

/** @brief IFX I2C context structure */
struct ifx_i2c_context
{
    /// I2C Slave address
    uint8_t slave_address;
    /// Frequency of i2c master
    uint16_t frequency;
    /// Data link layer frame size
    uint16_t frame_size;
    /// Pointer to pal gpio context for vdd
    pal_gpio_t* p_slave_vdd_pin;
    /// Pointer to pal gpio context for reset
    pal_gpio_t* p_slave_reset_pin;  
    /// Pointer to pal i2c context
    pal_i2c_t* p_pal_i2c_ctx;
     
    /// Upper layer event handler
    app_event_handler_t upper_layer_event_handler;
    /// Upper layer context
    void* p_upper_layer_ctx;
    /// Pointer to upper layer rx buffer
    uint8_t* p_upper_layer_rx_buffer;
    /// Pointer to length of upper layer rx buffer
    uint16_t* p_upper_layer_rx_buffer_len;
    
    /// Protocol variables
	/// ifx i2c wrapper apis state
    uint8_t state;
	/// ifx i2c wrapper api status
    uint8_t status;
    /// reset states
    uint8_t reset_state;
    /// type of reset
    uint8_t reset_type;
    /// init pal
    uint8_t do_pal_init;
    
    /// Transport layer context
    ifx_i2c_tl_t tl;
    /// Datalink layer context
    ifx_i2c_dl_t dl;
    /// Physical layer context
    ifx_i2c_pl_t pl;
    
    /// IFX I2C tx frame of max length
    uint8_t tx_frame_buffer[DL_MAX_FRAME_SIZE];
    /// IFX I2C rx frame of max length
    uint8_t rx_frame_buffer[DL_MAX_FRAME_SIZE];
       
};

/***********************************************************************************************************************
* GLOBAL
***********************************************************************************************************************/

/** @brief IFX I2C Instance */
extern ifx_i2c_context_t ifx_i2c_context_0;

/***********************************************************************************************************************
* LOCAL ROUTINES
***********************************************************************************************************************/

/***********************************************************************************************************************
* API PROTOTYPES
**********************************************************************************************************************/

/**
 * @}
 **/
#ifdef __cplusplus
}
#endif
#endif /* _IFX_I2C_CONFIG_H_ */
