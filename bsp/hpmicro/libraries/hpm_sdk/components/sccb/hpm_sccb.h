/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SCCB_H
#define HPM_SCCB_H

#include "hpm_common.h"
#include "hpm_soc_feature.h"
#include "hpm_i2c_drv.h"

typedef I2C_Type *sccb_type;

typedef enum _sccb_xfer_flag {
    /*Normal transfer with start condition, address, data and stop condition.*/
    sccb_xfer_no_flags,
    /*This flag allows the next transfer to change direction with repeated start*/
    sccb_xfer_no_stop,
    /*This flag allows chaining multiple writes or reads with the same direction*/
    sccb_xfer_suspend,
} sccb_xfer_flags_t;

typedef struct _sccb_bus {
    uint8_t initialzed;
    sccb_type sccb;
} hpm_sccb_bus_t;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief sccb master initialization
 *
 * @details Initialized sccb working at master mode
 *
 * @param [in] sccb sccb base address
 * @retval hpm_stat_t: status_success if initialization is completed without any error
 */
hpm_stat_t sccb_master_init(sccb_type sccb);

/**
 * @brief sccb master scan slave addr
 *
 * @details master scan the slave
 *
 * @param [in] sccb sccb base address
 * @retval uint8_t: the slave address val is zero if scan slave fail
 */
uint8_t sccb_master_scan(sccb_type sccb);

/**
 * @brief sccb master gen call slave
 *
 * @details the controller sends the command to determine whether the slave responds
 *
 * @param [in] sccb sccb base address
 * @param [in] cmd sccb master sends command
 * @retval hpm_stat_t: status_success if the slave responds
 */
hpm_stat_t sccb_master_gencall(sccb_type sccb, uint8_t cmd);

/**
 * @brief sccb master read 8bit data of specify 8bit register from certain slave device
 *
 * @details the function used to access 8 bit register address,read 8bit data
 * @note the register address must be 8bit
 *
 * @param [in]  sccb sccb base address
 * @param [in]  slv_addr sccb slave address
 * @param [out] reg_addr 8bit register address of sccb slave device
 * @param [out] reg_data point of the buffer to store 8bit data from device  the number of bytes is 1
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t sccb_master_readb(sccb_type sccb, uint8_t slv_addr, uint8_t reg_addr, uint8_t *reg_data);

/**
 * @brief sccb master write 8bit data of specify 8bit register from certain slave device
 *
 * @details the function used to access 8 bit register address,write 8bit data
 * @note the register address must be 8bit
 *
 * @param [in]  sccb sccb base address
 * @param [in]  slv_addr sccb slave address
 * @param [out] reg_addr 8bit register address of sccb slave device
 * @param [out] reg_data write 8bit data
 * @retval hpm_stat_t: status_success if writing is completed without any error
 */
hpm_stat_t sccb_master_writeb(sccb_type sccb, uint8_t slv_addr, uint8_t reg_addr, uint8_t reg_data);

/**
 * @brief sccb master read 8bit data of specify 16bit register from certain slave device
 *
 * @details the function used to access 16 bit register address,read 8bit data
 * @note the register address must be 16bit
 *
 * @param [in]  sccb sccb base address
 * @param [in]  slv_addr sccb slave address
 * @param [out] reg_addr 16bit register address of sccb slave device
 * @param [out] reg_data point of the buffer to store 8bit data from device  the number of bytes is 1
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t sccb_master_readb2(sccb_type sccb, uint8_t slv_addr, uint16_t reg_addr, uint8_t *reg_data);

/**
 * @brief sccb master write 8bit data of specify 16bit register from certain slave device
 *
 * @details the function used to access 16 bit register address,write 8bit data
 * @note the register address must be 8bit
 *
 * @param [in]  sccb sccb base address
 * @param [in]  slv_addr sccb slave address
 * @param [out] reg_addr 16bit register address of sccb slave device
 * @param [out] reg_data wirite 8bit data
 * @retval hpm_stat_t: status_success if writing is completed without any error
 */
