/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-2-7        YCHuang12        First version
*
******************************************************************************/

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

typedef enum
{
    NU_PA,
    NU_PB,
    NU_PC,
    NU_PD,
    NU_PE,
    NU_PF,
    NU_PG,
    NU_PORT_CNT,
} nu_gpio_port;

#define NU_GET_PININDEX(port, pin)        ((port)*16+(pin))
#define NU_GET_PINS(rt_pin_index)         ((rt_pin_index) & 0x0000000F)
#define NU_GET_PORT(rt_pin_index)         (((rt_pin_index)>>4) & 0x0000000F)
#define NU_GET_PIN_MASK(nu_gpio_pin)      (1 << (nu_gpio_pin))

#endif //__DRV_GPIO_H__
