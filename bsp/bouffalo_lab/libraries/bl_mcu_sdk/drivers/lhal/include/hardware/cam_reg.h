/**
  ******************************************************************************
  * @file    cam_reg.h
  * @version V1.0
  * @date    2022-11-30
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
#ifndef  __HARDWARE_CAM_H__
#define  __HARDWARE_CAM_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define CAM_DVP2AXI_CONFIGUE_OFFSET     (0x0)/* dvp2axi_configue */
#define CAM_DVP2AXI_ADDR_START_OFFSET   (0x4)/* dvp2axi_addr_start */
#define CAM_DVP2AXI_MEM_BCNT_OFFSET     (0x8)/* dvp2axi_mem_bcnt */
#define CAM_DVP2AXI_HSYNC_CROP_OFFSET   (0x30)/* dvp2axi_hsync_crop */
#define CAM_DVP2AXI_VSYNC_CROP_OFFSET   (0x34)/* dvp2axi_vsync_crop */
#define CAM_DVP2AXI_FRAM_EXM_OFFSET     (0x38)/* dvp2axi_fram_exm */
#define CAM_FRAME_START_ADDR0_OFFSET    (0x40)/* frame_start_addr0 */
#define CAM_FRAME_START_ADDR1_OFFSET    (0x48)/* frame_start_addr1 */
#define CAM_FRAME_START_ADDR2_OFFSET    (0x50)/* frame_start_addr2 */
#define CAM_FRAME_START_ADDR3_OFFSET    (0x58)/* frame_start_addr3 */
#if defined(BL702)
#define CAM_DVP2AXI_FRAME_BCNT_0_OFFSET (0xC)/* dvp2axi_frame_bcnt_0 */
#define CAM_DVP2AXI_ADDR_START_1_OFFSET (0x10)/* dvp2axi_addr_start_1 */
#define CAM_DVP2AXI_MEM_BCNT_1_OFFSET   (0x14)/* dvp2axi_mem_bcnt_1 */
#define CAM_DVP2AXI_FRAME_BCNT_1_OFFSET (0x18)/* dvp2axi_frame_bcnt_1 */
#define CAM_DVP_STATUS_AND_ERROR_OFFSET (0x1C)/* dvp_status_and_error */
#define CAM_DVP_FRAME_FIFO_POP_OFFSET   (0x20)/* dvp_frame_fifo_pop */
#define CAM_SNSR_CONTROL_OFFSET         (0x24)/* snsr_control */
#define CAM_INT_CONTROL_OFFSET          (0x28)/* int_control */
#define CAM_FRAME_BYTE_CNT0_0_OFFSET    (0x44)/* frame_byte_cnt0_0 */
#define CAM_FRAME_BYTE_CNT0_1_OFFSET    (0x4C)/* frame_byte_cnt0_1 */
#define CAM_FRAME_BYTE_CNT0_2_OFFSET    (0x54)/* frame_byte_cnt0_2 */
#define CAM_FRAME_BYTE_CNT0_3_OFFSET    (0x5C)/* frame_byte_cnt0_3 */
#define CAM_FRAME_START_ADDR0_4_OFFSET  (0x60)/* frame_start_addr0_4 */
#define CAM_FRAME_BYTE_CNT0_4_OFFSET    (0x64)/* frame_byte_cnt0_4 */
#define CAM_FRAME_START_ADDR0_5_OFFSET  (0x68)/* frame_start_addr0_5 */
#define CAM_FRAME_BYTE_CNT0_5_OFFSET    (0x6C)/* frame_byte_cnt0_5 */
#define CAM_FRAME_START_ADDR0_6_OFFSET  (0x70)/* frame_start_addr0_6 */
#define CAM_FRAME_BYTE_CNT0_6_OFFSET    (0x74)/* frame_byte_cnt0_6 */
#define CAM_FRAME_START_ADDR0_7_OFFSET  (0x78)/* frame_start_addr0_7 */
#define CAM_FRAME_BYTE_CNT0_7_OFFSET    (0x7C)/* frame_byte_cnt0_7 */
#define CAM_FRAME_START_ADDR1_0_OFFSET  (0x80)/* frame_start_addr1_0 */
#define CAM_FRAME_BYTE_CNT1_0_OFFSET    (0x84)/* frame_byte_cnt1_0 */
#define CAM_FRAME_START_ADDR1_1_OFFSET  (0x88)/* frame_start_addr1_1 */
#define CAM_FRAME_BYTE_CNT1_1_OFFSET    (0x8C)/* frame_byte_cnt1_1 */
#define CAM_FRAME_START_ADDR1_2_OFFSET  (0x90)/* frame_start_addr1_2 */
#define CAM_FRAME_BYTE_CNT1_2_OFFSET    (0x94)/* frame_byte_cnt1_2 */
#define CAM_FRAME_START_ADDR1_3_OFFSET  (0x98)/* frame_start_addr1_3 */
#define CAM_FRAME_BYTE_CNT1_3_OFFSET    (0x9C)/* frame_byte_cnt1_3 */
#define CAM_FRAME_START_ADDR1_4_OFFSET  (0xA0)/* frame_start_addr1_4 */
#define CAM_FRAME_BYTE_CNT1_4_OFFSET    (0xA4)/* frame_byte_cnt1_4 */
#define CAM_FRAME_START_ADDR1_5_OFFSET  (0xA8)/* frame_start_addr1_5 */
#define CAM_FRAME_BYTE_CNT1_5_OFFSET    (0xAC)/* frame_byte_cnt1_5 */
#define CAM_FRAME_START_ADDR1_6_OFFSET  (0xB0)/* frame_start_addr1_6 */
#define CAM_FRAME_BYTE_CNT1_6_OFFSET    (0xB4)/* frame_byte_cnt1_6 */
#define CAM_FRAME_START_ADDR1_7_OFFSET  (0xB8)/* frame_start_addr1_7 */
#define CAM_FRAME_BYTE_CNT1_7_OFFSET    (0xBC)/* frame_byte_cnt1_7 */
#define CAM_DVP_DEBUG_OFFSET            (0xFF0)/* dvp_debug */
#define CAM_DVP_DUMMY_REG_OFFSET        (0xFFC)/* dvp_dummy_reg */
#else
#define CAM_DVP_STATUS_AND_ERROR_OFFSET (0xC)/* dvp_status_and_error */
#define CAM_DVP2AXI_FRAME_BCNT_OFFSET   (0x10)/* dvp2axi_frame_bcnt */
#define CAM_DVP_FRAME_FIFO_POP_OFFSET   (0x14)/* dvp_frame_fifo_pop */
#define CAM_DVP2AXI_FRAME_VLD_OFFSET    (0x18)/* dvp2axi_frame_vld */
#define CAM_DVP2AXI_FRAME_PERIOD_OFFSET (0x1C)/* dvp2axi_frame_period */
#define CAM_DVP2AXI_MISC_OFFSET         (0x20)/* dvp2axi_misc */
#define CAM_FRAME_ID_STS01_OFFSET       (0x60)/* frame_id_sts01 */
#define CAM_FRAME_ID_STS23_OFFSET       (0x64)/* frame_id_sts23 */
#define CAM_DVP_DEBUG_OFFSET            (0xF0)/* dvp_debug */
#define CAM_DVP_DUMMY_REG_OFFSET        (0xFC)/* dvp_dummy_reg */
#endif

