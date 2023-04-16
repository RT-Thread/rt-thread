/***************************************************************************//**
* \file cyw20829a0kml.h
*
* \brief
* CYW20829A0KML device header
*
********************************************************************************
* \copyright
* (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
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

#ifndef _CYW20829A0KML_H_
#define _CYW20829A0KML_H_

/**
* \addtogroup group_device CYW20829A0KML
* \{
*/

/**
* \addtogroup Configuration_of_CMSIS
* \{
*/

/*******************************************************************************
*                         Interrupt Number Definition
*******************************************************************************/

typedef enum {
  /* ARM Cortex-M33 Core Interrupt Numbers */
  Reset_IRQn                        = -15,      /*!< -15 Reset Vector, invoked on Power up and warm reset */
  NonMaskableInt_IRQn               = -14,      /*!< -14 Non maskable Interrupt, cannot be stopped or preempted */
  HardFault_IRQn                    = -13,      /*!< -13 Hard Fault, all classes of Fault */
  MemoryManagement_IRQn             = -12,      /*!< -12 Memory Management, MPU mismatch, including Access Violation and No Match */
  BusFault_IRQn                     = -11,      /*!< -11 Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory related Fault */
  UsageFault_IRQn                   = -10,      /*!< -10 Usage Fault, i.e. Undef Instruction, Illegal State Transition */
  SecureFault_IRQn                  =  -9,      /*!<  -9 Secure Fault Interrupt */
  SVCall_IRQn                       =  -5,      /*!<  -5 System Service Call via SVC instruction */
  DebugMonitor_IRQn                 =  -4,      /*!<  -4 Debug Monitor */
  PendSV_IRQn                       =  -2,      /*!<  -2 Pendable request for system service */
  SysTick_IRQn                      =  -1,      /*!<  -1 System Tick Timer */
  /* CYW20829A0KML Peripheral Interrupt Numbers */
  ioss_interrupts_gpio_0_IRQn       =   0,      /*!<   0 [DeepSleep] GPIO Port Interrupt #0 */
  ioss_interrupts_gpio_1_IRQn       =   1,      /*!<   1 [DeepSleep] GPIO Port Interrupt #1 */
  ioss_interrupts_gpio_2_IRQn       =   2,      /*!<   2 [DeepSleep] GPIO Port Interrupt #2 */
  ioss_interrupts_gpio_3_IRQn       =   3,      /*!<   3 [DeepSleep] GPIO Port Interrupt #3 */
  ioss_interrupts_gpio_4_IRQn       =   4,      /*!<   4 [DeepSleep] GPIO Port Interrupt #4 */
  ioss_interrupts_gpio_5_IRQn       =   5,      /*!<   5 [DeepSleep] GPIO Port Interrupt #5 */
  ioss_interrupt_vdd_IRQn           =   6,      /*!<   6 [DeepSleep] GPIO Supply Detect Interrupt */
  ioss_interrupt_gpio_IRQn          =   7,      /*!<   7 [DeepSleep] GPIO All Ports */
  scb_0_interrupt_IRQn              =   8,      /*!<   8 [DeepSleep] Serial Communication Block #0 (DeepSleep capable) */
  srss_interrupt_mcwdt_0_IRQn       =   9,      /*!<   9 [DeepSleep] Multi Counter Watchdog Timer interrupt */
  srss_interrupt_backup_IRQn        =  10,      /*!<  10 [DeepSleep] Backup domain interrupt */
  srss_interrupt_IRQn               =  11,      /*!<  11 [DeepSleep] Other combined Interrupts for srss (LVD and CLKCAL, CLKCAL only supported in Active mode) */
  cpuss_interrupts_ipc_dpslp_0_IRQn =  12,      /*!<  12 [DeepSleep] cpuss Inter Process Communication Interrupt #0 */
  cpuss_interrupts_ipc_dpslp_1_IRQn =  13,      /*!<  13 [DeepSleep] cpuss Inter Process Communication Interrupt #1 */
  keyscan_interrupt_IRQn            =  14,      /*!<  14 [DeepSleep] mxkeyscan interrupt for keyscan edge or fifo thresh to WIC in M33 */
  srss_interrupt_wdt_IRQn           =  15,      /*!<  15 [DeepSleep] Interrupt from WDT */
  btss_interrupt_btss_ipc_IRQn      =  16,      /*!<  16 [DeepSleep] interrupt from BTSS IPC */
  scb_1_interrupt_IRQn              =  17,      /*!<  17 [Active] Serial Communication Block #1 */
  scb_2_interrupt_IRQn              =  18,      /*!<  18 [Active] Serial Communication Block #2 */
  cpuss_interrupts_dw0_0_IRQn       =  19,      /*!<  19 [Active] cpuss DataWire #0, Channel #0 */
  cpuss_interrupts_dw0_1_IRQn       =  20,      /*!<  20 [Active] cpuss DataWire #0, Channel #1 */
  cpuss_interrupts_dw0_2_IRQn       =  21,      /*!<  21 [Active] cpuss DataWire #0, Channel #2 */
  cpuss_interrupts_dw0_3_IRQn       =  22,      /*!<  22 [Active] cpuss DataWire #0, Channel #3 */
  cpuss_interrupts_dw0_4_IRQn       =  23,      /*!<  23 [Active] cpuss DataWire #0, Channel #4 */
  cpuss_interrupts_dw0_5_IRQn       =  24,      /*!<  24 [Active] cpuss DataWire #0, Channel #5 */
  cpuss_interrupts_dw0_6_IRQn       =  25,      /*!<  25 [Active] cpuss DataWire #0, Channel #6 */
  cpuss_interrupts_dw0_7_IRQn       =  26,      /*!<  26 [Active] cpuss DataWire #0, Channel #7 */
  cpuss_interrupts_dw0_8_IRQn       =  27,      /*!<  27 [Active] cpuss DataWire #0, Channel #8 */
  cpuss_interrupts_dw0_9_IRQn       =  28,      /*!<  28 [Active] cpuss DataWire #0, Channel #9 */
  cpuss_interrupts_dw0_10_IRQn      =  29,      /*!<  29 [Active] cpuss DataWire #0, Channel #10 */
  cpuss_interrupts_dw0_11_IRQn      =  30,      /*!<  30 [Active] cpuss DataWire #0, Channel #11 */
  cpuss_interrupts_dw0_12_IRQn      =  31,      /*!<  31 [Active] cpuss DataWire #0, Channel #12 */
  cpuss_interrupts_dw0_13_IRQn      =  32,      /*!<  32 [Active] cpuss DataWire #0, Channel #13 */
  cpuss_interrupts_dw0_14_IRQn      =  33,      /*!<  33 [Active] cpuss DataWire #0, Channel #14 */
  cpuss_interrupts_dw0_15_IRQn      =  34,      /*!<  34 [Active] cpuss DataWire #0, Channel #15 */
  cpuss_interrupt_mpc_promc_IRQn    =  35,      /*!<  35 [Active] PROMC Int */
  cpuss_interrupt_ppu_sramc0_IRQn   =  36,      /*!<  36 [Active] PPU SRAM0 */
  cpuss_interrupt_mpc_sramc0_IRQn   =  37,      /*!<  37 [Active] MPC SRAM0 */
  cpuss_interrupt_cm33_0_fp_IRQn    =  38,      /*!<  38 [Active] CM33 0 Floating Point Interrupt */
  cpuss_interrupts_cm33_0_cti_0_IRQn =  39,     /*!<  39 [Active] CM33-0 CTI interrupt outputs */
  cpuss_interrupts_cm33_0_cti_1_IRQn =  40,     /*!<  40 [Active] CM33-1 CTI interrupt outputs */
  cpuss_interrupt_exp_br_ahb_error_IRQn =  41,  /*!<  41 [Active] EXPANSION BRIDGE AHB Error interrupt */
  tcpwm_0_interrupts_0_IRQn         =  42,      /*!<  42 [Active] TCPWM #0, Counter #0 */
  tcpwm_0_interrupts_1_IRQn         =  43,      /*!<  43 [Active] TCPWM #0, Counter #1 */
  tcpwm_0_interrupts_256_IRQn       =  44,      /*!<  44 [Active] TCPWM #0, Counter #256 */
  tcpwm_0_interrupts_257_IRQn       =  45,      /*!<  45 [Active] TCPWM #0, Counter #257 */
  tcpwm_0_interrupts_258_IRQn       =  46,      /*!<  46 [Active] TCPWM #0, Counter #258 */
  tcpwm_0_interrupts_259_IRQn       =  47,      /*!<  47 [Active] TCPWM #0, Counter #259 */
  tcpwm_0_interrupts_260_IRQn       =  48,      /*!<  48 [Active] TCPWM #0, Counter #260 */
  tcpwm_0_interrupts_261_IRQn       =  49,      /*!<  49 [Active] TCPWM #0, Counter #261 */
  tcpwm_0_interrupts_262_IRQn       =  50,      /*!<  50 [Active] TCPWM #0, Counter #262 */
  smif_interrupt_normal_IRQn        =  51,      /*!<  51 [Active] Serial Memory Interface interrupt */
  smif_interrupt_mpc_IRQn           =  52,      /*!<  52 [Active] Serial Memory Interface interrupt */
  tdm_0_interrupts_rx_0_IRQn        =  53,      /*!<  53 [Active] TDM0 Audio interrupt RX */
  tdm_0_interrupts_tx_0_IRQn        =  54,      /*!<  54 [Active] TDM0 Audio interrupt TX */
  pdm_0_interrupts_0_IRQn           =  55,      /*!<  55 [Active] PDM0/PCM0 Audio interrupt */
  pdm_0_interrupts_1_IRQn           =  56,      /*!<  56 [Active] PDM0/PCM0 Audio interrupt */
  srss_interrupt_main_ppu_IRQn      =  57,      /*!<  57 [Active] SRSS Main PPU Interrupt */
  peri_interrupt_ppc_IRQn           =  58,      /*!<  58 [Active] PERI PPC Interrupt */
  peri_interrupt_ahb_error_IRQn     =  59,      /*!<  59 [Active] PERI AHB Interrupt */
  lin_0_interrupts_0_IRQn           =  60,      /*!<  60 [Active] LIN Interrupt, Channel #0 */
  lin_0_interrupts_1_IRQn           =  61,      /*!<  61 [Active] LIN Interrupt, Channel #1 */
  crypto_interrupt_error_IRQn       =  62,      /*!<  62 [Active] Crypto Interrupt */
  cpuss_interrupt_ppu_cpuss_IRQn    =  63,      /*!<  63 [Active] CPUSS PPU Interrupt */
  canfd_0_interrupts0_0_IRQn        =  64,      /*!<  64 [Active] CAN #0, Interrupt #0, Channel #0 */
  canfd_0_interrupts1_0_IRQn        =  65,      /*!<  65 [Active] CAN #0, Interrupt #1, Channel #0 */
  canfd_0_interrupt0_IRQn           =  66,      /*!<  66 [Active] Can #0, Consolidated interrupt #0 */
  adcmic_interrupt_adcmic_IRQn      =  67,      /*!<  67 [Active] ADCMIC interrupt */
  btss_interrupt_btss_exception_IRQn =  68,     /*!<  68 [Active] interrupt indicating BTSS has encountered exception */
  unconnected_IRQn                  = 240       /*!< 240 Unconnected */
} IRQn_Type;


