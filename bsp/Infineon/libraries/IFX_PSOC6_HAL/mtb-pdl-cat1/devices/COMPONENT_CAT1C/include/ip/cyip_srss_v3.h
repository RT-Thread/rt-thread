/***************************************************************************//**
* \file cyip_srss_v3.h
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

#ifndef _CYIP_SRSS_V3_H_
#define _CYIP_SRSS_V3_H_

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
#define MCWDT_CTR_SECTION_SIZE                  0x00000020UL
#define MCWDT_SECTION_SIZE                      0x00000100UL
#define WDT_SECTION_SIZE                        0x00000080UL
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
  * \brief ILO0 clock DeepSleep domain Clock Supervisor registers (CSV_ILO_CSV)
  */
typedef struct {
  __IOM uint32_t REF_CTL;                       /*!< 0x00000000 Clock Supervision Reference Control */
  __IOM uint32_t REF_LIMIT;                     /*!< 0x00000004 Clock Supervision Reference Limits */
  __IOM uint32_t MON_CTL;                       /*!< 0x00000008 Clock Supervision Monitor Control */
   __IM uint32_t RESERVED;
} CSV_ILO_CSV_Type;                             /*!< Size = 16 (0x10) */

/**
  * \brief CSV registers for HVILO clock (CSV_ILO)
  */
typedef struct {
        CSV_ILO_CSV_Type CSV;                   /*!< 0x00000000 ILO0 clock DeepSleep domain Clock Supervisor registers */
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
  * \brief MCWDT Configuration for Subcounter 0 and 1 (MCWDT_CTR)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 MCWDT Subcounter Control Register */
  __IOM uint32_t LOWER_LIMIT;                   /*!< 0x00000004 MCWDT Subcounter Lower Limit Register */
  __IOM uint32_t UPPER_LIMIT;                   /*!< 0x00000008 MCWDT Subcounter Upper Limit Register */
  __IOM uint32_t WARN_LIMIT;                    /*!< 0x0000000C MCWDT Subcounter Warn Limit Register */
  __IOM uint32_t CONFIG;                        /*!< 0x00000010 MCWDT Subcounter Configuration Register */
  __IOM uint32_t CNT;                           /*!< 0x00000014 MCWDT Subcounter Count Register */
   __IM uint32_t RESERVED[2];
} MCWDT_CTR_Type;                               /*!< Size = 32 (0x20) */

/**
  * \brief Multi-Counter Watchdog Timer (MCWDT)
  */
typedef struct {
        MCWDT_CTR_Type CTR[2];                  /*!< 0x00000000 MCWDT Configuration for Subcounter 0 and 1 */
  __IOM uint32_t CPU_SELECT;                    /*!< 0x00000040 MCWDT CPU selection register */
   __IM uint32_t RESERVED[15];
  __IOM uint32_t CTR2_CTL;                      /*!< 0x00000080 MCWDT Subcounter 2 Control register */
  __IOM uint32_t CTR2_CONFIG;                   /*!< 0x00000084 MCWDT Subcounter 2 Configuration register */
  __IOM uint32_t CTR2_CNT;                      /*!< 0x00000088 MCWDT Subcounter 2 Count Register */
   __IM uint32_t RESERVED1;
  __IOM uint32_t LOCK;                          /*!< 0x00000090 MCWDT Lock Register */
  __IOM uint32_t SERVICE;                       /*!< 0x00000094 MCWDT Service Register */
   __IM uint32_t RESERVED2[2];
  __IOM uint32_t INTR;                          /*!< 0x000000A0 MCWDT Interrupt Register */
  __IOM uint32_t INTR_SET;                      /*!< 0x000000A4 MCWDT Interrupt Set Register */
  __IOM uint32_t INTR_MASK;                     /*!< 0x000000A8 MCWDT Interrupt Mask Register */
   __IM uint32_t INTR_MASKED;                   /*!< 0x000000AC MCWDT Interrupt Masked Register */
   __IM uint32_t RESERVED3[20];
} MCWDT_Type;                                   /*!< Size = 256 (0x100) */

