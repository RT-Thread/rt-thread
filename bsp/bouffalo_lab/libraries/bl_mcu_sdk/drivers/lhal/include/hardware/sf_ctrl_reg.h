/**
  ******************************************************************************
  * @file    sf_ctrl_reg.h
  * @version V1.0
  * @date    2022-10-20
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
#ifndef  __SF_CTRL_REG_H__
#define  __SF_CTRL_REG_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define SF_CTRL_0_OFFSET                                        (0x0)/* sf_ctrl_0 */
#define SF_CTRL_1_OFFSET                                        (0x4)/* sf_ctrl_1 */
#define SF_CTRL_SF_IF_SAHB_0_OFFSET                             (0x8)/* sf_if_sahb_0 */
#define SF_CTRL_SF_IF_SAHB_1_OFFSET                             (0xC)/* sf_if_sahb_1 */
#define SF_CTRL_SF_IF_SAHB_2_OFFSET                             (0x10)/* sf_if_sahb_2 */
#define SF_CTRL_SF_IF_IAHB_0_OFFSET                             (0x14)/* sf_if_iahb_0 */
#define SF_CTRL_SF_IF_IAHB_1_OFFSET                             (0x18)/* sf_if_iahb_1 */
#define SF_CTRL_SF_IF_IAHB_2_OFFSET                             (0x1C)/* sf_if_iahb_2 */
#define SF_CTRL_SF_IF_STATUS_0_OFFSET                           (0x20)/* sf_if_status_0 */
#define SF_CTRL_SF_IF_STATUS_1_OFFSET                           (0x24)/* sf_if_status_1 */
#define SF_CTRL_SF_AES_OFFSET                                   (0x28)/* sf_aes */
#define SF_CTRL_SF_AHB2SIF_STATUS_OFFSET                        (0x2C)/* sf_ahb2sif_status */
#define SF_CTRL_SF_IF_IO_DLY_0_OFFSET                           (0x30)/* sf_if_io_dly_0 */
#define SF_CTRL_SF_IF_IO_DLY_1_OFFSET                           (0x34)/* sf_if_io_dly_1 */
#define SF_CTRL_SF_IF_IO_DLY_2_OFFSET                           (0x38)/* sf_if_io_dly_2 */
#define SF_CTRL_SF_IF_IO_DLY_3_OFFSET                           (0x3C)/* sf_if_io_dly_3 */
#define SF_CTRL_SF_IF_IO_DLY_4_OFFSET                           (0x40)/* sf_if_io_dly_4 */
#define SF_CTRL_SF_RESERVED_OFFSET                              (0x44)/* sf_reserved */
#define SF_CTRL_SF2_IF_IO_DLY_0_OFFSET                          (0x48)/* sf2_if_io_dly_0 */
#define SF_CTRL_SF2_IF_IO_DLY_1_OFFSET                          (0x4C)/* sf2_if_io_dly_1 */
#define SF_CTRL_SF2_IF_IO_DLY_2_OFFSET                          (0x50)/* sf2_if_io_dly_2 */
#define SF_CTRL_SF2_IF_IO_DLY_3_OFFSET                          (0x54)/* sf2_if_io_dly_3 */
#define SF_CTRL_SF2_IF_IO_DLY_4_OFFSET                          (0x58)/* sf2_if_io_dly_4 */
#define SF_CTRL_SF3_IF_IO_DLY_0_OFFSET                          (0x5C)/* sf3_if_io_dly_0 */
#define SF_CTRL_SF3_IF_IO_DLY_1_OFFSET                          (0x60)/* sf3_if_io_dly_1 */
#define SF_CTRL_SF3_IF_IO_DLY_2_OFFSET                          (0x64)/* sf3_if_io_dly_2 */
#define SF_CTRL_SF3_IF_IO_DLY_3_OFFSET                          (0x68)/* sf3_if_io_dly_3 */
#define SF_CTRL_SF3_IF_IO_DLY_4_OFFSET                          (0x6C)/* sf3_if_io_dly_4 */
#define SF_CTRL_2_OFFSET                                        (0x70)/* sf_ctrl_2 */
#define SF_CTRL_3_OFFSET                                        (0x74)/* sf_ctrl_3 */
#define SF_CTRL_SF_IF_IAHB_3_OFFSET                             (0x78)/* sf_if_iahb_3 */
#define SF_CTRL_SF_IF_IAHB_4_OFFSET                             (0x7C)/* sf_if_iahb_4 */
#define SF_CTRL_SF_IF_IAHB_5_OFFSET                             (0x80)/* sf_if_iahb_5 */
#define SF_CTRL_SF_IF_IAHB_6_OFFSET                             (0x84)/* sf_if_iahb_6 */
#define SF_CTRL_SF_IF_IAHB_7_OFFSET                             (0x88)/* sf_if_iahb_7 */
#define SF_CTRL_SF_IF_IAHB_8_OFFSET                             (0x8C)/* sf_if_iahb_8 */
#define SF_CTRL_SF_IF_IAHB_9_OFFSET                             (0x90)/* sf_if_iahb_9 */
#define SF_CTRL_SF_IF_IAHB_10_OFFSET                            (0x94)/* sf_if_iahb_10 */
#define SF_CTRL_SF_IF_IAHB_11_OFFSET                            (0x98)/* sf_if_iahb_11 */
#define SF_CTRL_SF_IF_IAHB_12_OFFSET                            (0x9C)/* sf_if_iahb_12 */
#define SF_CTRL_SF_ID0_OFFSET_OFFSET                            (0xA0)/* sf_id0_offset */
#define SF_CTRL_SF_ID1_OFFSET_OFFSET                            (0xA4)/* sf_id1_offset */
#define SF_CTRL_SF_BK2_ID0_OFFSET_OFFSET                        (0xA8)/* sf_bk2_id0_offset */
#define SF_CTRL_SF_BK2_ID1_OFFSET_OFFSET                        (0xAC)/* sf_bk2_id1_offset */
#define SF_CTRL_SF_DBG_OFFSET                                   (0xB0)/* sf_dbg */
#define SF_CTRL_SF_IF2_CTRL_0_OFFSET                            (0xC0)/* sf_if2_ctrl_0 */
#define SF_CTRL_SF_IF2_CTRL_1_OFFSET                            (0xC4)/* sf_if2_ctrl_1 */
#define SF_CTRL_SF_IF2_SAHB_0_OFFSET                            (0xC8)/* sf_if2_sahb_0 */
#define SF_CTRL_SF_IF2_SAHB_1_OFFSET                            (0xCC)/* sf_if2_sahb_1 */
#define SF_CTRL_SF_IF2_SAHB_2_OFFSET                            (0xD0)/* sf_if2_sahb_2 */
#define SF_CTRL_PROT_EN_RD_OFFSET                               (0x100)/* sf_ctrl_prot_en_rd */
#define SF_CTRL_PROT_EN_OFFSET                                  (0x104)/* sf_ctrl_prot_en */
#define SF_CTRL_SF_AES_KEY_R0_0_OFFSET                          (0x200)/* sf_aes_key_r0_0 */
#define SF_CTRL_SF_AES_KEY_R0_1_OFFSET                          (0x204)/* sf_aes_key_r0_1 */
#define SF_CTRL_SF_AES_KEY_R0_2_OFFSET                          (0x208)/* sf_aes_key_r0_2 */
#define SF_CTRL_SF_AES_KEY_R0_3_OFFSET                          (0x20C)/* sf_aes_key_r0_3 */
#define SF_CTRL_SF_AES_KEY_R0_4_OFFSET                          (0x210)/* sf_aes_key_r0_4 */
#define SF_CTRL_SF_AES_KEY_R0_5_OFFSET                          (0x214)/* sf_aes_key_r0_5 */
#define SF_CTRL_SF_AES_KEY_R0_6_OFFSET                          (0x218)/* sf_aes_key_r0_6 */
#define SF_CTRL_SF_AES_KEY_R0_7_OFFSET                          (0x21C)/* sf_aes_key_r0_7 */
#define SF_CTRL_SF_AES_IV_R0_W0_OFFSET                          (0x220)/* sf_aes_iv_r0_w0 */
#define SF_CTRL_SF_AES_IV_R0_W1_OFFSET                          (0x224)/* sf_aes_iv_r0_w1 */
#define SF_CTRL_SF_AES_IV_R0_W2_OFFSET                          (0x228)/* sf_aes_iv_r0_w2 */
#define SF_CTRL_SF_AES_IV_R0_W3_OFFSET                          (0x22C)/* sf_aes_iv_r0_w3 */
#define SF_CTRL_SF_AES_R0_START_OFFSET                          (0x230)/* sf_aes_r0_start */
#define SF_CTRL_SF_AES_R0_END_OFFSET                            (0x234)/* sf_aes_r0_end */
#define SF_CTRL_SF_AES_KEY_R1_0_OFFSET                          (0x280)/* sf_aes_key_r1_0 */
#define SF_CTRL_SF_AES_KEY_R1_1_OFFSET                          (0x284)/* sf_aes_key_r1_1 */
#define SF_CTRL_SF_AES_KEY_R1_2_OFFSET                          (0x288)/* sf_aes_key_r1_2 */
#define SF_CTRL_SF_AES_KEY_R1_3_OFFSET                          (0x28C)/* sf_aes_key_r1_3 */
#define SF_CTRL_SF_AES_KEY_R1_4_OFFSET                          (0x290)/* sf_aes_key_r1_4 */
#define SF_CTRL_SF_AES_KEY_R1_5_OFFSET                          (0x294)/* sf_aes_key_r1_5 */
#define SF_CTRL_SF_AES_KEY_R1_6_OFFSET                          (0x298)/* sf_aes_key_r1_6 */
#define SF_CTRL_SF_AES_KEY_R1_7_OFFSET                          (0x29C)/* sf_aes_key_r1_7 */
#define SF_CTRL_SF_AES_IV_R1_W0_OFFSET                          (0x2A0)/* sf_aes_iv_r1_w0 */
#define SF_CTRL_SF_AES_IV_R1_W1_OFFSET                          (0x2A4)/* sf_aes_iv_r1_w1 */
#define SF_CTRL_SF_AES_IV_R1_W2_OFFSET                          (0x2A8)/* sf_aes_iv_r1_w2 */
#define SF_CTRL_SF_AES_IV_R1_W3_OFFSET                          (0x2AC)/* sf_aes_iv_r1_w3 */
#define SF_CTRL_SF_AES_R1_START_OFFSET                          (0x2B0)/* sf_aes_r1_start */
#define SF_CTRL_SF_AES_R1_END_OFFSET                            (0x2B4)/* sf_aes_r1_end */
#define SF_CTRL_SF_AES_KEY_R2_0_OFFSET                          (0x300)/* sf_aes_key_r2_0 */
#define SF_CTRL_SF_AES_KEY_R2_1_OFFSET                          (0x304)/* sf_aes_key_r2_1 */
#define SF_CTRL_SF_AES_KEY_R2_2_OFFSET                          (0x308)/* sf_aes_key_r2_2 */
#define SF_CTRL_SF_AES_KEY_R2_3_OFFSET                          (0x30C)/* sf_aes_key_r2_3 */
#define SF_CTRL_SF_AES_KEY_R2_4_OFFSET                          (0x310)/* sf_aes_key_r2_4 */
#define SF_CTRL_SF_AES_KEY_R2_5_OFFSET                          (0x314)/* sf_aes_key_r2_5 */
#define SF_CTRL_SF_AES_KEY_R2_6_OFFSET                          (0x318)/* sf_aes_key_r2_6 */
#define SF_CTRL_SF_AES_KEY_R2_7_OFFSET                          (0x31C)/* sf_aes_key_r2_7 */
#define SF_CTRL_SF_AES_IV_R2_W0_OFFSET                          (0x320)/* sf_aes_iv_r2_w0 */
#define SF_CTRL_SF_AES_IV_R2_W1_OFFSET                          (0x324)/* sf_aes_iv_r2_w1 */
#define SF_CTRL_SF_AES_IV_R2_W2_OFFSET                          (0x328)/* sf_aes_iv_r2_w2 */
#define SF_CTRL_SF_AES_IV_R2_W3_OFFSET                          (0x32C)/* sf_aes_iv_r2_w3 */
#define SF_CTRL_SF_AES_R2_START_OFFSET                          (0x330)/* sf_aes_r2_start */
#define SF_CTRL_SF_AES_R2_END_OFFSET                            (0x334)/* sf_aes_r2_end */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : sf_ctrl_0 */
#define SF_CTRL_SF_CLK_SF_RX_INV_SEL                            (1<<2U)
#define SF_CTRL_SF_CLK_OUT_GATE_EN                              (1<<3U)
#define SF_CTRL_SF_CLK_OUT_INV_SEL                              (1<<4U)
#define SF_CTRL_SF_IF_READ_DLY_N_SHIFT                          (8U)
#define SF_CTRL_SF_IF_READ_DLY_N_MASK                           (0x7<<SF_CTRL_SF_IF_READ_DLY_N_SHIFT)
#define SF_CTRL_SF_IF_READ_DLY_EN                               (1<<11U)
#define SF_CTRL_SF_IF_INT                                       (1<<16U)
#define SF_CTRL_SF_IF_INT_CLR                                   (1<<17U)
#define SF_CTRL_SF_IF_INT_SET                                   (1<<18U)
#define SF_CTRL_SF_IF_32B_ADR_EN                                (1<<19U)
#define SF_CTRL_SF_AES_DOUT_ENDIAN                              (1<<20U)
#define SF_CTRL_SF_AES_DIN_ENDIAN                               (1<<21U)
#define SF_CTRL_SF_AES_KEY_ENDIAN                               (1<<22U)
#define SF_CTRL_SF_AES_IV_ENDIAN                                (1<<23U)
#define SF_CTRL_SF_ID_SHIFT                                     (24U)
#define SF_CTRL_SF_ID_MASK                                      (0xff<<SF_CTRL_SF_ID_SHIFT)

