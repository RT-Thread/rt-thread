/*
 * Copyright (c) 2023-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_QEIV2_DRV_H
#define HPM_QEIV2_DRV_H

#include "hpm_common.h"
#include "hpm_soc_ip_feature.h"
#include "hpm_qeiv2_regs.h"
/**
 * @brief QEIV2 driver APIs
 * @defgroup qeiv2_interface QEIV2 driver APIs
 * @ingroup io_interfaces
 * @{
 */
#define QEIV2_EVENT_WDOG_FLAG_MASK              (1U << 31U) /**< watchdog flag */
#define QEIV2_EVENT_HOME_FLAG_MASK              (1U << 30U) /**< home flag */
#define QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK  (1U << 29U) /**< postion compare match flag */
#define QEIV2_EVENT_Z_PHASE_FLAG_MASK           (1U << 28U) /**< z input flag */
#define QEIV2_EVENT_Z_MISS_FLAG_MASK            (1U << 27U) /**< z miss  flag */
#define QEIV2_EVENT_WIDTH_TIME_FLAG_MASK        (1U << 26U) /**< width time flag */
#define QEIV2_EVENT_POSITION2_COMPARE_FLAG_MASK (1U << 25U) /**< postion2 compare match flag */
#define QEIV2_EVENT_DIR_CHG_FLAG_MASK           (1U << 24U) /**< direction change flag */
#define QEIV2_EVENT_CYCLE0_FLAG_MASK            (1U << 23U) /**< cycle0 flag */
#define QEIV2_EVENT_CYCLE1_FLAG_MASK            (1U << 22U) /**< cycle1 flag */
#define QEIV2_EVENT_PULSE0_FLAG_MASK            (1U << 21U) /**< pulse0 flag */
#define QEIV2_EVENT_PULSE1_FLAG_MASK            (1U << 20U) /**< pulse1 flag */
#define QEIV2_EVENT_HOME2_FLAG_MASK             (1U << 19U) /**< home2 flag */
#define QEIV2_EVENT_FAULT_FLAG_MASK             (1U << 18U) /**< fault flag */

/**
 * @brief qeiv2 work mode
 *
 */
typedef enum qeiv2_work_mode {
    qeiv2_work_mode_abz    = 0, /**< Orthogonal decoder mode */
    qeiv2_work_mode_pd     = 1, /**< Directional (PD) mode */
    qeiv2_work_mode_ud     = 2, /**< Up and Down (UD) mode */
    qeiv2_work_mode_uvw    = 3, /**< UVW mode */
    qeiv2_work_mode_single = 4, /**< Single-phase mode */
    qeiv2_work_mode_sin    = 5, /**< Single sinewave mode */
    qeiv2_work_mode_sincos = 6, /**< Orthogonal sinewave mode */
} qeiv2_work_mode_t;

/**
 * @brief spd and tmr read selection
 *
 */
typedef enum qeiv2_spd_tmr_content {
    qeiv2_spd_tmr_as_spd_tm    = 0, /**< spd and timer register as spd and time */
    qeiv2_spd_tmr_as_pos_angle = 1, /**< spd and timer register as position and angle */
} qeiv2_spd_tmr_content_t;

/**
 * @brief compare match rotate direction
 *
 */
typedef enum qeiv2_rotate_dir {
    qeiv2_rotate_dir_forward = 0,
    qeiv2_rotate_dir_reverse = 1,
} qeiv2_rotate_dir_t;     /**< compare match rotate direction */

/**
 * @brief compare match position direction
 *
 */
typedef enum qeiv2_position_dir {
    qeiv2_pos_dir_decrease = 0,
    qeiv2_pos_dir_increase = 1,
} qeiv2_position_dir_t;     /**< compare match position direction */

/**
 * @brief counting mode of Z-phase counter
 *
 */
typedef enum qeiv2_z_count_work_mode {
    qeiv2_z_count_inc_on_z_input_assert  = 0, /**< zcnt will increment or decrement when Z input assert */
    qeiv2_z_count_inc_on_phase_count_max = 1, /**< zcnt will increment when phcnt upcount to phmax, decrement when phcnt downcount to 0 */
} qeiv2_z_count_work_mode_t;

/**
 * @brief counter type
 *
 */
typedef enum qeiv2_counter_type {
    qeiv2_counter_type_z     = 0, /**< Z counter */
    qeiv2_counter_type_phase = 1, /**< Phase counter */
    qeiv2_counter_type_speed = 2, /**< Speed counter */
    qeiv2_counter_type_timer = 3, /**< Timer counter */
} qeiv2_counter_type_t;

/**
 * @brief filter mode
 *
 */
typedef enum qeiv2_filter_mode {
    qeiv2_filter_mode_bypass = 0, /**< bypass */
    qeiv2_filter_mode_burr   = 4, /**< rapid change mode */
    qeiv2_filter_mode_delay,      /**< delay filter mode */
    qeiv2_filter_mode_peak,       /**< stable low mode */
    qeiv2_filter_mode_valley,     /**< stable high mode */
} qeiv2_filter_mode_t;

/**
 * @brief filter type
 *
 */
typedef enum qeiv2_filter_phase {
    qeiv2_filter_phase_a = 0, /**< filter phase a */
    qeiv2_filter_phase_b,     /**< filter phase b */
    qeiv2_filter_phase_z,     /**< filter phase z */
    qeiv2_filter_phase_h,     /**< filter phase h */
    qeiv2_filter_phase_h2,    /**< filter phase h2 */
    qeiv2_filter_phase_f,     /**< filter phase f */
} qeiv2_filter_phase_t;       /**< qeiv2_filter_phase_t */

/**
 * @brief uvw position option
 *
 */
typedef enum qeiv2_uvw_pos_opt {
    qeiv2_uvw_pos_opt_current = 0,   /**< output exact point position, MMC use this */
    qeiv2_uvw_pos_opt_next,          /**< output next area position, QEO use this */
} qeiv2_uvw_pos_opt_t;

typedef enum qeiv2_uvw_pos_sel {
    qeiv2_uvw_pos_sel_low = 0,
    qeiv2_uvw_pos_sel_high,
    qeiv2_uvw_pos_sel_edge
} qeiv2_uvw_pos_sel_t;       /**< qeiv2_uvw_pos_sel_t */

/**
 * @brief qeiv2 uvw position selection
 *
 */
#define QEIV2_UVW_POS_OPT_CUR_SEL_LOW                  0u
#define QEIV2_UVW_POS_OPT_CUR_SEL_HIGH                 1u
#define QEIV2_UVW_POS_OPT_CUR_SEL_EDGE                 2u
#define QEIV2_UVW_POS_OPT_NEX_SEL_LOW                  0u
#define QEIV2_UVW_POS_OPT_NEX_SEL_HIGH                 3u

