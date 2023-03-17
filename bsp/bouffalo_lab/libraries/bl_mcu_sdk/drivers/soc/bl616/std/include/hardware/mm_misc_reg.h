/**
  ******************************************************************************
  * @file    mm_misc_reg.h
  * @version V1.0
  * @date    2021-11-13
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
#ifndef __MM_MISC_REG_H__
#define __MM_MISC_REG_H__

#include "bl616.h"

/* 0x0 : config */
#define MM_MISC_CONFIG_OFFSET          (0x0)
#define MM_MISC_RG_DVPAS_ENABLE        MM_MISC_RG_DVPAS_ENABLE
#define MM_MISC_RG_DVPAS_ENABLE_POS    (0U)
#define MM_MISC_RG_DVPAS_ENABLE_LEN    (1U)
#define MM_MISC_RG_DVPAS_ENABLE_MSK    (((1U << MM_MISC_RG_DVPAS_ENABLE_LEN) - 1) << MM_MISC_RG_DVPAS_ENABLE_POS)
#define MM_MISC_RG_DVPAS_ENABLE_UMSK   (~(((1U << MM_MISC_RG_DVPAS_ENABLE_LEN) - 1) << MM_MISC_RG_DVPAS_ENABLE_POS))
#define MM_MISC_RG_DVPAS_HS_INV        MM_MISC_RG_DVPAS_HS_INV
#define MM_MISC_RG_DVPAS_HS_INV_POS    (1U)
#define MM_MISC_RG_DVPAS_HS_INV_LEN    (1U)
#define MM_MISC_RG_DVPAS_HS_INV_MSK    (((1U << MM_MISC_RG_DVPAS_HS_INV_LEN) - 1) << MM_MISC_RG_DVPAS_HS_INV_POS)
#define MM_MISC_RG_DVPAS_HS_INV_UMSK   (~(((1U << MM_MISC_RG_DVPAS_HS_INV_LEN) - 1) << MM_MISC_RG_DVPAS_HS_INV_POS))
#define MM_MISC_RG_DVPAS_VS_INV        MM_MISC_RG_DVPAS_VS_INV
#define MM_MISC_RG_DVPAS_VS_INV_POS    (2U)
#define MM_MISC_RG_DVPAS_VS_INV_LEN    (1U)
#define MM_MISC_RG_DVPAS_VS_INV_MSK    (((1U << MM_MISC_RG_DVPAS_VS_INV_LEN) - 1) << MM_MISC_RG_DVPAS_VS_INV_POS)
#define MM_MISC_RG_DVPAS_VS_INV_UMSK   (~(((1U << MM_MISC_RG_DVPAS_VS_INV_LEN) - 1) << MM_MISC_RG_DVPAS_VS_INV_POS))
#define MM_MISC_RG_DVPAS_DA_ORDER      MM_MISC_RG_DVPAS_DA_ORDER
#define MM_MISC_RG_DVPAS_DA_ORDER_POS  (3U)
#define MM_MISC_RG_DVPAS_DA_ORDER_LEN  (1U)
#define MM_MISC_RG_DVPAS_DA_ORDER_MSK  (((1U << MM_MISC_RG_DVPAS_DA_ORDER_LEN) - 1) << MM_MISC_RG_DVPAS_DA_ORDER_POS)
#define MM_MISC_RG_DVPAS_DA_ORDER_UMSK (~(((1U << MM_MISC_RG_DVPAS_DA_ORDER_LEN) - 1) << MM_MISC_RG_DVPAS_DA_ORDER_POS))
#define MM_MISC_RG_DVPAS_FIFO_TH       MM_MISC_RG_DVPAS_FIFO_TH
#define MM_MISC_RG_DVPAS_FIFO_TH_POS   (16U)
#define MM_MISC_RG_DVPAS_FIFO_TH_LEN   (11U)
#define MM_MISC_RG_DVPAS_FIFO_TH_MSK   (((1U << MM_MISC_RG_DVPAS_FIFO_TH_LEN) - 1) << MM_MISC_RG_DVPAS_FIFO_TH_POS)
#define MM_MISC_RG_DVPAS_FIFO_TH_UMSK  (~(((1U << MM_MISC_RG_DVPAS_FIFO_TH_LEN) - 1) << MM_MISC_RG_DVPAS_FIFO_TH_POS))

