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
 * @file     drv_spi.h
 * @brief    header file for spi driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CSI_SPI_H_
#define _CSI_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <drv_common.h>
#include <config.h>
#ifdef CONFIG_SPI_DMA
#include <drv_dmac.h>
#endif

/// definition for spi handle.
typedef void *spi_handle_t;

/****** SPI specific error codes *****/
typedef enum {
    EDRV_SPI_MODE  = (EDRV_SPECIFIC + 1),     ///< Specified Mode not supported
    EDRV_SPI_FRAME_FORMAT,                       ///< Specified Frame Format not supported
    EDRV_SPI_DATA_BITS,                          ///< Specified number of Data bits not supported
    EDRV_SPI_BIT_ORDER,                          ///< Specified Bit order not supported
    EDRV_SPI_SS_MODE                             ///< Specified Slave Select Mode not supported
} drv_spi_err_e;

/*----- SPI Control Codes: Mode -----*/
typedef enum {
    SPI_MODE_INACTIVE = 0,       ///< SPI Inactive
    SPI_MODE_MASTER,             ///< SPI Master (Output on MOSI, Input on MISO); arg = Bus Speed in bps
    SPI_MODE_SLAVE,              ///< SPI Slave  (Output on MISO, Input on MOSI)
    SPI_MODE_MASTER_SIMPLEX,     ///< SPI Master (Output/Input on MOSI); arg = Bus Speed in bps
    SPI_MODE_SLAVE_SIMPLEX       ///< SPI Slave  (Output/Input on MISO)
} spi_mode_e;

/*----- SPI Control Codes: Mode Parameters: Frame Format -----*/
typedef enum {
    SPI_FORMAT_CPOL0_CPHA0 = 0, ///< Clock Polarity 0, Clock Phase 0 (default)
    SPI_FORMAT_CPOL0_CPHA1,     ///< Clock Polarity 0, Clock Phase 1
    SPI_FORMAT_CPOL1_CPHA0,     ///< Clock Polarity 1, Clock Phase 0
    SPI_FORMAT_CPOL1_CPHA1,     ///< Clock Polarity 1, Clock Phase 1
} spi_format_e;

/*----- SPI Control Codes: Mode Parameters: Bit Order -----*/
typedef enum {
    SPI_ORDER_MSB2LSB = 0,  ///< SPI Bit order from MSB to LSB (default)
    SPI_ORDER_LSB2MSB       ///< SPI Bit order from LSB to MSB
} spi_bit_order_e;

/*----- SPI Control Codes: Mode Parameters: Data Width in bits -----*/
#define SPI_DATAWIDTH_MAX 32         /* 1 ~ 32 bit*/

/*----- SPI Control Codes: Mode Parameters: Slave Select Mode -----*/
typedef enum {
    /*options for SPI_MODE_MASTER/SPI_MODE_MASTER_SIMPLEX */
    SPI_SS_MASTER_UNUSED = 0,        ///< SPI Slave Select when Master: Not used (default).SS line is not controlled by master, For example,SS line connected to a fixed low level
    SPI_SS_MASTER_SW,               ///< SPI Slave Select when Master: Software controlled. SS line is configured by software
    SPI_SS_MASTER_HW_OUTPUT,         ///< SPI Slave Select when Master: Hardware controlled Output.SS line is activated or deactivated automatically by hardware
    SPI_SS_MASTER_HW_INPUT,          ///< SPI Slave Select when Master: Hardware monitored Input.Used in multi-master configuration where a master does not drive the Slave Select when driving the bus, but rather monitors it
    /*options for SPI_MODE_SLAVE/SPI_MODE_SLAVE_SIMPLEX */
    SPI_SS_SLAVE_HW,                 ///< SPI Slave Select when Slave: Hardware monitored (default).Hardware monitors the Slave Select line and accepts transfers only when the line is active
    SPI_SS_SLAVE_SW                  ///< SPI Slave Select when Slave: Software controlled.Used only when the Slave Select line is not used. Software controls if the slave is responding or not(enables or disables transfers)
} spi_ss_mode_e;

