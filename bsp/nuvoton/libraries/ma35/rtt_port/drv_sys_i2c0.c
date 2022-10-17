/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-11-11      Wayne            First version
*
******************************************************************************/

#include <rtthread.h>
#include "NuMicro.h"

#define ERROR rt_kprintf
#define RETRY_COUNT 3
/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
static uint8_t g_u8DeviceAddr = 0xB0;
static uint8_t g_uPageNum;
static uint8_t g_u8RegAddr;
static uint8_t g_u8WriteData;

static volatile uint8_t g_u8RxData;
static volatile uint8_t g_u8DataLen;
static volatile uint8_t g_u8EndFlag = 0;

static void I2C0_MasterRx(uint32_t u32Status)
{
    if (u32Status == 0x08)
    {
        /* START has been transmitted and prepare SLA+W */
        I2C0->DAT = g_u8DeviceAddr | (g_uPageNum << 1);
        I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | I2C_CTL_SI;
    }
    else if (u32Status == 0x18)
    {
        /* SLA+W has been transmitted and ACK has been received */
        I2C0->DAT = g_u8RegAddr;
        I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | I2C_CTL_SI;
    }
    else if (u32Status == 0x20)
    {
        /* SLA+W has been transmitted and NACK has been received */
        I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | (I2C_CTL_STA | I2C_CTL_STO | I2C_CTL_SI);
    }
    else if (u32Status == 0x28)
    {
        /* DATA has been transmitted and ACK has been received */
        I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | (I2C_CTL_STA | I2C_CTL_SI); // repeat start
    }
    else if (u32Status == 0x10)
    {
        /* Repeat START has been transmitted and prepare SLA+R */
        I2C0->DAT = (g_u8DeviceAddr | (g_uPageNum << 1)) | 0x01;
        I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | I2C_CTL_SI;
    }
    else if (u32Status == 0x40)
    {
        /* SLA+R has been transmitted and ACK has been received */
        I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | I2C_CTL_SI;
    }
    else if (u32Status == 0x58)
    {
        /* DATA has been received and NACK has been returned */
        g_u8RxData = I2C0->DAT;
        I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | (I2C_CTL_STO | I2C_CTL_SI);
        g_u8EndFlag = 1;
    }
    else
    {
        ERROR("Status 0x%x is NOT processed\n", u32Status);
    }
}

static void I2C0_MasterTx(uint32_t u32Status)
{
    if (u32Status == 0x08)
    {
        /* START has been transmitted */
        I2C0->DAT = g_u8DeviceAddr | (g_uPageNum << 1); /* Write SLA+W to Register I2CDAT */
        I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | I2C_CTL_SI;
    }
    else if (u32Status == 0x18)
    {
        /* SLA+W has been transmitted and ACK has been received */
        I2C0->DAT = g_u8RegAddr;
        I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | I2C_CTL_SI;
    }
    else if (u32Status == 0x20)
    {
        /* SLA+W has been transmitted and NACK has been received */
        I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | (I2C_CTL_STA | I2C_CTL_STO | I2C_CTL_SI);
    }
    else if (u32Status == 0x28)
    {
        /* DATA has been transmitted and ACK has been received */
        if ((g_u8DataLen == 0) && (g_u8EndFlag == 0))
        {
            I2C0->DAT = g_u8WriteData;
            I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | I2C_CTL_SI;
            g_u8DataLen++;
        }
        else
        {
            g_u8DataLen = 0;
            I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | (I2C_CTL_STO | I2C_CTL_SI);
            g_u8EndFlag = 1;
        }
    }
    else
    {
        ERROR("Status 0x%x is NOT processed\n", u32Status);
    }
}

static uint32_t ma35d1_write_i2c_data(uint32_t u32Addr, uint32_t u32Data)
{
    uint32_t I2C_TIME_OUT_COUNT = 0x20000;
    uint32_t u32Status;
    uint32_t u32time_out = 0;

    g_uPageNum = 0;
    if (g_uPageNum == 0xff)
    {
        ERROR("\n address error !!\n");
        return 0;
    }

    g_u8RegAddr     = u32Addr;
    g_u8WriteData   = u32Data;
    g_u8EndFlag     = 0x0;

    I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | I2C_CTL_STA;

    while (1)
    {
        if (I2C0->CTL0 & I2C_CTL_SI)
        {
            u32time_out = 0;
            u32Status = I2C0->STATUS0;
            I2C0_MasterTx(u32Status);
        }

        if (g_u8EndFlag)
        {
            break;
        }
        u32time_out++;
        if (u32time_out > I2C_TIME_OUT_COUNT)
        {
            ERROR("i2c Write Time Out!\n");
            return 0; // error
        }
    }
    return 1;
}