typedef enum qeiv2_uvw_pos_idx {
    qeiv2_uvw_pos0 = 0,
    qeiv2_uvw_pos1,
    qeiv2_uvw_pos2,
    qeiv2_uvw_pos3,
    qeiv2_uvw_pos4,
    qeiv2_uvw_pos5,
} qeiv2_uvw_pos_idx_t;       /**< qeiv2_uvw_pos_idx_t */

/**
 * @brief phase counter compare match config structure
 *
 */
typedef struct {
    uint32_t phcnt_cmp_value;
    bool ignore_rotate_dir;
    qeiv2_rotate_dir_t rotate_dir;
    bool ignore_zcmp;
    uint32_t zcmp_value;
} qeiv2_phcnt_cmp_match_config_t;

/**
 * @brief position compare match config structure
 *
 */
typedef struct {
    uint32_t pos_cmp_value;
    bool ignore_pos_dir;
    qeiv2_position_dir_t pos_dir;
} qeiv2_pos_cmp_match_config_t;

/**
 * @brief uvw config structure
 */
typedef struct {
    qeiv2_uvw_pos_opt_t pos_opt;
    qeiv2_uvw_pos_sel_t u_pos_sel[6];
    qeiv2_uvw_pos_sel_t v_pos_sel[6];
    qeiv2_uvw_pos_sel_t w_pos_sel[6];
    uint32_t pos_cfg[6];
} qeiv2_uvw_config_t;

/**
 * @brief adc config structure
 */
typedef struct {
    uint8_t adc_select;
    uint8_t adc_channel;
    int16_t param0;
    int16_t param1;
    uint32_t offset;
} qeiv2_adc_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief load phcnt, zcnt, spdcnt and tmrcnt into their read registers
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_load_counter_to_read_registers(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->CR |= QEIV2_CR_READ_MASK;
}

/**
 * @brief config z phase counter increment and decrement mode
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] mode
 *  @arg 1 zcnt will increment when phcnt upcount to phmax, decrement when phcnt downcount to 0
 *  @arg 0 zcnt will increment or decrement when Z input assert
 */
static inline void qeiv2_config_z_phase_counter_mode(QEIV2_Type *qeiv2_x, qeiv2_z_count_work_mode_t mode)
{
    qeiv2_x->CR = (qeiv2_x->CR & ~QEIV2_CR_ZCNTCFG_MASK) | QEIV2_CR_ZCNTCFG_SET(mode);
}

/**
 * @brief config phase max value and phase param
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] phmax maximum phcnt number, phcnt will rollover to 0 when it upcount to phmax
 */
static inline void qeiv2_config_phmax_phparam(QEIV2_Type *qeiv2_x, uint32_t phmax)
{
    uint32_t tmp;

    if (phmax > 0u) {
        phmax--;
    }
    qeiv2_x->PHCFG = QEIV2_PHCFG_PHMAX_SET(phmax);
    if (phmax == 0u) {
        qeiv2_x->PHASE_PARAM = 0xFFFFFFFFu;
    } else {
        tmp = (0x80000000u / (phmax + 1u));
        tmp <<= 1u;
        qeiv2_x->PHASE_PARAM = QEIV2_PHASE_PARAM_PHASE_PARAM_SET(tmp);
    }
}

/**
 * @brief config phase calibration value trigged by z phase
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] enable  phcnt will set to phidx when Z input assert
 * @param[in] phidx  phcnt reset value
 * @param[in] mode  qeiv2_work_mode_t
 */
static inline void qeiv2_config_z_phase_calibration(QEIV2_Type *qeiv2_x, uint32_t phidx, bool enable, qeiv2_work_mode_t mode)
{
    uint32_t tmp = qeiv2_x->CR;
    qeiv2_x->PHIDX = QEIV2_PHIDX_PHIDX_SET(phidx);
    if (enable) {
        tmp |= QEIV2_CR_PHCALIZ_MASK;
    } else {
        tmp &= ~QEIV2_CR_PHCALIZ_MASK;
    }
    if (enable && ((mode == qeiv2_work_mode_sin) || (mode == qeiv2_work_mode_sincos))) {
        tmp |= QEIV2_CR_Z_ONLY_EN_MASK;
    } else {
        tmp &= ~QEIV2_CR_Z_ONLY_EN_MASK;
    }
    qeiv2_x->CR = tmp;
}

/**
 * @brief  pause counter when pause assert
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] counter_mask
 *  @arg QEIV2_CR_PAUSEPOS_MASK
 *  @arg QEIV2_CR_PAUSESPD_MASK
 *  @arg QEIV2_CR_PAUSEPH_MASK
 *  @arg QEIV2_CR_PAUSEZ_MASK
 * @param[in] enable enable or disable pause
 */
static inline void qeiv2_pause_counter(QEIV2_Type *qeiv2_x, uint32_t counter_mask, bool enable)
{
    if (enable) {
        qeiv2_x->CR |= counter_mask;
    } else {
        qeiv2_x->CR &= ~counter_mask;
    }
}

/**
 * @brief  pause pos counter when fault assert
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] enable enable or disable pause
 */
static inline void qeiv2_pause_pos_counter_on_fault(QEIV2_Type *qeiv2_x, bool enable)
{
    if (enable) {
        qeiv2_x->CR |= QEIV2_CR_FAULTPOS_MASK;
    } else {
        qeiv2_x->CR &= ~QEIV2_CR_FAULTPOS_MASK;
    }
}

/**
 * @brief  enable load phcnt, zcnt, spdcnt and tmrcnt into their snap registers
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_enable_snap(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->CR |= QEIV2_CR_SNAPEN_MASK;
}

/**
 * @brief disable snap
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_disable_snap(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->CR &= ~QEIV2_CR_SNAPEN_MASK;
}

/**
 * @brief reset zcnt, spdcnt and tmrcnt to 0, reset phcnt to phidx.
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_reset_counter(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->CR |= QEIV2_CR_RSTCNT_MASK;
}

/**
 * @brief release counter.
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_release_counter(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->CR &= ~QEIV2_CR_RSTCNT_MASK;
}

/**
 * @brief select spd and tmr register content
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] content @ref qeiv2_spd_tmr_content_t
 */
static inline void qeiv2_select_spd_tmr_register_content(QEIV2_Type *qeiv2_x, qeiv2_spd_tmr_content_t content)
{
    qeiv2_x->CR = (qeiv2_x->CR & ~QEIV2_CR_RD_SEL_MASK) | QEIV2_CR_RD_SEL_SET(content);
}