/* 0x4 : sf_ctrl_1 */
#define SF_CTRL_SF_IF_SR_PAT_MASK_SHIFT                         (0U)
#define SF_CTRL_SF_IF_SR_PAT_MASK_MASK                          (0xff<<SF_CTRL_SF_IF_SR_PAT_MASK_SHIFT)
#define SF_CTRL_SF_IF_SR_PAT_SHIFT                              (8U)
#define SF_CTRL_SF_IF_SR_PAT_MASK                               (0xff<<SF_CTRL_SF_IF_SR_PAT_SHIFT)
#define SF_CTRL_SF_IF_SR_INT                                    (1<<16U)
#define SF_CTRL_SF_IF_SR_INT_EN                                 (1<<17U)
#define SF_CTRL_SF_IF_SR_INT_SET                                (1<<18U)
#define SF_CTRL_SF_IF_0_ACK_LAT_SHIFT                           (20U)
#define SF_CTRL_SF_IF_0_ACK_LAT_MASK                            (0x7<<SF_CTRL_SF_IF_0_ACK_LAT_SHIFT)
#define SF_CTRL_SF_AHB2SIF_DISWRAP                              (1<<23U)
#define SF_CTRL_SF_IF_REG_HOLD                                  (1<<24U)
#define SF_CTRL_SF_IF_REG_WP                                    (1<<25U)
#define SF_CTRL_SF_AHB2SIF_STOPPED                              (1<<26U)
#define SF_CTRL_SF_AHB2SIF_STOP                                 (1<<27U)
#define SF_CTRL_SF_IF_FN_SEL                                    (1<<28U)
#define SF_CTRL_SF_IF_EN                                        (1<<29U)
#define SF_CTRL_SF_AHB2SIF_EN                                   (1<<30U)
#define SF_CTRL_SF_AHB2SRAM_EN                                  (1<<31U)

/* 0x8 : sf_if_sahb_0 */
#define SF_CTRL_SF_IF_BUSY                                      (1<<0U)
#define SF_CTRL_SF_IF_0_TRIG                                    (1<<1U)
#define SF_CTRL_SF_IF_0_DAT_BYTE_SHIFT                          (2U)
#define SF_CTRL_SF_IF_0_DAT_BYTE_MASK                           (0x3ff<<SF_CTRL_SF_IF_0_DAT_BYTE_SHIFT)
#define SF_CTRL_SF_IF_0_DMY_BYTE_SHIFT                          (12U)
#define SF_CTRL_SF_IF_0_DMY_BYTE_MASK                           (0x1f<<SF_CTRL_SF_IF_0_DMY_BYTE_SHIFT)
#define SF_CTRL_SF_IF_0_ADR_BYTE_SHIFT                          (17U)
#define SF_CTRL_SF_IF_0_ADR_BYTE_MASK                           (0x7<<SF_CTRL_SF_IF_0_ADR_BYTE_SHIFT)
#define SF_CTRL_SF_IF_0_CMD_BYTE_SHIFT                          (20U)
#define SF_CTRL_SF_IF_0_CMD_BYTE_MASK                           (0x7<<SF_CTRL_SF_IF_0_CMD_BYTE_SHIFT)
#define SF_CTRL_SF_IF_0_DAT_RW                                  (1<<23U)
#define SF_CTRL_SF_IF_0_DAT_EN                                  (1<<24U)
#define SF_CTRL_SF_IF_0_DMY_EN                                  (1<<25U)
#define SF_CTRL_SF_IF_0_ADR_EN                                  (1<<26U)
#define SF_CTRL_SF_IF_0_CMD_EN                                  (1<<27U)
#define SF_CTRL_SF_IF_0_SPI_MODE_SHIFT                          (28U)
#define SF_CTRL_SF_IF_0_SPI_MODE_MASK                           (0x7<<SF_CTRL_SF_IF_0_SPI_MODE_SHIFT)
#define SF_CTRL_SF_IF_0_QPI_MODE_EN                             (1<<31U)

/* 0xC : sf_if_sahb_1 */
#define SF_CTRL_SF_IF_0_CMD_BUF_0_SHIFT                         (0U)
#define SF_CTRL_SF_IF_0_CMD_BUF_0_MASK                          (0xffffffffL<<SF_CTRL_SF_IF_0_CMD_BUF_0_SHIFT)

/* 0x10 : sf_if_sahb_2 */
#define SF_CTRL_SF_IF_0_CMD_BUF_1_SHIFT                         (0U)
#define SF_CTRL_SF_IF_0_CMD_BUF_1_MASK                          (0xffffffffL<<SF_CTRL_SF_IF_0_CMD_BUF_1_SHIFT)

/* 0x14 : sf_if_iahb_0 */
#define SF_CTRL_SF_IF_1_DMY_BYTE_SHIFT                          (12U)
#define SF_CTRL_SF_IF_1_DMY_BYTE_MASK                           (0x1f<<SF_CTRL_SF_IF_1_DMY_BYTE_SHIFT)
#define SF_CTRL_SF_IF_1_ADR_BYTE_SHIFT                          (17U)
#define SF_CTRL_SF_IF_1_ADR_BYTE_MASK                           (0x7<<SF_CTRL_SF_IF_1_ADR_BYTE_SHIFT)
#define SF_CTRL_SF_IF_1_CMD_BYTE_SHIFT                          (20U)
#define SF_CTRL_SF_IF_1_CMD_BYTE_MASK                           (0x7<<SF_CTRL_SF_IF_1_CMD_BYTE_SHIFT)
#define SF_CTRL_SF_IF_1_DAT_RW                                  (1<<23U)
#define SF_CTRL_SF_IF_1_DAT_EN                                  (1<<24U)
#define SF_CTRL_SF_IF_1_DMY_EN                                  (1<<25U)
#define SF_CTRL_SF_IF_1_ADR_EN                                  (1<<26U)
#define SF_CTRL_SF_IF_1_CMD_EN                                  (1<<27U)
#define SF_CTRL_SF_IF_1_SPI_MODE_SHIFT                          (28U)
#define SF_CTRL_SF_IF_1_SPI_MODE_MASK                           (0x7<<SF_CTRL_SF_IF_1_SPI_MODE_SHIFT)
#define SF_CTRL_SF_IF_1_QPI_MODE_EN                             (1<<31U)

