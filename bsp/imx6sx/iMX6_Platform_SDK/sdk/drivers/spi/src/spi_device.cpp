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

#include "spi/spi_device.h"
#include <assert.h>
#include <string.h>
#include "registers/regsecspi.h"
#include "core/ccm_pll.h"

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

namespace {

const param_ecspi_t kDefaultSPIParams = {
        0, // slave 0
        1, // master
        0, // active low
        0, // active high
        0, // phase 0
        16, // divide by 16
        0  // divide by 1
    };

}

///////////////////////////////////////////////////////////////////////////////
// Variables
///////////////////////////////////////////////////////////////////////////////

SPIMasterPort * SPIMasterPort::s_ports[HW_ECSPI_INSTANCE_COUNT] = {0};

///////////////////////////////////////////////////////////////////////////////
// Code
///////////////////////////////////////////////////////////////////////////////

SPIMasterPort * SPIMasterPort::getPort(int port)
{
    // Make sure the port is within range.
    if (port < 1 || port > HW_ECSPI_INSTANCE_COUNT)
    {
        return NULL;
    }
    
    SPIMasterPort * portObject = s_ports[port - 1];
    if (!portObject)
    {
        portObject = new SPIMasterPort(port);
    }
    return portObject;
}
    
void SPIMasterPort::reset()
{
    // Close and reopen to reset the port.
    ecspi_close(m_port);
    ecspi_open(m_port, &kDefaultSPIParams);
}

SPIMasterPort::SPIMasterPort(int port)
:   m_port((dev_ecspi_e)port)
{
    // Make sure the port is within range.
    assert(port >= 1 && port <= HW_ECSPI_INSTANCE_COUNT);
    
    // Open the port.
    int err = ecspi_open(m_port, &kDefaultSPIParams);
    if (err)
    {
        return;
    }
    
    // Save this port for future access.
    if (!s_ports[port])
    {
        s_ports[port - 1] = this;
    }
}

SPIMasterPort::~SPIMasterPort()
{
    // Close the port.
    ecspi_close(m_port);
    
    // Clear the saved port entry if it is set to us.
    if (s_ports[m_port - 1] == this)
    {
        s_ports[m_port - 1] = NULL;
    }
}

int SPIMasterPort::transfer(uint8_t address, const void * sendData, void * receiveData, uint32_t dataLength)
{
    return ecspi_xfer(m_port, reinterpret_cast<const uint8_t *>(sendData), reinterpret_cast<uint8_t *>(receiveData), dataLength);
}

void SPIMasterPort::configure(const param_ecspi_t & config)
{
    ecspi_configure(m_port, &config);
}

#if defined(__hide_from_compiler__)
    #pragma mark -
#endif

SPIDevice::SPIDevice(int port, uint8_t address, uint32_t busFrequencyKHz)
:   m_port(NULL),
    m_freq(0)
{
    m_port = SPIMasterPort::getPort(port);
    assert(m_port);
    
    m_params.channel = address;
    setBusFrequency(busFrequencyKHz);
}

SPIDevice::SPIDevice(SPIMasterPort * port, uint8_t address, uint32_t busFrequencyKHz)
:   m_port(NULL),
    m_freq(0)
{
    m_port = port;
    assert(m_port);
    
    m_params.channel = address;
    m_params.mode = 1; // master
    m_params.ss_pol = 0; // active low
    m_params.sclk_pol = 0;
    m_params.sclk_pha = 0;
    
    setBusFrequency(busFrequencyKHz);
}

void SPIDevice::setBusFrequency(uint32_t busFrequencyKHz)
{
    uint32_t clk = get_peri_clock(SPI_CLK);
    uint32_t busFreqHz = busFrequencyKHz * 1000;
    
    // busFreqHz = clk / pre_div / 2^post_div
    uint32_t div = clk / busFreqHz;
    
    // Make sure we don't end up with a clock higher than the requested one.
    if (clk / div > busFreqHz)
    {
        ++div;
    }
    
    uint32_t pre = 1;
    uint32_t post = 0;
    
    // Iteratively scan for a divider pair that produces the closest actual clock.
    // The pre and post dividers are each 4-bit fields. Pre ranges from 1-16, while
    // post ranges from 0-15 (resulting in a divisor of 2^0=1 through 2^15=65536).
    while ((pre * (1 << post) < div) && (post < 16))
    {
        while ((pre * (1 << post) < div) && (pre < 17))
        {
            ++pre;
        }
        
        // Overflow.
        if (pre >= 17)
        {
            ++post;
            pre = 1;
        }
    }
    
    // Clip the dividers to their maximum values.
    if (pre > 16)
    {
        pre = 16;
    }
    if (post > 15)
    {
        post = 15;
    }
    
    // Save the resulting dividers in the bus params.
    m_params.pre_div = pre;
    m_params.post_div = post;
}

void SPIDevice::setPolarityAndPhase(unsigned polarity, unsigned phase)
{
    m_params.sclk_pol = polarity; // 0==active high, 1==active low
    m_params.sclk_pha = phase;
}

void SPIDevice::setChipSelectPolarity(unsigned polarity)
{
    m_params.ss_pol = polarity;
}

int SPIDevice::transfer(const void * sendData, void * receiveData, uint32_t dataLength)
{
    assert(m_port);
    m_port->configure(m_params);
    return m_port->transfer(m_params.channel, sendData, receiveData, dataLength);
}

///////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////
