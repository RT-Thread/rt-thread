/**
  ******************************************************************************
  * @file    tzc_sec_reg.h
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
#ifndef __TZC_SEC_REG_H__
#define __TZC_SEC_REG_H__

#include "bl602.h"

/* 0x40 : tzc_rom_ctrl */
#define TZC_SEC_TZC_ROM_CTRL_OFFSET     (0x40)
#define TZC_SEC_TZC_ROM0_R0_ID0_EN      TZC_SEC_TZC_ROM0_R0_ID0_EN
#define TZC_SEC_TZC_ROM0_R0_ID0_EN_POS  (0U)
#define TZC_SEC_TZC_ROM0_R0_ID0_EN_LEN  (1U)
#define TZC_SEC_TZC_ROM0_R0_ID0_EN_MSK  (((1U << TZC_SEC_TZC_ROM0_R0_ID0_EN_LEN) - 1) << TZC_SEC_TZC_ROM0_R0_ID0_EN_POS)
#define TZC_SEC_TZC_ROM0_R0_ID0_EN_UMSK (~(((1U << TZC_SEC_TZC_ROM0_R0_ID0_EN_LEN) - 1) << TZC_SEC_TZC_ROM0_R0_ID0_EN_POS))
#define TZC_SEC_TZC_ROM0_R1_ID0_EN      TZC_SEC_TZC_ROM0_R1_ID0_EN
#define TZC_SEC_TZC_ROM0_R1_ID0_EN_POS  (1U)
#define TZC_SEC_TZC_ROM0_R1_ID0_EN_LEN  (1U)
#define TZC_SEC_TZC_ROM0_R1_ID0_EN_MSK  (((1U << TZC_SEC_TZC_ROM0_R1_ID0_EN_LEN) - 1) << TZC_SEC_TZC_ROM0_R1_ID0_EN_POS)
#define TZC_SEC_TZC_ROM0_R1_ID0_EN_UMSK (~(((1U << TZC_SEC_TZC_ROM0_R1_ID0_EN_LEN) - 1) << TZC_SEC_TZC_ROM0_R1_ID0_EN_POS))
#define TZC_SEC_TZC_ROM1_R0_ID0_EN      TZC_SEC_TZC_ROM1_R0_ID0_EN
#define TZC_SEC_TZC_ROM1_R0_ID0_EN_POS  (2U)
#define TZC_SEC_TZC_ROM1_R0_ID0_EN_LEN  (1U)
#define TZC_SEC_TZC_ROM1_R0_ID0_EN_MSK  (((1U << TZC_SEC_TZC_ROM1_R0_ID0_EN_LEN) - 1) << TZC_SEC_TZC_ROM1_R0_ID0_EN_POS)
#define TZC_SEC_TZC_ROM1_R0_ID0_EN_UMSK (~(((1U << TZC_SEC_TZC_ROM1_R0_ID0_EN_LEN) - 1) << TZC_SEC_TZC_ROM1_R0_ID0_EN_POS))
#define TZC_SEC_TZC_ROM1_R1_ID0_EN      TZC_SEC_TZC_ROM1_R1_ID0_EN
#define TZC_SEC_TZC_ROM1_R1_ID0_EN_POS  (3U)
#define TZC_SEC_TZC_ROM1_R1_ID0_EN_LEN  (1U)
#define TZC_SEC_TZC_ROM1_R1_ID0_EN_MSK  (((1U << TZC_SEC_TZC_ROM1_R1_ID0_EN_LEN) - 1) << TZC_SEC_TZC_ROM1_R1_ID0_EN_POS)
#define TZC_SEC_TZC_ROM1_R1_ID0_EN_UMSK (~(((1U << TZC_SEC_TZC_ROM1_R1_ID0_EN_LEN) - 1) << TZC_SEC_TZC_ROM1_R1_ID0_EN_POS))
#define TZC_SEC_TZC_ROM0_R0_ID1_EN      TZC_SEC_TZC_ROM0_R0_ID1_EN
#define TZC_SEC_TZC_ROM0_R0_ID1_EN_POS  (8U)
#define TZC_SEC_TZC_ROM0_R0_ID1_EN_LEN  (1U)
#define TZC_SEC_TZC_ROM0_R0_ID1_EN_MSK  (((1U << TZC_SEC_TZC_ROM0_R0_ID1_EN_LEN) - 1) << TZC_SEC_TZC_ROM0_R0_ID1_EN_POS)
#define TZC_SEC_TZC_ROM0_R0_ID1_EN_UMSK (~(((1U << TZC_SEC_TZC_ROM0_R0_ID1_EN_LEN) - 1) << TZC_SEC_TZC_ROM0_R0_ID1_EN_POS))
#define TZC_SEC_TZC_ROM0_R1_ID1_EN      TZC_SEC_TZC_ROM0_R1_ID1_EN
#define TZC_SEC_TZC_ROM0_R1_ID1_EN_POS  (9U)
#define TZC_SEC_TZC_ROM0_R1_ID1_EN_LEN  (1U)
#define TZC_SEC_TZC_ROM0_R1_ID1_EN_MSK  (((1U << TZC_SEC_TZC_ROM0_R1_ID1_EN_LEN) - 1) << TZC_SEC_TZC_ROM0_R1_ID1_EN_POS)
#define TZC_SEC_TZC_ROM0_R1_ID1_EN_UMSK (~(((1U << TZC_SEC_TZC_ROM0_R1_ID1_EN_LEN) - 1) << TZC_SEC_TZC_ROM0_R1_ID1_EN_POS))
#define TZC_SEC_TZC_ROM1_R0_ID1_EN      TZC_SEC_TZC_ROM1_R0_ID1_EN
#define TZC_SEC_TZC_ROM1_R0_ID1_EN_POS  (10U)
#define TZC_SEC_TZC_ROM1_R0_ID1_EN_LEN  (1U)
#define TZC_SEC_TZC_ROM1_R0_ID1_EN_MSK  (((1U << TZC_SEC_TZC_ROM1_R0_ID1_EN_LEN) - 1) << TZC_SEC_TZC_ROM1_R0_ID1_EN_POS)
#define TZC_SEC_TZC_ROM1_R0_ID1_EN_UMSK (~(((1U << TZC_SEC_TZC_ROM1_R0_ID1_EN_LEN) - 1) << TZC_SEC_TZC_ROM1_R0_ID1_EN_POS))
#define TZC_SEC_TZC_ROM1_R1_ID1_EN      TZC_SEC_TZC_ROM1_R1_ID1_EN
#define TZC_SEC_TZC_ROM1_R1_ID1_EN_POS  (11U)
#define TZC_SEC_TZC_ROM1_R1_ID1_EN_LEN  (1U)
#define TZC_SEC_TZC_ROM1_R1_ID1_EN_MSK  (((1U << TZC_SEC_TZC_ROM1_R1_ID1_EN_LEN) - 1) << TZC_SEC_TZC_ROM1_R1_ID1_EN_POS)
#define TZC_SEC_TZC_ROM1_R1_ID1_EN_UMSK (~(((1U << TZC_SEC_TZC_ROM1_R1_ID1_EN_LEN) - 1) << TZC_SEC_TZC_ROM1_R1_ID1_EN_POS))
#define TZC_SEC_TZC_ROM0_R0_EN          TZC_SEC_TZC_ROM0_R0_EN
#define TZC_SEC_TZC_ROM0_R0_EN_POS      (16U)
#define TZC_SEC_TZC_ROM0_R0_EN_LEN      (1U)
#define TZC_SEC_TZC_ROM0_R0_EN_MSK      (((1U << TZC_SEC_TZC_ROM0_R0_EN_LEN) - 1) << TZC_SEC_TZC_ROM0_R0_EN_POS)
#define TZC_SEC_TZC_ROM0_R0_EN_UMSK     (~(((1U << TZC_SEC_TZC_ROM0_R0_EN_LEN) - 1) << TZC_SEC_TZC_ROM0_R0_EN_POS))
#define TZC_SEC_TZC_ROM0_R1_EN          TZC_SEC_TZC_ROM0_R1_EN
#define TZC_SEC_TZC_ROM0_R1_EN_POS      (17U)
#define TZC_SEC_TZC_ROM0_R1_EN_LEN      (1U)
#define TZC_SEC_TZC_ROM0_R1_EN_MSK      (((1U << TZC_SEC_TZC_ROM0_R1_EN_LEN) - 1) << TZC_SEC_TZC_ROM0_R1_EN_POS)
#define TZC_SEC_TZC_ROM0_R1_EN_UMSK     (~(((1U << TZC_SEC_TZC_ROM0_R1_EN_LEN) - 1) << TZC_SEC_TZC_ROM0_R1_EN_POS))
#define TZC_SEC_TZC_ROM1_R0_EN          TZC_SEC_TZC_ROM1_R0_EN
#define TZC_SEC_TZC_ROM1_R0_EN_POS      (18U)
#define TZC_SEC_TZC_ROM1_R0_EN_LEN      (1U)
#define TZC_SEC_TZC_ROM1_R0_EN_MSK      (((1U << TZC_SEC_TZC_ROM1_R0_EN_LEN) - 1) << TZC_SEC_TZC_ROM1_R0_EN_POS)
#define TZC_SEC_TZC_ROM1_R0_EN_UMSK     (~(((1U << TZC_SEC_TZC_ROM1_R0_EN_LEN) - 1) << TZC_SEC_TZC_ROM1_R0_EN_POS))
#define TZC_SEC_TZC_ROM1_R1_EN          TZC_SEC_TZC_ROM1_R1_EN
#define TZC_SEC_TZC_ROM1_R1_EN_POS      (19U)
#define TZC_SEC_TZC_ROM1_R1_EN_LEN      (1U)
#define TZC_SEC_TZC_ROM1_R1_EN_MSK      (((1U << TZC_SEC_TZC_ROM1_R1_EN_LEN) - 1) << TZC_SEC_TZC_ROM1_R1_EN_POS)
#define TZC_SEC_TZC_ROM1_R1_EN_UMSK     (~(((1U << TZC_SEC_TZC_ROM1_R1_EN_LEN) - 1) << TZC_SEC_TZC_ROM1_R1_EN_POS))
#define TZC_SEC_TZC_ROM0_R0_LOCK        TZC_SEC_TZC_ROM0_R0_LOCK
#define TZC_SEC_TZC_ROM0_R0_LOCK_POS    (24U)
#define TZC_SEC_TZC_ROM0_R0_LOCK_LEN    (1U)
#define TZC_SEC_TZC_ROM0_R0_LOCK_MSK    (((1U << TZC_SEC_TZC_ROM0_R0_LOCK_LEN) - 1) << TZC_SEC_TZC_ROM0_R0_LOCK_POS)
#define TZC_SEC_TZC_ROM0_R0_LOCK_UMSK   (~(((1U << TZC_SEC_TZC_ROM0_R0_LOCK_LEN) - 1) << TZC_SEC_TZC_ROM0_R0_LOCK_POS))
#define TZC_SEC_TZC_ROM0_R1_LOCK        TZC_SEC_TZC_ROM0_R1_LOCK
#define TZC_SEC_TZC_ROM0_R1_LOCK_POS    (25U)
#define TZC_SEC_TZC_ROM0_R1_LOCK_LEN    (1U)
#define TZC_SEC_TZC_ROM0_R1_LOCK_MSK    (((1U << TZC_SEC_TZC_ROM0_R1_LOCK_LEN) - 1) << TZC_SEC_TZC_ROM0_R1_LOCK_POS)
#define TZC_SEC_TZC_ROM0_R1_LOCK_UMSK   (~(((1U << TZC_SEC_TZC_ROM0_R1_LOCK_LEN) - 1) << TZC_SEC_TZC_ROM0_R1_LOCK_POS))
#define TZC_SEC_TZC_ROM1_R0_LOCK        TZC_SEC_TZC_ROM1_R0_LOCK
#define TZC_SEC_TZC_ROM1_R0_LOCK_POS    (26U)
#define TZC_SEC_TZC_ROM1_R0_LOCK_LEN    (1U)
#define TZC_SEC_TZC_ROM1_R0_LOCK_MSK    (((1U << TZC_SEC_TZC_ROM1_R0_LOCK_LEN) - 1) << TZC_SEC_TZC_ROM1_R0_LOCK_POS)
#define TZC_SEC_TZC_ROM1_R0_LOCK_UMSK   (~(((1U << TZC_SEC_TZC_ROM1_R0_LOCK_LEN) - 1) << TZC_SEC_TZC_ROM1_R0_LOCK_POS))
#define TZC_SEC_TZC_ROM1_R1_LOCK        TZC_SEC_TZC_ROM1_R1_LOCK
#define TZC_SEC_TZC_ROM1_R1_LOCK_POS    (27U)
#define TZC_SEC_TZC_ROM1_R1_LOCK_LEN    (1U)
#define TZC_SEC_TZC_ROM1_R1_LOCK_MSK    (((1U << TZC_SEC_TZC_ROM1_R1_LOCK_LEN) - 1) << TZC_SEC_TZC_ROM1_R1_LOCK_POS)
#define TZC_SEC_TZC_ROM1_R1_LOCK_UMSK   (~(((1U << TZC_SEC_TZC_ROM1_R1_LOCK_LEN) - 1) << TZC_SEC_TZC_ROM1_R1_LOCK_POS))
#define TZC_SEC_TZC_SBOOT_DONE          TZC_SEC_TZC_SBOOT_DONE
#define TZC_SEC_TZC_SBOOT_DONE_POS      (28U)
#define TZC_SEC_TZC_SBOOT_DONE_LEN      (4U)
#define TZC_SEC_TZC_SBOOT_DONE_MSK      (((1U << TZC_SEC_TZC_SBOOT_DONE_LEN) - 1) << TZC_SEC_TZC_SBOOT_DONE_POS)
#define TZC_SEC_TZC_SBOOT_DONE_UMSK     (~(((1U << TZC_SEC_TZC_SBOOT_DONE_LEN) - 1) << TZC_SEC_TZC_SBOOT_DONE_POS))

