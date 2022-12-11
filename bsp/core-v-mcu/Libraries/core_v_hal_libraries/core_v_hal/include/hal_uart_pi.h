/*
 * Copyright (C) 2018 GreenWaves Technologies
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

#ifndef __PMSIS_DRIVERS_UART_H__
#define __PMSIS_DRIVERS_UART_H__

//#include "pmsis/pmsis_types.h"
#include "hal_pmsis_types.h"

/**
 * @ingroup groupDrivers
 */

/**
 * @defgroup UART UART
 *
 * \brief UART Universal Asynchronous Receiver Transmitter
 *
 * This API provides support for transferring data between an external UART
 * device and the processor running this driver.
 *
 */

/**
 * @addtogroup UART
 * @{
 */

/**
 * \struct pi_uart_conf
 *
 * \brief UART device configuration structure.
 *
 * This structure is used to pass the desired UART configuration to the runtime
 * when opening the device.
 */
struct pi_uart_conf
{
    uint32_t baudrate_bps;  /*!< Required baudrate, in baud per second. */
    uint8_t stop_bit_count; /*!< Number of stop bits, 1 stop bit (default) or
                              2 stop bits  */
    uint8_t parity_mode;    /*!< 1 to activate it, 0 to deactivate it. */
    uint8_t word_size;      /*!< Word size, in bits. */
    uint8_t enable_rx;      /*!< 1 to activate reception, 0 to deactivate it. */
    uint8_t enable_tx;      /*!< 1 to activate transmission, 0 to deactivate it. */
    uint8_t uart_id;        /*!< Uart interface ID. */
    uint8_t use_ctrl_flow;  /*!< 1 to activate control flow. */
    uint8_t is_usart;       /*!< 1 to activate usart */
};

/**
 * \enum pi_uart_stop_bits
 *
 * \brief Stop bits enum.
 */
enum pi_uart_stop_bits
{
    PI_UART_STOP_BITS_ONE = 0,  /*!< One stop bit. */
    PI_UART_STOP_BITS_TWO = 1   /*!< Two stop bits. */
};

/**
 * \enum pi_uart_parity_mode
 *
 * \brief Parity mode enum.
 */
enum pi_uart_parity_mode
{
    PI_UART_PARITY_DISABLE = 0, /*!< Disable parity mode. */
    PI_UART_PARITY_ENABLE  = 1  /*!< Enable parity mode. */
};

/**
 * \enum pi_uart_word_size
 *
 * \brief Bit length of each word.
 */
enum pi_uart_word_size
{
    PI_UART_WORD_SIZE_5_BITS = 0, /*!< 5 bits length. */
    PI_UART_WORD_SIZE_6_BITS = 1, /*!< 6 bits length. */
    PI_UART_WORD_SIZE_7_BITS = 2, /*!< 7 bits length. */
    PI_UART_WORD_SIZE_8_BITS = 3  /*!< 8 bits length. */
};


/**
 * \enum pi_uart_ioctl_cmd
 *
 * \brief UART ioctl commands.
 *
 * UART ioctl commands to configure, enable device.
 */
enum pi_uart_ioctl_cmd
{
    /**
     * \brief Setup UART device.
     *
     * Setup UART with given conf.
     * The parameter for this command is a struct pi_uart_conf.
     *
     * \param conf       Pointer to struct pi_uart_conf.
     */
    PI_UART_IOCTL_CONF_SETUP = 0,
    /**
     * \brief Abort RX transfers.
     *
     * Disable RX channel, abort current RX transfert,
     * and flush all pending transferts.
     *
     * \note This function disables reception channel after clearing UDMA
     *       channels. In order to send again data, the reception channel
     *       must re-enabled.
     */
    PI_UART_IOCTL_ABORT_RX   = 1,
    /**
     * \brief Abort TX transfers.
     *
     * Disable TX channel, abort current TX transfert,
     * and flush all pending transferts.
     *
     * \note This function disables transmission channel after clearing UDMA
     *       channels. In order to send again data, the transmission channel
     *       must re-enabled.
     */
    PI_UART_IOCTL_ABORT_TX   = 2,
    /**
     * \brief Enable reception.
     *
     * This command enables reception on UART device.
     */
    PI_UART_IOCTL_ENABLE_RX  = 3,
    /**
     * \brief Enable transmission.
     *
     * This command enables transmission on UART device.
     */
    PI_UART_IOCTL_ENABLE_TX  = 4
};

/**
 * \brief UART cluster request structure.
 *
 * This structure is used by the runtime to manage a cluster remote copy with
 * the UART. It must be instantiated once for each copy and must be kept
 * alive until the copy is finished. It can be instantiated as a normal
 * variable, for example as a global variable, a local one on the stack,
 * or through a memory allocator.
 */
