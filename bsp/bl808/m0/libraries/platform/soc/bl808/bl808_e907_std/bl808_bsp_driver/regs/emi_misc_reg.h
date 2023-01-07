/**
  ******************************************************************************
  * @file    emi_misc_reg.h
  * @version V1.0
  * @date    2021-09-10
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
#ifndef __EMI_MISC_REG_H__
#define __EMI_MISC_REG_H__

#include "bl808.h"

/* 0x00 : emi_bus_ctrl */
#define EMI_MISC_EMI_BUS_CTRL_OFFSET       (0x00)
#define EMI_MISC_RG_EMI_PCLK_FORCE_ON      EMI_MISC_RG_EMI_PCLK_FORCE_ON
#define EMI_MISC_RG_EMI_PCLK_FORCE_ON_POS  (0U)
#define EMI_MISC_RG_EMI_PCLK_FORCE_ON_LEN  (16U)
#define EMI_MISC_RG_EMI_PCLK_FORCE_ON_MSK  (((1U << EMI_MISC_RG_EMI_PCLK_FORCE_ON_LEN) - 1) << EMI_MISC_RG_EMI_PCLK_FORCE_ON_POS)
#define EMI_MISC_RG_EMI_PCLK_FORCE_ON_UMSK (~(((1U << EMI_MISC_RG_EMI_PCLK_FORCE_ON_LEN) - 1) << EMI_MISC_RG_EMI_PCLK_FORCE_ON_POS))

/* 0x04 : emi_bus_ctrl2 */
#define EMI_MISC_EMI_BUS_CTRL2_OFFSET  (0x04)
#define EMI_MISC_REG_SF_HARB_MODE      EMI_MISC_REG_SF_HARB_MODE
#define EMI_MISC_REG_SF_HARB_MODE_POS  (0U)
#define EMI_MISC_REG_SF_HARB_MODE_LEN  (1U)
#define EMI_MISC_REG_SF_HARB_MODE_MSK  (((1U << EMI_MISC_REG_SF_HARB_MODE_LEN) - 1) << EMI_MISC_REG_SF_HARB_MODE_POS)
#define EMI_MISC_REG_SF_HARB_MODE_UMSK (~(((1U << EMI_MISC_REG_SF_HARB_MODE_LEN) - 1) << EMI_MISC_REG_SF_HARB_MODE_POS))

/* 0x08 : emi_bus_thre */
#define EMI_MISC_EMI_BUS_THRE_OFFSET (0x08)
#define EMI_MISC_REG_X_WTHRE_PB      EMI_MISC_REG_X_WTHRE_PB
#define EMI_MISC_REG_X_WTHRE_PB_POS  (0U)
#define EMI_MISC_REG_X_WTHRE_PB_LEN  (2U)
#define EMI_MISC_REG_X_WTHRE_PB_MSK  (((1U << EMI_MISC_REG_X_WTHRE_PB_LEN) - 1) << EMI_MISC_REG_X_WTHRE_PB_POS)
#define EMI_MISC_REG_X_WTHRE_PB_UMSK (~(((1U << EMI_MISC_REG_X_WTHRE_PB_LEN) - 1) << EMI_MISC_REG_X_WTHRE_PB_POS))
#define EMI_MISC_REG_X_WTHRE_PA      EMI_MISC_REG_X_WTHRE_PA
#define EMI_MISC_REG_X_WTHRE_PA_POS  (2U)
#define EMI_MISC_REG_X_WTHRE_PA_LEN  (2U)
#define EMI_MISC_REG_X_WTHRE_PA_MSK  (((1U << EMI_MISC_REG_X_WTHRE_PA_LEN) - 1) << EMI_MISC_REG_X_WTHRE_PA_POS)
#define EMI_MISC_REG_X_WTHRE_PA_UMSK (~(((1U << EMI_MISC_REG_X_WTHRE_PA_LEN) - 1) << EMI_MISC_REG_X_WTHRE_PA_POS))

/* 0xFC : emi_misc_dummy */
#define EMI_MISC_DUMMY_OFFSET   (0xFC)
#define EMI_MISC_DUMMY_REG      EMI_MISC_DUMMY_REG
#define EMI_MISC_DUMMY_REG_POS  (0U)
#define EMI_MISC_DUMMY_REG_LEN  (32U)
#define EMI_MISC_DUMMY_REG_MSK  (((1U << EMI_MISC_DUMMY_REG_LEN) - 1) << EMI_MISC_DUMMY_REG_POS)
#define EMI_MISC_DUMMY_REG_UMSK (~(((1U << EMI_MISC_DUMMY_REG_LEN) - 1) << EMI_MISC_DUMMY_REG_POS))

struct emi_misc_reg {
    /* 0x00 : emi_bus_ctrl */
    union {
        struct {
            uint32_t rg_emi_pclk_force_on : 16; /* [15: 0],        r/w,     0xffff */
            uint32_t reserved_16_31       : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } emi_bus_ctrl;

    /* 0x04 : emi_bus_ctrl2 */
    union {
        struct {
            uint32_t reg_sf_harb_mode : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_31    : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } emi_bus_ctrl2;

    /* 0x08 : emi_bus_thre */
    union {
        struct {
            uint32_t reg_x_wthre_pB : 2;  /* [ 1: 0],        r/w,        0x0 */
            uint32_t reg_x_wthre_pA : 2;  /* [ 3: 2],        r/w,        0x0 */
            uint32_t reserved_4_31  : 28; /* [31: 4],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } emi_bus_thre;

    /* 0xc  reserved */
    uint8_t RESERVED0xc[240];

    /* 0xFC : emi_misc_dummy */
    union {
        struct {
            uint32_t dummy_reg : 32; /* [31: 0],        r/w, 0xffff0000 */
        } BF;
        uint32_t WORD;
    } emi_misc_dummy;
};

typedef volatile struct emi_misc_reg emi_misc_reg_t;

#endif /* __EMI_MISC_REG_H__ */
