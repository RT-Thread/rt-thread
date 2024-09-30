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
    __RW uint32_t RESET_STATUS;                /* 0x4: reset source status */
    __RW uint32_t RESET_HOLD;                  /* 0x8: reset hold attribute */
    __RW uint32_t RESET_ENABLE;                /* 0xC: reset source enable */
    __RW uint32_t RESET_HOT;                   /* 0x10: reset type triggered by reset */
    __RW uint32_t RESET_COLD;                  /* 0x14: reset type attribute */
    __R  uint8_t  RESERVED0[4];                /* 0x18 - 0x1B: Reserved */
    __RW uint32_t SOFTWARE_RESET;              /* 0x1C: Software reset counter */
} PPOR_Type;


/* Bitfield definition for register: RESET_FLAG */
/*
 * FLAG (W1C)
 *
 * reset reason of last hard reset, write 1 to clear each bit
 * 0: brownout
 * 1: temperature(not available)
 * 2: resetpin(not available)
 * 4: debug reset
 * 5: jtag reset
 * 8: cpu0 lockup(not available)
 * 9: cpu1 lockup(not available)
 * 10: cpu0 request(not available)
 * 11: cpu1 request(not available)
 * 16: watch dog 0
 * 17: watch dog 1
 * 18: watch dog 2
 * 19: watch dog 3
 * 20: pmic watch dog
 * 31: software
 */
#define PPOR_RESET_FLAG_FLAG_MASK (0xFFFFFFFFUL)
#define PPOR_RESET_FLAG_FLAG_SHIFT (0U)
#define PPOR_RESET_FLAG_FLAG_SET(x) (((uint32_t)(x) << PPOR_RESET_FLAG_FLAG_SHIFT) & PPOR_RESET_FLAG_FLAG_MASK)
#define PPOR_RESET_FLAG_FLAG_GET(x) (((uint32_t)(x) & PPOR_RESET_FLAG_FLAG_MASK) >> PPOR_RESET_FLAG_FLAG_SHIFT)

/* Bitfield definition for register: RESET_STATUS */
/*
 * STATUS (RW)
 *
 * current status of reset sources
 * 0: brownout
 * 1: temperature(not available)
 * 2: resetpin(not available)
 * 4: debug reset
 * 5: jtag reset
 * 8: cpu0 lockup(not available)
 * 9: cpu1 lockup(not available)
 * 10: cpu0 request(not available)
 * 11: cpu1 request(not available)
 * 16: watch dog 0
 * 17: watch dog 1
 * 18: watch dog 2
 * 19: watch dog 3
 * 20: pmic watch dog
 * 31: software
 */
#define PPOR_RESET_STATUS_STATUS_MASK (0xFFFFFFFFUL)
#define PPOR_RESET_STATUS_STATUS_SHIFT (0U)
#define PPOR_RESET_STATUS_STATUS_SET(x) (((uint32_t)(x) << PPOR_RESET_STATUS_STATUS_SHIFT) & PPOR_RESET_STATUS_STATUS_MASK)
#define PPOR_RESET_STATUS_STATUS_GET(x) (((uint32_t)(x) & PPOR_RESET_STATUS_STATUS_MASK) >> PPOR_RESET_STATUS_STATUS_SHIFT)

/* Bitfield definition for register: RESET_HOLD */
/*
 * STATUS (RW)
 *
 * hold arrtibute, when set, SOC keep in reset status until reset source release, or, reset will be released after SOC enter reset status
 * 0: brownout
 * 1: temperature(not available)
 * 2: resetpin(not available)
 * 4: debug reset
 * 5: jtag reset
 * 8: cpu0 lockup(not available)
 * 9: cpu1 lockup(not available)
 * 10: cpu0 request(not available)
 * 11: cpu1 request(not available)
 * 16: watch dog 0
 * 17: watch dog 1
 * 18: watch dog 2
 * 19: watch dog 3
 * 20: pmic watch dog
 * 31: software
 */
#define PPOR_RESET_HOLD_STATUS_MASK (0xFFFFFFFFUL)
#define PPOR_RESET_HOLD_STATUS_SHIFT (0U)
#define PPOR_RESET_HOLD_STATUS_SET(x) (((uint32_t)(x) << PPOR_RESET_HOLD_STATUS_SHIFT) & PPOR_RESET_HOLD_STATUS_MASK)
#define PPOR_RESET_HOLD_STATUS_GET(x) (((uint32_t)(x) & PPOR_RESET_HOLD_STATUS_MASK) >> PPOR_RESET_HOLD_STATUS_SHIFT)

