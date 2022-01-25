/**
 * @file    max32660.h
 * @brief   Device-specific perhiperal header file
 */

/*******************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2018-12-18 15:37:22 -0600 (Tue, 18 Dec 2018) $
 * $Revision: 40072 $
 *
 ******************************************************************************/

#ifndef _MAX32660_REGS_H_
#define _MAX32660_REGS_H_

#ifndef TARGET_NUM
#define TARGET_NUM  32660
#endif

#include <stdint.h>

#ifndef  FALSE
#define  FALSE      (0)
#endif

#ifndef  TRUE
#define  TRUE       (1)
#endif

#if !defined (__GNUC__)
#define CMSIS_VECTAB_VIRTUAL
#define CMSIS_VECTAB_VIRTUAL_HEADER_FILE "nvic_table.h"
#endif /* !__GNUC__ */

/* COMPILER SPECIFIC DEFINES (IAR, ARMCC and GNUC) */
#if defined ( __GNUC__ ) /* GCC */
#define __weak __attribute__((weak))

#elif defined ( __CC_ARM) /* Keil */

#define inline __inline
#pragma anon_unions

#endif

typedef enum {
    NonMaskableInt_IRQn    = -14,
    HardFault_IRQn         = -13,
    MemoryManagement_IRQn  = -12,
    BusFault_IRQn          = -11,
    UsageFault_IRQn        = -10,
    SVCall_IRQn            = -5,
    DebugMonitor_IRQn      = -4,
    PendSV_IRQn            = -2,
    SysTick_IRQn           = -1,

    /* Device-specific interrupt sources (external to ARM core)                 */
    /*                      table entry number                                  */
    /*                      ||||                                                */
    /*                      ||||  table offset address                          */
    /*                      vvvv  vvvvvv                                        */

    PF_IRQn = 0,         /* 0x10  0x0040  16: Power Fail */
    WDT0_IRQn,           /* 0x11  0x0044  17: Watchdog 0 */
    RSV00_IRQn,          /* 0x12  0x0048  18: RSV00 */
    RTC_IRQn,            /* 0x13  0x004C  19: RTC */
    RSV1_IRQn,           /* 0x14  0x0050  20: RSV1 */
    TMR0_IRQn,           /* 0x15  0x0054  21: Timer 0 */
    TMR1_IRQn,           /* 0x16  0x0058  22: Timer 1 */
    TMR2_IRQn,           /* 0x17  0x005C  23: Timer 2 */
    RSV02_IRQn,          /* 0x18  0x0060  24: RSV02 */
    RSV03_IRQn,          /* 0x19  0x0064  25: RSV03 */
    RSV04_IRQn,          /* 0x1A  0x0068  26: RSV04 */
    RSV05_IRQn,          /* 0x1B  0x006C  27: RSV05 */
    RSV06_IRQn,          /* 0x1C  0x0070  28: RSV06 */
    I2C0_IRQn,           /* 0x1D  0x0074  29: I2C0 */
    UART0_IRQn,          /* 0x1E  0x0078  30: UART 0 */
    UART1_IRQn,          /* 0x1F  0x007C  31: UART 1 */
    SPI17Y_IRQn,         /* 0x20  0x0080  32: SPI17Y */
    SPIMSS_IRQn,         /* 0x21  0x0084  33: SPIMSS */
    RSV07_IRQn,          /* 0x22  0x0088  34: RSV07 */
    RSV08_IRQn,          /* 0x23  0x008C  35: RSV08 */
    RSV09_IRQn,          /* 0x24  0x0090  36: RSV09 */
    RSV10_IRQn,          /* 0x25  0x0094  37: RSV10 */
    RSV11_IRQn,          /* 0x26  0x0098  38: RSV11 */
    FLC_IRQn,            /* 0x27  0x009C  39: FLC */
    GPIO0_IRQn,          /* 0x28  0x00A0  40: GPIO0 */
    RSV12_IRQn,          /* 0x29  0x00A4  41: RSV12 */
    RSV13_IRQn,          /* 0x2A  0x00A8  42: RSV13 */
    RSV14_IRQn,          /* 0x2B  0x00AC  43: RSV14 */
    DMA0_IRQn,           /* 0x2C  0x00B0  44: DMA0 */
    DMA1_IRQn,           /* 0x2D  0x00B4  45: DMA1 */
    DMA2_IRQn,           /* 0x2E  0x00B8  46: DMA2 */
    DMA3_IRQn,           /* 0x2F  0x00BC  47: DMA3 */
    RSV15_IRQn,          /* 0x30  0x00C0  48: RSV15 */
    RSV16_IRQn,          /* 0x31  0x00C4  49: RSV16 */
    RSV17_IRQn,          /* 0x32  0x00C8  50: RSV17 */
    RSV18_IRQn,          /* 0x33  0x00CC  51: RSV18 */
    I2C1_IRQn,           /* 0x34  0x00D0  52: I2C1 */
    RSV19_IRQn,          /* 0x35  0x00D4  53: RSV19 */
    RSV20_IRQn,          /* 0x36  0x00D8  54: RSV20 */
    RSV21_IRQn,          /* 0x37  0x00DC  55: RSV21 */
    RSV22_IRQn,          /* 0x38  0x00E0  56: RSV22 */
    RSV23_IRQn,          /* 0x39  0x00E4  57: RSV23 */
    RSV24_IRQn,          /* 0x3A  0x00E8  58: RSV24 */
    RSV25_IRQn,          /* 0x3B  0x00EC  59: RSV25 */
    RSV26_IRQn,          /* 0x3C  0x00F0  60: RSV26 */
    RSV27_IRQn,          /* 0x3D  0x00F4  61: RSV27 */
    RSV28_IRQn,          /* 0x3E  0x00F8  62: RSV28 */
    RSV29_IRQn,          /* 0x3F  0x00FC  63: RSV29 */
    RSV30_IRQn,          /* 0x40  0x0100  64: RSV30 */
    RSV31_IRQn,          /* 0x41  0x0104  65: RSV31 */
    RSV32_IRQn,          /* 0x42  0x0108  66: RSV32 */
    RSV33_IRQn,          /* 0x43  0x010C  67: RSV33 */
    RSV34_IRQn,          /* 0x44  0x0110  68: RSV34 */
    RSV35_IRQn,          /* 0x45  0x0114  69: RSV35 */
    GPIOWAKE_IRQn,       /* 0x46  0x0118  70: GPIO Wakeup */
    MXC_IRQ_EXT_COUNT,
} IRQn_Type;

