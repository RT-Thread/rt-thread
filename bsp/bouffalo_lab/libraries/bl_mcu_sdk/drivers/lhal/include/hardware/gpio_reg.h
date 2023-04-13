/**
  ******************************************************************************
  * @file    gpio_reg.h
  * @version V1.0
  * @date    2022-08-03
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
#ifndef  __HARDWARE_GPIO_H__
#define  __HARDWARE_GPIO_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/
#if defined(BL616) || defined(BL808) || defined(BL606P) || defined(BL628)
#define GLB_GPIO_CFG0_OFFSET                                    (0x8C4)/* gpio_cfg0 */
#define GLB_GPIO_CFG1_OFFSET                                    (0x8C8)/* gpio_cfg1 */
#define GLB_GPIO_CFG2_OFFSET                                    (0x8CC)/* gpio_cfg2 */
#define GLB_GPIO_CFG3_OFFSET                                    (0x8D0)/* gpio_cfg3 */
#define GLB_GPIO_CFG4_OFFSET                                    (0x8D4)/* gpio_cfg4 */
#define GLB_GPIO_CFG5_OFFSET                                    (0x8D8)/* gpio_cfg5 */
#define GLB_GPIO_CFG6_OFFSET                                    (0x8DC)/* gpio_cfg6 */
#define GLB_GPIO_CFG7_OFFSET                                    (0x8E0)/* gpio_cfg7 */
#define GLB_GPIO_CFG8_OFFSET                                    (0x8E4)/* gpio_cfg8 */
#define GLB_GPIO_CFG9_OFFSET                                    (0x8E8)/* gpio_cfg9 */
#define GLB_GPIO_CFG10_OFFSET                                   (0x8EC)/* gpio_cfg10 */
#define GLB_GPIO_CFG11_OFFSET                                   (0x8F0)/* gpio_cfg11 */
#define GLB_GPIO_CFG12_OFFSET                                   (0x8F4)/* gpio_cfg12 */
#define GLB_GPIO_CFG13_OFFSET                                   (0x8F8)/* gpio_cfg13 */
#define GLB_GPIO_CFG14_OFFSET                                   (0x8FC)/* gpio_cfg14 */
#define GLB_GPIO_CFG15_OFFSET                                   (0x900)/* gpio_cfg15 */
#define GLB_GPIO_CFG16_OFFSET                                   (0x904)/* gpio_cfg16 */
#define GLB_GPIO_CFG17_OFFSET                                   (0x908)/* gpio_cfg17 */
#define GLB_GPIO_CFG18_OFFSET                                   (0x90C)/* gpio_cfg18 */
#define GLB_GPIO_CFG19_OFFSET                                   (0x910)/* gpio_cfg19 */
#define GLB_GPIO_CFG20_OFFSET                                   (0x914)/* gpio_cfg20 */
#define GLB_GPIO_CFG21_OFFSET                                   (0x918)/* gpio_cfg21 */
#define GLB_GPIO_CFG22_OFFSET                                   (0x91C)/* gpio_cfg22 */
#define GLB_GPIO_CFG23_OFFSET                                   (0x920)/* gpio_cfg23 */
#define GLB_GPIO_CFG24_OFFSET                                   (0x924)/* gpio_cfg24 */
#define GLB_GPIO_CFG25_OFFSET                                   (0x928)/* gpio_cfg25 */
#define GLB_GPIO_CFG26_OFFSET                                   (0x92C)/* gpio_cfg26 */
#define GLB_GPIO_CFG27_OFFSET                                   (0x930)/* gpio_cfg27 */
#define GLB_GPIO_CFG28_OFFSET                                   (0x934)/* gpio_cfg28 */
#define GLB_GPIO_CFG29_OFFSET                                   (0x938)/* gpio_cfg29 */
#define GLB_GPIO_CFG30_OFFSET                                   (0x93C)/* gpio_cfg30 */
#define GLB_GPIO_CFG31_OFFSET                                   (0x940)/* gpio_cfg31 */
#define GLB_GPIO_CFG32_OFFSET                                   (0x944)/* gpio_cfg32 */
#define GLB_GPIO_CFG33_OFFSET                                   (0x948)/* gpio_cfg33 */
#define GLB_GPIO_CFG34_OFFSET                                   (0x94C)/* gpio_cfg34 */
#define GLB_GPIO_CFG35_OFFSET                                   (0x950)/* gpio_cfg35 */
#define GLB_GPIO_CFG36_OFFSET                                   (0x954)/* gpio_cfg36 */
#define GLB_GPIO_CFG37_OFFSET                                   (0x958)/* gpio_cfg37 */
#define GLB_GPIO_CFG38_OFFSET                                   (0x95C)/* gpio_cfg38 */
#define GLB_GPIO_CFG39_OFFSET                                   (0x960)/* gpio_cfg39 */
#define GLB_GPIO_CFG40_OFFSET                                   (0x964)/* gpio_cfg40 */
#define GLB_GPIO_CFG41_OFFSET                                   (0x968)/* gpio_cfg41 */
#define GLB_GPIO_CFG42_OFFSET                                   (0x96C)/* gpio_cfg42 */
#define GLB_GPIO_CFG43_OFFSET                                   (0x970)/* gpio_cfg43 */
#define GLB_GPIO_CFG44_OFFSET                                   (0x974)/* gpio_cfg44 */
#define GLB_GPIO_CFG45_OFFSET                                   (0x978)/* gpio_cfg45 */
#define GLB_GPIO_CFG46_OFFSET                                   (0x97C)/* gpio_cfg46 */
#define GLB_GPIO_CFG47_OFFSET                                   (0x980)/* gpio_cfg47 */
#define GLB_GPIO_CFG48_OFFSET                                   (0x984)/* gpio_cfg48 */
#define GLB_GPIO_CFG49_OFFSET                                   (0x988)/* gpio_cfg49 */
#define GLB_GPIO_CFG50_OFFSET                                   (0x98C)/* gpio_cfg50 */
#define GLB_GPIO_CFG51_OFFSET                                   (0x990)/* gpio_cfg51 */
#define GLB_GPIO_CFG52_OFFSET                                   (0x994)/* gpio_cfg52 */
#define GLB_GPIO_CFG53_OFFSET                                   (0x998)/* gpio_cfg53 */
#define GLB_GPIO_CFG54_OFFSET                                   (0x99C)/* gpio_cfg54 */
#define GLB_GPIO_CFG55_OFFSET                                   (0x9A0)/* gpio_cfg55 */
#define GLB_GPIO_CFG56_OFFSET                                   (0x9A4)/* gpio_cfg56 */
#define GLB_GPIO_CFG57_OFFSET                                   (0x9A8)/* gpio_cfg57 */
#define GLB_GPIO_CFG58_OFFSET                                   (0x9AC)/* gpio_cfg58 */
#define GLB_GPIO_CFG59_OFFSET                                   (0x9B0)/* gpio_cfg59 */
#define GLB_GPIO_CFG60_OFFSET                                   (0x9B4)/* gpio_cfg60 */
#define GLB_GPIO_CFG61_OFFSET                                   (0x9B8)/* gpio_cfg61 */
#define GLB_GPIO_CFG62_OFFSET                                   (0x9BC)/* gpio_cfg62 */
#define GLB_GPIO_CFG63_OFFSET                                   (0x9C0)/* gpio_cfg63 */
#define GLB_GPIO_CFG128_OFFSET                                  (0xAC4)/* gpio_cfg128 */
#define GLB_GPIO_CFG129_OFFSET                                  (0xAC8)/* gpio_cfg129 */
#define GLB_GPIO_CFG136_OFFSET                                  (0xAE4)/* gpio_cfg136 */
#define GLB_GPIO_CFG137_OFFSET                                  (0xAE8)/* gpio_cfg137 */
#define GLB_GPIO_CFG138_OFFSET                                  (0xAEC)/* gpio_cfg138 */
#define GLB_GPIO_CFG139_OFFSET                                  (0xAF0)/* gpio_cfg139 */
#define GLB_GPIO_CFG140_OFFSET                                  (0xAF4)/* gpio_cfg140 */
#define GLB_GPIO_CFG141_OFFSET                                  (0xAF8)/* gpio_cfg141 */
#define GLB_GPIO_CFG142_OFFSET                                  (0xAFC)/* gpio_cfg142 */
#define GLB_GPIO_CFG143_OFFSET                                  (0xB00)/* gpio_cfg143 */
#define GLB_GPIO_CFG144_OFFSET                                  (0xB04)/* gpio_cfg144 */

/* Register Bitfield definitions *****************************************************/

/* 0x8C4 : gpio_cfg0 */
#define GLB_REG_GPIO_0_IE                                       (1<<0U)
#define GLB_REG_GPIO_0_SMT                                      (1<<1U)
#define GLB_REG_GPIO_0_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_0_DRV_MASK                                 (0x3<<GLB_REG_GPIO_0_DRV_SHIFT)
#define GLB_REG_GPIO_0_PU                                       (1<<4U)
#define GLB_REG_GPIO_0_PD                                       (1<<5U)
#define GLB_REG_GPIO_0_OE                                       (1<<6U)
#define GLB_REG_GPIO_0_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_0_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_0_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_0_INT_MODE_SET_SHIFT                       (16U)
#define GLB_REG_GPIO_0_INT_MODE_SET_MASK                        (0xf<<GLB_REG_GPIO_0_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_0_INT_CLR                                  (1<<20U)
#define GLB_GPIO_0_INT_STAT                                     (1<<21U)
#define GLB_REG_GPIO_0_INT_MASK                                 (1<<22U)
#define GLB_REG_GPIO_0_O                                        (1<<24U)
#define GLB_REG_GPIO_0_SET                                      (1<<25U)
#define GLB_REG_GPIO_0_CLR                                      (1<<26U)
#define GLB_REG_GPIO_0_I                                        (1<<28U)
#define GLB_REG_GPIO_0_MODE_SHIFT                               (30U)
#define GLB_REG_GPIO_0_MODE_MASK                                (0x3<<GLB_REG_GPIO_0_MODE_SHIFT)

/* 0x8C8 : gpio_cfg1 */
#define GLB_REG_GPIO_1_IE                                       (1<<0U)
#define GLB_REG_GPIO_1_SMT                                      (1<<1U)
#define GLB_REG_GPIO_1_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_1_DRV_MASK                                 (0x3<<GLB_REG_GPIO_1_DRV_SHIFT)
#define GLB_REG_GPIO_1_PU                                       (1<<4U)
#define GLB_REG_GPIO_1_PD                                       (1<<5U)
#define GLB_REG_GPIO_1_OE                                       (1<<6U)
#define GLB_REG_GPIO_1_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_1_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_1_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_1_INT_MODE_SET_SHIFT                       (16U)
#define GLB_REG_GPIO_1_INT_MODE_SET_MASK                        (0xf<<GLB_REG_GPIO_1_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_1_INT_CLR                                  (1<<20U)
#define GLB_GPIO_1_INT_STAT                                     (1<<21U)
#define GLB_REG_GPIO_1_INT_MASK                                 (1<<22U)
#define GLB_REG_GPIO_1_O                                        (1<<24U)
#define GLB_REG_GPIO_1_SET                                      (1<<25U)
#define GLB_REG_GPIO_1_CLR                                      (1<<26U)
#define GLB_REG_GPIO_1_I                                        (1<<28U)
#define GLB_REG_GPIO_1_MODE_SHIFT                               (30U)
#define GLB_REG_GPIO_1_MODE_MASK                                (0x3<<GLB_REG_GPIO_1_MODE_SHIFT)

/* 0x8CC : gpio_cfg2 */
#define GLB_REG_GPIO_2_IE                                       (1<<0U)
#define GLB_REG_GPIO_2_SMT                                      (1<<1U)
#define GLB_REG_GPIO_2_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_2_DRV_MASK                                 (0x3<<GLB_REG_GPIO_2_DRV_SHIFT)
#define GLB_REG_GPIO_2_PU                                       (1<<4U)
#define GLB_REG_GPIO_2_PD                                       (1<<5U)
#define GLB_REG_GPIO_2_OE                                       (1<<6U)
#define GLB_REG_GPIO_2_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_2_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_2_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_2_INT_MODE_SET_SHIFT                       (16U)
#define GLB_REG_GPIO_2_INT_MODE_SET_MASK                        (0xf<<GLB_REG_GPIO_2_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_2_INT_CLR                                  (1<<20U)
#define GLB_GPIO_2_INT_STAT                                     (1<<21U)
#define GLB_REG_GPIO_2_INT_MASK                                 (1<<22U)
#define GLB_REG_GPIO_2_O                                        (1<<24U)
#define GLB_REG_GPIO_2_SET                                      (1<<25U)
#define GLB_REG_GPIO_2_CLR                                      (1<<26U)
#define GLB_REG_GPIO_2_I                                        (1<<28U)
#define GLB_REG_GPIO_2_MODE_SHIFT                               (30U)
#define GLB_REG_GPIO_2_MODE_MASK                                (0x3<<GLB_REG_GPIO_2_MODE_SHIFT)

/* 0x8D0 : gpio_cfg3 */
#define GLB_REG_GPIO_3_IE                                       (1<<0U)
#define GLB_REG_GPIO_3_SMT                                      (1<<1U)
#define GLB_REG_GPIO_3_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_3_DRV_MASK                                 (0x3<<GLB_REG_GPIO_3_DRV_SHIFT)
#define GLB_REG_GPIO_3_PU                                       (1<<4U)
#define GLB_REG_GPIO_3_PD                                       (1<<5U)
#define GLB_REG_GPIO_3_OE                                       (1<<6U)
#define GLB_REG_GPIO_3_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_3_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_3_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_3_INT_MODE_SET_SHIFT                       (16U)
#define GLB_REG_GPIO_3_INT_MODE_SET_MASK                        (0xf<<GLB_REG_GPIO_3_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_3_INT_CLR                                  (1<<20U)
#define GLB_GPIO_3_INT_STAT                                     (1<<21U)
#define GLB_REG_GPIO_3_INT_MASK                                 (1<<22U)
#define GLB_REG_GPIO_3_O                                        (1<<24U)
#define GLB_REG_GPIO_3_SET                                      (1<<25U)
#define GLB_REG_GPIO_3_CLR                                      (1<<26U)
#define GLB_REG_GPIO_3_I                                        (1<<28U)
#define GLB_REG_GPIO_3_MODE_SHIFT                               (30U)
#define GLB_REG_GPIO_3_MODE_MASK                                (0x3<<GLB_REG_GPIO_3_MODE_SHIFT)

/* 0x8D4 : gpio_cfg4 */
#define GLB_REG_GPIO_4_IE                                       (1<<0U)
#define GLB_REG_GPIO_4_SMT                                      (1<<1U)
#define GLB_REG_GPIO_4_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_4_DRV_MASK                                 (0x3<<GLB_REG_GPIO_4_DRV_SHIFT)
#define GLB_REG_GPIO_4_PU                                       (1<<4U)
#define GLB_REG_GPIO_4_PD                                       (1<<5U)
#define GLB_REG_GPIO_4_OE                                       (1<<6U)
#define GLB_REG_GPIO_4_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_4_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_4_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_4_INT_MODE_SET_SHIFT                       (16U)
#define GLB_REG_GPIO_4_INT_MODE_SET_MASK                        (0xf<<GLB_REG_GPIO_4_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_4_INT_CLR                                  (1<<20U)
#define GLB_GPIO_4_INT_STAT                                     (1<<21U)
#define GLB_REG_GPIO_4_INT_MASK                                 (1<<22U)
#define GLB_REG_GPIO_4_O                                        (1<<24U)
#define GLB_REG_GPIO_4_SET                                      (1<<25U)
#define GLB_REG_GPIO_4_CLR                                      (1<<26U)
#define GLB_REG_GPIO_4_I                                        (1<<28U)
#define GLB_REG_GPIO_4_MODE_SHIFT                               (30U)
#define GLB_REG_GPIO_4_MODE_MASK                                (0x3<<GLB_REG_GPIO_4_MODE_SHIFT)

