/**
  ******************************************************************************
  * @file    ef_data_reg.h
  * @version V1.0
  * @date    2021-10-20
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
#ifndef  __EF_DATA_REG_H__
#define  __EF_DATA_REG_H__

#include "bl616.h"

/* 0x0 : ef_cfg_0 */
#define EF_DATA_EF_CFG_0_OFFSET                                 (0x0)
#define EF_DATA_EF_SF_AES_MODE                                  EF_DATA_EF_SF_AES_MODE
#define EF_DATA_EF_SF_AES_MODE_POS                              (0U)
#define EF_DATA_EF_SF_AES_MODE_LEN                              (2U)
#define EF_DATA_EF_SF_AES_MODE_MSK                              (((1U<<EF_DATA_EF_SF_AES_MODE_LEN)-1)<<EF_DATA_EF_SF_AES_MODE_POS)
#define EF_DATA_EF_SF_AES_MODE_UMSK                             (~(((1U<<EF_DATA_EF_SF_AES_MODE_LEN)-1)<<EF_DATA_EF_SF_AES_MODE_POS))
#define EF_DATA_EF_AI_DIS                                       EF_DATA_EF_AI_DIS
#define EF_DATA_EF_AI_DIS_POS                                   (2U)
#define EF_DATA_EF_AI_DIS_LEN                                   (1U)
#define EF_DATA_EF_AI_DIS_MSK                                   (((1U<<EF_DATA_EF_AI_DIS_LEN)-1)<<EF_DATA_EF_AI_DIS_POS)
#define EF_DATA_EF_AI_DIS_UMSK                                  (~(((1U<<EF_DATA_EF_AI_DIS_LEN)-1)<<EF_DATA_EF_AI_DIS_POS))
#define EF_DATA_EF_CPU0_DIS                                     EF_DATA_EF_CPU0_DIS
#define EF_DATA_EF_CPU0_DIS_POS                                 (3U)
#define EF_DATA_EF_CPU0_DIS_LEN                                 (1U)
#define EF_DATA_EF_CPU0_DIS_MSK                                 (((1U<<EF_DATA_EF_CPU0_DIS_LEN)-1)<<EF_DATA_EF_CPU0_DIS_POS)
#define EF_DATA_EF_CPU0_DIS_UMSK                                (~(((1U<<EF_DATA_EF_CPU0_DIS_LEN)-1)<<EF_DATA_EF_CPU0_DIS_POS))
#define EF_DATA_EF_SBOOT_EN                                     EF_DATA_EF_SBOOT_EN
#define EF_DATA_EF_SBOOT_EN_POS                                 (4U)
#define EF_DATA_EF_SBOOT_EN_LEN                                 (2U)
#define EF_DATA_EF_SBOOT_EN_MSK                                 (((1U<<EF_DATA_EF_SBOOT_EN_LEN)-1)<<EF_DATA_EF_SBOOT_EN_POS)
#define EF_DATA_EF_SBOOT_EN_UMSK                                (~(((1U<<EF_DATA_EF_SBOOT_EN_LEN)-1)<<EF_DATA_EF_SBOOT_EN_POS))
#define EF_DATA_EF_UART_DIS                                     EF_DATA_EF_UART_DIS
#define EF_DATA_EF_UART_DIS_POS                                 (6U)
#define EF_DATA_EF_UART_DIS_LEN                                 (4U)
#define EF_DATA_EF_UART_DIS_MSK                                 (((1U<<EF_DATA_EF_UART_DIS_LEN)-1)<<EF_DATA_EF_UART_DIS_POS)
#define EF_DATA_EF_UART_DIS_UMSK                                (~(((1U<<EF_DATA_EF_UART_DIS_LEN)-1)<<EF_DATA_EF_UART_DIS_POS))
#define EF_DATA_EF_BUS_RMP_SW_EN                                EF_DATA_EF_BUS_RMP_SW_EN
#define EF_DATA_EF_BUS_RMP_SW_EN_POS                            (10U)
#define EF_DATA_EF_BUS_RMP_SW_EN_LEN                            (1U)
#define EF_DATA_EF_BUS_RMP_SW_EN_MSK                            (((1U<<EF_DATA_EF_BUS_RMP_SW_EN_LEN)-1)<<EF_DATA_EF_BUS_RMP_SW_EN_POS)
#define EF_DATA_EF_BUS_RMP_SW_EN_UMSK                           (~(((1U<<EF_DATA_EF_BUS_RMP_SW_EN_LEN)-1)<<EF_DATA_EF_BUS_RMP_SW_EN_POS))
#define EF_DATA_EF_BUS_RMP_DIS                                  EF_DATA_EF_BUS_RMP_DIS
#define EF_DATA_EF_BUS_RMP_DIS_POS                              (11U)
#define EF_DATA_EF_BUS_RMP_DIS_LEN                              (1U)
#define EF_DATA_EF_BUS_RMP_DIS_MSK                              (((1U<<EF_DATA_EF_BUS_RMP_DIS_LEN)-1)<<EF_DATA_EF_BUS_RMP_DIS_POS)
#define EF_DATA_EF_BUS_RMP_DIS_UMSK                             (~(((1U<<EF_DATA_EF_BUS_RMP_DIS_LEN)-1)<<EF_DATA_EF_BUS_RMP_DIS_POS))
#define EF_DATA_EF_SF_KEY_RE_SEL                                EF_DATA_EF_SF_KEY_RE_SEL
#define EF_DATA_EF_SF_KEY_RE_SEL_POS                            (12U)
#define EF_DATA_EF_SF_KEY_RE_SEL_LEN                            (2U)
#define EF_DATA_EF_SF_KEY_RE_SEL_MSK                            (((1U<<EF_DATA_EF_SF_KEY_RE_SEL_LEN)-1)<<EF_DATA_EF_SF_KEY_RE_SEL_POS)
#define EF_DATA_EF_SF_KEY_RE_SEL_UMSK                           (~(((1U<<EF_DATA_EF_SF_KEY_RE_SEL_LEN)-1)<<EF_DATA_EF_SF_KEY_RE_SEL_POS))
#define EF_DATA_EF_SDU_DIS                                      EF_DATA_EF_SDU_DIS
#define EF_DATA_EF_SDU_DIS_POS                                  (14U)
#define EF_DATA_EF_SDU_DIS_LEN                                  (1U)
#define EF_DATA_EF_SDU_DIS_MSK                                  (((1U<<EF_DATA_EF_SDU_DIS_LEN)-1)<<EF_DATA_EF_SDU_DIS_POS)
#define EF_DATA_EF_SDU_DIS_UMSK                                 (~(((1U<<EF_DATA_EF_SDU_DIS_LEN)-1)<<EF_DATA_EF_SDU_DIS_POS))
#define EF_DATA_EF_BTDM_DIS                                     EF_DATA_EF_BTDM_DIS
#define EF_DATA_EF_BTDM_DIS_POS                                 (15U)
#define EF_DATA_EF_BTDM_DIS_LEN                                 (1U)
#define EF_DATA_EF_BTDM_DIS_MSK                                 (((1U<<EF_DATA_EF_BTDM_DIS_LEN)-1)<<EF_DATA_EF_BTDM_DIS_POS)
#define EF_DATA_EF_BTDM_DIS_UMSK                                (~(((1U<<EF_DATA_EF_BTDM_DIS_LEN)-1)<<EF_DATA_EF_BTDM_DIS_POS))
#define EF_DATA_EF_WIFI_DIS                                     EF_DATA_EF_WIFI_DIS
#define EF_DATA_EF_WIFI_DIS_POS                                 (16U)
#define EF_DATA_EF_WIFI_DIS_LEN                                 (1U)
#define EF_DATA_EF_WIFI_DIS_MSK                                 (((1U<<EF_DATA_EF_WIFI_DIS_LEN)-1)<<EF_DATA_EF_WIFI_DIS_POS)
#define EF_DATA_EF_WIFI_DIS_UMSK                                (~(((1U<<EF_DATA_EF_WIFI_DIS_LEN)-1)<<EF_DATA_EF_WIFI_DIS_POS))
#define EF_DATA_EF_0_KEY_ENC_EN                                 EF_DATA_EF_0_KEY_ENC_EN
#define EF_DATA_EF_0_KEY_ENC_EN_POS                             (17U)
#define EF_DATA_EF_0_KEY_ENC_EN_LEN                             (1U)
#define EF_DATA_EF_0_KEY_ENC_EN_MSK                             (((1U<<EF_DATA_EF_0_KEY_ENC_EN_LEN)-1)<<EF_DATA_EF_0_KEY_ENC_EN_POS)
#define EF_DATA_EF_0_KEY_ENC_EN_UMSK                            (~(((1U<<EF_DATA_EF_0_KEY_ENC_EN_LEN)-1)<<EF_DATA_EF_0_KEY_ENC_EN_POS))
#define EF_DATA_EF_CAM_DIS                                      EF_DATA_EF_CAM_DIS
#define EF_DATA_EF_CAM_DIS_POS                                  (18U)
#define EF_DATA_EF_CAM_DIS_LEN                                  (1U)
#define EF_DATA_EF_CAM_DIS_MSK                                  (((1U<<EF_DATA_EF_CAM_DIS_LEN)-1)<<EF_DATA_EF_CAM_DIS_POS)
#define EF_DATA_EF_CAM_DIS_UMSK                                 (~(((1U<<EF_DATA_EF_CAM_DIS_LEN)-1)<<EF_DATA_EF_CAM_DIS_POS))
#define EF_DATA_EF_M154_DIS                                     EF_DATA_EF_M154_DIS
#define EF_DATA_EF_M154_DIS_POS                                 (19U)
#define EF_DATA_EF_M154_DIS_LEN                                 (1U)
#define EF_DATA_EF_M154_DIS_MSK                                 (((1U<<EF_DATA_EF_M154_DIS_LEN)-1)<<EF_DATA_EF_M154_DIS_POS)
#define EF_DATA_EF_M154_DIS_UMSK                                (~(((1U<<EF_DATA_EF_M154_DIS_LEN)-1)<<EF_DATA_EF_M154_DIS_POS))
#define EF_DATA_EF_SDU_RST_OPT                                  EF_DATA_EF_SDU_RST_OPT
#define EF_DATA_EF_SDU_RST_OPT_POS                              (20U)
#define EF_DATA_EF_SDU_RST_OPT_LEN                              (1U)
#define EF_DATA_EF_SDU_RST_OPT_MSK                              (((1U<<EF_DATA_EF_SDU_RST_OPT_LEN)-1)<<EF_DATA_EF_SDU_RST_OPT_POS)
#define EF_DATA_EF_SDU_RST_OPT_UMSK                             (~(((1U<<EF_DATA_EF_SDU_RST_OPT_LEN)-1)<<EF_DATA_EF_SDU_RST_OPT_POS))
#define EF_DATA_EF_CPU_RST_DBG_DIS                              EF_DATA_EF_CPU_RST_DBG_DIS
#define EF_DATA_EF_CPU_RST_DBG_DIS_POS                          (21U)
#define EF_DATA_EF_CPU_RST_DBG_DIS_LEN                          (1U)
#define EF_DATA_EF_CPU_RST_DBG_DIS_MSK                          (((1U<<EF_DATA_EF_CPU_RST_DBG_DIS_LEN)-1)<<EF_DATA_EF_CPU_RST_DBG_DIS_POS)
#define EF_DATA_EF_CPU_RST_DBG_DIS_UMSK                         (~(((1U<<EF_DATA_EF_CPU_RST_DBG_DIS_LEN)-1)<<EF_DATA_EF_CPU_RST_DBG_DIS_POS))
#define EF_DATA_EF_SE_DBG_DIS                                   EF_DATA_EF_SE_DBG_DIS
#define EF_DATA_EF_SE_DBG_DIS_POS                               (22U)
#define EF_DATA_EF_SE_DBG_DIS_LEN                               (1U)
#define EF_DATA_EF_SE_DBG_DIS_MSK                               (((1U<<EF_DATA_EF_SE_DBG_DIS_LEN)-1)<<EF_DATA_EF_SE_DBG_DIS_POS)
#define EF_DATA_EF_SE_DBG_DIS_UMSK                              (~(((1U<<EF_DATA_EF_SE_DBG_DIS_LEN)-1)<<EF_DATA_EF_SE_DBG_DIS_POS))
#define EF_DATA_EF_EFUSE_DBG_DIS                                EF_DATA_EF_EFUSE_DBG_DIS
#define EF_DATA_EF_EFUSE_DBG_DIS_POS                            (23U)
#define EF_DATA_EF_EFUSE_DBG_DIS_LEN                            (1U)
#define EF_DATA_EF_EFUSE_DBG_DIS_MSK                            (((1U<<EF_DATA_EF_EFUSE_DBG_DIS_LEN)-1)<<EF_DATA_EF_EFUSE_DBG_DIS_POS)
#define EF_DATA_EF_EFUSE_DBG_DIS_UMSK                           (~(((1U<<EF_DATA_EF_EFUSE_DBG_DIS_LEN)-1)<<EF_DATA_EF_EFUSE_DBG_DIS_POS))
#define EF_DATA_EF_DBG_JTAG_1_DIS                               EF_DATA_EF_DBG_JTAG_1_DIS
#define EF_DATA_EF_DBG_JTAG_1_DIS_POS                           (24U)
#define EF_DATA_EF_DBG_JTAG_1_DIS_LEN                           (2U)
#define EF_DATA_EF_DBG_JTAG_1_DIS_MSK                           (((1U<<EF_DATA_EF_DBG_JTAG_1_DIS_LEN)-1)<<EF_DATA_EF_DBG_JTAG_1_DIS_POS)
#define EF_DATA_EF_DBG_JTAG_1_DIS_UMSK                          (~(((1U<<EF_DATA_EF_DBG_JTAG_1_DIS_LEN)-1)<<EF_DATA_EF_DBG_JTAG_1_DIS_POS))
#define EF_DATA_EF_DBG_JTAG_0_DIS                               EF_DATA_EF_DBG_JTAG_0_DIS
#define EF_DATA_EF_DBG_JTAG_0_DIS_POS                           (26U)
#define EF_DATA_EF_DBG_JTAG_0_DIS_LEN                           (2U)
#define EF_DATA_EF_DBG_JTAG_0_DIS_MSK                           (((1U<<EF_DATA_EF_DBG_JTAG_0_DIS_LEN)-1)<<EF_DATA_EF_DBG_JTAG_0_DIS_POS)
#define EF_DATA_EF_DBG_JTAG_0_DIS_UMSK                          (~(((1U<<EF_DATA_EF_DBG_JTAG_0_DIS_LEN)-1)<<EF_DATA_EF_DBG_JTAG_0_DIS_POS))
#define EF_DATA_EF_DBG_MODE                                     EF_DATA_EF_DBG_MODE
#define EF_DATA_EF_DBG_MODE_POS                                 (28U)
#define EF_DATA_EF_DBG_MODE_LEN                                 (4U)
#define EF_DATA_EF_DBG_MODE_MSK                                 (((1U<<EF_DATA_EF_DBG_MODE_LEN)-1)<<EF_DATA_EF_DBG_MODE_POS)
#define EF_DATA_EF_DBG_MODE_UMSK                                (~(((1U<<EF_DATA_EF_DBG_MODE_LEN)-1)<<EF_DATA_EF_DBG_MODE_POS))

