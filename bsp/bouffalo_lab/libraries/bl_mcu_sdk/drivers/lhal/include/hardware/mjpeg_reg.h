/**
  ******************************************************************************
  * @file    mjpeg_reg.h
  * @version V1.0
  * @date    2022-11-01
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
#ifndef  __HARDWARE_MJPEG_REG_H__
#define  __HARDWARE_MJPEG_REG_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define MJPEG_CONTROL_1_OFFSET                                  (0x0)/* mjpeg_control_1 */
#define MJPEG_CONTROL_2_OFFSET                                  (0x4)/* mjpeg_control_2 */
#define MJPEG_YY_FRAME_ADDR_OFFSET                              (0x08)/* mjpeg_yy_frame_addr */
#define MJPEG_UV_FRAME_ADDR_OFFSET                              (0x0C)/* mjpeg_uv_frame_addr */
#define MJPEG_YUV_MEM_OFFSET                                    (0x10)/* mjpeg_yuv_mem */
#define MJPEG_JPEG_FRAME_ADDR_OFFSET                            (0x14)/* jpeg_frame_addr */
#define MJPEG_JPEG_STORE_MEMORY_OFFSET                          (0x18)/* jpeg_store_memory */
#define MJPEG_CONTROL_3_OFFSET                                  (0x1C)/* mjpeg_control_3 */
#define MJPEG_FRAME_FIFO_POP_OFFSET                             (0x20)/* mjpeg_frame_fifo_pop */
#define MJPEG_FRAME_SIZE_OFFSET                                 (0x24)/* mjpeg_frame_size */
#define MJPEG_HEADER_BYTE_OFFSET                                (0x28)/* mjpeg_header_byte */
#define MJPEG_SWAP_MODE_OFFSET                                  (0x30)/* mjpeg_swap_mode */
#define MJPEG_SWAP_BIT_CNT_OFFSET                               (0x34)/* mjpeg_swap_bit_cnt */
#define MJPEG_YUV_MEM_SW_OFFSET                                 (0x38)/* mjpeg_yuv_mem_sw */
#define MJPEG_Y_FRAME_READ_STATUS_1_OFFSET                      (0x40)/* mjpeg_Y_frame_read_status_1 */
#define MJPEG_Y_FRAME_READ_STATUS_2_OFFSET                      (0x44)/* mjpeg_Y_frame_read_status_2 */
#define MJPEG_Y_FRAME_WRITE_STATUS_OFFSET                       (0x48)/* mjpeg_Y_frame_write_status */
#define MJPEG_UV_FRAME_READ_STATUS_1_OFFSET                     (0x4C)/* mjpeg_UV_frame_read_status_1 */
#define MJPEG_UV_FRAME_READ_STATUS_2_OFFSET                     (0x50)/* mjpeg_UV_frame_read_status_2 */
#define MJPEG_UV_FRAME_WRITE_STATUS_OFFSET                      (0x54)/* mjpeg_UV_frame_write_status */
#define MJPEG_FRAME_W_HBLK_STATUS_OFFSET                        (0x58)/* mjpeg_frame_w_hblk_status */
#define MJPEG_START_ADDR0_OFFSET                                (0x80)/* mjpeg_start_addr0 */
#define MJPEG_BIT_CNT0_OFFSET                                   (0x84)/* mjpeg_bit_cnt0 */
#define MJPEG_START_ADDR1_OFFSET                                (0x88)/* mjpeg_start_addr1 */
#define MJPEG_BIT_CNT1_OFFSET                                   (0x8C)/* mjpeg_bit_cnt1 */
#define MJPEG_START_ADDR2_OFFSET                                (0x90)/* mjpeg_start_addr2 */
#define MJPEG_BIT_CNT2_OFFSET                                   (0x94)/* mjpeg_bit_cnt2 */
#define MJPEG_START_ADDR3_OFFSET                                (0x98)/* mjpeg_start_addr3 */
#define MJPEG_BIT_CNT3_OFFSET                                   (0x9C)/* mjpeg_bit_cnt3 */
#define MJPEG_Q_ENC_OFFSET                                      (0x100)/* mjpeg_q_enc */
#define MJPEG_FRAME_ID_10_OFFSET                                (0x110)/* mjpeg_frame_id_10 */
#define MJPEG_FRAME_ID_32_OFFSET                                (0x114)/* mjpeg_frame_id_32 */
#define MJPEG_DEBUG_OFFSET                                      (0x1F0)/* mjpeg_debug */
#define MJPEG_DUMMY_REG_OFFSET                                  (0x1FC)/* mjpeg_dummy_reg */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : mjpeg_control_1 */
#define MJPEG_REG_MJPEG_ENABLE                                  (1<<0U)
#define MJPEG_REG_MJPEG_BIT_ORDER                               (1<<1U)
#define MJPEG_REG_ORDER_U_EVEN                                  (1<<2U)
#define MJPEG_REG_HW_MODE_SWEN                                  (1<<3U)
#define MJPEG_REG_LAST_HF_WBLK_DMY                              (1<<4U)
#define MJPEG_REG_LAST_HF_HBLK_DMY                              (1<<5U)
#define MJPEG_REG_REFLECT_DMY                                   (1<<6U)
#define MJPEG_REG_READ_FWRAP                                    (1<<7U)
#define MJPEG_REG_W_XLEN_SHIFT                                  (8U)
#define MJPEG_REG_W_XLEN_MASK                                   (0x7<<MJPEG_REG_W_XLEN_SHIFT)
#define MJPEG_REG_YUV_MODE_SHIFT                                (12U)
#define MJPEG_REG_YUV_MODE_MASK                                 (0x3<<MJPEG_REG_YUV_MODE_SHIFT)
#define MJPEG_REG_MJPEG_HW_FRAME_SHIFT                          (24U)
#define MJPEG_REG_MJPEG_HW_FRAME_MASK                           (0x3f<<MJPEG_REG_MJPEG_HW_FRAME_SHIFT)

