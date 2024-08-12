/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PCFG_DRV_H
#define HPM_PCFG_DRV_H

#include "hpm_common.h"
#include "hpm_pcfg_regs.h"

/**
 *
 * @brief PCFG driver APIs
 * @defgroup pcfg_interface PCFG driver APIs
 * @ingroup io_interfaces
 * @{
 */
#define PCFG_CLOCK_GATE_MODE_ALWAYS_ON          (0x3UL)
#define PCFG_CLOCK_GATE_MODE_ALWAYS_OFF         (0x2UL)

#define PCFG_PERIPH_KEEP_CLOCK_ON(p) (PCFG_CLOCK_GATE_MODE_ALWAYS_ON << (p))
#define PCFG_PERIPH_KEEP_CLOCK_OFF(p) (PCFG_CLOCK_GATE_MODE_ALWAYS_OFF << (p))

/* @brief PCFG irc24m reference */
typedef enum {
    pcfg_irc24m_reference_32k = 0,
    pcfg_irc24m_reference_24m_xtal = 1
} pcfg_irc24m_reference_t;

/* @brief PCFG dcdc current limit */
typedef enum {
    pcfg_dcdc_lp_current_limit_250ma = 0,
    pcfg_dcdc_lp_current_limit_200ma = 1,
} pcfg_dcdc_lp_current_limit_t;

typedef enum {
    pcfg_dcdc_oc_limit_2000ma = 0,
    pcfg_dcdc_oc_limit_1300ma = 1,
} pcfg_dcdc_oc_limit_t;

/* @brief PCFG dcdc current hys */
typedef enum {
    pcfg_dcdc_current_hys_12_5mv = 0,
    pcfg_dcdc_current_hys_25mv = 1,
} pcfg_dcdc_current_hys_t;

/* @brief PCFG dcdc mode */
typedef enum {
    pcfg_dcdc_mode_off = 0,
    pcfg_dcdc_mode_basic = 1,
    pcfg_dcdc_mode_general = 3,
    pcfg_dcdc_mode_expert = 7,
} pcfg_dcdc_mode_t;

/* @brief PCFG pmc domain peripherals */
typedef enum {
    pcfg_pmc_periph_gpio = 6,
    pcfg_pmc_periph_ioc = 8,
    pcfg_pmc_periph_timer = 10,
    pcfg_pmc_periph_wdog = 12,
    pcfg_pmc_periph_uart = 14,
    pcfg_pmc_periph_vad = 16,
    pcfg_pmc_periph_pmic_mem = 18,
} pcfg_pmc_periph_t;

/* @brief PCFG status */
enum {
    status_pcfg_ldo_out_of_range = MAKE_STATUS(status_group_pcfg, 1),
};

/* @brief PCFG irc24m config */
typedef struct {
    uint32_t freq_in_hz;
    pcfg_irc24m_reference_t reference;
    bool return_to_default_on_xtal_loss;
    bool free_run;
} pcfg_irc24m_config_t;


#define PCFG_CLOCK_GATE_CONTROL_MASK(module, mode) \
    ((uint32_t) (mode) << ((module) << 1))

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief bandgap disable power save mode
 *
 * @param[in] ptr base address
 */
static inline void pcfg_bandgap_disable_power_save_mode(PCFG_Type *ptr)
{
    ptr->BANDGAP &= ~PCFG_BANDGAP_POWER_SAVE_MASK;
}

/**
 * @brief bandgap enable power save mode
 *
 * @param[in] ptr base address
 */
static inline void pcfg_bandgap_enable_power_save_mode(PCFG_Type *ptr)
{
    ptr->BANDGAP |= PCFG_BANDGAP_POWER_SAVE_MASK;
}

/**
 * @brief bandgap disable power save mode
 *
 * @param[in] ptr base address
 */
static inline void pcfg_bandgap_disable_lowpower_mode(PCFG_Type *ptr)
{
    ptr->BANDGAP &= ~PCFG_BANDGAP_LOWPOWER_MODE_MASK;
}

/**
 * @brief bandgap enable low power mode
 *
 * @param[in] ptr base address
 */
static inline void pcfg_bandgap_enable_lowpower_mode(PCFG_Type *ptr)
{
    ptr->BANDGAP |= PCFG_BANDGAP_LOWPOWER_MODE_MASK;
}

