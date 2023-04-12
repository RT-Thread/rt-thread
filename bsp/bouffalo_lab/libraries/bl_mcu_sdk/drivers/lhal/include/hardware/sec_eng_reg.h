/**
  ******************************************************************************
  * @file    sec_eng_reg.h
  * @version V1.0
  * @date    2022-08-15
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
#ifndef __HARDWARE_SEC_ENG_H__
#define __HARDWARE_SEC_ENG_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define SEC_ENG_SE_SHA_0_CTRL_OFFSET        (0x0)   /* se_sha_0_ctrl */
#define SEC_ENG_SE_SHA_0_MSA_OFFSET         (0x4)   /* se_sha_0_msa */
#define SEC_ENG_SE_SHA_0_STATUS_OFFSET      (0x8)   /* se_sha_0_status */
#define SEC_ENG_SE_SHA_0_ENDIAN_OFFSET      (0xC)   /* se_sha_0_endian */
#define SEC_ENG_SE_SHA_0_HASH_L_0_OFFSET    (0x10)  /* se_sha_0_hash_l_0 */
#define SEC_ENG_SE_SHA_0_HASH_L_1_OFFSET    (0x14)  /* se_sha_0_hash_l_1 */
#define SEC_ENG_SE_SHA_0_HASH_L_2_OFFSET    (0x18)  /* se_sha_0_hash_l_2 */
#define SEC_ENG_SE_SHA_0_HASH_L_3_OFFSET    (0x1C)  /* se_sha_0_hash_l_3 */
#define SEC_ENG_SE_SHA_0_HASH_L_4_OFFSET    (0x20)  /* se_sha_0_hash_l_4 */
#define SEC_ENG_SE_SHA_0_HASH_L_5_OFFSET    (0x24)  /* se_sha_0_hash_l_5 */
#define SEC_ENG_SE_SHA_0_HASH_L_6_OFFSET    (0x28)  /* se_sha_0_hash_l_6 */
#define SEC_ENG_SE_SHA_0_HASH_L_7_OFFSET    (0x2C)  /* se_sha_0_hash_l_7 */
#define SEC_ENG_SE_SHA_0_HASH_H_0_OFFSET    (0x30)  /* se_sha_0_hash_h_0 */
#define SEC_ENG_SE_SHA_0_HASH_H_1_OFFSET    (0x34)  /* se_sha_0_hash_h_1 */
#define SEC_ENG_SE_SHA_0_HASH_H_2_OFFSET    (0x38)  /* se_sha_0_hash_h_2 */
#define SEC_ENG_SE_SHA_0_HASH_H_3_OFFSET    (0x3C)  /* se_sha_0_hash_h_3 */
#define SEC_ENG_SE_SHA_0_HASH_H_4_OFFSET    (0x40)  /* se_sha_0_hash_h_4 */
#define SEC_ENG_SE_SHA_0_HASH_H_5_OFFSET    (0x44)  /* se_sha_0_hash_h_5 */
#define SEC_ENG_SE_SHA_0_HASH_H_6_OFFSET    (0x48)  /* se_sha_0_hash_h_6 */
#define SEC_ENG_SE_SHA_0_HASH_H_7_OFFSET    (0x4C)  /* se_sha_0_hash_h_7 */
#define SEC_ENG_SE_SHA_0_LINK_OFFSET        (0x50)  /* se_sha_0_link */
#define SEC_ENG_SE_SHA_0_CTRL_PROT_OFFSET   (0xFC)  /* se_sha_0_ctrl_prot */
#define SEC_ENG_SE_AES_0_CTRL_OFFSET        (0x100) /* se_aes_0_ctrl */
#define SEC_ENG_SE_AES_0_MSA_OFFSET         (0x104) /* se_aes_0_msa */
#define SEC_ENG_SE_AES_0_MDA_OFFSET         (0x108) /* se_aes_0_mda */
#define SEC_ENG_SE_AES_0_STATUS_OFFSET      (0x10C) /* se_aes_0_status */
#define SEC_ENG_SE_AES_0_IV_0_OFFSET        (0x110) /* se_aes_0_iv_0 */
#define SEC_ENG_SE_AES_0_IV_1_OFFSET        (0x114) /* se_aes_0_iv_1 */
#define SEC_ENG_SE_AES_0_IV_2_OFFSET        (0x118) /* se_aes_0_iv_2 */
#define SEC_ENG_SE_AES_0_IV_3_OFFSET        (0x11C) /* se_aes_0_iv_3 */
#define SEC_ENG_SE_AES_0_KEY_0_OFFSET       (0x120) /* se_aes_0_key_0 */
#define SEC_ENG_SE_AES_0_KEY_1_OFFSET       (0x124) /* se_aes_0_key_1 */
#define SEC_ENG_SE_AES_0_KEY_2_OFFSET       (0x128) /* se_aes_0_key_2 */
#define SEC_ENG_SE_AES_0_KEY_3_OFFSET       (0x12C) /* se_aes_0_key_3 */
#define SEC_ENG_SE_AES_0_KEY_4_OFFSET       (0x130) /* se_aes_0_key_4 */
#define SEC_ENG_SE_AES_0_KEY_5_OFFSET       (0x134) /* se_aes_0_key_5 */
#define SEC_ENG_SE_AES_0_KEY_6_OFFSET       (0x138) /* se_aes_0_key_6 */
#define SEC_ENG_SE_AES_0_KEY_7_OFFSET       (0x13C) /* se_aes_0_key_7 */
#define SEC_ENG_SE_AES_0_KEY_SEL_OFFSET     (0x140) /* se_aes_0_key_sel */
#define SEC_ENG_SE_AES_1_KEY_SEL_OFFSET     (0x144) /* se_aes_1_key_sel */
#define SEC_ENG_SE_AES_0_ENDIAN_OFFSET      (0x148) /* se_aes_0_endian */
#define SEC_ENG_SE_AES_0_SBOOT_OFFSET       (0x14C) /* se_aes_0_sboot */
#define SEC_ENG_SE_AES_0_LINK_OFFSET        (0x150) /* se_aes_0_link */
#define SEC_ENG_SE_AES_0_CTRL_PROT_OFFSET   (0x1FC) /* se_aes_0_ctrl_prot */
#define SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET     (0x200) /* se_trng_0_ctrl_0 */
#define SEC_ENG_SE_TRNG_0_STATUS_OFFSET     (0x204) /* se_trng_0_status */
#define SEC_ENG_SE_TRNG_0_DOUT_0_OFFSET     (0x208) /* se_trng_0_dout_0 */
#define SEC_ENG_SE_TRNG_0_DOUT_1_OFFSET     (0x20C) /* se_trng_0_dout_1 */
#define SEC_ENG_SE_TRNG_0_DOUT_2_OFFSET     (0x210) /* se_trng_0_dout_2 */
#define SEC_ENG_SE_TRNG_0_DOUT_3_OFFSET     (0x214) /* se_trng_0_dout_3 */
#define SEC_ENG_SE_TRNG_0_DOUT_4_OFFSET     (0x218) /* se_trng_0_dout_4 */
#define SEC_ENG_SE_TRNG_0_DOUT_5_OFFSET     (0x21C) /* se_trng_0_dout_5 */
#define SEC_ENG_SE_TRNG_0_DOUT_6_OFFSET     (0x220) /* se_trng_0_dout_6 */
#define SEC_ENG_SE_TRNG_0_DOUT_7_OFFSET     (0x224) /* se_trng_0_dout_7 */
#define SEC_ENG_SE_TRNG_0_TEST_OFFSET       (0x228) /* se_trng_0_test */
#define SEC_ENG_SE_TRNG_0_CTRL_1_OFFSET     (0x22C) /* se_trng_0_ctrl_1 */
#define SEC_ENG_SE_TRNG_0_CTRL_2_OFFSET     (0x230) /* se_trng_0_ctrl_2 */
#define SEC_ENG_SE_TRNG_0_CTRL_3_OFFSET     (0x234) /* se_trng_0_ctrl_3 */
#define SEC_ENG_SE_TRNG_0_TEST_OUT_0_OFFSET (0x240) /* se_trng_0_test_out_0 */
#define SEC_ENG_SE_TRNG_0_TEST_OUT_1_OFFSET (0x244) /* se_trng_0_test_out_1 */
#define SEC_ENG_SE_TRNG_0_TEST_OUT_2_OFFSET (0x248) /* se_trng_0_test_out_2 */
#define SEC_ENG_SE_TRNG_0_TEST_OUT_3_OFFSET (0x24C) /* se_trng_0_test_out_3 */
#define SEC_ENG_SE_TRNG_0_CTRL_PROT_OFFSET  (0x2FC) /* se_trng_0_ctrl_prot */
#define SEC_ENG_SE_PKA_0_CTRL_0_OFFSET      (0x300) /* se_pka_0_ctrl_0 */
#define SEC_ENG_SE_PKA_0_SEED_OFFSET        (0x30C) /* se_pka_0_seed */
#define SEC_ENG_SE_PKA_0_CTRL_1_OFFSET      (0x310) /* se_pka_0_ctrl_1 */
#define SEC_ENG_SE_PKA_0_RW_OFFSET          (0x340) /* se_pka_0_rw */
#define SEC_ENG_SE_PKA_0_RW_BURST_OFFSET    (0x360) /* se_pka_0_rw_burst */
#define SEC_ENG_SE_PKA_0_CTRL_PROT_OFFSET   (0x3FC) /* se_pka_0_ctrl_prot */
#define SEC_ENG_SE_CDET_0_CTRL_0_OFFSET     (0x400) /* se_cdet_0_ctrl_0 */
#define SEC_ENG_SE_CDET_0_CTRL_1_OFFSET     (0x404) /* se_cdet_0_ctrl_1 */
#define SEC_ENG_SE_CDET_0_CTRL_2_OFFSET     (0x408) /* se_cdet_0_ctrl_2 */
#define SEC_ENG_SE_CDET_0_CTRL_3_OFFSET     (0x40C) /* se_cdet_0_ctrl_3 */
#define SEC_ENG_SE_CDET_0_CTRL_PROT_OFFSET  (0x4FC) /* se_cdet_0_ctrl_prot */
#define SEC_ENG_SE_GMAC_0_CTRL_0_OFFSET     (0x500) /* se_gmac_0_ctrl_0 */
#define SEC_ENG_SE_GMAC_0_LCA_OFFSET        (0x504) /* se_gmac_0_lca */
#define SEC_ENG_SE_GMAC_0_STATUS_OFFSET     (0x508) /* se_gmac_0_status */
#define SEC_ENG_SE_GMAC_0_CTRL_PROT_OFFSET  (0x5FC) /* se_gmac_0_ctrl_prot */
#define SEC_ENG_SE_CTRL_PROT_RD_OFFSET      (0xF00) /* se_ctrl_prot_rd */
#define SEC_ENG_SE_CTRL_RESERVED_0_OFFSET   (0xF04) /* se_ctrl_reserved_0 */
#define SEC_ENG_SE_CTRL_RESERVED_1_OFFSET   (0xF08) /* se_ctrl_reserved_1 */
#define SEC_ENG_SE_CTRL_RESERVED_2_OFFSET   (0xF0C) /* se_ctrl_reserved_2 */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : se_sha_0_ctrl */
#define SEC_ENG_SE_SHA_0_BUSY           (1 << 0U)
#define SEC_ENG_SE_SHA_0_TRIG_1T        (1 << 1U)
#define SEC_ENG_SE_SHA_0_MODE_SHIFT     (2U)
#define SEC_ENG_SE_SHA_0_MODE_MASK      (0x7 << SEC_ENG_SE_SHA_0_MODE_SHIFT)
#define SEC_ENG_SE_SHA_0_EN             (1 << 5U)
#define SEC_ENG_SE_SHA_0_HASH_SEL       (1 << 6U)
#define SEC_ENG_SE_SHA_0_INT            (1 << 8U)
#define SEC_ENG_SE_SHA_0_INT_CLR_1T     (1 << 9U)
#define SEC_ENG_SE_SHA_0_INT_SET_1T     (1 << 10U)
#define SEC_ENG_SE_SHA_0_INT_MASK       (1 << 11U)
#define SEC_ENG_SE_SHA_0_MODE_EXT_SHIFT (12U)
#define SEC_ENG_SE_SHA_0_MODE_EXT_MASK  (0x3 << SEC_ENG_SE_SHA_0_MODE_EXT_SHIFT)
#define SEC_ENG_SE_SHA_0_LINK_MODE      (1 << 15U)
#define SEC_ENG_SE_SHA_0_MSG_LEN_SHIFT  (16U)
#define SEC_ENG_SE_SHA_0_MSG_LEN_MASK   (0xffff << SEC_ENG_SE_SHA_0_MSG_LEN_SHIFT)

