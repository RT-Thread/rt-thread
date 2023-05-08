/**
  ******************************************************************************
  * @file    cci_reg.h
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
#ifndef __CCI_REG_H__
#define __CCI_REG_H__

#include "bl616.h"

/* 0x0 : cci_cfg */
#define CCI_CFG_OFFSET              (0x0)
#define CCI_EN                      CCI_EN
#define CCI_EN_POS                  (0U)
#define CCI_EN_LEN                  (1U)
#define CCI_EN_MSK                  (((1U << CCI_EN_LEN) - 1) << CCI_EN_POS)
#define CCI_EN_UMSK                 (~(((1U << CCI_EN_LEN) - 1) << CCI_EN_POS))
#define CCI_SLV_SEL_CCI2            CCI_SLV_SEL_CCI2
#define CCI_SLV_SEL_CCI2_POS        (1U)
#define CCI_SLV_SEL_CCI2_LEN        (1U)
#define CCI_SLV_SEL_CCI2_MSK        (((1U << CCI_SLV_SEL_CCI2_LEN) - 1) << CCI_SLV_SEL_CCI2_POS)
#define CCI_SLV_SEL_CCI2_UMSK       (~(((1U << CCI_SLV_SEL_CCI2_LEN) - 1) << CCI_SLV_SEL_CCI2_POS))
#define CCI_MAS_SEL_CCI2            CCI_MAS_SEL_CCI2
#define CCI_MAS_SEL_CCI2_POS        (2U)
#define CCI_MAS_SEL_CCI2_LEN        (1U)
#define CCI_MAS_SEL_CCI2_MSK        (((1U << CCI_MAS_SEL_CCI2_LEN) - 1) << CCI_MAS_SEL_CCI2_POS)
#define CCI_MAS_SEL_CCI2_UMSK       (~(((1U << CCI_MAS_SEL_CCI2_LEN) - 1) << CCI_MAS_SEL_CCI2_POS))
#define CCI_MAS_HW_MODE             CCI_MAS_HW_MODE
#define CCI_MAS_HW_MODE_POS         (3U)
#define CCI_MAS_HW_MODE_LEN         (1U)
#define CCI_MAS_HW_MODE_MSK         (((1U << CCI_MAS_HW_MODE_LEN) - 1) << CCI_MAS_HW_MODE_POS)
#define CCI_MAS_HW_MODE_UMSK        (~(((1U << CCI_MAS_HW_MODE_LEN) - 1) << CCI_MAS_HW_MODE_POS))
#define CCI_REG_M_CCI_SCLK_EN       CCI_REG_M_CCI_SCLK_EN
#define CCI_REG_M_CCI_SCLK_EN_POS   (4U)
#define CCI_REG_M_CCI_SCLK_EN_LEN   (1U)
#define CCI_REG_M_CCI_SCLK_EN_MSK   (((1U << CCI_REG_M_CCI_SCLK_EN_LEN) - 1) << CCI_REG_M_CCI_SCLK_EN_POS)
#define CCI_REG_M_CCI_SCLK_EN_UMSK  (~(((1U << CCI_REG_M_CCI_SCLK_EN_LEN) - 1) << CCI_REG_M_CCI_SCLK_EN_POS))
#define CCI_REG_DIV_M_CCI_SCLK      CCI_REG_DIV_M_CCI_SCLK
#define CCI_REG_DIV_M_CCI_SCLK_POS  (5U)
#define CCI_REG_DIV_M_CCI_SCLK_LEN  (2U)
#define CCI_REG_DIV_M_CCI_SCLK_MSK  (((1U << CCI_REG_DIV_M_CCI_SCLK_LEN) - 1) << CCI_REG_DIV_M_CCI_SCLK_POS)
#define CCI_REG_DIV_M_CCI_SCLK_UMSK (~(((1U << CCI_REG_DIV_M_CCI_SCLK_LEN) - 1) << CCI_REG_DIV_M_CCI_SCLK_POS))
#define CCI_CFG_CCI1_PRE_READ       CCI_CFG_CCI1_PRE_READ
#define CCI_CFG_CCI1_PRE_READ_POS   (7U)
#define CCI_CFG_CCI1_PRE_READ_LEN   (1U)
#define CCI_CFG_CCI1_PRE_READ_MSK   (((1U << CCI_CFG_CCI1_PRE_READ_LEN) - 1) << CCI_CFG_CCI1_PRE_READ_POS)
#define CCI_CFG_CCI1_PRE_READ_UMSK  (~(((1U << CCI_CFG_CCI1_PRE_READ_LEN) - 1) << CCI_CFG_CCI1_PRE_READ_POS))
#define CCI_REG_SCCI_CLK_INV        CCI_REG_SCCI_CLK_INV
#define CCI_REG_SCCI_CLK_INV_POS    (8U)
#define CCI_REG_SCCI_CLK_INV_LEN    (1U)
#define CCI_REG_SCCI_CLK_INV_MSK    (((1U << CCI_REG_SCCI_CLK_INV_LEN) - 1) << CCI_REG_SCCI_CLK_INV_POS)
#define CCI_REG_SCCI_CLK_INV_UMSK   (~(((1U << CCI_REG_SCCI_CLK_INV_LEN) - 1) << CCI_REG_SCCI_CLK_INV_POS))
#define CCI_REG_MCCI_CLK_INV        CCI_REG_MCCI_CLK_INV
#define CCI_REG_MCCI_CLK_INV_POS    (9U)
#define CCI_REG_MCCI_CLK_INV_LEN    (1U)
#define CCI_REG_MCCI_CLK_INV_MSK    (((1U << CCI_REG_MCCI_CLK_INV_LEN) - 1) << CCI_REG_MCCI_CLK_INV_POS)
#define CCI_REG_MCCI_CLK_INV_UMSK   (~(((1U << CCI_REG_MCCI_CLK_INV_LEN) - 1) << CCI_REG_MCCI_CLK_INV_POS))
#define CCI_CFG_MCCI_DLY_R          CCI_CFG_MCCI_DLY_R
#define CCI_CFG_MCCI_DLY_R_POS      (16U)
#define CCI_CFG_MCCI_DLY_R_LEN      (1U)
#define CCI_CFG_MCCI_DLY_R_MSK      (((1U << CCI_CFG_MCCI_DLY_R_LEN) - 1) << CCI_CFG_MCCI_DLY_R_POS)
#define CCI_CFG_MCCI_DLY_R_UMSK     (~(((1U << CCI_CFG_MCCI_DLY_R_LEN) - 1) << CCI_CFG_MCCI_DLY_R_POS))

/* 0x4 : cci_addr */
#define CCI_ADDR_OFFSET       (0x4)
#define CCI_APB_CCI_ADDR      CCI_APB_CCI_ADDR
#define CCI_APB_CCI_ADDR_POS  (0U)
#define CCI_APB_CCI_ADDR_LEN  (32U)
#define CCI_APB_CCI_ADDR_MSK  (((1U << CCI_APB_CCI_ADDR_LEN) - 1) << CCI_APB_CCI_ADDR_POS)
#define CCI_APB_CCI_ADDR_UMSK (~(((1U << CCI_APB_CCI_ADDR_LEN) - 1) << CCI_APB_CCI_ADDR_POS))

/* 0x8 : cci_wdata */
#define CCI_WDATA_OFFSET       (0x8)
#define CCI_APB_CCI_WDATA      CCI_APB_CCI_WDATA
#define CCI_APB_CCI_WDATA_POS  (0U)
#define CCI_APB_CCI_WDATA_LEN  (32U)
#define CCI_APB_CCI_WDATA_MSK  (((1U << CCI_APB_CCI_WDATA_LEN) - 1) << CCI_APB_CCI_WDATA_POS)
#define CCI_APB_CCI_WDATA_UMSK (~(((1U << CCI_APB_CCI_WDATA_LEN) - 1) << CCI_APB_CCI_WDATA_POS))

/* 0xC : cci_rdata */
#define CCI_RDATA_OFFSET       (0xC)
#define CCI_APB_CCI_RDATA      CCI_APB_CCI_RDATA
#define CCI_APB_CCI_RDATA_POS  (0U)
#define CCI_APB_CCI_RDATA_LEN  (32U)
#define CCI_APB_CCI_RDATA_MSK  (((1U << CCI_APB_CCI_RDATA_LEN) - 1) << CCI_APB_CCI_RDATA_POS)
#define CCI_APB_CCI_RDATA_UMSK (~(((1U << CCI_APB_CCI_RDATA_LEN) - 1) << CCI_APB_CCI_RDATA_POS))

