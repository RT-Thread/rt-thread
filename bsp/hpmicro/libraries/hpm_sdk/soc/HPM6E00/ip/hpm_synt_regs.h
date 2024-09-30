/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SYNT_H
#define HPM_SYNT_H

typedef struct {
    __RW uint32_t GCR;                         /* 0x0: Global control register */
    __RW uint32_t RLD;                         /* 0x4: Counter reload register */
    __RW uint32_t TIMESTAMP_NEW;               /* 0x8: timestamp new value register */
    __R  uint32_t CNT;                         /* 0xC: Counter */
    __R  uint32_t TIMESTAMP_SAV;               /* 0x10: timestamp trig save value */
    __R  uint32_t TIMESTAMP_CUR;               /* 0x14: timestamp read value */
    __R  uint8_t  RESERVED0[8];                /* 0x18 - 0x1F: Reserved */
    __RW uint32_t CMP[16];                     /* 0x20 - 0x5C: Comparator */
} SYNT_Type;


/* Bitfield definition for register: GCR */
/*
 * TIMESTAMP_INC_NEW (WO)
 *
 * set to increase the timesamp with new value, auto clr
 */
#define SYNT_GCR_TIMESTAMP_INC_NEW_MASK (0x80000000UL)
#define SYNT_GCR_TIMESTAMP_INC_NEW_SHIFT (31U)
#define SYNT_GCR_TIMESTAMP_INC_NEW_SET(x) (((uint32_t)(x) << SYNT_GCR_TIMESTAMP_INC_NEW_SHIFT) & SYNT_GCR_TIMESTAMP_INC_NEW_MASK)
#define SYNT_GCR_TIMESTAMP_INC_NEW_GET(x) (((uint32_t)(x) & SYNT_GCR_TIMESTAMP_INC_NEW_MASK) >> SYNT_GCR_TIMESTAMP_INC_NEW_SHIFT)

/*
 * TIMESTAMP_DEC_NEW (WO)
 *
 * set to decrease the timesamp with new value, auto clr
 */
#define SYNT_GCR_TIMESTAMP_DEC_NEW_MASK (0x40000000UL)
#define SYNT_GCR_TIMESTAMP_DEC_NEW_SHIFT (30U)
#define SYNT_GCR_TIMESTAMP_DEC_NEW_SET(x) (((uint32_t)(x) << SYNT_GCR_TIMESTAMP_DEC_NEW_SHIFT) & SYNT_GCR_TIMESTAMP_DEC_NEW_MASK)
#define SYNT_GCR_TIMESTAMP_DEC_NEW_GET(x) (((uint32_t)(x) & SYNT_GCR_TIMESTAMP_DEC_NEW_MASK) >> SYNT_GCR_TIMESTAMP_DEC_NEW_SHIFT)

/*
 * TIMESTAMP_SET_NEW (WO)
 *
 * set  the timesamp to new value, auto clr
 */
#define SYNT_GCR_TIMESTAMP_SET_NEW_MASK (0x20000000UL)
#define SYNT_GCR_TIMESTAMP_SET_NEW_SHIFT (29U)
#define SYNT_GCR_TIMESTAMP_SET_NEW_SET(x) (((uint32_t)(x) << SYNT_GCR_TIMESTAMP_SET_NEW_SHIFT) & SYNT_GCR_TIMESTAMP_SET_NEW_MASK)
#define SYNT_GCR_TIMESTAMP_SET_NEW_GET(x) (((uint32_t)(x) & SYNT_GCR_TIMESTAMP_SET_NEW_MASK) >> SYNT_GCR_TIMESTAMP_SET_NEW_SHIFT)

/*
 * TIMESTAMP_RESET (WO)
 *
 * reset timesamp  to 0, auto clr
 */
#define SYNT_GCR_TIMESTAMP_RESET_MASK (0x10000000UL)
#define SYNT_GCR_TIMESTAMP_RESET_SHIFT (28U)
#define SYNT_GCR_TIMESTAMP_RESET_SET(x) (((uint32_t)(x) << SYNT_GCR_TIMESTAMP_RESET_SHIFT) & SYNT_GCR_TIMESTAMP_RESET_MASK)
#define SYNT_GCR_TIMESTAMP_RESET_GET(x) (((uint32_t)(x) & SYNT_GCR_TIMESTAMP_RESET_MASK) >> SYNT_GCR_TIMESTAMP_RESET_SHIFT)

/*
 * TIMESTAMP_DEBUG_EN (RW)
 *
 * set to enable cpu_debug_mode to stop the timesamp
 */