/* 0x4 : mjpeg_control_2 */
#define MJPEG_REG_SW_FRAME_SHIFT                                (0U)
#define MJPEG_REG_SW_FRAME_MASK                                 (0x1f<<MJPEG_REG_SW_FRAME_SHIFT)
#define MJPEG_REG_SW_KICK                                       (1<<6U)
#define MJPEG_REG_SW_KICK_MODE                                  (1<<7U)
#define MJPEG_REG_MJPEG_SW_MODE                                 (1<<8U)
#define MJPEG_REG_MJPEG_SW_RUN                                  (1<<9U)
#define MJPEG_REG_YY_DVP2AXI_SEL_SHIFT                          (10U)
#define MJPEG_REG_YY_DVP2AXI_SEL_MASK                           (0x7<<MJPEG_REG_YY_DVP2AXI_SEL_SHIFT)
#define MJPEG_REG_UV_DVP2AXI_SEL_SHIFT                          (13U)
#define MJPEG_REG_UV_DVP2AXI_SEL_MASK                           (0x7<<MJPEG_REG_UV_DVP2AXI_SEL_SHIFT)
#define MJPEG_REG_MJPEG_WAIT_CYCLE_SHIFT                        (16U)
#define MJPEG_REG_MJPEG_WAIT_CYCLE_MASK                         (0xffff<<MJPEG_REG_MJPEG_WAIT_CYCLE_SHIFT)

/* 0x08 : mjpeg_yy_frame_addr */
#define MJPEG_REG_YY_ADDR_START_SHIFT                           (0U)
#define MJPEG_REG_YY_ADDR_START_MASK                            (0xffffffff<<MJPEG_REG_YY_ADDR_START_SHIFT)

/* 0x0C : mjpeg_uv_frame_addr */
#define MJPEG_REG_UV_ADDR_START_SHIFT                           (0U)
#define MJPEG_REG_UV_ADDR_START_MASK                            (0xffffffff<<MJPEG_REG_UV_ADDR_START_SHIFT)