/* 0x44 : tzc_rom0_r0 */
#define TZC_SEC_TZC_ROM0_R0_OFFSET     (0x44)
#define TZC_SEC_TZC_ROM0_R0_END        TZC_SEC_TZC_ROM0_R0_END
#define TZC_SEC_TZC_ROM0_R0_END_POS    (0U)
#define TZC_SEC_TZC_ROM0_R0_END_LEN    (16U)
#define TZC_SEC_TZC_ROM0_R0_END_MSK    (((1U << TZC_SEC_TZC_ROM0_R0_END_LEN) - 1) << TZC_SEC_TZC_ROM0_R0_END_POS)
#define TZC_SEC_TZC_ROM0_R0_END_UMSK   (~(((1U << TZC_SEC_TZC_ROM0_R0_END_LEN) - 1) << TZC_SEC_TZC_ROM0_R0_END_POS))
#define TZC_SEC_TZC_ROM0_R0_START      TZC_SEC_TZC_ROM0_R0_START
#define TZC_SEC_TZC_ROM0_R0_START_POS  (16U)
#define TZC_SEC_TZC_ROM0_R0_START_LEN  (16U)
#define TZC_SEC_TZC_ROM0_R0_START_MSK  (((1U << TZC_SEC_TZC_ROM0_R0_START_LEN) - 1) << TZC_SEC_TZC_ROM0_R0_START_POS)
#define TZC_SEC_TZC_ROM0_R0_START_UMSK (~(((1U << TZC_SEC_TZC_ROM0_R0_START_LEN) - 1) << TZC_SEC_TZC_ROM0_R0_START_POS))

