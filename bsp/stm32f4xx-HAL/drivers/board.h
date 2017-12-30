/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 */

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef __BOARD_H__
#define __BOARD_H__

#include <stm32f4xx.h>
#include <stm32f4xx_hal.h>
#include <rtthread.h>
#if \
    defined(SOC_STM32F410T8)||\
    defined(SOC_STM32F410TB)
#define STM32F4xx_PIN_NUMBERS 36
#elif \
    defined(SOC_STM32F401CB)||\
    defined(SOC_STM32F401CC)||\
    defined(SOC_STM32F401CD)||\
    defined(SOC_STM32F401CE)||\
    defined(SOC_STM32F410C8)||\
    defined(SOC_STM32F410CB)||\
    defined(SOC_STM32F411CC)||\
    defined(SOC_STM32F411CE)||\
    defined(SOC_STM32F412CEU)||\
    defined(SOC_STM32F412CGU)||\
    defined(SOC_STM32F413CH)||\
    defined(SOC_STM32F413CG)||\
    defined(SOC_STM32F423CH)
#define STM32F4xx_PIN_NUMBERS 48
#elif \
    defined(SOC_STM32F405RG)||\
    defined(SOC_STM32F415RG)||\
    defined(SOC_STM32F401RB)||\
    defined(SOC_STM32F401RC)||\
    defined(SOC_STM32F401RD)||\
    defined(SOC_STM32F401RE)||\
    defined(SOC_STM32F410R8)||\
    defined(SOC_STM32F410RB)||\
    defined(SOC_STM32F411RC)||\
    defined(SOC_STM32F411RE)||\
    defined(SOC_STM32F446RC)||\
    defined(SOC_STM32F446RE)||\
    defined(SOC_STM32F412RET)||\
    defined(SOC_STM32F412RGT)||\
    defined(SOC_STM32F412REY)||\
    defined(SOC_STM32F412RGY)||\
    defined(SOC_STM32F413RH)||\
    defined(SOC_STM32F413RG)||\
    defined(SOC_STM32F423RH)
#define STM32F4xx_PIN_NUMBERS 64
#elif \
    defined(SOC_STM32F446MC)||\
    defined(SOC_STM32F446ME)||\
    defined(SOC_STM32F413MH)||\
    defined(SOC_STM32F413MG)
#define STM32F4xx_PIN_NUMBERS 81
#elif \
    defined(SOC_STM32F405VG)||\
    defined(SOC_STM32F415VG)||\
    defined(SOC_STM32F407VG)||\
    defined(SOC_STM32F407VE)||\
    defined(SOC_STM32F417VG)||\
    defined(SOC_STM32F417VE)||\
    defined(SOC_STM32F427VG)||\
    defined(SOC_STM32F427VI)||\
    defined(SOC_STM32F437VG)||\
    defined(SOC_STM32F437VI)||\
    defined(SOC_STM32F429VG)||\
    defined(SOC_STM32F429VI)||\
    defined(SOC_STM32F439VG)||\
    defined(SOC_STM32F439VI)||\
    defined(SOC_STM32F401VB)||\
    defined(SOC_STM32F401VC)||\
    defined(SOC_STM32F401VD)||\
    defined(SOC_STM32F401VE)||\
    defined(SOC_STM32F411VC)||\
    defined(SOC_STM32F411VE)||\
    defined(SOC_STM32F446VC)||\
    defined(SOC_STM32F446VE)||\
    defined(SOC_STM32F412VET)||\
    defined(SOC_STM32F412VGT)||\
    defined(SOC_STM32F412VEH)||\
    defined(SOC_STM32F412VGH)||\
    defined(SOC_STM32F413VH)||\
    defined(SOC_STM32F413VG)||\
    defined(SOC_STM32F423VH)
