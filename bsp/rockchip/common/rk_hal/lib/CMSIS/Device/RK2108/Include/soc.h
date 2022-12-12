/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#ifndef __SOC_H
#define __SOC_H
#ifdef __cplusplus
  extern "C" {
#endif

#ifndef __ASSEMBLY__
/* ================================================================================ */
/* ================                    DMA REQ                      =============== */
/* ================================================================================ */
typedef enum {
    DMA_REQ_UART0_TX = 0,
    DMA_REQ_UART0_RX = 1,
    DMA_REQ_UART1_TX = 2,
    DMA_REQ_UART1_RX = 3,
    DMA_REQ_UART2_TX = 4,
    DMA_REQ_UART2_RX = 5,
    DMA_REQ_I2S0_TX = 6,
    DMA_REQ_I2S0_RX = 7,
    DMA_REQ_I2S1_TX = 8,
    DMA_REQ_I2S1_RX = 9,
    DMA_REQ_PDM0 = 10,
    DMA_REQ_SPI1_TX = 11,
    DMA_REQ_SPI1_RX = 12,
    DMA_REQ_SPI2_TX = 13,
    DMA_REQ_SPI2_RX = 14,
    DMA_REQ_PWM = 15,
    DMA_REQ_AUDIOPWM = 16,
} DMA_REQ_Type;

/* ================================================================================ */
/* ================                       IRQ                      ================ */
/* ================================================================================ */
typedef enum
{
    /******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
    NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
    MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
    BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
    UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
    SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
    DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
    PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
    SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
    /******  RK2108 specific Interrupt Numbers **********************************************************************/
    CACHE_IRQn                  = 0,      /* cortex m4 cache                                            */
    MAILBOX0_AP_IRQn            = 2,      /* Mailbox0 ap                                                */
    MAILBOX0_BB_IRQn            = 3,      /* Mailbox0 bb                                                */
    MAILBOX1_AP_IRQn            = 4,      /* Mailbox1 ap                                                */
    MAILBOX1_BB_IRQn            = 5,      /* Mailbox1 bb                                                */
    MAILBOX2_AP_IRQn            = 6,      /* Mailbox2 ap                                                */
    MAILBOX2_BB_IRQn            = 7,      /* Mailbox2 bb                                                */
    PMU_IRQn                    = 8,      /* PMU                                                        */
    DMAC_IRQn                   = 9,      /* DMAC                                                       */
    DMAC_ABORT_IRQn             = 10,     /* DMA Abort                                                  */
    UART0_IRQn                  = 11,     /* UART 0                                                     */
    UART1_IRQn                  = 12,     /* UART 1                                                     */
    UART2_IRQn                  = 13,     /* UART 2                                                     */
    TIMER0_IRQn                 = 14,     /* Timer 0                                                    */
    TIMER1_IRQn                 = 15,     /* Timer 1                                                    */
    TIMER2_IRQn                 = 16,     /* Timer 2                                                    */
    TIMER3_IRQn                 = 17,     /* Timer 3                                                    */
    TIMER4_IRQn                 = 18,     /* Timer 4                                                    */
    TIMER5_IRQn                 = 19,     /* Timer 5                                                    */
    WDT0_IRQn                   = 20,     /* Watch dog 0                                                */
    WDT1_IRQn                   = 21,     /* Watch dog 1                                                */
    I2CMST0_IRQn                = 22,     /* I2C Master 0                                               */
    I2CMST1_IRQn                = 23,     /* I2C Master 1                                               */
    I2CMST2_IRQn                = 24,     /* I2C Master 2                                               */
    SPISLV0_IRQn                = 25,     /* SPI Slave 0                                                */
    SPIMST1_IRQn                = 26,     /* SPI Master 1                                               */
    FSPI0_IRQn                  = 27,     /* FSPI0                                                      */
    SDIO_IRQn                   = 28,     /* SDIO                                                       */
    GPIO0_IRQn                  = 29,     /* GPIO 0                                                     */
    GPIO1_IRQn                  = 30,     /* GPIO 1                                                     */
    USB_IRQn                    = 31,     /* USB                                                        */
    I2S0_IRQn                   = 32,     /* I2S 0                                                      */
    PDM0_IRQn                   = 33,     /* PDM 0                                                      */
    I2S1_IRQn                   = 34,     /* I2S 1                                                      */
    VAD_IRQn                    = 35,     /* VAD                                                        */
    VOP_IRQn                    = 36,     /* VOP                                                        */
    VOP_POST_LB_IRQn            = 37,     /* VOP post lb                                                */
    MIPI_DSI_HOST_IRQn          = 38,     /* MIPI dsi host                                              */
    TP_IRQn                     = 39,     /* TP                                                         */
    DSP_PFATAL_ERROR_IRQn       = 40,     /* DSP pfatal error                                           */
    PWM_IRQn                    = 41,     /* PWM                                                        */
    PWM_PWR_IRQn                = 42,     /* PWM PWR                                                    */
    AUDIOPWM_IRQn               = 43,     /* AUDIOPWM                                                   */
    VICAP_IRQn                  = 44,     /* VICAP                                                        */
    SPIMST2_IRQn                = 45,     /* SPI Master 2                                               */
    KEY_CTRL_IRQn               = 46,     /* KEY Control                                                */
    FSPI1_IRQn                  = 47,     /* FSPI1                                                      */
    NUM_INTERRUPTS
} IRQn_Type;
#endif /* __ASSEMBLY__ */

#define NVIC_PERIPH_IRQ_NUM MAX_IRQn
#define NVIC_PERIPH_IRQ_OFFSET 16

#define MAILBOX0_AP_IRQ0 MAILBOX0_AP_IRQn
#define MAILBOX0_AP_IRQ1 MAILBOX0_AP_IRQn
#define MAILBOX0_AP_IRQ2 MAILBOX0_AP_IRQn
#define MAILBOX0_AP_IRQ3 MAILBOX0_AP_IRQn

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

#define __CM4_REV                 0x0001U  /* Core revision r0p1                    */
#define __MPU_PRESENT             1U       /* RK2108 provides an MPU                */
#define __VTOR_PRESENT            1U       /* VTOR present */
#define __NVIC_PRIO_BITS          3U       /* RK2108 uses 3 Bits for the Priority Levels   */
#define __Vendor_SysTickConfig    0U       /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1U       /* FPU present                                  */

#ifndef __ASSEMBLY__
#include "core_cm4.h"             /* Cortex-M4 processor and core peripherals */
#include "system_rk2108.h"
#endif /* __ASSEMBLY__ */
#include "rk2108.h"
#include "rk2108_usb.h"

/****************************************************************************************/
/*                                                                                      */
/*                               Module Structure Section                               */
/*                                                                                      */
/****************************************************************************************/

/****************************************************************************************/
/*                                                                                      */
/*                                Module Address Section                                */
/*                                                                                      */
/****************************************************************************************/
/* Memory Base */
#define XIP_MAP0_BASE0      0x18000000U /* FSPI0 map address0 */
#define XIP_MAP1_BASE0      0x1C000000U /* FSPI1 map address0 */
#define DSP_ITCM_BASE       0x30000000U /* DSP itcm base address */
#define DSP_ITCM_END        0x3000ffffU /* DSP itcm end address */
#define DSP_DTCM_BASE       0x30200000U /* DSP dtcm base address */
#define DSP_DTCM_END        0x3027ffffU /* DSP dtcm end address */
#define USB_M31PHY_BASE     0x400B0340U /* USB M31 PHY base address */
#define SDIO_BASE           MMC_BASE    /* 0x40C90000U MMC base address */
#define USB_BASE            0x41300000U /* USB base address */
#define XIP_MAP0_BASE1      0x60000000U /* FSPI0 map address1 */
#define XIP_MAP1_BASE1      0x64000000U /* FSPI1 map address1 */
#define USB_PHY_CON_BASE    (GRF->USBPHY_CON0) /* USB PHY control base address */
#define USB_PHY_STATUS_BASE (GRF->USBPHY_STATUS0) /* USB PHY status base address */
/****************************************************************************************/
/*                                                                                      */
/*                               Module Variable Section                                */
/*                                                                                      */
/****************************************************************************************/
/* Module Variable Define */
#define USB                 ((struct USB_GLOBAL_REG *) USB_BASE)

#define IS_PCD_INSTANCE(instance) ((instance) == USB)
#define IS_HCD_INSTANCE(instance) ((instance) == USB)
/****************************************************************************************/
/*                                                                                      */
/*                               Register Bitmap Section                                */
/*                                                                                      */
/****************************************************************************************/
/*****************************************ICACHE*****************************************/
/* CACHE LINE SIZE */
#define CACHE_LINE_SHIFT                (5U)
#define CACHE_LINE_SIZE                 (0x1U << CACHE_LINE_SHIFT)
#define CACHE_LINE_ADDR_MASK            (0xFFFFFFFFU << CACHE_LINE_SHIFT)
#define CACHE_M_CLEAN                   0x0U
#define CACHE_M_INVALID                 0x2U
#define CACHE_M_CLEAN_INVALID           0x4U
#define CACHE_M_INVALID_ALL             0x6U

/* ICACHE ADDR TO DCACHE ADDR */
#define SRAM_IADDR_START                                   (0x04000000U)
#define SRAM_SIZE                                          (0x00100000U)
#define SRAM_IADDR_TO_DADDR_OFFSET                         (0x1c000000U)
#define XIP_NOR_IADDR_START                                (0x18000000U)
#define XIP_NOR_SIZE                                       (0x04000000U)
#define XIP_NOR_IADDR_TO_DADDR_OFFSET                      (0x48000000U)
#define XIP_PSRAM_IADDR_START                              (0x1C000000U)
#define XIP_PSRAM_SIZE                                     (0x04000000U)
#define XIP_PSRAM_IADDR_TO_DADDR_OFFSET                    (0x48000000U)

#define CACHE_REVISION                  (0x00000100U)
/*****************************************PMU*****************************************/
#ifndef __ASSEMBLY__
typedef enum PD_Id {
    PD_DSP              = 0x80000000U,
    PD_LOGIC            = 0x80011111U,
    PD_SHRM             = 0x80022222U,
    PD_AUDIO            = 0x80033333U,
} ePD_Id;
#endif
/****************************************FSPI********************************************/
#define FSPI_CHIP_CNT                            (2)
/****************************************MMC*********************************************/
#define CLK_SDIO_PLL                             CLK_SDIO_SRC
/****************************************WDT*********************************************/
#define PCLK_WDT                                 PCLK_LOGIC
/****************************************CRU*********************************************/
#define CPU_CLK_ID                               HCLK_M4
#define MEM_CLK_ID                               SCLK_SHRM
#define DSP_CLK_ID                               ACLK_DSP
/****************************************MBOX********************************************/
#define MBOX_CNT             2
#define MBOX_CHAN_CNT        4
/****************************************USB********************************************/
#define USB_PHY_SUSPEND_MASK \
    (GRF_USBPHY_CON0_UTMI_SEL_MASK | GRF_USBPHY_CON0_UTMI_SUSPEND_N_MASK | \
     GRF_USBPHY_CON0_UTMI_OPMODE_MASK | GRF_USBPHY_CON0_UTMI_XCVRSELECT_MASK | \
     GRF_USBPHY_CON0_UTMI_TERMSELECT_MASK | GRF_USBPHY_CON0_UTMI_DPPULLDOWN_MASK |\
     GRF_USBPHY_CON0_UTMI_DMPULLDOWN_MASK)
#define USB_PHY_RESUME_MASK                     GRF_USBPHY_CON0_UTMI_SEL_MASK
#define USB_PHY_CON_SHIFT                       GRF_USBPHY_CON0_UTMI_SEL_SHIFT
#define USB_PHY_LINESTATE_MASK                  GRF_USBPHY_STATUS0_UTMI_LINESTATE_MASK
#define USB_PHY_LINESTATE_SHIFT                 GRF_USBPHY_STATUS0_UTMI_LINESTATE_SHIFT
#define USB_PHY_SUSPEND_VAL                     0x1d1U
#define USB_PHY_RESUME_VAL                      0

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __SOC_H */
