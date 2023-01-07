/**
  ******************************************************************************
  * @file    lz4_reg.h
  * @version V1.0
  * @date    2021-06-15
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
#ifndef __LZ4_REG_H__
#define __LZ4_REG_H__

#include "bl808.h"

/* 0x0 : lz4_config */
#define LZ4_CONFIG_OFFSET (0x0)
#define LZ4_EN            LZ4_EN
#define LZ4_EN_POS        (0U)
#define LZ4_EN_LEN        (1U)
#define LZ4_EN_MSK        (((1U << LZ4_EN_LEN) - 1) << LZ4_EN_POS)
#define LZ4_EN_UMSK       (~(((1U << LZ4_EN_LEN) - 1) << LZ4_EN_POS))
#define LZ4_SUSPEND       LZ4_SUSPEND
#define LZ4_SUSPEND_POS   (1U)
#define LZ4_SUSPEND_LEN   (1U)
#define LZ4_SUSPEND_MSK   (((1U << LZ4_SUSPEND_LEN) - 1) << LZ4_SUSPEND_POS)
#define LZ4_SUSPEND_UMSK  (~(((1U << LZ4_SUSPEND_LEN) - 1) << LZ4_SUSPEND_POS))
#define LZ4_CHECKSUM      LZ4_CHECKSUM
#define LZ4_CHECKSUM_POS  (4U)
#define LZ4_CHECKSUM_LEN  (1U)
#define LZ4_CHECKSUM_MSK  (((1U << LZ4_CHECKSUM_LEN) - 1) << LZ4_CHECKSUM_POS)
#define LZ4_CHECKSUM_UMSK (~(((1U << LZ4_CHECKSUM_LEN) - 1) << LZ4_CHECKSUM_POS))

/* 0x4 : lz4_src_fix */
#define LZ4_SRC_FIX_OFFSET (0x4)
#define LZ4_SRC_FIX        LZ4_SRC_FIX
#define LZ4_SRC_FIX_POS    (12U)
#define LZ4_SRC_FIX_LEN    (14U)
#define LZ4_SRC_FIX_MSK    (((1U << LZ4_SRC_FIX_LEN) - 1) << LZ4_SRC_FIX_POS)
#define LZ4_SRC_FIX_UMSK   (~(((1U << LZ4_SRC_FIX_LEN) - 1) << LZ4_SRC_FIX_POS))

/* 0x8 : lz4_dst_fix */
#define LZ4_DST_FIX_OFFSET (0x8)
#define LZ4_DST_FIX        LZ4_DST_FIX
#define LZ4_DST_FIX_POS    (12U)
#define LZ4_DST_FIX_LEN    (14U)
#define LZ4_DST_FIX_MSK    (((1U << LZ4_DST_FIX_LEN) - 1) << LZ4_DST_FIX_POS)
#define LZ4_DST_FIX_UMSK   (~(((1U << LZ4_DST_FIX_LEN) - 1) << LZ4_DST_FIX_POS))

/* 0x10 : lz4_src_start */
#define LZ4_SRC_START_OFFSET (0x10)
#define LZ4_SRC_START        LZ4_SRC_START
#define LZ4_SRC_START_POS    (0U)
#define LZ4_SRC_START_LEN    (26U)
#define LZ4_SRC_START_MSK    (((1U << LZ4_SRC_START_LEN) - 1) << LZ4_SRC_START_POS)
#define LZ4_SRC_START_UMSK   (~(((1U << LZ4_SRC_START_LEN) - 1) << LZ4_SRC_START_POS))
#define LZ4_SRC_BASE         LZ4_SRC_BASE
#define LZ4_SRC_BASE_POS     (26U)
#define LZ4_SRC_BASE_LEN     (6U)
#define LZ4_SRC_BASE_MSK     (((1U << LZ4_SRC_BASE_LEN) - 1) << LZ4_SRC_BASE_POS)
#define LZ4_SRC_BASE_UMSK    (~(((1U << LZ4_SRC_BASE_LEN) - 1) << LZ4_SRC_BASE_POS))

/* 0x14 : lz4_src_end */
#define LZ4_SRC_END_OFFSET (0x14)
#define LZ4_SRC_END        LZ4_SRC_END
#define LZ4_SRC_END_POS    (0U)
#define LZ4_SRC_END_LEN    (26U)
#define LZ4_SRC_END_MSK    (((1U << LZ4_SRC_END_LEN) - 1) << LZ4_SRC_END_POS)
#define LZ4_SRC_END_UMSK   (~(((1U << LZ4_SRC_END_LEN) - 1) << LZ4_SRC_END_POS))

