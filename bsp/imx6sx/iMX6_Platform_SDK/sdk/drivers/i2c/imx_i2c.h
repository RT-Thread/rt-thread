/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __IMX_I2C_H__
#define __IMX_I2C_H__

#include "sdk_types.h"

//! @addtogroup diag_i2c

//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Read/write address bits
//!
//! Bit 0 of the i2c device address cycle to indicate r/w. 0 is for write, 1 is for read.
enum _i2c_rq {
    I2C_WRITE = 0,
    I2C_READ = 1
};

//! @brief I2C Error Codes
enum _i2c_err {
    ERR_TX = -1,
    ERR_RX = -2,
    ERR_ARB_LOST = -3,
    ERR_NO_ACK = -4,
    ERR_XFER = -5,
    ERR_RX_ACK = -6,
    ERR_NO_ACK_ON_START = -7,
    ERR_INVALID_REQUEST = -8
};

//! Default slave address used for the MX6.
enum _i2c_slave_id {
    IMX6_DEFAULT_SLAVE_ID = 0x60
};

//! @brief Info required to talk to an I2C device.
//!
//! Pairs an I2C port number with a device address.
//!
//! While the device address is often fixed and known in advance by the driver,
//! some devices have configurable addresses that can be changed with pin
//! settings. Thus, the same device may have different adresses on different
//! boards depending on how these pins are tied.
//!
//! Note that the @a address member's value is @i not pre-shifted. The 7-bit
//! address is right aligned within the byte, and the top bit is always set to 0.
typedef struct i2c_device_info {
    uint8_t port;       //!< I2C controller instance to which the device is connected. Starts at 1.
    uint8_t address;    //!< I2C device address in lower 7 bits.
    uint32_t freq;       //!< Maximum transfer speed in bits per second.
} i2c_device_info_t;

/*!
 * @brief An I2C transfer descriptor.
 *
 * To perform an I2C transfer, the caller first fills in an instance of this struct. Then
 * i2c_xfer() is called, passing a pointer to the #imx_i2c_request_t struct.
 *
 * @a ctl_addr should be set to either a valid controller instance number from 1 through
 * the number of I2C instances on the chip, or the base address of the controller.
 *
 * If @a device is set to a non-NULL value, it is a pointer to an #i2c_device_info_t struct
 * to use instead of the @a ctl_addr and @a dev_addr members of this struct.
 */
typedef struct imx_i2c_request {
    uint32_t ctl_addr;          //!< Either the I2C controller base address or instance number starting at 1.
    uint32_t dev_addr;          //!< The I2C device address.
    uint32_t reg_addr;          //!< The register address within the target device.
    uint32_t reg_addr_sz;       //!< Number of bytes for the address of I2C device register.
    uint8_t *buffer;            //!< Buffer to hold the data.
    uint32_t buffer_sz;         //!< The number of bytes for read/write.
    int32_t (*slave_receive) (const struct imx_i2c_request *rq);  //!< Function for slave to receive data from master.
    int32_t (*slave_transmit) (const struct imx_i2c_request *rq); //!< Function for slave to transmit data to master.
    const i2c_device_info_t * device; //!< Optional pointer to device info struct. Overrides @a ctl_addr and @a dev_addr if set.
} imx_i2c_request_t;

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the I2C module
 *
 * Mainly enable the I2C clock, module itself and the I2C clock prescaler.
 *
 * @param   base Either the base address of I2C module or the module's instance number. (also assigned for I2Cx_CLK)
 * @param   baud The desired data rate in bits per second.
 *
 * @return  0 if successful; non-zero otherwise
 */
int i2c_init(uint32_t base, uint32_t baud);

/*!
 * @brief Perform a single I2C transfer in the selected direction.
 *
 * This is a rather simple function that can be used for most I2C devices.
 *
 * Common steps for both READ and WRITE:
 *     - step 1: issue start signal
 *     - step 2: put I2C device addr on the bus (always 1 byte write. the dir always I2C_WRITE)
 *     - step 3: offset of the I2C device write (offset within the device. can be 1-4 bytes)
 *
 * For READ:
 *     - step 4: do repeat-start
 *     - step 5: send slave address again, but indicate a READ operation by setting LSB bit
 *     - Step 6: change to receive mode
 *     - Step 7: dummy read
 *     - Step 8: reading
 *
 * For WRITE:
 *     - Step 4: do data write
 *     - Step 5: generate STOP by clearing MSTA bit
 *
 * @param   rq        Pointer to #imx_i2c_request_t.
 * @param   dir       #I2C_READ or #I2C_WRITE
 *
 * @return  0 on success; non-zero otherwise
 */
int i2c_xfer(const imx_i2c_request_t *rq, int dir);

/*!
 * @brief Perform I2C read transfer.
 *
 * @param rq Pointer to #imx_i2c_request_t.
 */
int i2c_read(const imx_i2c_request_t *rq);

/*!
 * @brief Perform I2C write transfer.
 *
 * @param rq Pointer to #imx_i2c_request_t.
 */
int i2c_write(const imx_i2c_request_t *rq);

/*!
 * @brief I2C handler for the slave mode.
 *
 * The function is based on the flow chart for typical I2C polling routine described in the
 * I2C controller chapter of the reference manual.
 *
 * @param   rq Pointer to #imx_i2c_request_t.
 */
void i2c_slave_handler(const imx_i2c_request_t *rq);

/*!
 * @brief Handle the I2C transfers in slave mode.
 *
 * The slave mode behaves like any device with g_addr_cycle of address + g_data_cycle of data.
 * Master read =
 * START - SLAVE_ID/W - ACK - MEM_ADDR - ACK - START - SLAVE_ID/R - ACK - DATAx - NACK - STOP
 * 
 * Example for a 16-bit address access:
 * - 1st IRQ - receive the slave address and Write flag from master.
 * - 2nd IRQ - receive the lower byte of the requested 16-bit address.
 * - 3rd IRQ - receive the higher byte of the requested 16-bit address.
 * - 4th IRQ - receive the slave address and Read flag from master.
 * - 5th and next IRQ - transmit the data as long as NACK and STOP is not asserted.
 *
 * Master write =
 * START - SLAVE_ID/W - ACK - MEM_ADDR - ACK - DATAx - NACK - STOP
 *
 * - 1st IRQ - receive the slave address and Write flag from master.
 * - 2nd IRQ - receive the lower byte of the requested 16-bit address.
 * - 3rd IRQ - receive the higher byte of the requested 16-bit address.
 * - 4th and next IRQ - receive the data as long STOP is not asserted.
 *
 * @param   port Pointer to the I2C module structure.
 * @param   rq Pointer to #imx_i2c_request_t.
 */
void i2c_slave_xfer(imx_i2c_request_t *rq);

////////////////////////////////////////////////////////////////////////////////
// Board support
////////////////////////////////////////////////////////////////////////////////

//! @name Board support functions
//!
//! These functions are called by the driver in order to factor out board
//! specific functionality. They must be defined by the board support
//! library or the application.
//@{
//! @brief Configure IOMUX for the I2C driver.
void i2c_iomux_config(int instance);
//@}

#if defined(__cplusplus)
}
#endif

//! @}

#endif /* __IMX_I2C_H__ */
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
