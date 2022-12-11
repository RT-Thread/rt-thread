/******************************************************************************
 * @file     core_pulp_cluster.h
 * @brief    CMSIS PULP Core Cluster  Peripheral Access Layer Header File
 * @version  V0.0.1
 * @date     04. April 2020
 ******************************************************************************/
/*
 * Copyright (c) 2017 GreenWaves Technologies SAS. All rights reserved.
 * Copyright (c) 2020 ETH Zurich
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __CLUSTER_PULP_H_GENERIC__
#define __CLUSTER_PULP_H_GENERIC__

#ifdef FEATURE_CLUSTER

#include "core_pulp.h"

#ifdef __cplusplus
 extern "C" {
#endif

/*******************************************************************************
 *                 CMSIS definitions
 ******************************************************************************/
#define CLUSTER_ID                    0                 /**< CLuster ID */
#define CLUSTER_CORES_NUM             8                 /**< CLuster cores number */

#define CLUSTER_HW_MUTEX_NUM           1
/** SoC events statically reserved by the runtime*/
#define FC_CLUSTER_SW_NOTIF_EVENT      0                /**< Used to notify FC*/
#define CLUSTER_CLUSTER_SW_NOTIF_EVENT 1                /**< Used to notify CLUSTER*/

/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_core_base     Core Definitions
  \brief      Definitions for base addresses, unions, and structures.
  @{
 */
   /**
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
  __OM uint32_t EOC;                   /*!< Offset: 0x000 (R/W ) CPUID Base Register */
  __IOM uint32_t _reserved0;           /*!< Offset: 0x004 (R/W)  reserved Register */
  __IOM uint32_t FETCH_EN;             /*!< Offset: 0x008 (R/W)  Interrupt Control and State Register */
  __IOM uint32_t _reserved1;           /*!< Offset: 0x00C (R/W)  reserved Register */
  __OM  uint32_t EVENT;                /*!< Offset: 0x010 (W)  Event out Register */
  __IOM uint32_t _reserved2[3];        /*!< Offset: 0x014 (R/W)  reserved Register */
  __OM  uint32_t CLUSTER_CG;           /*!< Offset: 0x020 (R/W)  Event out Register */
  __IOM uint32_t _reserved3[7];        /*!< Offset: 0x024 (R/W)  reserved Registers */
  __IOM uint32_t BOOT_ADDR[8];         /*!< Offset: 0x040 (R/W)  Vector Table Offset Register */
} SCB_Type;

/* SCB Registers Definitions */
#define SCB_EOC_Pos                    0U                               /*!< SCB EOC Position */
#define SCB_EOC_Msk                    (1UL /* << SCB_EOC_Pos*/)         /*!< SCB EOC Mask */