/* 0x8D8 : gpio_cfg5 */
#define GLB_REG_GPIO_5_IE                                       (1<<0U)
#define GLB_REG_GPIO_5_SMT                                      (1<<1U)
#define GLB_REG_GPIO_5_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_5_DRV_MASK                                 (0x3<<GLB_REG_GPIO_5_DRV_SHIFT)
#define GLB_REG_GPIO_5_PU                                       (1<<4U)
#define GLB_REG_GPIO_5_PD                                       (1<<5U)
#define GLB_REG_GPIO_5_OE                                       (1<<6U)
#define GLB_REG_GPIO_5_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_5_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_5_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_5_INT_MODE_SET_SHIFT                       (16U)
#define GLB_REG_GPIO_5_INT_MODE_SET_MASK                        (0xf<<GLB_REG_GPIO_5_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_5_INT_CLR                                  (1<<20U)
#define GLB_GPIO_5_INT_STAT                                     (1<<21U)
#define GLB_REG_GPIO_5_INT_MASK                                 (1<<22U)
#define GLB_REG_GPIO_5_O                                        (1<<24U)
#define GLB_REG_GPIO_5_SET                                      (1<<25U)
#define GLB_REG_GPIO_5_CLR                                      (1<<26U)
#define GLB_REG_GPIO_5_I                                        (1<<28U)
#define GLB_REG_GPIO_5_MODE_SHIFT                               (30U)
#define GLB_REG_GPIO_5_MODE_MASK                                (0x3<<GLB_REG_GPIO_5_MODE_SHIFT)

/* 0x8DC : gpio_cfg6 */
#define GLB_REG_GPIO_6_IE                                       (1<<0U)
#define GLB_REG_GPIO_6_SMT                                      (1<<1U)
#define GLB_REG_GPIO_6_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_6_DRV_MASK                                 (0x3<<GLB_REG_GPIO_6_DRV_SHIFT)
#define GLB_REG_GPIO_6_PU                                       (1<<4U)
#define GLB_REG_GPIO_6_PD                                       (1<<5U)
#define GLB_REG_GPIO_6_OE                                       (1<<6U)
#define GLB_REG_GPIO_6_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_6_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_6_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_6_INT_MODE_SET_SHIFT                       (16U)
#define GLB_REG_GPIO_6_INT_MODE_SET_MASK                        (0xf<<GLB_REG_GPIO_6_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_6_INT_CLR                                  (1<<20U)
#define GLB_GPIO_6_INT_STAT                                     (1<<21U)
#define GLB_REG_GPIO_6_INT_MASK                                 (1<<22U)
#define GLB_REG_GPIO_6_O                                        (1<<24U)
#define GLB_REG_GPIO_6_SET                                      (1<<25U)
#define GLB_REG_GPIO_6_CLR                                      (1<<26U)
#define GLB_REG_GPIO_6_I                                        (1<<28U)
#define GLB_REG_GPIO_6_MODE_SHIFT                               (30U)
#define GLB_REG_GPIO_6_MODE_MASK                                (0x3<<GLB_REG_GPIO_6_MODE_SHIFT)

/* 0x8E0 : gpio_cfg7 */
#define GLB_REG_GPIO_7_IE                                       (1<<0U)
#define GLB_REG_GPIO_7_SMT                                      (1<<1U)
#define GLB_REG_GPIO_7_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_7_DRV_MASK                                 (0x3<<GLB_REG_GPIO_7_DRV_SHIFT)
#define GLB_REG_GPIO_7_PU                                       (1<<4U)
#define GLB_REG_GPIO_7_PD                                       (1<<5U)
#define GLB_REG_GPIO_7_OE                                       (1<<6U)
#define GLB_REG_GPIO_7_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_7_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_7_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_7_INT_MODE_SET_SHIFT                       (16U)
#define GLB_REG_GPIO_7_INT_MODE_SET_MASK                        (0xf<<GLB_REG_GPIO_7_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_7_INT_CLR                                  (1<<20U)
#define GLB_GPIO_7_INT_STAT                                     (1<<21U)
#define GLB_REG_GPIO_7_INT_MASK                                 (1<<22U)
#define GLB_REG_GPIO_7_O                                        (1<<24U)
#define GLB_REG_GPIO_7_SET                                      (1<<25U)
#define GLB_REG_GPIO_7_CLR                                      (1<<26U)
#define GLB_REG_GPIO_7_I                                        (1<<28U)
#define GLB_REG_GPIO_7_MODE_SHIFT                               (30U)
#define GLB_REG_GPIO_7_MODE_MASK                                (0x3<<GLB_REG_GPIO_7_MODE_SHIFT)

/* 0x8E4 : gpio_cfg8 */
#define GLB_REG_GPIO_8_IE                                       (1<<0U)
#define GLB_REG_GPIO_8_SMT                                      (1<<1U)
#define GLB_REG_GPIO_8_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_8_DRV_MASK                                 (0x3<<GLB_REG_GPIO_8_DRV_SHIFT)
#define GLB_REG_GPIO_8_PU                                       (1<<4U)
#define GLB_REG_GPIO_8_PD                                       (1<<5U)
#define GLB_REG_GPIO_8_OE                                       (1<<6U)
#define GLB_REG_GPIO_8_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_8_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_8_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_8_INT_MODE_SET_SHIFT                       (16U)
#define GLB_REG_GPIO_8_INT_MODE_SET_MASK                        (0xf<<GLB_REG_GPIO_8_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_8_INT_CLR                                  (1<<20U)
#define GLB_GPIO_8_INT_STAT                                     (1<<21U)
#define GLB_REG_GPIO_8_INT_MASK                                 (1<<22U)
#define GLB_REG_GPIO_8_O                                        (1<<24U)
#define GLB_REG_GPIO_8_SET                                      (1<<25U)
#define GLB_REG_GPIO_8_CLR                                      (1<<26U)
#define GLB_REG_GPIO_8_I                                        (1<<28U)
#define GLB_REG_GPIO_8_MODE_SHIFT                               (30U)
#define GLB_REG_GPIO_8_MODE_MASK                                (0x3<<GLB_REG_GPIO_8_MODE_SHIFT)

/* 0x8E8 : gpio_cfg9 */
#define GLB_REG_GPIO_9_IE                                       (1<<0U)
#define GLB_REG_GPIO_9_SMT                                      (1<<1U)
#define GLB_REG_GPIO_9_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_9_DRV_MASK                                 (0x3<<GLB_REG_GPIO_9_DRV_SHIFT)
#define GLB_REG_GPIO_9_PU                                       (1<<4U)
#define GLB_REG_GPIO_9_PD                                       (1<<5U)
#define GLB_REG_GPIO_9_OE                                       (1<<6U)
#define GLB_REG_GPIO_9_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_9_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_9_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_9_INT_MODE_SET_SHIFT                       (16U)
#define GLB_REG_GPIO_9_INT_MODE_SET_MASK                        (0xf<<GLB_REG_GPIO_9_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_9_INT_CLR                                  (1<<20U)
#define GLB_GPIO_9_INT_STAT                                     (1<<21U)
#define GLB_REG_GPIO_9_INT_MASK                                 (1<<22U)
#define GLB_REG_GPIO_9_O                                        (1<<24U)
#define GLB_REG_GPIO_9_SET                                      (1<<25U)
#define GLB_REG_GPIO_9_CLR                                      (1<<26U)
#define GLB_REG_GPIO_9_I                                        (1<<28U)
#define GLB_REG_GPIO_9_MODE_SHIFT                               (30U)
#define GLB_REG_GPIO_9_MODE_MASK                                (0x3<<GLB_REG_GPIO_9_MODE_SHIFT)

/* 0x8EC : gpio_cfg10 */
#define GLB_REG_GPIO_10_IE                                      (1<<0U)
#define GLB_REG_GPIO_10_SMT                                     (1<<1U)
#define GLB_REG_GPIO_10_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_10_DRV_MASK                                (0x3<<GLB_REG_GPIO_10_DRV_SHIFT)
#define GLB_REG_GPIO_10_PU                                      (1<<4U)
#define GLB_REG_GPIO_10_PD                                      (1<<5U)
#define GLB_REG_GPIO_10_OE                                      (1<<6U)
#define GLB_REG_GPIO_10_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_10_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_10_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_10_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_10_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_10_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_10_INT_CLR                                 (1<<20U)
#define GLB_GPIO_10_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_10_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_10_O                                       (1<<24U)
#define GLB_REG_GPIO_10_SET                                     (1<<25U)
#define GLB_REG_GPIO_10_CLR                                     (1<<26U)
#define GLB_REG_GPIO_10_I                                       (1<<28U)
#define GLB_REG_GPIO_10_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_10_MODE_MASK                               (0x3<<GLB_REG_GPIO_10_MODE_SHIFT)

/* 0x8F0 : gpio_cfg11 */
#define GLB_REG_GPIO_11_IE                                      (1<<0U)
#define GLB_REG_GPIO_11_SMT                                     (1<<1U)
#define GLB_REG_GPIO_11_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_11_DRV_MASK                                (0x3<<GLB_REG_GPIO_11_DRV_SHIFT)
#define GLB_REG_GPIO_11_PU                                      (1<<4U)
#define GLB_REG_GPIO_11_PD                                      (1<<5U)
#define GLB_REG_GPIO_11_OE                                      (1<<6U)
#define GLB_REG_GPIO_11_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_11_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_11_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_11_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_11_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_11_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_11_INT_CLR                                 (1<<20U)
#define GLB_GPIO_11_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_11_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_11_O                                       (1<<24U)
#define GLB_REG_GPIO_11_SET                                     (1<<25U)
#define GLB_REG_GPIO_11_CLR                                     (1<<26U)
#define GLB_REG_GPIO_11_I                                       (1<<28U)
#define GLB_REG_GPIO_11_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_11_MODE_MASK                               (0x3<<GLB_REG_GPIO_11_MODE_SHIFT)

/* 0x8F4 : gpio_cfg12 */
#define GLB_REG_GPIO_12_IE                                      (1<<0U)
#define GLB_REG_GPIO_12_SMT                                     (1<<1U)
#define GLB_REG_GPIO_12_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_12_DRV_MASK                                (0x3<<GLB_REG_GPIO_12_DRV_SHIFT)
#define GLB_REG_GPIO_12_PU                                      (1<<4U)
#define GLB_REG_GPIO_12_PD                                      (1<<5U)
#define GLB_REG_GPIO_12_OE                                      (1<<6U)
#define GLB_REG_GPIO_12_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_12_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_12_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_12_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_12_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_12_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_12_INT_CLR                                 (1<<20U)
#define GLB_GPIO_12_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_12_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_12_O                                       (1<<24U)
#define GLB_REG_GPIO_12_SET                                     (1<<25U)
#define GLB_REG_GPIO_12_CLR                                     (1<<26U)
#define GLB_REG_GPIO_12_I                                       (1<<28U)
#define GLB_REG_GPIO_12_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_12_MODE_MASK                               (0x3<<GLB_REG_GPIO_12_MODE_SHIFT)

/* 0x8F8 : gpio_cfg13 */
#define GLB_REG_GPIO_13_IE                                      (1<<0U)
#define GLB_REG_GPIO_13_SMT                                     (1<<1U)
#define GLB_REG_GPIO_13_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_13_DRV_MASK                                (0x3<<GLB_REG_GPIO_13_DRV_SHIFT)
#define GLB_REG_GPIO_13_PU                                      (1<<4U)
#define GLB_REG_GPIO_13_PD                                      (1<<5U)
#define GLB_REG_GPIO_13_OE                                      (1<<6U)
#define GLB_REG_GPIO_13_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_13_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_13_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_13_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_13_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_13_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_13_INT_CLR                                 (1<<20U)
#define GLB_GPIO_13_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_13_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_13_O                                       (1<<24U)
#define GLB_REG_GPIO_13_SET                                     (1<<25U)
#define GLB_REG_GPIO_13_CLR                                     (1<<26U)
#define GLB_REG_GPIO_13_I                                       (1<<28U)
#define GLB_REG_GPIO_13_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_13_MODE_MASK                               (0x3<<GLB_REG_GPIO_13_MODE_SHIFT)

/* 0x8FC : gpio_cfg14 */
#define GLB_REG_GPIO_14_IE                                      (1<<0U)
#define GLB_REG_GPIO_14_SMT                                     (1<<1U)
#define GLB_REG_GPIO_14_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_14_DRV_MASK                                (0x3<<GLB_REG_GPIO_14_DRV_SHIFT)
#define GLB_REG_GPIO_14_PU                                      (1<<4U)
#define GLB_REG_GPIO_14_PD                                      (1<<5U)
#define GLB_REG_GPIO_14_OE                                      (1<<6U)
#define GLB_REG_GPIO_14_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_14_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_14_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_14_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_14_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_14_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_14_INT_CLR                                 (1<<20U)
#define GLB_GPIO_14_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_14_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_14_O                                       (1<<24U)
#define GLB_REG_GPIO_14_SET                                     (1<<25U)
#define GLB_REG_GPIO_14_CLR                                     (1<<26U)
#define GLB_REG_GPIO_14_I                                       (1<<28U)
#define GLB_REG_GPIO_14_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_14_MODE_MASK                               (0x3<<GLB_REG_GPIO_14_MODE_SHIFT)

/* 0x900 : gpio_cfg15 */
#define GLB_REG_GPIO_15_IE                                      (1<<0U)
#define GLB_REG_GPIO_15_SMT                                     (1<<1U)
#define GLB_REG_GPIO_15_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_15_DRV_MASK                                (0x3<<GLB_REG_GPIO_15_DRV_SHIFT)
#define GLB_REG_GPIO_15_PU                                      (1<<4U)
#define GLB_REG_GPIO_15_PD                                      (1<<5U)
#define GLB_REG_GPIO_15_OE                                      (1<<6U)
#define GLB_REG_GPIO_15_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_15_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_15_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_15_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_15_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_15_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_15_INT_CLR                                 (1<<20U)
#define GLB_GPIO_15_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_15_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_15_O                                       (1<<24U)
#define GLB_REG_GPIO_15_SET                                     (1<<25U)
#define GLB_REG_GPIO_15_CLR                                     (1<<26U)
#define GLB_REG_GPIO_15_I                                       (1<<28U)
#define GLB_REG_GPIO_15_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_15_MODE_MASK                               (0x3<<GLB_REG_GPIO_15_MODE_SHIFT)

/* 0x904 : gpio_cfg16 */
#define GLB_REG_GPIO_16_IE                                      (1<<0U)
#define GLB_REG_GPIO_16_SMT                                     (1<<1U)
#define GLB_REG_GPIO_16_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_16_DRV_MASK                                (0x3<<GLB_REG_GPIO_16_DRV_SHIFT)
#define GLB_REG_GPIO_16_PU                                      (1<<4U)
#define GLB_REG_GPIO_16_PD                                      (1<<5U)
#define GLB_REG_GPIO_16_OE                                      (1<<6U)
#define GLB_REG_GPIO_16_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_16_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_16_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_16_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_16_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_16_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_16_INT_CLR                                 (1<<20U)
#define GLB_GPIO_16_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_16_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_16_O                                       (1<<24U)
#define GLB_REG_GPIO_16_SET                                     (1<<25U)
#define GLB_REG_GPIO_16_CLR                                     (1<<26U)
#define GLB_REG_GPIO_16_I                                       (1<<28U)
#define GLB_REG_GPIO_16_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_16_MODE_MASK                               (0x3<<GLB_REG_GPIO_16_MODE_SHIFT)