/* Bitfield definition for register: RESET_ENABLE */
/*
 * ENABLE (RW)
 *
 * enable of reset sources
 * 0: brownout
 * 1: temperature(not available)
 * 2: resetpin(not available)
 * 4: debug reset
 * 5: jtag reset
 * 8: cpu0 lockup(not available)
 * 9: cpu1 lockup(not available)
 * 10: cpu0 request(not available)
 * 11: cpu1 request(not available)
 * 16: watch dog 0
 * 17: watch dog 1
 * 18: watch dog 2
 * 19: watch dog 3
 * 20: pmic watch dog
 * 31: software
 */
#define PPOR_RESET_ENABLE_ENABLE_MASK (0xFFFFFFFFUL)
#define PPOR_RESET_ENABLE_ENABLE_SHIFT (0U)
#define PPOR_RESET_ENABLE_ENABLE_SET(x) (((uint32_t)(x) << PPOR_RESET_ENABLE_ENABLE_SHIFT) & PPOR_RESET_ENABLE_ENABLE_MASK)
#define PPOR_RESET_ENABLE_ENABLE_GET(x) (((uint32_t)(x) & PPOR_RESET_ENABLE_ENABLE_MASK) >> PPOR_RESET_ENABLE_ENABLE_SHIFT)

/* Bitfield definition for register: RESET_HOT */
/*
 * TYPE (RW)
 *
 * reset type of reset sources, 0 for cold/warm reset, all system control setting cleared including clock, ioc; 1 for hot reset, system control, ioc setting kept, peripheral setting cleared.
 * 0: brownout
 * 1: temperature(not available)
 * 2: resetpin(not available)
 * 4: debug reset
 * 5: jtag reset
 * 8: cpu0 lockup(not available)
 * 9: cpu1 lockup(not available)
 * 10: cpu0 request(not available)
 * 11: cpu1 request(not available)
 * 16: watch dog 0
 * 17: watch dog 1
 * 18: watch dog 2
 * 19: watch dog 3
 * 20: pmic watch dog
 * 31: software
 */
#define PPOR_RESET_HOT_TYPE_MASK (0xFFFFFFFFUL)
#define PPOR_RESET_HOT_TYPE_SHIFT (0U)
#define PPOR_RESET_HOT_TYPE_SET(x) (((uint32_t)(x) << PPOR_RESET_HOT_TYPE_SHIFT) & PPOR_RESET_HOT_TYPE_MASK)
#define PPOR_RESET_HOT_TYPE_GET(x) (((uint32_t)(x) & PPOR_RESET_HOT_TYPE_MASK) >> PPOR_RESET_HOT_TYPE_SHIFT)

/* Bitfield definition for register: RESET_COLD */
/*
 * FLAG (RW)
 *
 * perform cold or warm reset of chip, 0 for warm reset, fuse value and debug connection preserved; 1 for cold reset, fuse value reloaded and debug connection corrupted.  This bit is ignored when hot reset selected
 * 0: brownout
 * 1: temperature(not available)
 * 2: resetpin(not available)
 * 4: debug reset
 * 5: jtag reset
 * 8: cpu0 lockup(not available)
 * 9: cpu1 lockup(not available)
 * 10: cpu0 request(not available)
 * 11: cpu1 request(not available)
 * 16: watch dog 0
 * 17: watch dog 1
 * 18: watch dog 2
 * 19: watch dog 3
 * 20: pmic watch dog
 * 31: software
 */
#define PPOR_RESET_COLD_FLAG_MASK (0xFFFFFFFFUL)
#define PPOR_RESET_COLD_FLAG_SHIFT (0U)
#define PPOR_RESET_COLD_FLAG_SET(x) (((uint32_t)(x) << PPOR_RESET_COLD_FLAG_SHIFT) & PPOR_RESET_COLD_FLAG_MASK)
#define PPOR_RESET_COLD_FLAG_GET(x) (((uint32_t)(x) & PPOR_RESET_COLD_FLAG_MASK) >> PPOR_RESET_COLD_FLAG_SHIFT)

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
