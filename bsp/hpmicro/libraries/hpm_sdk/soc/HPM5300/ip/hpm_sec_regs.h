/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SEC_H
#define HPM_SEC_H

typedef struct {
    __RW uint32_t SECURE_STATE;                /* 0x0: Secure state */
    __RW uint32_t SECURE_STATE_CONFIG;         /* 0x4: secure state configuration */
    __RW uint32_t VIOLATION_CONFIG;            /* 0x8: Security violation config */
    __RW uint32_t ESCALATE_CONFIG;             /* 0xC: Escalate behavior on security event */
    __R  uint32_t EVENT;                       /* 0x10: Event and escalate status */
    __R  uint32_t LIFECYCLE;                   /* 0x14: Lifecycle */
} SEC_Type;


/* Bitfield definition for register: SECURE_STATE */
/*
 * ALLOW_NSC (RO)
 *
 * Non-secure state allow
 * 0: system is not healthy to enter non-secure state, request to enter non-secure state will cause a fail state
 * 1: system is healthy to enter non-secure state
 */
#define SEC_SECURE_STATE_ALLOW_NSC_MASK (0x20000UL)
#define SEC_SECURE_STATE_ALLOW_NSC_SHIFT (17U)
#define SEC_SECURE_STATE_ALLOW_NSC_GET(x) (((uint32_t)(x) & SEC_SECURE_STATE_ALLOW_NSC_MASK) >> SEC_SECURE_STATE_ALLOW_NSC_SHIFT)

/*
 * ALLOW_SEC (RO)
 *
 * Secure state allow
 * 0: system is not healthy to enter secure state, request to enter non-secure state will cause a fail state
 * 1: system is healthy to enter secure state
 */
#define SEC_SECURE_STATE_ALLOW_SEC_MASK (0x10000UL)
#define SEC_SECURE_STATE_ALLOW_SEC_SHIFT (16U)
#define SEC_SECURE_STATE_ALLOW_SEC_GET(x) (((uint32_t)(x) & SEC_SECURE_STATE_ALLOW_SEC_MASK) >> SEC_SECURE_STATE_ALLOW_SEC_SHIFT)

/*
 * PMIC_FAIL (RW)
 *
 * PMIC secure state one hot indicator
 * 0: secure state is not in fail state
 * 1: secure state is in fail state
 */
#define SEC_SECURE_STATE_PMIC_FAIL_MASK (0x80U)
#define SEC_SECURE_STATE_PMIC_FAIL_SHIFT (7U)
#define SEC_SECURE_STATE_PMIC_FAIL_SET(x) (((uint32_t)(x) << SEC_SECURE_STATE_PMIC_FAIL_SHIFT) & SEC_SECURE_STATE_PMIC_FAIL_MASK)
#define SEC_SECURE_STATE_PMIC_FAIL_GET(x) (((uint32_t)(x) & SEC_SECURE_STATE_PMIC_FAIL_MASK) >> SEC_SECURE_STATE_PMIC_FAIL_SHIFT)

/*
 * PMIC_NSC (RW)
 *
 * PMIC secure state one hot indicator
 * 0: secure state is not in non-secure state
 * 1: secure state is in non-secure state
 */
#define SEC_SECURE_STATE_PMIC_NSC_MASK (0x40U)
#define SEC_SECURE_STATE_PMIC_NSC_SHIFT (6U)
#define SEC_SECURE_STATE_PMIC_NSC_SET(x) (((uint32_t)(x) << SEC_SECURE_STATE_PMIC_NSC_SHIFT) & SEC_SECURE_STATE_PMIC_NSC_MASK)
#define SEC_SECURE_STATE_PMIC_NSC_GET(x) (((uint32_t)(x) & SEC_SECURE_STATE_PMIC_NSC_MASK) >> SEC_SECURE_STATE_PMIC_NSC_SHIFT)

/*
 * PMIC_SEC (RW)
 *
 * PMIC secure state one hot indicator
 * 0: secure state is not in secure state
 * 1: secure state is in secure state
 */
#define SEC_SECURE_STATE_PMIC_SEC_MASK (0x20U)
#define SEC_SECURE_STATE_PMIC_SEC_SHIFT (5U)
#define SEC_SECURE_STATE_PMIC_SEC_SET(x) (((uint32_t)(x) << SEC_SECURE_STATE_PMIC_SEC_SHIFT) & SEC_SECURE_STATE_PMIC_SEC_MASK)
#define SEC_SECURE_STATE_PMIC_SEC_GET(x) (((uint32_t)(x) & SEC_SECURE_STATE_PMIC_SEC_MASK) >> SEC_SECURE_STATE_PMIC_SEC_SHIFT)