/**
  * \brief Watchdog Timer (WDT)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 WDT Control Register */
  __IOM uint32_t LOWER_LIMIT;                   /*!< 0x00000004 WDT Lower Limit Register */
  __IOM uint32_t UPPER_LIMIT;                   /*!< 0x00000008 WDT Upper Limit Register */
  __IOM uint32_t WARN_LIMIT;                    /*!< 0x0000000C WDT Warn Limit Register */
  __IOM uint32_t CONFIG;                        /*!< 0x00000010 WDT Configuration Register */
  __IOM uint32_t CNT;                           /*!< 0x00000014 WDT Count Register */
   __IM uint32_t RESERVED[10];
  __IOM uint32_t LOCK;                          /*!< 0x00000040 WDT Lock register */
  __IOM uint32_t SERVICE;                       /*!< 0x00000044 WDT Service register */
   __IM uint32_t RESERVED1[2];
  __IOM uint32_t INTR;                          /*!< 0x00000050 WDT Interrupt Register */
  __IOM uint32_t INTR_SET;                      /*!< 0x00000054 WDT Interrupt Set Register */
  __IOM uint32_t INTR_MASK;                     /*!< 0x00000058 WDT Interrupt Mask Register */
   __IM uint32_t INTR_MASKED;                   /*!< 0x0000005C WDT Interrupt Masked Register */
   __IM uint32_t RESERVED2[8];
} WDT_Type;                                     /*!< Size = 128 (0x80) */

/**
  * \brief SRSS Core Registers (ver3) (SRSS)
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
   __IM uint32_t RESERVED3[892];
   __IM uint32_t PWR_CTL;                       /*!< 0x00001000 Power Mode Control */
  __IOM uint32_t PWR_CTL2;                      /*!< 0x00001004 Power Mode Control 2 */
  __IOM uint32_t PWR_HIBERNATE;                 /*!< 0x00001008 HIBERNATE Mode Register */
   __IM uint32_t RESERVED4;
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
   __IM uint32_t RESERVED5;
  __IOM uint32_t PWR_REGHC_CTL4;                /*!< 0x00001038 REGHC Control Register 4 */
   __IM uint32_t RESERVED6;
  __IOM uint32_t PWR_HIB_DATA[16];              /*!< 0x00001040 HIBERNATE Data Register */
   __IM uint32_t RESERVED7[16];
  __IOM uint32_t PWR_PMIC_CTL;                  /*!< 0x000010C0 PMIC Control Register */
   __IM uint32_t PWR_PMIC_STATUS;               /*!< 0x000010C4 PMIC Status Register */
  __IOM uint32_t PWR_PMIC_CTL2;                 /*!< 0x000010C8 PMIC Control Register 2 */
   __IM uint32_t RESERVED8;
  __IOM uint32_t PWR_PMIC_CTL4;                 /*!< 0x000010D0 PMIC Control Register 4 */
   __IM uint32_t RESERVED9[75];
  __IOM uint32_t CLK_PATH_SELECT[16];           /*!< 0x00001200 Clock Path Select Register */
  __IOM uint32_t CLK_ROOT_SELECT[16];           /*!< 0x00001240 Clock Root Select Register */
   __IM uint32_t RESERVED10[96];
        CSV_HF_Type CSV_HF;                     /*!< 0x00001400 Clock Supervisor (CSV) registers for Root clocks */
  __IOM uint32_t CLK_SELECT;                    /*!< 0x00001500 Clock selection register */
  __IOM uint32_t CLK_TIMER_CTL;                 /*!< 0x00001504 Timer Clock Control Register */
  __IOM uint32_t CLK_ILO0_CONFIG;               /*!< 0x00001508 ILO0 Configuration */
  __IOM uint32_t CLK_ILO1_CONFIG;               /*!< 0x0000150C ILO1 Configuration */
   __IM uint32_t RESERVED11[2];
  __IOM uint32_t CLK_IMO_CONFIG;                /*!< 0x00001518 IMO Configuration */
  __IOM uint32_t CLK_ECO_CONFIG;                /*!< 0x0000151C ECO Configuration Register */
  __IOM uint32_t CLK_ECO_PRESCALE;              /*!< 0x00001520 ECO Prescaler Configuration Register */
   __IM uint32_t CLK_ECO_STATUS;                /*!< 0x00001524 ECO Status Register */
  __IOM uint32_t CLK_PILO_CONFIG;               /*!< 0x00001528 Precision ILO Configuration Register */
   __IM uint32_t RESERVED12;
  __IOM uint32_t CLK_FLL_CONFIG;                /*!< 0x00001530 FLL Configuration Register */
  __IOM uint32_t CLK_FLL_CONFIG2;               /*!< 0x00001534 FLL Configuration Register 2 */
  __IOM uint32_t CLK_FLL_CONFIG3;               /*!< 0x00001538 FLL Configuration Register 3 */
  __IOM uint32_t CLK_FLL_CONFIG4;               /*!< 0x0000153C FLL Configuration Register 4 */
  __IOM uint32_t CLK_FLL_STATUS;                /*!< 0x00001540 FLL Status Register */
  __IOM uint32_t CLK_ECO_CONFIG2;               /*!< 0x00001544 ECO Configuration Register 2 */
   __IM uint32_t RESERVED13[46];
  __IOM uint32_t CLK_PLL_CONFIG[15];            /*!< 0x00001600 PLL Configuration Register */
   __IM uint32_t RESERVED14;
  __IOM uint32_t CLK_PLL_STATUS[15];            /*!< 0x00001640 PLL Status Register */
   __IM uint32_t RESERVED15[33];
  __IOM uint32_t CSV_REF_SEL;                   /*!< 0x00001700 Select CSV Reference clock for Active domain */
   __IM uint32_t RESERVED16[3];
        CSV_REF_Type CSV_REF;                   /*!< 0x00001710 CSV registers for the CSV Reference clock */
        CSV_LF_Type CSV_LF;                     /*!< 0x00001720 CSV registers for LF clock */
        CSV_ILO_Type CSV_ILO;                   /*!< 0x00001730 CSV registers for HVILO clock */
   __IM uint32_t RESERVED17[48];
  __IOM uint32_t RES_CAUSE;                     /*!< 0x00001800 Reset Cause Observation Register */
  __IOM uint32_t RES_CAUSE2;                    /*!< 0x00001804 Reset Cause Observation Register 2 */
   __IM uint32_t RESERVED18[62];
        CLK_PLL400M_Type CLK_PLL400M[15];       /*!< 0x00001900 400MHz PLL Configuration Register */
   __IM uint32_t RESERVED19[1417];
  __IOM uint32_t CLK_TRIM_ILO0_CTL;             /*!< 0x00003014 ILO0 Trim Register */
   __IM uint32_t RESERVED20[60];
  __IOM uint32_t PWR_TRIM_PWRSYS_CTL;           /*!< 0x00003108 Power System Trim Register */
   __IM uint32_t RESERVED21[2];
  __IOM uint32_t CLK_TRIM_PILO_CTL;             /*!< 0x00003114 PILO Trim Register */
  __IOM uint32_t CLK_TRIM_PILO_CTL2;            /*!< 0x00003118 PILO Trim Register 2 */
  __IOM uint32_t CLK_TRIM_PILO_CTL3;            /*!< 0x0000311C PILO Trim Register 3 */
   __IM uint32_t RESERVED22[64];
  __IOM uint32_t CLK_TRIM_ILO1_CTL;             /*!< 0x00003220 ILO1 Trim Register */
   __IM uint32_t RESERVED23[4983];
        MCWDT_Type MCWDT[4];                    /*!< 0x00008000 Multi-Counter Watchdog Timer */
   __IM uint32_t RESERVED24[3840];
        WDT_Type WDT_STRUCT;                    /*!< 0x0000C000 Watchdog Timer */
} SRSS_Type;                                    /*!< Size = 49280 (0xC080) */


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


