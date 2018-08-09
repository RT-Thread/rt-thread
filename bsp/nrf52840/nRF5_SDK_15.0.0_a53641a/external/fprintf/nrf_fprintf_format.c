/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*       (c) 2014 - 2017  SEGGER Microcontroller GmbH & Co. KG        *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER RTT * Real Time Transfer for embedded targets         *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* SEGGER strongly recommends to not make any changes                 *
* to or modify the source code of this software in order to stay     *
* compatible with the RTT protocol and J-Link.                       *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* conditions are met:                                                *
*                                                                    *
* o Redistributions of source code must retain the above copyright   *
*   notice, this list of conditions and the following disclaimer.    *
*                                                                    *
* o Redistributions in binary form must reproduce the above          *
*   copyright notice, this list of conditions and the following      *
*   disclaimer in the documentation and/or other materials provided  *
*   with the distribution.                                           *
*                                                                    *
* o Neither the name of SEGGER Microcontroller GmbH & Co. KG         *
*   nor the names of its contributors may be used to endorse or      *
*   promote products derived from this software without specific     *
*   prior written permission.                                        *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************
*                                                                    *
*       RTT version: 6.14d                                           *
*                                                                    *
*********************************************************************/

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_FPRINTF)

#include <stdarg.h>

#include "nrf_assert.h"
#include "nrf_fprintf.h"
#include "nrf_fprintf_format.h"

#define NRF_CLI_FORMAT_FLAG_LEFT_JUSTIFY   (1u << 0)
#define NRF_CLI_FORMAT_FLAG_PAD_ZERO       (1u << 1)
#define NRF_CLI_FORMAT_FLAG_PRINT_SIGN     (1u << 2)

static void buffer_add(nrf_fprintf_ctx_t * const p_ctx, char c)
{
    p_ctx->p_io_buffer[p_ctx->io_buffer_cnt++] = c;

    if (p_ctx->io_buffer_cnt >= p_ctx->io_buffer_size)
    {
        nrf_fprintf_buffer_flush(p_ctx);
    }
}

static void string_print(nrf_fprintf_ctx_t * const p_ctx,
                         char const *              p_str,
                         uint32_t                  FieldWidth,
                         uint32_t                  FormatFlags)
{
    uint32_t Width = 0;
    char c;

    if ((FormatFlags & NRF_CLI_FORMAT_FLAG_LEFT_JUSTIFY) == NRF_CLI_FORMAT_FLAG_LEFT_JUSTIFY)
    {
        while ((c = *p_str) != '\0')
        {
            p_str++;
            Width++;
            buffer_add(p_ctx, c);
        }

        while ((FieldWidth > Width) && (FieldWidth > 0))
        {
            FieldWidth--;
            buffer_add(p_ctx, ' ');
        }
    }
    else
    {
        if (p_str != 0)
        {
            Width = strlen(p_str);
        }

        while ((FieldWidth > Width) && (FieldWidth > 0))
        {
            FieldWidth--;
            buffer_add(p_ctx, ' ');
        }

        while ((c = *p_str) != '\0')
        {
            p_str++;
            Width++;
            buffer_add(p_ctx, c);
        }
    }
}

