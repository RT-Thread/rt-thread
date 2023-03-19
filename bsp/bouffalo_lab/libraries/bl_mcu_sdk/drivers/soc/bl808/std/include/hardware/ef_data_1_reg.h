/**
  ******************************************************************************
  * @file    ef_data_1_reg.h
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
#ifndef __EF_DATA_1_REG_H__
#define __EF_DATA_1_REG_H__

#include "bl808.h"

/* 0x80 : ef_key_slot_4_w0 */
#define EF_DATA_1_EF_KEY_SLOT_4_W0_OFFSET (0x80)
#define EF_DATA_1_EF_KEY_SLOT_4_W0        EF_DATA_1_EF_KEY_SLOT_4_W0
#define EF_DATA_1_EF_KEY_SLOT_4_W0_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_4_W0_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_4_W0_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_4_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_4_W0_POS)
#define EF_DATA_1_EF_KEY_SLOT_4_W0_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_4_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_4_W0_POS))

/* 0x84 : ef_key_slot_4_w1 */
#define EF_DATA_1_EF_KEY_SLOT_4_W1_OFFSET (0x84)
#define EF_DATA_1_EF_KEY_SLOT_4_W1        EF_DATA_1_EF_KEY_SLOT_4_W1
#define EF_DATA_1_EF_KEY_SLOT_4_W1_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_4_W1_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_4_W1_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_4_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_4_W1_POS)
#define EF_DATA_1_EF_KEY_SLOT_4_W1_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_4_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_4_W1_POS))

/* 0x88 : ef_key_slot_4_w2 */
#define EF_DATA_1_EF_KEY_SLOT_4_W2_OFFSET (0x88)
#define EF_DATA_1_EF_KEY_SLOT_4_W2        EF_DATA_1_EF_KEY_SLOT_4_W2
#define EF_DATA_1_EF_KEY_SLOT_4_W2_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_4_W2_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_4_W2_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_4_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_4_W2_POS)
#define EF_DATA_1_EF_KEY_SLOT_4_W2_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_4_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_4_W2_POS))

/* 0x8C : ef_key_slot_4_w3 */
#define EF_DATA_1_EF_KEY_SLOT_4_W3_OFFSET (0x8C)
#define EF_DATA_1_EF_KEY_SLOT_4_W3        EF_DATA_1_EF_KEY_SLOT_4_W3
#define EF_DATA_1_EF_KEY_SLOT_4_W3_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_4_W3_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_4_W3_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_4_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_4_W3_POS)
#define EF_DATA_1_EF_KEY_SLOT_4_W3_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_4_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_4_W3_POS))

/* 0x90 : ef_key_slot_5_w0 */
#define EF_DATA_1_EF_KEY_SLOT_5_W0_OFFSET (0x90)
#define EF_DATA_1_EF_KEY_SLOT_5_W0        EF_DATA_1_EF_KEY_SLOT_5_W0
#define EF_DATA_1_EF_KEY_SLOT_5_W0_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_5_W0_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_5_W0_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_5_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_5_W0_POS)
#define EF_DATA_1_EF_KEY_SLOT_5_W0_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_5_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_5_W0_POS))

/* 0x94 : ef_key_slot_5_w1 */
#define EF_DATA_1_EF_KEY_SLOT_5_W1_OFFSET (0x94)
#define EF_DATA_1_EF_KEY_SLOT_5_W1        EF_DATA_1_EF_KEY_SLOT_5_W1
#define EF_DATA_1_EF_KEY_SLOT_5_W1_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_5_W1_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_5_W1_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_5_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_5_W1_POS)
#define EF_DATA_1_EF_KEY_SLOT_5_W1_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_5_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_5_W1_POS))

/* 0x98 : ef_key_slot_5_w2 */
#define EF_DATA_1_EF_KEY_SLOT_5_W2_OFFSET (0x98)
#define EF_DATA_1_EF_KEY_SLOT_5_W2        EF_DATA_1_EF_KEY_SLOT_5_W2
#define EF_DATA_1_EF_KEY_SLOT_5_W2_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_5_W2_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_5_W2_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_5_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_5_W2_POS)
#define EF_DATA_1_EF_KEY_SLOT_5_W2_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_5_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_5_W2_POS))