/* 0x4 : ef_dbg_pwd_low */
#define EF_DATA_EF_DBG_PWD_LOW_OFFSET                           (0x4)
#define EF_DATA_EF_DBG_PWD_LOW                                  EF_DATA_EF_DBG_PWD_LOW
#define EF_DATA_EF_DBG_PWD_LOW_POS                              (0U)
#define EF_DATA_EF_DBG_PWD_LOW_LEN                              (32U)
#define EF_DATA_EF_DBG_PWD_LOW_MSK                              (((1U<<EF_DATA_EF_DBG_PWD_LOW_LEN)-1)<<EF_DATA_EF_DBG_PWD_LOW_POS)
#define EF_DATA_EF_DBG_PWD_LOW_UMSK                             (~(((1U<<EF_DATA_EF_DBG_PWD_LOW_LEN)-1)<<EF_DATA_EF_DBG_PWD_LOW_POS))

/* 0x8 : ef_dbg_pwd_high */
#define EF_DATA_EF_DBG_PWD_HIGH_OFFSET                          (0x8)
#define EF_DATA_EF_DBG_PWD_HIGH                                 EF_DATA_EF_DBG_PWD_HIGH
#define EF_DATA_EF_DBG_PWD_HIGH_POS                             (0U)
#define EF_DATA_EF_DBG_PWD_HIGH_LEN                             (32U)
#define EF_DATA_EF_DBG_PWD_HIGH_MSK                             (((1U<<EF_DATA_EF_DBG_PWD_HIGH_LEN)-1)<<EF_DATA_EF_DBG_PWD_HIGH_POS)
#define EF_DATA_EF_DBG_PWD_HIGH_UMSK                            (~(((1U<<EF_DATA_EF_DBG_PWD_HIGH_LEN)-1)<<EF_DATA_EF_DBG_PWD_HIGH_POS))

/* 0xC : ef_dbg_pwd2_low */
#define EF_DATA_EF_DBG_PWD2_LOW_OFFSET                          (0xC)
#define EF_DATA_EF_DBG_PWD2_LOW                                 EF_DATA_EF_DBG_PWD2_LOW
#define EF_DATA_EF_DBG_PWD2_LOW_POS                             (0U)
#define EF_DATA_EF_DBG_PWD2_LOW_LEN                             (32U)
#define EF_DATA_EF_DBG_PWD2_LOW_MSK                             (((1U<<EF_DATA_EF_DBG_PWD2_LOW_LEN)-1)<<EF_DATA_EF_DBG_PWD2_LOW_POS)
#define EF_DATA_EF_DBG_PWD2_LOW_UMSK                            (~(((1U<<EF_DATA_EF_DBG_PWD2_LOW_LEN)-1)<<EF_DATA_EF_DBG_PWD2_LOW_POS))

/* 0x10 : ef_dbg_pwd2_high */
#define EF_DATA_EF_DBG_PWD2_HIGH_OFFSET                         (0x10)
#define EF_DATA_EF_DBG_PWD2_HIGH                                EF_DATA_EF_DBG_PWD2_HIGH
#define EF_DATA_EF_DBG_PWD2_HIGH_POS                            (0U)
#define EF_DATA_EF_DBG_PWD2_HIGH_LEN                            (32U)
#define EF_DATA_EF_DBG_PWD2_HIGH_MSK                            (((1U<<EF_DATA_EF_DBG_PWD2_HIGH_LEN)-1)<<EF_DATA_EF_DBG_PWD2_HIGH_POS)
#define EF_DATA_EF_DBG_PWD2_HIGH_UMSK                           (~(((1U<<EF_DATA_EF_DBG_PWD2_HIGH_LEN)-1)<<EF_DATA_EF_DBG_PWD2_HIGH_POS))

/* 0x14 : ef_wifi_mac_low */
#define EF_DATA_EF_WIFI_MAC_LOW_OFFSET                          (0x14)
#define EF_DATA_EF_WIFI_MAC_LOW                                 EF_DATA_EF_WIFI_MAC_LOW
#define EF_DATA_EF_WIFI_MAC_LOW_POS                             (0U)
#define EF_DATA_EF_WIFI_MAC_LOW_LEN                             (32U)
#define EF_DATA_EF_WIFI_MAC_LOW_MSK                             (((1U<<EF_DATA_EF_WIFI_MAC_LOW_LEN)-1)<<EF_DATA_EF_WIFI_MAC_LOW_POS)
#define EF_DATA_EF_WIFI_MAC_LOW_UMSK                            (~(((1U<<EF_DATA_EF_WIFI_MAC_LOW_LEN)-1)<<EF_DATA_EF_WIFI_MAC_LOW_POS))

/* 0x18 : ef_wifi_mac_high */
#define EF_DATA_EF_WIFI_MAC_HIGH_OFFSET                         (0x18)
#define EF_DATA_EF_WIFI_MAC_HIGH                                EF_DATA_EF_WIFI_MAC_HIGH
#define EF_DATA_EF_WIFI_MAC_HIGH_POS                            (0U)
#define EF_DATA_EF_WIFI_MAC_HIGH_LEN                            (32U)
#define EF_DATA_EF_WIFI_MAC_HIGH_MSK                            (((1U<<EF_DATA_EF_WIFI_MAC_HIGH_LEN)-1)<<EF_DATA_EF_WIFI_MAC_HIGH_POS)
#define EF_DATA_EF_WIFI_MAC_HIGH_UMSK                           (~(((1U<<EF_DATA_EF_WIFI_MAC_HIGH_LEN)-1)<<EF_DATA_EF_WIFI_MAC_HIGH_POS))

/* 0x1C : ef_key_slot_0_w0 */
#define EF_DATA_EF_KEY_SLOT_0_W0_OFFSET                         (0x1C)
#define EF_DATA_EF_KEY_SLOT_0_W0                                EF_DATA_EF_KEY_SLOT_0_W0
#define EF_DATA_EF_KEY_SLOT_0_W0_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_0_W0_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_0_W0_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_0_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_0_W0_POS)
#define EF_DATA_EF_KEY_SLOT_0_W0_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_0_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_0_W0_POS))

/* 0x20 : ef_key_slot_0_w1 */
#define EF_DATA_EF_KEY_SLOT_0_W1_OFFSET                         (0x20)
#define EF_DATA_EF_KEY_SLOT_0_W1                                EF_DATA_EF_KEY_SLOT_0_W1
#define EF_DATA_EF_KEY_SLOT_0_W1_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_0_W1_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_0_W1_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_0_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_0_W1_POS)
#define EF_DATA_EF_KEY_SLOT_0_W1_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_0_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_0_W1_POS))

/* 0x24 : ef_key_slot_0_w2 */
#define EF_DATA_EF_KEY_SLOT_0_W2_OFFSET                         (0x24)
#define EF_DATA_EF_KEY_SLOT_0_W2                                EF_DATA_EF_KEY_SLOT_0_W2
#define EF_DATA_EF_KEY_SLOT_0_W2_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_0_W2_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_0_W2_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_0_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_0_W2_POS)
#define EF_DATA_EF_KEY_SLOT_0_W2_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_0_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_0_W2_POS))

/* 0x28 : ef_key_slot_0_w3 */
#define EF_DATA_EF_KEY_SLOT_0_W3_OFFSET                         (0x28)
#define EF_DATA_EF_KEY_SLOT_0_W3                                EF_DATA_EF_KEY_SLOT_0_W3
#define EF_DATA_EF_KEY_SLOT_0_W3_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_0_W3_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_0_W3_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_0_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_0_W3_POS)
#define EF_DATA_EF_KEY_SLOT_0_W3_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_0_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_0_W3_POS))

/* 0x2C : ef_key_slot_1_w0 */
#define EF_DATA_EF_KEY_SLOT_1_W0_OFFSET                         (0x2C)
#define EF_DATA_EF_KEY_SLOT_1_W0                                EF_DATA_EF_KEY_SLOT_1_W0
#define EF_DATA_EF_KEY_SLOT_1_W0_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_1_W0_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_1_W0_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_1_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_1_W0_POS)
#define EF_DATA_EF_KEY_SLOT_1_W0_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_1_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_1_W0_POS))

/* 0x30 : ef_key_slot_1_w1 */
#define EF_DATA_EF_KEY_SLOT_1_W1_OFFSET                         (0x30)
#define EF_DATA_EF_KEY_SLOT_1_W1                                EF_DATA_EF_KEY_SLOT_1_W1
#define EF_DATA_EF_KEY_SLOT_1_W1_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_1_W1_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_1_W1_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_1_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_1_W1_POS)
#define EF_DATA_EF_KEY_SLOT_1_W1_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_1_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_1_W1_POS))

/* 0x34 : ef_key_slot_1_w2 */
#define EF_DATA_EF_KEY_SLOT_1_W2_OFFSET                         (0x34)
#define EF_DATA_EF_KEY_SLOT_1_W2                                EF_DATA_EF_KEY_SLOT_1_W2
#define EF_DATA_EF_KEY_SLOT_1_W2_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_1_W2_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_1_W2_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_1_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_1_W2_POS)
#define EF_DATA_EF_KEY_SLOT_1_W2_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_1_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_1_W2_POS))

/* 0x38 : ef_key_slot_1_w3 */
#define EF_DATA_EF_KEY_SLOT_1_W3_OFFSET                         (0x38)
#define EF_DATA_EF_KEY_SLOT_1_W3                                EF_DATA_EF_KEY_SLOT_1_W3
#define EF_DATA_EF_KEY_SLOT_1_W3_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_1_W3_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_1_W3_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_1_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_1_W3_POS)
#define EF_DATA_EF_KEY_SLOT_1_W3_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_1_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_1_W3_POS))

/* 0x3C : ef_key_slot_2_w0 */
#define EF_DATA_EF_KEY_SLOT_2_W0_OFFSET                         (0x3C)
#define EF_DATA_EF_KEY_SLOT_2_W0                                EF_DATA_EF_KEY_SLOT_2_W0
#define EF_DATA_EF_KEY_SLOT_2_W0_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_2_W0_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_2_W0_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_2_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_2_W0_POS)
#define EF_DATA_EF_KEY_SLOT_2_W0_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_2_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_2_W0_POS))

/* 0x40 : ef_key_slot_2_w1 */
#define EF_DATA_EF_KEY_SLOT_2_W1_OFFSET                         (0x40)
#define EF_DATA_EF_KEY_SLOT_2_W1                                EF_DATA_EF_KEY_SLOT_2_W1
#define EF_DATA_EF_KEY_SLOT_2_W1_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_2_W1_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_2_W1_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_2_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_2_W1_POS)
#define EF_DATA_EF_KEY_SLOT_2_W1_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_2_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_2_W1_POS))

/* 0x44 : ef_key_slot_2_w2 */
#define EF_DATA_EF_KEY_SLOT_2_W2_OFFSET                         (0x44)
#define EF_DATA_EF_KEY_SLOT_2_W2                                EF_DATA_EF_KEY_SLOT_2_W2
#define EF_DATA_EF_KEY_SLOT_2_W2_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_2_W2_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_2_W2_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_2_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_2_W2_POS)
#define EF_DATA_EF_KEY_SLOT_2_W2_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_2_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_2_W2_POS))

/* 0x48 : ef_key_slot_2_w3 */
#define EF_DATA_EF_KEY_SLOT_2_W3_OFFSET                         (0x48)
#define EF_DATA_EF_KEY_SLOT_2_W3                                EF_DATA_EF_KEY_SLOT_2_W3
#define EF_DATA_EF_KEY_SLOT_2_W3_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_2_W3_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_2_W3_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_2_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_2_W3_POS)
#define EF_DATA_EF_KEY_SLOT_2_W3_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_2_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_2_W3_POS))

/* 0x4C : ef_key_slot_3_w0 */
#define EF_DATA_EF_KEY_SLOT_3_W0_OFFSET                         (0x4C)
#define EF_DATA_EF_KEY_SLOT_3_W0                                EF_DATA_EF_KEY_SLOT_3_W0
#define EF_DATA_EF_KEY_SLOT_3_W0_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_3_W0_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_3_W0_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_3_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_3_W0_POS)
#define EF_DATA_EF_KEY_SLOT_3_W0_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_3_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_3_W0_POS))

/* 0x50 : ef_key_slot_3_w1 */
#define EF_DATA_EF_KEY_SLOT_3_W1_OFFSET                         (0x50)
#define EF_DATA_EF_KEY_SLOT_3_W1                                EF_DATA_EF_KEY_SLOT_3_W1
#define EF_DATA_EF_KEY_SLOT_3_W1_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_3_W1_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_3_W1_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_3_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_3_W1_POS)
#define EF_DATA_EF_KEY_SLOT_3_W1_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_3_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_3_W1_POS))

