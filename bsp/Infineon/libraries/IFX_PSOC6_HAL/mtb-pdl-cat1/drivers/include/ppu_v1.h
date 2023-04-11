/***************************************************************************//**
* \file ppu_v1.h
* \version 1.0
*
* This file provides the header for ARM PPU driver
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
* SPDX-License-Identifier: BSD-3-Clause
*
* Arm SCP/MCP Software
* Copyright (c) 2015-2021, Arm Limited and Contributors. All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*******************************************************************************/


#ifndef PPU_V1_H
#define PPU_V1_H

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS)

/*!
 * \cond
 * @{
 */
#include <stdbool.h>
#include <stdint.h>
#include "cy_syslib.h"

/*
 * Macro additions by Cypress Semiconductor Corporation
 */
#define fwk_assert     CY_ASSERT
#define FWK_SUCCESS    CY_RET_SUCCESS


/*
 * PPU 1.1 register definitions
 */
struct ppu_v1_reg {
  __IOM  uint32_t PWPR;
  __IOM  uint32_t PMER;
  __IM   uint32_t PWSR;
          uint32_t RESERVED0;
  __IM   uint32_t DISR;
  __IM   uint32_t MISR;
  __IM   uint32_t STSR;
  __IOM  uint32_t UNLK;
  __IOM  uint32_t PWCR;
  __IOM  uint32_t PTCR;
          uint32_t RESERVED1[2];
  __IOM  uint32_t IMR;
  __IOM  uint32_t AIMR;
  __IOM  uint32_t ISR;
  __IOM  uint32_t AISR;
  __IOM  uint32_t IESR;
  __IOM  uint32_t OPSR;
          uint32_t RESERVED2[2];
  __IOM  uint32_t FUNRR;
  __IOM  uint32_t FULRR;
  __IOM  uint32_t MEMRR;
          uint8_t  RESERVED3[0x160 - 0x5C];
  __IOM  uint32_t EDTR0;
  __IOM  uint32_t EDTR1;
          uint32_t RESERVED4[2];
  __IOM  uint32_t DCCR0;
  __IOM  uint32_t DCCR1;
          uint8_t  RESERVED5[0xFB0 - 0x178];
  __IM   uint32_t IDR0;
  __IM   uint32_t IDR1;
          uint8_t  RESERVED6[0xFC8 - 0xFB8];
  __IM   uint32_t IIDR;
  __IM   uint32_t AIDR;
          uint8_t  RESERVED7[0x1000 - 0xFD0];
};

enum ppu_v1_mode {
    PPU_V1_MODE_OFF         = 0,
    PPU_V1_MODE_OFF_EMU     = 1,
    PPU_V1_MODE_MEM_RET     = 2,
    PPU_V1_MODE_MEM_RET_EMU = 3,
    PPU_V1_MODE_LOGIC_RET   = 4,
    PPU_V1_MODE_FULL_RET    = 5,
    PPU_V1_MODE_MEM_OFF     = 6,
    PPU_V1_MODE_FUNC_RET    = 7,
    PPU_V1_MODE_ON          = 8,
    PPU_V1_MODE_WARM_RST    = 9,
    PPU_V1_MODE_DBG_RECOV   = 10,
    /* No valid modes after this line */
    PPU_V1_MODE_COUNT
};

enum ppu_v1_opmode {
    PPU_V1_OPMODE_00,
    PPU_V1_OPMODE_01,
    PPU_V1_OPMODE_02,
    PPU_V1_OPMODE_03,
    PPU_V1_OPMODE_04,
    PPU_V1_OPMODE_05,
    PPU_V1_OPMODE_06,
    PPU_V1_OPMODE_07,
    PPU_V1_OPMODE_08,
    PPU_V1_OPMODE_09,
    PPU_V1_OPMODE_10,
    PPU_V1_OPMODE_11,
    PPU_V1_OPMODE_12,
    PPU_V1_OPMODE_13,
    PPU_V1_OPMODE_14,
    PPU_V1_OPMODE_15,
    /* No valid operating modes after this line */
    PPU_V1_OPMODE_COUNT
};

enum ppu_v1_op_devactive {
    PPU_V1_OP_DEVACTIVE_0,
    PPU_V1_OP_DEVACTIVE_1,
    PPU_V1_OP_DEVACTIVE_2,
    PPU_V1_OP_DEVACTIVE_3,
    PPU_V1_OP_DEVACTIVE_INDEPENDENT_COUNT,
    PPU_V1_OP_DEVACTIVE_4 = 4,
    PPU_V1_OP_DEVACTIVE_5,
    PPU_V1_OP_DEVACTIVE_6,
    PPU_V1_OP_DEVACTIVE_7,
    /* No valid operating mode devactive signal number after this line */
    PPU_V1_OP_DEVACTIVE_COUNT
};

