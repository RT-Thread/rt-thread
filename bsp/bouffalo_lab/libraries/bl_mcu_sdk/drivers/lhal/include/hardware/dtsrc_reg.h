/**
  ******************************************************************************
  * @file    dtsrc_reg.h
  * @version V1.0
  * @date    2022-12-15
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
#ifndef  __HARDWARE_DTSRC_H__
#define  __HARDWARE_DTSRC_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define DTSRC_CONFIG_OFFSET                                     (0x0)/* config */
#define DTSRC_FRAME_SIZE_H_OFFSET                               (0x4)/* frame_size_h */
#define DTSRC_FRAME_SIZE_V_OFFSET                               (0x8)/* frame_size_v */
#define DTSRC_FRAME_SIZE_CEA_861_OFFSET                         (0xC)/* frame_size_cea_861 */
#define DTSRC_PIX_DATA_RANGE_OFFSET                             (0x10)/* pix_data_range */
#define DTSRC_PIX_DATA_STEP_OFFSET                              (0x14)/* pix_data_step */
#define DTSRC_AXI2DVP_SETTING_OFFSET                            (0x20)/* axi2dvp_setting */
#define DTSRC_AXI2DVP_START_ADDR_BY_OFFSET                      (0x24)/* axi2dvp_start_addr_by */
#define DTSRC_AXI2DVP_BURST_CNT_OFFSET                          (0x28)/* axi2dvp_burst_cnt */
#define DTSRC_AXI2DVP_STATUS_OFFSET                             (0x2C)/* axi2dvp_status */
#define DTSRC_AXI2DVP_SWAP_ADDR_BY_OFFSET                       (0x30)/* axi2dvp_swap_addr_by */
#define DTSRC_AXI2DVP_PREFETCH_OFFSET                           (0x34)/* axi2dvp_prefetch */
#define DTSRC_SNSR2DVP_WAIT_POS_OFFSET                          (0x38)/* snsr2dvp_wait_pos */
#define DTSRC_AXI2DVP_START_ADDR_UV_OFFSET                      (0x40)/* axi2dvp_start_addr_uv */
#define DTSRC_AXI2DVP_SWAP_ADDR_UV_OFFSET                       (0x44)/* axi2dvp_swap_addr_uv */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : config */
#define DTSRC_CR_ENABLE                                         (1<<0U)
#define DTSRC_CR_AXI_EN                                         (1<<1U)
#define DTSRC_CR_MODE_CEA_861                                   (1<<2U)
#define DTSRC_CR_SNSR_EN                                        (1<<3U)
#define DTSRC_CR_SNSR_HSYNC_INV                                 (1<<4U)
#define DTSRC_CR_SNSR_VSYNC_INV                                 (1<<5U)
#define DTSRC_CR_AXI_SWAP_MODE                                  (1<<7U)
#define DTSRC_CR_AXI_SWAP_IDX_SEL_SHIFT                         (8U)
#define DTSRC_CR_AXI_SWAP_IDX_SEL_MASK                          (0xf<<DTSRC_CR_AXI_SWAP_IDX_SEL_SHIFT)
#define DTSRC_CR_AXI_SWAP_IDX_SWM                               (1<<12U)
#define DTSRC_CR_AXI_SWAP_IDX_SWV                               (1<<13U)
#define DTSRC_CR_AXI_DVP_DATA_MODE_SHIFT                        (16U)
#define DTSRC_CR_AXI_DVP_DATA_MODE_MASK                         (0x7<<DTSRC_CR_AXI_DVP_DATA_MODE_SHIFT)
#define DTSRC_CR_AXI_B0_SEL_SHIFT                               (20U)
#define DTSRC_CR_AXI_B0_SEL_MASK                                (0x3<<DTSRC_CR_AXI_B0_SEL_SHIFT)
#define DTSRC_CR_AXI_B1_SEL_SHIFT                               (22U)
#define DTSRC_CR_AXI_B1_SEL_MASK                                (0x3<<DTSRC_CR_AXI_B1_SEL_SHIFT)
#define DTSRC_CR_AXI_B2_SEL_SHIFT                               (24U)
#define DTSRC_CR_AXI_B2_SEL_MASK                                (0x3<<DTSRC_CR_AXI_B2_SEL_SHIFT)

/* 0x4 : frame_size_h */
#define DTSRC_CR_TOTAL_H_SHIFT                                  (0U)
#define DTSRC_CR_TOTAL_H_MASK                                   (0xfff<<DTSRC_CR_TOTAL_H_SHIFT)
#define DTSRC_CR_BLANK_H_SHIFT                                  (16U)
#define DTSRC_CR_BLANK_H_MASK                                   (0xfff<<DTSRC_CR_BLANK_H_SHIFT)

/* 0x8 : frame_size_v */
#define DTSRC_CR_TOTAL_V_SHIFT                                  (0U)
#define DTSRC_CR_TOTAL_V_MASK                                   (0xfff<<DTSRC_CR_TOTAL_V_SHIFT)
#define DTSRC_CR_BLANK_V_SHIFT                                  (16U)
#define DTSRC_CR_BLANK_V_MASK                                   (0xfff<<DTSRC_CR_BLANK_V_SHIFT)