/* 0x54 : ef_key_slot_3_w2 */
#define EF_DATA_EF_KEY_SLOT_3_W2_OFFSET                         (0x54)
#define EF_DATA_EF_KEY_SLOT_3_W2                                EF_DATA_EF_KEY_SLOT_3_W2
#define EF_DATA_EF_KEY_SLOT_3_W2_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_3_W2_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_3_W2_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_3_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_3_W2_POS)
#define EF_DATA_EF_KEY_SLOT_3_W2_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_3_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_3_W2_POS))

/* 0x58 : ef_key_slot_3_w3 */
#define EF_DATA_EF_KEY_SLOT_3_W3_OFFSET                         (0x58)
#define EF_DATA_EF_KEY_SLOT_3_W3                                EF_DATA_EF_KEY_SLOT_3_W3
#define EF_DATA_EF_KEY_SLOT_3_W3_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_3_W3_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_3_W3_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_3_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_3_W3_POS)
#define EF_DATA_EF_KEY_SLOT_3_W3_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_3_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_3_W3_POS))

/* 0x5C : ef_sw_usage_0 */
#define EF_DATA_EF_SW_USAGE_0_OFFSET                            (0x5C)
#define EF_DATA_EF_SW_USAGE_0                                   EF_DATA_EF_SW_USAGE_0
#define EF_DATA_EF_SW_USAGE_0_POS                               (0U)
#define EF_DATA_EF_SW_USAGE_0_LEN                               (32U)
#define EF_DATA_EF_SW_USAGE_0_MSK                               (((1U<<EF_DATA_EF_SW_USAGE_0_LEN)-1)<<EF_DATA_EF_SW_USAGE_0_POS)
#define EF_DATA_EF_SW_USAGE_0_UMSK                              (~(((1U<<EF_DATA_EF_SW_USAGE_0_LEN)-1)<<EF_DATA_EF_SW_USAGE_0_POS))

#define EF_DATA_EF_SBOOT_SIGN_MODE                              EF_DATA_EF_SBOOT_SIGN_MODE
#define EF_DATA_EF_SBOOT_SIGN_MODE_POS                          (7U)
#define EF_DATA_EF_SBOOT_SIGN_MODE_LEN                          (1U)
#define EF_DATA_EF_SBOOT_SIGN_MODE_MSK                          (((1U << EF_DATA_EF_SBOOT_SIGN_MODE_LEN) - 1) << EF_DATA_EF_SBOOT_SIGN_MODE_POS)
#define EF_DATA_EF_SBOOT_SIGN_MODE_UMSK                         (~(((1U << EF_DATA_EF_SBOOT_SIGN_MODE_LEN) - 1) << EF_DATA_EF_SBOOT_SIGN_MODE_POS))

/* 0x60 : ef_sw_usage_1 */
#define EF_DATA_EF_SW_USAGE_1_OFFSET                            (0x60)
#define EF_DATA_EF_SW_USAGE_1                                   EF_DATA_EF_SW_USAGE_1
#define EF_DATA_EF_SW_USAGE_1_POS                               (0U)
#define EF_DATA_EF_SW_USAGE_1_LEN                               (32U)
#define EF_DATA_EF_SW_USAGE_1_MSK                               (((1U<<EF_DATA_EF_SW_USAGE_1_LEN)-1)<<EF_DATA_EF_SW_USAGE_1_POS)
#define EF_DATA_EF_SW_USAGE_1_UMSK                              (~(((1U<<EF_DATA_EF_SW_USAGE_1_LEN)-1)<<EF_DATA_EF_SW_USAGE_1_POS))

/* 0x64 : ef_sw_usage_2 */
#define EF_DATA_EF_SW_USAGE_2_OFFSET                            (0x64)
#define EF_DATA_EF_SW_USAGE_2                                   EF_DATA_EF_SW_USAGE_2
#define EF_DATA_EF_SW_USAGE_2_POS                               (0U)
#define EF_DATA_EF_SW_USAGE_2_LEN                               (32U)
#define EF_DATA_EF_SW_USAGE_2_MSK                               (((1U<<EF_DATA_EF_SW_USAGE_2_LEN)-1)<<EF_DATA_EF_SW_USAGE_2_POS)
#define EF_DATA_EF_SW_USAGE_2_UMSK                              (~(((1U<<EF_DATA_EF_SW_USAGE_2_LEN)-1)<<EF_DATA_EF_SW_USAGE_2_POS))

/* 0x68 : ef_sw_usage_3 */
#define EF_DATA_EF_SW_USAGE_3_OFFSET                            (0x68)
#define EF_DATA_EF_SW_USAGE_3                                   EF_DATA_EF_SW_USAGE_3
#define EF_DATA_EF_SW_USAGE_3_POS                               (0U)
#define EF_DATA_EF_SW_USAGE_3_LEN                               (32U)
#define EF_DATA_EF_SW_USAGE_3_MSK                               (((1U<<EF_DATA_EF_SW_USAGE_3_LEN)-1)<<EF_DATA_EF_SW_USAGE_3_POS)
#define EF_DATA_EF_SW_USAGE_3_UMSK                              (~(((1U<<EF_DATA_EF_SW_USAGE_3_LEN)-1)<<EF_DATA_EF_SW_USAGE_3_POS))

/* 0x6C : ef_key_slot_11_w0 */
#define EF_DATA_EF_KEY_SLOT_11_W0_OFFSET                        (0x6C)
#define EF_DATA_EF_KEY_SLOT_11_W0                               EF_DATA_EF_KEY_SLOT_11_W0
#define EF_DATA_EF_KEY_SLOT_11_W0_POS                           (0U)
#define EF_DATA_EF_KEY_SLOT_11_W0_LEN                           (32U)
#define EF_DATA_EF_KEY_SLOT_11_W0_MSK                           (((1U<<EF_DATA_EF_KEY_SLOT_11_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_11_W0_POS)
#define EF_DATA_EF_KEY_SLOT_11_W0_UMSK                          (~(((1U<<EF_DATA_EF_KEY_SLOT_11_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_11_W0_POS))

/* 0x70 : ef_key_slot_11_w1 */
#define EF_DATA_EF_KEY_SLOT_11_W1_OFFSET                        (0x70)
#define EF_DATA_EF_KEY_SLOT_11_W1                               EF_DATA_EF_KEY_SLOT_11_W1
#define EF_DATA_EF_KEY_SLOT_11_W1_POS                           (0U)
#define EF_DATA_EF_KEY_SLOT_11_W1_LEN                           (32U)
#define EF_DATA_EF_KEY_SLOT_11_W1_MSK                           (((1U<<EF_DATA_EF_KEY_SLOT_11_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_11_W1_POS)
#define EF_DATA_EF_KEY_SLOT_11_W1_UMSK                          (~(((1U<<EF_DATA_EF_KEY_SLOT_11_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_11_W1_POS))

/* 0x74 : ef_key_slot_11_w2 */
#define EF_DATA_EF_KEY_SLOT_11_W2_OFFSET                        (0x74)
#define EF_DATA_EF_KEY_SLOT_11_W2                               EF_DATA_EF_KEY_SLOT_11_W2
#define EF_DATA_EF_KEY_SLOT_11_W2_POS                           (0U)
#define EF_DATA_EF_KEY_SLOT_11_W2_LEN                           (32U)
#define EF_DATA_EF_KEY_SLOT_11_W2_MSK                           (((1U<<EF_DATA_EF_KEY_SLOT_11_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_11_W2_POS)
#define EF_DATA_EF_KEY_SLOT_11_W2_UMSK                          (~(((1U<<EF_DATA_EF_KEY_SLOT_11_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_11_W2_POS))

/* 0x78 : ef_key_slot_11_w3 */
#define EF_DATA_EF_KEY_SLOT_11_W3_OFFSET                        (0x78)
#define EF_DATA_EF_KEY_SLOT_11_W3                               EF_DATA_EF_KEY_SLOT_11_W3
#define EF_DATA_EF_KEY_SLOT_11_W3_POS                           (0U)
#define EF_DATA_EF_KEY_SLOT_11_W3_LEN                           (32U)
#define EF_DATA_EF_KEY_SLOT_11_W3_MSK                           (((1U<<EF_DATA_EF_KEY_SLOT_11_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_11_W3_POS)
#define EF_DATA_EF_KEY_SLOT_11_W3_UMSK                          (~(((1U<<EF_DATA_EF_KEY_SLOT_11_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_11_W3_POS))

