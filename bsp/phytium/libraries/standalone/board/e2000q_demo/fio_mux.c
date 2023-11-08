/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fio_mux.c
 * Date: 2023-07-25 14:53:42
 * LastEditTime: 2023-07-25 08:25:29
 * Description:  This file is for io-pad function
 *
 * Modify History:
 *  Ver   Who        Date       Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   liusm    2023/7/25     init commit
 * 1.1   zhugengyu 2023/10/23   add sd mux
 */

/***************************** Include Files *********************************/
#include "fiopad_hw.h"
#include "fiopad.h"
#include "fio_mux.h"
#include "fparameters.h"
#include "fboard_port.h"

#include "fassert.h"

#define FBOARD_IO_DEBUG_TAG "FBOARD_IO-CFG"
#define FBOARD_IO_ERROR(format, ...)   FT_DEBUG_PRINT_E(FBOARD_IO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FBOARD_IO_WARN(format, ...)    FT_DEBUG_PRINT_W(FBOARD_IO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FBOARD_IO_INFO(format, ...)    FT_DEBUG_PRINT_I(FBOARD_IO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FBOARD_IO_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FBOARD_IO_DEBUG_TAG, format, ##__VA_ARGS__)

FIOPadCtrl iopad_ctrl;

/*****************************************************************************/
/**
 * @name: FIOPadSetSpimMux
 * @msg: set iopad mux for spim
 * @return {*}
 * @param {u32} spim_id, instance id of spi
 */
void FIOPadSetSpimMux(u32 spim_id)
{
    if (FSPI0_ID == spim_id)
    {
        FBOARD_IO_INFO("%d-%d-%d-%d", FIOPadGetFunc(&iopad_ctrl, FIOPAD_W55_REG0_OFFSET),
                       FIOPadGetFunc(&iopad_ctrl, FIOPAD_W53_REG0_OFFSET), FIOPadGetFunc(&iopad_ctrl, FIOPAD_U55_REG0_OFFSET),
                       FIOPadGetFunc(&iopad_ctrl, FIOPAD_U53_REG0_OFFSET));
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_W55_REG0_OFFSET, FIOPAD_FUNC2); /* sclk */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_W53_REG0_OFFSET, FIOPAD_FUNC2); /* txd */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_U55_REG0_OFFSET, FIOPAD_FUNC2); /* rxd */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_U53_REG0_OFFSET, FIOPAD_FUNC2); /* csn0 */
        FBOARD_IO_INFO("%d-%d-%d-%d", FIOPadGetFunc(&iopad_ctrl, FIOPAD_W55_REG0_OFFSET),
                       FIOPadGetFunc(&iopad_ctrl, FIOPAD_W53_REG0_OFFSET), FIOPadGetFunc(&iopad_ctrl, FIOPAD_U55_REG0_OFFSET),
                       FIOPadGetFunc(&iopad_ctrl, FIOPAD_U53_REG0_OFFSET));
    }
    else if (FSPI1_ID == spim_id)
    {
        FBOARD_IO_INFO("%d-%d-%d-%d", FIOPadGetFunc(&iopad_ctrl, FIOPAD_N43_REG0_OFFSET),
                       FIOPadGetFunc(&iopad_ctrl, FIOPAD_L31_REG0_OFFSET), FIOPadGetFunc(&iopad_ctrl, FIOPAD_J31_REG0_OFFSET),
                       FIOPadGetFunc(&iopad_ctrl, FIOPAD_J29_REG0_OFFSET));
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_N43_REG0_OFFSET, FIOPAD_FUNC4); /* sclk */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_L31_REG0_OFFSET, FIOPAD_FUNC4); /* txd */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_J31_REG0_OFFSET, FIOPAD_FUNC4); /* rxd */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_J29_REG0_OFFSET, FIOPAD_FUNC4); /* csn0 */
        FBOARD_IO_INFO("%d-%d-%d-%d", FIOPadGetFunc(&iopad_ctrl, FIOPAD_N43_REG0_OFFSET),
                       FIOPadGetFunc(&iopad_ctrl, FIOPAD_L31_REG0_OFFSET), FIOPadGetFunc(&iopad_ctrl, FIOPAD_J31_REG0_OFFSET),
                       FIOPadGetFunc(&iopad_ctrl, FIOPAD_J29_REG0_OFFSET));
    }
    else if (FSPI2_ID == spim_id)
    {
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_A33_REG0_OFFSET, FIOPAD_FUNC0); /* sclk */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_C33_REG0_OFFSET, FIOPAD_FUNC0); /* txd */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_C31_REG0_OFFSET, FIOPAD_FUNC0); /* rxd */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_A31_REG0_OFFSET, FIOPAD_FUNC0); /* csn0 */
    }
    else if (FSPI3_ID == spim_id)
    {
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_AC55_REG0_OFFSET, FIOPAD_FUNC2); /* sclk */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_AC53_REG0_OFFSET, FIOPAD_FUNC2); /* txd */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_AE51_REG0_OFFSET, FIOPAD_FUNC2); /* rxd */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_W51_REG0_OFFSET, FIOPAD_FUNC2); /* csn0 */
    }
}