/* 0x10 : cci_ctl */
#define CCI_CTL_OFFSET      (0x10)
#define CCI_WRITE_FLAG      CCI_WRITE_FLAG
#define CCI_WRITE_FLAG_POS  (0U)
#define CCI_WRITE_FLAG_LEN  (1U)
#define CCI_WRITE_FLAG_MSK  (((1U << CCI_WRITE_FLAG_LEN) - 1) << CCI_WRITE_FLAG_POS)
#define CCI_WRITE_FLAG_UMSK (~(((1U << CCI_WRITE_FLAG_LEN) - 1) << CCI_WRITE_FLAG_POS))
#define CCI_READ_FLAG       CCI_READ_FLAG
#define CCI_READ_FLAG_POS   (1U)
#define CCI_READ_FLAG_LEN   (1U)
#define CCI_READ_FLAG_MSK   (((1U << CCI_READ_FLAG_LEN) - 1) << CCI_READ_FLAG_POS)
#define CCI_READ_FLAG_UMSK  (~(((1U << CCI_READ_FLAG_LEN) - 1) << CCI_READ_FLAG_POS))
#define CCI_AHB_STATE       CCI_AHB_STATE
#define CCI_AHB_STATE_POS   (2U)
#define CCI_AHB_STATE_LEN   (2U)
#define CCI_AHB_STATE_MSK   (((1U << CCI_AHB_STATE_LEN) - 1) << CCI_AHB_STATE_POS)
#define CCI_AHB_STATE_UMSK  (~(((1U << CCI_AHB_STATE_LEN) - 1) << CCI_AHB_STATE_POS))

/* 0x750 : audio_pll_cfg0 */
#define CCI_AUDIO_PLL_CFG0_OFFSET   (0x750)
#define CCI_AUPLL_SDM_RSTB          CCI_AUPLL_SDM_RSTB
#define CCI_AUPLL_SDM_RSTB_POS      (0U)
#define CCI_AUPLL_SDM_RSTB_LEN      (1U)
#define CCI_AUPLL_SDM_RSTB_MSK      (((1U << CCI_AUPLL_SDM_RSTB_LEN) - 1) << CCI_AUPLL_SDM_RSTB_POS)
#define CCI_AUPLL_SDM_RSTB_UMSK     (~(((1U << CCI_AUPLL_SDM_RSTB_LEN) - 1) << CCI_AUPLL_SDM_RSTB_POS))
#define CCI_AUPLL_POSTDIV_RSTB      CCI_AUPLL_POSTDIV_RSTB
#define CCI_AUPLL_POSTDIV_RSTB_POS  (1U)
#define CCI_AUPLL_POSTDIV_RSTB_LEN  (1U)
#define CCI_AUPLL_POSTDIV_RSTB_MSK  (((1U << CCI_AUPLL_POSTDIV_RSTB_LEN) - 1) << CCI_AUPLL_POSTDIV_RSTB_POS)
#define CCI_AUPLL_POSTDIV_RSTB_UMSK (~(((1U << CCI_AUPLL_POSTDIV_RSTB_LEN) - 1) << CCI_AUPLL_POSTDIV_RSTB_POS))
#define CCI_AUPLL_FBDV_RSTB         CCI_AUPLL_FBDV_RSTB
#define CCI_AUPLL_FBDV_RSTB_POS     (2U)
#define CCI_AUPLL_FBDV_RSTB_LEN     (1U)
#define CCI_AUPLL_FBDV_RSTB_MSK     (((1U << CCI_AUPLL_FBDV_RSTB_LEN) - 1) << CCI_AUPLL_FBDV_RSTB_POS)
#define CCI_AUPLL_FBDV_RSTB_UMSK    (~(((1U << CCI_AUPLL_FBDV_RSTB_LEN) - 1) << CCI_AUPLL_FBDV_RSTB_POS))
#define CCI_AUPLL_REFDIV_RSTB       CCI_AUPLL_REFDIV_RSTB
#define CCI_AUPLL_REFDIV_RSTB_POS   (3U)
#define CCI_AUPLL_REFDIV_RSTB_LEN   (1U)
#define CCI_AUPLL_REFDIV_RSTB_MSK   (((1U << CCI_AUPLL_REFDIV_RSTB_LEN) - 1) << CCI_AUPLL_REFDIV_RSTB_POS)
#define CCI_AUPLL_REFDIV_RSTB_UMSK  (~(((1U << CCI_AUPLL_REFDIV_RSTB_LEN) - 1) << CCI_AUPLL_REFDIV_RSTB_POS))
#define CCI_PU_AUPLL_POSTDIV        CCI_PU_AUPLL_POSTDIV
#define CCI_PU_AUPLL_POSTDIV_POS    (4U)
#define CCI_PU_AUPLL_POSTDIV_LEN    (1U)
#define CCI_PU_AUPLL_POSTDIV_MSK    (((1U << CCI_PU_AUPLL_POSTDIV_LEN) - 1) << CCI_PU_AUPLL_POSTDIV_POS)
#define CCI_PU_AUPLL_POSTDIV_UMSK   (~(((1U << CCI_PU_AUPLL_POSTDIV_LEN) - 1) << CCI_PU_AUPLL_POSTDIV_POS))
#define CCI_PU_AUPLL_FBDV           CCI_PU_AUPLL_FBDV
#define CCI_PU_AUPLL_FBDV_POS       (5U)
#define CCI_PU_AUPLL_FBDV_LEN       (1U)
#define CCI_PU_AUPLL_FBDV_MSK       (((1U << CCI_PU_AUPLL_FBDV_LEN) - 1) << CCI_PU_AUPLL_FBDV_POS)
#define CCI_PU_AUPLL_FBDV_UMSK      (~(((1U << CCI_PU_AUPLL_FBDV_LEN) - 1) << CCI_PU_AUPLL_FBDV_POS))
#define CCI_PU_AUPLL_CLAMP_OP       CCI_PU_AUPLL_CLAMP_OP
#define CCI_PU_AUPLL_CLAMP_OP_POS   (6U)
#define CCI_PU_AUPLL_CLAMP_OP_LEN   (1U)
#define CCI_PU_AUPLL_CLAMP_OP_MSK   (((1U << CCI_PU_AUPLL_CLAMP_OP_LEN) - 1) << CCI_PU_AUPLL_CLAMP_OP_POS)
#define CCI_PU_AUPLL_CLAMP_OP_UMSK  (~(((1U << CCI_PU_AUPLL_CLAMP_OP_LEN) - 1) << CCI_PU_AUPLL_CLAMP_OP_POS))
#define CCI_PU_AUPLL_PFD            CCI_PU_AUPLL_PFD
#define CCI_PU_AUPLL_PFD_POS        (7U)
#define CCI_PU_AUPLL_PFD_LEN        (1U)
#define CCI_PU_AUPLL_PFD_MSK        (((1U << CCI_PU_AUPLL_PFD_LEN) - 1) << CCI_PU_AUPLL_PFD_POS)
#define CCI_PU_AUPLL_PFD_UMSK       (~(((1U << CCI_PU_AUPLL_PFD_LEN) - 1) << CCI_PU_AUPLL_PFD_POS))
#define CCI_PU_AUPLL_CP             CCI_PU_AUPLL_CP
#define CCI_PU_AUPLL_CP_POS         (8U)
#define CCI_PU_AUPLL_CP_LEN         (1U)
#define CCI_PU_AUPLL_CP_MSK         (((1U << CCI_PU_AUPLL_CP_LEN) - 1) << CCI_PU_AUPLL_CP_POS)
#define CCI_PU_AUPLL_CP_UMSK        (~(((1U << CCI_PU_AUPLL_CP_LEN) - 1) << CCI_PU_AUPLL_CP_POS))
#define CCI_PU_AUPLL_SFREG          CCI_PU_AUPLL_SFREG
#define CCI_PU_AUPLL_SFREG_POS      (9U)
#define CCI_PU_AUPLL_SFREG_LEN      (1U)
#define CCI_PU_AUPLL_SFREG_MSK      (((1U << CCI_PU_AUPLL_SFREG_LEN) - 1) << CCI_PU_AUPLL_SFREG_POS)
#define CCI_PU_AUPLL_SFREG_UMSK     (~(((1U << CCI_PU_AUPLL_SFREG_LEN) - 1) << CCI_PU_AUPLL_SFREG_POS))
#define CCI_PU_AUPLL                CCI_PU_AUPLL
#define CCI_PU_AUPLL_POS            (10U)
#define CCI_PU_AUPLL_LEN            (1U)
#define CCI_PU_AUPLL_MSK            (((1U << CCI_PU_AUPLL_LEN) - 1) << CCI_PU_AUPLL_POS)
#define CCI_PU_AUPLL_UMSK           (~(((1U << CCI_PU_AUPLL_LEN) - 1) << CCI_PU_AUPLL_POS))
#define CCI_PU_AUPLL_CLKTREE        CCI_PU_AUPLL_CLKTREE
#define CCI_PU_AUPLL_CLKTREE_POS    (11U)
#define CCI_PU_AUPLL_CLKTREE_LEN    (1U)
#define CCI_PU_AUPLL_CLKTREE_MSK    (((1U << CCI_PU_AUPLL_CLKTREE_LEN) - 1) << CCI_PU_AUPLL_CLKTREE_POS)
#define CCI_PU_AUPLL_CLKTREE_UMSK   (~(((1U << CCI_PU_AUPLL_CLKTREE_LEN) - 1) << CCI_PU_AUPLL_CLKTREE_POS))