/* 0x4 : se_sha_0_msa */
#define SEC_ENG_SE_SHA_0_MSA_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_MSA_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_MSA_SHIFT)

/* 0x8 : se_sha_0_status */
#define SEC_ENG_SE_SHA_0_STATUS_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_STATUS_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_STATUS_SHIFT)

/* 0xC : se_sha_0_endian */
#define SEC_ENG_SE_SHA_0_DOUT_ENDIAN (1 << 0U)

/* 0x10 : se_sha_0_hash_l_0 */
#define SEC_ENG_SE_SHA_0_HASH_L_0_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_L_0_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_L_0_SHIFT)

/* 0x14 : se_sha_0_hash_l_1 */
#define SEC_ENG_SE_SHA_0_HASH_L_1_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_L_1_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_L_1_SHIFT)

/* 0x18 : se_sha_0_hash_l_2 */
#define SEC_ENG_SE_SHA_0_HASH_L_2_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_L_2_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_L_2_SHIFT)

/* 0x1C : se_sha_0_hash_l_3 */
#define SEC_ENG_SE_SHA_0_HASH_L_3_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_L_3_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_L_3_SHIFT)

/* 0x20 : se_sha_0_hash_l_4 */
#define SEC_ENG_SE_SHA_0_HASH_L_4_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_L_4_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_L_4_SHIFT)