/**
 * @brief check if bandgap is trimmed or not
 *
 * @param[in] ptr base address
 *
 * @retval true if bandgap is trimmed
 */
static inline bool pcfg_bandgap_is_trimmed(PCFG_Type *ptr)
{
    return ptr->BANDGAP & PCFG_BANDGAP_VBG_TRIMMED_MASK;
}

/**
 * @brief bandgap reload trim value
 *
 * @param[in] ptr base address
 */
static inline void pcfg_bandgap_reload_trim(PCFG_Type *ptr)
{
    ptr->BANDGAP &= ~PCFG_BANDGAP_VBG_TRIMMED_MASK;
}

/**
 * @brief turn off LDO2P5
 *
 * @param[in] ptr base address
 */
static inline void pcfg_ldo2p5_turn_off(PCFG_Type *ptr)
{
    ptr->LDO2P5 &= ~PCFG_LDO2P5_ENABLE_MASK;
}

/**
 * @brief turn on LDO 2.5V
 *
 * @param[in] ptr base address
 */
static inline void pcfg_ldo2p5_turn_on(PCFG_Type *ptr)
{
    ptr->LDO2P5 |= PCFG_LDO2P5_ENABLE_MASK;
}

/**
 * @brief check if LDO 2.5V is stable
 *
 * @param[in] ptr base address
 *
 * @retval true if LDO2P5 is stable
 */
static inline bool pcfg_ldo2p5_is_stable(PCFG_Type *ptr)
{
    return PCFG_LDO2P5_READY_GET(ptr->LDO2P5);
}

/*
 * @brief check if DCDC is stable or not
 * @param[in] ptr base address
 * @retval true if DCDC is stable
 */
static inline bool pcfg_dcdc_is_stable(PCFG_Type *ptr)
{
    return PCFG_DCDC_MODE_READY_GET(ptr->DCDC_MODE);
}

/*
 * @brief set DCDC work mode
 * @param[in] ptr base address
 */
static inline void pcfg_dcdc_set_mode(PCFG_Type *ptr, uint8_t mode)
{
    ptr->DCDC_MODE = (ptr->DCDC_MODE & ~PCFG_DCDC_MODE_MODE_MASK) | PCFG_DCDC_MODE_MODE_SET(mode);
}

/**
 * @brief set low power current limit
 *
 * @param[in] ptr base address
 * @param[in] limit current limit at low power mode
 * @param[in] over_limit unused
 */
static inline void pcfg_dcdc_set_lp_current_limit(PCFG_Type *ptr, pcfg_dcdc_lp_current_limit_t limit, bool over_limit)
{
    (void) over_limit;
    ptr->DCDC_PROT = (ptr->DCDC_PROT & ~(PCFG_DCDC_PROT_ILIMIT_LP_MASK))
        | PCFG_DCDC_PROT_ILIMIT_LP_SET(limit);
}

/**
 * @brief disable power loss protection
 *
 * @param[in] ptr base address
 */
static inline void pcfg_dcdc_disable_power_loss_prot(PCFG_Type *ptr)
{
    ptr->DCDC_PROT |= PCFG_DCDC_PROT_DISABLE_POWER_LOSS_MASK;
}

/**
 * @brief enable power loss protection
 *
 * @param[in] ptr base address
 */
static inline void pcfg_dcdc_enable_power_loss_prot(PCFG_Type *ptr)
{
    ptr->DCDC_PROT &= ~PCFG_DCDC_PROT_DISABLE_POWER_LOSS_MASK;
}

/**
 * @brief check if power loss flag is set
 *
 * @param[in] ptr base address
 *
 * @retval true if power loss is set
 */
static inline bool pcfg_dcdc_is_power_loss(PCFG_Type *ptr)
{
    return PCFG_DCDC_PROT_POWER_LOSS_FLAG_GET(ptr->DCDC_PROT);
}

/**
 * @brief disable over voltage protection
 *
 * @param[in] ptr base address
 */
static inline void pcfg_dcdc_disable_over_voltage_prot(PCFG_Type *ptr)
{
    ptr->DCDC_PROT |= PCFG_DCDC_PROT_DISABLE_OVERVOLTAGE_MASK;
}