/* 0x9C : ef_key_slot_5_w3 */
#define EF_DATA_1_EF_KEY_SLOT_5_W3_OFFSET (0x9C)
#define EF_DATA_1_EF_KEY_SLOT_5_W3        EF_DATA_1_EF_KEY_SLOT_5_W3
#define EF_DATA_1_EF_KEY_SLOT_5_W3_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_5_W3_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_5_W3_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_5_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_5_W3_POS)
#define EF_DATA_1_EF_KEY_SLOT_5_W3_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_5_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_5_W3_POS))

/* 0xA0 : ef_key_slot_6_w0 */
#define EF_DATA_1_EF_KEY_SLOT_6_W0_OFFSET (0xA0)
#define EF_DATA_1_EF_KEY_SLOT_6_W0        EF_DATA_1_EF_KEY_SLOT_6_W0
#define EF_DATA_1_EF_KEY_SLOT_6_W0_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_6_W0_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_6_W0_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_6_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_6_W0_POS)
#define EF_DATA_1_EF_KEY_SLOT_6_W0_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_6_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_6_W0_POS))

/* 0xA4 : ef_key_slot_6_w1 */
#define EF_DATA_1_EF_KEY_SLOT_6_W1_OFFSET (0xA4)
#define EF_DATA_1_EF_KEY_SLOT_6_W1        EF_DATA_1_EF_KEY_SLOT_6_W1
#define EF_DATA_1_EF_KEY_SLOT_6_W1_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_6_W1_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_6_W1_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_6_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_6_W1_POS)
#define EF_DATA_1_EF_KEY_SLOT_6_W1_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_6_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_6_W1_POS))

/* 0xA8 : ef_key_slot_6_w2 */
#define EF_DATA_1_EF_KEY_SLOT_6_W2_OFFSET (0xA8)
#define EF_DATA_1_EF_KEY_SLOT_6_W2        EF_DATA_1_EF_KEY_SLOT_6_W2
#define EF_DATA_1_EF_KEY_SLOT_6_W2_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_6_W2_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_6_W2_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_6_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_6_W2_POS)
#define EF_DATA_1_EF_KEY_SLOT_6_W2_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_6_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_6_W2_POS))

/* 0xAC : ef_key_slot_6_w3 */
#define EF_DATA_1_EF_KEY_SLOT_6_W3_OFFSET (0xAC)
#define EF_DATA_1_EF_KEY_SLOT_6_W3        EF_DATA_1_EF_KEY_SLOT_6_W3
#define EF_DATA_1_EF_KEY_SLOT_6_W3_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_6_W3_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_6_W3_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_6_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_6_W3_POS)
#define EF_DATA_1_EF_KEY_SLOT_6_W3_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_6_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_6_W3_POS))

/* 0xB0 : ef_key_slot_7_w0 */
#define EF_DATA_1_EF_KEY_SLOT_7_W0_OFFSET (0xB0)
#define EF_DATA_1_EF_KEY_SLOT_7_W0        EF_DATA_1_EF_KEY_SLOT_7_W0
#define EF_DATA_1_EF_KEY_SLOT_7_W0_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_7_W0_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_7_W0_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_7_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_7_W0_POS)
#define EF_DATA_1_EF_KEY_SLOT_7_W0_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_7_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_7_W0_POS))

/* 0xB4 : ef_key_slot_7_w1 */
#define EF_DATA_1_EF_KEY_SLOT_7_W1_OFFSET (0xB4)
#define EF_DATA_1_EF_KEY_SLOT_7_W1        EF_DATA_1_EF_KEY_SLOT_7_W1
#define EF_DATA_1_EF_KEY_SLOT_7_W1_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_7_W1_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_7_W1_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_7_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_7_W1_POS)
#define EF_DATA_1_EF_KEY_SLOT_7_W1_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_7_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_7_W1_POS))

/* 0xB8 : ef_key_slot_7_w2 */
#define EF_DATA_1_EF_KEY_SLOT_7_W2_OFFSET (0xB8)
#define EF_DATA_1_EF_KEY_SLOT_7_W2        EF_DATA_1_EF_KEY_SLOT_7_W2
#define EF_DATA_1_EF_KEY_SLOT_7_W2_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_7_W2_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_7_W2_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_7_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_7_W2_POS)
#define EF_DATA_1_EF_KEY_SLOT_7_W2_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_7_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_7_W2_POS))