/* 0x908 : gpio_cfg17 */
#define GLB_REG_GPIO_17_IE                                      (1<<0U)
#define GLB_REG_GPIO_17_SMT                                     (1<<1U)
#define GLB_REG_GPIO_17_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_17_DRV_MASK                                (0x3<<GLB_REG_GPIO_17_DRV_SHIFT)
#define GLB_REG_GPIO_17_PU                                      (1<<4U)
#define GLB_REG_GPIO_17_PD                                      (1<<5U)
#define GLB_REG_GPIO_17_OE                                      (1<<6U)
#define GLB_REG_GPIO_17_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_17_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_17_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_17_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_17_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_17_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_17_INT_CLR                                 (1<<20U)
#define GLB_GPIO_17_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_17_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_17_O                                       (1<<24U)
#define GLB_REG_GPIO_17_SET                                     (1<<25U)
#define GLB_REG_GPIO_17_CLR                                     (1<<26U)
#define GLB_REG_GPIO_17_I                                       (1<<28U)
#define GLB_REG_GPIO_17_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_17_MODE_MASK                               (0x3<<GLB_REG_GPIO_17_MODE_SHIFT)

/* 0x90C : gpio_cfg18 */
#define GLB_REG_GPIO_18_IE                                      (1<<0U)
#define GLB_REG_GPIO_18_SMT                                     (1<<1U)
#define GLB_REG_GPIO_18_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_18_DRV_MASK                                (0x3<<GLB_REG_GPIO_18_DRV_SHIFT)
#define GLB_REG_GPIO_18_PU                                      (1<<4U)
#define GLB_REG_GPIO_18_PD                                      (1<<5U)
#define GLB_REG_GPIO_18_OE                                      (1<<6U)
#define GLB_REG_GPIO_18_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_18_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_18_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_18_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_18_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_18_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_18_INT_CLR                                 (1<<20U)
#define GLB_GPIO_18_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_18_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_18_O                                       (1<<24U)
#define GLB_REG_GPIO_18_SET                                     (1<<25U)
#define GLB_REG_GPIO_18_CLR                                     (1<<26U)
#define GLB_REG_GPIO_18_I                                       (1<<28U)
#define GLB_REG_GPIO_18_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_18_MODE_MASK                               (0x3<<GLB_REG_GPIO_18_MODE_SHIFT)

/* 0x910 : gpio_cfg19 */
#define GLB_REG_GPIO_19_IE                                      (1<<0U)
#define GLB_REG_GPIO_19_SMT                                     (1<<1U)
#define GLB_REG_GPIO_19_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_19_DRV_MASK                                (0x3<<GLB_REG_GPIO_19_DRV_SHIFT)
#define GLB_REG_GPIO_19_PU                                      (1<<4U)
#define GLB_REG_GPIO_19_PD                                      (1<<5U)
#define GLB_REG_GPIO_19_OE                                      (1<<6U)
#define GLB_REG_GPIO_19_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_19_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_19_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_19_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_19_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_19_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_19_INT_CLR                                 (1<<20U)
#define GLB_GPIO_19_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_19_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_19_O                                       (1<<24U)
#define GLB_REG_GPIO_19_SET                                     (1<<25U)
#define GLB_REG_GPIO_19_CLR                                     (1<<26U)
#define GLB_REG_GPIO_19_I                                       (1<<28U)
#define GLB_REG_GPIO_19_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_19_MODE_MASK                               (0x3<<GLB_REG_GPIO_19_MODE_SHIFT)

/* 0x914 : gpio_cfg20 */
#define GLB_REG_GPIO_20_IE                                      (1<<0U)
#define GLB_REG_GPIO_20_SMT                                     (1<<1U)
#define GLB_REG_GPIO_20_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_20_DRV_MASK                                (0x3<<GLB_REG_GPIO_20_DRV_SHIFT)
#define GLB_REG_GPIO_20_PU                                      (1<<4U)
#define GLB_REG_GPIO_20_PD                                      (1<<5U)
#define GLB_REG_GPIO_20_OE                                      (1<<6U)
#define GLB_REG_GPIO_20_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_20_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_20_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_20_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_20_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_20_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_20_INT_CLR                                 (1<<20U)
#define GLB_GPIO_20_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_20_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_20_O                                       (1<<24U)
#define GLB_REG_GPIO_20_SET                                     (1<<25U)
#define GLB_REG_GPIO_20_CLR                                     (1<<26U)
#define GLB_REG_GPIO_20_I                                       (1<<28U)
#define GLB_REG_GPIO_20_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_20_MODE_MASK                               (0x3<<GLB_REG_GPIO_20_MODE_SHIFT)

/* 0x918 : gpio_cfg21 */
#define GLB_REG_GPIO_21_IE                                      (1<<0U)
#define GLB_REG_GPIO_21_SMT                                     (1<<1U)
#define GLB_REG_GPIO_21_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_21_DRV_MASK                                (0x3<<GLB_REG_GPIO_21_DRV_SHIFT)
#define GLB_REG_GPIO_21_PU                                      (1<<4U)
#define GLB_REG_GPIO_21_PD                                      (1<<5U)
#define GLB_REG_GPIO_21_OE                                      (1<<6U)
#define GLB_REG_GPIO_21_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_21_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_21_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_21_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_21_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_21_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_21_INT_CLR                                 (1<<20U)
#define GLB_GPIO_21_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_21_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_21_O                                       (1<<24U)
#define GLB_REG_GPIO_21_SET                                     (1<<25U)
#define GLB_REG_GPIO_21_CLR                                     (1<<26U)
#define GLB_REG_GPIO_21_I                                       (1<<28U)
#define GLB_REG_GPIO_21_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_21_MODE_MASK                               (0x3<<GLB_REG_GPIO_21_MODE_SHIFT)

/* 0x91C : gpio_cfg22 */
#define GLB_REG_GPIO_22_IE                                      (1<<0U)
#define GLB_REG_GPIO_22_SMT                                     (1<<1U)
#define GLB_REG_GPIO_22_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_22_DRV_MASK                                (0x3<<GLB_REG_GPIO_22_DRV_SHIFT)
#define GLB_REG_GPIO_22_PU                                      (1<<4U)
#define GLB_REG_GPIO_22_PD                                      (1<<5U)
#define GLB_REG_GPIO_22_OE                                      (1<<6U)
#define GLB_REG_GPIO_22_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_22_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_22_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_22_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_22_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_22_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_22_INT_CLR                                 (1<<20U)
#define GLB_GPIO_22_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_22_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_22_O                                       (1<<24U)
#define GLB_REG_GPIO_22_SET                                     (1<<25U)
#define GLB_REG_GPIO_22_CLR                                     (1<<26U)
#define GLB_REG_GPIO_22_I                                       (1<<28U)
#define GLB_REG_GPIO_22_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_22_MODE_MASK                               (0x3<<GLB_REG_GPIO_22_MODE_SHIFT)

/* 0x920 : gpio_cfg23 */
#define GLB_REG_GPIO_23_IE                                      (1<<0U)
#define GLB_REG_GPIO_23_SMT                                     (1<<1U)
#define GLB_REG_GPIO_23_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_23_DRV_MASK                                (0x3<<GLB_REG_GPIO_23_DRV_SHIFT)
#define GLB_REG_GPIO_23_PU                                      (1<<4U)
#define GLB_REG_GPIO_23_PD                                      (1<<5U)
#define GLB_REG_GPIO_23_OE                                      (1<<6U)
#define GLB_REG_GPIO_23_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_23_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_23_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_23_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_23_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_23_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_23_INT_CLR                                 (1<<20U)
#define GLB_GPIO_23_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_23_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_23_O                                       (1<<24U)
#define GLB_REG_GPIO_23_SET                                     (1<<25U)
#define GLB_REG_GPIO_23_CLR                                     (1<<26U)
#define GLB_REG_GPIO_23_I                                       (1<<28U)
#define GLB_REG_GPIO_23_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_23_MODE_MASK                               (0x3<<GLB_REG_GPIO_23_MODE_SHIFT)

/* 0x924 : gpio_cfg24 */
#define GLB_REG_GPIO_24_IE                                      (1<<0U)
#define GLB_REG_GPIO_24_SMT                                     (1<<1U)
#define GLB_REG_GPIO_24_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_24_DRV_MASK                                (0x3<<GLB_REG_GPIO_24_DRV_SHIFT)
#define GLB_REG_GPIO_24_PU                                      (1<<4U)
#define GLB_REG_GPIO_24_PD                                      (1<<5U)
#define GLB_REG_GPIO_24_OE                                      (1<<6U)
#define GLB_REG_GPIO_24_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_24_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_24_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_24_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_24_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_24_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_24_INT_CLR                                 (1<<20U)
#define GLB_GPIO_24_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_24_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_24_O                                       (1<<24U)
#define GLB_REG_GPIO_24_SET                                     (1<<25U)
#define GLB_REG_GPIO_24_CLR                                     (1<<26U)
#define GLB_REG_GPIO_24_I                                       (1<<28U)
#define GLB_REG_GPIO_24_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_24_MODE_MASK                               (0x3<<GLB_REG_GPIO_24_MODE_SHIFT)

/* 0x928 : gpio_cfg25 */
#define GLB_REG_GPIO_25_IE                                      (1<<0U)
#define GLB_REG_GPIO_25_SMT                                     (1<<1U)
#define GLB_REG_GPIO_25_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_25_DRV_MASK                                (0x3<<GLB_REG_GPIO_25_DRV_SHIFT)
#define GLB_REG_GPIO_25_PU                                      (1<<4U)
#define GLB_REG_GPIO_25_PD                                      (1<<5U)
#define GLB_REG_GPIO_25_OE                                      (1<<6U)
#define GLB_REG_GPIO_25_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_25_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_25_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_25_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_25_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_25_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_25_INT_CLR                                 (1<<20U)
#define GLB_GPIO_25_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_25_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_25_O                                       (1<<24U)
#define GLB_REG_GPIO_25_SET                                     (1<<25U)
#define GLB_REG_GPIO_25_CLR                                     (1<<26U)
#define GLB_REG_GPIO_25_I                                       (1<<28U)
#define GLB_REG_GPIO_25_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_25_MODE_MASK                               (0x3<<GLB_REG_GPIO_25_MODE_SHIFT)

/* 0x92C : gpio_cfg26 */
#define GLB_REG_GPIO_26_IE                                      (1<<0U)
#define GLB_REG_GPIO_26_SMT                                     (1<<1U)
#define GLB_REG_GPIO_26_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_26_DRV_MASK                                (0x3<<GLB_REG_GPIO_26_DRV_SHIFT)
#define GLB_REG_GPIO_26_PU                                      (1<<4U)
#define GLB_REG_GPIO_26_PD                                      (1<<5U)
#define GLB_REG_GPIO_26_OE                                      (1<<6U)
#define GLB_REG_GPIO_26_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_26_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_26_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_26_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_26_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_26_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_26_INT_CLR                                 (1<<20U)
#define GLB_GPIO_26_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_26_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_26_O                                       (1<<24U)
#define GLB_REG_GPIO_26_SET                                     (1<<25U)
#define GLB_REG_GPIO_26_CLR                                     (1<<26U)
#define GLB_REG_GPIO_26_I                                       (1<<28U)
#define GLB_REG_GPIO_26_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_26_MODE_MASK                               (0x3<<GLB_REG_GPIO_26_MODE_SHIFT)

/* 0x930 : gpio_cfg27 */
#define GLB_REG_GPIO_27_IE                                      (1<<0U)
#define GLB_REG_GPIO_27_SMT                                     (1<<1U)
#define GLB_REG_GPIO_27_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_27_DRV_MASK                                (0x3<<GLB_REG_GPIO_27_DRV_SHIFT)
#define GLB_REG_GPIO_27_PU                                      (1<<4U)
#define GLB_REG_GPIO_27_PD                                      (1<<5U)
#define GLB_REG_GPIO_27_OE                                      (1<<6U)
#define GLB_REG_GPIO_27_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_27_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_27_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_27_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_27_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_27_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_27_INT_CLR                                 (1<<20U)
#define GLB_GPIO_27_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_27_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_27_O                                       (1<<24U)
#define GLB_REG_GPIO_27_SET                                     (1<<25U)
#define GLB_REG_GPIO_27_CLR                                     (1<<26U)
#define GLB_REG_GPIO_27_I                                       (1<<28U)
#define GLB_REG_GPIO_27_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_27_MODE_MASK                               (0x3<<GLB_REG_GPIO_27_MODE_SHIFT)

/* 0x934 : gpio_cfg28 */
#define GLB_REG_GPIO_28_IE                                      (1<<0U)
#define GLB_REG_GPIO_28_SMT                                     (1<<1U)
#define GLB_REG_GPIO_28_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_28_DRV_MASK                                (0x3<<GLB_REG_GPIO_28_DRV_SHIFT)
#define GLB_REG_GPIO_28_PU                                      (1<<4U)
#define GLB_REG_GPIO_28_PD                                      (1<<5U)
#define GLB_REG_GPIO_28_OE                                      (1<<6U)
#define GLB_REG_GPIO_28_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_28_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_28_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_28_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_28_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_28_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_28_INT_CLR                                 (1<<20U)
#define GLB_GPIO_28_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_28_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_28_O                                       (1<<24U)
#define GLB_REG_GPIO_28_SET                                     (1<<25U)
#define GLB_REG_GPIO_28_CLR                                     (1<<26U)
#define GLB_REG_GPIO_28_I                                       (1<<28U)
#define GLB_REG_GPIO_28_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_28_MODE_MASK                               (0x3<<GLB_REG_GPIO_28_MODE_SHIFT)

/* 0x938 : gpio_cfg29 */
#define GLB_REG_GPIO_29_IE                                      (1<<0U)
#define GLB_REG_GPIO_29_SMT                                     (1<<1U)
#define GLB_REG_GPIO_29_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_29_DRV_MASK                                (0x3<<GLB_REG_GPIO_29_DRV_SHIFT)
#define GLB_REG_GPIO_29_PU                                      (1<<4U)
#define GLB_REG_GPIO_29_PD                                      (1<<5U)
#define GLB_REG_GPIO_29_OE                                      (1<<6U)
#define GLB_REG_GPIO_29_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_29_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_29_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_29_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_29_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_29_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_29_INT_CLR                                 (1<<20U)
#define GLB_GPIO_29_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_29_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_29_O                                       (1<<24U)
#define GLB_REG_GPIO_29_SET                                     (1<<25U)
#define GLB_REG_GPIO_29_CLR                                     (1<<26U)
#define GLB_REG_GPIO_29_I                                       (1<<28U)
#define GLB_REG_GPIO_29_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_29_MODE_MASK                               (0x3<<GLB_REG_GPIO_29_MODE_SHIFT)

/* 0x93C : gpio_cfg30 */
#define GLB_REG_GPIO_30_IE                                      (1<<0U)
#define GLB_REG_GPIO_30_SMT                                     (1<<1U)
#define GLB_REG_GPIO_30_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_30_DRV_MASK                                (0x3<<GLB_REG_GPIO_30_DRV_SHIFT)
#define GLB_REG_GPIO_30_PU                                      (1<<4U)
#define GLB_REG_GPIO_30_PD                                      (1<<5U)
#define GLB_REG_GPIO_30_OE                                      (1<<6U)
#define GLB_REG_GPIO_30_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_30_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_30_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_30_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_30_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_30_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_30_INT_CLR                                 (1<<20U)
#define GLB_GPIO_30_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_30_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_30_O                                       (1<<24U)
#define GLB_REG_GPIO_30_SET                                     (1<<25U)
#define GLB_REG_GPIO_30_CLR                                     (1<<26U)
#define GLB_REG_GPIO_30_I                                       (1<<28U)
#define GLB_REG_GPIO_30_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_30_MODE_MASK                               (0x3<<GLB_REG_GPIO_30_MODE_SHIFT)