#define MXC_IRQ_COUNT (MXC_IRQ_EXT_COUNT + 16)


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------------  Configuration of the Cortex-M Processor and Core Peripherals  ---------------------- */
#define __CM4_REV                       0x0100          /*!< Cortex-M4 Core Revision                                */
#define __MPU_PRESENT                   1               /*!< MPU present or not                                     */
#define __NVIC_PRIO_BITS                3               /*!< Number of Bits used for Priority Levels                */
#define __Vendor_SysTickConfig          0               /*!< Set to 1 if different SysTick Config is used           */
#define __FPU_PRESENT                   1               /*!< FPU present or not                                     */

#include <core_cm4.h>                                   /*!< Cortex-M4 processor and core peripherals               */
#include "system_max32660.h"                            /*!< System Header                                          */


/* ================================================================================ */
/* ==================       Device Specific Memory Section       ================== */
/* ================================================================================ */

#define MXC_FLASH_MEM_BASE              0x00000000UL
#define MXC_FLASH_PAGE_SIZE             0x00002000UL
#define MXC_FLASH_MEM_SIZE              0x00040000UL
#define MXC_INFO_MEM_BASE               0x00040000UL
#define MXC_INFO_MEM_SIZE               0x00001000UL
#define MXC_SRAM_MEM_BASE               0x20000000UL
#define MXC_SRAM_MEM_SIZE               0x00018000UL

/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */

/*
   Base addresses and configuration settings for all MAX32660 peripheral modules.
*/

