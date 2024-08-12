/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PWM_DRV_H
#define HPM_PWM_DRV_H

#include "hpm_common.h"
#include "hpm_pwm_regs.h"
#include "hpm_soc_feature.h"
/**
 * @brief PWM driver APIs
 * @defgroup pwm_interface PWM driver APIs
 * @ingroup motor_interfaces
 * @{
 *
 */
#define PWM_UNLOCK_KEY (0xB0382607UL)

/* IRQ enable bit mask */
#define PWM_IRQ_FAULT PWM_IRQEN_FAULTIRQE_MASK
#define PWM_IRQ_EX_RELOAD PWM_IRQEN_XRLDIRQE_MASK
#define PWM_IRQ_HALF_RELOAD PWM_IRQEN_HALFRLDIRQE_MASK
#define PWM_IRQ_RELOAD PWM_IRQEN_RLDIRQE_MASK
#define PWM_IRQ_CMP(x) PWM_IRQEN_CMPIRQEX_SET((1 << x))

/* PWM force output mask */
#define PWM_FORCE_OUTPUT(pwm_index, force_output) \
    (force_output << (pwm_index << 1))

#define PWM_DUTY_CYCLE_FP_MAX ((1U << 24) - 1)

/**
 * @brief pwm trigger mode
 *
 */
typedef enum pwm_counter_type {
    pwm_counter_type_capture_rising_edge,   /**< rising edge trigger*/
    pwm_counter_type_capture_falling_edge,  /**< falling edge trigger*/
} pwm_counter_type_t;

/**
 * @brief pwm cmp mode
 *
 */
typedef enum pwm_cmp_mode {
    pwm_cmp_mode_output_compare = 0,    /**< output compare*/
    pwm_cmp_mode_input_capture = 1,     /**< input compare*/
} pwm_cmp_mode_t;

/**
 * @brief update time of the shadow register
 *
 */
typedef enum pwm_register_update {
    pwm_shadow_register_update_on_shlk = 0,     /**< after software set shlk bit of shlk register*/
    pwm_shadow_register_update_on_modify = 1,   /**<  immediately after the register being modified*/
    pwm_shadow_register_update_on_hw_event = 2, /**<  after hardware event assert*/
    pwm_shadow_register_update_on_sh_synci = 3, /**< after SHSYNCI assert */
} pwm_shadow_register_update_trigger_t;

/**
 * @brief configure the state of channel 0-7 outputs when the forced output is in effect
 *
 */
typedef enum pwm_fault_mode {
    pwm_fault_mode_force_output_0 = 0, /**< fault forced output logic 0 */
    pwm_fault_mode_force_output_1 = 1,  /**< fault forced output logic 1 */
    pwm_fault_mode_force_output_highz = 2,  /**< turn off output, pin becomes high resistance */
} pwm_fault_mode_t;

/**
 * @brief  select when to recover PWM output after fault
 *
 */
typedef enum pwm_fault_recovery_trigger {
    pwm_fault_recovery_immediately = 0, /**< immediately*/
    pwm_fault_recovery_on_reload = 1,   /**<  after pwm timer counter reload time*/
    pwm_fault_recovery_on_hw_event = 2, /**< after hardware event assert*/
    pwm_fault_recovery_on_fault_clear = 3,  /**<  after software write faultclr bit in GCR register*/
} pwm_fault_recovery_trigger_t;

/**
 * @brief fault input signal
 *
 */
typedef enum pwm_fault_source {
    pwm_fault_source_internal_0 = PWM_GCR_FAULTI0EN_MASK, /**< FAULTI0 */
    pwm_fault_source_internal_1 = PWM_GCR_FAULTI1EN_MASK, /**< FAULTI1 */
    pwm_fault_source_internal_2 = PWM_GCR_FAULTI2EN_MASK, /**< FAULTI2 */
    pwm_fault_source_internal_3 = PWM_GCR_FAULTI3EN_MASK, /**< FAULTI3 */
    pwm_fault_source_external_0 = PWM_GCR_FAULTE0EN_MASK, /**< EXFAULTI0 */
    pwm_fault_source_external_1 = PWM_GCR_FAULTE1EN_MASK, /**< EXFAULTI1 */
    pwm_fault_source_debug = PWM_GCR_DEBUGFAULT_MASK,   /**< Debug fault */
} pwm_fault_source_t;

/**
 * @brief Select sources for force output
 *
 */
typedef enum pwm_force_source {
    pwm_force_source_force_input = 0, /**< force output is enabled when FRCI assert */
    pwm_force_source_software = 1,  /**<  force output is enabled by software write swfrc to 1 */
} pwm_force_source_t;
/**
 * @brief select when the FRCMD shadow register will be loaded to its work register
 *
 */
typedef enum pwm_force_cmd_timing {
    pwm_force_immediately = 0,  /**< after software set shlk bit of shlk register */
    pwm_force_at_reload = 1,    /**< immediately after the register being modified */
    pwm_force_at_synci = 2,     /**< after hardware event assert */
    pwm_force_none = 3,         /**< after SHSYNCI assert */
} pwm_force_cmd_timing_t;

/**
 * @brief pwm output type
 *
 */
typedef enum pwm_output_type {
    pwm_output_0 = 0, /**< output 0 */
    pwm_output_1 = 1, /**< output 1 */
    pwm_output_high_z = 2, /**< output */
    pwm_output_no_force = 3,
} pwm_output_type_t;

/**
 * @brief pwm compare config
 *
 */
