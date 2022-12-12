/*
 * Copyright (c) 2021 hpmicro
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

#define PCFG_DCDC_MODE_TURN_OFF   (0U)
#define PCFG_DCDC_MODE_PERFORMACE (1U)
#define PCFG_DCDC_MODE_GENERIC    (2U)
#define PCFG_DCDC_MODE_EXPERT     (3U)

#define PCFG_CLOCK_GATE_MODE_ALWAYS_ON          (0x11U)
#define PCFG_CLOCK_GATE_MODE_ALWAYS_OFF         (0x10U)
#define PCFG_CLOCK_GATE_MODE_ALWAYS_FOLLOW_FLOW (0x01U)

/* @brief PCFG modules */
typedef enum {
    pcfg_module_fuse = 0,
    pcfg_module_sram,
    pcfg_module_vad,
    pcfg_module_gpio,
    pcfg_module_ioc,
    pcfg_module_timer,
    pcfg_module_wdog,
    pcfg_module_uart,
    pcfg_module_debug,
} pcfg_module_t;

/* @brief PCFG irc24m reference */
typedef enum {
    pcfg_irc24m_reference_32k = 0,
    pcfg_irc24m_reference_24m_xtal = 1
} pcfg_irc24m_reference_t;

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

#define PCFG_DEBUG_STOP_SOURCE_ENABLE_CORE0 (PCFG_DEBUG_STOP_CPU0_MASK)
#define PCFG_DEBUG_STOP_SOURCE_DISABLE_CORE0 (0)
#define PCFG_DEBUG_STOP_SOURCE_ENABLE_CORE1 (PCFG_DEBUG_STOP_CPU1_MASK)
#define PCFG_DEBUG_STOP_SOURCE_DISABLE_CORE1 (0)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief bandgap disable power save mode
 *
 * @param ptr base address
 */
static inline void pcfg_bandgap_disable_power_save_mode(PCFG_Type *ptr)
{
    ptr->BANDGAP &= ~PCFG_BANDGAP_POWER_SAVE_MASK;
}

/**
 * @brief bandgap enable power save mode
 *
 * @param ptr base address
 */
static inline void pcfg_bandgap_enable_power_save_mode(PCFG_Type *ptr)
{
    ptr->BANDGAP |= PCFG_BANDGAP_POWER_SAVE_MASK;
}

static inline void pcfg_bandgap_disable_lowpower_mode(PCFG_Type *ptr)
{
    ptr->BANDGAP &= ~PCFG_BANDGAP_LOWPOWER_MODE_MASK;
}

/**
 * @brief bandgap enable low power mode
 *
 * @param ptr base address
 */
static inline void pcfg_bandgap_enable_lowpower_mode(PCFG_Type *ptr)
{
    ptr->BANDGAP |= PCFG_BANDGAP_LOWPOWER_MODE_MASK;
}

/**
 * @brief check if bandgap is trimmed or not
 *
 * @param ptr base address
 *
 * @return true if bandgap is trimmed
 */
static inline bool pcfg_bandgap_is_trimmed(PCFG_Type *ptr)
{
    return ptr->BANDGAP & PCFG_BANDGAP_VBG_TRIMMED_MASK;
}

/**
 * @brief bandgap reload trim value
 *
 * @param ptr base address
 */
static inline void pcfg_bandgap_reload_trim(PCFG_Type *ptr)
{
    ptr->BANDGAP &= ~PCFG_BANDGAP_VBG_TRIMMED_MASK;
}

/**
 * @brief turn off LDO 1V
 *
 * @param ptr base address
 */
static inline void pcfg_ldo1p1_turn_off(PCFG_Type *ptr)
{
    ptr->LDO1P1 &= ~PCFG_LDO1P1_ENABLE_MASK;
}

/**
 * @brief turn of LDO 1V
 *
 * @param ptr base address
 */
static inline void pcfg_ldo1p1_turn_on(PCFG_Type *ptr)
{
    ptr->LDO1P1 |= PCFG_LDO1P1_ENABLE_MASK;
}

