/**
  ******************************************************************************
  * @file    ef_data_0_reg.h
  * @version V1.0
  * @date    2021-07-31
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
#ifndef __EF_DATA_0_REG_H__
#define __EF_DATA_0_REG_H__

#include "bl808.h"

/* 0x0 : ef_cfg_0 */
#define EF_DATA_0_EF_CFG_0_OFFSET         (0x0)
#define EF_DATA_0_EF_SF_AES_MODE          EF_DATA_0_EF_SF_AES_MODE
#define EF_DATA_0_EF_SF_AES_MODE_POS      (0U)
#define EF_DATA_0_EF_SF_AES_MODE_LEN      (2U)
#define EF_DATA_0_EF_SF_AES_MODE_MSK      (((1U << EF_DATA_0_EF_SF_AES_MODE_LEN) - 1) << EF_DATA_0_EF_SF_AES_MODE_POS)
#define EF_DATA_0_EF_SF_AES_MODE_UMSK     (~(((1U << EF_DATA_0_EF_SF_AES_MODE_LEN) - 1) << EF_DATA_0_EF_SF_AES_MODE_POS))
#define EF_DATA_0_EF_AI_DIS               EF_DATA_0_EF_AI_DIS
#define EF_DATA_0_EF_AI_DIS_POS           (2U)
#define EF_DATA_0_EF_AI_DIS_LEN           (1U)
#define EF_DATA_0_EF_AI_DIS_MSK           (((1U << EF_DATA_0_EF_AI_DIS_LEN) - 1) << EF_DATA_0_EF_AI_DIS_POS)
#define EF_DATA_0_EF_AI_DIS_UMSK          (~(((1U << EF_DATA_0_EF_AI_DIS_LEN) - 1) << EF_DATA_0_EF_AI_DIS_POS))
#define EF_DATA_0_EF_CPU0_DIS             EF_DATA_0_EF_CPU0_DIS
#define EF_DATA_0_EF_CPU0_DIS_POS         (3U)
#define EF_DATA_0_EF_CPU0_DIS_LEN         (1U)
#define EF_DATA_0_EF_CPU0_DIS_MSK         (((1U << EF_DATA_0_EF_CPU0_DIS_LEN) - 1) << EF_DATA_0_EF_CPU0_DIS_POS)
#define EF_DATA_0_EF_CPU0_DIS_UMSK        (~(((1U << EF_DATA_0_EF_CPU0_DIS_LEN) - 1) << EF_DATA_0_EF_CPU0_DIS_POS))
#define EF_DATA_0_EF_SBOOT_EN             EF_DATA_0_EF_SBOOT_EN
#define EF_DATA_0_EF_SBOOT_EN_POS         (4U)
#define EF_DATA_0_EF_SBOOT_EN_LEN         (2U)
#define EF_DATA_0_EF_SBOOT_EN_MSK         (((1U << EF_DATA_0_EF_SBOOT_EN_LEN) - 1) << EF_DATA_0_EF_SBOOT_EN_POS)
#define EF_DATA_0_EF_SBOOT_EN_UMSK        (~(((1U << EF_DATA_0_EF_SBOOT_EN_LEN) - 1) << EF_DATA_0_EF_SBOOT_EN_POS))
#define EF_DATA_0_EF_UART_DIS             EF_DATA_0_EF_UART_DIS
#define EF_DATA_0_EF_UART_DIS_POS         (6U)
#define EF_DATA_0_EF_UART_DIS_LEN         (4U)
#define EF_DATA_0_EF_UART_DIS_MSK         (((1U << EF_DATA_0_EF_UART_DIS_LEN) - 1) << EF_DATA_0_EF_UART_DIS_POS)
#define EF_DATA_0_EF_UART_DIS_UMSK        (~(((1U << EF_DATA_0_EF_UART_DIS_LEN) - 1) << EF_DATA_0_EF_UART_DIS_POS))
#define EF_DATA_0_EF_NO_XTAL              EF_DATA_0_EF_NO_XTAL
#define EF_DATA_0_EF_NO_XTAL_POS          (10U)
#define EF_DATA_0_EF_NO_XTAL_LEN          (1U)
#define EF_DATA_0_EF_NO_XTAL_MSK          (((1U << EF_DATA_0_EF_NO_XTAL_LEN) - 1) << EF_DATA_0_EF_NO_XTAL_POS)
#define EF_DATA_0_EF_NO_XTAL_UMSK         (~(((1U << EF_DATA_0_EF_NO_XTAL_LEN) - 1) << EF_DATA_0_EF_NO_XTAL_POS))
#define EF_DATA_0_EF_FORCE_NO_TRIM        EF_DATA_0_EF_FORCE_NO_TRIM
#define EF_DATA_0_EF_FORCE_NO_TRIM_POS    (11U)
#define EF_DATA_0_EF_FORCE_NO_TRIM_LEN    (1U)
#define EF_DATA_0_EF_FORCE_NO_TRIM_MSK    (((1U << EF_DATA_0_EF_FORCE_NO_TRIM_LEN) - 1) << EF_DATA_0_EF_FORCE_NO_TRIM_POS)
#define EF_DATA_0_EF_FORCE_NO_TRIM_UMSK   (~(((1U << EF_DATA_0_EF_FORCE_NO_TRIM_LEN) - 1) << EF_DATA_0_EF_FORCE_NO_TRIM_POS))
#define EF_DATA_0_EF_SF_KEY_RE_SEL        EF_DATA_0_EF_SF_KEY_RE_SEL
#define EF_DATA_0_EF_SF_KEY_RE_SEL_POS    (12U)
#define EF_DATA_0_EF_SF_KEY_RE_SEL_LEN    (2U)
#define EF_DATA_0_EF_SF_KEY_RE_SEL_MSK    (((1U << EF_DATA_0_EF_SF_KEY_RE_SEL_LEN) - 1) << EF_DATA_0_EF_SF_KEY_RE_SEL_POS)
#define EF_DATA_0_EF_SF_KEY_RE_SEL_UMSK   (~(((1U << EF_DATA_0_EF_SF_KEY_RE_SEL_LEN) - 1) << EF_DATA_0_EF_SF_KEY_RE_SEL_POS))
#define EF_DATA_0_EF_SDU_DIS              EF_DATA_0_EF_SDU_DIS
#define EF_DATA_0_EF_SDU_DIS_POS          (14U)
#define EF_DATA_0_EF_SDU_DIS_LEN          (1U)
#define EF_DATA_0_EF_SDU_DIS_MSK          (((1U << EF_DATA_0_EF_SDU_DIS_LEN) - 1) << EF_DATA_0_EF_SDU_DIS_POS)
#define EF_DATA_0_EF_SDU_DIS_UMSK         (~(((1U << EF_DATA_0_EF_SDU_DIS_LEN) - 1) << EF_DATA_0_EF_SDU_DIS_POS))
#define EF_DATA_0_EF_BTDM_DIS             EF_DATA_0_EF_BTDM_DIS
#define EF_DATA_0_EF_BTDM_DIS_POS         (15U)
#define EF_DATA_0_EF_BTDM_DIS_LEN         (1U)
#define EF_DATA_0_EF_BTDM_DIS_MSK         (((1U << EF_DATA_0_EF_BTDM_DIS_LEN) - 1) << EF_DATA_0_EF_BTDM_DIS_POS)
#define EF_DATA_0_EF_BTDM_DIS_UMSK        (~(((1U << EF_DATA_0_EF_BTDM_DIS_LEN) - 1) << EF_DATA_0_EF_BTDM_DIS_POS))
#define EF_DATA_0_EF_WIFI_DIS             EF_DATA_0_EF_WIFI_DIS
#define EF_DATA_0_EF_WIFI_DIS_POS         (16U)
#define EF_DATA_0_EF_WIFI_DIS_LEN         (1U)
#define EF_DATA_0_EF_WIFI_DIS_MSK         (((1U << EF_DATA_0_EF_WIFI_DIS_LEN) - 1) << EF_DATA_0_EF_WIFI_DIS_POS)
#define EF_DATA_0_EF_WIFI_DIS_UMSK        (~(((1U << EF_DATA_0_EF_WIFI_DIS_LEN) - 1) << EF_DATA_0_EF_WIFI_DIS_POS))
#define EF_DATA_0_EF_0_KEY_ENC_EN         EF_DATA_0_EF_0_KEY_ENC_EN
#define EF_DATA_0_EF_0_KEY_ENC_EN_POS     (17U)
#define EF_DATA_0_EF_0_KEY_ENC_EN_LEN     (1U)
#define EF_DATA_0_EF_0_KEY_ENC_EN_MSK     (((1U << EF_DATA_0_EF_0_KEY_ENC_EN_LEN) - 1) << EF_DATA_0_EF_0_KEY_ENC_EN_POS)
#define EF_DATA_0_EF_0_KEY_ENC_EN_UMSK    (~(((1U << EF_DATA_0_EF_0_KEY_ENC_EN_LEN) - 1) << EF_DATA_0_EF_0_KEY_ENC_EN_POS))
#define EF_DATA_0_EF_CAM_DIS              EF_DATA_0_EF_CAM_DIS
#define EF_DATA_0_EF_CAM_DIS_POS          (18U)
#define EF_DATA_0_EF_CAM_DIS_LEN          (1U)
#define EF_DATA_0_EF_CAM_DIS_MSK          (((1U << EF_DATA_0_EF_CAM_DIS_LEN) - 1) << EF_DATA_0_EF_CAM_DIS_POS)
#define EF_DATA_0_EF_CAM_DIS_UMSK         (~(((1U << EF_DATA_0_EF_CAM_DIS_LEN) - 1) << EF_DATA_0_EF_CAM_DIS_POS))
#define EF_DATA_0_EF_M154_DIS             EF_DATA_0_EF_M154_DIS
#define EF_DATA_0_EF_M154_DIS_POS         (19U)
#define EF_DATA_0_EF_M154_DIS_LEN         (1U)
#define EF_DATA_0_EF_M154_DIS_MSK         (((1U << EF_DATA_0_EF_M154_DIS_LEN) - 1) << EF_DATA_0_EF_M154_DIS_POS)
#define EF_DATA_0_EF_M154_DIS_UMSK        (~(((1U << EF_DATA_0_EF_M154_DIS_LEN) - 1) << EF_DATA_0_EF_M154_DIS_POS))
#define EF_DATA_0_EF_CPU1_DIS             EF_DATA_0_EF_CPU1_DIS
#define EF_DATA_0_EF_CPU1_DIS_POS         (20U)
#define EF_DATA_0_EF_CPU1_DIS_LEN         (1U)
#define EF_DATA_0_EF_CPU1_DIS_MSK         (((1U << EF_DATA_0_EF_CPU1_DIS_LEN) - 1) << EF_DATA_0_EF_CPU1_DIS_POS)
#define EF_DATA_0_EF_CPU1_DIS_UMSK        (~(((1U << EF_DATA_0_EF_CPU1_DIS_LEN) - 1) << EF_DATA_0_EF_CPU1_DIS_POS))
#define EF_DATA_0_EF_CPU_RST_DBG_DIS      EF_DATA_0_EF_CPU_RST_DBG_DIS
#define EF_DATA_0_EF_CPU_RST_DBG_DIS_POS  (21U)
#define EF_DATA_0_EF_CPU_RST_DBG_DIS_LEN  (1U)
#define EF_DATA_0_EF_CPU_RST_DBG_DIS_MSK  (((1U << EF_DATA_0_EF_CPU_RST_DBG_DIS_LEN) - 1) << EF_DATA_0_EF_CPU_RST_DBG_DIS_POS)
#define EF_DATA_0_EF_CPU_RST_DBG_DIS_UMSK (~(((1U << EF_DATA_0_EF_CPU_RST_DBG_DIS_LEN) - 1) << EF_DATA_0_EF_CPU_RST_DBG_DIS_POS))
#define EF_DATA_0_EF_SE_DBG_DIS           EF_DATA_0_EF_SE_DBG_DIS
#define EF_DATA_0_EF_SE_DBG_DIS_POS       (22U)
#define EF_DATA_0_EF_SE_DBG_DIS_LEN       (1U)
#define EF_DATA_0_EF_SE_DBG_DIS_MSK       (((1U << EF_DATA_0_EF_SE_DBG_DIS_LEN) - 1) << EF_DATA_0_EF_SE_DBG_DIS_POS)
#define EF_DATA_0_EF_SE_DBG_DIS_UMSK      (~(((1U << EF_DATA_0_EF_SE_DBG_DIS_LEN) - 1) << EF_DATA_0_EF_SE_DBG_DIS_POS))
#define EF_DATA_0_EF_EFUSE_DBG_DIS        EF_DATA_0_EF_EFUSE_DBG_DIS
#define EF_DATA_0_EF_EFUSE_DBG_DIS_POS    (23U)
#define EF_DATA_0_EF_EFUSE_DBG_DIS_LEN    (1U)
#define EF_DATA_0_EF_EFUSE_DBG_DIS_MSK    (((1U << EF_DATA_0_EF_EFUSE_DBG_DIS_LEN) - 1) << EF_DATA_0_EF_EFUSE_DBG_DIS_POS)
#define EF_DATA_0_EF_EFUSE_DBG_DIS_UMSK   (~(((1U << EF_DATA_0_EF_EFUSE_DBG_DIS_LEN) - 1) << EF_DATA_0_EF_EFUSE_DBG_DIS_POS))
#define EF_DATA_0_EF_DBG_JTAG_1_DIS       EF_DATA_0_EF_DBG_JTAG_1_DIS
#define EF_DATA_0_EF_DBG_JTAG_1_DIS_POS   (24U)
#define EF_DATA_0_EF_DBG_JTAG_1_DIS_LEN   (2U)
#define EF_DATA_0_EF_DBG_JTAG_1_DIS_MSK   (((1U << EF_DATA_0_EF_DBG_JTAG_1_DIS_LEN) - 1) << EF_DATA_0_EF_DBG_JTAG_1_DIS_POS)
#define EF_DATA_0_EF_DBG_JTAG_1_DIS_UMSK  (~(((1U << EF_DATA_0_EF_DBG_JTAG_1_DIS_LEN) - 1) << EF_DATA_0_EF_DBG_JTAG_1_DIS_POS))
#define EF_DATA_0_EF_DBG_JTAG_0_DIS       EF_DATA_0_EF_DBG_JTAG_0_DIS
#define EF_DATA_0_EF_DBG_JTAG_0_DIS_POS   (26U)
#define EF_DATA_0_EF_DBG_JTAG_0_DIS_LEN   (2U)
#define EF_DATA_0_EF_DBG_JTAG_0_DIS_MSK   (((1U << EF_DATA_0_EF_DBG_JTAG_0_DIS_LEN) - 1) << EF_DATA_0_EF_DBG_JTAG_0_DIS_POS)
#define EF_DATA_0_EF_DBG_JTAG_0_DIS_UMSK  (~(((1U << EF_DATA_0_EF_DBG_JTAG_0_DIS_LEN) - 1) << EF_DATA_0_EF_DBG_JTAG_0_DIS_POS))
#define EF_DATA_0_EF_DBG_MODE             EF_DATA_0_EF_DBG_MODE
#define EF_DATA_0_EF_DBG_MODE_POS         (28U)
#define EF_DATA_0_EF_DBG_MODE_LEN         (4U)
#define EF_DATA_0_EF_DBG_MODE_MSK         (((1U << EF_DATA_0_EF_DBG_MODE_LEN) - 1) << EF_DATA_0_EF_DBG_MODE_POS)
#define EF_DATA_0_EF_DBG_MODE_UMSK        (~(((1U << EF_DATA_0_EF_DBG_MODE_LEN) - 1) << EF_DATA_0_EF_DBG_MODE_POS))

