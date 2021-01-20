/*
 * File      : startup_gd32f10x_hd.s
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2021, RT-Thread Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-02     iysheng      first implementation
 */

.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.global  Reset_Handler
    .section  .text.Reset_Handler
    .type  Reset_Handler, STT_FUNC
Reset_Handler:
    ldr r1, =_sidata
    ldr r2, =_sdata
    ldr r3, =_edata

    subs r3, r2
    ble fill_bss_start

loop_copy_data:
    subs r3, #4
    ldr r0, [r1,r3]
    str r0, [r2,r3]
    bgt loop_copy_data

fill_bss_start:
    ldr r1, =__bss_start
    ldr r2, =__bss_end
    movs r0, 0
    subs r2, r1
    ble startup_enter

loop_fill_bss:
    subs r2, #4
    str r0, [r1, r2]
    bgt loop_fill_bss

startup_enter:
    bl SystemInit
    bl entry

