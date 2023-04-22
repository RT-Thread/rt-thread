/***************************************************************************//**
* \file cy_device_common.h
* \version 2.91
*
* \brief
* This file provides types and IP block definitions common for all PSoC 6
* devices.
*
********************************************************************************
* \copyright
* Copyright 2018-2021 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef _CY_DEVICE_COMMON_H_
#define _CY_DEVICE_COMMON_H_

#include <stdint.h>

/*******************************************************************************
*                     CPU Core Interrupts
*******************************************************************************/

typedef enum {
#if ((defined(__GNUC__)        && (__ARM_ARCH == 6) && (__ARM_ARCH_6M__ == 1)) || \
     (defined(__ICCARM__)      && (__CORE__ == __ARM6M__)) || \
     (defined(__ARMCC_VERSION) && (__TARGET_ARCH_THUMB == 3)) || \
     (defined(__ghs__)         && defined(__CORE_CORTEXM0PLUS__)))
  /* ARM Cortex-M0+ Core Interrupt Numbers */
  Reset_IRQn                        = -15,      /*!< -15 Reset Vector, invoked on Power up and warm reset */
  NonMaskableInt_IRQn               = -14,      /*!< -14 Non maskable Interrupt, cannot be stopped or preempted */
  HardFault_IRQn                    = -13,      /*!< -13 Hard Fault, all classes of Fault */
  SVCall_IRQn                       =  -5,      /*!<  -5 System Service Call via SVC instruction */
  PendSV_IRQn                       =  -2,      /*!<  -2 Pendable request for system service */
  SysTick_IRQn                      =  -1,      /*!<  -1 System Tick Timer */
  cpuss_interrupts_ipc_0_IRQn       =  23,      /*!<  23 [DeepSleep] CPUSS Inter Process Communication Interrupt #0 */
  unconnected_IRQn                  = 240
#else
  /* ARM Cortex-M4 Core Interrupt Numbers */
  Reset_IRQn                        = -15,      /*!< -15 Reset Vector, invoked on Power up and warm reset */
  NonMaskableInt_IRQn               = -14,      /*!< -14 Non maskable Interrupt, cannot be stopped or preempted */
  HardFault_IRQn                    = -13,      /*!< -13 Hard Fault, all classes of Fault */
  MemoryManagement_IRQn             = -12,      /*!< -12 Memory Management, MPU mismatch, including Access Violation and No Match */
  BusFault_IRQn                     = -11,      /*!< -11 Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory related Fault */
  UsageFault_IRQn                   = -10,      /*!< -10 Usage Fault, i.e. Undef Instruction, Illegal State Transition */
  SVCall_IRQn                       =  -5,      /*!<  -5 System Service Call via SVC instruction */
  DebugMonitor_IRQn                 =  -4,      /*!<  -4 Debug Monitor */
  PendSV_IRQn                       =  -2,      /*!<  -2 Pendable request for system service */
  SysTick_IRQn                      =  -1,      /*!<  -1 System Tick Timer */
  cpuss_interrupts_ipc_0_IRQn       =  23,      /*!<  23 [DeepSleep] CPUSS Inter Process Communication Interrupt #0 */
  unconnected_IRQn                  = 240
#endif
} IRQn_Type;


#if ((defined(__GNUC__)        && (__ARM_ARCH == 6) && (__ARM_ARCH_6M__ == 1)) || \
     (defined(__ICCARM__)      && (__CORE__ == __ARM6M__)) || \
     (defined(__ARMCC_VERSION) && (__TARGET_ARCH_THUMB == 3)) || \
     (defined(__ghs__)         && defined(__CORE_CORTEXM0PLUS__)))

typedef enum {
  disconnected_IRQn                 = 1023       /*!< 1023 Disconnected */
} cy_en_intr_t;

#endif

/*******************************************************************************
*                    Processor and Core Peripheral Section
*******************************************************************************/