#define SCB_FETCH_EN_Pos               0U                               /*!< SCB FETCH_EN Position */
#define SCB_FETCH_EN_Msk               (1UL /* << SCB_FETCH_EN_Pos*/)    /*!< SCB FETCH_EN Mask */
/*@} end of group CMSIS_FC_CTRL */

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_SCBC     System Control Block for Icache (SCBC)
  \brief    Type definitions for the System Control Block Registers
  @{
 */

typedef struct
{
  __IOM uint32_t ICACHE_ENABLE;            /*!< Offset: 0x00 (R/W ) Cluster Icache Enable Register  */
  __IOM uint32_t ICACHE_FLUSH;             /*!< Offset: 0x04 (R/W)  Cluster Icache Flush Register */
  __IOM uint32_t ICACHE_LX_SEL_FLUSH;      /*!< Offset: 0x08 (R/W)  Cluster Icache Level-X Flush Register or FC Flush Selected Address Register*/
  __IOM uint32_t ICACHE_SEL_FLUSH_STATUS;  /*!< Offset: 0x0C (R/W)  Cluster Icache Flush Selected Address Register or FC ICACHE status */
  __IOM uint32_t ICACHE_CNTS_CLEAR;        /*!< Offset: 0x10 (R/W)  Cluster Icache is private Icache */
  __IOM uint32_t ICACHE_CNTS_ENABLE;       /*!< Offset: 0x10 (R/W)  Cluster Icache is private Icache */
} SCBC_Type;

/* SCBC Registers Definitions */
#define SCBC_ENABLE_Pos                    0U                               /*!< SCBC_ENABLE Position */
#define SCBC_ENABLE_Msk                    (1UL /* << SCBC_ENABLE_Pos*/)         /*!< SCBC_ENABLE Mask */

#define SCBC_STATUS_Pos                    0U                               /*!< SCBC_STATUS Position */
#define SCBC_STATUS_Msk                    (1UL /* << SCBC_STATUS_Pos*/)         /*!< SCBC_STATUS Mask */

/*@} end of group CMSIS_SCBC */

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_EU_CORE_DEMUX     Event Unit Core
  \brief    Type definitions for the event unit core Registers
  @{
 */
/**
  \brief  Structure type to access the EU_CORE_DEMUX.
 */

typedef struct {
  __IOM  uint32_t MASK;                    /**< EU_DEMUX mask register, offset: 0x00 */
  __IOM  uint32_t MASK_AND;                /**< EU_DEMUX mask and register, offset: 0x04 */
  __IOM  uint32_t MASK_OR;                 /**< EU_DEMUX mask or register, offset: 0x08 */
  __IOM  uint32_t MASK_IRQ;                /**< EU_DEMUX mask irq register, offset: 0x0C */
  __IOM  uint32_t MASK_IRQ_AND;            /**< EU_DEMUX mask irq and register, offset: 0x10 */
  __IOM  uint32_t MASK_IRQ_OR;             /**< EU_DEMUX mask irq or register, offset: 0x14 */
  __IOM  uint32_t STATUS;                  /**< EU_DEMUX Status register, offset: 0x18 */
  __IOM  uint32_t BUFFER;                  /**< EU_DEMUX buffer register, offset: 0x1C */
  __IOM  uint32_t BUFFER_MASKED;           /**< EU_DEMUX buffer masked register, offset: 0x20 */
  __IOM  uint32_t BUFFER_IRQ_MASKED;       /**< EU_DEMUX buffer irq masked register, offset: 0x24 */
  __IOM  uint32_t BUFFER_CLEAR;            /**< EU_DEMUX buffer clear register, offset: 0x28 */
  __IOM  uint32_t SW_EVENTS_MASK;          /**< EU_DEMUX software event mask register, offset: 0x2C */
  __IOM  uint32_t SW_EVENTS_MASK_AND;      /**< EU_DEMUX software event mask and register, offset: 0x30 */
  __IOM  uint32_t SW_EVENTS_MASK_OR;       /**< EU_DEMUX software event mask or register, offset: 0x34 */
  __IOM  uint32_t EVENT_WAIT;              /**< EU_DEMUX event wait register, offset: 0x38 */
  __IOM  uint32_t EVENT_WAIT_CLEAR;        /**< EU_DEMUX event wait clear register, offset: 0x3C */
  __IOM  uint32_t MASK_SEC_IRQ;            /**< EU_DEMUX mask sec irq register, offset: 0x40 */

} EU_CORE_DEMUX_Type;

/*@} end of group CMSIS_EU_CORE_DEMUX */

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_EU_SEC_DEMUX     Event Unit Security
  \brief    Type definitions for the event unit security Registers
  @{
 */
/**
  \brief  Structure type to access the EU_SEC_DEMUX.
 */
typedef struct {
  __IOM  uint32_t MASK;             /**< EU_SEC_DEMUX mask register, offset: 0x00 */
  __IOM  uint32_t MASK_AND;         /**< EU_SEC_DEMUX mask and register, offset: 0x04 */
  __IOM  uint32_t MASK_OR;          /**< EU_SEC_DEMUX mask or register, offset: 0x08 */
} EU_SEC_DEMUX_Type;

#define EU_SEC_ELEM_NUM                 8

/*@} end of group CMSIS_EU_DEMUX */

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_EU_LOOP_DEMUX     Event Unit Loop
  \brief    Type definitions for the event unit Loop Registers
  @{
 */
/**
  \brief  Structure type to access the EU_LOOP_DEMUX.
 */
typedef struct {
  __IOM  uint32_t STATE;             /**< EU_LOOP_DEMUX state register, offset: 0x00 */
  __IOM  uint32_t START;             /**< EU_LOOP_DEMUX start register, offset: 0x04 */
  __IOM  uint32_t END;               /**< EU_LOOP_DEMUX end register, offset: 0x08 */
  __IOM  uint32_t INCR;              /**< EU_LOOP_DEMUX increment register, offset: 0x0C */
  __IOM  uint32_t CHUNK;             /**< EU_LOOP_DEMUX chunk register, offset: 0x10 */
  __IOM  uint32_t EPOCH;             /**< EU_LOOP_DEMUX epoch register, offset: 0x14 */
  __IOM  uint32_t SINGLE;            /**< EU_LOOP_DEMUX single register, offset: 0x18 */
} EU_LOOP_DEMUX_Type;

#define    EU_LOOP_DEMUX_DONE_                        0x0
#define    EU_LOOP_DEMUX_LOCKED_                      0x1
#define    EU_LOOP_DEMUX_SKIP_                        0x2

/*@} end of group CMSIS_EU_SW_EVENTS_DEMUX */

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_EU_SW_EVENTS_DEMUX     Event Unit Loop
  \brief    Type definitions for the event unit Loop Registers
  @{
 */
/**
  \brief  Structure type to access the EU_SW_EVENTS_DEMUX.
 */
typedef struct {
  __IOM  uint32_t TRIGGER_SET[8];             /**< EU_SW_EVENTS_DEMUX trigger set register, offset: 0x00 */
  __IOM  uint32_t _reserved0[8];              /*!< Offset: 0x20 (R/W)  Empty Registers */
  __IOM  uint32_t TRIGGER_WAIT[8];            /**< EU_SW_EVENTS_DEMUX trigger wait register, offset: 0x40 */
  __IOM  uint32_t _reserved1[8];              /*!< Offset: 0x60 (R/W)  Empty Registers */
  __IOM  uint32_t TRIGGER_CLR[8];             /**< EU_SW_EVENTS_DEMUX trigger clear register, offset: 0x80 */
} EU_SW_EVENTS_DEMUX_Type;

/*@} end of group CMSIS_EU_SW_EVENTS_DEMUX */

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_EU_DISPATCH_DEMUX     Event Unit Dispatch
  \brief    Type definitions for the event unit Dispatch Registers
  @{
 */
typedef struct {
  __IOM  uint32_t FIFO_ACCESS;             /**< EU_DISPATCH_DEMUX fifo access register, offset: 0x00 */
  __IOM  uint32_t TEAM_CONFIG;             /**< EU_DISPATCH_DEMUX team config register, offset: 0x04 */
} EU_DISPATCH_DEMUX_Type;

#define EU_DISPATCH_DEMUX_ELEM_NUM                 8

/*@} end of group CMSIS_EU_DISPATCH_DEMUX */

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_EU_MUTEX_DEMUX     Event Unit Hardware Mutex
  \brief    Type definitions for the event unit Dispatch Registers
  @{
 */
typedef struct {
  __IOM  uint32_t MUTEX[1];                    /**< EU_MUTEX_DEMUX mutex register, offset: 0x00 */
} EU_MUTEX_DEMUX_Type;

#define EU_MUTEX_DEMUX_ELEM_NUM                    1

/*@} end of group CMSIS_EU_MUTEX_DEMUX */

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_EU_BARRIER_DEMUX     Event Unit Barrier
  \brief    Type definitions for the event unit Barrier Registers
  @{
 */
typedef struct {
  __IOM  uint32_t TRIGGER_MASK;             /**< EU_BARRIER_DEMUX triger mask register, offset: 0x00 */
  __IOM  uint32_t STATUS;                   /**< EU_BARRIER_DEMUX status register, offset: 0x04 */
  __IOM  uint32_t STATUS_SUMMRY;            /**< EU_BARRIER_DEMUX status summary register, offset: 0x08 */
  __IOM  uint32_t TARGET_MASK;              /**< EU_BARRIER_DEMUX target mask register, offset: 0x0C */
  __IOM  uint32_t TRIGGER;                  /**< EU_BARRIER_DEMUX trigger register, offset: 0x10 */
  __IOM  uint32_t TRIGGER_SET;              /**< EU_BARRIER_DEMUX trigger set register, offset: 0x14 */
  __IOM  uint32_t TRIGGER_WAIT;             /**< EU_BARRIER_DEMUX trigger wait register, offset: 0x18 */
  __IOM  uint32_t TRIGGER_WAIT_CLEAR;       /**< EU_BARRIER_DEMUX trigger clear register, offset: 0x1C */

} EU_BARRIER_DEMUX_Type;
/* We have only one HW Barrier  */

/*@} end of group CMSIS_EU_BARRIER_DEMUX */

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_EU_SOC_EVENTS     Event Unit Barrier
  \brief    Type definitions for the event unit Barrier Registers
  @{
 */
typedef struct {
  __IM  uint32_t CURRENT_EVENT;             /**< EU_SOC_EVENTS current event register, offset: 0x00 */

} EU_SOC_EVENTS_Type;
/* We have only one HW Barrier  */

#define EU_CURRENT_VALID_BIT_MASK                  (0x80000000U)
#define EU_CURRENT_VALID_BIT_SHIFT                 (31U)
#define EU_CURRENT_VALID_BIT(x)                    (((uint32_t)(((uint32_t)(x)) << EU_CURRENT_VALID_BIT_SHIFT)) & EU_CURRENT_VALID_BIT_MASK)

#define EU_CURRENT_SOC_EVENT_MASK                  0xFF

/*@} end of group CMSIS_EU_SOC_EVENTS */

/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_core_base     Core Definitions
  \brief      Definitions for base addresses, unions, and structures.
  @{
 */
   /**
  \brief  Structure type to access the direct memory access (DMAMCHAN).
 */
typedef struct
{
  __IOM uint32_t CMD;                   /*!< Offset: 0x00 (R/W ) DMAMCHAN Command Base Register */
  __IOM uint32_t STATUS;                /*!< Offset: 0x04 (R/W)  DMAMCHAN Channle Status Register */
} DMAMCHAN_Type;

/* DMAMCHAN Registers Definitions */
#define DMAMCHAN_CMD_TID_Pos                    0U                               /*!< DMAMCHAN TID Position */
#define DMAMCHAN_CMD_TID_Msk                    (0xFUL /* << DMAMCHAN_CMD_TID_Pos*/)  /*!< DMAMCHAN TID Mask */

#define DMAMCHAN_CMD_BLE_Pos                    21U                              /*!< DMAMCHAN Broadcast Lines Enable Position */
#define DMAMCHAN_CMD_BLE_Msk                    (1UL << DMAMCHAN_CMD_BLE_Pos)    /*!< DMAMCHAN CMD Broadcast Lines Enable Mask */

#define DMAMCHAN_CMD_ILE_Pos                    20U                              /*!< DMAMCHAN Intrrupt Line EnableID Position */
#define DMAMCHAN_CMD_ILE_Msk                    (1UL << DMAMCHAN_CMD_ILE_Pos)    /*!< DMAMCHAN Intrrupt Line Enable Mask */

#define DMAMCHAN_CMD_ELE_Pos                    19U                              /*!< DMAMCHAN CMD Event Line Enable Position */
#define DMAMCHAN_CMD_ELE_Msk                    (1UL << DMAMCHAN_CMD_ELE_Pos)    /*!< DMAMCHAN CMD Event Line Enable Mask */

#define DMAMCHAN_CMD_2D_Pos                     18U                              /*!< DMAMCHAN CMD 2D transfer Position */
#define DMAMCHAN_CMD_2D_Msk                     (1UL << DMAMCHAN_CMD_2D_Pos)     /*!< DMAMCHAN CMD 2D transfer Mask */

#define DMAMCHAN_CMD_INC_Pos                    17U                              /*!< DMAMCHAN CMD Increment Position */
#define DMAMCHAN_CMD_INC_Msk                    (1UL << DMAMCHAN_CMD_INC_Pos)    /*!< DMAMCHAN CMD Increment Mask */

#define DMAMCHAN_CMD_TYP_Pos                    16U                              /*!< DMAMCHAN CMD Type Position */
#define DMAMCHAN_CMD_TYP_Msk                    (1UL << DMAMCHAN_CMD_TYP_Pos)    /*!< DMAMCHAN CMD Type Mask */

#define DMAMCHAN_CMD_LEN_Pos                    0U                               /*!< DMAMCHAN CMD Length Position */
#define DMAMCHAN_CMD_LEN_Msk                    (0xFFUL /*<< DMAMCHAN_EOC_Pos*/) /*!< DMAMCHAN CMD Length Mask */

#define DMAMCHAN_CMD_2D_STRIDE_Pos              16U                               /*!< DMAMCHAN CMD 2D STRIDE Position */
#define DMAMCHAN_CMD_2D_STRIDE_Msk              (0xFFUL << DMAMCHAN_CMD_2D_STRIDE_Pos) /*!< DMAMCHAN CMD 2D STRIDE Mask */

#define DMAMCHAN_CMD_2D_COUNT_Pos               0U                               /*!< DMAMCHAN CMD 2D COUNT Position */
#define DMAMCHAN_CMD_2D_COUNT_Msk               (0xFFUL /* << DMAMCHAN_CMD_2D_COUNT_Pos*/)  /*!< DMAMCHAN CMD 2D COUNT Mask */

/*@} end of group CMSIS_DMAMCHAN */

/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_core_base     Core Definitions
  \brief      Definitions for base addresses, unions, and structures.
  @{
 */
   /**
  \brief  Structure type to access the direct memory access compressor (DMAMCHAN).
 */
typedef struct
{
    /*!< Offset: 0x00 (W ) Compressor TCDM Address Register */
    __O uint32_t TCDM_ADDRESS;
    /*!< Offset: 0x04 (W ) Compressor L2 Address Register */
    __O uint32_t L2_ADDRESS;
    /*!< Offset: 0x08 (W ) Compressor configuration Register */
    __O uint32_t CONFIG;
    // 0xC
    __IOM uint32_t PAD0;
    /*!< Offset: 0x10 (W ) Compressor LUT patterns Register */
    __O uint32_t LUT;
    /*!< Offset: 0x14 (W ) Compressor compression special value Register */
    __O uint32_t SPECIAL;
    /*!< Offset: 0x18 (R ) Compressor readen bits Register */
    __I uint32_t BIT_READ;
    /*!< Offset: 0x1C (W ) Compressor transfer direction Register */
    __O uint32_t DIRECTION;
} DMAMCHAN_COMPRESSOR_Type;

typedef struct {
    __O uint32_t TCDM_ADDR;
    __O uint32_t L2_ADDR;
    __O uint32_t CONF_REG;
    __I uint32_t STAT_REG;
    __O uint32_t LUT_REG;
    __O uint32_t SYMBOL_REG;
    __O uint32_t BIT_READ_REG;
    __O uint32_t MODE_REG;
    __O uint32_t SW_RST_REG;
    __O uint32_t CLKEN_REG;
    __O uint32_t TRIGGER_REG;
    __IOM uint32_t PAD0;
    __O uint32_t L2_COUNT_REG;
    __O uint32_t L2_STRIDE_REG;
    __O uint32_t TCDM_COUNT_REG;
    __O uint32_t TCDM_STRIDE_REG;
} decompressor_t;

/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_CLUSTER_EU_CORES    Cluster Event Unit Cores
  \brief    Type definitions for the event unit core Registers
  @{
 */
/**
  \brief  Structure type to access the CLUSTER_EU_CORES.
 */

typedef struct {
  EU_CORE_DEMUX_Type CORES[CLUSTER_CORES_NUM];          /*!< Offset: 0x000 (R/W)  Cluster Event Unit cores */

} CLUSTER_EU_CORES_Type;

/*@} end of group CMSIS_CLUSTER_EU_CORE */

#define CLUSTER_DISPATCH_IS_ENTRY_MASK               (0x1U)
#define CLUSTER_DISPATCH_IS_ENTRY_SHIFT              (0U)
#define CLUSTER_DISPATCH_IS_ENTRY(x)                 (((uint32_t)(((uint32_t)(x)) /* << CLUSTER_DISPATCH_IS_ENTRY_SHIFT */)) & CLUSTER_DISPATCH_IS_ENTRY_MASK)

#define CLUSTER_DISPATCH_ENTRY_ADDR_MASK             (0x7FFFFFFEU)
#define CLUSTER_DISPATCH_ENTRY_ADDR_SHIFT            (1U)
#define CLUSTER_DISPATCH_ADDR_ENTRY(x)               (((uint32_t)(((uint32_t)(x)) << CLUSTER_DISPATCH_ENTRY_ADDR_SHIFT)) & CLUSTER_DISPATCH_ENTRY_ADDR_MASK)

#define CLUSTER_DISPATCH_ENTRY_MASK                  (0x7FFFFFFFU)
#define CLUSTER_DISPATCH_ENTRY_SHIFT                 (0U)
#define CLUSTER_DISPATCH_ENTRY(x)                    (((uint32_t)(((uint32_t)(x)) /*<< CLUSTER_DISPATCH_ENTRY_SHIFT*/)) & CLUSTER_DISPATCH_ENTRY_MASK)
#define READ_CLUSTER_DISPATCH_ENTRY(x)               (((uint32_t)(((uint32_t)(x)) & CLUSTER_DISPATCH_ENTRY_MASK)) /*>> CLUSTER_DISPATCH_ENTRY_SHIFT*/)

#define CLUSTER_DISPATCH_IS_JOB_MASK                 (0x80000000U)
#define CLUSTER_DISPATCH_IS_JOB_SHIFT                (31U)
#define CLUSTER_DISPATCH_IS_JOB(x)                   (((uint32_t)(((uint32_t)(x)) << CLUSTER_DISPATCH_IS_JOB_SHIFT)) & CLUSTER_DISPATCH_IS_JOB_MASK)

/* Memory map */

#define CLUSTER_BASE                    (ARCHI_CLUSTER_GLOBAL_ADDR(0)) /*!< CLUSTER Base Address */

#define CLUSTER_SCB_BASE                (ARCHI_CLUSTER_PERIPHERALS_GLOBAL_ADDR(0)) /*!< CLUSTER System Control Block Base Address */
#define CLUSTER_SCBC_BASE               (ARCHI_ICACHE_CTRL_ADDR)                   /*!< CLUSTER System Control Block Cache Base Address */
#define CLUSTER_SysTick_BASE            (ARCHI_CLUSTER_TIMER_ADDR)              /*!< CLUSTER SysTick Base Address */

#define CLUSTER_EU_BARRIER_BASE         (ARCHI_EU_ADDR + 0x400UL) /*!< CLUSTER Event Unit HW Barrier Base Address */
#define CLUSTER_EU_SW_EVENTS_BASE       (ARCHI_EU_ADDR + 0x600UL) /*!< CLUSTER Event Unit SW Events Base Address */
#define CLUSTER_EU_SOC_EVENTS_BASE      (ARCHI_EU_ADDR + 0x700UL) /*!< CLUSTER Event Unit SOC Events Base Address */
#define CLUSTER_EU_EXT_EVENTS_BASE      (ARCHI_EU_ADDR + 0x780UL) /*!< CLUSTER Event Unit EXT Events Base Address */

#define CLUSTER_EU_CORE_DEMUX_BASE      (ARCHI_DEMUX_PERIPHERALS_ADDR)        /*!< CLUSTER Event Unit Core Demux Base Address */
#define CLUSTER_EU_SEC_DEMUX_BASE       (ARCHI_DEMUX_PREIPHERALS_ADDR + 0x040UL)  /*!< CLUSTER Event Unit Security Demux Base Address */
#define CLUSTER_EU_LOOP_DEMUX_BASE      (ARCHI_DEMUX_PREIPHERALS_ADDR + 0x060UL)  /*!< CLUSTER Event Unit Loop Demux Base Address */
#define CLUSTER_EU_DISPATCH_DEMUX_BASE  (ARCHI_DEMUX_PREIPHERALS_ADDR + 0x080UL)  /*!< CLUSTER Event Unit Dispatch Demux Base Address */
#define CLUSTER_EU_MUTEX_DEMUX_BASE     (ARCHI_DEMUX_PREIPHERALS_ADDR + 0x0C0UL)  /*!< CLUSTER Event Unit Mutex Demux Base Address */
#define CLUSTER_EU_SW_EVENTS_DEMUX_BASE (ARCHI_DEMUX_PREIPHERALS_ADDR + 0x100UL)  /*!< CLUSTER Event Unit SW Events Demux Base Address */
#define CLUSTER_EU_BARRIER_DEMUX_BASE   (ARCHI_DEMUX_PREIPHERALS_ADDR + 0x200UL)  /*!< CLUSTER Event Unit Barrier Demux Base Address */

/* Cluster Core Structrue definitions */
#define CLUSTER_EU_SW_EVENTS      ((EU_SW_EVENTS_DEMUX_Type   *)  CLUSTER_EU_SW_EVENTS_BASE) /*!< EU_SW_EVENTS_DEMUX configuration struct */
#define EU_CORES    ((CLUSTER_EU_CORES_Type   *)   ARCHI_EU_ADDR)             /*!< CLUSTER_EU_CORES configuration struct */
#define SCB         ((SCB_Type   *)    CLUSTER_SCB_BASE )                     /*!< CLUSTER SCB configuration struct */
#define CLUSTER_SCBC  ((SCBC_Type   *)  CLUSTER_SCBC_BASE )                   /*!< CLUSTER SCBC configuration struct */

#define CLUSTER_SysTick             ((SysTick_Type   *)     CLUSTER_SysTick_BASE  )   /*!< SysTick configuration struct */
#define CLUSTER_TIMERL              ((TimerL_Type    *)     CLUSTER_SysTick_BASE  )   /*!< SysTick configuration struct */
#define CLUSTER_TIMERH              ((TimerH_Type    *)     CLUSTER_SysTick_BASE  )   /*!< SysTick configuration struct */

#ifdef __cplusplus
}
#endif

#endif

#endif /* __CLUSTER_PULP_H_GENERIC */