/* 0x754 : audio_pll_cfg1 */
#define CCI_AUDIO_PLL_CFG1_OFFSET   (0x754)
#define CCI_AUPLL_POSTDIV           CCI_AUPLL_POSTDIV
#define CCI_AUPLL_POSTDIV_POS       (0U)
#define CCI_AUPLL_POSTDIV_LEN       (7U)
#define CCI_AUPLL_POSTDIV_MSK       (((1U << CCI_AUPLL_POSTDIV_LEN) - 1) << CCI_AUPLL_POSTDIV_POS)
#define CCI_AUPLL_POSTDIV_UMSK      (~(((1U << CCI_AUPLL_POSTDIV_LEN) - 1) << CCI_AUPLL_POSTDIV_POS))
#define CCI_AUPLL_REFDIV_RATIO      CCI_AUPLL_REFDIV_RATIO
#define CCI_AUPLL_REFDIV_RATIO_POS  (8U)
#define CCI_AUPLL_REFDIV_RATIO_LEN  (4U)
#define CCI_AUPLL_REFDIV_RATIO_MSK  (((1U << CCI_AUPLL_REFDIV_RATIO_LEN) - 1) << CCI_AUPLL_REFDIV_RATIO_POS)
#define CCI_AUPLL_REFDIV_RATIO_UMSK (~(((1U << CCI_AUPLL_REFDIV_RATIO_LEN) - 1) << CCI_AUPLL_REFDIV_RATIO_POS))
#define CCI_AUPLL_REFCLK_SEL        CCI_AUPLL_REFCLK_SEL
#define CCI_AUPLL_REFCLK_SEL_POS    (16U)
#define CCI_AUPLL_REFCLK_SEL_LEN    (2U)
#define CCI_AUPLL_REFCLK_SEL_MSK    (((1U << CCI_AUPLL_REFCLK_SEL_LEN) - 1) << CCI_AUPLL_REFCLK_SEL_POS)
#define CCI_AUPLL_REFCLK_SEL_UMSK   (~(((1U << CCI_AUPLL_REFCLK_SEL_LEN) - 1) << CCI_AUPLL_REFCLK_SEL_POS))
#define CCI_AUPLL_VG11_SEL          CCI_AUPLL_VG11_SEL
#define CCI_AUPLL_VG11_SEL_POS      (20U)
#define CCI_AUPLL_VG11_SEL_LEN      (2U)
#define CCI_AUPLL_VG11_SEL_MSK      (((1U << CCI_AUPLL_VG11_SEL_LEN) - 1) << CCI_AUPLL_VG11_SEL_POS)
#define CCI_AUPLL_VG11_SEL_UMSK     (~(((1U << CCI_AUPLL_VG11_SEL_LEN) - 1) << CCI_AUPLL_VG11_SEL_POS))
#define CCI_AUPLL_VG13_SEL          CCI_AUPLL_VG13_SEL
#define CCI_AUPLL_VG13_SEL_POS      (24U)
#define CCI_AUPLL_VG13_SEL_LEN      (2U)
#define CCI_AUPLL_VG13_SEL_MSK      (((1U << CCI_AUPLL_VG13_SEL_LEN) - 1) << CCI_AUPLL_VG13_SEL_POS)
#define CCI_AUPLL_VG13_SEL_UMSK     (~(((1U << CCI_AUPLL_VG13_SEL_LEN) - 1) << CCI_AUPLL_VG13_SEL_POS))

/* 0x758 : audio_pll_cfg2 */
#define CCI_AUDIO_PLL_CFG2_OFFSET    (0x758)
#define CCI_AUPLL_SEL_CP_BIAS        CCI_AUPLL_SEL_CP_BIAS
#define CCI_AUPLL_SEL_CP_BIAS_POS    (0U)
#define CCI_AUPLL_SEL_CP_BIAS_LEN    (1U)
#define CCI_AUPLL_SEL_CP_BIAS_MSK    (((1U << CCI_AUPLL_SEL_CP_BIAS_LEN) - 1) << CCI_AUPLL_SEL_CP_BIAS_POS)
#define CCI_AUPLL_SEL_CP_BIAS_UMSK   (~(((1U << CCI_AUPLL_SEL_CP_BIAS_LEN) - 1) << CCI_AUPLL_SEL_CP_BIAS_POS))
#define CCI_AUPLL_ICP_5U             CCI_AUPLL_ICP_5U
#define CCI_AUPLL_ICP_5U_POS         (4U)
#define CCI_AUPLL_ICP_5U_LEN         (2U)
#define CCI_AUPLL_ICP_5U_MSK         (((1U << CCI_AUPLL_ICP_5U_LEN) - 1) << CCI_AUPLL_ICP_5U_POS)
#define CCI_AUPLL_ICP_5U_UMSK        (~(((1U << CCI_AUPLL_ICP_5U_LEN) - 1) << CCI_AUPLL_ICP_5U_POS))
#define CCI_AUPLL_ICP_1U             CCI_AUPLL_ICP_1U
#define CCI_AUPLL_ICP_1U_POS         (6U)
#define CCI_AUPLL_ICP_1U_LEN         (2U)
#define CCI_AUPLL_ICP_1U_MSK         (((1U << CCI_AUPLL_ICP_1U_LEN) - 1) << CCI_AUPLL_ICP_1U_POS)
#define CCI_AUPLL_ICP_1U_UMSK        (~(((1U << CCI_AUPLL_ICP_1U_LEN) - 1) << CCI_AUPLL_ICP_1U_POS))
#define CCI_AUPLL_INT_FRAC_SW        CCI_AUPLL_INT_FRAC_SW
#define CCI_AUPLL_INT_FRAC_SW_POS    (8U)
#define CCI_AUPLL_INT_FRAC_SW_LEN    (1U)
#define CCI_AUPLL_INT_FRAC_SW_MSK    (((1U << CCI_AUPLL_INT_FRAC_SW_LEN) - 1) << CCI_AUPLL_INT_FRAC_SW_POS)
#define CCI_AUPLL_INT_FRAC_SW_UMSK   (~(((1U << CCI_AUPLL_INT_FRAC_SW_LEN) - 1) << CCI_AUPLL_INT_FRAC_SW_POS))
#define CCI_AUPLL_CP_STARTUP_EN      CCI_AUPLL_CP_STARTUP_EN
#define CCI_AUPLL_CP_STARTUP_EN_POS  (9U)
#define CCI_AUPLL_CP_STARTUP_EN_LEN  (1U)
#define CCI_AUPLL_CP_STARTUP_EN_MSK  (((1U << CCI_AUPLL_CP_STARTUP_EN_LEN) - 1) << CCI_AUPLL_CP_STARTUP_EN_POS)
#define CCI_AUPLL_CP_STARTUP_EN_UMSK (~(((1U << CCI_AUPLL_CP_STARTUP_EN_LEN) - 1) << CCI_AUPLL_CP_STARTUP_EN_POS))
#define CCI_AUPLL_CP_OPAMP_EN        CCI_AUPLL_CP_OPAMP_EN
#define CCI_AUPLL_CP_OPAMP_EN_POS    (10U)
#define CCI_AUPLL_CP_OPAMP_EN_LEN    (1U)
#define CCI_AUPLL_CP_OPAMP_EN_MSK    (((1U << CCI_AUPLL_CP_OPAMP_EN_LEN) - 1) << CCI_AUPLL_CP_OPAMP_EN_POS)
#define CCI_AUPLL_CP_OPAMP_EN_UMSK   (~(((1U << CCI_AUPLL_CP_OPAMP_EN_LEN) - 1) << CCI_AUPLL_CP_OPAMP_EN_POS))