/*
 * PMIC_INS (RW)
 *
 * PMIC secure state one hot indicator
 * 0: secure state is not in inspect state
 * 1: secure state is in inspect state
 */
#define SEC_SECURE_STATE_PMIC_INS_MASK (0x10U)
#define SEC_SECURE_STATE_PMIC_INS_SHIFT (4U)
#define SEC_SECURE_STATE_PMIC_INS_SET(x) (((uint32_t)(x) << SEC_SECURE_STATE_PMIC_INS_SHIFT) & SEC_SECURE_STATE_PMIC_INS_MASK)
#define SEC_SECURE_STATE_PMIC_INS_GET(x) (((uint32_t)(x) & SEC_SECURE_STATE_PMIC_INS_MASK) >> SEC_SECURE_STATE_PMIC_INS_SHIFT)

/* Bitfield definition for register: SECURE_STATE_CONFIG */
/*
 * LOCK (RW)
 *
 * Lock bit of allow restart setting, once locked, lock bit itself and configuration register will keep value until next reset
 * 0: not locked, register can be modified
 * 1: register locked, write access to the register is ignored
 */
#define SEC_SECURE_STATE_CONFIG_LOCK_MASK (0x8U)
#define SEC_SECURE_STATE_CONFIG_LOCK_SHIFT (3U)
#define SEC_SECURE_STATE_CONFIG_LOCK_SET(x) (((uint32_t)(x) << SEC_SECURE_STATE_CONFIG_LOCK_SHIFT) & SEC_SECURE_STATE_CONFIG_LOCK_MASK)
#define SEC_SECURE_STATE_CONFIG_LOCK_GET(x) (((uint32_t)(x) & SEC_SECURE_STATE_CONFIG_LOCK_MASK) >> SEC_SECURE_STATE_CONFIG_LOCK_SHIFT)

/*
 * ALLOW_RESTART (RW)
 *
 * allow secure state restart from fail state
 * 0: restart is not allowed, only hardware reset can recover secure state
 * 1: software is allowed to switch to inspect state from fail state
 */
#define SEC_SECURE_STATE_CONFIG_ALLOW_RESTART_MASK (0x1U)
#define SEC_SECURE_STATE_CONFIG_ALLOW_RESTART_SHIFT (0U)
#define SEC_SECURE_STATE_CONFIG_ALLOW_RESTART_SET(x) (((uint32_t)(x) << SEC_SECURE_STATE_CONFIG_ALLOW_RESTART_SHIFT) & SEC_SECURE_STATE_CONFIG_ALLOW_RESTART_MASK)
#define SEC_SECURE_STATE_CONFIG_ALLOW_RESTART_GET(x) (((uint32_t)(x) & SEC_SECURE_STATE_CONFIG_ALLOW_RESTART_MASK) >> SEC_SECURE_STATE_CONFIG_ALLOW_RESTART_SHIFT)

/* Bitfield definition for register: VIOLATION_CONFIG */
/*
 * LOCK_NSC (RW)
 *
 * Lock bit non-secure violation setting, once locked, lock bit itself and configuration will keep value until next reset
 * 0: not locked, configuration can be modified
 * 1: register locked, write access to the configuration is ignored
 */
#define SEC_VIOLATION_CONFIG_LOCK_NSC_MASK (0x80000000UL)
#define SEC_VIOLATION_CONFIG_LOCK_NSC_SHIFT (31U)
#define SEC_VIOLATION_CONFIG_LOCK_NSC_SET(x) (((uint32_t)(x) << SEC_VIOLATION_CONFIG_LOCK_NSC_SHIFT) & SEC_VIOLATION_CONFIG_LOCK_NSC_MASK)
#define SEC_VIOLATION_CONFIG_LOCK_NSC_GET(x) (((uint32_t)(x) & SEC_VIOLATION_CONFIG_LOCK_NSC_MASK) >> SEC_VIOLATION_CONFIG_LOCK_NSC_SHIFT)

/*
 * NSC_VIO_CFG (RW)
 *
 * configuration of non-secure state violations, each bit represents one security event
 * 0: event is not a security violation
 * 1: event is a security violation
 */
