/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_QEI_DRV_H
#define HPM_QEI_DRV_H

#include "hpm_common.h"
#include "hpm_qei_regs.h"
/**
 * @brief QEI driver APIs
 * @defgroup qei_interface QEI driver APIs
 * @ingroup io_interfaces
 * @{
 *
 */
#define QEI_EVENT_WDOG_FLAG_MASK (1U << 31) /**< watchdog flag */
#define QEI_EVENT_HOME_FLAG_MASK (1U << 30) /**< home flag */
#define QEI_EVENT_POSITIVE_COMPARE_FLAG_MASK (1U << 29) /**< postion compare match flag */
#define QEI_EVENT_Z_PHASE_FLAG_MASK (1U << 28) /**< z input flag */

/**
 * @brief counting mode of Z-phase counter
 *
 */
typedef enum qei_z_count_inc_mode {
    qei_z_count_inc_on_z_input_assert = 0, /**< zcnt will increment or decrement when Z input assert */
    qei_z_count_inc_on_phase_count_max = 1, /**< zcnt will increment when phcnt upcount to phmax, decrement when phcnt downcount to 0 */
} qei_z_count_inc_mode_t;

/**
 * @brief motor rotation direction
 *
 */
typedef enum qei_rotation_dir_cmp {
    qei_rotation_dir_cmp_positive = 0,  /**< position compare need positive rotation */
    qei_rotation_dir_cmp_negative = 1,   /**< position compare need negative rotation */
    qei_rotation_dir_cmp_ignore = 2,    /**< ignore */
} qei_rotation_dir_cmp_t;

/**
 * @brief counter type
 *
 */
typedef enum qei_counter_type {
    qei_counter_type_z = 0, /**< Z counter */
    qei_counter_type_phase = 1, /**< Phase counter */
    qei_counter_type_speed = 2, /**< Speed counter */
    qei_counter_type_timer = 3, /**< Timer counter */
} qei_counter_type_t;

/**
 * @brief qei work mode
 *
 */
typedef enum qei_work_mode {
    qei_work_mode_abz = 0,  /**< Orthogonal decoder mode */
    qei_work_mode_pd = 1,   /**< Directional (PD) mode */
    qei_work_mode_ud = 2,   /**< Up and Down (UD) mode */
} qei_work_mode_t;

/**
 * @brief speed history type
 *
 */
typedef enum qei_speed_his_type {
    qei_speed_his0 = QEI_SPDHIS_SPDHIS0, /**< Speed history0 */
    qei_speed_his1 = QEI_SPDHIS_SPDHIS1, /**< Speed history1 */
    qei_speed_his2 = QEI_SPDHIS_SPDHIS2, /**< Speed history2 */
    qei_speed_his3 = QEI_SPDHIS_SPDHIS3, /**< Speed history3 */
} qei_speed_his_type_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief enable qei watchdog
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 */
static inline void qei_wdog_enable(QEI_Type *qei_x)
{
    qei_x->WDGCFG |= QEI_WDGCFG_WDGEN_MASK;
}

/**
 * @brief disable qei watchdog
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 */
static inline void qei_wdog_disable(QEI_Type *qei_x)
{
    qei_x->WDGCFG &= ~QEI_WDGCFG_WDGEN_MASK;
}

/**
 * @brief config watchdog
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] timeout watchdog timeout time
 * @param[in] enable
 *  @arg 1 - enable watchdog, You can use the @ref qei_wdog_disable  open watchdog
 *  @arg 0 - disable watchdog, You can use the @ref qei_wdog_enable  open watchdog
 */
static inline void qei_wdog_config(QEI_Type *qei_x, uint32_t timeout, bool enable)
{
    qei_x->WDGCFG = QEI_WDGCFG_WDGTO_SET(timeout) | QEI_WDGCFG_WDGEN_SET(enable);
}

/**
 * @brief
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] phase_count maximum phcnt number, phcnt will rollover to 0 when it upcount to phmax
 * @param[in] mode
 *  @arg 1 zcnt will increment when phcnt upcount to phmax, decrement when phcnt downcount to 0
 *  @arg 0 zcnt will increment or decrement when Z input assert
 * @param[in] z_calibrate  1- phcnt will set to phidx when Z input assert
 */
