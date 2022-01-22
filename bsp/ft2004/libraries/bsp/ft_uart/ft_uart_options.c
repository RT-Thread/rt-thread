/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-05-24 10:47:33
 * @Description:  This files is for uart option setting
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_uart.h"
#include "ft_uart_hw.h"
#include "ft_types.h"
/************************** Variable Definitions ****************************/
/*
 * The following data type is a map from an option to the offset in the
 * register to which it belongs as well as its bit mask in that register.
 */
typedef struct
{
    u32 Option;
    u32 RegisterOffset;
    u32 Mask;
} Mapping;

static Mapping OptionTable[] = {
    {FUART_OPTION_UARTEN, UARTCR_OFFSET, UARTCR_UARTEN},
    {FUART_OPTION_RXEN, UARTCR_OFFSET, UARTCR_RXE},
    {FUART_OPTION_TXEN, UARTCR_OFFSET, UARTCR_TXE},
    {FUART_OPTION_FIFOEN, UARTLCR_H_OFFSET, UARTLCR_H_FEN}};

#define FT_UART_NUM_OPITIONS (sizeof(OptionTable) / sizeof(Mapping))

void FUart_SetOptions(Ft_Uart *UartPtr, u32 Options)
{
    u32 Index;
    u32 RegValue;
    Ft_assertVoid(UartPtr != NULL);
    Ft_assertVoid(UartPtr->IsReady == FT_COMPONENT_IS_READLY);

    for (Index = 0; Index < FT_UART_NUM_OPITIONS; Index++)
    {
        RegValue = FT_UART_ReadReg(UartPtr->Config.BaseAddress, OptionTable[Index].RegisterOffset);

        if ((Options & OptionTable[Index].Option) != (u32)(0))
        {
            RegValue |= OptionTable[Index].Mask;
        }
        else
        {
            RegValue &= ~OptionTable[Index].Mask;
        }

        FT_UART_WriteReg(UartPtr->Config.BaseAddress, OptionTable[Index].RegisterOffset, RegValue);
    }
}

void FUart_SetSpecificOptions(Ft_Uart *UartPtr, u32 Options)
{
    u32 Index;
    u32 RegValue;
    Ft_assertVoid(UartPtr != NULL);

    for (Index = 0; Index < FT_UART_NUM_OPITIONS; Index++)
    {
        if ((Options & OptionTable[Index].Option) == (u32)(0))
        {
            continue;
        }

        RegValue = FT_UART_ReadReg(UartPtr->Config.BaseAddress, OptionTable[Index].RegisterOffset);

        /* set specific options */
        RegValue |= OptionTable[Index].Mask;
        FT_UART_WriteReg(UartPtr->Config.BaseAddress, OptionTable[Index].RegisterOffset, RegValue);
    }
}

void FUart_ClearSpecificOptions(FT_IN Ft_Uart *UartPtr, FT_IN u32 Options)
{
    u32 Index;
    u32 RegValue;
    Ft_assertVoid(UartPtr != NULL);

    for (Index = 0; Index < FT_UART_NUM_OPITIONS; Index++)
    {
        if ((Options & OptionTable[Index].Option) == (u32)(0))
        {
            continue;
        }

        RegValue = FT_UART_ReadReg(UartPtr->Config.BaseAddress, OptionTable[Index].RegisterOffset);

        /* remove specific options */
        RegValue &= ~OptionTable[Index].Mask;
        FT_UART_WriteReg(UartPtr->Config.BaseAddress, OptionTable[Index].RegisterOffset, RegValue);
    }
}