/* 0x7C : ef_data_0_lock */
#define EF_DATA_0_LOCK_OFFSET                                   (0x7C)
#define EF_DATA_EF_SEC_LIFECYCLE                                EF_DATA_EF_SEC_LIFECYCLE
#define EF_DATA_EF_SEC_LIFECYCLE_POS                            (0U)
#define EF_DATA_EF_SEC_LIFECYCLE_LEN                            (4U)
#define EF_DATA_EF_SEC_LIFECYCLE_MSK                            (((1U<<EF_DATA_EF_SEC_LIFECYCLE_LEN)-1)<<EF_DATA_EF_SEC_LIFECYCLE_POS)
#define EF_DATA_EF_SEC_LIFECYCLE_UMSK                           (~(((1U<<EF_DATA_EF_SEC_LIFECYCLE_LEN)-1)<<EF_DATA_EF_SEC_LIFECYCLE_POS))
#define EF_DATA_WR_LOCK_RSVD_0                                  EF_DATA_WR_LOCK_RSVD_0
#define EF_DATA_WR_LOCK_RSVD_0_POS                              (4U)
#define EF_DATA_WR_LOCK_RSVD_0_LEN                              (9U)
#define EF_DATA_WR_LOCK_RSVD_0_MSK                              (((1U<<EF_DATA_WR_LOCK_RSVD_0_LEN)-1)<<EF_DATA_WR_LOCK_RSVD_0_POS)
#define EF_DATA_WR_LOCK_RSVD_0_UMSK                             (~(((1U<<EF_DATA_WR_LOCK_RSVD_0_LEN)-1)<<EF_DATA_WR_LOCK_RSVD_0_POS))
#define EF_DATA_FLASH_DLY_COE                                   EF_DATA_FLASH_DLY_COE
#define EF_DATA_FLASH_DLY_COE_POS                               (13U)
#define EF_DATA_FLASH_DLY_COE_LEN                               (1U)
#define EF_DATA_FLASH_DLY_COE_MSK                               (((1U<<EF_DATA_FLASH_DLY_COE_LEN)-1)<<EF_DATA_FLASH_DLY_COE_POS)
#define EF_DATA_FLASH_DLY_COE_UMSK                              (~(((1U<<EF_DATA_FLASH_DLY_COE_LEN)-1)<<EF_DATA_FLASH_DLY_COE_POS))
#define EF_DATA_WR_LOCK_BOOT_MODE                               EF_DATA_WR_LOCK_BOOT_MODE
#define EF_DATA_WR_LOCK_BOOT_MODE_POS                           (14U)
#define EF_DATA_WR_LOCK_BOOT_MODE_LEN                           (1U)
#define EF_DATA_WR_LOCK_BOOT_MODE_MSK                           (((1U<<EF_DATA_WR_LOCK_BOOT_MODE_LEN)-1)<<EF_DATA_WR_LOCK_BOOT_MODE_POS)
#define EF_DATA_WR_LOCK_BOOT_MODE_UMSK                          (~(((1U<<EF_DATA_WR_LOCK_BOOT_MODE_LEN)-1)<<EF_DATA_WR_LOCK_BOOT_MODE_POS))
#define EF_DATA_WR_LOCK_DBG_PWD                                 EF_DATA_WR_LOCK_DBG_PWD
#define EF_DATA_WR_LOCK_DBG_PWD_POS                             (15U)
#define EF_DATA_WR_LOCK_DBG_PWD_LEN                             (1U)
#define EF_DATA_WR_LOCK_DBG_PWD_MSK                             (((1U<<EF_DATA_WR_LOCK_DBG_PWD_LEN)-1)<<EF_DATA_WR_LOCK_DBG_PWD_POS)
#define EF_DATA_WR_LOCK_DBG_PWD_UMSK                            (~(((1U<<EF_DATA_WR_LOCK_DBG_PWD_LEN)-1)<<EF_DATA_WR_LOCK_DBG_PWD_POS))
#define EF_DATA_WR_LOCK_WIFI_MAC                                EF_DATA_WR_LOCK_WIFI_MAC
#define EF_DATA_WR_LOCK_WIFI_MAC_POS                            (16U)
#define EF_DATA_WR_LOCK_WIFI_MAC_LEN                            (1U)
#define EF_DATA_WR_LOCK_WIFI_MAC_MSK                            (((1U<<EF_DATA_WR_LOCK_WIFI_MAC_LEN)-1)<<EF_DATA_WR_LOCK_WIFI_MAC_POS)
#define EF_DATA_WR_LOCK_WIFI_MAC_UMSK                           (~(((1U<<EF_DATA_WR_LOCK_WIFI_MAC_LEN)-1)<<EF_DATA_WR_LOCK_WIFI_MAC_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_0                              EF_DATA_WR_LOCK_KEY_SLOT_0
#define EF_DATA_WR_LOCK_KEY_SLOT_0_POS                          (17U)
#define EF_DATA_WR_LOCK_KEY_SLOT_0_LEN                          (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_0_MSK                          (((1U<<EF_DATA_WR_LOCK_KEY_SLOT_0_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_0_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_0_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_KEY_SLOT_0_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_0_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_1                              EF_DATA_WR_LOCK_KEY_SLOT_1
#define EF_DATA_WR_LOCK_KEY_SLOT_1_POS                          (18U)
#define EF_DATA_WR_LOCK_KEY_SLOT_1_LEN                          (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_1_MSK                          (((1U<<EF_DATA_WR_LOCK_KEY_SLOT_1_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_1_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_1_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_KEY_SLOT_1_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_1_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_2                              EF_DATA_WR_LOCK_KEY_SLOT_2
#define EF_DATA_WR_LOCK_KEY_SLOT_2_POS                          (19U)
#define EF_DATA_WR_LOCK_KEY_SLOT_2_LEN                          (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_2_MSK                          (((1U<<EF_DATA_WR_LOCK_KEY_SLOT_2_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_2_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_2_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_KEY_SLOT_2_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_2_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_3                              EF_DATA_WR_LOCK_KEY_SLOT_3
#define EF_DATA_WR_LOCK_KEY_SLOT_3_POS                          (20U)
#define EF_DATA_WR_LOCK_KEY_SLOT_3_LEN                          (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_3_MSK                          (((1U<<EF_DATA_WR_LOCK_KEY_SLOT_3_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_3_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_3_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_KEY_SLOT_3_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_3_POS))
#define EF_DATA_WR_LOCK_SW_USAGE_0                              EF_DATA_WR_LOCK_SW_USAGE_0
#define EF_DATA_WR_LOCK_SW_USAGE_0_POS                          (21U)
#define EF_DATA_WR_LOCK_SW_USAGE_0_LEN                          (1U)
#define EF_DATA_WR_LOCK_SW_USAGE_0_MSK                          (((1U<<EF_DATA_WR_LOCK_SW_USAGE_0_LEN)-1)<<EF_DATA_WR_LOCK_SW_USAGE_0_POS)
#define EF_DATA_WR_LOCK_SW_USAGE_0_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_SW_USAGE_0_LEN)-1)<<EF_DATA_WR_LOCK_SW_USAGE_0_POS))
#define EF_DATA_WR_LOCK_SW_USAGE_1                              EF_DATA_WR_LOCK_SW_USAGE_1
#define EF_DATA_WR_LOCK_SW_USAGE_1_POS                          (22U)
#define EF_DATA_WR_LOCK_SW_USAGE_1_LEN                          (1U)
#define EF_DATA_WR_LOCK_SW_USAGE_1_MSK                          (((1U<<EF_DATA_WR_LOCK_SW_USAGE_1_LEN)-1)<<EF_DATA_WR_LOCK_SW_USAGE_1_POS)
#define EF_DATA_WR_LOCK_SW_USAGE_1_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_SW_USAGE_1_LEN)-1)<<EF_DATA_WR_LOCK_SW_USAGE_1_POS))
#define EF_DATA_WR_LOCK_SW_USAGE_2                              EF_DATA_WR_LOCK_SW_USAGE_2
#define EF_DATA_WR_LOCK_SW_USAGE_2_POS                          (23U)
#define EF_DATA_WR_LOCK_SW_USAGE_2_LEN                          (1U)
#define EF_DATA_WR_LOCK_SW_USAGE_2_MSK                          (((1U<<EF_DATA_WR_LOCK_SW_USAGE_2_LEN)-1)<<EF_DATA_WR_LOCK_SW_USAGE_2_POS)
#define EF_DATA_WR_LOCK_SW_USAGE_2_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_SW_USAGE_2_LEN)-1)<<EF_DATA_WR_LOCK_SW_USAGE_2_POS))
#define EF_DATA_WR_LOCK_SW_USAGE_3                              EF_DATA_WR_LOCK_SW_USAGE_3
#define EF_DATA_WR_LOCK_SW_USAGE_3_POS                          (24U)
#define EF_DATA_WR_LOCK_SW_USAGE_3_LEN                          (1U)
#define EF_DATA_WR_LOCK_SW_USAGE_3_MSK                          (((1U<<EF_DATA_WR_LOCK_SW_USAGE_3_LEN)-1)<<EF_DATA_WR_LOCK_SW_USAGE_3_POS)
#define EF_DATA_WR_LOCK_SW_USAGE_3_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_SW_USAGE_3_LEN)-1)<<EF_DATA_WR_LOCK_SW_USAGE_3_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_11                             EF_DATA_WR_LOCK_KEY_SLOT_11
#define EF_DATA_WR_LOCK_KEY_SLOT_11_POS                         (25U)
#define EF_DATA_WR_LOCK_KEY_SLOT_11_LEN                         (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_11_MSK                         (((1U<<EF_DATA_WR_LOCK_KEY_SLOT_11_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_11_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_11_UMSK                        (~(((1U<<EF_DATA_WR_LOCK_KEY_SLOT_11_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_11_POS))
#define EF_DATA_RD_LOCK_DBG_PWD                                 EF_DATA_RD_LOCK_DBG_PWD
#define EF_DATA_RD_LOCK_DBG_PWD_POS                             (26U)
#define EF_DATA_RD_LOCK_DBG_PWD_LEN                             (1U)
#define EF_DATA_RD_LOCK_DBG_PWD_MSK                             (((1U<<EF_DATA_RD_LOCK_DBG_PWD_LEN)-1)<<EF_DATA_RD_LOCK_DBG_PWD_POS)
#define EF_DATA_RD_LOCK_DBG_PWD_UMSK                            (~(((1U<<EF_DATA_RD_LOCK_DBG_PWD_LEN)-1)<<EF_DATA_RD_LOCK_DBG_PWD_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_0                              EF_DATA_RD_LOCK_KEY_SLOT_0
#define EF_DATA_RD_LOCK_KEY_SLOT_0_POS                          (27U)
#define EF_DATA_RD_LOCK_KEY_SLOT_0_LEN                          (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_0_MSK                          (((1U<<EF_DATA_RD_LOCK_KEY_SLOT_0_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_0_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_0_UMSK                         (~(((1U<<EF_DATA_RD_LOCK_KEY_SLOT_0_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_0_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_1                              EF_DATA_RD_LOCK_KEY_SLOT_1
#define EF_DATA_RD_LOCK_KEY_SLOT_1_POS                          (28U)
#define EF_DATA_RD_LOCK_KEY_SLOT_1_LEN                          (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_1_MSK                          (((1U<<EF_DATA_RD_LOCK_KEY_SLOT_1_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_1_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_1_UMSK                         (~(((1U<<EF_DATA_RD_LOCK_KEY_SLOT_1_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_1_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_2                              EF_DATA_RD_LOCK_KEY_SLOT_2
#define EF_DATA_RD_LOCK_KEY_SLOT_2_POS                          (29U)
#define EF_DATA_RD_LOCK_KEY_SLOT_2_LEN                          (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_2_MSK                          (((1U<<EF_DATA_RD_LOCK_KEY_SLOT_2_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_2_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_2_UMSK                         (~(((1U<<EF_DATA_RD_LOCK_KEY_SLOT_2_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_2_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_3                              EF_DATA_RD_LOCK_KEY_SLOT_3
#define EF_DATA_RD_LOCK_KEY_SLOT_3_POS                          (30U)
#define EF_DATA_RD_LOCK_KEY_SLOT_3_LEN                          (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_3_MSK                          (((1U<<EF_DATA_RD_LOCK_KEY_SLOT_3_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_3_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_3_UMSK                         (~(((1U<<EF_DATA_RD_LOCK_KEY_SLOT_3_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_3_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_11                             EF_DATA_RD_LOCK_KEY_SLOT_11
#define EF_DATA_RD_LOCK_KEY_SLOT_11_POS                         (31U)
#define EF_DATA_RD_LOCK_KEY_SLOT_11_LEN                         (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_11_MSK                         (((1U<<EF_DATA_RD_LOCK_KEY_SLOT_11_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_11_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_11_UMSK                        (~(((1U<<EF_DATA_RD_LOCK_KEY_SLOT_11_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_11_POS))

/* 0x80 : ef_key_slot_4_w0 */
#define EF_DATA_EF_KEY_SLOT_4_W0_OFFSET                         (0x80)
#define EF_DATA_EF_KEY_SLOT_4_W0                                EF_DATA_EF_KEY_SLOT_4_W0
#define EF_DATA_EF_KEY_SLOT_4_W0_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_4_W0_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_4_W0_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_4_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_4_W0_POS)
#define EF_DATA_EF_KEY_SLOT_4_W0_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_4_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_4_W0_POS))

/* 0x84 : ef_key_slot_4_w1 */
#define EF_DATA_EF_KEY_SLOT_4_W1_OFFSET                         (0x84)
#define EF_DATA_EF_KEY_SLOT_4_W1                                EF_DATA_EF_KEY_SLOT_4_W1
#define EF_DATA_EF_KEY_SLOT_4_W1_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_4_W1_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_4_W1_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_4_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_4_W1_POS)
#define EF_DATA_EF_KEY_SLOT_4_W1_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_4_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_4_W1_POS))

/* 0x88 : ef_key_slot_4_w2 */
#define EF_DATA_EF_KEY_SLOT_4_W2_OFFSET                         (0x88)
#define EF_DATA_EF_KEY_SLOT_4_W2                                EF_DATA_EF_KEY_SLOT_4_W2
#define EF_DATA_EF_KEY_SLOT_4_W2_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_4_W2_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_4_W2_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_4_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_4_W2_POS)
#define EF_DATA_EF_KEY_SLOT_4_W2_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_4_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_4_W2_POS))

/* 0x8C : ef_key_slot_4_w3 */
#define EF_DATA_EF_KEY_SLOT_4_W3_OFFSET                         (0x8C)
#define EF_DATA_EF_KEY_SLOT_4_W3                                EF_DATA_EF_KEY_SLOT_4_W3
#define EF_DATA_EF_KEY_SLOT_4_W3_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_4_W3_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_4_W3_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_4_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_4_W3_POS)
#define EF_DATA_EF_KEY_SLOT_4_W3_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_4_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_4_W3_POS))

/* 0x90 : ef_key_slot_5_w0 */
#define EF_DATA_EF_KEY_SLOT_5_W0_OFFSET                         (0x90)
#define EF_DATA_EF_KEY_SLOT_5_W0                                EF_DATA_EF_KEY_SLOT_5_W0
#define EF_DATA_EF_KEY_SLOT_5_W0_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_5_W0_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_5_W0_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_5_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_5_W0_POS)
#define EF_DATA_EF_KEY_SLOT_5_W0_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_5_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_5_W0_POS))

/* 0x94 : ef_key_slot_5_w1 */
#define EF_DATA_EF_KEY_SLOT_5_W1_OFFSET                         (0x94)
#define EF_DATA_EF_KEY_SLOT_5_W1                                EF_DATA_EF_KEY_SLOT_5_W1
#define EF_DATA_EF_KEY_SLOT_5_W1_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_5_W1_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_5_W1_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_5_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_5_W1_POS)
#define EF_DATA_EF_KEY_SLOT_5_W1_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_5_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_5_W1_POS))

/* 0x98 : ef_key_slot_5_w2 */
#define EF_DATA_EF_KEY_SLOT_5_W2_OFFSET                         (0x98)
#define EF_DATA_EF_KEY_SLOT_5_W2                                EF_DATA_EF_KEY_SLOT_5_W2
#define EF_DATA_EF_KEY_SLOT_5_W2_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_5_W2_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_5_W2_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_5_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_5_W2_POS)
#define EF_DATA_EF_KEY_SLOT_5_W2_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_5_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_5_W2_POS))

/* 0x9C : ef_key_slot_5_w3 */
#define EF_DATA_EF_KEY_SLOT_5_W3_OFFSET                         (0x9C)
#define EF_DATA_EF_KEY_SLOT_5_W3                                EF_DATA_EF_KEY_SLOT_5_W3
#define EF_DATA_EF_KEY_SLOT_5_W3_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_5_W3_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_5_W3_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_5_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_5_W3_POS)
#define EF_DATA_EF_KEY_SLOT_5_W3_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_5_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_5_W3_POS))

/* 0xA0 : ef_key_slot_6_w0 */
#define EF_DATA_EF_KEY_SLOT_6_W0_OFFSET                         (0xA0)
#define EF_DATA_EF_KEY_SLOT_6_W0                                EF_DATA_EF_KEY_SLOT_6_W0
#define EF_DATA_EF_KEY_SLOT_6_W0_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_6_W0_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_6_W0_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_6_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_6_W0_POS)
#define EF_DATA_EF_KEY_SLOT_6_W0_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_6_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_6_W0_POS))

/* 0xA4 : ef_key_slot_6_w1 */
#define EF_DATA_EF_KEY_SLOT_6_W1_OFFSET                         (0xA4)
#define EF_DATA_EF_KEY_SLOT_6_W1                                EF_DATA_EF_KEY_SLOT_6_W1
#define EF_DATA_EF_KEY_SLOT_6_W1_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_6_W1_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_6_W1_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_6_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_6_W1_POS)
#define EF_DATA_EF_KEY_SLOT_6_W1_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_6_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_6_W1_POS))

/* 0xA8 : ef_key_slot_6_w2 */
#define EF_DATA_EF_KEY_SLOT_6_W2_OFFSET                         (0xA8)
#define EF_DATA_EF_KEY_SLOT_6_W2                                EF_DATA_EF_KEY_SLOT_6_W2
#define EF_DATA_EF_KEY_SLOT_6_W2_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_6_W2_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_6_W2_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_6_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_6_W2_POS)
#define EF_DATA_EF_KEY_SLOT_6_W2_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_6_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_6_W2_POS))

/* 0xAC : ef_key_slot_6_w3 */
#define EF_DATA_EF_KEY_SLOT_6_W3_OFFSET                         (0xAC)
#define EF_DATA_EF_KEY_SLOT_6_W3                                EF_DATA_EF_KEY_SLOT_6_W3
#define EF_DATA_EF_KEY_SLOT_6_W3_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_6_W3_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_6_W3_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_6_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_6_W3_POS)
#define EF_DATA_EF_KEY_SLOT_6_W3_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_6_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_6_W3_POS))

/* 0xB0 : ef_key_slot_7_w0 */
#define EF_DATA_EF_KEY_SLOT_7_W0_OFFSET                         (0xB0)
#define EF_DATA_EF_KEY_SLOT_7_W0                                EF_DATA_EF_KEY_SLOT_7_W0
#define EF_DATA_EF_KEY_SLOT_7_W0_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_7_W0_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_7_W0_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_7_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_7_W0_POS)
#define EF_DATA_EF_KEY_SLOT_7_W0_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_7_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_7_W0_POS))