/* 0x18 : sf_if_iahb_1 */
#define SF_CTRL_SF_IF_1_CMD_BUF_0_SHIFT                         (0U)
#define SF_CTRL_SF_IF_1_CMD_BUF_0_MASK                          (0xffffffffL<<SF_CTRL_SF_IF_1_CMD_BUF_0_SHIFT)

/* 0x1C : sf_if_iahb_2 */
#define SF_CTRL_SF_IF_1_CMD_BUF_1_SHIFT                         (0U)
#define SF_CTRL_SF_IF_1_CMD_BUF_1_MASK                          (0xffffffffL<<SF_CTRL_SF_IF_1_CMD_BUF_1_SHIFT)

/* 0x20 : sf_if_status_0 */
#define SF_CTRL_SF_IF_STATUS_0_SHIFT                            (0U)
#define SF_CTRL_SF_IF_STATUS_0_MASK                             (0xffffffffL<<SF_CTRL_SF_IF_STATUS_0_SHIFT)

/* 0x24 : sf_if_status_1 */
#define SF_CTRL_SF_IF_STATUS_1_SHIFT                            (0U)
#define SF_CTRL_SF_IF_STATUS_1_MASK                             (0xffffffffL<<SF_CTRL_SF_IF_STATUS_1_SHIFT)

/* 0x28 : sf_aes */
#define SF_CTRL_SF_AES_EN                                       (1<<0U)
#define SF_CTRL_SF_AES_MODE_SHIFT                               (1U)
#define SF_CTRL_SF_AES_MODE_MASK                                (0x3<<SF_CTRL_SF_AES_MODE_SHIFT)
#define SF_CTRL_SF_AES_BLK_MODE                                 (1<<3U)
#define SF_CTRL_SF_AES_XTS_KEY_OPT                              (1<<4U)
#define SF_CTRL_SF_AES_STATUS_SHIFT                             (5U)
#define SF_CTRL_SF_AES_STATUS_MASK                              (0x7ffffff<<SF_CTRL_SF_AES_STATUS_SHIFT)

/* 0x2C : sf_ahb2sif_status */
#define SF_CTRL_SF_AHB2SIF_STATUS_SHIFT                         (0U)
#define SF_CTRL_SF_AHB2SIF_STATUS_MASK                          (0xffffffffL<<SF_CTRL_SF_AHB2SIF_STATUS_SHIFT)

/* 0x30 : sf_if_io_dly_0 */
#define SF_CTRL_SF_CS_DLY_SEL_SHIFT                             (0U)
#define SF_CTRL_SF_CS_DLY_SEL_MASK                              (0x3<<SF_CTRL_SF_CS_DLY_SEL_SHIFT)
#define SF_CTRL_SF_CS2_DLY_SEL_SHIFT                            (2U)
#define SF_CTRL_SF_CS2_DLY_SEL_MASK                             (0x3<<SF_CTRL_SF_CS2_DLY_SEL_SHIFT)
#define SF_CTRL_SF_CLK_OUT_DLY_SEL_SHIFT                        (8U)
#define SF_CTRL_SF_CLK_OUT_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF_CLK_OUT_DLY_SEL_SHIFT)
#define SF_CTRL_SF_DQS_OE_DLY_SEL_SHIFT                         (26U)
#define SF_CTRL_SF_DQS_OE_DLY_SEL_MASK                          (0x3<<SF_CTRL_SF_DQS_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF_DQS_DI_DLY_SEL_SHIFT                         (28U)
#define SF_CTRL_SF_DQS_DI_DLY_SEL_MASK                          (0x3<<SF_CTRL_SF_DQS_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF_DQS_DO_DLY_SEL_SHIFT                         (30U)
#define SF_CTRL_SF_DQS_DO_DLY_SEL_MASK                          (0x3<<SF_CTRL_SF_DQS_DO_DLY_SEL_SHIFT)

/* 0x34 : sf_if_io_dly_1 */
#define SF_CTRL_SF_IO_0_OE_DLY_SEL_SHIFT                        (0U)
#define SF_CTRL_SF_IO_0_OE_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF_IO_0_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF_IO_0_DI_DLY_SEL_SHIFT                        (8U)
#define SF_CTRL_SF_IO_0_DI_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF_IO_0_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF_IO_0_DO_DLY_SEL_SHIFT                        (16U)
#define SF_CTRL_SF_IO_0_DO_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF_IO_0_DO_DLY_SEL_SHIFT)

/* 0x38 : sf_if_io_dly_2 */
#define SF_CTRL_SF_IO_1_OE_DLY_SEL_SHIFT                        (0U)
#define SF_CTRL_SF_IO_1_OE_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF_IO_1_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF_IO_1_DI_DLY_SEL_SHIFT                        (8U)
#define SF_CTRL_SF_IO_1_DI_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF_IO_1_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF_IO_1_DO_DLY_SEL_SHIFT                        (16U)
#define SF_CTRL_SF_IO_1_DO_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF_IO_1_DO_DLY_SEL_SHIFT)

/* 0x3C : sf_if_io_dly_3 */
#define SF_CTRL_SF_IO_2_OE_DLY_SEL_SHIFT                        (0U)
#define SF_CTRL_SF_IO_2_OE_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF_IO_2_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF_IO_2_DI_DLY_SEL_SHIFT                        (8U)
#define SF_CTRL_SF_IO_2_DI_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF_IO_2_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF_IO_2_DO_DLY_SEL_SHIFT                        (16U)
#define SF_CTRL_SF_IO_2_DO_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF_IO_2_DO_DLY_SEL_SHIFT)

/* 0x40 : sf_if_io_dly_4 */
#define SF_CTRL_SF_IO_3_OE_DLY_SEL_SHIFT                        (0U)
#define SF_CTRL_SF_IO_3_OE_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF_IO_3_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF_IO_3_DI_DLY_SEL_SHIFT                        (8U)
#define SF_CTRL_SF_IO_3_DI_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF_IO_3_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF_IO_3_DO_DLY_SEL_SHIFT                        (16U)
#define SF_CTRL_SF_IO_3_DO_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF_IO_3_DO_DLY_SEL_SHIFT)

/* 0x44 : sf_reserved */
#define SF_CTRL_SF_RESERVED_SHIFT                               (0U)
#define SF_CTRL_SF_RESERVED_MASK                                (0xffffffffL<<SF_CTRL_SF_RESERVED_SHIFT)

/* 0x48 : sf2_if_io_dly_0 */
#define SF_CTRL_SF2_CS_DLY_SEL_SHIFT                            (0U)
#define SF_CTRL_SF2_CS_DLY_SEL_MASK                             (0x3<<SF_CTRL_SF2_CS_DLY_SEL_SHIFT)
#define SF_CTRL_SF2_CS2_DLY_SEL_SHIFT                           (2U)
#define SF_CTRL_SF2_CS2_DLY_SEL_MASK                            (0x3<<SF_CTRL_SF2_CS2_DLY_SEL_SHIFT)
#define SF_CTRL_SF2_CLK_OUT_DLY_SEL_SHIFT                       (8U)
#define SF_CTRL_SF2_CLK_OUT_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF2_CLK_OUT_DLY_SEL_SHIFT)
#define SF_CTRL_SF2_DQS_OE_DLY_SEL_SHIFT                        (26U)
#define SF_CTRL_SF2_DQS_OE_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF2_DQS_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF2_DQS_DI_DLY_SEL_SHIFT                        (28U)
#define SF_CTRL_SF2_DQS_DI_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF2_DQS_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF2_DQS_DO_DLY_SEL_SHIFT                        (30U)
#define SF_CTRL_SF2_DQS_DO_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF2_DQS_DO_DLY_SEL_SHIFT)

/* 0x4C : sf2_if_io_dly_1 */
#define SF_CTRL_SF2_IO_0_OE_DLY_SEL_SHIFT                       (0U)
#define SF_CTRL_SF2_IO_0_OE_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF2_IO_0_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF2_IO_0_DI_DLY_SEL_SHIFT                       (8U)
#define SF_CTRL_SF2_IO_0_DI_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF2_IO_0_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF2_IO_0_DO_DLY_SEL_SHIFT                       (16U)
#define SF_CTRL_SF2_IO_0_DO_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF2_IO_0_DO_DLY_SEL_SHIFT)

/* 0x50 : sf2_if_io_dly_2 */
#define SF_CTRL_SF2_IO_1_OE_DLY_SEL_SHIFT                       (0U)
#define SF_CTRL_SF2_IO_1_OE_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF2_IO_1_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF2_IO_1_DI_DLY_SEL_SHIFT                       (8U)
#define SF_CTRL_SF2_IO_1_DI_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF2_IO_1_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF2_IO_1_DO_DLY_SEL_SHIFT                       (16U)
#define SF_CTRL_SF2_IO_1_DO_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF2_IO_1_DO_DLY_SEL_SHIFT)