typedef struct pi_cl_uart_req_s pi_cl_uart_req_t;

/**
 * \brief Initialize a UART configuration with default values.
 *
 * This function can be called to get default values for all parameters before
 * setting some of them.
 * The structure containing the configuration must be kept alive until the uart
 * device is opened.
 *
 * \param conf           Pointer to the UART configuration.
 */
void pi_uart_conf_init(struct pi_uart_conf *conf);

/**
 * \brief Open a UART device.
 *
 * This function must be called before the UART device can be used.
 * It will do all the needed configuration to make it usable and initialize
 * the handle used to refer to this opened device when calling other functions.
 *
 * \param device         Pointer to device structure of the device to open.
 *
 * \retval 0             If the operation is successfull.
 * \retval ERRNO         An error code otherwise.
 *
 * \note This structure is allocated by the called and must be kept alive until the
 *       device is closed.
 */
int pi_uart_open(struct pi_device *device);

/**
 * \brief Close an opened UART device.
 *
 * This function can be called to close an opened UART device once it is
 * not needed anymore, in order to free all allocated resources. Once this
 * function is called, the device is not accessible anymore and must be opened
 * again before being used.
 *
 * \param device         Pointer to device structure of the device to close.
 */
void pi_uart_close(struct pi_device *device);

/**
 * \brief Dynamically change device configuration.
 *
 * This function allows to send different commands to UART device.
 * The commands are listed above, cf. enum pi_uart_ioctl_cmd.
 *
 * \param device         Pointer to device descriptor of the UART device.
 * \param cmd            Ioctl command.
 * \param arg            Ioctl command args.
 *
 * \retval -1            If wrong ioctl command.
 * \retval Value         Otherwise return value depending on ioctl command.
 */
int pi_uart_ioctl(struct pi_device *device, uint32_t cmd, void *arg);

/**
 * \brief Write data to an UART.
 *
 * This writes data to the specified UART.
 * The caller is blocked until the transfer is finished.
 * Depending on the chip, there may be some restrictions on the memory which
 * can be used. Check the chip-specific documentation for more details.
 *
 * \param device         Pointer to device descriptor of the UART device.
 * \param buffer         Pointer to data buffer.
 * \param size           Size of data to copy in bytes.
 *
 * \retval 0             If operation is successfull.
 * \retval ERRNO         An error code otherwise.
 */
int pi_uart_write(struct pi_device *device, void *buffer, uint32_t size);

/**
 * \brief Read data from an UART.
 *
 * This reads data from the specified UART.
 * The caller is blocked until the transfer is finished.
 * Depending on the chip, there may be some restrictions on the memory which
 * can be used. Check the chip-specific documentation for more details.
 *
 * \param device         Pointer to device descriptor of the UART device.
 * \param buffer         Pointer to data buffer.
 * \param size           Size of data to copy in bytes.
 *
 * \retval 0             If operation is successfull.
 * \retval ERRNO         An error code otherwise.
 */
int pi_uart_read(struct pi_device *device, void *buffer, uint32_t size);

/**
 * \brief Write a byte to an UART.
 *
 * This writes a byte to the specified UART.
 * The caller is blocked until the transfer is finished.
 *
 * \param device         Pointer to device descriptor of the UART device.
 * \param byte         Pointer to data buffer.
 *
 * \retval 0             If operation is successfull.
 * \retval ERRNO         An error code otherwise.
 */
int pi_uart_write_byte(struct pi_device *device, uint8_t *byte);

/**
 * \brief Read a byte from an UART.
 *
 * This reads a byte from the specified UART.
 * The caller is blocked until the transfer is finished.
 *
 * \param device         Pointer to device descriptor of the UART device.
 * \param byte           Pointer to data buffer.
 *
 * \retval 0             If operation is successfull.
 * \retval ERRNO         An error code otherwise.
 */
int pi_uart_read_byte(struct pi_device *device, uint8_t *byte);

/**
 * \brief Write data to an UART asynchronously.
 *
 * This writes data to the specified UART asynchronously.
 * A task must be specified in order to specify how the caller should be
 * notified when the transfer is finished.
 * Depending on the chip, there may be some restrictions on the memory which
 * can be used. Check the chip-specific documentation for more details.
 *
 * \param device         Pointer to device descriptor of the UART device.
 * \param buffer         Pointer to data buffer.
 * \param size           Size of data to copy in bytes.
 * \param callback       Event task used to notify the end of transfer. See the
 *                       documentation of pi_task_t for more details.
 *
 * \retval 0             If operation is successfull.
 * \retval ERRNO         An error code otherwise.
 */
int pi_uart_write_async(struct pi_device *device, void *buffer, uint32_t size,
                        pi_task_t* callback);