#if ((defined(__GNUC__)        && (__ARM_ARCH == 6) && (__ARM_ARCH_6M__ == 1)) || \
     (defined(__ICCARM__)      && (__CORE__ == __ARM6M__)) || \
     (defined(__ARMCC_VERSION) && (__TARGET_ARCH_THUMB == 3)) || \
     (defined(__ghs__)         && defined(__CORE_CORTEXM0PLUS__)))

/* Configuration of the ARM Cortex-M0+ Processor and Core Peripherals */
#define __CM0PLUS_REV                   0x0001U /*!< CM0PLUS Core Revision */
#define __NVIC_PRIO_BITS                2       /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig          0       /*!< Set to 1 if different SysTick Config is used */
#define __VTOR_PRESENT                  1       /*!< Set to 1 if CPU supports Vector Table Offset Register */
#define __MPU_PRESENT                   1       /*!< MPU present or not */

/** \} Configuration_of_CMSIS */

#include "core_cm0plus.h"                       /*!< ARM Cortex-M0+ processor and core peripherals */

#else

/* Configuration of the ARM Cortex-M4 Processor and Core Peripherals */
#define __CM4_REV                       0x0001U /*!< CM4 Core Revision */
#define __NVIC_PRIO_BITS                3       /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig          0       /*!< Set to 1 if different SysTick Config is used */
#define __VTOR_PRESENT                  1       /*!< Set to 1 if CPU supports Vector Table Offset Register */
#define __MPU_PRESENT                   1       /*!< MPU present or not */
#define __FPU_PRESENT                   1       /*!< FPU present or not */
#define __CM0P_PRESENT                  1       /*!< CM0P present or not */

/** \} Configuration_of_CMSIS */

#include "core_cm4.h"                           /*!< ARM Cortex-M4 processor and core peripherals */

#endif

/*******************************************************************************
*         Product-Specific Enumeration Types
*******************************************************************************/
/* For the target device these enums are defined in product-specific
* configuration files.
* For the library these enums define the max value or a set of values used by
* the library that are common across all target devices, so the compiler can
* determine the enum width to hold the biggest number in the enum.
*/

typedef enum
{
    PCLK_PASS_CLOCK_CTDAC   = 55,
    PCLK_CLOCK_NR_MINUS_ONE = 255
} en_clk_dst_t;

typedef enum
{
    PRFL_MONITOR_NR_MINUS_ONE = 127
} en_ep_mon_sel_t;

typedef enum
{
    AMUX_SPLIT_NR_MINUS_ONE = 63
} cy_en_amux_split_t;

typedef enum
{
    TRIGGER_TYPE_LEVEL = 0u,
    TRIGGER_TYPE_EDGE  = 1u
} en_trig_type_t;

typedef enum
{
    CPUSS_MS_ID_CM0 =  0,
    CPUSS_MS_ID_CM4 = 14,
} en_prot_master_t;

typedef enum
{
    HSIOM_SEL_GPIO  =  0,       /* GPIO controls 'out' */
    HSIOM_SEL_AMUXA =  4,       /* Analog mux bus A */
    HSIOM_SEL_AMUXB =  5,       /* Analog mux bus B */
    HSIOM_SEL_ACT_2 = 10,       /* Active functionality 2 */
    HSIOM_SEL_ACT_3 = 11,       /* Active functionality 3 */
} en_hsiom_sel_t;

/*******************************************************************************
*              Platform and Peripheral Definitions
*******************************************************************************/