/**
 * @brief enable over voltage protection
 *
 * @param[in] ptr base address
 */
static inline void pcfg_dcdc_enable_over_voltage_prot(PCFG_Type *ptr)
{
    ptr->DCDC_PROT &= ~PCFG_DCDC_PROT_DISABLE_OVERVOLTAGE_MASK;
}

/**
 * @brief checkover over voltage flag
 *
 * @param[in] ptr base address
 * @retval true if flag is set
 */
static inline bool pcfg_dcdc_is_over_voltage(PCFG_Type *ptr)
{
    return PCFG_DCDC_PROT_OVERVOLT_FLAG_GET(ptr->DCDC_PROT);
}

/**
 * @brief disable over current protection
 *
 * @param[in] ptr base address
 */
static inline void pcfg_dcdc_disable_over_current_prot(PCFG_Type *ptr)
{
    ptr->DCDC_PROT |= PCFG_DCDC_PROT_DISABLE_SHORT_MASK;
}

/**
 * @brief enable over current protection
 *
 * @param[in] ptr base address
 */
static inline void pcfg_dcdc_enable_over_current_prot(PCFG_Type *ptr)
{
    ptr->DCDC_PROT &= ~PCFG_DCDC_PROT_DISABLE_SHORT_MASK;
}

/**
 * @brief set over current limit
 *
 * @param[in] ptr base address
 * @param[in] limit reference pcfg_dcdc_oc_limit_t
 */
static inline void pcfg_dcdc_set_over_current_limit(PCFG_Type *ptr, pcfg_dcdc_oc_limit_t limit)
{
    ptr->DCDC_PROT = (ptr->DCDC_PROT & ~PCFG_DCDC_PROT_SHORT_CURRENT_MASK) | PCFG_DCDC_PROT_SHORT_CURRENT_SET(limit);
}

/**
 * @brief checkover over current flag
 *
 * @param[in] ptr base address
 * @retval true if flag is set
 */
static inline bool pcfg_dcdc_is_over_current(PCFG_Type *ptr)
{
    return PCFG_DCDC_PROT_SHORT_FLAG_GET(ptr->DCDC_PROT);
}

/**
 * @brief disable current measurement
 *
 * @param[in] ptr base address
 */
static inline void pcfg_dcdc_disable_measure_current(PCFG_Type *ptr)
{
    ptr->DCDC_CURRENT &= ~PCFG_DCDC_CURRENT_ESTI_EN_MASK;
}

/**
 * @brief enable current measurement
 *
 * @param[in] ptr base address
 */
static inline void pcfg_dcdc_enable_measure_current(PCFG_Type *ptr)
{
    ptr->DCDC_CURRENT |= PCFG_DCDC_CURRENT_ESTI_EN_MASK;
}

/**
 * @brief check if measured current is valid
 *
 * @param[in] ptr base address
 *
 * @retval true if measured current is valid
 */
static inline bool pcfg_dcdc_is_measure_current_valid(PCFG_Type *ptr)
{
    return ptr->DCDC_CURRENT & PCFG_DCDC_CURRENT_VALID_MASK;
}

/**
 * @brief get measured current level
 *
 * @param[in] ptr base address
 *
 * @retval measured current, unit 50mA
 */
static inline bool pcfg_dcdc_get_measured_current_level(PCFG_Type *ptr)
{
    return PCFG_DCDC_CURRENT_LEVEL_GET(ptr->DCDC_CURRENT);
}

/**
 * @brief get DCDC start time in number of 24MHz clock cycles
 *
 * @param[in] ptr base address
 *
 * @retval dcdc start time in cycles
 */
static inline uint32_t pcfg_dcdc_get_start_time_in_cycle(PCFG_Type *ptr)
{
    return PCFG_DCDC_START_TIME_START_TIME_GET(ptr->DCDC_START_TIME);
}

/**
 * @brief get DCDC resume time in number of 24MHz clock cycles
 *
 * @param[in] ptr base address
 *
 * @retval dcdc resuem time in cycles
 */
static inline uint32_t pcfg_dcdc_get_resume_time_in_cycle(PCFG_Type *ptr)
{
    return PCFG_DCDC_RESUME_TIME_RESUME_TIME_GET(ptr->DCDC_RESUME_TIME);
}

