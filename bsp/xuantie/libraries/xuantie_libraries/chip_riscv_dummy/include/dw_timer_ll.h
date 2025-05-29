/*
 *	Copyright (C) 2017-2024 Alibaba Group Holding Limited
 */

/*******************************************************
 * @file 	dw_timer_ll.h
 * @brief	header file for timer ll driver
 * @version V1.0
 * @date	9. April 2020
 * ******************************************************/

#ifndef _DW_TIMER_LL_H_
#define _DW_TIMER_LL_H_

#include <stdio.h>
#include <soc.h>
#include <csi_core.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*! Timer1 Control Reg, 	offset: 0x08 */
#define DW_TIMER_CTL_ENABLE_SEL_Pos                                    (0U)
#define DW_TIMER_CTL_ENABLE_SEL_Msk                                    (0x1U << DW_TIMER_CTL_ENABLE_SEL_Pos)
#define DW_TIMER_CTL_ENABLE_SEL_EN                                     DW_TIMER_CTL_ENABLE_SEL_Msk

#define DW_TIMER_CTL_MODE_SEL_Pos                                      (1U)
#define DW_TIMER_CTL_MODE_SEL_Msk                                      (0x1U << DW_TIMER_CTL_MODE_SEL_Pos)
#define DW_TIMER_CTL_MODE_SEL_EN                                       DW_TIMER_CTL_MODE_SEL_Msk

#define DW_TIMER_CTL_INT_MASK_Pos                                      (2U)
#define DW_TIMER_CTL_INT_MASK_Msk                                      (0x1U << DW_TIMER_CTL_INT_MASK_Pos)
#define DW_TIMER_CTL_INT_MAKS_EN                                       DW_TIMER_CTL_INT_MASK_Msk

#define DW_TIMER_CTL_HARD_TRIG_Pos                                     (4U)
#define DW_TIMER_CTL_HARD_TRIG_Msk                                     (0x1U << DW_TIMER_CTL_HARD_TRIG_Pos)
#define DW_TIMER_CTL_HARD_TRIG_EN                                      DW_TIMER_CTL_HARD_TRIG_Msk

/*! Timer EOI,            offset: 0x0c */
#define DW_TIMER_EOI_REG_Pos                                           (0U)
#define DW_TIMER_EOI_REG_Msk                                           (0x1U << DW_TIMER_EOI_REG_Pos)
#define DW_TIMER_EOI_REG_EN                                            DW_TIMER_EOI_REG_Msk

/*! Timer Int Status,     offset: 0x10 */
#define DW_TIMER_INT_STATUS_Pos                                        (0U)
#define DW_TIMER_INT_STATUS_Msk                                        (0x1U << DW_TIMER_INT_STATUS_Pos)
#define DW_TIMER_INT_STATUS_EN                                         DW_TIMER_INT_STATUS_Msk

/*! Timers Int Status,    offset: 0xa0 */
#define DW_TIMERS_INT_STATUS_Pos                                       (0U)
#define DW_TIMERS_INT_STATUS_Msk                                       (0x2U << DW_TIMERS_INT_STATUS_Pos)
#define DW_TIMERS_INT_STATUS_EN                                        DW_TIMERS_INT_STATUS_Msk

/*! Timers EOI,           offset: 0xa4 */
#define DW_TIMERS_EOI_REG_Pos                                          (0U)
#define DW_TIMERS_EOI_REG_Msk                                          (0x2U << DW_TIMERS_EOI_REG_Pos)
#define DW_TIMERS_EOI_REG_EN                                           DW_TIMERS_EOI_REG_Msk

/*! Timers Raw Int Status,offset: 0xa8 */
#define DW_TIMERS_RAW_INT_STA_Pos                                      (0U)
#define DW_TIMERS_RAW_INT_STA_Msk                                      (0x2U << DW_TIMERS_RAW_INT_STA_Pos)
#define DW_TIMERS_RAW_INT_STA_EN                                       DW_TIMERS_RAW_INT_STA_Msk

typedef struct {
    __IOM uint32_t TLC;                                                /* Offset: 0x000 (R/W) TimerLoadCount */
    __IM  uint32_t TCV;                                                /* Offset: 0x004 (R/ ) TimerCurrentValue */
    __IOM uint32_t TCR;                                                /* Offset: 0x008 (R/W) TimerControlReg */
    __IM  uint32_t TEOI;                                               /* Offset: 0x00c (R/ ) TimerEOI */
    __IM  uint32_t TIS;                                                /* Offset: 0x010 (R/ ) TimerIntStatus */
} dw_timer_regs_t;

