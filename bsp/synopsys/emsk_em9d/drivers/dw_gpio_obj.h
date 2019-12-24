/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _DW_GPIO_OBJ_H_
#define _DW_GPIO_OBJ_H_

#include "device/designware/gpio/dw_gpio.h"

/**
 * \name    Designware GPIO Port Bank Control Macros
 * @{
 */
#define USE_DW_GPIO_PORT_A      1
#define USE_DW_GPIO_PORT_B      1
#define USE_DW_GPIO_PORT_C      1
#define USE_DW_GPIO_PORT_D      1
/** @} end of name */

/**
 * \name    Designware GPIO Port Interrupt Available Number Macros
 * @{
 */
#define EMSK_GPIO_A_INT_MAX_COUNT   32
#define EMSK_GPIO_B_INT_MAX_COUNT   0
#define EMSK_GPIO_C_INT_MAX_COUNT   0
#define EMSK_GPIO_D_INT_MAX_COUNT   0
/** @} end of name */

/**
 * \name    Designware GPIO Port Available Bits Macros
 * @{
 */
#define EMSK_GPIO_A_VALID_MASK      DW_GPIO_MASK_ALL
#define EMSK_GPIO_B_VALID_MASK      DW_GPIO_MASK_ALL
#define EMSK_GPIO_C_VALID_MASK      DW_GPIO_MASK_ALL
#define EMSK_GPIO_D_VALID_MASK      DW_GPIO_MASK_ALL
/** @} end of name */

#ifdef __cplusplus
extern "C" {
#endif

extern void dw_gpio_all_install(void);

#ifdef __cplusplus
}
#endif

#endif /* _DW_GPIO_OBJ_H_*/
