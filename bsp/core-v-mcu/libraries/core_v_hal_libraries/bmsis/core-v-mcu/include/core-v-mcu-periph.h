/*
 * Copyright 2020 GreenWaves Technologies
 * Copyright 2020 ETH Zurich
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */


/*!
 * @file periph.h
 * @version 1.0
 * @date 2017-07-19
 * @brief CMSIS Peripheral Access Layer for PULP
 *
 * CMSIS Peripheral Access Layer for PULP
 */

#ifndef TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_PERIPH_H_
#define TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_PERIPH_H_                       /**< Symbol preventing repeated inclusion */

#include "pmsis_gcc.h"
/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */
/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS  32                  /**< Number of interrupts in the Vector table */

typedef enum IRQn {
  FC_NOTIFY_CLUSTER_EVENT      = 0,                /**< Software event interrupt */
  CLUSTER_NOTIFY_FC_EVENT      = 1,                /**< Software event interrupt */
  FC_SW_NOTIFY_BRIDGE_EVENT    = 2,                /**< Software event interrupt */
  FC_SW_NOTIFY_EVENT           = 3,                /**< Software event interrupt */
  CLUSTER_NOTIFY_FC_IRQN       = 4,                /**< Software event interrupt */
  DMA_SW_IRQN                  = 6,
  PENDSV_IRQN                  = 7,                /**< Software event U -> M PendSV interrupt */

  /* Device specific interrupts */
  DMA_EVT_IRQN                 = 8,                /**< DMA event interrupt */
  DMA_IRQN                     = 9,                /**< DMA interrupt */
  FC_TIMER0_IRQN               = 10,               /**< FC timer0 event interrupt */
  SYSTICK_IRQN                 = 10,               /**< PULP U -> M System Tick Interrupt */
  FC_TIMER1_IRQN               = 11,               /**< FC timer1 interrupt */

  /* misc */
  FC_CLK_REF_EVENT             = 14,              /**< Reference clock edge event */
  FC_GPIO_EVENT                = 15,              /**< GPIO event */

  /* advanced timer events */
  FC_ADV_TIMER0_EVENT          = 17,              /**< Advanced Timer 0 event */
  FC_ADV_TIMER1_EVENT          = 18,              /**< Advanced Timer 1 event */
  FC_ADV_TIMER2_EVENT          = 19,              /**< Advanced Timer 2 event */
  FC_ADV_TIMER3_EVENT          = 20,              /**< Advanced Timer 3 event */

  /* CLUSTER_NOT_BUSY_EVENT       = 21, */
  /* CLUSTER_POK_EVENT            = 22, */
  /* CLUSTER_CG_OK_EVENT          = 23, */

  /* PICL_OK_EVENT                = 24, */
  /* SCU_OK_EVENT                 = 25, */

  FC_SOC_EVENT                 = 26,              /**< Event unit new event */

  FC_QUEUE_ERROR_EVENT         = 29,              /**< Event unit queue overflow event */

  FC_HP_EVENT1                 = 30,
  FC_HP_EVENT0                 = 31
} IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- PULP Core Configuration
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PULP_Core_Configuration PULP Core Configuration
 * @{
 */

#define __MPU_PRESENT                  0         /**< Defines if an MPU is present or not */
#define __NVIC_PRIO_BITS               0         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig         0         /**< Vendor specific implementation of SysTickConfig is defined */
#define __FPU_PRESENT                  0         /**< Defines if an FPU is present or not */

#include "core_pulp.h"              /* Core Peripheral Access Layer */

#ifdef FEATURE_CLUSTER
#include "core_pulp_cluster.h"              /* Cluster Access Layer */
#endif

/*!
 * @}
 */ /* end of group PULP_Core_Configuration */


/* ----------------------------------------------------------------------------
   -- Mapping Information
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Mapping_Information Mapping Information
 * @{
 */

/** Mapping Information */
/*!
 * @addtogroup udma_request
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*!
 * @}
 */ /* end of group udma_request */



/*!
 * @}
 */ /* end of group Mapping_Information */


/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */

/* ----------------------------------------------------------------------------
   -- FLL_CTRL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLL_CTRL_Peripheral_Access_Layer FLL_CTRL Peripheral Access Layer
 * @{
 */

/** FLL_CTRL - Registers Layout Typedef */
/* TODO: looks like pulp has 3 fll */
typedef struct {
  __IO  uint32_t FLL_STATUS;            /**< FLL_CTRL Status register, offset: 0x00 */
  __IO  uint32_t FLL_CONF1;                 /**< FLL_CTRL Configuration1 register, offset: 0x04 */
  __IO  uint32_t FLL_CONF2;                 /**< FLL_CTRL Configuration2 register, offset: 0x08 */
  __IO  uint32_t FLL_INTEGRATOR;            /**< FLL_CTRL INTEGRATOR register, offset: 0x0C */
} FLL_CTRL_Type;

/* TODO: removed this register, see if it still exists */
/* __IO  uint32_t FLL_CONVERGE;*/              /**< FLL_CTRL Fll Converge register, offset: 0x20 */

/* ----------------------------------------------------------------------------
   -- FLL_CTRL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLL_CTRL_Register_Masks FLL_CTRL Register Masks
 * @{
 */
/*! @name FLL_STATUS - FLL_CTRL status register */
#define FLL_CTRL_STATUS_MULTI_FACTOR_MASK              (0xFFFFU)
#define FLL_CTRL_STATUS_MULTI_FACTOR_SHIFT             (0U)
#define FLL_CTRL_STATUS_MULTI_FACTOR(x)                (((uint32_t)(((uint32_t)(x)) /* << FLL_CTRL_STATUS_MULTI_FACTOR_SHIFT */)) & FLL_CTRL_STATUS_MULTI_FACTOR_MASK)
#define READ_FLL_CTRL_STATUS_MULTI_FACTOR(x)           (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_STATUS_MULTI_FACTOR_MASK)) /*>> FLL_CTRL_STATUS_MULTI_FACTOR_SHIFT*/)

/*! @name SOC_CONF1 - FLL_CTRL configuration 1 register */
#define FLL_CTRL_CONF1_MULTI_FACTOR_MASK           (0xFFFFU)
#define FLL_CTRL_CONF1_MULTI_FACTOR_SHIFT          (0U)
#define FLL_CTRL_CONF1_MULTI_FACTOR(x)             (((uint32_t)(((uint32_t)(x)) /* << FLL_CTRL_CONF1_MULTI_FACTOR_SHIFT */)) & FLL_CTRL_CONF1_MULTI_FACTOR_MASK)
#define READ_FLL_CTRL_CONF1_MULTI_FACTOR(x)        (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_CONF1_MULTI_FACTOR_MASK)) /*>> FLL_CTRL_CONF1_MULTI_FACTOR_SHIFT*/)

#define FLL_CTRL_CONF1_DCO_INPUT_MASK              (0x3FF0000U)
#define FLL_CTRL_CONF1_DCO_INPUT_SHIFT             (16U)
#define FLL_CTRL_CONF1_DCO_INPUT(x)                (((uint32_t)(((uint32_t)(x)) << FLL_CTRL_CONF1_DCO_INPUT_SHIFT)) & FLL_CTRL_CONF1_DCO_INPUT_MASK)
#define READ_FLL_CTRL_CONF1_DCO_INPUT(x)           (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_CONF1_DCO_INPUT_MASK)) >> FLL_CTRL_CONF1_DCO_INPUT_SHIFT)

#define FLL_CTRL_CONF1_CLK_OUT_DIV_MASK            (0x3C000000U)
#define FLL_CTRL_CONF1_CLK_OUT_DIV_SHIFT           (26U)
#define FLL_CTRL_CONF1_CLK_OUT_DIV(x)              (((uint32_t)(((uint32_t)(x)) << FLL_CTRL_CONF1_CLK_OUT_DIV_SHIFT)) & FLL_CTRL_CONF1_CLK_OUT_DIV_MASK)
#define READ_FLL_CTRL_CONF1_CLK_OUT_DIV(x)         (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_CONF1_CLK_OUT_DIV_MASK)) >> FLL_CTRL_CONF1_CLK_OUT_DIV_SHIFT)

#define FLL_CTRL_CONF1_OUTPUT_LOCK_EN_MASK         (0x40000000U)
#define FLL_CTRL_CONF1_OUTPUT_LOCK_EN_SHIFT        (30U)
#define FLL_CTRL_CONF1_OUTPUT_LOCK_EN(x)           (((uint32_t)(((uint32_t)(x)) << FLL_CTRL_CONF1_OUTPUT_LOCK_EN_SHIFT)) & FLL_CTRL_CONF1_OUTPUT_LOCK_EN_MASK)
#define READ_FLL_CTRL_CONF1_OUTPUT_LOCK_EN(x)      (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_CONF1_OUTPUT_LOCK_EN_MASK)) >> FLL_CTRL_CONF1_OUTPUT_LOCK_EN_SHIFT)

#define FLL_CTRL_CONF1_MODE_MASK                   (0x80000000U)
#define FLL_CTRL_CONF1_MODE_SHIFT                  (31U)
#define FLL_CTRL_CONF1_MODE(x)                     (((uint32_t)(((uint32_t)(x)) << FLL_CTRL_CONF1_MODE_SHIFT)) & FLL_CTRL_CONF1_MODE_MASK)
#define READ_FLL_CTRL_CONF1_MODE(x)                (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_CONF1_MODE_MASK)) >> FLL_CTRL_CONF1_MODE_SHIFT)

/*! @name SOC_CONF2 - FLL_CTRL configuration 2 register */
#define FLL_CTRL_CONF2_LOOPGAIN_MASK               (0xFU)
#define FLL_CTRL_CONF2_LOOPGAIN_SHIF  T            (0U)
#define FLL_CTRL_CONF2_LOOPGAIN(x)                 (((uint32_t)(((uint32_t)(x)) /* << FLL_CTRL_CONF2_LOOPGAIN_SHIFT */)) & FLL_CTRL_CONF2_LOOPGAIN_MASK)
#define READ_FLL_CTRL_CONF2_LOOPGAIN(x)            (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_CONF2_LOOPGAIN_MASK))/* >> FLL_CTRL_CONF2_LOOPGAIN_SHIFT*/)

#define FLL_CTRL_CONF2_DEASSERT_CYCLES_MASK        (0x3F0U)
#define FLL_CTRL_CONF2_DEASSERT_CYCLES_SHIFT       (4U)
#define FLL_CTRL_CONF2_DEASSERT_CYCLES(x)          (((uint32_t)(((uint32_t)(x)) << FLL_CTRL_CONF2_DEASSERT_CYCLES_SHIFT)) & FLL_CTRL_CONF2_DEASSERT_CYCLES_MASK)
#define READ_FLL_CTRL_CONF2_DEASSERT_CYCLES(x)     (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_CONF2_DEASSERT_CYCLES_MASK)) >> FLL_CTRL_CONF2_DEASSERT_CYCLES_SHIFT)

#define FLL_CTRL_CONF2_ASSERT_CYCLES_MASK          (0xFC00U)
#define FLL_CTRL_CONF2_ASSERT_CYCLES_SHIFT         (10U)
#define FLL_CTRL_CONF2_ASSERT_CYCLES(x)            (((uint32_t)(((uint32_t)(x)) << FLL_CTRL_CONF2_ASSERT_CYCLES_SHIFT)) & FLL_CTRL_CONF2_ASSERT_CYCLES_MASK)
#define READ_FLL_CTRL_CONF2_ASSERT_CYCLES(x)       (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_CONF2_ASSERT_CYCLES_MASK)) >> FLL_CTRL_CONF2_ASSERT_CYCLES_SHIFT)

#define FLL_CTRL_CONF2_LOCK_TOLERANCE_MASK         (0xFFF0000U)
#define FLL_CTRL_CONF2_LOCK_TOLERANCE_SHIFT        (16U)
#define FLL_CTRL_CONF2_LOCK_TOLERANCE(x)           (((uint32_t)(((uint32_t)(x)) << FLL_CTRL_CONF2_LOCK_TOLERANCE_SHIFT)) & FLL_CTRL_CONF2_LOCK_TOLERANCE_MASK)
#define READ_FLL_CTRL_CONF2_LOCK_TOLERANCE(x)      (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_CONF2_LOCK_TOLERANCE_MASK)) >> FLL_CTRL_CONF2_LOCK_TOLERANCE_SHIFT)

#define FLL_CTRL_CONF2_CONF_CLK_SEL_MASK           (0x20000000U)
#define FLL_CTRL_CONF2_CONF_CLK_SEL_SHIFT          (29U)
#define FLL_CTRL_CONF2_CONF_CLK_SEL(x)             (((uint32_t)(((uint32_t)(x)) << FLL_CTRL_CONF2_CONF_CLK_SEL_SHIFT)) & FLL_CTRL_CONF2_CONF_CLK_SEL_MASK)
#define READ_FLL_CTRL_CONF2_CONF_CLK_SEL(x)        (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_CONF2_CONF_CLK_SEL_MASK)) >> FLL_CTRL_CONF2_CONF_CLK_SEL_SHIFT)

#define FLL_CTRL_CONF2_OPEN_LOOP_MASK              (0x40000000U)
#define FLL_CTRL_CONF2_OPEN_LOOP_SHIFT             (30U)
#define FLL_CTRL_CONF2_OPEN_LOOP(x)                (((uint32_t)(((uint32_t)(x)) << FLL_CTRL_CONF2_OPEN_LOOP_SHIFT)) & FLL_CTRL_CONF2_OPEN_LOOP_MASK)
#define READ_FLL_CTRL_CONF2_OPEN_LOOP(x)           (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_CONF2_OPEN_LOOP_MASK)) >> FLL_CTRL_CONF2_OPEN_LOOP_SHIFT)

#define FLL_CTRL_CONF2_DITHERING_MASK              (0x80000000U)
#define FLL_CTRL_CONF2_DITHERING_SHIFT             (31U)
#define FLL_CTRL_CONF2_DITHERING(x)                (((uint32_t)(((uint32_t)(x)) << FLL_CTRL_CONF2_DITHERING_SHIFT)) & FLL_CTRL_CONF2_DITHERING_MASK)
#define READ_FLL_CTRL_CONF2_DITHERING(x)           (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_CONF2_DITHERING_MASK)) >> FLL_CTRL_CONF2_DITHERING_SHIFT)

/*! @name SOC_INTEGRATOR - FLL_CTRL configuration 2 register */
#define FLL_CTRL_INTEGRATOR_FRACT_PART_MASK        (0xFFC0U)
#define FLL_CTRL_INTEGRATOR_FRACT_PART_SHIFT       (6U)
#define FLL_CTRL_INTEGRATOR_FRACT_PART(x)          (((uint32_t)(((uint32_t)(x)) << FLL_CTRL_INTEGRATOR_FRACT_PART_SHIFT)) & FLL_CTRL_INTEGRATOR_FRACT_PART_MASK)
#define READ_FLL_CTRL_INTEGRATOR_FRACT_PART(x)     (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_INTEGRATOR_FRACT_PART_MASK)) >> FLL_CTRL_INTEGRATOR_FRACT_PART_SHIFT)

#define FLL_CTRL_INTEGRATOR_INT_PART_MASK          (0x3FF0000U)
#define FLL_CTRL_INTEGRATOR_INT_PART_SHIFT         (16U)
#define FLL_CTRL_INTEGRATOR_INT_PART(x)            (((uint32_t)(((uint32_t)(x)) << FLL_CTRL_INTEGRATOR_INT_PART_SHIFT)) & FLL_CTRL_INTEGRATOR_INT_PART_MASK)
#define READ_FLL_CTRL_INTEGRATOR_INT_PART(x)       (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_INTEGRATOR_INT_PART_MASK)) >> FLL_CTRL_INTEGRATOR_INT_PART_SHIFT)

/*! @name FLL_CONVERGE - FLL_CTRL configuration 2 register */
#define FLL_CTRL_SOC_FLL_CONV_MASK                 (0x1U)
#define FLL_CTRL_SOC_FLL_CONV_SHIFT                (0U)
#define FLL_CTRL_SOC_FLL_CONV(x)                   (((uint32_t)(((uint32_t)(x)) /*<< FLL_CTRL_SOC_FLL_CONV_SHIFT */)) & FLL_CTRL_SOC_FLL_CONV_MASK)
#define READ_FLL_CTRL_SOC_FLL_CONV(x)              (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_SOC_FLL_CONV_MASK)) /*>> FLL_CTRL_SOC_FLL_CONV_SHIFT*/)

#define FLL_CTRL_CLUSTER_FLL_CONV_MASK             (0x2U)
#define FLL_CTRL_CLUSTER_FLL_CONV_SHIFT            (1U)
#define FLL_CTRL_CLUSTER_FLL_CONV(x)               (((uint32_t)(((uint32_t)(x)) << FLL_CTRL_CLUSTER_FLL_CONV_SHIFT)) & FLL_CTRL_CLUSTER_FLL_CONV_MASK)
#define READ_FLL_CTRL_CLUSTER_FLL_CONV(x)          (((uint32_t)(((uint32_t)(x)) & FLL_CTRL_CLUSTER_FLL_CONV_MASK)) >> FLL_CTRL_CLUSTER_FLL_CONV_SHIFT)


/*!
 * @}
 */ /* end of group FLL_CTRL_Register_Masks */

/* The number of FLL */
#define FLL_NUM       ARCHI_NB_FLL
/* The FLL reference frequency*/
#define FLL_REF_CLK   ARCHI_REF_CLOCK


/* FLL_CTRL - Peripheral instance base addresses */
/** Peripheral FLL_CTRL base address */
#define FLL_CTRL_BASE                                (SOC_PERIPHERALS_ADDR)
/** Peripheral FLL_CTRL base pointer */
#define FLL_CTRL                                     ((FLL_CTRL_Type *)FLL_CTRL_BASE)
/** Array initializer of FLL_CTRL base addresses */
#define FLL_CTRL_BASE_ADDRS                          { FLL_CTRL_BASE }
/** Array initializer of FLL_CTRL base pointers */
#define FLL_CTRL_BASE_PTRS                           { FLL_CTRL }

/*!
 * @}
 */ /* end of group FLL_CTRL_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- GPIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */
#include "hal_gpio_periph.h"
#define gpio(id) (((gpio_t *) GPIO_ADDR) + id)



/* ----------------------------------------------------------------------------
   -- UDMA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UDMA_Peripheral_Access_Layer  UDMA Peripheral Access Layer
 * @{
 */

/** UDMA - General Register Layout Typedef */
typedef struct {
  __IO uint32_t RX_SADDR;                          /**< RX UDMA buffer transfer address register, offset: 0x0 */
  __IO uint32_t RX_SIZE;                           /**< RX UDMA buffer transfer size register, offset: 0x4 */
  __IO uint32_t RX_CFG;                            /**< RX UDMA transfer configuration register, offset: 0x8 */
  __IO uint32_t RX_INITCFG;                        /**< Reserved, offset: 0xC */
  __IO uint32_t TX_SADDR;                          /**< TX UDMA buffer transfer address register, offset: 0x10 */
  __IO uint32_t TX_SIZE;                           /**< TX UDMA buffer transfer size register, offset: 0x14 */
  __IO uint32_t TX_CFG;                            /**< TX UDMA transfer configuration register, offset: 0x18 */
  __IO uint32_t TX_INITCFG;                        /**< Reserved, offset: 0x1C */

} UDMA_Type;

#include "hal_udma_core_periph.h"
/* ----------------------------------------------------------------------------
   -- UDMA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UDMA_Register_Masks UDMA Register Masks
 * @{
 */
/*! @name RX_SADDR - RX TX UDMA buffer transfer address register */
#define UDMA_SADDR_ADDR_MASK                 (0xFFFFU)
#define UDMA_SADDR_ADDR_SHIFT                (0U)
#define UDMA_SADDR_ADDR(x)                   (((uint32_t)(((uint32_t)(x)) /*<< UDMA_SADDR_ADDR_SHIFT*/)) & UDMA_SADDR_ADDR_MASK)

/*! @name RX_SIZE - RX TX UDMA buffer transfer size register */
#define UDMA_SIZE_SIZE_MASK                  (0x1FFFFU)
#define UDMA_SIZE_SIZE_SHIFT                 (0U)
#define UDMA_SIZE_SIZE(x)                    (((uint32_t)(((uint32_t)(x)) << UDMA_SIZE_SIZE_SHIFT)) & UDMA_SIZE_SIZE_MASK)


/*! @name RX_CFG - RX TX UDMA transfer configuration register */
#define UDMA_CFG_CONTINOUS_MASK              (0x1U)
#define UDMA_CFG_CONTINOUS_SHIFT             (0U)
#define UDMA_CFG_CONTINOUS(x)                (((uint32_t)(((uint32_t)(x)) /*<< UDMA_CFG_CONTINOUS_SHIFT*/)) & UDMA_CFG_CONTINOUS_MASK)
#define UDMA_CFG_DATA_SIZE_MASK              (0x6U)
#define UDMA_CFG_DATA_SIZE_SHIFT             (1U)
#define UDMA_CFG_DATA_SIZE(x)                (((uint32_t)(((uint32_t)(x)) << UDMA_CFG_DATA_SIZE_SHIFT)) & UDMA_CFG_DATA_SIZE_MASK)
#define UDMA_CFG_EN_MASK                     (0x10U)
#define UDMA_CFG_EN_SHIFT                    (4U)
#define UDMA_CFG_EN(x)                       (((uint32_t)(((uint32_t)(x)) << UDMA_CFG_EN_SHIFT)) & UDMA_CFG_EN_MASK)
#define UDMA_CFG_PENDING_MASK                (0x20U)
#define UDMA_CFG_PENDING_SHIFT               (5U)
#define UDMA_CFG_PENDING(x)                  (((uint32_t)(((uint32_t)(x)) << UDMA_CFG_PENDING_SHIFT)) & UDMA_CFG_PENDING_MASK)
#define UDMA_CFG_CLR_MASK                    (0x20U)
#define UDMA_CFG_CLR_SHIFT                   (5U)
#define UDMA_CFG_CLR(x)                      (((uint32_t)(((uint32_t)(x)) << UDMA_CFG_CLR_SHIFT)) & UDMA_CFG_CLR_MASK)

/*!
 * @}
 */ /* end of group UDMA_Register_Masks */


/* UDMA - Peripheral instance base addresses */
/** Peripheral UDMA base address 0x1A102080 */
#define UDMA_BASE                                UDMA_PERIPH_BASE_ADDR
/** Peripheral UDMA events number */
/* TODO: check those */
#define UDMA_EVENTS_NUM                          19
/** Peripheral UDMA channel number */
#define UDMA_CHANNEL_NUM                         10

/*!
 * @}
 */ /* end of group UDMA_Peripheral_Access_Layer */




/* ----------------------------------------------------------------------------
   -- UDMA Global Configuration Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UDMA_GC_Peripheral_Access_Layer UDMA_GC Peripheral Access Layer
 * @{
 */

/** UDMA Global configuration - Register Layout Typedef */
typedef struct {
  __IO uint32_t CG;                          /**< UDMA_GC clock gating register, offset: 0x0 */
  __IO uint32_t EVTIN;                       /**< UDMA_GC input event register, offset: 0x04 */
} UDMA_GC_Type;

/* ----------------------------------------------------------------------------
   -- UDMA_GC Register Masks
   ---------------------------------------------------------------------------- */
/*!
 * @addtogroup UDMA_GC_Register_Masks UDMA_GC Register Masks
 * @{
 */

/*! @name UDMA_GC - UDMA event in register, User chooses which events can come to UDMA as reference events, support up to 4 choices */
#define UDMA_GC_EVTIN_CHOICE0_MASK                  (0xFFU)
#define UDMA_GC_EVTIN_CHOICE0_SHIFT                 (0U)
#define UDMA_GC_EVTIN_CHOICE0(x)                    (((uint32_t)(((uint32_t)(x)) << UDMA_GC_EVTIN_CHOICE0_SHIFT)) & UDMA_GC_EVTIN_CHOICE0_MASK)

#define UDMA_GC_EVTIN_CHOICE1_MASK                  (0xFF00U)
#define UDMA_GC_EVTIN_CHOICE1_SHIFT                 (8U)
#define UDMA_GC_EVTIN_CHOICE1(x)                    (((uint32_t)(((uint32_t)(x)) << UDMA_GC_EVTIN_CHOICE1_SHIFT)) & UDMA_GC_EVTIN_CHOICE1_MASK)

#define UDMA_GC_EVTIN_CHOICE2_MASK                  (0xFF0000U)
#define UDMA_GC_EVTIN_CHOICE2_SHIFT                 (16U)
#define UDMA_GC_EVTIN_CHOICE2(x)                    (((uint32_t)(((uint32_t)(x)) << UDMA_GC_EVTIN_CHOICE2_SHIFT)) & UDMA_GC_EVTIN_CHOICE2_MASK)

#define UDMA_GC_EVTIN_CHOICE3_MASK                  (0xFF000000)
#define UDMA_GC_EVTIN_CHOICE3_SHIFT                 (24U)
#define UDMA_GC_EVTIN_CHOICE3(x)                    (((uint32_t)(((uint32_t)(x)) << UDMA_GC_EVTIN_CHOICE3_SHIFT)) & UDMA_GC_EVTIN_CHOICE3_MASK)

#define UDMA_GC_EVTIN_MASK(evt_in)                  (evt_in&0xFF)
#define UDMA_GC_EVTIN_SHIFT_ID(id)                  (id*8)

/*!
 * @}
 */ /* end of group UDMA_GC_Register_Masks */


/* UDMA Global configuration - instance base addresses */
/** Global configuration UDMA base address */
#define UDMA_GC_BASE                              (UDMA_CTRL_ADDR)
#define UDMA_GC                            ((UDMA_GC_Type *)UDMA_GC_BASE)

/*!
 * @}
 */ /* end of group UDMA_GC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SPIM Peripheral Access Layer
   ---------------------------------------------------------------------------- */
#include "hal_spi_periph.h"


/* ----------------------------------------------------------------------------
   -- HYPERBUS Peripheral Access Layer
   ---------------------------------------------------------------------------- */
#include "core-v-mcu-memory-map.h"
 #include "core-v-mcu-events.h"
/* #include "periph/hyper_periph.h" */
#define hyperbus(id) ((hyperbus_t *) UDMA_HYPER(id))


/* ----------------------------------------------------------------------------
   -- UART Peripheral Access Layer
   ---------------------------------------------------------------------------- */
#include "hal_uart_periph.h"
#define uart(id) ((uart_t *) UDMA_UART(id))


/* ----------------------------------------------------------------------------
   -- I2C Peripheral Access Layer
   ---------------------------------------------------------------------------- */
#include "hal_i2c_periph.h"
#define i2c(id) ((i2c_t *) UDMA_I2C(id))


/* ----------------------------------------------------------------------------
   -- DMACPY Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/* #include "periph/dmacpy_periph.h" */
#define dmacpy(id) ((dmacpy_t *) UDMA_DMACPY(id))


/* ----------------------------------------------------------------------------
   -- I2S Peripheral Access Layer
   ---------------------------------------------------------------------------- */
//#include "periph/i2s_periph.h"
#define i2s(id) ((i2s_t *) UDMA_I2S(id))


/* ----------------------------------------------------------------------------
   -- CPI Peripheral
   ---------------------------------------------------------------------------- */
/* #include "periph/cpi_periph.h" */
#define cpi(id) ((cpi_t *) UDMA_CPI(id))



/* ----------------------------------------------------------------------------
   -- SOC_CTRL Peripheral
   ---------------------------------------------------------------------------- */
#include "hal_soc_ctrl_periph.h"
#define soc_ctrl ((soc_ctrl_t *) APB_SOC_CTRL_ADDR)

/* TODO: Remove this instance.  */
/* SOC_CTRL - Peripheral instance base addresses */
/** Peripheral SOC_CTRL base address */
#define SOC_CTRL_BASE                                (SOC_PERIPHERALS_ADDR + 0x4000u)


/* ----------------------------------------------------------------------------
   -- PMU CTRL Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMU_CTRL_Peripheral_Access_Layer PMU_CTRL Peripheral Access Layer
 * @{
 */

/** PMU - General Register Layout Typedef */
typedef struct {
  __IO uint32_t RAR_DCDC;                     /**< PMU CTRL control register, offset: 0x000 */
  __IO uint32_t SLEEP_CTRL;                   /**< PMU CTRL sleep control register, offset: 0x004 */
  __IO uint32_t FORCE;                        /**< PMU CTRL register, offset: 0x008 */

} PMU_CTRL_Type;


/* ----------------------------------------------------------------------------
   -- PMU_CTRL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMU_CTRL_Register_Masks PMU_CTRL Register Masks
 * @{
 */
/*! @name RAR_DCDC - PMU control register */
#define PMU_CTRL_RAR_DCDC_NV_MASK         (0x1FU)
#define PMU_CTRL_RAR_DCDC_NV_SHIFT        (0U)
#define PMU_CTRL_RAR_DCDC_NV(x)           (((uint32_t)(((uint32_t)(x)) /* << PMU_CTRL_RAR_DCDC_NV_SHIFT*/)) & PMU_CTRL_RAR_DCDC_NV_MASK)
#define READ_PMU_CTRL_RAR_DCDC_NV(x)      (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_RAR_DCDC_NV_MASK)) /*>> PMU_CTRL_RAR_DCDC_NV_SHIFT*/)
#define PMU_CTRL_RAR_DCDC_MV_MASK         (0x1F00U)
#define PMU_CTRL_RAR_DCDC_MV_SHIFT        (8U)
#define PMU_CTRL_RAR_DCDC_MV(x)           (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_RAR_DCDC_MV_SHIFT)) & PMU_CTRL_RAR_DCDC_MV_MASK)
#define READ_PMU_CTRL_RAR_DCDC_MV(x)      (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_RAR_DCDC_MV_MASK)) >> PMU_CTRL_RAR_DCDC_MV_SHIFT)
#define PMU_CTRL_RAR_DCDC_LV_MASK         (0x1F0000U)
#define PMU_CTRL_RAR_DCDC_LV_SHIFT        (16U)
#define PMU_CTRL_RAR_DCDC_LV(x)           (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_RAR_DCDC_LV_SHIFT)) & PMU_CTRL_RAR_DCDC_LV_MASK)
#define READ_PMU_CTRL_RAR_DCDC_LV(x)      (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_RAR_DCDC_LV_MASK)) >> PMU_CTRL_RAR_DCDC_LV_SHIFT)
#define PMU_CTRL_RAR_DCDC_RV_MASK         (0x1F000000U)
#define PMU_CTRL_RAR_DCDC_RV_SHIFT        (24U)
#define PMU_CTRL_RAR_DCDC_RV(x)           (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_RAR_DCDC_RV_SHIFT)) & PMU_CTRL_RAR_DCDC_RV_MASK)
#define READ_PMU_CTRL_RAR_DCDC_RV(x)      (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_RAR_DCDC_RV_MASK)) >> PMU_CTRL_RAR_DCDC_RV_SHIFT)

/*! @name SLEEP_CTRL - PMU control register */
#define PMU_CTRL_SLEEP_CTRL_CFG_MEM_RET_MASK         (0xFU)
#define PMU_CTRL_SLEEP_CTRL_CFG_MEM_RET_SHIFT        (0U)
#define PMU_CTRL_SLEEP_CTRL_CFG_MEM_RET(x)           (((uint32_t)(((uint32_t)(x)) /* << PMU_CTRL_SLEEP_CTRL_CFG_MEM_RET_SHIFT*/)) & PMU_CTRL_SLEEP_CTRL_CFG_MEM_RET_MASK)
#define READ_PMU_CTRL_SLEEP_CTRL_CFG_MEM_RET(x)      (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_SLEEP_CTRL_CFG_MEM_RET_MASK)) /*>> PMU_CTRL_SLEEP_CTRL_CFG_MEM_RET_SHIFT*/)

#define PMU_CTRL_SLEEP_CTRL_CFG_FLL_SOC_RET_MASK     (0x10U)
#define PMU_CTRL_SLEEP_CTRL_CFG_FLL_SOC_RET_SHIFT    (4U)
#define PMU_CTRL_SLEEP_CTRL_CFG_FLL_SOC_RET(x)       (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_SLEEP_CTRL_CFG_FLL_SOC_RET_SHIFT)) & PMU_CTRL_SLEEP_CTRL_CFG_FLL_SOC_RET_MASK)
#define READ_PMU_CTRL_SLEEP_CTRL_CFG_FLL_SOC_RET(x)  (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_SLEEP_CTRL_CFG_FLL_SOC_RET_MASK)) >> PMU_CTRL_SLEEP_CTRL_CFG_FLL_SOC_RET_SHIFT)

#define PMU_CTRL_SLEEP_CTRL_CFG_FLL_CLUSTER_RET_MASK  (0x20U)
#define PMU_CTRL_SLEEP_CTRL_CFG_FLL_CLUSTER_RET_SHIFT (5U)
#define PMU_CTRL_SLEEP_CTRL_CFG_FLL_CLUSTER_RET(x)    (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_SLEEP_CTRL_CFG_FLL_CLUSTER_RET_SHIFT)) & PMU_CTRL_SLEEP_CTRL_CFG_FLL_CLUSTER_RET_MASK)
#define READ_PMU_CTRL_SLEEP_CTRL_CFG_FLL_CLUSTER_RET(x)   (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_SLEEP_CTRL_CFG_FLL_CLUSTER_RET_MASK)) >> PMU_CTRL_SLEEP_CTRL_CFG_FLL_CLUSTER_RET_SHIFT)

#define PMU_CTRL_SLEEP_CTRL_EXT_WAKE_SEL_MASK      (0x7C0U)
#define PMU_CTRL_SLEEP_CTRL_EXT_WAKE_SEL_SHIFT     (6U)
#define PMU_CTRL_SLEEP_CTRL_EXT_WAKE_SEL(x)        (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_SLEEP_CTRL_EXT_WAKE_SEL_SHIFT)) & PMU_CTRL_SLEEP_CTRL_EXT_WAKE_SEL_MASK)
#define READ_PMU_CTRL_SLEEP_CTRL_EXT_WAKE_SEL(x)   (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_SLEEP_CTRL_EXT_WAKE_SEL_MASK)) >> PMU_CTRL_SLEEP_CTRL_EXT_WAKE_SEL_SHIFT)

#define PMU_CTRL_SLEEP_CTRL_EXT_WAKE_TYPE_MASK     (0x1800U)
#define PMU_CTRL_SLEEP_CTRL_EXT_WAKE_TYPE_SHIFT    (11U)
#define PMU_CTRL_SLEEP_CTRL_EXT_WAKE_TYPE(x)       (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_SLEEP_CTRL_EXT_WAKE_TYPE_SHIFT)) & PMU_CTRL_SLEEP_CTRL_EXT_WAKE_TYPE_MASK)
#define READ_PMU_CTRL_SLEEP_CTRL_EXT_WAKE_TYPE(x)  (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_SLEEP_CTRL_EXT_WAKE_TYPE_MASK)) >> PMU_CTRL_SLEEP_CTRL_EXT_WAKE_TYPE_SHIFT)

#define PMU_CTRL_SLEEP_CTRL_EXT_WAKE_EN_MASK       (0x2000U)
#define PMU_CTRL_SLEEP_CTRL_EXT_WAKE_EN_SHIFT      (13U)
#define PMU_CTRL_SLEEP_CTRL_EXT_WAKE_EN(x)         (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_SLEEP_CTRL_EXT_WAKE_EN_SHIFT)) & PMU_CTRL_SLEEP_CTRL_EXT_WAKE_EN_MASK)
#define READ_PMU_CTRL_SLEEP_CTRL_EXT_WAKE_EN(x)    (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_SLEEP_CTRL_EXT_WAKE_EN_MASK)) >> PMU_CTRL_SLEEP_CTRL_EXT_WAKE_EN_SHIFT)

#define PMU_CTRL_SLEEP_CTRL_WAKEUP_MASK            (0xC000U)
#define PMU_CTRL_SLEEP_CTRL_WAKEUP_SHIFT           (14U)
#define PMU_CTRL_SLEEP_CTRL_WAKEUP(x)              (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_SLEEP_CTRL_WAKEUP_SHIFT)) & PMU_CTRL_SLEEP_CTRL_WAKEUP_MASK)
#define READ_PMU_CTRL_SLEEP_CTRL_WAKEUP(x)         (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_SLEEP_CTRL_WAKEUP_MASK)) >> PMU_CTRL_SLEEP_CTRL_WAKEUP_SHIFT)

#define PMU_CTRL_SLEEP_CTRL_BOOT_L2_MASK           (0x10000U)
#define PMU_CTRL_SLEEP_CTRL_BOOT_L2_SHIFT          (16U)
#define PMU_CTRL_SLEEP_CTRL_BOOT_L2(x)             (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_SLEEP_CTRL_BOOT_L2_SHIFT)) & PMU_CTRL_SLEEP_CTRL_BOOT_L2_MASK)
#define READ_PMU_CTRL_SLEEP_CTRL_BOOT_L2(x)        (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_SLEEP_CTRL_BOOT_L2_MASK)) >> PMU_CTRL_SLEEP_CTRL_BOOT_L2_SHIFT)

#define PMU_CTRL_SLEEP_CTRL_REBOOT_MASK            (0xC0000U)
#define PMU_CTRL_SLEEP_CTRL_REBOOT_SHIFT           (18U)
#define PMU_CTRL_SLEEP_CTRL_REBOOT(x)              (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_SLEEP_CTRL_REBOOT_SHIFT)) & PMU_CTRL_SLEEP_CTRL_REBOOT_MASK)
#define READ_PMU_CTRL_SLEEP_CTRL_REBOOT(x)         (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_SLEEP_CTRL_REBOOT_MASK)) >> PMU_CTRL_SLEEP_CTRL_REBOOT_SHIFT)

#define PMU_CTRL_SLEEP_CTRL_CLUSTER_WAKEUP_MASK      (0x100000U)
#define PMU_CTRL_SLEEP_CTRL_CLUSTER_WAKEUP_SHIFT     (20U)
#define PMU_CTRL_SLEEP_CTRL_CLUSTER_WAKEUP(x)        (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_SLEEP_CTRL_CLUSTER_WAKEUP_SHIFT)) & PMU_CTRL_SLEEP_CTRL_CLUSTER_WAKEUP_MASK)
#define READ_PMU_CTRL_SLEEP_CTRL_CLUSTER_WAKEUP(x)   (((uint32_t)(((uint32_t)(x)) & PMU_CTRL_SLEEP_CTRL_CLUSTER_WAKEUP_MASK)) >> PMU_CTRL_SLEEP_CTRL_CLUSTER_WAKEUP_SHIFT)

/*! @name FORCE - PMU control register */
#define PMU_CTRL_FORCE_MEM_RET_MASK                (0xFU)
#define PMU_CTRL_FORCE_MEM_RET_SHIFT               (0U)
#define PMU_CTRL_FORCE_MEM_RET(x)                  (((uint32_t)(((uint32_t)(x)) /* << PMU_CTRL_FORCE_MEM_RET_SHIFT*/)) & PMU_CTRL_FORCE_MEM_RET_MASK)

#define PMU_CTRL_FORCE_MEM_PWD_MASK                (0xF0U)
#define PMU_CTRL_FORCE_MEM_PWD_SHIFT               (4U)
#define PMU_CTRL_FORCE_MEM_PWD(x)                  (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_FORCE_MEM_PWD_SHIFT)) & PMU_CTRL_FORCE_MEM_PWD_MASK)

#define PMU_CTRL_FORCE_FLL_CLUSTER_RET_MASK        (0x100U)
#define PMU_CTRL_FORCE_FLL_CLUSTER_RET_SHIFT       (8U)
#define PMU_CTRL_FORCE_FLL_CLUSTER_RET(x)          (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_FORCE_FLL_CLUSTER_RET_SHIFT)) & PMU_CTRL_FORCE_FLL_CLUSTER_RET_MASK)

#define PMU_CTRL_FORCE_FLL_CLUSTER_PWD_MASK        (0x200U)
#define PMU_CTRL_FORCE_FLL_CLUSTER_PWD_SHIFT       (9U)
#define PMU_CTRL_FORCE_FLL_CLUSTER_PWD(x)          (((uint32_t)(((uint32_t)(x)) << PMU_CTRL_FORCE_FLL_CLUSTER_PWD_SHIFT)) & PMU_CTRL_FORCE_FLL_CLUSTER_PWD_MASK)

/*!
 * @}
 */ /* end of group PMU_CTRL_Register_Masks */


/* PMU CTRL- Peripheral instance base addresses */
/** Peripheral PMU CTRL base address */
#define PMU_CTRL_BASE                               (SOC_CTRL_BASE + 0x0100u)
/** Peripheral PMU_CTRL0 base pointer */
#define PMU_CTRL                                    ((PMU_CTRL_Type *)PMU_CTRL_BASE)
/** Array initializer of PMU_CTRL base addresses */
#define PMU_CTRL_BASE_ADDRS                         { PMU_CTRL_BASE }
/** Array initializer of PMU_CTRL base pointers */
#define PMU_CTRL_BASE_PTRS                          { PMU_CTRL }

/*!
 * @}
 */ /* end of group PMU_CTRL_Peripheral_Access_Layer */



/* ----------------------------------------------------------------------------
   -- PORT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Peripheral_Access_Layer PORT Peripheral Access Layer
 * @{
 */

/** PORT - Register Layout Typedef */
typedef struct {
  __IO  uint32_t PADFUN[4];                       /**< PORT pad function register 0, offset: 0x000 */
  __IO  uint32_t SLEEP_PADCFG[4];                 /**< PORT sleep pad configuration register 0, offset: 0x010 */
  __IO  uint32_t PAD_SLEEP;                       /**< PORT pad sleep register, offset: 0x020 */
  __IO  uint32_t _reserved0[7];                   /**< reserved, offset: 0x010 */
  __IO  uint32_t PADCFG[16];                      /**< PORT pad configuration register 0, offset: 0x040 */

} PORT_Type;

/* ----------------------------------------------------------------------------
   -- PORT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Masks GPIO Register Masks
 * @{
 */
#define GPIO_NUM                                 32

/*! @name PADFUN - GPIO pad mux registers */
#define PORT_PADFUN_MUX_MASK                     (0x3U)
#define PORT_PADFUN_MUX_SHIFT                    (0U)
#define PORT_PADFUN_MUX(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_PADFUN_MUX_SHIFT)) & PORT_PADFUN_MUX_MASK)

/*! @name PADCFG - GPIO pad configuration registers */
#define PORT_PADCFG_PULL_EN_MASK                 (0x1U)
#define PORT_PADCFG_PULL_EN_SHIFT                (0U)
#define PORT_PADCFG_PULL_EN(x)                   (((uint32_t)(((uint32_t)(x)) << PORT_PADCFG_PULL_EN_SHIFT)) & PORT_PADCFG_PULL_EN_MASK)
#define PORT_PADCFG_DRIVE_STRENGTH_MASK          (0x2U)
#define PORT_PADCFG_DRIVE_STRENGTH_SHIFT         (1U)
#define PORT_PADCFG_DRIVE_STRENGTH(x)            (((uint32_t)(((uint32_t)(x)) << PORT_PADCFG_DRIVE_STRENGTH_SHIFT)) & PORT_PADCFG_DRIVE_STRENGTH_MASK)

/*!
 * @}
 */ /* end of group PORT_Register_Masks */


/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base address */
#define PORTA_BASE                              (SOC_CTRL_BASE + 0x0140u)
/** Peripheral PORTA base pointer */
#define PORTA                                   ((PORT_Type *)PORTA_BASE)
/** Array initializer of PORT base addresses */
#define PORT_BASE_ADDRS                         { PORTA_BASE }
/** Array initializer of PORT base pointers */
#define PORT_BASE_PTRS                          { PORTA }

/*!
 * @}
 */ /* end of group PORT_Access_Layer */



/* ----------------------------------------------------------------------------
   -- IO POWER DOMAINS ISOLATION Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IO_ISO_Peripheral_Access_Layer IO_ISO Peripheral Access Layer
 * @{
 */

/** IO_ISO - Register Layout Typedef */
typedef struct {
  __IO  uint32_t GPIO_ISO;                       /**< IO_ISO GPIO power domains isolation, offset: 0x000 */
  __IO  uint32_t CAM_ISO;                        /**< IO_ISO Cemera power domains isolation, offset: 0x004 */
  __IO  uint32_t LVDS_ISO;                       /**< IO_ISO LVDS power domains isolation, offset: 0x008 */

} IO_ISO_Type;

/* ----------------------------------------------------------------------------
   -- IO_ISO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IO_ISO_Register_Masks GPIO Register Masks
 * @{
 */
#define IO_ISO_GPIO_ISO_MASK                 (0x1U)
#define IO_ISO_GPIO_ISO_SHIFT                (0U)
#define IO_ISO_GPIO_ISO(x)                   (((uint32_t)(((uint32_t)(x)) /* << IO_ISO_GPIO_ISO_SHIFT */)) & IO_ISO_GPIO_ISO_MASK)

#define IO_ISO_CAM_ISO_MASK                 (0x1U)
#define IO_ISO_CAM_ISO_SHIFT                (0U)
#define IO_ISO_CAM_ISO(x)                   (((uint32_t)(((uint32_t)(x)) /* << IO_ISO_CAM_ISO_SHIFT */)) & IO_ISO_CAM_ISO_MASK)

#define IO_ISO_LVDS_ISO_MASK                 (0x1U)
#define IO_ISO_LVDS_ISO_SHIFT                (0U)
#define IO_ISO_LVDS_ISO(x)                   (((uint32_t)(((uint32_t)(x)) /* << IO_ISO_LVDS_ISO_SHIFT */)) & IO_ISO_LVDS_ISO_MASK)


/*!
 * @}
 */ /* end of group IO_ISO_Register_Masks */


/* IO_ISO - Peripheral instance base addresses */
/** Peripheral IO_ISO base address */
#define IO_ISO_BASE                               (SOC_CTRL_BASE + 0x01C0u)
/** Peripheral IO_ISO base pointer */
#define IO_ISO                                    ((IO_ISO_Type *)IO_ISO_BASE)
/** Array initializer of IO_ISO base addresses */
#define IO_ISO_BASE_ADDRS                         { IO_ISO_BASE }
/** Array initializer of IO_ISO base pointers */
#define IO_ISO_BASE_PTRS                          { IO_ISO }

/*!
 * @}
 */ /* end of group IO_ISO_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PWM Peripheral
   ---------------------------------------------------------------------------- */
#include "hal_pwm_periph.h"
#include "hal_pwm_ctrl_periph.h"
#define pwm(id) ((pwm_t *) (ADV_TIMER_ADDR + (id << 6)))
#define pwm_ctrl ((pwm_ctrl_t *) (ADV_TIMER_ADDR + 0x100))



/* ----------------------------------------------------------------------------
   -- SOCEU (SOC EVENT UNIT) Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SOCEU_Peripheral_Access_Layer SOCEU Peripheral Access Layer
 * @{
 */

/** SOCEU - Register Layout Typedef */
typedef struct {
  __IO  uint32_t EVENT;                          /**< SOCEU event register, offset: 0x00 */
  __IO  uint32_t FC_MASK0;                       /**< SOCEU fc mask 0 register, offset: 0x04 */
  __IO  uint32_t FC_MASK1;                       /**< SOCEU fc mask 1 register, offset: 0x08 */
  __IO  uint32_t FC_MASK2;                       /**< SOCEU fc mask 2 register, offset: 0x0c */
  __IO  uint32_t FC_MASK3;                       /**< SOCEU fc mask 3 register, offset: 0x10 */
  __IO  uint32_t FC_MASK4;                       /**< SOCEU fc mask 4 register, offset: 0x14 */
  __IO  uint32_t FC_MASK5;                       /**< SOCEU fc mask 5 register, offset: 0x18 */
  __IO  uint32_t FC_MASK6;                       /**< SOCEU fc mask 6 register, offset: 0x1c */
  __IO  uint32_t FC_MASK7;                       /**< SOCEU fc mask 7 register, offset: 0x20 */
  __IO  uint32_t CL_MASK0;                       /**< SOCEU cluster mask 0 register, offset: 0x24 */
  __IO  uint32_t CL_MASK1;                       /**< SOCEU cluster mask 1 register, offset: 0x28 */
  __IO  uint32_t CL_MASK2;                       /**< SOCEU cluster mask 2 register, offset: 0x2C */
  __IO  uint32_t CL_MASK3;                       /**< SOCEU cluster mask 3 register, offset: 0x30 */
  __IO  uint32_t CL_MASK4;                       /**< SOCEU cluster mask 4 register, offset: 0x34 */
  __IO  uint32_t CL_MASK5;                       /**< SOCEU cluster mask 5 register, offset: 0x38 */
  __IO  uint32_t CL_MASK6;                       /**< SOCEU cluster mask 6 register, offset: 0x3C */
  __IO  uint32_t CL_MASK7;                       /**< SOCEU cluster mask 7 register, offset: 0x40 */
  __IO  uint32_t PR_MASK0;                       /**< SOCEU propagate mask MSB register, offset: 0x44 */
  __IO  uint32_t PR_MASK1;                       /**< SOCEU propagate mask MSB register, offset: 0x48 */
  __IO  uint32_t PR_MASK2;                       /**< SOCEU propagate mask MSB register, offset: 0x4c */
  __IO  uint32_t PR_MASK3;                       /**< SOCEU propagate mask MSB register, offset: 0x50 */
  __IO  uint32_t PR_MASK4;                       /**< SOCEU propagate mask MSB register, offset: 0x54 */
  __IO  uint32_t PR_MASK5;                       /**< SOCEU propagate mask MSB register, offset: 0x58 */
  __IO  uint32_t PR_MASK6;                       /**< SOCEU propagate mask MSB register, offset: 0x5c */
  __IO  uint32_t PR_MASK7;                       /**< SOCEU propagate mask MSB register, offset: 0x60 */
  __IO  uint32_t ERR_MASK0;                      /**< SOCEU error mask MSB register, offset: 0x64 */
  __IO  uint32_t ERR_MASK1;                      /**< SOCEU error mask MSB register, offset: 0x68 */
  __IO  uint32_t ERR_MASK2;                      /**< SOCEU error mask MSB register, offset: 0x6c */
  __IO  uint32_t ERR_MASK3;                      /**< SOCEU error mask MSB register, offset: 0x70 */
  __IO  uint32_t ERR_MASK4;                      /**< SOCEU error mask MSB register, offset: 0x74 */
  __IO  uint32_t ERR_MASK5;                      /**< SOCEU error mask MSB register, offset: 0x78 */
  __IO  uint32_t ERR_MASK6;                      /**< SOCEU error mask MSB register, offset: 0x7c */
  __IO  uint32_t ERR_MASK7;                      /**< SOCEU error mask MSB register, offset: 0x80 */
  __IO  uint32_t TIMER_SEL_HI;                   /**< SOCEU timer high register, offset: 0x84 */
  __IO  uint32_t TIMER_SEL_LO;                   /**< SOCEU timer low register, offset: 0x88 */
} SOCEU_Type;

#define SOC_EVENT_OFFSET 0x00
#define SOC_FC_MASK0_OFFSET 0x04
#define SOC_CL_MASK0_OFFSET 0x24
#define SOC_PR_MASK0_OFFSET 0x44
#define SOC_ERR_MASK0_OFFSET 0x64

/* ----------------------------------------------------------------------------
   -- SOCEU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SOCEU_Register_Masks SOCEU Register Masks
 * @{
 */
/* The SOC events number */
#define SOC_EVENTS_NUM              0x08
/*!
 * @}
 */ /* end of group SOCEU_Register_Masks */


/* SOCEU - Peripheral instance base addresses */
/** Peripheral SOCEU base address */
#define SOCEU_BASE                               SOC_EU_ADDR
/** Peripheral SOCEU base pointer */
#define SOCEU                                    ((SOCEU_Type *)SOCEU_BASE)
/** Array initializer of SOCEU base addresses */
#define SOCEU_BASE_ADDRS                         { SOCEU_BASE }
/** Array initializer of SOCEU base pointers */
#define SOCEU_BASE_PTRS                          { SOCEU }

/*!
 * @}
 */ /* end of group SOCEU_Peripheral_Access_Layer */



/* ----------------------------------------------------------------------------
   -- SW EVENT TRIGGER Register Address
   ---------------------------------------------------------------------------- */

#define EU_EVT_GETCLUSTERBASE(coreId)     (0x00200800u + (coreId << 6))


/* ----------------------------------------------------------------------------
   -- PMU DLC Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMU_DLC_Peripheral_Access_Layer PMU_DLC Peripheral Access_Layer
 * @{
 */

/** PMU - General Register Layout Typedef */
typedef struct {
  __IO uint32_t PCTRL;                          /**< PMU DLC control register, offset: 0x00 */
  __IO uint32_t PRDATA;                         /**< PMU DLC data register, offset: 0x04 */
  __IO uint32_t DLC_SR;                         /**< PMU DLC register, offset: 0x08 */
  __IO uint32_t DLC_IMR;                        /**< PMU DLC register, offset: 0x0C */
  __IO uint32_t DLC_IFR;                        /**< PMU DLC register, offset: 0x10 */
  __IO uint32_t DLC_IOIFR;                      /**< PMU DLC register, offset: 0x14 */
  __IO uint32_t DLC_IDIFR;                      /**< PMU DLC register, offset: 0x18 */
  __IO uint32_t DLC_IMCIFR;                     /**< PMU DLC register, offset: 0x1C */

} PMU_DLC_Type;

/* ----------------------------------------------------------------------------
   -- SOCEU Register Masks
   ---------------------------------------------------------------------------- */
/*!
 * @addtogroup PMU_DLC_Register_Masks PMU_DLC Register Masks
 * @{
 */

/*! @name PCTRL - PMU DLC PICL control register */
#define PMU_DLC_PCTRL_START_MASK              (0x1U)
#define PMU_DLC_PCTRL_START_SHIFT             (0U)
#define PMU_DLC_PCTRL_START(x)                (((uint32_t)(((uint32_t)(x)) /* << PMU_DLC_PCTRL_START_SHIFT */)) & PMU_DLC_PCTRL_START_MASK)
#define PMU_DLC_PCTRL_PADDR_MASK              (0x7FFEU)
#define PMU_DLC_PCTRL_PADDR_SHIFT             (1U)
#define PMU_DLC_PCTRL_PADDR(x)                (((uint32_t)(((uint32_t)(x)) << PMU_DLC_PCTRL_PADDR_SHIFT)) & PMU_DLC_PCTRL_PADDR_MASK)
#define PMU_DLC_PCTRL_DIR_MASK                (0x8000U)
#define PMU_DLC_PCTRL_DIR_SHIFT               (15U)
#define PMU_DLC_PCTRL_DIR(x)                  (((uint32_t)(((uint32_t)(x)) << PMU_DLC_PCTRL_DIR_SHIFT)) & PMU_DLC_PCTRL_DIR_MASK)
#define PMU_DLC_PCTRL_PWDATA_MASK             (0xFFFF0000U)
#define PMU_DLC_PCTRL_PWDATA_SHIFT            (16U)
#define PMU_DLC_PCTRL_PWDATA(x)               (((uint32_t)(((uint32_t)(x)) << PMU_DLC_PCTRL_PWDATA_SHIFT)) & PMU_DLC_PCTRL_PWDATA_MASK)

/*! @name PRDATA - PMU DLC PICL data read register */
#define PMU_DLC_PRDATA_PRDATA_MASK            (0xFFU)
#define PMU_DLC_PRDATA_PRDATA_SHIFT           (0U)
#define PMU_DLC_PRDATA_PRDATA(x)              (((uint32_t)(((uint32_t)(x)) /* << PMU_DLC_PRDATA_PRDATA_SHIFT */)) & PMU_DLC_PRDATA_PRDATA_MASK)

/*! @name SR - PMU DLC DLC Status register */
#define PMU_DLC_SR_PICL_BUSY_MASK             (0x1U)
#define PMU_DLC_SR_PICL_BUSY_SHIFT            (0U)
#define PMU_DLC_SR_PICL_BUSY(x)               (((uint32_t)(((uint32_t)(x)) /* << PMU_DLC_SR_PICL_BUSY_SHIFT */)) & PMU_DLC_SR_PICL_BUSY_MASK)
#define PMU_DLC_SR_SCU_BUSY_MASK              (0x2U)
#define PMU_DLC_SR_SCU_BUSY_SHIFT             (1U)
#define PMU_DLC_SR_SCU_BUSY(x)                (((uint32_t)(((uint32_t)(x)) << PMU_DLC_SR_SCU_BUSY_SHIFT)) & PMU_DLC_SR_SCU_BUSY_MASK)

/*! @name IMR - PMU DLC Interrupt mask register */
#define PMU_DLC_IMR_ICU_OK_MASK_MASK          (0x1U)
#define PMU_DLC_IMR_ICU_OK_MASK_SHIFT         (0U)
#define PMU_DLC_IMR_ICU_OK_MASK(x)            (((uint32_t)(((uint32_t)(x)) /* << PMU_DLC_IMR_ICU_OK_MASK_SHIFT */)) & PMU_DLC_IMR_ICU_OK_MASK_MASK)
#define PMU_DLC_IMR_ICU_DELAYED_MASK_MASK     (0x2U)
#define PMU_DLC_IMR_ICU_DELAYED_MASK_SHIFT    (1U)
#define PMU_DLC_IMR_ICU_DELAYED_MASK(x)       (((uint32_t)(((uint32_t)(x)) << PMU_DLC_IMR_ICU_DELAYED_MASK_SHIFT)) & PMU_DLC_IMR_ICU_DELAYED_MASK_MASK)
#define PMU_DLC_IMR_ICU_MODE_CHANGED_MASK_MASK     (0x4U)
#define PMU_DLC_IMR_ICU_MODE_CHANGED_MASK_SHIFT    (2U)
#define PMU_DLC_IMR_ICU_MODE_CHANGED_MASK(x)       (((uint32_t)(((uint32_t)(x)) << PMU_DLC_IMR_ICU_MODE_CHANGED_MASK_SHIFT)) & PMU_DLC_IMR_ICU_MODE_CHANGED_MASK_MASK)
#define PMU_DLC_IMR_PICL_OK_MASK_MASK         (0x8U)
#define PMU_DLC_IMR_PICL_OK_MASK_SHIFT        (3U)
#define PMU_DLC_IMR_PICL_OK_MASK(x)           (((uint32_t)(((uint32_t)(x)) << PMU_DLC_IMR_PICL_OK_MASK_SHIFT)) & PMU_DLC_IMR_PICL_OK_MASK_MASK)
#define PMU_DLC_IMR_SCU_OK_MASK_MASK          (0x10U)
#define PMU_DLC_IMR_SCU_OK_MASK_SHIFT         (4U)
#define PMU_DLC_IMR_SCU_OK_MASK(x)            (((uint32_t)(((uint32_t)(x)) << PMU_DLC_IMR_SCU_OK_MASK_SHIFT)) & PMU_DLC_IMR_SCU_OK_MASK_MASK)

/*! @name IFR - PMU DLC Interrupt flag register */
#define PMU_DLC_IFR_ICU_OK_FLAG_MASK          (0x1U)
#define PMU_DLC_IFR_ICU_OK_FLAG_SHIFT         (0U)
#define PMU_DLC_IFR_ICU_OK_FLAG(x)            (((uint32_t)(((uint32_t)(x)) /* << PMU_DLC_IFR_ICU_OK_FLAG_SHIFT */)) & PMU_DLC_IFR_ICU_OK_FLAG_MASK)
#define PMU_DLC_IFR_ICU_DELAYED_FLAG_MASK     (0x2U)
#define PMU_DLC_IFR_ICU_DELAYED_FLAG_SHIFT    (1U)
#define PMU_DLC_IFR_ICU_DELAYED_FLAG(x)       (((uint32_t)(((uint32_t)(x)) << PMU_DLC_IFR_ICU_DELAYED_FLAG_SHIFT)) & PMU_DLC_IFR_ICU_DELAYED_FLAG_MASK)
#define PMU_DLC_IFR_ICU_MODE_CHANGED_FLAG_MASK     (0x4U)
#define PMU_DLC_IFR_ICU_MODE_CHANGED_FLAG_SHIFT    (2U)
#define PMU_DLC_IFR_ICU_MODE_CHANGED_FLAG(x)       (((uint32_t)(((uint32_t)(x)) << PMU_DLC_IFR_ICU_MODE_CHANGED_FLAG_SHIFT)) & PMU_DLC_IFR_ICU_MODE_CHANGED_FLAG_MASK)
#define PMU_DLC_IFR_PICL_OK_FLAG_MASK         (0x8U)
#define PMU_DLC_IFR_PICL_OK_FLAG_SHIFT        (3U)
#define PMU_DLC_IFR_PICL_OK_FLAG(x)           (((uint32_t)(((uint32_t)(x)) << PMU_DLC_IFR_PICL_OK_FLAG_SHIFT)) & PMU_DLC_IFR_PICL_OK_FLAG_MASK)
#define PMU_DLC_IFR_SCU_OK_FLAG_MASK          (0x10U)
#define PMU_DLC_IFR_SCU_OK_FLAG_SHIFT         (4U)
#define PMU_DLC_IFR_SCU_OK_FLAG(x)            (((uint32_t)(((uint32_t)(x)) << PMU_DLC_IFR_SCU_OK_FLAG_SHIFT)) & PMU_DLC_IFR_SCU_OK_FLAG_MASK)

/*! @name IOIFR - PMU DLC icu_ok interrupt flag register */
#define PMU_DLC_IOIFR_ICU_OK_FLAG_MASK          (0xFFFFFFFEU)
#define PMU_DLC_IOIFR_ICU_OK_FLAG_SHIFT         (1U)
#define PMU_DLC_IOIFR_ICU_OK_FLAG(x)            (((uint32_t)(((uint32_t)(x)) << PMU_DLC_IOIFR_ICU_OK_FLAG_SHIFT)) & PMU_DLC_IOIFR_ICU_OK_FLAG_MASK)

/*! @name IDIFR - PMU DLC icu_delayed interrupt flag register */
#define PMU_DLC_IDIFR_ICU_DELAYED_FLAG_MASK     (0xFFFFFFFEU)
#define PMU_DLC_IDIFR_ICU_DELAYED_FLAG_SHIFT    (1U)
#define PMU_DLC_IDIFR_ICU_DELAYED_FLAG(x)       (((uint32_t)(((uint32_t)(x)) << PMU_DLC_IDIFR_ICU_DELAYED_FLAG_SHIFT)) & PMU_DLC_IDIFR_ICU_DELAYED_FLAG_MASK)

/*! @name IMCIFR - PMU DLC icu_mode changed interrupt flag register */
#define PMU_DLC_IMCIFR_ICU_MODE_CHANGED_FLAG_MASK     (0xFFFFFFFEU)
#define PMU_DLC_IMCIFR_ICU_MODE_CHANGED_FLAG_SHIFT    (1U)
#define PMU_DLC_IMCIFR_ICU_MODE_CHANGED_FLAG(x)       (((uint32_t)(((uint32_t)(x)) << PMU_DLC_IMCIFR_ICU_MODE_CHANGED_FLAG_SHIFT)) & PMU_DLC_IMCIFR_ICU_MODE_CHANGED_FLAG_MASK)

/*! @name PCTRL_PADDR The address to write in the DLC_PADDR register is CHIP_SEL_ADDR[4:0] concatenated with REG_ADDR[4:0]. */
#define PMU_DLC_PICL_REG_ADDR_MASK          (0x1FU)
#define PMU_DLC_PICL_REG_ADDR_SHIFT         (0U)
#define PMU_DLC_PICL_REG_ADDR(x)            (((uint32_t)(((uint32_t)(x)) /* << PMU_DLC_PICL_REG_ADDR_SHIFT */)) & PMU_DLC_PICL_REG_ADDR_MASK)
#define PMU_DLC_PICL_CHIP_SEL_ADDR_MASK     (0x3E0U)
#define PMU_DLC_PICL_CHIP_SEL_ADDR_SHIFT    (5U)
#define PMU_DLC_PICL_CHIP_SEL_ADDR(x)       (((uint32_t)(((uint32_t)(x)) << PMU_DLC_PICL_CHIP_SEL_ADDR_SHIFT)) & PMU_DLC_PICL_CHIP_SEL_ADDR_MASK)

/* CHIP_SEL_ADDR[4:0]*/
#define  PICL_WIU_ADDR         0x00
#define  PICL_ICU_ADDR         0x01

/* REG_ADDR[4:0]*/
#define  WIU_ISPMR_0           (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x00))
#define  WIU_ISPMR_1           (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x01))
#define  WIU_IFR_0             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x02))
#define  WIU_IFR_1             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x03))
#define  WIU_ICR_0             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x04))
#define  WIU_ICR_1             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x05))
#define  WIU_ICR_2             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x06))
#define  WIU_ICR_3             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x07))
#define  WIU_ICR_4             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x08))
#define  WIU_ICR_5             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x09))
#define  WIU_ICR_6             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x0A))
#define  WIU_ICR_7             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x0B))
#define  WIU_ICR_8             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x0C))
#define  WIU_ICR_9             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x0D))
#define  WIU_ICR_10            (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x0E))
#define  WIU_ICR_11            (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x0F))
#define  WIU_ICR_12            (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x10))
#define  WIU_ICR_13            (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x11))
#define  WIU_ICR_14            (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x12))
#define  WIU_ICR_15            (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_WIU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x13))

/* REG_ADDR[4:0]*/
#define  ICU_CR                (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_ICU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x00))
#define  ICU_MR                (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_ICU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x01))
#define  ICU_ISMR              (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_ICU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x02))
#define  ICU_DMR_0             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_ICU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x03))
#define  ICU_DMA_1             (PMU_DLC_PICL_CHIP_SEL_ADDR(PICL_ICU_ADDR) | PMU_DLC_PICL_REG_ADDR(0x04))

/*!
 * @}
 */ /* end of group PMU_DLC_Register_Masks */

/* PMU DLC- Peripheral instance base addresses */
/** Peripheral PMU DLC base address */
#define PMU_DLC_BASE                                (SOC_PERIPHERALS_ADDR + 0x7000u)
/** Peripheral PMU_DLC base pointer */
#define PMU_DLC                                     ((PMU_DLC_Type *)PMU_DLC_BASE)
/** Array initializer of PMU_DLC base addresses */
#define PMU_DLC_BASE_ADDRS                          { PMU_DLC_BASE }
/** Array initializer of PMU_DLC base pointers */
#define PMU_DLC_BASE_PTRS                           { PMU_DLC }

/*!
 * @}
 */ /* end of group PMU_DLC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RTC_APB Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/* #include "periph/rtc_periph.h" */
/* #define rtc(id) ((rtc_t *) RTC_ADDR) */


/* ----------------------------------------------------------------------------
   -- EFUSE CTRL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EFUSE_CTRL_Peripheral_Access_Layer EFUSE_CTRL Peripheral Access Layer
 * @{
 */



//#include "periph/efuse_periph.h"

/* EFUSE_CTRL - Peripheral instance base addresses */
/** Peripheral EFUSE_CTRL base address */
#define EFUSE_CTRL_BASE                               (SOC_PERIPHERALS_ADDR + 0x09000u)
/** Peripheral EFUSE_CTRL base pointer */
#define efuse_ctrl                                    ((efuse_ctrl_t *)EFUSE_CTRL_BASE)
/** Array initializer of EFUSE_CTRL base addresses */
#define EFUSE_CTRL_BASE_ADDRS                         { EFUSE_CTRL_BASE }
/** Array initializer of EFUSE_CTRL base pointers */
#define EFUSE_CTRL_BASE_PTRS                          { EFUSE_CTRL }

/*!
 * @}
 */ /* end of group EFUSE_CTRL_Peripheral_Access_Layer */


/* EFUSE_REGS - Peripheral instance base addresses */
/** Peripheral EFUSE_REGS base address */
#define EFUSE_REGS_BASE                                (SOC_PERIPHERALS_ADDR + 0x09200u)
/** Peripheral EFUSE_REGS base pointer */
#define efuse_regs                                     ((efuse_regs_t *)EFUSE_REGS_BASE)
#define efuse_regs_array                               ((int32_t*)EFUSE_REGS_BASE)
/** Array initializer of EFUSE_REGS base addresses */
#define EFUSE_REGS_BASE_ADDRS                          { EFUSE_REGS_BASE }
/** Array initializer of EFUSE_REGS base pointers */
#define EFUSE_REGS_BASE_PTRS                           { EFUSE_REGS }/*!
 * @}
 */ /* end of group EFUSE_CTRL_Peripheral_Access_Layer */



