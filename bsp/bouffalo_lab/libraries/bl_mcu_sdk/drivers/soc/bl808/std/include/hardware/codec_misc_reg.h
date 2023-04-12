/**
  ******************************************************************************
  * @file    codec_misc_reg.h
  * @version V1.0
  * @date    2021-05-11
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
#ifndef __CODEC_MISC_REG_H__
#define __CODEC_MISC_REG_H__

#include "bl808.h"

/* 0x00 : codec_bus_ctrl */
#define CODEC_MISC_CODEC_BUS_CTRL_OFFSET (0x00)
#define CODEC_MISC_RG_PCLK_FORCE_ON      CODEC_MISC_RG_PCLK_FORCE_ON
#define CODEC_MISC_RG_PCLK_FORCE_ON_POS  (0U)
#define CODEC_MISC_RG_PCLK_FORCE_ON_LEN  (16U)
#define CODEC_MISC_RG_PCLK_FORCE_ON_MSK  (((1U << CODEC_MISC_RG_PCLK_FORCE_ON_LEN) - 1) << CODEC_MISC_RG_PCLK_FORCE_ON_POS)
#define CODEC_MISC_RG_PCLK_FORCE_ON_UMSK (~(((1U << CODEC_MISC_RG_PCLK_FORCE_ON_LEN) - 1) << CODEC_MISC_RG_PCLK_FORCE_ON_POS))

