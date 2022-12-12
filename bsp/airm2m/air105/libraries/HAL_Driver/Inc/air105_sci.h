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



#ifndef __AIR105_SCI_H
#define __AIR105_SCI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "air105.h"
#include <arm_math.h>


#define SCI_UNCONFIG                (-1)
#define SCI_ICC_CLOCK_ERR           (-2)
#define SCI_REF_CLOCK_ERR           (-3)
#define SCI_IMPRECISION_CLK         (-4)
#define SCI_EMV_F_D_ERR             (-5)
#define SCI_EMV_TS_ERR              (-6)
#define SCI_EMV_ATR_ERR             (-7)
#define SCI_CARD_OUT_ERR            (-8)


int32_t SCI_ConfigEMV(uint8_t SCI_Bitmap, uint32_t SCIx_Clk);


#ifdef __cplusplus
}
#endif

#endif   ///< __AIR105_SCI_H

