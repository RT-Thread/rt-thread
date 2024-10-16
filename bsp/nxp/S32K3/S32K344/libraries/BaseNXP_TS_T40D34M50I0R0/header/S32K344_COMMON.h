/*
** ###################################################################
**     Processor:           S32K344
**     Reference manual:    S32K3xx RM Rev.3
**     Version:             rev. 1.9, 2021-10-27
**     Build:               b211026
**
**     Abstract:
**         Peripheral Access Layer for S32K344
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2021 NXP
**
**     NXP Confidential. This software is owned or controlled by NXP and may only be
**     used strictly in accordance with the applicable license terms. By expressly
**     accepting such terms or by downloading, installing, activating and/or otherwise
**     using the software, you are agreeing that you have read, and that you agree to
**     comply with and are bound by, such license terms. If you do not agree to be
**     bound by the applicable license terms, then you may not retain, install,
**     activate or otherwise use the software. The production use license in
**     Section 2.3 is expressly granted for this software.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
** ###################################################################
*/

/*!
 * @file S32K344.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344
 *
 * This file contains register definitions and macros for easy access to their
 * bit fields.
 *
 * This file assumes LITTLE endian system.
 */

/**
* @page misra_violations MISRA-C:2012 violations
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.3, local typedef not referenced
* The SoC header defines typedef for all modules.
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.5, local macro not referenced
* The SoC header defines macros for all modules and registers.
*
* @section [global]
* Violates MISRA 2012 Advisory Directive 4.9, Function-like macro
* These are generated macros used for accessing the bit-fields from registers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.1, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.2, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.4, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.5, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 21.1, defined macro '__I' is reserved to the compiler
* This type qualifier is needed to ensure correct I/O access and addressing.
*/


/* ----------------------------------------------------------------------------
   -- MCU activation
   ---------------------------------------------------------------------------- */

/* Prevention from multiple including the same memory map */
#if !defined(S32K344_COMMON_H_)  /* Check if memory map has not been already included */
#define S32K344_COMMON_H_
#define MCU_S32K344

/* Check if another memory map has not been also included */
#if (defined(MCU_ACTIVE))
  #error S32K344 memory map: There is already included another memory map. Only one memory map can be included.
#endif /* (defined(MCU_ACTIVE)) */
#define MCU_ACTIVE

#include "BasicTypes.h"

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0100U
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0009U

/* ----------------------------------------------------------------------------
   -- Generic macros
   ---------------------------------------------------------------------------- */

/* IO definitions (access restrictions to peripheral registers) */
/**
*   IO Type Qualifiers are used
*   \li to specify the access to peripheral variables.
*   \li for automatic generation of peripheral register debug information.
*/
#ifndef __IO
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */
#endif


/**
* @brief 32 bits memory read macro.
*/
#if !defined(REG_READ32)
  #define REG_READ32(address)               (*(volatile uint32_t*)(address))
#endif

/**
* @brief 32 bits memory write macro.
*/
#if !defined(REG_WRITE32)
  #define REG_WRITE32(address, value)       ((*(volatile uint32_t*)(address))= (uint32_t)(value))
#endif

/**
* @brief 32 bits bits setting macro.
*/
#if !defined(REG_BIT_SET32)
  #define REG_BIT_SET32(address, mask)      ((*(volatile uint32_t*)(address))|= (uint32_t)(mask))
#endif

/**
* @brief 32 bits bits clearing macro.
*/
#if !defined(REG_BIT_CLEAR32)
  #define REG_BIT_CLEAR32(address, mask)    ((*(volatile uint32_t*)(address))&= ((uint32_t)~((uint32_t)(mask))))
#endif

/**
* @brief 32 bit clear bits and set with new value
* @note It is user's responsability to make sure that value has only "mask" bits set - (value&~mask)==0
*/
#if !defined(REG_RMW32)
  #define REG_RMW32(address, mask, value)   (REG_WRITE32((address), ((REG_READ32(address)& ((uint32_t)~((uint32_t)(mask))))| ((uint32_t)(value)))))
#endif


/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS 229                /**< Number of interrupts in the Vector table */