/**
 * @brief check spd and tmr register content as pos and angle
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @return true if spd and timer register as pos and angle register
 */
static inline bool qeiv2_check_spd_tmr_as_pos_angle(QEIV2_Type *qeiv2_x)
{
    return ((qeiv2_x->CR & QEIV2_CR_RD_SEL_MASK) != 0) ? true : false;
}

/**
 * @brief set qeiv2 work mode
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] mode @ref qeiv2_work_mode_t
 */
static inline void qeiv2_set_work_mode(QEIV2_Type *qeiv2_x, qeiv2_work_mode_t mode)
{
    qeiv2_x->CR = (qeiv2_x->CR & ~QEIV2_CR_ENCTYP_MASK) | QEIV2_CR_ENCTYP_SET(mode);
}

/**
 * @brief config watchdog
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] timeout watchdog timeout time
 * @param[in] clr_phcnt the phase_cnt time passed, then clear wdog counter
 * @param[in] enable
 *  @arg 1 - enable watchdog
 *  @arg 0 - disable watchdog
 */
static inline void qeiv2_config_wdog(QEIV2_Type *qeiv2_x, uint32_t timeout, uint8_t clr_phcnt, bool enable)
{
    uint32_t tmp;
    tmp = QEIV2_WDGCFG_WDGTO_SET(timeout) | QEIV2_WDGCFG_WDOG_CFG_SET(clr_phcnt);
    if (enable) {
        tmp |= QEIV2_WDGCFG_WDGEN_MASK;
    } else {
        tmp &= ~QEIV2_WDGCFG_WDGEN_MASK;
    }
    qeiv2_x->WDGCFG = tmp;
}

/**
 * @brief enable trig out trigger event
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] event_mask
 *  @arg @ref QEIV2_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_PHASE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_MISS_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_WIDTH_TIME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION2_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_DIR_CHG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME2_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_FAULT_FLAG_MASK
 */
static inline void qeiv2_enable_trig_out_trigger_event(QEIV2_Type *qeiv2_x, uint32_t event_mask)
{
    qeiv2_x->TRGOEN |= event_mask;
}

/**
 * @brief disable trig out trigger event
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] event_mask
 *  @arg @ref QEIV2_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_PHASE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_MISS_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_WIDTH_TIME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION2_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_DIR_CHG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME2_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_FAULT_FLAG_MASK
 */
static inline void qeiv2_disable_trig_out_trigger_event(QEIV2_Type *qeiv2_x, uint32_t event_mask)
{
    qeiv2_x->TRGOEN &= ~event_mask;
}

/**
 * @brief enable load read trigger event
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] event_mask
 *  @arg @ref QEIV2_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_PHASE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_MISS_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_WIDTH_TIME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION2_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_DIR_CHG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME2_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_FAULT_FLAG_MASK
 */
static inline void qeiv2_enable_load_read_trigger_event(QEIV2_Type *qeiv2_x, uint32_t event_mask)
{
    qeiv2_x->READEN |= event_mask;
}

/**
 * @brief disable load read trigger event
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] event_mask
 *  @arg @ref QEIV2_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_PHASE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_MISS_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_WIDTH_TIME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION2_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_DIR_CHG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME2_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_FAULT_FLAG_MASK
 */
static inline void qeiv2_disable_load_read_trigger_event(QEIV2_Type *qeiv2_x, uint32_t event_mask)
{
    qeiv2_x->READEN &= ~event_mask;
}

/**
 * @brief enable dma request
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] mask
 *  @arg @ref QEIV2_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_PHASE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_MISS_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_WIDTH_TIME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION2_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_DIR_CHG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME2_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_FAULT_FLAG_MASK
 */
static inline void qeiv2_enable_dma_request(QEIV2_Type *qeiv2_x, uint32_t mask)
{
    qeiv2_x->DMAEN |= mask;
}

/**
 * @brief disable qeiv2 dma
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] mask
 *  @arg @ref QEIV2_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_PHASE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_MISS_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_WIDTH_TIME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION2_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_DIR_CHG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME2_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_FAULT_FLAG_MASK
 */
static inline void qeiv2_disable_dma_request(QEIV2_Type *qeiv2_x, uint32_t mask)
{
    qeiv2_x->DMAEN &= ~mask;
}

/**
 * @brief clear qeiv2 status register
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] mask
 *  @arg @ref QEIV2_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_PHASE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_MISS_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_WIDTH_TIME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION2_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_DIR_CHG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME2_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_FAULT_FLAG_MASK
 */
static inline void qeiv2_clear_status(QEIV2_Type *qeiv2_x, uint32_t mask)
{
    qeiv2_x->SR = mask;
}

/**
 * @brief get qeiv2 status
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval qeiv2 status:
 *  @arg @ref QEIV2_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_PHASE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_MISS_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_WIDTH_TIME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION2_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_DIR_CHG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME2_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_FAULT_FLAG_MASK
 */
static inline uint32_t qeiv2_get_status(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->SR;
}

/**
 * @brief get qeiv2 bit status
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] mask
 *  @arg @ref QEIV2_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_PHASE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_MISS_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_WIDTH_TIME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION2_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_DIR_CHG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME2_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_FAULT_FLAG_MASK
 * @retval true or false
 */
static inline bool qeiv2_get_bit_status(QEIV2_Type *qeiv2_x, uint32_t mask)
{
    return ((qeiv2_x->SR & mask) == mask) ? true : false;
}

/**
 * @brief enable qeiv2 irq
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] mask
 *  @arg @ref QEIV2_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_PHASE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_MISS_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_WIDTH_TIME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION2_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_DIR_CHG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME2_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_FAULT_FLAG_MASK
 */
static inline void qeiv2_enable_irq(QEIV2_Type *qeiv2_x, uint32_t mask)
{
    qeiv2_x->IRQEN |= mask;
}

/**
 * @brief disable qeiv2 irq
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] mask
 *  @arg @ref QEIV2_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_PHASE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_Z_MISS_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_WIDTH_TIME_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_POSITION2_COMPARE_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_DIR_CHG_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_CYCLE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE0_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_PULSE1_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_HOME2_FLAG_MASK
 *  @arg @ref QEIV2_EVENT_FAULT_FLAG_MASK
 */
static inline void qeiv2_disable_irq(QEIV2_Type *qeiv2_x, uint32_t mask)
{
    qeiv2_x->IRQEN &= ~mask;
}

/**
 * @brief get current counter value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] type @ref qeiv2_counter_type_t
 * @retval counter value
 */
static inline uint32_t qeiv2_get_current_count(QEIV2_Type *qeiv2_x, qeiv2_counter_type_t type)
{
    return *(&qeiv2_x->COUNT[QEIV2_COUNT_CURRENT].Z + type);
}