/* ----------------------------------------------------------------------------
   -- EFUSE REG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EFUSE_REGS_Peripheral_Access_Layer EFUSE_REGS Peripheral Access Layer
 * @{
 */

/** EFUSE_REGS - Registers Layout Typedef */
typedef struct {
  __IO  uint32_t INFO;                    /**< EFUSE INFO register, offset: 0x000 */
  __IO  uint32_t INFO2;                   /**< EFUSE_INFO2 register, offset: 0x004 */
  __IO  uint32_t AES_KEY[16];             /**< EFUSE_AES_KEY registers, offset: 0x008 */
  __IO  uint32_t AES_IV[8];               /**< EFUSE_AES_IV registers, offset: 0x048 */
  __IO  uint32_t WAIT_XTAL_DELTA_LSB;     /**< EFUSE_WAIT_XTAL_DELTA_LSB register, offset: 0x068 */
  __IO  uint32_t WAIT_XTAL_DELTA_MSB;     /**< EFUSE_WAIT_XTAL_DELTA_MSB register, offset: 0x06C */
  __IO  uint32_t WAIT_XTAL_MIN;           /**< EFUSE_WAIT_XTAL_MIN registers, offset: 0x070 */
  __IO  uint32_t WAIT_XTAL_MAX;           /**< EFUSE_WAIT_XTAL_MAX registers, offset: 0x074 */
  __IO  uint32_t HYPER_RDS_DELAY;         /**< EFUSE_WAIT_XTAL_MAX registers, offset: 0x078 */
  __IO  uint32_t FLL_FREQ;                /**< EFUSE_FLL_FREQ registers, offset: 0x07C */
  __IO  uint32_t FLL_TOLERANCE;           /**< EFUSE_FLL_TOLERANCE registers, offset: 0x080 */
  __IO  uint32_t FLL_ASSERT_CYCLE;        /**< EFUSE_FLL_ASSERT_CYCLE registers, offset: 0x084 */
  __IO  uint32_t _reserved[6];            /**< EFUSE_reserved registers, offset: 0x088 */
  __IO  uint32_t USER_REG[88];            /**< EFUSE_USER_REG, offset: 0x0A0 */
} EFUSE_REGS_Type;

