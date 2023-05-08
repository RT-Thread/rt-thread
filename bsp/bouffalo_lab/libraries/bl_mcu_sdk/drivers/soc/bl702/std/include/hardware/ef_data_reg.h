/**
  ******************************************************************************
  * @file    EF_DATA_reg.h
  * @version V1.2
  * @date    2020-04-30
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
#ifndef __EF_DATA_REG_H__
#define __EF_DATA_REG_H__

#include "bl702.h"

/* 0x0 : ef_cfg_0 */
#define EF_DATA_EF_CFG_0_OFFSET         (0x0)
#define EF_DATA_EF_SF_AES_MODE          EF_DATA_EF_SF_AES_MODE
#define EF_DATA_EF_SF_AES_MODE_POS      (0U)
#define EF_DATA_EF_SF_AES_MODE_LEN      (2U)
#define EF_DATA_EF_SF_AES_MODE_MSK      (((1U << EF_DATA_EF_SF_AES_MODE_LEN) - 1) << EF_DATA_EF_SF_AES_MODE_POS)
#define EF_DATA_EF_SF_AES_MODE_UMSK     (~(((1U << EF_DATA_EF_SF_AES_MODE_LEN) - 1) << EF_DATA_EF_SF_AES_MODE_POS))
#define EF_DATA_EF_SBOOT_SIGN_MODE      EF_DATA_EF_SBOOT_SIGN_MODE
#define EF_DATA_EF_SBOOT_SIGN_MODE_POS  (2U)
#define EF_DATA_EF_SBOOT_SIGN_MODE_LEN  (2U)
#define EF_DATA_EF_SBOOT_SIGN_MODE_MSK  (((1U << EF_DATA_EF_SBOOT_SIGN_MODE_LEN) - 1) << EF_DATA_EF_SBOOT_SIGN_MODE_POS)
#define EF_DATA_EF_SBOOT_SIGN_MODE_UMSK (~(((1U << EF_DATA_EF_SBOOT_SIGN_MODE_LEN) - 1) << EF_DATA_EF_SBOOT_SIGN_MODE_POS))
#define EF_DATA_EF_SBOOT_EN             EF_DATA_EF_SBOOT_EN
#define EF_DATA_EF_SBOOT_EN_POS         (4U)
#define EF_DATA_EF_SBOOT_EN_LEN         (2U)
#define EF_DATA_EF_SBOOT_EN_MSK         (((1U << EF_DATA_EF_SBOOT_EN_LEN) - 1) << EF_DATA_EF_SBOOT_EN_POS)
#define EF_DATA_EF_SBOOT_EN_UMSK        (~(((1U << EF_DATA_EF_SBOOT_EN_LEN) - 1) << EF_DATA_EF_SBOOT_EN_POS))
#define EF_DATA_EF_CPU0_ENC_EN          EF_DATA_EF_CPU0_ENC_EN
#define EF_DATA_EF_CPU0_ENC_EN_POS      (7U)
#define EF_DATA_EF_CPU0_ENC_EN_LEN      (1U)
#define EF_DATA_EF_CPU0_ENC_EN_MSK      (((1U << EF_DATA_EF_CPU0_ENC_EN_LEN) - 1) << EF_DATA_EF_CPU0_ENC_EN_POS)
#define EF_DATA_EF_CPU0_ENC_EN_UMSK     (~(((1U << EF_DATA_EF_CPU0_ENC_EN_LEN) - 1) << EF_DATA_EF_CPU0_ENC_EN_POS))
#define EF_DATA_EF_BOOT_SEL             EF_DATA_EF_BOOT_SEL
#define EF_DATA_EF_BOOT_SEL_POS         (8U)
#define EF_DATA_EF_BOOT_SEL_LEN         (4U)
#define EF_DATA_EF_BOOT_SEL_MSK         (((1U << EF_DATA_EF_BOOT_SEL_LEN) - 1) << EF_DATA_EF_BOOT_SEL_POS)
#define EF_DATA_EF_BOOT_SEL_UMSK        (~(((1U << EF_DATA_EF_BOOT_SEL_LEN) - 1) << EF_DATA_EF_BOOT_SEL_POS))
#define EF_DATA_EF_SF_KEY_0_SEL         EF_DATA_EF_SF_KEY_0_SEL
#define EF_DATA_EF_SF_KEY_0_SEL_POS     (12U)
#define EF_DATA_EF_SF_KEY_0_SEL_LEN     (2U)
#define EF_DATA_EF_SF_KEY_0_SEL_MSK     (((1U << EF_DATA_EF_SF_KEY_0_SEL_LEN) - 1) << EF_DATA_EF_SF_KEY_0_SEL_POS)
#define EF_DATA_EF_SF_KEY_0_SEL_UMSK    (~(((1U << EF_DATA_EF_SF_KEY_0_SEL_LEN) - 1) << EF_DATA_EF_SF_KEY_0_SEL_POS))
#define EF_DATA_EF_0_KEY_ENC_EN         EF_DATA_EF_0_KEY_ENC_EN
#define EF_DATA_EF_0_KEY_ENC_EN_POS     (17U)
#define EF_DATA_EF_0_KEY_ENC_EN_LEN     (1U)
#define EF_DATA_EF_0_KEY_ENC_EN_MSK     (((1U << EF_DATA_EF_0_KEY_ENC_EN_LEN) - 1) << EF_DATA_EF_0_KEY_ENC_EN_POS)
#define EF_DATA_EF_0_KEY_ENC_EN_UMSK    (~(((1U << EF_DATA_EF_0_KEY_ENC_EN_LEN) - 1) << EF_DATA_EF_0_KEY_ENC_EN_POS))
#define EF_DATA_EF_DBG_JTAG_0_DIS       EF_DATA_EF_DBG_JTAG_0_DIS
#define EF_DATA_EF_DBG_JTAG_0_DIS_POS   (26U)
#define EF_DATA_EF_DBG_JTAG_0_DIS_LEN   (2U)
#define EF_DATA_EF_DBG_JTAG_0_DIS_MSK   (((1U << EF_DATA_EF_DBG_JTAG_0_DIS_LEN) - 1) << EF_DATA_EF_DBG_JTAG_0_DIS_POS)
#define EF_DATA_EF_DBG_JTAG_0_DIS_UMSK  (~(((1U << EF_DATA_EF_DBG_JTAG_0_DIS_LEN) - 1) << EF_DATA_EF_DBG_JTAG_0_DIS_POS))
#define EF_DATA_EF_DBG_MODE             EF_DATA_EF_DBG_MODE
#define EF_DATA_EF_DBG_MODE_POS         (28U)
#define EF_DATA_EF_DBG_MODE_LEN         (4U)
#define EF_DATA_EF_DBG_MODE_MSK         (((1U << EF_DATA_EF_DBG_MODE_LEN) - 1) << EF_DATA_EF_DBG_MODE_POS)
#define EF_DATA_EF_DBG_MODE_UMSK        (~(((1U << EF_DATA_EF_DBG_MODE_LEN) - 1) << EF_DATA_EF_DBG_MODE_POS))