static inline void qei_phase_config(QEI_Type *qei_x, uint32_t phase_count,
                              qei_z_count_inc_mode_t mode, bool z_calibrate)
{
    qei_x->PHCFG = QEI_PHCFG_ZCNTCFG_SET(mode) | QEI_PHCFG_PHCALIZ_SET(z_calibrate)
                | QEI_PHCFG_PHMAX_SET(phase_count - 1);
}

/**
 * @brief set phase index
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] phase_index phcnt reset value, phcnt will reset to phidx when phcaliz set to 1
 */
static inline void qei_phase_set_index(QEI_Type *qei_x, uint32_t phase_index)
{
    qei_x->PHIDX = QEI_PHIDX_PHIDX_SET(phase_index);
}

/**
 * @brief enable trigger event
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] event_mask
 *  @arg @ref QEI_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEI_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEI_EVENT_POSITIVE_COMPARE_FLAG_MASK
 *  @arg @ref QEI_EVENT_Z_PHASE_FLAG_MASK
 */
static inline void qei_output_trigger_event_enable(QEI_Type *qei_x, uint32_t event_mask)
{
    qei_x->TRGOEN |= event_mask;
}

/**
 * @brief disable trigger event
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] event_mask
 *  @arg @ref QEI_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEI_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEI_EVENT_POSITIVE_COMPARE_FLAG_MASK
 *  @arg @ref QEI_EVENT_Z_PHASE_FLAG_MASK
 */
static inline void qei_output_trigger_event_disable(QEI_Type *qei_x, uint32_t event_mask)
{
    qei_x->TRGOEN &= ~event_mask;
}

/**
 * @brief enable load read  trigger event
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] event_mask
 *  @arg @ref QEI_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEI_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEI_EVENT_POSITIVE_COMPARE_FLAG_MASK
 *  @arg @ref QEI_EVENT_Z_PHASE_FLAG_MASK
 */
static inline void qei_load_read_trigger_event_enable(QEI_Type *qei_x, uint32_t event_mask)
{
    qei_x->READEN |= event_mask;
}

/**
 * @brief disable load read trigger event
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] event_mask
 *  @arg @ref QEI_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEI_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEI_EVENT_POSITIVE_COMPARE_FLAG_MASK
 *  @arg @ref QEI_EVENT_Z_PHASE_FLAG_MASK
 */
static inline void qei_load_read_trigger_event_disable(QEI_Type *qei_x, uint32_t event_mask)
{
    qei_x->READEN &= ~event_mask;
}

/**
 * @brief set zcnt postion compare value
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] cmp zcnt postion compare value
 */
static inline void qei_z_cmp_set(QEI_Type *qei_x, uint32_t cmp)
{
    qei_x->ZCMP = QEI_ZCMP_ZCMP_SET(cmp);
}

/**
 * @brief set spdcnt position compare value
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] cmp spdcnt position compare value
 */
static inline void qei_speed_cmp_set(QEI_Type *qei_x, uint32_t cmp)
{
    qei_x->SPDCMP = QEI_SPDCMP_SPDCMP_SET(cmp);
}

/**
 * @brief set Phase comparator value
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] cmp phcnt position compare value
 * @param[in] cmp_z 1- postion compare not include zcnt
 * @param[in] rotation_dir @ref qei_rotation_dir_cmp_t
 */
static inline void qei_phase_cmp_set(QEI_Type *qei_x, uint32_t cmp,
                            bool cmp_z, qei_rotation_dir_cmp_t rotation_dir)
{
    qei_x->PHCMP = QEI_PHCMP_PHCMP_SET(cmp)
        | QEI_PHCMP_ZCMPDIS_SET(!cmp_z)
        | ((rotation_dir == qei_rotation_dir_cmp_ignore)
                ? QEI_PHCMP_DIRCMPDIS_MASK : (QEI_PHCMP_DIRCMP_SET(rotation_dir)));
}

/**
 * @brief clear qei status register
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] mask
 *  @arg @ref QEI_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEI_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEI_EVENT_POSITIVE_COMPARE_FLAG_MASK
 *  @arg @ref QEI_EVENT_Z_PHASE_FLAG_MASK
 */