/* 0xBC : ef_key_slot_7_w3 */
#define EF_DATA_1_EF_KEY_SLOT_7_W3_OFFSET (0xBC)
#define EF_DATA_1_EF_KEY_SLOT_7_W3        EF_DATA_1_EF_KEY_SLOT_7_W3
#define EF_DATA_1_EF_KEY_SLOT_7_W3_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_7_W3_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_7_W3_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_7_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_7_W3_POS)
#define EF_DATA_1_EF_KEY_SLOT_7_W3_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_7_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_7_W3_POS))

/* 0xC0 : ef_key_slot_8_w0 */
#define EF_DATA_1_EF_KEY_SLOT_8_W0_OFFSET (0xC0)
#define EF_DATA_1_EF_KEY_SLOT_8_W0        EF_DATA_1_EF_KEY_SLOT_8_W0
#define EF_DATA_1_EF_KEY_SLOT_8_W0_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_8_W0_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_8_W0_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_8_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_8_W0_POS)
#define EF_DATA_1_EF_KEY_SLOT_8_W0_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_8_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_8_W0_POS))

/* 0xC4 : ef_key_slot_8_w1 */
#define EF_DATA_1_EF_KEY_SLOT_8_W1_OFFSET (0xC4)
#define EF_DATA_1_EF_KEY_SLOT_8_W1        EF_DATA_1_EF_KEY_SLOT_8_W1
#define EF_DATA_1_EF_KEY_SLOT_8_W1_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_8_W1_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_8_W1_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_8_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_8_W1_POS)
#define EF_DATA_1_EF_KEY_SLOT_8_W1_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_8_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_8_W1_POS))

/* 0xC8 : ef_key_slot_8_w2 */
#define EF_DATA_1_EF_KEY_SLOT_8_W2_OFFSET (0xC8)
#define EF_DATA_1_EF_KEY_SLOT_8_W2        EF_DATA_1_EF_KEY_SLOT_8_W2
#define EF_DATA_1_EF_KEY_SLOT_8_W2_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_8_W2_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_8_W2_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_8_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_8_W2_POS)
#define EF_DATA_1_EF_KEY_SLOT_8_W2_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_8_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_8_W2_POS))

/* 0xCC : ef_key_slot_8_w3 */
#define EF_DATA_1_EF_KEY_SLOT_8_W3_OFFSET (0xCC)
#define EF_DATA_1_EF_KEY_SLOT_8_W3        EF_DATA_1_EF_KEY_SLOT_8_W3
#define EF_DATA_1_EF_KEY_SLOT_8_W3_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_8_W3_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_8_W3_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_8_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_8_W3_POS)
#define EF_DATA_1_EF_KEY_SLOT_8_W3_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_8_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_8_W3_POS))

/* 0xD0 : ef_key_slot_9_w0 */
#define EF_DATA_1_EF_KEY_SLOT_9_W0_OFFSET (0xD0)
#define EF_DATA_1_EF_KEY_SLOT_9_W0        EF_DATA_1_EF_KEY_SLOT_9_W0
#define EF_DATA_1_EF_KEY_SLOT_9_W0_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_9_W0_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_9_W0_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_9_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_9_W0_POS)
#define EF_DATA_1_EF_KEY_SLOT_9_W0_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_9_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_9_W0_POS))

/* 0xD4 : ef_key_slot_9_w1 */
#define EF_DATA_1_EF_KEY_SLOT_9_W1_OFFSET (0xD4)
#define EF_DATA_1_EF_KEY_SLOT_9_W1        EF_DATA_1_EF_KEY_SLOT_9_W1
#define EF_DATA_1_EF_KEY_SLOT_9_W1_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_9_W1_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_9_W1_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_9_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_9_W1_POS)
#define EF_DATA_1_EF_KEY_SLOT_9_W1_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_9_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_9_W1_POS))