/* 0x4 : ef_dbg_pwd_low */
#define EF_DATA_EF_DBG_PWD_LOW_OFFSET (0x4)
#define EF_DATA_EF_DBG_PWD_LOW        EF_DATA_EF_DBG_PWD_LOW
#define EF_DATA_EF_DBG_PWD_LOW_POS    (0U)
#define EF_DATA_EF_DBG_PWD_LOW_LEN    (32U)
#define EF_DATA_EF_DBG_PWD_LOW_MSK    (((1U << EF_DATA_EF_DBG_PWD_LOW_LEN) - 1) << EF_DATA_EF_DBG_PWD_LOW_POS)
#define EF_DATA_EF_DBG_PWD_LOW_UMSK   (~(((1U << EF_DATA_EF_DBG_PWD_LOW_LEN) - 1) << EF_DATA_EF_DBG_PWD_LOW_POS))

/* 0x8 : ef_dbg_pwd_high */
#define EF_DATA_EF_DBG_PWD_HIGH_OFFSET (0x8)
#define EF_DATA_EF_DBG_PWD_HIGH        EF_DATA_EF_DBG_PWD_HIGH
#define EF_DATA_EF_DBG_PWD_HIGH_POS    (0U)
#define EF_DATA_EF_DBG_PWD_HIGH_LEN    (32U)
#define EF_DATA_EF_DBG_PWD_HIGH_MSK    (((1U << EF_DATA_EF_DBG_PWD_HIGH_LEN) - 1) << EF_DATA_EF_DBG_PWD_HIGH_POS)
#define EF_DATA_EF_DBG_PWD_HIGH_UMSK   (~(((1U << EF_DATA_EF_DBG_PWD_HIGH_LEN) - 1) << EF_DATA_EF_DBG_PWD_HIGH_POS))

/* 0xC : ef_ana_trim_0 */
#define EF_DATA_EF_ANA_TRIM_0_OFFSET (0xC)
#define EF_DATA_EF_ANA_TRIM_0        EF_DATA_EF_ANA_TRIM_0
#define EF_DATA_EF_ANA_TRIM_0_POS    (0U)
#define EF_DATA_EF_ANA_TRIM_0_LEN    (32U)
#define EF_DATA_EF_ANA_TRIM_0_MSK    (((1U << EF_DATA_EF_ANA_TRIM_0_LEN) - 1) << EF_DATA_EF_ANA_TRIM_0_POS)
#define EF_DATA_EF_ANA_TRIM_0_UMSK   (~(((1U << EF_DATA_EF_ANA_TRIM_0_LEN) - 1) << EF_DATA_EF_ANA_TRIM_0_POS))

/* 0x10 : ef_sw_usage_0 */
#define EF_DATA_EF_SW_USAGE_0_OFFSET (0x10)
#define EF_DATA_EF_SW_USAGE_0        EF_DATA_EF_SW_USAGE_0
#define EF_DATA_EF_SW_USAGE_0_POS    (0U)
#define EF_DATA_EF_SW_USAGE_0_LEN    (32U)
#define EF_DATA_EF_SW_USAGE_0_MSK    (((1U << EF_DATA_EF_SW_USAGE_0_LEN) - 1) << EF_DATA_EF_SW_USAGE_0_POS)
#define EF_DATA_EF_SW_USAGE_0_UMSK   (~(((1U << EF_DATA_EF_SW_USAGE_0_LEN) - 1) << EF_DATA_EF_SW_USAGE_0_POS))

/* 0x14 : ef_wifi_mac_low */
#define EF_DATA_EF_WIFI_MAC_LOW_OFFSET (0x14)
#define EF_DATA_EF_WIFI_MAC_LOW        EF_DATA_EF_WIFI_MAC_LOW
#define EF_DATA_EF_WIFI_MAC_LOW_POS    (0U)
#define EF_DATA_EF_WIFI_MAC_LOW_LEN    (32U)
#define EF_DATA_EF_WIFI_MAC_LOW_MSK    (((1U << EF_DATA_EF_WIFI_MAC_LOW_LEN) - 1) << EF_DATA_EF_WIFI_MAC_LOW_POS)
#define EF_DATA_EF_WIFI_MAC_LOW_UMSK   (~(((1U << EF_DATA_EF_WIFI_MAC_LOW_LEN) - 1) << EF_DATA_EF_WIFI_MAC_LOW_POS))

/* 0x18 : ef_wifi_mac_high */
#define EF_DATA_EF_WIFI_MAC_HIGH_OFFSET (0x18)
#define EF_DATA_EF_WIFI_MAC_HIGH        EF_DATA_EF_WIFI_MAC_HIGH
#define EF_DATA_EF_WIFI_MAC_HIGH_POS    (0U)
#define EF_DATA_EF_WIFI_MAC_HIGH_LEN    (32U)
#define EF_DATA_EF_WIFI_MAC_HIGH_MSK    (((1U << EF_DATA_EF_WIFI_MAC_HIGH_LEN) - 1) << EF_DATA_EF_WIFI_MAC_HIGH_POS)
#define EF_DATA_EF_WIFI_MAC_HIGH_UMSK   (~(((1U << EF_DATA_EF_WIFI_MAC_HIGH_LEN) - 1) << EF_DATA_EF_WIFI_MAC_HIGH_POS))