/**
 * @brief set DCDC start time in 24MHz clock cycles
 *
 * @param[in] ptr base address
 * @param[in] cycles start time in cycles
 */
static inline void pcfg_dcdc_set_start_time_in_cycle(PCFG_Type *ptr, uint32_t cycles)
{
    ptr->DCDC_START_TIME = PCFG_DCDC_START_TIME_START_TIME_SET(cycles);
}

/**
 * @brief set DCDC resuem time in 24MHz clock cycles
 *
 * @param[in] ptr base address
 * @param[in] cycles resume time in cycles
 */
static inline void pcfg_dcdc_set_resume_time_in_cycle(PCFG_Type *ptr, uint32_t cycles)
{
    ptr->DCDC_RESUME_TIME = PCFG_DCDC_RESUME_TIME_RESUME_TIME_SET(cycles);
}

/**
 * @brief set dcdc current hysteres range
 *
 * @param[in] ptr base address
 * @param[in] range current hysteres range
 */
static inline void pcfg_dcdc_set_current_hys_range(PCFG_Type *ptr, pcfg_dcdc_current_hys_t range)
{
    ptr->DCDC_MISC = (ptr->DCDC_MISC & (~PCFG_DCDC_MISC_OL_HYST_MASK)) | PCFG_DCDC_MISC_OL_HYST_SET(range);
}

/**
 * @brief disable power trap
 *
 * @param[in] ptr base address
 */
static inline void pcfg_disable_power_trap(PCFG_Type *ptr)
{
    ptr->POWER_TRAP &= ~PCFG_POWER_TRAP_TRAP_MASK;
}

/**
 * @brief enable power trap
 *
 * @param[in] ptr base address
 */
static inline void pcfg_enable_power_trap(PCFG_Type *ptr)
{
    ptr->POWER_TRAP |= PCFG_POWER_TRAP_TRAP_MASK;
}

/**
 * @brief check if power trap is triggered
 *
 * @param[in] ptr base address
 *
 * @retval true if power trap is triggered
 */
static inline bool pcfg_is_power_trap_triggered(PCFG_Type *ptr)
{
    return ptr->POWER_TRAP & PCFG_POWER_TRAP_TRIGGERED_MASK;
}

/**
 * @brief clear power trap trigger flag
 *
 * @param[in] ptr base address
 */
static inline void pcfg_clear_power_trap_trigger_flag(PCFG_Type *ptr)
{
    ptr->POWER_TRAP |= PCFG_POWER_TRAP_TRIGGERED_MASK;
}

/**
 * @brief disable dcdc retention
 *
 * @param[in] ptr base address
 */
static inline void pcfg_disable_dcdc_retention(PCFG_Type *ptr)
{
    ptr->POWER_TRAP &= ~PCFG_POWER_TRAP_RETENTION_MASK;
}

/**
 * @brief enable dcdc retention to retain soc sram data
 *
 * @param[in] ptr base address
 */
static inline void pcfg_enable_dcdc_retention(PCFG_Type *ptr)
{
    ptr->POWER_TRAP |= PCFG_POWER_TRAP_RETENTION_MASK;
}

/**
 * @brief clear wakeup cause flag
 *
 * @param[in] ptr base address
 * @param[in] mask mask of flags to be cleared
 */
static inline void pcfg_clear_wakeup_cause(PCFG_Type *ptr, uint32_t mask)
{
    ptr->WAKE_CAUSE |= mask;
}

/**
 * @brief get wakeup cause
 *
 * @param[in] ptr base address
 *
 * @retval mask of wake cause
 */
static inline uint32_t pcfg_get_wakeup_cause(PCFG_Type *ptr)
{
    return ptr->WAKE_CAUSE;
}

/**
 * @brief enable wakeup source
 *
 * @param[in] ptr base address
 * @param[in] mask wakeup source mask
 */
static inline void pcfg_enable_wakeup_source(PCFG_Type *ptr, uint32_t mask)
{
    ptr->WAKE_MASK &= ~mask;
}

/**
 * @brief disable wakeup source
 *
 * @param[in] ptr base address
 * @param[in] mask source to be disabled as wakeup source
 */
static inline void pcfg_disable_wakeup_source(PCFG_Type *ptr, uint32_t mask)
{
    ptr->WAKE_MASK |= mask;
}