/* 0xC : frame_size_cea_861 */
#define DTSRC_CR_H_DURATION_SHIFT                               (0U)
#define DTSRC_CR_H_DURATION_MASK                                (0xff<<DTSRC_CR_H_DURATION_SHIFT)
#define DTSRC_CR_H_PLACEMENT_SHIFT                              (8U)
#define DTSRC_CR_H_PLACEMENT_MASK                               (0xff<<DTSRC_CR_H_PLACEMENT_SHIFT)
#define DTSRC_CR_V_DURATION_SHIFT                               (16U)
#define DTSRC_CR_V_DURATION_MASK                                (0xff<<DTSRC_CR_V_DURATION_SHIFT)
#define DTSRC_CR_V_PLACEMENT_SHIFT                              (24U)
#define DTSRC_CR_V_PLACEMENT_MASK                               (0xff<<DTSRC_CR_V_PLACEMENT_SHIFT)

/* 0x10 : pix_data_range */
#define DTSRC_CR_DATA_MIN_SHIFT                                 (0U)
#define DTSRC_CR_DATA_MIN_MASK                                  (0xffff<<DTSRC_CR_DATA_MIN_SHIFT)
#define DTSRC_CR_DATA_MAX_SHIFT                                 (16U)
#define DTSRC_CR_DATA_MAX_MASK                                  (0xffff<<DTSRC_CR_DATA_MAX_SHIFT)

/* 0x14 : pix_data_step */
#define DTSRC_CR_DATA_STEP_SHIFT                                (0U)
#define DTSRC_CR_DATA_STEP_MASK                                 (0xff<<DTSRC_CR_DATA_STEP_SHIFT)

/* 0x20 : axi2dvp_setting */
#define DTSRC_CR_AXI_XLEN_SHIFT                                 (0U)
#define DTSRC_CR_AXI_XLEN_MASK                                  (0x7<<DTSRC_CR_AXI_XLEN_SHIFT)
#define DTSRC_CR_AXI_DRAIN_ERR_CLR                              (1<<4U)
#define DTSRC_CR_AXI_420_MODE                                   (1<<8U)
#define DTSRC_CR_AXI_420_UD_SEL                                 (1<<9U)
#define DTSRC_CR_QOS_SW_MODE                                    (1<<10U)
#define DTSRC_CR_QOS_SW                                         (1<<11U)

/* 0x24 : axi2dvp_start_addr_by */
#define DTSRC_CR_AXI_ADDR_START_BY_SHIFT                        (0U)
#define DTSRC_CR_AXI_ADDR_START_BY_MASK                         (0xffffffff<<DTSRC_CR_AXI_ADDR_START_BY_SHIFT)

/* 0x28 : axi2dvp_burst_cnt */
#define DTSRC_CR_AXI_FRAME_BC_SHIFT                             (0U)
#define DTSRC_CR_AXI_FRAME_BC_MASK                              (0xffffffff<<DTSRC_CR_AXI_FRAME_BC_SHIFT)

/* 0x2C : axi2dvp_status */
#define DTSRC_ST_AXI_FIFO_CNT_BY_SHIFT                          (0U)
#define DTSRC_ST_AXI_FIFO_CNT_BY_MASK                           (0x7f<<DTSRC_ST_AXI_FIFO_CNT_BY_SHIFT)
#define DTSRC_ST_AXI_DRAIN_ERROR_BY                             (1<<7U)
#define DTSRC_ST_AXI_STATE_IDLE_BY                              (1<<8U)
#define DTSRC_ST_AXI_STATE_FUNC_BY                              (1<<9U)
#define DTSRC_ST_AXI_STATE_FLSH_BY                              (1<<10U)
#define DTSRC_ST_AXI_FIFO_CNT_UV_SHIFT                          (16U)
#define DTSRC_ST_AXI_FIFO_CNT_UV_MASK                           (0x7f<<DTSRC_ST_AXI_FIFO_CNT_UV_SHIFT)
#define DTSRC_ST_AXI_DRAIN_ERROR_UV                             (1<<23U)
#define DTSRC_ST_AXI_STATE_IDLE_UV                              (1<<24U)
#define DTSRC_ST_AXI_STATE_FUNC_UV                              (1<<25U)
#define DTSRC_ST_AXI_STATE_FLSH_UV                              (1<<26U)

/* 0x30 : axi2dvp_swap_addr_by */
#define DTSRC_CR_AXI_ADDR_SWAP_BY_SHIFT                         (0U)
#define DTSRC_CR_AXI_ADDR_SWAP_BY_MASK                          (0xffffffff<<DTSRC_CR_AXI_ADDR_SWAP_BY_SHIFT)

/* 0x34 : axi2dvp_prefetch */
#define DTSRC_CR_PREFETCH_V_SHIFT                               (0U)
#define DTSRC_CR_PREFETCH_V_MASK                                (0xfff<<DTSRC_CR_PREFETCH_V_SHIFT)

/* 0x38 : snsr2dvp_wait_pos */
#define DTSRC_CR_SNSR_FIFO_TH_SHIFT                             (0U)
#define DTSRC_CR_SNSR_FIFO_TH_MASK                              (0x7ff<<DTSRC_CR_SNSR_FIFO_TH_SHIFT)

/* 0x40 : axi2dvp_start_addr_uv */
#define DTSRC_CR_AXI_ADDR_START_UV_SHIFT                        (0U)
#define DTSRC_CR_AXI_ADDR_START_UV_MASK                         (0xffffffff<<DTSRC_CR_AXI_ADDR_START_UV_SHIFT)

/* 0x44 : axi2dvp_swap_addr_uv */
#define DTSRC_CR_AXI_ADDR_SWAP_UV_SHIFT                         (0U)
#define DTSRC_CR_AXI_ADDR_SWAP_UV_MASK                          (0xffffffff<<DTSRC_CR_AXI_ADDR_SWAP_UV_SHIFT)


#endif  /* __HARDWARE_DTSRC_H__ */