/* 0x48 : tzc_rom0_r1 */
#define TZC_SEC_TZC_ROM0_R1_OFFSET     (0x48)
#define TZC_SEC_TZC_ROM0_R1_END        TZC_SEC_TZC_ROM0_R1_END
#define TZC_SEC_TZC_ROM0_R1_END_POS    (0U)
#define TZC_SEC_TZC_ROM0_R1_END_LEN    (16U)
#define TZC_SEC_TZC_ROM0_R1_END_MSK    (((1U << TZC_SEC_TZC_ROM0_R1_END_LEN) - 1) << TZC_SEC_TZC_ROM0_R1_END_POS)
#define TZC_SEC_TZC_ROM0_R1_END_UMSK   (~(((1U << TZC_SEC_TZC_ROM0_R1_END_LEN) - 1) << TZC_SEC_TZC_ROM0_R1_END_POS))
#define TZC_SEC_TZC_ROM0_R1_START      TZC_SEC_TZC_ROM0_R1_START
#define TZC_SEC_TZC_ROM0_R1_START_POS  (16U)
#define TZC_SEC_TZC_ROM0_R1_START_LEN  (16U)
#define TZC_SEC_TZC_ROM0_R1_START_MSK  (((1U << TZC_SEC_TZC_ROM0_R1_START_LEN) - 1) << TZC_SEC_TZC_ROM0_R1_START_POS)
#define TZC_SEC_TZC_ROM0_R1_START_UMSK (~(((1U << TZC_SEC_TZC_ROM0_R1_START_LEN) - 1) << TZC_SEC_TZC_ROM0_R1_START_POS))