/**
 * @name: FIOPadSetGpioMux
 * @msg: set iopad mux for gpio
 * @return {*}
 * @param {u32} gpio_id, instance id of gpio
 * @param {u32} pin_id, index of pin
 */
void FIOPadSetGpioMux(u32 gpio_id, u32 pin_id)
{
    if (FGPIO2_ID == gpio_id)
    {
        switch (pin_id)
        {
            case 11: /* gpio 2-a-11 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_N49_REG0_OFFSET, FIOPAD_FUNC0);
                break;
            case 12: /* gpio 2-a-12 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_L51_REG0_OFFSET, FIOPAD_FUNC0);
                break;
            case 13: /* gpio 2-a-13 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_L49_REG0_OFFSET, FIOPAD_FUNC0);
                break;
            case 14: /* gpio 2-a-14 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_N53_REG0_OFFSET, FIOPAD_FUNC0);
                break;
            case 15: /* gpio 2-a-15 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_J53_REG0_OFFSET, FIOPAD_FUNC0);
                break;
        }
    }
    else if (FGPIO3_ID == gpio_id)
    {
        switch (pin_id)
        {
            case 3: /* gpio 3-a-3 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_A33_REG0_OFFSET, FIOPAD_FUNC6);
                break;
            case 4: /* gpio 3-a-4 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_C33_REG0_OFFSET, FIOPAD_FUNC6);
                break;
            case 5: /* gpio 3-a-5 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_C31_REG0_OFFSET, FIOPAD_FUNC6);
                break;
            case 6: /* gpio 3-a-6 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_A31_REG0_OFFSET, FIOPAD_FUNC6);
                break;
            default:
                break;
        }
    }
    else if (FGPIO4_ID == gpio_id)
    {
        switch (pin_id)
        {
            case 5: /* gpio 4-a-5 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_W51_REG0_OFFSET, FIOPAD_FUNC6);
                break;
            case 9: /* gpio 4-a-9 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_U53_REG0_OFFSET, FIOPAD_FUNC6);
                break;
            case 10: /* gpio 4-a-10 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_AE49_REG0_OFFSET, FIOPAD_FUNC6);
                break;
            case 11: /* gpio 4-a-11 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_AC49_REG0_OFFSET, FIOPAD_FUNC6);
                break;
            case 12: /* gpio 4-a-12 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_AE47_REG0_OFFSET, FIOPAD_FUNC6);
                break;
            case 13: /* gpio 4-a-13 */
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_AA47_REG0_OFFSET, FIOPAD_FUNC6);
                break;
            default:
                break;
        }
    }
}


/**
 * @name: FIOPadSetCanMux
 * @msg: set iopad mux for can
 * @return {*}
 * @param {u32} can_id, instance id of can
 */
void FIOPadSetCanMux(u32 can_id)
{
    if (can_id == FCAN0_ID)
    {
        /* can0 */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_A41_REG0_OFFSET, FIOPAD_FUNC0); /* can0-tx: func 0 */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_A43_REG0_OFFSET, FIOPAD_FUNC0); /* can0-rx: func 0 */
    }
    else if (can_id == FCAN1_ID)
    {
        /* can1 */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_A45_REG0_OFFSET, FIOPAD_FUNC0); /* can1-tx: func 0 */
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_C45_REG0_OFFSET, FIOPAD_FUNC0); /* can1-rx: func 0 */
    }
    else
    {
        FBOARD_IO_ERROR("can id is error.\r\n");
    }
}

