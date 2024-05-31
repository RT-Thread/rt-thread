/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PPOR_H
#define HPM_PPOR_H

typedef struct {
    __W  uint32_t RESET_FLAG;                  /* 0x0: flag indicate reset source */
    __R  uint32_t RESET_STATUS;                /* 0x4: reset source status */
    __RW uint32_t RESET_HOLD;                  /* 0x8: reset hold attribute */
    __RW uint32_t RESET_ENABLE;                /* 0xC: reset source enable */
    __R  uint8_t  RESERVED0[12];               /* 0x10 - 0x1B: Reserved */
    __RW uint32_t SOFTWARE_RESET;              /* 0x1C: Software reset counter */
} PPOR_Type;


/* Bitfield definition for register: RESET_FLAG */
/*
 * FLAG (W1C)
 *
 * reset reason of last hard reset, write 1 to clear each bit
 * 0: brownout
 * 1: temperature(not available)
 * 4: debug reset
 * 5: jtag soft reset
 * 8: cpu0 lockup(not available)
 * 9: cpu1 lockup(not available)
 * 10: cpu0 request(not available)
 * 11: cpu1 request(not available)
 * 16: watch dog 0
 * 17: watch dog 1
 * 18: watch dog 2(not available)
 * 19: watch dog 3(not available)
 * 24: pmic watch dog
 * 30: jtag ieee reset
 * 31: software
 */
#define PPOR_RESET_FLAG_FLAG_MASK (0xFFFFFFFFUL)
#define PPOR_RESET_FLAG_FLAG_SHIFT (0U)
#define PPOR_RESET_FLAG_FLAG_SET(x) (((uint32_t)(x) << PPOR_RESET_FLAG_FLAG_SHIFT) & PPOR_RESET_FLAG_FLAG_MASK)
#define PPOR_RESET_FLAG_FLAG_GET(x) (((uint32_t)(x) & PPOR_RESET_FLAG_FLAG_MASK) >> PPOR_RESET_FLAG_FLAG_SHIFT)

/* Bitfield definition for register: RESET_STATUS */
/*
 * STATUS (RO)
 *
 * current status of reset sources
 * 0: brownout
 * 1: temperature(not available)
 * 4: debug reset
 * 5: jtag soft reset
 * 8: cpu0 lockup(not available)
 * 9: cpu1 lockup(not available)
 * 10: cpu0 request(not available)
 * 11: cpu1 request(not available)
 * 16: watch dog 0
 * 17: watch dog 1
 * 18: watch dog 2(not available)
 * 19: watch dog 3(not available)
 * 24: pmic watch dog
 * 30: jtag ieee reset
 * 31: software
 */
#define PPOR_RESET_STATUS_STATUS_MASK (0xFFFFFFFFUL)
#define PPOR_RESET_STATUS_STATUS_SHIFT (0U)
#define PPOR_RESET_STATUS_STATUS_GET(x) (((uint32_t)(x) & PPOR_RESET_STATUS_STATUS_MASK) >> PPOR_RESET_STATUS_STATUS_SHIFT)

/* Bitfield definition for register: RESET_HOLD */
/*
 * HOLD (RW)
 *
 * hold arrtibute, when set, SOC keep in reset status until reset source release, or, reset will be released after SOC enter reset status
 * 0: brownout
 * 1: temperature(not available)
 * 4: debug reset
 * 5: jtag soft reset
 * 8: cpu0 lockup(not available)
 * 9: cpu1 lockup(not available)
 * 10: cpu0 request(not available)
 * 11: cpu1 request(not available)
 * 16: watch dog 0
 * 17: watch dog 1
 * 18: watch dog 2(not available)
 * 19: watch dog 3(not available)
 * 24: pmic watch dog
 * 30: jtag ieee reset
 * 31: software
 */
#define PPOR_RESET_HOLD_HOLD_MASK (0xFFFFFFFFUL)
#define PPOR_RESET_HOLD_HOLD_SHIFT (0U)
#define PPOR_RESET_HOLD_HOLD_SET(x) (((uint32_t)(x) << PPOR_RESET_HOLD_HOLD_SHIFT) & PPOR_RESET_HOLD_HOLD_MASK)
#define PPOR_RESET_HOLD_HOLD_GET(x) (((uint32_t)(x) & PPOR_RESET_HOLD_HOLD_MASK) >> PPOR_RESET_HOLD_HOLD_SHIFT)

/* Bitfield definition for register: RESET_ENABLE */
/*
 * ENABLE (RW)
 *
 * enable of reset sources
 * 0: brownout
 * 1: temperature(not available)
 * 4: debug reset
 * 5: jtag soft reset
 * 8: cpu0 lockup(not available)
 * 9: cpu1 lockup(not available)
 * 10: cpu0 request(not available)
 * 11: cpu1 request(not available)
 * 16: watch dog 0
 * 17: watch dog 1
 * 18: watch dog 2(not available)
 * 19: watch dog 3(not available)
 * 24: pmic watch dog
 * 30: jtag ieee reset
 * 31: software
 */
#define PPOR_RESET_ENABLE_ENABLE_MASK (0xFFFFFFFFUL)
#define PPOR_RESET_ENABLE_ENABLE_SHIFT (0U)
#define PPOR_RESET_ENABLE_ENABLE_SET(x) (((uint32_t)(x) << PPOR_RESET_ENABLE_ENABLE_SHIFT) & PPOR_RESET_ENABLE_ENABLE_MASK)
#define PPOR_RESET_ENABLE_ENABLE_GET(x) (((uint32_t)(x) & PPOR_RESET_ENABLE_ENABLE_MASK) >> PPOR_RESET_ENABLE_ENABLE_SHIFT)

/* Bitfield definition for register: SOFTWARE_RESET */
/*
 * COUNTER (RW)
 *
 * counter decrease in 24MHz and stop at 0, trigger reset when value reach 2, software can write 0 to cancel reset
 */
#define PPOR_SOFTWARE_RESET_COUNTER_MASK (0xFFFFFFFFUL)
#define PPOR_SOFTWARE_RESET_COUNTER_SHIFT (0U)
#define PPOR_SOFTWARE_RESET_COUNTER_SET(x) (((uint32_t)(x) << PPOR_SOFTWARE_RESET_COUNTER_SHIFT) & PPOR_SOFTWARE_RESET_COUNTER_MASK)
#define PPOR_SOFTWARE_RESET_COUNTER_GET(x) (((uint32_t)(x) & PPOR_SOFTWARE_RESET_COUNTER_MASK) >> PPOR_SOFTWARE_RESET_COUNTER_SHIFT)




#endif /* HPM_PPOR_H */