/* 0x04 : codec_qos_ctrl */
#define CODEC_MISC_CODEC_QOS_CTRL_OFFSET (0x04)
#define CODEC_MISC_REG_JENC_AWQOS        CODEC_MISC_REG_JENC_AWQOS
#define CODEC_MISC_REG_JENC_AWQOS_POS    (0U)
#define CODEC_MISC_REG_JENC_AWQOS_LEN    (1U)
#define CODEC_MISC_REG_JENC_AWQOS_MSK    (((1U << CODEC_MISC_REG_JENC_AWQOS_LEN) - 1) << CODEC_MISC_REG_JENC_AWQOS_POS)
#define CODEC_MISC_REG_JENC_AWQOS_UMSK   (~(((1U << CODEC_MISC_REG_JENC_AWQOS_LEN) - 1) << CODEC_MISC_REG_JENC_AWQOS_POS))
#define CODEC_MISC_REG_JENC_ARQOS        CODEC_MISC_REG_JENC_ARQOS
#define CODEC_MISC_REG_JENC_ARQOS_POS    (1U)
#define CODEC_MISC_REG_JENC_ARQOS_LEN    (1U)
#define CODEC_MISC_REG_JENC_ARQOS_MSK    (((1U << CODEC_MISC_REG_JENC_ARQOS_LEN) - 1) << CODEC_MISC_REG_JENC_ARQOS_POS)
#define CODEC_MISC_REG_JENC_ARQOS_UMSK   (~(((1U << CODEC_MISC_REG_JENC_ARQOS_LEN) - 1) << CODEC_MISC_REG_JENC_ARQOS_POS))
#define CODEC_MISC_REG_JDEC_AWQOS        CODEC_MISC_REG_JDEC_AWQOS
#define CODEC_MISC_REG_JDEC_AWQOS_POS    (2U)
#define CODEC_MISC_REG_JDEC_AWQOS_LEN    (1U)
#define CODEC_MISC_REG_JDEC_AWQOS_MSK    (((1U << CODEC_MISC_REG_JDEC_AWQOS_LEN) - 1) << CODEC_MISC_REG_JDEC_AWQOS_POS)
#define CODEC_MISC_REG_JDEC_AWQOS_UMSK   (~(((1U << CODEC_MISC_REG_JDEC_AWQOS_LEN) - 1) << CODEC_MISC_REG_JDEC_AWQOS_POS))
#define CODEC_MISC_REG_JDEC_ARQOS        CODEC_MISC_REG_JDEC_ARQOS
#define CODEC_MISC_REG_JDEC_ARQOS_POS    (3U)
#define CODEC_MISC_REG_JDEC_ARQOS_LEN    (1U)
#define CODEC_MISC_REG_JDEC_ARQOS_MSK    (((1U << CODEC_MISC_REG_JDEC_ARQOS_LEN) - 1) << CODEC_MISC_REG_JDEC_ARQOS_POS)
#define CODEC_MISC_REG_JDEC_ARQOS_UMSK   (~(((1U << CODEC_MISC_REG_JDEC_ARQOS_LEN) - 1) << CODEC_MISC_REG_JDEC_ARQOS_POS))
#define CODEC_MISC_REG_VDO0_AWQOS        CODEC_MISC_REG_VDO0_AWQOS
#define CODEC_MISC_REG_VDO0_AWQOS_POS    (4U)
#define CODEC_MISC_REG_VDO0_AWQOS_LEN    (1U)
#define CODEC_MISC_REG_VDO0_AWQOS_MSK    (((1U << CODEC_MISC_REG_VDO0_AWQOS_LEN) - 1) << CODEC_MISC_REG_VDO0_AWQOS_POS)
#define CODEC_MISC_REG_VDO0_AWQOS_UMSK   (~(((1U << CODEC_MISC_REG_VDO0_AWQOS_LEN) - 1) << CODEC_MISC_REG_VDO0_AWQOS_POS))
#define CODEC_MISC_REG_VDO0_ARQOS        CODEC_MISC_REG_VDO0_ARQOS
#define CODEC_MISC_REG_VDO0_ARQOS_POS    (5U)
#define CODEC_MISC_REG_VDO0_ARQOS_LEN    (1U)
#define CODEC_MISC_REG_VDO0_ARQOS_MSK    (((1U << CODEC_MISC_REG_VDO0_ARQOS_LEN) - 1) << CODEC_MISC_REG_VDO0_ARQOS_POS)
#define CODEC_MISC_REG_VDO0_ARQOS_UMSK   (~(((1U << CODEC_MISC_REG_VDO0_ARQOS_LEN) - 1) << CODEC_MISC_REG_VDO0_ARQOS_POS))
#define CODEC_MISC_REG_VDO1_AWQOS        CODEC_MISC_REG_VDO1_AWQOS
#define CODEC_MISC_REG_VDO1_AWQOS_POS    (6U)
#define CODEC_MISC_REG_VDO1_AWQOS_LEN    (1U)
#define CODEC_MISC_REG_VDO1_AWQOS_MSK    (((1U << CODEC_MISC_REG_VDO1_AWQOS_LEN) - 1) << CODEC_MISC_REG_VDO1_AWQOS_POS)
#define CODEC_MISC_REG_VDO1_AWQOS_UMSK   (~(((1U << CODEC_MISC_REG_VDO1_AWQOS_LEN) - 1) << CODEC_MISC_REG_VDO1_AWQOS_POS))
#define CODEC_MISC_REG_VDO1_ARQOS        CODEC_MISC_REG_VDO1_ARQOS
#define CODEC_MISC_REG_VDO1_ARQOS_POS    (7U)
#define CODEC_MISC_REG_VDO1_ARQOS_LEN    (1U)
#define CODEC_MISC_REG_VDO1_ARQOS_MSK    (((1U << CODEC_MISC_REG_VDO1_ARQOS_LEN) - 1) << CODEC_MISC_REG_VDO1_ARQOS_POS)
#define CODEC_MISC_REG_VDO1_ARQOS_UMSK   (~(((1U << CODEC_MISC_REG_VDO1_ARQOS_LEN) - 1) << CODEC_MISC_REG_VDO1_ARQOS_POS))
#define CODEC_MISC_REG_REF_AWQOS         CODEC_MISC_REG_REF_AWQOS
#define CODEC_MISC_REG_REF_AWQOS_POS     (8U)
#define CODEC_MISC_REG_REF_AWQOS_LEN     (1U)
#define CODEC_MISC_REG_REF_AWQOS_MSK     (((1U << CODEC_MISC_REG_REF_AWQOS_LEN) - 1) << CODEC_MISC_REG_REF_AWQOS_POS)
#define CODEC_MISC_REG_REF_AWQOS_UMSK    (~(((1U << CODEC_MISC_REG_REF_AWQOS_LEN) - 1) << CODEC_MISC_REG_REF_AWQOS_POS))
#define CODEC_MISC_REG_REF_ARQOS         CODEC_MISC_REG_REF_ARQOS
#define CODEC_MISC_REG_REF_ARQOS_POS     (9U)
#define CODEC_MISC_REG_REF_ARQOS_LEN     (1U)
#define CODEC_MISC_REG_REF_ARQOS_MSK     (((1U << CODEC_MISC_REG_REF_ARQOS_LEN) - 1) << CODEC_MISC_REG_REF_ARQOS_POS)
#define CODEC_MISC_REG_REF_ARQOS_UMSK    (~(((1U << CODEC_MISC_REG_REF_ARQOS_LEN) - 1) << CODEC_MISC_REG_REF_ARQOS_POS))
#define CODEC_MISC_REG_CNN_AWQOS         CODEC_MISC_REG_CNN_AWQOS
#define CODEC_MISC_REG_CNN_AWQOS_POS     (10U)
#define CODEC_MISC_REG_CNN_AWQOS_LEN     (1U)
#define CODEC_MISC_REG_CNN_AWQOS_MSK     (((1U << CODEC_MISC_REG_CNN_AWQOS_LEN) - 1) << CODEC_MISC_REG_CNN_AWQOS_POS)
#define CODEC_MISC_REG_CNN_AWQOS_UMSK    (~(((1U << CODEC_MISC_REG_CNN_AWQOS_LEN) - 1) << CODEC_MISC_REG_CNN_AWQOS_POS))
#define CODEC_MISC_REG_CNN_ARQOS         CODEC_MISC_REG_CNN_ARQOS
#define CODEC_MISC_REG_CNN_ARQOS_POS     (11U)
#define CODEC_MISC_REG_CNN_ARQOS_LEN     (1U)
#define CODEC_MISC_REG_CNN_ARQOS_MSK     (((1U << CODEC_MISC_REG_CNN_ARQOS_LEN) - 1) << CODEC_MISC_REG_CNN_ARQOS_POS)
#define CODEC_MISC_REG_CNN_ARQOS_UMSK    (~(((1U << CODEC_MISC_REG_CNN_ARQOS_LEN) - 1) << CODEC_MISC_REG_CNN_ARQOS_POS))

