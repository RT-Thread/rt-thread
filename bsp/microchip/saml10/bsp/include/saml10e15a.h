/**
 * \file
 *
 * \brief Header file for ATSAML10E15A
 *
 * Copyright (c) 2019 Microchip Technology Inc.
 *
 * \license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
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
 *
 * \license_stop
 *
 */

/* file generated from device description version 2019-01-31T14:29:25Z */
#ifndef _SAML10E15A_H_
#define _SAML10E15A_H_

/** \addtogroup SAML10E15A_definitions SAML10E15A definitions
  This file defines all structures and symbols for SAML10E15A:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
 *  @{
 */

#ifdef __cplusplus
 extern "C" {
#endif

/** \defgroup Atmel_glob_defs Atmel Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.

    \remark
    CMSIS core has a syntax that differs from this using i.e. __I, __O, or __IO followed by 'uint<size>_t' respective types.
    Default the header files will follow the CMSIS core syntax.
 *  @{
 */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#include <stdint.h>

/* IO definitions (access restrictions to peripheral registers) */
#ifndef __cplusplus
typedef volatile const uint32_t RoReg;   /**< Read only 32-bit register (volatile const unsigned int) */
typedef volatile const uint16_t RoReg16; /**< Read only 16-bit register (volatile const unsigned int) */
typedef volatile const uint8_t  RoReg8;  /**< Read only  8-bit register (volatile const unsigned int) */
#else
typedef volatile       uint32_t RoReg;   /**< Read only 32-bit register (volatile const unsigned int) */
typedef volatile       uint16_t RoReg16; /**< Read only 16-bit register (volatile const unsigned int) */
typedef volatile       uint8_t  RoReg8;  /**< Read only  8-bit register (volatile const unsigned int) */
#endif
typedef volatile       uint32_t WoReg;   /**< Write only 32-bit register (volatile unsigned int) */
typedef volatile       uint16_t WoReg16; /**< Write only 16-bit register (volatile unsigned int) */
typedef volatile       uint8_t  WoReg8;  /**< Write only  8-bit register (volatile unsigned int) */
typedef volatile       uint32_t RwReg;   /**< Read-Write 32-bit register (volatile unsigned int) */
typedef volatile       uint16_t RwReg16; /**< Read-Write 16-bit register (volatile unsigned int) */
typedef volatile       uint8_t  RwReg8;  /**< Read-Write  8-bit register (volatile unsigned int) */

#define CAST(type, value) ((type *)(value)) /**< Pointer Type Conversion Macro for C/C++ */
#define REG_ACCESS(type, address) (*(type*)(address)) /**< C code: Register value */
#else /* Assembler */
#define CAST(type, value) (value) /**< Pointer Type Conversion Macro for Assembler */
#define REG_ACCESS(type, address) (address) /**< Assembly code: Register address */
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#if !defined(SKIP_INTEGER_LITERALS)

#if defined(_U_) || defined(_L_) || defined(_UL_)
  #error "Integer Literals macros already defined elsewhere"
#endif

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/* Macros that deal with adding suffixes to integer literal constants for C/C++ */
#define _U_(x) x ## U    /**< C code: Unsigned integer literal constant value */
#define _L_(x) x ## L    /**< C code: Long integer literal constant value */
#define _UL_(x) x ## UL  /**< C code: Unsigned Long integer literal constant value */

#else /* Assembler */

#define _U_(x) x    /**< Assembler: Unsigned integer literal constant value */
#define _L_(x) x    /**< Assembler: Long integer literal constant value */
#define _UL_(x) x   /**< Assembler: Unsigned Long integer literal constant value */
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* SKIP_INTEGER_LITERALS */
/** @}  end of Atmel Global Defines */

/** \addtogroup SAML10E15A_cmsis CMSIS Definitions
 *  @{
 */
/* ************************************************************************** */
/*   CMSIS DEFINITIONS FOR SAML10E15A */
/* ************************************************************************** */
#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** Interrupt Number Definition */
typedef enum IRQn
{
/******  CORTEX-M23 Processor Exceptions Numbers ******************************/
  Reset_IRQn                = -15, /**< 1   Reset Vector, invoked on Power up and warm reset  */
  NonMaskableInt_IRQn       = -14, /**< 2   Non maskable Interrupt, cannot be stopped or preempted  */
  HardFault_IRQn            = -13, /**< 3   Hard Fault, all classes of Fault     */
  SVCall_IRQn               = -5 , /**< 11  System Service Call via SVC instruction  */
  PendSV_IRQn               = -2 , /**< 14  Pendable request for system service  */
  SysTick_IRQn              = -1 , /**< 15  System Tick Timer                    */
/******  SAML10E15A specific Interrupt Numbers ***********************************/
  SYSTEM_IRQn               = 0  , /**< 0   SAML10E15A Main Clock (MCLK)        */
  WDT_IRQn                  = 1  , /**< 1   SAML10E15A Watchdog Timer (WDT)     */
  RTC_IRQn                  = 2  , /**< 2   SAML10E15A Real-Time Counter (RTC)  */
  EIC_0_IRQn                = 3  , /**< 3   SAML10E15A External Interrupt Controller (EIC) */
  EIC_1_IRQn                = 4  , /**< 4   SAML10E15A External Interrupt Controller (EIC) */
  EIC_2_IRQn                = 5  , /**< 5   SAML10E15A External Interrupt Controller (EIC) */
  EIC_3_IRQn                = 6  , /**< 6   SAML10E15A External Interrupt Controller (EIC) */
  EIC_OTHER_IRQn            = 7  , /**< 7   SAML10E15A External Interrupt Controller (EIC) */
  FREQM_IRQn                = 8  , /**< 8   SAML10E15A Frequency Meter (FREQM)  */
  NVMCTRL_IRQn              = 9  , /**< 9   SAML10E15A Non-Volatile Memory Controller (NVMCTRL) */
  PORT_IRQn                 = 10 , /**< 10  SAML10E15A Port Module (PORT)       */
  DMAC_0_IRQn               = 11 , /**< 11  SAML10E15A Direct Memory Access Controller (DMAC) */
  DMAC_1_IRQn               = 12 , /**< 12  SAML10E15A Direct Memory Access Controller (DMAC) */
  DMAC_2_IRQn               = 13 , /**< 13  SAML10E15A Direct Memory Access Controller (DMAC) */
  DMAC_3_IRQn               = 14 , /**< 14  SAML10E15A Direct Memory Access Controller (DMAC) */
  DMAC_OTHER_IRQn           = 15 , /**< 15  SAML10E15A Direct Memory Access Controller (DMAC) */
  EVSYS_0_IRQn              = 16 , /**< 16  SAML10E15A Event System Interface (EVSYS) */
  EVSYS_1_IRQn              = 17 , /**< 17  SAML10E15A Event System Interface (EVSYS) */
  EVSYS_2_IRQn              = 18 , /**< 18  SAML10E15A Event System Interface (EVSYS) */
  EVSYS_3_IRQn              = 19 , /**< 19  SAML10E15A Event System Interface (EVSYS) */
  EVSYS_NSCHK_IRQn          = 20 , /**< 20  SAML10E15A Event System Interface (EVSYS) */
  PAC_IRQn                  = 21 , /**< 21  SAML10E15A Peripheral Access Controller (PAC) */
  SERCOM0_0_IRQn            = 22 , /**< 22  SAML10E15A Serial Communication Interface (SERCOM0) */
  SERCOM0_1_IRQn            = 23 , /**< 23  SAML10E15A Serial Communication Interface (SERCOM0) */
  SERCOM0_2_IRQn            = 24 , /**< 24  SAML10E15A Serial Communication Interface (SERCOM0) */
  SERCOM0_OTHER_IRQn        = 25 , /**< 25  SAML10E15A Serial Communication Interface (SERCOM0) */
  SERCOM1_0_IRQn            = 26 , /**< 26  SAML10E15A Serial Communication Interface (SERCOM1) */
  SERCOM1_1_IRQn            = 27 , /**< 27  SAML10E15A Serial Communication Interface (SERCOM1) */
  SERCOM1_2_IRQn            = 28 , /**< 28  SAML10E15A Serial Communication Interface (SERCOM1) */
  SERCOM1_OTHER_IRQn        = 29 , /**< 29  SAML10E15A Serial Communication Interface (SERCOM1) */
  SERCOM2_0_IRQn            = 30 , /**< 30  SAML10E15A Serial Communication Interface (SERCOM2) */
  SERCOM2_1_IRQn            = 31 , /**< 31  SAML10E15A Serial Communication Interface (SERCOM2) */
  SERCOM2_2_IRQn            = 32 , /**< 32  SAML10E15A Serial Communication Interface (SERCOM2) */
  SERCOM2_OTHER_IRQn        = 33 , /**< 33  SAML10E15A Serial Communication Interface (SERCOM2) */
  TC0_IRQn                  = 34 , /**< 34  SAML10E15A Basic Timer Counter (TC0) */
  TC1_IRQn                  = 35 , /**< 35  SAML10E15A Basic Timer Counter (TC1) */
  TC2_IRQn                  = 36 , /**< 36  SAML10E15A Basic Timer Counter (TC2) */
  ADC_OTHER_IRQn            = 37 , /**< 37  SAML10E15A Analog Digital Converter (ADC) */
  ADC_RESRDY_IRQn           = 38 , /**< 38  SAML10E15A Analog Digital Converter (ADC) */
  AC_IRQn                   = 39 , /**< 39  SAML10E15A Analog Comparators (AC)  */
  DAC_UNDERRUN_A_IRQn       = 40 , /**< 40  SAML10E15A Digital Analog Converter (DAC) */
  DAC_EMPTY_IRQn            = 41 , /**< 41  SAML10E15A Digital Analog Converter (DAC) */
  PTC_IRQn                  = 42 , /**< 42  SAML10E15A Peripheral Touch Controller (PTC) */
  TRNG_IRQn                 = 43 , /**< 43  SAML10E15A True Random Generator (TRNG) */
  TRAM_IRQn                 = 44 , /**< 44  SAML10E15A TrustRAM (TRAM)          */

  PERIPH_COUNT_IRQn        = 45  /**< Number of peripheral IDs */
} IRQn_Type;
#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct _DeviceVectors
{
  /* Stack pointer */
  void* pvStack;
  /* Cortex-M handlers */
  void* pfnReset_Handler;                        /* -15 Reset Vector, invoked on Power up and warm reset  */
  void* pfnNonMaskableInt_Handler;               /* -14 Non maskable Interrupt, cannot be stopped or preempted  */
  void* pfnHardFault_Handler;                    /* -13 Hard Fault, all classes of Fault     */
  void* pvReservedC12;
  void* pvReservedC11;
  void* pvReservedC10;
  void* pvReservedC9;
  void* pvReservedC8;
  void* pvReservedC7;
  void* pvReservedC6;
  void* pfnSVCall_Handler;                       /*  -5 System Service Call via SVC instruction  */
  void* pvReservedC4;
  void* pvReservedC3;
  void* pfnPendSV_Handler;                       /*  -2 Pendable request for system service  */
  void* pfnSysTick_Handler;                      /*  -1 System Tick Timer                    */


  /* Peripheral handlers */
  void* pfnSYSTEM_Handler;                       /* 0   SAML10E15A Main Clock (MCLK)   */
  void* pfnWDT_Handler;                          /* 1   SAML10E15A Watchdog Timer (WDT) */
  void* pfnRTC_Handler;                          /* 2   SAML10E15A Real-Time Counter (RTC) */
  void* pfnEIC_0_Handler;                        /* 3   SAML10E15A External Interrupt Controller (EIC) */
  void* pfnEIC_1_Handler;                        /* 4   SAML10E15A External Interrupt Controller (EIC) */
  void* pfnEIC_2_Handler;                        /* 5   SAML10E15A External Interrupt Controller (EIC) */
  void* pfnEIC_3_Handler;                        /* 6   SAML10E15A External Interrupt Controller (EIC) */
  void* pfnEIC_OTHER_Handler;                    /* 7   SAML10E15A External Interrupt Controller (EIC) */
  void* pfnFREQM_Handler;                        /* 8   SAML10E15A Frequency Meter (FREQM) */
  void* pfnNVMCTRL_Handler;                      /* 9   SAML10E15A Non-Volatile Memory Controller (NVMCTRL) */
  void* pfnPORT_Handler;                         /* 10  SAML10E15A Port Module (PORT)  */
  void* pfnDMAC_0_Handler;                       /* 11  SAML10E15A Direct Memory Access Controller (DMAC) */
  void* pfnDMAC_1_Handler;                       /* 12  SAML10E15A Direct Memory Access Controller (DMAC) */
  void* pfnDMAC_2_Handler;                       /* 13  SAML10E15A Direct Memory Access Controller (DMAC) */
  void* pfnDMAC_3_Handler;                       /* 14  SAML10E15A Direct Memory Access Controller (DMAC) */
  void* pfnDMAC_OTHER_Handler;                   /* 15  SAML10E15A Direct Memory Access Controller (DMAC) */
  void* pfnEVSYS_0_Handler;                      /* 16  SAML10E15A Event System Interface (EVSYS) */
  void* pfnEVSYS_1_Handler;                      /* 17  SAML10E15A Event System Interface (EVSYS) */
  void* pfnEVSYS_2_Handler;                      /* 18  SAML10E15A Event System Interface (EVSYS) */
  void* pfnEVSYS_3_Handler;                      /* 19  SAML10E15A Event System Interface (EVSYS) */
  void* pfnEVSYS_NSCHK_Handler;                  /* 20  SAML10E15A Event System Interface (EVSYS) */
  void* pfnPAC_Handler;                          /* 21  SAML10E15A Peripheral Access Controller (PAC) */
  void* pfnSERCOM0_0_Handler;                    /* 22  SAML10E15A Serial Communication Interface (SERCOM0) */
  void* pfnSERCOM0_1_Handler;                    /* 23  SAML10E15A Serial Communication Interface (SERCOM0) */
  void* pfnSERCOM0_2_Handler;                    /* 24  SAML10E15A Serial Communication Interface (SERCOM0) */
  void* pfnSERCOM0_OTHER_Handler;                /* 25  SAML10E15A Serial Communication Interface (SERCOM0) */
  void* pfnSERCOM1_0_Handler;                    /* 26  SAML10E15A Serial Communication Interface (SERCOM1) */
  void* pfnSERCOM1_1_Handler;                    /* 27  SAML10E15A Serial Communication Interface (SERCOM1) */
  void* pfnSERCOM1_2_Handler;                    /* 28  SAML10E15A Serial Communication Interface (SERCOM1) */
  void* pfnSERCOM1_OTHER_Handler;                /* 29  SAML10E15A Serial Communication Interface (SERCOM1) */
  void* pfnSERCOM2_0_Handler;                    /* 30  SAML10E15A Serial Communication Interface (SERCOM2) */
  void* pfnSERCOM2_1_Handler;                    /* 31  SAML10E15A Serial Communication Interface (SERCOM2) */
  void* pfnSERCOM2_2_Handler;                    /* 32  SAML10E15A Serial Communication Interface (SERCOM2) */
  void* pfnSERCOM2_OTHER_Handler;                /* 33  SAML10E15A Serial Communication Interface (SERCOM2) */
  void* pfnTC0_Handler;                          /* 34  SAML10E15A Basic Timer Counter (TC0) */
  void* pfnTC1_Handler;                          /* 35  SAML10E15A Basic Timer Counter (TC1) */
  void* pfnTC2_Handler;                          /* 36  SAML10E15A Basic Timer Counter (TC2) */
  void* pfnADC_OTHER_Handler;                    /* 37  SAML10E15A Analog Digital Converter (ADC) */
  void* pfnADC_RESRDY_Handler;                   /* 38  SAML10E15A Analog Digital Converter (ADC) */
  void* pfnAC_Handler;                           /* 39  SAML10E15A Analog Comparators (AC) */
  void* pfnDAC_UNDERRUN_A_Handler;               /* 40  SAML10E15A Digital Analog Converter (DAC) */
  void* pfnDAC_EMPTY_Handler;                    /* 41  SAML10E15A Digital Analog Converter (DAC) */
  void* pfnPTC_Handler;                          /* 42  SAML10E15A Peripheral Touch Controller (PTC) */
  void* pfnTRNG_Handler;                         /* 43  SAML10E15A True Random Generator (TRNG) */
  void* pfnTRAM_Handler;                         /* 44  SAML10E15A TrustRAM (TRAM)     */
} DeviceVectors;

/* Defines for Deprecated Interrupt and Exceptions handler names */
#define pfnMemManage_Handler      pfnMemoryManagement_Handler     /**< \deprecated  Backward compatibility for ASF */
#define pfnDebugMon_Handler       pfnDebugMonitor_Handler         /**< \deprecated  Backward compatibility for ASF */
#define pfnNMI_Handler            pfnNonMaskableInt_Handler       /**< \deprecated  Backward compatibility for ASF */
#define pfnSVC_Handler            pfnSVCall_Handler               /**< \deprecated  Backward compatibility for ASF */

#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#if !defined DONT_USE_PREDEFINED_CORE_HANDLERS

/* CORTEX-M23 core handlers */
void Reset_Handler                 ( void );
void NonMaskableInt_Handler        ( void );
void HardFault_Handler             ( void );
void SVCall_Handler                ( void );
void PendSV_Handler                ( void );
void SysTick_Handler               ( void );
#endif /* DONT_USE_PREDEFINED_CORE_HANDLERS */

#if !defined DONT_USE_PREDEFINED_PERIPHERALS_HANDLERS

/* Peripherals handlers */
void AC_Handler                    ( void );
void ADC_OTHER_Handler             ( void );
void ADC_RESRDY_Handler            ( void );
void DAC_EMPTY_Handler             ( void );
void DAC_UNDERRUN_A_Handler        ( void );
void DMAC_0_Handler                ( void );
void DMAC_1_Handler                ( void );
void DMAC_2_Handler                ( void );
void DMAC_3_Handler                ( void );
void DMAC_OTHER_Handler            ( void );
void EIC_0_Handler                 ( void );
void EIC_1_Handler                 ( void );
void EIC_2_Handler                 ( void );
void EIC_3_Handler                 ( void );
void EIC_OTHER_Handler             ( void );
void EVSYS_0_Handler               ( void );
void EVSYS_1_Handler               ( void );
void EVSYS_2_Handler               ( void );
void EVSYS_3_Handler               ( void );
void EVSYS_NSCHK_Handler           ( void );
void FREQM_Handler                 ( void );
void NVMCTRL_Handler               ( void );
void PAC_Handler                   ( void );
void PORT_Handler                  ( void );
void PTC_Handler                   ( void );
void RTC_Handler                   ( void );
void SERCOM0_0_Handler             ( void );
void SERCOM0_1_Handler             ( void );
void SERCOM0_2_Handler             ( void );
void SERCOM0_OTHER_Handler         ( void );
void SERCOM1_0_Handler             ( void );
void SERCOM1_1_Handler             ( void );
void SERCOM1_2_Handler             ( void );
void SERCOM1_OTHER_Handler         ( void );
void SERCOM2_0_Handler             ( void );
void SERCOM2_1_Handler             ( void );
void SERCOM2_2_Handler             ( void );
void SERCOM2_OTHER_Handler         ( void );
void SYSTEM_Handler                ( void );
void TC0_Handler                   ( void );
void TC1_Handler                   ( void );
void TC2_Handler                   ( void );
void TRAM_Handler                  ( void );
void TRNG_Handler                  ( void );
void WDT_Handler                   ( void );
#endif /* DONT_USE_PREDEFINED_PERIPHERALS_HANDLERS */


/* Defines for Deprecated Interrupt and Exceptions handler names */
#define MemManage_Handler         MemoryManagement_Handler        /**< \deprecated  Backward compatibility for ASF */
#define DebugMon_Handler          DebugMonitor_Handler            /**< \deprecated  Backward compatibility for ASF */
#define NMI_Handler               NonMaskableInt_Handler          /**< \deprecated  Backward compatibility for ASF */
#define SVC_Handler               SVCall_Handler                  /**< \deprecated  Backward compatibility for ASF */

#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */


/*
 * \brief Configuration of the CORTEX-M23 Processor and Core Peripherals
 */

#define NUM_IRQ                       45 /**< Number of interrupt request lines                                         */
#define __ARMv8MBL_REV            0x0000 /**< Cortex-M23 Core Revision                                                  */
#define __BKPT_NUM                     4 /**< Number of FPB breakpoint comparators                                      */
#define __ETM_PRESENT                  0 /**< ETM present or not                                                        */
#define __FPU_PRESENT                  0 /**< FPU present or not                                                        */
#define __MPU_PRESENT                  1 /**< MPU present or not                                                        */
#define __MPU_REGIONS                  4 /**< Number of MPU regions                                                     */
#define __MTB_PRESENT                  0 /**< MTB present or not                                                        */
#define __NVIC_PRIO_BITS               2 /**< Number of Bits used for Priority Levels                                   */
#define __SAU_PRESENT                  0 /**< SAU present or not                                                        */
#define __SEC_ENABLED                  0 /**< TrustZone-M enabled or not                                                */
#define __SYST_NUM                     1 /**< Number of SysTick instances                                               */
#define __VTOR_PRESENT                 1 /**< Vector Table Offset Register present or not                               */
#define __Vendor_SysTickConfig         0 /**< Set to 1 if different SysTick Config is used                              */
#define __WPT_NUM                      2 /**< Number of DWT watchpoint comparators                                      */
#define __ARCH_ARM                     1
#define __ARCH_ARM_CORTEX_M            1

/*
 * \brief CMSIS includes
 */
#include <core_cm23.h>
#if !defined DONT_USE_CMSIS_INIT
#include "system_saml10.h"
#endif /* DONT_USE_CMSIS_INIT */

/** @}  end of SAML10E15A_cmsis CMSIS Definitions */

/** \defgroup SAML10E15A_api Peripheral Software API
 *  @{
 */

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR SAML10E15A */
/* ************************************************************************** */
#include "component/ac.h"
#include "component/adc.h"
#include "component/ccl.h"
#include "component/dac.h"
#include "component/dmac.h"
#include "component/dsu.h"
#include "component/eic.h"
#include "component/evsys.h"
#include "component/freqm.h"
#include "component/gclk.h"
#include "component/idau.h"
#include "component/mclk.h"
#include "component/nvmctrl.h"
#include "component/opamp.h"
#include "component/oscctrl.h"
#include "component/osc32kctrl.h"
#include "component/pac.h"
#include "component/pm.h"
#include "component/port.h"
#include "component/ptc.h"
#include "component/rstc.h"
#include "component/rtc.h"
#include "component/sercom.h"
#include "component/supc.h"
#include "component/tc.h"
#include "component/tram.h"
#include "component/trng.h"
#include "component/wdt.h"
/** @}  end of Peripheral Software API */

/** \defgroup SAML10E15A_reg Registers Access Definitions
 *  @{
 */

/* ************************************************************************** */
/*   REGISTER ACCESS DEFINITIONS FOR SAML10E15A */
/* ************************************************************************** */
#include "instance/ac.h"
#include "instance/adc.h"
#include "instance/ccl.h"
#include "instance/dac.h"
#include "instance/dmac.h"
#include "instance/dsu.h"
#include "instance/eic.h"
#include "instance/evsys.h"
#include "instance/freqm.h"
#include "instance/gclk.h"
#include "instance/idau.h"
#include "instance/mclk.h"
#include "instance/nvmctrl.h"
#include "instance/opamp.h"
#include "instance/oscctrl.h"
#include "instance/osc32kctrl.h"
#include "instance/pac.h"
#include "instance/pm.h"
#include "instance/port.h"
#include "instance/ptc.h"
#include "instance/rstc.h"
#include "instance/rtc.h"
#include "instance/sercom0.h"
#include "instance/sercom1.h"
#include "instance/sercom2.h"
#include "instance/supc.h"
#include "instance/tc0.h"
#include "instance/tc1.h"
#include "instance/tc2.h"
#include "instance/tram.h"
#include "instance/trng.h"
#include "instance/wdt.h"
/** @}  end of Registers Access Definitions */

/** \addtogroup SAML10E15A_id Peripheral Ids Definitions
 *  @{
 */

/* ************************************************************************** */
/*  PERIPHERAL ID DEFINITIONS FOR SAML10E15A */
/* ************************************************************************** */
#define ID_PAC          (  0) /**< \brief Peripheral Access Controller (PAC) */
#define ID_PM           (  1) /**< \brief Power Manager (PM) */
#define ID_MCLK         (  2) /**< \brief Main Clock (MCLK) */
#define ID_RSTC         (  3) /**< \brief Reset Controller (RSTC) */
#define ID_OSCCTRL      (  4) /**< \brief Oscillators Control (OSCCTRL) */
#define ID_OSC32KCTRL   (  5) /**< \brief 32k Oscillators Control (OSC32KCTRL) */
#define ID_SUPC         (  6) /**< \brief Supply Controller (SUPC) */
#define ID_GCLK         (  7) /**< \brief Generic Clock Generator (GCLK) */
#define ID_WDT          (  8) /**< \brief Watchdog Timer (WDT) */
#define ID_RTC          (  9) /**< \brief Real-Time Counter (RTC) */
#define ID_EIC          ( 10) /**< \brief External Interrupt Controller (EIC) */
#define ID_FREQM        ( 11) /**< \brief Frequency Meter (FREQM) */
#define ID_PORT         ( 12) /**< \brief Port Module (PORT) */
#define ID_AC           ( 13) /**< \brief Analog Comparators (AC) */
#define ID_IDAU         ( 32) /**< \brief Implementation Defined Attribution Unit (IDAU) */
#define ID_DSU          ( 33) /**< \brief Device Service Unit (DSU) */
#define ID_NVMCTRL      ( 34) /**< \brief Non-Volatile Memory Controller (NVMCTRL) */
#define ID_DMAC         ( 35) /**< \brief Direct Memory Access Controller (DMAC) */
#define ID_EVSYS        ( 64) /**< \brief Event System Interface (EVSYS) */
#define ID_SERCOM0      ( 65) /**< \brief Serial Communication Interface (SERCOM0) */
#define ID_SERCOM1      ( 66) /**< \brief Serial Communication Interface (SERCOM1) */
#define ID_SERCOM2      ( 67) /**< \brief Serial Communication Interface (SERCOM2) */
#define ID_TC0          ( 68) /**< \brief Basic Timer Counter (TC0) */
#define ID_TC1          ( 69) /**< \brief Basic Timer Counter (TC1) */
#define ID_TC2          ( 70) /**< \brief Basic Timer Counter (TC2) */
#define ID_ADC          ( 71) /**< \brief Analog Digital Converter (ADC) */
#define ID_DAC          ( 72) /**< \brief Digital Analog Converter (DAC) */
#define ID_PTC          ( 73) /**< \brief Peripheral Touch Controller (PTC) */
#define ID_TRNG         ( 74) /**< \brief True Random Generator (TRNG) */
#define ID_CCL          ( 75) /**< \brief Configurable Custom Logic (CCL) */
#define ID_OPAMP        ( 76) /**< \brief Operational Amplifier (OPAMP) */
#define ID_TRAM         ( 77) /**< \brief TrustRAM (TRAM) */

#define ID_PERIPH_COUNT ( 78) /**< \brief Number of peripheral IDs */
/** @}  end of Peripheral Ids Definitions */

/** \addtogroup SAML10E15A_base Peripheral Base Address Definitions
 *  @{
 */

/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR SAML10E15A */
/* ************************************************************************** */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#define AC                     (0x40003400)                   /**< \brief (AC        ) Base Address */
#define ADC                    (0x42001C00)                   /**< \brief (ADC       ) Base Address */
#define CCL                    (0x42002C00)                   /**< \brief (CCL       ) Base Address */
#define DAC                    (0x42002000)                   /**< \brief (DAC       ) Base Address */
#define DMAC                   (0x41006000)                   /**< \brief (DMAC      ) Base Address */
#define DSU                    (0x41002000)                   /**< \brief (DSU       ) Base Address */
#define DSU_EXT                (0x41002100)                   /**< \brief (DSU       ) Base Address */
#define EIC                    (0x40002800)                   /**< \brief (EIC       ) Base Address */
#define EVSYS                  (0x42000000)                   /**< \brief (EVSYS     ) Base Address */
#define FREQM                  (0x40002C00)                   /**< \brief (FREQM     ) Base Address */
#define GCLK                   (0x40001C00)                   /**< \brief (GCLK      ) Base Address */
#define IDAU                   (0x41000000)                   /**< \brief (IDAU      ) Base Address */
#define MCLK                   (0x40000800)                   /**< \brief (MCLK      ) Base Address */
#define NVMCTRL                (0x41004000)                   /**< \brief (NVMCTRL   ) Base Address */
#define OPAMP                  (0x42003000)                   /**< \brief (OPAMP     ) Base Address */
#define OSCCTRL                (0x40001000)                   /**< \brief (OSCCTRL   ) Base Address */
#define OSC32KCTRL             (0x40001400)                   /**< \brief (OSC32KCTRL) Base Address */
#define PAC                    (0x40000000)                   /**< \brief (PAC       ) Base Address */
#define PM                     (0x40000400)                   /**< \brief (PM        ) Base Address */
#define PORT                   (0x40003000)                   /**< \brief (PORT      ) Base Address */
#define PORT_IOBUS             (0x60000000)                   /**< \brief (PORT      ) Base Address */
#define PTC                    (0x42002400)                   /**< \brief (PTC       ) Base Address */
#define RSTC                   (0x40000C00)                   /**< \brief (RSTC      ) Base Address */
#define RTC                    (0x40002400)                   /**< \brief (RTC       ) Base Address */
#define SERCOM0                (0x42000400)                   /**< \brief (SERCOM0   ) Base Address */
#define SERCOM1                (0x42000800)                   /**< \brief (SERCOM1   ) Base Address */
#define SERCOM2                (0x42000C00)                   /**< \brief (SERCOM2   ) Base Address */
#define SUPC                   (0x40001800)                   /**< \brief (SUPC      ) Base Address */
#define TC0                    (0x42001000)                   /**< \brief (TC0       ) Base Address */
#define TC1                    (0x42001400)                   /**< \brief (TC1       ) Base Address */
#define TC2                    (0x42001800)                   /**< \brief (TC2       ) Base Address */
#define TRAM                   (0x42003400)                   /**< \brief (TRAM      ) Base Address */
#define TRNG                   (0x42002800)                   /**< \brief (TRNG      ) Base Address */
#define WDT                    (0x40002000)                   /**< \brief (WDT       ) Base Address */

#else /* For C/C++ compiler */

#define AC                     ((Ac *)0x40003400U)            /**< \brief (AC        ) Base Address */
#define AC_INST_NUM            1                              /**< \brief (AC        ) Number of instances */
#define AC_INSTS               { AC }                         /**< \brief (AC        ) Instances List */

#define ADC                    ((Adc *)0x42001C00U)           /**< \brief (ADC       ) Base Address */
#define ADC_INST_NUM           1                              /**< \brief (ADC       ) Number of instances */
#define ADC_INSTS              { ADC }                        /**< \brief (ADC       ) Instances List */

#define CCL                    ((Ccl *)0x42002C00U)           /**< \brief (CCL       ) Base Address */
#define CCL_INST_NUM           1                              /**< \brief (CCL       ) Number of instances */
#define CCL_INSTS              { CCL }                        /**< \brief (CCL       ) Instances List */

#define DAC                    ((Dac *)0x42002000U)           /**< \brief (DAC       ) Base Address */
#define DAC_INST_NUM           1                              /**< \brief (DAC       ) Number of instances */
#define DAC_INSTS              { DAC }                        /**< \brief (DAC       ) Instances List */

#define DMAC                   ((Dmac *)0x41006000U)          /**< \brief (DMAC      ) Base Address */
#define DMAC_INST_NUM          1                              /**< \brief (DMAC      ) Number of instances */
#define DMAC_INSTS             { DMAC }                       /**< \brief (DMAC      ) Instances List */

#define DSU                    ((Dsu *)0x41002000U)           /**< \brief (DSU       ) Base Address */
#define DSU_EXT                ((Dsu *)0x41002100U)           /**< \brief (DSU       ) Base Address */
#define DSU_INST_NUM           1                              /**< \brief (DSU       ) Number of instances */
#define DSU_INSTS              { DSU }                        /**< \brief (DSU       ) Instances List */

#define EIC                    ((Eic *)0x40002800U)           /**< \brief (EIC       ) Base Address */
#define EIC_INST_NUM           1                              /**< \brief (EIC       ) Number of instances */
#define EIC_INSTS              { EIC }                        /**< \brief (EIC       ) Instances List */

#define EVSYS                  ((Evsys *)0x42000000U)         /**< \brief (EVSYS     ) Base Address */
#define EVSYS_INST_NUM         1                              /**< \brief (EVSYS     ) Number of instances */
#define EVSYS_INSTS            { EVSYS }                      /**< \brief (EVSYS     ) Instances List */

#define FREQM                  ((Freqm *)0x40002C00U)         /**< \brief (FREQM     ) Base Address */
#define FREQM_INST_NUM         1                              /**< \brief (FREQM     ) Number of instances */
#define FREQM_INSTS            { FREQM }                      /**< \brief (FREQM     ) Instances List */

#define GCLK                   ((Gclk *)0x40001C00U)          /**< \brief (GCLK      ) Base Address */
#define GCLK_INST_NUM          1                              /**< \brief (GCLK      ) Number of instances */
#define GCLK_INSTS             { GCLK }                       /**< \brief (GCLK      ) Instances List */

#define IDAU                   ((Idau *)0x41000000U)          /**< \brief (IDAU      ) Base Address */
#define IDAU_INST_NUM          1                              /**< \brief (IDAU      ) Number of instances */
#define IDAU_INSTS             { IDAU }                       /**< \brief (IDAU      ) Instances List */

#define MCLK                   ((Mclk *)0x40000800U)          /**< \brief (MCLK      ) Base Address */
#define MCLK_INST_NUM          1                              /**< \brief (MCLK      ) Number of instances */
#define MCLK_INSTS             { MCLK }                       /**< \brief (MCLK      ) Instances List */

#define NVMCTRL                ((Nvmctrl *)0x41004000U)       /**< \brief (NVMCTRL   ) Base Address */
#define NVMCTRL_INST_NUM       1                              /**< \brief (NVMCTRL   ) Number of instances */
#define NVMCTRL_INSTS          { NVMCTRL }                    /**< \brief (NVMCTRL   ) Instances List */

#define OPAMP                  ((Opamp *)0x42003000U)         /**< \brief (OPAMP     ) Base Address */
#define OPAMP_INST_NUM         1                              /**< \brief (OPAMP     ) Number of instances */
#define OPAMP_INSTS            { OPAMP }                      /**< \brief (OPAMP     ) Instances List */

#define OSCCTRL                ((Oscctrl *)0x40001000U)       /**< \brief (OSCCTRL   ) Base Address */
#define OSCCTRL_INST_NUM       1                              /**< \brief (OSCCTRL   ) Number of instances */
#define OSCCTRL_INSTS          { OSCCTRL }                    /**< \brief (OSCCTRL   ) Instances List */

#define OSC32KCTRL             ((Osc32kctrl *)0x40001400U)    /**< \brief (OSC32KCTRL) Base Address */
#define OSC32KCTRL_INST_NUM    1                              /**< \brief (OSC32KCTRL) Number of instances */
#define OSC32KCTRL_INSTS       { OSC32KCTRL }                 /**< \brief (OSC32KCTRL) Instances List */

#define PAC                    ((Pac *)0x40000000U)           /**< \brief (PAC       ) Base Address */
#define PAC_INST_NUM           1                              /**< \brief (PAC       ) Number of instances */
#define PAC_INSTS              { PAC }                        /**< \brief (PAC       ) Instances List */

#define PM                     ((Pm *)0x40000400U)            /**< \brief (PM        ) Base Address */
#define PM_INST_NUM            1                              /**< \brief (PM        ) Number of instances */
#define PM_INSTS               { PM }                         /**< \brief (PM        ) Instances List */

#define PORT                   ((Port *)0x40003000U)          /**< \brief (PORT      ) Base Address */
#define PORT_IOBUS             ((Port *)0x60000000U)          /**< \brief (PORT      ) Base Address */
#define PORT_INST_NUM          1                              /**< \brief (PORT      ) Number of instances */
#define PORT_INSTS             { PORT }                       /**< \brief (PORT      ) Instances List */

#define PTC                    ((Ptc *)0x42002400U)           /**< \brief (PTC       ) Base Address */
#define PTC_INST_NUM           1                              /**< \brief (PTC       ) Number of instances */
#define PTC_INSTS              { PTC }                        /**< \brief (PTC       ) Instances List */

#define RSTC                   ((Rstc *)0x40000C00U)          /**< \brief (RSTC      ) Base Address */
#define RSTC_INST_NUM          1                              /**< \brief (RSTC      ) Number of instances */
#define RSTC_INSTS             { RSTC }                       /**< \brief (RSTC      ) Instances List */

#define RTC                    ((Rtc *)0x40002400U)           /**< \brief (RTC       ) Base Address */
#define RTC_INST_NUM           1                              /**< \brief (RTC       ) Number of instances */
#define RTC_INSTS              { RTC }                        /**< \brief (RTC       ) Instances List */

#define SERCOM0                ((Sercom *)0x42000400U)        /**< \brief (SERCOM0   ) Base Address */
#define SERCOM1                ((Sercom *)0x42000800U)        /**< \brief (SERCOM1   ) Base Address */
#define SERCOM2                ((Sercom *)0x42000C00U)        /**< \brief (SERCOM2   ) Base Address */
#define SERCOM_INST_NUM        3                              /**< \brief (SERCOM    ) Number of instances */
#define SERCOM_INSTS           { SERCOM0, SERCOM1, SERCOM2 }  /**< \brief (SERCOM    ) Instances List */

#define SUPC                   ((Supc *)0x40001800U)          /**< \brief (SUPC      ) Base Address */
#define SUPC_INST_NUM          1                              /**< \brief (SUPC      ) Number of instances */
#define SUPC_INSTS             { SUPC }                       /**< \brief (SUPC      ) Instances List */

#define TC0                    ((Tc *)0x42001000U)            /**< \brief (TC0       ) Base Address */
#define TC1                    ((Tc *)0x42001400U)            /**< \brief (TC1       ) Base Address */
#define TC2                    ((Tc *)0x42001800U)            /**< \brief (TC2       ) Base Address */
#define TC_INST_NUM            3                              /**< \brief (TC        ) Number of instances */
#define TC_INSTS               { TC0, TC1, TC2 }              /**< \brief (TC        ) Instances List */

#define TRAM                   ((Tram *)0x42003400U)          /**< \brief (TRAM      ) Base Address */
#define TRAM_INST_NUM          1                              /**< \brief (TRAM      ) Number of instances */
#define TRAM_INSTS             { TRAM }                       /**< \brief (TRAM      ) Instances List */

#define TRNG                   ((Trng *)0x42002800U)          /**< \brief (TRNG      ) Base Address */
#define TRNG_INST_NUM          1                              /**< \brief (TRNG      ) Number of instances */
#define TRNG_INSTS             { TRNG }                       /**< \brief (TRNG      ) Instances List */

#define WDT                    ((Wdt *)0x40002000U)           /**< \brief (WDT       ) Base Address */
#define WDT_INST_NUM           1                              /**< \brief (WDT       ) Number of instances */
#define WDT_INSTS              { WDT }                        /**< \brief (WDT       ) Instances List */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
/** @}  end of Peripheral Base Address Definitions */

/** \addtogroup SAML10E15A_pio Peripheral Pio Definitions
 *  @{
 */

/* ************************************************************************** */
/*   PIO DEFINITIONS FOR SAML10E15A*/
/* ************************************************************************** */
#include "pio/saml10e15a.h"
/** @}  end of Peripheral Pio Definitions */

/* ************************************************************************** */
/*   MEMORY MAPPING DEFINITIONS FOR SAML10E15A*/
/* ************************************************************************** */

#define FLASH_SIZE               _U_(0x00008000)       /*   32kB Memory segment type: flash */
#define FLASH_PAGE_SIZE          _U_(        64)
#define FLASH_NB_OF_PAGES        _U_(       512)

#define AUX_SIZE                 _U_(0x00000100)       /*    0kB Memory segment type: fuses */
#define AUX_PAGE_SIZE            _U_(        64)
#define AUX_NB_OF_PAGES          _U_(         4)

#define BOCOR_SIZE               _U_(0x00000100)       /*    0kB Memory segment type: fuses */
#define BOCOR_PAGE_SIZE          _U_(        64)
#define BOCOR_NB_OF_PAGES        _U_(         4)

#define DATAFLASH_SIZE           _U_(0x00000800)       /*    2kB Memory segment type: flash */
#define DATAFLASH_PAGE_SIZE      _U_(        64)
#define DATAFLASH_NB_OF_PAGES    _U_(        32)

#define SW_CALIB_SIZE            _U_(0x00000008)       /*    0kB Memory segment type: fuses */
#define TEMP_LOG_SIZE            _U_(0x00000008)       /*    0kB Memory segment type: fuses */
#define USER_PAGE_SIZE           _U_(0x00000100)       /*    0kB Memory segment type: user_page */
#define USER_PAGE_PAGE_SIZE      _U_(        64)
#define USER_PAGE_NB_OF_PAGES    _U_(         4)

#define HSRAM_SIZE               _U_(0x00002000)       /*    8kB Memory segment type: ram */
#define HPB0_SIZE                _U_(0x00008000)       /*   32kB Memory segment type: io */
#define HPB1_SIZE                _U_(0x00010000)       /*   64kB Memory segment type: io */
#define HPB2_SIZE                _U_(0x00004000)       /*   16kB Memory segment type: io */
#define PPB_SIZE                 _U_(0x00100000)       /* 1024kB Memory segment type: io */
#define SCS_SIZE                 _U_(0x00001000)       /*    4kB Memory segment type: io */
#define PERIPHERALS_SIZE         _U_(0x20000000)       /* 524288kB Memory segment type: io */

#define FLASH_ADDR               _U_(0x00000000)       /**< FLASH base address (type: flash)*/
#define AUX_ADDR                 _U_(0x00806000)       /**< AUX base address (type: fuses)*/
#define BOCOR_ADDR               _U_(0x0080c000)       /**< BOCOR base address (type: fuses)*/
#define DATAFLASH_ADDR           _U_(0x00400000)       /**< DATAFLASH base address (type: flash)*/
#define SW_CALIB_ADDR            _U_(0x00806020)       /**< SW_CALIB base address (type: fuses)*/
#define TEMP_LOG_ADDR            _U_(0x00806038)       /**< TEMP_LOG base address (type: fuses)*/
#define USER_PAGE_ADDR           _U_(0x00804000)       /**< USER_PAGE base address (type: user_page)*/
#define HSRAM_ADDR               _U_(0x20000000)       /**< HSRAM base address (type: ram)*/
#define HPB0_ADDR                _U_(0x40000000)       /**< HPB0 base address (type: io)*/
#define HPB1_ADDR                _U_(0x41000000)       /**< HPB1 base address (type: io)*/
#define HPB2_ADDR                _U_(0x42000000)       /**< HPB2 base address (type: io)*/
#define PPB_ADDR                 _U_(0xe0000000)       /**< PPB base address (type: io)*/
#define SCS_ADDR                 _U_(0xe000e000)       /**< SCS base address (type: io)*/
#define PERIPHERALS_ADDR         _U_(0x40000000)       /**< PERIPHERALS base address (type: io)*/

#define NVMCTRL_AUX              AUX_ADDR              /**< \brief \deprecated Old style definition. Use AUX_ADDR instead */
#define NVMCTRL_BOCOR            BOCOR_ADDR            /**< \brief \deprecated Old style definition. Use BOCOR_ADDR instead */
#define NVMCTRL_DATAFLASH        DATAFLASH_ADDR        /**< \brief \deprecated Old style definition. Use DATAFLASH_ADDR instead */
#define NVMCTRL_SW_CALIB         SW_CALIB_ADDR         /**< \brief \deprecated Old style definition. Use SW_CALIB_ADDR instead */
#define NVMCTRL_TEMP_LOG         TEMP_LOG_ADDR         /**< \brief \deprecated Old style definition. Use TEMP_LOG_ADDR instead */
#define NVMCTRL_USER             USER_PAGE_ADDR        /**< \brief \deprecated Old style definition. Use USER_PAGE_ADDR instead */

/* ************************************************************************** */
/**  DEVICE SIGNATURES FOR SAML10E15A */
/* ************************************************************************** */
#define DSU_DID                  _UL_(0X20840001)

/* ************************************************************************** */
/**  ELECTRICAL DEFINITIONS FOR SAML10E15A */
/* ************************************************************************** */

/* ************************************************************************** */
/** Event Generator IDs for SAML10E15A */
/* ************************************************************************** */
#define EVENT_ID_GEN_OSCCTRL_XOSC_FAIL                    1 /**< ID for OSCCTRL event generator XOSC_FAIL */
#define EVENT_ID_GEN_OSC32KCTRL_XOSC32K_FAIL              2 /**< ID for OSC32KCTRL event generator XOSC32K_FAIL */
#define EVENT_ID_GEN_SUPC_BOD33DET                        3 /**< ID for SUPC event generator BOD33DET */
#define EVENT_ID_GEN_RTC_PER_0                            4 /**< ID for RTC event generator PER_0 */
#define EVENT_ID_GEN_RTC_PER_1                            5 /**< ID for RTC event generator PER_1 */
#define EVENT_ID_GEN_RTC_PER_2                            6 /**< ID for RTC event generator PER_2 */
#define EVENT_ID_GEN_RTC_PER_3                            7 /**< ID for RTC event generator PER_3 */
#define EVENT_ID_GEN_RTC_PER_4                            8 /**< ID for RTC event generator PER_4 */
#define EVENT_ID_GEN_RTC_PER_5                            9 /**< ID for RTC event generator PER_5 */
#define EVENT_ID_GEN_RTC_PER_6                           10 /**< ID for RTC event generator PER_6 */
#define EVENT_ID_GEN_RTC_PER_7                           11 /**< ID for RTC event generator PER_7 */
#define EVENT_ID_GEN_RTC_CMP_0                           12 /**< ID for RTC event generator CMP_0 */
#define EVENT_ID_GEN_RTC_CMP_1                           13 /**< ID for RTC event generator CMP_1 */
#define EVENT_ID_GEN_RTC_TAMPER                          14 /**< ID for RTC event generator TAMPER */
#define EVENT_ID_GEN_RTC_OVF                             15 /**< ID for RTC event generator OVF */
#define EVENT_ID_GEN_RTC_PERD                            16 /**< ID for RTC event generator PERD */
#define EVENT_ID_GEN_EIC_EXTINT_0                        17 /**< ID for EIC event generator EXTINT_0 */
#define EVENT_ID_GEN_EIC_EXTINT_1                        18 /**< ID for EIC event generator EXTINT_1 */
#define EVENT_ID_GEN_EIC_EXTINT_2                        19 /**< ID for EIC event generator EXTINT_2 */
#define EVENT_ID_GEN_EIC_EXTINT_3                        20 /**< ID for EIC event generator EXTINT_3 */
#define EVENT_ID_GEN_EIC_EXTINT_4                        21 /**< ID for EIC event generator EXTINT_4 */
#define EVENT_ID_GEN_EIC_EXTINT_5                        22 /**< ID for EIC event generator EXTINT_5 */
#define EVENT_ID_GEN_EIC_EXTINT_6                        23 /**< ID for EIC event generator EXTINT_6 */
#define EVENT_ID_GEN_EIC_EXTINT_7                        24 /**< ID for EIC event generator EXTINT_7 */
#define EVENT_ID_GEN_DMAC_CH_0                           25 /**< ID for DMAC event generator CH_0 */
#define EVENT_ID_GEN_DMAC_CH_1                           26 /**< ID for DMAC event generator CH_1 */
#define EVENT_ID_GEN_DMAC_CH_2                           27 /**< ID for DMAC event generator CH_2 */
#define EVENT_ID_GEN_DMAC_CH_3                           28 /**< ID for DMAC event generator CH_3 */
#define EVENT_ID_GEN_TC0_OVF                             29 /**< ID for TC0 event generator OVF */
#define EVENT_ID_GEN_TC0_MCX_0                           30 /**< ID for TC0 event generator MCX_0 */
#define EVENT_ID_GEN_TC0_MCX_1                           31 /**< ID for TC0 event generator MCX_1 */
#define EVENT_ID_GEN_TC1_OVF                             32 /**< ID for TC1 event generator OVF */
#define EVENT_ID_GEN_TC1_MCX_0                           33 /**< ID for TC1 event generator MCX_0 */
#define EVENT_ID_GEN_TC1_MCX_1                           34 /**< ID for TC1 event generator MCX_1 */
#define EVENT_ID_GEN_TC2_OVF                             35 /**< ID for TC2 event generator OVF */
#define EVENT_ID_GEN_TC2_MCX_0                           36 /**< ID for TC2 event generator MCX_0 */
#define EVENT_ID_GEN_TC2_MCX_1                           37 /**< ID for TC2 event generator MCX_1 */
#define EVENT_ID_GEN_ADC_RESRDY                          38 /**< ID for ADC event generator RESRDY */
#define EVENT_ID_GEN_ADC_WINMON                          39 /**< ID for ADC event generator WINMON */
#define EVENT_ID_GEN_AC_COMP_0                           40 /**< ID for AC event generator COMP_0 */
#define EVENT_ID_GEN_AC_COMP_1                           41 /**< ID for AC event generator COMP_1 */
#define EVENT_ID_GEN_AC_WIN_0                            42 /**< ID for AC event generator WIN_0 */
#define EVENT_ID_GEN_DAC_EMPTY                           43 /**< ID for DAC event generator EMPTY */
#define EVENT_ID_GEN_TRNG_READY                          46 /**< ID for TRNG event generator READY */
#define EVENT_ID_GEN_CCL_LUTOUT_0                        47 /**< ID for CCL event generator LUTOUT_0 */
#define EVENT_ID_GEN_CCL_LUTOUT_1                        48 /**< ID for CCL event generator LUTOUT_1 */
#define EVENT_ID_GEN_PAC_ERR                             49 /**< ID for PAC event generator ERR */

/* ************************************************************************** */
/** Event User IDs for SAML10E15A */
/* ************************************************************************** */
#define EVENT_ID_USER_OSCCTRL_TUNE                        0 /**< ID for OSCCTRL event user TUNE */
#define EVENT_ID_USER_RTC_TAMPER                          1 /**< ID for RTC event user TAMPER */
#define EVENT_ID_USER_NVMCTRL_PAGEW                       2 /**< ID for NVMCTRL event user PAGEW */
#define EVENT_ID_USER_PORT_EV_0                           3 /**< ID for PORT event user EV_0 */
#define EVENT_ID_USER_PORT_EV_1                           4 /**< ID for PORT event user EV_1 */
#define EVENT_ID_USER_PORT_EV_2                           5 /**< ID for PORT event user EV_2 */
#define EVENT_ID_USER_PORT_EV_3                           6 /**< ID for PORT event user EV_3 */
#define EVENT_ID_USER_DMAC_CH_0                           7 /**< ID for DMAC event user CH_0 */
#define EVENT_ID_USER_DMAC_CH_1                           8 /**< ID for DMAC event user CH_1 */
#define EVENT_ID_USER_DMAC_CH_2                           9 /**< ID for DMAC event user CH_2 */
#define EVENT_ID_USER_DMAC_CH_3                          10 /**< ID for DMAC event user CH_3 */
#define EVENT_ID_USER_TC0_EVU                            11 /**< ID for TC0 event user EVU */
#define EVENT_ID_USER_TC1_EVU                            12 /**< ID for TC1 event user EVU */
#define EVENT_ID_USER_TC2_EVU                            13 /**< ID for TC2 event user EVU */
#define EVENT_ID_USER_ADC_START                          14 /**< ID for ADC event user START */
#define EVENT_ID_USER_ADC_SYNC                           15 /**< ID for ADC event user SYNC */
#define EVENT_ID_USER_AC_SOC_0                           16 /**< ID for AC event user SOC_0 */
#define EVENT_ID_USER_AC_SOC_1                           17 /**< ID for AC event user SOC_1 */
#define EVENT_ID_USER_DAC_START                          18 /**< ID for DAC event user START */
#define EVENT_ID_USER_CCL_LUTIN_0                        21 /**< ID for CCL event user LUTIN_0 */
#define EVENT_ID_USER_CCL_LUTIN_1                        22 /**< ID for CCL event user LUTIN_1 */

#ifdef __cplusplus
}
#endif

/** @}  end of SAML10E15A definitions */


#endif /* _SAML10E15A_H_ */
