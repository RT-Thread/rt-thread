/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**************************************************************************//**
 * @file     soc.h
 * @brief    CSI Core Peripheral Access Layer Header File for
 *           CSKYSOC Device Series
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef SOC_H
#define SOC_H

#ifdef __cplusplus
extern "C" {
#endif

#define  SYSTEM_CLOCK    (20000000)

/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum IRQn
{
    /* ----------------------  CSKYCK801 Specific Interrupt Numbers  --------------------- */
    GPIOA_IRQn                      =   0,
    CORET_IRQn                      =   1,      /* core Timer Interrupt */
    TIMA0_IRQn                      =   2,      /* timerA0 Interrupt */
    TIMA1_IRQn                      =   3,      /* timerA1 Interrupt */
    WDT_IRQn                        =   5,      /* wdt Interrupt */
    UART0_IRQn                      =   6,      /* uart0 Interrupt */
    UART1_IRQn                      =   7,      /* uart1 Interrupt */
    UART2_IRQn                      =   8,      /* uart2 Interrupt */
    I2C0_IRQn                       =   9,      /* i2c0 Interrupt */
    I2C1_IRQn                       =   10,     /* i2c1 Interrupt */
    SPI1_IRQn                       =   11,     /* spi0 Interrupt */
    SPI0_IRQn                       =   12,     /* spi1 Interrupt */
    RTC_IRQn                        =   13,     /* rtc Interrupt */
    EXTWAK_IRQn                     =   14,     /* extwakeup Interrupt */
    DMAC_IRQn                       =   17,     /* dmac Interrupt */
    PMU_IRQn                        =   18,     /* pmu Interrupt */
    PWM_IRQn                        =   19,     /* pwm Interrupt */
    UART3_IRQn                      =   21,     /* uart3 Interrupt */
    TIMB0_IRQn                      =   23,     /* timerB0 Interrupt */
    TIMB1_IRQn                      =   24,     /* timerB1 Interrupt */
    GPIOB_IRQn                      =   27,     /* GPIOB Interrupt */
    AES_IRQn                        =   26,     /* aes Interrupt */
    RSA_IRQn                        =   28,     /* rsa Interrupt */
    SHA_IRQn                        =   29,     /* sha Interrupt */

}
IRQn_Type;

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* --------  Configuration of the CK801 Processor and Core Peripherals  ------- */
#define __CK802_REV               0x0000U   /* Core revision r0p0 */
#define __MGU_PRESENT             0         /* MGU present or not */
#define __NVIC_PRIO_BITS          2         /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0         /* Set to 1 if different SysTick Config is used */

#include "core_ck802.h"                     /* Processor and core peripherals */
#include "stdint.h"

typedef enum
{
    CKENUM_DMA_UART0_RX,
    CKENUM_DMA_UART0_TX,
    CKENUM_DMA_UART1_RX,
    CKENUM_DMA_UART1_TX,
    CKENUM_DMA_ADC_RX,
    CKENUM_DMA_ADC_TX,
    CKENUM_DMA_SPI1_RX,
    CKENUM_DMA_SPI1_TX,
    CKENUM_DMA_SPI0_RX,
    CKENUM_DMA_SPI0_TX,
    CKENUM_DMA_IIC_RX,
    CKENUM_DMA_IIC_TX,
    CKENUM_DMA_IIC1_RX,
    CKENUM_DMA_IIC1_TX,
    CKENUM_DMA_IIS_RX,
    CKENUM_DMA_IIS_TX,
    CKENUM_DMA_MEMORY
} ckenum_dma_device_e;

/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */
#if 0

/* ================================================================================ */
/* ============== Universal Asyncronous Receiver / Transmitter (UART) ============= */
/* ================================================================================ */
typedef struct
{
    union
    {
        __IM uint32_t RBR;           /* Offset: 0x000 (R/ )  Receive buffer register */
        __OM uint32_t THR;           /* Offset: 0x000 ( /W)  Transmission hold register */
        __IOM uint32_t DLL;          /* Offset: 0x000 (R/W)  Clock frequency division low section register */
    };
    union
    {
        __IOM uint32_t DLH;          /* Offset: 0x004 (R/W)  Clock frequency division high section register */
        __IOM uint32_t IER;          /* Offset: 0x004 (R/W)  Interrupt enable register */
    };
    __IM uint32_t IIR;             /* Offset: 0x008 (R/ )  Interrupt indicia register */
    __IOM uint32_t LCR;            /* Offset: 0x00C (R/W)  Transmission control register */
    __IOM uint32_t MCR;            /* Offset: 0x010 (R/W)  Modem control register */
    __IM uint32_t LSR;             /* Offset: 0x014 (R/ )  Transmission state register */
    __IM uint32_t MSR;             /* Offset: 0x018 (R/ )  Modem state register */
    uint32_t RESERVED1[24];
    __IM uint32_t USR;             /* Offset: 0x07c (R/ )  UART state register */
} CSKY_UART_TypeDef;

/* ================================================================================ */
/* ==============            Inter-Integrated Circuit (IIC)           ============= */
/* ================================================================================ */
typedef struct
{
    __IOM uint32_t IC_CON;                    /* Offset: 0x000 (R/W)  Receive buffer register */
    __IOM uint32_t IC_TAR;                    /* Offset: 0x004 (R/W)  Transmission hold register */
    __IOM uint32_t IC_SAR;                    /* Offset: 0x008 (R/W)  Clock frequency division low section register */
    __IOM uint32_t IC_HS_MADDR;               /* Offset: 0x00c (R/W)  Clock frequency division high section register */
    __IOM uint32_t IC_DATA_CMD;               /* Offset: 0x010 (R/W)  Interrupt enable register */
    __IOM uint32_t IC_SS_SCL_HCNT;            /* Offset: 0x014 (R/W)  Interrupt indicia register */
    __IOM uint32_t IC_SS_SCL_LCNT;            /* Offset: 0x018 (R/W)  Transmission control register */
    __IOM uint32_t IC_FS_SCL_HCNT;            /* Offset: 0x01c (R/W)  Modem control register */
    __IOM uint32_t IC_FS_SCL_LCNT;            /* Offset: 0x020 (R/W)  Transmission state register */
    __IOM uint32_t IC_HS_SCL_HCNT;            /* Offset: 0x024 (R/W)  Transmission state register */
    __IOM uint32_t IC_HS_SCL_LCNT;            /* Offset: 0x028 (R/W)  Transmission state register */
    __IOM uint32_t IC_INTR_STAT;              /* Offset: 0x02c (R)  Transmission state register */
    __IOM uint32_t IC_INTR_MASK;              /* Offset: 0x030 (R/W)  Transmission state register */
    __IOM uint32_t IC_RAW_INTR_STAT;          /* Offset: 0x034 (R)  Transmission state register */
    __IOM uint32_t IC_RX_TL;                  /* Offset: 0x038 (R/W)  Transmission state register */
    __IOM uint32_t IC_TX_TL;                  /* Offset: 0x03c (R/W)  Transmission state register */
    __IOM uint32_t IC_CLR_INTR;               /* Offset: 0x040 (R)  Transmission state register */
    __IOM uint32_t IC_CLR_RX_UNDER;           /* Offset: 0x044 (R)  Transmission state register */
    __IOM uint32_t IC_CLR_RX_OVER;            /* Offset: 0x048 (R)  Transmission state register */
    __IOM uint32_t IC_CLR_TX_OVER;            /* Offset: 0x04c (R)  Transmission state register */
    __IOM uint32_t IC_CLR_RD_REQ;             /* Offset: 0x050 (R)  Transmission state register */
    __IOM uint32_t IC_CLR_TX_ABRT;            /* Offset: 0x054 (R)  Transmission state register */
    __IOM uint32_t IC_CLR_RX_DONE;            /* Offset: 0x058 (R)  Transmission state register */
    __IOM uint32_t IC_CLR_ACTIVITY;           /* Offset: 0x05c (R)  Transmission state register */
    __IOM uint32_t IC_CLR_STOP_DET;           /* Offset: 0x060 (R)  Transmission state register */
    __IOM uint32_t IC_CLR_START_DET;          /* Offset: 0x064 (R)  Transmission state register */
    __IOM uint32_t IC_CLR_GEN_CALL;           /* Offset: 0x068 (R)  Transmission state register */
    __IOM uint32_t IC_ENABLE;                 /* Offset: 0x06c (R/W)  Transmission state register */
    __IOM uint32_t IC_STATUS;                 /* Offset: 0x070 (R)  Transmission state register */
    __IOM uint32_t IC_TXFLR;                  /* Offset: 0x074 (R)  Transmission state register */
    __IOM uint32_t IC_RXFLR;                  /* Offset: 0x078 (R)  Transmission state register */
    uint32_t RESERVED;                        /* Offset: 0x014 (R/ )  Transmission state register */
    __IOM uint32_t IC_TX_ABRT_SOURCE;         /* Offset: 0x080 (R/W)  Transmission state register */
    __IOM uint32_t IC_SAR1;                   /* Offset: 0x084 (R/W)  Transmission state register */
    __IOM uint32_t IC_DMA_CR;                 /* Offset: 0x088 (R/W)  Transmission state register */
    __IOM uint32_t IC_DMA_TDLR;               /* Offset: 0x08c (R/W)  Transmission state register */
    __IOM uint32_t IC_DMA_RDLR;               /* Offset: 0x090 (R/W)  Transmission state register */
    __IOM uint32_t IC_SAR2;                   /* Offset: 0x094 (R/W)  Transmission state register */
    __IOM uint32_t IC_SAR3;                   /* Offset: 0x098 (R/W)  Transmission state register */
    __IOM uint32_t IC_MULTI_SLAVE;            /* Offset: 0x09c (R/W)  Transmission state register */
    __IOM uint32_t IC_GEN_CALL_EN;            /* Offset: 0x0a0 (R/W)  Transmission state register */

} CSKY_IIC_TypeDef;

/* ================================================================================ */
/* ==============                          TIMER                      ============= */
/* ================================================================================ */
typedef struct
{
    __IOM uint32_t TxLoadCount;               /* Offset: 0x000 (R/W)  Receive buffer register */
    __IOM uint32_t TxCurrentValue;            /* Offset: 0x004 (R)  Transmission hold register */
    __IOM uint32_t TxControl;                 /* Offset: 0x008 (R/W)  Clock frequency division low section register */
    __IOM uint32_t TxEOI;                     /* Offset: 0x00c (R)  Clock frequency division high section register */
    __IOM uint32_t TxIntStatus;               /* Offset: 0x010 (R)  Interrupt enable register */

} CSKY_TIMER_TypeDef;

/* ================================================================================ */
/* ==============                    TIMER  Control                   ============= */
/* ================================================================================ */
typedef struct
{
    __IOM uint32_t TimersIntStatus;            /* Offset: 0x000 (R)  Interrupt indicia register */
    __IOM uint32_t TimerEOI;                   /* Offset: 0x004 (R)  Transmission control register */
    __IOM uint32_t TimerRawIntStatus;          /* Offset: 0x008 (R)  Modem control register */

} CSKY_TIMER_Control_TypeDef;

/* ================================================================================ */
/* ==============                        GPIO                         ============= */
/* ================================================================================ */
typedef struct
{
    __IOM uint32_t SWPORT_DR;                 /* Offset: 0x000 (R/W)  Interrupt indicia register */
    __IOM uint32_t SWPORT_DDR;                /* Offset: 0x004 (R/W)  Interrupt indicia register */
    __IOM uint32_t PORT_CTL;                  /* Offset: 0x008 (R/W)  Interrupt indicia register */
} CKStruct_GPIO, *PCKStruct_GPIO;

typedef struct
{
    __IOM uint32_t SHA_CON;                     /* Offset: 0x000 (R/W)  Control register */
    __IOM uint32_t SHA_INTSTATE;                /* Offset: 0x004 (R/W)  Instatus register */
    __IOM uint32_t SHA_H0L;                     /* Offset: 0x008 (R/W)  H0L register */
    __IOM uint32_t SHA_H1L;                     /* Offset: 0x00c (R/W)  H1L register */
    __IOM uint32_t SHA_H2L;                     /* Offset: 0x010 (R/W)  H2L register */
    __IOM uint32_t SHA_H3L;                     /* Offset: 0x014 (R/W)  H3L register */
    __IOM uint32_t SHA_H4L;                     /* Offset: 0x018 (R/W)  H4L register */
    __IOM uint32_t SHA_H5L;                     /* Offset: 0x01c (R/W)  H5L register */
    __IOM uint32_t SHA_H6L;                     /* Offset: 0x020 (R/W)  H6L register */
    __IOM uint32_t SHA_H7L;                     /* Offset: 0x024 (R/W)  H7L register */
    __IOM uint32_t SHA_H0H;                     /* Offset: 0x028 (R/W)  H0H register */
    __IOM uint32_t SHA_H1H;                     /* Offset: 0x02c (R/W)  H1H register */
    __IOM uint32_t SHA_H2H;                     /* Offset: 0x030 (R/W)  H2H register */
    __IOM uint32_t SHA_H3H;                     /* Offset: 0x034 (R/W)  H3H register */
    __IOM uint32_t SHA_H4H;                     /* Offset: 0x038 (R/W)  H4H register */
    __IOM uint32_t SHA_H5H;                     /* Offset: 0x03c (R/W)  H5H register */
    __IOM uint32_t SHA_H6H;                     /* Offset: 0x040 (R/W)  H6H register */
    __IOM uint32_t SHA_H7H;                     /* Offset: 0x044 (R/W)  H7H register */
    __IOM uint32_t SHA_DATA1;                   /* Offset: 0x048 (R/W)  DATA1 register */
    uint32_t REV[15];
    __IOM uint32_t SHA_DATA2;                   /* Offset: 0x088 (R/W)  DATA2 register */
} CSKY_SHA_TypeDef;

#endif

#define CONFIG_CRC_NUM  1
#define CONFIG_IIC_NUM  2
#define CONFIG_TRNG_NUM 1
#define CONFIG_EFLASH_NUM 1
#define CONFIG_AES_NUM  1
#define CONFIG_RSA_NUM  1
#define CONFIG_SHA_NUM  1
#define CONFIG_SPI_NUM  2
#define CONFIG_PWM_NUM  1
#define CONFIG_TIMER_NUM 4
#define CONFIG_RTC_NUM 1
#define CONFIG_WDT_NUM 1
#define CONFIG_DMAC_NUM 1
#define CONFIG_ETH_NUM 2

#define CSKY_I2C0_BASE             (0x50014000UL)
#define CSKY_I2C1_BASE             (0x60014000UL)

#define CONFIG_USART_NUM 4
#define CSKY_UART0_BASE            (0x50010000UL)
#define CSKY_UART1_BASE            (0x50010400UL)
#define CSKY_UART2_BASE            (0x60010000UL)
#define CSKY_UART3_BASE            (0x60010400UL)

/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */
/* --------------------------  CPU FPGA memory map  ------------------------------- */
#define CSKY_EFLASH_BASE           (0x10000000UL)
#define CSKY_SRAM_BASE             (0x20000000UL)

#define CSKY_PMU_BASE              (0x40000000UL)
#define CSKY_DMA_BASE              (0x40001000UL)
#define CSKY_EFLASH_CONTROL_BASE   (0x40005000UL)
#define CSKY_OTP_BASE              (0x40006000UL)
#define CSKY_SRAM_CONTROL_BASE     (0x40009000UL)
#define CSKY_AES_BASE              (0x4000d000UL)
#define CSKY_SHA_BASE              (0x4000e000UL)
#define CSKY_RSA_BASE              (0x4000f000UL)
#define CSKY_CRC_BASE              (0x40010000UL)
#define CSKY_TRNG_BASE             (0x40015000UL)
#define CSKY_TIMERA0_BASE          (0x50000000UL)
#define CSKY_TIMERA1_BASE          (0x50000014UL)
#define CSKY_TIMERA_CONTROL_BASE   (0x500000a0UL)
#define CSKY_RTC_BASE              (0x50004000UL)
#define CSKY_WDT_BASE              (0x50008000UL)
#define CSKY_SPI0_BASE             (0x5000c000UL)

#define CONFIG_GPIO_NUM            2
#define CONFIG_GPIO_PIN_NUM        43
#define CSKY_GPIOA_BASE            (0x50018000UL)
#define CSKY_GPIOA_CONTROL_BASE    (0x50018030UL)
#define CSKY_PWM_BASE              (0x5001c000UL)
#define CSKY_ADC_BASE              (0x50020000UL)
#define CSKY_I2S0_BASE             (0x50030000UL)
#define CSKY_TIMERB0_BASE          (0x60000000UL)
#define CSKY_TIMERB1_BASE          (0x60000014UL)
#define CSKY_SPI1_BASE             (0x6000c000UL)

#define CSKY_GPIOB_BASE            (0x60018000UL)
#define CSKY_GPIOB_CONTROL_BASE    (0x60018030UL)
#define CSKY_TIMERB_CONTROL_BASE   (0x600000a0UL)
#define CSKY_SIPC_BASE             (0x6001c000UL)
#define CSKY_I2S1_BASE             (0x60020000UL)
#define CSKY_ETB_BASE              (0x60024000UL)
#define CSKY_USI_BASE              (0x60028000UL)

/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */
#define CSKY_UART1                 ((   CSKY_UART_TypeDef *)    CSKY_UART1_BASE)
#define CSKY_SHA                   ((   CSKY_SHA_TypeDef *)     CSKY_SHA_BASE)

#ifdef __cplusplus
}
#endif

#endif  /* SOC_H */
