/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

    .global	Reset_Handler
    .section ".start", "ax"
Reset_Handler:
    nop

.text
.weak SVC_Handler
SVC_Handler:
    ret