typedef struct pwm_cmp_config {
    uint32_t cmp;         /**< compare value */
    bool enable_ex_cmp;   /**< enable extended compare value */
#if defined(PWM_SOC_HRPWM_SUPPORT) && PWM_SOC_HRPWM_SUPPORT
    bool enable_hrcmp;     /**< enable high precision pwm */
#endif
    uint8_t mode;         /**< compare work mode: pwm_cmp_mode_output_compare or pwm_cmp_mode_input_capture */
    uint8_t update_trigger;  /**< compare configuration update trigger */
    uint8_t ex_cmp;       /**< extended compare value */
    uint8_t half_clock_cmp; /**< half clock compare value*/
    uint8_t jitter_cmp;     /**< jitter compare value */
#if defined(PWM_SOC_HRPWM_SUPPORT) && PWM_SOC_HRPWM_SUPPORT
    uint8_t hrcmp;         /**< high precision pwm */
#endif
} pwm_cmp_config_t;

/**
 * @brief pwm output channel config
 *
 */
typedef struct pwm_output_channel {
    uint8_t cmp_start_index; /**< output channel compare start index */
    uint8_t cmp_end_index;   /**< output channel compare end index */
    bool invert_output;      /**< invert output */
} pwm_output_channel_t;
/**
 * @brief pwm fault source config
 *
 */
typedef struct pwm_fault_source_config {
    uint32_t source_mask;                   /**< fault source mask*/
    bool fault_recover_at_rising_edge;      /**< recover fault at rising edge */
    bool fault_external_0_active_low;       /**< active external fault0 by low */
    bool fault_external_1_active_low;       /**< active external fault1 by low */
    uint8_t fault_output_recovery_trigger;  /**< fault output recoverty trigger */
} pwm_fault_source_config_t;

/**
 * @brief pwm config data
 *
 */
typedef struct pwm_config {
#if defined(PWM_SOC_HRPWM_SUPPORT) && PWM_SOC_HRPWM_SUPPORT
    bool hrpwm_update_mode;             /**< mode one or zero, HR CMP update timing */
#endif
    bool enable_output;                 /**< enable pwm output */
    bool invert_output;                 /**< invert pwm output level */
    uint8_t update_trigger;             /**< pwm config update trigger */
    uint8_t fault_mode;                 /**< fault mode */
    uint8_t fault_recovery_trigger;     /**< fault recoverty trigger */
    uint8_t force_source;               /**< fault source */
    uint32_t dead_zone_in_half_cycle;   /**< dead zone in half cycle*/
} pwm_config_t;

/**
 * @brief pair pwm config
 *
 */
typedef struct pwm_pair_config {
    pwm_config_t pwm[2];    /**< pwm config data */
} pwm_pair_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief pwm deinitialize function
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 *
 */
static inline void pwm_deinit(PWM_Type *pwm_x)
{
    pwm_x->IRQEN = 0;
    pwm_x->DMAEN = 0;
    pwm_x->SR |= pwm_x->SR;
    pwm_x->STA = 0;
    pwm_x->RLD = PWM_RLD_RLD_MASK;
    for (uint8_t i = 0; i < PWM_SOC_CMP_MAX_COUNT; i++) {
        pwm_x->CMP[i] = PWM_CMP_CMP_MASK;
        pwm_x->CMPCFG[i] = 0;
        pwm_x->CHCFG[i] = PWM_CHCFG_CMPSELEND_SET(PWM_SOC_CMP_MAX_COUNT - 1) | PWM_CHCFG_CMPSELBEG_SET(PWM_SOC_CMP_MAX_COUNT - 1);
    }
    pwm_x->FRCMD = 0;
    pwm_x->GCR = 0;
    pwm_x->SHCR = 0;
#if defined(PWM_SOC_HRPWM_SUPPORT) && PWM_SOC_HRPWM_SUPPORT
    pwm_x->HRPWM_CFG = 0;
#endif
    for (uint8_t i = 0; i < PWM_SOC_OUTPUT_TO_PWM_MAX_COUNT; i++) {
        pwm_x->PWMCFG[i] = 0;
    }
}

/**
 * @brief issue all shawdow register
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwm_issue_shadow_register_lock_event(PWM_Type *pwm_x)
{
    if (pwm_x->SHCR & PWM_SHCR_SHLKEN_MASK) {
        /*
         * if lock shadow register has been enabled in SHCR, it has to set
         * the lock bit twice to issue shadow register lock event.
         */
        pwm_x->SHLK = PWM_SHLK_SHLK_MASK;
    }
    pwm_x->SHLK = PWM_SHLK_SHLK_MASK;
}

/**
 * @brief lock all shawdow register
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwm_shadow_register_lock(PWM_Type *pwm_x)
{
    pwm_x->SHCR |= PWM_SHCR_SHLKEN_MASK;
    pwm_x->SHLK = PWM_SHLK_SHLK_MASK;
}

/**
 * @brief unlock all shadow register
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwm_shadow_register_unlock(PWM_Type *pwm_x)
{
    pwm_x->UNLK = PWM_UNLOCK_KEY;
}

/**
 * @brief set counter start value and extended start value
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] ex_start pwm timer counter extended start value
 * @param[in] start pwm timer counter start value
 */
static inline void pwm_set_start_count(PWM_Type *pwm_x,
                                        uint8_t ex_start,
                                        uint32_t start)
{
    pwm_x->STA = PWM_STA_XSTA_SET(ex_start)
        | PWM_STA_STA_SET(start);
}

#if defined(PWM_SOC_HRPWM_SUPPORT) && PWM_SOC_HRPWM_SUPPORT