/* Register Bitfield definitions *****************************************************/

/* 0x0 : dvp2axi_configue */
#define CAM_REG_DVP_ENABLE           (1<<0U)
#define CAM_REG_SW_MODE              (1<<1U)
#define CAM_REG_FRAM_VLD_POL         (1<<2U)
#define CAM_REG_LINE_VLD_POL         (1<<3U)
#define CAM_REG_XLEN_SHIFT           (4U)
#if defined(BL702)
#define CAM_REG_XLEN_MASK            (0x3<<CAM_REG_XLEN_SHIFT)
#else
#define CAM_REG_XLEN_MASK            (0x7<<CAM_REG_XLEN_SHIFT)
#endif
#define CAM_REG_DVP_MODE_SHIFT       (8U)
#define CAM_REG_DVP_MODE_MASK        (0x7<<CAM_REG_DVP_MODE_SHIFT)
#define CAM_REG_HW_MODE_FWRAP        (1<<11U)
#define CAM_REG_DROP_EN              (1<<12U)
#define CAM_REG_DROP_EVEN            (1<<13U)
#if defined(BL702)
#define CAM_REG_SUBSAMPLE_EN         (1<<14U)
#define CAM_REG_SUBSAMPLE_EVEN       (1<<15U)
#define CAM_REG_INTERLV_MODE         (1<<16U)
#else
#define CAM_REG_QOS_SW_MODE          (1<<14U)
#define CAM_REG_QOS_SW               (1<<15U)
#define CAM_REG_DVP_DATA_MODE_SHIFT  (16U)
#define CAM_REG_DVP_DATA_MODE_MASK   (0x7<<CAM_REG_DVP_DATA_MODE_SHIFT)
#define CAM_REG_DVP_DATA_BSEL        (1<<19U)
#endif
#define CAM_REG_DVP_PIX_CLK_CG       (1<<20U)
#if !defined(BL702)
#define CAM_REG_V_SUBSAMPLE_EN       (1<<22U)
#define CAM_REG_V_SUBSAMPLE_POL      (1<<23U)
#endif
#define CAM_REG_DVP_WAIT_CYCLE_SHIFT (24U)
#define CAM_REG_DVP_WAIT_CYCLE_MASK  (0xff<<CAM_REG_DVP_WAIT_CYCLE_SHIFT)