/* 0x75C : audio_pll_cfg3 */
#define CCI_AUDIO_PLL_CFG3_OFFSET (0x75C)
#define CCI_AUPLL_C4_EN           CCI_AUPLL_C4_EN
#define CCI_AUPLL_C4_EN_POS       (0U)
#define CCI_AUPLL_C4_EN_LEN       (1U)
#define CCI_AUPLL_C4_EN_MSK       (((1U << CCI_AUPLL_C4_EN_LEN) - 1) << CCI_AUPLL_C4_EN_POS)
#define CCI_AUPLL_C4_EN_UMSK      (~(((1U << CCI_AUPLL_C4_EN_LEN) - 1) << CCI_AUPLL_C4_EN_POS))
#define CCI_AUPLL_R4              CCI_AUPLL_R4
#define CCI_AUPLL_R4_POS          (4U)
#define CCI_AUPLL_R4_LEN          (2U)
#define CCI_AUPLL_R4_MSK          (((1U << CCI_AUPLL_R4_LEN) - 1) << CCI_AUPLL_R4_POS)
#define CCI_AUPLL_R4_UMSK         (~(((1U << CCI_AUPLL_R4_LEN) - 1) << CCI_AUPLL_R4_POS))
#define CCI_AUPLL_R4_SHORT        CCI_AUPLL_R4_SHORT
#define CCI_AUPLL_R4_SHORT_POS    (8U)
#define CCI_AUPLL_R4_SHORT_LEN    (1U)
#define CCI_AUPLL_R4_SHORT_MSK    (((1U << CCI_AUPLL_R4_SHORT_LEN) - 1) << CCI_AUPLL_R4_SHORT_POS)
#define CCI_AUPLL_R4_SHORT_UMSK   (~(((1U << CCI_AUPLL_R4_SHORT_LEN) - 1) << CCI_AUPLL_R4_SHORT_POS))
#define CCI_AUPLL_C3              CCI_AUPLL_C3
#define CCI_AUPLL_C3_POS          (12U)
#define CCI_AUPLL_C3_LEN          (2U)
#define CCI_AUPLL_C3_MSK          (((1U << CCI_AUPLL_C3_LEN) - 1) << CCI_AUPLL_C3_POS)
#define CCI_AUPLL_C3_UMSK         (~(((1U << CCI_AUPLL_C3_LEN) - 1) << CCI_AUPLL_C3_POS))
#define CCI_AUPLL_CZ              CCI_AUPLL_CZ
#define CCI_AUPLL_CZ_POS          (14U)
#define CCI_AUPLL_CZ_LEN          (2U)
#define CCI_AUPLL_CZ_MSK          (((1U << CCI_AUPLL_CZ_LEN) - 1) << CCI_AUPLL_CZ_POS)
#define CCI_AUPLL_CZ_UMSK         (~(((1U << CCI_AUPLL_CZ_LEN) - 1) << CCI_AUPLL_CZ_POS))
#define CCI_AUPLL_RZ              CCI_AUPLL_RZ
#define CCI_AUPLL_RZ_POS          (16U)
#define CCI_AUPLL_RZ_LEN          (3U)
#define CCI_AUPLL_RZ_MSK          (((1U << CCI_AUPLL_RZ_LEN) - 1) << CCI_AUPLL_RZ_POS)
#define CCI_AUPLL_RZ_UMSK         (~(((1U << CCI_AUPLL_RZ_LEN) - 1) << CCI_AUPLL_RZ_POS))

/* 0x760 : audio_pll_cfg4 */
#define CCI_AUDIO_PLL_CFG4_OFFSET     (0x760)
#define CCI_AUPLL_SEL_SAMPLE_CLK      CCI_AUPLL_SEL_SAMPLE_CLK
#define CCI_AUPLL_SEL_SAMPLE_CLK_POS  (0U)
#define CCI_AUPLL_SEL_SAMPLE_CLK_LEN  (2U)
#define CCI_AUPLL_SEL_SAMPLE_CLK_MSK  (((1U << CCI_AUPLL_SEL_SAMPLE_CLK_LEN) - 1) << CCI_AUPLL_SEL_SAMPLE_CLK_POS)
#define CCI_AUPLL_SEL_SAMPLE_CLK_UMSK (~(((1U << CCI_AUPLL_SEL_SAMPLE_CLK_LEN) - 1) << CCI_AUPLL_SEL_SAMPLE_CLK_POS))
#define CCI_AUPLL_SEL_FB_CLK          CCI_AUPLL_SEL_FB_CLK
#define CCI_AUPLL_SEL_FB_CLK_POS      (4U)
#define CCI_AUPLL_SEL_FB_CLK_LEN      (2U)
#define CCI_AUPLL_SEL_FB_CLK_MSK      (((1U << CCI_AUPLL_SEL_FB_CLK_LEN) - 1) << CCI_AUPLL_SEL_FB_CLK_POS)
#define CCI_AUPLL_SEL_FB_CLK_UMSK     (~(((1U << CCI_AUPLL_SEL_FB_CLK_LEN) - 1) << CCI_AUPLL_SEL_FB_CLK_POS))
#define CCI_AUPLL_SDMCLK_SEL          CCI_AUPLL_SDMCLK_SEL
#define CCI_AUPLL_SDMCLK_SEL_POS      (8U)
#define CCI_AUPLL_SDMCLK_SEL_LEN      (1U)
#define CCI_AUPLL_SDMCLK_SEL_MSK      (((1U << CCI_AUPLL_SDMCLK_SEL_LEN) - 1) << CCI_AUPLL_SDMCLK_SEL_POS)
#define CCI_AUPLL_SDMCLK_SEL_UMSK     (~(((1U << CCI_AUPLL_SDMCLK_SEL_LEN) - 1) << CCI_AUPLL_SDMCLK_SEL_POS))

/* 0x764 : audio_pll_cfg5 */
#define CCI_AUDIO_PLL_CFG5_OFFSET (0x764)
#define CCI_AUPLL_VCO_SPEED       CCI_AUPLL_VCO_SPEED
#define CCI_AUPLL_VCO_SPEED_POS   (0U)
#define CCI_AUPLL_VCO_SPEED_LEN   (3U)
#define CCI_AUPLL_VCO_SPEED_MSK   (((1U << CCI_AUPLL_VCO_SPEED_LEN) - 1) << CCI_AUPLL_VCO_SPEED_POS)
#define CCI_AUPLL_VCO_SPEED_UMSK  (~(((1U << CCI_AUPLL_VCO_SPEED_LEN) - 1) << CCI_AUPLL_VCO_SPEED_POS))

/* 0x768 : audio_pll_cfg6 */
#define CCI_AUDIO_PLL_CFG6_OFFSET (0x768)
#define CCI_AUPLL_SDMIN           CCI_AUPLL_SDMIN
#define CCI_AUPLL_SDMIN_POS       (0U)
#define CCI_AUPLL_SDMIN_LEN       (19U)
#define CCI_AUPLL_SDMIN_MSK       (((1U << CCI_AUPLL_SDMIN_LEN) - 1) << CCI_AUPLL_SDMIN_POS)
#define CCI_AUPLL_SDMIN_UMSK      (~(((1U << CCI_AUPLL_SDMIN_LEN) - 1) << CCI_AUPLL_SDMIN_POS))
#define CCI_AUPLL_SDM_BYPASS      CCI_AUPLL_SDM_BYPASS
#define CCI_AUPLL_SDM_BYPASS_POS  (24U)
#define CCI_AUPLL_SDM_BYPASS_LEN  (1U)
#define CCI_AUPLL_SDM_BYPASS_MSK  (((1U << CCI_AUPLL_SDM_BYPASS_LEN) - 1) << CCI_AUPLL_SDM_BYPASS_POS)
#define CCI_AUPLL_SDM_BYPASS_UMSK (~(((1U << CCI_AUPLL_SDM_BYPASS_LEN) - 1) << CCI_AUPLL_SDM_BYPASS_POS))

/* 0x76C : audio_pll_cfg7 */
#define CCI_AUDIO_PLL_CFG7_OFFSET       (0x76C)
#define CCI_AUPLL_SDM_ORDER_SEL         CCI_AUPLL_SDM_ORDER_SEL
#define CCI_AUPLL_SDM_ORDER_SEL_POS     (0U)
#define CCI_AUPLL_SDM_ORDER_SEL_LEN     (1U)
#define CCI_AUPLL_SDM_ORDER_SEL_MSK     (((1U << CCI_AUPLL_SDM_ORDER_SEL_LEN) - 1) << CCI_AUPLL_SDM_ORDER_SEL_POS)
#define CCI_AUPLL_SDM_ORDER_SEL_UMSK    (~(((1U << CCI_AUPLL_SDM_ORDER_SEL_LEN) - 1) << CCI_AUPLL_SDM_ORDER_SEL_POS))
#define CCI_AUPLL_SDM_SIG_DITH_SEL      CCI_AUPLL_SDM_SIG_DITH_SEL
#define CCI_AUPLL_SDM_SIG_DITH_SEL_POS  (16U)
#define CCI_AUPLL_SDM_SIG_DITH_SEL_LEN  (2U)
#define CCI_AUPLL_SDM_SIG_DITH_SEL_MSK  (((1U << CCI_AUPLL_SDM_SIG_DITH_SEL_LEN) - 1) << CCI_AUPLL_SDM_SIG_DITH_SEL_POS)
#define CCI_AUPLL_SDM_SIG_DITH_SEL_UMSK (~(((1U << CCI_AUPLL_SDM_SIG_DITH_SEL_LEN) - 1) << CCI_AUPLL_SDM_SIG_DITH_SEL_POS))

