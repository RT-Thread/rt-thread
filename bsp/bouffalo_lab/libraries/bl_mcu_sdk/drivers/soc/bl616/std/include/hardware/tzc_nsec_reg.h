/**
  ******************************************************************************
  * @file    tzc_nsec_reg.h
  * @version V1.0
  * @date    2021-10-30
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef  __TZC_NSEC_REG_H__
#define  __TZC_NSEC_REG_H__

#include "bl616.h"

/* 0x40 : tzc_rom_tzsrg_ctrl */
#define TZC_NSEC_TZC_ROM_TZSRG_CTRL_OFFSET                      (0x40)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_ID_EN                         TZC_NSEC_TZC_ROM_TZSRG_R0_ID_EN
#define TZC_NSEC_TZC_ROM_TZSRG_R0_ID_EN_POS                     (0U)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_ID_EN_LEN                     (4U)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_ID_EN_MSK                     (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R0_ID_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R0_ID_EN_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_ID_EN_UMSK                    (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R0_ID_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R0_ID_EN_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_R1_ID_EN                         TZC_NSEC_TZC_ROM_TZSRG_R1_ID_EN
#define TZC_NSEC_TZC_ROM_TZSRG_R1_ID_EN_POS                     (4U)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_ID_EN_LEN                     (4U)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_ID_EN_MSK                     (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R1_ID_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R1_ID_EN_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_ID_EN_UMSK                    (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R1_ID_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R1_ID_EN_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_R2_ID_EN                         TZC_NSEC_TZC_ROM_TZSRG_R2_ID_EN
#define TZC_NSEC_TZC_ROM_TZSRG_R2_ID_EN_POS                     (8U)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_ID_EN_LEN                     (4U)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_ID_EN_MSK                     (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R2_ID_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R2_ID_EN_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_ID_EN_UMSK                    (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R2_ID_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R2_ID_EN_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_RX_ID_EN                         TZC_NSEC_TZC_ROM_TZSRG_RX_ID_EN
#define TZC_NSEC_TZC_ROM_TZSRG_RX_ID_EN_POS                     (12U)
#define TZC_NSEC_TZC_ROM_TZSRG_RX_ID_EN_LEN                     (4U)
#define TZC_NSEC_TZC_ROM_TZSRG_RX_ID_EN_MSK                     (((1U<<TZC_NSEC_TZC_ROM_TZSRG_RX_ID_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_RX_ID_EN_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_RX_ID_EN_UMSK                    (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_RX_ID_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_RX_ID_EN_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_R0_EN                            TZC_NSEC_TZC_ROM_TZSRG_R0_EN
#define TZC_NSEC_TZC_ROM_TZSRG_R0_EN_POS                        (16U)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_EN_LEN                        (1U)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_EN_MSK                        (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R0_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R0_EN_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_EN_UMSK                       (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R0_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R0_EN_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_R1_EN                            TZC_NSEC_TZC_ROM_TZSRG_R1_EN
#define TZC_NSEC_TZC_ROM_TZSRG_R1_EN_POS                        (17U)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_EN_LEN                        (1U)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_EN_MSK                        (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R1_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R1_EN_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_EN_UMSK                       (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R1_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R1_EN_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_R2_EN                            TZC_NSEC_TZC_ROM_TZSRG_R2_EN
#define TZC_NSEC_TZC_ROM_TZSRG_R2_EN_POS                        (18U)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_EN_LEN                        (1U)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_EN_MSK                        (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R2_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R2_EN_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_EN_UMSK                       (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R2_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R2_EN_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_RX_EN                            TZC_NSEC_TZC_ROM_TZSRG_RX_EN
#define TZC_NSEC_TZC_ROM_TZSRG_RX_EN_POS                        (19U)
#define TZC_NSEC_TZC_ROM_TZSRG_RX_EN_LEN                        (1U)
#define TZC_NSEC_TZC_ROM_TZSRG_RX_EN_MSK                        (((1U<<TZC_NSEC_TZC_ROM_TZSRG_RX_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_RX_EN_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_RX_EN_UMSK                       (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_RX_EN_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_RX_EN_POS))
#define TZC_NSEC_TZC_BUS_RMP_EN                                 TZC_NSEC_TZC_BUS_RMP_EN
#define TZC_NSEC_TZC_BUS_RMP_EN_POS                             (22U)
#define TZC_NSEC_TZC_BUS_RMP_EN_LEN                             (1U)
#define TZC_NSEC_TZC_BUS_RMP_EN_MSK                             (((1U<<TZC_NSEC_TZC_BUS_RMP_EN_LEN)-1)<<TZC_NSEC_TZC_BUS_RMP_EN_POS)
#define TZC_NSEC_TZC_BUS_RMP_EN_UMSK                            (~(((1U<<TZC_NSEC_TZC_BUS_RMP_EN_LEN)-1)<<TZC_NSEC_TZC_BUS_RMP_EN_POS))
#define TZC_NSEC_TZC_BUS_RMP_EN_LOCK                            TZC_NSEC_TZC_BUS_RMP_EN_LOCK
#define TZC_NSEC_TZC_BUS_RMP_EN_LOCK_POS                        (23U)
#define TZC_NSEC_TZC_BUS_RMP_EN_LOCK_LEN                        (1U)
#define TZC_NSEC_TZC_BUS_RMP_EN_LOCK_MSK                        (((1U<<TZC_NSEC_TZC_BUS_RMP_EN_LOCK_LEN)-1)<<TZC_NSEC_TZC_BUS_RMP_EN_LOCK_POS)
#define TZC_NSEC_TZC_BUS_RMP_EN_LOCK_UMSK                       (~(((1U<<TZC_NSEC_TZC_BUS_RMP_EN_LOCK_LEN)-1)<<TZC_NSEC_TZC_BUS_RMP_EN_LOCK_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_R0_LOCK                          TZC_NSEC_TZC_ROM_TZSRG_R0_LOCK
#define TZC_NSEC_TZC_ROM_TZSRG_R0_LOCK_POS                      (24U)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_LOCK_LEN                      (1U)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_LOCK_MSK                      (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R0_LOCK_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R0_LOCK_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_LOCK_UMSK                     (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R0_LOCK_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R0_LOCK_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_R1_LOCK                          TZC_NSEC_TZC_ROM_TZSRG_R1_LOCK
#define TZC_NSEC_TZC_ROM_TZSRG_R1_LOCK_POS                      (25U)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_LOCK_LEN                      (1U)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_LOCK_MSK                      (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R1_LOCK_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R1_LOCK_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_LOCK_UMSK                     (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R1_LOCK_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R1_LOCK_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_R2_LOCK                          TZC_NSEC_TZC_ROM_TZSRG_R2_LOCK
#define TZC_NSEC_TZC_ROM_TZSRG_R2_LOCK_POS                      (26U)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_LOCK_LEN                      (1U)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_LOCK_MSK                      (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R2_LOCK_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R2_LOCK_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_LOCK_UMSK                     (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R2_LOCK_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R2_LOCK_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_RX_LOCK                          TZC_NSEC_TZC_ROM_TZSRG_RX_LOCK
#define TZC_NSEC_TZC_ROM_TZSRG_RX_LOCK_POS                      (27U)
#define TZC_NSEC_TZC_ROM_TZSRG_RX_LOCK_LEN                      (1U)
#define TZC_NSEC_TZC_ROM_TZSRG_RX_LOCK_MSK                      (((1U<<TZC_NSEC_TZC_ROM_TZSRG_RX_LOCK_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_RX_LOCK_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_RX_LOCK_UMSK                     (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_RX_LOCK_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_RX_LOCK_POS))
#define TZC_NSEC_TZC_SBOOT_DONE                                 TZC_NSEC_TZC_SBOOT_DONE
#define TZC_NSEC_TZC_SBOOT_DONE_POS                             (28U)
#define TZC_NSEC_TZC_SBOOT_DONE_LEN                             (4U)
#define TZC_NSEC_TZC_SBOOT_DONE_MSK                             (((1U<<TZC_NSEC_TZC_SBOOT_DONE_LEN)-1)<<TZC_NSEC_TZC_SBOOT_DONE_POS)
#define TZC_NSEC_TZC_SBOOT_DONE_UMSK                            (~(((1U<<TZC_NSEC_TZC_SBOOT_DONE_LEN)-1)<<TZC_NSEC_TZC_SBOOT_DONE_POS))

/* 0x44 : tzc_rom_tzsrg_adr_mask */
#define TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_OFFSET                  (0x44)
#define TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK                         TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK
#define TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_POS                     (0U)
#define TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_LEN                     (10U)
#define TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_MSK                     (((1U<<TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_UMSK                    (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_LOCK                    TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_LOCK
#define TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_LOCK_POS                (16U)
#define TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_LOCK_LEN                (1U)
#define TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_LOCK_MSK                (((1U<<TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_LOCK_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_LOCK_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_LOCK_UMSK               (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_LOCK_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_ADR_MASK_LOCK_POS))

/* 0x48 : tzc_rom_tzsrg_r0 */
#define TZC_NSEC_TZC_ROM_TZSRG_R0_OFFSET                        (0x48)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_END                           TZC_NSEC_TZC_ROM_TZSRG_R0_END
#define TZC_NSEC_TZC_ROM_TZSRG_R0_END_POS                       (0U)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_END_LEN                       (10U)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_END_MSK                       (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R0_END_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R0_END_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_END_UMSK                      (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R0_END_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R0_END_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_R0_START                         TZC_NSEC_TZC_ROM_TZSRG_R0_START
#define TZC_NSEC_TZC_ROM_TZSRG_R0_START_POS                     (16U)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_START_LEN                     (10U)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_START_MSK                     (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R0_START_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R0_START_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R0_START_UMSK                    (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R0_START_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R0_START_POS))

/* 0x4C : tzc_rom_tzsrg_r1 */
#define TZC_NSEC_TZC_ROM_TZSRG_R1_OFFSET                        (0x4C)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_END                           TZC_NSEC_TZC_ROM_TZSRG_R1_END
#define TZC_NSEC_TZC_ROM_TZSRG_R1_END_POS                       (0U)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_END_LEN                       (10U)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_END_MSK                       (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R1_END_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R1_END_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_END_UMSK                      (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R1_END_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R1_END_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_R1_START                         TZC_NSEC_TZC_ROM_TZSRG_R1_START
#define TZC_NSEC_TZC_ROM_TZSRG_R1_START_POS                     (16U)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_START_LEN                     (10U)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_START_MSK                     (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R1_START_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R1_START_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R1_START_UMSK                    (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R1_START_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R1_START_POS))

/* 0x50 : tzc_rom_tzsrg_r2 */
#define TZC_NSEC_TZC_ROM_TZSRG_R2_OFFSET                        (0x50)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_END                           TZC_NSEC_TZC_ROM_TZSRG_R2_END
#define TZC_NSEC_TZC_ROM_TZSRG_R2_END_POS                       (0U)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_END_LEN                       (10U)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_END_MSK                       (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R2_END_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R2_END_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_END_UMSK                      (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R2_END_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R2_END_POS))
#define TZC_NSEC_TZC_ROM_TZSRG_R2_START                         TZC_NSEC_TZC_ROM_TZSRG_R2_START
#define TZC_NSEC_TZC_ROM_TZSRG_R2_START_POS                     (16U)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_START_LEN                     (10U)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_START_MSK                     (((1U<<TZC_NSEC_TZC_ROM_TZSRG_R2_START_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R2_START_POS)
#define TZC_NSEC_TZC_ROM_TZSRG_R2_START_UMSK                    (~(((1U<<TZC_NSEC_TZC_ROM_TZSRG_R2_START_LEN)-1)<<TZC_NSEC_TZC_ROM_TZSRG_R2_START_POS))

/* 0x54 : tzc_rom_tzsrg_r3 */
#define TZC_NSEC_TZC_ROM_TZSRG_R3_OFFSET                        (0x54)

/* 0x100 : tzc_bmx_tzmid */
#define TZC_NSEC_TZC_BMX_TZMID_OFFSET                           (0x100)
#define TZC_NSEC_TZC_USB_TZMID                                  TZC_NSEC_TZC_USB_TZMID
#define TZC_NSEC_TZC_USB_TZMID_POS                              (2U)
#define TZC_NSEC_TZC_USB_TZMID_LEN                              (1U)
#define TZC_NSEC_TZC_USB_TZMID_MSK                              (((1U<<TZC_NSEC_TZC_USB_TZMID_LEN)-1)<<TZC_NSEC_TZC_USB_TZMID_POS)
#define TZC_NSEC_TZC_USB_TZMID_UMSK                             (~(((1U<<TZC_NSEC_TZC_USB_TZMID_LEN)-1)<<TZC_NSEC_TZC_USB_TZMID_POS))
#define TZC_NSEC_TZC_WIFI_TZMID                                 TZC_NSEC_TZC_WIFI_TZMID
#define TZC_NSEC_TZC_WIFI_TZMID_POS                             (3U)
#define TZC_NSEC_TZC_WIFI_TZMID_LEN                             (1U)
#define TZC_NSEC_TZC_WIFI_TZMID_MSK                             (((1U<<TZC_NSEC_TZC_WIFI_TZMID_LEN)-1)<<TZC_NSEC_TZC_WIFI_TZMID_POS)
#define TZC_NSEC_TZC_WIFI_TZMID_UMSK                            (~(((1U<<TZC_NSEC_TZC_WIFI_TZMID_LEN)-1)<<TZC_NSEC_TZC_WIFI_TZMID_POS))
#define TZC_NSEC_TZC_CCI_TZMID                                  TZC_NSEC_TZC_CCI_TZMID
#define TZC_NSEC_TZC_CCI_TZMID_POS                              (4U)
#define TZC_NSEC_TZC_CCI_TZMID_LEN                              (1U)
#define TZC_NSEC_TZC_CCI_TZMID_MSK                              (((1U<<TZC_NSEC_TZC_CCI_TZMID_LEN)-1)<<TZC_NSEC_TZC_CCI_TZMID_POS)
#define TZC_NSEC_TZC_CCI_TZMID_UMSK                             (~(((1U<<TZC_NSEC_TZC_CCI_TZMID_LEN)-1)<<TZC_NSEC_TZC_CCI_TZMID_POS))
#define TZC_NSEC_TZC_SDHM_TZMID                                 TZC_NSEC_TZC_SDHM_TZMID
#define TZC_NSEC_TZC_SDHM_TZMID_POS                             (5U)
#define TZC_NSEC_TZC_SDHM_TZMID_LEN                             (1U)
#define TZC_NSEC_TZC_SDHM_TZMID_MSK                             (((1U<<TZC_NSEC_TZC_SDHM_TZMID_LEN)-1)<<TZC_NSEC_TZC_SDHM_TZMID_POS)
#define TZC_NSEC_TZC_SDHM_TZMID_UMSK                            (~(((1U<<TZC_NSEC_TZC_SDHM_TZMID_LEN)-1)<<TZC_NSEC_TZC_SDHM_TZMID_POS))
#define TZC_NSEC_TZC_EMACA_TZMID                                TZC_NSEC_TZC_EMACA_TZMID
#define TZC_NSEC_TZC_EMACA_TZMID_POS                            (6U)
#define TZC_NSEC_TZC_EMACA_TZMID_LEN                            (1U)
#define TZC_NSEC_TZC_EMACA_TZMID_MSK                            (((1U<<TZC_NSEC_TZC_EMACA_TZMID_LEN)-1)<<TZC_NSEC_TZC_EMACA_TZMID_POS)
#define TZC_NSEC_TZC_EMACA_TZMID_UMSK                           (~(((1U<<TZC_NSEC_TZC_EMACA_TZMID_LEN)-1)<<TZC_NSEC_TZC_EMACA_TZMID_POS))
#define TZC_NSEC_TZC_CPU_TZMID                                  TZC_NSEC_TZC_CPU_TZMID
#define TZC_NSEC_TZC_CPU_TZMID_POS                              (7U)
#define TZC_NSEC_TZC_CPU_TZMID_LEN                              (1U)
#define TZC_NSEC_TZC_CPU_TZMID_MSK                              (((1U<<TZC_NSEC_TZC_CPU_TZMID_LEN)-1)<<TZC_NSEC_TZC_CPU_TZMID_POS)
#define TZC_NSEC_TZC_CPU_TZMID_UMSK                             (~(((1U<<TZC_NSEC_TZC_CPU_TZMID_LEN)-1)<<TZC_NSEC_TZC_CPU_TZMID_POS))
#define TZC_NSEC_TZC_DMA_TZMID                                  TZC_NSEC_TZC_DMA_TZMID
#define TZC_NSEC_TZC_DMA_TZMID_POS                              (8U)
#define TZC_NSEC_TZC_DMA_TZMID_LEN                              (1U)
#define TZC_NSEC_TZC_DMA_TZMID_MSK                              (((1U<<TZC_NSEC_TZC_DMA_TZMID_LEN)-1)<<TZC_NSEC_TZC_DMA_TZMID_POS)
#define TZC_NSEC_TZC_DMA_TZMID_UMSK                             (~(((1U<<TZC_NSEC_TZC_DMA_TZMID_LEN)-1)<<TZC_NSEC_TZC_DMA_TZMID_POS))
#define TZC_NSEC_TZC_SDUM_TZMID                                 TZC_NSEC_TZC_SDUM_TZMID
#define TZC_NSEC_TZC_SDUM_TZMID_POS                             (11U)
#define TZC_NSEC_TZC_SDUM_TZMID_LEN                             (1U)
#define TZC_NSEC_TZC_SDUM_TZMID_MSK                             (((1U<<TZC_NSEC_TZC_SDUM_TZMID_LEN)-1)<<TZC_NSEC_TZC_SDUM_TZMID_POS)
#define TZC_NSEC_TZC_SDUM_TZMID_UMSK                            (~(((1U<<TZC_NSEC_TZC_SDUM_TZMID_LEN)-1)<<TZC_NSEC_TZC_SDUM_TZMID_POS))
#define TZC_NSEC_TZC_USB_TZMID_SEL                              TZC_NSEC_TZC_USB_TZMID_SEL
#define TZC_NSEC_TZC_USB_TZMID_SEL_POS                          (18U)
#define TZC_NSEC_TZC_USB_TZMID_SEL_LEN                          (1U)
#define TZC_NSEC_TZC_USB_TZMID_SEL_MSK                          (((1U<<TZC_NSEC_TZC_USB_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_USB_TZMID_SEL_POS)
#define TZC_NSEC_TZC_USB_TZMID_SEL_UMSK                         (~(((1U<<TZC_NSEC_TZC_USB_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_USB_TZMID_SEL_POS))
#define TZC_NSEC_TZC_WIFI_TZMID_SEL                             TZC_NSEC_TZC_WIFI_TZMID_SEL
#define TZC_NSEC_TZC_WIFI_TZMID_SEL_POS                         (19U)
#define TZC_NSEC_TZC_WIFI_TZMID_SEL_LEN                         (1U)
#define TZC_NSEC_TZC_WIFI_TZMID_SEL_MSK                         (((1U<<TZC_NSEC_TZC_WIFI_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_WIFI_TZMID_SEL_POS)
#define TZC_NSEC_TZC_WIFI_TZMID_SEL_UMSK                        (~(((1U<<TZC_NSEC_TZC_WIFI_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_WIFI_TZMID_SEL_POS))
#define TZC_NSEC_TZC_CCI_TZMID_SEL                              TZC_NSEC_TZC_CCI_TZMID_SEL
#define TZC_NSEC_TZC_CCI_TZMID_SEL_POS                          (20U)
#define TZC_NSEC_TZC_CCI_TZMID_SEL_LEN                          (1U)
#define TZC_NSEC_TZC_CCI_TZMID_SEL_MSK                          (((1U<<TZC_NSEC_TZC_CCI_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_CCI_TZMID_SEL_POS)
#define TZC_NSEC_TZC_CCI_TZMID_SEL_UMSK                         (~(((1U<<TZC_NSEC_TZC_CCI_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_CCI_TZMID_SEL_POS))
#define TZC_NSEC_TZC_SDHM_TZMID_SEL                             TZC_NSEC_TZC_SDHM_TZMID_SEL
#define TZC_NSEC_TZC_SDHM_TZMID_SEL_POS                         (21U)
#define TZC_NSEC_TZC_SDHM_TZMID_SEL_LEN                         (1U)
#define TZC_NSEC_TZC_SDHM_TZMID_SEL_MSK                         (((1U<<TZC_NSEC_TZC_SDHM_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_SDHM_TZMID_SEL_POS)
#define TZC_NSEC_TZC_SDHM_TZMID_SEL_UMSK                        (~(((1U<<TZC_NSEC_TZC_SDHM_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_SDHM_TZMID_SEL_POS))
#define TZC_NSEC_TZC_EMACA_TZMID_SEL                            TZC_NSEC_TZC_EMACA_TZMID_SEL
#define TZC_NSEC_TZC_EMACA_TZMID_SEL_POS                        (22U)
#define TZC_NSEC_TZC_EMACA_TZMID_SEL_LEN                        (1U)
#define TZC_NSEC_TZC_EMACA_TZMID_SEL_MSK                        (((1U<<TZC_NSEC_TZC_EMACA_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_EMACA_TZMID_SEL_POS)
#define TZC_NSEC_TZC_EMACA_TZMID_SEL_UMSK                       (~(((1U<<TZC_NSEC_TZC_EMACA_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_EMACA_TZMID_SEL_POS))
#define TZC_NSEC_TZC_CPU_TZMID_SEL                              TZC_NSEC_TZC_CPU_TZMID_SEL
#define TZC_NSEC_TZC_CPU_TZMID_SEL_POS                          (23U)
#define TZC_NSEC_TZC_CPU_TZMID_SEL_LEN                          (1U)
#define TZC_NSEC_TZC_CPU_TZMID_SEL_MSK                          (((1U<<TZC_NSEC_TZC_CPU_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_CPU_TZMID_SEL_POS)
#define TZC_NSEC_TZC_CPU_TZMID_SEL_UMSK                         (~(((1U<<TZC_NSEC_TZC_CPU_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_CPU_TZMID_SEL_POS))
#define TZC_NSEC_TZC_DMA_TZMID_SEL                              TZC_NSEC_TZC_DMA_TZMID_SEL
#define TZC_NSEC_TZC_DMA_TZMID_SEL_POS                          (24U)
#define TZC_NSEC_TZC_DMA_TZMID_SEL_LEN                          (1U)
#define TZC_NSEC_TZC_DMA_TZMID_SEL_MSK                          (((1U<<TZC_NSEC_TZC_DMA_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_DMA_TZMID_SEL_POS)
#define TZC_NSEC_TZC_DMA_TZMID_SEL_UMSK                         (~(((1U<<TZC_NSEC_TZC_DMA_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_DMA_TZMID_SEL_POS))
#define TZC_NSEC_TZC_SDUM_TZMID_SEL                             TZC_NSEC_TZC_SDUM_TZMID_SEL
#define TZC_NSEC_TZC_SDUM_TZMID_SEL_POS                         (27U)
#define TZC_NSEC_TZC_SDUM_TZMID_SEL_LEN                         (1U)
#define TZC_NSEC_TZC_SDUM_TZMID_SEL_MSK                         (((1U<<TZC_NSEC_TZC_SDUM_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_SDUM_TZMID_SEL_POS)
#define TZC_NSEC_TZC_SDUM_TZMID_SEL_UMSK                        (~(((1U<<TZC_NSEC_TZC_SDUM_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_SDUM_TZMID_SEL_POS))