/* 0x4 : dvp2axi_addr_start */
#define CAM_REG_ADDR_START_SHIFT (0U)
#define CAM_REG_ADDR_START_MASK  (0xffffffff<<CAM_REG_ADDR_START_SHIFT)

/* 0x8 : dvp2axi_mem_bcnt */
#define CAM_REG_MEM_BURST_CNT_SHIFT (0U)
#define CAM_REG_MEM_BURST_CNT_MASK  (0xffffffff<<CAM_REG_MEM_BURST_CNT_SHIFT)

#if defined(BL702)
/* 0xC : dvp2ahb_frame_bcnt_0 */
#define CAM_REG_FRAME_BURST_CNT_0_SHIFT (0U)
#define CAM_REG_FRAME_BURST_CNT_0_MASK  (0xffffffff<<CAM_REG_FRAME_BURST_CNT_0_SHIFT)

/* 0x10 : dvp2ahb_addr_start_1 */
#define CAM_REG_ADDR_START_1_SHIFT (0U)
#define CAM_REG_ADDR_START_1_MASK  (0xffffffff<<CAM_REG_ADDR_START_1_SHIFT)

/* 0x14 : dvp2ahb_mem_bcnt_1 */
#define CAM_REG_MEM_BURST_CNT_1_SHIFT (0U)
#define CAM_REG_MEM_BURST_CNT_1_MASK  (0xffffffff<<CAM_REG_MEM_BURST_CNT_1_SHIFT)

/* 0x18 : dvp2ahb_frame_bcnt_1 */
#define CAM_REG_FRAME_BURST_CNT_1_SHIFT (0U)
#define CAM_REG_FRAME_BURST_CNT_1_MASK  (0xffffffff<<CAM_REG_FRAME_BURST_CNT_1_SHIFT)

