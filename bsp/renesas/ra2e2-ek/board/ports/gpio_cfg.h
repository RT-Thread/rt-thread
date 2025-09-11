/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-01-19     Sherman           first version
 */

/* Number of IRQ channels on the device */
#define RA_IRQ_MAX  8

/* PIN to IRQx table */
#define PIN2IRQX_TABLE                      \
{                                           \
    switch (pin)                            \
    {                                       \
    case BSP_IO_PORT_03_PIN_00:             \
    case BSP_IO_PORT_04_PIN_00:             \
        return 0;                           \
    case BSP_IO_PORT_01_PIN_01:             \
    case BSP_IO_PORT_01_PIN_12:             \
    case BSP_IO_PORT_02_PIN_05:             \
        return 1;                           \
    case BSP_IO_PORT_01_PIN_00:             \
    case BSP_IO_PORT_09_PIN_14:             \
        return 2;                           \
    case BSP_IO_PORT_01_PIN_10:             \
        return 3;                           \
    case BSP_IO_PORT_01_PIN_02:             \
    case BSP_IO_PORT_01_PIN_11:             \
        return 4;                           \
    case BSP_IO_PORT_01_PIN_08:             \
    case BSP_IO_PORT_04_PIN_01:             \
        return 5;                           \
    case BSP_IO_PORT_01_PIN_03:             \
        return 6;                           \
    case BSP_IO_PORT_00_PIN_15:             \
    case BSP_IO_PORT_01_PIN_09:             \
        return 7;                           \
    default  :                              \
        return -1;                          \
    }                                       \
}
