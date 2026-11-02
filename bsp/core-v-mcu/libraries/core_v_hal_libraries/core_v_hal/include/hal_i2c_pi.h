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

#ifndef HAL_INCLUDE_HAL_I2C_PI_H_
#define HAL_INCLUDE_HAL_I2C_PI_H_

#include "hal_pmsis_types.h"

/**
* @ingroup groupDrivers
*/

/**
 * @defgroup I2C I2C
 *
 * The I2C driver provides support for transferring data between an external
 * I2C device and the chip running this driver.
 *
 */

/**
 * @addtogroup I2C
 * @{
 */

/**@{*/

/// @cond IMPLEM

#define __PI_I2C_CTRL_SET_MAX_BAUDRATE_BIT 0

/// @endcond

/** \struct pi_i2c_conf_t
 * \brief I2C master configuration structure.
 *
 * This structure is used to pass the desired I2C configuration to the runtime
 * when opening a device.
 */
typedef struct pi_i2c_conf
{
    pi_device_e device;  /* Device type. */
    uint8_t itf;            /*!< Specifies on which I2C interface the device is
      connected. */
    int8_t cs;               /*!< i2c slave address (7 bits on MSB), the
      runtime will take care of the LSB of read and write. */
    int8_t is_slave;
    uint16_t slave_addr;
    uint16_t gap_slave_addr0;
    uint16_t gap_slave_addr1;
    uint32_t max_baudrate;   /*!< Maximum baudrate for the I2C bitstream which
      can be used with the opened device . */
} pi_i2c_conf_t;


/** \enum pi_i2c_xfer_flags_e
 * \brief Properties for I2C transfers
 *
 * This is used to specify additional behaviors when transfering data through
 * I2C.
 */
typedef enum {
  PI_I2C_XFER_STOP     = 0<<0,   /*!< Generate a STOP bit at the end of the
    transfer. */
  PI_I2C_XFER_NO_STOP  = 1<<0,   /*!< Don't generate a STOP bit at the end of
    the transfer. */
  PI_I2C_XFER_START    = 0<<1,    /*!< Generate a START bit at the beginning of
    the transfer. */
  PI_I2C_XFER_NO_START = 1<<1    /*!< Don't generate a START bit at the
    beginning of the transfer. */
} pi_i2c_xfer_flags_e;

/** \enum pi_i2c_ioctl_e
 * \brief Commands for pi_i2c_control.
 *
 * This is used to tell which command to execute through pi_i2c_control.
 */
typedef enum {
  PI_I2C_CTRL_SET_MAX_BAUDRATE  = 1 << __PI_I2C_CTRL_SET_MAX_BAUDRATE_BIT, /*!<
    Change maximum baudrate. */
} pi_i2c_ioctl_e;

/** \brief Initialize an I2C configuration with default values.
 *
 * This function can be called to get default values for all parameters before
 * setting some of them. The structure containing the configuration must be
 * kept alive until the I2C device is opened.
 *
 * \param conf A pointer to the I2C configuration.
 */
void pi_i2c_conf_init(pi_i2c_conf_t *conf);

/** \brief Open an I2C device.
 *
 * This function must be called before the Hyperbus device can be used.
 * It will do all the needed configuration to make it usable and initialize
 * the handle used to refer to this opened device when calling other functions.
 *
 * \param device    A pointer to the device structure of the device to open.
 *   This structure is allocated by the called and must be kept alive until the
 *   device is closed.
 * \return          0 if the operation is successfull, -1 if there was an error.
 */
int pi_i2c_open(struct pi_device *device);

/** \brief Close an opened I2C device.
 *
 * This function can be called to close an opened I2C device once it is
 * not needed anymore, in order to free all allocated resources. Once this
 * function is called, the device is not accessible anymore and must be opened
 * again before being used.
 *
 * \param device    The device structure of the device to close.
 */
void pi_i2c_close (struct pi_device *device);

