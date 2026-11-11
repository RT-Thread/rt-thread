/**
 ****************************************************************************************
 *
 * @file clib.h
 *
 * @brief C Library
 *
 * Copyright (c) 2023-2024 Renesas Electronics. All rights reserved.
 *
 * This software ("Software") is owned by Renesas Electronics.
 *
 * By using this Software you agree that Renesas Electronics retains all
 * intellectual property and proprietary rights in and to this Software and any
 * use, reproduction, disclosure or distribution of the Software without express
 * written permission or a license agreement from Renesas Electronics is
 * strictly prohibited. This Software is solely for use on or in conjunction
 * with Renesas Electronics products.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE
 * SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. EXCEPT AS OTHERWISE
 * PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * RENESAS ELECTRONICS BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 *
 ****************************************************************************************
 */

#ifndef __clib_h__
#define __clib_h__

#include <ctype.h>

#include "bsp_api.h"
#include "bsp_sflash_map_ra6w1.h"

__STATIC_INLINE unsigned char toint (char c)
{
    unsigned char rslt;

    if ((c >= '0') && (c <= '9'))
    {
        rslt = (c - '0');
    }
    else if ((c >= 'a') && (c <= 'f'))
    {
        rslt = (c - 'a' + (unsigned char) 10);
    }
    else if ((c >= 'A') && (c <= 'F'))
    {
        rslt = (c - 'A' + (unsigned char) 10);
    }
    else
    {
        rslt = (unsigned char) 0;
    }

    return rslt;
}

__STATIC_INLINE unsigned int htoi (char * s)
{
    unsigned int sum = 0;

    while ((*s >= '0') && (*s <= 'f'))
    {
        sum = sum * 16 + toint(*s++);
    }

    return sum;
}

__STATIC_INLINE int btoi (char * s)
{
    short sum = 0;

    while ((*s >= '0') && (*s <= '1'))
    {
        sum = (short) (sum * 2 + toint(*s++));
    }

    return sum;
}

__STATIC_INLINE unsigned int ctoi (char * s)
{
    unsigned int sum = 0;

    while ((*s >= '0') && (*s <= '9'))
    {
        sum = sum * 10 + toint(*s++);
    }

    return sum;
}

__STATIC_INLINE int stoi (char * s)
{
    int sum = 0, sign;

    if (*s == '-')
    {
        sign = -1;
        s++;
    }
    else
    {
        sign = 1;
    }

    while (*s)
    {
        sum = sum * 10 + toint(*s++);
    }

    sum = sign * sum;

    return sum;
}

#endif                                 /* __clib_h__ */