/* 0xB4 : ef_key_slot_7_w1 */
#define EF_DATA_EF_KEY_SLOT_7_W1_OFFSET                         (0xB4)
#define EF_DATA_EF_KEY_SLOT_7_W1                                EF_DATA_EF_KEY_SLOT_7_W1
#define EF_DATA_EF_KEY_SLOT_7_W1_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_7_W1_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_7_W1_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_7_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_7_W1_POS)
#define EF_DATA_EF_KEY_SLOT_7_W1_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_7_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_7_W1_POS))

/* 0xB8 : ef_key_slot_7_w2 */
#define EF_DATA_EF_KEY_SLOT_7_W2_OFFSET                         (0xB8)
#define EF_DATA_EF_KEY_SLOT_7_W2                                EF_DATA_EF_KEY_SLOT_7_W2
#define EF_DATA_EF_KEY_SLOT_7_W2_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_7_W2_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_7_W2_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_7_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_7_W2_POS)
#define EF_DATA_EF_KEY_SLOT_7_W2_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_7_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_7_W2_POS))

/* 0xBC : ef_key_slot_7_w3 */
#define EF_DATA_EF_KEY_SLOT_7_W3_OFFSET                         (0xBC)
#define EF_DATA_EF_KEY_SLOT_7_W3                                EF_DATA_EF_KEY_SLOT_7_W3
#define EF_DATA_EF_KEY_SLOT_7_W3_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_7_W3_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_7_W3_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_7_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_7_W3_POS)
#define EF_DATA_EF_KEY_SLOT_7_W3_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_7_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_7_W3_POS))

/* 0xC0 : ef_key_slot_8_w0 */
#define EF_DATA_EF_KEY_SLOT_8_W0_OFFSET                         (0xC0)
#define EF_DATA_EF_KEY_SLOT_8_W0                                EF_DATA_EF_KEY_SLOT_8_W0
#define EF_DATA_EF_KEY_SLOT_8_W0_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_8_W0_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_8_W0_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_8_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_8_W0_POS)
#define EF_DATA_EF_KEY_SLOT_8_W0_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_8_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_8_W0_POS))

/* 0xC4 : ef_key_slot_8_w1 */
#define EF_DATA_EF_KEY_SLOT_8_W1_OFFSET                         (0xC4)
#define EF_DATA_EF_KEY_SLOT_8_W1                                EF_DATA_EF_KEY_SLOT_8_W1
#define EF_DATA_EF_KEY_SLOT_8_W1_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_8_W1_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_8_W1_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_8_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_8_W1_POS)
#define EF_DATA_EF_KEY_SLOT_8_W1_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_8_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_8_W1_POS))

/* 0xC8 : ef_key_slot_8_w2 */
#define EF_DATA_EF_KEY_SLOT_8_W2_OFFSET                         (0xC8)
#define EF_DATA_EF_KEY_SLOT_8_W2                                EF_DATA_EF_KEY_SLOT_8_W2
#define EF_DATA_EF_KEY_SLOT_8_W2_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_8_W2_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_8_W2_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_8_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_8_W2_POS)
#define EF_DATA_EF_KEY_SLOT_8_W2_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_8_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_8_W2_POS))

/* 0xCC : ef_key_slot_8_w3 */
#define EF_DATA_EF_KEY_SLOT_8_W3_OFFSET                         (0xCC)
#define EF_DATA_EF_KEY_SLOT_8_W3                                EF_DATA_EF_KEY_SLOT_8_W3
#define EF_DATA_EF_KEY_SLOT_8_W3_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_8_W3_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_8_W3_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_8_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_8_W3_POS)
#define EF_DATA_EF_KEY_SLOT_8_W3_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_8_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_8_W3_POS))

/* 0xD0 : ef_key_slot_9_w0 */
#define EF_DATA_EF_KEY_SLOT_9_W0_OFFSET                         (0xD0)
#define EF_DATA_EF_KEY_SLOT_9_W0                                EF_DATA_EF_KEY_SLOT_9_W0
#define EF_DATA_EF_KEY_SLOT_9_W0_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_9_W0_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_9_W0_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_9_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_9_W0_POS)
#define EF_DATA_EF_KEY_SLOT_9_W0_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_9_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_9_W0_POS))

/* 0xD4 : ef_key_slot_9_w1 */
#define EF_DATA_EF_KEY_SLOT_9_W1_OFFSET                         (0xD4)
#define EF_DATA_EF_KEY_SLOT_9_W1                                EF_DATA_EF_KEY_SLOT_9_W1
#define EF_DATA_EF_KEY_SLOT_9_W1_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_9_W1_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_9_W1_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_9_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_9_W1_POS)
#define EF_DATA_EF_KEY_SLOT_9_W1_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_9_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_9_W1_POS))

/* 0xD8 : ef_key_slot_9_w2 */
#define EF_DATA_EF_KEY_SLOT_9_W2_OFFSET                         (0xD8)
#define EF_DATA_EF_KEY_SLOT_9_W2                                EF_DATA_EF_KEY_SLOT_9_W2
#define EF_DATA_EF_KEY_SLOT_9_W2_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_9_W2_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_9_W2_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_9_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_9_W2_POS)
#define EF_DATA_EF_KEY_SLOT_9_W2_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_9_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_9_W2_POS))

/* 0xDC : ef_key_slot_9_w3 */
#define EF_DATA_EF_KEY_SLOT_9_W3_OFFSET                         (0xDC)
#define EF_DATA_EF_KEY_SLOT_9_W3                                EF_DATA_EF_KEY_SLOT_9_W3
#define EF_DATA_EF_KEY_SLOT_9_W3_POS                            (0U)
#define EF_DATA_EF_KEY_SLOT_9_W3_LEN                            (32U)
#define EF_DATA_EF_KEY_SLOT_9_W3_MSK                            (((1U<<EF_DATA_EF_KEY_SLOT_9_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_9_W3_POS)
#define EF_DATA_EF_KEY_SLOT_9_W3_UMSK                           (~(((1U<<EF_DATA_EF_KEY_SLOT_9_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_9_W3_POS))

/* 0xE0 : ef_key_slot_10_w0 */
#define EF_DATA_EF_KEY_SLOT_10_W0_OFFSET                        (0xE0)
#define EF_DATA_EF_KEY_SLOT_10_W0                               EF_DATA_EF_KEY_SLOT_10_W0
#define EF_DATA_EF_KEY_SLOT_10_W0_POS                           (0U)
#define EF_DATA_EF_KEY_SLOT_10_W0_LEN                           (32U)
#define EF_DATA_EF_KEY_SLOT_10_W0_MSK                           (((1U<<EF_DATA_EF_KEY_SLOT_10_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_10_W0_POS)
#define EF_DATA_EF_KEY_SLOT_10_W0_UMSK                          (~(((1U<<EF_DATA_EF_KEY_SLOT_10_W0_LEN)-1)<<EF_DATA_EF_KEY_SLOT_10_W0_POS))

/* 0xE4 : ef_key_slot_10_w1 */
#define EF_DATA_EF_KEY_SLOT_10_W1_OFFSET                        (0xE4)
#define EF_DATA_EF_KEY_SLOT_10_W1                               EF_DATA_EF_KEY_SLOT_10_W1
#define EF_DATA_EF_KEY_SLOT_10_W1_POS                           (0U)
#define EF_DATA_EF_KEY_SLOT_10_W1_LEN                           (32U)
#define EF_DATA_EF_KEY_SLOT_10_W1_MSK                           (((1U<<EF_DATA_EF_KEY_SLOT_10_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_10_W1_POS)
#define EF_DATA_EF_KEY_SLOT_10_W1_UMSK                          (~(((1U<<EF_DATA_EF_KEY_SLOT_10_W1_LEN)-1)<<EF_DATA_EF_KEY_SLOT_10_W1_POS))

/* 0xE8 : ef_key_slot_10_w2 */
#define EF_DATA_EF_KEY_SLOT_10_W2_OFFSET                        (0xE8)
#define EF_DATA_EF_KEY_SLOT_10_W2                               EF_DATA_EF_KEY_SLOT_10_W2
#define EF_DATA_EF_KEY_SLOT_10_W2_POS                           (0U)
#define EF_DATA_EF_KEY_SLOT_10_W2_LEN                           (32U)
#define EF_DATA_EF_KEY_SLOT_10_W2_MSK                           (((1U<<EF_DATA_EF_KEY_SLOT_10_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_10_W2_POS)
#define EF_DATA_EF_KEY_SLOT_10_W2_UMSK                          (~(((1U<<EF_DATA_EF_KEY_SLOT_10_W2_LEN)-1)<<EF_DATA_EF_KEY_SLOT_10_W2_POS))

/* 0xEC : ef_key_slot_10_w3 */
#define EF_DATA_EF_KEY_SLOT_10_W3_OFFSET                        (0xEC)
#define EF_DATA_EF_KEY_SLOT_10_W3                               EF_DATA_EF_KEY_SLOT_10_W3
#define EF_DATA_EF_KEY_SLOT_10_W3_POS                           (0U)
#define EF_DATA_EF_KEY_SLOT_10_W3_LEN                           (32U)
#define EF_DATA_EF_KEY_SLOT_10_W3_MSK                           (((1U<<EF_DATA_EF_KEY_SLOT_10_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_10_W3_POS)
#define EF_DATA_EF_KEY_SLOT_10_W3_UMSK                          (~(((1U<<EF_DATA_EF_KEY_SLOT_10_W3_LEN)-1)<<EF_DATA_EF_KEY_SLOT_10_W3_POS))

/* 0xF0 : ef_dat_1_rsvd_0 */
#define EF_DATA_EF_DAT_1_RSVD_0_OFFSET                          (0xF0)
#define EF_DATA_EF_DAT_1_RSVD_0                                 EF_DATA_EF_DAT_1_RSVD_0
#define EF_DATA_EF_DAT_1_RSVD_0_POS                             (0U)
#define EF_DATA_EF_DAT_1_RSVD_0_LEN                             (32U)
#define EF_DATA_EF_DAT_1_RSVD_0_MSK                             (((1U<<EF_DATA_EF_DAT_1_RSVD_0_LEN)-1)<<EF_DATA_EF_DAT_1_RSVD_0_POS)
#define EF_DATA_EF_DAT_1_RSVD_0_UMSK                            (~(((1U<<EF_DATA_EF_DAT_1_RSVD_0_LEN)-1)<<EF_DATA_EF_DAT_1_RSVD_0_POS))

/* 0xF4 : ef_dat_1_rsvd_1 */
#define EF_DATA_EF_DAT_1_RSVD_1_OFFSET                          (0xF4)
#define EF_DATA_EF_DAT_1_RSVD_1                                 EF_DATA_EF_DAT_1_RSVD_1
#define EF_DATA_EF_DAT_1_RSVD_1_POS                             (0U)
#define EF_DATA_EF_DAT_1_RSVD_1_LEN                             (32U)
#define EF_DATA_EF_DAT_1_RSVD_1_MSK                             (((1U<<EF_DATA_EF_DAT_1_RSVD_1_LEN)-1)<<EF_DATA_EF_DAT_1_RSVD_1_POS)
#define EF_DATA_EF_DAT_1_RSVD_1_UMSK                            (~(((1U<<EF_DATA_EF_DAT_1_RSVD_1_LEN)-1)<<EF_DATA_EF_DAT_1_RSVD_1_POS))

/* 0xF8 : ef_dat_1_rsvd_2 */
#define EF_DATA_EF_DAT_1_RSVD_2_OFFSET                          (0xF8)
#define EF_DATA_EF_DAT_1_RSVD_2                                 EF_DATA_EF_DAT_1_RSVD_2
#define EF_DATA_EF_DAT_1_RSVD_2_POS                             (0U)
#define EF_DATA_EF_DAT_1_RSVD_2_LEN                             (32U)
#define EF_DATA_EF_DAT_1_RSVD_2_MSK                             (((1U<<EF_DATA_EF_DAT_1_RSVD_2_LEN)-1)<<EF_DATA_EF_DAT_1_RSVD_2_POS)
#define EF_DATA_EF_DAT_1_RSVD_2_UMSK                            (~(((1U<<EF_DATA_EF_DAT_1_RSVD_2_LEN)-1)<<EF_DATA_EF_DAT_1_RSVD_2_POS))

