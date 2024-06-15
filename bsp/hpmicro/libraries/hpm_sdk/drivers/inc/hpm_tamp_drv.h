/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_TAMP_DRV_H
#define HPM_TAMP_DRV_H

#include "hpm_common.h"
#include "hpm_tamp_regs.h"

/**
 *
 * @brief TAMPER driver APIs
 * @defgroup tamper_interface TAMPER driver APIs
 * @ingroup io_interfaces
 * @{
 */

typedef enum {
    spd_1_time_per_sec = 0,
    spd_2_times_per_sec,
    spd_4_times_per_sec,
    spd_8_times_per_sec,
    spd_16_times_per_sec,
    spd_32_times_per_sec,
    spd_64_times_per_sec,
    spd_128_times_per_sec,
    spd_256_times_per_sec,
    spd_512_times_per_sec,
    spd_1024_times_per_sec,
    spd_2048_times_per_sec,
    spd_4096_times_per_sec,
    spd_8192_times_per_sec,
    spd_16384_times_per_sec,
    spd_32768_times_per_sec,
} tamper_speed_t;

typedef enum {
    filter_len_1_cycle = 0,
    filter_len_2_cycles,
    filter_len_4_cycles,
    filter_len_8_cycles,
    filter_len_16_cycles,
    filter_len_32_cycles,
    filter_len_64_cycles,
    filter_len_128_cycles,
    filter_len_256_cycles,
    filter_len_512_cycles,
    filter_len_1024_cycles,
    filter_len_2048_cycles,
    filter_len_4096_cycles,
    filter_len_8192_cycles,
    filter_len_16384_cycles,
    filter_len_32768_cycles,
} tamper_filter_len_t;

 typedef struct {
    bool enable;
    bool active_mode;
    bool filter_bypass;
    bool expect_high_level;
    tamper_speed_t speed;
    tamper_filter_len_t filter_len;
    bool auto_recover;    /* used in active mode */
    uint32_t poly;    /* used in active mode */
    uint32_t lfsr;    /* used in active mode */
} tamper_ch_config_t;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Init tamper channel config
 *
 * @param[in] ptr tamper base address
 * @param[in] ch tamper channel
 * @param[in] config tamper channel config struct pointer
 *
 */
void tamp_init_ch_config(TAMP_Type *ptr, uint8_t ch, tamper_ch_config_t *config);

/**
 * @brief Get tamper default channel config
 *
 * @param[in] ptr tamper base address
 * @param[in] config tamper default channel config struct pointer
 *
 */
void tamp_get_default_ch_config(TAMP_Type *ptr, tamper_ch_config_t *config);

/**
 * @brief Set tamper channel enable or disable
 *
 * @param[in] ptr tamper base address
 * @param[in] ch tamper channel
 * @param[in] enable true - enable tamper, false - disable tamper
 *
 */
static inline void tamp_set_ch_enable(TAMP_Type *ptr, uint8_t ch, bool enable)
{
    ch >>= 1u;
    if (enable) {
        ptr->TAMP[ch].CONTROL |= TAMP_TAMP_CONTROL_ENABLE_MASK;
    } else {
        ptr->TAMP[ch].CONTROL &= ~TAMP_TAMP_CONTROL_ENABLE_MASK;
    }
}

/**
 * @brief Set tamper channel config lock or unlock
 *
 * @param[in] ptr tamper base address
 * @param[in] ch tamper channel
 * @param[in] lock true - config lock, false - config unlock
 *
 */
static inline void tamp_set_ch_config_lock(TAMP_Type *ptr, uint8_t ch, bool lock)
{
    ch >>= 1u;
    if (lock) {
        ptr->TAMP[ch].CONTROL |= TAMP_TAMP_CONTROL_LOCK_MASK;
    } else {
        ptr->TAMP[ch].CONTROL &= ~TAMP_TAMP_CONTROL_LOCK_MASK;
    }
}

/**
 * @brief Get tamper all channel flags
 *
 * @param[in] ptr tamper base address
 *
 * @return all channel flags
 */
static inline uint32_t tamp_get_flags(TAMP_Type *ptr)
{
    return TAMP_TAMP_FLAG_FLAG_GET(ptr->TAMP_FLAG);
}

/**
 * @brief Clear tamper flags
 *
 * @param[in] ptr tamper base address
 * @param[in] flags clear channel flags
 *
 */
static inline void tamp_clear_flags(TAMP_Type *ptr, uint32_t flags)
{
    ptr->TAMP_FLAG = TAMP_TAMP_FLAG_FLAG_SET(flags);
}

/**
 * @brief Check tamper channel flag
 *
 * @param[in] ptr TAMPER base address
 * @param[in] ch tamper channel
 *
 * @return true - flag is set, false - falg is unset.
 */
static inline bool tamp_check_ch_flag(TAMP_Type *ptr, uint8_t ch)
{
    return ((TAMP_TAMP_FLAG_FLAG_GET(ptr->TAMP_FLAG) & (1u << ch)) != 0u) ? true : false;
}

/**
 * @brief Clear tamper channel flag
 *
 * @param[in] ptr TAMPER base address
 * @param[in] ch tamper channel
 *
 */
static inline void tamp_clear_ch_flag(TAMP_Type *ptr, uint8_t ch)
{
    ptr->TAMP_FLAG = TAMP_TAMP_FLAG_FLAG_SET(1u << ch);
}

/**
 * @brief Set tamper channel irq enable or disable
 *
 * @param[in] ptr TAMPER base address
 * @param[in] ch tamper channel
 * @param[in] enable true - irq enable, false - irq disable
 *
 */
static inline void tamp_enable_ch_irq(TAMP_Type *ptr, uint8_t ch, bool enable)
{
    if (enable) {
        ptr->IRQ_EN |= TAMP_IRQ_EN_IRQ_EN_SET(1u << ch);
    } else {
        ptr->IRQ_EN &= ~TAMP_IRQ_EN_IRQ_EN_SET(1u << ch);
    }
}

/**
 * @brief Set tamper irq lock or unlock
 *
 * @param[in] ptr tamper base address
 * @param[in] lock true - irq lock, false - irq unlock
 *
 */
static inline void tamp_set_irq_lock(TAMP_Type *ptr, bool lock)
{
    if (lock) {
        ptr->IRQ_EN |= TAMP_IRQ_EN_LOCK_MASK;
    } else {
        ptr->IRQ_EN &= ~TAMP_IRQ_EN_LOCK_MASK;
    }
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_TAMP_DRV_H */