/* 0x4C : tzc_rom1_r0 */
#define TZC_SEC_TZC_ROM1_R0_OFFSET     (0x4C)
#define TZC_SEC_TZC_ROM1_R0_END        TZC_SEC_TZC_ROM1_R0_END
#define TZC_SEC_TZC_ROM1_R0_END_POS    (0U)
#define TZC_SEC_TZC_ROM1_R0_END_LEN    (16U)
#define TZC_SEC_TZC_ROM1_R0_END_MSK    (((1U << TZC_SEC_TZC_ROM1_R0_END_LEN) - 1) << TZC_SEC_TZC_ROM1_R0_END_POS)
#define TZC_SEC_TZC_ROM1_R0_END_UMSK   (~(((1U << TZC_SEC_TZC_ROM1_R0_END_LEN) - 1) << TZC_SEC_TZC_ROM1_R0_END_POS))
#define TZC_SEC_TZC_ROM1_R0_START      TZC_SEC_TZC_ROM1_R0_START
#define TZC_SEC_TZC_ROM1_R0_START_POS  (16U)
#define TZC_SEC_TZC_ROM1_R0_START_LEN  (16U)
#define TZC_SEC_TZC_ROM1_R0_START_MSK  (((1U << TZC_SEC_TZC_ROM1_R0_START_LEN) - 1) << TZC_SEC_TZC_ROM1_R0_START_POS)
#define TZC_SEC_TZC_ROM1_R0_START_UMSK (~(((1U << TZC_SEC_TZC_ROM1_R0_START_LEN) - 1) << TZC_SEC_TZC_ROM1_R0_START_POS))