/* 0x1C : dvp_status_and_error */
#define CAM_STS_NORMAL_INT                                      (1<<0U)
#define CAM_STS_NORMAL_INT_1                                    (1<<1U)
#define CAM_STS_MEM_INT                                         (1<<2U)
#define CAM_STS_MEM_INT_1                                       (1<<3U)
#define CAM_STS_FRAME_INT                                       (1<<4U)
#define CAM_STS_FRAME_INT_1                                     (1<<5U)
#define CAM_STS_FIFO_INT                                        (1<<6U)
#define CAM_STS_FIFO_INT_1                                      (1<<7U)
#define CAM_STS_HCNT_INT                                        (1<<8U)
#define CAM_STS_VCNT_INT                                        (1<<9U)
#define CAM_AHB_IDLE_0                                          (1<<16U)
#define CAM_AHB_IDLE_1                                          (1<<17U)
#define CAM_ST_DVP_IDLE                                         (1<<19U)
#define CAM_FRAME_VALID_CNT_SHIFT                               (20U)
#define CAM_FRAME_VALID_CNT_MASK                                (0xf<<CAM_FRAME_VALID_CNT_SHIFT)
#define CAM_FRAME_VALID_CNT_1_SHIFT                             (24U)
#define CAM_FRAME_VALID_CNT_1_MASK                              (0xf<<CAM_FRAME_VALID_CNT_1_SHIFT)
#define CAM_ST_BUS_IDLE                                         (1<<28U)
#define CAM_ST_BUS_FUNC                                         (1<<29U)
#define CAM_ST_BUS_WAIT                                         (1<<30U)
#define CAM_ST_BUS_FLSH                                         (1<<31U)
#else
/* 0xC : dvp_status_and_error */
#define CAM_REG_FRAME_CNT_TRGR_INT_SHIFT (0U)
#define CAM_REG_FRAME_CNT_TRGR_INT_MASK  (0x1f<<CAM_REG_FRAME_CNT_TRGR_INT_SHIFT)
#define CAM_REG_INT_HCNT_EN              (1<<6U)
#define CAM_REG_INT_VCNT_EN              (1<<7U)
#define CAM_REG_INT_NORMAL_EN            (1<<8U)
#define CAM_REG_INT_MEM_EN               (1<<9U)
#define CAM_REG_INT_FRAME_EN             (1<<10U)
#define CAM_REG_INT_FIFO_EN              (1<<11U)
#define CAM_STS_NORMAL_INT               (1<<12U)
#define CAM_STS_MEM_INT                  (1<<13U)
#define CAM_STS_FRAME_INT                (1<<14U)
#define CAM_STS_FIFO_INT                 (1<<15U)
#define CAM_FRAME_VALID_CNT_SHIFT        (16U)
#define CAM_FRAME_VALID_CNT_MASK         (0x1f<<CAM_FRAME_VALID_CNT_SHIFT)
#define CAM_STS_HCNT_INT                 (1<<21U)
#define CAM_STS_VCNT_INT                 (1<<22U)
#define CAM_ST_BUS_IDLE                  (1<<24U)
#define CAM_ST_BUS_FUNC                  (1<<25U)
#define CAM_ST_BUS_WAIT                  (1<<26U)
#define CAM_ST_BUS_FLSH                  (1<<27U)
#define CAM_AXI_IDLE                     (1<<28U)
#define CAM_ST_DVP_IDLE                  (1<<29U)

/* 0x10 : dvp2axi_frame_bcnt */
#define CAM_REG_FRAME_BYTE_CNT_SHIFT (0U)
#define CAM_REG_FRAME_BYTE_CNT_MASK  (0xffffffff<<CAM_REG_FRAME_BYTE_CNT_SHIFT)
#endif

/* 0x14 : dvp_frame_fifo_pop */
#define CAM_RFIFO_POP            (1<<0U)
#if defined(BL702)
#define CAM_RFIFO_POP_1          (1<<1U)
#endif
#define CAM_REG_INT_NORMAL_CLR   (1<<4U)
#define CAM_REG_INT_MEM_CLR      (1<<5U)
#define CAM_REG_INT_FRAME_CLR    (1<<6U)
#define CAM_REG_INT_FIFO_CLR     (1<<7U)
#define CAM_REG_INT_HCNT_CLR     (1<<8U)
#define CAM_REG_INT_VCNT_CLR     (1<<9U)
#if defined(BL702)
#define CAM_REG_INT_NORMAL_CLR_1 (1<<16U)
#define CAM_REG_INT_MEM_CLR_1    (1<<17U)
#define CAM_REG_INT_FRAME_CLR_1  (1<<18U)
#define CAM_REG_INT_FIFO_CLR_1   (1<<19U)
#endif