/* 0x08 : codec_bus_thre */
#define CODEC_MISC_CODEC_BUS_THRE_OFFSET        (0x08)
#define CODEC_MISC_REG_X_WTHRE_BLAI2SYSRAM      CODEC_MISC_REG_X_WTHRE_BLAI2SYSRAM
#define CODEC_MISC_REG_X_WTHRE_BLAI2SYSRAM_POS  (0U)
#define CODEC_MISC_REG_X_WTHRE_BLAI2SYSRAM_LEN  (2U)
#define CODEC_MISC_REG_X_WTHRE_BLAI2SYSRAM_MSK  (((1U << CODEC_MISC_REG_X_WTHRE_BLAI2SYSRAM_LEN) - 1) << CODEC_MISC_REG_X_WTHRE_BLAI2SYSRAM_POS)
#define CODEC_MISC_REG_X_WTHRE_BLAI2SYSRAM_UMSK (~(((1U << CODEC_MISC_REG_X_WTHRE_BLAI2SYSRAM_LEN) - 1) << CODEC_MISC_REG_X_WTHRE_BLAI2SYSRAM_POS))
#define CODEC_MISC_REG_X_WTHRE_BLAI2EXT         CODEC_MISC_REG_X_WTHRE_BLAI2EXT
#define CODEC_MISC_REG_X_WTHRE_BLAI2EXT_POS     (2U)
#define CODEC_MISC_REG_X_WTHRE_BLAI2EXT_LEN     (2U)
#define CODEC_MISC_REG_X_WTHRE_BLAI2EXT_MSK     (((1U << CODEC_MISC_REG_X_WTHRE_BLAI2EXT_LEN) - 1) << CODEC_MISC_REG_X_WTHRE_BLAI2EXT_POS)
#define CODEC_MISC_REG_X_WTHRE_BLAI2EXT_UMSK    (~(((1U << CODEC_MISC_REG_X_WTHRE_BLAI2EXT_LEN) - 1) << CODEC_MISC_REG_X_WTHRE_BLAI2EXT_POS))
#define CODEC_MISC_REG_X_WTHRE_VDO2PB           CODEC_MISC_REG_X_WTHRE_VDO2PB
#define CODEC_MISC_REG_X_WTHRE_VDO2PB_POS       (4U)
#define CODEC_MISC_REG_X_WTHRE_VDO2PB_LEN       (2U)
#define CODEC_MISC_REG_X_WTHRE_VDO2PB_MSK       (((1U << CODEC_MISC_REG_X_WTHRE_VDO2PB_LEN) - 1) << CODEC_MISC_REG_X_WTHRE_VDO2PB_POS)
#define CODEC_MISC_REG_X_WTHRE_VDO2PB_UMSK      (~(((1U << CODEC_MISC_REG_X_WTHRE_VDO2PB_LEN) - 1) << CODEC_MISC_REG_X_WTHRE_VDO2PB_POS))
#define CODEC_MISC_REG_X_WTHRE_VDO2PA           CODEC_MISC_REG_X_WTHRE_VDO2PA
#define CODEC_MISC_REG_X_WTHRE_VDO2PA_POS       (6U)
#define CODEC_MISC_REG_X_WTHRE_VDO2PA_LEN       (2U)
#define CODEC_MISC_REG_X_WTHRE_VDO2PA_MSK       (((1U << CODEC_MISC_REG_X_WTHRE_VDO2PA_LEN) - 1) << CODEC_MISC_REG_X_WTHRE_VDO2PA_POS)
#define CODEC_MISC_REG_X_WTHRE_VDO2PA_UMSK      (~(((1U << CODEC_MISC_REG_X_WTHRE_VDO2PA_LEN) - 1) << CODEC_MISC_REG_X_WTHRE_VDO2PA_POS))
#define CODEC_MISC_REG_X_WTHRE_VDO2SYSRAM       CODEC_MISC_REG_X_WTHRE_VDO2SYSRAM
#define CODEC_MISC_REG_X_WTHRE_VDO2SYSRAM_POS   (8U)
#define CODEC_MISC_REG_X_WTHRE_VDO2SYSRAM_LEN   (2U)
#define CODEC_MISC_REG_X_WTHRE_VDO2SYSRAM_MSK   (((1U << CODEC_MISC_REG_X_WTHRE_VDO2SYSRAM_LEN) - 1) << CODEC_MISC_REG_X_WTHRE_VDO2SYSRAM_POS)
#define CODEC_MISC_REG_X_WTHRE_VDO2SYSRAM_UMSK  (~(((1U << CODEC_MISC_REG_X_WTHRE_VDO2SYSRAM_LEN) - 1) << CODEC_MISC_REG_X_WTHRE_VDO2SYSRAM_POS))