/* MCWDT_CTR.CTL */
#define MCWDT_CTR_CTL_ENABLED_Pos               0UL
#define MCWDT_CTR_CTL_ENABLED_Msk               0x1UL
#define MCWDT_CTR_CTL_ENABLE_Pos                31UL
#define MCWDT_CTR_CTL_ENABLE_Msk                0x80000000UL
/* MCWDT_CTR.LOWER_LIMIT */
#define MCWDT_CTR_LOWER_LIMIT_LOWER_LIMIT_Pos   0UL
#define MCWDT_CTR_LOWER_LIMIT_LOWER_LIMIT_Msk   0xFFFFUL
/* MCWDT_CTR.UPPER_LIMIT */
#define MCWDT_CTR_UPPER_LIMIT_UPPER_LIMIT_Pos   0UL
#define MCWDT_CTR_UPPER_LIMIT_UPPER_LIMIT_Msk   0xFFFFUL
/* MCWDT_CTR.WARN_LIMIT */
#define MCWDT_CTR_WARN_LIMIT_WARN_LIMIT_Pos     0UL
#define MCWDT_CTR_WARN_LIMIT_WARN_LIMIT_Msk     0xFFFFUL
/* MCWDT_CTR.CONFIG */
#define MCWDT_CTR_CONFIG_LOWER_ACTION_Pos       0UL
#define MCWDT_CTR_CONFIG_LOWER_ACTION_Msk       0x3UL
#define MCWDT_CTR_CONFIG_UPPER_ACTION_Pos       4UL
#define MCWDT_CTR_CONFIG_UPPER_ACTION_Msk       0x30UL
#define MCWDT_CTR_CONFIG_WARN_ACTION_Pos        8UL
#define MCWDT_CTR_CONFIG_WARN_ACTION_Msk        0x100UL
#define MCWDT_CTR_CONFIG_AUTO_SERVICE_Pos       12UL
#define MCWDT_CTR_CONFIG_AUTO_SERVICE_Msk       0x1000UL
#define MCWDT_CTR_CONFIG_DEBUG_TRIGGER_EN_Pos   28UL
#define MCWDT_CTR_CONFIG_DEBUG_TRIGGER_EN_Msk   0x10000000UL
#define MCWDT_CTR_CONFIG_SLEEPDEEP_PAUSE_Pos    30UL
#define MCWDT_CTR_CONFIG_SLEEPDEEP_PAUSE_Msk    0x40000000UL
#define MCWDT_CTR_CONFIG_DEBUG_RUN_Pos          31UL
#define MCWDT_CTR_CONFIG_DEBUG_RUN_Msk          0x80000000UL
/* MCWDT_CTR.CNT */
#define MCWDT_CTR_CNT_CNT_Pos                   0UL
#define MCWDT_CTR_CNT_CNT_Msk                   0xFFFFUL