/* 0x1C : ef_key_slot_0_w0 */
#define EF_DATA_EF_KEY_SLOT_0_W0_OFFSET (0x1C)
#define EF_DATA_EF_KEY_SLOT_0_W0        EF_DATA_EF_KEY_SLOT_0_W0
#define EF_DATA_EF_KEY_SLOT_0_W0_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_0_W0_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_0_W0_MSK    (((1U << EF_DATA_EF_KEY_SLOT_0_W0_LEN) - 1) << EF_DATA_EF_KEY_SLOT_0_W0_POS)
#define EF_DATA_EF_KEY_SLOT_0_W0_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_0_W0_LEN) - 1) << EF_DATA_EF_KEY_SLOT_0_W0_POS))

/* 0x20 : ef_key_slot_0_w1 */
#define EF_DATA_EF_KEY_SLOT_0_W1_OFFSET (0x20)
#define EF_DATA_EF_KEY_SLOT_0_W1        EF_DATA_EF_KEY_SLOT_0_W1
#define EF_DATA_EF_KEY_SLOT_0_W1_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_0_W1_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_0_W1_MSK    (((1U << EF_DATA_EF_KEY_SLOT_0_W1_LEN) - 1) << EF_DATA_EF_KEY_SLOT_0_W1_POS)
#define EF_DATA_EF_KEY_SLOT_0_W1_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_0_W1_LEN) - 1) << EF_DATA_EF_KEY_SLOT_0_W1_POS))

/* 0x24 : ef_key_slot_0_w2 */
#define EF_DATA_EF_KEY_SLOT_0_W2_OFFSET (0x24)
#define EF_DATA_EF_KEY_SLOT_0_W2        EF_DATA_EF_KEY_SLOT_0_W2
#define EF_DATA_EF_KEY_SLOT_0_W2_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_0_W2_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_0_W2_MSK    (((1U << EF_DATA_EF_KEY_SLOT_0_W2_LEN) - 1) << EF_DATA_EF_KEY_SLOT_0_W2_POS)
#define EF_DATA_EF_KEY_SLOT_0_W2_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_0_W2_LEN) - 1) << EF_DATA_EF_KEY_SLOT_0_W2_POS))

/* 0x28 : ef_key_slot_0_w3 */
#define EF_DATA_EF_KEY_SLOT_0_W3_OFFSET (0x28)
#define EF_DATA_EF_KEY_SLOT_0_W3        EF_DATA_EF_KEY_SLOT_0_W3
#define EF_DATA_EF_KEY_SLOT_0_W3_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_0_W3_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_0_W3_MSK    (((1U << EF_DATA_EF_KEY_SLOT_0_W3_LEN) - 1) << EF_DATA_EF_KEY_SLOT_0_W3_POS)
#define EF_DATA_EF_KEY_SLOT_0_W3_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_0_W3_LEN) - 1) << EF_DATA_EF_KEY_SLOT_0_W3_POS))

/* 0x2C : ef_key_slot_1_w0 */
#define EF_DATA_EF_KEY_SLOT_1_W0_OFFSET (0x2C)
#define EF_DATA_EF_KEY_SLOT_1_W0        EF_DATA_EF_KEY_SLOT_1_W0
#define EF_DATA_EF_KEY_SLOT_1_W0_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_1_W0_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_1_W0_MSK    (((1U << EF_DATA_EF_KEY_SLOT_1_W0_LEN) - 1) << EF_DATA_EF_KEY_SLOT_1_W0_POS)
#define EF_DATA_EF_KEY_SLOT_1_W0_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_1_W0_LEN) - 1) << EF_DATA_EF_KEY_SLOT_1_W0_POS))

/* 0x30 : ef_key_slot_1_w1 */
#define EF_DATA_EF_KEY_SLOT_1_W1_OFFSET (0x30)
#define EF_DATA_EF_KEY_SLOT_1_W1        EF_DATA_EF_KEY_SLOT_1_W1
#define EF_DATA_EF_KEY_SLOT_1_W1_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_1_W1_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_1_W1_MSK    (((1U << EF_DATA_EF_KEY_SLOT_1_W1_LEN) - 1) << EF_DATA_EF_KEY_SLOT_1_W1_POS)
#define EF_DATA_EF_KEY_SLOT_1_W1_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_1_W1_LEN) - 1) << EF_DATA_EF_KEY_SLOT_1_W1_POS))

/* 0x34 : ef_key_slot_1_w2 */
#define EF_DATA_EF_KEY_SLOT_1_W2_OFFSET (0x34)
#define EF_DATA_EF_KEY_SLOT_1_W2        EF_DATA_EF_KEY_SLOT_1_W2
#define EF_DATA_EF_KEY_SLOT_1_W2_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_1_W2_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_1_W2_MSK    (((1U << EF_DATA_EF_KEY_SLOT_1_W2_LEN) - 1) << EF_DATA_EF_KEY_SLOT_1_W2_POS)
#define EF_DATA_EF_KEY_SLOT_1_W2_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_1_W2_LEN) - 1) << EF_DATA_EF_KEY_SLOT_1_W2_POS))

/* 0x38 : ef_key_slot_1_w3 */
#define EF_DATA_EF_KEY_SLOT_1_W3_OFFSET (0x38)
#define EF_DATA_EF_KEY_SLOT_1_W3        EF_DATA_EF_KEY_SLOT_1_W3
#define EF_DATA_EF_KEY_SLOT_1_W3_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_1_W3_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_1_W3_MSK    (((1U << EF_DATA_EF_KEY_SLOT_1_W3_LEN) - 1) << EF_DATA_EF_KEY_SLOT_1_W3_POS)
#define EF_DATA_EF_KEY_SLOT_1_W3_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_1_W3_LEN) - 1) << EF_DATA_EF_KEY_SLOT_1_W3_POS))

/* 0x3C : ef_key_slot_2_w0 */
#define EF_DATA_EF_KEY_SLOT_2_W0_OFFSET (0x3C)
#define EF_DATA_EF_KEY_SLOT_2_W0        EF_DATA_EF_KEY_SLOT_2_W0
#define EF_DATA_EF_KEY_SLOT_2_W0_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_2_W0_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_2_W0_MSK    (((1U << EF_DATA_EF_KEY_SLOT_2_W0_LEN) - 1) << EF_DATA_EF_KEY_SLOT_2_W0_POS)
#define EF_DATA_EF_KEY_SLOT_2_W0_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_2_W0_LEN) - 1) << EF_DATA_EF_KEY_SLOT_2_W0_POS))

