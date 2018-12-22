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
#if !defined(__gpio_pin_h__)
#define __gpio_pin_h__

#include <stdint.h>
#include <stdbool.h>

//! @addtogroup diag_gpio
//! @{

//! @name GpioPin helper macros
//@{
//! @brief Combines a bank and pin into a single scalar value.
#define GPIO_MAKE_PIN(b,p) ((((b) & 0xff) << 16) | ((p) & 0xff))

//! @brief Extract the bank number from a combined bank and pin value.
#define GPIO_EXTRACT_BANK(c) (((c) >> 16) & 0xff)

//! @brief Extract the pin number from a combined bank and pin value.
#define GPIO_EXTRACT_PIN(c) ((c) & 0xff)
//@}

#if __cplusplus

/*!
 * @brief GPIO pin.
 *
 * When you construct a GpioPin object, the specified pin is configured as a GPIO pin by
 * setting the appropriate register in the IOMUX controller. This also happens if you
 * change the pin by calling setPin(). The only exceptions to this are the default constructor
 * and copy constructor, which don't adjust mux settings for the pin. (The pin should already
 * be muxed as a GPIO when copied.) At no point will this class restore a pin to its previous
 * mux setting.
 */
class GpioPin
{
public:
    //! @brief GPIO pin directions.
    typedef enum _pin_direction {
        kInput = 0,
        kOutput = 1
    } pin_direction_t;
    
    //! @brief Default constructor.
    //!
    //! The bank and pin numbers are both set to 0. This constructor is really meant to allow
    //! instances to be created and initialized later, such as in structs or as globals.
    GpioPin() : m_bank(0), m_pin(0) {}
    
    //! @brief Constructor to set the bank and pin.
    //!
    //! Configures the pin mux setting to be a GPIO.
    GpioPin(uint8_t bank, uint8_t pin, pin_direction_t dir=kOutput);
    
    //! @brief Constructor taking a combined bank and pin value.
    GpioPin(uint32_t combinedPin, pin_direction_t dir=kOutput);
    
    //! @brief Copy constructor.
    GpioPin(const GpioPin & other) : m_bank(other.m_bank), m_pin(other.m_pin) {}
    
    //! @brief Assignment operator.
    GpioPin & operator = (const GpioPin & rhs) { setPin(rhs.getBank(), rhs.getPin()); return *this; }
    
    //! @name Pin number
    //@{
    void setPin(uint8_t bank, uint8_t pin);
    void setPin(uint32_t combinedPin);
    uint8_t getBank() const { return m_bank; }
    uint8_t getPin() const { return m_pin; }
    //@}
    
    //! @name I/O direction
    //@{
    void setDirection(pin_direction_t direction);
    pin_direction_t getDirection() const;
    //@}

    //! @name Pin values
    //@{
    void set(bool driveHigh);
    void set();
    void clear();
    bool get() const;
    //@}
    
    //! @name Operators
    //@{
    operator bool () const { return get(); }
    GpioPin & operator = (bool driveHigh) { set(driveHigh); return *this; }
    bool operator == (bool other) const { return get() == other; }
    bool operator != (bool other) const { return get() != other; }
    bool operator == (const GpioPin & rhs) const { return (m_bank == rhs.m_bank) && (m_pin == rhs.m_pin); }
    bool operator != (const GpioPin & rhs) const { return !(operator == (rhs)); }
    //@}

protected:

    uint8_t m_bank; //!< Bank number.
    uint8_t m_pin;  //!< Pin number.
    
};

/*!
 * @briefGeneral purpose digital output.
 */
class GpioOutput : public GpioPin
{
public:
    //! @brief Default constructor.
    GpioOutput() : GpioPin() {}
    
    //! @brief Constructor to set the bank and pin.
    //!
    //! Configures the pin mux setting to be a GPIO.
    GpioOutput(uint8_t bank, uint8_t pin) : GpioPin(bank, pin, kOutput) {}
    
    //! @brief Constructor taking a combined bank and pin value.
    GpioOutput(uint32_t combinedPin) : GpioPin(combinedPin, kOutput) {}
    
    //! @brief Copy constructor.
    GpioOutput(const GpioPin & other) : GpioPin(other.getBank(), other.getPin(), kOutput) {}
    
    //! @brief Assignment operator.
    GpioOutput & operator = (const GpioPin & rhs);
    
    //! @name Operators
    //@{
    operator bool () const { return get(); }
    GpioPin & operator = (bool driveHigh) { set(driveHigh); return *this; }
    bool operator == (bool other) const { return get() == other; }
    bool operator != (bool other) const { return get() != other; }
    bool operator == (const GpioPin & rhs) const { return (getBank() == rhs.getBank()) && (getPin() == rhs.getPin()); }
    bool operator != (const GpioPin & rhs) const { return !(operator == (rhs)); }
    //@}
};

/*!
 * @brief General purpose digital input.
 */
class GpioInput : public GpioPin
{
public:
    //! @brief Default constructor.
    GpioInput() : GpioPin() {}
    
    //! @brief Constructor to set the bank and pin.
    //!
    //! Configures the pin mux setting to be a GPIO.
    GpioInput(uint8_t bank, uint8_t pin) : GpioPin(bank, pin, kInput) {}
    
    //! @brief Constructor taking a combined bank and pin value.
    GpioInput(uint32_t combinedPin) : GpioPin(combinedPin, kInput) {}
    
    //! @brief Copy constructor.
    GpioInput(const GpioPin & other) : GpioPin(other.getBank(), other.getPin(), kInput) {}
    
    //! @brief Assignment operator.
    GpioInput & operator = (const GpioPin & rhs);
    
    //! @name Operators
    //@{
    operator bool () const { return get(); }
    bool operator == (bool other) const { return get() == other; }
    bool operator != (bool other) const { return get() != other; }
    bool operator == (const GpioPin & rhs) const { return (getBank() == rhs.getBank()) && (getPin() == rhs.getPin()); }
    bool operator != (const GpioPin & rhs) const { return !(operator == (rhs)); }
    //@}
};

#endif // __cplusplus

//! @}

#endif // __gpio_pin_h__
///////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////