/**
 * @name: FIOPadSetQspiMux
 * @msg: set iopad mux for qspi
 * @return {*}
 * @param {u32} qspi_id, id of qspi instance
 * @param {u32} cs_id, id of qspi cs
 */
void FIOPadSetQspiMux(u32 qspi_id, u32 cs_id)
{

    if (qspi_id == FQSPI0_ID)
    {
        /* add sck, io0-io3 iopad multiplex */
    }

    if (cs_id == FQSPI_CS_0)
    {
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_AR55_REG0_OFFSET, FIOPAD_FUNC0);
    }
    else if (cs_id == FQSPI_CS_1)
    {
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_AR49_REG0_OFFSET, FIOPAD_FUNC0);
    }
    else if (cs_id == FQSPI_CS_2)
    {
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_C37_REG0_OFFSET, FIOPAD_FUNC5);
    }
    else if (cs_id == FQSPI_CS_3)
    {
        FIOPadSetFunc(&iopad_ctrl, FIOPAD_A37_REG0_OFFSET, FIOPAD_FUNC5);
    }
    else
    {
        FBOARD_IO_ERROR("can id is error.\r\n");
    }
}

/**
 * @name: FIOPadSetPwmMux
 * @msg: set iopad mux for pwm
 * @return {*}
 * @param {u32} pwm_id, id of pwm instance
 * @param {u32} pwm_channel, channel of pwm instance
 */
void FIOPadSetPwmMux(u32 pwm_id, u32 pwm_channel)
{
    FASSERT(pwm_id < FPWM_NUM);
    FASSERT(pwm_channel < FPWM_CHANNEL_NUM);

    switch (pwm_id)
    {
        case FPWM0_ID:
            if (pwm_channel == 0)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_AL59_REG0_OFFSET, FIOPAD_FUNC1); /* PWM0_OUT: func 1 */
            }
            if (pwm_channel == 1)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_AJ57_REG0_OFFSET, FIOPAD_FUNC1); /* PWM1_OUT: func 1 */
            }
            break;

        case FPWM1_ID:
            if (pwm_channel == 0)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_AG57_REG0_OFFSET, FIOPAD_FUNC1); /* PWM2_OUT: func 1 */
            }
            if (pwm_channel == 1)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_AC59_REG0_OFFSET, FIOPAD_FUNC1); /* PWM3_OUT: func 1 */
            }
            break;

        case FPWM2_ID:
            if (pwm_channel == 0)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_BA55_REG0_OFFSET, FIOPAD_FUNC1); /* PWM4_OUT: func 1 */
            }
            if (pwm_channel == 1)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_C39_REG0_OFFSET, FIOPAD_FUNC2); /* PWM5_OUT: func 2 */
            }
            break;

        case FPWM3_ID:
            if (pwm_channel == 0)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_A37_REG0_OFFSET, FIOPAD_FUNC2); /* PWM6_OUT: func 2 */
            }
            if (pwm_channel == 1)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_A43_REG0_OFFSET, FIOPAD_FUNC2); /* PWM7_OUT: func 2 */
            }
            break;

        case FPWM4_ID:
            if (pwm_channel == 0)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_C45_REG0_OFFSET, FIOPAD_FUNC2); /* PWM8_OUT: func 2 */
            }
            if (pwm_channel == 1)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_A49_REG0_OFFSET, FIOPAD_FUNC2); /* PWM9_OUT: func 2 */
            }
            break;

        case FPWM5_ID:
            if (pwm_channel == 0)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_A51_REG0_OFFSET, FIOPAD_FUNC2); /* PWM10_OUT: func 2 */
            }
            if (pwm_channel == 1)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_C33_REG0_OFFSET, FIOPAD_FUNC2); /* PWM11_OUT: func 2 */
            }
            break;

        case FPWM6_ID:
            if (pwm_channel == 0)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_A31_REG0_OFFSET, FIOPAD_FUNC2); /* PWM12_OUT: func 2 */
            }
            if (pwm_channel == 1)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_J39_REG0_OFFSET, FIOPAD_FUNC3); /* PWM13_OUT: func 3 */
            }
            break;

        case FPWM7_ID:
            if (pwm_channel == 0)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_E43_REG0_OFFSET, FIOPAD_FUNC3); /* PWM14_OUT: func 3 */
            }
            if (pwm_channel == 1)
            {
                FIOPadSetFunc(&iopad_ctrl, FIOPAD_C43_REG0_OFFSET, FIOPAD_FUNC3); /* PWM15_OUT: func 3 */
            }
            break;

        default:
            FBOARD_IO_ERROR("pwm id is error.\r\n");
            break;
    }
}

