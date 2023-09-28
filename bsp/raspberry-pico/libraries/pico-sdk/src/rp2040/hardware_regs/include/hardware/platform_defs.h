/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_PLATFORM_DEFS_H
#define _HARDWARE_PLATFORM_DEFS_H

// This header is included from C and assembler - intended mostly for #defines; guard other stuff with #ifdef __ASSEMBLER__

#ifndef _u
#ifdef __ASSEMBLER__
#define _u(x) x
#else
#define _u(x) x ## u
#endif
#endif

#define NUM_CORES _u(2)
#define NUM_DMA_CHANNELS _u(12)
#define NUM_DMA_TIMERS _u(4)
#define NUM_IRQS _u(32)
#define NUM_USER_IRQS _u(6)
#define NUM_PIOS _u(2)
#define NUM_PIO_STATE_MACHINES _u(4)
#define NUM_PWM_SLICES _u(8)
#define NUM_SPIN_LOCKS _u(32)
#define NUM_UARTS _u(2)
#define NUM_I2CS _u(2)
#define NUM_SPIS _u(2)
#define NUM_TIMERS _u(4)
#define NUM_ADC_CHANNELS _u(5)

#define NUM_BANK0_GPIOS _u(30)
#define NUM_QSPI_GPIOS _u(6)

#define PIO_INSTRUCTION_COUNT _u(32)

// PICO_CONFIG: XOSC_KHZ, The crystal oscillator frequency in kHz, type=int, default=12000, advanced=true, group=hardware_base
// NOTE:  The system and USB clocks are generated from the frequency using two PLLs.
// If you override this define, or SYS_CLK_KHZ/USB_CLK_KHZ below, you will *also* need to add your own adjusted PLL set-up defines to
// override the defaults which live in src/rp2_common/hardware_clocks/include/hardware/clocks.h
// Please see the comments there about calculating the new PLL setting values.
#ifndef XOSC_KHZ
#define XOSC_KHZ _u(12000)
#endif

// PICO_CONFIG: SYS_CLK_KHZ, The system operating frequency in kHz, type=int, default=125000, advanced=true, group=hardware_base
#ifndef SYS_CLK_KHZ
#define SYS_CLK_KHZ _u(125000)
#endif

// PICO_CONFIG: USB_CLK_KHZ, USB clock frequency. Must be 48MHz for the USB interface to operate correctly, type=int, default=48000, advanced=true, group=hardware_base
#ifndef USB_CLK_KHZ
#define USB_CLK_KHZ _u(48000)
#endif

// For backwards compatibility define XOSC_MHZ if the frequency is indeed an integer number of Mhz.
#if defined(XOSC_KHZ) && !defined(XOSC_MHZ) && (XOSC_KHZ % 1000 == 0)
#define XOSC_MHZ (XOSC_KHZ / 1000)
#endif

// For backwards compatibility define SYS_CLK_MHZ if the frequency is indeed an integer number of Mhz.
#if defined(SYS_CLK_KHZ) && !defined(SYS_CLK_MHZ) && (SYS_CLK_KHZ % 1000 == 0)
#define SYS_CLK_MHZ (SYS_CLK_KHZ / 1000)
#endif

// For backwards compatibility define USB_CLK_MHZ if the frequency is indeed an integer number of Mhz.
#if defined(USB_CLK_KHZ) && !defined(USB_CLK_MHZ) && (USB_CLK_KHZ % 1000 == 0)
#define USB_CLK_MHZ (USB_CLK_KHZ / 1000)
#endif

#define FIRST_USER_IRQ (NUM_IRQS - NUM_USER_IRQS)
#define VTABLE_FIRST_IRQ 16

#endif

