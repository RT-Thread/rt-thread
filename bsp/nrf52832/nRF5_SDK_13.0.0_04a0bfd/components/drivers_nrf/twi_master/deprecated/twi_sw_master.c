/**
 * Copyright (c) 2009 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#include <stdbool.h>
#include <stdint.h>
#include "twi_master.h"
#include "nrf_delay.h"

#include "twi_master_config.h"

/*lint -e415 -e845 -save "Out of bounds access" */
#define TWI_SDA_STANDARD0_NODRIVE1() do { \
        NRF_GPIO->PIN_CNF[TWI_MASTER_CONFIG_DATA_PIN_NUMBER] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
        |(GPIO_PIN_CNF_DRIVE_S0D1 << GPIO_PIN_CNF_DRIVE_Pos)    \
        |(GPIO_PIN_CNF_PULL_Pullup << GPIO_PIN_CNF_PULL_Pos)  \
        |(GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) \
        |(GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);  \
} while (0) /*!< Configures SDA pin to Standard-0, No-drive 1 */


#define TWI_SCL_STANDARD0_NODRIVE1() do { \
        NRF_GPIO->PIN_CNF[TWI_MASTER_CONFIG_CLOCK_PIN_NUMBER] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
        |(GPIO_PIN_CNF_DRIVE_S0D1 << GPIO_PIN_CNF_DRIVE_Pos)    \
        |(GPIO_PIN_CNF_PULL_Pullup << GPIO_PIN_CNF_PULL_Pos)  \
        |(GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) \
        |(GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);  \
} while (0) /*!< Configures SCL pin to Standard-0, No-drive 1 */


/*lint -restore */

#ifndef TWI_MASTER_TIMEOUT_COUNTER_LOAD_VALUE
#define TWI_MASTER_TIMEOUT_COUNTER_LOAD_VALUE (0UL) //!< Unit is number of empty loops. Timeout for SMBus devices is 35 ms. Set to zero to disable slave timeout altogether.
#endif

static bool twi_master_clear_bus(void);
static bool twi_master_issue_startcondition(void);
static bool twi_master_issue_stopcondition(void);
static bool twi_master_clock_byte(uint_fast8_t databyte);
static bool twi_master_clock_byte_in(uint8_t * databyte, bool ack);
static bool twi_master_wait_while_scl_low(void);

bool twi_master_init(void)
{
    // Configure both pins to output Standard 0, No-drive (open-drain) 1
    TWI_SDA_STANDARD0_NODRIVE1(); /*lint !e416 "Creation of out of bounds pointer" */
    TWI_SCL_STANDARD0_NODRIVE1(); /*lint !e416 "Creation of out of bounds pointer" */

    // Configure SCL as output
    TWI_SCL_HIGH();
    TWI_SCL_OUTPUT();

    // Configure SDA as output
    TWI_SDA_HIGH();
    TWI_SDA_OUTPUT();

    return twi_master_clear_bus();
}

bool twi_master_transfer(uint8_t address, uint8_t * data, uint8_t data_length, bool issue_stop_condition)
{
    bool transfer_succeeded = true;

    transfer_succeeded &= twi_master_issue_startcondition();
    transfer_succeeded &= twi_master_clock_byte(address);

    if (address & TWI_READ_BIT)
    {
        /* Transfer direction is from Slave to Master */
        while (data_length-- && transfer_succeeded)
        {
            // To indicate to slave that we've finished transferring last data byte
            // we need to NACK the last transfer.
            if (data_length == 0)
            {
                transfer_succeeded &= twi_master_clock_byte_in(data, (bool)false);
            }
            else
            {
                transfer_succeeded &= twi_master_clock_byte_in(data, (bool)true);
            }
            data++;
        }
    }
    else
    {
        /* Transfer direction is from Master to Slave */
        while (data_length-- && transfer_succeeded)
        {
            transfer_succeeded &= twi_master_clock_byte(*data);
            data++;
        }
    }

    if (issue_stop_condition || !transfer_succeeded)
    {
        transfer_succeeded &= twi_master_issue_stopcondition();
    }

    return transfer_succeeded;
}

/**
 * @brief Function for detecting stuck slaves and tries to clear the bus.
 *
 * @return
 * @retval false Bus is stuck.
 * @retval true Bus is clear.
 */
