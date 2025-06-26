/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __SYSCTL_RST_H__
#define __SYSCTL_RST_H__

/* created by yangfan */

#include <stdint.h>
#include "stdbool.h"

typedef enum
{
    SYSCTL_RESET_CPU0_CORE,
    /* SYSCTL_RESET_CPU0_APB, */
    /* SYSCTL_RESET_CPU0_TDI, */
    SYSCTL_RESET_CPU0_FLUSH,
    SYSCTL_RESET_CPU1_CORE,
    /* SYSCTL_RESET_CPU1_APB, */
    SYSCTL_RESET_CPU1_FLUSH,
    SYSCTL_RESET_AI,
    SYSCTL_RESET_VPU,
    SYSCTL_RESET_HS,
    SYSCTL_RESET_HS_AHB,
    SYSCTL_RESET_SDIO0,
    SYSCTL_RESET_SDIO1,
    SYSCTL_RESET_SDIO_AXI,
    SYSCTL_RESET_USB0,
    SYSCTL_RESET_USB1,
    SYSCTL_RESET_USB0_AHB,
    SYSCTL_RESET_USB1_AHB,
    SYSCTL_RESET_SPI0,
    SYSCTL_RESET_SPI1,
    SYSCTL_RESET_SPI2,
    SYSCTL_RESET_SEC,
    SYSCTL_RESET_PDMA,
    SYSCTL_RESET_SDMA,
    SYSCTL_RESET_DECOMPRESS,
    SYSCTL_RESET_SRAM,
    SYSCTL_RESET_SHRM_AXIM,
    SYSCTL_RESET_SHRM_AXIS,
    SYSCTL_RESET_SHRM_APB,
    SYSCTL_RESET_NONAI2D,
    SYSCTL_RESET_MCTL,
    SYSCTL_RESET_ISP,
    SYSCTL_RESET_ISP_DW,
    SYSCTL_RESET_CSI0_APB,
    SYSCTL_RESET_CSI1_APB,
    SYSCTL_RESET_CSI2_APB,
    SYSCTL_RESET_CSI_DPHY_APB,
    SYSCTL_RESET_ISP_AHB,
    SYSCTL_RESET_M0,
    SYSCTL_RESET_M1,
    SYSCTL_RESET_M2,
    SYSCTL_RESET_DPU,
    SYSCTL_RESET_DISP,
    SYSCTL_RESET_GPU,
    SYSCTL_RESET_AUDIO,
    SYSCTL_RESET_TIMER0,
    SYSCTL_RESET_TIMER1,
    SYSCTL_RESET_TIMER2,
    SYSCTL_RESET_TIMER3,
    SYSCTL_RESET_TIMER4,
    SYSCTL_RESET_TIMER5,
    SYSCTL_RESET_TIMER_APB,
    SYSCTL_RESET_HDI,
    SYSCTL_RESET_WDT0,
    SYSCTL_RESET_WDT1,
    SYSCTL_RESET_WDT0_APB,
    SYSCTL_RESET_WDT1_APB,
    SYSCTL_RESET_TS_APB,
    SYSCTL_RESET_MAILBOX,
    SYSCTL_RESET_STC,
    SYSCTL_RESET_PMU,
    SYSCTL_RESET_LS_APB,
    SYSCTL_RESET_UART0,
    SYSCTL_RESET_UART1,
    SYSCTL_RESET_UART2,
    SYSCTL_RESET_UART3,
    SYSCTL_RESET_UART4,
    SYSCTL_RESET_I2C0,
    SYSCTL_RESET_I2C1,
    SYSCTL_RESET_I2C2,
    SYSCTL_RESET_I2C3,
    SYSCTL_RESET_I2C4,
    SYSCTL_RESET_JAMLINK0_APB,
    SYSCTL_RESET_JAMLINK1_APB,
    SYSCTL_RESET_JAMLINK2_APB,
    SYSCTL_RESET_JAMLINK3_APB,
    SYSCTL_RESET_CODEC_APB,
    SYSCTL_RESET_GPIO_DB,
    SYSCTL_RESET_GPIO_APB,
    SYSCTL_RESET_ADC,
    SYSCTL_RESET_ADC_APB,
    SYSCTL_RESET_PWM_APB,
    SYSCTL_RESET_SPI2AXI,
} sysctl_reset_e;