/* ----------------------------------------------------------------------------
   -- EFUSE_REGS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EFUSE_REGS_Register_Masks EFUSE_REGS Register Masks
 * @{
 */
/*! @name INFO - EFUSE information register */
#define EFUSE_INFO_PLT_MASK                           (0x07U)
#define EFUSE_INFO_PLT_SHIFT                          (0U)
#define EFUSE_INFO_PLT(x)                             (((uint32_t)(((uint32_t)(x)) /* << EFUSE_INFO_PLT_SHIFT */)) & EFUSE_INFO_PLT_MASK)

#define EFUSE_INFO_BOOT_MASK                          (0x38U)
#define EFUSE_INFO_BOOT_SHIFT                         (3U)
#define EFUSE_INFO_BOOT(x)                            (((uint32_t)(((uint32_t)(x)) << EFUSE_INFO_BOOT_SHIFT)) & EFUSE_INFO_BOOT_MASK)

#define EFUSE_INFO_ENCRYPTED_MASK                     (0x40U)
#define EFUSE_INFO_ENCRYPTED_SHIFT                    (6U)
#define EFUSE_INFO_ENCRYPTED(x)                       (((uint32_t)(((uint32_t)(x)) << EFUSE_INFO_ENCRYPTED_SHIFT)) & EFUSE_INFO_ENCRYPTED_MASK)