#define SYNT_GCR_TIMESTAMP_DEBUG_EN_MASK (0x20U)
#define SYNT_GCR_TIMESTAMP_DEBUG_EN_SHIFT (5U)
#define SYNT_GCR_TIMESTAMP_DEBUG_EN_SET(x) (((uint32_t)(x) << SYNT_GCR_TIMESTAMP_DEBUG_EN_SHIFT) & SYNT_GCR_TIMESTAMP_DEBUG_EN_MASK)
#define SYNT_GCR_TIMESTAMP_DEBUG_EN_GET(x) (((uint32_t)(x) & SYNT_GCR_TIMESTAMP_DEBUG_EN_MASK) >> SYNT_GCR_TIMESTAMP_DEBUG_EN_SHIFT)

/*
 * TIMESTAMP_ENABLE (RW)
 *
 * set to enable the timesamp , clr to stop
 */
#define SYNT_GCR_TIMESTAMP_ENABLE_MASK (0x10U)
#define SYNT_GCR_TIMESTAMP_ENABLE_SHIFT (4U)
#define SYNT_GCR_TIMESTAMP_ENABLE_SET(x) (((uint32_t)(x) << SYNT_GCR_TIMESTAMP_ENABLE_SHIFT) & SYNT_GCR_TIMESTAMP_ENABLE_MASK)
#define SYNT_GCR_TIMESTAMP_ENABLE_GET(x) (((uint32_t)(x) & SYNT_GCR_TIMESTAMP_ENABLE_MASK) >> SYNT_GCR_TIMESTAMP_ENABLE_SHIFT)

/*
 * TIMER_ONESHOT (RW)
 *
 * set for one shot mode, timer will run only once.
 * Software need reset timer first to start another one shot
 */
#define SYNT_GCR_TIMER_ONESHOT_MASK (0x8U)
#define SYNT_GCR_TIMER_ONESHOT_SHIFT (3U)
#define SYNT_GCR_TIMER_ONESHOT_SET(x) (((uint32_t)(x) << SYNT_GCR_TIMER_ONESHOT_SHIFT) & SYNT_GCR_TIMER_ONESHOT_MASK)
#define SYNT_GCR_TIMER_ONESHOT_GET(x) (((uint32_t)(x) & SYNT_GCR_TIMER_ONESHOT_MASK) >> SYNT_GCR_TIMER_ONESHOT_SHIFT)

/*
 * COUNTER_DEBUG_EN (RW)
 *
 * set to enable cpu_debug_mode to stop the counter
 */
#define SYNT_GCR_COUNTER_DEBUG_EN_MASK (0x4U)
#define SYNT_GCR_COUNTER_DEBUG_EN_SHIFT (2U)
#define SYNT_GCR_COUNTER_DEBUG_EN_SET(x) (((uint32_t)(x) << SYNT_GCR_COUNTER_DEBUG_EN_SHIFT) & SYNT_GCR_COUNTER_DEBUG_EN_MASK)
#define SYNT_GCR_COUNTER_DEBUG_EN_GET(x) (((uint32_t)(x) & SYNT_GCR_COUNTER_DEBUG_EN_MASK) >> SYNT_GCR_COUNTER_DEBUG_EN_SHIFT)

/*
 * CRST (RW)
 *
 * 1- Reset counter
 */
#define SYNT_GCR_CRST_MASK (0x2U)
#define SYNT_GCR_CRST_SHIFT (1U)
#define SYNT_GCR_CRST_SET(x) (((uint32_t)(x) << SYNT_GCR_CRST_SHIFT) & SYNT_GCR_CRST_MASK)
#define SYNT_GCR_CRST_GET(x) (((uint32_t)(x) & SYNT_GCR_CRST_MASK) >> SYNT_GCR_CRST_SHIFT)

/*
 * CEN (RW)
 *
 * 1- Enable counter
 */
#define SYNT_GCR_CEN_MASK (0x1U)
#define SYNT_GCR_CEN_SHIFT (0U)
#define SYNT_GCR_CEN_SET(x) (((uint32_t)(x) << SYNT_GCR_CEN_SHIFT) & SYNT_GCR_CEN_MASK)
#define SYNT_GCR_CEN_GET(x) (((uint32_t)(x) & SYNT_GCR_CEN_MASK) >> SYNT_GCR_CEN_SHIFT)

/* Bitfield definition for register: RLD */
/*
 * RLD (RW)
 *
 * counter reload value
 */