/* 0xD8 : ef_key_slot_9_w2 */
#define EF_DATA_1_EF_KEY_SLOT_9_W2_OFFSET (0xD8)
#define EF_DATA_1_EF_KEY_SLOT_9_W2        EF_DATA_1_EF_KEY_SLOT_9_W2
#define EF_DATA_1_EF_KEY_SLOT_9_W2_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_9_W2_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_9_W2_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_9_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_9_W2_POS)
#define EF_DATA_1_EF_KEY_SLOT_9_W2_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_9_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_9_W2_POS))

/* 0xDC : ef_key_slot_9_w3 */
#define EF_DATA_1_EF_KEY_SLOT_9_W3_OFFSET (0xDC)
#define EF_DATA_1_EF_KEY_SLOT_9_W3        EF_DATA_1_EF_KEY_SLOT_9_W3
#define EF_DATA_1_EF_KEY_SLOT_9_W3_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_9_W3_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_9_W3_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_9_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_9_W3_POS)
#define EF_DATA_1_EF_KEY_SLOT_9_W3_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_9_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_9_W3_POS))

/* 0xE0 : ef_key_slot_10_w0 */
#define EF_DATA_1_EF_KEY_SLOT_10_W0_OFFSET (0xE0)
#define EF_DATA_1_EF_KEY_SLOT_10_W0        EF_DATA_1_EF_KEY_SLOT_10_W0
#define EF_DATA_1_EF_KEY_SLOT_10_W0_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_10_W0_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_10_W0_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_10_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_10_W0_POS)
#define EF_DATA_1_EF_KEY_SLOT_10_W0_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_10_W0_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_10_W0_POS))

/* 0xE4 : ef_key_slot_10_w1 */
#define EF_DATA_1_EF_KEY_SLOT_10_W1_OFFSET (0xE4)
#define EF_DATA_1_EF_KEY_SLOT_10_W1        EF_DATA_1_EF_KEY_SLOT_10_W1
#define EF_DATA_1_EF_KEY_SLOT_10_W1_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_10_W1_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_10_W1_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_10_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_10_W1_POS)
#define EF_DATA_1_EF_KEY_SLOT_10_W1_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_10_W1_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_10_W1_POS))

/* 0xE8 : ef_key_slot_10_w2 */
#define EF_DATA_1_EF_KEY_SLOT_10_W2_OFFSET (0xE8)
#define EF_DATA_1_EF_KEY_SLOT_10_W2        EF_DATA_1_EF_KEY_SLOT_10_W2
#define EF_DATA_1_EF_KEY_SLOT_10_W2_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_10_W2_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_10_W2_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_10_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_10_W2_POS)
#define EF_DATA_1_EF_KEY_SLOT_10_W2_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_10_W2_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_10_W2_POS))

/* 0xEC : ef_key_slot_10_w3 */
#define EF_DATA_1_EF_KEY_SLOT_10_W3_OFFSET (0xEC)
#define EF_DATA_1_EF_KEY_SLOT_10_W3        EF_DATA_1_EF_KEY_SLOT_10_W3
#define EF_DATA_1_EF_KEY_SLOT_10_W3_POS    (0U)
#define EF_DATA_1_EF_KEY_SLOT_10_W3_LEN    (32U)
#define EF_DATA_1_EF_KEY_SLOT_10_W3_MSK    (((1U << EF_DATA_1_EF_KEY_SLOT_10_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_10_W3_POS)
#define EF_DATA_1_EF_KEY_SLOT_10_W3_UMSK   (~(((1U << EF_DATA_1_EF_KEY_SLOT_10_W3_LEN) - 1) << EF_DATA_1_EF_KEY_SLOT_10_W3_POS))

/* 0xF0 : ef_dat_1_rsvd_0 */
#define EF_DATA_1_EF_DAT_1_RSVD_0_OFFSET (0xF0)
#define EF_DATA_1_EF_DAT_1_RSVD_0        EF_DATA_1_EF_DAT_1_RSVD_0
#define EF_DATA_1_EF_DAT_1_RSVD_0_POS    (0U)
#define EF_DATA_1_EF_DAT_1_RSVD_0_LEN    (32U)
#define EF_DATA_1_EF_DAT_1_RSVD_0_MSK    (((1U << EF_DATA_1_EF_DAT_1_RSVD_0_LEN) - 1) << EF_DATA_1_EF_DAT_1_RSVD_0_POS)
#define EF_DATA_1_EF_DAT_1_RSVD_0_UMSK   (~(((1U << EF_DATA_1_EF_DAT_1_RSVD_0_LEN) - 1) << EF_DATA_1_EF_DAT_1_RSVD_0_POS))

