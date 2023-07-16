/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
#ifndef __DRIVERLIB__H_
#define __DRIVERLIB__H_

/* Common Modules */
#include <ti/devices/msp432e4/inc/msp.h>
#include <ti/devices/msp432e4/driverlib/adc.h>
#include <ti/devices/msp432e4/driverlib/aes.h>
#include <ti/devices/msp432e4/driverlib/can.h>
#include <ti/devices/msp432e4/driverlib/comp.h>
#include <ti/devices/msp432e4/driverlib/cpu.h>
#include <ti/devices/msp432e4/driverlib/crc.h>
#include <ti/devices/msp432e4/driverlib/debug.h>
#include <ti/devices/msp432e4/driverlib/des.h>
#include <ti/devices/msp432e4/driverlib/eeprom.h>
#include <ti/devices/msp432e4/driverlib/emac.h>
#include <ti/devices/msp432e4/driverlib/epi.h>
#include <ti/devices/msp432e4/driverlib/flash.h>
#include <ti/devices/msp432e4/driverlib/fpu.h>
#include <ti/devices/msp432e4/driverlib/gpio.h>
#include <ti/devices/msp432e4/driverlib/hibernate.h>
#include <ti/devices/msp432e4/driverlib/i2c.h>
#include <ti/devices/msp432e4/driverlib/interrupt.h>
#include <ti/devices/msp432e4/driverlib/mpu.h>
#include <ti/devices/msp432e4/driverlib/pin_map.h>
#include <ti/devices/msp432e4/driverlib/pwm.h>
#include <ti/devices/msp432e4/driverlib/qei.h>
#include <ti/devices/msp432e4/driverlib/rom.h>
#include <ti/devices/msp432e4/driverlib/rom_map.h>
#include <ti/devices/msp432e4/driverlib/shamd5.h>
#include <ti/devices/msp432e4/driverlib/ssi.h>
#include <ti/devices/msp432e4/driverlib/sw_crc.h>
#include <ti/devices/msp432e4/driverlib/sysctl.h>
#include <ti/devices/msp432e4/driverlib/sysexc.h>
#include <ti/devices/msp432e4/driverlib/systick.h>
#include <ti/devices/msp432e4/driverlib/timer.h>
#include <ti/devices/msp432e4/driverlib/types.h>
#include <ti/devices/msp432e4/driverlib/uart.h>
#include <ti/devices/msp432e4/driverlib/udma.h>
#include <ti/devices/msp432e4/driverlib/usb.h>
#include <ti/devices/msp432e4/driverlib/watchdog.h>

/* Device specific modules */
#if defined(__MCU_HAS_LCD__)
#include <ti/devices/msp432e4/driverlib/lcd.h>
#endif

#if defined(__MCU_HAS_ONEWIRE__)
#include <ti/devices/msp432e4/driverlib/onewire.h>
#endif

#endif // __DRIVERLIB__H_
