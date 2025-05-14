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
 * @file     iic.h
 * @brief    header file for iic driver
 * @version  V1.0
 * @date     08. Apr 2020
 * @model    iic
 ******************************************************************************/

#ifndef _DRV_IIC_H_
#define _DRV_IIC_H_

#include <stdint.h>
#include <stdbool.h>
#include <drv/common.h>
#include <drv/dma.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  \enum        csi_iic_mode_t
  \brief       iic work in master/slave mode
 */
typedef enum {
    IIC_MODE_MASTER               = 0U,     ///< IIC master
    IIC_MODE_SLAVE                          ///< IIC slave
} csi_iic_mode_t;

/**
  \enum        csi_iic_speed_t
  \brief       iic speed mode
 */
typedef enum {
    IIC_BUS_SPEED_STANDARD        = 0U,     ///< Standard Speed  (<=100kHz)
    IIC_BUS_SPEED_FAST,                     ///< Fast Speed      (<=400kHz)
    IIC_BUS_SPEED_FAST_PLUS,                ///< Fast plus Speed (<=  1MHz)
    IIC_BUS_SPEED_HIGH                      ///< High Speed      (<=3.4MHz)
} csi_iic_speed_t;

/**
  \enum        csi_iic_address_mode_t
  \brief       iic address mode
 */
typedef enum {
    IIC_ADDRESS_7BIT               = 0U,    ///< 7-bit address mode
    IIC_ADDRESS_10BIT                       ///< 10-bit address mode
} csi_iic_addr_mode_t;

/**
  \enum        csi_iic_mem_addr_size_t
  \brief       iic memory address size
 */
typedef enum {
    IIC_MEM_ADDR_SIZE_8BIT         = 0U,    ///< IIC e2prom  8bit address mode
    IIC_MEM_ADDR_SIZE_16BIT                 ///< IIC e2prom  16bit address mode
} csi_iic_mem_addr_size_t;

/**
  \enum        csi_iic_event_t
  \brief       iic event signaled by iic driver
 */
typedef enum {
    IIC_EVENT_SEND_COMPLETE        = 0U,     ///< Master/slave Send finished
    IIC_EVENT_RECEIVE_COMPLETE,              ///< Master/slave Receive finished
    IIC_EVENT_ERROR_OVERFLOW,                ///< Master/slave fifo overflow error
    IIC_EVENT_ERROR_UNDERFLOW,               ///< Master/slave fifo underflow error
    IIC_EVENT_ERROR                          ///< The receive buffer was completely filled to FIFO and more data arrived. That data is lost
} csi_iic_event_t;

/**
  \struct      csi_iic_t
  \brief       iic ctrl block
 */
typedef struct csi_iic csi_iic_t;
struct csi_iic {
    csi_dev_t                         dev;               ///< IIC hw-device info
    void (*callback)(csi_iic_t *iic, csi_iic_event_t event, void *arg); ///< IIC event callback for user
    void                              *arg;              ///< User private param passed to user callback
    uint8_t                           *data;             ///< IIC transfer-data buffer
    uint32_t                          size;              ///< IIC transfer-data size
    csi_iic_mode_t                    mode;              ///< IIC mode
    csi_dma_ch_t                      *tx_dma;           ///< Send dma channel handle
    csi_dma_ch_t                      *rx_dma;           ///< Receive dma channel handle
    void                              *send;             ///< Send function pointer asynchronously
    void                              *receive;          ///< Receive function pointer asynchronously
    csi_state_t                       state;             ///< IIC current state
    void                              *priv;
};

typedef void (*csi_iic_master_send_async_t)(csi_iic_t *iic, uint32_t devaddr, const void *data, uint32_t size);
typedef void (*csi_iic_master_receive_async_t)(csi_iic_t *iic, uint32_t devaddr, void *data, uint32_t size);
typedef void (*csi_iic_slave_send_async_t)(csi_iic_t *iic, const void *data, uint32_t size);
typedef void (*csi_iic_slave_receive_async_t)(csi_iic_t *iic, void *data, uint32_t size);