/**
 * @name: FIOPadSetMioMux
 * @msg: set iopad mux for mio
 * @return {*}
 * @param {u32} mio_id, instance id of i2c
 */
void FIOPadSetMioMux(u32 mio_id)
{
    switch (mio_id)
    {
        case FMIO0_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_A41_REG0_OFFSET, FIOPAD_FUNC5); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_A43_REG0_OFFSET, FIOPAD_FUNC5); /* sda */
        }
        break;
        case FMIO1_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_A45_REG0_OFFSET, FIOPAD_FUNC5); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_C45_REG0_OFFSET, FIOPAD_FUNC5); /* sda */
        }
        break;
        case FMIO2_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_A47_REG0_OFFSET, FIOPAD_FUNC5); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_A49_REG0_OFFSET, FIOPAD_FUNC5); /* sda */
        }
        break;
        case FMIO3_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_BA55_REG0_OFFSET, FIOPAD_FUNC4); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_BA53_REG0_OFFSET, FIOPAD_FUNC4); /* sda */
        }
        break;
        case FMIO4_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_R59_REG0_OFFSET, FIOPAD_FUNC4); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_U59_REG0_OFFSET, FIOPAD_FUNC4); /* sda */
        }
        break;
        case FMIO5_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_W49_REG0_OFFSET, FIOPAD_FUNC4); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_U57_REG0_OFFSET, FIOPAD_FUNC4); /* sda */
        }
        break;
        case FMIO6_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AA57_REG0_OFFSET, FIOPAD_FUNC4); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AA59_REG0_OFFSET, FIOPAD_FUNC4); /* sda */
        }
        break;
        case FMIO7_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_A39_REG0_OFFSET, FIOPAD_FUNC4); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_C39_REG0_OFFSET, FIOPAD_FUNC4); /* sda */
        }
        break;
        case FMIO8_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AA49_REG0_OFFSET, FIOPAD_FUNC4); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_W49_REG0_OFFSET, FIOPAD_FUNC4); /* sda */
        }
        break;
        case FMIO9_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AA51_REG0_OFFSET, FIOPAD_FUNC4); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_U49_REG0_OFFSET, FIOPAD_FUNC4); /* sda */
        }
        break;
        case FMIO10_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_C49_REG0_OFFSET, FIOPAD_FUNC5); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_A51_REG0_OFFSET, FIOPAD_FUNC5); /* sda */
        }
        break;
        case FMIO11_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_N27_REG0_OFFSET, FIOPAD_FUNC3); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_L29_REG0_OFFSET, FIOPAD_FUNC3); /* sda */
        }
        break;
        case FMIO12_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_E41_REG0_OFFSET, FIOPAD_FUNC3); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_L45_REG0_OFFSET, FIOPAD_FUNC3); /* sda */
        }
        break;
        case FMIO13_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_J49_REG0_OFFSET, FIOPAD_FUNC6); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_N49_REG0_OFFSET, FIOPAD_FUNC6); /* sda */
        }
        break;
        case FMIO14_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_L51_REG0_OFFSET, FIOPAD_FUNC6); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_L49_REG0_OFFSET, FIOPAD_FUNC6); /* sda */
        }
        break;
        case FMIO15_ID:
        {
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_N53_REG0_OFFSET, FIOPAD_FUNC6); /* scl */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_J53_REG0_OFFSET, FIOPAD_FUNC6); /* sda */
        }
        break;
        default:
            break;
    }
}

/**
 * @name: FIOPadSetTachoMux
 * @msg: set iopad mux for pwm_in
 * @return {*}
 * @param {u32} pwm_in_id, instance id of tacho
 */