/* 0x10 : mjpeg_yuv_mem */
#define MJPEG_REG_YY_MEM_HBLK_SHIFT                             (0U)
#define MJPEG_REG_YY_MEM_HBLK_MASK                              (0x1fff<<MJPEG_REG_YY_MEM_HBLK_SHIFT)
#define MJPEG_REG_UV_MEM_HBLK_SHIFT                             (16U)
#define MJPEG_REG_UV_MEM_HBLK_MASK                              (0x1fff<<MJPEG_REG_UV_MEM_HBLK_SHIFT)

/* 0x14 : jpeg_frame_addr */
#define MJPEG_REG_W_ADDR_START_SHIFT                            (0U)
#define MJPEG_REG_W_ADDR_START_MASK                             (0xffffffff<<MJPEG_REG_W_ADDR_START_SHIFT)

/* 0x18 : jpeg_store_memory */
#define MJPEG_REG_W_BURST_CNT_SHIFT                             (0U)
#define MJPEG_REG_W_BURST_CNT_MASK                              (0xffffffff<<MJPEG_REG_W_BURST_CNT_SHIFT)

/* 0x1C : mjpeg_control_3 */
#define MJPEG_REG_INT_NORMAL_EN                                 (1<<0U)
#define MJPEG_REG_INT_CAM_EN                                    (1<<1U)
#define MJPEG_REG_INT_MEM_EN                                    (1<<2U)
#define MJPEG_REG_INT_FRAME_EN                                  (1<<3U)
#define MJPEG_STS_NORMAL_INT                                    (1<<4U)
#define MJPEG_STS_CAM_INT                                       (1<<5U)
#define MJPEG_STS_MEM_INT                                       (1<<6U)
#define MJPEG_STS_FRAME_INT                                     (1<<7U)
#define MJPEG_IDLE                                              (1<<8U)
#define MJPEG_FUNC                                              (1<<9U)
#define MJPEG_WAIT                                              (1<<10U)
#define MJPEG_FLSH                                              (1<<11U)
#define MJPEG_MANS                                              (1<<12U)
#define MJPEG_MANF                                              (1<<13U)
#define MJPEG_AXI_READ_IDLE                                     (1<<14U)
#define MJPEG_AXI_WRITE_IDLE                                    (1<<15U)
#define MJPEG_REG_FRAME_CNT_TRGR_INT_SHIFT                      (16U)
#define MJPEG_REG_FRAME_CNT_TRGR_INT_MASK                       (0x1f<<MJPEG_REG_FRAME_CNT_TRGR_INT_SHIFT)
#define MJPEG_REG_INT_IDLE_EN                                   (1<<21U)
#define MJPEG_STS_IDLE_INT                                      (1<<22U)
#define MJPEG_FRAME_VALID_CNT_SHIFT                             (24U)
#define MJPEG_FRAME_VALID_CNT_MASK                              (0x1f<<MJPEG_FRAME_VALID_CNT_SHIFT)
#define MJPEG_REG_INT_SWAP_EN                                   (1<<29U)
#define MJPEG_STS_SWAP_INT                                      (1<<30U)

/* 0x20 : mjpeg_frame_fifo_pop */
#define MJPEG_RFIFO_POP                                         (1<<0U)
#define MJPEG_REG_W_SWAP_CLR                                    (1<<1U)
#define MJPEG_REG_INT_NORMAL_CLR                                (1<<8U)
#define MJPEG_REG_INT_CAM_CLR                                   (1<<9U)
#define MJPEG_REG_INT_MEM_CLR                                   (1<<10U)
#define MJPEG_REG_INT_FRAME_CLR                                 (1<<11U)
#define MJPEG_REG_INT_IDLE_CLR                                  (1<<12U)
#define MJPEG_REG_INT_SWAP_CLR                                  (1<<13U)

/* 0x24 : mjpeg_frame_size */
#define MJPEG_REG_FRAME_WBLK_SHIFT                              (0U)
#define MJPEG_REG_FRAME_WBLK_MASK                               (0xfff<<MJPEG_REG_FRAME_WBLK_SHIFT)
#define MJPEG_REG_FRAME_HBLK_SHIFT                              (16U)
#define MJPEG_REG_FRAME_HBLK_MASK                               (0xfff<<MJPEG_REG_FRAME_HBLK_SHIFT)