/* 0x10 : codec_bus_dec_err */
#define CODEC_MISC_CODEC_BUS_DEC_ERR_OFFSET    (0x10)
#define CODEC_MISC_REG_DEC_ERR_CLR             CODEC_MISC_REG_DEC_ERR_CLR
#define CODEC_MISC_REG_DEC_ERR_CLR_POS         (0U)
#define CODEC_MISC_REG_DEC_ERR_CLR_LEN         (1U)
#define CODEC_MISC_REG_DEC_ERR_CLR_MSK         (((1U << CODEC_MISC_REG_DEC_ERR_CLR_LEN) - 1) << CODEC_MISC_REG_DEC_ERR_CLR_POS)
#define CODEC_MISC_REG_DEC_ERR_CLR_UMSK        (~(((1U << CODEC_MISC_REG_DEC_ERR_CLR_LEN) - 1) << CODEC_MISC_REG_DEC_ERR_CLR_POS))
#define CODEC_MISC_REG_DEC_ERR_LATCH_LAST      CODEC_MISC_REG_DEC_ERR_LATCH_LAST
#define CODEC_MISC_REG_DEC_ERR_LATCH_LAST_POS  (1U)
#define CODEC_MISC_REG_DEC_ERR_LATCH_LAST_LEN  (1U)
#define CODEC_MISC_REG_DEC_ERR_LATCH_LAST_MSK  (((1U << CODEC_MISC_REG_DEC_ERR_LATCH_LAST_LEN) - 1) << CODEC_MISC_REG_DEC_ERR_LATCH_LAST_POS)
#define CODEC_MISC_REG_DEC_ERR_LATCH_LAST_UMSK (~(((1U << CODEC_MISC_REG_DEC_ERR_LATCH_LAST_LEN) - 1) << CODEC_MISC_REG_DEC_ERR_LATCH_LAST_POS))
#define CODEC_MISC_CODEC_HS_DEC_ERR_LAT        CODEC_MISC_CODEC_HS_DEC_ERR_LAT
#define CODEC_MISC_CODEC_HS_DEC_ERR_LAT_POS    (8U)
#define CODEC_MISC_CODEC_HS_DEC_ERR_LAT_LEN    (1U)
#define CODEC_MISC_CODEC_HS_DEC_ERR_LAT_MSK    (((1U << CODEC_MISC_CODEC_HS_DEC_ERR_LAT_LEN) - 1) << CODEC_MISC_CODEC_HS_DEC_ERR_LAT_POS)
#define CODEC_MISC_CODEC_HS_DEC_ERR_LAT_UMSK   (~(((1U << CODEC_MISC_CODEC_HS_DEC_ERR_LAT_LEN) - 1) << CODEC_MISC_CODEC_HS_DEC_ERR_LAT_POS))
#define CODEC_MISC_CODEC_HS_DEC_ERR_WRITE      CODEC_MISC_CODEC_HS_DEC_ERR_WRITE
#define CODEC_MISC_CODEC_HS_DEC_ERR_WRITE_POS  (9U)
#define CODEC_MISC_CODEC_HS_DEC_ERR_WRITE_LEN  (1U)
#define CODEC_MISC_CODEC_HS_DEC_ERR_WRITE_MSK  (((1U << CODEC_MISC_CODEC_HS_DEC_ERR_WRITE_LEN) - 1) << CODEC_MISC_CODEC_HS_DEC_ERR_WRITE_POS)
#define CODEC_MISC_CODEC_HS_DEC_ERR_WRITE_UMSK (~(((1U << CODEC_MISC_CODEC_HS_DEC_ERR_WRITE_LEN) - 1) << CODEC_MISC_CODEC_HS_DEC_ERR_WRITE_POS))
#define CODEC_MISC_CODEC_HS_DEC_ERR_SRC        CODEC_MISC_CODEC_HS_DEC_ERR_SRC
#define CODEC_MISC_CODEC_HS_DEC_ERR_SRC_POS    (12U)
#define CODEC_MISC_CODEC_HS_DEC_ERR_SRC_LEN    (2U)
#define CODEC_MISC_CODEC_HS_DEC_ERR_SRC_MSK    (((1U << CODEC_MISC_CODEC_HS_DEC_ERR_SRC_LEN) - 1) << CODEC_MISC_CODEC_HS_DEC_ERR_SRC_POS)
#define CODEC_MISC_CODEC_HS_DEC_ERR_SRC_UMSK   (~(((1U << CODEC_MISC_CODEC_HS_DEC_ERR_SRC_LEN) - 1) << CODEC_MISC_CODEC_HS_DEC_ERR_SRC_POS))
#define CODEC_MISC_CODEC_HS_DEC_ERR_ID         CODEC_MISC_CODEC_HS_DEC_ERR_ID
#define CODEC_MISC_CODEC_HS_DEC_ERR_ID_POS     (16U)
#define CODEC_MISC_CODEC_HS_DEC_ERR_ID_LEN     (1U)
#define CODEC_MISC_CODEC_HS_DEC_ERR_ID_MSK     (((1U << CODEC_MISC_CODEC_HS_DEC_ERR_ID_LEN) - 1) << CODEC_MISC_CODEC_HS_DEC_ERR_ID_POS)
#define CODEC_MISC_CODEC_HS_DEC_ERR_ID_UMSK    (~(((1U << CODEC_MISC_CODEC_HS_DEC_ERR_ID_LEN) - 1) << CODEC_MISC_CODEC_HS_DEC_ERR_ID_POS))