/*
 * @brief set output voltage of LDO 1V in mV
 * @param ptr base address
 * @param mv target voltage
 * @retval status_success if successfully configured
 */
hpm_stat_t pcfg_ldo1p1_set_voltage(PCFG_Type *ptr, uint16_t mv);

/**
 * @brief turn off LDO2P5
 *
 * @param ptr base address
 */
static inline void pcfg_ldo2p5_turn_off(PCFG_Type *ptr)
{
    ptr->LDO2P5 &= ~PCFG_LDO2P5_ENABLE_MASK;
}

/**
 * @brief turn on LDO 2.5V
 *
 * @param ptr base address
 */
static inline void pcfg_ldo2p5_turn_on(PCFG_Type *ptr)
{
    ptr->LDO2P5 |= PCFG_LDO2P5_ENABLE_MASK;
}

/**
 * @brief check if LDO 2.5V is stable
 *
 * @param ptr base address
 *
 * @return true if LDO2P5 is stable
 */
static inline bool pcfg_ldo2p5_is_stable(PCFG_Type *ptr)
{
    return PCFG_LDO2P5_READY_GET(ptr->LDO2P5);
}
/*
 * @brief set output voltage of LDO 2.5V in mV
 * @param ptr base address
 * @param mv target voltage
 * @retval status_success if successfully configured
 */
hpm_stat_t pcfg_ldo2p5_set_voltage(PCFG_Type *ptr, uint16_t mv);

/*
 * @brief set DCDC voltage
 * @param ptr base address
 * @param mv target voltage
 * @retval status_success if successfully configured
 */
hpm_stat_t pcfg_dcdc_set_voltage(PCFG_Type *ptr, uint16_t mv);

/*
 * @brief check if DCDC is stable or not
 * @param ptr base address
 * @retval true if DCDC is stable
 */
static inline bool pcfg_dcdc_is_stable(PCFG_Type *ptr)
{
    return PCFG_DCDC_MODE_READY_GET(ptr->DCDC_MODE);
}

/*
 * @brief check if DCDC is stable or not
 * @param ptr base address
 */
static inline void pcfg_dcdc_set_mode(PCFG_Type *ptr, uint8_t mode)
{
    ptr->DCDC_MODE = (ptr->DCDC_MODE & ~PCFG_DCDC_MODE_MODE_MASK) | PCFG_DCDC_MODE_MODE_SET(ptr->DCDC_MODE);
}

/*
 * @brief set DCDC voltage at standby mode
 * @param ptr base address
 * @param mv target voltage
 * @retval status_success if successfully configured
 */
hpm_stat_t pcfg_dcdc_set_lpmode_voltage(PCFG_Type *ptr, uint16_t mv);

/**
 * @brief set low power current limit
 *
 * @param ptr base address
 * @param limit current limit at low power mode
 * @param under_limit set to true means current is less than limit
 */
static inline void pcfg_dcdc_set_lp_current_limit(PCFG_Type *ptr, uint8_t limit, bool under_limit)
{
    ptr->DCDC_PROT = (ptr->DCDC_PROT & ~(PCFG_DCDC_PROT_ILIMIT_LP_MASK | PCFG_DCDC_PROT_OVERLOAD_LP_MASK))
        | PCFG_DCDC_PROT_ILIMIT_LP_SET(limit) | PCFG_DCDC_PROT_OVERLOAD_LP_SET(!under_limit);
}

/**
 * @brief disable power loss protection
 *
 * @param ptr base address
 */
static inline void pcfg_dcdc_disable_power_loss_prot(PCFG_Type *ptr)
{
    ptr->DCDC_PROT |= PCFG_DCDC_PROT_DISABLE_POWER_LOSS_MASK;
}

/**
 * @brief enable power loss protection
 *
 * @param ptr base address
 */
static inline void pcfg_dcdc_enable_power_loss_prot(PCFG_Type *ptr)
{
    ptr->DCDC_PROT &= ~PCFG_DCDC_PROT_DISABLE_POWER_LOSS_MASK;
}

/**
 * @brief check if power loss flag is set
 *
 * @param ptr base address
 *
 * @return true if power loss is set
 */
