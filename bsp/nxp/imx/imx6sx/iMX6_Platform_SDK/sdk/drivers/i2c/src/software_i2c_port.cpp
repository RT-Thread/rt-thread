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
#include "i2c/software_i2c_port.h"
#include <cassert>
#include "timer/timer.h"

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

//! @brief Address r/w flag values.
//!
//! These constants are used to indicate the transfer direction for an I2C transaction. The
//! read/write flag is passed in the least significant bit of the target device address.
enum _i2c_rw
{
    kI2CRead = 1,
    kI2CWrite = 0
};

// const static struct clock_timing ClockTiming[2] = {
//     { 3, 3, 2, 2, 5 },  // 100KHz
//     { 0, 0, 0, 0, 0 }   // 400KHz
// };

#define HOST_TO_LE_LONG(n) (n)

///////////////////////////////////////////////////////////////////////////////
// Code
///////////////////////////////////////////////////////////////////////////////

int SoftwareI2CPort::init(GpioPin * scl, GpioPin * sda)
{
    m_scl = *scl;
    m_sda = *sda;
    
    return I2C_OK;
}

SoftwareI2CPort::~SoftwareI2CPort()
{
}

void SoftwareI2CPort::fillAddressBuffer(uint8_t address, uint32_t subaddress, uint32_t subaddressLength)
{
    // First clear the address buffer.
    m_addressBuffer[0] = HOST_TO_LE_LONG((address << 1) | kI2CWrite);
    m_addressBuffer[1] = 0;

    // Set the target address and r/w flag.
    uint8_t * addressBytes = reinterpret_cast<uint8_t *>(&m_addressBuffer[1]);
    
    // Now fill in the subaddress if we have one.
    if (subaddressLength)
    {
        for (int i = subaddressLength; i > 0; --i)
        {
            addressBytes[i - 1] = subaddress & 0xff;
            subaddress >>= 8;
        }
    }
}

int SoftwareI2CPort::send(uint8_t address, uint32_t subaddress, uint32_t subaddressLength, const void * data, uint32_t dataLength)
{
    fillAddressBuffer(address, subaddress, subaddressLength);
    
    m_scl.setDirection(GpioPin::kInput);
    m_sda.setDirection(GpioPin::kInput);

    m_scl.clear();
    m_sda.clear();

    sendStart();

    bool ret = sendByte((address << 1), true);
    if (!ret)
    {
        sendStop();
    
        return I2C_ERROR_NO_SLAVE_ACK;
    }

    const uint8_t * subaddressData = (const uint8_t *)&m_addressBuffer[1];
    while (subaddressLength--)
    {
        ret = sendByte(*subaddressData++, true);
        if (!ret)
        {
            sendStop();
    
            return I2C_ERROR_GOT_NAK;
        }
    }

    const uint8_t * transfer_data = reinterpret_cast<const uint8_t *>(data);
    uint32_t u16Size = dataLength;
    while (u16Size--)
    {
        ret = sendByte(*transfer_data++, true);
        if (!ret)
        {
            sendStop();
    
            return I2C_ERROR_GOT_NAK;
        }
    }

    sendStop();
    
    return I2C_OK;
}

int SoftwareI2CPort::receive(uint8_t address, uint32_t subaddress, uint32_t subaddressLength, void * data, uint32_t dataLength)
{
    bool gotAck;
    
    fillAddressBuffer(address, subaddress, subaddressLength);
    
    // Send subaddress.
    if (subaddress)
    {
        // Send stop if there is no data.
        gotAck = _write(address, &m_addressBuffer[1], subaddressLength, true, !dataLength, false);
        
        if (!gotAck)
        {
            return I2C_ERROR_NO_SLAVE_ACK;
        }
    }
    
    // Read data.
    if (data)
    {
        // Always send stop.
        gotAck = _read(address, data, dataLength, false);
    }
    else if (!subaddress)
    {
        // Send only the slave read address.
        gotAck = _read(address, NULL, 0, false);
    }
    
    if (!gotAck)
    {
        return I2C_ERROR_NO_SLAVE_ACK;
    }
    
    return I2C_OK;
}

void SoftwareI2CPort::reset()
{
}

void SoftwareI2CPort::setupBusTiming(uint32_t freq)
{
    m_timing.low_count = 10;
    m_timing.high_count = 10;
    m_timing.rcv_count = 5;
    m_timing.xmit_count = 5;
    m_timing.lead_in_count = 7;
}

void SoftwareI2CPort::delay(uint32_t us)
{
    hal_delay_us(us);
}

