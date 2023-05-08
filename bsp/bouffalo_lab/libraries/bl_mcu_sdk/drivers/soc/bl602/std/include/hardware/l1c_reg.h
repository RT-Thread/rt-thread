/**
  ******************************************************************************
  * @file    l1c_reg.h
  * @version V1.2
  * @date    2019-11-22
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 Bouffalo Lab</center></h2>
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
#ifndef __L1C_REG_H__
#define __L1C_REG_H__

#include "bl602.h"

/* 0x0 : l1c_config */
#define L1C_CONFIG_OFFSET            (0x0)
#define L1C_CACHEABLE                L1C_CACHEABLE
#define L1C_CACHEABLE_POS            (0U)
#define L1C_CACHEABLE_LEN            (1U)
#define L1C_CACHEABLE_MSK            (((1U << L1C_CACHEABLE_LEN) - 1) << L1C_CACHEABLE_POS)
#define L1C_CACHEABLE_UMSK           (~(((1U << L1C_CACHEABLE_LEN) - 1) << L1C_CACHEABLE_POS))
#define L1C_CNT_EN                   L1C_CNT_EN
#define L1C_CNT_EN_POS               (1U)
#define L1C_CNT_EN_LEN               (1U)
#define L1C_CNT_EN_MSK               (((1U << L1C_CNT_EN_LEN) - 1) << L1C_CNT_EN_POS)
#define L1C_CNT_EN_UMSK              (~(((1U << L1C_CNT_EN_LEN) - 1) << L1C_CNT_EN_POS))
#define L1C_INVALID_EN               L1C_INVALID_EN
#define L1C_INVALID_EN_POS           (2U)
#define L1C_INVALID_EN_LEN           (1U)
#define L1C_INVALID_EN_MSK           (((1U << L1C_INVALID_EN_LEN) - 1) << L1C_INVALID_EN_POS)
#define L1C_INVALID_EN_UMSK          (~(((1U << L1C_INVALID_EN_LEN) - 1) << L1C_INVALID_EN_POS))
#define L1C_INVALID_DONE             L1C_INVALID_DONE
#define L1C_INVALID_DONE_POS         (3U)
#define L1C_INVALID_DONE_LEN         (1U)
#define L1C_INVALID_DONE_MSK         (((1U << L1C_INVALID_DONE_LEN) - 1) << L1C_INVALID_DONE_POS)
#define L1C_INVALID_DONE_UMSK        (~(((1U << L1C_INVALID_DONE_LEN) - 1) << L1C_INVALID_DONE_POS))
#define L1C_WAY_DIS                  L1C_WAY_DIS
#define L1C_WAY_DIS_POS              (8U)
#define L1C_WAY_DIS_LEN              (4U)
#define L1C_WAY_DIS_MSK              (((1U << L1C_WAY_DIS_LEN) - 1) << L1C_WAY_DIS_POS)
#define L1C_WAY_DIS_UMSK             (~(((1U << L1C_WAY_DIS_LEN) - 1) << L1C_WAY_DIS_POS))
#define L1C_IROM_2T_ACCESS           L1C_IROM_2T_ACCESS
#define L1C_IROM_2T_ACCESS_POS       (12U)
#define L1C_IROM_2T_ACCESS_LEN       (1U)
#define L1C_IROM_2T_ACCESS_MSK       (((1U << L1C_IROM_2T_ACCESS_LEN) - 1) << L1C_IROM_2T_ACCESS_POS)
#define L1C_IROM_2T_ACCESS_UMSK      (~(((1U << L1C_IROM_2T_ACCESS_LEN) - 1) << L1C_IROM_2T_ACCESS_POS))
#define L1C_BYPASS                   L1C_BYPASS
#define L1C_BYPASS_POS               (14U)
#define L1C_BYPASS_LEN               (1U)
#define L1C_BYPASS_MSK               (((1U << L1C_BYPASS_LEN) - 1) << L1C_BYPASS_POS)
#define L1C_BYPASS_UMSK              (~(((1U << L1C_BYPASS_LEN) - 1) << L1C_BYPASS_POS))
#define L1C_BMX_ERR_EN               L1C_BMX_ERR_EN
#define L1C_BMX_ERR_EN_POS           (15U)
#define L1C_BMX_ERR_EN_LEN           (1U)
#define L1C_BMX_ERR_EN_MSK           (((1U << L1C_BMX_ERR_EN_LEN) - 1) << L1C_BMX_ERR_EN_POS)
#define L1C_BMX_ERR_EN_UMSK          (~(((1U << L1C_BMX_ERR_EN_LEN) - 1) << L1C_BMX_ERR_EN_POS))
#define L1C_BMX_ARB_MODE             L1C_BMX_ARB_MODE
#define L1C_BMX_ARB_MODE_POS         (16U)
#define L1C_BMX_ARB_MODE_LEN         (2U)
#define L1C_BMX_ARB_MODE_MSK         (((1U << L1C_BMX_ARB_MODE_LEN) - 1) << L1C_BMX_ARB_MODE_POS)
#define L1C_BMX_ARB_MODE_UMSK        (~(((1U << L1C_BMX_ARB_MODE_LEN) - 1) << L1C_BMX_ARB_MODE_POS))
#define L1C_BMX_TIMEOUT_EN           L1C_BMX_TIMEOUT_EN
#define L1C_BMX_TIMEOUT_EN_POS       (20U)
#define L1C_BMX_TIMEOUT_EN_LEN       (4U)
#define L1C_BMX_TIMEOUT_EN_MSK       (((1U << L1C_BMX_TIMEOUT_EN_LEN) - 1) << L1C_BMX_TIMEOUT_EN_POS)
#define L1C_BMX_TIMEOUT_EN_UMSK      (~(((1U << L1C_BMX_TIMEOUT_EN_LEN) - 1) << L1C_BMX_TIMEOUT_EN_POS))
#define L1C_BMX_BUSY_OPTION_DIS      L1C_BMX_BUSY_OPTION_DIS
#define L1C_BMX_BUSY_OPTION_DIS_POS  (24U)
#define L1C_BMX_BUSY_OPTION_DIS_LEN  (1U)
#define L1C_BMX_BUSY_OPTION_DIS_MSK  (((1U << L1C_BMX_BUSY_OPTION_DIS_LEN) - 1) << L1C_BMX_BUSY_OPTION_DIS_POS)
#define L1C_BMX_BUSY_OPTION_DIS_UMSK (~(((1U << L1C_BMX_BUSY_OPTION_DIS_LEN) - 1) << L1C_BMX_BUSY_OPTION_DIS_POS))
#define L1C_EARLY_RESP_DIS           L1C_EARLY_RESP_DIS
#define L1C_EARLY_RESP_DIS_POS       (25U)
#define L1C_EARLY_RESP_DIS_LEN       (1U)
#define L1C_EARLY_RESP_DIS_MSK       (((1U << L1C_EARLY_RESP_DIS_LEN) - 1) << L1C_EARLY_RESP_DIS_POS)
#define L1C_EARLY_RESP_DIS_UMSK      (~(((1U << L1C_EARLY_RESP_DIS_LEN) - 1) << L1C_EARLY_RESP_DIS_POS))
#define L1C_WRAP_DIS                 L1C_WRAP_DIS
#define L1C_WRAP_DIS_POS             (26U)
#define L1C_WRAP_DIS_LEN             (1U)
#define L1C_WRAP_DIS_MSK             (((1U << L1C_WRAP_DIS_LEN) - 1) << L1C_WRAP_DIS_POS)
#define L1C_WRAP_DIS_UMSK            (~(((1U << L1C_WRAP_DIS_LEN) - 1) << L1C_WRAP_DIS_POS))

