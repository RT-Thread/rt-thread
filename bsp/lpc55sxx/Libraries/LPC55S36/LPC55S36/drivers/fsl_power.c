/*
 * Copyright 2020, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <string.h>
#include "fsl_common.h"
#include "fsl_power.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.power"
#endif

/* NOTE: These registers are handled by the SDK. The user should not modify the source code. Changes to the source code
 * can cause application failure. NXP is not responsible for any change to the code and is not obligated to provide
 * support. */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief LDO_FLASH_NV & LDO_EFUSE_PROG voltage settings
 */
typedef enum _v_ldo_flashnv_ldo_efuse
{
    V_LDO_1P650 = 0, /*!< 1.65  V */
    V_LDO_1P700 = 1, /*!< 1.7   V */
    V_LDO_1P750 = 2, /*!< 1.75  V */
    V_LDO_1P800 = 3, /*!< 1.8   V */
    V_LDO_1P850 = 4, /*!< 1.85  V */
    V_LDO_1P900 = 5, /*!< 1.9   V */
    V_LDO_1P950 = 6, /*!< 1.95  V */
    V_LDO_2P000 = 7  /*!< 2.0   V */
} v_ldo_flashnv_ldo_efuse_t;

/**
 * @brief Always On and Memories LDO voltage settings
 */
typedef enum _v_ao
{
    // V_AO_1P220 1.22  = 0,  /*!< 1.22  V */
    V_AO_0P700 = 1,  /*!< 0.7   V */
    V_AO_0P725 = 2,  /*!< 0.725 V */
    V_AO_0P750 = 3,  /*!< 0.75  V */
    V_AO_0P775 = 4,  /*!< 0.775 V */
    V_AO_0P800 = 5,  /*!< 0.8   V */
    V_AO_0P825 = 6,  /*!< 0.825 V */
    V_AO_0P850 = 7,  /*!< 0.85  V */
    V_AO_0P875 = 8,  /*!< 0.875 V */
    V_AO_0P900 = 9,  /*!< 0.9   V */
    V_AO_0P960 = 10, /*!< 0.96  V */
    V_AO_0P970 = 11, /*!< 0.97  V */
    V_AO_0P980 = 12, /*!< 0.98  V */
    V_AO_0P990 = 13, /*!< 0.99  V */
    V_AO_1P000 = 14, /*!< 1     V */
    V_AO_1P010 = 15, /*!< 1.01  V */
    V_AO_1P020 = 16, /*!< 1.02  V */
    V_AO_1P030 = 17, /*!< 1.03  V */
    V_AO_1P040 = 18, /*!< 1.04  V */
    V_AO_1P050 = 19, /*!< 1.05  V */
    V_AO_1P060 = 20, /*!< 1.06  V */
    V_AO_1P070 = 21, /*!< 1.07  V */
    V_AO_1P080 = 22, /*!< 1.08  V */
    V_AO_1P090 = 23, /*!< 1.09  V */
    V_AO_1P100 = 24, /*!< 1.1   V */
    V_AO_1P110 = 25, /*!< 1.11  V */
    V_AO_1P120 = 26, /*!< 1.12  V */
    V_AO_1P130 = 27, /*!< 1.13  V */
    V_AO_1P140 = 28, /*!< 1.14  V */
    V_AO_1P150 = 29, /*!< 1.15  V */
    V_AO_1P160 = 30, /*!< 1.16  V */
    V_AO_1P220 = 31  /*!< 1.22  V */
} v_ao_t;

/**
 * @brief DCDC voltage settings
 */
typedef enum _v_dcdc
{
    V_DCDC_0P950 = 0, /*!< 0.95  V */
    V_DCDC_0P975 = 1, /*!< 0.975 V */
    V_DCDC_1P000 = 2, /*!< 1     V */
    V_DCDC_1P025 = 3, /*!< 1.025 V */
    V_DCDC_1P050 = 4, /*!< 1.050 V */
    V_DCDC_1P075 = 5, /*!< 1.075 V */
    V_DCDC_1P100 = 6, /*!< 1.1   V */
    V_DCDC_1P125 = 7, /*!< 1.125 V */
    V_DCDC_1P150 = 8, /*!< 1.150 V */
    V_DCDC_1P175 = 9, /*!< 1.175 V */
    V_DCDC_1P200 = 10 /*!< 1.2   V */
} v_dcdc_t;

/**
 * @brief LDO_CORE High Power Mode voltage settings
 */
typedef enum _v_ldocore_hp
{
    V_LDOCORE_HP_1P373 = 0,  /*!< 1.373  V */
    V_LDOCORE_HP_1P365 = 1,  /*!< 1.365  V */
    V_LDOCORE_HP_1P359 = 2,  /*!< 1.359  V */
    V_LDOCORE_HP_1P352 = 3,  /*!< 1.352  V */
    V_LDOCORE_HP_1P345 = 4,  /*!< 1.345  V */
    V_LDOCORE_HP_1P339 = 5,  /*!< 1.339  V */
    V_LDOCORE_HP_1P332 = 6,  /*!< 1.332  V */
    V_LDOCORE_HP_1P325 = 7,  /*!< 1.325  V */
    V_LDOCORE_HP_1P318 = 8,  /*!< 1.318  V */
    V_LDOCORE_HP_1P311 = 9,  /*!< 1.311  V */
    V_LDOCORE_HP_1P305 = 10, /*!< 1.305  V */
    V_LDOCORE_HP_1P298 = 11, /*!< 1.298  V */
    V_LDOCORE_HP_1P291 = 12, /*!< 1.291  V */
    V_LDOCORE_HP_1P285 = 13, /*!< 1.285  V */
    V_LDOCORE_HP_1P278 = 14, /*!< 1.278  V */
    V_LDOCORE_HP_1P271 = 15, /*!< 1.271  V */
    V_LDOCORE_HP_1P264 = 16, /*!< 1.264  V */
    V_LDOCORE_HP_1P258 = 17, /*!< 1.258  V */
    V_LDOCORE_HP_1P251 = 18, /*!< 1.251  V */
    V_LDOCORE_HP_1P244 = 19, /*!< 1.244  V */
    V_LDOCORE_HP_1P237 = 20, /*!< 1.237  V */
    V_LDOCORE_HP_1P231 = 21, /*!< 1.231  V */
    V_LDOCORE_HP_1P224 = 22, /*!< 1.224  V */
    V_LDOCORE_HP_1P217 = 23, /*!< 1.217  V */
    V_LDOCORE_HP_1P210 = 24, /*!< 1.21   V */
    V_LDOCORE_HP_1P204 = 25, /*!< 1.204  V */
    V_LDOCORE_HP_1P197 = 26, /*!< 1.197  V */
    V_LDOCORE_HP_1P190 = 27, /*!< 1.19   V */
    V_LDOCORE_HP_1P183 = 28, /*!< 1.183  V */
    V_LDOCORE_HP_1P177 = 29, /*!< 1.177  V */
    V_LDOCORE_HP_1P169 = 30, /*!< 1.169  V */
    V_LDOCORE_HP_1P163 = 31, /*!< 1.163  V */
    V_LDOCORE_HP_1P156 = 32, /*!< 1.156  V */
    V_LDOCORE_HP_1P149 = 33, /*!< 1.149  V */
    V_LDOCORE_HP_1P143 = 34, /*!< 1.143  V */
    V_LDOCORE_HP_1P136 = 35, /*!< 1.136  V */
    V_LDOCORE_HP_1P129 = 36, /*!< 1.129  V */
    V_LDOCORE_HP_1P122 = 37, /*!< 1.122  V */
    V_LDOCORE_HP_1P116 = 38, /*!< 1.116  V */
    V_LDOCORE_HP_1P109 = 39, /*!< 1.109  V */
    V_LDOCORE_HP_1P102 = 40, /*!< 1.102  V */
    V_LDOCORE_HP_1P095 = 41, /*!< 1.095  V */
    V_LDOCORE_HP_1P088 = 42, /*!< 1.088  V */
    V_LDOCORE_HP_1P082 = 43, /*!< 1.082  V */
    V_LDOCORE_HP_1P075 = 44, /*!< 1.075  V */
    V_LDOCORE_HP_1P068 = 45, /*!< 1.068  V */
    V_LDOCORE_HP_1P062 = 46, /*!< 1.062  V */
    V_LDOCORE_HP_1P055 = 47, /*!< 1.055  V */
    V_LDOCORE_HP_1P048 = 48, /*!< 1.048  V */
    V_LDOCORE_HP_1P041 = 49, /*!< 1.041  V */
    V_LDOCORE_HP_1P034 = 50, /*!< 1.034  V */
    V_LDOCORE_HP_1P027 = 51, /*!< 1.027  V */
    V_LDOCORE_HP_1P021 = 52, /*!< 1.021  V */
    V_LDOCORE_HP_1P014 = 53, /*!< 1.014  V */
    V_LDOCORE_HP_1P007 = 54, /*!< 1.007  V */
    V_LDOCORE_HP_1P001 = 55, /*!< 1.001  V */
    V_LDOCORE_HP_0P993 = 56, /*!< 0.9937 V */
    V_LDOCORE_HP_0P987 = 57, /*!< 0.987  V */
    V_LDOCORE_HP_0P980 = 58, /*!< 0.9802 V */
    V_LDOCORE_HP_0P973 = 59, /*!< 0.9731 V */
    V_LDOCORE_HP_0P966 = 60, /*!< 0.9666 V */
    V_LDOCORE_HP_0P959 = 61, /*!< 0.9598 V */
    V_LDOCORE_HP_0P953 = 62, /*!< 0.9532 V */
    V_LDOCORE_HP_0P946 = 63, /*!< 0.946  V */
    V_LDOCORE_HP_0P939 = 64, /*!< 0.9398 V */
    V_LDOCORE_HP_0P932 = 65, /*!< 0.9327 V */
    V_LDOCORE_HP_0P926 = 66, /*!< 0.9262 V */
    V_LDOCORE_HP_0P919 = 67, /*!< 0.9199 V */
    V_LDOCORE_HP_0P913 = 68, /*!< 0.9135 V */
    V_LDOCORE_HP_0P907 = 69, /*!< 0.9071 V */
    V_LDOCORE_HP_0P901 = 70, /*!< 0.9012 V */
    V_LDOCORE_HP_0P895 = 71, /*!< 0.8953 V */
    V_LDOCORE_HP_0P889 = 72, /*!< 0.8895 V */
    V_LDOCORE_HP_0P883 = 73, /*!< 0.8837 V */
    V_LDOCORE_HP_0P877 = 74, /*!< 0.8779 V */
    V_LDOCORE_HP_0P871 = 75, /*!< 0.8719 V */
    V_LDOCORE_HP_0P865 = 76, /*!< 0.8658 V */
    V_LDOCORE_HP_0P859 = 77, /*!< 0.8596 V */
    V_LDOCORE_HP_0P853 = 78, /*!< 0.8537 V */
    V_LDOCORE_HP_0P847 = 79, /*!< 0.8474 V */
    V_LDOCORE_HP_0P841 = 80, /*!< 0.8413 V */
    V_LDOCORE_HP_0P835 = 81, /*!< 0.835  V */
    V_LDOCORE_HP_0P828 = 82, /*!< 0.8288 V */
    V_LDOCORE_HP_0P822 = 83, /*!< 0.8221 V */
    V_LDOCORE_HP_0P815 = 84, /*!< 0.8158 V */
    V_LDOCORE_HP_0P809 = 85, /*!< 0.8094 V */
    V_LDOCORE_HP_0P802 = 86, /*!< 0.8026 V */
    V_LDOCORE_HP_0P795 = 87, /*!< 0.7959 V */
    V_LDOCORE_HP_0P789 = 88, /*!< 0.7893 V */
    V_LDOCORE_HP_0P782 = 89, /*!< 0.7823 V */
    V_LDOCORE_HP_0P775 = 90, /*!< 0.7756 V */
    V_LDOCORE_HP_0P768 = 91, /*!< 0.7688 V */
    V_LDOCORE_HP_0P762 = 92, /*!< 0.7623 V */
    V_LDOCORE_HP_0P755 = 93, /*!< 0.7558 V */
    V_LDOCORE_HP_0P749 = 94, /*!< 0.749  V */
    V_LDOCORE_HP_0P742 = 95, /*!< 0.7421 V */
    V_LDOCORE_HP_0P735 = 96, /*!< 0.7354 V */
    V_LDOCORE_HP_0P728 = 97, /*!< 0.7284 V */
    V_LDOCORE_HP_0P722 = 98, /*!< 0.722  V */
    V_LDOCORE_HP_0P715 = 99  /*!< 0.715  V */
    //    V_LDOCORE_HP_0P715 = 100, /*!< 0.7148 V */
    //    V_LDOCORE_HP_0P715 = 101, /*!< 0.7148 V */
    //    V_LDOCORE_HP_0P715 = 102, /*!< 0.7151 V */
    //    V_LDOCORE_HP_0P715 = 103, /*!< 0.7147 V */
    //    V_LDOCORE_HP_0P715 = 104, /*!< 0.7147 V */
    //    V_LDOCORE_HP_0P715 = 105, /*!< 0.715  V */
    //    V_LDOCORE_HP_0P715 = 106, /*!< 0.7147 V */
    //    V_LDOCORE_HP_0P715 = 107, /*!< 0.715  V */
    //    V_LDOCORE_HP_0P715 = 108, /*!< 0.7152 V */
    //    V_LDOCORE_HP_0P715 = 109, /*!< 0.7148 V */
    //    V_LDOCORE_HP_0P715 = 110, /*!< 0.715  V */
    //    V_LDOCORE_HP_0P715 = 111, /*!< 0.7151 V */
    //    V_LDOCORE_HP_0P715 = 112, /*!< 0.7153 V */
    //    V_LDOCORE_HP_0P715 = 113, /*!< 0.7152 V */
    //    V_LDOCORE_HP_0P715 = 114, /*!< 0.7149 V */
    //    V_LDOCORE_HP_0P715 = 115, /*!< 0.7154 V */
    //    V_LDOCORE_HP_0P715 = 116, /*!< 0.7152 V */
    //    V_LDOCORE_HP_0P715 = 117, /*!< 0.7154 V */
    //    V_LDOCORE_HP_0P715 = 118, /*!< 0.7147 V */
    //    V_LDOCORE_HP_0P715 = 119, /*!< 0.7152 V */
    //    V_LDOCORE_HP_0P715 = 120, /*!< 0.7149 V */
    //    V_LDOCORE_HP_0P715 = 121, /*!< 0.7151 V */
    //    V_LDOCORE_HP_0P715 = 122, /*!< 0.7152 V */
    //    V_LDOCORE_HP_0P715 = 123, /*!< 0.7153 V */
    //    V_LDOCORE_HP_0P715 = 124, /*!< 0.7149 V */
    //    V_LDOCORE_HP_0P715 = 125, /*!< 0.7154 V */
    //    V_LDOCORE_HP_0P715 = 126, /*!< 0.7153 V */
    //    V_LDOCORE_HP_0P715 = 127, /*!< 0.7154 V */
} v_ldocore_hp_t;

/**
 * @brief LDO_CORE Low Power Mode voltage settings
 */
typedef enum _v_ldocore_lp
{
    V_LDOCORE_LP_0P750 = 3, /*!< 0.75  V */
    V_LDOCORE_LP_0P800 = 2, /*!< 0.8   V */
    V_LDOCORE_LP_0P850 = 1, /*!< 0.85  V */
    V_LDOCORE_LP_0P900 = 0  /*!< 0.9   V */
} v_ldocore_lp_t;

/**
 * @brief System Power Mode settings
 */
typedef enum _v_system_power_profile
{
    V_SYSTEM_POWER_PROFILE_LOW    = 0UL, /*!< For system below or equal to 100 MHz */
    V_SYSTEM_POWER_PROFILE_MEDIUM = 1UL, /*!< For system frequencies in ]100 MHz - 150 MHz] */
    V_SYSTEM_POWER_PROFILE_HIGH   = 2UL, /*!< For system above 150 MHz */
} v_system_power_profile_t;

/**
 * @brief Manufacturing Process Corners
 */
typedef enum
{
    PROCESS_CORNER_SSS,    /**< Slow Corner Process */
    PROCESS_CORNER_NNN,    /**< Nominal Corner Process */
    PROCESS_CORNER_FFF,    /**< Fast Corner Process */
    PROCESS_CORNER_OTHERS, /**< SFN, SNF, NFS, Poly Res ... Corner Process */
} lowpower_process_corner_enum;

/** @brief  Low Power main structure */
typedef struct
{
    __IO uint32_t CFG;          /*!< Low Power Mode Configuration, and miscallenous options  */
    __IO uint32_t PDCTRL[2];    /*!< Power Down control : controls power of various modules
                                 in the different Low power modes, including ROM */
    __IO uint32_t SRAMRETCTRL;  /*!< Power Down control : controls power SRAM instances
                                 in the different Low power modes */
    __IO uint32_t CPURETCTRL;   /*!< CPU0 retention control : controls CPU retention parameters in POWER DOWN modes */
    __IO uint64_t VOLTAGE;      /*!< Voltage control in Low Power Modes */
    __IO uint32_t WAKEUPSRC[4]; /*!< Wake up sources control for sleepcon */
    __IO uint32_t WAKEUPINT[4]; /*!< Wake up sources control for ARM */
    __IO uint32_t HWWAKE;       /*!< Interrupt that can postpone power down modes
                                 in case an interrupt is pending when the processor request deepsleep */
    __IO uint32_t WAKEUPIOSRC;  /*!< Wake up I/O sources in DEEP POWER-DOWN mode */
} LPC_LOWPOWER_T;

#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
/**
 * @brief NMPA related Registers
 */
#define FLASH_NMPA_BOD_LDOCORE                      (*((volatile unsigned int *)(0x3FC08)))
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_ARRAY0    (*((volatile unsigned int *)(0x3FC18)))
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_ARRAY1    (*((volatile unsigned int *)(0x3FC1C)))
#define FLASH_NMPA_LDO_AO                           (*((volatile unsigned int *)(0x3FC24)))
#define FLASH_NMPA_LDO_MEM                          (*((volatile unsigned int *)(0x3FD60)))
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_ARRAY0   (*((volatile unsigned int *)(0x3FCB0)))
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_ARRAY1   (*((volatile unsigned int *)(0x3FCB4)))
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_ARRAY0 (*((volatile unsigned int *)(0x3FCB8)))
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_ARRAY1 (*((volatile unsigned int *)(0x3FCBC)))
#define FLASH_NMPA_PVT_MONITOR_0_RINGO              (*((volatile unsigned int *)(0x3FCE0)))
#define FLASH_NMPA_PVT_MONITOR_1_RINGO              (*((volatile unsigned int *)(0x3FCF0)))