static bool twi_master_clear_bus(void)
{
    bool bus_clear;

    TWI_SDA_HIGH();
    TWI_SCL_HIGH();
    TWI_DELAY();


    if (TWI_SDA_READ() == 1 && TWI_SCL_READ() == 1)
    {
        bus_clear = true;
    }
    else if (TWI_SCL_READ() == 1)
    {
        bus_clear = false;
        // Clock max 18 pulses worst case scenario(9 for master to send the rest of command and 9 for slave to respond) to SCL line and wait for SDA come high
        for (uint_fast8_t i = 18; i--;)
        {
            TWI_SCL_LOW();
            TWI_DELAY();
            TWI_SCL_HIGH();
            TWI_DELAY();

            if (TWI_SDA_READ() == 1)
            {
                bus_clear = true;
                break;
            }
        }
    }
    else
    {
        bus_clear = false;
    }

    return bus_clear;
}

/**
 * @brief Function for issuing TWI START condition to the bus.
 *
 * START condition is signaled by pulling SDA low while SCL is high. After this function SCL and SDA will be low.
 *
 * @return
 * @retval false Timeout detected
 * @retval true Clocking succeeded
 */
static bool twi_master_issue_startcondition(void)
{
#if 0
    if (TWI_SCL_READ() == 1 && TWI_SDA_READ() == 1)
    {
        // Pull SDA low
        TWI_SDA_LOW();
    }
    else if (TWI_SCL_READ() == 1 && TWI_SDA_READ() == 0)
    {
        // Issue Stop by pulling SDA high
        TWI_SDA_HIGH();
        TWI_DELAY();

        // Then Start by pulling SDA low
        TWI_SDA_LOW();
    }
    else if (TWI_SCL_READ() == 0 && TWI_SDA_READ() == 0)
    {
        // First pull SDA high
        TWI_SDA_HIGH();

        // Then SCL high
        if (!twi_master_wait_while_scl_low())
        {
            return false;
        }

        // Then SDA low
        TWI_SDA_LOW();
    }
    else if (TWI_SCL_READ() == 0 && TWI_SDA_READ() == 1)
    {
        // SCL high
        if (!twi_master_wait_while_scl_low())
        {
            return false;
        }

        // Then SDA low
        TWI_SDA_LOW();
    }

    TWI_DELAY();
    TWI_SCL_LOW();
#endif

    // Make sure both SDA and SCL are high before pulling SDA low.
    TWI_SDA_HIGH();
    TWI_DELAY();
    if (!twi_master_wait_while_scl_low())
    {
        return false;
    }

    TWI_SDA_LOW();
    TWI_DELAY();

    // Other module function expect SCL to be low
    TWI_SCL_LOW();
    TWI_DELAY();

    return true;
}

/**
 * @brief Function for issuing TWI STOP condition to the bus.
 *
 * STOP condition is signaled by pulling SDA high while SCL is high. After this function SDA and SCL will be high.
 *
 * @return
 * @retval false Timeout detected
 * @retval true Clocking succeeded
 */
static bool twi_master_issue_stopcondition(void)
{
#if 0
    if (TWI_SCL_READ() == 1 && TWI_SDA_READ() == 1)
    {
        // Issue start, then issue stop

        // Pull SDA low to issue START
        TWI_SDA_LOW();
        TWI_DELAY();

        // Pull SDA high while SCL is high to issue STOP
        TWI_SDA_HIGH();
    }
    else if (TWI_SCL_READ() == 1 && TWI_SDA_READ() == 0)
    {
        // Pull SDA high while SCL is high to issue STOP
        TWI_SDA_HIGH();
    }
    else if (TWI_SCL_READ() == 0 && TWI_SDA_READ() == 0)
    {
        if (!twi_master_wait_while_scl_low())
        {
            return false;
        }

        // Pull SDA high while SCL is high to issue STOP
        TWI_SDA_HIGH();
    }
    else if (TWI_SCL_READ() == 0 && TWI_SDA_READ() == 1)
    {
        TWI_SDA_LOW();
        TWI_DELAY();

        // SCL high
        if (!twi_master_wait_while_scl_low())
        {
            return false;
        }

        // Pull SDA high while SCL is high to issue STOP
        TWI_SDA_HIGH();
    }

    TWI_DELAY();
#endif

    TWI_SDA_LOW();
    TWI_DELAY();
    if (!twi_master_wait_while_scl_low())
    {
        return false;
    }

    TWI_SDA_HIGH();
    TWI_DELAY();

    return true;
}

/**
 * @brief Function for clocking one data byte out and reads slave acknowledgment.
 *
 * Can handle clock stretching.
 * After calling this function SCL is low and SDA low/high depending on the
 * value of LSB of the data byte.
 * SCL is expected to be output and low when entering this function.
 *
 * @param databyte Data byte to clock out.
 * @return
 * @retval true Slave acknowledged byte.
 * @retval false Timeout or slave didn't acknowledge byte.
 */