/* MCWDT.CPU_SELECT */
#define MCWDT_CPU_SELECT_CPU_SEL_Pos            0UL
#define MCWDT_CPU_SELECT_CPU_SEL_Msk            0x3UL
/* MCWDT.CTR2_CTL */
#define MCWDT_CTR2_CTL_ENABLED_Pos              0UL
#define MCWDT_CTR2_CTL_ENABLED_Msk              0x1UL
#define MCWDT_CTR2_CTL_ENABLE_Pos               31UL
#define MCWDT_CTR2_CTL_ENABLE_Msk               0x80000000UL
/* MCWDT.CTR2_CONFIG */
#define MCWDT_CTR2_CONFIG_ACTION_Pos            0UL
#define MCWDT_CTR2_CONFIG_ACTION_Msk            0x1UL
#define MCWDT_CTR2_CONFIG_BITS_Pos              16UL
#define MCWDT_CTR2_CONFIG_BITS_Msk              0x1F0000UL
#define MCWDT_CTR2_CONFIG_DEBUG_TRIGGER_EN_Pos  28UL
#define MCWDT_CTR2_CONFIG_DEBUG_TRIGGER_EN_Msk  0x10000000UL
#define MCWDT_CTR2_CONFIG_SLEEPDEEP_PAUSE_Pos   30UL
#define MCWDT_CTR2_CONFIG_SLEEPDEEP_PAUSE_Msk   0x40000000UL
#define MCWDT_CTR2_CONFIG_DEBUG_RUN_Pos         31UL
#define MCWDT_CTR2_CONFIG_DEBUG_RUN_Msk         0x80000000UL
/* MCWDT.CTR2_CNT */
#define MCWDT_CTR2_CNT_CNT2_Pos                 0UL
#define MCWDT_CTR2_CNT_CNT2_Msk                 0xFFFFFFFFUL
/* MCWDT.LOCK */
#define MCWDT_LOCK_MCWDT_LOCK_Pos               0UL
#define MCWDT_LOCK_MCWDT_LOCK_Msk               0x3UL
/* MCWDT.SERVICE */
#define MCWDT_SERVICE_CTR0_SERVICE_Pos          0UL
#define MCWDT_SERVICE_CTR0_SERVICE_Msk          0x1UL
#define MCWDT_SERVICE_CTR1_SERVICE_Pos          1UL
#define MCWDT_SERVICE_CTR1_SERVICE_Msk          0x2UL
/* MCWDT.INTR */
#define MCWDT_INTR_CTR0_INT_Pos                 0UL
#define MCWDT_INTR_CTR0_INT_Msk                 0x1UL
#define MCWDT_INTR_CTR1_INT_Pos                 1UL
#define MCWDT_INTR_CTR1_INT_Msk                 0x2UL
#define MCWDT_INTR_CTR2_INT_Pos                 2UL
#define MCWDT_INTR_CTR2_INT_Msk                 0x4UL
/* MCWDT.INTR_SET */
#define MCWDT_INTR_SET_CTR0_INT_Pos             0UL
#define MCWDT_INTR_SET_CTR0_INT_Msk             0x1UL
#define MCWDT_INTR_SET_CTR1_INT_Pos             1UL
#define MCWDT_INTR_SET_CTR1_INT_Msk             0x2UL
#define MCWDT_INTR_SET_CTR2_INT_Pos             2UL
#define MCWDT_INTR_SET_CTR2_INT_Msk             0x4UL
/* MCWDT.INTR_MASK */
#define MCWDT_INTR_MASK_CTR0_INT_Pos            0UL
#define MCWDT_INTR_MASK_CTR0_INT_Msk            0x1UL
#define MCWDT_INTR_MASK_CTR1_INT_Pos            1UL
#define MCWDT_INTR_MASK_CTR1_INT_Msk            0x2UL
#define MCWDT_INTR_MASK_CTR2_INT_Pos            2UL
#define MCWDT_INTR_MASK_CTR2_INT_Msk            0x4UL
/* MCWDT.INTR_MASKED */
#define MCWDT_INTR_MASKED_CTR0_INT_Pos          0UL
#define MCWDT_INTR_MASKED_CTR0_INT_Msk          0x1UL
#define MCWDT_INTR_MASKED_CTR1_INT_Pos          1UL
#define MCWDT_INTR_MASKED_CTR1_INT_Msk          0x2UL
#define MCWDT_INTR_MASKED_CTR2_INT_Pos          2UL
#define MCWDT_INTR_MASKED_CTR2_INT_Msk          0x4UL


