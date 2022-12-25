/**
  ******************************************************************************
  * @file    dsp2_axi_ctrl_reg.h
  * @version V1.0
  * @date    2021-07-19
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
#ifndef __DSP2_AXI_CTRL_REG_H__
#define __DSP2_AXI_CTRL_REG_H__

#include "bl808.h"

/* 0x0 : nr_control */
#define DSP2_AXI_CTRL_NR_CONTROL_OFFSET     (0x0)
#define DSP2_AXI_CTRL_REG_ENABLE            DSP2_AXI_CTRL_REG_ENABLE
#define DSP2_AXI_CTRL_REG_ENABLE_POS        (0U)
#define DSP2_AXI_CTRL_REG_ENABLE_LEN        (1U)
#define DSP2_AXI_CTRL_REG_ENABLE_MSK        (((1U << DSP2_AXI_CTRL_REG_ENABLE_LEN) - 1) << DSP2_AXI_CTRL_REG_ENABLE_POS)
#define DSP2_AXI_CTRL_REG_ENABLE_UMSK       (~(((1U << DSP2_AXI_CTRL_REG_ENABLE_LEN) - 1) << DSP2_AXI_CTRL_REG_ENABLE_POS))
#define DSP2_AXI_CTRL_REG_DRAIN_CLR         DSP2_AXI_CTRL_REG_DRAIN_CLR
#define DSP2_AXI_CTRL_REG_DRAIN_CLR_POS     (1U)
#define DSP2_AXI_CTRL_REG_DRAIN_CLR_LEN     (1U)
#define DSP2_AXI_CTRL_REG_DRAIN_CLR_MSK     (((1U << DSP2_AXI_CTRL_REG_DRAIN_CLR_LEN) - 1) << DSP2_AXI_CTRL_REG_DRAIN_CLR_POS)
#define DSP2_AXI_CTRL_REG_DRAIN_CLR_UMSK    (~(((1U << DSP2_AXI_CTRL_REG_DRAIN_CLR_LEN) - 1) << DSP2_AXI_CTRL_REG_DRAIN_CLR_POS))
#define DSP2_AXI_CTRL_REG_OVERFLOW_CLR      DSP2_AXI_CTRL_REG_OVERFLOW_CLR
#define DSP2_AXI_CTRL_REG_OVERFLOW_CLR_POS  (2U)
#define DSP2_AXI_CTRL_REG_OVERFLOW_CLR_LEN  (1U)
#define DSP2_AXI_CTRL_REG_OVERFLOW_CLR_MSK  (((1U << DSP2_AXI_CTRL_REG_OVERFLOW_CLR_LEN) - 1) << DSP2_AXI_CTRL_REG_OVERFLOW_CLR_POS)
#define DSP2_AXI_CTRL_REG_OVERFLOW_CLR_UMSK (~(((1U << DSP2_AXI_CTRL_REG_OVERFLOW_CLR_LEN) - 1) << DSP2_AXI_CTRL_REG_OVERFLOW_CLR_POS))
#define DSP2_AXI_CTRL_REG_XLEN              DSP2_AXI_CTRL_REG_XLEN
#define DSP2_AXI_CTRL_REG_XLEN_POS          (4U)
#define DSP2_AXI_CTRL_REG_XLEN_LEN          (3U)
#define DSP2_AXI_CTRL_REG_XLEN_MSK          (((1U << DSP2_AXI_CTRL_REG_XLEN_LEN) - 1) << DSP2_AXI_CTRL_REG_XLEN_POS)
#define DSP2_AXI_CTRL_REG_XLEN_UMSK         (~(((1U << DSP2_AXI_CTRL_REG_XLEN_LEN) - 1) << DSP2_AXI_CTRL_REG_XLEN_POS))
#define DSP2_AXI_CTRL_REG_QOS_SW_MODE       DSP2_AXI_CTRL_REG_QOS_SW_MODE
#define DSP2_AXI_CTRL_REG_QOS_SW_MODE_POS   (8U)
#define DSP2_AXI_CTRL_REG_QOS_SW_MODE_LEN   (1U)
#define DSP2_AXI_CTRL_REG_QOS_SW_MODE_MSK   (((1U << DSP2_AXI_CTRL_REG_QOS_SW_MODE_LEN) - 1) << DSP2_AXI_CTRL_REG_QOS_SW_MODE_POS)
#define DSP2_AXI_CTRL_REG_QOS_SW_MODE_UMSK  (~(((1U << DSP2_AXI_CTRL_REG_QOS_SW_MODE_LEN) - 1) << DSP2_AXI_CTRL_REG_QOS_SW_MODE_POS))
#define DSP2_AXI_CTRL_REG_QOS_SW            DSP2_AXI_CTRL_REG_QOS_SW
#define DSP2_AXI_CTRL_REG_QOS_SW_POS        (9U)
#define DSP2_AXI_CTRL_REG_QOS_SW_LEN        (1U)
#define DSP2_AXI_CTRL_REG_QOS_SW_MSK        (((1U << DSP2_AXI_CTRL_REG_QOS_SW_LEN) - 1) << DSP2_AXI_CTRL_REG_QOS_SW_POS)
#define DSP2_AXI_CTRL_REG_QOS_SW_UMSK       (~(((1U << DSP2_AXI_CTRL_REG_QOS_SW_LEN) - 1) << DSP2_AXI_CTRL_REG_QOS_SW_POS))