typedef struct {
    dw_timer_regs_t timer[8];
    __IM  uint32_t TSIS;                                               /* Offset: 0x0a0 (R/ ) TimersIntStatus */
    __IM  uint32_t TSEOI;                                              /* Offset: 0x0a4 (R/ ) TimersEOI */
    __IM  uint32_t TSRIS;                                              /* Offset: 0x0a8 (R/ ) TimersRawIntStatus */
} dw_timer_general_regs_t;

static inline uint32_t dw_timer_read_load(dw_timer_regs_t *timer_base)
{
    return (timer_base->TLC);
}
static inline void dw_timer_write_load(dw_timer_regs_t *timer_base, uint32_t value)
{
    timer_base->TLC = value;
}
static inline uint32_t dw_timer_get_current(dw_timer_regs_t *timer_base)
{
    return (timer_base->TCV);
}
static inline void dw_timer_set_enable(dw_timer_regs_t *timer_base)
{
    timer_base->TCR |= (DW_TIMER_CTL_ENABLE_SEL_EN);
}
static inline void dw_timer_set_disable(dw_timer_regs_t *timer_base)
{
    timer_base->TCR &= ~(DW_TIMER_CTL_ENABLE_SEL_EN);
}
static inline uint32_t dw_timer_get_enable(dw_timer_regs_t *timer_base)
{
    return (((timer_base->TCR) & DW_TIMER_CTL_ENABLE_SEL_EN) ? (uint32_t)1 : (uint32_t)0);
}
static inline void dw_timer_set_mode_free(dw_timer_regs_t *timer_base)
{
    timer_base->TCR &= ~(DW_TIMER_CTL_MODE_SEL_EN);
}
static inline void dw_timer_set_mode_load(dw_timer_regs_t *timer_base)
{
    timer_base->TCR |= (DW_TIMER_CTL_MODE_SEL_EN);
}
static inline uint32_t dw_timer_get_model(dw_timer_regs_t *timer_base)
{
    return (((timer_base->TCR) & DW_TIMER_CTL_MODE_SEL_EN) ? (uint32_t)1 : (uint32_t)0);
}
static inline void dw_timer_set_mask(dw_timer_regs_t *timer_base)
{
    timer_base->TCR |= (DW_TIMER_CTL_INT_MAKS_EN);
}
static inline void dw_timer_set_unmask(dw_timer_regs_t *timer_base)
{
    timer_base->TCR &= ~(DW_TIMER_CTL_INT_MAKS_EN);
}
static inline uint32_t dw_timer_get_mask(dw_timer_regs_t *timer_base)
{
    return (((timer_base->TCR) & DW_TIMER_CTL_INT_MAKS_EN) ? (uint32_t)1 : (uint32_t)0);
}
static inline void dw_timer_set_hardtrigger_en(dw_timer_regs_t *timer_base)
{
    timer_base->TCR |= (DW_TIMER_CTL_HARD_TRIG_EN);
}
static inline void dw_timer_set_hardtrigger_dis(dw_timer_regs_t *timer_base)
{
    timer_base->TCR &= ~(DW_TIMER_CTL_HARD_TRIG_EN);
}
static inline uint32_t dw_timer_get_hardtrigger(dw_timer_regs_t *timer_base)
{
    return (((timer_base->TCR) & DW_TIMER_CTL_HARD_TRIG_EN) ? (uint32_t)1 : (uint32_t)0);
}
static inline uint32_t dw_timer_clear_irq(dw_timer_regs_t *timer_base)
{
    return (((timer_base->TEOI) & DW_TIMER_EOI_REG_EN) ? (uint32_t)1 : (uint32_t)0);
}
static inline uint32_t dw_timer_get_int_status(dw_timer_regs_t *timer_base)
{
    return (((timer_base->TIS) & DW_TIMER_INT_STATUS_EN) ? (uint32_t)1 : (uint32_t)0);
}
static inline uint32_t dw_timer_general_active_after_mask(dw_timer_general_regs_t *timer_base)
{
    return ((timer_base->TSIS) & DW_TIMERS_INT_STATUS_EN);
}
static inline uint32_t dw_timer_general_clear_irq(dw_timer_general_regs_t *timer_base)
{
    return ((timer_base->TSEOI) & DW_TIMERS_EOI_REG_EN);
}
static inline uint32_t dw_timer_general_active_prior_mask(dw_timer_general_regs_t *timer_base)
{
    return ((timer_base->TSRIS) & DW_TIMERS_RAW_INT_STA_EN);
}


#ifdef __cplusplus
}
#endif

#endif /* _DW_TIMER_LL_H_ */