#define EFUSE_INFO_WAIT_XTAL_MASK                     (0x80U)
#define EFUSE_INFO_WAIT_XTAL_SHIFT                    (7U)
#define EFUSE_INFO_WAIT_XTAL(x)                       (((uint32_t)(((uint32_t)(x)) << EFUSE_INFO_WAIT_XTAL_SHIFT)) & EFUSE_INFO_WAIT_XTAL_MASK)


/*!
 * @}
 */ /* end of group EFUSE_REGS_Register_Masks */


/* EFUSE_REGS - Peripheral instance base addresses */
/** Peripheral EFUSE_REGS base address */
#define EFUSE_REGS_BASE                                (SOC_PERIPHERALS_ADDR + 0x09200u)
/** Peripheral EFUSE_REGS base pointer */
#define EFUSE_REGS                                     ((EFUSE_REGS_Type *)EFUSE_REGS_BASE)
/** Array initializer of EFUSE_REGS base addresses */
#define EFUSE_REGS_BASE_ADDRS                          { EFUSE_REGS_BASE }
/** Array initializer of EFUSE_REGS base pointers */
#define EFUSE_REGS_BASE_PTRS                           { EFUSE_REGS }

/*!
 * @}
 */ /* end of group EFUSE_REGS_Peripheral_Access_Layer */



