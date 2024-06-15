/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-01-11   HPMICRO     First version
 * 2022-03-22   zhangjun    add GET_PIN
 */
#ifndef DRV_GPIO_H
#define DRV_GPIO_H

#define __HPM_PORT(port) IOC_PAD_P##port##00
#define GET_PIN(PORTx,PIN)  (__HPM_PORT(PORTx) + PIN)

int rt_hw_pin_init(void);


#endif /* DRV_GPIO_H */