/* 0x24 : se_sha_0_hash_l_5 */
#define SEC_ENG_SE_SHA_0_HASH_L_5_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_L_5_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_L_5_SHIFT)

/* 0x28 : se_sha_0_hash_l_6 */
#define SEC_ENG_SE_SHA_0_HASH_L_6_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_L_6_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_L_6_SHIFT)

/* 0x2C : se_sha_0_hash_l_7 */
#define SEC_ENG_SE_SHA_0_HASH_L_7_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_L_7_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_L_7_SHIFT)

/* 0x30 : se_sha_0_hash_h_0 */
#define SEC_ENG_SE_SHA_0_HASH_H_0_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_H_0_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_H_0_SHIFT)

/* 0x34 : se_sha_0_hash_h_1 */
#define SEC_ENG_SE_SHA_0_HASH_H_1_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_H_1_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_H_1_SHIFT)

/* 0x38 : se_sha_0_hash_h_2 */
#define SEC_ENG_SE_SHA_0_HASH_H_2_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_H_2_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_H_2_SHIFT)

/* 0x3C : se_sha_0_hash_h_3 */
#define SEC_ENG_SE_SHA_0_HASH_H_3_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_H_3_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_H_3_SHIFT)

/* 0x40 : se_sha_0_hash_h_4 */
#define SEC_ENG_SE_SHA_0_HASH_H_4_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_H_4_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_H_4_SHIFT)