#define STM32F4xx_PIN_NUMBERS 100
#elif \
    defined(SOC_STM32F405ZG)||\
    defined(SOC_STM32F415ZG)||\
    defined(SOC_STM32F407ZG)||\
    defined(SOC_STM32F407ZE)||\
    defined(SOC_STM32F417ZG)||\
    defined(SOC_STM32F417ZE)||\
    defined(SOC_STM32F427ZG)||\
    defined(SOC_STM32F427ZI)||\
    defined(SOC_STM32F437ZG)||\
    defined(SOC_STM32F437ZI)||\
    defined(SOC_STM32F429ZG)||\
    defined(SOC_STM32F429ZI)||\
    defined(SOC_STM32F439ZG)||\
    defined(SOC_STM32F439ZI)||\
    defined(SOC_STM32F446ZC)||\
    defined(SOC_STM32F446ZE)||\
    defined(SOC_STM32F412ZET)||\
    defined(SOC_STM32F412ZGT)||\
    defined(SOC_STM32F412ZEJ)||\
    defined(SOC_STM32F412ZGJ)||\
    defined(SOC_STM32F413ZH)||\
    defined(SOC_STM32F413ZG)||\
    defined(SOC_STM32F423ZH)
#define STM32F4xx_PIN_NUMBERS 144
#elif \
    defined(SOC_STM32F469AI)||\
    defined(SOC_STM32F469AG)||\
    defined(SOC_STM32F469AE)||\
    defined(SOC_STM32F479AI)||\
    defined(SOC_STM32F479AG)
#define STM32F4xx_PIN_NUMBERS 169
#elif \
    defined(SOC_STM32F407IG)||\
    defined(SOC_STM32F407IE)||\
    defined(SOC_STM32F417IG)||\
    defined(SOC_STM32F417IE)||\
    defined(SOC_STM32F427IG)||\
    defined(SOC_STM32F427II)||\
    defined(SOC_STM32F437IG)||\
    defined(SOC_STM32F437II)||\
    defined(SOC_STM32F429IG)||\
    defined(SOC_STM32F429II)||\
    defined(SOC_STM32F439IG)||\
    defined(SOC_STM32F439II)||\
    defined(SOC_STM32F469II)||\
    defined(SOC_STM32F469IG)||\
    defined(SOC_STM32F469IE)||\
    defined(SOC_STM32F479II)||\
    defined(SOC_STM32F479IG)
#define STM32F4xx_PIN_NUMBERS 176
#elif \
    defined(SOC_STM32F429BG)||\
    defined(SOC_STM32F429BI)||\
    defined(SOC_STM32F439BG)||\
    defined(SOC_STM32F439BI)||\
    defined(SOC_STM32F469BI)||\
    defined(SOC_STM32F469BG)||\
    defined(SOC_STM32F469BE)||\
    defined(SOC_STM32F479BI)||\
    defined(SOC_STM32F479BG)
#define STM32F4xx_PIN_NUMBERS 208
#elif \
    defined(SOC_STM32F429NG)||\
    defined(SOC_STM32F439NI)||\
    defined(SOC_STM32F439NG)||\
    defined(SOC_STM32F439NI)||\
    defined(SOC_STM32F469NI)||\
    defined(SOC_STM32F469NG)||\
    defined(SOC_STM32F469NE)||\
    defined(SOC_STM32F479NI)||\
    defined(SOC_STM32F479NG)
#define STM32F4xx_PIN_NUMBERS 216
#endif

#if \
    defined(SOC_STM32F405RG)||\
    defined(SOC_STM32F405VG)||\
    defined(SOC_STM32F405ZG)
//#define STM32F405xx
#define STM32_SRAM_SIZE (192-64)
#elif \
    defined(SOC_STM32F415RG)||\
    defined(SOC_STM32F415VG)||\
    defined(SOC_STM32F415ZG)
//#define STM32F415xx
#define STM32_SRAM_SIZE (192-64)
#elif \
    defined(SOC_STM32F407VG)||\
    defined(SOC_STM32F407VE)||\
    defined(SOC_STM32F407ZG)||\
    defined(SOC_STM32F407ZE)||\
    defined(SOC_STM32F407IG)||\
    defined(SOC_STM32F407IE)