/* 0xF4 : ef_dat_1_rsvd_1 */
#define EF_DATA_1_EF_DAT_1_RSVD_1_OFFSET (0xF4)
#define EF_DATA_1_EF_DAT_1_RSVD_1        EF_DATA_1_EF_DAT_1_RSVD_1
#define EF_DATA_1_EF_DAT_1_RSVD_1_POS    (0U)
#define EF_DATA_1_EF_DAT_1_RSVD_1_LEN    (32U)
#define EF_DATA_1_EF_DAT_1_RSVD_1_MSK    (((1U << EF_DATA_1_EF_DAT_1_RSVD_1_LEN) - 1) << EF_DATA_1_EF_DAT_1_RSVD_1_POS)
#define EF_DATA_1_EF_DAT_1_RSVD_1_UMSK   (~(((1U << EF_DATA_1_EF_DAT_1_RSVD_1_LEN) - 1) << EF_DATA_1_EF_DAT_1_RSVD_1_POS))

/* 0xF8 : ef_dat_1_rsvd_2 */
#define EF_DATA_1_EF_DAT_1_RSVD_2_OFFSET (0xF8)
#define EF_DATA_1_EF_DAT_1_RSVD_2        EF_DATA_1_EF_DAT_1_RSVD_2
#define EF_DATA_1_EF_DAT_1_RSVD_2_POS    (0U)
#define EF_DATA_1_EF_DAT_1_RSVD_2_LEN    (32U)
#define EF_DATA_1_EF_DAT_1_RSVD_2_MSK    (((1U << EF_DATA_1_EF_DAT_1_RSVD_2_LEN) - 1) << EF_DATA_1_EF_DAT_1_RSVD_2_POS)
#define EF_DATA_1_EF_DAT_1_RSVD_2_UMSK   (~(((1U << EF_DATA_1_EF_DAT_1_RSVD_2_LEN) - 1) << EF_DATA_1_EF_DAT_1_RSVD_2_POS))