/* 0x104 : tzc_bmx_tzmid_lock */
#define TZC_NSEC_TZC_BMX_TZMID_LOCK_OFFSET                      (0x104)
#define TZC_NSEC_TZC_USB_TZMID_LOCK                             TZC_NSEC_TZC_USB_TZMID_LOCK
#define TZC_NSEC_TZC_USB_TZMID_LOCK_POS                         (2U)
#define TZC_NSEC_TZC_USB_TZMID_LOCK_LEN                         (1U)
#define TZC_NSEC_TZC_USB_TZMID_LOCK_MSK                         (((1U<<TZC_NSEC_TZC_USB_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_USB_TZMID_LOCK_POS)
#define TZC_NSEC_TZC_USB_TZMID_LOCK_UMSK                        (~(((1U<<TZC_NSEC_TZC_USB_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_USB_TZMID_LOCK_POS))
#define TZC_NSEC_TZC_WIFI_TZMID_LOCK                            TZC_NSEC_TZC_WIFI_TZMID_LOCK
#define TZC_NSEC_TZC_WIFI_TZMID_LOCK_POS                        (3U)
#define TZC_NSEC_TZC_WIFI_TZMID_LOCK_LEN                        (1U)
#define TZC_NSEC_TZC_WIFI_TZMID_LOCK_MSK                        (((1U<<TZC_NSEC_TZC_WIFI_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_WIFI_TZMID_LOCK_POS)
#define TZC_NSEC_TZC_WIFI_TZMID_LOCK_UMSK                       (~(((1U<<TZC_NSEC_TZC_WIFI_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_WIFI_TZMID_LOCK_POS))
#define TZC_NSEC_TZC_CCI_TZMID_LOCK                             TZC_NSEC_TZC_CCI_TZMID_LOCK
#define TZC_NSEC_TZC_CCI_TZMID_LOCK_POS                         (4U)
#define TZC_NSEC_TZC_CCI_TZMID_LOCK_LEN                         (1U)
#define TZC_NSEC_TZC_CCI_TZMID_LOCK_MSK                         (((1U<<TZC_NSEC_TZC_CCI_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_CCI_TZMID_LOCK_POS)
#define TZC_NSEC_TZC_CCI_TZMID_LOCK_UMSK                        (~(((1U<<TZC_NSEC_TZC_CCI_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_CCI_TZMID_LOCK_POS))
#define TZC_NSEC_TZC_SDHM_TZMID_LOCK                            TZC_NSEC_TZC_SDHM_TZMID_LOCK
#define TZC_NSEC_TZC_SDHM_TZMID_LOCK_POS                        (5U)
#define TZC_NSEC_TZC_SDHM_TZMID_LOCK_LEN                        (1U)
#define TZC_NSEC_TZC_SDHM_TZMID_LOCK_MSK                        (((1U<<TZC_NSEC_TZC_SDHM_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SDHM_TZMID_LOCK_POS)
#define TZC_NSEC_TZC_SDHM_TZMID_LOCK_UMSK                       (~(((1U<<TZC_NSEC_TZC_SDHM_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SDHM_TZMID_LOCK_POS))
#define TZC_NSEC_TZC_EMACA_TZMID_LOCK                           TZC_NSEC_TZC_EMACA_TZMID_LOCK
#define TZC_NSEC_TZC_EMACA_TZMID_LOCK_POS                       (6U)
#define TZC_NSEC_TZC_EMACA_TZMID_LOCK_LEN                       (1U)
#define TZC_NSEC_TZC_EMACA_TZMID_LOCK_MSK                       (((1U<<TZC_NSEC_TZC_EMACA_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_EMACA_TZMID_LOCK_POS)
#define TZC_NSEC_TZC_EMACA_TZMID_LOCK_UMSK                      (~(((1U<<TZC_NSEC_TZC_EMACA_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_EMACA_TZMID_LOCK_POS))
#define TZC_NSEC_TZC_CPU_TZMID_LOCK                             TZC_NSEC_TZC_CPU_TZMID_LOCK
#define TZC_NSEC_TZC_CPU_TZMID_LOCK_POS                         (7U)
#define TZC_NSEC_TZC_CPU_TZMID_LOCK_LEN                         (1U)
#define TZC_NSEC_TZC_CPU_TZMID_LOCK_MSK                         (((1U<<TZC_NSEC_TZC_CPU_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_CPU_TZMID_LOCK_POS)
#define TZC_NSEC_TZC_CPU_TZMID_LOCK_UMSK                        (~(((1U<<TZC_NSEC_TZC_CPU_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_CPU_TZMID_LOCK_POS))
#define TZC_NSEC_TZC_DMA_TZMID_LOCK                             TZC_NSEC_TZC_DMA_TZMID_LOCK
#define TZC_NSEC_TZC_DMA_TZMID_LOCK_POS                         (8U)
#define TZC_NSEC_TZC_DMA_TZMID_LOCK_LEN                         (1U)
#define TZC_NSEC_TZC_DMA_TZMID_LOCK_MSK                         (((1U<<TZC_NSEC_TZC_DMA_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_DMA_TZMID_LOCK_POS)
#define TZC_NSEC_TZC_DMA_TZMID_LOCK_UMSK                        (~(((1U<<TZC_NSEC_TZC_DMA_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_DMA_TZMID_LOCK_POS))
#define TZC_NSEC_TZC_SDUM_TZMID_LOCK                            TZC_NSEC_TZC_SDUM_TZMID_LOCK
#define TZC_NSEC_TZC_SDUM_TZMID_LOCK_POS                        (11U)
#define TZC_NSEC_TZC_SDUM_TZMID_LOCK_LEN                        (1U)
#define TZC_NSEC_TZC_SDUM_TZMID_LOCK_MSK                        (((1U<<TZC_NSEC_TZC_SDUM_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SDUM_TZMID_LOCK_POS)
#define TZC_NSEC_TZC_SDUM_TZMID_LOCK_UMSK                       (~(((1U<<TZC_NSEC_TZC_SDUM_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SDUM_TZMID_LOCK_POS))

/* 0x108 : tzc_bmx_s0 */
#define TZC_NSEC_TZC_BMX_S0_OFFSET                              (0x108)
#define TZC_NSEC_TZC_BMX_DMA_TZSID_EN                           TZC_NSEC_TZC_BMX_DMA_TZSID_EN
#define TZC_NSEC_TZC_BMX_DMA_TZSID_EN_POS                       (2U)
#define TZC_NSEC_TZC_BMX_DMA_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_DMA_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_DMA_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_DMA_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_DMA_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_DMA_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_DMA_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_PWR_TZSID_EN                           TZC_NSEC_TZC_BMX_PWR_TZSID_EN
#define TZC_NSEC_TZC_BMX_PWR_TZSID_EN_POS                       (6U)
#define TZC_NSEC_TZC_BMX_PWR_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_PWR_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_PWR_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_PWR_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_PWR_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_PWR_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_PWR_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_SDH_TZSID_EN                           TZC_NSEC_TZC_BMX_SDH_TZSID_EN
#define TZC_NSEC_TZC_BMX_SDH_TZSID_EN_POS                       (8U)
#define TZC_NSEC_TZC_BMX_SDH_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_SDH_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_SDH_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_SDH_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_SDH_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_SDH_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_SDH_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_EMAC_TZSID_EN                          TZC_NSEC_TZC_BMX_EMAC_TZSID_EN
#define TZC_NSEC_TZC_BMX_EMAC_TZSID_EN_POS                      (10U)
#define TZC_NSEC_TZC_BMX_EMAC_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_EMAC_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_EMAC_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_EMAC_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_EMAC_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_EMAC_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_EMAC_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_SDU_TZSID_EN                           TZC_NSEC_TZC_BMX_SDU_TZSID_EN
#define TZC_NSEC_TZC_BMX_SDU_TZSID_EN_POS                       (12U)
#define TZC_NSEC_TZC_BMX_SDU_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_SDU_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_SDU_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_SDU_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_SDU_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_SDU_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_SDU_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_DMA_TZSID_LOCK                         TZC_NSEC_TZC_BMX_DMA_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_DMA_TZSID_LOCK_POS                     (17U)
#define TZC_NSEC_TZC_BMX_DMA_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_DMA_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_DMA_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_DMA_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_DMA_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_DMA_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_DMA_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_PWR_TZSID_LOCK                         TZC_NSEC_TZC_BMX_PWR_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_PWR_TZSID_LOCK_POS                     (19U)
#define TZC_NSEC_TZC_BMX_PWR_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_PWR_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_PWR_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_PWR_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_PWR_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_PWR_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_PWR_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_SDH_TZSID_LOCK                         TZC_NSEC_TZC_BMX_SDH_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_SDH_TZSID_LOCK_POS                     (20U)
#define TZC_NSEC_TZC_BMX_SDH_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_SDH_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_SDH_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_SDH_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_SDH_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_SDH_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_SDH_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_EMAC_TZSID_LOCK                        TZC_NSEC_TZC_BMX_EMAC_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_EMAC_TZSID_LOCK_POS                    (21U)
#define TZC_NSEC_TZC_BMX_EMAC_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_EMAC_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_EMAC_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_EMAC_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_EMAC_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_EMAC_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_EMAC_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_SDU_TZSID_LOCK                         TZC_NSEC_TZC_BMX_SDU_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_SDU_TZSID_LOCK_POS                     (22U)
#define TZC_NSEC_TZC_BMX_SDU_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_SDU_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_SDU_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_SDU_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_SDU_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_SDU_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_SDU_TZSID_LOCK_POS))

/* 0x10C : tzc_bmx_s1 */
#define TZC_NSEC_TZC_BMX_S1_OFFSET                              (0x10C)
#define TZC_NSEC_TZC_BMX_S10_TZSID_EN                           TZC_NSEC_TZC_BMX_S10_TZSID_EN
#define TZC_NSEC_TZC_BMX_S10_TZSID_EN_POS                       (0U)
#define TZC_NSEC_TZC_BMX_S10_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S10_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S10_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S10_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S10_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S10_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S10_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S11_TZSID_EN                           TZC_NSEC_TZC_BMX_S11_TZSID_EN
#define TZC_NSEC_TZC_BMX_S11_TZSID_EN_POS                       (2U)
#define TZC_NSEC_TZC_BMX_S11_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S11_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S11_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S11_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S11_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S11_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S11_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S12_TZSID_EN                           TZC_NSEC_TZC_BMX_S12_TZSID_EN
#define TZC_NSEC_TZC_BMX_S12_TZSID_EN_POS                       (4U)
#define TZC_NSEC_TZC_BMX_S12_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S12_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S12_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S12_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S12_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S12_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S12_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S13_TZSID_EN                           TZC_NSEC_TZC_BMX_S13_TZSID_EN
#define TZC_NSEC_TZC_BMX_S13_TZSID_EN_POS                       (6U)
#define TZC_NSEC_TZC_BMX_S13_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S13_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S13_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S13_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S13_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S13_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S13_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S14_TZSID_EN                           TZC_NSEC_TZC_BMX_S14_TZSID_EN
#define TZC_NSEC_TZC_BMX_S14_TZSID_EN_POS                       (8U)
#define TZC_NSEC_TZC_BMX_S14_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S14_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S14_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S14_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S14_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S14_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S14_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S15_TZSID_EN                           TZC_NSEC_TZC_BMX_S15_TZSID_EN
#define TZC_NSEC_TZC_BMX_S15_TZSID_EN_POS                       (10U)
#define TZC_NSEC_TZC_BMX_S15_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S15_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S15_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S15_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S15_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S15_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S15_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S16_TZSID_EN                           TZC_NSEC_TZC_BMX_S16_TZSID_EN
#define TZC_NSEC_TZC_BMX_S16_TZSID_EN_POS                       (12U)
#define TZC_NSEC_TZC_BMX_S16_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S16_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S16_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S16_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S16_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S16_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S16_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S17_TZSID_EN                           TZC_NSEC_TZC_BMX_S17_TZSID_EN
#define TZC_NSEC_TZC_BMX_S17_TZSID_EN_POS                       (14U)
#define TZC_NSEC_TZC_BMX_S17_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S17_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S17_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S17_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S17_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S17_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S17_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S18_TZSID_EN                           TZC_NSEC_TZC_BMX_S18_TZSID_EN
#define TZC_NSEC_TZC_BMX_S18_TZSID_EN_POS                       (16U)
#define TZC_NSEC_TZC_BMX_S18_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S18_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S18_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S18_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S18_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S18_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S18_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S19_TZSID_EN                           TZC_NSEC_TZC_BMX_S19_TZSID_EN
#define TZC_NSEC_TZC_BMX_S19_TZSID_EN_POS                       (18U)
#define TZC_NSEC_TZC_BMX_S19_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S19_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S19_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S19_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S19_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S19_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S19_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1A_TZSID_EN                           TZC_NSEC_TZC_BMX_S1A_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1A_TZSID_EN_POS                       (20U)
#define TZC_NSEC_TZC_BMX_S1A_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S1A_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S1A_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1A_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S1A_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1B_TZSID_EN                           TZC_NSEC_TZC_BMX_S1B_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1B_TZSID_EN_POS                       (22U)
#define TZC_NSEC_TZC_BMX_S1B_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S1B_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S1B_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1B_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1B_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S1B_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1B_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1C_TZSID_EN                           TZC_NSEC_TZC_BMX_S1C_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1C_TZSID_EN_POS                       (24U)
#define TZC_NSEC_TZC_BMX_S1C_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S1C_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S1C_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1C_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1C_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S1C_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1C_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1D_TZSID_EN                           TZC_NSEC_TZC_BMX_S1D_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1D_TZSID_EN_POS                       (26U)
#define TZC_NSEC_TZC_BMX_S1D_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S1D_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S1D_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1D_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1D_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S1D_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1D_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1E_TZSID_EN                           TZC_NSEC_TZC_BMX_S1E_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1E_TZSID_EN_POS                       (28U)
#define TZC_NSEC_TZC_BMX_S1E_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S1E_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S1E_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1E_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1E_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S1E_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1E_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1F_TZSID_EN                           TZC_NSEC_TZC_BMX_S1F_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1F_TZSID_EN_POS                       (30U)
#define TZC_NSEC_TZC_BMX_S1F_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S1F_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S1F_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1F_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1F_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S1F_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1F_TZSID_EN_POS))

/* 0x110 : tzc_bmx_s2 */
#define TZC_NSEC_TZC_BMX_S2_OFFSET                              (0x110)
#define TZC_NSEC_TZC_BMX_S20_TZSID_EN                           TZC_NSEC_TZC_BMX_S20_TZSID_EN
#define TZC_NSEC_TZC_BMX_S20_TZSID_EN_POS                       (0U)
#define TZC_NSEC_TZC_BMX_S20_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S20_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S20_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S20_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S20_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S20_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S20_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S21_TZSID_EN                           TZC_NSEC_TZC_BMX_S21_TZSID_EN
#define TZC_NSEC_TZC_BMX_S21_TZSID_EN_POS                       (2U)
#define TZC_NSEC_TZC_BMX_S21_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S21_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S21_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S21_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S21_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S21_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S21_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S22_TZSID_EN                           TZC_NSEC_TZC_BMX_S22_TZSID_EN
#define TZC_NSEC_TZC_BMX_S22_TZSID_EN_POS                       (4U)
#define TZC_NSEC_TZC_BMX_S22_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S22_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S22_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S22_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S22_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S22_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S22_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S23_TZSID_EN                           TZC_NSEC_TZC_BMX_S23_TZSID_EN
#define TZC_NSEC_TZC_BMX_S23_TZSID_EN_POS                       (6U)
#define TZC_NSEC_TZC_BMX_S23_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S23_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S23_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S23_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S23_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S23_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S23_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S24_TZSID_EN                           TZC_NSEC_TZC_BMX_S24_TZSID_EN
#define TZC_NSEC_TZC_BMX_S24_TZSID_EN_POS                       (8U)
#define TZC_NSEC_TZC_BMX_S24_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S24_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S24_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S24_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S24_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S24_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S24_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S25_TZSID_EN                           TZC_NSEC_TZC_BMX_S25_TZSID_EN
#define TZC_NSEC_TZC_BMX_S25_TZSID_EN_POS                       (10U)
#define TZC_NSEC_TZC_BMX_S25_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S25_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S25_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S25_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S25_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S25_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S25_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S26_TZSID_EN                           TZC_NSEC_TZC_BMX_S26_TZSID_EN
#define TZC_NSEC_TZC_BMX_S26_TZSID_EN_POS                       (12U)
#define TZC_NSEC_TZC_BMX_S26_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S26_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S26_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S26_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S26_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S26_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S26_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S27_TZSID_EN                           TZC_NSEC_TZC_BMX_S27_TZSID_EN
#define TZC_NSEC_TZC_BMX_S27_TZSID_EN_POS                       (14U)
#define TZC_NSEC_TZC_BMX_S27_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S27_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S27_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S27_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S27_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S27_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S27_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S28_TZSID_EN                           TZC_NSEC_TZC_BMX_S28_TZSID_EN
#define TZC_NSEC_TZC_BMX_S28_TZSID_EN_POS                       (16U)
#define TZC_NSEC_TZC_BMX_S28_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S28_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S28_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S28_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S28_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S28_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S28_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S29_TZSID_EN                           TZC_NSEC_TZC_BMX_S29_TZSID_EN
#define TZC_NSEC_TZC_BMX_S29_TZSID_EN_POS                       (18U)
#define TZC_NSEC_TZC_BMX_S29_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S29_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S29_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S29_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S29_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S29_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S29_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S2A_TZSID_EN                           TZC_NSEC_TZC_BMX_S2A_TZSID_EN
#define TZC_NSEC_TZC_BMX_S2A_TZSID_EN_POS                       (20U)
#define TZC_NSEC_TZC_BMX_S2A_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S2A_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S2A_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S2A_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S2A_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S2A_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S2A_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S2B_TZSID_EN                           TZC_NSEC_TZC_BMX_S2B_TZSID_EN
#define TZC_NSEC_TZC_BMX_S2B_TZSID_EN_POS                       (22U)
#define TZC_NSEC_TZC_BMX_S2B_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S2B_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S2B_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S2B_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S2B_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S2B_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S2B_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S2C_TZSID_EN                           TZC_NSEC_TZC_BMX_S2C_TZSID_EN
#define TZC_NSEC_TZC_BMX_S2C_TZSID_EN_POS                       (24U)
#define TZC_NSEC_TZC_BMX_S2C_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S2C_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S2C_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S2C_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S2C_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S2C_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S2C_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S2D_TZSID_EN                           TZC_NSEC_TZC_BMX_S2D_TZSID_EN
#define TZC_NSEC_TZC_BMX_S2D_TZSID_EN_POS                       (26U)
#define TZC_NSEC_TZC_BMX_S2D_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S2D_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S2D_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S2D_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S2D_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S2D_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S2D_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S2E_TZSID_EN                           TZC_NSEC_TZC_BMX_S2E_TZSID_EN
#define TZC_NSEC_TZC_BMX_S2E_TZSID_EN_POS                       (28U)
#define TZC_NSEC_TZC_BMX_S2E_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S2E_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S2E_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S2E_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S2E_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S2E_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S2E_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S2F_TZSID_EN                           TZC_NSEC_TZC_BMX_S2F_TZSID_EN
#define TZC_NSEC_TZC_BMX_S2F_TZSID_EN_POS                       (30U)
#define TZC_NSEC_TZC_BMX_S2F_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_BMX_S2F_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_BMX_S2F_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S2F_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S2F_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_BMX_S2F_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S2F_TZSID_EN_POS))