/* 0x4 : nr_haddr_start_address */
#define DSP2_AXI_CTRL_NR_HADDR_START_ADDRESS_OFFSET (0x4)
#define DSP2_AXI_CTRL_REG_ADDR_START                DSP2_AXI_CTRL_REG_ADDR_START
#define DSP2_AXI_CTRL_REG_ADDR_START_POS            (0U)
#define DSP2_AXI_CTRL_REG_ADDR_START_LEN            (32U)
#define DSP2_AXI_CTRL_REG_ADDR_START_MSK            (((1U << DSP2_AXI_CTRL_REG_ADDR_START_LEN) - 1) << DSP2_AXI_CTRL_REG_ADDR_START_POS)
#define DSP2_AXI_CTRL_REG_ADDR_START_UMSK           (~(((1U << DSP2_AXI_CTRL_REG_ADDR_START_LEN) - 1) << DSP2_AXI_CTRL_REG_ADDR_START_POS))

/* 0x8 : nr_memory_burst_count */
#define DSP2_AXI_CTRL_NR_MEMORY_BURST_COUNT_OFFSET (0x8)
#define DSP2_AXI_CTRL_REG_BURST_CNT                DSP2_AXI_CTRL_REG_BURST_CNT
#define DSP2_AXI_CTRL_REG_BURST_CNT_POS            (0U)
#define DSP2_AXI_CTRL_REG_BURST_CNT_LEN            (32U)
#define DSP2_AXI_CTRL_REG_BURST_CNT_MSK            (((1U << DSP2_AXI_CTRL_REG_BURST_CNT_LEN) - 1) << DSP2_AXI_CTRL_REG_BURST_CNT_POS)
#define DSP2_AXI_CTRL_REG_BURST_CNT_UMSK           (~(((1U << DSP2_AXI_CTRL_REG_BURST_CNT_LEN) - 1) << DSP2_AXI_CTRL_REG_BURST_CNT_POS))