/* ----------------------------------------------------------------------------
   -- FC_STDOUT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FC_STDOUT_Peripheral_Access_Layer FC_STDOUT Peripheral Access Layer
 * @{
 */

/** FC_STDOUT - Registers Layout Typedef */
typedef struct {
  __IO  uint32_t PUTC[16];                    /**< FC_STDOUT INFO register, offset: 0x000 */
} FC_STDOUT_Type;

/* ----------------------------------------------------------------------------
   -- FC_STDOUT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FC_STDOUT_Register_Masks FC_STDOUT Register Masks
 * @{
 */
/*! @name INFO - FC_STDOUT information register */

/*!
 * @}
 */ /* end of group FC_STDOUT_Register_Masks */


/* FC_STDOUT - Peripheral instance base addresses */
/** Peripheral FC_STDOUT base address */
#define FC_STDOUT_BASE                                (SOC_PERIPHERALS_ADDR + 0x10000u + (FC_CLUSTER_ID << 7))
/** Peripheral FC_STDOUT base pointer */
#define FC_STDOUT                                     ((FC_STDOUT_Type *)FC_STDOUT_BASE)
/** Array initializer of FC_STDOUT base addresses */
#define FC_STDOUT_BASE_ADDRS                          { FC_STDOUT_BASE }
/** Array initializer of FC_STDOUT base pointers */
#define FC_STDOUT_BASE_PTRS                           { FC_STDOUT }

