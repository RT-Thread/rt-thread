/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PSEC_DRV_H
#define HPM_PSEC_DRV_H
#include "hpm_common.h"
#include "hpm_psec_regs.h"

typedef enum psec_lifecycle {
    psec_lifecycle_unknown = 1 << 0,
    psec_lifecycle_create = 1 << 1,
    psec_lifecycle_nonsecucre = 1 << 2,
    psec_lifecycle_secucre = 1 << 3,
    psec_lifecycle_return = 1 << 4,
    psec_lifecycle_no_return = 1 << 5,
    psec_lifecycle_scribe = 1 << 6,
    psec_lifecycle_debate = 1 << 7,
} psec_lifecycle_t;

typedef enum batt_sec_state {
    batt_sec_state_ins = 0,
    batt_sec_state_secure = 1,
    batt_sec_state_non_secure = 2,
    batt_sec_state_fail = 3,
} batt_sec_state_t;

typedef enum psec_state {
    psec_state_ins = 0,
    psec_state_secure = 1,
    psec_state_non_secure = 2,
    psec_state_fail = 3,
} psec_state_t;

enum {
    status_psec_switch_state_not_allowed = MAKE_STATUS(status_group_psec, 1),
};

#define PSEC_PSECURE_STATE_MASK \
    (0xFU << PSEC_SECURE_STATE_PMIC_INS_SHIFT)
#define PSEC_BATT_SECURE_STATE_MASK \
    (0xFU << PSEC_SECURE_STATE_BATT_INS_SHIFT)