/* 0x4 : ef_dbg_pwd_low */
#define EF_DATA_0_EF_DBG_PWD_LOW_OFFSET (0x4)
#define EF_DATA_0_EF_DBG_PWD_LOW        EF_DATA_0_EF_DBG_PWD_LOW
#define EF_DATA_0_EF_DBG_PWD_LOW_POS    (0U)
#define EF_DATA_0_EF_DBG_PWD_LOW_LEN    (32U)
#define EF_DATA_0_EF_DBG_PWD_LOW_MSK    (((1U << EF_DATA_0_EF_DBG_PWD_LOW_LEN) - 1) << EF_DATA_0_EF_DBG_PWD_LOW_POS)
#define EF_DATA_0_EF_DBG_PWD_LOW_UMSK   (~(((1U << EF_DATA_0_EF_DBG_PWD_LOW_LEN) - 1) << EF_DATA_0_EF_DBG_PWD_LOW_POS))

/* 0x8 : ef_dbg_pwd_high */
#define EF_DATA_0_EF_DBG_PWD_HIGH_OFFSET (0x8)
#define EF_DATA_0_EF_DBG_PWD_HIGH        EF_DATA_0_EF_DBG_PWD_HIGH
#define EF_DATA_0_EF_DBG_PWD_HIGH_POS    (0U)
#define EF_DATA_0_EF_DBG_PWD_HIGH_LEN    (32U)
#define EF_DATA_0_EF_DBG_PWD_HIGH_MSK    (((1U << EF_DATA_0_EF_DBG_PWD_HIGH_LEN) - 1) << EF_DATA_0_EF_DBG_PWD_HIGH_POS)
#define EF_DATA_0_EF_DBG_PWD_HIGH_UMSK   (~(((1U << EF_DATA_0_EF_DBG_PWD_HIGH_LEN) - 1) << EF_DATA_0_EF_DBG_PWD_HIGH_POS))