/* 0xC : nr_hsync_control */
#define DSP2_AXI_CTRL_NR_HSYNC_CONTROL_OFFSET  (0xC)
#define DSP2_AXI_CTRL_REG_HSYNC_ACT_END        DSP2_AXI_CTRL_REG_HSYNC_ACT_END
#define DSP2_AXI_CTRL_REG_HSYNC_ACT_END_POS    (0U)
#define DSP2_AXI_CTRL_REG_HSYNC_ACT_END_LEN    (16U)
#define DSP2_AXI_CTRL_REG_HSYNC_ACT_END_MSK    (((1U << DSP2_AXI_CTRL_REG_HSYNC_ACT_END_LEN) - 1) << DSP2_AXI_CTRL_REG_HSYNC_ACT_END_POS)
#define DSP2_AXI_CTRL_REG_HSYNC_ACT_END_UMSK   (~(((1U << DSP2_AXI_CTRL_REG_HSYNC_ACT_END_LEN) - 1) << DSP2_AXI_CTRL_REG_HSYNC_ACT_END_POS))
#define DSP2_AXI_CTRL_REG_HSYNC_ACT_START      DSP2_AXI_CTRL_REG_HSYNC_ACT_START
#define DSP2_AXI_CTRL_REG_HSYNC_ACT_START_POS  (16U)
#define DSP2_AXI_CTRL_REG_HSYNC_ACT_START_LEN  (16U)
#define DSP2_AXI_CTRL_REG_HSYNC_ACT_START_MSK  (((1U << DSP2_AXI_CTRL_REG_HSYNC_ACT_START_LEN) - 1) << DSP2_AXI_CTRL_REG_HSYNC_ACT_START_POS)
#define DSP2_AXI_CTRL_REG_HSYNC_ACT_START_UMSK (~(((1U << DSP2_AXI_CTRL_REG_HSYNC_ACT_START_LEN) - 1) << DSP2_AXI_CTRL_REG_HSYNC_ACT_START_POS))

/* 0x10 : nr_vsync_control */
#define DSP2_AXI_CTRL_NR_VSYNC_CONTROL_OFFSET  (0x10)
#define DSP2_AXI_CTRL_REG_VSYNC_ACT_END        DSP2_AXI_CTRL_REG_VSYNC_ACT_END
#define DSP2_AXI_CTRL_REG_VSYNC_ACT_END_POS    (0U)
#define DSP2_AXI_CTRL_REG_VSYNC_ACT_END_LEN    (16U)
#define DSP2_AXI_CTRL_REG_VSYNC_ACT_END_MSK    (((1U << DSP2_AXI_CTRL_REG_VSYNC_ACT_END_LEN) - 1) << DSP2_AXI_CTRL_REG_VSYNC_ACT_END_POS)
#define DSP2_AXI_CTRL_REG_VSYNC_ACT_END_UMSK   (~(((1U << DSP2_AXI_CTRL_REG_VSYNC_ACT_END_LEN) - 1) << DSP2_AXI_CTRL_REG_VSYNC_ACT_END_POS))
#define DSP2_AXI_CTRL_REG_VSYNC_ACT_START      DSP2_AXI_CTRL_REG_VSYNC_ACT_START
#define DSP2_AXI_CTRL_REG_VSYNC_ACT_START_POS  (16U)
#define DSP2_AXI_CTRL_REG_VSYNC_ACT_START_LEN  (16U)
#define DSP2_AXI_CTRL_REG_VSYNC_ACT_START_MSK  (((1U << DSP2_AXI_CTRL_REG_VSYNC_ACT_START_LEN) - 1) << DSP2_AXI_CTRL_REG_VSYNC_ACT_START_POS)
#define DSP2_AXI_CTRL_REG_VSYNC_ACT_START_UMSK (~(((1U << DSP2_AXI_CTRL_REG_VSYNC_ACT_START_LEN) - 1) << DSP2_AXI_CTRL_REG_VSYNC_ACT_START_POS))