/* 0x114 : tzc_bmx_s_lock */
#define TZC_NSEC_TZC_BMX_S_LOCK_OFFSET                          (0x114)
#define TZC_NSEC_TZC_BMX_S10_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S10_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S10_TZSID_LOCK_POS                     (0U)
#define TZC_NSEC_TZC_BMX_S10_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S10_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S10_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S10_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S10_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S10_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S10_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S11_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S11_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S11_TZSID_LOCK_POS                     (1U)
#define TZC_NSEC_TZC_BMX_S11_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S11_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S11_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S11_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S11_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S11_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S11_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S12_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S12_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S12_TZSID_LOCK_POS                     (2U)
#define TZC_NSEC_TZC_BMX_S12_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S12_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S12_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S12_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S12_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S12_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S12_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S13_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S13_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S13_TZSID_LOCK_POS                     (3U)
#define TZC_NSEC_TZC_BMX_S13_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S13_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S13_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S13_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S13_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S13_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S13_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S14_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S14_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S14_TZSID_LOCK_POS                     (4U)
#define TZC_NSEC_TZC_BMX_S14_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S14_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S14_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S14_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S14_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S14_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S14_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S15_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S15_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S15_TZSID_LOCK_POS                     (5U)
#define TZC_NSEC_TZC_BMX_S15_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S15_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S15_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S15_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S15_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S15_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S15_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S16_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S16_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S16_TZSID_LOCK_POS                     (6U)
#define TZC_NSEC_TZC_BMX_S16_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S16_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S16_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S16_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S16_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S16_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S16_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S17_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S17_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S17_TZSID_LOCK_POS                     (7U)
#define TZC_NSEC_TZC_BMX_S17_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S17_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S17_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S17_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S17_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S17_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S17_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S18_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S18_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S18_TZSID_LOCK_POS                     (8U)
#define TZC_NSEC_TZC_BMX_S18_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S18_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S18_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S18_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S18_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S18_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S18_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S19_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S19_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S19_TZSID_LOCK_POS                     (9U)
#define TZC_NSEC_TZC_BMX_S19_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S19_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S19_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S19_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S19_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S19_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S19_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1A_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S1A_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1A_TZSID_LOCK_POS                     (10U)
#define TZC_NSEC_TZC_BMX_S1A_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S1A_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S1A_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1A_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S1A_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1B_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S1B_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1B_TZSID_LOCK_POS                     (11U)
#define TZC_NSEC_TZC_BMX_S1B_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S1B_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S1B_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1B_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1B_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S1B_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1B_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1C_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S1C_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1C_TZSID_LOCK_POS                     (12U)
#define TZC_NSEC_TZC_BMX_S1C_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S1C_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S1C_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1C_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1C_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S1C_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1C_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1D_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S1D_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1D_TZSID_LOCK_POS                     (13U)
#define TZC_NSEC_TZC_BMX_S1D_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S1D_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S1D_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1D_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1D_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S1D_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1D_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1E_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S1E_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1E_TZSID_LOCK_POS                     (14U)
#define TZC_NSEC_TZC_BMX_S1E_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S1E_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S1E_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1E_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1E_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S1E_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1E_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1F_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S1F_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1F_TZSID_LOCK_POS                     (15U)
#define TZC_NSEC_TZC_BMX_S1F_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S1F_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S1F_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1F_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1F_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S1F_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1F_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S20_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S20_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S20_TZSID_LOCK_POS                     (16U)
#define TZC_NSEC_TZC_BMX_S20_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S20_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S20_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S20_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S20_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S20_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S20_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S21_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S21_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S21_TZSID_LOCK_POS                     (17U)
#define TZC_NSEC_TZC_BMX_S21_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S21_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S21_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S21_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S21_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S21_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S21_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S22_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S22_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S22_TZSID_LOCK_POS                     (18U)
#define TZC_NSEC_TZC_BMX_S22_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S22_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S22_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S22_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S22_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S22_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S22_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S23_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S23_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S23_TZSID_LOCK_POS                     (19U)
#define TZC_NSEC_TZC_BMX_S23_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S23_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S23_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S23_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S23_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S23_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S23_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S24_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S24_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S24_TZSID_LOCK_POS                     (20U)
#define TZC_NSEC_TZC_BMX_S24_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S24_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S24_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S24_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S24_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S24_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S24_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S25_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S25_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S25_TZSID_LOCK_POS                     (21U)
#define TZC_NSEC_TZC_BMX_S25_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S25_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S25_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S25_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S25_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S25_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S25_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S26_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S26_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S26_TZSID_LOCK_POS                     (22U)
#define TZC_NSEC_TZC_BMX_S26_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S26_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S26_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S26_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S26_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S26_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S26_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S27_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S27_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S27_TZSID_LOCK_POS                     (23U)
#define TZC_NSEC_TZC_BMX_S27_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S27_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S27_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S27_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S27_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S27_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S27_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S28_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S28_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S28_TZSID_LOCK_POS                     (24U)
#define TZC_NSEC_TZC_BMX_S28_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S28_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S28_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S28_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S28_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S28_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S28_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S29_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S29_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S29_TZSID_LOCK_POS                     (25U)
#define TZC_NSEC_TZC_BMX_S29_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S29_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S29_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S29_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S29_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S29_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S29_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S2A_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S2A_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S2A_TZSID_LOCK_POS                     (26U)
#define TZC_NSEC_TZC_BMX_S2A_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S2A_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S2A_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S2A_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S2A_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S2A_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S2A_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S2B_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S2B_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S2B_TZSID_LOCK_POS                     (27U)
#define TZC_NSEC_TZC_BMX_S2B_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S2B_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S2B_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S2B_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S2B_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S2B_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S2B_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S2C_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S2C_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S2C_TZSID_LOCK_POS                     (28U)
#define TZC_NSEC_TZC_BMX_S2C_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S2C_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S2C_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S2C_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S2C_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S2C_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S2C_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S2D_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S2D_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S2D_TZSID_LOCK_POS                     (29U)
#define TZC_NSEC_TZC_BMX_S2D_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S2D_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S2D_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S2D_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S2D_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S2D_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S2D_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S2E_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S2E_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S2E_TZSID_LOCK_POS                     (30U)
#define TZC_NSEC_TZC_BMX_S2E_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S2E_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S2E_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S2E_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S2E_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S2E_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S2E_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S2F_TZSID_LOCK                         TZC_NSEC_TZC_BMX_S2F_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S2F_TZSID_LOCK_POS                     (31U)
#define TZC_NSEC_TZC_BMX_S2F_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_BMX_S2F_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_BMX_S2F_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S2F_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S2F_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_BMX_S2F_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S2F_TZSID_LOCK_POS))

/* 0x118 : tzc_bmx_s1a */
#define TZC_NSEC_TZC_BMX_S1A_OFFSET                             (0x118)
#define TZC_NSEC_TZC_BMX_S1A0_TZSID_EN                          TZC_NSEC_TZC_BMX_S1A0_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1A0_TZSID_EN_POS                      (0U)
#define TZC_NSEC_TZC_BMX_S1A0_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1A0_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1A0_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A0_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1A0_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1A0_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A0_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1A1_TZSID_EN                          TZC_NSEC_TZC_BMX_S1A1_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1A1_TZSID_EN_POS                      (2U)
#define TZC_NSEC_TZC_BMX_S1A1_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1A1_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1A1_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A1_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1A1_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1A1_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A1_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1A2_TZSID_EN                          TZC_NSEC_TZC_BMX_S1A2_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1A2_TZSID_EN_POS                      (4U)
#define TZC_NSEC_TZC_BMX_S1A2_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1A2_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1A2_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A2_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1A2_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1A2_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A2_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1A3_TZSID_EN                          TZC_NSEC_TZC_BMX_S1A3_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1A3_TZSID_EN_POS                      (6U)
#define TZC_NSEC_TZC_BMX_S1A3_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1A3_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1A3_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A3_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1A3_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1A3_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A3_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1A4_TZSID_EN                          TZC_NSEC_TZC_BMX_S1A4_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1A4_TZSID_EN_POS                      (8U)
#define TZC_NSEC_TZC_BMX_S1A4_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1A4_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1A4_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A4_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1A4_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1A4_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A4_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1A5_TZSID_EN                          TZC_NSEC_TZC_BMX_S1A5_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1A5_TZSID_EN_POS                      (10U)
#define TZC_NSEC_TZC_BMX_S1A5_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1A5_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1A5_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A5_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1A5_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1A5_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A5_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1A6_TZSID_EN                          TZC_NSEC_TZC_BMX_S1A6_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1A6_TZSID_EN_POS                      (12U)
#define TZC_NSEC_TZC_BMX_S1A6_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1A6_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1A6_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A6_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1A6_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1A6_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A6_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1A7_TZSID_EN                          TZC_NSEC_TZC_BMX_S1A7_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1A7_TZSID_EN_POS                      (14U)
#define TZC_NSEC_TZC_BMX_S1A7_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1A7_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1A7_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A7_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1A7_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1A7_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A7_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1A8_TZSID_EN                          TZC_NSEC_TZC_BMX_S1A8_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1A8_TZSID_EN_POS                      (16U)
#define TZC_NSEC_TZC_BMX_S1A8_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1A8_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1A8_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A8_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1A8_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1A8_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A8_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1A9_TZSID_EN                          TZC_NSEC_TZC_BMX_S1A9_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1A9_TZSID_EN_POS                      (18U)
#define TZC_NSEC_TZC_BMX_S1A9_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1A9_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1A9_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A9_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1A9_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1A9_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A9_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1AA_TZSID_EN                          TZC_NSEC_TZC_BMX_S1AA_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1AA_TZSID_EN_POS                      (20U)
#define TZC_NSEC_TZC_BMX_S1AA_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1AA_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1AA_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AA_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1AA_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1AA_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AA_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1AB_TZSID_EN                          TZC_NSEC_TZC_BMX_S1AB_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1AB_TZSID_EN_POS                      (22U)
#define TZC_NSEC_TZC_BMX_S1AB_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1AB_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1AB_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AB_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1AB_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1AB_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AB_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1AC_TZSID_EN                          TZC_NSEC_TZC_BMX_S1AC_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1AC_TZSID_EN_POS                      (24U)
#define TZC_NSEC_TZC_BMX_S1AC_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1AC_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1AC_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AC_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1AC_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1AC_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AC_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1AD_TZSID_EN                          TZC_NSEC_TZC_BMX_S1AD_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1AD_TZSID_EN_POS                      (26U)
#define TZC_NSEC_TZC_BMX_S1AD_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1AD_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1AD_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AD_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1AD_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1AD_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AD_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1AE_TZSID_EN                          TZC_NSEC_TZC_BMX_S1AE_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1AE_TZSID_EN_POS                      (28U)
#define TZC_NSEC_TZC_BMX_S1AE_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1AE_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1AE_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AE_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1AE_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1AE_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AE_TZSID_EN_POS))
#define TZC_NSEC_TZC_BMX_S1AF_TZSID_EN                          TZC_NSEC_TZC_BMX_S1AF_TZSID_EN
#define TZC_NSEC_TZC_BMX_S1AF_TZSID_EN_POS                      (30U)
#define TZC_NSEC_TZC_BMX_S1AF_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_BMX_S1AF_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_BMX_S1AF_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AF_TZSID_EN_POS)
#define TZC_NSEC_TZC_BMX_S1AF_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_BMX_S1AF_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AF_TZSID_EN_POS))

/* 0x11C : tzc_bmx_s1a_lock */
#define TZC_NSEC_TZC_BMX_S1A_LOCK_OFFSET                        (0x11C)
#define TZC_NSEC_TZC_BMX_S1A0_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1A0_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1A0_TZSID_LOCK_POS                    (0U)
#define TZC_NSEC_TZC_BMX_S1A0_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1A0_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1A0_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A0_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1A0_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1A0_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A0_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1A1_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1A1_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1A1_TZSID_LOCK_POS                    (1U)
#define TZC_NSEC_TZC_BMX_S1A1_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1A1_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1A1_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A1_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1A1_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1A1_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A1_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1A2_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1A2_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1A2_TZSID_LOCK_POS                    (2U)
#define TZC_NSEC_TZC_BMX_S1A2_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1A2_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1A2_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A2_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1A2_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1A2_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A2_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1A3_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1A3_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1A3_TZSID_LOCK_POS                    (3U)
#define TZC_NSEC_TZC_BMX_S1A3_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1A3_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1A3_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A3_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1A3_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1A3_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A3_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1A4_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1A4_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1A4_TZSID_LOCK_POS                    (4U)
#define TZC_NSEC_TZC_BMX_S1A4_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1A4_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1A4_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A4_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1A4_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1A4_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A4_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1A5_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1A5_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1A5_TZSID_LOCK_POS                    (5U)
#define TZC_NSEC_TZC_BMX_S1A5_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1A5_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1A5_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A5_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1A5_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1A5_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A5_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1A6_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1A6_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1A6_TZSID_LOCK_POS                    (6U)
#define TZC_NSEC_TZC_BMX_S1A6_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1A6_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1A6_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A6_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1A6_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1A6_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A6_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1A7_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1A7_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1A7_TZSID_LOCK_POS                    (7U)
#define TZC_NSEC_TZC_BMX_S1A7_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1A7_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1A7_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A7_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1A7_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1A7_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A7_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1A8_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1A8_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1A8_TZSID_LOCK_POS                    (8U)
#define TZC_NSEC_TZC_BMX_S1A8_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1A8_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1A8_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A8_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1A8_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1A8_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A8_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1A9_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1A9_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1A9_TZSID_LOCK_POS                    (9U)
#define TZC_NSEC_TZC_BMX_S1A9_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1A9_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1A9_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A9_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1A9_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1A9_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1A9_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1AA_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1AA_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1AA_TZSID_LOCK_POS                    (10U)
#define TZC_NSEC_TZC_BMX_S1AA_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1AA_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1AA_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AA_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1AA_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1AA_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AA_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1AB_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1AB_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1AB_TZSID_LOCK_POS                    (11U)
#define TZC_NSEC_TZC_BMX_S1AB_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1AB_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1AB_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AB_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1AB_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1AB_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AB_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1AC_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1AC_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1AC_TZSID_LOCK_POS                    (12U)
#define TZC_NSEC_TZC_BMX_S1AC_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1AC_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1AC_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AC_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1AC_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1AC_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AC_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1AD_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1AD_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1AD_TZSID_LOCK_POS                    (13U)
#define TZC_NSEC_TZC_BMX_S1AD_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1AD_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1AD_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AD_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1AD_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1AD_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AD_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1AE_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1AE_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1AE_TZSID_LOCK_POS                    (14U)
#define TZC_NSEC_TZC_BMX_S1AE_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1AE_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1AE_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AE_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1AE_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1AE_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AE_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_BMX_S1AF_TZSID_LOCK                        TZC_NSEC_TZC_BMX_S1AF_TZSID_LOCK
#define TZC_NSEC_TZC_BMX_S1AF_TZSID_LOCK_POS                    (15U)
#define TZC_NSEC_TZC_BMX_S1AF_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_BMX_S1AF_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_BMX_S1AF_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AF_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_BMX_S1AF_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_BMX_S1AF_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_BMX_S1AF_TZSID_LOCK_POS))

