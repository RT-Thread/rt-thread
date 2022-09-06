/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef __MM32F3277G_H__
#define __MM32F3277G_H__

/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS 76                 /**< Number of interrupts in the Vector table */

typedef enum IRQ {
  NMI_IRQn                              = -14,                                   /*!< Non Maskable Interrupt                 */
  HardFault_IRQn                        = -13,                                   /*!< Cortex-M3 SV Hard Fault Interrupt   */
  MemManage_IRQn                        = -12,                                   /*!< Cortex-M3 Memory Management Interrupt  */
  BusFault_IRQn                         = -11,                                   /*!< Cortex-M3 Bus Fault Interrupt  */
  UsageFault_IRQn                       = -10,                                   /*!< Cortex-M3 Usage Fault Interrupt  */
  SVCall_IRQn                           = -4,                                    /*!< Cortex-M3 SV Call Interrupt  */
  DebugMonitor_IRQn                     = -3,                                    /*!< Cortex-M3 Debug Monitor Interrupt  */
  PendSV_IRQn                           = -2,                                    /*!< Cortex-M3 Pend SV Interrupt  */
  SysTick_IRQn                          = -1,                                    /*!< Cortex-M3 System Tick Interrupt  */
  WWDG_IWDG_IRQn                        = 0,                                     /*!< Window watchdog interrupt */
  PVD_VDT_IRQn                          = 1,                                     /*!< (PVD) and (VDT) interrupt */
  TAMPER_IRQn                           = 2,                                     /*!< Intrusion detection interrupted */
  RTC_IRQn                              = 3,                                     /*!< RTC global interrupt */
  FLASH_IRQn                            = 4,                                     /*!< Flash global interrupt */
  RCC_CRS_IRQn                          = 5,                                     /*!< RCC and CRS global interrupt */
  EXTI0_IRQn                            = 6,                                     /*!< EXTI line 0 interrupt */
  EXTI1_IRQn                            = 7,                                     /*!< EXTI line 1 interrupted */
  EXTI2_IRQn                            = 8,                                     /*!< EXTI line 2 interrupted */
  EXTI3_IRQn                            = 9,                                     /*!< EXTI line 3 interrupted */
  EXTI4_IRQn                            = 10,                                    /*!< EXTI line 4 interrupted */
  DMA1_CH1_IRQn                         = 11,                                    /*!< DMA1 channel 1 global interrupt */
  DMA1_CH2_IRQn                         = 12,                                    /*!< DMA1 channel 2 global interrupt */
  DMA1_CH3_IRQn                         = 13,                                    /*!< DMA1 channel 3 global interrupt */
  DMA1_CH4_IRQn                         = 14,                                    /*!< DMA1 channel 4 global interrupt */
  DMA1_CH5_IRQn                         = 15,                                    /*!< DMA1 channel 5 global interrupt */
  DMA1_CH6_IRQn                         = 16,                                    /*!< DMA1 channel 6 global interrupt */
  DMA1_CH7_IRQn                         = 17,                                    /*!< DMA1 channel 7 global interrupt */
  ADC1_ADC2_IRQn                        = 18,                                    /*!< ADC1 and ADC2 global interrupt */
  Cache_IRQn                            = 19,                                    /*!< Cache global interrupt */
  CAN1_RX_IRQn                          = 21,                                    /*!< CAN1 accept interrupt */
  EXTI9_5_IRQn                          = 23,                                    /*!< EXTI line [9:5] is interrupted */
  TIM1_BRK_IRQn                         = 24,                                    /*!< TIM1 brake interruption */
  TIM1_UP_IRQn                          = 25,                                    /*!< TIM1 update interrupt */
  TIM1_TRG_COM_IRQn                     = 26,                                    /*!< TIM1 trigger, communication interruption */
  TIM1_CC_IRQn                          = 27,                                    /*!< TIM1 capture compare interrupt */
  TIM2_IRQn                             = 28,                                    /*!< TIM2 global interrupt */
  TIM3_IRQn                             = 29,                                    /*!< TIM3 global interrupt */
  TIM4_IRQn                             = 30,                                    /*!< TIM4 global interrupt */
  I2C1_IRQn                             = 31,                                    /*!< I2C1 global interrupt */
  I2C2_IRQn                             = 33,                                    /*!< I2C2 global interrupt */
  SPI1_IRQn                             = 35,                                    /*!< SPI1 global interrupt */
  SPI2_IRQn                             = 36,                                    /*!< SPI2 global interrupt */
  UART1_IRQn                            = 37,                                    /*!< UART1 global interrupt */
  UART2_IRQn                            = 38,                                    /*!< UART2 global interrupt */
  UART3_IRQn                            = 39,                                    /*!< UART3 global interrupt */
  EXTI15_10_IRQn                        = 40,                                    /*!< EXTI line [15:10] is interrupted */
  RTC_Alarm_IRQn                        = 41,                                    /*!< RTC alarm interrupt */
  USB_WKUP_IRQn                         = 42,                                    /*!< USB wakeup interrupt */
  TIM8_BRK_IRQn                         = 43,                                    /*!< TIM8 brake interruption */
  TIM8_UP_IRQn                          = 44,                                    /*!< TIM8 update interrupt */
  TIM8_TRG_COM_IRQn                     = 45,                                    /*!< TIM8 trigger, communication interruption */
  TIM8_CC_IRQn                          = 46,                                    /*!< TIM8 capture compare interrupt */
  ADC3_IRQn                             = 47,                                    /*!< ADC3 global interrupt */
  SDIO_IRQn                             = 49,                                    /*!< SDIO global interrupt */
  TIM5_IRQn                             = 50,                                    /*!< TIM5 global interrupt */
  SPI3_IRQn                             = 51,                                    /*!< SPI3 global interrupt */
  UART4_IRQn                            = 52,                                    /*!< UART4 global interrupt */
  UART5_IRQn                            = 53,                                    /*!< UART5 global interrupt */
  TIM6_IRQn                             = 54,                                    /*!< TIM6 global interrupt */
  TIM7_IRQn                             = 55,                                    /*!< TIM7 global interrupt */
  DMA2_CH1_IRQn                         = 56,                                    /*!< DMA2 channel 1 global interrupt */
  DMA2_CH2_IRQn                         = 57,                                    /*!< DMA2 channel 2 global interrupt */
  DMA2_CH3_IRQn                         = 58,                                    /*!< DMA2 channel 3 global interrupt */
  DMA2_CH4_IRQn                         = 59,                                    /*!< DMA2 channel 4 global interrupt */
  DMA2_CH5_IRQn                         = 60,                                    /*!< DMA2 channel 5 global interrupt */
  ETHERNET_MAC_IRQn                     = 61,                                    /*!< ETHERNET global interrupt */
  COMP1_2_IRQn                          = 64,                                    /*!< Comparator 1/2 interrupt */
  USB_FS_IRQn                           = 67,                                    /*!< USB FS global interrupt */
  UART6_IRQn                            = 71,                                    /*!< UART6 global interrupt */
  UART7_IRQn                            = 82,                                    /*!< UART7 global interrupt */
  UART8_IRQn                            = 83,                                    /*!< UART8 global interrupt */
} IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Cortex M3 Core Configuration
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Cortex_Core_Configuration Cortex M33 Core Configuration
 * @{
 */

#define __MPU_PRESENT                  0         /**< Defines if an MPU is present or not */
#define __NVIC_PRIO_BITS               3         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig         0         /**< Vendor specific implementation of SysTickConfig is defined */
#define __FPU_PRESENT                  0         /**< Defines if an FPU is present or not */
#define __DSP_PRESENT                  0         /**< Defines if Armv8-M Mainline core supports DSP instructions */
#define __SAUREGION_PRESENT            0         /**< Defines if an SAU is present or not */

#include "core_cm3.h"                 /* Core Peripheral Access Layer */

/*!
 * @}
 */ /* end of group Cortex_Core_Configuration */




/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* 定义大存储块映射基址 */
#define FLASH_ADDR_BASE    0x08000000u
#define EEPROM_BASE        0x08100000u
#define SRAM_BASE          0x20000000u

#define APB1_BASE          0x40000000u
#define APB2_BASE          0x40010000u

#define AHB1_1_BASE        0x40020000u
#define AHB1_2_BASE        0x40040000u
#define AHB2_BASE          0x50000000u
#define AHB3_BASE          0x60000000u

#define FSMC_BANK0_BASE    0x60000000u
#define FSMC_BANK1_BASE    0x64000000u
#define FSMC_BANK2_BASE    0x68000000u
#define FSMC_BANK3_BASE    0x6C000000u
/* 定义外设模块映射基址 */

#define TIM2_BASE     (APB1_BASE)
#define TIM3_BASE     (APB1_BASE + 0x0400)
#define TIM4_BASE     (APB1_BASE + 0x0800)
#define TIM5_BASE     (APB1_BASE + 0x0C00)
#define TIM6_BASE     (APB1_BASE + 0x1000)
#define TIM7_BASE     (APB1_BASE + 0x1400)
#define RTC_BKP_BASE  (APB1_BASE + 0x2800)
#define WWDG_BASE     (APB1_BASE + 0x2C00)
#define IWDG_BASE     (APB1_BASE + 0x3000)
#define SPI2_BASE     (APB1_BASE + 0x3800)
#define SPI3_BASE     (APB1_BASE + 0x3C00)
#define UART2_BASE    (APB1_BASE + 0x4400)
#define UART3_BASE    (APB1_BASE + 0x4800)
#define UART4_BASE    (APB1_BASE + 0x4C00)
#define UART5_BASE    (APB1_BASE + 0x5000)
#define I2C1_BASE     (APB1_BASE + 0x5400)
#define I2C2_BASE     (APB1_BASE + 0x5800)
#define CAN_BASE      (APB1_BASE + 0x6400)
#define CRS_BASE      (APB1_BASE + 0x6C00)
#define PWR_BASE      (APB1_BASE + 0x7000)
#define DAC_BASE      (APB1_BASE + 0x7400)
#define UART7_BASE    (APB1_BASE + 0x7800)
#define UART8_BASE    (APB1_BASE + 0x7C00)

#define SYSCFG_BASE   (APB2_BASE)
#define EXTI_BASE     (APB2_BASE + 0x0400)
#define ADC1_BASE     (APB2_BASE + 0x2400)
#define ADC2_BASE     (APB2_BASE + 0x2800)
#define TIM1_BASE     (APB2_BASE + 0x2C00)
#define SPI1_BASE     (APB2_BASE + 0x3000)
#define TIM8_BASE     (APB2_BASE + 0x3400)
#define UART1_BASE    (APB2_BASE + 0x3800)
#define UART6_BASE    (APB2_BASE + 0x3C00)
#define COMP_BASE     (APB2_BASE + 0x4000)
#define ADC3_BASE     (APB2_BASE + 0x4C00)
#define CACHE_BASE    (APB2_BASE + 0x6000)
#define SDIO_BASE     (APB2_BASE + 0x8000)

#define DMA1_BASE     (AHB1_1_BASE)
#define DMA2_BASE     (AHB1_1_BASE + 0x0400)
#define RCC_BASE      (AHB1_1_BASE + 0x1000)
#define FLASH_BASE    (AHB1_1_BASE + 0x2000)
#define CRC_BASE      (AHB1_1_BASE + 0x3000)
#define ETHERNET_BASE (AHB1_1_BASE + 0x8000)

#define GPIOA_BASE    (AHB1_2_BASE)
#define GPIOB_BASE    (AHB1_2_BASE + 0x400)
#define GPIOC_BASE    (AHB1_2_BASE + 0x800)
#define GPIOD_BASE    (AHB1_2_BASE + 0xC00)
#define GPIOE_BASE    (AHB1_2_BASE + 0x1000)
#define GPIOF_BASE    (AHB1_2_BASE + 0x1400)
#define GPIOG_BASE    (AHB1_2_BASE + 0x1800)
#define GPIOH_BASE    (AHB1_2_BASE + 0x1C00)

#define USB_FS_OTG_BASE (AHB2_BASE)

#define FSMC_BASE     (AHB3_BASE + 0x40000000)

/*!
 * @addtogroup FLASH_Peripheral_Access_Layer FLASH Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * FLASH Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t ACR;                                                            ///< Flash access control register                offset: 0x00
    __IO uint32_t KEYR;                                                           ///< FPEC key register                            offset: 0x04
    __IO uint32_t OPTKEYR;                                                        ///< Flash OPTKEY register                        offset: 0x08
    __IO uint32_t SR;                                                             ///< Flash Status Register                        offset: 0x0C
    __IO uint32_t CR;                                                             ///< Flash control register                       offset: 0x10
    __IO uint32_t AR;                                                             ///< Flash address register                       offset: 0x14
    __IO uint32_t Reserved0[1];                                                   ///< Reserved
    __IO uint32_t OBR;                                                            ///< Option byte register                         offset: 0x1C
    __IO uint32_t WRPR;                                                           ///< Write protection register                    offset: 0x20
} FLASH_Type;

/*******************************************************************************
 * FLASH Type
 ******************************************************************************/

/*!
 * @addtogroup FLASH_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief FLASH_ACR Register Bit Definition
 */

#define FLASH_ACR_PRFTBS_SHIFT                  (5)
#define FLASH_ACR_PRFTBS_MASK                   (0x01U << FLASH_ACR_PRFTBS_SHIFT)
#define FLASH_ACR_PRFTBS(x)                     (((uint32_t)(((uint32_t)(x)) << FLASH_ACR_PRFTBS_SHIFT)) & FLASH_ACR_PRFTBS_MASK)

#define FLASH_ACR_PRFTBE_SHIFT                  (4)
#define FLASH_ACR_PRFTBE_MASK                   (0x01U << FLASH_ACR_PRFTBE_SHIFT)
#define FLASH_ACR_PRFTBE(x)                     (((uint32_t)(((uint32_t)(x)) << FLASH_ACR_PRFTBE_SHIFT)) & FLASH_ACR_PRFTBE_MASK)

#define FLASH_ACR_LATENCY_SHIFT                 (0)
#define FLASH_ACR_LATENCY_MASK                  (0x7U << FLASH_ACR_LATENCY_SHIFT)
#define FLASH_ACR_LATENCY(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_ACR_LATENCY_SHIFT)) & FLASH_ACR_LATENCY_MASK)

/*!
 * @brief FLASH_KEYR Register Bit Definition
 */

#define FLASH_KEYR_FKEYR_SHIFT                  (0)
#define FLASH_KEYR_FKEYR_MASK                   (0xFFFFFFFFU << FLASH_KEYR_FKEYR_SHIFT)
#define FLASH_KEYR_FKEYR(x)                     (((uint32_t)(((uint32_t)(x)) << FLASH_KEYR_FKEYR_SHIFT)) & FLASH_KEYR_FKEYR_MASK)

/*!
 * @brief FLASH_OPTKEYR Register Bit Definition
 */

#define FLASH_OPTKEYR_OPTKEYR_SHIFT             (0)
#define FLASH_OPTKEYR_OPTKEYR_MASK              (0xFFFFFFFFU << FLASH_OPTKEYR_OPTKEYR_SHIFT)
#define FLASH_OPTKEYR_OPTKEYR(x)                (((uint32_t)(((uint32_t)(x)) << FLASH_OPTKEYR_OPTKEYR_SHIFT)) & FLASH_OPTKEYR_OPTKEYR_MASK)

/*!
 * @brief FLASH_SR Register Bit Definition
 */

#define FLASH_SR_EOP_SHIFT                      (5)
#define FLASH_SR_EOP_MASK                       (0x01U << FLASH_SR_EOP_SHIFT)
#define FLASH_SR_EOP(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_SR_EOP_SHIFT)) & FLASH_SR_EOP_MASK)

#define FLASH_SR_WRPRTERR_SHIFT                 (4)
#define FLASH_SR_WRPRTERR_MASK                  (0x01U << FLASH_SR_WRPRTERR_SHIFT)
#define FLASH_SR_WRPRTERR(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_SR_WRPRTERR_SHIFT)) & FLASH_SR_WRPRTERR_MASK)

#define FLASH_SR_PGERR_SHIFT                    (2)
#define FLASH_SR_PGERR_MASK                     (0x01U << FLASH_SR_PGERR_SHIFT)
#define FLASH_SR_PGERR(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_SR_PGERR_SHIFT)) & FLASH_SR_PGERR_MASK)

#define FLASH_SR_BSY_SHIFT                      (0)
#define FLASH_SR_BSY_MASK                       (0x01U << FLASH_SR_BSY_SHIFT)
#define FLASH_SR_BSY(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_SR_BSY_SHIFT)) & FLASH_SR_BSY_MASK)

/*!
 * @brief FLASH_CR Register Bit Definition
 */

#define FLASH_CR_OPTWRE_SHIFT                   (9)
#define FLASH_CR_OPTWRE_MASK                    (0x01U << FLASH_CR_OPTWRE_SHIFT)
#define FLASH_CR_OPTWRE(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_CR_OPTWRE_SHIFT)) & FLASH_CR_OPTWRE_MASK)

#define FLASH_CR_LOCK_SHIFT                     (7)
#define FLASH_CR_LOCK_MASK                      (0x01U << FLASH_CR_LOCK_SHIFT)
#define FLASH_CR_LOCK(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_CR_LOCK_SHIFT)) & FLASH_CR_LOCK_MASK)

#define FLASH_CR_STRT_SHIFT                     (6)
#define FLASH_CR_STRT_MASK                      (0x01U << FLASH_CR_STRT_SHIFT)
#define FLASH_CR_STRT(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_CR_STRT_SHIFT)) & FLASH_CR_STRT_MASK)

#define FLASH_CR_OPTER_SHIFT                    (5)
#define FLASH_CR_OPTER_MASK                     (0x01U << FLASH_CR_OPTER_SHIFT)
#define FLASH_CR_OPTER(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_CR_OPTER_SHIFT)) & FLASH_CR_OPTER_MASK)

#define FLASH_CR_OPTPG_SHIFT                    (4)
#define FLASH_CR_OPTPG_MASK                     (0x01U << FLASH_CR_OPTPG_SHIFT)
#define FLASH_CR_OPTPG(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_CR_OPTPG_SHIFT)) & FLASH_CR_OPTPG_MASK)

#define FLASH_CR_MER_SHIFT                      (2)
#define FLASH_CR_MER_MASK                       (0x01U << FLASH_CR_MER_SHIFT)
#define FLASH_CR_MER(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_CR_MER_SHIFT)) & FLASH_CR_MER_MASK)

#define FLASH_CR_PER_SHIFT                      (1)
#define FLASH_CR_PER_MASK                       (0x01U << FLASH_CR_PER_SHIFT)
#define FLASH_CR_PER(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_CR_PER_SHIFT)) & FLASH_CR_PER_MASK)

#define FLASH_CR_PG_SHIFT                       (0)
#define FLASH_CR_PG_MASK                        (0x01U << FLASH_CR_PG_SHIFT)
#define FLASH_CR_PG(x)                          (((uint32_t)(((uint32_t)(x)) << FLASH_CR_PG_SHIFT)) & FLASH_CR_PG_MASK)

/*!
 * @brief FLASH_AR Register Bit Definition
 */

#define FLASH_AR_FAR_SHIFT                      (0)
#define FLASH_AR_FAR_MASK                       (0xFFFFFFFFU << FLASH_AR_FAR_SHIFT)
#define FLASH_AR_FAR(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_AR_FAR_SHIFT)) & FLASH_AR_FAR_MASK)

/*!
 * @brief FLASH_OBR Register Bit Definition
 */

#define FLASH_OBR_DATA1_SHIFT                   (18)
#define FLASH_OBR_DATA1_MASK                    (0xFFU << FLASH_OBR_DATA1_SHIFT)
#define FLASH_OBR_DATA1(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_OBR_DATA1_SHIFT)) & FLASH_OBR_DATA1_MASK)

#define FLASH_OBR_DATA0_SHIFT                   (10)
#define FLASH_OBR_DATA0_MASK                    (0xFFU << FLASH_OBR_DATA0_SHIFT)
#define FLASH_OBR_DATA0(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_OBR_DATA0_SHIFT)) & FLASH_OBR_DATA0_MASK)

#define FLASH_OBR_NBOOT1_SHIFT                  (6)
#define FLASH_OBR_NBOOT1_MASK                   (0x01U << FLASH_OBR_NBOOT1_SHIFT)
#define FLASH_OBR_NBOOT1(x)                     (((uint32_t)(((uint32_t)(x)) << FLASH_OBR_NBOOT1_SHIFT)) & FLASH_OBR_NBOOT1_MASK)

#define FLASH_OBR_NRSTSTDBY_SHIFT               (4)
#define FLASH_OBR_NRSTSTDBY_MASK                (0x01U << FLASH_OBR_NRSTSTDBY_SHIFT)
#define FLASH_OBR_NRSTSTDBY(x)                  (((uint32_t)(((uint32_t)(x)) << FLASH_OBR_NRSTSTDBY_SHIFT)) & FLASH_OBR_NRSTSTDBY_MASK)

#define FLASH_OBR_NRSTSTOP_SHIFT                (3)
#define FLASH_OBR_NRSTSTOP_MASK                 (0x01U << FLASH_OBR_NRSTSTOP_SHIFT)
#define FLASH_OBR_NRSTSTOP(x)                   (((uint32_t)(((uint32_t)(x)) << FLASH_OBR_NRSTSTOP_SHIFT)) & FLASH_OBR_NRSTSTOP_MASK)

#define FLASH_OBR_WDGSW_SHIFT                   (2)
#define FLASH_OBR_WDGSW_MASK                    (0x01U << FLASH_OBR_WDGSW_SHIFT)
#define FLASH_OBR_WDGSW(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_OBR_WDGSW_SHIFT)) & FLASH_OBR_WDGSW_MASK)

#define FLASH_OBR_RDPRT_SHIFT                   (1)
#define FLASH_OBR_RDPRT_MASK                    (0x01U << FLASH_OBR_RDPRT_SHIFT)
#define FLASH_OBR_RDPRT(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_OBR_RDPRT_SHIFT)) & FLASH_OBR_RDPRT_MASK)

#define FLASH_OBR_OPTERR_SHIFT                  (0)
#define FLASH_OBR_OPTERR_MASK                   (0x01U << FLASH_OBR_OPTERR_SHIFT)
#define FLASH_OBR_OPTERR(x)                     (((uint32_t)(((uint32_t)(x)) << FLASH_OBR_OPTERR_SHIFT)) & FLASH_OBR_OPTERR_MASK)

/*!
 * @brief FLASH_WRPR Register Bit Definition
 */

#define FLASH_WRPR_WRP_SHIFT                    (0)
#define FLASH_WRPR_WRP_MASK                     (0xFFFFFFFFU << FLASH_WRPR_WRP_SHIFT)
#define FLASH_WRPR_WRP(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_WRPR_WRP_SHIFT)) & FLASH_WRPR_WRP_MASK)

/*!
 * @}
 */ /* end of group FLASH_Register_Masks */
/******************************************************************************
 * FLASH Instance
******************************************************************************/
#define FLASH                               ((FLASH_Type*)FLASH_BASE)

/*!
 * @}
 */ /* end of group FLASH_Peripheral_Access_Layer */



/*!
 * @addtogroup CACHE_Peripheral_Access_Layer CACHE Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * CACHE Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CCR;                                                            ///< Configuration and control register           offset: 0x00
    __IO uint32_t SR;                                                             ///< Status register                              offset: 0x04
    __IO uint32_t IMR;                                                            ///< Interrupt mask register                      offset: 0x08
    __IO uint32_t ISR;                                                            ///< Interrupt status register                    offset: 0x0C
    __IO uint32_t Reserved1[1];                                                   ///< Reserved
    __IO uint32_t CSHR;                                                           ///< Hit Statistics Register                      offset: 0x14
    __IO uint32_t CSMR;                                                           ///< Lost Statistics Register                     offset: 0x18
} CACHE_Type;

/*******************************************************************************
 * CACHE Type
 ******************************************************************************/

/*!
 * @addtogroup CACHE_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief CACHE_CCR Register Bit Definition
 */

#define CACHE_CCR_STATISTICEN_SHIFT             (6)
#define CACHE_CCR_STATISTICEN_MASK              (0x01U << CACHE_CCR_STATISTICEN_SHIFT)
#define CACHE_CCR_STATISTICEN(x)                (((uint32_t)(((uint32_t)(x)) << CACHE_CCR_STATISTICEN_SHIFT)) & CACHE_CCR_STATISTICEN_MASK)

#define CACHE_CCR_SETPREFETCH_SHIFT             (5)
#define CACHE_CCR_SETPREFETCH_MASK              (0x01U << CACHE_CCR_SETPREFETCH_SHIFT)
#define CACHE_CCR_SETPREFETCH(x)                (((uint32_t)(((uint32_t)(x)) << CACHE_CCR_SETPREFETCH_SHIFT)) & CACHE_CCR_SETPREFETCH_MASK)

#define CACHE_CCR_SETMANINV_SHIFT               (4)
#define CACHE_CCR_SETMANINV_MASK                (0x01U << CACHE_CCR_SETMANINV_SHIFT)
#define CACHE_CCR_SETMANINV(x)                  (((uint32_t)(((uint32_t)(x)) << CACHE_CCR_SETMANINV_SHIFT)) & CACHE_CCR_SETMANINV_MASK)

#define CACHE_CCR_SETMANPOW_SHIFT               (3)
#define CACHE_CCR_SETMANPOW_MASK                (0x01U << CACHE_CCR_SETMANPOW_SHIFT)
#define CACHE_CCR_SETMANPOW(x)                  (((uint32_t)(((uint32_t)(x)) << CACHE_CCR_SETMANPOW_SHIFT)) & CACHE_CCR_SETMANPOW_MASK)

#define CACHE_CCR_POWREQ_SHIFT                  (2)
#define CACHE_CCR_POWREQ_MASK                   (0x01U << CACHE_CCR_POWREQ_SHIFT)
#define CACHE_CCR_POWREQ(x)                     (((uint32_t)(((uint32_t)(x)) << CACHE_CCR_POWREQ_SHIFT)) & CACHE_CCR_POWREQ_MASK)

#define CACHE_CCR_INVREQ_SHIFT                  (1)
#define CACHE_CCR_INVREQ_MASK                   (0x01U << CACHE_CCR_INVREQ_SHIFT)
#define CACHE_CCR_INVREQ(x)                     (((uint32_t)(((uint32_t)(x)) << CACHE_CCR_INVREQ_SHIFT)) & CACHE_CCR_INVREQ_MASK)

#define CACHE_CCR_EN_SHIFT                      (0)
#define CACHE_CCR_EN_MASK                       (0x01U << CACHE_CCR_EN_SHIFT)
#define CACHE_CCR_EN(x)                         (((uint32_t)(((uint32_t)(x)) << CACHE_CCR_EN_SHIFT)) & CACHE_CCR_EN_MASK)

/*!
 * @brief CACHE_SR Register Bit Definition
 */

#define CACHE_SR_POWSTAT_SHIFT                  (4)
#define CACHE_SR_POWSTAT_MASK                   (0x01U << CACHE_SR_POWSTAT_SHIFT)
#define CACHE_SR_POWSTAT(x)                     (((uint32_t)(((uint32_t)(x)) << CACHE_SR_POWSTAT_SHIFT)) & CACHE_SR_POWSTAT_MASK)

#define CACHE_SR_INVSTAT_SHIFT                  (2)
#define CACHE_SR_INVSTAT_MASK                   (0x01U << CACHE_SR_INVSTAT_SHIFT)
#define CACHE_SR_INVSTAT(x)                     (((uint32_t)(((uint32_t)(x)) << CACHE_SR_INVSTAT_SHIFT)) & CACHE_SR_INVSTAT_MASK)

#define CACHE_SR_CS_SHIFT                       (0)
#define CACHE_SR_CS_MASK                        (0x3U << CACHE_SR_CS_SHIFT)
#define CACHE_SR_CS(x)                          (((uint32_t)(((uint32_t)(x)) << CACHE_SR_CS_SHIFT)) & CACHE_SR_CS_MASK)

/*!
 * @brief CACHE_IMR Register Bit Definition
 */

#define CACHE_IMR_MANINVERR_SHIFT               (1)
#define CACHE_IMR_MANINVERR_MASK                (0x01U << CACHE_IMR_MANINVERR_SHIFT)
#define CACHE_IMR_MANINVERR(x)                  (((uint32_t)(((uint32_t)(x)) << CACHE_IMR_MANINVERR_SHIFT)) & CACHE_IMR_MANINVERR_MASK)

#define CACHE_IMR_POWERR_SHIFT                  (0)
#define CACHE_IMR_POWERR_MASK                   (0x01U << CACHE_IMR_POWERR_SHIFT)
#define CACHE_IMR_POWERR(x)                     (((uint32_t)(((uint32_t)(x)) << CACHE_IMR_POWERR_SHIFT)) & CACHE_IMR_POWERR_MASK)

/*!
 * @brief CACHE_ISR Register Bit Definition
 */

#define CACHE_ISR_MANINVERR_SHIFT               (1)
#define CACHE_ISR_MANINVERR_MASK                (0x01U << CACHE_ISR_MANINVERR_SHIFT)
#define CACHE_ISR_MANINVERR(x)                  (((uint32_t)(((uint32_t)(x)) << CACHE_ISR_MANINVERR_SHIFT)) & CACHE_ISR_MANINVERR_MASK)

#define CACHE_ISR_POWERR_SHIFT                  (0)
#define CACHE_ISR_POWERR_MASK                   (0x01U << CACHE_ISR_POWERR_SHIFT)
#define CACHE_ISR_POWERR(x)                     (((uint32_t)(((uint32_t)(x)) << CACHE_ISR_POWERR_SHIFT)) & CACHE_ISR_POWERR_MASK)

/*!
 * @brief CACHE_CSHR Register Bit Definition
 */

#define CACHE_CSHR_CSHR_SHIFT                   (0)
#define CACHE_CSHR_CSHR_MASK                    (0xFFFFFFFFU << CACHE_CSHR_CSHR_SHIFT)
#define CACHE_CSHR_CSHR(x)                      (((uint32_t)(((uint32_t)(x)) << CACHE_CSHR_CSHR_SHIFT)) & CACHE_CSHR_CSHR_MASK)

/*!
 * @brief CACHE_CSMR Register Bit Definition
 */

#define CACHE_CSMR_CSMR_SHIFT                   (0)
#define CACHE_CSMR_CSMR_MASK                    (0xFFFFFFFFU << CACHE_CSMR_CSMR_SHIFT)
#define CACHE_CSMR_CSMR(x)                      (((uint32_t)(((uint32_t)(x)) << CACHE_CSMR_CSMR_SHIFT)) & CACHE_CSMR_CSMR_MASK)

/*!
 * @}
 */ /* end of group CACHE_Register_Masks */
/******************************************************************************
 * CACHE Instance
******************************************************************************/
#define CACHE                               ((CACHE_Type*)CACHE_BASE)

/*!
 * @}
 */ /* end of group CACHE_Peripheral_Access_Layer */



/*!
 * @addtogroup PWR_Peripheral_Access_Layer PWR Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * PWR Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CR1;                                                            ///< Power control register 1                     offset: 0x00
    __IO uint32_t CSR;                                                            ///< Power control status register                offset: 0x04
    __IO uint32_t CR2;                                                            ///< Power control register 2                     offset: 0x08
    __IO uint32_t CR3;                                                            ///< Power Control Register 3                     offset: 0x0C
    __IO uint32_t CR4;                                                            ///< Power Control Register 4                     offset: 0x10
    __IO uint32_t CR5;                                                            ///< Power Control Register 5                     offset: 0x14
    __IO uint32_t CR6;                                                            ///< Power Control Register 6                     offset: 0x18
    __IO uint32_t SR;                                                             ///< Power status register                        offset: 0x1C
    __IO uint32_t SCR;                                                            ///< Power Configuration Register                 offset: 0x18
    __IO uint32_t Reserved2[3];                                                   ///< Reserved
    __IO uint32_t CFGR;                                                           ///< Power Configuration Register                 offset: 0x28
} PWR_Type;

/*******************************************************************************
 * PWR Type
 ******************************************************************************/

/*!
 * @addtogroup PWR_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief PWR_CR1 Register Bit Definition
 */

#define PWR_CR1_VOS_SHIFT                       (14)
#define PWR_CR1_VOS_MASK                        (0x3U << PWR_CR1_VOS_SHIFT)
#define PWR_CR1_VOS(x)                          (((uint32_t)(((uint32_t)(x)) << PWR_CR1_VOS_SHIFT)) & PWR_CR1_VOS_MASK)

#define PWR_CR1_LPR_SHIFT                       (13)
#define PWR_CR1_LPR_MASK                        (0x01U << PWR_CR1_LPR_SHIFT)
#define PWR_CR1_LPR(x)                          (((uint32_t)(((uint32_t)(x)) << PWR_CR1_LPR_SHIFT)) & PWR_CR1_LPR_MASK)

#define PWR_CR1_CSBF_SHIFT                      (3)
#define PWR_CR1_CSBF_MASK                       (0x01U << PWR_CR1_CSBF_SHIFT)
#define PWR_CR1_CSBF(x)                         (((uint32_t)(((uint32_t)(x)) << PWR_CR1_CSBF_SHIFT)) & PWR_CR1_CSBF_MASK)

#define PWR_CR1_PDDS_SHIFT                      (1)
#define PWR_CR1_PDDS_MASK                       (0x01U << PWR_CR1_PDDS_SHIFT)
#define PWR_CR1_PDDS(x)                         (((uint32_t)(((uint32_t)(x)) << PWR_CR1_PDDS_SHIFT)) & PWR_CR1_PDDS_MASK)

#define PWR_CR1_LPDS_SHIFT                      (0)
#define PWR_CR1_LPDS_MASK                       (0x01U << PWR_CR1_LPDS_SHIFT)
#define PWR_CR1_LPDS(x)                         (((uint32_t)(((uint32_t)(x)) << PWR_CR1_LPDS_SHIFT)) & PWR_CR1_LPDS_MASK)

/*!
 * @brief PWR_CSR Register Bit Definition
 */

#define PWR_CSR_VOSRDY_SHIFT                    (14)
#define PWR_CSR_VOSRDY_MASK                     (0x01U << PWR_CSR_VOSRDY_SHIFT)
#define PWR_CSR_VOSRDY(x)                       (((uint32_t)(((uint32_t)(x)) << PWR_CSR_VOSRDY_SHIFT)) & PWR_CSR_VOSRDY_MASK)

#define PWR_CSR_SBF_SHIFT                       (1)
#define PWR_CSR_SBF_MASK                        (0x01U << PWR_CSR_SBF_SHIFT)
#define PWR_CSR_SBF(x)                          (((uint32_t)(((uint32_t)(x)) << PWR_CSR_SBF_SHIFT)) & PWR_CSR_SBF_MASK)

/*!
 * @brief PWR_CR2 Register Bit Definition
 */

#define PWR_CR2_ENWU_SHIFT                      (15)
#define PWR_CR2_ENWU_MASK                       (0x01U << PWR_CR2_ENWU_SHIFT)
#define PWR_CR2_ENWU(x)                         (((uint32_t)(((uint32_t)(x)) << PWR_CR2_ENWU_SHIFT)) & PWR_CR2_ENWU_MASK)

#define PWR_CR2_EWUP_SHIFT                   (0)
#define PWR_CR2_EWUP_MASK                    (0x3FU << PWR_CR2_EWUP_SHIFT)
#define PWR_CR2_EWUP(x)                      (((uint32_t)(((uint32_t)(x)) << PWR_CR2_EWUP_SHIFT)) & PWR_CR2_EWUP_MASK)

/*!
 * @brief PWR_CR3 Register Bit Definition
 */

#define PWR_CR3_WP_SHIFT                     (0)
#define PWR_CR3_WP_MASK                      (0x3FU << PWR_CR3_WP_SHIFT)
#define PWR_CR3_WP(x)                        (((uint32_t)(((uint32_t)(x)) << PWR_CR3_WP_SHIFT)) & PWR_CR3_WP_MASK)

/*!
 * @brief PWR_CR4 Register Bit Definition
 */

#define PWR_CR4_FILTCNT0_SHIFT                  (8)
#define PWR_CR4_FILTCNT0_MASK                   (0xFFU << PWR_CR4_FILTCNT0_SHIFT)
#define PWR_CR4_FILTCNT0(x)                     (((uint32_t)(((uint32_t)(x)) << PWR_CR4_FILTCNT0_SHIFT)) & PWR_CR4_FILTCNT0_MASK)

#define PWR_CR4_FILTF0_SHIFT                    (4)
#define PWR_CR4_FILTF0_MASK                     (0x01U << PWR_CR4_FILTF0_SHIFT)
#define PWR_CR4_FILTF0(x)                       (((uint32_t)(((uint32_t)(x)) << PWR_CR4_FILTF0_SHIFT)) & PWR_CR4_FILTF0_MASK)

#define PWR_CR4_FILTE0_SHIFT                    (2)
#define PWR_CR4_FILTE0_MASK                     (0x3U << PWR_CR4_FILTE0_SHIFT)
#define PWR_CR4_FILTE0(x)                       (((uint32_t)(((uint32_t)(x)) << PWR_CR4_FILTE0_SHIFT)) & PWR_CR4_FILTE0_MASK)

#define PWR_CR4_FILTSEL0_SHIFT                  (0)
#define PWR_CR4_FILTSEL0_MASK                   (0x3U << PWR_CR4_FILTSEL0_SHIFT)
#define PWR_CR4_FILTSEL0(x)                     (((uint32_t)(((uint32_t)(x)) << PWR_CR4_FILTSEL0_SHIFT)) & PWR_CR4_FILTSEL0_MASK)

/*!
 * @brief PWR_CR5 Register Bit Definition
 */

#define PWR_CR5_FILTCNT1_SHIFT                  (8)
#define PWR_CR5_FILTCNT1_MASK                   (0xFFU << PWR_CR5_FILTCNT1_SHIFT)
#define PWR_CR5_FILTCNT1(x)                     (((uint32_t)(((uint32_t)(x)) << PWR_CR5_FILTCNT1_SHIFT)) & PWR_CR5_FILTCNT1_MASK)

#define PWR_CR5_FILTF1_SHIFT                    (4)
#define PWR_CR5_FILTF1_MASK                     (0x01U << PWR_CR5_FILTF1_SHIFT)
#define PWR_CR5_FILTF1(x)                       (((uint32_t)(((uint32_t)(x)) << PWR_CR5_FILTF1_SHIFT)) & PWR_CR5_FILTF1_MASK)

#define PWR_CR5_FILTE1_SHIFT                    (2)
#define PWR_CR5_FILTE1_MASK                     (0x3U << PWR_CR5_FILTE1_SHIFT)
#define PWR_CR5_FILTE1(x)                       (((uint32_t)(((uint32_t)(x)) << PWR_CR5_FILTE1_SHIFT)) & PWR_CR5_FILTE1_MASK)

#define PWR_CR5_FILTSEL1_SHIFT                  (0)
#define PWR_CR5_FILTSEL1_MASK                   (0x3U << PWR_CR5_FILTSEL1_SHIFT)
#define PWR_CR5_FILTSEL1(x)                     (((uint32_t)(((uint32_t)(x)) << PWR_CR5_FILTSEL1_SHIFT)) & PWR_CR5_FILTSEL1_MASK)

/*!
 * @brief PWR_CR6 Register Bit Definition
 */

#define PWR_CR6_STDBY_FS_WK_SHIFT               (0)
#define PWR_CR6_STDBY_FS_WK_MASK                (0x7U << PWR_CR6_STDBY_FS_WK_SHIFT)
#define PWR_CR6_STDBY_FS_WK(x)                  (((uint32_t)(((uint32_t)(x)) << PWR_CR6_STDBY_FS_WK_SHIFT)) & PWR_CR6_STDBY_FS_WK_MASK)

/*!
 * @brief PWR_SR Register Bit Definition
 */

#define PWR_SR_WUF_SHIFT                     (0)
#define PWR_SR_WUF_MASK                      (0x3FU << PWR_SR_WUF_SHIFT)
#define PWR_SR_WUF(x)                        (((uint32_t)(((uint32_t)(x)) << PWR_SR_WUF_SHIFT)) & PWR_SR_WUF_MASK)

/*!
 * @brief PWR_SCR Register Bit Definition
 */

#define PWR_SCR_CWUF_SHIFT                   (0)
#define PWR_SCR_CWUF_MASK                    (0x3FU << PWR_SCR_CWUF_SHIFT)
#define PWR_SCR_CWUF(x)                      (((uint32_t)(((uint32_t)(x)) << PWR_SCR_CWUF_SHIFT)) & PWR_SCR_CWUF_MASK)

/*!
 * @brief PWR_CFGR Register Bit Definition
 */

#define PWR_CFGR_LSICAL_SHIFT                   (5)
#define PWR_CFGR_LSICAL_MASK                    (0x1FU << PWR_CFGR_LSICAL_SHIFT)
#define PWR_CFGR_LSICAL(x)                      (((uint32_t)(((uint32_t)(x)) << PWR_CFGR_LSICAL_SHIFT)) & PWR_CFGR_LSICAL_MASK)

#define PWR_CFGR_LSICALSEL_SHIFT                (0)
#define PWR_CFGR_LSICALSEL_MASK                 (0x1FU << PWR_CFGR_LSICALSEL_SHIFT)
#define PWR_CFGR_LSICALSEL(x)                   (((uint32_t)(((uint32_t)(x)) << PWR_CFGR_LSICALSEL_SHIFT)) & PWR_CFGR_LSICALSEL_MASK)

/*!
 * @}
 */ /* end of group PWR_Register_Masks */
/******************************************************************************
 * PWR Instance
******************************************************************************/
#define PWR                             ((PWR_Type*)PWR_BASE)

/*!
 * @}
 */ /* end of group PWR_Peripheral_Access_Layer */



/*!
 * @addtogroup RCC_Peripheral_Access_Layer RCC Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * RCC Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CR;                                                             ///< Clock control register                       offset: 0x00
    __IO uint32_t CFGR;                                                           ///< Clock configuration register                 offset: 0x04
    __IO uint32_t CIR;                                                            ///< Clock interrupt register                     offset: 0x08
    __IO uint32_t AHB3RSTR;                                                       ///< AHB3 peripheral reset register               offset: 0x0C
    __IO uint32_t AHB2RSTR;                                                       ///< AHB2 peripheral reset register               offset: 0x10
    __IO uint32_t AHB1RSTR;                                                       ///< AHB1 peripheral reset register               offset: 0x14
    __IO uint32_t APB2RSTR;                                                       ///< APB2 peripheral reset register               offset: 0x18
    __IO uint32_t APB1RSTR;                                                       ///< APB1 peripheral reset register               offset: 0x1C
    __IO uint32_t AHB3ENR;                                                        ///< AHB3 peripheral clock enable register        offset: 0x20
    __IO uint32_t AHB2ENR;                                                        ///< AHB2 peripheral clock enable register        offset: 0x24
    __IO uint32_t AHB1ENR;                                                        ///< AHB1 peripheral clock enable register        offset: 0x28
    __IO uint32_t APB2ENR;                                                        ///< APB2 peripheral clock enable register        offset: 0x2C
    __IO uint32_t APB1ENR;                                                        ///< APB1 peripheral clock enable register        offset: 0x30
    __IO uint32_t BDCR;                                                           ///< Backup domain control register               offset: 0x34
    __IO uint32_t CSR;                                                            ///< Control status register                      offset: 0x38
    __IO uint32_t SYSCFG;                                                         ///< System Configuration Register                offset: 0x3C
    __IO uint32_t CFGR2;                                                          ///< Clock configuration register 2               offset: 0x40
    __IO uint32_t ICSCR;                                                          ///< Internal clock source calibration register   offset: 0x44
    __IO uint32_t PLLCFGR;                                                        ///< PLL configuration register                   offset: 0x48
    __IO uint32_t Reserved3[13];                                                  ///< Reserved
    __IO uint32_t HSIDLY;                                                         ///< HSI delay register                           offset: 0x80
    __IO uint32_t HSEDLY;                                                         ///< HSE delay register                           offset: 0x84
    __IO uint32_t PLLDLY;                                                         ///< PLL delay register                           offset: 0x88
} RCC_Type;

/*******************************************************************************
 * RCC Type
 ******************************************************************************/

/*!
 * @addtogroup RCC_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief RCC_CR Register Bit Definition
 */

#define RCC_CR_PLLRDY_SHIFT                     (25)
#define RCC_CR_PLLRDY_MASK                      (0x01U << RCC_CR_PLLRDY_SHIFT)
#define RCC_CR_PLLRDY(x)                        (((uint32_t)(((uint32_t)(x)) << RCC_CR_PLLRDY_SHIFT)) & RCC_CR_PLLRDY_MASK)

#define RCC_CR_PLLON_SHIFT                      (24)
#define RCC_CR_PLLON_MASK                       (0x01U << RCC_CR_PLLON_SHIFT)
#define RCC_CR_PLLON(x)                         (((uint32_t)(((uint32_t)(x)) << RCC_CR_PLLON_SHIFT)) & RCC_CR_PLLON_MASK)

#define RCC_CR_CSSON_SHIFT                      (19)
#define RCC_CR_CSSON_MASK                       (0x01U << RCC_CR_CSSON_SHIFT)
#define RCC_CR_CSSON(x)                         (((uint32_t)(((uint32_t)(x)) << RCC_CR_CSSON_SHIFT)) & RCC_CR_CSSON_MASK)

#define RCC_CR_HSEBYP_SHIFT                     (18)
#define RCC_CR_HSEBYP_MASK                      (0x01U << RCC_CR_HSEBYP_SHIFT)
#define RCC_CR_HSEBYP(x)                        (((uint32_t)(((uint32_t)(x)) << RCC_CR_HSEBYP_SHIFT)) & RCC_CR_HSEBYP_MASK)

#define RCC_CR_HSERDY_SHIFT                     (17)
#define RCC_CR_HSERDY_MASK                      (0x01U << RCC_CR_HSERDY_SHIFT)
#define RCC_CR_HSERDY(x)                        (((uint32_t)(((uint32_t)(x)) << RCC_CR_HSERDY_SHIFT)) & RCC_CR_HSERDY_MASK)

#define RCC_CR_HSEON_SHIFT                      (16)
#define RCC_CR_HSEON_MASK                       (0x01U << RCC_CR_HSEON_SHIFT)
#define RCC_CR_HSEON(x)                         (((uint32_t)(((uint32_t)(x)) << RCC_CR_HSEON_SHIFT)) & RCC_CR_HSEON_MASK)

#define RCC_CR_HSIDIV_SHIFT                     (11)
#define RCC_CR_HSIDIV_MASK                      (0x7U << RCC_CR_HSIDIV_SHIFT)
#define RCC_CR_HSIDIV(x)                        (((uint32_t)(((uint32_t)(x)) << RCC_CR_HSIDIV_SHIFT)) & RCC_CR_HSIDIV_MASK)

#define RCC_CR_HSIRDY_SHIFT                     (1)
#define RCC_CR_HSIRDY_MASK                      (0x01U << RCC_CR_HSIRDY_SHIFT)
#define RCC_CR_HSIRDY(x)                        (((uint32_t)(((uint32_t)(x)) << RCC_CR_HSIRDY_SHIFT)) & RCC_CR_HSIRDY_MASK)

#define RCC_CR_HSION_SHIFT                      (0)
#define RCC_CR_HSION_MASK                       (0x01U << RCC_CR_HSION_SHIFT)
#define RCC_CR_HSION(x)                         (((uint32_t)(((uint32_t)(x)) << RCC_CR_HSION_SHIFT)) & RCC_CR_HSION_MASK)

/*!
 * @brief RCC_CFGR Register Bit Definition
 */

#define RCC_CFGR_MCO_SHIFT                      (24)
#define RCC_CFGR_MCO_MASK                       (0x7U << RCC_CFGR_MCO_SHIFT)
#define RCC_CFGR_MCO(x)                         (((uint32_t)(((uint32_t)(x)) << RCC_CFGR_MCO_SHIFT)) & RCC_CFGR_MCO_MASK)

#define RCC_CFGR_USBPRE_SHIFT                   (22)
#define RCC_CFGR_USBPRE_MASK                    (0x3U << RCC_CFGR_USBPRE_SHIFT)
#define RCC_CFGR_USBPRE(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CFGR_USBPRE_SHIFT)) & RCC_CFGR_USBPRE_MASK)

#define RCC_CFGR_PPRE2_SHIFT                    (11)
#define RCC_CFGR_PPRE2_MASK                     (0x7U << RCC_CFGR_PPRE2_SHIFT)
#define RCC_CFGR_PPRE2(x)                       (((uint32_t)(((uint32_t)(x)) << RCC_CFGR_PPRE2_SHIFT)) & RCC_CFGR_PPRE2_MASK)

#define RCC_CFGR_PPRE1_SHIFT                    (8)
#define RCC_CFGR_PPRE1_MASK                     (0x7U << RCC_CFGR_PPRE1_SHIFT)
#define RCC_CFGR_PPRE1(x)                       (((uint32_t)(((uint32_t)(x)) << RCC_CFGR_PPRE1_SHIFT)) & RCC_CFGR_PPRE1_MASK)

#define RCC_CFGR_HPRE_SHIFT                     (4)
#define RCC_CFGR_HPRE_MASK                      (0xFU << RCC_CFGR_HPRE_SHIFT)
#define RCC_CFGR_HPRE(x)                        (((uint32_t)(((uint32_t)(x)) << RCC_CFGR_HPRE_SHIFT)) & RCC_CFGR_HPRE_MASK)

#define RCC_CFGR_SWS_SHIFT                      (2)
#define RCC_CFGR_SWS_MASK                       (0x3U << RCC_CFGR_SWS_SHIFT)
#define RCC_CFGR_SWS(x)                         (((uint32_t)(((uint32_t)(x)) << RCC_CFGR_SWS_SHIFT)) & RCC_CFGR_SWS_MASK)

#define RCC_CFGR_SW_SHIFT                       (0)
#define RCC_CFGR_SW_MASK                        (0x3U << RCC_CFGR_SW_SHIFT)
#define RCC_CFGR_SW(x)                          (((uint32_t)(((uint32_t)(x)) << RCC_CFGR_SW_SHIFT)) & RCC_CFGR_SW_MASK)

/*!
 * @brief RCC_CIR Register Bit Definition
 */

#define RCC_CIR_CSSC_SHIFT                      (23)
#define RCC_CIR_CSSC_MASK                       (0x01U << RCC_CIR_CSSC_SHIFT)
#define RCC_CIR_CSSC(x)                         (((uint32_t)(((uint32_t)(x)) << RCC_CIR_CSSC_SHIFT)) & RCC_CIR_CSSC_MASK)

#define RCC_CIR_PLLRDYC_SHIFT                   (20)
#define RCC_CIR_PLLRDYC_MASK                    (0x01U << RCC_CIR_PLLRDYC_SHIFT)
#define RCC_CIR_PLLRDYC(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CIR_PLLRDYC_SHIFT)) & RCC_CIR_PLLRDYC_MASK)

#define RCC_CIR_HSERDYC_SHIFT                   (19)
#define RCC_CIR_HSERDYC_MASK                    (0x01U << RCC_CIR_HSERDYC_SHIFT)
#define RCC_CIR_HSERDYC(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CIR_HSERDYC_SHIFT)) & RCC_CIR_HSERDYC_MASK)

#define RCC_CIR_HSIRDYC_SHIFT                   (18)
#define RCC_CIR_HSIRDYC_MASK                    (0x01U << RCC_CIR_HSIRDYC_SHIFT)
#define RCC_CIR_HSIRDYC(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CIR_HSIRDYC_SHIFT)) & RCC_CIR_HSIRDYC_MASK)

#define RCC_CIR_LSERDYC_SHIFT                   (17)
#define RCC_CIR_LSERDYC_MASK                    (0x01U << RCC_CIR_LSERDYC_SHIFT)
#define RCC_CIR_LSERDYC(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CIR_LSERDYC_SHIFT)) & RCC_CIR_LSERDYC_MASK)

#define RCC_CIR_LSIRDYC_SHIFT                   (16)
#define RCC_CIR_LSIRDYC_MASK                    (0x01U << RCC_CIR_LSIRDYC_SHIFT)
#define RCC_CIR_LSIRDYC(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CIR_LSIRDYC_SHIFT)) & RCC_CIR_LSIRDYC_MASK)

#define RCC_CIR_PLLRDYIE_SHIFT                  (12)
#define RCC_CIR_PLLRDYIE_MASK                   (0x01U << RCC_CIR_PLLRDYIE_SHIFT)
#define RCC_CIR_PLLRDYIE(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_CIR_PLLRDYIE_SHIFT)) & RCC_CIR_PLLRDYIE_MASK)

#define RCC_CIR_HSERDYIE_SHIFT                  (11)
#define RCC_CIR_HSERDYIE_MASK                   (0x01U << RCC_CIR_HSERDYIE_SHIFT)
#define RCC_CIR_HSERDYIE(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_CIR_HSERDYIE_SHIFT)) & RCC_CIR_HSERDYIE_MASK)

#define RCC_CIR_HSIRDYIE_SHIFT                  (10)
#define RCC_CIR_HSIRDYIE_MASK                   (0x01U << RCC_CIR_HSIRDYIE_SHIFT)
#define RCC_CIR_HSIRDYIE(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_CIR_HSIRDYIE_SHIFT)) & RCC_CIR_HSIRDYIE_MASK)

#define RCC_CIR_LSERDYIE_SHIFT                  (9)
#define RCC_CIR_LSERDYIE_MASK                   (0x01U << RCC_CIR_LSERDYIE_SHIFT)
#define RCC_CIR_LSERDYIE(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_CIR_LSERDYIE_SHIFT)) & RCC_CIR_LSERDYIE_MASK)

#define RCC_CIR_LSIRDYIE_SHIFT                  (8)
#define RCC_CIR_LSIRDYIE_MASK                   (0x01U << RCC_CIR_LSIRDYIE_SHIFT)
#define RCC_CIR_LSIRDYIE(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_CIR_LSIRDYIE_SHIFT)) & RCC_CIR_LSIRDYIE_MASK)

#define RCC_CIR_CSSF_SHIFT                      (7)
#define RCC_CIR_CSSF_MASK                       (0x01U << RCC_CIR_CSSF_SHIFT)
#define RCC_CIR_CSSF(x)                         (((uint32_t)(((uint32_t)(x)) << RCC_CIR_CSSF_SHIFT)) & RCC_CIR_CSSF_MASK)

#define RCC_CIR_PLLRDYF_SHIFT                   (4)
#define RCC_CIR_PLLRDYF_MASK                    (0x01U << RCC_CIR_PLLRDYF_SHIFT)
#define RCC_CIR_PLLRDYF(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CIR_PLLRDYF_SHIFT)) & RCC_CIR_PLLRDYF_MASK)

#define RCC_CIR_HSERDYF_SHIFT                   (3)
#define RCC_CIR_HSERDYF_MASK                    (0x01U << RCC_CIR_HSERDYF_SHIFT)
#define RCC_CIR_HSERDYF(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CIR_HSERDYF_SHIFT)) & RCC_CIR_HSERDYF_MASK)

#define RCC_CIR_HSIRDYF_SHIFT                   (2)
#define RCC_CIR_HSIRDYF_MASK                    (0x01U << RCC_CIR_HSIRDYF_SHIFT)
#define RCC_CIR_HSIRDYF(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CIR_HSIRDYF_SHIFT)) & RCC_CIR_HSIRDYF_MASK)

#define RCC_CIR_LSERDYF_SHIFT                   (1)
#define RCC_CIR_LSERDYF_MASK                    (0x01U << RCC_CIR_LSERDYF_SHIFT)
#define RCC_CIR_LSERDYF(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CIR_LSERDYF_SHIFT)) & RCC_CIR_LSERDYF_MASK)

#define RCC_CIR_LSIRDYF_SHIFT                   (0)
#define RCC_CIR_LSIRDYF_MASK                    (0x01U << RCC_CIR_LSIRDYF_SHIFT)
#define RCC_CIR_LSIRDYF(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CIR_LSIRDYF_SHIFT)) & RCC_CIR_LSIRDYF_MASK)

/*!
 * @brief RCC_AHB3RSTR Register Bit Definition
 */

#define RCC_AHB3RSTR_FSMC_SHIFT                 (0)
#define RCC_AHB3RSTR_FSMC_MASK                  (0x01U << RCC_AHB3RSTR_FSMC_SHIFT)
#define RCC_AHB3RSTR_FSMC(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_AHB3RSTR_FSMC_SHIFT)) & RCC_AHB3RSTR_FSMC_MASK)

/*!
 * @brief RCC_AHB2RSTR Register Bit Definition
 */

#define RCC_AHB2RSTR_USBOTGFS_SHIFT             (7)
#define RCC_AHB2RSTR_USBOTGFS_MASK              (0x01U << RCC_AHB2RSTR_USBOTGFS_SHIFT)
#define RCC_AHB2RSTR_USBOTGFS(x)                (((uint32_t)(((uint32_t)(x)) << RCC_AHB2RSTR_USBOTGFS_SHIFT)) & RCC_AHB2RSTR_USBOTGFS_MASK)

/*!
 * @brief RCC_AHB1RSTR Register Bit Definition
 */

#define RCC_AHB1RSTR_ETHMAC_SHIFT               (25)
#define RCC_AHB1RSTR_ETHMAC_MASK                (0x01U << RCC_AHB1RSTR_ETHMAC_SHIFT)
#define RCC_AHB1RSTR_ETHMAC(x)                  (((uint32_t)(((uint32_t)(x)) << RCC_AHB1RSTR_ETHMAC_SHIFT)) & RCC_AHB1RSTR_ETHMAC_MASK)

#define RCC_AHB1RSTR_DMA2_SHIFT                 (22)
#define RCC_AHB1RSTR_DMA2_MASK                  (0x01U << RCC_AHB1RSTR_DMA2_SHIFT)
#define RCC_AHB1RSTR_DMA2(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_AHB1RSTR_DMA2_SHIFT)) & RCC_AHB1RSTR_DMA2_MASK)

#define RCC_AHB1RSTR_DMA1_SHIFT                 (21)
#define RCC_AHB1RSTR_DMA1_MASK                  (0x01U << RCC_AHB1RSTR_DMA1_SHIFT)
#define RCC_AHB1RSTR_DMA1(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_AHB1RSTR_DMA1_SHIFT)) & RCC_AHB1RSTR_DMA1_MASK)

#define RCC_AHB1RSTR_CRC_SHIFT                  (12)
#define RCC_AHB1RSTR_CRC_MASK                   (0x01U << RCC_AHB1RSTR_CRC_SHIFT)
#define RCC_AHB1RSTR_CRC(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_AHB1RSTR_CRC_SHIFT)) & RCC_AHB1RSTR_CRC_MASK)

#define RCC_AHB1RSTR_SDIO_SHIFT                 (10)
#define RCC_AHB1RSTR_SDIO_MASK                  (0x01U << RCC_AHB1RSTR_SDIO_SHIFT)
#define RCC_AHB1RSTR_SDIO(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_AHB1RSTR_SDIO_SHIFT)) & RCC_AHB1RSTR_SDIO_MASK)

#define RCC_AHB1RSTR_GPIOH_SHIFT                (7)
#define RCC_AHB1RSTR_GPIOH_MASK                 (0x01U << RCC_AHB1RSTR_GPIOH_SHIFT)
#define RCC_AHB1RSTR_GPIOH(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_AHB1RSTR_GPIOH_SHIFT)) & RCC_AHB1RSTR_GPIOH_MASK)

#define RCC_AHB1RSTR_GPIOG_SHIFT                (6)
#define RCC_AHB1RSTR_GPIOG_MASK                 (0x01U << RCC_AHB1RSTR_GPIOG_SHIFT)
#define RCC_AHB1RSTR_GPIOG(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_AHB1RSTR_GPIOG_SHIFT)) & RCC_AHB1RSTR_GPIOG_MASK)

#define RCC_AHB1RSTR_GPIOF_SHIFT                (5)
#define RCC_AHB1RSTR_GPIOF_MASK                 (0x01U << RCC_AHB1RSTR_GPIOF_SHIFT)
#define RCC_AHB1RSTR_GPIOF(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_AHB1RSTR_GPIOF_SHIFT)) & RCC_AHB1RSTR_GPIOF_MASK)

#define RCC_AHB1RSTR_GPIOE_SHIFT                (4)
#define RCC_AHB1RSTR_GPIOE_MASK                 (0x01U << RCC_AHB1RSTR_GPIOE_SHIFT)
#define RCC_AHB1RSTR_GPIOE(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_AHB1RSTR_GPIOE_SHIFT)) & RCC_AHB1RSTR_GPIOE_MASK)

#define RCC_AHB1RSTR_GPIOD_SHIFT                (3)
#define RCC_AHB1RSTR_GPIOD_MASK                 (0x01U << RCC_AHB1RSTR_GPIOD_SHIFT)
#define RCC_AHB1RSTR_GPIOD(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_AHB1RSTR_GPIOD_SHIFT)) & RCC_AHB1RSTR_GPIOD_MASK)

#define RCC_AHB1RSTR_GPIOC_SHIFT                (2)
#define RCC_AHB1RSTR_GPIOC_MASK                 (0x01U << RCC_AHB1RSTR_GPIOC_SHIFT)
#define RCC_AHB1RSTR_GPIOC(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_AHB1RSTR_GPIOC_SHIFT)) & RCC_AHB1RSTR_GPIOC_MASK)

#define RCC_AHB1RSTR_GPIOB_SHIFT                (1)
#define RCC_AHB1RSTR_GPIOB_MASK                 (0x01U << RCC_AHB1RSTR_GPIOB_SHIFT)
#define RCC_AHB1RSTR_GPIOB(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_AHB1RSTR_GPIOB_SHIFT)) & RCC_AHB1RSTR_GPIOB_MASK)

#define RCC_AHB1RSTR_GPIOA_SHIFT                (0)
#define RCC_AHB1RSTR_GPIOA_MASK                 (0x01U << RCC_AHB1RSTR_GPIOA_SHIFT)
#define RCC_AHB1RSTR_GPIOA(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_AHB1RSTR_GPIOA_SHIFT)) & RCC_AHB1RSTR_GPIOA_MASK)

/*!
 * @brief RCC_APB2RSTR Register Bit Definition
 */

#define RCC_APB2RSTR_COMP_SHIFT                 (15)
#define RCC_APB2RSTR_COMP_MASK                  (0x01U << RCC_APB2RSTR_COMP_SHIFT)
#define RCC_APB2RSTR_COMP(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB2RSTR_COMP_SHIFT)) & RCC_APB2RSTR_COMP_MASK)

#define RCC_APB2RSTR_SYSCFG_SHIFT               (14)
#define RCC_APB2RSTR_SYSCFG_MASK                (0x01U << RCC_APB2RSTR_SYSCFG_SHIFT)
#define RCC_APB2RSTR_SYSCFG(x)                  (((uint32_t)(((uint32_t)(x)) << RCC_APB2RSTR_SYSCFG_SHIFT)) & RCC_APB2RSTR_SYSCFG_MASK)

#define RCC_APB2RSTR_SPI1_SHIFT                 (12)
#define RCC_APB2RSTR_SPI1_MASK                  (0x01U << RCC_APB2RSTR_SPI1_SHIFT)
#define RCC_APB2RSTR_SPI1(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB2RSTR_SPI1_SHIFT)) & RCC_APB2RSTR_SPI1_MASK)

#define RCC_APB2RSTR_ADC3_SHIFT                 (10)
#define RCC_APB2RSTR_ADC3_MASK                  (0x01U << RCC_APB2RSTR_ADC3_SHIFT)
#define RCC_APB2RSTR_ADC3(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB2RSTR_ADC3_SHIFT)) & RCC_APB2RSTR_ADC3_MASK)

#define RCC_APB2RSTR_ADC2_SHIFT                 (9)
#define RCC_APB2RSTR_ADC2_MASK                  (0x01U << RCC_APB2RSTR_ADC2_SHIFT)
#define RCC_APB2RSTR_ADC2(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB2RSTR_ADC2_SHIFT)) & RCC_APB2RSTR_ADC2_MASK)

#define RCC_APB2RSTR_ADC1_SHIFT                 (8)
#define RCC_APB2RSTR_ADC1_MASK                  (0x01U << RCC_APB2RSTR_ADC1_SHIFT)
#define RCC_APB2RSTR_ADC1(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB2RSTR_ADC1_SHIFT)) & RCC_APB2RSTR_ADC1_MASK)

#define RCC_APB2RSTR_UART6_SHIFT                (5)
#define RCC_APB2RSTR_UART6_MASK                 (0x01U << RCC_APB2RSTR_UART6_SHIFT)
#define RCC_APB2RSTR_UART6(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_APB2RSTR_UART6_SHIFT)) & RCC_APB2RSTR_UART6_MASK)

#define RCC_APB2RSTR_UART1_SHIFT                (4)
#define RCC_APB2RSTR_UART1_MASK                 (0x01U << RCC_APB2RSTR_UART1_SHIFT)
#define RCC_APB2RSTR_UART1(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_APB2RSTR_UART1_SHIFT)) & RCC_APB2RSTR_UART1_MASK)

#define RCC_APB2RSTR_TIM8_SHIFT                 (1)
#define RCC_APB2RSTR_TIM8_MASK                  (0x01U << RCC_APB2RSTR_TIM8_SHIFT)
#define RCC_APB2RSTR_TIM8(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB2RSTR_TIM8_SHIFT)) & RCC_APB2RSTR_TIM8_MASK)

#define RCC_APB2RSTR_TIM1_SHIFT                 (0)
#define RCC_APB2RSTR_TIM1_MASK                  (0x01U << RCC_APB2RSTR_TIM1_SHIFT)
#define RCC_APB2RSTR_TIM1(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB2RSTR_TIM1_SHIFT)) & RCC_APB2RSTR_TIM1_MASK)

/*!
 * @brief RCC_APB1RSTR Register Bit Definition
 */

#define RCC_APB1RSTR_UART8_SHIFT                (31)
#define RCC_APB1RSTR_UART8_MASK                 (0x01U << RCC_APB1RSTR_UART8_SHIFT)
#define RCC_APB1RSTR_UART8(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_UART8_SHIFT)) & RCC_APB1RSTR_UART8_MASK)

#define RCC_APB1RSTR_UART7_SHIFT                (30)
#define RCC_APB1RSTR_UART7_MASK                 (0x01U << RCC_APB1RSTR_UART7_SHIFT)
#define RCC_APB1RSTR_UART7(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_UART7_SHIFT)) & RCC_APB1RSTR_UART7_MASK)

#define RCC_APB1RSTR_DAC_SHIFT                  (29)
#define RCC_APB1RSTR_DAC_MASK                   (0x01U << RCC_APB1RSTR_DAC_SHIFT)
#define RCC_APB1RSTR_DAC(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_DAC_SHIFT)) & RCC_APB1RSTR_DAC_MASK)

#define RCC_APB1RSTR_PWR_SHIFT                  (28)
#define RCC_APB1RSTR_PWR_MASK                   (0x01U << RCC_APB1RSTR_PWR_SHIFT)
#define RCC_APB1RSTR_PWR(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_PWR_SHIFT)) & RCC_APB1RSTR_PWR_MASK)

#define RCC_APB1RSTR_BKP_SHIFT                  (27)
#define RCC_APB1RSTR_BKP_MASK                   (0x01U << RCC_APB1RSTR_BKP_SHIFT)
#define RCC_APB1RSTR_BKP(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_BKP_SHIFT)) & RCC_APB1RSTR_BKP_MASK)

#define RCC_APB1RSTR_CAN_SHIFT                  (25)
#define RCC_APB1RSTR_CAN_MASK                   (0x01U << RCC_APB1RSTR_CAN_SHIFT)
#define RCC_APB1RSTR_CAN(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_CAN_SHIFT)) & RCC_APB1RSTR_CAN_MASK)

#define RCC_APB1RSTR_CRS_SHIFT                  (24)
#define RCC_APB1RSTR_CRS_MASK                   (0x01U << RCC_APB1RSTR_CRS_SHIFT)
#define RCC_APB1RSTR_CRS(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_CRS_SHIFT)) & RCC_APB1RSTR_CRS_MASK)

#define RCC_APB1RSTR_I2C2_SHIFT                 (22)
#define RCC_APB1RSTR_I2C2_MASK                  (0x01U << RCC_APB1RSTR_I2C2_SHIFT)
#define RCC_APB1RSTR_I2C2(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_I2C2_SHIFT)) & RCC_APB1RSTR_I2C2_MASK)

#define RCC_APB1RSTR_I2C1_SHIFT                 (21)
#define RCC_APB1RSTR_I2C1_MASK                  (0x01U << RCC_APB1RSTR_I2C1_SHIFT)
#define RCC_APB1RSTR_I2C1(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_I2C1_SHIFT)) & RCC_APB1RSTR_I2C1_MASK)

#define RCC_APB1RSTR_UART5_SHIFT                (20)
#define RCC_APB1RSTR_UART5_MASK                 (0x01U << RCC_APB1RSTR_UART5_SHIFT)
#define RCC_APB1RSTR_UART5(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_UART5_SHIFT)) & RCC_APB1RSTR_UART5_MASK)

#define RCC_APB1RSTR_UART4_SHIFT                (19)
#define RCC_APB1RSTR_UART4_MASK                 (0x01U << RCC_APB1RSTR_UART4_SHIFT)
#define RCC_APB1RSTR_UART4(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_UART4_SHIFT)) & RCC_APB1RSTR_UART4_MASK)

#define RCC_APB1RSTR_UART3_SHIFT                (18)
#define RCC_APB1RSTR_UART3_MASK                 (0x01U << RCC_APB1RSTR_UART3_SHIFT)
#define RCC_APB1RSTR_UART3(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_UART3_SHIFT)) & RCC_APB1RSTR_UART3_MASK)

#define RCC_APB1RSTR_UART2_SHIFT                (17)
#define RCC_APB1RSTR_UART2_MASK                 (0x01U << RCC_APB1RSTR_UART2_SHIFT)
#define RCC_APB1RSTR_UART2(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_UART2_SHIFT)) & RCC_APB1RSTR_UART2_MASK)

#define RCC_APB1RSTR_SPI3_SHIFT                 (15)
#define RCC_APB1RSTR_SPI3_MASK                  (0x01U << RCC_APB1RSTR_SPI3_SHIFT)
#define RCC_APB1RSTR_SPI3(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_SPI3_SHIFT)) & RCC_APB1RSTR_SPI3_MASK)

#define RCC_APB1RSTR_SPI2_SHIFT                 (14)
#define RCC_APB1RSTR_SPI2_MASK                  (0x01U << RCC_APB1RSTR_SPI2_SHIFT)
#define RCC_APB1RSTR_SPI2(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_SPI2_SHIFT)) & RCC_APB1RSTR_SPI2_MASK)

#define RCC_APB1RSTR_WWDG_SHIFT                 (11)
#define RCC_APB1RSTR_WWDG_MASK                  (0x01U << RCC_APB1RSTR_WWDG_SHIFT)
#define RCC_APB1RSTR_WWDG(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_WWDG_SHIFT)) & RCC_APB1RSTR_WWDG_MASK)

#define RCC_APB1RSTR_TIM7_SHIFT                 (5)
#define RCC_APB1RSTR_TIM7_MASK                  (0x01U << RCC_APB1RSTR_TIM7_SHIFT)
#define RCC_APB1RSTR_TIM7(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_TIM7_SHIFT)) & RCC_APB1RSTR_TIM7_MASK)

#define RCC_APB1RSTR_TIM6_SHIFT                 (4)
#define RCC_APB1RSTR_TIM6_MASK                  (0x01U << RCC_APB1RSTR_TIM6_SHIFT)
#define RCC_APB1RSTR_TIM6(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_TIM6_SHIFT)) & RCC_APB1RSTR_TIM6_MASK)

#define RCC_APB1RSTR_TIM5_SHIFT                 (3)
#define RCC_APB1RSTR_TIM5_MASK                  (0x01U << RCC_APB1RSTR_TIM5_SHIFT)
#define RCC_APB1RSTR_TIM5(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_TIM5_SHIFT)) & RCC_APB1RSTR_TIM5_MASK)

#define RCC_APB1RSTR_TIM4_SHIFT                 (2)
#define RCC_APB1RSTR_TIM4_MASK                  (0x01U << RCC_APB1RSTR_TIM4_SHIFT)
#define RCC_APB1RSTR_TIM4(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_TIM4_SHIFT)) & RCC_APB1RSTR_TIM4_MASK)

#define RCC_APB1RSTR_TIM3_SHIFT                 (1)
#define RCC_APB1RSTR_TIM3_MASK                  (0x01U << RCC_APB1RSTR_TIM3_SHIFT)
#define RCC_APB1RSTR_TIM3(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_TIM3_SHIFT)) & RCC_APB1RSTR_TIM3_MASK)

#define RCC_APB1RSTR_TIM2_SHIFT                 (0)
#define RCC_APB1RSTR_TIM2_MASK                  (0x01U << RCC_APB1RSTR_TIM2_SHIFT)
#define RCC_APB1RSTR_TIM2(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1RSTR_TIM2_SHIFT)) & RCC_APB1RSTR_TIM2_MASK)

/*!
 * @brief RCC_AHB3ENR Register Bit Definition
 */

#define RCC_AHB3ENR_FSMC_SHIFT                  (0)
#define RCC_AHB3ENR_FSMC_MASK                   (0x01U << RCC_AHB3ENR_FSMC_SHIFT)
#define RCC_AHB3ENR_FSMC(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_AHB3ENR_FSMC_SHIFT)) & RCC_AHB3ENR_FSMC_MASK)

/*!
 * @brief RCC_AHB2ENR Register Bit Definition
 */

#define RCC_AHB2ENR_USBOTGFS_SHIFT              (7)
#define RCC_AHB2ENR_USBOTGFS_MASK               (0x01U << RCC_AHB2ENR_USBOTGFS_SHIFT)
#define RCC_AHB2ENR_USBOTGFS(x)                 (((uint32_t)(((uint32_t)(x)) << RCC_AHB2ENR_USBOTGFS_SHIFT)) & RCC_AHB2ENR_USBOTGFS_MASK)

/*!
 * @brief RCC_AHB1ENR Register Bit Definition
 */

#define RCC_AHB1ENR_ETHMAC_SHIFT                (25)
#define RCC_AHB1ENR_ETHMAC_MASK                 (0x01U << RCC_AHB1ENR_ETHMAC_SHIFT)
#define RCC_AHB1ENR_ETHMAC(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_ETHMAC_SHIFT)) & RCC_AHB1ENR_ETHMAC_MASK)

#define RCC_AHB1ENR_DMA2_SHIFT                  (22)
#define RCC_AHB1ENR_DMA2_MASK                   (0x01U << RCC_AHB1ENR_DMA2_SHIFT)
#define RCC_AHB1ENR_DMA2(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_DMA2_SHIFT)) & RCC_AHB1ENR_DMA2_MASK)

#define RCC_AHB1ENR_DMA1_SHIFT                  (21)
#define RCC_AHB1ENR_DMA1_MASK                   (0x01U << RCC_AHB1ENR_DMA1_SHIFT)
#define RCC_AHB1ENR_DMA1(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_DMA1_SHIFT)) & RCC_AHB1ENR_DMA1_MASK)

#define RCC_AHB1ENR_SRAM_SHIFT                  (14)
#define RCC_AHB1ENR_SRAM_MASK                   (0x01U << RCC_AHB1ENR_SRAM_SHIFT)
#define RCC_AHB1ENR_SRAM(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_SRAM_SHIFT)) & RCC_AHB1ENR_SRAM_MASK)

#define RCC_AHB1ENR_FLASH_SHIFT                 (13)
#define RCC_AHB1ENR_FLASH_MASK                  (0x01U << RCC_AHB1ENR_FLASH_SHIFT)
#define RCC_AHB1ENR_FLASH(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_FLASH_SHIFT)) & RCC_AHB1ENR_FLASH_MASK)

#define RCC_AHB1ENR_CRC_SHIFT                   (12)
#define RCC_AHB1ENR_CRC_MASK                    (0x01U << RCC_AHB1ENR_CRC_SHIFT)
#define RCC_AHB1ENR_CRC(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_CRC_SHIFT)) & RCC_AHB1ENR_CRC_MASK)

#define RCC_AHB1ENR_SDIO_SHIFT                  (10)
#define RCC_AHB1ENR_SDIO_MASK                   (0x01U << RCC_AHB1ENR_SDIO_SHIFT)
#define RCC_AHB1ENR_SDIO(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_SDIO_SHIFT)) & RCC_AHB1ENR_SDIO_MASK)

#define RCC_AHB1ENR_GPIOH_SHIFT                 (7)
#define RCC_AHB1ENR_GPIOH_MASK                  (0x01U << RCC_AHB1ENR_GPIOH_SHIFT)
#define RCC_AHB1ENR_GPIOH(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_GPIOH_SHIFT)) & RCC_AHB1ENR_GPIOH_MASK)

#define RCC_AHB1ENR_GPIOG_SHIFT                 (6)
#define RCC_AHB1ENR_GPIOG_MASK                  (0x01U << RCC_AHB1ENR_GPIOG_SHIFT)
#define RCC_AHB1ENR_GPIOG(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_GPIOG_SHIFT)) & RCC_AHB1ENR_GPIOG_MASK)

#define RCC_AHB1ENR_GPIOF_SHIFT                 (5)
#define RCC_AHB1ENR_GPIOF_MASK                  (0x01U << RCC_AHB1ENR_GPIOF_SHIFT)
#define RCC_AHB1ENR_GPIOF(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_GPIOF_SHIFT)) & RCC_AHB1ENR_GPIOF_MASK)

#define RCC_AHB1ENR_GPIOE_SHIFT                 (4)
#define RCC_AHB1ENR_GPIOE_MASK                  (0x01U << RCC_AHB1ENR_GPIOE_SHIFT)
#define RCC_AHB1ENR_GPIOE(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_GPIOE_SHIFT)) & RCC_AHB1ENR_GPIOE_MASK)

#define RCC_AHB1ENR_GPIOD_SHIFT                 (3)
#define RCC_AHB1ENR_GPIOD_MASK                  (0x01U << RCC_AHB1ENR_GPIOD_SHIFT)
#define RCC_AHB1ENR_GPIOD(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_GPIOD_SHIFT)) & RCC_AHB1ENR_GPIOD_MASK)

#define RCC_AHB1ENR_GPIOC_SHIFT                 (2)
#define RCC_AHB1ENR_GPIOC_MASK                  (0x01U << RCC_AHB1ENR_GPIOC_SHIFT)
#define RCC_AHB1ENR_GPIOC(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_GPIOC_SHIFT)) & RCC_AHB1ENR_GPIOC_MASK)

#define RCC_AHB1ENR_GPIOB_SHIFT                 (1)
#define RCC_AHB1ENR_GPIOB_MASK                  (0x01U << RCC_AHB1ENR_GPIOB_SHIFT)
#define RCC_AHB1ENR_GPIOB(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_GPIOB_SHIFT)) & RCC_AHB1ENR_GPIOB_MASK)

#define RCC_AHB1ENR_GPIOA_SHIFT                 (0)
#define RCC_AHB1ENR_GPIOA_MASK                  (0x01U << RCC_AHB1ENR_GPIOA_SHIFT)
#define RCC_AHB1ENR_GPIOA(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_AHB1ENR_GPIOA_SHIFT)) & RCC_AHB1ENR_GPIOA_MASK)

/*!
 * @brief RCC_APB2ENR Register Bit Definition
 */

#define RCC_APB2ENR_COMP_SHIFT                  (15)
#define RCC_APB2ENR_COMP_MASK                   (0x01U << RCC_APB2ENR_COMP_SHIFT)
#define RCC_APB2ENR_COMP(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB2ENR_COMP_SHIFT)) & RCC_APB2ENR_COMP_MASK)

#define RCC_APB2ENR_SYSCFG_SHIFT                (14)
#define RCC_APB2ENR_SYSCFG_MASK                 (0x01U << RCC_APB2ENR_SYSCFG_SHIFT)
#define RCC_APB2ENR_SYSCFG(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_APB2ENR_SYSCFG_SHIFT)) & RCC_APB2ENR_SYSCFG_MASK)

#define RCC_APB2ENR_SPI1_SHIFT                  (12)
#define RCC_APB2ENR_SPI1_MASK                   (0x01U << RCC_APB2ENR_SPI1_SHIFT)
#define RCC_APB2ENR_SPI1(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB2ENR_SPI1_SHIFT)) & RCC_APB2ENR_SPI1_MASK)

#define RCC_APB2ENR_ADC3_SHIFT                  (10)
#define RCC_APB2ENR_ADC3_MASK                   (0x01U << RCC_APB2ENR_ADC3_SHIFT)
#define RCC_APB2ENR_ADC3(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB2ENR_ADC3_SHIFT)) & RCC_APB2ENR_ADC3_MASK)

#define RCC_APB2ENR_ADC2_SHIFT                  (9)
#define RCC_APB2ENR_ADC2_MASK                   (0x01U << RCC_APB2ENR_ADC2_SHIFT)
#define RCC_APB2ENR_ADC2(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB2ENR_ADC2_SHIFT)) & RCC_APB2ENR_ADC2_MASK)

#define RCC_APB2ENR_ADC1_SHIFT                  (8)
#define RCC_APB2ENR_ADC1_MASK                   (0x01U << RCC_APB2ENR_ADC1_SHIFT)
#define RCC_APB2ENR_ADC1(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB2ENR_ADC1_SHIFT)) & RCC_APB2ENR_ADC1_MASK)

#define RCC_APB2ENR_UART6_SHIFT                 (5)
#define RCC_APB2ENR_UART6_MASK                  (0x01U << RCC_APB2ENR_UART6_SHIFT)
#define RCC_APB2ENR_UART6(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB2ENR_UART6_SHIFT)) & RCC_APB2ENR_UART6_MASK)

#define RCC_APB2ENR_UART1_SHIFT                 (4)
#define RCC_APB2ENR_UART1_MASK                  (0x01U << RCC_APB2ENR_UART1_SHIFT)
#define RCC_APB2ENR_UART1(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB2ENR_UART1_SHIFT)) & RCC_APB2ENR_UART1_MASK)

#define RCC_APB2ENR_TIM8_SHIFT                  (1)
#define RCC_APB2ENR_TIM8_MASK                   (0x01U << RCC_APB2ENR_TIM8_SHIFT)
#define RCC_APB2ENR_TIM8(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB2ENR_TIM8_SHIFT)) & RCC_APB2ENR_TIM8_MASK)

#define RCC_APB2ENR_TIM1_SHIFT                  (0)
#define RCC_APB2ENR_TIM1_MASK                   (0x01U << RCC_APB2ENR_TIM1_SHIFT)
#define RCC_APB2ENR_TIM1(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB2ENR_TIM1_SHIFT)) & RCC_APB2ENR_TIM1_MASK)

/*!
 * @brief RCC_APB1ENR Register Bit Definition
 */

#define RCC_APB1ENR_UART8_SHIFT                 (31)
#define RCC_APB1ENR_UART8_MASK                  (0x01U << RCC_APB1ENR_UART8_SHIFT)
#define RCC_APB1ENR_UART8(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_UART8_SHIFT)) & RCC_APB1ENR_UART8_MASK)

#define RCC_APB1ENR_UART7_SHIFT                 (30)
#define RCC_APB1ENR_UART7_MASK                  (0x01U << RCC_APB1ENR_UART7_SHIFT)
#define RCC_APB1ENR_UART7(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_UART7_SHIFT)) & RCC_APB1ENR_UART7_MASK)

#define RCC_APB1ENR_DAC_SHIFT                   (29)
#define RCC_APB1ENR_DAC_MASK                    (0x01U << RCC_APB1ENR_DAC_SHIFT)
#define RCC_APB1ENR_DAC(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_DAC_SHIFT)) & RCC_APB1ENR_DAC_MASK)

#define RCC_APB1ENR_PWR_SHIFT                   (28)
#define RCC_APB1ENR_PWR_MASK                    (0x01U << RCC_APB1ENR_PWR_SHIFT)
#define RCC_APB1ENR_PWR(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_PWR_SHIFT)) & RCC_APB1ENR_PWR_MASK)

#define RCC_APB1ENR_BKP_SHIFT                   (27)
#define RCC_APB1ENR_BKP_MASK                    (0x01U << RCC_APB1ENR_BKP_SHIFT)
#define RCC_APB1ENR_BKP(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_BKP_SHIFT)) & RCC_APB1ENR_BKP_MASK)

#define RCC_APB1ENR_CAN_SHIFT                   (25)
#define RCC_APB1ENR_CAN_MASK                    (0x01U << RCC_APB1ENR_CAN_SHIFT)
#define RCC_APB1ENR_CAN(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_CAN_SHIFT)) & RCC_APB1ENR_CAN_MASK)

#define RCC_APB1ENR_CRS_SHIFT                   (24)
#define RCC_APB1ENR_CRS_MASK                    (0x01U << RCC_APB1ENR_CRS_SHIFT)
#define RCC_APB1ENR_CRS(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_CRS_SHIFT)) & RCC_APB1ENR_CRS_MASK)

#define RCC_APB1ENR_I2C2_SHIFT                  (22)
#define RCC_APB1ENR_I2C2_MASK                   (0x01U << RCC_APB1ENR_I2C2_SHIFT)
#define RCC_APB1ENR_I2C2(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_I2C2_SHIFT)) & RCC_APB1ENR_I2C2_MASK)

#define RCC_APB1ENR_I2C1_SHIFT                  (21)
#define RCC_APB1ENR_I2C1_MASK                   (0x01U << RCC_APB1ENR_I2C1_SHIFT)
#define RCC_APB1ENR_I2C1(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_I2C1_SHIFT)) & RCC_APB1ENR_I2C1_MASK)

#define RCC_APB1ENR_UART5_SHIFT                 (20)
#define RCC_APB1ENR_UART5_MASK                  (0x01U << RCC_APB1ENR_UART5_SHIFT)
#define RCC_APB1ENR_UART5(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_UART5_SHIFT)) & RCC_APB1ENR_UART5_MASK)

#define RCC_APB1ENR_UART4_SHIFT                 (19)
#define RCC_APB1ENR_UART4_MASK                  (0x01U << RCC_APB1ENR_UART4_SHIFT)
#define RCC_APB1ENR_UART4(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_UART4_SHIFT)) & RCC_APB1ENR_UART4_MASK)

#define RCC_APB1ENR_UART3_SHIFT                 (18)
#define RCC_APB1ENR_UART3_MASK                  (0x01U << RCC_APB1ENR_UART3_SHIFT)
#define RCC_APB1ENR_UART3(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_UART3_SHIFT)) & RCC_APB1ENR_UART3_MASK)

#define RCC_APB1ENR_UART2_SHIFT                 (17)
#define RCC_APB1ENR_UART2_MASK                  (0x01U << RCC_APB1ENR_UART2_SHIFT)
#define RCC_APB1ENR_UART2(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_UART2_SHIFT)) & RCC_APB1ENR_UART2_MASK)

#define RCC_APB1ENR_SPI3_SHIFT                  (15)
#define RCC_APB1ENR_SPI3_MASK                   (0x01U << RCC_APB1ENR_SPI3_SHIFT)
#define RCC_APB1ENR_SPI3(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_SPI3_SHIFT)) & RCC_APB1ENR_SPI3_MASK)

#define RCC_APB1ENR_SPI2_SHIFT                  (14)
#define RCC_APB1ENR_SPI2_MASK                   (0x01U << RCC_APB1ENR_SPI2_SHIFT)
#define RCC_APB1ENR_SPI2(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_SPI2_SHIFT)) & RCC_APB1ENR_SPI2_MASK)

#define RCC_APB1ENR_WWDG_SHIFT                  (11)
#define RCC_APB1ENR_WWDG_MASK                   (0x01U << RCC_APB1ENR_WWDG_SHIFT)
#define RCC_APB1ENR_WWDG(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_WWDG_SHIFT)) & RCC_APB1ENR_WWDG_MASK)

#define RCC_APB1ENR_TIM7_SHIFT                  (5)
#define RCC_APB1ENR_TIM7_MASK                   (0x01U << RCC_APB1ENR_TIM7_SHIFT)
#define RCC_APB1ENR_TIM7(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_TIM7_SHIFT)) & RCC_APB1ENR_TIM7_MASK)

#define RCC_APB1ENR_TIM6_SHIFT                  (4)
#define RCC_APB1ENR_TIM6_MASK                   (0x01U << RCC_APB1ENR_TIM6_SHIFT)
#define RCC_APB1ENR_TIM6(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_TIM6_SHIFT)) & RCC_APB1ENR_TIM6_MASK)

#define RCC_APB1ENR_TIM5_SHIFT                  (3)
#define RCC_APB1ENR_TIM5_MASK                   (0x01U << RCC_APB1ENR_TIM5_SHIFT)
#define RCC_APB1ENR_TIM5(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_TIM5_SHIFT)) & RCC_APB1ENR_TIM5_MASK)

#define RCC_APB1ENR_TIM4_SHIFT                  (2)
#define RCC_APB1ENR_TIM4_MASK                   (0x01U << RCC_APB1ENR_TIM4_SHIFT)
#define RCC_APB1ENR_TIM4(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_TIM4_SHIFT)) & RCC_APB1ENR_TIM4_MASK)

#define RCC_APB1ENR_TIM3_SHIFT                  (1)
#define RCC_APB1ENR_TIM3_MASK                   (0x01U << RCC_APB1ENR_TIM3_SHIFT)
#define RCC_APB1ENR_TIM3(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_TIM3_SHIFT)) & RCC_APB1ENR_TIM3_MASK)

#define RCC_APB1ENR_TIM2_SHIFT                  (0)
#define RCC_APB1ENR_TIM2_MASK                   (0x01U << RCC_APB1ENR_TIM2_SHIFT)
#define RCC_APB1ENR_TIM2(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_APB1ENR_TIM2_SHIFT)) & RCC_APB1ENR_TIM2_MASK)

/*!
 * @brief RCC_BDCR Register Bit Definition
 */

#define RCC_BDCR_DBP_SHIFT                      (24)
#define RCC_BDCR_DBP_MASK                       (0x01U << RCC_BDCR_DBP_SHIFT)
#define RCC_BDCR_DBP(x)                         (((uint32_t)(((uint32_t)(x)) << RCC_BDCR_DBP_SHIFT)) & RCC_BDCR_DBP_MASK)

#define RCC_BDCR_BDRST_SHIFT                    (16)
#define RCC_BDCR_BDRST_MASK                     (0x01U << RCC_BDCR_BDRST_SHIFT)
#define RCC_BDCR_BDRST(x)                       (((uint32_t)(((uint32_t)(x)) << RCC_BDCR_BDRST_SHIFT)) & RCC_BDCR_BDRST_MASK)

#define RCC_BDCR_RTCEN_SHIFT                    (15)
#define RCC_BDCR_RTCEN_MASK                     (0x01U << RCC_BDCR_RTCEN_SHIFT)
#define RCC_BDCR_RTCEN(x)                       (((uint32_t)(((uint32_t)(x)) << RCC_BDCR_RTCEN_SHIFT)) & RCC_BDCR_RTCEN_MASK)

#define RCC_BDCR_RTCSEL_SHIFT                   (8)
#define RCC_BDCR_RTCSEL_MASK                    (0x3U << RCC_BDCR_RTCSEL_SHIFT)
#define RCC_BDCR_RTCSEL(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_BDCR_RTCSEL_SHIFT)) & RCC_BDCR_RTCSEL_MASK)

#define RCC_BDCR_LSEBYP_SHIFT                   (2)
#define RCC_BDCR_LSEBYP_MASK                    (0x01U << RCC_BDCR_LSEBYP_SHIFT)
#define RCC_BDCR_LSEBYP(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_BDCR_LSEBYP_SHIFT)) & RCC_BDCR_LSEBYP_MASK)

#define RCC_BDCR_LSERDY_SHIFT                   (1)
#define RCC_BDCR_LSERDY_MASK                    (0x01U << RCC_BDCR_LSERDY_SHIFT)
#define RCC_BDCR_LSERDY(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_BDCR_LSERDY_SHIFT)) & RCC_BDCR_LSERDY_MASK)

#define RCC_BDCR_LSEON_SHIFT                    (0)
#define RCC_BDCR_LSEON_MASK                     (0x01U << RCC_BDCR_LSEON_SHIFT)
#define RCC_BDCR_LSEON(x)                       (((uint32_t)(((uint32_t)(x)) << RCC_BDCR_LSEON_SHIFT)) & RCC_BDCR_LSEON_MASK)

/*!
 * @brief RCC_CSR Register Bit Definition
 */

#define RCC_CSR_LPWRRSTF_SHIFT                  (31)
#define RCC_CSR_LPWRRSTF_MASK                   (0x01U << RCC_CSR_LPWRRSTF_SHIFT)
#define RCC_CSR_LPWRRSTF(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_CSR_LPWRRSTF_SHIFT)) & RCC_CSR_LPWRRSTF_MASK)

#define RCC_CSR_WWDGRSTF_SHIFT                  (30)
#define RCC_CSR_WWDGRSTF_MASK                   (0x01U << RCC_CSR_WWDGRSTF_SHIFT)
#define RCC_CSR_WWDGRSTF(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_CSR_WWDGRSTF_SHIFT)) & RCC_CSR_WWDGRSTF_MASK)

#define RCC_CSR_IWDGRSTF_SHIFT                  (29)
#define RCC_CSR_IWDGRSTF_MASK                   (0x01U << RCC_CSR_IWDGRSTF_SHIFT)
#define RCC_CSR_IWDGRSTF(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_CSR_IWDGRSTF_SHIFT)) & RCC_CSR_IWDGRSTF_MASK)

#define RCC_CSR_SFTRSTF_SHIFT                   (28)
#define RCC_CSR_SFTRSTF_MASK                    (0x01U << RCC_CSR_SFTRSTF_SHIFT)
#define RCC_CSR_SFTRSTF(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CSR_SFTRSTF_SHIFT)) & RCC_CSR_SFTRSTF_MASK)

#define RCC_CSR_PORRSTF_SHIFT                   (27)
#define RCC_CSR_PORRSTF_MASK                    (0x01U << RCC_CSR_PORRSTF_SHIFT)
#define RCC_CSR_PORRSTF(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CSR_PORRSTF_SHIFT)) & RCC_CSR_PORRSTF_MASK)

#define RCC_CSR_PINRSTF_SHIFT                   (26)
#define RCC_CSR_PINRSTF_MASK                    (0x01U << RCC_CSR_PINRSTF_SHIFT)
#define RCC_CSR_PINRSTF(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CSR_PINRSTF_SHIFT)) & RCC_CSR_PINRSTF_MASK)

#define RCC_CSR_RMVF_SHIFT                      (24)
#define RCC_CSR_RMVF_MASK                       (0x01U << RCC_CSR_RMVF_SHIFT)
#define RCC_CSR_RMVF(x)                         (((uint32_t)(((uint32_t)(x)) << RCC_CSR_RMVF_SHIFT)) & RCC_CSR_RMVF_MASK)

#define RCC_CSR_LOCKUPF_SHIFT                   (23)
#define RCC_CSR_LOCKUPF_MASK                    (0x01U << RCC_CSR_LOCKUPF_SHIFT)
#define RCC_CSR_LOCKUPF(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CSR_LOCKUPF_SHIFT)) & RCC_CSR_LOCKUPF_MASK)

#define RCC_CSR_PVDRSTF_SHIFT                   (22)
#define RCC_CSR_PVDRSTF_MASK                    (0x01U << RCC_CSR_PVDRSTF_SHIFT)
#define RCC_CSR_PVDRSTF(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CSR_PVDRSTF_SHIFT)) & RCC_CSR_PVDRSTF_MASK)

#define RCC_CSR_VDTRSTF_SHIFT                   (21)
#define RCC_CSR_VDTRSTF_MASK                    (0x01U << RCC_CSR_VDTRSTF_SHIFT)
#define RCC_CSR_VDTRSTF(x)                      (((uint32_t)(((uint32_t)(x)) << RCC_CSR_VDTRSTF_SHIFT)) & RCC_CSR_VDTRSTF_MASK)

#define RCC_CSR_VDTRSTNEN_SHIFT                 (8)
#define RCC_CSR_VDTRSTNEN_MASK                  (0x01U << RCC_CSR_VDTRSTNEN_SHIFT)
#define RCC_CSR_VDTRSTNEN(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_CSR_VDTRSTNEN_SHIFT)) & RCC_CSR_VDTRSTNEN_MASK)

#define RCC_CSR_LOCKUPEN_SHIFT                  (7)
#define RCC_CSR_LOCKUPEN_MASK                   (0x01U << RCC_CSR_LOCKUPEN_SHIFT)
#define RCC_CSR_LOCKUPEN(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_CSR_LOCKUPEN_SHIFT)) & RCC_CSR_LOCKUPEN_MASK)

#define RCC_CSR_PVDRSTEN_SHIFT                  (6)
#define RCC_CSR_PVDRSTEN_MASK                   (0x01U << RCC_CSR_PVDRSTEN_SHIFT)
#define RCC_CSR_PVDRSTEN(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_CSR_PVDRSTEN_SHIFT)) & RCC_CSR_PVDRSTEN_MASK)

#define RCC_CSR_LSIOENLV_SHIFT                  (5)
#define RCC_CSR_LSIOENLV_MASK                   (0x01U << RCC_CSR_LSIOENLV_SHIFT)
#define RCC_CSR_LSIOENLV(x)                     (((uint32_t)(((uint32_t)(x)) << RCC_CSR_LSIOENLV_SHIFT)) & RCC_CSR_LSIOENLV_MASK)

#define RCC_CSR_LSIRDY_SHIFT                    (1)
#define RCC_CSR_LSIRDY_MASK                     (0x01U << RCC_CSR_LSIRDY_SHIFT)
#define RCC_CSR_LSIRDY(x)                       (((uint32_t)(((uint32_t)(x)) << RCC_CSR_LSIRDY_SHIFT)) & RCC_CSR_LSIRDY_MASK)

#define RCC_CSR_LSION_SHIFT                     (0)
#define RCC_CSR_LSION_MASK                      (0x01U << RCC_CSR_LSION_SHIFT)
#define RCC_CSR_LSION(x)                        (((uint32_t)(((uint32_t)(x)) << RCC_CSR_LSION_SHIFT)) & RCC_CSR_LSION_MASK)

/*!
 * @brief RCC_SYSCFG Register Bit Definition
 */

#define RCC_SYSCFG_OSCLPFEN_SHIFT               (14)
#define RCC_SYSCFG_OSCLPFEN_MASK                (0x01U << RCC_SYSCFG_OSCLPFEN_SHIFT)
#define RCC_SYSCFG_OSCLPFEN(x)                  (((uint32_t)(((uint32_t)(x)) << RCC_SYSCFG_OSCLPFEN_SHIFT)) & RCC_SYSCFG_OSCLPFEN_MASK)

#define RCC_SYSCFG_PADOSCTRIM_SHIFT             (8)
#define RCC_SYSCFG_PADOSCTRIM_MASK              (0x1FU << RCC_SYSCFG_PADOSCTRIM_SHIFT)
#define RCC_SYSCFG_PADOSCTRIM(x)                (((uint32_t)(((uint32_t)(x)) << RCC_SYSCFG_PADOSCTRIM_SHIFT)) & RCC_SYSCFG_PADOSCTRIM_MASK)

#define RCC_SYSCFG_DATAPREFETCH_SHIFT           (2)
#define RCC_SYSCFG_DATAPREFETCH_MASK            (0x01U << RCC_SYSCFG_DATAPREFETCH_SHIFT)
#define RCC_SYSCFG_DATAPREFETCH(x)              (((uint32_t)(((uint32_t)(x)) << RCC_SYSCFG_DATAPREFETCH_SHIFT)) & RCC_SYSCFG_DATAPREFETCH_MASK)

#define RCC_SYSCFG_SECTOR1KCFG_SHIFT            (1)
#define RCC_SYSCFG_SECTOR1KCFG_MASK             (0x01U << RCC_SYSCFG_SECTOR1KCFG_SHIFT)
#define RCC_SYSCFG_SECTOR1KCFG(x)               (((uint32_t)(((uint32_t)(x)) << RCC_SYSCFG_SECTOR1KCFG_SHIFT)) & RCC_SYSCFG_SECTOR1KCFG_MASK)

#define RCC_SYSCFG_PROGCHECKEN_SHIFT            (0)
#define RCC_SYSCFG_PROGCHECKEN_MASK             (0x01U << RCC_SYSCFG_PROGCHECKEN_SHIFT)
#define RCC_SYSCFG_PROGCHECKEN(x)               (((uint32_t)(((uint32_t)(x)) << RCC_SYSCFG_PROGCHECKEN_SHIFT)) & RCC_SYSCFG_PROGCHECKEN_MASK)

/*!
 * @brief RCC_CFGR2 Register Bit Definition
 */

#define RCC_CFGR2_APB1CLKHVPRE_SHIFT            (16)
#define RCC_CFGR2_APB1CLKHVPRE_MASK             (0xFU << RCC_CFGR2_APB1CLKHVPRE_SHIFT)
#define RCC_CFGR2_APB1CLKHVPRE(x)               (((uint32_t)(((uint32_t)(x)) << RCC_CFGR2_APB1CLKHVPRE_SHIFT)) & RCC_CFGR2_APB1CLKHVPRE_MASK)

#define RCC_CFGR2_FSMCPRE_SHIFT                 (8)
#define RCC_CFGR2_FSMCPRE_MASK                  (0x1FU << RCC_CFGR2_FSMCPRE_SHIFT)
#define RCC_CFGR2_FSMCPRE(x)                    (((uint32_t)(((uint32_t)(x)) << RCC_CFGR2_FSMCPRE_SHIFT)) & RCC_CFGR2_FSMCPRE_MASK)

#define RCC_CFGR2_TIMADVPRE_SHIFT               (1)
#define RCC_CFGR2_TIMADVPRE_MASK                (0x7U << RCC_CFGR2_TIMADVPRE_SHIFT)
#define RCC_CFGR2_TIMADVPRE(x)                  (((uint32_t)(((uint32_t)(x)) << RCC_CFGR2_TIMADVPRE_SHIFT)) & RCC_CFGR2_TIMADVPRE_MASK)

#define RCC_CFGR2_TIMADVCKSEL_SHIFT             (0)
#define RCC_CFGR2_TIMADVCKSEL_MASK              (0x01U << RCC_CFGR2_TIMADVCKSEL_SHIFT)
#define RCC_CFGR2_TIMADVCKSEL(x)                (((uint32_t)(((uint32_t)(x)) << RCC_CFGR2_TIMADVCKSEL_SHIFT)) & RCC_CFGR2_TIMADVCKSEL_MASK)

/*!
 * @brief RCC_ICSCR Register Bit Definition
 */

#define RCC_ICSCR_HSICALSFT_SHIFT               (16)
#define RCC_ICSCR_HSICALSFT_MASK                (0x3FFU << RCC_ICSCR_HSICALSFT_SHIFT)
#define RCC_ICSCR_HSICALSFT(x)                  (((uint32_t)(((uint32_t)(x)) << RCC_ICSCR_HSICALSFT_SHIFT)) & RCC_ICSCR_HSICALSFT_MASK)

#define RCC_ICSCR_HSICALSEL_SHIFT               (11)
#define RCC_ICSCR_HSICALSEL_MASK                (0x1FU << RCC_ICSCR_HSICALSEL_SHIFT)
#define RCC_ICSCR_HSICALSEL(x)                  (((uint32_t)(((uint32_t)(x)) << RCC_ICSCR_HSICALSEL_SHIFT)) & RCC_ICSCR_HSICALSEL_MASK)

#define RCC_ICSCR_TRIMCRSSEL_SHIFT              (0)
#define RCC_ICSCR_TRIMCRSSEL_MASK               (0x01U << RCC_ICSCR_TRIMCRSSEL_SHIFT)
#define RCC_ICSCR_TRIMCRSSEL(x)                 (((uint32_t)(((uint32_t)(x)) << RCC_ICSCR_TRIMCRSSEL_SHIFT)) & RCC_ICSCR_TRIMCRSSEL_MASK)

/*!
 * @brief RCC_PLLCFGR Register Bit Definition
 */

#define RCC_PLLCFGR_PLLMUL_SHIFT                (16)
#define RCC_PLLCFGR_PLLMUL_MASK                 (0x7FU << RCC_PLLCFGR_PLLMUL_SHIFT)
#define RCC_PLLCFGR_PLLMUL(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_PLLCFGR_PLLMUL_SHIFT)) & RCC_PLLCFGR_PLLMUL_MASK)

#define RCC_PLLCFGR_PLLDIV_SHIFT                (8)
#define RCC_PLLCFGR_PLLDIV_MASK                 (0x7U << RCC_PLLCFGR_PLLDIV_SHIFT)
#define RCC_PLLCFGR_PLLDIV(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_PLLCFGR_PLLDIV_SHIFT)) & RCC_PLLCFGR_PLLDIV_MASK)

#define RCC_PLLCFGR_PLLLDS_SHIFT                (4)
#define RCC_PLLCFGR_PLLLDS_MASK                 (0x3U << RCC_PLLCFGR_PLLLDS_SHIFT)
#define RCC_PLLCFGR_PLLLDS(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_PLLCFGR_PLLLDS_SHIFT)) & RCC_PLLCFGR_PLLLDS_MASK)

#define RCC_PLLCFGR_PLLICTRL_SHIFT              (2)
#define RCC_PLLCFGR_PLLICTRL_MASK               (0x3U << RCC_PLLCFGR_PLLICTRL_SHIFT)
#define RCC_PLLCFGR_PLLICTRL(x)                 (((uint32_t)(((uint32_t)(x)) << RCC_PLLCFGR_PLLICTRL_SHIFT)) & RCC_PLLCFGR_PLLICTRL_MASK)

#define RCC_PLLCFGR_PLLXTPRE_SHIFT              (1)
#define RCC_PLLCFGR_PLLXTPRE_MASK               (0x01U << RCC_PLLCFGR_PLLXTPRE_SHIFT)
#define RCC_PLLCFGR_PLLXTPRE(x)                 (((uint32_t)(((uint32_t)(x)) << RCC_PLLCFGR_PLLXTPRE_SHIFT)) & RCC_PLLCFGR_PLLXTPRE_MASK)

#define RCC_PLLCFGR_PLLSRC_SHIFT                (0)
#define RCC_PLLCFGR_PLLSRC_MASK                 (0x01U << RCC_PLLCFGR_PLLSRC_SHIFT)
#define RCC_PLLCFGR_PLLSRC(x)                   (((uint32_t)(((uint32_t)(x)) << RCC_PLLCFGR_PLLSRC_SHIFT)) & RCC_PLLCFGR_PLLSRC_MASK)

/*!
 * @brief RCC_HSIDLY Register Bit Definition
 */

#define RCC_HSIDLY_HSIEQUCNT_SHIFT              (0)
#define RCC_HSIDLY_HSIEQUCNT_MASK               (0xFFU << RCC_HSIDLY_HSIEQUCNT_SHIFT)
#define RCC_HSIDLY_HSIEQUCNT(x)                 (((uint32_t)(((uint32_t)(x)) << RCC_HSIDLY_HSIEQUCNT_SHIFT)) & RCC_HSIDLY_HSIEQUCNT_MASK)

/*!
 * @brief RCC_HSEDLY Register Bit Definition
 */

#define RCC_HSEDLY_HSEEQUCNT_SHIFT              (0)
#define RCC_HSEDLY_HSEEQUCNT_MASK               (0xFFFFU << RCC_HSEDLY_HSEEQUCNT_SHIFT)
#define RCC_HSEDLY_HSEEQUCNT(x)                 (((uint32_t)(((uint32_t)(x)) << RCC_HSEDLY_HSEEQUCNT_SHIFT)) & RCC_HSEDLY_HSEEQUCNT_MASK)

/*!
 * @brief RCC_PLLDLY Register Bit Definition
 */

#define RCC_PLLDLY_PLLEQUCNT_SHIFT              (0)
#define RCC_PLLDLY_PLLEQUCNT_MASK               (0x3FFU << RCC_PLLDLY_PLLEQUCNT_SHIFT)
#define RCC_PLLDLY_PLLEQUCNT(x)                 (((uint32_t)(((uint32_t)(x)) << RCC_PLLDLY_PLLEQUCNT_SHIFT)) & RCC_PLLDLY_PLLEQUCNT_MASK)

/*!
 * @}
 */ /* end of group RCC_Register_Masks */
/******************************************************************************
 * RCC Instance
******************************************************************************/
#define RCC                             ((RCC_Type*)RCC_BASE)

/*!
 * @}
 */ /* end of group RCC_Peripheral_Access_Layer */



/*!
 * @addtogroup SYSCFG_Peripheral_Access_Layer SYSCFG Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * SYSCFG Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CFGR;                                                           ///< SYSCFG configuration register                offset: 0x00
    __IO uint32_t Reserved4[1];                                                   ///< Reserved
    __IO uint32_t EXTICR1;                                                        ///< External interrupt configuration register 1  offset: 0x08
    __IO uint32_t EXTICR2;                                                        ///< External interrupt configuration register 2  offset: 0x0C
    __IO uint32_t EXTICR3;                                                        ///< External interrupt configuration register 3  offset: 0x10
    __IO uint32_t EXTICR4;                                                        ///< External interrupt configuration register 4  offset: 0x14
    __IO uint32_t CFGR2;                                                          ///< SYSCFG configuration register 2              offset: 0x18
    __IO uint32_t PDETCSR;                                                        ///< Power detection configuration status registeroffset: 0x1C
    __IO uint32_t VOSDLY;                                                         ///< VOSDLY configuration register                offset: 0x20
} SYSCFG_Type;

/*******************************************************************************
 * SYSCFG Type
 ******************************************************************************/

/*!
 * @addtogroup SYSCFG_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief SYSCFG_CFGR Register Bit Definition
 */

#define SYSCFG_CFGR_MODESEL_SHIFT               (29)
#define SYSCFG_CFGR_MODESEL_MASK                (0x3U << SYSCFG_CFGR_MODESEL_SHIFT)
#define SYSCFG_CFGR_MODESEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCFG_CFGR_MODESEL_SHIFT)) & SYSCFG_CFGR_MODESEL_MASK)

#define SYSCFG_CFGR_FCODATAEN_SHIFT             (28)
#define SYSCFG_CFGR_FCODATAEN_MASK              (0x01U << SYSCFG_CFGR_FCODATAEN_SHIFT)
#define SYSCFG_CFGR_FCODATAEN(x)                (((uint32_t)(((uint32_t)(x)) << SYSCFG_CFGR_FCODATAEN_SHIFT)) & SYSCFG_CFGR_FCODATAEN_MASK)

#define SYSCFG_CFGR_MEMMODE_SHIFT               (0)
#define SYSCFG_CFGR_MEMMODE_MASK                (0x3U << SYSCFG_CFGR_MEMMODE_SHIFT)
#define SYSCFG_CFGR_MEMMODE(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCFG_CFGR_MEMMODE_SHIFT)) & SYSCFG_CFGR_MEMMODE_MASK)

/*!
 * @brief SYSCFG_EXTICR1 Register Bit Definition
 */

#define SYSCFG_EXTICR1_EXTIX_SHIFT              (0)
#define SYSCFG_EXTICR1_EXTIX_MASK               (0xFFFFU << SYSCFG_EXTICR1_EXTIX_SHIFT)
#define SYSCFG_EXTICR1_EXTIX(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCFG_EXTICR1_EXTIX_SHIFT)) & SYSCFG_EXTICR1_EXTIX_MASK)

/*!
 * @brief SYSCFG_EXTICR2 Register Bit Definition
 */

#define SYSCFG_EXTICR2_EXTIX_SHIFT              (0)
#define SYSCFG_EXTICR2_EXTIX_MASK               (0xFFFFU << SYSCFG_EXTICR2_EXTIX_SHIFT)
#define SYSCFG_EXTICR2_EXTIX(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCFG_EXTICR2_EXTIX_SHIFT)) & SYSCFG_EXTICR2_EXTIX_MASK)

/*!
 * @brief SYSCFG_EXTICR3 Register Bit Definition
 */

#define SYSCFG_EXTICR3_EXTIX_SHIFT              (0)
#define SYSCFG_EXTICR3_EXTIX_MASK               (0xFFFFU << SYSCFG_EXTICR3_EXTIX_SHIFT)
#define SYSCFG_EXTICR3_EXTIX(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCFG_EXTICR3_EXTIX_SHIFT)) & SYSCFG_EXTICR3_EXTIX_MASK)

/*!
 * @brief SYSCFG_EXTICR4 Register Bit Definition
 */

#define SYSCFG_EXTICR4_EXTIX_SHIFT              (0)
#define SYSCFG_EXTICR4_EXTIX_MASK               (0xFFFFU << SYSCFG_EXTICR4_EXTIX_SHIFT)
#define SYSCFG_EXTICR4_EXTIX(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCFG_EXTICR4_EXTIX_SHIFT)) & SYSCFG_EXTICR4_EXTIX_MASK)

/*!
 * @brief SYSCFG_CFGR2 Register Bit Definition
 */

#define SYSCFG_CFGR2_MACSPDSEL_SHIFT            (21)
#define SYSCFG_CFGR2_MACSPDSEL_MASK             (0x01U << SYSCFG_CFGR2_MACSPDSEL_SHIFT)
#define SYSCFG_CFGR2_MACSPDSEL(x)               (((uint32_t)(((uint32_t)(x)) << SYSCFG_CFGR2_MACSPDSEL_SHIFT)) & SYSCFG_CFGR2_MACSPDSEL_MASK)

#define SYSCFG_CFGR2_MIIRMIISEL_SHIFT           (20)
#define SYSCFG_CFGR2_MIIRMIISEL_MASK            (0x01U << SYSCFG_CFGR2_MIIRMIISEL_SHIFT)
#define SYSCFG_CFGR2_MIIRMIISEL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCFG_CFGR2_MIIRMIISEL_SHIFT)) & SYSCFG_CFGR2_MIIRMIISEL_MASK)

#define SYSCFG_CFGR2_I2C2MODESEL_SHIFT          (17)
#define SYSCFG_CFGR2_I2C2MODESEL_MASK           (0x01U << SYSCFG_CFGR2_I2C2MODESEL_SHIFT)
#define SYSCFG_CFGR2_I2C2MODESEL(x)             (((uint32_t)(((uint32_t)(x)) << SYSCFG_CFGR2_I2C2MODESEL_SHIFT)) & SYSCFG_CFGR2_I2C2MODESEL_MASK)

#define SYSCFG_CFGR2_I2C1MODESEL_SHIFT          (16)
#define SYSCFG_CFGR2_I2C1MODESEL_MASK           (0x01U << SYSCFG_CFGR2_I2C1MODESEL_SHIFT)
#define SYSCFG_CFGR2_I2C1MODESEL(x)             (((uint32_t)(((uint32_t)(x)) << SYSCFG_CFGR2_I2C1MODESEL_SHIFT)) & SYSCFG_CFGR2_I2C1MODESEL_MASK)

/*!
 * @brief SYSCFG_PDETCSR Register Bit Definition
 */

#define SYSCFG_PDETCSR_VBATDIV3EN_SHIFT         (11)
#define SYSCFG_PDETCSR_VBATDIV3EN_MASK          (0x01U << SYSCFG_PDETCSR_VBATDIV3EN_SHIFT)
#define SYSCFG_PDETCSR_VBATDIV3EN(x)            (((uint32_t)(((uint32_t)(x)) << SYSCFG_PDETCSR_VBATDIV3EN_SHIFT)) & SYSCFG_PDETCSR_VBATDIV3EN_MASK)

#define SYSCFG_PDETCSR_VDTLS_SHIFT              (9)
#define SYSCFG_PDETCSR_VDTLS_MASK               (0x3U << SYSCFG_PDETCSR_VDTLS_SHIFT)
#define SYSCFG_PDETCSR_VDTLS(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCFG_PDETCSR_VDTLS_SHIFT)) & SYSCFG_PDETCSR_VDTLS_MASK)

#define SYSCFG_PDETCSR_VDTE_SHIFT               (8)
#define SYSCFG_PDETCSR_VDTE_MASK                (0x01U << SYSCFG_PDETCSR_VDTE_SHIFT)
#define SYSCFG_PDETCSR_VDTE(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCFG_PDETCSR_VDTE_SHIFT)) & SYSCFG_PDETCSR_VDTE_MASK)

#define SYSCFG_PDETCSR_VDTO_SHIFT               (6)
#define SYSCFG_PDETCSR_VDTO_MASK                (0x01U << SYSCFG_PDETCSR_VDTO_SHIFT)
#define SYSCFG_PDETCSR_VDTO(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCFG_PDETCSR_VDTO_SHIFT)) & SYSCFG_PDETCSR_VDTO_MASK)

#define SYSCFG_PDETCSR_PVDO_SHIFT               (5)
#define SYSCFG_PDETCSR_PVDO_MASK                (0x01U << SYSCFG_PDETCSR_PVDO_SHIFT)
#define SYSCFG_PDETCSR_PVDO(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCFG_PDETCSR_PVDO_SHIFT)) & SYSCFG_PDETCSR_PVDO_MASK)

#define SYSCFG_PDETCSR_PLS_SHIFT                (1)
#define SYSCFG_PDETCSR_PLS_MASK                 (0xFU << SYSCFG_PDETCSR_PLS_SHIFT)
#define SYSCFG_PDETCSR_PLS(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCFG_PDETCSR_PLS_SHIFT)) & SYSCFG_PDETCSR_PLS_MASK)

#define SYSCFG_PDETCSR_PVDE_SHIFT               (0)
#define SYSCFG_PDETCSR_PVDE_MASK                (0x01U << SYSCFG_PDETCSR_PVDE_SHIFT)
#define SYSCFG_PDETCSR_PVDE(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCFG_PDETCSR_PVDE_SHIFT)) & SYSCFG_PDETCSR_PVDE_MASK)

/*!
 * @brief SYSCFG_VOSDLY Register Bit Definition
 */

#define SYSCFG_VOSDLY_VOSDLYCNT_SHIFT           (0)
#define SYSCFG_VOSDLY_VOSDLYCNT_MASK            (0x3FFU << SYSCFG_VOSDLY_VOSDLYCNT_SHIFT)
#define SYSCFG_VOSDLY_VOSDLYCNT(x)              (((uint32_t)(((uint32_t)(x)) << SYSCFG_VOSDLY_VOSDLYCNT_SHIFT)) & SYSCFG_VOSDLY_VOSDLYCNT_MASK)

/*!
 * @}
 */ /* end of group SYSCFG_Register_Masks */
/******************************************************************************
 * SYSCFG Instance
******************************************************************************/
#define SYSCFG                              ((SYSCFG_Type*)SYSCFG_BASE)

/*!
 * @}
 */ /* end of group SYSCFG_Peripheral_Access_Layer */



/*!
 * @addtogroup EXTI_Peripheral_Access_Layer EXTI Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * EXTI Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t IMR;                                                            ///< Interrupt mask register                      offset: 0x00
    __IO uint32_t EMR;                                                            ///< Event mask register                          offset: 0x04
    __IO uint32_t RTSR;                                                           ///< Rising edge trigger selection register       offset: 0x08
    __IO uint32_t FTSR;                                                           ///< Falling edge trigger selection register      offset: 0x0C
    __IO uint32_t SWIER;                                                          ///< Software interrupt event register            offset: 0x10
    __IO uint32_t PR;                                                             ///< Pending register                             offset: 0x14
} EXTI_Type;

/*******************************************************************************
 * EXTI Type
 ******************************************************************************/

/*!
 * @addtogroup EXTI_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief EXTI_IMR Register Bit Definition
 */

#define EXTI_IMR_IMRX_SHIFT                     (0)
#define EXTI_IMR_IMRX_MASK                      (0xFFFFFFFFU << EXTI_IMR_IMRX_SHIFT)
#define EXTI_IMR_IMRX(x)                        (((uint32_t)(((uint32_t)(x)) << EXTI_IMR_IMRX_SHIFT)) & EXTI_IMR_IMRX_MASK)

/*!
 * @brief EXTI_EMR Register Bit Definition
 */

#define EXTI_EMR_EMRX_SHIFT                     (0)
#define EXTI_EMR_EMRX_MASK                      (0xFFFFFFFFU << EXTI_EMR_EMRX_SHIFT)
#define EXTI_EMR_EMRX(x)                        (((uint32_t)(((uint32_t)(x)) << EXTI_EMR_EMRX_SHIFT)) & EXTI_EMR_EMRX_MASK)

/*!
 * @brief EXTI_RTSR Register Bit Definition
 */

#define EXTI_RTSR_TRX_SHIFT                     (0)
#define EXTI_RTSR_TRX_MASK                      (0xFFFFFFFFU << EXTI_RTSR_TRX_SHIFT)
#define EXTI_RTSR_TRX(x)                        (((uint32_t)(((uint32_t)(x)) << EXTI_RTSR_TRX_SHIFT)) & EXTI_RTSR_TRX_MASK)

/*!
 * @brief EXTI_FTSR Register Bit Definition
 */

#define EXTI_FTSR_TRX_SHIFT                     (0)
#define EXTI_FTSR_TRX_MASK                      (0xFFFFFFFFU << EXTI_FTSR_TRX_SHIFT)
#define EXTI_FTSR_TRX(x)                        (((uint32_t)(((uint32_t)(x)) << EXTI_FTSR_TRX_SHIFT)) & EXTI_FTSR_TRX_MASK)

/*!
 * @brief EXTI_SWIER Register Bit Definition
 */

#define EXTI_SWIER_SWIERX_SHIFT                 (0)
#define EXTI_SWIER_SWIERX_MASK                  (0x3FFFFFU << EXTI_SWIER_SWIERX_SHIFT)
#define EXTI_SWIER_SWIERX(x)                    (((uint32_t)(((uint32_t)(x)) << EXTI_SWIER_SWIERX_SHIFT)) & EXTI_SWIER_SWIERX_MASK)

#define EXTI_SWIER_SWIERX_SHIFT                 (0)
#define EXTI_SWIER_SWIERX_MASK                  (0x3FFFFFU << EXTI_SWIER_SWIERX_SHIFT)
#define EXTI_SWIER_SWIERX(x)                    (((uint32_t)(((uint32_t)(x)) << EXTI_SWIER_SWIERX_SHIFT)) & EXTI_SWIER_SWIERX_MASK)

/*!
 * @brief EXTI_PR Register Bit Definition
 */

#define EXTI_PR_PRX_SHIFT                       (0)
#define EXTI_PR_PRX_MASK                        (0x3FFFFFU << EXTI_PR_PRX_SHIFT)
#define EXTI_PR_PRX(x)                          (((uint32_t)(((uint32_t)(x)) << EXTI_PR_PRX_SHIFT)) & EXTI_PR_PRX_MASK)

/*!
 * @}
 */ /* end of group EXTI_Register_Masks */
/******************************************************************************
 * EXTI Instance
******************************************************************************/
#define EXTI                                ((EXTI_Type*)EXTI_BASE)

/*!
 * @}
 */ /* end of group EXTI_Peripheral_Access_Layer */



/*!
 * @addtogroup DMA_Peripheral_Access_Layer DMA Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * DMA Type
 ******************************************************************************/
#define DMA_CHANNEL_COUNT  7u

typedef struct {
    __IO uint32_t ISR;                                                          ///< DMAinterruptstatusregister                   offset: 0x00
    __IO uint32_t IFCR;                                                         ///< DMAinterruptflagclearregister                offset: 0x04
    struct {
            __IO uint32_t CCR;                                                  ///< DMAchannelxconfigurationregister             offset: 0x08
            __IO uint32_t CNDTR;                                                ///< DMAchannelxtransferquantityregister          offset: 0x0C
            __IO uint32_t CPAR;                                                 ///< DMAchannelxperipheraladdressregister         offset: 0x10
            __IO uint32_t CMAR;                                                 ///< DMAchannelxmemoryaddressregister             offset: 0x14
            __IO uint32_t Reserved0;
    } CH[DMA_CHANNEL_COUNT];

} DMA_Type;
/*******************************************************************************
 * DMA Type
 ******************************************************************************/

/*!
 * @addtogroup DMA_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief DMA_ISR Register Bit Definition
 */

#define DMA_ISR_TEIF7_SHIFT                     (27)
#define DMA_ISR_TEIF7_MASK                      (0x01U << DMA_ISR_TEIF7_SHIFT)
#define DMA_ISR_TEIF7(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TEIF7_SHIFT)) & DMA_ISR_TEIF7_MASK)

#define DMA_ISR_HTIF7_SHIFT                     (26)
#define DMA_ISR_HTIF7_MASK                      (0x01U << DMA_ISR_HTIF7_SHIFT)
#define DMA_ISR_HTIF7(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_HTIF7_SHIFT)) & DMA_ISR_HTIF7_MASK)

#define DMA_ISR_TCIF7_SHIFT                     (25)
#define DMA_ISR_TCIF7_MASK                      (0x01U << DMA_ISR_TCIF7_SHIFT)
#define DMA_ISR_TCIF7(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TCIF7_SHIFT)) & DMA_ISR_TCIF7_MASK)

#define DMA_ISR_GIF7_SHIFT                      (24)
#define DMA_ISR_GIF7_MASK                       (0x01U << DMA_ISR_GIF7_SHIFT)
#define DMA_ISR_GIF7(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ISR_GIF7_SHIFT)) & DMA_ISR_GIF7_MASK)

#define DMA_ISR_TEIF6_SHIFT                     (23)
#define DMA_ISR_TEIF6_MASK                      (0x01U << DMA_ISR_TEIF6_SHIFT)
#define DMA_ISR_TEIF6(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TEIF6_SHIFT)) & DMA_ISR_TEIF6_MASK)

#define DMA_ISR_HTIF6_SHIFT                     (22)
#define DMA_ISR_HTIF6_MASK                      (0x01U << DMA_ISR_HTIF6_SHIFT)
#define DMA_ISR_HTIF6(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_HTIF6_SHIFT)) & DMA_ISR_HTIF6_MASK)

#define DMA_ISR_TCIF6_SHIFT                     (21)
#define DMA_ISR_TCIF6_MASK                      (0x01U << DMA_ISR_TCIF6_SHIFT)
#define DMA_ISR_TCIF6(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TCIF6_SHIFT)) & DMA_ISR_TCIF6_MASK)

#define DMA_ISR_GIF6_SHIFT                      (20)
#define DMA_ISR_GIF6_MASK                       (0x01U << DMA_ISR_GIF6_SHIFT)
#define DMA_ISR_GIF6(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ISR_GIF6_SHIFT)) & DMA_ISR_GIF6_MASK)

#define DMA_ISR_TEIF5_SHIFT                     (19)
#define DMA_ISR_TEIF5_MASK                      (0x01U << DMA_ISR_TEIF5_SHIFT)
#define DMA_ISR_TEIF5(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TEIF5_SHIFT)) & DMA_ISR_TEIF5_MASK)

#define DMA_ISR_HTIF5_SHIFT                     (18)
#define DMA_ISR_HTIF5_MASK                      (0x01U << DMA_ISR_HTIF5_SHIFT)
#define DMA_ISR_HTIF5(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_HTIF5_SHIFT)) & DMA_ISR_HTIF5_MASK)

#define DMA_ISR_TCIF5_SHIFT                     (17)
#define DMA_ISR_TCIF5_MASK                      (0x01U << DMA_ISR_TCIF5_SHIFT)
#define DMA_ISR_TCIF5(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TCIF5_SHIFT)) & DMA_ISR_TCIF5_MASK)

#define DMA_ISR_GIF5_SHIFT                      (16)
#define DMA_ISR_GIF5_MASK                       (0x01U << DMA_ISR_GIF5_SHIFT)
#define DMA_ISR_GIF5(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ISR_GIF5_SHIFT)) & DMA_ISR_GIF5_MASK)

#define DMA_ISR_TEIF4_SHIFT                     (15)
#define DMA_ISR_TEIF4_MASK                      (0x01U << DMA_ISR_TEIF4_SHIFT)
#define DMA_ISR_TEIF4(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TEIF4_SHIFT)) & DMA_ISR_TEIF4_MASK)

#define DMA_ISR_HTIF4_SHIFT                     (14)
#define DMA_ISR_HTIF4_MASK                      (0x01U << DMA_ISR_HTIF4_SHIFT)
#define DMA_ISR_HTIF4(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_HTIF4_SHIFT)) & DMA_ISR_HTIF4_MASK)

#define DMA_ISR_TCIF4_SHIFT                     (13)
#define DMA_ISR_TCIF4_MASK                      (0x01U << DMA_ISR_TCIF4_SHIFT)
#define DMA_ISR_TCIF4(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TCIF4_SHIFT)) & DMA_ISR_TCIF4_MASK)

#define DMA_ISR_GIF4_SHIFT                      (12)
#define DMA_ISR_GIF4_MASK                       (0x01U << DMA_ISR_GIF4_SHIFT)
#define DMA_ISR_GIF4(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ISR_GIF4_SHIFT)) & DMA_ISR_GIF4_MASK)

#define DMA_ISR_TEIF3_SHIFT                     (11)
#define DMA_ISR_TEIF3_MASK                      (0x01U << DMA_ISR_TEIF3_SHIFT)
#define DMA_ISR_TEIF3(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TEIF3_SHIFT)) & DMA_ISR_TEIF3_MASK)

#define DMA_ISR_HTIF3_SHIFT                     (10)
#define DMA_ISR_HTIF3_MASK                      (0x01U << DMA_ISR_HTIF3_SHIFT)
#define DMA_ISR_HTIF3(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_HTIF3_SHIFT)) & DMA_ISR_HTIF3_MASK)

#define DMA_ISR_TCIF3_SHIFT                     (9)
#define DMA_ISR_TCIF3_MASK                      (0x01U << DMA_ISR_TCIF3_SHIFT)
#define DMA_ISR_TCIF3(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TCIF3_SHIFT)) & DMA_ISR_TCIF3_MASK)

#define DMA_ISR_GIF3_SHIFT                      (8)
#define DMA_ISR_GIF3_MASK                       (0x01U << DMA_ISR_GIF3_SHIFT)
#define DMA_ISR_GIF3(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ISR_GIF3_SHIFT)) & DMA_ISR_GIF3_MASK)

#define DMA_ISR_TEIF2_SHIFT                     (7)
#define DMA_ISR_TEIF2_MASK                      (0x01U << DMA_ISR_TEIF2_SHIFT)
#define DMA_ISR_TEIF2(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TEIF2_SHIFT)) & DMA_ISR_TEIF2_MASK)

#define DMA_ISR_HTIF2_SHIFT                     (6)
#define DMA_ISR_HTIF2_MASK                      (0x01U << DMA_ISR_HTIF2_SHIFT)
#define DMA_ISR_HTIF2(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_HTIF2_SHIFT)) & DMA_ISR_HTIF2_MASK)

#define DMA_ISR_TCIF2_SHIFT                     (5)
#define DMA_ISR_TCIF2_MASK                      (0x01U << DMA_ISR_TCIF2_SHIFT)
#define DMA_ISR_TCIF2(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TCIF2_SHIFT)) & DMA_ISR_TCIF2_MASK)

#define DMA_ISR_GIF2_SHIFT                      (4)
#define DMA_ISR_GIF2_MASK                       (0x01U << DMA_ISR_GIF2_SHIFT)
#define DMA_ISR_GIF2(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ISR_GIF2_SHIFT)) & DMA_ISR_GIF2_MASK)

#define DMA_ISR_TEIF1_SHIFT                     (3)
#define DMA_ISR_TEIF1_MASK                      (0x01U << DMA_ISR_TEIF1_SHIFT)
#define DMA_ISR_TEIF1(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TEIF1_SHIFT)) & DMA_ISR_TEIF1_MASK)

#define DMA_ISR_HTIF1_SHIFT                     (2)
#define DMA_ISR_HTIF1_MASK                      (0x01U << DMA_ISR_HTIF1_SHIFT)
#define DMA_ISR_HTIF1(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_HTIF1_SHIFT)) & DMA_ISR_HTIF1_MASK)

#define DMA_ISR_TCIF1_SHIFT                     (1)
#define DMA_ISR_TCIF1_MASK                      (0x01U << DMA_ISR_TCIF1_SHIFT)
#define DMA_ISR_TCIF1(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_ISR_TCIF1_SHIFT)) & DMA_ISR_TCIF1_MASK)

#define DMA_ISR_GIF1_SHIFT                      (0)
#define DMA_ISR_GIF1_MASK                       (0x01U << DMA_ISR_GIF1_SHIFT)
#define DMA_ISR_GIF1(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_ISR_GIF1_SHIFT)) & DMA_ISR_GIF1_MASK)

/*!
 * @brief DMA_IFCR Register Bit Definition
 */

#define DMA_IFCR_CTEIF7_SHIFT                   (27)
#define DMA_IFCR_CTEIF7_MASK                    (0x01U << DMA_IFCR_CTEIF7_SHIFT)
#define DMA_IFCR_CTEIF7(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTEIF7_SHIFT)) & DMA_IFCR_CTEIF7_MASK)

#define DMA_IFCR_CHTIF7_SHIFT                   (26)
#define DMA_IFCR_CHTIF7_MASK                    (0x01U << DMA_IFCR_CHTIF7_SHIFT)
#define DMA_IFCR_CHTIF7(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CHTIF7_SHIFT)) & DMA_IFCR_CHTIF7_MASK)

#define DMA_IFCR_CTCIF7_SHIFT                   (25)
#define DMA_IFCR_CTCIF7_MASK                    (0x01U << DMA_IFCR_CTCIF7_SHIFT)
#define DMA_IFCR_CTCIF7(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTCIF7_SHIFT)) & DMA_IFCR_CTCIF7_MASK)

#define DMA_IFCR_CGIF7_SHIFT                    (24)
#define DMA_IFCR_CGIF7_MASK                     (0x01U << DMA_IFCR_CGIF7_SHIFT)
#define DMA_IFCR_CGIF7(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CGIF7_SHIFT)) & DMA_IFCR_CGIF7_MASK)

#define DMA_IFCR_CTEIF6_SHIFT                   (23)
#define DMA_IFCR_CTEIF6_MASK                    (0x01U << DMA_IFCR_CTEIF6_SHIFT)
#define DMA_IFCR_CTEIF6(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTEIF6_SHIFT)) & DMA_IFCR_CTEIF6_MASK)

#define DMA_IFCR_CHTIF6_SHIFT                   (22)
#define DMA_IFCR_CHTIF6_MASK                    (0x01U << DMA_IFCR_CHTIF6_SHIFT)
#define DMA_IFCR_CHTIF6(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CHTIF6_SHIFT)) & DMA_IFCR_CHTIF6_MASK)

#define DMA_IFCR_CTCIF6_SHIFT                   (21)
#define DMA_IFCR_CTCIF6_MASK                    (0x01U << DMA_IFCR_CTCIF6_SHIFT)
#define DMA_IFCR_CTCIF6(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTCIF6_SHIFT)) & DMA_IFCR_CTCIF6_MASK)

#define DMA_IFCR_CGIF6_SHIFT                    (20)
#define DMA_IFCR_CGIF6_MASK                     (0x01U << DMA_IFCR_CGIF6_SHIFT)
#define DMA_IFCR_CGIF6(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CGIF6_SHIFT)) & DMA_IFCR_CGIF6_MASK)

#define DMA_IFCR_CTEIF5_SHIFT                   (19)
#define DMA_IFCR_CTEIF5_MASK                    (0x01U << DMA_IFCR_CTEIF5_SHIFT)
#define DMA_IFCR_CTEIF5(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTEIF5_SHIFT)) & DMA_IFCR_CTEIF5_MASK)

#define DMA_IFCR_CHTIF5_SHIFT                   (18)
#define DMA_IFCR_CHTIF5_MASK                    (0x01U << DMA_IFCR_CHTIF5_SHIFT)
#define DMA_IFCR_CHTIF5(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CHTIF5_SHIFT)) & DMA_IFCR_CHTIF5_MASK)

#define DMA_IFCR_CTCIF5_SHIFT                   (17)
#define DMA_IFCR_CTCIF5_MASK                    (0x01U << DMA_IFCR_CTCIF5_SHIFT)
#define DMA_IFCR_CTCIF5(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTCIF5_SHIFT)) & DMA_IFCR_CTCIF5_MASK)

#define DMA_IFCR_CGIF5_SHIFT                    (16)
#define DMA_IFCR_CGIF5_MASK                     (0x01U << DMA_IFCR_CGIF5_SHIFT)
#define DMA_IFCR_CGIF5(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CGIF5_SHIFT)) & DMA_IFCR_CGIF5_MASK)

#define DMA_IFCR_CTEIF4_SHIFT                   (15)
#define DMA_IFCR_CTEIF4_MASK                    (0x01U << DMA_IFCR_CTEIF4_SHIFT)
#define DMA_IFCR_CTEIF4(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTEIF4_SHIFT)) & DMA_IFCR_CTEIF4_MASK)

#define DMA_IFCR_CHTIF4_SHIFT                   (14)
#define DMA_IFCR_CHTIF4_MASK                    (0x01U << DMA_IFCR_CHTIF4_SHIFT)
#define DMA_IFCR_CHTIF4(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CHTIF4_SHIFT)) & DMA_IFCR_CHTIF4_MASK)

#define DMA_IFCR_CTCIF4_SHIFT                   (13)
#define DMA_IFCR_CTCIF4_MASK                    (0x01U << DMA_IFCR_CTCIF4_SHIFT)
#define DMA_IFCR_CTCIF4(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTCIF4_SHIFT)) & DMA_IFCR_CTCIF4_MASK)

#define DMA_IFCR_CGIF4_SHIFT                    (12)
#define DMA_IFCR_CGIF4_MASK                     (0x01U << DMA_IFCR_CGIF4_SHIFT)
#define DMA_IFCR_CGIF4(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CGIF4_SHIFT)) & DMA_IFCR_CGIF4_MASK)

#define DMA_IFCR_CTEIF3_SHIFT                   (11)
#define DMA_IFCR_CTEIF3_MASK                    (0x01U << DMA_IFCR_CTEIF3_SHIFT)
#define DMA_IFCR_CTEIF3(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTEIF3_SHIFT)) & DMA_IFCR_CTEIF3_MASK)

#define DMA_IFCR_CHTIF3_SHIFT                   (10)
#define DMA_IFCR_CHTIF3_MASK                    (0x01U << DMA_IFCR_CHTIF3_SHIFT)
#define DMA_IFCR_CHTIF3(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CHTIF3_SHIFT)) & DMA_IFCR_CHTIF3_MASK)

#define DMA_IFCR_CTCIF3_SHIFT                   (9)
#define DMA_IFCR_CTCIF3_MASK                    (0x01U << DMA_IFCR_CTCIF3_SHIFT)
#define DMA_IFCR_CTCIF3(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTCIF3_SHIFT)) & DMA_IFCR_CTCIF3_MASK)

#define DMA_IFCR_CGIF3_SHIFT                    (8)
#define DMA_IFCR_CGIF3_MASK                     (0x01U << DMA_IFCR_CGIF3_SHIFT)
#define DMA_IFCR_CGIF3(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CGIF3_SHIFT)) & DMA_IFCR_CGIF3_MASK)

#define DMA_IFCR_CTEIF2_SHIFT                   (7)
#define DMA_IFCR_CTEIF2_MASK                    (0x01U << DMA_IFCR_CTEIF2_SHIFT)
#define DMA_IFCR_CTEIF2(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTEIF2_SHIFT)) & DMA_IFCR_CTEIF2_MASK)

#define DMA_IFCR_CHTIF2_SHIFT                   (6)
#define DMA_IFCR_CHTIF2_MASK                    (0x01U << DMA_IFCR_CHTIF2_SHIFT)
#define DMA_IFCR_CHTIF2(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CHTIF2_SHIFT)) & DMA_IFCR_CHTIF2_MASK)

#define DMA_IFCR_CTCIF2_SHIFT                   (5)
#define DMA_IFCR_CTCIF2_MASK                    (0x01U << DMA_IFCR_CTCIF2_SHIFT)
#define DMA_IFCR_CTCIF2(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTCIF2_SHIFT)) & DMA_IFCR_CTCIF2_MASK)

#define DMA_IFCR_CGIF2_SHIFT                    (4)
#define DMA_IFCR_CGIF2_MASK                     (0x01U << DMA_IFCR_CGIF2_SHIFT)
#define DMA_IFCR_CGIF2(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CGIF2_SHIFT)) & DMA_IFCR_CGIF2_MASK)

#define DMA_IFCR_CTEIF1_SHIFT                   (3)
#define DMA_IFCR_CTEIF1_MASK                    (0x01U << DMA_IFCR_CTEIF1_SHIFT)
#define DMA_IFCR_CTEIF1(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTEIF1_SHIFT)) & DMA_IFCR_CTEIF1_MASK)

#define DMA_IFCR_CHTIF1_SHIFT                   (2)
#define DMA_IFCR_CHTIF1_MASK                    (0x01U << DMA_IFCR_CHTIF1_SHIFT)
#define DMA_IFCR_CHTIF1(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CHTIF1_SHIFT)) & DMA_IFCR_CHTIF1_MASK)

#define DMA_IFCR_CTCIF1_SHIFT                   (1)
#define DMA_IFCR_CTCIF1_MASK                    (0x01U << DMA_IFCR_CTCIF1_SHIFT)
#define DMA_IFCR_CTCIF1(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CTCIF1_SHIFT)) & DMA_IFCR_CTCIF1_MASK)

#define DMA_IFCR_CGIF1_SHIFT                    (0)
#define DMA_IFCR_CGIF1_MASK                     (0x01U << DMA_IFCR_CGIF1_SHIFT)
#define DMA_IFCR_CGIF1(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_IFCR_CGIF1_SHIFT)) & DMA_IFCR_CGIF1_MASK)

/*!
 * @brief DMA_CCR Register Bit Definition
 */

#define DMA_CCR_ARE_SHIFT                       (15)
#define DMA_CCR_ARE_MASK                        (0x01U << DMA_CCR_ARE_SHIFT)
#define DMA_CCR_ARE(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_CCR_ARE_SHIFT)) & DMA_CCR_ARE_MASK)

#define DMA_CCR_MEM2MEM_SHIFT                   (14)
#define DMA_CCR_MEM2MEM_MASK                    (0x01U << DMA_CCR_MEM2MEM_SHIFT)
#define DMA_CCR_MEM2MEM(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_CCR_MEM2MEM_SHIFT)) & DMA_CCR_MEM2MEM_MASK)

#define DMA_CCR_PL_SHIFT                        (12)
#define DMA_CCR_PL_MASK                         (0x3U << DMA_CCR_PL_SHIFT)
#define DMA_CCR_PL(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CCR_PL_SHIFT)) & DMA_CCR_PL_MASK)

#define DMA_CCR_MSIZE_SHIFT                     (10)
#define DMA_CCR_MSIZE_MASK                      (0x3U << DMA_CCR_MSIZE_SHIFT)
#define DMA_CCR_MSIZE(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_CCR_MSIZE_SHIFT)) & DMA_CCR_MSIZE_MASK)

#define DMA_CCR_PSIZE_SHIFT                     (8)
#define DMA_CCR_PSIZE_MASK                      (0x3U << DMA_CCR_PSIZE_SHIFT)
#define DMA_CCR_PSIZE(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_CCR_PSIZE_SHIFT)) & DMA_CCR_PSIZE_MASK)

#define DMA_CCR_MINC_SHIFT                      (7)
#define DMA_CCR_MINC_MASK                       (0x01U << DMA_CCR_MINC_SHIFT)
#define DMA_CCR_MINC(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_CCR_MINC_SHIFT)) & DMA_CCR_MINC_MASK)

#define DMA_CCR_PINC_SHIFT                      (6)
#define DMA_CCR_PINC_MASK                       (0x01U << DMA_CCR_PINC_SHIFT)
#define DMA_CCR_PINC(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_CCR_PINC_SHIFT)) & DMA_CCR_PINC_MASK)

#define DMA_CCR_CIRC_SHIFT                      (5)
#define DMA_CCR_CIRC_MASK                       (0x01U << DMA_CCR_CIRC_SHIFT)
#define DMA_CCR_CIRC(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_CCR_CIRC_SHIFT)) & DMA_CCR_CIRC_MASK)

#define DMA_CCR_DIR_SHIFT                       (4)
#define DMA_CCR_DIR_MASK                        (0x01U << DMA_CCR_DIR_SHIFT)
#define DMA_CCR_DIR(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_CCR_DIR_SHIFT)) & DMA_CCR_DIR_MASK)

#define DMA_CCR_TEIE_SHIFT                      (3)
#define DMA_CCR_TEIE_MASK                       (0x01U << DMA_CCR_TEIE_SHIFT)
#define DMA_CCR_TEIE(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_CCR_TEIE_SHIFT)) & DMA_CCR_TEIE_MASK)

#define DMA_CCR_HTIE_SHIFT                      (2)
#define DMA_CCR_HTIE_MASK                       (0x01U << DMA_CCR_HTIE_SHIFT)
#define DMA_CCR_HTIE(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_CCR_HTIE_SHIFT)) & DMA_CCR_HTIE_MASK)

#define DMA_CCR_TCIE_SHIFT                      (1)
#define DMA_CCR_TCIE_MASK                       (0x01U << DMA_CCR_TCIE_SHIFT)
#define DMA_CCR_TCIE(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_CCR_TCIE_SHIFT)) & DMA_CCR_TCIE_MASK)

#define DMA_CCR_EN_SHIFT                        (0)
#define DMA_CCR_EN_MASK                         (0x01U << DMA_CCR_EN_SHIFT)
#define DMA_CCR_EN(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_CCR_EN_SHIFT)) & DMA_CCR_EN_MASK)

/*!
 * @brief DMA_CNDTR Register Bit Definition
 */

#define DMA_CNDTR_NDT_SHIFT                     (0)
#define DMA_CNDTR_NDT_MASK                      (0xFFFFU << DMA_CNDTR_NDT_SHIFT)
#define DMA_CNDTR_NDT(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_CNDTR_NDT_SHIFT)) & DMA_CNDTR_NDT_MASK)

/*!
 * @brief DMA_CPAR Register Bit Definition
 */

#define DMA_CPAR_PA_SHIFT                       (0)
#define DMA_CPAR_PA_MASK                        (0xFFFFFFFFU << DMA_CPAR_PA_SHIFT)
#define DMA_CPAR_PA(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_CPAR_PA_SHIFT)) & DMA_CPAR_PA_MASK)

/*!
 * @brief DMA_CMAR Register Bit Definition
 */

#define DMA_CMAR_MA_SHIFT                       (0)
#define DMA_CMAR_MA_MASK                        (0xFFFFFFFFU << DMA_CMAR_MA_SHIFT)
#define DMA_CMAR_MA(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_CMAR_MA_SHIFT)) & DMA_CMAR_MA_MASK)

/*!
 * @}
 */ /* end of group DMA_Register_Masks */
/******************************************************************************
 * DMA Instance
******************************************************************************/
#define DMA1                                ((DMA_Type*)DMA1_BASE)
#define DMA2                                ((DMA_Type*)DMA2_BASE)

/*!
 * @}
 */ /* end of group DMA_Peripheral_Access_Layer */



/*!
 * @addtogroup BKP_Peripheral_Access_Layer BKP Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * BKP Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t Reserved5[16];                                                  ///< Reserved
    __IO uint32_t RTCCR;                                                          ///< RTC clock calibration register               offset: 0x40
    __IO uint32_t CR;                                                             ///< Backup control register                      offset: 0x44
    __IO uint32_t CSR;                                                            ///< Backup control status register               offset: 0x48
    __IO uint32_t Reserved6[1];                                                   ///< Reserved
    __IO uint32_t DR[20];                                                             ///< Backup data register x                       offset: 0x50
} BKP_Type;

/*******************************************************************************
 * BKP Type
 ******************************************************************************/

/*!
 * @addtogroup BKP_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief BKP_RTCCR Register Bit Definition
 */

#define BKP_RTCCR_ASOS_SHIFT                    (9)
#define BKP_RTCCR_ASOS_MASK                     (0x01U << BKP_RTCCR_ASOS_SHIFT)
#define BKP_RTCCR_ASOS(x)                       (((uint32_t)(((uint32_t)(x)) << BKP_RTCCR_ASOS_SHIFT)) & BKP_RTCCR_ASOS_MASK)

#define BKP_RTCCR_ASOE_SHIFT                    (8)
#define BKP_RTCCR_ASOE_MASK                     (0x01U << BKP_RTCCR_ASOE_SHIFT)
#define BKP_RTCCR_ASOE(x)                       (((uint32_t)(((uint32_t)(x)) << BKP_RTCCR_ASOE_SHIFT)) & BKP_RTCCR_ASOE_MASK)

#define BKP_RTCCR_CCO_SHIFT                     (7)
#define BKP_RTCCR_CCO_MASK                      (0x01U << BKP_RTCCR_CCO_SHIFT)
#define BKP_RTCCR_CCO(x)                        (((uint32_t)(((uint32_t)(x)) << BKP_RTCCR_CCO_SHIFT)) & BKP_RTCCR_CCO_MASK)

#define BKP_RTCCR_CAL_SHIFT                     (0)
#define BKP_RTCCR_CAL_MASK                      (0x7FU << BKP_RTCCR_CAL_SHIFT)
#define BKP_RTCCR_CAL(x)                        (((uint32_t)(((uint32_t)(x)) << BKP_RTCCR_CAL_SHIFT)) & BKP_RTCCR_CAL_MASK)

/*!
 * @brief BKP_CR Register Bit Definition
 */

#define BKP_CR_TPAL_SHIFT                       (1)
#define BKP_CR_TPAL_MASK                        (0x01U << BKP_CR_TPAL_SHIFT)
#define BKP_CR_TPAL(x)                          (((uint32_t)(((uint32_t)(x)) << BKP_CR_TPAL_SHIFT)) & BKP_CR_TPAL_MASK)

#define BKP_CR_TPE_SHIFT                        (0)
#define BKP_CR_TPE_MASK                         (0x01U << BKP_CR_TPE_SHIFT)
#define BKP_CR_TPE(x)                           (((uint32_t)(((uint32_t)(x)) << BKP_CR_TPE_SHIFT)) & BKP_CR_TPE_MASK)

/*!
 * @brief BKP_CSR Register Bit Definition
 */

#define BKP_CSR_TIF_SHIFT                       (9)
#define BKP_CSR_TIF_MASK                        (0x01U << BKP_CSR_TIF_SHIFT)
#define BKP_CSR_TIF(x)                          (((uint32_t)(((uint32_t)(x)) << BKP_CSR_TIF_SHIFT)) & BKP_CSR_TIF_MASK)

#define BKP_CSR_TEF_SHIFT                       (8)
#define BKP_CSR_TEF_MASK                        (0x01U << BKP_CSR_TEF_SHIFT)
#define BKP_CSR_TEF(x)                          (((uint32_t)(((uint32_t)(x)) << BKP_CSR_TEF_SHIFT)) & BKP_CSR_TEF_MASK)

#define BKP_CSR_TPIE_SHIFT                      (2)
#define BKP_CSR_TPIE_MASK                       (0x01U << BKP_CSR_TPIE_SHIFT)
#define BKP_CSR_TPIE(x)                         (((uint32_t)(((uint32_t)(x)) << BKP_CSR_TPIE_SHIFT)) & BKP_CSR_TPIE_MASK)

#define BKP_CSR_CTI_SHIFT                       (1)
#define BKP_CSR_CTI_MASK                        (0x01U << BKP_CSR_CTI_SHIFT)
#define BKP_CSR_CTI(x)                          (((uint32_t)(((uint32_t)(x)) << BKP_CSR_CTI_SHIFT)) & BKP_CSR_CTI_MASK)

#define BKP_CSR_CTE_SHIFT                       (0)
#define BKP_CSR_CTE_MASK                        (0x01U << BKP_CSR_CTE_SHIFT)
#define BKP_CSR_CTE(x)                          (((uint32_t)(((uint32_t)(x)) << BKP_CSR_CTE_SHIFT)) & BKP_CSR_CTE_MASK)

/*!
 * @brief BKP_DR Register Bit Definition
 */

#define BKP_DR_BKP_SHIFT                        (0)
#define BKP_DR_BKP_MASK                         (0xFFFFU << BKP_DR_BKP_SHIFT)
#define BKP_DR_BKP(x)                           (((uint32_t)(((uint32_t)(x)) << BKP_DR_BKP_SHIFT)) & BKP_DR_BKP_MASK)

/*!
 * @}
 */ /* end of group BKP_Register_Masks */
/******************************************************************************
 * BKP Instance
******************************************************************************/
#define BKP                             ((BKP_Type*)RTC_BKP_BASE)

/*!
 * @}
 */ /* end of group BKP_Peripheral_Access_Layer */



/*!
 * @addtogroup CRS_Peripheral_Access_Layer CRS Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * CRS Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CR;                                                             ///< CRS control register                         offset: 0x00
    __IO uint32_t CFGR;                                                           ///< CRS configuration register                   offset: 0x04
    __IO uint32_t lSR;                                                            ///< CRS interrupt status register                offset: 0x08
    __IO uint32_t lCR;                                                            ///< CRS interrupt flag clear register            offset: 0x0C
} CRS_Type;

/*******************************************************************************
 * CRS Type
 ******************************************************************************/

/*!
 * @addtogroup CRS_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief CRS_CR Register Bit Definition
 */

#define CRS_CR_TRIM_SHIFT                       (8)
#define CRS_CR_TRIM_MASK                        (0x3FFU << CRS_CR_TRIM_SHIFT)
#define CRS_CR_TRIM(x)                          (((uint32_t)(((uint32_t)(x)) << CRS_CR_TRIM_SHIFT)) & CRS_CR_TRIM_MASK)

#define CRS_CR_SWSYNC_SHIFT                     (7)
#define CRS_CR_SWSYNC_MASK                      (0x01U << CRS_CR_SWSYNC_SHIFT)
#define CRS_CR_SWSYNC(x)                        (((uint32_t)(((uint32_t)(x)) << CRS_CR_SWSYNC_SHIFT)) & CRS_CR_SWSYNC_MASK)

#define CRS_CR_AUTOTRIMEN_SHIFT                 (6)
#define CRS_CR_AUTOTRIMEN_MASK                  (0x01U << CRS_CR_AUTOTRIMEN_SHIFT)
#define CRS_CR_AUTOTRIMEN(x)                    (((uint32_t)(((uint32_t)(x)) << CRS_CR_AUTOTRIMEN_SHIFT)) & CRS_CR_AUTOTRIMEN_MASK)

#define CRS_CR_CEN_SHIFT                        (5)
#define CRS_CR_CEN_MASK                         (0x01U << CRS_CR_CEN_SHIFT)
#define CRS_CR_CEN(x)                           (((uint32_t)(((uint32_t)(x)) << CRS_CR_CEN_SHIFT)) & CRS_CR_CEN_MASK)

#define CRS_CR_ESYNCIE_SHIFT                    (3)
#define CRS_CR_ESYNCIE_MASK                     (0x01U << CRS_CR_ESYNCIE_SHIFT)
#define CRS_CR_ESYNCIE(x)                       (((uint32_t)(((uint32_t)(x)) << CRS_CR_ESYNCIE_SHIFT)) & CRS_CR_ESYNCIE_MASK)

#define CRS_CR_ERRIE_SHIFT                      (2)
#define CRS_CR_ERRIE_MASK                       (0x01U << CRS_CR_ERRIE_SHIFT)
#define CRS_CR_ERRIE(x)                         (((uint32_t)(((uint32_t)(x)) << CRS_CR_ERRIE_SHIFT)) & CRS_CR_ERRIE_MASK)

#define CRS_CR_SYNCWARNIE_SHIFT                 (1)
#define CRS_CR_SYNCWARNIE_MASK                  (0x01U << CRS_CR_SYNCWARNIE_SHIFT)
#define CRS_CR_SYNCWARNIE(x)                    (((uint32_t)(((uint32_t)(x)) << CRS_CR_SYNCWARNIE_SHIFT)) & CRS_CR_SYNCWARNIE_MASK)

#define CRS_CR_SYNCOKIE_SHIFT                   (0)
#define CRS_CR_SYNCOKIE_MASK                    (0x01U << CRS_CR_SYNCOKIE_SHIFT)
#define CRS_CR_SYNCOKIE(x)                      (((uint32_t)(((uint32_t)(x)) << CRS_CR_SYNCOKIE_SHIFT)) & CRS_CR_SYNCOKIE_MASK)

/*!
 * @brief CRS_CFGR Register Bit Definition
 */

#define CRS_CFGR_SYNCPOL_SHIFT                  (31)
#define CRS_CFGR_SYNCPOL_MASK                   (0x01U << CRS_CFGR_SYNCPOL_SHIFT)
#define CRS_CFGR_SYNCPOL(x)                     (((uint32_t)(((uint32_t)(x)) << CRS_CFGR_SYNCPOL_SHIFT)) & CRS_CFGR_SYNCPOL_MASK)

#define CRS_CFGR_SYNCSRC_SHIFT                  (28)
#define CRS_CFGR_SYNCSRC_MASK                   (0x3U << CRS_CFGR_SYNCSRC_SHIFT)
#define CRS_CFGR_SYNCSRC(x)                     (((uint32_t)(((uint32_t)(x)) << CRS_CFGR_SYNCSRC_SHIFT)) & CRS_CFGR_SYNCSRC_MASK)

#define CRS_CFGR_SYNCDIV_SHIFT                  (24)
#define CRS_CFGR_SYNCDIV_MASK                   (0x7U << CRS_CFGR_SYNCDIV_SHIFT)
#define CRS_CFGR_SYNCDIV(x)                     (((uint32_t)(((uint32_t)(x)) << CRS_CFGR_SYNCDIV_SHIFT)) & CRS_CFGR_SYNCDIV_MASK)

#define CRS_CFGR_FELIM_SHIFT                    (16)
#define CRS_CFGR_FELIM_MASK                     (0xFFU << CRS_CFGR_FELIM_SHIFT)
#define CRS_CFGR_FELIM(x)                       (((uint32_t)(((uint32_t)(x)) << CRS_CFGR_FELIM_SHIFT)) & CRS_CFGR_FELIM_MASK)

#define CRS_CFGR_RELOAD_SHIFT                   (0)
#define CRS_CFGR_RELOAD_MASK                    (0xFFFFU << CRS_CFGR_RELOAD_SHIFT)
#define CRS_CFGR_RELOAD(x)                      (((uint32_t)(((uint32_t)(x)) << CRS_CFGR_RELOAD_SHIFT)) & CRS_CFGR_RELOAD_MASK)

/*!
 * @brief CRS_lSR Register Bit Definition
 */

#define CRS_lSR_FECAP_SHIFT                     (16)
#define CRS_lSR_FECAP_MASK                      (0xFFFFU << CRS_lSR_FECAP_SHIFT)
#define CRS_lSR_FECAP(x)                        (((uint32_t)(((uint32_t)(x)) << CRS_lSR_FECAP_SHIFT)) & CRS_lSR_FECAP_MASK)

#define CRS_lSR_FEDIR_SHIFT                     (15)
#define CRS_lSR_FEDIR_MASK                      (0x01U << CRS_lSR_FEDIR_SHIFT)
#define CRS_lSR_FEDIR(x)                        (((uint32_t)(((uint32_t)(x)) << CRS_lSR_FEDIR_SHIFT)) & CRS_lSR_FEDIR_MASK)

#define CRS_lSR_TRIMOVF_SHIFT                   (10)
#define CRS_lSR_TRIMOVF_MASK                    (0x01U << CRS_lSR_TRIMOVF_SHIFT)
#define CRS_lSR_TRIMOVF(x)                      (((uint32_t)(((uint32_t)(x)) << CRS_lSR_TRIMOVF_SHIFT)) & CRS_lSR_TRIMOVF_MASK)

#define CRS_lSR_SYNCMISS_SHIFT                  (9)
#define CRS_lSR_SYNCMISS_MASK                   (0x01U << CRS_lSR_SYNCMISS_SHIFT)
#define CRS_lSR_SYNCMISS(x)                     (((uint32_t)(((uint32_t)(x)) << CRS_lSR_SYNCMISS_SHIFT)) & CRS_lSR_SYNCMISS_MASK)

#define CRS_lSR_SYNCERR_SHIFT                   (8)
#define CRS_lSR_SYNCERR_MASK                    (0x01U << CRS_lSR_SYNCERR_SHIFT)
#define CRS_lSR_SYNCERR(x)                      (((uint32_t)(((uint32_t)(x)) << CRS_lSR_SYNCERR_SHIFT)) & CRS_lSR_SYNCERR_MASK)

#define CRS_lSR_ESYNCF_SHIFT                    (3)
#define CRS_lSR_ESYNCF_MASK                     (0x01U << CRS_lSR_ESYNCF_SHIFT)
#define CRS_lSR_ESYNCF(x)                       (((uint32_t)(((uint32_t)(x)) << CRS_lSR_ESYNCF_SHIFT)) & CRS_lSR_ESYNCF_MASK)

#define CRS_lSR_ERRF_SHIFT                      (2)
#define CRS_lSR_ERRF_MASK                       (0x01U << CRS_lSR_ERRF_SHIFT)
#define CRS_lSR_ERRF(x)                         (((uint32_t)(((uint32_t)(x)) << CRS_lSR_ERRF_SHIFT)) & CRS_lSR_ERRF_MASK)

#define CRS_lSR_SYNCWARNF_SHIFT                 (1)
#define CRS_lSR_SYNCWARNF_MASK                  (0x01U << CRS_lSR_SYNCWARNF_SHIFT)
#define CRS_lSR_SYNCWARNF(x)                    (((uint32_t)(((uint32_t)(x)) << CRS_lSR_SYNCWARNF_SHIFT)) & CRS_lSR_SYNCWARNF_MASK)

#define CRS_lSR_SYNCOKF_SHIFT                   (0)
#define CRS_lSR_SYNCOKF_MASK                    (0x01U << CRS_lSR_SYNCOKF_SHIFT)
#define CRS_lSR_SYNCOKF(x)                      (((uint32_t)(((uint32_t)(x)) << CRS_lSR_SYNCOKF_SHIFT)) & CRS_lSR_SYNCOKF_MASK)

/*!
 * @brief CRS_lCR Register Bit Definition
 */

#define CRS_lCR_ESYNCC_SHIFT                    (3)
#define CRS_lCR_ESYNCC_MASK                     (0x01U << CRS_lCR_ESYNCC_SHIFT)
#define CRS_lCR_ESYNCC(x)                       (((uint32_t)(((uint32_t)(x)) << CRS_lCR_ESYNCC_SHIFT)) & CRS_lCR_ESYNCC_MASK)

#define CRS_lCR_ERRC_SHIFT                      (2)
#define CRS_lCR_ERRC_MASK                       (0x01U << CRS_lCR_ERRC_SHIFT)
#define CRS_lCR_ERRC(x)                         (((uint32_t)(((uint32_t)(x)) << CRS_lCR_ERRC_SHIFT)) & CRS_lCR_ERRC_MASK)

#define CRS_lCR_SYNCWARNC_SHIFT                 (1)
#define CRS_lCR_SYNCWARNC_MASK                  (0x01U << CRS_lCR_SYNCWARNC_SHIFT)
#define CRS_lCR_SYNCWARNC(x)                    (((uint32_t)(((uint32_t)(x)) << CRS_lCR_SYNCWARNC_SHIFT)) & CRS_lCR_SYNCWARNC_MASK)

#define CRS_lCR_SYNCOKC_SHIFT                   (0)
#define CRS_lCR_SYNCOKC_MASK                    (0x01U << CRS_lCR_SYNCOKC_SHIFT)
#define CRS_lCR_SYNCOKC(x)                      (((uint32_t)(((uint32_t)(x)) << CRS_lCR_SYNCOKC_SHIFT)) & CRS_lCR_SYNCOKC_MASK)

/*!
 * @}
 */ /* end of group CRS_Register_Masks */
/******************************************************************************
 * CRS Instance
******************************************************************************/
#define CRS                             ((CRS_Type*)CRS_BASE)

/*!
 * @}
 */ /* end of group CRS_Peripheral_Access_Layer */



/*!
 * @addtogroup GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * GPIO Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CRL;                                                            ///< Port configuration low register              offset: 0x00
    __IO uint32_t CRH;                                                            ///< Port configuration high register             offset: 0x04
    __IO uint32_t IDR;                                                            ///< Port input data register                     offset: 0x08
    __IO uint32_t ODR;                                                            ///< Port output data register                    offset: 0x0C
    __IO uint32_t BSRR;                                                           ///< Port set/clear register                      offset: 0x10
    __IO uint32_t BRR;                                                            ///< Port bit clear register                      offset: 0x14
    __IO uint32_t LCKR;                                                           ///< Port configuration lock register             offset: 0x18
    __IO uint32_t DCR;                                                            ///< Port output open drain control register      offset: 0x1C
    __IO uint32_t AFRL;                                                           ///< Port multiplexing function low register      offset: 0x20
    __IO uint32_t AFRH;                                                           ///< Port multiplexing function high register     offset: 0x24
} GPIO_Type;

/*******************************************************************************
 * GPIO Type
 ******************************************************************************/

/*!
 * @addtogroup GPIO_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief GPIO_CRL Register Bit Definition
 */

#define GPIO_CRL_CNF7_SHIFT                     (30)
#define GPIO_CRL_CNF7_MASK                      (0x3U << GPIO_CRL_CNF7_SHIFT)
#define GPIO_CRL_CNF7(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_CNF7_SHIFT)) & GPIO_CRL_CNF7_MASK)

#define GPIO_CRL_CNF6_SHIFT                     (26)
#define GPIO_CRL_CNF6_MASK                      (0x3U << GPIO_CRL_CNF6_SHIFT)
#define GPIO_CRL_CNF6(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_CNF6_SHIFT)) & GPIO_CRL_CNF6_MASK)

#define GPIO_CRL_CNF5_SHIFT                     (22)
#define GPIO_CRL_CNF5_MASK                      (0x3U << GPIO_CRL_CNF5_SHIFT)
#define GPIO_CRL_CNF5(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_CNF5_SHIFT)) & GPIO_CRL_CNF5_MASK)

#define GPIO_CRL_CNF4_SHIFT                     (18)
#define GPIO_CRL_CNF4_MASK                      (0x3U << GPIO_CRL_CNF4_SHIFT)
#define GPIO_CRL_CNF4(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_CNF4_SHIFT)) & GPIO_CRL_CNF4_MASK)

#define GPIO_CRL_CNF3_SHIFT                     (14)
#define GPIO_CRL_CNF3_MASK                      (0x3U << GPIO_CRL_CNF3_SHIFT)
#define GPIO_CRL_CNF3(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_CNF3_SHIFT)) & GPIO_CRL_CNF3_MASK)

#define GPIO_CRL_CNF2_SHIFT                     (10)
#define GPIO_CRL_CNF2_MASK                      (0x3U << GPIO_CRL_CNF2_SHIFT)
#define GPIO_CRL_CNF2(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_CNF2_SHIFT)) & GPIO_CRL_CNF2_MASK)

#define GPIO_CRL_CNF1_SHIFT                     (6)
#define GPIO_CRL_CNF1_MASK                      (0x3U << GPIO_CRL_CNF1_SHIFT)
#define GPIO_CRL_CNF1(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_CNF1_SHIFT)) & GPIO_CRL_CNF1_MASK)

#define GPIO_CRL_CNF0_SHIFT                     (2)
#define GPIO_CRL_CNF0_MASK                      (0x3U << GPIO_CRL_CNF0_SHIFT)
#define GPIO_CRL_CNF0(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_CNF0_SHIFT)) & GPIO_CRL_CNF0_MASK)

#define GPIO_CRL_MODE7_SHIFT                    (28)
#define GPIO_CRL_MODE7_MASK                     (0x3U << GPIO_CRL_MODE7_SHIFT)
#define GPIO_CRL_MODE7(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_MODE7_SHIFT)) & GPIO_CRL_MODE7_MASK)

#define GPIO_CRL_MODE6_SHIFT                    (24)
#define GPIO_CRL_MODE6_MASK                     (0x3U << GPIO_CRL_MODE6_SHIFT)
#define GPIO_CRL_MODE6(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_MODE6_SHIFT)) & GPIO_CRL_MODE6_MASK)

#define GPIO_CRL_MODE5_SHIFT                    (20)
#define GPIO_CRL_MODE5_MASK                     (0x3U << GPIO_CRL_MODE5_SHIFT)
#define GPIO_CRL_MODE5(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_MODE5_SHIFT)) & GPIO_CRL_MODE5_MASK)

#define GPIO_CRL_MODE4_SHIFT                    (16)
#define GPIO_CRL_MODE4_MASK                     (0x3U << GPIO_CRL_MODE4_SHIFT)
#define GPIO_CRL_MODE4(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_MODE4_SHIFT)) & GPIO_CRL_MODE4_MASK)

#define GPIO_CRL_MODE3_SHIFT                    (12)
#define GPIO_CRL_MODE3_MASK                     (0x3U << GPIO_CRL_MODE3_SHIFT)
#define GPIO_CRL_MODE3(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_MODE3_SHIFT)) & GPIO_CRL_MODE3_MASK)

#define GPIO_CRL_MODE2_SHIFT                    (8)
#define GPIO_CRL_MODE2_MASK                     (0x3U << GPIO_CRL_MODE2_SHIFT)
#define GPIO_CRL_MODE2(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_MODE2_SHIFT)) & GPIO_CRL_MODE2_MASK)

#define GPIO_CRL_MODE1_SHIFT                    (4)
#define GPIO_CRL_MODE1_MASK                     (0x3U << GPIO_CRL_MODE1_SHIFT)
#define GPIO_CRL_MODE1(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_MODE1_SHIFT)) & GPIO_CRL_MODE1_MASK)

#define GPIO_CRL_MODE0_SHIFT                    (0)
#define GPIO_CRL_MODE0_MASK                     (0x3U << GPIO_CRL_MODE0_SHIFT)
#define GPIO_CRL_MODE0(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRL_MODE0_SHIFT)) & GPIO_CRL_MODE0_MASK)

/*!
 * @brief GPIO_CRH Register Bit Definition
 */

#define GPIO_CRH_CNF15_SHIFT                    (30)
#define GPIO_CRH_CNF15_MASK                     (0x3U << GPIO_CRH_CNF15_SHIFT)
#define GPIO_CRH_CNF15(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_CNF15_SHIFT)) & GPIO_CRH_CNF15_MASK)

#define GPIO_CRH_CNF14_SHIFT                    (26)
#define GPIO_CRH_CNF14_MASK                     (0x3U << GPIO_CRH_CNF14_SHIFT)
#define GPIO_CRH_CNF14(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_CNF14_SHIFT)) & GPIO_CRH_CNF14_MASK)

#define GPIO_CRH_CNF13_SHIFT                    (22)
#define GPIO_CRH_CNF13_MASK                     (0x3U << GPIO_CRH_CNF13_SHIFT)
#define GPIO_CRH_CNF13(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_CNF13_SHIFT)) & GPIO_CRH_CNF13_MASK)

#define GPIO_CRH_CNF12_SHIFT                    (18)
#define GPIO_CRH_CNF12_MASK                     (0x3U << GPIO_CRH_CNF12_SHIFT)
#define GPIO_CRH_CNF12(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_CNF12_SHIFT)) & GPIO_CRH_CNF12_MASK)

#define GPIO_CRH_CNF11_SHIFT                    (14)
#define GPIO_CRH_CNF11_MASK                     (0x3U << GPIO_CRH_CNF11_SHIFT)
#define GPIO_CRH_CNF11(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_CNF11_SHIFT)) & GPIO_CRH_CNF11_MASK)

#define GPIO_CRH_CNF10_SHIFT                    (10)
#define GPIO_CRH_CNF10_MASK                     (0x3U << GPIO_CRH_CNF10_SHIFT)
#define GPIO_CRH_CNF10(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_CNF10_SHIFT)) & GPIO_CRH_CNF10_MASK)

#define GPIO_CRH_CNF9_SHIFT                     (6)
#define GPIO_CRH_CNF9_MASK                      (0x3U << GPIO_CRH_CNF9_SHIFT)
#define GPIO_CRH_CNF9(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_CNF9_SHIFT)) & GPIO_CRH_CNF9_MASK)

#define GPIO_CRH_CNF8_SHIFT                     (2)
#define GPIO_CRH_CNF8_MASK                      (0x3U << GPIO_CRH_CNF8_SHIFT)
#define GPIO_CRH_CNF8(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_CNF8_SHIFT)) & GPIO_CRH_CNF8_MASK)

#define GPIO_CRH_MODE15_SHIFT                   (28)
#define GPIO_CRH_MODE15_MASK                    (0x3U << GPIO_CRH_MODE15_SHIFT)
#define GPIO_CRH_MODE15(x)                      (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_MODE15_SHIFT)) & GPIO_CRH_MODE15_MASK)

#define GPIO_CRH_MODE14_SHIFT                   (24)
#define GPIO_CRH_MODE14_MASK                    (0x3U << GPIO_CRH_MODE14_SHIFT)
#define GPIO_CRH_MODE14(x)                      (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_MODE14_SHIFT)) & GPIO_CRH_MODE14_MASK)

#define GPIO_CRH_MODE13_SHIFT                   (20)
#define GPIO_CRH_MODE13_MASK                    (0x3U << GPIO_CRH_MODE13_SHIFT)
#define GPIO_CRH_MODE13(x)                      (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_MODE13_SHIFT)) & GPIO_CRH_MODE13_MASK)

#define GPIO_CRH_MODE12_SHIFT                   (16)
#define GPIO_CRH_MODE12_MASK                    (0x3U << GPIO_CRH_MODE12_SHIFT)
#define GPIO_CRH_MODE12(x)                      (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_MODE12_SHIFT)) & GPIO_CRH_MODE12_MASK)

#define GPIO_CRH_MODE11_SHIFT                   (12)
#define GPIO_CRH_MODE11_MASK                    (0x3U << GPIO_CRH_MODE11_SHIFT)
#define GPIO_CRH_MODE11(x)                      (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_MODE11_SHIFT)) & GPIO_CRH_MODE11_MASK)

#define GPIO_CRH_MODE10_SHIFT                   (8)
#define GPIO_CRH_MODE10_MASK                    (0x3U << GPIO_CRH_MODE10_SHIFT)
#define GPIO_CRH_MODE10(x)                      (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_MODE10_SHIFT)) & GPIO_CRH_MODE10_MASK)

#define GPIO_CRH_MODE9_SHIFT                    (4)
#define GPIO_CRH_MODE9_MASK                     (0x3U << GPIO_CRH_MODE9_SHIFT)
#define GPIO_CRH_MODE9(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_MODE9_SHIFT)) & GPIO_CRH_MODE9_MASK)

#define GPIO_CRH_MODE8_SHIFT                    (0)
#define GPIO_CRH_MODE8_MASK                     (0x3U << GPIO_CRH_MODE8_SHIFT)
#define GPIO_CRH_MODE8(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_CRH_MODE8_SHIFT)) & GPIO_CRH_MODE8_MASK)

/*!
 * @brief GPIO_IDR Register Bit Definition
 */

#define GPIO_IDR_IDRy_SHIFT                     (0)
#define GPIO_IDR_IDRy_MASK                      (0xFFFFU << GPIO_IDR_IDRy_SHIFT)
#define GPIO_IDR_IDRy(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_IDR_IDRy_SHIFT)) & GPIO_IDR_IDRy_MASK)

/*!
 * @brief GPIO_ODR Register Bit Definition
 */

#define GPIO_ODR_ODRY_SHIFT                     (0)
#define GPIO_ODR_ODRY_MASK                      (0xFFFFU << GPIO_ODR_ODRY_SHIFT)
#define GPIO_ODR_ODRY(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_ODR_ODRY_SHIFT)) & GPIO_ODR_ODRY_MASK)

/*!
 * @brief GPIO_BSRR Register Bit Definition
 */

#define GPIO_BSRR_BRY_SHIFT                     (16)
#define GPIO_BSRR_BRY_MASK                      (0xFFFFU << GPIO_BSRR_BRY_SHIFT)
#define GPIO_BSRR_BRY(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_BSRR_BRY_SHIFT)) & GPIO_BSRR_BRY_MASK)

#define GPIO_BSRR_BSY_SHIFT                     (0)
#define GPIO_BSRR_BSY_MASK                      (0xFFFFU << GPIO_BSRR_BSY_SHIFT)
#define GPIO_BSRR_BSY(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_BSRR_BSY_SHIFT)) & GPIO_BSRR_BSY_MASK)

/*!
 * @brief GPIO_BRR Register Bit Definition
 */

#define GPIO_BRR_BRY_SHIFT                      (0)
#define GPIO_BRR_BRY_MASK                       (0xFFFFU << GPIO_BRR_BRY_SHIFT)
#define GPIO_BRR_BRY(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_BRR_BRY_SHIFT)) & GPIO_BRR_BRY_MASK)

/*!
 * @brief GPIO_LCKR Register Bit Definition
 */

#define GPIO_LCKR_LCKK_SHIFT                    (16)
#define GPIO_LCKR_LCKK_MASK                     (0x01U << GPIO_LCKR_LCKK_SHIFT)
#define GPIO_LCKR_LCKK(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_LCKR_LCKK_SHIFT)) & GPIO_LCKR_LCKK_MASK)

#define GPIO_LCKR_LCK_SHIFT                     (0)
#define GPIO_LCKR_LCK_MASK                      (0xFFFFU << GPIO_LCKR_LCK_SHIFT)
#define GPIO_LCKR_LCK(x)                        (((uint32_t)(((uint32_t)(x)) << GPIO_LCKR_LCK_SHIFT)) & GPIO_LCKR_LCK_MASK)

/*!
 * @brief GPIO_DCR Register Bit Definition
 */

#define GPIO_DCR_PX15PX1_SHIFT                 (2)
#define GPIO_DCR_PX15PX1_MASK                  (0x3FFFFFFFU << GPIO_DCR_PX15PX1_SHIFT)
#define GPIO_DCR_PX15PX1(x)                    (((uint32_t)(((uint32_t)(x)) << GPIO_DCR_PX15PX1_SHIFT)) & GPIO_DCR_PX15PX1_MASK)

#define GPIO_DCR_PX0_SHIFT                      (0)
#define GPIO_DCR_PX0_MASK                       (0x3U << GPIO_DCR_PX0_SHIFT)
#define GPIO_DCR_PX0(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_DCR_PX0_SHIFT)) & GPIO_DCR_PX0_MASK)

/*!
 * @brief GPIO_AFRL Register Bit Definition
 */

#define GPIO_AFRL_AFRY_SHIFT                    (0)
#define GPIO_AFRL_AFRY_MASK                     (0xFFFFFFFFU << GPIO_AFRL_AFRY_SHIFT)
#define GPIO_AFRL_AFRY(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_AFRL_AFRY_SHIFT)) & GPIO_AFRL_AFRY_MASK)

/*!
 * @brief GPIO_AFRH Register Bit Definition
 */

#define GPIO_AFRH_AFRY_SHIFT                    (0)
#define GPIO_AFRH_AFRY_MASK                     (0xFFFFFFFFU << GPIO_AFRH_AFRY_SHIFT)
#define GPIO_AFRH_AFRY(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_AFRH_AFRY_SHIFT)) & GPIO_AFRH_AFRY_MASK)

/*!
 * @}
 */ /* end of group GPIO_Register_Masks */
/******************************************************************************
 * GPIO Instance
******************************************************************************/
#define GPIOA                               ((GPIO_Type*)GPIOA_BASE)
#define GPIOB                               ((GPIO_Type*)GPIOB_BASE)
#define GPIOC                               ((GPIO_Type*)GPIOC_BASE)
#define GPIOD                               ((GPIO_Type*)GPIOD_BASE)
#define GPIOE                               ((GPIO_Type*)GPIOE_BASE)
#define GPIOF                               ((GPIO_Type*)GPIOF_BASE)
#define GPIOG                               ((GPIO_Type*)GPIOG_BASE)
#define GPIOH                               ((GPIO_Type*)GPIOH_BASE)

/*!
 * @}
 */ /* end of group GPIO_Peripheral_Access_Layer */



/*!
 * @addtogroup TIM1_Peripheral_Access_Layer TIM1 Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * TIM1 Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CR1;                                                            ///< Control register 1                           offset: 0x00
    __IO uint32_t CR2;                                                            ///< Control register 2                           offset: 0x04
    __IO uint32_t SMCR;                                                           ///< Slave mode control register                  offset: 0x08
    __IO uint32_t DIER;                                                           ///< DMA/interrupt enable register                offset: 0x0C
    __IO uint32_t SR;                                                             ///< Status register                              offset: 0x10
    __IO uint32_t EGR;                                                            ///< Event generation register                    offset: 0x14
    __IO uint32_t CCMR1;                                                          ///< Capture/compare mode register 1              offset: 0x18
    __IO uint32_t CCMR2;                                                          ///< Capture/compare mode register 2              offset: 0x1C
    __IO uint32_t CCER;                                                           ///< Capture/compare enable register              offset: 0x20
    __IO uint32_t CNT;                                                            ///< Counter                                      offset: 0x24
    __IO uint32_t PSC;                                                            ///< Prescaler                                    offset: 0x28
    __IO uint32_t ARR;                                                            ///< Autoload register                            offset: 0x2C
    __IO uint32_t RCR;                                                            ///< Repeat count register                        offset: 0x30
    __IO uint32_t CCR[4];
//    __IO uint32_t CCR1;                                                           ///< Capture/compare register 1                   offset: 0x34
//    __IO uint32_t CCR2;                                                           ///< Capture/compare register 2                   offset: 0x38
//    __IO uint32_t CCR3;                                                           ///< Capture/compare register 3                   offset: 0x3C
//    __IO uint32_t CCR4;                                                           ///< Capture/compare register 4                   offset: 0x40
    __IO uint32_t BDTR;                                                           ///< Brake and dead zone registers                offset: 0x44
    __IO uint32_t DCR;                                                            ///< DMA control register                         offset: 0x48
    __IO uint32_t DMAR;                                                           ///< DMA address in continuous mode               offset: 0x4C
    __IO uint32_t Reserved7[1];                                                   ///< Reserved
    __IO uint32_t CCMR3;                                                          ///< Capture/compare mode register 3              offset: 0x54
    __IO uint32_t CCR5;                                                           ///< Capture/compare register 5                   offset: 0x58
    __IO uint32_t PDER;                                                           ///< PWM phase shift/DMA repeat update request enable register offset: 0x5C
    __IO uint32_t CCRFALL[5];                                                     ///< PWM phase shift down counting capture/compare register offset: 0x60
} TIM1_Type;

/*******************************************************************************
 * TIM1 Type
 ******************************************************************************/

/*!
 * @addtogroup TIM1_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief TIM1_CR1 Register Bit Definition
 */

#define TIM1_CR1_CKD_SHIFT                      (8)
#define TIM1_CR1_CKD_MASK                       (0x3U << TIM1_CR1_CKD_SHIFT)
#define TIM1_CR1_CKD(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_CR1_CKD_SHIFT)) & TIM1_CR1_CKD_MASK)

#define TIM1_CR1_APRE_SHIFT                     (7)
#define TIM1_CR1_APRE_MASK                      (0x01U << TIM1_CR1_APRE_SHIFT)
#define TIM1_CR1_APRE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_CR1_APRE_SHIFT)) & TIM1_CR1_APRE_MASK)

#define TIM1_CR1_CMS_SHIFT                      (5)
#define TIM1_CR1_CMS_MASK                       (0x3U << TIM1_CR1_CMS_SHIFT)
#define TIM1_CR1_CMS(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_CR1_CMS_SHIFT)) & TIM1_CR1_CMS_MASK)

#define TIM1_CR1_DIR_SHIFT                      (4)
#define TIM1_CR1_DIR_MASK                       (0x01U << TIM1_CR1_DIR_SHIFT)
#define TIM1_CR1_DIR(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_CR1_DIR_SHIFT)) & TIM1_CR1_DIR_MASK)

#define TIM1_CR1_OPM_SHIFT                      (3)
#define TIM1_CR1_OPM_MASK                       (0x01U << TIM1_CR1_OPM_SHIFT)
#define TIM1_CR1_OPM(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_CR1_OPM_SHIFT)) & TIM1_CR1_OPM_MASK)

#define TIM1_CR1_URS_SHIFT                      (2)
#define TIM1_CR1_URS_MASK                       (0x01U << TIM1_CR1_URS_SHIFT)
#define TIM1_CR1_URS(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_CR1_URS_SHIFT)) & TIM1_CR1_URS_MASK)

#define TIM1_CR1_UDIS_SHIFT                     (1)
#define TIM1_CR1_UDIS_MASK                      (0x01U << TIM1_CR1_UDIS_SHIFT)
#define TIM1_CR1_UDIS(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_CR1_UDIS_SHIFT)) & TIM1_CR1_UDIS_MASK)

#define TIM1_CR1_CEN_SHIFT                      (0)
#define TIM1_CR1_CEN_MASK                       (0x01U << TIM1_CR1_CEN_SHIFT)
#define TIM1_CR1_CEN(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_CR1_CEN_SHIFT)) & TIM1_CR1_CEN_MASK)

/*!
 * @brief TIM1_CR2 Register Bit Definition
 */

#define TIM1_CR2_OIS4_SHIFT                     (14)
#define TIM1_CR2_OIS4_MASK                      (0x01U << TIM1_CR2_OIS4_SHIFT)
#define TIM1_CR2_OIS4(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_CR2_OIS4_SHIFT)) & TIM1_CR2_OIS4_MASK)

#define TIM1_CR2_OIS3N_SHIFT                    (13)
#define TIM1_CR2_OIS3N_MASK                     (0x01U << TIM1_CR2_OIS3N_SHIFT)
#define TIM1_CR2_OIS3N(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CR2_OIS3N_SHIFT)) & TIM1_CR2_OIS3N_MASK)

#define TIM1_CR2_OIS3_SHIFT                     (12)
#define TIM1_CR2_OIS3_MASK                      (0x01U << TIM1_CR2_OIS3_SHIFT)
#define TIM1_CR2_OIS3(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_CR2_OIS3_SHIFT)) & TIM1_CR2_OIS3_MASK)

#define TIM1_CR2_OIS2N_SHIFT                    (11)
#define TIM1_CR2_OIS2N_MASK                     (0x01U << TIM1_CR2_OIS2N_SHIFT)
#define TIM1_CR2_OIS2N(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CR2_OIS2N_SHIFT)) & TIM1_CR2_OIS2N_MASK)

#define TIM1_CR2_OIS2_SHIFT                     (10)
#define TIM1_CR2_OIS2_MASK                      (0x01U << TIM1_CR2_OIS2_SHIFT)
#define TIM1_CR2_OIS2(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_CR2_OIS2_SHIFT)) & TIM1_CR2_OIS2_MASK)

#define TIM1_CR2_OIS1N_SHIFT                    (9)
#define TIM1_CR2_OIS1N_MASK                     (0x01U << TIM1_CR2_OIS1N_SHIFT)
#define TIM1_CR2_OIS1N(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CR2_OIS1N_SHIFT)) & TIM1_CR2_OIS1N_MASK)

#define TIM1_CR2_OIS1_SHIFT                     (8)
#define TIM1_CR2_OIS1_MASK                      (0x01U << TIM1_CR2_OIS1_SHIFT)
#define TIM1_CR2_OIS1(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_CR2_OIS1_SHIFT)) & TIM1_CR2_OIS1_MASK)

#define TIM1_CR2_TI1S_SHIFT                     (7)
#define TIM1_CR2_TI1S_MASK                      (0x01U << TIM1_CR2_TI1S_SHIFT)
#define TIM1_CR2_TI1S(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_CR2_TI1S_SHIFT)) & TIM1_CR2_TI1S_MASK)

#define TIM1_CR2_MMS_SHIFT                      (4)
#define TIM1_CR2_MMS_MASK                       (0x7U << TIM1_CR2_MMS_SHIFT)
#define TIM1_CR2_MMS(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_CR2_MMS_SHIFT)) & TIM1_CR2_MMS_MASK)

#define TIM1_CR2_CCDS_SHIFT                     (3)
#define TIM1_CR2_CCDS_MASK                      (0x01U << TIM1_CR2_CCDS_SHIFT)
#define TIM1_CR2_CCDS(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_CR2_CCDS_SHIFT)) & TIM1_CR2_CCDS_MASK)

#define TIM1_CR2_CCUS_SHIFT                     (2)
#define TIM1_CR2_CCUS_MASK                      (0x01U << TIM1_CR2_CCUS_SHIFT)
#define TIM1_CR2_CCUS(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_CR2_CCUS_SHIFT)) & TIM1_CR2_CCUS_MASK)

#define TIM1_CR2_CCPC_SHIFT                     (0)
#define TIM1_CR2_CCPC_MASK                      (0x01U << TIM1_CR2_CCPC_SHIFT)
#define TIM1_CR2_CCPC(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_CR2_CCPC_SHIFT)) & TIM1_CR2_CCPC_MASK)

/*!
 * @brief TIM1_SMCR Register Bit Definition
 */

#define TIM1_SMCR_ETP_SHIFT                     (15)
#define TIM1_SMCR_ETP_MASK                      (0x01U << TIM1_SMCR_ETP_SHIFT)
#define TIM1_SMCR_ETP(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SMCR_ETP_SHIFT)) & TIM1_SMCR_ETP_MASK)

#define TIM1_SMCR_ECE_SHIFT                     (14)
#define TIM1_SMCR_ECE_MASK                      (0x01U << TIM1_SMCR_ECE_SHIFT)
#define TIM1_SMCR_ECE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SMCR_ECE_SHIFT)) & TIM1_SMCR_ECE_MASK)

#define TIM1_SMCR_ETPS_SHIFT                    (12)
#define TIM1_SMCR_ETPS_MASK                     (0x3U << TIM1_SMCR_ETPS_SHIFT)
#define TIM1_SMCR_ETPS(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_SMCR_ETPS_SHIFT)) & TIM1_SMCR_ETPS_MASK)

#define TIM1_SMCR_ETF_SHIFT                     (8)
#define TIM1_SMCR_ETF_MASK                      (0xFU << TIM1_SMCR_ETF_SHIFT)
#define TIM1_SMCR_ETF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SMCR_ETF_SHIFT)) & TIM1_SMCR_ETF_MASK)

#define TIM1_SMCR_MSM_SHIFT                     (7)
#define TIM1_SMCR_MSM_MASK                      (0x01U << TIM1_SMCR_MSM_SHIFT)
#define TIM1_SMCR_MSM(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SMCR_MSM_SHIFT)) & TIM1_SMCR_MSM_MASK)

#define TIM1_SMCR_TS_SHIFT                      (4)
#define TIM1_SMCR_TS_MASK                       (0x7U << TIM1_SMCR_TS_SHIFT)
#define TIM1_SMCR_TS(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_SMCR_TS_SHIFT)) & TIM1_SMCR_TS_MASK)

#define TIM1_SMCR_OCCS_SHIFT                    (3)
#define TIM1_SMCR_OCCS_MASK                     (0x01U << TIM1_SMCR_OCCS_SHIFT)
#define TIM1_SMCR_OCCS(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_SMCR_OCCS_SHIFT)) & TIM1_SMCR_OCCS_MASK)

#define TIM1_SMCR_SMS_SHIFT                     (0)
#define TIM1_SMCR_SMS_MASK                      (0x7U << TIM1_SMCR_SMS_SHIFT)
#define TIM1_SMCR_SMS(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SMCR_SMS_SHIFT)) & TIM1_SMCR_SMS_MASK)

/*!
 * @brief TIM1_DIER Register Bit Definition
 */

#define TIM1_DIER_CC5DE_SHIFT                   (17)
#define TIM1_DIER_CC5DE_MASK                    (0x01U << TIM1_DIER_CC5DE_SHIFT)
#define TIM1_DIER_CC5DE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_CC5DE_SHIFT)) & TIM1_DIER_CC5DE_MASK)

#define TIM1_DIER_CC5IE_SHIFT                   (16)
#define TIM1_DIER_CC5IE_MASK                    (0x01U << TIM1_DIER_CC5IE_SHIFT)
#define TIM1_DIER_CC5IE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_CC5IE_SHIFT)) & TIM1_DIER_CC5IE_MASK)

#define TIM1_DIER_TDE_SHIFT                     (14)
#define TIM1_DIER_TDE_MASK                      (0x01U << TIM1_DIER_TDE_SHIFT)
#define TIM1_DIER_TDE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_TDE_SHIFT)) & TIM1_DIER_TDE_MASK)

#define TIM1_DIER_COMDE_SHIFT                   (13)
#define TIM1_DIER_COMDE_MASK                    (0x01U << TIM1_DIER_COMDE_SHIFT)
#define TIM1_DIER_COMDE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_COMDE_SHIFT)) & TIM1_DIER_COMDE_MASK)

#define TIM1_DIER_CC4DE_SHIFT                   (12)
#define TIM1_DIER_CC4DE_MASK                    (0x01U << TIM1_DIER_CC4DE_SHIFT)
#define TIM1_DIER_CC4DE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_CC4DE_SHIFT)) & TIM1_DIER_CC4DE_MASK)

#define TIM1_DIER_CC3DE_SHIFT                   (11)
#define TIM1_DIER_CC3DE_MASK                    (0x01U << TIM1_DIER_CC3DE_SHIFT)
#define TIM1_DIER_CC3DE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_CC3DE_SHIFT)) & TIM1_DIER_CC3DE_MASK)

#define TIM1_DIER_CC2DE_SHIFT                   (10)
#define TIM1_DIER_CC2DE_MASK                    (0x01U << TIM1_DIER_CC2DE_SHIFT)
#define TIM1_DIER_CC2DE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_CC2DE_SHIFT)) & TIM1_DIER_CC2DE_MASK)

#define TIM1_DIER_CC1DE_SHIFT                   (9)
#define TIM1_DIER_CC1DE_MASK                    (0x01U << TIM1_DIER_CC1DE_SHIFT)
#define TIM1_DIER_CC1DE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_CC1DE_SHIFT)) & TIM1_DIER_CC1DE_MASK)

#define TIM1_DIER_UDE_SHIFT                     (8)
#define TIM1_DIER_UDE_MASK                      (0x01U << TIM1_DIER_UDE_SHIFT)
#define TIM1_DIER_UDE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_UDE_SHIFT)) & TIM1_DIER_UDE_MASK)

#define TIM1_DIER_BIE_SHIFT                     (7)
#define TIM1_DIER_BIE_MASK                      (0x01U << TIM1_DIER_BIE_SHIFT)
#define TIM1_DIER_BIE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_BIE_SHIFT)) & TIM1_DIER_BIE_MASK)

#define TIM1_DIER_TIE_SHIFT                     (6)
#define TIM1_DIER_TIE_MASK                      (0x01U << TIM1_DIER_TIE_SHIFT)
#define TIM1_DIER_TIE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_TIE_SHIFT)) & TIM1_DIER_TIE_MASK)

#define TIM1_DIER_COMIE_SHIFT                   (5)
#define TIM1_DIER_COMIE_MASK                    (0x01U << TIM1_DIER_COMIE_SHIFT)
#define TIM1_DIER_COMIE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_COMIE_SHIFT)) & TIM1_DIER_COMIE_MASK)

#define TIM1_DIER_CC4IE_SHIFT                   (4)
#define TIM1_DIER_CC4IE_MASK                    (0x01U << TIM1_DIER_CC4IE_SHIFT)
#define TIM1_DIER_CC4IE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_CC4IE_SHIFT)) & TIM1_DIER_CC4IE_MASK)

#define TIM1_DIER_CC3IE_SHIFT                   (3)
#define TIM1_DIER_CC3IE_MASK                    (0x01U << TIM1_DIER_CC3IE_SHIFT)
#define TIM1_DIER_CC3IE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_CC3IE_SHIFT)) & TIM1_DIER_CC3IE_MASK)

#define TIM1_DIER_CC2IE_SHIFT                   (2)
#define TIM1_DIER_CC2IE_MASK                    (0x01U << TIM1_DIER_CC2IE_SHIFT)
#define TIM1_DIER_CC2IE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_CC2IE_SHIFT)) & TIM1_DIER_CC2IE_MASK)

#define TIM1_DIER_CC1IE_SHIFT                   (1)
#define TIM1_DIER_CC1IE_MASK                    (0x01U << TIM1_DIER_CC1IE_SHIFT)
#define TIM1_DIER_CC1IE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_CC1IE_SHIFT)) & TIM1_DIER_CC1IE_MASK)

#define TIM1_DIER_UIE_SHIFT                     (0)
#define TIM1_DIER_UIE_MASK                      (0x01U << TIM1_DIER_UIE_SHIFT)
#define TIM1_DIER_UIE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_DIER_UIE_SHIFT)) & TIM1_DIER_UIE_MASK)

/*!
 * @brief TIM1_SR Register Bit Definition
 */

#define TIM1_SR_CC5IF_SHIFT                     (16)
#define TIM1_SR_CC5IF_MASK                      (0x01U << TIM1_SR_CC5IF_SHIFT)
#define TIM1_SR_CC5IF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SR_CC5IF_SHIFT)) & TIM1_SR_CC5IF_MASK)

#define TIM1_SR_CC4OF_SHIFT                     (12)
#define TIM1_SR_CC4OF_MASK                      (0x01U << TIM1_SR_CC4OF_SHIFT)
#define TIM1_SR_CC4OF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SR_CC4OF_SHIFT)) & TIM1_SR_CC4OF_MASK)

#define TIM1_SR_CC3OF_SHIFT                     (11)
#define TIM1_SR_CC3OF_MASK                      (0x01U << TIM1_SR_CC3OF_SHIFT)
#define TIM1_SR_CC3OF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SR_CC3OF_SHIFT)) & TIM1_SR_CC3OF_MASK)

#define TIM1_SR_CC2OF_SHIFT                     (10)
#define TIM1_SR_CC2OF_MASK                      (0x01U << TIM1_SR_CC2OF_SHIFT)
#define TIM1_SR_CC2OF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SR_CC2OF_SHIFT)) & TIM1_SR_CC2OF_MASK)

#define TIM1_SR_CC1OF_SHIFT                     (9)
#define TIM1_SR_CC1OF_MASK                      (0x01U << TIM1_SR_CC1OF_SHIFT)
#define TIM1_SR_CC1OF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SR_CC1OF_SHIFT)) & TIM1_SR_CC1OF_MASK)

#define TIM1_SR_BIF_SHIFT                       (7)
#define TIM1_SR_BIF_MASK                        (0x01U << TIM1_SR_BIF_SHIFT)
#define TIM1_SR_BIF(x)                          (((uint32_t)(((uint32_t)(x)) << TIM1_SR_BIF_SHIFT)) & TIM1_SR_BIF_MASK)

#define TIM1_SR_TIF_SHIFT                       (6)
#define TIM1_SR_TIF_MASK                        (0x01U << TIM1_SR_TIF_SHIFT)
#define TIM1_SR_TIF(x)                          (((uint32_t)(((uint32_t)(x)) << TIM1_SR_TIF_SHIFT)) & TIM1_SR_TIF_MASK)

#define TIM1_SR_COMIF_SHIFT                     (5)
#define TIM1_SR_COMIF_MASK                      (0x01U << TIM1_SR_COMIF_SHIFT)
#define TIM1_SR_COMIF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SR_COMIF_SHIFT)) & TIM1_SR_COMIF_MASK)

#define TIM1_SR_CC4IF_SHIFT                     (4)
#define TIM1_SR_CC4IF_MASK                      (0x01U << TIM1_SR_CC4IF_SHIFT)
#define TIM1_SR_CC4IF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SR_CC4IF_SHIFT)) & TIM1_SR_CC4IF_MASK)

#define TIM1_SR_CC3IF_SHIFT                     (3)
#define TIM1_SR_CC3IF_MASK                      (0x01U << TIM1_SR_CC3IF_SHIFT)
#define TIM1_SR_CC3IF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SR_CC3IF_SHIFT)) & TIM1_SR_CC3IF_MASK)

#define TIM1_SR_CC2IF_SHIFT                     (2)
#define TIM1_SR_CC2IF_MASK                      (0x01U << TIM1_SR_CC2IF_SHIFT)
#define TIM1_SR_CC2IF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SR_CC2IF_SHIFT)) & TIM1_SR_CC2IF_MASK)

#define TIM1_SR_CC1IF_SHIFT                     (1)
#define TIM1_SR_CC1IF_MASK                      (0x01U << TIM1_SR_CC1IF_SHIFT)
#define TIM1_SR_CC1IF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_SR_CC1IF_SHIFT)) & TIM1_SR_CC1IF_MASK)

#define TIM1_SR_UIF_SHIFT                       (0)
#define TIM1_SR_UIF_MASK                        (0x01U << TIM1_SR_UIF_SHIFT)
#define TIM1_SR_UIF(x)                          (((uint32_t)(((uint32_t)(x)) << TIM1_SR_UIF_SHIFT)) & TIM1_SR_UIF_MASK)

/*!
 * @brief TIM1_EGR Register Bit Definition
 */

#define TIM1_EGR_CC5G_SHIFT                     (16)
#define TIM1_EGR_CC5G_MASK                      (0x01U << TIM1_EGR_CC5G_SHIFT)
#define TIM1_EGR_CC5G(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_EGR_CC5G_SHIFT)) & TIM1_EGR_CC5G_MASK)

#define TIM1_EGR_BG_SHIFT                       (7)
#define TIM1_EGR_BG_MASK                        (0x01U << TIM1_EGR_BG_SHIFT)
#define TIM1_EGR_BG(x)                          (((uint32_t)(((uint32_t)(x)) << TIM1_EGR_BG_SHIFT)) & TIM1_EGR_BG_MASK)

#define TIM1_EGR_TG_SHIFT                       (6)
#define TIM1_EGR_TG_MASK                        (0x01U << TIM1_EGR_TG_SHIFT)
#define TIM1_EGR_TG(x)                          (((uint32_t)(((uint32_t)(x)) << TIM1_EGR_TG_SHIFT)) & TIM1_EGR_TG_MASK)

#define TIM1_EGR_COMG_SHIFT                     (5)
#define TIM1_EGR_COMG_MASK                      (0x01U << TIM1_EGR_COMG_SHIFT)
#define TIM1_EGR_COMG(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_EGR_COMG_SHIFT)) & TIM1_EGR_COMG_MASK)

#define TIM1_EGR_CC4G_SHIFT                     (4)
#define TIM1_EGR_CC4G_MASK                      (0x01U << TIM1_EGR_CC4G_SHIFT)
#define TIM1_EGR_CC4G(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_EGR_CC4G_SHIFT)) & TIM1_EGR_CC4G_MASK)

#define TIM1_EGR_CC3G_SHIFT                     (3)
#define TIM1_EGR_CC3G_MASK                      (0x01U << TIM1_EGR_CC3G_SHIFT)
#define TIM1_EGR_CC3G(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_EGR_CC3G_SHIFT)) & TIM1_EGR_CC3G_MASK)

#define TIM1_EGR_CC2G_SHIFT                     (2)
#define TIM1_EGR_CC2G_MASK                      (0x01U << TIM1_EGR_CC2G_SHIFT)
#define TIM1_EGR_CC2G(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_EGR_CC2G_SHIFT)) & TIM1_EGR_CC2G_MASK)

#define TIM1_EGR_CC1G_SHIFT                     (1)
#define TIM1_EGR_CC1G_MASK                      (0x01U << TIM1_EGR_CC1G_SHIFT)
#define TIM1_EGR_CC1G(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_EGR_CC1G_SHIFT)) & TIM1_EGR_CC1G_MASK)

#define TIM1_EGR_UG_SHIFT                       (0)
#define TIM1_EGR_UG_MASK                        (0x01U << TIM1_EGR_UG_SHIFT)
#define TIM1_EGR_UG(x)                          (((uint32_t)(((uint32_t)(x)) << TIM1_EGR_UG_SHIFT)) & TIM1_EGR_UG_MASK)

/*!
 * @brief TIM1_CCMR1 Register Bit Definition
 */

#define TIM1_CCMR1_OC2CE_SHIFT                  (15)
#define TIM1_CCMR1_OC2CE_MASK                   (0x01U << TIM1_CCMR1_OC2CE_SHIFT)
#define TIM1_CCMR1_OC2CE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_OC2CE_SHIFT)) & TIM1_CCMR1_OC2CE_MASK)

#define TIM1_CCMR1_OC2M_SHIFT                   (12)
#define TIM1_CCMR1_OC2M_MASK                    (0x7U << TIM1_CCMR1_OC2M_SHIFT)
#define TIM1_CCMR1_OC2M(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_OC2M_SHIFT)) & TIM1_CCMR1_OC2M_MASK)

#define TIM1_CCMR1_OC2PE_SHIFT                  (11)
#define TIM1_CCMR1_OC2PE_MASK                   (0x01U << TIM1_CCMR1_OC2PE_SHIFT)
#define TIM1_CCMR1_OC2PE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_OC2PE_SHIFT)) & TIM1_CCMR1_OC2PE_MASK)

#define TIM1_CCMR1_OC2FE_SHIFT                  (10)
#define TIM1_CCMR1_OC2FE_MASK                   (0x01U << TIM1_CCMR1_OC2FE_SHIFT)
#define TIM1_CCMR1_OC2FE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_OC2FE_SHIFT)) & TIM1_CCMR1_OC2FE_MASK)

#define TIM1_CCMR1_CC2S_SHIFT                   (8)
#define TIM1_CCMR1_CC2S_MASK                    (0x3U << TIM1_CCMR1_CC2S_SHIFT)
#define TIM1_CCMR1_CC2S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_CC2S_SHIFT)) & TIM1_CCMR1_CC2S_MASK)

#define TIM1_CCMR1_OC1CE_SHIFT                  (7)
#define TIM1_CCMR1_OC1CE_MASK                   (0x01U << TIM1_CCMR1_OC1CE_SHIFT)
#define TIM1_CCMR1_OC1CE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_OC1CE_SHIFT)) & TIM1_CCMR1_OC1CE_MASK)

#define TIM1_CCMR1_OC1M_SHIFT                   (4)
#define TIM1_CCMR1_OC1M_MASK                    (0x7U << TIM1_CCMR1_OC1M_SHIFT)
#define TIM1_CCMR1_OC1M(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_OC1M_SHIFT)) & TIM1_CCMR1_OC1M_MASK)

#define TIM1_CCMR1_OC1PE_SHIFT                  (3)
#define TIM1_CCMR1_OC1PE_MASK                   (0x01U << TIM1_CCMR1_OC1PE_SHIFT)
#define TIM1_CCMR1_OC1PE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_OC1PE_SHIFT)) & TIM1_CCMR1_OC1PE_MASK)

#define TIM1_CCMR1_OC1FE_SHIFT                  (2)
#define TIM1_CCMR1_OC1FE_MASK                   (0x01U << TIM1_CCMR1_OC1FE_SHIFT)
#define TIM1_CCMR1_OC1FE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_OC1FE_SHIFT)) & TIM1_CCMR1_OC1FE_MASK)

#define TIM1_CCMR1_CC1S_SHIFT                   (0)
#define TIM1_CCMR1_CC1S_MASK                    (0x3U << TIM1_CCMR1_CC1S_SHIFT)
#define TIM1_CCMR1_CC1S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_CC1S_SHIFT)) & TIM1_CCMR1_CC1S_MASK)

/*!
 * @brief TIM1_CCMR1 Register Bit Definition
 */

#define TIM1_CCMR1_IC2F_SHIFT                   (12)
#define TIM1_CCMR1_IC2F_MASK                    (0xFU << TIM1_CCMR1_IC2F_SHIFT)
#define TIM1_CCMR1_IC2F(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_IC2F_SHIFT)) & TIM1_CCMR1_IC2F_MASK)

#define TIM1_CCMR1_IC2PSC_SHIFT                 (10)
#define TIM1_CCMR1_IC2PSC_MASK                  (0x3U << TIM1_CCMR1_IC2PSC_SHIFT)
#define TIM1_CCMR1_IC2PSC(x)                    (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_IC2PSC_SHIFT)) & TIM1_CCMR1_IC2PSC_MASK)

#define TIM1_CCMR1_CC2S_SHIFT                   (8)
#define TIM1_CCMR1_CC2S_MASK                    (0x3U << TIM1_CCMR1_CC2S_SHIFT)
#define TIM1_CCMR1_CC2S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_CC2S_SHIFT)) & TIM1_CCMR1_CC2S_MASK)

#define TIM1_CCMR1_IC1F_SHIFT                   (4)
#define TIM1_CCMR1_IC1F_MASK                    (0xFU << TIM1_CCMR1_IC1F_SHIFT)
#define TIM1_CCMR1_IC1F(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_IC1F_SHIFT)) & TIM1_CCMR1_IC1F_MASK)

#define TIM1_CCMR1_IC1PSC_SHIFT                 (2)
#define TIM1_CCMR1_IC1PSC_MASK                  (0x3U << TIM1_CCMR1_IC1PSC_SHIFT)
#define TIM1_CCMR1_IC1PSC(x)                    (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_IC1PSC_SHIFT)) & TIM1_CCMR1_IC1PSC_MASK)

#define TIM1_CCMR1_CC1S_SHIFT                   (0)
#define TIM1_CCMR1_CC1S_MASK                    (0x3U << TIM1_CCMR1_CC1S_SHIFT)
#define TIM1_CCMR1_CC1S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR1_CC1S_SHIFT)) & TIM1_CCMR1_CC1S_MASK)

/*!
 * @brief TIM1_CCMR2 Register Bit Definition
 */

#define TIM1_CCMR2_OC4CE_SHIFT                  (15)
#define TIM1_CCMR2_OC4CE_MASK                   (0x01U << TIM1_CCMR2_OC4CE_SHIFT)
#define TIM1_CCMR2_OC4CE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_OC4CE_SHIFT)) & TIM1_CCMR2_OC4CE_MASK)

#define TIM1_CCMR2_OC4M_SHIFT                   (12)
#define TIM1_CCMR2_OC4M_MASK                    (0x7U << TIM1_CCMR2_OC4M_SHIFT)
#define TIM1_CCMR2_OC4M(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_OC4M_SHIFT)) & TIM1_CCMR2_OC4M_MASK)

#define TIM1_CCMR2_OC4PE_SHIFT                  (11)
#define TIM1_CCMR2_OC4PE_MASK                   (0x01U << TIM1_CCMR2_OC4PE_SHIFT)
#define TIM1_CCMR2_OC4PE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_OC4PE_SHIFT)) & TIM1_CCMR2_OC4PE_MASK)

#define TIM1_CCMR2_OC4FE_SHIFT                  (10)
#define TIM1_CCMR2_OC4FE_MASK                   (0x01U << TIM1_CCMR2_OC4FE_SHIFT)
#define TIM1_CCMR2_OC4FE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_OC4FE_SHIFT)) & TIM1_CCMR2_OC4FE_MASK)

#define TIM1_CCMR2_CC4S_SHIFT                   (8)
#define TIM1_CCMR2_CC4S_MASK                    (0x3U << TIM1_CCMR2_CC4S_SHIFT)
#define TIM1_CCMR2_CC4S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_CC4S_SHIFT)) & TIM1_CCMR2_CC4S_MASK)

#define TIM1_CCMR2_OC3CE_SHIFT                  (7)
#define TIM1_CCMR2_OC3CE_MASK                   (0x01U << TIM1_CCMR2_OC3CE_SHIFT)
#define TIM1_CCMR2_OC3CE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_OC3CE_SHIFT)) & TIM1_CCMR2_OC3CE_MASK)

#define TIM1_CCMR2_OC3M_SHIFT                   (4)
#define TIM1_CCMR2_OC3M_MASK                    (0x7U << TIM1_CCMR2_OC3M_SHIFT)
#define TIM1_CCMR2_OC3M(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_OC3M_SHIFT)) & TIM1_CCMR2_OC3M_MASK)

#define TIM1_CCMR2_OC3PE_SHIFT                  (3)
#define TIM1_CCMR2_OC3PE_MASK                   (0x01U << TIM1_CCMR2_OC3PE_SHIFT)
#define TIM1_CCMR2_OC3PE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_OC3PE_SHIFT)) & TIM1_CCMR2_OC3PE_MASK)

#define TIM1_CCMR2_OC3FE_SHIFT                  (2)
#define TIM1_CCMR2_OC3FE_MASK                   (0x01U << TIM1_CCMR2_OC3FE_SHIFT)
#define TIM1_CCMR2_OC3FE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_OC3FE_SHIFT)) & TIM1_CCMR2_OC3FE_MASK)

#define TIM1_CCMR2_CC3S_SHIFT                   (0)
#define TIM1_CCMR2_CC3S_MASK                    (0x3U << TIM1_CCMR2_CC3S_SHIFT)
#define TIM1_CCMR2_CC3S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_CC3S_SHIFT)) & TIM1_CCMR2_CC3S_MASK)

/*!
 * @brief TIM1_CCMR2 Register Bit Definition
 */

#define TIM1_CCMR2_IC4F_SHIFT                   (12)
#define TIM1_CCMR2_IC4F_MASK                    (0xFU << TIM1_CCMR2_IC4F_SHIFT)
#define TIM1_CCMR2_IC4F(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_IC4F_SHIFT)) & TIM1_CCMR2_IC4F_MASK)

#define TIM1_CCMR2_IC4PSC_SHIFT                 (10)
#define TIM1_CCMR2_IC4PSC_MASK                  (0x3U << TIM1_CCMR2_IC4PSC_SHIFT)
#define TIM1_CCMR2_IC4PSC(x)                    (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_IC4PSC_SHIFT)) & TIM1_CCMR2_IC4PSC_MASK)

#define TIM1_CCMR2_CC4S_SHIFT                   (8)
#define TIM1_CCMR2_CC4S_MASK                    (0x3U << TIM1_CCMR2_CC4S_SHIFT)
#define TIM1_CCMR2_CC4S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_CC4S_SHIFT)) & TIM1_CCMR2_CC4S_MASK)

#define TIM1_CCMR2_IC3F_SHIFT                   (4)
#define TIM1_CCMR2_IC3F_MASK                    (0xFU << TIM1_CCMR2_IC3F_SHIFT)
#define TIM1_CCMR2_IC3F(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_IC3F_SHIFT)) & TIM1_CCMR2_IC3F_MASK)

#define TIM1_CCMR2_IC3PSC_SHIFT                 (2)
#define TIM1_CCMR2_IC3PSC_MASK                  (0x3U << TIM1_CCMR2_IC3PSC_SHIFT)
#define TIM1_CCMR2_IC3PSC(x)                    (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_IC3PSC_SHIFT)) & TIM1_CCMR2_IC3PSC_MASK)

#define TIM1_CCMR2_CC3S_SHIFT                   (0)
#define TIM1_CCMR2_CC3S_MASK                    (0x3U << TIM1_CCMR2_CC3S_SHIFT)
#define TIM1_CCMR2_CC3S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR2_CC3S_SHIFT)) & TIM1_CCMR2_CC3S_MASK)

/*!
 * @brief TIM1_CCER Register Bit Definition
 */

#define TIM1_CCER_CC4NP_SHIFT                   (15)
#define TIM1_CCER_CC4NP_MASK                    (0x01U << TIM1_CCER_CC4NP_SHIFT)
#define TIM1_CCER_CC4NP(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC4NP_SHIFT)) & TIM1_CCER_CC4NP_MASK)

#define TIM1_CCER_CC4P_SHIFT                    (13)
#define TIM1_CCER_CC4P_MASK                     (0x01U << TIM1_CCER_CC4P_SHIFT)
#define TIM1_CCER_CC4P(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC4P_SHIFT)) & TIM1_CCER_CC4P_MASK)

#define TIM1_CCER_CC4E_SHIFT                    (12)
#define TIM1_CCER_CC4E_MASK                     (0x01U << TIM1_CCER_CC4E_SHIFT)
#define TIM1_CCER_CC4E(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC4E_SHIFT)) & TIM1_CCER_CC4E_MASK)

#define TIM1_CCER_CC3NP_SHIFT                   (11)
#define TIM1_CCER_CC3NP_MASK                    (0x01U << TIM1_CCER_CC3NP_SHIFT)
#define TIM1_CCER_CC3NP(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC3NP_SHIFT)) & TIM1_CCER_CC3NP_MASK)

#define TIM1_CCER_CC3NE_SHIFT                   (10)
#define TIM1_CCER_CC3NE_MASK                    (0x01U << TIM1_CCER_CC3NE_SHIFT)
#define TIM1_CCER_CC3NE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC3NE_SHIFT)) & TIM1_CCER_CC3NE_MASK)

#define TIM1_CCER_CC3P_SHIFT                    (9)
#define TIM1_CCER_CC3P_MASK                     (0x01U << TIM1_CCER_CC3P_SHIFT)
#define TIM1_CCER_CC3P(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC3P_SHIFT)) & TIM1_CCER_CC3P_MASK)

#define TIM1_CCER_CC3E_SHIFT                    (8)
#define TIM1_CCER_CC3E_MASK                     (0x01U << TIM1_CCER_CC3E_SHIFT)
#define TIM1_CCER_CC3E(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC3E_SHIFT)) & TIM1_CCER_CC3E_MASK)

#define TIM1_CCER_CC2NP_SHIFT                   (7)
#define TIM1_CCER_CC2NP_MASK                    (0x01U << TIM1_CCER_CC2NP_SHIFT)
#define TIM1_CCER_CC2NP(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC2NP_SHIFT)) & TIM1_CCER_CC2NP_MASK)

#define TIM1_CCER_CC2NE_SHIFT                   (6)
#define TIM1_CCER_CC2NE_MASK                    (0x01U << TIM1_CCER_CC2NE_SHIFT)
#define TIM1_CCER_CC2NE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC2NE_SHIFT)) & TIM1_CCER_CC2NE_MASK)

#define TIM1_CCER_CC2P_SHIFT                    (5)
#define TIM1_CCER_CC2P_MASK                     (0x01U << TIM1_CCER_CC2P_SHIFT)
#define TIM1_CCER_CC2P(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC2P_SHIFT)) & TIM1_CCER_CC2P_MASK)

#define TIM1_CCER_CC2E_SHIFT                    (4)
#define TIM1_CCER_CC2E_MASK                     (0x01U << TIM1_CCER_CC2E_SHIFT)
#define TIM1_CCER_CC2E(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC2E_SHIFT)) & TIM1_CCER_CC2E_MASK)

#define TIM1_CCER_CC1NP_SHIFT                   (3)
#define TIM1_CCER_CC1NP_MASK                    (0x01U << TIM1_CCER_CC1NP_SHIFT)
#define TIM1_CCER_CC1NP(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC1NP_SHIFT)) & TIM1_CCER_CC1NP_MASK)

#define TIM1_CCER_CC1NE_SHIFT                   (2)
#define TIM1_CCER_CC1NE_MASK                    (0x01U << TIM1_CCER_CC1NE_SHIFT)
#define TIM1_CCER_CC1NE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC1NE_SHIFT)) & TIM1_CCER_CC1NE_MASK)

#define TIM1_CCER_CC1P_SHIFT                    (1)
#define TIM1_CCER_CC1P_MASK                     (0x01U << TIM1_CCER_CC1P_SHIFT)
#define TIM1_CCER_CC1P(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC1P_SHIFT)) & TIM1_CCER_CC1P_MASK)

#define TIM1_CCER_CC1E_SHIFT                    (0)
#define TIM1_CCER_CC1E_MASK                     (0x01U << TIM1_CCER_CC1E_SHIFT)
#define TIM1_CCER_CC1E(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CCER_CC1E_SHIFT)) & TIM1_CCER_CC1E_MASK)

/*!
 * @brief TIM1_CNT Register Bit Definition
 */

#define TIM1_CNT_CNT_SHIFT                      (0)
#define TIM1_CNT_CNT_MASK                       (0xFFFFU << TIM1_CNT_CNT_SHIFT)
#define TIM1_CNT_CNT(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_CNT_CNT_SHIFT)) & TIM1_CNT_CNT_MASK)

/*!
 * @brief TIM1_PSC Register Bit Definition
 */

#define TIM1_PSC_PSC_SHIFT                      (0)
#define TIM1_PSC_PSC_MASK                       (0xFFFFU << TIM1_PSC_PSC_SHIFT)
#define TIM1_PSC_PSC(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_PSC_PSC_SHIFT)) & TIM1_PSC_PSC_MASK)

/*!
 * @brief TIM1_ARR Register Bit Definition
 */

#define TIM1_ARR_ARR_SHIFT                      (0)
#define TIM1_ARR_ARR_MASK                       (0xFFFFU << TIM1_ARR_ARR_SHIFT)
#define TIM1_ARR_ARR(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_ARR_ARR_SHIFT)) & TIM1_ARR_ARR_MASK)

/*!
 * @brief TIM1_RCR Register Bit Definition
 */

#define TIM1_RCR_REPCNT_SHIFT                   (8)
#define TIM1_RCR_REPCNT_MASK                    (0xFFU << TIM1_RCR_REPCNT_SHIFT)
#define TIM1_RCR_REPCNT(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_RCR_REPCNT_SHIFT)) & TIM1_RCR_REPCNT_MASK)

#define TIM1_RCR_REP_SHIFT                      (0)
#define TIM1_RCR_REP_MASK                       (0xFFU << TIM1_RCR_REP_SHIFT)
#define TIM1_RCR_REP(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_RCR_REP_SHIFT)) & TIM1_RCR_REP_MASK)

/*!
 * @brief TIM1_CCR1 Register Bit Definition
 */

#define TIM1_CCR1_CCR1_SHIFT                    (0)
#define TIM1_CCR1_CCR1_MASK                     (0xFFFFU << TIM1_CCR1_CCR1_SHIFT)
#define TIM1_CCR1_CCR1(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CCR1_CCR1_SHIFT)) & TIM1_CCR1_CCR1_MASK)

/*!
 * @brief TIM1_CCR2 Register Bit Definition
 */

#define TIM1_CCR2_CCR2_SHIFT                    (0)
#define TIM1_CCR2_CCR2_MASK                     (0xFFFFU << TIM1_CCR2_CCR2_SHIFT)
#define TIM1_CCR2_CCR2(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CCR2_CCR2_SHIFT)) & TIM1_CCR2_CCR2_MASK)

/*!
 * @brief TIM1_CCR3 Register Bit Definition
 */

#define TIM1_CCR3_CCR3_SHIFT                    (0)
#define TIM1_CCR3_CCR3_MASK                     (0xFFFFU << TIM1_CCR3_CCR3_SHIFT)
#define TIM1_CCR3_CCR3(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CCR3_CCR3_SHIFT)) & TIM1_CCR3_CCR3_MASK)

/*!
 * @brief TIM1_CCR4 Register Bit Definition
 */

#define TIM1_CCR4_CCR4_SHIFT                    (0)
#define TIM1_CCR4_CCR4_MASK                     (0xFFFFU << TIM1_CCR4_CCR4_SHIFT)
#define TIM1_CCR4_CCR4(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CCR4_CCR4_SHIFT)) & TIM1_CCR4_CCR4_MASK)

/*!
 * @brief TIM1_BDTR Register Bit Definition
 */

#define TIM1_BDTR_DOE_SHIFT                     (16)
#define TIM1_BDTR_DOE_MASK                      (0x01U << TIM1_BDTR_DOE_SHIFT)
#define TIM1_BDTR_DOE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_BDTR_DOE_SHIFT)) & TIM1_BDTR_DOE_MASK)

#define TIM1_BDTR_MOE_SHIFT                     (15)
#define TIM1_BDTR_MOE_MASK                      (0x01U << TIM1_BDTR_MOE_SHIFT)
#define TIM1_BDTR_MOE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_BDTR_MOE_SHIFT)) & TIM1_BDTR_MOE_MASK)

#define TIM1_BDTR_AOE_SHIFT                     (14)
#define TIM1_BDTR_AOE_MASK                      (0x01U << TIM1_BDTR_AOE_SHIFT)
#define TIM1_BDTR_AOE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_BDTR_AOE_SHIFT)) & TIM1_BDTR_AOE_MASK)

#define TIM1_BDTR_BKP_SHIFT                     (13)
#define TIM1_BDTR_BKP_MASK                      (0x01U << TIM1_BDTR_BKP_SHIFT)
#define TIM1_BDTR_BKP(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_BDTR_BKP_SHIFT)) & TIM1_BDTR_BKP_MASK)

#define TIM1_BDTR_BKE_SHIFT                     (12)
#define TIM1_BDTR_BKE_MASK                      (0x01U << TIM1_BDTR_BKE_SHIFT)
#define TIM1_BDTR_BKE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_BDTR_BKE_SHIFT)) & TIM1_BDTR_BKE_MASK)

#define TIM1_BDTR_OSSR_SHIFT                    (11)
#define TIM1_BDTR_OSSR_MASK                     (0x01U << TIM1_BDTR_OSSR_SHIFT)
#define TIM1_BDTR_OSSR(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_BDTR_OSSR_SHIFT)) & TIM1_BDTR_OSSR_MASK)

#define TIM1_BDTR_OSSI_SHIFT                    (10)
#define TIM1_BDTR_OSSI_MASK                     (0x01U << TIM1_BDTR_OSSI_SHIFT)
#define TIM1_BDTR_OSSI(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_BDTR_OSSI_SHIFT)) & TIM1_BDTR_OSSI_MASK)

#define TIM1_BDTR_LOCK_SHIFT                    (8)
#define TIM1_BDTR_LOCK_MASK                     (0x3U << TIM1_BDTR_LOCK_SHIFT)
#define TIM1_BDTR_LOCK(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_BDTR_LOCK_SHIFT)) & TIM1_BDTR_LOCK_MASK)

#define TIM1_BDTR_DTG_SHIFT                     (0)
#define TIM1_BDTR_DTG_MASK                      (0xFFU << TIM1_BDTR_DTG_SHIFT)
#define TIM1_BDTR_DTG(x)                        (((uint32_t)(((uint32_t)(x)) << TIM1_BDTR_DTG_SHIFT)) & TIM1_BDTR_DTG_MASK)

/*!
 * @brief TIM1_DCR Register Bit Definition
 */

#define TIM1_DCR_DBL_SHIFT                      (8)
#define TIM1_DCR_DBL_MASK                       (0x1FU << TIM1_DCR_DBL_SHIFT)
#define TIM1_DCR_DBL(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_DCR_DBL_SHIFT)) & TIM1_DCR_DBL_MASK)

#define TIM1_DCR_DBA_SHIFT                      (0)
#define TIM1_DCR_DBA_MASK                       (0x1FU << TIM1_DCR_DBA_SHIFT)
#define TIM1_DCR_DBA(x)                         (((uint32_t)(((uint32_t)(x)) << TIM1_DCR_DBA_SHIFT)) & TIM1_DCR_DBA_MASK)

/*!
 * @brief TIM1_DMAR Register Bit Definition
 */

#define TIM1_DMAR_DMAB_SHIFT                    (0)
#define TIM1_DMAR_DMAB_MASK                     (0xFFFFU << TIM1_DMAR_DMAB_SHIFT)
#define TIM1_DMAR_DMAB(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_DMAR_DMAB_SHIFT)) & TIM1_DMAR_DMAB_MASK)

/*!
 * @brief TIM1_CCMR3 Register Bit Definition
 */

#define TIM1_CCMR3_OC5M_SHIFT                   (4)
#define TIM1_CCMR3_OC5M_MASK                    (0x7U << TIM1_CCMR3_OC5M_SHIFT)
#define TIM1_CCMR3_OC5M(x)                      (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR3_OC5M_SHIFT)) & TIM1_CCMR3_OC5M_MASK)

#define TIM1_CCMR3_OC5PE_SHIFT                  (3)
#define TIM1_CCMR3_OC5PE_MASK                   (0x01U << TIM1_CCMR3_OC5PE_SHIFT)
#define TIM1_CCMR3_OC5PE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR3_OC5PE_SHIFT)) & TIM1_CCMR3_OC5PE_MASK)

#define TIM1_CCMR3_OC5FE_SHIFT                  (2)
#define TIM1_CCMR3_OC5FE_MASK                   (0x01U << TIM1_CCMR3_OC5FE_SHIFT)
#define TIM1_CCMR3_OC5FE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM1_CCMR3_OC5FE_SHIFT)) & TIM1_CCMR3_OC5FE_MASK)

/*!
 * @brief TIM1_CCR5 Register Bit Definition
 */

#define TIM1_CCR5_CCR5_SHIFT                    (0)
#define TIM1_CCR5_CCR5_MASK                     (0xFFFFU << TIM1_CCR5_CCR5_SHIFT)
#define TIM1_CCR5_CCR5(x)                       (((uint32_t)(((uint32_t)(x)) << TIM1_CCR5_CCR5_SHIFT)) & TIM1_CCR5_CCR5_MASK)

/*!
 * @brief TIM1_PDER Register Bit Definition
 */

#define TIM1_PDER_CCR5SHIFTEN_SHIFT             (5)
#define TIM1_PDER_CCR5SHIFTEN_MASK              (0x01U << TIM1_PDER_CCR5SHIFTEN_SHIFT)
#define TIM1_PDER_CCR5SHIFTEN(x)                (((uint32_t)(((uint32_t)(x)) << TIM1_PDER_CCR5SHIFTEN_SHIFT)) & TIM1_PDER_CCR5SHIFTEN_MASK)

#define TIM1_PDER_CCR4SHIFTEN_SHIFT             (4)
#define TIM1_PDER_CCR4SHIFTEN_MASK              (0x01U << TIM1_PDER_CCR4SHIFTEN_SHIFT)
#define TIM1_PDER_CCR4SHIFTEN(x)                (((uint32_t)(((uint32_t)(x)) << TIM1_PDER_CCR4SHIFTEN_SHIFT)) & TIM1_PDER_CCR4SHIFTEN_MASK)

#define TIM1_PDER_CCR3SHIFTEN_SHIFT             (3)
#define TIM1_PDER_CCR3SHIFTEN_MASK              (0x01U << TIM1_PDER_CCR3SHIFTEN_SHIFT)
#define TIM1_PDER_CCR3SHIFTEN(x)                (((uint32_t)(((uint32_t)(x)) << TIM1_PDER_CCR3SHIFTEN_SHIFT)) & TIM1_PDER_CCR3SHIFTEN_MASK)

#define TIM1_PDER_CCR2SHIFTEN_SHIFT             (2)
#define TIM1_PDER_CCR2SHIFTEN_MASK              (0x01U << TIM1_PDER_CCR2SHIFTEN_SHIFT)
#define TIM1_PDER_CCR2SHIFTEN(x)                (((uint32_t)(((uint32_t)(x)) << TIM1_PDER_CCR2SHIFTEN_SHIFT)) & TIM1_PDER_CCR2SHIFTEN_MASK)

#define TIM1_PDER_CCR1SHIFTEN_SHIFT             (1)
#define TIM1_PDER_CCR1SHIFTEN_MASK              (0x01U << TIM1_PDER_CCR1SHIFTEN_SHIFT)
#define TIM1_PDER_CCR1SHIFTEN(x)                (((uint32_t)(((uint32_t)(x)) << TIM1_PDER_CCR1SHIFTEN_SHIFT)) & TIM1_PDER_CCR1SHIFTEN_MASK)

#define TIM1_PDER_CCDREPE_SHIFT                 (0)
#define TIM1_PDER_CCDREPE_MASK                  (0x01U << TIM1_PDER_CCDREPE_SHIFT)
#define TIM1_PDER_CCDREPE(x)                    (((uint32_t)(((uint32_t)(x)) << TIM1_PDER_CCDREPE_SHIFT)) & TIM1_PDER_CCDREPE_MASK)

/*!
 * @brief TIM1_CCRFALL Register Bit Definition
 */

#define TIM1_CCRFALL_CCRXFALL_SHIFT             (0)
#define TIM1_CCRFALL_CCRXFALL_MASK              (0xFFFFU << TIM1_CCRFALL_CCRXFALL_SHIFT)
#define TIM1_CCRFALL_CCRXFALL(x)                (((uint32_t)(((uint32_t)(x)) << TIM1_CCRFALL_CCRXFALL_SHIFT)) & TIM1_CCRFALL_CCRXFALL_MASK)

/*!
 * @}
 */ /* end of group TIM1_Register_Masks */
/******************************************************************************
 * TIM1/8 Instance
******************************************************************************/
#define TIM1                                ((TIM1_Type*)TIM1_BASE)
#define TIM8                                ((TIM1_Type*)TIM8_BASE)

/*!
 * @}
 */ /* end of group TIM1_Peripheral_Access_Layer */



/*!
 * @addtogroup TIM3_Peripheral_Access_Layer TIM3 Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * TIM3 Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CR1;                                                            ///< Control register 1                           offset: 0x00
    __IO uint32_t CR2;                                                            ///< Control register 2                           offset: 0x04
    __IO uint32_t SMCR;                                                           ///< Slave mode control register                  offset: 0x08
    __IO uint32_t DIER;                                                           ///< DMA/interrupt enable register                offset: 0x0C
    __IO uint32_t SR;                                                             ///< Status register                              offset: 0x10
    __IO uint32_t EGR;                                                            ///< Event generation register                    offset: 0x14
    __IO uint32_t CCMR1;                                                          ///<                                              offset: 0x18
    __IO uint32_t CCMR2;                                                          ///< Capture/compare mode register 1              offset: 0x1C
    __IO uint32_t CCER;                                                           ///< Capture/compare enable register              offset: 0x20
    __IO uint32_t CNT;                                                            ///< Counter                                      offset: 0x24
    __IO uint32_t PSC;                                                            ///< Prescaler                                    offset: 0x28
    __IO uint32_t ARR;                                                            ///< Autoload register                            offset: 0x2C
    __IO uint32_t Reserved8[1];                                                   ///< Reserved
    __IO uint32_t CCR[4];
//    __IO uint32_t CCR1;                                                           ///< Capture/compare register 1                   offset: 0x34
//    __IO uint32_t CCR2;                                                           ///< Capture/compare register 2                   offset: 0x38
//    __IO uint32_t CCR3;                                                           ///< Capture/compare register 3                   offset: 0x3C
//    __IO uint32_t CCR4;                                                           ///< Capture/compare register 4                   offset: 0x40
    __IO uint32_t Reserved9[1];                                                   ///< Reserved
    __IO uint32_t DCR;                                                            ///< DMA control register                         offset: 0x48
    __IO uint32_t DMAR;                                                           ///< DMA address in continuous mode               offset: 0x4C
} TIM3_Type;

/*******************************************************************************
 * TIM3 Type
 ******************************************************************************/

/*!
 * @addtogroup TIM3_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief TIM3_CR1 Register Bit Definition
 */

#define TIM3_CR1_CKD_SHIFT                      (8)
#define TIM3_CR1_CKD_MASK                       (0x3U << TIM3_CR1_CKD_SHIFT)
#define TIM3_CR1_CKD(x)                         (((uint32_t)(((uint32_t)(x)) << TIM3_CR1_CKD_SHIFT)) & TIM3_CR1_CKD_MASK)

#define TIM3_CR1_APRE_SHIFT                     (7)
#define TIM3_CR1_APRE_MASK                      (0x01U << TIM3_CR1_APRE_SHIFT)
#define TIM3_CR1_APRE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_CR1_APRE_SHIFT)) & TIM3_CR1_APRE_MASK)

#define TIM3_CR1_CMS_SHIFT                      (5)
#define TIM3_CR1_CMS_MASK                       (0x3U << TIM3_CR1_CMS_SHIFT)
#define TIM3_CR1_CMS(x)                         (((uint32_t)(((uint32_t)(x)) << TIM3_CR1_CMS_SHIFT)) & TIM3_CR1_CMS_MASK)

#define TIM3_CR1_DIR_SHIFT                      (4)
#define TIM3_CR1_DIR_MASK                       (0x01U << TIM3_CR1_DIR_SHIFT)
#define TIM3_CR1_DIR(x)                         (((uint32_t)(((uint32_t)(x)) << TIM3_CR1_DIR_SHIFT)) & TIM3_CR1_DIR_MASK)

#define TIM3_CR1_OPM_SHIFT                      (3)
#define TIM3_CR1_OPM_MASK                       (0x01U << TIM3_CR1_OPM_SHIFT)
#define TIM3_CR1_OPM(x)                         (((uint32_t)(((uint32_t)(x)) << TIM3_CR1_OPM_SHIFT)) & TIM3_CR1_OPM_MASK)

#define TIM3_CR1_URS_SHIFT                      (2)
#define TIM3_CR1_URS_MASK                       (0x01U << TIM3_CR1_URS_SHIFT)
#define TIM3_CR1_URS(x)                         (((uint32_t)(((uint32_t)(x)) << TIM3_CR1_URS_SHIFT)) & TIM3_CR1_URS_MASK)

#define TIM3_CR1_UDIS_SHIFT                     (1)
#define TIM3_CR1_UDIS_MASK                      (0x01U << TIM3_CR1_UDIS_SHIFT)
#define TIM3_CR1_UDIS(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_CR1_UDIS_SHIFT)) & TIM3_CR1_UDIS_MASK)

#define TIM3_CR1_CEN_SHIFT                      (0)
#define TIM3_CR1_CEN_MASK                       (0x01U << TIM3_CR1_CEN_SHIFT)
#define TIM3_CR1_CEN(x)                         (((uint32_t)(((uint32_t)(x)) << TIM3_CR1_CEN_SHIFT)) & TIM3_CR1_CEN_MASK)

/*!
 * @brief TIM3_CR2 Register Bit Definition
 */

#define TIM3_CR2_TI1S_SHIFT                     (7)
#define TIM3_CR2_TI1S_MASK                      (0x01U << TIM3_CR2_TI1S_SHIFT)
#define TIM3_CR2_TI1S(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_CR2_TI1S_SHIFT)) & TIM3_CR2_TI1S_MASK)

#define TIM3_CR2_MMS_SHIFT                      (4)
#define TIM3_CR2_MMS_MASK                       (0x7U << TIM3_CR2_MMS_SHIFT)
#define TIM3_CR2_MMS(x)                         (((uint32_t)(((uint32_t)(x)) << TIM3_CR2_MMS_SHIFT)) & TIM3_CR2_MMS_MASK)

#define TIM3_CR2_CCDS_SHIFT                     (3)
#define TIM3_CR2_CCDS_MASK                      (0x01U << TIM3_CR2_CCDS_SHIFT)
#define TIM3_CR2_CCDS(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_CR2_CCDS_SHIFT)) & TIM3_CR2_CCDS_MASK)

/*!
 * @brief TIM3_SMCR Register Bit Definition
 */

#define TIM3_SMCR_ETP_SHIFT                     (15)
#define TIM3_SMCR_ETP_MASK                      (0x01U << TIM3_SMCR_ETP_SHIFT)
#define TIM3_SMCR_ETP(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_SMCR_ETP_SHIFT)) & TIM3_SMCR_ETP_MASK)

#define TIM3_SMCR_ECE_SHIFT                     (14)
#define TIM3_SMCR_ECE_MASK                      (0x01U << TIM3_SMCR_ECE_SHIFT)
#define TIM3_SMCR_ECE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_SMCR_ECE_SHIFT)) & TIM3_SMCR_ECE_MASK)

#define TIM3_SMCR_ETPS_SHIFT                    (12)
#define TIM3_SMCR_ETPS_MASK                     (0x3U << TIM3_SMCR_ETPS_SHIFT)
#define TIM3_SMCR_ETPS(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_SMCR_ETPS_SHIFT)) & TIM3_SMCR_ETPS_MASK)

#define TIM3_SMCR_ETF_SHIFT                     (8)
#define TIM3_SMCR_ETF_MASK                      (0xFU << TIM3_SMCR_ETF_SHIFT)
#define TIM3_SMCR_ETF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_SMCR_ETF_SHIFT)) & TIM3_SMCR_ETF_MASK)

#define TIM3_SMCR_MSM_SHIFT                     (7)
#define TIM3_SMCR_MSM_MASK                      (0x01U << TIM3_SMCR_MSM_SHIFT)
#define TIM3_SMCR_MSM(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_SMCR_MSM_SHIFT)) & TIM3_SMCR_MSM_MASK)

#define TIM3_SMCR_TS_SHIFT                      (4)
#define TIM3_SMCR_TS_MASK                       (0x7U << TIM3_SMCR_TS_SHIFT)
#define TIM3_SMCR_TS(x)                         (((uint32_t)(((uint32_t)(x)) << TIM3_SMCR_TS_SHIFT)) & TIM3_SMCR_TS_MASK)

#define TIM3_SMCR_OCCS_SHIFT                    (3)
#define TIM3_SMCR_OCCS_MASK                     (0x01U << TIM3_SMCR_OCCS_SHIFT)
#define TIM3_SMCR_OCCS(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_SMCR_OCCS_SHIFT)) & TIM3_SMCR_OCCS_MASK)

#define TIM3_SMCR_SMS_SHIFT                     (0)
#define TIM3_SMCR_SMS_MASK                      (0x7U << TIM3_SMCR_SMS_SHIFT)
#define TIM3_SMCR_SMS(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_SMCR_SMS_SHIFT)) & TIM3_SMCR_SMS_MASK)

/*!
 * @brief TIM3_DIER Register Bit Definition
 */

#define TIM3_DIER_TDE_SHIFT                     (14)
#define TIM3_DIER_TDE_MASK                      (0x01U << TIM3_DIER_TDE_SHIFT)
#define TIM3_DIER_TDE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_DIER_TDE_SHIFT)) & TIM3_DIER_TDE_MASK)

#define TIM3_DIER_CC4DE_SHIFT                   (12)
#define TIM3_DIER_CC4DE_MASK                    (0x01U << TIM3_DIER_CC4DE_SHIFT)
#define TIM3_DIER_CC4DE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_DIER_CC4DE_SHIFT)) & TIM3_DIER_CC4DE_MASK)

#define TIM3_DIER_CC3DE_SHIFT                   (11)
#define TIM3_DIER_CC3DE_MASK                    (0x01U << TIM3_DIER_CC3DE_SHIFT)
#define TIM3_DIER_CC3DE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_DIER_CC3DE_SHIFT)) & TIM3_DIER_CC3DE_MASK)

#define TIM3_DIER_CC2DE_SHIFT                   (10)
#define TIM3_DIER_CC2DE_MASK                    (0x01U << TIM3_DIER_CC2DE_SHIFT)
#define TIM3_DIER_CC2DE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_DIER_CC2DE_SHIFT)) & TIM3_DIER_CC2DE_MASK)

#define TIM3_DIER_CC1DE_SHIFT                   (9)
#define TIM3_DIER_CC1DE_MASK                    (0x01U << TIM3_DIER_CC1DE_SHIFT)
#define TIM3_DIER_CC1DE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_DIER_CC1DE_SHIFT)) & TIM3_DIER_CC1DE_MASK)

#define TIM3_DIER_UDE_SHIFT                     (8)
#define TIM3_DIER_UDE_MASK                      (0x01U << TIM3_DIER_UDE_SHIFT)
#define TIM3_DIER_UDE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_DIER_UDE_SHIFT)) & TIM3_DIER_UDE_MASK)

#define TIM3_DIER_TIE_SHIFT                     (6)
#define TIM3_DIER_TIE_MASK                      (0x01U << TIM3_DIER_TIE_SHIFT)
#define TIM3_DIER_TIE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_DIER_TIE_SHIFT)) & TIM3_DIER_TIE_MASK)

#define TIM3_DIER_CC4IE_SHIFT                   (4)
#define TIM3_DIER_CC4IE_MASK                    (0x01U << TIM3_DIER_CC4IE_SHIFT)
#define TIM3_DIER_CC4IE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_DIER_CC4IE_SHIFT)) & TIM3_DIER_CC4IE_MASK)

#define TIM3_DIER_CC3IE_SHIFT                   (3)
#define TIM3_DIER_CC3IE_MASK                    (0x01U << TIM3_DIER_CC3IE_SHIFT)
#define TIM3_DIER_CC3IE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_DIER_CC3IE_SHIFT)) & TIM3_DIER_CC3IE_MASK)

#define TIM3_DIER_CC2IE_SHIFT                   (2)
#define TIM3_DIER_CC2IE_MASK                    (0x01U << TIM3_DIER_CC2IE_SHIFT)
#define TIM3_DIER_CC2IE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_DIER_CC2IE_SHIFT)) & TIM3_DIER_CC2IE_MASK)

#define TIM3_DIER_CC1IE_SHIFT                   (1)
#define TIM3_DIER_CC1IE_MASK                    (0x01U << TIM3_DIER_CC1IE_SHIFT)
#define TIM3_DIER_CC1IE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_DIER_CC1IE_SHIFT)) & TIM3_DIER_CC1IE_MASK)

#define TIM3_DIER_UIE_SHIFT                     (0)
#define TIM3_DIER_UIE_MASK                      (0x01U << TIM3_DIER_UIE_SHIFT)
#define TIM3_DIER_UIE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_DIER_UIE_SHIFT)) & TIM3_DIER_UIE_MASK)

/*!
 * @brief TIM3_SR Register Bit Definition
 */

#define TIM3_SR_CC4OF_SHIFT                     (12)
#define TIM3_SR_CC4OF_MASK                      (0x01U << TIM3_SR_CC4OF_SHIFT)
#define TIM3_SR_CC4OF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_SR_CC4OF_SHIFT)) & TIM3_SR_CC4OF_MASK)

#define TIM3_SR_CC3OF_SHIFT                     (11)
#define TIM3_SR_CC3OF_MASK                      (0x01U << TIM3_SR_CC3OF_SHIFT)
#define TIM3_SR_CC3OF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_SR_CC3OF_SHIFT)) & TIM3_SR_CC3OF_MASK)

#define TIM3_SR_CC2OF_SHIFT                     (10)
#define TIM3_SR_CC2OF_MASK                      (0x01U << TIM3_SR_CC2OF_SHIFT)
#define TIM3_SR_CC2OF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_SR_CC2OF_SHIFT)) & TIM3_SR_CC2OF_MASK)

#define TIM3_SR_CC1OF_SHIFT                     (9)
#define TIM3_SR_CC1OF_MASK                      (0x01U << TIM3_SR_CC1OF_SHIFT)
#define TIM3_SR_CC1OF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_SR_CC1OF_SHIFT)) & TIM3_SR_CC1OF_MASK)

#define TIM3_SR_TIF_SHIFT                       (6)
#define TIM3_SR_TIF_MASK                        (0x01U << TIM3_SR_TIF_SHIFT)
#define TIM3_SR_TIF(x)                          (((uint32_t)(((uint32_t)(x)) << TIM3_SR_TIF_SHIFT)) & TIM3_SR_TIF_MASK)

#define TIM3_SR_CC4IF_SHIFT                     (4)
#define TIM3_SR_CC4IF_MASK                      (0x01U << TIM3_SR_CC4IF_SHIFT)
#define TIM3_SR_CC4IF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_SR_CC4IF_SHIFT)) & TIM3_SR_CC4IF_MASK)

#define TIM3_SR_CC3IF_SHIFT                     (3)
#define TIM3_SR_CC3IF_MASK                      (0x01U << TIM3_SR_CC3IF_SHIFT)
#define TIM3_SR_CC3IF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_SR_CC3IF_SHIFT)) & TIM3_SR_CC3IF_MASK)

#define TIM3_SR_CC2IF_SHIFT                     (2)
#define TIM3_SR_CC2IF_MASK                      (0x01U << TIM3_SR_CC2IF_SHIFT)
#define TIM3_SR_CC2IF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_SR_CC2IF_SHIFT)) & TIM3_SR_CC2IF_MASK)

#define TIM3_SR_CC1IF_SHIFT                     (1)
#define TIM3_SR_CC1IF_MASK                      (0x01U << TIM3_SR_CC1IF_SHIFT)
#define TIM3_SR_CC1IF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_SR_CC1IF_SHIFT)) & TIM3_SR_CC1IF_MASK)

#define TIM3_SR_UIF_SHIFT                       (0)
#define TIM3_SR_UIF_MASK                        (0x01U << TIM3_SR_UIF_SHIFT)
#define TIM3_SR_UIF(x)                          (((uint32_t)(((uint32_t)(x)) << TIM3_SR_UIF_SHIFT)) & TIM3_SR_UIF_MASK)

/*!
 * @brief TIM3_EGR Register Bit Definition
 */

#define TIM3_EGR_TG_SHIFT                       (6)
#define TIM3_EGR_TG_MASK                        (0x01U << TIM3_EGR_TG_SHIFT)
#define TIM3_EGR_TG(x)                          (((uint32_t)(((uint32_t)(x)) << TIM3_EGR_TG_SHIFT)) & TIM3_EGR_TG_MASK)

#define TIM3_EGR_COMG_SHIFT                     (5)
#define TIM3_EGR_COMG_MASK                      (0x01U << TIM3_EGR_COMG_SHIFT)
#define TIM3_EGR_COMG(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_EGR_COMG_SHIFT)) & TIM3_EGR_COMG_MASK)

#define TIM3_EGR_CC4G_SHIFT                     (4)
#define TIM3_EGR_CC4G_MASK                      (0x01U << TIM3_EGR_CC4G_SHIFT)
#define TIM3_EGR_CC4G(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_EGR_CC4G_SHIFT)) & TIM3_EGR_CC4G_MASK)

#define TIM3_EGR_CC3G_SHIFT                     (3)
#define TIM3_EGR_CC3G_MASK                      (0x01U << TIM3_EGR_CC3G_SHIFT)
#define TIM3_EGR_CC3G(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_EGR_CC3G_SHIFT)) & TIM3_EGR_CC3G_MASK)

#define TIM3_EGR_CC2G_SHIFT                     (2)
#define TIM3_EGR_CC2G_MASK                      (0x01U << TIM3_EGR_CC2G_SHIFT)
#define TIM3_EGR_CC2G(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_EGR_CC2G_SHIFT)) & TIM3_EGR_CC2G_MASK)

#define TIM3_EGR_CC1G_SHIFT                     (1)
#define TIM3_EGR_CC1G_MASK                      (0x01U << TIM3_EGR_CC1G_SHIFT)
#define TIM3_EGR_CC1G(x)                        (((uint32_t)(((uint32_t)(x)) << TIM3_EGR_CC1G_SHIFT)) & TIM3_EGR_CC1G_MASK)

#define TIM3_EGR_UG_SHIFT                       (0)
#define TIM3_EGR_UG_MASK                        (0x01U << TIM3_EGR_UG_SHIFT)
#define TIM3_EGR_UG(x)                          (((uint32_t)(((uint32_t)(x)) << TIM3_EGR_UG_SHIFT)) & TIM3_EGR_UG_MASK)

/*!
 * @brief TIM3_CCMR1 Register Bit Definition
 */

#define TIM3_CCMR1_OC2CE_SHIFT                  (15)
#define TIM3_CCMR1_OC2CE_MASK                   (0x01U << TIM3_CCMR1_OC2CE_SHIFT)
#define TIM3_CCMR1_OC2CE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_OC2CE_SHIFT)) & TIM3_CCMR1_OC2CE_MASK)

#define TIM3_CCMR1_OC2M_SHIFT                   (12)
#define TIM3_CCMR1_OC2M_MASK                    (0x7U << TIM3_CCMR1_OC2M_SHIFT)
#define TIM3_CCMR1_OC2M(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_OC2M_SHIFT)) & TIM3_CCMR1_OC2M_MASK)

#define TIM3_CCMR1_OC2PE_SHIFT                  (11)
#define TIM3_CCMR1_OC2PE_MASK                   (0x01U << TIM3_CCMR1_OC2PE_SHIFT)
#define TIM3_CCMR1_OC2PE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_OC2PE_SHIFT)) & TIM3_CCMR1_OC2PE_MASK)

#define TIM3_CCMR1_OC2FE_SHIFT                  (10)
#define TIM3_CCMR1_OC2FE_MASK                   (0x01U << TIM3_CCMR1_OC2FE_SHIFT)
#define TIM3_CCMR1_OC2FE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_OC2FE_SHIFT)) & TIM3_CCMR1_OC2FE_MASK)

#define TIM3_CCMR1_CC2S_SHIFT                   (8)
#define TIM3_CCMR1_CC2S_MASK                    (0x3U << TIM3_CCMR1_CC2S_SHIFT)
#define TIM3_CCMR1_CC2S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_CC2S_SHIFT)) & TIM3_CCMR1_CC2S_MASK)

#define TIM3_CCMR1_OC1CE_SHIFT                  (7)
#define TIM3_CCMR1_OC1CE_MASK                   (0x01U << TIM3_CCMR1_OC1CE_SHIFT)
#define TIM3_CCMR1_OC1CE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_OC1CE_SHIFT)) & TIM3_CCMR1_OC1CE_MASK)

#define TIM3_CCMR1_OC1M_SHIFT                   (4)
#define TIM3_CCMR1_OC1M_MASK                    (0x7U << TIM3_CCMR1_OC1M_SHIFT)
#define TIM3_CCMR1_OC1M(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_OC1M_SHIFT)) & TIM3_CCMR1_OC1M_MASK)

#define TIM3_CCMR1_OC1PE_SHIFT                  (3)
#define TIM3_CCMR1_OC1PE_MASK                   (0x01U << TIM3_CCMR1_OC1PE_SHIFT)
#define TIM3_CCMR1_OC1PE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_OC1PE_SHIFT)) & TIM3_CCMR1_OC1PE_MASK)

#define TIM3_CCMR1_OC1FE_SHIFT                  (2)
#define TIM3_CCMR1_OC1FE_MASK                   (0x01U << TIM3_CCMR1_OC1FE_SHIFT)
#define TIM3_CCMR1_OC1FE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_OC1FE_SHIFT)) & TIM3_CCMR1_OC1FE_MASK)

#define TIM3_CCMR1_CC1S_SHIFT                   (0)
#define TIM3_CCMR1_CC1S_MASK                    (0x3U << TIM3_CCMR1_CC1S_SHIFT)
#define TIM3_CCMR1_CC1S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_CC1S_SHIFT)) & TIM3_CCMR1_CC1S_MASK)

/*!
 * @brief TIM3_CCMR1 Register Bit Definition
 */

#define TIM3_CCMR1_IC2F_SHIFT                   (12)
#define TIM3_CCMR1_IC2F_MASK                    (0xFU << TIM3_CCMR1_IC2F_SHIFT)
#define TIM3_CCMR1_IC2F(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_IC2F_SHIFT)) & TIM3_CCMR1_IC2F_MASK)

#define TIM3_CCMR1_IC2PSC_SHIFT                 (10)
#define TIM3_CCMR1_IC2PSC_MASK                  (0x3U << TIM3_CCMR1_IC2PSC_SHIFT)
#define TIM3_CCMR1_IC2PSC(x)                    (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_IC2PSC_SHIFT)) & TIM3_CCMR1_IC2PSC_MASK)

#define TIM3_CCMR1_CC2S_SHIFT                   (8)
#define TIM3_CCMR1_CC2S_MASK                    (0x3U << TIM3_CCMR1_CC2S_SHIFT)
#define TIM3_CCMR1_CC2S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_CC2S_SHIFT)) & TIM3_CCMR1_CC2S_MASK)

#define TIM3_CCMR1_IC1F_SHIFT                   (4)
#define TIM3_CCMR1_IC1F_MASK                    (0xFU << TIM3_CCMR1_IC1F_SHIFT)
#define TIM3_CCMR1_IC1F(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_IC1F_SHIFT)) & TIM3_CCMR1_IC1F_MASK)

#define TIM3_CCMR1_IC1PSC_SHIFT                 (2)
#define TIM3_CCMR1_IC1PSC_MASK                  (0x3U << TIM3_CCMR1_IC1PSC_SHIFT)
#define TIM3_CCMR1_IC1PSC(x)                    (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_IC1PSC_SHIFT)) & TIM3_CCMR1_IC1PSC_MASK)

#define TIM3_CCMR1_CC1S_SHIFT                   (0)
#define TIM3_CCMR1_CC1S_MASK                    (0x3U << TIM3_CCMR1_CC1S_SHIFT)
#define TIM3_CCMR1_CC1S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR1_CC1S_SHIFT)) & TIM3_CCMR1_CC1S_MASK)

/*!
 * @brief TIM3_CCMR2 Register Bit Definition
 */

#define TIM3_CCMR2_OC4CE_SHIFT                  (15)
#define TIM3_CCMR2_OC4CE_MASK                   (0x01U << TIM3_CCMR2_OC4CE_SHIFT)
#define TIM3_CCMR2_OC4CE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_OC4CE_SHIFT)) & TIM3_CCMR2_OC4CE_MASK)

#define TIM3_CCMR2_OC4M_SHIFT                   (12)
#define TIM3_CCMR2_OC4M_MASK                    (0x7U << TIM3_CCMR2_OC4M_SHIFT)
#define TIM3_CCMR2_OC4M(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_OC4M_SHIFT)) & TIM3_CCMR2_OC4M_MASK)

#define TIM3_CCMR2_OC4PE_SHIFT                  (11)
#define TIM3_CCMR2_OC4PE_MASK                   (0x01U << TIM3_CCMR2_OC4PE_SHIFT)
#define TIM3_CCMR2_OC4PE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_OC4PE_SHIFT)) & TIM3_CCMR2_OC4PE_MASK)

#define TIM3_CCMR2_OC4FE_SHIFT                  (10)
#define TIM3_CCMR2_OC4FE_MASK                   (0x01U << TIM3_CCMR2_OC4FE_SHIFT)
#define TIM3_CCMR2_OC4FE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_OC4FE_SHIFT)) & TIM3_CCMR2_OC4FE_MASK)

#define TIM3_CCMR2_CC4S_SHIFT                   (8)
#define TIM3_CCMR2_CC4S_MASK                    (0x3U << TIM3_CCMR2_CC4S_SHIFT)
#define TIM3_CCMR2_CC4S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_CC4S_SHIFT)) & TIM3_CCMR2_CC4S_MASK)

#define TIM3_CCMR2_OC3CE_SHIFT                  (7)
#define TIM3_CCMR2_OC3CE_MASK                   (0x01U << TIM3_CCMR2_OC3CE_SHIFT)
#define TIM3_CCMR2_OC3CE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_OC3CE_SHIFT)) & TIM3_CCMR2_OC3CE_MASK)

#define TIM3_CCMR2_OC3M_SHIFT                   (4)
#define TIM3_CCMR2_OC3M_MASK                    (0x7U << TIM3_CCMR2_OC3M_SHIFT)
#define TIM3_CCMR2_OC3M(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_OC3M_SHIFT)) & TIM3_CCMR2_OC3M_MASK)

#define TIM3_CCMR2_OC3PE_SHIFT                  (3)
#define TIM3_CCMR2_OC3PE_MASK                   (0x01U << TIM3_CCMR2_OC3PE_SHIFT)
#define TIM3_CCMR2_OC3PE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_OC3PE_SHIFT)) & TIM3_CCMR2_OC3PE_MASK)

#define TIM3_CCMR2_OC3FE_SHIFT                  (2)
#define TIM3_CCMR2_OC3FE_MASK                   (0x01U << TIM3_CCMR2_OC3FE_SHIFT)
#define TIM3_CCMR2_OC3FE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_OC3FE_SHIFT)) & TIM3_CCMR2_OC3FE_MASK)

#define TIM3_CCMR2_CC3S_SHIFT                   (0)
#define TIM3_CCMR2_CC3S_MASK                    (0x3U << TIM3_CCMR2_CC3S_SHIFT)
#define TIM3_CCMR2_CC3S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_CC3S_SHIFT)) & TIM3_CCMR2_CC3S_MASK)

/*!
 * @brief TIM3_CCMR2 Register Bit Definition
 */

#define TIM3_CCMR2_IC4F_SHIFT                   (12)
#define TIM3_CCMR2_IC4F_MASK                    (0xFU << TIM3_CCMR2_IC4F_SHIFT)
#define TIM3_CCMR2_IC4F(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_IC4F_SHIFT)) & TIM3_CCMR2_IC4F_MASK)

#define TIM3_CCMR2_IC4PSC_SHIFT                 (10)
#define TIM3_CCMR2_IC4PSC_MASK                  (0x3U << TIM3_CCMR2_IC4PSC_SHIFT)
#define TIM3_CCMR2_IC4PSC(x)                    (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_IC4PSC_SHIFT)) & TIM3_CCMR2_IC4PSC_MASK)

#define TIM3_CCMR2_CC4S_SHIFT                   (8)
#define TIM3_CCMR2_CC4S_MASK                    (0x3U << TIM3_CCMR2_CC4S_SHIFT)
#define TIM3_CCMR2_CC4S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_CC4S_SHIFT)) & TIM3_CCMR2_CC4S_MASK)

#define TIM3_CCMR2_IC3F_SHIFT                   (4)
#define TIM3_CCMR2_IC3F_MASK                    (0xFU << TIM3_CCMR2_IC3F_SHIFT)
#define TIM3_CCMR2_IC3F(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_IC3F_SHIFT)) & TIM3_CCMR2_IC3F_MASK)

#define TIM3_CCMR2_IC3PSC_SHIFT                 (2)
#define TIM3_CCMR2_IC3PSC_MASK                  (0x3U << TIM3_CCMR2_IC3PSC_SHIFT)
#define TIM3_CCMR2_IC3PSC(x)                    (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_IC3PSC_SHIFT)) & TIM3_CCMR2_IC3PSC_MASK)

#define TIM3_CCMR2_CC3S_SHIFT                   (0)
#define TIM3_CCMR2_CC3S_MASK                    (0x3U << TIM3_CCMR2_CC3S_SHIFT)
#define TIM3_CCMR2_CC3S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCMR2_CC3S_SHIFT)) & TIM3_CCMR2_CC3S_MASK)

/*!
 * @brief TIM3_CCER Register Bit Definition
 */

#define TIM3_CCER_CC4NP_SHIFT                   (15)
#define TIM3_CCER_CC4NP_MASK                    (0x01U << TIM3_CCER_CC4NP_SHIFT)
#define TIM3_CCER_CC4NP(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCER_CC4NP_SHIFT)) & TIM3_CCER_CC4NP_MASK)

#define TIM3_CCER_CC4P_SHIFT                    (13)
#define TIM3_CCER_CC4P_MASK                     (0x01U << TIM3_CCER_CC4P_SHIFT)
#define TIM3_CCER_CC4P(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_CCER_CC4P_SHIFT)) & TIM3_CCER_CC4P_MASK)

#define TIM3_CCER_CC4E_SHIFT                    (12)
#define TIM3_CCER_CC4E_MASK                     (0x01U << TIM3_CCER_CC4E_SHIFT)
#define TIM3_CCER_CC4E(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_CCER_CC4E_SHIFT)) & TIM3_CCER_CC4E_MASK)

#define TIM3_CCER_CC3NP_SHIFT                   (11)
#define TIM3_CCER_CC3NP_MASK                    (0x01U << TIM3_CCER_CC3NP_SHIFT)
#define TIM3_CCER_CC3NP(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCER_CC3NP_SHIFT)) & TIM3_CCER_CC3NP_MASK)

#define TIM3_CCER_CC3P_SHIFT                    (9)
#define TIM3_CCER_CC3P_MASK                     (0x01U << TIM3_CCER_CC3P_SHIFT)
#define TIM3_CCER_CC3P(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_CCER_CC3P_SHIFT)) & TIM3_CCER_CC3P_MASK)

#define TIM3_CCER_CC3E_SHIFT                    (8)
#define TIM3_CCER_CC3E_MASK                     (0x01U << TIM3_CCER_CC3E_SHIFT)
#define TIM3_CCER_CC3E(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_CCER_CC3E_SHIFT)) & TIM3_CCER_CC3E_MASK)

#define TIM3_CCER_CC2NP_SHIFT                   (7)
#define TIM3_CCER_CC2NP_MASK                    (0x01U << TIM3_CCER_CC2NP_SHIFT)
#define TIM3_CCER_CC2NP(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCER_CC2NP_SHIFT)) & TIM3_CCER_CC2NP_MASK)

#define TIM3_CCER_CC2P_SHIFT                    (5)
#define TIM3_CCER_CC2P_MASK                     (0x01U << TIM3_CCER_CC2P_SHIFT)
#define TIM3_CCER_CC2P(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_CCER_CC2P_SHIFT)) & TIM3_CCER_CC2P_MASK)

#define TIM3_CCER_CC2E_SHIFT                    (4)
#define TIM3_CCER_CC2E_MASK                     (0x01U << TIM3_CCER_CC2E_SHIFT)
#define TIM3_CCER_CC2E(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_CCER_CC2E_SHIFT)) & TIM3_CCER_CC2E_MASK)

#define TIM3_CCER_CC1NP_SHIFT                   (3)
#define TIM3_CCER_CC1NP_MASK                    (0x01U << TIM3_CCER_CC1NP_SHIFT)
#define TIM3_CCER_CC1NP(x)                      (((uint32_t)(((uint32_t)(x)) << TIM3_CCER_CC1NP_SHIFT)) & TIM3_CCER_CC1NP_MASK)

#define TIM3_CCER_CC1P_SHIFT                    (1)
#define TIM3_CCER_CC1P_MASK                     (0x01U << TIM3_CCER_CC1P_SHIFT)
#define TIM3_CCER_CC1P(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_CCER_CC1P_SHIFT)) & TIM3_CCER_CC1P_MASK)

#define TIM3_CCER_CC1E_SHIFT                    (0)
#define TIM3_CCER_CC1E_MASK                     (0x01U << TIM3_CCER_CC1E_SHIFT)
#define TIM3_CCER_CC1E(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_CCER_CC1E_SHIFT)) & TIM3_CCER_CC1E_MASK)

/*!
 * @brief TIM3_CNT Register Bit Definition
 */

#define TIM3_CNT_CNT_SHIFT                      (0)
#define TIM3_CNT_CNT_MASK                       (0xFFFFU << TIM3_CNT_CNT_SHIFT)
#define TIM3_CNT_CNT(x)                         (((uint32_t)(((uint32_t)(x)) << TIM3_CNT_CNT_SHIFT)) & TIM3_CNT_CNT_MASK)

/*!
 * @brief TIM3_PSC Register Bit Definition
 */

#define TIM3_PSC_PSC_SHIFT                      (0)
#define TIM3_PSC_PSC_MASK                       (0xFFFFU << TIM3_PSC_PSC_SHIFT)
#define TIM3_PSC_PSC(x)                         (((uint32_t)(((uint32_t)(x)) << TIM3_PSC_PSC_SHIFT)) & TIM3_PSC_PSC_MASK)

/*!
 * @brief TIM3_ARR Register Bit Definition
 */

#define TIM3_ARR_ARR_SHIFT                      (0)
#define TIM3_ARR_ARR_MASK                       (0xFFFFU << TIM3_ARR_ARR_SHIFT)
#define TIM3_ARR_ARR(x)                         (((uint32_t)(((uint32_t)(x)) << TIM3_ARR_ARR_SHIFT)) & TIM3_ARR_ARR_MASK)

/*!
 * @brief TIM3_CCR1 Register Bit Definition
 */

#define TIM3_CCR1_CCR1_SHIFT                    (0)
#define TIM3_CCR1_CCR1_MASK                     (0xFFFFU << TIM3_CCR1_CCR1_SHIFT)
#define TIM3_CCR1_CCR1(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_CCR1_CCR1_SHIFT)) & TIM3_CCR1_CCR1_MASK)

/*!
 * @brief TIM3_CCR2 Register Bit Definition
 */

#define TIM3_CCR2_CCR2_SHIFT                    (0)
#define TIM3_CCR2_CCR2_MASK                     (0xFFFFU << TIM3_CCR2_CCR2_SHIFT)
#define TIM3_CCR2_CCR2(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_CCR2_CCR2_SHIFT)) & TIM3_CCR2_CCR2_MASK)

/*!
 * @brief TIM3_CCR3 Register Bit Definition
 */

#define TIM3_CCR3_CCR3_SHIFT                    (0)
#define TIM3_CCR3_CCR3_MASK                     (0xFFFFU << TIM3_CCR3_CCR3_SHIFT)
#define TIM3_CCR3_CCR3(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_CCR3_CCR3_SHIFT)) & TIM3_CCR3_CCR3_MASK)

/*!
 * @brief TIM3_CCR4 Register Bit Definition
 */

#define TIM3_CCR4_CCR4_SHIFT                    (0)
#define TIM3_CCR4_CCR4_MASK                     (0xFFFFU << TIM3_CCR4_CCR4_SHIFT)
#define TIM3_CCR4_CCR4(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_CCR4_CCR4_SHIFT)) & TIM3_CCR4_CCR4_MASK)

/*!
 * @brief TIM3_DCR Register Bit Definition
 */

#define TIM3_DCR_DBL_SHIFT                      (8)
#define TIM3_DCR_DBL_MASK                       (0x1FU << TIM3_DCR_DBL_SHIFT)
#define TIM3_DCR_DBL(x)                         (((uint32_t)(((uint32_t)(x)) << TIM3_DCR_DBL_SHIFT)) & TIM3_DCR_DBL_MASK)

#define TIM3_DCR_DBA_SHIFT                      (0)
#define TIM3_DCR_DBA_MASK                       (0x1FU << TIM3_DCR_DBA_SHIFT)
#define TIM3_DCR_DBA(x)                         (((uint32_t)(((uint32_t)(x)) << TIM3_DCR_DBA_SHIFT)) & TIM3_DCR_DBA_MASK)

/*!
 * @brief TIM3_DMAR Register Bit Definition
 */

#define TIM3_DMAR_DMAB_SHIFT                    (0)
#define TIM3_DMAR_DMAB_MASK                     (0xFFFFU << TIM3_DMAR_DMAB_SHIFT)
#define TIM3_DMAR_DMAB(x)                       (((uint32_t)(((uint32_t)(x)) << TIM3_DMAR_DMAB_SHIFT)) & TIM3_DMAR_DMAB_MASK)

/*!
 * @}
 */ /* end of group TIM3_Register_Masks */
/******************************************************************************
 * TIM3/4 Instance
******************************************************************************/
#define TIM3                                ((TIM3_Type*)TIM3_BASE)
#define TIM4                                ((TIM3_Type*)TIM4_BASE)

/*!
 * @}
 */ /* end of group TIM3_Peripheral_Access_Layer */



/*!
 * @addtogroup TIM2_Peripheral_Access_Layer TIM2 Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * TIM2 Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CR1;                                                            ///< Control register 1                           offset: 0x00
    __IO uint32_t CR2;                                                            ///< Control register 2                           offset: 0x04
    __IO uint32_t SMCR;                                                           ///< Slave mode control register                  offset: 0x08
    __IO uint32_t DIER;                                                           ///< DMA/interrupt enable register                offset: 0x0C
    __IO uint32_t SR;                                                             ///< Status register                              offset: 0x10
    __IO uint32_t EGR;                                                            ///< Event generation register                    offset: 0x14
    __IO uint32_t CCMR1;                                                          ///<                                              offset: 0x18
    __IO uint32_t CCMR2;                                                          ///<                                              offset: 0x1C
    __IO uint32_t CCER;                                                           ///< Capture/compare enable register              offset: 0x20
    __IO uint32_t CNT;                                                            ///< Counter                                      offset: 0x24
    __IO uint32_t PSC;                                                            ///< Prescaler                                    offset: 0x28
    __IO uint32_t ARR;                                                            ///< Autoload register                            offset: 0x2C
    __IO uint32_t Reserved10[1];                                                   ///< Reserved
    __IO uint32_t CCR[4];
//    __IO uint32_t CCR1;                                                           ///< Capture/compare register 1                   offset: 0x34
//    __IO uint32_t CCR2;                                                           ///< Capture/compare register 2                   offset: 0x38
//    __IO uint32_t CCR3;                                                           ///< Capture/compare register 3                   offset: 0x3C
//    __IO uint32_t CCR4;                                                           ///< Capture/compare register 4                   offset: 0x40
    __IO uint32_t Reserved11[1];                                                   ///< Reserved
    __IO uint32_t DCR;                                                            ///< DMA control register                         offset: 0x48
    __IO uint32_t DMAR;                                                           ///< DMA address in continuous mode               offset: 0x4C
    __IO uint32_t OR;                                                             ///< TIMERx option register                       offset: 0x50
} TIM2_Type;

/*******************************************************************************
 * TIM2 Type
 ******************************************************************************/

/*!
 * @addtogroup TIM2_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief TIM2_CR1 Register Bit Definition
 */

#define TIM2_CR1_CKD_SHIFT                      (8)
#define TIM2_CR1_CKD_MASK                       (0x3U << TIM2_CR1_CKD_SHIFT)
#define TIM2_CR1_CKD(x)                         (((uint32_t)(((uint32_t)(x)) << TIM2_CR1_CKD_SHIFT)) & TIM2_CR1_CKD_MASK)

#define TIM2_CR1_APRE_SHIFT                     (7)
#define TIM2_CR1_APRE_MASK                      (0x01U << TIM2_CR1_APRE_SHIFT)
#define TIM2_CR1_APRE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_CR1_APRE_SHIFT)) & TIM2_CR1_APRE_MASK)

#define TIM2_CR1_CMS_SHIFT                      (5)
#define TIM2_CR1_CMS_MASK                       (0x3U << TIM2_CR1_CMS_SHIFT)
#define TIM2_CR1_CMS(x)                         (((uint32_t)(((uint32_t)(x)) << TIM2_CR1_CMS_SHIFT)) & TIM2_CR1_CMS_MASK)

#define TIM2_CR1_DIR_SHIFT                      (4)
#define TIM2_CR1_DIR_MASK                       (0x01U << TIM2_CR1_DIR_SHIFT)
#define TIM2_CR1_DIR(x)                         (((uint32_t)(((uint32_t)(x)) << TIM2_CR1_DIR_SHIFT)) & TIM2_CR1_DIR_MASK)

#define TIM2_CR1_OPM_SHIFT                      (3)
#define TIM2_CR1_OPM_MASK                       (0x01U << TIM2_CR1_OPM_SHIFT)
#define TIM2_CR1_OPM(x)                         (((uint32_t)(((uint32_t)(x)) << TIM2_CR1_OPM_SHIFT)) & TIM2_CR1_OPM_MASK)

#define TIM2_CR1_URS_SHIFT                      (2)
#define TIM2_CR1_URS_MASK                       (0x01U << TIM2_CR1_URS_SHIFT)
#define TIM2_CR1_URS(x)                         (((uint32_t)(((uint32_t)(x)) << TIM2_CR1_URS_SHIFT)) & TIM2_CR1_URS_MASK)

#define TIM2_CR1_UDIS_SHIFT                     (1)
#define TIM2_CR1_UDIS_MASK                      (0x01U << TIM2_CR1_UDIS_SHIFT)
#define TIM2_CR1_UDIS(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_CR1_UDIS_SHIFT)) & TIM2_CR1_UDIS_MASK)

#define TIM2_CR1_CEN_SHIFT                      (0)
#define TIM2_CR1_CEN_MASK                       (0x01U << TIM2_CR1_CEN_SHIFT)
#define TIM2_CR1_CEN(x)                         (((uint32_t)(((uint32_t)(x)) << TIM2_CR1_CEN_SHIFT)) & TIM2_CR1_CEN_MASK)

/*!
 * @brief TIM2_CR2 Register Bit Definition
 */

#define TIM2_CR2_TI1S_SHIFT                     (7)
#define TIM2_CR2_TI1S_MASK                      (0x01U << TIM2_CR2_TI1S_SHIFT)
#define TIM2_CR2_TI1S(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_CR2_TI1S_SHIFT)) & TIM2_CR2_TI1S_MASK)

#define TIM2_CR2_MMS_SHIFT                      (4)
#define TIM2_CR2_MMS_MASK                       (0x7U << TIM2_CR2_MMS_SHIFT)
#define TIM2_CR2_MMS(x)                         (((uint32_t)(((uint32_t)(x)) << TIM2_CR2_MMS_SHIFT)) & TIM2_CR2_MMS_MASK)

#define TIM2_CR2_CCDS_SHIFT                     (3)
#define TIM2_CR2_CCDS_MASK                      (0x01U << TIM2_CR2_CCDS_SHIFT)
#define TIM2_CR2_CCDS(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_CR2_CCDS_SHIFT)) & TIM2_CR2_CCDS_MASK)

/*!
 * @brief TIM2_SMCR Register Bit Definition
 */

#define TIM2_SMCR_ETP_SHIFT                     (15)
#define TIM2_SMCR_ETP_MASK                      (0x01U << TIM2_SMCR_ETP_SHIFT)
#define TIM2_SMCR_ETP(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_SMCR_ETP_SHIFT)) & TIM2_SMCR_ETP_MASK)

#define TIM2_SMCR_ECE_SHIFT                     (14)
#define TIM2_SMCR_ECE_MASK                      (0x01U << TIM2_SMCR_ECE_SHIFT)
#define TIM2_SMCR_ECE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_SMCR_ECE_SHIFT)) & TIM2_SMCR_ECE_MASK)

#define TIM2_SMCR_ETPS_SHIFT                    (12)
#define TIM2_SMCR_ETPS_MASK                     (0x3U << TIM2_SMCR_ETPS_SHIFT)
#define TIM2_SMCR_ETPS(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_SMCR_ETPS_SHIFT)) & TIM2_SMCR_ETPS_MASK)

#define TIM2_SMCR_ETF_SHIFT                     (8)
#define TIM2_SMCR_ETF_MASK                      (0xFU << TIM2_SMCR_ETF_SHIFT)
#define TIM2_SMCR_ETF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_SMCR_ETF_SHIFT)) & TIM2_SMCR_ETF_MASK)

#define TIM2_SMCR_MSM_SHIFT                     (7)
#define TIM2_SMCR_MSM_MASK                      (0x01U << TIM2_SMCR_MSM_SHIFT)
#define TIM2_SMCR_MSM(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_SMCR_MSM_SHIFT)) & TIM2_SMCR_MSM_MASK)

#define TIM2_SMCR_TS_SHIFT                      (4)
#define TIM2_SMCR_TS_MASK                       (0x7U << TIM2_SMCR_TS_SHIFT)
#define TIM2_SMCR_TS(x)                         (((uint32_t)(((uint32_t)(x)) << TIM2_SMCR_TS_SHIFT)) & TIM2_SMCR_TS_MASK)

#define TIM2_SMCR_OCCS_SHIFT                    (3)
#define TIM2_SMCR_OCCS_MASK                     (0x01U << TIM2_SMCR_OCCS_SHIFT)
#define TIM2_SMCR_OCCS(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_SMCR_OCCS_SHIFT)) & TIM2_SMCR_OCCS_MASK)

#define TIM2_SMCR_SMS_SHIFT                     (0)
#define TIM2_SMCR_SMS_MASK                      (0x7U << TIM2_SMCR_SMS_SHIFT)
#define TIM2_SMCR_SMS(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_SMCR_SMS_SHIFT)) & TIM2_SMCR_SMS_MASK)

/*!
 * @brief TIM2_DIER Register Bit Definition
 */

#define TIM2_DIER_TDE_SHIFT                     (14)
#define TIM2_DIER_TDE_MASK                      (0x01U << TIM2_DIER_TDE_SHIFT)
#define TIM2_DIER_TDE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_DIER_TDE_SHIFT)) & TIM2_DIER_TDE_MASK)

#define TIM2_DIER_CC4DE_SHIFT                   (12)
#define TIM2_DIER_CC4DE_MASK                    (0x01U << TIM2_DIER_CC4DE_SHIFT)
#define TIM2_DIER_CC4DE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_DIER_CC4DE_SHIFT)) & TIM2_DIER_CC4DE_MASK)

#define TIM2_DIER_CC3DE_SHIFT                   (11)
#define TIM2_DIER_CC3DE_MASK                    (0x01U << TIM2_DIER_CC3DE_SHIFT)
#define TIM2_DIER_CC3DE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_DIER_CC3DE_SHIFT)) & TIM2_DIER_CC3DE_MASK)

#define TIM2_DIER_CC2DE_SHIFT                   (10)
#define TIM2_DIER_CC2DE_MASK                    (0x01U << TIM2_DIER_CC2DE_SHIFT)
#define TIM2_DIER_CC2DE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_DIER_CC2DE_SHIFT)) & TIM2_DIER_CC2DE_MASK)

#define TIM2_DIER_CC1DE_SHIFT                   (9)
#define TIM2_DIER_CC1DE_MASK                    (0x01U << TIM2_DIER_CC1DE_SHIFT)
#define TIM2_DIER_CC1DE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_DIER_CC1DE_SHIFT)) & TIM2_DIER_CC1DE_MASK)

#define TIM2_DIER_UDE_SHIFT                     (8)
#define TIM2_DIER_UDE_MASK                      (0x01U << TIM2_DIER_UDE_SHIFT)
#define TIM2_DIER_UDE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_DIER_UDE_SHIFT)) & TIM2_DIER_UDE_MASK)

#define TIM2_DIER_TIE_SHIFT                     (6)
#define TIM2_DIER_TIE_MASK                      (0x01U << TIM2_DIER_TIE_SHIFT)
#define TIM2_DIER_TIE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_DIER_TIE_SHIFT)) & TIM2_DIER_TIE_MASK)

#define TIM2_DIER_CC4IE_SHIFT                   (4)
#define TIM2_DIER_CC4IE_MASK                    (0x01U << TIM2_DIER_CC4IE_SHIFT)
#define TIM2_DIER_CC4IE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_DIER_CC4IE_SHIFT)) & TIM2_DIER_CC4IE_MASK)

#define TIM2_DIER_CC3IE_SHIFT                   (3)
#define TIM2_DIER_CC3IE_MASK                    (0x01U << TIM2_DIER_CC3IE_SHIFT)
#define TIM2_DIER_CC3IE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_DIER_CC3IE_SHIFT)) & TIM2_DIER_CC3IE_MASK)

#define TIM2_DIER_CC2IE_SHIFT                   (2)
#define TIM2_DIER_CC2IE_MASK                    (0x01U << TIM2_DIER_CC2IE_SHIFT)
#define TIM2_DIER_CC2IE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_DIER_CC2IE_SHIFT)) & TIM2_DIER_CC2IE_MASK)

#define TIM2_DIER_CC1IE_SHIFT                   (1)
#define TIM2_DIER_CC1IE_MASK                    (0x01U << TIM2_DIER_CC1IE_SHIFT)
#define TIM2_DIER_CC1IE(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_DIER_CC1IE_SHIFT)) & TIM2_DIER_CC1IE_MASK)

#define TIM2_DIER_UIE_SHIFT                     (0)
#define TIM2_DIER_UIE_MASK                      (0x01U << TIM2_DIER_UIE_SHIFT)
#define TIM2_DIER_UIE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_DIER_UIE_SHIFT)) & TIM2_DIER_UIE_MASK)

/*!
 * @brief TIM2_SR Register Bit Definition
 */

#define TIM2_SR_CC4OF_SHIFT                     (12)
#define TIM2_SR_CC4OF_MASK                      (0x01U << TIM2_SR_CC4OF_SHIFT)
#define TIM2_SR_CC4OF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_SR_CC4OF_SHIFT)) & TIM2_SR_CC4OF_MASK)

#define TIM2_SR_CC3OF_SHIFT                     (11)
#define TIM2_SR_CC3OF_MASK                      (0x01U << TIM2_SR_CC3OF_SHIFT)
#define TIM2_SR_CC3OF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_SR_CC3OF_SHIFT)) & TIM2_SR_CC3OF_MASK)

#define TIM2_SR_CC2OF_SHIFT                     (10)
#define TIM2_SR_CC2OF_MASK                      (0x01U << TIM2_SR_CC2OF_SHIFT)
#define TIM2_SR_CC2OF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_SR_CC2OF_SHIFT)) & TIM2_SR_CC2OF_MASK)

#define TIM2_SR_CC1OF_SHIFT                     (9)
#define TIM2_SR_CC1OF_MASK                      (0x01U << TIM2_SR_CC1OF_SHIFT)
#define TIM2_SR_CC1OF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_SR_CC1OF_SHIFT)) & TIM2_SR_CC1OF_MASK)

#define TIM2_SR_TIF_SHIFT                       (6)
#define TIM2_SR_TIF_MASK                        (0x01U << TIM2_SR_TIF_SHIFT)
#define TIM2_SR_TIF(x)                          (((uint32_t)(((uint32_t)(x)) << TIM2_SR_TIF_SHIFT)) & TIM2_SR_TIF_MASK)

#define TIM2_SR_CC4IF_SHIFT                     (4)
#define TIM2_SR_CC4IF_MASK                      (0x01U << TIM2_SR_CC4IF_SHIFT)
#define TIM2_SR_CC4IF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_SR_CC4IF_SHIFT)) & TIM2_SR_CC4IF_MASK)

#define TIM2_SR_CC3IF_SHIFT                     (3)
#define TIM2_SR_CC3IF_MASK                      (0x01U << TIM2_SR_CC3IF_SHIFT)
#define TIM2_SR_CC3IF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_SR_CC3IF_SHIFT)) & TIM2_SR_CC3IF_MASK)

#define TIM2_SR_CC2IF_SHIFT                     (2)
#define TIM2_SR_CC2IF_MASK                      (0x01U << TIM2_SR_CC2IF_SHIFT)
#define TIM2_SR_CC2IF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_SR_CC2IF_SHIFT)) & TIM2_SR_CC2IF_MASK)

#define TIM2_SR_CC1IF_SHIFT                     (1)
#define TIM2_SR_CC1IF_MASK                      (0x01U << TIM2_SR_CC1IF_SHIFT)
#define TIM2_SR_CC1IF(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_SR_CC1IF_SHIFT)) & TIM2_SR_CC1IF_MASK)

#define TIM2_SR_UIF_SHIFT                       (0)
#define TIM2_SR_UIF_MASK                        (0x01U << TIM2_SR_UIF_SHIFT)
#define TIM2_SR_UIF(x)                          (((uint32_t)(((uint32_t)(x)) << TIM2_SR_UIF_SHIFT)) & TIM2_SR_UIF_MASK)

/*!
 * @brief TIM2_EGR Register Bit Definition
 */

#define TIM2_EGR_TG_SHIFT                       (6)
#define TIM2_EGR_TG_MASK                        (0x01U << TIM2_EGR_TG_SHIFT)
#define TIM2_EGR_TG(x)                          (((uint32_t)(((uint32_t)(x)) << TIM2_EGR_TG_SHIFT)) & TIM2_EGR_TG_MASK)

#define TIM2_EGR_COMG_SHIFT                     (5)
#define TIM2_EGR_COMG_MASK                      (0x01U << TIM2_EGR_COMG_SHIFT)
#define TIM2_EGR_COMG(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_EGR_COMG_SHIFT)) & TIM2_EGR_COMG_MASK)

#define TIM2_EGR_CC4G_SHIFT                     (4)
#define TIM2_EGR_CC4G_MASK                      (0x01U << TIM2_EGR_CC4G_SHIFT)
#define TIM2_EGR_CC4G(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_EGR_CC4G_SHIFT)) & TIM2_EGR_CC4G_MASK)

#define TIM2_EGR_CC3G_SHIFT                     (3)
#define TIM2_EGR_CC3G_MASK                      (0x01U << TIM2_EGR_CC3G_SHIFT)
#define TIM2_EGR_CC3G(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_EGR_CC3G_SHIFT)) & TIM2_EGR_CC3G_MASK)

#define TIM2_EGR_CC2G_SHIFT                     (2)
#define TIM2_EGR_CC2G_MASK                      (0x01U << TIM2_EGR_CC2G_SHIFT)
#define TIM2_EGR_CC2G(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_EGR_CC2G_SHIFT)) & TIM2_EGR_CC2G_MASK)

#define TIM2_EGR_CC1G_SHIFT                     (1)
#define TIM2_EGR_CC1G_MASK                      (0x01U << TIM2_EGR_CC1G_SHIFT)
#define TIM2_EGR_CC1G(x)                        (((uint32_t)(((uint32_t)(x)) << TIM2_EGR_CC1G_SHIFT)) & TIM2_EGR_CC1G_MASK)

#define TIM2_EGR_UG_SHIFT                       (0)
#define TIM2_EGR_UG_MASK                        (0x01U << TIM2_EGR_UG_SHIFT)
#define TIM2_EGR_UG(x)                          (((uint32_t)(((uint32_t)(x)) << TIM2_EGR_UG_SHIFT)) & TIM2_EGR_UG_MASK)

/*!
 * @brief TIM2_CCMR1 Register Bit Definition
 */

#define TIM2_CCMR1_OC2CE_SHIFT                  (15)
#define TIM2_CCMR1_OC2CE_MASK                   (0x01U << TIM2_CCMR1_OC2CE_SHIFT)
#define TIM2_CCMR1_OC2CE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_OC2CE_SHIFT)) & TIM2_CCMR1_OC2CE_MASK)

#define TIM2_CCMR1_OC2M_SHIFT                   (12)
#define TIM2_CCMR1_OC2M_MASK                    (0x7U << TIM2_CCMR1_OC2M_SHIFT)
#define TIM2_CCMR1_OC2M(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_OC2M_SHIFT)) & TIM2_CCMR1_OC2M_MASK)

#define TIM2_CCMR1_OC2PE_SHIFT                  (11)
#define TIM2_CCMR1_OC2PE_MASK                   (0x01U << TIM2_CCMR1_OC2PE_SHIFT)
#define TIM2_CCMR1_OC2PE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_OC2PE_SHIFT)) & TIM2_CCMR1_OC2PE_MASK)

#define TIM2_CCMR1_OC2FE_SHIFT                  (10)
#define TIM2_CCMR1_OC2FE_MASK                   (0x01U << TIM2_CCMR1_OC2FE_SHIFT)
#define TIM2_CCMR1_OC2FE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_OC2FE_SHIFT)) & TIM2_CCMR1_OC2FE_MASK)

#define TIM2_CCMR1_CC2S_SHIFT                   (8)
#define TIM2_CCMR1_CC2S_MASK                    (0x3U << TIM2_CCMR1_CC2S_SHIFT)
#define TIM2_CCMR1_CC2S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_CC2S_SHIFT)) & TIM2_CCMR1_CC2S_MASK)

#define TIM2_CCMR1_OC1CE_SHIFT                  (7)
#define TIM2_CCMR1_OC1CE_MASK                   (0x01U << TIM2_CCMR1_OC1CE_SHIFT)
#define TIM2_CCMR1_OC1CE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_OC1CE_SHIFT)) & TIM2_CCMR1_OC1CE_MASK)

#define TIM2_CCMR1_OC1M_SHIFT                   (4)
#define TIM2_CCMR1_OC1M_MASK                    (0x7U << TIM2_CCMR1_OC1M_SHIFT)
#define TIM2_CCMR1_OC1M(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_OC1M_SHIFT)) & TIM2_CCMR1_OC1M_MASK)

#define TIM2_CCMR1_OC1PE_SHIFT                  (3)
#define TIM2_CCMR1_OC1PE_MASK                   (0x01U << TIM2_CCMR1_OC1PE_SHIFT)
#define TIM2_CCMR1_OC1PE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_OC1PE_SHIFT)) & TIM2_CCMR1_OC1PE_MASK)

#define TIM2_CCMR1_OC1FE_SHIFT                  (2)
#define TIM2_CCMR1_OC1FE_MASK                   (0x01U << TIM2_CCMR1_OC1FE_SHIFT)
#define TIM2_CCMR1_OC1FE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_OC1FE_SHIFT)) & TIM2_CCMR1_OC1FE_MASK)

#define TIM2_CCMR1_CC1S_SHIFT                   (0)
#define TIM2_CCMR1_CC1S_MASK                    (0x3U << TIM2_CCMR1_CC1S_SHIFT)
#define TIM2_CCMR1_CC1S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_CC1S_SHIFT)) & TIM2_CCMR1_CC1S_MASK)

/*!
 * @brief TIM2_CCMR1 Register Bit Definition
 */

#define TIM2_CCMR1_IC2F_SHIFT                   (12)
#define TIM2_CCMR1_IC2F_MASK                    (0xFU << TIM2_CCMR1_IC2F_SHIFT)
#define TIM2_CCMR1_IC2F(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_IC2F_SHIFT)) & TIM2_CCMR1_IC2F_MASK)

#define TIM2_CCMR1_IC2PSC_SHIFT                 (10)
#define TIM2_CCMR1_IC2PSC_MASK                  (0x3U << TIM2_CCMR1_IC2PSC_SHIFT)
#define TIM2_CCMR1_IC2PSC(x)                    (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_IC2PSC_SHIFT)) & TIM2_CCMR1_IC2PSC_MASK)

#define TIM2_CCMR1_CC2S_SHIFT                   (8)
#define TIM2_CCMR1_CC2S_MASK                    (0x3U << TIM2_CCMR1_CC2S_SHIFT)
#define TIM2_CCMR1_CC2S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_CC2S_SHIFT)) & TIM2_CCMR1_CC2S_MASK)

#define TIM2_CCMR1_IC1F_SHIFT                   (4)
#define TIM2_CCMR1_IC1F_MASK                    (0xFU << TIM2_CCMR1_IC1F_SHIFT)
#define TIM2_CCMR1_IC1F(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_IC1F_SHIFT)) & TIM2_CCMR1_IC1F_MASK)

#define TIM2_CCMR1_IC1PSC_SHIFT                 (2)
#define TIM2_CCMR1_IC1PSC_MASK                  (0x3U << TIM2_CCMR1_IC1PSC_SHIFT)
#define TIM2_CCMR1_IC1PSC(x)                    (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_IC1PSC_SHIFT)) & TIM2_CCMR1_IC1PSC_MASK)

#define TIM2_CCMR1_CC1S_SHIFT                   (0)
#define TIM2_CCMR1_CC1S_MASK                    (0x3U << TIM2_CCMR1_CC1S_SHIFT)
#define TIM2_CCMR1_CC1S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR1_CC1S_SHIFT)) & TIM2_CCMR1_CC1S_MASK)

/*!
 * @brief TIM2_CCMR2 Register Bit Definition
 */

#define TIM2_CCMR2_OC4CE_SHIFT                  (15)
#define TIM2_CCMR2_OC4CE_MASK                   (0x01U << TIM2_CCMR2_OC4CE_SHIFT)
#define TIM2_CCMR2_OC4CE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_OC4CE_SHIFT)) & TIM2_CCMR2_OC4CE_MASK)

#define TIM2_CCMR2_OC4M_SHIFT                   (12)
#define TIM2_CCMR2_OC4M_MASK                    (0x7U << TIM2_CCMR2_OC4M_SHIFT)
#define TIM2_CCMR2_OC4M(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_OC4M_SHIFT)) & TIM2_CCMR2_OC4M_MASK)

#define TIM2_CCMR2_OC4PE_SHIFT                  (11)
#define TIM2_CCMR2_OC4PE_MASK                   (0x01U << TIM2_CCMR2_OC4PE_SHIFT)
#define TIM2_CCMR2_OC4PE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_OC4PE_SHIFT)) & TIM2_CCMR2_OC4PE_MASK)

#define TIM2_CCMR2_OC4FE_SHIFT                  (10)
#define TIM2_CCMR2_OC4FE_MASK                   (0x01U << TIM2_CCMR2_OC4FE_SHIFT)
#define TIM2_CCMR2_OC4FE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_OC4FE_SHIFT)) & TIM2_CCMR2_OC4FE_MASK)

#define TIM2_CCMR2_CC4S_SHIFT                   (8)
#define TIM2_CCMR2_CC4S_MASK                    (0x3U << TIM2_CCMR2_CC4S_SHIFT)
#define TIM2_CCMR2_CC4S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_CC4S_SHIFT)) & TIM2_CCMR2_CC4S_MASK)

#define TIM2_CCMR2_OC3CE_SHIFT                  (7)
#define TIM2_CCMR2_OC3CE_MASK                   (0x01U << TIM2_CCMR2_OC3CE_SHIFT)
#define TIM2_CCMR2_OC3CE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_OC3CE_SHIFT)) & TIM2_CCMR2_OC3CE_MASK)

#define TIM2_CCMR2_OC3M_SHIFT                   (4)
#define TIM2_CCMR2_OC3M_MASK                    (0x7U << TIM2_CCMR2_OC3M_SHIFT)
#define TIM2_CCMR2_OC3M(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_OC3M_SHIFT)) & TIM2_CCMR2_OC3M_MASK)

#define TIM2_CCMR2_OC3PE_SHIFT                  (3)
#define TIM2_CCMR2_OC3PE_MASK                   (0x01U << TIM2_CCMR2_OC3PE_SHIFT)
#define TIM2_CCMR2_OC3PE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_OC3PE_SHIFT)) & TIM2_CCMR2_OC3PE_MASK)

#define TIM2_CCMR2_OC3FE_SHIFT                  (2)
#define TIM2_CCMR2_OC3FE_MASK                   (0x01U << TIM2_CCMR2_OC3FE_SHIFT)
#define TIM2_CCMR2_OC3FE(x)                     (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_OC3FE_SHIFT)) & TIM2_CCMR2_OC3FE_MASK)

#define TIM2_CCMR2_CC3S_SHIFT                   (0)
#define TIM2_CCMR2_CC3S_MASK                    (0x3U << TIM2_CCMR2_CC3S_SHIFT)
#define TIM2_CCMR2_CC3S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_CC3S_SHIFT)) & TIM2_CCMR2_CC3S_MASK)

/*!
 * @brief TIM2_CCMR2 Register Bit Definition
 */

#define TIM2_CCMR2_IC4F_SHIFT                   (12)
#define TIM2_CCMR2_IC4F_MASK                    (0xFU << TIM2_CCMR2_IC4F_SHIFT)
#define TIM2_CCMR2_IC4F(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_IC4F_SHIFT)) & TIM2_CCMR2_IC4F_MASK)

#define TIM2_CCMR2_IC4PSC_SHIFT                 (10)
#define TIM2_CCMR2_IC4PSC_MASK                  (0x3U << TIM2_CCMR2_IC4PSC_SHIFT)
#define TIM2_CCMR2_IC4PSC(x)                    (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_IC4PSC_SHIFT)) & TIM2_CCMR2_IC4PSC_MASK)

#define TIM2_CCMR2_CC4S_SHIFT                   (8)
#define TIM2_CCMR2_CC4S_MASK                    (0x3U << TIM2_CCMR2_CC4S_SHIFT)
#define TIM2_CCMR2_CC4S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_CC4S_SHIFT)) & TIM2_CCMR2_CC4S_MASK)

#define TIM2_CCMR2_IC3F_SHIFT                   (4)
#define TIM2_CCMR2_IC3F_MASK                    (0xFU << TIM2_CCMR2_IC3F_SHIFT)
#define TIM2_CCMR2_IC3F(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_IC3F_SHIFT)) & TIM2_CCMR2_IC3F_MASK)

#define TIM2_CCMR2_IC3PSC_SHIFT                 (2)
#define TIM2_CCMR2_IC3PSC_MASK                  (0x3U << TIM2_CCMR2_IC3PSC_SHIFT)
#define TIM2_CCMR2_IC3PSC(x)                    (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_IC3PSC_SHIFT)) & TIM2_CCMR2_IC3PSC_MASK)

#define TIM2_CCMR2_CC3S_SHIFT                   (0)
#define TIM2_CCMR2_CC3S_MASK                    (0x3U << TIM2_CCMR2_CC3S_SHIFT)
#define TIM2_CCMR2_CC3S(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCMR2_CC3S_SHIFT)) & TIM2_CCMR2_CC3S_MASK)

/*!
 * @brief TIM2_CCER Register Bit Definition
 */

#define TIM2_CCER_CC4NP_SHIFT                   (15)
#define TIM2_CCER_CC4NP_MASK                    (0x01U << TIM2_CCER_CC4NP_SHIFT)
#define TIM2_CCER_CC4NP(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCER_CC4NP_SHIFT)) & TIM2_CCER_CC4NP_MASK)

#define TIM2_CCER_CC4P_SHIFT                    (13)
#define TIM2_CCER_CC4P_MASK                     (0x01U << TIM2_CCER_CC4P_SHIFT)
#define TIM2_CCER_CC4P(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_CCER_CC4P_SHIFT)) & TIM2_CCER_CC4P_MASK)

#define TIM2_CCER_CC4E_SHIFT                    (12)
#define TIM2_CCER_CC4E_MASK                     (0x01U << TIM2_CCER_CC4E_SHIFT)
#define TIM2_CCER_CC4E(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_CCER_CC4E_SHIFT)) & TIM2_CCER_CC4E_MASK)

#define TIM2_CCER_CC3NP_SHIFT                   (11)
#define TIM2_CCER_CC3NP_MASK                    (0x01U << TIM2_CCER_CC3NP_SHIFT)
#define TIM2_CCER_CC3NP(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCER_CC3NP_SHIFT)) & TIM2_CCER_CC3NP_MASK)

#define TIM2_CCER_CC3P_SHIFT                    (9)
#define TIM2_CCER_CC3P_MASK                     (0x01U << TIM2_CCER_CC3P_SHIFT)
#define TIM2_CCER_CC3P(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_CCER_CC3P_SHIFT)) & TIM2_CCER_CC3P_MASK)

#define TIM2_CCER_CC3E_SHIFT                    (8)
#define TIM2_CCER_CC3E_MASK                     (0x01U << TIM2_CCER_CC3E_SHIFT)
#define TIM2_CCER_CC3E(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_CCER_CC3E_SHIFT)) & TIM2_CCER_CC3E_MASK)

#define TIM2_CCER_CC2NP_SHIFT                   (7)
#define TIM2_CCER_CC2NP_MASK                    (0x01U << TIM2_CCER_CC2NP_SHIFT)
#define TIM2_CCER_CC2NP(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCER_CC2NP_SHIFT)) & TIM2_CCER_CC2NP_MASK)

#define TIM2_CCER_CC2P_SHIFT                    (5)
#define TIM2_CCER_CC2P_MASK                     (0x01U << TIM2_CCER_CC2P_SHIFT)
#define TIM2_CCER_CC2P(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_CCER_CC2P_SHIFT)) & TIM2_CCER_CC2P_MASK)

#define TIM2_CCER_CC2E_SHIFT                    (4)
#define TIM2_CCER_CC2E_MASK                     (0x01U << TIM2_CCER_CC2E_SHIFT)
#define TIM2_CCER_CC2E(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_CCER_CC2E_SHIFT)) & TIM2_CCER_CC2E_MASK)

#define TIM2_CCER_CC1NP_SHIFT                   (3)
#define TIM2_CCER_CC1NP_MASK                    (0x01U << TIM2_CCER_CC1NP_SHIFT)
#define TIM2_CCER_CC1NP(x)                      (((uint32_t)(((uint32_t)(x)) << TIM2_CCER_CC1NP_SHIFT)) & TIM2_CCER_CC1NP_MASK)

#define TIM2_CCER_CC1P_SHIFT                    (1)
#define TIM2_CCER_CC1P_MASK                     (0x01U << TIM2_CCER_CC1P_SHIFT)
#define TIM2_CCER_CC1P(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_CCER_CC1P_SHIFT)) & TIM2_CCER_CC1P_MASK)

#define TIM2_CCER_CC1E_SHIFT                    (0)
#define TIM2_CCER_CC1E_MASK                     (0x01U << TIM2_CCER_CC1E_SHIFT)
#define TIM2_CCER_CC1E(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_CCER_CC1E_SHIFT)) & TIM2_CCER_CC1E_MASK)

/*!
 * @brief TIM2_CNT Register Bit Definition
 */

#define TIM2_CNT_CNT_SHIFT                      (0)
#define TIM2_CNT_CNT_MASK                       (0xFFFFFFFFU << TIM2_CNT_CNT_SHIFT)
#define TIM2_CNT_CNT(x)                         (((uint32_t)(((uint32_t)(x)) << TIM2_CNT_CNT_SHIFT)) & TIM2_CNT_CNT_MASK)

/*!
 * @brief TIM2_PSC Register Bit Definition
 */

#define TIM2_PSC_PSC_SHIFT                      (0)
#define TIM2_PSC_PSC_MASK                       (0xFFFFU << TIM2_PSC_PSC_SHIFT)
#define TIM2_PSC_PSC(x)                         (((uint32_t)(((uint32_t)(x)) << TIM2_PSC_PSC_SHIFT)) & TIM2_PSC_PSC_MASK)

/*!
 * @brief TIM2_ARR Register Bit Definition
 */

#define TIM2_ARR_ARR_SHIFT                      (0)
#define TIM2_ARR_ARR_MASK                       (0xFFFFFFFFU << TIM2_ARR_ARR_SHIFT)
#define TIM2_ARR_ARR(x)                         (((uint32_t)(((uint32_t)(x)) << TIM2_ARR_ARR_SHIFT)) & TIM2_ARR_ARR_MASK)

/*!
 * @brief TIM2_CCR1 Register Bit Definition
 */

#define TIM2_CCR1_CCR1_SHIFT                    (0)
#define TIM2_CCR1_CCR1_MASK                     (0xFFFFFFFFU << TIM2_CCR1_CCR1_SHIFT)
#define TIM2_CCR1_CCR1(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_CCR1_CCR1_SHIFT)) & TIM2_CCR1_CCR1_MASK)

/*!
 * @brief TIM2_CCR2 Register Bit Definition
 */

#define TIM2_CCR2_CCR2_SHIFT                    (0)
#define TIM2_CCR2_CCR2_MASK                     (0xFFFFFFFFU << TIM2_CCR2_CCR2_SHIFT)
#define TIM2_CCR2_CCR2(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_CCR2_CCR2_SHIFT)) & TIM2_CCR2_CCR2_MASK)

/*!
 * @brief TIM2_CCR3 Register Bit Definition
 */

#define TIM2_CCR3_CCR3_SHIFT                    (0)
#define TIM2_CCR3_CCR3_MASK                     (0xFFFFFFFFU << TIM2_CCR3_CCR3_SHIFT)
#define TIM2_CCR3_CCR3(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_CCR3_CCR3_SHIFT)) & TIM2_CCR3_CCR3_MASK)

/*!
 * @brief TIM2_CCR4 Register Bit Definition
 */

#define TIM2_CCR4_CCR4_SHIFT                    (0)
#define TIM2_CCR4_CCR4_MASK                     (0xFFFFFFFFU << TIM2_CCR4_CCR4_SHIFT)
#define TIM2_CCR4_CCR4(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_CCR4_CCR4_SHIFT)) & TIM2_CCR4_CCR4_MASK)

/*!
 * @brief TIM2_DCR Register Bit Definition
 */

#define TIM2_DCR_DBL_SHIFT                      (8)
#define TIM2_DCR_DBL_MASK                       (0x1FU << TIM2_DCR_DBL_SHIFT)
#define TIM2_DCR_DBL(x)                         (((uint32_t)(((uint32_t)(x)) << TIM2_DCR_DBL_SHIFT)) & TIM2_DCR_DBL_MASK)

#define TIM2_DCR_DBA_SHIFT                      (0)
#define TIM2_DCR_DBA_MASK                       (0x1FU << TIM2_DCR_DBA_SHIFT)
#define TIM2_DCR_DBA(x)                         (((uint32_t)(((uint32_t)(x)) << TIM2_DCR_DBA_SHIFT)) & TIM2_DCR_DBA_MASK)

/*!
 * @brief TIM2_DMAR Register Bit Definition
 */

#define TIM2_DMAR_DMAB_SHIFT                    (0)
#define TIM2_DMAR_DMAB_MASK                     (0xFFFFU << TIM2_DMAR_DMAB_SHIFT)
#define TIM2_DMAR_DMAB(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_DMAR_DMAB_SHIFT)) & TIM2_DMAR_DMAB_MASK)

/*!
 * @brief TIM2_OR Register Bit Definition
 */

#define TIM2_OR_TI4RMP_SHIFT                    (6)
#define TIM2_OR_TI4RMP_MASK                     (0x3U << TIM2_OR_TI4RMP_SHIFT)
#define TIM2_OR_TI4RMP(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_OR_TI4RMP_SHIFT)) & TIM2_OR_TI4RMP_MASK)

#define TIM2_OR_ETRRMP_SHIFT                    (0)
#define TIM2_OR_ETRRMP_MASK                     (0x7U << TIM2_OR_ETRRMP_SHIFT)
#define TIM2_OR_ETRRMP(x)                       (((uint32_t)(((uint32_t)(x)) << TIM2_OR_ETRRMP_SHIFT)) & TIM2_OR_ETRRMP_MASK)

/*!
 * @}
 */ /* end of group TIM2_Register_Masks */
/******************************************************************************
 * TIM2/5 Instance
******************************************************************************/
#define TIM2                                ((TIM2_Type*)TIM2_BASE)
#define TIM5                                ((TIM2_Type*)TIM5_BASE)

/*!
 * @}
 */ /* end of group TIM2_Peripheral_Access_Layer */



/*!
 * @addtogroup TIM6_Peripheral_Access_Layer TIM6 Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * TIM6 Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CR1;                                                            ///< Control register 1                           offset: 0x00
    __IO uint32_t Reserved12[2];                                                   ///< Reserved
    __IO uint32_t DIER;                                                           ///< DMA/interrupt enable register                offset: 0x0C
    __IO uint32_t SR;                                                             ///< Status register                              offset: 0x10
    __IO uint32_t EGR;                                                            ///< Event generation register                    offset: 0x14
    __IO uint32_t Reserved13[3];                                                   ///< Reserved
    __IO uint32_t CNT;                                                            ///< Counter                                      offset: 0x24
    __IO uint32_t PSC;                                                            ///< Prescaler                                    offset: 0x28
    __IO uint32_t ARR;                                                            ///< Autoload register                            offset: 0x2C
} TIM6_Type;

/*******************************************************************************
 * TIM6 Type
 ******************************************************************************/

/*!
 * @addtogroup TIM6_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief TIM6_CR1 Register Bit Definition
 */

#define TIM6_CR1_APRE_SHIFT                     (7)
#define TIM6_CR1_APRE_MASK                      (0x01U << TIM6_CR1_APRE_SHIFT)
#define TIM6_CR1_APRE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM6_CR1_APRE_SHIFT)) & TIM6_CR1_APRE_MASK)

#define TIM6_CR1_OPM_SHIFT                      (3)
#define TIM6_CR1_OPM_MASK                       (0x01U << TIM6_CR1_OPM_SHIFT)
#define TIM6_CR1_OPM(x)                         (((uint32_t)(((uint32_t)(x)) << TIM6_CR1_OPM_SHIFT)) & TIM6_CR1_OPM_MASK)

#define TIM6_CR1_URS_SHIFT                      (2)
#define TIM6_CR1_URS_MASK                       (0x01U << TIM6_CR1_URS_SHIFT)
#define TIM6_CR1_URS(x)                         (((uint32_t)(((uint32_t)(x)) << TIM6_CR1_URS_SHIFT)) & TIM6_CR1_URS_MASK)

#define TIM6_CR1_UDIS_SHIFT                     (1)
#define TIM6_CR1_UDIS_MASK                      (0x01U << TIM6_CR1_UDIS_SHIFT)
#define TIM6_CR1_UDIS(x)                        (((uint32_t)(((uint32_t)(x)) << TIM6_CR1_UDIS_SHIFT)) & TIM6_CR1_UDIS_MASK)

#define TIM6_CR1_CEN_SHIFT                      (0)
#define TIM6_CR1_CEN_MASK                       (0x01U << TIM6_CR1_CEN_SHIFT)
#define TIM6_CR1_CEN(x)                         (((uint32_t)(((uint32_t)(x)) << TIM6_CR1_CEN_SHIFT)) & TIM6_CR1_CEN_MASK)

/*!
 * @brief TIM6_DIER Register Bit Definition
 */

#define TIM6_DIER_UDE_SHIFT                     (8)
#define TIM6_DIER_UDE_MASK                      (0x01U << TIM6_DIER_UDE_SHIFT)
#define TIM6_DIER_UDE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM6_DIER_UDE_SHIFT)) & TIM6_DIER_UDE_MASK)

#define TIM6_DIER_UIE_SHIFT                     (0)
#define TIM6_DIER_UIE_MASK                      (0x01U << TIM6_DIER_UIE_SHIFT)
#define TIM6_DIER_UIE(x)                        (((uint32_t)(((uint32_t)(x)) << TIM6_DIER_UIE_SHIFT)) & TIM6_DIER_UIE_MASK)

/*!
 * @brief TIM6_SR Register Bit Definition
 */

#define TIM6_SR_UIF_SHIFT                       (0)
#define TIM6_SR_UIF_MASK                        (0x01U << TIM6_SR_UIF_SHIFT)
#define TIM6_SR_UIF(x)                          (((uint32_t)(((uint32_t)(x)) << TIM6_SR_UIF_SHIFT)) & TIM6_SR_UIF_MASK)

/*!
 * @brief TIM6_EGR Register Bit Definition
 */

#define TIM6_EGR_UG_SHIFT                       (0)
#define TIM6_EGR_UG_MASK                        (0x01U << TIM6_EGR_UG_SHIFT)
#define TIM6_EGR_UG(x)                          (((uint32_t)(((uint32_t)(x)) << TIM6_EGR_UG_SHIFT)) & TIM6_EGR_UG_MASK)

/*!
 * @brief TIM6_CNT Register Bit Definition
 */

#define TIM6_CNT_CNT_SHIFT                      (0)
#define TIM6_CNT_CNT_MASK                       (0xFFFFU << TIM6_CNT_CNT_SHIFT)
#define TIM6_CNT_CNT(x)                         (((uint32_t)(((uint32_t)(x)) << TIM6_CNT_CNT_SHIFT)) & TIM6_CNT_CNT_MASK)

/*!
 * @brief TIM6_PSC Register Bit Definition
 */

#define TIM6_PSC_PSC_SHIFT                      (0)
#define TIM6_PSC_PSC_MASK                       (0xFFFFU << TIM6_PSC_PSC_SHIFT)
#define TIM6_PSC_PSC(x)                         (((uint32_t)(((uint32_t)(x)) << TIM6_PSC_PSC_SHIFT)) & TIM6_PSC_PSC_MASK)

/*!
 * @brief TIM6_ARR Register Bit Definition
 */

#define TIM6_ARR_ARR_SHIFT                      (0)
#define TIM6_ARR_ARR_MASK                       (0xFFFFU << TIM6_ARR_ARR_SHIFT)
#define TIM6_ARR_ARR(x)                         (((uint32_t)(((uint32_t)(x)) << TIM6_ARR_ARR_SHIFT)) & TIM6_ARR_ARR_MASK)

/*!
 * @}
 */ /* end of group TIM6_Register_Masks */
/******************************************************************************
 * TIM6/7 Instance
******************************************************************************/
#define TIM6                                ((TIM6_Type*)TIM6_BASE)
#define TIM7                                ((TIM6_Type*)TIM7_BASE)

/*!
 * @}
 */ /* end of group TIM6_Peripheral_Access_Layer */



/*!
 * @addtogroup IWDG_Peripheral_Access_Layer IWDG Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * IWDG Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t KR;                                                             ///< Key register                                 offset: 0x00
    __IO uint32_t PR;                                                             ///< Prescaler register                           offset: 0x04
    __IO uint32_t RLR;                                                            ///< Reload register                              offset: 0x08
    __IO uint32_t SR;                                                             ///< Status register                              offset: 0x0C
    __IO uint32_t CR;                                                             ///< Control register                             offset: 0x10
    __IO uint32_t IGEN;                                                           ///< Interrupt generation register                offset: 0x14
    __IO uint32_t CNT;                                                            ///< Counting register                            offset: 0x18
    __IO uint32_t PS;                                                             ///< Divide count register                        offset: 0x1c
} IWDG_Type;

/*******************************************************************************
 * IWDG Type
 ******************************************************************************/

/*!
 * @addtogroup IWDG_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief IWDG_KR Register Bit Definition
 */

#define IWDG_KR_KEY_SHIFT                       (0)
#define IWDG_KR_KEY_MASK                        (0xFFFFU << IWDG_KR_KEY_SHIFT)
#define IWDG_KR_KEY(x)                          (((uint32_t)(((uint32_t)(x)) << IWDG_KR_KEY_SHIFT)) & IWDG_KR_KEY_MASK)

/*!
 * @brief IWDG_PR Register Bit Definition
 */

#define IWDG_PR_PR_SHIFT                        (0)
#define IWDG_PR_PR_MASK                         (0x7U << IWDG_PR_PR_SHIFT)
#define IWDG_PR_PR(x)                           (((uint32_t)(((uint32_t)(x)) << IWDG_PR_PR_SHIFT)) & IWDG_PR_PR_MASK)

/*!
 * @brief IWDG_RLR Register Bit Definition
 */

#define IWDG_RLR_RL_SHIFT                       (0)
#define IWDG_RLR_RL_MASK                        (0xFFFU << IWDG_RLR_RL_SHIFT)
#define IWDG_RLR_RL(x)                          (((uint32_t)(((uint32_t)(x)) << IWDG_RLR_RL_SHIFT)) & IWDG_RLR_RL_MASK)

/*!
 * @brief IWDG_SR Register Bit Definition
 */

#define IWDG_SR_UPDATE_SHIFT                    (3)
#define IWDG_SR_UPDATE_MASK                     (0x01U << IWDG_SR_UPDATE_SHIFT)
#define IWDG_SR_UPDATE(x)                       (((uint32_t)(((uint32_t)(x)) << IWDG_SR_UPDATE_SHIFT)) & IWDG_SR_UPDATE_MASK)

#define IWDG_SR_IVU_SHIFT                       (2)
#define IWDG_SR_IVU_MASK                        (0x01U << IWDG_SR_IVU_SHIFT)
#define IWDG_SR_IVU(x)                          (((uint32_t)(((uint32_t)(x)) << IWDG_SR_IVU_SHIFT)) & IWDG_SR_IVU_MASK)

#define IWDG_SR_RVU_SHIFT                       (1)
#define IWDG_SR_RVU_MASK                        (0x01U << IWDG_SR_RVU_SHIFT)
#define IWDG_SR_RVU(x)                          (((uint32_t)(((uint32_t)(x)) << IWDG_SR_RVU_SHIFT)) & IWDG_SR_RVU_MASK)

#define IWDG_SR_PVU_SHIFT                       (0)
#define IWDG_SR_PVU_MASK                        (0x01U << IWDG_SR_PVU_SHIFT)
#define IWDG_SR_PVU(x)                          (((uint32_t)(((uint32_t)(x)) << IWDG_SR_PVU_SHIFT)) & IWDG_SR_PVU_MASK)

/*!
 * @brief IWDG_CR Register Bit Definition
 */

#define IWDG_CR_IRQCLR_SHIFT                   (1)
#define IWDG_CR_IRQCLR_MASK                    (0x01U << IWDG_CR_IRQCLR_SHIFT)
#define IWDG_CR_IRQCLR(x)                      (((uint32_t)(((uint32_t)(x)) << IWDG_CR_IRQCLR_SHIFT)) & IWDG_CR_IRQCLR_MASK)

#define IWDG_CR_IRQSEL_SHIFT                   (0)
#define IWDG_CR_IRQSEL_MASK                    (0x01U << IWDG_CR_IRQSEL_SHIFT)
#define IWDG_CR_IRQSEL(x)                      (((uint32_t)(((uint32_t)(x)) << IWDG_CR_IRQSEL_SHIFT)) & IWDG_CR_IRQSEL_MASK)

/*!
 * @brief IWDG_IGEN Register Bit Definition
 */

#define IWDG_IGEN_IGEN_SHIFT                    (0)
#define IWDG_IGEN_IGEN_MASK                     (0xFFFU << IWDG_IGEN_IGEN_SHIFT)
#define IWDG_IGEN_IGEN(x)                       (((uint32_t)(((uint32_t)(x)) << IWDG_IGEN_IGEN_SHIFT)) & IWDG_IGEN_IGEN_MASK)

/*!
 * @brief IWDG_CNT Register Bit Definition
 */

#define IWDG_CNT_IWDGCNT_SHIFT                 (0)
#define IWDG_CNT_IWDGCNT_MASK                  (0xFFFU << IWDG_CNT_IWDGCNT_SHIFT)
#define IWDG_CNT_IWDGCNT(x)                    (((uint32_t)(((uint32_t)(x)) << IWDG_CNT_IWDGCNT_SHIFT)) & IWDG_CNT_IWDGCNT_MASK)

/*!
 * @brief IWDG_PS Register Bit Definition
 */

#define IWDG_PS_IWDGPS_SHIFT                   (0)
#define IWDG_PS_IWDGPS_MASK                    (0xFFU << IWDG_PS_IWDGPS_SHIFT)
#define IWDG_PS_IWDGPS(x)                      (((uint32_t)(((uint32_t)(x)) << IWDG_PS_IWDGPS_SHIFT)) & IWDG_PS_IWDGPS_MASK)

/*!
 * @}
 */ /* end of group IWDG_Register_Masks */
/******************************************************************************
 * IWDG Instance
******************************************************************************/
#define IWDG                                ((IWDG_Type*)IWDG_BASE)

/*!
 * @}
 */ /* end of group IWDG_Peripheral_Access_Layer */



/*!
 * @addtogroup WWDG_Peripheral_Access_Layer WWDG Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * WWDG Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CR;                                                             ///< Control register                             offset: 0x00
    __IO uint32_t CFGR;                                                           ///< Configuration register                       offset: 0x04
    __IO uint32_t SR;                                                             ///< Status register                              offset: 0x08
} WWDG_Type;

/*******************************************************************************
 * WWDG Type
 ******************************************************************************/

/*!
 * @addtogroup WWDG_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief WWDG_CR Register Bit Definition
 */

#define WWDG_CR_WDGA_SHIFT                      (7)
#define WWDG_CR_WDGA_MASK                       (0x01U << WWDG_CR_WDGA_SHIFT)
#define WWDG_CR_WDGA(x)                         (((uint32_t)(((uint32_t)(x)) << WWDG_CR_WDGA_SHIFT)) & WWDG_CR_WDGA_MASK)

#define WWDG_CR_T_SHIFT                         (0)
#define WWDG_CR_T_MASK                          (0x7FU << WWDG_CR_T_SHIFT)
#define WWDG_CR_T(x)                            (((uint32_t)(((uint32_t)(x)) << WWDG_CR_T_SHIFT)) & WWDG_CR_T_MASK)

/*!
 * @brief WWDG_CFGR Register Bit Definition
 */

#define WWDG_CFGR_EWI_SHIFT                     (9)
#define WWDG_CFGR_EWI_MASK                      (0x01U << WWDG_CFGR_EWI_SHIFT)
#define WWDG_CFGR_EWI(x)                        (((uint32_t)(((uint32_t)(x)) << WWDG_CFGR_EWI_SHIFT)) & WWDG_CFGR_EWI_MASK)

#define WWDG_CFGR_WDGTB_SHIFT                   (7)
#define WWDG_CFGR_WDGTB_MASK                    (0x3U << WWDG_CFGR_WDGTB_SHIFT)
#define WWDG_CFGR_WDGTB(x)                      (((uint32_t)(((uint32_t)(x)) << WWDG_CFGR_WDGTB_SHIFT)) & WWDG_CFGR_WDGTB_MASK)

#define WWDG_CFGR_W_SHIFT                       (0)
#define WWDG_CFGR_W_MASK                        (0x7FU << WWDG_CFGR_W_SHIFT)
#define WWDG_CFGR_W(x)                          (((uint32_t)(((uint32_t)(x)) << WWDG_CFGR_W_SHIFT)) & WWDG_CFGR_W_MASK)

/*!
 * @brief WWDG_SR Register Bit Definition
 */

#define WWDG_SR_EWIF_SHIFT                      (0)
#define WWDG_SR_EWIF_MASK                       (0x01U << WWDG_SR_EWIF_SHIFT)
#define WWDG_SR_EWIF(x)                         (((uint32_t)(((uint32_t)(x)) << WWDG_SR_EWIF_SHIFT)) & WWDG_SR_EWIF_MASK)

/*!
 * @}
 */ /* end of group WWDG_Register_Masks */
/******************************************************************************
 * WWDG Instance
******************************************************************************/
#define WWDG                                ((WWDG_Type*)WWDG_BASE)

/*!
 * @}
 */ /* end of group WWDG_Peripheral_Access_Layer */



/*!
 * @addtogroup RTC_Peripheral_Access_Layer RTC Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * RTC Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CRH;                                                            ///< RTC control register high                    offset: 0x00
    __IO uint32_t CRL;                                                            ///< RTC control register low bit                 offset: 0x04
    __IO uint32_t PRLH;                                                           ///< RTC prescaler load register high             offset: 0x08
    __IO uint32_t PRLL;                                                           ///< RTC prescaler load register low bit          offset: 0x0C
    __IO uint32_t DIVH;                                                           ///< RTC prescaler frequency division factor register high bitoffset: 0x10
    __IO uint32_t DIVL;                                                           ///< RTC prescaler division factor register low bitoffset: 0x14
    __IO uint32_t CNTH;                                                           ///< RTC counter register high bit                offset: 0x18
    __IO uint32_t CNTL;                                                           ///< RTC counter register low bit                 offset: 0x1C
    __IO uint32_t ALRH;                                                           ///< RTC alarm register high bit                  offset: 0x20
    __IO uint32_t ALRL;                                                           ///< RTC alarm register low bit                   offset: 0x24
    __IO uint32_t MSRH;                                                           ///< RTC millisecond register high                offset: 0x28
    __IO uint32_t MSRL;                                                           ///< RTC millisecond register low bit             offset: 0x2C
    __IO uint32_t Reserved14[3];                                                  ///< Reserved
    __IO uint32_t LSECFG;                                                         ///< RTC configuration register                   offset: 0x3C
} RTC_Type;
/*******************************************************************************
 * RTC Type
 ******************************************************************************/

/*!
 * @addtogroup RTC_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief RTC_CRH Register Bit Definition
 */

#define RTC_CRH_OWIE_SHIFT                      (2)
#define RTC_CRH_OWIE_MASK                       (0x01U << RTC_CRH_OWIE_SHIFT)
#define RTC_CRH_OWIE(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_CRH_OWIE_SHIFT)) & RTC_CRH_OWIE_MASK)

#define RTC_CRH_ALRIE_SHIFT                     (1)
#define RTC_CRH_ALRIE_MASK                      (0x01U << RTC_CRH_ALRIE_SHIFT)
#define RTC_CRH_ALRIE(x)                        (((uint32_t)(((uint32_t)(x)) << RTC_CRH_ALRIE_SHIFT)) & RTC_CRH_ALRIE_MASK)

#define RTC_CRH_SECIE_SHIFT                     (0)
#define RTC_CRH_SECIE_MASK                      (0x01U << RTC_CRH_SECIE_SHIFT)
#define RTC_CRH_SECIE(x)                        (((uint32_t)(((uint32_t)(x)) << RTC_CRH_SECIE_SHIFT)) & RTC_CRH_SECIE_MASK)

/*!
 * @brief RTC_CRL Register Bit Definition
 */

#define RTC_CRL_ALPEN_SHIFT                     (6)
#define RTC_CRL_ALPEN_MASK                      (0x01U << RTC_CRL_ALPEN_SHIFT)
#define RTC_CRL_ALPEN(x)                        (((uint32_t)(((uint32_t)(x)) << RTC_CRL_ALPEN_SHIFT)) & RTC_CRL_ALPEN_MASK)

#define RTC_CRL_RTOFF_SHIFT                     (5)
#define RTC_CRL_RTOFF_MASK                      (0x01U << RTC_CRL_RTOFF_SHIFT)
#define RTC_CRL_RTOFF(x)                        (((uint32_t)(((uint32_t)(x)) << RTC_CRL_RTOFF_SHIFT)) & RTC_CRL_RTOFF_MASK)

#define RTC_CRL_CNF_SHIFT                       (4)
#define RTC_CRL_CNF_MASK                        (0x01U << RTC_CRL_CNF_SHIFT)
#define RTC_CRL_CNF(x)                          (((uint32_t)(((uint32_t)(x)) << RTC_CRL_CNF_SHIFT)) & RTC_CRL_CNF_MASK)

#define RTC_CRL_RSF_SHIFT                       (3)
#define RTC_CRL_RSF_MASK                        (0x01U << RTC_CRL_RSF_SHIFT)
#define RTC_CRL_RSF(x)                          (((uint32_t)(((uint32_t)(x)) << RTC_CRL_RSF_SHIFT)) & RTC_CRL_RSF_MASK)

#define RTC_CRL_OWF_SHIFT                       (2)
#define RTC_CRL_OWF_MASK                        (0x01U << RTC_CRL_OWF_SHIFT)
#define RTC_CRL_OWF(x)                          (((uint32_t)(((uint32_t)(x)) << RTC_CRL_OWF_SHIFT)) & RTC_CRL_OWF_MASK)

#define RTC_CRL_ALRF_SHIFT                      (1)
#define RTC_CRL_ALRF_MASK                       (0x01U << RTC_CRL_ALRF_SHIFT)
#define RTC_CRL_ALRF(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_CRL_ALRF_SHIFT)) & RTC_CRL_ALRF_MASK)

#define RTC_CRL_SECF_SHIFT                      (0)
#define RTC_CRL_SECF_MASK                       (0x01U << RTC_CRL_SECF_SHIFT)
#define RTC_CRL_SECF(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_CRL_SECF_SHIFT)) & RTC_CRL_SECF_MASK)

/*!
 * @brief RTC_PRLH Register Bit Definition
 */

#define RTC_PRLH_PRL_SHIFT                      (0)
#define RTC_PRLH_PRL_MASK                       (0xFU << RTC_PRLH_PRL_SHIFT)
#define RTC_PRLH_PRL(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_PRLH_PRL_SHIFT)) & RTC_PRLH_PRL_MASK)

/*!
 * @brief RTC_PRLL Register Bit Definition
 */

#define RTC_PRLL_PRL_SHIFT                      (0)
#define RTC_PRLL_PRL_MASK                       (0xFFFFU << RTC_PRLL_PRL_SHIFT)
#define RTC_PRLL_PRL(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_PRLL_PRL_SHIFT)) & RTC_PRLL_PRL_MASK)

/*!
 * @brief RTC_DIVH Register Bit Definition
 */

#define RTC_DIVH_DIV_SHIFT                      (0)
#define RTC_DIVH_DIV_MASK                       (0xFU << RTC_DIVH_DIV_SHIFT)
#define RTC_DIVH_DIV(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_DIVH_DIV_SHIFT)) & RTC_DIVH_DIV_MASK)

/*!
 * @brief RTC_DIVL Register Bit Definition
 */

#define RTC_DIVL_DIV_SHIFT                      (0)
#define RTC_DIVL_DIV_MASK                       (0xFFFFU << RTC_DIVL_DIV_SHIFT)
#define RTC_DIVL_DIV(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_DIVL_DIV_SHIFT)) & RTC_DIVL_DIV_MASK)

/*!
 * @brief RTC_CNTH Register Bit Definition
 */

#define RTC_CNTH_CNT_SHIFT                      (0)
#define RTC_CNTH_CNT_MASK                       (0xFFFFU << RTC_CNTH_CNT_SHIFT)
#define RTC_CNTH_CNT(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_CNTH_CNT_SHIFT)) & RTC_CNTH_CNT_MASK)

/*!
 * @brief RTC_CNTL Register Bit Definition
 */

#define RTC_CNTL_CNT_SHIFT                      (0)
#define RTC_CNTL_CNT_MASK                       (0xFFFFU << RTC_CNTL_CNT_SHIFT)
#define RTC_CNTL_CNT(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_CNTL_CNT_SHIFT)) & RTC_CNTL_CNT_MASK)

/*!
 * @brief RTC_ALRH Register Bit Definition
 */

#define RTC_ALRH_ALR_SHIFT                      (0)
#define RTC_ALRH_ALR_MASK                       (0xFFFFU << RTC_ALRH_ALR_SHIFT)
#define RTC_ALRH_ALR(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_ALRH_ALR_SHIFT)) & RTC_ALRH_ALR_MASK)

/*!
 * @brief RTC_ALRL Register Bit Definition
 */

#define RTC_ALRL_ALR_SHIFT                      (0)
#define RTC_ALRL_ALR_MASK                       (0xFFFFU << RTC_ALRL_ALR_SHIFT)
#define RTC_ALRL_ALR(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_ALRL_ALR_SHIFT)) & RTC_ALRL_ALR_MASK)

/*!
 * @brief RTC_MSRH Register Bit Definition
 */

#define RTC_MSRH_MSR_SHIFT                      (0)
#define RTC_MSRH_MSR_MASK                       (0xFU << RTC_MSRH_MSR_SHIFT)
#define RTC_MSRH_MSR(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_MSRH_MSR_SHIFT)) & RTC_MSRH_MSR_MASK)

/*!
 * @brief RTC_MSRL Register Bit Definition
 */

#define RTC_MSRL_MSR_SHIFT                      (0)
#define RTC_MSRL_MSR_MASK                       (0xFFFFU << RTC_MSRL_MSR_SHIFT)
#define RTC_MSRL_MSR(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_MSRL_MSR_SHIFT)) & RTC_MSRL_MSR_MASK)

/*!
 * @brief RTC_LSECFG Register Bit Definition
 */

#define RTC_LSECFG_LSEIB_SHIFT                 (8)
#define RTC_LSECFG_LSEIB_MASK                  (0x3U << RTC_LSECFG_LSEIB_SHIFT)
#define RTC_LSECFG_LSEIB(x)                    (((uint32_t)(((uint32_t)(x)) << RTC_LSECFG_LSEIB_SHIFT)) & RTC_LSECFG_LSEIB_MASK)

#define RTC_LSECFG_LSERFBSEL_SHIFT             (6)
#define RTC_LSECFG_LSERFBSEL_MASK              (0x3U << RTC_LSECFG_LSERFBSEL_SHIFT)
#define RTC_LSECFG_LSERFBSEL(x)                (((uint32_t)(((uint32_t)(x)) << RTC_LSECFG_LSERFBSEL_SHIFT)) & RTC_LSECFG_LSERFBSEL_MASK)

#define RTC_LSECFG_LSEDR_SHIFT                 (4)
#define RTC_LSECFG_LSEDR_MASK                  (0x3U << RTC_LSECFG_LSEDR_SHIFT)
#define RTC_LSECFG_LSEDR(x)                    (((uint32_t)(((uint32_t)(x)) << RTC_LSECFG_LSEDR_SHIFT)) & RTC_LSECFG_LSEDR_MASK)

#define RTC_LSECFG_LSETEST_SHIFT               (0)
#define RTC_LSECFG_LSETEST_MASK                (0xFU << RTC_LSECFG_LSETEST_SHIFT)
#define RTC_LSECFG_LSETEST(x)                  (((uint32_t)(((uint32_t)(x)) << RTC_LSECFG_LSETEST_SHIFT)) & RTC_LSECFG_LSETEST_MASK)

/*!
 * @}
 */ /* end of group RTC_Register_Masks */
/******************************************************************************
 * RTC Instance
******************************************************************************/
#define RTC                             ((RTC_Type*)RTC_BKP_BASE)

/*!
 * @}
 */ /* end of group RTC_Peripheral_Access_Layer */



/*!
 * @addtogroup UART_Peripheral_Access_Layer UART Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * UART Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t TDR;                                                            ///< UART transmit data register                  offset: 0x00
    __IO uint32_t RDR;                                                            ///< UART receive data register                   offset: 0x04
    __IO uint32_t CSR;                                                            ///< UART current status register                 offset: 0x08
    __IO uint32_t ISR;                                                            ///< UART interrupt status register               offset: 0x0C
    __IO uint32_t IER;                                                            ///< UART interrupt enable register               offset: 0x10
    __IO uint32_t ICR;                                                            ///< UART interrupt clear register                offset: 0x14
    __IO uint32_t GCR;                                                            ///< UART global control register                 offset: 0x18
    __IO uint32_t CCR;                                                            ///< UART general control register                offset: 0x1C
    __IO uint32_t BRR;                                                            ///< UART baud rate register                      offset: 0x20
    __IO uint32_t FRA;                                                            ///< UART Fractional Baud Rate Register           offset: 0x24
    __IO uint32_t RXADDR;                                                         ///< UART receive address register                offset: 0x28
    __IO uint32_t RXMASK;                                                         ///< UART receive mask register                   offset: 0x2C
    __IO uint32_t SCR;                                                            ///< UART SCR register                            offset: 0x30
    __IO uint32_t IDLR;                                                           ///< UART IDLE data length register               offset: 0x34
    __IO uint32_t ABRCR;                                                          ///< UART ABRCR automatic baud rate control registeroffset: 0x38
    __IO uint32_t IRDA;                                                           ///< UART IRDA infrared function control register offset: 0x3C
} UART_Type;

/*******************************************************************************
 * UART Type
 ******************************************************************************/

/*!
 * @addtogroup UART_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief UART_TDR Register Bit Definition
 */

#define UART_TDR_TXREG_SHIFT                    (0)
#define UART_TDR_TXREG_MASK                     (0x1FFU << UART_TDR_TXREG_SHIFT)
#define UART_TDR_TXREG(x)                       (((uint32_t)(((uint32_t)(x)) << UART_TDR_TXREG_SHIFT)) & UART_TDR_TXREG_MASK)

/*!
 * @brief UART_RDR Register Bit Definition
 */

#define UART_RDR_RXREG_SHIFT                    (0)
#define UART_RDR_RXREG_MASK                     (0x1FFU << UART_RDR_RXREG_SHIFT)
#define UART_RDR_RXREG(x)                       (((uint32_t)(((uint32_t)(x)) << UART_RDR_RXREG_SHIFT)) & UART_RDR_RXREG_MASK)

/*!
 * @brief UART_CSR Register Bit Definition
 */

#define UART_CSR_TXEPT_SHIFT                    (3)
#define UART_CSR_TXEPT_MASK                     (0x01U << UART_CSR_TXEPT_SHIFT)
#define UART_CSR_TXEPT(x)                       (((uint32_t)(((uint32_t)(x)) << UART_CSR_TXEPT_SHIFT)) & UART_CSR_TXEPT_MASK)

#define UART_CSR_TXFULL_SHIFT                   (2)
#define UART_CSR_TXFULL_MASK                    (0x01U << UART_CSR_TXFULL_SHIFT)
#define UART_CSR_TXFULL(x)                      (((uint32_t)(((uint32_t)(x)) << UART_CSR_TXFULL_SHIFT)) & UART_CSR_TXFULL_MASK)

#define UART_CSR_RXAVL_SHIFT                    (1)
#define UART_CSR_RXAVL_MASK                     (0x01U << UART_CSR_RXAVL_SHIFT)
#define UART_CSR_RXAVL(x)                       (((uint32_t)(((uint32_t)(x)) << UART_CSR_RXAVL_SHIFT)) & UART_CSR_RXAVL_MASK)

#define UART_CSR_TXC_SHIFT                      (0)
#define UART_CSR_TXC_MASK                       (0x01U << UART_CSR_TXC_SHIFT)
#define UART_CSR_TXC(x)                         (((uint32_t)(((uint32_t)(x)) << UART_CSR_TXC_SHIFT)) & UART_CSR_TXC_MASK)

/*!
 * @brief UART_ISR Register Bit Definition
 */

#define UART_ISR_ABRERRINTF_SHIFT               (11)
#define UART_ISR_ABRERRINTF_MASK                (0x01U << UART_ISR_ABRERRINTF_SHIFT)
#define UART_ISR_ABRERRINTF(x)                  (((uint32_t)(((uint32_t)(x)) << UART_ISR_ABRERRINTF_SHIFT)) & UART_ISR_ABRERRINTF_MASK)

#define UART_ISR_ABRENDINTF_SHIFT               (10)
#define UART_ISR_ABRENDINTF_MASK                (0x01U << UART_ISR_ABRENDINTF_SHIFT)
#define UART_ISR_ABRENDINTF(x)                  (((uint32_t)(((uint32_t)(x)) << UART_ISR_ABRENDINTF_SHIFT)) & UART_ISR_ABRENDINTF_MASK)

#define UART_ISR_RXIDLEINTF_SHIFT               (9)
#define UART_ISR_RXIDLEINTF_MASK                (0x01U << UART_ISR_RXIDLEINTF_SHIFT)
#define UART_ISR_RXIDLEINTF(x)                  (((uint32_t)(((uint32_t)(x)) << UART_ISR_RXIDLEINTF_SHIFT)) & UART_ISR_RXIDLEINTF_MASK)

#define UART_ISR_RXB8INTF_SHIFT                 (8)
#define UART_ISR_RXB8INTF_MASK                  (0x01U << UART_ISR_RXB8INTF_SHIFT)
#define UART_ISR_RXB8INTF(x)                    (((uint32_t)(((uint32_t)(x)) << UART_ISR_RXB8INTF_SHIFT)) & UART_ISR_RXB8INTF_MASK)

#define UART_ISR_TXBRKINTF_SHIFT                (7)
#define UART_ISR_TXBRKINTF_MASK                 (0x01U << UART_ISR_TXBRKINTF_SHIFT)
#define UART_ISR_TXBRKINTF(x)                   (((uint32_t)(((uint32_t)(x)) << UART_ISR_TXBRKINTF_SHIFT)) & UART_ISR_TXBRKINTF_MASK)

#define UART_ISR_RXBRKINTF_SHIFT                (6)
#define UART_ISR_RXBRKINTF_MASK                 (0x01U << UART_ISR_RXBRKINTF_SHIFT)
#define UART_ISR_RXBRKINTF(x)                   (((uint32_t)(((uint32_t)(x)) << UART_ISR_RXBRKINTF_SHIFT)) & UART_ISR_RXBRKINTF_MASK)

#define UART_ISR_RXFERRINTF_SHIFT               (5)
#define UART_ISR_RXFERRINTF_MASK                (0x01U << UART_ISR_RXFERRINTF_SHIFT)
#define UART_ISR_RXFERRINTF(x)                  (((uint32_t)(((uint32_t)(x)) << UART_ISR_RXFERRINTF_SHIFT)) & UART_ISR_RXFERRINTF_MASK)

#define UART_ISR_RXPERRINTF_SHIFT               (4)
#define UART_ISR_RXPERRINTF_MASK                (0x01U << UART_ISR_RXPERRINTF_SHIFT)
#define UART_ISR_RXPERRINTF(x)                  (((uint32_t)(((uint32_t)(x)) << UART_ISR_RXPERRINTF_SHIFT)) & UART_ISR_RXPERRINTF_MASK)

#define UART_ISR_RXOERRINTF_SHIFT               (3)
#define UART_ISR_RXOERRINTF_MASK                (0x01U << UART_ISR_RXOERRINTF_SHIFT)
#define UART_ISR_RXOERRINTF(x)                  (((uint32_t)(((uint32_t)(x)) << UART_ISR_RXOERRINTF_SHIFT)) & UART_ISR_RXOERRINTF_MASK)

#define UART_ISR_TXCINTF_SHIFT                  (2)
#define UART_ISR_TXCINTF_MASK                   (0x01U << UART_ISR_TXCINTF_SHIFT)
#define UART_ISR_TXCINTF(x)                     (((uint32_t)(((uint32_t)(x)) << UART_ISR_TXCINTF_SHIFT)) & UART_ISR_TXCINTF_MASK)

#define UART_ISR_RXINTF_SHIFT                   (1)
#define UART_ISR_RXINTF_MASK                    (0x01U << UART_ISR_RXINTF_SHIFT)
#define UART_ISR_RXINTF(x)                      (((uint32_t)(((uint32_t)(x)) << UART_ISR_RXINTF_SHIFT)) & UART_ISR_RXINTF_MASK)

#define UART_ISR_TXINTF_SHIFT                   (0)
#define UART_ISR_TXINTF_MASK                    (0x01U << UART_ISR_TXINTF_SHIFT)
#define UART_ISR_TXINTF(x)                      (((uint32_t)(((uint32_t)(x)) << UART_ISR_TXINTF_SHIFT)) & UART_ISR_TXINTF_MASK)

/*!
 * @brief UART_IER Register Bit Definition
 */

#define UART_IER_ABRERRIEN_SHIFT                (11)
#define UART_IER_ABRERRIEN_MASK                 (0x01U << UART_IER_ABRERRIEN_SHIFT)
#define UART_IER_ABRERRIEN(x)                   (((uint32_t)(((uint32_t)(x)) << UART_IER_ABRERRIEN_SHIFT)) & UART_IER_ABRERRIEN_MASK)

#define UART_IER_ABRENDIEN_SHIFT                (10)
#define UART_IER_ABRENDIEN_MASK                 (0x01U << UART_IER_ABRENDIEN_SHIFT)
#define UART_IER_ABRENDIEN(x)                   (((uint32_t)(((uint32_t)(x)) << UART_IER_ABRENDIEN_SHIFT)) & UART_IER_ABRENDIEN_MASK)

#define UART_IER_RXIDLEIEN_SHIFT                (9)
#define UART_IER_RXIDLEIEN_MASK                 (0x01U << UART_IER_RXIDLEIEN_SHIFT)
#define UART_IER_RXIDLEIEN(x)                   (((uint32_t)(((uint32_t)(x)) << UART_IER_RXIDLEIEN_SHIFT)) & UART_IER_RXIDLEIEN_MASK)

#define UART_IER_RXB8IEN_SHIFT                  (8)
#define UART_IER_RXB8IEN_MASK                   (0x01U << UART_IER_RXB8IEN_SHIFT)
#define UART_IER_RXB8IEN(x)                     (((uint32_t)(((uint32_t)(x)) << UART_IER_RXB8IEN_SHIFT)) & UART_IER_RXB8IEN_MASK)

#define UART_IER_TXBRKIEN_SHIFT                 (7)
#define UART_IER_TXBRKIEN_MASK                  (0x01U << UART_IER_TXBRKIEN_SHIFT)
#define UART_IER_TXBRKIEN(x)                    (((uint32_t)(((uint32_t)(x)) << UART_IER_TXBRKIEN_SHIFT)) & UART_IER_TXBRKIEN_MASK)

#define UART_IER_RXBRKIEN_SHIFT                 (6)
#define UART_IER_RXBRKIEN_MASK                  (0x01U << UART_IER_RXBRKIEN_SHIFT)
#define UART_IER_RXBRKIEN(x)                    (((uint32_t)(((uint32_t)(x)) << UART_IER_RXBRKIEN_SHIFT)) & UART_IER_RXBRKIEN_MASK)

#define UART_IER_RXFERRIEN_SHIFT                (5)
#define UART_IER_RXFERRIEN_MASK                 (0x01U << UART_IER_RXFERRIEN_SHIFT)
#define UART_IER_RXFERRIEN(x)                   (((uint32_t)(((uint32_t)(x)) << UART_IER_RXFERRIEN_SHIFT)) & UART_IER_RXFERRIEN_MASK)

#define UART_IER_RXPERRIEN_SHIFT                (4)
#define UART_IER_RXPERRIEN_MASK                 (0x01U << UART_IER_RXPERRIEN_SHIFT)
#define UART_IER_RXPERRIEN(x)                   (((uint32_t)(((uint32_t)(x)) << UART_IER_RXPERRIEN_SHIFT)) & UART_IER_RXPERRIEN_MASK)

#define UART_IER_RXOERRIEN_SHIFT                (3)
#define UART_IER_RXOERRIEN_MASK                 (0x01U << UART_IER_RXOERRIEN_SHIFT)
#define UART_IER_RXOERRIEN(x)                   (((uint32_t)(((uint32_t)(x)) << UART_IER_RXOERRIEN_SHIFT)) & UART_IER_RXOERRIEN_MASK)

#define UART_IER_TXCIEN_SHIFT                   (2)
#define UART_IER_TXCIEN_MASK                    (0x01U << UART_IER_TXCIEN_SHIFT)
#define UART_IER_TXCIEN(x)                      (((uint32_t)(((uint32_t)(x)) << UART_IER_TXCIEN_SHIFT)) & UART_IER_TXCIEN_MASK)

#define UART_IER_RXIEN_SHIFT                    (1)
#define UART_IER_RXIEN_MASK                     (0x01U << UART_IER_RXIEN_SHIFT)
#define UART_IER_RXIEN(x)                       (((uint32_t)(((uint32_t)(x)) << UART_IER_RXIEN_SHIFT)) & UART_IER_RXIEN_MASK)

#define UART_IER_TXIEN_SHIFT                    (0)
#define UART_IER_TXIEN_MASK                     (0x01U << UART_IER_TXIEN_SHIFT)
#define UART_IER_TXIEN(x)                       (((uint32_t)(((uint32_t)(x)) << UART_IER_TXIEN_SHIFT)) & UART_IER_TXIEN_MASK)

/*!
 * @brief UART_ICR Register Bit Definition
 */

#define UART_ICR_ABRERRICLR_SHIFT               (11)
#define UART_ICR_ABRERRICLR_MASK                (0x01U << UART_ICR_ABRERRICLR_SHIFT)
#define UART_ICR_ABRERRICLR(x)                  (((uint32_t)(((uint32_t)(x)) << UART_ICR_ABRERRICLR_SHIFT)) & UART_ICR_ABRERRICLR_MASK)

#define UART_ICR_ABRENDICLR_SHIFT               (10)
#define UART_ICR_ABRENDICLR_MASK                (0x01U << UART_ICR_ABRENDICLR_SHIFT)
#define UART_ICR_ABRENDICLR(x)                  (((uint32_t)(((uint32_t)(x)) << UART_ICR_ABRENDICLR_SHIFT)) & UART_ICR_ABRENDICLR_MASK)

#define UART_ICR_RXIDLEICLR_SHIFT               (9)
#define UART_ICR_RXIDLEICLR_MASK                (0x01U << UART_ICR_RXIDLEICLR_SHIFT)
#define UART_ICR_RXIDLEICLR(x)                  (((uint32_t)(((uint32_t)(x)) << UART_ICR_RXIDLEICLR_SHIFT)) & UART_ICR_RXIDLEICLR_MASK)

#define UART_ICR_RXB8ICLR_SHIFT                 (8)
#define UART_ICR_RXB8ICLR_MASK                  (0x01U << UART_ICR_RXB8ICLR_SHIFT)
#define UART_ICR_RXB8ICLR(x)                    (((uint32_t)(((uint32_t)(x)) << UART_ICR_RXB8ICLR_SHIFT)) & UART_ICR_RXB8ICLR_MASK)

#define UART_ICR_TXBRKICLR_SHIFT                (7)
#define UART_ICR_TXBRKICLR_MASK                 (0x01U << UART_ICR_TXBRKICLR_SHIFT)
#define UART_ICR_TXBRKICLR(x)                   (((uint32_t)(((uint32_t)(x)) << UART_ICR_TXBRKICLR_SHIFT)) & UART_ICR_TXBRKICLR_MASK)

#define UART_ICR_RXBRKICLR_SHIFT                (6)
#define UART_ICR_RXBRKICLR_MASK                 (0x01U << UART_ICR_RXBRKICLR_SHIFT)
#define UART_ICR_RXBRKICLR(x)                   (((uint32_t)(((uint32_t)(x)) << UART_ICR_RXBRKICLR_SHIFT)) & UART_ICR_RXBRKICLR_MASK)

#define UART_ICR_RXFERRICLR_SHIFT               (5)
#define UART_ICR_RXFERRICLR_MASK                (0x01U << UART_ICR_RXFERRICLR_SHIFT)
#define UART_ICR_RXFERRICLR(x)                  (((uint32_t)(((uint32_t)(x)) << UART_ICR_RXFERRICLR_SHIFT)) & UART_ICR_RXFERRICLR_MASK)

#define UART_ICR_RXPERRICLR_SHIFT               (4)
#define UART_ICR_RXPERRICLR_MASK                (0x01U << UART_ICR_RXPERRICLR_SHIFT)
#define UART_ICR_RXPERRICLR(x)                  (((uint32_t)(((uint32_t)(x)) << UART_ICR_RXPERRICLR_SHIFT)) & UART_ICR_RXPERRICLR_MASK)

#define UART_ICR_RXOERRICLR_SHIFT               (3)
#define UART_ICR_RXOERRICLR_MASK                (0x01U << UART_ICR_RXOERRICLR_SHIFT)
#define UART_ICR_RXOERRICLR(x)                  (((uint32_t)(((uint32_t)(x)) << UART_ICR_RXOERRICLR_SHIFT)) & UART_ICR_RXOERRICLR_MASK)

#define UART_ICR_TXCICLR_SHIFT                  (2)
#define UART_ICR_TXCICLR_MASK                   (0x01U << UART_ICR_TXCICLR_SHIFT)
#define UART_ICR_TXCICLR(x)                     (((uint32_t)(((uint32_t)(x)) << UART_ICR_TXCICLR_SHIFT)) & UART_ICR_TXCICLR_MASK)

#define UART_ICR_RXICLR_SHIFT                   (1)
#define UART_ICR_RXICLR_MASK                    (0x01U << UART_ICR_RXICLR_SHIFT)
#define UART_ICR_RXICLR(x)                      (((uint32_t)(((uint32_t)(x)) << UART_ICR_RXICLR_SHIFT)) & UART_ICR_RXICLR_MASK)

#define UART_ICR_TXICLR_SHIFT                   (0)
#define UART_ICR_TXICLR_MASK                    (0x01U << UART_ICR_TXICLR_SHIFT)
#define UART_ICR_TXICLR(x)                      (((uint32_t)(((uint32_t)(x)) << UART_ICR_TXICLR_SHIFT)) & UART_ICR_TXICLR_MASK)

/*!
 * @brief UART_GCR Register Bit Definition
 */

#define UART_GCR_TXTOG_SHIFT                    (10)
#define UART_GCR_TXTOG_MASK                     (0x01U << UART_GCR_TXTOG_SHIFT)
#define UART_GCR_TXTOG(x)                       (((uint32_t)(((uint32_t)(x)) << UART_GCR_TXTOG_SHIFT)) & UART_GCR_TXTOG_MASK)

#define UART_GCR_RXTOG_SHIFT                    (9)
#define UART_GCR_RXTOG_MASK                     (0x01U << UART_GCR_RXTOG_SHIFT)
#define UART_GCR_RXTOG(x)                       (((uint32_t)(((uint32_t)(x)) << UART_GCR_RXTOG_SHIFT)) & UART_GCR_RXTOG_MASK)

#define UART_GCR_SWAP_SHIFT                     (8)
#define UART_GCR_SWAP_MASK                      (0x01U << UART_GCR_SWAP_SHIFT)
#define UART_GCR_SWAP(x)                        (((uint32_t)(((uint32_t)(x)) << UART_GCR_SWAP_SHIFT)) & UART_GCR_SWAP_MASK)

#define UART_GCR_SELB8_SHIFT                    (7)
#define UART_GCR_SELB8_MASK                     (0x01U << UART_GCR_SELB8_SHIFT)
#define UART_GCR_SELB8(x)                       (((uint32_t)(((uint32_t)(x)) << UART_GCR_SELB8_SHIFT)) & UART_GCR_SELB8_MASK)

#define UART_GCR_TXEN_SHIFT                     (4)
#define UART_GCR_TXEN_MASK                      (0x01U << UART_GCR_TXEN_SHIFT)
#define UART_GCR_TXEN(x)                        (((uint32_t)(((uint32_t)(x)) << UART_GCR_TXEN_SHIFT)) & UART_GCR_TXEN_MASK)

#define UART_GCR_RXEN_SHIFT                     (3)
#define UART_GCR_RXEN_MASK                      (0x01U << UART_GCR_RXEN_SHIFT)
#define UART_GCR_RXEN(x)                        (((uint32_t)(((uint32_t)(x)) << UART_GCR_RXEN_SHIFT)) & UART_GCR_RXEN_MASK)

#define UART_GCR_AUTOFLOWEN_SHIFT               (2)
#define UART_GCR_AUTOFLOWEN_MASK                (0x01U << UART_GCR_AUTOFLOWEN_SHIFT)
#define UART_GCR_AUTOFLOWEN(x)                  (((uint32_t)(((uint32_t)(x)) << UART_GCR_AUTOFLOWEN_SHIFT)) & UART_GCR_AUTOFLOWEN_MASK)

#define UART_GCR_DMAMODE_SHIFT                  (1)
#define UART_GCR_DMAMODE_MASK                   (0x01U << UART_GCR_DMAMODE_SHIFT)
#define UART_GCR_DMAMODE(x)                     (((uint32_t)(((uint32_t)(x)) << UART_GCR_DMAMODE_SHIFT)) & UART_GCR_DMAMODE_MASK)

#define UART_GCR_UARTEN_SHIFT                   (0)
#define UART_GCR_UARTEN_MASK                    (0x01U << UART_GCR_UARTEN_SHIFT)
#define UART_GCR_UARTEN(x)                      (((uint32_t)(((uint32_t)(x)) << UART_GCR_UARTEN_SHIFT)) & UART_GCR_UARTEN_MASK)

/*!
 * @brief UART_CCR Register Bit Definition
 */

#define UART_CCR_LIN_SHIFT                      (14)
#define UART_CCR_LIN_MASK                       (0x01U << UART_CCR_LIN_SHIFT)
#define UART_CCR_LIN(x)                         (((uint32_t)(((uint32_t)(x)) << UART_CCR_LIN_SHIFT)) & UART_CCR_LIN_MASK)

#define UART_CCR_WAKE_SHIFT                     (13)
#define UART_CCR_WAKE_MASK                      (0x01U << UART_CCR_WAKE_SHIFT)
#define UART_CCR_WAKE(x)                        (((uint32_t)(((uint32_t)(x)) << UART_CCR_WAKE_SHIFT)) & UART_CCR_WAKE_MASK)

#define UART_CCR_RWU_SHIFT                      (12)
#define UART_CCR_RWU_MASK                       (0x01U << UART_CCR_RWU_SHIFT)
#define UART_CCR_RWU(x)                         (((uint32_t)(((uint32_t)(x)) << UART_CCR_RWU_SHIFT)) & UART_CCR_RWU_MASK)

#define UART_CCR_B8EN_SHIFT                     (11)
#define UART_CCR_B8EN_MASK                      (0x01U << UART_CCR_B8EN_SHIFT)
#define UART_CCR_B8EN(x)                        (((uint32_t)(((uint32_t)(x)) << UART_CCR_B8EN_SHIFT)) & UART_CCR_B8EN_MASK)

#define UART_CCR_B8TOG_SHIFT                    (10)
#define UART_CCR_B8TOG_MASK                     (0x01U << UART_CCR_B8TOG_SHIFT)
#define UART_CCR_B8TOG(x)                       (((uint32_t)(((uint32_t)(x)) << UART_CCR_B8TOG_SHIFT)) & UART_CCR_B8TOG_MASK)

#define UART_CCR_B8POL_SHIFT                    (9)
#define UART_CCR_B8POL_MASK                     (0x01U << UART_CCR_B8POL_SHIFT)
#define UART_CCR_B8POL(x)                       (((uint32_t)(((uint32_t)(x)) << UART_CCR_B8POL_SHIFT)) & UART_CCR_B8POL_MASK)

#define UART_CCR_B8TXD_SHIFT                    (8)
#define UART_CCR_B8TXD_MASK                     (0x01U << UART_CCR_B8TXD_SHIFT)
#define UART_CCR_B8TXD(x)                       (((uint32_t)(((uint32_t)(x)) << UART_CCR_B8TXD_SHIFT)) & UART_CCR_B8TXD_MASK)

#define UART_CCR_B8RXD_SHIFT                    (7)
#define UART_CCR_B8RXD_MASK                     (0x01U << UART_CCR_B8RXD_SHIFT)
#define UART_CCR_B8RXD(x)                       (((uint32_t)(((uint32_t)(x)) << UART_CCR_B8RXD_SHIFT)) & UART_CCR_B8RXD_MASK)

#define UART_CCR_SPB1_SHIFT                     (6)
#define UART_CCR_SPB1_MASK                      (0x01U << UART_CCR_SPB1_SHIFT)
#define UART_CCR_SPB1(x)                        (((uint32_t)(((uint32_t)(x)) << UART_CCR_SPB1_SHIFT)) & UART_CCR_SPB1_MASK)

#define UART_CCR_CHAR_SHIFT                     (4)
#define UART_CCR_CHAR_MASK                      (0x3U << UART_CCR_CHAR_SHIFT)
#define UART_CCR_CHAR(x)                        (((uint32_t)(((uint32_t)(x)) << UART_CCR_CHAR_SHIFT)) & UART_CCR_CHAR_MASK)

#define UART_CCR_BRK_SHIFT                      (3)
#define UART_CCR_BRK_MASK                       (0x01U << UART_CCR_BRK_SHIFT)
#define UART_CCR_BRK(x)                         (((uint32_t)(((uint32_t)(x)) << UART_CCR_BRK_SHIFT)) & UART_CCR_BRK_MASK)

#define UART_CCR_SPB0_SHIFT                     (2)
#define UART_CCR_SPB0_MASK                      (0x01U << UART_CCR_SPB0_SHIFT)
#define UART_CCR_SPB0(x)                        (((uint32_t)(((uint32_t)(x)) << UART_CCR_SPB0_SHIFT)) & UART_CCR_SPB0_MASK)

#define UART_CCR_PSEL_SHIFT                     (1)
#define UART_CCR_PSEL_MASK                      (0x01U << UART_CCR_PSEL_SHIFT)
#define UART_CCR_PSEL(x)                        (((uint32_t)(((uint32_t)(x)) << UART_CCR_PSEL_SHIFT)) & UART_CCR_PSEL_MASK)

#define UART_CCR_PEN_SHIFT                      (0)
#define UART_CCR_PEN_MASK                       (0x01U << UART_CCR_PEN_SHIFT)
#define UART_CCR_PEN(x)                         (((uint32_t)(((uint32_t)(x)) << UART_CCR_PEN_SHIFT)) & UART_CCR_PEN_MASK)

/*!
 * @brief UART_BRR Register Bit Definition
 */

#define UART_BRR_DIVMANTISSA_SHIFT              (0)
#define UART_BRR_DIVMANTISSA_MASK               (0xFFFFU << UART_BRR_DIVMANTISSA_SHIFT)
#define UART_BRR_DIVMANTISSA(x)                 (((uint32_t)(((uint32_t)(x)) << UART_BRR_DIVMANTISSA_SHIFT)) & UART_BRR_DIVMANTISSA_MASK)

/*!
 * @brief UART_FRA Register Bit Definition
 */

#define UART_FRA_DIVFRACTION_SHIFT              (0)
#define UART_FRA_DIVFRACTION_MASK               (0xFFFFU << UART_FRA_DIVFRACTION_SHIFT)
#define UART_FRA_DIVFRACTION(x)                 (((uint32_t)(((uint32_t)(x)) << UART_FRA_DIVFRACTION_SHIFT)) & UART_FRA_DIVFRACTION_MASK)

/*!
 * @brief UART_RXADDR Register Bit Definition
 */

#define UART_RXADDR_RXADDR_SHIFT                (0)
#define UART_RXADDR_RXADDR_MASK                 (0xFFU << UART_RXADDR_RXADDR_SHIFT)
#define UART_RXADDR_RXADDR(x)                   (((uint32_t)(((uint32_t)(x)) << UART_RXADDR_RXADDR_SHIFT)) & UART_RXADDR_RXADDR_MASK)

/*!
 * @brief UART_RXMASK Register Bit Definition
 */

#define UART_RXMASK_RXMASK_SHIFT                (0)
#define UART_RXMASK_RXMASK_MASK                 (0xFFU << UART_RXMASK_RXMASK_SHIFT)
#define UART_RXMASK_RXMASK(x)                   (((uint32_t)(((uint32_t)(x)) << UART_RXMASK_RXMASK_SHIFT)) & UART_RXMASK_RXMASK_MASK)

/*!
 * @brief UART_SCR Register Bit Definition
 */

#define UART_SCR_HDSEL_SHIFT                    (12)
#define UART_SCR_HDSEL_MASK                     (0x01U << UART_SCR_HDSEL_SHIFT)
#define UART_SCR_HDSEL(x)                       (((uint32_t)(((uint32_t)(x)) << UART_SCR_HDSEL_SHIFT)) & UART_SCR_HDSEL_MASK)

#define UART_SCR_SCFCNT_SHIFT                   (4)
#define UART_SCR_SCFCNT_MASK                    (0xFFU << UART_SCR_SCFCNT_SHIFT)
#define UART_SCR_SCFCNT(x)                      (((uint32_t)(((uint32_t)(x)) << UART_SCR_SCFCNT_SHIFT)) & UART_SCR_SCFCNT_MASK)

#define UART_SCR_NACK_SHIFT                     (2)
#define UART_SCR_NACK_MASK                      (0x01U << UART_SCR_NACK_SHIFT)
#define UART_SCR_NACK(x)                        (((uint32_t)(((uint32_t)(x)) << UART_SCR_NACK_SHIFT)) & UART_SCR_NACK_MASK)

#define UART_SCR_SCAEN_SHIFT                    (1)
#define UART_SCR_SCAEN_MASK                     (0x01U << UART_SCR_SCAEN_SHIFT)
#define UART_SCR_SCAEN(x)                       (((uint32_t)(((uint32_t)(x)) << UART_SCR_SCAEN_SHIFT)) & UART_SCR_SCAEN_MASK)

#define UART_SCR_SCEN_SHIFT                     (0)
#define UART_SCR_SCEN_MASK                      (0x01U << UART_SCR_SCEN_SHIFT)
#define UART_SCR_SCEN(x)                        (((uint32_t)(((uint32_t)(x)) << UART_SCR_SCEN_SHIFT)) & UART_SCR_SCEN_MASK)

/*!
 * @brief UART_IDLR Register Bit Definition
 */

#define UART_IDLR_IDLR_SHIFT                    (0)
#define UART_IDLR_IDLR_MASK                     (0xFFFFU << UART_IDLR_IDLR_SHIFT)
#define UART_IDLR_IDLR(x)                       (((uint32_t)(((uint32_t)(x)) << UART_IDLR_IDLR_SHIFT)) & UART_IDLR_IDLR_MASK)

/*!
 * @brief UART_ABRCR Register Bit Definition
 */

#define UART_ABRCR_LATTEREDGE_SHIFT             (4)
#define UART_ABRCR_LATTEREDGE_MASK              (0x01U << UART_ABRCR_LATTEREDGE_SHIFT)
#define UART_ABRCR_LATTEREDGE(x)                (((uint32_t)(((uint32_t)(x)) << UART_ABRCR_LATTEREDGE_SHIFT)) & UART_ABRCR_LATTEREDGE_MASK)

#define UART_ABRCR_FORMEREDGE_SHIFT             (3)
#define UART_ABRCR_FORMEREDGE_MASK              (0x01U << UART_ABRCR_FORMEREDGE_SHIFT)
#define UART_ABRCR_FORMEREDGE(x)                (((uint32_t)(((uint32_t)(x)) << UART_ABRCR_FORMEREDGE_SHIFT)) & UART_ABRCR_FORMEREDGE_MASK)

#define UART_ABRCR_ABRBITCNT_SHIFT              (1)
#define UART_ABRCR_ABRBITCNT_MASK               (0x3U << UART_ABRCR_ABRBITCNT_SHIFT)
#define UART_ABRCR_ABRBITCNT(x)                 (((uint32_t)(((uint32_t)(x)) << UART_ABRCR_ABRBITCNT_SHIFT)) & UART_ABRCR_ABRBITCNT_MASK)

#define UART_ABRCR_ABREN_SHIFT                  (0)
#define UART_ABRCR_ABREN_MASK                   (0x01U << UART_ABRCR_ABREN_SHIFT)
#define UART_ABRCR_ABREN(x)                     (((uint32_t)(((uint32_t)(x)) << UART_ABRCR_ABREN_SHIFT)) & UART_ABRCR_ABREN_MASK)

/*!
 * @brief UART_IRDA Register Bit Definition
 */

#define UART_IRDA_PSCREG_SHIFT                  (8)
#define UART_IRDA_PSCREG_MASK                   (0xFFU << UART_IRDA_PSCREG_SHIFT)
#define UART_IRDA_PSCREG(x)                     (((uint32_t)(((uint32_t)(x)) << UART_IRDA_PSCREG_SHIFT)) & UART_IRDA_PSCREG_MASK)

#define UART_IRDA_SIRLP_SHIFT                   (1)
#define UART_IRDA_SIRLP_MASK                    (0x01U << UART_IRDA_SIRLP_SHIFT)
#define UART_IRDA_SIRLP(x)                      (((uint32_t)(((uint32_t)(x)) << UART_IRDA_SIRLP_SHIFT)) & UART_IRDA_SIRLP_MASK)

#define UART_IRDA_SIREN_SHIFT                   (0)
#define UART_IRDA_SIREN_MASK                    (0x01U << UART_IRDA_SIREN_SHIFT)
#define UART_IRDA_SIREN(x)                      (((uint32_t)(((uint32_t)(x)) << UART_IRDA_SIREN_SHIFT)) & UART_IRDA_SIREN_MASK)

/*!
 * @}
 */ /* end of group UART_Register_Masks */
/******************************************************************************
 * UART Instance
******************************************************************************/
#define UART1                               ((UART_Type*)UART1_BASE)
#define UART2                               ((UART_Type*)UART2_BASE)
#define UART3                               ((UART_Type*)UART3_BASE)
#define UART4                               ((UART_Type*)UART4_BASE)
#define UART5                               ((UART_Type*)UART5_BASE)
#define UART6                               ((UART_Type*)UART6_BASE)
#define UART7                               ((UART_Type*)UART7_BASE)
#define UART8                               ((UART_Type*)UART8_BASE)

/*!
 * @}
 */ /* end of group UART_Peripheral_Access_Layer */



/*!
 * @addtogroup SPI_Peripheral_Access_Layer SPI Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * SPI Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t TXREG;                                                      ///< Send data register                           offset: 0x00
    __IO uint32_t RXREG;                                                      ///< Receive data register                        offset: 0x04
    __IO uint32_t CSTAT;                                                      ///< Current status register                      offset: 0x08
    __IO uint32_t INTSTAT;                                                    ///< Interrupt status register                    offset: 0x0C
    __IO uint32_t INTEN;                                                      ///< Interrupt enable register                    offset: 0x10
    __IO uint32_t INTCLR;                                                     ///< Interrupt clear register                     offset: 0x14
    __IO uint32_t GCTL;                                                       ///< Global control register                      offset: 0x18
    __IO uint32_t CCTL;                                                       ///< General control register                     offset: 0x1C
    __IO uint32_t SPBRG;                                                      ///< Baud rate generator                          offset: 0x20
    __IO uint32_t RXDNR;                                                      ///< Received data number register                offset: 0x24
    __IO uint32_t NSSR;                                                       ///< Slave chip select register                   offset: 0x28
    __IO uint32_t EXTCTL;                                                     ///< Data control register                        offset: 0x2C
    __IO uint32_t I2SCFGR;                                                    ///< I2S configuration register                   offset: 0x30
} SPI_Type;

/*******************************************************************************
 * SPI Type
 ******************************************************************************/

/*!
 * @addtogroup SPI_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief SPI_I2S_TXREG Register Bit Definition
 */

#define SPI_I2S_TXREG_TXREG_SHIFT               (0)
#define SPI_I2S_TXREG_TXREG_MASK                (0xFFFFFFFFU << SPI_I2S_TXREG_TXREG_SHIFT)
#define SPI_I2S_TXREG_TXREG(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_I2S_TXREG_TXREG_SHIFT)) & SPI_I2S_TXREG_TXREG_MASK)

/*!
 * @brief SPI_I2S_RXREG Register Bit Definition
 */

#define SPI_I2S_RXREG_RXREG_SHIFT               (0)
#define SPI_I2S_RXREG_RXREG_MASK                (0xFFFFFFFFU << SPI_I2S_RXREG_RXREG_SHIFT)
#define SPI_I2S_RXREG_RXREG(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_I2S_RXREG_RXREG_SHIFT)) & SPI_I2S_RXREG_RXREG_MASK)

/*!
 * @brief SPI_I2S_CSTAT Register Bit Definition
 */

#define SPI_I2S_CSTAT_CHSIDE_SHIFT              (13)
#define SPI_I2S_CSTAT_CHSIDE_MASK               (0x01U << SPI_I2S_CSTAT_CHSIDE_SHIFT)
#define SPI_I2S_CSTAT_CHSIDE(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CSTAT_CHSIDE_SHIFT)) & SPI_I2S_CSTAT_CHSIDE_MASK)

#define SPI_I2S_CSTAT_BUSY_SHIFT                (12)
#define SPI_I2S_CSTAT_BUSY_MASK                 (0x01U << SPI_I2S_CSTAT_BUSY_SHIFT)
#define SPI_I2S_CSTAT_BUSY(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CSTAT_BUSY_SHIFT)) & SPI_I2S_CSTAT_BUSY_MASK)

#define SPI_I2S_CSTAT_RXFADDR_SHIFT             (8)
#define SPI_I2S_CSTAT_RXFADDR_MASK              (0xFU << SPI_I2S_CSTAT_RXFADDR_SHIFT)
#define SPI_I2S_CSTAT_RXFADDR(x)                (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CSTAT_RXFADDR_SHIFT)) & SPI_I2S_CSTAT_RXFADDR_MASK)

#define SPI_I2S_CSTAT_TXFADDR_SHIFT             (4)
#define SPI_I2S_CSTAT_TXFADDR_MASK              (0xFU << SPI_I2S_CSTAT_TXFADDR_SHIFT)
#define SPI_I2S_CSTAT_TXFADDR(x)                (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CSTAT_TXFADDR_SHIFT)) & SPI_I2S_CSTAT_TXFADDR_MASK)

#define SPI_I2S_CSTAT_RXAVL4BYTE_SHIFT          (3)
#define SPI_I2S_CSTAT_RXAVL4BYTE_MASK           (0x01U << SPI_I2S_CSTAT_RXAVL4BYTE_SHIFT)
#define SPI_I2S_CSTAT_RXAVL4BYTE(x)             (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CSTAT_RXAVL4BYTE_SHIFT)) & SPI_I2S_CSTAT_RXAVL4BYTE_MASK)

#define SPI_I2S_CSTAT_TXFULL_SHIFT              (2)
#define SPI_I2S_CSTAT_TXFULL_MASK               (0x01U << SPI_I2S_CSTAT_TXFULL_SHIFT)
#define SPI_I2S_CSTAT_TXFULL(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CSTAT_TXFULL_SHIFT)) & SPI_I2S_CSTAT_TXFULL_MASK)

#define SPI_I2S_CSTAT_RXAVL_SHIFT               (1)
#define SPI_I2S_CSTAT_RXAVL_MASK                (0x01U << SPI_I2S_CSTAT_RXAVL_SHIFT)
#define SPI_I2S_CSTAT_RXAVL(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CSTAT_RXAVL_SHIFT)) & SPI_I2S_CSTAT_RXAVL_MASK)

#define SPI_I2S_CSTAT_TXEPT_SHIFT               (0)
#define SPI_I2S_CSTAT_TXEPT_MASK                (0x01U << SPI_I2S_CSTAT_TXEPT_SHIFT)
#define SPI_I2S_CSTAT_TXEPT(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CSTAT_TXEPT_SHIFT)) & SPI_I2S_CSTAT_TXEPT_MASK)

/*!
 * @brief SPI_I2S_INTSTAT Register Bit Definition
 */

#define SPI_I2S_INTSTAT_FREINTF_SHIFT           (7)
#define SPI_I2S_INTSTAT_FREINTF_MASK            (0x01U << SPI_I2S_INTSTAT_FREINTF_SHIFT)
#define SPI_I2S_INTSTAT_FREINTF(x)              (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTSTAT_FREINTF_SHIFT)) & SPI_I2S_INTSTAT_FREINTF_MASK)

#define SPI_I2S_INTSTAT_TXEPTINTF_SHIFT         (6)
#define SPI_I2S_INTSTAT_TXEPTINTF_MASK          (0x01U << SPI_I2S_INTSTAT_TXEPTINTF_SHIFT)
#define SPI_I2S_INTSTAT_TXEPTINTF(x)            (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTSTAT_TXEPTINTF_SHIFT)) & SPI_I2S_INTSTAT_TXEPTINTF_MASK)

#define SPI_I2S_INTSTAT_RXFULLINTF_SHIFT        (5)
#define SPI_I2S_INTSTAT_RXFULLINTF_MASK         (0x01U << SPI_I2S_INTSTAT_RXFULLINTF_SHIFT)
#define SPI_I2S_INTSTAT_RXFULLINTF(x)           (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTSTAT_RXFULLINTF_SHIFT)) & SPI_I2S_INTSTAT_RXFULLINTF_MASK)

#define SPI_I2S_INTSTAT_RXMATCHINTF_SHIFT       (4)
#define SPI_I2S_INTSTAT_RXMATCHINTF_MASK        (0x01U << SPI_I2S_INTSTAT_RXMATCHINTF_SHIFT)
#define SPI_I2S_INTSTAT_RXMATCHINTF(x)          (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTSTAT_RXMATCHINTF_SHIFT)) & SPI_I2S_INTSTAT_RXMATCHINTF_MASK)

#define SPI_I2S_INTSTAT_RXOERRINTF_SHIFT        (3)
#define SPI_I2S_INTSTAT_RXOERRINTF_MASK         (0x01U << SPI_I2S_INTSTAT_RXOERRINTF_SHIFT)
#define SPI_I2S_INTSTAT_RXOERRINTF(x)           (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTSTAT_RXOERRINTF_SHIFT)) & SPI_I2S_INTSTAT_RXOERRINTF_MASK)

#define SPI_I2S_INTSTAT_UNDERRUNINTF_SHIFT      (2)
#define SPI_I2S_INTSTAT_UNDERRUNINTF_MASK       (0x01U << SPI_I2S_INTSTAT_UNDERRUNINTF_SHIFT)
#define SPI_I2S_INTSTAT_UNDERRUNINTF(x)         (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTSTAT_UNDERRUNINTF_SHIFT)) & SPI_I2S_INTSTAT_UNDERRUNINTF_MASK)

#define SPI_I2S_INTSTAT_RXINTF_SHIFT            (1)
#define SPI_I2S_INTSTAT_RXINTF_MASK             (0x01U << SPI_I2S_INTSTAT_RXINTF_SHIFT)
#define SPI_I2S_INTSTAT_RXINTF(x)               (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTSTAT_RXINTF_SHIFT)) & SPI_I2S_INTSTAT_RXINTF_MASK)

#define SPI_I2S_INTSTAT_TXINTF_SHIFT            (0)
#define SPI_I2S_INTSTAT_TXINTF_MASK             (0x01U << SPI_I2S_INTSTAT_TXINTF_SHIFT)
#define SPI_I2S_INTSTAT_TXINTF(x)               (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTSTAT_TXINTF_SHIFT)) & SPI_I2S_INTSTAT_TXINTF_MASK)

/*!
 * @brief SPI_I2S_INTEN Register Bit Definition
 */

#define SPI_I2S_INTEN_FREIEN_SHIFT              (7)
#define SPI_I2S_INTEN_FREIEN_MASK               (0x01U << SPI_I2S_INTEN_FREIEN_SHIFT)
#define SPI_I2S_INTEN_FREIEN(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTEN_FREIEN_SHIFT)) & SPI_I2S_INTEN_FREIEN_MASK)

#define SPI_I2S_INTEN_TXEPTIEN_SHIFT            (6)
#define SPI_I2S_INTEN_TXEPTIEN_MASK             (0x01U << SPI_I2S_INTEN_TXEPTIEN_SHIFT)
#define SPI_I2S_INTEN_TXEPTIEN(x)               (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTEN_TXEPTIEN_SHIFT)) & SPI_I2S_INTEN_TXEPTIEN_MASK)

#define SPI_I2S_INTEN_RXFULLIEN_SHIFT           (5)
#define SPI_I2S_INTEN_RXFULLIEN_MASK            (0x01U << SPI_I2S_INTEN_RXFULLIEN_SHIFT)
#define SPI_I2S_INTEN_RXFULLIEN(x)              (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTEN_RXFULLIEN_SHIFT)) & SPI_I2S_INTEN_RXFULLIEN_MASK)

#define SPI_I2S_INTEN_RXMATCHIEN_SHIFT          (4)
#define SPI_I2S_INTEN_RXMATCHIEN_MASK           (0x01U << SPI_I2S_INTEN_RXMATCHIEN_SHIFT)
#define SPI_I2S_INTEN_RXMATCHIEN(x)             (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTEN_RXMATCHIEN_SHIFT)) & SPI_I2S_INTEN_RXMATCHIEN_MASK)

#define SPI_I2S_INTEN_RXOERRIEN_SHIFT           (3)
#define SPI_I2S_INTEN_RXOERRIEN_MASK            (0x01U << SPI_I2S_INTEN_RXOERRIEN_SHIFT)
#define SPI_I2S_INTEN_RXOERRIEN(x)              (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTEN_RXOERRIEN_SHIFT)) & SPI_I2S_INTEN_RXOERRIEN_MASK)

#define SPI_I2S_INTEN_UNDERRUNIEN_SHIFT         (2)
#define SPI_I2S_INTEN_UNDERRUNIEN_MASK          (0x01U << SPI_I2S_INTEN_UNDERRUNIEN_SHIFT)
#define SPI_I2S_INTEN_UNDERRUNIEN(x)            (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTEN_UNDERRUNIEN_SHIFT)) & SPI_I2S_INTEN_UNDERRUNIEN_MASK)

#define SPI_I2S_INTEN_RXIEN_SHIFT               (1)
#define SPI_I2S_INTEN_RXIEN_MASK                (0x01U << SPI_I2S_INTEN_RXIEN_SHIFT)
#define SPI_I2S_INTEN_RXIEN(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTEN_RXIEN_SHIFT)) & SPI_I2S_INTEN_RXIEN_MASK)

#define SPI_I2S_INTEN_TXIEN_SHIFT               (0)
#define SPI_I2S_INTEN_TXIEN_MASK                (0x01U << SPI_I2S_INTEN_TXIEN_SHIFT)
#define SPI_I2S_INTEN_TXIEN(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTEN_TXIEN_SHIFT)) & SPI_I2S_INTEN_TXIEN_MASK)

/*!
 * @brief SPI_I2S_INTCLR Register Bit Definition
 */

#define SPI_I2S_INTCLR_FREICLR_SHIFT            (7)
#define SPI_I2S_INTCLR_FREICLR_MASK             (0x01U << SPI_I2S_INTCLR_FREICLR_SHIFT)
#define SPI_I2S_INTCLR_FREICLR(x)               (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTCLR_FREICLR_SHIFT)) & SPI_I2S_INTCLR_FREICLR_MASK)

#define SPI_I2S_INTCLR_TXEPTICLR_SHIFT          (6)
#define SPI_I2S_INTCLR_TXEPTICLR_MASK           (0x01U << SPI_I2S_INTCLR_TXEPTICLR_SHIFT)
#define SPI_I2S_INTCLR_TXEPTICLR(x)             (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTCLR_TXEPTICLR_SHIFT)) & SPI_I2S_INTCLR_TXEPTICLR_MASK)

#define SPI_I2S_INTCLR_RXFULLICLR_SHIFT         (5)
#define SPI_I2S_INTCLR_RXFULLICLR_MASK          (0x01U << SPI_I2S_INTCLR_RXFULLICLR_SHIFT)
#define SPI_I2S_INTCLR_RXFULLICLR(x)            (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTCLR_RXFULLICLR_SHIFT)) & SPI_I2S_INTCLR_RXFULLICLR_MASK)

#define SPI_I2S_INTCLR_RXMATCHICLR_SHIFT        (4)
#define SPI_I2S_INTCLR_RXMATCHICLR_MASK         (0x01U << SPI_I2S_INTCLR_RXMATCHICLR_SHIFT)
#define SPI_I2S_INTCLR_RXMATCHICLR(x)           (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTCLR_RXMATCHICLR_SHIFT)) & SPI_I2S_INTCLR_RXMATCHICLR_MASK)

#define SPI_I2S_INTCLR_RXOERRICLR_SHIFT         (3)
#define SPI_I2S_INTCLR_RXOERRICLR_MASK          (0x01U << SPI_I2S_INTCLR_RXOERRICLR_SHIFT)
#define SPI_I2S_INTCLR_RXOERRICLR(x)            (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTCLR_RXOERRICLR_SHIFT)) & SPI_I2S_INTCLR_RXOERRICLR_MASK)

#define SPI_I2S_INTCLR_UNDERRUNICLR_SHIFT       (2)
#define SPI_I2S_INTCLR_UNDERRUNICLR_MASK        (0x01U << SPI_I2S_INTCLR_UNDERRUNICLR_SHIFT)
#define SPI_I2S_INTCLR_UNDERRUNICLR(x)          (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTCLR_UNDERRUNICLR_SHIFT)) & SPI_I2S_INTCLR_UNDERRUNICLR_MASK)

#define SPI_I2S_INTCLR_RXICLR_SHIFT             (1)
#define SPI_I2S_INTCLR_RXICLR_MASK              (0x01U << SPI_I2S_INTCLR_RXICLR_SHIFT)
#define SPI_I2S_INTCLR_RXICLR(x)                (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTCLR_RXICLR_SHIFT)) & SPI_I2S_INTCLR_RXICLR_MASK)

#define SPI_I2S_INTCLR_TXICLR_SHIFT             (0)
#define SPI_I2S_INTCLR_TXICLR_MASK              (0x01U << SPI_I2S_INTCLR_TXICLR_SHIFT)
#define SPI_I2S_INTCLR_TXICLR(x)                (((uint32_t)(((uint32_t)(x)) << SPI_I2S_INTCLR_TXICLR_SHIFT)) & SPI_I2S_INTCLR_TXICLR_MASK)

/*!
 * @brief SPI_I2S_GCTL Register Bit Definition
 */

#define SPI_I2S_GCTL_PADSEL_SHIFT               (13)
#define SPI_I2S_GCTL_PADSEL_MASK                (0x1FU << SPI_I2S_GCTL_PADSEL_SHIFT)
#define SPI_I2S_GCTL_PADSEL(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_I2S_GCTL_PADSEL_SHIFT)) & SPI_I2S_GCTL_PADSEL_MASK)

#define SPI_I2S_GCTL_NSSTOG_SHIFT               (12)
#define SPI_I2S_GCTL_NSSTOG_MASK                (0x01U << SPI_I2S_GCTL_NSSTOG_SHIFT)
#define SPI_I2S_GCTL_NSSTOG(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_I2S_GCTL_NSSTOG_SHIFT)) & SPI_I2S_GCTL_NSSTOG_MASK)

#define SPI_I2S_GCTL_DW832_SHIFT                (11)
#define SPI_I2S_GCTL_DW832_MASK                 (0x01U << SPI_I2S_GCTL_DW832_SHIFT)
#define SPI_I2S_GCTL_DW832(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_I2S_GCTL_DW832_SHIFT)) & SPI_I2S_GCTL_DW832_MASK)

#define SPI_I2S_GCTL_NSS_SHIFT                  (10)
#define SPI_I2S_GCTL_NSS_MASK                   (0x01U << SPI_I2S_GCTL_NSS_SHIFT)
#define SPI_I2S_GCTL_NSS(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_I2S_GCTL_NSS_SHIFT)) & SPI_I2S_GCTL_NSS_MASK)

#define SPI_I2S_GCTL_DMAMODE_SHIFT              (9)
#define SPI_I2S_GCTL_DMAMODE_MASK               (0x01U << SPI_I2S_GCTL_DMAMODE_SHIFT)
#define SPI_I2S_GCTL_DMAMODE(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_I2S_GCTL_DMAMODE_SHIFT)) & SPI_I2S_GCTL_DMAMODE_MASK)

#define SPI_I2S_GCTL_RXEN_SHIFT                 (4)
#define SPI_I2S_GCTL_RXEN_MASK                  (0x01U << SPI_I2S_GCTL_RXEN_SHIFT)
#define SPI_I2S_GCTL_RXEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_I2S_GCTL_RXEN_SHIFT)) & SPI_I2S_GCTL_RXEN_MASK)

#define SPI_I2S_GCTL_TXEN_SHIFT                 (3)
#define SPI_I2S_GCTL_TXEN_MASK                  (0x01U << SPI_I2S_GCTL_TXEN_SHIFT)
#define SPI_I2S_GCTL_TXEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_I2S_GCTL_TXEN_SHIFT)) & SPI_I2S_GCTL_TXEN_MASK)

#define SPI_I2S_GCTL_MODE_SHIFT                 (2)
#define SPI_I2S_GCTL_MODE_MASK                  (0x01U << SPI_I2S_GCTL_MODE_SHIFT)
#define SPI_I2S_GCTL_MODE(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_I2S_GCTL_MODE_SHIFT)) & SPI_I2S_GCTL_MODE_MASK)

#define SPI_I2S_GCTL_INTEN_SHIFT                (1)
#define SPI_I2S_GCTL_INTEN_MASK                 (0x01U << SPI_I2S_GCTL_INTEN_SHIFT)
#define SPI_I2S_GCTL_INTEN(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_I2S_GCTL_INTEN_SHIFT)) & SPI_I2S_GCTL_INTEN_MASK)

#define SPI_I2S_GCTL_SPIEN_SHIFT                (0)
#define SPI_I2S_GCTL_SPIEN_MASK                 (0x01U << SPI_I2S_GCTL_SPIEN_SHIFT)
#define SPI_I2S_GCTL_SPIEN(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_I2S_GCTL_SPIEN_SHIFT)) & SPI_I2S_GCTL_SPIEN_MASK)

/*!
 * @brief SPI_I2S_CCTL Register Bit Definition
 */

#define SPI_I2S_CCTL_CPHASEL_SHIFT              (6)
#define SPI_I2S_CCTL_CPHASEL_MASK               (0x01U << SPI_I2S_CCTL_CPHASEL_SHIFT)
#define SPI_I2S_CCTL_CPHASEL(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CCTL_CPHASEL_SHIFT)) & SPI_I2S_CCTL_CPHASEL_MASK)

#define SPI_I2S_CCTL_TXEDGE_SHIFT               (5)
#define SPI_I2S_CCTL_TXEDGE_MASK                (0x01U << SPI_I2S_CCTL_TXEDGE_SHIFT)
#define SPI_I2S_CCTL_TXEDGE(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CCTL_TXEDGE_SHIFT)) & SPI_I2S_CCTL_TXEDGE_MASK)

#define SPI_I2S_CCTL_RXEDGE_SHIFT               (4)
#define SPI_I2S_CCTL_RXEDGE_MASK                (0x01U << SPI_I2S_CCTL_RXEDGE_SHIFT)
#define SPI_I2S_CCTL_RXEDGE(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CCTL_RXEDGE_SHIFT)) & SPI_I2S_CCTL_RXEDGE_MASK)

#define SPI_I2S_CCTL_SPILEN_SHIFT               (3)
#define SPI_I2S_CCTL_SPILEN_MASK                (0x01U << SPI_I2S_CCTL_SPILEN_SHIFT)
#define SPI_I2S_CCTL_SPILEN(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CCTL_SPILEN_SHIFT)) & SPI_I2S_CCTL_SPILEN_MASK)

#define SPI_I2S_CCTL_LSBFE_SHIFT                (2)
#define SPI_I2S_CCTL_LSBFE_MASK                 (0x01U << SPI_I2S_CCTL_LSBFE_SHIFT)
#define SPI_I2S_CCTL_LSBFE(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CCTL_LSBFE_SHIFT)) & SPI_I2S_CCTL_LSBFE_MASK)

#define SPI_I2S_CCTL_CPOL_SHIFT                 (1)
#define SPI_I2S_CCTL_CPOL_MASK                  (0x01U << SPI_I2S_CCTL_CPOL_SHIFT)
#define SPI_I2S_CCTL_CPOL(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CCTL_CPOL_SHIFT)) & SPI_I2S_CCTL_CPOL_MASK)

#define SPI_I2S_CCTL_CPHA_SHIFT                 (0)
#define SPI_I2S_CCTL_CPHA_MASK                  (0x01U << SPI_I2S_CCTL_CPHA_SHIFT)
#define SPI_I2S_CCTL_CPHA(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_I2S_CCTL_CPHA_SHIFT)) & SPI_I2S_CCTL_CPHA_MASK)

/*!
 * @brief SPI_I2S_SPBRG Register Bit Definition
 */

#define SPI_I2S_SPBRG_SPBRG_SHIFT               (0)
#define SPI_I2S_SPBRG_SPBRG_MASK                (0xFFFFU << SPI_I2S_SPBRG_SPBRG_SHIFT)
#define SPI_I2S_SPBRG_SPBRG(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_I2S_SPBRG_SPBRG_SHIFT)) & SPI_I2S_SPBRG_SPBRG_MASK)

/*!
 * @brief SPI_I2S_RXDNR Register Bit Definition
 */

#define SPI_I2S_RXDNR_RXDNR_SHIFT               (0)
#define SPI_I2S_RXDNR_RXDNR_MASK                (0xFFFFU << SPI_I2S_RXDNR_RXDNR_SHIFT)
#define SPI_I2S_RXDNR_RXDNR(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_I2S_RXDNR_RXDNR_SHIFT)) & SPI_I2S_RXDNR_RXDNR_MASK)

/*!
 * @brief SPI_I2S_NSSR Register Bit Definition
 */

#define SPI_I2S_NSSR_NSS_SHIFT                  (0)
#define SPI_I2S_NSSR_NSS_MASK                   (0x01U << SPI_I2S_NSSR_NSS_SHIFT)
#define SPI_I2S_NSSR_NSS(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_I2S_NSSR_NSS_SHIFT)) & SPI_I2S_NSSR_NSS_MASK)

/*!
 * @brief SPI_I2S_EXTCTL Register Bit Definition
 */

#define SPI_I2S_EXTCTL_EXTLEN_SHIFT             (0)
#define SPI_I2S_EXTCTL_EXTLEN_MASK              (0x1FU << SPI_I2S_EXTCTL_EXTLEN_SHIFT)
#define SPI_I2S_EXTCTL_EXTLEN(x)                (((uint32_t)(((uint32_t)(x)) << SPI_I2S_EXTCTL_EXTLEN_SHIFT)) & SPI_I2S_EXTCTL_EXTLEN_MASK)

/*!
 * @brief SPI_I2S_I2SCFGR Register Bit Definition
 */

#define SPI_I2S_I2SCFGR_I2SDIV_SHIFT            (16)
#define SPI_I2S_I2SCFGR_I2SDIV_MASK             (0x1FFU << SPI_I2S_I2SCFGR_I2SDIV_SHIFT)
#define SPI_I2S_I2SCFGR_I2SDIV(x)               (((uint32_t)(((uint32_t)(x)) << SPI_I2S_I2SCFGR_I2SDIV_SHIFT)) & SPI_I2S_I2SCFGR_I2SDIV_MASK)

#define SPI_I2S_I2SCFGR_MCKOE_SHIFT             (11)
#define SPI_I2S_I2SCFGR_MCKOE_MASK              (0x01U << SPI_I2S_I2SCFGR_MCKOE_SHIFT)
#define SPI_I2S_I2SCFGR_MCKOE(x)                (((uint32_t)(((uint32_t)(x)) << SPI_I2S_I2SCFGR_MCKOE_SHIFT)) & SPI_I2S_I2SCFGR_MCKOE_MASK)

#define SPI_I2S_I2SCFGR_SPII2S_SHIFT            (10)
#define SPI_I2S_I2SCFGR_SPII2S_MASK             (0x01U << SPI_I2S_I2SCFGR_SPII2S_SHIFT)
#define SPI_I2S_I2SCFGR_SPII2S(x)               (((uint32_t)(((uint32_t)(x)) << SPI_I2S_I2SCFGR_SPII2S_SHIFT)) & SPI_I2S_I2SCFGR_SPII2S_MASK)

#define SPI_I2S_I2SCFGR_PCMSYNC_SHIFT           (6)
#define SPI_I2S_I2SCFGR_PCMSYNC_MASK            (0x01U << SPI_I2S_I2SCFGR_PCMSYNC_SHIFT)
#define SPI_I2S_I2SCFGR_PCMSYNC(x)              (((uint32_t)(((uint32_t)(x)) << SPI_I2S_I2SCFGR_PCMSYNC_SHIFT)) & SPI_I2S_I2SCFGR_PCMSYNC_MASK)

#define SPI_I2S_I2SCFGR_I2SSTD_SHIFT            (4)
#define SPI_I2S_I2SCFGR_I2SSTD_MASK             (0x3U << SPI_I2S_I2SCFGR_I2SSTD_SHIFT)
#define SPI_I2S_I2SCFGR_I2SSTD(x)               (((uint32_t)(((uint32_t)(x)) << SPI_I2S_I2SCFGR_I2SSTD_SHIFT)) & SPI_I2S_I2SCFGR_I2SSTD_MASK)

#define SPI_I2S_I2SCFGR_DATLEN_SHIFT            (1)
#define SPI_I2S_I2SCFGR_DATLEN_MASK             (0x3U << SPI_I2S_I2SCFGR_DATLEN_SHIFT)
#define SPI_I2S_I2SCFGR_DATLEN(x)               (((uint32_t)(((uint32_t)(x)) << SPI_I2S_I2SCFGR_DATLEN_SHIFT)) & SPI_I2S_I2SCFGR_DATLEN_MASK)

#define SPI_I2S_I2SCFGR_CHLEN_SHIFT             (0)
#define SPI_I2S_I2SCFGR_CHLEN_MASK              (0x01U << SPI_I2S_I2SCFGR_CHLEN_SHIFT)
#define SPI_I2S_I2SCFGR_CHLEN(x)                (((uint32_t)(((uint32_t)(x)) << SPI_I2S_I2SCFGR_CHLEN_SHIFT)) & SPI_I2S_I2SCFGR_CHLEN_MASK)

/*!
 * @}
 */ /* end of group SPI_Register_Masks */
/******************************************************************************
 * SPI Instance
******************************************************************************/
#define SPI1                                ((SPI_Type*)SPI1_BASE)
#define SPI2                                ((SPI_Type*)SPI2_BASE)
#define SPI3                                ((SPI_Type*)SPI3_BASE)

/*!
 * @}
 */ /* end of group SPI_Peripheral_Access_Layer */



/*!
 * @addtogroup I2C_Peripheral_Access_Layer I2C Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * I2C Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CR;                                                             ///< I2C control register                         offset: 0x00
    __IO uint32_t TAR;                                                            ///< I2C target address register                  offset: 0x04
    __IO uint32_t SAR;                                                            ///< I2C slave address register                   offset: 0x08
    __IO uint32_t Reserved14[1];                                                   ///< Reserved
    __IO uint32_t DR;                                                             ///< I2C data command register                    offset: 0x10
    __IO uint32_t SSHR;                                                           ///< Standard mode I2C clock high level count registeroffset: 0x14
    __IO uint32_t SSLR;                                                           ///< Standard mode I2C clock low count register   offset: 0x18
    __IO uint32_t FSHR;                                                           ///< Fast mode I2C clock high level count registeroffset: 0x1C
    __IO uint32_t FSLR;                                                           ///< Fast mode I2C clock low count register       offset: 0x20
    __IO uint32_t Reserved15[2];                                                   ///< Reserved
    __IO uint32_t ISR;                                                            ///< I2C interrupt status register                offset: 0x2C
    __IO uint32_t IMR;                                                            ///< I2C interrupt mask register                  offset: 0x30
    __IO uint32_t RAWISR;                                                         ///< I2C RAW interrupt register                   offset: 0x34
    __IO uint32_t RXTLR;                                                          ///< I2C receive threshold                        offset: 0x38
    __IO uint32_t TXTLR;                                                          ///< I2C send threshold                           offset: 0x3C
    __IO uint32_t ICR;                                                            ///< I2C combination and independent interrupt clear registeroffset: 0x40
    __IO uint32_t RXUNDER;                                                       ///< I2C clears the RXUNDER interrupt register   offset: 0x44
    __IO uint32_t RXOVER;                                                        ///< I2C clears the RXOVER interrupt register    offset: 0x48
    __IO uint32_t TXOVER;                                                        ///< I2C clear TXOVER interrupt register         offset: 0x4C
    __IO uint32_t RDREQ;                                                         ///< I2C clears the RDREQ interrupt register     offset: 0x50
    __IO uint32_t TXABRT;                                                        ///< I2C clear TXABRT interrupt register         offset: 0x54
    __IO uint32_t RXDONE;                                                        ///< I2C clears the RXDONE interrupt register    offset: 0x58
    __IO uint32_t ACTIV;                                                          ///< I2C clears the ACTIVITY interrupt register   offset: 0x5C
    __IO uint32_t STOP;                                                           ///< I2C clears the STOP_DET interrupt register   offset: 0x60
    __IO uint32_t START;                                                          ///< I2C clears the START_DET interrupt register  offset: 0x64
    __IO uint32_t GC;                                                             ///< I2C clears the GEN_CALL interrupt register   offset: 0x68
    __IO uint32_t ENR;                                                            ///< I2C enable register                          offset: 0x6C
    __IO uint32_t SR;                                                             ///< I2C status register                          offset: 0x70
    __IO uint32_t TXFLR;                                                          ///< I2C transmit buffer level register           offset: 0x74
    __IO uint32_t RXFLR;                                                          ///< I2C receive buffer level register            offset: 0x78
    __IO uint32_t HOLD;                                                           ///< I2C SDA hold time register                   offset: 0x7C
    __IO uint32_t Reserved16[2];                                                   ///< Reserved
    __IO uint32_t DMA;                                                            ///< I2C DMA control register                     offset: 0x88
    __IO uint32_t Reserved17[2];                                                   ///< Reserved
    __IO uint32_t SETUP;                                                          ///< I2C SDA Setup Time Register                  offset: 0x94
    __IO uint32_t GCR;                                                            ///< I2C general call ACK register                offset: 0x98
    __IO uint32_t Reserved18[5];                                                   ///< Reserved
    __IO uint32_t SLVMASK;                                                        ///< I2C slave address mask register              offset: 0xB0
    __IO uint32_t SLVRCVADDR;                                                     ///< I2C slave receiver address register          offset: 0xB4
} I2C_Type;

/*******************************************************************************
 * I2C Type
 ******************************************************************************/

/*!
 * @addtogroup I2C_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief I2C_CR Register Bit Definition
 */

#define I2C_CR_SLVTXABRTDIS_SHIFT               (11)
#define I2C_CR_SLVTXABRTDIS_MASK                (0x01U << I2C_CR_SLVTXABRTDIS_SHIFT)
#define I2C_CR_SLVTXABRTDIS(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_CR_SLVTXABRTDIS_SHIFT)) & I2C_CR_SLVTXABRTDIS_MASK)

#define I2C_CR_RESTART_SHIFT                    (10)
#define I2C_CR_RESTART_MASK                     (0x01U << I2C_CR_RESTART_SHIFT)
#define I2C_CR_RESTART(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_CR_RESTART_SHIFT)) & I2C_CR_RESTART_MASK)

#define I2C_CR_STOP_SHIFT                       (9)
#define I2C_CR_STOP_MASK                        (0x01U << I2C_CR_STOP_SHIFT)
#define I2C_CR_STOP(x)                          (((uint32_t)(((uint32_t)(x)) << I2C_CR_STOP_SHIFT)) & I2C_CR_STOP_MASK)

#define I2C_CR_EMPINT_SHIFT                     (8)
#define I2C_CR_EMPINT_MASK                      (0x01U << I2C_CR_EMPINT_SHIFT)
#define I2C_CR_EMPINT(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_CR_EMPINT_SHIFT)) & I2C_CR_EMPINT_MASK)

#define I2C_CR_STOPINT_SHIFT                    (7)
#define I2C_CR_STOPINT_MASK                     (0x01U << I2C_CR_STOPINT_SHIFT)
#define I2C_CR_STOPINT(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_CR_STOPINT_SHIFT)) & I2C_CR_STOPINT_MASK)

#define I2C_CR_DISSLAVE_SHIFT                   (6)
#define I2C_CR_DISSLAVE_MASK                    (0x01U << I2C_CR_DISSLAVE_SHIFT)
#define I2C_CR_DISSLAVE(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_CR_DISSLAVE_SHIFT)) & I2C_CR_DISSLAVE_MASK)

#define I2C_CR_REPEN_SHIFT                      (5)
#define I2C_CR_REPEN_MASK                       (0x01U << I2C_CR_REPEN_SHIFT)
#define I2C_CR_REPEN(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_CR_REPEN_SHIFT)) & I2C_CR_REPEN_MASK)

#define I2C_CR_MASTER10_SHIFT                   (4)
#define I2C_CR_MASTER10_MASK                    (0x01U << I2C_CR_MASTER10_SHIFT)
#define I2C_CR_MASTER10(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_CR_MASTER10_SHIFT)) & I2C_CR_MASTER10_MASK)

#define I2C_CR_SLAVE10_SHIFT                    (3)
#define I2C_CR_SLAVE10_MASK                     (0x01U << I2C_CR_SLAVE10_SHIFT)
#define I2C_CR_SLAVE10(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_CR_SLAVE10_SHIFT)) & I2C_CR_SLAVE10_MASK)

#define I2C_CR_SPEED_SHIFT                      (1)
#define I2C_CR_SPEED_MASK                       (0x3U << I2C_CR_SPEED_SHIFT)
#define I2C_CR_SPEED(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_CR_SPEED_SHIFT)) & I2C_CR_SPEED_MASK)

#define I2C_CR_MASTER_SHIFT                     (0)
#define I2C_CR_MASTER_MASK                      (0x01U << I2C_CR_MASTER_SHIFT)
#define I2C_CR_MASTER(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_CR_MASTER_SHIFT)) & I2C_CR_MASTER_MASK)

/*!
 * @brief I2C_TAR Register Bit Definition
 */

#define I2C_TAR_SPECIAL_SHIFT                   (11)
#define I2C_TAR_SPECIAL_MASK                    (0x01U << I2C_TAR_SPECIAL_SHIFT)
#define I2C_TAR_SPECIAL(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_TAR_SPECIAL_SHIFT)) & I2C_TAR_SPECIAL_MASK)

#define I2C_TAR_GC_SHIFT                        (10)
#define I2C_TAR_GC_MASK                         (0x01U << I2C_TAR_GC_SHIFT)
#define I2C_TAR_GC(x)                           (((uint32_t)(((uint32_t)(x)) << I2C_TAR_GC_SHIFT)) & I2C_TAR_GC_MASK)

#define I2C_TAR_ADDR_SHIFT                      (0)
#define I2C_TAR_ADDR_MASK                       (0x3FFU << I2C_TAR_ADDR_SHIFT)
#define I2C_TAR_ADDR(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_TAR_ADDR_SHIFT)) & I2C_TAR_ADDR_MASK)

/*!
 * @brief I2C_SAR Register Bit Definition
 */

#define I2C_SAR_ADDR_SHIFT                      (0)
#define I2C_SAR_ADDR_MASK                       (0x3FFU << I2C_SAR_ADDR_SHIFT)
#define I2C_SAR_ADDR(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_SAR_ADDR_SHIFT)) & I2C_SAR_ADDR_MASK)

/*!
 * @brief I2C_DR Register Bit Definition
 */

#define I2C_DR_CMD_SHIFT                        (8)
#define I2C_DR_CMD_MASK                         (0x01U << I2C_DR_CMD_SHIFT)
#define I2C_DR_CMD(x)                           (((uint32_t)(((uint32_t)(x)) << I2C_DR_CMD_SHIFT)) & I2C_DR_CMD_MASK)

#define I2C_DR_DAT_SHIFT                        (0)
#define I2C_DR_DAT_MASK                         (0xFFU << I2C_DR_DAT_SHIFT)
#define I2C_DR_DAT(x)                           (((uint32_t)(((uint32_t)(x)) << I2C_DR_DAT_SHIFT)) & I2C_DR_DAT_MASK)

/*!
 * @brief I2C_SSHR Register Bit Definition
 */

#define I2C_SSHR_CNT_SHIFT                      (0)
#define I2C_SSHR_CNT_MASK                       (0xFFFFU << I2C_SSHR_CNT_SHIFT)
#define I2C_SSHR_CNT(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_SSHR_CNT_SHIFT)) & I2C_SSHR_CNT_MASK)

/*!
 * @brief I2C_SSLR Register Bit Definition
 */

#define I2C_SSLR_CNT_SHIFT                      (0)
#define I2C_SSLR_CNT_MASK                       (0xFFFFU << I2C_SSLR_CNT_SHIFT)
#define I2C_SSLR_CNT(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_SSLR_CNT_SHIFT)) & I2C_SSLR_CNT_MASK)

/*!
 * @brief I2C_FSHR Register Bit Definition
 */

#define I2C_FSHR_CNT_SHIFT                      (0)
#define I2C_FSHR_CNT_MASK                       (0xFFFFU << I2C_FSHR_CNT_SHIFT)
#define I2C_FSHR_CNT(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_FSHR_CNT_SHIFT)) & I2C_FSHR_CNT_MASK)

/*!
 * @brief I2C_FSLR Register Bit Definition
 */

#define I2C_FSLR_CNT_SHIFT                      (0)
#define I2C_FSLR_CNT_MASK                       (0xFFFFU << I2C_FSLR_CNT_SHIFT)
#define I2C_FSLR_CNT(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_FSLR_CNT_SHIFT)) & I2C_FSLR_CNT_MASK)

/*!
 * @brief I2C_ISR Register Bit Definition
 */

#define I2C_ISR_ISR_SHIFT                       (0)
#define I2C_ISR_ISR_MASK                        (0xFFFU << I2C_ISR_ISR_SHIFT)
#define I2C_ISR_ISR(x)                          (((uint32_t)(((uint32_t)(x)) << I2C_ISR_ISR_SHIFT)) & I2C_ISR_ISR_MASK)

/*!
 * @brief I2C_IMR Register Bit Definition
 */

#define I2C_IMR_IMR_SHIFT                       (0)
#define I2C_IMR_IMR_MASK                        (0xFFFU << I2C_IMR_IMR_SHIFT)
#define I2C_IMR_IMR(x)                          (((uint32_t)(((uint32_t)(x)) << I2C_IMR_IMR_SHIFT)) & I2C_IMR_IMR_MASK)

/*!
 * @brief I2C_RAWISR Register Bit Definition
 */

#define I2C_RAWISR_GC_SHIFT                     (11)
#define I2C_RAWISR_GC_MASK                      (0x01U << I2C_RAWISR_GC_SHIFT)
#define I2C_RAWISR_GC(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_RAWISR_GC_SHIFT)) & I2C_RAWISR_GC_MASK)

#define I2C_RAWISR_START_SHIFT                  (10)
#define I2C_RAWISR_START_MASK                   (0x01U << I2C_RAWISR_START_SHIFT)
#define I2C_RAWISR_START(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_RAWISR_START_SHIFT)) & I2C_RAWISR_START_MASK)

#define I2C_RAWISR_STOP_SHIFT                   (9)
#define I2C_RAWISR_STOP_MASK                    (0x01U << I2C_RAWISR_STOP_SHIFT)
#define I2C_RAWISR_STOP(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_RAWISR_STOP_SHIFT)) & I2C_RAWISR_STOP_MASK)

#define I2C_RAWISR_ACTIV_SHIFT                  (8)
#define I2C_RAWISR_ACTIV_MASK                   (0x01U << I2C_RAWISR_ACTIV_SHIFT)
#define I2C_RAWISR_ACTIV(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_RAWISR_ACTIV_SHIFT)) & I2C_RAWISR_ACTIV_MASK)

#define I2C_RAWISR_RXDONE_SHIFT                 (7)
#define I2C_RAWISR_RXDONE_MASK                  (0x01U << I2C_RAWISR_RXDONE_SHIFT)
#define I2C_RAWISR_RXDONE(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_RAWISR_RXDONE_SHIFT)) & I2C_RAWISR_RXDONE_MASK)

#define I2C_RAWISR_TXABRT_SHIFT                 (6)
#define I2C_RAWISR_TXABRT_MASK                  (0x01U << I2C_RAWISR_TXABRT_SHIFT)
#define I2C_RAWISR_TXABRT(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_RAWISR_TXABRT_SHIFT)) & I2C_RAWISR_TXABRT_MASK)

#define I2C_RAWISR_RDREQ_SHIFT                  (5)
#define I2C_RAWISR_RDREQ_MASK                   (0x01U << I2C_RAWISR_RDREQ_SHIFT)
#define I2C_RAWISR_RDREQ(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_RAWISR_RDREQ_SHIFT)) & I2C_RAWISR_RDREQ_MASK)

#define I2C_RAWISR_TXEMPTY_SHIFT                (4)
#define I2C_RAWISR_TXEMPTY_MASK                 (0x01U << I2C_RAWISR_TXEMPTY_SHIFT)
#define I2C_RAWISR_TXEMPTY(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_RAWISR_TXEMPTY_SHIFT)) & I2C_RAWISR_TXEMPTY_MASK)

#define I2C_RAWISR_TXOVER_SHIFT                 (3)
#define I2C_RAWISR_TXOVER_MASK                  (0x01U << I2C_RAWISR_TXOVER_SHIFT)
#define I2C_RAWISR_TXOVER(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_RAWISR_TXOVER_SHIFT)) & I2C_RAWISR_TXOVER_MASK)

#define I2C_RAWISR_RXFULL_SHIFT                 (2)
#define I2C_RAWISR_RXFULL_MASK                  (0x01U << I2C_RAWISR_RXFULL_SHIFT)
#define I2C_RAWISR_RXFULL(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_RAWISR_RXFULL_SHIFT)) & I2C_RAWISR_RXFULL_MASK)

#define I2C_RAWISR_RXOVER_SHIFT                 (1)
#define I2C_RAWISR_RXOVER_MASK                  (0x01U << I2C_RAWISR_RXOVER_SHIFT)
#define I2C_RAWISR_RXOVER(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_RAWISR_RXOVER_SHIFT)) & I2C_RAWISR_RXOVER_MASK)

#define I2C_RAWISR_RXUNDER_SHIFT                (0)
#define I2C_RAWISR_RXUNDER_MASK                 (0x01U << I2C_RAWISR_RXUNDER_SHIFT)
#define I2C_RAWISR_RXUNDER(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_RAWISR_RXUNDER_SHIFT)) & I2C_RAWISR_RXUNDER_MASK)

/*!
 * @brief I2C_RXTLR Register Bit Definition
 */

#define I2C_RXTLR_TL_SHIFT                      (0)
#define I2C_RXTLR_TL_MASK                       (0xFFU << I2C_RXTLR_TL_SHIFT)
#define I2C_RXTLR_TL(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_RXTLR_TL_SHIFT)) & I2C_RXTLR_TL_MASK)

/*!
 * @brief I2C_TXTLR Register Bit Definition
 */

#define I2C_TXTLR_TL_SHIFT                      (0)
#define I2C_TXTLR_TL_MASK                       (0xFFU << I2C_TXTLR_TL_SHIFT)
#define I2C_TXTLR_TL(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_TXTLR_TL_SHIFT)) & I2C_TXTLR_TL_MASK)

/*!
 * @brief I2C_ICR Register Bit Definition
 */

#define I2C_ICR_ICR_SHIFT                       (0)
#define I2C_ICR_ICR_MASK                        (0x01U << I2C_ICR_ICR_SHIFT)
#define I2C_ICR_ICR(x)                          (((uint32_t)(((uint32_t)(x)) << I2C_ICR_ICR_SHIFT)) & I2C_ICR_ICR_MASK)

/*!
 * @brief I2C_RXUNDER Register Bit Definition
 */

#define I2C_RXUNDER_RXUNDER_SHIFT              (0)
#define I2C_RXUNDER_RXUNDER_MASK               (0x01U << I2C_RXUNDER_RXUNDER_SHIFT)
#define I2C_RXUNDER_RXUNDER(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_RXUNDER_RXUNDER_SHIFT)) & I2C_RXUNDER_RXUNDER_MASK)

/*!
 * @brief I2C_RXOVER Register Bit Definition
 */

#define I2C_RXOVER_RXOVER_SHIFT                (0)
#define I2C_RXOVER_RXOVER_MASK                 (0x01U << I2C_RXOVER_RXOVER_SHIFT)
#define I2C_RXOVER_RXOVER(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_RXOVER_RXOVER_SHIFT)) & I2C_RXOVER_RXOVER_MASK)

/*!
 * @brief I2C_TXOVER Register Bit Definition
 */

#define I2C_TXOVER_TXOVER_SHIFT                (0)
#define I2C_TXOVER_TXOVER_MASK                 (0x01U << I2C_TXOVER_TXOVER_SHIFT)
#define I2C_TXOVER_TXOVER(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_TXOVER_TXOVER_SHIFT)) & I2C_TXOVER_TXOVER_MASK)

/*!
 * @brief I2C_RDREQ Register Bit Definition
 */

#define I2C_RDREQ_RDREQ_SHIFT                  (0)
#define I2C_RDREQ_RDREQ_MASK                   (0x01U << I2C_RDREQ_RDREQ_SHIFT)
#define I2C_RDREQ_RDREQ(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_RDREQ_RDREQ_SHIFT)) & I2C_RDREQ_RDREQ_MASK)

/*!
 * @brief I2C_TXABRT Register Bit Definition
 */

#define I2C_TXABRT_TXABRT_SHIFT                (0)
#define I2C_TXABRT_TXABRT_MASK                 (0x01U << I2C_TXABRT_TXABRT_SHIFT)
#define I2C_TXABRT_TXABRT(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_TXABRT_TXABRT_SHIFT)) & I2C_TXABRT_TXABRT_MASK)

/*!
 * @brief I2C_RXDONE Register Bit Definition
 */

#define I2C_RXDONE_RXDONE_SHIFT                (0)
#define I2C_RXDONE_RXDONE_MASK                 (0x01U << I2C_RXDONE_RXDONE_SHIFT)
#define I2C_RXDONE_RXDONE(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_RXDONE_RXDONE_SHIFT)) & I2C_RXDONE_RXDONE_MASK)

/*!
 * @brief I2C_ACTIV Register Bit Definition
 */

#define I2C_ACTIV_ACTIV_SHIFT                   (0)
#define I2C_ACTIV_ACTIV_MASK                    (0x01U << I2C_ACTIV_ACTIV_SHIFT)
#define I2C_ACTIV_ACTIV(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_ACTIV_ACTIV_SHIFT)) & I2C_ACTIV_ACTIV_MASK)

/*!
 * @brief I2C_STOP Register Bit Definition
 */

#define I2C_STOP_STOP_SHIFT                     (0)
#define I2C_STOP_STOP_MASK                      (0x01U << I2C_STOP_STOP_SHIFT)
#define I2C_STOP_STOP(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_STOP_STOP_SHIFT)) & I2C_STOP_STOP_MASK)

/*!
 * @brief I2C_START Register Bit Definition
 */

#define I2C_START_START_SHIFT                   (0)
#define I2C_START_START_MASK                    (0x01U << I2C_START_START_SHIFT)
#define I2C_START_START(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_START_START_SHIFT)) & I2C_START_START_MASK)

/*!
 * @brief I2C_GC Register Bit Definition
 */

#define I2C_GC_GC_SHIFT                         (0)
#define I2C_GC_GC_MASK                          (0x01U << I2C_GC_GC_SHIFT)
#define I2C_GC_GC(x)                            (((uint32_t)(((uint32_t)(x)) << I2C_GC_GC_SHIFT)) & I2C_GC_GC_MASK)

/*!
 * @brief I2C_ENR Register Bit Definition
 */

#define I2C_ENR_ABORT_SHIFT                     (1)
#define I2C_ENR_ABORT_MASK                      (0x01U << I2C_ENR_ABORT_SHIFT)
#define I2C_ENR_ABORT(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_ENR_ABORT_SHIFT)) & I2C_ENR_ABORT_MASK)

#define I2C_ENR_ENABLE_SHIFT                    (0)
#define I2C_ENR_ENABLE_MASK                     (0x01U << I2C_ENR_ENABLE_SHIFT)
#define I2C_ENR_ENABLE(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_ENR_ENABLE_SHIFT)) & I2C_ENR_ENABLE_MASK)

/*!
 * @brief I2C_SR Register Bit Definition
 */

#define I2C_SR_SLVACTIV_SHIFT                   (6)
#define I2C_SR_SLVACTIV_MASK                    (0x01U << I2C_SR_SLVACTIV_SHIFT)
#define I2C_SR_SLVACTIV(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_SR_SLVACTIV_SHIFT)) & I2C_SR_SLVACTIV_MASK)

#define I2C_SR_MSTACTIV_SHIFT                   (5)
#define I2C_SR_MSTACTIV_MASK                    (0x01U << I2C_SR_MSTACTIV_SHIFT)
#define I2C_SR_MSTACTIV(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_SR_MSTACTIV_SHIFT)) & I2C_SR_MSTACTIV_MASK)

#define I2C_SR_RFF_SHIFT                        (4)
#define I2C_SR_RFF_MASK                         (0x01U << I2C_SR_RFF_SHIFT)
#define I2C_SR_RFF(x)                           (((uint32_t)(((uint32_t)(x)) << I2C_SR_RFF_SHIFT)) & I2C_SR_RFF_MASK)

#define I2C_SR_RFNE_SHIFT                       (3)
#define I2C_SR_RFNE_MASK                        (0x01U << I2C_SR_RFNE_SHIFT)
#define I2C_SR_RFNE(x)                          (((uint32_t)(((uint32_t)(x)) << I2C_SR_RFNE_SHIFT)) & I2C_SR_RFNE_MASK)

#define I2C_SR_TFE_SHIFT                        (2)
#define I2C_SR_TFE_MASK                         (0x01U << I2C_SR_TFE_SHIFT)
#define I2C_SR_TFE(x)                           (((uint32_t)(((uint32_t)(x)) << I2C_SR_TFE_SHIFT)) & I2C_SR_TFE_MASK)

#define I2C_SR_TFNF_SHIFT                       (1)
#define I2C_SR_TFNF_MASK                        (0x01U << I2C_SR_TFNF_SHIFT)
#define I2C_SR_TFNF(x)                          (((uint32_t)(((uint32_t)(x)) << I2C_SR_TFNF_SHIFT)) & I2C_SR_TFNF_MASK)

#define I2C_SR_ACTIV_SHIFT                      (0)
#define I2C_SR_ACTIV_MASK                       (0x01U << I2C_SR_ACTIV_SHIFT)
#define I2C_SR_ACTIV(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_SR_ACTIV_SHIFT)) & I2C_SR_ACTIV_MASK)

/*!
 * @brief I2C_TXFLR Register Bit Definition
 */

#define I2C_TXFLR_CNT_SHIFT                     (0)
#define I2C_TXFLR_CNT_MASK                      (0x3U << I2C_TXFLR_CNT_SHIFT)
#define I2C_TXFLR_CNT(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_TXFLR_CNT_SHIFT)) & I2C_TXFLR_CNT_MASK)

/*!
 * @brief I2C_RXFLR Register Bit Definition
 */

#define I2C_RXFLR_CNT_SHIFT                     (0)
#define I2C_RXFLR_CNT_MASK                      (0x3U << I2C_RXFLR_CNT_SHIFT)
#define I2C_RXFLR_CNT(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_RXFLR_CNT_SHIFT)) & I2C_RXFLR_CNT_MASK)

/*!
 * @brief I2C_HOLD Register Bit Definition
 */

#define I2C_HOLD_RXHOLD_SHIFT                   (16)
#define I2C_HOLD_RXHOLD_MASK                    (0xFFU << I2C_HOLD_RXHOLD_SHIFT)
#define I2C_HOLD_RXHOLD(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_HOLD_RXHOLD_SHIFT)) & I2C_HOLD_RXHOLD_MASK)

#define I2C_HOLD_TXHOLD_SHIFT                   (0)
#define I2C_HOLD_TXHOLD_MASK                    (0xFFFFU << I2C_HOLD_TXHOLD_SHIFT)
#define I2C_HOLD_TXHOLD(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_HOLD_TXHOLD_SHIFT)) & I2C_HOLD_TXHOLD_MASK)

/*!
 * @brief I2C_DMA Register Bit Definition
 */

#define I2C_DMA_TXEN_SHIFT                      (1)
#define I2C_DMA_TXEN_MASK                       (0x01U << I2C_DMA_TXEN_SHIFT)
#define I2C_DMA_TXEN(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_DMA_TXEN_SHIFT)) & I2C_DMA_TXEN_MASK)

#define I2C_DMA_RXEN_SHIFT                      (0)
#define I2C_DMA_RXEN_MASK                       (0x01U << I2C_DMA_RXEN_SHIFT)
#define I2C_DMA_RXEN(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_DMA_RXEN_SHIFT)) & I2C_DMA_RXEN_MASK)

/*!
 * @brief I2C_SETUP Register Bit Definition
 */

#define I2C_SETUP_CNT_SHIFT                     (0)
#define I2C_SETUP_CNT_MASK                      (0xFFU << I2C_SETUP_CNT_SHIFT)
#define I2C_SETUP_CNT(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_SETUP_CNT_SHIFT)) & I2C_SETUP_CNT_MASK)

/*!
 * @brief I2C_GCR Register Bit Definition
 */

#define I2C_GCR_GC_SHIFT                        (0)
#define I2C_GCR_GC_MASK                         (0x01U << I2C_GCR_GC_SHIFT)
#define I2C_GCR_GC(x)                           (((uint32_t)(((uint32_t)(x)) << I2C_GCR_GC_SHIFT)) & I2C_GCR_GC_MASK)

/*!
 * @brief I2C_SLVMASK Register Bit Definition
 */

#define I2C_SLVMASK_MASK_SHIFT                  (0)
#define I2C_SLVMASK_MASK_MASK                   (0x3FFU << I2C_SLVMASK_MASK_SHIFT)
#define I2C_SLVMASK_MASK(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_SLVMASK_MASK_SHIFT)) & I2C_SLVMASK_MASK_MASK)

/*!
 * @brief I2C_SLVRCVADDR Register Bit Definition
 */

#define I2C_SLVRCVADDR_ADDR_SHIFT               (0)
#define I2C_SLVRCVADDR_ADDR_MASK                (0x3FFU << I2C_SLVRCVADDR_ADDR_SHIFT)
#define I2C_SLVRCVADDR_ADDR(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_SLVRCVADDR_ADDR_SHIFT)) & I2C_SLVRCVADDR_ADDR_MASK)

/*!
 * @}
 */ /* end of group I2C_Register_Masks */
/******************************************************************************
 * I2C Instance
******************************************************************************/
#define I2C1                                ((I2C_Type*)I2C1_BASE)
#define I2C2                                ((I2C_Type*)I2C2_BASE)

/*!
 * @}
 */ /* end of group I2C_Peripheral_Access_Layer */



/*!
 * @addtogroup CAN_Peripheral_Access_Layer CAN Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * CAN Basic Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CR;                                                             ///< CAN control register                         offset: 0x00
    __IO uint32_t CMR;                                                            ///< CAN command register                         offset: 0x04
    __IO uint32_t SR;                                                             ///< CAN status register                          offset: 0x08
    __IO uint32_t IR;                                                             ///< CAN Interrupt Register                     offset: 0x0C
    __IO uint32_t GROUP0ACR;                                                     ///< CAN Acceptance Code Register Group 0         offset: 0x10
    __IO uint32_t GROUP0AMR;                                                     ///< CAN acceptance mask register group 0         offset: 0x14
    __IO uint32_t BTR0;                                                           ///< CAN bus timing 0                             offset: 0x18
    __IO uint32_t BTR1;                                                           ///< CAN bus timing 1                             offset: 0x1C
    __IO uint32_t Reserved19[2];                                                   ///< Reserved
    __IO uint32_t TXID0;                                                          ///< CAN send identification code register 0      offset: 0x28
    __IO uint32_t TXID1;                                                          ///< CAN send identification code register 1      offset: 0x2C
    __IO uint32_t Reserved20[20];                                                  ///< Reserved
    __IO uint32_t CDR;                                                            ///< CAN clock divider register                   offset: 0x7C
    __IO uint32_t AFM0;                                                           ///< CAN filter mode register 0                   offset: 0x80
    __IO uint32_t AFM1;                                                           ///< CAN filter mode register 1                   offset: 0x84
    __IO uint32_t AFM2;                                                           ///< CAN filter mode register 2                   offset: 0x88
    __IO uint32_t FGA0;                                                           ///< CAN filter group enable register 0           offset: 0x8c
    __IO uint32_t FGA1;                                                           ///< CAN filter group enable register 1           offset: 0x90
    __IO uint32_t FGA2;                                                           ///< CAN filter group enable register 2           offset: 0x94
    __IO uint32_t GROUPACR;                                                     ///< CAN Acceptance Code Register Group x(X = 1~19)offset: 0x98
    __IO uint32_t Reserved21[3];                                                   ///< Reserved
    __IO uint32_t GROUPAMR;                                                     ///< CAN Acceptance Mask Register Group x(X = 1~19)offset: 0xA8
} CAN_Basic_Type;
/*******************************************************************************
 * CAN Peli Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t MOD;                                                            ///< CAN mode register                            offset: 0x00
    __IO uint32_t CMR;                                                            ///< CAN command register                         offset: 0x04
    __IO uint32_t SR;                                                             ///< CAN status register                          offset: 0x08
    __IO uint32_t Reserved19a[1];                                                 ///< Reserved
    __IO uint32_t IER;                                                            ///< CAN interrupt enable register                offset: 0x10
    __IO uint32_t Reserved20a[1];                                                 ///< Reserved
    __IO uint32_t BTR0;                                                           ///< CAN bus timing 0                             offset: 0x18
    __IO uint32_t BTR1;                                                           ///< CAN bus timing 1                             offset: 0x1C
    __IO uint32_t Reserved21a[3];                                                 ///< Reserved
    __IO uint32_t ALC;                                                            ///< CAN Arbitration Loss Capture Register        offset: 0x2C
    __IO uint32_t ECC;                                                            ///< CAN error code capture                       offset: 0x30
    __IO uint32_t EWLR;                                                           ///< CAN error alarm limit register               offset: 0x34
    __IO uint32_t RXERR;                                                          ///< CAN RX error count register                  offset: 0x38
    __IO uint32_t TXERR;                                                          ///< CAN TX error count register                  offset: 0x3C
    __IO uint32_t SFF;                                                            ///< Send frame information register              offset: 0x40
    __IO uint32_t TXID0;                                                          ///< CAN send identification code register 0      offset: 0x44
    __IO uint32_t TXID1;                                                          ///< CAN send identification code register 1      offset: 0x48
    __IO uint32_t TXDATA0;                                                        ///< CAN send data register 0                     offset: 0x4C
    __IO uint32_t TXDATA1;                                                        ///< CAN send data register 1                     offset: 0x50
    __IO uint32_t Reserved20[10];                                                 ///< Reserved
    __IO uint32_t CDR;                                                            ///< CAN clock divider register                   offset: 0x7C
    __IO uint32_t AFM0;                                                           ///< CAN filter mode register 0                   offset: 0x80
    __IO uint32_t AFM1;                                                           ///< CAN filter mode register 1                   offset: 0x84
    __IO uint32_t AFM2;                                                           ///< CAN filter mode register 2                   offset: 0x88
    __IO uint32_t FGA0;                                                           ///< CAN filter group enable register 0           offset: 0x8c
    __IO uint32_t FGA1;                                                           ///< CAN filter group enable register 1           offset: 0x90
    __IO uint32_t FGA2;                                                           ///< CAN filter group enable register 2           offset: 0x94
    __IO uint32_t GROUPACR;                                                       ///< CAN Acceptance Code Register Group x(X = 1~19)offset: 0x98
    __IO uint32_t Reserved21[3];                                                  ///< Reserved
    __IO uint32_t GROUPAMR;                                                       ///< CAN Acceptance Mask Register Group x(X = 1~19)offset: 0xA8
} CAN_Peli_Type;

/*******************************************************************************
 * CAN Type
 ******************************************************************************/

/*!
 * @addtogroup CAN_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief CAN_MOD Register Bit Definition
 */

#define CAN_MOD_AFM_SHIFT                       (3)
#define CAN_MOD_AFM_MASK                        (0x01U << CAN_MOD_AFM_SHIFT)
#define CAN_MOD_AFM(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_MOD_AFM_SHIFT)) & CAN_MOD_AFM_MASK)

#define CAN_MOD_STM_SHIFT                       (2)
#define CAN_MOD_STM_MASK                        (0x01U << CAN_MOD_STM_SHIFT)
#define CAN_MOD_STM(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_MOD_STM_SHIFT)) & CAN_MOD_STM_MASK)

#define CAN_MOD_LOM_SHIFT                       (1)
#define CAN_MOD_LOM_MASK                        (0x01U << CAN_MOD_LOM_SHIFT)
#define CAN_MOD_LOM(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_MOD_LOM_SHIFT)) & CAN_MOD_LOM_MASK)

#define CAN_MOD_RM_SHIFT                        (0)
#define CAN_MOD_RM_MASK                         (0x01U << CAN_MOD_RM_SHIFT)
#define CAN_MOD_RM(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_MOD_RM_SHIFT)) & CAN_MOD_RM_MASK)

/*!
 * @brief CAN_CR Register Bit Definition
 */

#define CAN_CR_OIE_SHIFT                        (4)
#define CAN_CR_OIE_MASK                         (0x01U << CAN_CR_OIE_SHIFT)
#define CAN_CR_OIE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_CR_OIE_SHIFT)) & CAN_CR_OIE_MASK)

#define CAN_CR_EIE_SHIFT                        (3)
#define CAN_CR_EIE_MASK                         (0x01U << CAN_CR_EIE_SHIFT)
#define CAN_CR_EIE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_CR_EIE_SHIFT)) & CAN_CR_EIE_MASK)

#define CAN_CR_TIE_SHIFT                        (2)
#define CAN_CR_TIE_MASK                         (0x01U << CAN_CR_TIE_SHIFT)
#define CAN_CR_TIE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_CR_TIE_SHIFT)) & CAN_CR_TIE_MASK)

#define CAN_CR_RIE_SHIFT                        (1)
#define CAN_CR_RIE_MASK                         (0x01U << CAN_CR_RIE_SHIFT)
#define CAN_CR_RIE(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_CR_RIE_SHIFT)) & CAN_CR_RIE_MASK)

#define CAN_CR_RR_SHIFT                         (0)
#define CAN_CR_RR_MASK                          (0x01U << CAN_CR_RR_SHIFT)
#define CAN_CR_RR(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_CR_RR_SHIFT)) & CAN_CR_RR_MASK)

/*!
 * @brief CAN_CMR Register Bit Definition
 */

#define CAN_CMR_ERB_SHIFT                       (5)
#define CAN_CMR_ERB_MASK                        (0x01U << CAN_CMR_ERB_SHIFT)
#define CAN_CMR_ERB(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CMR_ERB_SHIFT)) & CAN_CMR_ERB_MASK)

#define CAN_CMR_SRR_SHIFT                       (4)
#define CAN_CMR_SRR_MASK                        (0x01U << CAN_CMR_SRR_SHIFT)
#define CAN_CMR_SRR(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CMR_SRR_SHIFT)) & CAN_CMR_SRR_MASK)

#define CAN_CMR_CDO_SHIFT                       (3)
#define CAN_CMR_CDO_MASK                        (0x01U << CAN_CMR_CDO_SHIFT)
#define CAN_CMR_CDO(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CMR_CDO_SHIFT)) & CAN_CMR_CDO_MASK)

#define CAN_CMR_RRB_SHIFT                       (2)
#define CAN_CMR_RRB_MASK                        (0x01U << CAN_CMR_RRB_SHIFT)
#define CAN_CMR_RRB(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_CMR_RRB_SHIFT)) & CAN_CMR_RRB_MASK)

#define CAN_CMR_AT_SHIFT                        (1)
#define CAN_CMR_AT_MASK                         (0x01U << CAN_CMR_AT_SHIFT)
#define CAN_CMR_AT(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_CMR_AT_SHIFT)) & CAN_CMR_AT_MASK)

#define CAN_CMR_TR_SHIFT                        (0)
#define CAN_CMR_TR_MASK                         (0x01U << CAN_CMR_TR_SHIFT)
#define CAN_CMR_TR(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_CMR_TR_SHIFT)) & CAN_CMR_TR_MASK)

/*!
 * @brief CAN_SR Register Bit Definition
 */

#define CAN_SR_BS_SHIFT                         (7)
#define CAN_SR_BS_MASK                          (0x01U << CAN_SR_BS_SHIFT)
#define CAN_SR_BS(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_SR_BS_SHIFT)) & CAN_SR_BS_MASK)

#define CAN_SR_ES_SHIFT                         (6)
#define CAN_SR_ES_MASK                          (0x01U << CAN_SR_ES_SHIFT)
#define CAN_SR_ES(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_SR_ES_SHIFT)) & CAN_SR_ES_MASK)

#define CAN_SR_TS_SHIFT                         (5)
#define CAN_SR_TS_MASK                          (0x01U << CAN_SR_TS_SHIFT)
#define CAN_SR_TS(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_SR_TS_SHIFT)) & CAN_SR_TS_MASK)

#define CAN_SR_RS_SHIFT                         (4)
#define CAN_SR_RS_MASK                          (0x01U << CAN_SR_RS_SHIFT)
#define CAN_SR_RS(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_SR_RS_SHIFT)) & CAN_SR_RS_MASK)

#define CAN_SR_TCS_SHIFT                        (3)
#define CAN_SR_TCS_MASK                         (0x01U << CAN_SR_TCS_SHIFT)
#define CAN_SR_TCS(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_SR_TCS_SHIFT)) & CAN_SR_TCS_MASK)

#define CAN_SR_TBS_SHIFT                        (2)
#define CAN_SR_TBS_MASK                         (0x01U << CAN_SR_TBS_SHIFT)
#define CAN_SR_TBS(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_SR_TBS_SHIFT)) & CAN_SR_TBS_MASK)

#define CAN_SR_DOS_SHIFT                        (1)
#define CAN_SR_DOS_MASK                         (0x01U << CAN_SR_DOS_SHIFT)
#define CAN_SR_DOS(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_SR_DOS_SHIFT)) & CAN_SR_DOS_MASK)

#define CAN_SR_RBS_SHIFT                        (0)
#define CAN_SR_RBS_MASK                         (0x01U << CAN_SR_RBS_SHIFT)
#define CAN_SR_RBS(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_SR_RBS_SHIFT)) & CAN_SR_RBS_MASK)

/*!
 * @brief
CAN_IR Register Bit Definition
 */

#define CAN_IR_BEI_SHIFT                        (7)
#define CAN_IR_BEI_MASK                         (0x01U << CAN_IR_BEI_SHIFT)
#define CAN_IR_BEI(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_BEI_SHIFT)) & CAN_IR_BEI_MASK)

#define CAN_IR_ALI_SHIFT                        (6)
#define CAN_IR_ALI_MASK                         (0x01U << CAN_IR_ALI_SHIFT)
#define CAN_IR_ALI(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_ALI_SHIFT)) & CAN_IR_ALI_MASK)

#define CAN_IR_EPI_SHIFT                        (5)
#define CAN_IR_EPI_MASK                         (0x01U << CAN_IR_EPI_SHIFT)
#define CAN_IR_EPI(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_EPI_SHIFT)) & CAN_IR_EPI_MASK)

#define CAN_IR_DOI_SHIFT                        (3)
#define CAN_IR_DOI_MASK                         (0x01U << CAN_IR_DOI_SHIFT)
#define CAN_IR_DOI(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_IR_DOI_SHIFT)) & CAN_IR_DOI_MASK)

#define CAN_IR_EI_SHIFT                         (2)
#define CAN_IR_EI_MASK                          (0x01U << CAN_IR_EI_SHIFT)
#define CAN_IR_EI(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_EI_SHIFT)) & CAN_IR_EI_MASK)

#define CAN_IR_TI_SHIFT                         (1)
#define CAN_IR_TI_MASK                          (0x01U << CAN_IR_TI_SHIFT)
#define CAN_IR_TI(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_TI_SHIFT)) & CAN_IR_TI_MASK)

#define CAN_IR_RI_SHIFT                         (0)
#define CAN_IR_RI_MASK                          (0x01U << CAN_IR_RI_SHIFT)
#define CAN_IR_RI(x)                            (((uint32_t)(((uint32_t)(x)) << CAN_IR_RI_SHIFT)) & CAN_IR_RI_MASK)

/*!
 * @brief CAN_IER Register Bit Definition
 */

#define CAN_IER_BEIE_SHIFT                      (7)
#define CAN_IER_BEIE_MASK                       (0x01U << CAN_IER_BEIE_SHIFT)
#define CAN_IER_BEIE(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_IER_BEIE_SHIFT)) & CAN_IER_BEIE_MASK)

#define CAN_IER_ALIE_SHIFT                      (6)
#define CAN_IER_ALIE_MASK                       (0x01U << CAN_IER_ALIE_SHIFT)
#define CAN_IER_ALIE(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_IER_ALIE_SHIFT)) & CAN_IER_ALIE_MASK)

#define CAN_IER_EPIE_SHIFT                      (5)
#define CAN_IER_EPIE_MASK                       (0x01U << CAN_IER_EPIE_SHIFT)
#define CAN_IER_EPIE(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_IER_EPIE_SHIFT)) & CAN_IER_EPIE_MASK)

#define CAN_IER_DOIE_SHIFT                      (3)
#define CAN_IER_DOIE_MASK                       (0x01U << CAN_IER_DOIE_SHIFT)
#define CAN_IER_DOIE(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_IER_DOIE_SHIFT)) & CAN_IER_DOIE_MASK)

#define CAN_IER_EIE_SHIFT                       (2)
#define CAN_IER_EIE_MASK                        (0x01U << CAN_IER_EIE_SHIFT)
#define CAN_IER_EIE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IER_EIE_SHIFT)) & CAN_IER_EIE_MASK)

#define CAN_IER_TIE_SHIFT                       (1)
#define CAN_IER_TIE_MASK                        (0x01U << CAN_IER_TIE_SHIFT)
#define CAN_IER_TIE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IER_TIE_SHIFT)) & CAN_IER_TIE_MASK)

#define CAN_IER_RIE_SHIFT                       (0)
#define CAN_IER_RIE_MASK                        (0x01U << CAN_IER_RIE_SHIFT)
#define CAN_IER_RIE(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_IER_RIE_SHIFT)) & CAN_IER_RIE_MASK)

/*!
 * @brief CAN_GROUP0ACR Register Bit Definition
 */

#define CAN_GROUP0ACR_AC_SHIFT                 (0)
#define CAN_GROUP0ACR_AC_MASK                  (0xFFU << CAN_GROUP0ACR_AC_SHIFT)
#define CAN_GROUP0ACR_AC(x)                    (((uint32_t)(((uint32_t)(x)) << CAN_GROUP0ACR_AC_SHIFT)) & CAN_GROUP0ACR_AC_MASK)

/*!
 * @brief CAN_GROUP0AMR Register Bit Definition
 */

#define CAN_GROUP0AMR_AM_SHIFT                 (0)
#define CAN_GROUP0AMR_AM_MASK                  (0xFFU << CAN_GROUP0AMR_AM_SHIFT)
#define CAN_GROUP0AMR_AM(x)                    (((uint32_t)(((uint32_t)(x)) << CAN_GROUP0AMR_AM_SHIFT)) & CAN_GROUP0AMR_AM_MASK)

/*!
 * @brief CAN_BTR0 Register Bit Definition
 */

#define CAN_BTR0_SJW_SHIFT                      (6)
#define CAN_BTR0_SJW_MASK                       (0x3U << CAN_BTR0_SJW_SHIFT)
#define CAN_BTR0_SJW(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_BTR0_SJW_SHIFT)) & CAN_BTR0_SJW_MASK)

#define CAN_BTR0_BRP_SHIFT                      (0)
#define CAN_BTR0_BRP_MASK                       (0x3FU << CAN_BTR0_BRP_SHIFT)
#define CAN_BTR0_BRP(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_BTR0_BRP_SHIFT)) & CAN_BTR0_BRP_MASK)

/*!
 * @brief CAN_BTR1 Register Bit Definition
 */

#define CAN_BTR1_SAM_SHIFT                      (7)
#define CAN_BTR1_SAM_MASK                       (0x01U << CAN_BTR1_SAM_SHIFT)
#define CAN_BTR1_SAM(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_BTR1_SAM_SHIFT)) & CAN_BTR1_SAM_MASK)

#define CAN_BTR1_TSEG2TSEG1_SHIFT               (0)
#define CAN_BTR1_TSEG2TSEG1_MASK                (0x7FU << CAN_BTR1_TSEG2TSEG1_SHIFT)
#define CAN_BTR1_TSEG2TSEG1(x)                  (((uint32_t)(((uint32_t)(x)) << CAN_BTR1_TSEG2TSEG1_SHIFT)) & CAN_BTR1_TSEG2TSEG1_MASK)

/*!
 * @brief CAN_TXID0 Register Bit Definition
 */

#define CAN_TXID0_IDX_SHIFT                     (0)
#define CAN_TXID0_IDX_MASK                      (0xFFU << CAN_TXID0_IDX_SHIFT)
#define CAN_TXID0_IDX(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXID0_IDX_SHIFT)) & CAN_TXID0_IDX_MASK)

/*!
 * @brief CAN_TXID1 Register Bit Definition
 */

#define CAN_TXID1_IDX_SHIFT                     (5)
#define CAN_TXID1_IDX_MASK                      (0x7U << CAN_TXID1_IDX_SHIFT)
#define CAN_TXID1_IDX(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXID1_IDX_SHIFT)) & CAN_TXID1_IDX_MASK)

#define CAN_TXID1_RTR_SHIFT                     (4)
#define CAN_TXID1_RTR_MASK                      (0x01U << CAN_TXID1_RTR_SHIFT)
#define CAN_TXID1_RTR(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXID1_RTR_SHIFT)) & CAN_TXID1_RTR_MASK)

#define CAN_TXID1_DLCX_SHIFT                    (0)
#define CAN_TXID1_DLCX_MASK                     (0xFU << CAN_TXID1_DLCX_SHIFT)
#define CAN_TXID1_DLCX(x)                       (((uint32_t)(((uint32_t)(x)) << CAN_TXID1_DLCX_SHIFT)) & CAN_TXID1_DLCX_MASK)

/*!
 * @brief CAN_ALC Register Bit Definition
 */

#define CAN_ALC_BITNO_SHIFT                     (0)
#define CAN_ALC_BITNO_MASK                      (0x1FU << CAN_ALC_BITNO_SHIFT)
#define CAN_ALC_BITNO(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_ALC_BITNO_SHIFT)) & CAN_ALC_BITNO_MASK)

/*!
 * @brief CAN_ECC Register Bit Definition
 */

#define CAN_ECC_ERRC_SHIFT                      (6)
#define CAN_ECC_ERRC_MASK                       (0x3U << CAN_ECC_ERRC_SHIFT)
#define CAN_ECC_ERRC(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_ECC_ERRC_SHIFT)) & CAN_ECC_ERRC_MASK)

#define CAN_ECC_DIR_SHIFT                       (5)
#define CAN_ECC_DIR_MASK                        (0x01U << CAN_ECC_DIR_SHIFT)
#define CAN_ECC_DIR(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ECC_DIR_SHIFT)) & CAN_ECC_DIR_MASK)

#define CAN_ECC_SEG_SHIFT                       (0)
#define CAN_ECC_SEG_MASK                        (0x1FU << CAN_ECC_SEG_SHIFT)
#define CAN_ECC_SEG(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_ECC_SEG_SHIFT)) & CAN_ECC_SEG_MASK)

/*!
 * @brief CAN_EWLR Register Bit Definition
 */

#define CAN_EWLR_EWL_SHIFT                      (0)
#define CAN_EWLR_EWL_MASK                       (0xFFU << CAN_EWLR_EWL_SHIFT)
#define CAN_EWLR_EWL(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_EWLR_EWL_SHIFT)) & CAN_EWLR_EWL_MASK)

/*!
 * @brief CAN_RXERR Register Bit Definition
 */

#define CAN_RXERR_RXERR_SHIFT                   (0)
#define CAN_RXERR_RXERR_MASK                    (0xFFU << CAN_RXERR_RXERR_SHIFT)
#define CAN_RXERR_RXERR(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_RXERR_RXERR_SHIFT)) & CAN_RXERR_RXERR_MASK)

/*!
 * @brief CAN_TXERR Register Bit Definition
 */

#define CAN_TXERR_TXERR_SHIFT                   (0)
#define CAN_TXERR_TXERR_MASK                    (0xFFU << CAN_TXERR_TXERR_SHIFT)
#define CAN_TXERR_TXERR(x)                      (((uint32_t)(((uint32_t)(x)) << CAN_TXERR_TXERR_SHIFT)) & CAN_TXERR_TXERR_MASK)

#define CAN_TXERR_RTR_SHIFT                     (6)
#define CAN_TXERR_RTR_MASK                      (0x01U << CAN_TXERR_RTR_SHIFT)
#define CAN_TXERR_RTR(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXERR_RTR_SHIFT)) & CAN_TXERR_RTR_MASK)

#define CAN_TXERR_DLC_SHIFT                     (0)
#define CAN_TXERR_DLC_MASK                      (0xFU << CAN_TXERR_DLC_SHIFT)
#define CAN_TXERR_DLC(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXERR_DLC_SHIFT)) & CAN_TXERR_DLC_MASK)

/*!
 * @brief CAN_SFF Register Bit Definition
 */

#define CAN_SFF_FF_SHIFT                        (7)
#define CAN_SFF_FF_MASK                         (0x01U << CAN_SFF_FF_SHIFT)
#define CAN_SFF_FF(x)                           (((uint32_t)(((uint32_t)(x)) << CAN_SFF_FF_SHIFT)) & CAN_SFF_FF_MASK)

#define CAN_SFF_RTR_SHIFT                       (6)
#define CAN_SFF_RTR_MASK                        (0x01U << CAN_SFF_RTR_SHIFT)
#define CAN_SFF_RTR(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_SFF_RTR_SHIFT)) & CAN_SFF_RTR_MASK)

#define CAN_SFF_DLC_SHIFT                       (0)
#define CAN_SFF_DLC_MASK                        (0xFU << CAN_SFF_DLC_SHIFT)
#define CAN_SFF_DLC(x)                          (((uint32_t)(((uint32_t)(x)) << CAN_SFF_DLC_SHIFT)) & CAN_SFF_DLC_MASK)

/*!
 * @brief CAN_TXID0 Register Bit Definition
 */

#define CAN_TXID0_IDX_SHIFT                     (0)
#define CAN_TXID0_IDX_MASK                      (0xFFU << CAN_TXID0_IDX_SHIFT)
#define CAN_TXID0_IDX(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXID0_IDX_SHIFT)) & CAN_TXID0_IDX_MASK)

/*!
 * @brief CAN_TXID1 Register Bit Definition
 */

#define CAN_TXID1_ID_SHIFT                     (0)
#define CAN_TXID1_ID_MASK                      (0xFFU << CAN_TXID1_ID_SHIFT)
#define CAN_TXID1_ID(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_TXID1_ID_SHIFT)) & CAN_TXID1_ID_MASK)

/*!
 * @brief CAN_TXDATA0 Register Bit Definition
 */

#define CAN_TXDATA0_DATA0_SHIFT                 (0)
#define CAN_TXDATA0_DATA0_MASK                  (0xFFU << CAN_TXDATA0_DATA0_SHIFT)
#define CAN_TXDATA0_DATA0(x)                    (((uint32_t)(((uint32_t)(x)) << CAN_TXDATA0_DATA0_SHIFT)) & CAN_TXDATA0_DATA0_MASK)

/*!
 * @brief CAN_TXDATA1 Register Bit Definition
 */

#define CAN_TXDATA1_DATA1_SHIFT                 (0)
#define CAN_TXDATA1_DATA1_MASK                  (0xFFU << CAN_TXDATA1_DATA1_SHIFT)
#define CAN_TXDATA1_DATA1(x)                    (((uint32_t)(((uint32_t)(x)) << CAN_TXDATA1_DATA1_SHIFT)) & CAN_TXDATA1_DATA1_MASK)

/*!
 * @brief CAN_CDR Register Bit Definition
 */

#define CAN_CDR_MODE_SHIFT                      (7)
#define CAN_CDR_MODE_MASK                       (0x01U << CAN_CDR_MODE_SHIFT)
#define CAN_CDR_MODE(x)                         (((uint32_t)(((uint32_t)(x)) << CAN_CDR_MODE_SHIFT)) & CAN_CDR_MODE_MASK)

/*!
 * @brief CAN_AFM0 Register Bit Definition
 */

#define CAN_AFM0_AFMX_SHIFT                     (1)
#define CAN_AFM0_AFMX_MASK                      (0x7FU << CAN_AFM0_AFMX_SHIFT)
#define CAN_AFM0_AFMX(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_AFM0_AFMX_SHIFT)) & CAN_AFM0_AFMX_MASK)

/*!
 * @brief CAN_AFM1 Register Bit Definition
 */

#define CAN_AFM1_AFMX_SHIFT                     (0)
#define CAN_AFM1_AFMX_MASK                      (0xFFU << CAN_AFM1_AFMX_SHIFT)
#define CAN_AFM1_AFMX(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_AFM1_AFMX_SHIFT)) & CAN_AFM1_AFMX_MASK)

/*!
 * @brief CAN_AFM2 Register Bit Definition
 */

#define CAN_AFM2_AFMX_SHIFT                     (0)
#define CAN_AFM2_AFMX_MASK                      (0xFU << CAN_AFM2_AFMX_SHIFT)
#define CAN_AFM2_AFMX(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_AFM2_AFMX_SHIFT)) & CAN_AFM2_AFMX_MASK)

/*!
 * @brief CAN_FGA0 Register Bit Definition
 */

#define CAN_FGA0_FGAX_SHIFT                     (1)
#define CAN_FGA0_FGAX_MASK                      (0x7FU << CAN_FGA0_FGAX_SHIFT)
#define CAN_FGA0_FGAX(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_FGA0_FGAX_SHIFT)) & CAN_FGA0_FGAX_MASK)

/*!
 * @brief CAN_FGA1 Register Bit Definition
 */

#define CAN_FGA1_FGAX_SHIFT                     (0)
#define CAN_FGA1_FGAX_MASK                      (0xFFU << CAN_FGA1_FGAX_SHIFT)
#define CAN_FGA1_FGAX(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_FGA1_FGAX_SHIFT)) & CAN_FGA1_FGAX_MASK)

/*!
 * @brief CAN_FGA2 Register Bit Definition
 */

#define CAN_FGA2_FGAX_SHIFT                     (0)
#define CAN_FGA2_FGAX_MASK                      (0xFFU << CAN_FGA2_FGAX_SHIFT)
#define CAN_FGA2_FGAX(x)                        (((uint32_t)(((uint32_t)(x)) << CAN_FGA2_FGAX_SHIFT)) & CAN_FGA2_FGAX_MASK)

/*!
 * @brief CAN_GROUPACR
 Register Bit Definition
 */

#define CAN_GROUPACR_AC_SHIFT                  (0)
#define CAN_GROUPACR_AC_MASK                   (0xFFU << CAN_GROUPACR_AC_SHIFT)
#define CAN_GROUPACR_AC(x)                     (((uint32_t)(((uint32_t)(x)) << CAN_GROUPACR_AC_SHIFT)) & CAN_GROUPACR_AC_MASK)

/*!
 * @brief CAN_GROUPAMR
 Register Bit Definition
 */

#define CAN_GROUPAMR_AM_SHIFT                  (0)
#define CAN_GROUPAMR_AM_MASK                   (0xFFU << CAN_GROUPAMR_AM_SHIFT)
#define CAN_GROUPAMR_AM(x)                     (((uint32_t)(((uint32_t)(x)) << CAN_GROUPAMR_AM_SHIFT)) & CAN_GROUPAMR_AM_MASK)

/*!
 * @}
 */ /* end of group CAN_Register_Masks */
/******************************************************************************
 * CAN Instance
******************************************************************************/
#define CAN_Basic                               ((CAN_Basic_Type*)CAN_BASE)
#define CAN_Peli                                ((CAN_Peli_Type*)CAN_BASE)

/*!
 * @}
 */ /* end of group CAN_Peripheral_Access_Layer */



/*!
 * @addtogroup USB_Peripheral_Access_Layer USB Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * USB Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t Reserved22[4];                                                  ///< Reserved
    __IO uint32_t OTGISTAT;                                                       ///< OTG Interrupt Status Register                offset: 0x10
    __IO uint32_t OTGICTRL;                                                       ///< OTG Interrupt Control Register               offset: 0x14
    __IO uint32_t OTGSTAT;                                                        ///< OTG Status Register                          offset: 0x18
    __IO uint32_t OTGCTRL;                                                        ///< OTG Control register                         offset: 0x1C
    __IO uint32_t Reserved23[24];                                                 ///< Reserved
    __IO uint32_t INTSTAT;                                                        ///< Interrupt status register                    offset: 0x80
    __IO uint32_t INTENB;                                                         ///< Interrupt enable register                    offset: 0x84
    __IO uint32_t ERRSTAT;                                                        ///< Error interrupt status register              offset: 0x88
    __IO uint32_t ERRENB;                                                         ///< Error interrupt enable register              offset: 0x8C
    __IO uint32_t STAT;                                                           ///< Status register                              offset: 0x90
    __IO uint32_t CTL;                                                            ///< Control register                             offset: 0x94
    __IO uint32_t ADDR;                                                           ///< Address register                             offset: 0x98
    __IO uint32_t BDTPAGE01;                                                      ///< BDT page register 1                          offset: 0x9C
    __IO uint32_t FRMNUML;                                                        ///< Frame number register                        offset: 0xA0
    __IO uint32_t FRMNUMH;                                                        ///< Frame number register                        offset: 0xA4
    __IO uint32_t TOKEN;                                                          ///< Token register                               offset: 0xA8
    __IO uint32_t SOFTHLD;                                                        ///< SOF threshold register                       offset: 0xAC
    __IO uint32_t BDTPAGE02;                                                      ///< BDT page register 2                          offset: 0xB0
    __IO uint32_t BDTPAGE03;                                                      ///< BDT page register 3                          offset: 0xB4
    __IO uint32_t Reserved24[2];                                                  ///< Reserved
    __IO uint32_t EPCTL[16];                                                      ///< Endpoint control register                    offset: 0xC0
} USB_Type;

/*******************************************************************************
 * USB Type
 ******************************************************************************/

/*!
 * @addtogroup USB_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief USB_OTGISTAT Register Bit Definition
 */

#define USB_OTGISTAT_IDCHG_SHIFT               (7)
#define USB_OTGISTAT_IDCHG_MASK                (0x01U << USB_OTGISTAT_IDCHG_SHIFT)
#define USB_OTGISTAT_IDCHG(x)                  (((uint32_t)(((uint32_t)(x)) << USB_OTGISTAT_IDCHG_SHIFT)) & USB_OTGISTAT_IDCHG_MASK)

#define USB_OTGISTAT_1MSEC_SHIFT               (6)
#define USB_OTGISTAT_1MSEC_MASK                (0x01U << USB_OTGISTAT_1MSEC_SHIFT)
#define USB_OTGISTAT_1MSEC(x)                  (((uint32_t)(((uint32_t)(x)) << USB_OTGISTAT_1MSEC_SHIFT)) & USB_OTGISTAT_1MSEC_MASK)

#define USB_OTGISTAT_LINESTATECHG_SHIFT        (5)
#define USB_OTGISTAT_LINESTATECHG_MASK         (0x01U << USB_OTGISTAT_LINESTATECHG_SHIFT)
#define USB_OTGISTAT_LINESTATECHG(x)           (((uint32_t)(((uint32_t)(x)) << USB_OTGISTAT_LINESTATECHG_SHIFT)) & USB_OTGISTAT_LINESTATECHG_MASK)

#define USB_OTGISTAT_SESSVLDCHG_SHIFT          (2)
#define USB_OTGISTAT_SESSVLDCHG_MASK           (0x01U << USB_OTGISTAT_SESSVLDCHG_SHIFT)
#define USB_OTGISTAT_SESSVLDCHG(x)             (((uint32_t)(((uint32_t)(x)) << USB_OTGISTAT_SESSVLDCHG_SHIFT)) & USB_OTGISTAT_SESSVLDCHG_MASK)

#define USB_OTGISTAT_BSESSENDCHG_SHIFT         (2)
#define USB_OTGISTAT_BSESSENDCHG_MASK          (0x01U << USB_OTGISTAT_BSESSENDCHG_SHIFT)
#define USB_OTGISTAT_BSESSENDCHG(x)            (((uint32_t)(((uint32_t)(x)) << USB_OTGISTAT_BSESSENDCHG_SHIFT)) & USB_OTGISTAT_BSESSENDCHG_MASK)

#define USB_OTGISTAT_AVBUSVLDCHG_SHIFT         (0)
#define USB_OTGISTAT_AVBUSVLDCHG_MASK          (0x01U << USB_OTGISTAT_AVBUSVLDCHG_SHIFT)
#define USB_OTGISTAT_AVBUSVLDCHG(x)            (((uint32_t)(((uint32_t)(x)) << USB_OTGISTAT_AVBUSVLDCHG_SHIFT)) & USB_OTGISTAT_AVBUSVLDCHG_MASK)

/*!
 * @brief USB_OTGICTRL Register Bit Definition
 */

#define USB_OTGICTRL_IDEN_SHIFT                (7)
#define USB_OTGICTRL_IDEN_MASK                 (0x01U << USB_OTGICTRL_IDEN_SHIFT)
#define USB_OTGICTRL_IDEN(x)                   (((uint32_t)(((uint32_t)(x)) << USB_OTGICTRL_IDEN_SHIFT)) & USB_OTGICTRL_IDEN_MASK)

#define USB_OTGICTRL_1MSECEN_SHIFT             (6)
#define USB_OTGICTRL_1MSECEN_MASK              (0x01U << USB_OTGICTRL_1MSECEN_SHIFT)
#define USB_OTGICTRL_1MSECEN(x)                (((uint32_t)(((uint32_t)(x)) << USB_OTGICTRL_1MSECEN_SHIFT)) & USB_OTGICTRL_1MSECEN_MASK)

#define USB_OTGICTRL_LINESTATEEN_SHIFT         (5)
#define USB_OTGICTRL_LINESTATEEN_MASK          (0x01U << USB_OTGICTRL_LINESTATEEN_SHIFT)
#define USB_OTGICTRL_LINESTATEEN(x)            (((uint32_t)(((uint32_t)(x)) << USB_OTGICTRL_LINESTATEEN_SHIFT)) & USB_OTGICTRL_LINESTATEEN_MASK)

#define USB_OTGICTRL_SESSVLDEN_SHIFT           (3)
#define USB_OTGICTRL_SESSVLDEN_MASK            (0x01U << USB_OTGICTRL_SESSVLDEN_SHIFT)
#define USB_OTGICTRL_SESSVLDEN(x)              (((uint32_t)(((uint32_t)(x)) << USB_OTGICTRL_SESSVLDEN_SHIFT)) & USB_OTGICTRL_SESSVLDEN_MASK)

#define USB_OTGICTRL_BSESSENDEN_SHIFT          (2)
#define USB_OTGICTRL_BSESSENDEN_MASK           (0x01U << USB_OTGICTRL_BSESSENDEN_SHIFT)
#define USB_OTGICTRL_BSESSENDEN(x)             (((uint32_t)(((uint32_t)(x)) << USB_OTGICTRL_BSESSENDEN_SHIFT)) & USB_OTGICTRL_BSESSENDEN_MASK)

#define USB_OTGICTRL_AVBUSVLDEN_SHIFT          (0)
#define USB_OTGICTRL_AVBUSVLDEN_MASK           (0x01U << USB_OTGICTRL_AVBUSVLDEN_SHIFT)
#define USB_OTGICTRL_AVBUSVLDEN(x)             (((uint32_t)(((uint32_t)(x)) << USB_OTGICTRL_AVBUSVLDEN_SHIFT)) & USB_OTGICTRL_AVBUSVLDEN_MASK)

/*!
 * @brief USB_OTGSTAT Register Bit Definition
 */

#define USB_OTGSTAT_ID_SHIFT                   (7)
#define USB_OTGSTAT_ID_MASK                    (0x01U << USB_OTGSTAT_ID_SHIFT)
#define USB_OTGSTAT_ID(x)                      (((uint32_t)(((uint32_t)(x)) << USB_OTGSTAT_ID_SHIFT)) & USB_OTGSTAT_ID_MASK)

#define USB_OTGSTAT_1MSEC_SHIFT                (6)
#define USB_OTGSTAT_1MSEC_MASK                 (0x01U << USB_OTGSTAT_1MSEC_SHIFT)
#define USB_OTGSTAT_1MSEC(x)                   (((uint32_t)(((uint32_t)(x)) << USB_OTGSTAT_1MSEC_SHIFT)) & USB_OTGSTAT_1MSEC_MASK)

#define USB_OTGSTAT_LINESTATESTABLE_SHIFT      (5)
#define USB_OTGSTAT_LINESTATESTABLE_MASK       (0x01U << USB_OTGSTAT_LINESTATESTABLE_SHIFT)
#define USB_OTGSTAT_LINESTATESTABLE(x)         (((uint32_t)(((uint32_t)(x)) << USB_OTGSTAT_LINESTATESTABLE_SHIFT)) & USB_OTGSTAT_LINESTATESTABLE_MASK)

#define USB_OTGSTAT_SESSVLD_SHIFT              (3)
#define USB_OTGSTAT_SESSVLD_MASK               (0x01U << USB_OTGSTAT_SESSVLD_SHIFT)
#define USB_OTGSTAT_SESSVLD(x)                 (((uint32_t)(((uint32_t)(x)) << USB_OTGSTAT_SESSVLD_SHIFT)) & USB_OTGSTAT_SESSVLD_MASK)

#define USB_OTGSTAT_BSESSEND_SHIFT             (2)
#define USB_OTGSTAT_BSESSEND_MASK              (0x01U << USB_OTGSTAT_BSESSEND_SHIFT)
#define USB_OTGSTAT_BSESSEND(x)                (((uint32_t)(((uint32_t)(x)) << USB_OTGSTAT_BSESSEND_SHIFT)) & USB_OTGSTAT_BSESSEND_MASK)

#define USB_OTGSTAT_AVBUSVLD_SHIFT             (0)
#define USB_OTGSTAT_AVBUSVLD_MASK              (0x01U << USB_OTGSTAT_AVBUSVLD_SHIFT)
#define USB_OTGSTAT_AVBUSVLD(x)                (((uint32_t)(((uint32_t)(x)) << USB_OTGSTAT_AVBUSVLD_SHIFT)) & USB_OTGSTAT_AVBUSVLD_MASK)

/*!
 * @brief USB_OTGCTRL Register Bit Definition
 */

#define USB_OTGCTRL_DPHIGH_SHIFT               (7)
#define USB_OTGCTRL_DPHIGH_MASK                (0x01U << USB_OTGCTRL_DPHIGH_SHIFT)
#define USB_OTGCTRL_DPHIGH(x)                  (((uint32_t)(((uint32_t)(x)) << USB_OTGCTRL_DPHIGH_SHIFT)) & USB_OTGCTRL_DPHIGH_MASK)

#define USB_OTGCTRL_DMHIGH_SHIFT               (6)
#define USB_OTGCTRL_DMHIGH_MASK                (0x01U << USB_OTGCTRL_DMHIGH_SHIFT)
#define USB_OTGCTRL_DMHIGH(x)                  (((uint32_t)(((uint32_t)(x)) << USB_OTGCTRL_DMHIGH_SHIFT)) & USB_OTGCTRL_DMHIGH_MASK)

#define USB_OTGCTRL_DPLOW_SHIFT                (5)
#define USB_OTGCTRL_DPLOW_MASK                 (0x01U << USB_OTGCTRL_DPLOW_SHIFT)
#define USB_OTGCTRL_DPLOW(x)                   (((uint32_t)(((uint32_t)(x)) << USB_OTGCTRL_DPLOW_SHIFT)) & USB_OTGCTRL_DPLOW_MASK)

#define USB_OTGCTRL_DMLOW_SHIFT                (4)
#define USB_OTGCTRL_DMLOW_MASK                 (0x01U << USB_OTGCTRL_DMLOW_SHIFT)
#define USB_OTGCTRL_DMLOW(x)                   (((uint32_t)(((uint32_t)(x)) << USB_OTGCTRL_DMLOW_SHIFT)) & USB_OTGCTRL_DMLOW_MASK)

#define USB_OTGCTRL_VBUSON_SHIFT               (3)
#define USB_OTGCTRL_VBUSON_MASK                (0x01U << USB_OTGCTRL_VBUSON_SHIFT)
#define USB_OTGCTRL_VBUSON(x)                  (((uint32_t)(((uint32_t)(x)) << USB_OTGCTRL_VBUSON_SHIFT)) & USB_OTGCTRL_VBUSON_MASK)

#define USB_OTGCTRL_OTGEN_SHIFT                (2)
#define USB_OTGCTRL_OTGEN_MASK                 (0x01U << USB_OTGCTRL_OTGEN_SHIFT)
#define USB_OTGCTRL_OTGEN(x)                   (((uint32_t)(((uint32_t)(x)) << USB_OTGCTRL_OTGEN_SHIFT)) & USB_OTGCTRL_OTGEN_MASK)

#define USB_OTGCTRL_VBUSCHG_SHIFT              (1)
#define USB_OTGCTRL_VBUSCHG_MASK               (0x01U << USB_OTGCTRL_VBUSCHG_SHIFT)
#define USB_OTGCTRL_VBUSCHG(x)                 (((uint32_t)(((uint32_t)(x)) << USB_OTGCTRL_VBUSCHG_SHIFT)) & USB_OTGCTRL_VBUSCHG_MASK)

#define USB_OTGCTRL_VBUSDSCHG_SHIFT            (0)
#define USB_OTGCTRL_VBUSDSCHG_MASK             (0x01U << USB_OTGCTRL_VBUSDSCHG_SHIFT)
#define USB_OTGCTRL_VBUSDSCHG(x)               (((uint32_t)(((uint32_t)(x)) << USB_OTGCTRL_VBUSDSCHG_SHIFT)) & USB_OTGCTRL_VBUSDSCHG_MASK)

/*!
 * @brief USB_INTSTAT Register Bit Definition
 */

#define USB_INTSTAT_STALL_SHIFT                (7)
#define USB_INTSTAT_STALL_MASK                 (0x01U << USB_INTSTAT_STALL_SHIFT)
#define USB_INTSTAT_STALL(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_STALL_SHIFT)) & USB_INTSTAT_STALL_MASK)

#define USB_INTSTAT_ATTACH_SHIFT               (6)
#define USB_INTSTAT_ATTACH_MASK                (0x01U << USB_INTSTAT_ATTACH_SHIFT)
#define USB_INTSTAT_ATTACH(x)                  (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_ATTACH_SHIFT)) & USB_INTSTAT_ATTACH_MASK)

#define USB_INTSTAT_RESUME_SHIFT               (5)
#define USB_INTSTAT_RESUME_MASK                (0x01U << USB_INTSTAT_RESUME_SHIFT)
#define USB_INTSTAT_RESUME(x)                  (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_RESUME_SHIFT)) & USB_INTSTAT_RESUME_MASK)

#define USB_INTSTAT_SLEEP_SHIFT                (4)
#define USB_INTSTAT_SLEEP_MASK                 (0x01U << USB_INTSTAT_SLEEP_SHIFT)
#define USB_INTSTAT_SLEEP(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_SLEEP_SHIFT)) & USB_INTSTAT_SLEEP_MASK)

#define USB_INTSTAT_TOKDNE_SHIFT               (3)
#define USB_INTSTAT_TOKDNE_MASK                (0x01U << USB_INTSTAT_TOKDNE_SHIFT)
#define USB_INTSTAT_TOKDNE(x)                  (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_TOKDNE_SHIFT)) & USB_INTSTAT_TOKDNE_MASK)

#define USB_INTSTAT_SOFTOK_SHIFT               (2)
#define USB_INTSTAT_SOFTOK_MASK                (0x01U << USB_INTSTAT_SOFTOK_SHIFT)
#define USB_INTSTAT_SOFTOK(x)                  (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_SOFTOK_SHIFT)) & USB_INTSTAT_SOFTOK_MASK)

#define USB_INTSTAT_ERROR_SHIFT                (1)
#define USB_INTSTAT_ERROR_MASK                 (0x01U << USB_INTSTAT_ERROR_SHIFT)
#define USB_INTSTAT_ERROR(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_ERROR_SHIFT)) & USB_INTSTAT_ERROR_MASK)

#define USB_INTSTAT_USBRST_SHIFT               (0)
#define USB_INTSTAT_USBRST_MASK                (0x01U << USB_INTSTAT_USBRST_SHIFT)
#define USB_INTSTAT_USBRST(x)                  (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_USBRST_SHIFT)) & USB_INTSTAT_USBRST_MASK)

/*!
 * @brief USB_INTENB Register Bit Definition
 */

#define USB_INTENB_STALL_SHIFT                 (7)
#define USB_INTENB_STALL_MASK                  (0x01U << USB_INTENB_STALL_SHIFT)
#define USB_INTENB_STALL(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTENB_STALL_SHIFT)) & USB_INTENB_STALL_MASK)

#define USB_INTENB_ATTACH_SHIFT                (6)
#define USB_INTENB_ATTACH_MASK                 (0x01U << USB_INTENB_ATTACH_SHIFT)
#define USB_INTENB_ATTACH(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTENB_ATTACH_SHIFT)) & USB_INTENB_ATTACH_MASK)

#define USB_INTENB_RESUME_SHIFT                (5)
#define USB_INTENB_RESUME_MASK                 (0x01U << USB_INTENB_RESUME_SHIFT)
#define USB_INTENB_RESUME(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTENB_RESUME_SHIFT)) & USB_INTENB_RESUME_MASK)

#define USB_INTENB_SLEEP_SHIFT                 (4)
#define USB_INTENB_SLEEP_MASK                  (0x01U << USB_INTENB_SLEEP_SHIFT)
#define USB_INTENB_SLEEP(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTENB_SLEEP_SHIFT)) & USB_INTENB_SLEEP_MASK)

#define USB_INTENB_TOKDNE_SHIFT                (3)
#define USB_INTENB_TOKDNE_MASK                 (0x01U << USB_INTENB_TOKDNE_SHIFT)
#define USB_INTENB_TOKDNE(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTENB_TOKDNE_SHIFT)) & USB_INTENB_TOKDNE_MASK)

#define USB_INTENB_SOFTOK_SHIFT                (2)
#define USB_INTENB_SOFTOK_MASK                 (0x01U << USB_INTENB_SOFTOK_SHIFT)
#define USB_INTENB_SOFTOK(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTENB_SOFTOK_SHIFT)) & USB_INTENB_SOFTOK_MASK)

#define USB_INTENB_ERROR_SHIFT                 (1)
#define USB_INTENB_ERROR_MASK                  (0x01U << USB_INTENB_ERROR_SHIFT)
#define USB_INTENB_ERROR(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTENB_ERROR_SHIFT)) & USB_INTENB_ERROR_MASK)

#define USB_INTENB_USBRST_SHIFT                (0)
#define USB_INTENB_USBRST_MASK                 (0x01U << USB_INTENB_USBRST_SHIFT)
#define USB_INTENB_USBRST(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTENB_USBRST_SHIFT)) & USB_INTENB_USBRST_MASK)

/*!
 * @brief USB_ERRSTAT Register Bit Definition
 */

#define USB_ERRSTAT_BTSERR_SHIFT               (7)
#define USB_ERRSTAT_BTSERR_MASK                (0x01U << USB_ERRSTAT_BTSERR_SHIFT)
#define USB_ERRSTAT_BTSERR(x)                  (((uint32_t)(((uint32_t)(x)) << USB_ERRSTAT_BTSERR_SHIFT)) & USB_ERRSTAT_BTSERR_MASK)

#define USB_ERRSTAT_DMAERR_SHIFT               (5)
#define USB_ERRSTAT_DMAERR_MASK                (0x01U << USB_ERRSTAT_DMAERR_SHIFT)
#define USB_ERRSTAT_DMAERR(x)                  (((uint32_t)(((uint32_t)(x)) << USB_ERRSTAT_DMAERR_SHIFT)) & USB_ERRSTAT_DMAERR_MASK)

#define USB_ERRSTAT_BTOERR_SHIFT               (4)
#define USB_ERRSTAT_BTOERR_MASK                (0x01U << USB_ERRSTAT_BTOERR_SHIFT)
#define USB_ERRSTAT_BTOERR(x)                  (((uint32_t)(((uint32_t)(x)) << USB_ERRSTAT_BTOERR_SHIFT)) & USB_ERRSTAT_BTOERR_MASK)

#define USB_ERRSTAT_DFN8_SHIFT                 (3)
#define USB_ERRSTAT_DFN8_MASK                  (0x01U << USB_ERRSTAT_DFN8_SHIFT)
#define USB_ERRSTAT_DFN8(x)                    (((uint32_t)(((uint32_t)(x)) << USB_ERRSTAT_DFN8_SHIFT)) & USB_ERRSTAT_DFN8_MASK)

#define USB_ERRSTAT_CRC16_SHIFT                (2)
#define USB_ERRSTAT_CRC16_MASK                 (0x01U << USB_ERRSTAT_CRC16_SHIFT)
#define USB_ERRSTAT_CRC16(x)                   (((uint32_t)(((uint32_t)(x)) << USB_ERRSTAT_CRC16_SHIFT)) & USB_ERRSTAT_CRC16_MASK)

#define USB_ERRSTAT_CRC5EOF_SHIFT              (1)
#define USB_ERRSTAT_CRC5EOF_MASK               (0x01U << USB_ERRSTAT_CRC5EOF_SHIFT)
#define USB_ERRSTAT_CRC5EOF(x)                 (((uint32_t)(((uint32_t)(x)) << USB_ERRSTAT_CRC5EOF_SHIFT)) & USB_ERRSTAT_CRC5EOF_MASK)

#define USB_ERRSTAT_PIDERR_SHIFT               (0)
#define USB_ERRSTAT_PIDERR_MASK                (0x01U << USB_ERRSTAT_PIDERR_SHIFT)
#define USB_ERRSTAT_PIDERR(x)                  (((uint32_t)(((uint32_t)(x)) << USB_ERRSTAT_PIDERR_SHIFT)) & USB_ERRSTAT_PIDERR_MASK)

/*!
 * @brief USB_ERRENB Register Bit Definition
 */

#define USB_ERRENB_BTSERR_SHIFT                (7)
#define USB_ERRENB_BTSERR_MASK                 (0x01U << USB_ERRENB_BTSERR_SHIFT)
#define USB_ERRENB_BTSERR(x)                   (((uint32_t)(((uint32_t)(x)) << USB_ERRENB_BTSERR_SHIFT)) & USB_ERRENB_BTSERR_MASK)

#define USB_ERRENB_DMAERR_SHIFT                (5)
#define USB_ERRENB_DMAERR_MASK                 (0x01U << USB_ERRENB_DMAERR_SHIFT)
#define USB_ERRENB_DMAERR(x)                   (((uint32_t)(((uint32_t)(x)) << USB_ERRENB_DMAERR_SHIFT)) & USB_ERRENB_DMAERR_MASK)

#define USB_ERRENB_BTOERR_SHIFT                (4)
#define USB_ERRENB_BTOERR_MASK                 (0x01U << USB_ERRENB_BTOERR_SHIFT)
#define USB_ERRENB_BTOERR(x)                   (((uint32_t)(((uint32_t)(x)) << USB_ERRENB_BTOERR_SHIFT)) & USB_ERRENB_BTOERR_MASK)

#define USB_ERRENB_DFN8_SHIFT                  (3)
#define USB_ERRENB_DFN8_MASK                   (0x01U << USB_ERRENB_DFN8_SHIFT)
#define USB_ERRENB_DFN8(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ERRENB_DFN8_SHIFT)) & USB_ERRENB_DFN8_MASK)

#define USB_ERRENB_CRC16_SHIFT                 (2)
#define USB_ERRENB_CRC16_MASK                  (0x01U << USB_ERRENB_CRC16_SHIFT)
#define USB_ERRENB_CRC16(x)                    (((uint32_t)(((uint32_t)(x)) << USB_ERRENB_CRC16_SHIFT)) & USB_ERRENB_CRC16_MASK)

#define USB_ERRENB_CRC5EOF_SHIFT               (1)
#define USB_ERRENB_CRC5EOF_MASK                (0x01U << USB_ERRENB_CRC5EOF_SHIFT)
#define USB_ERRENB_CRC5EOF(x)                  (((uint32_t)(((uint32_t)(x)) << USB_ERRENB_CRC5EOF_SHIFT)) & USB_ERRENB_CRC5EOF_MASK)

#define USB_ERRENB_PIDERR_SHIFT                (0)
#define USB_ERRENB_PIDERR_MASK                 (0x01U << USB_ERRENB_PIDERR_SHIFT)
#define USB_ERRENB_PIDERR(x)                   (((uint32_t)(((uint32_t)(x)) << USB_ERRENB_PIDERR_SHIFT)) & USB_ERRENB_PIDERR_MASK)

/*!
 * @brief USB_STAT Register Bit Definition
 */

#define USB_STAT_ENDP_SHIFT                     (4)
#define USB_STAT_ENDP_MASK                      (0xFU << USB_STAT_ENDP_SHIFT)
#define USB_STAT_ENDP(x)                        (((uint32_t)(((uint32_t)(x)) << USB_STAT_ENDP_SHIFT)) & USB_STAT_ENDP_MASK)

#define USB_STAT_TX_SHIFT                       (3)
#define USB_STAT_TX_MASK                        (0x01U << USB_STAT_TX_SHIFT)
#define USB_STAT_TX(x)                          (((uint32_t)(((uint32_t)(x)) << USB_STAT_TX_SHIFT)) & USB_STAT_TX_MASK)

#define USB_STAT_ODD_SHIFT                      (2)
#define USB_STAT_ODD_MASK                       (0x01U << USB_STAT_ODD_SHIFT)
#define USB_STAT_ODD(x)                         (((uint32_t)(((uint32_t)(x)) << USB_STAT_ODD_SHIFT)) & USB_STAT_ODD_MASK)

/*!
 * @brief USB_CTL Register Bit Definition
 */

#define USB_CTL_JSTATE_SHIFT                    (7)
#define USB_CTL_JSTATE_MASK                     (0x01U << USB_CTL_JSTATE_SHIFT)
#define USB_CTL_JSTATE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_CTL_JSTATE_SHIFT)) & USB_CTL_JSTATE_MASK)

#define USB_CTL_SE0_SHIFT                       (6)
#define USB_CTL_SE0_MASK                        (0x01U << USB_CTL_SE0_SHIFT)
#define USB_CTL_SE0(x)                          (((uint32_t)(((uint32_t)(x)) << USB_CTL_SE0_SHIFT)) & USB_CTL_SE0_MASK)

#define USB_CTL_TXDSUSPENDTOKENBUSY_SHIFT       (5)
#define USB_CTL_TXDSUSPENDTOKENBUSY_MASK        (0x01U << USB_CTL_TXDSUSPENDTOKENBUSY_SHIFT)
#define USB_CTL_TXDSUSPENDTOKENBUSY(x)          (((uint32_t)(((uint32_t)(x)) << USB_CTL_TXDSUSPENDTOKENBUSY_SHIFT)) & USB_CTL_TXDSUSPENDTOKENBUSY_MASK)

#define USB_CTL_RESET_SHIFT                     (4)
#define USB_CTL_RESET_MASK                      (0x01U << USB_CTL_RESET_SHIFT)
#define USB_CTL_RESET(x)                        (((uint32_t)(((uint32_t)(x)) << USB_CTL_RESET_SHIFT)) & USB_CTL_RESET_MASK)

#define USB_CTL_HOSTMODEEN_SHIFT                (3)
#define USB_CTL_HOSTMODEEN_MASK                 (0x01U << USB_CTL_HOSTMODEEN_SHIFT)
#define USB_CTL_HOSTMODEEN(x)                   (((uint32_t)(((uint32_t)(x)) << USB_CTL_HOSTMODEEN_SHIFT)) & USB_CTL_HOSTMODEEN_MASK)

#define USB_CTL_RESUME_SHIFT                    (2)
#define USB_CTL_RESUME_MASK                     (0x01U << USB_CTL_RESUME_SHIFT)
#define USB_CTL_RESUME(x)                       (((uint32_t)(((uint32_t)(x)) << USB_CTL_RESUME_SHIFT)) & USB_CTL_RESUME_MASK)

#define USB_CTL_ODDRST_SHIFT                    (1)
#define USB_CTL_ODDRST_MASK                     (0x01U << USB_CTL_ODDRST_SHIFT)
#define USB_CTL_ODDRST(x)                       (((uint32_t)(((uint32_t)(x)) << USB_CTL_ODDRST_SHIFT)) & USB_CTL_ODDRST_MASK)

#define USB_CTL_USBEN_SHIFT                     (0)
#define USB_CTL_USBEN_MASK                      (0x01U << USB_CTL_USBEN_SHIFT)
#define USB_CTL_USBEN(x)                        (((uint32_t)(((uint32_t)(x)) << USB_CTL_USBEN_SHIFT)) & USB_CTL_USBEN_MASK)

/*!
 * @brief USB_ADDR Register Bit Definition
 */

#define USB_ADDR_LSEN_SHIFT                     (7)
#define USB_ADDR_LSEN_MASK                      (0x01U << USB_ADDR_LSEN_SHIFT)
#define USB_ADDR_LSEN(x)                        (((uint32_t)(((uint32_t)(x)) << USB_ADDR_LSEN_SHIFT)) & USB_ADDR_LSEN_MASK)

#define USB_ADDR_ADDR_SHIFT                     (0)
#define USB_ADDR_ADDR_MASK                      (0x7FU << USB_ADDR_ADDR_SHIFT)
#define USB_ADDR_ADDR(x)                        (((uint32_t)(((uint32_t)(x)) << USB_ADDR_ADDR_SHIFT)) & USB_ADDR_ADDR_MASK)

/*!
 * @brief USB_BDTPAGE01 Register Bit Definition
 */

#define USB_BDTPAGE01_BDTBA_SHIFT             (1)
#define USB_BDTPAGE01_BDTBA_MASK              (0x7FU << USB_BDTPAGE01_BDTBA_SHIFT)
#define USB_BDTPAGE01_BDTBA(x)                (((uint32_t)(((uint32_t)(x)) << USB_BDTPAGE01_BDTBA_SHIFT)) & USB_BDTPAGE01_BDTBA_MASK)

/*!
 * @brief USB_FRMNUML Register Bit Definition
 */

#define USB_FRMNUML_FRM_SHIFT                  (0)
#define USB_FRMNUML_FRM_MASK                   (0xFFU << USB_FRMNUML_FRM_SHIFT)
#define USB_FRMNUML_FRM(x)                     (((uint32_t)(((uint32_t)(x)) << USB_FRMNUML_FRM_SHIFT)) & USB_FRMNUML_FRM_MASK)

/*!
 * @brief USB_FRMNUMH Register Bit Definition
 */

#define USB_FRMNUMH_FRM_SHIFT                  (0)
#define USB_FRMNUMH_FRM_MASK                   (0x7U << USB_FRMNUMH_FRM_SHIFT)
#define USB_FRMNUMH_FRM(x)                     (((uint32_t)(((uint32_t)(x)) << USB_FRMNUMH_FRM_SHIFT)) & USB_FRMNUMH_FRM_MASK)

/*!
 * @brief USB_TOKEN Register Bit Definition
 */

#define USB_TOKEN_TOKENPID_SHIFT                (4)
#define USB_TOKEN_TOKENPID_MASK                 (0xFU << USB_TOKEN_TOKENPID_SHIFT)
#define USB_TOKEN_TOKENPID(x)                   (((uint32_t)(((uint32_t)(x)) << USB_TOKEN_TOKENPID_SHIFT)) & USB_TOKEN_TOKENPID_MASK)

#define USB_TOKEN_TOKENENDPT_SHIFT              (0)
#define USB_TOKEN_TOKENENDPT_MASK               (0xFU << USB_TOKEN_TOKENENDPT_SHIFT)
#define USB_TOKEN_TOKENENDPT(x)                 (((uint32_t)(((uint32_t)(x)) << USB_TOKEN_TOKENENDPT_SHIFT)) & USB_TOKEN_TOKENENDPT_MASK)

/*!
 * @brief USB_SOFTHLD Register Bit Definition
 */

#define USB_SOFTHLD_CNT_SHIFT                  (0)
#define USB_SOFTHLD_CNT_MASK                   (0xFFU << USB_SOFTHLD_CNT_SHIFT)
#define USB_SOFTHLD_CNT(x)                     (((uint32_t)(((uint32_t)(x)) << USB_SOFTHLD_CNT_SHIFT)) & USB_SOFTHLD_CNT_MASK)

/*!
 * @brief USB_BDTPAGE02 Register Bit Definition
 */

#define USB_BDTPAGE02_BDTBA_SHIFT             (0)
#define USB_BDTPAGE02_BDTBA_MASK              (0xFFU << USB_BDTPAGE02_BDTBA_SHIFT)
#define USB_BDTPAGE02_BDTBA(x)                (((uint32_t)(((uint32_t)(x)) << USB_BDTPAGE02_BDTBA_SHIFT)) & USB_BDTPAGE02_BDTBA_MASK)

/*!
 * @brief USB_BDTPAGE03 Register Bit Definition
 */

#define USB_BDTPAGE03_BDTBA_SHIFT             (0)
#define USB_BDTPAGE03_BDTBA_MASK              (0xFFU << USB_BDTPAGE03_BDTBA_SHIFT)
#define USB_BDTPAGE03_BDTBA(x)                (((uint32_t)(((uint32_t)(x)) << USB_BDTPAGE03_BDTBA_SHIFT)) & USB_BDTPAGE03_BDTBA_MASK)

/*!
 * @brief USB_EPCTL Register Bit Definition
 */

#define USB_EPCTL_HOSTWOHUB_SHIFT              (7)
#define USB_EPCTL_HOSTWOHUB_MASK               (0x01U << USB_EPCTL_HOSTWOHUB_SHIFT)
#define USB_EPCTL_HOSTWOHUB(x)                 (((uint32_t)(((uint32_t)(x)) << USB_EPCTL_HOSTWOHUB_SHIFT)) & USB_EPCTL_HOSTWOHUB_MASK)

#define USB_EPCTL_RETRYDIS_SHIFT               (6)
#define USB_EPCTL_RETRYDIS_MASK                (0x01U << USB_EPCTL_RETRYDIS_SHIFT)
#define USB_EPCTL_RETRYDIS(x)                  (((uint32_t)(((uint32_t)(x)) << USB_EPCTL_RETRYDIS_SHIFT)) & USB_EPCTL_RETRYDIS_MASK)

#define USB_EPCTL_EPCTLDISEPRXENEPTXEN_SHIFT   (2)
#define USB_EPCTL_EPCTLDISEPRXENEPTXEN_MASK    (0x7U << USB_EPCTL_EPCTLDISEPRXENEPTXEN_SHIFT)
#define USB_EPCTL_EPCTLDISEPRXENEPTXEN(x)      (((uint32_t)(((uint32_t)(x)) << USB_EPCTL_EPCTLDISEPRXENEPTXEN_SHIFT)) & USB_EPCTL_EPCTLDISEPRXENEPTXEN_MASK)

#define USB_EPCTL_EPSTALL_SHIFT                (1)
#define USB_EPCTL_EPSTALL_MASK                 (0x01U << USB_EPCTL_EPSTALL_SHIFT)
#define USB_EPCTL_EPSTALL(x)                   (((uint32_t)(((uint32_t)(x)) << USB_EPCTL_EPSTALL_SHIFT)) & USB_EPCTL_EPSTALL_MASK)

#define USB_EPCTL_EPHSHK_SHIFT                 (0)
#define USB_EPCTL_EPHSHK_MASK                  (0x01U << USB_EPCTL_EPHSHK_SHIFT)
#define USB_EPCTL_EPHSHK(x)                    (((uint32_t)(((uint32_t)(x)) << USB_EPCTL_EPHSHK_SHIFT)) & USB_EPCTL_EPHSHK_MASK)

/*!
 * @}
 */ /* end of group USB_Register_Masks */
/******************************************************************************
 * USB Instance
******************************************************************************/
#define USB                             ((USB_Type*)USB_FS_OTG_BASE)

/*!
 * @}
 */ /* end of group USB_Peripheral_Access_Layer */



/*!
 * @addtogroup ETH_Peripheral_Access_Layer ETH Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * ETH Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t MACCR;                                                          ///< MAC configuration register                   offset: 0x0000
    __IO uint32_t MACAFR;                                                         ///< MAC address filter control register          offset: 0x0004
    __IO uint32_t MACHTHR;                                                        ///< MAC HASH table high register                 offset: 0x0008
    __IO uint32_t MACHTLR;                                                        ///< MAC HASH table low register                  offset: 0x000C
    __IO uint32_t MACSMIAR;                                                       ///< SMI address register                         offset: 0x0010
    __IO uint32_t MACSMIDR;                                                       ///< SMI data register                            offset: 0x0014
    __IO uint32_t MACFCR;                                                         ///< MAC flow control register                    offset: 0x0018
    __IO uint32_t MACVLTR;                                                        ///< MAC VLAN Tag Register                        offset: 0x001C
    __IO uint32_t Reserved25[1];                                                  ///< Reserved
    __IO uint32_t MACSR;                                                          ///< MAC status register                          offset: 0x0024
    __IO uint32_t Reserved26[6];                                                  ///< Reserved
    struct{
          __IO uint32_t MACAHR;                                                   ///< MAC filter address high register            offset: 0x0040
          __IO uint32_t MACALR;                                                   ///< MAC filter address low register             offset: 0x0044
        }MACAH_L[16];
    __IO uint32_t Reserved27[464];                                                ///< Reserved
    struct{
          __IO uint32_t MACAHR;                                                   ///< MAC filter address high register            offset: 0x0800
          __IO uint32_t MACALR;                                                   ///< MAC filter address low register             offset: 0x0804
        }MACAH_H[16];
    __IO uint32_t Reserved28[480];                                                ///< Reserved
    __IO uint32_t DMABSR;                                                         ///< DMA bus control register                     offset: 0x1000
    __IO uint32_t DMATXPDR;                                                       ///< DMA send polling register                    offset: 0x1004
    __IO uint32_t DMARXPDR;                                                       ///< DMA receive polling register                 offset: 0x1008
    __IO uint32_t DMARXDSAR;                                                      ///< DMA receive descriptor address register      offset: 0x100C
    __IO uint32_t DMATXDSAR;                                                      ///< DMA send descriptor address register         offset: 0x1010
    __IO uint32_t DMASR;                                                          ///< DMA status register                          offset: 0x1014
    __IO uint32_t DMAMDR;                                                         ///< DMA working mode register                    offset: 0x0018
    __IO uint32_t DMAIR;                                                          ///< DMA interrupt register                       offset: 0x101C
    __IO uint32_t DMAFLCR;                                                        ///< DMA frame loss statistics register           offset: 0x1020
    __IO uint32_t DMAWDTR;                                                        ///< DMA watchdog timer register                  offset: 0x1024
    __IO uint32_t Reserved32[8];                                                  ///< Reserved
    __IO uint32_t DMACUTTXDSAR;                                                   ///< DMA current send descriptor address register offset: 0x1048
    __IO uint32_t DMACUTRXDSAR;                                                   ///< DMA current receive descriptor address registeroffset: 0x104C
    __IO uint32_t DMACUTTXBFAR;                                                   ///< DMA current send buffer address register     offset: 0x1050
    __IO uint32_t DMACUTRXBFAR;                                                   ///< DMA current receive buffer address register  offset: 0x1054

} ETH_Type;

/*******************************************************************************
 * ETH Type
 ******************************************************************************/

/*!
 * @addtogroup ETH_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief ETH_MACSMIAR Register Bit Definition
 */

#define ETH_MACSMIAR_SMIADD_SHIFT               (11)
#define ETH_MACSMIAR_SMIADD_MASK                (0x1FU << ETH_MACSMIAR_SMIADD_SHIFT)
#define ETH_MACSMIAR_SMIADD(x)                  (((uint32_t)(((uint32_t)(x)) << ETH_MACSMIAR_SMIADD_SHIFT)) & ETH_MACSMIAR_SMIADD_MASK)

#define ETH_MACSMIAR_SMIREG_SHIFT               (6)
#define ETH_MACSMIAR_SMIREG_MASK                (0x1FU << ETH_MACSMIAR_SMIREG_SHIFT)
#define ETH_MACSMIAR_SMIREG(x)                  (((uint32_t)(((uint32_t)(x)) << ETH_MACSMIAR_SMIREG_SHIFT)) & ETH_MACSMIAR_SMIREG_MASK)

#define ETH_MACSMIAR_SMICLK_SHIFT               (2)
#define ETH_MACSMIAR_SMICLK_MASK                (0xFU << ETH_MACSMIAR_SMICLK_SHIFT)
#define ETH_MACSMIAR_SMICLK(x)                  (((uint32_t)(((uint32_t)(x)) << ETH_MACSMIAR_SMICLK_SHIFT)) & ETH_MACSMIAR_SMICLK_MASK)

#define ETH_MACSMIAR_SMIWR_SHIFT                (1)
#define ETH_MACSMIAR_SMIWR_MASK                 (0x01U << ETH_MACSMIAR_SMIWR_SHIFT)
#define ETH_MACSMIAR_SMIWR(x)                   (((uint32_t)(((uint32_t)(x)) << ETH_MACSMIAR_SMIWR_SHIFT)) & ETH_MACSMIAR_SMIWR_MASK)

#define ETH_MACSMIAR_SMIBY_SHIFT                (0)
#define ETH_MACSMIAR_SMIBY_MASK                 (0x01U << ETH_MACSMIAR_SMIBY_SHIFT)
#define ETH_MACSMIAR_SMIBY(x)                   (((uint32_t)(((uint32_t)(x)) << ETH_MACSMIAR_SMIBY_SHIFT)) & ETH_MACSMIAR_SMIBY_MASK)

/*!
 * @brief ETH_MACSMIDR Register Bit Definition
 */

#define ETH_MACSMIDR_SMIDATA_SHIFT              (0)
#define ETH_MACSMIDR_SMIDATA_MASK               (0xFFFFU << ETH_MACSMIDR_SMIDATA_SHIFT)
#define ETH_MACSMIDR_SMIDATA(x)                 (((uint32_t)(((uint32_t)(x)) << ETH_MACSMIDR_SMIDATA_SHIFT)) & ETH_MACSMIDR_SMIDATA_MASK)

/*!
 * @brief ETH_MACCR Register Bit Definition
 */

#define ETH_MACCR_CST_SHIFT                     (25)
#define ETH_MACCR_CST_MASK                      (0x01U << ETH_MACCR_CST_SHIFT)
#define ETH_MACCR_CST(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_CST_SHIFT)) & ETH_MACCR_CST_MASK)

#define ETH_MACCR_WTD_SHIFT                     (23)
#define ETH_MACCR_WTD_MASK                      (0x01U << ETH_MACCR_WTD_SHIFT)
#define ETH_MACCR_WTD(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_WTD_SHIFT)) & ETH_MACCR_WTD_MASK)

#define ETH_MACCR_JD_SHIFT                      (22)
#define ETH_MACCR_JD_MASK                       (0x01U << ETH_MACCR_JD_SHIFT)
#define ETH_MACCR_JD(x)                         (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_JD_SHIFT)) & ETH_MACCR_JD_MASK)

#define ETH_MACCR_IFG_SHIFT                     (17)
#define ETH_MACCR_IFG_MASK                      (0x7U << ETH_MACCR_IFG_SHIFT)
#define ETH_MACCR_IFG(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_IFG_SHIFT)) & ETH_MACCR_IFG_MASK)

#define ETH_MACCR_MCRS_SHIFT                    (16)
#define ETH_MACCR_MCRS_MASK                     (0x01U << ETH_MACCR_MCRS_SHIFT)
#define ETH_MACCR_MCRS(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_MCRS_SHIFT)) & ETH_MACCR_MCRS_MASK)

#define ETH_MACCR_ROD_SHIFT                     (13)
#define ETH_MACCR_ROD_MASK                      (0x01U << ETH_MACCR_ROD_SHIFT)
#define ETH_MACCR_ROD(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_ROD_SHIFT)) & ETH_MACCR_ROD_MASK)

#define ETH_MACCR_LM_SHIFT                      (12)
#define ETH_MACCR_LM_MASK                       (0x01U << ETH_MACCR_LM_SHIFT)
#define ETH_MACCR_LM(x)                         (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_LM_SHIFT)) & ETH_MACCR_LM_MASK)

#define ETH_MACCR_DM_SHIFT                      (11)
#define ETH_MACCR_DM_MASK                       (0x01U << ETH_MACCR_DM_SHIFT)
#define ETH_MACCR_DM(x)                         (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_DM_SHIFT)) & ETH_MACCR_DM_MASK)

#define ETH_MACCR_IPCO_SHIFT                    (10)
#define ETH_MACCR_IPCO_MASK                     (0x01U << ETH_MACCR_IPCO_SHIFT)
#define ETH_MACCR_IPCO(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_IPCO_SHIFT)) & ETH_MACCR_IPCO_MASK)

#define ETH_MACCR_RETY_SHIFT                    (9)
#define ETH_MACCR_RETY_MASK                     (0x01U << ETH_MACCR_RETY_SHIFT)
#define ETH_MACCR_RETY(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_RETY_SHIFT)) & ETH_MACCR_RETY_MASK)

#define ETH_MACCR_APCS_SHIFT                    (7)
#define ETH_MACCR_APCS_MASK                     (0x01U << ETH_MACCR_APCS_SHIFT)
#define ETH_MACCR_APCS(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_APCS_SHIFT)) & ETH_MACCR_APCS_MASK)

#define ETH_MACCR_BL_SHIFT                      (5)
#define ETH_MACCR_BL_MASK                       (0x3U << ETH_MACCR_BL_SHIFT)
#define ETH_MACCR_BL(x)                         (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_BL_SHIFT)) & ETH_MACCR_BL_MASK)

#define ETH_MACCR_DLYC_SHIFT                    (4)
#define ETH_MACCR_DLYC_MASK                     (0x01U << ETH_MACCR_DLYC_SHIFT)
#define ETH_MACCR_DLYC(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_DLYC_SHIFT)) & ETH_MACCR_DLYC_MASK)

#define ETH_MACCR_TE_SHIFT                      (3)
#define ETH_MACCR_TE_MASK                       (0x01U << ETH_MACCR_TE_SHIFT)
#define ETH_MACCR_TE(x)                         (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_TE_SHIFT)) & ETH_MACCR_TE_MASK)

#define ETH_MACCR_RE_SHIFT                      (2)
#define ETH_MACCR_RE_MASK                       (0x01U << ETH_MACCR_RE_SHIFT)
#define ETH_MACCR_RE(x)                         (((uint32_t)(((uint32_t)(x)) << ETH_MACCR_RE_SHIFT)) & ETH_MACCR_RE_MASK)

/*!
 * @brief ETH_MACSR Register Bit Definition
 */

#define ETH_MACSR_TXFF_SHIFT                    (25)
#define ETH_MACSR_TXFF_MASK                     (0x01U << ETH_MACSR_TXFF_SHIFT)
#define ETH_MACSR_TXFF(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACSR_TXFF_SHIFT)) & ETH_MACSR_TXFF_MASK)

#define ETH_MACSR_TXFNE_SHIFT                   (24)
#define ETH_MACSR_TXFNE_MASK                    (0x01U << ETH_MACSR_TXFNE_SHIFT)
#define ETH_MACSR_TXFNE(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_MACSR_TXFNE_SHIFT)) & ETH_MACSR_TXFNE_MASK)

#define ETH_MACSR_TXFWA_SHIFT                   (22)
#define ETH_MACSR_TXFWA_MASK                    (0x01U << ETH_MACSR_TXFWA_SHIFT)
#define ETH_MACSR_TXFWA(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_MACSR_TXFWA_SHIFT)) & ETH_MACSR_TXFWA_MASK)

#define ETH_MACSR_TXFRS_SHIFT                   (20)
#define ETH_MACSR_TXFRS_MASK                    (0x3U << ETH_MACSR_TXFRS_SHIFT)
#define ETH_MACSR_TXFRS(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_MACSR_TXFRS_SHIFT)) & ETH_MACSR_TXFRS_MASK)

#define ETH_MACSR_MTP_SHIFT                     (19)
#define ETH_MACSR_MTP_MASK                      (0x01U << ETH_MACSR_MTP_SHIFT)
#define ETH_MACSR_MTP(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_MACSR_MTP_SHIFT)) & ETH_MACSR_MTP_MASK)

#define ETH_MACSR_MTS_SHIFT                     (17)
#define ETH_MACSR_MTS_MASK                      (0x3U << ETH_MACSR_MTS_SHIFT)
#define ETH_MACSR_MTS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_MACSR_MTS_SHIFT)) & ETH_MACSR_MTS_MASK)

#define ETH_MACSR_MTE_SHIFT                     (16)
#define ETH_MACSR_MTE_MASK                      (0x01U << ETH_MACSR_MTE_SHIFT)
#define ETH_MACSR_MTE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_MACSR_MTE_SHIFT)) & ETH_MACSR_MTE_MASK)

#define ETH_MACSR_RXFLL_SHIFT                   (8)
#define ETH_MACSR_RXFLL_MASK                    (0x3U << ETH_MACSR_RXFLL_SHIFT)
#define ETH_MACSR_RXFLL(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_MACSR_RXFLL_SHIFT)) & ETH_MACSR_RXFLL_MASK)

#define ETH_MACSR_RXFRS_SHIFT                   (5)
#define ETH_MACSR_RXFRS_MASK                    (0x3U << ETH_MACSR_RXFRS_SHIFT)
#define ETH_MACSR_RXFRS(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_MACSR_RXFRS_SHIFT)) & ETH_MACSR_RXFRS_MASK)

#define ETH_MACSR_RXFWA_SHIFT                   (4)
#define ETH_MACSR_RXFWA_MASK                    (0x01U << ETH_MACSR_RXFWA_SHIFT)
#define ETH_MACSR_RXFWA(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_MACSR_RXFWA_SHIFT)) & ETH_MACSR_RXFWA_MASK)

#define ETH_MACSR_MRS_SHIFT                     (1)
#define ETH_MACSR_MRS_MASK                      (0x3U << ETH_MACSR_MRS_SHIFT)
#define ETH_MACSR_MRS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_MACSR_MRS_SHIFT)) & ETH_MACSR_MRS_MASK)

#define ETH_MACSR_MRE_SHIFT                     (0)
#define ETH_MACSR_MRE_MASK                      (0x01U << ETH_MACSR_MRE_SHIFT)
#define ETH_MACSR_MRE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_MACSR_MRE_SHIFT)) & ETH_MACSR_MRE_MASK)

/*!
 * @brief ETH_MACFCR Register Bit Definition
 */

#define ETH_MACFCR_PSET_SHIFT                   (16)
#define ETH_MACFCR_PSET_MASK                    (0xFFFFU << ETH_MACFCR_PSET_SHIFT)
#define ETH_MACFCR_PSET(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_MACFCR_PSET_SHIFT)) & ETH_MACFCR_PSET_MASK)

#define ETH_MACFCR_DZPQ_SHIFT                   (7)
#define ETH_MACFCR_DZPQ_MASK                    (0x01U << ETH_MACFCR_DZPQ_SHIFT)
#define ETH_MACFCR_DZPQ(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_MACFCR_DZPQ_SHIFT)) & ETH_MACFCR_DZPQ_MASK)

#define ETH_MACFCR_PLT_SHIFT                    (4)
#define ETH_MACFCR_PLT_MASK                     (0x3U << ETH_MACFCR_PLT_SHIFT)
#define ETH_MACFCR_PLT(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACFCR_PLT_SHIFT)) & ETH_MACFCR_PLT_MASK)

#define ETH_MACFCR_UP_SHIFT                     (3)
#define ETH_MACFCR_UP_MASK                      (0x01U << ETH_MACFCR_UP_SHIFT)
#define ETH_MACFCR_UP(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_MACFCR_UP_SHIFT)) & ETH_MACFCR_UP_MASK)

#define ETH_MACFCR_FRE_SHIFT                    (2)
#define ETH_MACFCR_FRE_MASK                     (0x01U << ETH_MACFCR_FRE_SHIFT)
#define ETH_MACFCR_FRE(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACFCR_FRE_SHIFT)) & ETH_MACFCR_FRE_MASK)

#define ETH_MACFCR_FTE_SHIFT                    (1)
#define ETH_MACFCR_FTE_MASK                     (0x01U << ETH_MACFCR_FTE_SHIFT)
#define ETH_MACFCR_FTE(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACFCR_FTE_SHIFT)) & ETH_MACFCR_FTE_MASK)

#define ETH_MACFCR_FCBBPA_SHIFT                 (0)
#define ETH_MACFCR_FCBBPA_MASK                  (0x01U << ETH_MACFCR_FCBBPA_SHIFT)
#define ETH_MACFCR_FCBBPA(x)                    (((uint32_t)(((uint32_t)(x)) << ETH_MACFCR_FCBBPA_SHIFT)) & ETH_MACFCR_FCBBPA_MASK)

/*!
 * @brief ETH_MACAFR Register Bit Definition
 */

#define ETH_MACAFR_RALL_SHIFT                   (31)
#define ETH_MACAFR_RALL_MASK                    (0x01U << ETH_MACAFR_RALL_SHIFT)
#define ETH_MACAFR_RALL(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_MACAFR_RALL_SHIFT)) & ETH_MACAFR_RALL_MASK)

#define ETH_MACAFR_VTFE_SHIFT                   (16)
#define ETH_MACAFR_VTFE_MASK                    (0x01U << ETH_MACAFR_VTFE_SHIFT)
#define ETH_MACAFR_VTFE(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_MACAFR_VTFE_SHIFT)) & ETH_MACAFR_VTFE_MASK)

#define ETH_MACAFR_HPF_SHIFT                    (10)
#define ETH_MACAFR_HPF_MASK                     (0x01U << ETH_MACAFR_HPF_SHIFT)
#define ETH_MACAFR_HPF(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACAFR_HPF_SHIFT)) & ETH_MACAFR_HPF_MASK)

#define ETH_MACAFR_SAF_SHIFT                    (9)
#define ETH_MACAFR_SAF_MASK                     (0x01U << ETH_MACAFR_SAF_SHIFT)
#define ETH_MACAFR_SAF(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACAFR_SAF_SHIFT)) & ETH_MACAFR_SAF_MASK)

#define ETH_MACAFR_SAIF_SHIFT                   (8)
#define ETH_MACAFR_SAIF_MASK                    (0x01U << ETH_MACAFR_SAIF_SHIFT)
#define ETH_MACAFR_SAIF(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_MACAFR_SAIF_SHIFT)) & ETH_MACAFR_SAIF_MASK)

#define ETH_MACAFR_PCF_SHIFT                    (6)
#define ETH_MACAFR_PCF_MASK                     (0x3U << ETH_MACAFR_PCF_SHIFT)
#define ETH_MACAFR_PCF(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACAFR_PCF_SHIFT)) & ETH_MACAFR_PCF_MASK)

#define ETH_MACAFR_DBF_SHIFT                    (5)
#define ETH_MACAFR_DBF_MASK                     (0x01U << ETH_MACAFR_DBF_SHIFT)
#define ETH_MACAFR_DBF(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACAFR_DBF_SHIFT)) & ETH_MACAFR_DBF_MASK)

#define ETH_MACAFR_PMF_SHIFT                    (4)
#define ETH_MACAFR_PMF_MASK                     (0x01U << ETH_MACAFR_PMF_SHIFT)
#define ETH_MACAFR_PMF(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_MACAFR_PMF_SHIFT)) & ETH_MACAFR_PMF_MASK)

#define ETH_MACAFR_DAIF_SHIFT                   (3)
#define ETH_MACAFR_DAIF_MASK                    (0x01U << ETH_MACAFR_DAIF_SHIFT)
#define ETH_MACAFR_DAIF(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_MACAFR_DAIF_SHIFT)) & ETH_MACAFR_DAIF_MASK)

#define ETH_MACAFR_HM_SHIFT                     (2)
#define ETH_MACAFR_HM_MASK                      (0x01U << ETH_MACAFR_HM_SHIFT)
#define ETH_MACAFR_HM(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_MACAFR_HM_SHIFT)) & ETH_MACAFR_HM_MASK)

#define ETH_MACAFR_HU_SHIFT                     (1)
#define ETH_MACAFR_HU_MASK                      (0x01U << ETH_MACAFR_HU_SHIFT)
#define ETH_MACAFR_HU(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_MACAFR_HU_SHIFT)) & ETH_MACAFR_HU_MASK)

#define ETH_MACAFR_PM_SHIFT                     (0)
#define ETH_MACAFR_PM_MASK                      (0x01U << ETH_MACAFR_PM_SHIFT)
#define ETH_MACAFR_PM(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_MACAFR_PM_SHIFT)) & ETH_MACAFR_PM_MASK)

/*!
 * @brief ETH_MACAHR0 Register Bit Definition
 */

#define ETH_MACAHR0_ADDE_SHIFT                  (31)
#define ETH_MACAHR0_ADDE_MASK                   (0x01U << ETH_MACAHR0_ADDE_SHIFT)
#define ETH_MACAHR0_ADDE(x)                     (((uint32_t)(((uint32_t)(x)) << ETH_MACAHR0_ADDE_SHIFT)) & ETH_MACAHR0_ADDE_MASK)

#define ETH_MACAHR0_SELE_SHIFT                  (30)
#define ETH_MACAHR0_SELE_MASK                   (0x01U << ETH_MACAHR0_SELE_SHIFT)
#define ETH_MACAHR0_SELE(x)                     (((uint32_t)(((uint32_t)(x)) << ETH_MACAHR0_SELE_SHIFT)) & ETH_MACAHR0_SELE_MASK)

#define ETH_MACAHR0_MBYTEC_SHIFT                (24)
#define ETH_MACAHR0_MBYTEC_MASK                 (0x3FU << ETH_MACAHR0_MBYTEC_SHIFT)
#define ETH_MACAHR0_MBYTEC(x)                   (((uint32_t)(((uint32_t)(x)) << ETH_MACAHR0_MBYTEC_SHIFT)) & ETH_MACAHR0_MBYTEC_MASK)

#define ETH_MACAHR0_MACADDH_SHIFT               (0)
#define ETH_MACAHR0_MACADDH_MASK                (0xFFFFU << ETH_MACAHR0_MACADDH_SHIFT)
#define ETH_MACAHR0_MACADDH(x)                  (((uint32_t)(((uint32_t)(x)) << ETH_MACAHR0_MACADDH_SHIFT)) & ETH_MACAHR0_MACADDH_MASK)

/*!
 * @brief ETH_MACALR0 Register Bit Definition
 */

#define ETH_MACALR0_MACADDL_SHIFT               (0)
#define ETH_MACALR0_MACADDL_MASK                (0xFFFFFFFFU << ETH_MACALR0_MACADDL_SHIFT)
#define ETH_MACALR0_MACADDL(x)                  (((uint32_t)(((uint32_t)(x)) << ETH_MACALR0_MACADDL_SHIFT)) & ETH_MACALR0_MACADDL_MASK)

/*!
 * @brief ETH_MACHTHR Register Bit Definition
 */

#define ETH_MACHTHR_MACHTABH_SHIFT              (0)
#define ETH_MACHTHR_MACHTABH_MASK               (0xFFFFFFFFU << ETH_MACHTHR_MACHTABH_SHIFT)
#define ETH_MACHTHR_MACHTABH(x)                 (((uint32_t)(((uint32_t)(x)) << ETH_MACHTHR_MACHTABH_SHIFT)) & ETH_MACHTHR_MACHTABH_MASK)

/*!
 * @brief ETH_MACHTLR Register Bit Definition
 */

#define ETH_MACHTLR_MACHTABL_SHIFT              (0)
#define ETH_MACHTLR_MACHTABL_MASK               (0xFFFFFFFFU << ETH_MACHTLR_MACHTABL_SHIFT)
#define ETH_MACHTLR_MACHTABL(x)                 (((uint32_t)(((uint32_t)(x)) << ETH_MACHTLR_MACHTABL_SHIFT)) & ETH_MACHTLR_MACHTABL_MASK)

/*!
 * @brief ETH_MACVLTR Register Bit Definition
 */

#define ETH_MACVLTR_VLANTAG_SHIFT               (0)
#define ETH_MACVLTR_VLANTAG_MASK                (0xFFFFU << ETH_MACVLTR_VLANTAG_SHIFT)
#define ETH_MACVLTR_VLANTAG(x)                  (((uint32_t)(((uint32_t)(x)) << ETH_MACVLTR_VLANTAG_SHIFT)) & ETH_MACVLTR_VLANTAG_MASK)

/*!
 * @brief ETH_DMAMDR Register Bit Definition
 */

#define ETH_DMAMDR_DTCOE_SHIFT                  (26)
#define ETH_DMAMDR_DTCOE_MASK                   (0x01U << ETH_DMAMDR_DTCOE_SHIFT)
#define ETH_DMAMDR_DTCOE(x)                     (((uint32_t)(((uint32_t)(x)) << ETH_DMAMDR_DTCOE_SHIFT)) & ETH_DMAMDR_DTCOE_MASK)

#define ETH_DMAMDR_RSF_SHIFT                    (25)
#define ETH_DMAMDR_RSF_MASK                     (0x01U << ETH_DMAMDR_RSF_SHIFT)
#define ETH_DMAMDR_RSF(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMAMDR_RSF_SHIFT)) & ETH_DMAMDR_RSF_MASK)

#define ETH_DMAMDR_DFRF_SHIFT                   (24)
#define ETH_DMAMDR_DFRF_MASK                    (0x01U << ETH_DMAMDR_DFRF_SHIFT)
#define ETH_DMAMDR_DFRF(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_DMAMDR_DFRF_SHIFT)) & ETH_DMAMDR_DFRF_MASK)

#define ETH_DMAMDR_TSF_SHIFT                    (21)
#define ETH_DMAMDR_TSF_MASK                     (0x01U << ETH_DMAMDR_TSF_SHIFT)
#define ETH_DMAMDR_TSF(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMAMDR_TSF_SHIFT)) & ETH_DMAMDR_TSF_MASK)

#define ETH_DMAMDR_FTF_SHIFT                    (20)
#define ETH_DMAMDR_FTF_MASK                     (0x01U << ETH_DMAMDR_FTF_SHIFT)
#define ETH_DMAMDR_FTF(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMAMDR_FTF_SHIFT)) & ETH_DMAMDR_FTF_MASK)

#define ETH_DMAMDR_TTC_SHIFT                    (14)
#define ETH_DMAMDR_TTC_MASK                     (0x7U << ETH_DMAMDR_TTC_SHIFT)
#define ETH_DMAMDR_TTC(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMAMDR_TTC_SHIFT)) & ETH_DMAMDR_TTC_MASK)

#define ETH_DMAMDR_STT_SHIFT                    (13)
#define ETH_DMAMDR_STT_MASK                     (0x01U << ETH_DMAMDR_STT_SHIFT)
#define ETH_DMAMDR_STT(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMAMDR_STT_SHIFT)) & ETH_DMAMDR_STT_MASK)

#define ETH_DMAMDR_FEF_SHIFT                    (7)
#define ETH_DMAMDR_FEF_MASK                     (0x01U << ETH_DMAMDR_FEF_SHIFT)
#define ETH_DMAMDR_FEF(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMAMDR_FEF_SHIFT)) & ETH_DMAMDR_FEF_MASK)

#define ETH_DMAMDR_FUF_SHIFT                    (6)
#define ETH_DMAMDR_FUF_MASK                     (0x01U << ETH_DMAMDR_FUF_SHIFT)
#define ETH_DMAMDR_FUF(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMAMDR_FUF_SHIFT)) & ETH_DMAMDR_FUF_MASK)

#define ETH_DMAMDR_DGF_SHIFT                    (5)
#define ETH_DMAMDR_DGF_MASK                     (0x01U << ETH_DMAMDR_DGF_SHIFT)
#define ETH_DMAMDR_DGF(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMAMDR_DGF_SHIFT)) & ETH_DMAMDR_DGF_MASK)

#define ETH_DMAMDR_RTC_SHIFT                    (3)
#define ETH_DMAMDR_RTC_MASK                     (0x3U << ETH_DMAMDR_RTC_SHIFT)
#define ETH_DMAMDR_RTC(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMAMDR_RTC_SHIFT)) & ETH_DMAMDR_RTC_MASK)

#define ETH_DMAMDR_OSF_SHIFT                    (2)
#define ETH_DMAMDR_OSF_MASK                     (0x01U << ETH_DMAMDR_OSF_SHIFT)
#define ETH_DMAMDR_OSF(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMAMDR_OSF_SHIFT)) & ETH_DMAMDR_OSF_MASK)

#define ETH_DMAMDR_SR_SHIFT                     (1)
#define ETH_DMAMDR_SR_MASK                      (0x01U << ETH_DMAMDR_SR_SHIFT)
#define ETH_DMAMDR_SR(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAMDR_SR_SHIFT)) & ETH_DMAMDR_SR_MASK)

/*!
 * @brief ETH_DMABSR Register Bit Definition
 */

#define ETH_DMABSR_ALL_SHIFT                    (25)
#define ETH_DMABSR_ALL_MASK                     (0x01U << ETH_DMABSR_ALL_SHIFT)
#define ETH_DMABSR_ALL(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMABSR_ALL_SHIFT)) & ETH_DMABSR_ALL_MASK)

#define ETH_DMABSR_FBST_SHIFT                   (16)
#define ETH_DMABSR_FBST_MASK                    (0x01U << ETH_DMABSR_FBST_SHIFT)
#define ETH_DMABSR_FBST(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_DMABSR_FBST_SHIFT)) & ETH_DMABSR_FBST_MASK)

#define ETH_DMABSR_FTPR_SHIFT                   (14)
#define ETH_DMABSR_FTPR_MASK                    (0x3U << ETH_DMABSR_FTPR_SHIFT)
#define ETH_DMABSR_FTPR(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_DMABSR_FTPR_SHIFT)) & ETH_DMABSR_FTPR_MASK)

#define ETH_DMABSR_PBL_SHIFT                    (8)
#define ETH_DMABSR_PBL_MASK                     (0x3FU << ETH_DMABSR_PBL_SHIFT)
#define ETH_DMABSR_PBL(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMABSR_PBL_SHIFT)) & ETH_DMABSR_PBL_MASK)

#define ETH_DMABSR_DSL_SHIFT                    (2)
#define ETH_DMABSR_DSL_MASK                     (0x1FU << ETH_DMABSR_DSL_SHIFT)
#define ETH_DMABSR_DSL(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMABSR_DSL_SHIFT)) & ETH_DMABSR_DSL_MASK)

#define ETH_DMABSR_DMAA_SHIFT                   (1)
#define ETH_DMABSR_DMAA_MASK                    (0x01U << ETH_DMABSR_DMAA_SHIFT)
#define ETH_DMABSR_DMAA(x)                      (((uint32_t)(((uint32_t)(x)) << ETH_DMABSR_DMAA_SHIFT)) & ETH_DMABSR_DMAA_MASK)

#define ETH_DMABSR_SR_SHIFT                     (0)
#define ETH_DMABSR_SR_MASK                      (0x01U << ETH_DMABSR_SR_SHIFT)
#define ETH_DMABSR_SR(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMABSR_SR_SHIFT)) & ETH_DMABSR_SR_MASK)

/*!
 * @brief ETH_DMAIR Register Bit Definition
 */

#define ETH_DMAIR_NIE_SHIFT                     (16)
#define ETH_DMAIR_NIE_MASK                      (0x01U << ETH_DMAIR_NIE_SHIFT)
#define ETH_DMAIR_NIE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_NIE_SHIFT)) & ETH_DMAIR_NIE_MASK)

#define ETH_DMAIR_AIE_SHIFT                     (15)
#define ETH_DMAIR_AIE_MASK                      (0x01U << ETH_DMAIR_AIE_SHIFT)
#define ETH_DMAIR_AIE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_AIE_SHIFT)) & ETH_DMAIR_AIE_MASK)

#define ETH_DMAIR_ERE_SHIFT                     (14)
#define ETH_DMAIR_ERE_MASK                      (0x01U << ETH_DMAIR_ERE_SHIFT)
#define ETH_DMAIR_ERE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_ERE_SHIFT)) & ETH_DMAIR_ERE_MASK)

#define ETH_DMAIR_FBE_SHIFT                     (13)
#define ETH_DMAIR_FBE_MASK                      (0x01U << ETH_DMAIR_FBE_SHIFT)
#define ETH_DMAIR_FBE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_FBE_SHIFT)) & ETH_DMAIR_FBE_MASK)

#define ETH_DMAIR_ETE_SHIFT                     (10)
#define ETH_DMAIR_ETE_MASK                      (0x01U << ETH_DMAIR_ETE_SHIFT)
#define ETH_DMAIR_ETE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_ETE_SHIFT)) & ETH_DMAIR_ETE_MASK)

#define ETH_DMAIR_RWE_SHIFT                     (9)
#define ETH_DMAIR_RWE_MASK                      (0x01U << ETH_DMAIR_RWE_SHIFT)
#define ETH_DMAIR_RWE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_RWE_SHIFT)) & ETH_DMAIR_RWE_MASK)

#define ETH_DMAIR_RSE_SHIFT                     (8)
#define ETH_DMAIR_RSE_MASK                      (0x01U << ETH_DMAIR_RSE_SHIFT)
#define ETH_DMAIR_RSE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_RSE_SHIFT)) & ETH_DMAIR_RSE_MASK)

#define ETH_DMAIR_RUE_SHIFT                     (7)
#define ETH_DMAIR_RUE_MASK                      (0x01U << ETH_DMAIR_RUE_SHIFT)
#define ETH_DMAIR_RUE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_RUE_SHIFT)) & ETH_DMAIR_RUE_MASK)

#define ETH_DMAIR_RIE_SHIFT                     (6)
#define ETH_DMAIR_RIE_MASK                      (0x01U << ETH_DMAIR_RIE_SHIFT)
#define ETH_DMAIR_RIE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_RIE_SHIFT)) & ETH_DMAIR_RIE_MASK)

#define ETH_DMAIR_UNE_SHIFT                     (5)
#define ETH_DMAIR_UNE_MASK                      (0x01U << ETH_DMAIR_UNE_SHIFT)
#define ETH_DMAIR_UNE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_UNE_SHIFT)) & ETH_DMAIR_UNE_MASK)

#define ETH_DMAIR_OVE_SHIFT                     (4)
#define ETH_DMAIR_OVE_MASK                      (0x01U << ETH_DMAIR_OVE_SHIFT)
#define ETH_DMAIR_OVE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_OVE_SHIFT)) & ETH_DMAIR_OVE_MASK)

#define ETH_DMAIR_TJE_SHIFT                     (3)
#define ETH_DMAIR_TJE_MASK                      (0x01U << ETH_DMAIR_TJE_SHIFT)
#define ETH_DMAIR_TJE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_TJE_SHIFT)) & ETH_DMAIR_TJE_MASK)

#define ETH_DMAIR_TUE_SHIFT                     (2)
#define ETH_DMAIR_TUE_MASK                      (0x01U << ETH_DMAIR_TUE_SHIFT)
#define ETH_DMAIR_TUE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_TUE_SHIFT)) & ETH_DMAIR_TUE_MASK)

#define ETH_DMAIR_TSE_SHIFT                     (1)
#define ETH_DMAIR_TSE_MASK                      (0x01U << ETH_DMAIR_TSE_SHIFT)
#define ETH_DMAIR_TSE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_TSE_SHIFT)) & ETH_DMAIR_TSE_MASK)

#define ETH_DMAIR_TIE_SHIFT                     (0)
#define ETH_DMAIR_TIE_MASK                      (0x01U << ETH_DMAIR_TIE_SHIFT)
#define ETH_DMAIR_TIE(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMAIR_TIE_SHIFT)) & ETH_DMAIR_TIE_MASK)

/*!
 * @brief ETH_DMASR Register Bit Definition
 */

#define ETH_DMASR_EBUS_SHIFT                    (23)
#define ETH_DMASR_EBUS_MASK                     (0x7U << ETH_DMASR_EBUS_SHIFT)
#define ETH_DMASR_EBUS(x)                       (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_EBUS_SHIFT)) & ETH_DMASR_EBUS_MASK)

#define ETH_DMASR_TPS_SHIFT                     (20)
#define ETH_DMASR_TPS_MASK                      (0x7U << ETH_DMASR_TPS_SHIFT)
#define ETH_DMASR_TPS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_TPS_SHIFT)) & ETH_DMASR_TPS_MASK)

#define ETH_DMASR_RPS_SHIFT                     (17)
#define ETH_DMASR_RPS_MASK                      (0x7U << ETH_DMASR_RPS_SHIFT)
#define ETH_DMASR_RPS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_RPS_SHIFT)) & ETH_DMASR_RPS_MASK)

#define ETH_DMASR_NIS_SHIFT                     (16)
#define ETH_DMASR_NIS_MASK                      (0x01U << ETH_DMASR_NIS_SHIFT)
#define ETH_DMASR_NIS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_NIS_SHIFT)) & ETH_DMASR_NIS_MASK)

#define ETH_DMASR_AIS_SHIFT                     (15)
#define ETH_DMASR_AIS_MASK                      (0x01U << ETH_DMASR_AIS_SHIFT)
#define ETH_DMASR_AIS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_AIS_SHIFT)) & ETH_DMASR_AIS_MASK)

#define ETH_DMASR_ERS_SHIFT                     (14)
#define ETH_DMASR_ERS_MASK                      (0x01U << ETH_DMASR_ERS_SHIFT)
#define ETH_DMASR_ERS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_ERS_SHIFT)) & ETH_DMASR_ERS_MASK)

#define ETH_DMASR_FBS_SHIFT                     (13)
#define ETH_DMASR_FBS_MASK                      (0x01U << ETH_DMASR_FBS_SHIFT)
#define ETH_DMASR_FBS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_FBS_SHIFT)) & ETH_DMASR_FBS_MASK)

#define ETH_DMASR_ETS_SHIFT                     (10)
#define ETH_DMASR_ETS_MASK                      (0x01U << ETH_DMASR_ETS_SHIFT)
#define ETH_DMASR_ETS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_ETS_SHIFT)) & ETH_DMASR_ETS_MASK)

#define ETH_DMASR_RWS_SHIFT                     (9)
#define ETH_DMASR_RWS_MASK                      (0x01U << ETH_DMASR_RWS_SHIFT)
#define ETH_DMASR_RWS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_RWS_SHIFT)) & ETH_DMASR_RWS_MASK)

#define ETH_DMASR_RSS_SHIFT                     (8)
#define ETH_DMASR_RSS_MASK                      (0x01U << ETH_DMASR_RSS_SHIFT)
#define ETH_DMASR_RSS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_RSS_SHIFT)) & ETH_DMASR_RSS_MASK)

#define ETH_DMASR_RUS_SHIFT                     (7)
#define ETH_DMASR_RUS_MASK                      (0x01U << ETH_DMASR_RUS_SHIFT)
#define ETH_DMASR_RUS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_RUS_SHIFT)) & ETH_DMASR_RUS_MASK)

#define ETH_DMASR_RIS_SHIFT                     (6)
#define ETH_DMASR_RIS_MASK                      (0x01U << ETH_DMASR_RIS_SHIFT)
#define ETH_DMASR_RIS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_RIS_SHIFT)) & ETH_DMASR_RIS_MASK)

#define ETH_DMASR_UNS_SHIFT                     (5)
#define ETH_DMASR_UNS_MASK                      (0x01U << ETH_DMASR_UNS_SHIFT)
#define ETH_DMASR_UNS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_UNS_SHIFT)) & ETH_DMASR_UNS_MASK)

#define ETH_DMASR_OVS_SHIFT                     (4)
#define ETH_DMASR_OVS_MASK                      (0x01U << ETH_DMASR_OVS_SHIFT)
#define ETH_DMASR_OVS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_OVS_SHIFT)) & ETH_DMASR_OVS_MASK)

#define ETH_DMASR_TJS_SHIFT                     (3)
#define ETH_DMASR_TJS_MASK                      (0x01U << ETH_DMASR_TJS_SHIFT)
#define ETH_DMASR_TJS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_TJS_SHIFT)) & ETH_DMASR_TJS_MASK)

#define ETH_DMASR_TUS_SHIFT                     (2)
#define ETH_DMASR_TUS_MASK                      (0x01U << ETH_DMASR_TUS_SHIFT)
#define ETH_DMASR_TUS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_TUS_SHIFT)) & ETH_DMASR_TUS_MASK)

#define ETH_DMASR_TSS_SHIFT                     (1)
#define ETH_DMASR_TSS_MASK                      (0x01U << ETH_DMASR_TSS_SHIFT)
#define ETH_DMASR_TSS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_TSS_SHIFT)) & ETH_DMASR_TSS_MASK)

#define ETH_DMASR_TIS_SHIFT                     (0)
#define ETH_DMASR_TIS_MASK                      (0x01U << ETH_DMASR_TIS_SHIFT)
#define ETH_DMASR_TIS(x)                        (((uint32_t)(((uint32_t)(x)) << ETH_DMASR_TIS_SHIFT)) & ETH_DMASR_TIS_MASK)

/*!
 * @brief ETH_DMAFLCR Register Bit Definition
 */

#define ETH_DMAFLCR_OVFF_SHIFT                  (28)
#define ETH_DMAFLCR_OVFF_MASK                   (0x01U << ETH_DMAFLCR_OVFF_SHIFT)
#define ETH_DMAFLCR_OVFF(x)                     (((uint32_t)(((uint32_t)(x)) << ETH_DMAFLCR_OVFF_SHIFT)) & ETH_DMAFLCR_OVFF_MASK)

#define ETH_DMAFLCR_OVFC_SHIFT                  (17)
#define ETH_DMAFLCR_OVFC_MASK                   (0x7FFU << ETH_DMAFLCR_OVFC_SHIFT)
#define ETH_DMAFLCR_OVFC(x)                     (((uint32_t)(((uint32_t)(x)) << ETH_DMAFLCR_OVFC_SHIFT)) & ETH_DMAFLCR_OVFC_MASK)

#define ETH_DMAFLCR_BNAF_SHIFT                  (16)
#define ETH_DMAFLCR_BNAF_MASK                   (0x01U << ETH_DMAFLCR_BNAF_SHIFT)
#define ETH_DMAFLCR_BNAF(x)                     (((uint32_t)(((uint32_t)(x)) << ETH_DMAFLCR_BNAF_SHIFT)) & ETH_DMAFLCR_BNAF_MASK)

#define ETH_DMAFLCR_BNAC_SHIFT                  (0)
#define ETH_DMAFLCR_BNAC_MASK                   (0xFFFFU << ETH_DMAFLCR_BNAC_SHIFT)
#define ETH_DMAFLCR_BNAC(x)                     (((uint32_t)(((uint32_t)(x)) << ETH_DMAFLCR_BNAC_SHIFT)) & ETH_DMAFLCR_BNAC_MASK)

/*!
 * @brief ETH_DMAWDTR Register Bit Definition
 */

#define ETH_DMAWDTR_RIWT_SHIFT                  (0)
#define ETH_DMAWDTR_RIWT_MASK                   (0xFFU << ETH_DMAWDTR_RIWT_SHIFT)
#define ETH_DMAWDTR_RIWT(x)                     (((uint32_t)(((uint32_t)(x)) << ETH_DMAWDTR_RIWT_SHIFT)) & ETH_DMAWDTR_RIWT_MASK)

/*!
 * @brief ETH_DMARXPDR Register Bit Definition
 */

#define ETH_DMARXPDR_RXPD_SHIFT                 (0)
#define ETH_DMARXPDR_RXPD_MASK                  (0xFFFFFFFFU << ETH_DMARXPDR_RXPD_SHIFT)
#define ETH_DMARXPDR_RXPD(x)                    (((uint32_t)(((uint32_t)(x)) << ETH_DMARXPDR_RXPD_SHIFT)) & ETH_DMARXPDR_RXPD_MASK)

/*!
 * @brief ETH_DMATXPDR Register Bit Definition
 */

#define ETH_DMATXPDR_TXPD_SHIFT                 (0)
#define ETH_DMATXPDR_TXPD_MASK                  (0xFFFFFFFFU << ETH_DMATXPDR_TXPD_SHIFT)
#define ETH_DMATXPDR_TXPD(x)                    (((uint32_t)(((uint32_t)(x)) << ETH_DMATXPDR_TXPD_SHIFT)) & ETH_DMATXPDR_TXPD_MASK)

/*!
 * @brief ETH_DMARXDSAR Register Bit Definition
 */

#define ETH_DMARXDSAR_RXDSA_SHIFT               (0)
#define ETH_DMARXDSAR_RXDSA_MASK                (0xFFFFFFFFU << ETH_DMARXDSAR_RXDSA_SHIFT)
#define ETH_DMARXDSAR_RXDSA(x)                  (((uint32_t)(((uint32_t)(x)) << ETH_DMARXDSAR_RXDSA_SHIFT)) & ETH_DMARXDSAR_RXDSA_MASK)

/*!
 * @brief ETH_DMATXDSAR Register Bit Definition
 */

#define ETH_DMATXDSAR_TXDSA_SHIFT               (0)
#define ETH_DMATXDSAR_TXDSA_MASK                (0xFFFFFFFFU << ETH_DMATXDSAR_TXDSA_SHIFT)
#define ETH_DMATXDSAR_TXDSA(x)                  (((uint32_t)(((uint32_t)(x)) << ETH_DMATXDSAR_TXDSA_SHIFT)) & ETH_DMATXDSAR_TXDSA_MASK)

/*!
 * @brief ETH_DMACUTRXDSAR Register Bit Definition
 */

#define ETH_DMACUTRXDSAR_CUTRXDSA_SHIFT         (0)
#define ETH_DMACUTRXDSAR_CUTRXDSA_MASK          (0xFFFFFFFFU << ETH_DMACUTRXDSAR_CUTRXDSA_SHIFT)
#define ETH_DMACUTRXDSAR_CUTRXDSA(x)            (((uint32_t)(((uint32_t)(x)) << ETH_DMACUTRXDSAR_CUTRXDSA_SHIFT)) & ETH_DMACUTRXDSAR_CUTRXDSA_MASK)

/*!
 * @brief ETH_DMACUTTXDSAR Register Bit Definition
 */

#define ETH_DMACUTTXDSAR_CUTTXDSA_SHIFT         (0)
#define ETH_DMACUTTXDSAR_CUTTXDSA_MASK          (0xFFFFFFFFU << ETH_DMACUTTXDSAR_CUTTXDSA_SHIFT)
#define ETH_DMACUTTXDSAR_CUTTXDSA(x)            (((uint32_t)(((uint32_t)(x)) << ETH_DMACUTTXDSAR_CUTTXDSA_SHIFT)) & ETH_DMACUTTXDSAR_CUTTXDSA_MASK)

/*!
 * @brief ETH_DMACUTRXBFAR Register Bit Definition
 */

#define ETH_DMACUTRXBFAR_CUTRXBUF_SHIFT         (0)
#define ETH_DMACUTRXBFAR_CUTRXBUF_MASK          (0xFFFFFFFFU << ETH_DMACUTRXBFAR_CUTRXBUF_SHIFT)
#define ETH_DMACUTRXBFAR_CUTRXBUF(x)            (((uint32_t)(((uint32_t)(x)) << ETH_DMACUTRXBFAR_CUTRXBUF_SHIFT)) & ETH_DMACUTRXBFAR_CUTRXBUF_MASK)

/*!
 * @brief ETH_DMACUTTXBFAR Register Bit Definition
 */

#define ETH_DMACUTTXBFAR_CUTTXBUF_SHIFT         (0)
#define ETH_DMACUTTXBFAR_CUTTXBUF_MASK          (0xFFFFFFFFU << ETH_DMACUTTXBFAR_CUTTXBUF_SHIFT)
#define ETH_DMACUTTXBFAR_CUTTXBUF(x)            (((uint32_t)(((uint32_t)(x)) << ETH_DMACUTTXBFAR_CUTTXBUF_SHIFT)) & ETH_DMACUTTXBFAR_CUTTXBUF_MASK)

/*!
 * @}
 */ /* end of group ETH_Register_Masks */
/******************************************************************************
 * ETH Instance
******************************************************************************/
#define ETH                             ((ETH_Type*)ETHERNET_BASE)

/*!
 * @}
 */ /* end of group ETH_Peripheral_Access_Layer */



/*!
 * @addtogroup SDIO_Peripheral_Access_Layer SDIO Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * SDIO Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t MMCCTRL;                                                       ///< MMCCTRL                                     offset: 0x00
    __IO uint32_t MMCIO;                                                         ///< MMCIO                                       offset: 0x04
    __IO uint32_t MMCBYTECNTL;                                                   ///< MMCBYTECNTL                                 offset: 0x08
    __IO uint32_t MMCTRBLOCKCNT;                                                 ///< MMCTRBLOCKCNT                               offset: 0x0C
    __IO uint32_t MMCCRCCTL;                                                     ///< MMCCRCCTL                                   offset: 0x10
    __IO uint32_t CMDCRC;                                                        ///< CMDCRC                                      offset: 0x14
    __IO uint32_t DATCRCL;                                                       ///< DATCRCL                                     offset: 0x18
    __IO uint32_t DATCRCH;                                                       ///< DATCRCH                                     offset: 0x1C
    __IO uint32_t MMCPORT;                                                       ///< MMCPORT                                     offset: 0x20
    __IO uint32_t MMCINTMASK;                                                    ///< MMCINTMASK                                  offset: 0x24
    __IO uint32_t CLRMMCINT;                                                     ///< CLRMMCINT                                   offset: 0x28
    __IO uint32_t MMCCARDSEL;                                                    ///< MMCCARDSEL                                  offset: 0x2C
    __IO uint32_t MMCSIQ;                                                        ///< MMCSIQ                                      offset: 0x30
    __IO uint32_t MMCIOMBCTL;                                                    ///< MMCIOMBCTL                                  offset: 0x34
    __IO uint32_t MMCBLOCKCNT;                                                   ///< MMCBLOCKCNT                                 offset: 0x38
    __IO uint32_t MMCTIMEOUTCNT;                                                 ///< MMCTIMEOUTCN                                offset: 0x3C
    __IO uint32_t CMDBUF[16];                                                    ///< CMDBUFx (0..15)                             offset: 0x40
    __IO uint32_t BUFCTL;                                                       ///< BUFCTL                                      offset: 0x80
    __IO uint32_t Reserved36[31];                                                ///< Reserved
    __IO uint32_t DATABUF[126];                                                  ///< DATABUF                                     offset: 0x100
} SDIO_Type;

/*******************************************************************************
 * SDIO Type
 ******************************************************************************/

/*!
 * @addtogroup SDIO_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief SDIO_MMCCTRL Register Bit Definition
 */

#define SDIO_MMCCTRL_RDWTEN_SHIFT              (10)
#define SDIO_MMCCTRL_RDWTEN_MASK               (0x01U << SDIO_MMCCTRL_RDWTEN_SHIFT)
#define SDIO_MMCCTRL_RDWTEN(x)                 (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCTRL_RDWTEN_SHIFT)) & SDIO_MMCCTRL_RDWTEN_MASK)

#define SDIO_MMCCTRL_INTEN_SHIFT               (9)
#define SDIO_MMCCTRL_INTEN_MASK                (0x01U << SDIO_MMCCTRL_INTEN_SHIFT)
#define SDIO_MMCCTRL_INTEN(x)                  (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCTRL_INTEN_SHIFT)) & SDIO_MMCCTRL_INTEN_MASK)

#define SDIO_MMCCTRL_MDEN_SHIFT                (8)
#define SDIO_MMCCTRL_MDEN_MASK                 (0x01U << SDIO_MMCCTRL_MDEN_SHIFT)
#define SDIO_MMCCTRL_MDEN(x)                   (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCTRL_MDEN_SHIFT)) & SDIO_MMCCTRL_MDEN_MASK)

#define SDIO_MMCCTRL_DATWT_SHIFT               (7)
#define SDIO_MMCCTRL_DATWT_MASK                (0x01U << SDIO_MMCCTRL_DATWT_SHIFT)
#define SDIO_MMCCTRL_DATWT(x)                  (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCTRL_DATWT_SHIFT)) & SDIO_MMCCTRL_DATWT_MASK)

#define SDIO_MMCCTRL_SELPTSM_SHIFT             (6)
#define SDIO_MMCCTRL_SELPTSM_MASK              (0x01U << SDIO_MMCCTRL_SELPTSM_SHIFT)
#define SDIO_MMCCTRL_SELPTSM(x)                (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCTRL_SELPTSM_SHIFT)) & SDIO_MMCCTRL_SELPTSM_MASK)

#define SDIO_MMCCTRL_CLKSP_SHIFT               (3)
#define SDIO_MMCCTRL_CLKSP_MASK                (0x7U << SDIO_MMCCTRL_CLKSP_SHIFT)
#define SDIO_MMCCTRL_CLKSP(x)                  (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCTRL_CLKSP_SHIFT)) & SDIO_MMCCTRL_CLKSP_MASK)

#define SDIO_MMCCTRL_OUTM_SHIFT                (2)
#define SDIO_MMCCTRL_OUTM_MASK                 (0x01U << SDIO_MMCCTRL_OUTM_SHIFT)
#define SDIO_MMCCTRL_OUTM(x)                   (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCTRL_OUTM_SHIFT)) & SDIO_MMCCTRL_OUTM_MASK)

#define SDIO_MMCCTRL_SELSM_SHIFT               (1)
#define SDIO_MMCCTRL_SELSM_MASK                (0x01U << SDIO_MMCCTRL_SELSM_SHIFT)
#define SDIO_MMCCTRL_SELSM(x)                  (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCTRL_SELSM_SHIFT)) & SDIO_MMCCTRL_SELSM_MASK)

#define SDIO_MMCCTRL_OPMSEL_SHIFT              (0)
#define SDIO_MMCCTRL_OPMSEL_MASK               (0x01U << SDIO_MMCCTRL_OPMSEL_SHIFT)
#define SDIO_MMCCTRL_OPMSEL(x)                 (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCTRL_OPMSEL_SHIFT)) & SDIO_MMCCTRL_OPMSEL_MASK)

/*!
 * @brief SDIO_MMCIO Register Bit Definition
 */

#define SDIO_MMCIO_CMDAF_SHIFT                 (9)
#define SDIO_MMCIO_CMDAF_MASK                  (0x01U << SDIO_MMCIO_CMDAF_SHIFT)
#define SDIO_MMCIO_CMDAF(x)                    (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIO_CMDAF_SHIFT)) & SDIO_MMCIO_CMDAF_MASK)

#define SDIO_MMCIO_CMDCH_SHIFT                 (8)
#define SDIO_MMCIO_CMDCH_MASK                  (0x01U << SDIO_MMCIO_CMDCH_SHIFT)
#define SDIO_MMCIO_CMDCH(x)                    (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIO_CMDCH_SHIFT)) & SDIO_MMCIO_CMDCH_MASK)

#define SDIO_MMCIO_AUTOCLKG_SHIFT              (7)
#define SDIO_MMCIO_AUTOCLKG_MASK               (0x01U << SDIO_MMCIO_AUTOCLKG_SHIFT)
#define SDIO_MMCIO_AUTOCLKG(x)                 (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIO_AUTOCLKG_SHIFT)) & SDIO_MMCIO_AUTOCLKG_MASK)

#define SDIO_MMCIO_ENRRESP_SHIFT               (6)
#define SDIO_MMCIO_ENRRESP_MASK                (0x01U << SDIO_MMCIO_ENRRESP_SHIFT)
#define SDIO_MMCIO_ENRRESP(x)                  (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIO_ENRRESP_SHIFT)) & SDIO_MMCIO_ENRRESP_MASK)

#define SDIO_MMCIO_PCLKG_SHIFT                 (5)
#define SDIO_MMCIO_PCLKG_MASK                  (0x01U << SDIO_MMCIO_PCLKG_SHIFT)
#define SDIO_MMCIO_PCLKG(x)                    (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIO_PCLKG_SHIFT)) & SDIO_MMCIO_PCLKG_MASK)

#define SDIO_MMCIO_CIDCSDRD_SHIFT              (4)
#define SDIO_MMCIO_CIDCSDRD_MASK               (0x01U << SDIO_MMCIO_CIDCSDRD_SHIFT)
#define SDIO_MMCIO_CIDCSDRD(x)                 (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIO_CIDCSDRD_SHIFT)) & SDIO_MMCIO_CIDCSDRD_MASK)

#define SDIO_MMCIO_RESPCMDSEL_SHIFT            (3)
#define SDIO_MMCIO_RESPCMDSEL_MASK             (0x01U << SDIO_MMCIO_RESPCMDSEL_SHIFT)
#define SDIO_MMCIO_RESPCMDSEL(x)               (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIO_RESPCMDSEL_SHIFT)) & SDIO_MMCIO_RESPCMDSEL_MASK)

#define SDIO_MMCIO_AUTOTR_SHIFT                (2)
#define SDIO_MMCIO_AUTOTR_MASK                 (0x01U << SDIO_MMCIO_AUTOTR_SHIFT)
#define SDIO_MMCIO_AUTOTR(x)                   (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIO_AUTOTR_SHIFT)) & SDIO_MMCIO_AUTOTR_MASK)

#define SDIO_MMCIO_TRANSFDIR_SHIFT             (1)
#define SDIO_MMCIO_TRANSFDIR_MASK              (0x01U << SDIO_MMCIO_TRANSFDIR_SHIFT)
#define SDIO_MMCIO_TRANSFDIR(x)                (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIO_TRANSFDIR_SHIFT)) & SDIO_MMCIO_TRANSFDIR_MASK)

#define SDIO_MMCIO_AUTODATTR_SHIFT             (0)
#define SDIO_MMCIO_AUTODATTR_MASK              (0x01U << SDIO_MMCIO_AUTODATTR_SHIFT)
#define SDIO_MMCIO_AUTODATTR(x)                (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIO_AUTODATTR_SHIFT)) & SDIO_MMCIO_AUTODATTR_MASK)

/*!
 * @brief SDIO_MMCBYTECNTL Register Bit Definition
 */

#define SDIO_MMCBYTECNTL_CNT_SHIFT             (0)
#define SDIO_MMCBYTECNTL_CNT_MASK              (0xFFFFU << SDIO_MMCBYTECNTL_CNT_SHIFT)
#define SDIO_MMCBYTECNTL_CNT(x)                (((uint32_t)(((uint32_t)(x)) << SDIO_MMCBYTECNTL_CNT_SHIFT)) & SDIO_MMCBYTECNTL_CNT_MASK)

/*!
 * @brief SDIO_MMCTRBLOCKCNT Register Bit Definition
 */

#define SDIO_MMCTRBLOCKCNT_CNT_SHIFT          (0)
#define SDIO_MMCTRBLOCKCNT_CNT_MASK           (0xFFFFU << SDIO_MMCTRBLOCKCNT_CNT_SHIFT)
#define SDIO_MMCTRBLOCKCNT_CNT(x)             (((uint32_t)(((uint32_t)(x)) << SDIO_MMCTRBLOCKCNT_CNT_SHIFT)) & SDIO_MMCTRBLOCKCNT_CNT_MASK)

/*!
 * @brief SDIO_MMCCRCCTL Register Bit Definition
 */

#define SDIO_MMCCRCCTL_CMDCRCEN_SHIFT          (7)
#define SDIO_MMCCRCCTL_CMDCRCEN_MASK           (0x01U << SDIO_MMCCRCCTL_CMDCRCEN_SHIFT)
#define SDIO_MMCCRCCTL_CMDCRCEN(x)             (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCRCCTL_CMDCRCEN_SHIFT)) & SDIO_MMCCRCCTL_CMDCRCEN_MASK)

#define SDIO_MMCCRCCTL_DATCRCEN_SHIFT          (6)
#define SDIO_MMCCRCCTL_DATCRCEN_MASK           (0x01U << SDIO_MMCCRCCTL_DATCRCEN_SHIFT)
#define SDIO_MMCCRCCTL_DATCRCEN(x)             (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCRCCTL_DATCRCEN_SHIFT)) & SDIO_MMCCRCCTL_DATCRCEN_MASK)

#define SDIO_MMCCRCCTL_ENCHK_SHIFT             (5)
#define SDIO_MMCCRCCTL_ENCHK_MASK              (0x01U << SDIO_MMCCRCCTL_ENCHK_SHIFT)
#define SDIO_MMCCRCCTL_ENCHK(x)                (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCRCCTL_ENCHK_SHIFT)) & SDIO_MMCCRCCTL_ENCHK_MASK)

#define SDIO_MMCCRCCTL_ENRDMB_SHIFT            (4)
#define SDIO_MMCCRCCTL_ENRDMB_MASK             (0x01U << SDIO_MMCCRCCTL_ENRDMB_SHIFT)
#define SDIO_MMCCRCCTL_ENRDMB(x)               (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCRCCTL_ENRDMB_SHIFT)) & SDIO_MMCCRCCTL_ENRDMB_MASK)

#define SDIO_MMCCRCCTL_DATCRCS_SHIFT           (2)
#define SDIO_MMCCRCCTL_DATCRCS_MASK            (0x3U << SDIO_MMCCRCCTL_DATCRCS_SHIFT)
#define SDIO_MMCCRCCTL_DATCRCS(x)              (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCRCCTL_DATCRCS_SHIFT)) & SDIO_MMCCRCCTL_DATCRCS_MASK)

#define SDIO_MMCCRCCTL_CMDCRCE_SHIFT           (1)
#define SDIO_MMCCRCCTL_CMDCRCE_MASK            (0x01U << SDIO_MMCCRCCTL_CMDCRCE_SHIFT)
#define SDIO_MMCCRCCTL_CMDCRCE(x)              (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCRCCTL_CMDCRCE_SHIFT)) & SDIO_MMCCRCCTL_CMDCRCE_MASK)

#define SDIO_MMCCRCCTL_DATCRCE_SHIFT           (0)
#define SDIO_MMCCRCCTL_DATCRCE_MASK            (0x01U << SDIO_MMCCRCCTL_DATCRCE_SHIFT)
#define SDIO_MMCCRCCTL_DATCRCE(x)              (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCRCCTL_DATCRCE_SHIFT)) & SDIO_MMCCRCCTL_DATCRCE_MASK)

/*!
 * @brief SDIO_CMDCRC Register Bit Definition
 */

#define SDIO_CMDCRC_CMDCRCV_SHIFT              (0)
#define SDIO_CMDCRC_CMDCRCV_MASK               (0x7FU << SDIO_CMDCRC_CMDCRCV_SHIFT)
#define SDIO_CMDCRC_CMDCRCV(x)                 (((uint32_t)(((uint32_t)(x)) << SDIO_CMDCRC_CMDCRCV_SHIFT)) & SDIO_CMDCRC_CMDCRCV_MASK)

/*!
 * @brief SDIO_DATCRCL Register Bit Definition
 */

#define SDIO_DATCRCL_DATCRCLV_SHIFT            (0)
#define SDIO_DATCRCL_DATCRCLV_MASK             (0x7FU << SDIO_DATCRCL_DATCRCLV_SHIFT)
#define SDIO_DATCRCL_DATCRCLV(x)               (((uint32_t)(((uint32_t)(x)) << SDIO_DATCRCL_DATCRCLV_SHIFT)) & SDIO_DATCRCL_DATCRCLV_MASK)

/*!
 * @brief SDIO_DATCRCH Register Bit Definition
 */

#define SDIO_DATCRCH_DATCRCHV_SHIFT            (0)
#define SDIO_DATCRCH_DATCRCHV_MASK             (0x7FU << SDIO_DATCRCH_DATCRCHV_SHIFT)
#define SDIO_DATCRCH_DATCRCHV(x)               (((uint32_t)(((uint32_t)(x)) << SDIO_DATCRCH_DATCRCHV_SHIFT)) & SDIO_DATCRCH_DATCRCHV_MASK)

/*!
 * @brief SDIO_MMCPORT Register Bit Definition
 */

#define SDIO_MMCPORT_PCLKS_SHIFT               (7)
#define SDIO_MMCPORT_PCLKS_MASK                (0x01U << SDIO_MMCPORT_PCLKS_SHIFT)
#define SDIO_MMCPORT_PCLKS(x)                  (((uint32_t)(((uint32_t)(x)) << SDIO_MMCPORT_PCLKS_SHIFT)) & SDIO_MMCPORT_PCLKS_MASK)

#define SDIO_MMCPORT_PCMDS_SHIFT               (6)
#define SDIO_MMCPORT_PCMDS_MASK                (0x01U << SDIO_MMCPORT_PCMDS_SHIFT)
#define SDIO_MMCPORT_PCMDS(x)                  (((uint32_t)(((uint32_t)(x)) << SDIO_MMCPORT_PCMDS_SHIFT)) & SDIO_MMCPORT_PCMDS_MASK)

#define SDIO_MMCPORT_PDATS_SHIFT               (5)
#define SDIO_MMCPORT_PDATS_MASK                (0x01U << SDIO_MMCPORT_PDATS_SHIFT)
#define SDIO_MMCPORT_PDATS(x)                  (((uint32_t)(((uint32_t)(x)) << SDIO_MMCPORT_PDATS_SHIFT)) & SDIO_MMCPORT_PDATS_MASK)

#define SDIO_MMCPORT_AUTONTEN_SHIFT            (4)
#define SDIO_MMCPORT_AUTONTEN_MASK             (0x01U << SDIO_MMCPORT_AUTONTEN_SHIFT)
#define SDIO_MMCPORT_AUTONTEN(x)               (((uint32_t)(((uint32_t)(x)) << SDIO_MMCPORT_AUTONTEN_SHIFT)) & SDIO_MMCPORT_AUTONTEN_MASK)

#define SDIO_MMCPORT_NTCR_SHIFT                (0)
#define SDIO_MMCPORT_NTCR_MASK                 (0xFU << SDIO_MMCPORT_NTCR_SHIFT)
#define SDIO_MMCPORT_NTCR(x)                   (((uint32_t)(((uint32_t)(x)) << SDIO_MMCPORT_NTCR_SHIFT)) & SDIO_MMCPORT_NTCR_MASK)

/*!
 * @brief SDIO_MMCINTMASK Register Bit Definition
 */

#define SDIO_MMCINTMASK_D1INTM_SHIFT          (8)
#define SDIO_MMCINTMASK_D1INTM_MASK           (0x01U << SDIO_MMCINTMASK_D1INTM_SHIFT)
#define SDIO_MMCINTMASK_D1INTM(x)             (((uint32_t)(((uint32_t)(x)) << SDIO_MMCINTMASK_D1INTM_SHIFT)) & SDIO_MMCINTMASK_D1INTM_MASK)

#define SDIO_MMCINTMASK_CRCINTM_SHIFT         (7)
#define SDIO_MMCINTMASK_CRCINTM_MASK          (0x01U << SDIO_MMCINTMASK_CRCINTM_SHIFT)
#define SDIO_MMCINTMASK_CRCINTM(x)            (((uint32_t)(((uint32_t)(x)) << SDIO_MMCINTMASK_CRCINTM_SHIFT)) & SDIO_MMCINTMASK_CRCINTM_MASK)

#define SDIO_MMCINTMASK_CRTINTM_SHIFT         (6)
#define SDIO_MMCINTMASK_CRTINTM_MASK          (0x01U << SDIO_MMCINTMASK_CRTINTM_SHIFT)
#define SDIO_MMCINTMASK_CRTINTM(x)            (((uint32_t)(((uint32_t)(x)) << SDIO_MMCINTMASK_CRTINTM_SHIFT)) & SDIO_MMCINTMASK_CRTINTM_MASK)

#define SDIO_MMCINTMASK_MBTINTM_SHIFT         (5)
#define SDIO_MMCINTMASK_MBTINTM_MASK          (0x01U << SDIO_MMCINTMASK_MBTINTM_SHIFT)
#define SDIO_MMCINTMASK_MBTINTM(x)            (((uint32_t)(((uint32_t)(x)) << SDIO_MMCINTMASK_MBTINTM_SHIFT)) & SDIO_MMCINTMASK_MBTINTM_MASK)

#define SDIO_MMCINTMASK_MBDINTM_SHIFT         (4)
#define SDIO_MMCINTMASK_MBDINTM_MASK          (0x01U << SDIO_MMCINTMASK_MBDINTM_SHIFT)
#define SDIO_MMCINTMASK_MBDINTM(x)            (((uint32_t)(((uint32_t)(x)) << SDIO_MMCINTMASK_MBDINTM_SHIFT)) & SDIO_MMCINTMASK_MBDINTM_MASK)

#define SDIO_MMCINTMASK_CMDEINT_SHIFT         (3)
#define SDIO_MMCINTMASK_CMDEINT_MASK          (0x01U << SDIO_MMCINTMASK_CMDEINT_SHIFT)
#define SDIO_MMCINTMASK_CMDEINT(x)            (((uint32_t)(((uint32_t)(x)) << SDIO_MMCINTMASK_CMDEINT_SHIFT)) & SDIO_MMCINTMASK_CMDEINT_MASK)

#define SDIO_MMCINTMASK_DATEINT_SHIFT         (2)
#define SDIO_MMCINTMASK_DATEINT_MASK          (0x01U << SDIO_MMCINTMASK_DATEINT_SHIFT)
#define SDIO_MMCINTMASK_DATEINT(x)            (((uint32_t)(((uint32_t)(x)) << SDIO_MMCINTMASK_DATEINT_SHIFT)) & SDIO_MMCINTMASK_DATEINT_MASK)

#define SDIO_MMCINTMASK_DATDINT_SHIFT         (1)
#define SDIO_MMCINTMASK_DATDINT_MASK          (0x01U << SDIO_MMCINTMASK_DATDINT_SHIFT)
#define SDIO_MMCINTMASK_DATDINT(x)            (((uint32_t)(((uint32_t)(x)) << SDIO_MMCINTMASK_DATDINT_SHIFT)) & SDIO_MMCINTMASK_DATDINT_MASK)

#define SDIO_MMCINTMASK_CMDDINT_SHIFT         (0)
#define SDIO_MMCINTMASK_CMDDINT_MASK          (0x01U << SDIO_MMCINTMASK_CMDDINT_SHIFT)
#define SDIO_MMCINTMASK_CMDDINT(x)            (((uint32_t)(((uint32_t)(x)) << SDIO_MMCINTMASK_CMDDINT_SHIFT)) & SDIO_MMCINTMASK_CMDDINT_MASK)

/*!
 * @brief SDIO_CLRMMCINT Register Bit Definition
 */

#define SDIO_CLRMMCINT_D1MC_SHIFT             (8)
#define SDIO_CLRMMCINT_D1MC_MASK              (0x01U << SDIO_CLRMMCINT_D1MC_SHIFT)
#define SDIO_CLRMMCINT_D1MC(x)                (((uint32_t)(((uint32_t)(x)) << SDIO_CLRMMCINT_D1MC_SHIFT)) & SDIO_CLRMMCINT_D1MC_MASK)

#define SDIO_CLRMMCINT_CRCEMC_SHIFT           (7)
#define SDIO_CLRMMCINT_CRCEMC_MASK            (0x01U << SDIO_CLRMMCINT_CRCEMC_SHIFT)
#define SDIO_CLRMMCINT_CRCEMC(x)              (((uint32_t)(((uint32_t)(x)) << SDIO_CLRMMCINT_CRCEMC_SHIFT)) & SDIO_CLRMMCINT_CRCEMC_MASK)

#define SDIO_CLRMMCINT_CRNTMC_SHIFT           (6)
#define SDIO_CLRMMCINT_CRNTMC_MASK            (0x01U << SDIO_CLRMMCINT_CRNTMC_SHIFT)
#define SDIO_CLRMMCINT_CRNTMC(x)              (((uint32_t)(((uint32_t)(x)) << SDIO_CLRMMCINT_CRNTMC_SHIFT)) & SDIO_CLRMMCINT_CRNTMC_MASK)

#define SDIO_CLRMMCINT_MBTMC_SHIFT            (5)
#define SDIO_CLRMMCINT_MBTMC_MASK             (0x01U << SDIO_CLRMMCINT_MBTMC_SHIFT)
#define SDIO_CLRMMCINT_MBTMC(x)               (((uint32_t)(((uint32_t)(x)) << SDIO_CLRMMCINT_MBTMC_SHIFT)) & SDIO_CLRMMCINT_MBTMC_MASK)

#define SDIO_CLRMMCINT_MBDMC_SHIFT            (4)
#define SDIO_CLRMMCINT_MBDMC_MASK             (0x01U << SDIO_CLRMMCINT_MBDMC_SHIFT)
#define SDIO_CLRMMCINT_MBDMC(x)               (((uint32_t)(((uint32_t)(x)) << SDIO_CLRMMCINT_MBDMC_SHIFT)) & SDIO_CLRMMCINT_MBDMC_MASK)

#define SDIO_CLRMMCINT_CMDEMC_SHIFT           (3)
#define SDIO_CLRMMCINT_CMDEMC_MASK            (0x01U << SDIO_CLRMMCINT_CMDEMC_SHIFT)
#define SDIO_CLRMMCINT_CMDEMC(x)              (((uint32_t)(((uint32_t)(x)) << SDIO_CLRMMCINT_CMDEMC_SHIFT)) & SDIO_CLRMMCINT_CMDEMC_MASK)

#define SDIO_CLRMMCINT_DATEMC_SHIFT           (2)
#define SDIO_CLRMMCINT_DATEMC_MASK            (0x01U << SDIO_CLRMMCINT_DATEMC_SHIFT)
#define SDIO_CLRMMCINT_DATEMC(x)              (((uint32_t)(((uint32_t)(x)) << SDIO_CLRMMCINT_DATEMC_SHIFT)) & SDIO_CLRMMCINT_DATEMC_MASK)

#define SDIO_CLRMMCINT_DATDMC_SHIFT           (1)
#define SDIO_CLRMMCINT_DATDMC_MASK            (0x01U << SDIO_CLRMMCINT_DATDMC_SHIFT)
#define SDIO_CLRMMCINT_DATDMC(x)              (((uint32_t)(((uint32_t)(x)) << SDIO_CLRMMCINT_DATDMC_SHIFT)) & SDIO_CLRMMCINT_DATDMC_MASK)

#define SDIO_CLRMMCINT_CMDDMC_SHIFT           (0)
#define SDIO_CLRMMCINT_CMDDMC_MASK            (0x01U << SDIO_CLRMMCINT_CMDDMC_SHIFT)
#define SDIO_CLRMMCINT_CMDDMC(x)              (((uint32_t)(((uint32_t)(x)) << SDIO_CLRMMCINT_CMDDMC_SHIFT)) & SDIO_CLRMMCINT_CMDDMC_MASK)

/*!
 * @brief SDIO_MMCCARDSEL Register Bit Definition
 */

#define SDIO_MMCCARDSEL_CTREN_SHIFT            (7)
#define SDIO_MMCCARDSEL_CTREN_MASK             (0x01U << SDIO_MMCCARDSEL_CTREN_SHIFT)
#define SDIO_MMCCARDSEL_CTREN(x)               (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCARDSEL_CTREN_SHIFT)) & SDIO_MMCCARDSEL_CTREN_MASK)

#define SDIO_MMCCARDSEL_ENPCLK_SHIFT           (6)
#define SDIO_MMCCARDSEL_ENPCLK_MASK            (0x01U << SDIO_MMCCARDSEL_ENPCLK_SHIFT)
#define SDIO_MMCCARDSEL_ENPCLK(x)              (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCARDSEL_ENPCLK_SHIFT)) & SDIO_MMCCARDSEL_ENPCLK_MASK)

#define SDIO_MMCCARDSEL_TSCALE_SHIFT           (0)
#define SDIO_MMCCARDSEL_TSCALE_MASK            (0x3FU << SDIO_MMCCARDSEL_TSCALE_SHIFT)
#define SDIO_MMCCARDSEL_TSCALE(x)              (((uint32_t)(((uint32_t)(x)) << SDIO_MMCCARDSEL_TSCALE_SHIFT)) & SDIO_MMCCARDSEL_TSCALE_MASK)

/*!
 * @brief SDIO_MMCSIQ Register Bit Definition
 */

#define SDIO_MMCSIQ_PCMDS_SHIFT                (7)
#define SDIO_MMCSIQ_PCMDS_MASK                 (0x01U << SDIO_MMCSIQ_PCMDS_SHIFT)
#define SDIO_MMCSIQ_PCMDS(x)                   (((uint32_t)(((uint32_t)(x)) << SDIO_MMCSIQ_PCMDS_SHIFT)) & SDIO_MMCSIQ_PCMDS_MASK)

#define SDIO_MMCSIQ_CRCSTATUS_SHIFT            (4)
#define SDIO_MMCSIQ_CRCSTATUS_MASK             (0x7U << SDIO_MMCSIQ_CRCSTATUS_SHIFT)
#define SDIO_MMCSIQ_CRCSTATUS(x)               (((uint32_t)(((uint32_t)(x)) << SDIO_MMCSIQ_CRCSTATUS_SHIFT)) & SDIO_MMCSIQ_CRCSTATUS_MASK)

#define SDIO_MMCSIQ_PDAT3S_SHIFT               (3)
#define SDIO_MMCSIQ_PDAT3S_MASK                (0x01U << SDIO_MMCSIQ_PDAT3S_SHIFT)
#define SDIO_MMCSIQ_PDAT3S(x)                  (((uint32_t)(((uint32_t)(x)) << SDIO_MMCSIQ_PDAT3S_SHIFT)) & SDIO_MMCSIQ_PDAT3S_MASK)

#define SDIO_MMCSIQ_PDAT2S_SHIFT               (2)
#define SDIO_MMCSIQ_PDAT2S_MASK                (0x01U << SDIO_MMCSIQ_PDAT2S_SHIFT)
#define SDIO_MMCSIQ_PDAT2S(x)                  (((uint32_t)(((uint32_t)(x)) << SDIO_MMCSIQ_PDAT2S_SHIFT)) & SDIO_MMCSIQ_PDAT2S_MASK)

#define SDIO_MMCSIQ_PDAT1S_SHIFT               (1)
#define SDIO_MMCSIQ_PDAT1S_MASK                (0x01U << SDIO_MMCSIQ_PDAT1S_SHIFT)
#define SDIO_MMCSIQ_PDAT1S(x)                  (((uint32_t)(((uint32_t)(x)) << SDIO_MMCSIQ_PDAT1S_SHIFT)) & SDIO_MMCSIQ_PDAT1S_MASK)

#define SDIO_MMCSIQ_PDAT0S_SHIFT               (0)
#define SDIO_MMCSIQ_PDAT0S_MASK                (0x01U << SDIO_MMCSIQ_PDAT0S_SHIFT)
#define SDIO_MMCSIQ_PDAT0S(x)                  (((uint32_t)(((uint32_t)(x)) << SDIO_MMCSIQ_PDAT0S_SHIFT)) & SDIO_MMCSIQ_PDAT0S_MASK)

/*!
 * @brief SDIO_MMCIOMBCTL Register Bit Definition
 */

#define SDIO_MMCIOMBCTL_NTSSEL_SHIFT          (6)
#define SDIO_MMCIOMBCTL_NTSSEL_MASK           (0x3U << SDIO_MMCIOMBCTL_NTSSEL_SHIFT)
#define SDIO_MMCIOMBCTL_NTSSEL(x)             (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIOMBCTL_NTSSEL_SHIFT)) & SDIO_MMCIOMBCTL_NTSSEL_MASK)

#define SDIO_MMCIOMBCTL_BTSSEL_SHIFT          (4)
#define SDIO_MMCIOMBCTL_BTSSEL_MASK           (0x3U << SDIO_MMCIOMBCTL_BTSSEL_SHIFT)
#define SDIO_MMCIOMBCTL_BTSSEL(x)             (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIOMBCTL_BTSSEL_SHIFT)) & SDIO_MMCIOMBCTL_BTSSEL_MASK)

#define SDIO_MMCIOMBCTL_PCLKP_SHIFT           (3)
#define SDIO_MMCIOMBCTL_PCLKP_MASK            (0x01U << SDIO_MMCIOMBCTL_PCLKP_SHIFT)
#define SDIO_MMCIOMBCTL_PCLKP(x)              (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIOMBCTL_PCLKP_SHIFT)) & SDIO_MMCIOMBCTL_PCLKP_MASK)

#define SDIO_MMCIOMBCTL_PAUTOTR_SHIFT         (2)
#define SDIO_MMCIOMBCTL_PAUTOTR_MASK          (0x01U << SDIO_MMCIOMBCTL_PAUTOTR_SHIFT)
#define SDIO_MMCIOMBCTL_PAUTOTR(x)            (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIOMBCTL_PAUTOTR_SHIFT)) & SDIO_MMCIOMBCTL_PAUTOTR_MASK)

#define SDIO_MMCIOMBCTL_SMBDTD_SHIFT          (1)
#define SDIO_MMCIOMBCTL_SMBDTD_MASK           (0x01U << SDIO_MMCIOMBCTL_SMBDTD_SHIFT)
#define SDIO_MMCIOMBCTL_SMBDTD(x)             (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIOMBCTL_SMBDTD_SHIFT)) & SDIO_MMCIOMBCTL_SMBDTD_MASK)

#define SDIO_MMCIOMBCTL_SPMBDTR_SHIFT         (0)
#define SDIO_MMCIOMBCTL_SPMBDTR_MASK          (0x01U << SDIO_MMCIOMBCTL_SPMBDTR_SHIFT)
#define SDIO_MMCIOMBCTL_SPMBDTR(x)            (((uint32_t)(((uint32_t)(x)) << SDIO_MMCIOMBCTL_SPMBDTR_SHIFT)) & SDIO_MMCIOMBCTL_SPMBDTR_MASK)

/*!
 * @brief SDIO_MMCBLOCKCNT Register Bit Definition
 */

#define SDIO_MMCBLOCKCNT_BCNT_SHIFT            (0)
#define SDIO_MMCBLOCKCNT_BCNT_MASK             (0xFFFFU << SDIO_MMCBLOCKCNT_BCNT_SHIFT)
#define SDIO_MMCBLOCKCNT_BCNT(x)               (((uint32_t)(((uint32_t)(x)) << SDIO_MMCBLOCKCNT_BCNT_SHIFT)) & SDIO_MMCBLOCKCNT_BCNT_MASK)

/*!
 * @brief SDIO_MMCTIMEOUTCNT Register Bit Definition
 */

#define SDIO_MMCTIMEOUTCNT_DTCNT_SHIFT         (0)
#define SDIO_MMCTIMEOUTCNT_DTCNT_MASK          (0xFFU << SDIO_MMCTIMEOUTCNT_DTCNT_SHIFT)
#define SDIO_MMCTIMEOUTCNT_DTCNT(x)            (((uint32_t)(((uint32_t)(x)) << SDIO_MMCTIMEOUTCNT_DTCNT_SHIFT)) & SDIO_MMCTIMEOUTCNT_DTCNT_MASK)

/*!
 * @brief SDIO_CMDBUF Register Bit Definition
 */

#define SDIO_CMDBUF_DAT_SHIFT                  (0)
#define SDIO_CMDBUF_DAT_MASK                   (0xFFU << SDIO_CMDBUF_DAT_SHIFT)
#define SDIO_CMDBUF_DAT(x)                     (((uint32_t)(((uint32_t)(x)) << SDIO_CMDBUF_DAT_SHIFT)) & SDIO_CMDBUF_DAT_MASK)

/*!
 * @brief SDIO_BUFCTL Register Bit Definition
 */

#define SDIO_BUFCTL_DBFEN_SHIFT                (15)
#define SDIO_BUFCTL_DBFEN_MASK                 (0x01U << SDIO_BUFCTL_DBFEN_SHIFT)
#define SDIO_BUFCTL_DBFEN(x)                   (((uint32_t)(((uint32_t)(x)) << SDIO_BUFCTL_DBFEN_SHIFT)) & SDIO_BUFCTL_DBFEN_MASK)

#define SDIO_BUFCTL_DRM_SHIFT                  (14)
#define SDIO_BUFCTL_DRM_MASK                   (0x01U << SDIO_BUFCTL_DRM_SHIFT)
#define SDIO_BUFCTL_DRM(x)                     (((uint32_t)(((uint32_t)(x)) << SDIO_BUFCTL_DRM_SHIFT)) & SDIO_BUFCTL_DRM_MASK)

#define SDIO_BUFCTL_DFIFOSM_SHIFT              (12)
#define SDIO_BUFCTL_DFIFOSM_MASK               (0x01U << SDIO_BUFCTL_DFIFOSM_SHIFT)
#define SDIO_BUFCTL_DFIFOSM(x)                 (((uint32_t)(((uint32_t)(x)) << SDIO_BUFCTL_DFIFOSM_SHIFT)) & SDIO_BUFCTL_DFIFOSM_MASK)

#define SDIO_BUFCTL_SBAD_SHIFT                 (11)
#define SDIO_BUFCTL_SBAD_MASK                  (0x01U << SDIO_BUFCTL_SBAD_SHIFT)
#define SDIO_BUFCTL_SBAD(x)                    (((uint32_t)(((uint32_t)(x)) << SDIO_BUFCTL_SBAD_SHIFT)) & SDIO_BUFCTL_SBAD_MASK)

#define SDIO_BUFCTL_DMAHEN_SHIFT               (10)
#define SDIO_BUFCTL_DMAHEN_MASK                (0x01U << SDIO_BUFCTL_DMAHEN_SHIFT)
#define SDIO_BUFCTL_DMAHEN(x)                  (((uint32_t)(((uint32_t)(x)) << SDIO_BUFCTL_DMAHEN_SHIFT)) & SDIO_BUFCTL_DMAHEN_MASK)

#define SDIO_BUFCTL_DBML_SHIFT                 (2)
#define SDIO_BUFCTL_DBML_MASK                  (0xFFU << SDIO_BUFCTL_DBML_SHIFT)
#define SDIO_BUFCTL_DBML(x)                    (((uint32_t)(((uint32_t)(x)) << SDIO_BUFCTL_DBML_SHIFT)) & SDIO_BUFCTL_DBML_MASK)

#define SDIO_BUFCTL_DBE_SHIFT                  (1)
#define SDIO_BUFCTL_DBE_MASK                   (0x01U << SDIO_BUFCTL_DBE_SHIFT)
#define SDIO_BUFCTL_DBE(x)                     (((uint32_t)(((uint32_t)(x)) << SDIO_BUFCTL_DBE_SHIFT)) & SDIO_BUFCTL_DBE_MASK)

#define SDIO_BUFCTL_DBF_SHIFT                  (0)
#define SDIO_BUFCTL_DBF_MASK                   (0x01U << SDIO_BUFCTL_DBF_SHIFT)
#define SDIO_BUFCTL_DBF(x)                     (((uint32_t)(((uint32_t)(x)) << SDIO_BUFCTL_DBF_SHIFT)) & SDIO_BUFCTL_DBF_MASK)

/*!
 * @brief SDIO_DATABUF Register Bit Definition
 */

#define SDIO_DATABUF_DB_SHIFT                  (0)
#define SDIO_DATABUF_DB_MASK                   (0xFFFFFFFFU << SDIO_DATABUF_DB_SHIFT)
#define SDIO_DATABUF_DB(x)                     (((uint32_t)(((uint32_t)(x)) << SDIO_DATABUF_DB_SHIFT)) & SDIO_DATABUF_DB_MASK)

/*!
 * @}
 */ /* end of group SDIO_Register_Masks */
/******************************************************************************
 * SDIO Instance
******************************************************************************/
#define SDIO                                ((SDIO_Type*)SDIO_BASE)

/*!
 * @}
 */ /* end of group SDIO_Peripheral_Access_Layer */



/*!
 * @addtogroup FSMC_Peripheral_Access_Layer FSMC Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * FSMC Type
 ******************************************************************************/
#define FSMC_SMTMGR_REG_NUM 3u /*!< the number of FSMC SMTMGR. */
typedef struct {
    __IO uint32_t Reserved37[21];                                                 ///< Reserved
    __IO uint32_t SMSKR0;                                                         ///< Memory mask register                         offset: 0x54
    __IO uint32_t Reserved38[15];                                                 ///< Reserved
    __IO uint32_t SMTMGRSET[FSMC_SMTMGR_REG_NUM];                                 ///< Memory timing register 0                     offset: 0x94
    __IO uint32_t Reserved39[1];                                                  ///< Reserved
    __IO uint32_t SMCTLR;                                                         ///< Memory control register                      offset: 0xA4
} FSMC_Type;

/*******************************************************************************
 * FSMC Type
 ******************************************************************************/

/*!
 * @addtogroup FSMC_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief FSMC_SMSKR0 Register Bit Definition
 */

#define FSMC_SMSKR0_REGSELECT_SHIFT             (8)
#define FSMC_SMSKR0_REGSELECT_MASK              (0x7U << FSMC_SMSKR0_REGSELECT_SHIFT)
#define FSMC_SMSKR0_REGSELECT(x)                (((uint32_t)(((uint32_t)(x)) << FSMC_SMSKR0_REGSELECT_SHIFT)) & FSMC_SMSKR0_REGSELECT_MASK)

#define FSMC_SMSKR0_MEMTYPE_SHIFT               (5)
#define FSMC_SMSKR0_MEMTYPE_MASK                (0x7U << FSMC_SMSKR0_MEMTYPE_SHIFT)
#define FSMC_SMSKR0_MEMTYPE(x)                  (((uint32_t)(((uint32_t)(x)) << FSMC_SMSKR0_MEMTYPE_SHIFT)) & FSMC_SMSKR0_MEMTYPE_MASK)

#define FSMC_SMSKR0_MEMSIZE_SHIFT               (0)
#define FSMC_SMSKR0_MEMSIZE_MASK                (0x1FU << FSMC_SMSKR0_MEMSIZE_SHIFT)
#define FSMC_SMSKR0_MEMSIZE(x)                  (((uint32_t)(((uint32_t)(x)) << FSMC_SMSKR0_MEMSIZE_SHIFT)) & FSMC_SMSKR0_MEMSIZE_MASK)

/*!
 * @brief FSMC_SMTMGRSET Register Bit Definition
 */

#define FSMC_SMTMGRSET_SMREADPIPE_SHIFT         (28)
#define FSMC_SMTMGRSET_SMREADPIPE_MASK          (0x3U << FSMC_SMTMGRSET_SMREADPIPE_SHIFT)
#define FSMC_SMTMGRSET_SMREADPIPE(x)            (((uint32_t)(((uint32_t)(x)) << FSMC_SMTMGRSET_SMREADPIPE_SHIFT)) & FSMC_SMTMGRSET_SMREADPIPE_MASK)

#define FSMC_SMTMGRSET_READYMODE_SHIFT          (26)
#define FSMC_SMTMGRSET_READYMODE_MASK           (0x01U << FSMC_SMTMGRSET_READYMODE_SHIFT)
#define FSMC_SMTMGRSET_READYMODE(x)             (((uint32_t)(((uint32_t)(x)) << FSMC_SMTMGRSET_READYMODE_SHIFT)) & FSMC_SMTMGRSET_READYMODE_MASK)

#define FSMC_SMTMGRSET_TWP_SHIFT                (10)
#define FSMC_SMTMGRSET_TWP_MASK                 (0x3FU << FSMC_SMTMGRSET_TWP_SHIFT)
#define FSMC_SMTMGRSET_TWP(x)                   (((uint32_t)(((uint32_t)(x)) << FSMC_SMTMGRSET_TWP_SHIFT)) & FSMC_SMTMGRSET_TWP_MASK)

#define FSMC_SMTMGRSET_TWR_SHIFT                (8)
#define FSMC_SMTMGRSET_TWR_MASK                 (0x3U << FSMC_SMTMGRSET_TWR_SHIFT)
#define FSMC_SMTMGRSET_TWR(x)                   (((uint32_t)(((uint32_t)(x)) << FSMC_SMTMGRSET_TWR_SHIFT)) & FSMC_SMTMGRSET_TWR_MASK)

#define FSMC_SMTMGRSET_TAS_SHIFT                (6)
#define FSMC_SMTMGRSET_TAS_MASK                 (0x3U << FSMC_SMTMGRSET_TAS_SHIFT)
#define FSMC_SMTMGRSET_TAS(x)                   (((uint32_t)(((uint32_t)(x)) << FSMC_SMTMGRSET_TAS_SHIFT)) & FSMC_SMTMGRSET_TAS_MASK)

#define FSMC_SMTMGRSET_TRC_SHIFT                (0)
#define FSMC_SMTMGRSET_TRC_MASK                 (0x3FU << FSMC_SMTMGRSET_TRC_SHIFT)
#define FSMC_SMTMGRSET_TRC(x)                   (((uint32_t)(((uint32_t)(x)) << FSMC_SMTMGRSET_TRC_SHIFT)) & FSMC_SMTMGRSET_TRC_MASK)


/*!
 * @brief FSMC_SMCTLR Register Bit Definition
 */

#define FSMC_SMCTLR_SMDATAWIDTHSET2_SHIFT       (13)
#define FSMC_SMCTLR_SMDATAWIDTHSET2_MASK        (0x7U << FSMC_SMCTLR_SMDATAWIDTHSET2_SHIFT)
#define FSMC_SMCTLR_SMDATAWIDTHSET2(x)          (((uint32_t)(((uint32_t)(x)) << FSMC_SMCTLR_SMDATAWIDTHSET2_SHIFT)) & FSMC_SMCTLR_SMDATAWIDTHSET2_MASK)

#define FSMC_SMCTLR_SMDATAWIDTHSET1_SHIFT       (10)
#define FSMC_SMCTLR_SMDATAWIDTHSET1_MASK        (0x7U << FSMC_SMCTLR_SMDATAWIDTHSET1_SHIFT)
#define FSMC_SMCTLR_SMDATAWIDTHSET1(x)          (((uint32_t)(((uint32_t)(x)) << FSMC_SMCTLR_SMDATAWIDTHSET1_SHIFT)) & FSMC_SMCTLR_SMDATAWIDTHSET1_MASK)

#define FSMC_SMCTLR_SMDATAWIDTHSET0_SHIFT       (7)
#define FSMC_SMCTLR_SMDATAWIDTHSET0_MASK        (0x7U << FSMC_SMCTLR_SMDATAWIDTHSET0_SHIFT)
#define FSMC_SMCTLR_SMDATAWIDTHSET0(x)          (((uint32_t)(((uint32_t)(x)) << FSMC_SMCTLR_SMDATAWIDTHSET0_SHIFT)) & FSMC_SMCTLR_SMDATAWIDTHSET0_MASK)

#define FSMC_SMCTLR_FLASHRP_SHIFT               (0)
#define FSMC_SMCTLR_FLASHRP_MASK                (0x01U << FSMC_SMCTLR_FLASHRP_SHIFT)
#define FSMC_SMCTLR_FLASHRP(x)                  (((uint32_t)(((uint32_t)(x)) << FSMC_SMCTLR_FLASHRP_SHIFT)) & FSMC_SMCTLR_FLASHRP_MASK)

/*!
 * @}
 */ /* end of group FSMC_Register_Masks */
/******************************************************************************
 * FSMC Instance
******************************************************************************/
#define FSMC                                ((FSMC_Type*)FSMC_BASE)

/*!
 * @}
 */ /* end of group FSMC_Peripheral_Access_Layer */



/*!
 * @addtogroup ADC_Peripheral_Access_Layer ADC Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * ADC Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t ADDATA;                                                         ///< A/D data register                            offset: 0x00
    __IO uint32_t ADCFG;                                                          ///< A/D configuration register                   offset: 0x04
    __IO uint32_t ADCR;                                                           ///< A/D control register                         offset: 0x08
    __IO uint32_t ADCHS;                                                          ///< A/D channel selection register               offset: 0x0C
    __IO uint32_t ADCMPR;                                                         ///< A/D window compare register                  offset: 0x10
    __IO uint32_t ADSTA;                                                          ///< A/D status register                          offset: 0x14
    __IO uint32_t ADDR[16];                                                       ///< A/D data register                            offset: 0x18
    __IO uint32_t ADSTAEXT;                                                       ///< A/D extended status register                 offset: 0x58
    __IO uint32_t CHANY0;                                                         ///< A/D any channel channel selection register 0 offset: 0x5C
    __IO uint32_t CHANY1;                                                         ///< A/D any channel channel selection register 1 offset: 0x60
    __IO uint32_t ANYCFG;                                                         ///< A/D arbitrary channel configuration register offset: 0x64
    __IO uint32_t ANYCR;                                                          ///< A/D arbitrary channel control register       offset: 0x68
    __IO uint32_t Reserved41[1];                                                  ///< Reserved
    __IO uint32_t SMPR1;                                                          ///< A/D sampling configuration register 1        offset: 0x70
    __IO uint32_t SMPR2;                                                          ///< A/D sampling configuration register 2        offset: 0x74
    __IO uint32_t Reserved42[1];                                                  ///< Reserved
    __IO uint32_t JOFR[4];                                                        ///< A/D injection channel data compensation registeroffset: 0x7C
    __IO uint32_t JSQR;                                                           ///< A/D injection channel continuous register    offset: 0x8C
    __IO uint32_t JADDATA;                                                        ///< A/D injection channel data register          offset: 0x90
    __IO uint32_t Reserved44[7];                                                  ///< Reserved
    __IO uint32_t JDR[4];                                                         ///< A/D injection channel data register          offset: 0xB0
} ADC_Type;

/*******************************************************************************
 * ADC Type
 ******************************************************************************/

/*!
 * @addtogroup ADC_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief ADC_ADDATA Register Bit Definition
 */

#define ADC_ADDATA_VALID_SHIFT                  (21)
#define ADC_ADDATA_VALID_MASK                   (0x01U << ADC_ADDATA_VALID_SHIFT)
#define ADC_ADDATA_VALID(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADDATA_VALID_SHIFT)) & ADC_ADDATA_VALID_MASK)

#define ADC_ADDATA_OVERRUN_SHIFT                (20)
#define ADC_ADDATA_OVERRUN_MASK                 (0x01U << ADC_ADDATA_OVERRUN_SHIFT)
#define ADC_ADDATA_OVERRUN(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_ADDATA_OVERRUN_SHIFT)) & ADC_ADDATA_OVERRUN_MASK)

#define ADC_ADDATA_CHANNELSEL_SHIFT             (16)
#define ADC_ADDATA_CHANNELSEL_MASK              (0xFU << ADC_ADDATA_CHANNELSEL_SHIFT)
#define ADC_ADDATA_CHANNELSEL(x)                (((uint32_t)(((uint32_t)(x)) << ADC_ADDATA_CHANNELSEL_SHIFT)) & ADC_ADDATA_CHANNELSEL_MASK)

#define ADC_ADDATA_DATA_SHIFT                   (0)
#define ADC_ADDATA_DATA_MASK                    (0xFFFFU << ADC_ADDATA_DATA_SHIFT)
#define ADC_ADDATA_DATA(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADDATA_DATA_SHIFT)) & ADC_ADDATA_DATA_MASK)

/*!
 * @brief ADC_ADCFG Register Bit Definition
 */

#define ADC_ADCFG_JADWEN_SHIFT                  (16)
#define ADC_ADCFG_JADWEN_MASK                   (0x01U << ADC_ADCFG_JADWEN_SHIFT)
#define ADC_ADCFG_JADWEN(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADCFG_JADWEN_SHIFT)) & ADC_ADCFG_JADWEN_MASK)

#define ADC_ADCFG_ADCPREL_SHIFT                  (14)
#define ADC_ADCFG_ADCPREL_MASK                   (0x01U << ADC_ADCFG_ADCPREL_SHIFT)
#define ADC_ADCFG_ADCPREL(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADCFG_ADCPREL_SHIFT)) & ADC_ADCFG_ADCPREL_MASK)

#define ADC_ADCFG_RSLTCTL_SHIFT                 (7)
#define ADC_ADCFG_RSLTCTL_MASK                  (0x7U << ADC_ADCFG_RSLTCTL_SHIFT)
#define ADC_ADCFG_RSLTCTL(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_ADCFG_RSLTCTL_SHIFT)) & ADC_ADCFG_RSLTCTL_MASK)

#define ADC_ADCFG_ADCPREH_SHIFT                  (4)
#define ADC_ADCFG_ADCPREH_MASK                   (0x7U << ADC_ADCFG_ADCPREH_SHIFT)
#define ADC_ADCFG_ADCPREH(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADCFG_ADCPREH_SHIFT)) & ADC_ADCFG_ADCPREH_MASK)

#define ADC_ADCFG_VSEN_SHIFT                    (3)
#define ADC_ADCFG_VSEN_MASK                     (0x01U << ADC_ADCFG_VSEN_SHIFT)
#define ADC_ADCFG_VSEN(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_ADCFG_VSEN_SHIFT)) & ADC_ADCFG_VSEN_MASK)

#define ADC_ADCFG_TSEN_SHIFT                    (2)
#define ADC_ADCFG_TSEN_MASK                     (0x01U << ADC_ADCFG_TSEN_SHIFT)
#define ADC_ADCFG_TSEN(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_ADCFG_TSEN_SHIFT)) & ADC_ADCFG_TSEN_MASK)

#define ADC_ADCFG_ADWEN_SHIFT                   (1)
#define ADC_ADCFG_ADWEN_MASK                    (0x01U << ADC_ADCFG_ADWEN_SHIFT)
#define ADC_ADCFG_ADWEN(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADCFG_ADWEN_SHIFT)) & ADC_ADCFG_ADWEN_MASK)

#define ADC_ADCFG_ADEN_SHIFT                    (0)
#define ADC_ADCFG_ADEN_MASK                     (0x01U << ADC_ADCFG_ADEN_SHIFT)
#define ADC_ADCFG_ADEN(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_ADCFG_ADEN_SHIFT)) & ADC_ADCFG_ADEN_MASK)

/*!
 * @brief ADC_ADCR Register Bit Definition
 */

#define ADC_ADCR_EOCIE_SHIFT                    (27)
#define ADC_ADCR_EOCIE_MASK                     (0x01U << ADC_ADCR_EOCIE_SHIFT)
#define ADC_ADCR_EOCIE(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_EOCIE_SHIFT)) & ADC_ADCR_EOCIE_MASK)

#define ADC_ADCR_EOSMPIE_SHIFT                  (26)
#define ADC_ADCR_EOSMPIE_MASK                   (0x01U << ADC_ADCR_EOSMPIE_SHIFT)
#define ADC_ADCR_EOSMPIE(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_EOSMPIE_SHIFT)) & ADC_ADCR_EOSMPIE_MASK)

#define ADC_ADCR_TRGEDGE_SHIFT                  (24)
#define ADC_ADCR_TRGEDGE_MASK                   (0x3U << ADC_ADCR_TRGEDGE_SHIFT)
#define ADC_ADCR_TRGEDGE(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_TRGEDGE_SHIFT)) & ADC_ADCR_TRGEDGE_MASK)

#define ADC_ADCR_TRGSHIFT_SHIFT                 (19)
#define ADC_ADCR_TRGSHIFT_MASK                  (0x7U << ADC_ADCR_TRGSHIFT_SHIFT)
#define ADC_ADCR_TRGSHIFT(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_TRGSHIFT_SHIFT)) & ADC_ADCR_TRGSHIFT_MASK)

#define ADC_ADCR_TRGSELH_SHIFT                   (17)
#define ADC_ADCR_TRGSELH_MASK                    (0x3U << ADC_ADCR_TRGSELH_SHIFT)
#define ADC_ADCR_TRGSELH(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_TRGSELH_SHIFT)) & ADC_ADCR_TRGSELH_MASK)

#define ADC_ADCR_SCANDIR_SHIFT                  (16)
#define ADC_ADCR_SCANDIR_MASK                   (0x01U << ADC_ADCR_SCANDIR_SHIFT)
#define ADC_ADCR_SCANDIR(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_SCANDIR_SHIFT)) & ADC_ADCR_SCANDIR_MASK)

#define ADC_ADCR_CMPCH_SHIFT                    (12)
#define ADC_ADCR_CMPCH_MASK                     (0xFU << ADC_ADCR_CMPCH_SHIFT)
#define ADC_ADCR_CMPCH(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_CMPCH_SHIFT)) & ADC_ADCR_CMPCH_MASK)

#define ADC_ADCR_ALIGN_SHIFT                    (11)
#define ADC_ADCR_ALIGN_MASK                     (0x01U << ADC_ADCR_ALIGN_SHIFT)
#define ADC_ADCR_ALIGN(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_ALIGN_SHIFT)) & ADC_ADCR_ALIGN_MASK)

#define ADC_ADCR_ADMD_SHIFT                     (9)
#define ADC_ADCR_ADMD_MASK                      (0x3U << ADC_ADCR_ADMD_SHIFT)
#define ADC_ADCR_ADMD(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_ADMD_SHIFT)) & ADC_ADCR_ADMD_MASK)

#define ADC_ADCR_ADST_SHIFT                     (8)
#define ADC_ADCR_ADST_MASK                      (0x01U << ADC_ADCR_ADST_SHIFT)
#define ADC_ADCR_ADST(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_ADST_SHIFT)) & ADC_ADCR_ADST_MASK)

#define ADC_ADCR_TRGSELL_SHIFT                   (4)
#define ADC_ADCR_TRGSELL_MASK                    (0x7U << ADC_ADCR_TRGSELL_SHIFT)
#define ADC_ADCR_TRGSELL(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_TRGSELL_SHIFT)) & ADC_ADCR_TRGSELL_MASK)

#define ADC_ADCR_DMAEN_SHIFT                    (3)
#define ADC_ADCR_DMAEN_MASK                     (0x01U << ADC_ADCR_DMAEN_SHIFT)
#define ADC_ADCR_DMAEN(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_DMAEN_SHIFT)) & ADC_ADCR_DMAEN_MASK)

#define ADC_ADCR_TRGEN_SHIFT                    (2)
#define ADC_ADCR_TRGEN_MASK                     (0x01U << ADC_ADCR_TRGEN_SHIFT)
#define ADC_ADCR_TRGEN(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_TRGEN_SHIFT)) & ADC_ADCR_TRGEN_MASK)

#define ADC_ADCR_ADWIE_SHIFT                    (1)
#define ADC_ADCR_ADWIE_MASK                     (0x01U << ADC_ADCR_ADWIE_SHIFT)
#define ADC_ADCR_ADWIE(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_ADWIE_SHIFT)) & ADC_ADCR_ADWIE_MASK)

#define ADC_ADCR_ADIE_SHIFT                     (0)
#define ADC_ADCR_ADIE_MASK                      (0x01U << ADC_ADCR_ADIE_SHIFT)
#define ADC_ADCR_ADIE(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_ADCR_ADIE_SHIFT)) & ADC_ADCR_ADIE_MASK)

/*!
 * @brief ADC_ADCHS Register Bit Definition
 */

#define ADC_ADCHS_CHENVS_SHIFT                  (15)
#define ADC_ADCHS_CHENVS_MASK                   (0x01U << ADC_ADCHS_CHENVS_SHIFT)
#define ADC_ADCHS_CHENVS(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHENVS_SHIFT)) & ADC_ADCHS_CHENVS_MASK)

#define ADC_ADCHS_CHENTS_SHIFT                  (14)
#define ADC_ADCHS_CHENTS_MASK                   (0x01U << ADC_ADCHS_CHENTS_SHIFT)
#define ADC_ADCHS_CHENTS(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHENTS_SHIFT)) & ADC_ADCHS_CHENTS_MASK)

#define ADC_ADCHS_CHEN13_SHIFT                  (13)
#define ADC_ADCHS_CHEN13_MASK                   (0x01U << ADC_ADCHS_CHEN13_SHIFT)
#define ADC_ADCHS_CHEN13(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN13_SHIFT)) & ADC_ADCHS_CHEN13_MASK)

#define ADC_ADCHS_CHEN12_SHIFT                  (12)
#define ADC_ADCHS_CHEN12_MASK                   (0x01U << ADC_ADCHS_CHEN12_SHIFT)
#define ADC_ADCHS_CHEN12(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN12_SHIFT)) & ADC_ADCHS_CHEN12_MASK)

#define ADC_ADCHS_CHEN11_SHIFT                  (11)
#define ADC_ADCHS_CHEN11_MASK                   (0x01U << ADC_ADCHS_CHEN11_SHIFT)
#define ADC_ADCHS_CHEN11(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN11_SHIFT)) & ADC_ADCHS_CHEN11_MASK)

#define ADC_ADCHS_CHEN10_SHIFT                  (10)
#define ADC_ADCHS_CHEN10_MASK                   (0x01U << ADC_ADCHS_CHEN10_SHIFT)
#define ADC_ADCHS_CHEN10(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN10_SHIFT)) & ADC_ADCHS_CHEN10_MASK)

#define ADC_ADCHS_CHEN9_SHIFT                   (9)
#define ADC_ADCHS_CHEN9_MASK                    (0x01U << ADC_ADCHS_CHEN9_SHIFT)
#define ADC_ADCHS_CHEN9(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN9_SHIFT)) & ADC_ADCHS_CHEN9_MASK)

#define ADC_ADCHS_CHEN8_SHIFT                   (8)
#define ADC_ADCHS_CHEN8_MASK                    (0x01U << ADC_ADCHS_CHEN8_SHIFT)
#define ADC_ADCHS_CHEN8(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN8_SHIFT)) & ADC_ADCHS_CHEN8_MASK)

#define ADC_ADCHS_CHEN7_SHIFT                   (7)
#define ADC_ADCHS_CHEN7_MASK                    (0x01U << ADC_ADCHS_CHEN7_SHIFT)
#define ADC_ADCHS_CHEN7(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN7_SHIFT)) & ADC_ADCHS_CHEN7_MASK)

#define ADC_ADCHS_CHEN6_SHIFT                   (6)
#define ADC_ADCHS_CHEN6_MASK                    (0x01U << ADC_ADCHS_CHEN6_SHIFT)
#define ADC_ADCHS_CHEN6(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN6_SHIFT)) & ADC_ADCHS_CHEN6_MASK)

#define ADC_ADCHS_CHEN5_SHIFT                   (5)
#define ADC_ADCHS_CHEN5_MASK                    (0x01U << ADC_ADCHS_CHEN5_SHIFT)
#define ADC_ADCHS_CHEN5(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN5_SHIFT)) & ADC_ADCHS_CHEN5_MASK)

#define ADC_ADCHS_CHEN4_SHIFT                   (4)
#define ADC_ADCHS_CHEN4_MASK                    (0x01U << ADC_ADCHS_CHEN4_SHIFT)
#define ADC_ADCHS_CHEN4(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN4_SHIFT)) & ADC_ADCHS_CHEN4_MASK)

#define ADC_ADCHS_CHEN3_SHIFT                   (3)
#define ADC_ADCHS_CHEN3_MASK                    (0x01U << ADC_ADCHS_CHEN3_SHIFT)
#define ADC_ADCHS_CHEN3(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN3_SHIFT)) & ADC_ADCHS_CHEN3_MASK)

#define ADC_ADCHS_CHEN2_SHIFT                   (2)
#define ADC_ADCHS_CHEN2_MASK                    (0x01U << ADC_ADCHS_CHEN2_SHIFT)
#define ADC_ADCHS_CHEN2(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN2_SHIFT)) & ADC_ADCHS_CHEN2_MASK)

#define ADC_ADCHS_CHEN1_SHIFT                   (1)
#define ADC_ADCHS_CHEN1_MASK                    (0x01U << ADC_ADCHS_CHEN1_SHIFT)
#define ADC_ADCHS_CHEN1(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN1_SHIFT)) & ADC_ADCHS_CHEN1_MASK)

#define ADC_ADCHS_CHEN0_SHIFT                   (0)
#define ADC_ADCHS_CHEN0_MASK                    (0x01U << ADC_ADCHS_CHEN0_SHIFT)
#define ADC_ADCHS_CHEN0(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADCHS_CHEN0_SHIFT)) & ADC_ADCHS_CHEN0_MASK)

/*!
 * @brief ADC_ADCMPR Register Bit Definition
 */

#define ADC_ADCMPR_CMPHDATA_SHIFT               (16)
#define ADC_ADCMPR_CMPHDATA_MASK                (0xFFFU << ADC_ADCMPR_CMPHDATA_SHIFT)
#define ADC_ADCMPR_CMPHDATA(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_ADCMPR_CMPHDATA_SHIFT)) & ADC_ADCMPR_CMPHDATA_MASK)

#define ADC_ADCMPR_CMPLDATA_SHIFT               (0)
#define ADC_ADCMPR_CMPLDATA_MASK                (0xFFFU << ADC_ADCMPR_CMPLDATA_SHIFT)
#define ADC_ADCMPR_CMPLDATA(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_ADCMPR_CMPLDATA_SHIFT)) & ADC_ADCMPR_CMPLDATA_MASK)

/*!
 * @brief ADC_ADSTA Register Bit Definition
 */

#define ADC_ADSTA_OVERRUN_SHIFT                 (20)
#define ADC_ADSTA_OVERRUN_MASK                  (0xFFFU << ADC_ADSTA_OVERRUN_SHIFT)
#define ADC_ADSTA_OVERRUN(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_ADSTA_OVERRUN_SHIFT)) & ADC_ADSTA_OVERRUN_MASK)

#define ADC_ADSTA_VALID_SHIFT                   (8)
#define ADC_ADSTA_VALID_MASK                    (0xFFFU << ADC_ADSTA_VALID_SHIFT)
#define ADC_ADSTA_VALID(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADSTA_VALID_SHIFT)) & ADC_ADSTA_VALID_MASK)

#define ADC_ADSTA_CHANNEL_SHIFT                 (4)
#define ADC_ADSTA_CHANNEL_MASK                  (0xFU << ADC_ADSTA_CHANNEL_SHIFT)
#define ADC_ADSTA_CHANNEL(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_ADSTA_CHANNEL_SHIFT)) & ADC_ADSTA_CHANNEL_MASK)

#define ADC_ADSTA_BUSY_SHIFT                    (2)
#define ADC_ADSTA_BUSY_MASK                     (0x01U << ADC_ADSTA_BUSY_SHIFT)
#define ADC_ADSTA_BUSY(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_ADSTA_BUSY_SHIFT)) & ADC_ADSTA_BUSY_MASK)

#define ADC_ADSTA_ADWIF_SHIFT                   (1)
#define ADC_ADSTA_ADWIF_MASK                    (0x01U << ADC_ADSTA_ADWIF_SHIFT)
#define ADC_ADSTA_ADWIF(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADSTA_ADWIF_SHIFT)) & ADC_ADSTA_ADWIF_MASK)

#define ADC_ADSTA_ADIF_SHIFT                   (0)
#define ADC_ADSTA_ADIF_MASK                    (0x01U << ADC_ADSTA_ADIF_SHIFT)
#define ADC_ADSTA_ADIF(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ADSTA_ADIF_SHIFT)) & ADC_ADSTA_ADIF_MASK)

/*!
 * @brief ADC_ADDR Register Bit Definition
 */

#define ADC_ADDR_VALID_SHIFT                    (21)
#define ADC_ADDR_VALID_MASK                     (0x01U << ADC_ADDR_VALID_SHIFT)
#define ADC_ADDR_VALID(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_ADDR_VALID_SHIFT)) & ADC_ADDR_VALID_MASK)

#define ADC_ADDR_OVERRUN_SHIFT                  (20)
#define ADC_ADDR_OVERRUN_MASK                   (0x01U << ADC_ADDR_OVERRUN_SHIFT)
#define ADC_ADDR_OVERRUN(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ADDR_OVERRUN_SHIFT)) & ADC_ADDR_OVERRUN_MASK)

#define ADC_ADDR_DATA_SHIFT                     (0)
#define ADC_ADDR_DATA_MASK                      (0xFFFFU << ADC_ADDR_DATA_SHIFT)
#define ADC_ADDR_DATA(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_ADDR_DATA_SHIFT)) & ADC_ADDR_DATA_MASK)

/*!
 * @brief ADC_ADSTAEXT Register Bit Definition
 */

#define ADC_ADSTAEXT_JBUSY_SHIFT               (21)
#define ADC_ADSTAEXT_JBUSY_MASK                (0x01U << ADC_ADSTAEXT_JBUSY_SHIFT)
#define ADC_ADSTAEXT_JBUSY(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_ADSTAEXT_JBUSY_SHIFT)) & ADC_ADSTAEXT_JBUSY_MASK)

#define ADC_ADSTAEXT_JEOSIF_SHIFT              (20)
#define ADC_ADSTAEXT_JEOSIF_MASK               (0x01U << ADC_ADSTAEXT_JEOSIF_SHIFT)
#define ADC_ADSTAEXT_JEOSIF(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_ADSTAEXT_JEOSIF_SHIFT)) & ADC_ADSTAEXT_JEOSIF_MASK)

#define ADC_ADSTAEXT_JEOCIF_SHIFT              (19)
#define ADC_ADSTAEXT_JEOCIF_MASK               (0x01U << ADC_ADSTAEXT_JEOCIF_SHIFT)
#define ADC_ADSTAEXT_JEOCIF(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_ADSTAEXT_JEOCIF_SHIFT)) & ADC_ADSTAEXT_JEOCIF_MASK)

#define ADC_ADSTAEXT_JEOSMPIF_SHIFT            (18)
#define ADC_ADSTAEXT_JEOSMPIF_MASK             (0x01U << ADC_ADSTAEXT_JEOSMPIF_SHIFT)
#define ADC_ADSTAEXT_JEOSMPIF(x)               (((uint32_t)(((uint32_t)(x)) << ADC_ADSTAEXT_JEOSMPIF_SHIFT)) & ADC_ADSTAEXT_JEOSMPIF_MASK)

#define ADC_ADSTAEXT_EOCIF_SHIFT               (17)
#define ADC_ADSTAEXT_EOCIF_MASK                (0x01U << ADC_ADSTAEXT_EOCIF_SHIFT)
#define ADC_ADSTAEXT_EOCIF(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_ADSTAEXT_EOCIF_SHIFT)) & ADC_ADSTAEXT_EOCIF_MASK)

#define ADC_ADSTAEXT_EOSMPIF_SHIFT             (16)
#define ADC_ADSTAEXT_EOSMPIF_MASK              (0x01U << ADC_ADSTAEXT_EOSMPIF_SHIFT)
#define ADC_ADSTAEXT_EOSMPIF(x)                (((uint32_t)(((uint32_t)(x)) << ADC_ADSTAEXT_EOSMPIF_SHIFT)) & ADC_ADSTAEXT_EOSMPIF_MASK)

#define ADC_ADSTAEXT_OVERRUN_SHIFT             (4)
#define ADC_ADSTAEXT_OVERRUN_MASK              (0xFU << ADC_ADSTAEXT_OVERRUN_SHIFT)
#define ADC_ADSTAEXT_OVERRUN(x)                (((uint32_t)(((uint32_t)(x)) << ADC_ADSTAEXT_OVERRUN_SHIFT)) & ADC_ADSTAEXT_OVERRUN_MASK)

#define ADC_ADSTAEXT_VALID_SHIFT               (0)
#define ADC_ADSTAEXT_VALID_MASK                (0xFU << ADC_ADSTAEXT_VALID_SHIFT)
#define ADC_ADSTAEXT_VALID(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_ADSTAEXT_VALID_SHIFT)) & ADC_ADSTAEXT_VALID_MASK)

/*!
 * @brief ADC_CHANY0 Register Bit Definition
 */

#define ADC_CHANY0_CHANYSEL7_SHIFT              (28)
#define ADC_CHANY0_CHANYSEL7_MASK               (0xFU << ADC_CHANY0_CHANYSEL7_SHIFT)
#define ADC_CHANY0_CHANYSEL7(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_CHANY0_CHANYSEL7_SHIFT)) & ADC_CHANY0_CHANYSEL7_MASK)

#define ADC_CHANY0_CHANYSEL6_SHIFT              (24)
#define ADC_CHANY0_CHANYSEL6_MASK               (0xFU << ADC_CHANY0_CHANYSEL6_SHIFT)
#define ADC_CHANY0_CHANYSEL6(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_CHANY0_CHANYSEL6_SHIFT)) & ADC_CHANY0_CHANYSEL6_MASK)

#define ADC_CHANY0_CHANYSEL5_SHIFT              (20)
#define ADC_CHANY0_CHANYSEL5_MASK               (0xFU << ADC_CHANY0_CHANYSEL5_SHIFT)
#define ADC_CHANY0_CHANYSEL5(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_CHANY0_CHANYSEL5_SHIFT)) & ADC_CHANY0_CHANYSEL5_MASK)

#define ADC_CHANY0_CHANYSEL4_SHIFT              (16)
#define ADC_CHANY0_CHANYSEL4_MASK               (0xFU << ADC_CHANY0_CHANYSEL4_SHIFT)
#define ADC_CHANY0_CHANYSEL4(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_CHANY0_CHANYSEL4_SHIFT)) & ADC_CHANY0_CHANYSEL4_MASK)

#define ADC_CHANY0_CHANYSEL3_SHIFT              (12)
#define ADC_CHANY0_CHANYSEL3_MASK               (0xFU << ADC_CHANY0_CHANYSEL3_SHIFT)
#define ADC_CHANY0_CHANYSEL3(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_CHANY0_CHANYSEL3_SHIFT)) & ADC_CHANY0_CHANYSEL3_MASK)

#define ADC_CHANY0_CHANYSEL2_SHIFT              (8)
#define ADC_CHANY0_CHANYSEL2_MASK               (0xFU << ADC_CHANY0_CHANYSEL2_SHIFT)
#define ADC_CHANY0_CHANYSEL2(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_CHANY0_CHANYSEL2_SHIFT)) & ADC_CHANY0_CHANYSEL2_MASK)

#define ADC_CHANY0_CHANYSEL1_SHIFT              (4)
#define ADC_CHANY0_CHANYSEL1_MASK               (0xFU << ADC_CHANY0_CHANYSEL1_SHIFT)
#define ADC_CHANY0_CHANYSEL1(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_CHANY0_CHANYSEL1_SHIFT)) & ADC_CHANY0_CHANYSEL1_MASK)

#define ADC_CHANY0_CHANYSEL0_SHIFT              (0)
#define ADC_CHANY0_CHANYSEL0_MASK               (0xFU << ADC_CHANY0_CHANYSEL0_SHIFT)
#define ADC_CHANY0_CHANYSEL0(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_CHANY0_CHANYSEL0_SHIFT)) & ADC_CHANY0_CHANYSEL0_MASK)

/*!
 * @brief ADC_CHANY1 Register Bit Definition
 */

#define ADC_CHANY1_CHANYSEL15_SHIFT             (28)
#define ADC_CHANY1_CHANYSEL15_MASK              (0xFU << ADC_CHANY1_CHANYSEL15_SHIFT)
#define ADC_CHANY1_CHANYSEL15(x)                (((uint32_t)(((uint32_t)(x)) << ADC_CHANY1_CHANYSEL15_SHIFT)) & ADC_CHANY1_CHANYSEL15_MASK)

#define ADC_CHANY1_CHANYSEL14_SHIFT             (24)
#define ADC_CHANY1_CHANYSEL14_MASK              (0xFU << ADC_CHANY1_CHANYSEL14_SHIFT)
#define ADC_CHANY1_CHANYSEL14(x)                (((uint32_t)(((uint32_t)(x)) << ADC_CHANY1_CHANYSEL14_SHIFT)) & ADC_CHANY1_CHANYSEL14_MASK)

#define ADC_CHANY1_CHANYSEL13_SHIFT             (20)
#define ADC_CHANY1_CHANYSEL13_MASK              (0xFU << ADC_CHANY1_CHANYSEL13_SHIFT)
#define ADC_CHANY1_CHANYSEL13(x)                (((uint32_t)(((uint32_t)(x)) << ADC_CHANY1_CHANYSEL13_SHIFT)) & ADC_CHANY1_CHANYSEL13_MASK)

#define ADC_CHANY1_CHANYSEL12_SHIFT             (16)
#define ADC_CHANY1_CHANYSEL12_MASK              (0xFU << ADC_CHANY1_CHANYSEL12_SHIFT)
#define ADC_CHANY1_CHANYSEL12(x)                (((uint32_t)(((uint32_t)(x)) << ADC_CHANY1_CHANYSEL12_SHIFT)) & ADC_CHANY1_CHANYSEL12_MASK)

#define ADC_CHANY1_CHANYSEL11_SHIFT             (12)
#define ADC_CHANY1_CHANYSEL11_MASK              (0xFU << ADC_CHANY1_CHANYSEL11_SHIFT)
#define ADC_CHANY1_CHANYSEL11(x)                (((uint32_t)(((uint32_t)(x)) << ADC_CHANY1_CHANYSEL11_SHIFT)) & ADC_CHANY1_CHANYSEL11_MASK)

#define ADC_CHANY1_CHANYSEL10_SHIFT             (8)
#define ADC_CHANY1_CHANYSEL10_MASK              (0xFU << ADC_CHANY1_CHANYSEL10_SHIFT)
#define ADC_CHANY1_CHANYSEL10(x)                (((uint32_t)(((uint32_t)(x)) << ADC_CHANY1_CHANYSEL10_SHIFT)) & ADC_CHANY1_CHANYSEL10_MASK)

#define ADC_CHANY1_CHANYSEL9_SHIFT              (4)
#define ADC_CHANY1_CHANYSEL9_MASK               (0xFU << ADC_CHANY1_CHANYSEL9_SHIFT)
#define ADC_CHANY1_CHANYSEL9(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_CHANY1_CHANYSEL9_SHIFT)) & ADC_CHANY1_CHANYSEL9_MASK)

#define ADC_CHANY1_CHANYSEL8_SHIFT              (0)
#define ADC_CHANY1_CHANYSEL8_MASK               (0xFU << ADC_CHANY1_CHANYSEL8_SHIFT)
#define ADC_CHANY1_CHANYSEL8(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_CHANY1_CHANYSEL8_SHIFT)) & ADC_CHANY1_CHANYSEL8_MASK)

/*!
 * @brief ADC_ANYCFG Register Bit Definition
 */

#define ADC_ANYCFG_CHANYNUM_SHIFT              (0)
#define ADC_ANYCFG_CHANYNUM_MASK               (0xFU << ADC_ANYCFG_CHANYNUM_SHIFT)
#define ADC_ANYCFG_CHANYNUM(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_ANYCFG_CHANYNUM_SHIFT)) & ADC_ANYCFG_CHANYNUM_MASK)

/*!
 * @brief ADC_ANYCR Register Bit Definition
 */

#define ADC_ANYCR_JTRGEDGE_SHIFT               (16)
#define ADC_ANYCR_JTRGEDGE_MASK                (0x3U << ADC_ANYCR_JTRGEDGE_SHIFT)
#define ADC_ANYCR_JTRGEDGE(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_ANYCR_JTRGEDGE_SHIFT)) & ADC_ANYCR_JTRGEDGE_MASK)

#define ADC_ANYCR_JTRGSHIFT_SHIFT              (13)
#define ADC_ANYCR_JTRGSHIFT_MASK               (0x7U << ADC_ANYCR_JTRGSHIFT_SHIFT)
#define ADC_ANYCR_JTRGSHIFT(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_ANYCR_JTRGSHIFT_SHIFT)) & ADC_ANYCR_JTRGSHIFT_MASK)

#define ADC_ANYCR_JTRGSEL_SHIFT                (8)
#define ADC_ANYCR_JTRGSEL_MASK                 (0x7U << ADC_ANYCR_JTRGSEL_SHIFT)
#define ADC_ANYCR_JTRGSEL(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_ANYCR_JTRGSEL_SHIFT)) & ADC_ANYCR_JTRGSEL_MASK)

#define ADC_ANYCR_JTRGEN_SHIFT                 (7)
#define ADC_ANYCR_JTRGEN_MASK                  (0x01U << ADC_ANYCR_JTRGEN_SHIFT)
#define ADC_ANYCR_JTRGEN(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_ANYCR_JTRGEN_SHIFT)) & ADC_ANYCR_JTRGEN_MASK)

#define ADC_ANYCR_JADST_SHIFT                  (6)
#define ADC_ANYCR_JADST_MASK                   (0x01U << ADC_ANYCR_JADST_SHIFT)
#define ADC_ANYCR_JADST(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ANYCR_JADST_SHIFT)) & ADC_ANYCR_JADST_MASK)

#define ADC_ANYCR_JAUTO_SHIFT                  (5)
#define ADC_ANYCR_JAUTO_MASK                   (0x01U << ADC_ANYCR_JAUTO_SHIFT)
#define ADC_ANYCR_JAUTO(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_ANYCR_JAUTO_SHIFT)) & ADC_ANYCR_JAUTO_MASK)

#define ADC_ANYCR_JEOSIE_SHIFT                 (4)
#define ADC_ANYCR_JEOSIE_MASK                  (0x01U << ADC_ANYCR_JEOSIE_SHIFT)
#define ADC_ANYCR_JEOSIE(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_ANYCR_JEOSIE_SHIFT)) & ADC_ANYCR_JEOSIE_MASK)

#define ADC_ANYCR_JEOCIE_SHIFT                 (3)
#define ADC_ANYCR_JEOCIE_MASK                  (0x01U << ADC_ANYCR_JEOCIE_SHIFT)
#define ADC_ANYCR_JEOCIE(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_ANYCR_JEOCIE_SHIFT)) & ADC_ANYCR_JEOCIE_MASK)

#define ADC_ANYCR_JEOSMPIE_SHIFT               (2)
#define ADC_ANYCR_JEOSMPIE_MASK                (0x01U << ADC_ANYCR_JEOSMPIE_SHIFT)
#define ADC_ANYCR_JEOSMPIE(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_ANYCR_JEOSMPIE_SHIFT)) & ADC_ANYCR_JEOSMPIE_MASK)

#define ADC_ANYCR_JCEN_SHIFT                   (1)
#define ADC_ANYCR_JCEN_MASK                    (0x01U << ADC_ANYCR_JCEN_SHIFT)
#define ADC_ANYCR_JCEN(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_ANYCR_JCEN_SHIFT)) & ADC_ANYCR_JCEN_MASK)

#define ADC_ANYCR_CHANYMDEN_SHIFT              (0)
#define ADC_ANYCR_CHANYMDEN_MASK               (0x01U << ADC_ANYCR_CHANYMDEN_SHIFT)
#define ADC_ANYCR_CHANYMDEN(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_ANYCR_CHANYMDEN_SHIFT)) & ADC_ANYCR_CHANYMDEN_MASK)

/*!
 * @brief ADC_SMPR1 Register Bit Definition
 */

#define ADC_SMPR1_SAMCTLX_SHIFT                 (0)
#define ADC_SMPR1_SAMCTLX_MASK                  (0xFFFFFFFFU << ADC_SMPR1_SAMCTLX_SHIFT)
#define ADC_SMPR1_SAMCTLX(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_SMPR1_SAMCTLX_SHIFT)) & ADC_SMPR1_SAMCTLX_MASK)

/*!
 * @brief ADC_SMPR2 Register Bit Definition
 */

#define ADC_SMPR2_SAMCTLX_SHIFT                 (0)
#define ADC_SMPR2_SAMCTLX_MASK                  (0xFFFFFFFFU << ADC_SMPR2_SAMCTLX_SHIFT)
#define ADC_SMPR2_SAMCTLX(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_SMPR2_SAMCTLX_SHIFT)) & ADC_SMPR2_SAMCTLX_MASK)

/*!
 * @brief ADC_JOFR Register Bit Definition
 */

#define ADC_JOFR_JOFR_SHIFT                     (0)
#define ADC_JOFR_JOFR_MASK                      (0xFFFU << ADC_JOFR_JOFR_SHIFT)
#define ADC_JOFR_JOFR(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_JOFR_JOFR_SHIFT)) & ADC_JOFR_JOFR_MASK)

/*!
 * @brief ADC_JSQR Register Bit Definition
 */

#define ADC_JSQR_JNUM_SHIFT                     (20)
#define ADC_JSQR_JNUM_MASK                      (0x3U << ADC_JSQR_JNUM_SHIFT)
#define ADC_JSQR_JNUM(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_JSQR_JNUM_SHIFT)) & ADC_JSQR_JNUM_MASK)

#define ADC_JSQR_JSQ3_SHIFT                     (15)
#define ADC_JSQR_JSQ3_MASK                      (0x1FU << ADC_JSQR_JSQ3_SHIFT)
#define ADC_JSQR_JSQ3(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_JSQR_JSQ3_SHIFT)) & ADC_JSQR_JSQ3_MASK)

#define ADC_JSQR_JSQ2_SHIFT                     (10)
#define ADC_JSQR_JSQ2_MASK                      (0x1FU << ADC_JSQR_JSQ2_SHIFT)
#define ADC_JSQR_JSQ2(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_JSQR_JSQ2_SHIFT)) & ADC_JSQR_JSQ2_MASK)

#define ADC_JSQR_JSQ1_SHIFT                     (5)
#define ADC_JSQR_JSQ1_MASK                      (0x1FU << ADC_JSQR_JSQ1_SHIFT)
#define ADC_JSQR_JSQ1(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_JSQR_JSQ1_SHIFT)) & ADC_JSQR_JSQ1_MASK)

#define ADC_JSQR_JSQ0_SHIFT                     (0)
#define ADC_JSQR_JSQ0_MASK                      (0x1FU << ADC_JSQR_JSQ0_SHIFT)
#define ADC_JSQR_JSQ0(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_JSQR_JSQ0_SHIFT)) & ADC_JSQR_JSQ0_MASK)

/*!
 * @brief ADC_JADDATA Register Bit Definition
 */

#define ADC_JADDATA_JVALID_SHIFT                (22)
#define ADC_JADDATA_JVALID_MASK                 (0x01U << ADC_JADDATA_JVALID_SHIFT)
#define ADC_JADDATA_JVALID(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_JADDATA_JVALID_SHIFT)) & ADC_JADDATA_JVALID_MASK)

#define ADC_JADDATA_JOVERRUN_SHIFT              (21)
#define ADC_JADDATA_JOVERRUN_MASK               (0x01U << ADC_JADDATA_JOVERRUN_SHIFT)
#define ADC_JADDATA_JOVERRUN(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_JADDATA_JOVERRUN_SHIFT)) & ADC_JADDATA_JOVERRUN_MASK)

#define ADC_JADDATA_JCHANNELSEL_SHIFT           (16)
#define ADC_JADDATA_JCHANNELSEL_MASK            (0xFU << ADC_JADDATA_JCHANNELSEL_SHIFT)
#define ADC_JADDATA_JCHANNELSEL(x)              (((uint32_t)(((uint32_t)(x)) << ADC_JADDATA_JCHANNELSEL_SHIFT)) & ADC_JADDATA_JCHANNELSEL_MASK)

#define ADC_JADDATA_JDATA_SHIFT                 (0)
#define ADC_JADDATA_JDATA_MASK                  (0xFFFFU << ADC_JADDATA_JDATA_SHIFT)
#define ADC_JADDATA_JDATA(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_JADDATA_JDATA_SHIFT)) & ADC_JADDATA_JDATA_MASK)

/*!
 * @brief ADC_JDR Register Bit Definition
 */

#define ADC_JDR_JVALID_SHIFT                    (22)
#define ADC_JDR_JVALID_MASK                     (0x01U << ADC_JDR_JVALID_SHIFT)
#define ADC_JDR_JVALID(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_JDR_JVALID_SHIFT)) & ADC_JDR_JVALID_MASK)

#define ADC_JDR_JOVERRUN_SHIFT                  (21)
#define ADC_JDR_JOVERRUN_MASK                   (0x01U << ADC_JDR_JOVERRUN_SHIFT)
#define ADC_JDR_JOVERRUN(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_JDR_JOVERRUN_SHIFT)) & ADC_JDR_JOVERRUN_MASK)

#define ADC_JDR_JDATA_SHIFT                     (0)
#define ADC_JDR_JDATA_MASK                      (0xFFFFU << ADC_JDR_JDATA_SHIFT)
#define ADC_JDR_JDATA(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_JDR_JDATA_SHIFT)) & ADC_JDR_JDATA_MASK)

/*!
 * @}
 */ /* end of group ADC_Register_Masks */
/******************************************************************************
 * ADC Instance
******************************************************************************/
#define ADC1                                ((ADC_Type*)ADC1_BASE)
#define ADC2                                ((ADC_Type*)ADC2_BASE)
#define ADC3                                ((ADC_Type*)ADC3_BASE)

/*!
 * @}
 */ /* end of group ADC_Peripheral_Access_Layer */



/*!
 * @addtogroup DAC_Peripheral_Access_Layer DAC Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * DAC Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CR;                                                             ///< DAC control register                         offset: 0x00
    __IO uint32_t SWTRIGR;                                                        ///< DAC software trigger register                offset: 0x04
    __IO uint32_t DHR12R1;                                                        ///< 12-bit right-justified data holding register for DAC channel 1 offset: 0x08
    __IO uint32_t DHR12L1;                                                        ///< DAC channel 1 12-bit left-justified data holding register offset: 0x0C
    __IO uint32_t DHR8R1;                                                         ///< 8-bit right-justified data holding register for DAC channel 1 offset: 0x10
    __IO uint32_t DHR12R2;                                                        ///< 12-bit right-justified data holding register for DAC channel 2 offset: 0x14
    __IO uint32_t DHR12L2;                                                        ///< 12-bit left-justified data holding register for DAC channel 2 offset: 0x18
    __IO uint32_t DHR8R2;                                                         ///< 8-bit right-justified data holding register for DAC channel 2 offset: 0x1C
    __IO uint32_t DHR12RD;                                                        ///< 12-bit right-justified data holding register for dual DAC offset: 0x20
    __IO uint32_t DHR12LD;                                                        ///< 12-bit left-justified data holding register for dual DAC offset: 0x24
    __IO uint32_t DHR8RD;                                                         ///< 8-bit right-justified data holding register for dual DAC offset: 0x28
    __IO uint32_t DOR1;                                                           ///< DAC channel 1 data output register           offset: 0x2C
    __IO uint32_t DOR2;                                                           ///< DAC channel 2 data output register           offset: 0x30
} DAC_Type;

/*******************************************************************************
 * DAC Type
 ******************************************************************************/

/*!
 * @addtogroup DAC_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief DAC_CR Register Bit Definition
 */

#define DAC_CR_DMAEN2_SHIFT                     (28)
#define DAC_CR_DMAEN2_MASK                      (0x01U << DAC_CR_DMAEN2_SHIFT)
#define DAC_CR_DMAEN2(x)                        (((uint32_t)(((uint32_t)(x)) << DAC_CR_DMAEN2_SHIFT)) & DAC_CR_DMAEN2_MASK)

#define DAC_CR_MAMP2_SHIFT                      (24)
#define DAC_CR_MAMP2_MASK                       (0xFU << DAC_CR_MAMP2_SHIFT)
#define DAC_CR_MAMP2(x)                         (((uint32_t)(((uint32_t)(x)) << DAC_CR_MAMP2_SHIFT)) & DAC_CR_MAMP2_MASK)

#define DAC_CR_WAVE2_SHIFT                      (22)
#define DAC_CR_WAVE2_MASK                       (0x03U << DAC_CR_WAVE2_SHIFT)
#define DAC_CR_WAVE2(x)                         (((uint32_t)(((uint32_t)(x)) << DAC_CR_WAVE2_SHIFT)) & DAC_CR_WAVE2_MASK)

#define DAC_CR_TSEL2_SHIFT                      (19)
#define DAC_CR_TSEL2_MASK                       (0x07U << DAC_CR_TSEL2_SHIFT)
#define DAC_CR_TSEL2(x)                         (((uint32_t)(((uint32_t)(x)) << DAC_CR_TSEL2_SHIFT)) & DAC_CR_TSEL2_MASK)

#define DAC_CR_TEN2_SHIFT                       (18)
#define DAC_CR_TEN2_MASK                        (0x01U << DAC_CR_TEN2_SHIFT)
#define DAC_CR_TEN2(x)                          (((uint32_t)(((uint32_t)(x)) << DAC_CR_TEN2_SHIFT)) & DAC_CR_TEN2_MASK)

#define DAC_CR_BOFF2_SHIFT                      (17)
#define DAC_CR_BOFF2_MASK                       (0x01U << DAC_CR_BOFF2_SHIFT)
#define DAC_CR_BOFF2(x)                         (((uint32_t)(((uint32_t)(x)) << DAC_CR_BOFF2_SHIFT)) & DAC_CR_BOFF2_MASK)

#define DAC_CR_EN2_SHIFT                        (16)
#define DAC_CR_EN2_MASK                         (0x01U << DAC_CR_EN2_SHIFT)
#define DAC_CR_EN2(x)                           (((uint32_t)(((uint32_t)(x)) << DAC_CR_EN2_SHIFT)) & DAC_CR_EN2_MASK)

#define DAC_CR_DMAEN1_SHIFT                     (12)
#define DAC_CR_DMAEN1_MASK                      (0x01U << DAC_CR_DMAEN1_SHIFT)
#define DAC_CR_DMAEN1(x)                        (((uint32_t)(((uint32_t)(x)) << DAC_CR_DMAEN1_SHIFT)) & DAC_CR_DMAEN1_MASK)

#define DAC_CR_MAMP1_SHIFT                      (8)
#define DAC_CR_MAMP1_MASK                       (0xFU << DAC_CR_MAMP1_SHIFT)
#define DAC_CR_MAMP1(x)                         (((uint32_t)(((uint32_t)(x)) << DAC_CR_MAMP1_SHIFT)) & DAC_CR_MAMP1_MASK)

#define DAC_CR_WAVE1_SHIFT                      (6)
#define DAC_CR_WAVE1_MASK                       (0x3U << DAC_CR_WAVE1_SHIFT)
#define DAC_CR_WAVE1(x)                         (((uint32_t)(((uint32_t)(x)) << DAC_CR_WAVE1_SHIFT)) & DAC_CR_WAVE1_MASK)

#define DAC_CR_TSEL1_SHIFT                      (3)
#define DAC_CR_TSEL1_MASK                       (0x7U << DAC_CR_TSEL1_SHIFT)
#define DAC_CR_TSEL1(x)                         (((uint32_t)(((uint32_t)(x)) << DAC_CR_TSEL1_SHIFT)) & DAC_CR_TSEL1_MASK)

#define DAC_CR_TEN1_SHIFT                       (2)
#define DAC_CR_TEN1_MASK                        (0x01U << DAC_CR_TEN1_SHIFT)
#define DAC_CR_TEN1(x)                          (((uint32_t)(((uint32_t)(x)) << DAC_CR_TEN1_SHIFT)) & DAC_CR_TEN1_MASK)

#define DAC_CR_BOFF1_SHIFT                      (1)
#define DAC_CR_BOFF1_MASK                       (0x01U << DAC_CR_BOFF1_SHIFT)
#define DAC_CR_BOFF1(x)                         (((uint32_t)(((uint32_t)(x)) << DAC_CR_BOFF1_SHIFT)) & DAC_CR_BOFF1_MASK)

#define DAC_CR_EN1_SHIFT                        (0)
#define DAC_CR_EN1_MASK                         (0x01U << DAC_CR_EN1_SHIFT)
#define DAC_CR_EN1(x)                           (((uint32_t)(((uint32_t)(x)) << DAC_CR_EN1_SHIFT)) & DAC_CR_EN1_MASK)

/*!
 * @brief DAC_SWTRIGR Register Bit Definition
 */

#define DAC_SWTRIGR_DACPRE_SHIFT                (8)
#define DAC_SWTRIGR_DACPRE_MASK                 (0x7FU << DAC_SWTRIGR_DACPRE_SHIFT)
#define DAC_SWTRIGR_DACPRE(x)                   (((uint32_t)(((uint32_t)(x)) << DAC_SWTRIGR_DACPRE_SHIFT)) & DAC_SWTRIGR_DACPRE_MASK)

#define DAC_SWTRIGR_SWTRIG2_SHIFT               (1)
#define DAC_SWTRIGR_SWTRIG2_MASK                (0x01U << DAC_SWTRIGR_SWTRIG2_SHIFT)
#define DAC_SWTRIGR_SWTRIG2(x)                  (((uint32_t)(((uint32_t)(x)) << DAC_SWTRIGR_SWTRIG2_SHIFT)) & DAC_SWTRIGR_SWTRIG2_MASK)

#define DAC_SWTRIGR_SWTRIG1_SHIFT               (0)
#define DAC_SWTRIGR_SWTRIG1_MASK                (0x01U << DAC_SWTRIGR_SWTRIG1_SHIFT)
#define DAC_SWTRIGR_SWTRIG1(x)                  (((uint32_t)(((uint32_t)(x)) << DAC_SWTRIGR_SWTRIG1_SHIFT)) & DAC_SWTRIGR_SWTRIG1_MASK)

/*!
 * @brief DAC_DHR12R1 Register Bit Definition
 */

#define DAC_DHR12R1_DACC1DHR_SHIFT              (0)
#define DAC_DHR12R1_DACC1DHR_MASK               (0xFFFU << DAC_DHR12R1_DACC1DHR_SHIFT)
#define DAC_DHR12R1_DACC1DHR(x)                 (((uint32_t)(((uint32_t)(x)) << DAC_DHR12R1_DACC1DHR_SHIFT)) & DAC_DHR12R1_DACC1DHR_MASK)

/*!
 * @brief DAC_DHR12L1 Register Bit Definition
 */

#define DAC_DHR12L1_DACC1DHR_SHIFT              (4)
#define DAC_DHR12L1_DACC1DHR_MASK               (0xFFFU << DAC_DHR12L1_DACC1DHR_SHIFT)
#define DAC_DHR12L1_DACC1DHR(x)                 (((uint32_t)(((uint32_t)(x)) << DAC_DHR12L1_DACC1DHR_SHIFT)) & DAC_DHR12L1_DACC1DHR_MASK)

/*!
 * @brief DAC_DHR8R1 Register Bit Definition
 */

#define DAC_DHR8R1_DACC1DHR_SHIFT               (0)
#define DAC_DHR8R1_DACC1DHR_MASK                (0xFFU << DAC_DHR8R1_DACC1DHR_SHIFT)
#define DAC_DHR8R1_DACC1DHR(x)                  (((uint32_t)(((uint32_t)(x)) << DAC_DHR8R1_DACC1DHR_SHIFT)) & DAC_DHR8R1_DACC1DHR_MASK)

/*!
 * @brief DAC_DHR12R2 Register Bit Definition
 */

#define DAC_DHR12R2_DACC2DHR_SHIFT              (0)
#define DAC_DHR12R2_DACC2DHR_MASK               (0xFFFU << DAC_DHR12R2_DACC2DHR_SHIFT)
#define DAC_DHR12R2_DACC2DHR(x)                 (((uint32_t)(((uint32_t)(x)) << DAC_DHR12R2_DACC2DHR_SHIFT)) & DAC_DHR12R2_DACC2DHR_MASK)

/*!
 * @brief DAC_DHR12L2 Register Bit Definition
 */

#define DAC_DHR12L2_DACC2DHR_SHIFT              (4)
#define DAC_DHR12L2_DACC2DHR_MASK               (0xFFFU << DAC_DHR12L2_DACC2DHR_SHIFT)
#define DAC_DHR12L2_DACC2DHR(x)                 (((uint32_t)(((uint32_t)(x)) << DAC_DHR12L2_DACC2DHR_SHIFT)) & DAC_DHR12L2_DACC2DHR_MASK)

/*!
 * @brief DAC_DHR8R2 Register Bit Definition
 */

#define DAC_DHR8R2_DACC2DHR_SHIFT               (0)
#define DAC_DHR8R2_DACC2DHR_MASK                (0xFFU << DAC_DHR8R2_DACC2DHR_SHIFT)
#define DAC_DHR8R2_DACC2DHR(x)                  (((uint32_t)(((uint32_t)(x)) << DAC_DHR8R2_DACC2DHR_SHIFT)) & DAC_DHR8R2_DACC2DHR_MASK)

/*!
 * @brief DAC_DHR12RD Register Bit Definition
 */

#define DAC_DHR12RD_DACC2DHR_SHIFT              (16)
#define DAC_DHR12RD_DACC2DHR_MASK               (0xFFFU << DAC_DHR12RD_DACC2DHR_SHIFT)
#define DAC_DHR12RD_DACC2DHR(x)                 (((uint32_t)(((uint32_t)(x)) << DAC_DHR12RD_DACC2DHR_SHIFT)) & DAC_DHR12RD_DACC2DHR_MASK)

#define DAC_DHR12RD_DACC1DHR_SHIFT              (0)
#define DAC_DHR12RD_DACC1DHR_MASK               (0xFFFU << DAC_DHR12RD_DACC1DHR_SHIFT)
#define DAC_DHR12RD_DACC1DHR(x)                 (((uint32_t)(((uint32_t)(x)) << DAC_DHR12RD_DACC1DHR_SHIFT)) & DAC_DHR12RD_DACC1DHR_MASK)

/*!
 * @brief DAC_DHR12LD Register Bit Definition
 */

#define DAC_DHR12LD_DACC2DHR_SHIFT              (20)
#define DAC_DHR12LD_DACC2DHR_MASK               (0xFFFU << DAC_DHR12LD_DACC2DHR_SHIFT)
#define DAC_DHR12LD_DACC2DHR(x)                 (((uint32_t)(((uint32_t)(x)) << DAC_DHR12LD_DACC2DHR_SHIFT)) & DAC_DHR12LD_DACC2DHR_MASK)

#define DAC_DHR12LD_DACC1DHR_SHIFT              (4)
#define DAC_DHR12LD_DACC1DHR_MASK               (0xFFFU << DAC_DHR12LD_DACC1DHR_SHIFT)
#define DAC_DHR12LD_DACC1DHR(x)                 (((uint32_t)(((uint32_t)(x)) << DAC_DHR12LD_DACC1DHR_SHIFT)) & DAC_DHR12LD_DACC1DHR_MASK)

/*!
 * @brief DAC_DHR8RD Register Bit Definition
 */

#define DAC_DHR8RD_DACC2DHR_SHIFT               (8)
#define DAC_DHR8RD_DACC2DHR_MASK                (0xFFU << DAC_DHR8RD_DACC2DHR_SHIFT)
#define DAC_DHR8RD_DACC2DHR(x)                  (((uint32_t)(((uint32_t)(x)) << DAC_DHR8RD_DACC2DHR_SHIFT)) & DAC_DHR8RD_DACC2DHR_MASK)

#define DAC_DHR8RD_DACC1DHR_SHIFT               (0)
#define DAC_DHR8RD_DACC1DHR_MASK                (0xFFU << DAC_DHR8RD_DACC1DHR_SHIFT)
#define DAC_DHR8RD_DACC1DHR(x)                  (((uint32_t)(((uint32_t)(x)) << DAC_DHR8RD_DACC1DHR_SHIFT)) & DAC_DHR8RD_DACC1DHR_MASK)

/*!
 * @brief DAC_DOR1 Register Bit Definition
 */

#define DAC_DOR1_DACC1DOR_SHIFT                 (0)
#define DAC_DOR1_DACC1DOR_MASK                  (0xFFFU << DAC_DOR1_DACC1DOR_SHIFT)
#define DAC_DOR1_DACC1DOR(x)                    (((uint32_t)(((uint32_t)(x)) << DAC_DOR1_DACC1DOR_SHIFT)) & DAC_DOR1_DACC1DOR_MASK)

/*!
 * @brief DAC_DOR2 Register Bit Definition
 */

#define DAC_DOR2_DACC2DOR_SHIFT                 (0)
#define DAC_DOR2_DACC2DOR_MASK                  (0xFFFU << DAC_DOR2_DACC2DOR_SHIFT)
#define DAC_DOR2_DACC2DOR(x)                    (((uint32_t)(((uint32_t)(x)) << DAC_DOR2_DACC2DOR_SHIFT)) & DAC_DOR2_DACC2DOR_MASK)

/*!
 * @}
 */ /* end of group DAC_Register_Masks */
/******************************************************************************
 * DAC Instance
******************************************************************************/
#define DAC                             ((DAC_Type*)DAC_BASE)

/*!
 * @}
 */ /* end of group DAC_Peripheral_Access_Layer */



/*!
 * @addtogroup COMP_Peripheral_Access_Layer COMP Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * COMP Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t Reserved45a[3];                                                 ///< Reserved
    __IO uint32_t CSR[2];                                                         ///< Comparator x (x=1, 2) control and status registeroffset: 0x0C
    __IO uint32_t Reserved45[1];                                                  ///< Reserved
    __IO uint32_t CRV;                                                            ///< Comparator external reference voltage registeroffset: 0x18
    __IO uint32_t POLL[2];                                                        ///< Comparator x (x=1, 2) polling register       offset: 0x1C
} COMP_Type;

/*******************************************************************************
 * COMP Type
 ******************************************************************************/

/*!
 * @addtogroup COMP_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief COMP_CSR Register Bit Definition
 */

#define COMP_CSR_LOCK_SHIFT                     (31)
#define COMP_CSR_LOCK_MASK                      (0x01U << COMP_CSR_LOCK_SHIFT)
#define COMP_CSR_LOCK(x)                        (((uint32_t)(((uint32_t)(x)) << COMP_CSR_LOCK_SHIFT)) & COMP_CSR_LOCK_MASK)

#define COMP_CSR_OUT_SHIFT                      (30)
#define COMP_CSR_OUT_MASK                       (0x01U << COMP_CSR_OUT_SHIFT)
#define COMP_CSR_OUT(x)                         (((uint32_t)(((uint32_t)(x)) << COMP_CSR_OUT_SHIFT)) & COMP_CSR_OUT_MASK)

#define COMP_CSR_OFLT_SHIFT                     (18)
#define COMP_CSR_OFLT_MASK                      (0x7U << COMP_CSR_OFLT_SHIFT)
#define COMP_CSR_OFLT(x)                        (((uint32_t)(((uint32_t)(x)) << COMP_CSR_OFLT_SHIFT)) & COMP_CSR_OFLT_MASK)

#define COMP_CSR_HYST_SHIFT                     (16)
#define COMP_CSR_HYST_MASK                      (0x3U << COMP_CSR_HYST_SHIFT)
#define COMP_CSR_HYST(x)                        (((uint32_t)(((uint32_t)(x)) << COMP_CSR_HYST_SHIFT)) & COMP_CSR_HYST_MASK)

#define COMP_CSR_POL_SHIFT                      (15)
#define COMP_CSR_POL_MASK                       (0x01U << COMP_CSR_POL_SHIFT)
#define COMP_CSR_POL(x)                         (((uint32_t)(((uint32_t)(x)) << COMP_CSR_POL_SHIFT)) & COMP_CSR_POL_MASK)

#define COMP_CSR_OUTSEL_SHIFT                   (10)
#define COMP_CSR_OUTSEL_MASK                    (0xFU << COMP_CSR_OUTSEL_SHIFT)
#define COMP_CSR_OUTSEL(x)                      (((uint32_t)(((uint32_t)(x)) << COMP_CSR_OUTSEL_SHIFT)) & COMP_CSR_OUTSEL_MASK)

#define COMP_CSR_INPSEL_SHIFT                   (7)
#define COMP_CSR_INPSEL_MASK                    (0x3U << COMP_CSR_INPSEL_SHIFT)
#define COMP_CSR_INPSEL(x)                      (((uint32_t)(((uint32_t)(x)) << COMP_CSR_INPSEL_SHIFT)) & COMP_CSR_INPSEL_MASK)

#define COMP_CSR_INMSEL_SHIFT                   (4)
#define COMP_CSR_INMSEL_MASK                    (0x3U << COMP_CSR_INMSEL_SHIFT)
#define COMP_CSR_INMSEL(x)                      (((uint32_t)(((uint32_t)(x)) << COMP_CSR_INMSEL_SHIFT)) & COMP_CSR_INMSEL_MASK)

#define COMP_CSR_MODE_SHIFT                     (2)
#define COMP_CSR_MODE_MASK                      (0x3U << COMP_CSR_MODE_SHIFT)
#define COMP_CSR_MODE(x)                        (((uint32_t)(((uint32_t)(x)) << COMP_CSR_MODE_SHIFT)) & COMP_CSR_MODE_MASK)

#define COMP_CSR_EN_SHIFT                       (0)
#define COMP_CSR_EN_MASK                        (0x01U << COMP_CSR_EN_SHIFT)
#define COMP_CSR_EN(x)                          (((uint32_t)(((uint32_t)(x)) << COMP_CSR_EN_SHIFT)) & COMP_CSR_EN_MASK)

/*!
 * @brief COMP_CRV Register Bit Definition
 */

#define COMP_CRV_CRVSRC_SHIFT                   (5)
#define COMP_CRV_CRVSRC_MASK                    (0x01U << COMP_CRV_CRVSRC_SHIFT)
#define COMP_CRV_CRVSRC(x)                      (((uint32_t)(((uint32_t)(x)) << COMP_CRV_CRVSRC_SHIFT)) & COMP_CRV_CRVSRC_MASK)

#define COMP_CRV_CRVEN_SHIFT                    (4)
#define COMP_CRV_CRVEN_MASK                     (0x01U << COMP_CRV_CRVEN_SHIFT)
#define COMP_CRV_CRVEN(x)                       (((uint32_t)(((uint32_t)(x)) << COMP_CRV_CRVEN_SHIFT)) & COMP_CRV_CRVEN_MASK)

#define COMP_CRV_CRVSEL_SHIFT                   (0)
#define COMP_CRV_CRVSEL_MASK                    (0xFU << COMP_CRV_CRVSEL_SHIFT)
#define COMP_CRV_CRVSEL(x)                      (((uint32_t)(((uint32_t)(x)) << COMP_CRV_CRVSEL_SHIFT)) & COMP_CRV_CRVSEL_MASK)

/*!
 * @brief COMP_POLL Register Bit Definition
 */

#define COMP_POLL_POUT_SHIFT                    (8)
#define COMP_POLL_POUT_MASK                     (0x7U << COMP_POLL_POUT_SHIFT)
#define COMP_POLL_POUT(x)                       (((uint32_t)(((uint32_t)(x)) << COMP_POLL_POUT_SHIFT)) & COMP_POLL_POUT_MASK)

#define COMP_POLL_PERIOD_SHIFT                  (4)
#define COMP_POLL_PERIOD_MASK                   (0x7U << COMP_POLL_PERIOD_SHIFT)
#define COMP_POLL_PERIOD(x)                     (((uint32_t)(((uint32_t)(x)) << COMP_POLL_PERIOD_SHIFT)) & COMP_POLL_PERIOD_MASK)

#define COMP_POLL_FIXN_SHIFT                    (2)
#define COMP_POLL_FIXN_MASK                     (0x01U << COMP_POLL_FIXN_SHIFT)
#define COMP_POLL_FIXN(x)                       (((uint32_t)(((uint32_t)(x)) << COMP_POLL_FIXN_SHIFT)) & COMP_POLL_FIXN_MASK)

#define COMP_POLL_POLLCH_SHIFT                  (1)
#define COMP_POLL_POLLCH_MASK                   (0x01U << COMP_POLL_POLLCH_SHIFT)
#define COMP_POLL_POLLCH(x)                     (((uint32_t)(((uint32_t)(x)) << COMP_POLL_POLLCH_SHIFT)) & COMP_POLL_POLLCH_MASK)

#define COMP_POLL_POLLEN_SHIFT                  (0)
#define COMP_POLL_POLLEN_MASK                   (0x01U << COMP_POLL_POLLEN_SHIFT)
#define COMP_POLL_POLLEN(x)                     (((uint32_t)(((uint32_t)(x)) << COMP_POLL_POLLEN_SHIFT)) & COMP_POLL_POLLEN_MASK)

/*!
 * @}
 */ /* end of group COMP_Register_Masks */
/******************************************************************************
 * COMP Instance
******************************************************************************/
#define COMP                                    ((COMP_Type*)COMP_BASE)

/*!
 * @}
 */ /* end of group COMP_Peripheral_Access_Layer */



/*!
 * @addtogroup CRC_Peripheral_Access_Layer CRC Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * CRC Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t DR;                                                             ///< CRC data register                            offset: 0x00
    __IO uint32_t IDR;                                                            ///< CRC independent data register                offset: 0x04
    __IO uint32_t CTRL;                                                           ///< CRC control register                         offset: 0x08
    __IO uint32_t MIR;                                                            ///< CRC intermediate data register               offset: 0x0C
} CRC_Type;

/*******************************************************************************
 * CRC Type
 ******************************************************************************/

/*!
 * @addtogroup CRC_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief CRC_DR Register Bit Definition
 */

#define CRC_DR_DR_SHIFT                         (0)
#define CRC_DR_DR_MASK                          (0xFFFFFFFFU << CRC_DR_DR_SHIFT)
#define CRC_DR_DR(x)                            (((uint32_t)(((uint32_t)(x)) << CRC_DR_DR_SHIFT)) & CRC_DR_DR_MASK)

/*!
 * @brief CRC_IDR Register Bit Definition
 */

#define CRC_IDR_IDR_SHIFT                       (0)
#define CRC_IDR_IDR_MASK                        (0xFFU << CRC_IDR_IDR_SHIFT)
#define CRC_IDR_IDR(x)                          (((uint32_t)(((uint32_t)(x)) << CRC_IDR_IDR_SHIFT)) & CRC_IDR_IDR_MASK)

/*!
 * @brief CRC_CTRL Register Bit Definition
 */

#define CRC_CTRL_BIGEO_SHIFT                    (5)
#define CRC_CTRL_BIGEO_MASK                     (0x01U << CRC_CTRL_BIGEO_SHIFT)
#define CRC_CTRL_BIGEO(x)                       (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_BIGEO_SHIFT)) & CRC_CTRL_BIGEO_MASK)

#define CRC_CTRL_BIGEI_SHIFT                    (4)
#define CRC_CTRL_BIGEI_MASK                     (0x01U << CRC_CTRL_BIGEI_SHIFT)
#define CRC_CTRL_BIGEI(x)                       (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_BIGEI_SHIFT)) & CRC_CTRL_BIGEI_MASK)

#define CRC_CTRL_CRCBITSEL_SHIFT                (2)
#define CRC_CTRL_CRCBITSEL_MASK                 (0x3U << CRC_CTRL_CRCBITSEL_SHIFT)
#define CRC_CTRL_CRCBITSEL(x)                   (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_CRCBITSEL_SHIFT)) & CRC_CTRL_CRCBITSEL_MASK)

#define CRC_CTRL_POLY32MGN_SHIFT                (1)
#define CRC_CTRL_POLY32MGN_MASK                 (0x01U << CRC_CTRL_POLY32MGN_SHIFT)
#define CRC_CTRL_POLY32MGN(x)                   (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_POLY32MGN_SHIFT)) & CRC_CTRL_POLY32MGN_MASK)

#define CRC_CTRL_RESET_SHIFT                    (0)
#define CRC_CTRL_RESET_MASK                     (0x01U << CRC_CTRL_RESET_SHIFT)
#define CRC_CTRL_RESET(x)                       (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_RESET_SHIFT)) & CRC_CTRL_RESET_MASK)

/*!
 * @brief CRC_MIR Register Bit Definition
 */

#define CRC_MIR_CRCMIR_SHIFT                    (0)
#define CRC_MIR_CRCMIR_MASK                     (0xFFFFFFFFU << CRC_MIR_CRCMIR_SHIFT)
#define CRC_MIR_CRCMIR(x)                       (((uint32_t)(((uint32_t)(x)) << CRC_MIR_CRCMIR_SHIFT)) & CRC_MIR_CRCMIR_MASK)

/*!
 * @}
 */ /* end of group CRC_Register_Masks */
/******************************************************************************
 * CRC Instance
******************************************************************************/
#define CRC                                     ((CRC_Type*)CRC_BASE)

/*!
 * @}
 */ /* end of group CRC_Peripheral_Access_Layer */



/*!
 * @addtogroup DEBUG_Peripheral_Access_Layer DEBUG Peripheral Access Layer
 *  @{
 */

/*******************************************************************************
 * DEBUG Type
 ******************************************************************************/
typedef struct {
    __IO uint32_t CR;                                                             ///< DEBUG control register                       offset: 0x00
} DBG_Type;

/*******************************************************************************
 * DEBUG Type
 ******************************************************************************/

/*!
 * @addtogroup DEBUG_Register_Masks Register Masks
 * @{
 */

/*!
 * @brief DBG_CR Register Bit Definition
 */

#define DBG_CR_DEBUGTIM8STOP_SHIFT            (17)
#define DBG_CR_DEBUGTIM8STOP_MASK             (0xFU << DBG_CR_DEBUGTIM8STOP_SHIFT)
#define DBG_CR_DEBUGTIM8STOP(x)               (((uint32_t)(((uint32_t)(x)) << DBG_CR_DEBUGTIM8STOP_SHIFT)) & DBG_CR_DEBUGTIMXSTOP_MASK)

#define DBG_CR_DEBUGTIM1STOP_SHIFT            (10)
#define DBG_CR_DEBUGTIM1STOP_MASK             (0xFU << DBG_CR_DEBUGTIM1STOP_SHIFT)
#define DBG_CR_DEBUGTIM1STOP(x)               (((uint32_t)(((uint32_t)(x)) << DBG_CR_DEBUGTIM1STOP_SHIFT)) & DBG_CR_DEBUGTIMXSTOP_MASK)

#define DBG_CR_DEBUGWWDGSTOP_SHIFT            (9)
#define DBG_CR_DEBUGWWDGSTOP_MASK             (0x01U << DBG_CR_DEBUGWWDGSTOP_SHIFT)
#define DBG_CR_DEBUGWWDGSTOP(x)               (((uint32_t)(((uint32_t)(x)) << DBG_CR_DEBUGWWDGSTOP_SHIFT)) & DBG_CR_DEBUGWWDGSTOP_MASK)

#define DBG_CR_DEBUGIWDGSTOP_SHIFT            (8)
#define DBG_CR_DEBUGIWDGSTOP_MASK             (0x01U << DBG_CR_DEBUGIWDGSTOP_SHIFT)
#define DBG_CR_DEBUGIWDGSTOP(x)               (((uint32_t)(((uint32_t)(x)) << DBG_CR_DEBUGIWDGSTOP_SHIFT)) & DBG_CR_DEBUGIWDGSTOP_MASK)

#define DBG_CR_DEBUGSTOPFORLDO_SHIFT          (3)
#define DBG_CR_DEBUGSTOPFORLDO_MASK           (0x01U << DBG_CR_DEBUGSTOPFORLDO_SHIFT)
#define DBG_CR_DEBUGSTOPFORLDO(x)             (((uint32_t)(((uint32_t)(x)) << DBG_CR_DEBUGSTOPFORLDO_SHIFT)) & DBG_CR_DEBUGSTOPFORLDO_MASK)

/*!
 * @}
 */ /* end of group DEBUG_Register_Masks */
/******************************************************************************
 * DEBUG Instance
******************************************************************************/
#define DBG                                   ((DBG_Type*)DBG_BASE)

/*!
 * @}
 */ /* end of group DEBUG_Peripheral_Access_Layer */




/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */

#endif /* __MM32F3277G_H__ */