static inline void qei_clear_status(QEI_Type *qei_x, uint32_t mask)
{
    qei_x->SR = mask;
}

/**
 * @brief get qei status
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @retval qei status:
 *  @arg @ref QEI_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEI_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEI_EVENT_POSITIVE_COMPARE_FLAG_MASK
 *  @arg @ref QEI_EVENT_Z_PHASE_FLAG_MASK
 */
static inline uint32_t qei_get_status(QEI_Type *qei_x)
{
    return qei_x->SR;
}

/**
 * @brief get qei bit status
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] mask
 *  @arg @ref QEI_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEI_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEI_EVENT_POSITIVE_COMPARE_FLAG_MASK
 *  @arg @ref QEI_EVENT_Z_PHASE_FLAG_MASK
 * @retval true or false
 */
static inline bool qei_get_bit_status(QEI_Type *qei_x, uint32_t mask)
{
    if ((qei_x->SR & mask) == mask) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief enable qei irq
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] mask
 *  @arg @ref QEI_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEI_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEI_EVENT_POSITIVE_COMPARE_FLAG_MASK
 *  @arg @ref QEI_EVENT_Z_PHASE_FLAG_MASK
 */
static inline void qei_irq_enable(QEI_Type *qei_x, uint32_t mask)
{
    qei_x->IRQEN |= mask;
}

/**
 * @brief disable qei irq
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] mask
 *  @arg @ref QEI_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEI_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEI_EVENT_POSITIVE_COMPARE_FLAG_MASK
 *  @arg @ref QEI_EVENT_Z_PHASE_FLAG_MASK
 */
static inline void qei_irq_disable(QEI_Type *qei_x, uint32_t mask)
{
    qei_x->IRQEN &= ~mask;
}

/**
 * @brief enable dma request
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] mask
 *  @arg @ref QEI_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEI_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEI_EVENT_POSITIVE_COMPARE_FLAG_MASK
 *  @arg @ref QEI_EVENT_Z_PHASE_FLAG_MASK
 */
static inline void qei_dma_request_enable(QEI_Type *qei_x, uint32_t mask)
{
    qei_x->DMAEN |= mask;
}

/**
 * @brief disable qei dma
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] mask
 *  @arg @ref QEI_EVENT_WDOG_FLAG_MASK
 *  @arg @ref QEI_EVENT_HOME_FLAG_MASK
 *  @arg @ref QEI_EVENT_POSITIVE_COMPARE_FLAG_MASK
 *  @arg @ref QEI_EVENT_Z_PHASE_FLAG_MASK
 */
static inline void qei_dma_request_disable(QEI_Type *qei_x, uint32_t mask)
{
    qei_x->DMAEN &= ~mask;
}

/**
 * @brief get current counter value
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] type @ref qei_counter_type_t
 * @retval counter value
 */
static inline uint32_t qei_get_current_count(QEI_Type *qei_x,
                                            qei_counter_type_t type)
{
    return *(&qei_x->COUNT[QEI_COUNT_CURRENT].Z + type);
}

/**
 * @brief get current phcnt value
 *
 * @param qei_x QEI base address, HPM_QEIx(x=0...n)
 * @return phcnt value 
 */
static inline uint32_t qei_get_current_phase_phcnt(QEI_Type *qei_x)
{
    return QEI_COUNT_PH_PHCNT_GET(qei_get_current_count(qei_x, qei_counter_type_phase));
}

/**
 * @brief get current a phase status
 *
 * @param qei_x QEI base address, HPM_QEIx(x=0...n)
 * @return a phase level
 */
static inline bool qei_get_current_phase_astat(QEI_Type *qei_x)
{
    return QEI_COUNT_PH_ASTAT_GET(qei_get_current_count(qei_x, qei_counter_type_phase));
}

/**
 * @brief get current b phase status
 *
 * @param qei_x QEI base address, HPM_QEIx(x=0...n)
 * @return b phase level
 */
static inline bool qei_get_current_phase_bstat(QEI_Type *qei_x)
{
    return QEI_COUNT_PH_BSTAT_GET(qei_get_current_count(qei_x, qei_counter_type_phase));
}

/**
 * @brief get current phase dir
 *
 * @param qei_x QEI base address, HPM_QEIx(x=0...n)
 * @return dir
 */