/**
 * @brief set clock gate mode in vpmc domain
 *
 * @param[in] ptr base address
 * @param[in] mode clock gate mode mask
 */
static inline void pcfg_set_periph_clock_mode(PCFG_Type *ptr, uint32_t mode)
{
    ptr->SCG_CTRL = mode;
}

/*
 * @brief check if DDR DCDC is stable or not
 * @param[in] ptr base address
 * @retval true if DDR DCDC is stable
 */
static inline bool pcfg_ddr_dcdc_is_stable(PCFG_Type *ptr)
{
    return PCFG_DCDCM_MODE_READY_GET(ptr->DCDCM_MODE);
}

/*
 * @brief set DDR DCDC work mode
 * @param[in] ptr base address
 */
static inline void pcfg_ddr_dcdc_set_mode(PCFG_Type *ptr, uint8_t mode)
{
    ptr->DCDCM_MODE = (ptr->DCDCM_MODE & ~PCFG_DCDCM_MODE_MODE_MASK) | PCFG_DCDCM_MODE_MODE_SET(mode);
}


/*
 * @brief set on-chip DDR DCDC enable and voltage
 * @param[in] ptr base address
 * @param[in] voltage unit mv
 */
static inline void pcfg_ddr_dcdc_set_voltage_output(PCFG_Type *ptr, uint8_t voltage)
{
    ptr->DCDCM_MODE = (ptr->DCDCM_MODE & ~(PCFG_DCDCM_MODE_VOLT_MASK | PCFG_DCDCM_MODE_MODE_MASK))
                        | PCFG_DCDCM_MODE_VOLT_SET(voltage) | PCFG_DCDCM_MODE_MODE_SET(pcfg_dcdc_mode_basic);
}

/**
 * @brief set ddr low power current limit
 *
 * @param[in] ptr base address
 * @param[in] limit current limit at low power mode
 */
static inline void pcfg_ddr_dcdc_set_lp_current_limit(PCFG_Type *ptr, pcfg_dcdc_lp_current_limit_t limit)
{
    ptr->DCDCM_PROT = (ptr->DCDCM_PROT & ~(PCFG_DCDCM_PROT_ILIMIT_LP_MASK))
        | PCFG_DCDCM_PROT_ILIMIT_LP_SET(limit);
}

/**
 * @brief disable ddr power loss protection
 *
 * @param[in] ptr base address
 */
static inline void pcfg_ddr_dcdc_disable_power_loss_prot(PCFG_Type *ptr)
{
    ptr->DCDCM_PROT |= PCFG_DCDCM_PROT_DISABLE_POWER_LOSS_MASK;
}

/**
 * @brief enable ddr power loss protection
 *
 * @param[in] ptr base address
 */
static inline void pcfg_ddr_dcdc_enable_power_loss_prot(PCFG_Type *ptr)
{
    ptr->DCDCM_PROT &= ~PCFG_DCDCM_PROT_DISABLE_POWER_LOSS_MASK;
}

/**
 * @brief check if ddr power loss flag is set
 *
 * @param[in] ptr base address
 *
 * @retval true if power loss is set
 */
static inline bool pcfg_ddr_dcdc_is_power_loss(PCFG_Type *ptr)
{
    return PCFG_DCDCM_PROT_POWER_LOSS_FLAG_GET(ptr->DCDCM_PROT);
}

/**
 * @brief disable ddr over voltage protection
 *
 * @param[in] ptr base address
 */
static inline void pcfg_ddr_dcdc_disable_over_voltage_prot(PCFG_Type *ptr)
{
    ptr->DCDCM_PROT |= PCFG_DCDCM_PROT_DISABLE_OVERVOLTAGE_MASK;
}

/**
 * @brief enable ddr over voltage protection
 *
 * @param[in] ptr base address
 */
static inline void pcfg_ddr_dcdc_enable_over_voltage_prot(PCFG_Type *ptr)
{
    ptr->DCDCM_PROT &= ~PCFG_DCDCM_PROT_DISABLE_OVERVOLTAGE_MASK;
}

/**
 * @brief checkover ddr over voltage flag
 *
 * @param[in] ptr base address
 * @retval true if flag is set
 */
