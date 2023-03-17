/**
  ******************************************************************************
  * @file    cam_front_reg.h
  * @version V1.0
  * @date    2022-12-03
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
#ifndef  __HARDWARE_CAM_FRONT_H__
#define  __HARDWARE_CAM_FRONT_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define CAM_FRONT_CONFIG_OFFSET                                 (0x0)/* config */
#define CAM_FRONT_DVP2BUS_SRC_SEL_1_OFFSET                      (0x8)/* dvp2bus_src_sel_1 */
#if defined(BL616)
#define CAM_FRONT_SNSR_CTRL_OFFSET                              (0xC)/* snsr_ctrl */
#define CAM_FRONT_EMI_MISC_OFFSET                               (0x10)/* emi_misc */
#define CAM_FRONT_ISP_ID_YUV_OFFSET                             (0x14)/* isp_id_yuv */
#endif
#if defined(BL808)
#define CAM_FRONT_PIX_DATA_CTRL_OFFSET                          (0x4)/* pix_data_ctrl */
#define CAM_FRONT_DVP2BUS_SRC_SEL_2_OFFSET                      (0x14)/* dvp2bus_src_sel_2 */
#define CAM_FRONT_ISP_ID_YUV_OFFSET                             (0x28)/* isp_id_yuv */
#define CAM_FRONT_ADJA_CTRL_2_OFFSET                            (0x108)/* adjA_ctrl_2 */
#define CAM_FRONT_Y2RA_CONFIG_0_OFFSET                          (0x160)/* y2rA_config_0 */
#define CAM_FRONT_Y2RA_CONFIG_1_OFFSET                          (0x164)/* y2rA_config_1 */
#define CAM_FRONT_Y2RA_CONFIG_2_OFFSET                          (0x168)/* y2rA_config_2 */
#define CAM_FRONT_Y2RA_CONFIG_3_OFFSET                          (0x16C)/* y2rA_config_3 */
#define CAM_FRONT_Y2RA_CONFIG_4_OFFSET                          (0x170)/* y2rA_config_4 */
#define CAM_FRONT_Y2RA_CONFIG_5_OFFSET                          (0x174)/* y2rA_config_5 */
#define CAM_FRONT_Y2RA_CONFIG_6_OFFSET                          (0x178)/* y2rA_config_6 */
#define CAM_FRONT_Y2RA_CONFIG_7_OFFSET                          (0x17C)/* y2rA_config_7 */
#endif

/* Register Bitfield definitions *****************************************************/

/* 0x0 : config */
#define CAM_FRONT_RG_DVPAS_ENABLE                               (1<<0U)
#define CAM_FRONT_RG_DVPAS_HS_INV                               (1<<1U)
#define CAM_FRONT_RG_DVPAS_VS_INV                               (1<<2U)
#define CAM_FRONT_RG_DVPAS_DA_ORDER                             (1<<3U)
#define CAM_FRONT_RG_DVPAS_FIFO_TH_SHIFT                        (16U)
#define CAM_FRONT_RG_DVPAS_FIFO_TH_MASK                         (0x7ff<<CAM_FRONT_RG_DVPAS_FIFO_TH_SHIFT)

#if defined(BL808)
/* 0x4 : pix_data_ctrl */
#define CAM_FRONT_REG_PIX_DATA_CTRL_SHIFT                       (0U)
#define CAM_FRONT_REG_PIX_DATA_CTRL_MASK                        (0xfff<<CAM_FRONT_REG_PIX_DATA_CTRL_SHIFT)
#define CAM_FRONT_REG_PIX_DATA_SHT_BIT_SHIFT                    (16U)
#define CAM_FRONT_REG_PIX_DATA_SHT_BIT_MASK                     (0xf<<CAM_FRONT_REG_PIX_DATA_SHT_BIT_SHIFT)
#define CAM_FRONT_REG_PIX_DATA_SHT_DIR                          (1<<20U)
#define CAM_FRONT_REG_ISP_DTSRC_SRC                             (1<<31U)