/* 0x14 : nr_status */
#define DSP2_AXI_CTRL_NR_STATUS_OFFSET       (0x14)
#define DSP2_AXI_CTRL_STATUS_R_DRAIN         DSP2_AXI_CTRL_STATUS_R_DRAIN
#define DSP2_AXI_CTRL_STATUS_R_DRAIN_POS     (4U)
#define DSP2_AXI_CTRL_STATUS_R_DRAIN_LEN     (1U)
#define DSP2_AXI_CTRL_STATUS_R_DRAIN_MSK     (((1U << DSP2_AXI_CTRL_STATUS_R_DRAIN_LEN) - 1) << DSP2_AXI_CTRL_STATUS_R_DRAIN_POS)
#define DSP2_AXI_CTRL_STATUS_R_DRAIN_UMSK    (~(((1U << DSP2_AXI_CTRL_STATUS_R_DRAIN_LEN) - 1) << DSP2_AXI_CTRL_STATUS_R_DRAIN_POS))
#define DSP2_AXI_CTRL_STATUS_W_OVERFLOW      DSP2_AXI_CTRL_STATUS_W_OVERFLOW
#define DSP2_AXI_CTRL_STATUS_W_OVERFLOW_POS  (5U)
#define DSP2_AXI_CTRL_STATUS_W_OVERFLOW_LEN  (1U)
#define DSP2_AXI_CTRL_STATUS_W_OVERFLOW_MSK  (((1U << DSP2_AXI_CTRL_STATUS_W_OVERFLOW_LEN) - 1) << DSP2_AXI_CTRL_STATUS_W_OVERFLOW_POS)
#define DSP2_AXI_CTRL_STATUS_W_OVERFLOW_UMSK (~(((1U << DSP2_AXI_CTRL_STATUS_W_OVERFLOW_LEN) - 1) << DSP2_AXI_CTRL_STATUS_W_OVERFLOW_POS))
#define DSP2_AXI_CTRL_STATE_W_DVP_IDLE       DSP2_AXI_CTRL_STATE_W_DVP_IDLE
#define DSP2_AXI_CTRL_STATE_W_DVP_IDLE_POS   (8U)
#define DSP2_AXI_CTRL_STATE_W_DVP_IDLE_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_W_DVP_IDLE_MSK   (((1U << DSP2_AXI_CTRL_STATE_W_DVP_IDLE_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_DVP_IDLE_POS)
#define DSP2_AXI_CTRL_STATE_W_DVP_IDLE_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_W_DVP_IDLE_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_DVP_IDLE_POS))
#define DSP2_AXI_CTRL_STATE_W_DVP_WTST       DSP2_AXI_CTRL_STATE_W_DVP_WTST
#define DSP2_AXI_CTRL_STATE_W_DVP_WTST_POS   (9U)
#define DSP2_AXI_CTRL_STATE_W_DVP_WTST_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_W_DVP_WTST_MSK   (((1U << DSP2_AXI_CTRL_STATE_W_DVP_WTST_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_DVP_WTST_POS)
#define DSP2_AXI_CTRL_STATE_W_DVP_WTST_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_W_DVP_WTST_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_DVP_WTST_POS))
#define DSP2_AXI_CTRL_STATE_W_DVP_FUNC       DSP2_AXI_CTRL_STATE_W_DVP_FUNC
#define DSP2_AXI_CTRL_STATE_W_DVP_FUNC_POS   (10U)
#define DSP2_AXI_CTRL_STATE_W_DVP_FUNC_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_W_DVP_FUNC_MSK   (((1U << DSP2_AXI_CTRL_STATE_W_DVP_FUNC_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_DVP_FUNC_POS)
#define DSP2_AXI_CTRL_STATE_W_DVP_FUNC_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_W_DVP_FUNC_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_DVP_FUNC_POS))
#define DSP2_AXI_CTRL_STATE_W_DVP_FEND       DSP2_AXI_CTRL_STATE_W_DVP_FEND
#define DSP2_AXI_CTRL_STATE_W_DVP_FEND_POS   (11U)
#define DSP2_AXI_CTRL_STATE_W_DVP_FEND_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_W_DVP_FEND_MSK   (((1U << DSP2_AXI_CTRL_STATE_W_DVP_FEND_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_DVP_FEND_POS)
#define DSP2_AXI_CTRL_STATE_W_DVP_FEND_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_W_DVP_FEND_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_DVP_FEND_POS))
#define DSP2_AXI_CTRL_STATE_W_DVP_FLSH       DSP2_AXI_CTRL_STATE_W_DVP_FLSH
#define DSP2_AXI_CTRL_STATE_W_DVP_FLSH_POS   (12U)
#define DSP2_AXI_CTRL_STATE_W_DVP_FLSH_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_W_DVP_FLSH_MSK   (((1U << DSP2_AXI_CTRL_STATE_W_DVP_FLSH_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_DVP_FLSH_POS)
#define DSP2_AXI_CTRL_STATE_W_DVP_FLSH_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_W_DVP_FLSH_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_DVP_FLSH_POS))
#define DSP2_AXI_CTRL_STATE_W_BUS_IDLE       DSP2_AXI_CTRL_STATE_W_BUS_IDLE
#define DSP2_AXI_CTRL_STATE_W_BUS_IDLE_POS   (13U)
#define DSP2_AXI_CTRL_STATE_W_BUS_IDLE_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_W_BUS_IDLE_MSK   (((1U << DSP2_AXI_CTRL_STATE_W_BUS_IDLE_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_BUS_IDLE_POS)
#define DSP2_AXI_CTRL_STATE_W_BUS_IDLE_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_W_BUS_IDLE_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_BUS_IDLE_POS))
#define DSP2_AXI_CTRL_STATE_W_BUS_FUNC       DSP2_AXI_CTRL_STATE_W_BUS_FUNC
#define DSP2_AXI_CTRL_STATE_W_BUS_FUNC_POS   (14U)
#define DSP2_AXI_CTRL_STATE_W_BUS_FUNC_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_W_BUS_FUNC_MSK   (((1U << DSP2_AXI_CTRL_STATE_W_BUS_FUNC_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_BUS_FUNC_POS)
#define DSP2_AXI_CTRL_STATE_W_BUS_FUNC_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_W_BUS_FUNC_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_BUS_FUNC_POS))
#define DSP2_AXI_CTRL_STATE_W_BUS_FEND       DSP2_AXI_CTRL_STATE_W_BUS_FEND
#define DSP2_AXI_CTRL_STATE_W_BUS_FEND_POS   (15U)
#define DSP2_AXI_CTRL_STATE_W_BUS_FEND_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_W_BUS_FEND_MSK   (((1U << DSP2_AXI_CTRL_STATE_W_BUS_FEND_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_BUS_FEND_POS)
#define DSP2_AXI_CTRL_STATE_W_BUS_FEND_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_W_BUS_FEND_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_BUS_FEND_POS))
#define DSP2_AXI_CTRL_STATE_W_BUS_FLSH       DSP2_AXI_CTRL_STATE_W_BUS_FLSH
#define DSP2_AXI_CTRL_STATE_W_BUS_FLSH_POS   (16U)
#define DSP2_AXI_CTRL_STATE_W_BUS_FLSH_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_W_BUS_FLSH_MSK   (((1U << DSP2_AXI_CTRL_STATE_W_BUS_FLSH_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_BUS_FLSH_POS)
#define DSP2_AXI_CTRL_STATE_W_BUS_FLSH_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_W_BUS_FLSH_LEN) - 1) << DSP2_AXI_CTRL_STATE_W_BUS_FLSH_POS))
#define DSP2_AXI_CTRL_STATE_R_DVP_IDLE       DSP2_AXI_CTRL_STATE_R_DVP_IDLE
#define DSP2_AXI_CTRL_STATE_R_DVP_IDLE_POS   (17U)
#define DSP2_AXI_CTRL_STATE_R_DVP_IDLE_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_R_DVP_IDLE_MSK   (((1U << DSP2_AXI_CTRL_STATE_R_DVP_IDLE_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_DVP_IDLE_POS)
#define DSP2_AXI_CTRL_STATE_R_DVP_IDLE_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_R_DVP_IDLE_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_DVP_IDLE_POS))
#define DSP2_AXI_CTRL_STATE_R_DVP_WTST       DSP2_AXI_CTRL_STATE_R_DVP_WTST
#define DSP2_AXI_CTRL_STATE_R_DVP_WTST_POS   (18U)
#define DSP2_AXI_CTRL_STATE_R_DVP_WTST_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_R_DVP_WTST_MSK   (((1U << DSP2_AXI_CTRL_STATE_R_DVP_WTST_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_DVP_WTST_POS)
#define DSP2_AXI_CTRL_STATE_R_DVP_WTST_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_R_DVP_WTST_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_DVP_WTST_POS))
#define DSP2_AXI_CTRL_STATE_R_DVP_FUNC       DSP2_AXI_CTRL_STATE_R_DVP_FUNC
#define DSP2_AXI_CTRL_STATE_R_DVP_FUNC_POS   (19U)
#define DSP2_AXI_CTRL_STATE_R_DVP_FUNC_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_R_DVP_FUNC_MSK   (((1U << DSP2_AXI_CTRL_STATE_R_DVP_FUNC_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_DVP_FUNC_POS)
#define DSP2_AXI_CTRL_STATE_R_DVP_FUNC_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_R_DVP_FUNC_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_DVP_FUNC_POS))
#define DSP2_AXI_CTRL_STATE_R_DVP_FEND       DSP2_AXI_CTRL_STATE_R_DVP_FEND
#define DSP2_AXI_CTRL_STATE_R_DVP_FEND_POS   (20U)
#define DSP2_AXI_CTRL_STATE_R_DVP_FEND_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_R_DVP_FEND_MSK   (((1U << DSP2_AXI_CTRL_STATE_R_DVP_FEND_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_DVP_FEND_POS)
#define DSP2_AXI_CTRL_STATE_R_DVP_FEND_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_R_DVP_FEND_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_DVP_FEND_POS))
#define DSP2_AXI_CTRL_STATE_R_DVP_FLSH       DSP2_AXI_CTRL_STATE_R_DVP_FLSH
#define DSP2_AXI_CTRL_STATE_R_DVP_FLSH_POS   (21U)
#define DSP2_AXI_CTRL_STATE_R_DVP_FLSH_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_R_DVP_FLSH_MSK   (((1U << DSP2_AXI_CTRL_STATE_R_DVP_FLSH_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_DVP_FLSH_POS)
#define DSP2_AXI_CTRL_STATE_R_DVP_FLSH_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_R_DVP_FLSH_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_DVP_FLSH_POS))
#define DSP2_AXI_CTRL_STATE_R_BUS_IDLE       DSP2_AXI_CTRL_STATE_R_BUS_IDLE
#define DSP2_AXI_CTRL_STATE_R_BUS_IDLE_POS   (22U)
#define DSP2_AXI_CTRL_STATE_R_BUS_IDLE_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_R_BUS_IDLE_MSK   (((1U << DSP2_AXI_CTRL_STATE_R_BUS_IDLE_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_BUS_IDLE_POS)
#define DSP2_AXI_CTRL_STATE_R_BUS_IDLE_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_R_BUS_IDLE_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_BUS_IDLE_POS))
#define DSP2_AXI_CTRL_STATE_R_BUS_FUNC       DSP2_AXI_CTRL_STATE_R_BUS_FUNC
#define DSP2_AXI_CTRL_STATE_R_BUS_FUNC_POS   (23U)
#define DSP2_AXI_CTRL_STATE_R_BUS_FUNC_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_R_BUS_FUNC_MSK   (((1U << DSP2_AXI_CTRL_STATE_R_BUS_FUNC_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_BUS_FUNC_POS)
#define DSP2_AXI_CTRL_STATE_R_BUS_FUNC_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_R_BUS_FUNC_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_BUS_FUNC_POS))
#define DSP2_AXI_CTRL_STATE_R_BUS_FEND       DSP2_AXI_CTRL_STATE_R_BUS_FEND
#define DSP2_AXI_CTRL_STATE_R_BUS_FEND_POS   (24U)
#define DSP2_AXI_CTRL_STATE_R_BUS_FEND_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_R_BUS_FEND_MSK   (((1U << DSP2_AXI_CTRL_STATE_R_BUS_FEND_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_BUS_FEND_POS)
#define DSP2_AXI_CTRL_STATE_R_BUS_FEND_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_R_BUS_FEND_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_BUS_FEND_POS))
#define DSP2_AXI_CTRL_STATE_R_BUS_FLSH       DSP2_AXI_CTRL_STATE_R_BUS_FLSH
#define DSP2_AXI_CTRL_STATE_R_BUS_FLSH_POS   (25U)
#define DSP2_AXI_CTRL_STATE_R_BUS_FLSH_LEN   (1U)
#define DSP2_AXI_CTRL_STATE_R_BUS_FLSH_MSK   (((1U << DSP2_AXI_CTRL_STATE_R_BUS_FLSH_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_BUS_FLSH_POS)
#define DSP2_AXI_CTRL_STATE_R_BUS_FLSH_UMSK  (~(((1U << DSP2_AXI_CTRL_STATE_R_BUS_FLSH_LEN) - 1) << DSP2_AXI_CTRL_STATE_R_BUS_FLSH_POS))
#define DSP2_AXI_CTRL_AXI_R_IDLE             DSP2_AXI_CTRL_AXI_R_IDLE
#define DSP2_AXI_CTRL_AXI_R_IDLE_POS         (26U)
#define DSP2_AXI_CTRL_AXI_R_IDLE_LEN         (1U)
#define DSP2_AXI_CTRL_AXI_R_IDLE_MSK         (((1U << DSP2_AXI_CTRL_AXI_R_IDLE_LEN) - 1) << DSP2_AXI_CTRL_AXI_R_IDLE_POS)
#define DSP2_AXI_CTRL_AXI_R_IDLE_UMSK        (~(((1U << DSP2_AXI_CTRL_AXI_R_IDLE_LEN) - 1) << DSP2_AXI_CTRL_AXI_R_IDLE_POS))
#define DSP2_AXI_CTRL_AXI_W_IDLE             DSP2_AXI_CTRL_AXI_W_IDLE
#define DSP2_AXI_CTRL_AXI_W_IDLE_POS         (27U)
#define DSP2_AXI_CTRL_AXI_W_IDLE_LEN         (1U)
#define DSP2_AXI_CTRL_AXI_W_IDLE_MSK         (((1U << DSP2_AXI_CTRL_AXI_W_IDLE_LEN) - 1) << DSP2_AXI_CTRL_AXI_W_IDLE_POS)
#define DSP2_AXI_CTRL_AXI_W_IDLE_UMSK        (~(((1U << DSP2_AXI_CTRL_AXI_W_IDLE_LEN) - 1) << DSP2_AXI_CTRL_AXI_W_IDLE_POS))