static inline bool qei_get_current_phase_dir(QEI_Type *qei_x)
{
    return QEI_COUNT_PH_DIR_GET(qei_get_current_count(qei_x, qei_counter_type_phase));
}

/**
 * @brief get read event count value
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] type @ref qei_counter_type_t
 * @retval counter value
 */
static inline uint32_t qei_get_count_on_read_event(QEI_Type *qei_x,
                                            qei_counter_type_t type)
{
    return *(&(qei_x->COUNT[QEI_COUNT_READ].Z) + type);
}

/**
 * @brief read the value of each phase snapshot 0 counter
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] type @ref qei_counter_type_t
 * @retval counter value
 */
static inline uint32_t qei_get_count_on_snap0_event(QEI_Type *qei_x,
                                            qei_counter_type_t type)
{
    return *(&qei_x->COUNT[QEI_COUNT_SNAP0].Z + type);
}

/**
 * @brief read the value of each phase snapshot 1 counter
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] type @ref qei_counter_type_t
 * @retval  counter value
 */
static inline uint32_t qei_get_count_on_snap1_event(QEI_Type *qei_x,
                                            qei_counter_type_t type)
{
    return *(&qei_x->COUNT[QEI_COUNT_SNAP1].Z + type);
}

/**
 * @brief get speed history
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] hist_index @ref qei_speed_his_type_t
 * @retval speed history value
 *  @arg counter value
 */
static inline uint32_t qei_get_speed_history(QEI_Type *qei_x, qei_speed_his_type_t hist_index)
{
    return QEI_SPDHIS_SPDHIS0_GET(qei_x->SPDHIS[hist_index]);
}

/**
 * @brief load phcnt, zcnt, spdcnt and tmrcnt into their read registers
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 */
static inline void qei_load_counter_to_read_registers(QEI_Type *qei_x)
{
    qei_x->CR |= QEI_CR_READ_MASK;
}

/**
 * @brief reset spdcnt/phcnt/zcnt
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] counter_mask
 *  @arg 1 reset zcnt when H assert
 *  @arg (1<<1) reset phcnt when H assert
 *  @arg (1<<2) reset spdcnt when H assert
 */
static inline void qei_reset_counter_on_h_assert(QEI_Type *qei_x,
                                               uint32_t counter_mask)
{
    qei_x->CR |= counter_mask << 16;
}

/**
 * @brief  pause spdcnt when PAUSE assert
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] counter_mask
 *  @arg 1 pause spdcnt when PAUSE assert
 *  @arg (1<<1)  pause spdcnt when PAUSE assert
 *  @arg (1<<2) pause spdcnt when PAUSE assert
 */
static inline void qei_pause_counter_on_pause(QEI_Type *qei_x,
                                               uint32_t counter_mask)
{
    qei_x->CR |= counter_mask << 12;
}

/**
 * @brief  load phcnt, zcnt, spdcnt and tmrcnt into their snap registers
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 */
static inline void qei_snap_enable(QEI_Type *qei_x)
{
    qei_x->CR |= QEI_CR_SNAPEN_MASK;
}

/**
 * @brief disable snap
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 */
static inline void qei_snap_disable(QEI_Type *qei_x)
{
    qei_x->CR &= ~QEI_CR_SNAPEN_MASK;
}

/**
 * @brief reset zcnt, spdcnt and tmrcnt to 0
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 */
static inline void qei_counter_reset_assert(QEI_Type *qei_x)
{
    qei_x->CR |= QEI_CR_RSTCNT_MASK;
}

/**
 * @brief qei counter reset release
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 */
static inline void qei_counter_reset_release(QEI_Type *qei_x)
{
    qei_x->CR &= ~QEI_CR_RSTCNT_MASK;
}

/**
 * @brief set work mode
 *
 * @param[in] qei_x QEI base address, HPM_QEIx(x=0...n)
 * @param[in] mode @ref qei_work_mode_t
 */
static inline void qei_set_work_mode(QEI_Type *qei_x, qei_work_mode_t mode)
{
    qei_x->CR = (qei_x->CR & ~QEI_CR_ENCTYP_MASK) | QEI_CR_ENCTYP_SET(mode);
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_QEI_DRV_H */