/* 0x8 : dvp2bus_src_sel_1 */
#define MM_MISC_DVP2BUS_SRC_SEL_1_OFFSET (0x8)
#define MM_MISC_RG_D2X_DVP_SEL           MM_MISC_RG_D2X_DVP_SEL
#define MM_MISC_RG_D2X_DVP_SEL_POS       (0U)
#define MM_MISC_RG_D2X_DVP_SEL_LEN       (1U)
#define MM_MISC_RG_D2X_DVP_SEL_MSK       (((1U << MM_MISC_RG_D2X_DVP_SEL_LEN) - 1) << MM_MISC_RG_D2X_DVP_SEL_POS)
#define MM_MISC_RG_D2X_DVP_SEL_UMSK      (~(((1U << MM_MISC_RG_D2X_DVP_SEL_LEN) - 1) << MM_MISC_RG_D2X_DVP_SEL_POS))

/* 0xC : snsr_ctrl */
#define MM_MISC_SNSR_CTRL_OFFSET  (0xC)
#define MM_MISC_RG_SNSR_RST       MM_MISC_RG_SNSR_RST
#define MM_MISC_RG_SNSR_RST_POS   (0U)
#define MM_MISC_RG_SNSR_RST_LEN   (1U)
#define MM_MISC_RG_SNSR_RST_MSK   (((1U << MM_MISC_RG_SNSR_RST_LEN) - 1) << MM_MISC_RG_SNSR_RST_POS)
#define MM_MISC_RG_SNSR_RST_UMSK  (~(((1U << MM_MISC_RG_SNSR_RST_LEN) - 1) << MM_MISC_RG_SNSR_RST_POS))
#define MM_MISC_RG_SNSR_PWDN      MM_MISC_RG_SNSR_PWDN
#define MM_MISC_RG_SNSR_PWDN_POS  (1U)
#define MM_MISC_RG_SNSR_PWDN_LEN  (1U)
#define MM_MISC_RG_SNSR_PWDN_MSK  (((1U << MM_MISC_RG_SNSR_PWDN_LEN) - 1) << MM_MISC_RG_SNSR_PWDN_POS)
#define MM_MISC_RG_SNSR_PWDN_UMSK (~(((1U << MM_MISC_RG_SNSR_PWDN_LEN) - 1) << MM_MISC_RG_SNSR_PWDN_POS))

/* 0x10 : emi_misc */
#define MM_MISC_EMI_MISC_OFFSET       (0x10)
#define MM_MISC_REG_X_WTHRE_PB        MM_MISC_REG_X_WTHRE_PB
#define MM_MISC_REG_X_WTHRE_PB_POS    (0U)
#define MM_MISC_REG_X_WTHRE_PB_LEN    (2U)
#define MM_MISC_REG_X_WTHRE_PB_MSK    (((1U << MM_MISC_REG_X_WTHRE_PB_LEN) - 1) << MM_MISC_REG_X_WTHRE_PB_POS)
#define MM_MISC_REG_X_WTHRE_PB_UMSK   (~(((1U << MM_MISC_REG_X_WTHRE_PB_LEN) - 1) << MM_MISC_REG_X_WTHRE_PB_POS))
#define MM_MISC_REG_SF_HARB_MODE      MM_MISC_REG_SF_HARB_MODE
#define MM_MISC_REG_SF_HARB_MODE_POS  (4U)
#define MM_MISC_REG_SF_HARB_MODE_LEN  (1U)
#define MM_MISC_REG_SF_HARB_MODE_MSK  (((1U << MM_MISC_REG_SF_HARB_MODE_LEN) - 1) << MM_MISC_REG_SF_HARB_MODE_POS)
#define MM_MISC_REG_SF_HARB_MODE_UMSK (~(((1U << MM_MISC_REG_SF_HARB_MODE_LEN) - 1) << MM_MISC_REG_SF_HARB_MODE_POS))