/*
 * Bit definitions for PWPR
 */
#define PPU_V1_PWPR_PWR_POLICY_POS   0
#define PPU_V1_PWPR_OP_POLICY_POS    16

#define PPU_V1_PWPR_POLICY       UINT32_C(0x0000000F)
#define PPU_V1_PWPR_DYNAMIC_EN   UINT32_C(0x00000100)
#define PPU_V1_PWPR_OFF_LOCK_EN  UINT32_C(0x00001000)
#define PPU_V1_PWPR_OP_POLICY    UINT32_C(0x000F0000)
#define PPU_V1_PWPR_OP_DYN_EN    UINT32_C(0x01000000)

/*
 * Bit definitions for PWSR
 */
#define PPU_V1_PWSR_PWR_STATUS_POS   0
#define PPU_V1_PWSR_OP_STATUS_POS    16

#define PPU_V1_PWSR_PWR_STATUS       UINT32_C(0x0000000F)
#define PPU_V1_PWSR_PWR_DYN_STATUS   UINT32_C(0x00000100)
#define PPU_V1_PWSR_OFF_LOCK_STATUS  UINT32_C(0x00001000)
#define PPU_V1_PWSR_OP_STATUS        UINT32_C(0x000F0000)
#define PPU_V1_PWSR_OP_DYN_STATUS    UINT32_C(0x01000000)

/*
 * Bit definitions for DISR
 */
#define PPU_V1_DISR_PWR_DEVACTIVE_STATUS_POS 0
#define PPU_V1_DISR_OP_DEVACTIVE_STATUS_POS 24

/*
 * Bit definitions for UNLK
 */
#define PPU_V1_UNLK_OFF_UNLOCK       UINT32_C(0x00000001)

/*
 * Bit definitions for PWCR
 */
#define PPU_V1_PWCR_DEV_REQ_EN        UINT32_C(0x000000FF)
#define PPU_V1_PWCR_DEV_ACTIVE_EN     UINT32_C(0x0007FF00)
#define PPU_V1_PWCR_OP_DEV_ACTIVE_EN  UINT32_C(0xFF000000)

/*
 * Definitions for IESR and OPSR
 */
enum ppu_v1_edge_sensitivity {
    PPU_V1_EDGE_SENSITIVITY_MASKED,
    PPU_V1_EDGE_SENSITIVITY_RISING_EDGE,
    PPU_V1_EDGE_SENSITIVITY_FALLING_EDGE,
    PPU_V1_EDGE_SENSITIVITY_BOTH_EDGES,
    /* No valid edge sensitivity after this line */
    PPU_V1_EDGE_SENSITIVITY_COUNT
};

#define PPU_V1_BITS_PER_EDGE_SENSITIVITY 2
#define PPU_V1_EDGE_SENSITIVITY_MASK  0x3

/*
 * Bit definitions for IMR
 */
#define PPU_V1_IMR_MASK                     UINT32_C(0x0000003F)
#define PPU_V1_IMR_STA_POLICY_TRN_IRQ_MASK  UINT32_C(0x00000001)
#define PPU_V1_IMR_STA_ACCEPT_IRQ_MASK      UINT32_C(0x00000002)
#define PPU_V1_IMR_STA_DENY_IRQ_MASK        UINT32_C(0x00000004)
#define PPU_V1_IMR_EMU_ACCEPT_IRQ_MASK      UINT32_C(0x00000008)
#define PPU_V1_IMR_EMU_DENY_IRQ_MASK        UINT32_C(0x00000010)
#define PPU_V1_IMR_DYN_POLICY_MIN_IRQ_MASK  UINT32_C(0x00000020)

/*
 * Bit definitions for AIMR
 */
#define PPU_V1_AIMR_MASK                     UINT32_C(0x0000001F)
#define PPU_V1_AIMR_UNSPT_POLICY_IRQ_MASK    UINT32_C(0x00000001)
#define PPU_V1_AIMR_DYN_ACCEPT_IRQ_MASK      UINT32_C(0x00000002)
#define PPU_V1_AIMR_DYN_DENY_IRQ_MASK        UINT32_C(0x00000004)
#define PPU_V1_AIMR_STA_POLICY_PWR_IRQ_MASK  UINT32_C(0x00000008)
#define PPU_V1_AIMR_STA_POLICY_OP_IRQ_MASK   UINT32_C(0x00000010)