#define CY_IP_MXTCPWM                   1u
#define CY_IP_MXTCPWM_INSTANCES         1u
#define CY_IP_MXTCPWM_VERSION           1u
#define CY_IP_MXCSDV2                   1u
#define CY_IP_MXLCD                     1u
#define CY_IP_MXS40SRSS                 1u
#define CY_IP_MXS40SRSS_RTC             1u
#define CY_IP_MXS40SRSS_MCWDT           1u
#define CY_IP_MXSCB                     1u
#define CY_IP_MXSCB_VERSION             1u
#define CY_IP_MXPERI                    1u
#define CY_IP_MXPERI_TR                 1u
#define CY_IP_M4CPUSS                   1u
#define CY_IP_M4CPUSS_DMAC              1u
#define CY_IP_M4CPUSS_DMA               1u
#define CY_IP_MXCRYPTO                  1u
#define CY_IP_MXCRYPTO_VERSION          2u
#define CY_IP_MXBLESS                   1u
#define CY_IP_MXSDHC                    1u
#define CY_IP_MXTTCANFD                 1u
#define CY_IP_MXAUDIOSS                 1u
#define CY_IP_MXLPCOMP                  1u
#define CY_IP_MXS40PASS                 1u
#define CY_IP_MXS40PASS_SAR             1u
#define CY_IP_MXS40PASS_CTDAC           1u
#define CY_IP_MXS40PASS_CTB             1u
#define CY_IP_MXSMIF                    1u
#define CY_IP_MXSMIF_VERSION            1u
#define CY_IP_MXUSBFS                   1u
#define CY_IP_MXS40IOSS                 1u
#define CY_IP_MXEFUSE                   1u
#define CY_IP_MXUDB                     1u
#define CY_IP_MXPROFILE                 1u


/*******************************************************************************
*              Include IP Block Definitions
*******************************************************************************/
#include "ip/cyip_sflash.h"
#include "ip/cyip_peri.h"
#include "ip/cyip_peri_v2.h"
#include "ip/cyip_peri_ms_v2.h"
#include "ip/cyip_crypto.h"
#include "ip/cyip_crypto_v2.h"
#include "ip/cyip_cpuss.h"
#include "ip/cyip_cpuss_v2.h"
#include "ip/cyip_fault.h"
#include "ip/cyip_fault_v2.h"
#include "ip/cyip_ipc.h"
#include "ip/cyip_ipc_v2.h"
#include "ip/cyip_prot.h"
#include "ip/cyip_prot_v2.h"
#include "ip/cyip_flashc.h"
#include "ip/cyip_flashc_v2.h"
#include "ip/cyip_srss.h"
#include "ip/cyip_backup.h"
#include "ip/cyip_dw.h"
#include "ip/cyip_dw_v2.h"
#include "ip/cyip_dmac_v2.h"
#include "ip/cyip_efuse.h"
#include "ip/cyip_profile.h"
#include "ip/cyip_hsiom.h"
#include "ip/cyip_hsiom_v2.h"
#include "ip/cyip_gpio.h"
#include "ip/cyip_gpio_v2.h"
#include "ip/cyip_smartio.h"
#include "ip/cyip_smartio_v2.h"
#include "ip/cyip_udb.h"
#include "ip/cyip_lpcomp.h"
#include "ip/cyip_csd.h"
#include "ip/cyip_tcpwm.h"
#include "ip/cyip_lcd.h"
#include "ip/cyip_ble.h"
#include "ip/cyip_usbfs.h"
#include "ip/cyip_smif.h"
#include "ip/cyip_sdhc.h"
#include "ip/cyip_scb.h"
#include "ip/cyip_ctbm.h"
#include "ip/cyip_ctdac.h"
#include "ip/cyip_sar.h"
#include "ip/cyip_pass.h"
#include "ip/cyip_pass_v2.h"
#include "ip/cyip_i2s.h"
#include "ip/cyip_pdm.h"
#include "ip/cyip_canfd.h"

