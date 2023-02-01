/*
 * Copyright 2020 GreenWaves Technologies
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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef HAL_INCLUDE_HAL_UART_INTERNAL_H_
#define HAL_INCLUDE_HAL_UART_INTERNAL_H_

#include "hal_uart_pi.h"
#include "core-v-mcu-pmsis.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define UART_TX_BUFFER_SIZE     16
#define UART_DEFAULT_PRE_ALLOC_EVT 5

#define NB_UART 1

#ifndef UART_DRIVER_DATA_IMPLEM_SPECIFC
    #define UART_DRIVER_DATA_IMPLEM_SPECIFC
#endif

/*
 * pi_task:
 * data[0] = l2_buf
 * data[1] = size
 * data[2] = channel
 * data[3] = repeat_size
 * data[4] = device_id (used for delegation)
 */
struct uart_itf_data_s
{
    struct pi_task *fifo_head[2]; /*!< 0 = RX | 1 = TX. */
    struct pi_task *fifo_tail[2]; /*!< 0 = RX | 1 = TX. */
    uint32_t nb_open;             /*!< Number of times device has been opened. */
    uint32_t device_id;           /*!< Device ID. */
    UART_DRIVER_DATA_IMPLEM_SPECIFC
};

/*******************************************************************************
 * Driver data
 *****************************************************************************/

/*******************************************************************************
 * Function declaration
 ******************************************************************************/

/**
 * \brief Initialize conf struct.
 *
 * This function initializes a config struct with default values.
 *
 * \param conf           Pointer to struct pi_uart_conf.
 */
void __pi_uart_conf_init(struct pi_uart_conf *conf);

/**
 * \brief Open a device.
 *
 * This function opens a device.
 * A conf struct and a pointer to store UART driver info should be given.
 *
 * \para driver_data     Pointer to store driver info.
 * \param conf           Pointer to struct pi_uart_conf.
 *
 * \retval 0            If operation is successfull.
 * \retval ERRNO        An error code otherwise.
 */
int32_t __pi_uart_open(struct uart_itf_data_s **driver_data,
                       struct pi_uart_conf *conf);

/**
 * \brief Close a device.
 *
 * This function closes an opened device.
 *
 * \param driver_data    Pointer to driver info.
 */
void __pi_uart_close(struct uart_itf_data_s *driver_data);

/**
 * \brief Ioctl commands.
 *
 * This function allows to configure a device using ioctl commands.
 *
 * \param driver_data    Pointer to driver info.
 * \param cmd            Ioctl command.
 * \param arg            Ioctl command arg.
 *
 * \retval -1            If wrong ioctl command.
 * \retval Value         Value depending on ioctl command.
 */
int32_t __pi_uart_ioctl(struct uart_itf_data_s *driver_data, uint32_t cmd,
                        void *arg);

/**
 * \brief Transfer data.
 *
 * This function allows to send/receive data using the periph.
 * The transfer is executed immediately if there is no current transfer or no
 * pending transfer. Otherwise, the transfer is enqueued in a fifo.
 *
 * \param driver_data    Pointer to driver info.
 * \param l2_buf         Address of data buffer.
 * \param size           Size of data buffer.
 * \param channel        Direction of transfer.
 * \param task           Event task used to notify end of transfer.
 *
 * \retval 0             If operation is successfull.
 * \retval -1            Otherwise.
 */
int32_t __pi_uart_copy(struct uart_itf_data_s *driver_data, uint32_t l2_buf,
                       uint32_t size, udma_channel_e channel,
                       struct pi_task *task);

/**
 * \brief Transfer data.
 *
 * This function allows to send data using the periph.
 * The transfer is executed immediately if there is no current transfer or no
 * pending transfer. Otherwise, the transfer is enqueued in a fifo.
 *
 * \param driver_data    Pointer to driver info.
 * \param buffer         Pointer to data buffer.
 * \param size           Size of data buffer.
 * \param task           Event task used to notify end of transfer.
 *
 * \retval 0             If operation is successfull.
 * \retval -1            Otherwise.
 */
static inline int __pi_uart_write(struct uart_itf_data_s *data, void *buffer,
                                  uint32_t size, pi_task_t *callback)
{
    return __pi_uart_copy(data, (uint32_t) buffer, size, TX_CHANNEL, callback);
}

/**
 * \brief Transfer data.
 *
 * This function allows to receive data using the periph.
 * The transfer is executed immediately if there is no current transfer or no
 * pending transfer. Otherwise, the transfer is enqueued in a fifo.
 *
 * \param driver_data    Pointer to driver info.
 * \param buffer         Pointer to data buffer.
 * \param size           Size of data buffer.
 * \param task           Event task used to notify end of transfer.
 *
 * \retval 0             If operation is successfull.
 * \retval -1            Otherwise.
 */
static inline int __pi_uart_read(struct uart_itf_data_s *data, void *buffer,
                                 uint32_t size, pi_task_t *callback)
{
   return  __pi_uart_copy(data, (uint32_t) buffer, size, RX_CHANNEL, callback);
}



#endif /* HAL_INCLUDE_HAL_UART_INTERNAL_H_ */