/**
 * @brief set hrpwm counter start value
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param start pwm timer counter start value
 */
static inline void pwm_set_hrpwm_start_count(PWM_Type *pwm_x,
                                        uint32_t start)
{
    pwm_x->STA_HRPWM = PWM_STA_HRPWM_STA_SET(start);
}

#endif

/**
 * @brief set the reload value
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] ex_reload pwm timer counter extended reload value
 * @param[in] reload pwm timer counter reload value
 */
static inline void pwm_set_reload(PWM_Type *pwm_x,
                                   uint8_t ex_reload,
                                   uint32_t reload)
{
    pwm_shadow_register_unlock(pwm_x);
    pwm_x->RLD = PWM_RLD_XRLD_SET(ex_reload)
        | PWM_RLD_RLD_SET(reload);
}

#if defined(PWM_SOC_HRPWM_SUPPORT) && PWM_SOC_HRPWM_SUPPORT

/**
 * @brief set the hr pwm reload value
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param hr_reload pwm timer counter hrpwm reload value
 * @param reload pwm timer counter reload value
 */
static inline void pwm_set_hrpwm_reload(PWM_Type *pwm_x,
                                   uint16_t hrpwm_reload,
                                   uint32_t reload)
{
    pwm_shadow_register_unlock(pwm_x);
    pwm_x->RLD_HRPWM = PWM_RLD_HRPWM_RLD_HR_SET(hrpwm_reload)
        | PWM_RLD_HRPWM_RLD_SET(reload);
}

#endif

/**
 * @brief clear pwm status register
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] mask :
 *  @arg        PWM_IRQ_FAULT: fault condition flag
 *  @arg        PWM_IRQ_EX_RELOAD : extended reload flag, this flag set when xcnt count to xrld value or when SYNCI assert
 *  @arg        PWM_IRQ_HALF_RELOAD: half reload flag, this flag set when cnt count to rld/2
 *  @arg        PWM_IRQ_RELOAD: reload flag, this flag set when cnt count to rld value or when SYNCI assert
 *  @arg        PWM_IRQ_CMP(x)(x=0...n): comparator output compare or input capture flag
 */
static inline void pwm_clear_status(PWM_Type *pwm_x, uint32_t mask)
{
    pwm_x->SR |= mask;
}

#if defined(PWM_SOC_TIMER_RESET_SUPPORT) && PWM_SOC_TIMER_RESET_SUPPORT

/**
 * @brief Reset timer and extension timer
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwm_timer_reset(PWM_Type *pwm_x)
{
     pwm_x->GCR = ((pwm_x->GCR & ~(PWM_GCR_TIMERRESET_MASK)) | PWM_GCR_TIMERRESET_SET(1));
}

#endif

/**
 * @brief get pwm status register
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @retval uint32_t SR register value
 */
static inline uint32_t pwm_get_status(PWM_Type *pwm_x)
{
    return pwm_x->SR;
}

/**
 * @brief disable pwm irq
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] mask :
 *  @arg        PWM_IRQ_FAULT: fault condition interrupt enable
 *  @arg        PWM_IRQ_EX_RELOAD: extended reload flag interrupt enable
 *  @arg        PWM_IRQ_HALF_RELOAD: half reload flag interrupt enable
 *  @arg        PWM_IRQ_RELOAD: reload flag interrupt enable
 *  @arg        PWM_IRQ_CMP(x)(x=0...n): comparator output compare or input capture flag interrupt enable
 */
static inline void pwm_disable_irq(PWM_Type *pwm_x, uint32_t mask)
{
    pwm_x->IRQEN &= ~mask;
}

/**
 * @brief enable pwm irq
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] mask :
 *  @arg        PWM_IRQ_FAULT: fault condition interrupt enable
 *  @arg        PWM_IRQ_EX_RELOAD: extended reload flag interrupt enable
 *  @arg        PWM_IRQ_HALF_RELOAD: half reload flag interrupt enable
 *  @arg        PWM_IRQ_RELOAD: reload flag interrupt enable
 *  @arg        PWM_IRQ_CMP(x)(x=0...n): comparator output compare or input capture flag interrupt enable
 */
static inline void pwm_enable_irq(PWM_Type *pwm_x, uint32_t mask)
{
    pwm_x->IRQEN |= mask;
}

/**
 * @brief disable pwm dma request
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] mask :
 *  @arg        PWM_IRQ_FAULT: fault condition DMA request enable
 *  @arg        PWM_IRQ_EX_RELOAD: extended reload flag DMA request enable
 *  @arg        PWM_IRQ_HALF_RELOAD: half reload flag DMA request enable
 *  @arg        PWM_IRQ_RELOAD: reload flag DMA request enable
 *  @arg        PWM_IRQ_CMP(x)(x=0...n): comparator output compare or input capture flag DMA request enable
 *
 */
static inline void pwm_disable_dma_request(PWM_Type *pwm_x, uint32_t mask)
{
    pwm_x->DMAEN &= ~mask;
}

/**
 * @brief enable pwm dma request
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] mask :
 *  @arg        PWM_IRQ_FAULT: fault condition DMA request enable
 *  @arg        PWM_IRQ_EX_RELOAD: extended reload flag DMA request enable
 *  @arg        PWM_IRQ_HALF_RELOAD: half reload flag DMA request enable
 *  @arg        PWM_IRQ_RELOAD: reload flag DMA request enable
 *  @arg        PWM_IRQ_CMP(x)(x=0...n): comparator output compare or input capture flag DMA request enable
 *
 */