/*******************************************************************************
*            IP Type Definitions
*******************************************************************************/
typedef SFLASH_V1_Type SFLASH_Type;
typedef PERI_GR_V2_Type PERI_GR_Type;
typedef PERI_TR_GR_V2_Type PERI_TR_GR_Type;
typedef PERI_TR_1TO1_GR_V2_Type PERI_TR_1TO1_GR_Type;
typedef PERI_PPU_PR_V1_Type PERI_PPU_PR_Type;
typedef PERI_PPU_GR_V1_Type PERI_PPU_GR_Type;
typedef PERI_GR_PPU_SL_V1_Type PERI_GR_PPU_SL_Type;
typedef PERI_GR_PPU_RG_V1_Type PERI_GR_PPU_RG_Type;
typedef PERI_V2_Type PERI_Type;
typedef PERI_MS_PPU_PR_V2_Type PERI_MS_PPU_PR_Type;
typedef PERI_MS_PPU_FX_V2_Type PERI_MS_PPU_FX_Type;
typedef PERI_MS_V2_Type PERI_MS_Type;
typedef CRYPTO_V2_Type CRYPTO_Type;
typedef CPUSS_V2_Type CPUSS_Type;
typedef FAULT_STRUCT_V2_Type FAULT_STRUCT_Type;
typedef FAULT_V2_Type FAULT_Type;
typedef IPC_STRUCT_V2_Type IPC_STRUCT_Type;
typedef IPC_INTR_STRUCT_V2_Type IPC_INTR_STRUCT_Type;
typedef IPC_V2_Type IPC_Type;
typedef PROT_SMPU_SMPU_STRUCT_V2_Type PROT_SMPU_SMPU_STRUCT_Type;
typedef PROT_SMPU_V2_Type PROT_SMPU_Type;
typedef PROT_MPU_MPU_STRUCT_V2_Type PROT_MPU_MPU_STRUCT_Type;
typedef PROT_MPU_V2_Type PROT_MPU_Type;
typedef PROT_V2_Type PROT_Type;
typedef FLASHC_FM_CTL_V2_Type FLASHC_FM_CTL_Type;
typedef FLASHC_V2_Type FLASHC_Type;
typedef MCWDT_STRUCT_V1_Type MCWDT_STRUCT_Type;
typedef SRSS_V1_Type SRSS_Type;
typedef BACKUP_V1_Type BACKUP_Type;
typedef DW_CH_STRUCT_V2_Type DW_CH_STRUCT_Type;
typedef DW_V2_Type DW_Type;
typedef DMAC_CH_V2_Type DMAC_CH_Type;
typedef DMAC_V2_Type DMAC_Type;
typedef EFUSE_V1_Type EFUSE_Type;
typedef PROFILE_CNT_STRUCT_V1_Type PROFILE_CNT_STRUCT_Type;
typedef PROFILE_V1_Type PROFILE_Type;
typedef HSIOM_PRT_V2_Type HSIOM_PRT_Type;
typedef HSIOM_V2_Type HSIOM_Type;
typedef GPIO_PRT_V2_Type GPIO_PRT_Type;
typedef GPIO_V2_Type GPIO_Type;
typedef SMARTIO_PRT_V2_Type SMARTIO_PRT_Type;
typedef SMARTIO_V2_Type SMARTIO_Type;
typedef UDB_WRKONE_V1_Type UDB_WRKONE_Type;
typedef UDB_WRKMULT_V1_Type UDB_WRKMULT_Type;
typedef UDB_UDBPAIR_UDBSNG_V1_Type UDB_UDBPAIR_UDBSNG_Type;
typedef UDB_UDBPAIR_ROUTE_V1_Type UDB_UDBPAIR_ROUTE_Type;
typedef UDB_UDBPAIR_V1_Type UDB_UDBPAIR_Type;
typedef UDB_DSI_V1_Type UDB_DSI_Type;
typedef UDB_PA_V1_Type UDB_PA_Type;
typedef UDB_BCTL_V1_Type UDB_BCTL_Type;
typedef UDB_UDBIF_V1_Type UDB_UDBIF_Type;
typedef UDB_V1_Type UDB_Type;
typedef LPCOMP_V1_Type LPCOMP_Type;
typedef CSD_V1_Type CSD_Type;
typedef TCPWM_CNT_V1_Type TCPWM_CNT_Type;
typedef TCPWM_V1_Type TCPWM_Type;
typedef LCD_V1_Type LCD_Type;
typedef BLE_RCB_RCBLL_V1_Type BLE_RCB_RCBLL_Type;
typedef BLE_RCB_V1_Type BLE_RCB_Type;
typedef BLE_BLELL_V1_Type BLE_BLELL_Type;
typedef BLE_BLESS_V1_Type BLE_BLESS_Type;
typedef BLE_V1_Type BLE_Type;
typedef USBFS_USBDEV_V1_Type USBFS_USBDEV_Type;
typedef USBFS_USBLPM_V1_Type USBFS_USBLPM_Type;
typedef USBFS_USBHOST_V1_Type USBFS_USBHOST_Type;
typedef USBFS_V1_Type USBFS_Type;
typedef SMIF_DEVICE_V1_Type SMIF_DEVICE_Type;
typedef SMIF_V1_Type SMIF_Type;
typedef SDHC_WRAP_V1_Type SDHC_WRAP_Type;
typedef SDHC_CORE_V1_Type SDHC_CORE_Type;
typedef SDHC_V1_Type SDHC_Type;
typedef CySCB_V1_Type CySCB_Type;
typedef CTBM_V1_Type CTBM_Type;
typedef CTDAC_V1_Type CTDAC_Type;
typedef SAR_V1_Type SAR_Type;
typedef PASS_AREF_V1_Type PASS_AREF_Type;
typedef PASS_V1_Type PASS_Type;
typedef PDM_V1_Type PDM_Type;
typedef I2S_V1_Type I2S_Type;
typedef CANFD_V1_Type CANFD_Type;
typedef CANFD_CH_V1_Type CANFD_CH_Type;
typedef CANFD_CH_M_TTCAN_V1_Type CANFD_CH_M_TTCAN_Type;

