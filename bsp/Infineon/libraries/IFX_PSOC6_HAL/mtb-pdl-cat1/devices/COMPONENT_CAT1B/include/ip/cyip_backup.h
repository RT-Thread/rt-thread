/***************************************************************************//**
* \file cyip_backup.h
*
* \brief
* BACKUP IP definitions
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

#ifndef _CYIP_BACKUP_H_
#define _CYIP_BACKUP_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                    BACKUP
*******************************************************************************/

#define BACKUP_CSV_BAK_CSV_SECTION_SIZE         0x00000010UL
#define BACKUP_CSV_BAK_SECTION_SIZE             0x00000010UL
#define BACKUP_SECTION_SIZE                     0x00010000UL

/**
  * \brief clk_bak Backup domain Clock Supervisor registers (BACKUP_CSV_BAK_CSV)
  */
typedef struct {
  __IOM uint32_t REF_CTL;                       /*!< 0x00000000 Clock Supervision Reference Control */
  __IOM uint32_t REF_LIMIT;                     /*!< 0x00000004 Clock Supervision Reference Limits */
  __IOM uint32_t MON_CTL;                       /*!< 0x00000008 Clock Supervision Monitor Control */
   __IM uint32_t RESERVED;
} BACKUP_CSV_BAK_CSV_Type;                      /*!< Size = 16 (0x10) */

/**
  * \brief CSV registers for clk_bak clock (BACKUP_CSV_BAK)
  */
typedef struct {
        BACKUP_CSV_BAK_CSV_Type CSV;            /*!< 0x00000000 clk_bak Backup domain Clock Supervisor registers */
} BACKUP_CSV_BAK_Type;                          /*!< Size = 16 (0x10) */

/**
  * \brief SRSS Backup Registers (BACKUP)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 Control */
   __IM uint32_t RESERVED;
  __IOM uint32_t RTC_RW;                        /*!< 0x00000008 RTC Read Write register */
  __IOM uint32_t CAL_CTL;                       /*!< 0x0000000C Oscillator calibration for absolute frequency */
   __IM uint32_t STATUS;                        /*!< 0x00000010 Status */
  __IOM uint32_t RTC_TIME;                      /*!< 0x00000014 Calendar Seconds, Minutes, Hours, Day of Week */
  __IOM uint32_t RTC_DATE;                      /*!< 0x00000018 Calendar Day of Month, Month,  Year */
  __IOM uint32_t ALM1_TIME;                     /*!< 0x0000001C Alarm 1 Seconds, Minute, Hours, Day of Week */
  __IOM uint32_t ALM1_DATE;                     /*!< 0x00000020 Alarm 1 Day of Month, Month */
  __IOM uint32_t ALM2_TIME;                     /*!< 0x00000024 Alarm 2 Seconds, Minute, Hours, Day of Week */
  __IOM uint32_t ALM2_DATE;                     /*!< 0x00000028 Alarm 2 Day of Month, Month */
  __IOM uint32_t INTR;                          /*!< 0x0000002C Interrupt request register */
  __IOM uint32_t INTR_SET;                      /*!< 0x00000030 Interrupt set request register */
  __IOM uint32_t INTR_MASK;                     /*!< 0x00000034 Interrupt mask register */
   __IM uint32_t INTR_MASKED;                   /*!< 0x00000038 Interrupt masked request register */
   __IM uint32_t RESERVED1[2];
  __IOM uint32_t PMIC_CTL;                      /*!< 0x00000044 PMIC control register */
  __IOM uint32_t RESET;                         /*!< 0x00000048 Backup reset register */
   __IM uint32_t RESERVED2[13];
  __IOM uint32_t LPECO_CTL;                     /*!< 0x00000080 Low-power external crystal oscillator control */
  __IOM uint32_t LPECO_PRESCALE;                /*!< 0x00000084 Low-power external crystal oscillator prescaler */
   __IM uint32_t LPECO_STATUS;                  /*!< 0x00000088 Low-power external crystal oscillator status */
   __IM uint32_t RESERVED3;
   __IM uint32_t WCO_STATUS;                    /*!< 0x00000090 WCO Status Register */
   __IM uint32_t RESERVED4[27];
        BACKUP_CSV_BAK_Type CSV_BAK;            /*!< 0x00000100 CSV registers for clk_bak clock */
   __IM uint32_t RESERVED5[956];
  __IOM uint32_t BREG_SET0[4];                  /*!< 0x00001000 Backup register region 0 */
  __IOM uint32_t BREG_SET1[4];                  /*!< 0x00001010 Backup register region 1 */
  __IOM uint32_t BREG_SET2[8];                  /*!< 0x00001020 Backup register region 2 */
   __IM uint32_t RESERVED6[16];
  __IOM uint32_t BREG_SET3[48];                 /*!< 0x00001080 Backup register region 3 */
} BACKUP_Type;                                  /*!< Size = 4416 (0x1140) */