/* 0x44 : se_sha_0_hash_h_5 */
#define SEC_ENG_SE_SHA_0_HASH_H_5_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_H_5_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_H_5_SHIFT)

/* 0x48 : se_sha_0_hash_h_6 */
#define SEC_ENG_SE_SHA_0_HASH_H_6_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_H_6_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_H_6_SHIFT)

/* 0x4C : se_sha_0_hash_h_7 */
#define SEC_ENG_SE_SHA_0_HASH_H_7_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_HASH_H_7_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_HASH_H_7_SHIFT)

/* 0x50 : se_sha_0_link */
#define SEC_ENG_SE_SHA_0_LCA_SHIFT (0U)
#define SEC_ENG_SE_SHA_0_LCA_MASK  (0xffffffff << SEC_ENG_SE_SHA_0_LCA_SHIFT)

/* 0xFC : se_sha_0_ctrl_prot */
#define SEC_ENG_SE_SHA_ID0_EN (1 << 1U)
#define SEC_ENG_SE_SHA_ID1_EN (1 << 2U)

/* 0x100 : se_aes_0_ctrl */
#define SEC_ENG_SE_AES_0_BUSY             (1 << 0U)
#define SEC_ENG_SE_AES_0_TRIG_1T          (1 << 1U)
#define SEC_ENG_SE_AES_0_EN               (1 << 2U)
#define SEC_ENG_SE_AES_0_MODE_SHIFT       (3U)
#define SEC_ENG_SE_AES_0_MODE_MASK        (0x3 << SEC_ENG_SE_AES_0_MODE_SHIFT)
#define SEC_ENG_SE_AES_0_DEC_EN           (1 << 5U)
#define SEC_ENG_SE_AES_0_DEC_KEY_SEL      (1 << 6U)
#define SEC_ENG_SE_AES_0_HW_KEY_EN        (1 << 7U)
#define SEC_ENG_SE_AES_0_INT              (1 << 8U)
#define SEC_ENG_SE_AES_0_INT_CLR_1T       (1 << 9U)
#define SEC_ENG_SE_AES_0_INT_SET_1T       (1 << 10U)
#define SEC_ENG_SE_AES_0_INT_MASK         (1 << 11U)
#define SEC_ENG_SE_AES_0_BLOCK_MODE_SHIFT (12U)
#define SEC_ENG_SE_AES_0_BLOCK_MODE_MASK  (0x3 << SEC_ENG_SE_AES_0_BLOCK_MODE_SHIFT)
#define SEC_ENG_SE_AES_0_IV_SEL           (1 << 14U)
#define SEC_ENG_SE_AES_0_LINK_MODE        (1 << 15U)
#define SEC_ENG_SE_AES_0_MSG_LEN_SHIFT    (16U)
#define SEC_ENG_SE_AES_0_MSG_LEN_MASK     (0xffff << SEC_ENG_SE_AES_0_MSG_LEN_SHIFT)

/* 0x104 : se_aes_0_msa */
#define SEC_ENG_SE_AES_0_MSA_SHIFT (0U)
#define SEC_ENG_SE_AES_0_MSA_MASK  (0xffffffff << SEC_ENG_SE_AES_0_MSA_SHIFT)

/* 0x108 : se_aes_0_mda */
#define SEC_ENG_SE_AES_0_MDA_SHIFT (0U)
#define SEC_ENG_SE_AES_0_MDA_MASK  (0xffffffff << SEC_ENG_SE_AES_0_MDA_SHIFT)

/* 0x10C : se_aes_0_status */
#define SEC_ENG_SE_AES_0_STATUS_SHIFT (0U)
#define SEC_ENG_SE_AES_0_STATUS_MASK  (0xffffffff << SEC_ENG_SE_AES_0_STATUS_SHIFT)

/* 0x110 : se_aes_0_iv_0 */
#define SEC_ENG_SE_AES_0_IV_0_SHIFT (0U)
#define SEC_ENG_SE_AES_0_IV_0_MASK  (0xffffffff << SEC_ENG_SE_AES_0_IV_0_SHIFT)

/* 0x114 : se_aes_0_iv_1 */
#define SEC_ENG_SE_AES_0_IV_1_SHIFT (0U)
#define SEC_ENG_SE_AES_0_IV_1_MASK  (0xffffffff << SEC_ENG_SE_AES_0_IV_1_SHIFT)

/* 0x118 : se_aes_0_iv_2 */
#define SEC_ENG_SE_AES_0_IV_2_SHIFT (0U)
#define SEC_ENG_SE_AES_0_IV_2_MASK  (0xffffffff << SEC_ENG_SE_AES_0_IV_2_SHIFT)

/* 0x11C : se_aes_0_iv_3 */
#define SEC_ENG_SE_AES_0_IV_3_SHIFT (0U)
#define SEC_ENG_SE_AES_0_IV_3_MASK  (0xffffffff << SEC_ENG_SE_AES_0_IV_3_SHIFT)