/**
 * @brief NMPA related masks
 */

#define FLASH_NMPA_BOD_LDOCORE_REGREF_1P8V_OFFSET_SHIFT (24U)
#define FLASH_NMPA_BOD_LDOCORE_REGREF_1P8V_OFFSET_MASK  (0xFF000000U)
#define FLASH_NMPA_LDO_AO_VADJ_ACTIVE_SHIFT             (0U)
#define FLASH_NMPA_LDO_AO_VADJ_ACTIVE_MASK              (0xFFU)
#endif

/**
 * @brief CSS related Registers
 */
#define CSSV2_STATUS_REG            (*((volatile unsigned int *)(0x40030000)))
#define CSSV2_CTRL_REG              (*((volatile unsigned int *)(0x40030004)))
#define SYSCON_CSS_CLK_CTRL_REG     (*((volatile unsigned int *)(0x400009B0)))
#define SYSCON_CSS_CLK_CTRL_SET_REG (*((volatile unsigned int *)(0x400009B4)))
#define SYSCON_CSS_CLK_CTRL_CLR_REG (*((volatile unsigned int *)(0x400009B8)))

/**
 * @brief Wake-up I/O positions
 */
/*!< wake-up 0 */
#define WAKEUPIO_0_PORT (1UL)
#define WAKEUPIO_0_PINS (1UL)
/*!< wake-up 1 */
#define WAKEUPIO_1_PORT (0UL)
#define WAKEUPIO_1_PINS (28UL)
/*!< wake-up 2 */
#define WAKEUPIO_2_PORT (1UL)
#define WAKEUPIO_2_PINS (18UL)
/*!< wake-up 3 */
#define WAKEUPIO_3_PORT (1UL)
#define WAKEUPIO_3_PINS (30UL)
/*!< wake-up 4 */
#define WAKEUPIO_4_PORT (0UL)
#define WAKEUPIO_4_PINS (26UL)

/**
 * @brief SRAM Low Power Modes
 */
#define LOWPOWER_SRAM_LPMODE_MASK      (0xFUL)
#define LOWPOWER_SRAM_LPMODE_ACTIVE    (0x6UL) /*!< SRAM functional mode                                */
#define LOWPOWER_SRAM_LPMODE_SLEEP     (0xFUL) /*!< SRAM Sleep mode (Data retention, fast wake up)      */
#define LOWPOWER_SRAM_LPMODE_DEEPSLEEP (0x8UL) /*!< SRAM Deep Sleep mode (Data retention, slow wake up) */
#define LOWPOWER_SRAM_LPMODE_SHUTDOWN  (0x9UL) /*!< SRAM Shut Down mode (no data retention)             */
#define LOWPOWER_SRAM_LPMODE_POWERUP   (0xAUL) /*!< SRAM is powering up                                 */

/**
 * @brief SoC Low Power modes
 */
#define LOWPOWER_CFG_LPMODE_INDEX          0
#define LOWPOWER_CFG_LPMODE_MASK           (0x3UL << LOWPOWER_CFG_LPMODE_INDEX)
#define LOWPOWER_CFG_SELCLOCK_INDEX        2
#define LOWPOWER_CFG_SELCLOCK_MASK         (0x1UL << LOWPOWER_CFG_SELCLOCK_INDEX)
#define LOWPOWER_CFG_SELMEMSUPPLY_INDEX    3
#define LOWPOWER_CFG_SELMEMSUPPLY_MASK     (0x1UL << LOWPOWER_CFG_SELMEMSUPPLY_INDEX)
#define LOWPOWER_CFG_MEMLOWPOWERMODE_INDEX 4
#define LOWPOWER_CFG_MEMLOWPOWERMODE_MASK  (0x1UL << LOWPOWER_CFG_MEMLOWPOWERMODE_INDEX)
#define LOWPOWER_CFG_LDODEEPSLEEPREF_INDEX 5
#define LOWPOWER_CFG_LDODEEPSLEEPREF_MASK  (0x1UL << LOWPOWER_CFG_LDODEEPSLEEPREF_INDEX)

#define LOWPOWER_CFG_LPMODE_ACTIVE        0 /*!< ACTIVE mode */
#define LOWPOWER_CFG_LPMODE_DEEPSLEEP     1 /*!< DEEP-SLEEP mode */
#define LOWPOWER_CFG_LPMODE_POWERDOWN     2 /*!< POWER-DOWN mode */
#define LOWPOWER_CFG_LPMODE_DEEPPOWERDOWN 3 /*!< DEEP POWER-DOWN mode */
#define LOWPOWER_CFG_LPMODE_SLEEP         4 /*!< SLEEP mode */

#define LOWPOWER_CFG_SELCLOCK_1MHZ 0 /*!< The 1 MHz clock is used during the configuration of the PMC */
#define LOWPOWER_CFG_SELCLOCK_12MHZ \
    1 /*!< The 12 MHz clock is used during the configuration of the PMC (to speed up PMC configuration process)*/

#define LOWPOWER_CFG_SELMEMSUPPLY_LDOMEM 0 /*!< In DEEP SLEEP power mode, the Memories are supplied by the LDO_MEM */
#define LOWPOWER_CFG_SELMEMSUPPLY_LDODEEPSLEEP \
    1 /*!< In DEEP SLEEP power mode, the Memories are supplied by the LDO_DEEP_SLEEP (or DCDC) */

#define LOWPOWER_CFG_MEMLOWPOWERMODE_SOURCEBIASING                                                                     \
    0 /*!< All SRAM instances use "Source Biasing" as low power mode technic (it is recommended to set LDO_MEM as high \
         as possible -- 1.1V typical -- during low power mode) */
#define LOWPOWER_CFG_MEMLOWPOWERMODE_VOLTAGESCALING                                                                    \
    1 /*!< All SRAM instances use "Voltage Scaling" as low power mode technic (it is recommended to set LDO_MEM as low \
         as possible -- down to 0.7V -- during low power mode) */

/**
 * @brief LDO Voltage control in Low Power Modes
 */
#define LOWPOWER_VOLTAGE_LDO_PMU_INDEX       0
#define LOWPOWER_VOLTAGE_LDO_PMU_MASK        (0x1FULL << LOWPOWER_VOLTAGE_LDO_PMU_INDEX)
#define LOWPOWER_VOLTAGE_LDO_MEM_INDEX       5
#define LOWPOWER_VOLTAGE_LDO_MEM_MASK        (0x1FULL << LOWPOWER_VOLTAGE_LDO_MEM_INDEX)
#define LOWPOWER_VOLTAGE_LDO_PMU_BOOST_INDEX 10
#define LOWPOWER_VOLTAGE_LDO_PMU_BOOST_MASK  (0x1FULL << LOWPOWER_VOLTAGE_LDO_PMU_BOOST_INDEX)
#define LOWPOWER_VOLTAGE_LDO_MEM_BOOST_INDEX 15
#define LOWPOWER_VOLTAGE_LDO_MEM_BOOST_MASK  (0x1FULL << LOWPOWER_VOLTAGE_LDO_MEM_BOOST_INDEX)

/* CPU Retention Control*/
#define LOWPOWER_CPURETCTRL_ENA_INDEX           0
#define LOWPOWER_CPURETCTRL_ENA_MASK            (0x1UL << LOWPOWER_CPURETCTRL_ENA_INDEX)
#define LOWPOWER_CPURETCTRL_MEMBASE_INDEX       1
#define LOWPOWER_CPURETCTRL_MEMBASE_MASK        (0x1FFF << LOWPOWER_CPURETCTRL_MEMBASE_INDEX)
#define LOWPOWER_CPURETCTRL_RETDATALENGTH_INDEX 14
#define LOWPOWER_CPURETCTRL_RETDATALENGTH_MASK  (0x3FFUL << LOWPOWER_CPURETCTRL_RETDATALENGTH_INDEX)

/**
 * @brief SRAM Power Control Registers Code
 */
//                                                         LSDEL   DSBDEL   DSB    LS
#define SRAM_PWR_MODE_ACT_CODE (0x6UL) // Active          |  0        1      1      0
#define SRAM_PWR_MODE_LS_CODE  (0xFUL) // Light Sleep     |  1        1      1      1
#define SRAM_PWR_MODE_DS_CODE  (0x8UL) // Deep Sleep      |  1        0      0      0
#define SRAM_PWR_MODE_SD_CODE  (0x9UL) // Shut Down       |  1        0      0      1
#define SRAM_PWR_MODE_MPU_CODE (0xEUL) // Matrix Power Up |  1        1      1      0
#define SRAM_PWR_MODE_FPU_CODE (0xAUL) // Full Power Up   |  1        0      1      0

/**
 * @brief System voltage setting
 */
// All 3 DCDC_POWER_PROFILE_* constants below have been updated after chip characterization on ATE
#define DCDC_POWER_PROFILE_LOW_MAX_FREQ_HZ \
    (100000000UL) /* Maximum System Frequency allowed with DCDC Power Profile LOW */
#define DCDC_POWER_PROFILE_MEDIUM_MAX_FREQ_HZ \
    (135000000UL) /* Maximum System Frequency allowed with DCDC Power Profile MEDIUM */
#define DCDC_POWER_PROFILE_HIGH_MAX_FREQ_HZ \
    (150000000UL) /* Maximum System Frequency allowed with DCDC Power Profile HIGH */

/**
 * @brief Manufacturing Process Parameters
 */
// All 3 PROCESS_* constants below have been updated after chip characterization on ATE
#define PROCESS_NNN_AVG_HZ (14900000UL) /* Average Ring Oscillator value for Nominal (NNN) Manufacturing Process */
#define PROCESS_NNN_STD_HZ \
    (515000UL) /* Standard Deviation Ring Oscillator value for Nominal (NNN) Manufacturing Process */
#define PROCESS_NNN_LIMITS \
    (2UL) /* Nominal (NNN) Manufacturing Process Ring Oscillator values limit (with respect to the Average value) */

#define PROCESS_NNN_MIN_HZ \
    (PROCESS_NNN_AVG_HZ -  \
     (PROCESS_NNN_LIMITS * \
      PROCESS_NNN_STD_HZ)) /* Minimum Ring Oscillator value for Nominal (NNN) Manufacturing Process */

#define PROCESS_NNN_MAX_HZ \
    (PROCESS_NNN_AVG_HZ +  \
     (PROCESS_NNN_LIMITS * \
      PROCESS_NNN_STD_HZ)) /* Maximum Ring OScillator value for Nominal (NNN) Manufacturing Process */

// All 9 VOLTAGE_* constants below have been updated after chip characterization on ATE
#define VOLTAGE_SSS_LOW_MV (1075UL) /* Voltage Settings for : Process=SSS, DCDC Power Profile=LOW */
#define VOLTAGE_SSS_MED_MV (1175UL) /* Voltage Settings for : Process=SSS, DCDC Power Profile=MEDIUM */
#define VOLTAGE_SSS_HIG_MV (1200UL) /* Voltage Settings for : Process=SSS, DCDC Power Profile=HIGH */

#define VOLTAGE_NNN_LOW_MV (1025UL) /* Voltage Settings for : Process=NNN, DCDC Power Profile=LOW */
#define VOLTAGE_NNN_MED_MV (1100UL) /* Voltage Settings for : Process=NNN, DCDC Power Profile=MEDIUM */
#define VOLTAGE_NNN_HIG_MV (1150UL) /* Voltage Settings for : Process=NNN, DCDC Power Profile=HIGH */

#define VOLTAGE_FFF_LOW_MV (1025UL) /* Voltage Settings for : Process=FFF, DCDC Power Profile=LOW */
#define VOLTAGE_FFF_MED_MV (1100UL) /* Voltage Settings for : Process=FFF, DCDC Power Profile=MEDIUM */
#define VOLTAGE_FFF_HIG_MV (1150UL) /* Voltage Settings for : Process=FFF, DCDC Power Profile=HIGH */

/*******************************************************************************
 * Codes
 ******************************************************************************/

/*******************************************************************************
 * LOCAL FUNCTIONS PROTOTYPES
 ******************************************************************************/
static void POWER_WaitLDOCoreInit(void);
static void POWER_SRAMPowerUpDelay(void);
static void POWER_PowerCycleCpu(void);
static void POWER_SetLowPowerMode(LPC_LOWPOWER_T *p_lowpower_cfg);
static uint32_t POWER_WakeUpIOCtrl(uint32_t p_wakeup_io_ctrl);
static uint32_t POWER_SetLdoAoLdoMemVoltage(uint32_t p_lp_mode);
static void POWER_SetSystemPowerProfile(v_system_power_profile_t power_profile);
static void POWER_SetVoltageForProcess(v_system_power_profile_t power_profile);
static lowpower_process_corner_enum POWER_GetPartProcessCorner(void);
static void POWER_SetSystemVoltage(uint32_t system_voltage_mv);
static void POWER_SetSystemClock12MHZ(void);
static void POWER_SRAMSetRegister(power_sram_index_t sram_index, uint32_t power_mode);
static void POWER_SRAMActiveToLightSleep(power_sram_index_t sram_index);
static void POWER_SRAMActiveToDeepSleep(power_sram_index_t sram_index);
static void POWER_SRAMActiveToShutDown(power_sram_index_t sram_index);
static void POWER_SRAMLightSleepToActive(power_sram_index_t sram_index);
static void POWER_SRAMDeepSleepToActive(power_sram_index_t sram_index);
static void POWER_SRAMShutDownToActive(power_sram_index_t sram_index);

/**
 * brief    SoC Power Management Controller initialization
 * return   power_status_t
 */
power_status_t POWER_PowerInit(void)
{
    // To speed up PMC configuration, change PMC clock from 1 MHz to 12 MHz.
    // Set Power Mode to "ACTIVE" (required specially when waking up from DEEP POWER-DOWN)
    PMC->CTRL = (PMC->CTRL | PMC_CTRL_SELCLOCK_MASK) & (~PMC_CTRL_LPMODE_MASK);

    // Check that no time out occured during the hardware wake-up process
    if (PMC->TIMEOUTEVENTS != 0)
    {
        // A least 1 time-out error occured.
        return kPOWER_Status_Fail;
    }

    // Set up wake-up IO pad control source : IOCON ((WAKEUPIO_ENABLE = 0)
    PMC->WAKEUPIOCTRL &= ~PMC_WAKEUPIOCTRL_WAKEUPIO_ENABLE_CTRL_MASK;

    // Set LDO_FLASHNV output voltage
    PMC->LDOFLASHNV = (PMC->LDOFLASHNV & (~PMC_LDOFLASHNV_VADJ_MASK)) | PMC_LDOFLASHNV_VADJ(V_LDO_1P850);

    // Set LDO_EFUSE_PROG output voltage
    PMC->LDOEFUSEPROG = (PMC->LDOEFUSEPROG & (~PMC_LDOEFUSEPROG_VADJ_MASK)) | PMC_LDOEFUSEPROG_VADJ(V_LDO_1P850);

    // Configure the voltage level of LDO CORE Low Power mode (TODO :: :: Temporarily set to 0.9V; target is 0.8 V)*/
    PMC->LDOCORE0 = (PMC->LDOCORE0 & (~PMC_LDOCORE0_LPREGREFSEL_MASK)) | PMC_LDOCORE0_LPREGREFSEL(V_LDOCORE_LP_0P900);

    // SRAM uses Voltage Scaling in all Low Power modes
    PMC->SRAMCTRL = (PMC->SRAMCTRL & (~PMC_SRAMCTRL_SMB_MASK)) | PMC_SRAMCTRL_SMB(3);

    // Enable Analog References fast wake-up in case of wake-up from all low power modes and Hardware Pin reset
    PMC->REFFASTWKUP = PMC->REFFASTWKUP | PMC_REFFASTWKUP_LPWKUP_MASK | PMC_REFFASTWKUP_HWWKUP_MASK;

    // Enable FRO192MHz shut-off glitch suppression.
    // TODO ::  :: Check the Power Consumption Impact of this setting during DEEP-SLEEP and POWER-DOWN.
    //             (Supposed to be 1 to 2uA in typical conditions). If the impe
    //
    ANACTRL->OSC_TESTBUS = 0x1;

    return kPOWER_Status_Success;
}

/**
 * brief
 * return   power_status_t
 */
power_status_t POWER_SetCorePowerSource(power_core_pwr_source_t pwr_source)
{
    uint32_t pmc_reg_data;

    switch (pwr_source)
    {
        case kPOWER_CoreSrcDCDC:
        {
            // Enable DCDC (1st step)
            PMC->CMD = PMC_CMD_DCDCENABLE_MASK;

            // Wait until DCDC is enabled
            while ((PMC->STATUSPWR & PMC_STATUSPWR_DCDCPWROK_MASK) == 0)
                ;

            // Disable LDO Core Low Power Mode (2nd step)
            PMC->CMD = PMC_CMD_LDOCORELOWPWRDISABLE_MASK;

            // Disable LDO Core High Power Mode (3rd step)
            PMC->CMD = PMC_CMD_LDOCOREHIGHPWRDISABLE_MASK;

            // Check PMC Finite State Machines status
            pmc_reg_data = PMC->STATUS & (PMC_STATUS_FSMDCDCENABLE_MASK | PMC_STATUS_FSMLDOCOREHPENABLE_MASK |
                                          PMC_STATUS_FSMLDOCORELPENABLE_MASK | PMC_STATUS_FSMLDOCOREEXPTMRENABLE_MASK);
            if (pmc_reg_data != (PMC_STATUS_FSMDCDCENABLE_MASK | PMC_STATUS_FSMLDOCOREEXPTMRENABLE_MASK))
            {
                // Error : only DCDC and LDO CORE Exponential Timer must both be enabled.
                return (kPOWER_Status_Fail);
            }
        }
        break;

        case kPOWER_CoreSrcLDOCoreHP:
        {
            // Enable LDO Core High Power Mode (1st step)
            PMC->CMD = PMC_CMD_LDOCOREHIGHPWRENABLE_MASK;

            // Note: Once LDO_CORE High Power Mode has been enabled,
            // at least 2us are required before one can reliabily sample
            // the LDO Low Voltage Detectore Output.
            POWER_WaitLDOCoreInit();

            // Wait until LDO CORE High Power is enabled
            while ((PMC->STATUSPWR & PMC_STATUSPWR_LDOCOREPWROK_MASK) == 0)
                ;

            // Disable DCDC (2nd step)
            PMC->CMD = PMC_CMD_DCDCDISABLE_MASK;

            // Disable LDO Core Low Power Mode (3rd step)
            PMC->CMD = PMC_CMD_LDOCORELOWPWRDISABLE_MASK;

            // Check PMC Finite State Machines status
            pmc_reg_data = PMC->STATUS & (PMC_STATUS_FSMDCDCENABLE_MASK | PMC_STATUS_FSMLDOCOREHPENABLE_MASK |
                                          PMC_STATUS_FSMLDOCORELPENABLE_MASK | PMC_STATUS_FSMLDOCOREEXPTMRENABLE_MASK);
            if (pmc_reg_data != PMC_STATUS_FSMLDOCOREHPENABLE_MASK)
            {
                // Error : only LDO CORE High Power mode must both be enabled.
                return (kPOWER_Status_Fail);
            }
        }
        break;

        case kPOWER_CoreSrcLDOCoreLP:
        {
            // Enable LDO Core Low Power Mode (1st step)
            PMC->CMD = PMC_CMD_LDOCORELOWPWRENABLE_MASK;

            // Disable LDO Core High Power Mode (2nd step)
            PMC->CMD = PMC_CMD_LDOCOREHIGHPWRDISABLE_MASK;

            // Disable DCDC (3rd step)
            PMC->CMD = PMC_CMD_DCDCDISABLE_MASK;

            // Check PMC Finite State Machines status
            pmc_reg_data = PMC->STATUS & (PMC_STATUS_FSMDCDCENABLE_MASK | PMC_STATUS_FSMLDOCOREHPENABLE_MASK |
                                          PMC_STATUS_FSMLDOCORELPENABLE_MASK | PMC_STATUS_FSMLDOCOREEXPTMRENABLE_MASK);
            if (pmc_reg_data != (PMC_STATUS_FSMLDOCORELPENABLE_MASK | PMC_STATUS_FSMLDOCOREEXPTMRENABLE_MASK))
            {
                // Error : only LDO CORE Low Power mode and LDO CORE Exponential Timer must both be enabled.
                return (kPOWER_Status_Fail);
            }
        }
        break;

        case kPOWER_CoreSrcExternal:
        {
            // Disable LDO Core Low Power Mode (1st step)
            PMC->CMD = PMC_CMD_LDOCORELOWPWRDISABLE_MASK;

            // Disable LDO Core High Power Mode (2nd step)
            PMC->CMD = PMC_CMD_LDOCOREHIGHPWRDISABLE_MASK;

            // Disable DCDC (3rd step)
            PMC->CMD = PMC_CMD_DCDCDISABLE_MASK;

            // Check PMC Finite State Machines status
            pmc_reg_data = PMC->STATUS & (PMC_STATUS_FSMDCDCENABLE_MASK | PMC_STATUS_FSMLDOCOREHPENABLE_MASK |
                                          PMC_STATUS_FSMLDOCORELPENABLE_MASK | PMC_STATUS_FSMLDOCOREEXPTMRENABLE_MASK);
            if (pmc_reg_data != 0)
            {
                // Error :  All power sources must be disabled.
                return (kPOWER_Status_Fail);
            }
        }
        break;

        default: // Not supported
            return (kPOWER_Status_Fail);

    } // End switch (pwr_source)

    return (kPOWER_Status_Success);
}

/**
 * brief
 * @param   :
 * return   power_core_pwr_source_t
 */
power_core_pwr_source_t POWER_GetCorePowerSource(void)
{
    uint32_t reg_status, reg_statuspwr;

    reg_status    = PMC->STATUS;
    reg_statuspwr = PMC->STATUSPWR;

    if ((reg_statuspwr & PMC_STATUSPWR_DCDCPWROK_MASK) && (reg_status & PMC_STATUS_FSMDCDCENABLE_MASK))
    {
        /* DCDC */
        return (kPOWER_CoreSrcDCDC);
    }
    else
    {
        if ((reg_statuspwr & PMC_STATUSPWR_LDOCOREPWROK_MASK) && (reg_status & PMC_STATUS_FSMLDOCOREHPENABLE_MASK))
        {
            /* LDO_CORE High Power Mode */
            return (kPOWER_CoreSrcLDOCoreHP);
        }
        else
        {
            if (reg_status & PMC_STATUS_FSMLDOCORELPENABLE_MASK)
            {
                /* LDO_CORE Low Power Mode */
                return (kPOWER_CoreSrcLDOCoreLP);
            }
            else
            {
                /* External */
                return (kPOWER_CoreSrcExternal);
            }
        }
    }
}

/**
 * brief
 * return   nothing
 */
power_status_t POWER_CorePowerSourceControl(power_core_pwr_source_t pwr_source, power_core_pwr_state_t pwr_state)
{
    switch (pwr_source)
    {
        case kPOWER_CoreSrcDCDC:
        {
            if (pwr_state == kPOWER_CorePwrEnable)
            {
                // Enable DCDC
                PMC->CMD = PMC_CMD_DCDCENABLE_MASK;

                // Wait until DCDC is enabled
                while ((PMC->STATUSPWR & PMC_STATUSPWR_DCDCPWROK_MASK) == 0)
                    ;

                // Check PMC Finite State Machines status
                if ((PMC->STATUS & PMC_STATUS_FSMDCDCENABLE_MASK) == 0)
                {
                    // Error : DCDC not enabled.
                    return (kPOWER_Status_Fail);
                }
            }
            else
            {
                // Disable DCDC
                PMC->CMD = PMC_CMD_DCDCDISABLE_MASK;

                // Check PMC Finite State Machines status
                if ((PMC->STATUS & PMC_STATUS_FSMDCDCENABLE_MASK) != 0)
                {
                    // Error : DCDC is enabled.
                    return (kPOWER_Status_Fail);
                }
            }
        }
        break;

        case kPOWER_CoreSrcLDOCoreHP:
        {
            if (pwr_state == kPOWER_CorePwrEnable)
            {
                // Enable LDO Core High Power Mode
                PMC->CMD = PMC_CMD_LDOCOREHIGHPWRENABLE_MASK;

                // Note: Once LDO_CORE High Power Mode has been enabled,
                // at least 2us are required before one can reliabily sample
                // the LDO Low Voltage Detector Output.
                POWER_WaitLDOCoreInit();

                // Wait until LDO CORE High Power is enabled
                while ((PMC->STATUSPWR & PMC_STATUSPWR_LDOCOREPWROK_MASK) == 0)
                    ;

                // Check PMC Finite State Machines status
                if ((PMC->STATUS & PMC_STATUS_FSMLDOCOREHPENABLE_MASK) == 0)
                {
                    // Error : LDO CORE High Power mode is not enabled.
                    return (kPOWER_Status_Fail);
                }
            }
            else
            {
                // Disable LDO Core High Power Mode
                PMC->CMD = PMC_CMD_LDOCOREHIGHPWRDISABLE_MASK;

                // Check PMC Finite State Machines status
                if ((PMC->STATUS & PMC_STATUS_FSMLDOCOREHPENABLE_MASK) != 0)
                {
                    // Error : LDO CORE High Power mode is enabled.
                    return (kPOWER_Status_Fail);
                }
            }
        }
        break;

        case kPOWER_CoreSrcLDOCoreLP:
        {
            if (pwr_state == kPOWER_CorePwrEnable)
            {
                // Enable LDO Core Low Power Mode (1st step)
                PMC->CMD = PMC_CMD_LDOCORELOWPWRENABLE_MASK;

                // Check PMC Finite State Machines status
                if ((PMC->STATUS & (PMC_STATUS_FSMLDOCORELPENABLE_MASK | PMC_STATUS_FSMLDOCOREEXPTMRENABLE_MASK)) !=
                    (PMC_STATUS_FSMLDOCORELPENABLE_MASK | PMC_STATUS_FSMLDOCOREEXPTMRENABLE_MASK))
                {
                    // Error : LDO CORE Low Power mode is not enabled.
                    return (kPOWER_Status_Fail);
                }
            }
            else
            {
                // Disable LDO Core Low Power Mode
                PMC->CMD = PMC_CMD_LDOCORELOWPWRDISABLE_MASK;

                // Check PMC Finite State Machines status
                if ((PMC->STATUS & (PMC_STATUS_FSMLDOCORELPENABLE_MASK | PMC_STATUS_FSMLDOCOREEXPTMRENABLE_MASK)) != 0)
                {
                    // Error : LDO CORE Low Power mode is enabled.
                    return (kPOWER_Status_Fail);
                }
            }
        }
        break;

        default: // Not supported
            return (kPOWER_Status_Fail);

    } // End switch (pwr_source)

    return (kPOWER_Status_Success);
}

/**
 * brief
 * return
 */
power_sram_pwr_mode_t POWER_GetSRAMPowerMode(power_sram_index_t sram_index)
{
    power_sram_pwr_mode_t pwr_mode;
    uint32_t state;
    uint32_t sram_ctrl_0 = PMC->SRAMCTRL0;
    uint32_t sram_ctrl_1 = PMC->SRAMCTRL1;

    switch (sram_index)
    {
        case kPOWER_SRAM_IDX_RAM_X0:
        {
            state = (sram_ctrl_0 >> PMC_SRAMCTRL0_RAM_X0_LS_SHIFT) & 0xF;
            break;
        }

        case kPOWER_SRAM_IDX_RAM_00:
        {
            state = (sram_ctrl_0 >> PMC_SRAMCTRL0_RAM_00_LS_SHIFT) & 0xF;
            break;
        }

        case kPOWER_SRAM_IDX_RAM_01:
        {
            state = (sram_ctrl_0 >> PMC_SRAMCTRL0_RAM_01_LS_SHIFT) & 0xF;
            break;
        }

        case kPOWER_SRAM_IDX_RAM_02:
        {
            state = (sram_ctrl_0 >> PMC_SRAMCTRL0_RAM_02_LS_SHIFT) & 0xF;
            break;
        }

        case kPOWER_SRAM_IDX_RAM_03:
        {
            state = (sram_ctrl_0 >> PMC_SRAMCTRL0_RAM_03_LS_SHIFT) & 0xF;
            break;
        }

        case kPOWER_SRAM_IDX_RAM_10:
        {
            state = (sram_ctrl_0 >> PMC_SRAMCTRL0_RAM_10_LS_SHIFT) & 0xF;
            break;
        }

        case kPOWER_SRAM_IDX_RAM_20:
        {
            state = (sram_ctrl_0 >> PMC_SRAMCTRL0_RAM_20_LS_SHIFT) & 0xF;
            break;
        }

        case kPOWER_SRAM_IDX_RAM_30:
        {
            state = (sram_ctrl_0 >> PMC_SRAMCTRL0_RAM_30_LS_SHIFT) & 0xF;
            break;
        }

        case kPOWER_SRAM_IDX_RAM_40:
        {
            state = (sram_ctrl_1 >> PMC_SRAMCTRL1_RAM_40_LS_SHIFT) & 0xF;
            break;
        }

        case kPOWER_SRAM_IDX_RAM_41:
        {
            state = (sram_ctrl_1 >> PMC_SRAMCTRL1_RAM_41_LS_SHIFT) & 0xF;
            break;
        }

        case kPOWER_SRAM_IDX_RAM_42:
        {
            state = (sram_ctrl_1 >> PMC_SRAMCTRL1_RAM_42_LS_SHIFT) & 0xF;
            break;
        }

        case kPOWER_SRAM_IDX_RAM_43:
        {
            state = (sram_ctrl_1 >> PMC_SRAMCTRL1_RAM_43_LS_SHIFT) & 0xF;
            break;
        }

        default:
            // Error
            state = 0x6; // Active.
    }

    switch (state)
    {
        case 0x6:
            pwr_mode = kPOWER_SRAMPwrActive;
            break;

        case 0xF:
            pwr_mode = kPOWER_SRAMPwrLightSleep;
            break;

        case 0x8:
            pwr_mode = kPOWER_SRAMPwrDeepSleep;
            break;

        case 0x9:
            pwr_mode = kPOWER_SRAMPwrShutDown;
            break;

        default:
            pwr_mode = kPOWER_SRAMPwrActive;
    }

    return (pwr_mode);
}

/**
 * brief
 * return
 */
power_status_t POWER_SRAMPowerModeControl(power_sram_bit_t sram_inst, power_sram_pwr_mode_t pwr_mode)
{
    power_sram_pwr_mode_t current_pwr_mode;
    power_sram_index_t sram_index = kPOWER_SRAM_IDX_RAM_X0;

    sram_inst = (power_sram_bit_t)((uint32_t)sram_inst & 0x3FFF); /* Only SRAM from RAM_X0 to RAM_F3 */
    while ((uint32_t)sram_inst != 0)
    {
        // There is a least 1 SRAM instance to be processed
        if ((uint32_t)sram_inst & 0x1)
        {
            // Get current SRAM state
            current_pwr_mode = POWER_GetSRAMPowerMode(sram_index);

            // The SRAM instance Power state must be updated
            switch (current_pwr_mode)
            {
                case kPOWER_SRAMPwrActive:
                { // Active
                    switch (pwr_mode)
                    {
                        case kPOWER_SRAMPwrActive:
                        { // Active ---> Active : there is nothing to do.
                            break;
                        }

                        case kPOWER_SRAMPwrLightSleep:
                        { // Active ---> Light Sleep
                            POWER_SRAMActiveToLightSleep(sram_index);
                            break;
                        }

                        case kPOWER_SRAMPwrDeepSleep:
                        { // Active ---> Deep Sleep
                            POWER_SRAMActiveToDeepSleep(sram_index);
                            break;
                        }

                        case kPOWER_SRAMPwrShutDown:
                        { // Active ---> Shut Down
                            POWER_SRAMActiveToShutDown(sram_index);
                            break;
                        }

                        default:
                            // Do nothing.
                            ;
                    } // switch( pwr_mode )

                    break;
                }

                case kPOWER_SRAMPwrLightSleep:
                { // Light Sleep
                    switch (pwr_mode)
                    {
                        case kPOWER_SRAMPwrActive:
                        { // Light Sleep ---> Active
                            POWER_SRAMLightSleepToActive(sram_index);
                            break;
                        }

                        case kPOWER_SRAMPwrLightSleep:
                        { // Light Sleep ---> Light Sleep : there is nothing to do.
                            break;
                        }

                        default:
                            // Light Sleep ---> Shut Down : FORBIDDEN (error)
                            // Light Sleep ---> Deep Sleep : FORBIDDEN (error)
                            return (kPOWER_Status_Fail);
                    } // switch( pwr_mode )

                    break;
                }

                case kPOWER_SRAMPwrDeepSleep:
                { // Deep Sleep
                    switch (pwr_mode)
                    {
                        case kPOWER_SRAMPwrActive:
                        { // Deep Sleep ---> Active
                            POWER_SRAMDeepSleepToActive(sram_index);
                            break;
                        }

                        case kPOWER_SRAMPwrDeepSleep:
                        { // Deep Sleep ---> Deep Sleep : there is nothing to do.
                            break;
                        }

                        default:
                            // Deep Sleep ---> Shut Down : FORBIDDEN (error)
                            // Deep Sleep ---> Light Sleep : FORBIDDEN (error)
                            return (kPOWER_Status_Fail);
                    } // switch( pwr_mode )

                    break;
                }

                case kPOWER_SRAMPwrShutDown:
                { // Shutdown
                    switch (pwr_mode)
                    {
                        case kPOWER_SRAMPwrActive:
                        { // Shutdown ---> Active
                            POWER_SRAMShutDownToActive(sram_index);
                            break;
                        }

                        case kPOWER_SRAMPwrShutDown:
                        { // Shutdown ---> Shut Down : there is nothing to do.
                            break;
                        }

                        default:
                            // Shutdown ---> Deep Sleep : FORBIDDEN (error)
                            // Shutdown ---> Light Sleep : FORBIDDEN (error)
                            return (kPOWER_Status_Fail);
                    } // switch( pwr_mode )

                    break;
                }

                default:
                    // Do nothing
                    ;
            } // switch( current_pwr_mode )
        }     // if ( (uint32_t)sram_inst & 0x1 )

        // Move to next SRAM index
        sram_inst  = (power_sram_bit_t)((uint32_t)sram_inst >> 1);
        sram_index = (power_sram_index_t)((uint32_t)sram_index + 1);
    } // while ((uint32_t)sram_inst != 0 )

    return (kPOWER_Status_Success);
}

/**
 * @brief   Configures and enters in SLEEP low power mode
 * @return  Nothing
 */
void POWER_EnterSleep(void)
{
    uint32_t pmsk;
    pmsk = __get_PRIMASK();             /* Save CORTEX-M33 interrupt configuration */
    __disable_irq();                    /* Disable all interrupts */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk; /* CORTEX-M33 uses "Sleep" mode */
    __WFI();                            /* CORTEX-M33 enters "Sleep" mode */
    __set_PRIMASK(pmsk);                /* Restore CORTEX-M33 interrupt configuration (after wake up) */
}

/**
 * brief    PMC Deep Sleep function call
 * return   nothing
 */