/*******************************************************************************
*                    Processor and Core Peripheral Section
*******************************************************************************/

/* Configuration of the ARM Cortex-M33 Processor and Core Peripherals */
#define __CM33_REV                      0x0001U /*!< CM33 Core Revision */
#define __NVIC_PRIO_BITS                3       /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig          0       /*!< Set to 1 if different SysTick Config is used */
#define __VTOR_PRESENT                  1       /*!< Set to 1 if CPU supports Vector Table Offset Register */
#define __MPU_PRESENT                   1       /*!< MPU present or not */
#define __FPU_PRESENT                   1       /*!< FPU present or not */
#define __CM0P_PRESENT                  0       /*!< CM0P present or not */
#define __DTCM_PRESENT                  0       /*!< Data Tightly Coupled Memory is present or not */
#define __ICACHE_PRESENT                0       /*!< Instruction Cache present or not */
#define __DCACHE_PRESENT                0       /*!< Data Cache present or not */
#define __DSP_PRESENT                   0       /*!< DSP extension present or not */

/** \} Configuration_of_CMSIS */

#include "core_cm33.h"                          /*!< ARM Cortex-M33 processor and core peripherals */


/* Memory Blocks */
#define CY_ROM_BASE                     0x00000000UL
#define CY_ROM_SIZE                     0x00010000UL
#define CY_ROM_SECURE_OFFSET            0x10000000UL
#define CY_ROM_REMAP_OFFSET             0x00000000UL
#define CY_ROM_REMAP_SECURE_OFFSET      0x10000000UL
#define CY_CAN0MRAM_BASE                0x40450000UL
#define CY_CAN0MRAM_SIZE                0x00010000UL
#define CY_EFUSE_BASE                   0x40810800UL
#define CY_EFUSE_SIZE                   0x00000200UL
#define CY_XIP_BASE                     0x60000000UL
#define CY_XIP_SIZE                     0x08000000UL
#define CY_XIP_SECURE_OFFSET            0x70000000UL
#define CY_XIP_REMAP_OFFSET             0x08000000UL
#define CY_XIP_REMAP_SECURE_OFFSET      0x18000000UL
#define CY_SRAM0_BASE                   0x20000000UL
#define CY_SRAM0_SIZE                   0x00020000UL
#define CY_SRAM0_SECURE_OFFSET          0x30000000UL
#define CY_SRAM0_REMAP_OFFSET           0x04000000UL
#define CY_SRAM0_REMAP_SECURE_OFFSET    0x14000000UL

#include "system_cat1b.h"                       /*!< Category 1B System */

/* IP List */
#define CY_IP_MXS40ADCMIC               1u
#define CY_IP_MXS40ADCMIC_INSTANCES     1u
#define CY_IP_MXS40ADCMIC_VERSION       1u
#define CY_IP_MXS40BLE52SS              1u
#define CY_IP_MXS40BLE52SS_INSTANCES    1u
#define CY_IP_MXS40BLE52SS_VERSION      1u
#define CY_IP_MXTTCANFD                 1u
#define CY_IP_MXTTCANFD_INSTANCES       1u
#define CY_IP_MXTTCANFD_VERSION         3u
#define CY_IP_M33SYSCPUSS               1u
#define CY_IP_M33SYSCPUSS_INSTANCES     1u
#define CY_IP_M33SYSCPUSS_VERSION       1u
#define CY_IP_MXCRYPTOLITE              1u
#define CY_IP_MXCRYPTOLITE_INSTANCES    1u
#define CY_IP_MXCRYPTOLITE_VERSION      1u
#define CY_IP_MXDFT                     1u
#define CY_IP_MXDFT_INSTANCES           1u
#define CY_IP_MXDFT_VERSION             2u
#define CY_IP_MXEFUSE                   1u
#define CY_IP_MXEFUSE_INSTANCES         1u
#define CY_IP_MXEFUSE_VERSION           3u
#define CY_IP_MXS40SIOSS                1u
#define CY_IP_MXS40SIOSS_INSTANCES      1u
#define CY_IP_MXS40SIOSS_VERSION        1u
#define CY_IP_MXKEYSCAN                 1u
#define CY_IP_MXKEYSCAN_INSTANCES       1u
#define CY_IP_MXKEYSCAN_VERSION         1u
#define CY_IP_MXLIN                     1u
#define CY_IP_MXLIN_INSTANCES           1u
#define CY_IP_MXLIN_VERSION             1u
#define CY_IP_MXCM33                    1u
#define CY_IP_MXCM33_INSTANCES          1u
#define CY_IP_MXCM33_VERSION            1u
#define CY_IP_MXDW                      1u
#define CY_IP_MXDW_INSTANCES            1u
#define CY_IP_MXDW_VERSION              1u
#define CY_IP_MXIPC                     1u
#define CY_IP_MXIPC_INSTANCES           1u
#define CY_IP_MXIPC_VERSION             1u
#define CY_IP_MXPROMC                   1u
#define CY_IP_MXPROMC_INSTANCES         1u
#define CY_IP_MXPROMC_VERSION           1u
#define CY_IP_MXSRAMC                   1u
#define CY_IP_MXSRAMC_INSTANCES         1u
#define CY_IP_MXSRAMC_VERSION           1u
#define CY_IP_MXPDM                     1u
#define CY_IP_MXPDM_INSTANCES           1u
#define CY_IP_MXPDM_VERSION             1u
#define CY_IP_MXSPERI                   1u
#define CY_IP_MXSPERI_INSTANCES         1u
#define CY_IP_MXSPERI_VERSION           1u
#define CY_IP_MXSPERI_TR                1u
#define CY_IP_MXSPERI_TR_INSTANCES      1u
#define CY_IP_MXSPERI_TR_VERSION        1u
#define CY_IP_MXSCB                     1u
#define CY_IP_MXSCB_INSTANCES           3u
#define CY_IP_MXSCB_VERSION             4u
#define CY_IP_MXSMIF                    1u
#define CY_IP_MXSMIF_INSTANCES          1u
#define CY_IP_MXSMIF_VERSION            3u
#define CY_IP_MXS40SSRSS                1u
#define CY_IP_MXS40SSRSS_INSTANCES      1u
#define CY_IP_MXS40SSRSS_VERSION        1u
#define CY_IP_MXTCPWM                   1u
#define CY_IP_MXTCPWM_INSTANCES         1u
#define CY_IP_MXTCPWM_VERSION           2u
#define CY_IP_MXTDM                     1u
#define CY_IP_MXTDM_INSTANCES           1u
#define CY_IP_MXTDM_VERSION             1u

#include "cyw20829_config.h"
#include "gpio_cyw20829_40_qfn.h"

#define CY_DEVICE_CYW20829
#define CY_DEVICE_SERIES_20829
#define CY_SILICON_ID                   0x1EB41069UL
#define CY_HF_CLK_MAX_FREQ              96000000UL


/*******************************************************************************
*                                     PERI
*******************************************************************************/