/****** SPI Slave Select Signal definitions *****/
typedef enum {
    SPI_SS_INACTIVE = 0,        ///< SPI Slave Select Signal/line Inactive
    SPI_SS_ACTIVE               ///< SPI Slave Select Signal/line Active
} spi_ss_stat_e;

/**
\brief SPI Status
*/
typedef struct {
    uint32_t busy       : 1;              ///< Transmitter/Receiver busy flag
    uint32_t data_lost  : 1;              ///< Data lost: Receive overflow / Transmit underflow (cleared on start of transfer operation)
    uint32_t mode_fault : 1;              ///< Mode fault detected; optional (cleared on start of transfer operation)
} spi_status_t;

/****** SPI Event *****/
typedef enum {
    SPI_EVENT_TRANSFER_COMPLETE = 0,   ///< Data Transfer completed. Occurs after call to ARM_SPI_Send, ARM_SPI_Receive, or ARM_SPI_Transfer to indicate that all the data has been transferred. The driver is ready for the next transfer operation
    SPI_EVENT_TX_COMPLETE,              ///< Data Transfer completed. Occurs after call to ARM_SPI_Send, ARM_SPI_Receive, or ARM_SPI_Transfer to indicate that all the data has been transferred. The driver is ready for the next transfer operation
    SPI_EVENT_RX_COMPLETE,              ///< Data Transfer completed. Occurs after call to ARM_SPI_Send, ARM_SPI_Receive, or ARM_SPI_Transfer to indicate that all the data has been transferred. The driver is ready for the next transfer operation
    SPI_EVENT_DATA_LOST,               ///< Data lost: Receive overflow / Transmit underflow. Occurs in slave mode when data is requested/sent by master but send/receive/transfer operation has not been started and indicates that data is lost. Occurs also in master mode when driver cannot transfer data fast enough.
    SPI_EVENT_MODE_FAULT               ///< Master Mode Fault (SS deactivated when Master).Occurs in master mode when Slave Select is deactivated and indicates Master Mode Fault. The driver is ready for the next transfer operation.
} spi_event_e;

typedef void (*spi_event_cb_t)(spi_event_e event, void *arg);  ///< Pointer to \ref spi_event_cb_t : SPI Event call back.

/**
\brief SPI Driver Capabilities.
*/
typedef struct {
    uint32_t simplex          : 1;        ///< supports Simplex Mode (Master and Slave)
    uint32_t ti_ssi           : 1;        ///< supports TI Synchronous Serial Interface
    uint32_t microwire        : 1;        ///< supports Microwire Interface
    uint32_t event_mode_fault : 1;        ///< Signal Mode Fault event: \ref spi_event_e
} spi_capabilities_t;

/**
  \brief       Initialize SPI Interface. 1. Initializes the resources needed for the SPI interface 2.registers event callback function
  \param[in]   mosi spi pin of mosi
  \param[in]   miso spi pin of miso
  \param[in]   sclk spi pin of sclk
  \param[in]   ssel spi pin of ssel
  \param[in]   cb_event  event call back function \ref spi_event_cb_t
  \param[in]   cb_arg    argument for call back function
  \return      return spi handle if success
*/
spi_handle_t csi_spi_initialize(pin_t mosi, pin_t miso, pin_t sclk, pin_t ssel, spi_event_cb_t cb_event, void *cb_arg);

/**
  \brief       De-initialize SPI Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle spi handle to operate.
  \return      error code
*/
int32_t csi_spi_uninitialize(spi_handle_t handle);

/**
  \brief       Get driver capabilities.
  \param[in]   handle spi handle to operate.
  \return      \ref spi_capabilities_t
*/
spi_capabilities_t csi_spi_get_capabilities(spi_handle_t handle);

