/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * @file     drv_usart.h
 * @brief    header file for usart driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CSI_USART_H_
#define _CSI_USART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <drv_common.h>

/// definition for usart handle.
typedef void *usart_handle_t;

/****** USART specific error codes *****/
typedef enum {
    EDRV_USART_MODE  = (EDRV_SPECIFIC + 1),      ///< Specified Mode not supported
    EDRV_USART_BAUDRATE,                         ///< Specified baudrate not supported
    EDRV_USART_DATA_BITS,                        ///< Specified number of Data bits not supported
    EDRV_USART_PARITY,                           ///< Specified Parity not supported
    EDRV_USART_STOP_BITS,                        ///< Specified number of Stop bits not supported
    EDRV_USART_FLOW_CONTROL,                     ///< Specified Flow Control not supported
    EDRV_USART_CPOL,                             ///< Specified Clock Polarity not supported
    EDRV_USART_CPHA                              ///< Specified Clock Phase not supported
} drv_usart_error_e;

/*----- USART Control Codes: Mode -----*/
typedef enum {
    USART_MODE_ASYNCHRONOUS         = 0,   ///< USART (Asynchronous)
    USART_MODE_SYNCHRONOUS_MASTER      ,   ///< Synchronous Master
    USART_MODE_SYNCHRONOUS_SLAVE       ,   ///< Synchronous Slave (external clock signal)
    USART_MODE_SINGLE_WIRE                 ///< USART Single-wire (half-duplex)
} usart_mode_e;

/*----- USART Control Codes: Mode Parameters: Data Bits -----*/
typedef enum {
    USART_DATA_BITS_5             = 0,    ///< 5 Data bits
    USART_DATA_BITS_6                ,    ///< 6 Data bit
    USART_DATA_BITS_7                ,    ///< 7 Data bits
    USART_DATA_BITS_8                ,    ///< 8 Data bits (default)
    USART_DATA_BITS_9                     ///< 9 Data bits
} usart_data_bits_e;

/*----- USART Control Codes: Mode Parameters: Parity -----*/
typedef enum {
    USART_PARITY_NONE            = 0,       ///< No Parity (default)
    USART_PARITY_EVEN               ,       ///< Even Parity
    USART_PARITY_ODD                ,       ///< Odd Parity
    USART_PARITY_1                  ,       ///< Parity forced to 1
    USART_PARITY_0                          ///< Parity forced to 0
} usart_parity_e;

/*----- USART Control Codes: Mode Parameters: Stop Bits -----*/
typedef enum {
    USART_STOP_BITS_1            = 0,    ///< 1 Stop bit (default)
    USART_STOP_BITS_2               ,    ///< 2 Stop bits
    USART_STOP_BITS_1_5             ,    ///< 1.5 Stop bits
    USART_STOP_BITS_0_5                  ///< 0.5 Stop bits
} usart_stop_bits_e;

/*----- USART Control Codes: Mode Parameters: Clock Polarity (Synchronous mode) -----*/
typedef enum {
    USART_CPOL0                  = 0,    ///< CPOL = 0 (default)
    USART_CPOL1                          ///< CPOL = 1
} usart_cpol_e;

/*----- USART Control Codes: Mode Parameters: Clock Phase (Synchronous mode) -----*/
typedef enum {
    USART_CPHA0                  = 0,   ///< CPHA = 0 (default)
    USART_CPHA1                         ///< CPHA = 1
} usart_cpha_e;

/*----- USART Control Codes: flush data type-----*/
typedef enum {
    USART_FLUSH_WRITE,
    USART_FLUSH_READ
} usart_flush_type_e;

/**
\brief USART Status
*/
typedef struct  {
    uint32_t tx_busy          : 1;        ///< Transmitter busy flag
    uint32_t rx_busy          : 1;        ///< Receiver busy flag
    uint32_t tx_underflow     : 1;        ///< Transmit data underflow detected (cleared on start of next send operation)(Synchronous Slave)
    uint32_t rx_overflow      : 1;        ///< Receive data overflow detected (cleared on start of next receive operation)
    uint32_t rx_break         : 1;        ///< Break detected on receive (cleared on start of next receive operation)
    uint32_t rx_framing_error : 1;        ///< Framing error detected on receive (cleared on start of next receive operation)
    uint32_t rx_parity_error  : 1;        ///< Parity error detected on receive (cleared on start of next receive operation)
} usart_status_t;