/* 0x14 : isp_id_yuv */
#define MM_MISC_ISP_ID_YUV_OFFSET           (0x14)
#define MM_MISC_REG_YUV_IDGEN_RST           MM_MISC_REG_YUV_IDGEN_RST
#define MM_MISC_REG_YUV_IDGEN_RST_POS       (0U)
#define MM_MISC_REG_YUV_IDGEN_RST_LEN       (1U)
#define MM_MISC_REG_YUV_IDGEN_RST_MSK       (((1U << MM_MISC_REG_YUV_IDGEN_RST_LEN) - 1) << MM_MISC_REG_YUV_IDGEN_RST_POS)
#define MM_MISC_REG_YUV_IDGEN_RST_UMSK      (~(((1U << MM_MISC_REG_YUV_IDGEN_RST_LEN) - 1) << MM_MISC_REG_YUV_IDGEN_RST_POS))
#define MM_MISC_REG_YUV_IDGEN_EDGE          MM_MISC_REG_YUV_IDGEN_EDGE
#define MM_MISC_REG_YUV_IDGEN_EDGE_POS      (1U)
#define MM_MISC_REG_YUV_IDGEN_EDGE_LEN      (1U)
#define MM_MISC_REG_YUV_IDGEN_EDGE_MSK      (((1U << MM_MISC_REG_YUV_IDGEN_EDGE_LEN) - 1) << MM_MISC_REG_YUV_IDGEN_EDGE_POS)
#define MM_MISC_REG_YUV_IDGEN_EDGE_UMSK     (~(((1U << MM_MISC_REG_YUV_IDGEN_EDGE_LEN) - 1) << MM_MISC_REG_YUV_IDGEN_EDGE_POS))
#define MM_MISC_REG_YUV_IDGEN_CNT_INCR      MM_MISC_REG_YUV_IDGEN_CNT_INCR
#define MM_MISC_REG_YUV_IDGEN_CNT_INCR_POS  (16U)
#define MM_MISC_REG_YUV_IDGEN_CNT_INCR_LEN  (16U)
#define MM_MISC_REG_YUV_IDGEN_CNT_INCR_MSK  (((1U << MM_MISC_REG_YUV_IDGEN_CNT_INCR_LEN) - 1) << MM_MISC_REG_YUV_IDGEN_CNT_INCR_POS)
#define MM_MISC_REG_YUV_IDGEN_CNT_INCR_UMSK (~(((1U << MM_MISC_REG_YUV_IDGEN_CNT_INCR_LEN) - 1) << MM_MISC_REG_YUV_IDGEN_CNT_INCR_POS))

/* 0x100 : mm_mbist_ctrl */
#define MM_MISC_MM_MBIST_CTRL_OFFSET (0x100)
#define MM_MISC_MBIST_MODE           MM_MISC_MBIST_MODE
#define MM_MISC_MBIST_MODE_POS       (0U)
#define MM_MISC_MBIST_MODE_LEN       (1U)
#define MM_MISC_MBIST_MODE_MSK       (((1U << MM_MISC_MBIST_MODE_LEN) - 1) << MM_MISC_MBIST_MODE_POS)
#define MM_MISC_MBIST_MODE_UMSK      (~(((1U << MM_MISC_MBIST_MODE_LEN) - 1) << MM_MISC_MBIST_MODE_POS))
#define MM_MISC_REG_MBIST_RST_N      MM_MISC_REG_MBIST_RST_N
#define MM_MISC_REG_MBIST_RST_N_POS  (1U)
#define MM_MISC_REG_MBIST_RST_N_LEN  (1U)
#define MM_MISC_REG_MBIST_RST_N_MSK  (((1U << MM_MISC_REG_MBIST_RST_N_LEN) - 1) << MM_MISC_REG_MBIST_RST_N_POS)
#define MM_MISC_REG_MBIST_RST_N_UMSK (~(((1U << MM_MISC_REG_MBIST_RST_N_LEN) - 1) << MM_MISC_REG_MBIST_RST_N_POS))
#define MM_MISC_NAP                  MM_MISC_NAP
#define MM_MISC_NAP_POS              (4U)
#define MM_MISC_NAP_LEN              (1U)
#define MM_MISC_NAP_MSK              (((1U << MM_MISC_NAP_LEN) - 1) << MM_MISC_NAP_POS)
#define MM_MISC_NAP_UMSK             (~(((1U << MM_MISC_NAP_LEN) - 1) << MM_MISC_NAP_POS))
#define MM_MISC_DVSE                 MM_MISC_DVSE
#define MM_MISC_DVSE_POS             (5U)
#define MM_MISC_DVSE_LEN             (1U)
#define MM_MISC_DVSE_MSK             (((1U << MM_MISC_DVSE_LEN) - 1) << MM_MISC_DVSE_POS)
#define MM_MISC_DVSE_UMSK            (~(((1U << MM_MISC_DVSE_LEN) - 1) << MM_MISC_DVSE_POS))
#define MM_MISC_DVS                  MM_MISC_DVS
#define MM_MISC_DVS_POS              (8U)
#define MM_MISC_DVS_LEN              (4U)
#define MM_MISC_DVS_MSK              (((1U << MM_MISC_DVS_LEN) - 1) << MM_MISC_DVS_POS)
#define MM_MISC_DVS_UMSK             (~(((1U << MM_MISC_DVS_LEN) - 1) << MM_MISC_DVS_POS))
#define MM_MISC_MM_MBIST_DONE        MM_MISC_MM_MBIST_DONE
#define MM_MISC_MM_MBIST_DONE_POS    (16U)
#define MM_MISC_MM_MBIST_DONE_LEN    (7U)
#define MM_MISC_MM_MBIST_DONE_MSK    (((1U << MM_MISC_MM_MBIST_DONE_LEN) - 1) << MM_MISC_MM_MBIST_DONE_POS)
#define MM_MISC_MM_MBIST_DONE_UMSK   (~(((1U << MM_MISC_MM_MBIST_DONE_LEN) - 1) << MM_MISC_MM_MBIST_DONE_POS))
#define MM_MISC_MM_MBIST_FAIL        MM_MISC_MM_MBIST_FAIL
#define MM_MISC_MM_MBIST_FAIL_POS    (24U)
#define MM_MISC_MM_MBIST_FAIL_LEN    (7U)
#define MM_MISC_MM_MBIST_FAIL_MSK    (((1U << MM_MISC_MM_MBIST_FAIL_LEN) - 1) << MM_MISC_MM_MBIST_FAIL_POS)
#define MM_MISC_MM_MBIST_FAIL_UMSK   (~(((1U << MM_MISC_MM_MBIST_FAIL_LEN) - 1) << MM_MISC_MM_MBIST_FAIL_POS))