/*
 * Bit definitions for ISR
 */
#define PPU_V1_ISR_MASK                        UINT32_C(0xFF07FFBF)
#define PPU_V1_ISR_STA_POLICY_TRN_IRQ          UINT32_C(0x00000001)
#define PPU_V1_ISR_STA_ACCEPT_IRQ              UINT32_C(0x00000002)
#define PPU_V1_ISR_STA_DENY_IRQ                UINT32_C(0x00000004)
#define PPU_V1_ISR_EMU_ACCEPT_IRQ              UINT32_C(0x00000008)
#define PPU_V1_ISR_EMU_DENY_IRQ                UINT32_C(0x00000010)
#define PPU_V1_ISR_DYN_POLICY_MIN_IRQ          UINT32_C(0x00000020)
#define PPU_V1_ISR_OTHER_IRQ                   UINT32_C(0x00000080)
#define PPU_V1_ISR_ACTIVE_EDGE_POS             8
#define PPU_V1_ISR_ACTIVE_EDGE_IRQ_MASK        UINT32_C(0x0007FF00)
#define PPU_V1_ISR_ACTIVE_EDGE_ACTIVE0_IRQ     UINT32_C(0x00000100)
#define PPU_V1_ISR_ACTIVE_EDGE_ACTIVE1_IRQ     UINT32_C(0x00000200)
#define PPU_V1_ISR_ACTIVE_EDGE_ACTIVE2_IRQ     UINT32_C(0x00000400)
#define PPU_V1_ISR_ACTIVE_EDGE_ACTIVE3_IRQ     UINT32_C(0x00000800)
#define PPU_V1_ISR_ACTIVE_EDGE_ACTIVE4_IRQ     UINT32_C(0x00001000)
#define PPU_V1_ISR_ACTIVE_EDGE_ACTIVE5_IRQ     UINT32_C(0x00002000)
#define PPU_V1_ISR_ACTIVE_EDGE_ACTIVE6_IRQ     UINT32_C(0x00004000)
#define PPU_V1_ISR_ACTIVE_EDGE_ACTIVE7_IRQ     UINT32_C(0x00008000)
#define PPU_V1_ISR_ACTIVE_EDGE_ACTIVE8_IRQ     UINT32_C(0x00010000)
#define PPU_V1_ISR_ACTIVE_EDGE_ACTIVE9_IRQ     UINT32_C(0x00020000)
#define PPU_V1_ISR_ACTIVE_EDGE_ACTIVE10_IRQ    UINT32_C(0x00040000)
#define PPU_V1_ISR_OP_ACTIVE_EDGE_POS          24
#define PPU_V1_ISR_OP_ACTIVE_EDGE_IRQ_MASK     UINT32_C(0xFF000000)
#define PPU_V1_ISR_OP_ACTIVE_EDGE_ACTIVE0_IRQ  UINT32_C(0x01000000)
#define PPU_V1_ISR_OP_ACTIVE_EDGE_ACTIVE1_IRQ  UINT32_C(0x02000000)
#define PPU_V1_ISR_OP_ACTIVE_EDGE_ACTIVE2_IRQ  UINT32_C(0x04000000)
#define PPU_V1_ISR_OP_ACTIVE_EDGE_ACTIVE3_IRQ  UINT32_C(0x08000000)
#define PPU_V1_ISR_OP_ACTIVE_EDGE_ACTIVE4_IRQ  UINT32_C(0x10000000)
#define PPU_V1_ISR_OP_ACTIVE_EDGE_ACTIVE5_IRQ  UINT32_C(0x20000000)
#define PPU_V1_ISR_OP_ACTIVE_EDGE_ACTIVE6_IRQ  UINT32_C(0x40000000)
#define PPU_V1_ISR_OP_ACTIVE_EDGE_ACTIVE7_IRQ  UINT32_C(0x80000000)

/*
 * Bit definitions for AISR
 */
#define PPU_V1_AISR_MASK                UINT32_C(0x0000001F)
#define PPU_V1_AISR_UNSPT_POLICY_IRQ    UINT32_C(0x00000001)
#define PPU_V1_AISR_DYN_ACCEPT_IRQ      UINT32_C(0x00000002)
#define PPU_V1_AISR_DYN_DENY_IRQ        UINT32_C(0x00000004)
#define PPU_V1_AISR_STA_POLICY_PWR_IRQ  UINT32_C(0x00000008)
#define PPU_V1_AISR_STA_POLICY_OP_IRQ   UINT32_C(0x00000010)


