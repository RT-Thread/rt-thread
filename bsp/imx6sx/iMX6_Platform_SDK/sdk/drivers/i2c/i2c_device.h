/*
 * Copyright (c) 2011-2013, Freescale Semiconductor, Inc.
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
#if !defined(__i2c_device_h__)
#define __i2c_device_h__

#include <stdint.h>
#include "i2c/imx_i2c.h"

//! @addtogroup diag_i2c
//! @{

//! @name I2C Errors
//@{
#define I2C_ERROR_BASE                           (1000)
#define I2C_OK                                   (0)

//! @brief OS-independent error code for success.
#define I2C_ERROR_NONE                           I2C_OK

//! @brief Got a NAK from the target device.
#define I2C_ERROR_GOT_NAK                        (I2C_ERROR_BASE | 0x06)

//! @brief No slave ACK.
//!
//! The slave addressed by a master transfer did not respond with an acknowledge. This is different
//! from #I2C_ERROR_GOT_NAK, where a slave actively NAKed a transaction.
#define I2C_ERROR_NO_SLAVE_ACK                   (I2C_ERROR_BASE | 0x07)

//! @brief Early termination error.
//!
//! This error indicates that a master write to a slave device was NAKed by the slave before the
//! transfer was completed.
#define I2C_ERROR_EARLY_TERM                     (I2C_ERROR_BASE | 0x08)

//! @brief Transaction lost arbitration to another master.
//!
//! This error indicates that a master read or write transaction lost an arbitration with another
//! master. Master loss is indicated by the master attempting to transmit a one to the bus at the
//! same time as another master writes a zero. The wired and bus produces a zero on the bus which
//! is detected by the losing master.
#define I2C_ERROR_MASTER_LOSS                    (I2C_ERROR_BASE | 0x09)
//@}

#if __cplusplus

class I2CDevice;

/*!
 * @brief Manages a single I2C master port.
 *
 * Once a port is initialized, it is stored in an internal table and is accessible with the
 * static getPort() member function.
 */
class I2CMasterPort
{
public:
    //! @brief Available I2C ports.
    enum _i2c_ports {
        kI2C0 = 0,
        kI2C1,
        kI2C2,
        kNumPorts
    };

    //! @brief Returns the port object for a given port number.
    //!
    //! A previously created port object will be returned if it exists. If no object has been
    //! created for the specified port number, one will be dynamically allocated for you.
    static I2CMasterPort * getPort(int port);
    
    //! @brief Constructor.
    I2CMasterPort(int port);
    
    //! @brief Destructor.
    virtual ~I2CMasterPort();

    //! @name Transfers
    //@{
    //! @brief Send data to a slave.
    virtual int send(uint8_t address, uint32_t subaddress, uint32_t subaddressLength, const void * data, uint32_t dataLength);
    //! @brief Receive data from a slave.
    virtual int receive(uint8_t address, uint32_t subaddress, uint32_t subaddressLength, void * data, uint32_t dataLength);
    //@}

    //! @name Bus control
    //@{
    virtual void reset();
    virtual void setBusSpeed(uint32_t freq);
    //@}

protected:

    int m_port; //!< This port number.
    
    //! Table of port objects.
    static I2CMasterPort * s_ports[];
    
};

/*!
 * @brief Class representing one I2C device.
 *
 * The device addresses used with this class must @i not be preshifted to be the upper 7 bits
 * of the address byte.
 */
class I2CDevice
{
public:
    
    //! @brief Constructor.
    //!
    //! The I2CMasterPort object will be created dynamically if it does not already exist.
    I2CDevice(int port, uint8_t address, uint32_t busFrequencyKHz=100);
    
    //! @brief Constructor.
    //!
    //! This version of init() takes a pointer to the I2CMasterPort object to use, instead of just a
    //! port number.
    I2CDevice(I2CMasterPort * port, uint8_t address, uint32_t busFrequencyKHz=100);
    
    //! @brief Constructor that takes a device info struct.
    I2CDevice(const i2c_device_info_t * deviceInfo);
    
    //! @name Bus frequency
    //@{
    uint32_t getBusFrequency() const { return m_freq; }
    void setBusFrequency(uint32_t busFrequencyKHz) { m_freq = busFrequencyKHz; }
    //@}
    
    //! @name Transfers
    //@{
    int send(uint32_t subaddress, uint32_t subaddressLength, const void * data, uint32_t dataLength);
    int send(const void * data, uint32_t dataLength) { return send(0, 0, data, dataLength); }
    
    int receive(uint32_t subaddress, uint32_t subaddressLength, void * data, uint32_t dataLength);
    int receive(void * data, uint32_t dataLength) { return receive(0, 0, data, dataLength); }
    //@}

protected:
    I2CMasterPort * m_port;   //!< Our port object.
    uint8_t m_address;  //!< The device's 7-bit address.
    uint32_t m_freq;    //!< Bus frequency to use with this device in kHz. Normally either 100 or 400.
};

#endif // __cplusplus

//! @}

#endif // __i2c_device_h__
///////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////