struct mm_misc_reg {
    /* 0x0 : config */
    union {
        struct {
            uint32_t rg_dvpas_enable   : 1;  /* [    0],        r/w,        0x0 */
            uint32_t rg_dvpas_hs_inv   : 1;  /* [    1],        r/w,        0x0 */
            uint32_t rg_dvpas_vs_inv   : 1;  /* [    2],        r/w,        0x0 */
            uint32_t rg_dvpas_da_order : 1;  /* [    3],        r/w,        0x0 */
            uint32_t reserved_4_15     : 12; /* [15: 4],       rsvd,        0x0 */
            uint32_t rg_dvpas_fifo_th  : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } config;

    /* 0x4  reserved */
    uint8_t RESERVED0x4[4];

    /* 0x8 : dvp2bus_src_sel_1 */
    union {
        struct {
            uint32_t rg_d2x_dvp_sel : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_31  : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } dvp2bus_src_sel_1;

    /* 0xC : snsr_ctrl */
    union {
        struct {
            uint32_t rg_snsr_rst   : 1;  /* [    0],        r/w,        0x0 */
            uint32_t rg_snsr_pwdn  : 1;  /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_31 : 30; /* [31: 2],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } snsr_ctrl;

    /* 0x10 : emi_misc */
    union {
        struct {
            uint32_t reg_x_wthre_pB   : 2;  /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_3     : 2;  /* [ 3: 2],       rsvd,        0x0 */
            uint32_t reg_sf_harb_mode : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_31    : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } emi_misc;

    /* 0x14 : isp_id_yuv */
    union {
        struct {
            uint32_t reg_yuv_idgen_rst      : 1;  /* [    0],        w1p,        0x0 */
            uint32_t reg_yuv_idgen_edge     : 1;  /* [    1],        r/w,        0x1 */
            uint32_t reserved_2_15          : 14; /* [15: 2],       rsvd,        0x0 */
            uint32_t reg_yuv_idgen_cnt_incr : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } isp_id_yuv;

    /* 0x18  reserved */
    uint8_t RESERVED0x18[232];

    /* 0x100 : mm_mbist_ctrl */
    union {
        struct {
            uint32_t mbist_mode      : 1; /* [    0],        r/w,        0x0 */
            uint32_t reg_mbist_rst_n : 1; /* [    1],        r/w,        0x1 */
            uint32_t reserved_2_3    : 2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t NAP             : 1; /* [    4],        r/w,        0x0 */
            uint32_t DVSE            : 1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7    : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t DVS             : 4; /* [11: 8],        r/w,        0xc */
            uint32_t reserved_12_15  : 4; /* [15:12],       rsvd,        0x0 */
            uint32_t mm_mbist_done   : 7; /* [22:16],          r,        0x0 */
            uint32_t reserved_23     : 1; /* [   23],       rsvd,        0x0 */
            uint32_t mm_mbist_fail   : 7; /* [30:24],          r,        0x0 */
            uint32_t reserved_31     : 1; /* [   31],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mm_mbist_ctrl;
};

typedef volatile struct mm_misc_reg mm_misc_reg_t;

#endif /* __MM_MISC_REG_H__ */