/* 0x28 : mjpeg_header_byte */
#define MJPEG_REG_HEAD_BYTE_SHIFT                               (0U)
#define MJPEG_REG_HEAD_BYTE_MASK                                (0xfff<<MJPEG_REG_HEAD_BYTE_SHIFT)
#define MJPEG_REG_TAIL_EXP                                      (1<<16U)
#define MJPEG_REG_Y0_ORDER_SHIFT                                (24U)
#define MJPEG_REG_Y0_ORDER_MASK                                 (0x3<<MJPEG_REG_Y0_ORDER_SHIFT)
#define MJPEG_REG_U0_ORDER_SHIFT                                (26U)
#define MJPEG_REG_U0_ORDER_MASK                                 (0x3<<MJPEG_REG_U0_ORDER_SHIFT)
#define MJPEG_REG_Y1_ORDER_SHIFT                                (28U)
#define MJPEG_REG_Y1_ORDER_MASK                                 (0x3<<MJPEG_REG_Y1_ORDER_SHIFT)
#define MJPEG_REG_V0_ORDER_SHIFT                                (30U)
#define MJPEG_REG_V0_ORDER_MASK                                 (0x3<<MJPEG_REG_V0_ORDER_SHIFT)

/* 0x30 : mjpeg_swap_mode */
#define MJPEG_REG_W_SWAP_MODE                                   (1<<0U)
#define MJPEG_STS_SWAP0_FULL                                    (1<<8U)
#define MJPEG_STS_SWAP1_FULL                                    (1<<9U)
#define MJPEG_STS_READ_SWAP_IDX                                 (1<<10U)
#define MJPEG_STS_SWAP_FSTART                                   (1<<11U)
#define MJPEG_STS_SWAP_FEND                                     (1<<12U)

/* 0x34 : mjpeg_swap_bit_cnt */
#define MJPEG_FRAME_SWAP_END_BIT_CNT_SHIFT                      (0U)
#define MJPEG_FRAME_SWAP_END_BIT_CNT_MASK                       (0xffffffff<<MJPEG_FRAME_SWAP_END_BIT_CNT_SHIFT)

/* 0x38 : mjpeg_yuv_mem_sw */
#define MJPEG_REG_SW_KICK_HBLK_SHIFT                            (0U)
#define MJPEG_REG_SW_KICK_HBLK_MASK                             (0x1fff<<MJPEG_REG_SW_KICK_HBLK_SHIFT)

/* 0x40 : mjpeg_Y_frame_read_status_1 */
#define MJPEG_YY_MEM_HBLK_R_SHIFT                               (0U)
#define MJPEG_YY_MEM_HBLK_R_MASK                                (0x1fff<<MJPEG_YY_MEM_HBLK_R_SHIFT)
#define MJPEG_YY_FRM_HBLK_R_SHIFT                               (16U)
#define MJPEG_YY_FRM_HBLK_R_MASK                                (0x1fff<<MJPEG_YY_FRM_HBLK_R_SHIFT)

/* 0x44 : mjpeg_Y_frame_read_status_2 */
#define MJPEG_YY_WBLK_R_SHIFT                                   (0U)
#define MJPEG_YY_WBLK_R_MASK                                    (0x1fff<<MJPEG_YY_WBLK_R_SHIFT)
#define MJPEG_YY_MEM_RND_R_SHIFT                                (16U)
#define MJPEG_YY_MEM_RND_R_MASK                                 (0xff<<MJPEG_YY_MEM_RND_R_SHIFT)
#define MJPEG_YY_FRM_CNT_R_SHIFT                                (24U)
#define MJPEG_YY_FRM_CNT_R_MASK                                 (0xff<<MJPEG_YY_FRM_CNT_R_SHIFT)