/* 0x54 : sf2_if_io_dly_3 */
#define SF_CTRL_SF2_IO_2_OE_DLY_SEL_SHIFT                       (0U)
#define SF_CTRL_SF2_IO_2_OE_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF2_IO_2_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF2_IO_2_DI_DLY_SEL_SHIFT                       (8U)
#define SF_CTRL_SF2_IO_2_DI_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF2_IO_2_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF2_IO_2_DO_DLY_SEL_SHIFT                       (16U)
#define SF_CTRL_SF2_IO_2_DO_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF2_IO_2_DO_DLY_SEL_SHIFT)

/* 0x58 : sf2_if_io_dly_4 */
#define SF_CTRL_SF2_IO_3_OE_DLY_SEL_SHIFT                       (0U)
#define SF_CTRL_SF2_IO_3_OE_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF2_IO_3_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF2_IO_3_DI_DLY_SEL_SHIFT                       (8U)
#define SF_CTRL_SF2_IO_3_DI_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF2_IO_3_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF2_IO_3_DO_DLY_SEL_SHIFT                       (16U)
#define SF_CTRL_SF2_IO_3_DO_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF2_IO_3_DO_DLY_SEL_SHIFT)

/* 0x5C : sf3_if_io_dly_0 */
#define SF_CTRL_SF3_CS_DLY_SEL_SHIFT                            (0U)
#define SF_CTRL_SF3_CS_DLY_SEL_MASK                             (0x3<<SF_CTRL_SF3_CS_DLY_SEL_SHIFT)
#define SF_CTRL_SF3_CS2_DLY_SEL_SHIFT                           (2U)
#define SF_CTRL_SF3_CS2_DLY_SEL_MASK                            (0x3<<SF_CTRL_SF3_CS2_DLY_SEL_SHIFT)
#define SF_CTRL_SF3_CLK_OUT_DLY_SEL_SHIFT                       (8U)
#define SF_CTRL_SF3_CLK_OUT_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF3_CLK_OUT_DLY_SEL_SHIFT)
#define SF_CTRL_SF3_DQS_OE_DLY_SEL_SHIFT                        (26U)
#define SF_CTRL_SF3_DQS_OE_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF3_DQS_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF3_DQS_DI_DLY_SEL_SHIFT                        (28U)
#define SF_CTRL_SF3_DQS_DI_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF3_DQS_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF3_DQS_DO_DLY_SEL_SHIFT                        (30U)
#define SF_CTRL_SF3_DQS_DO_DLY_SEL_MASK                         (0x3<<SF_CTRL_SF3_DQS_DO_DLY_SEL_SHIFT)

/* 0x60 : sf3_if_io_dly_1 */
#define SF_CTRL_SF3_IO_0_OE_DLY_SEL_SHIFT                       (0U)
#define SF_CTRL_SF3_IO_0_OE_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF3_IO_0_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF3_IO_0_DI_DLY_SEL_SHIFT                       (8U)
#define SF_CTRL_SF3_IO_0_DI_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF3_IO_0_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF3_IO_0_DO_DLY_SEL_SHIFT                       (16U)
#define SF_CTRL_SF3_IO_0_DO_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF3_IO_0_DO_DLY_SEL_SHIFT)

/* 0x64 : sf3_if_io_dly_2 */
#define SF_CTRL_SF3_IO_1_OE_DLY_SEL_SHIFT                       (0U)
#define SF_CTRL_SF3_IO_1_OE_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF3_IO_1_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF3_IO_1_DI_DLY_SEL_SHIFT                       (8U)
#define SF_CTRL_SF3_IO_1_DI_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF3_IO_1_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF3_IO_1_DO_DLY_SEL_SHIFT                       (16U)
#define SF_CTRL_SF3_IO_1_DO_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF3_IO_1_DO_DLY_SEL_SHIFT)

/* 0x68 : sf3_if_io_dly_3 */
#define SF_CTRL_SF3_IO_2_OE_DLY_SEL_SHIFT                       (0U)
#define SF_CTRL_SF3_IO_2_OE_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF3_IO_2_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF3_IO_2_DI_DLY_SEL_SHIFT                       (8U)
#define SF_CTRL_SF3_IO_2_DI_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF3_IO_2_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF3_IO_2_DO_DLY_SEL_SHIFT                       (16U)
#define SF_CTRL_SF3_IO_2_DO_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF3_IO_2_DO_DLY_SEL_SHIFT)

/* 0x6C : sf3_if_io_dly_4 */
#define SF_CTRL_SF3_IO_3_OE_DLY_SEL_SHIFT                       (0U)
#define SF_CTRL_SF3_IO_3_OE_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF3_IO_3_OE_DLY_SEL_SHIFT)
#define SF_CTRL_SF3_IO_3_DI_DLY_SEL_SHIFT                       (8U)
#define SF_CTRL_SF3_IO_3_DI_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF3_IO_3_DI_DLY_SEL_SHIFT)
#define SF_CTRL_SF3_IO_3_DO_DLY_SEL_SHIFT                       (16U)
#define SF_CTRL_SF3_IO_3_DO_DLY_SEL_MASK                        (0x3<<SF_CTRL_SF3_IO_3_DO_DLY_SEL_SHIFT)

/* 0x70 : sf_ctrl_2 */
#define SF_CTRL_SF_IF_PAD_SEL_SHIFT                             (0U)
#define SF_CTRL_SF_IF_PAD_SEL_MASK                              (0x3<<SF_CTRL_SF_IF_PAD_SEL_SHIFT)
#define SF_CTRL_SF_IF_PAD_SEL_LOCK                              (1<<3U)
#define SF_CTRL_SF_IF_DTR_EN                                    (1<<4U)
#define SF_CTRL_SF_IF_DQS_EN                                    (1<<5U)
#define SF_CTRL_SF_IF_TRIG_WR_PROT                              (1<<6U)
#define SF_CTRL_SF_ID_OFFSET_LOCK                               (1<<7U)
#define SF_CTRL_SF_AHB2SIF_REMAP_LOCK                           (1<<25U)
#define SF_CTRL_SF_AHB2SIF_REMAP_SHIFT                          (26U)
#define SF_CTRL_SF_AHB2SIF_REMAP_MASK                           (0x3<<SF_CTRL_SF_AHB2SIF_REMAP_SHIFT)
#define SF_CTRL_SF_IF_BK_SWAP                                   (1<<28U)
#define SF_CTRL_SF_IF_BK2_MODE                                  (1<<29U)
#define SF_CTRL_SF_IF_BK2_EN                                    (1<<30U)
#define SF_CTRL_SF_IF_0_BK_SEL                                  (1<<31U)

/* 0x74 : sf_ctrl_3 */
#define SF_CTRL_SF_CMDS_2_WRAP_LEN_SHIFT                        (0U)
#define SF_CTRL_SF_CMDS_2_WRAP_LEN_MASK                         (0xf<<SF_CTRL_SF_CMDS_2_WRAP_LEN_SHIFT)
#define SF_CTRL_SF_CMDS_2_EN                                    (1<<4U)
#define SF_CTRL_SF_CMDS_2_BT_DLY_SHIFT                          (5U)
#define SF_CTRL_SF_CMDS_2_BT_DLY_MASK                           (0x7<<SF_CTRL_SF_CMDS_2_BT_DLY_SHIFT)
#define SF_CTRL_SF_CMDS_2_BT_EN                                 (1<<8U)
#define SF_CTRL_SF_CMDS_2_WRAP_Q_INI                            (1<<9U)
#define SF_CTRL_SF_CMDS_2_WRAP_MODE_SHIFT                       (10U)
#define SF_CTRL_SF_CMDS_2_WRAP_MODE_MASK                        (0x3<<SF_CTRL_SF_CMDS_2_WRAP_MODE_SHIFT)
#define SF_CTRL_SF_CMDS_2_WRAP_Q                                (1<<12U)
#define SF_CTRL_SF_CMDS_1_WRAP_LEN_SHIFT                        (13U)
#define SF_CTRL_SF_CMDS_1_WRAP_LEN_MASK                         (0xf<<SF_CTRL_SF_CMDS_1_WRAP_LEN_SHIFT)
#define SF_CTRL_SF_CMDS_1_EN                                    (1<<17U)
#define SF_CTRL_SF_CMDS_1_WRAP_MODE_SHIFT                       (18U)
#define SF_CTRL_SF_CMDS_1_WRAP_MODE_MASK                        (0x3<<SF_CTRL_SF_CMDS_1_WRAP_MODE_SHIFT)
#define SF_CTRL_SF_CMDS_CORE_EN                                 (1<<20U)
#define SF_CTRL_SF_IF_1_ACK_LAT_SHIFT                           (29U)
#define SF_CTRL_SF_IF_1_ACK_LAT_MASK                            (0x7<<SF_CTRL_SF_IF_1_ACK_LAT_SHIFT)

/* 0x78 : sf_if_iahb_3 */
#define SF_CTRL_SF_IF_2_DMY_BYTE_SHIFT                          (12U)
#define SF_CTRL_SF_IF_2_DMY_BYTE_MASK                           (0x1f<<SF_CTRL_SF_IF_2_DMY_BYTE_SHIFT)
#define SF_CTRL_SF_IF_2_ADR_BYTE_SHIFT                          (17U)
#define SF_CTRL_SF_IF_2_ADR_BYTE_MASK                           (0x7<<SF_CTRL_SF_IF_2_ADR_BYTE_SHIFT)
#define SF_CTRL_SF_IF_2_CMD_BYTE_SHIFT                          (20U)
#define SF_CTRL_SF_IF_2_CMD_BYTE_MASK                           (0x7<<SF_CTRL_SF_IF_2_CMD_BYTE_SHIFT)
#define SF_CTRL_SF_IF_2_DAT_RW                                  (1<<23U)
#define SF_CTRL_SF_IF_2_DAT_EN                                  (1<<24U)
#define SF_CTRL_SF_IF_2_DMY_EN                                  (1<<25U)
#define SF_CTRL_SF_IF_2_ADR_EN                                  (1<<26U)
#define SF_CTRL_SF_IF_2_CMD_EN                                  (1<<27U)
#define SF_CTRL_SF_IF_2_SPI_MODE_SHIFT                          (28U)
#define SF_CTRL_SF_IF_2_SPI_MODE_MASK                           (0x7<<SF_CTRL_SF_IF_2_SPI_MODE_SHIFT)
#define SF_CTRL_SF_IF_2_QPI_MODE_EN                             (1<<31U)