#define SYNT_RLD_RLD_MASK (0xFFFFFFFFUL)
#define SYNT_RLD_RLD_SHIFT (0U)
#define SYNT_RLD_RLD_SET(x) (((uint32_t)(x) << SYNT_RLD_RLD_SHIFT) & SYNT_RLD_RLD_MASK)
#define SYNT_RLD_RLD_GET(x) (((uint32_t)(x) & SYNT_RLD_RLD_MASK) >> SYNT_RLD_RLD_SHIFT)

/* Bitfield definition for register: TIMESTAMP_NEW */
/*
 * VALUE (RW)
 *
 * new value for timesamp , can be used as set/inc/dec
 */
#define SYNT_TIMESTAMP_NEW_VALUE_MASK (0xFFFFFFFFUL)
#define SYNT_TIMESTAMP_NEW_VALUE_SHIFT (0U)
#define SYNT_TIMESTAMP_NEW_VALUE_SET(x) (((uint32_t)(x) << SYNT_TIMESTAMP_NEW_VALUE_SHIFT) & SYNT_TIMESTAMP_NEW_VALUE_MASK)
#define SYNT_TIMESTAMP_NEW_VALUE_GET(x) (((uint32_t)(x) & SYNT_TIMESTAMP_NEW_VALUE_MASK) >> SYNT_TIMESTAMP_NEW_VALUE_SHIFT)

/* Bitfield definition for register: CNT */
/*
 * CNT (RO)
 *
 * counter
 */
#define SYNT_CNT_CNT_MASK (0xFFFFFFFFUL)
#define SYNT_CNT_CNT_SHIFT (0U)
#define SYNT_CNT_CNT_GET(x) (((uint32_t)(x) & SYNT_CNT_CNT_MASK) >> SYNT_CNT_CNT_SHIFT)

/* Bitfield definition for register: TIMESTAMP_SAV */
/*
 * VALUE (RO)
 *
 * use the trigger to save timesamp  here
 */
#define SYNT_TIMESTAMP_SAV_VALUE_MASK (0xFFFFFFFFUL)
#define SYNT_TIMESTAMP_SAV_VALUE_SHIFT (0U)
#define SYNT_TIMESTAMP_SAV_VALUE_GET(x) (((uint32_t)(x) & SYNT_TIMESTAMP_SAV_VALUE_MASK) >> SYNT_TIMESTAMP_SAV_VALUE_SHIFT)

/* Bitfield definition for register: TIMESTAMP_CUR */
/*
 * VALUE (RO)
 *
 * current timesamp  value
 */
#define SYNT_TIMESTAMP_CUR_VALUE_MASK (0xFFFFFFFFUL)
#define SYNT_TIMESTAMP_CUR_VALUE_SHIFT (0U)
#define SYNT_TIMESTAMP_CUR_VALUE_GET(x) (((uint32_t)(x) & SYNT_TIMESTAMP_CUR_VALUE_MASK) >> SYNT_TIMESTAMP_CUR_VALUE_SHIFT)

/* Bitfield definition for register array: CMP */
/*
 * CMP (RW)
 *
 * comparator value, the output will assert when counter count to this value
 */
#define SYNT_CMP_CMP_MASK (0xFFFFFFFFUL)
#define SYNT_CMP_CMP_SHIFT (0U)
#define SYNT_CMP_CMP_SET(x) (((uint32_t)(x) << SYNT_CMP_CMP_SHIFT) & SYNT_CMP_CMP_MASK)
#define SYNT_CMP_CMP_GET(x) (((uint32_t)(x) & SYNT_CMP_CMP_MASK) >> SYNT_CMP_CMP_SHIFT)



/* CMP register group index macro definition */
#define SYNT_CMP_0 (0UL)
#define SYNT_CMP_1 (1UL)
#define SYNT_CMP_2 (2UL)
#define SYNT_CMP_3 (3UL)
#define SYNT_CMP_4 (4UL)
#define SYNT_CMP_5 (5UL)
#define SYNT_CMP_6 (6UL)
#define SYNT_CMP_7 (7UL)
#define SYNT_CMP_8 (8UL)
#define SYNT_CMP_9 (9UL)
#define SYNT_CMP_10 (10UL)
#define SYNT_CMP_11 (11UL)
#define SYNT_CMP_12 (12UL)
#define SYNT_CMP_13 (13UL)
#define SYNT_CMP_14 (14UL)
#define SYNT_CMP_15 (15UL)


#endif /* HPM_SYNT_H */