/* 0x14 : codec_bus_dec_err_addr */
#define CODEC_MISC_CODEC_BUS_DEC_ERR_ADDR_OFFSET (0x14)
#define CODEC_MISC_CODEC_HS_DEC_ERR_ADDR         CODEC_MISC_CODEC_HS_DEC_ERR_ADDR
#define CODEC_MISC_CODEC_HS_DEC_ERR_ADDR_POS     (0U)
#define CODEC_MISC_CODEC_HS_DEC_ERR_ADDR_LEN     (32U)
#define CODEC_MISC_CODEC_HS_DEC_ERR_ADDR_MSK     (((1U << CODEC_MISC_CODEC_HS_DEC_ERR_ADDR_LEN) - 1) << CODEC_MISC_CODEC_HS_DEC_ERR_ADDR_POS)
#define CODEC_MISC_CODEC_HS_DEC_ERR_ADDR_UMSK    (~(((1U << CODEC_MISC_CODEC_HS_DEC_ERR_ADDR_LEN) - 1) << CODEC_MISC_CODEC_HS_DEC_ERR_ADDR_POS))

/* 0x20 : blai_lmtr_rd */
#define CODEC_MISC_BLAI_LMTR_RD_OFFSET     (0x20)
#define CODEC_MISC_REG_BLAI_RCMD_CNT       CODEC_MISC_REG_BLAI_RCMD_CNT
#define CODEC_MISC_REG_BLAI_RCMD_CNT_POS   (0U)
#define CODEC_MISC_REG_BLAI_RCMD_CNT_LEN   (16U)
#define CODEC_MISC_REG_BLAI_RCMD_CNT_MSK   (((1U << CODEC_MISC_REG_BLAI_RCMD_CNT_LEN) - 1) << CODEC_MISC_REG_BLAI_RCMD_CNT_POS)
#define CODEC_MISC_REG_BLAI_RCMD_CNT_UMSK  (~(((1U << CODEC_MISC_REG_BLAI_RCMD_CNT_LEN) - 1) << CODEC_MISC_REG_BLAI_RCMD_CNT_POS))
#define CODEC_MISC_REG_BLAI_RCMD_MODE      CODEC_MISC_REG_BLAI_RCMD_MODE
#define CODEC_MISC_REG_BLAI_RCMD_MODE_POS  (31U)
#define CODEC_MISC_REG_BLAI_RCMD_MODE_LEN  (1U)
#define CODEC_MISC_REG_BLAI_RCMD_MODE_MSK  (((1U << CODEC_MISC_REG_BLAI_RCMD_MODE_LEN) - 1) << CODEC_MISC_REG_BLAI_RCMD_MODE_POS)
#define CODEC_MISC_REG_BLAI_RCMD_MODE_UMSK (~(((1U << CODEC_MISC_REG_BLAI_RCMD_MODE_LEN) - 1) << CODEC_MISC_REG_BLAI_RCMD_MODE_POS))