/*******************************************************************************
*             Symbols with External Linkage
*******************************************************************************/

extern uint32_t cy_PeriClkFreqHz;
extern uint32_t cy_BleEcoClockFreqHz;
extern uint32_t cy_Hfclk0FreqHz;
extern uint32_t cy_delayFreqKhz;
extern uint8_t  cy_delayFreqMhz;
extern uint32_t cy_AhbFreqHz;

extern void SystemCoreClockUpdate(void);
extern uint32_t Cy_SysGetCM4Status(void);

/*******************************************************************************
*             Platform and Peripheral Parameters
*******************************************************************************/

/* Flash Start Address and Size */
#define CY_FLASH_BASE                   0x10000000UL
#define CY_FLASH_SIZE                   0x00100000UL
/* Page size in # of 32-bit words (1: 4 bytes, 2: 8 bytes, ... */
#define CPUSS_FLASHC_PA_SIZE            128u
/* EEPROM Start Address and Size */
#define CY_EM_EEPROM_BASE               0x14000000UL
#define CY_EM_EEPROM_SIZE               0x00008000UL
/* Number of 8.0 dividers */
#define PERI_DIV_8_NR                   8u
/* Number of 16.0 dividers */
#define PERI_DIV_16_NR                  16u
/* Number of 16.5 (fractional) dividers */
#define PERI_DIV_16_5_NR                4u
/* Number of 24.5 (fractional) dividers */
#define PERI_DIV_24_5_NR                1u
/* The number of protection contexts ([2, 16]). */
#define PERI_PC_NR                      8u
/* Number of external devices supported ([1,4]) */
#define SMIF_DEVICE_NR                  4u
/* Number of ports in device */
#define IOSS_GPIO_GPIO_PORT_NR          15u
/* Number of SAR channels */
#define PASS_SAR_SAR_CHANNELS           16u
/* CM4 Enabled State */
#define CY_SYS_CM4_STATUS_ENABLED       3U
/* Cryptography IP present or not (0=No, 1=Yes) */
#define CPUSS_CRYPTO_PRESENT            1u
/* AES cipher support (0 = no support, 1 = support */
#define CPUSS_CRYPTO_AES                1u
/* (Tripple) DES cipher support (0 = no support, 1 = support */
#define CPUSS_CRYPTO_DES                1u
/* Pseudo random number generation support (0 = no support, 1 = support) */
#define CPUSS_CRYPTO_PR                 1u
/* SHA support included */
#define CPUSS_CRYPTO_SHA                1u
/* SHA1 hash support (0 = no support, 1 = support) */
#define CPUSS_CRYPTO_SHA1               1u
/* SHA256 hash support (0 = no support, 1 = support) */
#define CPUSS_CRYPTO_SHA256             1u
/* SHA512 hash support (0 = no support, 1 = support) */
#define CPUSS_CRYPTO_SHA512             1u
/* Cyclic Redundancy Check support (0 = no support, 1 = support) */
#define CPUSS_CRYPTO_CRC                1u
/* Vector unit support (0 = no support, 1 = support) */
#define CPUSS_CRYPTO_VU                 1u
/* True random number generation support (0 = no support, 1 = support) */
#define CPUSS_CRYPTO_TR                 1u
/* String support (0 = no support, 1 = support) */
#define CPUSS_CRYPTO_STR                1u
/* Number of ports supoprting up to 4 COMs */
#define LCD_NUMPORTS                    8u
/* Number of ports supporting up to 8 COMs */
#define LCD_NUMPORTS8                   8u
/* Number of ports supporting up to 16 COMs */
#define LCD_NUMPORTS16                  0u
/* SRAM0 is implemented with 8 32KB macros. */
#define CPUSS_RAMC0_MACRO_NR            9u
/* System RAM 1 present or not (0=No, 1=Yes) */
#define CPUSS_RAMC1_PRESENT             0u
/* System RAM 1 size in kilobytes */
#define CPUSS_SRAM1_SIZE                32u
/* Number of macros used to implement System RAM 1. Example: 8 if 256 KB System
   RAM 1 is implemented with 8 32KB macros. */
