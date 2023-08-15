/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_RTC_H
#define HPM_RTC_H

typedef struct {
    __RW uint32_t SECOND;                      /* 0x0: Second counter */
    __R  uint32_t SUBSEC;                      /* 0x4: Sub-second counter */
    __RW uint32_t SEC_SNAP;                    /* 0x8: Second counter snap shot */
    __RW uint32_t SUB_SNAP;                    /* 0xC: Sub-second counter snap shot */
    __RW uint32_t ALARM0;                      /* 0x10: RTC alarm0 */
    __RW uint32_t ALARM0_INC;                  /* 0x14: Alarm0 incremental */
    __RW uint32_t ALARM1;                      /* 0x18: RTC alarm1 */
    __RW uint32_t ALARM1_INC;                  /* 0x1C: Alarm1 incremental */
    __RW uint32_t ALARM_FLAG;                  /* 0x20: RTC alarm flag */
    __RW uint32_t ALARM_EN;                    /* 0x24: RTC alarm enable */
} RTC_Type;


/* Bitfield definition for register: SECOND */
/*
 * SECOND (RW)
 *
 * second counter
 */
#define RTC_SECOND_SECOND_MASK (0xFFFFFFFFUL)
#define RTC_SECOND_SECOND_SHIFT (0U)
#define RTC_SECOND_SECOND_SET(x) (((uint32_t)(x) << RTC_SECOND_SECOND_SHIFT) & RTC_SECOND_SECOND_MASK)
#define RTC_SECOND_SECOND_GET(x) (((uint32_t)(x) & RTC_SECOND_SECOND_MASK) >> RTC_SECOND_SECOND_SHIFT)

/* Bitfield definition for register: SUBSEC */
/*
 * SUBSEC (RO)
 *
 * sub second counter
 */
#define RTC_SUBSEC_SUBSEC_MASK (0xFFFFFFFFUL)
#define RTC_SUBSEC_SUBSEC_SHIFT (0U)
#define RTC_SUBSEC_SUBSEC_GET(x) (((uint32_t)(x) & RTC_SUBSEC_SUBSEC_MASK) >> RTC_SUBSEC_SUBSEC_SHIFT)

/* Bitfield definition for register: SEC_SNAP */
/*
 * SEC_SNAP (RW)
 *
 * second snap shot, write to take snap shot
 */
#define RTC_SEC_SNAP_SEC_SNAP_MASK (0xFFFFFFFFUL)
#define RTC_SEC_SNAP_SEC_SNAP_SHIFT (0U)
#define RTC_SEC_SNAP_SEC_SNAP_SET(x) (((uint32_t)(x) << RTC_SEC_SNAP_SEC_SNAP_SHIFT) & RTC_SEC_SNAP_SEC_SNAP_MASK)
#define RTC_SEC_SNAP_SEC_SNAP_GET(x) (((uint32_t)(x) & RTC_SEC_SNAP_SEC_SNAP_MASK) >> RTC_SEC_SNAP_SEC_SNAP_SHIFT)

/* Bitfield definition for register: SUB_SNAP */
/*
 * SUB_SNAP (RW)
 *
 * sub second snap shot, write to take snap shot
 */
#define RTC_SUB_SNAP_SUB_SNAP_MASK (0xFFFFFFFFUL)
#define RTC_SUB_SNAP_SUB_SNAP_SHIFT (0U)
#define RTC_SUB_SNAP_SUB_SNAP_SET(x) (((uint32_t)(x) << RTC_SUB_SNAP_SUB_SNAP_SHIFT) & RTC_SUB_SNAP_SUB_SNAP_MASK)
#define RTC_SUB_SNAP_SUB_SNAP_GET(x) (((uint32_t)(x) & RTC_SUB_SNAP_SUB_SNAP_MASK) >> RTC_SUB_SNAP_SUB_SNAP_SHIFT)

/* Bitfield definition for register: ALARM0 */
/*
 * ALARM (RW)
 *
 * Alarm time for second counter, on each alarm match, alarm increase ALARM0_INC
 */
#define RTC_ALARM0_ALARM_MASK (0xFFFFFFFFUL)
#define RTC_ALARM0_ALARM_SHIFT (0U)
#define RTC_ALARM0_ALARM_SET(x) (((uint32_t)(x) << RTC_ALARM0_ALARM_SHIFT) & RTC_ALARM0_ALARM_MASK)
#define RTC_ALARM0_ALARM_GET(x) (((uint32_t)(x) & RTC_ALARM0_ALARM_MASK) >> RTC_ALARM0_ALARM_SHIFT)

/* Bitfield definition for register: ALARM0_INC */
/*
 * INCREASE (RW)
 *
 * adder when ARLAM0 happen, helps to create periodical alarm
 */