/**
 * @brief get current phcnt value
 *
 * @param qeiv2_x QEI base address, HPM_QEIx(x=0...n)
 * @return phcnt value 
 */
static inline uint32_t qeiv2_get_current_phase_phcnt(QEIV2_Type *qeiv2_x)
{
    return QEIV2_COUNT_PH_PHCNT_GET(qeiv2_get_current_count(qeiv2_x, qeiv2_counter_type_phase));
}

/**
 * @brief get current a phase level
 *
 * @param qeiv2_x QEI base address, HPM_QEIx(x=0...n)
 * @return a phase level
 */
static inline bool qeiv2_get_current_phase_a_level(QEIV2_Type *qeiv2_x)
{
    return QEIV2_COUNT_PH_ASTAT_GET(qeiv2_get_current_count(qeiv2_x, qeiv2_counter_type_phase));
}

/**
 * @brief get current b phase level
 *
 * @param qeiv2_x QEI base address, HPM_QEIx(x=0...n)
 * @return b phase level
 */
static inline bool qeiv2_get_current_phase_b_level(QEIV2_Type *qeiv2_x)
{
    return QEIV2_COUNT_PH_BSTAT_GET(qeiv2_get_current_count(qeiv2_x, qeiv2_counter_type_phase));
}

/**
 * @brief get current phase dir
 *
 * @param qeiv2_x QEI base address, HPM_QEIx(x=0...n)
 * @return dir
 */
static inline bool qeiv2_get_current_phase_dir(QEIV2_Type *qeiv2_x)
{
    return QEIV2_COUNT_PH_DIR_GET(qeiv2_get_current_count(qeiv2_x, qeiv2_counter_type_phase));
}


/**
 * @brief get read event count value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] type @ref qeiv2_counter_type_t
 * @retval counter value
 */
static inline uint32_t qeiv2_get_count_on_read_event(QEIV2_Type *qeiv2_x, qeiv2_counter_type_t type)
{
    return *(&(qeiv2_x->COUNT[QEIV2_COUNT_READ].Z) + type);
}

/**
 * @brief read the value of each phase snapshot 0 counter
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] type @ref qeiv2_counter_type_t
 * @retval counter value
 */
static inline uint32_t qeiv2_get_count_on_snap0_event(QEIV2_Type *qeiv2_x, qeiv2_counter_type_t type)
{
    return *(&qeiv2_x->COUNT[QEIV2_COUNT_SNAP0].Z + type);
}

/**
 * @brief read the value of each phase snapshot 1 counter
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] type @ref qeiv2_counter_type_t
 * @retval  counter value
 */
static inline uint32_t qeiv2_get_count_on_snap1_event(QEIV2_Type *qeiv2_x, qeiv2_counter_type_t type)
{
    return *(&qeiv2_x->COUNT[QEIV2_COUNT_SNAP1].Z + type);
}

/**
 * @brief set zcnt compare value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] cmp zcnt compare value
 */
static inline void qeiv2_set_z_cmp_value(QEIV2_Type *qeiv2_x, uint32_t cmp)
{
    qeiv2_x->ZCMP = QEIV2_ZCMP_ZCMP_SET(cmp);
}

/**
 * @brief set phcnt compare value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] cmp phcnt compare value
 */
static inline void qeiv2_set_phcnt_cmp_value(QEIV2_Type *qeiv2_x, uint32_t cmp)
{
    qeiv2_x->PHCMP = QEIV2_PHCMP_PHCMP_SET(cmp);
}

/**
 * @brief set spdcnt or position compare value. It's selected by CR register rd_sel bit.
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] cmp spdcnt or position compare value
 *  when set @ref qeiv2_spd_tmr_as_spd_tm, this is spdcmp value. (ABZ encoder)
 *  when set @ref qeiv2_spd_tmr_as_pos_angle, this is poscmp value. (sin or sincos encoder)
 */
static inline void qeiv2_set_spd_pos_cmp_value(QEIV2_Type *qeiv2_x, uint32_t cmp)
{
    qeiv2_x->SPDCMP = QEIV2_SPDCMP_SPDCMP_SET(cmp);
}

/**
 * @brief set compare match options
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] ignore_zcmp ignore zcmp
 * @param[in] ignore_phcmp ignore phcmp
 * @param[in] ignore_spdposcmp ignore spdposcmp
 *  when set @ref qeiv2_spd_tmr_as_spd_tm, this is spdcmp value. (ABZ encoder)
 *  when set @ref qeiv2_spd_tmr_as_pos_angle, this is poscmp value. (sin or sincos encoder)
 * @param[in] ignore_rotate_dir ignore encoder rotation direction. (ABZ encoder)
 * @param[in] rotate_dir when don't ignore rotation direction, match rotation direction. @ref qeiv2_rotate_dir_t. (ABZ encoder)
 * @param[in] ignore_pos_dir ignore position increase or decrease direction. (sin or sincos encoder)
 * @param[in] pos_dir when don't ignore position direction, match position direction. @ref qeiv2_position_dir_t. (sin or sincos encoder)
 */
static inline void qeiv2_set_cmp_match_option(QEIV2_Type *qeiv2_x, bool ignore_zcmp, bool ignore_phcmp, bool ignore_spdposcmp,
                                        bool ignore_rotate_dir, qeiv2_rotate_dir_t rotate_dir, bool ignore_pos_dir, qeiv2_position_dir_t pos_dir)
{
    qeiv2_x->MATCH_CFG = (qeiv2_x->MATCH_CFG & (~(QEIV2_MATCH_CFG_ZCMPDIS_MASK | QEIV2_MATCH_CFG_PHASE_MATCH_DIS_MASK | QEIV2_MATCH_CFG_SPDCMPDIS_MASK
                                                | QEIV2_MATCH_CFG_DIRCMPDIS_MASK | QEIV2_MATCH_CFG_DIRCMP_MASK
                                                | QEIV2_MATCH_CFG_POS_MATCH_OPT_MASK | QEIV2_MATCH_CFG_POS_MATCH_DIR_MASK)))
                        | QEIV2_MATCH_CFG_ZCMPDIS_SET(ignore_zcmp) | QEIV2_MATCH_CFG_PHASE_MATCH_DIS_SET(ignore_phcmp)
                        | QEIV2_MATCH_CFG_SPDCMPDIS_SET(ignore_spdposcmp)
                        | QEIV2_MATCH_CFG_DIRCMPDIS_SET(ignore_rotate_dir) | QEIV2_MATCH_CFG_DIRCMP_SET(rotate_dir)
                        | QEIV2_MATCH_CFG_POS_MATCH_OPT_SET(!ignore_pos_dir) | QEIV2_MATCH_CFG_POS_MATCH_DIR_SET(pos_dir);
}