/* 0x40 : ef_key_slot_2_w1 */
#define EF_DATA_EF_KEY_SLOT_2_W1_OFFSET (0x40)
#define EF_DATA_EF_KEY_SLOT_2_W1        EF_DATA_EF_KEY_SLOT_2_W1
#define EF_DATA_EF_KEY_SLOT_2_W1_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_2_W1_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_2_W1_MSK    (((1U << EF_DATA_EF_KEY_SLOT_2_W1_LEN) - 1) << EF_DATA_EF_KEY_SLOT_2_W1_POS)
#define EF_DATA_EF_KEY_SLOT_2_W1_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_2_W1_LEN) - 1) << EF_DATA_EF_KEY_SLOT_2_W1_POS))

/* 0x44 : ef_key_slot_2_w2 */
#define EF_DATA_EF_KEY_SLOT_2_W2_OFFSET (0x44)
#define EF_DATA_EF_KEY_SLOT_2_W2        EF_DATA_EF_KEY_SLOT_2_W2
#define EF_DATA_EF_KEY_SLOT_2_W2_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_2_W2_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_2_W2_MSK    (((1U << EF_DATA_EF_KEY_SLOT_2_W2_LEN) - 1) << EF_DATA_EF_KEY_SLOT_2_W2_POS)
#define EF_DATA_EF_KEY_SLOT_2_W2_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_2_W2_LEN) - 1) << EF_DATA_EF_KEY_SLOT_2_W2_POS))

/* 0x48 : ef_key_slot_2_w3 */
#define EF_DATA_EF_KEY_SLOT_2_W3_OFFSET (0x48)
#define EF_DATA_EF_KEY_SLOT_2_W3        EF_DATA_EF_KEY_SLOT_2_W3
#define EF_DATA_EF_KEY_SLOT_2_W3_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_2_W3_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_2_W3_MSK    (((1U << EF_DATA_EF_KEY_SLOT_2_W3_LEN) - 1) << EF_DATA_EF_KEY_SLOT_2_W3_POS)
#define EF_DATA_EF_KEY_SLOT_2_W3_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_2_W3_LEN) - 1) << EF_DATA_EF_KEY_SLOT_2_W3_POS))

/* 0x4C : ef_key_slot_3_w0 */
#define EF_DATA_EF_KEY_SLOT_3_W0_OFFSET (0x4C)
#define EF_DATA_EF_KEY_SLOT_3_W0        EF_DATA_EF_KEY_SLOT_3_W0
#define EF_DATA_EF_KEY_SLOT_3_W0_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_3_W0_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_3_W0_MSK    (((1U << EF_DATA_EF_KEY_SLOT_3_W0_LEN) - 1) << EF_DATA_EF_KEY_SLOT_3_W0_POS)
#define EF_DATA_EF_KEY_SLOT_3_W0_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_3_W0_LEN) - 1) << EF_DATA_EF_KEY_SLOT_3_W0_POS))

/* 0x50 : ef_key_slot_3_w1 */
#define EF_DATA_EF_KEY_SLOT_3_W1_OFFSET (0x50)
#define EF_DATA_EF_KEY_SLOT_3_W1        EF_DATA_EF_KEY_SLOT_3_W1
#define EF_DATA_EF_KEY_SLOT_3_W1_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_3_W1_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_3_W1_MSK    (((1U << EF_DATA_EF_KEY_SLOT_3_W1_LEN) - 1) << EF_DATA_EF_KEY_SLOT_3_W1_POS)
#define EF_DATA_EF_KEY_SLOT_3_W1_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_3_W1_LEN) - 1) << EF_DATA_EF_KEY_SLOT_3_W1_POS))

/* 0x54 : ef_key_slot_3_w2 */
#define EF_DATA_EF_KEY_SLOT_3_W2_OFFSET (0x54)
#define EF_DATA_EF_KEY_SLOT_3_W2        EF_DATA_EF_KEY_SLOT_3_W2
#define EF_DATA_EF_KEY_SLOT_3_W2_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_3_W2_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_3_W2_MSK    (((1U << EF_DATA_EF_KEY_SLOT_3_W2_LEN) - 1) << EF_DATA_EF_KEY_SLOT_3_W2_POS)
#define EF_DATA_EF_KEY_SLOT_3_W2_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_3_W2_LEN) - 1) << EF_DATA_EF_KEY_SLOT_3_W2_POS))

/* 0x58 : ef_key_slot_3_w3 */
#define EF_DATA_EF_KEY_SLOT_3_W3_OFFSET (0x58)
#define EF_DATA_EF_KEY_SLOT_3_W3        EF_DATA_EF_KEY_SLOT_3_W3
#define EF_DATA_EF_KEY_SLOT_3_W3_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_3_W3_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_3_W3_MSK    (((1U << EF_DATA_EF_KEY_SLOT_3_W3_LEN) - 1) << EF_DATA_EF_KEY_SLOT_3_W3_POS)
#define EF_DATA_EF_KEY_SLOT_3_W3_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_3_W3_LEN) - 1) << EF_DATA_EF_KEY_SLOT_3_W3_POS))

/* 0x5C : ef_key_slot_4_w0 */
#define EF_DATA_EF_KEY_SLOT_4_W0_OFFSET (0x5C)
#define EF_DATA_EF_KEY_SLOT_4_W0        EF_DATA_EF_KEY_SLOT_4_W0
#define EF_DATA_EF_KEY_SLOT_4_W0_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_4_W0_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_4_W0_MSK    (((1U << EF_DATA_EF_KEY_SLOT_4_W0_LEN) - 1) << EF_DATA_EF_KEY_SLOT_4_W0_POS)
#define EF_DATA_EF_KEY_SLOT_4_W0_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_4_W0_LEN) - 1) << EF_DATA_EF_KEY_SLOT_4_W0_POS))

/* 0x60 : ef_key_slot_4_w1 */
#define EF_DATA_EF_KEY_SLOT_4_W1_OFFSET (0x60)
#define EF_DATA_EF_KEY_SLOT_4_W1        EF_DATA_EF_KEY_SLOT_4_W1
#define EF_DATA_EF_KEY_SLOT_4_W1_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_4_W1_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_4_W1_MSK    (((1U << EF_DATA_EF_KEY_SLOT_4_W1_LEN) - 1) << EF_DATA_EF_KEY_SLOT_4_W1_POS)
#define EF_DATA_EF_KEY_SLOT_4_W1_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_4_W1_LEN) - 1) << EF_DATA_EF_KEY_SLOT_4_W1_POS))