bool SoftwareI2CPort::readACK()
{
    uint8_t bit;

    m_sda.setDirection(GpioPin::kInput);

    delay(m_timing.low_count + m_timing.xmit_count);
    m_scl.setDirection(GpioPin::kInput);
    delay(m_timing.rcv_count);

    bit = m_sda;

    delay(m_timing.high_count);

    // Drive the clock line low so that we retain ownership of the i2c bus.
    m_scl.setDirection(GpioPin::kOutput);

    // Some devices seem to require the SDA to be low on entry into the next byte.
    m_sda.setDirection(GpioPin::kOutput);

    return (bit == 0);
}

void SoftwareI2CPort::sendStart()
{
    m_sda.setDirection(GpioPin::kOutput);
    delay(m_timing.lead_in_count);
    m_scl.setDirection(GpioPin::kOutput);
}

void SoftwareI2CPort::sendStop()
{
    delay(m_timing.low_count + m_timing.xmit_count);

    m_scl.setDirection(GpioPin::kInput);
    delay(m_timing.lead_in_count);
    m_sda.setDirection(GpioPin::kInput);
}

bool SoftwareI2CPort::sendByte(uint8_t byte, bool holdLow)
{
    uint32_t mask = 0x80;

    for (mask = 0x80; mask != 0; mask >>= 1)
    {
        delay(m_timing.xmit_count);
    
        if (byte & mask)
        {
            m_sda.setDirection(GpioPin::kInput);
        }
        else
        {
            m_sda.setDirection(GpioPin::kOutput);
        }
    
        delay(m_timing.low_count);
        m_scl.setDirection(GpioPin::kInput);
        while (!m_scl); // wait for scl to go high, in case the slave is holding it low for clock stretching
        delay(m_timing.high_count + m_timing.rcv_count);
        m_scl.setDirection(GpioPin::kOutput);
    }

    return readACK();
}

uint8_t SoftwareI2CPort::readByte(bool send_ack, bool holdLow)
{
    int i;
    uint8_t byte = 0;

    m_sda.setDirection(GpioPin::kInput);

    for (i = 7; i >= 0; i--)
    {
        delay(m_timing.xmit_count + m_timing.low_count);
        m_scl.setDirection(GpioPin::kInput);
        while (!m_scl); // wait for scl to go high, in case the slave is holding it low for clock stretching
        delay(m_timing.rcv_count);
    
        byte |= m_sda << i;
    
        delay(m_timing.high_count);
        m_scl.setDirection(GpioPin::kOutput);
    }

    // We have read 8-bits so now perform the ACK/NAK.
    delay(m_timing.xmit_count);

    m_sda.setDirection(send_ack ? GpioPin::kOutput : GpioPin::kInput);

    delay(m_timing.low_count);

    m_scl.setDirection(GpioPin::kInput);
    while (!m_scl); // wait for scl to go high, in case the slave is holding it low for clock stretching
    delay(m_timing.high_count + m_timing.rcv_count);
    m_scl.setDirection(GpioPin::kOutput);

    m_sda.setDirection(GpioPin::kInput);

    return byte;
}

bool SoftwareI2CPort::_write(uint8_t u8SlaveAddress, const void* pData, uint16_t u16Size, bool doSendStart, bool bStop, bool holdLow)
{
    const uint8_t * transfer_data = reinterpret_cast<const uint8_t *>(pData);

    if (doSendStart)
    {
        m_scl.setDirection(GpioPin::kInput);
    }
    m_sda.setDirection(GpioPin::kInput);

    m_scl.clear();
    m_sda.clear();

    if (doSendStart)
    {
        sendStart();
    }

    bool ret = sendByte((u8SlaveAddress << 1), true);
    if (!ret)
    {
        sendStop();
    
        return ret;
    }

    while (u16Size--)
    {
        bool isLast = (u16Size == 0);
        ret = sendByte(*transfer_data++, (isLast && holdLow));
        if (!ret)
        {
            sendStop();
    
            return ret;
        }
    }

    if (bStop)
    {
        sendStop();
    }

    return true;
}

bool SoftwareI2CPort::_read(uint8_t u8SlaveAddress, void* pData, uint16_t u16Size, bool holdLow)
{
    uint8_t * transfer_data = reinterpret_cast<uint8_t *>(pData);

    m_scl.setDirection(GpioPin::kInput);
    m_sda.setDirection(GpioPin::kInput);

    m_scl.clear();
    m_sda.clear();

    sendStart();

    bool ret = sendByte((u8SlaveAddress << 1) | 0x01, true);
    if (!ret)
    {
        sendStop();
    
        return ret;
    }

    while (u16Size--)
    {
        // The last byte in the transfer must NAK the byte.  This tells
        // the slave device that the transfer is finished.
        bool isLast = (u16Size == 0);
        *transfer_data++ = readByte(!isLast, (isLast && holdLow));
    }

    sendStop();

    return true;
}

///////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////