/* 0x940 : gpio_cfg31 */
#define GLB_REG_GPIO_31_IE                                      (1<<0U)
#define GLB_REG_GPIO_31_SMT                                     (1<<1U)
#define GLB_REG_GPIO_31_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_31_DRV_MASK                                (0x3<<GLB_REG_GPIO_31_DRV_SHIFT)
#define GLB_REG_GPIO_31_PU                                      (1<<4U)
#define GLB_REG_GPIO_31_PD                                      (1<<5U)
#define GLB_REG_GPIO_31_OE                                      (1<<6U)
#define GLB_REG_GPIO_31_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_31_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_31_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_31_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_31_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_31_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_31_INT_CLR                                 (1<<20U)
#define GLB_GPIO_31_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_31_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_31_O                                       (1<<24U)
#define GLB_REG_GPIO_31_SET                                     (1<<25U)
#define GLB_REG_GPIO_31_CLR                                     (1<<26U)
#define GLB_REG_GPIO_31_I                                       (1<<28U)
#define GLB_REG_GPIO_31_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_31_MODE_MASK                               (0x3<<GLB_REG_GPIO_31_MODE_SHIFT)

/* 0x944 : gpio_cfg32 */
#define GLB_REG_GPIO_32_IE                                      (1<<0U)
#define GLB_REG_GPIO_32_SMT                                     (1<<1U)
#define GLB_REG_GPIO_32_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_32_DRV_MASK                                (0x3<<GLB_REG_GPIO_32_DRV_SHIFT)
#define GLB_REG_GPIO_32_PU                                      (1<<4U)
#define GLB_REG_GPIO_32_PD                                      (1<<5U)
#define GLB_REG_GPIO_32_OE                                      (1<<6U)
#define GLB_REG_GPIO_32_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_32_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_32_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_32_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_32_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_32_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_32_INT_CLR                                 (1<<20U)
#define GLB_GPIO_32_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_32_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_32_O                                       (1<<24U)
#define GLB_REG_GPIO_32_SET                                     (1<<25U)
#define GLB_REG_GPIO_32_CLR                                     (1<<26U)
#define GLB_REG_GPIO_32_I                                       (1<<28U)
#define GLB_REG_GPIO_32_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_32_MODE_MASK                               (0x3<<GLB_REG_GPIO_32_MODE_SHIFT)

/* 0x948 : gpio_cfg33 */
#define GLB_REG_GPIO_33_IE                                      (1<<0U)
#define GLB_REG_GPIO_33_SMT                                     (1<<1U)
#define GLB_REG_GPIO_33_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_33_DRV_MASK                                (0x3<<GLB_REG_GPIO_33_DRV_SHIFT)
#define GLB_REG_GPIO_33_PU                                      (1<<4U)
#define GLB_REG_GPIO_33_PD                                      (1<<5U)
#define GLB_REG_GPIO_33_OE                                      (1<<6U)
#define GLB_REG_GPIO_33_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_33_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_33_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_33_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_33_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_33_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_33_INT_CLR                                 (1<<20U)
#define GLB_GPIO_33_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_33_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_33_O                                       (1<<24U)
#define GLB_REG_GPIO_33_SET                                     (1<<25U)
#define GLB_REG_GPIO_33_CLR                                     (1<<26U)
#define GLB_REG_GPIO_33_I                                       (1<<28U)
#define GLB_REG_GPIO_33_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_33_MODE_MASK                               (0x3<<GLB_REG_GPIO_33_MODE_SHIFT)

/* 0x94C : gpio_cfg34 */
#define GLB_REG_GPIO_34_IE                                      (1<<0U)
#define GLB_REG_GPIO_34_SMT                                     (1<<1U)
#define GLB_REG_GPIO_34_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_34_DRV_MASK                                (0x3<<GLB_REG_GPIO_34_DRV_SHIFT)
#define GLB_REG_GPIO_34_PU                                      (1<<4U)
#define GLB_REG_GPIO_34_PD                                      (1<<5U)
#define GLB_REG_GPIO_34_OE                                      (1<<6U)
#define GLB_REG_GPIO_34_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_34_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_34_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_34_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_34_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_34_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_34_INT_CLR                                 (1<<20U)
#define GLB_GPIO_34_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_34_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_34_O                                       (1<<24U)
#define GLB_REG_GPIO_34_SET                                     (1<<25U)
#define GLB_REG_GPIO_34_CLR                                     (1<<26U)
#define GLB_REG_GPIO_34_I                                       (1<<28U)
#define GLB_REG_GPIO_34_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_34_MODE_MASK                               (0x3<<GLB_REG_GPIO_34_MODE_SHIFT)

/* 0x950 : gpio_cfg35 */
#define GLB_REG_GPIO_35_IE                                      (1<<0U)
#define GLB_REG_GPIO_35_SMT                                     (1<<1U)
#define GLB_REG_GPIO_35_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_35_DRV_MASK                                (0x3<<GLB_REG_GPIO_35_DRV_SHIFT)
#define GLB_REG_GPIO_35_PU                                      (1<<4U)
#define GLB_REG_GPIO_35_PD                                      (1<<5U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG_GPIO_35_OE                                      (1<<6U)
#define GLB_REG_GPIO_35_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_35_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_35_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_35_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_35_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_35_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_35_INT_CLR                                 (1<<20U)
#define GLB_GPIO_35_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_35_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_35_O                                       (1<<24U)
#define GLB_REG_GPIO_35_SET                                     (1<<25U)
#define GLB_REG_GPIO_35_CLR                                     (1<<26U)
#define GLB_REG_GPIO_35_I                                       (1<<28U)
#define GLB_REG_GPIO_35_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_35_MODE_MASK                               (0x3<<GLB_REG_GPIO_35_MODE_SHIFT)
#endif

/* 0x954 : gpio_cfg36 */
#define GLB_REG_GPIO_36_IE                                      (1<<0U)
#define GLB_REG_GPIO_36_SMT                                     (1<<1U)
#define GLB_REG_GPIO_36_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_36_DRV_MASK                                (0x3<<GLB_REG_GPIO_36_DRV_SHIFT)
#define GLB_REG_GPIO_36_PU                                      (1<<4U)
#define GLB_REG_GPIO_36_PD                                      (1<<5U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG_GPIO_36_OE                                      (1<<6U)
#define GLB_REG_GPIO_36_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_36_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_36_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_36_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_36_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_36_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_36_INT_CLR                                 (1<<20U)
#define GLB_GPIO_36_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_36_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_36_O                                       (1<<24U)
#define GLB_REG_GPIO_36_SET                                     (1<<25U)
#define GLB_REG_GPIO_36_CLR                                     (1<<26U)
#define GLB_REG_GPIO_36_I                                       (1<<28U)
#define GLB_REG_GPIO_36_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_36_MODE_MASK                               (0x3<<GLB_REG_GPIO_36_MODE_SHIFT)
#endif

/* 0x958 : gpio_cfg37 */
#define GLB_REG_GPIO_37_IE                                      (1<<0U)
#define GLB_REG_GPIO_37_SMT                                     (1<<1U)
#define GLB_REG_GPIO_37_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_37_DRV_MASK                                (0x3<<GLB_REG_GPIO_37_DRV_SHIFT)
#define GLB_REG_GPIO_37_PU                                      (1<<4U)
#define GLB_REG_GPIO_37_PD                                      (1<<5U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG_GPIO_37_OE                                      (1<<6U)
#define GLB_REG_GPIO_37_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_37_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_37_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_37_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_37_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_37_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_37_INT_CLR                                 (1<<20U)
#define GLB_GPIO_37_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_37_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_37_O                                       (1<<24U)
#define GLB_REG_GPIO_37_SET                                     (1<<25U)
#define GLB_REG_GPIO_37_CLR                                     (1<<26U)
#define GLB_REG_GPIO_37_I                                       (1<<28U)
#define GLB_REG_GPIO_37_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_37_MODE_MASK                               (0x3<<GLB_REG_GPIO_37_MODE_SHIFT)
#endif

/* 0x95C : gpio_cfg38 */
#define GLB_REG_GPIO_38_IE                                      (1<<0U)
#define GLB_REG_GPIO_38_SMT                                     (1<<1U)
#define GLB_REG_GPIO_38_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_38_DRV_MASK                                (0x3<<GLB_REG_GPIO_38_DRV_SHIFT)
#define GLB_REG_GPIO_38_PU                                      (1<<4U)
#define GLB_REG_GPIO_38_PD                                      (1<<5U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG_GPIO_38_OE                                      (1<<6U)
#define GLB_REG_GPIO_38_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_38_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_38_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_38_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_38_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_38_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_38_INT_CLR                                 (1<<20U)
#define GLB_GPIO_38_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_38_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_38_O                                       (1<<24U)
#define GLB_REG_GPIO_38_SET                                     (1<<25U)
#define GLB_REG_GPIO_38_CLR                                     (1<<26U)
#define GLB_REG_GPIO_38_I                                       (1<<28U)
#define GLB_REG_GPIO_38_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_38_MODE_MASK                               (0x3<<GLB_REG_GPIO_38_MODE_SHIFT)
#endif

/* 0x960 : gpio_cfg39 */
#define GLB_REG_GPIO_39_IE                                      (1<<0U)
#define GLB_REG_GPIO_39_SMT                                     (1<<1U)
#define GLB_REG_GPIO_39_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_39_DRV_MASK                                (0x3<<GLB_REG_GPIO_39_DRV_SHIFT)
#define GLB_REG_GPIO_39_PU                                      (1<<4U)
#define GLB_REG_GPIO_39_PD                                      (1<<5U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG_GPIO_39_OE                                      (1<<6U)
#define GLB_REG_GPIO_39_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_39_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_39_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_39_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_39_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_39_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_39_INT_CLR                                 (1<<20U)
#define GLB_GPIO_39_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_39_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_39_O                                       (1<<24U)
#define GLB_REG_GPIO_39_SET                                     (1<<25U)
#define GLB_REG_GPIO_39_CLR                                     (1<<26U)
#define GLB_REG_GPIO_39_I                                       (1<<28U)
#define GLB_REG_GPIO_39_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_39_MODE_MASK                               (0x3<<GLB_REG_GPIO_39_MODE_SHIFT)
#endif

/* 0x964 : gpio_cfg40 */
#define GLB_REG_GPIO_40_IE                                      (1<<0U)
#define GLB_REG_GPIO_40_SMT                                     (1<<1U)
#define GLB_REG_GPIO_40_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_40_DRV_MASK                                (0x3<<GLB_REG_GPIO_40_DRV_SHIFT)
#define GLB_REG_GPIO_40_PU                                      (1<<4U)
#define GLB_REG_GPIO_40_PD                                      (1<<5U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG_GPIO_40_OE                                      (1<<6U)
#define GLB_REG_GPIO_40_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_40_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_40_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_40_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_40_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_40_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_40_INT_CLR                                 (1<<20U)
#define GLB_GPIO_40_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_40_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_40_O                                       (1<<24U)
#define GLB_REG_GPIO_40_SET                                     (1<<25U)
#define GLB_REG_GPIO_40_CLR                                     (1<<26U)
#define GLB_REG_GPIO_40_I                                       (1<<28U)
#define GLB_REG_GPIO_40_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_40_MODE_MASK                               (0x3<<GLB_REG_GPIO_40_MODE_SHIFT)
#endif

/* 0x968 : gpio_cfg41 */
#define GLB_REG_GPIO_41_IE                                      (1<<0U)
#define GLB_REG_GPIO_41_SMT                                     (1<<1U)
#define GLB_REG_GPIO_41_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_41_DRV_MASK                                (0x3<<GLB_REG_GPIO_41_DRV_SHIFT)
#define GLB_REG_GPIO_41_PU                                      (1<<4U)
#define GLB_REG_GPIO_41_PD                                      (1<<5U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG_GPIO_41_OE                                      (1<<6U)
#define GLB_REG_GPIO_41_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_41_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_41_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_41_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_41_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_41_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_41_INT_CLR                                 (1<<20U)
#define GLB_GPIO_41_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_41_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_41_O                                       (1<<24U)
#define GLB_REG_GPIO_41_SET                                     (1<<25U)
#define GLB_REG_GPIO_41_CLR                                     (1<<26U)
#define GLB_REG_GPIO_41_I                                       (1<<28U)
#define GLB_REG_GPIO_41_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_41_MODE_MASK                               (0x3<<GLB_REG_GPIO_41_MODE_SHIFT)
#endif

/* 0x96C : gpio_cfg42 */
#define GLB_REG_GPIO_42_IE                                      (1<<0U)
#define GLB_REG_GPIO_42_SMT                                     (1<<1U)
#define GLB_REG_GPIO_42_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_42_DRV_MASK                                (0x3<<GLB_REG_GPIO_42_DRV_SHIFT)
#define GLB_REG_GPIO_42_PU                                      (1<<4U)
#define GLB_REG_GPIO_42_PD                                      (1<<5U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG_GPIO_42_OE                                      (1<<6U)
#define GLB_REG_GPIO_42_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_42_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_42_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_42_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_42_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_42_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_42_INT_CLR                                 (1<<20U)
#define GLB_GPIO_42_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_42_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_42_O                                       (1<<24U)
#define GLB_REG_GPIO_42_SET                                     (1<<25U)
#define GLB_REG_GPIO_42_CLR                                     (1<<26U)
#define GLB_REG_GPIO_42_I                                       (1<<28U)
#define GLB_REG_GPIO_42_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_42_MODE_MASK                               (0x3<<GLB_REG_GPIO_42_MODE_SHIFT)
#endif

/* 0x970 : gpio_cfg43 */
#define GLB_REG_GPIO_43_IE                                      (1<<0U)
#define GLB_REG_GPIO_43_SMT                                     (1<<1U)
#define GLB_REG_GPIO_43_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_43_DRV_MASK                                (0x3<<GLB_REG_GPIO_43_DRV_SHIFT)
#define GLB_REG_GPIO_43_PU                                      (1<<4U)
#define GLB_REG_GPIO_43_PD                                      (1<<5U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG_GPIO_43_OE                                      (1<<6U)
#define GLB_REG_GPIO_43_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_43_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_43_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_43_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_43_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_43_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_43_INT_CLR                                 (1<<20U)
#define GLB_GPIO_43_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_43_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_43_O                                       (1<<24U)
#define GLB_REG_GPIO_43_SET                                     (1<<25U)
#define GLB_REG_GPIO_43_CLR                                     (1<<26U)
#define GLB_REG_GPIO_43_I                                       (1<<28U)
#define GLB_REG_GPIO_43_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_43_MODE_MASK                               (0x3<<GLB_REG_GPIO_43_MODE_SHIFT)
#endif

/* 0x974 : gpio_cfg44 */
#define GLB_REG_GPIO_44_IE                                      (1<<0U)
#define GLB_REG_GPIO_44_SMT                                     (1<<1U)
#define GLB_REG_GPIO_44_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_44_DRV_MASK                                (0x3<<GLB_REG_GPIO_44_DRV_SHIFT)
#define GLB_REG_GPIO_44_PU                                      (1<<4U)
#define GLB_REG_GPIO_44_PD                                      (1<<5U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG_GPIO_44_OE                                      (1<<6U)
#define GLB_REG_GPIO_44_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_44_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_44_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_44_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_44_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_44_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_44_INT_CLR                                 (1<<20U)
#define GLB_GPIO_44_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_44_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_44_O                                       (1<<24U)
#define GLB_REG_GPIO_44_SET                                     (1<<25U)
#define GLB_REG_GPIO_44_CLR                                     (1<<26U)
#define GLB_REG_GPIO_44_I                                       (1<<28U)
#define GLB_REG_GPIO_44_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_44_MODE_MASK                               (0x3<<GLB_REG_GPIO_44_MODE_SHIFT)
#endif