/* 0x64 : ef_key_slot_4_w2 */
#define EF_DATA_EF_KEY_SLOT_4_W2_OFFSET (0x64)
#define EF_DATA_EF_KEY_SLOT_4_W2        EF_DATA_EF_KEY_SLOT_4_W2
#define EF_DATA_EF_KEY_SLOT_4_W2_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_4_W2_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_4_W2_MSK    (((1U << EF_DATA_EF_KEY_SLOT_4_W2_LEN) - 1) << EF_DATA_EF_KEY_SLOT_4_W2_POS)
#define EF_DATA_EF_KEY_SLOT_4_W2_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_4_W2_LEN) - 1) << EF_DATA_EF_KEY_SLOT_4_W2_POS))

/* 0x68 : ef_key_slot_4_w3 */
#define EF_DATA_EF_KEY_SLOT_4_W3_OFFSET (0x68)
#define EF_DATA_EF_KEY_SLOT_4_W3        EF_DATA_EF_KEY_SLOT_4_W3
#define EF_DATA_EF_KEY_SLOT_4_W3_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_4_W3_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_4_W3_MSK    (((1U << EF_DATA_EF_KEY_SLOT_4_W3_LEN) - 1) << EF_DATA_EF_KEY_SLOT_4_W3_POS)
#define EF_DATA_EF_KEY_SLOT_4_W3_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_4_W3_LEN) - 1) << EF_DATA_EF_KEY_SLOT_4_W3_POS))

/* 0x6C : ef_key_slot_5_w0 */
#define EF_DATA_EF_KEY_SLOT_5_W0_OFFSET (0x6C)
#define EF_DATA_EF_KEY_SLOT_5_W0        EF_DATA_EF_KEY_SLOT_5_W0
#define EF_DATA_EF_KEY_SLOT_5_W0_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_5_W0_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_5_W0_MSK    (((1U << EF_DATA_EF_KEY_SLOT_5_W0_LEN) - 1) << EF_DATA_EF_KEY_SLOT_5_W0_POS)
#define EF_DATA_EF_KEY_SLOT_5_W0_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_5_W0_LEN) - 1) << EF_DATA_EF_KEY_SLOT_5_W0_POS))

/* 0x70 : ef_key_slot_5_w1 */
#define EF_DATA_EF_KEY_SLOT_5_W1_OFFSET (0x70)
#define EF_DATA_EF_KEY_SLOT_5_W1        EF_DATA_EF_KEY_SLOT_5_W1
#define EF_DATA_EF_KEY_SLOT_5_W1_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_5_W1_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_5_W1_MSK    (((1U << EF_DATA_EF_KEY_SLOT_5_W1_LEN) - 1) << EF_DATA_EF_KEY_SLOT_5_W1_POS)
#define EF_DATA_EF_KEY_SLOT_5_W1_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_5_W1_LEN) - 1) << EF_DATA_EF_KEY_SLOT_5_W1_POS))

/* 0x74 : ef_key_slot_5_w2 */
#define EF_DATA_EF_KEY_SLOT_5_W2_OFFSET (0x74)
#define EF_DATA_EF_KEY_SLOT_5_W2        EF_DATA_EF_KEY_SLOT_5_W2
#define EF_DATA_EF_KEY_SLOT_5_W2_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_5_W2_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_5_W2_MSK    (((1U << EF_DATA_EF_KEY_SLOT_5_W2_LEN) - 1) << EF_DATA_EF_KEY_SLOT_5_W2_POS)
#define EF_DATA_EF_KEY_SLOT_5_W2_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_5_W2_LEN) - 1) << EF_DATA_EF_KEY_SLOT_5_W2_POS))

/* 0x78 : ef_key_slot_5_w3 */
#define EF_DATA_EF_KEY_SLOT_5_W3_OFFSET (0x78)
#define EF_DATA_EF_KEY_SLOT_5_W3        EF_DATA_EF_KEY_SLOT_5_W3
#define EF_DATA_EF_KEY_SLOT_5_W3_POS    (0U)
#define EF_DATA_EF_KEY_SLOT_5_W3_LEN    (32U)
#define EF_DATA_EF_KEY_SLOT_5_W3_MSK    (((1U << EF_DATA_EF_KEY_SLOT_5_W3_LEN) - 1) << EF_DATA_EF_KEY_SLOT_5_W3_POS)
#define EF_DATA_EF_KEY_SLOT_5_W3_UMSK   (~(((1U << EF_DATA_EF_KEY_SLOT_5_W3_LEN) - 1) << EF_DATA_EF_KEY_SLOT_5_W3_POS))

