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

#include "bl_inc.h"
#define OTP_KEY1                    (0xABCD00A5)
#define OTP_KEY2                    (0x1234005A)
#define OTP_START_ADDRESS           (0x40008000)

void OTP_Write(uint32_t Address, const uint32_t *Data, uint32_t Len)
{
    uint32_t i;
    SYSCTRL->CG_CTRL2 |= SYSCTRL_AHBPeriph_OTP;
    OTP->RO = 0;
    OTP->CFG = 0;
    for(i = 0; i < Len; i++)
    {
        OTP->PDATA = Data[i];
        OTP->ADDR = Address + (i * 4);
        OTP->PROT = OTP_KEY1;
        OTP->PROT = OTP_KEY2;
        OTP->CS |= 1;
        while((OTP->CS & 0x00000001)){;}
        OTP->CS &= ~(0x07 << 1);
    }
    SYSCTRL->CG_CTRL2 &= ~SYSCTRL_AHBPeriph_OTP;
}

void OTP_Read(uint32_t Address, uint8_t *Data, uint32_t Len)
{
    SYSCTRL->CG_CTRL2 |= SYSCTRL_AHBPeriph_OTP;
    OTP->CFG = 0x02;
    while(!(OTP->CS & 0x80000000)){;}
    memcpy(Data, Address + OTP_START_ADDRESS, Len);
    SYSCTRL->CG_CTRL2 &= ~SYSCTRL_AHBPeriph_OTP;
}
void OTP_Lock(void)
{
    SYSCTRL->CG_CTRL2 |= SYSCTRL_AHBPeriph_OTP;
    OTP->CFG = 0x02;
    OTP->RO = 0xffffffff;
    OTP->ROL = 0xffffffff;
    OTP->CFG = 0x01;
    SYSCTRL->CG_CTRL2 &= ~SYSCTRL_AHBPeriph_OTP;
}

void OTP_GetSn(uint8_t *ChipSN)
{
    memcpy(ChipSN, (uint32_t *)(SYSCTRL_CHIP_SN_ADDR), SYSCTRL_CHIP_SN_LEN);
}