/* 0x770 : audio_pll_cfg8 */
#define CCI_AUDIO_PLL_CFG8_OFFSET    (0x770)
#define CCI_AUPLL_EN_DIV1            CCI_AUPLL_EN_DIV1
#define CCI_AUPLL_EN_DIV1_POS        (0U)
#define CCI_AUPLL_EN_DIV1_LEN        (1U)
#define CCI_AUPLL_EN_DIV1_MSK        (((1U << CCI_AUPLL_EN_DIV1_LEN) - 1) << CCI_AUPLL_EN_DIV1_POS)
#define CCI_AUPLL_EN_DIV1_UMSK       (~(((1U << CCI_AUPLL_EN_DIV1_LEN) - 1) << CCI_AUPLL_EN_DIV1_POS))
#define CCI_AUPLL_EN_DIV2            CCI_AUPLL_EN_DIV2
#define CCI_AUPLL_EN_DIV2_POS        (1U)
#define CCI_AUPLL_EN_DIV2_LEN        (1U)
#define CCI_AUPLL_EN_DIV2_MSK        (((1U << CCI_AUPLL_EN_DIV2_LEN) - 1) << CCI_AUPLL_EN_DIV2_POS)
#define CCI_AUPLL_EN_DIV2_UMSK       (~(((1U << CCI_AUPLL_EN_DIV2_LEN) - 1) << CCI_AUPLL_EN_DIV2_POS))
#define CCI_AUPLL_EN_DIV2P5          CCI_AUPLL_EN_DIV2P5
#define CCI_AUPLL_EN_DIV2P5_POS      (2U)
#define CCI_AUPLL_EN_DIV2P5_LEN      (1U)
#define CCI_AUPLL_EN_DIV2P5_MSK      (((1U << CCI_AUPLL_EN_DIV2P5_LEN) - 1) << CCI_AUPLL_EN_DIV2P5_POS)
#define CCI_AUPLL_EN_DIV2P5_UMSK     (~(((1U << CCI_AUPLL_EN_DIV2P5_LEN) - 1) << CCI_AUPLL_EN_DIV2P5_POS))
#define CCI_AUPLL_EN_DIV3            CCI_AUPLL_EN_DIV3
#define CCI_AUPLL_EN_DIV3_POS        (3U)
#define CCI_AUPLL_EN_DIV3_LEN        (1U)
#define CCI_AUPLL_EN_DIV3_MSK        (((1U << CCI_AUPLL_EN_DIV3_LEN) - 1) << CCI_AUPLL_EN_DIV3_POS)
#define CCI_AUPLL_EN_DIV3_UMSK       (~(((1U << CCI_AUPLL_EN_DIV3_LEN) - 1) << CCI_AUPLL_EN_DIV3_POS))
#define CCI_AUPLL_EN_DIV4            CCI_AUPLL_EN_DIV4
#define CCI_AUPLL_EN_DIV4_POS        (4U)
#define CCI_AUPLL_EN_DIV4_LEN        (1U)
#define CCI_AUPLL_EN_DIV4_MSK        (((1U << CCI_AUPLL_EN_DIV4_LEN) - 1) << CCI_AUPLL_EN_DIV4_POS)
#define CCI_AUPLL_EN_DIV4_UMSK       (~(((1U << CCI_AUPLL_EN_DIV4_LEN) - 1) << CCI_AUPLL_EN_DIV4_POS))
#define CCI_AUPLL_EN_DIV5            CCI_AUPLL_EN_DIV5
#define CCI_AUPLL_EN_DIV5_POS        (5U)
#define CCI_AUPLL_EN_DIV5_LEN        (1U)
#define CCI_AUPLL_EN_DIV5_MSK        (((1U << CCI_AUPLL_EN_DIV5_LEN) - 1) << CCI_AUPLL_EN_DIV5_POS)
#define CCI_AUPLL_EN_DIV5_UMSK       (~(((1U << CCI_AUPLL_EN_DIV5_LEN) - 1) << CCI_AUPLL_EN_DIV5_POS))
#define CCI_AUPLL_EN_DIV6            CCI_AUPLL_EN_DIV6
#define CCI_AUPLL_EN_DIV6_POS        (6U)
#define CCI_AUPLL_EN_DIV6_LEN        (1U)
#define CCI_AUPLL_EN_DIV6_MSK        (((1U << CCI_AUPLL_EN_DIV6_LEN) - 1) << CCI_AUPLL_EN_DIV6_POS)
#define CCI_AUPLL_EN_DIV6_UMSK       (~(((1U << CCI_AUPLL_EN_DIV6_LEN) - 1) << CCI_AUPLL_EN_DIV6_POS))
#define CCI_AUPLL_EN_DIV10           CCI_AUPLL_EN_DIV10
#define CCI_AUPLL_EN_DIV10_POS       (7U)
#define CCI_AUPLL_EN_DIV10_LEN       (1U)
#define CCI_AUPLL_EN_DIV10_MSK       (((1U << CCI_AUPLL_EN_DIV10_LEN) - 1) << CCI_AUPLL_EN_DIV10_POS)
#define CCI_AUPLL_EN_DIV10_UMSK      (~(((1U << CCI_AUPLL_EN_DIV10_LEN) - 1) << CCI_AUPLL_EN_DIV10_POS))
#define CCI_AUPLL_EN_DIV15           CCI_AUPLL_EN_DIV15
#define CCI_AUPLL_EN_DIV15_POS       (8U)
#define CCI_AUPLL_EN_DIV15_LEN       (1U)
#define CCI_AUPLL_EN_DIV15_MSK       (((1U << CCI_AUPLL_EN_DIV15_LEN) - 1) << CCI_AUPLL_EN_DIV15_POS)
#define CCI_AUPLL_EN_DIV15_UMSK      (~(((1U << CCI_AUPLL_EN_DIV15_LEN) - 1) << CCI_AUPLL_EN_DIV15_POS))
#define CCI_AUPLL_SEL_DIV1_DIV2      CCI_AUPLL_SEL_DIV1_DIV2
#define CCI_AUPLL_SEL_DIV1_DIV2_POS  (9U)
#define CCI_AUPLL_SEL_DIV1_DIV2_LEN  (1U)
#define CCI_AUPLL_SEL_DIV1_DIV2_MSK  (((1U << CCI_AUPLL_SEL_DIV1_DIV2_LEN) - 1) << CCI_AUPLL_SEL_DIV1_DIV2_POS)
#define CCI_AUPLL_SEL_DIV1_DIV2_UMSK (~(((1U << CCI_AUPLL_SEL_DIV1_DIV2_LEN) - 1) << CCI_AUPLL_SEL_DIV1_DIV2_POS))