/**
 * @brief set zcnt compare2 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] cmp zcnt compare2 value
 */
static inline void qeiv2_set_z_cmp2_value(QEIV2_Type *qeiv2_x, uint32_t cmp)
{
    qeiv2_x->ZCMP2 = QEIV2_ZCMP2_ZCMP2_SET(cmp);
}

/**
 * @brief set phcnt compare2 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] cmp phcnt compare2 value
 */
static inline void qeiv2_set_phcnt_cmp2_value(QEIV2_Type *qeiv2_x, uint32_t cmp)
{
    qeiv2_x->PHCMP2 = QEIV2_PHCMP2_PHCMP2_SET(cmp);
}

/**
 * @brief set spdcnt or position compare2 value. It's selected by CR register rd_sel bit.
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] cmp spdcnt or position compare2 value
 */
static inline void qeiv2_set_spd_pos_cmp2_value(QEIV2_Type *qeiv2_x, uint32_t cmp)
{
    qeiv2_x->SPDCMP2 = QEIV2_SPDCMP2_SPDCMP2_SET(cmp);
}

/**
 * @brief set compare2 match options
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] ignore_zcmp ignore zcmp
 * @param[in] ignore_phcmp ignore phcmp
 * @param[in] ignore_spdposcmp ignore spdposcmp.
 *  when set @ref qeiv2_spd_tmr_as_spd_tm, this is spdcmp value. (ABZ encoder)
 *  when set @ref qeiv2_spd_tmr_as_pos_angle, this is poscmp value. (sin or sincos encoder)
 * @param[in] ignore_rotate_dir ignore encoder rotation direction. (ABZ encoder)
 * @param[in] rotate_dir when don't ignore rotation direction, match rotation direction. @ref qeiv2_rotate_dir_t. (ABZ encoder)
 * @param[in] ignore_pos_dir ignore position increase or decrease direction. (sin or sincos encoder)
 * @param[in] pos_dir when don't ignore position direction, match position direction. @ref qeiv2_position_dir_t. (sin or sincos encoder)
 */
static inline void qeiv2_set_cmp2_match_option(QEIV2_Type *qeiv2_x, bool ignore_zcmp, bool ignore_phcmp, bool ignore_spdposcmp,
                                        bool ignore_rotate_dir, qeiv2_rotate_dir_t rotate_dir, bool ignore_pos_dir, qeiv2_position_dir_t pos_dir)
{
    qeiv2_x->MATCH_CFG = (qeiv2_x->MATCH_CFG & ~(QEIV2_MATCH_CFG_ZCMP2DIS_MASK | QEIV2_MATCH_CFG_PHASE_MATCH_DIS2_MASK | QEIV2_MATCH_CFG_SPDCMP2DIS_MASK
                                               | QEIV2_MATCH_CFG_DIRCMP2DIS_MASK | QEIV2_MATCH_CFG_DIRCMP2_MASK
                                               | QEIV2_MATCH_CFG_POS_MATCH2_OPT_MASK | QEIV2_MATCH_CFG_POS_MATCH2_DIR_MASK))
                        | QEIV2_MATCH_CFG_ZCMP2DIS_SET(ignore_zcmp) | QEIV2_MATCH_CFG_PHASE_MATCH_DIS2_SET(ignore_phcmp)
                        | QEIV2_MATCH_CFG_SPDCMP2DIS_SET(ignore_spdposcmp)
                        | QEIV2_MATCH_CFG_DIRCMP2DIS_SET(ignore_rotate_dir) | QEIV2_MATCH_CFG_DIRCMP2_SET(rotate_dir)
                        | QEIV2_MATCH_CFG_POS_MATCH2_OPT_SET(!ignore_pos_dir) | QEIV2_MATCH_CFG_POS_MATCH2_DIR_SET(pos_dir);
}

/**
 * @brief config signal enablement and edge
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] siga_en enable signal A/U
 * @param[in] sigb_en enable signal B/V
 * @param[in] sigz_en enable signal Z/W
 * @param[in] posedge_en enable rise edge
 * @param[in] negedge_en enable fall edge
 */
static inline void qeiv2_config_abz_uvw_signal_edge(QEIV2_Type *qeiv2_x, bool siga_en, bool sigb_en, bool sigz_en, bool posedge_en, bool negedge_en)
{
    qeiv2_x->QEI_CFG = (qeiv2_x->QEI_CFG & ~(QEIV2_QEI_CFG_SIGA_EN_MASK | QEIV2_QEI_CFG_SIGB_EN_MASK | QEIV2_QEI_CFG_SIGZ_EN_MASK
                                           | QEIV2_QEI_CFG_POSIDGE_EN_MASK | QEIV2_QEI_CFG_NEGEDGE_EN_MASK))
                     | (QEIV2_QEI_CFG_SIGA_EN_SET(siga_en) | QEIV2_QEI_CFG_SIGB_EN_SET(sigb_en) | QEIV2_QEI_CFG_SIGZ_EN_SET(sigz_en)
                     | QEIV2_QEI_CFG_POSIDGE_EN_SET(posedge_en) | QEIV2_QEI_CFG_NEGEDGE_EN_SET(negedge_en));
}

/**
 * @brief set pulse0 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] pulse_num for speed detection, will count the cycle number for configed pulse_num
 */
static inline void qeiv2_set_pulse0_num(QEIV2_Type *qeiv2_x, uint32_t pulse_num)
{
    qeiv2_x->PULSE0_NUM = QEIV2_PULSE0_NUM_PULSE0_NUM_SET(pulse_num);
}

/**
 * @brief get cycle0 snap0 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval cycle0 snap0 value
 */
static inline uint32_t qeiv2_get_pulse0_cycle_snap0(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->CYCLE0_SNAP0;
}

/**
 * @brief get cycle0 snap1 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval cycle0 snap1 value
 */
static inline uint32_t qeiv2_get_pulse0_cycle_snap1(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->CYCLE0_SNAP1;
}

/**
 * @brief set pulse1 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] pulse_num for speed detection, will count the cycle number for configed pulse_num
 */
static inline void qeiv2_set_pulse1_num(QEIV2_Type *qeiv2_x, uint32_t pulse_num)
{
    qeiv2_x->PULSE1_NUM = QEIV2_PULSE1_NUM_PULSE1_NUM_SET(pulse_num);
}

/**
 * @brief get cycle1 snap0 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval cycle1 snap0 value
 */
static inline uint32_t qeiv2_get_pulse1_cycle_snap0(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->CYCLE1_SNAP0;
}

