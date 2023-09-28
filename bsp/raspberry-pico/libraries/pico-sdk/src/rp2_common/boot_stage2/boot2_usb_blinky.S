/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/asm_helper.S"

// Stub second stage which calls into USB bootcode, with parameters.
// USB boot takes two parameters:
// - A GPIO mask for activity LED -- if mask is 0, don't touch GPIOs at all
// - A mask of interfaces to disable. Bit 0 disables MSC, bit 1 disables PICOBoot
// The bootrom passes 0 for both of these parameters, but user code (or this
// second stage) can pass anything.

#define USB_BOOT_MSD_AND_PICOBOOT 0x0
#define USB_BOOT_MSD_ONLY 0x2
#define USB_BOOT_PICOBOOT_ONLY 0x1

// Config
#define ACTIVITY_LED 0
#define BOOT_MODE USB_BOOT_MSD_AND_PICOBOOT

pico_default_asm_setup

.section .text

regular_func _stage2_boot
    movs r7, #0x14               // Pointer to _well_known pointer table in ROM
    ldrh r0, [r7, #0]           // Offset 0 is 16 bit pointer to function table
    ldrh r7, [r7, #4]           // Offset 4 is 16 bit pointer to table lookup routine
    ldr r1, =('U' | ('B' << 8)) // Symbol for USB Boot
    blx r7
    cmp r0, #0
    beq dead

    mov r7, r0
    ldr r0, =(1u << ACTIVITY_LED) // Mask of which GPIO (or GPIOs) to use
    movs r1, #BOOT_MODE
    blx r7

dead:
    wfi
    b dead

.global literals
literals:
.ltorg

.end