void FIOPadSetTachoMux(u32 pwm_in_id)
{
    switch (pwm_in_id)
    {
        case FTACHO0_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AN57_REG0_OFFSET, FIOPAD_FUNC1);
            break;
        case FTACHO1_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AJ59_REG0_OFFSET, FIOPAD_FUNC1);
            break;
        case FTACHO2_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AG59_REG0_OFFSET, FIOPAD_FUNC1);
            break;
        case FTACHO3_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AE59_REG0_OFFSET, FIOPAD_FUNC1);
            break;
        case FTACHO4_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AC57_REG0_OFFSET, FIOPAD_FUNC1);
            break;
        case FTACHO5_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_BA53_REG0_OFFSET, FIOPAD_FUNC1);
            break;
        case FTACHO6_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_C37_REG0_OFFSET, FIOPAD_FUNC2);
            break;
        case FTACHO7_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_A41_REG0_OFFSET, FIOPAD_FUNC2);
            break;
        case FTACHO8_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_A45_REG0_OFFSET, FIOPAD_FUNC2);
            break;
        case FTACHO9_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_A47_REG0_OFFSET, FIOPAD_FUNC2);
            break;
        case FTACHO10_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_C49_REG0_OFFSET, FIOPAD_FUNC2);
            break;
        case FTACHO11_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_A33_REG0_OFFSET, FIOPAD_FUNC2);
            break;
        case FTACHO12_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_C31_REG0_OFFSET, FIOPAD_FUNC2);
            break;
        case FTACHO13_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AA49_REG0_OFFSET, FIOPAD_FUNC2);
            break;
        case FTACHO14_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AA51_REG0_OFFSET, FIOPAD_FUNC2);
            break;
        case FTACHO15_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_G59_REG0_OFFSET, FIOPAD_FUNC2);
            break;
        default:
            break;
    }
}

/**
 * @name: FIOPadSetUartMux
 * @msg: set iopad mux for uart
 * @return {*}
 * @param {u32} uart_id, instance id of uart
 */
void FIOPadSetUartMux(u32 uart_id)
{
    switch (uart_id)
    {
        case FUART0_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_J37_REG0_OFFSET, FIOPAD_FUNC4);
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_J39_REG0_OFFSET, FIOPAD_FUNC4);
            break;
        case FUART1_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AW51_REG0_OFFSET, FIOPAD_FUNC0);
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AU51_REG0_OFFSET, FIOPAD_FUNC0);
            break;
        case FUART2_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_A47_REG0_OFFSET, FIOPAD_FUNC0);
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_A49_REG0_OFFSET, FIOPAD_FUNC0);
            break;
        case FUART3_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_L37_REG0_OFFSET, FIOPAD_FUNC2);
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_N35_REG0_OFFSET, FIOPAD_FUNC2);
            break;
        default:
            break;
    }
}

/**
 * @name: FIOPadSetUartMux
 * @msg: set iopad mux for i2s
 * @return {*}
 */
void FIOPadSetI2sMux(void)
{
    FIOPadSetFunc(&iopad_ctrl, FIOPAD_L51_REG0_OFFSET, FIOPAD_FUNC6);
    FIOPadSetFunc(&iopad_ctrl, FIOPAD_L49_REG0_OFFSET, FIOPAD_FUNC6);
}

/**
 * @name: FIOPadSetSdMux
 * @msg: set iopad mux for sd
 * @return {*}
 */
void FIOPadSetSdMux(u32 sd_id)
{
    /* set mux for int pin, card_int_n_0 card_int_n_1 */
    switch (sd_id)
    {
        case FSDIF0_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AN49_REG0_OFFSET, FIOPAD_FUNC0);
            break;
        case FSDIF1_ID:
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_N45_REG0_OFFSET, FIOPAD_FUNC5);
            break;
    }
}

/**
 * @name: FIOMuxInit
 * @msg: init io mux
 * @return {void}
 * @note:
 */
_WEAK void FIOMuxInit(void)
{
    FIOPadCfgInitialize(&iopad_ctrl, FIOPadLookupConfig(FIOPAD0_ID));

    return;
}

/**
 * @name: FIOMuxDeInit
 * @msg: deinit io mux
 * @return {void}
 * @note:
 */
_WEAK void FIOMuxDeInit(void)
{
    FIOPadDeInitialize(&iopad_ctrl);
}