/* WDT.CTL */
#define WDT_CTL_ENABLED_Pos                     0UL
#define WDT_CTL_ENABLED_Msk                     0x1UL
#define WDT_CTL_ENABLE_Pos                      31UL
#define WDT_CTL_ENABLE_Msk                      0x80000000UL
/* WDT.LOWER_LIMIT */
#define WDT_LOWER_LIMIT_LOWER_LIMIT_Pos         0UL
#define WDT_LOWER_LIMIT_LOWER_LIMIT_Msk         0xFFFFFFFFUL
/* WDT.UPPER_LIMIT */
#define WDT_UPPER_LIMIT_UPPER_LIMIT_Pos         0UL
#define WDT_UPPER_LIMIT_UPPER_LIMIT_Msk         0xFFFFFFFFUL
/* WDT.WARN_LIMIT */
#define WDT_WARN_LIMIT_WARN_LIMIT_Pos           0UL
#define WDT_WARN_LIMIT_WARN_LIMIT_Msk           0xFFFFFFFFUL
/* WDT.CONFIG */
#define WDT_CONFIG_LOWER_ACTION_Pos             0UL
#define WDT_CONFIG_LOWER_ACTION_Msk             0x1UL
#define WDT_CONFIG_UPPER_ACTION_Pos             4UL
#define WDT_CONFIG_UPPER_ACTION_Msk             0x10UL
#define WDT_CONFIG_WARN_ACTION_Pos              8UL
#define WDT_CONFIG_WARN_ACTION_Msk              0x100UL
#define WDT_CONFIG_AUTO_SERVICE_Pos             12UL
#define WDT_CONFIG_AUTO_SERVICE_Msk             0x1000UL
#define WDT_CONFIG_DEBUG_TRIGGER_EN_Pos         28UL
#define WDT_CONFIG_DEBUG_TRIGGER_EN_Msk         0x10000000UL
#define WDT_CONFIG_DPSLP_PAUSE_Pos              29UL
#define WDT_CONFIG_DPSLP_PAUSE_Msk              0x20000000UL
#define WDT_CONFIG_HIB_PAUSE_Pos                30UL
#define WDT_CONFIG_HIB_PAUSE_Msk                0x40000000UL
#define WDT_CONFIG_DEBUG_RUN_Pos                31UL
#define WDT_CONFIG_DEBUG_RUN_Msk                0x80000000UL
/* WDT.CNT */
#define WDT_CNT_CNT_Pos                         0UL
#define WDT_CNT_CNT_Msk                         0xFFFFFFFFUL
/* WDT.LOCK */
#define WDT_LOCK_WDT_LOCK_Pos                   0UL
#define WDT_LOCK_WDT_LOCK_Msk                   0x3UL
/* WDT.SERVICE */
#define WDT_SERVICE_SERVICE_Pos                 0UL
#define WDT_SERVICE_SERVICE_Msk                 0x1UL
/* WDT.INTR */
#define WDT_INTR_WDT_Pos                        0UL
#define WDT_INTR_WDT_Msk                        0x1UL
/* WDT.INTR_SET */
#define WDT_INTR_SET_WDT_Pos                    0UL
#define WDT_INTR_SET_WDT_Msk                    0x1UL
/* WDT.INTR_MASK */
#define WDT_INTR_MASK_WDT_Pos                   0UL
#define WDT_INTR_MASK_WDT_Msk                   0x1UL
/* WDT.INTR_MASKED */
#define WDT_INTR_MASKED_WDT_Pos                 0UL
#define WDT_INTR_MASKED_WDT_Msk                 0x1UL