hpm_stat_t sccb_master_writeb2(sccb_type sccb, uint8_t slv_addr, uint16_t reg_addr, uint8_t reg_data);

/**
 * @brief sccb master read 16bit data of specify 8bit register from certain slave device
 *
 * @details the function used to access 8 bit register address,read 16bit data
 * @note the register address must be 8bit
 *
 * @param [in]  sccb sccb base address
 * @param [in]  slv_addr sccb slave address
 * @param [out] reg_addr 8bit register address of sccb slave device
 * @param [out] reg_data point of the buffer to store 16bit data from device  the number of bytes is 1
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t sccb_master_readw(sccb_type sccb, uint8_t slv_addr, uint8_t reg_addr, uint16_t *reg_data);

/**
 * @brief sccb master write 16bit data of specify 8bit register from certain slave device
 *
 * @details the function used to access 8 bit register address,write 16bit data
 * @note the register address must be 8bit
 *
 * @param [in]  sccb sccb base address
 * @param [in]  slv_addr sccb slave address
 * @param [out] reg_addr 8bit register address of sccb slave device
 * @param [out] reg_data wirite 16bit data
 * @retval hpm_stat_t: status_success if writing is completed without any error
 */
hpm_stat_t sccb_master_writew(sccb_type sccb, uint8_t slv_addr, uint8_t reg_addr, uint16_t reg_data);

/**
 * @brief sccb master read 16bit data of specify 16it register from certain slave device
 *
 * @details the function used to access 16 bit register address,read 16bit data
 * @note the register address must be 16bit
 *
 * @param [in]  sccb sccb base address
 * @param [in]  slv_addr sccb slave address
 * @param [out] reg_addr 16bit register address of sccb slave device
 * @param [out] reg_data point of the buffer to store 16bit data from device  the number of bytes is 1
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t sccb_master_readw2(sccb_type sccb, uint8_t slv_addr, uint16_t reg_addr, uint16_t *reg_data);

/**
 * @brief sccb master write 16bit data of specify 16bit register from certain slave device
 *
 * @details the function used to access 16bit register address,write 16bit data
 * @note the register address must be 16bit
 *
 * @param [in]  sccb sccb base address
 * @param [in]  slv_addr sccb slave address
 * @param [out] reg_addr 16bit register address of sccb slave device
 * @param [out] reg_data wirite 16bit data
 * @retval hpm_stat_t: status_success if writing is completed without any error
 */
hpm_stat_t sccb_master_writew2(sccb_type sccb, uint8_t slv_addr, uint16_t reg_addr, uint16_t reg_data);

/**
 * @brief sccb master reads the specified number of bytes continuously at the specified flag
 *
 * @details the size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in]  sccb sccb base address
 * @param [in]  slv_addr sccb slave address
 * @param [out] buf  point of the buffer to store 8bit data from device
 * @param [out] len  size of data to be read in bytes
 * @param [in] len  size of data to be read in bytes
 * @retval hpm_stat_t: status_success if reading is completed without any error
 */
hpm_stat_t sccb_master_read_bytes(sccb_type sccb, uint8_t slv_addr, uint8_t *buf, const uint32_t len, uint8_t flags);

/**
 * @brief sccb master weite the specified number of bytes continuously at the specified flag
 *
 * @details the size should not not greater than I2C_SOC_TRANSFER_COUNT_MAX
 *
 * @param [in]  sccb sccb base address
 * @param [in]  slv_addr sccb slave address
 * @param [out] buf  point of the buffer to store 8bit data from device
 * @param [out] len  size of data to be write in bytes
 * @param [in] len  size of data to be write in bytes
 * @retval hpm_stat_t: status_success if writing is completed without any error
 */
hpm_stat_t cambus_write_bytes(sccb_type sccb, uint8_t slv_addr, uint8_t *buf, const uint32_t len, uint8_t flags);

#ifdef __cplusplus
}
#endif

#endif