/** \brief Dynamically change the device configuration.
 *
 * This function can be called to change part of the device configuration after
 * it has been opened.
 *
 * \param device  A pointer to the structure describing the device.
 * \param cmd     The command which specifies which parameters of the driver to
 * modify and for some of them also their values. The command must be one of
 * those defined in pi_i2c_ioctl_e.
 * \param arg       An additional value which is required for some parameters
 * when they are set.
 */
void pi_i2c_ioctl(struct pi_device *device, uint32_t cmd, void *arg);

/** \brief Enqueue a burst read copy from the I2C (from I2C device to chip).
 *
 * This function can be used to read at least 1 byte of data from the I2C
 * device. The copy will make a synchronous transfer between the I2C and one of
 * the chip memory.
 * The caller is blocked until the transfer is finished.
 * Depending on the chip, there may be some restrictions on the memory which
 * can be used. Check the chip-specific documentation for more details.
 *
 * \param device  A pointer to the structure describing the device.
 * \param rx_buff The address in the chip where the received data must be
 *   written.
 * \param length  The size in bytes of the copy.
 * \param flags  Specify additional transfer behaviors like start and stop bits
 *   management.
 */
void pi_i2c_read(struct pi_device *device, uint8_t *rx_buff, int length,
  pi_i2c_xfer_flags_e flags);

/** \brief Enqueue a burst write copy to the I2C (from chip to I2C device).
 *
 * This function can be used to write at least 1 byte of data to the I2C device.
 * The copy will make a synchronous transfer between the I2C and one of the
 * chip memory.
 * The caller is blocked until the transfer is finished.
 * Depending on the chip, there may be some restrictions on the memory which
 * can be used. Check the chip-specific documentation for more details.
 *
 * \param device    A pointer to the structure describing the device.
 * \param tx_data     The address in the chip where the data to be sent is read.
 * \param length      The size in bytes of the copy.
 * \param flags  Specify additional transfer behaviors like start and stop bits
 *   management.
 */
void pi_i2c_write(struct pi_device *device, uint8_t *tx_data, int length,
  pi_i2c_xfer_flags_e flags);

/** \brief Enqueue an asynchronous burst read copy from the I2C (from I2C
 * device to chip).
 *
 * This function can be used to read at least 1 byte of data from the I2C
 * device.
 * The copy will make an asynchronous transfer between the I2C and one of the
 * chip memory.
 * A task must be specified in order to specify how the caller should be
 * notified when the transfer is finished.
 * Depending on the chip, there may be some restrictions on the memory which
 * can be used. Check the chip-specific documentation for more details.
 *
 * \param device  A pointer to the structure describing the device.
 * \param rx_buff  The address in the chip where the received data must be
 *   written.
 * \param length   The size in bytes of the copy.
 * \param flags  Specify additional transfer behaviors like start and stop
 *   bits management.
 * \param task        The task used to notify the end of transfer.
   See the documentation of pi_task_t for more details.
 */
void pi_i2c_read_async(struct pi_device *device, uint8_t *rx_buff, int length,
  pi_i2c_xfer_flags_e flags, pi_task_t *task);

/** \brief Enqueue a burst write copy to the I2C (from chip to I2C device).
 *
 * This function can be used to write at least 1 byte of data to the I2C device.
 * The copy will make an asynchronous transfer between the I2C and one of the
 * chip memory.
 * A task must be specified in order to specify how the caller should be
 * notified when the transfer is finished.
 * Depending on the chip, there may be some restrictions on the memory which
 * can be used. Check the chip-specific documentation for more details.
 *
 * \param device    A pointer to the structure describing the device.
 * \param tx_data   The address in the chip where the data to be sent is read.
 * \param length    The size in bytes of the copy
 * \param flags  Specify additional transfer behaviors like start and stop bits
 *   management.
 * \param task        The task used to notify the end of transfer.
   See the documentation of pi_task_t for more details.
 */
void pi_i2c_write_async(struct pi_device *device, uint8_t *tx_data, int length,
  pi_i2c_xfer_flags_e flags, pi_task_t *task);

//!@}

/**
 * @}
 */

#endif /* HAL_INCLUDE_HAL_I2C_PI_H_ */
