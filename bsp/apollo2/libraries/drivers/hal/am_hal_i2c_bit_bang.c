//*****************************************************************************
//
//  am_hal_i2c_bit_bang.c
//! @file
//!
//! @brief I2C bit bang module.
//!
//! These functions implement the I2C bit bang utility
//! It implements an I2C interface at close to 400 kHz
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>

#include "am_mcu_apollo.h"
//#include "am_util.h"
#include "am_hal_i2c_bit_bang.h"

// Max number of clock cycles to wait for clock stretch
#define I2C_BB_MAX_CLOCK_STRETCH_WAIT               100

#define I2C_BB_DESIRED_FREQ_HZ                      400000

#define I2C_BB_CYCLES_PER_DELAY_COUNT               3
#define I2C_BB_ONE_BIT_TIME_IN_CYCLES               (AM_HAL_CLKGEN_FREQ_MAX_HZ/I2C_BB_DESIRED_FREQ_HZ)
#define I2C_BB_ONE_BIT_TIME_IN_DELAY_COUNT          (I2C_BB_ONE_BIT_TIME_IN_CYCLES/I2C_BB_CYCLES_PER_DELAY_COUNT)

// Number of loops (each worth 3 cycles) needed to delay for defined time
// This is imprecise, as there is a setup time as well which is not accounted
// for
// One Bit time = 120 Cycles (400 kHz @ 48 MHz)
#define HALF_BIT_TIME    (I2C_BB_ONE_BIT_TIME_IN_DELAY_COUNT/2)
#define QUARTER_BIT_TIME (I2C_BB_ONE_BIT_TIME_IN_DELAY_COUNT/4)
#define ASM_DELAY        am_hal_flash_delay

// Empirically determined adjustments to account for the fact that there is a
// variable time spent in actual processing as well, and hence we need not delay
// for the full time. This processing time is variable based on exact processing
// needed at various times, and will also vary based on compiler type and
// optimization levels
#define I2C_BB_TIMER_ADJUST     6 // Can not be more than QUARTER_BIT_TIME - 1
#define I2C_BB_TIMER_HI_ADJUST  15 // Can not be more than HALF_BIT_TIME - 1
#define I2C_BB_TIMER_LO_ADJUST  13 // Can not be more than HALF_BIT_TIME - 1

// Wait till it is time to end the SCL Hi Period
#define WAIT_I2C_CLOCK_HI_PERIOD()     ASM_DELAY(HALF_BIT_TIME - I2C_BB_TIMER_HI_ADJUST)
// Wait till it is time to end the SCL Lo Period
#define WAIT_I2C_CLOCK_LOW_PERIOD()    ASM_DELAY(HALF_BIT_TIME - I2C_BB_TIMER_LO_ADJUST)
// Delay for Quarter Clock
#define WAIT_FOR_QUARTER_I2C_CLOCK()   ASM_DELAY(QUARTER_BIT_TIME - I2C_BB_TIMER_ADJUST)
#define WRITE_SCL_LO()    \
    do { \
        AM_REGVAL(am_hal_i2c_bit_bang_priv.sck_reg_clr_addr) = (am_hal_i2c_bit_bang_priv.sck_reg_val); \
    } while(0)

#define PULL_SCL_HI()    \
    do { \
        AM_REGVAL(am_hal_i2c_bit_bang_priv.sck_reg_set_addr) = (am_hal_i2c_bit_bang_priv.sck_reg_val); \
    } while(0)

#define GET_SCL()   (AM_REGVAL(am_hal_i2c_bit_bang_priv.sck_reg_read_addr) & (am_hal_i2c_bit_bang_priv.sck_reg_val))
#define GET_SDA()   (AM_REGVAL(am_hal_i2c_bit_bang_priv.sda_reg_read_addr) & (am_hal_i2c_bit_bang_priv.sda_reg_val))

