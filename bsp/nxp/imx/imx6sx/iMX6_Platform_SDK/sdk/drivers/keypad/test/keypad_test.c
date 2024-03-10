/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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

#include <stdio.h>
#include "sdk.h"
#include "keypad_test.h"

void multiple_key_press_test(void);

/*!
 * @brief Main unit test for the Keypad.
 */
void keypad_test(void)
{
    uint8_t sel;

    printf("Start Keypad unit tests:");

    do {
        printf("\n  1 - Multiple keys pressed test.\n");
        printf("  x - to exit.\n\n");

        do {
            sel = getchar();
        } while (sel == (uint8_t) NONE_CHAR);

        if (sel == 'x') {
            printf("\nTest exit.\n");
            break;
        }

        if (sel == '1')
            multiple_key_press_test();

    } while(1);

    return;
}

/*!
 * A test that detects that multiple keys are pressed and waits for them
 * to release to print what are the keys.
 */
void multiple_key_press_test(void)
{
    uint8_t row, col, exit_test, kppcol, kpprow;
    uint16_t read_keys[8] = {0};

    // this is a 3x3 matrix - col[7:5] x row[7:5] 
    kppcol = kpprow = 0xF0;

    kpp_open(kppcol, kpprow);

    exit_test = 1;
    do
    {
        printf("Please press any key (SW19 to exit):\n");

        // get the first pressed key(s) 
        kpp_get_keypad_state(read_keys, false);

        /* a delay is required between 2 captures to detect that
         * multiple keys are pressed
         * It is too difficult for a user to push multiple keys within a single
         * capture of few micro seconds.
         * That delay and the number of captures should be adjusted per applications.
         */
        hal_delay_us(50000);

        // get the next pressed key(s) after half a second 
        kpp_get_keypad_state(read_keys, false);

        // wait for no key pressed 
        kpp_wait_for_release_state();

        for(col=0;col<8;col++)
        {
            if((read_keys[col] & 0xFF) != 0x00)
            {
                for(row=0;row<8;row++)
                {
                    if((read_keys[col] & (1 << row)) != 0)
                    {
                        printf("Key %s was pressed.\n",KEYPAD_MAP[row][col]);
                        // exit test if key on row=col=7 is pressed 
                        if((row & col) == 7)
                            exit_test = 0;
                    }
                }
            }
        }

    } while(exit_test);

    kpp_close();
}
