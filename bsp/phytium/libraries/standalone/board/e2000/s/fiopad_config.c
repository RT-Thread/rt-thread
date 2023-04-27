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
#include "fpinctrl.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

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