static inline void pwm_enable_dma_request(PWM_Type *pwm_x, uint32_t mask)
{
    pwm_x->DMAEN |= mask;
}

/**
 * @brief set target cmp as hardware event to trigger force cmd output
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] target_cmp_index cmp index  select one of the cmp as hardware event time to load FRCMD shadow registers [0-23]
 */
static inline void pwm_set_force_cmd_shadow_register_hwevent(PWM_Type *pwm_x,
                                                    uint8_t target_cmp_index)
{
    pwm_x->SHCR = ((pwm_x->SHCR & ~(PWM_SHCR_FRCSHDWSEL_MASK))
                    | PWM_SHCR_FRCSHDWSEL_SET(target_cmp_index));
}
/**
 * @note if trigger is not set to hardware event, target_cmp_index can be
 * passed with any value
 *
 */

/**
 * @brief set shadow register control register
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] trigger  select when the counter related shadow registers @ref pwm_shadow_register_update_trigger_t
 * @param[in] target_cmp_index  select one of the comparators as hardware event (0..(PWM_SOC_CMP_MAX_COUNT-1))
 */
static inline void pwm_set_load_counter_shadow_register_trigger(PWM_Type *pwm_x,
                                pwm_shadow_register_update_trigger_t trigger,
                                uint8_t target_cmp_index)
{
    if (trigger == pwm_shadow_register_update_on_hw_event) {
        pwm_x->SHCR = ((pwm_x->SHCR & ~(PWM_SHCR_CNTSHDWSEL_MASK
                        | PWM_SHCR_CNTSHDWUPT_MASK))
                | PWM_SHCR_CNTSHDWSEL_SET(target_cmp_index)
                | PWM_SHCR_CNTSHDWUPT_SET(trigger));
    } else {
        pwm_x->SHCR = ((pwm_x->SHCR & ~(PWM_SHCR_CNTSHDWUPT_MASK))
                | PWM_SHCR_CNTSHDWUPT_SET(trigger));
    }
}

/**
 * @brief Configure input capture cmp to trigger shadow register updates
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index cmp index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 * @param[in] is_falling_edge  which edge is used as shadow register hardware load event
 *  @arg 1- falling edge
 *  @arg 0- rising edge
 */
static inline void pwm_load_cmp_shadow_on_capture(PWM_Type *pwm_x,
                                                   uint8_t index,
                                                   bool is_falling_edge)
{
    pwm_x->CMPCFG[index] |= PWM_CMPCFG_CMPMODE_MASK;
    pwm_x->GCR = ((pwm_x->GCR & ~(PWM_GCR_CMPSHDWSEL_MASK | PWM_GCR_HWSHDWEDG_MASK))
            | PWM_GCR_CMPSHDWSEL_SET(index)
            | PWM_GCR_HWSHDWEDG_SET(is_falling_edge));
}

#if defined(PWM_SOC_SHADOW_TRIG_SUPPORT) && PWM_SOC_SHADOW_TRIG_SUPPORT

/**
 * @brief RLD, STA shadow registers take effect at the reload point
 *
 * @param pwm_x pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param is_enable true or false
 */
static inline void pwm_set_cnt_shadow_trig_reload(PWM_Type *pwm_x, bool is_enable)
{
	pwm_x->SHCR = ((pwm_x->SHCR & ~PWM_SHCR_CNT_UPDATE_RELOAD_MASK)
            | PWM_SHCR_CNT_UPDATE_RELOAD_SET(is_enable));
}

/**
 * @brief Set the timer shadow register to update the trigger edge
 *
 * @param[in] pwm_x pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] is_falling_edge which edge is used as shadow register hardware load event
 *  @arg 1- falling edge
 *  @arg 0- rising edge
 */
static inline void pwm_set_cnt_shadow_trig_edge(PWM_Type *pwm_x,
                                                   bool is_falling_edge)
{
    pwm_x->SHCR = ((pwm_x->SHCR & ~PWM_SHCR_CNT_UPDATE_EDGE_MASK)
            | PWM_SHCR_CNT_UPDATE_EDGE_SET(is_falling_edge));
}

/**
 * @brief Set the force output shadow register to update the trigger edge
 *
 * @param[in] pwm_x pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] is_falling_edge which edge is used as shadow register hardware load event
 *  @arg 1- falling edge
 *  @arg 0- rising edge
 */
static inline void pwm_set_force_shadow_trig_edge(PWM_Type *pwm_x,
                                                   bool is_falling_edge)
{
    pwm_x->SHCR = ((pwm_x->SHCR & ~PWM_SHCR_FORCE_UPDATE_EDGE_MASK)
            | PWM_SHCR_FORCE_UPDATE_EDGE_SET(is_falling_edge));
}

#endif
/**
 * @brief disable pwn cmp half clock
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index cmp index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 */
static inline void pwm_cmp_disable_half_clock(PWM_Type *pwm_x, uint8_t index)
{
    pwm_x->CMP[index] &= ~PWM_CMP_CMPHLF_MASK;
}

/**
 * @brief enable pwm cmp half clock
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index cmp index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 */
static inline void pwm_cmp_enable_half_clock(PWM_Type *pwm_x, uint8_t index)
{
    pwm_x->CMP[index] |= PWM_CMP_CMPHLF_MASK;
}

/**
 * @brief update pwm cmp jitter counter compare value
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index cmp index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 * @param[in] jitter jitter value
 */