/* 0x7C : EF_DATA_lock */
#define EF_DATA_LOCK_OFFSET               (0x7C)
#define EF_DATA_EF_ANA_TRIM_1             EF_DATA_EF_ANA_TRIM_1
#define EF_DATA_EF_ANA_TRIM_1_POS         (0U)
#define EF_DATA_EF_ANA_TRIM_1_LEN         (13U)
#define EF_DATA_EF_ANA_TRIM_1_MSK         (((1U << EF_DATA_EF_ANA_TRIM_1_LEN) - 1) << EF_DATA_EF_ANA_TRIM_1_POS)
#define EF_DATA_EF_ANA_TRIM_1_UMSK        (~(((1U << EF_DATA_EF_ANA_TRIM_1_LEN) - 1) << EF_DATA_EF_ANA_TRIM_1_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_4_L      EF_DATA_WR_LOCK_KEY_SLOT_4_L
#define EF_DATA_WR_LOCK_KEY_SLOT_4_L_POS  (13U)
#define EF_DATA_WR_LOCK_KEY_SLOT_4_L_LEN  (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_4_L_MSK  (((1U << EF_DATA_WR_LOCK_KEY_SLOT_4_L_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_4_L_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_4_L_UMSK (~(((1U << EF_DATA_WR_LOCK_KEY_SLOT_4_L_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_4_L_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_5_L      EF_DATA_WR_LOCK_KEY_SLOT_5_L
#define EF_DATA_WR_LOCK_KEY_SLOT_5_L_POS  (14U)
#define EF_DATA_WR_LOCK_KEY_SLOT_5_L_LEN  (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_5_L_MSK  (((1U << EF_DATA_WR_LOCK_KEY_SLOT_5_L_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_5_L_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_5_L_UMSK (~(((1U << EF_DATA_WR_LOCK_KEY_SLOT_5_L_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_5_L_POS))
#define EF_DATA_WR_LOCK_BOOT_MODE         EF_DATA_WR_LOCK_BOOT_MODE
#define EF_DATA_WR_LOCK_BOOT_MODE_POS     (15U)
#define EF_DATA_WR_LOCK_BOOT_MODE_LEN     (1U)
#define EF_DATA_WR_LOCK_BOOT_MODE_MSK     (((1U << EF_DATA_WR_LOCK_BOOT_MODE_LEN) - 1) << EF_DATA_WR_LOCK_BOOT_MODE_POS)
#define EF_DATA_WR_LOCK_BOOT_MODE_UMSK    (~(((1U << EF_DATA_WR_LOCK_BOOT_MODE_LEN) - 1) << EF_DATA_WR_LOCK_BOOT_MODE_POS))
#define EF_DATA_WR_LOCK_DBG_PWD           EF_DATA_WR_LOCK_DBG_PWD
#define EF_DATA_WR_LOCK_DBG_PWD_POS       (16U)
#define EF_DATA_WR_LOCK_DBG_PWD_LEN       (1U)
#define EF_DATA_WR_LOCK_DBG_PWD_MSK       (((1U << EF_DATA_WR_LOCK_DBG_PWD_LEN) - 1) << EF_DATA_WR_LOCK_DBG_PWD_POS)
#define EF_DATA_WR_LOCK_DBG_PWD_UMSK      (~(((1U << EF_DATA_WR_LOCK_DBG_PWD_LEN) - 1) << EF_DATA_WR_LOCK_DBG_PWD_POS))
#define EF_DATA_WR_LOCK_SW_USAGE_0        EF_DATA_WR_LOCK_SW_USAGE_0
#define EF_DATA_WR_LOCK_SW_USAGE_0_POS    (17U)
#define EF_DATA_WR_LOCK_SW_USAGE_0_LEN    (1U)
#define EF_DATA_WR_LOCK_SW_USAGE_0_MSK    (((1U << EF_DATA_WR_LOCK_SW_USAGE_0_LEN) - 1) << EF_DATA_WR_LOCK_SW_USAGE_0_POS)
#define EF_DATA_WR_LOCK_SW_USAGE_0_UMSK   (~(((1U << EF_DATA_WR_LOCK_SW_USAGE_0_LEN) - 1) << EF_DATA_WR_LOCK_SW_USAGE_0_POS))
#define EF_DATA_WR_LOCK_WIFI_MAC          EF_DATA_WR_LOCK_WIFI_MAC
#define EF_DATA_WR_LOCK_WIFI_MAC_POS      (18U)
#define EF_DATA_WR_LOCK_WIFI_MAC_LEN      (1U)
#define EF_DATA_WR_LOCK_WIFI_MAC_MSK      (((1U << EF_DATA_WR_LOCK_WIFI_MAC_LEN) - 1) << EF_DATA_WR_LOCK_WIFI_MAC_POS)
#define EF_DATA_WR_LOCK_WIFI_MAC_UMSK     (~(((1U << EF_DATA_WR_LOCK_WIFI_MAC_LEN) - 1) << EF_DATA_WR_LOCK_WIFI_MAC_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_0        EF_DATA_WR_LOCK_KEY_SLOT_0
#define EF_DATA_WR_LOCK_KEY_SLOT_0_POS    (19U)
#define EF_DATA_WR_LOCK_KEY_SLOT_0_LEN    (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_0_MSK    (((1U << EF_DATA_WR_LOCK_KEY_SLOT_0_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_0_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_0_UMSK   (~(((1U << EF_DATA_WR_LOCK_KEY_SLOT_0_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_0_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_1        EF_DATA_WR_LOCK_KEY_SLOT_1
#define EF_DATA_WR_LOCK_KEY_SLOT_1_POS    (20U)
#define EF_DATA_WR_LOCK_KEY_SLOT_1_LEN    (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_1_MSK    (((1U << EF_DATA_WR_LOCK_KEY_SLOT_1_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_1_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_1_UMSK   (~(((1U << EF_DATA_WR_LOCK_KEY_SLOT_1_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_1_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_2        EF_DATA_WR_LOCK_KEY_SLOT_2
#define EF_DATA_WR_LOCK_KEY_SLOT_2_POS    (21U)
#define EF_DATA_WR_LOCK_KEY_SLOT_2_LEN    (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_2_MSK    (((1U << EF_DATA_WR_LOCK_KEY_SLOT_2_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_2_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_2_UMSK   (~(((1U << EF_DATA_WR_LOCK_KEY_SLOT_2_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_2_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_3        EF_DATA_WR_LOCK_KEY_SLOT_3
#define EF_DATA_WR_LOCK_KEY_SLOT_3_POS    (22U)
#define EF_DATA_WR_LOCK_KEY_SLOT_3_LEN    (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_3_MSK    (((1U << EF_DATA_WR_LOCK_KEY_SLOT_3_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_3_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_3_UMSK   (~(((1U << EF_DATA_WR_LOCK_KEY_SLOT_3_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_3_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_4_H      EF_DATA_WR_LOCK_KEY_SLOT_4_H
#define EF_DATA_WR_LOCK_KEY_SLOT_4_H_POS  (23U)
#define EF_DATA_WR_LOCK_KEY_SLOT_4_H_LEN  (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_4_H_MSK  (((1U << EF_DATA_WR_LOCK_KEY_SLOT_4_H_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_4_H_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_4_H_UMSK (~(((1U << EF_DATA_WR_LOCK_KEY_SLOT_4_H_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_4_H_POS))
#define EF_DATA_WR_LOCK_KEY_SLOT_5_H      EF_DATA_WR_LOCK_KEY_SLOT_5_H
#define EF_DATA_WR_LOCK_KEY_SLOT_5_H_POS  (24U)
#define EF_DATA_WR_LOCK_KEY_SLOT_5_H_LEN  (1U)
#define EF_DATA_WR_LOCK_KEY_SLOT_5_H_MSK  (((1U << EF_DATA_WR_LOCK_KEY_SLOT_5_H_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_5_H_POS)
#define EF_DATA_WR_LOCK_KEY_SLOT_5_H_UMSK (~(((1U << EF_DATA_WR_LOCK_KEY_SLOT_5_H_LEN) - 1) << EF_DATA_WR_LOCK_KEY_SLOT_5_H_POS))
#define EF_DATA_RD_LOCK_DBG_PWD           EF_DATA_RD_LOCK_DBG_PWD
#define EF_DATA_RD_LOCK_DBG_PWD_POS       (25U)
#define EF_DATA_RD_LOCK_DBG_PWD_LEN       (1U)
#define EF_DATA_RD_LOCK_DBG_PWD_MSK       (((1U << EF_DATA_RD_LOCK_DBG_PWD_LEN) - 1) << EF_DATA_RD_LOCK_DBG_PWD_POS)
#define EF_DATA_RD_LOCK_DBG_PWD_UMSK      (~(((1U << EF_DATA_RD_LOCK_DBG_PWD_LEN) - 1) << EF_DATA_RD_LOCK_DBG_PWD_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_0        EF_DATA_RD_LOCK_KEY_SLOT_0
#define EF_DATA_RD_LOCK_KEY_SLOT_0_POS    (26U)
#define EF_DATA_RD_LOCK_KEY_SLOT_0_LEN    (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_0_MSK    (((1U << EF_DATA_RD_LOCK_KEY_SLOT_0_LEN) - 1) << EF_DATA_RD_LOCK_KEY_SLOT_0_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_0_UMSK   (~(((1U << EF_DATA_RD_LOCK_KEY_SLOT_0_LEN) - 1) << EF_DATA_RD_LOCK_KEY_SLOT_0_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_1        EF_DATA_RD_LOCK_KEY_SLOT_1
#define EF_DATA_RD_LOCK_KEY_SLOT_1_POS    (27U)
#define EF_DATA_RD_LOCK_KEY_SLOT_1_LEN    (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_1_MSK    (((1U << EF_DATA_RD_LOCK_KEY_SLOT_1_LEN) - 1) << EF_DATA_RD_LOCK_KEY_SLOT_1_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_1_UMSK   (~(((1U << EF_DATA_RD_LOCK_KEY_SLOT_1_LEN) - 1) << EF_DATA_RD_LOCK_KEY_SLOT_1_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_2        EF_DATA_RD_LOCK_KEY_SLOT_2
#define EF_DATA_RD_LOCK_KEY_SLOT_2_POS    (28U)
#define EF_DATA_RD_LOCK_KEY_SLOT_2_LEN    (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_2_MSK    (((1U << EF_DATA_RD_LOCK_KEY_SLOT_2_LEN) - 1) << EF_DATA_RD_LOCK_KEY_SLOT_2_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_2_UMSK   (~(((1U << EF_DATA_RD_LOCK_KEY_SLOT_2_LEN) - 1) << EF_DATA_RD_LOCK_KEY_SLOT_2_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_3        EF_DATA_RD_LOCK_KEY_SLOT_3
#define EF_DATA_RD_LOCK_KEY_SLOT_3_POS    (29U)
#define EF_DATA_RD_LOCK_KEY_SLOT_3_LEN    (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_3_MSK    (((1U << EF_DATA_RD_LOCK_KEY_SLOT_3_LEN) - 1) << EF_DATA_RD_LOCK_KEY_SLOT_3_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_3_UMSK   (~(((1U << EF_DATA_RD_LOCK_KEY_SLOT_3_LEN) - 1) << EF_DATA_RD_LOCK_KEY_SLOT_3_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_4        EF_DATA_RD_LOCK_KEY_SLOT_4
#define EF_DATA_RD_LOCK_KEY_SLOT_4_POS    (30U)
#define EF_DATA_RD_LOCK_KEY_SLOT_4_LEN    (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_4_MSK    (((1U << EF_DATA_RD_LOCK_KEY_SLOT_4_LEN) - 1) << EF_DATA_RD_LOCK_KEY_SLOT_4_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_4_UMSK   (~(((1U << EF_DATA_RD_LOCK_KEY_SLOT_4_LEN) - 1) << EF_DATA_RD_LOCK_KEY_SLOT_4_POS))
#define EF_DATA_RD_LOCK_KEY_SLOT_5        EF_DATA_RD_LOCK_KEY_SLOT_5
#define EF_DATA_RD_LOCK_KEY_SLOT_5_POS    (31U)
#define EF_DATA_RD_LOCK_KEY_SLOT_5_LEN    (1U)
#define EF_DATA_RD_LOCK_KEY_SLOT_5_MSK    (((1U << EF_DATA_RD_LOCK_KEY_SLOT_5_LEN) - 1) << EF_DATA_RD_LOCK_KEY_SLOT_5_POS)
#define EF_DATA_RD_LOCK_KEY_SLOT_5_UMSK   (~(((1U << EF_DATA_RD_LOCK_KEY_SLOT_5_LEN) - 1) << EF_DATA_RD_LOCK_KEY_SLOT_5_POS))