/* 0x978 : gpio_cfg45 */
#define GLB_REG_GPIO_45_IE                                      (1<<0U)
#define GLB_REG_GPIO_45_SMT                                     (1<<1U)
#define GLB_REG_GPIO_45_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_45_DRV_MASK                                (0x3<<GLB_REG_GPIO_45_DRV_SHIFT)
#define GLB_REG_GPIO_45_PU                                      (1<<4U)
#define GLB_REG_GPIO_45_PD                                      (1<<5U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG_GPIO_45_OE                                      (1<<6U)
#define GLB_REG_GPIO_45_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_45_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_45_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_45_INT_MODE_SET_SHIFT                      (16U)
#define GLB_REG_GPIO_45_INT_MODE_SET_MASK                       (0xf<<GLB_REG_GPIO_45_INT_MODE_SET_SHIFT)
#define GLB_REG_GPIO_45_INT_CLR                                 (1<<20U)
#define GLB_GPIO_45_INT_STAT                                    (1<<21U)
#define GLB_REG_GPIO_45_INT_MASK                                (1<<22U)
#define GLB_REG_GPIO_45_O                                       (1<<24U)
#define GLB_REG_GPIO_45_SET                                     (1<<25U)
#define GLB_REG_GPIO_45_CLR                                     (1<<26U)
#define GLB_REG_GPIO_45_I                                       (1<<28U)
#define GLB_REG_GPIO_45_MODE_SHIFT                              (30U)
#define GLB_REG_GPIO_45_MODE_MASK                               (0x3<<GLB_REG_GPIO_45_MODE_SHIFT)
#endif

/* 0x97C : gpio_cfg46 */
#define GLB_REG_GPIO_46_IE                                      (1<<0U)
#define GLB_REG_GPIO_46_SMT                                     (1<<1U)
#define GLB_REG_GPIO_46_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_46_DRV_MASK                                (0x3<<GLB_REG_GPIO_46_DRV_SHIFT)
#define GLB_REG_GPIO_46_PU                                      (1<<4U)
#define GLB_REG_GPIO_46_PD                                      (1<<5U)

/* 0x980 : gpio_cfg47 */
#define GLB_REG_GPIO_47_IE                                      (1<<0U)
#define GLB_REG_GPIO_47_SMT                                     (1<<1U)
#define GLB_REG_GPIO_47_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_47_DRV_MASK                                (0x3<<GLB_REG_GPIO_47_DRV_SHIFT)
#define GLB_REG_GPIO_47_PU                                      (1<<4U)
#define GLB_REG_GPIO_47_PD                                      (1<<5U)

/* 0x984 : gpio_cfg48 */
#define GLB_REG_GPIO_48_IE                                      (1<<0U)
#define GLB_REG_GPIO_48_SMT                                     (1<<1U)
#define GLB_REG_GPIO_48_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_48_DRV_MASK                                (0x3<<GLB_REG_GPIO_48_DRV_SHIFT)
#define GLB_REG_GPIO_48_PU                                      (1<<4U)
#define GLB_REG_GPIO_48_PD                                      (1<<5U)

/* 0x988 : gpio_cfg49 */
#define GLB_REG_GPIO_49_IE                                      (1<<0U)
#define GLB_REG_GPIO_49_SMT                                     (1<<1U)
#define GLB_REG_GPIO_49_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_49_DRV_MASK                                (0x3<<GLB_REG_GPIO_49_DRV_SHIFT)
#define GLB_REG_GPIO_49_PU                                      (1<<4U)
#define GLB_REG_GPIO_49_PD                                      (1<<5U)

/* 0x98C : gpio_cfg50 */
#define GLB_REG_GPIO_50_IE                                      (1<<0U)
#define GLB_REG_GPIO_50_SMT                                     (1<<1U)
#define GLB_REG_GPIO_50_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_50_DRV_MASK                                (0x3<<GLB_REG_GPIO_50_DRV_SHIFT)
#define GLB_REG_GPIO_50_PU                                      (1<<4U)
#define GLB_REG_GPIO_50_PD                                      (1<<5U)

/* 0x990 : gpio_cfg51 */
#define GLB_REG_GPIO_51_IE                                      (1<<0U)
#define GLB_REG_GPIO_51_SMT                                     (1<<1U)
#define GLB_REG_GPIO_51_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_51_DRV_MASK                                (0x3<<GLB_REG_GPIO_51_DRV_SHIFT)
#define GLB_REG_GPIO_51_PU                                      (1<<4U)
#define GLB_REG_GPIO_51_PD                                      (1<<5U)

/* 0x994 : gpio_cfg52 */
#define GLB_REG_GPIO_52_IE                                      (1<<0U)
#define GLB_REG_GPIO_52_SMT                                     (1<<1U)
#define GLB_REG_GPIO_52_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_52_DRV_MASK                                (0x3<<GLB_REG_GPIO_52_DRV_SHIFT)
#define GLB_REG_GPIO_52_PU                                      (1<<4U)
#define GLB_REG_GPIO_52_PD                                      (1<<5U)

/* 0x998 : gpio_cfg53 */
#define GLB_REG_GPIO_53_IE                                      (1<<0U)
#define GLB_REG_GPIO_53_SMT                                     (1<<1U)
#define GLB_REG_GPIO_53_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_53_DRV_MASK                                (0x3<<GLB_REG_GPIO_53_DRV_SHIFT)
#define GLB_REG_GPIO_53_PU                                      (1<<4U)
#define GLB_REG_GPIO_53_PD                                      (1<<5U)

/* 0x99C : gpio_cfg54 */
#define GLB_REG_GPIO_54_IE                                      (1<<0U)
#define GLB_REG_GPIO_54_SMT                                     (1<<1U)
#define GLB_REG_GPIO_54_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_54_DRV_MASK                                (0x3<<GLB_REG_GPIO_54_DRV_SHIFT)
#define GLB_REG_GPIO_54_PU                                      (1<<4U)
#define GLB_REG_GPIO_54_PD                                      (1<<5U)

/* 0x9A0 : gpio_cfg55 */
#define GLB_REG_GPIO_55_IE                                      (1<<0U)
#define GLB_REG_GPIO_55_SMT                                     (1<<1U)
#define GLB_REG_GPIO_55_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_55_DRV_MASK                                (0x3<<GLB_REG_GPIO_55_DRV_SHIFT)
#define GLB_REG_GPIO_55_PU                                      (1<<4U)
#define GLB_REG_GPIO_55_PD                                      (1<<5U)

/* 0x9A4 : gpio_cfg56 */

/* 0x9A8 : gpio_cfg57 */

/* 0x9AC : gpio_cfg58 */

/* 0x9B0 : gpio_cfg59 */

/* 0x9B4 : gpio_cfg60 */

/* 0x9B8 : gpio_cfg61 */

/* 0x9BC : gpio_cfg62 */

/* 0x9C0 : gpio_cfg63 */

/* 0xAC4 : gpio_cfg128 */
#define GLB_REG2_GPIO_0_I                                       (1<<0U)
#define GLB_REG2_GPIO_1_I                                       (1<<1U)
#define GLB_REG2_GPIO_2_I                                       (1<<2U)
#define GLB_REG2_GPIO_3_I                                       (1<<3U)
#define GLB_REG2_GPIO_4_I                                       (1<<4U)
#define GLB_REG2_GPIO_5_I                                       (1<<5U)
#define GLB_REG2_GPIO_6_I                                       (1<<6U)
#define GLB_REG2_GPIO_7_I                                       (1<<7U)
#define GLB_REG2_GPIO_8_I                                       (1<<8U)
#define GLB_REG2_GPIO_9_I                                       (1<<9U)
#define GLB_REG2_GPIO_10_I                                      (1<<10U)
#define GLB_REG2_GPIO_11_I                                      (1<<11U)
#define GLB_REG2_GPIO_12_I                                      (1<<12U)
#define GLB_REG2_GPIO_13_I                                      (1<<13U)
#define GLB_REG2_GPIO_14_I                                      (1<<14U)
#define GLB_REG2_GPIO_15_I                                      (1<<15U)
#define GLB_REG2_GPIO_16_I                                      (1<<16U)
#define GLB_REG2_GPIO_17_I                                      (1<<17U)
#define GLB_REG2_GPIO_18_I                                      (1<<18U)
#define GLB_REG2_GPIO_19_I                                      (1<<19U)
#define GLB_REG2_GPIO_20_I                                      (1<<20U)
#define GLB_REG2_GPIO_21_I                                      (1<<21U)
#define GLB_REG2_GPIO_22_I                                      (1<<22U)
#define GLB_REG2_GPIO_23_I                                      (1<<23U)
#define GLB_REG2_GPIO_24_I                                      (1<<24U)
#define GLB_REG2_GPIO_25_I                                      (1<<25U)
#define GLB_REG2_GPIO_26_I                                      (1<<26U)
#define GLB_REG2_GPIO_27_I                                      (1<<27U)
#define GLB_REG2_GPIO_28_I                                      (1<<28U)
#define GLB_REG2_GPIO_29_I                                      (1<<29U)
#define GLB_REG2_GPIO_30_I                                      (1<<30U)
#define GLB_REG2_GPIO_31_I                                      (1<<31U)

/* 0xAC8 : gpio_cfg129 */
#define GLB_REG2_GPIO_32_I                                      (1<<0U)
#define GLB_REG2_GPIO_33_I                                      (1<<1U)
#define GLB_REG2_GPIO_34_I                                      (1<<2U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG2_GPIO_35_I                                      (1<<3U)
#define GLB_REG2_GPIO_36_I                                      (1<<4U)
#define GLB_REG2_GPIO_37_I                                      (1<<5U)
#define GLB_REG2_GPIO_38_I                                      (1<<6U)
#define GLB_REG2_GPIO_39_I                                      (1<<7U)
#define GLB_REG2_GPIO_40_I                                      (1<<8U)
#define GLB_REG2_GPIO_41_I                                      (1<<9U)
#define GLB_REG2_GPIO_42_I                                      (1<<10U)
#define GLB_REG2_GPIO_43_I                                      (1<<11U)
#define GLB_REG2_GPIO_44_I                                      (1<<12U)
#define GLB_REG2_GPIO_45_I                                      (1<<13U)
#endif

/* 0xAE4 : gpio_cfg136 */
#define GLB_REG2_GPIO_0_O                                       (1<<0U)
#define GLB_REG2_GPIO_1_O                                       (1<<1U)
#define GLB_REG2_GPIO_2_O                                       (1<<2U)
#define GLB_REG2_GPIO_3_O                                       (1<<3U)
#define GLB_REG2_GPIO_4_O                                       (1<<4U)
#define GLB_REG2_GPIO_5_O                                       (1<<5U)
#define GLB_REG2_GPIO_6_O                                       (1<<6U)
#define GLB_REG2_GPIO_7_O                                       (1<<7U)
#define GLB_REG2_GPIO_8_O                                       (1<<8U)
#define GLB_REG2_GPIO_9_O                                       (1<<9U)
#define GLB_REG2_GPIO_10_O                                      (1<<10U)
#define GLB_REG2_GPIO_11_O                                      (1<<11U)
#define GLB_REG2_GPIO_12_O                                      (1<<12U)
#define GLB_REG2_GPIO_13_O                                      (1<<13U)
#define GLB_REG2_GPIO_14_O                                      (1<<14U)
#define GLB_REG2_GPIO_15_O                                      (1<<15U)
#define GLB_REG2_GPIO_16_O                                      (1<<16U)
#define GLB_REG2_GPIO_17_O                                      (1<<17U)
#define GLB_REG2_GPIO_18_O                                      (1<<18U)
#define GLB_REG2_GPIO_19_O                                      (1<<19U)
#define GLB_REG2_GPIO_20_O                                      (1<<20U)
#define GLB_REG2_GPIO_21_O                                      (1<<21U)
#define GLB_REG2_GPIO_22_O                                      (1<<22U)
#define GLB_REG2_GPIO_23_O                                      (1<<23U)
#define GLB_REG2_GPIO_24_O                                      (1<<24U)
#define GLB_REG2_GPIO_25_O                                      (1<<25U)
#define GLB_REG2_GPIO_26_O                                      (1<<26U)
#define GLB_REG2_GPIO_27_O                                      (1<<27U)
#define GLB_REG2_GPIO_28_O                                      (1<<28U)
#define GLB_REG2_GPIO_29_O                                      (1<<29U)
#define GLB_REG2_GPIO_30_O                                      (1<<30U)
#define GLB_REG2_GPIO_31_O                                      (1<<31U)

/* 0xAE8 : gpio_cfg137 */
#define GLB_REG2_GPIO_32_O                                      (1<<0U)
#define GLB_REG2_GPIO_33_O                                      (1<<1U)
#define GLB_REG2_GPIO_34_O                                      (1<<2U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG2_GPIO_35_O                                      (1<<3U)
#define GLB_REG2_GPIO_36_O                                      (1<<4U)
#define GLB_REG2_GPIO_37_O                                      (1<<5U)
#define GLB_REG2_GPIO_38_O                                      (1<<6U)
#define GLB_REG2_GPIO_39_O                                      (1<<7U)
#define GLB_REG2_GPIO_40_O                                      (1<<8U)
#define GLB_REG2_GPIO_41_O                                      (1<<9U)
#define GLB_REG2_GPIO_42_O                                      (1<<10U)
#define GLB_REG2_GPIO_43_O                                      (1<<11U)
#define GLB_REG2_GPIO_44_O                                      (1<<12U)
#define GLB_REG2_GPIO_45_O                                      (1<<13U)
#endif

/* 0xAEC : gpio_cfg138 */
#define GLB_REG2_GPIO_0_SET                                     (1<<0U)
#define GLB_REG2_GPIO_1_SET                                     (1<<1U)
#define GLB_REG2_GPIO_2_SET                                     (1<<2U)
#define GLB_REG2_GPIO_3_SET                                     (1<<3U)
#define GLB_REG2_GPIO_4_SET                                     (1<<4U)
#define GLB_REG2_GPIO_5_SET                                     (1<<5U)
#define GLB_REG2_GPIO_6_SET                                     (1<<6U)
#define GLB_REG2_GPIO_7_SET                                     (1<<7U)
#define GLB_REG2_GPIO_8_SET                                     (1<<8U)
#define GLB_REG2_GPIO_9_SET                                     (1<<9U)
#define GLB_REG2_GPIO_10_SET                                    (1<<10U)
#define GLB_REG2_GPIO_11_SET                                    (1<<11U)
#define GLB_REG2_GPIO_12_SET                                    (1<<12U)
#define GLB_REG2_GPIO_13_SET                                    (1<<13U)
#define GLB_REG2_GPIO_14_SET                                    (1<<14U)
#define GLB_REG2_GPIO_15_SET                                    (1<<15U)
#define GLB_REG2_GPIO_16_SET                                    (1<<16U)
#define GLB_REG2_GPIO_17_SET                                    (1<<17U)
#define GLB_REG2_GPIO_18_SET                                    (1<<18U)
#define GLB_REG2_GPIO_19_SET                                    (1<<19U)
#define GLB_REG2_GPIO_20_SET                                    (1<<20U)
#define GLB_REG2_GPIO_21_SET                                    (1<<21U)
#define GLB_REG2_GPIO_22_SET                                    (1<<22U)
#define GLB_REG2_GPIO_23_SET                                    (1<<23U)
#define GLB_REG2_GPIO_24_SET                                    (1<<24U)
#define GLB_REG2_GPIO_25_SET                                    (1<<25U)
#define GLB_REG2_GPIO_26_SET                                    (1<<26U)
#define GLB_REG2_GPIO_27_SET                                    (1<<27U)
#define GLB_REG2_GPIO_28_SET                                    (1<<28U)
#define GLB_REG2_GPIO_29_SET                                    (1<<29U)
#define GLB_REG2_GPIO_30_SET                                    (1<<30U)
#define GLB_REG2_GPIO_31_SET                                    (1<<31U)