#define PERI_BASE                               0x40000000UL
#define PERI                                    ((PERI_Type*) PERI_BASE)                                          /* 0x40000000 */
#define PERI_GR0                                ((PERI_GR_Type*) &PERI->GR[0])                                    /* 0x40004000 */
#define PERI_GR1                                ((PERI_GR_Type*) &PERI->GR[1])                                    /* 0x40004040 */
#define PERI_GR2                                ((PERI_GR_Type*) &PERI->GR[2])                                    /* 0x40004080 */
#define PERI_GR3                                ((PERI_GR_Type*) &PERI->GR[3])                                    /* 0x400040C0 */
#define PERI_TR_GR0                             ((PERI_TR_GR_Type*) &PERI->TR_GR[0])                              /* 0x40008000 */
#define PERI_TR_GR1                             ((PERI_TR_GR_Type*) &PERI->TR_GR[1])                              /* 0x40008400 */
#define PERI_TR_GR2                             ((PERI_TR_GR_Type*) &PERI->TR_GR[2])                              /* 0x40008800 */
#define PERI_TR_GR3                             ((PERI_TR_GR_Type*) &PERI->TR_GR[3])                              /* 0x40008C00 */
#define PERI_TR_GR4                             ((PERI_TR_GR_Type*) &PERI->TR_GR[4])                              /* 0x40009000 */
#define PERI_TR_GR5                             ((PERI_TR_GR_Type*) &PERI->TR_GR[5])                              /* 0x40009400 */
#define PERI_TR_GR6                             ((PERI_TR_GR_Type*) &PERI->TR_GR[6])                              /* 0x40009800 */
#define PERI_TR_GR7                             ((PERI_TR_GR_Type*) &PERI->TR_GR[7])                              /* 0x40009C00 */
#define PERI_TR_GR8                             ((PERI_TR_GR_Type*) &PERI->TR_GR[8])                              /* 0x4000A000 */
#define PERI_TR_GR9                             ((PERI_TR_GR_Type*) &PERI->TR_GR[9])                              /* 0x4000A400 */
#define PERI_TR_1TO1_GR0                        ((PERI_TR_1TO1_GR_Type*) &PERI->TR_1TO1_GR[0])                    /* 0x4000C000 */
#define PERI_TR_1TO1_GR1                        ((PERI_TR_1TO1_GR_Type*) &PERI->TR_1TO1_GR[1])                    /* 0x4000C400 */
#define PERI_TR_1TO1_GR2                        ((PERI_TR_1TO1_GR_Type*) &PERI->TR_1TO1_GR[2])                    /* 0x4000C800 */
#define PERI_TR_1TO1_GR3                        ((PERI_TR_1TO1_GR_Type*) &PERI->TR_1TO1_GR[3])                    /* 0x4000CC00 */
#define PERI_TR_1TO1_GR4                        ((PERI_TR_1TO1_GR_Type*) &PERI->TR_1TO1_GR[4])                    /* 0x4000D000 */

/*******************************************************************************
*                                     PPC
*******************************************************************************/

#define PPC_BASE                                0x40020000UL
#define PPC                                     ((PPC_Type*) PPC_BASE)                                            /* 0x40020000 */
#define PPC_R_ADDR0                             ((PPC_R_ADDR_Type*) &PPC->R_ADDR[0])                              /* 0x40025000 */
#define PPC_R_ADDR1                             ((PPC_R_ADDR_Type*) &PPC->R_ADDR[1])                              /* 0x40025004 */
#define PPC_R_ADDR2                             ((PPC_R_ADDR_Type*) &PPC->R_ADDR[2])                              /* 0x40025008 */
#define PPC_R_ADDR3                             ((PPC_R_ADDR_Type*) &PPC->R_ADDR[3])                              /* 0x4002500C */
#define PPC_R_ADDR4                             ((PPC_R_ADDR_Type*) &PPC->R_ADDR[4])                              /* 0x40025010 */
#define PPC_R_ADDR5                             ((PPC_R_ADDR_Type*) &PPC->R_ADDR[5])                              /* 0x40025014 */
#define PPC_R_ADDR6                             ((PPC_R_ADDR_Type*) &PPC->R_ADDR[6])                              /* 0x40025018 */
#define PPC_R_ADDR7                             ((PPC_R_ADDR_Type*) &PPC->R_ADDR[7])                              /* 0x4002501C */
#define PPC_R_ADDR8                             ((PPC_R_ADDR_Type*) &PPC->R_ADDR[8])                              /* 0x40025020 */
#define PPC_R_ADDR9                             ((PPC_R_ADDR_Type*) &PPC->R_ADDR[9])                              /* 0x40025024 */
#define PPC_R_ADDR10                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[10])                             /* 0x40025028 */
#define PPC_R_ADDR11                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[11])                             /* 0x4002502C */
#define PPC_R_ADDR12                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[12])                             /* 0x40025030 */
#define PPC_R_ADDR13                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[13])                             /* 0x40025034 */
#define PPC_R_ADDR14                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[14])                             /* 0x40025038 */
#define PPC_R_ADDR15                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[15])                             /* 0x4002503C */
#define PPC_R_ADDR16                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[16])                             /* 0x40025040 */
#define PPC_R_ADDR17                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[17])                             /* 0x40025044 */
#define PPC_R_ADDR18                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[18])                             /* 0x40025048 */
#define PPC_R_ADDR19                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[19])                             /* 0x4002504C */
#define PPC_R_ADDR20                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[20])                             /* 0x40025050 */
#define PPC_R_ADDR21                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[21])                             /* 0x40025054 */
#define PPC_R_ADDR22                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[22])                             /* 0x40025058 */
#define PPC_R_ADDR23                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[23])                             /* 0x4002505C */
#define PPC_R_ADDR24                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[24])                             /* 0x40025060 */
#define PPC_R_ADDR25                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[25])                             /* 0x40025064 */
#define PPC_R_ADDR26                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[26])                             /* 0x40025068 */
#define PPC_R_ADDR27                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[27])                             /* 0x4002506C */
#define PPC_R_ADDR28                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[28])                             /* 0x40025070 */
#define PPC_R_ADDR29                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[29])                             /* 0x40025074 */
#define PPC_R_ADDR30                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[30])                             /* 0x40025078 */
#define PPC_R_ADDR31                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[31])                             /* 0x4002507C */
#define PPC_R_ADDR32                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[32])                             /* 0x40025080 */
#define PPC_R_ADDR33                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[33])                             /* 0x40025084 */
#define PPC_R_ADDR34                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[34])                             /* 0x40025088 */
#define PPC_R_ADDR35                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[35])                             /* 0x4002508C */
#define PPC_R_ADDR36                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[36])                             /* 0x40025090 */
#define PPC_R_ADDR37                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[37])                             /* 0x40025094 */
#define PPC_R_ADDR38                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[38])                             /* 0x40025098 */
#define PPC_R_ADDR39                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[39])                             /* 0x4002509C */
#define PPC_R_ADDR40                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[40])                             /* 0x400250A0 */
#define PPC_R_ADDR41                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[41])                             /* 0x400250A4 */
#define PPC_R_ADDR42                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[42])                             /* 0x400250A8 */
#define PPC_R_ADDR43                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[43])                             /* 0x400250AC */
#define PPC_R_ADDR44                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[44])                             /* 0x400250B0 */
#define PPC_R_ADDR45                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[45])                             /* 0x400250B4 */
#define PPC_R_ADDR46                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[46])                             /* 0x400250B8 */
#define PPC_R_ADDR47                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[47])                             /* 0x400250BC */
#define PPC_R_ADDR48                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[48])                             /* 0x400250C0 */
#define PPC_R_ADDR49                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[49])                             /* 0x400250C4 */
#define PPC_R_ADDR50                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[50])                             /* 0x400250C8 */
#define PPC_R_ADDR51                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[51])                             /* 0x400250CC */
#define PPC_R_ADDR52                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[52])                             /* 0x400250D0 */
#define PPC_R_ADDR53                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[53])                             /* 0x400250D4 */
#define PPC_R_ADDR54                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[54])                             /* 0x400250D8 */
#define PPC_R_ADDR55                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[55])                             /* 0x400250DC */
#define PPC_R_ADDR56                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[56])                             /* 0x400250E0 */
#define PPC_R_ADDR57                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[57])                             /* 0x400250E4 */
#define PPC_R_ADDR58                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[58])                             /* 0x400250E8 */
#define PPC_R_ADDR59                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[59])                             /* 0x400250EC */
#define PPC_R_ADDR60                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[60])                             /* 0x400250F0 */
#define PPC_R_ADDR61                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[61])                             /* 0x400250F4 */
#define PPC_R_ADDR62                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[62])                             /* 0x400250F8 */
#define PPC_R_ADDR63                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[63])                             /* 0x400250FC */
#define PPC_R_ADDR64                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[64])                             /* 0x40025100 */
#define PPC_R_ADDR65                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[65])                             /* 0x40025104 */
#define PPC_R_ADDR66                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[66])                             /* 0x40025108 */
#define PPC_R_ADDR67                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[67])                             /* 0x4002510C */
#define PPC_R_ADDR68                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[68])                             /* 0x40025110 */
#define PPC_R_ADDR69                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[69])                             /* 0x40025114 */
#define PPC_R_ADDR70                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[70])                             /* 0x40025118 */
#define PPC_R_ADDR71                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[71])                             /* 0x4002511C */
#define PPC_R_ADDR72                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[72])                             /* 0x40025120 */
#define PPC_R_ADDR73                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[73])                             /* 0x40025124 */
#define PPC_R_ADDR74                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[74])                             /* 0x40025128 */
#define PPC_R_ADDR75                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[75])                             /* 0x4002512C */
#define PPC_R_ADDR76                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[76])                             /* 0x40025130 */
#define PPC_R_ADDR77                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[77])                             /* 0x40025134 */
#define PPC_R_ADDR78                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[78])                             /* 0x40025138 */
#define PPC_R_ADDR79                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[79])                             /* 0x4002513C */
#define PPC_R_ADDR80                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[80])                             /* 0x40025140 */
#define PPC_R_ADDR81                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[81])                             /* 0x40025144 */
#define PPC_R_ADDR82                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[82])                             /* 0x40025148 */
#define PPC_R_ADDR83                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[83])                             /* 0x4002514C */
#define PPC_R_ADDR84                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[84])                             /* 0x40025150 */
#define PPC_R_ADDR85                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[85])                             /* 0x40025154 */
#define PPC_R_ADDR86                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[86])                             /* 0x40025158 */
#define PPC_R_ADDR87                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[87])                             /* 0x4002515C */
#define PPC_R_ADDR88                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[88])                             /* 0x40025160 */
#define PPC_R_ADDR89                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[89])                             /* 0x40025164 */
#define PPC_R_ADDR90                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[90])                             /* 0x40025168 */
#define PPC_R_ADDR91                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[91])                             /* 0x4002516C */
#define PPC_R_ADDR92                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[92])                             /* 0x40025170 */
#define PPC_R_ADDR93                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[93])                             /* 0x40025174 */
#define PPC_R_ADDR94                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[94])                             /* 0x40025178 */
#define PPC_R_ADDR95                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[95])                             /* 0x4002517C */
#define PPC_R_ADDR96                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[96])                             /* 0x40025180 */
#define PPC_R_ADDR97                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[97])                             /* 0x40025184 */
#define PPC_R_ADDR98                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[98])                             /* 0x40025188 */
#define PPC_R_ADDR99                            ((PPC_R_ADDR_Type*) &PPC->R_ADDR[99])                             /* 0x4002518C */
#define PPC_R_ADDR100                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[100])                            /* 0x40025190 */
#define PPC_R_ADDR101                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[101])                            /* 0x40025194 */
#define PPC_R_ADDR102                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[102])                            /* 0x40025198 */
#define PPC_R_ADDR103                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[103])                            /* 0x4002519C */
#define PPC_R_ADDR104                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[104])                            /* 0x400251A0 */
#define PPC_R_ADDR105                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[105])                            /* 0x400251A4 */
#define PPC_R_ADDR106                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[106])                            /* 0x400251A8 */
#define PPC_R_ADDR107                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[107])                            /* 0x400251AC */
#define PPC_R_ADDR108                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[108])                            /* 0x400251B0 */
#define PPC_R_ADDR109                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[109])                            /* 0x400251B4 */
#define PPC_R_ADDR110                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[110])                            /* 0x400251B8 */
#define PPC_R_ADDR111                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[111])                            /* 0x400251BC */
#define PPC_R_ADDR112                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[112])                            /* 0x400251C0 */
#define PPC_R_ADDR113                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[113])                            /* 0x400251C4 */
#define PPC_R_ADDR114                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[114])                            /* 0x400251C8 */
#define PPC_R_ADDR115                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[115])                            /* 0x400251CC */
#define PPC_R_ADDR116                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[116])                            /* 0x400251D0 */
#define PPC_R_ADDR117                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[117])                            /* 0x400251D4 */
#define PPC_R_ADDR118                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[118])                            /* 0x400251D8 */
#define PPC_R_ADDR119                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[119])                            /* 0x400251DC */
#define PPC_R_ADDR120                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[120])                            /* 0x400251E0 */
#define PPC_R_ADDR121                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[121])                            /* 0x400251E4 */
#define PPC_R_ADDR122                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[122])                            /* 0x400251E8 */
#define PPC_R_ADDR123                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[123])                            /* 0x400251EC */
#define PPC_R_ADDR124                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[124])                            /* 0x400251F0 */
#define PPC_R_ADDR125                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[125])                            /* 0x400251F4 */
#define PPC_R_ADDR126                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[126])                            /* 0x400251F8 */
#define PPC_R_ADDR127                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[127])                            /* 0x400251FC */
#define PPC_R_ADDR128                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[128])                            /* 0x40025200 */
#define PPC_R_ADDR129                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[129])                            /* 0x40025204 */
#define PPC_R_ADDR130                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[130])                            /* 0x40025208 */
#define PPC_R_ADDR131                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[131])                            /* 0x4002520C */
#define PPC_R_ADDR132                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[132])                            /* 0x40025210 */
#define PPC_R_ADDR133                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[133])                            /* 0x40025214 */
#define PPC_R_ADDR134                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[134])                            /* 0x40025218 */
#define PPC_R_ADDR135                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[135])                            /* 0x4002521C */
#define PPC_R_ADDR136                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[136])                            /* 0x40025220 */
#define PPC_R_ADDR137                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[137])                            /* 0x40025224 */
#define PPC_R_ADDR138                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[138])                            /* 0x40025228 */
#define PPC_R_ADDR139                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[139])                            /* 0x4002522C */
#define PPC_R_ADDR140                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[140])                            /* 0x40025230 */
#define PPC_R_ADDR141                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[141])                            /* 0x40025234 */
#define PPC_R_ADDR142                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[142])                            /* 0x40025238 */
#define PPC_R_ADDR143                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[143])                            /* 0x4002523C */
#define PPC_R_ADDR144                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[144])                            /* 0x40025240 */
#define PPC_R_ADDR145                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[145])                            /* 0x40025244 */
#define PPC_R_ADDR146                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[146])                            /* 0x40025248 */
#define PPC_R_ADDR147                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[147])                            /* 0x4002524C */
#define PPC_R_ADDR148                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[148])                            /* 0x40025250 */
#define PPC_R_ADDR149                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[149])                            /* 0x40025254 */
#define PPC_R_ADDR150                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[150])                            /* 0x40025258 */
#define PPC_R_ADDR151                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[151])                            /* 0x4002525C */
#define PPC_R_ADDR152                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[152])                            /* 0x40025260 */
#define PPC_R_ADDR153                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[153])                            /* 0x40025264 */
#define PPC_R_ADDR154                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[154])                            /* 0x40025268 */
#define PPC_R_ADDR155                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[155])                            /* 0x4002526C */
#define PPC_R_ADDR156                           ((PPC_R_ADDR_Type*) &PPC->R_ADDR[156])                            /* 0x40025270 */
#define PPC_R_ATT0                              ((PPC_R_ATT_Type*) &PPC->R_ATT[0])                                /* 0x40026000 */
#define PPC_R_ATT1                              ((PPC_R_ATT_Type*) &PPC->R_ATT[1])                                /* 0x40026004 */
#define PPC_R_ATT2                              ((PPC_R_ATT_Type*) &PPC->R_ATT[2])                                /* 0x40026008 */
#define PPC_R_ATT3                              ((PPC_R_ATT_Type*) &PPC->R_ATT[3])                                /* 0x4002600C */
#define PPC_R_ATT4                              ((PPC_R_ATT_Type*) &PPC->R_ATT[4])                                /* 0x40026010 */
#define PPC_R_ATT5                              ((PPC_R_ATT_Type*) &PPC->R_ATT[5])                                /* 0x40026014 */
#define PPC_R_ATT6                              ((PPC_R_ATT_Type*) &PPC->R_ATT[6])                                /* 0x40026018 */
#define PPC_R_ATT7                              ((PPC_R_ATT_Type*) &PPC->R_ATT[7])                                /* 0x4002601C */
#define PPC_R_ATT8                              ((PPC_R_ATT_Type*) &PPC->R_ATT[8])                                /* 0x40026020 */
#define PPC_R_ATT9                              ((PPC_R_ATT_Type*) &PPC->R_ATT[9])                                /* 0x40026024 */
#define PPC_R_ATT10                             ((PPC_R_ATT_Type*) &PPC->R_ATT[10])                               /* 0x40026028 */
#define PPC_R_ATT11                             ((PPC_R_ATT_Type*) &PPC->R_ATT[11])                               /* 0x4002602C */
#define PPC_R_ATT12                             ((PPC_R_ATT_Type*) &PPC->R_ATT[12])                               /* 0x40026030 */
#define PPC_R_ATT13                             ((PPC_R_ATT_Type*) &PPC->R_ATT[13])                               /* 0x40026034 */
#define PPC_R_ATT14                             ((PPC_R_ATT_Type*) &PPC->R_ATT[14])                               /* 0x40026038 */
#define PPC_R_ATT15                             ((PPC_R_ATT_Type*) &PPC->R_ATT[15])                               /* 0x4002603C */
#define PPC_R_ATT16                             ((PPC_R_ATT_Type*) &PPC->R_ATT[16])                               /* 0x40026040 */
#define PPC_R_ATT17                             ((PPC_R_ATT_Type*) &PPC->R_ATT[17])                               /* 0x40026044 */
#define PPC_R_ATT18                             ((PPC_R_ATT_Type*) &PPC->R_ATT[18])                               /* 0x40026048 */
#define PPC_R_ATT19                             ((PPC_R_ATT_Type*) &PPC->R_ATT[19])                               /* 0x4002604C */
#define PPC_R_ATT20                             ((PPC_R_ATT_Type*) &PPC->R_ATT[20])                               /* 0x40026050 */
#define PPC_R_ATT21                             ((PPC_R_ATT_Type*) &PPC->R_ATT[21])                               /* 0x40026054 */
#define PPC_R_ATT22                             ((PPC_R_ATT_Type*) &PPC->R_ATT[22])                               /* 0x40026058 */
#define PPC_R_ATT23                             ((PPC_R_ATT_Type*) &PPC->R_ATT[23])                               /* 0x4002605C */
#define PPC_R_ATT24                             ((PPC_R_ATT_Type*) &PPC->R_ATT[24])                               /* 0x40026060 */
#define PPC_R_ATT25                             ((PPC_R_ATT_Type*) &PPC->R_ATT[25])                               /* 0x40026064 */
#define PPC_R_ATT26                             ((PPC_R_ATT_Type*) &PPC->R_ATT[26])                               /* 0x40026068 */
#define PPC_R_ATT27                             ((PPC_R_ATT_Type*) &PPC->R_ATT[27])                               /* 0x4002606C */
#define PPC_R_ATT28                             ((PPC_R_ATT_Type*) &PPC->R_ATT[28])                               /* 0x40026070 */
#define PPC_R_ATT29                             ((PPC_R_ATT_Type*) &PPC->R_ATT[29])                               /* 0x40026074 */
#define PPC_R_ATT30                             ((PPC_R_ATT_Type*) &PPC->R_ATT[30])                               /* 0x40026078 */
#define PPC_R_ATT31                             ((PPC_R_ATT_Type*) &PPC->R_ATT[31])                               /* 0x4002607C */
#define PPC_R_ATT32                             ((PPC_R_ATT_Type*) &PPC->R_ATT[32])                               /* 0x40026080 */
#define PPC_R_ATT33                             ((PPC_R_ATT_Type*) &PPC->R_ATT[33])                               /* 0x40026084 */
#define PPC_R_ATT34                             ((PPC_R_ATT_Type*) &PPC->R_ATT[34])                               /* 0x40026088 */
#define PPC_R_ATT35                             ((PPC_R_ATT_Type*) &PPC->R_ATT[35])                               /* 0x4002608C */
#define PPC_R_ATT36                             ((PPC_R_ATT_Type*) &PPC->R_ATT[36])                               /* 0x40026090 */
#define PPC_R_ATT37                             ((PPC_R_ATT_Type*) &PPC->R_ATT[37])                               /* 0x40026094 */
#define PPC_R_ATT38                             ((PPC_R_ATT_Type*) &PPC->R_ATT[38])                               /* 0x40026098 */
#define PPC_R_ATT39                             ((PPC_R_ATT_Type*) &PPC->R_ATT[39])                               /* 0x4002609C */
#define PPC_R_ATT40                             ((PPC_R_ATT_Type*) &PPC->R_ATT[40])                               /* 0x400260A0 */
#define PPC_R_ATT41                             ((PPC_R_ATT_Type*) &PPC->R_ATT[41])                               /* 0x400260A4 */
#define PPC_R_ATT42                             ((PPC_R_ATT_Type*) &PPC->R_ATT[42])                               /* 0x400260A8 */
#define PPC_R_ATT43                             ((PPC_R_ATT_Type*) &PPC->R_ATT[43])                               /* 0x400260AC */
#define PPC_R_ATT44                             ((PPC_R_ATT_Type*) &PPC->R_ATT[44])                               /* 0x400260B0 */
#define PPC_R_ATT45                             ((PPC_R_ATT_Type*) &PPC->R_ATT[45])                               /* 0x400260B4 */
#define PPC_R_ATT46                             ((PPC_R_ATT_Type*) &PPC->R_ATT[46])                               /* 0x400260B8 */
#define PPC_R_ATT47                             ((PPC_R_ATT_Type*) &PPC->R_ATT[47])                               /* 0x400260BC */
#define PPC_R_ATT48                             ((PPC_R_ATT_Type*) &PPC->R_ATT[48])                               /* 0x400260C0 */
#define PPC_R_ATT49                             ((PPC_R_ATT_Type*) &PPC->R_ATT[49])                               /* 0x400260C4 */
#define PPC_R_ATT50                             ((PPC_R_ATT_Type*) &PPC->R_ATT[50])                               /* 0x400260C8 */
#define PPC_R_ATT51                             ((PPC_R_ATT_Type*) &PPC->R_ATT[51])                               /* 0x400260CC */
#define PPC_R_ATT52                             ((PPC_R_ATT_Type*) &PPC->R_ATT[52])                               /* 0x400260D0 */
#define PPC_R_ATT53                             ((PPC_R_ATT_Type*) &PPC->R_ATT[53])                               /* 0x400260D4 */
#define PPC_R_ATT54                             ((PPC_R_ATT_Type*) &PPC->R_ATT[54])                               /* 0x400260D8 */
#define PPC_R_ATT55                             ((PPC_R_ATT_Type*) &PPC->R_ATT[55])                               /* 0x400260DC */
#define PPC_R_ATT56                             ((PPC_R_ATT_Type*) &PPC->R_ATT[56])                               /* 0x400260E0 */
#define PPC_R_ATT57                             ((PPC_R_ATT_Type*) &PPC->R_ATT[57])                               /* 0x400260E4 */
#define PPC_R_ATT58                             ((PPC_R_ATT_Type*) &PPC->R_ATT[58])                               /* 0x400260E8 */
#define PPC_R_ATT59                             ((PPC_R_ATT_Type*) &PPC->R_ATT[59])                               /* 0x400260EC */
#define PPC_R_ATT60                             ((PPC_R_ATT_Type*) &PPC->R_ATT[60])                               /* 0x400260F0 */
#define PPC_R_ATT61                             ((PPC_R_ATT_Type*) &PPC->R_ATT[61])                               /* 0x400260F4 */
#define PPC_R_ATT62                             ((PPC_R_ATT_Type*) &PPC->R_ATT[62])                               /* 0x400260F8 */
#define PPC_R_ATT63                             ((PPC_R_ATT_Type*) &PPC->R_ATT[63])                               /* 0x400260FC */
#define PPC_R_ATT64                             ((PPC_R_ATT_Type*) &PPC->R_ATT[64])                               /* 0x40026100 */
#define PPC_R_ATT65                             ((PPC_R_ATT_Type*) &PPC->R_ATT[65])                               /* 0x40026104 */
#define PPC_R_ATT66                             ((PPC_R_ATT_Type*) &PPC->R_ATT[66])                               /* 0x40026108 */
#define PPC_R_ATT67                             ((PPC_R_ATT_Type*) &PPC->R_ATT[67])                               /* 0x4002610C */
#define PPC_R_ATT68                             ((PPC_R_ATT_Type*) &PPC->R_ATT[68])                               /* 0x40026110 */
#define PPC_R_ATT69                             ((PPC_R_ATT_Type*) &PPC->R_ATT[69])                               /* 0x40026114 */
#define PPC_R_ATT70                             ((PPC_R_ATT_Type*) &PPC->R_ATT[70])                               /* 0x40026118 */
#define PPC_R_ATT71                             ((PPC_R_ATT_Type*) &PPC->R_ATT[71])                               /* 0x4002611C */
#define PPC_R_ATT72                             ((PPC_R_ATT_Type*) &PPC->R_ATT[72])                               /* 0x40026120 */
#define PPC_R_ATT73                             ((PPC_R_ATT_Type*) &PPC->R_ATT[73])                               /* 0x40026124 */
#define PPC_R_ATT74                             ((PPC_R_ATT_Type*) &PPC->R_ATT[74])                               /* 0x40026128 */
#define PPC_R_ATT75                             ((PPC_R_ATT_Type*) &PPC->R_ATT[75])                               /* 0x4002612C */
#define PPC_R_ATT76                             ((PPC_R_ATT_Type*) &PPC->R_ATT[76])                               /* 0x40026130 */
#define PPC_R_ATT77                             ((PPC_R_ATT_Type*) &PPC->R_ATT[77])                               /* 0x40026134 */
#define PPC_R_ATT78                             ((PPC_R_ATT_Type*) &PPC->R_ATT[78])                               /* 0x40026138 */
#define PPC_R_ATT79                             ((PPC_R_ATT_Type*) &PPC->R_ATT[79])                               /* 0x4002613C */
#define PPC_R_ATT80                             ((PPC_R_ATT_Type*) &PPC->R_ATT[80])                               /* 0x40026140 */
#define PPC_R_ATT81                             ((PPC_R_ATT_Type*) &PPC->R_ATT[81])                               /* 0x40026144 */
#define PPC_R_ATT82                             ((PPC_R_ATT_Type*) &PPC->R_ATT[82])                               /* 0x40026148 */
#define PPC_R_ATT83                             ((PPC_R_ATT_Type*) &PPC->R_ATT[83])                               /* 0x4002614C */
#define PPC_R_ATT84                             ((PPC_R_ATT_Type*) &PPC->R_ATT[84])                               /* 0x40026150 */
#define PPC_R_ATT85                             ((PPC_R_ATT_Type*) &PPC->R_ATT[85])                               /* 0x40026154 */
#define PPC_R_ATT86                             ((PPC_R_ATT_Type*) &PPC->R_ATT[86])                               /* 0x40026158 */
#define PPC_R_ATT87                             ((PPC_R_ATT_Type*) &PPC->R_ATT[87])                               /* 0x4002615C */
#define PPC_R_ATT88                             ((PPC_R_ATT_Type*) &PPC->R_ATT[88])                               /* 0x40026160 */
#define PPC_R_ATT89                             ((PPC_R_ATT_Type*) &PPC->R_ATT[89])                               /* 0x40026164 */
#define PPC_R_ATT90                             ((PPC_R_ATT_Type*) &PPC->R_ATT[90])                               /* 0x40026168 */
#define PPC_R_ATT91                             ((PPC_R_ATT_Type*) &PPC->R_ATT[91])                               /* 0x4002616C */
#define PPC_R_ATT92                             ((PPC_R_ATT_Type*) &PPC->R_ATT[92])                               /* 0x40026170 */
#define PPC_R_ATT93                             ((PPC_R_ATT_Type*) &PPC->R_ATT[93])                               /* 0x40026174 */
#define PPC_R_ATT94                             ((PPC_R_ATT_Type*) &PPC->R_ATT[94])                               /* 0x40026178 */
#define PPC_R_ATT95                             ((PPC_R_ATT_Type*) &PPC->R_ATT[95])                               /* 0x4002617C */
#define PPC_R_ATT96                             ((PPC_R_ATT_Type*) &PPC->R_ATT[96])                               /* 0x40026180 */
#define PPC_R_ATT97                             ((PPC_R_ATT_Type*) &PPC->R_ATT[97])                               /* 0x40026184 */
#define PPC_R_ATT98                             ((PPC_R_ATT_Type*) &PPC->R_ATT[98])                               /* 0x40026188 */
#define PPC_R_ATT99                             ((PPC_R_ATT_Type*) &PPC->R_ATT[99])                               /* 0x4002618C */
#define PPC_R_ATT100                            ((PPC_R_ATT_Type*) &PPC->R_ATT[100])                              /* 0x40026190 */
#define PPC_R_ATT101                            ((PPC_R_ATT_Type*) &PPC->R_ATT[101])                              /* 0x40026194 */
#define PPC_R_ATT102                            ((PPC_R_ATT_Type*) &PPC->R_ATT[102])                              /* 0x40026198 */
#define PPC_R_ATT103                            ((PPC_R_ATT_Type*) &PPC->R_ATT[103])                              /* 0x4002619C */
#define PPC_R_ATT104                            ((PPC_R_ATT_Type*) &PPC->R_ATT[104])                              /* 0x400261A0 */
#define PPC_R_ATT105                            ((PPC_R_ATT_Type*) &PPC->R_ATT[105])                              /* 0x400261A4 */
#define PPC_R_ATT106                            ((PPC_R_ATT_Type*) &PPC->R_ATT[106])                              /* 0x400261A8 */
#define PPC_R_ATT107                            ((PPC_R_ATT_Type*) &PPC->R_ATT[107])                              /* 0x400261AC */
#define PPC_R_ATT108                            ((PPC_R_ATT_Type*) &PPC->R_ATT[108])                              /* 0x400261B0 */
#define PPC_R_ATT109                            ((PPC_R_ATT_Type*) &PPC->R_ATT[109])                              /* 0x400261B4 */
#define PPC_R_ATT110                            ((PPC_R_ATT_Type*) &PPC->R_ATT[110])                              /* 0x400261B8 */
#define PPC_R_ATT111                            ((PPC_R_ATT_Type*) &PPC->R_ATT[111])                              /* 0x400261BC */
#define PPC_R_ATT112                            ((PPC_R_ATT_Type*) &PPC->R_ATT[112])                              /* 0x400261C0 */
#define PPC_R_ATT113                            ((PPC_R_ATT_Type*) &PPC->R_ATT[113])                              /* 0x400261C4 */
#define PPC_R_ATT114                            ((PPC_R_ATT_Type*) &PPC->R_ATT[114])                              /* 0x400261C8 */
#define PPC_R_ATT115                            ((PPC_R_ATT_Type*) &PPC->R_ATT[115])                              /* 0x400261CC */
#define PPC_R_ATT116                            ((PPC_R_ATT_Type*) &PPC->R_ATT[116])                              /* 0x400261D0 */
#define PPC_R_ATT117                            ((PPC_R_ATT_Type*) &PPC->R_ATT[117])                              /* 0x400261D4 */
#define PPC_R_ATT118                            ((PPC_R_ATT_Type*) &PPC->R_ATT[118])                              /* 0x400261D8 */
#define PPC_R_ATT119                            ((PPC_R_ATT_Type*) &PPC->R_ATT[119])                              /* 0x400261DC */
#define PPC_R_ATT120                            ((PPC_R_ATT_Type*) &PPC->R_ATT[120])                              /* 0x400261E0 */
#define PPC_R_ATT121                            ((PPC_R_ATT_Type*) &PPC->R_ATT[121])                              /* 0x400261E4 */
#define PPC_R_ATT122                            ((PPC_R_ATT_Type*) &PPC->R_ATT[122])                              /* 0x400261E8 */
#define PPC_R_ATT123                            ((PPC_R_ATT_Type*) &PPC->R_ATT[123])                              /* 0x400261EC */
#define PPC_R_ATT124                            ((PPC_R_ATT_Type*) &PPC->R_ATT[124])                              /* 0x400261F0 */
#define PPC_R_ATT125                            ((PPC_R_ATT_Type*) &PPC->R_ATT[125])                              /* 0x400261F4 */
#define PPC_R_ATT126                            ((PPC_R_ATT_Type*) &PPC->R_ATT[126])                              /* 0x400261F8 */
#define PPC_R_ATT127                            ((PPC_R_ATT_Type*) &PPC->R_ATT[127])                              /* 0x400261FC */
#define PPC_R_ATT128                            ((PPC_R_ATT_Type*) &PPC->R_ATT[128])                              /* 0x40026200 */
#define PPC_R_ATT129                            ((PPC_R_ATT_Type*) &PPC->R_ATT[129])                              /* 0x40026204 */
#define PPC_R_ATT130                            ((PPC_R_ATT_Type*) &PPC->R_ATT[130])                              /* 0x40026208 */
#define PPC_R_ATT131                            ((PPC_R_ATT_Type*) &PPC->R_ATT[131])                              /* 0x4002620C */
#define PPC_R_ATT132                            ((PPC_R_ATT_Type*) &PPC->R_ATT[132])                              /* 0x40026210 */
#define PPC_R_ATT133                            ((PPC_R_ATT_Type*) &PPC->R_ATT[133])                              /* 0x40026214 */
#define PPC_R_ATT134                            ((PPC_R_ATT_Type*) &PPC->R_ATT[134])                              /* 0x40026218 */
#define PPC_R_ATT135                            ((PPC_R_ATT_Type*) &PPC->R_ATT[135])                              /* 0x4002621C */
#define PPC_R_ATT136                            ((PPC_R_ATT_Type*) &PPC->R_ATT[136])                              /* 0x40026220 */
#define PPC_R_ATT137                            ((PPC_R_ATT_Type*) &PPC->R_ATT[137])                              /* 0x40026224 */
#define PPC_R_ATT138                            ((PPC_R_ATT_Type*) &PPC->R_ATT[138])                              /* 0x40026228 */
#define PPC_R_ATT139                            ((PPC_R_ATT_Type*) &PPC->R_ATT[139])                              /* 0x4002622C */
#define PPC_R_ATT140                            ((PPC_R_ATT_Type*) &PPC->R_ATT[140])                              /* 0x40026230 */
#define PPC_R_ATT141                            ((PPC_R_ATT_Type*) &PPC->R_ATT[141])                              /* 0x40026234 */
#define PPC_R_ATT142                            ((PPC_R_ATT_Type*) &PPC->R_ATT[142])                              /* 0x40026238 */
#define PPC_R_ATT143                            ((PPC_R_ATT_Type*) &PPC->R_ATT[143])                              /* 0x4002623C */
#define PPC_R_ATT144                            ((PPC_R_ATT_Type*) &PPC->R_ATT[144])                              /* 0x40026240 */
#define PPC_R_ATT145                            ((PPC_R_ATT_Type*) &PPC->R_ATT[145])                              /* 0x40026244 */
#define PPC_R_ATT146                            ((PPC_R_ATT_Type*) &PPC->R_ATT[146])                              /* 0x40026248 */
#define PPC_R_ATT147                            ((PPC_R_ATT_Type*) &PPC->R_ATT[147])                              /* 0x4002624C */
#define PPC_R_ATT148                            ((PPC_R_ATT_Type*) &PPC->R_ATT[148])                              /* 0x40026250 */
#define PPC_R_ATT149                            ((PPC_R_ATT_Type*) &PPC->R_ATT[149])                              /* 0x40026254 */
#define PPC_R_ATT150                            ((PPC_R_ATT_Type*) &PPC->R_ATT[150])                              /* 0x40026258 */
#define PPC_R_ATT151                            ((PPC_R_ATT_Type*) &PPC->R_ATT[151])                              /* 0x4002625C */
#define PPC_R_ATT152                            ((PPC_R_ATT_Type*) &PPC->R_ATT[152])                              /* 0x40026260 */
#define PPC_R_ATT153                            ((PPC_R_ATT_Type*) &PPC->R_ATT[153])                              /* 0x40026264 */
#define PPC_R_ATT154                            ((PPC_R_ATT_Type*) &PPC->R_ATT[154])                              /* 0x40026268 */
#define PPC_R_ATT155                            ((PPC_R_ATT_Type*) &PPC->R_ATT[155])                              /* 0x4002626C */
#define PPC_R_ATT156                            ((PPC_R_ATT_Type*) &PPC->R_ATT[156])                              /* 0x40026270 */

/*******************************************************************************
*                                  PERI_PCLK
*******************************************************************************/

#define PERI_PCLK_BASE                          0x40040000UL
#define PERI_PCLK                               ((PERI_PCLK_Type*) PERI_PCLK_BASE)                                /* 0x40040000 */
#define PERI_PCLK_GR0                           ((PERI_PCLK_GR_Type*) &PERI_PCLK->GR[0])                          /* 0x40040000 */
#define PERI_PCLK_GR1                           ((PERI_PCLK_GR_Type*) &PERI_PCLK->GR[1])                          /* 0x40042000 */
#define PERI_PCLK_GR2                           ((PERI_PCLK_GR_Type*) &PERI_PCLK->GR[2])                          /* 0x40044000 */
#define PERI_PCLK_GR3                           ((PERI_PCLK_GR_Type*) &PERI_PCLK->GR[3])                          /* 0x40046000 */
#define PERI_PCLK_GR4                           ((PERI_PCLK_GR_Type*) &PERI_PCLK->GR[4])                          /* 0x40048000 */
#define PERI_PCLK_GR5                           ((PERI_PCLK_GR_Type*) &PERI_PCLK->GR[5])                          /* 0x4004A000 */
#define PERI_PCLK_GR6                           ((PERI_PCLK_GR_Type*) &PERI_PCLK->GR[6])                          /* 0x4004C000 */

/*******************************************************************************
*                                   RAMC_PPU
*******************************************************************************/

#define RAMC_PPU0_BASE                          0x40100000UL
#define RAMC_PPU1_BASE                          0x40101000UL
#define RAMC_PPU2_BASE                          0x40102000UL
#define RAMC_PPU0                               ((RAMC_PPU_Type*) RAMC_PPU0_BASE)                                 /* 0x40100000 */
#define RAMC_PPU1                               ((RAMC_PPU_Type*) RAMC_PPU1_BASE)                                 /* 0x40101000 */
#define RAMC_PPU2                               ((RAMC_PPU_Type*) RAMC_PPU2_BASE)                                 /* 0x40102000 */

/*******************************************************************************
*                                    ICACHE
*******************************************************************************/

#define ICACHE0_BASE                            0x40103000UL
#define ICACHE1_BASE                            0x40104000UL
#define ICACHE0                                 ((ICACHE_Type*) ICACHE0_BASE)                                     /* 0x40103000 */
#define ICACHE1                                 ((ICACHE_Type*) ICACHE1_BASE)                                     /* 0x40104000 */

/*******************************************************************************
*                                  CPUSS_PPU
*******************************************************************************/

#define CPUSS_PPU_BASE                          0x40105000UL
#define CPUSS_PPU                               ((CPUSS_PPU_Type*) CPUSS_PPU_BASE)                                /* 0x40105000 */