/******************************************************************************/
/*                                                             Global control */
#define MXC_BASE_GCR                    ((uint32_t)0x40000000UL)
#define MXC_GCR                         ((mxc_gcr_regs_t*)MXC_BASE_GCR)

/******************************************************************************/
/*                                            Non-battery backed SI Registers */
#define MXC_BASE_SIR                    ((uint32_t)0x40000400UL)
#define MXC_SIR                         ((mxc_sir_regs_t*)MXC_BASE_SIR)

/******************************************************************************/
/*                                                                   Watchdog */
#define MXC_BASE_WDT0                   ((uint32_t)0x40003000UL)
#define MXC_WDT0                        ((mxc_wdt_regs_t*)MXC_BASE_WDT0)

/******************************************************************************/
/*                                                            Real Time Clock */
#define MXC_BASE_RTC                    ((uint32_t)0x40006000UL)
#define MXC_RTC                         ((mxc_rtc_regs_t*)MXC_BASE_RTC)

/******************************************************************************/
/*                                                            Power Sequencer */
#define MXC_BASE_PWRSEQ                 ((uint32_t)0x40006800UL)
#define MXC_PWRSEQ                      ((mxc_pwrseq_regs_t*)MXC_BASE_PWRSEQ)


/******************************************************************************/
/*                                                                       GPIO */
#define MXC_CFG_GPIO_INSTANCES          (1)
#define MXC_CFG_GPIO_PINS_PORT          (14)

#define MXC_BASE_GPIO0                  ((uint32_t)0x40008000UL)
#define MXC_GPIO0                       ((mxc_gpio_regs_t*)MXC_BASE_GPIO0)

#define MXC_GPIO_GET_IDX(p)             ((p) == MXC_GPIO0 ? 0 :-1)

#define MXC_GPIO_GET_GPIO(i)            ((i) == 0 ? MXC_GPIO0 : 0)

#define MXC_GPIO_GET_IRQ(i)             ((i) == 0 ? GPIO0_IRQn : 0)

/******************************************************************************/
/*                                                                      Timer */
#define MXC_CFG_TMR_INSTANCES           (3)

#define MXC_BASE_TMR0                   ((uint32_t)0x40010000UL)
#define MXC_TMR0                        ((mxc_tmr_regs_t*)MXC_BASE_TMR0)
#define MXC_BASE_TMR1                   ((uint32_t)0x40011000UL)
#define MXC_TMR1                        ((mxc_tmr_regs_t*)MXC_BASE_TMR1)
#define MXC_BASE_TMR2                   ((uint32_t)0x40012000UL)
#define MXC_TMR2                        ((mxc_tmr_regs_t*)MXC_BASE_TMR2)

#define MXC_TMR_GET_IRQ(i)              (IRQn_Type)((i) == 0 ? TMR0_IRQn :     \
                                            (i) == 1 ? TMR1_IRQn :             \
                                            (i) == 2 ? TMR2_IRQn : 0)

#define MXC_TMR_GET_BASE(i)             ((i) == 0 ? MXC_BASE_TMR0 :            \
                                            (i) == 1 ? MXC_BASE_TMR1 :         \
                                            (i) == 2 ? MXC_BASE_TMR2 : 0)

#define MXC_TMR_GET_TMR(i)              ((i) == 0 ? MXC_TMR0 :                 \
                                            (i) == 1 ? MXC_TMR1 :              \
                                            (i) == 2 ? MXC_TMR2 : 0)

#define MXC_TMR_GET_IDX(p)              ((p) == MXC_TMR0 ? 0 :                 \
                                            (p) == MXC_TMR1 ? 1 :              \
                                            (p) == MXC_TMR2 ? 2 : -1)

/******************************************************************************/
/*                                                                    SPIMSS  */

#define MXC_SPIMSS_INSTANCES            (1)
#define MXC_SPIMSS_FIFO_DEPTH           (8)