/****** USART Event *****/
typedef enum {
    USART_EVENT_SEND_COMPLETE       = 0,  ///< Send completed; however USART may still transmit data
    USART_EVENT_RECEIVE_COMPLETE    = 1,  ///< Receive completed
    USART_EVENT_RECEIVED            = 2,  ///< Receiving data
    USART_EVENT_TRANSFER_COMPLETE   = 3,  ///< Transfer completed
    USART_EVENT_TX_COMPLETE         = 4,  ///< Transmit completed (optional)
    USART_EVENT_TX_UNDERFLOW        = 5,  ///< Transmit data not available (Synchronous Slave)
    USART_EVENT_RX_OVERFLOW         = 6,  ///< Receive data overflow
    USART_EVENT_RX_TIMEOUT          = 7,  ///< Receive character timeout (optional)
    USART_EVENT_RX_BREAK            = 8,  ///< Break detected on receive
    USART_EVENT_RX_FRAMING_ERROR    = 9,  ///< Framing error detected on receive
    USART_EVENT_RX_PARITY_ERROR     = 10,  ///< Parity error detected on receive
} usart_event_e;

typedef void (*usart_event_cb_t)(usart_event_e event, void *cb_arg);   ///< Pointer to \ref usart_event_cb_t : USART Event call back.

/**
\brief USART Driver Capabilities.
*/
typedef struct  {
    uint32_t asynchronous       : 1;      ///< supports USART (Asynchronous) mode
    uint32_t synchronous_master : 1;      ///< supports Synchronous Master mode
    uint32_t synchronous_slave  : 1;      ///< supports Synchronous Slave mode
    uint32_t single_wire        : 1;      ///< supports USART Single-wire mode
    uint32_t event_tx_complete  : 1;      ///< Transmit completed event
    uint32_t event_rx_timeout   : 1;      ///< Signal receive character timeout event
} usart_capabilities_t;

/**
  \brief       Initialize USART Interface. 1. Initializes the resources needed for the USART interface 2.registers event callback function
  \param[in]   tx usart pin of tx
  \param[in]   rx usart pin of rx
  \param[in]   cb_event  Pointer to \ref usart_event_cb_t
  \param[in]   cb_arg    argument for cb_event
  \return      return usart handle if success
*/
usart_handle_t csi_usart_initialize(pin_t tx, pin_t rx, usart_event_cb_t cb_event, void *cb_arg);

/**
  \brief       De-initialize USART Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  usart handle to operate.
  \return      error code
*/
int32_t csi_usart_uninitialize(usart_handle_t handle);
/**
  \brief       Get driver capabilities.
  \param[in]   handle  usart handle to operate.
  \return      \ref usart_capabilities_t
*/
usart_capabilities_t csi_usart_get_capabilities(usart_handle_t handle);

/**
  \brief       config usart mode.
  \param[in]   handle  usart handle to operate.
  \param[in]   sysclk    system clock.
  \param[in]   baud      configured baud .
  \param[in]   mode      \ref usart_mode_e .
  \param[in]   parity    \ref usart_parity_e .
  \param[in]   stopbits  \ref usart_stop_bits_e .
  \param[in]   bits      \ref usart_data_bits_e .
  \return      error code
*/
int32_t csi_usart_config(usart_handle_t handle,
                         uint32_t sysclk,
                         uint32_t baud,
                         usart_mode_e mode,
                         usart_parity_e parity,
                         usart_stop_bits_e stopbits,
                         usart_data_bits_e bits);

/**
  \brief       config usart default tx value. used in synchronous mode
  \param[in]   handle  usart handle to operate.
  \param[in]   value  default tx value
  \return      error code
*/
int32_t csi_usart_set_default_tx_value(usart_handle_t handle, uint32_t value);

