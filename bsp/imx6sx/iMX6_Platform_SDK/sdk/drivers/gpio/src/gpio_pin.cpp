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
#include <cassert>
#include "gpio/gpio_pin.h"
#include "gpio/gpio.h"
#include "registers/regsiomuxc.h"

///////////////////////////////////////////////////////////////////////////////
// Code
///////////////////////////////////////////////////////////////////////////////

GpioPin::GpioPin(uint8_t bank, uint8_t pin, pin_direction_t dir)
:   m_bank(bank),
    m_pin(pin)
{
    gpio_set_gpio(m_bank, m_pin);
    setDirection(dir);
}

GpioPin::GpioPin(uint32_t combinedPin, pin_direction_t dir)
:   m_bank(GPIO_EXTRACT_BANK(combinedPin)),
    m_pin(GPIO_EXTRACT_PIN(combinedPin))
{
    gpio_set_gpio(m_bank, m_pin);
    setDirection(dir);
}

void GpioPin::setPin(uint8_t bank, uint8_t pin)
{
    m_bank = bank;
    m_pin = pin;
    gpio_set_gpio(m_bank, m_pin);
}

void GpioPin::setPin(uint32_t combinedPin)
{
    m_bank = GPIO_EXTRACT_BANK(combinedPin);
    m_pin = GPIO_EXTRACT_PIN(combinedPin);
    gpio_set_gpio(m_bank, m_pin);
}

void GpioPin::setDirection(pin_direction_t direction)
{
    int32_t dir = (direction == kInput) ? GPIO_GDIR_INPUT : GPIO_GDIR_OUTPUT;
    gpio_set_direction(m_bank, m_pin, dir);
}

GpioPin::pin_direction_t GpioPin::getDirection() const
{
    return (gpio_get_direction(m_bank, m_pin) == GPIO_GDIR_INPUT) ? kInput : kOutput;
}

void GpioPin::set(bool driveHigh)
{
    if (driveHigh)
    {
        set();
    }
    else
    {
        clear();
    }
}

void GpioPin::set()
{
    gpio_set_level(m_bank, m_pin, 1);
}

void GpioPin::clear()
{
    gpio_set_level(m_bank, m_pin, 0);
}

bool GpioPin::get() const
{
    return gpio_get_level(m_bank, m_pin);
}

#if defined(__hide_from_compiler__)
    #pragma mark -
#endif

GpioOutput & GpioOutput::operator = (const GpioPin & rhs)
{
    setPin(rhs.getBank(), rhs.getPin());
    setDirection(kOutput);
    return *this;
}

#if defined(__hide_from_compiler__)
    #pragma mark -
#endif

GpioInput & GpioInput::operator = (const GpioPin & rhs)
{
    setPin(rhs.getBank(), rhs.getPin());
    setDirection(kInput);
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////