/* 0xC : ef_dbg_pwd2_low */
#define EF_DATA_0_EF_DBG_PWD2_LOW_OFFSET (0xC)
#define EF_DATA_0_EF_DBG_PWD2_LOW        EF_DATA_0_EF_DBG_PWD2_LOW
#define EF_DATA_0_EF_DBG_PWD2_LOW_POS    (0U)
#define EF_DATA_0_EF_DBG_PWD2_LOW_LEN    (32U)
#define EF_DATA_0_EF_DBG_PWD2_LOW_MSK    (((1U << EF_DATA_0_EF_DBG_PWD2_LOW_LEN) - 1) << EF_DATA_0_EF_DBG_PWD2_LOW_POS)
#define EF_DATA_0_EF_DBG_PWD2_LOW_UMSK   (~(((1U << EF_DATA_0_EF_DBG_PWD2_LOW_LEN) - 1) << EF_DATA_0_EF_DBG_PWD2_LOW_POS))

/* 0x10 : ef_dbg_pwd2_high */
#define EF_DATA_0_EF_DBG_PWD2_HIGH_OFFSET (0x10)
#define EF_DATA_0_EF_DBG_PWD2_HIGH        EF_DATA_0_EF_DBG_PWD2_HIGH
#define EF_DATA_0_EF_DBG_PWD2_HIGH_POS    (0U)
#define EF_DATA_0_EF_DBG_PWD2_HIGH_LEN    (32U)
#define EF_DATA_0_EF_DBG_PWD2_HIGH_MSK    (((1U << EF_DATA_0_EF_DBG_PWD2_HIGH_LEN) - 1) << EF_DATA_0_EF_DBG_PWD2_HIGH_POS)
#define EF_DATA_0_EF_DBG_PWD2_HIGH_UMSK   (~(((1U << EF_DATA_0_EF_DBG_PWD2_HIGH_LEN) - 1) << EF_DATA_0_EF_DBG_PWD2_HIGH_POS))

/* 0x14 : ef_wifi_mac_low */
#define EF_DATA_0_EF_WIFI_MAC_LOW_OFFSET (0x14)
#define EF_DATA_0_EF_WIFI_MAC_LOW        EF_DATA_0_EF_WIFI_MAC_LOW
#define EF_DATA_0_EF_WIFI_MAC_LOW_POS    (0U)
#define EF_DATA_0_EF_WIFI_MAC_LOW_LEN    (32U)
#define EF_DATA_0_EF_WIFI_MAC_LOW_MSK    (((1U << EF_DATA_0_EF_WIFI_MAC_LOW_LEN) - 1) << EF_DATA_0_EF_WIFI_MAC_LOW_POS)
#define EF_DATA_0_EF_WIFI_MAC_LOW_UMSK   (~(((1U << EF_DATA_0_EF_WIFI_MAC_LOW_LEN) - 1) << EF_DATA_0_EF_WIFI_MAC_LOW_POS))

/* 0x18 : ef_wifi_mac_high */
#define EF_DATA_0_EF_WIFI_MAC_HIGH_OFFSET (0x18)
#define EF_DATA_0_EF_WIFI_MAC_HIGH        EF_DATA_0_EF_WIFI_MAC_HIGH
#define EF_DATA_0_EF_WIFI_MAC_HIGH_POS    (0U)
#define EF_DATA_0_EF_WIFI_MAC_HIGH_LEN    (32U)
#define EF_DATA_0_EF_WIFI_MAC_HIGH_MSK    (((1U << EF_DATA_0_EF_WIFI_MAC_HIGH_LEN) - 1) << EF_DATA_0_EF_WIFI_MAC_HIGH_POS)
#define EF_DATA_0_EF_WIFI_MAC_HIGH_UMSK   (~(((1U << EF_DATA_0_EF_WIFI_MAC_HIGH_LEN) - 1) << EF_DATA_0_EF_WIFI_MAC_HIGH_POS))

/* 0x1C : ef_key_slot_0_w0 */
#define EF_DATA_0_EF_KEY_SLOT_0_W0_OFFSET (0x1C)
#define EF_DATA_0_EF_KEY_SLOT_0_W0        EF_DATA_0_EF_KEY_SLOT_0_W0
#define EF_DATA_0_EF_KEY_SLOT_0_W0_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_0_W0_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_0_W0_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_0_W0_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_0_W0_POS)
#define EF_DATA_0_EF_KEY_SLOT_0_W0_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_0_W0_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_0_W0_POS))

/* 0x20 : ef_key_slot_0_w1 */
#define EF_DATA_0_EF_KEY_SLOT_0_W1_OFFSET (0x20)
#define EF_DATA_0_EF_KEY_SLOT_0_W1        EF_DATA_0_EF_KEY_SLOT_0_W1
#define EF_DATA_0_EF_KEY_SLOT_0_W1_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_0_W1_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_0_W1_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_0_W1_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_0_W1_POS)
#define EF_DATA_0_EF_KEY_SLOT_0_W1_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_0_W1_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_0_W1_POS))