/**
 * @brief get cycle1 snap1 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval cycle1 snap1 value
 */
static inline uint32_t qeiv2_get_pulse1_cycle_snap1(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->CYCLE1_SNAP1;
}

/**
 * @brief set cycle0 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] cycle_num for speed detection, will count the pulse number for configed cycle_num
 */
static inline void qeiv2_set_cycle0_num(QEIV2_Type *qeiv2_x, uint32_t cycle_num)
{
    qeiv2_x->CYCLE0_NUM = QEIV2_CYCLE0_NUM_CYCLE0_NUM_SET(cycle_num);
}

/**
 * @brief get pulse0 snap0 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval pulse0 snap0 value
 */
static inline uint32_t qeiv2_get_cycle0_pulse_snap0(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->PULSE0_SNAP0;
}

/**
 * @brief get pulse0 snap1 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval pulse0 snap1 value
 */
static inline uint32_t qeiv2_get_cycle0_pulse_snap1(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->PULSE0_SNAP1;
}

/**
 * @brief get pulse0cycle snap0 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval pulse0cycle snap0 value
 */
static inline uint32_t qeiv2_get_cycle0_pulse0cycle_snap0(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->PULSE0CYCLE_SNAP0;
}

/**
 * @brief get pulse0cycle snap1 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval pulse0cycle snap1 value
 */
static inline uint32_t qeiv2_get_cycle0_pulse0cycle_snap1(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->PULSE0CYCLE_SNAP1;
}

/**
 * @brief set cycle1 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] cycle_num for speed detection, will count the pulse number for configed cycle_num
 */
static inline void qeiv2_set_cycle1_num(QEIV2_Type *qeiv2_x, uint32_t cycle_num)
{
    qeiv2_x->CYCLE1_NUM = QEIV2_CYCLE1_NUM_CYCLE1_NUM_SET(cycle_num);
}

#if defined(HPM_IP_FEATURE_QEIV2_ONESHOT_MODE) && HPM_IP_FEATURE_QEIV2_ONESHOT_MODE
/**
 * @brief disable cycle0 oneshot mode
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_disable_cycle0_oneshot_mode(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG &= ~QEIV2_QEI_CFG_CYCLE0_ONESHOT_MASK;
}

/**
 * @brief enable cycle0 oneshot mode
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_enable_cycle0_oneshot_mode(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG |= QEIV2_QEI_CFG_CYCLE0_ONESHOT_MASK;
}

/**
 * @brief disable cycle1 oneshot mode
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_disable_cycle1_oneshot_mode(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG &= ~QEIV2_QEI_CFG_CYCLE1_ONESHOT_MASK;
}

/**
 * @brief enable cycle1 oneshot mode
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_enable_cycle1_oneshot_mode(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG |= QEIV2_QEI_CFG_CYCLE1_ONESHOT_MASK;
}

/**
 * @brief disable pulse0 oneshot mode
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_disable_pulse0_oneshot_mode(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG &= ~QEIV2_QEI_CFG_PULSE0_ONESHOT_MASK;
}

/**
 * @brief enable pulse0 oneshot mode
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_enable_pulse0_oneshot_mode(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG |= QEIV2_QEI_CFG_PULSE0_ONESHOT_MASK;
}

/**
 * @brief disable pulse1 oneshot mode
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_disable_pulse1_oneshot_mode(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG &= ~QEIV2_QEI_CFG_PULSE1_ONESHOT_MASK;
}

/**
 * @brief enable pulse1 oneshot mode
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_enable_pulse1_oneshot_mode(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG |= QEIV2_QEI_CFG_PULSE1_ONESHOT_MASK;
}
#endif

#if defined(HPM_IP_FEATURE_QEIV2_SW_RESTART_TRG) && HPM_IP_FEATURE_QEIV2_SW_RESTART_TRG
/**
 * @brief disable trigger cycle0
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_disable_trig_cycle0(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG &= ~QEIV2_QEI_CFG_TRIG_CYCLE0_EN_MASK;
}

/**
 * @brief enable trigger cycle0
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_enable_trig_cycle0(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG |= QEIV2_QEI_CFG_TRIG_CYCLE0_EN_MASK;
}

/**
 * @brief disable trigger cycle1
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_disable_trig_cycle1(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG &= ~QEIV2_QEI_CFG_TRIG_CYCLE1_EN_MASK;
}

/**
 * @brief enable trigger cycle1
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_enable_trig_cycle1(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG |= QEIV2_QEI_CFG_TRIG_CYCLE1_EN_MASK;
}

/**
 * @brief disable trigger pulse0
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_disable_trig_pulse0(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG &= ~QEIV2_QEI_CFG_TRIG_PULSE0_EN_MASK;
}

/**
 * @brief enable trigger pulse0
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_enable_trig_pulse0(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG |= QEIV2_QEI_CFG_TRIG_PULSE0_EN_MASK;
}

/**
 * @brief disable trigger pulse1
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_disable_trig_pulse1(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG &= ~QEIV2_QEI_CFG_TRIG_PULSE1_EN_MASK;
}

/**
 * @brief enable trigger pulse1
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_enable_trig_pulse1(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG |= QEIV2_QEI_CFG_TRIG_PULSE1_EN_MASK;
}

/**
 * @brief software restart cycle0
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_sw_restart_cycle0(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG |= QEIV2_QEI_CFG_SW_PULSE0_RESTART_MASK;
}

/**
 * @brief software restart cycle1
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_sw_restart_cycle1(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG |= QEIV2_QEI_CFG_SW_PULSE1_RESTART_MASK;
}

/**
 * @brief software restart pulse0
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_sw_restart_pulse0(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG |= QEIV2_QEI_CFG_SW_CYCLE0_RESTART_MASK;
}

/**
 * @brief software restart pulse1
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 */
static inline void qeiv2_sw_restart_pulse1(QEIV2_Type *qeiv2_x)
{
    qeiv2_x->QEI_CFG |= QEIV2_QEI_CFG_SW_CYCLE1_RESTART_MASK;
}
#endif

/**
 * @brief get pulse1 snap0 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval pulse1 snap0 value
 */
static inline uint32_t qeiv2_get_cycle1_pulse_snap0(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->PULSE1_SNAP0;
}

/**
 * @brief get pulse1 snap1 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval pulse1 snap1 value
 */
static inline uint32_t qeiv2_get_cycle1_pulse_snap1(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->PULSE1_SNAP1;
}

/**
 * @brief get pulse1cycle snap0 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval pulse1cycle snap0 value
 */
static inline uint32_t qeiv2_get_cycle1_pulse1cycle_snap0(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->PULSE1CYCLE_SNAP0;
}