/* 0x4 : hit_cnt_lsb */
#define L1C_HIT_CNT_LSB_OFFSET (0x4)
#define L1C_HIT_CNT_LSB        L1C_HIT_CNT_LSB
#define L1C_HIT_CNT_LSB_POS    (0U)
#define L1C_HIT_CNT_LSB_LEN    (32U)
#define L1C_HIT_CNT_LSB_MSK    (((1U << L1C_HIT_CNT_LSB_LEN) - 1) << L1C_HIT_CNT_LSB_POS)
#define L1C_HIT_CNT_LSB_UMSK   (~(((1U << L1C_HIT_CNT_LSB_LEN) - 1) << L1C_HIT_CNT_LSB_POS))

/* 0x8 : hit_cnt_msb */
#define L1C_HIT_CNT_MSB_OFFSET (0x8)
#define L1C_HIT_CNT_MSB        L1C_HIT_CNT_MSB
#define L1C_HIT_CNT_MSB_POS    (0U)
#define L1C_HIT_CNT_MSB_LEN    (32U)
#define L1C_HIT_CNT_MSB_MSK    (((1U << L1C_HIT_CNT_MSB_LEN) - 1) << L1C_HIT_CNT_MSB_POS)
#define L1C_HIT_CNT_MSB_UMSK   (~(((1U << L1C_HIT_CNT_MSB_LEN) - 1) << L1C_HIT_CNT_MSB_POS))