/* 0x24 : ef_key_slot_0_w2 */
#define EF_DATA_0_EF_KEY_SLOT_0_W2_OFFSET (0x24)
#define EF_DATA_0_EF_KEY_SLOT_0_W2        EF_DATA_0_EF_KEY_SLOT_0_W2
#define EF_DATA_0_EF_KEY_SLOT_0_W2_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_0_W2_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_0_W2_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_0_W2_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_0_W2_POS)
#define EF_DATA_0_EF_KEY_SLOT_0_W2_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_0_W2_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_0_W2_POS))

/* 0x28 : ef_key_slot_0_w3 */
#define EF_DATA_0_EF_KEY_SLOT_0_W3_OFFSET (0x28)
#define EF_DATA_0_EF_KEY_SLOT_0_W3        EF_DATA_0_EF_KEY_SLOT_0_W3
#define EF_DATA_0_EF_KEY_SLOT_0_W3_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_0_W3_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_0_W3_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_0_W3_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_0_W3_POS)
#define EF_DATA_0_EF_KEY_SLOT_0_W3_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_0_W3_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_0_W3_POS))

/* 0x2C : ef_key_slot_1_w0 */
#define EF_DATA_0_EF_KEY_SLOT_1_W0_OFFSET (0x2C)
#define EF_DATA_0_EF_KEY_SLOT_1_W0        EF_DATA_0_EF_KEY_SLOT_1_W0
#define EF_DATA_0_EF_KEY_SLOT_1_W0_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_1_W0_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_1_W0_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_1_W0_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_1_W0_POS)
#define EF_DATA_0_EF_KEY_SLOT_1_W0_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_1_W0_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_1_W0_POS))

/* 0x30 : ef_key_slot_1_w1 */
#define EF_DATA_0_EF_KEY_SLOT_1_W1_OFFSET (0x30)
#define EF_DATA_0_EF_KEY_SLOT_1_W1        EF_DATA_0_EF_KEY_SLOT_1_W1
#define EF_DATA_0_EF_KEY_SLOT_1_W1_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_1_W1_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_1_W1_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_1_W1_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_1_W1_POS)
#define EF_DATA_0_EF_KEY_SLOT_1_W1_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_1_W1_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_1_W1_POS))

/* 0x34 : ef_key_slot_1_w2 */
#define EF_DATA_0_EF_KEY_SLOT_1_W2_OFFSET (0x34)
#define EF_DATA_0_EF_KEY_SLOT_1_W2        EF_DATA_0_EF_KEY_SLOT_1_W2
#define EF_DATA_0_EF_KEY_SLOT_1_W2_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_1_W2_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_1_W2_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_1_W2_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_1_W2_POS)
#define EF_DATA_0_EF_KEY_SLOT_1_W2_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_1_W2_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_1_W2_POS))

/* 0x38 : ef_key_slot_1_w3 */
#define EF_DATA_0_EF_KEY_SLOT_1_W3_OFFSET (0x38)
#define EF_DATA_0_EF_KEY_SLOT_1_W3        EF_DATA_0_EF_KEY_SLOT_1_W3
#define EF_DATA_0_EF_KEY_SLOT_1_W3_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_1_W3_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_1_W3_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_1_W3_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_1_W3_POS)
#define EF_DATA_0_EF_KEY_SLOT_1_W3_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_1_W3_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_1_W3_POS))

/* 0x3C : ef_key_slot_2_w0 */
#define EF_DATA_0_EF_KEY_SLOT_2_W0_OFFSET (0x3C)
#define EF_DATA_0_EF_KEY_SLOT_2_W0        EF_DATA_0_EF_KEY_SLOT_2_W0
#define EF_DATA_0_EF_KEY_SLOT_2_W0_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_2_W0_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_2_W0_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_2_W0_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_2_W0_POS)
#define EF_DATA_0_EF_KEY_SLOT_2_W0_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_2_W0_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_2_W0_POS))

/* 0x40 : ef_key_slot_2_w1 */
#define EF_DATA_0_EF_KEY_SLOT_2_W1_OFFSET (0x40)
#define EF_DATA_0_EF_KEY_SLOT_2_W1        EF_DATA_0_EF_KEY_SLOT_2_W1
#define EF_DATA_0_EF_KEY_SLOT_2_W1_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_2_W1_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_2_W1_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_2_W1_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_2_W1_POS)
#define EF_DATA_0_EF_KEY_SLOT_2_W1_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_2_W1_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_2_W1_POS))

/* 0x44 : ef_key_slot_2_w2 */
#define EF_DATA_0_EF_KEY_SLOT_2_W2_OFFSET (0x44)
#define EF_DATA_0_EF_KEY_SLOT_2_W2        EF_DATA_0_EF_KEY_SLOT_2_W2
#define EF_DATA_0_EF_KEY_SLOT_2_W2_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_2_W2_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_2_W2_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_2_W2_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_2_W2_POS)
#define EF_DATA_0_EF_KEY_SLOT_2_W2_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_2_W2_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_2_W2_POS))

/* 0x48 : ef_key_slot_2_w3 */
#define EF_DATA_0_EF_KEY_SLOT_2_W3_OFFSET (0x48)
#define EF_DATA_0_EF_KEY_SLOT_2_W3        EF_DATA_0_EF_KEY_SLOT_2_W3
#define EF_DATA_0_EF_KEY_SLOT_2_W3_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_2_W3_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_2_W3_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_2_W3_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_2_W3_POS)
#define EF_DATA_0_EF_KEY_SLOT_2_W3_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_2_W3_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_2_W3_POS))

/* 0x4C : ef_key_slot_3_w0 */
#define EF_DATA_0_EF_KEY_SLOT_3_W0_OFFSET (0x4C)
#define EF_DATA_0_EF_KEY_SLOT_3_W0        EF_DATA_0_EF_KEY_SLOT_3_W0
#define EF_DATA_0_EF_KEY_SLOT_3_W0_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_3_W0_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_3_W0_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_3_W0_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_3_W0_POS)
#define EF_DATA_0_EF_KEY_SLOT_3_W0_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_3_W0_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_3_W0_POS))

/* 0x50 : ef_key_slot_3_w1 */
#define EF_DATA_0_EF_KEY_SLOT_3_W1_OFFSET (0x50)
#define EF_DATA_0_EF_KEY_SLOT_3_W1        EF_DATA_0_EF_KEY_SLOT_3_W1
#define EF_DATA_0_EF_KEY_SLOT_3_W1_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_3_W1_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_3_W1_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_3_W1_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_3_W1_POS)
#define EF_DATA_0_EF_KEY_SLOT_3_W1_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_3_W1_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_3_W1_POS))

/* 0x54 : ef_key_slot_3_w2 */
#define EF_DATA_0_EF_KEY_SLOT_3_W2_OFFSET (0x54)
#define EF_DATA_0_EF_KEY_SLOT_3_W2        EF_DATA_0_EF_KEY_SLOT_3_W2
#define EF_DATA_0_EF_KEY_SLOT_3_W2_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_3_W2_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_3_W2_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_3_W2_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_3_W2_POS)
#define EF_DATA_0_EF_KEY_SLOT_3_W2_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_3_W2_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_3_W2_POS))

/* 0x58 : ef_key_slot_3_w3 */
#define EF_DATA_0_EF_KEY_SLOT_3_W3_OFFSET (0x58)
#define EF_DATA_0_EF_KEY_SLOT_3_W3        EF_DATA_0_EF_KEY_SLOT_3_W3
#define EF_DATA_0_EF_KEY_SLOT_3_W3_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_3_W3_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_3_W3_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_3_W3_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_3_W3_POS)
#define EF_DATA_0_EF_KEY_SLOT_3_W3_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_3_W3_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_3_W3_POS))

