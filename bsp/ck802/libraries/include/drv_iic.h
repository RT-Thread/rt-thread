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
 * @file     drv_iic.h
 * @brief    header file for iic driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CSI_IIC_H_
#define _CSI_IIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <drv_common.h>

/// definition for iic handle.
typedef void *iic_handle_t;

/*----- IIC Control Codes: Mode -----*/
typedef enum {
    IIC_MODE_MASTER,             ///< IIC Master
    IIC_MODE_SLAVE               ///< IIC Slave
} iic_mode_e;

/*----- IIC Control Codes: IIC Bus Speed -----*/
typedef enum {
    I2C_BUS_SPEED_STANDARD  = 0, ///< Standard Speed (100kHz)
    I2C_BUS_SPEED_FAST      = 1, ///< Fast Speed     (400kHz)
    I2C_BUS_SPEED_FAST_PLUS = 2, ///< Fast+ Speed    (  1MHz)
    I2C_BUS_SPEED_HIGH      = 3  ///< High Speed     (3.4MHz)
} iic_speed_e;

/*----- IIC Control Codes: IIC Address Mode -----*/
typedef enum {
    I2C_ADDRESS_7BIT        = 0,  ///< 7-bit address mode
    I2C_ADDRESS_10BIT       = 1   ///< 10-bit address mode
} iic_address_mode_e;

/**
\brief IIC Status
*/
typedef struct {
    uint32_t busy             : 1;        ///< Transmitter/Receiver busy flag
    uint32_t mode             : 1;        ///< Mode: 0=Slave, 1=Master
    uint32_t direction        : 1;        ///< Direction: 0=Transmitter, 1=Receiver
    uint32_t general_call     : 1;        ///< General Call(address 0) indication (cleared on start of next Slave operation)
    uint32_t arbitration_lost : 1;        ///< Master lost arbitration(in case of multi-masters) (cleared on start of next Master operation)
    uint32_t bus_error        : 1;        ///< Bus error detected (cleared on start of next Master/Slave operation)
} iic_status_t;

/****** IIC Event *****/
typedef enum {
    I2C_EVENT_TRANSFER_DONE        = 0,  ///< Master/Slave Transmit/Receive finished
    I2C_EVENT_TRANSFER_INCOMPLETE  = 1,  ///< Master/Slave Transmit/Receive incomplete transfer
    I2C_EVENT_SLAVE_TRANSMIT       = 2,  ///< Slave Transmit operation requested
    I2C_EVENT_SLAVE_RECEIVE        = 3,  ///< Slave Receive operation requested
    I2C_EVENT_ADDRESS_NACK         = 4,  ///< Address not acknowledged from Slave
    I2C_EVENT_GENERAL_CALL         = 5,  ///< General Call indication
    I2C_EVENT_ARBITRATION_LOST     = 6,  ///< Master lost arbitration
    I2C_EVENT_BUS_ERROR            = 7,  ///< Bus error detected (START/STOP at illegal position)
    I2C_EVENT_BUS_CLEAR            = 8   ///< Bus clear finished
} iic_event_e;

typedef void (*iic_event_cb_t)(iic_event_e event, void *arg);  ///< Pointer to \ref iic_event_cb_t : IIC Event call back.

/**
\brief IIC Driver Capabilities.
*/
typedef struct  {
    uint32_t address_10_bit : 1;          ///< supports 10-bit addressing
} iic_capabilities_t;

/**
  \brief       Initialize IIC Interface specified by pins. \n
               1. Initializes the resources needed for the IIC interface 2.registers event callback function
  \param[in]   scl  scl pin of iic.
  \param[in]   sda  sda pin of iic.
  \param[in]   cb_event  Pointer to \ref iic_event_cb_t
  \param[in]   cb_arg    argument for call back function
  \return      0 for success, negative for error code
*/
iic_handle_t csi_iic_initialize(pin_t scl, pin_t sda, iic_event_cb_t cb_event, void *cb_arg);