/**
  \brief       Init iic ctrl block
               Initializes the resources needed for the iic instance
  \param[in]   iic    Handle of iic instance
  \param[in]   idx    Index of instance
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_init(csi_iic_t *iic, uint32_t idx);

/**
  \brief       Uninit iic ctrl block
               Stops operation and releases the software resources used by the instance
  \param[in]   iic    Handle of iic instance
  \return      None
*/
void csi_iic_uninit(csi_iic_t *iic);

/**
  \brief       Config iic master or slave mode
  \param[in]   iic     Handle of iic instance
  \param[in]   mode    iic mode \ref csi_iic_mode_t
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_mode(csi_iic_t *iic, csi_iic_mode_t mode);

/**
  \brief       Config iic addr mode
  \param[in]   iic          Handle of iic instance
  \param[in]   addr_mode    iic addr mode \ref csi_iic_addr_mode_t
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_addr_mode(csi_iic_t *iic, csi_iic_addr_mode_t addr_mode);

/**
  \brief       Config iic speed
  \param[in]   iic      Handle of iic instance
  \param[in]   speed    iic speed mode \ref csi_iic_speed_t
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_speed(csi_iic_t *iic, csi_iic_speed_t speed);

/**
  \brief       Config iic own addr
  \param[in]   iic         Handle of iic instance
  \param[in]   own_addr    iic set own addr at slave mode
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_own_addr(csi_iic_t *iic, uint32_t own_addr);

/**
  \brief       Start sending data as iic master
               This function is blocking
  \param[in]   iic       Handle of iic instance
  \param[in]   devaddr   Addrress of slave device
  \param[in]   data      Pointer to send data buffer
  \param[in]   size      Size of data items to send
  \param[in]   timout    Unit of time delay(ms)
  \return      The amount of real data sent or error code
*/
int32_t csi_iic_master_send(csi_iic_t *iic, uint32_t devaddr, const void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Start receiving data as iic master
               This function is blocking
  \param[in]   iic        Handle to operate
  \param[in]   devaddr    iic addrress of slave device
  \param[out]  data       Pointer to buffer for data to receive from iic receiver
  \param[in]   size       Size of data items to receive
  \param[in]   timeout    Unit of time delay(ms)
  \return      The amount of real data received or error code
*/
int32_t csi_iic_master_receive(csi_iic_t *iic, uint32_t devaddr, void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Start sending data as iic master
               This function is non-blocking,\ref csi_iic_event_t is signaled when transfer completes or error happens
  \param[in]   iic     Handle to operate
  \param[in]   devaddr iic addrress of slave device
  \param[in]   data    Pointer to send data buffer
  \param[in]   size    Size of data items to send
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_master_send_async(csi_iic_t *iic, uint32_t devaddr, const void *data, uint32_t size);

/**
  \brief       Start receiving data as iic master.
               This function is non-blocking.\ref csi_iic_event_t is signaled when transfer completes or error happens
  \param[in]   iic     Handle to operate
  \param[in]   devaddr iic addrress of slave device
  \param[out]  data    Pointer to buffer for data to receive from iic receiver
  \param[in]   size    Size of data items to receive
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_master_receive_async(csi_iic_t *iic, uint32_t devaddr, void *data, uint32_t size);

/**
  \brief       Start sending data as iic master
               This function is blocking
  \param[in]   iic             Handle of iic instance
  \param[in]   devaddr         Addrress of slave device
  \param[in]   memaddr         Internal addr of device
  \param[in]   memaddr_size    Internal addr mode of device
  \param[in]   data            Pointer to send data buffer
  \param[in]   size            Size of data items to send
  \param[in]   timout          Unit of time delay(ms)
  \return      The amount of real data sent or error code
*/
int32_t csi_iic_mem_send(csi_iic_t *iic, uint32_t devaddr, uint16_t memaddr, csi_iic_mem_addr_size_t memaddr_size, const void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Start receiving data as iic master
               This function is blocking
  \param[in]   iic             Handle to operate
  \param[in]   devaddr         iic addrress of slave device
  \param[in]   memaddr         Internal addr of device
  \param[in]   memaddr_mode    Internal addr mode of device
  \param[out]  data            Pointer to buffer for data to receive from eeprom device
  \param[in]   size            Size of data items to receive
  \param[in]   timeout         Unit of time delay(ms)
  \return      The amount of real data received or error code
*/
int32_t csi_iic_mem_receive(csi_iic_t *iic, uint32_t devaddr, uint16_t memaddr, csi_iic_mem_addr_size_t memaddr_size, void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Start sending data as iic slave
               This function is blocking
  \param[in]   iic        Handle to operate
  \param[in]   data       Pointer to buffer with data to send to iic master
  \param[in]   size       Size of data items to send
  \param[in]   timeout    Unit of time delay(ms)
  \return      The amount of real data sent or error code
*/
int32_t csi_iic_slave_send(csi_iic_t *iic, const void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Start receiving data as iic slave
               This function is blocking
  \param[in]   iic        Handle to operate
  \param[out]  data       Pointer to buffer for data to receive from iic master
  \param[in]   size       Size of data items to receive
  \param[in]   timeout    Unit of time delay(ms)
  \return      The amount of real data received or error code
*/
int32_t csi_iic_slave_receive(csi_iic_t *iic, void *data, uint32_t size, uint32_t timeout);

/**
  \brief       Start sending data as iic slave
               This function is non-blocking,\ref csi_iic_event_t is signaled when transfer completes or error happens
  \param[in]   iic     Handle to operate
  \param[in]   data    Pointer to buffer with data to send to iic master
  \param[in]   size    Size of data items to send
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_slave_send_async(csi_iic_t *iic, const void *data, uint32_t size);

/**
  \brief       Start receiving data as iic slave
               This function is non-blocking,\ref csi_iic_event_t is signaled when transfer completes or error happens
  \param[in]   handle  iic handle to operate
  \param[out]  data    Pointer to buffer for data to receive from iic master
  \param[in]   size    Size of data items to receive
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_slave_receive_async(csi_iic_t *iic, void *data, uint32_t size);

/**
  \brief       Attach callback to the iic
  \param[in]   iic    iic handle to operate
  \param[in]   cb     Event callback function \ref csi_iic_callback_t
  \param[in]   arg    User private param for event callback
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_attach_callback(csi_iic_t *iic, void *callback, void *arg);

/**
  \brief       Detach callback from the iic
  \param[in]   iic    iic handle to operate
  \return      None
*/
void csi_iic_detach_callback(csi_iic_t *iic);

/**
  \brief       Config iic stop to generate
  \param[in]   iic       iic handle to operate
  \param[in]   enable    Transfer operation is pending - stop condition will not be generated
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_xfer_pending(csi_iic_t *iic, bool enable);

/**
  \brief       Link DMA channel to iic device
  \param[in]   iic       Handle to operate
  \param[in]   tx_dma    The DMA channel handle for send, when it is NULL means to unlink the channel
  \param[in]   rx_dma    The DMA channel handle for receive, when it is NULL means to unlink the channel
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_link_dma(csi_iic_t *iic, csi_dma_ch_t *tx_dma, csi_dma_ch_t *rx_dma);

/**
  \brief       Get iic state
  \param[in]   iic      Handle to operate
  \param[out]  state    iic state \ref csi_state_t
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_get_state(csi_iic_t *iic, csi_state_t *state);

/**
  \brief       Enable iic power manage
  \param[in]   iic    iic handle to operate
  \return      error code \ref csi_error_t
*/
csi_error_t csi_iic_enable_pm(csi_iic_t *iic);

/**
  \brief       Disable iic power manage
  \param[in]   iic    iic handle to operate
  \return      None
*/
void csi_iic_disable_pm(csi_iic_t *iic);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_IIC_H_ */
