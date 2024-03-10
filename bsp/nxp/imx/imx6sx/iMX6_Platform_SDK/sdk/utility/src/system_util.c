/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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

/*!
 * @file  system_util.c
 * @brief The system utility functions for the environment.
 *
 * @ingroup diag_util
 */

#include <sys/stat.h>
#include <stdio.h>
#include "sdk.h"
#include "uart/imx_uart.h"
#include "text_color.h"
#include "registers/regsccm.h"
#include "core/cortex_a9.h"

//! Number of bytes to allocate at once while reading input strings.
#define INPUT_STRING_ALLOC_SIZE (64)

//! ASCII control characters.
enum
{
    kEscapeChar = 0x1b,
    kBackspaceChar = 0x08,
    kDeleteChar = 0x7f
};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

__attribute__ ((noreturn)) void _sys_exit(int32_t return_code)
{
    // Only go to sleep in release builds.
#if !DEBUG
    // just put system into WFI mode
    _ARM_WFI();
#endif

#if DEBUG
    // For debug builds, stop in a debugger.
    mybkpt();
#endif

    while (1) ;
}

__attribute__ ((naked)) void mybkpt(void)
{
    asm volatile (
#if DEBUG
        "bkpt #0        \n"
#endif
        "bx lr          \n"
        );
}

int32_t is_input_char(uint8_t c, const char* const indent)
{
    uint8_t input, lc, uc;

    if (c >= 'A' && c <= 'Z') {
        uc = c;
        lc = c - 'A' + 'a';
    } else if (c >= 'a' && c <= 'z') {
        lc = c;
        uc = c - 'a' + 'A';
    } else {
        printf_color(g_TextAttributeBold, g_TextColorRed, "%sError: not a valid letter: %c\n",
        		indent == NULL ? "" : indent, c);
        return 0;
    }
    printf("%sPlease enter %c or %c to confirm.\n", indent == NULL ? "" : indent, lc, uc);
    do {
        input = uart_getchar(g_debug_uart_port);
    } while (input == NONE_CHAR);
    printf("%c\n", input);

    if ((input == uc) || (input == lc))
        return 1;
    else
        return 0;
}

char * read_input_string(input_string_filter_t filter)
{
    int len = 0;
    int maxLen = INPUT_STRING_ALLOC_SIZE;
    char * result = (char *)malloc(maxLen + 1);
    if (!result)
    {
        return NULL;
    }
    
    // Start off with an empty string.
    result[0] = 0;
    
    while (true)
    {
        char c = getchar();
        if (c == NONE_CHAR)
        {
            continue;
        }
        else if (c == '\r' || c == '\n')
        {
            // End entering.
            fputc('\n', stdout);
            break;
        }
        // Escape cancels input.
        else if (c == kEscapeChar)
        {
            len = 0;
            fputc('\n', stdout);
            break;
        }
        // Support both backspace and delete so it works regardless of terminal config.
        else if (c == kBackspaceChar || c == kDeleteChar)
        {
            if (len > 0)
            {
                result[--len] = 0;
            }
            
            // Erase the char.
            fputc(c, stdout);
            fputc(' ', stdout);
            fputc(c, stdout);
            
            continue;
        }
        
        // Ask the filter if the char is ok.
        if (filter && !filter(c, result))
        {
            continue;
        }
        
        // Reallocate the string if needed.
        if (len >= maxLen)
        {
            maxLen += INPUT_STRING_ALLOC_SIZE;
            result = (char *)realloc(result, maxLen + 1);
            if (!result)
            {
                return NULL;
            }
        }
        
        // Build up the string.
        result[len++] = c;
        result[len] = 0;
        
        // Echo the character.
        fputc(c, stdout);
    }
    
    return result;
}

uint32_t get_input_hex(void)
{
    uint8_t tmp[8];
    uint8_t recvCh, q;

    printf("Enter up to a 8-digit HEX value, e.g. 1A2B3C4D, then hit enter.\n");

    for(q=0;q<8;q++)
        tmp[q] = 0;

    q = 0;
    do {
        recvCh = getchar();
        if (recvCh != NONE_CHAR) {
            if (recvCh >= '0' && recvCh <= '9') {
                tmp[q] = recvCh - '0';
            }
            else if (recvCh >= 'a' && recvCh <= 'f') {
                tmp[q] = recvCh - 'a' + 10;
            }
            else if (recvCh >= 'A' && recvCh <= 'F') {
                tmp[q] = recvCh - 'A' + 10;
            }
            else {
                if ((recvCh == '\n') || (recvCh == '\r'))
                    break;
                else {
                    printf("\nNot a valid input, valid inputs are [0-9,a-f,A-F]\n");
                    continue;
                }
            }
            fputc(recvCh, stdout);
            q++;
        }
    } while (1);

    return (uint32_t) tmp[0] * 0x10000000 + tmp[1] * 0x1000000 + tmp[2] * 0x100000
                      + tmp[3] * 0x10000 + tmp[4] * 0x1000 + tmp[5] * 0x100
                      + tmp[6] * 0x10 + tmp[7];
}

int read_int(void)
{
    int result = 0;
    bool isDone = false;
    
    while (!isDone)
    {
        char c = getchar();
        switch (c)
        {
            case NONE_CHAR:
            default:
                continue;
            
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                // Update our int value.
                result = (result * 10) + (c - '0');
                break;
                
            case '\n':
            case '\r':
                // Exit the scan loop.
                c = '\n';
                isDone = true;
                break;
        }

        // Echo the char.
        fputc(c, stdout);
    }

    return result;
}

void jump_to_sdp(void)
{
	/* Re-configure the clock gating like the ROM expects it */
    HW_CCM_CCGR0_WR(0xF0C03F0F);
    HW_CCM_CCGR1_WR(0xF0FC0000);
    HW_CCM_CCGR2_WR(0xFC3FF00C);
    HW_CCM_CCGR3_WR(0x3FF00000);
    HW_CCM_CCGR4_WR(0x0000FF00);
    HW_CCM_CCGR5_WR(0xF0033F0F);
    HW_CCM_CCGR6_WR(0xFFFF0303);

	/* enter the ROM Serial Download Protocol */
    hab_rvt_failsafe();
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