static inline void pwm_cmp_update_jitter_value(PWM_Type *pwm_x, uint8_t index, uint8_t jitter)
{
    pwm_x->CMP[index] = (pwm_x->CMP[index] & ~PWM_CMP_CMPJIT_MASK) | PWM_CMP_CMPJIT_SET(jitter);
}

/**
 * @brief update pwm cmp value
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index cmp index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 * @param[in] cmp clock counter compare value
 * @param[in] ex_cmp extended counter compare value
 */
static inline void pwm_cmp_update_cmp_value(PWM_Type *pwm_x, uint8_t index,
                                            uint32_t cmp, uint16_t ex_cmp)
{
    pwm_x->CMP[index] = (pwm_x->CMP[index] & ~(PWM_CMP_CMP_MASK | PWM_CMP_XCMP_MASK))
        | PWM_CMP_CMP_SET(cmp) | PWM_CMP_XCMP_SET(ex_cmp);
}

#if defined(PWM_SOC_HRPWM_SUPPORT) && PWM_SOC_HRPWM_SUPPORT
/**
 * @brief update high-precision cmp value
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index cmp index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 * @param[in] cmp clock counter compare value
 * @param[in] hrcmp high-precision pwm
 */
static inline void pwm_cmp_update_hrcmp_value(PWM_Type *pwm_x, uint8_t index,
                                            uint32_t cmp, uint16_t hrcmp)
{
    pwm_x->CMP_HRPWM[index] = (pwm_x->CMP_HRPWM[index] & ~(PWM_CMP_HRPWM_CMP_MASK | PWM_CMP_HRPWM_CMP_HR_MASK))
        | PWM_CMP_HRPWM_CMP_SET(cmp) | PWM_CMP_HRPWM_CMP_HR_SET(hrcmp);
}
#endif

/**
 * @brief Forced update of pwm cmp register value, cmp content guaranteed accurate by user
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index cmp index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 * @param[in] cmp cmp register data
 */
static inline void pwm_cmp_force_value(PWM_Type *pwm_x, uint8_t index, uint32_t cmp)
{
    pwm_x->CMP[index] = cmp;
}

/**
 * @brief config pwm cmp
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index cmp index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 * @param[in] config @ref pwm_cmp_config_t
 */
static inline void pwm_config_cmp(PWM_Type *pwm_x, uint8_t index, pwm_cmp_config_t *config)
{
    pwm_shadow_register_unlock(pwm_x);
    if (config->mode == pwm_cmp_mode_output_compare) {
#if defined(PWM_SOC_HRPWM_SUPPORT) && PWM_SOC_HRPWM_SUPPORT
        if (config->enable_hrcmp) {
            pwm_x->CMPCFG[index] = PWM_CMPCFG_CMPSHDWUPT_SET(config->update_trigger);
            pwm_x->CMP[index] = PWM_CMP_HRPWM_CMP_SET(config->cmp)
                        | PWM_CMP_HRPWM_CMP_HR_SET(config->hrcmp);
        } else {
#endif
            pwm_x->CMPCFG[index] = (config->enable_ex_cmp ? PWM_CMPCFG_XCNTCMPEN_MASK : 0)
                        | PWM_CMPCFG_CMPSHDWUPT_SET(config->update_trigger);
            pwm_x->CMP[index] = PWM_CMP_CMP_SET(config->cmp)
                        | PWM_CMP_XCMP_SET(config->ex_cmp)
                        | PWM_CMP_CMPHLF_SET(config->half_clock_cmp)
                        | PWM_CMP_CMPJIT_SET(config->jitter_cmp);
#if defined(PWM_SOC_HRPWM_SUPPORT) && PWM_SOC_HRPWM_SUPPORT
        }
#endif
    } else {
        pwm_x->CMPCFG[index] |= PWM_CMPCFG_CMPMODE_MASK;
    }
}

/**
 * @brief config pwm output channel
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index channel index (0..(PWM_SOC_PWM_MAX_COUNT-1))
 * @param[in] config @ref pwm_output_channel_t
 */
static inline void pwm_config_output_channel(PWM_Type *pwm_x, uint8_t index, pwm_output_channel_t *config)
{
    pwm_x->CHCFG[index] = PWM_CHCFG_CMPSELBEG_SET(config->cmp_start_index)
                            | PWM_CHCFG_CMPSELEND_SET(config->cmp_end_index)
                            | PWM_CHCFG_OUTPOL_SET(config->invert_output);
}

/**
 * @brief config pwm fault source
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] config @ref pwm_fault_source_config_t
 */
static inline void pwm_config_fault_source(PWM_Type *pwm_x, pwm_fault_source_config_t *config)
{
    pwm_x->GCR = (pwm_x->GCR & ~(PWM_GCR_FAULTI0EN_MASK | PWM_GCR_FAULTI1EN_MASK
                | PWM_GCR_FAULTI2EN_MASK | PWM_GCR_FAULTI3EN_MASK
                | PWM_GCR_FAULTE0EN_MASK | PWM_GCR_FAULTE1EN_MASK
                | PWM_GCR_FAULTRECEDG_MASK | PWM_GCR_FAULTEXPOL_MASK
                | PWM_GCR_FAULTRECHWSEL_MASK))
        | config->source_mask
        | PWM_GCR_FAULTEXPOL_SET((config->fault_external_0_active_low ? 0x1 : 0) | (config->fault_external_1_active_low ? 0x2 : 0))
        | PWM_GCR_FAULTRECEDG_SET(config->fault_recover_at_rising_edge)
        | PWM_GCR_FAULTRECHWSEL_SET(config->fault_output_recovery_trigger);
}