/* 0x5C : ef_sw_usage_0 */
#define EF_DATA_0_EF_SW_USAGE_0_OFFSET (0x5C)
#define EF_DATA_0_EF_SW_USAGE_0        EF_DATA_0_EF_SW_USAGE_0
#define EF_DATA_0_EF_SW_USAGE_0_POS    (0U)
#define EF_DATA_0_EF_SW_USAGE_0_LEN    (32U)
#define EF_DATA_0_EF_SW_USAGE_0_MSK    (((1U << EF_DATA_0_EF_SW_USAGE_0_LEN) - 1) << EF_DATA_0_EF_SW_USAGE_0_POS)
#define EF_DATA_0_EF_SW_USAGE_0_UMSK   (~(((1U << EF_DATA_0_EF_SW_USAGE_0_LEN) - 1) << EF_DATA_0_EF_SW_USAGE_0_POS))

#define EF_DATA_0_EF_SBOOT_SIGN_MODE      EF_DATA_0_EF_SBOOT_SIGN_MODE
#define EF_DATA_0_EF_SBOOT_SIGN_MODE_POS  (8U)
#define EF_DATA_0_EF_SBOOT_SIGN_MODE_LEN  (2U)
#define EF_DATA_0_EF_SBOOT_SIGN_MODE_MSK  (((1U << EF_DATA_0_EF_SBOOT_SIGN_MODE_LEN) - 1) << EF_DATA_0_EF_SBOOT_SIGN_MODE_POS)
#define EF_DATA_0_EF_SBOOT_SIGN_MODE_UMSK (~(((1U << EF_DATA_0_EF_SBOOT_SIGN_MODE_LEN) - 1) << EF_DATA_0_EF_SBOOT_SIGN_MODE_POS))

/* 0x60 : ef_sw_usage_1 */
#define EF_DATA_0_EF_SW_USAGE_1_OFFSET (0x60)
#define EF_DATA_0_EF_SW_USAGE_1        EF_DATA_0_EF_SW_USAGE_1
#define EF_DATA_0_EF_SW_USAGE_1_POS    (0U)
#define EF_DATA_0_EF_SW_USAGE_1_LEN    (32U)
#define EF_DATA_0_EF_SW_USAGE_1_MSK    (((1U << EF_DATA_0_EF_SW_USAGE_1_LEN) - 1) << EF_DATA_0_EF_SW_USAGE_1_POS)
#define EF_DATA_0_EF_SW_USAGE_1_UMSK   (~(((1U << EF_DATA_0_EF_SW_USAGE_1_LEN) - 1) << EF_DATA_0_EF_SW_USAGE_1_POS))

/* 0x64 : ef_sw_usage_2 */
#define EF_DATA_0_EF_SW_USAGE_2_OFFSET (0x64)
#define EF_DATA_0_EF_SW_USAGE_2        EF_DATA_0_EF_SW_USAGE_2
#define EF_DATA_0_EF_SW_USAGE_2_POS    (0U)
#define EF_DATA_0_EF_SW_USAGE_2_LEN    (32U)
#define EF_DATA_0_EF_SW_USAGE_2_MSK    (((1U << EF_DATA_0_EF_SW_USAGE_2_LEN) - 1) << EF_DATA_0_EF_SW_USAGE_2_POS)
#define EF_DATA_0_EF_SW_USAGE_2_UMSK   (~(((1U << EF_DATA_0_EF_SW_USAGE_2_LEN) - 1) << EF_DATA_0_EF_SW_USAGE_2_POS))

/* 0x68 : ef_sw_usage_3 */
#define EF_DATA_0_EF_SW_USAGE_3_OFFSET (0x68)
#define EF_DATA_0_EF_SW_USAGE_3        EF_DATA_0_EF_SW_USAGE_3
#define EF_DATA_0_EF_SW_USAGE_3_POS    (0U)
#define EF_DATA_0_EF_SW_USAGE_3_LEN    (32U)
#define EF_DATA_0_EF_SW_USAGE_3_MSK    (((1U << EF_DATA_0_EF_SW_USAGE_3_LEN) - 1) << EF_DATA_0_EF_SW_USAGE_3_POS)
#define EF_DATA_0_EF_SW_USAGE_3_UMSK   (~(((1U << EF_DATA_0_EF_SW_USAGE_3_LEN) - 1) << EF_DATA_0_EF_SW_USAGE_3_POS))

/* 0x6C : ef_key_slot_11_w0 */
#define EF_DATA_0_EF_KEY_SLOT_11_W0_OFFSET (0x6C)
#define EF_DATA_0_EF_KEY_SLOT_11_W0        EF_DATA_0_EF_KEY_SLOT_11_W0
#define EF_DATA_0_EF_KEY_SLOT_11_W0_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_11_W0_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_11_W0_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_11_W0_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_11_W0_POS)
#define EF_DATA_0_EF_KEY_SLOT_11_W0_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_11_W0_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_11_W0_POS))

/* 0x70 : ef_key_slot_11_w1 */
#define EF_DATA_0_EF_KEY_SLOT_11_W1_OFFSET (0x70)
#define EF_DATA_0_EF_KEY_SLOT_11_W1        EF_DATA_0_EF_KEY_SLOT_11_W1
#define EF_DATA_0_EF_KEY_SLOT_11_W1_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_11_W1_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_11_W1_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_11_W1_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_11_W1_POS)
#define EF_DATA_0_EF_KEY_SLOT_11_W1_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_11_W1_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_11_W1_POS))

/* 0x74 : ef_key_slot_11_w2 */
#define EF_DATA_0_EF_KEY_SLOT_11_W2_OFFSET (0x74)
#define EF_DATA_0_EF_KEY_SLOT_11_W2        EF_DATA_0_EF_KEY_SLOT_11_W2
#define EF_DATA_0_EF_KEY_SLOT_11_W2_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_11_W2_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_11_W2_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_11_W2_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_11_W2_POS)
#define EF_DATA_0_EF_KEY_SLOT_11_W2_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_11_W2_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_11_W2_POS))

/* 0x78 : ef_key_slot_11_w3 */
#define EF_DATA_0_EF_KEY_SLOT_11_W3_OFFSET (0x78)
#define EF_DATA_0_EF_KEY_SLOT_11_W3        EF_DATA_0_EF_KEY_SLOT_11_W3
#define EF_DATA_0_EF_KEY_SLOT_11_W3_POS    (0U)
#define EF_DATA_0_EF_KEY_SLOT_11_W3_LEN    (32U)
#define EF_DATA_0_EF_KEY_SLOT_11_W3_MSK    (((1U << EF_DATA_0_EF_KEY_SLOT_11_W3_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_11_W3_POS)
#define EF_DATA_0_EF_KEY_SLOT_11_W3_UMSK   (~(((1U << EF_DATA_0_EF_KEY_SLOT_11_W3_LEN) - 1) << EF_DATA_0_EF_KEY_SLOT_11_W3_POS))

