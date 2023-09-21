/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_BPOR_H
#define HPM_BPOR_H

typedef struct {
    __RW uint32_t POR_CAUSE;                   /* 0x0: Power on cause */
    __RW uint32_t POR_SELECT;                  /* 0x4: Power on select */
    __RW uint32_t POR_CONFIG;                  /* 0x8: Power on reset config */
    __RW uint32_t POR_CONTROL;                 /* 0xC: Power down control */
} BPOR_Type;


/* Bitfield definition for register: POR_CAUSE */
/*
 * CAUSE (RW)
 *
 * Power on cause, each bit represnts one cause, write 1 to clear each bit
 * bit0: wakeup button
 * bit1: security violation
 * bit2: RTC alarm 0
 * bit3: RTC alarm 1
 * bit4: GPIO
 */
#define BPOR_POR_CAUSE_CAUSE_MASK (0x1FU)
#define BPOR_POR_CAUSE_CAUSE_SHIFT (0U)
#define BPOR_POR_CAUSE_CAUSE_SET(x) (((uint32_t)(x) << BPOR_POR_CAUSE_CAUSE_SHIFT) & BPOR_POR_CAUSE_CAUSE_MASK)
#define BPOR_POR_CAUSE_CAUSE_GET(x) (((uint32_t)(x) & BPOR_POR_CAUSE_CAUSE_MASK) >> BPOR_POR_CAUSE_CAUSE_SHIFT)

/* Bitfield definition for register: POR_SELECT */
/*
 * SELECT (RW)
 *
 * Power on cause select, each bit represnts one cause, value 1 enables corresponding cause
 * bit0: wakeup button
 * bit1: security violation
 * bit2: RTC alarm 0
 * bit3: RTC alarm 1
 * bit4: GPIO
 */
#define BPOR_POR_SELECT_SELECT_MASK (0x1FU)
#define BPOR_POR_SELECT_SELECT_SHIFT (0U)
#define BPOR_POR_SELECT_SELECT_SET(x) (((uint32_t)(x) << BPOR_POR_SELECT_SELECT_SHIFT) & BPOR_POR_SELECT_SELECT_MASK)
#define BPOR_POR_SELECT_SELECT_GET(x) (((uint32_t)(x) & BPOR_POR_SELECT_SELECT_MASK) >> BPOR_POR_SELECT_SELECT_SHIFT)

/* Bitfield definition for register: POR_CONFIG */
/*
 * RETENTION (RW)
 *
 * retention battery domain setting
 * 0: battery reset on reset pin reset happen
 * 1: battery domain retention when reset pin reset happen
 */
#define BPOR_POR_CONFIG_RETENTION_MASK (0x1U)
#define BPOR_POR_CONFIG_RETENTION_SHIFT (0U)
#define BPOR_POR_CONFIG_RETENTION_SET(x) (((uint32_t)(x) << BPOR_POR_CONFIG_RETENTION_SHIFT) & BPOR_POR_CONFIG_RETENTION_MASK)
#define BPOR_POR_CONFIG_RETENTION_GET(x) (((uint32_t)(x) & BPOR_POR_CONFIG_RETENTION_MASK) >> BPOR_POR_CONFIG_RETENTION_SHIFT)

/* Bitfield definition for register: POR_CONTROL */
/*
 * COUNTER (RW)
 *
 * Chip power down counter, counter decreasing if value is not 0, power down of chip happens on counter value is 1
 */
#define BPOR_POR_CONTROL_COUNTER_MASK (0xFFFFU)
#define BPOR_POR_CONTROL_COUNTER_SHIFT (0U)
#define BPOR_POR_CONTROL_COUNTER_SET(x) (((uint32_t)(x) << BPOR_POR_CONTROL_COUNTER_SHIFT) & BPOR_POR_CONTROL_COUNTER_MASK)
#define BPOR_POR_CONTROL_COUNTER_GET(x) (((uint32_t)(x) & BPOR_POR_CONTROL_COUNTER_MASK) >> BPOR_POR_CONTROL_COUNTER_SHIFT)




#endif /* HPM_BPOR_H */
