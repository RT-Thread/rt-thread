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

/*
 * K230 Memory Map
 *
 * See K230 Technical Reference Manual, chapter 1.5 Address Space mapping
 */
#define SRAM_BASE_ADDR              (0x80200000UL)
#define SRAM_IO_SIZE                (0x00200000UL)

#define KPU_BASE_ADDR               (0x80400000UL)
#define KPU_IO_SIZE                 (0x00000800UL)

#define FFT_BASE_ADDR               (0x80400800UL)
#define FFT_IO_SIZE                 (0x00000400UL)

#define AI2D_BASE_ADDR              (0x80400C00UL)
#define AI2D_IO_SIZE                (0x00000400UL)

#define GSDMA_BASE_ADDR             (0x80800000UL)
#define GSDMA_IO_SIZE               (0x00004000UL)

#define DMA_BASE_ADDR               (0x80804000UL)
#define DMA_IO_SIZE                 (0x00004000UL)

#define DECOMP_BASE_ADDR            (0x80808000UL)
#define DECOMP_IO_SIZE              (0x00004000UL)

#define NON_AI2D_BASE_ADDR          (0x8080C000UL)
#define NON_AI2D_IO_SIZE            (0x00004000UL)

#define ISP_BASE_ADDR               (0x90000000UL)
#define ISP_IO_SIZE                 (0x00008000UL)

#define DEWARP_BASE_ADDR            (0x90008000UL)
#define DEWARP_IO_SIZE              (0x00001000UL)

#define CSI_BASE_ADDR               (0x90009000UL)
#define CSI_IO_SIZE                 (0x00002000UL)

#define VPU_BASE_ADDR               (0x90400000UL)
#define VPU_IO_SIZE                 (0x00010000UL)

/*2.5D*/
#define TAAH_GPU_BASE_ADDR          (0x90800000UL)
#define TAAH_GPU_IO_SIZE            (0x00040000UL)

#define VO_BASE_ADDR                (0x90840000UL)
#define VO_IO_SIZE                  (0x00010000UL)

#define DSI_BASE_ADDR               (0x90850000UL)
#define DSI_IO_SIZE                 (0x00001000UL)

#define GPU_ENGINE_BASE_ADDR        (0x90A00000UL)
#define GPU_ENGINE_IO_SIZE          (0x00000800UL)

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

#define HDI_BASE_ADDR               (0x91107800UL)
#define HDI_IO_SIZE                 (0x00000800UL)

#define STC_BASE_ADDR               (0x91108000UL)
#define STC_IO_SIZE                 (0x00001000UL)

#define BOOTROM_BASE_ADDR           (0x91200000UL)
#define BOOTROM_IO_SIZE             (0x00010000UL)

#define SECURITY_BASE_ADDR          (0x91210000UL)
#define SECURITY_IO_SIZE            (0x00008000UL)

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

#define CODEC_BASE_ADDR             (0x9140E000UL)
#define CODEC_IO_SIZE               (0x00001000UL)

#define AUDIO_BASE_ADDR             (0x9140F000UL)
#define AUDIO_IO_SIZE               (0x00001000UL)

#define USB2_BASE_ADDR              (0x91500000UL)
#define USB2_IO_SIZE                (0x00080000UL)

#define SD_HC_BASE_ADDR             (0x91580000UL)
#define SD_HC_IO_SIZE               (0x00002000UL)

#define SPI_QOPI_BASE_ADDR          (0x91582000UL)
#define SPI_QOPI_IO_SIZE            (0x00002000UL)

#define SPI_OPI_BASE_ADDR           (0x91584000UL)
#define SPI_OPI_IO_SIZE             (0x00001000UL)

#define HI_SYS_CONFIG_BASE_ADDR     (0x91585000UL)
#define HI_SYS_CONFIG_IO_SIZE       (0x00000400UL)

#define DDRC_CONF_BASE_ADDR         (0x98000000UL)
#define DDRC_CONF_IO_SIZE           (0x02000000UL)

#define SPI_XIP_FLASH_BASE_ADDR     (0xC0000000UL)
#define SPI_XIP_FLASH_IO_SIZE       (0x08000000UL)

#define IO_SPACE_BASE_ADDR          (KPU_BASE_ADDR)

#define TIMER_CLK_FREQ  (27000000)

#endif // BOARD_H__