/* 0x7C : sf_if_iahb_4 */
#define SF_CTRL_SF_IF_2_CMD_BUF_0_SHIFT                         (0U)
#define SF_CTRL_SF_IF_2_CMD_BUF_0_MASK                          (0xffffffffL<<SF_CTRL_SF_IF_2_CMD_BUF_0_SHIFT)

/* 0x80 : sf_if_iahb_5 */
#define SF_CTRL_SF_IF_2_CMD_BUF_1_SHIFT                         (0U)
#define SF_CTRL_SF_IF_2_CMD_BUF_1_MASK                          (0xffffffffL<<SF_CTRL_SF_IF_2_CMD_BUF_1_SHIFT)

/* 0x84 : sf_if_iahb_6 */
#define SF_CTRL_SF_IF_3_ADR_BYTE_SHIFT                          (17U)
#define SF_CTRL_SF_IF_3_ADR_BYTE_MASK                           (0x7<<SF_CTRL_SF_IF_3_ADR_BYTE_SHIFT)
#define SF_CTRL_SF_IF_3_CMD_BYTE_SHIFT                          (20U)
#define SF_CTRL_SF_IF_3_CMD_BYTE_MASK                           (0x7<<SF_CTRL_SF_IF_3_CMD_BYTE_SHIFT)
#define SF_CTRL_SF_IF_3_ADR_EN                                  (1<<26U)
#define SF_CTRL_SF_IF_3_CMD_EN                                  (1<<27U)
#define SF_CTRL_SF_IF_3_SPI_MODE_SHIFT                          (28U)
#define SF_CTRL_SF_IF_3_SPI_MODE_MASK                           (0x7<<SF_CTRL_SF_IF_3_SPI_MODE_SHIFT)
#define SF_CTRL_SF_IF_3_QPI_MODE_EN                             (1<<31U)

/* 0x88 : sf_if_iahb_7 */
#define SF_CTRL_SF_IF_3_CMD_BUF_0_SHIFT                         (0U)
#define SF_CTRL_SF_IF_3_CMD_BUF_0_MASK                          (0xffffffffL<<SF_CTRL_SF_IF_3_CMD_BUF_0_SHIFT)

/* 0x8C : sf_if_iahb_8 */
#define SF_CTRL_SF_IF_3_CMD_BUF_1_SHIFT                         (0U)
#define SF_CTRL_SF_IF_3_CMD_BUF_1_MASK                          (0xffffffffL<<SF_CTRL_SF_IF_3_CMD_BUF_1_SHIFT)

/* 0x90 : sf_if_iahb_9 */
#define SF_CTRL_SF_IF_4_DMY_BYTE_SHIFT                          (12U)
#define SF_CTRL_SF_IF_4_DMY_BYTE_MASK                           (0x1f<<SF_CTRL_SF_IF_4_DMY_BYTE_SHIFT)
#define SF_CTRL_SF_IF_4_ADR_BYTE_SHIFT                          (17U)
#define SF_CTRL_SF_IF_4_ADR_BYTE_MASK                           (0x7<<SF_CTRL_SF_IF_4_ADR_BYTE_SHIFT)
#define SF_CTRL_SF_IF_4_CMD_BYTE_SHIFT                          (20U)
#define SF_CTRL_SF_IF_4_CMD_BYTE_MASK                           (0x7<<SF_CTRL_SF_IF_4_CMD_BYTE_SHIFT)
#define SF_CTRL_SF_IF_4_DAT_RW                                  (1<<23U)
#define SF_CTRL_SF_IF_4_DAT_EN                                  (1<<24U)
#define SF_CTRL_SF_IF_4_DMY_EN                                  (1<<25U)
#define SF_CTRL_SF_IF_4_ADR_EN                                  (1<<26U)
#define SF_CTRL_SF_IF_4_CMD_EN                                  (1<<27U)
#define SF_CTRL_SF_IF_4_SPI_MODE_SHIFT                          (28U)
#define SF_CTRL_SF_IF_4_SPI_MODE_MASK                           (0x7<<SF_CTRL_SF_IF_4_SPI_MODE_SHIFT)
#define SF_CTRL_SF_IF_4_QPI_MODE_EN                             (1<<31U)

/* 0x94 : sf_if_iahb_10 */
#define SF_CTRL_SF_IF_4_CMD_BUF_0_SHIFT                         (0U)
#define SF_CTRL_SF_IF_4_CMD_BUF_0_MASK                          (0xffffffffL<<SF_CTRL_SF_IF_4_CMD_BUF_0_SHIFT)

/* 0x98 : sf_if_iahb_11 */
#define SF_CTRL_SF_IF_4_CMD_BUF_1_SHIFT                         (0U)
#define SF_CTRL_SF_IF_4_CMD_BUF_1_MASK                          (0xffffffffL<<SF_CTRL_SF_IF_4_CMD_BUF_1_SHIFT)

/* 0x9C : sf_if_iahb_12 */
#define SF_CTRL_SF2_CLK_SF_RX_INV_SEL                           (1<<2U)
#define SF_CTRL_SF2_CLK_SF_RX_INV_SRC                           (1<<3U)
#define SF_CTRL_SF2_CLK_OUT_INV_SEL                             (1<<4U)
#define SF_CTRL_SF3_CLK_OUT_INV_SEL                             (1<<5U)
#define SF_CTRL_SF2_IF_READ_DLY_N_SHIFT                         (8U)
#define SF_CTRL_SF2_IF_READ_DLY_N_MASK                          (0x7<<SF_CTRL_SF2_IF_READ_DLY_N_SHIFT)
#define SF_CTRL_SF2_IF_READ_DLY_EN                              (1<<11U)
#define SF_CTRL_SF2_IF_READ_DLY_SRC                             (1<<12U)

/* 0xA0 : sf_id0_offset */
#define SF_CTRL_SF_ID0_OFFSET_SHIFT                             (0U)
#define SF_CTRL_SF_ID0_OFFSET_MASK                              (0xfffffff<<SF_CTRL_SF_ID0_OFFSET_SHIFT)

/* 0xA4 : sf_id1_offset */
#define SF_CTRL_SF_ID1_OFFSET_SHIFT                             (0U)
#define SF_CTRL_SF_ID1_OFFSET_MASK                              (0xfffffff<<SF_CTRL_SF_ID1_OFFSET_SHIFT)

/* 0xA8 : sf_bk2_id0_offset */
#define SF_CTRL_SF_BK2_ID0_OFFSET_SHIFT                         (0U)
#define SF_CTRL_SF_BK2_ID0_OFFSET_MASK                          (0xfffffff<<SF_CTRL_SF_BK2_ID0_OFFSET_SHIFT)

/* 0xAC : sf_bk2_id1_offset */
#define SF_CTRL_SF_BK2_ID1_OFFSET_SHIFT                         (0U)
#define SF_CTRL_SF_BK2_ID1_OFFSET_MASK                          (0xfffffff<<SF_CTRL_SF_BK2_ID1_OFFSET_SHIFT)

/* 0xB0 : sf_dbg */
#define SF_CTRL_SF_AUTOLOAD_ST_SHIFT                            (0U)
#define SF_CTRL_SF_AUTOLOAD_ST_MASK                             (0x1f<<SF_CTRL_SF_AUTOLOAD_ST_SHIFT)
#define SF_CTRL_SF_AUTOLOAD_ST_DONE                             (1<<5U)

/* 0xC0 : sf_if2_ctrl_0 */
#define SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL                        (1<<2U)
#define SF_CTRL_SF_IF2_READ_DLY_N_SHIFT                         (8U)
#define SF_CTRL_SF_IF2_READ_DLY_N_MASK                          (0x7<<SF_CTRL_SF_IF2_READ_DLY_N_SHIFT)
#define SF_CTRL_SF_IF2_READ_DLY_EN                              (1<<11U)
#define SF_CTRL_SF_IF2_INT                                      (1<<16U)
#define SF_CTRL_SF_IF2_INT_CLR                                  (1<<17U)
#define SF_CTRL_SF_IF2_INT_SET                                  (1<<18U)
#define SF_CTRL_SF_IF2_REPLACE_SF1                              (1<<23U)
#define SF_CTRL_SF_IF2_REPLACE_SF2                              (1<<24U)
#define SF_CTRL_SF_IF2_REPLACE_SF3                              (1<<25U)
#define SF_CTRL_SF_IF2_PAD_SEL_SHIFT                            (26U)
#define SF_CTRL_SF_IF2_PAD_SEL_MASK                             (0x3<<SF_CTRL_SF_IF2_PAD_SEL_SHIFT)
#define SF_CTRL_SF_IF2_BK_SWAP                                  (1<<28U)
#define SF_CTRL_SF_IF2_BK2_MODE                                 (1<<29U)
#define SF_CTRL_SF_IF2_BK2_EN                                   (1<<30U)
#define SF_CTRL_SF_IF2_BK_SEL                                   (1<<31U)

