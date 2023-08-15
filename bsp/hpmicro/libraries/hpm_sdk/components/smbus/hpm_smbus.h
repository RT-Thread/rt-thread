/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SMBUS_H
#define HPM_SMBUS_H

#include "hpm_common.h"
#include "hpm_soc_feature.h"
#include "hpm_i2c_drv.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief SMbus master write data
 *
 * @details write data at slave mode
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address SMbus slave address
 * @param [in] data byte to be writed
 * @retval hpm_stat_t: status_success if writing is completed without any error
 */
hpm_stat_t hpm_smbus_master_write_byte(I2C_Type *ptr, uint8_t slave_address,
                                       uint8_t data);

/**
 * @brief SMbus master read byte from certain slave device
 *
 * @details Read byte from SMbus device
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address SMbus slave address
 * @param [out] data pointer of the byte read from device
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t hpm_smbus_master_read_byte(I2C_Type *ptr, uint8_t slave_address,
                                      uint8_t *data);

/**
 * @brief SMbus master write byte from certain slave device in command code
 *
 * @details write byte from SMbus device in command code
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address SMbus slave address
 * @param [in] command command code
 * @param [in] data byte to be writed
 * @retval hpm_stat_t: status_success if writing is completed without any error
 */
hpm_stat_t hpm_smbus_master_write_byte_in_command(I2C_Type *ptr, uint8_t slave_address,
                                                  uint8_t command, uint8_t data);

/**
 * @brief SMbus master write word(16bits) from certain slave device in command code
 *
 * @details write word(16bits) from SMbus device in command code
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address SMbus slave address
 * @param [in] command command code
 * @param [in] data word to be writed
 * @retval hpm_stat_t: status_success if writing is completed without any error
 */
hpm_stat_t hpm_smbus_master_write_word_in_command(I2C_Type *ptr, uint8_t slave_address,
                                                  uint8_t command,  uint16_t data);

/**
 * @brief SMbus master read byte from certain slave device in command code
 *
 * @details read byte from SMbus device in command code
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address SMbus slave address
 * @param [in] command command code
 * @param [in] data byte to be read
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t hpm_smbus_master_read_byte_in_command(I2C_Type *ptr, uint8_t slave_address,
                                                 uint8_t command, uint8_t *data);

/**
 * @brief SMbus master read word(16bits) from certain slave device in command code
 *
 * @details read word from SMbus device in command code
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address SMbus slave address
 * @param [in] command command code
 * @param [in] data word to be read
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t hpm_smbus_master_read_word_in_command(I2C_Type *ptr, uint8_t slave_address,
                                                 uint8_t command, uint16_t *data);

/**
 * @brief SMbus master block write from certain slave device in command code
 *
 * @details block write from SMbus device in command code
 * @note size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address SMbus slave address
 * @param [in] command command code
 * @param [in] data pointer of the buffer to store data read from device
 * @param [in] size size of data to be read in bytes
 * @retval hpm_stat_t: status_success if writing is completed without any error
 */
hpm_stat_t hpm_smbus_master_write_block_in_command(I2C_Type *ptr, uint8_t slave_address,
                                                   uint8_t command, uint8_t *data, uint32_t size);

/**
 * @brief SMbus master block read from certain slave device in command code
 *
 * @details block read from SMbus device in command code
 * @note size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address SMbus slave address
 * @param [in] command command code
 * @param [out] data pointer of the buffer to store data read from device
 * @param [in] size size of data to be read in bytes
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t hpm_smbus_master_read_block_in_command(I2C_Type *ptr, uint8_t slave_address,
                                                  uint8_t command, uint8_t *data, uint32_t size);

/**
 * @brief SMbus master write data to certain slave device
 *
 * @details Write data to SMbus device
 * @note size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address SMbus slave address
 * @param [in] data pointer of the data to be sent
 * @param [in] size size of data to be sent in bytes
 * @retval hpm_stat_t: status_success if writing is completed without any error
 */
hpm_stat_t hpm_smbus_master_write(I2C_Type *ptr, uint8_t slave_address,
                                  uint8_t *data, uint32_t size);

/**
 * @brief SMbus master read data from certain slave device
 *
 * @details Read data from SMbus device
 * @note size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] ptr I2C base address
 * @param [in] device_address SMbus slave address
 * @param [out] data pointer of the buffer to store data read from device
 * @param [in] size size of data to be read in bytes
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t hpm_smbus_master_read(I2C_Type *ptr, uint8_t slave_address,
                                 uint8_t *data, uint32_t size);

/**
 * @brief SMbus slave write data
 *
 * @details Write data at SMbus slave mode.
 * @note size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] ptr I2C base address
 * @param [in] buf pointer of the buffer to store data sent from device
 * @param [in] size size of data to be sent in bytes
 * @retval hpm_stat_t status_success if writing is completed without any error
 */
hpm_stat_t hpm_smbus_slave_write(I2C_Type *ptr, uint8_t *data, uint32_t size);

/**
 * @brief SMbus slave read data
 *
 * @details Read data at SMbus slave mode
 * @note size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in] ptr I2C base address
 * @param [in] buf pointer of the buffer to store data read from device
 * @param [in] size size of data to be read in bytes
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t hpm_smbus_slave_read(I2C_Type *ptr, uint8_t *data, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif


