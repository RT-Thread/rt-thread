/***************************************************************************//**
* \file cyip_srss.h
*
* \brief
* SRSS IP definitions
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

#ifndef _CYIP_SRSS_H_
#define _CYIP_SRSS_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                     SRSS
*******************************************************************************/

#define CSV_HF_CSV_SECTION_SIZE                 0x00000010UL
#define CSV_HF_SECTION_SIZE                     0x00000100UL
#define CSV_REF_CSV_SECTION_SIZE                0x00000010UL
#define CSV_REF_SECTION_SIZE                    0x00000010UL
#define CSV_LF_CSV_SECTION_SIZE                 0x00000010UL
#define CSV_LF_SECTION_SIZE                     0x00000010UL
#define CSV_ILO_CSV_SECTION_SIZE                0x00000010UL
#define CSV_ILO_SECTION_SIZE                    0x00000010UL
#define CLK_PLL400M_SECTION_SIZE                0x00000010UL
#define MCWDT_STRUCT_SECTION_SIZE               0x00000040UL
#define SRSS_SECTION_SIZE                       0x00010000UL

/**
  * \brief Active domain Clock Supervisor (CSV) registers (CSV_HF_CSV)
  */
typedef struct {
  __IOM uint32_t REF_CTL;                       /*!< 0x00000000 Clock Supervision Reference Control */
  __IOM uint32_t REF_LIMIT;                     /*!< 0x00000004 Clock Supervision Reference Limits */
  __IOM uint32_t MON_CTL;                       /*!< 0x00000008 Clock Supervision Monitor Control */
   __IM uint32_t RESERVED;
} CSV_HF_CSV_Type;                              /*!< Size = 16 (0x10) */

/**
  * \brief Clock Supervisor (CSV) registers for Root clocks (CSV_HF)
  */
typedef struct {
        CSV_HF_CSV_Type CSV[16];                /*!< 0x00000000 Active domain Clock Supervisor (CSV) registers */
} CSV_HF_Type;                                  /*!< Size = 256 (0x100) */

/**
  * \brief Active domain Clock Supervisor (CSV) registers for CSV Reference clock (CSV_REF_CSV)
  */
typedef struct {
  __IOM uint32_t REF_CTL;                       /*!< 0x00000000 Clock Supervision Reference Control */
  __IOM uint32_t REF_LIMIT;                     /*!< 0x00000004 Clock Supervision Reference Limits */
  __IOM uint32_t MON_CTL;                       /*!< 0x00000008 Clock Supervision Monitor Control */
   __IM uint32_t RESERVED;
} CSV_REF_CSV_Type;                             /*!< Size = 16 (0x10) */

/**
  * \brief CSV registers for the CSV Reference clock (CSV_REF)
  */
typedef struct {
        CSV_REF_CSV_Type CSV;                   /*!< 0x00000000 Active domain Clock Supervisor (CSV) registers for CSV
                                                                Reference clock */
} CSV_REF_Type;                                 /*!< Size = 16 (0x10) */

/**
  * \brief LF clock Clock Supervisor registers (CSV_LF_CSV)
  */
typedef struct {
  __IOM uint32_t REF_CTL;                       /*!< 0x00000000 Clock Supervision Reference Control */
  __IOM uint32_t REF_LIMIT;                     /*!< 0x00000004 Clock Supervision Reference Limits */
  __IOM uint32_t MON_CTL;                       /*!< 0x00000008 Clock Supervision Monitor Control */
   __IM uint32_t RESERVED;
} CSV_LF_CSV_Type;                              /*!< Size = 16 (0x10) */

/**
  * \brief CSV registers for LF clock (CSV_LF)
  */
typedef struct {
        CSV_LF_CSV_Type CSV;                    /*!< 0x00000000 LF clock Clock Supervisor registers */
} CSV_LF_Type;                                  /*!< Size = 16 (0x10) */

/**
  * \brief HVILO clock DeepSleep domain Clock Supervisor registers (CSV_ILO_CSV)
  */
typedef struct {
  __IOM uint32_t REF_CTL;                       /*!< 0x00000000 Clock Supervision Reference Control */
  __IOM uint32_t REF_LIMIT;                     /*!< 0x00000004 Clock Supervision Reference Limits */
  __IOM uint32_t MON_CTL;                       /*!< 0x00000008 Clock Supervision Monitor Control */
   __IM uint32_t RESERVED;
} CSV_ILO_CSV_Type;                             /*!< Size = 16 (0x10) */

/**
  * \brief CSV registers for ILO clock (CSV_ILO)
  */
typedef struct {
        CSV_ILO_CSV_Type CSV;                   /*!< 0x00000000 HVILO clock DeepSleep domain Clock Supervisor registers */
} CSV_ILO_Type;                                 /*!< Size = 16 (0x10) */

/**
  * \brief 400MHz PLL Configuration Register (CLK_PLL400M)
  */
typedef struct {
  __IOM uint32_t CONFIG;                        /*!< 0x00000000 400MHz PLL Configuration Register */
  __IOM uint32_t CONFIG2;                       /*!< 0x00000004 400MHz PLL Configuration Register 2 */
  __IOM uint32_t CONFIG3;                       /*!< 0x00000008 400MHz PLL Configuration Register 3 */
  __IOM uint32_t STATUS;                        /*!< 0x0000000C 400MHz PLL Status Register */
} CLK_PLL400M_Type;                             /*!< Size = 16 (0x10) */

/**
  * \brief Multi-Counter Watchdog Timer (Type A) (MCWDT_STRUCT)
  */
typedef struct {
   __IM uint32_t RESERVED;
  __IOM uint32_t MCWDT_CNTLOW;                  /*!< 0x00000004 Multi-Counter Watchdog Sub-counters 0/1 */
  __IOM uint32_t MCWDT_CNTHIGH;                 /*!< 0x00000008 Multi-Counter Watchdog Sub-counter 2 */
  __IOM uint32_t MCWDT_MATCH;                   /*!< 0x0000000C Multi-Counter Watchdog Counter Match Register */
  __IOM uint32_t MCWDT_CONFIG;                  /*!< 0x00000010 Multi-Counter Watchdog Counter Configuration */
  __IOM uint32_t MCWDT_CTL;                     /*!< 0x00000014 Multi-Counter Watchdog Counter Control */
  __IOM uint32_t MCWDT_INTR;                    /*!< 0x00000018 Multi-Counter Watchdog Counter Interrupt Register */
  __IOM uint32_t MCWDT_INTR_SET;                /*!< 0x0000001C Multi-Counter Watchdog Counter Interrupt Set Register */
  __IOM uint32_t MCWDT_INTR_MASK;               /*!< 0x00000020 Multi-Counter Watchdog Counter Interrupt Mask Register */
   __IM uint32_t MCWDT_INTR_MASKED;             /*!< 0x00000024 Multi-Counter Watchdog Counter Interrupt Masked Register */
  __IOM uint32_t MCWDT_LOCK;                    /*!< 0x00000028 Multi-Counter Watchdog Counter Lock Register */
  __IOM uint32_t MCWDT_LOWER_LIMIT;             /*!< 0x0000002C Multi-Counter Watchdog Counter Lower Limit Register */
   __IM uint32_t RESERVED1[4];
} MCWDT_STRUCT_Type;                            /*!< Size = 64 (0x40) */

/**
  * \brief SRSS Core Registers (SRSS)
  */
typedef struct {
   __IM uint32_t RESERVED[16];
   __IM uint32_t PWR_LVD_STATUS;                /*!< 0x00000040 High Voltage / Low Voltage Detector (HVLVD) Status Register */
   __IM uint32_t PWR_LVD_STATUS2;               /*!< 0x00000044 High Voltage / Low Voltage Detector (HVLVD) Status Register #2 */
   __IM uint32_t RESERVED1[46];
  __IOM uint32_t CLK_DSI_SELECT[16];            /*!< 0x00000100 Clock DSI Select Register */
  __IOM uint32_t CLK_OUTPUT_FAST;               /*!< 0x00000140 Fast Clock Output Select Register */
  __IOM uint32_t CLK_OUTPUT_SLOW;               /*!< 0x00000144 Slow Clock Output Select Register */
  __IOM uint32_t CLK_CAL_CNT1;                  /*!< 0x00000148 Clock Calibration Counter 1 */
   __IM uint32_t CLK_CAL_CNT2;                  /*!< 0x0000014C Clock Calibration Counter 2 */
   __IM uint32_t RESERVED2[44];
  __IOM uint32_t SRSS_INTR;                     /*!< 0x00000200 SRSS Interrupt Register */
  __IOM uint32_t SRSS_INTR_SET;                 /*!< 0x00000204 SRSS Interrupt Set Register */
  __IOM uint32_t SRSS_INTR_MASK;                /*!< 0x00000208 SRSS Interrupt Mask Register */
   __IM uint32_t SRSS_INTR_MASKED;              /*!< 0x0000020C SRSS Interrupt Masked Register */
   __IM uint32_t RESERVED3[60];
  __IOM uint32_t SRSS_AINTR;                    /*!< 0x00000300 SRSS Additional Interrupt Register */
  __IOM uint32_t SRSS_AINTR_SET;                /*!< 0x00000304 SRSS Additional Interrupt Set Register */
  __IOM uint32_t SRSS_AINTR_MASK;               /*!< 0x00000308 SRSS Additional Interrupt Mask Register */
   __IM uint32_t SRSS_AINTR_MASKED;             /*!< 0x0000030C SRSS Additional Interrupt Masked Register */
   __IM uint32_t RESERVED4[61];
  __IOM uint32_t TST_DEBUG_CTL;                 /*!< 0x00000404 Debug Control Register */
  __IOM uint32_t TST_DEBUG_STATUS;              /*!< 0x00000408 Debug Status Register */
   __IM uint32_t RESERVED5;
  __IOM uint32_t RES_SOFT_CTL;                  /*!< 0x00000410 Soft Reset Trigger Register */
   __IM uint32_t RESERVED6[251];
  __IOM uint32_t PWR_HIB_DATA[16];              /*!< 0x00000800 HIBERNATE Data Register */
   __IM uint32_t RESERVED7[24];
  __IOM uint32_t PWR_HIB_WAKE_CTL;              /*!< 0x000008A0 Hibernate Wakeup Mask Register */
  __IOM uint32_t PWR_HIB_WAKE_CTL2;             /*!< 0x000008A4 Hibernate Wakeup Polarity Register */
   __IM uint32_t RESERVED8;
  __IOM uint32_t PWR_HIB_WAKE_CAUSE;            /*!< 0x000008AC Hibernate Wakeup Cause Register */
   __IM uint32_t RESERVED9[468];
   __IM uint32_t PWR_CTL;                       /*!< 0x00001000 Power Mode Control */
  __IOM uint32_t PWR_CTL2;                      /*!< 0x00001004 Power Mode Control 2 */
  __IOM uint32_t PWR_HIBERNATE;                 /*!< 0x00001008 HIBERNATE Mode Register */
   __IM uint32_t RESERVED10;
  __IOM uint32_t PWR_BUCK_CTL;                  /*!< 0x00001010 Buck Control Register */
  __IOM uint32_t PWR_BUCK_CTL2;                 /*!< 0x00001014 Buck Control Register 2 */
  __IOM uint32_t PWR_SSV_CTL;                   /*!< 0x00001018 Supply Supervision Control Register */
   __IM uint32_t PWR_SSV_STATUS;                /*!< 0x0000101C Supply Supervision Status Register */
  __IOM uint32_t PWR_LVD_CTL;                   /*!< 0x00001020 High Voltage / Low Voltage Detector (HVLVD) Configuration
                                                                Register */
  __IOM uint32_t PWR_LVD_CTL2;                  /*!< 0x00001024 High Voltage / Low Voltage Detector (HVLVD) Configuration
                                                                Register #2 */
  __IOM uint32_t PWR_REGHC_CTL;                 /*!< 0x00001028 REGHC Control Register */
   __IM uint32_t PWR_REGHC_STATUS;              /*!< 0x0000102C REGHC Status Register */
  __IOM uint32_t PWR_REGHC_CTL2;                /*!< 0x00001030 REGHC Control Register 2 */
   __IM uint32_t RESERVED11[35];
  __IOM uint32_t PWR_PMIC_CTL;                  /*!< 0x000010C0 PMIC Control Register */
   __IM uint32_t PWR_PMIC_STATUS;               /*!< 0x000010C4 PMIC Status Register */
  __IOM uint32_t PWR_PMIC_CTL2;                 /*!< 0x000010C8 PMIC Control Register 2 */
   __IM uint32_t RESERVED12;
  __IOM uint32_t PWR_PMIC_CTL4;                 /*!< 0x000010D0 PMIC Control Register 4 */
   __IM uint32_t RESERVED13[75];
  __IOM uint32_t CLK_PATH_SELECT[16];           /*!< 0x00001200 Clock Path Select Register */
  __IOM uint32_t CLK_ROOT_SELECT[16];           /*!< 0x00001240 Clock Root Select Register */
  __IOM uint32_t CLK_DIRECT_SELECT[16];         /*!< 0x00001280 Clock Root Direct Select Register */
   __IM uint32_t RESERVED14[80];
        CSV_HF_Type CSV_HF;                     /*!< 0x00001400 Clock Supervisor (CSV) registers for Root clocks */
  __IOM uint32_t CLK_SELECT;                    /*!< 0x00001500 Clock selection register */
   __IM uint32_t RESERVED15;
  __IOM uint32_t CLK_ILO0_CONFIG;               /*!< 0x00001508 ILO0 Configuration */
  __IOM uint32_t CLK_ILO1_CONFIG;               /*!< 0x0000150C ILO1 Configuration */
   __IM uint32_t RESERVED16[2];
  __IOM uint32_t CLK_IMO_CONFIG;                /*!< 0x00001518 IMO Configuration */
  __IOM uint32_t CLK_ECO_CONFIG;                /*!< 0x0000151C ECO Configuration Register */
  __IOM uint32_t CLK_ECO_PRESCALE;              /*!< 0x00001520 ECO Prescaler Configuration Register */
   __IM uint32_t CLK_ECO_STATUS;                /*!< 0x00001524 ECO Status Register */
  __IOM uint32_t CLK_PILO_CONFIG;               /*!< 0x00001528 Precision ILO Configuration Register */
   __IM uint32_t RESERVED17;
  __IOM uint32_t CLK_FLL_CONFIG;                /*!< 0x00001530 FLL Configuration Register */
  __IOM uint32_t CLK_FLL_CONFIG2;               /*!< 0x00001534 FLL Configuration Register 2 */
  __IOM uint32_t CLK_FLL_CONFIG3;               /*!< 0x00001538 FLL Configuration Register 3 */
  __IOM uint32_t CLK_FLL_CONFIG4;               /*!< 0x0000153C FLL Configuration Register 4 */
  __IOM uint32_t CLK_FLL_STATUS;                /*!< 0x00001540 FLL Status Register */
  __IOM uint32_t CLK_ECO_CONFIG2;               /*!< 0x00001544 ECO Configuration Register 2 */
  __IOM uint32_t CLK_ILO_CONFIG;                /*!< 0x00001548 ILO Configuration */
  __IOM uint32_t CLK_TRIM_ILO_CTL;              /*!< 0x0000154C ILO Trim Register */
  __IOM uint32_t CLK_TRIM_ILO0_CTL;             /*!< 0x00001550 ILO0 Trim Register */
  __IOM uint32_t CLK_MF_SELECT;                 /*!< 0x00001554 Medium Frequency Clock Select Register */
  __IOM uint32_t CLK_MFO_CONFIG;                /*!< 0x00001558 MFO Configuration Register */
   __IM uint32_t RESERVED18;
  __IOM uint32_t CLK_IHO_CONFIG;                /*!< 0x00001560 IHO Configuration Register */
  __IOM uint32_t CLK_ALTHF_CTL;                 /*!< 0x00001564 Alternate High Frequency Clock Control Register */
   __IM uint32_t RESERVED19[38];
  __IOM uint32_t CLK_PLL_CONFIG[15];            /*!< 0x00001600 PLL Configuration Register */
   __IM uint32_t RESERVED20;
  __IOM uint32_t CLK_PLL_STATUS[15];            /*!< 0x00001640 PLL Status Register */
   __IM uint32_t RESERVED21[33];
  __IOM uint32_t CSV_REF_SEL;                   /*!< 0x00001700 Select CSV Reference clock for Active domain */
   __IM uint32_t RESERVED22[3];
        CSV_REF_Type CSV_REF;                   /*!< 0x00001710 CSV registers for the CSV Reference clock */
        CSV_LF_Type CSV_LF;                     /*!< 0x00001720 CSV registers for LF clock */
        CSV_ILO_Type CSV_ILO;                   /*!< 0x00001730 CSV registers for ILO clock */
   __IM uint32_t RESERVED23[48];
  __IOM uint32_t RES_CAUSE;                     /*!< 0x00001800 Reset Cause Observation Register */
  __IOM uint32_t RES_CAUSE2;                    /*!< 0x00001804 Reset Cause Observation Register 2 */
  __IOM uint32_t RES_CAUSE_EXTEND;              /*!< 0x00001808 Extended Reset Cause Observation Register */
   __IM uint32_t RESERVED24[2];
   __OM uint32_t RES_PXRES_CTL;                 /*!< 0x00001814 Programmable XRES Control Register */
   __IM uint32_t RESERVED25[58];
        CLK_PLL400M_Type CLK_PLL400M[15];       /*!< 0x00001900 400MHz PLL Configuration Register */
   __IM uint32_t RESERVED26[132];
  __IOM uint32_t PWR_CBUCK_CTL;                 /*!< 0x00001C00 Core Buck Control Register */
  __IOM uint32_t PWR_CBUCK_CTL2;                /*!< 0x00001C04 Core Buck Control Register 2 */
  __IOM uint32_t PWR_CBUCK_CTL3;                /*!< 0x00001C08 Core Buck Control Register 3 */
   __IM uint32_t PWR_CBUCK_STATUS;              /*!< 0x00001C0C Core Buck Status Register */
  __IOM uint32_t PWR_SDR0_CTL;                  /*!< 0x00001C10 Step Down Regulator 0 Control Register */
  __IOM uint32_t PWR_SDR1_CTL;                  /*!< 0x00001C14 Step Down Regulator 1 Control Register */
   __IM uint32_t RESERVED27[6];
  __IOM uint32_t PWR_HVLDO0_CTL;                /*!< 0x00001C30 HVLDO0 Control Register */
   __IM uint32_t RESERVED28[264];
  __IOM uint32_t TST_XRES_SECURE;               /*!< 0x00002054 SECURE TEST and FIRMWARE TEST Key control register */
   __IM uint32_t RESERVED29[21];
  __IOM uint32_t PWR_TRIM_CBUCK_CTL;            /*!< 0x000020AC CBUCK Trim Register */
   __IM uint32_t RESERVED30[987];
  __IOM uint32_t CLK_TRIM_ECO_CTL;              /*!< 0x0000301C ECO Trim Register */
   __IM uint32_t RESERVED31[128];
  __IOM uint32_t CLK_TRIM_ILO1_CTL;             /*!< 0x00003220 ILO1 Trim Register */
   __IM uint32_t RESERVED32[9079];
  __IOM uint32_t WDT_CTL;                       /*!< 0x0000C000 Watchdog Counter Control Register (Type A) */
  __IOM uint32_t WDT_CNT;                       /*!< 0x0000C004 Watchdog Counter Count Register (Type A) */
  __IOM uint32_t WDT_MATCH;                     /*!< 0x0000C008 Watchdog Counter Match Register (Type A) */
  __IOM uint32_t WDT_MATCH2;                    /*!< 0x0000C00C Watchdog Counter Match Register 2 (Type A) */
   __IM uint32_t RESERVED33[1020];
        MCWDT_STRUCT_Type MCWDT_STRUCT[4];      /*!< 0x0000D000 Multi-Counter Watchdog Timer (Type A) */
} SRSS_Type;                                    /*!< Size = 53504 (0xD100) */


/* CSV_HF_CSV.REF_CTL */
#define CSV_HF_CSV_REF_CTL_STARTUP_Pos          0UL
#define CSV_HF_CSV_REF_CTL_STARTUP_Msk          0xFFFFUL
#define CSV_HF_CSV_REF_CTL_CSV_ACTION_Pos       30UL
#define CSV_HF_CSV_REF_CTL_CSV_ACTION_Msk       0x40000000UL
#define CSV_HF_CSV_REF_CTL_CSV_EN_Pos           31UL
#define CSV_HF_CSV_REF_CTL_CSV_EN_Msk           0x80000000UL
/* CSV_HF_CSV.REF_LIMIT */
#define CSV_HF_CSV_REF_LIMIT_LOWER_Pos          0UL
#define CSV_HF_CSV_REF_LIMIT_LOWER_Msk          0xFFFFUL
#define CSV_HF_CSV_REF_LIMIT_UPPER_Pos          16UL
#define CSV_HF_CSV_REF_LIMIT_UPPER_Msk          0xFFFF0000UL
/* CSV_HF_CSV.MON_CTL */
#define CSV_HF_CSV_MON_CTL_PERIOD_Pos           0UL
#define CSV_HF_CSV_MON_CTL_PERIOD_Msk           0xFFFFUL


/* CSV_REF_CSV.REF_CTL */
#define CSV_REF_CSV_REF_CTL_STARTUP_Pos         0UL
#define CSV_REF_CSV_REF_CTL_STARTUP_Msk         0xFFFFUL
#define CSV_REF_CSV_REF_CTL_CSV_ACTION_Pos      30UL
#define CSV_REF_CSV_REF_CTL_CSV_ACTION_Msk      0x40000000UL
#define CSV_REF_CSV_REF_CTL_CSV_EN_Pos          31UL
#define CSV_REF_CSV_REF_CTL_CSV_EN_Msk          0x80000000UL
/* CSV_REF_CSV.REF_LIMIT */
#define CSV_REF_CSV_REF_LIMIT_LOWER_Pos         0UL
#define CSV_REF_CSV_REF_LIMIT_LOWER_Msk         0xFFFFUL
#define CSV_REF_CSV_REF_LIMIT_UPPER_Pos         16UL
#define CSV_REF_CSV_REF_LIMIT_UPPER_Msk         0xFFFF0000UL
/* CSV_REF_CSV.MON_CTL */
#define CSV_REF_CSV_MON_CTL_PERIOD_Pos          0UL
#define CSV_REF_CSV_MON_CTL_PERIOD_Msk          0xFFFFUL


/* CSV_LF_CSV.REF_CTL */
#define CSV_LF_CSV_REF_CTL_STARTUP_Pos          0UL
#define CSV_LF_CSV_REF_CTL_STARTUP_Msk          0xFFUL
#define CSV_LF_CSV_REF_CTL_CSV_EN_Pos           31UL
#define CSV_LF_CSV_REF_CTL_CSV_EN_Msk           0x80000000UL
/* CSV_LF_CSV.REF_LIMIT */
#define CSV_LF_CSV_REF_LIMIT_LOWER_Pos          0UL
#define CSV_LF_CSV_REF_LIMIT_LOWER_Msk          0xFFUL
#define CSV_LF_CSV_REF_LIMIT_UPPER_Pos          16UL
#define CSV_LF_CSV_REF_LIMIT_UPPER_Msk          0xFF0000UL
/* CSV_LF_CSV.MON_CTL */
#define CSV_LF_CSV_MON_CTL_PERIOD_Pos           0UL
#define CSV_LF_CSV_MON_CTL_PERIOD_Msk           0xFFUL


/* CSV_ILO_CSV.REF_CTL */
#define CSV_ILO_CSV_REF_CTL_STARTUP_Pos         0UL
#define CSV_ILO_CSV_REF_CTL_STARTUP_Msk         0xFFUL
#define CSV_ILO_CSV_REF_CTL_CSV_EN_Pos          31UL
#define CSV_ILO_CSV_REF_CTL_CSV_EN_Msk          0x80000000UL
/* CSV_ILO_CSV.REF_LIMIT */
#define CSV_ILO_CSV_REF_LIMIT_LOWER_Pos         0UL
#define CSV_ILO_CSV_REF_LIMIT_LOWER_Msk         0xFFUL
#define CSV_ILO_CSV_REF_LIMIT_UPPER_Pos         16UL
#define CSV_ILO_CSV_REF_LIMIT_UPPER_Msk         0xFF0000UL
/* CSV_ILO_CSV.MON_CTL */
#define CSV_ILO_CSV_MON_CTL_PERIOD_Pos          0UL
#define CSV_ILO_CSV_MON_CTL_PERIOD_Msk          0xFFUL


/* CLK_PLL400M.CONFIG */
#define CLK_PLL400M_CONFIG_FEEDBACK_DIV_Pos     0UL
#define CLK_PLL400M_CONFIG_FEEDBACK_DIV_Msk     0xFFUL
#define CLK_PLL400M_CONFIG_REFERENCE_DIV_Pos    8UL
#define CLK_PLL400M_CONFIG_REFERENCE_DIV_Msk    0x1F00UL
#define CLK_PLL400M_CONFIG_OUTPUT_DIV_Pos       16UL
#define CLK_PLL400M_CONFIG_OUTPUT_DIV_Msk       0x1F0000UL
#define CLK_PLL400M_CONFIG_LOCK_DELAY_Pos       25UL
#define CLK_PLL400M_CONFIG_LOCK_DELAY_Msk       0x6000000UL
#define CLK_PLL400M_CONFIG_BYPASS_SEL_Pos       28UL
#define CLK_PLL400M_CONFIG_BYPASS_SEL_Msk       0x30000000UL
#define CLK_PLL400M_CONFIG_ENABLE_Pos           31UL
#define CLK_PLL400M_CONFIG_ENABLE_Msk           0x80000000UL
/* CLK_PLL400M.CONFIG2 */
#define CLK_PLL400M_CONFIG2_FRAC_DIV_Pos        0UL
#define CLK_PLL400M_CONFIG2_FRAC_DIV_Msk        0xFFFFFFUL
#define CLK_PLL400M_CONFIG2_FRAC_DITHER_EN_Pos  28UL
#define CLK_PLL400M_CONFIG2_FRAC_DITHER_EN_Msk  0x70000000UL
#define CLK_PLL400M_CONFIG2_FRAC_EN_Pos         31UL
#define CLK_PLL400M_CONFIG2_FRAC_EN_Msk         0x80000000UL
/* CLK_PLL400M.CONFIG3 */
#define CLK_PLL400M_CONFIG3_SSCG_DEPTH_Pos      0UL
#define CLK_PLL400M_CONFIG3_SSCG_DEPTH_Msk      0x3FFUL
#define CLK_PLL400M_CONFIG3_SSCG_RATE_Pos       16UL
#define CLK_PLL400M_CONFIG3_SSCG_RATE_Msk       0x70000UL
#define CLK_PLL400M_CONFIG3_SSCG_DITHER_EN_Pos  24UL
#define CLK_PLL400M_CONFIG3_SSCG_DITHER_EN_Msk  0x1000000UL
#define CLK_PLL400M_CONFIG3_SSCG_MODE_Pos       28UL
#define CLK_PLL400M_CONFIG3_SSCG_MODE_Msk       0x10000000UL
#define CLK_PLL400M_CONFIG3_SSCG_EN_Pos         31UL
#define CLK_PLL400M_CONFIG3_SSCG_EN_Msk         0x80000000UL
/* CLK_PLL400M.STATUS */
#define CLK_PLL400M_STATUS_LOCKED_Pos           0UL
#define CLK_PLL400M_STATUS_LOCKED_Msk           0x1UL
#define CLK_PLL400M_STATUS_UNLOCK_OCCURRED_Pos  1UL
#define CLK_PLL400M_STATUS_UNLOCK_OCCURRED_Msk  0x2UL


/* MCWDT_STRUCT.MCWDT_CNTLOW */
#define MCWDT_STRUCT_MCWDT_CNTLOW_WDT_CTR0_Pos  0UL
#define MCWDT_STRUCT_MCWDT_CNTLOW_WDT_CTR0_Msk  0xFFFFUL
#define MCWDT_STRUCT_MCWDT_CNTLOW_WDT_CTR1_Pos  16UL
#define MCWDT_STRUCT_MCWDT_CNTLOW_WDT_CTR1_Msk  0xFFFF0000UL
/* MCWDT_STRUCT.MCWDT_CNTHIGH */
#define MCWDT_STRUCT_MCWDT_CNTHIGH_WDT_CTR2_Pos 0UL
#define MCWDT_STRUCT_MCWDT_CNTHIGH_WDT_CTR2_Msk 0xFFFFFFFFUL
/* MCWDT_STRUCT.MCWDT_MATCH */
#define MCWDT_STRUCT_MCWDT_MATCH_WDT_MATCH0_Pos 0UL
#define MCWDT_STRUCT_MCWDT_MATCH_WDT_MATCH0_Msk 0xFFFFUL
#define MCWDT_STRUCT_MCWDT_MATCH_WDT_MATCH1_Pos 16UL
#define MCWDT_STRUCT_MCWDT_MATCH_WDT_MATCH1_Msk 0xFFFF0000UL
/* MCWDT_STRUCT.MCWDT_CONFIG */
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_MODE0_Pos 0UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_MODE0_Msk 0x3UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_CLEAR0_Pos 2UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_CLEAR0_Msk 0x4UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_CASCADE0_1_Pos 3UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_CASCADE0_1_Msk 0x8UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_LOWER_MODE0_Pos 4UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_LOWER_MODE0_Msk 0x30UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_CARRY0_1_Pos 6UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_CARRY0_1_Msk 0x40UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_MATCH0_1_Pos 7UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_MATCH0_1_Msk 0x80UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_MODE1_Pos 8UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_MODE1_Msk 0x300UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_CLEAR1_Pos 10UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_CLEAR1_Msk 0x400UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_CASCADE1_2_Pos 11UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_CASCADE1_2_Msk 0x800UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_LOWER_MODE1_Pos 12UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_LOWER_MODE1_Msk 0x3000UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_CARRY1_2_Pos 14UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_CARRY1_2_Msk 0x4000UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_MATCH1_2_Pos 15UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_MATCH1_2_Msk 0x8000UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_MODE2_Pos 16UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_MODE2_Msk 0x10000UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_BITS2_Pos 24UL
#define MCWDT_STRUCT_MCWDT_CONFIG_WDT_BITS2_Msk 0x1F000000UL
/* MCWDT_STRUCT.MCWDT_CTL */
#define MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE0_Pos  0UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE0_Msk  0x1UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLED0_Pos 1UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLED0_Msk 0x2UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_RESET0_Pos   3UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_RESET0_Msk   0x8UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE1_Pos  8UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE1_Msk  0x100UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLED1_Pos 9UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLED1_Msk 0x200UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_RESET1_Pos   11UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_RESET1_Msk   0x800UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE2_Pos  16UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE2_Msk  0x10000UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLED2_Pos 17UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLED2_Msk 0x20000UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_RESET2_Pos   19UL
#define MCWDT_STRUCT_MCWDT_CTL_WDT_RESET2_Msk   0x80000UL
/* MCWDT_STRUCT.MCWDT_INTR */
#define MCWDT_STRUCT_MCWDT_INTR_MCWDT_INT0_Pos  0UL
#define MCWDT_STRUCT_MCWDT_INTR_MCWDT_INT0_Msk  0x1UL
#define MCWDT_STRUCT_MCWDT_INTR_MCWDT_INT1_Pos  1UL
#define MCWDT_STRUCT_MCWDT_INTR_MCWDT_INT1_Msk  0x2UL
#define MCWDT_STRUCT_MCWDT_INTR_MCWDT_INT2_Pos  2UL
#define MCWDT_STRUCT_MCWDT_INTR_MCWDT_INT2_Msk  0x4UL
/* MCWDT_STRUCT.MCWDT_INTR_SET */
#define MCWDT_STRUCT_MCWDT_INTR_SET_MCWDT_INT0_Pos 0UL
#define MCWDT_STRUCT_MCWDT_INTR_SET_MCWDT_INT0_Msk 0x1UL
#define MCWDT_STRUCT_MCWDT_INTR_SET_MCWDT_INT1_Pos 1UL
#define MCWDT_STRUCT_MCWDT_INTR_SET_MCWDT_INT1_Msk 0x2UL
#define MCWDT_STRUCT_MCWDT_INTR_SET_MCWDT_INT2_Pos 2UL
#define MCWDT_STRUCT_MCWDT_INTR_SET_MCWDT_INT2_Msk 0x4UL
/* MCWDT_STRUCT.MCWDT_INTR_MASK */
#define MCWDT_STRUCT_MCWDT_INTR_MASK_MCWDT_INT0_Pos 0UL
#define MCWDT_STRUCT_MCWDT_INTR_MASK_MCWDT_INT0_Msk 0x1UL
#define MCWDT_STRUCT_MCWDT_INTR_MASK_MCWDT_INT1_Pos 1UL
#define MCWDT_STRUCT_MCWDT_INTR_MASK_MCWDT_INT1_Msk 0x2UL
#define MCWDT_STRUCT_MCWDT_INTR_MASK_MCWDT_INT2_Pos 2UL
#define MCWDT_STRUCT_MCWDT_INTR_MASK_MCWDT_INT2_Msk 0x4UL
/* MCWDT_STRUCT.MCWDT_INTR_MASKED */
#define MCWDT_STRUCT_MCWDT_INTR_MASKED_MCWDT_INT0_Pos 0UL
#define MCWDT_STRUCT_MCWDT_INTR_MASKED_MCWDT_INT0_Msk 0x1UL
#define MCWDT_STRUCT_MCWDT_INTR_MASKED_MCWDT_INT1_Pos 1UL
#define MCWDT_STRUCT_MCWDT_INTR_MASKED_MCWDT_INT1_Msk 0x2UL
#define MCWDT_STRUCT_MCWDT_INTR_MASKED_MCWDT_INT2_Pos 2UL
#define MCWDT_STRUCT_MCWDT_INTR_MASKED_MCWDT_INT2_Msk 0x4UL
/* MCWDT_STRUCT.MCWDT_LOCK */
#define MCWDT_STRUCT_MCWDT_LOCK_MCWDT_LOCK_Pos  30UL
#define MCWDT_STRUCT_MCWDT_LOCK_MCWDT_LOCK_Msk  0xC0000000UL
/* MCWDT_STRUCT.MCWDT_LOWER_LIMIT */
#define MCWDT_STRUCT_MCWDT_LOWER_LIMIT_WDT_LOWER_LIMIT0_Pos 0UL
#define MCWDT_STRUCT_MCWDT_LOWER_LIMIT_WDT_LOWER_LIMIT0_Msk 0xFFFFUL
#define MCWDT_STRUCT_MCWDT_LOWER_LIMIT_WDT_LOWER_LIMIT1_Pos 16UL
#define MCWDT_STRUCT_MCWDT_LOWER_LIMIT_WDT_LOWER_LIMIT1_Msk 0xFFFF0000UL


/* SRSS.PWR_LVD_STATUS */
#define SRSS_PWR_LVD_STATUS_HVLVD1_OK_Pos       0UL
#define SRSS_PWR_LVD_STATUS_HVLVD1_OK_Msk       0x1UL
/* SRSS.PWR_LVD_STATUS2 */
#define SRSS_PWR_LVD_STATUS2_HVLVD2_OUT_Pos     0UL
#define SRSS_PWR_LVD_STATUS2_HVLVD2_OUT_Msk     0x1UL
/* SRSS.CLK_DSI_SELECT */
#define SRSS_CLK_DSI_SELECT_DSI_MUX_Pos         0UL
#define SRSS_CLK_DSI_SELECT_DSI_MUX_Msk         0x1FUL
/* SRSS.CLK_OUTPUT_FAST */
#define SRSS_CLK_OUTPUT_FAST_FAST_SEL0_Pos      0UL
#define SRSS_CLK_OUTPUT_FAST_FAST_SEL0_Msk      0xFUL
#define SRSS_CLK_OUTPUT_FAST_PATH_SEL0_Pos      4UL
#define SRSS_CLK_OUTPUT_FAST_PATH_SEL0_Msk      0xF0UL
#define SRSS_CLK_OUTPUT_FAST_HFCLK_SEL0_Pos     8UL
#define SRSS_CLK_OUTPUT_FAST_HFCLK_SEL0_Msk     0xF00UL
#define SRSS_CLK_OUTPUT_FAST_FAST_SEL1_Pos      16UL
#define SRSS_CLK_OUTPUT_FAST_FAST_SEL1_Msk      0xF0000UL
#define SRSS_CLK_OUTPUT_FAST_PATH_SEL1_Pos      20UL
#define SRSS_CLK_OUTPUT_FAST_PATH_SEL1_Msk      0xF00000UL
#define SRSS_CLK_OUTPUT_FAST_HFCLK_SEL1_Pos     24UL
#define SRSS_CLK_OUTPUT_FAST_HFCLK_SEL1_Msk     0xF000000UL
/* SRSS.CLK_OUTPUT_SLOW */
#define SRSS_CLK_OUTPUT_SLOW_SLOW_SEL0_Pos      0UL
#define SRSS_CLK_OUTPUT_SLOW_SLOW_SEL0_Msk      0xFUL
#define SRSS_CLK_OUTPUT_SLOW_SLOW_SEL1_Pos      4UL
#define SRSS_CLK_OUTPUT_SLOW_SLOW_SEL1_Msk      0xF0UL
/* SRSS.CLK_CAL_CNT1 */
#define SRSS_CLK_CAL_CNT1_CAL_COUNTER1_Pos      0UL
#define SRSS_CLK_CAL_CNT1_CAL_COUNTER1_Msk      0xFFFFFFUL
#define SRSS_CLK_CAL_CNT1_CAL_RESET_Pos         29UL
#define SRSS_CLK_CAL_CNT1_CAL_RESET_Msk         0x20000000UL
#define SRSS_CLK_CAL_CNT1_CAL_CLK1_PRESENT_Pos  30UL
#define SRSS_CLK_CAL_CNT1_CAL_CLK1_PRESENT_Msk  0x40000000UL
#define SRSS_CLK_CAL_CNT1_CAL_COUNTER_DONE_Pos  31UL
#define SRSS_CLK_CAL_CNT1_CAL_COUNTER_DONE_Msk  0x80000000UL
/* SRSS.CLK_CAL_CNT2 */
#define SRSS_CLK_CAL_CNT2_CAL_COUNTER2_Pos      0UL
#define SRSS_CLK_CAL_CNT2_CAL_COUNTER2_Msk      0xFFFFFFUL
/* SRSS.SRSS_INTR */
#define SRSS_SRSS_INTR_WDT_MATCH_Pos            0UL
#define SRSS_SRSS_INTR_WDT_MATCH_Msk            0x1UL
#define SRSS_SRSS_INTR_CLK_CAL_Pos              5UL
#define SRSS_SRSS_INTR_CLK_CAL_Msk              0x20UL
#define SRSS_SRSS_INTR_AINTR_Pos                31UL
#define SRSS_SRSS_INTR_AINTR_Msk                0x80000000UL
/* SRSS.SRSS_INTR_SET */
#define SRSS_SRSS_INTR_SET_WDT_MATCH_Pos        0UL
#define SRSS_SRSS_INTR_SET_WDT_MATCH_Msk        0x1UL
#define SRSS_SRSS_INTR_SET_CLK_CAL_Pos          5UL
#define SRSS_SRSS_INTR_SET_CLK_CAL_Msk          0x20UL
/* SRSS.SRSS_INTR_MASK */
#define SRSS_SRSS_INTR_MASK_WDT_MATCH_Pos       0UL
#define SRSS_SRSS_INTR_MASK_WDT_MATCH_Msk       0x1UL
#define SRSS_SRSS_INTR_MASK_CLK_CAL_Pos         5UL
#define SRSS_SRSS_INTR_MASK_CLK_CAL_Msk         0x20UL
/* SRSS.SRSS_INTR_MASKED */
#define SRSS_SRSS_INTR_MASKED_WDT_MATCH_Pos     0UL
#define SRSS_SRSS_INTR_MASKED_WDT_MATCH_Msk     0x1UL
#define SRSS_SRSS_INTR_MASKED_CLK_CAL_Pos       5UL
#define SRSS_SRSS_INTR_MASKED_CLK_CAL_Msk       0x20UL
#define SRSS_SRSS_INTR_MASKED_AINTR_Pos         31UL
#define SRSS_SRSS_INTR_MASKED_AINTR_Msk         0x80000000UL
/* SRSS.SRSS_AINTR */
#define SRSS_SRSS_AINTR_HVLVD1_Pos              1UL
#define SRSS_SRSS_AINTR_HVLVD1_Msk              0x2UL
#define SRSS_SRSS_AINTR_HVLVD2_Pos              2UL
#define SRSS_SRSS_AINTR_HVLVD2_Msk              0x4UL
/* SRSS.SRSS_AINTR_SET */
#define SRSS_SRSS_AINTR_SET_HVLVD1_Pos          1UL
#define SRSS_SRSS_AINTR_SET_HVLVD1_Msk          0x2UL
#define SRSS_SRSS_AINTR_SET_HVLVD2_Pos          2UL
#define SRSS_SRSS_AINTR_SET_HVLVD2_Msk          0x4UL
/* SRSS.SRSS_AINTR_MASK */
#define SRSS_SRSS_AINTR_MASK_HVLVD1_Pos         1UL
#define SRSS_SRSS_AINTR_MASK_HVLVD1_Msk         0x2UL
#define SRSS_SRSS_AINTR_MASK_HVLVD2_Pos         2UL
#define SRSS_SRSS_AINTR_MASK_HVLVD2_Msk         0x4UL
/* SRSS.SRSS_AINTR_MASKED */
#define SRSS_SRSS_AINTR_MASKED_HVLVD1_Pos       1UL
#define SRSS_SRSS_AINTR_MASKED_HVLVD1_Msk       0x2UL
#define SRSS_SRSS_AINTR_MASKED_HVLVD2_Pos       2UL
#define SRSS_SRSS_AINTR_MASKED_HVLVD2_Msk       0x4UL
/* SRSS.TST_DEBUG_CTL */
#define SRSS_TST_DEBUG_CTL_REQUEST_Pos          0UL
#define SRSS_TST_DEBUG_CTL_REQUEST_Msk          0xFUL
#define SRSS_TST_DEBUG_CTL_DEBUG_WFA_Pos        31UL
#define SRSS_TST_DEBUG_CTL_DEBUG_WFA_Msk        0x80000000UL
/* SRSS.TST_DEBUG_STATUS */
#define SRSS_TST_DEBUG_STATUS_DEBUG_STATUS_Pos  0UL
#define SRSS_TST_DEBUG_STATUS_DEBUG_STATUS_Msk  0xFFFFFFFFUL
/* SRSS.RES_SOFT_CTL */
#define SRSS_RES_SOFT_CTL_TRIGGER_SOFT_Pos      0UL
#define SRSS_RES_SOFT_CTL_TRIGGER_SOFT_Msk      0x1UL
/* SRSS.PWR_HIB_DATA */
#define SRSS_PWR_HIB_DATA_HIB_DATA_Pos          0UL
#define SRSS_PWR_HIB_DATA_HIB_DATA_Msk          0xFFFFFFFFUL
/* SRSS.PWR_HIB_WAKE_CTL */
#define SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_SRC_Pos  0UL
#define SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_SRC_Msk  0xFFFFFFUL
#define SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_CSV_BAK_Pos 29UL
#define SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_CSV_BAK_Msk 0x20000000UL
#define SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_RTC_Pos  30UL
#define SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_RTC_Msk  0x40000000UL
#define SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_WDT_Pos  31UL
#define SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_WDT_Msk  0x80000000UL
/* SRSS.PWR_HIB_WAKE_CTL2 */
#define SRSS_PWR_HIB_WAKE_CTL2_HIB_WAKE_SRC_Pos 0UL
#define SRSS_PWR_HIB_WAKE_CTL2_HIB_WAKE_SRC_Msk 0xFFFFFFUL
/* SRSS.PWR_HIB_WAKE_CAUSE */
#define SRSS_PWR_HIB_WAKE_CAUSE_HIB_WAKE_SRC_Pos 0UL
#define SRSS_PWR_HIB_WAKE_CAUSE_HIB_WAKE_SRC_Msk 0xFFFFFFUL
#define SRSS_PWR_HIB_WAKE_CAUSE_HIB_WAKE_CSV_BAK_Pos 29UL
#define SRSS_PWR_HIB_WAKE_CAUSE_HIB_WAKE_CSV_BAK_Msk 0x20000000UL
#define SRSS_PWR_HIB_WAKE_CAUSE_HIB_WAKE_RTC_Pos 30UL
#define SRSS_PWR_HIB_WAKE_CAUSE_HIB_WAKE_RTC_Msk 0x40000000UL
#define SRSS_PWR_HIB_WAKE_CAUSE_HIB_WAKE_WDT_Pos 31UL
#define SRSS_PWR_HIB_WAKE_CAUSE_HIB_WAKE_WDT_Msk 0x80000000UL
/* SRSS.PWR_CTL */
#define SRSS_PWR_CTL_POWER_MODE_Pos             0UL
#define SRSS_PWR_CTL_POWER_MODE_Msk             0x3UL
#define SRSS_PWR_CTL_DEBUG_SESSION_Pos          4UL
#define SRSS_PWR_CTL_DEBUG_SESSION_Msk          0x10UL
#define SRSS_PWR_CTL_LPM_READY_Pos              5UL
#define SRSS_PWR_CTL_LPM_READY_Msk              0x20UL
/* SRSS.PWR_CTL2 */
#define SRSS_PWR_CTL2_LINREG_DIS_Pos            0UL
#define SRSS_PWR_CTL2_LINREG_DIS_Msk            0x1UL
#define SRSS_PWR_CTL2_LINREG_OK_Pos             1UL
#define SRSS_PWR_CTL2_LINREG_OK_Msk             0x2UL
#define SRSS_PWR_CTL2_LINREG_LPMODE_Pos         2UL
#define SRSS_PWR_CTL2_LINREG_LPMODE_Msk         0x4UL
#define SRSS_PWR_CTL2_DPSLP_REG_DIS_Pos         4UL
#define SRSS_PWR_CTL2_DPSLP_REG_DIS_Msk         0x10UL
#define SRSS_PWR_CTL2_RET_REG_DIS_Pos           8UL
#define SRSS_PWR_CTL2_RET_REG_DIS_Msk           0x100UL
#define SRSS_PWR_CTL2_NWELL_REG_DIS_Pos         12UL
#define SRSS_PWR_CTL2_NWELL_REG_DIS_Msk         0x1000UL
#define SRSS_PWR_CTL2_REFV_DIS_Pos              16UL
#define SRSS_PWR_CTL2_REFV_DIS_Msk              0x10000UL
#define SRSS_PWR_CTL2_REFV_OK_Pos               17UL
#define SRSS_PWR_CTL2_REFV_OK_Msk               0x20000UL
#define SRSS_PWR_CTL2_REFVBUF_DIS_Pos           20UL
#define SRSS_PWR_CTL2_REFVBUF_DIS_Msk           0x100000UL
#define SRSS_PWR_CTL2_REFVBUF_OK_Pos            21UL
#define SRSS_PWR_CTL2_REFVBUF_OK_Msk            0x200000UL
#define SRSS_PWR_CTL2_REFI_DIS_Pos              24UL
#define SRSS_PWR_CTL2_REFI_DIS_Msk              0x1000000UL
#define SRSS_PWR_CTL2_REFI_OK_Pos               25UL
#define SRSS_PWR_CTL2_REFI_OK_Msk               0x2000000UL
#define SRSS_PWR_CTL2_REFI_LPMODE_Pos           26UL
#define SRSS_PWR_CTL2_REFI_LPMODE_Msk           0x4000000UL
#define SRSS_PWR_CTL2_PORBOD_LPMODE_Pos         27UL
#define SRSS_PWR_CTL2_PORBOD_LPMODE_Msk         0x8000000UL
#define SRSS_PWR_CTL2_BGREF_LPMODE_Pos          28UL
#define SRSS_PWR_CTL2_BGREF_LPMODE_Msk          0x10000000UL
#define SRSS_PWR_CTL2_FREEZE_DPSLP_Pos          30UL
#define SRSS_PWR_CTL2_FREEZE_DPSLP_Msk          0x40000000UL
#define SRSS_PWR_CTL2_PLL_LS_BYPASS_Pos         31UL
#define SRSS_PWR_CTL2_PLL_LS_BYPASS_Msk         0x80000000UL
/* SRSS.PWR_HIBERNATE */
#define SRSS_PWR_HIBERNATE_TOKEN_Pos            0UL
#define SRSS_PWR_HIBERNATE_TOKEN_Msk            0xFFUL
#define SRSS_PWR_HIBERNATE_UNLOCK_Pos           8UL
#define SRSS_PWR_HIBERNATE_UNLOCK_Msk           0xFF00UL
#define SRSS_PWR_HIBERNATE_FREEZE_Pos           17UL
#define SRSS_PWR_HIBERNATE_FREEZE_Msk           0x20000UL
#define SRSS_PWR_HIBERNATE_MASK_HIBALARM_Pos    18UL
#define SRSS_PWR_HIBERNATE_MASK_HIBALARM_Msk    0x40000UL
#define SRSS_PWR_HIBERNATE_MASK_HIBWDT_Pos      19UL
#define SRSS_PWR_HIBERNATE_MASK_HIBWDT_Msk      0x80000UL
#define SRSS_PWR_HIBERNATE_POLARITY_HIBPIN_Pos  20UL
#define SRSS_PWR_HIBERNATE_POLARITY_HIBPIN_Msk  0xF00000UL
#define SRSS_PWR_HIBERNATE_MASK_HIBPIN_Pos      24UL
#define SRSS_PWR_HIBERNATE_MASK_HIBPIN_Msk      0xF000000UL
#define SRSS_PWR_HIBERNATE_SENSE_MODE_Pos       29UL
#define SRSS_PWR_HIBERNATE_SENSE_MODE_Msk       0x20000000UL
#define SRSS_PWR_HIBERNATE_HIBERNATE_DISABLE_Pos 30UL
#define SRSS_PWR_HIBERNATE_HIBERNATE_DISABLE_Msk 0x40000000UL
#define SRSS_PWR_HIBERNATE_HIBERNATE_Pos        31UL
#define SRSS_PWR_HIBERNATE_HIBERNATE_Msk        0x80000000UL
/* SRSS.PWR_BUCK_CTL */
#define SRSS_PWR_BUCK_CTL_BUCK_OUT1_SEL_Pos     0UL
#define SRSS_PWR_BUCK_CTL_BUCK_OUT1_SEL_Msk     0x7UL
#define SRSS_PWR_BUCK_CTL_BUCK_EN_Pos           30UL
#define SRSS_PWR_BUCK_CTL_BUCK_EN_Msk           0x40000000UL
#define SRSS_PWR_BUCK_CTL_BUCK_OUT1_EN_Pos      31UL
#define SRSS_PWR_BUCK_CTL_BUCK_OUT1_EN_Msk      0x80000000UL
/* SRSS.PWR_BUCK_CTL2 */
#define SRSS_PWR_BUCK_CTL2_BUCK_OUT2_SEL_Pos    0UL
#define SRSS_PWR_BUCK_CTL2_BUCK_OUT2_SEL_Msk    0x7UL
#define SRSS_PWR_BUCK_CTL2_BUCK_OUT2_HW_SEL_Pos 30UL
#define SRSS_PWR_BUCK_CTL2_BUCK_OUT2_HW_SEL_Msk 0x40000000UL
#define SRSS_PWR_BUCK_CTL2_BUCK_OUT2_EN_Pos     31UL
#define SRSS_PWR_BUCK_CTL2_BUCK_OUT2_EN_Msk     0x80000000UL
/* SRSS.PWR_SSV_CTL */
#define SRSS_PWR_SSV_CTL_BODVDDD_VSEL_Pos       0UL
#define SRSS_PWR_SSV_CTL_BODVDDD_VSEL_Msk       0x1UL
#define SRSS_PWR_SSV_CTL_BODVDDD_ENABLE_Pos     3UL
#define SRSS_PWR_SSV_CTL_BODVDDD_ENABLE_Msk     0x8UL
#define SRSS_PWR_SSV_CTL_BODVDDA_VSEL_Pos       4UL
#define SRSS_PWR_SSV_CTL_BODVDDA_VSEL_Msk       0x10UL
#define SRSS_PWR_SSV_CTL_BODVDDA_ACTION_Pos     6UL
#define SRSS_PWR_SSV_CTL_BODVDDA_ACTION_Msk     0xC0UL
#define SRSS_PWR_SSV_CTL_BODVDDA_ENABLE_Pos     8UL
#define SRSS_PWR_SSV_CTL_BODVDDA_ENABLE_Msk     0x100UL
#define SRSS_PWR_SSV_CTL_BODVCCD_ENABLE_Pos     11UL
#define SRSS_PWR_SSV_CTL_BODVCCD_ENABLE_Msk     0x800UL
#define SRSS_PWR_SSV_CTL_OVDVDDD_VSEL_Pos       16UL
#define SRSS_PWR_SSV_CTL_OVDVDDD_VSEL_Msk       0x10000UL
#define SRSS_PWR_SSV_CTL_OVDVDDD_ENABLE_Pos     19UL
#define SRSS_PWR_SSV_CTL_OVDVDDD_ENABLE_Msk     0x80000UL
#define SRSS_PWR_SSV_CTL_OVDVDDA_VSEL_Pos       20UL
#define SRSS_PWR_SSV_CTL_OVDVDDA_VSEL_Msk       0x100000UL
#define SRSS_PWR_SSV_CTL_OVDVDDA_ACTION_Pos     22UL
#define SRSS_PWR_SSV_CTL_OVDVDDA_ACTION_Msk     0xC00000UL
#define SRSS_PWR_SSV_CTL_OVDVDDA_ENABLE_Pos     24UL
#define SRSS_PWR_SSV_CTL_OVDVDDA_ENABLE_Msk     0x1000000UL
#define SRSS_PWR_SSV_CTL_OVDVCCD_ENABLE_Pos     27UL
#define SRSS_PWR_SSV_CTL_OVDVCCD_ENABLE_Msk     0x8000000UL
/* SRSS.PWR_SSV_STATUS */
#define SRSS_PWR_SSV_STATUS_BODVDDD_OK_Pos      0UL
#define SRSS_PWR_SSV_STATUS_BODVDDD_OK_Msk      0x1UL
#define SRSS_PWR_SSV_STATUS_BODVDDA_OK_Pos      1UL
#define SRSS_PWR_SSV_STATUS_BODVDDA_OK_Msk      0x2UL
#define SRSS_PWR_SSV_STATUS_BODVCCD_OK_Pos      2UL
#define SRSS_PWR_SSV_STATUS_BODVCCD_OK_Msk      0x4UL
#define SRSS_PWR_SSV_STATUS_OVDVDDD_OK_Pos      8UL
#define SRSS_PWR_SSV_STATUS_OVDVDDD_OK_Msk      0x100UL
#define SRSS_PWR_SSV_STATUS_OVDVDDA_OK_Pos      9UL
#define SRSS_PWR_SSV_STATUS_OVDVDDA_OK_Msk      0x200UL
#define SRSS_PWR_SSV_STATUS_OVDVCCD_OK_Pos      10UL
#define SRSS_PWR_SSV_STATUS_OVDVCCD_OK_Msk      0x400UL
#define SRSS_PWR_SSV_STATUS_OCD_ACT_LINREG_OK_Pos 16UL
#define SRSS_PWR_SSV_STATUS_OCD_ACT_LINREG_OK_Msk 0x10000UL
#define SRSS_PWR_SSV_STATUS_OCD_DPSLP_REG_OK_Pos 17UL
#define SRSS_PWR_SSV_STATUS_OCD_DPSLP_REG_OK_Msk 0x20000UL
/* SRSS.PWR_LVD_CTL */
#define SRSS_PWR_LVD_CTL_HVLVD1_TRIPSEL_Pos     0UL
#define SRSS_PWR_LVD_CTL_HVLVD1_TRIPSEL_Msk     0xFUL
#define SRSS_PWR_LVD_CTL_HVLVD1_SRCSEL_Pos      4UL
#define SRSS_PWR_LVD_CTL_HVLVD1_SRCSEL_Msk      0x70UL
#define SRSS_PWR_LVD_CTL_HVLVD1_EN_Pos          7UL
#define SRSS_PWR_LVD_CTL_HVLVD1_EN_Msk          0x80UL
#define SRSS_PWR_LVD_CTL_HVLVD1_TRIPSEL_HT_Pos  8UL
#define SRSS_PWR_LVD_CTL_HVLVD1_TRIPSEL_HT_Msk  0x1F00UL
#define SRSS_PWR_LVD_CTL_HVLVD1_DPSLP_EN_HT_Pos 14UL
#define SRSS_PWR_LVD_CTL_HVLVD1_DPSLP_EN_HT_Msk 0x4000UL
#define SRSS_PWR_LVD_CTL_HVLVD1_EN_HT_Pos       15UL
#define SRSS_PWR_LVD_CTL_HVLVD1_EN_HT_Msk       0x8000UL
#define SRSS_PWR_LVD_CTL_HVLVD1_EDGE_SEL_Pos    16UL
#define SRSS_PWR_LVD_CTL_HVLVD1_EDGE_SEL_Msk    0x30000UL
#define SRSS_PWR_LVD_CTL_HVLVD1_ACTION_Pos      18UL
#define SRSS_PWR_LVD_CTL_HVLVD1_ACTION_Msk      0x40000UL
/* SRSS.PWR_LVD_CTL2 */
#define SRSS_PWR_LVD_CTL2_HVLVD2_TRIPSEL_HT_Pos 8UL
#define SRSS_PWR_LVD_CTL2_HVLVD2_TRIPSEL_HT_Msk 0x1F00UL
#define SRSS_PWR_LVD_CTL2_HVLVD2_DPSLP_EN_HT_Pos 14UL
#define SRSS_PWR_LVD_CTL2_HVLVD2_DPSLP_EN_HT_Msk 0x4000UL
#define SRSS_PWR_LVD_CTL2_HVLVD2_EN_HT_Pos      15UL
#define SRSS_PWR_LVD_CTL2_HVLVD2_EN_HT_Msk      0x8000UL
#define SRSS_PWR_LVD_CTL2_HVLVD2_EDGE_SEL_Pos   16UL
#define SRSS_PWR_LVD_CTL2_HVLVD2_EDGE_SEL_Msk   0x30000UL
#define SRSS_PWR_LVD_CTL2_HVLVD2_ACTION_Pos     18UL
#define SRSS_PWR_LVD_CTL2_HVLVD2_ACTION_Msk     0x40000UL
/* SRSS.PWR_REGHC_CTL */
#define SRSS_PWR_REGHC_CTL_REGHC_MODE_Pos       0UL
#define SRSS_PWR_REGHC_CTL_REGHC_MODE_Msk       0x1UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_DRV_VOUT_Pos 2UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_DRV_VOUT_Msk 0xCUL
#define SRSS_PWR_REGHC_CTL_REGHC_VADJ_Pos       4UL
#define SRSS_PWR_REGHC_CTL_REGHC_VADJ_Msk       0x1F0UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_USE_LINREG_Pos 10UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_USE_LINREG_Msk 0x400UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_USE_RADJ_Pos 11UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_USE_RADJ_Msk 0x800UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_RADJ_Pos  12UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_RADJ_Msk  0x7000UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_CTL_OUTEN_Pos 16UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_CTL_OUTEN_Msk 0x10000UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_CTL_POLARITY_Pos 17UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_CTL_POLARITY_Msk 0x20000UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_STATUS_INEN_Pos 18UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_STATUS_INEN_Msk 0x40000UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_STATUS_POLARITY_Pos 19UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_STATUS_POLARITY_Msk 0x80000UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_STATUS_WAIT_Pos 20UL
#define SRSS_PWR_REGHC_CTL_REGHC_PMIC_STATUS_WAIT_Msk 0x3FF00000UL
#define SRSS_PWR_REGHC_CTL_REGHC_TRANS_USE_OCD_Pos 30UL
#define SRSS_PWR_REGHC_CTL_REGHC_TRANS_USE_OCD_Msk 0x40000000UL
#define SRSS_PWR_REGHC_CTL_REGHC_CONFIGURED_Pos 31UL
#define SRSS_PWR_REGHC_CTL_REGHC_CONFIGURED_Msk 0x80000000UL
/* SRSS.PWR_REGHC_STATUS */
#define SRSS_PWR_REGHC_STATUS_REGHC_ENABLED_Pos 0UL
#define SRSS_PWR_REGHC_STATUS_REGHC_ENABLED_Msk 0x1UL
#define SRSS_PWR_REGHC_STATUS_REGHC_OCD_OK_Pos  1UL
#define SRSS_PWR_REGHC_STATUS_REGHC_OCD_OK_Msk  0x2UL
#define SRSS_PWR_REGHC_STATUS_REGHC_CKT_OK_Pos  2UL
#define SRSS_PWR_REGHC_STATUS_REGHC_CKT_OK_Msk  0x4UL
#define SRSS_PWR_REGHC_STATUS_REGHC_UV_OUT_Pos  8UL
#define SRSS_PWR_REGHC_STATUS_REGHC_UV_OUT_Msk  0x100UL
#define SRSS_PWR_REGHC_STATUS_REGHC_OV_OUT_Pos  9UL
#define SRSS_PWR_REGHC_STATUS_REGHC_OV_OUT_Msk  0x200UL
#define SRSS_PWR_REGHC_STATUS_REGHC_PMIC_STATUS_OK_Pos 12UL
#define SRSS_PWR_REGHC_STATUS_REGHC_PMIC_STATUS_OK_Msk 0x1000UL
#define SRSS_PWR_REGHC_STATUS_REGHC_SEQ_BUSY_Pos 31UL
#define SRSS_PWR_REGHC_STATUS_REGHC_SEQ_BUSY_Msk 0x80000000UL
/* SRSS.PWR_REGHC_CTL2 */
#define SRSS_PWR_REGHC_CTL2_REGHC_PMIC_STATUS_TIMEOUT_Pos 0UL
#define SRSS_PWR_REGHC_CTL2_REGHC_PMIC_STATUS_TIMEOUT_Msk 0xFFUL
#define SRSS_PWR_REGHC_CTL2_REGHC_EN_Pos        31UL
#define SRSS_PWR_REGHC_CTL2_REGHC_EN_Msk        0x80000000UL
/* SRSS.PWR_PMIC_CTL */
#define SRSS_PWR_PMIC_CTL_PMIC_VREF_Pos         2UL
#define SRSS_PWR_PMIC_CTL_PMIC_VREF_Msk         0xCUL
#define SRSS_PWR_PMIC_CTL_PMIC_VADJ_Pos         4UL
#define SRSS_PWR_PMIC_CTL_PMIC_VADJ_Msk         0x1F0UL
#define SRSS_PWR_PMIC_CTL_PMIC_USE_LINREG_Pos   10UL
#define SRSS_PWR_PMIC_CTL_PMIC_USE_LINREG_Msk   0x400UL
#define SRSS_PWR_PMIC_CTL_PMIC_VADJ_BUF_EN_Pos  15UL
#define SRSS_PWR_PMIC_CTL_PMIC_VADJ_BUF_EN_Msk  0x8000UL
#define SRSS_PWR_PMIC_CTL_PMIC_CTL_OUTEN_Pos    16UL
#define SRSS_PWR_PMIC_CTL_PMIC_CTL_OUTEN_Msk    0x10000UL
#define SRSS_PWR_PMIC_CTL_PMIC_CTL_POLARITY_Pos 17UL
#define SRSS_PWR_PMIC_CTL_PMIC_CTL_POLARITY_Msk 0x20000UL
#define SRSS_PWR_PMIC_CTL_PMIC_STATUS_INEN_Pos  18UL
#define SRSS_PWR_PMIC_CTL_PMIC_STATUS_INEN_Msk  0x40000UL
#define SRSS_PWR_PMIC_CTL_PMIC_STATUS_POLARITY_Pos 19UL
#define SRSS_PWR_PMIC_CTL_PMIC_STATUS_POLARITY_Msk 0x80000UL
#define SRSS_PWR_PMIC_CTL_PMIC_STATUS_WAIT_Pos  20UL
#define SRSS_PWR_PMIC_CTL_PMIC_STATUS_WAIT_Msk  0x3FF00000UL
#define SRSS_PWR_PMIC_CTL_PMIC_CONFIGURED_Pos   31UL
#define SRSS_PWR_PMIC_CTL_PMIC_CONFIGURED_Msk   0x80000000UL
/* SRSS.PWR_PMIC_STATUS */
#define SRSS_PWR_PMIC_STATUS_PMIC_ENABLED_Pos   0UL
#define SRSS_PWR_PMIC_STATUS_PMIC_ENABLED_Msk   0x1UL
#define SRSS_PWR_PMIC_STATUS_PMIC_STATUS_OK_Pos 12UL
#define SRSS_PWR_PMIC_STATUS_PMIC_STATUS_OK_Msk 0x1000UL
#define SRSS_PWR_PMIC_STATUS_PMIC_SEQ_BUSY_Pos  31UL
#define SRSS_PWR_PMIC_STATUS_PMIC_SEQ_BUSY_Msk  0x80000000UL
/* SRSS.PWR_PMIC_CTL2 */
#define SRSS_PWR_PMIC_CTL2_PMIC_STATUS_TIMEOUT_Pos 0UL
#define SRSS_PWR_PMIC_CTL2_PMIC_STATUS_TIMEOUT_Msk 0xFFUL
#define SRSS_PWR_PMIC_CTL2_PMIC_EN_Pos          31UL
#define SRSS_PWR_PMIC_CTL2_PMIC_EN_Msk          0x80000000UL
/* SRSS.PWR_PMIC_CTL4 */
#define SRSS_PWR_PMIC_CTL4_PMIC_VADJ_DIS_Pos    30UL
#define SRSS_PWR_PMIC_CTL4_PMIC_VADJ_DIS_Msk    0x40000000UL
#define SRSS_PWR_PMIC_CTL4_PMIC_DPSLP_Pos       31UL
#define SRSS_PWR_PMIC_CTL4_PMIC_DPSLP_Msk       0x80000000UL
/* SRSS.CLK_PATH_SELECT */
#define SRSS_CLK_PATH_SELECT_PATH_MUX_Pos       0UL
#define SRSS_CLK_PATH_SELECT_PATH_MUX_Msk       0x7UL
/* SRSS.CLK_ROOT_SELECT */
#define SRSS_CLK_ROOT_SELECT_ROOT_MUX_Pos       0UL
#define SRSS_CLK_ROOT_SELECT_ROOT_MUX_Msk       0xFUL
#define SRSS_CLK_ROOT_SELECT_ROOT_DIV_Pos       4UL
#define SRSS_CLK_ROOT_SELECT_ROOT_DIV_Msk       0x30UL
#define SRSS_CLK_ROOT_SELECT_DIRECT_MUX_Pos     8UL
#define SRSS_CLK_ROOT_SELECT_DIRECT_MUX_Msk     0x100UL
#define SRSS_CLK_ROOT_SELECT_ENABLE_Pos         31UL
#define SRSS_CLK_ROOT_SELECT_ENABLE_Msk         0x80000000UL
/* SRSS.CLK_DIRECT_SELECT */
#define SRSS_CLK_DIRECT_SELECT_DIRECT_MUX_Pos   8UL
#define SRSS_CLK_DIRECT_SELECT_DIRECT_MUX_Msk   0x100UL
/* SRSS.CLK_SELECT */
#define SRSS_CLK_SELECT_LFCLK_SEL_Pos           0UL
#define SRSS_CLK_SELECT_LFCLK_SEL_Msk           0x7UL
#define SRSS_CLK_SELECT_PUMP_SEL_Pos            8UL
#define SRSS_CLK_SELECT_PUMP_SEL_Msk            0xF00UL
#define SRSS_CLK_SELECT_PUMP_DIV_Pos            12UL
#define SRSS_CLK_SELECT_PUMP_DIV_Msk            0x7000UL
#define SRSS_CLK_SELECT_PUMP_ENABLE_Pos         15UL
#define SRSS_CLK_SELECT_PUMP_ENABLE_Msk         0x8000UL
/* SRSS.CLK_ILO0_CONFIG */
#define SRSS_CLK_ILO0_CONFIG_ILO0_BACKUP_Pos    0UL
#define SRSS_CLK_ILO0_CONFIG_ILO0_BACKUP_Msk    0x1UL
#define SRSS_CLK_ILO0_CONFIG_ILO0_MON_ENABLE_Pos 30UL
#define SRSS_CLK_ILO0_CONFIG_ILO0_MON_ENABLE_Msk 0x40000000UL
#define SRSS_CLK_ILO0_CONFIG_ENABLE_Pos         31UL
#define SRSS_CLK_ILO0_CONFIG_ENABLE_Msk         0x80000000UL
/* SRSS.CLK_ILO1_CONFIG */
#define SRSS_CLK_ILO1_CONFIG_ILO1_MON_ENABLE_Pos 30UL
#define SRSS_CLK_ILO1_CONFIG_ILO1_MON_ENABLE_Msk 0x40000000UL
#define SRSS_CLK_ILO1_CONFIG_ENABLE_Pos         31UL
#define SRSS_CLK_ILO1_CONFIG_ENABLE_Msk         0x80000000UL
/* SRSS.CLK_IMO_CONFIG */
#define SRSS_CLK_IMO_CONFIG_DPSLP_ENABLE_Pos    30UL
#define SRSS_CLK_IMO_CONFIG_DPSLP_ENABLE_Msk    0x40000000UL
#define SRSS_CLK_IMO_CONFIG_ENABLE_Pos          31UL
#define SRSS_CLK_IMO_CONFIG_ENABLE_Msk          0x80000000UL
/* SRSS.CLK_ECO_CONFIG */
#define SRSS_CLK_ECO_CONFIG_AGC_EN_Pos          1UL
#define SRSS_CLK_ECO_CONFIG_AGC_EN_Msk          0x2UL
#define SRSS_CLK_ECO_CONFIG_ECO_DIV_DISABLE_Pos 27UL
#define SRSS_CLK_ECO_CONFIG_ECO_DIV_DISABLE_Msk 0x8000000UL
#define SRSS_CLK_ECO_CONFIG_ECO_DIV_ENABLE_Pos  28UL
#define SRSS_CLK_ECO_CONFIG_ECO_DIV_ENABLE_Msk  0x10000000UL
#define SRSS_CLK_ECO_CONFIG_ECO_EN_Pos          31UL
#define SRSS_CLK_ECO_CONFIG_ECO_EN_Msk          0x80000000UL
/* SRSS.CLK_ECO_PRESCALE */
#define SRSS_CLK_ECO_PRESCALE_ECO_DIV_ENABLED_Pos 0UL
#define SRSS_CLK_ECO_PRESCALE_ECO_DIV_ENABLED_Msk 0x1UL
#define SRSS_CLK_ECO_PRESCALE_ECO_FRAC_DIV_Pos  8UL
#define SRSS_CLK_ECO_PRESCALE_ECO_FRAC_DIV_Msk  0xFF00UL
#define SRSS_CLK_ECO_PRESCALE_ECO_INT_DIV_Pos   16UL
#define SRSS_CLK_ECO_PRESCALE_ECO_INT_DIV_Msk   0x3FF0000UL
/* SRSS.CLK_ECO_STATUS */
#define SRSS_CLK_ECO_STATUS_ECO_OK_Pos          0UL
#define SRSS_CLK_ECO_STATUS_ECO_OK_Msk          0x1UL
#define SRSS_CLK_ECO_STATUS_ECO_READY_Pos       1UL
#define SRSS_CLK_ECO_STATUS_ECO_READY_Msk       0x2UL
/* SRSS.CLK_PILO_CONFIG */
#define SRSS_CLK_PILO_CONFIG_PILO_BACKUP_Pos    0UL
#define SRSS_CLK_PILO_CONFIG_PILO_BACKUP_Msk    0x1UL
#define SRSS_CLK_PILO_CONFIG_PILO_TCSC_EN_Pos   16UL
#define SRSS_CLK_PILO_CONFIG_PILO_TCSC_EN_Msk   0x10000UL
#define SRSS_CLK_PILO_CONFIG_PILO_EN_Pos        31UL
#define SRSS_CLK_PILO_CONFIG_PILO_EN_Msk        0x80000000UL
/* SRSS.CLK_FLL_CONFIG */
#define SRSS_CLK_FLL_CONFIG_FLL_MULT_Pos        0UL
#define SRSS_CLK_FLL_CONFIG_FLL_MULT_Msk        0x3FFFFUL
#define SRSS_CLK_FLL_CONFIG_FLL_OUTPUT_DIV_Pos  24UL
#define SRSS_CLK_FLL_CONFIG_FLL_OUTPUT_DIV_Msk  0x1000000UL
#define SRSS_CLK_FLL_CONFIG_FLL_ENABLE_Pos      31UL
#define SRSS_CLK_FLL_CONFIG_FLL_ENABLE_Msk      0x80000000UL
/* SRSS.CLK_FLL_CONFIG2 */
#define SRSS_CLK_FLL_CONFIG2_FLL_REF_DIV_Pos    0UL
#define SRSS_CLK_FLL_CONFIG2_FLL_REF_DIV_Msk    0x1FFFUL
#define SRSS_CLK_FLL_CONFIG2_LOCK_TOL_Pos       16UL
#define SRSS_CLK_FLL_CONFIG2_LOCK_TOL_Msk       0xFF0000UL
#define SRSS_CLK_FLL_CONFIG2_UPDATE_TOL_Pos     24UL
#define SRSS_CLK_FLL_CONFIG2_UPDATE_TOL_Msk     0xFF000000UL
/* SRSS.CLK_FLL_CONFIG3 */
#define SRSS_CLK_FLL_CONFIG3_FLL_LF_IGAIN_Pos   0UL
#define SRSS_CLK_FLL_CONFIG3_FLL_LF_IGAIN_Msk   0xFUL
#define SRSS_CLK_FLL_CONFIG3_FLL_LF_PGAIN_Pos   4UL
#define SRSS_CLK_FLL_CONFIG3_FLL_LF_PGAIN_Msk   0xF0UL
#define SRSS_CLK_FLL_CONFIG3_SETTLING_COUNT_Pos 8UL
#define SRSS_CLK_FLL_CONFIG3_SETTLING_COUNT_Msk 0x1FFF00UL
#define SRSS_CLK_FLL_CONFIG3_BYPASS_SEL_Pos     28UL
#define SRSS_CLK_FLL_CONFIG3_BYPASS_SEL_Msk     0x30000000UL
/* SRSS.CLK_FLL_CONFIG4 */
#define SRSS_CLK_FLL_CONFIG4_CCO_LIMIT_Pos      0UL
#define SRSS_CLK_FLL_CONFIG4_CCO_LIMIT_Msk      0xFFUL
#define SRSS_CLK_FLL_CONFIG4_CCO_RANGE_Pos      8UL
#define SRSS_CLK_FLL_CONFIG4_CCO_RANGE_Msk      0x700UL
#define SRSS_CLK_FLL_CONFIG4_CCO_FREQ_Pos       16UL
#define SRSS_CLK_FLL_CONFIG4_CCO_FREQ_Msk       0x1FF0000UL
#define SRSS_CLK_FLL_CONFIG4_CCO_HW_UPDATE_DIS_Pos 30UL
#define SRSS_CLK_FLL_CONFIG4_CCO_HW_UPDATE_DIS_Msk 0x40000000UL
#define SRSS_CLK_FLL_CONFIG4_CCO_ENABLE_Pos     31UL
#define SRSS_CLK_FLL_CONFIG4_CCO_ENABLE_Msk     0x80000000UL
/* SRSS.CLK_FLL_STATUS */
#define SRSS_CLK_FLL_STATUS_LOCKED_Pos          0UL
#define SRSS_CLK_FLL_STATUS_LOCKED_Msk          0x1UL
#define SRSS_CLK_FLL_STATUS_UNLOCK_OCCURRED_Pos 1UL
#define SRSS_CLK_FLL_STATUS_UNLOCK_OCCURRED_Msk 0x2UL
#define SRSS_CLK_FLL_STATUS_CCO_READY_Pos       2UL
#define SRSS_CLK_FLL_STATUS_CCO_READY_Msk       0x4UL
/* SRSS.CLK_ECO_CONFIG2 */
#define SRSS_CLK_ECO_CONFIG2_WDTRIM_Pos         0UL
#define SRSS_CLK_ECO_CONFIG2_WDTRIM_Msk         0x7UL
#define SRSS_CLK_ECO_CONFIG2_ATRIM_Pos          4UL
#define SRSS_CLK_ECO_CONFIG2_ATRIM_Msk          0xF0UL
#define SRSS_CLK_ECO_CONFIG2_FTRIM_Pos          8UL
#define SRSS_CLK_ECO_CONFIG2_FTRIM_Msk          0x300UL
#define SRSS_CLK_ECO_CONFIG2_RTRIM_Pos          10UL
#define SRSS_CLK_ECO_CONFIG2_RTRIM_Msk          0xC00UL
#define SRSS_CLK_ECO_CONFIG2_GTRIM_Pos          12UL
#define SRSS_CLK_ECO_CONFIG2_GTRIM_Msk          0x7000UL
/* SRSS.CLK_ILO_CONFIG */
#define SRSS_CLK_ILO_CONFIG_ILO_BACKUP_Pos      0UL
#define SRSS_CLK_ILO_CONFIG_ILO_BACKUP_Msk      0x1UL
#define SRSS_CLK_ILO_CONFIG_ENABLE_Pos          31UL
#define SRSS_CLK_ILO_CONFIG_ENABLE_Msk          0x80000000UL
/* SRSS.CLK_TRIM_ILO_CTL */
#define SRSS_CLK_TRIM_ILO_CTL_ILO_FTRIM_Pos     0UL
#define SRSS_CLK_TRIM_ILO_CTL_ILO_FTRIM_Msk     0x3FUL
/* SRSS.CLK_TRIM_ILO0_CTL */
#define SRSS_CLK_TRIM_ILO0_CTL_ILO0_FTRIM_Pos   0UL
#define SRSS_CLK_TRIM_ILO0_CTL_ILO0_FTRIM_Msk   0x3FUL
#define SRSS_CLK_TRIM_ILO0_CTL_ILO0_MONTRIM_Pos 8UL
#define SRSS_CLK_TRIM_ILO0_CTL_ILO0_MONTRIM_Msk 0xF00UL
/* SRSS.CLK_MF_SELECT */
#define SRSS_CLK_MF_SELECT_MFCLK_SEL_Pos        0UL
#define SRSS_CLK_MF_SELECT_MFCLK_SEL_Msk        0x7UL
#define SRSS_CLK_MF_SELECT_MFCLK_DIV_Pos        8UL
#define SRSS_CLK_MF_SELECT_MFCLK_DIV_Msk        0xFF00UL
#define SRSS_CLK_MF_SELECT_ENABLE_Pos           31UL
#define SRSS_CLK_MF_SELECT_ENABLE_Msk           0x80000000UL
/* SRSS.CLK_MFO_CONFIG */
#define SRSS_CLK_MFO_CONFIG_DPSLP_ENABLE_Pos    30UL
#define SRSS_CLK_MFO_CONFIG_DPSLP_ENABLE_Msk    0x40000000UL
#define SRSS_CLK_MFO_CONFIG_ENABLE_Pos          31UL
#define SRSS_CLK_MFO_CONFIG_ENABLE_Msk          0x80000000UL
/* SRSS.CLK_IHO_CONFIG */
#define SRSS_CLK_IHO_CONFIG_ENABLE_Pos          31UL
#define SRSS_CLK_IHO_CONFIG_ENABLE_Msk          0x80000000UL
/* SRSS.CLK_ALTHF_CTL */
#define SRSS_CLK_ALTHF_CTL_ALTHF_ENABLED_Pos    0UL
#define SRSS_CLK_ALTHF_CTL_ALTHF_ENABLED_Msk    0x1UL
#define SRSS_CLK_ALTHF_CTL_ALTHF_ENABLE_Pos     31UL
#define SRSS_CLK_ALTHF_CTL_ALTHF_ENABLE_Msk     0x80000000UL
/* SRSS.CLK_PLL_CONFIG */
#define SRSS_CLK_PLL_CONFIG_FEEDBACK_DIV_Pos    0UL
#define SRSS_CLK_PLL_CONFIG_FEEDBACK_DIV_Msk    0x7FUL
#define SRSS_CLK_PLL_CONFIG_REFERENCE_DIV_Pos   8UL
#define SRSS_CLK_PLL_CONFIG_REFERENCE_DIV_Msk   0x1F00UL
#define SRSS_CLK_PLL_CONFIG_OUTPUT_DIV_Pos      16UL
#define SRSS_CLK_PLL_CONFIG_OUTPUT_DIV_Msk      0x1F0000UL
#define SRSS_CLK_PLL_CONFIG_LOCK_DELAY_Pos      25UL
#define SRSS_CLK_PLL_CONFIG_LOCK_DELAY_Msk      0x6000000UL
#define SRSS_CLK_PLL_CONFIG_PLL_LF_MODE_Pos     27UL
#define SRSS_CLK_PLL_CONFIG_PLL_LF_MODE_Msk     0x8000000UL
#define SRSS_CLK_PLL_CONFIG_BYPASS_SEL_Pos      28UL
#define SRSS_CLK_PLL_CONFIG_BYPASS_SEL_Msk      0x30000000UL
#define SRSS_CLK_PLL_CONFIG_ENABLE_Pos          31UL
#define SRSS_CLK_PLL_CONFIG_ENABLE_Msk          0x80000000UL
/* SRSS.CLK_PLL_STATUS */
#define SRSS_CLK_PLL_STATUS_LOCKED_Pos          0UL
#define SRSS_CLK_PLL_STATUS_LOCKED_Msk          0x1UL
#define SRSS_CLK_PLL_STATUS_UNLOCK_OCCURRED_Pos 1UL
#define SRSS_CLK_PLL_STATUS_UNLOCK_OCCURRED_Msk 0x2UL
/* SRSS.CSV_REF_SEL */
#define SRSS_CSV_REF_SEL_REF_MUX_Pos            0UL
#define SRSS_CSV_REF_SEL_REF_MUX_Msk            0x7UL
/* SRSS.RES_CAUSE */
#define SRSS_RES_CAUSE_RESET_WDT_Pos            0UL
#define SRSS_RES_CAUSE_RESET_WDT_Msk            0x1UL
#define SRSS_RES_CAUSE_RESET_ACT_FAULT_Pos      1UL
#define SRSS_RES_CAUSE_RESET_ACT_FAULT_Msk      0x2UL
#define SRSS_RES_CAUSE_RESET_DPSLP_FAULT_Pos    2UL
#define SRSS_RES_CAUSE_RESET_DPSLP_FAULT_Msk    0x4UL
#define SRSS_RES_CAUSE_RESET_TC_DBGRESET_Pos    3UL
#define SRSS_RES_CAUSE_RESET_TC_DBGRESET_Msk    0x8UL
#define SRSS_RES_CAUSE_RESET_SOFT_Pos           4UL
#define SRSS_RES_CAUSE_RESET_SOFT_Msk           0x10UL
#define SRSS_RES_CAUSE_RESET_MCWDT0_Pos         5UL
#define SRSS_RES_CAUSE_RESET_MCWDT0_Msk         0x20UL
#define SRSS_RES_CAUSE_RESET_MCWDT1_Pos         6UL
#define SRSS_RES_CAUSE_RESET_MCWDT1_Msk         0x40UL
#define SRSS_RES_CAUSE_RESET_MCWDT2_Pos         7UL
#define SRSS_RES_CAUSE_RESET_MCWDT2_Msk         0x80UL
#define SRSS_RES_CAUSE_RESET_MCWDT3_Pos         8UL
#define SRSS_RES_CAUSE_RESET_MCWDT3_Msk         0x100UL
/* SRSS.RES_CAUSE2 */
#define SRSS_RES_CAUSE2_RESET_CSV_HF_Pos        0UL
#define SRSS_RES_CAUSE2_RESET_CSV_HF_Msk        0xFFFFUL
#define SRSS_RES_CAUSE2_RESET_CSV_REF_Pos       16UL
#define SRSS_RES_CAUSE2_RESET_CSV_REF_Msk       0x10000UL
/* SRSS.RES_CAUSE_EXTEND */
#define SRSS_RES_CAUSE_EXTEND_RESET_XRES_Pos    16UL
#define SRSS_RES_CAUSE_EXTEND_RESET_XRES_Msk    0x10000UL
#define SRSS_RES_CAUSE_EXTEND_RESET_BODVDDD_Pos 17UL
#define SRSS_RES_CAUSE_EXTEND_RESET_BODVDDD_Msk 0x20000UL
#define SRSS_RES_CAUSE_EXTEND_RESET_BODVDDA_Pos 18UL
#define SRSS_RES_CAUSE_EXTEND_RESET_BODVDDA_Msk 0x40000UL
#define SRSS_RES_CAUSE_EXTEND_RESET_BODVCCD_Pos 19UL
#define SRSS_RES_CAUSE_EXTEND_RESET_BODVCCD_Msk 0x80000UL
#define SRSS_RES_CAUSE_EXTEND_RESET_OVDVDDD_Pos 20UL
#define SRSS_RES_CAUSE_EXTEND_RESET_OVDVDDD_Msk 0x100000UL
#define SRSS_RES_CAUSE_EXTEND_RESET_OVDVDDA_Pos 21UL
#define SRSS_RES_CAUSE_EXTEND_RESET_OVDVDDA_Msk 0x200000UL
#define SRSS_RES_CAUSE_EXTEND_RESET_OVDVCCD_Pos 22UL
#define SRSS_RES_CAUSE_EXTEND_RESET_OVDVCCD_Msk 0x400000UL
#define SRSS_RES_CAUSE_EXTEND_RESET_OCD_ACT_LINREG_Pos 23UL
#define SRSS_RES_CAUSE_EXTEND_RESET_OCD_ACT_LINREG_Msk 0x800000UL
#define SRSS_RES_CAUSE_EXTEND_RESET_OCD_DPSLP_LINREG_Pos 24UL
#define SRSS_RES_CAUSE_EXTEND_RESET_OCD_DPSLP_LINREG_Msk 0x1000000UL
#define SRSS_RES_CAUSE_EXTEND_RESET_OCD_REGHC_Pos 25UL
#define SRSS_RES_CAUSE_EXTEND_RESET_OCD_REGHC_Msk 0x2000000UL
#define SRSS_RES_CAUSE_EXTEND_RESET_PMIC_Pos    26UL
#define SRSS_RES_CAUSE_EXTEND_RESET_PMIC_Msk    0x4000000UL
#define SRSS_RES_CAUSE_EXTEND_RESET_PXRES_Pos   28UL
#define SRSS_RES_CAUSE_EXTEND_RESET_PXRES_Msk   0x10000000UL
#define SRSS_RES_CAUSE_EXTEND_RESET_STRUCT_XRES_Pos 29UL
#define SRSS_RES_CAUSE_EXTEND_RESET_STRUCT_XRES_Msk 0x20000000UL
#define SRSS_RES_CAUSE_EXTEND_RESET_PORVDDD_Pos 30UL
#define SRSS_RES_CAUSE_EXTEND_RESET_PORVDDD_Msk 0x40000000UL
/* SRSS.RES_PXRES_CTL */
#define SRSS_RES_PXRES_CTL_PXRES_TRIGGER_Pos    0UL
#define SRSS_RES_PXRES_CTL_PXRES_TRIGGER_Msk    0x1UL
/* SRSS.PWR_CBUCK_CTL */
#define SRSS_PWR_CBUCK_CTL_CBUCK_VSEL_Pos       0UL
#define SRSS_PWR_CBUCK_CTL_CBUCK_VSEL_Msk       0x1FUL
#define SRSS_PWR_CBUCK_CTL_CBUCK_MODE_Pos       8UL
#define SRSS_PWR_CBUCK_CTL_CBUCK_MODE_Msk       0x1F00UL
/* SRSS.PWR_CBUCK_CTL2 */
#define SRSS_PWR_CBUCK_CTL2_CBUCK_OVERRIDE_Pos  28UL
#define SRSS_PWR_CBUCK_CTL2_CBUCK_OVERRIDE_Msk  0x10000000UL
#define SRSS_PWR_CBUCK_CTL2_CBUCK_PAUSE_Pos     29UL
#define SRSS_PWR_CBUCK_CTL2_CBUCK_PAUSE_Msk     0x20000000UL
#define SRSS_PWR_CBUCK_CTL2_CBUCK_COPY_SETTINGS_Pos 30UL
#define SRSS_PWR_CBUCK_CTL2_CBUCK_COPY_SETTINGS_Msk 0x40000000UL
#define SRSS_PWR_CBUCK_CTL2_CBUCK_USE_SETTINGS_Pos 31UL
#define SRSS_PWR_CBUCK_CTL2_CBUCK_USE_SETTINGS_Msk 0x80000000UL
/* SRSS.PWR_CBUCK_CTL3 */
#define SRSS_PWR_CBUCK_CTL3_CBUCK_INRUSH_SEL_Pos 31UL
#define SRSS_PWR_CBUCK_CTL3_CBUCK_INRUSH_SEL_Msk 0x80000000UL
/* SRSS.PWR_CBUCK_STATUS */
#define SRSS_PWR_CBUCK_STATUS_PMU_DONE_Pos      31UL
#define SRSS_PWR_CBUCK_STATUS_PMU_DONE_Msk      0x80000000UL
/* SRSS.PWR_SDR0_CTL */
#define SRSS_PWR_SDR0_CTL_SDR0_CBUCK_VSEL_Pos   0UL
#define SRSS_PWR_SDR0_CTL_SDR0_CBUCK_VSEL_Msk   0x1FUL
#define SRSS_PWR_SDR0_CTL_SDR0_CBUCK_MODE_Pos   5UL
#define SRSS_PWR_SDR0_CTL_SDR0_CBUCK_MODE_Msk   0x3E0UL
#define SRSS_PWR_SDR0_CTL_SDR0_CBUCK_DPSLP_VSEL_Pos 10UL
#define SRSS_PWR_SDR0_CTL_SDR0_CBUCK_DPSLP_VSEL_Msk 0x7C00UL
#define SRSS_PWR_SDR0_CTL_SDR0_CBUCK_DPSLP_MODE_Pos 15UL
#define SRSS_PWR_SDR0_CTL_SDR0_CBUCK_DPSLP_MODE_Msk 0xF8000UL
#define SRSS_PWR_SDR0_CTL_SDR0_VSEL_Pos         20UL
#define SRSS_PWR_SDR0_CTL_SDR0_VSEL_Msk         0xF00000UL
#define SRSS_PWR_SDR0_CTL_SDR0_DPSLP_VSEL_Pos   26UL
#define SRSS_PWR_SDR0_CTL_SDR0_DPSLP_VSEL_Msk   0x3C000000UL
#define SRSS_PWR_SDR0_CTL_SDR0_ALLOW_BYPASS_Pos 31UL
#define SRSS_PWR_SDR0_CTL_SDR0_ALLOW_BYPASS_Msk 0x80000000UL
/* SRSS.PWR_SDR1_CTL */
#define SRSS_PWR_SDR1_CTL_SDR1_CBUCK_VSEL_Pos   0UL
#define SRSS_PWR_SDR1_CTL_SDR1_CBUCK_VSEL_Msk   0x1FUL
#define SRSS_PWR_SDR1_CTL_SDR1_CBUCK_MODE_Pos   8UL
#define SRSS_PWR_SDR1_CTL_SDR1_CBUCK_MODE_Msk   0x1F00UL
#define SRSS_PWR_SDR1_CTL_SDR1_VSEL_Pos         16UL
#define SRSS_PWR_SDR1_CTL_SDR1_VSEL_Msk         0xF0000UL
#define SRSS_PWR_SDR1_CTL_SDR1_HW_SEL_Pos       30UL
#define SRSS_PWR_SDR1_CTL_SDR1_HW_SEL_Msk       0x40000000UL
#define SRSS_PWR_SDR1_CTL_SDR1_ENABLE_Pos       31UL
#define SRSS_PWR_SDR1_CTL_SDR1_ENABLE_Msk       0x80000000UL
/* SRSS.PWR_HVLDO0_CTL */
#define SRSS_PWR_HVLDO0_CTL_HVLDO0_VSEL_Pos     0UL
#define SRSS_PWR_HVLDO0_CTL_HVLDO0_VSEL_Msk     0xFUL
#define SRSS_PWR_HVLDO0_CTL_HVLDO0_HW_SEL_Pos   30UL
#define SRSS_PWR_HVLDO0_CTL_HVLDO0_HW_SEL_Msk   0x40000000UL
#define SRSS_PWR_HVLDO0_CTL_HVLDO0_ENABLE_Pos   31UL
#define SRSS_PWR_HVLDO0_CTL_HVLDO0_ENABLE_Msk   0x80000000UL
/* SRSS.TST_XRES_SECURE */
#define SRSS_TST_XRES_SECURE_DATA8_Pos          0UL
#define SRSS_TST_XRES_SECURE_DATA8_Msk          0xFFUL
#define SRSS_TST_XRES_SECURE_FW_WR_Pos          8UL
#define SRSS_TST_XRES_SECURE_FW_WR_Msk          0xF00UL
#define SRSS_TST_XRES_SECURE_SECURE_WR_Pos      16UL
#define SRSS_TST_XRES_SECURE_SECURE_WR_Msk      0xF0000UL
#define SRSS_TST_XRES_SECURE_FW_KEY_OK_Pos      29UL
#define SRSS_TST_XRES_SECURE_FW_KEY_OK_Msk      0x20000000UL
#define SRSS_TST_XRES_SECURE_SECURE_KEY_OK_Pos  30UL
#define SRSS_TST_XRES_SECURE_SECURE_KEY_OK_Msk  0x40000000UL
#define SRSS_TST_XRES_SECURE_SECURE_DISABLE_Pos 31UL
#define SRSS_TST_XRES_SECURE_SECURE_DISABLE_Msk 0x80000000UL
/* SRSS.PWR_TRIM_CBUCK_CTL */
#define SRSS_PWR_TRIM_CBUCK_CTL_CBUCK_DPSLP_VSEL_Pos 0UL
#define SRSS_PWR_TRIM_CBUCK_CTL_CBUCK_DPSLP_VSEL_Msk 0x1FUL
#define SRSS_PWR_TRIM_CBUCK_CTL_CBUCK_DPSLP_MODE_Pos 8UL
#define SRSS_PWR_TRIM_CBUCK_CTL_CBUCK_DPSLP_MODE_Msk 0x1F00UL
/* SRSS.CLK_TRIM_ECO_CTL */
#define SRSS_CLK_TRIM_ECO_CTL_ITRIM_Pos         16UL
#define SRSS_CLK_TRIM_ECO_CTL_ITRIM_Msk         0x3F0000UL
/* SRSS.CLK_TRIM_ILO1_CTL */
#define SRSS_CLK_TRIM_ILO1_CTL_ILO1_FTRIM_Pos   0UL
#define SRSS_CLK_TRIM_ILO1_CTL_ILO1_FTRIM_Msk   0x3FUL
#define SRSS_CLK_TRIM_ILO1_CTL_ILO1_MONTRIM_Pos 8UL
#define SRSS_CLK_TRIM_ILO1_CTL_ILO1_MONTRIM_Msk 0xF00UL
/* SRSS.WDT_CTL */
#define SRSS_WDT_CTL_WDT_EN_Pos                 0UL
#define SRSS_WDT_CTL_WDT_EN_Msk                 0x1UL
#define SRSS_WDT_CTL_WDT_CLK_SEL_Pos            4UL
#define SRSS_WDT_CTL_WDT_CLK_SEL_Msk            0x30UL
#define SRSS_WDT_CTL_WDT_LOCK_Pos               30UL
#define SRSS_WDT_CTL_WDT_LOCK_Msk               0xC0000000UL
/* SRSS.WDT_CNT */
#define SRSS_WDT_CNT_COUNTER_Pos                0UL
#define SRSS_WDT_CNT_COUNTER_Msk                0xFFFFFFFFUL
/* SRSS.WDT_MATCH */
#define SRSS_WDT_MATCH_MATCH_Pos                0UL
#define SRSS_WDT_MATCH_MATCH_Msk                0xFFFFFFFFUL
/* SRSS.WDT_MATCH2 */
#define SRSS_WDT_MATCH2_IGNORE_BITS_ABOVE_Pos   0UL
#define SRSS_WDT_MATCH2_IGNORE_BITS_ABOVE_Msk   0x1FUL


#endif /* _CYIP_SRSS_H_ */


/* [] END OF FILE */