/* 0xFC : ef_data_1_lock */
#define EF_DATA_1_LOCK_OFFSET               (0xFC)
#define EF_DATA_1_WR_LOCK_RSVD_1            EF_DATA_1_WR_LOCK_RSVD_1
#define EF_DATA_1_WR_LOCK_RSVD_1_POS        (0U)
#define EF_DATA_1_WR_LOCK_RSVD_1_LEN        (15U)
#define EF_DATA_1_WR_LOCK_RSVD_1_MSK        (((1U << EF_DATA_1_WR_LOCK_RSVD_1_LEN) - 1) << EF_DATA_1_WR_LOCK_RSVD_1_POS)
#define EF_DATA_1_WR_LOCK_RSVD_1_UMSK       (~(((1U << EF_DATA_1_WR_LOCK_RSVD_1_LEN) - 1) << EF_DATA_1_WR_LOCK_RSVD_1_POS))
#define EF_DATA_1_WR_LOCK_KEY_SLOT_4        EF_DATA_1_WR_LOCK_KEY_SLOT_4
#define EF_DATA_1_WR_LOCK_KEY_SLOT_4_POS    (15U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_4_LEN    (1U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_4_MSK    (((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_4_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_4_POS)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_4_UMSK   (~(((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_4_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_4_POS))
#define EF_DATA_1_WR_LOCK_KEY_SLOT_5        EF_DATA_1_WR_LOCK_KEY_SLOT_5
#define EF_DATA_1_WR_LOCK_KEY_SLOT_5_POS    (16U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_5_LEN    (1U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_5_MSK    (((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_5_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_5_POS)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_5_UMSK   (~(((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_5_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_5_POS))
#define EF_DATA_1_WR_LOCK_KEY_SLOT_6        EF_DATA_1_WR_LOCK_KEY_SLOT_6
#define EF_DATA_1_WR_LOCK_KEY_SLOT_6_POS    (17U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_6_LEN    (1U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_6_MSK    (((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_6_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_6_POS)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_6_UMSK   (~(((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_6_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_6_POS))
#define EF_DATA_1_WR_LOCK_KEY_SLOT_7        EF_DATA_1_WR_LOCK_KEY_SLOT_7
#define EF_DATA_1_WR_LOCK_KEY_SLOT_7_POS    (18U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_7_LEN    (1U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_7_MSK    (((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_7_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_7_POS)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_7_UMSK   (~(((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_7_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_7_POS))
#define EF_DATA_1_WR_LOCK_KEY_SLOT_8        EF_DATA_1_WR_LOCK_KEY_SLOT_8
#define EF_DATA_1_WR_LOCK_KEY_SLOT_8_POS    (19U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_8_LEN    (1U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_8_MSK    (((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_8_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_8_POS)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_8_UMSK   (~(((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_8_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_8_POS))
#define EF_DATA_1_WR_LOCK_KEY_SLOT_9        EF_DATA_1_WR_LOCK_KEY_SLOT_9
#define EF_DATA_1_WR_LOCK_KEY_SLOT_9_POS    (20U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_9_LEN    (1U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_9_MSK    (((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_9_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_9_POS)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_9_UMSK   (~(((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_9_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_9_POS))
#define EF_DATA_1_WR_LOCK_KEY_SLOT_10       EF_DATA_1_WR_LOCK_KEY_SLOT_10
#define EF_DATA_1_WR_LOCK_KEY_SLOT_10_POS   (21U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_10_LEN   (1U)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_10_MSK   (((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_10_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_10_POS)
#define EF_DATA_1_WR_LOCK_KEY_SLOT_10_UMSK  (~(((1U << EF_DATA_1_WR_LOCK_KEY_SLOT_10_LEN) - 1) << EF_DATA_1_WR_LOCK_KEY_SLOT_10_POS))
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_0      EF_DATA_1_WR_LOCK_DAT_1_RSVD_0
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_0_POS  (22U)
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_0_LEN  (1U)
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_0_MSK  (((1U << EF_DATA_1_WR_LOCK_DAT_1_RSVD_0_LEN) - 1) << EF_DATA_1_WR_LOCK_DAT_1_RSVD_0_POS)
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_0_UMSK (~(((1U << EF_DATA_1_WR_LOCK_DAT_1_RSVD_0_LEN) - 1) << EF_DATA_1_WR_LOCK_DAT_1_RSVD_0_POS))
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_1      EF_DATA_1_WR_LOCK_DAT_1_RSVD_1
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_1_POS  (23U)
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_1_LEN  (1U)
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_1_MSK  (((1U << EF_DATA_1_WR_LOCK_DAT_1_RSVD_1_LEN) - 1) << EF_DATA_1_WR_LOCK_DAT_1_RSVD_1_POS)
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_1_UMSK (~(((1U << EF_DATA_1_WR_LOCK_DAT_1_RSVD_1_LEN) - 1) << EF_DATA_1_WR_LOCK_DAT_1_RSVD_1_POS))
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_2      EF_DATA_1_WR_LOCK_DAT_1_RSVD_2
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_2_POS  (24U)
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_2_LEN  (1U)
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_2_MSK  (((1U << EF_DATA_1_WR_LOCK_DAT_1_RSVD_2_LEN) - 1) << EF_DATA_1_WR_LOCK_DAT_1_RSVD_2_POS)
#define EF_DATA_1_WR_LOCK_DAT_1_RSVD_2_UMSK (~(((1U << EF_DATA_1_WR_LOCK_DAT_1_RSVD_2_LEN) - 1) << EF_DATA_1_WR_LOCK_DAT_1_RSVD_2_POS))
#define EF_DATA_1_RD_LOCK_KEY_SLOT_4        EF_DATA_1_RD_LOCK_KEY_SLOT_4
#define EF_DATA_1_RD_LOCK_KEY_SLOT_4_POS    (25U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_4_LEN    (1U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_4_MSK    (((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_4_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_4_POS)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_4_UMSK   (~(((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_4_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_4_POS))
#define EF_DATA_1_RD_LOCK_KEY_SLOT_5        EF_DATA_1_RD_LOCK_KEY_SLOT_5
#define EF_DATA_1_RD_LOCK_KEY_SLOT_5_POS    (26U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_5_LEN    (1U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_5_MSK    (((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_5_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_5_POS)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_5_UMSK   (~(((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_5_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_5_POS))
#define EF_DATA_1_RD_LOCK_KEY_SLOT_6        EF_DATA_1_RD_LOCK_KEY_SLOT_6
#define EF_DATA_1_RD_LOCK_KEY_SLOT_6_POS    (27U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_6_LEN    (1U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_6_MSK    (((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_6_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_6_POS)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_6_UMSK   (~(((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_6_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_6_POS))
#define EF_DATA_1_RD_LOCK_KEY_SLOT_7        EF_DATA_1_RD_LOCK_KEY_SLOT_7
#define EF_DATA_1_RD_LOCK_KEY_SLOT_7_POS    (28U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_7_LEN    (1U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_7_MSK    (((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_7_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_7_POS)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_7_UMSK   (~(((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_7_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_7_POS))
#define EF_DATA_1_RD_LOCK_KEY_SLOT_8        EF_DATA_1_RD_LOCK_KEY_SLOT_8
#define EF_DATA_1_RD_LOCK_KEY_SLOT_8_POS    (29U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_8_LEN    (1U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_8_MSK    (((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_8_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_8_POS)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_8_UMSK   (~(((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_8_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_8_POS))
#define EF_DATA_1_RD_LOCK_KEY_SLOT_9        EF_DATA_1_RD_LOCK_KEY_SLOT_9
#define EF_DATA_1_RD_LOCK_KEY_SLOT_9_POS    (30U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_9_LEN    (1U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_9_MSK    (((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_9_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_9_POS)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_9_UMSK   (~(((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_9_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_9_POS))
#define EF_DATA_1_RD_LOCK_KEY_SLOT_10       EF_DATA_1_RD_LOCK_KEY_SLOT_10
#define EF_DATA_1_RD_LOCK_KEY_SLOT_10_POS   (31U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_10_LEN   (1U)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_10_MSK   (((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_10_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_10_POS)
#define EF_DATA_1_RD_LOCK_KEY_SLOT_10_UMSK  (~(((1U << EF_DATA_1_RD_LOCK_KEY_SLOT_10_LEN) - 1) << EF_DATA_1_RD_LOCK_KEY_SLOT_10_POS))

