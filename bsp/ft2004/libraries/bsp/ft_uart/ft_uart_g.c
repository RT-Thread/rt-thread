/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 13:42:30
 * @Description:  This files is for uart config
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_uart.h"
#include "ft_parameters.h"

FUart_Config_t FUart_Config_tTable[FT_UART_NUM] = {
    {FT_UART0_ID,
     FT_UART0_BASE_ADDR,
     FT_UART0_CLK_FREQ_HZ,
     38},
    {FT_UART1_ID,
     FT_UART1_BASE_ADDR,
     FT_UART1_CLK_FREQ_HZ,
     39},
    {FT_UART2_ID,
     FT_UART2_BASE_ADDR,
     FT_UART2_CLK_FREQ_HZ,
     40},
    {FT_UART3_ID,
     FT_UART3_BASE_ADDR,
     FT_UART3_CLK_FREQ_HZ,
     41}};