/**
  \brief       config spi mode.
  \param[in]   handle spi handle to operate.
  \param[in]   sysclk    sysclk for spi module.
  \param[in]   baud      spi baud rate. if negative, then this attribute not changed
  \param[in]   mode      \ref spi_mode_e . if negative, then this attribute not changed
  \param[in]   format    \ref spi_format_e . if negative, then this attribute not changed
  \param[in]   order     \ref spi_bit_order_e . if negative, then this attribute not changed
  \param[in]   ss_mode   \ref spi_ss_mode_e . if negative, then this attribute not changed
  \param[in]   bit_width spi data bitwidth: (1 ~ SPI_DATAWIDTH_MAX) . if negative, then this attribute not changed
  \return      error code
*/
int32_t csi_spi_config(spi_handle_t handle,
                       int32_t          sysclk,
                       int32_t          baud,
                       spi_mode_e       mode,
                       spi_format_e     format,
                       spi_bit_order_e  order,
                       spi_ss_mode_e    ss_mode,
                       int32_t          bit_width);

/**
  \brief       config spi default tx value.
  \param[in]   handle spi handle to operate.
  \param[in]   value     default tx value
  \return      error code
*/
int32_t csi_spi_set_default_tx_value(spi_handle_t handle, uint32_t value);

/**
\brief         sending data to SPI transmitter,(received data is ignored).
               if non-blocking mode, this function only start the sending,
               \ref spi_event_e is signaled when operation completes or error happens.
               \ref csi_spi_get_status can indicates operation status.
               if blocking mode, this function return after operation completes or error happens.
  \param[in]   handle spi handle to operate.
  \param[in]   data  Pointer to buffer with data to send to SPI transmitter. data_type is : uint8_t for 1..8 data bits, uint16_t for 9..16 data bits,uint32_t for 17..32 data bits,
  \param[in]   num   Number of data items to send.
  \param[in]   block_mode   blocking and non_blocking to selcect
  \return      error code
*/
int32_t csi_spi_send(spi_handle_t handle, const void *data, uint32_t num, uint8_t block_mode);

/**
  \brief       receiving data from SPI receiver.transmits the default value as specified by csi_spi_set_default_tx_value
               if non-blocking mode, this function only start the receiving,
               \ref spi_event_e is signaled when operation completes or error happens.
               \ref csi_spi_get_status can indicates operation status.
               if blocking mode, this function return after operation completes or error happens.
  \param[in]   handle spi handle to operate.
  \param[out]  data  Pointer to buffer for data to receive from SPI receiver
  \param[in]   num   Number of data items to receive
  \param[in]   block_mode   blocking and non_blocking to selcect
  \return      error code
*/
int32_t csi_spi_receive(spi_handle_t handle, void *data, uint32_t num, uint8_t block_mode);

/**
  \brief       sending/receiving data to/from SPI transmitter/receiver.
               if non-blocking mode, this function only start the transfer,
               \ref spi_event_e is signaled when operation completes or error happens.
               \ref csi_spi_get_status can indicates operation status.
               if blocking mode, this function return after operation completes or error happens.
  \param[in]   handle spi handle to operate.
  \param[in]   data_out  Pointer to buffer with data to send to SPI transmitter
  \param[out]  data_in   Pointer to buffer for data to receive from SPI receiver
  \param[in]   num_out      Number of data items to send
  \param[in]   num_in       Number of data items to receive
  \param[in]   block_mode   blocking and non_blocking to selcect
  \return      error code
*/
int32_t csi_spi_transfer(spi_handle_t handle, const void *data_out, void *data_in, uint32_t num_out, uint32_t num_in, uint8_t block_mode);

/**
  \brief       abort spi transfer.
  \param[in]   handle spi handle to operate.
  \return      error code
*/
int32_t csi_spi_abort_transfer(spi_handle_t handle);

/**
  \brief       Get SPI status.
  \param[in]   handle spi handle to operate.
  \return      SPI status \ref spi_status_t
*/
spi_status_t csi_spi_get_status(spi_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* _CSI_SPI_H_ */