/* 0x774 : audio_pll_cfg9 */
#define CCI_AUDIO_PLL_CFG9_OFFSET       (0x774)
#define CCI_AUPLL_DC_TP_OUT_EN          CCI_AUPLL_DC_TP_OUT_EN
#define CCI_AUPLL_DC_TP_OUT_EN_POS      (0U)
#define CCI_AUPLL_DC_TP_OUT_EN_LEN      (1U)
#define CCI_AUPLL_DC_TP_OUT_EN_MSK      (((1U << CCI_AUPLL_DC_TP_OUT_EN_LEN) - 1) << CCI_AUPLL_DC_TP_OUT_EN_POS)
#define CCI_AUPLL_DC_TP_OUT_EN_UMSK     (~(((1U << CCI_AUPLL_DC_TP_OUT_EN_LEN) - 1) << CCI_AUPLL_DC_TP_OUT_EN_POS))
#define CCI_TEN_AUPLL                   CCI_TEN_AUPLL
#define CCI_TEN_AUPLL_POS               (1U)
#define CCI_TEN_AUPLL_LEN               (1U)
#define CCI_TEN_AUPLL_MSK               (((1U << CCI_TEN_AUPLL_LEN) - 1) << CCI_TEN_AUPLL_POS)
#define CCI_TEN_AUPLL_UMSK              (~(((1U << CCI_TEN_AUPLL_LEN) - 1) << CCI_TEN_AUPLL_POS))
#define CCI_TEN_AUPLL_SFREG             CCI_TEN_AUPLL_SFREG
#define CCI_TEN_AUPLL_SFREG_POS         (2U)
#define CCI_TEN_AUPLL_SFREG_LEN         (1U)
#define CCI_TEN_AUPLL_SFREG_MSK         (((1U << CCI_TEN_AUPLL_SFREG_LEN) - 1) << CCI_TEN_AUPLL_SFREG_POS)
#define CCI_TEN_AUPLL_SFREG_UMSK        (~(((1U << CCI_TEN_AUPLL_SFREG_LEN) - 1) << CCI_TEN_AUPLL_SFREG_POS))
#define CCI_DTEN_AUPLL_FIN              CCI_DTEN_AUPLL_FIN
#define CCI_DTEN_AUPLL_FIN_POS          (4U)
#define CCI_DTEN_AUPLL_FIN_LEN          (1U)
#define CCI_DTEN_AUPLL_FIN_MSK          (((1U << CCI_DTEN_AUPLL_FIN_LEN) - 1) << CCI_DTEN_AUPLL_FIN_POS)
#define CCI_DTEN_AUPLL_FIN_UMSK         (~(((1U << CCI_DTEN_AUPLL_FIN_LEN) - 1) << CCI_DTEN_AUPLL_FIN_POS))
#define CCI_DTEN_AUPLL_FREF             CCI_DTEN_AUPLL_FREF
#define CCI_DTEN_AUPLL_FREF_POS         (5U)
#define CCI_DTEN_AUPLL_FREF_LEN         (1U)
#define CCI_DTEN_AUPLL_FREF_MSK         (((1U << CCI_DTEN_AUPLL_FREF_LEN) - 1) << CCI_DTEN_AUPLL_FREF_POS)
#define CCI_DTEN_AUPLL_FREF_UMSK        (~(((1U << CCI_DTEN_AUPLL_FREF_LEN) - 1) << CCI_DTEN_AUPLL_FREF_POS))
#define CCI_DTEN_AUPLL_FSDM             CCI_DTEN_AUPLL_FSDM
#define CCI_DTEN_AUPLL_FSDM_POS         (6U)
#define CCI_DTEN_AUPLL_FSDM_LEN         (1U)
#define CCI_DTEN_AUPLL_FSDM_MSK         (((1U << CCI_DTEN_AUPLL_FSDM_LEN) - 1) << CCI_DTEN_AUPLL_FSDM_POS)
#define CCI_DTEN_AUPLL_FSDM_UMSK        (~(((1U << CCI_DTEN_AUPLL_FSDM_LEN) - 1) << CCI_DTEN_AUPLL_FSDM_POS))
#define CCI_DTEN_AUPLL_DIV15            CCI_DTEN_AUPLL_DIV15
#define CCI_DTEN_AUPLL_DIV15_POS        (7U)
#define CCI_DTEN_AUPLL_DIV15_LEN        (1U)
#define CCI_DTEN_AUPLL_DIV15_MSK        (((1U << CCI_DTEN_AUPLL_DIV15_LEN) - 1) << CCI_DTEN_AUPLL_DIV15_POS)
#define CCI_DTEN_AUPLL_DIV15_UMSK       (~(((1U << CCI_DTEN_AUPLL_DIV15_LEN) - 1) << CCI_DTEN_AUPLL_DIV15_POS))
#define CCI_DTEN_AUPLL_DIV5             CCI_DTEN_AUPLL_DIV5
#define CCI_DTEN_AUPLL_DIV5_POS         (8U)
#define CCI_DTEN_AUPLL_DIV5_LEN         (1U)
#define CCI_DTEN_AUPLL_DIV5_MSK         (((1U << CCI_DTEN_AUPLL_DIV5_LEN) - 1) << CCI_DTEN_AUPLL_DIV5_POS)
#define CCI_DTEN_AUPLL_DIV5_UMSK        (~(((1U << CCI_DTEN_AUPLL_DIV5_LEN) - 1) << CCI_DTEN_AUPLL_DIV5_POS))
#define CCI_DTEN_AUPLL_POSTDIV_CLK      CCI_DTEN_AUPLL_POSTDIV_CLK
#define CCI_DTEN_AUPLL_POSTDIV_CLK_POS  (9U)
#define CCI_DTEN_AUPLL_POSTDIV_CLK_LEN  (1U)
#define CCI_DTEN_AUPLL_POSTDIV_CLK_MSK  (((1U << CCI_DTEN_AUPLL_POSTDIV_CLK_LEN) - 1) << CCI_DTEN_AUPLL_POSTDIV_CLK_POS)
#define CCI_DTEN_AUPLL_POSTDIV_CLK_UMSK (~(((1U << CCI_DTEN_AUPLL_POSTDIV_CLK_LEN) - 1) << CCI_DTEN_AUPLL_POSTDIV_CLK_POS))
#define CCI_DTEST_AUPLL_PULLDOWN        CCI_DTEST_AUPLL_PULLDOWN
#define CCI_DTEST_AUPLL_PULLDOWN_POS    (10U)
#define CCI_DTEST_AUPLL_PULLDOWN_LEN    (1U)
#define CCI_DTEST_AUPLL_PULLDOWN_MSK    (((1U << CCI_DTEST_AUPLL_PULLDOWN_LEN) - 1) << CCI_DTEST_AUPLL_PULLDOWN_POS)
#define CCI_DTEST_AUPLL_PULLDOWN_UMSK   (~(((1U << CCI_DTEST_AUPLL_PULLDOWN_LEN) - 1) << CCI_DTEST_AUPLL_PULLDOWN_POS))

/* 0x778 : audio_pll_cfg10 */
#define CCI_AUDIO_PLL_CFG10_OFFSET       (0x778)
#define CCI_AUPLL_SSC_EN                 CCI_AUPLL_SSC_EN
#define CCI_AUPLL_SSC_EN_POS             (0U)
#define CCI_AUPLL_SSC_EN_LEN             (1U)
#define CCI_AUPLL_SSC_EN_MSK             (((1U << CCI_AUPLL_SSC_EN_LEN) - 1) << CCI_AUPLL_SSC_EN_POS)
#define CCI_AUPLL_SSC_EN_UMSK            (~(((1U << CCI_AUPLL_SSC_EN_LEN) - 1) << CCI_AUPLL_SSC_EN_POS))
#define CCI_AUPLL_SSC_CNT                CCI_AUPLL_SSC_CNT
#define CCI_AUPLL_SSC_CNT_POS            (4U)
#define CCI_AUPLL_SSC_CNT_LEN            (8U)
#define CCI_AUPLL_SSC_CNT_MSK            (((1U << CCI_AUPLL_SSC_CNT_LEN) - 1) << CCI_AUPLL_SSC_CNT_POS)
#define CCI_AUPLL_SSC_CNT_UMSK           (~(((1U << CCI_AUPLL_SSC_CNT_LEN) - 1) << CCI_AUPLL_SSC_CNT_POS))
#define CCI_AUPLL_SSC_GAIN               CCI_AUPLL_SSC_GAIN
#define CCI_AUPLL_SSC_GAIN_POS           (12U)
#define CCI_AUPLL_SSC_GAIN_LEN           (3U)
#define CCI_AUPLL_SSC_GAIN_MSK           (((1U << CCI_AUPLL_SSC_GAIN_LEN) - 1) << CCI_AUPLL_SSC_GAIN_POS)
#define CCI_AUPLL_SSC_GAIN_UMSK          (~(((1U << CCI_AUPLL_SSC_GAIN_LEN) - 1) << CCI_AUPLL_SSC_GAIN_POS))
#define CCI_AUPLL_SSC_START_GATE_EN      CCI_AUPLL_SSC_START_GATE_EN
#define CCI_AUPLL_SSC_START_GATE_EN_POS  (16U)
#define CCI_AUPLL_SSC_START_GATE_EN_LEN  (1U)
#define CCI_AUPLL_SSC_START_GATE_EN_MSK  (((1U << CCI_AUPLL_SSC_START_GATE_EN_LEN) - 1) << CCI_AUPLL_SSC_START_GATE_EN_POS)
#define CCI_AUPLL_SSC_START_GATE_EN_UMSK (~(((1U << CCI_AUPLL_SSC_START_GATE_EN_LEN) - 1) << CCI_AUPLL_SSC_START_GATE_EN_POS))
#define CCI_AUPLL_SSC_START              CCI_AUPLL_SSC_START
#define CCI_AUPLL_SSC_START_POS          (20U)
#define CCI_AUPLL_SSC_START_LEN          (1U)
#define CCI_AUPLL_SSC_START_MSK          (((1U << CCI_AUPLL_SSC_START_LEN) - 1) << CCI_AUPLL_SSC_START_POS)
#define CCI_AUPLL_SSC_START_UMSK         (~(((1U << CCI_AUPLL_SSC_START_LEN) - 1) << CCI_AUPLL_SSC_START_POS))

