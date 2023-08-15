/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SYNT_H
#define HPM_SYNT_H

typedef struct {
    __RW uint32_t GCR;                         /* 0x0: Global control register */
    __RW uint32_t RLD;                         /* 0x4: Counter reload register */
    __RW uint32_t SYNT_NEW;                    /* 0x8: sync timer new value register */
    __R  uint32_t CNT;                         /* 0xC: Counter */
    __R  uint32_t SYNT_SAVE;                   /* 0x10: sync timer trig save value */
    __R  uint32_t SYNT_READ;                   /* 0x14: sync timer read value */
    __R  uint8_t  RESERVED0[8];                /* 0x18 - 0x1F: Reserved */
    __RW uint32_t CMP[4];                      /* 0x20 - 0x2C: Comparator */
} SYNT_Type;


/* Bitfield definition for register: GCR */
/*
 * SYNC_TIMER_INC (WO)
 *
 * set to increase the sync timer with new_value, auto clr
 */
#define SYNT_GCR_SYNC_TIMER_INC_MASK (0x80000000UL)
#define SYNT_GCR_SYNC_TIMER_INC_SHIFT (31U)
#define SYNT_GCR_SYNC_TIMER_INC_SET(x) (((uint32_t)(x) << SYNT_GCR_SYNC_TIMER_INC_SHIFT) & SYNT_GCR_SYNC_TIMER_INC_MASK)
#define SYNT_GCR_SYNC_TIMER_INC_GET(x) (((uint32_t)(x) & SYNT_GCR_SYNC_TIMER_INC_MASK) >> SYNT_GCR_SYNC_TIMER_INC_SHIFT)

/*
 * SYNC_TIMER_DEC (WO)
 *
 * set to decrease the sync timer with new_value, auto clr
 */
#define SYNT_GCR_SYNC_TIMER_DEC_MASK (0x40000000UL)
#define SYNT_GCR_SYNC_TIMER_DEC_SHIFT (30U)
#define SYNT_GCR_SYNC_TIMER_DEC_SET(x) (((uint32_t)(x) << SYNT_GCR_SYNC_TIMER_DEC_SHIFT) & SYNT_GCR_SYNC_TIMER_DEC_MASK)
#define SYNT_GCR_SYNC_TIMER_DEC_GET(x) (((uint32_t)(x) & SYNT_GCR_SYNC_TIMER_DEC_MASK) >> SYNT_GCR_SYNC_TIMER_DEC_SHIFT)

/*
 * SYNC_TIMER_NEW (WO)
 *
 * set  the sync timer to new_value, auto clr
 */
#define SYNT_GCR_SYNC_TIMER_NEW_MASK (0x20000000UL)
#define SYNT_GCR_SYNC_TIMER_NEW_SHIFT (29U)
#define SYNT_GCR_SYNC_TIMER_NEW_SET(x) (((uint32_t)(x) << SYNT_GCR_SYNC_TIMER_NEW_SHIFT) & SYNT_GCR_SYNC_TIMER_NEW_MASK)
#define SYNT_GCR_SYNC_TIMER_NEW_GET(x) (((uint32_t)(x) & SYNT_GCR_SYNC_TIMER_NEW_MASK) >> SYNT_GCR_SYNC_TIMER_NEW_SHIFT)

/*
 * SYNC_TIMER_RESET (WO)
 *
 * reset sync timer to 0, auto clr
 */
#define SYNT_GCR_SYNC_TIMER_RESET_MASK (0x10000000UL)
#define SYNT_GCR_SYNC_TIMER_RESET_SHIFT (28U)
#define SYNT_GCR_SYNC_TIMER_RESET_SET(x) (((uint32_t)(x) << SYNT_GCR_SYNC_TIMER_RESET_SHIFT) & SYNT_GCR_SYNC_TIMER_RESET_MASK)
#define SYNT_GCR_SYNC_TIMER_RESET_GET(x) (((uint32_t)(x) & SYNT_GCR_SYNC_TIMER_RESET_MASK) >> SYNT_GCR_SYNC_TIMER_RESET_SHIFT)

/*
 * SYNC_TIMER_STOPEN (RW)
 *
 * set to enable cpu_debug_mode to stop the sync timer
 */