/* 0xFC : ef_data_1_lock */
#define EF_DATA_1_LOCK_OFFSET                                   (0xFC)
#define EF_DATA_WR_LOCK_RSVD_1                                  EF_DATA_WR_LOCK_RSVD_1
#define EF_DATA_WR_LOCK_RSVD_1_POS                              (0U)
#define EF_DATA_WR_LOCK_RSVD_1_LEN                              (15U)
#define EF_DATA_WR_LOCK_RSVD_1_MSK                              (((1U<<EF_DATA_WR_LOCK_RSVD_1_LEN)-1)<<EF_DATA_WR_LOCK_RSVD_1_POS)
#define EF_DATA_WR_LOCK_RSVD_1_UMSK                             (~(((1U<<EF_DATA_WR_LOCK_RSVD_1_LEN)-1)<<EF_DATA_WR_LOCK_RSVD_1_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_4                              EF_DATA_WR_LOCK_KEY_SLOT_4
#define EF_DATA_WR_LOCK_KEY_SLOT_4_POS                          (15U)
#define EF_DATA_WR_LOCK_KEY_SLOT_4_LEN                          (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_4_MSK                          (((1U<<EF_DATA_WR_LOCK_KEY_SLOT_4_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_4_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_4_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_KEY_SLOT_4_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_4_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_5                              EF_DATA_WR_LOCK_KEY_SLOT_5
#define EF_DATA_WR_LOCK_KEY_SLOT_5_POS                          (16U)
#define EF_DATA_WR_LOCK_KEY_SLOT_5_LEN                          (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_5_MSK                          (((1U<<EF_DATA_WR_LOCK_KEY_SLOT_5_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_5_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_5_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_KEY_SLOT_5_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_5_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_6                              EF_DATA_WR_LOCK_KEY_SLOT_6
#define EF_DATA_WR_LOCK_KEY_SLOT_6_POS                          (17U)
#define EF_DATA_WR_LOCK_KEY_SLOT_6_LEN                          (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_6_MSK                          (((1U<<EF_DATA_WR_LOCK_KEY_SLOT_6_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_6_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_6_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_KEY_SLOT_6_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_6_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_7                              EF_DATA_WR_LOCK_KEY_SLOT_7
#define EF_DATA_WR_LOCK_KEY_SLOT_7_POS                          (18U)
#define EF_DATA_WR_LOCK_KEY_SLOT_7_LEN                          (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_7_MSK                          (((1U<<EF_DATA_WR_LOCK_KEY_SLOT_7_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_7_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_7_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_KEY_SLOT_7_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_7_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_8                              EF_DATA_WR_LOCK_KEY_SLOT_8
#define EF_DATA_WR_LOCK_KEY_SLOT_8_POS                          (19U)
#define EF_DATA_WR_LOCK_KEY_SLOT_8_LEN                          (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_8_MSK                          (((1U<<EF_DATA_WR_LOCK_KEY_SLOT_8_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_8_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_8_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_KEY_SLOT_8_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_8_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_9                              EF_DATA_WR_LOCK_KEY_SLOT_9
#define EF_DATA_WR_LOCK_KEY_SLOT_9_POS                          (20U)
#define EF_DATA_WR_LOCK_KEY_SLOT_9_LEN                          (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_9_MSK                          (((1U<<EF_DATA_WR_LOCK_KEY_SLOT_9_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_9_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_9_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_KEY_SLOT_9_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_9_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_10                             EF_DATA_WR_LOCK_KEY_SLOT_10
#define EF_DATA_WR_LOCK_KEY_SLOT_10_POS                         (21U)
#define EF_DATA_WR_LOCK_KEY_SLOT_10_LEN                         (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_10_MSK                         (((1U<<EF_DATA_WR_LOCK_KEY_SLOT_10_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_10_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_10_UMSK                        (~(((1U<<EF_DATA_WR_LOCK_KEY_SLOT_10_LEN)-1)<<EF_DATA_WR_LOCK_KEY_SLOT_10_POS))
#define EF_DATA_WR_LOCK_DAT_1_RSVD_0                            EF_DATA_WR_LOCK_DAT_1_RSVD_0
#define EF_DATA_WR_LOCK_DAT_1_RSVD_0_POS                        (22U)
#define EF_DATA_WR_LOCK_DAT_1_RSVD_0_LEN                        (1U)
#define EF_DATA_WR_LOCK_DAT_1_RSVD_0_MSK                        (((1U<<EF_DATA_WR_LOCK_DAT_1_RSVD_0_LEN)-1)<<EF_DATA_WR_LOCK_DAT_1_RSVD_0_POS)
#define EF_DATA_WR_LOCK_DAT_1_RSVD_0_UMSK                       (~(((1U<<EF_DATA_WR_LOCK_DAT_1_RSVD_0_LEN)-1)<<EF_DATA_WR_LOCK_DAT_1_RSVD_0_POS))
#define EF_DATA_WR_LOCK_DAT_1_RSVD_1                            EF_DATA_WR_LOCK_DAT_1_RSVD_1
#define EF_DATA_WR_LOCK_DAT_1_RSVD_1_POS                        (23U)
#define EF_DATA_WR_LOCK_DAT_1_RSVD_1_LEN                        (1U)
#define EF_DATA_WR_LOCK_DAT_1_RSVD_1_MSK                        (((1U<<EF_DATA_WR_LOCK_DAT_1_RSVD_1_LEN)-1)<<EF_DATA_WR_LOCK_DAT_1_RSVD_1_POS)
#define EF_DATA_WR_LOCK_DAT_1_RSVD_1_UMSK                       (~(((1U<<EF_DATA_WR_LOCK_DAT_1_RSVD_1_LEN)-1)<<EF_DATA_WR_LOCK_DAT_1_RSVD_1_POS))
#define EF_DATA_WR_LOCK_DAT_1_RSVD_2                            EF_DATA_WR_LOCK_DAT_1_RSVD_2
#define EF_DATA_WR_LOCK_DAT_1_RSVD_2_POS                        (24U)
#define EF_DATA_WR_LOCK_DAT_1_RSVD_2_LEN                        (1U)
#define EF_DATA_WR_LOCK_DAT_1_RSVD_2_MSK                        (((1U<<EF_DATA_WR_LOCK_DAT_1_RSVD_2_LEN)-1)<<EF_DATA_WR_LOCK_DAT_1_RSVD_2_POS)
#define EF_DATA_WR_LOCK_DAT_1_RSVD_2_UMSK                       (~(((1U<<EF_DATA_WR_LOCK_DAT_1_RSVD_2_LEN)-1)<<EF_DATA_WR_LOCK_DAT_1_RSVD_2_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_4                              EF_DATA_RD_LOCK_KEY_SLOT_4
#define EF_DATA_RD_LOCK_KEY_SLOT_4_POS                          (25U)
#define EF_DATA_RD_LOCK_KEY_SLOT_4_LEN                          (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_4_MSK                          (((1U<<EF_DATA_RD_LOCK_KEY_SLOT_4_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_4_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_4_UMSK                         (~(((1U<<EF_DATA_RD_LOCK_KEY_SLOT_4_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_4_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_5                              EF_DATA_RD_LOCK_KEY_SLOT_5
#define EF_DATA_RD_LOCK_KEY_SLOT_5_POS                          (26U)
#define EF_DATA_RD_LOCK_KEY_SLOT_5_LEN                          (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_5_MSK                          (((1U<<EF_DATA_RD_LOCK_KEY_SLOT_5_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_5_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_5_UMSK                         (~(((1U<<EF_DATA_RD_LOCK_KEY_SLOT_5_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_5_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_6                              EF_DATA_RD_LOCK_KEY_SLOT_6
#define EF_DATA_RD_LOCK_KEY_SLOT_6_POS                          (27U)
#define EF_DATA_RD_LOCK_KEY_SLOT_6_LEN                          (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_6_MSK                          (((1U<<EF_DATA_RD_LOCK_KEY_SLOT_6_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_6_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_6_UMSK                         (~(((1U<<EF_DATA_RD_LOCK_KEY_SLOT_6_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_6_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_7                              EF_DATA_RD_LOCK_KEY_SLOT_7
#define EF_DATA_RD_LOCK_KEY_SLOT_7_POS                          (28U)
#define EF_DATA_RD_LOCK_KEY_SLOT_7_LEN                          (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_7_MSK                          (((1U<<EF_DATA_RD_LOCK_KEY_SLOT_7_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_7_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_7_UMSK                         (~(((1U<<EF_DATA_RD_LOCK_KEY_SLOT_7_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_7_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_8                              EF_DATA_RD_LOCK_KEY_SLOT_8
#define EF_DATA_RD_LOCK_KEY_SLOT_8_POS                          (29U)
#define EF_DATA_RD_LOCK_KEY_SLOT_8_LEN                          (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_8_MSK                          (((1U<<EF_DATA_RD_LOCK_KEY_SLOT_8_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_8_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_8_UMSK                         (~(((1U<<EF_DATA_RD_LOCK_KEY_SLOT_8_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_8_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_9                              EF_DATA_RD_LOCK_KEY_SLOT_9
#define EF_DATA_RD_LOCK_KEY_SLOT_9_POS                          (30U)
#define EF_DATA_RD_LOCK_KEY_SLOT_9_LEN                          (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_9_MSK                          (((1U<<EF_DATA_RD_LOCK_KEY_SLOT_9_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_9_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_9_UMSK                         (~(((1U<<EF_DATA_RD_LOCK_KEY_SLOT_9_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_9_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_10                             EF_DATA_RD_LOCK_KEY_SLOT_10
#define EF_DATA_RD_LOCK_KEY_SLOT_10_POS                         (31U)
#define EF_DATA_RD_LOCK_KEY_SLOT_10_LEN                         (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_10_MSK                         (((1U<<EF_DATA_RD_LOCK_KEY_SLOT_10_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_10_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_10_UMSK                        (~(((1U<<EF_DATA_RD_LOCK_KEY_SLOT_10_LEN)-1)<<EF_DATA_RD_LOCK_KEY_SLOT_10_POS))

/* 0x100 : ef_zone_00_w0 */
#define EF_DATA_EF_ZONE_00_W0_OFFSET                            (0x100)

/* 0x104 : ef_zone_00_w1 */
#define EF_DATA_EF_ZONE_00_W1_OFFSET                            (0x104)

/* 0x108 : ef_zone_00_w2 */
#define EF_DATA_EF_ZONE_00_W2_OFFSET                            (0x108)

/* 0x10C : ef_zone_00_w3 */
#define EF_DATA_EF_ZONE_00_W3_OFFSET                            (0x10C)

/* 0x110 : ef_zone_01_w0 */
#define EF_DATA_EF_ZONE_01_W0_OFFSET                            (0x110)

/* 0x114 : ef_zone_01_w1 */
#define EF_DATA_EF_ZONE_01_W1_OFFSET                            (0x114)

/* 0x118 : ef_zone_01_w2 */
#define EF_DATA_EF_ZONE_01_W2_OFFSET                            (0x118)

/* 0x11C : ef_zone_01_w3 */
#define EF_DATA_EF_ZONE_01_W3_OFFSET                            (0x11C)

/* 0x120 : ef_zone_02_w0 */
#define EF_DATA_EF_ZONE_02_W0_OFFSET                            (0x120)

/* 0x124 : ef_zone_02_w1 */
#define EF_DATA_EF_ZONE_02_W1_OFFSET                            (0x124)

/* 0x128 : ef_zone_02_w2 */
#define EF_DATA_EF_ZONE_02_W2_OFFSET                            (0x128)

/* 0x12C : ef_zone_02_w3 */
#define EF_DATA_EF_ZONE_02_W3_OFFSET                            (0x12C)

/* 0x130 : ef_zone_03_w0 */
#define EF_DATA_EF_ZONE_03_W0_OFFSET                            (0x130)

/* 0x134 : ef_zone_03_w1 */
#define EF_DATA_EF_ZONE_03_W1_OFFSET                            (0x134)

/* 0x138 : ef_zone_03_w2 */
#define EF_DATA_EF_ZONE_03_W2_OFFSET                            (0x138)

/* 0x13C : ef_zone_03_w3 */
#define EF_DATA_EF_ZONE_03_W3_OFFSET                            (0x13C)

/* 0x140 : ef_zone_04_w0 */
#define EF_DATA_EF_ZONE_04_W0_OFFSET                            (0x140)

/* 0x144 : ef_zone_04_w1 */
#define EF_DATA_EF_ZONE_04_W1_OFFSET                            (0x144)

/* 0x148 : ef_zone_04_w2 */
#define EF_DATA_EF_ZONE_04_W2_OFFSET                            (0x148)

/* 0x14C : ef_zone_04_w3 */
#define EF_DATA_EF_ZONE_04_W3_OFFSET                            (0x14C)

/* 0x150 : ef_zone_05_w0 */
#define EF_DATA_EF_ZONE_05_W0_OFFSET                            (0x150)

/* 0x154 : ef_zone_05_w1 */
#define EF_DATA_EF_ZONE_05_W1_OFFSET                            (0x154)

/* 0x158 : ef_zone_05_w2 */
#define EF_DATA_EF_ZONE_05_W2_OFFSET                            (0x158)

/* 0x15C : ef_zone_05_w3 */
#define EF_DATA_EF_ZONE_05_W3_OFFSET                            (0x15C)

/* 0x160 : ef_zone_06_w0 */
#define EF_DATA_EF_ZONE_06_W0_OFFSET                            (0x160)

/* 0x164 : ef_zone_06_w1 */
#define EF_DATA_EF_ZONE_06_W1_OFFSET                            (0x164)

/* 0x168 : ef_zone_06_w2 */
#define EF_DATA_EF_ZONE_06_W2_OFFSET                            (0x168)

/* 0x16C : ef_zone_06_w3 */
#define EF_DATA_EF_ZONE_06_W3_OFFSET                            (0x16C)

/* 0x170 : ef_zone_07_w0 */
#define EF_DATA_EF_ZONE_07_W0_OFFSET                            (0x170)

/* 0x174 : ef_zone_07_w1 */
#define EF_DATA_EF_ZONE_07_W1_OFFSET                            (0x174)

/* 0x178 : ef_zone_07_w2 */
#define EF_DATA_EF_ZONE_07_W2_OFFSET                            (0x178)

/* 0x17C : ef_zone_07_w3 */
#define EF_DATA_EF_ZONE_07_W3_OFFSET                            (0x17C)

/* 0x180 : ef_zone_08_w0 */
#define EF_DATA_EF_ZONE_08_W0_OFFSET                            (0x180)

/* 0x184 : ef_zone_08_w1 */
#define EF_DATA_EF_ZONE_08_W1_OFFSET                            (0x184)

/* 0x188 : ef_zone_08_w2 */
#define EF_DATA_EF_ZONE_08_W2_OFFSET                            (0x188)

/* 0x18C : ef_zone_08_w3 */
#define EF_DATA_EF_ZONE_08_W3_OFFSET                            (0x18C)

/* 0x190 : ef_zone_09_w0 */
#define EF_DATA_EF_ZONE_09_W0_OFFSET                            (0x190)

/* 0x194 : ef_zone_09_w1 */
#define EF_DATA_EF_ZONE_09_W1_OFFSET                            (0x194)

/* 0x198 : ef_zone_09_w2 */
#define EF_DATA_EF_ZONE_09_W2_OFFSET                            (0x198)

/* 0x19C : ef_zone_09_w3 */
#define EF_DATA_EF_ZONE_09_W3_OFFSET                            (0x19C)

