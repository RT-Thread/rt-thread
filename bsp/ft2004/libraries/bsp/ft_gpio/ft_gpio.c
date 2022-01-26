/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-27 17:55:31
 * @LastEditTime: 2021-05-25 16:43:31
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_gpio.h"
#include "ft_gpio_hw.h"
#include "ft_assert.h"
#include "ft_debug.h"

#define GPIO_MAX_PIN 7
#define GPIO_MAX_CTRL_ID 1

void FGpio_SetGroupModeA(FT_IN u32 ctrlId, FT_IN u8 pin, FT_IN u32 mode)
{
    u32 RegVal;
    Ft_assertNoneReturn(ctrlId <= GPIO_MAX_CTRL_ID);
    Ft_assertNoneReturn(pin <= GPIO_MAX_PIN);

    RegVal = FGpioA_ReadReg(ctrlId, GPIO_INTEN);
    switch (mode)
    {
    case GPIO_MODE_GPIO:
        RegVal &= ~(1 << pin);
        break;
    case GPIO_MODE_INT:
        RegVal |= (1 << pin);
        break;
    default:
        Ft_assertNoneReturn(0);
        break;
    }

    FGpioA_WriteReg(ctrlId, GPIO_INTEN, RegVal);
    return;
}

static void FGpio_SetPinInOutA(FT_IN u32 ctrlId, FT_IN u8 pin, FT_IN u8 inOut)
{
    u32 RegVal;
    Ft_assertNoneReturn(ctrlId <= GPIO_MAX_CTRL_ID);
    Ft_assertNoneReturn(pin <= GPIO_MAX_PIN);

    RegVal = FGpioA_ReadReg(ctrlId, GPIO_SWPORTA_DDR);
    if (inOut != (RegVal & (0x1 << pin)))
    {
        if (GPIO_INPUT == inOut)
        {
            RegVal &= ~(0x1 << pin);
        }
        else if (GPIO_OUTPUT == inOut)
        {
            RegVal |= (0x1 << pin);
        }
        else
        {
            Ft_assertNoneReturn(0);
        }

        FGpioA_WriteReg(ctrlId, GPIO_SWPORTA_DDR, RegVal);
    }

    return;
}

u32 FGpio_ReadPinA(FT_IN u32 ctrlId, FT_IN u8 pin)
{
    u32 RegVal;
    u32 OnOff;
    Ft_assertNoneReturn(ctrlId <= GPIO_MAX_CTRL_ID);
    Ft_assertNoneReturn(pin <= GPIO_MAX_PIN);

    FGpio_SetPinInOutA(ctrlId, pin, GPIO_INPUT);
    RegVal = FGpioA_ReadReg(ctrlId, GPIO_EXT_PORTA);
    OnOff = (RegVal & (0x1 << pin)) ? GPIO_ON : GPIO_OFF;
    return OnOff;
}

void FGpio_WritePinA(FT_IN u32 ctrlId, FT_IN u8 pin, FT_IN u8 onOff)
{
    u32 RegVal;
    Ft_assertNoneReturn(ctrlId <= GPIO_MAX_CTRL_ID);
    Ft_assertNoneReturn(pin <= GPIO_MAX_PIN);
    Ft_assertNoneReturn((onOff == GPIO_OFF) || (onOff == GPIO_ON));

    FGpio_SetPinInOutA(ctrlId, pin, GPIO_OUTPUT);
    RegVal = FGpioA_ReadReg(ctrlId, GPIO_SWPORTA_DR);
    if (GPIO_OFF == onOff)
    {
        RegVal &= ~(1 << pin);
    }
    else
    {
        RegVal |= (1 << pin);
    }
    FGpioA_WriteReg(ctrlId, GPIO_SWPORTA_DR, RegVal);
    return;
}