#if defined(BL702)
/* 0x24 : snsr_control */
#define CAM_REG_CAM_RST  (1<<0U)
#define CAM_REG_CAM_PWDN (1<<1U)

/* 0x28 : int_control */
#define CAM_REG_INT_NORMAL_EN            (1<<0U)
#define CAM_REG_INT_NORMAL_1_EN          (1<<1U)
#define CAM_REG_INT_MEM_EN               (1<<2U)
#define CAM_REG_INT_FRAME_EN             (1<<3U)
#define CAM_REG_INT_FIFO_EN              (1<<4U)
#define CAM_REG_INT_HCNT_EN              (1<<5U)
#define CAM_REG_INT_VCNT_EN              (1<<6U)
#define CAM_REG_FRAME_CNT_TRGR_INT_SHIFT (28U)
#define CAM_REG_FRAME_CNT_TRGR_INT_MASK  (0xf<<CAM_REG_FRAME_CNT_TRGR_INT_SHIFT)
#else
/* 0x18 : dvp2axi_frame_vld */
#define CAM_REG_FRAME_N_VLD_SHIFT (0U)
#define CAM_REG_FRAME_N_VLD_MASK  (0xffffffff<<CAM_REG_FRAME_N_VLD_SHIFT)

/* 0x1C : dvp2axi_frame_period */
#define CAM_REG_FRAME_PERIOD_SHIFT (0U)
#define CAM_REG_FRAME_PERIOD_MASK  (0x1f<<CAM_REG_FRAME_PERIOD_SHIFT)

/* 0x20 : dvp2axi_misc */
#define CAM_REG_ALPHA_SHIFT      (0U)
#define CAM_REG_ALPHA_MASK       (0xff<<CAM_REG_ALPHA_SHIFT)
#define CAM_REG_FORMAT_565_SHIFT (8U)
#define CAM_REG_FORMAT_565_MASK  (0x7<<CAM_REG_FORMAT_565_SHIFT)
#endif

/* 0x30 : dvp2axi_hsync_crop */
#define CAM_REG_HSYNC_ACT_END_SHIFT   (0U)
#define CAM_REG_HSYNC_ACT_END_MASK    (0xffff<<CAM_REG_HSYNC_ACT_END_SHIFT)
#define CAM_REG_HSYNC_ACT_START_SHIFT (16U)
#define CAM_REG_HSYNC_ACT_START_MASK  (0xffff<<CAM_REG_HSYNC_ACT_START_SHIFT)

/* 0x34 : dvp2axi_vsync_crop */
#define CAM_REG_VSYNC_ACT_END_SHIFT   (0U)
#define CAM_REG_VSYNC_ACT_END_MASK    (0xffff<<CAM_REG_VSYNC_ACT_END_SHIFT)
#define CAM_REG_VSYNC_ACT_START_SHIFT (16U)
#define CAM_REG_VSYNC_ACT_START_MASK  (0xffff<<CAM_REG_VSYNC_ACT_START_SHIFT)

/* 0x38 : dvp2axi_fram_exm */
#define CAM_REG_TOTAL_HCNT_SHIFT (0U)
#define CAM_REG_TOTAL_HCNT_MASK  (0xffff<<CAM_REG_TOTAL_HCNT_SHIFT)
#define CAM_REG_TOTAL_VCNT_SHIFT (16U)
#define CAM_REG_TOTAL_VCNT_MASK  (0xffff<<CAM_REG_TOTAL_VCNT_SHIFT)

/* 0x40 : frame_start_addr0 */
#define CAM_FRAME_START_ADDR_0_SHIFT (0U)
#define CAM_FRAME_START_ADDR_0_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_0_SHIFT)