static void unsigned_print(nrf_fprintf_ctx_t * const p_ctx,
                           uint32_t                  v,
                           uint32_t                  Base,
                           uint32_t                  NumDigits,
                           uint32_t                  FieldWidth,
                           uint32_t                  FormatFlags)
{
    static const char _aV2C[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                                   'A', 'B', 'C', 'D', 'E', 'F' };
    uint32_t Div;
    uint32_t Value;
    uint32_t Width;
    char c;

    Value = v;
    //
    // Get actual field width
    //
    Width = 1u;
    while (Value >= Base)
    {
        Value = (Value / Base);
        Width++;
    }
    if (NumDigits > Width)
    {
        Width = NumDigits;
    }
    //
    // Print leading chars if necessary
    //
    if ((FormatFlags & NRF_CLI_FORMAT_FLAG_LEFT_JUSTIFY) == 0u)
    {
        if (FieldWidth != 0u)
        {
            if (((FormatFlags & NRF_CLI_FORMAT_FLAG_PAD_ZERO) == NRF_CLI_FORMAT_FLAG_PAD_ZERO) &&
                (NumDigits == 0u))
            {
                c = '0';
            }
            else
            {
                c = ' ';
            }
            while ((FieldWidth != 0u) && (Width < FieldWidth))
            {
                FieldWidth--;
                buffer_add(p_ctx, c);
            }
        }
    }

    Value = 1;
    /*
     * Compute Digit.
     * Loop until Digit has the value of the highest digit required.
     * Example: If the output is 345 (Base 10), loop 2 times until Digit is 100.
     */
    while (1)
    {
        /* User specified a min number of digits to print? => Make sure we loop at least that
         * often, before checking anything else (> 1 check avoids problems with NumDigits
         * being signed / unsigned)
         */
        if (NumDigits > 1u)
        {
            NumDigits--;
        }
        else
        {
            Div = v / Value;
            // Is our divider big enough to extract the highest digit from value? => Done
            if (Div < Base)
            {
                break;
            }
        }
        Value *= Base;
    }
    //
    // Output digits
    //
    do
    {
        Div = v / Value;
        v -= Div * Value;
        buffer_add(p_ctx, _aV2C[Div]);
        Value /= Base;
    } while (Value);
    //
    // Print trailing spaces if necessary
    //
    if ((FormatFlags & NRF_CLI_FORMAT_FLAG_LEFT_JUSTIFY) == NRF_CLI_FORMAT_FLAG_LEFT_JUSTIFY)
    {
        if (FieldWidth != 0u)
        {
            while ((FieldWidth != 0u) && (Width < FieldWidth))
            {
                FieldWidth--;
                buffer_add(p_ctx, ' ');
            }
        }
    }
}

static void int_print(nrf_fprintf_ctx_t * const p_ctx,
                      int32_t                   v,
                      uint32_t                  Base,
                      uint32_t                  NumDigits,
                      uint32_t                  FieldWidth,
                      uint32_t                  FormatFlags)
{
    uint32_t Width;
    int32_t Number;

    Number = (v < 0) ? -v : v;

    //
    // Get actual field width
    //
    Width = 1u;
    while (Number >= (int32_t)Base)
    {
        Number = (Number / (int32_t)Base);
        Width++;
    }
    if (NumDigits > Width)
    {
        Width = NumDigits;
    }
    if ((FieldWidth > 0u) && ((v < 0) ||
        ((FormatFlags & NRF_CLI_FORMAT_FLAG_PRINT_SIGN) == NRF_CLI_FORMAT_FLAG_PRINT_SIGN)))
    {
        FieldWidth--;
    }
    //
    // Print leading spaces if necessary
    //
    if ((((FormatFlags & NRF_CLI_FORMAT_FLAG_PAD_ZERO) == 0u) || (NumDigits != 0u)) &&
        ((FormatFlags & NRF_CLI_FORMAT_FLAG_LEFT_JUSTIFY) == 0u))
    {
        if (FieldWidth != 0u)
        {
            while ((FieldWidth != 0u) && (Width < FieldWidth))
            {
                FieldWidth--;
                buffer_add(p_ctx, ' ');
            }
        }
    }
    //
    // Print sign if necessary
    //
    if (v < 0)
    {
        v = -v;
        buffer_add(p_ctx, '-');
    }
    else if ((FormatFlags & NRF_CLI_FORMAT_FLAG_PRINT_SIGN) == NRF_CLI_FORMAT_FLAG_PRINT_SIGN)
    {
        buffer_add(p_ctx, '+');
    }
    else
    {
        /* do nothing */
    }
    //
    // Print leading zeros if necessary
    //
    if (((FormatFlags & NRF_CLI_FORMAT_FLAG_PAD_ZERO) == NRF_CLI_FORMAT_FLAG_PAD_ZERO) &&
        ((FormatFlags & NRF_CLI_FORMAT_FLAG_LEFT_JUSTIFY) == 0u) && (NumDigits == 0u))
    {
        if (FieldWidth != 0u)
        {
            while ((FieldWidth != 0u) && (Width < FieldWidth))
            {
                FieldWidth--;
                buffer_add(p_ctx, '0');
            }
        }
    }
    //
    // Print number without sign
    //
    unsigned_print(p_ctx, (uint32_t)v, Base, NumDigits, FieldWidth, FormatFlags);
}