/* 0x48 : mjpeg_Y_frame_write_status */
#define MJPEG_YY_MEM_HBLK_W_SHIFT                               (0U)
#define MJPEG_YY_MEM_HBLK_W_MASK                                (0x1fff<<MJPEG_YY_MEM_HBLK_W_SHIFT)
#define MJPEG_YY_MEM_RND_W_SHIFT                                (16U)
#define MJPEG_YY_MEM_RND_W_MASK                                 (0xff<<MJPEG_YY_MEM_RND_W_SHIFT)
#define MJPEG_YY_FRM_CNT_W_SHIFT                                (24U)
#define MJPEG_YY_FRM_CNT_W_MASK                                 (0xff<<MJPEG_YY_FRM_CNT_W_SHIFT)

/* 0x4C : mjpeg_UV_frame_read_status_1 */
#define MJPEG_UV_MEM_HBLK_R_SHIFT                               (0U)
#define MJPEG_UV_MEM_HBLK_R_MASK                                (0x1fff<<MJPEG_UV_MEM_HBLK_R_SHIFT)
#define MJPEG_UV_FRM_HBLK_R_SHIFT                               (16U)
#define MJPEG_UV_FRM_HBLK_R_MASK                                (0x1fff<<MJPEG_UV_FRM_HBLK_R_SHIFT)

/* 0x50 : mjpeg_UV_frame_read_status_2 */
#define MJPEG_UV_WBLK_R_SHIFT                                   (0U)
#define MJPEG_UV_WBLK_R_MASK                                    (0x1fff<<MJPEG_UV_WBLK_R_SHIFT)
#define MJPEG_UV_MEM_RND_R_SHIFT                                (16U)
#define MJPEG_UV_MEM_RND_R_MASK                                 (0xff<<MJPEG_UV_MEM_RND_R_SHIFT)
#define MJPEG_UV_FRM_CNT_R_SHIFT                                (24U)
#define MJPEG_UV_FRM_CNT_R_MASK                                 (0xff<<MJPEG_UV_FRM_CNT_R_SHIFT)

/* 0x54 : mjpeg_UV_frame_write_status */
#define MJPEG_UV_MEM_HBLK_W_SHIFT                               (0U)
#define MJPEG_UV_MEM_HBLK_W_MASK                                (0x1fff<<MJPEG_UV_MEM_HBLK_W_SHIFT)
#define MJPEG_UV_MEM_RND_W_SHIFT                                (16U)
#define MJPEG_UV_MEM_RND_W_MASK                                 (0xff<<MJPEG_UV_MEM_RND_W_SHIFT)
#define MJPEG_UV_FRM_CNT_W_SHIFT                                (24U)
#define MJPEG_UV_FRM_CNT_W_MASK                                 (0xff<<MJPEG_UV_FRM_CNT_W_SHIFT)

/* 0x58 : mjpeg_frame_w_hblk_status */
#define MJPEG_YY_FRM_HBLK_W_SHIFT                               (0U)
#define MJPEG_YY_FRM_HBLK_W_MASK                                (0x1fff<<MJPEG_YY_FRM_HBLK_W_SHIFT)
#define MJPEG_UV_FRM_HBLK_W_SHIFT                               (16U)
#define MJPEG_UV_FRM_HBLK_W_MASK                                (0x1fff<<MJPEG_UV_FRM_HBLK_W_SHIFT)

/* 0x80 : mjpeg_start_addr0 */
#define MJPEG_FRAME_START_ADDR_0_SHIFT                          (0U)
#define MJPEG_FRAME_START_ADDR_0_MASK                           (0xffffffff<<MJPEG_FRAME_START_ADDR_0_SHIFT)

/* 0x84 : mjpeg_bit_cnt0 */
#define MJPEG_FRAME_BIT_CNT_0_SHIFT                             (0U)
#define MJPEG_FRAME_BIT_CNT_0_MASK                              (0xffffffff<<MJPEG_FRAME_BIT_CNT_0_SHIFT)

/* 0x88 : mjpeg_start_addr1 */
#define MJPEG_FRAME_START_ADDR_1_SHIFT                          (0U)
#define MJPEG_FRAME_START_ADDR_1_MASK                           (0xffffffff<<MJPEG_FRAME_START_ADDR_1_SHIFT)