/* 0x24 : blai_lmtr_wr */
#define CODEC_MISC_BLAI_LMTR_WR_OFFSET     (0x24)
#define CODEC_MISC_REG_BLAI_WCMD_CNT       CODEC_MISC_REG_BLAI_WCMD_CNT
#define CODEC_MISC_REG_BLAI_WCMD_CNT_POS   (0U)
#define CODEC_MISC_REG_BLAI_WCMD_CNT_LEN   (16U)
#define CODEC_MISC_REG_BLAI_WCMD_CNT_MSK   (((1U << CODEC_MISC_REG_BLAI_WCMD_CNT_LEN) - 1) << CODEC_MISC_REG_BLAI_WCMD_CNT_POS)
#define CODEC_MISC_REG_BLAI_WCMD_CNT_UMSK  (~(((1U << CODEC_MISC_REG_BLAI_WCMD_CNT_LEN) - 1) << CODEC_MISC_REG_BLAI_WCMD_CNT_POS))
#define CODEC_MISC_REG_BLAI_WCMD_MODE      CODEC_MISC_REG_BLAI_WCMD_MODE
#define CODEC_MISC_REG_BLAI_WCMD_MODE_POS  (31U)
#define CODEC_MISC_REG_BLAI_WCMD_MODE_LEN  (1U)
#define CODEC_MISC_REG_BLAI_WCMD_MODE_MSK  (((1U << CODEC_MISC_REG_BLAI_WCMD_MODE_LEN) - 1) << CODEC_MISC_REG_BLAI_WCMD_MODE_POS)
#define CODEC_MISC_REG_BLAI_WCMD_MODE_UMSK (~(((1U << CODEC_MISC_REG_BLAI_WCMD_MODE_LEN) - 1) << CODEC_MISC_REG_BLAI_WCMD_MODE_POS))