/* 0x8 : dvp2bus_src_sel_1 */
#define CAM_FRONT_RG_D2B_DVP_SEL_A_SHIFT                        (0U)
#define CAM_FRONT_RG_D2B_DVP_SEL_A_MASK                         (0x3f<<CAM_FRONT_RG_D2B_DVP_SEL_A_SHIFT)
#define CAM_FRONT_RG_D2X_ID_SEL_A                               (1<<7U)
#define CAM_FRONT_RG_D2B_DVP_SEL_B_SHIFT                        (8U)
#define CAM_FRONT_RG_D2B_DVP_SEL_B_MASK                         (0x3f<<CAM_FRONT_RG_D2B_DVP_SEL_B_SHIFT)
#define CAM_FRONT_RG_D2X_ID_SEL_B                               (1<<15U)
#define CAM_FRONT_RG_D2B_DVP_SEL_C_SHIFT                        (16U)
#define CAM_FRONT_RG_D2B_DVP_SEL_C_MASK                         (0x3f<<CAM_FRONT_RG_D2B_DVP_SEL_C_SHIFT)
#define CAM_FRONT_RG_D2X_ID_SEL_C                               (1<<23U)
#define CAM_FRONT_RG_D2B_DVP_SEL_D_SHIFT                        (24U)
#define CAM_FRONT_RG_D2B_DVP_SEL_D_MASK                         (0x3f<<CAM_FRONT_RG_D2B_DVP_SEL_D_SHIFT)
#define CAM_FRONT_RG_D2X_ID_SEL_D                               (1<<31U)

/* 0x14 : dvp2bus_src_sel_2 */
#define CAM_FRONT_RG_D2B_DVP_SEL_E_SHIFT                        (0U)
#define CAM_FRONT_RG_D2B_DVP_SEL_E_MASK                         (0x3f<<CAM_FRONT_RG_D2B_DVP_SEL_E_SHIFT)
#define CAM_FRONT_RG_D2X_ID_SEL_E                               (1<<7U)
#define CAM_FRONT_RG_D2B_DVP_SEL_F_SHIFT                        (8U)
#define CAM_FRONT_RG_D2B_DVP_SEL_F_MASK                         (0x3f<<CAM_FRONT_RG_D2B_DVP_SEL_F_SHIFT)
#define CAM_FRONT_RG_D2X_ID_SEL_F                               (1<<15U)
#define CAM_FRONT_RG_D2B_DVP_SEL_G_SHIFT                        (16U)
#define CAM_FRONT_RG_D2B_DVP_SEL_G_MASK                         (0x3f<<CAM_FRONT_RG_D2B_DVP_SEL_G_SHIFT)
#define CAM_FRONT_RG_D2X_ID_SEL_G                               (1<<23U)
#define CAM_FRONT_RG_D2B_DVP_SEL_H_SHIFT                        (24U)
#define CAM_FRONT_RG_D2B_DVP_SEL_H_MASK                         (0x3f<<CAM_FRONT_RG_D2B_DVP_SEL_H_SHIFT)
#define CAM_FRONT_RG_D2X_ID_SEL_H                               (1<<31U)

/* 0x160 : y2rA_config_0 */
#define CAM_FRONT_RG_Y2RA_PRE_0_SHIFT                           (0U)
#define CAM_FRONT_RG_Y2RA_PRE_0_MASK                            (0x1ff<<CAM_FRONT_RG_Y2RA_PRE_0_SHIFT)
#define CAM_FRONT_RG_Y2RA_POS_0_SHIFT                           (16U)
#define CAM_FRONT_RG_Y2RA_POS_0_MASK                            (0x1ff<<CAM_FRONT_RG_Y2RA_POS_0_SHIFT)
#define CAM_FRONT_RG_Y2RA_EN                                    (1<<27U)
#define CAM_FRONT_RG_Y2RA_SEL_SHIFT                             (28U)
#define CAM_FRONT_RG_Y2RA_SEL_MASK                              (0xf<<CAM_FRONT_RG_Y2RA_SEL_SHIFT)

/* 0x164 : y2rA_config_1 */
#define CAM_FRONT_RG_Y2RA_PRE_1_SHIFT                           (0U)
#define CAM_FRONT_RG_Y2RA_PRE_1_MASK                            (0x1ff<<CAM_FRONT_RG_Y2RA_PRE_1_SHIFT)
#define CAM_FRONT_RG_Y2RA_POS_1_SHIFT                           (16U)
#define CAM_FRONT_RG_Y2RA_POS_1_MASK                            (0x1ff<<CAM_FRONT_RG_Y2RA_POS_1_SHIFT)