/* 0x8C : mjpeg_bit_cnt1 */
#define MJPEG_FRAME_BIT_CNT_1_SHIFT                             (0U)
#define MJPEG_FRAME_BIT_CNT_1_MASK                              (0xffffffff<<MJPEG_FRAME_BIT_CNT_1_SHIFT)

/* 0x90 : mjpeg_start_addr2 */
#define MJPEG_FRAME_START_ADDR_2_SHIFT                          (0U)
#define MJPEG_FRAME_START_ADDR_2_MASK                           (0xffffffff<<MJPEG_FRAME_START_ADDR_2_SHIFT)

/* 0x94 : mjpeg_bit_cnt2 */
#define MJPEG_FRAME_BIT_CNT_2_SHIFT                             (0U)
#define MJPEG_FRAME_BIT_CNT_2_MASK                              (0xffffffff<<MJPEG_FRAME_BIT_CNT_2_SHIFT)

/* 0x98 : mjpeg_start_addr3 */
#define MJPEG_FRAME_START_ADDR_3_SHIFT                          (0U)
#define MJPEG_FRAME_START_ADDR_3_MASK                           (0xffffffff<<MJPEG_FRAME_START_ADDR_3_SHIFT)

/* 0x9C : mjpeg_bit_cnt3 */
#define MJPEG_FRAME_BIT_CNT_3_SHIFT                             (0U)
#define MJPEG_FRAME_BIT_CNT_3_MASK                              (0xffffffff<<MJPEG_FRAME_BIT_CNT_3_SHIFT)

/* 0x100 : mjpeg_q_enc */
#define MJPEG_FRAME_Q_SRAM_0                                    (1<<0U)
#define MJPEG_FRAME_Q_SRAM_1                                    (1<<1U)
#define MJPEG_FRAME_Q_SRAM_2                                    (1<<2U)
#define MJPEG_FRAME_Q_SRAM_3                                    (1<<3U)
#define MJPEG_REG_Q_SRAM_SW                                     (1<<24U)
#define MJPEG_STS_Q_SRAM_ENC                                    (1<<25U)

/* 0x110 : mjpeg_frame_id_10 */
#define MJPEG_FRAME_ID_0_SHIFT                                  (0U)
#define MJPEG_FRAME_ID_0_MASK                                   (0xffff<<MJPEG_FRAME_ID_0_SHIFT)
#define MJPEG_FRAME_ID_1_SHIFT                                  (16U)
#define MJPEG_FRAME_ID_1_MASK                                   (0xffff<<MJPEG_FRAME_ID_1_SHIFT)

/* 0x114 : mjpeg_frame_id_32 */
#define MJPEG_FRAME_ID_2_SHIFT                                  (0U)
#define MJPEG_FRAME_ID_2_MASK                                   (0xffff<<MJPEG_FRAME_ID_2_SHIFT)
#define MJPEG_FRAME_ID_3_SHIFT                                  (16U)
#define MJPEG_FRAME_ID_3_MASK                                   (0xffff<<MJPEG_FRAME_ID_3_SHIFT)

/* 0x1F0 : mjpeg_debug */
#define MJPEG_REG_MJPEG_DBG_EN                                  (1<<0U)
#define MJPEG_REG_MJPEG_DBG_SEL_SHIFT                           (4U)
#define MJPEG_REG_MJPEG_DBG_SEL_MASK                            (0xf<<MJPEG_REG_MJPEG_DBG_SEL_SHIFT)
#define MJPEG_REG_ID_LATCH_HBLK_SHIFT                           (8U)
#define MJPEG_REG_ID_LATCH_HBLK_MASK                            (0xf<<MJPEG_REG_ID_LATCH_HBLK_SHIFT)

/* 0x1FC : mjpeg_dummy_reg */
#define MJPEG_DUMMY_REG_SHIFT                                   (0U)
#define MJPEG_DUMMY_REG_MASK                                    (0xffffffff<<MJPEG_DUMMY_REG_SHIFT)


#endif  /* __HARDWARE_MJPEG_REG_H__ */