/**
 * @brief clear pwm fault status
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwm_clear_fault(PWM_Type *pwm_x)
{
    pwm_x->GCR |= PWM_GCR_FAULTCLR_MASK;
    pwm_x->GCR &= ~PWM_GCR_FAULTCLR_MASK;
}

/**
 * @brief stop the pwm timer counter
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwm_stop_counter(PWM_Type *pwm_x)
{
    pwm_x->GCR &= ~PWM_GCR_CEN_MASK;
}

/**
 * @brief start pwm timer counter
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwm_start_counter(PWM_Type *pwm_x)
{
    pwm_x->GCR |= PWM_GCR_CEN_MASK;
}

/**
 * @brief enable software force
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwm_enable_sw_force(PWM_Type *pwm_x)
{
    pwm_x->GCR |= PWM_GCR_SWFRC_MASK;
}

/**
 * @brief disable software force , force will take effect
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwm_disable_sw_force(PWM_Type *pwm_x)
{
    pwm_x->GCR &= ~PWM_GCR_SWFRC_MASK;
}

/**
 * @brief enable pwm reload value by synci
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwm_enable_reload_at_synci(PWM_Type *pwm_x)
{
    pwm_x->GCR |= PWM_GCR_XRLDSYNCEN_MASK | PWM_GCR_RLDSYNCEN_MASK;
}

/**
 * @brief disable pwm output
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index pwm index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 */
static inline void pwm_disable_output(PWM_Type *pwm_x, uint8_t index)
{
    pwm_x->PWMCFG[index] &= ~PWM_PWMCFG_OEN_MASK;
}

/**
 * @brief enable pwm output
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index pwm index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 */
static inline void pwm_enable_output(PWM_Type *pwm_x, uint8_t index)
{
    pwm_x->PWMCFG[index] |= PWM_PWMCFG_OEN_MASK;
}

/**
 * @brief config pwm force output level per output channel
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] output_mask PWM output channel force level, set it using the macro
 *  @arg PWM_FORCE_OUTPUT(pwm_index, force_output)
 */
static inline void pwm_set_force_output(PWM_Type *pwm_x, uint32_t output_mask)
{
    pwm_x->FRCMD = PWM_FRCMD_FRCMD_SET(output_mask);
}

/**
 * @brief config pwm force polarity
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] polarity polarity of input pwm_force
 *  @arg 1- active low
 *  @arg 0- active high
 */
static inline void pwm_config_force_polarity(PWM_Type *pwm_x, bool polarity)
{
    pwm_x->GCR = (pwm_x->GCR & ~(PWM_GCR_FRCPOL_MASK)) | PWM_GCR_FRCPOL_SET(polarity);
}

/**
 * @brief config the force effective time
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] timing @ref pwm_force_cmd_timing_t
 */
static inline void pwm_config_force_cmd_timing(PWM_Type *pwm_x, pwm_force_cmd_timing_t timing)
{
    pwm_x->GCR = (pwm_x->GCR & ~(PWM_GCR_FRCTIME_MASK)) | PWM_GCR_FRCTIME_SET(timing);
}

/**
 * @brief enable pwm sw force output
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index pwm cmp index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 */
static inline void pwm_enable_pwm_sw_force_output(PWM_Type *pwm_x, uint8_t index)
{
    pwm_x->PWMCFG[index] |= PWM_PWMCFG_OEN_MASK | PWM_PWMCFG_FRCSRCSEL_MASK
        | PWM_PWMCFG_FRCSHDWUPT_SET(pwm_shadow_register_update_on_modify);
}

/**
 * @brief disable pwm sw force output
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index pwm cmp index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 */
static inline void pwm_disable_pwm_sw_force_output(PWM_Type *pwm_x, uint8_t index)
{
    pwm_x->PWMCFG[index] &= ~PWM_PWMCFG_FRCSRCSEL_MASK;
}

/**
 * @brief config PWM channel configure registe
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index pwm channel index (0..(PWM_SOC_PWM_MAX_COUNT-1))
 * @param[in] config @ref pwm_config_t
 * @param[in] enable_pair_mode enable pair mode
 *  @arg 1- PWM output is in pair mode
 *  @arg 0- PWM output is in indepandent mode
 */
static inline void pwm_config_pwm(PWM_Type *pwm_x, uint8_t index,
                                  pwm_config_t *config, bool enable_pair_mode)
{
    pwm_x->PWMCFG[index] = PWM_PWMCFG_OEN_SET(config->enable_output)
        | PWM_PWMCFG_FRCSHDWUPT_SET(config->update_trigger)
        | PWM_PWMCFG_FAULTMODE_SET(config->fault_mode)
        | PWM_PWMCFG_FAULTRECTIME_SET(config->fault_recovery_trigger)
        | PWM_PWMCFG_FRCSRCSEL_SET(config->force_source)
        | PWM_PWMCFG_PAIR_SET(enable_pair_mode)
#if defined(PWM_SOC_HRPWM_SUPPORT) && PWM_SOC_HRPWM_SUPPORT
        | PWM_PWMCFG_HR_UPDATE_MODE_SET(config->hrpwm_update_mode)
#endif
        | PWM_PWMCFG_DEADAREA_SET(config->dead_zone_in_half_cycle);
}

/**
 * @brief getting the counter reload value for a pwm timer
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @retval pwm reload value
 */
static inline uint32_t pwm_get_reload_val(PWM_Type *pwm_x)
{
    return PWM_RLD_RLD_GET(pwm_x->RLD);
}

