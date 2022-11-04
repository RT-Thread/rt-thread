/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     liYony       first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#define PIN_USERDATA_END {-1,0}

#ifdef __cplusplus
extern "C" {
#endif

#define __CH32_PORT(port)  GPIO##port##_BASE
#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__CH32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)

int rt_hw_pin_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */
