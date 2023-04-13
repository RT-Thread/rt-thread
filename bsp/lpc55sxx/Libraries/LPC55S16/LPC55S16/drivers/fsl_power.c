/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_common.h"
#include "fsl_power.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.power"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** @brief  Low Power main structure */
typedef enum
{
    VD_AON       = 0x0, /*!< Digital Always On power domain */
    VD_MEM       = 0x1, /*!< Memories (SRAM) power domain   */
    VD_DCDC      = 0x2, /*!< Core logic power domain        */
    VD_DEEPSLEEP = 0x3  /*!< Core logic power domain        */
} LPC_POWER_DOMAIN_T;

/**
 * @brief LDO_FLASH_NV & LDO_USB voltage settings
 */
typedef enum _v_flashnv
{
    V_LDOFLASHNV_1P650 = 0, /*!< 0.95  V */
    V_LDOFLASHNV_1P700 = 1, /*!< 0.975 V */
    V_LDOFLASHNV_1P750 = 2, /*!< 1     V */
    V_LDOFLASHNV_0P800 = 3, /*!< 1.025 V */
    V_LDOFLASHNV_1P850 = 4, /*!< 1.050 V */
    V_LDOFLASHNV_1P900 = 5, /*!< 1.075 V */
    V_LDOFLASHNV_1P950 = 6, /*!< 1.1   V */
    V_LDOFLASHNV_2P000 = 7  /*!< 1.125 V */
} v_flashnv_t;

/** @brief  Low Power main structure */
typedef struct
{                              /*     */
    __IO uint32_t CFG;         /*!< Low Power Mode Configuration, and miscallenous options  */
    __IO uint32_t PDCTRL0;     /*!< Power Down control : controls power of various modules
                                 in the different Low power modes, including ROM */
    __IO uint32_t SRAMRETCTRL; /*!< Power Down control : controls power SRAM instances
                                 in the different Low power modes */
    __IO uint32_t CPURETCTRL;  /*!< CPU0 retention control : controls CPU retention parameters in POWER DOWN modes */
    __IO uint64_t VOLTAGE;     /*!< Voltage control in Low Power Modes */
    __IO uint64_t WAKEUPSRC;   /*!< Wake up sources control for sleepcon */
    __IO uint64_t WAKEUPINT;   /*!< Wake up sources control for ARM */
    __IO uint32_t HWWAKE;      /*!< Interrupt that can postpone power down modes
                                 in case an interrupt is pending when the processor request deepsleep */
    __IO uint32_t WAKEUPIOSRC; /*!< Wake up I/O sources in DEEP POWER DOWN mode */
    __IO uint32_t TIMERCFG;    /*!< Wake up timers configuration */
    __IO uint32_t TIMERCOUNT;  /*!< Wake up Timer count*/
    __IO uint32_t POWERCYCLE;  /*!< Cancels entry in Low Power mode if set with 0xDEADABBA (might be used by some
                                 interrupt handlers)*/
} LPC_LOWPOWER_T;

/*   */
#define LOWPOWER_POWERCYCLE_CANCELLED 0xDEADABBAUL /*!<    */

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
 * @brief Wake up timers configuration in Low Power Modes
 */
#define LOWPOWER_TIMERCFG_CTRL_INDEX   0
#define LOWPOWER_TIMERCFG_CTRL_MASK    (0x1UL << LOWPOWER_TIMERCFG_CTRL_INDEX)
#define LOWPOWER_TIMERCFG_TIMER_INDEX  1
#define LOWPOWER_TIMERCFG_TIMER_MASK   (0x7UL << LOWPOWER_TIMERCFG_TIMER_INDEX)
#define LOWPOWER_TIMERCFG_OSC32K_INDEX 4
#define LOWPOWER_TIMERCFG_OSC32K_MASK  (0x1UL << LOWPOWER_TIMERCFG_OSC32K_INDEX)

#define LOWPOWER_TIMERCFG_CTRL_DISABLE 0 /*!< Wake Timer Disable */
#define LOWPOWER_TIMERCFG_CTRL_ENABLE  1 /*!< Wake Timer Enable  */

/**
 * @brief Primary Wake up timers configuration in Low Power Modes
 */
#define LOWPOWER_TIMERCFG_TIMER_RTC1KHZ 0 /*!< 1 KHz Real Time Counter (RTC) used as wake up source */
#define LOWPOWER_TIMERCFG_TIMER_RTC1HZ  1 /*!< 1 Hz Real Time Counter (RTC) used as wake up source  */
#define LOWPOWER_TIMERCFG_TIMER_OSTIMER 2 /*!< OS Event Timer used as wake up source                */

#define LOWPOWER_TIMERCFG_OSC32K_FRO32KHZ  0 /*!< Wake up Timers uses FRO 32 KHz as clock source      */
#define LOWPOWER_TIMERCFG_OSC32K_XTAL32KHZ 1 /*!< Wake up Timers uses Chrystal 32 KHz as clock source */

//! @brief Interface for lowpower functions
typedef struct LowpowerDriverInterface
{
    void (*power_cycle_cpu_and_flash)(void);
    void (*set_lowpower_mode)(LPC_LOWPOWER_T *p_lowpower_cfg);
} lowpower_driver_interface_t;

/**<  DCDC Power Profiles */
typedef enum
{
    DCDC_POWER_PROFILE_LOW,    /**<  LOW (for CPU frequencies below DCDC_POWER_PROFILE_LOW_MAX_FREQ_HZ) */
    DCDC_POWER_PROFILE_MEDIUM, /**<  MEDIUM (for CPU frequencies between DCDC_POWER_PROFILE_LOW_MAX_FREQ_HZ and
                                  DCDC_POWER_PROFILE_MEDIUM_MAX_FREQ_HZ) */
    DCDC_POWER_PROFILE_HIGH,   /**<  HIGH (for CPU frequencies between DCDC_POWER_PROFILE_MEDIUM_MAX_FREQ_HZ and
                                  DCDC_POWER_PROFILE_HIGH_MAX_FREQ_HZ) */
} lowpower_dcdc_power_profile_enum;

/**<  Manufacturing Process Corners */
typedef enum
{
    PROCESS_CORNER_SSS,    /**< Slow Corner Process */
    PROCESS_CORNER_NNN,    /**< Nominal Corner Process */
    PROCESS_CORNER_FFF,    /**< Fast Corner Process */
    PROCESS_CORNER_OTHERS, /**< SFN, SNF, NFS, Poly Res ... Corner Process */
} lowpower_process_corner_enum;

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
 * @brief Deep Sleep LDO voltage settings
 */
typedef enum _v_deepsleep
{
    V_DEEPSLEEP_0P900 = 0, /*!< 0.9   V */
    V_DEEPSLEEP_0P925 = 1, /*!< 0.925 V */
    V_DEEPSLEEP_0P950 = 2, /*!< 0.95  V */
    V_DEEPSLEEP_0P975 = 3, /*!< 0.975 V */
    V_DEEPSLEEP_1P000 = 4, /*!< 1.000 V */
    V_DEEPSLEEP_1P025 = 5, /*!< 1.025 V */
    V_DEEPSLEEP_1P050 = 6, /*!< 1.050 V */
    V_DEEPSLEEP_1P075 = 7  /*!< 1.075 V */
} v_deepsleep_t;

/**
 * @brief Always On and Memories LDO voltage settings
 */
typedef enum _v_ao
{
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

/* Low Power modes  */
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

#define LOWPOWER_CFG_LPMODE_ACTIVE        0 /*!< ACTIVE mode          */
#define LOWPOWER_CFG_LPMODE_DEEPSLEEP     1 /*!< DEEP SLEEP mode      */
#define LOWPOWER_CFG_LPMODE_POWERDOWN     2 /*!< POWER DOWN mode      */
#define LOWPOWER_CFG_LPMODE_DEEPPOWERDOWN 3 /*!< DEEP POWER DOWN mode */
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

/* CPU Retention Control*/
#define LOWPOWER_CPURETCTRL_ENA_INDEX           0
#define LOWPOWER_CPURETCTRL_ENA_MASK            (0x1UL << LOWPOWER_CPURETCTRL_ENA_INDEX)
#define LOWPOWER_CPURETCTRL_MEMBASE_INDEX       1
#define LOWPOWER_CPURETCTRL_MEMBASE_MASK        (0x1FFFUL << LOWPOWER_CPURETCTRL_MEMBASE_INDEX)
#define LOWPOWER_CPURETCTRL_RETDATALENGTH_INDEX 14
#define LOWPOWER_CPURETCTRL_RETDATALENGTH_MASK  (0x3FFUL << LOWPOWER_CPURETCTRL_RETDATALENGTH_INDEX)

/* Voltgae setting*/
#define DCDC_POWER_PROFILE_LOW_MAX_FREQ_HZ \
    (72000000U) /* Maximum System Frequency allowed with DCDC Power Profile LOW */
#define DCDC_POWER_PROFILE_MEDIUM_MAX_FREQ_HZ \
    (100000000U) /* Maximum System Frequency allowed with DCDC Power Profile MEDIUM */
#define DCDC_POWER_PROFILE_HIGH_MAX_FREQ_HZ \
    (150000000U)                       /* Maximum System Frequency allowed with DCDC Power Profile HIGH */
#define PROCESS_NNN_AVG_HZ (19300000U) /* Average Ring OScillator value for Nominal (NNN) Manufacturing Process */
#define PROCESS_NNN_STD_HZ \
    (400000U) /* Standard Deviation Ring OScillator value for Nominal (NNN) Manufacturing Process */
#define PROCESS_NNN_LIMITS \
    (6U) /* Nominal (NNN) Manufacturing Process Ring Oscillator values limit (with respect to the Average value) */
#define PROCESS_NNN_MIN_HZ \
    (PROCESS_NNN_AVG_HZ -  \
     (PROCESS_NNN_LIMITS * \
      PROCESS_NNN_STD_HZ)) /* Minimum Ring OScillator value for Nominal (NNN) Manufacturing Process */
#define PROCESS_NNN_MAX_HZ \
    (PROCESS_NNN_AVG_HZ +  \
     (PROCESS_NNN_LIMITS * \
      PROCESS_NNN_STD_HZ))         /* Maximum Ring OScillator value for Nominal (NNN) Manufacturing Process */
#define VOLTAGE_SSS_LOW_MV (1100U) /* Voltage Settings for : Process=SSS, DCDC Power Profile=LOW */
#define VOLTAGE_SSS_MED_MV (1150U) /* Voltage Settings for : Process=SSS, DCDC Power Profile=MEDIUM */
#define VOLTAGE_SSS_HIG_MV (1200U) /* Voltage Settings for : Process=SSS, DCDC Power Profile=HIGH */
#define VOLTAGE_NNN_LOW_MV (1050U) /* Voltage Settings for : Process=NNN, DCDC Power Profile=LOW */
#define VOLTAGE_NNN_MED_MV (1075U) /* Voltage Settings for : Process=NNN, DCDC Power Profile=MEDIUM */
#define VOLTAGE_NNN_HIG_MV (1150U) /* Voltage Settings for : Process=NNN, DCDC Power Profile=HIGH */
#define VOLTAGE_FFF_LOW_MV (1000U) /* Voltage Settings for : Process=FFF, DCDC Power Profile=LOW */
#define VOLTAGE_FFF_MED_MV (1025U) /* Voltage Settings for : Process=FFF, DCDC Power Profile=MEDIUM */
#define VOLTAGE_FFF_HIG_MV (1050U) /* Voltage Settings for : Process=FFF, DCDC Power Profile=HIGH */

/**
 * @brief LDO Voltage control in Low Power Modes
 */
#define LOWPOWER_VOLTAGE_LDO_PMU_INDEX        0
#define LOWPOWER_VOLTAGE_LDO_PMU_MASK         (0x1FULL << LOWPOWER_VOLTAGE_LDO_PMU_INDEX)
#define LOWPOWER_VOLTAGE_LDO_MEM_INDEX        5
#define LOWPOWER_VOLTAGE_LDO_MEM_MASK         (0x1FULL << LOWPOWER_VOLTAGE_LDO_MEM_INDEX)
#define LOWPOWER_VOLTAGE_LDO_DEEP_SLEEP_INDEX 10
#define LOWPOWER_VOLTAGE_LDO_DEEP_SLEEP_MASK  (0x7ULL << LOWPOWER_VOLTAGE_LDO_DEEP_SLEEP_INDEX)
#define LOWPOWER_VOLTAGE_LDO_PMU_BOOST_INDEX  19
#define LOWPOWER_VOLTAGE_LDO_PMU_BOOST_MASK   (0x1FULL << LOWPOWER_VOLTAGE_LDO_PMU_BOOST_INDEX)
#define LOWPOWER_VOLTAGE_LDO_MEM_BOOST_INDEX  24
#define LOWPOWER_VOLTAGE_LDO_MEM_BOOST_MASK   (0x1FULL << LOWPOWER_VOLTAGE_LDO_MEM_BOOST_INDEX)
#define LOWPOWER_VOLTAGE_DCDC_INDEX           29
#define LOWPOWER_VOLTAGE_DCDC_MASK            (0xFULL << LOWPOWER_VOLTAGE_DCDC_INDEX)

/*! @brief set and clear bit MACRO's. */
#define U32_SET_BITS(P, B) ((*(uint32_t *)P) |= (B))
#define U32_CLR_BITS(P, B) ((*(uint32_t *)P) &= ~(B))
/* Return values from Config (N-2) page of flash */
#define GET_16MXO_TRIM() (*(uint32_t *)(FLASH_NMPA_BASE + 0xC8U)) // (0x3FCC8)
#define GET_32KXO_TRIM() (*(uint32_t *)(FLASH_NMPA_BASE + 0xCCU)) // (0x3FCCC)

#define CPU_RETENTION_RAMX_STORAGE_START_ADDR (0x04002000)

#define XO_SLAVE_EN (1)
/*******************************************************************************
 * Codes
 ******************************************************************************/

/*******************************************************************************
 * LOCAL FUNCTIONS PROTOTYPES
 ******************************************************************************/
static void lf_get_deepsleep_core_supply_cfg(uint32_t exclude_from_pd, uint32_t *dcdc_voltage);
static uint32_t lf_set_ldo_ao_ldo_mem_voltage(uint32_t p_lp_mode, uint32_t p_dcdc_voltage);
static uint32_t lf_wakeup_io_ctrl(uint32_t p_wakeup_io_ctrl);
static uint8_t CLOCK_u8OscCapConvert(uint8_t u8OscCap, uint8_t u8CapBankDiscontinuity);

static void lowpower_set_dcdc_power_profile(lowpower_dcdc_power_profile_enum dcdc_power_profile);
static lowpower_process_corner_enum lowpower_get_part_process_corner(void);
static void lowpower_set_voltage_for_process(lowpower_dcdc_power_profile_enum dcdc_power_profile);
static lowpower_driver_interface_t *s_lowpowerDriver = (lowpower_driver_interface_t *)(0x130050e4);

/**
 * @brief   Configures and enters in low power mode
 * @param   p_lowpower_cfg: pointer to a structure that contains all low power mode parameters
 * @return  Nothing
 *
 *          !!! IMPORTANT NOTES :
 *           1 - CPU Interrupt Enable registers are updated with p_lowpower_cfg->WAKEUPINT. They are NOT restored by the
 * API.
 *           2 - The Non Maskable Interrupt (NMI) should be disable before calling this API (otherwise, there is a risk
 * of Dead Lock).
 *           3 - The HARD FAULT handler should execute from SRAM. (The Hard fault handler should initiate a full chip
 * reset)
 */
static void POWER_EnterLowPower(LPC_LOWPOWER_T *p_lowpower_cfg);

/**
 * @brief
 * @param
 * @return
 */
static void lf_set_dcdc_power_profile_low(void)
{
#define DCDC_POWER_PROFILE_LOW_0_ADDRS (FLASH_NMPA_BASE + 0xE0U) // N4M (0x3FCE0U) / N4S (0x9FCE0U)
#define DCDC_POWER_PROFILE_LOW_1_ADDRS (FLASH_NMPA_BASE + 0xE4U) // N4M (0x3FCE4U) / N4S (0x9FCE4U)

    uint32_t dcdcTrimValue0 = (*((volatile unsigned int *)(DCDC_POWER_PROFILE_LOW_0_ADDRS)));
    uint32_t dcdcTrimValue1 = (*((volatile unsigned int *)(DCDC_POWER_PROFILE_LOW_1_ADDRS)));

    if (0UL != (dcdcTrimValue0 & 0x1UL))
    {
        PMC->DCDC0 = dcdcTrimValue0 >> 1;
        PMC->DCDC1 = dcdcTrimValue1;
    }
}

/**
 * @brief   Configures and enters in low power mode
 * @param           : p_lowpower_cfg
 * @return  Nothing
 */
static void POWER_EnterLowPower(LPC_LOWPOWER_T *p_lowpower_cfg)
{
    /* PMC clk set to 12 MHZ */
    p_lowpower_cfg->CFG |= (uint32_t)LOWPOWER_CFG_SELCLOCK_12MHZ << LOWPOWER_CFG_SELCLOCK_INDEX;

    /* Enable Analog References fast wake-up in case of wake-up from a low power mode (DEEP SLEEP, POWER DOWN and DEEP
     * POWER DOWN) and Hardware Pin reset */
    PMC->REFFASTWKUP = (PMC->REFFASTWKUP & (~PMC_REFFASTWKUP_LPWKUP_MASK) & (~PMC_REFFASTWKUP_HWWKUP_MASK)) |
                       PMC_REFFASTWKUP_LPWKUP(1) | PMC_REFFASTWKUP_HWWKUP(1);

    /* SRAM uses Voltage Scaling in all Low Power modes */
    PMC->SRAMCTRL = (PMC->SRAMCTRL & (~PMC_SRAMCTRL_SMB_MASK)) | PMC_SRAMCTRL_SMB(3);

    /* CPU Retention configuration : preserve the value of FUNCRETENTIONCTRL.RET_LENTH which is a Hardware defined
     * parameter. */
    p_lowpower_cfg->CPURETCTRL = (SYSCON->FUNCRETENTIONCTRL & SYSCON_FUNCRETENTIONCTRL_RET_LENTH_MASK) |
                                 (p_lowpower_cfg->CPURETCTRL & (~SYSCON_FUNCRETENTIONCTRL_RET_LENTH_MASK));

    /* Switch System Clock to FRO12Mhz (the configuration before calling this function will not be restored back) */
    CLOCK_AttachClk(kFRO12M_to_MAIN_CLK);                      /* Switch main clock to FRO12MHz */
    CLOCK_SetClkDiv(kCLOCK_DivAhbClk, 1U, false);              /* Main clock divided by 1 */
    SYSCON->FMCCR = (SYSCON->FMCCR & 0xFFFF0000UL) | 0x201AUL; /* Adjust FMC waiting time cycles */
    lf_set_dcdc_power_profile_low(); /* Align DCDC Power profile with the 12 MHz clock (DCDC Power Profile LOW) */

    (*(s_lowpowerDriver->set_lowpower_mode))(p_lowpower_cfg);

    /* Restore the configuration of the MISCCTRL Register : LOWPWR_FLASH_BUF = 0, LDOMEMBLEEDDSLP = 0, LDOMEMHIGHZMODE =
     * 0 */
    PMC->MISCCTRL &= (~PMC_MISCCTRL_LOWPWR_FLASH_BUF_MASK) & (~PMC_MISCCTRL_DISABLE_BLEED_MASK) &
                     (~PMC_MISCCTRL_LDOMEMHIGHZMODE_MASK);
}

/**
 * @brief   Shut off the Flash and execute the _WFI(), then power up the Flash after wake-up event
 * @param   None
 * @return  Nothing
 */
void POWER_CycleCpuAndFlash(void)
{
    (*(s_lowpowerDriver->power_cycle_cpu_and_flash))();
};

/**
 * brief    PMC Deep Sleep function call
 * return   nothing
 */
void POWER_EnterDeepSleep(uint32_t exclude_from_pd,
                          uint32_t sram_retention_ctrl,
                          uint64_t wakeup_interrupts,
                          uint32_t hardware_wake_ctrl)
{
    LPC_LOWPOWER_T lv_low_power_mode_cfg; /* Low Power Mode configuration structure */
    uint32_t cpu0_nmi_enable;
    uint32_t cpu0_int_enable_0;
    uint32_t cpu0_int_enable_1;
    uint32_t dcdc_voltage;
    uint32_t pmc_reset_ctrl;
    /* Clear Low Power Mode configuration variable */
    (void)memset(&lv_low_power_mode_cfg, 0x0, sizeof(LPC_LOWPOWER_T));

    /* Configure Low Power Mode configuration variable */
    lv_low_power_mode_cfg.CFG |= (uint32_t)LOWPOWER_CFG_LPMODE_DEEPSLEEP
                                 << LOWPOWER_CFG_LPMODE_INDEX; /* DEEPSLEEP mode */

    lf_get_deepsleep_core_supply_cfg(exclude_from_pd, &dcdc_voltage);

    if (((exclude_from_pd & (uint32_t)kPDRUNCFG_PD_USB1_PHY) != 0UL) &&
        ((exclude_from_pd & (uint32_t)kPDRUNCFG_PD_LDOUSBHS) != 0UL))
    {
        /* USB High Speed is required as wake-up source in Deep Sleep mode: make sure LDO FLASH NV stays powered during
         * deep-sleep */
        exclude_from_pd = exclude_from_pd | (uint32_t)kPDRUNCFG_PD_LDOFLASHNV;
    }

    /* DCDC will be always used during Deep Sleep (instead of LDO Deep Sleep); Make sure LDO MEM & Analog references
     * will stay powered, Shut down ROM */
    lv_low_power_mode_cfg.PDCTRL0 = (~exclude_from_pd & ~(uint32_t)kPDRUNCFG_PD_DCDC & ~(uint32_t)kPDRUNCFG_PD_LDOMEM &
                                     ~(uint32_t)kPDRUNCFG_PD_BIAS) |
                                    (uint32_t)kPDRUNCFG_PD_LDODEEPSLEEP | (uint32_t)kPDRUNCFG_PD_ROM;

    /* Voltage control in DeepSleep Low Power Modes */
    /* The Memories Voltage settings below are for voltage scaling */
    lv_low_power_mode_cfg.VOLTAGE = lf_set_ldo_ao_ldo_mem_voltage(LOWPOWER_CFG_LPMODE_POWERDOWN, dcdc_voltage);

    /* SRAM retention control during POWERDOWN */
    lv_low_power_mode_cfg.SRAMRETCTRL = sram_retention_ctrl;

    /* CPU Wake up & Interrupt sources control */
    lv_low_power_mode_cfg.WAKEUPINT = wakeup_interrupts;
    lv_low_power_mode_cfg.WAKEUPSRC = wakeup_interrupts;

    /* Interrupts that allow DMA transfers with Flexcomm without waking up the Processor */
    if (0UL != (hardware_wake_ctrl & (LOWPOWER_HWWAKE_PERIPHERALS | LOWPOWER_HWWAKE_SDMA0 | LOWPOWER_HWWAKE_SDMA1)))
    {
        lv_low_power_mode_cfg.HWWAKE = (hardware_wake_ctrl & ~LOWPOWER_HWWAKE_FORCED) | LOWPOWER_HWWAKE_ENABLE_FRO192M;
    }

    cpu0_nmi_enable = SYSCON->NMISRC & SYSCON_NMISRC_NMIENCPU0_MASK; /* Save the configuration of the NMI Register */
    SYSCON->NMISRC &= ~SYSCON_NMISRC_NMIENCPU0_MASK;                 /* Disable NMI of CPU0 */

    /* Save the configuration of the CPU interrupt enable Registers (because they are overwritten inside the low power
     * API */
    cpu0_int_enable_0 = NVIC->ISER[0];
    cpu0_int_enable_1 = NVIC->ISER[1];

    pmc_reset_ctrl = PMC->RESETCTRL;

    if ((pmc_reset_ctrl & (PMC_RESETCTRL_BODCORERESETENA_SECURE_MASK | PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_MASK)) ==
        ((0x1UL << PMC_RESETCTRL_BODCORERESETENA_SECURE_SHIFT) |
         (0x1UL << PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_SHIFT)))
    {
        /* BoD CORE reset is activated, so make sure BoD Core and Biasing won't be shutdown */
        lv_low_power_mode_cfg.PDCTRL0 &= ~(uint32_t)kPDRUNCFG_PD_BODCORE & ~(uint32_t)kPDRUNCFG_PD_BIAS;
    }
    if ((pmc_reset_ctrl & (PMC_RESETCTRL_BODVBATRESETENA_SECURE_MASK | PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_MASK)) ==
        ((0x1UL << PMC_RESETCTRL_BODVBATRESETENA_SECURE_SHIFT) |
         (0x1UL << PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_SHIFT)))
    {
        /* BoD VBAT reset is activated, so make sure BoD VBAT and Biasing won't be shutdown */
        lv_low_power_mode_cfg.PDCTRL0 &= ~(uint32_t)kPDRUNCFG_PD_BODVBAT & ~(uint32_t)kPDRUNCFG_PD_BIAS;
    }

    /* Enter low power mode */
    POWER_EnterLowPower(&lv_low_power_mode_cfg);

    /* Restore the configuration of the NMI Register */
    SYSCON->NMISRC |= cpu0_nmi_enable;

    /* Restore the configuration of the CPU interrupt enable Registers (because they have been overwritten inside the
     * low power API */
    NVIC->ISER[0] = cpu0_int_enable_0;
    NVIC->ISER[1] = cpu0_int_enable_1;
}

/**
 * brief    PMC power Down function call
 * return   nothing
 */
void POWER_EnterPowerDown(uint32_t exclude_from_pd,
                          uint32_t sram_retention_ctrl,
                          uint64_t wakeup_interrupts,
                          uint32_t cpu_retention_ctrl)
{
    LPC_LOWPOWER_T lv_low_power_mode_cfg; /* Low Power Mode configuration structure */
    uint32_t cpu0_nmi_enable;
    uint32_t cpu0_int_enable_0;
    uint32_t cpu0_int_enable_1;
    uint64_t wakeup_src_int;
    uint32_t pmc_reset_ctrl;
    uint32_t rng_entropy_save[6];

    uint32_t analog_ctrl_regs[12]; /* To store Analog Controller Regristers */

    /* Clear Low Power Mode configuration variable */
    (void)memset(&lv_low_power_mode_cfg, 0x0, sizeof(LPC_LOWPOWER_T));

    /* Configure Low Power Mode configuration variable */
    lv_low_power_mode_cfg.CFG |= (uint32_t)LOWPOWER_CFG_LPMODE_POWERDOWN
                                 << LOWPOWER_CFG_LPMODE_INDEX; /* POWER DOWN mode */

    /* Only FRO32K, XTAL32K, COMP, BIAS and LDO_MEM can be stay powered during POWERDOWN (valid from application point
     * of view; Hardware allows BODVBAT, LDODEEPSLEEP and FRO1M to stay powered, that's why they are excluded below) */
    lv_low_power_mode_cfg.PDCTRL0 = (~exclude_from_pd) | (uint32_t)kPDRUNCFG_PD_BODVBAT | (uint32_t)kPDRUNCFG_PD_FRO1M |
                                    (uint32_t)kPDRUNCFG_PD_LDODEEPSLEEP;

    /* @TODO Guillaume: add save/restore entropy during PowerDown */
    /* Entropy for RNG need to saved */
    if ((exclude_from_pd & (uint32_t)kPDRUNCFG_PD_RNG) != 0UL)
    {
        CLOCK_EnableClock(kCLOCK_Rng);
        RESET_ClearPeripheralReset(kRNG_RST_SHIFT_RSTn);
        for (int i = 0; i < 6; i++)
        {
            rng_entropy_save[i] = RNG->RANDOM_NUMBER;
        }
    }

    /* CPU0 retention Ctrl.
     * For the time being, we do not allow customer to relocate the CPU retention area in SRAMX, meaning that the
     * retention area range is [0x0400_6000 - 0x0400_6600] (beginning of RAMX2 for N4S) If required by customer,
     * retention area range is [0x0400_2000 - 0x0400_2600] (beginning of RAMX2 for N4M) If required by customer,
     * cpu_retention_ctrl[13:1] will be used for that to modify the default retention area
     */
    lv_low_power_mode_cfg.CPURETCTRL =
        (cpu_retention_ctrl & LOWPOWER_CPURETCTRL_ENA_MASK) |
        ((((uint32_t)CPU_RETENTION_RAMX_STORAGE_START_ADDR >> 2UL) << LOWPOWER_CPURETCTRL_MEMBASE_INDEX) &
         LOWPOWER_CPURETCTRL_MEMBASE_MASK);
    if (0UL != (cpu_retention_ctrl & 0x1UL))
    {
        /* Add RAMX2 for retention */
        sram_retention_ctrl |= LOWPOWER_SRAMRETCTRL_RETEN_RAMX2;
        /* CPU retention is required: store Analog Controller Registers */
        analog_ctrl_regs[0]  = ANACTRL->FRO192M_CTRL;
        analog_ctrl_regs[1]  = ANACTRL->ANALOG_CTRL_CFG;
        analog_ctrl_regs[2]  = ANACTRL->ADC_CTRL;
        analog_ctrl_regs[3]  = ANACTRL->XO32M_CTRL;
        analog_ctrl_regs[4]  = ANACTRL->BOD_DCDC_INT_CTRL;
        analog_ctrl_regs[5]  = ANACTRL->RINGO0_CTRL;
        analog_ctrl_regs[6]  = ANACTRL->RINGO1_CTRL;
        analog_ctrl_regs[7]  = ANACTRL->RINGO2_CTRL;
        analog_ctrl_regs[8]  = ANACTRL->LDO_XO32M;
        analog_ctrl_regs[9]  = ANACTRL->AUX_BIAS;
        analog_ctrl_regs[10] = ANACTRL->USBHS_PHY_CTRL;
        analog_ctrl_regs[11] = ANACTRL->USBHS_PHY_TRIM;
    }

    /* SRAM retention control during POWERDOWN */
    lv_low_power_mode_cfg.SRAMRETCTRL = sram_retention_ctrl;

    /* Sanity check: If retention is required for any of SRAM instances, make sure LDO MEM will stay powered */
    if ((sram_retention_ctrl & 0x7FFFUL) != 0UL)
    {
        lv_low_power_mode_cfg.PDCTRL0 &= ~(uint32_t)kPDRUNCFG_PD_LDOMEM;
    }

    /* Voltage control in Low Power Modes */
    /* The Memories Voltage settings below are for voltage scaling */
    lv_low_power_mode_cfg.VOLTAGE = lf_set_ldo_ao_ldo_mem_voltage(LOWPOWER_CFG_LPMODE_POWERDOWN, 0);

    /* CPU Wake up & Interrupt sources control : only WAKEUP_GPIO_GLOBALINT0, WAKEUP_GPIO_GLOBALINT1, WAKEUP_FLEXCOMM3,
     * WAKEUP_ACMP_CAPT, WAKEUP_RTC_LITE_ALARM_WAKEUP, WAKEUP_OS_EVENT_TIMER, WAKEUP_ALLWAKEUPIOS */
    wakeup_src_int = (uint64_t)(WAKEUP_GPIO_GLOBALINT0 | WAKEUP_GPIO_GLOBALINT1 | WAKEUP_FLEXCOMM3 | WAKEUP_ACMP |
                                WAKEUP_RTC_LITE_ALARM_WAKEUP | WAKEUP_OS_EVENT_TIMER | WAKEUP_ALLWAKEUPIOS);
    lv_low_power_mode_cfg.WAKEUPINT = wakeup_interrupts & wakeup_src_int;
    lv_low_power_mode_cfg.WAKEUPSRC = wakeup_interrupts & wakeup_src_int;

    cpu0_nmi_enable = SYSCON->NMISRC & SYSCON_NMISRC_NMIENCPU0_MASK; /* Save the configuration of the NMI Register */
    SYSCON->NMISRC &= ~SYSCON_NMISRC_NMIENCPU0_MASK;                 /* Disable NMI of CPU0 */

    /* Save the configuration of the CPU interrupt enable Registers (because they are overwritten inside the low power
     * API */
    cpu0_int_enable_0 = NVIC->ISER[0];
    cpu0_int_enable_1 = NVIC->ISER[1];

    /* Disable BoD VBAT and BoD Core resets */
    /* BOD VBAT disable reset */
    pmc_reset_ctrl =
        PMC->RESETCTRL & (~(PMC_RESETCTRL_BODVBATRESETENA_SECURE_MASK | PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_MASK));
    pmc_reset_ctrl |= (0x2UL << PMC_RESETCTRL_BODVBATRESETENA_SECURE_SHIFT) |
                      (0x2UL << PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_SHIFT);

    /* BOD CORE disable reset */
    pmc_reset_ctrl &= (~(PMC_RESETCTRL_BODCORERESETENA_SECURE_MASK | PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_MASK));
    pmc_reset_ctrl |= (0x2UL << PMC_RESETCTRL_BODCORERESETENA_SECURE_SHIFT) |
                      (0x2UL << PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_SHIFT);

    PMC->RESETCTRL = pmc_reset_ctrl;

    /* Enter low power mode */
    POWER_EnterLowPower(&lv_low_power_mode_cfg);

    /*** We'll reach this point in case of POWERDOWN with CPU retention or if the POWERDOWN has not been taken (for
      instance because an interrupt is pending). In case of CPU retention, assumption is that the SRAM containing the
      stack used to call this function shall be preserved during low power ***/

#if defined(PUF_SRAM_CTRL_CFG_ENABLE_MASK)
    /* Following code is to reset PUF to remove over consumption */
    /* Enable PUF register clock to access register */
    SYSCON->AHBCLKCTRLSET[2] = SYSCON_AHBCLKCTRL2_PUF_MASK;
    /* Release PUF reset */
    SYSCON->PRESETCTRLCLR[2] = SYSCON_PRESETCTRL2_PUF_RST_MASK;
    /* Enable PUF SRAM */
    PUF_SRAM_CTRL->CFG |= PUF_SRAM_CTRL_CFG_ENABLE_MASK | PUF_SRAM_CTRL_CFG_CKGATING_MASK;

    /* Disable PUF register clock. */
    // Delaying the line of code below until the PUF State Machine execution is completed:
    // Shuting down the clock to early will prevent the state machine from reaching the end.
    // => Wait for status bit in PUF Controller Registers before stop PUF clock.
    while (0UL == (PUF_SRAM_CTRL->INT_STATUS & PUF_SRAM_CTRL_INT_STATUS_READY_MASK))
    {
    }

    SYSCON->AHBCLKCTRLCLR[2] = SYSCON_AHBCLKCTRL2_PUF_MASK;
#endif
    /* Restore the configuration of the NMI Register */
    SYSCON->NMISRC |= cpu0_nmi_enable;

    /* Restore PMC RESETCTRL register */
    PMC->RESETCTRL = pmc_reset_ctrl;

    /* Restore the configuration of the CPU interrupt enable Registers (because they have been overwritten inside the
     * low power API */
    NVIC->ISER[0] = cpu0_int_enable_0;
    NVIC->ISER[1] = cpu0_int_enable_1;

    if ((cpu_retention_ctrl & 0x1UL) != 0UL)
    {
        /* Restore Analog Controller Registers */
        ANACTRL->FRO192M_CTRL      = analog_ctrl_regs[0] | ANACTRL_FRO192M_CTRL_WRTRIM_MASK;
        ANACTRL->ANALOG_CTRL_CFG   = analog_ctrl_regs[1];
        ANACTRL->ADC_CTRL          = analog_ctrl_regs[2];
        ANACTRL->XO32M_CTRL        = analog_ctrl_regs[3];
        ANACTRL->BOD_DCDC_INT_CTRL = analog_ctrl_regs[4];
        ANACTRL->RINGO0_CTRL       = analog_ctrl_regs[5];
        ANACTRL->RINGO1_CTRL       = analog_ctrl_regs[6];
        ANACTRL->RINGO2_CTRL       = analog_ctrl_regs[7];
        ANACTRL->LDO_XO32M         = analog_ctrl_regs[8];
        ANACTRL->AUX_BIAS          = analog_ctrl_regs[9];
        ANACTRL->USBHS_PHY_CTRL    = analog_ctrl_regs[10];
        ANACTRL->USBHS_PHY_TRIM    = analog_ctrl_regs[11];
    }

    /* @TODO Guillaume: add save/restore entropy during PowerDown */
    /* Restore Entropy for RNG */
    if ((exclude_from_pd & (uint32_t)kPDRUNCFG_PD_RNG) != 0UL)
    {
        RNG->POWERDOWN &= ~RNG_POWERDOWN_POWERDOWN_MASK;
        for (int i = 0; i < 6; i++)
        {
            RNG->ENTROPY_INJECT = rng_entropy_save[i];
        }
    }
}

/**
 * brief    PMC Deep Sleep Power Down function call
 * return   nothing
 */
void POWER_EnterDeepPowerDown(uint32_t exclude_from_pd,
                              uint32_t sram_retention_ctrl,
                              uint64_t wakeup_interrupts,
                              uint32_t wakeup_io_ctrl)
{
    LPC_LOWPOWER_T lv_low_power_mode_cfg; /* Low Power Mode configuration structure */
    uint32_t cpu0_nmi_enable;
    uint32_t cpu0_int_enable_0;
    uint32_t cpu0_int_enable_1;
    uint32_t pmc_reset_ctrl;

    /* Clear Low Power Mode configuration variable */
    (void)memset(&lv_low_power_mode_cfg, 0x0, sizeof(LPC_LOWPOWER_T));

    /* Configure Low Power Mode configuration variable */
    lv_low_power_mode_cfg.CFG |= (uint32_t)LOWPOWER_CFG_LPMODE_DEEPPOWERDOWN
                                 << LOWPOWER_CFG_LPMODE_INDEX; /* DEEP POWER DOWN mode */

    /* Only FRO32K, XTAL32K and LDO_MEM can be stay powered during DEEPPOWERDOWN (valid from application point of view;
     * Hardware allows BODVBAT, BIAS FRO1M and COMP to stay powered, that's why they are excluded below) */
    lv_low_power_mode_cfg.PDCTRL0 = (~exclude_from_pd) | (uint32_t)kPDRUNCFG_PD_BIAS | (uint32_t)kPDRUNCFG_PD_BODVBAT |
                                    (uint32_t)kPDRUNCFG_PD_FRO1M | (uint32_t)kPDRUNCFG_PD_COMP;

    /* SRAM retention control during DEEPPOWERDOWN */
    /* RAM00 used by ROM code to restart. */
    sram_retention_ctrl = sram_retention_ctrl & (~(LOWPOWER_SRAMRETCTRL_RETEN_RAM00));

    /* SRAM retention control during DEEPPOWERDOWN */
    lv_low_power_mode_cfg.SRAMRETCTRL = sram_retention_ctrl;

    /* Sanity check: If retention is required for any of SRAM instances, make sure LDO MEM will stay powered */
    if ((sram_retention_ctrl & 0x7FFFUL) != 0UL)
    {
        lv_low_power_mode_cfg.PDCTRL0 &= ~(uint32_t)kPDRUNCFG_PD_LDOMEM;
    }

    /* Voltage control in Low Power Modes */
    /* The Memories Voltage settings below are for voltage scaling */
    lv_low_power_mode_cfg.VOLTAGE = lf_set_ldo_ao_ldo_mem_voltage(LOWPOWER_CFG_LPMODE_DEEPPOWERDOWN, 0);

    lv_low_power_mode_cfg.WAKEUPINT =
        wakeup_interrupts & (WAKEUP_RTC_LITE_ALARM_WAKEUP |
                             WAKEUP_OS_EVENT_TIMER); /* CPU Wake up sources control : only WAKEUP_RTC_LITE_ALARM_WAKEUP,
                                                        WAKEUP_OS_EVENT_TIMER */
    lv_low_power_mode_cfg.WAKEUPSRC =
        wakeup_interrupts &
        (WAKEUP_RTC_LITE_ALARM_WAKEUP | WAKEUP_OS_EVENT_TIMER |
         WAKEUP_ALLWAKEUPIOS); /*!< Hardware Wake up sources control: : only WAKEUP_RTC_LITE_ALARM_WAKEUP,
                                  WAKEUP_OS_EVENT_TIMER and WAKEUP_ALLWAKEUPIOS */

    /* Wake up I/O sources */
    lv_low_power_mode_cfg.WAKEUPIOSRC = lf_wakeup_io_ctrl(wakeup_io_ctrl);

    cpu0_nmi_enable = SYSCON->NMISRC & SYSCON_NMISRC_NMIENCPU0_MASK; /* Save the configuration of the NMI Register */
    SYSCON->NMISRC &= ~SYSCON_NMISRC_NMIENCPU0_MASK;                 /* Disable NMI of CPU0 */

    /* Save the configuration of the CPU interrupt enable Registers (because they are overwritten inside the low power
     * API */
    cpu0_int_enable_0 = NVIC->ISER[0];
    cpu0_int_enable_1 = NVIC->ISER[1];

    /* Save the configuration of the PMC RESETCTRL register */
    /* BOD VBAT disable reset */
    pmc_reset_ctrl =
        PMC->RESETCTRL & (~(PMC_RESETCTRL_BODVBATRESETENA_SECURE_MASK | PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_MASK));
    pmc_reset_ctrl |= (0x2UL << PMC_RESETCTRL_BODVBATRESETENA_SECURE_SHIFT) |
                      (0x2UL << PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_SHIFT);

    /* BOD CORE disable reset */
    pmc_reset_ctrl &= (~(PMC_RESETCTRL_BODCORERESETENA_SECURE_MASK | PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_MASK));
    pmc_reset_ctrl |= (0x2UL << PMC_RESETCTRL_BODCORERESETENA_SECURE_SHIFT) |
                      (0x2UL << PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_SHIFT);

    PMC->RESETCTRL = pmc_reset_ctrl;

    /* Enter low power mode */
    POWER_EnterLowPower(&lv_low_power_mode_cfg);

    /*** We'll reach this point ONLY and ONLY if the DEEPPOWERDOWN has not been taken (for instance because an RTC or
     * OSTIMER interrupt is pending) ***/

    /* Restore the configuration of the NMI Register */
    SYSCON->NMISRC |= cpu0_nmi_enable;

    /* Restore PMC RESETCTRL register */
    PMC->RESETCTRL = pmc_reset_ctrl;

    /* Restore the configuration of the CPU interrupt enable Registers (because they have been overwritten inside the
     * low power API */
    NVIC->ISER[0] = cpu0_int_enable_0;
    NVIC->ISER[1] = cpu0_int_enable_1;
}

/**
 * brief    PMC Sleep function call
 * return   nothing
 */
void POWER_EnterSleep(void)
{
    uint32_t pmsk;
    pmsk = __get_PRIMASK();
    __disable_irq();
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    __WFI();
    __set_PRIMASK(pmsk);
}

/**
 * @brief   Get Digital Core logic supply source to be used during Deep Sleep.
 * @param [in]  exclude_from_pd: COmpoenents NOT to be powered down during Deep Sleep
 * @param [out] core_supply: 0 = LDO DEEPSLEEP will be used / 1 = DCDC will be used
 * @param [out] dcdc_voltage: as defined by V_DCDC_* in fsl_power.h

 * @return  Nothing
 */
static void lf_get_deepsleep_core_supply_cfg(uint32_t exclude_from_pd, uint32_t *dcdc_voltage)
{
    *dcdc_voltage = V_DCDC_0P950; /* Default value */

    if (((exclude_from_pd & (uint32_t)kPDRUNCFG_PD_USB1_PHY) != 0) &&
        ((exclude_from_pd & (uint32_t)kPDRUNCFG_PD_LDOUSBHS) != 0))
    {
        /* USB High Speed is required as wake-up source in Deep Sleep mode */
        PMC->MISCCTRL |= PMC_MISCCTRL_LOWPWR_FLASH_BUF_MASK; /* Force flash buffer in low power mode */
        *dcdc_voltage = V_DCDC_1P000; /* Set DCDC voltage to be 1.000 V (USB HS IP cannot work below 0.990 V) */
    }
}

/**
 * @brief
 * @param
 * @return
 */
static uint32_t lf_set_ldo_ao_ldo_mem_voltage(uint32_t p_lp_mode, uint32_t p_dcdc_voltage)
{
#define FLASH_NMPA_LDO_AO_ADDRS                (FLASH_NMPA_BASE + 0x0F4U) // N4M (0x3FCF4U) / N4S (0x9FCF4U)
#define FLASH_NMPA_LDO_AO_DSLP_TRIM_VALID_MASK (0x100U)
#define FLASH_NMPA_LDO_AO_DSLP_TRIM_MASK       (0x3E00U)
#define FLASH_NMPA_LDO_AO_DSLP_TRIM_SHIFT      (9U)
#define FLASH_NMPA_LDO_AO_PDWN_TRIM_VALID_MASK (0x10000U)
#define FLASH_NMPA_LDO_AO_PDWN_TRIM_MASK       (0x3E0000U)
#define FLASH_NMPA_LDO_AO_PDWN_TRIM_SHIFT      (17U)
#define FLASH_NMPA_LDO_AO_DPDW_TRIM_VALID_MASK (0x1000000U)
#define FLASH_NMPA_LDO_AO_DPDW_TRIM_MASK       (0x3E000000U)
#define FLASH_NMPA_LDO_AO_DPDW_TRIM_SHIFT      (25U)

    uint32_t ldo_ao_trim, voltage;
    uint32_t lv_v_ldo_pmu, lv_v_ldo_pmu_boost;

    ldo_ao_trim = (*((volatile unsigned int *)(FLASH_NMPA_LDO_AO_ADDRS)));

    switch (p_lp_mode)
    {
        case LOWPOWER_CFG_LPMODE_DEEPSLEEP:
        {
            if ((ldo_ao_trim & FLASH_NMPA_LDO_AO_DSLP_TRIM_VALID_MASK) != 0UL)
            {
                /* Apply settings coming from Flash */
                lv_v_ldo_pmu = (ldo_ao_trim & FLASH_NMPA_LDO_AO_DSLP_TRIM_MASK) >> FLASH_NMPA_LDO_AO_DSLP_TRIM_SHIFT;
                lv_v_ldo_pmu_boost = lv_v_ldo_pmu - 2UL; /* - 50 mV */
            }
            else
            {
                /* Apply default settings */
                lv_v_ldo_pmu       = (uint32_t)V_AO_0P900;
                lv_v_ldo_pmu_boost = (uint32_t)V_AO_0P850;
            }
        }
        break;

        case LOWPOWER_CFG_LPMODE_POWERDOWN:
        {
            if ((ldo_ao_trim & FLASH_NMPA_LDO_AO_PDWN_TRIM_VALID_MASK) != 0UL)
            {
                /* Apply settings coming from Flash */
                lv_v_ldo_pmu = (ldo_ao_trim & FLASH_NMPA_LDO_AO_PDWN_TRIM_MASK) >> FLASH_NMPA_LDO_AO_PDWN_TRIM_SHIFT;
                lv_v_ldo_pmu_boost = lv_v_ldo_pmu - 2UL; /* - 50 mV */
            }
            else
            {
                /* Apply default settings */
                lv_v_ldo_pmu       = (uint32_t)V_AO_0P800;
                lv_v_ldo_pmu_boost = (uint32_t)V_AO_0P750;
            }
        }
        break;

        case LOWPOWER_CFG_LPMODE_DEEPPOWERDOWN:
        {
            if ((ldo_ao_trim & FLASH_NMPA_LDO_AO_DPDW_TRIM_VALID_MASK) != 0UL)
            {
                /* Apply settings coming from Flash */
                lv_v_ldo_pmu = (ldo_ao_trim & FLASH_NMPA_LDO_AO_DPDW_TRIM_MASK) >> FLASH_NMPA_LDO_AO_DPDW_TRIM_SHIFT;
                lv_v_ldo_pmu_boost = lv_v_ldo_pmu - 2UL; /* - 50 mV */
            }
            else
            {
                /* Apply default settings */
                lv_v_ldo_pmu       = (uint32_t)V_AO_0P800;
                lv_v_ldo_pmu_boost = (uint32_t)V_AO_0P750;
            }
        }
        break;

        default:
            /* Should never reach this point */
            lv_v_ldo_pmu       = (uint32_t)V_AO_1P100;
            lv_v_ldo_pmu_boost = (uint32_t)V_AO_1P050;
            break;
    }

    /* The Memories Voltage settings below are for voltage scaling */
    voltage =
        (lv_v_ldo_pmu << LOWPOWER_VOLTAGE_LDO_PMU_INDEX) |               /*  */
        (lv_v_ldo_pmu_boost << LOWPOWER_VOLTAGE_LDO_PMU_BOOST_INDEX) |   /*  */
        ((uint32_t)V_AO_0P750 << LOWPOWER_VOLTAGE_LDO_MEM_INDEX) |       /* Set to 0.75V (voltage Scaling) */
        ((uint32_t)V_AO_0P700 << LOWPOWER_VOLTAGE_LDO_MEM_BOOST_INDEX) | /* Set to 0.7V  (voltage Scaling) */
        ((uint32_t)V_DEEPSLEEP_0P900
         << LOWPOWER_VOLTAGE_LDO_DEEP_SLEEP_INDEX) |    /* Set to 0.90 V (Not used because LDO_DEEP_SLEEP is disabled)*/
        (p_dcdc_voltage << LOWPOWER_VOLTAGE_DCDC_INDEX) /*  */
        ;

    return (voltage);
}

/**
 * @brief
 * @param
 * @return
 */
static uint32_t lf_wakeup_io_ctrl(uint32_t p_wakeup_io_ctrl)
{
    uint32_t wake_up_type;
    uint32_t wakeup_io_ctrl_reg;
    uint8_t use_external_pullupdown = 0;

    /* Configure Pull up & Pull down based on the required wake-up edge */
    CLOCK_EnableClock(kCLOCK_Iocon);

    wakeup_io_ctrl_reg = 0UL;

    /* Wake-up I/O 0 */
    wake_up_type = (p_wakeup_io_ctrl & 0x3UL) >> LOWPOWER_WAKEUPIOSRC_PIO0_INDEX;
    wakeup_io_ctrl_reg |= (wake_up_type << LOWPOWER_WAKEUPIOSRC_PIO0_INDEX);
    use_external_pullupdown = (uint8_t)((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO0_USEEXTERNALPULLUPDOWN_MASK) >>
                                        LOWPOWER_WAKEUPIO_PIO0_USEEXTERNALPULLUPDOWN_INDEX);

    if (use_external_pullupdown == 0UL)
    {
        if ((wake_up_type == 1UL) || (wake_up_type == 3UL))
        {
            /* Rising edge and both rising and falling edges */
            IOCON->PIO[1][1] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(1); /* Pull down */
            wakeup_io_ctrl_reg |=
                ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO0MODE_INDEX);
        }
        else
        {
            if (wake_up_type == 2UL)
            {
                /* Falling edge only */
                IOCON->PIO[1][1] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(2); /* Pull up */
                wakeup_io_ctrl_reg |=
                    ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO0MODE_INDEX);
            }
            else
            {
                /* Wake-up I/O is disabled : set it as required by the user */
                if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO0_DISABLEPULLUPDOWN_MASK) != 0UL)
                {
                    /* Wake-up I/O is configured as Plain Input */
                    // @TODO not used               p_wakeup_io_ctrl &= ~LOWPOWER_WAKEUPIO_PIO0_PULLUPDOWN_MASK;
                    wakeup_io_ctrl_reg |=
                        ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN << LOWPOWER_WAKEUPIOSRC_PIO0MODE_INDEX);
                }
                else
                {
                    /* Wake-up I/O is configured as pull-up or pull-down */
                    // @TODO update for mask name
                    if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO0_PULLUPDOWN_MASK) != 0UL)
                    {
                        /* Wake-up I/O is configured as pull-up */
                        wakeup_io_ctrl_reg |=
                            ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO0MODE_INDEX);
                    }
                    else
                    {
                        /* Wake-up I/O is configured as pull-down */
                        wakeup_io_ctrl_reg |=
                            ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO0MODE_INDEX);
                    }
                }
            }
        }
    }
    else
    {
        wakeup_io_ctrl_reg |= ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN << LOWPOWER_WAKEUPIOSRC_PIO0MODE_INDEX);
    }

    /* Wake-up I/O 1 */
    wake_up_type = (p_wakeup_io_ctrl & 0xCUL) >> LOWPOWER_WAKEUPIOSRC_PIO1_INDEX;
    wakeup_io_ctrl_reg |= (wake_up_type << LOWPOWER_WAKEUPIOSRC_PIO1_INDEX);
    use_external_pullupdown = (uint8_t)((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO1_USEEXTERNALPULLUPDOWN_MASK) >>
                                        LOWPOWER_WAKEUPIO_PIO1_USEEXTERNALPULLUPDOWN_INDEX);

    if (use_external_pullupdown == 0UL)
    {
        if ((wake_up_type == 1UL) || (wake_up_type == 3UL))
        {
            /* Rising edge  and both rising and falling edges */
            IOCON->PIO[0][28] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(1); /* Pull down */
            wakeup_io_ctrl_reg |=
                ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO1MODE_INDEX);
        }
        else
        {
            if (wake_up_type == 2UL)
            {
                /* Falling edge only */
                IOCON->PIO[0][28] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(2); /* Pull up */
                wakeup_io_ctrl_reg |=
                    ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO1MODE_INDEX);
            }
            else
            {
                /* Wake-up I/O is disabled : set it as required by the user */
                if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO1_DISABLEPULLUPDOWN_MASK) != 0UL)
                {
                    /* Wake-up I/O is configured as Plain Input */
                    // @TODO not used                p_wakeup_io_ctrl &= ~LOWPOWER_WAKEUPIO_PIO1_PULLUPDOWN_MASK;
                    wakeup_io_ctrl_reg |=
                        ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN << LOWPOWER_WAKEUPIOSRC_PIO1MODE_INDEX);
                }
                else
                {
                    /* Wake-up I/O is configured as pull-up or pull-down */
                    // @TODO update for mask name
                    if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO1_PULLUPDOWN_MASK) != 0UL)
                    {
                        /* Wake-up I/O is configured as pull-up */
                        wakeup_io_ctrl_reg |=
                            ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO1MODE_INDEX);
                    }
                    else
                    {
                        /* Wake-up I/O is configured as pull-down */
                        wakeup_io_ctrl_reg |=
                            ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO1MODE_INDEX);
                    }
                }
            }
        }
    }
    else
    {
        wakeup_io_ctrl_reg |= ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN << LOWPOWER_WAKEUPIOSRC_PIO1MODE_INDEX);
    }

    /* Wake-up I/O 2 */
    wake_up_type = (p_wakeup_io_ctrl & 0x30UL) >> LOWPOWER_WAKEUPIOSRC_PIO2_INDEX;
    wakeup_io_ctrl_reg |= (wake_up_type << LOWPOWER_WAKEUPIOSRC_PIO2_INDEX);
    use_external_pullupdown = (uint8_t)((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO2_USEEXTERNALPULLUPDOWN_MASK) >>
                                        LOWPOWER_WAKEUPIO_PIO2_USEEXTERNALPULLUPDOWN_INDEX);

    if (use_external_pullupdown == 0UL)
    {
        if ((wake_up_type == 1UL) || (wake_up_type == 3UL))
        {
            /* Rising edge  and both rising and falling edges */
            IOCON->PIO[1][18] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(1); /* Pull down */
            wakeup_io_ctrl_reg |=
                ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO2MODE_INDEX);
        }
        else
        {
            if (wake_up_type == 2UL)
            {
                /* Falling edge only */
                IOCON->PIO[1][18] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(2); /* Pull up */
                wakeup_io_ctrl_reg |=
                    ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO2MODE_INDEX);
            }
            else
            {
                /* Wake-up I/O is disabled : set it as required by the user */
                if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO2_DISABLEPULLUPDOWN_MASK) != 0UL)
                {
                    /* Wake-up I/O is configured as Plain Input */
                    // @TODO not used                p_wakeup_io_ctrl &= ~LOWPOWER_WAKEUPIO_PIO2_PULLUPDOWN_MASK;
                    wakeup_io_ctrl_reg |=
                        ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN << LOWPOWER_WAKEUPIOSRC_PIO2MODE_INDEX);
                }
                else
                {
                    /* Wake-up I/O is configured as pull-up or pull-down */
                    // @TODO update for mask name
                    if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO2_PULLUPDOWN_MASK) != 0UL)
                    {
                        /* Wake-up I/O is configured as pull-up */
                        wakeup_io_ctrl_reg |=
                            ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO2MODE_INDEX);
                    }
                    else
                    {
                        /* Wake-up I/O is configured as pull-down */
                        wakeup_io_ctrl_reg |=
                            ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO2MODE_INDEX);
                    }
                }
            }
        }
    }
    else
    {
        wakeup_io_ctrl_reg |= ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN << LOWPOWER_WAKEUPIOSRC_PIO2MODE_INDEX);
    }

    /* Wake-up I/O 3 */
    wake_up_type = (p_wakeup_io_ctrl & 0xC0UL) >> LOWPOWER_WAKEUPIOSRC_PIO3_INDEX;
    wakeup_io_ctrl_reg |= (wake_up_type << LOWPOWER_WAKEUPIOSRC_PIO3_INDEX);
    use_external_pullupdown = (uint8_t)((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO3_USEEXTERNALPULLUPDOWN_MASK) >>
                                        LOWPOWER_WAKEUPIO_PIO3_USEEXTERNALPULLUPDOWN_INDEX);

    if (use_external_pullupdown == 0UL)
    {
        if ((wake_up_type == 1UL) || (wake_up_type == 3UL))
        {
            /* Rising edge  and both rising and falling edges */
            IOCON->PIO[1][30] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(1); /* Pull down */
            wakeup_io_ctrl_reg |=
                ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO3MODE_INDEX);
        }
        else
        {
            if (wake_up_type == 2UL)
            {
                /* Falling edge only */
                IOCON->PIO[1][30] = IOCON_PIO_DIGIMODE(1) | IOCON_PIO_MODE(2); /* Pull up */
                wakeup_io_ctrl_reg |=
                    ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO3MODE_INDEX);
            }
            else
            {
                /* Wake-up I/O is disabled : set it as required by the user */
                if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO3_DISABLEPULLUPDOWN_MASK) != 0UL)
                {
                    /* Wake-up I/O is configured as Plain Input */
                    // @TODO not used                p_wakeup_io_ctrl &= ~LOWPOWER_WAKEUPIO_PIO3_PULLUPDOWN_MASK;
                    wakeup_io_ctrl_reg |=
                        ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN << LOWPOWER_WAKEUPIOSRC_PIO3MODE_INDEX);
                }
                else
                {
                    /* Wake-up I/O is configured as pull-up or pull-down */
                    // @TODO update for mask name
                    if ((p_wakeup_io_ctrl & LOWPOWER_WAKEUPIO_PIO3_PULLUPDOWN_MASK) != 0UL)
                    {
                        /* Wake-up I/O is configured as pull-up */
                        wakeup_io_ctrl_reg |=
                            ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP << LOWPOWER_WAKEUPIOSRC_PIO3MODE_INDEX);
                    }
                    else
                    {
                        /* Wake-up I/O is configured as pull-down */
                        wakeup_io_ctrl_reg |=
                            ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN << LOWPOWER_WAKEUPIOSRC_PIO3MODE_INDEX);
                    }
                }
            }
        }
    }
    else
    {
        wakeup_io_ctrl_reg |= ((uint32_t)LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN << LOWPOWER_WAKEUPIOSRC_PIO3MODE_INDEX);
    }

    return (wakeup_io_ctrl_reg);
}

/**
 * @brief
 * @param
 * @return
 */
static uint8_t CLOCK_u8OscCapConvert(uint8_t u8OscCap, uint8_t u8CapBankDiscontinuity)
{
    /* Compensate for discontinuity in the capacitor banks */
    if (u8OscCap < 64U)
    {
        if (u8OscCap >= u8CapBankDiscontinuity)
        {
            u8OscCap -= u8CapBankDiscontinuity;
        }
        else
        {
            u8OscCap = 0U;
        }
    }
    else
    {
        if (u8OscCap <= (127U - u8CapBankDiscontinuity))
        {
            u8OscCap += u8CapBankDiscontinuity;
        }
        else
        {
            u8OscCap = 127U;
        }
    }
    return u8OscCap;
}

/**
 * @brief             Described in fsl_common.h
 * @param
 * @return
 */
static void lowpower_set_system_voltage(uint32_t system_voltage_mv)
{
    /*
     * Set system voltage
     */
    uint32_t lv_ldo_ao       = (uint32_t)V_AO_1P100;   /* <ldo_ao> */
    uint32_t lv_ldo_ao_boost = (uint32_t)V_AO_1P150;   /* <ldo_ao_boost> */
    uint32_t lv_dcdc         = (uint32_t)V_DCDC_1P100; /* <dcdc> */

    if (system_voltage_mv <= 950UL)
    {
        lv_dcdc         = (uint32_t)V_DCDC_0P950;
        lv_ldo_ao       = (uint32_t)V_AO_0P960;
        lv_ldo_ao_boost = (uint32_t)V_AO_1P010;
    }
    else if (system_voltage_mv <= 975UL)
    {
        lv_dcdc         = (uint32_t)V_DCDC_0P975;
        lv_ldo_ao       = (uint32_t)V_AO_0P980;
        lv_ldo_ao_boost = (uint32_t)V_AO_1P030;
    }
    else if (system_voltage_mv <= 1000UL)
    {
        lv_dcdc         = (uint32_t)V_DCDC_1P000;
        lv_ldo_ao       = (uint32_t)V_AO_1P000;
        lv_ldo_ao_boost = (uint32_t)V_AO_1P050;
    }
    else if (system_voltage_mv <= 1025UL)
    {
        lv_dcdc         = (uint32_t)V_DCDC_1P025;
        lv_ldo_ao       = (uint32_t)V_AO_1P030;
        lv_ldo_ao_boost = (uint32_t)V_AO_1P080;
    }
    else if (system_voltage_mv <= 1050UL)
    {
        lv_dcdc         = (uint32_t)V_DCDC_1P050;
        lv_ldo_ao       = (uint32_t)V_AO_1P060;
        lv_ldo_ao_boost = (uint32_t)V_AO_1P110;
    }
    else if (system_voltage_mv <= 1075UL)
    {
        lv_dcdc         = (uint32_t)V_DCDC_1P075;
        lv_ldo_ao       = (uint32_t)V_AO_1P080;
        lv_ldo_ao_boost = (uint32_t)V_AO_1P130;
    }
    else if (system_voltage_mv <= 1100UL)
    {
        lv_dcdc         = (uint32_t)V_DCDC_1P100;
        lv_ldo_ao       = (uint32_t)V_AO_1P100;
        lv_ldo_ao_boost = (uint32_t)V_AO_1P150;
    }
    else if (system_voltage_mv <= 1125UL)
    {
        lv_dcdc         = (uint32_t)V_DCDC_1P125;
        lv_ldo_ao       = (uint32_t)V_AO_1P130;
        lv_ldo_ao_boost = (uint32_t)V_AO_1P160;
    }
    else if (system_voltage_mv <= 1150UL)
    {
        lv_dcdc         = (uint32_t)V_DCDC_1P150;
        lv_ldo_ao       = (uint32_t)V_AO_1P160;
        lv_ldo_ao_boost = (uint32_t)V_AO_1P220;
    }
    else if (system_voltage_mv <= 1175UL)
    {
        lv_dcdc         = (uint32_t)V_DCDC_1P175;
        lv_ldo_ao       = (uint32_t)V_AO_1P160;
        lv_ldo_ao_boost = (uint32_t)V_AO_1P220;
    }
    else
    {
        lv_dcdc         = (uint32_t)V_DCDC_1P200;
        lv_ldo_ao       = (uint32_t)V_AO_1P160;
        lv_ldo_ao_boost = (uint32_t)V_AO_1P220;
    }

    /* Set up LDO Always-On voltages */
    PMC->LDOPMU = (PMC->LDOPMU & (~PMC_LDOPMU_VADJ_MASK) & (~PMC_LDOPMU_VADJ_BOOST_MASK)) | PMC_LDOPMU_VADJ(lv_ldo_ao) |
                  PMC_LDOPMU_VADJ_BOOST(lv_ldo_ao_boost);

    /* Set up DCDC voltage */
    PMC->DCDC0 = (PMC->DCDC0 & (~PMC_DCDC0_VOUT_MASK)) | PMC_DCDC0_VOUT(lv_dcdc);
}