/* 0x50 : tzc_rom1_r1 */
#define TZC_SEC_TZC_ROM1_R1_OFFSET     (0x50)
#define TZC_SEC_TZC_ROM1_R1_END        TZC_SEC_TZC_ROM1_R1_END
#define TZC_SEC_TZC_ROM1_R1_END_POS    (0U)
#define TZC_SEC_TZC_ROM1_R1_END_LEN    (16U)
#define TZC_SEC_TZC_ROM1_R1_END_MSK    (((1U << TZC_SEC_TZC_ROM1_R1_END_LEN) - 1) << TZC_SEC_TZC_ROM1_R1_END_POS)
#define TZC_SEC_TZC_ROM1_R1_END_UMSK   (~(((1U << TZC_SEC_TZC_ROM1_R1_END_LEN) - 1) << TZC_SEC_TZC_ROM1_R1_END_POS))
#define TZC_SEC_TZC_ROM1_R1_START      TZC_SEC_TZC_ROM1_R1_START
#define TZC_SEC_TZC_ROM1_R1_START_POS  (16U)
#define TZC_SEC_TZC_ROM1_R1_START_LEN  (16U)
#define TZC_SEC_TZC_ROM1_R1_START_MSK  (((1U << TZC_SEC_TZC_ROM1_R1_START_LEN) - 1) << TZC_SEC_TZC_ROM1_R1_START_POS)
#define TZC_SEC_TZC_ROM1_R1_START_UMSK (~(((1U << TZC_SEC_TZC_ROM1_R1_START_LEN) - 1) << TZC_SEC_TZC_ROM1_R1_START_POS))