#define CPUSS_RAMC1_MACRO_NR            1u
/* System RAM 2 present or not (0=No, 1=Yes) */
#define CPUSS_RAMC2_PRESENT             0u
/* System RAM 2 size in kilobytes */
#define CPUSS_SRAM2_SIZE                256u
/* Number of macros used to implement System RAM 2. Example: 8 if 256 KB System
   RAM 2 is implemented with 8 32KB macros. */
#define CPUSS_RAMC2_MACRO_NR            16u
/* System ROM size in KB */
#define CPUSS_ROM_SIZE                  128u
/* Number of DMAC channels */
#define CPUSS_DMAC_CH_NR                4u

/*******************************************************************************
*           Access Definitions for IP Blocks
*******************************************************************************/

#define SFLASH_BASE                             0x16000000UL
#define SFLASH                                  ((SFLASH_Type*) SFLASH_BASE)
#define SRSS_BASE                               0x40260000UL
#define SRSS                                    ((SRSS_Type*) SRSS_BASE)
#define BACKUP_BASE                             0x40270000UL
#define BACKUP                                  ((BACKUP_Type*) BACKUP_BASE)
#define PROFILE_BASE                            0x402D0000UL
#define PROFILE                                 ((PROFILE_Type*) PROFILE_BASE)
#define BLE_BASE                                0x403C0000UL
#define BLE                                     ((BLE_Type*) BLE_BASE)
#define CRYPTO_BASE                             0x40110000UL
#define CRYPTO                                  ((CRYPTO_Type*) CRYPTO_BASE)                                      /* 0x40110000 */
#define CTBM0_BASE                              0x40900000UL                                            /* for the PASS_v2 only */
#define CTBM0                                   ((CTBM_Type*) CTBM0_BASE)                                         /* 0x40900000 */
#endif /* _CY_DEVICE_COMMON_H_ */


/* [] END OF FILE */
