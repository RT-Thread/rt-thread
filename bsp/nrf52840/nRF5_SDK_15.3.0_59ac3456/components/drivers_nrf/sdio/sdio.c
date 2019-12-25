/**
 * Copyright (c) 2009 - 2019, Nordic Semiconductor ASA
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
#include <stdint.h>

#include "nrf.h"
#include "nrf_delay.h"
#include "sdio.h"
#include "nrf_gpio.h"

#include "sdio_config.h"

/*lint ++flb "Enter library region" */

/*lint -e717 -save "Suppress do {} while (0) for these macros" */
#define SDIO_CLOCK_HIGH()   do { NRF_GPIO->OUTSET = (1UL << SDIO_CONFIG_CLOCK_PIN_NUMBER); } while (0) /*!< Pulls SCL line high */
#define SDIO_CLOCK_LOW()    do { NRF_GPIO->OUTCLR = (1UL << SDIO_CONFIG_CLOCK_PIN_NUMBER); } while (0) /*!< Pulls SCL line low */
#define SDIO_DATA_HIGH()    do { NRF_GPIO->OUTSET = (1UL << SDIO_CONFIG_DATA_PIN_NUMBER); } while (0)  /*!< Pulls SDA line high */
#define SDIO_DATA_LOW()     do { NRF_GPIO->OUTCLR = (1UL << SDIO_CONFIG_DATA_PIN_NUMBER); } while (0)  /*!< Pulls SDA line low */
#define SDIO_DATA_OUTPUT()  do { NRF_GPIO->DIRSET = (1UL << SDIO_CONFIG_DATA_PIN_NUMBER); } while (0)  /*!< Configures SDA pin as output */
#define SDIO_CLOCK_OUTPUT() do { NRF_GPIO->DIRSET = (1UL << SDIO_CONFIG_CLOCK_PIN_NUMBER); } while (0) /*!< Configures SCL pin as output */
/*lint -restore */

/*lint -emacro(845,SDIO_DATA_INPUT) // A zero has been given as right argument to operator '|'" */

#define SDIO_DATA_INPUT() do {                       \
        nrf_gpio_cfg_input(25, NRF_GPIO_PIN_NOPULL); \
} while (0)

#define SDIO_DATA_READ()  ((NRF_GPIO->IN >> SDIO_CONFIG_DATA_PIN_NUMBER) & 0x1UL)  /*!< Reads current state of SDA */
#define SDIO_CLOCK_READ() ((NRF_GPIO->IN >> SDIO_CONFIG_CLOCK_PIN_NUMBER) & 0x1UL) /*!< Reads current state of SCL */
#define SDIO_DELAY()      nrf_delay_us(10)                                         /*!< Time to wait when pin states are changed. For fast-mode the delay can be zero and for standard-mode 4 us delay is sufficient. */

void sdio_init(void)
{
    SDIO_CLOCK_HIGH();
    SDIO_DATA_HIGH();
    SDIO_CLOCK_OUTPUT();
    SDIO_DATA_INPUT();

    // If slave is stuck in the middle of transfer, clock out bits until the slave ACKs the transfer
    for (uint_fast8_t i = 16; i--;)
    {
        SDIO_DELAY();
        SDIO_CLOCK_LOW();
        SDIO_DELAY();
        SDIO_CLOCK_HIGH();
        SDIO_DELAY();

        if (SDIO_DATA_READ())
        {
            break;
        }
    }

    for (uint_fast8_t i = 5; i--;)
    {
        SDIO_DELAY();
        SDIO_CLOCK_LOW();
        SDIO_DELAY();
        SDIO_CLOCK_HIGH();
    }

    SDIO_DATA_OUTPUT();
    SDIO_DATA_HIGH();

    SDIO_DELAY();
}

uint8_t sdio_read_byte(uint8_t address)
{
    uint8_t data_byte = 0;

    SDIO_DATA_OUTPUT();

    for (uint_fast8_t i = 8; i--;)
    {
        SDIO_DELAY();

        SDIO_CLOCK_LOW();

        if (address & (1U << i))
        {
            SDIO_DATA_HIGH();
        }
        else
        {
            SDIO_DATA_LOW();
        }

        SDIO_DELAY();

        SDIO_CLOCK_HIGH();
    }

    nrf_delay_us(20);

    SDIO_DATA_INPUT();

    for (uint_fast8_t i = 8; i--;)
    {
        SDIO_CLOCK_LOW();
        SDIO_DELAY();
        SDIO_CLOCK_HIGH();
        SDIO_DELAY();
        data_byte |= (uint8_t)(SDIO_DATA_READ() << i);
    }

    SDIO_DATA_HIGH();
    SDIO_DATA_OUTPUT();

    SDIO_DELAY();

    return data_byte;
}

void sdio_read_burst(uint8_t * target_buffer, uint8_t target_buffer_size)
{
    uint_fast8_t address = 0x63;

    SDIO_DATA_OUTPUT();

    for (uint_fast8_t bit_index=8; bit_index--;)
    {
        SDIO_CLOCK_LOW();

        if (address & (1U << bit_index))
        {
            SDIO_DATA_HIGH();
        }
        else
        {
            SDIO_DATA_LOW();
        }

        SDIO_CLOCK_HIGH();
    }

    SDIO_DATA_INPUT();

    for (uint_fast8_t target_buffer_index = 0; target_buffer_index < target_buffer_size; target_buffer_index++)
    {
        target_buffer[target_buffer_index] = 0;

        for (uint_fast8_t bit_index = 8; bit_index--;)
        {
            SDIO_CLOCK_LOW();
            SDIO_CLOCK_HIGH();
            target_buffer[target_buffer_index] |= (uint8_t)(SDIO_DATA_READ() << bit_index);
        }
    }
}

void sdio_write_byte(uint8_t address, uint8_t data_byte)
{
    // Add write indication bit
    address |= 0x80;

    SDIO_DATA_OUTPUT();

    for (uint_fast8_t i = 8; i--;)
    {
        SDIO_DELAY();

        SDIO_CLOCK_LOW();

        if (address & (1U << i))
        {
            SDIO_DATA_HIGH();
        }
        else
        {
            SDIO_DATA_LOW();
        }

        SDIO_DELAY();

        SDIO_CLOCK_HIGH();
    }

    SDIO_DELAY();

    for (uint_fast8_t i = 8; i--;)
    {
        SDIO_CLOCK_LOW();

        if (data_byte & (1U << i))
        {
            SDIO_DATA_HIGH();
        }
        else
        {
            SDIO_DATA_LOW();
        }

        SDIO_DELAY();

        SDIO_CLOCK_HIGH();

        SDIO_DELAY();
    }

    SDIO_DATA_HIGH();

    SDIO_DELAY();
}

/*lint --flb "Leave library region" */
