/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     GuEe-GUI     The first version
 */

#ifndef __PSCI_H__
#define __PSCI_H__

#include <stdint.h>

/*
 * Non-Confidential PSCI 1.0 release (30 January 2015), and errata fix for PSCI 0.2, unsupport PSCI 0.1
 */
#define PSCI_VER_0_2                        0x00000002

#define PSCI_METHOD_SMC                     3
#define PSCI_METHOD_HVC                     2

/* PSCI 0.2 interface */
#define PSCI_0_2_FN_BASE                    0x84000000
#define PSCI_0_2_FN(n)                      (PSCI_0_2_FN_BASE + (n))
#define PSCI_0_2_FN_END                     0x8400001F

#define PSCI_0_2_FN64_BASE                  0xC4000000
#define PSCI_0_2_FN64(n)                    (PSCI_0_2_FN64_BASE + (n))
#define PSCI_0_2_FN64_END                   0xC400001F

#define PSCI_0_2_FN_PSCI_VERSION            PSCI_0_2_FN(0)
#define PSCI_0_2_FN_CPU_SUSPEND             PSCI_0_2_FN(1)
#define PSCI_0_2_FN_CPU_OFF                 PSCI_0_2_FN(2)
#define PSCI_0_2_FN_CPU_ON                  PSCI_0_2_FN(3)
#define PSCI_0_2_FN_AFFINITY_INFO           PSCI_0_2_FN(4)
#define PSCI_0_2_FN_MIGRATE                 PSCI_0_2_FN(5)
#define PSCI_0_2_FN_MIGRATE_INFO_TYPE       PSCI_0_2_FN(6)
#define PSCI_0_2_FN_MIGRATE_INFO_UP_CPU     PSCI_0_2_FN(7)
#define PSCI_0_2_FN_SYSTEM_OFF              PSCI_0_2_FN(8)
#define PSCI_0_2_FN_SYSTEM_RESET            PSCI_0_2_FN(9)

#define PSCI_0_2_FN64_CPU_SUSPEND           PSCI_0_2_FN64(1)
#define PSCI_0_2_FN64_CPU_ON                PSCI_0_2_FN64(3)
#define PSCI_0_2_FN64_AFFINITY_INFO         PSCI_0_2_FN64(4)
#define PSCI_0_2_FN64_MIGRATE               PSCI_0_2_FN64(5)
#define PSCI_0_2_FN64_MIGRATE_INFO_UP_CPU   PSCI_0_2_FN64(7)

/* PSCI 1.0 interface */
#define PSCI_1_0_FN_PSCI_FEATURES           PSCI_0_2_FN(10)
#define PSCI_1_0_FN_CPU_FREEZE              PSCI_0_2_FN(11)
#define PSCI_1_0_FN_CPU_DEFAULT_SUSPEND     PSCI_0_2_FN(12)
#define PSCI_1_0_FN_NODE_HW_STATE           PSCI_0_2_FN(13)
#define PSCI_1_0_FN_SYSTEM_SUSPEND          PSCI_0_2_FN(14)
#define PSCI_1_0_FN_SET_SUSPEND_MODE        PSCI_0_2_FN(15)
#define PSCI_1_0_FN_STAT_RESIDENCY          PSCI_0_2_FN(16)
#define PSCI_1_0_FN_STAT_COUNT              PSCI_0_2_FN(17)

#define PSCI_1_0_FN64_CPU_DEFAULT_SUSPEND   PSCI_0_2_FN64(12)
#define PSCI_1_0_FN64_NODE_HW_STATE         PSCI_0_2_FN64(13)
#define PSCI_1_0_FN64_SYSTEM_SUSPEND        PSCI_0_2_FN64(14)
#define PSCI_1_0_FN64_STAT_RESIDENCY        PSCI_0_2_FN64(16)
#define PSCI_1_0_FN64_STAT_COUNT            PSCI_0_2_FN64(17)

/* 1KB stack per core */
#define PSCI_STACK_SHIFT                    10
#define PSCI_STACK_SIZE                     (1 << PSCI_STACK_SHIFT)

/* PSCI affinity level state returned by AFFINITY_INFO */
#define PSCI_AFFINITY_LEVEL_ON              0
#define PSCI_AFFINITY_LEVEL_OFF             1
#define PSCI_AFFINITY_LEVEL_ON_PENDING      2

/*
 * PSCI power state
 *  power_level:
 *      Level 0: cores
 *      Level 1: clusters
 *      Level 2: system
 *  state_type:
 *      value 0: standby or retention state
 *      value 1: powerdown state(entry and context_id is valid)
 *  state_id:
 *      StateID
 */
#define PSCI_POWER_STATE(power_level, state_type, state_id) \
( \
    ((power_level) << 24) | \
    ((state_type) << 16)  | \
    ((state_id) << 24) \
)

/*
 * For system, cluster, core
 *  0: run
 *  1: standby(only core)
 *  2: retention
 *  3: powerdown
 */
#define PSCI_POWER_STATE_ID(state_id_power_level, system, cluster, core) \
( \
    ((state_id_power_level) << 12) | \
    ((system) << 8)  | \
    ((cluster) << 4) | \
    (core) \
)

#define PSCI_RET_SUCCESS                    0
#define PSCI_RET_NOT_SUPPORTED              (-1)
#define PSCI_RET_INVALID_PARAMETERS         (-2)
#define PSCI_RET_DENIED                     (-3)
#define PSCI_RET_ALREADY_ON                 (-4)
#define PSCI_RET_ON_PENDING                 (-5)
#define PSCI_RET_INTERNAL_FAILURE           (-6)
#define PSCI_RET_NOT_PRESENT                (-7)
#define PSCI_RET_DISABLED                   (-8)
#define PSCI_RET_INVALID_ADDRESS            (-9)

void arm_psci_init(uint64_t method, uint64_t *platform_shutdown_args, uint64_t *platform_reboot_args);

uint32_t arm_psci_get_version();
uint32_t arm_psci_get_affinity_info(uint64_t target_affinity, uint64_t lowest_affinity_level);
uint32_t arm_psci_get_feature(uint32_t psci_func_id);

uint32_t arm_psci_cpu_off(uint64_t state);
uint32_t arm_psci_cpu_on(uint64_t mpid, uint64_t entry);
uint32_t arm_psci_cpu_suspend(uint32_t power_state, uint64_t entry);

void arm_psci_system_off();
void arm_psci_system_reboot();

#endif  /*__PSCI_H__*/