/* 0x77C : audio_pll_cfg11 */
#define CCI_AUDIO_PLL_CFG11_OFFSET (0x77C)
#define CCI_AUPLL_RESV             CCI_AUPLL_RESV
#define CCI_AUPLL_RESV_POS         (0U)
#define CCI_AUPLL_RESV_LEN         (16U)
#define CCI_AUPLL_RESV_MSK         (((1U << CCI_AUPLL_RESV_LEN) - 1) << CCI_AUPLL_RESV_POS)
#define CCI_AUPLL_RESV_UMSK        (~(((1U << CCI_AUPLL_RESV_LEN) - 1) << CCI_AUPLL_RESV_POS))
#define CCI_AUPLL_DL_CTRL_15       CCI_AUPLL_DL_CTRL_15
#define CCI_AUPLL_DL_CTRL_15_POS   (23U)
#define CCI_AUPLL_DL_CTRL_15_LEN   (1U)
#define CCI_AUPLL_DL_CTRL_15_MSK   (((1U << CCI_AUPLL_DL_CTRL_15_LEN) - 1) << CCI_AUPLL_DL_CTRL_15_POS)
#define CCI_AUPLL_DL_CTRL_15_UMSK  (~(((1U << CCI_AUPLL_DL_CTRL_15_LEN) - 1) << CCI_AUPLL_DL_CTRL_15_POS))
#define CCI_AUPLL_DL_CTRL_10       CCI_AUPLL_DL_CTRL_10
#define CCI_AUPLL_DL_CTRL_10_POS   (24U)
#define CCI_AUPLL_DL_CTRL_10_LEN   (1U)
#define CCI_AUPLL_DL_CTRL_10_MSK   (((1U << CCI_AUPLL_DL_CTRL_10_LEN) - 1) << CCI_AUPLL_DL_CTRL_10_POS)
#define CCI_AUPLL_DL_CTRL_10_UMSK  (~(((1U << CCI_AUPLL_DL_CTRL_10_LEN) - 1) << CCI_AUPLL_DL_CTRL_10_POS))
#define CCI_AUPLL_DL_CTRL_6        CCI_AUPLL_DL_CTRL_6
#define CCI_AUPLL_DL_CTRL_6_POS    (25U)
#define CCI_AUPLL_DL_CTRL_6_LEN    (1U)
#define CCI_AUPLL_DL_CTRL_6_MSK    (((1U << CCI_AUPLL_DL_CTRL_6_LEN) - 1) << CCI_AUPLL_DL_CTRL_6_POS)
#define CCI_AUPLL_DL_CTRL_6_UMSK   (~(((1U << CCI_AUPLL_DL_CTRL_6_LEN) - 1) << CCI_AUPLL_DL_CTRL_6_POS))
#define CCI_AUPLL_DL_CTRL_5        CCI_AUPLL_DL_CTRL_5
#define CCI_AUPLL_DL_CTRL_5_POS    (26U)
#define CCI_AUPLL_DL_CTRL_5_LEN    (1U)
#define CCI_AUPLL_DL_CTRL_5_MSK    (((1U << CCI_AUPLL_DL_CTRL_5_LEN) - 1) << CCI_AUPLL_DL_CTRL_5_POS)
#define CCI_AUPLL_DL_CTRL_5_UMSK   (~(((1U << CCI_AUPLL_DL_CTRL_5_LEN) - 1) << CCI_AUPLL_DL_CTRL_5_POS))
#define CCI_AUPLL_DL_CTRL_4        CCI_AUPLL_DL_CTRL_4
#define CCI_AUPLL_DL_CTRL_4_POS    (27U)
#define CCI_AUPLL_DL_CTRL_4_LEN    (1U)
#define CCI_AUPLL_DL_CTRL_4_MSK    (((1U << CCI_AUPLL_DL_CTRL_4_LEN) - 1) << CCI_AUPLL_DL_CTRL_4_POS)
#define CCI_AUPLL_DL_CTRL_4_UMSK   (~(((1U << CCI_AUPLL_DL_CTRL_4_LEN) - 1) << CCI_AUPLL_DL_CTRL_4_POS))
#define CCI_AUPLL_DL_CTRL_3        CCI_AUPLL_DL_CTRL_3
#define CCI_AUPLL_DL_CTRL_3_POS    (28U)
#define CCI_AUPLL_DL_CTRL_3_LEN    (1U)
#define CCI_AUPLL_DL_CTRL_3_MSK    (((1U << CCI_AUPLL_DL_CTRL_3_LEN) - 1) << CCI_AUPLL_DL_CTRL_3_POS)
#define CCI_AUPLL_DL_CTRL_3_UMSK   (~(((1U << CCI_AUPLL_DL_CTRL_3_LEN) - 1) << CCI_AUPLL_DL_CTRL_3_POS))
#define CCI_AUPLL_DL_CTRL_2P5      CCI_AUPLL_DL_CTRL_2P5
#define CCI_AUPLL_DL_CTRL_2P5_POS  (29U)
#define CCI_AUPLL_DL_CTRL_2P5_LEN  (1U)
#define CCI_AUPLL_DL_CTRL_2P5_MSK  (((1U << CCI_AUPLL_DL_CTRL_2P5_LEN) - 1) << CCI_AUPLL_DL_CTRL_2P5_POS)
#define CCI_AUPLL_DL_CTRL_2P5_UMSK (~(((1U << CCI_AUPLL_DL_CTRL_2P5_LEN) - 1) << CCI_AUPLL_DL_CTRL_2P5_POS))
#define CCI_AUPLL_DL_CTRL_2        CCI_AUPLL_DL_CTRL_2
#define CCI_AUPLL_DL_CTRL_2_POS    (30U)
#define CCI_AUPLL_DL_CTRL_2_LEN    (1U)
#define CCI_AUPLL_DL_CTRL_2_MSK    (((1U << CCI_AUPLL_DL_CTRL_2_LEN) - 1) << CCI_AUPLL_DL_CTRL_2_POS)
#define CCI_AUPLL_DL_CTRL_2_UMSK   (~(((1U << CCI_AUPLL_DL_CTRL_2_LEN) - 1) << CCI_AUPLL_DL_CTRL_2_POS))
#define CCI_AUPLL_DL_CTRL_1        CCI_AUPLL_DL_CTRL_1
#define CCI_AUPLL_DL_CTRL_1_POS    (31U)
#define CCI_AUPLL_DL_CTRL_1_LEN    (1U)
#define CCI_AUPLL_DL_CTRL_1_MSK    (((1U << CCI_AUPLL_DL_CTRL_1_LEN) - 1) << CCI_AUPLL_DL_CTRL_1_POS)
#define CCI_AUPLL_DL_CTRL_1_UMSK   (~(((1U << CCI_AUPLL_DL_CTRL_1_LEN) - 1) << CCI_AUPLL_DL_CTRL_1_POS))

struct cci_reg {
    /* 0x0 : cci_cfg */
    union {
        struct {
            uint32_t cci_en             : 1;  /* [    0],        r/w,        0x1 */
            uint32_t cci_slv_sel_cci2   : 1;  /* [    1],        r/w,        0x0 */
            uint32_t cci_mas_sel_cci2   : 1;  /* [    2],        r/w,        0x0 */
            uint32_t cci_mas_hw_mode    : 1;  /* [    3],        r/w,        0x0 */
            uint32_t reg_m_cci_sclk_en  : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reg_div_m_cci_sclk : 2;  /* [ 6: 5],        r/w,        0x1 */
            uint32_t cfg_cci1_pre_read  : 1;  /* [    7],        r/w,        0x0 */
            uint32_t reg_scci_clk_inv   : 1;  /* [    8],        r/w,        0x0 */
            uint32_t reg_mcci_clk_inv   : 1;  /* [    9],        r/w,        0x1 */
            uint32_t reserved_10_15     : 6;  /* [15:10],       rsvd,        0x0 */
            uint32_t cfg_mcci_dly_r     : 1;  /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_31     : 15; /* [31:17],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } cci_cfg;

    /* 0x4 : cci_addr */
    union {
        struct {
            uint32_t apb_cci_addr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } cci_addr;

    /* 0x8 : cci_wdata */
    union {
        struct {
            uint32_t apb_cci_wdata : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } cci_wdata;

    /* 0xC : cci_rdata */
    union {
        struct {
            uint32_t apb_cci_rdata : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } cci_rdata;

    /* 0x10 : cci_ctl */
    union {
        struct {
            uint32_t cci_write_flag : 1;  /* [    0],          r,        0x0 */
            uint32_t cci_read_flag  : 1;  /* [    1],          r,        0x0 */
            uint32_t ahb_state      : 2;  /* [ 3: 2],          r,        0x0 */
            uint32_t reserved_4_31  : 28; /* [31: 4],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } cci_ctl;

    /* 0x14  reserved */
    uint8_t RESERVED0x14[1852];