void POWER_EnterDeepSleep(uint32_t exclude_from_pd[2],
                          uint32_t sram_retention_ctrl,
                          uint32_t wakeup_interrupts[4],
                          uint32_t hardware_wake_ctrl)
{
    LPC_LOWPOWER_T lv_low_power_mode_cfg; /* Low Power Mode configuration structure */
    uint32_t pmc_reset_ctrl;

    /* Clear Low Power Mode configuration variable */
    memset(&lv_low_power_mode_cfg, 0x0, sizeof(LPC_LOWPOWER_T));

    /* Configure Low Power Mode configuration variable */
    lv_low_power_mode_cfg.CFG = LOWPOWER_CFG_LPMODE_DEEPSLEEP << LOWPOWER_CFG_LPMODE_INDEX; /* DEEPSLEEP mode */

    /* Make sure LDO MEM & Analog references will stay powered, Shut down ROM & LDO Flash NV */
    lv_low_power_mode_cfg.PDCTRL[0] =
        (~exclude_from_pd[0] & ~kPDRUNCFG_PD_LDOMEM & ~kPDRUNCFG_PD_BIAS) | kPDRUNCFG_PD_ROM | kPDRUNCFG_PD_LDOFLASHNV;
    lv_low_power_mode_cfg.PDCTRL[1] = ~exclude_from_pd[1];

    // Voltage control in DeepSleep Low Power Modes
    lv_low_power_mode_cfg.VOLTAGE = POWER_SetLdoAoLdoMemVoltage(LOWPOWER_CFG_LPMODE_DEEPSLEEP);

    // SRAM retention control during DEEP-SLEEP
    lv_low_power_mode_cfg.SRAMRETCTRL = sram_retention_ctrl & kPOWER_SRAM_DSLP_MASK;

    /* Interrupts that allow DMA transfers with Flexcomm without waking up the Processor */
    if (hardware_wake_ctrl & (LOWPOWER_HWWAKE_PERIPHERALS | LOWPOWER_HWWAKE_DMIC | LOWPOWER_HWWAKE_SDMA0 |
                              LOWPOWER_HWWAKE_SDMA1 | LOWPOWER_HWWAKE_DAC))
    {
        lv_low_power_mode_cfg.HWWAKE = (hardware_wake_ctrl & ~LOWPOWER_HWWAKE_FORCED) | LOWPOWER_HWWAKE_ENABLE_FRO192M;
    }

    // @NOTE Niobe4mini: update with new BOD reset enable management
    pmc_reset_ctrl = PMC->RESETCTRL;
    if ((pmc_reset_ctrl & (PMC_RESETCTRL_BODCORERESETENA_SECURE_MASK | PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_MASK)) ==
        ((0x1 << PMC_RESETCTRL_BODCORERESETENA_SECURE_SHIFT) | (0x1 << PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_SHIFT)))
    {
        /* BoD CORE reset is activated, so make sure BoD Core and Biasing won't be shutdown */
        lv_low_power_mode_cfg.PDCTRL[0] &= ~kPDRUNCFG_PD_BODCORE & ~kPDRUNCFG_PD_BIAS;
    }

    if ((pmc_reset_ctrl &
         (PMC_RESETCTRL_BODVDDMAINRESETENA_SECURE_MASK | PMC_RESETCTRL_BODVDDMAINRESETENA_SECURE_DP_MASK)) ==
        ((0x1 << PMC_RESETCTRL_BODVDDMAINRESETENA_SECURE_SHIFT) |
         (0x1 << PMC_RESETCTRL_BODVDDMAINRESETENA_SECURE_DP_SHIFT)))
    {
        /* BoD VDDMAIN reset is activated, so make sure BoD VDDMAIN and Biasing won't be shutdown */
        lv_low_power_mode_cfg.PDCTRL[0] &= ~kPDRUNCFG_PD_BODVDDMAIN & ~kPDRUNCFG_PD_BIAS;
    }

    /* CPU Wake up & Interrupt sources control */
    lv_low_power_mode_cfg.WAKEUPSRC[0] = lv_low_power_mode_cfg.WAKEUPINT[0] = wakeup_interrupts[0];
    lv_low_power_mode_cfg.WAKEUPSRC[1] = lv_low_power_mode_cfg.WAKEUPINT[1] = wakeup_interrupts[1];
    lv_low_power_mode_cfg.WAKEUPSRC[2] = lv_low_power_mode_cfg.WAKEUPINT[2] = wakeup_interrupts[2];
    lv_low_power_mode_cfg.WAKEUPSRC[3] = lv_low_power_mode_cfg.WAKEUPINT[3] = wakeup_interrupts[3];

    /* Enter low power mode */
    POWER_SetLowPowerMode(&lv_low_power_mode_cfg);
}

/**
 * brief    PMC power Down function call
 * return   nothing
 */
void POWER_EnterPowerDown(uint32_t exclude_from_pd[1],
                          uint32_t sram_retention_ctrl,
                          uint32_t wakeup_interrupts[4],
                          uint32_t cpu_retention_addr)
{
    LPC_LOWPOWER_T lv_low_power_mode_cfg; /* Low Power Mode configuration structure */

    // Clear Low Power Mode configuration variable
    memset(&lv_low_power_mode_cfg, 0x0, sizeof(LPC_LOWPOWER_T));

    // Configure Low Power Mode configuration variable : POWER DOWN mode
    lv_low_power_mode_cfg.CFG = LOWPOWER_CFG_LPMODE_POWERDOWN << LOWPOWER_CFG_LPMODE_INDEX;

    // Only FRO32K, XTAL32K, FRO1M, COMP, BIAS and VREF can stay powered during POWERDOWN.
    // LDO_MEM is enabled (because at least 1 SRAM instance will be required - for CPU state retention -)
    lv_low_power_mode_cfg.PDCTRL[0] = ~(exclude_from_pd[0] | kPDRUNCFG_PD_LDOMEM);
    lv_low_power_mode_cfg.PDCTRL[1] = 0xFFFFFFFF;

    // Force Bias activation if Analog Comparator is required, otherwise, disable it.
    if ((lv_low_power_mode_cfg.PDCTRL[0] & kPDRUNCFG_PD_COMP) == 0)
    {
        // Analog Comparator is required du ring power-down: Enable Biasing
        lv_low_power_mode_cfg.PDCTRL[0] = lv_low_power_mode_cfg.PDCTRL[0] & (~kPDRUNCFG_PD_BIAS);
    }
    else
    {
        // Analog Comparator is not required du ring power-down: Disable Biasing
        lv_low_power_mode_cfg.PDCTRL[0] = lv_low_power_mode_cfg.PDCTRL[0] | kPDRUNCFG_PD_BIAS;
    }

// SRAM retention control during POWER-DOWN

// Depending on where the user wants to locate the CPU state retention data,
// the associated SRAM instance will be automatically put in retention mode.
// The boundaries are defined in such a way that the area where the CPU state
// will be retained does not cross any SRAM instance boundary.
// Per hardware design, 1540 bytes are necessary to store the whole CPU state
#define RAM_00_CPU_RET_ADDR_MIN 0x20000000UL // RAM_00 start address
#define RAM_00_CPU_RET_ADDR_MAX 0x200009FCUL // RAM_00 start address + 1540 - 1
#define RAM_01_CPU_RET_ADDR_MIN 0x20001000UL // RAM_01 start address
#define RAM_01_CPU_RET_ADDR_MAX 0x200019FCUL // RAM_01 start address + 1540 - 1
#define RAM_02_CPU_RET_ADDR_MIN 0x20002000UL // RAM_02 start address
#define RAM_02_CPU_RET_ADDR_MAX 0x200029FCUL // RAM_02 start address + 1540 - 1
#define RAM_03_CPU_RET_ADDR_MIN 0x20003000UL // RAM_03 start address
#define RAM_03_CPU_RET_ADDR_MAX 0x200039FCUL // RAM_03 start address + 1540 - 1

    if ((cpu_retention_addr >= RAM_00_CPU_RET_ADDR_MIN) && (cpu_retention_addr <= RAM_00_CPU_RET_ADDR_MAX))
    {
        // Inside RAM_00
        sram_retention_ctrl |= kPOWER_SRAM_RAM_00;
    }
    else
    {
        if ((cpu_retention_addr >= RAM_01_CPU_RET_ADDR_MIN) && (cpu_retention_addr <= RAM_01_CPU_RET_ADDR_MAX))
        {
            // Inside RAM_01
            sram_retention_ctrl |= kPOWER_SRAM_RAM_01;
        }
        else
        {
            if ((cpu_retention_addr >= RAM_02_CPU_RET_ADDR_MIN) && (cpu_retention_addr <= RAM_02_CPU_RET_ADDR_MAX))
            {
                // Inside RAM_02
                sram_retention_ctrl |= kPOWER_SRAM_RAM_02;
            }
            else
            {
                if ((cpu_retention_addr >= RAM_03_CPU_RET_ADDR_MIN) && (cpu_retention_addr <= RAM_03_CPU_RET_ADDR_MAX))
                {
                    // Inside RAM_03
                    sram_retention_ctrl |= kPOWER_SRAM_RAM_03;
                }
                else
                {
                    // Error! Therefore, we locate the retention area in RAM_00
                    cpu_retention_addr = 0x20000000UL;
                    sram_retention_ctrl |= kPOWER_SRAM_RAM_00;
                }
            }
        }
    }

    lv_low_power_mode_cfg.SRAMRETCTRL = sram_retention_ctrl & kPOWER_SRAM_PDWN_MASK;

    // Voltage control in Low Power Modes
    // The Memories Voltage settings below are for voltage scaling
    lv_low_power_mode_cfg.VOLTAGE = POWER_SetLdoAoLdoMemVoltage(LOWPOWER_CFG_LPMODE_POWERDOWN);

    /* CPU0 retention Address */
    lv_low_power_mode_cfg.CPURETCTRL = ((cpu_retention_addr >> 1) | LOWPOWER_CPURETCTRL_ENA_MASK) &
                                       (LOWPOWER_CPURETCTRL_MEMBASE_MASK | LOWPOWER_CPURETCTRL_ENA_MASK);

    /* CPU Wake up & Interrupt sources control */
    lv_low_power_mode_cfg.WAKEUPSRC[0] = lv_low_power_mode_cfg.WAKEUPINT[0] =
        wakeup_interrupts[0] & (WAKEUP_GPIO_GLOBALINT0 | WAKEUP_GPIO_GLOBALINT1 | WAKEUP_FLEXCOMM3 | WAKEUP_ACMP |
                                WAKEUP_RTC_ALARM_WAKEUP | WAKEUP_WAKEUP_MAILBOX);
    lv_low_power_mode_cfg.WAKEUPSRC[1] = lv_low_power_mode_cfg.WAKEUPINT[1] =
        wakeup_interrupts[1] & WAKEUP_OS_EVENT_TIMER;
    lv_low_power_mode_cfg.WAKEUPSRC[2] = lv_low_power_mode_cfg.WAKEUPINT[2] = 0UL;
    lv_low_power_mode_cfg.WAKEUPSRC[3] = lv_low_power_mode_cfg.WAKEUPINT[3] = wakeup_interrupts[3] & WAKEUP_ITRC;

    /* Enter low power mode */
    POWER_SetLowPowerMode(&lv_low_power_mode_cfg);
}

/**
 * brief    PMC Deep Power-Down function call
 * return   nothing
 */
void POWER_EnterDeepPowerDown(uint32_t exclude_from_pd[1],
                              uint32_t sram_retention_ctrl,
                              uint32_t wakeup_interrupts[2],
                              uint32_t wakeup_io_ctrl)
{
    LPC_LOWPOWER_T lv_low_power_mode_cfg; /* Low Power Mode configuration structure */

    // Clear Low Power Mode configuration variable
    memset(&lv_low_power_mode_cfg, 0x0, sizeof(LPC_LOWPOWER_T));

    // Configure Low Power Mode configuration variable : DEEP POWER-DOWN mode
    lv_low_power_mode_cfg.CFG = LOWPOWER_CFG_LPMODE_DEEPPOWERDOWN << LOWPOWER_CFG_LPMODE_INDEX;

    // Note: only FRO32K, XTAL32K, FRO1M and LDO_MEM can stay powered during DEEP POWER-DOWN
    lv_low_power_mode_cfg.PDCTRL[0] = ~exclude_from_pd[0];
    lv_low_power_mode_cfg.PDCTRL[1] = 0xFFFFFFFF;

    // SRAM retention control during DEEP POWER-DOWN
    // RAM_X0, RAM_02 and RAM_03 excluded: they are used by ROM Boot code
    sram_retention_ctrl               = sram_retention_ctrl & kPOWER_SRAM_DPWD_MASK;
    lv_low_power_mode_cfg.SRAMRETCTRL = sram_retention_ctrl;

    // Sanity check: if retention is required for any SRAM instance other than RAM_00, make sure LDO MEM will stay
    // powered */
    if ((sram_retention_ctrl & (~kPOWER_SRAM_RAM_00)) != 0)
    {
        // SRAM retention is required : enable LDO_MEM
        lv_low_power_mode_cfg.PDCTRL[0] &= ~kPDRUNCFG_PD_LDOMEM;
    }
    else
    {
        // No SRAM retention required : disable LDO_MEM
        lv_low_power_mode_cfg.PDCTRL[0] |= kPDRUNCFG_PD_LDOMEM;
    }

    // Voltage control in Low Power Modes
    // The Memories Voltage settings below are for voltage scaling
    lv_low_power_mode_cfg.VOLTAGE = POWER_SetLdoAoLdoMemVoltage(LOWPOWER_CFG_LPMODE_DEEPPOWERDOWN);

    // Wake up sources control
    lv_low_power_mode_cfg.WAKEUPSRC[0] = lv_low_power_mode_cfg.WAKEUPINT[0] =
        wakeup_interrupts[0] &
        WAKEUP_RTC_ALARM_WAKEUP; /* CPU Wake up sources control : only WAKEUP_RTC_LITE_ALARM_WAKEUP */
    lv_low_power_mode_cfg.WAKEUPSRC[1] = lv_low_power_mode_cfg.WAKEUPINT[1] =
        wakeup_interrupts[1] & WAKEUP_OS_EVENT_TIMER; /* CPU Wake up sources control : only WAKEUP_OS_EVENT_TIMER */
    lv_low_power_mode_cfg.WAKEUPSRC[2] = lv_low_power_mode_cfg.WAKEUPINT[2] = 0UL;
    lv_low_power_mode_cfg.WAKEUPSRC[3] = lv_low_power_mode_cfg.WAKEUPINT[3] = 0UL;

    /* Wake up I/O sources */
    lv_low_power_mode_cfg.WAKEUPIOSRC = POWER_WakeUpIOCtrl(wakeup_io_ctrl);

    /* Enter low power mode */
    POWER_SetLowPowerMode(&lv_low_power_mode_cfg);

    /*** We'll reach this point ONLY and ONLY if the DEEPPOWERDOWN has not been taken (for instance because an RTC or
     * OSTIMER interrupt is pending) ***/
}

/**
 * @brief   Configures the 5 wake-up pins to wake up the part in DEEP-SLEEP and POWER-DOWN low power modes.
 * @param   wakeup_io_cfg_src : for all wake-up pins : indicates if the config is from IOCON or from PMC.
 * @param   wakeup_io_ctrl: the 5 wake-up pins configurations (see "LOWPOWER_WAKEUPIOSRC_*" #defines)

 * @return  Nothing
 *
 *          !!! IMPORTANT NOTES :
 *           1 - To be called just before POWER_EnterDeepSleep() or POWER_EnterPowerDown().
 */
/**
 * brief    PMC Deep Power-Down function call
 * return   nothing
 */
void POWER_SetWakeUpPins(uint32_t wakeup_io_cfg_src, uint32_t wakeup_io_ctrl)
{
    if (wakeup_io_cfg_src == LOWPOWER_WAKEUPIO_CFG_SRC_IOCON)
    {
        /* All wake-up pins controls are coming from IOCON */

        wakeup_io_ctrl = wakeup_io_ctrl | LOWPOWER_WAKEUPIO_PIO0_DISABLEPULLUPDOWN_MASK |
                         LOWPOWER_WAKEUPIO_PIO1_DISABLEPULLUPDOWN_MASK | LOWPOWER_WAKEUPIO_PIO2_DISABLEPULLUPDOWN_MASK |
                         LOWPOWER_WAKEUPIO_PIO3_DISABLEPULLUPDOWN_MASK |
                         LOWPOWER_WAKEUPIO_PIO4_DISABLEPULLUPDOWN_MASK; /* Make sure IOCON is not modified inside
                                                                           POWER_WakeUpIOCtrl */

        PMC->WAKEUPIOCTRL = POWER_WakeUpIOCtrl(wakeup_io_ctrl) & (~PMC_WAKEUPIOCTRL_WAKEUPIO_ENABLE_CTRL_MASK);
    }
    else
    {
        /* All wake-up pins controls are coming from PMC */
        PMC->WAKEUPIOCTRL = POWER_WakeUpIOCtrl(wakeup_io_ctrl) | PMC_WAKEUPIOCTRL_WAKEUPIO_ENABLE_CTRL_MASK;
    }

    /* Release Wake up I/O reset (WAKEUPIO_RSTN = 1)*/
    PMC->WAKEUPIOCTRL |= PMC_WAKEUPIOCTRL_WAKEUPIO_RSTN_MASK;
}

void POWER_GetWakeUpCause(power_reset_cause_t *reset_cause,
                          power_boot_mode_t *boot_mode,
                          power_wakeup_pin_t *wakeup_pin_cause)
{
    uint32_t reset_cause_reg;
    uint32_t boot_mode_reg;
    uint32_t wakeupio_cause_reg;

    boot_mode_reg = (PMC->STATUS & PMC_STATUS_BOOTMODE_MASK) >> PMC_STATUS_BOOTMODE_SHIFT;

    switch (boot_mode_reg)
    {
        case 1:
            /* DEEP-SLEEP */
            *boot_mode = kBOOT_MODE_LP_DEEP_SLEEP;
            break;
        case 2:
            /* POWER-DOWN */
            *boot_mode = kBOOT_MODE_LP_POWER_DOWN;
            break;
        case 3:
            /* DEEP-POWER-DOWN */
            *boot_mode = kBOOT_MODE_LP_DEEP_POWER_DOWN;
            break;
        default:
            /* All non Low Power Mode wake-up */
            *boot_mode = kBOOT_MODE_POWER_UP;
    }

    wakeupio_cause_reg = PMC->WAKEIOCAUSE;

    if (boot_mode_reg == 0)
    {
        /* POWER-UP: Power On Reset, Pin reset, Brown Out Detectors, Software Reset:
         * PMC has been reset, so wake up pin event not expected to have happened. */
        *wakeup_pin_cause = kWAKEUP_PIN_NONE;
    }
    else
    {
        switch (((wakeupio_cause_reg & PMC_WAKEIOCAUSE_WAKEUPIO_EVENTS_ORDER_MASK) >>
                 PMC_WAKEIOCAUSE_WAKEUPIO_EVENTS_ORDER_SHIFT))
        {
            case 0x0:
                *wakeup_pin_cause = kWAKEUP_PIN_NONE;
                break;
            case 0x1:
                *wakeup_pin_cause = kWAKEUP_PIN_0;
                break;
            case 0x2:
                *wakeup_pin_cause = kWAKEUP_PIN_1;
                break;
            case 0x4:
                *wakeup_pin_cause = kWAKEUP_PIN_2;
                break;
            case 0x8:
                *wakeup_pin_cause = kWAKEUP_PIN_3;
                break;
            case 0x10:
                *wakeup_pin_cause = kWAKEUP_PIN_4;
                break;
            default:
                /* Mutiple */
                *wakeup_pin_cause = kWAKEUP_PIN_MULTIPLE;
                break;
        }
    }

    reset_cause_reg = PMC->AOREG1;

    /*
     * Prioritize interrupts source with respect to how critical they are.
     */
    if (reset_cause_reg & PMC_AOREG1_CDOGRESET_MASK)
    { /* Code Watchdog Reset */
        *reset_cause = kRESET_CAUSE_CDOGRESET;
    }
    else
    {
        if (reset_cause_reg & PMC_AOREG1_WDTRESET_MASK)
        { /* Watchdog Timer Reset */
            *reset_cause = kRESET_CAUSE_WDTRESET;
        }
        else
        {
            if (reset_cause_reg & PMC_AOREG1_SYSTEMRESET_MASK)
            { /* ARM System Reset */
                *reset_cause = kRESET_CAUSE_ARMSYSTEMRESET;
            }
            else
            {
                if (boot_mode_reg != 3) /* POWER-UP: Power On Reset, Pin reset, Brown Out Detectors, Software Reset,
                                           DEEP-SLEEP and POWER-DOWN */
                {
                    /*
                     * Prioritise Reset causes, starting from the strongest (Power On Reset)
                     */
                    if (reset_cause_reg & PMC_AOREG1_POR_MASK)
                    { /* Power On Reset */
                        *reset_cause = kRESET_CAUSE_POR;
                    }
                    else
                    {
                        if (reset_cause_reg & PMC_AOREG1_BODRESET_MASK)
                        { /* Brown-out Detector reset (either BODVBAT or BODCORE) */
                            *reset_cause = kRESET_CAUSE_BODRESET;
                        }
                        else
                        {
                            if (reset_cause_reg & PMC_AOREG1_PADRESET_MASK)
                            { /* Hardware Pin Reset */
                                *reset_cause = kRESET_CAUSE_PADRESET;
                            }
                            else
                            {
                                if (reset_cause_reg & PMC_AOREG1_SWRRESET_MASK)
                                { /* Software triggered Reset */
                                    *reset_cause = kRESET_CAUSE_SWRRESET;
                                }
                                else
                                { /* Unknown Reset Cause (shall never occur) */
                                    *reset_cause = kRESET_CAUSE_NOT_DETERMINISTIC;
                                }
                            }
                        }
                    }
                }
                else /* boot_mode_reg == 3 : DEEP-POWER-DOWN */
                {
                    switch (((reset_cause_reg & PMC_AOREG1_DPD_EVENTS_ORDER_MASK) >> PMC_AOREG1_DPD_EVENTS_ORDER_SHIFT))
                    {
                        case 1:
                            *reset_cause = kRESET_CAUSE_DPDRESET_WAKEUPIO;
                            break;
                        case 2:
                            *reset_cause = kRESET_CAUSE_DPDRESET_RTC;
                            break;
                        case 3:
                            *reset_cause = kRESET_CAUSE_DPDRESET_WAKEUPIO_RTC;
                            break;
                        case 4:
                            *reset_cause = kRESET_CAUSE_DPDRESET_OSTIMER;
                            break;
                        case 5:
                            *reset_cause = kRESET_CAUSE_DPDRESET_WAKEUPIO_OSTIMER;
                            break;
                        case 6:
                            *reset_cause = kRESET_CAUSE_DPDRESET_RTC_OSTIMER;
                            break;
                        case 7:
                            *reset_cause = kRESET_CAUSE_DPDRESET_WAKEUPIO_RTC_OSTIMER;
                            break;
                        default:
                            /* Unknown Reset Cause (shall not occur) */
                            *reset_cause = kRESET_CAUSE_NOT_DETERMINISTIC;
                            break;
                    }
                } // if ( boot_mode != 3 )

            } // if ( reset_cause_reg & PMC_AOREG1_CDOGRESET_MASK )

        } // if ( reset_cause_reg & PMC_AOREG1_WDTRESET_MASK )

    } // if ( reset_cause_reg & PMC_AOREG1_SYSTEMRESET_MASK )
}

/**
 * @brief             Described in fsl_common.h
 * @param
 * @return
 */
void POWER_SetVoltageForFreq(uint32_t system_freq_hz)
{
    if (system_freq_hz <= DCDC_POWER_PROFILE_LOW_MAX_FREQ_HZ)
    {
        /* [0 Hz - DCDC_POWER_PROFILE_LOW_MAX_FREQ_HZ Hz] */
        POWER_SetSystemPowerProfile(V_SYSTEM_POWER_PROFILE_LOW);
        POWER_SetVoltageForProcess(V_SYSTEM_POWER_PROFILE_LOW);
    }
    else
    {
        if (system_freq_hz <= DCDC_POWER_PROFILE_MEDIUM_MAX_FREQ_HZ)
        {
            /* ]DCDC_POWER_PROFILE_LOW_MAX_FREQ_HZ Hz - DCDC_POWER_PROFILE_MEDIUM_MAX_FREQ_HZ Hz] */
            POWER_SetSystemPowerProfile(V_SYSTEM_POWER_PROFILE_MEDIUM);
            POWER_SetVoltageForProcess(V_SYSTEM_POWER_PROFILE_MEDIUM);
        }
        else
        {
            /* > DCDC_POWER_PROFILE_MEDIUM_MAX_FREQ_HZ Hz */
            POWER_SetSystemPowerProfile(V_SYSTEM_POWER_PROFILE_HIGH);
            POWER_SetVoltageForProcess(V_SYSTEM_POWER_PROFILE_HIGH);
        }
    }
}

/**
 * @brief	Wait at least 2us.
 * @param	None
 * @return	Nothing
 */

static void POWER_WaitLDOCoreInit(void)
{
    /*
     * Note: Once LDO_CORE High Power Mode has been enabled,
     * at least 2us are required before one can reliabily sample
     * the LDO Low Voltage Detectore Output.
     * The PMC clock being 12 MHz, with at least 5 dummy read
     * operations, it is guaranteed by design that, whatever the
     * System/CPU clock frequency (up to 200 MHz).
     */

    volatile uint32_t reg_data;
    for (uint32_t i = 0; i < 5; i++)
        reg_data = PMC->STATUSPWR; /* Dummy Read */
    (void)reg_data;
}

/**
 * @brief	Wait at least 2us.
 * @param	None
 * @return	Nothing
 */

static void POWER_SRAMPowerUpDelay(void)
{
    /*
     * Note: Wait about 1 us
     * The PMC clock being 12 MHz, with at least 3 dummy read
     * operations, it is guaranteed by design that when this ,
     * function is called, at least 1 us will elapse,
     * whatever the System/CPU clock frequency (up to 200 MHz).
     */

    volatile uint32_t reg_data;
    for (uint32_t i = 0; i < 3; i++)
        reg_data = PMC->STATUSPWR; /* Dummy Read */
    (void)reg_data;
}

/**
 * @brief	Shut off the Flash and execute the _WFI(), then power up the Flash after wake-up event
 * @param	None
 * @return	Nothing
 */

static void POWER_PowerCycleCpu(void)
{
    /* Switch System Clock to FRO12Mhz (the configuration before calling this function will not be restored back) */
    POWER_SetSystemClock12MHZ();

    /* Configure the Cortex-M33 in Deep Sleep mode */
    SCB->SCR = SCB->SCR | SCB_SCR_SLEEPDEEP_Msk;

    /* Enter in low power mode */
    __WFI();

    /* Configure the Cortex-M33 in Active mode */
    SCB->SCR = SCB->SCR & (~SCB_SCR_SLEEPDEEP_Msk);
};

/**
 * @brief	Configures and enters in low power mode
 * @param	: p_lowpower_cfg
 * @return	Nothing
 */
static void POWER_SetLowPowerMode(LPC_LOWPOWER_T *p_lowpower_cfg)
{
    uint32_t i, primask, reg_data;
    uint32_t cpu0_nmi_enable;
    uint32_t cpu0_int_enable[4];
    uint32_t analog_ctrl_regs[7]; /* To store Analog Controller Registers */
    uint32_t vref_regs[4];        /* To store VREF Registers */
    uint32_t fmccr_reg;           /* FMC Configuration Register */

    /* Save FMC configuration */
    fmccr_reg = SYSCON->FMCCR;

    cpu0_nmi_enable = SYSCON->NMISRC & SYSCON_NMISRC_NMIENCPU0_MASK; /* Save the configuration of the NMI Register */
    SYSCON->NMISRC &= ~SYSCON_NMISRC_NMIENCPU0_MASK;                 /* Disable NMI of CPU0 */

    // Save the configuration of the CPU interrupt enable Registers (because they are overwritten in
    // POWER_SetLowPowerMode)
    for (i = 0; i < 4; i++)
    {
        cpu0_int_enable[i] = NVIC->ISER[i];
    }

    uint32_t low_power_mode = (p_lowpower_cfg->CFG & LOWPOWER_CFG_LPMODE_MASK) >> LOWPOWER_CFG_LPMODE_INDEX;

    /* Set the Low power mode.*/
    PMC->CTRL = (PMC->CTRL & (~PMC_CTRL_LPMODE_MASK)) | PMC_CTRL_LPMODE(low_power_mode);

    /* SRAM in Retention modes */
    PMC->SRAMRETCTRL = p_lowpower_cfg->SRAMRETCTRL;

    /* Configure the voltage level of the Always On domain, Memories LDO */
    PMC->LDOPMU = (PMC->LDOPMU & (~PMC_LDOPMU_VADJ_PWD_MASK) & (~PMC_LDOPMU_VADJ_BOOST_PWD_MASK)) |
                  PMC_LDOPMU_VADJ_PWD((p_lowpower_cfg->VOLTAGE & LOWPOWER_VOLTAGE_LDO_PMU_MASK) >>
                                      LOWPOWER_VOLTAGE_LDO_PMU_INDEX) |
                  PMC_LDOPMU_VADJ_BOOST_PWD((p_lowpower_cfg->VOLTAGE & LOWPOWER_VOLTAGE_LDO_PMU_BOOST_MASK) >>
                                            LOWPOWER_VOLTAGE_LDO_PMU_BOOST_INDEX);

    PMC->LDOMEM = (PMC->LDOMEM & (~PMC_LDOMEM_VADJ_PWD_MASK) & (~PMC_LDOMEM_VADJ_BOOST_PWD_MASK)) |
                  PMC_LDOMEM_VADJ_PWD((p_lowpower_cfg->VOLTAGE & LOWPOWER_VOLTAGE_LDO_MEM_MASK) >>
                                      LOWPOWER_VOLTAGE_LDO_MEM_INDEX) |
                  PMC_LDOMEM_VADJ_BOOST_PWD((p_lowpower_cfg->VOLTAGE & LOWPOWER_VOLTAGE_LDO_MEM_BOOST_MASK) >>
                                            LOWPOWER_VOLTAGE_LDO_MEM_BOOST_INDEX);

    /*
     * Enable wake up interrupt.
     * Rational : we enable each interrupt (NVIC->ISER) that can wake up the CPU here (before the __disable_irq()
     * below): Hence, if an interrupt was pending and not treated before (for any reason), the CPU will jump to that
     *            interrupt handler before trying to enter the low power mode.
     *            VERY IMPORTANT : Also, any interrupt set in NVIC->ISER, even though __disable_irq(), will make the CPU
     *                             go out of the Deep Sleep mode.
     */
    for (i = 0; i < 4; i++)
    {
        NVIC->ISER[i]      = p_lowpower_cfg->WAKEUPINT[i]; /* Enable wake-up interrupt */
        SYSCON->STARTER[i] = p_lowpower_cfg->WAKEUPSRC[i]; /* Enable wake-up sources */
    }

    /* Save the configuration of the Priority Mask Register */
    primask = __get_PRIMASK();

    switch (low_power_mode)
    {
        case LOWPOWER_CFG_LPMODE_DEEPSLEEP:
        {
            /* DEEP SLEEP power mode */

            uint32_t bod_core_trglvl; /* BoD Core trigger level */
            uint32_t css_ctrl, syscon_css_clk_ctrl, syscon_css_clk_pclk_hclk;
            uint32_t syscon_autoclkgateoverride_reg; /* AUTOCLKGATEOVERRIDE Configuration Register */

            /* Analog Modules to be shut off */
            PMC->PDSLEEPCFG0 = p_lowpower_cfg->PDCTRL[0];
            PMC->PDSLEEPCFG1 = p_lowpower_cfg->PDCTRL[1];

            /* Saving AUTOCLKGATEOVERRIDE register*/
            syscon_autoclkgateoverride_reg = SYSCON->AUTOCLKGATEOVERRIDE;

            /* DMA transactions with Flexcomm during DEEP SLEEP */
            SYSCON->HARDWARESLEEP = p_lowpower_cfg->HWWAKE;
            /* Enable autoclockgating on SDMA0 and SDMA1 during DeepSleep*/
            SYSCON->AUTOCLKGATEOVERRIDE =
                0xC0DE0000 | (syscon_autoclkgateoverride_reg &
                              (~(SYSCON_AUTOCLKGATEOVERRIDE_SDMA1_MASK | SYSCON_AUTOCLKGATEOVERRIDE_SDMA0_MASK)));

            /* Make sure DEEP POWER DOWN reset is disabled */
            PMC->RESETCTRL = PMC->RESETCTRL & (~PMC_RESETCTRL_DPDWAKEUPRESETENABLE_MASK);

            /* Adjust BoD Core Trip point . Currently set to 700 mV. TODO :: :: Check this value. */
            reg_data        = PMC->BODCORE;
            bod_core_trglvl = (reg_data & PMC_BODCORE_TRIGLVL_MASK) >> PMC_BODCORE_TRIGLVL_SHIFT;
            PMC->BODCORE    = (reg_data & (~PMC_BODCORE_TRIGLVL_MASK)) | PMC_BODCORE_TRIGLVL(kPOWER_BodCoreLevel700mv);

            // CSSV2
            {
                syscon_css_clk_ctrl = SYSCON_CSS_CLK_CTRL_REG & (1U << 1);

                css_ctrl = 0U;

#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
                syscon_css_clk_pclk_hclk = SYSCON->AHBCLKCTRL2 & (1U << 18);
                /* Check if CSS is NOT in reset AND is clocked and enable, to avoid deadlock situations or a hardfault
                 */
                if (((SYSCON->PRESETCTRL2 & 0x40000U) == 0) && syscon_css_clk_pclk_hclk && (CSSV2_CTRL_REG & 0x1))
#else
                syscon_css_clk_pclk_hclk = SYSCON->AHBCLKCTRL[2] & (1U << 18);
                /* Check if CSS is NOT in reset AND is clocked and enable, to avoid deadlock situations or a hardfault
                 */
                if (((SYSCON->PRESETCTRL[2] & 0x40000U) == 0) && syscon_css_clk_pclk_hclk && (CSSV2_CTRL_REG & 0x1))
#endif
                {
                    css_ctrl = CSSV2_CTRL_REG;

                    /* Wait until CSS is in idle state (CSS_STATUS_BUSY_MASK) */
                    while (CSSV2_STATUS_REG & 0x1)
                        ;

                    /* Disable CSS */
                    CSSV2_CTRL_REG = CSSV2_CTRL_REG & 0xFFFFFFFE;

                    /* Swicth off i_css_clk/pclk/hclk */
                    SYSCON->AHBCLKCTRLCLR[2] = (1U << 18);
                }

                /* Switch off DTRNG clocks */
                SYSCON_CSS_CLK_CTRL_CLR_REG = (1U << 1);
            }

            /* Disable all IRQs */
            __disable_irq();

            /*
             * - Switch PMC clock to 1 MHz,
             * - Set LDO_MEM as SRAM supply source during DEEP-SLEEP,
             * - Set LDO_CORE Low Power mode as Core supply source during DEEP-SLEEP,
             * - Select Core Logic supply source when waking up from DEEP-SLEEP.
             */
            reg_data = PMC->CTRL & (~PMC_CTRL_SELCLOCK_MASK) & (~PMC_CTRL_DEEPSLEEPCORESUPPLY_MASK) &
                       (~PMC_CTRL_SELMEMSUPPLY_MASK);
            if (POWER_GetCorePowerSource() == kPOWER_CoreSrcDCDC)
            {
                /* Core Logic is supplied by DCDC Converter when waking up from DEEP-SLEEP */
                PMC->CTRL = reg_data & (~PMC_CTRL_SELCORESUPPLYWK_MASK);
            }
            else
            {
                /* Core Logic is supplied by LDO CORE (configured in High Power mode) when waking up from DEEP-SLEEP */
                PMC->CTRL = reg_data | PMC_CTRL_SELCORESUPPLYWK_MASK;
            }

            /* _WFI() */
            POWER_PowerCycleCpu();

            /* Switch PMC clock to 12 MHz and Configure the PMC in ACTIVE mode */
            PMC->CTRL = (PMC->CTRL & (~PMC_CTRL_LPMODE_MASK)) | PMC_CTRL_SELCLOCK_MASK |
                        PMC_CTRL_LPMODE(LOWPOWER_CFG_LPMODE_ACTIVE);

            /* Restore BoD Core Trip point. */
            PMC->BODCORE = (PMC->BODCORE & (~PMC_BODCORE_TRIGLVL_MASK)) | PMC_BODCORE_TRIGLVL(bod_core_trglvl);

            // CSSV2
            {
                /* Restore i_css_clk/pclk/hclk */
                SYSCON->AHBCLKCTRLSET[2] = syscon_css_clk_pclk_hclk;

                /* Restore DTRNG clocks */
                SYSCON_CSS_CLK_CTRL_SET_REG = syscon_css_clk_ctrl;

/* Check if CSS is NOT in reset AND is clocked, to avoid deadlock situations */
#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
                if (((SYSCON->PRESETCTRL2 & 0x40000U) == 0) && syscon_css_clk_pclk_hclk && (css_ctrl & 0x1))
#else
                if (((SYSCON->PRESETCTRL[2] & 0x40000U) == 0) && syscon_css_clk_pclk_hclk && (css_ctrl & 0x1))
#endif
                {
                    /* Restore CSS */
                    CSSV2_CTRL_REG = css_ctrl;

                    /* Wait until CSS is in idle state */
                    while (CSSV2_STATUS_REG & 0x1)
                        ;
                }
            }

            /* Restore AUTOCLKGATEOVERRIDE register*/
            SYSCON->AUTOCLKGATEOVERRIDE = 0xC0DE0000 | syscon_autoclkgateoverride_reg;

            /* Reset Sleep Postpone configuration */
            SYSCON->HARDWARESLEEP = 0;

            break;
        }

        case LOWPOWER_CFG_LPMODE_POWERDOWN:
        {
            uint32_t lpcac_ctrl_reg;
            uint32_t vref_rst_state;
            uint32_t vref_clk_state;
            uint32_t syscon_ahbclk_reg_0;
            uint32_t syscon_css_clk_ctrl, syscon_css_clk_pclk_hclk;

            /* POWER DOWN power mode */
            power_core_pwr_source_t core_supply_source;

            /* Only FRO32K, XTAL32K, FRO1M, COMP, BIAS, LDO_MEM and can VREF stay powered during POWERDOWN */
            PMC->PDSLEEPCFG0 =
                p_lowpower_cfg->PDCTRL[0] |
                (0xFFFFFFFF & (~(kPDRUNCFG_PD_FRO1M | kPDRUNCFG_PD_FRO32K | kPDRUNCFG_PD_XTAL32K | kPDRUNCFG_PD_COMP |
                                 kPDRUNCFG_PD_BIAS | kPDRUNCFG_PD_LDOMEM | kPDRUNCFG_PD_VREF)));
            PMC->PDSLEEPCFG1 = p_lowpower_cfg->PDCTRL[1];

            /* Make sure DEEP POWER DOWN reset is disabled */
            PMC->RESETCTRL = PMC->RESETCTRL & (~PMC_RESETCTRL_DPDWAKEUPRESETENABLE_MASK);

/* Enable VREF Module (reset & clock) */
#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
            vref_rst_state           = (SYSCON->PRESETCTRL3) & SYSCON_PRESETCTRL3_VREF_RST_MASK;
            vref_clk_state           = (SYSCON->AHBCLKCTRL3) & SYSCON_AHBCLKCTRL3_VREF_MASK;
            SYSCON->PRESETCTRLCLR[3] = SYSCON_PRESETCTRL3_VREF_RST_MASK;
            SYSCON->AHBCLKCTRLSET[3] = SYSCON_AHBCLKCTRL3_VREF_MASK;
#else
            vref_rst_state = (*(uint32_t *)(((uint32_t *)SYSCON->RESERVED_5))) & 0x40000UL;
            vref_clk_state = (*(uint32_t *)(((uint32_t *)SYSCON->RESERVED_9))) & 0x40000UL;
            *(uint32_t *)(((uint32_t *)SYSCON->RESERVED_7)) = 0x40000UL;
            *(uint32_t *)(((uint32_t *)SYSCON->RESERVED_10)) = 0x40000UL;
#endif

            /* Save VREF Module User Configuration ... */
            vref_regs[0] = VREF->CSR;
            vref_regs[1] = VREF->UTRIM;
            /* Save VREF Module Factory Trimmings ... */
            VREF->TEST_UNLOCK = 0x5AA5UL << 1; /* TEST_UNLOCK. Required before writting TRIM0 & TRIM1 */
            vref_regs[2]      = VREF->TRIM0;
            vref_regs[3]      = VREF->TRIM1;

            /* ... then enable VREF Module isolation */
            PMC->MISCCTRL = PMC->MISCCTRL | PMC_MISCCTRL_VREF_ISO_MASK;

            // CSSV2
            {
                syscon_css_clk_ctrl = SYSCON_CSS_CLK_CTRL_REG & (1U << 1);
#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
                syscon_css_clk_pclk_hclk = SYSCON->AHBCLKCTRL2 & (1U << 18);
#else
                syscon_css_clk_pclk_hclk = SYSCON->AHBCLKCTRL[2] & (1U << 18);
#endif

                /* Switch off DTRNG clocks */
                SYSCON_CSS_CLK_CTRL_CLR_REG = (1U << 1);

                /* Swicth off i_css_clk/pclk/hclk */
                SYSCON->AHBCLKCTRLCLR[2] = (1U << 18);
            }

            /* CPU0 Retention */
            SYSCON->FUNCRETENTIONCTRL =
                (SYSCON->FUNCRETENTIONCTRL & SYSCON_FUNCRETENTIONCTRL_RET_LENTH_MASK) | p_lowpower_cfg->CPURETCTRL;

            /* Disable all IRQs */
            __disable_irq();

            /*
             * From here :
             *  1 - If an interrupt that is enable occurs, the _WFI instruction will not be executed and we won't enter
             * in POWER DOWN. 2 - If an interrupt that is not enable occurs, there is no consequence neither on the
             * execution of the low power mode nor on the behaviour of the CPU.
             */

            /* Switch PMC clock to 1 MHz and select LDO CORE (configured in High Power mode) as Core Logic supply source
             * when waking up from POWER-DOWN */
            PMC->CTRL = (PMC->CTRL & (~PMC_CTRL_SELCLOCK_MASK)) | PMC_CTRL_SELCORESUPPLYWK_MASK;

            /* Save user Core Supply Source configuration */
            core_supply_source = POWER_GetCorePowerSource();

            /* Store Analog Controller Registers */
            analog_ctrl_regs[0] = ANACTRL->FRO192M_CTRL;
            analog_ctrl_regs[1] = ANACTRL->ANALOG_CTRL_CFG;
            analog_ctrl_regs[2] = ANACTRL->ADC_CTRL;
            analog_ctrl_regs[3] = ANACTRL->XO32M_CTRL;
            analog_ctrl_regs[4] = ANACTRL->BOD_DCDC_INT_CTRL;
            analog_ctrl_regs[5] = ANACTRL->LDO_XO32M;
            analog_ctrl_regs[6] = ANACTRL->OSC_TESTBUS;

            /* Save Flash Cache settings, then disable and clear it */
            lpcac_ctrl_reg     = SYSCON->LPCAC_CTRL;
            SYSCON->LPCAC_CTRL = 0x3; /* dis_lpcac = '1', clr_lpcac = '1' */

/* Save ROM clock setting, then enable it.
 * It is important to have the ROM clock running before entering
 * POWER-DOWN for the following two reasons:
 * 1 - In case of POWER-DOWN with CPU state retention (which is the only
 *     option currently offered to the user), some flip-flops that depend
       on this clock need to be saved.
 * 2 - In case of POWER-DOWN without CPU state retention (which is a
 *     hardware feature that is NOT offered to the user for the time being)
 *     CPU reboot cannot occur if ROM clock has been shut down.
 */
#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
            syscon_ahbclk_reg_0      = SYSCON->AHBCLKCTRL0;
            SYSCON->AHBCLKCTRLSET[0] = SYSCON_AHBCLKCTRL0_ROM_MASK; /* Enable the clock for ROM */
#else
            syscon_ahbclk_reg_0 = SYSCON->AHBCLKCTRL[0];
            SYSCON->AHBCLKCTRLSET[0] = SYSCON_AHBCLKCTRL_ROM_MASK; /* Enable the clock for ROM */
#endif

            /* _WFI() */
            POWER_PowerCycleCpu();

/* Restore ROM clock setting */
#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
            SYSCON->AHBCLKCTRL0 = syscon_ahbclk_reg_0;
#else
            SYSCON->AHBCLKCTRL[0] = syscon_ahbclk_reg_0;
#endif
            /* Restore Flash Cache settings */
            SYSCON->LPCAC_CTRL = lpcac_ctrl_reg;

            /* Switch PMC clock to 12 MHz and Configure the PMC in ACTIVE mode */
            PMC->CTRL = (PMC->CTRL & (~PMC_CTRL_LPMODE_MASK)) | PMC_CTRL_SELCLOCK_MASK |
                        PMC_CTRL_LPMODE(LOWPOWER_CFG_LPMODE_ACTIVE);

#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
            {
                /* Restore i_css_clk/pclk/hclk */
                SYSCON->AHBCLKCTRLSET[2] = syscon_css_clk_pclk_hclk;

                /* Restore DTRNG clocks */
                SYSCON_CSS_CLK_CTRL_SET_REG = syscon_css_clk_ctrl;
            }
#endif

            /* Restore Analog Controller Registers */
            ANACTRL->FRO192M_CTRL      = analog_ctrl_regs[0] | ANACTRL_FRO192M_CTRL_WRTRIM_MASK;
            ANACTRL->ANALOG_CTRL_CFG   = analog_ctrl_regs[1];
            ANACTRL->ADC_CTRL          = analog_ctrl_regs[2];
            ANACTRL->XO32M_CTRL        = analog_ctrl_regs[3];
            ANACTRL->BOD_DCDC_INT_CTRL = analog_ctrl_regs[4];
            ANACTRL->LDO_XO32M         = analog_ctrl_regs[5];
            ANACTRL->OSC_TESTBUS       = analog_ctrl_regs[6];

            /* Restore VREF Module Factory Trimmings ... */
            VREF->TEST_UNLOCK = 0x5AA5UL << 1; /* TEST_UNLOCK. Required before writting TRIM0 & TRIM1 */
            VREF->TRIM0       = vref_regs[2];
            VREF->TRIM1       = vref_regs[3];
            /* ... then restore VREF Module User Configuration */
            VREF->CSR   = vref_regs[0];
            VREF->UTRIM = vref_regs[1];

/* Restore VREF module reset and clock state */
#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
            SYSCON->PRESETCTRL3 = (SYSCON->PRESETCTRL3 & (~SYSCON_PRESETCTRL3_VREF_RST_MASK)) | vref_rst_state;
            SYSCON->AHBCLKCTRL3 = (SYSCON->AHBCLKCTRL3 & (~SYSCON_AHBCLKCTRL3_VREF_MASK)) | vref_clk_state;
#else
            *(uint32_t *)(((uint32_t *)SYSCON->RESERVED_5)) =
                ((*(uint32_t *)(((uint32_t *)SYSCON->RESERVED_5))) & (~0x40000UL)) | vref_rst_state;
            *(uint32_t *)(((uint32_t *)SYSCON->RESERVED_9)) =
                ((*(uint32_t *)(((uint32_t *)SYSCON->RESERVED_9))) & (~0x40000UL)) | vref_clk_state;
#endif

            /* Disable VREF Module isolation ... */
            PMC->MISCCTRL = PMC->MISCCTRL & (~PMC_MISCCTRL_VREF_ISO_MASK);

            /* After wake up from Power-down, the Core supply source is LDO CORE */
            /* So restore the user configuration if necessary */
            if (core_supply_source == kPOWER_CoreSrcDCDC)
            {
                /* Restore DCDC Converter as Core Logic supply source */
                /* NOTE: PMC must be set in ACTIVE mode first before doing this switching to DCDC */
                (void)POWER_SetCorePowerSource(kPOWER_CoreSrcDCDC);
            }

            break;
        }

        case LOWPOWER_CFG_LPMODE_DEEPPOWERDOWN:
        {
            /* DEEP-POWER-DOWN power mode */

            /* Configure wake-up by I/O :
             * - Set up wake-up IO pad control source : PMC WAKEUPIOCTRL (WAKEUPIO_ENABLE = 1)
             * - Reset Wake-up I/O Edge Detectors & Cause (WAKEUPIO_RSTN = 0)
             */
            PMC->WAKEUPIOCTRL = p_lowpower_cfg->WAKEUPIOSRC | PMC_WAKEUPIOCTRL_WAKEUPIO_ENABLE_CTRL_MASK;

            /* Release Wake up I/O reset (WAKEUPIO_RSTN = 1)*/
            PMC->WAKEUPIOCTRL |= PMC_WAKEUPIOCTRL_WAKEUPIO_RSTN_MASK;

            /* Only FRO1M, FRO32K, XTAL32K and LDOMEM can stay powered during DEEP POWER-DOWN */
            PMC->PDSLEEPCFG0 =
                p_lowpower_cfg->PDCTRL[0] | (0xFFFFFFFF & (~(kPDRUNCFG_PD_FRO1M | kPDRUNCFG_PD_FRO32K |
                                                             kPDRUNCFG_PD_XTAL32K | kPDRUNCFG_PD_LDOMEM)));
            PMC->PDSLEEPCFG1 = p_lowpower_cfg->PDCTRL[1];

            /* Disable all IRQs */
            __disable_irq();

            /*
             * From here :
             *  1 - If an interrupt that is enabled occurs, the _WFI instruction will not be executed and we won't enter
             * in POWER DOWN. 2 - If an interrupt that is not enabled occurs, there is no consequence neither on the
             * execution of the low power mode nor on the behaviour of the CPU.
             */

            /* clear all Reset causes */
            PMC->RESETCAUSE = 0xFFFFFFFF;

            /* Enable DEEP POWER-DOWN reset */
            PMC->RESETCTRL |= PMC_RESETCTRL_DPDWAKEUPRESETENABLE_MASK;

            /* Switch PMC clock to 1 MHz */
            PMC->CTRL = PMC->CTRL & (~PMC_CTRL_SELCLOCK_MASK);

            /* _WFI() */
            POWER_PowerCycleCpu();

            /*** We should never reach this point, unless the Low Power cycle has been cancelled somehow. ***/
            /* Switch PMC clock to 12 MHz and Configure the PMC in ACTIVE mode */
            PMC->CTRL = (PMC->CTRL & (~PMC_CTRL_LPMODE_MASK)) | PMC_CTRL_SELCLOCK_MASK |
                        PMC_CTRL_LPMODE(LOWPOWER_CFG_LPMODE_ACTIVE);

            break;
        }

        default:
        {
            /* Error */
        }
    } // End switch( low_power_mode )

    /* Restore FMC Configuration */
    SYSCON->FMCCR = SYSCON->FMCCR | (fmccr_reg & SYSCON_FMCCR_PREFEN_MASK);

    /*
     * Restore the configuration of the Priority Mask Register.
     * Rational : if the interrupts were enable before entering the Low power mode, they will be re-enabled,
     *            if they were disabled, they will stay disabled.
     */
    __set_PRIMASK(primask);

    /* Restore the configuration of the NMI Register */
    SYSCON->NMISRC |= cpu0_nmi_enable;

    /* Restore the configuration of the CPU interrupt enable Registers (because they have been overwritten inside the
     * low power API */
    for (i = 0; i < 4; i++)
    {
        NVIC->ISER[i] = cpu0_int_enable[i];
    }
}

/**
 * @brief	Configures and enters in low power mode
 * @param	: p_lowpower_cfg
 * @return	Nothing
 */
static uint32_t POWER_WakeUpIOCtrl(uint32_t p_wakeup_io_ctrl)
{
    uint32_t wake_up_type;
    uint32_t wakeup_io_ctrl_reg = 0;

// Enable IOCON
#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
    SYSCON->PRESETCTRLCLR[0] = SYSCON_PRESETCTRL0_IOCON_RST_MASK;
    SYSCON->AHBCLKCTRLSET[0] = SYSCON_AHBCLKCTRL0_IOCON_MASK;
#else
    SYSCON->PRESETCTRLCLR[0] = SYSCON_PRESETCTRL_IOCON_RST_MASK;
    SYSCON->AHBCLKCTRLSET[0] = SYSCON_AHBCLKCTRL_IOCON_MASK;
#endif

    /* Configure Pull up & Pull down based on the required wake-up edge */

    /* Wake-up I/O 0 */
    wake_up_type =
        (p_wakeup_io_ctrl & (PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP0_MASK | PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP0_MASK)) >>
        LOWPOWER_WAKEUPIOSRC_PIO0_INDEX;
    wakeup_io_ctrl_reg |= (wake_up_type << LOWPOWER_WAKEUPIOSRC_PIO0_INDEX);
    if ((wake_up_type == LOWPOWER_WAKEUPIOSRC_RISING) || (wake_up_type == LOWPOWER_WAKEUPIOSRC_RISING_FALLING))
    {
        /* Rising edge and both rising and falling edges */
        if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO0_DISABLEPULLUPDOWN_MASK) == 0)
        {
            /* Internal pull up / pull down are not disabled by the user, so use them */
            IOCON->PIO[WAKEUPIO_0_PORT][WAKEUPIO_0_PINS] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(1); /* Pull down */
            wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO0MODE_INDEX);
        }
    }
    else
    {
        if (wake_up_type == LOWPOWER_WAKEUPIOSRC_FALLING)
        {
            /* Falling edge only */
            if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO0_DISABLEPULLUPDOWN_MASK) == 0)
            {
                /* Internal pull up / pull down are not disabled by the user, so use them */
                IOCON->PIO[WAKEUPIO_0_PORT][WAKEUPIO_0_PINS] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(2); /* Pull up */
                wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO0MODE_INDEX);
            }
        }
        else
        {
            /* Wake-up I/O is disabled : set pull-up/pull-down as required by the user */
            if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO0_DISABLEPULLUPDOWN_MASK) != 0)
            {
                /* Wake-up I/O is configured as Plain Input */
                p_wakeup_io_ctrl &= ~LOWPOWER_WAKEUPIO_PIO0_PULLUPDOWN_MASK;
                wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN << LOWPOWER_WAKEUPIOSRC_PIO0MODE_INDEX);
            }
            else
            {
                /* Wake-up I/O is configured as pull-up or pull-down */
                if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO0_PULLUPDOWN_MASK) != 0)
                {
                    /* Wake-up I/O is configured as pull-up */
                    wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO0MODE_INDEX);
                }
                else
                {
                    /* Wake-up I/O is configured as pull-down */
                    wakeup_io_ctrl_reg |=
                        (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO0MODE_INDEX);
                }
            }
        }
    }

    /* Wake-up I/O 1 */
    wake_up_type =
        (p_wakeup_io_ctrl & (PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP1_MASK | PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP1_MASK)) >>
        LOWPOWER_WAKEUPIOSRC_PIO1_INDEX;
    wakeup_io_ctrl_reg |= (wake_up_type << LOWPOWER_WAKEUPIOSRC_PIO1_INDEX);
    if ((wake_up_type == LOWPOWER_WAKEUPIOSRC_RISING) || (wake_up_type == LOWPOWER_WAKEUPIOSRC_RISING_FALLING))
    {
        /* Rising edge  and both rising and falling edges */
        if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO1_DISABLEPULLUPDOWN_MASK) == 0)
        {
            /* Internal pull up / pull down are not disabled by the user, so use them */
            IOCON->PIO[WAKEUPIO_1_PORT][WAKEUPIO_1_PINS] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(1); /* Pull down */
            wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO1MODE_INDEX);
        }
    }
    else
    {
        if (wake_up_type == LOWPOWER_WAKEUPIOSRC_FALLING)
        {
            /* Falling edge only */
            if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO1_DISABLEPULLUPDOWN_MASK) == 0)
            {
                /* Internal pull up / pull down are not disabled by the user, so use them */
                IOCON->PIO[WAKEUPIO_1_PORT][WAKEUPIO_1_PINS] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(2); /* Pull up */
                wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO1MODE_INDEX);
            }
        }
        else
        {
            /* Wake-up I/O is disabled : set it as required by the user */
            if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO1_DISABLEPULLUPDOWN_MASK) != 0)
            {
                /* Wake-up I/O is configured as Plain Input */
                p_wakeup_io_ctrl &= ~LOWPOWER_WAKEUPIO_PIO1_PULLUPDOWN_MASK;
                wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN << LOWPOWER_WAKEUPIOSRC_PIO1MODE_INDEX);
            }
            else
            {
                /* Wake-up I/O is configured as pull-up or pull-down */
                if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO1_PULLUPDOWN_MASK) != 0)
                {
                    /* Wake-up I/O is configured as pull-up */
                    wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO1MODE_INDEX);
                }
                else
                {
                    /* Wake-up I/O is configured as pull-down */
                    wakeup_io_ctrl_reg |=
                        (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO1MODE_INDEX);
                }
            }
        }
    }

    /* Wake-up I/O 2 */
    wake_up_type =
        (p_wakeup_io_ctrl & (PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP2_MASK | PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP2_MASK)) >>
        LOWPOWER_WAKEUPIOSRC_PIO2_INDEX;
    wakeup_io_ctrl_reg |= (wake_up_type << LOWPOWER_WAKEUPIOSRC_PIO2_INDEX);
    if ((wake_up_type == LOWPOWER_WAKEUPIOSRC_RISING) || (wake_up_type == LOWPOWER_WAKEUPIOSRC_RISING_FALLING))
    {
        /* Rising edge  and both rising and falling edges */
        if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO2_DISABLEPULLUPDOWN_MASK) == 0)
        {
            /* Internal pull up / pull down are not disabled by the user, so use them */
            IOCON->PIO[WAKEUPIO_2_PORT][WAKEUPIO_2_PINS] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(1); /* Pull down */
            wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO2MODE_INDEX);
        }
    }
    else
    {
        if (wake_up_type == LOWPOWER_WAKEUPIOSRC_FALLING)
        {
            /* Falling edge only */
            if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO2_DISABLEPULLUPDOWN_MASK) == 0)
            {
                /* Internal pull up / pull down are not disabled by the user, so use them */
                IOCON->PIO[WAKEUPIO_2_PORT][WAKEUPIO_2_PINS] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(2); /* Pull up */
                wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO2MODE_INDEX);
            }
        }
        else
        {
            /* Wake-up I/O is disabled : set it as required by the user */
            if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO2_DISABLEPULLUPDOWN_MASK) != 0)
            {
                /* Wake-up I/O is configured as Plain Input */
                p_wakeup_io_ctrl &= ~LOWPOWER_WAKEUPIO_PIO2_PULLUPDOWN_MASK;
                wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN << LOWPOWER_WAKEUPIOSRC_PIO2MODE_INDEX);
            }
            else
            {
                /* Wake-up I/O is configured as pull-up or pull-down */
                if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO2_PULLUPDOWN_MASK) != 0)
                {
                    /* Wake-up I/O is configured as pull-up */
                    wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO2MODE_INDEX);
                }
                else
                {
                    /* Wake-up I/O is configured as pull-down */
                    wakeup_io_ctrl_reg |=
                        (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO2MODE_INDEX);
                }
            }
        }
    }

    /* Wake-up I/O 3 */
    wake_up_type =
        (p_wakeup_io_ctrl & (PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP3_MASK | PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP3_MASK)) >>
        LOWPOWER_WAKEUPIOSRC_PIO3_INDEX;
    wakeup_io_ctrl_reg |= (wake_up_type << LOWPOWER_WAKEUPIOSRC_PIO3_INDEX);
    if ((wake_up_type == LOWPOWER_WAKEUPIOSRC_RISING) || (wake_up_type == LOWPOWER_WAKEUPIOSRC_RISING_FALLING))
    {
        /* Rising edge  and both rising and falling edges */
        if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO3_DISABLEPULLUPDOWN_MASK) == 0)
        {
            /* Internal pull up / pull down are not disabled by the user, so use them */
            IOCON->PIO[WAKEUPIO_3_PORT][WAKEUPIO_3_PINS] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(1); /* Pull down */
            wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO3MODE_INDEX);
        }
    }
    else
    {
        if (wake_up_type == LOWPOWER_WAKEUPIOSRC_FALLING)
        {
            /* Falling edge only */
            if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO3_DISABLEPULLUPDOWN_MASK) == 0)
            {
                /* Internal pull up / pull down are not disabled by the user, so use them */
                IOCON->PIO[WAKEUPIO_3_PORT][WAKEUPIO_3_PINS] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(2); /* Pull up */
                wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO3MODE_INDEX);
            }
        }
        else
        {
            /* Wake-up I/O is disabled : set it as required by the user */
            if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO3_DISABLEPULLUPDOWN_MASK) != 0)
            {
                /* Wake-up I/O is configured as Plain Input */
                p_wakeup_io_ctrl &= ~LOWPOWER_WAKEUPIO_PIO3_PULLUPDOWN_MASK;
                wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN << LOWPOWER_WAKEUPIOSRC_PIO3MODE_INDEX);
            }
            else
            {
                /* Wake-up I/O is configured as pull-up or pull-down */
                if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO3_PULLUPDOWN_MASK) != 0)
                {
                    /* Wake-up I/O is configured as pull-up */
                    wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO3MODE_INDEX);
                }
                else
                {
                    /* Wake-up I/O is configured as pull-down */
                    wakeup_io_ctrl_reg |=
                        (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO3MODE_INDEX);
                }
            }
        }
    }

    /* Wake-up I/O 4 */
    wake_up_type =
        (p_wakeup_io_ctrl & (PMC_WAKEUPIOCTRL_RISINGEDGEWAKEUP4_MASK | PMC_WAKEUPIOCTRL_FALLINGEDGEWAKEUP4_MASK)) >>
        LOWPOWER_WAKEUPIOSRC_PIO4_INDEX;
    wakeup_io_ctrl_reg |= (wake_up_type << LOWPOWER_WAKEUPIOSRC_PIO4_INDEX);
    if ((wake_up_type == LOWPOWER_WAKEUPIOSRC_RISING) || (wake_up_type == LOWPOWER_WAKEUPIOSRC_RISING_FALLING))
    {
        /* Rising edge  and both rising and falling edges */
        if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO4_DISABLEPULLUPDOWN_MASK) == 0)
        {
            /* Internal pull up / pull down are not disabled by the user, so use them */
            IOCON->PIO[WAKEUPIO_4_PORT][WAKEUPIO_4_PINS] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(1); /* Pull down */
            wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO4MODE_INDEX);
        }
    }
    else
    {
        if (wake_up_type == LOWPOWER_WAKEUPIOSRC_FALLING)
        {
            /* Falling edge only */
            if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO4_DISABLEPULLUPDOWN_MASK) == 0)
            {
                /* Internal pull up / pull down are not disabled by the user, so use them */
                IOCON->PIO[WAKEUPIO_4_PORT][WAKEUPIO_4_PINS] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(2); /* Pull up */
                wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO4MODE_INDEX);
            }
        }
        else
        {
            /* Wake-up I/O is disabled : set it as required by the user */
            if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO4_DISABLEPULLUPDOWN_MASK) != 0)
            {
                /* Wake-up I/O is configured as Plain Input */
                p_wakeup_io_ctrl &= ~LOWPOWER_WAKEUPIO_PIO4_PULLUPDOWN_MASK;
                wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN << LOWPOWER_WAKEUPIOSRC_PIO4MODE_INDEX);
            }
            else
            {
                /* Wake-up I/O is configured as pull-up or pull-down */
                if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO4_PULLUPDOWN_MASK) != 0)
                {
                    /* Wake-up I/O is configured as pull-up */
                    wakeup_io_ctrl_reg |= (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO4MODE_INDEX);
                }
                else
                {
                    /* Wake-up I/O is configured as pull-down */
                    wakeup_io_ctrl_reg |=
                        (LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO4MODE_INDEX);
                }
            }
        }
    }

    return (wakeup_io_ctrl_reg);
}

static uint32_t POWER_SetLdoAoLdoMemVoltage(uint32_t p_lp_mode)
{
    uint32_t voltage      = 0;
    uint32_t ldo_ao_trim  = 0;
    uint32_t ldo_mem_trim = 0;
    uint32_t lv_v_ldo_pmu, lv_v_ldo_pmu_boost;
    uint32_t lv_v_ldo_mem, lv_v_ldo_mem_boost;

#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
    ldo_ao_trim  = FLASH_NMPA_LDO_AO;
    ldo_mem_trim = FLASH_NMPA_LDO_MEM;
#endif

    switch (p_lp_mode)
    {
        case LOWPOWER_CFG_LPMODE_DEEPSLEEP:
        {
            if ((ldo_ao_trim & 0x80000000) != 0)
            {
                /* Apply settings coming from Flash */
                lv_v_ldo_pmu       = (ldo_ao_trim >> 8) & 0x1F;
                lv_v_ldo_pmu_boost = (ldo_ao_trim >> 13) & 0x1F;
            }
            else
            {
                /* Apply default settings */
                lv_v_ldo_pmu       = V_AO_0P900;
                lv_v_ldo_pmu_boost = V_AO_0P850;
            }
        }
        break;

        case LOWPOWER_CFG_LPMODE_POWERDOWN:
        {
            if ((ldo_ao_trim & 0x80000000) != 0)
            {
                /* Apply settings coming from Flash */
                lv_v_ldo_pmu       = (ldo_ao_trim >> 18) & 0x1F;
                lv_v_ldo_pmu_boost = (ldo_ao_trim >> 23) & 0x1F;
            }
            else
            {
                /* Apply default settings */
                lv_v_ldo_pmu       = V_AO_0P800;
                lv_v_ldo_pmu_boost = V_AO_0P750;
            }
        }
        break;

        case LOWPOWER_CFG_LPMODE_DEEPPOWERDOWN:
        {
            if ((ldo_ao_trim & 0x80000000) != 0)
            {
                /* Apply settings coming from Flash */
                lv_v_ldo_pmu       = (ldo_ao_trim >> 18) & 0x1F;
                lv_v_ldo_pmu_boost = (ldo_ao_trim >> 23) & 0x1F;
            }
            else
            {
                /* Apply default settings */
                lv_v_ldo_pmu       = V_AO_0P800;
                lv_v_ldo_pmu_boost = V_AO_0P750;
            }
        }
        break;

        default:
            /* We should never reach this point */
            lv_v_ldo_pmu       = V_AO_1P100;
            lv_v_ldo_pmu_boost = V_AO_1P050;
    }

    if ((ldo_mem_trim & 0x80000000) != 0)
    {
        /* Apply settings coming from Flash */
        lv_v_ldo_mem       = ldo_mem_trim & 0x1F;
        lv_v_ldo_mem_boost = (ldo_mem_trim >> 8) & 0x1F;
    }
    else
    {
        /* Apply default settings */
        lv_v_ldo_mem       = V_AO_0P750; /* Set to 0.75V (voltage Scaling) */
        lv_v_ldo_mem_boost = V_AO_0P700; /* Set to 0.7V  (voltage Scaling) */
    }

    /* The Memories Voltage settings below are for voltage scaling */
    voltage = (lv_v_ldo_pmu << LOWPOWER_VOLTAGE_LDO_PMU_INDEX) |
              (lv_v_ldo_pmu_boost << LOWPOWER_VOLTAGE_LDO_PMU_BOOST_INDEX) |
              (lv_v_ldo_mem << LOWPOWER_VOLTAGE_LDO_MEM_INDEX) |
              (lv_v_ldo_mem_boost << LOWPOWER_VOLTAGE_LDO_MEM_BOOST_INDEX);

    return (voltage);
}

/**
 * @brief	Configures System Power Profile
 * @param	power_profile : Low/Medium/High
 * @return	Nothing
 */
static void POWER_SetSystemPowerProfile(v_system_power_profile_t power_profile)
{
    uint32_t dcdcTrimValue0 = 0;
    uint32_t dcdcTrimValue1 = 0;

    switch (power_profile)
    {
        case V_SYSTEM_POWER_PROFILE_MEDIUM:
            /* Medium */

#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
            dcdcTrimValue0 = FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_ARRAY0;
            dcdcTrimValue1 = FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_ARRAY1;
#endif

            if (dcdcTrimValue0 & 0x1)
            {
                /* DCDC Trimmings in Flash are valid */
                dcdcTrimValue0 = dcdcTrimValue0 >> 1;
                PMC->DCDC0     = dcdcTrimValue0;
                PMC->DCDC1     = dcdcTrimValue1;
            }
            else
            {
                /* DCDC Trimmings in Flash are not valid.
                 * Set a default value */
                PMC->DCDC0 = 0x0220ACF1 >> 1;
                PMC->DCDC1 = 0x01D05C78;
            }

            break;

        case V_SYSTEM_POWER_PROFILE_HIGH:
/* High */
#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
            dcdcTrimValue0 = FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_ARRAY0;
            dcdcTrimValue1 = FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_ARRAY1;
#endif

            if (dcdcTrimValue0 & 0x1)
            {
                /* DCDC Trimmings in Flash are valid */
                dcdcTrimValue0 = dcdcTrimValue0 >> 1;
                PMC->DCDC0     = dcdcTrimValue0;
                PMC->DCDC1     = dcdcTrimValue1;
            }
            else
            {
                /* DCDC Trimmings in Flash are not valid.
                 * Set a default value */
                PMC->DCDC0 = 0x0228ACF9 >> 1;
                PMC->DCDC1 = 0x01E05C68;
            }

            break;

        default:
/* Low */
#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
            dcdcTrimValue0 = FLASH_NMPA_DCDC_POWER_PROFILE_LOW_ARRAY0;
            dcdcTrimValue1 = FLASH_NMPA_DCDC_POWER_PROFILE_LOW_ARRAY1;
#endif

            if (dcdcTrimValue0 & 0x1)
            {
                /* DCDC Trimmings in Flash are valid */
                dcdcTrimValue0 = dcdcTrimValue0 >> 1;
                PMC->DCDC0     = dcdcTrimValue0;
                PMC->DCDC1     = dcdcTrimValue1;
            }
            else
            {
                /* DCDC Trimmings in Flash are not valid.
                 * Set a default value */
                PMC->DCDC0 = 0x0210CCFD >> 1;
                PMC->DCDC1 = 0x01C05C98;
            }
    }
}

/**
 * @brief	Configures System Power Profile
 * @param	power_profile : Low/Medium/High
 * @return	Nothing
 */
static void POWER_SetVoltageForProcess(v_system_power_profile_t power_profile)
{
    /* Get Sample Process Corner */
    lowpower_process_corner_enum part_process_corner = POWER_GetPartProcessCorner();

    switch (part_process_corner)
    {
        case PROCESS_CORNER_SSS:
            /* Slow Corner */
            {
                switch (power_profile)
                {
                    case V_SYSTEM_POWER_PROFILE_MEDIUM:
                        /* Medium */
                        POWER_SetSystemVoltage(VOLTAGE_SSS_MED_MV);
                        break;

                    case V_SYSTEM_POWER_PROFILE_HIGH:
                        /* High */
                        POWER_SetSystemVoltage(VOLTAGE_SSS_HIG_MV);
                        break;

                    default:
                        /* V_SYSTEM_POWER_PROFILE_LOW */
                        POWER_SetSystemVoltage(VOLTAGE_SSS_LOW_MV);
                } // switch(power_profile)
            }
            break;

        case PROCESS_CORNER_FFF:
            /* Fast Corner */
            {
                switch (power_profile)
                {
                    case V_SYSTEM_POWER_PROFILE_MEDIUM:
                        /* Medium */
                        POWER_SetSystemVoltage(VOLTAGE_FFF_MED_MV);
                        break;

                    case V_SYSTEM_POWER_PROFILE_HIGH:
                        /* High */
                        POWER_SetSystemVoltage(VOLTAGE_FFF_HIG_MV);
                        break;

                    default:
                        /* V_SYSTEM_POWER_PROFILE_LOW */
                        POWER_SetSystemVoltage(VOLTAGE_FFF_LOW_MV);
                } // switch(power_profile)
            }
            break;

        default:
            /* Nominal (NNN) and all others Process Corners : assume Nominal Corner */
            {
                switch (power_profile)
                {
                    case V_SYSTEM_POWER_PROFILE_MEDIUM:
                        /* Medium */
                        POWER_SetSystemVoltage(VOLTAGE_NNN_MED_MV);
                        break;

                    case V_SYSTEM_POWER_PROFILE_HIGH:
                        /* High */
                        POWER_SetSystemVoltage(VOLTAGE_NNN_HIG_MV);
                        break;

                    default:
                        /* V_SYSTEM_POWER_PROFILE_LOW */
                        POWER_SetSystemVoltage(VOLTAGE_NNN_LOW_MV);
                } // switch(power_profile)
            }
    } // switch(part_process_corner)
}

/**
 * @brief
 * @param
 * @return
 */
static lowpower_process_corner_enum POWER_GetPartProcessCorner(void)
{
    lowpower_process_corner_enum part_process_corner;
    uint32_t pvt_ringo_hz;
    uint32_t pvt_ringo_0 = 0;
    uint32_t pvt_ringo_1 = 0;

#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
    pvt_ringo_0 = FLASH_NMPA_PVT_MONITOR_0_RINGO;
    pvt_ringo_1 = FLASH_NMPA_PVT_MONITOR_1_RINGO;
#endif

    /*
     * Check that the PVT Monitors Trimmings in flash are valid.
     * Note : On Customer Samples, PVT Trimmings in flash will ALWAYS be valid,
     *      so that in the SDK, the check below could be skipped (but NOT the right shift operation)
     */
    if (pvt_ringo_0 & 0x1)
    {
        /* PVT Trimmings in Flash are valid */
        pvt_ringo_0 = pvt_ringo_0 >> 1;
    }
    else
    {
        /* PVT Trimmings in Flash are NOT valid (average value assumed) */
        pvt_ringo_0 = PROCESS_NNN_AVG_HZ;
    }

    if (pvt_ringo_1 & 0x1)
    {
        /* PVT Trimmings in Flash are valid */
        pvt_ringo_1 = pvt_ringo_1 >> 1;
    }
    else
    {
        /* PVT Trimmings in Flash are NOT valid (average value assumed) */
        pvt_ringo_1 = PROCESS_NNN_AVG_HZ;
    }

    /*
     * There are 2 Ring Oscillators in the System.
     * We consider the worst case scenario by choosing
     * the minimum of the 2 Ring Oscillators values
     * as the final value to determine the Process Corner.
     */
    if (pvt_ringo_1 <= pvt_ringo_0)
    {
        pvt_ringo_hz = pvt_ringo_1;
    }
    else
    {
        pvt_ringo_hz = pvt_ringo_0;
    }

    /*
     * Determine the process corner based on the value of the Ring Oscillator frequency
     */
    if (pvt_ringo_hz <= PROCESS_NNN_MIN_HZ)
    {
        /* SSS Process Corner */
        part_process_corner = PROCESS_CORNER_SSS;
    }
    else
    {
        if (pvt_ringo_hz <= PROCESS_NNN_MAX_HZ)
        {
            /* NNN Process Corner */
            part_process_corner = PROCESS_CORNER_NNN;
        }
        else
        {
            /* FFF Process Corner */
            part_process_corner = PROCESS_CORNER_FFF;
        }
    }

    return (part_process_corner);
}