/* 0x140 : tzc_ocram_tzsrg_ctrl */
#define TZC_NSEC_TZC_OCRAM_TZSRG_CTRL_OFFSET                    (0x140)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_ID_EN                       TZC_NSEC_TZC_OCRAM_TZSRG_R0_ID_EN
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_ID_EN_POS                   (0U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_ID_EN_LEN                   (4U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_ID_EN_MSK                   (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_ID_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_ID_EN_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_ID_EN_UMSK                  (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_ID_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_ID_EN_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_ID_EN                       TZC_NSEC_TZC_OCRAM_TZSRG_R1_ID_EN
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_ID_EN_POS                   (4U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_ID_EN_LEN                   (4U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_ID_EN_MSK                   (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_ID_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_ID_EN_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_ID_EN_UMSK                  (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_ID_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_ID_EN_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_ID_EN                       TZC_NSEC_TZC_OCRAM_TZSRG_R2_ID_EN
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_ID_EN_POS                   (8U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_ID_EN_LEN                   (4U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_ID_EN_MSK                   (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_ID_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_ID_EN_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_ID_EN_UMSK                  (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_ID_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_ID_EN_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_ID_EN                       TZC_NSEC_TZC_OCRAM_TZSRG_RX_ID_EN
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_ID_EN_POS                   (12U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_ID_EN_LEN                   (4U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_ID_EN_MSK                   (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_RX_ID_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_RX_ID_EN_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_ID_EN_UMSK                  (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_RX_ID_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_RX_ID_EN_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_EN                          TZC_NSEC_TZC_OCRAM_TZSRG_R0_EN
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_EN_POS                      (16U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_EN_LEN                      (1U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_EN_MSK                      (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_EN_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_EN_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_EN                          TZC_NSEC_TZC_OCRAM_TZSRG_R1_EN
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_EN_POS                      (17U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_EN_LEN                      (1U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_EN_MSK                      (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_EN_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_EN_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_EN                          TZC_NSEC_TZC_OCRAM_TZSRG_R2_EN
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_EN_POS                      (18U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_EN_LEN                      (1U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_EN_MSK                      (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_EN_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_EN_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_EN                          TZC_NSEC_TZC_OCRAM_TZSRG_RX_EN
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_EN_POS                      (19U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_EN_LEN                      (1U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_EN_MSK                      (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_RX_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_RX_EN_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_RX_EN_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_RX_EN_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_LOCK                        TZC_NSEC_TZC_OCRAM_TZSRG_R0_LOCK
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_LOCK_POS                    (20U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_LOCK_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_LOCK_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_LOCK_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_LOCK_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_LOCK                        TZC_NSEC_TZC_OCRAM_TZSRG_R1_LOCK
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_LOCK_POS                    (21U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_LOCK_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_LOCK_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_LOCK_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_LOCK_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_LOCK                        TZC_NSEC_TZC_OCRAM_TZSRG_R2_LOCK
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_LOCK_POS                    (22U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_LOCK_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_LOCK_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_LOCK_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_LOCK_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_LOCK                        TZC_NSEC_TZC_OCRAM_TZSRG_RX_LOCK
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_LOCK_POS                    (23U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_RX_LOCK_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_RX_LOCK_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_RX_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_RX_LOCK_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_RX_LOCK_POS))

/* 0x144 : tzc_ocram_tzsrg_adr_mask */
#define TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_OFFSET                (0x144)
#define TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK                       TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK
#define TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_POS                   (0U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_LEN                   (10U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_MSK                   (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_UMSK                  (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_LOCK                  TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_LOCK
#define TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_LOCK_POS              (16U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_LOCK_LEN              (1U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_LOCK_MSK              (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_LOCK_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_LOCK_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_LOCK_UMSK             (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_LOCK_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_ADR_MASK_LOCK_POS))

/* 0x148 : tzc_ocram_tzsrg_r0 */
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_OFFSET                      (0x148)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_END                         TZC_NSEC_TZC_OCRAM_TZSRG_R0_END
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_END_POS                     (0U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_END_LEN                     (10U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_END_MSK                     (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_END_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_END_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_END_UMSK                    (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_END_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_END_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_START                       TZC_NSEC_TZC_OCRAM_TZSRG_R0_START
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_START_POS                   (16U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_START_LEN                   (10U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_START_MSK                   (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_START_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_START_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R0_START_UMSK                  (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_START_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R0_START_POS))

/* 0x14C : tzc_ocram_tzsrg_r1 */
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_OFFSET                      (0x14C)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_END                         TZC_NSEC_TZC_OCRAM_TZSRG_R1_END
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_END_POS                     (0U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_END_LEN                     (10U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_END_MSK                     (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_END_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_END_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_END_UMSK                    (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_END_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_END_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_START                       TZC_NSEC_TZC_OCRAM_TZSRG_R1_START
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_START_POS                   (16U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_START_LEN                   (10U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_START_MSK                   (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_START_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_START_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R1_START_UMSK                  (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_START_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R1_START_POS))

/* 0x150 : tzc_ocram_tzsrg_r2 */
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_OFFSET                      (0x150)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_END                         TZC_NSEC_TZC_OCRAM_TZSRG_R2_END
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_END_POS                     (0U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_END_LEN                     (10U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_END_MSK                     (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_END_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_END_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_END_UMSK                    (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_END_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_END_POS))
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_START                       TZC_NSEC_TZC_OCRAM_TZSRG_R2_START
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_START_POS                   (16U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_START_LEN                   (10U)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_START_MSK                   (((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_START_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_START_POS)
#define TZC_NSEC_TZC_OCRAM_TZSRG_R2_START_UMSK                  (~(((1U<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_START_LEN)-1)<<TZC_NSEC_TZC_OCRAM_TZSRG_R2_START_POS))

/* 0x154 : tzc_ocram_tzsrg_r3 */
#define TZC_NSEC_TZC_OCRAM_TZSRG_R3_OFFSET                      (0x154)

/* 0x180 : tzc_wram_tzsrg_ctrl */
#define TZC_NSEC_TZC_WRAM_TZSRG_CTRL_OFFSET                     (0x180)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_ID_EN                        TZC_NSEC_TZC_WRAM_TZSRG_R0_ID_EN
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_ID_EN_POS                    (0U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_ID_EN_LEN                    (4U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_ID_EN_MSK                    (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R0_ID_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R0_ID_EN_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_ID_EN_UMSK                   (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R0_ID_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R0_ID_EN_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_ID_EN                        TZC_NSEC_TZC_WRAM_TZSRG_R1_ID_EN
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_ID_EN_POS                    (4U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_ID_EN_LEN                    (4U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_ID_EN_MSK                    (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R1_ID_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R1_ID_EN_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_ID_EN_UMSK                   (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R1_ID_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R1_ID_EN_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_ID_EN                        TZC_NSEC_TZC_WRAM_TZSRG_R2_ID_EN
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_ID_EN_POS                    (8U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_ID_EN_LEN                    (4U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_ID_EN_MSK                    (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R2_ID_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R2_ID_EN_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_ID_EN_UMSK                   (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R2_ID_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R2_ID_EN_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_ID_EN                        TZC_NSEC_TZC_WRAM_TZSRG_RX_ID_EN
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_ID_EN_POS                    (12U)
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_ID_EN_LEN                    (4U)
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_ID_EN_MSK                    (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_RX_ID_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_RX_ID_EN_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_ID_EN_UMSK                   (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_RX_ID_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_RX_ID_EN_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_EN                           TZC_NSEC_TZC_WRAM_TZSRG_R0_EN
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_EN_POS                       (16U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_EN_LEN                       (1U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_EN_MSK                       (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R0_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R0_EN_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R0_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R0_EN_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_EN                           TZC_NSEC_TZC_WRAM_TZSRG_R1_EN
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_EN_POS                       (17U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_EN_LEN                       (1U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_EN_MSK                       (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R1_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R1_EN_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R1_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R1_EN_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_EN                           TZC_NSEC_TZC_WRAM_TZSRG_R2_EN
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_EN_POS                       (18U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_EN_LEN                       (1U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_EN_MSK                       (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R2_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R2_EN_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R2_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R2_EN_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_EN                           TZC_NSEC_TZC_WRAM_TZSRG_RX_EN
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_EN_POS                       (19U)
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_EN_LEN                       (1U)
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_EN_MSK                       (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_RX_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_RX_EN_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_RX_EN_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_RX_EN_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_LOCK                         TZC_NSEC_TZC_WRAM_TZSRG_R0_LOCK
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_LOCK_POS                     (20U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R0_LOCK_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R0_LOCK_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R0_LOCK_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R0_LOCK_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_LOCK                         TZC_NSEC_TZC_WRAM_TZSRG_R1_LOCK
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_LOCK_POS                     (21U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R1_LOCK_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R1_LOCK_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R1_LOCK_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R1_LOCK_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_LOCK                         TZC_NSEC_TZC_WRAM_TZSRG_R2_LOCK
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_LOCK_POS                     (22U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R2_LOCK_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R2_LOCK_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R2_LOCK_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R2_LOCK_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_LOCK                         TZC_NSEC_TZC_WRAM_TZSRG_RX_LOCK
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_LOCK_POS                     (23U)
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_RX_LOCK_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_RX_LOCK_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_RX_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_RX_LOCK_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_RX_LOCK_POS))

/* 0x184 : tzc_wram_tzsrg_adr_mask */
#define TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_OFFSET                 (0x184)
#define TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK                        TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK
#define TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_POS                    (0U)
#define TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_LEN                    (10U)
#define TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_MSK                    (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_UMSK                   (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_LOCK                   TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_LOCK
#define TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_LOCK_POS               (16U)
#define TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_LOCK_LEN               (1U)
#define TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_LOCK_MSK               (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_LOCK_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_LOCK_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_LOCK_UMSK              (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_LOCK_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_ADR_MASK_LOCK_POS))

/* 0x188 : tzc_wram_tzsrg_r0 */
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_OFFSET                       (0x188)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_END                          TZC_NSEC_TZC_WRAM_TZSRG_R0_END
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_END_POS                      (0U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_END_LEN                      (10U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_END_MSK                      (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R0_END_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R0_END_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_END_UMSK                     (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R0_END_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R0_END_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_START                        TZC_NSEC_TZC_WRAM_TZSRG_R0_START
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_START_POS                    (16U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_START_LEN                    (10U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_START_MSK                    (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R0_START_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R0_START_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R0_START_UMSK                   (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R0_START_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R0_START_POS))

/* 0x18C : tzc_wram_tzsrg_r1 */
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_OFFSET                       (0x18C)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_END                          TZC_NSEC_TZC_WRAM_TZSRG_R1_END
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_END_POS                      (0U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_END_LEN                      (10U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_END_MSK                      (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R1_END_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R1_END_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_END_UMSK                     (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R1_END_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R1_END_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_START                        TZC_NSEC_TZC_WRAM_TZSRG_R1_START
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_START_POS                    (16U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_START_LEN                    (10U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_START_MSK                    (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R1_START_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R1_START_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R1_START_UMSK                   (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R1_START_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R1_START_POS))

/* 0x190 : tzc_wram_tzsrg_r2 */
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_OFFSET                       (0x190)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_END                          TZC_NSEC_TZC_WRAM_TZSRG_R2_END
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_END_POS                      (0U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_END_LEN                      (10U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_END_MSK                      (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R2_END_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R2_END_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_END_UMSK                     (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R2_END_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R2_END_POS))
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_START                        TZC_NSEC_TZC_WRAM_TZSRG_R2_START
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_START_POS                    (16U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_START_LEN                    (10U)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_START_MSK                    (((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R2_START_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R2_START_POS)
#define TZC_NSEC_TZC_WRAM_TZSRG_R2_START_UMSK                   (~(((1U<<TZC_NSEC_TZC_WRAM_TZSRG_R2_START_LEN)-1)<<TZC_NSEC_TZC_WRAM_TZSRG_R2_START_POS))

/* 0x194 : tzc_wram_tzsrg_r3 */
#define TZC_NSEC_TZC_WRAM_TZSRG_R3_OFFSET                       (0x194)

/* 0x198 : tzc_wifi_dbg */
#define TZC_NSEC_TZC_WIFI_DBG_OFFSET                            (0x198)
#define TZC_NSEC_TZC_MAC_DBG_DIS                                TZC_NSEC_TZC_MAC_DBG_DIS
#define TZC_NSEC_TZC_MAC_DBG_DIS_POS                            (0U)
#define TZC_NSEC_TZC_MAC_DBG_DIS_LEN                            (1U)
#define TZC_NSEC_TZC_MAC_DBG_DIS_MSK                            (((1U<<TZC_NSEC_TZC_MAC_DBG_DIS_LEN)-1)<<TZC_NSEC_TZC_MAC_DBG_DIS_POS)
#define TZC_NSEC_TZC_MAC_DBG_DIS_UMSK                           (~(((1U<<TZC_NSEC_TZC_MAC_DBG_DIS_LEN)-1)<<TZC_NSEC_TZC_MAC_DBG_DIS_POS))

/* 0x240 : tzc_pdm_ctrl */
#define TZC_NSEC_TZC_PDM_CTRL_OFFSET                            (0x240)

/* 0x244 : tzc_uart_ctrl */
#define TZC_NSEC_TZC_UART_CTRL_OFFSET                           (0x244)

/* 0x248 : tzc_i2c_ctrl */
#define TZC_NSEC_TZC_I2C_CTRL_OFFSET                            (0x248)

/* 0x24C : tzc_timer_ctrl */
#define TZC_NSEC_TZC_TIMER_CTRL_OFFSET                          (0x24C)

/* 0x250 : tzc_i2s_ctrl */
#define TZC_NSEC_TZC_I2S_CTRL_OFFSET                            (0x250)

/* 0x280 : tzc_sf_tzsrg_ctrl */
#define TZC_NSEC_TZC_SF_TZSRG_CTRL_OFFSET                       (0x280)
#define TZC_NSEC_TZC_SF_TZSRG_R0_ID_EN                          TZC_NSEC_TZC_SF_TZSRG_R0_ID_EN
#define TZC_NSEC_TZC_SF_TZSRG_R0_ID_EN_POS                      (0U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_ID_EN_LEN                      (4U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_ID_EN_MSK                      (((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_ID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_ID_EN_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R0_ID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_ID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_ID_EN_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R1_ID_EN                          TZC_NSEC_TZC_SF_TZSRG_R1_ID_EN
#define TZC_NSEC_TZC_SF_TZSRG_R1_ID_EN_POS                      (4U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_ID_EN_LEN                      (4U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_ID_EN_MSK                      (((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_ID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_ID_EN_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R1_ID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_ID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_ID_EN_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R2_ID_EN                          TZC_NSEC_TZC_SF_TZSRG_R2_ID_EN
#define TZC_NSEC_TZC_SF_TZSRG_R2_ID_EN_POS                      (8U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_ID_EN_LEN                      (4U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_ID_EN_MSK                      (((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_ID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_ID_EN_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R2_ID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_ID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_ID_EN_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R3_ID_EN                          TZC_NSEC_TZC_SF_TZSRG_R3_ID_EN
#define TZC_NSEC_TZC_SF_TZSRG_R3_ID_EN_POS                      (12U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_ID_EN_LEN                      (4U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_ID_EN_MSK                      (((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_ID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_ID_EN_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R3_ID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_ID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_ID_EN_POS))
#define TZC_NSEC_TZC_SF_TZSRG_RX_ID_EN                          TZC_NSEC_TZC_SF_TZSRG_RX_ID_EN
#define TZC_NSEC_TZC_SF_TZSRG_RX_ID_EN_POS                      (16U)
#define TZC_NSEC_TZC_SF_TZSRG_RX_ID_EN_LEN                      (4U)
#define TZC_NSEC_TZC_SF_TZSRG_RX_ID_EN_MSK                      (((1U<<TZC_NSEC_TZC_SF_TZSRG_RX_ID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_RX_ID_EN_POS)
#define TZC_NSEC_TZC_SF_TZSRG_RX_ID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_RX_ID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_RX_ID_EN_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R0_EN                             TZC_NSEC_TZC_SF_TZSRG_R0_EN
#define TZC_NSEC_TZC_SF_TZSRG_R0_EN_POS                         (20U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_EN_LEN                         (1U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_EN_MSK                         (((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_EN_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R0_EN_UMSK                        (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_EN_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R1_EN                             TZC_NSEC_TZC_SF_TZSRG_R1_EN
#define TZC_NSEC_TZC_SF_TZSRG_R1_EN_POS                         (21U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_EN_LEN                         (1U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_EN_MSK                         (((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_EN_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R1_EN_UMSK                        (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_EN_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R2_EN                             TZC_NSEC_TZC_SF_TZSRG_R2_EN
#define TZC_NSEC_TZC_SF_TZSRG_R2_EN_POS                         (22U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_EN_LEN                         (1U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_EN_MSK                         (((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_EN_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R2_EN_UMSK                        (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_EN_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R3_EN                             TZC_NSEC_TZC_SF_TZSRG_R3_EN
#define TZC_NSEC_TZC_SF_TZSRG_R3_EN_POS                         (23U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_EN_LEN                         (1U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_EN_MSK                         (((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_EN_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R3_EN_UMSK                        (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_EN_POS))
#define TZC_NSEC_TZC_SF_TZSRG_RX_EN                             TZC_NSEC_TZC_SF_TZSRG_RX_EN
#define TZC_NSEC_TZC_SF_TZSRG_RX_EN_POS                         (24U)
#define TZC_NSEC_TZC_SF_TZSRG_RX_EN_LEN                         (1U)
#define TZC_NSEC_TZC_SF_TZSRG_RX_EN_MSK                         (((1U<<TZC_NSEC_TZC_SF_TZSRG_RX_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_RX_EN_POS)
#define TZC_NSEC_TZC_SF_TZSRG_RX_EN_UMSK                        (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_RX_EN_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_RX_EN_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R0_LOCK                           TZC_NSEC_TZC_SF_TZSRG_R0_LOCK
#define TZC_NSEC_TZC_SF_TZSRG_R0_LOCK_POS                       (25U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_LOCK_LEN                       (1U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_LOCK_MSK                       (((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_LOCK_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R0_LOCK_UMSK                      (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_LOCK_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R1_LOCK                           TZC_NSEC_TZC_SF_TZSRG_R1_LOCK
#define TZC_NSEC_TZC_SF_TZSRG_R1_LOCK_POS                       (26U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_LOCK_LEN                       (1U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_LOCK_MSK                       (((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_LOCK_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R1_LOCK_UMSK                      (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_LOCK_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R2_LOCK                           TZC_NSEC_TZC_SF_TZSRG_R2_LOCK
#define TZC_NSEC_TZC_SF_TZSRG_R2_LOCK_POS                       (27U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_LOCK_LEN                       (1U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_LOCK_MSK                       (((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_LOCK_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R2_LOCK_UMSK                      (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_LOCK_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R3_LOCK                           TZC_NSEC_TZC_SF_TZSRG_R3_LOCK
#define TZC_NSEC_TZC_SF_TZSRG_R3_LOCK_POS                       (28U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_LOCK_LEN                       (1U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_LOCK_MSK                       (((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_LOCK_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R3_LOCK_UMSK                      (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_LOCK_POS))
#define TZC_NSEC_TZC_SF_TZSRG_RX_LOCK                           TZC_NSEC_TZC_SF_TZSRG_RX_LOCK
#define TZC_NSEC_TZC_SF_TZSRG_RX_LOCK_POS                       (29U)
#define TZC_NSEC_TZC_SF_TZSRG_RX_LOCK_LEN                       (1U)
#define TZC_NSEC_TZC_SF_TZSRG_RX_LOCK_MSK                       (((1U<<TZC_NSEC_TZC_SF_TZSRG_RX_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_RX_LOCK_POS)
#define TZC_NSEC_TZC_SF_TZSRG_RX_LOCK_UMSK                      (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_RX_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_RX_LOCK_POS))

/* 0x284 : tzc_sf_tzsrg_adr_mask */
#define TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_OFFSET                   (0x284)
#define TZC_NSEC_TZC_SF_TZSRG_ADR_MASK                          TZC_NSEC_TZC_SF_TZSRG_ADR_MASK
#define TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_POS                      (0U)
#define TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_LEN                      (19U)
#define TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_MSK                      (((1U<<TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_POS)
#define TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_UMSK                     (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_POS))
#define TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_LOCK                     TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_LOCK
#define TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_LOCK_POS                 (31U)
#define TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_LOCK_LEN                 (1U)
#define TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_LOCK_MSK                 (((1U<<TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_LOCK_POS)
#define TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_LOCK_UMSK                (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_ADR_MASK_LOCK_POS))

/* 0x288 : tzc_sf_tzsrg_r0 */
#define TZC_NSEC_TZC_SF_TZSRG_R0_OFFSET                         (0x288)
#define TZC_NSEC_TZC_SF_TZSRG_R0_END                            TZC_NSEC_TZC_SF_TZSRG_R0_END
#define TZC_NSEC_TZC_SF_TZSRG_R0_END_POS                        (0U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_END_LEN                        (16U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_END_MSK                        (((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_END_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_END_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R0_END_UMSK                       (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_END_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_END_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R0_START                          TZC_NSEC_TZC_SF_TZSRG_R0_START
#define TZC_NSEC_TZC_SF_TZSRG_R0_START_POS                      (16U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_START_LEN                      (16U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_START_MSK                      (((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_START_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_START_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R0_START_UMSK                     (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_START_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_START_POS))

/* 0x28C : tzc_sf_tzsrg_r1 */
#define TZC_NSEC_TZC_SF_TZSRG_R1_OFFSET                         (0x28C)
#define TZC_NSEC_TZC_SF_TZSRG_R1_END                            TZC_NSEC_TZC_SF_TZSRG_R1_END
#define TZC_NSEC_TZC_SF_TZSRG_R1_END_POS                        (0U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_END_LEN                        (16U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_END_MSK                        (((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_END_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_END_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R1_END_UMSK                       (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_END_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_END_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R1_START                          TZC_NSEC_TZC_SF_TZSRG_R1_START
#define TZC_NSEC_TZC_SF_TZSRG_R1_START_POS                      (16U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_START_LEN                      (16U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_START_MSK                      (((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_START_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_START_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R1_START_UMSK                     (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_START_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_START_POS))

/* 0x290 : tzc_sf_tzsrg_r2 */
#define TZC_NSEC_TZC_SF_TZSRG_R2_OFFSET                         (0x290)
#define TZC_NSEC_TZC_SF_TZSRG_R2_END                            TZC_NSEC_TZC_SF_TZSRG_R2_END
#define TZC_NSEC_TZC_SF_TZSRG_R2_END_POS                        (0U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_END_LEN                        (16U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_END_MSK                        (((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_END_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_END_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R2_END_UMSK                       (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_END_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_END_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R2_START                          TZC_NSEC_TZC_SF_TZSRG_R2_START
#define TZC_NSEC_TZC_SF_TZSRG_R2_START_POS                      (16U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_START_LEN                      (16U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_START_MSK                      (((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_START_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_START_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R2_START_UMSK                     (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_START_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_START_POS))

/* 0x294 : tzc_sf_tzsrg_r3 */
#define TZC_NSEC_TZC_SF_TZSRG_R3_OFFSET                         (0x294)
#define TZC_NSEC_TZC_SF_TZSRG_R3_END                            TZC_NSEC_TZC_SF_TZSRG_R3_END
#define TZC_NSEC_TZC_SF_TZSRG_R3_END_POS                        (0U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_END_LEN                        (16U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_END_MSK                        (((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_END_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_END_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R3_END_UMSK                       (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_END_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_END_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R3_START                          TZC_NSEC_TZC_SF_TZSRG_R3_START
#define TZC_NSEC_TZC_SF_TZSRG_R3_START_POS                      (16U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_START_LEN                      (16U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_START_MSK                      (((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_START_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_START_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R3_START_UMSK                     (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_START_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_START_POS))

/* 0x298 : tzc_sf_tzsrg_msb */
#define TZC_NSEC_TZC_SF_TZSRG_MSB_OFFSET                        (0x298)
#define TZC_NSEC_TZC_SF_TZSRG_R0_END_MSB                        TZC_NSEC_TZC_SF_TZSRG_R0_END_MSB
#define TZC_NSEC_TZC_SF_TZSRG_R0_END_MSB_POS                    (0U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_END_MSB_LEN                    (3U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_END_MSB_MSK                    (((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_END_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_END_MSB_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R0_END_MSB_UMSK                   (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_END_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_END_MSB_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R0_START_MSB                      TZC_NSEC_TZC_SF_TZSRG_R0_START_MSB
#define TZC_NSEC_TZC_SF_TZSRG_R0_START_MSB_POS                  (4U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_START_MSB_LEN                  (3U)
#define TZC_NSEC_TZC_SF_TZSRG_R0_START_MSB_MSK                  (((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_START_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_START_MSB_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R0_START_MSB_UMSK                 (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R0_START_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R0_START_MSB_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R1_END_MSB                        TZC_NSEC_TZC_SF_TZSRG_R1_END_MSB
#define TZC_NSEC_TZC_SF_TZSRG_R1_END_MSB_POS                    (8U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_END_MSB_LEN                    (3U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_END_MSB_MSK                    (((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_END_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_END_MSB_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R1_END_MSB_UMSK                   (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_END_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_END_MSB_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R1_START_MSB                      TZC_NSEC_TZC_SF_TZSRG_R1_START_MSB
#define TZC_NSEC_TZC_SF_TZSRG_R1_START_MSB_POS                  (12U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_START_MSB_LEN                  (3U)
#define TZC_NSEC_TZC_SF_TZSRG_R1_START_MSB_MSK                  (((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_START_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_START_MSB_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R1_START_MSB_UMSK                 (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R1_START_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R1_START_MSB_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R2_END_MSB                        TZC_NSEC_TZC_SF_TZSRG_R2_END_MSB
#define TZC_NSEC_TZC_SF_TZSRG_R2_END_MSB_POS                    (16U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_END_MSB_LEN                    (3U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_END_MSB_MSK                    (((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_END_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_END_MSB_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R2_END_MSB_UMSK                   (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_END_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_END_MSB_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R2_START_MSB                      TZC_NSEC_TZC_SF_TZSRG_R2_START_MSB
#define TZC_NSEC_TZC_SF_TZSRG_R2_START_MSB_POS                  (20U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_START_MSB_LEN                  (3U)
#define TZC_NSEC_TZC_SF_TZSRG_R2_START_MSB_MSK                  (((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_START_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_START_MSB_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R2_START_MSB_UMSK                 (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R2_START_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R2_START_MSB_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R3_END_MSB                        TZC_NSEC_TZC_SF_TZSRG_R3_END_MSB
#define TZC_NSEC_TZC_SF_TZSRG_R3_END_MSB_POS                    (24U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_END_MSB_LEN                    (3U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_END_MSB_MSK                    (((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_END_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_END_MSB_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R3_END_MSB_UMSK                   (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_END_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_END_MSB_POS))
#define TZC_NSEC_TZC_SF_TZSRG_R3_START_MSB                      TZC_NSEC_TZC_SF_TZSRG_R3_START_MSB
#define TZC_NSEC_TZC_SF_TZSRG_R3_START_MSB_POS                  (28U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_START_MSB_LEN                  (3U)
#define TZC_NSEC_TZC_SF_TZSRG_R3_START_MSB_MSK                  (((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_START_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_START_MSB_POS)
#define TZC_NSEC_TZC_SF_TZSRG_R3_START_MSB_UMSK                 (~(((1U<<TZC_NSEC_TZC_SF_TZSRG_R3_START_MSB_LEN)-1)<<TZC_NSEC_TZC_SF_TZSRG_R3_START_MSB_POS))

/* 0x300 : tzc_mm_bmx_tzmid */
#define TZC_NSEC_TZC_MM_BMX_TZMID_OFFSET                        (0x300)
#define TZC_NSEC_TZC_CODEC_TZMID                                TZC_NSEC_TZC_CODEC_TZMID
#define TZC_NSEC_TZC_CODEC_TZMID_POS                            (2U)
#define TZC_NSEC_TZC_CODEC_TZMID_LEN                            (1U)
#define TZC_NSEC_TZC_CODEC_TZMID_MSK                            (((1U<<TZC_NSEC_TZC_CODEC_TZMID_LEN)-1)<<TZC_NSEC_TZC_CODEC_TZMID_POS)
#define TZC_NSEC_TZC_CODEC_TZMID_UMSK                           (~(((1U<<TZC_NSEC_TZC_CODEC_TZMID_LEN)-1)<<TZC_NSEC_TZC_CODEC_TZMID_POS))
#define TZC_NSEC_TZC_CODEC_TZMID_SEL                            TZC_NSEC_TZC_CODEC_TZMID_SEL
#define TZC_NSEC_TZC_CODEC_TZMID_SEL_POS                        (18U)
#define TZC_NSEC_TZC_CODEC_TZMID_SEL_LEN                        (1U)
#define TZC_NSEC_TZC_CODEC_TZMID_SEL_MSK                        (((1U<<TZC_NSEC_TZC_CODEC_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_CODEC_TZMID_SEL_POS)
#define TZC_NSEC_TZC_CODEC_TZMID_SEL_UMSK                       (~(((1U<<TZC_NSEC_TZC_CODEC_TZMID_SEL_LEN)-1)<<TZC_NSEC_TZC_CODEC_TZMID_SEL_POS))

/* 0x304 : tzc_mm_bmx_tzmid_lock */
#define TZC_NSEC_TZC_MM_BMX_TZMID_LOCK_OFFSET                   (0x304)
#define TZC_NSEC_TZC_CODEC_TZMID_LOCK                           TZC_NSEC_TZC_CODEC_TZMID_LOCK
#define TZC_NSEC_TZC_CODEC_TZMID_LOCK_POS                       (2U)
#define TZC_NSEC_TZC_CODEC_TZMID_LOCK_LEN                       (1U)
#define TZC_NSEC_TZC_CODEC_TZMID_LOCK_MSK                       (((1U<<TZC_NSEC_TZC_CODEC_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_CODEC_TZMID_LOCK_POS)
#define TZC_NSEC_TZC_CODEC_TZMID_LOCK_UMSK                      (~(((1U<<TZC_NSEC_TZC_CODEC_TZMID_LOCK_LEN)-1)<<TZC_NSEC_TZC_CODEC_TZMID_LOCK_POS))

/* 0x308 : tzc_mm_bmx_s0 */
#define TZC_NSEC_TZC_MM_BMX_S0_OFFSET                           (0x308)

/* 0x30C : tzc_mm_bmx_s1 */
#define TZC_NSEC_TZC_MM_BMX_S1_OFFSET                           (0x30C)

/* 0x310 : tzc_mm_bmx_s2 */
#define TZC_NSEC_TZC_MM_BMX_S2_OFFSET                           (0x310)

/* 0x314 : tzc_mm_bmx_s_lock0 */
#define TZC_NSEC_TZC_MM_BMX_S_LOCK0_OFFSET                      (0x314)

/* 0x318 : tzc_mm_bmx_s_lock1 */
#define TZC_NSEC_TZC_MM_BMX_S_LOCK1_OFFSET                      (0x318)

/* 0x340 : tzc_l2sram_tzsrg_ctrl */
#define TZC_NSEC_TZC_L2SRAM_TZSRG_CTRL_OFFSET                   (0x340)

/* 0x344 : tzc_l2sram_tzsrg_adr_mask */
#define TZC_NSEC_TZC_L2SRAM_TZSRG_ADR_MASK_OFFSET               (0x344)

/* 0x348 : tzc_l2sram_tzsrg_r0 */
#define TZC_NSEC_TZC_L2SRAM_TZSRG_R0_OFFSET                     (0x348)

/* 0x34C : tzc_l2sram_tzsrg_r1 */
#define TZC_NSEC_TZC_L2SRAM_TZSRG_R1_OFFSET                     (0x34C)

/* 0x350 : tzc_l2sram_tzsrg_r2 */
#define TZC_NSEC_TZC_L2SRAM_TZSRG_R2_OFFSET                     (0x350)

/* 0x354 : tzc_l2sram_tzsrg_r3 */
#define TZC_NSEC_TZC_L2SRAM_TZSRG_R3_OFFSET                     (0x354)

/* 0x360 : tzc_vram_tzsrg_ctrl */
#define TZC_NSEC_TZC_VRAM_TZSRG_CTRL_OFFSET                     (0x360)

/* 0x364 : tzc_vram_tzsrg_adr_mask */
#define TZC_NSEC_TZC_VRAM_TZSRG_ADR_MASK_OFFSET                 (0x364)

/* 0x368 : tzc_vram_tzsrg_r0 */
#define TZC_NSEC_TZC_VRAM_TZSRG_R0_OFFSET                       (0x368)

/* 0x36C : tzc_vram_tzsrg_r1 */
#define TZC_NSEC_TZC_VRAM_TZSRG_R1_OFFSET                       (0x36C)

/* 0x370 : tzc_vram_tzsrg_r2 */
#define TZC_NSEC_TZC_VRAM_TZSRG_R2_OFFSET                       (0x370)

/* 0x374 : tzc_vram_tzsrg_r3 */
#define TZC_NSEC_TZC_VRAM_TZSRG_R3_OFFSET                       (0x374)

/* 0x380 : tzc_psrama_tzsrg_ctrl */
#define TZC_NSEC_TZC_PSRAMA_TZSRG_CTRL_OFFSET                   (0x380)

/* 0x384 : tzc_psrama_tzsrg_adr_mask */
#define TZC_NSEC_TZC_PSRAMA_TZSRG_ADR_MASK_OFFSET               (0x384)

/* 0x388 : tzc_psrama_tzsrg_r0 */
#define TZC_NSEC_TZC_PSRAMA_TZSRG_R0_OFFSET                     (0x388)

/* 0x38C : tzc_psrama_tzsrg_r1 */
#define TZC_NSEC_TZC_PSRAMA_TZSRG_R1_OFFSET                     (0x38C)

/* 0x390 : tzc_psrama_tzsrg_r2 */
#define TZC_NSEC_TZC_PSRAMA_TZSRG_R2_OFFSET                     (0x390)

/* 0x394 : tzc_psrama_tzsrg_r3 */
#define TZC_NSEC_TZC_PSRAMA_TZSRG_R3_OFFSET                     (0x394)

/* 0x3A0 : tzc_psramb_tzsrg_ctrl */
#define TZC_NSEC_TZC_PSRAMB_TZSRG_CTRL_OFFSET                   (0x3A0)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_ID_EN                      TZC_NSEC_TZC_PSRAMB_TZSRG_R0_ID_EN
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_ID_EN_POS                  (0U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_ID_EN_LEN                  (4U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_ID_EN_MSK                  (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_ID_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_ID_EN_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_ID_EN_UMSK                 (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_ID_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_ID_EN_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_ID_EN                      TZC_NSEC_TZC_PSRAMB_TZSRG_R1_ID_EN
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_ID_EN_POS                  (4U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_ID_EN_LEN                  (4U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_ID_EN_MSK                  (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_ID_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_ID_EN_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_ID_EN_UMSK                 (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_ID_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_ID_EN_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_ID_EN                      TZC_NSEC_TZC_PSRAMB_TZSRG_R2_ID_EN
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_ID_EN_POS                  (8U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_ID_EN_LEN                  (4U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_ID_EN_MSK                  (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_ID_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_ID_EN_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_ID_EN_UMSK                 (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_ID_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_ID_EN_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_ID_EN                      TZC_NSEC_TZC_PSRAMB_TZSRG_RX_ID_EN
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_ID_EN_POS                  (12U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_ID_EN_LEN                  (4U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_ID_EN_MSK                  (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_RX_ID_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_RX_ID_EN_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_ID_EN_UMSK                 (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_RX_ID_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_RX_ID_EN_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_EN                         TZC_NSEC_TZC_PSRAMB_TZSRG_R0_EN
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_EN_POS                     (16U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_EN_LEN                     (1U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_EN_MSK                     (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_EN_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_EN_UMSK                    (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_EN_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_EN                         TZC_NSEC_TZC_PSRAMB_TZSRG_R1_EN
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_EN_POS                     (17U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_EN_LEN                     (1U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_EN_MSK                     (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_EN_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_EN_UMSK                    (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_EN_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_EN                         TZC_NSEC_TZC_PSRAMB_TZSRG_R2_EN
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_EN_POS                     (18U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_EN_LEN                     (1U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_EN_MSK                     (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_EN_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_EN_UMSK                    (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_EN_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_EN                         TZC_NSEC_TZC_PSRAMB_TZSRG_RX_EN
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_EN_POS                     (19U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_EN_LEN                     (1U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_EN_MSK                     (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_RX_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_RX_EN_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_EN_UMSK                    (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_RX_EN_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_RX_EN_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_LOCK                       TZC_NSEC_TZC_PSRAMB_TZSRG_R0_LOCK
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_LOCK_POS                   (24U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_LOCK_LEN                   (1U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_LOCK_MSK                   (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_LOCK_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_LOCK_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_LOCK_UMSK                  (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_LOCK_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_LOCK_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_LOCK                       TZC_NSEC_TZC_PSRAMB_TZSRG_R1_LOCK
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_LOCK_POS                   (25U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_LOCK_LEN                   (1U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_LOCK_MSK                   (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_LOCK_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_LOCK_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_LOCK_UMSK                  (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_LOCK_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_LOCK_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_LOCK                       TZC_NSEC_TZC_PSRAMB_TZSRG_R2_LOCK
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_LOCK_POS                   (26U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_LOCK_LEN                   (1U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_LOCK_MSK                   (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_LOCK_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_LOCK_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_LOCK_UMSK                  (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_LOCK_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_LOCK_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_LOCK                       TZC_NSEC_TZC_PSRAMB_TZSRG_RX_LOCK
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_LOCK_POS                   (27U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_LOCK_LEN                   (1U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_LOCK_MSK                   (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_RX_LOCK_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_RX_LOCK_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_RX_LOCK_UMSK                  (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_RX_LOCK_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_RX_LOCK_POS))

/* 0x3A4 : tzc_psramb_tzsrg_adr_mask */
#define TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_OFFSET               (0x3A4)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK                      TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK
#define TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_POS                  (0U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_LEN                  (16U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_MSK                  (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_UMSK                 (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_LOCK                 TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_LOCK
#define TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_LOCK_POS             (16U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_LOCK_LEN             (1U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_LOCK_MSK             (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_LOCK_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_LOCK_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_LOCK_UMSK            (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_LOCK_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_ADR_MASK_LOCK_POS))

/* 0x3A8 : tzc_psramb_tzsrg_r0 */
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_OFFSET                     (0x3A8)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_END                        TZC_NSEC_TZC_PSRAMB_TZSRG_R0_END
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_END_POS                    (0U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_END_LEN                    (16U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_END_MSK                    (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_END_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_END_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_END_UMSK                   (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_END_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_END_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_START                      TZC_NSEC_TZC_PSRAMB_TZSRG_R0_START
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_START_POS                  (16U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_START_LEN                  (16U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_START_MSK                  (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_START_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_START_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R0_START_UMSK                 (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_START_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R0_START_POS))

/* 0x3AC : tzc_psramb_tzsrg_r1 */
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_OFFSET                     (0x3AC)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_END                        TZC_NSEC_TZC_PSRAMB_TZSRG_R1_END
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_END_POS                    (0U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_END_LEN                    (16U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_END_MSK                    (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_END_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_END_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_END_UMSK                   (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_END_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_END_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_START                      TZC_NSEC_TZC_PSRAMB_TZSRG_R1_START
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_START_POS                  (16U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_START_LEN                  (16U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_START_MSK                  (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_START_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_START_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R1_START_UMSK                 (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_START_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R1_START_POS))

/* 0x3B0 : tzc_psramb_tzsrg_r2 */
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_OFFSET                     (0x3B0)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_END                        TZC_NSEC_TZC_PSRAMB_TZSRG_R2_END
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_END_POS                    (0U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_END_LEN                    (16U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_END_MSK                    (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_END_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_END_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_END_UMSK                   (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_END_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_END_POS))
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_START                      TZC_NSEC_TZC_PSRAMB_TZSRG_R2_START
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_START_POS                  (16U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_START_LEN                  (16U)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_START_MSK                  (((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_START_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_START_POS)
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R2_START_UMSK                 (~(((1U<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_START_LEN)-1)<<TZC_NSEC_TZC_PSRAMB_TZSRG_R2_START_POS))

/* 0x3B4 : tzc_psramb_tzsrg_r3 */
#define TZC_NSEC_TZC_PSRAMB_TZSRG_R3_OFFSET                     (0x3B4)

/* 0x3c0 : tzc_xram_tzsrg_ctrl */
#define TZC_NSEC_TZC_XRAM_TZSRG_CTRL_OFFSET                     (0x3c0)

/* 0x3C4 : tzc_xram_tzsrg_adr_mask */
#define TZC_NSEC_TZC_XRAM_TZSRG_ADR_MASK_OFFSET                 (0x3C4)

/* 0x3C8 : tzc_xram_tzsrg_r0 */
#define TZC_NSEC_TZC_XRAM_TZSRG_R0_OFFSET                       (0x3C8)

/* 0x3CC : tzc_xram_tzsrg_r1 */
#define TZC_NSEC_TZC_XRAM_TZSRG_R1_OFFSET                       (0x3CC)

/* 0x3D0 : tzc_xram_tzsrg_r2 */
#define TZC_NSEC_TZC_XRAM_TZSRG_R2_OFFSET                       (0x3D0)

/* 0x3D4 : tzc_xram_tzsrg_r3 */
#define TZC_NSEC_TZC_XRAM_TZSRG_R3_OFFSET                       (0x3D4)

/* 0xF00 : tzc_glb_ctrl_0 */
#define TZC_NSEC_TZC_GLB_CTRL_0_OFFSET                          (0xF00)
#define TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_EN                     TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_EN
#define TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_EN_POS                 (0U)
#define TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_EN_LEN                 (2U)
#define TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_EN_MSK                 (((1U<<TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_EN_POS)
#define TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_EN_UMSK                (~(((1U<<TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_EN_POS))
#define TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_EN                     TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_EN
#define TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_EN_POS                 (2U)
#define TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_EN_LEN                 (2U)
#define TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_EN_MSK                 (((1U<<TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_EN_POS)
#define TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_EN_UMSK                (~(((1U<<TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_EN_POS))
#define TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_EN                     TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_EN
#define TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_EN_POS                 (4U)
#define TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_EN_LEN                 (2U)
#define TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_EN_MSK                 (((1U<<TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_EN_POS)
#define TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_EN_UMSK                (~(((1U<<TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_EN_POS))
#define TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_EN                    TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_EN
#define TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_EN_POS                (6U)
#define TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_EN_LEN                (2U)
#define TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_EN_MSK                (((1U<<TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_EN_POS)
#define TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_EN_UMSK               (~(((1U<<TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_EN_POS))
#define TZC_NSEC_TZC_GLB_MISC_TZSID_EN                          TZC_NSEC_TZC_GLB_MISC_TZSID_EN
#define TZC_NSEC_TZC_GLB_MISC_TZSID_EN_POS                      (8U)
#define TZC_NSEC_TZC_GLB_MISC_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_GLB_MISC_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_GLB_MISC_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_MISC_TZSID_EN_POS)
#define TZC_NSEC_TZC_GLB_MISC_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_GLB_MISC_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_MISC_TZSID_EN_POS))
#define TZC_NSEC_TZC_GLB_SRAM_TZSID_EN                          TZC_NSEC_TZC_GLB_SRAM_TZSID_EN
#define TZC_NSEC_TZC_GLB_SRAM_TZSID_EN_POS                      (10U)
#define TZC_NSEC_TZC_GLB_SRAM_TZSID_EN_LEN                      (2U)
#define TZC_NSEC_TZC_GLB_SRAM_TZSID_EN_MSK                      (((1U<<TZC_NSEC_TZC_GLB_SRAM_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_SRAM_TZSID_EN_POS)
#define TZC_NSEC_TZC_GLB_SRAM_TZSID_EN_UMSK                     (~(((1U<<TZC_NSEC_TZC_GLB_SRAM_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_SRAM_TZSID_EN_POS))
#define TZC_NSEC_TZC_GLB_SWRST_TZSID_EN                         TZC_NSEC_TZC_GLB_SWRST_TZSID_EN
#define TZC_NSEC_TZC_GLB_SWRST_TZSID_EN_POS                     (12U)
#define TZC_NSEC_TZC_GLB_SWRST_TZSID_EN_LEN                     (2U)
#define TZC_NSEC_TZC_GLB_SWRST_TZSID_EN_MSK                     (((1U<<TZC_NSEC_TZC_GLB_SWRST_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_SWRST_TZSID_EN_POS)
#define TZC_NSEC_TZC_GLB_SWRST_TZSID_EN_UMSK                    (~(((1U<<TZC_NSEC_TZC_GLB_SWRST_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_SWRST_TZSID_EN_POS))
#define TZC_NSEC_TZC_GLB_BMX_TZSID_EN                           TZC_NSEC_TZC_GLB_BMX_TZSID_EN
#define TZC_NSEC_TZC_GLB_BMX_TZSID_EN_POS                       (14U)
#define TZC_NSEC_TZC_GLB_BMX_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_GLB_BMX_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_GLB_BMX_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_BMX_TZSID_EN_POS)
#define TZC_NSEC_TZC_GLB_BMX_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_GLB_BMX_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_BMX_TZSID_EN_POS))
#define TZC_NSEC_TZC_GLB_DBG_TZSID_EN                           TZC_NSEC_TZC_GLB_DBG_TZSID_EN
#define TZC_NSEC_TZC_GLB_DBG_TZSID_EN_POS                       (16U)
#define TZC_NSEC_TZC_GLB_DBG_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_GLB_DBG_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_GLB_DBG_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_DBG_TZSID_EN_POS)
#define TZC_NSEC_TZC_GLB_DBG_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_GLB_DBG_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_DBG_TZSID_EN_POS))
#define TZC_NSEC_TZC_GLB_MBIST_TZSID_EN                         TZC_NSEC_TZC_GLB_MBIST_TZSID_EN
#define TZC_NSEC_TZC_GLB_MBIST_TZSID_EN_POS                     (18U)
#define TZC_NSEC_TZC_GLB_MBIST_TZSID_EN_LEN                     (2U)
#define TZC_NSEC_TZC_GLB_MBIST_TZSID_EN_MSK                     (((1U<<TZC_NSEC_TZC_GLB_MBIST_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_MBIST_TZSID_EN_POS)
#define TZC_NSEC_TZC_GLB_MBIST_TZSID_EN_UMSK                    (~(((1U<<TZC_NSEC_TZC_GLB_MBIST_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_MBIST_TZSID_EN_POS))
#define TZC_NSEC_TZC_GLB_CLK_TZSID_EN                           TZC_NSEC_TZC_GLB_CLK_TZSID_EN
#define TZC_NSEC_TZC_GLB_CLK_TZSID_EN_POS                       (20U)
#define TZC_NSEC_TZC_GLB_CLK_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_GLB_CLK_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_GLB_CLK_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_CLK_TZSID_EN_POS)
#define TZC_NSEC_TZC_GLB_CLK_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_GLB_CLK_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_CLK_TZSID_EN_POS))
#define TZC_NSEC_TZC_GLB_INT_TZSID_EN                           TZC_NSEC_TZC_GLB_INT_TZSID_EN
#define TZC_NSEC_TZC_GLB_INT_TZSID_EN_POS                       (22U)
#define TZC_NSEC_TZC_GLB_INT_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_GLB_INT_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_GLB_INT_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_INT_TZSID_EN_POS)
#define TZC_NSEC_TZC_GLB_INT_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_GLB_INT_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_INT_TZSID_EN_POS))
#define TZC_NSEC_TZC_GLB_PWR_TZSID_EN                           TZC_NSEC_TZC_GLB_PWR_TZSID_EN
#define TZC_NSEC_TZC_GLB_PWR_TZSID_EN_POS                       (24U)
#define TZC_NSEC_TZC_GLB_PWR_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_GLB_PWR_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_GLB_PWR_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_PWR_TZSID_EN_POS)
#define TZC_NSEC_TZC_GLB_PWR_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_GLB_PWR_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_GLB_PWR_TZSID_EN_POS))

/* 0xF04 : tzc_glb_ctrl_1 */
#define TZC_NSEC_TZC_GLB_CTRL_1_OFFSET                          (0xF04)

/* 0xF08 : tzc_glb_ctrl_2 */
#define TZC_NSEC_TZC_GLB_CTRL_2_OFFSET                          (0xF08)
#define TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_LOCK                   TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_LOCK
#define TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_LOCK_POS               (0U)
#define TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_LOCK_LEN               (1U)
#define TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_LOCK_MSK               (((1U<<TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_LOCK_UMSK              (~(((1U<<TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_PWRON_RST_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_LOCK                   TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_LOCK
#define TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_LOCK_POS               (1U)
#define TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_LOCK_LEN               (1U)
#define TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_LOCK_MSK               (((1U<<TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_LOCK_UMSK              (~(((1U<<TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_CPU_RESET_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_LOCK                   TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_LOCK
#define TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_LOCK_POS               (2U)
#define TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_LOCK_LEN               (1U)
#define TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_LOCK_MSK               (((1U<<TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_LOCK_UMSK              (~(((1U<<TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_SYS_RESET_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_LOCK                  TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_LOCK
#define TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_LOCK_POS              (3U)
#define TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_LOCK_LEN              (1U)
#define TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_LOCK_MSK              (((1U<<TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_LOCK_UMSK             (~(((1U<<TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_CPU2_RESET_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_GLB_MISC_TZSID_LOCK                        TZC_NSEC_TZC_GLB_MISC_TZSID_LOCK
#define TZC_NSEC_TZC_GLB_MISC_TZSID_LOCK_POS                    (4U)
#define TZC_NSEC_TZC_GLB_MISC_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_GLB_MISC_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_GLB_MISC_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_MISC_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_GLB_MISC_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_GLB_MISC_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_MISC_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_GLB_SRAM_TZSID_LOCK                        TZC_NSEC_TZC_GLB_SRAM_TZSID_LOCK
#define TZC_NSEC_TZC_GLB_SRAM_TZSID_LOCK_POS                    (5U)
#define TZC_NSEC_TZC_GLB_SRAM_TZSID_LOCK_LEN                    (1U)
#define TZC_NSEC_TZC_GLB_SRAM_TZSID_LOCK_MSK                    (((1U<<TZC_NSEC_TZC_GLB_SRAM_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_SRAM_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_GLB_SRAM_TZSID_LOCK_UMSK                   (~(((1U<<TZC_NSEC_TZC_GLB_SRAM_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_SRAM_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_GLB_SWRST_TZSID_LOCK                       TZC_NSEC_TZC_GLB_SWRST_TZSID_LOCK
#define TZC_NSEC_TZC_GLB_SWRST_TZSID_LOCK_POS                   (6U)
#define TZC_NSEC_TZC_GLB_SWRST_TZSID_LOCK_LEN                   (1U)
#define TZC_NSEC_TZC_GLB_SWRST_TZSID_LOCK_MSK                   (((1U<<TZC_NSEC_TZC_GLB_SWRST_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_SWRST_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_GLB_SWRST_TZSID_LOCK_UMSK                  (~(((1U<<TZC_NSEC_TZC_GLB_SWRST_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_SWRST_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_GLB_BMX_TZSID_LOCK                         TZC_NSEC_TZC_GLB_BMX_TZSID_LOCK
#define TZC_NSEC_TZC_GLB_BMX_TZSID_LOCK_POS                     (7U)
#define TZC_NSEC_TZC_GLB_BMX_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_GLB_BMX_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_GLB_BMX_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_BMX_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_GLB_BMX_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_GLB_BMX_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_BMX_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_GLB_DBG_TZSID_LOCK                         TZC_NSEC_TZC_GLB_DBG_TZSID_LOCK
#define TZC_NSEC_TZC_GLB_DBG_TZSID_LOCK_POS                     (8U)
#define TZC_NSEC_TZC_GLB_DBG_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_GLB_DBG_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_GLB_DBG_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_DBG_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_GLB_DBG_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_GLB_DBG_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_DBG_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_GLB_MBIST_TZSID_LOCK                       TZC_NSEC_TZC_GLB_MBIST_TZSID_LOCK
#define TZC_NSEC_TZC_GLB_MBIST_TZSID_LOCK_POS                   (9U)
#define TZC_NSEC_TZC_GLB_MBIST_TZSID_LOCK_LEN                   (1U)
#define TZC_NSEC_TZC_GLB_MBIST_TZSID_LOCK_MSK                   (((1U<<TZC_NSEC_TZC_GLB_MBIST_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_MBIST_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_GLB_MBIST_TZSID_LOCK_UMSK                  (~(((1U<<TZC_NSEC_TZC_GLB_MBIST_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_MBIST_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_GLB_CLK_TZSID_LOCK                         TZC_NSEC_TZC_GLB_CLK_TZSID_LOCK
#define TZC_NSEC_TZC_GLB_CLK_TZSID_LOCK_POS                     (10U)
#define TZC_NSEC_TZC_GLB_CLK_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_GLB_CLK_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_GLB_CLK_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_CLK_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_GLB_CLK_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_GLB_CLK_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_CLK_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_GLB_INT_TZSID_LOCK                         TZC_NSEC_TZC_GLB_INT_TZSID_LOCK
#define TZC_NSEC_TZC_GLB_INT_TZSID_LOCK_POS                     (11U)
#define TZC_NSEC_TZC_GLB_INT_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_GLB_INT_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_GLB_INT_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_INT_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_GLB_INT_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_GLB_INT_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_INT_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_GLB_PWR_TZSID_LOCK                         TZC_NSEC_TZC_GLB_PWR_TZSID_LOCK
#define TZC_NSEC_TZC_GLB_PWR_TZSID_LOCK_POS                     (12U)
#define TZC_NSEC_TZC_GLB_PWR_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_GLB_PWR_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_GLB_PWR_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_PWR_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_GLB_PWR_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_GLB_PWR_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_GLB_PWR_TZSID_LOCK_POS))

/* 0xF20 : tzc_mm_ctrl_0 */
#define TZC_NSEC_TZC_MM_CTRL_0_OFFSET                           (0xF20)

/* 0xF24 : tzc_mm_ctrl_1 */
#define TZC_NSEC_TZC_MM_CTRL_1_OFFSET                           (0xF24)

/* 0xF28 : tzc_mm_ctrl_2 */
#define TZC_NSEC_TZC_MM_CTRL_2_OFFSET                           (0xF28)

/* 0xF40 : tzc_se_ctrl_0 */
#define TZC_NSEC_TZC_SE_CTRL_0_OFFSET                           (0xF40)
#define TZC_NSEC_TZC_SE_SHA_TZSID_EN                            TZC_NSEC_TZC_SE_SHA_TZSID_EN
#define TZC_NSEC_TZC_SE_SHA_TZSID_EN_POS                        (0U)
#define TZC_NSEC_TZC_SE_SHA_TZSID_EN_LEN                        (2U)
#define TZC_NSEC_TZC_SE_SHA_TZSID_EN_MSK                        (((1U<<TZC_NSEC_TZC_SE_SHA_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SE_SHA_TZSID_EN_POS)
#define TZC_NSEC_TZC_SE_SHA_TZSID_EN_UMSK                       (~(((1U<<TZC_NSEC_TZC_SE_SHA_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SE_SHA_TZSID_EN_POS))
#define TZC_NSEC_TZC_SE_AES_TZSID_EN                            TZC_NSEC_TZC_SE_AES_TZSID_EN
#define TZC_NSEC_TZC_SE_AES_TZSID_EN_POS                        (2U)
#define TZC_NSEC_TZC_SE_AES_TZSID_EN_LEN                        (2U)
#define TZC_NSEC_TZC_SE_AES_TZSID_EN_MSK                        (((1U<<TZC_NSEC_TZC_SE_AES_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SE_AES_TZSID_EN_POS)
#define TZC_NSEC_TZC_SE_AES_TZSID_EN_UMSK                       (~(((1U<<TZC_NSEC_TZC_SE_AES_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SE_AES_TZSID_EN_POS))
#define TZC_NSEC_TZC_SE_TRNG_TZSID_EN                           TZC_NSEC_TZC_SE_TRNG_TZSID_EN
#define TZC_NSEC_TZC_SE_TRNG_TZSID_EN_POS                       (4U)
#define TZC_NSEC_TZC_SE_TRNG_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_SE_TRNG_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_SE_TRNG_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SE_TRNG_TZSID_EN_POS)
#define TZC_NSEC_TZC_SE_TRNG_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_SE_TRNG_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SE_TRNG_TZSID_EN_POS))
#define TZC_NSEC_TZC_SE_PKA_TZSID_EN                            TZC_NSEC_TZC_SE_PKA_TZSID_EN
#define TZC_NSEC_TZC_SE_PKA_TZSID_EN_POS                        (6U)
#define TZC_NSEC_TZC_SE_PKA_TZSID_EN_LEN                        (2U)
#define TZC_NSEC_TZC_SE_PKA_TZSID_EN_MSK                        (((1U<<TZC_NSEC_TZC_SE_PKA_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SE_PKA_TZSID_EN_POS)
#define TZC_NSEC_TZC_SE_PKA_TZSID_EN_UMSK                       (~(((1U<<TZC_NSEC_TZC_SE_PKA_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SE_PKA_TZSID_EN_POS))
#define TZC_NSEC_TZC_SE_CDET_TZSID_EN                           TZC_NSEC_TZC_SE_CDET_TZSID_EN
#define TZC_NSEC_TZC_SE_CDET_TZSID_EN_POS                       (8U)
#define TZC_NSEC_TZC_SE_CDET_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_SE_CDET_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_SE_CDET_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SE_CDET_TZSID_EN_POS)
#define TZC_NSEC_TZC_SE_CDET_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_SE_CDET_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SE_CDET_TZSID_EN_POS))
#define TZC_NSEC_TZC_SE_GMAC_TZSID_EN                           TZC_NSEC_TZC_SE_GMAC_TZSID_EN
#define TZC_NSEC_TZC_SE_GMAC_TZSID_EN_POS                       (10U)
#define TZC_NSEC_TZC_SE_GMAC_TZSID_EN_LEN                       (2U)
#define TZC_NSEC_TZC_SE_GMAC_TZSID_EN_MSK                       (((1U<<TZC_NSEC_TZC_SE_GMAC_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SE_GMAC_TZSID_EN_POS)
#define TZC_NSEC_TZC_SE_GMAC_TZSID_EN_UMSK                      (~(((1U<<TZC_NSEC_TZC_SE_GMAC_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SE_GMAC_TZSID_EN_POS))
#define TZC_NSEC_TZC_SE_TZSID_CRMD                              TZC_NSEC_TZC_SE_TZSID_CRMD
#define TZC_NSEC_TZC_SE_TZSID_CRMD_POS                          (12U)
#define TZC_NSEC_TZC_SE_TZSID_CRMD_LEN                          (1U)
#define TZC_NSEC_TZC_SE_TZSID_CRMD_MSK                          (((1U<<TZC_NSEC_TZC_SE_TZSID_CRMD_LEN)-1)<<TZC_NSEC_TZC_SE_TZSID_CRMD_POS)
#define TZC_NSEC_TZC_SE_TZSID_CRMD_UMSK                         (~(((1U<<TZC_NSEC_TZC_SE_TZSID_CRMD_LEN)-1)<<TZC_NSEC_TZC_SE_TZSID_CRMD_POS))
#define TZC_NSEC_TZC_SE_WDT_DLY                                 TZC_NSEC_TZC_SE_WDT_DLY
#define TZC_NSEC_TZC_SE_WDT_DLY_POS                             (16U)
#define TZC_NSEC_TZC_SE_WDT_DLY_LEN                             (16U)
#define TZC_NSEC_TZC_SE_WDT_DLY_MSK                             (((1U<<TZC_NSEC_TZC_SE_WDT_DLY_LEN)-1)<<TZC_NSEC_TZC_SE_WDT_DLY_POS)
#define TZC_NSEC_TZC_SE_WDT_DLY_UMSK                            (~(((1U<<TZC_NSEC_TZC_SE_WDT_DLY_LEN)-1)<<TZC_NSEC_TZC_SE_WDT_DLY_POS))

/* 0xF44 : tzc_se_ctrl_1 */
#define TZC_NSEC_TZC_SE_CTRL_1_OFFSET                           (0xF44)
#define TZC_NSEC_TZC_SF_CR_TZSID_EN                             TZC_NSEC_TZC_SF_CR_TZSID_EN
#define TZC_NSEC_TZC_SF_CR_TZSID_EN_POS                         (0U)
#define TZC_NSEC_TZC_SF_CR_TZSID_EN_LEN                         (2U)
#define TZC_NSEC_TZC_SF_CR_TZSID_EN_MSK                         (((1U<<TZC_NSEC_TZC_SF_CR_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_CR_TZSID_EN_POS)
#define TZC_NSEC_TZC_SF_CR_TZSID_EN_UMSK                        (~(((1U<<TZC_NSEC_TZC_SF_CR_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_CR_TZSID_EN_POS))
#define TZC_NSEC_TZC_SF_SEC_TZSID_EN                            TZC_NSEC_TZC_SF_SEC_TZSID_EN
#define TZC_NSEC_TZC_SF_SEC_TZSID_EN_POS                        (2U)
#define TZC_NSEC_TZC_SF_SEC_TZSID_EN_LEN                        (2U)
#define TZC_NSEC_TZC_SF_SEC_TZSID_EN_MSK                        (((1U<<TZC_NSEC_TZC_SF_SEC_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_SEC_TZSID_EN_POS)
#define TZC_NSEC_TZC_SF_SEC_TZSID_EN_UMSK                       (~(((1U<<TZC_NSEC_TZC_SF_SEC_TZSID_EN_LEN)-1)<<TZC_NSEC_TZC_SF_SEC_TZSID_EN_POS))
#define TZC_NSEC_TZC_SF_TZSID_CRMD                              TZC_NSEC_TZC_SF_TZSID_CRMD
#define TZC_NSEC_TZC_SF_TZSID_CRMD_POS                          (4U)
#define TZC_NSEC_TZC_SF_TZSID_CRMD_LEN                          (1U)
#define TZC_NSEC_TZC_SF_TZSID_CRMD_MSK                          (((1U<<TZC_NSEC_TZC_SF_TZSID_CRMD_LEN)-1)<<TZC_NSEC_TZC_SF_TZSID_CRMD_POS)
#define TZC_NSEC_TZC_SF_TZSID_CRMD_UMSK                         (~(((1U<<TZC_NSEC_TZC_SF_TZSID_CRMD_LEN)-1)<<TZC_NSEC_TZC_SF_TZSID_CRMD_POS))

/* 0xF48 : tzc_se_ctrl_2 */
#define TZC_NSEC_TZC_SE_CTRL_2_OFFSET                           (0xF48)
#define TZC_NSEC_TZC_SE_SHA_TZSID_LOCK                          TZC_NSEC_TZC_SE_SHA_TZSID_LOCK
#define TZC_NSEC_TZC_SE_SHA_TZSID_LOCK_POS                      (0U)
#define TZC_NSEC_TZC_SE_SHA_TZSID_LOCK_LEN                      (1U)
#define TZC_NSEC_TZC_SE_SHA_TZSID_LOCK_MSK                      (((1U<<TZC_NSEC_TZC_SE_SHA_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_SHA_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_SE_SHA_TZSID_LOCK_UMSK                     (~(((1U<<TZC_NSEC_TZC_SE_SHA_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_SHA_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_SE_AES_TZSID_LOCK                          TZC_NSEC_TZC_SE_AES_TZSID_LOCK
#define TZC_NSEC_TZC_SE_AES_TZSID_LOCK_POS                      (1U)
#define TZC_NSEC_TZC_SE_AES_TZSID_LOCK_LEN                      (1U)
#define TZC_NSEC_TZC_SE_AES_TZSID_LOCK_MSK                      (((1U<<TZC_NSEC_TZC_SE_AES_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_AES_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_SE_AES_TZSID_LOCK_UMSK                     (~(((1U<<TZC_NSEC_TZC_SE_AES_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_AES_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_SE_TRNG_TZSID_LOCK                         TZC_NSEC_TZC_SE_TRNG_TZSID_LOCK
#define TZC_NSEC_TZC_SE_TRNG_TZSID_LOCK_POS                     (2U)
#define TZC_NSEC_TZC_SE_TRNG_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_SE_TRNG_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_SE_TRNG_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_TRNG_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_SE_TRNG_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_SE_TRNG_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_TRNG_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_SE_PKA_TZSID_LOCK                          TZC_NSEC_TZC_SE_PKA_TZSID_LOCK
#define TZC_NSEC_TZC_SE_PKA_TZSID_LOCK_POS                      (3U)
#define TZC_NSEC_TZC_SE_PKA_TZSID_LOCK_LEN                      (1U)
#define TZC_NSEC_TZC_SE_PKA_TZSID_LOCK_MSK                      (((1U<<TZC_NSEC_TZC_SE_PKA_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_PKA_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_SE_PKA_TZSID_LOCK_UMSK                     (~(((1U<<TZC_NSEC_TZC_SE_PKA_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_PKA_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_SE_CDET_TZSID_LOCK                         TZC_NSEC_TZC_SE_CDET_TZSID_LOCK
#define TZC_NSEC_TZC_SE_CDET_TZSID_LOCK_POS                     (4U)
#define TZC_NSEC_TZC_SE_CDET_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_SE_CDET_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_SE_CDET_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_CDET_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_SE_CDET_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_SE_CDET_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_CDET_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_SE_GMAC_TZSID_LOCK                         TZC_NSEC_TZC_SE_GMAC_TZSID_LOCK
#define TZC_NSEC_TZC_SE_GMAC_TZSID_LOCK_POS                     (5U)
#define TZC_NSEC_TZC_SE_GMAC_TZSID_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_SE_GMAC_TZSID_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_SE_GMAC_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_GMAC_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_SE_GMAC_TZSID_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_SE_GMAC_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_GMAC_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_SE_TZSID_CRMD_LOCK                         TZC_NSEC_TZC_SE_TZSID_CRMD_LOCK
#define TZC_NSEC_TZC_SE_TZSID_CRMD_LOCK_POS                     (6U)
#define TZC_NSEC_TZC_SE_TZSID_CRMD_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_SE_TZSID_CRMD_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_SE_TZSID_CRMD_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_TZSID_CRMD_LOCK_POS)
#define TZC_NSEC_TZC_SE_TZSID_CRMD_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_SE_TZSID_CRMD_LOCK_LEN)-1)<<TZC_NSEC_TZC_SE_TZSID_CRMD_LOCK_POS))
#define TZC_NSEC_TZC_SF_CR_TZSID_LOCK                           TZC_NSEC_TZC_SF_CR_TZSID_LOCK
#define TZC_NSEC_TZC_SF_CR_TZSID_LOCK_POS                       (16U)
#define TZC_NSEC_TZC_SF_CR_TZSID_LOCK_LEN                       (1U)
#define TZC_NSEC_TZC_SF_CR_TZSID_LOCK_MSK                       (((1U<<TZC_NSEC_TZC_SF_CR_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_CR_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_SF_CR_TZSID_LOCK_UMSK                      (~(((1U<<TZC_NSEC_TZC_SF_CR_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_CR_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_SF_SEC_TZSID_LOCK                          TZC_NSEC_TZC_SF_SEC_TZSID_LOCK
#define TZC_NSEC_TZC_SF_SEC_TZSID_LOCK_POS                      (17U)
#define TZC_NSEC_TZC_SF_SEC_TZSID_LOCK_LEN                      (1U)
#define TZC_NSEC_TZC_SF_SEC_TZSID_LOCK_MSK                      (((1U<<TZC_NSEC_TZC_SF_SEC_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_SEC_TZSID_LOCK_POS)
#define TZC_NSEC_TZC_SF_SEC_TZSID_LOCK_UMSK                     (~(((1U<<TZC_NSEC_TZC_SF_SEC_TZSID_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_SEC_TZSID_LOCK_POS))
#define TZC_NSEC_TZC_SF_TZSID_CRMD_LOCK                         TZC_NSEC_TZC_SF_TZSID_CRMD_LOCK
#define TZC_NSEC_TZC_SF_TZSID_CRMD_LOCK_POS                     (18U)
#define TZC_NSEC_TZC_SF_TZSID_CRMD_LOCK_LEN                     (1U)
#define TZC_NSEC_TZC_SF_TZSID_CRMD_LOCK_MSK                     (((1U<<TZC_NSEC_TZC_SF_TZSID_CRMD_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSID_CRMD_LOCK_POS)
#define TZC_NSEC_TZC_SF_TZSID_CRMD_LOCK_UMSK                    (~(((1U<<TZC_NSEC_TZC_SF_TZSID_CRMD_LOCK_LEN)-1)<<TZC_NSEC_TZC_SF_TZSID_CRMD_LOCK_POS))


struct  tzc_nsec_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[64];

    /* 0x40 : tzc_rom_tzsrg_ctrl */
    union {
        struct {
            uint32_t tzc_rom_tzsrg_r0_id_en         :  4; /* [ 3: 0],          r,        0xf */
            uint32_t tzc_rom_tzsrg_r1_id_en         :  4; /* [ 7: 4],          r,        0xf */
            uint32_t tzc_rom_tzsrg_r2_id_en         :  4; /* [11: 8],          r,        0xf */
            uint32_t tzc_rom_tzsrg_rx_id_en         :  4; /* [15:12],          r,        0xf */
            uint32_t tzc_rom_tzsrg_r0_en            :  1; /* [   16],          r,        0x0 */
            uint32_t tzc_rom_tzsrg_r1_en            :  1; /* [   17],          r,        0x0 */
            uint32_t tzc_rom_tzsrg_r2_en            :  1; /* [   18],          r,        0x0 */
            uint32_t tzc_rom_tzsrg_rx_en            :  1; /* [   19],          r,        0x0 */
            uint32_t reserved_20_21                 :  2; /* [21:20],       rsvd,        0x0 */
            uint32_t tzc_bus_rmp_en                 :  1; /* [   22],          r,        0x0 */
            uint32_t tzc_bus_rmp_en_lock            :  1; /* [   23],          r,        0x0 */
            uint32_t tzc_rom_tzsrg_r0_lock          :  1; /* [   24],          r,        0x0 */
            uint32_t tzc_rom_tzsrg_r1_lock          :  1; /* [   25],          r,        0x0 */
            uint32_t tzc_rom_tzsrg_r2_lock          :  1; /* [   26],          r,        0x0 */
            uint32_t tzc_rom_tzsrg_rx_lock          :  1; /* [   27],          r,        0x0 */
            uint32_t tzc_sboot_done                 :  4; /* [31:28],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_rom_tzsrg_ctrl;

    /* 0x44 : tzc_rom_tzsrg_adr_mask */
    union {
        struct {
            uint32_t tzc_rom_tzsrg_adr_mask         : 10; /* [ 9: 0],          r,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t tzc_rom_tzsrg_adr_mask_lock    :  1; /* [   16],          r,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_rom_tzsrg_adr_mask;

    /* 0x48 : tzc_rom_tzsrg_r0 */
    union {
        struct {
            uint32_t tzc_rom_tzsrg_r0_end           : 10; /* [ 9: 0],          r,      0x3ff */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t tzc_rom_tzsrg_r0_start         : 10; /* [25:16],          r,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_rom_tzsrg_r0;

    /* 0x4C : tzc_rom_tzsrg_r1 */
    union {
        struct {
            uint32_t tzc_rom_tzsrg_r1_end           : 10; /* [ 9: 0],          r,      0x3ff */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t tzc_rom_tzsrg_r1_start         : 10; /* [25:16],          r,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_rom_tzsrg_r1;

    /* 0x50 : tzc_rom_tzsrg_r2 */
    union {
        struct {
            uint32_t tzc_rom_tzsrg_r2_end           : 10; /* [ 9: 0],          r,      0x3ff */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t tzc_rom_tzsrg_r2_start         : 10; /* [25:16],          r,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_rom_tzsrg_r2;

    /* 0x54 : tzc_rom_tzsrg_r3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_rom_tzsrg_r3;

    /* 0x58  reserved */
    uint8_t RESERVED0x58[168];

    /* 0x100 : tzc_bmx_tzmid */
    union {
        struct {
            uint32_t reserved_0_1                   :  2; /* [ 1: 0],       rsvd,        0x0 */
            uint32_t tzc_usb_tzmid                  :  1; /* [    2],          r,        0x0 */
            uint32_t tzc_wifi_tzmid                 :  1; /* [    3],          r,        0x0 */
            uint32_t tzc_cci_tzmid                  :  1; /* [    4],          r,        0x0 */
            uint32_t tzc_sdhm_tzmid                 :  1; /* [    5],          r,        0x0 */
            uint32_t tzc_emacA_tzmid                :  1; /* [    6],          r,        0x0 */
            uint32_t tzc_cpu_tzmid                  :  1; /* [    7],          r,        0x0 */
            uint32_t tzc_dma_tzmid                  :  1; /* [    8],          r,        0x0 */
            uint32_t reserved_9_10                  :  2; /* [10: 9],       rsvd,        0x0 */
            uint32_t tzc_sdum_tzmid                 :  1; /* [   11],          r,        0x0 */
            uint32_t reserved_12_17                 :  6; /* [17:12],       rsvd,        0x0 */
            uint32_t tzc_usb_tzmid_sel              :  1; /* [   18],          r,        0x1 */
            uint32_t tzc_wifi_tzmid_sel             :  1; /* [   19],          r,        0x1 */
            uint32_t tzc_cci_tzmid_sel              :  1; /* [   20],          r,        0x1 */
            uint32_t tzc_sdhm_tzmid_sel             :  1; /* [   21],          r,        0x1 */
            uint32_t tzc_emacA_tzmid_sel            :  1; /* [   22],          r,        0x1 */
            uint32_t tzc_cpu_tzmid_sel              :  1; /* [   23],          r,        0x1 */
            uint32_t tzc_dma_tzmid_sel              :  1; /* [   24],          r,        0x1 */
            uint32_t reserved_25_26                 :  2; /* [26:25],       rsvd,        0x0 */
            uint32_t tzc_sdum_tzmid_sel             :  1; /* [   27],          r,        0x1 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_bmx_tzmid;

    /* 0x104 : tzc_bmx_tzmid_lock */
    union {
        struct {
            uint32_t reserved_0_1                   :  2; /* [ 1: 0],       rsvd,        0x0 */
            uint32_t tzc_usb_tzmid_lock             :  1; /* [    2],          r,        0x0 */
            uint32_t tzc_wifi_tzmid_lock            :  1; /* [    3],          r,        0x0 */
            uint32_t tzc_cci_tzmid_lock             :  1; /* [    4],          r,        0x0 */
            uint32_t tzc_sdhm_tzmid_lock            :  1; /* [    5],          r,        0x0 */
            uint32_t tzc_emacA_tzmid_lock           :  1; /* [    6],          r,        0x0 */
            uint32_t tzc_cpu_tzmid_lock             :  1; /* [    7],          r,        0x0 */
            uint32_t tzc_dma_tzmid_lock             :  1; /* [    8],          r,        0x0 */
            uint32_t reserved_9_10                  :  2; /* [10: 9],       rsvd,        0x0 */
            uint32_t tzc_sdum_tzmid_lock            :  1; /* [   11],          r,        0x0 */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_bmx_tzmid_lock;

    /* 0x108 : tzc_bmx_s0 */
    union {
        struct {
            uint32_t reserved_0_1                   :  2; /* [ 1: 0],       rsvd,        0x0 */
            uint32_t tzc_bmx_dma_tzsid_en           :  2; /* [ 3: 2],          r,        0x3 */
            uint32_t reserved_4_5                   :  2; /* [ 5: 4],       rsvd,        0x0 */
            uint32_t tzc_bmx_pwr_tzsid_en           :  2; /* [ 7: 6],          r,        0x3 */
            uint32_t tzc_bmx_sdh_tzsid_en           :  2; /* [ 9: 8],          r,        0x3 */
            uint32_t tzc_bmx_emac_tzsid_en          :  2; /* [11:10],          r,        0x3 */
            uint32_t tzc_bmx_sdu_tzsid_en           :  2; /* [13:12],          r,        0x3 */
            uint32_t reserved_14_16                 :  3; /* [16:14],       rsvd,        0x0 */
            uint32_t tzc_bmx_dma_tzsid_lock         :  1; /* [   17],          r,        0x0 */
            uint32_t reserved_18                    :  1; /* [   18],       rsvd,        0x0 */
            uint32_t tzc_bmx_pwr_tzsid_lock         :  1; /* [   19],          r,        0x0 */
            uint32_t tzc_bmx_sdh_tzsid_lock         :  1; /* [   20],          r,        0x0 */
            uint32_t tzc_bmx_emac_tzsid_lock        :  1; /* [   21],          r,        0x0 */
            uint32_t tzc_bmx_sdu_tzsid_lock         :  1; /* [   22],          r,        0x0 */
            uint32_t reserved_23_31                 :  9; /* [31:23],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_bmx_s0;

    /* 0x10C : tzc_bmx_s1 */
    union {
        struct {
            uint32_t tzc_bmx_s10_tzsid_en           :  2; /* [ 1: 0],          r,        0x3 */
            uint32_t tzc_bmx_s11_tzsid_en           :  2; /* [ 3: 2],          r,        0x3 */
            uint32_t tzc_bmx_s12_tzsid_en           :  2; /* [ 5: 4],          r,        0x3 */
            uint32_t tzc_bmx_s13_tzsid_en           :  2; /* [ 7: 6],          r,        0x3 */
            uint32_t tzc_bmx_s14_tzsid_en           :  2; /* [ 9: 8],          r,        0x3 */
            uint32_t tzc_bmx_s15_tzsid_en           :  2; /* [11:10],          r,        0x3 */
            uint32_t tzc_bmx_s16_tzsid_en           :  2; /* [13:12],          r,        0x3 */
            uint32_t tzc_bmx_s17_tzsid_en           :  2; /* [15:14],          r,        0x3 */
            uint32_t tzc_bmx_s18_tzsid_en           :  2; /* [17:16],          r,        0x3 */
            uint32_t tzc_bmx_s19_tzsid_en           :  2; /* [19:18],          r,        0x3 */
            uint32_t tzc_bmx_s1a_tzsid_en           :  2; /* [21:20],          r,        0x3 */
            uint32_t tzc_bmx_s1b_tzsid_en           :  2; /* [23:22],          r,        0x3 */
            uint32_t tzc_bmx_s1c_tzsid_en           :  2; /* [25:24],          r,        0x3 */
            uint32_t tzc_bmx_s1d_tzsid_en           :  2; /* [27:26],          r,        0x3 */
            uint32_t tzc_bmx_s1e_tzsid_en           :  2; /* [29:28],          r,        0x3 */
            uint32_t tzc_bmx_s1f_tzsid_en           :  2; /* [31:30],          r,        0x3 */
        }BF;
        uint32_t WORD;
    } tzc_bmx_s1;

    /* 0x110 : tzc_bmx_s2 */
    union {
        struct {
            uint32_t tzc_bmx_s20_tzsid_en           :  2; /* [ 1: 0],          r,        0x3 */
            uint32_t tzc_bmx_s21_tzsid_en           :  2; /* [ 3: 2],          r,        0x3 */
            uint32_t tzc_bmx_s22_tzsid_en           :  2; /* [ 5: 4],          r,        0x3 */
            uint32_t tzc_bmx_s23_tzsid_en           :  2; /* [ 7: 6],          r,        0x3 */
            uint32_t tzc_bmx_s24_tzsid_en           :  2; /* [ 9: 8],          r,        0x3 */
            uint32_t tzc_bmx_s25_tzsid_en           :  2; /* [11:10],          r,        0x3 */
            uint32_t tzc_bmx_s26_tzsid_en           :  2; /* [13:12],          r,        0x3 */
            uint32_t tzc_bmx_s27_tzsid_en           :  2; /* [15:14],          r,        0x3 */
            uint32_t tzc_bmx_s28_tzsid_en           :  2; /* [17:16],          r,        0x3 */
            uint32_t tzc_bmx_s29_tzsid_en           :  2; /* [19:18],          r,        0x3 */
            uint32_t tzc_bmx_s2a_tzsid_en           :  2; /* [21:20],          r,        0x3 */
            uint32_t tzc_bmx_s2b_tzsid_en           :  2; /* [23:22],          r,        0x3 */
            uint32_t tzc_bmx_s2c_tzsid_en           :  2; /* [25:24],          r,        0x3 */
            uint32_t tzc_bmx_s2d_tzsid_en           :  2; /* [27:26],          r,        0x3 */
            uint32_t tzc_bmx_s2e_tzsid_en           :  2; /* [29:28],          r,        0x3 */
            uint32_t tzc_bmx_s2f_tzsid_en           :  2; /* [31:30],          r,        0x3 */
        }BF;
        uint32_t WORD;
    } tzc_bmx_s2;

    /* 0x114 : tzc_bmx_s_lock */
    union {
        struct {
            uint32_t tzc_bmx_s10_tzsid_lock         :  1; /* [    0],          r,        0x0 */
            uint32_t tzc_bmx_s11_tzsid_lock         :  1; /* [    1],          r,        0x0 */
            uint32_t tzc_bmx_s12_tzsid_lock         :  1; /* [    2],          r,        0x0 */
            uint32_t tzc_bmx_s13_tzsid_lock         :  1; /* [    3],          r,        0x0 */
            uint32_t tzc_bmx_s14_tzsid_lock         :  1; /* [    4],          r,        0x0 */
            uint32_t tzc_bmx_s15_tzsid_lock         :  1; /* [    5],          r,        0x0 */
            uint32_t tzc_bmx_s16_tzsid_lock         :  1; /* [    6],          r,        0x0 */
            uint32_t tzc_bmx_s17_tzsid_lock         :  1; /* [    7],          r,        0x0 */
            uint32_t tzc_bmx_s18_tzsid_lock         :  1; /* [    8],          r,        0x0 */
            uint32_t tzc_bmx_s19_tzsid_lock         :  1; /* [    9],          r,        0x0 */
            uint32_t tzc_bmx_s1a_tzsid_lock         :  1; /* [   10],          r,        0x0 */
            uint32_t tzc_bmx_s1b_tzsid_lock         :  1; /* [   11],          r,        0x0 */
            uint32_t tzc_bmx_s1c_tzsid_lock         :  1; /* [   12],          r,        0x0 */
            uint32_t tzc_bmx_s1d_tzsid_lock         :  1; /* [   13],          r,        0x0 */
            uint32_t tzc_bmx_s1e_tzsid_lock         :  1; /* [   14],          r,        0x0 */
            uint32_t tzc_bmx_s1f_tzsid_lock         :  1; /* [   15],          r,        0x0 */
            uint32_t tzc_bmx_s20_tzsid_lock         :  1; /* [   16],          r,        0x0 */
            uint32_t tzc_bmx_s21_tzsid_lock         :  1; /* [   17],          r,        0x0 */
            uint32_t tzc_bmx_s22_tzsid_lock         :  1; /* [   18],          r,        0x0 */
            uint32_t tzc_bmx_s23_tzsid_lock         :  1; /* [   19],          r,        0x0 */
            uint32_t tzc_bmx_s24_tzsid_lock         :  1; /* [   20],          r,        0x0 */
            uint32_t tzc_bmx_s25_tzsid_lock         :  1; /* [   21],          r,        0x0 */
            uint32_t tzc_bmx_s26_tzsid_lock         :  1; /* [   22],          r,        0x0 */
            uint32_t tzc_bmx_s27_tzsid_lock         :  1; /* [   23],          r,        0x0 */
            uint32_t tzc_bmx_s28_tzsid_lock         :  1; /* [   24],          r,        0x0 */
            uint32_t tzc_bmx_s29_tzsid_lock         :  1; /* [   25],          r,        0x0 */
            uint32_t tzc_bmx_s2a_tzsid_lock         :  1; /* [   26],          r,        0x0 */
            uint32_t tzc_bmx_s2b_tzsid_lock         :  1; /* [   27],          r,        0x0 */
            uint32_t tzc_bmx_s2c_tzsid_lock         :  1; /* [   28],          r,        0x0 */
            uint32_t tzc_bmx_s2d_tzsid_lock         :  1; /* [   29],          r,        0x0 */
            uint32_t tzc_bmx_s2e_tzsid_lock         :  1; /* [   30],          r,        0x0 */
            uint32_t tzc_bmx_s2f_tzsid_lock         :  1; /* [   31],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_bmx_s_lock;

    /* 0x118 : tzc_bmx_s1a */
    union {
        struct {
            uint32_t tzc_bmx_s1a0_tzsid_en          :  2; /* [ 1: 0],          r,        0x3 */
            uint32_t tzc_bmx_s1a1_tzsid_en          :  2; /* [ 3: 2],          r,        0x3 */
            uint32_t tzc_bmx_s1a2_tzsid_en          :  2; /* [ 5: 4],          r,        0x3 */
            uint32_t tzc_bmx_s1a3_tzsid_en          :  2; /* [ 7: 6],          r,        0x3 */
            uint32_t tzc_bmx_s1a4_tzsid_en          :  2; /* [ 9: 8],          r,        0x3 */
            uint32_t tzc_bmx_s1a5_tzsid_en          :  2; /* [11:10],          r,        0x3 */
            uint32_t tzc_bmx_s1a6_tzsid_en          :  2; /* [13:12],          r,        0x3 */
            uint32_t tzc_bmx_s1a7_tzsid_en          :  2; /* [15:14],          r,        0x3 */
            uint32_t tzc_bmx_s1a8_tzsid_en          :  2; /* [17:16],          r,        0x3 */
            uint32_t tzc_bmx_s1a9_tzsid_en          :  2; /* [19:18],          r,        0x3 */
            uint32_t tzc_bmx_s1aa_tzsid_en          :  2; /* [21:20],          r,        0x3 */
            uint32_t tzc_bmx_s1ab_tzsid_en          :  2; /* [23:22],          r,        0x3 */
            uint32_t tzc_bmx_s1ac_tzsid_en          :  2; /* [25:24],          r,        0x3 */
            uint32_t tzc_bmx_s1ad_tzsid_en          :  2; /* [27:26],          r,        0x3 */
            uint32_t tzc_bmx_s1ae_tzsid_en          :  2; /* [29:28],          r,        0x3 */
            uint32_t tzc_bmx_s1af_tzsid_en          :  2; /* [31:30],          r,        0x3 */
        }BF;
        uint32_t WORD;
    } tzc_bmx_s1a;

    /* 0x11C : tzc_bmx_s1a_lock */
    union {
        struct {
            uint32_t tzc_bmx_s1a0_tzsid_lock        :  1; /* [    0],          r,        0x0 */
            uint32_t tzc_bmx_s1a1_tzsid_lock        :  1; /* [    1],          r,        0x0 */
            uint32_t tzc_bmx_s1a2_tzsid_lock        :  1; /* [    2],          r,        0x0 */
            uint32_t tzc_bmx_s1a3_tzsid_lock        :  1; /* [    3],          r,        0x0 */
            uint32_t tzc_bmx_s1a4_tzsid_lock        :  1; /* [    4],          r,        0x0 */
            uint32_t tzc_bmx_s1a5_tzsid_lock        :  1; /* [    5],          r,        0x0 */
            uint32_t tzc_bmx_s1a6_tzsid_lock        :  1; /* [    6],          r,        0x0 */
            uint32_t tzc_bmx_s1a7_tzsid_lock        :  1; /* [    7],          r,        0x0 */
            uint32_t tzc_bmx_s1a8_tzsid_lock        :  1; /* [    8],          r,        0x0 */
            uint32_t tzc_bmx_s1a9_tzsid_lock        :  1; /* [    9],          r,        0x0 */
            uint32_t tzc_bmx_s1aa_tzsid_lock        :  1; /* [   10],          r,        0x0 */
            uint32_t tzc_bmx_s1ab_tzsid_lock        :  1; /* [   11],          r,        0x0 */
            uint32_t tzc_bmx_s1ac_tzsid_lock        :  1; /* [   12],          r,        0x0 */
            uint32_t tzc_bmx_s1ad_tzsid_lock        :  1; /* [   13],          r,        0x0 */
            uint32_t tzc_bmx_s1ae_tzsid_lock        :  1; /* [   14],          r,        0x0 */
            uint32_t tzc_bmx_s1af_tzsid_lock        :  1; /* [   15],          r,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_bmx_s1a_lock;

    /* 0x120  reserved */
    uint8_t RESERVED0x120[32];

    /* 0x140 : tzc_ocram_tzsrg_ctrl */
    union {
        struct {
            uint32_t tzc_ocram_tzsrg_r0_id_en       :  4; /* [ 3: 0],          r,        0xf */
            uint32_t tzc_ocram_tzsrg_r1_id_en       :  4; /* [ 7: 4],          r,        0xf */
            uint32_t tzc_ocram_tzsrg_r2_id_en       :  4; /* [11: 8],          r,        0xf */
            uint32_t tzc_ocram_tzsrg_rx_id_en       :  4; /* [15:12],          r,        0xf */
            uint32_t tzc_ocram_tzsrg_r0_en          :  1; /* [   16],          r,        0x0 */
            uint32_t tzc_ocram_tzsrg_r1_en          :  1; /* [   17],          r,        0x0 */
            uint32_t tzc_ocram_tzsrg_r2_en          :  1; /* [   18],          r,        0x0 */
            uint32_t tzc_ocram_tzsrg_rx_en          :  1; /* [   19],          r,        0x0 */
            uint32_t tzc_ocram_tzsrg_r0_lock        :  1; /* [   20],          r,        0x0 */
            uint32_t tzc_ocram_tzsrg_r1_lock        :  1; /* [   21],          r,        0x0 */
            uint32_t tzc_ocram_tzsrg_r2_lock        :  1; /* [   22],          r,        0x0 */
            uint32_t tzc_ocram_tzsrg_rx_lock        :  1; /* [   23],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_ocram_tzsrg_ctrl;

    /* 0x144 : tzc_ocram_tzsrg_adr_mask */
    union {
        struct {
            uint32_t tzc_ocram_tzsrg_adr_mask       : 10; /* [ 9: 0],          r,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t tzc_ocram_tzsrg_adr_mask_lock  :  1; /* [   16],          r,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_ocram_tzsrg_adr_mask;

    /* 0x148 : tzc_ocram_tzsrg_r0 */
    union {
        struct {
            uint32_t tzc_ocram_tzsrg_r0_end         : 10; /* [ 9: 0],          r,      0x3ff */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t tzc_ocram_tzsrg_r0_start       : 10; /* [25:16],          r,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_ocram_tzsrg_r0;

    /* 0x14C : tzc_ocram_tzsrg_r1 */
    union {
        struct {
            uint32_t tzc_ocram_tzsrg_r1_end         : 10; /* [ 9: 0],          r,      0x3ff */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t tzc_ocram_tzsrg_r1_start       : 10; /* [25:16],          r,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_ocram_tzsrg_r1;

    /* 0x150 : tzc_ocram_tzsrg_r2 */
    union {
        struct {
            uint32_t tzc_ocram_tzsrg_r2_end         : 10; /* [ 9: 0],          r,      0x3ff */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t tzc_ocram_tzsrg_r2_start       : 10; /* [25:16],          r,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_ocram_tzsrg_r2;

    /* 0x154 : tzc_ocram_tzsrg_r3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_ocram_tzsrg_r3;

    /* 0x158  reserved */
    uint8_t RESERVED0x158[40];

    /* 0x180 : tzc_wram_tzsrg_ctrl */
    union {
        struct {
            uint32_t tzc_wram_tzsrg_r0_id_en        :  4; /* [ 3: 0],          r,        0xf */
            uint32_t tzc_wram_tzsrg_r1_id_en        :  4; /* [ 7: 4],          r,        0xf */
            uint32_t tzc_wram_tzsrg_r2_id_en        :  4; /* [11: 8],          r,        0xf */
            uint32_t tzc_wram_tzsrg_rx_id_en        :  4; /* [15:12],          r,        0xf */
            uint32_t tzc_wram_tzsrg_r0_en           :  1; /* [   16],          r,        0x0 */
            uint32_t tzc_wram_tzsrg_r1_en           :  1; /* [   17],          r,        0x0 */
            uint32_t tzc_wram_tzsrg_r2_en           :  1; /* [   18],          r,        0x0 */
            uint32_t tzc_wram_tzsrg_rx_en           :  1; /* [   19],          r,        0x0 */
            uint32_t tzc_wram_tzsrg_r0_lock         :  1; /* [   20],          r,        0x0 */
            uint32_t tzc_wram_tzsrg_r1_lock         :  1; /* [   21],          r,        0x0 */
            uint32_t tzc_wram_tzsrg_r2_lock         :  1; /* [   22],          r,        0x0 */
            uint32_t tzc_wram_tzsrg_rx_lock         :  1; /* [   23],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_wram_tzsrg_ctrl;

    /* 0x184 : tzc_wram_tzsrg_adr_mask */
    union {
        struct {
            uint32_t tzc_wram_tzsrg_adr_mask        : 10; /* [ 9: 0],          r,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t tzc_wram_tzsrg_adr_mask_lock   :  1; /* [   16],          r,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_wram_tzsrg_adr_mask;

    /* 0x188 : tzc_wram_tzsrg_r0 */
    union {
        struct {
            uint32_t tzc_wram_tzsrg_r0_end          : 10; /* [ 9: 0],          r,      0x3ff */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t tzc_wram_tzsrg_r0_start        : 10; /* [25:16],          r,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_wram_tzsrg_r0;

    /* 0x18C : tzc_wram_tzsrg_r1 */
    union {
        struct {
            uint32_t tzc_wram_tzsrg_r1_end          : 10; /* [ 9: 0],          r,      0x3ff */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t tzc_wram_tzsrg_r1_start        : 10; /* [25:16],          r,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_wram_tzsrg_r1;

    /* 0x190 : tzc_wram_tzsrg_r2 */
    union {
        struct {
            uint32_t tzc_wram_tzsrg_r2_end          : 10; /* [ 9: 0],          r,      0x3ff */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t tzc_wram_tzsrg_r2_start        : 10; /* [25:16],          r,        0x0 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_wram_tzsrg_r2;

    /* 0x194 : tzc_wram_tzsrg_r3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_wram_tzsrg_r3;

    /* 0x198 : tzc_wifi_dbg */
    union {
        struct {
            uint32_t tzc_mac_dbg_dis                :  1; /* [    0],          r,        0x1 */
            uint32_t reserved_1_31                  : 31; /* [31: 1],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_wifi_dbg;

    /* 0x19c  reserved */
    uint8_t RESERVED0x19c[164];

    /* 0x240 : tzc_pdm_ctrl */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_pdm_ctrl;

    /* 0x244 : tzc_uart_ctrl */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_uart_ctrl;

    /* 0x248 : tzc_i2c_ctrl */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_i2c_ctrl;

    /* 0x24C : tzc_timer_ctrl */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_timer_ctrl;

    /* 0x250 : tzc_i2s_ctrl */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_i2s_ctrl;

    /* 0x254  reserved */
    uint8_t RESERVED0x254[44];

    /* 0x280 : tzc_sf_tzsrg_ctrl */
    union {
        struct {
            uint32_t tzc_sf_tzsrg_r0_id_en          :  4; /* [ 3: 0],          r,        0xf */
            uint32_t tzc_sf_tzsrg_r1_id_en          :  4; /* [ 7: 4],          r,        0xf */
            uint32_t tzc_sf_tzsrg_r2_id_en          :  4; /* [11: 8],          r,        0xf */
            uint32_t tzc_sf_tzsrg_r3_id_en          :  4; /* [15:12],          r,        0xf */
            uint32_t tzc_sf_tzsrg_rx_id_en          :  4; /* [19:16],          r,        0xf */
            uint32_t tzc_sf_tzsrg_r0_en             :  1; /* [   20],          r,        0x0 */
            uint32_t tzc_sf_tzsrg_r1_en             :  1; /* [   21],          r,        0x0 */
            uint32_t tzc_sf_tzsrg_r2_en             :  1; /* [   22],          r,        0x0 */
            uint32_t tzc_sf_tzsrg_r3_en             :  1; /* [   23],          r,        0x0 */
            uint32_t tzc_sf_tzsrg_rx_en             :  1; /* [   24],          r,        0x0 */
            uint32_t tzc_sf_tzsrg_r0_lock           :  1; /* [   25],          r,        0x0 */
            uint32_t tzc_sf_tzsrg_r1_lock           :  1; /* [   26],          r,        0x0 */
            uint32_t tzc_sf_tzsrg_r2_lock           :  1; /* [   27],          r,        0x0 */
            uint32_t tzc_sf_tzsrg_r3_lock           :  1; /* [   28],          r,        0x0 */
            uint32_t tzc_sf_tzsrg_rx_lock           :  1; /* [   29],          r,        0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_sf_tzsrg_ctrl;

    /* 0x284 : tzc_sf_tzsrg_adr_mask */
    union {
        struct {
            uint32_t tzc_sf_tzsrg_adr_mask          : 19; /* [18: 0],          r,        0x0 */
            uint32_t reserved_19_30                 : 12; /* [30:19],       rsvd,        0x0 */
            uint32_t tzc_sf_tzsrg_adr_mask_lock     :  1; /* [   31],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_sf_tzsrg_adr_mask;

    /* 0x288 : tzc_sf_tzsrg_r0 */
    union {
        struct {
            uint32_t tzc_sf_tzsrg_r0_end            : 16; /* [15: 0],          r,     0xffff */
            uint32_t tzc_sf_tzsrg_r0_start          : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_sf_tzsrg_r0;

    /* 0x28C : tzc_sf_tzsrg_r1 */
    union {
        struct {
            uint32_t tzc_sf_tzsrg_r1_end            : 16; /* [15: 0],          r,     0xffff */
            uint32_t tzc_sf_tzsrg_r1_start          : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_sf_tzsrg_r1;

    /* 0x290 : tzc_sf_tzsrg_r2 */
    union {
        struct {
            uint32_t tzc_sf_tzsrg_r2_end            : 16; /* [15: 0],          r,     0xffff */
            uint32_t tzc_sf_tzsrg_r2_start          : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_sf_tzsrg_r2;

    /* 0x294 : tzc_sf_tzsrg_r3 */
    union {
        struct {
            uint32_t tzc_sf_tzsrg_r3_end            : 16; /* [15: 0],          r,     0xffff */
            uint32_t tzc_sf_tzsrg_r3_start          : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_sf_tzsrg_r3;

    /* 0x298 : tzc_sf_tzsrg_msb */
    union {
        struct {
            uint32_t tzc_sf_tzsrg_r0_end_msb        :  3; /* [ 2: 0],          r,        0x0 */
            uint32_t reserved_3                     :  1; /* [    3],       rsvd,        0x0 */
            uint32_t tzc_sf_tzsrg_r0_start_msb      :  3; /* [ 6: 4],          r,        0x0 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t tzc_sf_tzsrg_r1_end_msb        :  3; /* [10: 8],          r,        0x0 */
            uint32_t reserved_11                    :  1; /* [   11],       rsvd,        0x0 */
            uint32_t tzc_sf_tzsrg_r1_start_msb      :  3; /* [14:12],          r,        0x0 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t tzc_sf_tzsrg_r2_end_msb        :  3; /* [18:16],          r,        0x0 */
            uint32_t reserved_19                    :  1; /* [   19],       rsvd,        0x0 */
            uint32_t tzc_sf_tzsrg_r2_start_msb      :  3; /* [22:20],          r,        0x0 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t tzc_sf_tzsrg_r3_end_msb        :  3; /* [26:24],          r,        0x0 */
            uint32_t reserved_27                    :  1; /* [   27],       rsvd,        0x0 */
            uint32_t tzc_sf_tzsrg_r3_start_msb      :  3; /* [30:28],          r,        0x0 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_sf_tzsrg_msb;

    /* 0x29c  reserved */
    uint8_t RESERVED0x29c[100];

    /* 0x300 : tzc_mm_bmx_tzmid */
    union {
        struct {
            uint32_t reserved_0_1                   :  2; /* [ 1: 0],       rsvd,        0x0 */
            uint32_t tzc_codec_tzmid                :  1; /* [    2],          r,        0x0 */
            uint32_t reserved_3_17                  : 15; /* [17: 3],       rsvd,        0x0 */
            uint32_t tzc_codec_tzmid_sel            :  1; /* [   18],          r,        0x1 */
            uint32_t reserved_19_31                 : 13; /* [31:19],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_mm_bmx_tzmid;

    /* 0x304 : tzc_mm_bmx_tzmid_lock */
    union {
        struct {
            uint32_t reserved_0_1                   :  2; /* [ 1: 0],       rsvd,        0x0 */
            uint32_t tzc_codec_tzmid_lock           :  1; /* [    2],          r,        0x0 */
            uint32_t reserved_3_31                  : 29; /* [31: 3],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_mm_bmx_tzmid_lock;

    /* 0x308 : tzc_mm_bmx_s0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_mm_bmx_s0;

    /* 0x30C : tzc_mm_bmx_s1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_mm_bmx_s1;

    /* 0x310 : tzc_mm_bmx_s2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_mm_bmx_s2;

    /* 0x314 : tzc_mm_bmx_s_lock0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_mm_bmx_s_lock0;

    /* 0x318 : tzc_mm_bmx_s_lock1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_mm_bmx_s_lock1;

    /* 0x31c  reserved */
    uint8_t RESERVED0x31c[36];

    /* 0x340 : tzc_l2sram_tzsrg_ctrl */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_l2sram_tzsrg_ctrl;

    /* 0x344 : tzc_l2sram_tzsrg_adr_mask */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_l2sram_tzsrg_adr_mask;

    /* 0x348 : tzc_l2sram_tzsrg_r0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_l2sram_tzsrg_r0;

    /* 0x34C : tzc_l2sram_tzsrg_r1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_l2sram_tzsrg_r1;

    /* 0x350 : tzc_l2sram_tzsrg_r2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_l2sram_tzsrg_r2;

    /* 0x354 : tzc_l2sram_tzsrg_r3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_l2sram_tzsrg_r3;

    /* 0x358  reserved */
    uint8_t RESERVED0x358[8];

    /* 0x360 : tzc_vram_tzsrg_ctrl */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_vram_tzsrg_ctrl;

    /* 0x364 : tzc_vram_tzsrg_adr_mask */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_vram_tzsrg_adr_mask;

    /* 0x368 : tzc_vram_tzsrg_r0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_vram_tzsrg_r0;

    /* 0x36C : tzc_vram_tzsrg_r1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_vram_tzsrg_r1;

    /* 0x370 : tzc_vram_tzsrg_r2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_vram_tzsrg_r2;

    /* 0x374 : tzc_vram_tzsrg_r3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_vram_tzsrg_r3;

    /* 0x378  reserved */
    uint8_t RESERVED0x378[8];

    /* 0x380 : tzc_psrama_tzsrg_ctrl */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_psrama_tzsrg_ctrl;

    /* 0x384 : tzc_psrama_tzsrg_adr_mask */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_psrama_tzsrg_adr_mask;

    /* 0x388 : tzc_psrama_tzsrg_r0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_psrama_tzsrg_r0;

    /* 0x38C : tzc_psrama_tzsrg_r1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_psrama_tzsrg_r1;

    /* 0x390 : tzc_psrama_tzsrg_r2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_psrama_tzsrg_r2;

    /* 0x394 : tzc_psrama_tzsrg_r3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_psrama_tzsrg_r3;

    /* 0x398  reserved */
    uint8_t RESERVED0x398[8];

    /* 0x3A0 : tzc_psramb_tzsrg_ctrl */
    union {
        struct {
            uint32_t tzc_psramb_tzsrg_r0_id_en      :  4; /* [ 3: 0],          r,        0xf */
            uint32_t tzc_psramb_tzsrg_r1_id_en      :  4; /* [ 7: 4],          r,        0xf */
            uint32_t tzc_psramb_tzsrg_r2_id_en      :  4; /* [11: 8],          r,        0xf */
            uint32_t tzc_psramb_tzsrg_rx_id_en      :  4; /* [15:12],          r,        0xf */
            uint32_t tzc_psramb_tzsrg_r0_en         :  1; /* [   16],          r,        0x0 */
            uint32_t tzc_psramb_tzsrg_r1_en         :  1; /* [   17],          r,        0x0 */
            uint32_t tzc_psramb_tzsrg_r2_en         :  1; /* [   18],          r,        0x0 */
            uint32_t tzc_psramb_tzsrg_rx_en         :  1; /* [   19],          r,        0x0 */
            uint32_t reserved_20_23                 :  4; /* [23:20],       rsvd,        0x0 */
            uint32_t tzc_psramb_tzsrg_r0_lock       :  1; /* [   24],          r,        0x0 */
            uint32_t tzc_psramb_tzsrg_r1_lock       :  1; /* [   25],          r,        0x0 */
            uint32_t tzc_psramb_tzsrg_r2_lock       :  1; /* [   26],          r,        0x0 */
            uint32_t tzc_psramb_tzsrg_rx_lock       :  1; /* [   27],          r,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_psramb_tzsrg_ctrl;

    /* 0x3A4 : tzc_psramb_tzsrg_adr_mask */
    union {
        struct {
            uint32_t tzc_psramb_tzsrg_adr_mask      : 16; /* [15: 0],          r,        0x0 */
            uint32_t tzc_psramb_tzsrg_adr_mask_lock :  1; /* [   16],          r,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_psramb_tzsrg_adr_mask;

    /* 0x3A8 : tzc_psramb_tzsrg_r0 */
    union {
        struct {
            uint32_t tzc_psramb_tzsrg_r0_end        : 16; /* [15: 0],          r,     0xffff */
            uint32_t tzc_psramb_tzsrg_r0_start      : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_psramb_tzsrg_r0;

    /* 0x3AC : tzc_psramb_tzsrg_r1 */
    union {
        struct {
            uint32_t tzc_psramb_tzsrg_r1_end        : 16; /* [15: 0],          r,     0xffff */
            uint32_t tzc_psramb_tzsrg_r1_start      : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_psramb_tzsrg_r1;

    /* 0x3B0 : tzc_psramb_tzsrg_r2 */
    union {
        struct {
            uint32_t tzc_psramb_tzsrg_r2_end        : 16; /* [15: 0],          r,     0xffff */
            uint32_t tzc_psramb_tzsrg_r2_start      : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_psramb_tzsrg_r2;

    /* 0x3B4 : tzc_psramb_tzsrg_r3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_psramb_tzsrg_r3;

    /* 0x3b8  reserved */
    uint8_t RESERVED0x3b8[8];

    /* 0x3c0 : tzc_xram_tzsrg_ctrl */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_xram_tzsrg_ctrl;

    /* 0x3C4 : tzc_xram_tzsrg_adr_mask */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_xram_tzsrg_adr_mask;

    /* 0x3C8 : tzc_xram_tzsrg_r0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_xram_tzsrg_r0;

    /* 0x3CC : tzc_xram_tzsrg_r1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_xram_tzsrg_r1;

    /* 0x3D0 : tzc_xram_tzsrg_r2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_xram_tzsrg_r2;

    /* 0x3D4 : tzc_xram_tzsrg_r3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_xram_tzsrg_r3;

    /* 0x3d8  reserved */
    uint8_t RESERVED0x3d8[2856];

    /* 0xF00 : tzc_glb_ctrl_0 */
    union {
        struct {
            uint32_t tzc_glb_pwron_rst_tzsid_en     :  2; /* [ 1: 0],          r,        0x3 */
            uint32_t tzc_glb_cpu_reset_tzsid_en     :  2; /* [ 3: 2],          r,        0x3 */
            uint32_t tzc_glb_sys_reset_tzsid_en     :  2; /* [ 5: 4],          r,        0x3 */
            uint32_t tzc_glb_cpu2_reset_tzsid_en    :  2; /* [ 7: 6],          r,        0x3 */
            uint32_t tzc_glb_misc_tzsid_en          :  2; /* [ 9: 8],          r,        0x3 */
            uint32_t tzc_glb_sram_tzsid_en          :  2; /* [11:10],          r,        0x3 */
            uint32_t tzc_glb_swrst_tzsid_en         :  2; /* [13:12],          r,        0x3 */
            uint32_t tzc_glb_bmx_tzsid_en           :  2; /* [15:14],          r,        0x3 */
            uint32_t tzc_glb_dbg_tzsid_en           :  2; /* [17:16],          r,        0x3 */
            uint32_t tzc_glb_mbist_tzsid_en         :  2; /* [19:18],          r,        0x3 */
            uint32_t tzc_glb_clk_tzsid_en           :  2; /* [21:20],          r,        0x3 */
            uint32_t tzc_glb_int_tzsid_en           :  2; /* [23:22],          r,        0x3 */
            uint32_t tzc_glb_pwr_tzsid_en           :  2; /* [25:24],          r,        0x3 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_glb_ctrl_0;

    /* 0xF04 : tzc_glb_ctrl_1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_glb_ctrl_1;

    /* 0xF08 : tzc_glb_ctrl_2 */
    union {
        struct {
            uint32_t tzc_glb_pwron_rst_tzsid_lock   :  1; /* [    0],          r,        0x0 */
            uint32_t tzc_glb_cpu_reset_tzsid_lock   :  1; /* [    1],          r,        0x0 */
            uint32_t tzc_glb_sys_reset_tzsid_lock   :  1; /* [    2],          r,        0x0 */
            uint32_t tzc_glb_cpu2_reset_tzsid_lock  :  1; /* [    3],          r,        0x0 */
            uint32_t tzc_glb_misc_tzsid_lock        :  1; /* [    4],          r,        0x0 */
            uint32_t tzc_glb_sram_tzsid_lock        :  1; /* [    5],          r,        0x0 */
            uint32_t tzc_glb_swrst_tzsid_lock       :  1; /* [    6],          r,        0x0 */
            uint32_t tzc_glb_bmx_tzsid_lock         :  1; /* [    7],          r,        0x0 */
            uint32_t tzc_glb_dbg_tzsid_lock         :  1; /* [    8],          r,        0x0 */
            uint32_t tzc_glb_mbist_tzsid_lock       :  1; /* [    9],          r,        0x0 */
            uint32_t tzc_glb_clk_tzsid_lock         :  1; /* [   10],          r,        0x0 */
            uint32_t tzc_glb_int_tzsid_lock         :  1; /* [   11],          r,        0x0 */
            uint32_t tzc_glb_pwr_tzsid_lock         :  1; /* [   12],          r,        0x0 */
            uint32_t reserved_13_31                 : 19; /* [31:13],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_glb_ctrl_2;

    /* 0xf0c  reserved */
    uint8_t RESERVED0xf0c[20];

    /* 0xF20 : tzc_mm_ctrl_0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_mm_ctrl_0;

    /* 0xF24 : tzc_mm_ctrl_1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_mm_ctrl_1;

    /* 0xF28 : tzc_mm_ctrl_2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_mm_ctrl_2;

    /* 0xf2c  reserved */
    uint8_t RESERVED0xf2c[20];

    /* 0xF40 : tzc_se_ctrl_0 */
    union {
        struct {
            uint32_t tzc_se_sha_tzsid_en            :  2; /* [ 1: 0],          r,        0x3 */
            uint32_t tzc_se_aes_tzsid_en            :  2; /* [ 3: 2],          r,        0x3 */
            uint32_t tzc_se_trng_tzsid_en           :  2; /* [ 5: 4],          r,        0x3 */
            uint32_t tzc_se_pka_tzsid_en            :  2; /* [ 7: 6],          r,        0x3 */
            uint32_t tzc_se_cdet_tzsid_en           :  2; /* [ 9: 8],          r,        0x3 */
            uint32_t tzc_se_gmac_tzsid_en           :  2; /* [11:10],          r,        0x3 */
            uint32_t tzc_se_tzsid_crmd              :  1; /* [   12],          r,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t tzc_se_wdt_dly                 : 16; /* [31:16],          r,        0x5 */
        }BF;
        uint32_t WORD;
    } tzc_se_ctrl_0;

    /* 0xF44 : tzc_se_ctrl_1 */
    union {
        struct {
            uint32_t tzc_sf_cr_tzsid_en             :  2; /* [ 1: 0],          r,        0x3 */
            uint32_t tzc_sf_sec_tzsid_en            :  2; /* [ 3: 2],          r,        0x3 */
            uint32_t tzc_sf_tzsid_crmd              :  1; /* [    4],          r,        0x0 */
            uint32_t reserved_5_31                  : 27; /* [31: 5],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_se_ctrl_1;

    /* 0xF48 : tzc_se_ctrl_2 */
    union {
        struct {
            uint32_t tzc_se_sha_tzsid_lock          :  1; /* [    0],          r,        0x0 */
            uint32_t tzc_se_aes_tzsid_lock          :  1; /* [    1],          r,        0x0 */
            uint32_t tzc_se_trng_tzsid_lock         :  1; /* [    2],          r,        0x0 */
            uint32_t tzc_se_pka_tzsid_lock          :  1; /* [    3],          r,        0x0 */
            uint32_t tzc_se_cdet_tzsid_lock         :  1; /* [    4],          r,        0x0 */
            uint32_t tzc_se_gmac_tzsid_lock         :  1; /* [    5],          r,        0x0 */
            uint32_t tzc_se_tzsid_crmd_lock         :  1; /* [    6],          r,        0x0 */
            uint32_t reserved_7_15                  :  9; /* [15: 7],       rsvd,        0x0 */
            uint32_t tzc_sf_cr_tzsid_lock           :  1; /* [   16],          r,        0x0 */
            uint32_t tzc_sf_sec_tzsid_lock          :  1; /* [   17],          r,        0x0 */
            uint32_t tzc_sf_tzsid_crmd_lock         :  1; /* [   18],          r,        0x0 */
            uint32_t reserved_19_31                 : 13; /* [31:19],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_se_ctrl_2;

};

typedef volatile struct tzc_nsec_reg tzc_nsec_reg_t;


#endif  /* __TZC_NSEC_REG_H__ */