/* 0x120 : se_aes_0_key_0 */
#define SEC_ENG_SE_AES_0_KEY_0_SHIFT (0U)
#define SEC_ENG_SE_AES_0_KEY_0_MASK  (0xffffffff << SEC_ENG_SE_AES_0_KEY_0_SHIFT)

/* 0x124 : se_aes_0_key_1 */
#define SEC_ENG_SE_AES_0_KEY_1_SHIFT (0U)
#define SEC_ENG_SE_AES_0_KEY_1_MASK  (0xffffffff << SEC_ENG_SE_AES_0_KEY_1_SHIFT)

/* 0x128 : se_aes_0_key_2 */
#define SEC_ENG_SE_AES_0_KEY_2_SHIFT (0U)
#define SEC_ENG_SE_AES_0_KEY_2_MASK  (0xffffffff << SEC_ENG_SE_AES_0_KEY_2_SHIFT)

/* 0x12C : se_aes_0_key_3 */
#define SEC_ENG_SE_AES_0_KEY_3_SHIFT (0U)
#define SEC_ENG_SE_AES_0_KEY_3_MASK  (0xffffffff << SEC_ENG_SE_AES_0_KEY_3_SHIFT)

/* 0x130 : se_aes_0_key_4 */
#define SEC_ENG_SE_AES_0_KEY_4_SHIFT (0U)
#define SEC_ENG_SE_AES_0_KEY_4_MASK  (0xffffffff << SEC_ENG_SE_AES_0_KEY_4_SHIFT)

/* 0x134 : se_aes_0_key_5 */
#define SEC_ENG_SE_AES_0_KEY_5_SHIFT (0U)
#define SEC_ENG_SE_AES_0_KEY_5_MASK  (0xffffffff << SEC_ENG_SE_AES_0_KEY_5_SHIFT)

/* 0x138 : se_aes_0_key_6 */
#define SEC_ENG_SE_AES_0_KEY_6_SHIFT (0U)
#define SEC_ENG_SE_AES_0_KEY_6_MASK  (0xffffffff << SEC_ENG_SE_AES_0_KEY_6_SHIFT)

/* 0x13C : se_aes_0_key_7 */
#define SEC_ENG_SE_AES_0_KEY_7_SHIFT (0U)
#define SEC_ENG_SE_AES_0_KEY_7_MASK  (0xffffffff << SEC_ENG_SE_AES_0_KEY_7_SHIFT)

/* 0x140 : se_aes_0_key_sel */
#define SEC_ENG_SE_AES_0_KEY_SEL_SHIFT (0U)
#define SEC_ENG_SE_AES_0_KEY_SEL_MASK  (0x3 << SEC_ENG_SE_AES_0_KEY_SEL_SHIFT)

/* 0x144 : se_aes_1_key_sel */
#define SEC_ENG_SE_AES_1_KEY_SEL_SHIFT (0U)
#define SEC_ENG_SE_AES_1_KEY_SEL_MASK  (0x3 << SEC_ENG_SE_AES_1_KEY_SEL_SHIFT)

/* 0x148 : se_aes_0_endian */
#define SEC_ENG_SE_AES_0_DOUT_ENDIAN   (1 << 0U)
#define SEC_ENG_SE_AES_0_DIN_ENDIAN    (1 << 1U)
#define SEC_ENG_SE_AES_0_KEY_ENDIAN    (1 << 2U)
#define SEC_ENG_SE_AES_0_IV_ENDIAN     (1 << 3U)
#define SEC_ENG_SE_AES_0_TWK_ENDIAN    (1 << 4U)
#define SEC_ENG_SE_AES_0_CTR_LEN_SHIFT (30U)
#define SEC_ENG_SE_AES_0_CTR_LEN_MASK  (0x3 << SEC_ENG_SE_AES_0_CTR_LEN_SHIFT)

/* 0x14C : se_aes_sboot */
#define SEC_ENG_SE_AES_0_SBOOT_KEY_SEL (1 << 0U)
#define SEC_ENG_SE_AES_0_XTS_MODE      (1 << 15U)
#define SEC_ENG_SE_AES_0_UNI_LEN_SHIFT (16U)
#define SEC_ENG_SE_AES_0_UNI_LEN_MASK  (0xffff << SEC_ENG_SE_AES_0_UNI_LEN_SHIFT)

/* 0x150 : se_aes_0_link */
#define SEC_ENG_SE_AES_0_LCA_SHIFT (0U)
#define SEC_ENG_SE_AES_0_LCA_MASK  (0xffffffff << SEC_ENG_SE_AES_0_LCA_SHIFT)

/* 0x1FC : se_aes_0_ctrl_prot */
#define SEC_ENG_SE_AES_ID0_EN (1 << 1U)
#define SEC_ENG_SE_AES_ID1_EN (1 << 2U)