/* 0x28 : id_selection */
#define CODEC_MISC_ID_SELECTION_OFFSET (0x28)
#define CODEC_MISC_RG_JENC_ID_SEL      CODEC_MISC_RG_JENC_ID_SEL
#define CODEC_MISC_RG_JENC_ID_SEL_POS  (0U)
#define CODEC_MISC_RG_JENC_ID_SEL_LEN  (1U)
#define CODEC_MISC_RG_JENC_ID_SEL_MSK  (((1U << CODEC_MISC_RG_JENC_ID_SEL_LEN) - 1) << CODEC_MISC_RG_JENC_ID_SEL_POS)
#define CODEC_MISC_RG_JENC_ID_SEL_UMSK (~(((1U << CODEC_MISC_RG_JENC_ID_SEL_LEN) - 1) << CODEC_MISC_RG_JENC_ID_SEL_POS))

/* 0xFC : CODEC_MISC_Dummy */
#define CODEC_MISC_DUMMY_OFFSET   (0xFC)
#define CODEC_MISC_DUMMY_REG      CODEC_MISC_DUMMY_REG
#define CODEC_MISC_DUMMY_REG_POS  (0U)
#define CODEC_MISC_DUMMY_REG_LEN  (32U)
#define CODEC_MISC_DUMMY_REG_MSK  (((1U << CODEC_MISC_DUMMY_REG_LEN) - 1) << CODEC_MISC_DUMMY_REG_POS)
#define CODEC_MISC_DUMMY_REG_UMSK (~(((1U << CODEC_MISC_DUMMY_REG_LEN) - 1) << CODEC_MISC_DUMMY_REG_POS))

struct codec_misc_reg {
    /* 0x00 : codec_bus_ctrl */
    union {
        struct {
            uint32_t rg_pclk_force_on : 16; /* [15: 0],        r/w,     0xffff */
            uint32_t reserved_16_31   : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } codec_bus_ctrl;