/* 0xAF0 : gpio_cfg139 */
#define GLB_REG2_GPIO_32_SET                                    (1<<0U)
#define GLB_REG2_GPIO_33_SET                                    (1<<1U)
#define GLB_REG2_GPIO_34_SET                                    (1<<2U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG2_GPIO_35_SET                                    (1<<3U)
#define GLB_REG2_GPIO_36_SET                                    (1<<4U)
#define GLB_REG2_GPIO_37_SET                                    (1<<5U)
#define GLB_REG2_GPIO_38_SET                                    (1<<6U)
#define GLB_REG2_GPIO_39_SET                                    (1<<7U)
#define GLB_REG2_GPIO_40_SET                                    (1<<8U)
#define GLB_REG2_GPIO_41_SET                                    (1<<9U)
#define GLB_REG2_GPIO_42_SET                                    (1<<10U)
#define GLB_REG2_GPIO_43_SET                                    (1<<11U)
#define GLB_REG2_GPIO_44_SET                                    (1<<12U)
#define GLB_REG2_GPIO_45_SET                                    (1<<13U)
#endif

/* 0xAEC : gpio_cfg140 */
#define GLB_REG2_GPIO_0_CLR                                     (1<<0U)
#define GLB_REG2_GPIO_1_CLR                                     (1<<1U)
#define GLB_REG2_GPIO_2_CLR                                     (1<<2U)
#define GLB_REG2_GPIO_3_CLR                                     (1<<3U)
#define GLB_REG2_GPIO_4_CLR                                     (1<<4U)
#define GLB_REG2_GPIO_5_CLR                                     (1<<5U)
#define GLB_REG2_GPIO_6_CLR                                     (1<<6U)
#define GLB_REG2_GPIO_7_CLR                                     (1<<7U)
#define GLB_REG2_GPIO_8_CLR                                     (1<<8U)
#define GLB_REG2_GPIO_9_CLR                                     (1<<9U)
#define GLB_REG2_GPIO_10_CLR                                    (1<<10U)
#define GLB_REG2_GPIO_11_CLR                                    (1<<11U)
#define GLB_REG2_GPIO_12_CLR                                    (1<<12U)
#define GLB_REG2_GPIO_13_CLR                                    (1<<13U)
#define GLB_REG2_GPIO_14_CLR                                    (1<<14U)
#define GLB_REG2_GPIO_15_CLR                                    (1<<15U)
#define GLB_REG2_GPIO_16_CLR                                    (1<<16U)
#define GLB_REG2_GPIO_17_CLR                                    (1<<17U)
#define GLB_REG2_GPIO_18_CLR                                    (1<<18U)
#define GLB_REG2_GPIO_19_CLR                                    (1<<19U)
#define GLB_REG2_GPIO_20_CLR                                    (1<<20U)
#define GLB_REG2_GPIO_21_CLR                                    (1<<21U)
#define GLB_REG2_GPIO_22_CLR                                    (1<<22U)
#define GLB_REG2_GPIO_23_CLR                                    (1<<23U)
#define GLB_REG2_GPIO_24_CLR                                    (1<<24U)
#define GLB_REG2_GPIO_25_CLR                                    (1<<25U)
#define GLB_REG2_GPIO_26_CLR                                    (1<<26U)
#define GLB_REG2_GPIO_27_CLR                                    (1<<27U)
#define GLB_REG2_GPIO_28_CLR                                    (1<<28U)
#define GLB_REG2_GPIO_29_CLR                                    (1<<29U)
#define GLB_REG2_GPIO_30_CLR                                    (1<<30U)
#define GLB_REG2_GPIO_31_CLR                                    (1<<31U)

/* 0xAF8 : gpio_cfg141 */
#define GLB_REG2_GPIO_32_CLR                                    (1<<0U)
#define GLB_REG2_GPIO_33_CLR                                    (1<<1U)
#define GLB_REG2_GPIO_34_CLR                                    (1<<2U)
#if defined(BL808)||defined(BL606P)
#define GLB_REG2_GPIO_35_CLR                                    (1<<3U)
#define GLB_REG2_GPIO_36_CLR                                    (1<<4U)
#define GLB_REG2_GPIO_37_CLR                                    (1<<5U)
#define GLB_REG2_GPIO_38_CLR                                    (1<<6U)
#define GLB_REG2_GPIO_39_CLR                                    (1<<7U)
#define GLB_REG2_GPIO_40_CLR                                    (1<<8U)
#define GLB_REG2_GPIO_41_CLR                                    (1<<9U)
#define GLB_REG2_GPIO_42_CLR                                    (1<<10U)
#define GLB_REG2_GPIO_43_CLR                                    (1<<11U)
#define GLB_REG2_GPIO_44_CLR                                    (1<<12U)
#define GLB_REG2_GPIO_45_CLR                                    (1<<13U)
#endif

/* 0xAFC : gpio_cfg142 */
#define GLB_CR_GPIO_TX_EN                                       (1<<0U)
#define GLB_CR_INVERT_CODE0_HIGH                                (1<<1U)
#define GLB_CR_INVERT_CODE1_HIGH                                (1<<2U)
#define GLB_CR_CODE_TOTAL_TIME_SHIFT                            (7U)
#define GLB_CR_CODE_TOTAL_TIME_MASK                             (0x1ff<<GLB_CR_CODE_TOTAL_TIME_SHIFT)
#define GLB_CR_CODE0_HIGH_TIME_SHIFT                            (16U)
#define GLB_CR_CODE0_HIGH_TIME_MASK                             (0xff<<GLB_CR_CODE0_HIGH_TIME_SHIFT)
#define GLB_CR_CODE1_HIGH_TIME_SHIFT                            (24U)
#define GLB_CR_CODE1_HIGH_TIME_MASK                             (0xff<<GLB_CR_CODE1_HIGH_TIME_SHIFT)

/* 0xB00 : gpio_cfg143 */
#define GLB_CR_GPIO_DMA_TX_EN                                   (1<<0U)
#define GLB_CR_GPIO_DMA_OUT_SEL_LATCH                           (1<<1U)
#define GLB_GPIO_TX_FIFO_CLR                                    (1<<2U)
#define GLB_GPIO_TX_END_CLR                                     (1<<3U)
#define GLB_GPIO_TX_FIFO_OVERFLOW                               (1<<4U)
#define GLB_GPIO_TX_FIFO_UNDERFLOW                              (1<<5U)
#define GLB_CR_GPIO_DMA_PARK_VALUE                              (1<<7U)
#define GLB_GPIO_TX_FIFO_CNT_SHIFT                              (8U)
#define GLB_GPIO_TX_FIFO_CNT_MASK                               (0xff<<GLB_GPIO_TX_FIFO_CNT_SHIFT)
#define GLB_CR_GPIO_TX_FIFO_TH_SHIFT                            (16U)
#define GLB_CR_GPIO_TX_FIFO_TH_MASK                             (0x7f<<GLB_CR_GPIO_TX_FIFO_TH_SHIFT)
#define GLB_CR_GPIO_TX_END_MASK                                 (1<<23U)
#define GLB_CR_GPIO_TX_FIFO_MASK                                (1<<24U)
#define GLB_CR_GPIO_TX_FER_MASK                                 (1<<25U)
#define GLB_R_GPIO_TX_END_INT                                   (1<<26U)
#define GLB_R_GPIO_TX_FIFO_INT                                  (1<<27U)
#define GLB_R_GPIO_TX_FER_INT                                   (1<<28U)
#define GLB_CR_GPIO_TX_END_EN                                   (1<<29U)
#define GLB_CR_GPIO_TX_FIFO_EN                                  (1<<30U)
#define GLB_CR_GPIO_TX_FER_EN                                   (1<<31U)

/* 0xB04 : gpio_cfg144 */
#define GLB_GPIO_TX_DATA_TO_FIFO_SHIFT                          (0U)
#define GLB_GPIO_TX_DATA_TO_FIFO_MASK                           (0xffff<<GLB_GPIO_TX_DATA_TO_FIFO_SHIFT)

#elif defined(BL702) || defined(BL602) || defined(BL702L)

#define GLB_GPIO_CFGCTL0_OFFSET                                 (0x100)/* GPIO_CFGCTL0 */
#define GLB_GPIO_CFGCTL1_OFFSET                                 (0x104)/* GPIO_CFGCTL1 */
#define GLB_GPIO_CFGCTL2_OFFSET                                 (0x108)/* GPIO_CFGCTL2 */
#define GLB_GPIO_CFGCTL3_OFFSET                                 (0x10C)/* GPIO_CFGCTL3 */
#define GLB_GPIO_CFGCTL4_OFFSET                                 (0x110)/* GPIO_CFGCTL4 */
#define GLB_GPIO_CFGCTL5_OFFSET                                 (0x114)/* GPIO_CFGCTL5 */
#define GLB_GPIO_CFGCTL6_OFFSET                                 (0x118)/* GPIO_CFGCTL6 */
#define GLB_GPIO_CFGCTL7_OFFSET                                 (0x11C)/* GPIO_CFGCTL7 */
#define GLB_GPIO_CFGCTL8_OFFSET                                 (0x120)/* GPIO_CFGCTL8 */
#define GLB_GPIO_CFGCTL9_OFFSET                                 (0x124)/* GPIO_CFGCTL9 */
#define GLB_GPIO_CFGCTL10_OFFSET                                (0x128)/* GPIO_CFGCTL10 */
#define GLB_GPIO_CFGCTL11_OFFSET                                (0x12C)/* GPIO_CFGCTL11 */
#define GLB_GPIO_CFGCTL12_OFFSET                                (0x130)/* GPIO_CFGCTL12 */
#define GLB_GPIO_CFGCTL13_OFFSET                                (0x134)/* GPIO_CFGCTL13 */
#define GLB_GPIO_CFGCTL14_OFFSET                                (0x138)/* GPIO_CFGCTL14 */
#define GLB_GPIO_CFGCTL15_OFFSET                                (0x13C)/* GPIO_CFGCTL15 */
#define GLB_GPIO_CFGCTL16_OFFSET                                (0x140)/* GPIO_CFGCTL16 */
#define GLB_GPIO_CFGCTL17_OFFSET                                (0x144)/* GPIO_CFGCTL17 */
#define GLB_GPIO_CFGCTL18_OFFSET                                (0x148)/* GPIO_CFGCTL18 */
#define GLB_GPIO_CFGCTL30_OFFSET                                (0x180)/* GPIO_CFGCTL30 */
#define GLB_GPIO_CFGCTL31_OFFSET                                (0x184)/* GPIO_CFGCTL31 */
#define GLB_GPIO_CFGCTL32_OFFSET                                (0x188)/* GPIO_CFGCTL32 */
#define GLB_GPIO_CFGCTL33_OFFSET                                (0x18C)/* GPIO_CFGCTL33 */
#define GLB_GPIO_CFGCTL34_OFFSET                                (0x190)/* GPIO_CFGCTL34 */
#define GLB_GPIO_CFGCTL35_OFFSET                                (0x194)/* GPIO_CFGCTL35 */
#define GLB_GPIO_CFGCTL36_OFFSET                                (0x198)/* GPIO_CFGCTL36 */
#define GLB_GPIO_INT_MASK1_OFFSET                               (0x1A0)/* GPIO_INT_MASK1 */
#define GLB_GPIO_INT_STAT1_OFFSET                               (0x1A8)/* GPIO_INT_STAT1 */
#define GLB_GPIO_INT_CLR1_OFFSET                                (0x1B0)/* GPIO_INT_CLR1 */
#define GLB_GPIO_INT_MODE_SET1_OFFSET                           (0x1C0)/* GPIO_INT_MODE_SET1 */
#define GLB_GPIO_INT_MODE_SET2_OFFSET                           (0x1C4)/* GPIO_INT_MODE_SET2 */
#define GLB_GPIO_INT_MODE_SET3_OFFSET                           (0x1C8)/* GPIO_INT_MODE_SET3 */
#define GLB_GPIO_INT_MODE_SET4_OFFSET                           (0x1CC)/* GPIO_INT_MODE_SET4 */
#define GLB_GPIO_INT2_MASK1_OFFSET                              (0x1D0)/* GPIO_INT2_MASK1 */
#define GLB_GPIO_INT2_STAT1_OFFSET                              (0x1D4)/* GPIO_INT2_STAT1 */
#define GLB_GPIO_INT2_CLR1_OFFSET                               (0x1D8)/* GPIO_INT2_CLR1 */
#define GLB_GPIO_INT2_MODE_SET1_OFFSET                          (0x1DC)/* GPIO_INT2_MODE_SET1 */
#define GLB_GPIO_INT2_MODE_SET2_OFFSET                          (0x1E0)/* GPIO_INT2_MODE_SET2 */
#define GLB_GPIO_INT2_MODE_SET3_OFFSET                          (0x1E4)/* GPIO_INT2_MODE_SET3 */
#define GLB_GPIO_INT2_MODE_SET4_OFFSET                          (0x1E8)/* GPIO_INT2_MODE_SET4 */

/* 0x100 : GPIO_CFGCTL0 */
#define GLB_REG_GPIO_0_IE                                       (1<<0U)
#define GLB_REG_GPIO_0_SMT                                      (1<<1U)
#define GLB_REG_GPIO_0_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_0_DRV_MASK                                 (0x3<<GLB_REG_GPIO_0_DRV_SHIFT)
#define GLB_REG_GPIO_0_PU                                       (1<<4U)
#define GLB_REG_GPIO_0_PD                                       (1<<5U)
#define GLB_REG_GPIO_0_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_0_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_0_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_1_IE                                       (1<<16U)
#define GLB_REG_GPIO_1_SMT                                      (1<<17U)
#define GLB_REG_GPIO_1_DRV_SHIFT                                (18U)
#define GLB_REG_GPIO_1_DRV_MASK                                 (0x3<<GLB_REG_GPIO_1_DRV_SHIFT)
#define GLB_REG_GPIO_1_PU                                       (1<<20U)
#define GLB_REG_GPIO_1_PD                                       (1<<21U)
#define GLB_REG_GPIO_1_FUNC_SEL_SHIFT                           (24U)
#define GLB_REG_GPIO_1_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_1_FUNC_SEL_SHIFT)

/* 0x104 : GPIO_CFGCTL1 */
#define GLB_REG_GPIO_2_IE                                       (1<<0U)
#define GLB_REG_GPIO_2_SMT                                      (1<<1U)
#define GLB_REG_GPIO_2_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_2_DRV_MASK                                 (0x3<<GLB_REG_GPIO_2_DRV_SHIFT)
#define GLB_REG_GPIO_2_PU                                       (1<<4U)
#define GLB_REG_GPIO_2_PD                                       (1<<5U)
#define GLB_REG_GPIO_2_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_2_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_2_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_3_IE                                       (1<<16U)
#define GLB_REG_GPIO_3_SMT                                      (1<<17U)
#define GLB_REG_GPIO_3_DRV_SHIFT                                (18U)
#define GLB_REG_GPIO_3_DRV_MASK                                 (0x3<<GLB_REG_GPIO_3_DRV_SHIFT)
#define GLB_REG_GPIO_3_PU                                       (1<<20U)
#define GLB_REG_GPIO_3_PD                                       (1<<21U)
#define GLB_REG_GPIO_3_FUNC_SEL_SHIFT                           (24U)
#define GLB_REG_GPIO_3_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_3_FUNC_SEL_SHIFT)

