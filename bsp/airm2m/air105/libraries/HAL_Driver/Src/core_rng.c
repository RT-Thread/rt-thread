/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "user.h"

void RNG_Init(void)
{
    TRNG->RNG_ANA = 0;
    TRNG->RNG_CSR = 0;
}
/**
 * @brief 获取随机数
 *
 * @param Buf，一次获取4个32bit数据
 */
void RNG_GetData(uint32_t Buf[4])
{
    if (TRNG->RNG_CSR & TRNG_RNG_CSR_S128_TRNG0_Mask)
    {
        ;
    }
    else
    {
        TRNG->RNG_CSR = 0;
        while(!(TRNG->RNG_CSR & TRNG_RNG_CSR_S128_TRNG0_Mask)){;}
    }
    Buf[0] = TRNG->RNG_DATA[0];
    Buf[1] = TRNG->RNG_DATA[0];
    Buf[2] = TRNG->RNG_DATA[0];
    Buf[3] = TRNG->RNG_DATA[0];
    TRNG->RNG_CSR = 0;


}