static inline bool pcfg_ddr_dcdc_is_over_voltage(PCFG_Type *ptr)
{
    return PCFG_DCDCM_PROT_OVERVOLT_FLAG_GET(ptr->DCDCM_PROT);
}

/**
 * @brief disable ddr over current protection
 *
 * @param[in] ptr base address
 */
static inline void pcfg_ddr_dcdc_disable_over_current_prot(PCFG_Type *ptr)
{
    ptr->DCDCM_PROT |= PCFG_DCDCM_PROT_DISABLE_SHORT_MASK;
}

/**
 * @brief enable ddr over current protection
 *
 * @param[in] ptr base address
 */
static inline void pcfg_ddr_dcdc_enable_over_current_prot(PCFG_Type *ptr)
{
    ptr->DCDCM_PROT &= ~PCFG_DCDCM_PROT_DISABLE_SHORT_MASK;
}

/**
 * @brief set ddr over current limit
 *
 * @param[in] ptr base address
 * @param[in] limit reference pcfg_dcdc_oc_limit_t
 */
static inline void pcfg_ddr_dcdc_set_over_current_limit(PCFG_Type *ptr, pcfg_dcdc_oc_limit_t limit)
{
    ptr->DCDCM_PROT = (ptr->DCDCM_PROT & ~PCFG_DCDCM_PROT_SHORT_CURRENT_MASK) | PCFG_DCDCM_PROT_SHORT_CURRENT_SET(limit);
}

/**
 * @brief checkover ddr over current flag
 *
 * @param[in] ptr base address
 * @retval true if flag is set
 */
static inline bool pcfg_ddr_dcdc_is_over_current(PCFG_Type *ptr)
{
    return PCFG_DCDCM_PROT_SHORT_FLAG_GET(ptr->DCDCM_PROT);
}

/**
 * @brief disable ddr current measurement
 *
 * @param[in] ptr base address
 */
static inline void pcfg_ddr_dcdc_disable_measure_current(PCFG_Type *ptr)
{
    ptr->DCDCM_CURRENT &= ~PCFG_DCDCM_CURRENT_ESTI_EN_MASK;
}

/**
 * @brief enable ddr current measurement
 *
 * @param[in] ptr base address
 */
static inline void pcfg_ddr_dcdc_enable_measure_current(PCFG_Type *ptr)
{
    ptr->DCDCM_CURRENT |= PCFG_DCDCM_CURRENT_ESTI_EN_MASK;
}

/**
 * @brief check if measured ddr current is valid
 *
 * @param[in] ptr base address
 *
 * @retval true if measured ddr current is valid
 */
static inline bool pcfg_ddr_dcdc_is_measure_current_valid(PCFG_Type *ptr)
{
    return ptr->DCDCM_CURRENT & PCFG_DCDCM_CURRENT_VALID_MASK;
}

/**
 * @brief get measured ddr current level
 *
 * @param[in] ptr base address
 *
 * @retval measured ddr current, unit 50mA
 */
static inline bool pcfg_ddr_dcdc_get_measured_current_level(PCFG_Type *ptr)
{
    return PCFG_DCDCM_CURRENT_LEVEL_GET(ptr->DCDCM_CURRENT);
}

/**
 * @brief get ddr dcdc start time in number of 24MHz clock cycles
 *
 * @param[in] ptr base address
 *
 * @retval ddr dcdc start time in cycles
 */
static inline uint32_t pcfg_ddr_dcdc_get_start_time_in_cycle(PCFG_Type *ptr)
{
    return PCFG_DCDCM_START_TIME_START_TIME_GET(ptr->DCDCM_START_TIME);
}

/**
 * @brief get ddr dcdc resume time in number of 24MHz clock cycles
 *
 * @param[in] ptr base address
 *
 * @retval ddr dcdc resuem time in cycles
 */
static inline uint32_t pcfg_ddr_dcdc_get_resume_time_in_cycle(PCFG_Type *ptr)
{
    return PCFG_DCDCM_RESUME_TIME_RESUME_TIME_GET(ptr->DCDCM_RESUME_TIME);
}

/**
 * @brief set ddr dcdc start time in 24MHz clock cycles
 *
 * @param[in] ptr base address
 * @param[in] cycles start time in cycles
 */