#define WRITE_SDA_LO()    \
    do { \
        AM_REGVAL(am_hal_i2c_bit_bang_priv.sda_reg_clr_addr) = (am_hal_i2c_bit_bang_priv.sda_reg_val); \
    } while(0)

#define PULL_SDA_HI()    \
    do { \
        AM_REGVAL(am_hal_i2c_bit_bang_priv.sda_reg_set_addr) = (am_hal_i2c_bit_bang_priv.sda_reg_val); \
    } while(0)


//*****************************************************************************
//
// I2C Bit Bang Private Data Structure
//
//*****************************************************************************
typedef struct am_util_bit_bang_priv
{
    bool  start_flag;
    uint32_t sck_gpio_number;
    uint32_t sda_gpio_number;
    uint32_t sck_reg_set_addr;
    uint32_t sck_reg_clr_addr;
    uint32_t sck_reg_read_addr;
    uint32_t sck_reg_val;
    uint32_t sda_reg_set_addr;
    uint32_t sda_reg_clr_addr;
    uint32_t sda_reg_read_addr;
    uint32_t sda_reg_val;
} am_hal_i2c_bit_bang_priv_t;
static am_hal_i2c_bit_bang_priv_t am_hal_i2c_bit_bang_priv;

//
// Wait for any stretched clock to go high
// If it times out - return failure
//
static __inline bool
i2c_pull_and_wait_scl_hi(void)
{
    // Maximum time to wait for clock stretching
    uint32_t maxLoop = 4*I2C_BB_MAX_CLOCK_STRETCH_WAIT + 1;
    // Pull SCL High
    PULL_SCL_HI();
    // Poll for SCL to check for clock stretching
    while (!GET_SCL())
    {
        if (--maxLoop == 0)
        {
            // timeout!
            return true;
        }
        WAIT_FOR_QUARTER_I2C_CLOCK();
    }
    return false;
}