struct ef_data_1_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[128];

    /* 0x80 : ef_key_slot_4_w0 */
    union {
        struct {
            uint32_t ef_key_slot_4_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_4_w0;

    /* 0x84 : ef_key_slot_4_w1 */
    union {
        struct {
            uint32_t ef_key_slot_4_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_4_w1;

    /* 0x88 : ef_key_slot_4_w2 */
    union {
        struct {
            uint32_t ef_key_slot_4_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_4_w2;

    /* 0x8C : ef_key_slot_4_w3 */
    union {
        struct {
            uint32_t ef_key_slot_4_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_4_w3;

    /* 0x90 : ef_key_slot_5_w0 */
    union {
        struct {
            uint32_t ef_key_slot_5_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_5_w0;

    /* 0x94 : ef_key_slot_5_w1 */
    union {
        struct {
            uint32_t ef_key_slot_5_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_5_w1;

    /* 0x98 : ef_key_slot_5_w2 */
    union {
        struct {
            uint32_t ef_key_slot_5_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_5_w2;

    /* 0x9C : ef_key_slot_5_w3 */
    union {
        struct {
            uint32_t ef_key_slot_5_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_5_w3;

    /* 0xA0 : ef_key_slot_6_w0 */
    union {
        struct {
            uint32_t ef_key_slot_6_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_6_w0;

    /* 0xA4 : ef_key_slot_6_w1 */
    union {
        struct {
            uint32_t ef_key_slot_6_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_6_w1;

    /* 0xA8 : ef_key_slot_6_w2 */
    union {
        struct {
            uint32_t ef_key_slot_6_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_6_w2;

    /* 0xAC : ef_key_slot_6_w3 */
    union {
        struct {
            uint32_t ef_key_slot_6_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_6_w3;

    /* 0xB0 : ef_key_slot_7_w0 */
    union {
        struct {
            uint32_t ef_key_slot_7_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_7_w0;

    /* 0xB4 : ef_key_slot_7_w1 */
    union {
        struct {
            uint32_t ef_key_slot_7_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_7_w1;

    /* 0xB8 : ef_key_slot_7_w2 */
    union {
        struct {
            uint32_t ef_key_slot_7_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_7_w2;

    /* 0xBC : ef_key_slot_7_w3 */
    union {
        struct {
            uint32_t ef_key_slot_7_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_7_w3;

    /* 0xC0 : ef_key_slot_8_w0 */
    union {
        struct {
            uint32_t ef_key_slot_8_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_8_w0;

    /* 0xC4 : ef_key_slot_8_w1 */
    union {
        struct {
            uint32_t ef_key_slot_8_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_8_w1;

    /* 0xC8 : ef_key_slot_8_w2 */
    union {
        struct {
            uint32_t ef_key_slot_8_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_8_w2;

    /* 0xCC : ef_key_slot_8_w3 */
    union {
        struct {
            uint32_t ef_key_slot_8_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_8_w3;

    /* 0xD0 : ef_key_slot_9_w0 */
    union {
        struct {
            uint32_t ef_key_slot_9_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_9_w0;

    /* 0xD4 : ef_key_slot_9_w1 */
    union {
        struct {
            uint32_t ef_key_slot_9_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_9_w1;

    /* 0xD8 : ef_key_slot_9_w2 */
    union {
        struct {
            uint32_t ef_key_slot_9_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_9_w2;

    /* 0xDC : ef_key_slot_9_w3 */
    union {
        struct {
            uint32_t ef_key_slot_9_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_9_w3;

    /* 0xE0 : ef_key_slot_10_w0 */
    union {
        struct {
            uint32_t ef_key_slot_10_w0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_10_w0;

    /* 0xE4 : ef_key_slot_10_w1 */
    union {
        struct {
            uint32_t ef_key_slot_10_w1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_10_w1;

    /* 0xE8 : ef_key_slot_10_w2 */
    union {
        struct {
            uint32_t ef_key_slot_10_w2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_10_w2;

    /* 0xEC : ef_key_slot_10_w3 */
    union {
        struct {
            uint32_t ef_key_slot_10_w3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_key_slot_10_w3;

    /* 0xF0 : ef_dat_1_rsvd_0 */
    union {
        struct {
            uint32_t ef_dat_1_rsvd_0 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_dat_1_rsvd_0;

    /* 0xF4 : ef_dat_1_rsvd_1 */
    union {
        struct {
            uint32_t ef_dat_1_rsvd_1 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_dat_1_rsvd_1;

    /* 0xF8 : ef_dat_1_rsvd_2 */
    union {
        struct {
            uint32_t ef_dat_1_rsvd_2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_dat_1_rsvd_2;

    /* 0xFC : ef_data_1_lock */
    union {
        struct {
            uint32_t wr_lock_rsvd_1       : 15; /* [14: 0],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_4   : 1;  /* [   15],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_5   : 1;  /* [   16],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_6   : 1;  /* [   17],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_7   : 1;  /* [   18],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_8   : 1;  /* [   19],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_9   : 1;  /* [   20],        r/w,        0x0 */
            uint32_t wr_lock_key_slot_10  : 1;  /* [   21],        r/w,        0x0 */
            uint32_t wr_lock_dat_1_rsvd_0 : 1;  /* [   22],        r/w,        0x0 */
            uint32_t wr_lock_dat_1_rsvd_1 : 1;  /* [   23],        r/w,        0x0 */
            uint32_t wr_lock_dat_1_rsvd_2 : 1;  /* [   24],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_4   : 1;  /* [   25],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_5   : 1;  /* [   26],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_6   : 1;  /* [   27],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_7   : 1;  /* [   28],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_8   : 1;  /* [   29],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_9   : 1;  /* [   30],        r/w,        0x0 */
            uint32_t rd_lock_key_slot_10  : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ef_data_1_lock;
};

typedef volatile struct ef_data_1_reg ef_data_1_reg_t;

#endif /* __EF_DATA_1_REG_H__ */
