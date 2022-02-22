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


#ifndef __AIR105_CRC_H
#define __AIR105_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air105.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
    CRC_16 = 0x01,
    CRC_16_Modbus = 0x02,
    CRC_CCITT_0xffff = 0x03,
    CRC_CCITT_XModem = 0x04,
    CRC_32 = 0x05
}CRC_Param_TypeDef;

typedef enum
{
    CRC_Poly_16_1021 = 0x01,
    CRC_Poly_16_8005 = 0x02,
    CRC_Poly_32_04C11DB7 = 0x03
}CRC_Poly_TypeDef;

typedef enum
{
    CRC_PolyMode_Normal = 0x01,
    CRC_PolyMode_Reversed = 0x02,
}CRC_PolyMode_TypeDef;

typedef struct
{
    CRC_Poly_TypeDef CRC_Poly;
    CRC_PolyMode_TypeDef CRC_PolyMode;
    uint32_t CRC_Init_Value;
    uint32_t CRC_Xor_Value;
}CRC_ConfigTypeDef;


uint32_t CRC_CalcBlockCRC(uint32_t CRC_type, uint8_t *pData, uint32_t len);
uint32_t CRC_Calc(CRC_ConfigTypeDef *CRC_Config, uint8_t *pData, uint32_t len);


#ifdef __cplusplus
}
#endif

#endif