/* 0xFC : nr_RSVD */
#define DSP2_AXI_CTRL_NR_RSVD_OFFSET (0xFC)

struct dsp2_axi_ctrl_reg {
    /* 0x0 : nr_control */
    union {
        struct
        {
            uint32_t reg_enable       : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reg_drain_clr    : 1;  /* [    1],        w1p,        0x0 */
            uint32_t reg_overflow_clr : 1;  /* [    2],        w1p,        0x0 */
            uint32_t reserved_3       : 1;  /* [    3],       rsvd,        0x0 */
            uint32_t reg_xlen         : 3;  /* [ 6: 4],        r/w,        0x3 */
            uint32_t reserved_7       : 1;  /* [    7],       rsvd,        0x0 */
            uint32_t reg_qos_sw_mode  : 1;  /* [    8],        r/w,        0x0 */
            uint32_t reg_qos_sw       : 1;  /* [    9],        r/w,        0x0 */
            uint32_t reserved_10_31   : 22; /* [31:10],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } nr_control;

    /* 0x4 : nr_haddr_start_address */
    union {
        struct
        {
            uint32_t reg_addr_start : 32; /* [31: 0],        r/w, 0x70000000 */
        } BF;
        uint32_t WORD;
    } nr_haddr_start_address;

    /* 0x8 : nr_memory_burst_count */
    union {
        struct
        {
            uint32_t reg_burst_cnt : 32; /* [31: 0],        r/w,       0x80 */
        } BF;
        uint32_t WORD;
    } nr_memory_burst_count;