/**
  \brief       De-initialize IIC Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  iic handle to operate.
  \return      0 for success, negative for error code
*/
int32_t csi_iic_uninitialize(iic_handle_t handle);

/**
  \brief       Get driver capabilities.
  \param[in]   handle  iic handle to operate.
  \return      \ref iic_capabilities_t
*/
iic_capabilities_t csi_iic_get_capabilities(iic_handle_t handle);

/**
  \brief       config iic attributes.
  \param[in]   handle    iic handle to operate.
  \param[in]   mode      iic mode \ref iic_mode_e. if negative, then this attribute not changed.
  \param[in]   speed     iic speed \ref iic_speed_e. if negative, then this attribute not changed.
  \param[in]   addr_mode iic address mode \ref iic_address_mode_e. if negative, then this attribute not changed.
  \param[in]   slave_addr iic address of slave. if negative, then this attribute not changed.
  \return      0 for success, negative for error code
*/
int32_t csi_iic_config(iic_handle_t handle,
                       iic_mode_e mode,
                       iic_speed_e speed,
                       iic_address_mode_e addr_mode,
                       int32_t slave_addr);

/**
  \brief       Start transmitting data as I2C Master.
               This function is non-blocking,\ref iic_event_e is signaled when transfer completes or error happens.
               \ref csi_iic_get_status can indicates transmission status.
  \param[in]   handle         iic handle to operate.
  \param[in]   data           data to send to I2C Slave
  \param[in]   num            Number of data items to send
  \param[in]   xfer_pending   Transfer operation is pending - Stop condition will not be generated
  \return      0 for success, negative for error code
*/
int32_t csi_iic_master_send(iic_handle_t handle, const void *data, uint32_t num, bool xfer_pending);

/**
  \brief       Start receiving data as I2C Master.
               This function is non-blocking,\ref iic_event_e is signaled when transfer completes or error happens.
               \ref csi_iic_get_status can indicates transmission status.
  \param[in]   handle  iic handle to operate.
  \param[out]  data    Pointer to buffer for data to receive from IIC receiver
  \param[in]   num     Number of data items to receive
  \param[in]   xfer_pending   Transfer operation is pending - Stop condition will not be generated
  \return      0 for success, negative for error code
*/
int32_t csi_iic_master_receive(iic_handle_t handle, const void *data, uint32_t num, bool xfer_pending);

/**
  \brief       Start transmitting data as I2C Slave.
               This function is non-blocking,\ref iic_event_e is signaled when transfer completes or error happens.
               \ref csi_iic_get_status can indicates transmission status.
  \param[in]   handle  iic handle to operate.
  \param[in]   data  Pointer to buffer with data to transmit to I2C Master
  \param[in]   num   Number of data items to send
  \return      0 for success, negative for error code
*/
int32_t csi_iic_slave_send(iic_handle_t handle, const void *data, uint32_t num);

/**
  \brief       Start receiving data as I2C Slave.
               This function is non-blocking,\ref iic_event_e is signaled when transfer completes or error happens.
               \ref csi_iic_get_status can indicates transmission status.
  \param[in]   handle  iic handle to operate.
  \param[out]  data  Pointer to buffer for data to receive from I2C Master
  \param[in]   num   Number of data items to receive
  \return      0 for success, negative for error code
*/
int32_t csi_iic_slave_receive(iic_handle_t handle, const void *data, uint32_t num);

/**
  \brief       abort transfer.
  \param[in]   handle  iic handle to operate.
  \return      0 for success, negative for error code
*/
int32_t csi_iic_abort_transfer(iic_handle_t handle);

/**
  \brief       Get IIC status.
  \param[in]   handle  iic handle to operate.
  \return      IIC status \ref iic_status_t
*/
iic_status_t csi_iic_get_status(iic_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* _CSI_IIC_H_ */