/* 0x1A0 : ef_zone_10_w0 */
#define EF_DATA_EF_ZONE_10_W0_OFFSET                            (0x1A0)

/* 0x1A4 : ef_zone_10_w1 */
#define EF_DATA_EF_ZONE_10_W1_OFFSET                            (0x1A4)

/* 0x1A8 : ef_zone_10_w2 */
#define EF_DATA_EF_ZONE_10_W2_OFFSET                            (0x1A8)

/* 0x1AC : ef_zone_10_w3 */
#define EF_DATA_EF_ZONE_10_W3_OFFSET                            (0x1AC)

/* 0x1B0 : ef_zone_11_w0 */
#define EF_DATA_EF_ZONE_11_W0_OFFSET                            (0x1B0)

/* 0x1B4 : ef_zone_11_w1 */
#define EF_DATA_EF_ZONE_11_W1_OFFSET                            (0x1B4)

/* 0x1B8 : ef_zone_11_w2 */
#define EF_DATA_EF_ZONE_11_W2_OFFSET                            (0x1B8)

/* 0x1BC : ef_zone_11_w3 */
#define EF_DATA_EF_ZONE_11_W3_OFFSET                            (0x1BC)

/* 0x1C0 : ef_zone_12_w0 */
#define EF_DATA_EF_ZONE_12_W0_OFFSET                            (0x1C0)

/* 0x1C4 : ef_zone_12_w1 */
#define EF_DATA_EF_ZONE_12_W1_OFFSET                            (0x1C4)

/* 0x1C8 : ef_zone_12_w2 */
#define EF_DATA_EF_ZONE_12_W2_OFFSET                            (0x1C8)

/* 0x1CC : ef_zone_12_w3 */
#define EF_DATA_EF_ZONE_12_W3_OFFSET                            (0x1CC)

/* 0x1D0 : ef_zone_13_w0 */
#define EF_DATA_EF_ZONE_13_W0_OFFSET                            (0x1D0)

/* 0x1D4 : ef_zone_13_w1 */
#define EF_DATA_EF_ZONE_13_W1_OFFSET                            (0x1D4)

/* 0x1D8 : ef_zone_13_w2 */
#define EF_DATA_EF_ZONE_13_W2_OFFSET                            (0x1D8)

/* 0x1DC : ef_zone_13_w3 */
#define EF_DATA_EF_ZONE_13_W3_OFFSET                            (0x1DC)

/* 0x1E0 : ef_zone_14_w0 */
#define EF_DATA_EF_ZONE_14_W0_OFFSET                            (0x1E0)

/* 0x1E4 : ef_zone_14_w1 */
#define EF_DATA_EF_ZONE_14_W1_OFFSET                            (0x1E4)

/* 0x1E8 : ef_zone_14_w2 */
#define EF_DATA_EF_ZONE_14_W2_OFFSET                            (0x1E8)

/* 0x1EC : ef_zone_14_w3 */
#define EF_DATA_EF_ZONE_14_W3_OFFSET                            (0x1EC)

/* 0x1F0 : ef_zone_15_w0 */
#define EF_DATA_EF_ZONE_15_W0_OFFSET                            (0x1F0)

/* 0x1F4 : ef_zone_15_w1 */
#define EF_DATA_EF_ZONE_15_W1_OFFSET                            (0x1F4)

/* 0x1F8 : ef_zone_15_w2 */
#define EF_DATA_EF_ZONE_15_W2_OFFSET                            (0x1F8)

/* 0x1FC : ef_zone_15_w3 */
#define EF_DATA_EF_ZONE_15_W3_OFFSET                            (0x1FC)
#define EF_DATA_EF_ZONE_15_W3                                   EF_DATA_EF_ZONE_15_W3
#define EF_DATA_EF_ZONE_15_W3_POS                               (0U)
#define EF_DATA_EF_ZONE_15_W3_LEN                               (16U)
#define EF_DATA_EF_ZONE_15_W3_MSK                               (((1U<<EF_DATA_EF_ZONE_15_W3_LEN)-1)<<EF_DATA_EF_ZONE_15_W3_POS)
#define EF_DATA_EF_ZONE_15_W3_UMSK                              (~(((1U<<EF_DATA_EF_ZONE_15_W3_LEN)-1)<<EF_DATA_EF_ZONE_15_W3_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_00                              EF_DATA_WR_LOCK_EF_ZONE_00
#define EF_DATA_WR_LOCK_EF_ZONE_00_POS                          (16U)
#define EF_DATA_WR_LOCK_EF_ZONE_00_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_00_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_00_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_00_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_00_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_00_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_00_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_01                              EF_DATA_WR_LOCK_EF_ZONE_01
#define EF_DATA_WR_LOCK_EF_ZONE_01_POS                          (17U)
#define EF_DATA_WR_LOCK_EF_ZONE_01_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_01_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_01_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_01_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_01_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_01_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_01_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_02                              EF_DATA_WR_LOCK_EF_ZONE_02
#define EF_DATA_WR_LOCK_EF_ZONE_02_POS                          (18U)
#define EF_DATA_WR_LOCK_EF_ZONE_02_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_02_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_02_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_02_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_02_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_02_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_02_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_03                              EF_DATA_WR_LOCK_EF_ZONE_03
#define EF_DATA_WR_LOCK_EF_ZONE_03_POS                          (19U)
#define EF_DATA_WR_LOCK_EF_ZONE_03_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_03_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_03_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_03_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_03_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_03_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_03_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_04                              EF_DATA_WR_LOCK_EF_ZONE_04
#define EF_DATA_WR_LOCK_EF_ZONE_04_POS                          (20U)
#define EF_DATA_WR_LOCK_EF_ZONE_04_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_04_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_04_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_04_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_04_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_04_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_04_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_05                              EF_DATA_WR_LOCK_EF_ZONE_05
#define EF_DATA_WR_LOCK_EF_ZONE_05_POS                          (21U)
#define EF_DATA_WR_LOCK_EF_ZONE_05_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_05_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_05_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_05_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_05_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_05_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_05_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_06                              EF_DATA_WR_LOCK_EF_ZONE_06
#define EF_DATA_WR_LOCK_EF_ZONE_06_POS                          (22U)
#define EF_DATA_WR_LOCK_EF_ZONE_06_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_06_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_06_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_06_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_06_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_06_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_06_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_07                              EF_DATA_WR_LOCK_EF_ZONE_07
#define EF_DATA_WR_LOCK_EF_ZONE_07_POS                          (23U)
#define EF_DATA_WR_LOCK_EF_ZONE_07_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_07_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_07_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_07_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_07_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_07_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_07_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_08                              EF_DATA_WR_LOCK_EF_ZONE_08
#define EF_DATA_WR_LOCK_EF_ZONE_08_POS                          (24U)
#define EF_DATA_WR_LOCK_EF_ZONE_08_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_08_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_08_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_08_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_08_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_08_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_08_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_09                              EF_DATA_WR_LOCK_EF_ZONE_09
#define EF_DATA_WR_LOCK_EF_ZONE_09_POS                          (25U)
#define EF_DATA_WR_LOCK_EF_ZONE_09_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_09_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_09_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_09_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_09_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_09_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_09_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_10                              EF_DATA_WR_LOCK_EF_ZONE_10
#define EF_DATA_WR_LOCK_EF_ZONE_10_POS                          (26U)
#define EF_DATA_WR_LOCK_EF_ZONE_10_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_10_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_10_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_10_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_10_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_10_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_10_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_11                              EF_DATA_WR_LOCK_EF_ZONE_11
#define EF_DATA_WR_LOCK_EF_ZONE_11_POS                          (27U)
#define EF_DATA_WR_LOCK_EF_ZONE_11_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_11_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_11_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_11_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_11_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_11_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_11_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_12                              EF_DATA_WR_LOCK_EF_ZONE_12
#define EF_DATA_WR_LOCK_EF_ZONE_12_POS                          (28U)
#define EF_DATA_WR_LOCK_EF_ZONE_12_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_12_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_12_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_12_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_12_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_12_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_12_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_13                              EF_DATA_WR_LOCK_EF_ZONE_13
#define EF_DATA_WR_LOCK_EF_ZONE_13_POS                          (29U)
#define EF_DATA_WR_LOCK_EF_ZONE_13_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_13_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_13_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_13_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_13_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_13_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_13_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_14                              EF_DATA_WR_LOCK_EF_ZONE_14
#define EF_DATA_WR_LOCK_EF_ZONE_14_POS                          (30U)
#define EF_DATA_WR_LOCK_EF_ZONE_14_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_14_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_14_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_14_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_14_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_14_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_14_POS))
#define EF_DATA_WR_LOCK_EF_ZONE_15                              EF_DATA_WR_LOCK_EF_ZONE_15
#define EF_DATA_WR_LOCK_EF_ZONE_15_POS                          (31U)
#define EF_DATA_WR_LOCK_EF_ZONE_15_LEN                          (1U)
#define EF_DATA_WR_LOCK_EF_ZONE_15_MSK                          (((1U<<EF_DATA_WR_LOCK_EF_ZONE_15_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_15_POS)
#define EF_DATA_WR_LOCK_EF_ZONE_15_UMSK                         (~(((1U<<EF_DATA_WR_LOCK_EF_ZONE_15_LEN)-1)<<EF_DATA_WR_LOCK_EF_ZONE_15_POS))


struct  ef_data_reg {
    /* 0x0 : ef_cfg_0 */
    union {
        struct {
            uint32_t ef_sf_aes_mode                 :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t ef_ai_dis                      :  1; /* [    2],        r/w,        0x0 */
            uint32_t ef_cpu0_dis                    :  1; /* [    3],        r/w,        0x0 */
            uint32_t ef_sboot_en                    :  2; /* [ 5: 4],        r/w,        0x0 */
            uint32_t ef_uart_dis                    :  4; /* [ 9: 6],        r/w,        0x0 */
            uint32_t ef_bus_rmp_sw_en               :  1; /* [   10],        r/w,        0x0 */
            uint32_t ef_bus_rmp_dis                 :  1; /* [   11],        r/w,        0x0 */
            uint32_t ef_sf_key_re_sel               :  2; /* [13:12],        r/w,        0x0 */
            uint32_t ef_sdu_dis                     :  1; /* [   14],        r/w,        0x0 */
            uint32_t ef_btdm_dis                    :  1; /* [   15],        r/w,        0x0 */
            uint32_t ef_wifi_dis                    :  1; /* [   16],        r/w,        0x0 */
            uint32_t ef_0_key_enc_en                :  1; /* [   17],        r/w,        0x0 */
            uint32_t ef_cam_dis                     :  1; /* [   18],        r/w,        0x0 */
            uint32_t ef_m154_dis                    :  1; /* [   19],        r/w,        0x0 */
            uint32_t ef_sdu_rst_opt                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t ef_cpu_rst_dbg_dis             :  1; /* [   21],        r/w,        0x0 */
            uint32_t ef_se_dbg_dis                  :  1; /* [   22],        r/w,        0x0 */
            uint32_t ef_efuse_dbg_dis               :  1; /* [   23],        r/w,        0x0 */
            uint32_t ef_dbg_jtag_1_dis              :  2; /* [25:24],        r/w,        0x0 */
            uint32_t ef_dbg_jtag_0_dis              :  2; /* [27:26],        r/w,        0x0 */
            uint32_t ef_dbg_mode                    :  4; /* [31:28],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_cfg_0;

    /* 0x4 : ef_dbg_pwd_low */
    union {
        struct {
            uint32_t ef_dbg_pwd_low                 : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_dbg_pwd_low;

    /* 0x8 : ef_dbg_pwd_high */
    union {
        struct {
            uint32_t ef_dbg_pwd_high                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_dbg_pwd_high;

    /* 0xC : ef_dbg_pwd2_low */
    union {
        struct {
            uint32_t ef_dbg_pwd2_low                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_dbg_pwd2_low;

    /* 0x10 : ef_dbg_pwd2_high */
    union {
        struct {
            uint32_t ef_dbg_pwd2_high               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_dbg_pwd2_high;

    /* 0x14 : ef_wifi_mac_low */
    union {
        struct {
            uint32_t ef_wifi_mac_low                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_wifi_mac_low;

    /* 0x18 : ef_wifi_mac_high */
    union {
        struct {
            uint32_t ef_wifi_mac_high               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_wifi_mac_high;

    /* 0x1C : ef_key_slot_0_w0 */
    union {
        struct {
            uint32_t ef_key_slot_0_w0               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_0_w0;

    /* 0x20 : ef_key_slot_0_w1 */
    union {
        struct {
            uint32_t ef_key_slot_0_w1               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_0_w1;

    /* 0x24 : ef_key_slot_0_w2 */
    union {
        struct {
            uint32_t ef_key_slot_0_w2               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_0_w2;

    /* 0x28 : ef_key_slot_0_w3 */
    union {
        struct {
            uint32_t ef_key_slot_0_w3               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_0_w3;

    /* 0x2C : ef_key_slot_1_w0 */
    union {
        struct {
            uint32_t ef_key_slot_1_w0               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_1_w0;

    /* 0x30 : ef_key_slot_1_w1 */
    union {
        struct {
            uint32_t ef_key_slot_1_w1               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_1_w1;

    /* 0x34 : ef_key_slot_1_w2 */
    union {
        struct {
            uint32_t ef_key_slot_1_w2               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_1_w2;

    /* 0x38 : ef_key_slot_1_w3 */
    union {
        struct {
            uint32_t ef_key_slot_1_w3               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_1_w3;

    /* 0x3C : ef_key_slot_2_w0 */
    union {
        struct {
            uint32_t ef_key_slot_2_w0               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_2_w0;

    /* 0x40 : ef_key_slot_2_w1 */
    union {
        struct {
            uint32_t ef_key_slot_2_w1               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_2_w1;

    /* 0x44 : ef_key_slot_2_w2 */
    union {
        struct {
            uint32_t ef_key_slot_2_w2               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_2_w2;

    /* 0x48 : ef_key_slot_2_w3 */
    union {
        struct {
            uint32_t ef_key_slot_2_w3               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_2_w3;