/**
 * @brief get pulse1cycle snap1 value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval pulse01cycle snap1 value
 */
static inline uint32_t qeiv2_get_cycle1_pulse1cycle_snap1(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->PULSE1CYCLE_SNAP1;
}

/**
 * @brief enable or disable clear counter if detect direction change
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] enable enable or disable clear counter if detect direction change
 */
static inline void qeiv2_clear_counter_when_dir_chg(QEIV2_Type *qeiv2_x, bool enable)
{
    if (enable) {
        qeiv2_x->QEI_CFG |= QEIV2_QEI_CFG_SPEED_DIR_CHG_EN_MASK;
    } else {
        qeiv2_x->QEI_CFG &= ~QEIV2_QEI_CFG_SPEED_DIR_CHG_EN_MASK;
    }
}

/**
 * @brief adcx config
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] config qeiv2_adc_config_t
 * @param[in] enable enable or disable adcx
 */
static inline void qeiv2_config_adcx(QEIV2_Type *qeiv2_x, qeiv2_adc_config_t *config, bool enable)
{
    uint32_t tmp;
    tmp = QEIV2_ADCX_CFG0_X_ADCSEL_SET(config->adc_select) | QEIV2_ADCX_CFG0_X_CHAN_SET(config->adc_channel);
    qeiv2_x->ADCX_CFG1 = QEIV2_ADCX_CFG1_X_PARAM1_SET(config->param1) | QEIV2_ADCX_CFG1_X_PARAM0_SET(config->param0);
    qeiv2_x->ADCX_CFG2 = QEIV2_ADCX_CFG2_X_OFFSET_SET(config->offset);
    if (enable) {
        tmp |= QEIV2_ADCX_CFG0_X_ADC_ENABLE_MASK;
    } else {
        tmp &= ~QEIV2_ADCX_CFG0_X_ADC_ENABLE_MASK;
    }
    qeiv2_x->ADCX_CFG0 = tmp;
}

/**
 * @brief adcy config
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] config qeiv2_adc_config_t
 * @param[in] enable enable or disable adcy
 */
static inline void qeiv2_config_adcy(QEIV2_Type *qeiv2_x, qeiv2_adc_config_t *config, bool enable)
{
    uint32_t tmp;
    tmp = QEIV2_ADCY_CFG0_Y_ADCSEL_SET(config->adc_select) | QEIV2_ADCY_CFG0_Y_CHAN_SET(config->adc_channel);
    qeiv2_x->ADCY_CFG1 = QEIV2_ADCY_CFG1_Y_PARAM1_SET(config->param1) | QEIV2_ADCY_CFG1_Y_PARAM0_SET(config->param0);
    qeiv2_x->ADCY_CFG2 = QEIV2_ADCY_CFG2_Y_OFFSET_SET(config->offset);
    if (enable) {
        tmp |= QEIV2_ADCY_CFG0_Y_ADC_ENABLE_MASK;
    } else {
        tmp &= ~QEIV2_ADCY_CFG0_Y_ADC_ENABLE_MASK;
    }
    qeiv2_x->ADCY_CFG0 = tmp;
}

/**
 * @brief set adcx and adcy delay
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] delay x/y delay, default 1.25us@200MHz, max 80ms
 */
static inline void qeiv2_set_adc_xy_delay(QEIV2_Type *qeiv2_x, uint32_t delay)
{
    qeiv2_x->CAL_CFG = QEIV2_CAL_CFG_XY_DELAY_SET(delay);
}

/**
 * @brief set position threshold
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] threshold Position change threshold. When two position changes exceed this value,
 *                      it will be considered as an invalid position and no valid signal will be output.
 */
static inline void qeiv2_set_position_threshold(QEIV2_Type *qeiv2_x, uint32_t threshold)
{
    qeiv2_x->POS_THRESHOLD = QEIV2_POS_THRESHOLD_POS_THRESHOLD_SET(threshold);
}

/**
 * @brief set uvw position option
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] opt qeiv2_uvw_pos_opt_t
 */
static inline void qeiv2_set_uvw_position_opt(QEIV2_Type *qeiv2_x, qeiv2_uvw_pos_opt_t opt)
{
    qeiv2_x->QEI_CFG = (qeiv2_x->QEI_CFG & ~QEIV2_QEI_CFG_UVW_POS_OPT0_MASK) | QEIV2_QEI_CFG_UVW_POS_OPT0_SET(opt);
}

/**
 * @brief set config uvw position
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] idx uvw position config index
 *  @arg @ref qeiv2_uvw_pos_idx_t
 * @param[in] u_pos_sel U position selection based by uvw position option
 *  @arg @ref QEIV2_UVW_POS_OPT_CUR_SEL_LOW
 *  @arg @ref QEIV2_UVW_POS_OPT_CUR_SEL_HIGH
 *  @arg @ref QEIV2_UVW_POS_OPT_CUR_SEL_EDGE
 *  @arg @ref QEIV2_UVW_POS_OPT_NEX_SEL_LOW
 *  @arg @ref QEIV2_UVW_POS_OPT_NEX_SEL_HIGH
 * @param[in] v_pos_sel V position selection based by uvw position option
 *  @arg @ref QEIV2_UVW_POS_OPT_CUR_SEL_LOW
 *  @arg @ref QEIV2_UVW_POS_OPT_CUR_SEL_HIGH
 *  @arg @ref QEIV2_UVW_POS_OPT_CUR_SEL_EDGE
 *  @arg @ref QEIV2_UVW_POS_OPT_NEX_SEL_LOW
 *  @arg @ref QEIV2_UVW_POS_OPT_NEX_SEL_HIGH
 * @param[in] w_pos_sel W position selection based by uvw position option
 *  @arg @ref QEIV2_UVW_POS_OPT_CUR_SEL_LOW
 *  @arg @ref QEIV2_UVW_POS_OPT_CUR_SEL_HIGH
 *  @arg @ref QEIV2_UVW_POS_OPT_CUR_SEL_EDGE
 *  @arg @ref QEIV2_UVW_POS_OPT_NEX_SEL_LOW
 *  @arg @ref QEIV2_UVW_POS_OPT_NEX_SEL_HIGH
 * @param[in] enable enable this uvw config
 */