/* 0x108 : GPIO_CFGCTL2 */
#define GLB_REG_GPIO_4_IE                                       (1<<0U)
#define GLB_REG_GPIO_4_SMT                                      (1<<1U)
#define GLB_REG_GPIO_4_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_4_DRV_MASK                                 (0x3<<GLB_REG_GPIO_4_DRV_SHIFT)
#define GLB_REG_GPIO_4_PU                                       (1<<4U)
#define GLB_REG_GPIO_4_PD                                       (1<<5U)
#define GLB_REG_GPIO_4_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_4_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_4_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_5_IE                                       (1<<16U)
#define GLB_REG_GPIO_5_SMT                                      (1<<17U)
#define GLB_REG_GPIO_5_DRV_SHIFT                                (18U)
#define GLB_REG_GPIO_5_DRV_MASK                                 (0x3<<GLB_REG_GPIO_5_DRV_SHIFT)
#define GLB_REG_GPIO_5_PU                                       (1<<20U)
#define GLB_REG_GPIO_5_PD                                       (1<<21U)
#define GLB_REG_GPIO_5_FUNC_SEL_SHIFT                           (24U)
#define GLB_REG_GPIO_5_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_5_FUNC_SEL_SHIFT)

/* 0x10C : GPIO_CFGCTL3 */
#define GLB_REG_GPIO_6_IE                                       (1<<0U)
#define GLB_REG_GPIO_6_SMT                                      (1<<1U)
#define GLB_REG_GPIO_6_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_6_DRV_MASK                                 (0x3<<GLB_REG_GPIO_6_DRV_SHIFT)
#define GLB_REG_GPIO_6_PU                                       (1<<4U)
#define GLB_REG_GPIO_6_PD                                       (1<<5U)
#define GLB_REG_GPIO_6_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_6_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_6_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_7_IE                                       (1<<16U)
#define GLB_REG_GPIO_7_SMT                                      (1<<17U)
#define GLB_REG_GPIO_7_DRV_SHIFT                                (18U)
#define GLB_REG_GPIO_7_DRV_MASK                                 (0x3<<GLB_REG_GPIO_7_DRV_SHIFT)
#define GLB_REG_GPIO_7_PU                                       (1<<20U)
#define GLB_REG_GPIO_7_PD                                       (1<<21U)
#define GLB_REG_GPIO_7_FUNC_SEL_SHIFT                           (24U)
#define GLB_REG_GPIO_7_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_7_FUNC_SEL_SHIFT)

/* 0x110 : GPIO_CFGCTL4 */
#define GLB_REG_GPIO_8_IE                                       (1<<0U)
#define GLB_REG_GPIO_8_SMT                                      (1<<1U)
#define GLB_REG_GPIO_8_DRV_SHIFT                                (2U)
#define GLB_REG_GPIO_8_DRV_MASK                                 (0x3<<GLB_REG_GPIO_8_DRV_SHIFT)
#define GLB_REG_GPIO_8_PU                                       (1<<4U)
#define GLB_REG_GPIO_8_PD                                       (1<<5U)
#define GLB_REG_GPIO_8_FUNC_SEL_SHIFT                           (8U)
#define GLB_REG_GPIO_8_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_8_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_9_IE                                       (1<<16U)
#define GLB_REG_GPIO_9_SMT                                      (1<<17U)
#define GLB_REG_GPIO_9_DRV_SHIFT                                (18U)
#define GLB_REG_GPIO_9_DRV_MASK                                 (0x3<<GLB_REG_GPIO_9_DRV_SHIFT)
#define GLB_REG_GPIO_9_PU                                       (1<<20U)
#define GLB_REG_GPIO_9_PD                                       (1<<21U)
#define GLB_REG_GPIO_9_FUNC_SEL_SHIFT                           (24U)
#define GLB_REG_GPIO_9_FUNC_SEL_MASK                            (0x1f<<GLB_REG_GPIO_9_FUNC_SEL_SHIFT)

/* 0x114 : GPIO_CFGCTL5 */
#define GLB_REG_GPIO_10_IE                                      (1<<0U)
#define GLB_REG_GPIO_10_SMT                                     (1<<1U)
#define GLB_REG_GPIO_10_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_10_DRV_MASK                                (0x3<<GLB_REG_GPIO_10_DRV_SHIFT)
#define GLB_REG_GPIO_10_PU                                      (1<<4U)
#define GLB_REG_GPIO_10_PD                                      (1<<5U)
#define GLB_REG_GPIO_10_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_10_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_10_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_11_IE                                      (1<<16U)
#define GLB_REG_GPIO_11_SMT                                     (1<<17U)
#define GLB_REG_GPIO_11_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_11_DRV_MASK                                (0x3<<GLB_REG_GPIO_11_DRV_SHIFT)
#define GLB_REG_GPIO_11_PU                                      (1<<20U)
#define GLB_REG_GPIO_11_PD                                      (1<<21U)
#define GLB_REG_GPIO_11_FUNC_SEL_SHIFT                          (24U)
#define GLB_REG_GPIO_11_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_11_FUNC_SEL_SHIFT)

/* 0x118 : GPIO_CFGCTL6 */
#define GLB_REG_GPIO_12_IE                                      (1<<0U)
#define GLB_REG_GPIO_12_SMT                                     (1<<1U)
#define GLB_REG_GPIO_12_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_12_DRV_MASK                                (0x3<<GLB_REG_GPIO_12_DRV_SHIFT)
#define GLB_REG_GPIO_12_PU                                      (1<<4U)
#define GLB_REG_GPIO_12_PD                                      (1<<5U)
#define GLB_REG_GPIO_12_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_12_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_12_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_13_IE                                      (1<<16U)
#define GLB_REG_GPIO_13_SMT                                     (1<<17U)
#define GLB_REG_GPIO_13_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_13_DRV_MASK                                (0x3<<GLB_REG_GPIO_13_DRV_SHIFT)
#define GLB_REG_GPIO_13_PU                                      (1<<20U)
#define GLB_REG_GPIO_13_PD                                      (1<<21U)
#define GLB_REG_GPIO_13_FUNC_SEL_SHIFT                          (24U)
#define GLB_REG_GPIO_13_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_13_FUNC_SEL_SHIFT)

/* 0x11C : GPIO_CFGCTL7 */
#define GLB_REG_GPIO_14_IE                                      (1<<0U)
#define GLB_REG_GPIO_14_SMT                                     (1<<1U)
#define GLB_REG_GPIO_14_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_14_DRV_MASK                                (0x3<<GLB_REG_GPIO_14_DRV_SHIFT)
#define GLB_REG_GPIO_14_PU                                      (1<<4U)
#define GLB_REG_GPIO_14_PD                                      (1<<5U)
#define GLB_REG_GPIO_14_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_14_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_14_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_15_IE                                      (1<<16U)
#define GLB_REG_GPIO_15_SMT                                     (1<<17U)
#define GLB_REG_GPIO_15_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_15_DRV_MASK                                (0x3<<GLB_REG_GPIO_15_DRV_SHIFT)
#define GLB_REG_GPIO_15_PU                                      (1<<20U)
#define GLB_REG_GPIO_15_PD                                      (1<<21U)
#define GLB_REG_GPIO_15_FUNC_SEL_SHIFT                          (24U)
#define GLB_REG_GPIO_15_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_15_FUNC_SEL_SHIFT)

/* 0x120 : GPIO_CFGCTL8 */
#define GLB_REG_GPIO_16_IE                                      (1<<0U)
#define GLB_REG_GPIO_16_SMT                                     (1<<1U)
#define GLB_REG_GPIO_16_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_16_DRV_MASK                                (0x3<<GLB_REG_GPIO_16_DRV_SHIFT)
#define GLB_REG_GPIO_16_PU                                      (1<<4U)
#define GLB_REG_GPIO_16_PD                                      (1<<5U)
#define GLB_REG_GPIO_16_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_16_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_16_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_17_IE                                      (1<<16U)
#define GLB_REG_GPIO_17_SMT                                     (1<<17U)
#define GLB_REG_GPIO_17_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_17_DRV_MASK                                (0x3<<GLB_REG_GPIO_17_DRV_SHIFT)
#define GLB_REG_GPIO_17_PU                                      (1<<20U)
#define GLB_REG_GPIO_17_PD                                      (1<<21U)
#define GLB_REG_GPIO_17_FUNC_SEL_SHIFT                          (24U)
#define GLB_REG_GPIO_17_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_17_FUNC_SEL_SHIFT)

/* 0x124 : GPIO_CFGCTL9 */
#define GLB_REG_GPIO_18_IE                                      (1<<0U)
#define GLB_REG_GPIO_18_SMT                                     (1<<1U)
#define GLB_REG_GPIO_18_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_18_DRV_MASK                                (0x3<<GLB_REG_GPIO_18_DRV_SHIFT)
#define GLB_REG_GPIO_18_PU                                      (1<<4U)
#define GLB_REG_GPIO_18_PD                                      (1<<5U)
#define GLB_REG_GPIO_18_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_18_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_18_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_19_IE                                      (1<<16U)
#define GLB_REG_GPIO_19_SMT                                     (1<<17U)
#define GLB_REG_GPIO_19_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_19_DRV_MASK                                (0x3<<GLB_REG_GPIO_19_DRV_SHIFT)
#define GLB_REG_GPIO_19_PU                                      (1<<20U)
#define GLB_REG_GPIO_19_PD                                      (1<<21U)
#define GLB_REG_GPIO_19_FUNC_SEL_SHIFT                          (24U)
#define GLB_REG_GPIO_19_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_19_FUNC_SEL_SHIFT)

/* 0x128 : GPIO_CFGCTL10 */
#define GLB_REG_GPIO_20_IE                                      (1<<0U)
#define GLB_REG_GPIO_20_SMT                                     (1<<1U)
#define GLB_REG_GPIO_20_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_20_DRV_MASK                                (0x3<<GLB_REG_GPIO_20_DRV_SHIFT)
#define GLB_REG_GPIO_20_PU                                      (1<<4U)
#define GLB_REG_GPIO_20_PD                                      (1<<5U)
#define GLB_REG_GPIO_20_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_20_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_20_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_21_IE                                      (1<<16U)
#define GLB_REG_GPIO_21_SMT                                     (1<<17U)
#define GLB_REG_GPIO_21_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_21_DRV_MASK                                (0x3<<GLB_REG_GPIO_21_DRV_SHIFT)
#define GLB_REG_GPIO_21_PU                                      (1<<20U)
#define GLB_REG_GPIO_21_PD                                      (1<<21U)
#define GLB_REG_GPIO_21_FUNC_SEL_SHIFT                          (24U)
#define GLB_REG_GPIO_21_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_21_FUNC_SEL_SHIFT)

/* 0x12C : GPIO_CFGCTL11 */
#define GLB_REG_GPIO_22_IE                                      (1<<0U)
#define GLB_REG_GPIO_22_SMT                                     (1<<1U)
#define GLB_REG_GPIO_22_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_22_DRV_MASK                                (0x3<<GLB_REG_GPIO_22_DRV_SHIFT)
#define GLB_REG_GPIO_22_PU                                      (1<<4U)
#define GLB_REG_GPIO_22_PD                                      (1<<5U)
#define GLB_REG_GPIO_22_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_22_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_22_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_23_IE                                      (1<<16U)
#define GLB_REG_GPIO_23_SMT                                     (1<<17U)
#define GLB_REG_GPIO_23_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_23_DRV_MASK                                (0x3<<GLB_REG_GPIO_23_DRV_SHIFT)
#define GLB_REG_GPIO_23_PU                                      (1<<20U)
#define GLB_REG_GPIO_23_PD                                      (1<<21U)
#define GLB_REG_GPIO_23_FUNC_SEL_SHIFT                          (24U)
#define GLB_REG_GPIO_23_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_23_FUNC_SEL_SHIFT)

/* 0x130 : GPIO_CFGCTL12 */
#define GLB_REG_GPIO_24_IE                                      (1<<0U)
#define GLB_REG_GPIO_24_SMT                                     (1<<1U)
#define GLB_REG_GPIO_24_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_24_DRV_MASK                                (0x3<<GLB_REG_GPIO_24_DRV_SHIFT)
#define GLB_REG_GPIO_24_PU                                      (1<<4U)
#define GLB_REG_GPIO_24_PD                                      (1<<5U)
#define GLB_REG_GPIO_24_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_24_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_24_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_25_IE                                      (1<<16U)
#define GLB_REG_GPIO_25_SMT                                     (1<<17U)
#define GLB_REG_GPIO_25_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_25_DRV_MASK                                (0x3<<GLB_REG_GPIO_25_DRV_SHIFT)
#define GLB_REG_GPIO_25_PU                                      (1<<20U)
#define GLB_REG_GPIO_25_PD                                      (1<<21U)
#define GLB_REG_GPIO_25_FUNC_SEL_SHIFT                          (24U)
#define GLB_REG_GPIO_25_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_25_FUNC_SEL_SHIFT)

/* 0x134 : GPIO_CFGCTL13 */
#define GLB_REG_GPIO_26_IE                                      (1<<0U)
#define GLB_REG_GPIO_26_SMT                                     (1<<1U)
#define GLB_REG_GPIO_26_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_26_DRV_MASK                                (0x3<<GLB_REG_GPIO_26_DRV_SHIFT)
#define GLB_REG_GPIO_26_PU                                      (1<<4U)
#define GLB_REG_GPIO_26_PD                                      (1<<5U)
#define GLB_REG_GPIO_26_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_26_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_26_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_27_IE                                      (1<<16U)
#define GLB_REG_GPIO_27_SMT                                     (1<<17U)
#define GLB_REG_GPIO_27_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_27_DRV_MASK                                (0x3<<GLB_REG_GPIO_27_DRV_SHIFT)
#define GLB_REG_GPIO_27_PU                                      (1<<20U)
#define GLB_REG_GPIO_27_PD                                      (1<<21U)
#define GLB_REG_GPIO_27_FUNC_SEL_SHIFT                          (24U)
#define GLB_REG_GPIO_27_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_27_FUNC_SEL_SHIFT)

/* 0x138 : GPIO_CFGCTL14 */
#define GLB_REG_GPIO_28_IE                                      (1<<0U)
#define GLB_REG_GPIO_28_SMT                                     (1<<1U)
#define GLB_REG_GPIO_28_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_28_DRV_MASK                                (0x3<<GLB_REG_GPIO_28_DRV_SHIFT)
#define GLB_REG_GPIO_28_PU                                      (1<<4U)
#define GLB_REG_GPIO_28_PD                                      (1<<5U)
#define GLB_REG_GPIO_28_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_28_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_28_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_29_IE                                      (1<<16U)
#define GLB_REG_GPIO_29_SMT                                     (1<<17U)
#define GLB_REG_GPIO_29_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_29_DRV_MASK                                (0x3<<GLB_REG_GPIO_29_DRV_SHIFT)
#define GLB_REG_GPIO_29_PU                                      (1<<20U)
#define GLB_REG_GPIO_29_PD                                      (1<<21U)
#define GLB_REG_GPIO_29_FUNC_SEL_SHIFT                          (24U)
#define GLB_REG_GPIO_29_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_29_FUNC_SEL_SHIFT)