/*!
 * @}
 */ /* end of group FC_STDOUT_Peripheral_Access_Layer */


#ifdef FEATURE_CLUSTER
/* ----------------------------------------------------------------------------
   -- CLUSTER_STDOUT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CLUSTER_STDOUT_Peripheral_Access_Layer CLUSTER_STDOUT Peripheral Access Layer
 * @{
 */

/** CLUSTER_STDOUT - Registers Layout Typedef */
typedef struct {
  __IO  uint32_t PUTC[16];                    /**< CLUSTER_STDOUT INFO register, offset: 0x000 */
} CLUSTER_STDOUT_Type;

/* ----------------------------------------------------------------------------
   -- CLUSTER_STDOUT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CLUSTER_STDOUT_Register_Masks CLUSTER_STDOUT Register Masks
 * @{
 */
/*! @name INFO - CLUSTER_STDOUT information register */

/*!
 * @}
 */ /* end of group CLUSTER_STDOUT_Register_Masks */


/* CLUSTER_STDOUT - Peripheral instance base addresses */
/** Peripheral CLUSTER_STDOUT base address */
#define CLUSTER_STDOUT_BASE                                (SOC_PERIPHERALS_ADDR + 0x10000u)
/** Peripheral CLUSTER_STDOUT base pointer */
#define CLUSTER_STDOUT                                     ((CLUSTER_STDOUT_Type *)CLUSTER_STDOUT_BASE)
/** Array initializer of CLUSTER_STDOUT base addresses */
#define CLUSTER_STDOUT_BASE_ADDRS                          { CLUSTER_STDOUT_BASE }
/** Array initializer of CLUSTER_STDOUT base pointers */
#define CLUSTER_STDOUT_BASE_PTRS                           { CLUSTER_STDOUT }