/**
 * @brief   Described in fsl_common.h
 * @param
 * @return
 */
static void lowpower_set_dcdc_power_profile(lowpower_dcdc_power_profile_enum dcdc_power_profile)
{
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ADDRS    (FLASH_NMPA_BASE + 0xE0U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_ADDRS    (FLASH_NMPA_BASE + 0xE4U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ADDRS (FLASH_NMPA_BASE + 0xE8U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_ADDRS (FLASH_NMPA_BASE + 0xECU)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ADDRS   (FLASH_NMPA_BASE + 0xD8U)
#define FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_ADDRS   (FLASH_NMPA_BASE + 0xDCU)

    const uint32_t PMC_DCDC0_DEFAULT = 0x010C4E68;
    const uint32_t PMC_DCDC1_DEFAULT = 0x01803A98;

    uint32_t dcdcTrimValue0;
    uint32_t dcdcTrimValue1;

    switch (dcdc_power_profile)
    {
        case DCDC_POWER_PROFILE_LOW:
            /* Low */
            dcdcTrimValue0 = (*((volatile unsigned int *)(FLASH_NMPA_DCDC_POWER_PROFILE_LOW_0_ADDRS)));
            dcdcTrimValue1 = (*((volatile unsigned int *)(FLASH_NMPA_DCDC_POWER_PROFILE_LOW_1_ADDRS)));

            if (0UL != (dcdcTrimValue0 & 0x1UL))
            {
                dcdcTrimValue0 = dcdcTrimValue0 >> 1;

                PMC->DCDC0 = dcdcTrimValue0;
                PMC->DCDC1 = dcdcTrimValue1;
#if (defined(NIOBE_DEBUG_LEVEL) && (NIOBE_DEBUG_LEVEL >= 1))
                PRINTF(
                    "\nINFO : DCDC Power Profile set to "
                    "LOW"
                    "\n");
#endif
            }
            break;

        case DCDC_POWER_PROFILE_MEDIUM:
            /* Medium */
            dcdcTrimValue0 = (*((volatile unsigned int *)(FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_0_ADDRS)));
            dcdcTrimValue1 = (*((volatile unsigned int *)(FLASH_NMPA_DCDC_POWER_PROFILE_MEDIUM_1_ADDRS)));

            if (0UL != (dcdcTrimValue0 & 0x1UL))
            {
                dcdcTrimValue0 = dcdcTrimValue0 >> 1;

                PMC->DCDC0 = dcdcTrimValue0;
                PMC->DCDC1 = dcdcTrimValue1;
#if (defined(NIOBE_DEBUG_LEVEL) && (NIOBE_DEBUG_LEVEL >= 1))
                PRINTF(
                    "\nINFO : DCDC Power Profile set to "
                    "MEDIUM"
                    "\n");
#endif
            }
            break;

        case DCDC_POWER_PROFILE_HIGH:
            /* High */
            dcdcTrimValue0 = (*((volatile unsigned int *)(FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_0_ADDRS)));
            dcdcTrimValue1 = (*((volatile unsigned int *)(FLASH_NMPA_DCDC_POWER_PROFILE_HIGH_1_ADDRS)));

            if (0UL != (dcdcTrimValue0 & 0x1UL))
            {
                dcdcTrimValue0 = dcdcTrimValue0 >> 1;

                PMC->DCDC0 = dcdcTrimValue0;
                PMC->DCDC1 = dcdcTrimValue1;
#if (defined(NIOBE_DEBUG_LEVEL) && (NIOBE_DEBUG_LEVEL >= 1))
                PRINTF(
                    "\nINFO : DCDC Power Profile set to "
                    "HIGH"
                    "\n");
#endif
            }
            break;

        default:
            /* Low */
            PMC->DCDC0 = PMC_DCDC0_DEFAULT;
            PMC->DCDC1 = PMC_DCDC1_DEFAULT;
#if (defined(NIOBE_DEBUG_LEVEL) && (NIOBE_DEBUG_LEVEL >= 1))
            PRINTF(
                "\nINFO : DCDC Power Profile set to "
                "LOW"
                "\n");
#endif
            break;
    }
}

/**
 * @brief
 * @param
 * @return
 */
static lowpower_process_corner_enum lowpower_get_part_process_corner(void)
{
#define FLASH_NMPA_PVT_MONITOR_0_RINGO_ADDRS (FLASH_NMPA_BASE + 0x130U)
#define FLASH_NMPA_PVT_MONITOR_1_RINGO_ADDRS (FLASH_NMPA_BASE + 0x140U)

    lowpower_process_corner_enum part_process_corner;
    uint32_t pvt_ringo_hz;
    uint32_t pvt_ringo_0 = (*((volatile unsigned int *)(FLASH_NMPA_PVT_MONITOR_0_RINGO_ADDRS)));
    uint32_t pvt_ringo_1 = (*((volatile unsigned int *)(FLASH_NMPA_PVT_MONITOR_1_RINGO_ADDRS)));

    /*
     * Check that the PVT Monitors Trimmings in flash are valid.
     */
    if (0UL != (pvt_ringo_0 & 0x1UL))
    {
        /* PVT Trimmings in Flash are valid */
        pvt_ringo_0 = pvt_ringo_0 >> 1;
    }
    else
    {
        /* PVT Trimmings in Flash are NOT valid (average value assumed) */
        pvt_ringo_0 = PROCESS_NNN_AVG_HZ;
    }

    if (0UL != (pvt_ringo_1 & 0x1UL))
    {
        /* PVT Trimmings in Flash are valid */
        pvt_ringo_1 = pvt_ringo_1 >> 1;
    }
    else
    {
        /* PVT Trimmings in Flash are NOT valid (average value assumed) */
        pvt_ringo_1 = PROCESS_NNN_AVG_HZ;
    }

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
#if (defined(NIOBE_DEBUG_LEVEL) && (NIOBE_DEBUG_LEVEL >= 1))
        PRINTF(
            "\nINFO : Process Corner : "
            "SSS"
            "\n");
#endif
    }
    else
    {
        if (pvt_ringo_hz <= PROCESS_NNN_MAX_HZ)
        {
            /* NNN Process Corner */
            part_process_corner = PROCESS_CORNER_NNN;
#if (defined(NIOBE_DEBUG_LEVEL) && (NIOBE_DEBUG_LEVEL >= 1))
            PRINTF(
                "\nINFO : Process Corner : "
                "NNN"
                "\n");
#endif
        }
        else
        {
            /* FFF Process Corner */
            part_process_corner = PROCESS_CORNER_FFF;
#if (defined(NIOBE_DEBUG_LEVEL) && (NIOBE_DEBUG_LEVEL >= 1))
            PRINTF(
                "\nINFO : Process Corner : "
                "FFF"
                "\n");
#endif
        }
    }

    return (part_process_corner);
}

/**
 * @brief   Described in fsl_common.h
 * @param
 * @return
 */
static void lowpower_set_voltage_for_process(lowpower_dcdc_power_profile_enum dcdc_power_profile)
{
    /* Get Sample Process Corner */
    lowpower_process_corner_enum part_process_corner = lowpower_get_part_process_corner();

    switch (part_process_corner)
    {
        case PROCESS_CORNER_SSS:
            /* Slow Corner */
            {
                switch (dcdc_power_profile)
                {
                    case DCDC_POWER_PROFILE_MEDIUM:
                        /* Medium */
                        lowpower_set_system_voltage(VOLTAGE_SSS_MED_MV);
                        break;

                    case DCDC_POWER_PROFILE_HIGH:
                        /* High */
                        lowpower_set_system_voltage(VOLTAGE_SSS_HIG_MV);
                        break;

                    default:
                        /* DCDC_POWER_PROFILE_LOW */
                        lowpower_set_system_voltage(VOLTAGE_SSS_LOW_MV);
                        break;
                } // switch(dcdc_power_profile)
            }
            break;

        case PROCESS_CORNER_FFF:
            /* Fast Corner */
            {
                switch (dcdc_power_profile)
                {
                    case DCDC_POWER_PROFILE_MEDIUM:
                        /* Medium */
                        lowpower_set_system_voltage(VOLTAGE_FFF_MED_MV);
                        break;

                    case DCDC_POWER_PROFILE_HIGH:
                        /* High */
                        lowpower_set_system_voltage(VOLTAGE_FFF_HIG_MV);
                        break;

                    default:
                        /* DCDC_POWER_PROFILE_LOW */
                        lowpower_set_system_voltage(VOLTAGE_FFF_LOW_MV);
                        break;
                } // switch(dcdc_power_profile)
            }
            break;

        default:
            /* Nominal (NNN) and all others Process Corners : assume Nominal Corner */
            {
                switch (dcdc_power_profile)
                {
                    case DCDC_POWER_PROFILE_MEDIUM:
                        /* Medium */
                        lowpower_set_system_voltage(VOLTAGE_NNN_MED_MV);
                        break;

                    case DCDC_POWER_PROFILE_HIGH:
                        /* High */
                        lowpower_set_system_voltage(VOLTAGE_NNN_HIG_MV);
                        break;

                    default:
                        /* DCDC_POWER_PROFILE_LOW */
                        lowpower_set_system_voltage(VOLTAGE_NNN_LOW_MV);
                        break;
                } // switch(dcdc_power_profile)
                break;
            }
    } // switch(part_process_corner)
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
        lowpower_set_dcdc_power_profile(DCDC_POWER_PROFILE_LOW); /* DCDC VOUT = 1.05 V by default */
        lowpower_set_voltage_for_process(DCDC_POWER_PROFILE_LOW);
    }
    else
    {
        if (system_freq_hz <= DCDC_POWER_PROFILE_MEDIUM_MAX_FREQ_HZ)
        {
            /* ]DCDC_POWER_PROFILE_LOW_MAX_FREQ_HZ Hz - DCDC_POWER_PROFILE_MEDIUM_MAX_FREQ_HZ Hz] */
            lowpower_set_dcdc_power_profile(DCDC_POWER_PROFILE_MEDIUM); /* DCDC VOUT = 1.15 V by default */
            lowpower_set_voltage_for_process(DCDC_POWER_PROFILE_MEDIUM);
        }
        else
        {
            /* > DCDC_POWER_PROFILE_MEDIUM_MAX_FREQ_HZ Hz */
            lowpower_set_dcdc_power_profile(DCDC_POWER_PROFILE_HIGH); /* DCDC VOUT = 1.2 V by default */
            lowpower_set_voltage_for_process(DCDC_POWER_PROFILE_HIGH);
        }
    }
}

void POWER_Xtal16mhzCapabankTrim(int32_t pi32_16MfXtalIecLoadpF_x100,
                                 int32_t pi32_16MfXtalPPcbParCappF_x100,
                                 int32_t pi32_16MfXtalNPcbParCappF_x100)
{
    uint32_t u32XOTrimValue;
    uint8_t u8IECXinCapCal6pF, u8IECXinCapCal8pF, u8IECXoutCapCal6pF, u8IECXoutCapCal8pF, u8XOSlave;
    int32_t iaXin_x4, ibXin, iaXout_x4, ibXout;
    int32_t iXOCapInpF_x100, iXOCapOutpF_x100;
    uint8_t u8XOCapInCtrl, u8XOCapOutCtrl;
    uint32_t u32RegVal;
    int32_t i32Tmp;

    /* Enable and set LDO, if not already done */
    POWER_SetXtal16mhzLdo();
    /* Get Cal values from Flash */
    u32XOTrimValue = GET_16MXO_TRIM();
    /* Check validity and apply */
    if ((0UL != (u32XOTrimValue & 1UL)) && (0UL != ((u32XOTrimValue >> 15UL) & 1UL)))
    {
        /* These fields are 7 bits, unsigned */
        u8IECXinCapCal6pF  = (uint8_t)((u32XOTrimValue >> 1UL) & 0x7fUL);
        u8IECXinCapCal8pF  = (uint8_t)((u32XOTrimValue >> 8UL) & 0x7fUL);
        u8IECXoutCapCal6pF = (uint8_t)((u32XOTrimValue >> 16UL) & 0x7fUL);
        u8IECXoutCapCal8pF = (uint8_t)((u32XOTrimValue >> 23UL) & 0x7fUL);
        /* This field is 1 bit */
        u8XOSlave = (uint8_t)((u32XOTrimValue >> 30UL) & 0x1UL);
        /* Linear fit coefficients calculation */
        iaXin_x4  = (int)u8IECXinCapCal8pF - (int)u8IECXinCapCal6pF;
        ibXin     = (int)u8IECXinCapCal6pF - iaXin_x4 * 3;
        iaXout_x4 = (int)u8IECXoutCapCal8pF - (int)u8IECXoutCapCal6pF;
        ibXout    = (int)u8IECXoutCapCal6pF - iaXout_x4 * 3;
    }
    else
    {
        iaXin_x4  = 20;  // gain in LSB/pF
        ibXin     = -9;  // offset in LSB
        iaXout_x4 = 20;  // gain in LSB/pF
        ibXout    = -13; // offset in LSB
        u8XOSlave = 0;
    }
    /* In & out load cap calculation with derating */
    iXOCapInpF_x100 = 2 * pi32_16MfXtalIecLoadpF_x100 - pi32_16MfXtalNPcbParCappF_x100 +
                      39 * ((int32_t)XO_SLAVE_EN - (int32_t)u8XOSlave) - 15;
    iXOCapOutpF_x100 = 2 * pi32_16MfXtalIecLoadpF_x100 - pi32_16MfXtalPPcbParCappF_x100 - 21;
    /* In & out XO_OSC_CAP_Code_CTRL calculation, with rounding */
    i32Tmp         = ((iXOCapInpF_x100 * iaXin_x4 + ibXin * 400) + 200) / 400;
    u8XOCapInCtrl  = (uint8_t)i32Tmp;
    i32Tmp         = ((iXOCapOutpF_x100 * iaXout_x4 + ibXout * 400) + 200) / 400;
    u8XOCapOutCtrl = (uint8_t)i32Tmp;
    /* Read register and clear fields to be written */
    u32RegVal = ANACTRL->XO32M_CTRL;
    u32RegVal &= ~(ANACTRL_XO32M_CTRL_OSC_CAP_IN_MASK | ANACTRL_XO32M_CTRL_OSC_CAP_OUT_MASK);
    /* Configuration of 32 MHz XO output buffers */
#if (XO_SLAVE_EN == 0)
    u32RegVal &= ~(ANACTRL_XO32M_CTRL_SLAVE_MASK | ANACTRL_XO32M_CTRL_ACBUF_PASS_ENABLE_MASK);
#else
    u32RegVal |= ANACTRL_XO32M_CTRL_SLAVE_MASK | ANACTRL_XO32M_CTRL_ACBUF_PASS_ENABLE_MASK;
#endif
    /* XO_OSC_CAP_Code_CTRL to XO_OSC_CAP_Code conversion */
    u32RegVal |= (uint32_t)CLOCK_u8OscCapConvert(u8XOCapInCtrl, 13) << ANACTRL_XO32M_CTRL_OSC_CAP_IN_SHIFT;
    u32RegVal |= (uint32_t)CLOCK_u8OscCapConvert(u8XOCapOutCtrl, 13) << ANACTRL_XO32M_CTRL_OSC_CAP_OUT_SHIFT;
    /* Write back to register */
    ANACTRL->XO32M_CTRL = u32RegVal;
}

void POWER_Xtal32khzCapabankTrim(int32_t pi32_32kfXtalIecLoadpF_x100,
                                 int32_t pi32_32kfXtalPPcbParCappF_x100,
                                 int32_t pi32_32kfXtalNPcbParCappF_x100)
{
    uint32_t u32XOTrimValue;
    uint8_t u8IECXinCapCal6pF, u8IECXinCapCal8pF, u8IECXoutCapCal6pF, u8IECXoutCapCal8pF;
    int32_t iaXin_x4, ibXin, iaXout_x4, ibXout;
    int32_t iXOCapInpF_x100, iXOCapOutpF_x100;
    uint8_t u8XOCapInCtrl, u8XOCapOutCtrl;
    uint32_t u32RegVal;
    int32_t i32Tmp;
    /* Get Cal values from Flash */
    u32XOTrimValue = GET_32KXO_TRIM();
    /* check validity and apply */
    if ((0UL != (u32XOTrimValue & 1UL)) && (0UL != ((u32XOTrimValue >> 15UL) & 1UL)))
    {
        /* These fields are 7 bits, unsigned */
        u8IECXinCapCal6pF  = (uint8_t)((u32XOTrimValue >> 1UL) & 0x7fUL);
        u8IECXinCapCal8pF  = (uint8_t)((u32XOTrimValue >> 8UL) & 0x7fUL);
        u8IECXoutCapCal6pF = (uint8_t)((u32XOTrimValue >> 16UL) & 0x7fUL);
        u8IECXoutCapCal8pF = (uint8_t)((u32XOTrimValue >> 23UL) & 0x7fUL);
        /* Linear fit coefficients calculation */
        iaXin_x4  = (int)u8IECXinCapCal8pF - (int)u8IECXinCapCal6pF;
        ibXin     = (int)u8IECXinCapCal6pF - iaXin_x4 * 3;
        iaXout_x4 = (int)u8IECXoutCapCal8pF - (int)u8IECXoutCapCal6pF;
        ibXout    = (int)u8IECXoutCapCal6pF - iaXout_x4 * 3;
    }
    else
    {
        iaXin_x4  = 16; // gain in LSB/pF
        ibXin     = 12; // offset in LSB
        iaXout_x4 = 16; // gain in LSB/pF
        ibXout    = 11; // offset in LSB
    }

    /* In & out load cap calculation with derating */
    iXOCapInpF_x100  = 2 * pi32_32kfXtalIecLoadpF_x100 - pi32_32kfXtalNPcbParCappF_x100 - 130;
    iXOCapOutpF_x100 = 2 * pi32_32kfXtalIecLoadpF_x100 - pi32_32kfXtalPPcbParCappF_x100 - 41;

    /* In & out XO_OSC_CAP_Code_CTRL calculation, with rounding */
    i32Tmp         = ((iXOCapInpF_x100 * iaXin_x4 + ibXin * 400) + 200) / 400;
    u8XOCapInCtrl  = (uint8_t)i32Tmp;
    i32Tmp         = ((iXOCapOutpF_x100 * iaXout_x4 + ibXout * 400) + 200) / 400;
    u8XOCapOutCtrl = (uint8_t)i32Tmp;

    /* Read register and clear fields to be written */
    u32RegVal = PMC->XTAL32K;
    u32RegVal &= ~(PMC_XTAL32K_CAPBANKIN_MASK | PMC_XTAL32K_CAPBANKOUT_MASK);

    /* XO_OSC_CAP_Code_CTRL to XO_OSC_CAP_Code conversion */
    u32RegVal |= (uint32_t)CLOCK_u8OscCapConvert(u8XOCapInCtrl, 23) << PMC_XTAL32K_CAPBANKIN_SHIFT;
    u32RegVal |= (uint32_t)CLOCK_u8OscCapConvert(u8XOCapOutCtrl, 23) << PMC_XTAL32K_CAPBANKOUT_SHIFT;

    /* Write back to register */
    PMC->XTAL32K = u32RegVal;
}

void POWER_SetXtal16mhzLdo(void)
{
    uint32_t temp;
    const uint32_t u32Mask =
        (ANACTRL_LDO_XO32M_VOUT_MASK | ANACTRL_LDO_XO32M_IBIAS_MASK | ANACTRL_LDO_XO32M_STABMODE_MASK);

    const uint32_t u32Value =
        (ANACTRL_LDO_XO32M_VOUT(0x5) | ANACTRL_LDO_XO32M_IBIAS(0x2) | ANACTRL_LDO_XO32M_STABMODE(0x1));

    /* Enable & set-up XTAL 32 MHz clock LDO */
    temp = ANACTRL->LDO_XO32M;

    if ((temp & u32Mask) != u32Value)
    {
        temp &= ~u32Mask;

        /*
         * Enable the XTAL32M LDO
         * Adjust the output voltage level, 0x5 for 1.1V
         * Adjust the biasing current, 0x2 value
         * Stability configuration, 0x1 default mode
         */
        temp |= u32Value;

        ANACTRL->LDO_XO32M = temp;

        /* Delay for LDO to be up */
        // CLOCK_uDelay(20);
    }

    /* Enable LDO XO32M */
    PMC->PDRUNCFGCLR0 = PMC_PDRUNCFG0_PDEN_LDOXO32M_MASK;
}

/*!
 * @brief set BOD VBAT level.
 *
 * @param level BOD detect level
 * @param hyst BoD Hysteresis control
 * @param enBodVbatReset VBAT brown out detect reset
 */
void POWER_SetBodVbatLevel(power_bod_vbat_level_t level, power_bod_hyst_t hyst, bool enBodVbatReset)
{
    uint32_t pmc_reset_ctrl;
    /* BOD VBAT disable reset */
    pmc_reset_ctrl =
        PMC->RESETCTRL & (~(PMC_RESETCTRL_BODVBATRESETENA_SECURE_MASK | PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_MASK));
    pmc_reset_ctrl |= (0x2UL << PMC_RESETCTRL_BODVBATRESETENA_SECURE_SHIFT) |
                      (0x2UL << PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_SHIFT);

    PMC->RESETCTRL = pmc_reset_ctrl;

    PMC->BODVBAT = (PMC->BODVBAT & (~(PMC_BODVBAT_TRIGLVL_MASK | PMC_BODVBAT_HYST_MASK))) | PMC_BODVBAT_TRIGLVL(level) |
                   PMC_BODVBAT_HYST(hyst);

    /* BOD VBAT enable reset */
    if ((uint32_t)enBodVbatReset == 1UL)
    {
        pmc_reset_ctrl &= (~(PMC_RESETCTRL_BODVBATRESETENA_SECURE_MASK | PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_MASK));
        pmc_reset_ctrl |= (0x1UL << PMC_RESETCTRL_BODVBATRESETENA_SECURE_SHIFT) |
                          (0x1UL << PMC_RESETCTRL_BODVBATRESETENA_SECURE_DP_SHIFT);
        PMC->RESETCTRL = pmc_reset_ctrl;
    }
}

#if defined(PMC_BODCORE_TRIGLVL_MASK)
/*!
 * @brief set BOD core level.
 *
 * @param level BOD detect level
 * @param hyst BoD Hysteresis control
 * @param enBodCoreReset core brown out detect reset
 */
void POWER_SetBodCoreLevel(power_bod_core_level_t level, power_bod_hyst_t hyst, bool enBodCoreReset)
{
    uint32_t pmc_reset_ctrl;
    /* BOD CORE disable reset */
    pmc_reset_ctrl =
        PMC->RESETCTRL & (~(PMC_RESETCTRL_BODCORERESETENA_SECURE_MASK | PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_MASK));
    pmc_reset_ctrl |=
        (0x2 << PMC_RESETCTRL_BODCORERESETENA_SECURE_SHIFT) | (0x2 << PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_SHIFT);

    PMC->RESETCTRL = pmc_reset_ctrl;

    PMC->BODCORE = (PMC->BODCORE & (~(PMC_BODCORE_TRIGLVL_MASK | PMC_BODCORE_HYST_MASK))) | PMC_BODCORE_TRIGLVL(level) |
                   PMC_BODCORE_HYST(hyst);

    /* BOD CORE enable reset */
    if (enBodCoreReset == 1)
    {
        pmc_reset_ctrl &= (~(PMC_RESETCTRL_BODCORERESETENA_SECURE_MASK | PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_MASK));
        pmc_reset_ctrl |= (0x1 << PMC_RESETCTRL_BODCORERESETENA_SECURE_SHIFT) |
                          (0x1 << PMC_RESETCTRL_BODCORERESETENA_SECURE_DP_SHIFT);
        PMC->RESETCTRL = pmc_reset_ctrl;
    }
}
#endif

/**
 * @brief   Return some key information related to the device reset causes / wake-up sources, for all power modes.
 * @param   p_reset_cause   : the device reset cause, according to the definition of power_device_reset_cause_t type.
 * @param   p_boot_mode     : the device boot mode, according to the definition of power_device_boot_mode_t type.
 * @param   p_wakeupio_cause: the wake-up pin sources, according to the definition of register PMC->WAKEIOCAUSE[3:0].

 * @return  Nothing
 *
 *         !!!  IMPORTANT ERRATA - IMPORTANT ERRATA - IMPORTANT ERRATA     !!!
 *         !!!   valid ONLY for LPC55S69 (not for LPC55S16 and LPC55S06)   !!!
 *         !!!   when FALLING EDGE DETECTION is enabled on wake-up pins:   !!!
 *         - 1. p_wakeupio_cause is NOT ACCURATE
 *         - 2. Spurious kRESET_CAUSE_DPDRESET_WAKEUPIO* event is reported when
 *              several wake-up sources are enabled during DEEP-POWER-DOWN
 *              (like enabling wake-up on RTC and Falling edge wake-up pins)
 *
 */
void POWER_GetWakeUpCause(power_device_reset_cause_t *p_reset_cause,
                          power_device_boot_mode_t *p_boot_mode,
                          uint32_t *p_wakeupio_cause)
{
    uint32_t reset_cause_reg;
    uint32_t boot_mode_reg;

#if (defined(LPC55S06_SERIES) || defined(LPC55S04_SERIES) || defined(LPC5506_SERIES) || defined(LPC5504_SERIES) || \
     defined(LPC5502_SERIES) || defined(LPC55S16_SERIES) || defined(LPC55S14_SERIES) || defined(LPC5516_SERIES) || \
     defined(LPC5514_SERIES) || defined(LPC5512_SERIES))
    reset_cause_reg = (PMC->AOREG1) & 0x3FF0UL;
#else /* LPC55S69/28 */
    reset_cause_reg = (PMC->AOREG1) & 0x1FF0UL;
#endif

    /*
     * Prioritize interrupts source with respect to their critical level
     */
#if (defined(LPC55S06_SERIES) || defined(LPC55S04_SERIES) || defined(LPC5506_SERIES) || defined(LPC5504_SERIES) || \
     defined(LPC5502_SERIES) || defined(LPC55S16_SERIES) || defined(LPC55S14_SERIES) || defined(LPC5516_SERIES) || \
     defined(LPC5514_SERIES) || defined(LPC5512_SERIES))
    if (0UL != (reset_cause_reg & PMC_AOREG1_CDOGRESET_MASK))
    { /* Code Watchdog Reset */
        *p_reset_cause    = kRESET_CAUSE_CDOGRESET;
        *p_boot_mode      = kBOOT_MODE_POWER_UP;
        *p_wakeupio_cause = 0; /* Device has not been waked-up by any wake-up pins */
    }
    else
#endif
    {
        if (0UL != (reset_cause_reg & PMC_AOREG1_WDTRESET_MASK))
        { /* Watchdog Timer Reset */
            *p_reset_cause    = kRESET_CAUSE_WDTRESET;
            *p_boot_mode      = kBOOT_MODE_POWER_UP;
            *p_wakeupio_cause = 0; /* Device has not been waked-up by any wake-up pins */
        }
        else
        {
            if (0UL != (reset_cause_reg & PMC_AOREG1_SYSTEMRESET_MASK))
            { /* ARM System Reset */
                *p_reset_cause    = kRESET_CAUSE_ARMSYSTEMRESET;
                *p_boot_mode      = kBOOT_MODE_POWER_UP;
                *p_wakeupio_cause = 0; /* Device has not been waked-up by any wake-up pins */
            }
            else
            {
                boot_mode_reg = (PMC->STATUS & PMC_STATUS_BOOTMODE_MASK) >> PMC_STATUS_BOOTMODE_SHIFT;

                if (boot_mode_reg == 0UL) /* POWER-UP: Power On Reset, Pin reset, Brown Out Detectors, Software Reset */
                {
                    *p_boot_mode      = kBOOT_MODE_POWER_UP; /* All non wake-up from a Low Power mode */
                    *p_wakeupio_cause = 0;                   /* Device has not been waked-up by any wake-up pins */

                    /*
                     * Prioritise Reset causes, starting from the strongest (Power On Reset)
                     */
                    if (0UL != (reset_cause_reg & PMC_AOREG1_POR_MASK))
                    { /* Power On Reset */
                        *p_reset_cause = kRESET_CAUSE_POR;
                    }
                    else
                    {
                        if (0UL != (reset_cause_reg & PMC_AOREG1_BODRESET_MASK))
                        { /* Brown-out Detector reset (either BODVBAT or BODCORE) */
                            *p_reset_cause = kRESET_CAUSE_BODRESET;
                        }
                        else
                        {
                            if (0UL != (reset_cause_reg & PMC_AOREG1_PADRESET_MASK))
                            { /* Hardware Pin Reset */
                                *p_reset_cause = kRESET_CAUSE_PADRESET;
                            }
                            else
                            {
                                if (0UL != (reset_cause_reg & PMC_AOREG1_SWRRESET_MASK))
                                { /* Software triggered Reset */
                                    *p_reset_cause = kRESET_CAUSE_SWRRESET;
                                }
                                else
                                { /* Unknown Reset Cause */
                                    *p_reset_cause = kRESET_CAUSE_NOT_DETERMINISTIC;
                                }
                            }
                        }
                    }

#if (defined(LPC55S06_SERIES) || defined(LPC55S04_SERIES) || defined(LPC5506_SERIES) || defined(LPC5504_SERIES) || \
     defined(LPC5502_SERIES) || defined(LPC55S16_SERIES) || defined(LPC55S14_SERIES) || defined(LPC5516_SERIES) || \
     defined(LPC5514_SERIES) || defined(LPC5512_SERIES))
                    /* Transfer the control of the 4 wake-up pins to IOCON (instead of the Power Management Controller
                     */
                    PMC->WAKEUPIOCTRL = PMC->WAKEUPIOCTRL & (~PMC_WAKEUPIOCTRL_WAKEUPIO_ENABLE_CTRL_MASK);
#endif
                }
                else /* DEEP-SLEEP, POWER-DOWN and DEEP-POWER-DOWN */
                {
                    /*
                     * 1- First, save wakeup_io_cause register ...
                     */
                    *p_wakeupio_cause = PMC->WAKEIOCAUSE;

                    if (boot_mode_reg == 3UL) /* DEEP-POWER-DOWN */
                    {
                        *p_boot_mode = kBOOT_MODE_LP_DEEP_POWER_DOWN;

                        switch (((reset_cause_reg >> PMC_AOREG1_DPDRESET_WAKEUPIO_SHIFT) & 0x7UL))
                        {
                            case 1:
                                *p_reset_cause = kRESET_CAUSE_DPDRESET_WAKEUPIO;
                                break;
                            case 2:
                                *p_reset_cause = kRESET_CAUSE_DPDRESET_RTC;
                                break;
                            case 3:
                                *p_reset_cause = kRESET_CAUSE_DPDRESET_WAKEUPIO_RTC;
                                break;
                            case 4:
                                *p_reset_cause = kRESET_CAUSE_DPDRESET_OSTIMER;
                                break;
                            case 5:
                                *p_reset_cause = kRESET_CAUSE_DPDRESET_WAKEUPIO_OSTIMER;
                                break;
                            case 6:
                                *p_reset_cause = kRESET_CAUSE_DPDRESET_RTC_OSTIMER;
                                break;
                            case 7:
                                *p_reset_cause = kRESET_CAUSE_DPDRESET_WAKEUPIO_RTC_OSTIMER;
                                break;
                            default:
                                /* Unknown Reset Cause */
                                *p_reset_cause = kRESET_CAUSE_NOT_DETERMINISTIC;
                                break;
                        }

#if (defined(LPC55S06_SERIES) || defined(LPC55S04_SERIES) || defined(LPC5506_SERIES) || defined(LPC5504_SERIES) || \
     defined(LPC5502_SERIES) || defined(LPC55S16_SERIES) || defined(LPC55S14_SERIES) || defined(LPC5516_SERIES) || \
     defined(LPC5514_SERIES) || defined(LPC5512_SERIES))
                        /*
                         * 2- Next, transfer the control of the 4 wake-up pins
                         * to IOCON (instead of the Power Management Controller)
                         */
                        PMC->WAKEUPIOCTRL = PMC->WAKEUPIOCTRL & (~PMC_WAKEUPIOCTRL_WAKEUPIO_ENABLE_CTRL_MASK);
#endif
                    }
                    else /* DEEP-SLEEP and POWER-DOWN */
                    {
                        *p_reset_cause = kRESET_CAUSE_NOT_RELEVANT;

                        /*
                         * The control of the 4 wake-up pins is already in IOCON,
                         * so there is nothing special to do.
                         */

                        if (boot_mode_reg == 1UL) /* DEEP-SLEEP */
                        {
                            *p_boot_mode = kBOOT_MODE_LP_DEEP_SLEEP;
                        }
                        else /* POWER-DOWN */
                        {
                            *p_boot_mode = kBOOT_MODE_LP_POWER_DOWN;

                        } /* if ( boot_mode_reg == 1 ) DEEP-SLEEP */

                    } /* if ( boot_mode == 3 )  DEEP-POWER-DOWN */

                } /* if ( boot_mode == 0 )  POWER-UP */

            } /* if ( reset_cause_reg & PMC_AOREG1_CDOGRESET_MASK ) */

        } /* if ( reset_cause_reg & PMC_AOREG1_WDTRESET_MASK ) */

    } /* if ( reset_cause_reg & PMC_AOREG1_SYSTEMRESET_MASK ) */
}