/* 0x200 : se_trng_0_ctrl_0 */
#define SEC_ENG_SE_TRNG_0_BUSY           (1 << 0U)
#define SEC_ENG_SE_TRNG_0_TRIG_1T        (1 << 1U)
#define SEC_ENG_SE_TRNG_0_EN             (1 << 2U)
#define SEC_ENG_SE_TRNG_0_DOUT_CLR_1T    (1 << 3U)
#define SEC_ENG_SE_TRNG_0_HT_ERROR       (1 << 4U)
#define SEC_ENG_SE_TRNG_0_INT            (1 << 8U)
#define SEC_ENG_SE_TRNG_0_INT_CLR_1T     (1 << 9U)
#define SEC_ENG_SE_TRNG_0_INT_SET_1T     (1 << 10U)
#define SEC_ENG_SE_TRNG_0_INT_MASK       (1 << 11U)
#define SEC_ENG_SE_TRNG_0_MANUAL_FUN_SEL (1 << 13U)
#define SEC_ENG_SE_TRNG_0_MANUAL_RESEED  (1 << 14U)
#define SEC_ENG_SE_TRNG_0_MANUAL_EN      (1 << 15U)

/* 0x204 : se_trng_0_status */
#define SEC_ENG_SE_TRNG_0_STATUS_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_STATUS_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_STATUS_SHIFT)

/* 0x208 : se_trng_0_dout_0 */
#define SEC_ENG_SE_TRNG_0_DOUT_0_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_DOUT_0_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_DOUT_0_SHIFT)

/* 0x20C : se_trng_0_dout_1 */
#define SEC_ENG_SE_TRNG_0_DOUT_1_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_DOUT_1_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_DOUT_1_SHIFT)

/* 0x210 : se_trng_0_dout_2 */
#define SEC_ENG_SE_TRNG_0_DOUT_2_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_DOUT_2_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_DOUT_2_SHIFT)

/* 0x214 : se_trng_0_dout_3 */
#define SEC_ENG_SE_TRNG_0_DOUT_3_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_DOUT_3_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_DOUT_3_SHIFT)

/* 0x218 : se_trng_0_dout_4 */
#define SEC_ENG_SE_TRNG_0_DOUT_4_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_DOUT_4_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_DOUT_4_SHIFT)

/* 0x21C : se_trng_0_dout_5 */
#define SEC_ENG_SE_TRNG_0_DOUT_5_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_DOUT_5_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_DOUT_5_SHIFT)

/* 0x220 : se_trng_0_dout_6 */
#define SEC_ENG_SE_TRNG_0_DOUT_6_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_DOUT_6_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_DOUT_6_SHIFT)

/* 0x224 : se_trng_0_dout_7 */
#define SEC_ENG_SE_TRNG_0_DOUT_7_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_DOUT_7_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_DOUT_7_SHIFT)

/* 0x228 : se_trng_0_test */
#define SEC_ENG_SE_TRNG_0_TEST_EN          (1 << 0U)
#define SEC_ENG_SE_TRNG_0_CP_TEST_EN       (1 << 1U)
#define SEC_ENG_SE_TRNG_0_CP_BYPASS        (1 << 2U)
#define SEC_ENG_SE_TRNG_0_HT_DIS           (1 << 3U)
#define SEC_ENG_SE_TRNG_0_HT_ALARM_N_SHIFT (4U)
#define SEC_ENG_SE_TRNG_0_HT_ALARM_N_MASK  (0xff << SEC_ENG_SE_TRNG_0_HT_ALARM_N_SHIFT)

/* 0x22C : se_trng_0_ctrl_1 */
#define SEC_ENG_SE_TRNG_0_RESEED_N_LSB_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_RESEED_N_LSB_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_RESEED_N_LSB_SHIFT)

/* 0x230 : se_trng_0_ctrl_2 */
#define SEC_ENG_SE_TRNG_0_RESEED_N_MSB_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_RESEED_N_MSB_MASK  (0xffff << SEC_ENG_SE_TRNG_0_RESEED_N_MSB_SHIFT)

/* 0x234 : se_trng_0_ctrl_3 */
#define SEC_ENG_SE_TRNG_0_CP_RATIO_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_CP_RATIO_MASK  (0xff << SEC_ENG_SE_TRNG_0_CP_RATIO_SHIFT)
#define SEC_ENG_SE_TRNG_0_HT_RCT_C_SHIFT (8U)
#define SEC_ENG_SE_TRNG_0_HT_RCT_C_MASK  (0xff << SEC_ENG_SE_TRNG_0_HT_RCT_C_SHIFT)
#define SEC_ENG_SE_TRNG_0_HT_APT_C_SHIFT (16U)
#define SEC_ENG_SE_TRNG_0_HT_APT_C_MASK  (0x3ff << SEC_ENG_SE_TRNG_0_HT_APT_C_SHIFT)
#define SEC_ENG_SE_TRNG_0_HT_OD_EN       (1 << 26U)
#define SEC_ENG_SE_TRNG_0_ROSC_EN        (1 << 31U)

/* 0x240 : se_trng_0_test_out_0 */
#define SEC_ENG_SE_TRNG_0_TEST_OUT_0_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_TEST_OUT_0_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_TEST_OUT_0_SHIFT)

/* 0x244 : se_trng_0_test_out_1 */
#define SEC_ENG_SE_TRNG_0_TEST_OUT_1_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_TEST_OUT_1_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_TEST_OUT_1_SHIFT)

/* 0x248 : se_trng_0_test_out_2 */
#define SEC_ENG_SE_TRNG_0_TEST_OUT_2_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_TEST_OUT_2_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_TEST_OUT_2_SHIFT)