    /* 0x750 : audio_pll_cfg0 */
    union {
        struct {
            uint32_t aupll_sdm_rstb     : 1;  /* [    0],        r/w,        0x1 */
            uint32_t aupll_postdiv_rstb : 1;  /* [    1],        r/w,        0x1 */
            uint32_t aupll_fbdv_rstb    : 1;  /* [    2],        r/w,        0x1 */
            uint32_t aupll_refdiv_rstb  : 1;  /* [    3],        r/w,        0x1 */
            uint32_t pu_aupll_postdiv   : 1;  /* [    4],        r/w,        0x1 */
            uint32_t pu_aupll_fbdv      : 1;  /* [    5],        r/w,        0x1 */
            uint32_t pu_aupll_clamp_op  : 1;  /* [    6],        r/w,        0x1 */
            uint32_t pu_aupll_pfd       : 1;  /* [    7],        r/w,        0x1 */
            uint32_t pu_aupll_cp        : 1;  /* [    8],        r/w,        0x1 */
            uint32_t pu_aupll_sfreg     : 1;  /* [    9],        r/w,        0x0 */
            uint32_t pu_aupll           : 1;  /* [   10],        r/w,        0x0 */
            uint32_t pu_aupll_clktree   : 1;  /* [   11],        r/w,        0x1 */
            uint32_t reserved_12_31     : 20; /* [31:12],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } audio_pll_cfg0;

    /* 0x754 : audio_pll_cfg1 */
    union {
        struct {
            uint32_t aupll_postdiv      : 7; /* [ 6: 0],        r/w,       0x12 */
            uint32_t reserved_7         : 1; /* [    7],       rsvd,        0x0 */
            uint32_t aupll_refdiv_ratio : 4; /* [11: 8],        r/w,        0x4 */
            uint32_t reserved_12_15     : 4; /* [15:12],       rsvd,        0x0 */
            uint32_t aupll_refclk_sel   : 2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_19     : 2; /* [19:18],       rsvd,        0x0 */
            uint32_t aupll_vg11_sel     : 2; /* [21:20],        r/w,        0x1 */
            uint32_t reserved_22_23     : 2; /* [23:22],       rsvd,        0x0 */
            uint32_t aupll_vg13_sel     : 2; /* [25:24],        r/w,        0x1 */
            uint32_t reserved_26_31     : 6; /* [31:26],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } audio_pll_cfg1;

    /* 0x758 : audio_pll_cfg2 */
    union {
        struct {
            uint32_t aupll_sel_cp_bias   : 1;  /* [    0],        r/w,        0x1 */
            uint32_t reserved_1_3        : 3;  /* [ 3: 1],       rsvd,        0x0 */
            uint32_t aupll_icp_5u        : 2;  /* [ 5: 4],        r/w,        0x0 */
            uint32_t aupll_icp_1u        : 2;  /* [ 7: 6],        r/w,        0x1 */
            uint32_t aupll_int_frac_sw   : 1;  /* [    8],        r/w,        0x1 */
            uint32_t aupll_cp_startup_en : 1;  /* [    9],        r/w,        0x1 */
            uint32_t aupll_cp_opamp_en   : 1;  /* [   10],        r/w,        0x1 */
            uint32_t reserved_11_31      : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } audio_pll_cfg2;

    /* 0x75C : audio_pll_cfg3 */
    union {
        struct {
            uint32_t aupll_c4_en    : 1;  /* [    0],        r/w,        0x1 */
            uint32_t reserved_1_3   : 3;  /* [ 3: 1],       rsvd,        0x0 */
            uint32_t aupll_r4       : 2;  /* [ 5: 4],        r/w,        0x2 */
            uint32_t reserved_6_7   : 2;  /* [ 7: 6],       rsvd,        0x0 */
            uint32_t aupll_r4_short : 1;  /* [    8],        r/w,        0x0 */
            uint32_t reserved_9_11  : 3;  /* [11: 9],       rsvd,        0x0 */
            uint32_t aupll_c3       : 2;  /* [13:12],        r/w,        0x2 */
            uint32_t aupll_cz       : 2;  /* [15:14],        r/w,        0x2 */
            uint32_t aupll_rz       : 3;  /* [18:16],        r/w,        0x5 */
            uint32_t reserved_19_31 : 13; /* [31:19],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } audio_pll_cfg3;

    /* 0x760 : audio_pll_cfg4 */
    union {
        struct {
            uint32_t aupll_sel_sample_clk : 2;  /* [ 1: 0],        r/w,        0x1 */
            uint32_t reserved_2_3         : 2;  /* [ 3: 2],       rsvd,        0x0 */
            uint32_t aupll_sel_fb_clk     : 2;  /* [ 5: 4],        r/w,        0x1 */
            uint32_t reserved_6_7         : 2;  /* [ 7: 6],       rsvd,        0x0 */
            uint32_t aupll_sdmclk_sel     : 1;  /* [    8],        r/w,        0x1 */
            uint32_t reserved_9_31        : 23; /* [31: 9],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } audio_pll_cfg4;

    /* 0x764 : audio_pll_cfg5 */
    union {
        struct {
            uint32_t aupll_vco_speed : 3;  /* [ 2: 0],        r/w,        0x3 */
            uint32_t reserved_3_31   : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } audio_pll_cfg5;

    /* 0x768 : audio_pll_cfg6 */
    union {
        struct {
            uint32_t aupll_sdmin      : 19; /* [18: 0],        r/w,    0x161e5 */
            uint32_t reserved_19_23   : 5;  /* [23:19],       rsvd,        0x0 */
            uint32_t aupll_sdm_bypass : 1;  /* [   24],        r/w,        0x0 */
            uint32_t reserved_25_31   : 7;  /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } audio_pll_cfg6;

    /* 0x76C : audio_pll_cfg7 */
    union {
        struct {
            uint32_t aupll_sdm_order_sel    : 1;  /* [    0],        r/w,        0x1 */
            uint32_t reserved_1_15          : 15; /* [15: 1],       rsvd,        0x0 */
            uint32_t aupll_sdm_sig_dith_sel : 2;  /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31         : 14; /* [31:18],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } audio_pll_cfg7;

    /* 0x770 : audio_pll_cfg8 */
    union {
        struct {
            uint32_t aupll_en_div1       : 1;  /* [    0],        r/w,        0x0 */
            uint32_t aupll_en_div2       : 1;  /* [    1],        r/w,        0x0 */
            uint32_t aupll_en_div2p5     : 1;  /* [    2],        r/w,        0x0 */
            uint32_t aupll_en_div3       : 1;  /* [    3],        r/w,        0x0 */
            uint32_t aupll_en_div4       : 1;  /* [    4],        r/w,        0x0 */
            uint32_t aupll_en_div5       : 1;  /* [    5],        r/w,        0x0 */
            uint32_t aupll_en_div6       : 1;  /* [    6],        r/w,        0x0 */
            uint32_t aupll_en_div10      : 1;  /* [    7],        r/w,        0x0 */
            uint32_t aupll_en_div15      : 1;  /* [    8],        r/w,        0x0 */
            uint32_t aupll_sel_div1_div2 : 1;  /* [    9],        r/w,        0x0 */
            uint32_t reserved_10_31      : 22; /* [31:10],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } audio_pll_cfg8;

    /* 0x774 : audio_pll_cfg9 */
    union {
        struct {
            uint32_t aupll_dc_tp_out_en     : 1;  /* [    0],        r/w,        0x0 */
            uint32_t ten_aupll              : 1;  /* [    1],        r/w,        0x0 */
            uint32_t ten_aupll_sfreg        : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3             : 1;  /* [    3],       rsvd,        0x0 */
            uint32_t dten_aupll_fin         : 1;  /* [    4],        r/w,        0x0 */
            uint32_t dten_aupll_fref        : 1;  /* [    5],        r/w,        0x0 */
            uint32_t dten_aupll_fsdm        : 1;  /* [    6],        r/w,        0x0 */
            uint32_t dten_aupll_div15       : 1;  /* [    7],        r/w,        0x0 */
            uint32_t dten_aupll_div5        : 1;  /* [    8],        r/w,        0x0 */
            uint32_t dten_aupll_postdiv_clk : 1;  /* [    9],        r/w,        0x0 */
            uint32_t dtest_aupll_pulldown   : 1;  /* [   10],        r/w,        0x1 */
            uint32_t reserved_11_31         : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } audio_pll_cfg9;

    /* 0x778 : audio_pll_cfg10 */
    union {
        struct {
            uint32_t aupll_ssc_en            : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_3            : 3;  /* [ 3: 1],       rsvd,        0x0 */
            uint32_t aupll_ssc_cnt           : 8;  /* [11: 4],        r/w,       0x64 */
            uint32_t aupll_ssc_gain          : 3;  /* [14:12],        r/w,        0x4 */
            uint32_t reserved_15             : 1;  /* [   15],       rsvd,        0x0 */
            uint32_t aupll_ssc_start_gate_en : 1;  /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_19          : 3;  /* [19:17],       rsvd,        0x0 */
            uint32_t aupll_ssc_start         : 1;  /* [   20],        r/w,        0x1 */
            uint32_t reserved_21_31          : 11; /* [31:21],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } audio_pll_cfg10;

    /* 0x77C : audio_pll_cfg11 */
    union {
        struct {
            uint32_t aupll_resv        : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_22    : 7;  /* [22:16],       rsvd,        0x0 */
            uint32_t aupll_dl_ctrl_15  : 1;  /* [   23],        r/w,        0x0 */
            uint32_t aupll_dl_ctrl_10  : 1;  /* [   24],        r/w,        0x0 */
            uint32_t aupll_dl_ctrl_6   : 1;  /* [   25],        r/w,        0x0 */
            uint32_t aupll_dl_ctrl_5   : 1;  /* [   26],        r/w,        0x0 */
            uint32_t aupll_dl_ctrl_4   : 1;  /* [   27],        r/w,        0x0 */
            uint32_t aupll_dl_ctrl_3   : 1;  /* [   28],        r/w,        0x0 */
            uint32_t aupll_dl_ctrl_2p5 : 1;  /* [   29],        r/w,        0x0 */
            uint32_t aupll_dl_ctrl_2   : 1;  /* [   30],        r/w,        0x0 */
            uint32_t aupll_dl_ctrl_1   : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } audio_pll_cfg11;
};

typedef volatile struct cci_reg cci_reg_t;

#endif /* __CCI_REG_H__ */