/* 0x13C : GPIO_CFGCTL15 */
#define GLB_REG_GPIO_30_IE                                      (1<<0U)
#define GLB_REG_GPIO_30_SMT                                     (1<<1U)
#define GLB_REG_GPIO_30_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_30_DRV_MASK                                (0x3<<GLB_REG_GPIO_30_DRV_SHIFT)
#define GLB_REG_GPIO_30_PU                                      (1<<4U)
#define GLB_REG_GPIO_30_PD                                      (1<<5U)
#define GLB_REG_GPIO_30_FUNC_SEL_SHIFT                          (8U)
#define GLB_REG_GPIO_30_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_30_FUNC_SEL_SHIFT)
#define GLB_REG_GPIO_31_IE                                      (1<<16U)
#define GLB_REG_GPIO_31_SMT                                     (1<<17U)
#define GLB_REG_GPIO_31_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_31_DRV_MASK                                (0x3<<GLB_REG_GPIO_31_DRV_SHIFT)
#define GLB_REG_GPIO_31_PU                                      (1<<20U)
#define GLB_REG_GPIO_31_PD                                      (1<<21U)
#define GLB_REG_GPIO_31_FUNC_SEL_SHIFT                          (24U)
#define GLB_REG_GPIO_31_FUNC_SEL_MASK                           (0x1f<<GLB_REG_GPIO_31_FUNC_SEL_SHIFT)

/* 0x140 : GPIO_CFGCTL16 */
#define GLB_REG_GPIO_32_IE                                      (1<<0U)
#define GLB_REG_GPIO_32_SMT                                     (1<<1U)
#define GLB_REG_GPIO_32_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_32_DRV_MASK                                (0x3<<GLB_REG_GPIO_32_DRV_SHIFT)
#define GLB_REG_GPIO_32_PU                                      (1<<4U)
#define GLB_REG_GPIO_32_PD                                      (1<<5U)
#define GLB_REG_GPIO_33_IE                                      (1<<16U)
#define GLB_REG_GPIO_33_SMT                                     (1<<17U)
#define GLB_REG_GPIO_33_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_33_DRV_MASK                                (0x3<<GLB_REG_GPIO_33_DRV_SHIFT)
#define GLB_REG_GPIO_33_PU                                      (1<<20U)
#define GLB_REG_GPIO_33_PD                                      (1<<21U)

/* 0x144 : GPIO_CFGCTL17 */
#define GLB_REG_GPIO_34_IE                                      (1<<0U)
#define GLB_REG_GPIO_34_SMT                                     (1<<1U)
#define GLB_REG_GPIO_34_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_34_DRV_MASK                                (0x3<<GLB_REG_GPIO_34_DRV_SHIFT)
#define GLB_REG_GPIO_34_PU                                      (1<<4U)
#define GLB_REG_GPIO_34_PD                                      (1<<5U)
#define GLB_REG_GPIO_35_IE                                      (1<<16U)
#define GLB_REG_GPIO_35_SMT                                     (1<<17U)
#define GLB_REG_GPIO_35_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_35_DRV_MASK                                (0x3<<GLB_REG_GPIO_35_DRV_SHIFT)
#define GLB_REG_GPIO_35_PU                                      (1<<20U)
#define GLB_REG_GPIO_35_PD                                      (1<<21U)

/* 0x148 : GPIO_CFGCTL18 */
#define GLB_REG_GPIO_36_IE                                      (1<<0U)
#define GLB_REG_GPIO_36_SMT                                     (1<<1U)
#define GLB_REG_GPIO_36_DRV_SHIFT                               (2U)
#define GLB_REG_GPIO_36_DRV_MASK                                (0x3<<GLB_REG_GPIO_36_DRV_SHIFT)
#define GLB_REG_GPIO_36_PU                                      (1<<4U)
#define GLB_REG_GPIO_36_PD                                      (1<<5U)
#define GLB_REG_GPIO_37_IE                                      (1<<16U)
#define GLB_REG_GPIO_37_SMT                                     (1<<17U)
#define GLB_REG_GPIO_37_DRV_SHIFT                               (18U)
#define GLB_REG_GPIO_37_DRV_MASK                                (0x3<<GLB_REG_GPIO_37_DRV_SHIFT)
#define GLB_REG_GPIO_37_PU                                      (1<<20U)
#define GLB_REG_GPIO_37_PD                                      (1<<21U)

/* 0x180 : GPIO_CFGCTL30 */
#define GLB_REG_GPIO_0_I                                        (1<<0U)
#define GLB_REG_GPIO_1_I                                        (1<<1U)
#define GLB_REG_GPIO_2_I                                        (1<<2U)
#define GLB_REG_GPIO_3_I                                        (1<<3U)
#define GLB_REG_GPIO_4_I                                        (1<<4U)
#define GLB_REG_GPIO_5_I                                        (1<<5U)
#define GLB_REG_GPIO_6_I                                        (1<<6U)
#define GLB_REG_GPIO_7_I                                        (1<<7U)
#define GLB_REG_GPIO_8_I                                        (1<<8U)
#define GLB_REG_GPIO_9_I                                        (1<<9U)
#define GLB_REG_GPIO_10_I                                       (1<<10U)
#define GLB_REG_GPIO_11_I                                       (1<<11U)
#define GLB_REG_GPIO_12_I                                       (1<<12U)
#define GLB_REG_GPIO_13_I                                       (1<<13U)
#define GLB_REG_GPIO_14_I                                       (1<<14U)
#define GLB_REG_GPIO_15_I                                       (1<<15U)
#define GLB_REG_GPIO_16_I                                       (1<<16U)
#define GLB_REG_GPIO_17_I                                       (1<<17U)
#define GLB_REG_GPIO_18_I                                       (1<<18U)
#define GLB_REG_GPIO_19_I                                       (1<<19U)
#define GLB_REG_GPIO_20_I                                       (1<<20U)
#define GLB_REG_GPIO_21_I                                       (1<<21U)
#define GLB_REG_GPIO_22_I                                       (1<<22U)
#define GLB_REG_GPIO_23_I                                       (1<<23U)
#define GLB_REG_GPIO_24_I                                       (1<<24U)
#define GLB_REG_GPIO_25_I                                       (1<<25U)
#define GLB_REG_GPIO_26_I                                       (1<<26U)
#define GLB_REG_GPIO_27_I                                       (1<<27U)
#define GLB_REG_GPIO_28_I                                       (1<<28U)
#define GLB_REG_GPIO_29_I                                       (1<<29U)
#define GLB_REG_GPIO_30_I                                       (1<<30U)
#define GLB_REG_GPIO_31_I                                       (1<<31U)

/* 0x184 : GPIO_CFGCTL31 */

/* 0x188 : GPIO_CFGCTL32 */
#define GLB_REG_GPIO_0_O                                        (1<<0U)
#define GLB_REG_GPIO_1_O                                        (1<<1U)
#define GLB_REG_GPIO_2_O                                        (1<<2U)
#define GLB_REG_GPIO_3_O                                        (1<<3U)
#define GLB_REG_GPIO_4_O                                        (1<<4U)
#define GLB_REG_GPIO_5_O                                        (1<<5U)
#define GLB_REG_GPIO_6_O                                        (1<<6U)
#define GLB_REG_GPIO_7_O                                        (1<<7U)
#define GLB_REG_GPIO_8_O                                        (1<<8U)
#define GLB_REG_GPIO_9_O                                        (1<<9U)
#define GLB_REG_GPIO_10_O                                       (1<<10U)
#define GLB_REG_GPIO_11_O                                       (1<<11U)
#define GLB_REG_GPIO_12_O                                       (1<<12U)
#define GLB_REG_GPIO_13_O                                       (1<<13U)
#define GLB_REG_GPIO_14_O                                       (1<<14U)
#define GLB_REG_GPIO_15_O                                       (1<<15U)
#define GLB_REG_GPIO_16_O                                       (1<<16U)
#define GLB_REG_GPIO_17_O                                       (1<<17U)
#define GLB_REG_GPIO_18_O                                       (1<<18U)
#define GLB_REG_GPIO_19_O                                       (1<<19U)
#define GLB_REG_GPIO_20_O                                       (1<<20U)
#define GLB_REG_GPIO_21_O                                       (1<<21U)
#define GLB_REG_GPIO_22_O                                       (1<<22U)
#define GLB_REG_GPIO_23_O                                       (1<<23U)
#define GLB_REG_GPIO_24_O                                       (1<<24U)
#define GLB_REG_GPIO_25_O                                       (1<<25U)
#define GLB_REG_GPIO_26_O                                       (1<<26U)
#define GLB_REG_GPIO_27_O                                       (1<<27U)
#define GLB_REG_GPIO_28_O                                       (1<<28U)
#define GLB_REG_GPIO_29_O                                       (1<<29U)
#define GLB_REG_GPIO_30_O                                       (1<<30U)
#define GLB_REG_GPIO_31_O                                       (1<<31U)

/* 0x18C : GPIO_CFGCTL33 */

/* 0x190 : GPIO_CFGCTL34 */
#define GLB_REG_GPIO_0_OE                                       (1<<0U)
#define GLB_REG_GPIO_1_OE                                       (1<<1U)
#define GLB_REG_GPIO_2_OE                                       (1<<2U)
#define GLB_REG_GPIO_3_OE                                       (1<<3U)
#define GLB_REG_GPIO_4_OE                                       (1<<4U)
#define GLB_REG_GPIO_5_OE                                       (1<<5U)
#define GLB_REG_GPIO_6_OE                                       (1<<6U)
#define GLB_REG_GPIO_7_OE                                       (1<<7U)
#define GLB_REG_GPIO_8_OE                                       (1<<8U)
#define GLB_REG_GPIO_9_OE                                       (1<<9U)
#define GLB_REG_GPIO_10_OE                                      (1<<10U)
#define GLB_REG_GPIO_11_OE                                      (1<<11U)
#define GLB_REG_GPIO_12_OE                                      (1<<12U)
#define GLB_REG_GPIO_13_OE                                      (1<<13U)
#define GLB_REG_GPIO_14_OE                                      (1<<14U)
#define GLB_REG_GPIO_15_OE                                      (1<<15U)
#define GLB_REG_GPIO_16_OE                                      (1<<16U)
#define GLB_REG_GPIO_17_OE                                      (1<<17U)
#define GLB_REG_GPIO_18_OE                                      (1<<18U)
#define GLB_REG_GPIO_19_OE                                      (1<<19U)
#define GLB_REG_GPIO_20_OE                                      (1<<20U)
#define GLB_REG_GPIO_21_OE                                      (1<<21U)
#define GLB_REG_GPIO_22_OE                                      (1<<22U)
#define GLB_REG_GPIO_23_OE                                      (1<<23U)
#define GLB_REG_GPIO_24_OE                                      (1<<24U)
#define GLB_REG_GPIO_25_OE                                      (1<<25U)
#define GLB_REG_GPIO_26_OE                                      (1<<26U)
#define GLB_REG_GPIO_27_OE                                      (1<<27U)
#define GLB_REG_GPIO_28_OE                                      (1<<28U)
#define GLB_REG_GPIO_29_OE                                      (1<<29U)
#define GLB_REG_GPIO_30_OE                                      (1<<30U)
#define GLB_REG_GPIO_31_OE                                      (1<<31U)

/* 0x194 : GPIO_CFGCTL35 */

/* 0x1A0 : GPIO_INT_MASK1 */
#define GLB_REG_GPIO_INT_MASK1_SHIFT                            (0U)
#define GLB_REG_GPIO_INT_MASK1_MASK                             (0xffffffff<<GLB_REG_GPIO_INT_MASK1_SHIFT)

/* 0x1A8 : GPIO_INT_STAT1 */
#define GLB_GPIO_INT_STAT1_SHIFT                                (0U)
#define GLB_GPIO_INT_STAT1_MASK                                 (0xffffffff<<GLB_GPIO_INT_STAT1_SHIFT)

/* 0x1B0 : GPIO_INT_CLR1 */
#define GLB_REG_GPIO_INT_CLR1_SHIFT                             (0U)
#define GLB_REG_GPIO_INT_CLR1_MASK                              (0xffffffff<<GLB_REG_GPIO_INT_CLR1_SHIFT)

/* 0x1C0 : GPIO_INT_MODE_SET1 */
#define GLB_REG_GPIO_INT_MODE_SET1_SHIFT                        (0U)
#define GLB_REG_GPIO_INT_MODE_SET1_MASK                         (0x3fffffff<<GLB_REG_GPIO_INT_MODE_SET1_SHIFT)

/* 0x1C4 : GPIO_INT_MODE_SET2 */
#define GLB_REG_GPIO_INT_MODE_SET2_SHIFT                        (0U)
#define GLB_REG_GPIO_INT_MODE_SET2_MASK                         (0x3fffffff<<GLB_REG_GPIO_INT_MODE_SET2_SHIFT)

/* 0x1C8 : GPIO_INT_MODE_SET3 */
#define GLB_REG_GPIO_INT_MODE_SET3_SHIFT                        (0U)
#define GLB_REG_GPIO_INT_MODE_SET3_MASK                         (0x3fffffff<<GLB_REG_GPIO_INT_MODE_SET3_SHIFT)

/* 0x1CC : GPIO_INT_MODE_SET4 */
#define GLB_REG_GPIO_INT_MODE_SET4_SHIFT                        (0U)
#define GLB_REG_GPIO_INT_MODE_SET4_MASK                         (0x3f<<GLB_REG_GPIO_INT_MODE_SET4_SHIFT)

/* 0x1D0 : GPIO_INT2_MASK1 */
#define GLB_REG_GPIO_INT2_MASK1_SHIFT                           (0U)
#define GLB_REG_GPIO_INT2_MASK1_MASK                            (0xffffffff<<GLB_REG_GPIO_INT2_MASK1_SHIFT)

/* 0x1D4 : GPIO_INT2_STAT1 */
#define GLB_GPIO_INT2_STAT1_SHIFT                               (0U)
#define GLB_GPIO_INT2_STAT1_MASK                                (0xffffffff<<GLB_GPIO_INT2_STAT1_SHIFT)

/* 0x1D8 : GPIO_INT2_CLR1 */
#define GLB_REG_GPIO_INT2_CLR1_SHIFT                            (0U)
#define GLB_REG_GPIO_INT2_CLR1_MASK                             (0xffffffff<<GLB_REG_GPIO_INT2_CLR1_SHIFT)

/* 0x1DC : GPIO_INT2_MODE_SET1 */
#define GLB_REG_GPIO_INT2_MODE_SET1_SHIFT                       (0U)
#define GLB_REG_GPIO_INT2_MODE_SET1_MASK                        (0x3fffffff<<GLB_REG_GPIO_INT2_MODE_SET1_SHIFT)

/* 0x1E0 : GPIO_INT2_MODE_SET2 */
#define GLB_REG_GPIO_INT2_MODE_SET2_SHIFT                       (0U)
#define GLB_REG_GPIO_INT2_MODE_SET2_MASK                        (0x3fffffff<<GLB_REG_GPIO_INT2_MODE_SET2_SHIFT)

/* 0x1E4 : GPIO_INT2_MODE_SET3 */
#define GLB_REG_GPIO_INT2_MODE_SET3_SHIFT                       (0U)
#define GLB_REG_GPIO_INT2_MODE_SET3_MASK                        (0x3fffffff<<GLB_REG_GPIO_INT2_MODE_SET3_SHIFT)

/* 0x1E8 : GPIO_INT2_MODE_SET4 */
#define GLB_REG_GPIO_INT2_MODE_SET4_SHIFT                       (0U)
#define GLB_REG_GPIO_INT2_MODE_SET4_MASK                        (0x3f<<GLB_REG_GPIO_INT2_MODE_SET4_SHIFT)

#endif

#endif




/* __HARDWARE_GPIO_H__ */
