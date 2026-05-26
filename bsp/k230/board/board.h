/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 */

#ifndef BOARD_H__
#define BOARD_H__

#include "rtconfig.h"
#include "mem_layout.h"
#include "irq_num.h"

/*
 * K230 Memory Map
 *
 * See K230 Technical Reference Manual, chapter 1.5 Address Space mapping
 */
#define KPU_BASE_ADDR               (0x80400000UL)
#define KPU_IO_SIZE                 (0x00000800UL)

#define FFT_BASE_ADDR               (0x80400800UL)
#define FFT_IO_SIZE                 (0x00000400UL)

#define AI2D_BASE_ADDR              (0x80400C00UL)
#define AI2D_IO_SIZE                (0x00000400UL)

#define DMA_BASE_ADDR               (0x80804000UL)
#define DMA_IO_SIZE                 (0x00004000UL)

#define PMU_BASE_ADDR               (0x91000000UL)
#define PMU_IO_SIZE                 (0x00000C00UL)

#define RTC_BASE_ADDR               (0x91000C00UL)
#define RTC_IO_SIZE                 (0x00000400UL)

#define CMU_BASE_ADDR               (0x91100000UL)
#define CMU_IO_SIZE                 (0x00001000UL)

#define RMU_BASE_ADDR               (0x91101000UL)
#define RMU_IO_SIZE                 (0x00001000UL)

#define BOOT_BASE_ADDR              (0x91102000UL)
#define BOOT_IO_SIZE                (0x00001000UL)

#define PWR_BASE_ADDR               (0x91103000UL)
#define PWR_IO_SIZE                 (0x00001000UL)

#define MAILBOX_BASE_ADDR           (0x91104000UL)
#define MAILBOX_IO_SIZE             (0x00001000UL)

#define IOMUX_BASE_ADDR             (0x91105000UL)
#define IOMUX_IO_SIZE               (0x00000800UL)

#define HW_TIMER_BASE_ADDR          (0x91105800UL)
#define HW_TIMER_IO_SIZE            (0x00000800UL)

#define WDT0_BASE_ADDR              (0x91106000UL)
#define WDT0_IO_SIZE                (0x00000800UL)

#define WDT1_BASE_ADDR              (0x91106800UL)
#define WDT1_IO_SIZE                (0x00000800UL)

#define TS_BASE_ADDR                (0x91107000UL)
#define TS_IO_SIZE                  (0x00000800UL)

#define UART0_BASE_ADDR             (0x91400000UL)
#define UART0_IO_SIZE               (0x00001000UL)

#define UART1_BASE_ADDR             (0x91401000UL)
#define UART1_IO_SIZE               (0x00001000UL)

#define UART2_BASE_ADDR             (0x91402000UL)
#define UART2_IO_SIZE               (0x00001000UL)

#define UART3_BASE_ADDR             (0x91403000UL)
#define UART3_IO_SIZE               (0x00001000UL)

#define UART4_BASE_ADDR             (0x91404000UL)
#define UART4_IO_SIZE               (0x00001000UL)

#define I2C0_BASE_ADDR              (0x91405000UL)
#define I2C0_IO_SIZE                (0x00001000UL)

#define I2C1_BASE_ADDR              (0x91406000UL)
#define I2C1_IO_SIZE                (0x00001000UL)

#define I2C2_BASE_ADDR              (0x91407000UL)
#define I2C2_IO_SIZE                (0x00001000UL)

#define I2C3_BASE_ADDR              (0x91408000UL)
#define I2C3_IO_SIZE                (0x00001000UL)

#define I2C4_BASE_ADDR              (0x91409000UL)
#define I2C4_IO_SIZE                (0x00001000UL)

#define PWM_BASE_ADDR               (0x9140A000UL)
#define PWM_IO_SIZE                 (0x00001000UL)

#define GPIO0_BASE_ADDR             (0x9140B000UL)
#define GPIO0_IO_SIZE               (0x00001000UL)

#define GPIO1_BASE_ADDR             (0x9140C000UL)
#define GPIO1_IO_SIZE               (0x00001000UL)

#define ADC_BASE_ADDR               (0x9140D000UL)
#define ADC_IO_SIZE                 (0x00001000UL)

#define SPI_QOPI_BASE_ADDR          (0x91582000UL)
#define SPI_QOPI_IO_SIZE            (0x00002000UL)

#define SPI_OPI_BASE_ADDR           (0x91584000UL)
#define SPI_OPI_IO_SIZE             (0x00001000UL)

#endif // BOARD_H__
