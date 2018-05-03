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
#if !defined(__software_i2c_port_h__)
#define __software_i2c_port_h__

#include "i2c/i2c_device.h"
#include "gpio/gpio_pin.h"

//! @addtogroup diag_i2c
//! @{

/*!
 * @brief GPIO-based software I2C peripheral.
 *
 * In order to stay consistent with the i2c spec, we do not 
 * drive the SDA/SCL HIGH.  Instead the pin will be placed into
 * HI-Z and allow the pull-ups to get the line to HIGH.  This makes
 * sure we do not have bus contention on the 9th clock pulse (ACK) as
 * there may be period when SDA is HIGH and we have not HI-Z'ed the line
 * to read in the pulse, but the slave device tries to drive the line LOW.
 * We are safe when we drive the line LOW and the slave device drives
 * the line LOW.
 *
 * Known issues:
 * - Does not perform master arbitration.
 * - No timeouts.
 */
class SoftwareI2CPort : public I2CMasterPort
{
public:
    
    //! @brief Init the I2C port.
    int init(GpioPin * scl, GpioPin * sda);
    
    //! @brief Destructor.
    virtual ~SoftwareI2CPort();

    virtual int send(uint8_t address, uint32_t subaddress, uint32_t subaddressLength, const void * data, uint32_t dataLength);
    virtual int receive(uint8_t address, uint32_t subaddress, uint32_t subaddressLength, void * data, uint32_t dataLength);

    virtual void reset();
    virtual void setupBusTiming(uint32_t freq);

protected:

    GpioPin m_scl;
    GpioPin m_sda;

    struct clock_timing
    {
        uint32_t low_count;
        uint32_t high_count;
    
        uint32_t rcv_count;
        uint32_t xmit_count;
    
        uint32_t lead_in_count;
    };
    
    clock_timing m_timing;
    uint32_t m_addressBuffer[3];

    void fillAddressBuffer(uint8_t address, uint32_t subaddress, uint32_t subaddressLength);

    void delay(uint32_t us);

    bool readACK();
    void sendStart();
    void sendStop();
    bool sendByte(uint8_t byte, bool holdLow);
    uint8_t readByte(bool send_ack, bool holdLow);

    bool _write(uint8_t u8SlaveAddress, const void* pData, uint16_t u16Size, bool doSendStart, bool bStop, bool holdLow);
    bool _read(uint8_t u8SlaveAddress, void* pData, uint16_t u16Size, bool holdLow);
    
};

//! @}

#endif // __software_i2c_port_h__
///////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////