//*****************************************************************************
//
//! @brief Initialize i2c bit bang private data structure
//!
//! @param sck_gpio_number is the GPIO # for the I2C SCK clock pin
//! @param sda_gpio_number is the GPIO # for the I2C SDA data pin
//!
//! This function initializes the I2C bit bang utility's internal data struct.
//!
//! returns None.
//
//*****************************************************************************
am_hal_i2c_bit_bang_enum_e
am_hal_i2c_bit_bang_init(uint32_t sck_gpio_number,
                         uint32_t sda_gpio_number)
{
    int i;
    //
    // remember GPIO pin assignments for I2C bus signals
    //
    am_hal_i2c_bit_bang_priv.sck_gpio_number = sck_gpio_number;
    am_hal_i2c_bit_bang_priv.sda_gpio_number = sda_gpio_number;

    am_hal_i2c_bit_bang_priv.sck_reg_set_addr = AM_HAL_GPIO_WTS_REG(sck_gpio_number);
    am_hal_i2c_bit_bang_priv.sck_reg_clr_addr = AM_HAL_GPIO_WTC_REG(sck_gpio_number);
    am_hal_i2c_bit_bang_priv.sck_reg_read_addr = AM_HAL_GPIO_RD_REG(sck_gpio_number);
    am_hal_i2c_bit_bang_priv.sck_reg_val = AM_HAL_GPIO_WTC_M(sck_gpio_number);
    am_hal_i2c_bit_bang_priv.sda_reg_set_addr = AM_HAL_GPIO_WTS_REG(sda_gpio_number);
    am_hal_i2c_bit_bang_priv.sda_reg_clr_addr = AM_HAL_GPIO_WTC_REG(sda_gpio_number);
    am_hal_i2c_bit_bang_priv.sda_reg_read_addr = AM_HAL_GPIO_RD_REG(sda_gpio_number);
    am_hal_i2c_bit_bang_priv.sda_reg_val =  AM_HAL_GPIO_WTC_M(sda_gpio_number);

    //
    // Set SCK GPIO data bit high so we aren't pulling down the clock
    //
    am_hal_gpio_out_bit_set(sck_gpio_number);
    //
    // Set up SCK GPIO configuration bi-direction, input
    //
    am_hal_gpio_pin_config(sck_gpio_number, AM_HAL_PIN_OPENDRAIN | AM_HAL_GPIO_INPEN);

    //
    // Set SDA GPIO data bit high so we aren't pulling down the data line
    //
    am_hal_gpio_out_bit_set(sda_gpio_number);
    //
    // Set up SDA GPIO configuration bi-direction, input
    //
    am_hal_gpio_pin_config(sda_gpio_number, AM_HAL_PIN_OPENDRAIN | AM_HAL_GPIO_INPEN);

    // Now make sure we have control of the clock line
    //
    // Wait for any stretched clock to go high. Return if still not high
    //
    if (i2c_pull_and_wait_scl_hi())
    {
        return AM_HAL_I2C_BIT_BANG_CLOCK_TIMEOUT;
    }
    if (!GET_SDA())
    {
        // If previous transaction did not finish - SDA may be pulled low for a Read.
        // If so - need to flush out the data (max 8 bits) & NACK
        for (i = 0; i < 9; i++)
        {
            //
            // Pull down on clock line
            //
            WRITE_SCL_LO();
            //
            // Delay for 1/2 bit cell time to start the clock and let peer write on SDA
            //
            WAIT_I2C_CLOCK_LOW_PERIOD();
            if (i2c_pull_and_wait_scl_hi())
            {
                return AM_HAL_I2C_BIT_BANG_CLOCK_TIMEOUT;
            }
            if (GET_SDA())
            {
                // Send START/STOP to clear the bus
                //
                // Delay for 1/4 bit cell time
                //
                WAIT_FOR_QUARTER_I2C_CLOCK();
                WRITE_SDA_LO();
                //
                // Delay for 1/4 bit cell time
                //
                WAIT_FOR_QUARTER_I2C_CLOCK();
                //
                // Pull down on clock line
                //
                WRITE_SCL_LO();
                //
                // Delay for 1/2 bit cell time to start the clock and let peer write on SDA
                //
                WAIT_I2C_CLOCK_LOW_PERIOD();
                //
                // Release the clock line
                //
                PULL_SCL_HI();
                //
                // Delay for 1/4 bit cell time
                //
                WAIT_FOR_QUARTER_I2C_CLOCK();
                PULL_SDA_HI();
                //
                // Delay for 1/4 bit cell time
                //
                WAIT_FOR_QUARTER_I2C_CLOCK();
                break;
            }
        }
        if (i == 9)
        {
            // It is it still stuck after 9 clocks - something is wrong. Need to bail out
            return AM_HAL_I2C_BIT_BANG_DATA_TIMEOUT;
        }
    }
    return AM_HAL_I2C_BIT_BANG_SUCCESS;
}

