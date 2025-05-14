 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     drv/qspi.h
 * @brief    Header File for QSPI Driver
 * @version  V1.0
 * @date     8. Apr 2020
 * @model    qspi
 ******************************************************************************/

#ifndef _DRV_QSPI_H_
#define _DRV_QSPI_H_

#include <stdint.h>
#include <stdbool.h>
#include <drv/common.h>
#include <drv/dma.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \enum      csi_qspi_clock_mode_t
 * \brief     QSPI clock mode
 */
typedef enum {
    QSPI_CLOCK_MODE_0 = 0,      ///< Clock Polarity 0, Clock Phase 0
    QSPI_CLOCK_MODE_1,          ///< Clock Polarity 0, Clock Phase 1
    QSPI_CLOCK_MODE_2,          ///< Clock Polarity 1, Clock Phase 0
    QSPI_CLOCK_MODE_3,          ///< Clock Polarity 1, Clock Phase 1
} csi_qspi_mode_t;

/**
 * \enum   csi_qspi_bus_width_t
 * \brief  QSPI bus width
 */
typedef enum {
    QSPI_CFG_BUS_SINGLE = 0,  ///< Single line
    QSPI_CFG_BUS_DUAL,        ///< Two line
    QSPI_CFG_BUS_QUAD,        ///< Four line
} csi_qspi_bus_width_t;

/**
 * \enum   csi_qspi_address_size_t
 * \brief  Address size in bits
 */
typedef enum {
    QSPI_ADDRESS_8_BITS = 0,
    QSPI_ADDRESS_16_BITS,
    QSPI_ADDRESS_24_BITS,
    QSPI_ADDRESS_32_BITS,
} csi_qspi_address_size_t;

/**
 * \enum      csi_qspi_alternate_bytes_size_t
 * rief       QSPI alternate bytes
 */
typedef enum {
    QSPI_ALTERNATE_8_BITS = 0,
    QSPI_ALTERNATE_16_BITS,
    QSPI_ALTERNATE_24_BITS,
    QSPI_ALTERNATE_32_BITS,
} csi_qspi_alt_size_t;

/** QSPI command
 *
 * Defines a frame format. It consists of instruction, address, alternative, dummy count and data
 */
typedef struct {
    struct {
        csi_qspi_bus_width_t bus_width; ///< Bus width for the instruction
        uint8_t value;                  ///< Instruction value
        bool disabled;                  ///< Instruction phase skipped if disabled is set to true
    } instruction;
    struct {
        csi_qspi_bus_width_t bus_width; ///< Bus width for the address
        csi_qspi_address_size_t size;   ///< Address size
        uint32_t value;                 ///< Address value
        bool disabled;                  ///< Address phase skipped if disabled is set to true
    }  address;
    struct {
        csi_qspi_bus_width_t bus_width; ///< Bus width for alternative
        csi_qspi_alt_size_t size;       ///< Alternative size
        uint32_t value;                 ///< Alternative value
        bool disabled;                  ///< Alternative phase skipped if disabled is set to true
    } alt;
    uint8_t dummy_count;                ///< Dummy cycles count
    struct {
        csi_qspi_bus_width_t bus_width; ///< Bus width for data
    } data;
    uint8_t ddr_enable;
} csi_qspi_command_t;

/**
 * \enum   csi_qspi_event_t
 * \brief  QSPI event
 */
typedef enum {
    QSPI_EVENT_COMMAND_COMPLETE = 0,    ///< Command completed
    QSPI_EVENT_ERROR,                   ///< An error has occurred
} csi_qspi_event_t;

/**
 * \struct csi_qspi_t
 * \brief  QSPI Handle Structure definition
 */

typedef struct csi_qspi csi_qspi_t;
struct csi_qspi {
    csi_dev_t         dev;              ///< QSPI hw-device info
    void (*callback)(csi_qspi_t *qspi, csi_qspi_event_t event, void *arg); ///< User callback function
    void              *arg;             ///< QSPI custom designed param passed to evt_cb
    uint8_t           *tx_data;         ///< Pointer to QSPI Tx transfer Buffer
    uint32_t          tx_size;          ///< QSPI Tx Transfer size
    uint8_t           *rx_data;         ///< Pointer to QSPI Rx transfer Buffer
    uint32_t          rx_size;          ///< QSPI Rx Transfer size
    void              *send;            ///< The send_async func
    void              *receive;         ///< The receive_async func
    void              *send_receive;    ///< The send_receive_async func
    csi_state_t       state;            ///< Peripheral state
    csi_dma_ch_t      *tx_dma;
    csi_dma_ch_t      *rx_dma;
    void              *priv;
};

/**
  \brief       Init QSPI ctrl block
               1. Initializes the QSPI mode according to the specified parameters in the csi_qspi_init_t
               2. Registers event callback function and user param for the callback
  \param[in]   qspi    Handle of QSPI instance
  \param[in]   idx     Index of instance
  \return      Error code
*/
csi_error_t csi_qspi_init(csi_qspi_t *qspi, uint32_t idx);


/**
  \brief       De-initialize QSPI Instance
               stops operation and releases the software resources used by the Instance
  \param[in]   qspi Handle of QSPI instance
*/
void csi_qspi_uninit(csi_qspi_t *qspi);

/**
  \brief       Attach the callback handler to QSPI
  \param[in]   qspi        Operate handle
  \param[in]   callback    Callback function
  \param[in]   arg         User can define it by himself as callback's param
  \return      Error code
*/
csi_error_t csi_qspi_attach_callback(csi_qspi_t *qspi, void *callback, void *arg);