    /* 0x04 : codec_qos_ctrl */
    union {
        struct {
            uint32_t reg_jenc_awqos : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reg_jenc_arqos : 1;  /* [    1],        r/w,        0x0 */
            uint32_t reg_jdec_awqos : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reg_jdec_arqos : 1;  /* [    3],        r/w,        0x0 */
            uint32_t reg_vdo0_awqos : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reg_vdo0_arqos : 1;  /* [    5],        r/w,        0x0 */
            uint32_t reg_vdo1_awqos : 1;  /* [    6],        r/w,        0x0 */
            uint32_t reg_vdo1_arqos : 1;  /* [    7],        r/w,        0x0 */
            uint32_t reg_ref_awqos  : 1;  /* [    8],        r/w,        0x0 */
            uint32_t reg_ref_arqos  : 1;  /* [    9],        r/w,        0x0 */
            uint32_t reg_cnn_awqos  : 1;  /* [   10],        r/w,        0x0 */
            uint32_t reg_cnn_arqos  : 1;  /* [   11],        r/w,        0x0 */
            uint32_t reserved_12_31 : 20; /* [31:12],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } codec_qos_ctrl;

    /* 0x08 : codec_bus_thre */
    union {
        struct {
            uint32_t reg_x_wthre_blai2sysram : 2;  /* [ 1: 0],        r/w,        0x0 */
            uint32_t reg_x_wthre_blai2ext    : 2;  /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_x_wthre_vdo2pb      : 2;  /* [ 5: 4],        r/w,        0x0 */
            uint32_t reg_x_wthre_vdo2pa      : 2;  /* [ 7: 6],        r/w,        0x0 */
            uint32_t reg_x_wthre_vdo2sysram  : 2;  /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_31          : 22; /* [31:10],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } codec_bus_thre;

    /* 0xc  reserved */
    uint8_t RESERVED0xc[20];

    /* 0x10 : codec_bus_dec_err */
    union {
        struct
        {
            uint32_t reg_dec_err_clr        : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reg_dec_err_latch_last : 1;  /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_7           : 6;  /* [ 7: 2],       rsvd,        0x0 */
            uint32_t codec_hs_dec_err_lat   : 1;  /* [    8],          r,        0x0 */
            uint32_t codec_hs_dec_err_write : 1;  /* [    9],          r,        0x0 */
            uint32_t reserved_10_11         : 2;  /* [11:10],       rsvd,        0x0 */
            uint32_t codec_hs_dec_err_src   : 2;  /* [13:12],          r,        0x0 */
            uint32_t reserved_14_15         : 2;  /* [15:14],       rsvd,        0x0 */
            uint32_t codec_hs_dec_err_id    : 1;  /* [   16],          r,        0x0 */
            uint32_t reserved_17_31         : 15; /* [31:17],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } codec_bus_dec_err;

    /* 0x14 : codec_bus_dec_err_addr */
    union {
        struct
        {
            uint32_t codec_hs_dec_err_addr : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } codec_bus_dec_err_addr;

    /* 0x18  reserved */
    uint8_t RESERVED0x18[8];

    /* 0x20 : blai_lmtr_rd */
    union {
        struct {
            uint32_t reg_blai_rcmd_cnt  : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_30     : 15; /* [30:16],       rsvd,        0x0 */
            uint32_t reg_blai_rcmd_mode : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } blai_lmtr_rd;

    /* 0x24 : blai_lmtr_wr */
    union {
        struct {
            uint32_t reg_blai_wcmd_cnt  : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_30     : 15; /* [30:16],       rsvd,        0x0 */
            uint32_t reg_blai_wcmd_mode : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } blai_lmtr_wr;

    /* 0x28 : id_selection */
    union {
        struct {
            uint32_t rg_jenc_id_sel : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_31  : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } id_selection;

    /* 0x2c  reserved */
    uint8_t RESERVED0x2c[208];

    /* 0xFC : CODEC_MISC_Dummy */
    union {
        struct {
            uint32_t dummy_reg : 32; /* [31: 0],        r/w, 0xffff0000 */
        } BF;
        uint32_t WORD;
    } CODEC_MISC_Dummy;
};

typedef volatile struct codec_misc_reg codec_misc_reg_t;

#endif /* __CODEC_MISC_REG_H__ */
