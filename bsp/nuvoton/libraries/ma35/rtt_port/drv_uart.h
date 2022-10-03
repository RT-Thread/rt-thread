/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-2-7        Wayne        First version
*
******************************************************************************/

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include <rtdevice.h>
#include "board.h"

rt_err_t rt_hw_uart_init(void);
void nu_uart_set_rs485aud(struct rt_serial_device *serial, rt_bool_t bRTSActiveLowLevel);

#endif /* __DRV_UART_H__ */