/* 0xC : miss_cnt */
#define L1C_MISS_CNT_OFFSET (0xC)
#define L1C_MISS_CNT        L1C_MISS_CNT
#define L1C_MISS_CNT_POS    (0U)
#define L1C_MISS_CNT_LEN    (32U)
#define L1C_MISS_CNT_MSK    (((1U << L1C_MISS_CNT_LEN) - 1) << L1C_MISS_CNT_POS)
#define L1C_MISS_CNT_UMSK   (~(((1U << L1C_MISS_CNT_LEN) - 1) << L1C_MISS_CNT_POS))

/* 0x10 : l1c_range */
#define L1C_RANGE_OFFSET (0x10)

/* 0x200 : l1c_bmx_err_addr_en */
#define L1C_BMX_ERR_ADDR_EN_OFFSET (0x200)
#define L1C_BMX_ERR_ADDR_DIS       L1C_BMX_ERR_ADDR_DIS
#define L1C_BMX_ERR_ADDR_DIS_POS   (0U)
#define L1C_BMX_ERR_ADDR_DIS_LEN   (1U)
#define L1C_BMX_ERR_ADDR_DIS_MSK   (((1U << L1C_BMX_ERR_ADDR_DIS_LEN) - 1) << L1C_BMX_ERR_ADDR_DIS_POS)
#define L1C_BMX_ERR_ADDR_DIS_UMSK  (~(((1U << L1C_BMX_ERR_ADDR_DIS_LEN) - 1) << L1C_BMX_ERR_ADDR_DIS_POS))
#define L1C_BMX_ERR_DEC            L1C_BMX_ERR_DEC
#define L1C_BMX_ERR_DEC_POS        (4U)
#define L1C_BMX_ERR_DEC_LEN        (1U)
#define L1C_BMX_ERR_DEC_MSK        (((1U << L1C_BMX_ERR_DEC_LEN) - 1) << L1C_BMX_ERR_DEC_POS)
#define L1C_BMX_ERR_DEC_UMSK       (~(((1U << L1C_BMX_ERR_DEC_LEN) - 1) << L1C_BMX_ERR_DEC_POS))
#define L1C_BMX_ERR_TZ             L1C_BMX_ERR_TZ
#define L1C_BMX_ERR_TZ_POS         (5U)
#define L1C_BMX_ERR_TZ_LEN         (1U)
#define L1C_BMX_ERR_TZ_MSK         (((1U << L1C_BMX_ERR_TZ_LEN) - 1) << L1C_BMX_ERR_TZ_POS)
#define L1C_BMX_ERR_TZ_UMSK        (~(((1U << L1C_BMX_ERR_TZ_LEN) - 1) << L1C_BMX_ERR_TZ_POS))
#define L1C_HSEL_OPTION            L1C_HSEL_OPTION
#define L1C_HSEL_OPTION_POS        (16U)
#define L1C_HSEL_OPTION_LEN        (4U)
#define L1C_HSEL_OPTION_MSK        (((1U << L1C_HSEL_OPTION_LEN) - 1) << L1C_HSEL_OPTION_POS)
#define L1C_HSEL_OPTION_UMSK       (~(((1U << L1C_HSEL_OPTION_LEN) - 1) << L1C_HSEL_OPTION_POS))