#ifdef __cplusplus
extern "C" {
#endif

static inline psec_lifecycle_t psec_get_pmic_lifecycle(PSEC_Type *ptr)
{
    return (psec_lifecycle_t) PSEC_LIFECYCLE_LIFECYCLE_GET(ptr->LIFECYCLE);
}

static inline hpm_stat_t psec_switch_pmic_state(PSEC_Type *ptr, psec_state_t state)
{
    if (state == psec_state_secure) {
        if (!PSEC_SECURE_STATE_ALLOW_SEC_GET(ptr->SECURE_STATE)) {
            return status_psec_switch_state_not_allowed;
        }
    } else if (state == psec_state_non_secure) {
        if (!PSEC_SECURE_STATE_ALLOW_NSC_GET(ptr->SECURE_STATE)) {
            return status_psec_switch_state_not_allowed;
        }
    }
    ptr->SECURE_STATE = (ptr->SECURE_STATE & ~PSEC_PSECURE_STATE_MASK)
                    | (1U << (PSEC_SECURE_STATE_PMIC_INS_SHIFT + state));
    return status_success;
}

static inline void psec_allow_psecure_state_restart(PSEC_Type *ptr, bool allow)
{
    ptr->SECURE_STATE_CONFIG = (ptr->SECURE_STATE_CONFIG
            & ~PSEC_SECURE_STATE_CONFIG_ALLOW_RESTART_MASK)
        | PSEC_SECURE_STATE_CONFIG_ALLOW_RESTART_SET(allow);
}

static inline void psec_lock_psecure_state_restart(PSEC_Type *ptr, bool lock)
{
    ptr->SECURE_STATE_CONFIG = (ptr->SECURE_STATE_CONFIG
            & ~PSEC_SECURE_STATE_CONFIG_LOCK_MASK)
        | PSEC_SECURE_STATE_CONFIG_LOCK_SET(lock);
}

static inline void psec_pmic_rom_secrets_present(PSEC_Type *ptr, bool presented)
{
    ptr->SECURE_STATE_CONFIG = (ptr->SECURE_STATE_CONFIG
            & ~PSEC_SECURE_STATE_CONFIG_ROM_SECRETS_MASK)
        | PSEC_SECURE_STATE_CONFIG_ROM_SECRETS_SET(presented);
}

static inline void psec_psec_secure_state_config(PSEC_Type *ptr,
                                                        bool rom_secrets_presented,
                                                        bool allow_secure_state_restart,
                                                        bool lock_secure_state_restart)
{
    ptr->SECURE_STATE_CONFIG = PSEC_SECURE_STATE_CONFIG_ROM_SECRETS_SET(rom_secrets_presented)
                | PSEC_SECURE_STATE_CONFIG_ALLOW_RESTART_SET(allow_secure_state_restart)
                | PSEC_SECURE_STATE_CONFIG_LOCK_SET(lock_secure_state_restart);
}

static inline void psec_pmic_non_secure_violation_config(PSEC_Type *ptr,
                                                        uint32_t violation_setting,
                                                        bool lock)
{
    ptr->VIOLATION_CONFIG = (ptr->VIOLATION_CONFIG
            & ~(PSEC_VIOLATION_CONFIG_LOCK_NSC_MASK
                | PSEC_VIOLATION_CONFIG_NSC_VIO_CFG_MASK))
        | PSEC_VIOLATION_CONFIG_LOCK_NSC_SET(lock)
        | PSEC_VIOLATION_CONFIG_NSC_VIO_CFG_SET(violation_setting);
}

static inline void psec_psecure_violation_config(PSEC_Type *ptr,
                                                        uint32_t violation_setting,
                                                        bool lock)
{
    ptr->VIOLATION_CONFIG = (ptr->VIOLATION_CONFIG
            & ~(PSEC_VIOLATION_CONFIG_LOCK_SEC_MASK
                | PSEC_VIOLATION_CONFIG_SEC_VIO_CFG_MASK))
        | PSEC_VIOLATION_CONFIG_LOCK_SEC_SET(lock)
        | PSEC_VIOLATION_CONFIG_SEC_VIO_CFG_SET(violation_setting);
}

static inline void psec_pmic_non_secure_escalate_config(PSEC_Type *ptr,
                                                        uint32_t violation_setting,
                                                        bool lock)
{
    ptr->ESCALATE_CONFIG = (ptr->ESCALATE_CONFIG
            & ~(PSEC_ESCALATE_CONFIG_LOCK_NSC_MASK
                | PSEC_ESCALATE_CONFIG_NSC_VIO_CFG_MASK))
        | PSEC_ESCALATE_CONFIG_LOCK_NSC_SET(lock)
        | PSEC_ESCALATE_CONFIG_NSC_VIO_CFG_SET(violation_setting);
}

static inline void psec_psecure_escalate_config(PSEC_Type *ptr,
                                                        uint32_t violation_setting,
                                                        bool lock)
{
    ptr->ESCALATE_CONFIG = (ptr->ESCALATE_CONFIG
            & ~(PSEC_ESCALATE_CONFIG_LOCK_SEC_MASK
                | PSEC_ESCALATE_CONFIG_SEC_VIO_CFG_MASK))
        | PSEC_ESCALATE_CONFIG_LOCK_SEC_SET(lock)
        | PSEC_ESCALATE_CONFIG_SEC_VIO_CFG_SET(violation_setting);
}

static inline uint32_t psec_get_pmic_status(PSEC_Type *ptr)
{
    return ptr->EVENT;
}

static inline psec_lifecycle_t psec_get_batt_lifecycle(PSEC_Type *ptr)
{
    return (psec_lifecycle_t) PSEC_LIFECYCLE_LIFECYCLE_GET(ptr->LIFECYCLE);
}

static inline hpm_stat_t psec_switch_batt_state(PSEC_Type *ptr, batt_sec_state_t state)
{
    if (state == batt_sec_state_secure) {
        if (!PSEC_SECURE_STATE_ALLOW_SEC_GET(ptr->SECURE_STATE)) {
            return status_psec_switch_state_not_allowed;
        }
    } else if (state == batt_sec_state_non_secure) {
        if (!PSEC_SECURE_STATE_ALLOW_NSC_GET(ptr->SECURE_STATE)) {
            return status_psec_switch_state_not_allowed;
        }
    }
    ptr->SECURE_STATE = (ptr->SECURE_STATE & ~PSEC_BATT_SECURE_STATE_MASK)
                    | (1U << (PSEC_SECURE_STATE_BATT_INS_SHIFT + state));
    return status_success;
}

static inline void psec_allow_batt_secure_state_restart(PSEC_Type *ptr, bool allow)
{
    ptr->SECURE_STATE_CONFIG = (ptr->SECURE_STATE_CONFIG
            & ~PSEC_SECURE_STATE_CONFIG_ALLOW_RESTART_MASK)
        | PSEC_SECURE_STATE_CONFIG_ALLOW_RESTART_SET(allow);
}

static inline void psec_lock_batt_secure_state_restart(PSEC_Type *ptr, bool lock)
{
    ptr->SECURE_STATE_CONFIG = (ptr->SECURE_STATE_CONFIG
            & ~PSEC_SECURE_STATE_CONFIG_LOCK_MASK)
        | PSEC_SECURE_STATE_CONFIG_LOCK_SET(lock);
}

static inline void psec_batt_rom_secrets_present(PSEC_Type *ptr, bool presented)
{
    ptr->SECURE_STATE_CONFIG = (ptr->SECURE_STATE_CONFIG
            & ~PSEC_SECURE_STATE_CONFIG_ROM_SECRETS_MASK)
        | PSEC_SECURE_STATE_CONFIG_ROM_SECRETS_SET(presented);
}

static inline void psec_batt_set_secure_state_config(PSEC_Type *ptr,
                                                        bool rom_secrets_presented,
                                                        bool allow_secure_state_restart,
                                                        bool lock_secure_state_restart)
{
    ptr->SECURE_STATE_CONFIG = PSEC_SECURE_STATE_CONFIG_ROM_SECRETS_SET(rom_secrets_presented)
                | PSEC_SECURE_STATE_CONFIG_ALLOW_RESTART_SET(allow_secure_state_restart)
                | PSEC_SECURE_STATE_CONFIG_LOCK_SET(lock_secure_state_restart);
}

static inline void psec_batt_non_secure_violation_config(PSEC_Type *ptr,
                                                        uint32_t violation_setting,
                                                        bool lock)
{
    ptr->VIOLATION_CONFIG = (ptr->VIOLATION_CONFIG
            & ~(PSEC_VIOLATION_CONFIG_LOCK_NSC_MASK
                | PSEC_VIOLATION_CONFIG_NSC_VIO_CFG_MASK))
        | PSEC_VIOLATION_CONFIG_LOCK_NSC_SET(lock)
        | PSEC_VIOLATION_CONFIG_NSC_VIO_CFG_SET(violation_setting);
}

static inline void psec_batt_secure_violation_config(PSEC_Type *ptr,
                                                        uint32_t violation_setting,
                                                        bool lock)
{
    ptr->VIOLATION_CONFIG = (ptr->VIOLATION_CONFIG
            & ~(PSEC_VIOLATION_CONFIG_LOCK_SEC_MASK
                | PSEC_VIOLATION_CONFIG_SEC_VIO_CFG_MASK))
        | PSEC_VIOLATION_CONFIG_LOCK_SEC_SET(lock)
        | PSEC_VIOLATION_CONFIG_SEC_VIO_CFG_SET(violation_setting);
}

static inline void psec_batt_non_secure_escalate_config(PSEC_Type *ptr,
                                                        uint32_t violation_setting,
                                                        bool lock)
{
    ptr->ESCALATE_CONFIG = (ptr->ESCALATE_CONFIG
            & ~(PSEC_ESCALATE_CONFIG_LOCK_NSC_MASK
                | PSEC_ESCALATE_CONFIG_NSC_VIO_CFG_MASK))
        | PSEC_ESCALATE_CONFIG_LOCK_NSC_SET(lock)
        | PSEC_ESCALATE_CONFIG_NSC_VIO_CFG_SET(violation_setting);
}

static inline void psec_batt_secure_escalate_config(PSEC_Type *ptr,
                                                        uint32_t violation_setting,
                                                        bool lock)
{
    ptr->ESCALATE_CONFIG = (ptr->ESCALATE_CONFIG
            & ~(PSEC_ESCALATE_CONFIG_LOCK_SEC_MASK
                | PSEC_ESCALATE_CONFIG_SEC_VIO_CFG_MASK))
        | PSEC_ESCALATE_CONFIG_LOCK_SEC_SET(lock)
        | PSEC_ESCALATE_CONFIG_SEC_VIO_CFG_SET(violation_setting);
}

static inline uint32_t psec_get_batt_status(PSEC_Type *ptr)
{
    return ptr->EVENT;
}
#ifdef __cplusplus
}
#endif

#endif /* HPM_PSEC_DRV_H */