#define MXC_BASE_SPIMSS                ((uint32_t)0x40019000UL)
#define MXC_SPIMSS                     ((mxc_spimss_regs_t*)MXC_BASE_SPIMSS)

#define MXC_SPIMSS_GET_IDX(p)            ((p) == MXC_SPIMSS ? 0 :  -1)
#define MXC_SPIMSS_GET_SPI(i)            ((i) == 0 ? MXC_SPIMSS :   0)

/******************************************************************************/
/*                                                                        I2C */
#define MXC_I2C_INSTANCES               (2)
#define MXC_I2C_FIFO_DEPTH              (8)

#define MXC_BASE_I2C0                   ((uint32_t)0x4001D000UL)
#define MXC_I2C0                        ((mxc_i2c_regs_t*)MXC_BASE_I2C0)
#define MXC_BASE_I2C1                   ((uint32_t)0x4001E000UL)
#define MXC_I2C1                        ((mxc_i2c_regs_t*)MXC_BASE_I2C1)

#define MXC_I2C_GET_IRQ(i)              (IRQn_Type)((i) == 0 ? I2C0_IRQn :     \
                                            (i) == 1 ? I2C1_IRQn : 0)

#define MXC_I2C_GET_BASE(i)             ((i) == 0 ? MXC_BASE_I2C0 :            \
                                            (i) == 1 ? MXC_BASE_I2C1 : 0)

#define MXC_I2C_GET_I2C(i)              ((i) == 0 ? MXC_I2C0 :                 \
                                            (i) == 1 ? MXC_I2C1 : 0)

#define MXC_I2C_GET_IDX(p)              ((p) == MXC_I2C0 ? 0 :                 \
                                            (p) == MXC_I2C1 ? 1 : -1)

/******************************************************************************/
/*                                                                        DMA */
#define MXC_DMA_CHANNELS                (4)

#define MXC_BASE_DMA                    ((uint32_t)0x40028000UL)
#define MXC_DMA                         ((mxc_dma_regs_t*)MXC_BASE_DMA)

/******************************************************************************/
/*                                                                        FLC */
#define MXC_BASE_FLC                    ((uint32_t)0x40029000UL)
#define MXC_FLC                         ((mxc_flc_regs_t*)MXC_BASE_FLC)

/******************************************************************************/
/*                                                          Instruction Cache */
#define MXC_BASE_ICC                    ((uint32_t)0x4002A000UL)
#define MXC_ICC                         ((mxc_icc_regs_t*)MXC_BASE_ICC)

/******************************************************************************/
/*                                               UART / Serial Port Interface */

#define MXC_UART_INSTANCES              (2)
#define MXC_UART_FIFO_DEPTH             (8)

#define MXC_BASE_UART0                  ((uint32_t)0x40042000UL)
#define MXC_UART0                       ((mxc_uart_regs_t*)MXC_BASE_UART0)
#define MXC_BASE_UART1                  ((uint32_t)0x40043000UL)
#define MXC_UART1                       ((mxc_uart_regs_t*)MXC_BASE_UART1)

#define MXC_UART_GET_IRQ(i)             (IRQn_Type)((i) == 0 ? UART0_IRQn :    \
                                            (i) == 1 ? UART1_IRQn : 0)

#define MXC_UART_GET_BASE(i)            ((i) == 0 ? MXC_BASE_UART0 :           \
                                            (i) == 1 ? MXC_BASE_UART1 : 0)

#define MXC_UART_GET_UART(i)            ((i) == 0 ? MXC_UART0 :                \
                                            (i) == 1 ? MXC_UART1 : 0)

#define MXC_UART_GET_IDX(p)             ((p) == MXC_UART0 ? 0 :                \
                                            (p) == MXC_UART1 ? 1 : -1)

/******************************************************************************/
/*                                                                        SPI */


#define MXC_SPI17Y_INSTANCES               (4)
#define MXC_SPI17Y_SS_INSTANCES            (1)
#define MXC_SPI17Y_FIFO_DEPTH              (32)