/* 0x204 : l1c_bmx_err_addr */
#define L1C_BMX_ERR_ADDR_OFFSET (0x204)
#define L1C_BMX_ERR_ADDR        L1C_BMX_ERR_ADDR
#define L1C_BMX_ERR_ADDR_POS    (0U)
#define L1C_BMX_ERR_ADDR_LEN    (32U)
#define L1C_BMX_ERR_ADDR_MSK    (((1U << L1C_BMX_ERR_ADDR_LEN) - 1) << L1C_BMX_ERR_ADDR_POS)
#define L1C_BMX_ERR_ADDR_UMSK   (~(((1U << L1C_BMX_ERR_ADDR_LEN) - 1) << L1C_BMX_ERR_ADDR_POS))

/* 0x208 : irom1_misr_dataout_0 */
#define L1C_IROM1_MISR_DATAOUT_0_OFFSET (0x208)
#define L1C_IROM1_MISR_DATAOUT_0        L1C_IROM1_MISR_DATAOUT_0
#define L1C_IROM1_MISR_DATAOUT_0_POS    (0U)
#define L1C_IROM1_MISR_DATAOUT_0_LEN    (32U)
#define L1C_IROM1_MISR_DATAOUT_0_MSK    (((1U << L1C_IROM1_MISR_DATAOUT_0_LEN) - 1) << L1C_IROM1_MISR_DATAOUT_0_POS)
#define L1C_IROM1_MISR_DATAOUT_0_UMSK   (~(((1U << L1C_IROM1_MISR_DATAOUT_0_LEN) - 1) << L1C_IROM1_MISR_DATAOUT_0_POS))

/* 0x20C : irom1_misr_dataout_1 */
#define L1C_IROM1_MISR_DATAOUT_1_OFFSET (0x20C)

/* 0x210 : cpu_clk_gate */
#define L1C_CPU_CLK_GATE_OFFSET       (0x210)
#define L1C_FORCE_E21_CLOCK_ON_0      L1C_FORCE_E21_CLOCK_ON_0
#define L1C_FORCE_E21_CLOCK_ON_0_POS  (0U)
#define L1C_FORCE_E21_CLOCK_ON_0_LEN  (1U)
#define L1C_FORCE_E21_CLOCK_ON_0_MSK  (((1U << L1C_FORCE_E21_CLOCK_ON_0_LEN) - 1) << L1C_FORCE_E21_CLOCK_ON_0_POS)
#define L1C_FORCE_E21_CLOCK_ON_0_UMSK (~(((1U << L1C_FORCE_E21_CLOCK_ON_0_LEN) - 1) << L1C_FORCE_E21_CLOCK_ON_0_POS))
#define L1C_FORCE_E21_CLOCK_ON_1      L1C_FORCE_E21_CLOCK_ON_1
#define L1C_FORCE_E21_CLOCK_ON_1_POS  (1U)
#define L1C_FORCE_E21_CLOCK_ON_1_LEN  (1U)
#define L1C_FORCE_E21_CLOCK_ON_1_MSK  (((1U << L1C_FORCE_E21_CLOCK_ON_1_LEN) - 1) << L1C_FORCE_E21_CLOCK_ON_1_POS)
#define L1C_FORCE_E21_CLOCK_ON_1_UMSK (~(((1U << L1C_FORCE_E21_CLOCK_ON_1_LEN) - 1) << L1C_FORCE_E21_CLOCK_ON_1_POS))
#define L1C_FORCE_E21_CLOCK_ON_2      L1C_FORCE_E21_CLOCK_ON_2
#define L1C_FORCE_E21_CLOCK_ON_2_POS  (2U)
#define L1C_FORCE_E21_CLOCK_ON_2_LEN  (1U)
#define L1C_FORCE_E21_CLOCK_ON_2_MSK  (((1U << L1C_FORCE_E21_CLOCK_ON_2_LEN) - 1) << L1C_FORCE_E21_CLOCK_ON_2_POS)
#define L1C_FORCE_E21_CLOCK_ON_2_UMSK (~(((1U << L1C_FORCE_E21_CLOCK_ON_2_LEN) - 1) << L1C_FORCE_E21_CLOCK_ON_2_POS))