/**
 * @brief getting the extended counter reload value for a pwm timer
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @retval pwm extended reload value
 */
static inline uint32_t pwm_get_ex_reload_val(PWM_Type *pwm_x)
{
    return PWM_RLD_XRLD_GET(pwm_x->RLD);
}

/**
 * @brief getting the value of the pwm counter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @retval pwm counter value
 */
static inline uint32_t pwm_get_counter_val(PWM_Type *pwm_x)
{
    return PWM_CNT_CNT_GET(pwm_x->CNT);
}

/**
 * @brief getting the value of the pwm extended counter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @retval pwm counter value
 */
static inline uint32_t pwm_get_ex_counter_val(PWM_Type *pwm_x)
{
    return PWM_CNT_XCNT_GET(pwm_x->CNT);
}

/**
 * @brief pwm load cmp shadow on match
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] index cmp index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 * @param[in] config @ref pwm_cmp_config_t
 * @retval status_invalid_argument or status_success
 */
hpm_stat_t pwm_load_cmp_shadow_on_match(PWM_Type *pwm_x,
                                         uint8_t index,
                                         pwm_cmp_config_t *config);

/**
 * @brief pwm get captured count
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[out] buf count value
 * @param[in] counter @ref pwm_counter_type_t
 * @param[in] start_index start capture index (0..(PWM_SOC_CMP_MAX_COUNT-1))
 * @param[in] num capture num (1..PWM_SOC_CMP_MAX_COUNT)
 */
void pwm_get_captured_count(PWM_Type *pwm_x, uint32_t *buf, pwm_counter_type_t counter, uint8_t start_index, uint8_t num);

/**
 * @brief get default cmp config
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[out] config @ref pwm_cmp_config_t
 */
void pwm_get_default_cmp_config(PWM_Type *pwm_x, pwm_cmp_config_t *config);

/**
 * @brief get default output channel config
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[out] config @ref pwm_output_channel_t
 */
void pwm_get_default_output_channel_config(PWM_Type *pwm_x, pwm_output_channel_t *config);

/**
 * @brief get default pwm config
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[out] config @ref pwm_config_t
 */
void pwm_get_default_pwm_config(PWM_Type *pwm_x, pwm_config_t *config);

/**
 * @brief get default pwm pair config
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[out] config @ref pwm_pair_config_t
 */
void pwm_get_default_pwm_pair_config(PWM_Type *pwm_x, pwm_pair_config_t *config);

/**
 * @brief setup waveform
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] pwm_index pwm channel index (0..(PWM_SOC_PWM_MAX_COUNT-1))
 * @param[in] pwm_config @ref pwm_config_t
 * @param[in] cmp_start_index pwm cmp index (0..(PWM_SOC_PWM_MAX_COUNT-1))
 * @param[in] cmp @ref pwm_cmp_config_t
 * @param[in] cmp_num cmp num (1..PWM_SOC_CMP_MAX_COUNT), cmp[cmp_num-1] must not overflow
 * @retval hpm_stat_t
 */
hpm_stat_t pwm_setup_waveform(PWM_Type *pwm_x,
                        uint8_t pwm_index, pwm_config_t *pwm_config,
                        uint8_t cmp_start_index, pwm_cmp_config_t *cmp, uint8_t cmp_num);
/**
 * @brief setup pwm waveform in pair
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] pwm_index pwm channel index (0..(PWM_SOC_PWM_MAX_COUNT-1))
 * @param[in] pwm_pair_config @ref pwm_pair_config_t
 * @param[in] cmp_start_index pwm cmp index (0..(PWM_SOC_PWM_MAX_COUNT-1))
 * @param[in] cmp @ref pwm_cmp_config_t
 * @param[in] cmp_num cmp num (1..PWM_SOC_CMP_MAX_COUNT), cmp[cmp_num-1] must not overflow
 * @retval hpm_stat_t @ref status_invalid_argument or @ref status_success
 */
hpm_stat_t pwm_setup_waveform_in_pair(PWM_Type *pwm_x,
                        uint8_t pwm_index, pwm_pair_config_t *pwm_pair_config,
                        uint8_t cmp_start_index, pwm_cmp_config_t *cmp, uint8_t cmp_num);

/**
 * @brief update raw compare value for edge aligned waveform
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] cmp_index index of cmp to be adjusted (0..(PWM_SOC_PWM_MAX_COUNT-1))
 * @param[in] target_cmp target compare value
 * @retval hpm_stat_t @ref status_invalid_argument or @ref status_success
 */
hpm_stat_t pwm_update_raw_cmp_edge_aligned(PWM_Type *pwm_x, uint8_t cmp_index,
                                uint32_t target_cmp);

/**
 * @brief update raw compare value for central aligned waveform
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] cmp1_index index of cmp1 to be adjusted (cmp1_index must be even number)
 * @param[in] cmp2_index index of cmp2 to be adjusted (cmp2_index must be odd number)
 * @param[in] target_cmp1 target compare value for cmp1
 * @param[in] target_cmp2 target compare value for cmp2
 * @retval hpm_stat_t @ref status_invalid_argument or @ref status_success cmp1_index
 */
hpm_stat_t pwm_update_raw_cmp_central_aligned(PWM_Type *pwm_x, uint8_t cmp1_index,
                                       uint8_t cmp2_index, uint32_t target_cmp1, uint32_t target_cmp2);
#if defined(PWM_SOC_HRPWM_SUPPORT) && PWM_SOC_HRPWM_SUPPORT

/**
 * @brief recovery hrpwm output
 *
 * @param pwm_x @ref PWM_Type PWM base address
 */
