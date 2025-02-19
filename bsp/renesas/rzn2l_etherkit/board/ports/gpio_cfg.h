/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2024-03-11    Wangyuqiang   first version
 */

/* Number of IRQ channels on the device */
#define RA_IRQ_MAX  16

/* PIN to IRQx table */
#define PIN2IRQX_TABLE                      \
{                                           \
    switch (pin)                            \
    {                                       \
    case BSP_IO_PORT_00_PIN_1:             \
    case BSP_IO_PORT_09_PIN_2:             \
    case BSP_IO_PORT_18_PIN_3:             \
        return 0;                           \
    case BSP_IO_PORT_00_PIN_3:             \
    case BSP_IO_PORT_07_PIN_4:             \
    case BSP_IO_PORT_18_PIN_4:             \
        return 1;                           \
    case BSP_IO_PORT_01_PIN_2:             \
        return 2;                           \
    case BSP_IO_PORT_01_PIN_4:             \
        return 3;                           \
    case BSP_IO_PORT_02_PIN_0:             \
    case BSP_IO_PORT_22_PIN_2:             \
        return 4;                           \
    case BSP_IO_PORT_03_PIN_5:             \
    case BSP_IO_PORT_13_PIN_2:             \
        return 5;                           \
    case BSP_IO_PORT_14_PIN_2:             \
    case BSP_IO_PORT_21_PIN_5:             \
        return 6;                           \
    case BSP_IO_PORT_16_PIN_3:             \
        return 7;                           \
    case BSP_IO_PORT_03_PIN_6:             \
    case BSP_IO_PORT_16_PIN_6:             \
        return 8;                           \
    case BSP_IO_PORT_03_PIN_7:             \
    case BSP_IO_PORT_21_PIN_6:             \
        return 9;                           \
    case BSP_IO_PORT_04_PIN_4:             \
    case BSP_IO_PORT_18_PIN_1:             \
    case BSP_IO_PORT_21_PIN_7:             \
        return 10;                          \
    case BSP_IO_PORT_10_PIN_4:             \
    case BSP_IO_PORT_18_PIN_6:             \
        return 11;                          \
    case BSP_IO_PORT_05_PIN_0:             \
    case BSP_IO_PORT_05_PIN_4:             \
    case BSP_IO_PORT_05_PIN_6:             \
        return 12;                          \
    case BSP_IO_PORT_00_PIN_4:             \
    case BSP_IO_PORT_00_PIN_7:             \
    case BSP_IO_PORT_05_PIN_1:             \
        return 13;                          \
    case BSP_IO_PORT_02_PIN_2:             \
    case BSP_IO_PORT_03_PIN_0:             \
    case BSP_IO_PORT_05_PIN_2:             \
        return 14;                          \
    case BSP_IO_PORT_02_PIN_3:             \
    case BSP_IO_PORT_05_PIN_3:             \
    case BSP_IO_PORT_22_PIN_0:             \
        return 15;                          \
    default  :                              \
        return -1;                          \
    }                                       \
}