#define RTC_ALARM0_INC_INCREASE_MASK (0xFFFFFFFFUL)
#define RTC_ALARM0_INC_INCREASE_SHIFT (0U)
#define RTC_ALARM0_INC_INCREASE_SET(x) (((uint32_t)(x) << RTC_ALARM0_INC_INCREASE_SHIFT) & RTC_ALARM0_INC_INCREASE_MASK)
#define RTC_ALARM0_INC_INCREASE_GET(x) (((uint32_t)(x) & RTC_ALARM0_INC_INCREASE_MASK) >> RTC_ALARM0_INC_INCREASE_SHIFT)

/* Bitfield definition for register: ALARM1 */
/*
 * ALARM (RW)
 *
 * Alarm time for second counter, on each alarm match, alarm increase ALARM0_INC
 */
#define RTC_ALARM1_ALARM_MASK (0xFFFFFFFFUL)
#define RTC_ALARM1_ALARM_SHIFT (0U)
#define RTC_ALARM1_ALARM_SET(x) (((uint32_t)(x) << RTC_ALARM1_ALARM_SHIFT) & RTC_ALARM1_ALARM_MASK)
#define RTC_ALARM1_ALARM_GET(x) (((uint32_t)(x) & RTC_ALARM1_ALARM_MASK) >> RTC_ALARM1_ALARM_SHIFT)

/* Bitfield definition for register: ALARM1_INC */
/*
 * INCREASE (RW)
 *
 * adder when ARLAM0 happen, helps to create periodical alarm
 */
#define RTC_ALARM1_INC_INCREASE_MASK (0xFFFFFFFFUL)
#define RTC_ALARM1_INC_INCREASE_SHIFT (0U)
#define RTC_ALARM1_INC_INCREASE_SET(x) (((uint32_t)(x) << RTC_ALARM1_INC_INCREASE_SHIFT) & RTC_ALARM1_INC_INCREASE_MASK)
#define RTC_ALARM1_INC_INCREASE_GET(x) (((uint32_t)(x) & RTC_ALARM1_INC_INCREASE_MASK) >> RTC_ALARM1_INC_INCREASE_SHIFT)

/* Bitfield definition for register: ALARM_FLAG */
/*
 * ALARM1 (RW)
 *
 * alarm1 happen
 */
#define RTC_ALARM_FLAG_ALARM1_MASK (0x2U)
#define RTC_ALARM_FLAG_ALARM1_SHIFT (1U)
#define RTC_ALARM_FLAG_ALARM1_SET(x) (((uint32_t)(x) << RTC_ALARM_FLAG_ALARM1_SHIFT) & RTC_ALARM_FLAG_ALARM1_MASK)
#define RTC_ALARM_FLAG_ALARM1_GET(x) (((uint32_t)(x) & RTC_ALARM_FLAG_ALARM1_MASK) >> RTC_ALARM_FLAG_ALARM1_SHIFT)

/*
 * ALARM0 (RW)
 *
 * alarm0 happen
 */
#define RTC_ALARM_FLAG_ALARM0_MASK (0x1U)
#define RTC_ALARM_FLAG_ALARM0_SHIFT (0U)
#define RTC_ALARM_FLAG_ALARM0_SET(x) (((uint32_t)(x) << RTC_ALARM_FLAG_ALARM0_SHIFT) & RTC_ALARM_FLAG_ALARM0_MASK)
#define RTC_ALARM_FLAG_ALARM0_GET(x) (((uint32_t)(x) & RTC_ALARM_FLAG_ALARM0_MASK) >> RTC_ALARM_FLAG_ALARM0_SHIFT)

/* Bitfield definition for register: ALARM_EN */
/*
 * ENABLE1 (RW)
 *
 * alarm1 mask
 * 0: alarm1 disabled
 * 1: alarm1 enabled
 */
#define RTC_ALARM_EN_ENABLE1_MASK (0x2U)
#define RTC_ALARM_EN_ENABLE1_SHIFT (1U)
#define RTC_ALARM_EN_ENABLE1_SET(x) (((uint32_t)(x) << RTC_ALARM_EN_ENABLE1_SHIFT) & RTC_ALARM_EN_ENABLE1_MASK)
#define RTC_ALARM_EN_ENABLE1_GET(x) (((uint32_t)(x) & RTC_ALARM_EN_ENABLE1_MASK) >> RTC_ALARM_EN_ENABLE1_SHIFT)

/*
 * ENABLE0 (RW)
 *
 * alarm0 mask
 * 0: alarm0 disabled
 * 1: alarm0 enabled
 */
#define RTC_ALARM_EN_ENABLE0_MASK (0x1U)
#define RTC_ALARM_EN_ENABLE0_SHIFT (0U)
#define RTC_ALARM_EN_ENABLE0_SET(x) (((uint32_t)(x) << RTC_ALARM_EN_ENABLE0_SHIFT) & RTC_ALARM_EN_ENABLE0_MASK)
#define RTC_ALARM_EN_ENABLE0_GET(x) (((uint32_t)(x) & RTC_ALARM_EN_ENABLE0_MASK) >> RTC_ALARM_EN_ENABLE0_SHIFT)




#endif /* HPM_RTC_H */