struct EF_DATA_reg {
    /* 0x0 : ef_cfg_0 */
    union {
        struct
        {
            uint32_t ef_sf_aes_mode     : 2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t ef_sboot_sign_mode : 2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t rsvd0              : 2; /* [ 5: 4],        r/w,        0x0 */
            uint32_t rsvd1              : 1; /* [    6],        r/w,        0x0 */
            uint32_t ef_cpu0_enc_en     : 1; /* [    7],        r/w,        0x0 */
            uint32_t ef_boot_sel        : 4; /* [11: 8],        r/w,        0x0 */
            uint32_t ef_sf_key_0_sel    : 2; /* [13:12],        r/w,        0x0 */
            uint32_t rsvd2              : 1; /* [   14],        r/w,        0x0 */
            uint32_t rsvd3              : 1; /* [   15],        r/w,        0x0 */
            uint32_t rsvd4              : 1; /* [   16],        r/w,        0x0 */
            uint32_t ef_0_key_enc_en    : 1; /* [   17],        r/w,        0x0 */
            uint32_t rsvd5              : 1; /* [   18],        r/w,        0x0 */
            uint32_t rsvd6              : 1; /* [   19],        r/w,        0x0 */
            uint32_t rsvd7              : 1; /* [   20],        r/w,        0x0 */
            uint32_t rsvd8              : 1; /* [   21],        r/w,        0x0 */
            uint32_t rsvd9              : 1; /* [   22],        r/w,        0x0 */
            uint32_t rsvd10             : 1; /* [   23],        r/w,        0x0 */
            uint32_t rsvd11             : 2; /* [25:24],        r/w,        0x0 */
            uint32_t ef_dbg_jtag_0_dis  : 2; /* [27:26],        r/w,        0x0 */
            uint32_t ef_dbg_mode        : 4; /* [31:28],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_cfg_0;

    /* 0x4 : ef_dbg_pwd_low */
    union {
        struct
        {
            uint32_t ef_dbg_pwd_low : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_dbg_pwd_low;