//*****************************************************************************
//
//! @brief Receive one data byte from an I2C device
//!
//! This function handles sending one byte to a slave device
//! bNack defines if we should send an ACK or NACK
//!
//! returns the byte received
//
//*****************************************************************************
static __inline am_hal_i2c_bit_bang_enum_e
i2c_receive_byte(uint8_t *pRxByte, bool bNack)
{
    int i;
    uint8_t data_byte = 0;

    //
    // Loop through receiving 8 bits
    //
    for (i = 0; i < 8; i++)
    {
        //
        // Pull down on clock line
        //
        WRITE_SCL_LO();

        //
        // release the data line from from the previous ACK
        //
        PULL_SDA_HI();

        //
        // Delay for 1/2 bit cell time to start the clock and let peer write on SDA
        //
        WAIT_I2C_CLOCK_LOW_PERIOD();

        if (i2c_pull_and_wait_scl_hi())
        {
            return AM_HAL_I2C_BIT_BANG_CLOCK_TIMEOUT;
        }
        //
        // grab the data bit here
        //
        if ( GET_SDA() )
        {
            //
            // set the bit in the data byte to be returned
            //
            data_byte |=  (0x80 >> i);
        }

        //
        // Delay for 1/2 bit cell time while clock is high
        //
        WAIT_I2C_CLOCK_HI_PERIOD();
    }

    *pRxByte = data_byte;
    //
    // Pull down on clock line
    //
    WRITE_SCL_LO();

    //
    // pull the data line down so we can ACK/NAK the byte we just received
    //
    if (bNack)
    {
        //
        // Pull up on data line with clock low to indicate NAK
        //
        PULL_SDA_HI();
    }
    else
    {
        //
        // Pull down on data line with clock low to indicate ACK
        //
        WRITE_SDA_LO();
    }
    //
    // Delay for 1/2 bit cell time before sending ACK to device
    //
    WAIT_I2C_CLOCK_LOW_PERIOD();

    if (i2c_pull_and_wait_scl_hi())
    {
        return AM_HAL_I2C_BIT_BANG_CLOCK_TIMEOUT;
    }
    //
    // Delay for 1/2 bit cell time while clock is high to le peer sample the ACK/NAK
    //
    WAIT_I2C_CLOCK_HI_PERIOD();
    //
    // Give the received data byte back to them
    //
    return AM_HAL_I2C_BIT_BANG_SUCCESS;
}

//*****************************************************************************
//
//! @brief Send one data bytes to an I2C device
//!
//! @param one_byte the byte to send, could be address could be data
//!
//! This function handles sending one byte to a slave device
//! Starts with 0 clock and runs till full cycle
//!
//! returns I2C BB ENUM
//!     {
//!     AM_HAL_I2C_BIT_BANG_SUCCESS,
//!     AM_HAL_I2C_BIT_BANG_ADDRESS_NAKED
//!     }
//
//*****************************************************************************
static __inline am_hal_i2c_bit_bang_enum_e
i2c_send_byte(uint8_t one_byte)
{
    int i;
    bool data_naked = false;

    //
    // Loop through sending 8 bits
    //
    for (i = 0; i < 8; i++)
    {
        //
        // Pull down on clock line
        //
        WRITE_SCL_LO();

        //
        // output the next data bit
        //
        if ( one_byte & (0x80 >> i) )
        {
            PULL_SDA_HI();
        }
        else
        {
            WRITE_SDA_LO();
        }

        //
        // Delay for 1/2 bit cell time to start the clock
        //
        WAIT_I2C_CLOCK_LOW_PERIOD();

        if (i2c_pull_and_wait_scl_hi())
        {
            return AM_HAL_I2C_BIT_BANG_CLOCK_TIMEOUT;
        }
        //
        // Delay for 1/2 bit cell time while clock is high
        //
        WAIT_I2C_CLOCK_HI_PERIOD();
    }

    //
    // Pull down on clock line
    //
    WRITE_SCL_LO();

    //
    // Delay for 1/2 bit cell time to start the clock
    //
    WAIT_I2C_CLOCK_LOW_PERIOD();

    if (i2c_pull_and_wait_scl_hi())
    {
        return AM_HAL_I2C_BIT_BANG_CLOCK_TIMEOUT;
    }
    //
    // Grab the state of the ACK bit and return it
    //
    data_naked = GET_SDA();
    //
    // Delay for 1/2 bit cell time to complete the high period
    //
    WAIT_I2C_CLOCK_HI_PERIOD();
    if ( data_naked )
    {
        return AM_HAL_I2C_BIT_BANG_DATA_NAKED;
    }
    else
    {
        return AM_HAL_I2C_BIT_BANG_SUCCESS;
    }
}