/* 0x7C : ef_data_0_lock */
#define EF_DATA_0_LOCK_OFFSET              (0x7C)
#define EF_DATA_0_EF_SEC_LIFECYCLE         EF_DATA_0_EF_SEC_LIFECYCLE
#define EF_DATA_0_EF_SEC_LIFECYCLE_POS     (0U)
#define EF_DATA_0_EF_SEC_LIFECYCLE_LEN     (4U)
#define EF_DATA_0_EF_SEC_LIFECYCLE_MSK     (((1U << EF_DATA_0_EF_SEC_LIFECYCLE_LEN) - 1) << EF_DATA_0_EF_SEC_LIFECYCLE_POS)
#define EF_DATA_0_EF_SEC_LIFECYCLE_UMSK    (~(((1U << EF_DATA_0_EF_SEC_LIFECYCLE_LEN) - 1) << EF_DATA_0_EF_SEC_LIFECYCLE_POS))
#define EF_DATA_0_WR_LOCK_RSVD_0           EF_DATA_0_WR_LOCK_RSVD_0
#define EF_DATA_0_WR_LOCK_RSVD_0_POS       (4U)
#define EF_DATA_0_WR_LOCK_RSVD_0_LEN       (10U)
#define EF_DATA_0_WR_LOCK_RSVD_0_MSK       (((1U << EF_DATA_0_WR_LOCK_RSVD_0_LEN) - 1) << EF_DATA_0_WR_LOCK_RSVD_0_POS)
#define EF_DATA_0_WR_LOCK_RSVD_0_UMSK      (~(((1U << EF_DATA_0_WR_LOCK_RSVD_0_LEN) - 1) << EF_DATA_0_WR_LOCK_RSVD_0_POS))
#define EF_DATA_0_WR_LOCK_BOOT_MODE        EF_DATA_0_WR_LOCK_BOOT_MODE
#define EF_DATA_0_WR_LOCK_BOOT_MODE_POS    (14U)
#define EF_DATA_0_WR_LOCK_BOOT_MODE_LEN    (1U)
#define EF_DATA_0_WR_LOCK_BOOT_MODE_MSK    (((1U << EF_DATA_0_WR_LOCK_BOOT_MODE_LEN) - 1) << EF_DATA_0_WR_LOCK_BOOT_MODE_POS)
#define EF_DATA_0_WR_LOCK_BOOT_MODE_UMSK   (~(((1U << EF_DATA_0_WR_LOCK_BOOT_MODE_LEN) - 1) << EF_DATA_0_WR_LOCK_BOOT_MODE_POS))
#define EF_DATA_0_WR_LOCK_DBG_PWD          EF_DATA_0_WR_LOCK_DBG_PWD
#define EF_DATA_0_WR_LOCK_DBG_PWD_POS      (15U)
#define EF_DATA_0_WR_LOCK_DBG_PWD_LEN      (1U)
#define EF_DATA_0_WR_LOCK_DBG_PWD_MSK      (((1U << EF_DATA_0_WR_LOCK_DBG_PWD_LEN) - 1) << EF_DATA_0_WR_LOCK_DBG_PWD_POS)
#define EF_DATA_0_WR_LOCK_DBG_PWD_UMSK     (~(((1U << EF_DATA_0_WR_LOCK_DBG_PWD_LEN) - 1) << EF_DATA_0_WR_LOCK_DBG_PWD_POS))
#define EF_DATA_0_WR_LOCK_WIFI_MAC         EF_DATA_0_WR_LOCK_WIFI_MAC
#define EF_DATA_0_WR_LOCK_WIFI_MAC_POS     (16U)
#define EF_DATA_0_WR_LOCK_WIFI_MAC_LEN     (1U)
#define EF_DATA_0_WR_LOCK_WIFI_MAC_MSK     (((1U << EF_DATA_0_WR_LOCK_WIFI_MAC_LEN) - 1) << EF_DATA_0_WR_LOCK_WIFI_MAC_POS)
#define EF_DATA_0_WR_LOCK_WIFI_MAC_UMSK    (~(((1U << EF_DATA_0_WR_LOCK_WIFI_MAC_LEN) - 1) << EF_DATA_0_WR_LOCK_WIFI_MAC_POS))
#define EF_DATA_0_WR_LOCK_KEY_SLOT_0       EF_DATA_0_WR_LOCK_KEY_SLOT_0
#define EF_DATA_0_WR_LOCK_KEY_SLOT_0_POS   (17U)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_0_LEN   (1U)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_0_MSK   (((1U << EF_DATA_0_WR_LOCK_KEY_SLOT_0_LEN) - 1) << EF_DATA_0_WR_LOCK_KEY_SLOT_0_POS)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_0_UMSK  (~(((1U << EF_DATA_0_WR_LOCK_KEY_SLOT_0_LEN) - 1) << EF_DATA_0_WR_LOCK_KEY_SLOT_0_POS))
#define EF_DATA_0_WR_LOCK_KEY_SLOT_1       EF_DATA_0_WR_LOCK_KEY_SLOT_1
#define EF_DATA_0_WR_LOCK_KEY_SLOT_1_POS   (18U)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_1_LEN   (1U)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_1_MSK   (((1U << EF_DATA_0_WR_LOCK_KEY_SLOT_1_LEN) - 1) << EF_DATA_0_WR_LOCK_KEY_SLOT_1_POS)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_1_UMSK  (~(((1U << EF_DATA_0_WR_LOCK_KEY_SLOT_1_LEN) - 1) << EF_DATA_0_WR_LOCK_KEY_SLOT_1_POS))
#define EF_DATA_0_WR_LOCK_KEY_SLOT_2       EF_DATA_0_WR_LOCK_KEY_SLOT_2
#define EF_DATA_0_WR_LOCK_KEY_SLOT_2_POS   (19U)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_2_LEN   (1U)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_2_MSK   (((1U << EF_DATA_0_WR_LOCK_KEY_SLOT_2_LEN) - 1) << EF_DATA_0_WR_LOCK_KEY_SLOT_2_POS)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_2_UMSK  (~(((1U << EF_DATA_0_WR_LOCK_KEY_SLOT_2_LEN) - 1) << EF_DATA_0_WR_LOCK_KEY_SLOT_2_POS))
#define EF_DATA_0_WR_LOCK_KEY_SLOT_3       EF_DATA_0_WR_LOCK_KEY_SLOT_3
#define EF_DATA_0_WR_LOCK_KEY_SLOT_3_POS   (20U)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_3_LEN   (1U)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_3_MSK   (((1U << EF_DATA_0_WR_LOCK_KEY_SLOT_3_LEN) - 1) << EF_DATA_0_WR_LOCK_KEY_SLOT_3_POS)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_3_UMSK  (~(((1U << EF_DATA_0_WR_LOCK_KEY_SLOT_3_LEN) - 1) << EF_DATA_0_WR_LOCK_KEY_SLOT_3_POS))
#define EF_DATA_0_WR_LOCK_SW_USAGE_0       EF_DATA_0_WR_LOCK_SW_USAGE_0
#define EF_DATA_0_WR_LOCK_SW_USAGE_0_POS   (21U)
#define EF_DATA_0_WR_LOCK_SW_USAGE_0_LEN   (1U)
#define EF_DATA_0_WR_LOCK_SW_USAGE_0_MSK   (((1U << EF_DATA_0_WR_LOCK_SW_USAGE_0_LEN) - 1) << EF_DATA_0_WR_LOCK_SW_USAGE_0_POS)
#define EF_DATA_0_WR_LOCK_SW_USAGE_0_UMSK  (~(((1U << EF_DATA_0_WR_LOCK_SW_USAGE_0_LEN) - 1) << EF_DATA_0_WR_LOCK_SW_USAGE_0_POS))
#define EF_DATA_0_WR_LOCK_SW_USAGE_1       EF_DATA_0_WR_LOCK_SW_USAGE_1
#define EF_DATA_0_WR_LOCK_SW_USAGE_1_POS   (22U)
#define EF_DATA_0_WR_LOCK_SW_USAGE_1_LEN   (1U)
#define EF_DATA_0_WR_LOCK_SW_USAGE_1_MSK   (((1U << EF_DATA_0_WR_LOCK_SW_USAGE_1_LEN) - 1) << EF_DATA_0_WR_LOCK_SW_USAGE_1_POS)
#define EF_DATA_0_WR_LOCK_SW_USAGE_1_UMSK  (~(((1U << EF_DATA_0_WR_LOCK_SW_USAGE_1_LEN) - 1) << EF_DATA_0_WR_LOCK_SW_USAGE_1_POS))
#define EF_DATA_0_WR_LOCK_SW_USAGE_2       EF_DATA_0_WR_LOCK_SW_USAGE_2
#define EF_DATA_0_WR_LOCK_SW_USAGE_2_POS   (23U)
#define EF_DATA_0_WR_LOCK_SW_USAGE_2_LEN   (1U)
#define EF_DATA_0_WR_LOCK_SW_USAGE_2_MSK   (((1U << EF_DATA_0_WR_LOCK_SW_USAGE_2_LEN) - 1) << EF_DATA_0_WR_LOCK_SW_USAGE_2_POS)
#define EF_DATA_0_WR_LOCK_SW_USAGE_2_UMSK  (~(((1U << EF_DATA_0_WR_LOCK_SW_USAGE_2_LEN) - 1) << EF_DATA_0_WR_LOCK_SW_USAGE_2_POS))
#define EF_DATA_0_WR_LOCK_SW_USAGE_3       EF_DATA_0_WR_LOCK_SW_USAGE_3
#define EF_DATA_0_WR_LOCK_SW_USAGE_3_POS   (24U)
#define EF_DATA_0_WR_LOCK_SW_USAGE_3_LEN   (1U)
#define EF_DATA_0_WR_LOCK_SW_USAGE_3_MSK   (((1U << EF_DATA_0_WR_LOCK_SW_USAGE_3_LEN) - 1) << EF_DATA_0_WR_LOCK_SW_USAGE_3_POS)
#define EF_DATA_0_WR_LOCK_SW_USAGE_3_UMSK  (~(((1U << EF_DATA_0_WR_LOCK_SW_USAGE_3_LEN) - 1) << EF_DATA_0_WR_LOCK_SW_USAGE_3_POS))
#define EF_DATA_0_WR_LOCK_KEY_SLOT_11      EF_DATA_0_WR_LOCK_KEY_SLOT_11
#define EF_DATA_0_WR_LOCK_KEY_SLOT_11_POS  (25U)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_11_LEN  (1U)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_11_MSK  (((1U << EF_DATA_0_WR_LOCK_KEY_SLOT_11_LEN) - 1) << EF_DATA_0_WR_LOCK_KEY_SLOT_11_POS)
#define EF_DATA_0_WR_LOCK_KEY_SLOT_11_UMSK (~(((1U << EF_DATA_0_WR_LOCK_KEY_SLOT_11_LEN) - 1) << EF_DATA_0_WR_LOCK_KEY_SLOT_11_POS))
#define EF_DATA_0_RD_LOCK_DBG_PWD          EF_DATA_0_RD_LOCK_DBG_PWD
#define EF_DATA_0_RD_LOCK_DBG_PWD_POS      (26U)
#define EF_DATA_0_RD_LOCK_DBG_PWD_LEN      (1U)
#define EF_DATA_0_RD_LOCK_DBG_PWD_MSK      (((1U << EF_DATA_0_RD_LOCK_DBG_PWD_LEN) - 1) << EF_DATA_0_RD_LOCK_DBG_PWD_POS)
#define EF_DATA_0_RD_LOCK_DBG_PWD_UMSK     (~(((1U << EF_DATA_0_RD_LOCK_DBG_PWD_LEN) - 1) << EF_DATA_0_RD_LOCK_DBG_PWD_POS))
#define EF_DATA_0_RD_LOCK_KEY_SLOT_0       EF_DATA_0_RD_LOCK_KEY_SLOT_0
#define EF_DATA_0_RD_LOCK_KEY_SLOT_0_POS   (27U)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_0_LEN   (1U)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_0_MSK   (((1U << EF_DATA_0_RD_LOCK_KEY_SLOT_0_LEN) - 1) << EF_DATA_0_RD_LOCK_KEY_SLOT_0_POS)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_0_UMSK  (~(((1U << EF_DATA_0_RD_LOCK_KEY_SLOT_0_LEN) - 1) << EF_DATA_0_RD_LOCK_KEY_SLOT_0_POS))
#define EF_DATA_0_RD_LOCK_KEY_SLOT_1       EF_DATA_0_RD_LOCK_KEY_SLOT_1
#define EF_DATA_0_RD_LOCK_KEY_SLOT_1_POS   (28U)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_1_LEN   (1U)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_1_MSK   (((1U << EF_DATA_0_RD_LOCK_KEY_SLOT_1_LEN) - 1) << EF_DATA_0_RD_LOCK_KEY_SLOT_1_POS)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_1_UMSK  (~(((1U << EF_DATA_0_RD_LOCK_KEY_SLOT_1_LEN) - 1) << EF_DATA_0_RD_LOCK_KEY_SLOT_1_POS))
#define EF_DATA_0_RD_LOCK_KEY_SLOT_2       EF_DATA_0_RD_LOCK_KEY_SLOT_2
#define EF_DATA_0_RD_LOCK_KEY_SLOT_2_POS   (29U)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_2_LEN   (1U)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_2_MSK   (((1U << EF_DATA_0_RD_LOCK_KEY_SLOT_2_LEN) - 1) << EF_DATA_0_RD_LOCK_KEY_SLOT_2_POS)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_2_UMSK  (~(((1U << EF_DATA_0_RD_LOCK_KEY_SLOT_2_LEN) - 1) << EF_DATA_0_RD_LOCK_KEY_SLOT_2_POS))
#define EF_DATA_0_RD_LOCK_KEY_SLOT_3       EF_DATA_0_RD_LOCK_KEY_SLOT_3
#define EF_DATA_0_RD_LOCK_KEY_SLOT_3_POS   (30U)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_3_LEN   (1U)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_3_MSK   (((1U << EF_DATA_0_RD_LOCK_KEY_SLOT_3_LEN) - 1) << EF_DATA_0_RD_LOCK_KEY_SLOT_3_POS)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_3_UMSK  (~(((1U << EF_DATA_0_RD_LOCK_KEY_SLOT_3_LEN) - 1) << EF_DATA_0_RD_LOCK_KEY_SLOT_3_POS))
#define EF_DATA_0_RD_LOCK_KEY_SLOT_11      EF_DATA_0_RD_LOCK_KEY_SLOT_11
#define EF_DATA_0_RD_LOCK_KEY_SLOT_11_POS  (31U)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_11_LEN  (1U)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_11_MSK  (((1U << EF_DATA_0_RD_LOCK_KEY_SLOT_11_LEN) - 1) << EF_DATA_0_RD_LOCK_KEY_SLOT_11_POS)
#define EF_DATA_0_RD_LOCK_KEY_SLOT_11_UMSK (~(((1U << EF_DATA_0_RD_LOCK_KEY_SLOT_11_LEN) - 1) << EF_DATA_0_RD_LOCK_KEY_SLOT_11_POS))

