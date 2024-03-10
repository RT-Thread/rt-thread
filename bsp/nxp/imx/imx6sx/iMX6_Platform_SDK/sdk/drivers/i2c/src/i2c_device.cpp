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

#include "i2c/i2c_device.h"
#include <assert.h>
#include <string.h>
#include "i2c/imx_i2c.h"

//! @brief Frequency to init the port to.
const uint32_t kI2CDefaultBusFrequency = 100;

///////////////////////////////////////////////////////////////////////////////
// Variables
///////////////////////////////////////////////////////////////////////////////

I2CMasterPort * I2CMasterPort::s_ports[kNumPorts] = {0};

///////////////////////////////////////////////////////////////////////////////
// Code
///////////////////////////////////////////////////////////////////////////////

I2CMasterPort * I2CMasterPort::getPort(int port)
{
    // Make sure the port is within range.
    if (port < 0 || port >= kNumPorts)
    {
        return NULL;
    }
    
    I2CMasterPort * portObject = s_ports[port];
    if (!portObject)
    {
        portObject = new I2CMasterPort(port);
    }
    return portObject;
}
    
void I2CMasterPort::reset()
{
    i2c_init(m_port + 1, kI2CDefaultBusFrequency * 1000);
}

I2CMasterPort::I2CMasterPort(int port)
:   m_port(port)
{
    // Our port numbers start at 0, but the instance passed to i2c_init() is base 1.
    int err = i2c_init(port + 1, kI2CDefaultBusFrequency * 1000);
    if (err)
    {
        return;
    }
    
    // Save this port for future access.
    if (port < kNumPorts && !s_ports[port])
    {
        s_ports[port] = this;
    }
}

I2CMasterPort::~I2CMasterPort()
{
    s_ports[m_port] = NULL;
}

//! Writing data to the I2C target uses two DMA descriptors. It can be done with a single 
//! descriptor, but that requires one contiguous buffer for all data including the address byte.
//! So we use two descriptors, which allows us to use the @a data pointer directly instead of
//! having to copy into a temporary buffer.
int I2CMasterPort::send(uint8_t address, uint32_t subaddress, uint32_t subaddressLength, const void * data, uint32_t dataLength)
{
    assert(!data || ((uint32_t)data & 3) == 0);  // Data pointer must be word aligned.
    assert(!data || dataLength);
    
    // Build request.
    imx_i2c_request_t rq = {0};
    rq.ctl_addr = m_port + 1;
    rq.dev_addr = address;
    rq.reg_addr = subaddress;
    rq.reg_addr_sz = subaddressLength;
    rq.buffer = const_cast<uint8_t *>(reinterpret_cast<const uint8_t *>(data));
    rq.buffer_sz = dataLength;
    
    return i2c_xfer(&rq, I2C_WRITE);
}

int I2CMasterPort::receive(uint8_t address, uint32_t subaddress, uint32_t subaddressLength, void * data, uint32_t dataLength)
{
    assert(!data || ((uint32_t)data & 3) == 0);  // Data pointer must be word aligned.
    assert(!data || dataLength);
    
    // Build request.
    imx_i2c_request_t rq = {0};
    rq.ctl_addr = m_port + 1;
    rq.dev_addr = address;
    rq.reg_addr = subaddress;
    rq.reg_addr_sz = subaddressLength;
    rq.buffer = reinterpret_cast<uint8_t *>(data);
    rq.buffer_sz = dataLength;
    
    return i2c_xfer(&rq, I2C_READ);
}

//! To change timing we have to re-init the port.
void I2CMasterPort::setBusSpeed(uint32_t freq)
{
    i2c_init(m_port + 1, freq * 1000);
}

#if defined(__hide_from_compiler__)
    #pragma mark -
#endif

I2CDevice::I2CDevice(int port, uint8_t address, uint32_t busFrequencyKHz)
{
    m_port = I2CMasterPort::getPort(port);
    assert(m_port);
    m_address = address;
    m_freq = busFrequencyKHz;
}

I2CDevice::I2CDevice(I2CMasterPort * port, uint8_t address, uint32_t busFrequencyKHz)
{
    m_port = port;
    assert(m_port);
    m_address = address;
    m_freq = busFrequencyKHz;
}

I2CDevice::I2CDevice(const i2c_device_info_t * deviceInfo)
{
    m_port = I2CMasterPort::getPort(deviceInfo->port - 1);
    assert(m_port);
    m_address = deviceInfo->address;
    m_freq = deviceInfo->freq;
}

int I2CDevice::send(uint32_t subaddress, uint32_t subaddressLength, const void * data, uint32_t dataLength)
{
    m_port->setBusSpeed(m_freq);
    return m_port->send(m_address, subaddress, subaddressLength, data, dataLength);
}

int I2CDevice::receive(uint32_t subaddress, uint32_t subaddressLength, void * data, uint32_t dataLength)
{
    m_port->setBusSpeed(m_freq);
    return m_port->receive(m_address, subaddress, subaddressLength, data, dataLength);
}

///////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////