/*******************************************************************************
*                                     RAMC
*******************************************************************************/

#define RAMC0_BASE                              0x40110000UL
#define RAMC0                                   ((RAMC_Type*) RAMC0_BASE)                                         /* 0x40110000 */
#define RAMC0_MPC0                              ((RAMC_MPC_Type*) &RAMC0->MPC[0])                                 /* 0x40114000 */

/*******************************************************************************
*                                    PROMC
*******************************************************************************/

#define PROMC_BASE                              0x40140000UL
#define PROMC                                   ((PROMC_Type*) PROMC_BASE)                                        /* 0x40140000 */
#define PROMC_MPC0                              ((PROMC_MPC_Type*) &PROMC->MPC[0])                                /* 0x40141000 */

/*******************************************************************************
*                                    MXCM33
*******************************************************************************/

#define MXCM33_BASE                             0x40160000UL
#define MXCM33                                  ((MXCM33_Type*) MXCM33_BASE)                                      /* 0x40160000 */

/*******************************************************************************
*                                      DW
*******************************************************************************/

#define DW0_BASE                                0x40180000UL
#define DW0                                     ((DW_Type*) DW0_BASE)                                             /* 0x40180000 */
#define DW0_CH_STRUCT0                          ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[0])                         /* 0x40188000 */
#define DW0_CH_STRUCT1                          ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[1])                         /* 0x40188040 */
#define DW0_CH_STRUCT2                          ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[2])                         /* 0x40188080 */
#define DW0_CH_STRUCT3                          ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[3])                         /* 0x401880C0 */
#define DW0_CH_STRUCT4                          ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[4])                         /* 0x40188100 */
#define DW0_CH_STRUCT5                          ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[5])                         /* 0x40188140 */
#define DW0_CH_STRUCT6                          ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[6])                         /* 0x40188180 */
#define DW0_CH_STRUCT7                          ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[7])                         /* 0x401881C0 */
#define DW0_CH_STRUCT8                          ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[8])                         /* 0x40188200 */
#define DW0_CH_STRUCT9                          ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[9])                         /* 0x40188240 */
#define DW0_CH_STRUCT10                         ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[10])                        /* 0x40188280 */
#define DW0_CH_STRUCT11                         ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[11])                        /* 0x401882C0 */
#define DW0_CH_STRUCT12                         ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[12])                        /* 0x40188300 */
#define DW0_CH_STRUCT13                         ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[13])                        /* 0x40188340 */
#define DW0_CH_STRUCT14                         ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[14])                        /* 0x40188380 */
#define DW0_CH_STRUCT15                         ((DW_CH_STRUCT_Type*) &DW0->CH_STRUCT[15])                        /* 0x401883C0 */

/*******************************************************************************
*                                    CPUSS
*******************************************************************************/

#define CPUSS_BASE                              0x401C0000UL
#define CPUSS                                   ((CPUSS_Type*) CPUSS_BASE)                                        /* 0x401C0000 */

/*******************************************************************************
*                                  MS_CTL_1_2
*******************************************************************************/

#define MS_CTL_1_2_BASE                         0x401C4000UL
#define MS_CTL_1_2                              ((MS_CTL_1_2_Type*) MS_CTL_1_2_BASE)                              /* 0x401C4000 */
#define MS5                                     ((MS_Type*) &MS_CTL_1_2->MS[5])                                   /* 0x401C4050 */
#define MS_PC5                                  ((MS_PC_Type*) &MS_CTL_1_2->MS_PC[5])                             /* 0x401C5050 */

/*******************************************************************************
*                                 CPUSS_SL_CTL
*******************************************************************************/

#define CPUSS_SL_CTL_BASE                       0x401C8000UL
#define CPUSS_SL_CTL                            ((CPUSS_SL_CTL_Type*) CPUSS_SL_CTL_BASE)                          /* 0x401C8000 */

/*******************************************************************************
*                                     IPC
*******************************************************************************/

#define IPC_BASE                                0x401D0000UL
#define IPC                                     ((IPC_Type*) IPC_BASE)                                            /* 0x401D0000 */
#define IPC_STRUCT0                             ((IPC_STRUCT_Type*) &IPC->STRUCT[0])                              /* 0x401D0000 */
#define IPC_STRUCT1                             ((IPC_STRUCT_Type*) &IPC->STRUCT[1])                              /* 0x401D0020 */
#define IPC_STRUCT2                             ((IPC_STRUCT_Type*) &IPC->STRUCT[2])                              /* 0x401D0040 */
#define IPC_STRUCT3                             ((IPC_STRUCT_Type*) &IPC->STRUCT[3])                              /* 0x401D0060 */
#define IPC_INTR_STRUCT0                        ((IPC_INTR_STRUCT_Type*) &IPC->INTR_STRUCT[0])                    /* 0x401D1000 */
#define IPC_INTR_STRUCT1                        ((IPC_INTR_STRUCT_Type*) &IPC->INTR_STRUCT[1])                    /* 0x401D1020 */

/*******************************************************************************
*                                     SRSS
*******************************************************************************/

#define SRSS_BASE                               0x40200000UL
#define SRSS                                    ((SRSS_Type*) SRSS_BASE)                                          /* 0x40200000 */
#define MCWDT_STRUCT0                           ((MCWDT_STRUCT_Type*) &SRSS->MCWDT_STRUCT[0])                     /* 0x4020D000 */

/*******************************************************************************
*                                   PWRMODE
*******************************************************************************/

#define PWRMODE_BASE                            0x40210000UL
#define PWRMODE                                 ((PWRMODE_Type*) PWRMODE_BASE)                                    /* 0x40210000 */
#define PWRMODE_PD0                             ((PWRMODE_PD_Type*) &PWRMODE->PD[0])                              /* 0x40210000 */
#define PWRMODE_PD1                             ((PWRMODE_PD_Type*) &PWRMODE->PD[1])                              /* 0x40210010 */
#define PWRMODE_PD2                             ((PWRMODE_PD_Type*) &PWRMODE->PD[2])                              /* 0x40210020 */
#define PWRMODE_PD3                             ((PWRMODE_PD_Type*) &PWRMODE->PD[3])                              /* 0x40210030 */
#define PWRMODE_PD4                             ((PWRMODE_PD_Type*) &PWRMODE->PD[4])                              /* 0x40210040 */
#define PWRMODE_PD5                             ((PWRMODE_PD_Type*) &PWRMODE->PD[5])                              /* 0x40210050 */
#define PWRMODE_PD6                             ((PWRMODE_PD_Type*) &PWRMODE->PD[6])                              /* 0x40210060 */
#define PWRMODE_PD7                             ((PWRMODE_PD_Type*) &PWRMODE->PD[7])                              /* 0x40210070 */
#define PWRMODE_PD8                             ((PWRMODE_PD_Type*) &PWRMODE->PD[8])                              /* 0x40210080 */
#define PWRMODE_PD9                             ((PWRMODE_PD_Type*) &PWRMODE->PD[9])                              /* 0x40210090 */
#define PWRMODE_PD10                            ((PWRMODE_PD_Type*) &PWRMODE->PD[10])                             /* 0x402100A0 */
#define PWRMODE_PD11                            ((PWRMODE_PD_Type*) &PWRMODE->PD[11])                             /* 0x402100B0 */
#define PWRMODE_PD12                            ((PWRMODE_PD_Type*) &PWRMODE->PD[12])                             /* 0x402100C0 */
#define PWRMODE_PD13                            ((PWRMODE_PD_Type*) &PWRMODE->PD[13])                             /* 0x402100D0 */
#define PWRMODE_PD14                            ((PWRMODE_PD_Type*) &PWRMODE->PD[14])                             /* 0x402100E0 */
#define PWRMODE_PD15                            ((PWRMODE_PD_Type*) &PWRMODE->PD[15])                             /* 0x402100F0 */
#define PWRMODE_PPU_MAIN                        ((PWRMODE_PPU_MAIN_Type*) &PWRMODE->PPU_MAIN)                     /* 0x40211000 */
#define PWRMODE_PPU_MAIN_PPU_MAIN               ((PWRMODE_PPU_MAIN_PPU_MAIN_Type*) &PWRMODE->PPU_MAIN.PPU_MAIN)   /* 0x40211000 */

/*******************************************************************************
*                                    BACKUP
*******************************************************************************/

#define BACKUP_BASE                             0x40220000UL
#define BACKUP                                  ((BACKUP_Type*) BACKUP_BASE)                                      /* 0x40220000 */

/*******************************************************************************
*                                  CRYPTOLITE
*******************************************************************************/

#define CRYPTOLITE_BASE                         0x40230000UL
#define CRYPTOLITE                              ((CRYPTOLITE_Type*) CRYPTOLITE_BASE)                              /* 0x40230000 */

/*******************************************************************************
*                                    HSIOM
*******************************************************************************/