//#define STM32F407xx
#define STM32_SRAM_SIZE (192-64)
#elif \
    defined(SOC_STM32F417VG)||\
    defined(SOC_STM32F417VE)||\
    defined(SOC_STM32F417ZG)||\
    defined(SOC_STM32F417ZE)||\
    defined(SOC_STM32F417IG)||\
    defined(SOC_STM32F417IE)
//#define STM32F417xx
#define STM32_SRAM_SIZE (192-64)
#elif \
    defined(SOC_STM32F427VG)||\
    defined(SOC_STM32F427VI)||\
    defined(SOC_STM32F427ZG)||\
    defined(SOC_STM32F427ZI)||\
    defined(SOC_STM32F427IG)||\
    defined(SOC_STM32F427II)
//#define STM32F427xx
#define STM32_SRAM_SIZE (256-64)
#elif \
    defined(SOC_STM32F437VG)||\
    defined(SOC_STM32F437VI)||\
    defined(SOC_STM32F437ZG)||\
    defined(SOC_STM32F437ZI)||\
    defined(SOC_STM32F437IG)||\
    defined(SOC_STM32F437II)
//#define STM32F437xx
#define STM32_SRAM_SIZE (256-64)
#elif \
    defined(SOC_STM32F429VG)||\
    defined(SOC_STM32F429VI)||\
    defined(SOC_STM32F429ZG)||\
    defined(SOC_STM32F429ZI)||\
    defined(SOC_STM32F429BG)||\
    defined(SOC_STM32F429BI)||\
    defined(SOC_STM32F429NG)||\
    defined(SOC_STM32F429NI)||\
    defined(SOC_STM32F429IG)||\
    defined(SOC_STM32F429II)
//#define STM32F429xx
#define STM32_SRAM_SIZE (256-64)
#elif \
    defined(SOC_STM32F439VG)||\
    defined(SOC_STM32F439VI)||\
    defined(SOC_STM32F439ZG)||\
    defined(SOC_STM32F439ZI)||\
    defined(SOC_STM32F439BG)||\
    defined(SOC_STM32F439BI)||\
    defined(SOC_STM32F439NG)||\
    defined(SOC_STM32F439NI)||\
    defined(SOC_STM32F439IG)||\
    defined(SOC_STM32F439II)
//#define STM32F439xx
#define STM32_SRAM_SIZE (256-64)
#elif \
    defined(SOC_STM32F401CB)||\
    defined(SOC_STM32F401CC)||\
    defined(SOC_STM32F401RB)||\
    defined(SOC_STM32F401RC)||\
    defined(SOC_STM32F401VB)||\
    defined(SOC_STM32F401VC)
//#define STM32F401xC
#define STM32_SRAM_SIZE 64
#elif \
    defined(SOC_STM32F401CD)||\
    defined(SOC_STM32F401RD)||\
    defined(SOC_STM32F401VD)||\
    defined(SOC_STM32F401CE)||\
    defined(SOC_STM32F401RE)||\
    defined(SOC_STM32F401VE)
//#define STM32F401xE
#define STM32_SRAM_SIZE 96
#elif \
    defined(SOC_STM32F410T8)||\
    defined(SOC_STM32F410TB)
//#define STM32F410Tx
#define STM32_SRAM_SIZE 32
#elif \
    defined(SOC_STM32F410C8)||\
    defined(SOC_STM32F410CB)
//#define STM32F410Cx
#define STM32_SRAM_SIZE 32
#elif \
    defined(SOC_STM32F410R8)||\
    defined(SOC_STM32F410RB)
//#define STM32F410Rx
#define STM32_SRAM_SIZE 32
#elif \
    defined(SOC_STM32F411CC)||\
    defined(SOC_STM32F411RC)||\
    defined(SOC_STM32F411VC)||\
    defined(SOC_STM32F411CE)||\
    defined(SOC_STM32F411RE)||\
    defined(SOC_STM32F411VE)