//*****************************************************************************
//
//! @brief Receive a string of data bytes from an I2C device
//!
//! @param address (only 8 bit I2C addresses are supported)
//!        LSB is I2C R/W
//! @param number_of_bytes to transfer (# payload bytes)
//! @param pData pointer to data buffer to receive payload
//!
//! This function handles receiving a payload from a slave device
//!
//! returns ENUM{AM_HAL_I2C_BIT_BANG_SUCCESS,AM_HAL_I2C_BIT_BANG_ADDRESS_NAKED}
//
//*****************************************************************************
am_hal_i2c_bit_bang_enum_e
am_hal_i2c_bit_bang_receive(uint8_t address, uint32_t number_of_bytes,
                            uint8_t *pData, uint8_t ui8Offset,
                            bool bUseOffset, bool bNoStop)
{
    uint32_t ui32I;
    am_hal_i2c_bit_bang_enum_e status = AM_HAL_I2C_BIT_BANG_SUCCESS;


    if (i2c_pull_and_wait_scl_hi())
    {
        return AM_HAL_I2C_BIT_BANG_CLOCK_TIMEOUT;
    }
    //
    // Pull down on data line with clock high --> START CONDITION
    //
    WRITE_SDA_LO();

    //
    // Delay for 1/2 bit cell time to start the clock
    //
    WAIT_I2C_CLOCK_HI_PERIOD();

    //
    // send the address byte and wait for the ACK/NAK
    //
    status = i2c_send_byte(address);
    if ( status != AM_HAL_I2C_BIT_BANG_SUCCESS )
    {
        if ( status == AM_HAL_I2C_BIT_BANG_DATA_NAKED)
        {
            return AM_HAL_I2C_BIT_BANG_ADDRESS_NAKED;
        }
        return status;
    }

    if ( bUseOffset )
    {
        status = i2c_send_byte(ui8Offset);
        if ( status != AM_HAL_I2C_BIT_BANG_SUCCESS )
        {
            return status;
        }
    }

    //
    // receive the requested number of data bytes
    //
    for (ui32I = 0; ui32I < number_of_bytes - 1; ui32I++)
    {
        //
        // receive the data bytes and send ACK for each one
        //
        status = i2c_receive_byte(pData, false);
        if (status != AM_HAL_I2C_BIT_BANG_SUCCESS)
        {
            return status;
        }
        pData++;
    }
    // Send NAK for the last byte
    status = i2c_receive_byte(pData, true);
    if (status != AM_HAL_I2C_BIT_BANG_SUCCESS)
    {
        return status;
    }

    //********************
    // Send stop condition
    //********************
    //
    // Pull down on clock line
    //
    WRITE_SCL_LO();

    //
    // Delay for 1/4 bit cell time
    //
    WAIT_FOR_QUARTER_I2C_CLOCK();


    if (!bNoStop)
    {
        //
        // Pull down on data line with clock low
        //
        WRITE_SDA_LO();
    }
    else
    {
        //
        // Release data line with clock low itself, as we are not sending STOP
        //
        PULL_SDA_HI();
    }
    //
    //
    // Delay for 1/4 bit cell time
    //
    WAIT_FOR_QUARTER_I2C_CLOCK();

    if (i2c_pull_and_wait_scl_hi())
    {
        return AM_HAL_I2C_BIT_BANG_CLOCK_TIMEOUT;
    }
    //
    // Delay for 1/2 bit cell time while clock is high
    //
    WAIT_I2C_CLOCK_HI_PERIOD();

    if (!bNoStop)
    {
        //
        // release data line with clock high --> STOP CONDITION
        //
        PULL_SDA_HI();
    }

    //
    // message successfully received (how could we fail???)
    //
    return AM_HAL_I2C_BIT_BANG_SUCCESS;
}

