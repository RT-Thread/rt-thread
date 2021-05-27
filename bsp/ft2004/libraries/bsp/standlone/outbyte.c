/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 17:54:32
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "ft_parameters.h"
#include "ft_uart_hw.h"

void outbyte(char byte)
{
    FUart_SendByte(FT_STDOUT_BASEADDRESS, byte);
}