/* 0x18 : lz4_dst_start */
#define LZ4_DST_START_OFFSET (0x18)
#define LZ4_DST_START        LZ4_DST_START
#define LZ4_DST_START_POS    (0U)
#define LZ4_DST_START_LEN    (26U)
#define LZ4_DST_START_MSK    (((1U << LZ4_DST_START_LEN) - 1) << LZ4_DST_START_POS)
#define LZ4_DST_START_UMSK   (~(((1U << LZ4_DST_START_LEN) - 1) << LZ4_DST_START_POS))
#define LZ4_DST_BASE         LZ4_DST_BASE
#define LZ4_DST_BASE_POS     (26U)
#define LZ4_DST_BASE_LEN     (6U)
#define LZ4_DST_BASE_MSK     (((1U << LZ4_DST_BASE_LEN) - 1) << LZ4_DST_BASE_POS)
#define LZ4_DST_BASE_UMSK    (~(((1U << LZ4_DST_BASE_LEN) - 1) << LZ4_DST_BASE_POS))

/* 0x1C : lz4_dst_end */
#define LZ4_DST_END_OFFSET (0x1C)
#define LZ4_DST_END        LZ4_DST_END
#define LZ4_DST_END_POS    (0U)
#define LZ4_DST_END_LEN    (26U)
#define LZ4_DST_END_MSK    (((1U << LZ4_DST_END_LEN) - 1) << LZ4_DST_END_POS)
#define LZ4_DST_END_UMSK   (~(((1U << LZ4_DST_END_LEN) - 1) << LZ4_DST_END_POS))

/* 0x20 : lz4_int_en */
#define LZ4_INT_EN_OFFSET    (0x20)
#define LZ4_DONE_EN          LZ4_DONE_EN
#define LZ4_DONE_EN_POS      (0U)
#define LZ4_DONE_EN_LEN      (1U)
#define LZ4_DONE_EN_MSK      (((1U << LZ4_DONE_EN_LEN) - 1) << LZ4_DONE_EN_POS)
#define LZ4_DONE_EN_UMSK     (~(((1U << LZ4_DONE_EN_LEN) - 1) << LZ4_DONE_EN_POS))
#define LZ4_ERR_EN           LZ4_ERR_EN
#define LZ4_ERR_EN_POS       (1U)
#define LZ4_ERR_EN_LEN       (1U)
#define LZ4_ERR_EN_MSK       (((1U << LZ4_ERR_EN_LEN) - 1) << LZ4_ERR_EN_POS)
#define LZ4_ERR_EN_UMSK      (~(((1U << LZ4_ERR_EN_LEN) - 1) << LZ4_ERR_EN_POS))
#define LZ4_DST_INT_EN       LZ4_DST_INT_EN
#define LZ4_DST_INT_EN_POS   (10U)
#define LZ4_DST_INT_EN_LEN   (6U)
#define LZ4_DST_INT_EN_MSK   (((1U << LZ4_DST_INT_EN_LEN) - 1) << LZ4_DST_INT_EN_POS)
#define LZ4_DST_INT_EN_UMSK  (~(((1U << LZ4_DST_INT_EN_LEN) - 1) << LZ4_DST_INT_EN_POS))
#define LZ4_DST_INT_INV      LZ4_DST_INT_INV
#define LZ4_DST_INT_INV_POS  (26U)
#define LZ4_DST_INT_INV_LEN  (6U)
#define LZ4_DST_INT_INV_MSK  (((1U << LZ4_DST_INT_INV_LEN) - 1) << LZ4_DST_INT_INV_POS)
#define LZ4_DST_INT_INV_UMSK (~(((1U << LZ4_DST_INT_INV_LEN) - 1) << LZ4_DST_INT_INV_POS))

/* 0x24 : lz4_int_sta */
#define LZ4_INT_STA_OFFSET   (0x24)
#define LZ4_DONE_STA         LZ4_DONE_STA
#define LZ4_DONE_STA_POS     (0U)
#define LZ4_DONE_STA_LEN     (1U)
#define LZ4_DONE_STA_MSK     (((1U << LZ4_DONE_STA_LEN) - 1) << LZ4_DONE_STA_POS)
#define LZ4_DONE_STA_UMSK    (~(((1U << LZ4_DONE_STA_LEN) - 1) << LZ4_DONE_STA_POS))
#define LZ4_ERR_STA          LZ4_ERR_STA
#define LZ4_ERR_STA_POS      (1U)
#define LZ4_ERR_STA_LEN      (1U)
#define LZ4_ERR_STA_MSK      (((1U << LZ4_ERR_STA_LEN) - 1) << LZ4_ERR_STA_POS)
#define LZ4_ERR_STA_UMSK     (~(((1U << LZ4_ERR_STA_LEN) - 1) << LZ4_ERR_STA_POS))
#define LZ4_DST_INT_STA      LZ4_DST_INT_STA
#define LZ4_DST_INT_STA_POS  (10U)
#define LZ4_DST_INT_STA_LEN  (6U)
#define LZ4_DST_INT_STA_MSK  (((1U << LZ4_DST_INT_STA_LEN) - 1) << LZ4_DST_INT_STA_POS)
#define LZ4_DST_INT_STA_UMSK (~(((1U << LZ4_DST_INT_STA_LEN) - 1) << LZ4_DST_INT_STA_POS))