//*****************************************************************************
//
//! @brief Send a string of data bytes to an I2C device
//!
//! @param address (only 8 bit I2C addresses are supported)
//!        LSB is I2C R/W
//! @param number_of_bytes to transfer (# payload bytes)
//! @param pData pointer to data buffer containing payload
//!
//! This function handles sending a payload to a slave device
//!
//! returns ENUM {AM_HAL_I2C_BIT_BANG_SUCCESS, AM_HAL_I2C_BIT_BANG_DATA_NAKED,
//!               AM_HAL_I2C_BIT_BANG_ADDRESS_NAKED}
//
//*****************************************************************************
am_hal_i2c_bit_bang_enum_e
am_hal_i2c_bit_bang_send(uint8_t address, uint32_t number_of_bytes,
                         uint8_t *pData, uint8_t ui8Offset,
                         bool bUseOffset, bool bNoStop)
{
    uint32_t ui32I;
    am_hal_i2c_bit_bang_enum_e status;
    bool data_naked = false;

    if (i2c_pull_and_wait_scl_hi())
    {
        return AM_HAL_I2C_BIT_BANG_CLOCK_TIMEOUT;
    }
    //
    // Pull down on data line with clock high --> START CONDITION
    //
    WRITE_SDA_LO();

    //
    // Delay for 1/2 bit cell time to start the clock
    //
    WAIT_I2C_CLOCK_HI_PERIOD();

    //
    // send the address byte and wait for the ACK/NAK
    //
    status = i2c_send_byte(address);
    if ( status != AM_HAL_I2C_BIT_BANG_SUCCESS )
    {
        if ( status == AM_HAL_I2C_BIT_BANG_DATA_NAKED)
        {
            return AM_HAL_I2C_BIT_BANG_ADDRESS_NAKED;
        }
        return status;
    }

    if ( bUseOffset )
    {
        status = i2c_send_byte(ui8Offset);
        if ( status != AM_HAL_I2C_BIT_BANG_SUCCESS )
        {
            return status;
        }
    }

    //
    // send the requested number of data bytes
    //
    for (ui32I = 0; ui32I < number_of_bytes; ui32I++)
    {
        //
        // send out the data bytes while watching for premature NAK
        //
        status =  i2c_send_byte(*pData++);
        if (status != AM_HAL_I2C_BIT_BANG_SUCCESS)
        {
            if (status == AM_HAL_I2C_BIT_BANG_DATA_NAKED)
            {
                if (ui32I != (number_of_bytes-1))
                {
                    data_naked = true;
                    // TODO - should we be sending the STOP bit in this case regardless of bNoStop?
                    break;
                }
                else
                {
                    status = AM_HAL_I2C_BIT_BANG_SUCCESS;
                }
            }
            else
            {
                return status;
            }
        }
    }

    //********************
    // Send stop condition
    //********************

    //
    // Pull down on clock line
    //
    WRITE_SCL_LO();

    //
    // Delay for 1/4 bit cell time
    //
    WAIT_FOR_QUARTER_I2C_CLOCK();


    if (!bNoStop)
    {
        //
        // Pull down on data line with clock low
        //
        WRITE_SDA_LO();
    }
    else
    {
        //
        // Release data line with clock low itself, as we are not sending STOP
        //
        PULL_SDA_HI();
    }

    //
    // Delay for 1/4 bit cell time
    //
    WAIT_FOR_QUARTER_I2C_CLOCK();

    if (i2c_pull_and_wait_scl_hi())
    {
        return AM_HAL_I2C_BIT_BANG_CLOCK_TIMEOUT;
    }
    if (!bNoStop)
    {
        //
        // release data line with clock high --> STOP CONDITION
        //
        PULL_SDA_HI();
    }

    //
    // Delay for 1/2 bit cell time while clock is high
    //
    WAIT_I2C_CLOCK_HI_PERIOD();

    if ( data_naked )
    {
        return AM_HAL_I2C_BIT_BANG_DATA_NAKED;  // if it happens early
    }

    //
    // message successfully sent
    //
    return AM_HAL_I2C_BIT_BANG_SUCCESS;
}