void nrf_fprintf_fmt(nrf_fprintf_ctx_t * const p_ctx,
                    char const *               p_fmt,
                    va_list *                  p_args)
{
    ASSERT(p_ctx != NULL);

    ASSERT(p_ctx->fwrite != NULL);
    ASSERT(p_ctx->p_io_buffer != NULL);
    ASSERT(p_ctx->io_buffer_size > 0);

    if (p_fmt == NULL)
    {
        return;
    }

    char c;
    int32_t v;
    uint32_t NumDigits;
    uint32_t FormatFlags;
    uint32_t FieldWidth;

    do
    {
        c = *p_fmt;
        p_fmt++;

        if (c == 0u)
        {
            break;
        }
        if (c == '%')
        {
            //
            // Filter out flags
            //
            FormatFlags = 0u;
            v = 1;

            do
            {
                c = *p_fmt;
                switch (c)
                {
                    case '-':
                        FormatFlags |= NRF_CLI_FORMAT_FLAG_LEFT_JUSTIFY;
                        p_fmt++;
                        break;
                    case '0':
                        FormatFlags |= NRF_CLI_FORMAT_FLAG_PAD_ZERO;
                        p_fmt++;
                        break;
                    case '+':
                        FormatFlags |= NRF_CLI_FORMAT_FLAG_PRINT_SIGN;
                        p_fmt++;
                        break;
                    default:
                        v = 0;
                        break;
                }
            } while (v);

            //
            // filter out field width
            //
            FieldWidth = 0u;
            do
            {
                if (c == '*')
                {
                    /*lint -save -e64 -e56*/
                    FieldWidth += va_arg(*p_args, unsigned);
                    /*lint -restore*/
                    p_fmt++;
                    break;
                }
                c = *p_fmt;
                if ((c < '0') || (c > '9'))
                {
                    break;
                }
                p_fmt++;
                FieldWidth = (FieldWidth * 10u) + (c - '0');
            } while (1);

            //
            // Filter out precision (number of digits to display)
            //
            NumDigits = 0u;
            c = *p_fmt;
            if (c == '.')
            {
                p_fmt++;
                do
                {
                    c = *p_fmt;
                    if ((c < '0') || (c > '9'))
                    {
                        break;
                    }
                    p_fmt++;
                    NumDigits = NumDigits * 10u + (c - '0');
                } while (1);
            }
            //
            // Filter out length modifier
            //
            c = *p_fmt;
            do
            {
                if ((c == 'l') || (c == 'h'))
                {
                    p_fmt++;
                    c = *p_fmt;
                }
                else
                {
                    break;
                }
            } while (1);
            //
            // Handle specifiers
            //
            /*lint -save -e64*/
            switch (c)
            {
                case 'c':
                {
                    char c0;
                    v = va_arg(*p_args, int32_t);
                    c0 = (char)v;
                    buffer_add(p_ctx, c0);
                    break;
                }
                case 'd':
                case 'i':
                    v = va_arg(*p_args, int32_t);
                    int_print(p_ctx,
                              v,
                              10u,
                              NumDigits,
                              FieldWidth,
                              FormatFlags);
                    break;
                case 'u':
                    v = va_arg(*p_args, int32_t);
                    unsigned_print(p_ctx,
                                   (uint32_t)v,
                                   10u,
                                   NumDigits,
                                   FieldWidth,
                                   FormatFlags);
                    break;
                case 'x':
                case 'X':
                    v = va_arg(*p_args, int32_t);
                    unsigned_print(p_ctx,
                                   (uint32_t)v,
                                   16u,
                                   NumDigits,
                                   FieldWidth,
                                   FormatFlags);
                    break;
                case 's':
                {
                    char const * p_s = va_arg(*p_args, const char *);
                    string_print(p_ctx, p_s, FieldWidth, FormatFlags);
                    break;
                }
                case 'p':
                    v = va_arg(*p_args, int32_t);
                    buffer_add(p_ctx, '0');
                    buffer_add(p_ctx, 'x');
                    unsigned_print(p_ctx, (uint32_t)v, 16u, 8u, 8u, 0);
                    break;
                case '%':
                    buffer_add(p_ctx, '%');
                    break;
                default:
                    break;
            }
            /*lint -restore*/
            p_fmt++;
        }
        else
        {
            buffer_add(p_ctx, c);
        }
    } while (*p_fmt != '\0');

    if (p_ctx->auto_flush)
    {
        nrf_fprintf_buffer_flush(p_ctx);
    }
}

#endif // NRF_MODULE_ENABLED(NRF_FPRINTF)