static inline void qeiv2_set_uvw_position_sel(QEIV2_Type *qeiv2_x, qeiv2_uvw_pos_idx_t idx, uint8_t u_pos_sel, uint8_t v_pos_sel,
                                             uint8_t w_pos_sel, bool enable)
{
    uint32_t tmp;
    tmp = QEIV2_UVW_POS_CFG_U_POS_SEL_SET(u_pos_sel)
        | QEIV2_UVW_POS_CFG_V_POS_SEL_SET(v_pos_sel)
        | QEIV2_UVW_POS_CFG_W_POS_SEL_SET(w_pos_sel);
    if (enable) {
        tmp |= QEIV2_UVW_POS_CFG_POS_EN_MASK;
    } else {
        tmp &= ~QEIV2_UVW_POS_CFG_POS_EN_MASK;
    }
    qeiv2_x->UVW_POS_CFG[idx] = tmp;
}

/**
 * @brief set uvw position
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] idx uvw position config index
 *  @arg @ref qeiv2_uvw_pos_idx_t
 * @param[in] pos angle corresponding to UVW signal position
 */
static inline void qeiv2_set_uvw_position(QEIV2_Type *qeiv2_x, qeiv2_uvw_pos_idx_t idx, uint32_t pos)
{
    qeiv2_x->UVW_POS[idx] = pos;
}

/**
 * @brief set z phase counter value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] cnt z phase counter value
 */
static inline void qeiv2_set_z_phase(QEIV2_Type *qeiv2_x, uint32_t cnt)
{
    qeiv2_x->COUNT[QEIV2_COUNT_CURRENT].Z = cnt;
}

/**
 * @brief set phase counter value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] cnt phase counter value
 */
static inline void qeiv2_set_phase_cnt(QEIV2_Type *qeiv2_x, uint32_t cnt)
{
    qeiv2_x->PHASE_CNT = cnt;
}

/**
 * @brief get phase counter value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval phase counter value
 */
static inline uint32_t qeiv2_get_phase_cnt(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->PHASE_CNT;
}

/**
 * @brief update phase counter value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] inc set to add value to phase_cnt
 * @param[in] dec set to minus value to phase_cnt (set inc and dec same time willl act inc)
 * @param[in] value value to be added or minus from phase_cnt. only valid when inc or dec is set in one 32bit write operation.
 */
static inline void qeiv2_update_phase_cnt(QEIV2_Type *qeiv2_x, bool inc, bool dec, uint32_t value)
{
    qeiv2_x->PHASE_UPDATE = QEIV2_PHASE_UPDATE_INC_SET(inc) | QEIV2_PHASE_UPDATE_DEC_SET(dec) | QEIV2_PHASE_UPDATE_VALUE_SET(value);
}

/**
 * @brief set position value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] pos position
 */
static inline void qeiv2_set_position(QEIV2_Type *qeiv2_x, uint32_t pos)
{
    qeiv2_x->POSITION = pos;
}

/**
 * @brief get position value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval position value
 */
static inline uint32_t qeiv2_get_postion(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->POSITION;
}

/**
 * @brief update position value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] inc set to add value to position
 * @param[in] dec set to minus cnt value to position (set inc and dec same time willl act inc)
 * @param[in] value value to be added or minus from position. only valid when inc or dec is set in one 32bit write operation.
 */
static inline void qeiv2_update_position(QEIV2_Type *qeiv2_x, bool inc, bool dec, uint32_t value)
{
    qeiv2_x->POSITION_UPDATE = QEIV2_POSITION_UPDATE_INC_SET(inc) | QEIV2_POSITION_UPDATE_DEC_SET(dec) | QEIV2_POSITION_UPDATE_VALUE_SET(value);
}

/**
 * @brief get angle value
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @retval angle value
 */
static inline uint32_t qeiv2_get_angle(QEIV2_Type *qeiv2_x)
{
    return qeiv2_x->ANGLE;
}

/**
 * @brief config position timeout for mmc module
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] tm postion timeout value
 * @param[in] enable enable position timeout feature. If timeout, send valid again.
 */
static inline void qeiv2_config_position_timeout(QEIV2_Type *qeiv2_x, uint32_t tm, bool enable)
{
    uint32_t tmp;
    tmp = QEIV2_POS_TIMEOUT_TIMEOUT_SET(tm);
    if (enable) {
        tmp |= QEIV2_POS_TIMEOUT_ENABLE_MASK;
    } else {
        tmp &= ~QEIV2_POS_TIMEOUT_ENABLE_MASK;
    }
    qeiv2_x->POS_TIMEOUT = tmp;
}

/**
 * @brief config phcnt compare match condition
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] config  @ref qeiv2_phcnt_cmp_match_config_t
 * @return status_invalid_argument or status_success
 */
hpm_stat_t qeiv2_config_phcnt_cmp_match_condition(QEIV2_Type *qeiv2_x, qeiv2_phcnt_cmp_match_config_t *config);

/**
 * @brief config position compare match condition
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] config  @ref qeiv2_pos_cmp_match_config_t
 * @return status_invalid_argument or status_success
 */
hpm_stat_t qeiv2_config_position_cmp_match_condition(QEIV2_Type *qeiv2_x, qeiv2_pos_cmp_match_config_t *config);

/**
 * @brief config phcnt compare2 match condition
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] config  @ref qeiv2_phcnt_cmp_match_config_t
 * @return status_invalid_argument or status_success
 */
hpm_stat_t qeiv2_config_phcnt_cmp2_match_condition(QEIV2_Type *qeiv2_x, qeiv2_phcnt_cmp_match_config_t *config);

/**
 * @brief config position compare2 match condition
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] config  @ref qeiv2_pos_cmp_match_config_t
 * @return status_invalid_argument or status_success
 */
hpm_stat_t qeiv2_config_position_cmp2_match_condition(QEIV2_Type *qeiv2_x, qeiv2_pos_cmp_match_config_t *config);

/**
 * @brief get uvw position default config
 *
 * @param[out] config uvw position default config structure pointer
 */
void qeiv2_get_uvw_position_defconfig(qeiv2_uvw_config_t *config);

/**
 * @brief config uvw position
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] config  uvw position config structure pointer
 * @return status_invalid_argument or status_success
 */
hpm_stat_t qeiv2_config_uvw_position(QEIV2_Type *qeiv2_x, qeiv2_uvw_config_t *config);

/**
 * @brief config signal filter
 *
 * @param[in] qeiv2_x QEIV2 base address, HPM_QEIV2x(x=0...n)
 * @param[in] phase filter phase
 *  @arg @ref qeiv2_filter_phase_t
 * @param[in] outinv Filter will invert the output
 * @param[in] mode qeiv2_filter_mode_t
 * @param[in] sync set to enable sychronization input signal with TRGM clock
 * @param[in] filtlen defines the filter counter length.
 */
void qeiv2_config_filter(QEIV2_Type *qeiv2_x, qeiv2_filter_phase_t phase, bool outinv, qeiv2_filter_mode_t mode, bool sync, uint32_t filtlen);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_QEIV2_DRV_H */