typedef enum
{
    SYSCTL_RESET_TIME_CPU0,
    SYSCTL_RESET_TIME_CPU0_APB,
    SYSCTL_RESET_TIME_CPU1,
    SYSCTL_RESET_TIME_CPU1_APB,
    SYSCTL_RESET_TIME_AI,
    SYSCTL_RESET_TIME_VPU,
    SYSCTL_RESET_TIME_HS_HCLK,
    SYSCTL_RESET_TIME_SDCTL,
    SYSCTL_RESET_TIME_USB,
    SYSCTL_RESET_TIME_USB_AHB,
    SYSCTL_RESET_TIME_SPI,
    SYSCTL_RESET_TIME_SEC_SYS,
    SYSCTL_RESET_TIME_DMAC,
    SYSCTL_RESET_TIME_DECOMPRESS,
    SYSCTL_RESET_TIME_SRAM,
    SYSCTL_RESET_TIME_NONAI2D,
    SYSCTL_RESET_TIME_MCTL,
    SYSCTL_RESET_TIME_ISP,
    SYSCTL_RESET_TIME_ISP_DW,
    SYSCTL_RESET_TIME_DPU,
    SYSCTL_RESET_TIME_DISP_SYS,
    SYSCTL_RESET_TIME_V2P5D_SYS,
    SYSCTL_RESET_TIME_AUDIO,
} sysctl_reset_time_e;

/* See TRM 2.1.4, Table 2-1-2 */
typedef struct {
    volatile uint32_t cpu0_rst_tim;         /* 0x00 */
    volatile uint32_t cpu0_rst_ctl;         /* 0x04 */
    volatile uint32_t cpu1_rst_tim;         /* 0x08 */
    volatile uint32_t cpu1_rst_ctl;         /* 0x0c */
    volatile uint32_t ai_rst_tim;           /* 0x10 */
    volatile uint32_t ai_rst_ctl;           /* 0x14 */
    volatile uint32_t vpu_rst_tim;          /* 0x18 */
    volatile uint32_t vpu_rst_ctl;          /* 0x1c */
    volatile uint32_t soc_ctl_rst_ctl;      /* 0x20 */
    volatile uint32_t losys_rst_ctl;        /* 0x24 */
    volatile uint32_t hisys_hclk_tim;       /* 0x28 */
    volatile uint32_t hisys_rst_ctl;        /* 0x2c */
    volatile uint32_t sdctl_rst_tim;        /* 0x30 */
    volatile uint32_t sdc_rst_ctl;          /* 0x34 */
    volatile uint32_t usb_rst_tim;          /* 0x38 */
    volatile uint32_t usb_rst_ctl;          /* 0x3c */
    volatile uint32_t spi_rst_tim;          /* 0x40 */
    volatile uint32_t spi_rst_ctl;          /* 0x44 */
    volatile uint32_t sec_sys_rst_tim;      /* 0x48 */
    volatile uint32_t sec_rst_ctl;          /* 0x4c */
    volatile uint32_t dmac_rst_tim;         /* 0x50 */
    volatile uint32_t dma_rst_ctl;          /* 0x54 */
    volatile uint32_t decompress_rst_tim;   /* 0x58 */
    volatile uint32_t decompress_rst_ctl;   /* 0x5c */
    volatile uint32_t sram_rst_tim;         /* 0x60 */
    volatile uint32_t sram_rst_ctl;         /* 0x64 */
    volatile uint32_t nonai2d_rst_tim;      /* 0x68 */
    volatile uint32_t nonai2d_rst_ctl;      /* 0x6c */
    volatile uint32_t mctl_rst_tim;         /* 0x70 */
    volatile uint32_t mctl_rst_ctl;         /* 0x74 */
    volatile uint32_t isp_rst_tim;          /* 0x78 */
    volatile uint32_t isp_dw_rst_tim;       /* 0x7c */
    volatile uint32_t isp_rst_ctl;          /* 0x80 */
    volatile uint32_t dpu_rst_tim;          /* 0x84 */
    volatile uint32_t dpu_rst_ctl;          /* 0x88 */
    volatile uint32_t disp_sys_rst_tim;     /* 0x8c */
    volatile uint32_t disp_rst_ctl;         /* 0x90 */
    volatile uint32_t v2p5d_sys_rst_tim;    /* 0x94 */
    volatile uint32_t v2p5d_rst_ctl;        /* 0x98 */
    volatile uint32_t reserved;             /* 0x9c */
    volatile uint32_t audio_rst_tim;        /* 0xa0 */
    volatile uint32_t audio_rst_ctl;        /* 0xa4 */
    volatile uint32_t spi2axi_rst_ctl;      /* 0xa8 */
} sysctl_rst_t;

/* Just call this API to reset */
bool sysctl_reset(sysctl_reset_e reset);
bool sysctl_set_reset_time(sysctl_reset_time_e reset, uint32_t tim0, uint32_t tim1, uint32_t tim2);

#endif