/*!
 * @}
 */ /* end of group CLUSTER_STDOUT_Peripheral_Access_Layer */




/* ----------------------------------------------------------------------------
   -- HWCE Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup HWCE Peripheral_Access_Layer HWCE Peripheral Access Layer
 * @{
 */

/** HWCE - Registers Layout Typedef */
typedef struct {
    __IO  uint32_t HWCE_TRIGGER_REG;              /**< HWCE Trigger register, offset: 0x00 */
    __IO  uint32_t HWCE_ACQUIRE_REG;              /**< HWCE Acquire register, offset: 0x04 */
    __IO  uint32_t HWCE_FINISHED_REG;             /**< HWCE Finished register, offset: 0x08 */
    __IO  uint32_t HWCE_STATUS_REG;               /**< HWCE Status register, offset: 0x0C */
    __IO  uint32_t HWCE_RUNNING_JOB_REG;          /**< HWCE Running Job register, offset: 0x10 */
    __IO  uint32_t HWCE_SOFT_CLEAR_REG;           /**< HWCE Soft_Clear register, offset: 0x14 */
    __IO  uint32_t _reserved0[2];                 /**< HWCE Non used registers, offser: 0x18 */
    __IO  uint32_t HWCE_GEN_CONFIG0_REG;          /**< HWCE Gen_Config0 register, offset: 0x20 */
    __IO  uint32_t HWCE_GEN_CONFIG1_REG;          /**< HWCE Gen_Config1 register, offset: 0x24 */
    __IO  uint32_t _reserved1[6];                 /**< HWCE unused registers, offset: 0x28 */
    __IO  uint32_t HWCE_Y_TRANS_SIZE_REG;         /**< HWCE Y_Trans_Size register, offset: 0x40 */
    __IO  uint32_t HWCE_Y_LINE_STRIDE_LENGTH_REG; /**< HWCE Y_Line_Stride_Length register, offset: 0x44 */
    __IO  uint32_t HWCE_Y_FEAT_STRIDE_LENGTH_REG; /**< HWCE Y_Feat_Stride_Length register, offset: 0x48 */
    __IO  uint32_t HWCE_Y_OUT_3_REG;              /**< HWCE Y_Out_3 register, offset: 0x4C */
    __IO  uint32_t HWCE_Y_OUT_2_REG;              /**< HWCE Y_Out_2 register, offset: 0x50 */
    __IO  uint32_t HWCE_Y_OUT_1_REG;              /**< HWCE Y_Out_1 register, offset: 0x54 */
    __IO  uint32_t HWCE_Y_OUT_0_REG;              /**< HWCE Y_Out_0 register, offset: 0x58 */
    __IO  uint32_t HWCE_Y_IN_3_REG;               /**< HWCE Y_In_3 register, offset: 0x5C */
    __IO  uint32_t HWCE_Y_IN_2_REG;               /**< HWCE Y_In_2 register, offset: 0x60 */
    __IO  uint32_t HWCE_Y_IN_1_REG;               /**< HWCE Y_In_1 register, offset: 0x64 */
    __IO  uint32_t HWCE_Y_IN_0_REG;               /**< HWCE Y_In_0 register, offset: 0x68 */
    __IO  uint32_t HWCE_X_TRANS_SIZE_REG;         /**< HWCE X_Trans_Size register, offset: 0x6C */
    __IO  uint32_t HWCE_X_LINE_STRIDE_LENGTH_REG; /**< HWCE X_Line_Stride_Length register, offset: 0x70 */
    __IO  uint32_t HWCE_X_FEAT_STRIDE_LENGTH_REG; /**< HWCE X_Feat_Stride_Length register, offset: 0x74 */
    __IO  uint32_t HWCE_X_IN_REG;                 /**< HWCE X_In register, offset: 0x78 */
    __IO  uint32_t HWCE_W_REG;                    /**< HWCE W register, offset: 0x7C */
    __IO  uint32_t HWCE_JOB_CONFIG0_REG;          /**< HWCE Job_Config0 register, offset: 0x80 */
    __IO  uint32_t HWCE_JOB_CONFIG1_REG;          /**< HWCE Job_Config1 register, offset: 0x84 */
} HWCE_Type;