/**
  \brief       Detach the callback handler
  \param[in]   qspi    Operate handle
  \return      None
*/
void csi_qspi_detach_callback(csi_qspi_t *qspi);

/**
  \brief      Config qspi frequence
  \param[in]  qspi    Handle of qspi instance
  \param[in]  hz      QSPI frequence
  \return     The actual config frequency
*/
uint32_t csi_qspi_frequence(csi_qspi_t *qspi, uint32_t hz);

/**
  \brief      Config qspi mode
  \param[in]  qspi    Handle of qspi instance
  \param[in]  mode    QSPI mode
  \return     Error code
*/
csi_error_t csi_qspi_mode(csi_qspi_t *qspi, csi_qspi_mode_t mode);

/**
  \brief       Send an amount of data in blocking mode
  \param[in]   qspi       QSPI handle
  \param[in]   cmd        Structure that contains the command configuration information
  \param[in]   data       Pointer to data buffer
  \param[in]   size       Size of data to send
  \param[in]   timeout    Time out duration
  \return      If send successful, this function shall return the num of data witch is sent successful
               otherwise, the function shall return error code
  */
int32_t csi_qspi_send(csi_qspi_t *qspi, csi_qspi_command_t *cmd, const void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Receive an amount of data in blocking mode
  \param[in]   qspi       QSPI handle
  \param[in]   cmd        Structure that contains the command configuration information
  \param[out]  data       Pointer to data buffer
  \param[in]   size       Size of data items to receive
  \param[in]   timeout    Time out duration
  \return      If receive successful, this function shall return the num of data witch is received successfulful
               otherwise, the function shall return error code
  */
int32_t csi_qspi_receive(csi_qspi_t *qspi, csi_qspi_command_t *cmd, void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Transfer an amount of data in blocking mode
  \param[in]   qspi       QSPI handle
  \param[in]   cmd        Structure that contains the command configuration information
  \param[in]   tx_data    Pointer to send data buffer
  \param[out]  rx_data    Pointer to receive data buffer
  \param[in]   size       Size of data to transfer
  \param[in]   timeout    Time out duration
  \return      If transfer successful, this function shall return the num of data witch is transfer successfulful
               otherwise, the function shall return error code
  */
int32_t csi_qspi_send_receive(csi_qspi_t *qspi, csi_qspi_command_t *cmd, const void *tx_data, void *rx_data, uint32_t size, uint32_t timeout);

/**
  \brief       Send an amount of data in async mode
  \param[in]   qspi    QSPI handle
  \param[in]   cmd     Structure that contains the command configuration information
  \param[in]   data    Pointer to data buffer
  \param[in]   size    Size of data to send
  \return      Data number send
  */
csi_error_t csi_qspi_send_async(csi_qspi_t *qspi, csi_qspi_command_t *cmd, const void *data, uint32_t size);

/**
  \brief       Receive an amount of data in async mode
  \param[in]   qspi    QSPI handle
  \param[in]   cmd     Structure that contains the command configuration information
  \param[out]  data    Pointer to data buffer
  \param[in]   size    Size of data items to receive
  \return      Data number received
  */
csi_error_t csi_qspi_receive_async(csi_qspi_t *qspi, csi_qspi_command_t *cmd, void *data, uint32_t size);

/**
  \brief       Transfer an amount of data in async mode
  \param[in]   qspi       QSPI handle
  \param[in]   cmd        Structure that contains the command configuration information
  \param[in]   tx_data    Pointer to send data buffer
  \param[out]  rx_data    Pointer to receive data buffer
  \param[in]   size       Size of data to transfer
  \return      Data number transfered
  */
csi_error_t csi_qspi_send_receive_async(csi_qspi_t *qspi, csi_qspi_command_t *cmd, const void *tx_data, void *rx_data, uint32_t size);

/**
  \brief       Link DMA channel to qspi device
  \param[in]   qspi      QSPI handle to operate
  \param[in]   tx_dma    The DMA channel handle for send, when it is NULL means to unlink the channel
  \param[in]   rx_dma    The DMA channel handle for receive, when it is NULL means to unlink the channel
  \return      Error code
*/
csi_error_t csi_qspi_link_dma(csi_qspi_t *qspi, csi_dma_ch_t *tx_dma, csi_dma_ch_t *rx_dma);

/**
  \brief       Get the state of qspi device
  \param[in]   qspi     QSPI handle
  \param[in]   state    QSPI state \ref csi_state_t
  \return      Error code
  */
csi_error_t csi_qspi_get_state(csi_qspi_t *qspi, csi_state_t *state);

/**
  \brief       Comfigure the memory mapped mode
  \param[in]   qspi    QSPI handle
  \param[in]   cmd     Structure that contains the command configuration information
  \return      Error code
  */
csi_error_t csi_qspi_memory_mapped(csi_qspi_t *qspi, csi_qspi_command_t *cmd);

/**
  \brief       Enable qspi power manage
  \param[in]   qspi    QSPI handle to operate
  \return      Error code
*/
csi_error_t csi_qspi_enable_pm(csi_qspi_t *qspi);

/**
  \brief       Disable qspi power manage
  \param[in]   qspi    QSPI handle to operate
  \return      None
*/
void csi_qspi_disable_pm(csi_qspi_t *qspi);

#ifdef __cplusplus
}
#endif

#endif  /* _DRV_QSPI_H_*/