struct tzc_sec_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[64];

    /* 0x40 : tzc_rom_ctrl */
    union {
        struct
        {
            uint32_t tzc_rom0_r0_id0_en : 1; /* [    0],        r/w,        0x1 */
            uint32_t tzc_rom0_r1_id0_en : 1; /* [    1],        r/w,        0x1 */
            uint32_t tzc_rom1_r0_id0_en : 1; /* [    2],        r/w,        0x1 */
            uint32_t tzc_rom1_r1_id0_en : 1; /* [    3],        r/w,        0x1 */
            uint32_t reserved_4_7       : 4; /* [ 7: 4],       rsvd,        0x0 */
            uint32_t tzc_rom0_r0_id1_en : 1; /* [    8],        r/w,        0x1 */
            uint32_t tzc_rom0_r1_id1_en : 1; /* [    9],        r/w,        0x1 */
            uint32_t tzc_rom1_r0_id1_en : 1; /* [   10],        r/w,        0x1 */
            uint32_t tzc_rom1_r1_id1_en : 1; /* [   11],        r/w,        0x1 */
            uint32_t reserved_12_15     : 4; /* [15:12],       rsvd,        0x0 */
            uint32_t tzc_rom0_r0_en     : 1; /* [   16],        r/w,        0x0 */
            uint32_t tzc_rom0_r1_en     : 1; /* [   17],        r/w,        0x0 */
            uint32_t tzc_rom1_r0_en     : 1; /* [   18],        r/w,        0x0 */
            uint32_t tzc_rom1_r1_en     : 1; /* [   19],        r/w,        0x0 */
            uint32_t reserved_20_23     : 4; /* [23:20],       rsvd,        0x0 */
            uint32_t tzc_rom0_r0_lock   : 1; /* [   24],        r/w,        0x0 */
            uint32_t tzc_rom0_r1_lock   : 1; /* [   25],        r/w,        0x0 */
            uint32_t tzc_rom1_r0_lock   : 1; /* [   26],        r/w,        0x0 */
            uint32_t tzc_rom1_r1_lock   : 1; /* [   27],        r/w,        0x0 */
            uint32_t tzc_sboot_done     : 4; /* [31:28],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } tzc_rom_ctrl;

    /* 0x44 : tzc_rom0_r0 */
    union {
        struct
        {
            uint32_t tzc_rom0_r0_end   : 16; /* [15: 0],        r/w,     0xffff */
            uint32_t tzc_rom0_r0_start : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } tzc_rom0_r0;

    /* 0x48 : tzc_rom0_r1 */
    union {
        struct
        {
            uint32_t tzc_rom0_r1_end   : 16; /* [15: 0],        r/w,     0xffff */
            uint32_t tzc_rom0_r1_start : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } tzc_rom0_r1;

    /* 0x4C : tzc_rom1_r0 */
    union {
        struct
        {
            uint32_t tzc_rom1_r0_end   : 16; /* [15: 0],        r/w,     0xffff */
            uint32_t tzc_rom1_r0_start : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } tzc_rom1_r0;

    /* 0x50 : tzc_rom1_r1 */
    union {
        struct
        {
            uint32_t tzc_rom1_r1_end   : 16; /* [15: 0],        r/w,     0xffff */
            uint32_t tzc_rom1_r1_start : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } tzc_rom1_r1;
};

typedef volatile struct tzc_sec_reg tzc_sec_reg_t;

#endif /* __TZC_SEC_REG_H__ */