/* 0xC4 : sf_if2_ctrl_1 */
#define SF_CTRL_SF_IF2_SR_PAT_MASK_SHIFT                        (0U)
#define SF_CTRL_SF_IF2_SR_PAT_MASK_MASK                         (0xff<<SF_CTRL_SF_IF2_SR_PAT_MASK_SHIFT)
#define SF_CTRL_SF_IF2_SR_PAT_SHIFT                             (8U)
#define SF_CTRL_SF_IF2_SR_PAT_MASK                              (0xff<<SF_CTRL_SF_IF2_SR_PAT_SHIFT)
#define SF_CTRL_SF_IF2_SR_INT                                   (1<<16U)
#define SF_CTRL_SF_IF2_SR_INT_EN                                (1<<17U)
#define SF_CTRL_SF_IF2_SR_INT_SET                               (1<<18U)
#define SF_CTRL_SF_IF2_ACK_LAT_SHIFT                            (20U)
#define SF_CTRL_SF_IF2_ACK_LAT_MASK                             (0x7<<SF_CTRL_SF_IF2_ACK_LAT_SHIFT)
#define SF_CTRL_SF_IF2_REG_HOLD                                 (1<<24U)
#define SF_CTRL_SF_IF2_REG_WP                                   (1<<25U)
#define SF_CTRL_SF_IF2_FN_SEL                                   (1<<28U)
#define SF_CTRL_SF_IF2_EN                                       (1<<29U)

/* 0xC8 : sf_if2_sahb_0 */
#define SF_CTRL_SF_IF2_BUSY                                     (1<<0U)
#define SF_CTRL_SF_IF2_0_TRIG                                   (1<<1U)
#define SF_CTRL_SF_IF2_0_DAT_BYTE_SHIFT                         (2U)
#define SF_CTRL_SF_IF2_0_DAT_BYTE_MASK                          (0x3ff<<SF_CTRL_SF_IF2_0_DAT_BYTE_SHIFT)
#define SF_CTRL_SF_IF2_0_DMY_BYTE_SHIFT                         (12U)
#define SF_CTRL_SF_IF2_0_DMY_BYTE_MASK                          (0x1f<<SF_CTRL_SF_IF2_0_DMY_BYTE_SHIFT)
#define SF_CTRL_SF_IF2_0_ADR_BYTE_SHIFT                         (17U)
#define SF_CTRL_SF_IF2_0_ADR_BYTE_MASK                          (0x7<<SF_CTRL_SF_IF2_0_ADR_BYTE_SHIFT)
#define SF_CTRL_SF_IF2_0_CMD_BYTE_SHIFT                         (20U)
#define SF_CTRL_SF_IF2_0_CMD_BYTE_MASK                          (0x7<<SF_CTRL_SF_IF2_0_CMD_BYTE_SHIFT)
#define SF_CTRL_SF_IF2_0_DAT_RW                                 (1<<23U)
#define SF_CTRL_SF_IF2_0_DAT_EN                                 (1<<24U)
#define SF_CTRL_SF_IF2_0_DMY_EN                                 (1<<25U)
#define SF_CTRL_SF_IF2_0_ADR_EN                                 (1<<26U)
#define SF_CTRL_SF_IF2_0_CMD_EN                                 (1<<27U)
#define SF_CTRL_SF_IF2_0_SPI_MODE_SHIFT                         (28U)
#define SF_CTRL_SF_IF2_0_SPI_MODE_MASK                          (0x7<<SF_CTRL_SF_IF2_0_SPI_MODE_SHIFT)
#define SF_CTRL_SF_IF2_0_QPI_MODE_EN                            (1<<31U)

/* 0xCC : sf_if2_sahb_1 */
#define SF_CTRL_SF_IF2_0_CMD_BUF_0_SHIFT                        (0U)
#define SF_CTRL_SF_IF2_0_CMD_BUF_0_MASK                         (0xffffffffL<<SF_CTRL_SF_IF2_0_CMD_BUF_0_SHIFT)

/* 0xD0 : sf_if2_sahb_2 */
#define SF_CTRL_SF_IF2_0_CMD_BUF_1_SHIFT                        (0U)
#define SF_CTRL_SF_IF2_0_CMD_BUF_1_MASK                         (0xffffffffL<<SF_CTRL_SF_IF2_0_CMD_BUF_1_SHIFT)

/* 0x100 : sf_ctrl_prot_en_rd */
#define SF_CTRL_ID0_EN_RD                                       (1<<1U)
#define SF_CTRL_ID1_EN_RD                                       (1<<2U)
#define SF_CTRL_SF_SEC_TZSID_LOCK                               (1<<28U)
#define SF_CTRL_SF_IF2_0_TRIG_WR_LOCK                           (1<<29U)
#define SF_CTRL_SF_IF_0_TRIG_WR_LOCK                            (1<<30U)
#define SF_CTRL_SF_DBG_DIS                                      (1<<31U)

/* 0x104 : sf_ctrl_prot_en */
#define SF_CTRL_ID0_EN                                          (1<<1U)
#define SF_CTRL_ID1_EN                                          (1<<2U)

/* 0x200 : sf_aes_key_r0_0 */
#define SF_CTRL_SF_AES_KEY_R0_0_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R0_0_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R0_0_SHIFT)

/* 0x204 : sf_aes_key_r0_1 */
#define SF_CTRL_SF_AES_KEY_R0_1_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R0_1_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R0_1_SHIFT)

/* 0x208 : sf_aes_key_r0_2 */
#define SF_CTRL_SF_AES_KEY_R0_2_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R0_2_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R0_2_SHIFT)

/* 0x20C : sf_aes_key_r0_3 */
#define SF_CTRL_SF_AES_KEY_R0_3_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R0_3_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R0_3_SHIFT)

/* 0x210 : sf_aes_key_r0_4 */
#define SF_CTRL_SF_AES_KEY_R0_4_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R0_4_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R0_4_SHIFT)

/* 0x214 : sf_aes_key_r0_5 */
#define SF_CTRL_SF_AES_KEY_R0_5_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R0_5_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R0_5_SHIFT)

/* 0x218 : sf_aes_key_r0_6 */
#define SF_CTRL_SF_AES_KEY_R0_6_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R0_6_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R0_6_SHIFT)

/* 0x21C : sf_aes_key_r0_7 */
#define SF_CTRL_SF_AES_KEY_R0_7_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R0_7_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R0_7_SHIFT)

/* 0x220 : sf_aes_iv_r0_w0 */
#define SF_CTRL_SF_AES_IV_R0_W0_SHIFT                           (0U)
#define SF_CTRL_SF_AES_IV_R0_W0_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_IV_R0_W0_SHIFT)

/* 0x224 : sf_aes_iv_r0_w1 */
#define SF_CTRL_SF_AES_IV_R0_W1_SHIFT                           (0U)
#define SF_CTRL_SF_AES_IV_R0_W1_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_IV_R0_W1_SHIFT)

/* 0x228 : sf_aes_iv_r0_w2 */
#define SF_CTRL_SF_AES_IV_R0_W2_SHIFT                           (0U)
#define SF_CTRL_SF_AES_IV_R0_W2_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_IV_R0_W2_SHIFT)

/* 0x22C : sf_aes_iv_r0_w3 */
#define SF_CTRL_SF_AES_IV_R0_W3_SHIFT                           (0U)
#define SF_CTRL_SF_AES_IV_R0_W3_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_IV_R0_W3_SHIFT)

/* 0x230 : sf_aes_r0_start */
#define SF_CTRL_SF_AES_REGION_R0_START_SHIFT                    (0U)
#define SF_CTRL_SF_AES_REGION_R0_START_MASK                     (0x7ffff<<SF_CTRL_SF_AES_REGION_R0_START_SHIFT)
#define SF_CTRL_SF_AES_REGION_R0_HW_KEY_EN                      (1<<29U)
#define SF_CTRL_SF_AES_REGION_R0_EN                             (1<<30U)
#define SF_CTRL_SF_AES_REGION_R0_LOCK                           (1<<31U)

/* 0x234 : sf_aes_r0_end */
#define SF_CTRL_SF_AES_REGION_R0_END_SHIFT                      (0U)
#define SF_CTRL_SF_AES_REGION_R0_END_MASK                       (0x7ffff<<SF_CTRL_SF_AES_REGION_R0_END_SHIFT)

/* 0x280 : sf_aes_key_r1_0 */
#define SF_CTRL_SF_AES_KEY_R1_0_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R1_0_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R1_0_SHIFT)

/* 0x284 : sf_aes_key_r1_1 */
#define SF_CTRL_SF_AES_KEY_R1_1_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R1_1_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R1_1_SHIFT)

/* 0x288 : sf_aes_key_r1_2 */
#define SF_CTRL_SF_AES_KEY_R1_2_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R1_2_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R1_2_SHIFT)

/* 0x28C : sf_aes_key_r1_3 */
#define SF_CTRL_SF_AES_KEY_R1_3_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R1_3_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R1_3_SHIFT)

/* 0x290 : sf_aes_key_r1_4 */
#define SF_CTRL_SF_AES_KEY_R1_4_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R1_4_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R1_4_SHIFT)

/* 0x294 : sf_aes_key_r1_5 */
#define SF_CTRL_SF_AES_KEY_R1_5_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R1_5_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R1_5_SHIFT)

/* 0x298 : sf_aes_key_r1_6 */
#define SF_CTRL_SF_AES_KEY_R1_6_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R1_6_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R1_6_SHIFT)

/* 0x29C : sf_aes_key_r1_7 */
#define SF_CTRL_SF_AES_KEY_R1_7_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R1_7_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R1_7_SHIFT)

/* 0x2A0 : sf_aes_iv_r1_w0 */
#define SF_CTRL_SF_AES_IV_R1_W0_SHIFT                           (0U)
#define SF_CTRL_SF_AES_IV_R1_W0_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_IV_R1_W0_SHIFT)

/* 0x2A4 : sf_aes_iv_r1_w1 */
#define SF_CTRL_SF_AES_IV_R1_W1_SHIFT                           (0U)
#define SF_CTRL_SF_AES_IV_R1_W1_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_IV_R1_W1_SHIFT)

