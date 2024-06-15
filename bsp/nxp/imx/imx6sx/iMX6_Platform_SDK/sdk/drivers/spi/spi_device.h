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
#if !defined(__spi_device_h__)
#define __spi_device_h__

#include <stdint.h>
#include "spi/ecspi_ifc.h"

//! @addtogroup diag_spi
//! @{

#if __cplusplus

/*!
 * @brief Manages a single SPI master port.
 *
 * Once a port is initialized, it is stored in an internal table and is accessible with the
 * static getPort() member function.
 */
class SPIMasterPort
{
public:
    //! @brief Returns the port object for a given port number.
    //!
    //! A previously created port object will be returned if it exists. If no object has been
    //! created for the specified port number, one will be dynamically allocated for you.
    static SPIMasterPort * getPort(int port);
    
    //! @brief Constructor.
    SPIMasterPort(int port);
    
    //! @brief Destructor.
    virtual ~SPIMasterPort();

    //! @name Transfers
    //@{
    //! @brief Perform a full-duplex transfer, both sending and receiving data.
    //!
    //! The number of bytes sent and received is always the same. And because SPI transfers are
    //! always full-duplex, data is always transferred in both directions. However, either of the
    //! send or receive buffer pointers may be set to NULL. If the @a sendData buffer is NULL,
    //! then zero bytes are sent to the device. If @a receiveData is NULL, then any received data
    //! is simply ignored.
    //!
    //! @param address Chip select number of the device to talk with.
    //! @param sendData Pointer to buffer of data to send. Optional, may be NULL.
    //! @param receiveData Pointer to buffer of data to receive. Optional, may be NULL.
    //! @param dataLength Number of bits (not bytes!) to send and receive. If this value is zero then no
    //!     transfer is performed.
    //! @retval SUCCESS
    virtual int transfer(uint8_t address, const void * sendData, void * receiveData, uint32_t dataLength);
    //@}

    //! @name Bus control
    //@{
    virtual void reset();
    virtual void configure(const param_ecspi_t & config);
    //@}

protected:

    dev_ecspi_e m_port; //!< This port number.
    
    //! Table of port objects.
    static SPIMasterPort * s_ports[];
    
};

/*!
 * @brief Class representing one SPI slave device.
 *
 * The device addresses used with this class specify which slave chip select signal to use
 * when communicating with the device.
 */
class SPIDevice
{
public:
    
    //! @brief Constructor.
    //!
    //! The I2CMasterPort object will be created dynamically if it does not already exist.
    SPIDevice(int port, uint8_t address, uint32_t busFrequencyKHz=1000);
    
    //! @brief Constructor.
    //!
    //! This version of the constructor takes a pointer to the SPIMasterPort object to use, instead
    //! of just a port number.
    SPIDevice(SPIMasterPort * port, uint8_t address, uint32_t busFrequencyKHz=1000);
    
    //! @name Bus configuration
    //@{
    void setBusFrequency(uint32_t busFrequencyKHz);
    void setPolarityAndPhase(unsigned polarity, unsigned phase);
    void setChipSelectPolarity(unsigned polarity);
    //@}
    
    //! @name Transfers
    //@{
    //! @brief Perform a full-duplex transfer, both sending and receiving data.
    //!
    //! The number of bytes sent and received is always the same. And because SPI transfers are
    //! always full-duplex, data is always transferred in both directions. However, either of the
    //! send or receive buffer pointers may be set to NULL. If the @a sendData buffer is NULL,
    //! then zero bytes are sent to the device. If @a receiveData is NULL, then any received data
    //! is simply ignored.
    //!
    //! @param sendData Pointer to buffer of data to send. Optional, may be NULL.
    //! @param receiveData Pointer to buffer of data to receive. Optional, may be NULL.
    //! @param dataLength Number of bits (not bytes!) to send and receive. If this value is zero then no
    //!     transfer is performed.
    //! @retval SUCCESS
    int transfer(const void * sendData, void * receiveData, uint32_t dataLength);
    
    //! @brief Send data to the slave device.
    int send(const void * data, uint32_t dataLength) { return transfer(data, NULL, dataLength); }
    
    //! @brief Receive data from the slave device.
    int receive(void * data, uint32_t dataLength) { return transfer(NULL, data, dataLength); }
    //@}

protected:
    SPIMasterPort * m_port;   //!< Our port object.
    param_ecspi_t m_params; //!< Parameters for this device.
    uint32_t m_freq;    //!< Nominal bus frequency to use with this device in kHz.
};

#endif // __cplusplus

//! @}

#endif // __i2c_device_h__
///////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////