struct l1c_reg {
    /* 0x0 : l1c_config */
    union {
        struct
        {
            uint32_t l1c_cacheable           : 1; /* [    0],        r/w,        0x0 */
            uint32_t l1c_cnt_en              : 1; /* [    1],        r/w,        0x0 */
            uint32_t l1c_invalid_en          : 1; /* [    2],        r/w,        0x0 */
            uint32_t l1c_invalid_done        : 1; /* [    3],          r,        0x0 */
            uint32_t reserved_4_7            : 4; /* [ 7: 4],       rsvd,        0x0 */
            uint32_t l1c_way_dis             : 4; /* [11: 8],        r/w,        0xf */
            uint32_t irom_2t_access          : 1; /* [   12],        r/w,        0x0 */
            uint32_t reserved_13             : 1; /* [   13],       rsvd,        0x0 */
            uint32_t l1c_bypass              : 1; /* [   14],        r/w,        0x0 */
            uint32_t l1c_bmx_err_en          : 1; /* [   15],        r/w,        0x0 */
            uint32_t l1c_bmx_arb_mode        : 2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_19          : 2; /* [19:18],       rsvd,        0x0 */
            uint32_t l1c_bmx_timeout_en      : 4; /* [23:20],        r/w,        0x0 */
            uint32_t l1c_bmx_busy_option_dis : 1; /* [   24],        r/w,        0x0 */
            uint32_t early_resp_dis          : 1; /* [   25],        r/w,        0x1 */
            uint32_t wrap_dis                : 1; /* [   26],        r/w,        0x1 */
            uint32_t reserved_27_31          : 5; /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } l1c_config;

    /* 0x4 : hit_cnt_lsb */
    union {
        struct
        {
            uint32_t hit_cnt_lsb : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } hit_cnt_lsb;

    /* 0x8 : hit_cnt_msb */
    union {
        struct
        {
            uint32_t hit_cnt_msb : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } hit_cnt_msb;

    /* 0xC : miss_cnt */
    union {
        struct
        {
            uint32_t miss_cnt : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } miss_cnt;

    /* 0x10 : l1c_range */
    union {
        struct
        {
            uint32_t reserved_0_31 : 32; /* [31: 0],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } l1c_range;

    /* 0x14  reserved */
    uint8_t RESERVED0x14[492];

    /* 0x200 : l1c_bmx_err_addr_en */
    union {
        struct
        {
            uint32_t l1c_bmx_err_addr_dis : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_3         : 3;  /* [ 3: 1],       rsvd,        0x0 */
            uint32_t l1c_bmx_err_dec      : 1;  /* [    4],          r,        0x0 */
            uint32_t l1c_bmx_err_tz       : 1;  /* [    5],          r,        0x0 */
            uint32_t reserved_6_15        : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t l1c_hsel_option      : 4;  /* [19:16],        r/w,        0x0 */
            uint32_t reserved_20_31       : 12; /* [31:20],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } l1c_bmx_err_addr_en;

    /* 0x204 : l1c_bmx_err_addr */
    union {
        struct
        {
            uint32_t l1c_bmx_err_addr : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } l1c_bmx_err_addr;

    /* 0x208 : irom1_misr_dataout_0 */
    union {
        struct
        {
            uint32_t irom1_misr_dataout_0 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } irom1_misr_dataout_0;

    /* 0x20C : irom1_misr_dataout_1 */
    union {
        struct
        {
            uint32_t reserved_0_31 : 32; /* [31: 0],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } irom1_misr_dataout_1;

    /* 0x210 : cpu_clk_gate */
    union {
        struct
        {
            uint32_t force_e21_clock_on_0 : 1;  /* [    0],        r/w,        0x0 */
            uint32_t force_e21_clock_on_1 : 1;  /* [    1],        r/w,        0x0 */
            uint32_t force_e21_clock_on_2 : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_31        : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } cpu_clk_gate;
};

typedef volatile struct l1c_reg l1c_reg_t;

#endif /* __L1C_REG_H__ */