/* 0x2A8 : sf_aes_iv_r1_w2 */
#define SF_CTRL_SF_AES_IV_R1_W2_SHIFT                           (0U)
#define SF_CTRL_SF_AES_IV_R1_W2_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_IV_R1_W2_SHIFT)

/* 0x2AC : sf_aes_iv_r1_w3 */
#define SF_CTRL_SF_AES_IV_R1_W3_SHIFT                           (0U)
#define SF_CTRL_SF_AES_IV_R1_W3_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_IV_R1_W3_SHIFT)

/* 0x2B0 : sf_aes_r1_start */
#define SF_CTRL_SF_AES_R1_START_SHIFT                           (0U)
#define SF_CTRL_SF_AES_R1_START_MASK                            (0x7ffff<<SF_CTRL_SF_AES_R1_START_SHIFT)
#define SF_CTRL_SF_AES_R1_HW_KEY_EN                             (1<<29U)
#define SF_CTRL_SF_AES_R1_EN                                    (1<<30U)
#define SF_CTRL_SF_AES_R1_LOCK                                  (1<<31U)

/* 0x2B4 : sf_aes_r1_end */
#define SF_CTRL_SF_AES_R1_END_SHIFT                             (0U)
#define SF_CTRL_SF_AES_R1_END_MASK                              (0x7ffff<<SF_CTRL_SF_AES_R1_END_SHIFT)

/* 0x300 : sf_aes_key_r2_0 */
#define SF_CTRL_SF_AES_KEY_R2_0_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R2_0_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R2_0_SHIFT)

/* 0x304 : sf_aes_key_r2_1 */
#define SF_CTRL_SF_AES_KEY_R2_1_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R2_1_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R2_1_SHIFT)

/* 0x308 : sf_aes_key_r2_2 */
#define SF_CTRL_SF_AES_KEY_R2_2_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R2_2_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R2_2_SHIFT)

/* 0x30C : sf_aes_key_r2_3 */
#define SF_CTRL_SF_AES_KEY_R2_3_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R2_3_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R2_3_SHIFT)

/* 0x310 : sf_aes_key_r2_4 */
#define SF_CTRL_SF_AES_KEY_R2_4_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R2_4_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R2_4_SHIFT)

/* 0x314 : sf_aes_key_r2_5 */
#define SF_CTRL_SF_AES_KEY_R2_5_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R2_5_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R2_5_SHIFT)

/* 0x318 : sf_aes_key_r2_6 */
#define SF_CTRL_SF_AES_KEY_R2_6_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R2_6_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R2_6_SHIFT)

/* 0x31C : sf_aes_key_r2_7 */
#define SF_CTRL_SF_AES_KEY_R2_7_SHIFT                           (0U)
#define SF_CTRL_SF_AES_KEY_R2_7_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_KEY_R2_7_SHIFT)

/* 0x320 : sf_aes_iv_r2_w0 */
#define SF_CTRL_SF_AES_IV_R2_W0_SHIFT                           (0U)
#define SF_CTRL_SF_AES_IV_R2_W0_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_IV_R2_W0_SHIFT)

/* 0x324 : sf_aes_iv_r2_w1 */
#define SF_CTRL_SF_AES_IV_R2_W1_SHIFT                           (0U)
#define SF_CTRL_SF_AES_IV_R2_W1_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_IV_R2_W1_SHIFT)

/* 0x328 : sf_aes_iv_r2_w2 */
#define SF_CTRL_SF_AES_IV_R2_W2_SHIFT                           (0U)
#define SF_CTRL_SF_AES_IV_R2_W2_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_IV_R2_W2_SHIFT)

/* 0x32C : sf_aes_iv_r2_w3 */
#define SF_CTRL_SF_AES_IV_R2_W3_SHIFT                           (0U)
#define SF_CTRL_SF_AES_IV_R2_W3_MASK                            (0xffffffffL<<SF_CTRL_SF_AES_IV_R2_W3_SHIFT)

/* 0x330 : sf_aes_r2_start */
#define SF_CTRL_SF_AES_R2_START_SHIFT                           (0U)
#define SF_CTRL_SF_AES_R2_START_MASK                            (0x7ffff<<SF_CTRL_SF_AES_R2_START_SHIFT)
#define SF_CTRL_SF_AES_R2_HW_KEY_EN                             (1<<29U)
#define SF_CTRL_SF_AES_R2_EN                                    (1<<30U)
#define SF_CTRL_SF_AES_R2_LOCK                                  (1<<31U)

/* 0x334 : sf_aes_r2_end */
#define SF_CTRL_SF_AES_R2_END_SHIFT                             (0U)
#define SF_CTRL_SF_AES_R2_END_MASK                              (0x7ffff<<SF_CTRL_SF_AES_R2_END_SHIFT)



/*Following is reg patch*/

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define SF_CTRL_IF_SAHB_0_OFFSET                                (0x0)/* sf_if_sahb_0 */
#define SF_CTRL_IF_SAHB_1_OFFSET                                (0x4)/* sf_if_sahb_1 */
#define SF_CTRL_IF_SAHB_2_OFFSET                                (0x8)/* sf_if_sahb_2 */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : sf_if_sahb_0 */
#define SF_CTRL_IF_BUSY                                         (1<<0U)
#define SF_CTRL_IF_0_TRIG                                       (1<<1U)
#define SF_CTRL_IF_0_DAT_BYTE_SHIFT                             (2U)
#define SF_CTRL_IF_0_DAT_BYTE_MASK                              (0x3ff<<SF_CTRL_IF_0_DAT_BYTE_SHIFT)
#define SF_CTRL_IF_0_DMY_BYTE_SHIFT                             (12U)
#define SF_CTRL_IF_0_DMY_BYTE_MASK                              (0x1f<<SF_CTRL_IF_0_DMY_BYTE_SHIFT)
#define SF_CTRL_IF_0_ADR_BYTE_SHIFT                             (17U)
#define SF_CTRL_IF_0_ADR_BYTE_MASK                              (0x7<<SF_CTRL_IF_0_ADR_BYTE_SHIFT)
#define SF_CTRL_IF_0_CMD_BYTE_SHIFT                             (20U)
#define SF_CTRL_IF_0_CMD_BYTE_MASK                              (0x7<<SF_CTRL_IF_0_CMD_BYTE_SHIFT)
#define SF_CTRL_IF_0_DAT_RW                                     (1<<23U)
#define SF_CTRL_IF_0_DAT_EN                                     (1<<24U)
#define SF_CTRL_IF_0_DMY_EN                                     (1<<25U)
#define SF_CTRL_IF_0_ADR_EN                                     (1<<26U)
#define SF_CTRL_IF_0_CMD_EN                                     (1<<27U)
#define SF_CTRL_IF_0_SPI_MODE_SHIFT                             (28U)
#define SF_CTRL_IF_0_SPI_MODE_MASK                              (0x7<<SF_CTRL_IF_0_SPI_MODE_SHIFT)
#define SF_CTRL_IF_0_QPI_MODE_EN                                (1<<31U)

/* 0x4 : sf_if_sahb_1 */
#define SF_CTRL_IF_0_CMD_BUF_0_SHIFT                            (0U)
#define SF_CTRL_IF_0_CMD_BUF_0_MASK                             (0xffffffffL<<SF_CTRL_IF_0_CMD_BUF_0_SHIFT)

/* 0x8 : sf_if_sahb_2 */
#define SF_CTRL_IF_0_CMD_BUF_1_SHIFT                            (0U)
#define SF_CTRL_IF_0_CMD_BUF_1_MASK                             (0xffffffffL<<SF_CTRL_IF_0_CMD_BUF_1_SHIFT)


#define SF_CTRL_IF1_SAHB_OFFSET     0x8
#define SF_CTRL_IF2_SAHB_OFFSET     0xC8


/*Following is reg patch*/

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define SF_CTRL_IO_DLY_0_OFFSET                                 (0x0)/* if_io_dly_0 */
#define SF_CTRL_IO_DLY_1_OFFSET                                 (0x4)/* if_io_dly_1 */
#define SF_CTRL_IO_DLY_2_OFFSET                                 (0x8)/* if_io_dly_2 */
#define SF_CTRL_IO_DLY_3_OFFSET                                 (0xc)/* if_io_dly_3 */
#define SF_CTRL_IO_DLY_4_OFFSET                                 (0x10)/* if_io_dly_4 */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : if_io_dly_0 */
#define SF_CTRL_CS_DLY_SEL_SHIFT                                (0U)
#define SF_CTRL_CS_DLY_SEL_MASK                                 (0x3<<SF_CTRL_CS_DLY_SEL_SHIFT)
#define SF_CTRL_CS2_DLY_SEL_SHIFT                               (2U)
#define SF_CTRL_CS2_DLY_SEL_MASK                                (0x3<<SF_CTRL_CS2_DLY_SEL_SHIFT)
#define SF_CTRL_CLK_OUT_DLY_SEL_SHIFT                           (8U)
#define SF_CTRL_CLK_OUT_DLY_SEL_MASK                            (0x3<<SF_CTRL_CLK_OUT_DLY_SEL_SHIFT)
#define SF_CTRL_DQS_OE_DLY_SEL_SHIFT                            (26U)
#define SF_CTRL_DQS_OE_DLY_SEL_MASK                             (0x3<<SF_CTRL_DQS_OE_DLY_SEL_SHIFT)
#define SF_CTRL_DQS_DI_DLY_SEL_SHIFT                            (28U)
#define SF_CTRL_DQS_DI_DLY_SEL_MASK                             (0x3<<SF_CTRL_DQS_DI_DLY_SEL_SHIFT)
#define SF_CTRL_DQS_DO_DLY_SEL_SHIFT                            (30U)
#define SF_CTRL_DQS_DO_DLY_SEL_MASK                             (0x3<<SF_CTRL_DQS_DO_DLY_SEL_SHIFT)