typedef enum {
  /* Auxiliary constants */
  NotAvail_IRQn                = -128,             /**< Not available device specific interrupt */

  /* Core interrupts */
  NonMaskableInt_IRQn          = -14,              /**< Non Maskable Interrupt */
  HardFault_IRQn               = -13,              /**< Cortex-M7 SV Hard Fault Interrupt */
  MemoryManagement_IRQn        = -12,              /**< Cortex-M7 Memory Management Interrupt */
  BusFault_IRQn                = -11,              /**< Cortex-M7 Bus Fault Interrupt */
  UsageFault_IRQn              = -10,              /**< Cortex-M7 Usage Fault Interrupt */
  SVCall_IRQn                  = -5,               /**< Cortex-M7 SV Call Interrupt */
  DebugMonitor_IRQn            = -4,               /**< Cortex-M7 Debug Monitor Interrupt */
  PendSV_IRQn                  = -2,               /**< Cortex-M7 Pend SV Interrupt */
  SysTick_IRQn                 = -1,               /**< Cortex-M7 System Tick Interrupt */

  /* Device specific interrupts */
  INT0_IRQn                    = 0,                /**< CPU to CPU int0 */
  INT1_IRQn                    = 1,                /**< CPU to CPU int1 */
  INT2_IRQn                    = 2,                /**< CPU to CPU int2 */
  INT3_IRQn                    = 3,                /**< CPU to CPU int3 */
  DMATCD0_IRQn                 = 4,                /**< DMA transfer complete and error CH0 */
  DMATCD1_IRQn                 = 5,                /**< DMA transfer complete and error CH1 */
  DMATCD2_IRQn                 = 6,                /**< DMA transfer complete and error CH2 */
  DMATCD3_IRQn                 = 7,                /**< DMA transfer complete and error CH3 */
  DMATCD4_IRQn                 = 8,                /**< DMA transfer complete and error CH4 */
  DMATCD5_IRQn                 = 9,                /**< DMA transfer complete and error CH5 */
  DMATCD6_IRQn                 = 10,               /**< DMA transfer complete and error CH6 */
  DMATCD7_IRQn                 = 11,               /**< DMA transfer complete and error CH7 */
  DMATCD8_IRQn                 = 12,               /**< DMA transfer complete and error CH8 */
  DMATCD9_IRQn                 = 13,               /**< DMA transfer complete and error CH9 */
  DMATCD10_IRQn                = 14,               /**< DMA transfer complete and error CH10 */
  DMATCD11_IRQn                = 15,               /**< DMA transfer complete and error CH11 */
  DMATCD12_IRQn                = 16,               /**< DMA transfer complete and error CH12 */
  DMATCD13_IRQn                = 17,               /**< DMA transfer complete and error CH13 */
  DMATCD14_IRQn                = 18,               /**< DMA transfer complete and error CH14 */
  DMATCD15_IRQn                = 19,               /**< DMA transfer complete and error CH15 */
  DMATCD16_IRQn                = 20,               /**< DMA transfer complete and error CH16 */
  DMATCD17_IRQn                = 21,               /**< DMA transfer complete and error CH17 */
  DMATCD18_IRQn                = 22,               /**< DMA transfer complete and error CH18 */
  DMATCD19_IRQn                = 23,               /**< DMA transfer complete and error CH19 */
  DMATCD20_IRQn                = 24,               /**< DMA transfer complete and error CH20 */
  DMATCD21_IRQn                = 25,               /**< DMA transfer complete and error CH21 */
  DMATCD22_IRQn                = 26,               /**< DMA transfer complete and error CH22 */
  DMATCD23_IRQn                = 27,               /**< DMA transfer complete and error CH23 */
  DMATCD24_IRQn                = 28,               /**< DMA transfer complete and error CH24 */
  DMATCD25_IRQn                = 29,               /**< DMA transfer complete and error CH25 */
  DMATCD26_IRQn                = 30,               /**< DMA transfer complete and error CH26 */
  DMATCD27_IRQn                = 31,               /**< DMA transfer complete and error CH27 */
  DMATCD28_IRQn                = 32,               /**< DMA transfer complete and error CH28 */
  DMATCD29_IRQn                = 33,               /**< DMA transfer complete and error CH29 */
  DMATCD30_IRQn                = 34,               /**< DMA transfer complete and error CH30 */
  DMATCD31_IRQn                = 35,               /**< DMA transfer complete and error CH31 */
  ERM_0_IRQn                   = 36,               /**< Single bit ECC error */
  ERM_1_IRQn                   = 37,               /**< Multi bit ECC error */
  MCM_IRQn                     = 38,               /**< Multi bit ECC error */
  STM0_IRQn                    = 39,               /**< Single interrupt vector for all four channels */
  STM1_IRQn                    = 40,               /**< Single interrupt vector for all four channels */
  SWT0_IRQn                    = 42,               /**< Platform watchdog initial time-out */
  CTI0_IRQn                    = 45,               /**< CTI Interrupt 0 */
  FLASH_0_IRQn                 = 48,               /**< Program or erase operation is completed */
  FLASH_1_IRQn                 = 49,               /**< Main watchdog timeout interrupt */
  FLASH_2_IRQn                 = 50,               /**< Alternate watchdog timeout interrupt */
  RGM_IRQn                     = 51,               /**< Interrupt request to the system */
  PMC_IRQn                     = 52,               /**< One interrupt for all LVDs, One interrupt for all HVDs */
  SIUL_0_IRQn                  = 53,               /**< External Interrupt Vector 0 */
  SIUL_1_IRQn                  = 54,               /**< External Interrupt Vector 1 */
  SIUL_2_IRQn                  = 55,               /**< External Interrupt Vector 2 */
  SIUL_3_IRQn                  = 56,               /**< External Interrupt Vector 3 */
  EMIOS0_0_IRQn                = 61,               /**< Interrupt request 23,22,21,20 */
  EMIOS0_1_IRQn                = 62,               /**< Interrupt request 19,18,17,16 */
  EMIOS0_2_IRQn                = 63,               /**< Interrupt request 15,14,13,12 */
  EMIOS0_3_IRQn                = 64,               /**< Interrupt request 11,10,9,8 */
  EMIOS0_4_IRQn                = 65,               /**< Interrupt request 7,6,5,4 */
  EMIOS0_5_IRQn                = 66,               /**< Interrupt request 3,2,1,0 */
  EMIOS1_0_IRQn                = 69,               /**< Interrupt request 23,22,21,20 */
  EMIOS1_1_IRQn                = 70,               /**< Interrupt request 19,18,17,16 */
  EMIOS1_2_IRQn                = 71,               /**< Interrupt request 15,14,13,12 */
  EMIOS1_3_IRQn                = 72,               /**< Interrupt request 11,10,9,8 */
  EMIOS1_4_IRQn                = 73,               /**< Interrupt request 7,6,5,4 */
  EMIOS1_5_IRQn                = 74,               /**< Interrupt request 3,2,1,0 */
  EMIOS2_0_IRQn                = 77,               /**< Interrupt request 23,22,21,20 */
  EMIOS2_1_IRQn                = 78,               /**< Interrupt request 19,18,17,16 */
  EMIOS2_2_IRQn                = 79,               /**< Interrupt request 15,14,13,12 */
  EMIOS2_3_IRQn                = 80,               /**< Interrupt request 11,10,9,8 */
  EMIOS2_4_IRQn                = 81,               /**< Interrupt request 7,6,5,4 */
  EMIOS2_5_IRQn                = 82,               /**< Interrupt request 3,2,1,0 */
  WKPU_IRQn                    = 83,               /**< Interrupts from pad group 0,1,2,3, Interrupts from pad group 0_64, Interrupts from pad group 1_64, Interrupts from pad group 2_64, Interrupts from pad group 3_64 */
  CMU0_IRQn                    = 84,               /**< CMU0 interrupt */
  CMU1_IRQn                    = 85,               /**< CMU1 interrupt */
  CMU2_IRQn                    = 86,               /**< CMU2 interrupt */
  BCTU_IRQn                    = 87,               /**< An interrupt is requested when a conversion is issued to the ADC, An interrupt is requested when new data is available from ADC0 conversion, An interrupt is requested when new data is available from ADC1 conversion, An interrupt is requested when new data is available from ADC2 conversion, An interrupt is requested when the last command of a list is issued to the ADC,An Interrupt output for FIFO1,An Interrupt output for FIFO2 */
  LCU0_IRQn                    = 92,               /**< Interrupt 0, Interrupt 1 Interrupt 2 */
  LCU1_IRQn                    = 93,               /**< Interrupt 0, Interrupt 1 Interrupt 2 */
  PIT0_IRQn                    = 96,               /**< Interrupt for Channel0,Interrupt for Channel1,Interrupt for Channel2,Interrupt for Channel3,Interrupt for Channel4 */
  PIT1_IRQn                    = 97,               /**< Interrupt for Channel0,Interrupt for Channel1,Interrupt for Channel2,Interrupt for Channel3 */
  PIT2_IRQn                    = 98,               /**< Interrupt for Channel0,Interrupt for Channel1,Interrupt for Channel2,Interrupt for Channel3 */
  RTC_IRQn                     = 102,              /**< RTCF or ROVRF interrupt to be serviced by the system controller, APIF interrupt to be serviced by the system controller */
  EMAC_0_IRQn                  = 105,              /**< Common interrupt */
  EMAC_1_IRQn                  = 106,              /**< Tx interrupt 0, Tx interrupt 1 */
  EMAC_2_IRQn                  = 107,              /**< Rx interrupt 0, Rx interrupt 1 */
  EMAC_3_IRQn                  = 108,              /**< Safety interrupt correctable, Safety interrupt un-correctable */
  FlexCAN0_0_IRQn              = 109,              /**< Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN0_1_IRQn              = 110,              /**< Message Buffer Interrupt line 0-31,ORed Interrupt for Message Buffers */
  FlexCAN0_2_IRQn              = 111,              /**< Message Buffer Interrupt line 32-63 */
  FlexCAN0_3_IRQn              = 112,              /**< Message Buffer Interrupt line 64-95 */
  FlexCAN1_0_IRQn              = 113,              /**< Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN1_1_IRQn              = 114,              /**< Message Buffer Interrupt line 0-31 */
  FlexCAN1_2_IRQn              = 115,              /**< Message Buffer Interrupt line 32-63 */
  FlexCAN2_0_IRQn              = 116,              /**< Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN2_1_IRQn              = 117,              /**< Message Buffer Interrupt line 0-31 */
  FlexCAN2_2_IRQn              = 118,              /**< Message Buffer Interrupt line 32-63 */
  FlexCAN3_0_IRQn              = 119,              /**< Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN3_1_IRQn              = 120,              /**< Message Buffer Interrupt line 0-31 */
  FlexCAN4_0_IRQn              = 121,              /**< Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN4_1_IRQn              = 122,              /**< Message Buffer Interrupt line 0-31 */
  FlexCAN5_0_IRQn              = 123,              /**< Interrupt indicating that the CAN bus went to Bus Off state */
  FlexCAN5_1_IRQn              = 124,              /**< Message Buffer Interrupt line 0-31 */
  FLEXIO_IRQn                  = 139,              /**< FlexIO Interrupt */
  LPUART0_IRQn                 = 141,              /**< TX and RX interrupt */
  LPUART1_IRQn                 = 142,              /**< TX and RX interrupt */
  LPUART2_IRQn                 = 143,              /**< TX and RX interrupt */
  LPUART3_IRQn                 = 144,              /**< TX and RX interrupt */
  LPUART4_IRQn                 = 145,              /**< TX and RX interrupt */
  LPUART5_IRQn                 = 146,              /**< TX and RX interrupt */
  LPUART6_IRQn                 = 147,              /**< TX and RX interrupt */
  LPUART7_IRQn                 = 148,              /**< TX and RX interrupt */
  LPUART8_IRQn                 = 149,              /**< TX and RX interrupt */
  LPUART9_IRQn                 = 150,              /**< TX and RX interrupt */
  LPUART10_IRQn                = 151,              /**< TX and RX interrupt */
  LPUART11_IRQn                = 152,              /**< TX and RX interrupt */
  LPUART12_IRQn                = 153,              /**< TX and RX interrupt */
  LPUART13_IRQn                = 154,              /**< TX and RX interrupt */
  LPUART14_IRQn                = 155,              /**< TX and RX interrupt */
  LPUART15_IRQn                = 156,              /**< TX and RX interrupt */
  LPI2C0_IRQn                  = 161,              /**< LPI2C Master Interrupt, LPI2C Interrupt */
  LPI2C1_IRQn                  = 162,              /**< LPI2C Master Interrupt, LPI2C Interrupt */
  LPSPI0_IRQn                  = 165,              /**< LPSPI Interrupt */
  LPSPI1_IRQn                  = 166,              /**< LPSPI Interrupt */
  LPSPI2_IRQn                  = 167,              /**< LPSPI Interrupt */
  LPSPI3_IRQn                  = 168,              /**< LPSPI Interrupt */
  LPSPI4_IRQn                  = 169,              /**< LPSPI Interrupt */
  LPSPI5_IRQn                  = 170,              /**< LPSPI Interrupt */
  QSPI_IRQn                    = 173,              /**< TX Buffer Fill interrupt, Transfer Complete / Transaction Finished, RX Buffer Drain interrupt, Buffer Overflow / Underrun interrupt, Serial Flash Communication Error interrupt, All interrupts ORed output */
  SAI0_IRQn                    = 174,              /**< RX interrupt,TX interrupt */
  SAI1_IRQn                    = 175,              /**< RX interrupt,TX interrupt */
  JDC_IRQn                     = 178,              /**< Indicates new data to be read from JIN_IPS register or can be written to JOUT_IPS register */
  ADC0_IRQn                    = 180,              /**< End of conversion, Error interrupt, Watchdog interrupt */
  ADC1_IRQn                    = 181,              /**< End of conversion, Error interrupt, Watchdog interrupt */
  ADC2_IRQn                    = 182,              /**< End of conversion, Error interrupt, Watchdog interrupt */
  LPCMP0_IRQn                  = 183,              /**< Async interrupt */
  LPCMP1_IRQn                  = 184,              /**< Async interrupt */
  LPCMP2_IRQn                  = 185,              /**< Async interrupt */
  FCCU_0_IRQn                  = 189,              /**< Interrupt request(ALARM state) */
  FCCU_1_IRQn                  = 190,              /**< Interrupt request(miscellaneous conditions) */
  STCU_LBIST_MBIST_IRQn        = 191,              /**< Interrupt request(miscellaneous conditions) */
  HSE_MU0_TX_IRQn              = 192,              /**< ORed TX interrupt to MU-0 */
  HSE_MU0_RX_IRQn              = 193,              /**< ORed RX interrupt to MU-0 */
  HSE_MU0_ORED_IRQn            = 194,              /**< ORed general purpose interrupt request to MU-0 */
  HSE_MU1_TX_IRQn              = 195,              /**< ORed TX interrupt to MU-1 */
  HSE_MU1_RX_IRQn              = 196,              /**< ORed RX interrupt to MU-1 */
  HSE_MU1_ORED_IRQn            = 197,              /**< ORed general purpose interrupt request to MU-1 */
  SoC_PLL_IRQn                 = 212               /**< PLL LOL interrupt */
} IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Cortex M7 Core Configuration
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Cortex_Core_Configuration Cortex M7 Core Configuration
 * @{
 */

#define __MPU_PRESENT                  1         /**< Defines if an MPU is present or not */
#define __ICACHE_PRESENT               1         /**< Defines if an ICACHE is present or not */
#define __DCACHE_PRESENT               1         /**< Defines if an DCACHE is present or not */
#define __DTCM_PRESENT                 1         /**< Defines if an DTCM is present or not */
#define __NVIC_PRIO_BITS               4         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig         0         /**< Vendor specific implementation of SysTickConfig is defined */
#define __FPU_PRESENT                  1         /**< Defines if an FPU is present or not */


/*!
 * @}
 */ /* end of group Cortex_Core_Configuration */


/* ----------------------------------------------------------------------------
   -- SDK Compatibility
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SDK_Compatibility_Symbols SDK Compatibility
 * @{
 */

/* No SDK compatibility issues. */

/*!
 * @}
 */ /* end of group SDK_Compatibility_Symbols */


#endif  /* #if !defined(S32K344_COMMON_H_) */