static inline bool pcfg_dcdc_is_power_loss(PCFG_Type *ptr)
{
    return PCFG_DCDC_PROT_POWER_LOSS_FLAG_GET(ptr->DCDC_PROT);
}

/**
 * @brief disable over voltage protection
 *
 * @param ptr base address
 */
static inline void pcfg_dcdc_disable_over_voltage_prot(PCFG_Type *ptr)
{
    ptr->DCDC_PROT |= PCFG_DCDC_PROT_DISABLE_OVERVOLTAGE_MASK;
}

/**
 * @brief enable over voltage protection
 *
 * @param ptr base address
 */
static inline void pcfg_dcdc_ensable_over_voltage_prot(PCFG_Type *ptr)
{
    ptr->DCDC_PROT &= ~PCFG_DCDC_PROT_DISABLE_OVERVOLTAGE_MASK;
}

/**
 * @brief checkover voltage flag
 *
 * @param ptr base address
 * @return true if flag is set
 */
static inline bool pcfg_dcdc_is_over_voltage(PCFG_Type *ptr)
{
    return PCFG_DCDC_PROT_OVERVOLT_FLAG_GET(ptr->DCDC_PROT) & PCFG_DCDC_PROT_OVERVOLT_FLAG_MASK;
}

/**
 * @brief disable current measurement
 *
 * @param ptr base address
 */
static inline void pcfg_dcdc_disable_measure_current(PCFG_Type *ptr)
{
    ptr->DCDC_CURRENT &= ~PCFG_DCDC_CURRENT_ESTI_EN_MASK;
}

/**
 * @brief enable current measurement
 *
 * @param ptr base address
 */
static inline void pcfg_dcdc_enable_measure_current(PCFG_Type *ptr)
{
    ptr->DCDC_CURRENT |= PCFG_DCDC_CURRENT_ESTI_EN_MASK;
}

/**
 * @brief check if measured current is valid
 *
 * @param ptr base address
 *
 * @return true if measured current is valid
 */
static inline bool pcfg_dcdc_is_measure_current_valid(PCFG_Type *ptr)
{
    return ptr->DCDC_CURRENT & PCFG_DCDC_CURRENT_VALID_MASK;
}

/*
 * @brief get current DCDC current level in mA
 *
 * @param ptr base address
 * @retval Current level at mA
 */
uint16_t pcfg_dcdc_get_current_level(PCFG_Type *ptr);

/**
 * @brief get DCDC start time in number of 24MHz clock cycles
 *
 * @param ptr base address
 *
 * @return dcdc start time in cycles
 */
static inline uint32_t pcfg_get_dcdc_start_time_in_cycle(PCFG_Type *ptr)
{
    return PCFG_DCDC_START_TIME_START_TIME_GET(ptr->DCDC_START_TIME);
}

/**
 * @brief get DCDC resume time in number of 24MHz clock cycles
 *
 * @param ptr base address
 *
 * @return dcdc resuem time in cycles
 */
static inline uint32_t pcfg_get_dcdc_resume_time_in_cycle(PCFG_Type *ptr)
{
    return PCFG_DCDC_RESUME_TIME_RESUME_TIME_GET(ptr->DCDC_RESUME_TIME);
}

/**
 * @brief set DCDC start time in 24MHz clock cycles
 *
 * @param ptr base address
 * @param cycles start time in cycles
 */
static inline void pcfg_set_dcdc_start_time_in_cycle(PCFG_Type *ptr, uint32_t cycles)
{
    ptr->DCDC_START_TIME = PCFG_DCDC_START_TIME_START_TIME_SET(cycles);
}

/**
 * @brief set DCDC resuem time in 24MHz clock cycles
 *
 * @param ptr base address
 * @param cycles resume time in cycles
 */
static inline void pcfg_set_dcdc_resume_time_in_cycle(PCFG_Type *ptr, uint32_t cycles)
{
    ptr->DCDC_RESUME_TIME = PCFG_DCDC_RESUME_TIME_RESUME_TIME_SET(cycles);
}

/**
 * @brief disable power trap
 *
 * @param ptr base address
 */