#define SYNT_GCR_SYNC_TIMER_STOPEN_MASK (0x20U)
#define SYNT_GCR_SYNC_TIMER_STOPEN_SHIFT (5U)
#define SYNT_GCR_SYNC_TIMER_STOPEN_SET(x) (((uint32_t)(x) << SYNT_GCR_SYNC_TIMER_STOPEN_SHIFT) & SYNT_GCR_SYNC_TIMER_STOPEN_MASK)
#define SYNT_GCR_SYNC_TIMER_STOPEN_GET(x) (((uint32_t)(x) & SYNT_GCR_SYNC_TIMER_STOPEN_MASK) >> SYNT_GCR_SYNC_TIMER_STOPEN_SHIFT)

/*
 * SYNC_TIMER_ENABLE (RW)
 *
 * set to enable the sync timer, clr to stop
 */
#define SYNT_GCR_SYNC_TIMER_ENABLE_MASK (0x10U)
#define SYNT_GCR_SYNC_TIMER_ENABLE_SHIFT (4U)
#define SYNT_GCR_SYNC_TIMER_ENABLE_SET(x) (((uint32_t)(x) << SYNT_GCR_SYNC_TIMER_ENABLE_SHIFT) & SYNT_GCR_SYNC_TIMER_ENABLE_MASK)
#define SYNT_GCR_SYNC_TIMER_ENABLE_GET(x) (((uint32_t)(x) & SYNT_GCR_SYNC_TIMER_ENABLE_MASK) >> SYNT_GCR_SYNC_TIMER_ENABLE_SHIFT)

/*
 * STOPEN (RW)
 *
 * set to enable cpu_debug_mode to stop the counter
 */
#define SYNT_GCR_STOPEN_MASK (0x4U)
#define SYNT_GCR_STOPEN_SHIFT (2U)
#define SYNT_GCR_STOPEN_SET(x) (((uint32_t)(x) << SYNT_GCR_STOPEN_SHIFT) & SYNT_GCR_STOPEN_MASK)
#define SYNT_GCR_STOPEN_GET(x) (((uint32_t)(x) & SYNT_GCR_STOPEN_MASK) >> SYNT_GCR_STOPEN_SHIFT)

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

/* Bitfield definition for register: SYNT_NEW */
/*
 * NEW_VALUE (RW)
 *
 * new value for sync timer, can be used as update/inc/dec
 */
#define SYNT_SYNT_NEW_NEW_VALUE_MASK (0xFFFFFFFFUL)
#define SYNT_SYNT_NEW_NEW_VALUE_SHIFT (0U)
#define SYNT_SYNT_NEW_NEW_VALUE_SET(x) (((uint32_t)(x) << SYNT_SYNT_NEW_NEW_VALUE_SHIFT) & SYNT_SYNT_NEW_NEW_VALUE_MASK)
#define SYNT_SYNT_NEW_NEW_VALUE_GET(x) (((uint32_t)(x) & SYNT_SYNT_NEW_NEW_VALUE_MASK) >> SYNT_SYNT_NEW_NEW_VALUE_SHIFT)

/* Bitfield definition for register: CNT */
/*
 * CNT (RO)
 *
 * counter
 */
#define SYNT_CNT_CNT_MASK (0xFFFFFFFFUL)
#define SYNT_CNT_CNT_SHIFT (0U)
#define SYNT_CNT_CNT_GET(x) (((uint32_t)(x) & SYNT_CNT_CNT_MASK) >> SYNT_CNT_CNT_SHIFT)

/* Bitfield definition for register: SYNT_SAVE */
/*
 * TIME_SAVE (RO)
 *
 * use the trigger to save sync timer here
 */
#define SYNT_SYNT_SAVE_TIME_SAVE_MASK (0xFFFFFFFFUL)
#define SYNT_SYNT_SAVE_TIME_SAVE_SHIFT (0U)
#define SYNT_SYNT_SAVE_TIME_SAVE_GET(x) (((uint32_t)(x) & SYNT_SYNT_SAVE_TIME_SAVE_MASK) >> SYNT_SYNT_SAVE_TIME_SAVE_SHIFT)

/* Bitfield definition for register: SYNT_READ */
/*
 * SYNC_TIME (RO)
 *
 * current sync timer value
 */
#define SYNT_SYNT_READ_SYNC_TIME_MASK (0xFFFFFFFFUL)
#define SYNT_SYNT_READ_SYNC_TIME_SHIFT (0U)
#define SYNT_SYNT_READ_SYNC_TIME_GET(x) (((uint32_t)(x) & SYNT_SYNT_READ_SYNC_TIME_MASK) >> SYNT_SYNT_READ_SYNC_TIME_SHIFT)

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


#endif /* HPM_SYNT_H */