/* 0x24C : se_trng_0_test_out_3 */
#define SEC_ENG_SE_TRNG_0_TEST_OUT_3_SHIFT (0U)
#define SEC_ENG_SE_TRNG_0_TEST_OUT_3_MASK  (0xffffffff << SEC_ENG_SE_TRNG_0_TEST_OUT_3_SHIFT)

/* 0x2FC : se_trng_0_ctrl_prot */
#define SEC_ENG_SE_TRNG_ID0_EN (1 << 1U)
#define SEC_ENG_SE_TRNG_ID1_EN (1 << 2U)

/* 0x300 : se_pka_0_ctrl_0 */
#define SEC_ENG_SE_PKA_0_DONE          (1 << 0U)
#define SEC_ENG_SE_PKA_0_DONE_CLR_1T   (1 << 1U)
#define SEC_ENG_SE_PKA_0_BUSY          (1 << 2U)
#define SEC_ENG_SE_PKA_0_EN            (1 << 3U)
#define SEC_ENG_SE_PKA_0_PROT_MD_SHIFT (4U)
#define SEC_ENG_SE_PKA_0_PROT_MD_MASK  (0xf << SEC_ENG_SE_PKA_0_PROT_MD_SHIFT)
#define SEC_ENG_SE_PKA_0_INT           (1 << 8U)
#define SEC_ENG_SE_PKA_0_INT_CLR_1T    (1 << 9U)
#define SEC_ENG_SE_PKA_0_INT_SET       (1 << 10U)
#define SEC_ENG_SE_PKA_0_INT_MASK      (1 << 11U)
#define SEC_ENG_SE_PKA_0_ENDIAN        (1 << 12U)
#define SEC_ENG_SE_PKA_0_RAM_CLR_MD    (1 << 13U)
#define SEC_ENG_SE_PKA_0_STATUS_CLR_1T (1 << 15U)
#define SEC_ENG_SE_PKA_0_STATUS_SHIFT  (16U)
#define SEC_ENG_SE_PKA_0_STATUS_MASK   (0xffff << SEC_ENG_SE_PKA_0_STATUS_SHIFT)

/* 0x30C : se_pka_0_seed */
#define SEC_ENG_SE_PKA_0_SEED_SHIFT (0U)
#define SEC_ENG_SE_PKA_0_SEED_MASK  (0xffffffff << SEC_ENG_SE_PKA_0_SEED_SHIFT)

/* 0x310 : se_pka_0_ctrl_1 */
#define SEC_ENG_SE_PKA_0_HBURST_SHIFT (0U)
#define SEC_ENG_SE_PKA_0_HBURST_MASK  (0x7 << SEC_ENG_SE_PKA_0_HBURST_SHIFT)
#define SEC_ENG_SE_PKA_0_HBYPASS      (1 << 3U)

/* 0x340 : se_pka_0_rw */

/* 0x360 : se_pka_0_rw_burst */

/* 0x3FC : se_pka_0_ctrl_prot */
#define SEC_ENG_SE_PKA_ID0_EN (1 << 1U)
#define SEC_ENG_SE_PKA_ID1_EN (1 << 2U)

/* 0x400 : se_cdet_0_ctrl_0 */
#define SEC_ENG_SE_CDET_0_EN           (1 << 0U)
#define SEC_ENG_SE_CDET_0_BUSY         (1 << 1U)
#define SEC_ENG_SE_CDET_0_STATUS_SHIFT (3U)
#define SEC_ENG_SE_CDET_0_STATUS_MASK  (0x1f << SEC_ENG_SE_CDET_0_STATUS_SHIFT)
#define SEC_ENG_SE_CDET_0_INT          (1 << 8U)
#define SEC_ENG_SE_CDET_0_INT_CLR      (1 << 9U)
#define SEC_ENG_SE_CDET_0_INT_SET      (1 << 10U)
#define SEC_ENG_SE_CDET_0_INT_MASK     (1 << 11U)
#define SEC_ENG_SE_CDET_0_MODE         (1 << 12U)

/* 0x404 : se_cdet_0_ctrl_1 */
#define SEC_ENG_SE_CDET_0_G_LOOP_MAX_SHIFT (0U)
#define SEC_ENG_SE_CDET_0_G_LOOP_MAX_MASK  (0xffff << SEC_ENG_SE_CDET_0_G_LOOP_MAX_SHIFT)
#define SEC_ENG_SE_CDET_0_G_LOOP_MIN_SHIFT (16U)
#define SEC_ENG_SE_CDET_0_G_LOOP_MIN_MASK  (0xffff << SEC_ENG_SE_CDET_0_G_LOOP_MIN_SHIFT)

/* 0x408 : se_cdet_0_ctrl_2 */
#define SEC_ENG_SE_CDET_0_T_LOOP_N_SHIFT (0U)
#define SEC_ENG_SE_CDET_0_T_LOOP_N_MASK  (0xffff << SEC_ENG_SE_CDET_0_T_LOOP_N_SHIFT)
#define SEC_ENG_SE_CDET_0_T_DLY_N_SHIFT  (16U)
#define SEC_ENG_SE_CDET_0_T_DLY_N_MASK   (0xff << SEC_ENG_SE_CDET_0_T_DLY_N_SHIFT)
#define SEC_ENG_SE_CDET_0_G_SLP_N_SHIFT  (24U)
#define SEC_ENG_SE_CDET_0_G_SLP_N_MASK   (0xff << SEC_ENG_SE_CDET_0_G_SLP_N_SHIFT)