    /* 0x8 : ef_dbg_pwd_high */
    union {
        struct
        {
            uint32_t ef_dbg_pwd_high : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_dbg_pwd_high;

    /* 0xC : ef_ana_trim_0 */
    union {
        struct
        {
            uint32_t ef_ana_trim_0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_ana_trim_0;

    /* 0x10 : ef_sw_usage_0 */
    union {
        struct
        {
            uint32_t ef_sw_usage_0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_sw_usage_0;

    /* 0x14 : ef_wifi_mac_low */
    union {
        struct
        {
            uint32_t ef_wifi_mac_low : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_wifi_mac_low;

    /* 0x18 : ef_wifi_mac_high */
    union {
        struct
        {
            uint32_t ef_wifi_mac_high : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_wifi_mac_high;

    /* 0x1C : ef_key_slot_0_w0 */
    union {
        struct
        {
            uint32_t ef_key_slot_0_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_0_w0;

    /* 0x20 : ef_key_slot_0_w1 */
    union {
        struct
        {
            uint32_t ef_key_slot_0_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_0_w1;

    /* 0x24 : ef_key_slot_0_w2 */
    union {
        struct
        {
            uint32_t ef_key_slot_0_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_0_w2;

    /* 0x28 : ef_key_slot_0_w3 */
    union {
        struct
        {
            uint32_t ef_key_slot_0_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_0_w3;

    /* 0x2C : ef_key_slot_1_w0 */
    union {
        struct
        {
            uint32_t ef_key_slot_1_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_1_w0;

    /* 0x30 : ef_key_slot_1_w1 */
    union {
        struct
        {
            uint32_t ef_key_slot_1_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_1_w1;

    /* 0x34 : ef_key_slot_1_w2 */
    union {
        struct
        {
            uint32_t ef_key_slot_1_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_1_w2;

    /* 0x38 : ef_key_slot_1_w3 */
    union {
        struct
        {
            uint32_t ef_key_slot_1_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_1_w3;

    /* 0x3C : ef_key_slot_2_w0 */
    union {
        struct
        {
            uint32_t ef_key_slot_2_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_2_w0;

    /* 0x40 : ef_key_slot_2_w1 */
    union {
        struct
        {
            uint32_t ef_key_slot_2_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_2_w1;

    /* 0x44 : ef_key_slot_2_w2 */
    union {
        struct
        {
            uint32_t ef_key_slot_2_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_2_w2;

    /* 0x48 : ef_key_slot_2_w3 */
    union {
        struct
        {
            uint32_t ef_key_slot_2_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_2_w3;

    /* 0x4C : ef_key_slot_3_w0 */
    union {
        struct
        {
            uint32_t ef_key_slot_3_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_3_w0;

    /* 0x50 : ef_key_slot_3_w1 */
    union {
        struct
        {
            uint32_t ef_key_slot_3_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_3_w1;

    /* 0x54 : ef_key_slot_3_w2 */
    union {
        struct
        {
            uint32_t ef_key_slot_3_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_3_w2;

    /* 0x58 : ef_key_slot_3_w3 */
    union {
        struct
        {
            uint32_t ef_key_slot_3_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_3_w3;

    /* 0x5C : ef_key_slot_4_w0 */
    union {
        struct
        {
            uint32_t ef_key_slot_4_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_4_w0;

    /* 0x60 : ef_key_slot_4_w1 */
    union {
        struct
        {
            uint32_t ef_key_slot_4_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_4_w1;

    /* 0x64 : ef_key_slot_4_w2 */
    union {
        struct
        {
            uint32_t ef_key_slot_4_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_4_w2;

    /* 0x68 : ef_key_slot_4_w3 */
    union {
        struct
        {
            uint32_t ef_key_slot_4_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_4_w3;

    /* 0x6C : ef_key_slot_5_w0 */
    union {
        struct
        {
            uint32_t ef_key_slot_5_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_5_w0;

    /* 0x70 : ef_key_slot_5_w1 */
    union {
        struct
        {
            uint32_t ef_key_slot_5_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_5_w1;

    /* 0x74 : ef_key_slot_5_w2 */
    union {
        struct
        {
            uint32_t ef_key_slot_5_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_5_w2;

    /* 0x78 : ef_key_slot_5_w3 */
    union {
        struct
        {
            uint32_t ef_key_slot_5_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_5_w3;

    /* 0x7C : EF_DATA_lock */
    union {
        struct
        {
            uint32_t ef_ana_trim_1        : 13; /* [12: 0],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_4_l : 1;  /* [   13],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_5_l : 1;  /* [   14],        r/w,        0x0 */
            uint32_t wr_lock_boot_mode    : 1;  /* [   15],        r/w,        0x0 */
            uint32_t wr_lock_dbg_pwd      : 1;  /* [   16],        r/w,        0x0 */
            uint32_t wr_lock_sw_usage_0   : 1;  /* [   17],        r/w,        0x0 */
            uint32_t wr_lock_wifi_mac     : 1;  /* [   18],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_0   : 1;  /* [   19],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_1   : 1;  /* [   20],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_2   : 1;  /* [   21],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_3   : 1;  /* [   22],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_4_h : 1;  /* [   23],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_5_h : 1;  /* [   24],        r/w,        0x0 */
            uint32_t rd_lock_dbg_pwd      : 1;  /* [   25],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_0   : 1;  /* [   26],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_1   : 1;  /* [   27],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_2   : 1;  /* [   28],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_3   : 1;  /* [   29],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_4   : 1;  /* [   30],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_5   : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } EF_DATA_lock;
};

typedef volatile struct EF_DATA_reg EF_DATA_reg_t;

#endif /* __EF_DATA_REG_H__ */