#define MXC_BASE_SPI17Y                   ((uint32_t)0x40046000UL)
#define MXC_SPI17Y                        ((mxc_spi17y_regs_t*)MXC_BASE_SPI17Y)

#define MXC_SPI17Y_GET_IDX(p)               ((p) == MXC_SPI17Y ? 0 :  -1)

#define MXC_SPI17Y_GET_BASE(i)             ((i) == 0 ? MXC_BASE_SPI17Y :  0)

#define MXC_SPI17Y_GET_SPI17Y(i)             ((i) == 0 ? MXC_SPI17Y :   0)

/******************************************************************************/
/*                                                               Bit Shifting */

#define MXC_F_BIT_0                     (1 << 0)
#define MXC_F_BIT_1                     (1 << 1)
#define MXC_F_BIT_2                     (1 << 2)
#define MXC_F_BIT_3                     (1 << 3)
#define MXC_F_BIT_4                     (1 << 4)
#define MXC_F_BIT_5                     (1 << 5)
#define MXC_F_BIT_6                     (1 << 6)
#define MXC_F_BIT_7                     (1 << 7)
#define MXC_F_BIT_8                     (1 << 8)
#define MXC_F_BIT_9                     (1 << 9)
#define MXC_F_BIT_10                    (1 << 10)
#define MXC_F_BIT_11                    (1 << 11)
#define MXC_F_BIT_12                    (1 << 12)
#define MXC_F_BIT_13                    (1 << 13)
#define MXC_F_BIT_14                    (1 << 14)
#define MXC_F_BIT_15                    (1 << 15)
#define MXC_F_BIT_16                    (1 << 16)
#define MXC_F_BIT_17                    (1 << 17)
#define MXC_F_BIT_18                    (1 << 18)
#define MXC_F_BIT_19                    (1 << 19)
#define MXC_F_BIT_20                    (1 << 20)
#define MXC_F_BIT_21                    (1 << 21)
#define MXC_F_BIT_22                    (1 << 22)
#define MXC_F_BIT_23                    (1 << 23)
#define MXC_F_BIT_24                    (1 << 24)
#define MXC_F_BIT_25                    (1 << 25)
#define MXC_F_BIT_26                    (1 << 26)
#define MXC_F_BIT_27                    (1 << 27)
#define MXC_F_BIT_28                    (1 << 28)
#define MXC_F_BIT_29                    (1 << 29)
#define MXC_F_BIT_30                    (1 << 30)
#define MXC_F_BIT_31                    (1 << 31)

/******************************************************************************/
/*                                                               Bit Banding  */

#define BITBAND(reg, bit)               ((0xf0000000 & (uint32_t)(reg)) + 0x2000000 + \
                                            (((uint32_t)(reg) & 0x0fffffff) << 5) + ((bit) << 2))

#define MXC_CLRBIT(reg, bit)            (*(volatile uint32_t *)BITBAND(reg, bit) = 0)
#define MXC_SETBIT(reg, bit)            (*(volatile uint32_t *)BITBAND(reg, bit) = 1)
#define MXC_GETBIT(reg, bit)            (*(volatile uint32_t *)BITBAND(reg, bit))

#define MXC_SETFIELD(reg, mask, value)  (reg = (reg & ~mask) | (value & mask))

/******************************************************************************/
/*                                                                  SCB CPACR */

/* Note: Added by Maxim Integrated, as these are missing from CMSIS/Core/Include/core_cm4.h */
#define SCB_CPACR_CP10_Pos              20                              /*!< SCB CPACR: Coprocessor 10 Position */
#define SCB_CPACR_CP10_Msk              (0x3UL << SCB_CPACR_CP10_Pos)   /*!< SCB CPACR: Coprocessor 10 Mask */
#define SCB_CPACR_CP11_Pos              22                              /*!< SCB CPACR: Coprocessor 11 Position */
#define SCB_CPACR_CP11_Msk              (0x3UL << SCB_CPACR_CP11_Pos)   /*!< SCB CPACR: Coprocessor 11 Mask */

#endif  /* _MAX32660_REGS_H_ */