/* 0x40C : se_cdet_0_ctrl_3 */
#define SEC_ENG_SE_CDET_0_T_COUNT_SHIFT (0U)
#define SEC_ENG_SE_CDET_0_T_COUNT_MASK  (0xffff << SEC_ENG_SE_CDET_0_T_COUNT_SHIFT)
#define SEC_ENG_SE_CDET_0_G_COUNT_SHIFT (16U)
#define SEC_ENG_SE_CDET_0_G_COUNT_MASK  (0xffff << SEC_ENG_SE_CDET_0_G_COUNT_SHIFT)

/* 0x4FC : se_cdet_0_ctrl_prot */
#define SEC_ENG_SE_CDET_PROT_EN (1 << 0U)
#define SEC_ENG_SE_CDET_ID0_EN  (1 << 1U)
#define SEC_ENG_SE_CDET_ID1_EN  (1 << 2U)

/* 0x500 : se_gmac_0_ctrl_0 */
#define SEC_ENG_SE_GMAC_0_BUSY       (1 << 0U)
#define SEC_ENG_SE_GMAC_0_TRIG_1T    (1 << 1U)
#define SEC_ENG_SE_GMAC_0_EN         (1 << 2U)
#define SEC_ENG_SE_GMAC_0_INT        (1 << 8U)
#define SEC_ENG_SE_GMAC_0_INT_CLR_1T (1 << 9U)
#define SEC_ENG_SE_GMAC_0_INT_SET_1T (1 << 10U)
#define SEC_ENG_SE_GMAC_0_INT_MASK   (1 << 11U)
#define SEC_ENG_SE_GMAC_0_T_ENDIAN   (1 << 12U)
#define SEC_ENG_SE_GMAC_0_H_ENDIAN   (1 << 13U)
#define SEC_ENG_SE_GMAC_0_X_ENDIAN   (1 << 14U)

/* 0x504 : se_gmac_0_lca */
#define SEC_ENG_SE_GMAC_0_LCA_SHIFT (0U)
#define SEC_ENG_SE_GMAC_0_LCA_MASK  (0xffffffff << SEC_ENG_SE_GMAC_0_LCA_SHIFT)

/* 0x508 : se_gmac_0_status */
#define SEC_ENG_SE_GMAC_0_STATUS_SHIFT (0U)
#define SEC_ENG_SE_GMAC_0_STATUS_MASK  (0xffffffff << SEC_ENG_SE_GMAC_0_STATUS_SHIFT)

/* 0x5FC : se_gmac_0_ctrl_prot */
#define SEC_ENG_SE_GMAC_ID0_EN (1 << 1U)
#define SEC_ENG_SE_GMAC_ID1_EN (1 << 2U)

/* 0xF00 : se_ctrl_prot_rd */
#define SEC_ENG_SE_SHA_ID0_EN_RD  (1 << 0U)
#define SEC_ENG_SE_SHA_ID1_EN_RD  (1 << 1U)
#define SEC_ENG_SE_AES_ID0_EN_RD  (1 << 2U)
#define SEC_ENG_SE_AES_ID1_EN_RD  (1 << 3U)
#define SEC_ENG_SE_TRNG_ID0_EN_RD (1 << 4U)
#define SEC_ENG_SE_TRNG_ID1_EN_RD (1 << 5U)
#define SEC_ENG_SE_PKA_ID0_EN_RD  (1 << 6U)
#define SEC_ENG_SE_PKA_ID1_EN_RD  (1 << 7U)
#define SEC_ENG_SE_CDET_ID0_EN_RD (1 << 8U)
#define SEC_ENG_SE_CDET_ID1_EN_RD (1 << 9U)
#define SEC_ENG_SE_GMAC_ID0_EN_RD (1 << 10U)
#define SEC_ENG_SE_GMAC_ID1_EN_RD (1 << 11U)
#define SEC_ENG_SE_DBG_DIS        (1 << 31U)

/* 0xF04 : se_ctrl_reserved_0 */
#define SEC_ENG_SE_CTRL_RESERVED_0_SHIFT (0U)
#define SEC_ENG_SE_CTRL_RESERVED_0_MASK  (0xffffffff << SEC_ENG_SE_CTRL_RESERVED_0_SHIFT)

/* 0xF08 : se_ctrl_reserved_1 */
#define SEC_ENG_SE_CTRL_RESERVED_1_SHIFT (0U)
#define SEC_ENG_SE_CTRL_RESERVED_1_MASK  (0xffffffff << SEC_ENG_SE_CTRL_RESERVED_1_SHIFT)

/* 0xF0C : se_ctrl_reserved_2 */
#define SEC_ENG_SE_CTRL_RESERVED_2_SHIFT (0U)
#define SEC_ENG_SE_CTRL_RESERVED_2_MASK  (0xffffffff << SEC_ENG_SE_CTRL_RESERVED_2_SHIFT)

#endif /* __HARDWARE_SEC_ENG_H__ */