/* BACKUP_CSV_BAK_CSV.REF_CTL */
#define BACKUP_CSV_BAK_CSV_REF_CTL_STARTUP_Pos  0UL
#define BACKUP_CSV_BAK_CSV_REF_CTL_STARTUP_Msk  0xFFUL
#define BACKUP_CSV_BAK_CSV_REF_CTL_CSV_EN_Pos   31UL
#define BACKUP_CSV_BAK_CSV_REF_CTL_CSV_EN_Msk   0x80000000UL
/* BACKUP_CSV_BAK_CSV.REF_LIMIT */
#define BACKUP_CSV_BAK_CSV_REF_LIMIT_LOWER_Pos  0UL
#define BACKUP_CSV_BAK_CSV_REF_LIMIT_LOWER_Msk  0xFFUL
#define BACKUP_CSV_BAK_CSV_REF_LIMIT_UPPER_Pos  16UL
#define BACKUP_CSV_BAK_CSV_REF_LIMIT_UPPER_Msk  0xFF0000UL
/* BACKUP_CSV_BAK_CSV.MON_CTL */
#define BACKUP_CSV_BAK_CSV_MON_CTL_PERIOD_Pos   0UL
#define BACKUP_CSV_BAK_CSV_MON_CTL_PERIOD_Msk   0xFFUL


/* BACKUP.CTL */
#define BACKUP_CTL_WCO_EN_Pos                   3UL
#define BACKUP_CTL_WCO_EN_Msk                   0x8UL
#define BACKUP_CTL_CLK_SEL_Pos                  8UL
#define BACKUP_CTL_CLK_SEL_Msk                  0x700UL
#define BACKUP_CTL_PRESCALER_Pos                12UL
#define BACKUP_CTL_PRESCALER_Msk                0x3000UL
#define BACKUP_CTL_WCO_BYPASS_Pos               16UL
#define BACKUP_CTL_WCO_BYPASS_Msk               0x10000UL
#define BACKUP_CTL_VDDBAK_CTL_Pos               17UL
#define BACKUP_CTL_VDDBAK_CTL_Msk               0x60000UL
#define BACKUP_CTL_VBACKUP_MEAS_Pos             19UL
#define BACKUP_CTL_VBACKUP_MEAS_Msk             0x80000UL
#define BACKUP_CTL_EN_CHARGE_KEY_Pos            24UL
#define BACKUP_CTL_EN_CHARGE_KEY_Msk            0xFF000000UL
/* BACKUP.RTC_RW */
#define BACKUP_RTC_RW_READ_Pos                  0UL
#define BACKUP_RTC_RW_READ_Msk                  0x1UL
#define BACKUP_RTC_RW_WRITE_Pos                 1UL
#define BACKUP_RTC_RW_WRITE_Msk                 0x2UL
/* BACKUP.CAL_CTL */
#define BACKUP_CAL_CTL_CALIB_VAL_Pos            0UL
#define BACKUP_CAL_CTL_CALIB_VAL_Msk            0x3FUL
#define BACKUP_CAL_CTL_CALIB_SIGN_Pos           6UL
#define BACKUP_CAL_CTL_CALIB_SIGN_Msk           0x40UL
#define BACKUP_CAL_CTL_CAL_COMP_PER_MIN_Pos     16UL
#define BACKUP_CAL_CTL_CAL_COMP_PER_MIN_Msk     0x30000UL
#define BACKUP_CAL_CTL_CAL_SEL_Pos              28UL
#define BACKUP_CAL_CTL_CAL_SEL_Msk              0x30000000UL
#define BACKUP_CAL_CTL_CAL_OUT_Pos              31UL
#define BACKUP_CAL_CTL_CAL_OUT_Msk              0x80000000UL
/* BACKUP.STATUS */
#define BACKUP_STATUS_RTC_BUSY_Pos              0UL
#define BACKUP_STATUS_RTC_BUSY_Msk              0x1UL
#define BACKUP_STATUS_WCO_OK_Pos                2UL
#define BACKUP_STATUS_WCO_OK_Msk                0x4UL
/* BACKUP.RTC_TIME */
#define BACKUP_RTC_TIME_RTC_SEC_Pos             0UL
#define BACKUP_RTC_TIME_RTC_SEC_Msk             0x3FUL
#define BACKUP_RTC_TIME_RTC_MIN_Pos             8UL
#define BACKUP_RTC_TIME_RTC_MIN_Msk             0x3F00UL
#define BACKUP_RTC_TIME_RTC_HOUR_Pos            16UL
#define BACKUP_RTC_TIME_RTC_HOUR_Msk            0x1F0000UL
#define BACKUP_RTC_TIME_CTRL_12HR_Pos           22UL
#define BACKUP_RTC_TIME_CTRL_12HR_Msk           0x400000UL
#define BACKUP_RTC_TIME_RTC_DAY_Pos             24UL
#define BACKUP_RTC_TIME_RTC_DAY_Msk             0x7000000UL
/* BACKUP.RTC_DATE */
#define BACKUP_RTC_DATE_RTC_DATE_Pos            0UL
#define BACKUP_RTC_DATE_RTC_DATE_Msk            0x1FUL
#define BACKUP_RTC_DATE_RTC_MON_Pos             8UL
#define BACKUP_RTC_DATE_RTC_MON_Msk             0xF00UL
#define BACKUP_RTC_DATE_RTC_YEAR_Pos            16UL
#define BACKUP_RTC_DATE_RTC_YEAR_Msk            0x7F0000UL
/* BACKUP.ALM1_TIME */
#define BACKUP_ALM1_TIME_ALM_SEC_Pos            0UL
#define BACKUP_ALM1_TIME_ALM_SEC_Msk            0x3FUL
#define BACKUP_ALM1_TIME_ALM_SEC_EN_Pos         7UL
#define BACKUP_ALM1_TIME_ALM_SEC_EN_Msk         0x80UL
#define BACKUP_ALM1_TIME_ALM_MIN_Pos            8UL
#define BACKUP_ALM1_TIME_ALM_MIN_Msk            0x3F00UL
#define BACKUP_ALM1_TIME_ALM_MIN_EN_Pos         15UL
#define BACKUP_ALM1_TIME_ALM_MIN_EN_Msk         0x8000UL
#define BACKUP_ALM1_TIME_ALM_HOUR_Pos           16UL
#define BACKUP_ALM1_TIME_ALM_HOUR_Msk           0x1F0000UL
#define BACKUP_ALM1_TIME_ALM_HOUR_EN_Pos        23UL
#define BACKUP_ALM1_TIME_ALM_HOUR_EN_Msk        0x800000UL
#define BACKUP_ALM1_TIME_ALM_DAY_Pos            24UL
#define BACKUP_ALM1_TIME_ALM_DAY_Msk            0x7000000UL
#define BACKUP_ALM1_TIME_ALM_DAY_EN_Pos         31UL
#define BACKUP_ALM1_TIME_ALM_DAY_EN_Msk         0x80000000UL
/* BACKUP.ALM1_DATE */
#define BACKUP_ALM1_DATE_ALM_DATE_Pos           0UL
#define BACKUP_ALM1_DATE_ALM_DATE_Msk           0x1FUL
#define BACKUP_ALM1_DATE_ALM_DATE_EN_Pos        7UL
#define BACKUP_ALM1_DATE_ALM_DATE_EN_Msk        0x80UL
#define BACKUP_ALM1_DATE_ALM_MON_Pos            8UL
#define BACKUP_ALM1_DATE_ALM_MON_Msk            0xF00UL
#define BACKUP_ALM1_DATE_ALM_MON_EN_Pos         15UL
#define BACKUP_ALM1_DATE_ALM_MON_EN_Msk         0x8000UL
#define BACKUP_ALM1_DATE_ALM_EN_Pos             31UL
#define BACKUP_ALM1_DATE_ALM_EN_Msk             0x80000000UL
/* BACKUP.ALM2_TIME */
#define BACKUP_ALM2_TIME_ALM_SEC_Pos            0UL
#define BACKUP_ALM2_TIME_ALM_SEC_Msk            0x3FUL
#define BACKUP_ALM2_TIME_ALM_SEC_EN_Pos         7UL
#define BACKUP_ALM2_TIME_ALM_SEC_EN_Msk         0x80UL
#define BACKUP_ALM2_TIME_ALM_MIN_Pos            8UL
#define BACKUP_ALM2_TIME_ALM_MIN_Msk            0x3F00UL
#define BACKUP_ALM2_TIME_ALM_MIN_EN_Pos         15UL
#define BACKUP_ALM2_TIME_ALM_MIN_EN_Msk         0x8000UL
#define BACKUP_ALM2_TIME_ALM_HOUR_Pos           16UL
#define BACKUP_ALM2_TIME_ALM_HOUR_Msk           0x1F0000UL
#define BACKUP_ALM2_TIME_ALM_HOUR_EN_Pos        23UL
#define BACKUP_ALM2_TIME_ALM_HOUR_EN_Msk        0x800000UL
#define BACKUP_ALM2_TIME_ALM_DAY_Pos            24UL
#define BACKUP_ALM2_TIME_ALM_DAY_Msk            0x7000000UL
#define BACKUP_ALM2_TIME_ALM_DAY_EN_Pos         31UL
#define BACKUP_ALM2_TIME_ALM_DAY_EN_Msk         0x80000000UL
/* BACKUP.ALM2_DATE */
#define BACKUP_ALM2_DATE_ALM_DATE_Pos           0UL
#define BACKUP_ALM2_DATE_ALM_DATE_Msk           0x1FUL
#define BACKUP_ALM2_DATE_ALM_DATE_EN_Pos        7UL
#define BACKUP_ALM2_DATE_ALM_DATE_EN_Msk        0x80UL
#define BACKUP_ALM2_DATE_ALM_MON_Pos            8UL
#define BACKUP_ALM2_DATE_ALM_MON_Msk            0xF00UL
#define BACKUP_ALM2_DATE_ALM_MON_EN_Pos         15UL
#define BACKUP_ALM2_DATE_ALM_MON_EN_Msk         0x8000UL
#define BACKUP_ALM2_DATE_ALM_EN_Pos             31UL
#define BACKUP_ALM2_DATE_ALM_EN_Msk             0x80000000UL
/* BACKUP.INTR */
#define BACKUP_INTR_ALARM1_Pos                  0UL
#define BACKUP_INTR_ALARM1_Msk                  0x1UL
#define BACKUP_INTR_ALARM2_Pos                  1UL
#define BACKUP_INTR_ALARM2_Msk                  0x2UL
#define BACKUP_INTR_CENTURY_Pos                 2UL
#define BACKUP_INTR_CENTURY_Msk                 0x4UL
/* BACKUP.INTR_SET */
#define BACKUP_INTR_SET_ALARM1_Pos              0UL
#define BACKUP_INTR_SET_ALARM1_Msk              0x1UL
#define BACKUP_INTR_SET_ALARM2_Pos              1UL
#define BACKUP_INTR_SET_ALARM2_Msk              0x2UL
#define BACKUP_INTR_SET_CENTURY_Pos             2UL
#define BACKUP_INTR_SET_CENTURY_Msk             0x4UL
/* BACKUP.INTR_MASK */
#define BACKUP_INTR_MASK_ALARM1_Pos             0UL
#define BACKUP_INTR_MASK_ALARM1_Msk             0x1UL
#define BACKUP_INTR_MASK_ALARM2_Pos             1UL
#define BACKUP_INTR_MASK_ALARM2_Msk             0x2UL
#define BACKUP_INTR_MASK_CENTURY_Pos            2UL
#define BACKUP_INTR_MASK_CENTURY_Msk            0x4UL
/* BACKUP.INTR_MASKED */
#define BACKUP_INTR_MASKED_ALARM1_Pos           0UL
#define BACKUP_INTR_MASKED_ALARM1_Msk           0x1UL
#define BACKUP_INTR_MASKED_ALARM2_Pos           1UL
#define BACKUP_INTR_MASKED_ALARM2_Msk           0x2UL
#define BACKUP_INTR_MASKED_CENTURY_Pos          2UL
#define BACKUP_INTR_MASKED_CENTURY_Msk          0x4UL
/* BACKUP.PMIC_CTL */
#define BACKUP_PMIC_CTL_UNLOCK_Pos              8UL
#define BACKUP_PMIC_CTL_UNLOCK_Msk              0xFF00UL
#define BACKUP_PMIC_CTL_POLARITY_Pos            16UL
#define BACKUP_PMIC_CTL_POLARITY_Msk            0x10000UL
#define BACKUP_PMIC_CTL_PMIC_EN_OUTEN_Pos       29UL
#define BACKUP_PMIC_CTL_PMIC_EN_OUTEN_Msk       0x20000000UL
#define BACKUP_PMIC_CTL_PMIC_ALWAYSEN_Pos       30UL
#define BACKUP_PMIC_CTL_PMIC_ALWAYSEN_Msk       0x40000000UL
#define BACKUP_PMIC_CTL_PMIC_EN_Pos             31UL
#define BACKUP_PMIC_CTL_PMIC_EN_Msk             0x80000000UL
/* BACKUP.RESET */
#define BACKUP_RESET_RESET_Pos                  31UL
#define BACKUP_RESET_RESET_Msk                  0x80000000UL
/* BACKUP.LPECO_CTL */
#define BACKUP_LPECO_CTL_LPECO_CRANGE_Pos       4UL
#define BACKUP_LPECO_CTL_LPECO_CRANGE_Msk       0x30UL
#define BACKUP_LPECO_CTL_LPECO_FRANGE_Pos       8UL
#define BACKUP_LPECO_CTL_LPECO_FRANGE_Msk       0x100UL
#define BACKUP_LPECO_CTL_LPECO_AMP_SEL_Pos      12UL
#define BACKUP_LPECO_CTL_LPECO_AMP_SEL_Msk      0x1000UL
#define BACKUP_LPECO_CTL_LPECO_DIV_ENABLE_Pos   28UL
#define BACKUP_LPECO_CTL_LPECO_DIV_ENABLE_Msk   0x10000000UL
#define BACKUP_LPECO_CTL_LPECO_AMPDET_EN_Pos    30UL
#define BACKUP_LPECO_CTL_LPECO_AMPDET_EN_Msk    0x40000000UL
#define BACKUP_LPECO_CTL_LPECO_EN_Pos           31UL
#define BACKUP_LPECO_CTL_LPECO_EN_Msk           0x80000000UL
/* BACKUP.LPECO_PRESCALE */
#define BACKUP_LPECO_PRESCALE_LPECO_DIV_ENABLED_Pos 0UL
#define BACKUP_LPECO_PRESCALE_LPECO_DIV_ENABLED_Msk 0x1UL
#define BACKUP_LPECO_PRESCALE_LPECO_FRAC_DIV_Pos 8UL
#define BACKUP_LPECO_PRESCALE_LPECO_FRAC_DIV_Msk 0xFF00UL
#define BACKUP_LPECO_PRESCALE_LPECO_INT_DIV_Pos 16UL
#define BACKUP_LPECO_PRESCALE_LPECO_INT_DIV_Msk 0x3FF0000UL
/* BACKUP.LPECO_STATUS */
#define BACKUP_LPECO_STATUS_LPECO_AMPDET_OK_Pos 0UL
#define BACKUP_LPECO_STATUS_LPECO_AMPDET_OK_Msk 0x1UL
#define BACKUP_LPECO_STATUS_LPECO_READY_Pos     1UL
#define BACKUP_LPECO_STATUS_LPECO_READY_Msk     0x2UL
/* BACKUP.WCO_STATUS */
#define BACKUP_WCO_STATUS_WCO_OK_Pos            2UL
#define BACKUP_WCO_STATUS_WCO_OK_Msk            0x4UL
/* BACKUP.BREG_SET0 */
#define BACKUP_BREG_SET0_BREG_Pos               0UL
#define BACKUP_BREG_SET0_BREG_Msk               0xFFFFFFFFUL
/* BACKUP.BREG_SET1 */
#define BACKUP_BREG_SET1_BREG_Pos               0UL
#define BACKUP_BREG_SET1_BREG_Msk               0xFFFFFFFFUL
/* BACKUP.BREG_SET2 */
#define BACKUP_BREG_SET2_BREG_Pos               0UL
#define BACKUP_BREG_SET2_BREG_Msk               0xFFFFFFFFUL
/* BACKUP.BREG_SET3 */
#define BACKUP_BREG_SET3_BREG_Pos               0UL
#define BACKUP_BREG_SET3_BREG_Msk               0xFFFFFFFFUL


#endif /* _CYIP_BACKUP_H_ */


/* [] END OF FILE */
