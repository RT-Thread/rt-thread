/**
 * Copyright (c) 2008 - 2018, Nordic Semiconductor ASA
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
#include "nrf6350.h"
#include "nrf_delay.h"
#include "twi_master.h"

/*lint ++flb "Enter library region" */

#define DDRAM_ADR 0x80      //!< Write to DDRAM AC
#define DDRAM_WR  0x40      //!< Write to DDRAM
#define FUNC_SET  0x00      //!< Enter LCD Function settings
#define LCD_ADDR  0x3E      //!< LCD display adr
#define JS_ADDR   0x3F      //!< Joystick adr

#define X 0                 //!< X direction in pos 0 of joystick array
#define Y 1                 //!< Y direction in pos 1 of joystick array


//static void nrf6350_nrf6350_lcd_set_instruction(uint8_t instr);

#define BUF_LEN 32                   //!< LCD data buffer length
static uint8_t data_buffer[BUF_LEN]; //!<  LCD data buffer
static uint8_t empty_str[18] = {DDRAM_WR, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; //!<  Blank line


static bool nrf6350_lcd_set_instruction(uint8_t instr)
{
    nrf_delay_us(10000);
    data_buffer[0] = FUNC_SET;
    data_buffer[1] = instr;
    return twi_master_transfer(LCD_ADDR << 1, data_buffer, 2, TWI_ISSUE_STOP);
}

bool nrf6350_lcd_clear(void)
{
    nrf_delay_us(10000);
    data_buffer[0] = FUNC_SET;
    data_buffer[1] = (uint8_t)(DDRAM_ADR + LCD_UPPER_LINE);
    if (!twi_master_transfer(LCD_ADDR << 1, data_buffer, 2, TWI_ISSUE_STOP))
        return false;
    if (!twi_master_transfer(LCD_ADDR << 1, empty_str, 18, TWI_ISSUE_STOP))
    {
        return false;
    }
    data_buffer[1] = DDRAM_ADR + LCD_LOWER_LINE;
    if (!twi_master_transfer(LCD_ADDR << 1, data_buffer, 2, TWI_ISSUE_STOP))
        return false;
    if (!twi_master_transfer(LCD_ADDR << 1, empty_str, 18, TWI_ISSUE_STOP))
        return false;
    return true;
}

bool nrf6350_lcd_set_contrast(uint8_t contrast)
{
    nrf_delay_us(10000);
    data_buffer[0] = FUNC_SET;
    data_buffer[1] = 0x70 | contrast;
    return twi_master_transfer(LCD_ADDR << 1, data_buffer, 2, TWI_ISSUE_STOP);
}

bool nrf6350_lcd_on(void)
{
    nrf_delay_us(10000);
    data_buffer[0] = FUNC_SET;
    data_buffer[1] = 0x0C;
    return twi_master_transfer(LCD_ADDR << 1, data_buffer, 2, TWI_ISSUE_STOP);
}

bool nrf6350_lcd_off(void)
{
    nrf_delay_us(10000);
    data_buffer[0] = FUNC_SET;
    data_buffer[1] = 0x08;
    return twi_master_transfer(LCD_ADDR << 1, data_buffer, 2, TWI_ISSUE_STOP);
}

bool nrf6350_lcd_init(void)
{
    if (!twi_master_init())
    {
        return false;
    }

    // Sometimes the first command doesn't get through, so we'll try
    // sending non-important "wake up" command first and don't care if it fails.
    (void)nrf6350_lcd_wake_up();

    if (!nrf6350_lcd_set_instruction(0x38)) // Function set.
        return false;
    if (!nrf6350_lcd_set_instruction(0x39))                 // Choose two-line mode.
        return false;
    if (!nrf6350_lcd_set_instruction(0x14))                 // Internal OSC frequency.
        return false;
    if (!nrf6350_lcd_set_contrast(LCD_CONTRAST_HIGH))       // Contrast set (low byte).
        return false;
    if (!nrf6350_lcd_set_instruction(0x5F))                 // Power/ICON control/.
        return false;
    if (!nrf6350_lcd_set_instruction(0x6A))                 // Follower control.
        return false;
    nrf_delay_us(200000);                                   // Need to wait 200ms here according to datasheet.
    if (!nrf6350_lcd_on())                                  // Display ON.
        return false;
    if (!nrf6350_lcd_clear())                               // Clear display.
        return false;
    return nrf6350_lcd_set_instruction(0x06);               // Entry mode set.
}

bool nrf6350_lcd_write_string(const char *p_text, uint8_t size, uint8_t line, uint8_t pos)
{
    uint8_t i;

    data_buffer[0] = FUNC_SET;
    data_buffer[1] = DDRAM_ADR + (pos + line);
    if (!twi_master_transfer(LCD_ADDR << 1, data_buffer, 2, TWI_ISSUE_STOP))
        return false;
    if (!twi_master_transfer(LCD_ADDR << 1, empty_str, 18 - pos, TWI_ISSUE_STOP))
        return false;
    data_buffer[0] = FUNC_SET;
    data_buffer[1] = DDRAM_ADR + (pos + line);
    if (!twi_master_transfer(LCD_ADDR << 1, data_buffer, 2, TWI_ISSUE_STOP))
        return false;
    data_buffer[0] = DDRAM_WR;
    for (i=0;i<size;i++)
    {
        if (i == LCD_LLEN)
            break;
        data_buffer[i + 1] = (uint8_t) * p_text++;
    }
    return twi_master_transfer(LCD_ADDR << 1, data_buffer, i + 1, TWI_ISSUE_STOP);
}

bool  nrf6350_js_get_value(int8_t * val)
{
    uint8_t js_data;

    if (!twi_master_transfer(JS_ADDR << 1 | TWI_READ_BIT, data_buffer, 1, TWI_ISSUE_STOP))
        return false;
    js_data = (~data_buffer[0] & 0x1D); // Select the useful bits.

    if ((js_data & 0x01) != 0) // Check joystick position.
    {
        val[X] = -1;
    }
    else if ((js_data & 0x10) != 0)
    {
        val[X] = 1;
    }
    else
    {
        val[X] = 0;
    }

    if ((js_data & 0x04) != 0)
    {
        val[Y] = 1;
    }
    else if ((js_data & 0x08) != 0)
    {
        val[Y] = -1;
    }
    else
    {
        val[Y] = 0;
    }
    return true;
}


bool nrf6350_js_get_status(uint8_t * js_state)
{
    uint8_t js_data;

    if (!twi_master_transfer(JS_ADDR << 1 | TWI_READ_BIT, &js_data, 1, TWI_ISSUE_STOP))
    {
        return false;
    }
    js_data   = ~js_data;
    *js_state = js_data & 0x1F;
    return true;
}

/** @brief  First time communication with the development kit nRF6350 display will fail, this
 *          returns false on timeout instead of attempting to recover.
 */
static bool nrf6350_lcd_write_without_recovery(uint8_t * data,
                                               uint8_t   data_length,
                                               bool      issue_stop_condition)
{
    uint32_t timeout = 20000; /* max loops to wait for EVENTS_TXDSENT event*/

    if (data_length == 0)
    {
        /* Return false for requesting data of size 0 */
        return false;
    }

    NRF_TWI1->TXD           = *data++;
    NRF_TWI1->TASKS_STARTTX = 1;

    /** @snippet [TWI HW master write] */
    while (true)
    {
        while (NRF_TWI1->EVENTS_TXDSENT == 0 && (--timeout))
        {
            // Do nothing.
        }

        if (timeout == 0)
        {
            NRF_TWI1->EVENTS_STOPPED = 0;
            NRF_TWI1->TASKS_STOP     = 1;

            /* Wait until stop sequence is sent */
            while (NRF_TWI1->EVENTS_STOPPED == 0)
            {
                // Do nothing.
            }

            /* Timeout before receiving event*/
            return false;
        }

        NRF_TWI1->EVENTS_TXDSENT = 0;
        if (--data_length == 0)
        {
            break;
        }

        NRF_TWI1->TXD = *data++;
    }
    /** @snippet [TWI HW master write] */

    if (issue_stop_condition)
    {
        NRF_TWI1->EVENTS_STOPPED = 0;
        NRF_TWI1->TASKS_STOP     = 1;

        /* Wait until stop sequence is sent */
        while (NRF_TWI1->EVENTS_STOPPED == 0)
        {
            // Do nothing.
        }
    }
    return true;
}

/** @brief  Function for transfer by twi_master.
 */
bool nrf6350_lcd_wake_up(void)
{
    uint8_t address              = (LCD_ADDR << 1);
    uint8_t dummy_data[]         = {0, 0, 0, 0};
    uint8_t dummy_data_length    = 4;
    bool    issue_stop_condition = 0;
    bool    transfer_succeeded   = false;

    NRF_TWI1->ADDRESS = (address >> 1);

    transfer_succeeded = nrf6350_lcd_write_without_recovery(dummy_data,
                                                            dummy_data_length,
                                                            issue_stop_condition);

    NRF_TWI1->EVENTS_ERROR = 0;

    return transfer_succeeded;
}

/*lint --flb "Leave library region" */