struct ef_data_0_reg {
    /* 0x0 : ef_cfg_0 */
    union {
        struct {
            uint32_t ef_sf_aes_mode     : 2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t ef_ai_dis          : 1; /* [    2],        r/w,        0x0 */
            uint32_t ef_cpu0_dis        : 1; /* [    3],        r/w,        0x0 */
            uint32_t ef_sboot_en        : 2; /* [ 5: 4],        r/w,        0x0 */
            uint32_t ef_uart_dis        : 4; /* [ 9: 6],        r/w,        0x0 */
            uint32_t ef_ble2_dis        : 1; /* [   10],        r/w,        0x0 */
            uint32_t ef_m1542_dis       : 1; /* [   11],        r/w,        0x0 */
            uint32_t ef_sf_key_re_sel   : 2; /* [13:12],        r/w,        0x0 */
            uint32_t ef_sdu_dis         : 1; /* [   14],        r/w,        0x0 */
            uint32_t ef_btdm_dis        : 1; /* [   15],        r/w,        0x0 */
            uint32_t ef_wifi_dis        : 1; /* [   16],        r/w,        0x0 */
            uint32_t ef_0_key_enc_en    : 1; /* [   17],        r/w,        0x0 */
            uint32_t ef_cam_dis         : 1; /* [   18],        r/w,        0x0 */
            uint32_t ef_m154_dis        : 1; /* [   19],        r/w,        0x0 */
            uint32_t ef_cpu1_dis        : 1; /* [   20],        r/w,        0x0 */
            uint32_t ef_cpu_rst_dbg_dis : 1; /* [   21],        r/w,        0x0 */
            uint32_t ef_se_dbg_dis      : 1; /* [   22],        r/w,        0x0 */
            uint32_t ef_efuse_dbg_dis   : 1; /* [   23],        r/w,        0x0 */
            uint32_t ef_dbg_jtag_1_dis  : 2; /* [25:24],        r/w,        0x0 */
            uint32_t ef_dbg_jtag_0_dis  : 2; /* [27:26],        r/w,        0x0 */
            uint32_t ef_dbg_mode        : 4; /* [31:28],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_cfg_0;

    /* 0x4 : ef_dbg_pwd_low */
    union {
        struct {
            uint32_t ef_dbg_pwd_low : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_dbg_pwd_low;