/**
 * \brief Read data from an UART asynchronously.
 *
 * This reads data from the specified UART asynchronously.
 * A task must be specified in order to specify how the caller should be
 * notified when the transfer is finished.
 * Depending on the chip, there may be some restrictions on the memory which
 * can be used. Check the chip-specific documentation for more details.
 *
 * \param device         Pointer to device descriptor of the UART device.
 * \param buffer         Pointer to data buffer.
 * \param size           Size of data to copy in bytes.
 * \param callback       Event task used to notify the end of transfer. See the
 *                       documentation of pi_task_t for more details.
 *
 * \retval 0             If operation is successfull.
 * \retval ERRNO         An error code otherwise.
 */
int pi_uart_read_async(struct pi_device *device, void *buffer, uint32_t size,
                       pi_task_t* callback);

/**
 * \brief Write a byte to an UART asynchronously.
 *
 * This writes a byte to the specified UART asynchronously.
 * A task must be specified in order to specify how the caller should be
 * notified when the transfer is finished.
 *
 * \param device         Pointer to device descriptor of the UART device.
 * \param byte           Pointer to data buffer.
 * \param callback       Event task used to notify the end of transfer. See the
 *                       documentation of pi_task_t for more details.
 *
 * \retval 0             If operation is successfull.
 * \retval ERRNO         An error code otherwise.
 */
int pi_uart_write_byte_async(struct pi_device *device, uint8_t *byte, pi_task_t* callback);


/**
 * \brief Write data to an UART from cluster side.
 *
 * This function implements the same feature as pi_uart_write but can be called
 * from cluster side in order to expose the feature on the cluster.
 * A pointer to a request structure must be provided so that the runtime can
 * properly do the remote call.
 *
 * \param device         Pointer to device descriptor of the UART device.
 * \param buffer         Pointer to data buffer.
 * \param size           Size of data to copy in bytes.
 * \param req            Request structure used for termination.
 *
 * \retval 0             If operation is successfull.
 * \retval ERRNO         An error code otherwise.
 */
int pi_cl_uart_write(pi_device_t *device, void *buffer, uint32_t size, pi_cl_uart_req_t *req);

/**
 * \brief Write a byte to an UART from cluster side.
 *
 * This function implements the same feature as pi_uart_write_byte but can be
 * called from cluster side in order to expose the feature on the cluster.
 * A pointer to a request structure must be provided so that the runtime can
 * properly do the remote call.
 *
 * \param device         Pointer to device descriptor of the UART device.
 * \param byte           Pointer to data buffer.
 * \param req            Request structure used for termination.
 *
 * \retval 0             If operation is successfull.
 * \retval ERRNO         An error code otherwise.
 */
int pi_cl_uart_write_byte(pi_device_t *device, uint8_t *byte, pi_cl_uart_req_t *req);

/**
 * \brief Wait until the specified UART cluster write request has finished.
 *
 * This blocks the calling core until the specified cluster remote copy is
 * finished.
 *
 * \param req            Request structure used for termination.
 */
//static inline void pi_cl_uart_write_wait(pi_cl_uart_req_t *req);

/**
 * \brief Read a byte from an UART from cluster side.
 *
 * This function implements the same feature as pi_uart_read_byte but can be
 * called from cluster side in order to expose the feature on the cluster.
 * A pointer to a request structure must be provided so that the runtime can
 * properly do the remote call.
 *
 * \param device         Pointer to device descriptor of the UART device.
 * \param buffer         Pointer to data buffer.
 * \param size           Size of data to copy in bytes.
 * \param req            Request structure used for termination.
 *
 * \retval 0             If operation is successfull.
 * \retval ERRNO         An error code otherwise.
 */
int pi_cl_uart_read(pi_device_t *device, void *buffer, uint32_t size, pi_cl_uart_req_t *req);

/**
 * \brief Read a byte from an UART.
 *
 * This reads a byte from the specified UART.
 * The caller is blocked until the transfer is finished.
 *
 * \param device         Pointer to device descriptor of the UART device.
 * \param byte           Pointer to data buffer.
 * \param req            Request structure used for termination.
 *
 * \retval 0             If operation is successfull.
 * \retval ERRNO         An error code otherwise.
 */
int pi_cl_uart_read_byte(pi_device_t *device, uint8_t *byte, pi_cl_uart_req_t *req);

/**
 * \brief Wait until the specified UART cluster read request has finished.
 *
 * This blocks the calling core until the specified cluster remote copy is
 * finished.
 *
 * \param req            Request structure used for termination.
 */
//static inline void pi_cl_uart_read_wait(pi_cl_uart_req_t *req);

/**
 * @}
 */

#endif  /* __PMSIS_DRIVERS_UART_H__ */