    /* 0x4C : ef_key_slot_3_w0 */
    union {
        struct {
            uint32_t ef_key_slot_3_w0               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_3_w0;

    /* 0x50 : ef_key_slot_3_w1 */
    union {
        struct {
            uint32_t ef_key_slot_3_w1               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_3_w1;

    /* 0x54 : ef_key_slot_3_w2 */
    union {
        struct {
            uint32_t ef_key_slot_3_w2               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_3_w2;

    /* 0x58 : ef_key_slot_3_w3 */
    union {
        struct {
            uint32_t ef_key_slot_3_w3               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_3_w3;

    /* 0x5C : ef_sw_usage_0 */
    union {
        struct {
            uint32_t ef_sw_usage_0                  : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_sw_usage_0;

    /* 0x60 : ef_sw_usage_1 */
    union {
        struct {
            uint32_t ef_sw_usage_1                  : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_sw_usage_1;

    /* 0x64 : ef_sw_usage_2 */
    union {
        struct {
            uint32_t ef_sw_usage_2                  : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_sw_usage_2;

    /* 0x68 : ef_sw_usage_3 */
    union {
        struct {
            uint32_t ef_sw_usage_3                  : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_sw_usage_3;

    /* 0x6C : ef_key_slot_11_w0 */
    union {
        struct {
            uint32_t ef_key_slot_11_w0              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_11_w0;

    /* 0x70 : ef_key_slot_11_w1 */
    union {
        struct {
            uint32_t ef_key_slot_11_w1              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_11_w1;

    /* 0x74 : ef_key_slot_11_w2 */
    union {
        struct {
            uint32_t ef_key_slot_11_w2              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_11_w2;

    /* 0x78 : ef_key_slot_11_w3 */
    union {
        struct {
            uint32_t ef_key_slot_11_w3              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_11_w3;

    /* 0x7C : ef_data_0_lock */
    union {
        struct {
            uint32_t ef_sec_lifecycle               :  4; /* [ 3: 0],        r/w,        0x0 */
            uint32_t wr_lock_rsvd_0                 :  9; /* [12: 4],        r/w,        0x0 */
            uint32_t flash_dly_coe                  :  1; /* [   13],        r/w,        0x0 */
            uint32_t wr_lock_boot_mode              :  1; /* [   14],        r/w,        0x0 */
            uint32_t wr_lock_dbg_pwd                :  1; /* [   15],        r/w,        0x0 */
            uint32_t wr_lock_wifi_mac               :  1; /* [   16],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_0             :  1; /* [   17],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_1             :  1; /* [   18],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_2             :  1; /* [   19],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_3             :  1; /* [   20],        r/w,        0x0 */
            uint32_t wr_lock_sw_usage_0             :  1; /* [   21],        r/w,        0x0 */
            uint32_t wr_lock_sw_usage_1             :  1; /* [   22],        r/w,        0x0 */
            uint32_t wr_lock_sw_usage_2             :  1; /* [   23],        r/w,        0x0 */
            uint32_t wr_lock_sw_usage_3             :  1; /* [   24],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_11            :  1; /* [   25],        r/w,        0x0 */
            uint32_t rd_lock_dbg_pwd                :  1; /* [   26],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_0             :  1; /* [   27],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_1             :  1; /* [   28],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_2             :  1; /* [   29],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_3             :  1; /* [   30],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_11            :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_data_0_lock;

    /* 0x80 : ef_key_slot_4_w0 */
    union {
        struct {
            uint32_t ef_key_slot_4_w0               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_4_w0;

    /* 0x84 : ef_key_slot_4_w1 */
    union {
        struct {
            uint32_t ef_key_slot_4_w1               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_4_w1;

    /* 0x88 : ef_key_slot_4_w2 */
    union {
        struct {
            uint32_t ef_key_slot_4_w2               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_4_w2;

    /* 0x8C : ef_key_slot_4_w3 */
    union {
        struct {
            uint32_t ef_key_slot_4_w3               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_4_w3;

    /* 0x90 : ef_key_slot_5_w0 */
    union {
        struct {
            uint32_t ef_key_slot_5_w0               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_5_w0;

    /* 0x94 : ef_key_slot_5_w1 */
    union {
        struct {
            uint32_t ef_key_slot_5_w1               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_5_w1;

    /* 0x98 : ef_key_slot_5_w2 */
    union {
        struct {
            uint32_t ef_key_slot_5_w2               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_5_w2;

    /* 0x9C : ef_key_slot_5_w3 */
    union {
        struct {
            uint32_t ef_key_slot_5_w3               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_5_w3;

    /* 0xA0 : ef_key_slot_6_w0 */
    union {
        struct {
            uint32_t ef_key_slot_6_w0               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_6_w0;

    /* 0xA4 : ef_key_slot_6_w1 */
    union {
        struct {
            uint32_t ef_key_slot_6_w1               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_6_w1;

    /* 0xA8 : ef_key_slot_6_w2 */
    union {
        struct {
            uint32_t ef_key_slot_6_w2               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_6_w2;

    /* 0xAC : ef_key_slot_6_w3 */
    union {
        struct {
            uint32_t ef_key_slot_6_w3               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_6_w3;

    /* 0xB0 : ef_key_slot_7_w0 */
    union {
        struct {
            uint32_t ef_key_slot_7_w0               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_7_w0;

    /* 0xB4 : ef_key_slot_7_w1 */
    union {
        struct {
            uint32_t ef_key_slot_7_w1               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_7_w1;

    /* 0xB8 : ef_key_slot_7_w2 */
    union {
        struct {
            uint32_t ef_key_slot_7_w2               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_7_w2;

    /* 0xBC : ef_key_slot_7_w3 */
    union {
        struct {
            uint32_t ef_key_slot_7_w3               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_7_w3;

    /* 0xC0 : ef_key_slot_8_w0 */
    union {
        struct {
            uint32_t ef_key_slot_8_w0               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_8_w0;

    /* 0xC4 : ef_key_slot_8_w1 */
    union {
        struct {
            uint32_t ef_key_slot_8_w1               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_8_w1;

    /* 0xC8 : ef_key_slot_8_w2 */
    union {
        struct {
            uint32_t ef_key_slot_8_w2               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_8_w2;

    /* 0xCC : ef_key_slot_8_w3 */
    union {
        struct {
            uint32_t ef_key_slot_8_w3               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_8_w3;

    /* 0xD0 : ef_key_slot_9_w0 */
    union {
        struct {
            uint32_t ef_key_slot_9_w0               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_9_w0;

    /* 0xD4 : ef_key_slot_9_w1 */
    union {
        struct {
            uint32_t ef_key_slot_9_w1               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_9_w1;

    /* 0xD8 : ef_key_slot_9_w2 */
    union {
        struct {
            uint32_t ef_key_slot_9_w2               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_9_w2;

    /* 0xDC : ef_key_slot_9_w3 */
    union {
        struct {
            uint32_t ef_key_slot_9_w3               : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_9_w3;

    /* 0xE0 : ef_key_slot_10_w0 */
    union {
        struct {
            uint32_t ef_key_slot_10_w0              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_10_w0;

    /* 0xE4 : ef_key_slot_10_w1 */
    union {
        struct {
            uint32_t ef_key_slot_10_w1              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_10_w1;

    /* 0xE8 : ef_key_slot_10_w2 */
    union {
        struct {
            uint32_t ef_key_slot_10_w2              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_10_w2;

    /* 0xEC : ef_key_slot_10_w3 */
    union {
        struct {
            uint32_t ef_key_slot_10_w3              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_key_slot_10_w3;

    /* 0xF0 : ef_dat_1_rsvd_0 */
    union {
        struct {
            uint32_t ef_dat_1_rsvd_0                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_dat_1_rsvd_0;

    /* 0xF4 : ef_dat_1_rsvd_1 */
    union {
        struct {
            uint32_t ef_dat_1_rsvd_1                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_dat_1_rsvd_1;

    /* 0xF8 : ef_dat_1_rsvd_2 */
    union {
        struct {
            uint32_t ef_dat_1_rsvd_2                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_dat_1_rsvd_2;

    /* 0xFC : ef_data_1_lock */
    union {
        struct {
            uint32_t wr_lock_rsvd_1                 : 15; /* [14: 0],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_4             :  1; /* [   15],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_5             :  1; /* [   16],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_6             :  1; /* [   17],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_7             :  1; /* [   18],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_8             :  1; /* [   19],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_9             :  1; /* [   20],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_10            :  1; /* [   21],        r/w,        0x0 */
            uint32_t wr_lock_dat_1_rsvd_0           :  1; /* [   22],        r/w,        0x0 */
            uint32_t wr_lock_dat_1_rsvd_1           :  1; /* [   23],        r/w,        0x0 */
            uint32_t wr_lock_dat_1_rsvd_2           :  1; /* [   24],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_4             :  1; /* [   25],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_5             :  1; /* [   26],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_6             :  1; /* [   27],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_7             :  1; /* [   28],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_8             :  1; /* [   29],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_9             :  1; /* [   30],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_10            :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_data_1_lock;

    /* 0x100 : ef_zone_00_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_00_w0;

    /* 0x104 : ef_zone_00_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_00_w1;

    /* 0x108 : ef_zone_00_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_00_w2;

    /* 0x10C : ef_zone_00_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_00_w3;

    /* 0x110 : ef_zone_01_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_01_w0;

    /* 0x114 : ef_zone_01_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_01_w1;

    /* 0x118 : ef_zone_01_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_01_w2;

    /* 0x11C : ef_zone_01_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_01_w3;

    /* 0x120 : ef_zone_02_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_02_w0;

    /* 0x124 : ef_zone_02_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_02_w1;

    /* 0x128 : ef_zone_02_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_02_w2;

    /* 0x12C : ef_zone_02_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_02_w3;

    /* 0x130 : ef_zone_03_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_03_w0;

    /* 0x134 : ef_zone_03_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_03_w1;

    /* 0x138 : ef_zone_03_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_03_w2;

    /* 0x13C : ef_zone_03_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_03_w3;

    /* 0x140 : ef_zone_04_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_04_w0;

    /* 0x144 : ef_zone_04_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_04_w1;

    /* 0x148 : ef_zone_04_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_04_w2;

    /* 0x14C : ef_zone_04_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_04_w3;

    /* 0x150 : ef_zone_05_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_05_w0;

    /* 0x154 : ef_zone_05_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_05_w1;

    /* 0x158 : ef_zone_05_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_05_w2;

    /* 0x15C : ef_zone_05_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_05_w3;

    /* 0x160 : ef_zone_06_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_06_w0;

    /* 0x164 : ef_zone_06_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_06_w1;

    /* 0x168 : ef_zone_06_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_06_w2;

    /* 0x16C : ef_zone_06_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_06_w3;

    /* 0x170 : ef_zone_07_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_07_w0;

    /* 0x174 : ef_zone_07_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_07_w1;

    /* 0x178 : ef_zone_07_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_07_w2;

    /* 0x17C : ef_zone_07_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_07_w3;

    /* 0x180 : ef_zone_08_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_08_w0;

    /* 0x184 : ef_zone_08_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_08_w1;

    /* 0x188 : ef_zone_08_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_08_w2;

    /* 0x18C : ef_zone_08_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_08_w3;

    /* 0x190 : ef_zone_09_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_09_w0;

    /* 0x194 : ef_zone_09_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_09_w1;

    /* 0x198 : ef_zone_09_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_09_w2;

    /* 0x19C : ef_zone_09_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_09_w3;

    /* 0x1A0 : ef_zone_10_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_10_w0;

    /* 0x1A4 : ef_zone_10_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_10_w1;

    /* 0x1A8 : ef_zone_10_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_10_w2;

    /* 0x1AC : ef_zone_10_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_10_w3;

    /* 0x1B0 : ef_zone_11_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_11_w0;

    /* 0x1B4 : ef_zone_11_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_11_w1;

    /* 0x1B8 : ef_zone_11_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_11_w2;

    /* 0x1BC : ef_zone_11_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_11_w3;

    /* 0x1C0 : ef_zone_12_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_12_w0;

    /* 0x1C4 : ef_zone_12_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_12_w1;

    /* 0x1C8 : ef_zone_12_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_12_w2;

    /* 0x1CC : ef_zone_12_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_12_w3;

    /* 0x1D0 : ef_zone_13_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_13_w0;

    /* 0x1D4 : ef_zone_13_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_13_w1;

    /* 0x1D8 : ef_zone_13_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_13_w2;

    /* 0x1DC : ef_zone_13_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_13_w3;

    /* 0x1E0 : ef_zone_14_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_14_w0;

    /* 0x1E4 : ef_zone_14_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_14_w1;

    /* 0x1E8 : ef_zone_14_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_14_w2;

    /* 0x1EC : ef_zone_14_w3 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_14_w3;

    /* 0x1F0 : ef_zone_15_w0 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_15_w0;

    /* 0x1F4 : ef_zone_15_w1 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_15_w1;

    /* 0x1F8 : ef_zone_15_w2 */
    union {
        struct {
            uint32_t reserved_0_31                  : 32; /* [31: 0],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_15_w2;

    /* 0x1FC : ef_zone_15_w3 */
    union {
        struct {
            uint32_t ef_zone_15_w3                  : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_00             :  1; /* [   16],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_01             :  1; /* [   17],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_02             :  1; /* [   18],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_03             :  1; /* [   19],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_04             :  1; /* [   20],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_05             :  1; /* [   21],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_06             :  1; /* [   22],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_07             :  1; /* [   23],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_08             :  1; /* [   24],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_09             :  1; /* [   25],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_10             :  1; /* [   26],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_11             :  1; /* [   27],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_12             :  1; /* [   28],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_13             :  1; /* [   29],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_14             :  1; /* [   30],        r/w,        0x0 */
            uint32_t wr_lock_ef_zone_15             :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ef_zone_15_w3;

};

typedef volatile struct ef_data_reg ef_data_reg_t;


#endif  /* __EF_DATA_REG_H__ */
