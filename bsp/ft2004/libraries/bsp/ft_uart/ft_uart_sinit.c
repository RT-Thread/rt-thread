/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 13:44:56
 * @Description:  This files is for uart static init
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_uart.h"
#include "ft_parameters.h"

extern FUart_Config_t FUart_Config_tTable[FT_UART_NUM];

/**
 * @name: Ft_Uart_LookupConfig
 * @msg:  获取串口的基本配置
 * @param {u16} InstanceId FT_UARTX_ID
 * @return {*}
 */
FUart_Config_t *FUart_LookupConfig(u32 InstanceId)
{
    FUart_Config_t *CfgPtr = NULL;
    u32 Index;

    for (Index = 0; Index < (u32)FT_UART_NUM; Index++)
    {
        if (FUart_Config_tTable[Index].InstanceId == InstanceId)
        {
            CfgPtr = &FUart_Config_tTable[Index];
            break;
        }
    }

    return (FUart_Config_t *)CfgPtr;
}