/* ----------------------------------------------------------------------------
   -- HWCE Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup HWCE_Register_Masks HWCE Register Masks
 * @{
 */
/*! @name INFO - HWCE information register */
/* Internal registers */
#define HWCE_TRIGGER              ( 0x00 )
#define HWCE_ACQUIRE              ( 0x04 )
#define HWCE_FINISHED             ( 0x08 )
#define HWCE_STATUS               ( 0x0C )
#define HWCE_RUNNING_JOB          ( 0x10 )
#define HWCE_SOFT_CLEAR           ( 0x14 )
#define HWCE_GEN_CONFIG0          ( 0x20 )
#define HWCE_GEN_CONFIG1          ( 0x24 )

/* Configuration registers */
#define HWCE_Y_TRANS_SIZE         ( 0x40 )
#define HWCE_Y_LINE_STRIDE_LENGTH ( 0x44 )
#define HWCE_Y_FEAT_STRIDE_LENGTH ( 0x48 )
#define HWCE_Y_OUT_3_BASE_ADDR    ( 0x4C )
#define HWCE_Y_OUT_2_BASE_ADDR    ( 0x50 )
#define HWCE_Y_OUT_1_BASE_ADDR    ( 0x54 )
#define HWCE_Y_OUT_0_BASE_ADDR    ( 0x58 )
#define HWCE_Y_IN_3_BASE_ADDR     ( 0x5C )
#define HWCE_Y_IN_2_BASE_ADDR     ( 0x60 )
#define HWCE_Y_IN_1_BASE_ADDR     ( 0x64 )
#define HWCE_Y_IN_0_BASE_ADDR     ( 0x68 )
#define HWCE_X_TRANS_SIZE         ( 0x6C )
#define HWCE_X_LINE_STRIDE_LENGTH ( 0x70 )
#define HWCE_X_FEAT_STRIDE_LENGTH ( 0x74 )
#define HWCE_X_IN_BASE_ADDR       ( 0x78 )
#define HWCE_W_BASE_ADDR          ( 0x7C )
#define HWCE_JOB_CONFIG0          ( 0x80 )
#define HWCE_JOB_CONFIG1          ( 0x84 )

#define HWCE_NB_IO_REGS           ( 18 )

#define HWCE_ACQUIRE_CONTEXT_COPY ( -3 )
#define HWCE_ACQUIRE_LOCKED       ( -2 )
#define HWCE_ACQUIRE_QUEUE_FULL   ( -1 )
#define HWCE_ACQUIRE_READY        ( 0 )

#define HWCE_GEN_CONFIG0_WSTRIDE(x)           ((x) >> 16)
#define HWCE_GEN_CONFIG0_NCP(x)               (((x) >> 13) & 0x1)
#define HWCE_GEN_CONFIG0_CONV(x)              (((x) >> 11) & 0x3)
#define HWCE_GEN_CONFIG0_VECT(x)              (((x) >> 9) & 0x3)
#define HWCE_GEN_CONFIG0_UNS(x)               (((x) >> 8) & 1)
#define HWCE_GEN_CONFIG0_NY(x)                (((x) >> 7) & 1)
#define HWCE_GEN_CONFIG0_NF(x)                (((x) >> 6) & 1)
#define HWCE_GEN_CONFIG0_QF(x)                ((x) & 0x3f)

#define HWCE_GEN_CONFIG0_CONV_5x5 ( 0 )
#define HWCE_GEN_CONFIG0_CONV_3x3 ( 1 )
#define HWCE_GEN_CONFIG0_CONV_4x7 ( 2 )

#define HWCE_GEN_CONFIG0_VECT_1   ( 0 )
#define HWCE_GEN_CONFIG0_VECT_2   ( 1 )
#define HWCE_GEN_CONFIG0_VECT_4   ( 2 )

#define HWCE_GEN_CONFIG1_PIXSHIFTR(x)         (((x) >> 16) & 0x1F)
#define HWCE_GEN_CONFIG1_PIXMODE(x)           (((x) >> 8) & 0x3)
#define HWCE_GEN_CONFIG1_PIXSHIFTL(x)         (((x) >> 0) & 0x1F)

#define HWCE_JOB_CONFIG0_NOYCONST(x)          ((x) >> 16)
#define HWCE_JOB_CONFIG0_LBUFLEN(x)           ((x) & 0x3ff)

#define HWCE_JOB_CONFIG1_LO(x)                (((x) >> 24) & 0x1)
#define HWCE_JOB_CONFIG1_WIF(x)               (((x) >> 16) & 0x3F)
#define HWCE_JOB_CONFIG1_WOF(x)               (((x) >> 8) & 0x1F)
#define HWCE_JOB_CONFIG1_VECT_DISABLE_MASK(x) (((x) >> 0) & 0xF)

#define HWCE_JOB_STRIDE(x)                    ((x) >> 16)
#define HWCE_JOB_LENGTH(x)                    ((x) & 0xffff)

  /*!
   * @}
   */ /* end of group HWCE_Register_Masks */


/* HWCE - Peripheral instance base addresses */
/** Peripheral HWCE base address */
#define HWCE_BASE                                (CORE_PERI_BASE + 0x00001000)
/** Peripheral HWCE base pointer */
#define HWCE                                     ((HWCE_Type *) HWCE_BASE)
/** Array initializer of HWCE base addresses */
#define HWCE_BASE_ADDRS                          { HWCE_BASE }
/** Array initializer of HWCE base pointers */
#define HWCE_BASE_PTRS                           { HWCE }

/*!
 * @}
 */ /* end of group HWCE_Peripheral_Access_Layer */


#endif


/*
** End of section using anonymous unions
*/

/*!
 * @}
 */ /* end of group Peripheral_access_layer */

/* ----------------------------------------------------------------------------
   -- SDK Compatibility
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SDK_Compatibility_Symbols SDK Compatibility
 * @{
 */

/*!
 * @}
 */ /* end of group SDK_Compatibility_Symbols */





#endif /* TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_PERIPH_H_ */