/* 0x28 : lz4_monitor */
#define LZ4_MONITOR_OFFSET (0x28)
#define LZ4_CS             LZ4_CS
#define LZ4_CS_POS         (0U)
#define LZ4_CS_LEN         (4U)
#define LZ4_CS_MSK         (((1U << LZ4_CS_LEN) - 1) << LZ4_CS_POS)
#define LZ4_CS_UMSK        (~(((1U << LZ4_CS_LEN) - 1) << LZ4_CS_POS))

struct lz4_reg {
    /* 0x0 : lz4_config */
    union {
        struct {
            uint32_t lz4_en        : 1;  /* [    0],        r/w,        0x0 */
            uint32_t lz4_suspend   : 1;  /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_3  : 2;  /* [ 3: 2],       rsvd,        0x0 */
            uint32_t lz4_checksum  : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_27 : 23; /* [27: 5],       rsvd,        0x0 */
            uint32_t rsvd_31_28    : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } lz4_config;

    /* 0x4 : lz4_src_fix */
    union {
        struct {
            uint32_t reserved_0_11  : 12; /* [11: 0],       rsvd,        0x0 */
            uint32_t lz4_src_fix    : 14; /* [25:12],        r/w,        0x0 */
            uint32_t reserved_26_31 : 6;  /* [31:26],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } lz4_src_fix;

    /* 0x8 : lz4_dst_fix */
    union {
        struct {
            uint32_t reserved_0_11  : 12; /* [11: 0],       rsvd,        0x0 */
            uint32_t lz4_dst_fix    : 14; /* [25:12],        r/w,        0x0 */
            uint32_t reserved_26_31 : 6;  /* [31:26],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } lz4_dst_fix;

    /* 0xc  reserved */
    uint8_t RESERVED0xc[4];

    /* 0x10 : lz4_src_start */
    union {
        struct {
            uint32_t lz4_src_start : 26; /* [25: 0],        r/w,        0x0 */
            uint32_t lz4_src_base  : 6;  /* [31:26],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } lz4_src_start;

    /* 0x14 : lz4_src_end */
    union {
        struct {
            uint32_t lz4_src_end    : 26; /* [25: 0],          r,        0x0 */
            uint32_t reserved_26_31 : 6;  /* [31:26],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } lz4_src_end;

    /* 0x18 : lz4_dst_start */
    union {
        struct {
            uint32_t lz4_dst_start : 26; /* [25: 0],        r/w,        0x0 */
            uint32_t lz4_dst_base  : 6;  /* [31:26],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } lz4_dst_start;

    /* 0x1C : lz4_dst_end */
    union {
        struct {
            uint32_t lz4_dst_end    : 26; /* [25: 0],          r,        0x0 */
            uint32_t reserved_26_31 : 6;  /* [31:26],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } lz4_dst_end;

    /* 0x20 : lz4_int_en */
    union {
        struct {
            uint32_t lz4_done_en     : 1;  /* [    0],        r/w,        0x1 */
            uint32_t lz4_err_en      : 1;  /* [    1],        r/w,        0x1 */
            uint32_t reserved_2_9    : 8;  /* [ 9: 2],       rsvd,        0x0 */
            uint32_t lz4_dst_int_en  : 6;  /* [15:10],        r/w,        0x0 */
            uint32_t reserved_16_25  : 10; /* [25:16],       rsvd,        0x0 */
            uint32_t lz4_dst_int_inv : 6;  /* [31:26],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } lz4_int_en;

    /* 0x24 : lz4_int_sta */
    union {
        struct {
            uint32_t lz4_done_sta    : 1;  /* [    0],          r,        0x0 */
            uint32_t lz4_err_sta     : 1;  /* [    1],          r,        0x0 */
            uint32_t reserved_2_9    : 8;  /* [ 9: 2],       rsvd,        0x0 */
            uint32_t lz4_dst_int_sta : 6;  /* [15:10],          r,        0x0 */
            uint32_t reserved_16_31  : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } lz4_int_sta;

    /* 0x28 : lz4_monitor */
    union {
        struct {
            uint32_t lz4_cs        : 4;  /* [ 3: 0],          r,        0x0 */
            uint32_t reserved_4_31 : 28; /* [31: 4],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } lz4_monitor;
};

typedef volatile struct lz4_reg lz4_reg_t;

#endif /* __LZ4_REG_H__ */