/**
  \brief       Start sending data to USART transmitter,(received data is ignored).
               This function is non-blocking,\ref usart_event_e is signaled when operation completes or error happens.
               \ref csi_usart_get_status can indicates operation status.
  \param[in]   handle  usart handle to operate.
  \param[in]   data  Pointer to buffer with data to send to USART transmitter. data_type is : uint8_t for 5..8 data bits, uint16_t for 9 data bits
  \param[in]   num   Number of data items to send
  \return      error code
*/
int32_t csi_usart_send(usart_handle_t handle, const void *data, uint32_t num/*,bool asynch*/);

/**
  \brief       Abort Send data to USART transmitter
  \param[in]   handle  usart handle to operate.
  \return      error code
*/
int32_t csi_usart_abort_send(usart_handle_t handle);

/**
  \brief       Start receiving data from USART receiver.transmits the default value as specified by csi_usart_set_default_tx_value. \n
               This function is non-blocking,\ref usart_event_e is signaled when operation completes or error happens.
               \ref csi_usart_get_status can indicates operation status.
  \param[in]   handle  usart handle to operate.
  \param[out]  data  Pointer to buffer for data to receive from USART receiver.data_type is : uint8_t for 5..8 data bits, uint16_t for 9 data bits
  \param[in]   num   Number of data items to receive
  \return      error code
*/
int32_t csi_usart_receive(usart_handle_t handle, void *data, uint32_t num/*,bool asynch*/);

/**
  \brief       query data from UART receiver FIFO.
  \param[in]   handle  usart handle to operate.
  \param[out]  data  Pointer to buffer for data to receive from UART receiver
  \param[in]   num   Number of data items to receive
  \return      receive fifo data num
*/
int32_t csi_usart_receive_query(usart_handle_t handle, void *data, uint32_t num/*,bool asynch*/);

/**
  \brief       Abort Receive data from USART receiver
  \param[in]   handle  usart handle to operate.
  \return      error code
*/
int32_t csi_usart_abort_receive(usart_handle_t handle);

/**
  \brief       Start synchronously sends data to the USART transmitter and receives data from the USART receiver. used in synchronous mode
               This function is non-blocking,\ref usart_event_e is signaled when operation completes or error happens.
               \ref csi_usart_get_status can indicates operation status.
  \param[in]   handle  usart handle to operate.
  \param[in]   data_out  Pointer to buffer with data to send to USART transmitter.data_type is : uint8_t for 5..8 data bits, uint16_t for 9 data bits
  \param[out]  data_in   Pointer to buffer for data to receive from USART receiver.data_type is : uint8_t for 5..8 data bits, uint16_t for 9 data bits
  \param[in]   num       Number of data items to transfer
  \return      error code
*/
int32_t csi_usart_transfer(usart_handle_t handle, const void *data_out, void *data_in, uint32_t num/*,bool asynch*/);

/**
  \brief       abort sending/receiving data to/from USART transmitter/receiver.
  \param[in]   handle  usart handle to operate.
  \return      error code
*/
int32_t csi_usart_abort_transfer(usart_handle_t handle);

/**
  \brief       Get USART status.
  \param[in]   handle  usart handle to operate.
  \return      USART status \ref usart_status_t
*/
usart_status_t csi_usart_get_status(usart_handle_t handle);

/**
  \brief       flush receive/send data.
  \param[in]   handle usart handle to operate.
  \param[in]   type \ref usart_flush_type_e .
  \return      error code
*/
int32_t csi_usart_flush(usart_handle_t handle, usart_flush_type_e type);


//add function
int32_t dw_usart_getchar(usart_handle_t handle, uint8_t *ch);
int32_t dw_usart_getchar_no_poll(usart_handle_t handle, uint8_t *ch);
int32_t dw_usart_putchar(usart_handle_t handle, uint8_t ch);
int32_t dw_usart_set_int_flag(usart_handle_t handle,uint32_t flag);
int32_t dw_usart_clr_int_flag(usart_handle_t handle,uint32_t flag);

#ifdef __cplusplus
}
#endif

#endif /* _CSI_USART_H_ */