    /* 0xC : nr_hsync_control */
    union {
        struct
        {
            uint32_t reg_hsync_act_end   : 16; /* [15: 0],        r/w,     0xffff */
            uint32_t reg_hsync_act_start : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } nr_hsync_control;

    /* 0x10 : nr_vsync_control */
    union {
        struct
        {
            uint32_t reg_vsync_act_end   : 16; /* [15: 0],        r/w,     0xffff */
            uint32_t reg_vsync_act_start : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } nr_vsync_control;

    /* 0x14 : nr_status */
    union {
        struct
        {
            uint32_t reserved_0_3      : 4; /* [ 3: 0],       rsvd,        0x0 */
            uint32_t status_r_drain    : 1; /* [    4],          r,        0x0 */
            uint32_t status_w_overflow : 1; /* [    5],          r,        0x0 */
            uint32_t reserved_6_7      : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t state_w_dvp_idle  : 1; /* [    8],          r,        0x1 */
            uint32_t state_w_dvp_wtst  : 1; /* [    9],          r,        0x0 */
            uint32_t state_w_dvp_func  : 1; /* [   10],          r,        0x0 */
            uint32_t state_w_dvp_fend  : 1; /* [   11],          r,        0x0 */
            uint32_t state_w_dvp_flsh  : 1; /* [   12],          r,        0x0 */
            uint32_t state_w_bus_idle  : 1; /* [   13],          r,        0x1 */
            uint32_t state_w_bus_func  : 1; /* [   14],          r,        0x0 */
            uint32_t state_w_bus_fend  : 1; /* [   15],          r,        0x0 */
            uint32_t state_w_bus_flsh  : 1; /* [   16],          r,        0x0 */
            uint32_t state_r_dvp_idle  : 1; /* [   17],          r,        0x1 */
            uint32_t state_r_dvp_wtst  : 1; /* [   18],          r,        0x0 */
            uint32_t state_r_dvp_func  : 1; /* [   19],          r,        0x0 */
            uint32_t state_r_dvp_fend  : 1; /* [   20],          r,        0x0 */
            uint32_t state_r_dvp_flsh  : 1; /* [   21],          r,        0x0 */
            uint32_t state_r_bus_idle  : 1; /* [   22],          r,        0x1 */
            uint32_t state_r_bus_func  : 1; /* [   23],          r,        0x0 */
            uint32_t state_r_bus_fend  : 1; /* [   24],          r,        0x0 */
            uint32_t state_r_bus_flsh  : 1; /* [   25],          r,        0x0 */
            uint32_t axi_r_idle        : 1; /* [   26],          r,        0x0 */
            uint32_t axi_w_idle        : 1; /* [   27],          r,        0x0 */
            uint32_t reserved_28_31    : 4; /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } nr_status;

    /* 0x18  reserved */
    uint8_t RESERVED0x18[228];

    /* 0xFC : nr_RSVD */
    union {
        struct
        {
            uint32_t RESERVED_31_0 : 32; /* [31: 0],       rsvd, 0xffff0000 */
        } BF;
        uint32_t WORD;
    } nr_RSVD;
};

typedef volatile struct dsp2_axi_ctrl_reg dsp2_axi_ctrl_reg_t;

#endif /* __DSP2_AXI_CTRL_REG_H__ */