static inline void pcfg_ddr_dcdc_set_start_time_in_cycle(PCFG_Type *ptr, uint32_t cycles)
{
    ptr->DCDCM_START_TIME = PCFG_DCDCM_START_TIME_START_TIME_SET(cycles);
}

/**
 * @brief set ddr dcdc resuem time in 24MHz clock cycles
 *
 * @param[in] ptr base address
 * @param[in] cycles resume time in cycles
 */
static inline void pcfg_ddr_dcdc_set_resume_time_in_cycle(PCFG_Type *ptr, uint32_t cycles)
{
    ptr->DCDCM_RESUME_TIME = PCFG_DCDCM_RESUME_TIME_RESUME_TIME_SET(cycles);
}

/**
 * @brief set ddr dcdc current hysteres range
 *
 * @param[in] ptr base address
 * @param[in] range current hysteres range
 */
static inline void pcfg_ddr_dcdc_set_current_hys_range(PCFG_Type *ptr, pcfg_dcdc_current_hys_t range)
{
    ptr->DCDCM_MISC = (ptr->DCDCM_MISC & (~PCFG_DCDCM_MISC_OL_HYST_MASK)) | PCFG_DCDCM_MISC_OL_HYST_SET(range);
}

/**
 * @brief disable ddr dcdc retention
 *
 * @param[in] ptr base address
 */
static inline void pcfg_ddr_dcdc_disable_retention(PCFG_Type *ptr)
{
    ptr->DCDCM_POWER_CONFIG &= ~PCFG_DCDCM_POWER_CONFIG_RETENTION_MASK;
}

/**
 * @brief enable ddr dcdc retention to retain soc sram data
 *
 * @param[in] ptr base address
 */
static inline void pcfg_ddr_dcdc_enable_retention(PCFG_Type *ptr)
{
    ptr->DCDCM_POWER_CONFIG |= PCFG_DCDCM_POWER_CONFIG_RETENTION_MASK;
}

/**
 * @brief check if irc24m is trimmed
 *
 * @param[in] ptr base address
 *
 * @retval true if it is trimmed
 */
static inline bool pcfg_irc24m_is_trimmed(PCFG_Type *ptr)
{
    return ptr->RC24M & PCFG_RC24M_RC_TRIMMED_MASK;
}

/**
 * @brief reload irc24m trim value
 *
 * @param[in] ptr base address
 */
static inline void pcfg_irc24m_reload_trim(PCFG_Type *ptr)
{
    ptr->RC24M &= ~PCFG_RC24M_RC_TRIMMED_MASK;
}

/**
 * @brief config irc24m track
 *
 * @param[in] ptr base address
 * @param[in] config config data
 */
void pcfg_irc24m_config_track(PCFG_Type *ptr, pcfg_irc24m_config_t *config);

/*
 * @brief set DCDC voltage at standby mode
 * @param[in] ptr base address
 * @param[in] mv target voltage
 * @retval status_success if successfully configured
 */
hpm_stat_t pcfg_dcdc_set_lpmode_voltage(PCFG_Type *ptr, uint16_t mv);

/*
 * @brief set output voltage of LDO 2.5V in mV
 * @param[in] ptr base address
 * @param[in] mv target voltage
 * @retval status_success if successfully configured
 */
hpm_stat_t pcfg_ldo2p5_set_voltage(PCFG_Type *ptr, uint16_t mv);

/*
 * @brief set DCDC voltage
 * @param[in] ptr base address
 * @param[in] mv target voltage
 * @retval status_success if successfully configured
 */
hpm_stat_t pcfg_dcdc_set_voltage(PCFG_Type *ptr, uint16_t mv);

/*
 * @brief set output voltage of LDO 1V in mV
 * @param[in] ptr base address
 * @param[in] mv target voltage
 * @retval status_success if successfully configured
 */
hpm_stat_t pcfg_ldo1p1_set_voltage(PCFG_Type *ptr, uint16_t mv);

/*
 * @brief get current DCDC current level in mA
 *
 * @param[in] ptr base address
 * @retval Current level at mA
 */
uint16_t pcfg_dcdc_get_current_level(PCFG_Type *ptr);


#ifdef __cplusplus
}
#endif
/**
 * @}
 */

#endif /* HPM_PCFG_DRV_H */