static inline void pcfg_disable_power_trap(PCFG_Type *ptr)
{
    ptr->POWER_TRAP &= ~PCFG_POWER_TRAP_TRAP_MASK;
}

/**
 * @brief enable power trap
 *
 * @param ptr base address
 */
static inline void pcfg_enable_power_trap(PCFG_Type *ptr)
{
    ptr->POWER_TRAP |= PCFG_POWER_TRAP_TRAP_MASK;
}

/**
 * @brief check if power trap is triggered
 *
 * @param ptr base address
 *
 * @return true if power trap is triggered
 */
static inline bool pcfg_is_power_trap_triggered(PCFG_Type *ptr)
{
    return ptr->POWER_TRAP & PCFG_POWER_TRAP_TRIGGERED_MASK;
}

/**
 * @brief clear power trap trigger flag
 *
 * @param ptr base address
 */
static inline void pcfg_clear_power_trap_trigger_flag(PCFG_Type *ptr)
{
    ptr->POWER_TRAP |= PCFG_POWER_TRAP_TRIGGERED_MASK;
}

/**
 * @brief disable dcdc retention
 *
 * @param ptr base address
 */
static inline void pcfg_disable_dcdc_retention(PCFG_Type *ptr)
{
    ptr->POWER_TRAP &= ~PCFG_POWER_TRAP_RETENTION_MASK;
}

/**
 * @brief enable dcdc retention to retain soc sram data
 *
 * @param ptr base address
 */
static inline void pcfg_enable_dcdc_retention(PCFG_Type *ptr)
{
    ptr->POWER_TRAP |= PCFG_POWER_TRAP_RETENTION_MASK;
}

/**
 * @brief clear wakeup cause flag
 *
 * @param ptr base address
 * @param mask mask of flags to be cleared
 */
static inline void pcfg_clear_wakeup_cause(PCFG_Type *ptr, uint32_t mask)
{
    ptr->WAKE_CAUSE |= mask;
}

/**
 * @brief get wakeup cause
 *
 * @param ptr base address
 *
 * @return mask of wake cause
 */
static inline uint32_t pcfg_get_wakeup_cause(PCFG_Type *ptr)
{
    return ptr->WAKE_CAUSE;
}

/**
 * @brief enable wakeup source
 *
 * @param ptr base address
 * @param mask wakeup source mask
 */
static inline void pcfg_enable_wakeup_source(PCFG_Type *ptr, uint32_t mask)
{
    ptr->WAKE_MASK &= ~mask;
}

/**
 * @brief disable wakeup source
 *
 * @param ptr base address
 * @param mask source to be disabled as wakeup source
 */
static inline void pcfg_disable_wakeup_source(PCFG_Type *ptr, uint32_t mask)
{
    ptr->WAKE_MASK |= mask;
}

/**
 * @brief set clock gate mode in pmic domain
 *
 * @param ptr base address
 * @param mode clock gate mode mask
 */
static inline void pcfg_set_clock_gate_in_pmic(PCFG_Type *ptr, uint32_t mode)
{
    ptr->SCG_CTRL = mode;
}

static inline void pcfg_config_debug_stop_source(PCFG_Type *ptr, uint8_t mask)
{
    ptr->DEBUG_STOP = mask;
}

/**
 * @brief check if irc24m is trimmed
 *
 * @param ptr base address
 *
 * @return true if it is trimmed
 */
static inline bool pcfg_irc24m_is_trimmed(PCFG_Type *ptr)
{
    return ptr->RC24M & PCFG_RC24M_RC_TRIMMED_MASK;
}

/**
 * @brief reload irc24m trim value
 *
 * @param ptr base address
 */
static inline void pcfg_irc24m_reload_trim(PCFG_Type *ptr)
{
    ptr->RC24M &= ~PCFG_RC24M_RC_TRIMMED_MASK;
}

/**
 * @brief config irc24m track
 *
 * @param ptr base address
 * @param config config data
 */
void pcfg_irc24m_config_track(PCFG_Type *ptr, pcfg_irc24m_config_t *config);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */

#endif /* HPM_PMIC_PCFG_DRV_H */
