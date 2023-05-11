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
 * FilePath: fiopad_config.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:29
 * Description:  This file is for io-pad function definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/11/5    init commit
 * 1.1   zhugengyu  2022/3/21    adopt to lastest tech spec.
 */

/***************************** Include Files *********************************/
#include "fiopad.h"
#include "fparameters.h"
#include "fdebug.h"
#include "fpinctrl.h"
#include "fassert.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FIOPAD_DEBUG_TAG "FIOPAD-CFG"
#define FIOPAD_ERROR(format, ...)   FT_DEBUG_PRINT_E(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOPAD_WARN(format, ...)    FT_DEBUG_PRINT_W(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOPAD_INFO(format, ...)    FT_DEBUG_PRINT_I(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOPAD_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

/*****************************************************************************/
/**
 * @name: FIOPadSetSpimMux
 * @msg: set iopad mux for spim
 * @return {*}
 * @param {u32} spim_id, instance id of spi
 */
void FIOPadSetSpimMux(u32 spim_id)
{
    if (FSPI2_ID == spim_id)
    {
        FPinSetFunc(FIOPAD_A29, FPIN_FUNC0); /* sclk */
        FPinSetFunc(FIOPAD_C29, FPIN_FUNC0); /* txd */
        FPinSetFunc(FIOPAD_C27, FPIN_FUNC0); /* rxd */
        FPinSetFunc(FIOPAD_A27, FPIN_FUNC0); /* csn0 */
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
    if (FGPIO3_ID == gpio_id)
    {
        switch (pin_id)
        {
            case 3: /* gpio 3-a-3 */
                FPinSetFunc(FIOPAD_A29, FPIN_FUNC6);
                break;
            case 4: /* gpio 3-a-4 */
                FPinSetFunc(FIOPAD_C29, FPIN_FUNC6);
                break;
            case 5: /* gpio 3-a-5 */
                FPinSetFunc(FIOPAD_C27, FPIN_FUNC6);
                break;
            case 6: /* gpio 3-a-6 */
                FPinSetFunc(FIOPAD_A27, FPIN_FUNC6);
                break;
            case 7: /* gpio 3-a-7 */ /*cannot use this pin*/
                FPinSetFunc(FIOPAD_AJ49, FPIN_FUNC6);
                break;
            case 8: /* gpio 3-a-8 */
                FPinSetFunc(FIOPAD_AL45, FPIN_FUNC6);
                break;
            case 9: /* gpio 3-a-9 */
                FPinSetFunc(FIOPAD_AL43, FPIN_FUNC6);
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
                FPinSetFunc(FIOPAD_W47, FPIN_FUNC6);
                break;
            case 9: /* gpio 4-a-9 */
                FPinSetFunc(FIOPAD_U49, FPIN_FUNC6);
                break;
            case 10: /* gpio 4-a-10 */
                FPinSetFunc(FIOPAD_AE45, FPIN_FUNC6);
                break;
            case 11: /* gpio 4-a-11 */
                FPinSetFunc(FIOPAD_AC45, FPIN_FUNC6);
                break;
            case 12: /* gpio 4-a-12 */
                FPinSetFunc(FIOPAD_AE43, FPIN_FUNC6);
                break;
            case 13: /* gpio 4-a-13 */
                FPinSetFunc(FIOPAD_AA43, FPIN_FUNC6);
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
        FPinSetFunc(FIOPAD_A37, FPIN_FUNC0); /* can0-tx: func 0 */
        FPinSetFunc(FIOPAD_A39, FPIN_FUNC0); /* can0-rx: func 0 */
    }
    else if (can_id == FCAN1_ID)
    {
		/* can1 */
        FPinSetFunc(FIOPAD_A41, FPIN_FUNC0); /* can1-tx: func 0 */
        FPinSetFunc(FIOPAD_C41, FPIN_FUNC0); /* can1-rx: func 0 */
    }
    else
    {
        FIOPAD_ERROR("can id is error.\r\n");
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
        FPinSetFunc(FIOPAD_AR51, FPIN_FUNC0);
    }
    else if (cs_id == FQSPI_CS_1)
    {
        FPinSetFunc(FIOPAD_AR45, FPIN_FUNC0);
    }
    else if (cs_id == FQSPI_CS_2)
    {
        FPinSetFunc(FIOPAD_C33, FPIN_FUNC5);
    }
    else if (cs_id == FQSPI_CS_3)
    {
        FPinSetFunc(FIOPAD_A33, FPIN_FUNC5);
    }
    else
    {
        FIOPAD_ERROR("can id is error.\r\n");
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
                FPinSetFunc(FIOPAD_AL55, FPIN_FUNC1); /* PWM0_OUT: func 1 */
            }
            if (pwm_channel == 1)
            {
                FPinSetFunc(FIOPAD_AJ53, FPIN_FUNC1); /* PWM1_OUT: func 1 */
            }
            break;

        case FPWM1_ID:
            if (pwm_channel == 0)
            {
                FPinSetFunc(FIOPAD_AG53, FPIN_FUNC1); /* PWM2_OUT: func 1 */
            }
            if (pwm_channel == 1)
            {
                FPinSetFunc(FIOPAD_AC55, FPIN_FUNC1); /* PWM3_OUT: func 1 */
            }
            break;

        case FPWM2_ID:
            if (pwm_channel == 0)
            {
                FPinSetFunc(FIOPAD_BA51, FPIN_FUNC1); /* PWM4_OUT: func 1 */
            }
            if (pwm_channel == 1)
            {
                FPinSetFunc(FIOPAD_C35, FPIN_FUNC2); /* PWM5_OUT: func 2 */
            }
            break;

        case FPWM3_ID:
            if (pwm_channel == 0)
            {
                FPinSetFunc(FIOPAD_A33, FPIN_FUNC2); /* PWM6_OUT: func 2 */
            }
            if (pwm_channel == 1)
            {
                FPinSetFunc(FIOPAD_A39, FPIN_FUNC2); /* PWM7_OUT: func 2 */
            }
            break;

        case FPWM4_ID:
            if (pwm_channel == 0)
            {
                FPinSetFunc(FIOPAD_C41, FPIN_FUNC2); /* PWM8_OUT: func 2 */
            }
            if (pwm_channel == 1)
            {
                FPinSetFunc(FIOPAD_A45, FPIN_FUNC2); /* PWM9_OUT: func 2 */
            }
            break;

        case FPWM5_ID:
            if (pwm_channel == 0)
            {
                FPinSetFunc(FIOPAD_A47, FPIN_FUNC2); /* PWM10_OUT: func 2 */
            }
            if (pwm_channel == 1)
            {
                FPinSetFunc(FIOPAD_C29, FPIN_FUNC2); /* PWM11_OUT: func 2 */
            }
            break;

        case FPWM6_ID:
            if (pwm_channel == 0)
            {
                FPinSetFunc(FIOPAD_A27, FPIN_FUNC2); /* PWM12_OUT: func 2 */
            }
            if (pwm_channel == 1)
            {
                FPinSetFunc(FIOPAD_J35, FPIN_FUNC3); /* PWM13_OUT: func 3 */
            }
            break;

        case FPWM7_ID:
            if (pwm_channel == 0)
            {
                FPinSetFunc(FIOPAD_E39, FPIN_FUNC3); /* PWM14_OUT: func 3 */
            }
            if (pwm_channel == 1)
            {
                FPinSetFunc(FIOPAD_C39, FPIN_FUNC3); /* PWM15_OUT: func 3 */
            }
            break;

        default:
            FIOPAD_ERROR("pwm id is error.\r\n");
            break;
    }
}


/**
 * @name: FIOPadSetAdcMux
 * @msg: set iopad mux for adc
 * @return {*}
 * @param {u32} adc_id, id of adc instance
 * @param {u32} adc_channel, id of adc channel
 */
void FIOPadSetAdcMux(u32 adc_id, u32 adc_channel)
{

    if (adc_id == FADC0_ID)
    {
        switch (adc_channel)
        {
            case FADC_CHANNEL_0:
                FPinSetFunc(FIOPAD_R47, FPIN_FUNC7); /* adc0-0: func 7 */
                break;
            case FADC_CHANNEL_1:
                FPinSetFunc(FIOPAD_R45, FPIN_FUNC7); /* adc0-1: func 7 */
                break;
            case FADC_CHANNEL_2:
                FPinSetFunc(FIOPAD_N47, FPIN_FUNC7); /* adc0-2: func 7 */
                break;
            case FADC_CHANNEL_3:
                FPinSetFunc(FIOPAD_N51, FPIN_FUNC7); /* adc0-3: func 7 */
                break;
            case FADC_CHANNEL_4:
                FPinSetFunc(FIOPAD_L51, FPIN_FUNC7); /* adc0-4: func 7 */
                break;
            case FADC_CHANNEL_5:
                FPinSetFunc(FIOPAD_J51, FPIN_FUNC7); /* adc0-5: func 7 */
                break;
            case FADC_CHANNEL_6:
                FPinSetFunc(FIOPAD_J41, FPIN_FUNC7); /* adc0-6: func 7 */
                break;
            case FADC_CHANNEL_7:
                FPinSetFunc(FIOPAD_E43, FPIN_FUNC7); /* adc0-7: func 7 */
                break;
            default:
                FIOPAD_ERROR("adc %d channel %d is error.\r\n", adc_id, adc_channel);
                break;
        }
    }
    else
    {
        FIOPAD_ERROR("adc %d channel %d is error.\r\n", adc_id, adc_channel);
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
            FPinSetFunc(FIOPAD_A37, FPIN_FUNC5); /* scl */
            FPinSetFunc(FIOPAD_A39, FPIN_FUNC5); /* sda */
        }
        break;
        case FMIO1_ID:
        {
            FPinSetFunc(FIOPAD_A41, FPIN_FUNC5); /* scl */
            FPinSetFunc(FIOPAD_C41, FPIN_FUNC5); /* sda */
        }
        break;
        case FMIO2_ID:
        {
            FPinSetFunc(FIOPAD_A43, FPIN_FUNC5); /* scl */
            FPinSetFunc(FIOPAD_A45, FPIN_FUNC5); /* sda */
        }
        break;
        case FMIO3_ID:
        {
            FPinSetFunc(FIOPAD_BA51, FPIN_FUNC4); /* scl */
            FPinSetFunc(FIOPAD_BA49, FPIN_FUNC4); /* sda */
        }
        break;
        case FMIO4_ID:
        {
            FPinSetFunc(FIOPAD_R55, FPIN_FUNC4); /* scl */
            FPinSetFunc(FIOPAD_U55, FPIN_FUNC4); /* sda */
        }
        break;
        case FMIO5_ID:
        {
            FPinSetFunc(FIOPAD_W45, FPIN_FUNC4); /* scl */
            FPinSetFunc(FIOPAD_U53, FPIN_FUNC4); /* sda */
        }
        break;
        case FMIO6_ID:
        {
            FPinSetFunc(FIOPAD_AA53, FPIN_FUNC4); /* scl */
            FPinSetFunc(FIOPAD_AA55, FPIN_FUNC4); /* sda */
        }
        break;
        case FMIO7_ID:
        {
            FPinSetFunc(FIOPAD_A35, FPIN_FUNC4); /* scl */
            FPinSetFunc(FIOPAD_C35, FPIN_FUNC4); /* sda */
        }
        break;
        case FMIO8_ID:
        {
            FPinSetFunc(FIOPAD_AA45, FPIN_FUNC4); /* scl */
            FPinSetFunc(FIOPAD_W45, FPIN_FUNC4); /* sda */
        }
        break;
        case FMIO9_ID:
        {
            FPinSetFunc(FIOPAD_AA47, FPIN_FUNC4); /* scl */
            FPinSetFunc(FIOPAD_U45, FPIN_FUNC4); /* sda */
        }
        break;
        case FMIO10_ID:
        {
            FPinSetFunc(FIOPAD_C45, FPIN_FUNC5); /* scl */
            FPinSetFunc(FIOPAD_A47, FPIN_FUNC5); /* sda */
        }
        break;
        case FMIO11_ID:
        {
            FPinSetFunc(FIOPAD_N23, FPIN_FUNC3); /* scl */
            FPinSetFunc(FIOPAD_L25, FPIN_FUNC3); /* sda */
        }
        break;
        case FMIO12_ID:
        {
            FPinSetFunc(FIOPAD_E37, FPIN_FUNC3); /* scl */
            FPinSetFunc(FIOPAD_L41, FPIN_FUNC3); /* sda */
        }
        break;
        case FMIO13_ID:
        {
            FPinSetFunc(FIOPAD_J45, FPIN_FUNC6); /* scl */
            FPinSetFunc(FIOPAD_N45, FPIN_FUNC6); /* sda */
        }
        break;
        case FMIO14_ID:
        {
            FPinSetFunc(FIOPAD_L47, FPIN_FUNC6); /* scl */
            FPinSetFunc(FIOPAD_L45, FPIN_FUNC6); /* sda */
        }
        break;
        case FMIO15_ID:
        {
            FPinSetFunc(FIOPAD_N49, FPIN_FUNC6); /* scl */
            FPinSetFunc(FIOPAD_J49, FPIN_FUNC6); /* sda */
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
            FPinSetFunc(FIOPAD_AN53, FPIN_FUNC1);
            break;
        case FTACHO1_ID:
            FPinSetFunc(FIOPAD_AJ55, FPIN_FUNC1);
            break;
        case FTACHO2_ID:
            FPinSetFunc(FIOPAD_AG55, FPIN_FUNC1);
            break;
        case FTACHO3_ID:
            FPinSetFunc(FIOPAD_AE55, FPIN_FUNC1);
            break;
        case FTACHO4_ID:
            FPinSetFunc(FIOPAD_AC53, FPIN_FUNC1);
            break;
        case FTACHO5_ID:
            FPinSetFunc(FIOPAD_BA49, FPIN_FUNC1);
            break;
        case FTACHO6_ID:
            FPinSetFunc(FIOPAD_C33, FPIN_FUNC2);
            break;
        case FTACHO7_ID:
            FPinSetFunc(FIOPAD_A37, FPIN_FUNC2);
            break;
        case FTACHO8_ID:
            FPinSetFunc(FIOPAD_A41, FPIN_FUNC2);
            break;
        case FTACHO9_ID:
            FPinSetFunc(FIOPAD_A43, FPIN_FUNC2);
            break;
        case FTACHO10_ID:
            FPinSetFunc(FIOPAD_C45, FPIN_FUNC2);
            break;
        case FTACHO11_ID:
            FPinSetFunc(FIOPAD_A29, FPIN_FUNC2);
            break;
        case FTACHO12_ID:
            FPinSetFunc(FIOPAD_C27, FPIN_FUNC2);
            break;
        case FTACHO13_ID:
            FPinSetFunc(FIOPAD_AA45, FPIN_FUNC2);
            break;
        case FTACHO14_ID:
            FPinSetFunc(FIOPAD_AA47, FPIN_FUNC2);
            break;
        case FTACHO15_ID:
            FPinSetFunc(FIOPAD_G55, FPIN_FUNC2);
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
            FPinSetFunc(FIOPAD_J33, FPIN_FUNC4);
            FPinSetFunc(FIOPAD_J35, FPIN_FUNC4);
            break;
        case FUART1_ID:
            FPinSetFunc(FIOPAD_AW47, FPIN_FUNC0);
            FPinSetFunc(FIOPAD_AU47, FPIN_FUNC0);
            break;
        case FUART2_ID:
            FPinSetFunc(FIOPAD_A43, FPIN_FUNC0);
            FPinSetFunc(FIOPAD_A45, FPIN_FUNC0);
            break;
        case FUART3_ID:
            FPinSetFunc(FIOPAD_L33, FPIN_FUNC2);
            FPinSetFunc(FIOPAD_N31, FPIN_FUNC2);
            break;
        default:
            break;
    }
}