    /* 0x8 : ef_dbg_pwd_high */
    union {
        struct {
            uint32_t ef_dbg_pwd_high : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_dbg_pwd_high;

    /* 0xC : ef_dbg_pwd2_low */
    union {
        struct {
            uint32_t ef_dbg_pwd2_low : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_dbg_pwd2_low;

    /* 0x10 : ef_dbg_pwd2_high */
    union {
        struct {
            uint32_t ef_dbg_pwd2_high : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_dbg_pwd2_high;

    /* 0x14 : ef_wifi_mac_low */
    union {
        struct {
            uint32_t ef_wifi_mac_low : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_wifi_mac_low;

    /* 0x18 : ef_wifi_mac_high */
    union {
        struct {
            uint32_t ef_wifi_mac_high : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_wifi_mac_high;

    /* 0x1C : ef_key_slot_0_w0 */
    union {
        struct {
            uint32_t ef_key_slot_0_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_0_w0;

    /* 0x20 : ef_key_slot_0_w1 */
    union {
        struct {
            uint32_t ef_key_slot_0_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_0_w1;

    /* 0x24 : ef_key_slot_0_w2 */
    union {
        struct {
            uint32_t ef_key_slot_0_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_0_w2;

    /* 0x28 : ef_key_slot_0_w3 */
    union {
        struct {
            uint32_t ef_key_slot_0_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_0_w3;

    /* 0x2C : ef_key_slot_1_w0 */
    union {
        struct {
            uint32_t ef_key_slot_1_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_1_w0;

    /* 0x30 : ef_key_slot_1_w1 */
    union {
        struct {
            uint32_t ef_key_slot_1_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_1_w1;

    /* 0x34 : ef_key_slot_1_w2 */
    union {
        struct {
            uint32_t ef_key_slot_1_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_1_w2;

    /* 0x38 : ef_key_slot_1_w3 */
    union {
        struct {
            uint32_t ef_key_slot_1_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_1_w3;

    /* 0x3C : ef_key_slot_2_w0 */
    union {
        struct {
            uint32_t ef_key_slot_2_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_2_w0;

    /* 0x40 : ef_key_slot_2_w1 */
    union {
        struct {
            uint32_t ef_key_slot_2_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_2_w1;

    /* 0x44 : ef_key_slot_2_w2 */
    union {
        struct {
            uint32_t ef_key_slot_2_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_2_w2;

    /* 0x48 : ef_key_slot_2_w3 */
    union {
        struct {
            uint32_t ef_key_slot_2_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_2_w3;

    /* 0x4C : ef_key_slot_3_w0 */
    union {
        struct {
            uint32_t ef_key_slot_3_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_3_w0;

    /* 0x50 : ef_key_slot_3_w1 */
    union {
        struct {
            uint32_t ef_key_slot_3_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_3_w1;

    /* 0x54 : ef_key_slot_3_w2 */
    union {
        struct {
            uint32_t ef_key_slot_3_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_3_w2;

    /* 0x58 : ef_key_slot_3_w3 */
    union {
        struct {
            uint32_t ef_key_slot_3_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_3_w3;

    /* 0x5C : ef_sw_usage_0 */
    union {
        struct {
            uint32_t ef_sw_usage_0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_sw_usage_0;

    /* 0x60 : ef_sw_usage_1 */
    union {
        struct {
            uint32_t ef_sw_usage_1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_sw_usage_1;

    /* 0x64 : ef_sw_usage_2 */
    union {
        struct {
            uint32_t ef_sw_usage_2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_sw_usage_2;

    /* 0x68 : ef_sw_usage_3 */
    union {
        struct {
            uint32_t ef_sw_usage_3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_sw_usage_3;

    /* 0x6C : ef_key_slot_11_w0 */
    union {
        struct {
            uint32_t ef_key_slot_11_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_11_w0;

    /* 0x70 : ef_key_slot_11_w1 */
    union {
        struct {
            uint32_t ef_key_slot_11_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_11_w1;

    /* 0x74 : ef_key_slot_11_w2 */
    union {
        struct {
            uint32_t ef_key_slot_11_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_11_w2;

    /* 0x78 : ef_key_slot_11_w3 */
    union {
        struct {
            uint32_t ef_key_slot_11_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_11_w3;

    /* 0x7C : ef_data_0_lock */
    union {
        struct {
            uint32_t ef_sec_lifecycle    : 4;  /* [ 3: 0],        r/w,        0x0 */
            uint32_t wr_lock_rsvd_0      : 10; /* [13: 4],        r/w,        0x0 */
            uint32_t wr_lock_boot_mode   : 1;  /* [   14],        r/w,        0x0 */
            uint32_t wr_lock_dbg_pwd     : 1;  /* [   15],        r/w,        0x0 */
            uint32_t wr_lock_wifi_mac    : 1;  /* [   16],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_0  : 1;  /* [   17],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_1  : 1;  /* [   18],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_2  : 1;  /* [   19],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_3  : 1;  /* [   20],        r/w,        0x0 */
            uint32_t wr_lock_sw_usage_0  : 1;  /* [   21],        r/w,        0x0 */
            uint32_t wr_lock_sw_usage_1  : 1;  /* [   22],        r/w,        0x0 */
            uint32_t wr_lock_sw_usage_2  : 1;  /* [   23],        r/w,        0x0 */
            uint32_t wr_lock_sw_usage_3  : 1;  /* [   24],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_11 : 1;  /* [   25],        r/w,        0x0 */
            uint32_t rd_lock_dbg_pwd     : 1;  /* [   26],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_0  : 1;  /* [   27],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_1  : 1;  /* [   28],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_2  : 1;  /* [   29],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_3  : 1;  /* [   30],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_11 : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_data_0_lock;
};

typedef volatile struct ef_data_0_reg ef_data_0_reg_t;

#endif /* __EF_DATA_0_REG_H__ */