/*
 * Bit definitions for MISR
 */
#define PPU_V1_MISR_DEVDENY_STATUS_POS  16
#define PPU_V1_MISR_DEVDENY_STATUS_MASK UINT32_C(0x00FF0000)

/*
 * Bit definitions for AIDR
 */
#define PPU_V1_AIDR_ARCH_REV_MINOR  UINT32_C(0x0000000F)
#define PPU_V1_AIDR_ARCH_REV_MAJOR  UINT32_C(0x000000F0)

/*
 * Definitions for PPU Arch version ID
 */
#define PPU_V1_ARCH_ID  0x11

/*
 * Bit definitions for IDR0
 */
#define PPU_V1_IDR0_NUM_OPMODE_POS    4
#define PPU_V1_IDR0_NUM_OPMODE        UINT32_C(0x000000F0)

/*
 * Initializes the PPU by masking all interrupts and acknowledging any
 * previously pending interrupt.
 */
void ppu_v1_init(struct ppu_v1_reg *ppu);

/*
 * Set PPU's power mode and wait for the transition.
 * Note: This function currently supports only synchronous transitions with
 *       limited error detection.
 */
int ppu_v1_set_power_mode(struct ppu_v1_reg *ppu, enum ppu_v1_mode ppu_mode);

/*
 * Request PPU's power mode and don't wait for the transition.
 */
int ppu_v1_request_power_mode(struct ppu_v1_reg *ppu,
                              enum ppu_v1_mode ppu_mode);

/*
 * Request a change to the PPU's operating mode.
 */
int ppu_v1_request_operating_mode(struct ppu_v1_reg *ppu,
                                  enum ppu_v1_opmode op_mode);

/*
 * Enable PPU's dynamic operating mode transitions
 */
void ppu_v1_opmode_dynamic_enable(struct ppu_v1_reg *ppu,
                                  enum ppu_v1_opmode min_dyn_mode);

/*
 * Enable PPU's dynamic power mode transitions
 */
void ppu_v1_dynamic_enable(struct ppu_v1_reg *ppu,
                           enum ppu_v1_mode min_dyn_state);

/*
 * Enable the lock in the OFF state
 */
void ppu_v1_lock_off_enable(struct ppu_v1_reg *ppu);

/*
 * Disable the lock in the OFF state
 */
void ppu_v1_lock_off_disable(struct ppu_v1_reg *ppu);

/*
 * Get the current power mode.
 */
enum ppu_v1_mode ppu_v1_get_power_mode(struct ppu_v1_reg *ppu);

/*
 * Get the current programmed power policy mode.
 */
enum ppu_v1_mode ppu_v1_get_programmed_power_mode(struct ppu_v1_reg *ppu);

/*
 * Get the current operating mode.
 */
enum ppu_v1_opmode ppu_v1_get_operating_mode(struct ppu_v1_reg *ppu);

/*
 * Get the current programmed operating mode policy.
 */
enum ppu_v1_opmode ppu_v1_get_programmed_operating_mode(struct ppu_v1_reg *ppu);

/*
 * Check whether the dynamic transitions are enabled or not.
 */
bool ppu_v1_is_dynamic_enabled(struct ppu_v1_reg *ppu);

/*
 * Check whether the locked in the MEM_RET or OFF state.
 */
bool ppu_v1_is_locked(struct ppu_v1_reg *ppu);

/*
 * Check if the DEVACTIVE signal associated to a power mode is high.
 */
bool ppu_v1_is_power_devactive_high(struct ppu_v1_reg *ppu,
                                    enum ppu_v1_mode ppu_mode);

/*
 * Check if the DEVACTIVE signal associated to an operating mode is high.
 */
bool ppu_v1_is_op_devactive_high(struct ppu_v1_reg *ppu,
                                 enum ppu_v1_op_devactive op_devactive);

/*
 * Unlock the power domain from the OFF power mode.
 */
void ppu_v1_off_unlock(struct ppu_v1_reg *ppu);

/*
 * Disable the check of the DEVACTIVE signals by the PPU logic for state
 * transition.
 */
void ppu_v1_disable_devactive(struct ppu_v1_reg *ppu);