#if defined(BL702)
/* 0x44 : frame_byte_cnt0_0 */
#define CAM_FRAME_BYTE_CNT_0_0_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_0_0_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_0_0_SHIFT)
#endif

/* 0x48 : frame_start_addr1 */
#define CAM_FRAME_START_ADDR_1_SHIFT (0U)
#define CAM_FRAME_START_ADDR_1_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_1_SHIFT)

#if defined(BL702)
/* 0x4C : frame_byte_cnt0_1 */
#define CAM_FRAME_BYTE_CNT_0_1_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_0_1_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_0_1_SHIFT)
#endif

/* 0x50 : frame_start_addr2 */
#define CAM_FRAME_START_ADDR_2_SHIFT (0U)
#define CAM_FRAME_START_ADDR_2_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_2_SHIFT)

#if defined(BL702)
/* 0x54 : frame_byte_cnt0_2 */
#define CAM_FRAME_BYTE_CNT_0_2_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_0_2_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_0_2_SHIFT)
#endif

/* 0x58 : frame_start_addr3 */
#define CAM_FRAME_START_ADDR_3_SHIFT (0U)
#define CAM_FRAME_START_ADDR_3_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_3_SHIFT)

#if defined(BL702)
/* 0x5C : frame_byte_cnt0_3 */
#define CAM_FRAME_BYTE_CNT_0_3_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_0_3_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_0_3_SHIFT)

/* 0x60 : frame_start_addr0_4 */
#define CAM_FRAME_START_ADDR_0_4_SHIFT (0U)
#define CAM_FRAME_START_ADDR_0_4_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_0_4_SHIFT)

/* 0x64 : frame_byte_cnt0_4 */
#define CAM_FRAME_BYTE_CNT_0_4_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_0_4_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_0_4_SHIFT)

/* 0x68 : frame_start_addr0_5 */
#define CAM_FRAME_START_ADDR_0_5_SHIFT (0U)
#define CAM_FRAME_START_ADDR_0_5_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_0_5_SHIFT)

/* 0x6C : frame_byte_cnt0_5 */
#define CAM_FRAME_BYTE_CNT_0_5_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_0_5_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_0_5_SHIFT)

/* 0x70 : frame_start_addr0_6 */
#define CAM_FRAME_START_ADDR_0_6_SHIFT (0U)
#define CAM_FRAME_START_ADDR_0_6_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_0_6_SHIFT)

/* 0x74 : frame_byte_cnt0_6 */
#define CAM_FRAME_BYTE_CNT_0_6_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_0_6_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_0_6_SHIFT)

/* 0x78 : frame_start_addr0_7 */
#define CAM_FRAME_START_ADDR_0_7_SHIFT (0U)
#define CAM_FRAME_START_ADDR_0_7_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_0_7_SHIFT)

/* 0x7C : frame_byte_cnt0_7 */
#define CAM_FRAME_BYTE_CNT_0_7_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_0_7_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_0_7_SHIFT)

/* 0x80 : frame_start_addr1_0 */
#define CAM_FRAME_START_ADDR_1_0_SHIFT (0U)
#define CAM_FRAME_START_ADDR_1_0_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_1_0_SHIFT)

/* 0x84 : frame_byte_cnt1_0 */
#define CAM_FRAME_BYTE_CNT_1_0_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_1_0_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_1_0_SHIFT)

/* 0x88 : frame_start_addr1_1 */
#define CAM_FRAME_START_ADDR_1_1_SHIFT (0U)
#define CAM_FRAME_START_ADDR_1_1_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_1_1_SHIFT)

/* 0x8C : frame_byte_cnt1_1 */
#define CAM_FRAME_BYTE_CNT_1_1_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_1_1_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_1_1_SHIFT)

/* 0x90 : frame_start_addr1_2 */
#define CAM_FRAME_START_ADDR_1_2_SHIFT (0U)
#define CAM_FRAME_START_ADDR_1_2_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_1_2_SHIFT)