#define SEC_VIOLATION_CONFIG_NSC_VIO_CFG_MASK (0x7FFF0000UL)
#define SEC_VIOLATION_CONFIG_NSC_VIO_CFG_SHIFT (16U)
#define SEC_VIOLATION_CONFIG_NSC_VIO_CFG_SET(x) (((uint32_t)(x) << SEC_VIOLATION_CONFIG_NSC_VIO_CFG_SHIFT) & SEC_VIOLATION_CONFIG_NSC_VIO_CFG_MASK)
#define SEC_VIOLATION_CONFIG_NSC_VIO_CFG_GET(x) (((uint32_t)(x) & SEC_VIOLATION_CONFIG_NSC_VIO_CFG_MASK) >> SEC_VIOLATION_CONFIG_NSC_VIO_CFG_SHIFT)

/*
 * LOCK_SEC (RW)
 *
 * Lock bit secure violation setting, once locked, lock bit itself and configuration will keep value until next reset
 * 0: not locked, configuration can be modified
 * 1: register locked, write access to the configuration is ignored
 */
#define SEC_VIOLATION_CONFIG_LOCK_SEC_MASK (0x8000U)
#define SEC_VIOLATION_CONFIG_LOCK_SEC_SHIFT (15U)
#define SEC_VIOLATION_CONFIG_LOCK_SEC_SET(x) (((uint32_t)(x) << SEC_VIOLATION_CONFIG_LOCK_SEC_SHIFT) & SEC_VIOLATION_CONFIG_LOCK_SEC_MASK)
#define SEC_VIOLATION_CONFIG_LOCK_SEC_GET(x) (((uint32_t)(x) & SEC_VIOLATION_CONFIG_LOCK_SEC_MASK) >> SEC_VIOLATION_CONFIG_LOCK_SEC_SHIFT)

/*
 * SEC_VIO_CFG (RW)
 *
 * configuration of secure state violations, each bit represents one security event
 * 0: event is not a security violation
 * 1: event is a security violation
 */
#define SEC_VIOLATION_CONFIG_SEC_VIO_CFG_MASK (0x7FFFU)
#define SEC_VIOLATION_CONFIG_SEC_VIO_CFG_SHIFT (0U)
#define SEC_VIOLATION_CONFIG_SEC_VIO_CFG_SET(x) (((uint32_t)(x) << SEC_VIOLATION_CONFIG_SEC_VIO_CFG_SHIFT) & SEC_VIOLATION_CONFIG_SEC_VIO_CFG_MASK)
#define SEC_VIOLATION_CONFIG_SEC_VIO_CFG_GET(x) (((uint32_t)(x) & SEC_VIOLATION_CONFIG_SEC_VIO_CFG_MASK) >> SEC_VIOLATION_CONFIG_SEC_VIO_CFG_SHIFT)

/* Bitfield definition for register: ESCALATE_CONFIG */
/*
 * LOCK_NSC (RW)
 *
 * Lock bit non-secure escalate setting, once locked, lock bit itself and configuration will keep value until next reset
 * 0: not locked, configuration can be modified
 * 1: register locked, write access to the configuration is ignored
 */
#define SEC_ESCALATE_CONFIG_LOCK_NSC_MASK (0x80000000UL)
#define SEC_ESCALATE_CONFIG_LOCK_NSC_SHIFT (31U)
#define SEC_ESCALATE_CONFIG_LOCK_NSC_SET(x) (((uint32_t)(x) << SEC_ESCALATE_CONFIG_LOCK_NSC_SHIFT) & SEC_ESCALATE_CONFIG_LOCK_NSC_MASK)
#define SEC_ESCALATE_CONFIG_LOCK_NSC_GET(x) (((uint32_t)(x) & SEC_ESCALATE_CONFIG_LOCK_NSC_MASK) >> SEC_ESCALATE_CONFIG_LOCK_NSC_SHIFT)

/*
 * NSC_VIO_CFG (RW)
 *
 * configuration of non-secure state escalates, each bit represents one security event
 * 0: event is not a security escalate
 * 1: event is a security escalate
 */
#define SEC_ESCALATE_CONFIG_NSC_VIO_CFG_MASK (0x7FFF0000UL)
#define SEC_ESCALATE_CONFIG_NSC_VIO_CFG_SHIFT (16U)
#define SEC_ESCALATE_CONFIG_NSC_VIO_CFG_SET(x) (((uint32_t)(x) << SEC_ESCALATE_CONFIG_NSC_VIO_CFG_SHIFT) & SEC_ESCALATE_CONFIG_NSC_VIO_CFG_MASK)
#define SEC_ESCALATE_CONFIG_NSC_VIO_CFG_GET(x) (((uint32_t)(x) & SEC_ESCALATE_CONFIG_NSC_VIO_CFG_MASK) >> SEC_ESCALATE_CONFIG_NSC_VIO_CFG_SHIFT)