static inline void pwm_recovery_hrpwm_output(PWM_Type *pwm_x)
{
    pwm_x->HRPWM_CFG |= PWM_HRPWM_CFG_CAL_SW_EN_MASK;
    pwm_x->ANA_CFG0 |= PWM_ANA_CFG0_CAL_SW_TRIG_H_MASK;
    pwm_x->ANA_CFG0 &= ~PWM_ANA_CFG0_CAL_SW_TRIG_H_MASK;
    pwm_x->ANA_CFG0 |= PWM_ANA_CFG0_CAL_SW_TRIG_H_MASK;
    pwm_x->ANA_CFG0 &= ~PWM_ANA_CFG0_CAL_SW_TRIG_H_MASK;
    pwm_x->HRPWM_CFG &= ~PWM_HRPWM_CFG_CAL_SW_EN_MASK;
}

/**
 * @brief Enable high-precision pwm
 *
 * @param[in] pwm_x @ref PWM_Type PWM base address
 */
static inline void pwm_enable_hrpwm(PWM_Type *pwm_x)
{
    pwm_x->GCR = (pwm_x->GCR & ~(PWM_GCR_HR_PWM_EN_MASK)) | PWM_GCR_HR_PWM_EN_SET(1);
}

/**
 * @brief Disable high-precision pwm
 *
 * @param[in] pwm_x @ref PWM_Type PWM base address
 */
static inline void pwm_disable_hrpwm(PWM_Type *pwm_x)
{
    pwm_x->GCR = pwm_x->GCR & ~(PWM_GCR_HR_PWM_EN_MASK);
}

/**
 * @brief Calibrate all channels of hrpwm
 *
 * @param[in] pwm_x @ref PWM_Type PWM base address
 */
static inline void pwm_cal_hrpwm_start(PWM_Type *pwm_x)
{
    pwm_x->HRPWM_CFG |= PWM_HRPWM_CFG_CAL_START_MASK;
}

/**
 * @brief Calibrate specified hrpwm channels
 *
 * @param[in] pwm_x @ref PWM_Type PWM base address
 * @param[in] chn Channel number
 */
static inline void pwm_cal_hrpwm_chn_start(PWM_Type *pwm_x, uint8_t chn)
{
    pwm_x->HRPWM_CFG |= PWM_HRPWM_CFG_CAL_START_SET(chn);
}

/**
 * @brief Wait for the completion of calibration of the specified channel of high-precision PWM, blocking
 *
 * @param[in] pwm_x @ref PWM_Type PWM base address
 * @param[in] chn Channel number
 */
static inline void pwm_cal_hrpwm_chn_wait(PWM_Type *pwm_x, uint8_t chn)
{
    while (PWM_ANASTS_CALON_GET(pwm_x->ANASTS[chn])) {
    };
}

/**
 * @brief get calibration status
 *
 * @param[in] pwm_x pwm_x @ref PWM_Type PWM base address
 * @param[in] chn Channel number
 * @return uint32_t  finished will be set zero.
 */
static inline uint32_t pwm_get_cal_hrpwm_status(PWM_Type *pwm_x, uint8_t chn)
{
    return PWM_ANASTS_CALON_GET(pwm_x->ANASTS[chn]);
}

/**
 * @brief getting the counter reload value for hrpwm counter
 *
 * @param pwm_x pwm_x @ref PWM_Type PWM base address
 * @return uint32_t hrpwm reload
 */
static inline uint32_t pwm_get_hrpwm_reload_val(PWM_Type *pwm_x)
{
    return PWM_RLD_HRPWM_RLD_GET(pwm_x->RLD_HRPWM);
}

/**
 * @brief getting the counter reload value for hrpwm hr counter
 *
 * @param pwm_x pwm_x @ref PWM_Type PWM base address
 * @return uint32_t hrpwm hr reload
 */
static inline uint32_t pwm_get_hrpwm_hr_reload_val(PWM_Type *pwm_x)
{
    return PWM_RLD_HRPWM_RLD_HR_GET(pwm_x->RLD_HRPWM);
}


/**
 * @brief update raw high-precision compare value for edge aligned waveform
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] cmp_index index of cmp to be adjusted (0..(PWM_SOC_PWM_MAX_COUNT-1))
 * @param[in] target_cmp target compare value
 * @param[in] target_hrcmp target high-precision compare value
 * @return hpm_stat_t
 */
hpm_stat_t pwm_update_raw_hrcmp_edge_aligned(PWM_Type *pwm_x, uint8_t cmp_index, uint32_t target_cmp,
            uint16_t target_hrcmp);

/**
 * @brief update raw high-precision compare value for central aligned waveform
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param[in] cmp1_index index of cmp1 to be adjusted (cmp1_index must be even number)
 * @param[in] cmp2_index index of cmp2 to be adjusted (cmp2_index must be odd number)
 * @param[in] target_cmp1 target compare value for cmp1
 * @param[in] target_cmp2 target compare value for cmp2
 * @param[in] target_hrcmp1 target high-precision compare value for cmp1
 * @param[in] target_hrcmp2 target high-precision compare value for cmp2
 * @return hpm_stat_t
 */
hpm_stat_t pwm_update_raw_hrcmp_central_aligned(PWM_Type *pwm_x, uint8_t cmp1_index,
                                       uint8_t cmp2_index, uint32_t target_cmp1, uint32_t target_cmp2,
                                        uint16_t target_hrcmp1, uint16_t target_hrcmp2);
#endif

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_PWM_DRV_H */