/* 0x94 : frame_byte_cnt1_2 */
#define CAM_FRAME_BYTE_CNT_1_2_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_1_2_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_1_2_SHIFT)

/* 0x98 : frame_start_addr1_3 */
#define CAM_FRAME_START_ADDR_1_3_SHIFT (0U)
#define CAM_FRAME_START_ADDR_1_3_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_1_3_SHIFT)

/* 0x9C : frame_byte_cnt1_3 */
#define CAM_FRAME_BYTE_CNT_1_3_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_1_3_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_1_3_SHIFT)

/* 0xA0 : frame_start_addr1_4 */
#define CAM_FRAME_START_ADDR_1_4_SHIFT (0U)
#define CAM_FRAME_START_ADDR_1_4_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_1_4_SHIFT)

/* 0xA4 : frame_byte_cnt1_4 */
#define CAM_FRAME_BYTE_CNT_1_4_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_1_4_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_1_4_SHIFT)

/* 0xA8 : frame_start_addr1_5 */
#define CAM_FRAME_START_ADDR_1_5_SHIFT (0U)
#define CAM_FRAME_START_ADDR_1_5_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_1_5_SHIFT)

/* 0xAC : frame_byte_cnt1_5 */
#define CAM_FRAME_BYTE_CNT_1_5_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_1_5_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_1_5_SHIFT)

/* 0xB0 : frame_start_addr1_6 */
#define CAM_FRAME_START_ADDR_1_6_SHIFT (0U)
#define CAM_FRAME_START_ADDR_1_6_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_1_6_SHIFT)

/* 0xB4 : frame_byte_cnt1_6 */
#define CAM_FRAME_BYTE_CNT_1_6_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_1_6_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_1_6_SHIFT)

/* 0xB8 : frame_start_addr1_7 */
#define CAM_FRAME_START_ADDR_1_7_SHIFT (0U)
#define CAM_FRAME_START_ADDR_1_7_MASK  (0xffffffff<<CAM_FRAME_START_ADDR_1_7_SHIFT)

/* 0xBC : frame_byte_cnt1_7 */
#define CAM_FRAME_BYTE_CNT_1_7_SHIFT (0U)
#define CAM_FRAME_BYTE_CNT_1_7_MASK  (0xffffffff<<CAM_FRAME_BYTE_CNT_1_7_SHIFT)
#else

/* 0x60 : frame_id_sts01 */
#define CAM_FRAME_ID_0_SHIFT (0U)
#define CAM_FRAME_ID_0_MASK  (0xffff<<CAM_FRAME_ID_0_SHIFT)
#define CAM_FRAME_ID_1_SHIFT (16U)
#define CAM_FRAME_ID_1_MASK  (0xffff<<CAM_FRAME_ID_1_SHIFT)

/* 0x64 : frame_id_sts23 */
#define CAM_FRAME_ID_2_SHIFT (0U)
#define CAM_FRAME_ID_2_MASK  (0xffff<<CAM_FRAME_ID_2_SHIFT)
#define CAM_FRAME_ID_3_SHIFT (16U)
#define CAM_FRAME_ID_3_MASK  (0xffff<<CAM_FRAME_ID_3_SHIFT)
#endif

/* 0xF0 : dvp_debug */
#define CAM_REG_DVP_DBG_EN          (1<<0U)
#define CAM_REG_DVP_DBG_SEL_SHIFT   (1U)
#define CAM_REG_DVP_DBG_SEL_MASK    (0x7<<CAM_REG_DVP_DBG_SEL_SHIFT)
#if !defined(BL702)
#define CAM_REG_ID_LATCH_LINE_SHIFT (8U)
#define CAM_REG_ID_LATCH_LINE_MASK  (0xf<<CAM_REG_ID_LATCH_LINE_SHIFT)
#endif

/* 0xFC : dvp_dummy_reg */


#endif  /* __HARDWARE_CAM_H__ */