/*
 * LOCK_SEC (RW)
 *
 * Lock bit secure escalate setting, once locked, lock bit itself and configuration will keep value until next reset
 * 0: not locked, configuration can be modified
 * 1: register locked, write access to the configuration is ignored
 */
#define SEC_ESCALATE_CONFIG_LOCK_SEC_MASK (0x8000U)
#define SEC_ESCALATE_CONFIG_LOCK_SEC_SHIFT (15U)
#define SEC_ESCALATE_CONFIG_LOCK_SEC_SET(x) (((uint32_t)(x) << SEC_ESCALATE_CONFIG_LOCK_SEC_SHIFT) & SEC_ESCALATE_CONFIG_LOCK_SEC_MASK)
#define SEC_ESCALATE_CONFIG_LOCK_SEC_GET(x) (((uint32_t)(x) & SEC_ESCALATE_CONFIG_LOCK_SEC_MASK) >> SEC_ESCALATE_CONFIG_LOCK_SEC_SHIFT)

/*
 * SEC_VIO_CFG (RW)
 *
 * configuration of secure state escalates, each bit represents one security event
 * 0: event is not a security escalate
 * 1: event is a security escalate
 */
#define SEC_ESCALATE_CONFIG_SEC_VIO_CFG_MASK (0x7FFFU)
#define SEC_ESCALATE_CONFIG_SEC_VIO_CFG_SHIFT (0U)
#define SEC_ESCALATE_CONFIG_SEC_VIO_CFG_SET(x) (((uint32_t)(x) << SEC_ESCALATE_CONFIG_SEC_VIO_CFG_SHIFT) & SEC_ESCALATE_CONFIG_SEC_VIO_CFG_MASK)
#define SEC_ESCALATE_CONFIG_SEC_VIO_CFG_GET(x) (((uint32_t)(x) & SEC_ESCALATE_CONFIG_SEC_VIO_CFG_MASK) >> SEC_ESCALATE_CONFIG_SEC_VIO_CFG_SHIFT)

/* Bitfield definition for register: EVENT */
/*
 * EVENT (RO)
 *
 * local event statue, each bit represents one security event
 */
#define SEC_EVENT_EVENT_MASK (0xFFFF0000UL)
#define SEC_EVENT_EVENT_SHIFT (16U)
#define SEC_EVENT_EVENT_GET(x) (((uint32_t)(x) & SEC_EVENT_EVENT_MASK) >> SEC_EVENT_EVENT_SHIFT)

/*
 * PMIC_ESC_NSC (RO)
 *
 * PMIC is escalating non-secure event
 */
#define SEC_EVENT_PMIC_ESC_NSC_MASK (0x8U)
#define SEC_EVENT_PMIC_ESC_NSC_SHIFT (3U)
#define SEC_EVENT_PMIC_ESC_NSC_GET(x) (((uint32_t)(x) & SEC_EVENT_PMIC_ESC_NSC_MASK) >> SEC_EVENT_PMIC_ESC_NSC_SHIFT)

/*
 * PMIC_ESC_SEC (RO)
 *
 * PMIC is escalting secure event
 */
#define SEC_EVENT_PMIC_ESC_SEC_MASK (0x4U)
#define SEC_EVENT_PMIC_ESC_SEC_SHIFT (2U)
#define SEC_EVENT_PMIC_ESC_SEC_GET(x) (((uint32_t)(x) & SEC_EVENT_PMIC_ESC_SEC_MASK) >> SEC_EVENT_PMIC_ESC_SEC_SHIFT)

/* Bitfield definition for register: LIFECYCLE */
/*
 * LIFECYCLE (RO)
 *
 * lifecycle status,
 * bit7: lifecycle_debate,
 * bit6: lifecycle_scribe,
 * bit5: lifecycle_no_ret,
 * bit4: lifecycle_return,
 * bit3: lifecycle_secure,
 * bit2: lifecycle_nonsec,
 * bit1: lifecycle_create,
 * bit0: lifecycle_unknow
 */
#define SEC_LIFECYCLE_LIFECYCLE_MASK (0xFFU)
#define SEC_LIFECYCLE_LIFECYCLE_SHIFT (0U)
#define SEC_LIFECYCLE_LIFECYCLE_GET(x) (((uint32_t)(x) & SEC_LIFECYCLE_LIFECYCLE_MASK) >> SEC_LIFECYCLE_LIFECYCLE_SHIFT)




#endif /* HPM_SEC_H */
