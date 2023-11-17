/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     GuEe-GUI     The first version
 */

#ifndef __PSCI_H__
#define __PSCI_H__

#include <rtdef.h>

/*
 * Non-Confidential PSCI 1.0 release (30 January 2015), and errata fix for PSCI 0.2, unsupport PSCI 0.1
 */

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
#define PSCI_1_1_FN_SYSTEM_RESET2           PSCI_0_2_FN(18)

#define PSCI_1_0_FN64_CPU_DEFAULT_SUSPEND   PSCI_0_2_FN64(12)
#define PSCI_1_0_FN64_NODE_HW_STATE         PSCI_0_2_FN64(13)
#define PSCI_1_0_FN64_SYSTEM_SUSPEND        PSCI_0_2_FN64(14)
#define PSCI_1_0_FN64_STAT_RESIDENCY        PSCI_0_2_FN64(16)
#define PSCI_1_0_FN64_STAT_COUNT            PSCI_0_2_FN64(17)
#define PSCI_1_1_FN64_SYSTEM_RESET2         PSCI_0_2_FN64(18)

/* PSCI version decoding (independent of PSCI version) */
#define PSCI_VERSION_MAJOR_SHIFT            16
#define PSCI_VERSION_MINOR_MASK             ((1U << PSCI_VERSION_MAJOR_SHIFT) - 1)
#define PSCI_VERSION_MAJOR_MASK             ~PSCI_VERSION_MINOR_MASK
#define PSCI_VERSION_MAJOR(version)         (((version) & PSCI_VERSION_MAJOR_MASK) >> PSCI_VERSION_MAJOR_SHIFT)
#define PSCI_VERSION_MINOR(version)         ((version) & PSCI_VERSION_MINOR_MASK)
#define PSCI_VERSION(major, min)            ((((major) << PSCI_VERSION_MAJOR_SHIFT) & PSCI_VERSION_MAJOR_MASK) | \
                                                    ((min) & PSCI_VERSION_MINOR_MASK))

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
#define PSCI_POWER_STATE_LEVEL_CORES        0
#define PSCI_POWER_STATE_LEVEL_CLUSTERS     1
#define PSCI_POWER_STATE_LEVEL_SYSTEM       2

#define PSCI_POWER_STATE_TYPE_STANDBY       0
#define PSCI_POWER_STATE_TYPE_POWER_DOWN    1

#define PSCI_POWER_LEVEL_SHIFT              24
#define PSCI_POWER_STATE_TYPE_SHIFT         16
#define PSCI_POWER_STATE_ID_SHIFT           0
#define PSCI_POWER_STATE(power_level, state_type, state_id) \
( \
    ((power_level) << PSCI_POWER_LEVEL_SHIFT) | \
    ((state_type) << PSCI_POWER_STATE_TYPE_SHIFT)  | \
    ((state_id) << PSCI_POWER_STATE_ID_SHIFT) \
)
#define PSCI_POWER_LEVEL_VAL(state)         (((state) >> PSCI_POWER_LEVEL_SHIFT) & 0x3)
#define PSCI_POWER_STATE_TYPE_VAL(state)    (((state) >> PSCI_POWER_STATE_TYPE_SHIFT) & 0x1)
#define PSCI_POWER_STATE_ID_VAL(state)      (((state) >> PSCI_POWER_STATE_ID_SHIFT) & 0xffff)

/*
 * For system, cluster, core
 *  0: run
 *  1: standby(only core)
 *  2: retention
 *  3: powerdown
 */
#define PSCI_POWER_STATE_ID_RUN         0
#define PSCI_POWER_STATE_ID_STANDBY     1
#define PSCI_POWER_STATE_ID_RETENTION   2
#define PSCI_POWER_STATE_ID_POWERDOWN   3

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

void psci_system_off(void);
void psci_system_reboot(void);
rt_uint32_t rt_psci_get_version(void);
rt_uint32_t rt_psci_cpu_on(int cpuid, rt_ubase_t entry_point);
rt_uint32_t rt_psci_cpu_off(rt_uint32_t state);
rt_uint32_t rt_psci_cpu_suspend(rt_uint32_t power_state, rt_ubase_t entry_point);
rt_uint32_t rt_psci_migrate(int cpuid);
rt_uint32_t rt_psci_get_affinity_info(rt_ubase_t target_affinity, rt_ubase_t lowest_affinity_level);
rt_uint32_t rt_psci_migrate_info_type(void);

#endif  /* __PSCI_H__ */