static bool twi_master_clock_byte(uint_fast8_t databyte)
{
    bool transfer_succeeded = true;

    /** @snippet [TWI SW master write] */
    // Make sure SDA is an output
    TWI_SDA_OUTPUT();

    // MSB first
    for (uint_fast8_t i = 0x80; i != 0; i >>= 1)
    {
        TWI_SCL_LOW();
        TWI_DELAY();

        if (databyte & i)
        {
            TWI_SDA_HIGH();
        }
        else
        {
            TWI_SDA_LOW();
        }

        if (!twi_master_wait_while_scl_low())
        {
            transfer_succeeded = false; // Timeout
            break;
        }
    }

    // Finish last data bit by pulling SCL low
    TWI_SCL_LOW();
    TWI_DELAY();

    /** @snippet [TWI SW master write] */

    // Configure TWI_SDA pin as input for receiving the ACK bit
    TWI_SDA_INPUT();

    // Give some time for the slave to load the ACK bit on the line
    TWI_DELAY();

    // Pull SCL high and wait a moment for SDA line to settle
    // Make sure slave is not stretching the clock
    transfer_succeeded &= twi_master_wait_while_scl_low();

    // Read ACK/NACK. NACK == 1, ACK == 0
    transfer_succeeded &= !(TWI_SDA_READ());

    // Finish ACK/NACK bit clock cycle and give slave a moment to release control
    // of the SDA line
    TWI_SCL_LOW();
    TWI_DELAY();

    // Configure TWI_SDA pin as output as other module functions expect that
    TWI_SDA_OUTPUT();

    return transfer_succeeded;
}


/**
 * @brief Function for clocking one data byte in and sends ACK/NACK bit.
 *
 * Can handle clock stretching.
 * SCL is expected to be output and low when entering this function.
 * After calling this function, SCL is high and SDA low/high depending if ACK/NACK was sent.
 *
 * @param databyte Data byte to clock out.
 * @param ack If true, send ACK. Otherwise send NACK.
 * @return
 * @retval true Byte read succesfully
 * @retval false Timeout detected
 */
static bool twi_master_clock_byte_in(uint8_t *databyte, bool ack)
{
    uint_fast8_t byte_read          = 0;
    bool         transfer_succeeded = true;

    /** @snippet [TWI SW master read] */
    // Make sure SDA is an input
    TWI_SDA_INPUT();

    // SCL state is guaranteed to be high here

    // MSB first
    for (uint_fast8_t i = 0x80; i != 0; i >>= 1)
    {
        if (!twi_master_wait_while_scl_low())
        {
            transfer_succeeded = false;
            break;
        }

        if (TWI_SDA_READ())
        {
            byte_read |= i;
        }
        else
        {
            // No need to do anything
        }

        TWI_SCL_LOW();
        TWI_DELAY();
    }

    // Make sure SDA is an output before we exit the function
    TWI_SDA_OUTPUT();
    /** @snippet [TWI SW master read] */

    *databyte = (uint8_t)byte_read;

    // Send ACK bit

    // SDA high == NACK, SDA low == ACK
    if (ack)
    {
        TWI_SDA_LOW();
    }
    else
    {
        TWI_SDA_HIGH();
    }

    // Let SDA line settle for a moment
    TWI_DELAY();

    // Drive SCL high to start ACK/NACK bit transfer
    // Wait until SCL is high, or timeout occurs
    if (!twi_master_wait_while_scl_low())
    {
        transfer_succeeded = false; // Timeout
    }

    // Finish ACK/NACK bit clock cycle and give slave a moment to react
    TWI_SCL_LOW();
    TWI_DELAY();

    return transfer_succeeded;
}


/**
 * @brief Function for pulling SCL high and waits until it is high or timeout occurs.
 *
 * SCL is expected to be output before entering this function.
 * @note If TWI_MASTER_TIMEOUT_COUNTER_LOAD_VALUE is set to zero, timeout functionality is not compiled in.
 * @return
 * @retval true SCL is now high.
 * @retval false Timeout occurred and SCL is still low.
 */
static bool twi_master_wait_while_scl_low(void)
{
#if TWI_MASTER_TIMEOUT_COUNTER_LOAD_VALUE != 0
    uint32_t volatile timeout_counter = TWI_MASTER_TIMEOUT_COUNTER_LOAD_VALUE;
#endif

    // Pull SCL high just in case if something left it low
    TWI_SCL_HIGH();
    TWI_DELAY();

    while (TWI_SCL_READ() == 0)
    {
        // If SCL is low, one of the slaves is busy and we must wait

#if TWI_MASTER_TIMEOUT_COUNTER_LOAD_VALUE != 0
        if (timeout_counter-- == 0)
        {
            // If timeout_detected, return false
            return false;
        }
#endif
    }

    return true;
}

/*lint --flb "Leave library region" */