/* SRSS.PWR_LVD_STATUS */
#define SRSS_PWR_LVD_STATUS_HVLVD1_OUT_Pos      0UL
#define SRSS_PWR_LVD_STATUS_HVLVD1_OUT_Msk      0x1UL
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
#define SRSS_CLK_CAL_CNT1_CAL_COUNTER_DONE_Pos  31UL
#define SRSS_CLK_CAL_CNT1_CAL_COUNTER_DONE_Msk  0x80000000UL
/* SRSS.CLK_CAL_CNT2 */
#define SRSS_CLK_CAL_CNT2_CAL_COUNTER2_Pos      0UL
#define SRSS_CLK_CAL_CNT2_CAL_COUNTER2_Msk      0xFFFFFFUL
/* SRSS.SRSS_INTR */
#define SRSS_SRSS_INTR_HVLVD1_Pos               1UL
#define SRSS_SRSS_INTR_HVLVD1_Msk               0x2UL
#define SRSS_SRSS_INTR_HVLVD2_Pos               2UL
#define SRSS_SRSS_INTR_HVLVD2_Msk               0x4UL
#define SRSS_SRSS_INTR_CLK_CAL_Pos              5UL
#define SRSS_SRSS_INTR_CLK_CAL_Msk              0x20UL
/* SRSS.SRSS_INTR_SET */
#define SRSS_SRSS_INTR_SET_HVLVD1_Pos           1UL
#define SRSS_SRSS_INTR_SET_HVLVD1_Msk           0x2UL
#define SRSS_SRSS_INTR_SET_HVLVD2_Pos           2UL
#define SRSS_SRSS_INTR_SET_HVLVD2_Msk           0x4UL
#define SRSS_SRSS_INTR_SET_CLK_CAL_Pos          5UL
#define SRSS_SRSS_INTR_SET_CLK_CAL_Msk          0x20UL
/* SRSS.SRSS_INTR_MASK */
#define SRSS_SRSS_INTR_MASK_HVLVD1_Pos          1UL
#define SRSS_SRSS_INTR_MASK_HVLVD1_Msk          0x2UL
#define SRSS_SRSS_INTR_MASK_HVLVD2_Pos          2UL
#define SRSS_SRSS_INTR_MASK_HVLVD2_Msk          0x4UL
#define SRSS_SRSS_INTR_MASK_CLK_CAL_Pos         5UL
#define SRSS_SRSS_INTR_MASK_CLK_CAL_Msk         0x20UL
/* SRSS.SRSS_INTR_MASKED */
#define SRSS_SRSS_INTR_MASKED_HVLVD1_Pos        1UL
#define SRSS_SRSS_INTR_MASKED_HVLVD1_Msk        0x2UL
#define SRSS_SRSS_INTR_MASKED_HVLVD2_Pos        2UL
#define SRSS_SRSS_INTR_MASKED_HVLVD2_Msk        0x4UL
#define SRSS_SRSS_INTR_MASKED_CLK_CAL_Pos       5UL
#define SRSS_SRSS_INTR_MASKED_CLK_CAL_Msk       0x20UL
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
#define SRSS_PWR_CTL2_REFVBUF_LPMODE_Pos        22UL
#define SRSS_PWR_CTL2_REFVBUF_LPMODE_Msk        0x400000UL
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
/* SRSS.PWR_REGHC_CTL4 */
#define SRSS_PWR_REGHC_CTL4_REGHC_PMIC_VADJ_DIS_Pos 30UL
#define SRSS_PWR_REGHC_CTL4_REGHC_PMIC_VADJ_DIS_Msk 0x40000000UL
#define SRSS_PWR_REGHC_CTL4_REGHC_PMIC_DPSLP_Pos 31UL
#define SRSS_PWR_REGHC_CTL4_REGHC_PMIC_DPSLP_Msk 0x80000000UL
/* SRSS.PWR_HIB_DATA */
#define SRSS_PWR_HIB_DATA_HIB_DATA_Pos          0UL
#define SRSS_PWR_HIB_DATA_HIB_DATA_Msk          0xFFFFFFFFUL
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
/* SRSS.CLK_SELECT */
#define SRSS_CLK_SELECT_LFCLK_SEL_Pos           0UL
#define SRSS_CLK_SELECT_LFCLK_SEL_Msk           0x7UL
#define SRSS_CLK_SELECT_PUMP_SEL_Pos            8UL
#define SRSS_CLK_SELECT_PUMP_SEL_Msk            0xF00UL
#define SRSS_CLK_SELECT_PUMP_DIV_Pos            12UL
#define SRSS_CLK_SELECT_PUMP_DIV_Msk            0x7000UL
#define SRSS_CLK_SELECT_PUMP_ENABLE_Pos         15UL
#define SRSS_CLK_SELECT_PUMP_ENABLE_Msk         0x8000UL
/* SRSS.CLK_TIMER_CTL */
#define SRSS_CLK_TIMER_CTL_TIMER_SEL_Pos        0UL
#define SRSS_CLK_TIMER_CTL_TIMER_SEL_Msk        0x1UL
#define SRSS_CLK_TIMER_CTL_TIMER_HF0_DIV_Pos    8UL
#define SRSS_CLK_TIMER_CTL_TIMER_HF0_DIV_Msk    0x300UL
#define SRSS_CLK_TIMER_CTL_TIMER_DIV_Pos        16UL
#define SRSS_CLK_TIMER_CTL_TIMER_DIV_Msk        0xFF0000UL
#define SRSS_CLK_TIMER_CTL_ENABLE_Pos           31UL
#define SRSS_CLK_TIMER_CTL_ENABLE_Msk           0x80000000UL
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
#define SRSS_CLK_PILO_CONFIG_PILO_FFREQ_Pos     0UL
#define SRSS_CLK_PILO_CONFIG_PILO_FFREQ_Msk     0x3FFUL
#define SRSS_CLK_PILO_CONFIG_PILO_CLK_EN_Pos    29UL
#define SRSS_CLK_PILO_CONFIG_PILO_CLK_EN_Msk    0x20000000UL
#define SRSS_CLK_PILO_CONFIG_PILO_RESET_N_Pos   30UL
#define SRSS_CLK_PILO_CONFIG_PILO_RESET_N_Msk   0x40000000UL
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
#define SRSS_RES_CAUSE_RESET_XRES_Pos           16UL
#define SRSS_RES_CAUSE_RESET_XRES_Msk           0x10000UL
#define SRSS_RES_CAUSE_RESET_BODVDDD_Pos        17UL
#define SRSS_RES_CAUSE_RESET_BODVDDD_Msk        0x20000UL
#define SRSS_RES_CAUSE_RESET_BODVDDA_Pos        18UL
#define SRSS_RES_CAUSE_RESET_BODVDDA_Msk        0x40000UL
#define SRSS_RES_CAUSE_RESET_BODVCCD_Pos        19UL
#define SRSS_RES_CAUSE_RESET_BODVCCD_Msk        0x80000UL
#define SRSS_RES_CAUSE_RESET_OVDVDDD_Pos        20UL
#define SRSS_RES_CAUSE_RESET_OVDVDDD_Msk        0x100000UL
#define SRSS_RES_CAUSE_RESET_OVDVDDA_Pos        21UL
#define SRSS_RES_CAUSE_RESET_OVDVDDA_Msk        0x200000UL
#define SRSS_RES_CAUSE_RESET_OVDVCCD_Pos        22UL
#define SRSS_RES_CAUSE_RESET_OVDVCCD_Msk        0x400000UL
#define SRSS_RES_CAUSE_RESET_OCD_ACT_LINREG_Pos 23UL
#define SRSS_RES_CAUSE_RESET_OCD_ACT_LINREG_Msk 0x800000UL
#define SRSS_RES_CAUSE_RESET_OCD_DPSLP_LINREG_Pos 24UL
#define SRSS_RES_CAUSE_RESET_OCD_DPSLP_LINREG_Msk 0x1000000UL
#define SRSS_RES_CAUSE_RESET_OCD_REGHC_Pos      25UL
#define SRSS_RES_CAUSE_RESET_OCD_REGHC_Msk      0x2000000UL
#define SRSS_RES_CAUSE_RESET_PMIC_Pos           26UL
#define SRSS_RES_CAUSE_RESET_PMIC_Msk           0x4000000UL
#define SRSS_RES_CAUSE_RESET_PXRES_Pos          28UL
#define SRSS_RES_CAUSE_RESET_PXRES_Msk          0x10000000UL
#define SRSS_RES_CAUSE_RESET_STRUCT_XRES_Pos    29UL
#define SRSS_RES_CAUSE_RESET_STRUCT_XRES_Msk    0x20000000UL
#define SRSS_RES_CAUSE_RESET_PORVDDD_Pos        30UL
#define SRSS_RES_CAUSE_RESET_PORVDDD_Msk        0x40000000UL
/* SRSS.RES_CAUSE2 */
#define SRSS_RES_CAUSE2_RESET_CSV_HF_Pos        0UL
#define SRSS_RES_CAUSE2_RESET_CSV_HF_Msk        0xFFFFUL
#define SRSS_RES_CAUSE2_RESET_CSV_REF_Pos       16UL
#define SRSS_RES_CAUSE2_RESET_CSV_REF_Msk       0x10000UL
/* SRSS.CLK_TRIM_ILO0_CTL */
#define SRSS_CLK_TRIM_ILO0_CTL_ILO0_FTRIM_Pos   0UL
#define SRSS_CLK_TRIM_ILO0_CTL_ILO0_FTRIM_Msk   0x3FUL
#define SRSS_CLK_TRIM_ILO0_CTL_ILO0_MONTRIM_Pos 8UL
#define SRSS_CLK_TRIM_ILO0_CTL_ILO0_MONTRIM_Msk 0xF00UL
/* SRSS.PWR_TRIM_PWRSYS_CTL */
#define SRSS_PWR_TRIM_PWRSYS_CTL_ACT_REG_TRIM_Pos 0UL
#define SRSS_PWR_TRIM_PWRSYS_CTL_ACT_REG_TRIM_Msk 0x1FUL
#define SRSS_PWR_TRIM_PWRSYS_CTL_ACT_REG_BOOST_Pos 30UL
#define SRSS_PWR_TRIM_PWRSYS_CTL_ACT_REG_BOOST_Msk 0xC0000000UL
/* SRSS.CLK_TRIM_PILO_CTL */
#define SRSS_CLK_TRIM_PILO_CTL_PILO_CFREQ_Pos   0UL
#define SRSS_CLK_TRIM_PILO_CTL_PILO_CFREQ_Msk   0x3FUL
#define SRSS_CLK_TRIM_PILO_CTL_PILO_OSC_TRIM_Pos 12UL
#define SRSS_CLK_TRIM_PILO_CTL_PILO_OSC_TRIM_Msk 0x7000UL
#define SRSS_CLK_TRIM_PILO_CTL_PILO_COMP_TRIM_Pos 16UL
#define SRSS_CLK_TRIM_PILO_CTL_PILO_COMP_TRIM_Msk 0x30000UL
#define SRSS_CLK_TRIM_PILO_CTL_PILO_NBIAS_TRIM_Pos 18UL
#define SRSS_CLK_TRIM_PILO_CTL_PILO_NBIAS_TRIM_Msk 0xC0000UL
#define SRSS_CLK_TRIM_PILO_CTL_PILO_RES_TRIM_Pos 20UL
#define SRSS_CLK_TRIM_PILO_CTL_PILO_RES_TRIM_Msk 0x1F00000UL
#define SRSS_CLK_TRIM_PILO_CTL_PILO_ISLOPE_TRIM_Pos 26UL
#define SRSS_CLK_TRIM_PILO_CTL_PILO_ISLOPE_TRIM_Msk 0xC000000UL
#define SRSS_CLK_TRIM_PILO_CTL_PILO_VTDIFF_TRIM_Pos 28UL
#define SRSS_CLK_TRIM_PILO_CTL_PILO_VTDIFF_TRIM_Msk 0x70000000UL
/* SRSS.CLK_TRIM_PILO_CTL2 */
#define SRSS_CLK_TRIM_PILO_CTL2_PILO_VREF_TRIM_Pos 0UL
#define SRSS_CLK_TRIM_PILO_CTL2_PILO_VREF_TRIM_Msk 0xFFUL
#define SRSS_CLK_TRIM_PILO_CTL2_PILO_IREFBM_TRIM_Pos 8UL
#define SRSS_CLK_TRIM_PILO_CTL2_PILO_IREFBM_TRIM_Msk 0x1F00UL
#define SRSS_CLK_TRIM_PILO_CTL2_PILO_IREF_TRIM_Pos 16UL
#define SRSS_CLK_TRIM_PILO_CTL2_PILO_IREF_TRIM_Msk 0xFF0000UL
/* SRSS.CLK_TRIM_PILO_CTL3 */
#define SRSS_CLK_TRIM_PILO_CTL3_PILO_ENGOPT_Pos 0UL
#define SRSS_CLK_TRIM_PILO_CTL3_PILO_ENGOPT_Msk 0xFFFFUL
/* SRSS.CLK_TRIM_ILO1_CTL */
#define SRSS_CLK_TRIM_ILO1_CTL_ILO1_FTRIM_Pos   0UL
#define SRSS_CLK_TRIM_ILO1_CTL_ILO1_FTRIM_Msk   0x3FUL
#define SRSS_CLK_TRIM_ILO1_CTL_ILO1_MONTRIM_Pos 8UL
#define SRSS_CLK_TRIM_ILO1_CTL_ILO1_MONTRIM_Msk 0xF00UL


#endif /* _CYIP_SRSS_V3_H_ */


/* [] END OF FILE */
