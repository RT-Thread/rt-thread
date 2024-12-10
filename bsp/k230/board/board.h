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

#include <rtconfig.h>

extern unsigned int __sram_size;
extern unsigned int __sram_base;
extern unsigned int __sram_end;
#define RAM_END     (rt_size_t)((void *)&__sram_end)

extern unsigned int __bss_start;
extern unsigned int __bss_end;

#define RT_HW_HEAP_BEGIN    ((void *)&__bss_end)
#define RT_HW_HEAP_END      ((void *)(((rt_size_t)RT_HW_HEAP_BEGIN) + 8 * 1024 * 1024))

#define RT_HW_PAGE_START    ((void *)((rt_size_t)RT_HW_HEAP_END + sizeof(rt_size_t)))
#define RT_HW_PAGE_END      ((void *)(RAM_END))

void rt_hw_board_init(void);
void rt_init_user_mem(struct rt_thread *thread, const char *name, unsigned long *entry);

#define TIMER_CLK_FREQ  (27000000UL)

/*
From K230 Technical Reference Manual Address Space mapping

Start Address   End Address     Function            Size
0x0000_0000     0x8000_0000     DDRC                2GB
0x8000_0000     0x8020_0000     KPU L2 Cache        2MB
0x8020_0000     0x8040_0000     SRAM                2MB
0x8040_0000     0x8040_0800     KPU                 2KB
0x8040_0800     0x8040_0C00     FFT                 1KB
0x8040_0C00     0x8040_1000     AI 2D Engine        1KB
0x8080_0000     0x8080_4000     gsdma               16KB
0x8080_4000     0x8080_8000     DMA                 16KB
0x8080_8000     0x8080_C000     decomp_gzip         16KB
0x8080_C000     0x8081_0000     non_ai_2d           16KB
0x9000_0000     0x9000_8000     ISP                 32KB
0x9000_8000     0x9000_9000     DeWarp              4KB
0x9000_9000     0x9000_B000     RX CSI              8KB
0x9040_0000     0x9041_0000     VPU                 64KB
0x9080_0000     0x9084_0000     2.5D                256KB
0x9084_0000     0x9085_0000     VO                  64KB
0x9085_0000     0x9085_1000     VO_cfg/DSI          4KB
0x90A0_0000     0x90A0_0800     3D Engine           2KB
0x9100_0000     0x9100_0C00     PMU                 3KB
0x9100_0C00     0x9100_1000     RTC                 1KB
0x9110_0000     0x9110_1000     CMU                 4KB
0x9110_1000     0x9110_2000     RMU                 4KB
0x9110_2000     0x9110_3000     BOOT                4KB
0x9110_3000     0x9110_4000     PWR                 4KB
0x9110_4000     0x9110_5000     mailbox             4KB
0x9110_5000     0x9110_5800     iomux               2KB
0x9110_5800     0x9110_6000     timer               2KB
0x9110_6000     0x9110_6800     wdt0                2KB
0x9110_6800     0x9110_7000     wdt1                2KB
0x9110_7000     0x9110_7800     TS                  2KB
0x9110_7800     0x9110_8000     HDI                 2KB
0x9110_8000     0x9110_9000     STC                 4KB
0x9120_0000     0x9121_0000     BootRom             64KB
0x9121_0000     0x9121_8000     Security            2KB
0x9140_0000     0x9140_1000     UART0               4KB
0x9140_1000     0x9140_2000     UART1               4KB
0x9140_2000     0x9140_3000     UART2               4KB
0x9140_3000     0x9140_4000     UART3               4KB
0x9140_4000     0x9140_5000     UART4               4KB
0x9140_5000     0x9140_6000     I2C0                4KB
0x9140_6000     0x9140_7000     I2C1                4KB
0x9140_7000     0x9140_8000     I2C2                4KB
0x9140_8000     0x9140_9000     I2C3                4KB
0x9140_9000     0x9140_A000     I2C4                4KB
0x9140_A000     0x9140_B000     PWM                 4KB
0x9140_B000     0x9140_C000     GPIO0               4KB
0x9140_C000     0x9140_D000     GPIO1               4KB
0x9140_D000     0x9140_E000     ADC                 4KB
0x9140_E000     0x9140_F000     CODEC               4KB
0x9140_F000     0x9141_0000     Audio (I2S)         4KB
0x9150_0000     0x9158_0000     USB2.0 OTG x2       256KB
0x9158_0000     0x9158_2000     SD HC X2            8KB
0x9158_2000     0x9158_4000     SPI QOPI x2         9KB
0x9158_4000     0x9158_5000     SPI OPI             4KB
0x9158_5000     0x9158_5400     Hi_sys_config       1KB
0x9800_0000     0x9A00_0000     DDRC config         32MB
0xC000_0000     0xC800_0000     SPI OPI XIP FLASH   128MB
0xf_0000_0000   0xf_0020_3004   CPU0 Plic           ~2MB
0xf_0000_0000   0xf_0020_3004   CPU1 Plic           ~2MB
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

#define DEVICE_MEM_BASE_ADDR        (0x80400000UL)
#define DEVICE_MEM_SIZE             (0x20000000UL)

#endif