static uint32_t ma35d1_read_i2c_data(uint32_t u32Addr, uint32_t *pu32Data)
{
    uint32_t I2C_TIME_OUT_COUNT = 0x200000;
    uint32_t u32Status;
    uint32_t u32time_out = 0;

    g_uPageNum = 0;
    if (g_uPageNum == 0xff)
    {
        ERROR("\n address error !!\n");
        return 0;
    }

    g_u8RegAddr     = u32Addr;
    g_u8EndFlag     = 0x0;

    I2C0->CTL0 = (I2C0->CTL0 & ~0x3c) | I2C_CTL_STA;

    while (1)
    {
        if (I2C0->CTL0 & I2C_CTL_SI)
        {
            u32time_out = 0;
            u32Status = I2C0->STATUS0;
            I2C0_MasterRx(u32Status);
        }

        if (g_u8EndFlag)
        {
            break;
        }

        u32time_out++;
        if (u32time_out > I2C_TIME_OUT_COUNT)
        {
            ERROR("i2c Read Time Out!\n");
            return 1; // error
        }
    }

    *pu32Data = g_u8RxData;
    return 2;
}

static uint32_t ma35d1_read_pmic_data(uint32_t u32Addr, uint32_t *pu32Data)
{
    uint32_t j = RETRY_COUNT;

    while (j-- > 0)
    {
        if (ma35d1_read_i2c_data(u32Addr, pu32Data) == 2)
        {
            break;
        }
    }

    if (j <= 0)
    {
        ERROR("\n READ ERROR! \n");
        return 0;
    }

    return 1;
}

static uint32_t ma35d1_write_pmic_data(uint32_t u32Addr, uint32_t u32Data)
{
    uint32_t j = RETRY_COUNT;

    while (j-- > 0)
    {
        if (ma35d1_write_i2c_data(u32Addr, u32Data) == 1)
        {
            break;
        }
    }

    if (j <= 0)
    {
        ERROR("\n WRITE ERROR [%d]! \n", j);
        return 0;
    }

    return 1;
}

static void ma35d1_i2c0_init(uint32_t sys_clk)
{
    unsigned long clk_rate;
    uint32_t u32Div, speed;

    outpw((void *)0x40460208, inpw((void *)0x40460208) | (0x3fff << 16)); // enable GPIO clock
    outpw((void *)0x40460210, inpw((void *)0x40460210) | (0x1 << 0));  // I2C0 CLK

    outpw(0x40460098, ((inpw(0x40460098) & ~0x0f000000) | (0x6 << 24))); // PD.6 I2C0_SDA
    outpw(0x40460098, ((inpw(0x40460098) & ~0xf0000000) | (0x6 << 28))); // PD.7 I2C0_CLK
    outpw(0x400400F0, 0x5 << 12); // pull high

    /* i2c_clk = 100KHz */
    clk_rate = sys_clk;
    speed = 100 * 1000;

    /* assume speed above 1000 are Hz-specified */
    if (speed > 1000) speed = speed / 1000;
    if (speed > 400) speed = 400;

    u32Div = (uint32_t)(((clk_rate * 10U) / (speed * 4U) + 5U) / 10U - 1U);

    I2C0->CLKDIV = u32Div;
    I2C0->CTL0 = I2C0->CTL0 | I2C_CTL0_I2CEN_Msk; /* i2c enable */
}

uint32_t ma35d1_set_cpu_voltage(uint32_t sys_clk, uint32_t u32Vol)
{
    /*
        RegValue = (Voltage - 0.3) / 0.01
        RegValue(hex)   Voltage(v)
            0x5B        1.22
            0x5C        1.23
            0x5D        1.24
            0x5F        1.25
            0x60        1.26
            0x61        1.27
            0x62        1.28
            0x63        1.29
            0x64        1.30
            0x65        1.31
            0x66        1.32
            0x67        1.33
            0x68        1.34
            0x69        1.35
     */
    uint32_t u32Data = 0;

    if ((u32Vol < 0x59) || (u32Vol > 0x68))
        return 0;

    ma35d1_i2c0_init(sys_clk);
    ma35d1_write_pmic_data(0xA4, u32Vol);
    ma35d1_read_pmic_data(0xA4, &u32Data);

    return (u32Data == u32Vol);
}