/**
 * @brief
 * @param
 * @return
 */
static void POWER_SetSystemVoltage(uint32_t system_voltage_mv)
{
    /*
     * Set system voltage
     */
    uint32_t lv_ldo_ao       = V_AO_1P100;         /* <ldo_ao> */
    uint32_t lv_ldo_ao_boost = V_AO_1P150;         /* <ldo_ao_boost> */
    uint32_t lv_dcdc         = V_DCDC_1P100;       /* <dcdc> */
    uint32_t lv_ldo_core     = V_LDOCORE_HP_1P102; /* <ldo_core> */

    /*
     * Because DCDC has less code than LD_AO, we first determine the
     * optimum DCDC settings, then we find the closest possible settings
     * for LDO_AO, knowing that we want both settings to be as close as possible
     * (ideally, they shall be equal).
     */

    if (system_voltage_mv <= 950)
    {
        lv_dcdc         = V_DCDC_0P950;
        lv_ldo_ao       = V_AO_0P960;
        lv_ldo_ao_boost = V_AO_1P010;
        lv_ldo_core     = V_LDOCORE_HP_0P953;
    }
    else if (system_voltage_mv <= 975)
    {
        lv_dcdc         = V_DCDC_0P975;
        lv_ldo_ao       = V_AO_0P980;
        lv_ldo_ao_boost = V_AO_1P030;
        lv_ldo_core     = V_LDOCORE_HP_0P980;
    }
    else if (system_voltage_mv <= 1000)
    {
        lv_dcdc         = V_DCDC_1P000;
        lv_ldo_ao       = V_AO_1P000;
        lv_ldo_ao_boost = V_AO_1P050;
        lv_ldo_core     = V_LDOCORE_HP_1P001;
    }
    else if (system_voltage_mv <= 1025)
    {
        lv_dcdc         = V_DCDC_1P025;
        lv_ldo_ao       = V_AO_1P030;
        lv_ldo_ao_boost = V_AO_1P080;
        lv_ldo_core     = V_LDOCORE_HP_1P027;
    }
    else if (system_voltage_mv <= 1050)
    {
        lv_dcdc         = V_DCDC_1P050;
        lv_ldo_ao       = V_AO_1P060;
        lv_ldo_ao_boost = V_AO_1P110;
        lv_ldo_core     = V_LDOCORE_HP_1P055;
    }
    else if (system_voltage_mv <= 1075)
    {
        lv_dcdc         = V_DCDC_1P075;
        lv_ldo_ao       = V_AO_1P080;
        lv_ldo_ao_boost = V_AO_1P130;
        lv_ldo_core     = V_LDOCORE_HP_1P075;
    }
    else if (system_voltage_mv <= 1100)
    {
        lv_dcdc         = V_DCDC_1P100;
        lv_ldo_ao       = V_AO_1P100;
        lv_ldo_ao_boost = V_AO_1P150;
        lv_ldo_core     = V_LDOCORE_HP_1P102;
    }
    else if (system_voltage_mv <= 1125)
    {
        lv_dcdc         = V_DCDC_1P125;
        lv_ldo_ao       = V_AO_1P130;
        lv_ldo_ao_boost = V_AO_1P160;
        lv_ldo_core     = V_LDOCORE_HP_1P027;
    }
    else if (system_voltage_mv <= 1150)
    {
        lv_dcdc         = V_DCDC_1P150;
        lv_ldo_ao       = V_AO_1P160;
        lv_ldo_ao_boost = V_AO_1P220;
        lv_ldo_core     = V_LDOCORE_HP_1P156;
    }
    else if (system_voltage_mv <= 1175)
    {
        lv_dcdc         = V_DCDC_1P175;
        lv_ldo_ao       = V_AO_1P160;
        lv_ldo_ao_boost = V_AO_1P220;
        lv_ldo_core     = V_LDOCORE_HP_1P177;
    }
    else
    {
        lv_dcdc         = V_DCDC_1P200;
        lv_ldo_ao       = V_AO_1P220;
        lv_ldo_ao_boost = V_AO_1P220;
        lv_ldo_core     = V_LDOCORE_HP_1P204;
    }

/* Set up LDO Always-On voltages */
#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
    /* Apply LDO_AO Trimmings */
    {
        int8_t ldo_ao_offset;
        int32_t lv_ldo_ao_signed;

        ldo_ao_offset =
            (int8_t)((FLASH_NMPA_LDO_AO & FLASH_NMPA_LDO_AO_VADJ_ACTIVE_MASK) >> FLASH_NMPA_LDO_AO_VADJ_ACTIVE_SHIFT);
        lv_ldo_ao_signed = (int32_t)((int32_t)lv_ldo_ao + (int32_t)ldo_ao_offset);

        if (lv_ldo_ao_signed < (int32_t)V_AO_0P960)
        {
            lv_ldo_ao = V_AO_0P960;
        }
        else
        {
            if (lv_ldo_ao_signed > (int32_t)V_AO_1P220)
            {
                lv_ldo_ao = V_AO_1P220;
            }
            else
            {
                lv_ldo_ao = (uint32_t)lv_ldo_ao_signed;
            }
        }
    }
// Note: In ACTIVE mode, the LDO BOOST mode is always enabled.
// Therefore, the value of the "lv_ldo_ao_boost" does not really matter.
// For that reason, we do not recompuete it here.
#endif
    PMC->LDOPMU = (PMC->LDOPMU & (~PMC_LDOPMU_VADJ_MASK) & (~PMC_LDOPMU_VADJ_BOOST_MASK)) | PMC_LDOPMU_VADJ(lv_ldo_ao) |
                  PMC_LDOPMU_VADJ_BOOST(lv_ldo_ao_boost);

    /* Set up DCDC voltage */
    PMC->DCDC0 = (PMC->DCDC0 & (~PMC_DCDC0_VOUT_MASK)) | PMC_DCDC0_VOUT(lv_dcdc);

/* Set up LDO_CORE voltage */
#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
    /* Apply LDO_CORE Trimmings */
    {
        int8_t ldo_core_regref_offset;
        int32_t lv_ldo_core_signed;

        ldo_core_regref_offset = (int8_t)((FLASH_NMPA_BOD_LDOCORE & FLASH_NMPA_BOD_LDOCORE_REGREF_1P8V_OFFSET_MASK) >>
                                          FLASH_NMPA_BOD_LDOCORE_REGREF_1P8V_OFFSET_SHIFT);
        lv_ldo_core_signed     = (int32_t)((int32_t)lv_ldo_core + (int32_t)ldo_core_regref_offset);

        if (lv_ldo_core_signed < (int32_t)V_LDOCORE_HP_1P204)
        {
            lv_ldo_core = V_LDOCORE_HP_1P204;
        }
        else
        {
            if (lv_ldo_core_signed > (int32_t)V_LDOCORE_HP_0P953)
            {
                lv_ldo_core = V_LDOCORE_HP_0P953;
            }
            else
            {
                lv_ldo_core = (uint32_t)lv_ldo_core_signed;
            }
        }
    }
#endif
    PMC->LDOCORE0 = (PMC->LDOCORE0 & (~PMC_LDOCORE0_REGREFTRIM_MASK)) | PMC_LDOCORE0_REGREFTRIM(lv_ldo_core);
}

/**
 * brief
 * return
 */
static void POWER_SRAMSetRegister(power_sram_index_t sram_index, uint32_t power_mode)
{
    switch (sram_index)
    {
        case kPOWER_SRAM_IDX_RAM_X0:
        {
            PMC->SRAMCTRL0 = (PMC->SRAMCTRL0 & (~(0xFUL << PMC_SRAMCTRL0_RAM_X0_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL0_RAM_X0_LS_SHIFT);
            break;
        }

        case kPOWER_SRAM_IDX_RAM_00:
        {
            PMC->SRAMCTRL0 = (PMC->SRAMCTRL0 & (~(0xFUL << PMC_SRAMCTRL0_RAM_00_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL0_RAM_00_LS_SHIFT);
            break;
        }

        case kPOWER_SRAM_IDX_RAM_01:
        {
            PMC->SRAMCTRL0 = (PMC->SRAMCTRL0 & (~(0xFUL << PMC_SRAMCTRL0_RAM_01_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL0_RAM_01_LS_SHIFT);
            break;
        }

        case kPOWER_SRAM_IDX_RAM_02:
        {
            PMC->SRAMCTRL0 = (PMC->SRAMCTRL0 & (~(0xFUL << PMC_SRAMCTRL0_RAM_02_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL0_RAM_02_LS_SHIFT);
            break;
        }

        case kPOWER_SRAM_IDX_RAM_03:
        {
            PMC->SRAMCTRL0 = (PMC->SRAMCTRL0 & (~(0xFUL << PMC_SRAMCTRL0_RAM_03_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL0_RAM_03_LS_SHIFT);
            break;
        }

        case kPOWER_SRAM_IDX_RAM_10:
        {
            PMC->SRAMCTRL0 = (PMC->SRAMCTRL0 & (~(0xFUL << PMC_SRAMCTRL0_RAM_10_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL0_RAM_10_LS_SHIFT);
            break;
        }

        case kPOWER_SRAM_IDX_RAM_20:
        {
            PMC->SRAMCTRL0 = (PMC->SRAMCTRL0 & (~(0xFUL << PMC_SRAMCTRL0_RAM_20_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL0_RAM_20_LS_SHIFT);
            break;
        }

        case kPOWER_SRAM_IDX_RAM_30:
        {
            PMC->SRAMCTRL0 = (PMC->SRAMCTRL0 & (~(0xFUL << PMC_SRAMCTRL0_RAM_30_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL0_RAM_30_LS_SHIFT);
            break;
        }

        case kPOWER_SRAM_IDX_RAM_40:
        {
            PMC->SRAMCTRL1 = (PMC->SRAMCTRL1 & (~(0xFUL << PMC_SRAMCTRL1_RAM_40_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL1_RAM_40_LS_SHIFT);
            break;
        }

        case kPOWER_SRAM_IDX_RAM_41:
        {
            PMC->SRAMCTRL1 = (PMC->SRAMCTRL1 & (~(0xFUL << PMC_SRAMCTRL1_RAM_41_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL1_RAM_41_LS_SHIFT);
            break;
        }

        case kPOWER_SRAM_IDX_RAM_42:
        {
            PMC->SRAMCTRL1 = (PMC->SRAMCTRL1 & (~(0xFUL << PMC_SRAMCTRL1_RAM_42_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL1_RAM_42_LS_SHIFT);
            break;
        }

        case kPOWER_SRAM_IDX_RAM_43:
        {
            PMC->SRAMCTRL1 = (PMC->SRAMCTRL1 & (~(0xFUL << PMC_SRAMCTRL1_RAM_43_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL1_RAM_43_LS_SHIFT);
            break;
        }

        case kPOWER_SRAM_IDX_FLASHCACHE:
        {
            PMC->SRAMCTRL1 = (PMC->SRAMCTRL1 & (~(0xFUL << PMC_SRAMCTRL1_RAM_FLASHLPCACHE_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL1_RAM_FLASHLPCACHE_LS_SHIFT);
            break;
        }

        case kPOWER_SRAM_IDX_FLEXSPICACHE:
        {
            PMC->SRAMCTRL1 = (PMC->SRAMCTRL1 & (~(0xFUL << PMC_SRAMCTRL1_RAM_FLEXSPILPCACHE_LS_SHIFT))) |
                             (power_mode << PMC_SRAMCTRL1_RAM_FLEXSPILPCACHE_LS_SHIFT);
            break;
        }

        default:
            // Error
            ;
    }
}

/**
 * brief
 * return
 */
static void POWER_SRAMActiveToLightSleep(power_sram_index_t sram_index)
{
    POWER_SRAMSetRegister(sram_index, SRAM_PWR_MODE_LS_CODE);
}

/**
 * brief
 * return
 */
static void POWER_SRAMActiveToDeepSleep(power_sram_index_t sram_index)
{
    POWER_SRAMSetRegister(sram_index, SRAM_PWR_MODE_DS_CODE);
}

/**
 * brief
 * return
 */
static void POWER_SRAMActiveToShutDown(power_sram_index_t sram_index)
{
    POWER_SRAMSetRegister(sram_index, SRAM_PWR_MODE_SD_CODE);
}

/**
 * brief
 * return
 */
static void POWER_SRAMLightSleepToActive(power_sram_index_t sram_index)
{
    POWER_SRAMSetRegister(sram_index, SRAM_PWR_MODE_MPU_CODE);
    // Wait at least 944.90 ns (worst case, from gf40rfnv_nxp_ehlvsram_008192x032bw4c04_mh_pt_m7)
    POWER_SRAMPowerUpDelay(); // wait about 1 us
    POWER_SRAMSetRegister(sram_index, SRAM_PWR_MODE_ACT_CODE);
}

/**
 * brief
 * return
 */
static void POWER_SRAMDeepSleepToActive(power_sram_index_t sram_index)
{
    POWER_SRAMSetRegister(sram_index, SRAM_PWR_MODE_FPU_CODE);
    // Wait at least 707.30 ns (worst case, from gf40rfnv_nxp_ehlvsram_008192x032bw4c04_mh_pt_m7)
    POWER_SRAMPowerUpDelay(); // wait about 1 us
    POWER_SRAMSetRegister(sram_index, SRAM_PWR_MODE_ACT_CODE);
}

/**
 * brief
 * return
 */
static void POWER_SRAMShutDownToActive(power_sram_index_t sram_index)
{
    POWER_SRAMSetRegister(sram_index, SRAM_PWR_MODE_FPU_CODE);
    // Wait at least 382.80 ns (worst case, from gf40rfnv_nxp_ehlvsram_008192x032bw4c04_mh_pt_m7)
    POWER_SRAMPowerUpDelay(); // wait about 1 us
    POWER_SRAMSetRegister(sram_index, SRAM_PWR_MODE_ACT_CODE);
}

/**
 * brief
 * return
 */
static void POWER_SetSystemClock12MHZ(void)
{
    if ((SYSCON->MAINCLKSELA != 0) || (SYSCON->MAINCLKSELB != 0) ||
        ((SYSCON->AHBCLKDIV & SYSCON_AHBCLKDIV_DIV_MASK) != 0))
    {
        /* The System is NOT running at 12 MHz: so switch the system on 12 MHz clock */
        /* IMPORTANT NOTE : The assumption here is that before calling any Low Power API
         * the system will be running at a frequency higher or equal to 12 MHz.
         */
        uint32_t flash_int_enable_reg;
        uint32_t num_wait_states = 1; /* Default to the maximum number of wait states */

        /* Switch main clock to FRO12MHz ( the order of the 5 settings below is critical) */
        SYSCON->MAINCLKSELA = SYSCON_MAINCLKSELA_SEL(0); /* Main clock A source select : FRO 12 MHz clock */
        SYSCON->MAINCLKSELB = SYSCON_MAINCLKSELB_SEL(0); /* Main clock B source select : Main Clock A */
        SYSCON->AHBCLKDIV   = SYSCON_AHBCLKDIV_DIV(0);   /* Main clock divided by 1 */

/* Adjust FMC waiting time cycles (num_wait_states) and disable PREFETCH
 * NOTE : PREFETCH disable MUST BE DONE BEFORE the flash command below.
 */
#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
        SYSCON->FMCCR = (SYSCON->FMCCR & (~SYSCON_FMCCR_FLASHTIM_MASK) & (~SYSCON_FMCCR_PREFEN_MASK)) |
                        SYSCON_FMCCR_FLASHTIM(num_wait_states);
        /* Adjust Flash Controller waiting time */
        flash_int_enable_reg = FLASH->INTEN; /* Save INT_ENABLE register. */
        FLASH->INTEN_CLR     = 0x1F;         /* Disable all interrupt */
        FLASH->INTSTAT_CLR   = 0x1F;         /* Clear all status flags */
#else
        SYSCON->FMCCR = (SYSCON->FMCCR & (~SYSCON_FMCCR_FMCTIM_MASK) & (~SYSCON_FMCCR_PREFEN_MASK)) |
                        SYSCON_FMCCR_FMCTIM(num_wait_states);
        /* Adjust Flash Controller waiting time */
        flash_int_enable_reg = FLASH->INT_ENABLE; /* Save INT_ENABLE register. */
        FLASH->INT_CLR_ENABLE = 0x1F;             /* Disable all interrupt */
        FLASH->INT_CLR_STATUS = 0x1F;             /* Clear all status flags */
#endif

        FLASH->DATAW[0] = num_wait_states;
        FLASH->CMD      = 0x2; /* CMD_SET_READ_MODE */

#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
        /* Wait until the cmd is completed (without error) */
        while (!(FLASH->INTSTAT & FLASH_INTSTAT_DONE_MASK))
            ;
        FLASH->INTSTAT_CLR = 0x1F;                 /* Clear all status flags, then ... */
        FLASH->INTEN_SET   = flash_int_enable_reg; /* ... restore INT_ENABLE register. */
#else
        /* Wait until the cmd is completed (without error) */
        while (!(FLASH->INT_STATUS & FLASH_INT_STATUS_DONE_MASK))
            ;
        FLASH->INT_CLR_STATUS = 0x1F;                 /* Clear all status flags, then ... */
        FLASH->INT_SET_ENABLE = flash_int_enable_reg; /* ... restore INT_ENABLE register. */
#endif

        POWER_SetSystemPowerProfile(
            V_SYSTEM_POWER_PROFILE_LOW); /* Align DCDC/LDO_CORE Power profile with the 12 MHz frequency */
    }
    else
    {
        /* The System is already running at 12 MHz: so disable FMC PREFETCH feature only */
        SYSCON->FMCCR = SYSCON->FMCCR & (~SYSCON_FMCCR_PREFEN_MASK);
    }
}