/* 0x4 : if_io_dly_1 */
#define SF_CTRL_IO_0_OE_DLY_SEL_SHIFT                           (0U)
#define SF_CTRL_IO_0_OE_DLY_SEL_MASK                            (0x3<<SF_CTRL_IO_0_OE_DLY_SEL_SHIFT)
#define SF_CTRL_IO_0_DI_DLY_SEL_SHIFT                           (8U)
#define SF_CTRL_IO_0_DI_DLY_SEL_MASK                            (0x3<<SF_CTRL_IO_0_DI_DLY_SEL_SHIFT)
#define SF_CTRL_IO_0_DO_DLY_SEL_SHIFT                           (16U)
#define SF_CTRL_IO_0_DO_DLY_SEL_MASK                            (0x3<<SF_CTRL_IO_0_DO_DLY_SEL_SHIFT)

/* 0x8 : if_io_dly_2 */
#define SF_CTRL_IO_1_OE_DLY_SEL_SHIFT                           (0U)
#define SF_CTRL_IO_1_OE_DLY_SEL_MASK                            (0x3<<SF_CTRL_IO_1_OE_DLY_SEL_SHIFT)
#define SF_CTRL_IO_1_DI_DLY_SEL_SHIFT                           (8U)
#define SF_CTRL_IO_1_DI_DLY_SEL_MASK                            (0x3<<SF_CTRL_IO_1_DI_DLY_SEL_SHIFT)
#define SF_CTRL_IO_1_DO_DLY_SEL_SHIFT                           (16U)
#define SF_CTRL_IO_1_DO_DLY_SEL_MASK                            (0x3<<SF_CTRL_IO_1_DO_DLY_SEL_SHIFT)

/* 0xc : if_io_dly_3 */
#define SF_CTRL_IO_2_OE_DLY_SEL_SHIFT                           (0U)
#define SF_CTRL_IO_2_OE_DLY_SEL_MASK                            (0x3<<SF_CTRL_IO_2_OE_DLY_SEL_SHIFT)
#define SF_CTRL_IO_2_DI_DLY_SEL_SHIFT                           (8U)
#define SF_CTRL_IO_2_DI_DLY_SEL_MASK                            (0x3<<SF_CTRL_IO_2_DI_DLY_SEL_SHIFT)
#define SF_CTRL_IO_2_DO_DLY_SEL_SHIFT                           (16U)
#define SF_CTRL_IO_2_DO_DLY_SEL_MASK                            (0x3<<SF_CTRL_IO_2_DO_DLY_SEL_SHIFT)

/* 0x10 : if_io_dly_4 */
#define SF_CTRL_IO_3_OE_DLY_SEL_SHIFT                           (0U)
#define SF_CTRL_IO_3_OE_DLY_SEL_MASK                            (0x3<<SF_CTRL_IO_3_OE_DLY_SEL_SHIFT)
#define SF_CTRL_IO_3_DI_DLY_SEL_SHIFT                           (8U)
#define SF_CTRL_IO_3_DI_DLY_SEL_MASK                            (0x3<<SF_CTRL_IO_3_DI_DLY_SEL_SHIFT)
#define SF_CTRL_IO_3_DO_DLY_SEL_SHIFT                           (16U)
#define SF_CTRL_IO_3_DO_DLY_SEL_MASK                            (0x3<<SF_CTRL_IO_3_DO_DLY_SEL_SHIFT)


#define SF_CTRL_IF_IO_DLY_1_OFFSET     0x30
#define SF_CTRL_IF_IO_DLY_2_OFFSET     0x48
#define SF_CTRL_IF_IO_DLY_3_OFFSET     0x5C


/*Following is reg patch*/

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define SF_CTRL_SF_AES_KEY_0_OFFSET                             (0x0)/* sf_aes_key_0 */
#define SF_CTRL_SF_AES_KEY_1_OFFSET                             (0x4)/* sf_aes_key_1 */
#define SF_CTRL_SF_AES_KEY_2_OFFSET                             (0x8)/* sf_aes_key_2 */
#define SF_CTRL_SF_AES_KEY_3_OFFSET                             (0xc)/* sf_aes_key_3 */
#define SF_CTRL_SF_AES_KEY_4_OFFSET                             (0x10)/* sf_aes_key_4 */
#define SF_CTRL_SF_AES_KEY_5_OFFSET                             (0x14)/* sf_aes_key_5 */
#define SF_CTRL_SF_AES_KEY_6_OFFSET                             (0x18)/* sf_aes_key_6 */
#define SF_CTRL_SF_AES_KEY_7_OFFSET                             (0x1c)/* sf_aes_key_7 */
#define SF_CTRL_SF_AES_IV_W0_OFFSET                             (0x20)/* sf_aes_iv_w0 */
#define SF_CTRL_SF_AES_IV_W1_OFFSET                             (0x24)/* sf_aes_iv_w1 */
#define SF_CTRL_SF_AES_IV_W2_OFFSET                             (0x28)/* sf_aes_iv_w2 */
#define SF_CTRL_SF_AES_IV_W3_OFFSET                             (0x2c)/* sf_aes_iv_w3 */
#define SF_CTRL_SF_AES_START_OFFSET                             (0x30)/* sf_aes_start */
#define SF_CTRL_SF_AES_END_OFFSET                               (0x34)/* sf_aes_end */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : sf_aes_key_0 */
#define SF_CTRL_SF_AES_KEY_0_SHIFT                              (0U)
#define SF_CTRL_SF_AES_KEY_0_MASK                               (0xffffffffL<<SF_CTRL_SF_AES_KEY_0_SHIFT)

/* 0x4 : sf_aes_key_1 */
#define SF_CTRL_SF_AES_KEY_1_SHIFT                              (0U)
#define SF_CTRL_SF_AES_KEY_1_MASK                               (0xffffffffL<<SF_CTRL_SF_AES_KEY_1_SHIFT)

/* 0x8 : sf_aes_key_2 */
#define SF_CTRL_SF_AES_KEY_2_SHIFT                              (0U)
#define SF_CTRL_SF_AES_KEY_2_MASK                               (0xffffffffL<<SF_CTRL_SF_AES_KEY_2_SHIFT)

/* 0xc : sf_aes_key_3 */
#define SF_CTRL_SF_AES_KEY_3_SHIFT                              (0U)
#define SF_CTRL_SF_AES_KEY_3_MASK                               (0xffffffffL<<SF_CTRL_SF_AES_KEY_3_SHIFT)

/* 0x10 : sf_aes_key_4 */
#define SF_CTRL_SF_AES_KEY_4_SHIFT                              (0U)
#define SF_CTRL_SF_AES_KEY_4_MASK                               (0xffffffffL<<SF_CTRL_SF_AES_KEY_4_SHIFT)

/* 0x14 : sf_aes_key_5 */
#define SF_CTRL_SF_AES_KEY_5_SHIFT                              (0U)
#define SF_CTRL_SF_AES_KEY_5_MASK                               (0xffffffffL<<SF_CTRL_SF_AES_KEY_5_SHIFT)

/* 0x18 : sf_aes_key_6 */
#define SF_CTRL_SF_AES_KEY_6_SHIFT                              (0U)
#define SF_CTRL_SF_AES_KEY_6_MASK                               (0xffffffffL<<SF_CTRL_SF_AES_KEY_6_SHIFT)

/* 0x1c : sf_aes_key_7 */
#define SF_CTRL_SF_AES_KEY_7_SHIFT                              (0U)
#define SF_CTRL_SF_AES_KEY_7_MASK                               (0xffffffffL<<SF_CTRL_SF_AES_KEY_7_SHIFT)

/* 0x20 : sf_aes_iv_w0 */
#define SF_CTRL_SF_AES_IV_W0_SHIFT                              (0U)
#define SF_CTRL_SF_AES_IV_W0_MASK                               (0xffffffffL<<SF_CTRL_SF_AES_IV_W0_SHIFT)

/* 0x24 : sf_aes_iv_w1 */
#define SF_CTRL_SF_AES_IV_W1_SHIFT                              (0U)
#define SF_CTRL_SF_AES_IV_W1_MASK                               (0xffffffffL<<SF_CTRL_SF_AES_IV_W1_SHIFT)

/* 0x28 : sf_aes_iv_w2 */
#define SF_CTRL_SF_AES_IV_W2_SHIFT                              (0U)
#define SF_CTRL_SF_AES_IV_W2_MASK                               (0xffffffffL<<SF_CTRL_SF_AES_IV_W2_SHIFT)

/* 0x2c : sf_aes_iv_w3 */
#define SF_CTRL_SF_AES_IV_W3_SHIFT                              (0U)
#define SF_CTRL_SF_AES_IV_W3_MASK                               (0xffffffffL<<SF_CTRL_SF_AES_IV_W3_SHIFT)

/* 0x30 : sf_aes_start */
#define SF_CTRL_SF_AES_REGION_START_SHIFT                       (0U)
#define SF_CTRL_SF_AES_REGION_START_MASK                        (0x7ffff<<SF_CTRL_SF_AES_REGION_START_SHIFT)
#define SF_CTRL_SF_AES_REGION_HW_KEY_EN                         (1<<29U)
#define SF_CTRL_SF_AES_REGION_EN                                (1<<30U)
#define SF_CTRL_SF_AES_REGION_LOCK                              (1<<31U)

/* 0x34 : sf_aes_end */
#define SF_CTRL_SF_AES_REGION_END_SHIFT                         (0U)
#define SF_CTRL_SF_AES_REGION_END_MASK                          (0x7ffff<<SF_CTRL_SF_AES_REGION_END_SHIFT)


#define SF_CTRL_AES_REGION_OFFSET     0x200

#endif  /* __SF_CTRL_REG_H__ */