/* 0x168 : y2rA_config_2 */
#define CAM_FRONT_RG_Y2RA_PRE_2_SHIFT                           (0U)
#define CAM_FRONT_RG_Y2RA_PRE_2_MASK                            (0x1ff<<CAM_FRONT_RG_Y2RA_PRE_2_SHIFT)
#define CAM_FRONT_RG_Y2RA_POS_2_SHIFT                           (16U)
#define CAM_FRONT_RG_Y2RA_POS_2_MASK                            (0x1ff<<CAM_FRONT_RG_Y2RA_POS_2_SHIFT)

/* 0x16C : y2rA_config_3 */
#define CAM_FRONT_RG_Y2RA_MTX_00_SHIFT                          (0U)
#define CAM_FRONT_RG_Y2RA_MTX_00_MASK                           (0xfff<<CAM_FRONT_RG_Y2RA_MTX_00_SHIFT)
#define CAM_FRONT_RG_Y2RA_MTX_01_SHIFT                          (16U)
#define CAM_FRONT_RG_Y2RA_MTX_01_MASK                           (0xfff<<CAM_FRONT_RG_Y2RA_MTX_01_SHIFT)

/* 0x170 : y2rA_config_4 */
#define CAM_FRONT_RG_Y2RA_MTX_02_SHIFT                          (0U)
#define CAM_FRONT_RG_Y2RA_MTX_02_MASK                           (0xfff<<CAM_FRONT_RG_Y2RA_MTX_02_SHIFT)
#define CAM_FRONT_RG_Y2RA_MTX_10_SHIFT                          (16U)
#define CAM_FRONT_RG_Y2RA_MTX_10_MASK                           (0xfff<<CAM_FRONT_RG_Y2RA_MTX_10_SHIFT)

/* 0x174 : y2rA_config_5 */
#define CAM_FRONT_RG_Y2RA_MTX_11_SHIFT                          (0U)
#define CAM_FRONT_RG_Y2RA_MTX_11_MASK                           (0xfff<<CAM_FRONT_RG_Y2RA_MTX_11_SHIFT)
#define CAM_FRONT_RG_Y2RA_MTX_12_SHIFT                          (16U)
#define CAM_FRONT_RG_Y2RA_MTX_12_MASK                           (0xfff<<CAM_FRONT_RG_Y2RA_MTX_12_SHIFT)

/* 0x178 : y2rA_config_6 */
#define CAM_FRONT_RG_Y2RA_MTX_20_SHIFT                          (0U)
#define CAM_FRONT_RG_Y2RA_MTX_20_MASK                           (0xfff<<CAM_FRONT_RG_Y2RA_MTX_20_SHIFT)
#define CAM_FRONT_RG_Y2RA_MTX_21_SHIFT                          (16U)
#define CAM_FRONT_RG_Y2RA_MTX_21_MASK                           (0xfff<<CAM_FRONT_RG_Y2RA_MTX_21_SHIFT)

/* 0x17C : y2rA_config_7 */
#define CAM_FRONT_RG_Y2RA_MTX_22_SHIFT                          (0U)
#define CAM_FRONT_RG_Y2RA_MTX_22_MASK                           (0xfff<<CAM_FRONT_RG_Y2RA_MTX_22_SHIFT)
#endif

#if defined(BL616)
/* 0x8 : dvp2bus_src_sel_1 */
#define CAM_FRONT_RG_D2X_DVP_SEL                                (1<<0U)

/* 0xC : snsr_ctrl */
#define CAM_FRONT_RG_SNSR_RST                                   (1<<0U)
#define CAM_FRONT_RG_SNSR_PWDN                                  (1<<1U)

/* 0x10 : emi_misc */
#define CAM_FRONT_REG_X_WTHRE_PB_SHIFT                          (0U)
#define CAM_FRONT_REG_X_WTHRE_PB_MASK                           (0x3<<CAM_FRONT_REG_X_WTHRE_PB_SHIFT)
#define CAM_FRONT_REG_SF_HARB_MODE                              (1<<4U)
#endif

/* 0x14 : isp_id_yuv */
#define CAM_FRONT_REG_YUV_IDGEN_RST                             (1<<0U)
#define CAM_FRONT_REG_YUV_IDGEN_EDGE                            (1<<1U)
#define CAM_FRONT_REG_YUV_IDGEN_CNT_INCR_SHIFT                  (16U)
#define CAM_FRONT_REG_YUV_IDGEN_CNT_INCR_MASK                   (0xffff<<CAM_FRONT_REG_YUV_IDGEN_CNT_INCR_SHIFT)


#endif  /* __CAM_FRONT_REG_H__ */