#define HSIOM_BASE                              0x40400000UL
#define HSIOM                                   ((HSIOM_Type*) HSIOM_BASE)                                        /* 0x40400000 */
#define HSIOM_PRT0                              ((HSIOM_PRT_Type*) &HSIOM->PRT[0])                                /* 0x40400000 */
#define HSIOM_PRT1                              ((HSIOM_PRT_Type*) &HSIOM->PRT[1])                                /* 0x40400010 */
#define HSIOM_PRT2                              ((HSIOM_PRT_Type*) &HSIOM->PRT[2])                                /* 0x40400020 */
#define HSIOM_PRT3                              ((HSIOM_PRT_Type*) &HSIOM->PRT[3])                                /* 0x40400030 */
#define HSIOM_PRT4                              ((HSIOM_PRT_Type*) &HSIOM->PRT[4])                                /* 0x40400040 */
#define HSIOM_PRT5                              ((HSIOM_PRT_Type*) &HSIOM->PRT[5])                                /* 0x40400050 */

/*******************************************************************************
*                                     GPIO
*******************************************************************************/

#define GPIO_BASE                               0x40410000UL
#define GPIO                                    ((GPIO_Type*) GPIO_BASE)                                          /* 0x40410000 */
#define GPIO_PRT0                               ((GPIO_PRT_Type*) &GPIO->PRT[0])                                  /* 0x40410000 */
#define GPIO_PRT1                               ((GPIO_PRT_Type*) &GPIO->PRT[1])                                  /* 0x40410080 */
#define GPIO_PRT2                               ((GPIO_PRT_Type*) &GPIO->PRT[2])                                  /* 0x40410100 */
#define GPIO_PRT3                               ((GPIO_PRT_Type*) &GPIO->PRT[3])                                  /* 0x40410180 */
#define GPIO_PRT4                               ((GPIO_PRT_Type*) &GPIO->PRT[4])                                  /* 0x40410200 */
#define GPIO_PRT5                               ((GPIO_PRT_Type*) &GPIO->PRT[5])                                  /* 0x40410280 */

/*******************************************************************************
*                                   SMARTIO
*******************************************************************************/

#define SMARTIO_BASE                            0x40420000UL
#define SMARTIO                                 ((SMARTIO_Type*) SMARTIO_BASE)                                    /* 0x40420000 */
#define SMARTIO_PRT3                            ((SMARTIO_PRT_Type*) &SMARTIO->PRT[3])                            /* 0x40420300 */

/*******************************************************************************
*                                     LIN
*******************************************************************************/

#define LIN0_BASE                               0x40430000UL
#define LIN0                                    ((LIN_Type*) LIN0_BASE)                                           /* 0x40430000 */
#define LIN0_CH0                                ((LIN_CH_Type*) &LIN0->CH[0])                                     /* 0x40438000 */
#define LIN0_CH1                                ((LIN_CH_Type*) &LIN0->CH[1])                                     /* 0x40438100 */

/*******************************************************************************
*                                    CANFD
*******************************************************************************/

#define CANFD0_BASE                             0x40440000UL
#define CANFD0                                  ((CANFD_Type*) CANFD0_BASE)                                       /* 0x40440000 */
#define CANFD0_CH0                              ((CANFD_CH_Type*) &CANFD0->CH[0])                                 /* 0x40440000 */
#define CANFD0_CH0_M_TTCAN                      ((CANFD_CH_M_TTCAN_Type*) &CANFD0->CH[0].M_TTCAN)                 /* 0x40440000 */

/*******************************************************************************
*                                    TCPWM
*******************************************************************************/

#define TCPWM0_BASE                             0x404A0000UL
#define TCPWM0                                  ((TCPWM_Type*) TCPWM0_BASE)                                       /* 0x404A0000 */
#define TCPWM0_GRP0                             ((TCPWM_GRP_Type*) &TCPWM0->GRP[0])                               /* 0x404A0000 */
#define TCPWM0_GRP1                             ((TCPWM_GRP_Type*) &TCPWM0->GRP[1])                               /* 0x404A8000 */
#define TCPWM0_GRP0_CNT0                        ((TCPWM_GRP_CNT_Type*) &TCPWM0->GRP[0].CNT[0])                    /* 0x404A0000 */
#define TCPWM0_GRP0_CNT1                        ((TCPWM_GRP_CNT_Type*) &TCPWM0->GRP[0].CNT[1])                    /* 0x404A0080 */
#define TCPWM0_GRP1_CNT0                        ((TCPWM_GRP_CNT_Type*) &TCPWM0->GRP[1].CNT[0])                    /* 0x404A8000 */
#define TCPWM0_GRP1_CNT1                        ((TCPWM_GRP_CNT_Type*) &TCPWM0->GRP[1].CNT[1])                    /* 0x404A8080 */
#define TCPWM0_GRP1_CNT2                        ((TCPWM_GRP_CNT_Type*) &TCPWM0->GRP[1].CNT[2])                    /* 0x404A8100 */
#define TCPWM0_GRP1_CNT3                        ((TCPWM_GRP_CNT_Type*) &TCPWM0->GRP[1].CNT[3])                    /* 0x404A8180 */
#define TCPWM0_GRP1_CNT4                        ((TCPWM_GRP_CNT_Type*) &TCPWM0->GRP[1].CNT[4])                    /* 0x404A8200 */
#define TCPWM0_GRP1_CNT5                        ((TCPWM_GRP_CNT_Type*) &TCPWM0->GRP[1].CNT[5])                    /* 0x404A8280 */
#define TCPWM0_GRP1_CNT6                        ((TCPWM_GRP_CNT_Type*) &TCPWM0->GRP[1].CNT[6])                    /* 0x404A8300 */

/*******************************************************************************
*                                 MXS40ADCMIC
*******************************************************************************/

#define MXS40ADCMIC0_BASE                       0x40520000UL
#define MXS40ADCMIC0                            ((MXS40ADCMIC_Type*) MXS40ADCMIC0_BASE)                           /* 0x40520000 */

/*******************************************************************************
*                                     SCB
*******************************************************************************/

#define SCB0_BASE                               0x40590000UL
#define SCB1_BASE                               0x405A0000UL
#define SCB2_BASE                               0x405B0000UL
#define SCB0                                    ((CySCB_Type*) SCB0_BASE)                                         /* 0x40590000 */
#define SCB1                                    ((CySCB_Type*) SCB1_BASE)                                         /* 0x405A0000 */
#define SCB2                                    ((CySCB_Type*) SCB2_BASE)                                         /* 0x405B0000 */

/*******************************************************************************
*                                    EFUSE
*******************************************************************************/

#define EFUSE_BASE                              0x40810000UL
#define EFUSE                                   ((EFUSE_Type*) EFUSE_BASE)                                        /* 0x40810000 */

/*******************************************************************************
*                                     SMIF
*******************************************************************************/

#define SMIF0_BASE                              0x40890000UL
#define SMIF0                                   ((SMIF_Type*) SMIF0_BASE)                                         /* 0x40890000 */
#define SMIF0_SMIF_CRYPTO0                      ((SMIF_SMIF_CRYPTO_Type*) &SMIF0->SMIF_CRYPTO_BLOCK[0])           /* 0x40890200 */
#define SMIF0_DEVICE0                           ((SMIF_DEVICE_Type*) &SMIF0->DEVICE[0])                           /* 0x40890800 */
#define SMIF0_DEVICE1                           ((SMIF_DEVICE_Type*) &SMIF0->DEVICE[1])                           /* 0x40890880 */
#define SMIF0_MPC0                              ((SMIF_MPC_Type*) &SMIF0->MPC[0])                                 /* 0x40891000 */

/*******************************************************************************
*                                     TDM
*******************************************************************************/

#define TDM0_BASE                               0x408C0000UL
#define TDM0                                    ((TDM_Type*) TDM0_BASE)                                           /* 0x408C0000 */
#define TDM0_TDM_STRUCT0                        ((TDM_TDM_STRUCT_Type*) &TDM0->TDM_STRUCT[0])                     /* 0x408C8000 */
#define TDM0_TDM_STRUCT0_TDM_TX_STRUCT          ((TDM_TDM_STRUCT_TDM_TX_STRUCT_Type*) &TDM0->TDM_STRUCT[0].TDM_TX_STRUCT) /* 0x408C8000 */
#define TDM0_TDM_STRUCT0_TDM_RX_STRUCT          ((TDM_TDM_STRUCT_TDM_RX_STRUCT_Type*) &TDM0->TDM_STRUCT[0].TDM_RX_STRUCT) /* 0x408C8100 */

/*******************************************************************************
*                                     PDM
*******************************************************************************/

#define PDM0_BASE                               0x408D0000UL
#define PDM0                                    ((PDM_Type*) PDM0_BASE)                                           /* 0x408D0000 */
#define PDM0_CH0                                ((PDM_CH_Type*) &PDM0->CH[0])                                     /* 0x408D8000 */
#define PDM0_CH1                                ((PDM_CH_Type*) &PDM0->CH[1])                                     /* 0x408D8100 */

/*******************************************************************************
*                                  MXKEYSCAN
*******************************************************************************/

#define MXKEYSCAN_BASE                          0x40920000UL
#define MXKEYSCAN                               ((MXKEYSCAN_Type*) MXKEYSCAN_BASE)                                /* 0x40920000 */

/*******************************************************************************
*                                     BTSS
*******************************************************************************/

#define BTSS_BASE                               0x42000000UL
#define BTSS                                    ((BTSS_Type*) BTSS_BASE)                                          /* 0x42000000 */
#define BTSS_DATA_RAM_IPC                       ((BTSS_DATA_RAM_IPC_Type*) &BTSS->DATA_RAM_IPC)                   /* 0x42600000 */

/** \} CYW20829A0KML */

#endif /* _CYW20829A0KML_H_ */


/* [] END OF FILE */