/*
 * Disable the handshake with the P-channel or the Q-channels
 */
void ppu_v1_disable_handshake(struct ppu_v1_reg *ppu);

/*
 * Set one or more bits of the interrupt mask register.
 */
void ppu_v1_interrupt_mask(struct ppu_v1_reg *ppu, unsigned int mask);

/*
 * Set one or more bits of the additional interrupt mask register.
 */
void ppu_v1_additional_interrupt_mask(struct ppu_v1_reg *ppu,
    unsigned int mask);

/*
 * Clear one or more bits of the interrupt mask register.
 */
void ppu_v1_interrupt_unmask(struct ppu_v1_reg *ppu, unsigned int mask);

/*
 * Clear one or more bits of the additional interrupt mask register.
 */
void ppu_v1_additional_interrupt_unmask(struct ppu_v1_reg *ppu,
    unsigned int mask);

/*
 * Check if some additional interrupts are pending.
 */
bool ppu_v1_is_additional_interrupt_pending(struct ppu_v1_reg *ppu,
    unsigned int mask);

/*
 * Acknowledge one or more interrupts.
 */
void ppu_v1_ack_interrupt(struct ppu_v1_reg *ppu, unsigned int mask);

/*
 * Acknowledge one or more additional interrupts.
 */
void ppu_v1_ack_additional_interrupt(struct ppu_v1_reg *ppu, unsigned int mask);

/*
 * Set input edge sensitivity. See 'enum ppu_v1_edge_sensitivity' for the
 * available sensitivities.
 */
void ppu_v1_set_input_edge_sensitivity(struct ppu_v1_reg *ppu,
    enum ppu_v1_mode ppu_mode, enum ppu_v1_edge_sensitivity edge_sensitivity);

/*
 * Get input edge sensitivity. See 'enum ppu_v1_edge_sensitivity' for the
 * available sensitivities.
 */
enum ppu_v1_edge_sensitivity ppu_v1_get_input_edge_sensitivity(
    struct ppu_v1_reg *ppu, enum ppu_v1_mode ppu_mode);

/*
 * Acknowledge a power active edge interrupt.
 */
void ppu_v1_ack_power_active_edge_interrupt(struct ppu_v1_reg *ppu,
                                            enum ppu_v1_mode ppu_mode);

/*
 * Check if a power active edge interrupt is pending.
 */
bool ppu_v1_is_power_active_edge_interrupt(struct ppu_v1_reg *ppu,
                                           enum ppu_v1_mode ppu_mode);

/*
 * Set operating mode active edge sensitivity. See
 * 'enum ppu_v1_edge_sensitivity' for the available sensitivities.
 */
void ppu_v1_set_op_active_edge_sensitivity(struct ppu_v1_reg *ppu,
    enum ppu_v1_op_devactive op_devactive,
    enum ppu_v1_edge_sensitivity edge_sensitivity);

/*
 * Get operating mode active edge sensitivity.
 * See 'enum ppu_v1_edge_sensitivity for the available sensitivities.
 */
enum ppu_v1_edge_sensitivity ppu_v1_get_op_active_edge_sensitivity(
    struct ppu_v1_reg *ppu, enum ppu_v1_op_devactive op_devactive);

/*
 * Acknowledge operating mode active edge interrupt.
 */
void ppu_v1_ack_op_active_edge_interrupt(struct ppu_v1_reg *ppu,
    enum ppu_v1_op_devactive op_devactive);

/*
 * Check if an operating mode active edge interrupt is pending.
 */
bool ppu_v1_is_op_active_edge_interrupt(struct ppu_v1_reg *ppu,
    enum ppu_v1_op_devactive op_devactive);

/*
 * Check if the DYN input edge interrupt is pending.
 */
bool ppu_v1_is_dyn_policy_min_interrupt(struct ppu_v1_reg *ppu);

/*
 * Get the number of operating modes.
 */
unsigned int ppu_v1_get_num_opmode(struct ppu_v1_reg *ppu);

/*
 * Get the PPU architecture ID.
 */
unsigned int ppu_v1_get_arch_id(struct ppu_v1_reg *ppu);

/*
 * Get the ID(s) of device that denied Deepsleep
 */
unsigned int ppu_v1_get_failure_device_id(struct ppu_v1_reg *ppu);

/*!
 * \endcond
 * @}
 */
#endif /* CY_IP_MXS40SRSS || CY_IP_MXS40SSRSS*/

#endif  /* PPU_V1_H */