//#define STM32F411xE
#define STM32_SRAM_SIZE 128
#elif \
    defined(SOC_STM32F446MC)||\
    defined(SOC_STM32F446ME)||\
    defined(SOC_STM32F446RC)||\
    defined(SOC_STM32F446RE)||\
    defined(SOC_STM32F446VC)||\
    defined(SOC_STM32F446VE)||\
    defined(SOC_STM32F446ZC)||\
    defined(SOC_STM32F446ZE)
//#define STM32F446xx
#define STM32_SRAM_SIZE 128
#elif \
    defined(SOC_STM32F469AI)||\
    defined(SOC_STM32F469II)||\
    defined(SOC_STM32F469BI)||\
    defined(SOC_STM32F469NI)||\
    defined(SOC_STM32F469AG)||\
    defined(SOC_STM32F469IG)||\
    defined(SOC_STM32F469BG)||\
    defined(SOC_STM32F469NG)||\
    defined(SOC_STM32F469AE)||\
    defined(SOC_STM32F469IE)||\
    defined(SOC_STM32F469BE)||\
    defined(SOC_STM32F469NE)
//#define STM32F469xx
#define STM32_SRAM_SIZE (384-64)
#elif \
    defined(SOC_STM32F479AI)||\
    defined(SOC_STM32F479II)||\
    defined(SOC_STM32F479BI)||\
    defined(SOC_STM32F479NI)||\
    defined(SOC_STM32F479AG)||\
    defined(SOC_STM32F479IG)||\
    defined(SOC_STM32F479BG)||\
    defined(SOC_STM32F479NG)
//#define STM32F479xx
#define STM32_SRAM_SIZE (384-64)
#elif \
    defined(SOC_STM32F412CEU)||\
    defined(SOC_STM32F412CGU)
//#define STM32F412Cx
#elif \
    defined(SOC_STM32F412ZET)||\
    defined(SOC_STM32F412ZGT)||\
    defined(SOC_STM32F412ZEJ)||\
    defined(SOC_STM32F412ZGJ)
//#define STM32F412Zx
#define STM32_SRAM_SIZE 256
#elif \
    defined(SOC_STM32F412VET)||\
    defined(SOC_STM32F412VGT)||\
    defined(SOC_STM32F412VEH)||\
    defined(SOC_STM32F412VGH)
//#define STM32F412Vx
#define STM32_SRAM_SIZE 256
#elif \
    defined(SOC_STM32F412RET)||\
    defined(SOC_STM32F412RGT)||\
    defined(SOC_STM32F412REY)||\
    defined(SOC_STM32F412RGY)
//#define STM32F412Rx
#define STM32_SRAM_SIZE 256
#elif \
    defined(SOC_STM32F413CH)||\
    defined(SOC_STM32F413MH)||\
    defined(SOC_STM32F413RH)||\
    defined(SOC_STM32F413VH)||\
    defined(SOC_STM32F413ZH)||\
    defined(SOC_STM32F413CG)||\
    defined(SOC_STM32F413MG)||\
    defined(SOC_STM32F413RG)||\
    defined(SOC_STM32F413VG)||\
    defined(SOC_STM32F413ZG)
//#define STM32F413xx
#define STM32_SRAM_SIZE 320
#elif \
    defined(SOC_STM32F423CH)||\
    defined(SOC_STM32F423RH)||\
    defined(SOC_STM32F423VH)||\
    defined(SOC_STM32F423ZH)
//#define STM32F423xx
#define STM32_SRAM_SIZE 320
#endif


#define STM32_SRAM_END          (0x20000000 + STM32_SRAM_SIZE * 1024)

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN  ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN  (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN  ((void *)&__bss_end)
#endif
#define HEAP_END    STM32_SRAM_END

#endif
extern void rt_hw_board_init(void);
// <<< Use Configuration Wizard in Context Menu >>>
