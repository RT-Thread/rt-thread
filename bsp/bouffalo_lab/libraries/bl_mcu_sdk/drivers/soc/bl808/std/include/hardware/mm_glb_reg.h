/**
  ******************************************************************************
  * @file    mm_glb_reg.h
  * @version V1.0
  * @date    2021-07-12
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
#ifndef __MM_GLB_REG_H__
#define __MM_GLB_REG_H__

#include "bl808.h"

/* 0x0 : mm_clk_ctrl_cpu */
#define MM_GLB_MM_CLK_CTRL_CPU_OFFSET        (0x0)
#define MM_GLB_REG_PLL_EN                    MM_GLB_REG_PLL_EN
#define MM_GLB_REG_PLL_EN_POS                (0U)
#define MM_GLB_REG_PLL_EN_LEN                (1U)
#define MM_GLB_REG_PLL_EN_MSK                (((1U << MM_GLB_REG_PLL_EN_LEN) - 1) << MM_GLB_REG_PLL_EN_POS)
#define MM_GLB_REG_PLL_EN_UMSK               (~(((1U << MM_GLB_REG_PLL_EN_LEN) - 1) << MM_GLB_REG_PLL_EN_POS))
#define MM_GLB_REG_CPU_CLK_EN                MM_GLB_REG_CPU_CLK_EN
#define MM_GLB_REG_CPU_CLK_EN_POS            (1U)
#define MM_GLB_REG_CPU_CLK_EN_LEN            (1U)
#define MM_GLB_REG_CPU_CLK_EN_MSK            (((1U << MM_GLB_REG_CPU_CLK_EN_LEN) - 1) << MM_GLB_REG_CPU_CLK_EN_POS)
#define MM_GLB_REG_CPU_CLK_EN_UMSK           (~(((1U << MM_GLB_REG_CPU_CLK_EN_LEN) - 1) << MM_GLB_REG_CPU_CLK_EN_POS))
#define MM_GLB_REG_BCLK_EN                   MM_GLB_REG_BCLK_EN
#define MM_GLB_REG_BCLK_EN_POS               (2U)
#define MM_GLB_REG_BCLK_EN_LEN               (1U)
#define MM_GLB_REG_BCLK_EN_MSK               (((1U << MM_GLB_REG_BCLK_EN_LEN) - 1) << MM_GLB_REG_BCLK_EN_POS)
#define MM_GLB_REG_BCLK_EN_UMSK              (~(((1U << MM_GLB_REG_BCLK_EN_LEN) - 1) << MM_GLB_REG_BCLK_EN_POS))
#define MM_GLB_REG_MM_CPU_CLK_EN             MM_GLB_REG_MM_CPU_CLK_EN
#define MM_GLB_REG_MM_CPU_CLK_EN_POS         (3U)
#define MM_GLB_REG_MM_CPU_CLK_EN_LEN         (1U)
#define MM_GLB_REG_MM_CPU_CLK_EN_MSK         (((1U << MM_GLB_REG_MM_CPU_CLK_EN_LEN) - 1) << MM_GLB_REG_MM_CPU_CLK_EN_POS)
#define MM_GLB_REG_MM_CPU_CLK_EN_UMSK        (~(((1U << MM_GLB_REG_MM_CPU_CLK_EN_LEN) - 1) << MM_GLB_REG_MM_CPU_CLK_EN_POS))
#define MM_GLB_REG_UART_CLK_SEL              MM_GLB_REG_UART_CLK_SEL
#define MM_GLB_REG_UART_CLK_SEL_POS          (4U)
#define MM_GLB_REG_UART_CLK_SEL_LEN          (2U)
#define MM_GLB_REG_UART_CLK_SEL_MSK          (((1U << MM_GLB_REG_UART_CLK_SEL_LEN) - 1) << MM_GLB_REG_UART_CLK_SEL_POS)
#define MM_GLB_REG_UART_CLK_SEL_UMSK         (~(((1U << MM_GLB_REG_UART_CLK_SEL_LEN) - 1) << MM_GLB_REG_UART_CLK_SEL_POS))
#define MM_GLB_REG_I2C_CLK_SEL               MM_GLB_REG_I2C_CLK_SEL
#define MM_GLB_REG_I2C_CLK_SEL_POS           (6U)
#define MM_GLB_REG_I2C_CLK_SEL_LEN           (1U)
#define MM_GLB_REG_I2C_CLK_SEL_MSK           (((1U << MM_GLB_REG_I2C_CLK_SEL_LEN) - 1) << MM_GLB_REG_I2C_CLK_SEL_POS)
#define MM_GLB_REG_I2C_CLK_SEL_UMSK          (~(((1U << MM_GLB_REG_I2C_CLK_SEL_LEN) - 1) << MM_GLB_REG_I2C_CLK_SEL_POS))
#define MM_GLB_REG_SPI_CLK_SEL               MM_GLB_REG_SPI_CLK_SEL
#define MM_GLB_REG_SPI_CLK_SEL_POS           (7U)
#define MM_GLB_REG_SPI_CLK_SEL_LEN           (1U)
#define MM_GLB_REG_SPI_CLK_SEL_MSK           (((1U << MM_GLB_REG_SPI_CLK_SEL_LEN) - 1) << MM_GLB_REG_SPI_CLK_SEL_POS)
#define MM_GLB_REG_SPI_CLK_SEL_UMSK          (~(((1U << MM_GLB_REG_SPI_CLK_SEL_LEN) - 1) << MM_GLB_REG_SPI_CLK_SEL_POS))
#define MM_GLB_REG_CPU_CLK_SEL               MM_GLB_REG_CPU_CLK_SEL
#define MM_GLB_REG_CPU_CLK_SEL_POS           (8U)
#define MM_GLB_REG_CPU_CLK_SEL_LEN           (2U)
#define MM_GLB_REG_CPU_CLK_SEL_MSK           (((1U << MM_GLB_REG_CPU_CLK_SEL_LEN) - 1) << MM_GLB_REG_CPU_CLK_SEL_POS)
#define MM_GLB_REG_CPU_CLK_SEL_UMSK          (~(((1U << MM_GLB_REG_CPU_CLK_SEL_LEN) - 1) << MM_GLB_REG_CPU_CLK_SEL_POS))
#define MM_GLB_REG_XCLK_CLK_SEL              MM_GLB_REG_XCLK_CLK_SEL
#define MM_GLB_REG_XCLK_CLK_SEL_POS          (10U)
#define MM_GLB_REG_XCLK_CLK_SEL_LEN          (1U)
#define MM_GLB_REG_XCLK_CLK_SEL_MSK          (((1U << MM_GLB_REG_XCLK_CLK_SEL_LEN) - 1) << MM_GLB_REG_XCLK_CLK_SEL_POS)
#define MM_GLB_REG_XCLK_CLK_SEL_UMSK         (~(((1U << MM_GLB_REG_XCLK_CLK_SEL_LEN) - 1) << MM_GLB_REG_XCLK_CLK_SEL_POS))
#define MM_GLB_REG_CPU_ROOT_CLK_SEL          MM_GLB_REG_CPU_ROOT_CLK_SEL
#define MM_GLB_REG_CPU_ROOT_CLK_SEL_POS      (11U)
#define MM_GLB_REG_CPU_ROOT_CLK_SEL_LEN      (1U)
#define MM_GLB_REG_CPU_ROOT_CLK_SEL_MSK      (((1U << MM_GLB_REG_CPU_ROOT_CLK_SEL_LEN) - 1) << MM_GLB_REG_CPU_ROOT_CLK_SEL_POS)
#define MM_GLB_REG_CPU_ROOT_CLK_SEL_UMSK     (~(((1U << MM_GLB_REG_CPU_ROOT_CLK_SEL_LEN) - 1) << MM_GLB_REG_CPU_ROOT_CLK_SEL_POS))
#define MM_GLB_REG_MMCPU0_CLK_EN             MM_GLB_REG_MMCPU0_CLK_EN
#define MM_GLB_REG_MMCPU0_CLK_EN_POS         (12U)
#define MM_GLB_REG_MMCPU0_CLK_EN_LEN         (1U)
#define MM_GLB_REG_MMCPU0_CLK_EN_MSK         (((1U << MM_GLB_REG_MMCPU0_CLK_EN_LEN) - 1) << MM_GLB_REG_MMCPU0_CLK_EN_POS)
#define MM_GLB_REG_MMCPU0_CLK_EN_UMSK        (~(((1U << MM_GLB_REG_MMCPU0_CLK_EN_LEN) - 1) << MM_GLB_REG_MMCPU0_CLK_EN_POS))
#define MM_GLB_REG_BCLK1X_SEL                MM_GLB_REG_BCLK1X_SEL
#define MM_GLB_REG_BCLK1X_SEL_POS            (13U)
#define MM_GLB_REG_BCLK1X_SEL_LEN            (2U)
#define MM_GLB_REG_BCLK1X_SEL_MSK            (((1U << MM_GLB_REG_BCLK1X_SEL_LEN) - 1) << MM_GLB_REG_BCLK1X_SEL_POS)
#define MM_GLB_REG_BCLK1X_SEL_UMSK           (~(((1U << MM_GLB_REG_BCLK1X_SEL_LEN) - 1) << MM_GLB_REG_BCLK1X_SEL_POS))
#define MM_GLB_REG_BCLK2X_DIV_ACT_PULSE      MM_GLB_REG_BCLK2X_DIV_ACT_PULSE
#define MM_GLB_REG_BCLK2X_DIV_ACT_PULSE_POS  (18U)
#define MM_GLB_REG_BCLK2X_DIV_ACT_PULSE_LEN  (1U)
#define MM_GLB_REG_BCLK2X_DIV_ACT_PULSE_MSK  (((1U << MM_GLB_REG_BCLK2X_DIV_ACT_PULSE_LEN) - 1) << MM_GLB_REG_BCLK2X_DIV_ACT_PULSE_POS)
#define MM_GLB_REG_BCLK2X_DIV_ACT_PULSE_UMSK (~(((1U << MM_GLB_REG_BCLK2X_DIV_ACT_PULSE_LEN) - 1) << MM_GLB_REG_BCLK2X_DIV_ACT_PULSE_POS))
#define MM_GLB_REG_BCLK2X_DIV_BYPASS         MM_GLB_REG_BCLK2X_DIV_BYPASS
#define MM_GLB_REG_BCLK2X_DIV_BYPASS_POS     (19U)
#define MM_GLB_REG_BCLK2X_DIV_BYPASS_LEN     (1U)
#define MM_GLB_REG_BCLK2X_DIV_BYPASS_MSK     (((1U << MM_GLB_REG_BCLK2X_DIV_BYPASS_LEN) - 1) << MM_GLB_REG_BCLK2X_DIV_BYPASS_POS)
#define MM_GLB_REG_BCLK2X_DIV_BYPASS_UMSK    (~(((1U << MM_GLB_REG_BCLK2X_DIV_BYPASS_LEN) - 1) << MM_GLB_REG_BCLK2X_DIV_BYPASS_POS))
#define MM_GLB_STS_BCLK2X_PROT_DONE          MM_GLB_STS_BCLK2X_PROT_DONE
#define MM_GLB_STS_BCLK2X_PROT_DONE_POS      (20U)
#define MM_GLB_STS_BCLK2X_PROT_DONE_LEN      (1U)
#define MM_GLB_STS_BCLK2X_PROT_DONE_MSK      (((1U << MM_GLB_STS_BCLK2X_PROT_DONE_LEN) - 1) << MM_GLB_STS_BCLK2X_PROT_DONE_POS)
#define MM_GLB_STS_BCLK2X_PROT_DONE_UMSK     (~(((1U << MM_GLB_STS_BCLK2X_PROT_DONE_LEN) - 1) << MM_GLB_STS_BCLK2X_PROT_DONE_POS))
#define MM_GLB_REG_BCLK2X_SW_DONE_CNT        MM_GLB_REG_BCLK2X_SW_DONE_CNT
#define MM_GLB_REG_BCLK2X_SW_DONE_CNT_POS    (24U)
#define MM_GLB_REG_BCLK2X_SW_DONE_CNT_LEN    (4U)
#define MM_GLB_REG_BCLK2X_SW_DONE_CNT_MSK    (((1U << MM_GLB_REG_BCLK2X_SW_DONE_CNT_LEN) - 1) << MM_GLB_REG_BCLK2X_SW_DONE_CNT_POS)
#define MM_GLB_REG_BCLK2X_SW_DONE_CNT_UMSK   (~(((1U << MM_GLB_REG_BCLK2X_SW_DONE_CNT_LEN) - 1) << MM_GLB_REG_BCLK2X_SW_DONE_CNT_POS))
#define MM_GLB_CPU_CLK_SW_STATE              MM_GLB_CPU_CLK_SW_STATE
#define MM_GLB_CPU_CLK_SW_STATE_POS          (28U)
#define MM_GLB_CPU_CLK_SW_STATE_LEN          (3U)
#define MM_GLB_CPU_CLK_SW_STATE_MSK          (((1U << MM_GLB_CPU_CLK_SW_STATE_LEN) - 1) << MM_GLB_CPU_CLK_SW_STATE_POS)
#define MM_GLB_CPU_CLK_SW_STATE_UMSK         (~(((1U << MM_GLB_CPU_CLK_SW_STATE_LEN) - 1) << MM_GLB_CPU_CLK_SW_STATE_POS))

/* 0x4 : mm_clk_cpu */
#define MM_GLB_MM_CLK_CPU_OFFSET       (0x4)
#define MM_GLB_REG_CPU_CLK_DIV         MM_GLB_REG_CPU_CLK_DIV
#define MM_GLB_REG_CPU_CLK_DIV_POS     (0U)
#define MM_GLB_REG_CPU_CLK_DIV_LEN     (8U)
#define MM_GLB_REG_CPU_CLK_DIV_MSK     (((1U << MM_GLB_REG_CPU_CLK_DIV_LEN) - 1) << MM_GLB_REG_CPU_CLK_DIV_POS)
#define MM_GLB_REG_CPU_CLK_DIV_UMSK    (~(((1U << MM_GLB_REG_CPU_CLK_DIV_LEN) - 1) << MM_GLB_REG_CPU_CLK_DIV_POS))
#define MM_GLB_REG_CNN_CLK_DIV_EN      MM_GLB_REG_CNN_CLK_DIV_EN
#define MM_GLB_REG_CNN_CLK_DIV_EN_POS  (8U)
#define MM_GLB_REG_CNN_CLK_DIV_EN_LEN  (1U)
#define MM_GLB_REG_CNN_CLK_DIV_EN_MSK  (((1U << MM_GLB_REG_CNN_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_CNN_CLK_DIV_EN_POS)
#define MM_GLB_REG_CNN_CLK_DIV_EN_UMSK (~(((1U << MM_GLB_REG_CNN_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_CNN_CLK_DIV_EN_POS))
#define MM_GLB_REG_CNN_CLK_SEL         MM_GLB_REG_CNN_CLK_SEL
#define MM_GLB_REG_CNN_CLK_SEL_POS     (9U)
#define MM_GLB_REG_CNN_CLK_SEL_LEN     (2U)
#define MM_GLB_REG_CNN_CLK_SEL_MSK     (((1U << MM_GLB_REG_CNN_CLK_SEL_LEN) - 1) << MM_GLB_REG_CNN_CLK_SEL_POS)
#define MM_GLB_REG_CNN_CLK_SEL_UMSK    (~(((1U << MM_GLB_REG_CNN_CLK_SEL_LEN) - 1) << MM_GLB_REG_CNN_CLK_SEL_POS))
#define MM_GLB_REG_CNN_CLK_DIV         MM_GLB_REG_CNN_CLK_DIV
#define MM_GLB_REG_CNN_CLK_DIV_POS     (12U)
#define MM_GLB_REG_CNN_CLK_DIV_LEN     (3U)
#define MM_GLB_REG_CNN_CLK_DIV_MSK     (((1U << MM_GLB_REG_CNN_CLK_DIV_LEN) - 1) << MM_GLB_REG_CNN_CLK_DIV_POS)
#define MM_GLB_REG_CNN_CLK_DIV_UMSK    (~(((1U << MM_GLB_REG_CNN_CLK_DIV_LEN) - 1) << MM_GLB_REG_CNN_CLK_DIV_POS))
#define MM_GLB_REG_BCLK2X_DIV          MM_GLB_REG_BCLK2X_DIV
#define MM_GLB_REG_BCLK2X_DIV_POS      (16U)
#define MM_GLB_REG_BCLK2X_DIV_LEN      (8U)
#define MM_GLB_REG_BCLK2X_DIV_MSK      (((1U << MM_GLB_REG_BCLK2X_DIV_LEN) - 1) << MM_GLB_REG_BCLK2X_DIV_POS)
#define MM_GLB_REG_BCLK2X_DIV_UMSK     (~(((1U << MM_GLB_REG_BCLK2X_DIV_LEN) - 1) << MM_GLB_REG_BCLK2X_DIV_POS))
#define MM_GLB_REG_BCLK1X_DIV          MM_GLB_REG_BCLK1X_DIV
#define MM_GLB_REG_BCLK1X_DIV_POS      (24U)
#define MM_GLB_REG_BCLK1X_DIV_LEN      (8U)
#define MM_GLB_REG_BCLK1X_DIV_MSK      (((1U << MM_GLB_REG_BCLK1X_DIV_LEN) - 1) << MM_GLB_REG_BCLK1X_DIV_POS)
#define MM_GLB_REG_BCLK1X_DIV_UMSK     (~(((1U << MM_GLB_REG_BCLK1X_DIV_LEN) - 1) << MM_GLB_REG_BCLK1X_DIV_POS))

/* 0x8 : dp_clk */
#define MM_GLB_DP_CLK_OFFSET          (0x8)
#define MM_GLB_REG_CLK_DIV_EN         MM_GLB_REG_CLK_DIV_EN
#define MM_GLB_REG_CLK_DIV_EN_POS     (0U)
#define MM_GLB_REG_CLK_DIV_EN_LEN     (1U)
#define MM_GLB_REG_CLK_DIV_EN_MSK     (((1U << MM_GLB_REG_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_CLK_DIV_EN_POS)
#define MM_GLB_REG_CLK_DIV_EN_UMSK    (~(((1U << MM_GLB_REG_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_CLK_DIV_EN_POS))
#define MM_GLB_REG_CLK_SEL            MM_GLB_REG_CLK_SEL
#define MM_GLB_REG_CLK_SEL_POS        (1U)
#define MM_GLB_REG_CLK_SEL_LEN        (2U)
#define MM_GLB_REG_CLK_SEL_MSK        (((1U << MM_GLB_REG_CLK_SEL_LEN) - 1) << MM_GLB_REG_CLK_SEL_POS)
#define MM_GLB_REG_CLK_SEL_UMSK       (~(((1U << MM_GLB_REG_CLK_SEL_LEN) - 1) << MM_GLB_REG_CLK_SEL_POS))
#define MM_GLB_REG_CLK_DIV            MM_GLB_REG_CLK_DIV
#define MM_GLB_REG_CLK_DIV_POS        (8U)
#define MM_GLB_REG_CLK_DIV_LEN        (8U)
#define MM_GLB_REG_CLK_DIV_MSK        (((1U << MM_GLB_REG_CLK_DIV_LEN) - 1) << MM_GLB_REG_CLK_DIV_POS)
#define MM_GLB_REG_CLK_DIV_UMSK       (~(((1U << MM_GLB_REG_CLK_DIV_LEN) - 1) << MM_GLB_REG_CLK_DIV_POS))
#define MM_GLB_REG_DP_CLK_DIV_EN      MM_GLB_REG_DP_CLK_DIV_EN
#define MM_GLB_REG_DP_CLK_DIV_EN_POS  (16U)
#define MM_GLB_REG_DP_CLK_DIV_EN_LEN  (1U)
#define MM_GLB_REG_DP_CLK_DIV_EN_MSK  (((1U << MM_GLB_REG_DP_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_DP_CLK_DIV_EN_POS)
#define MM_GLB_REG_DP_CLK_DIV_EN_UMSK (~(((1U << MM_GLB_REG_DP_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_DP_CLK_DIV_EN_POS))
#define MM_GLB_REG_DP_CLK_SEL         MM_GLB_REG_DP_CLK_SEL
#define MM_GLB_REG_DP_CLK_SEL_POS     (17U)
#define MM_GLB_REG_DP_CLK_SEL_LEN     (1U)
#define MM_GLB_REG_DP_CLK_SEL_MSK     (((1U << MM_GLB_REG_DP_CLK_SEL_LEN) - 1) << MM_GLB_REG_DP_CLK_SEL_POS)
#define MM_GLB_REG_DP_CLK_SEL_UMSK    (~(((1U << MM_GLB_REG_DP_CLK_SEL_LEN) - 1) << MM_GLB_REG_DP_CLK_SEL_POS))
#define MM_GLB_REG_DP_CLK_DIV         MM_GLB_REG_DP_CLK_DIV
#define MM_GLB_REG_DP_CLK_DIV_POS     (20U)
#define MM_GLB_REG_DP_CLK_DIV_LEN     (4U)
#define MM_GLB_REG_DP_CLK_DIV_MSK     (((1U << MM_GLB_REG_DP_CLK_DIV_LEN) - 1) << MM_GLB_REG_DP_CLK_DIV_POS)
#define MM_GLB_REG_DP_CLK_DIV_UMSK    (~(((1U << MM_GLB_REG_DP_CLK_DIV_LEN) - 1) << MM_GLB_REG_DP_CLK_DIV_POS))

/* 0xC : codec_clk */
#define MM_GLB_CODEC_CLK_OFFSET         (0xC)
#define MM_GLB_REG_H264_CLK_DIV_EN      MM_GLB_REG_H264_CLK_DIV_EN
#define MM_GLB_REG_H264_CLK_DIV_EN_POS  (8U)
#define MM_GLB_REG_H264_CLK_DIV_EN_LEN  (1U)
#define MM_GLB_REG_H264_CLK_DIV_EN_MSK  (((1U << MM_GLB_REG_H264_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_H264_CLK_DIV_EN_POS)
#define MM_GLB_REG_H264_CLK_DIV_EN_UMSK (~(((1U << MM_GLB_REG_H264_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_H264_CLK_DIV_EN_POS))
#define MM_GLB_REG_H264_CLK_SEL         MM_GLB_REG_H264_CLK_SEL
#define MM_GLB_REG_H264_CLK_SEL_POS     (9U)
#define MM_GLB_REG_H264_CLK_SEL_LEN     (2U)
#define MM_GLB_REG_H264_CLK_SEL_MSK     (((1U << MM_GLB_REG_H264_CLK_SEL_LEN) - 1) << MM_GLB_REG_H264_CLK_SEL_POS)
#define MM_GLB_REG_H264_CLK_SEL_UMSK    (~(((1U << MM_GLB_REG_H264_CLK_SEL_LEN) - 1) << MM_GLB_REG_H264_CLK_SEL_POS))
#define MM_GLB_REG_H264_CLK_DIV         MM_GLB_REG_H264_CLK_DIV
#define MM_GLB_REG_H264_CLK_DIV_POS     (12U)
#define MM_GLB_REG_H264_CLK_DIV_LEN     (3U)
#define MM_GLB_REG_H264_CLK_DIV_MSK     (((1U << MM_GLB_REG_H264_CLK_DIV_LEN) - 1) << MM_GLB_REG_H264_CLK_DIV_POS)
#define MM_GLB_REG_H264_CLK_DIV_UMSK    (~(((1U << MM_GLB_REG_H264_CLK_DIV_LEN) - 1) << MM_GLB_REG_H264_CLK_DIV_POS))

/* 0x10 : mm_clk_ctrl_peri */
#define MM_GLB_MM_CLK_CTRL_PERI_OFFSET   (0x10)
#define MM_GLB_REG_I2C0_CLK_DIV          MM_GLB_REG_I2C0_CLK_DIV
#define MM_GLB_REG_I2C0_CLK_DIV_POS      (0U)
#define MM_GLB_REG_I2C0_CLK_DIV_LEN      (8U)
#define MM_GLB_REG_I2C0_CLK_DIV_MSK      (((1U << MM_GLB_REG_I2C0_CLK_DIV_LEN) - 1) << MM_GLB_REG_I2C0_CLK_DIV_POS)
#define MM_GLB_REG_I2C0_CLK_DIV_UMSK     (~(((1U << MM_GLB_REG_I2C0_CLK_DIV_LEN) - 1) << MM_GLB_REG_I2C0_CLK_DIV_POS))
#define MM_GLB_REG_I2C0_CLK_DIV_EN       MM_GLB_REG_I2C0_CLK_DIV_EN
#define MM_GLB_REG_I2C0_CLK_DIV_EN_POS   (8U)
#define MM_GLB_REG_I2C0_CLK_DIV_EN_LEN   (1U)
#define MM_GLB_REG_I2C0_CLK_DIV_EN_MSK   (((1U << MM_GLB_REG_I2C0_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_I2C0_CLK_DIV_EN_POS)
#define MM_GLB_REG_I2C0_CLK_DIV_EN_UMSK  (~(((1U << MM_GLB_REG_I2C0_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_I2C0_CLK_DIV_EN_POS))
#define MM_GLB_REG_I2C0_CLK_EN           MM_GLB_REG_I2C0_CLK_EN
#define MM_GLB_REG_I2C0_CLK_EN_POS       (9U)
#define MM_GLB_REG_I2C0_CLK_EN_LEN       (1U)
#define MM_GLB_REG_I2C0_CLK_EN_MSK       (((1U << MM_GLB_REG_I2C0_CLK_EN_LEN) - 1) << MM_GLB_REG_I2C0_CLK_EN_POS)
#define MM_GLB_REG_I2C0_CLK_EN_UMSK      (~(((1U << MM_GLB_REG_I2C0_CLK_EN_LEN) - 1) << MM_GLB_REG_I2C0_CLK_EN_POS))
#define MM_GLB_REG_UART0_CLK_DIV_EN      MM_GLB_REG_UART0_CLK_DIV_EN
#define MM_GLB_REG_UART0_CLK_DIV_EN_POS  (16U)
#define MM_GLB_REG_UART0_CLK_DIV_EN_LEN  (1U)
#define MM_GLB_REG_UART0_CLK_DIV_EN_MSK  (((1U << MM_GLB_REG_UART0_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_UART0_CLK_DIV_EN_POS)
#define MM_GLB_REG_UART0_CLK_DIV_EN_UMSK (~(((1U << MM_GLB_REG_UART0_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_UART0_CLK_DIV_EN_POS))
#define MM_GLB_REG_UART0_CLK_DIV         MM_GLB_REG_UART0_CLK_DIV
#define MM_GLB_REG_UART0_CLK_DIV_POS     (17U)
#define MM_GLB_REG_UART0_CLK_DIV_LEN     (3U)
#define MM_GLB_REG_UART0_CLK_DIV_MSK     (((1U << MM_GLB_REG_UART0_CLK_DIV_LEN) - 1) << MM_GLB_REG_UART0_CLK_DIV_POS)
#define MM_GLB_REG_UART0_CLK_DIV_UMSK    (~(((1U << MM_GLB_REG_UART0_CLK_DIV_LEN) - 1) << MM_GLB_REG_UART0_CLK_DIV_POS))
#define MM_GLB_REG_SPI_CLK_DIV_EN        MM_GLB_REG_SPI_CLK_DIV_EN
#define MM_GLB_REG_SPI_CLK_DIV_EN_POS    (23U)
#define MM_GLB_REG_SPI_CLK_DIV_EN_LEN    (1U)
#define MM_GLB_REG_SPI_CLK_DIV_EN_MSK    (((1U << MM_GLB_REG_SPI_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_SPI_CLK_DIV_EN_POS)
#define MM_GLB_REG_SPI_CLK_DIV_EN_UMSK   (~(((1U << MM_GLB_REG_SPI_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_SPI_CLK_DIV_EN_POS))
#define MM_GLB_REG_SPI_CLK_DIV           MM_GLB_REG_SPI_CLK_DIV
#define MM_GLB_REG_SPI_CLK_DIV_POS       (24U)
#define MM_GLB_REG_SPI_CLK_DIV_LEN       (8U)
#define MM_GLB_REG_SPI_CLK_DIV_MSK       (((1U << MM_GLB_REG_SPI_CLK_DIV_LEN) - 1) << MM_GLB_REG_SPI_CLK_DIV_POS)
#define MM_GLB_REG_SPI_CLK_DIV_UMSK      (~(((1U << MM_GLB_REG_SPI_CLK_DIV_LEN) - 1) << MM_GLB_REG_SPI_CLK_DIV_POS))

/* 0x18 : mm_clk_ctrl_peri3 */
#define MM_GLB_MM_CLK_CTRL_PERI3_OFFSET  (0x18)
#define MM_GLB_REG_I2C1_CLK_DIV          MM_GLB_REG_I2C1_CLK_DIV
#define MM_GLB_REG_I2C1_CLK_DIV_POS      (0U)
#define MM_GLB_REG_I2C1_CLK_DIV_LEN      (8U)
#define MM_GLB_REG_I2C1_CLK_DIV_MSK      (((1U << MM_GLB_REG_I2C1_CLK_DIV_LEN) - 1) << MM_GLB_REG_I2C1_CLK_DIV_POS)
#define MM_GLB_REG_I2C1_CLK_DIV_UMSK     (~(((1U << MM_GLB_REG_I2C1_CLK_DIV_LEN) - 1) << MM_GLB_REG_I2C1_CLK_DIV_POS))
#define MM_GLB_REG_I2C1_CLK_DIV_EN       MM_GLB_REG_I2C1_CLK_DIV_EN
#define MM_GLB_REG_I2C1_CLK_DIV_EN_POS   (8U)
#define MM_GLB_REG_I2C1_CLK_DIV_EN_LEN   (1U)
#define MM_GLB_REG_I2C1_CLK_DIV_EN_MSK   (((1U << MM_GLB_REG_I2C1_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_I2C1_CLK_DIV_EN_POS)
#define MM_GLB_REG_I2C1_CLK_DIV_EN_UMSK  (~(((1U << MM_GLB_REG_I2C1_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_I2C1_CLK_DIV_EN_POS))
#define MM_GLB_REG_I2C1_CLK_EN           MM_GLB_REG_I2C1_CLK_EN
#define MM_GLB_REG_I2C1_CLK_EN_POS       (9U)
#define MM_GLB_REG_I2C1_CLK_EN_LEN       (1U)
#define MM_GLB_REG_I2C1_CLK_EN_MSK       (((1U << MM_GLB_REG_I2C1_CLK_EN_LEN) - 1) << MM_GLB_REG_I2C1_CLK_EN_POS)
#define MM_GLB_REG_I2C1_CLK_EN_UMSK      (~(((1U << MM_GLB_REG_I2C1_CLK_EN_LEN) - 1) << MM_GLB_REG_I2C1_CLK_EN_POS))
#define MM_GLB_REG_UART1_CLK_DIV_EN      MM_GLB_REG_UART1_CLK_DIV_EN
#define MM_GLB_REG_UART1_CLK_DIV_EN_POS  (16U)
#define MM_GLB_REG_UART1_CLK_DIV_EN_LEN  (1U)
#define MM_GLB_REG_UART1_CLK_DIV_EN_MSK  (((1U << MM_GLB_REG_UART1_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_UART1_CLK_DIV_EN_POS)
#define MM_GLB_REG_UART1_CLK_DIV_EN_UMSK (~(((1U << MM_GLB_REG_UART1_CLK_DIV_EN_LEN) - 1) << MM_GLB_REG_UART1_CLK_DIV_EN_POS))
#define MM_GLB_REG_UART1_CLK_DIV         MM_GLB_REG_UART1_CLK_DIV
#define MM_GLB_REG_UART1_CLK_DIV_POS     (17U)
#define MM_GLB_REG_UART1_CLK_DIV_LEN     (3U)
#define MM_GLB_REG_UART1_CLK_DIV_MSK     (((1U << MM_GLB_REG_UART1_CLK_DIV_LEN) - 1) << MM_GLB_REG_UART1_CLK_DIV_POS)
#define MM_GLB_REG_UART1_CLK_DIV_UMSK    (~(((1U << MM_GLB_REG_UART1_CLK_DIV_LEN) - 1) << MM_GLB_REG_UART1_CLK_DIV_POS))

/* 0x40 : mm_sw_sys_reset */
#define MM_GLB_MM_SW_SYS_RESET_OFFSET     (0x40)
#define MM_GLB_REG_CTRL_SYS_RESET         MM_GLB_REG_CTRL_SYS_RESET
#define MM_GLB_REG_CTRL_SYS_RESET_POS     (0U)
#define MM_GLB_REG_CTRL_SYS_RESET_LEN     (1U)
#define MM_GLB_REG_CTRL_SYS_RESET_MSK     (((1U << MM_GLB_REG_CTRL_SYS_RESET_LEN) - 1) << MM_GLB_REG_CTRL_SYS_RESET_POS)
#define MM_GLB_REG_CTRL_SYS_RESET_UMSK    (~(((1U << MM_GLB_REG_CTRL_SYS_RESET_LEN) - 1) << MM_GLB_REG_CTRL_SYS_RESET_POS))
#define MM_GLB_REG_CTRL_PWRON_RST         MM_GLB_REG_CTRL_PWRON_RST
#define MM_GLB_REG_CTRL_PWRON_RST_POS     (2U)
#define MM_GLB_REG_CTRL_PWRON_RST_LEN     (1U)
#define MM_GLB_REG_CTRL_PWRON_RST_MSK     (((1U << MM_GLB_REG_CTRL_PWRON_RST_LEN) - 1) << MM_GLB_REG_CTRL_PWRON_RST_POS)
#define MM_GLB_REG_CTRL_PWRON_RST_UMSK    (~(((1U << MM_GLB_REG_CTRL_PWRON_RST_LEN) - 1) << MM_GLB_REG_CTRL_PWRON_RST_POS))
#define MM_GLB_REG_CTRL_MMCPU0_RESET      MM_GLB_REG_CTRL_MMCPU0_RESET
#define MM_GLB_REG_CTRL_MMCPU0_RESET_POS  (8U)
#define MM_GLB_REG_CTRL_MMCPU0_RESET_LEN  (1U)
#define MM_GLB_REG_CTRL_MMCPU0_RESET_MSK  (((1U << MM_GLB_REG_CTRL_MMCPU0_RESET_LEN) - 1) << MM_GLB_REG_CTRL_MMCPU0_RESET_POS)
#define MM_GLB_REG_CTRL_MMCPU0_RESET_UMSK (~(((1U << MM_GLB_REG_CTRL_MMCPU0_RESET_LEN) - 1) << MM_GLB_REG_CTRL_MMCPU0_RESET_POS))

/* 0x44 : sw_reset_mm_peri */
#define MM_GLB_SW_RESET_MM_PERI_OFFSET (0x44)
#define MM_GLB_SWRST_MM_MISC           MM_GLB_SWRST_MM_MISC
#define MM_GLB_SWRST_MM_MISC_POS       (0U)
#define MM_GLB_SWRST_MM_MISC_LEN       (1U)
#define MM_GLB_SWRST_MM_MISC_MSK       (((1U << MM_GLB_SWRST_MM_MISC_LEN) - 1) << MM_GLB_SWRST_MM_MISC_POS)
#define MM_GLB_SWRST_MM_MISC_UMSK      (~(((1U << MM_GLB_SWRST_MM_MISC_LEN) - 1) << MM_GLB_SWRST_MM_MISC_POS))
#define MM_GLB_SWRST_DMA               MM_GLB_SWRST_DMA
#define MM_GLB_SWRST_DMA_POS           (1U)
#define MM_GLB_SWRST_DMA_LEN           (1U)
#define MM_GLB_SWRST_DMA_MSK           (((1U << MM_GLB_SWRST_DMA_LEN) - 1) << MM_GLB_SWRST_DMA_POS)
#define MM_GLB_SWRST_DMA_UMSK          (~(((1U << MM_GLB_SWRST_DMA_LEN) - 1) << MM_GLB_SWRST_DMA_POS))
#define MM_GLB_SWRST_UART0             MM_GLB_SWRST_UART0
#define MM_GLB_SWRST_UART0_POS         (2U)
#define MM_GLB_SWRST_UART0_LEN         (1U)
#define MM_GLB_SWRST_UART0_MSK         (((1U << MM_GLB_SWRST_UART0_LEN) - 1) << MM_GLB_SWRST_UART0_POS)
#define MM_GLB_SWRST_UART0_UMSK        (~(((1U << MM_GLB_SWRST_UART0_LEN) - 1) << MM_GLB_SWRST_UART0_POS))
#define MM_GLB_SWRST_I2C0              MM_GLB_SWRST_I2C0
#define MM_GLB_SWRST_I2C0_POS          (3U)
#define MM_GLB_SWRST_I2C0_LEN          (1U)
#define MM_GLB_SWRST_I2C0_MSK          (((1U << MM_GLB_SWRST_I2C0_LEN) - 1) << MM_GLB_SWRST_I2C0_POS)
#define MM_GLB_SWRST_I2C0_UMSK         (~(((1U << MM_GLB_SWRST_I2C0_LEN) - 1) << MM_GLB_SWRST_I2C0_POS))
#define MM_GLB_SWRST_I2C1              MM_GLB_SWRST_I2C1
#define MM_GLB_SWRST_I2C1_POS          (4U)
#define MM_GLB_SWRST_I2C1_LEN          (1U)
#define MM_GLB_SWRST_I2C1_MSK          (((1U << MM_GLB_SWRST_I2C1_LEN) - 1) << MM_GLB_SWRST_I2C1_POS)
#define MM_GLB_SWRST_I2C1_UMSK         (~(((1U << MM_GLB_SWRST_I2C1_LEN) - 1) << MM_GLB_SWRST_I2C1_POS))
#define MM_GLB_SWRST_IPC               MM_GLB_SWRST_IPC
#define MM_GLB_SWRST_IPC_POS           (5U)
#define MM_GLB_SWRST_IPC_LEN           (1U)
#define MM_GLB_SWRST_IPC_MSK           (((1U << MM_GLB_SWRST_IPC_LEN) - 1) << MM_GLB_SWRST_IPC_POS)
#define MM_GLB_SWRST_IPC_UMSK          (~(((1U << MM_GLB_SWRST_IPC_LEN) - 1) << MM_GLB_SWRST_IPC_POS))
#define MM_GLB_SWRST_DMA2D             MM_GLB_SWRST_DMA2D
#define MM_GLB_SWRST_DMA2D_POS         (6U)
#define MM_GLB_SWRST_DMA2D_LEN         (1U)
#define MM_GLB_SWRST_DMA2D_MSK         (((1U << MM_GLB_SWRST_DMA2D_LEN) - 1) << MM_GLB_SWRST_DMA2D_POS)
#define MM_GLB_SWRST_DMA2D_UMSK        (~(((1U << MM_GLB_SWRST_DMA2D_LEN) - 1) << MM_GLB_SWRST_DMA2D_POS))
#define MM_GLB_SWRST_SPI               MM_GLB_SWRST_SPI
#define MM_GLB_SWRST_SPI_POS           (8U)
#define MM_GLB_SWRST_SPI_LEN           (1U)
#define MM_GLB_SWRST_SPI_MSK           (((1U << MM_GLB_SWRST_SPI_LEN) - 1) << MM_GLB_SWRST_SPI_POS)
#define MM_GLB_SWRST_SPI_UMSK          (~(((1U << MM_GLB_SWRST_SPI_LEN) - 1) << MM_GLB_SWRST_SPI_POS))
#define MM_GLB_SWRST_TIMER             MM_GLB_SWRST_TIMER
#define MM_GLB_SWRST_TIMER_POS         (9U)
#define MM_GLB_SWRST_TIMER_LEN         (1U)
#define MM_GLB_SWRST_TIMER_MSK         (((1U << MM_GLB_SWRST_TIMER_LEN) - 1) << MM_GLB_SWRST_TIMER_POS)
#define MM_GLB_SWRST_TIMER_UMSK        (~(((1U << MM_GLB_SWRST_TIMER_LEN) - 1) << MM_GLB_SWRST_TIMER_POS))
#define MM_GLB_SWRST_I2S0              MM_GLB_SWRST_I2S0
#define MM_GLB_SWRST_I2S0_POS          (10U)
#define MM_GLB_SWRST_I2S0_LEN          (1U)
#define MM_GLB_SWRST_I2S0_MSK          (((1U << MM_GLB_SWRST_I2S0_LEN) - 1) << MM_GLB_SWRST_I2S0_POS)
#define MM_GLB_SWRST_I2S0_UMSK         (~(((1U << MM_GLB_SWRST_I2S0_LEN) - 1) << MM_GLB_SWRST_I2S0_POS))
#define MM_GLB_SWRST_I2S1              MM_GLB_SWRST_I2S1
#define MM_GLB_SWRST_I2S1_POS          (11U)
#define MM_GLB_SWRST_I2S1_LEN          (1U)
#define MM_GLB_SWRST_I2S1_MSK          (((1U << MM_GLB_SWRST_I2S1_LEN) - 1) << MM_GLB_SWRST_I2S1_POS)
#define MM_GLB_SWRST_I2S1_UMSK         (~(((1U << MM_GLB_SWRST_I2S1_LEN) - 1) << MM_GLB_SWRST_I2S1_POS))
#define MM_GLB_SWRST_PDM0              MM_GLB_SWRST_PDM0
#define MM_GLB_SWRST_PDM0_POS          (12U)
#define MM_GLB_SWRST_PDM0_LEN          (1U)
#define MM_GLB_SWRST_PDM0_MSK          (((1U << MM_GLB_SWRST_PDM0_LEN) - 1) << MM_GLB_SWRST_PDM0_POS)
#define MM_GLB_SWRST_PDM0_UMSK         (~(((1U << MM_GLB_SWRST_PDM0_LEN) - 1) << MM_GLB_SWRST_PDM0_POS))
#define MM_GLB_SWRST_PDM1              MM_GLB_SWRST_PDM1
#define MM_GLB_SWRST_PDM1_POS          (13U)
#define MM_GLB_SWRST_PDM1_LEN          (1U)
#define MM_GLB_SWRST_PDM1_MSK          (((1U << MM_GLB_SWRST_PDM1_LEN) - 1) << MM_GLB_SWRST_PDM1_POS)
#define MM_GLB_SWRST_PDM1_UMSK         (~(((1U << MM_GLB_SWRST_PDM1_LEN) - 1) << MM_GLB_SWRST_PDM1_POS))
#define MM_GLB_SWRST_UART1             MM_GLB_SWRST_UART1
#define MM_GLB_SWRST_UART1_POS         (14U)
#define MM_GLB_SWRST_UART1_LEN         (1U)
#define MM_GLB_SWRST_UART1_MSK         (((1U << MM_GLB_SWRST_UART1_LEN) - 1) << MM_GLB_SWRST_UART1_POS)
#define MM_GLB_SWRST_UART1_UMSK        (~(((1U << MM_GLB_SWRST_UART1_LEN) - 1) << MM_GLB_SWRST_UART1_POS))
#define MM_GLB_SWRST_PUHS              MM_GLB_SWRST_PUHS
#define MM_GLB_SWRST_PUHS_POS          (15U)
#define MM_GLB_SWRST_PUHS_LEN          (1U)
#define MM_GLB_SWRST_PUHS_MSK          (((1U << MM_GLB_SWRST_PUHS_LEN) - 1) << MM_GLB_SWRST_PUHS_POS)
#define MM_GLB_SWRST_PUHS_UMSK         (~(((1U << MM_GLB_SWRST_PUHS_LEN) - 1) << MM_GLB_SWRST_PUHS_POS))

/* 0x48 : sw_reset_sub */
#define MM_GLB_SW_RESET_SUB_OFFSET  (0x48)
#define MM_GLB_SWRST_MISC           MM_GLB_SWRST_MISC
#define MM_GLB_SWRST_MISC_POS       (0U)
#define MM_GLB_SWRST_MISC_LEN       (1U)
#define MM_GLB_SWRST_MISC_MSK       (((1U << MM_GLB_SWRST_MISC_LEN) - 1) << MM_GLB_SWRST_MISC_POS)
#define MM_GLB_SWRST_MISC_UMSK      (~(((1U << MM_GLB_SWRST_MISC_LEN) - 1) << MM_GLB_SWRST_MISC_POS))
#define MM_GLB_SWRST_MAIN           MM_GLB_SWRST_MAIN
#define MM_GLB_SWRST_MAIN_POS       (1U)
#define MM_GLB_SWRST_MAIN_LEN       (1U)
#define MM_GLB_SWRST_MAIN_MSK       (((1U << MM_GLB_SWRST_MAIN_LEN) - 1) << MM_GLB_SWRST_MAIN_POS)
#define MM_GLB_SWRST_MAIN_UMSK      (~(((1U << MM_GLB_SWRST_MAIN_LEN) - 1) << MM_GLB_SWRST_MAIN_POS))
#define MM_GLB_SWRST_TSRC           MM_GLB_SWRST_TSRC
#define MM_GLB_SWRST_TSRC_POS       (2U)
#define MM_GLB_SWRST_TSRC_LEN       (1U)
#define MM_GLB_SWRST_TSRC_MSK       (((1U << MM_GLB_SWRST_TSRC_LEN) - 1) << MM_GLB_SWRST_TSRC_POS)
#define MM_GLB_SWRST_TSRC_UMSK      (~(((1U << MM_GLB_SWRST_TSRC_LEN) - 1) << MM_GLB_SWRST_TSRC_POS))
#define MM_GLB_SWRST_DP_TSRC        MM_GLB_SWRST_DP_TSRC
#define MM_GLB_SWRST_DP_TSRC_POS    (3U)
#define MM_GLB_SWRST_DP_TSRC_LEN    (1U)
#define MM_GLB_SWRST_DP_TSRC_MSK    (((1U << MM_GLB_SWRST_DP_TSRC_LEN) - 1) << MM_GLB_SWRST_DP_TSRC_POS)
#define MM_GLB_SWRST_DP_TSRC_UMSK   (~(((1U << MM_GLB_SWRST_DP_TSRC_LEN) - 1) << MM_GLB_SWRST_DP_TSRC_POS))
#define MM_GLB_SWRST_NR3D_CTRL      MM_GLB_SWRST_NR3D_CTRL
#define MM_GLB_SWRST_NR3D_CTRL_POS  (4U)
#define MM_GLB_SWRST_NR3D_CTRL_LEN  (1U)
#define MM_GLB_SWRST_NR3D_CTRL_MSK  (((1U << MM_GLB_SWRST_NR3D_CTRL_LEN) - 1) << MM_GLB_SWRST_NR3D_CTRL_POS)
#define MM_GLB_SWRST_NR3D_CTRL_UMSK (~(((1U << MM_GLB_SWRST_NR3D_CTRL_LEN) - 1) << MM_GLB_SWRST_NR3D_CTRL_POS))
#define MM_GLB_SWRST_DVP2BUSA       MM_GLB_SWRST_DVP2BUSA
#define MM_GLB_SWRST_DVP2BUSA_POS   (5U)
#define MM_GLB_SWRST_DVP2BUSA_LEN   (1U)
#define MM_GLB_SWRST_DVP2BUSA_MSK   (((1U << MM_GLB_SWRST_DVP2BUSA_LEN) - 1) << MM_GLB_SWRST_DVP2BUSA_POS)
#define MM_GLB_SWRST_DVP2BUSA_UMSK  (~(((1U << MM_GLB_SWRST_DVP2BUSA_LEN) - 1) << MM_GLB_SWRST_DVP2BUSA_POS))
#define MM_GLB_SWRST_DVP2BUSB       MM_GLB_SWRST_DVP2BUSB
#define MM_GLB_SWRST_DVP2BUSB_POS   (6U)
#define MM_GLB_SWRST_DVP2BUSB_LEN   (1U)
#define MM_GLB_SWRST_DVP2BUSB_MSK   (((1U << MM_GLB_SWRST_DVP2BUSB_LEN) - 1) << MM_GLB_SWRST_DVP2BUSB_POS)
#define MM_GLB_SWRST_DVP2BUSB_UMSK  (~(((1U << MM_GLB_SWRST_DVP2BUSB_LEN) - 1) << MM_GLB_SWRST_DVP2BUSB_POS))
#define MM_GLB_SWRST_DVP2BUSC       MM_GLB_SWRST_DVP2BUSC
#define MM_GLB_SWRST_DVP2BUSC_POS   (7U)
#define MM_GLB_SWRST_DVP2BUSC_LEN   (1U)
#define MM_GLB_SWRST_DVP2BUSC_MSK   (((1U << MM_GLB_SWRST_DVP2BUSC_LEN) - 1) << MM_GLB_SWRST_DVP2BUSC_POS)
#define MM_GLB_SWRST_DVP2BUSC_UMSK  (~(((1U << MM_GLB_SWRST_DVP2BUSC_LEN) - 1) << MM_GLB_SWRST_DVP2BUSC_POS))
#define MM_GLB_SWRST_DVP2BUSD       MM_GLB_SWRST_DVP2BUSD
#define MM_GLB_SWRST_DVP2BUSD_POS   (8U)
#define MM_GLB_SWRST_DVP2BUSD_LEN   (1U)
#define MM_GLB_SWRST_DVP2BUSD_MSK   (((1U << MM_GLB_SWRST_DVP2BUSD_LEN) - 1) << MM_GLB_SWRST_DVP2BUSD_POS)
#define MM_GLB_SWRST_DVP2BUSD_UMSK  (~(((1U << MM_GLB_SWRST_DVP2BUSD_LEN) - 1) << MM_GLB_SWRST_DVP2BUSD_POS))
#define MM_GLB_SWRST_MIPI           MM_GLB_SWRST_MIPI
#define MM_GLB_SWRST_MIPI_POS       (9U)
#define MM_GLB_SWRST_MIPI_LEN       (1U)
#define MM_GLB_SWRST_MIPI_MSK       (((1U << MM_GLB_SWRST_MIPI_LEN) - 1) << MM_GLB_SWRST_MIPI_POS)
#define MM_GLB_SWRST_MIPI_UMSK      (~(((1U << MM_GLB_SWRST_MIPI_LEN) - 1) << MM_GLB_SWRST_MIPI_POS))
#define MM_GLB_SWRST_DVP2BUSE       MM_GLB_SWRST_DVP2BUSE
#define MM_GLB_SWRST_DVP2BUSE_POS   (17U)
#define MM_GLB_SWRST_DVP2BUSE_LEN   (1U)
#define MM_GLB_SWRST_DVP2BUSE_MSK   (((1U << MM_GLB_SWRST_DVP2BUSE_LEN) - 1) << MM_GLB_SWRST_DVP2BUSE_POS)
#define MM_GLB_SWRST_DVP2BUSE_UMSK  (~(((1U << MM_GLB_SWRST_DVP2BUSE_LEN) - 1) << MM_GLB_SWRST_DVP2BUSE_POS))
#define MM_GLB_SWRST_DVP2BUSF       MM_GLB_SWRST_DVP2BUSF
#define MM_GLB_SWRST_DVP2BUSF_POS   (18U)
#define MM_GLB_SWRST_DVP2BUSF_LEN   (1U)
#define MM_GLB_SWRST_DVP2BUSF_MSK   (((1U << MM_GLB_SWRST_DVP2BUSF_LEN) - 1) << MM_GLB_SWRST_DVP2BUSF_POS)
#define MM_GLB_SWRST_DVP2BUSF_UMSK  (~(((1U << MM_GLB_SWRST_DVP2BUSF_LEN) - 1) << MM_GLB_SWRST_DVP2BUSF_POS))
#define MM_GLB_SWRST_DVP2BUSG       MM_GLB_SWRST_DVP2BUSG
#define MM_GLB_SWRST_DVP2BUSG_POS   (19U)
#define MM_GLB_SWRST_DVP2BUSG_LEN   (1U)
#define MM_GLB_SWRST_DVP2BUSG_MSK   (((1U << MM_GLB_SWRST_DVP2BUSG_LEN) - 1) << MM_GLB_SWRST_DVP2BUSG_POS)
#define MM_GLB_SWRST_DVP2BUSG_UMSK  (~(((1U << MM_GLB_SWRST_DVP2BUSG_LEN) - 1) << MM_GLB_SWRST_DVP2BUSG_POS))
#define MM_GLB_SWRST_DVP2BUSH       MM_GLB_SWRST_DVP2BUSH
#define MM_GLB_SWRST_DVP2BUSH_POS   (20U)
#define MM_GLB_SWRST_DVP2BUSH_LEN   (1U)
#define MM_GLB_SWRST_DVP2BUSH_MSK   (((1U << MM_GLB_SWRST_DVP2BUSH_LEN) - 1) << MM_GLB_SWRST_DVP2BUSH_POS)
#define MM_GLB_SWRST_DVP2BUSH_UMSK  (~(((1U << MM_GLB_SWRST_DVP2BUSH_LEN) - 1) << MM_GLB_SWRST_DVP2BUSH_POS))

/* 0x4C : sw_reset_codec_sub */
#define MM_GLB_SW_RESET_CODEC_SUB_OFFSET (0x4C)
#define MM_GLB_SWRST_CODEC_MISC          MM_GLB_SWRST_CODEC_MISC
#define MM_GLB_SWRST_CODEC_MISC_POS      (0U)
#define MM_GLB_SWRST_CODEC_MISC_LEN      (1U)
#define MM_GLB_SWRST_CODEC_MISC_MSK      (((1U << MM_GLB_SWRST_CODEC_MISC_LEN) - 1) << MM_GLB_SWRST_CODEC_MISC_POS)
#define MM_GLB_SWRST_CODEC_MISC_UMSK     (~(((1U << MM_GLB_SWRST_CODEC_MISC_LEN) - 1) << MM_GLB_SWRST_CODEC_MISC_POS))
#define MM_GLB_SWRST_MJPEG               MM_GLB_SWRST_MJPEG
#define MM_GLB_SWRST_MJPEG_POS           (1U)
#define MM_GLB_SWRST_MJPEG_LEN           (1U)
#define MM_GLB_SWRST_MJPEG_MSK           (((1U << MM_GLB_SWRST_MJPEG_LEN) - 1) << MM_GLB_SWRST_MJPEG_POS)
#define MM_GLB_SWRST_MJPEG_UMSK          (~(((1U << MM_GLB_SWRST_MJPEG_LEN) - 1) << MM_GLB_SWRST_MJPEG_POS))
#define MM_GLB_SWRST_H264                MM_GLB_SWRST_H264
#define MM_GLB_SWRST_H264_POS            (2U)
#define MM_GLB_SWRST_H264_LEN            (1U)
#define MM_GLB_SWRST_H264_MSK            (((1U << MM_GLB_SWRST_H264_LEN) - 1) << MM_GLB_SWRST_H264_POS)
#define MM_GLB_SWRST_H264_UMSK           (~(((1U << MM_GLB_SWRST_H264_LEN) - 1) << MM_GLB_SWRST_H264_POS))
#define MM_GLB_SWRST_MJPEG_DEC           MM_GLB_SWRST_MJPEG_DEC
#define MM_GLB_SWRST_MJPEG_DEC_POS       (3U)
#define MM_GLB_SWRST_MJPEG_DEC_LEN       (1U)
#define MM_GLB_SWRST_MJPEG_DEC_MSK       (((1U << MM_GLB_SWRST_MJPEG_DEC_LEN) - 1) << MM_GLB_SWRST_MJPEG_DEC_POS)
#define MM_GLB_SWRST_MJPEG_DEC_UMSK      (~(((1U << MM_GLB_SWRST_MJPEG_DEC_LEN) - 1) << MM_GLB_SWRST_MJPEG_DEC_POS))
#define MM_GLB_SWRST_CNN                 MM_GLB_SWRST_CNN
#define MM_GLB_SWRST_CNN_POS             (4U)
#define MM_GLB_SWRST_CNN_LEN             (1U)
#define MM_GLB_SWRST_CNN_MSK             (((1U << MM_GLB_SWRST_CNN_LEN) - 1) << MM_GLB_SWRST_CNN_POS)
#define MM_GLB_SWRST_CNN_UMSK            (~(((1U << MM_GLB_SWRST_CNN_LEN) - 1) << MM_GLB_SWRST_CNN_POS))
#define MM_GLB_SWRST_VRAM                MM_GLB_SWRST_VRAM
#define MM_GLB_SWRST_VRAM_POS            (16U)
#define MM_GLB_SWRST_VRAM_LEN            (1U)
#define MM_GLB_SWRST_VRAM_MSK            (((1U << MM_GLB_SWRST_VRAM_LEN) - 1) << MM_GLB_SWRST_VRAM_POS)
#define MM_GLB_SWRST_VRAM_UMSK           (~(((1U << MM_GLB_SWRST_VRAM_LEN) - 1) << MM_GLB_SWRST_VRAM_POS))

/* 0x50 : image_sensor_ctrl */
#define MM_GLB_IMAGE_SENSOR_CTRL_OFFSET (0x50)
#define MM_GLB_RG_IS_RST_N              MM_GLB_RG_IS_RST_N
#define MM_GLB_RG_IS_RST_N_POS          (0U)
#define MM_GLB_RG_IS_RST_N_LEN          (1U)
#define MM_GLB_RG_IS_RST_N_MSK          (((1U << MM_GLB_RG_IS_RST_N_LEN) - 1) << MM_GLB_RG_IS_RST_N_POS)
#define MM_GLB_RG_IS_RST_N_UMSK         (~(((1U << MM_GLB_RG_IS_RST_N_LEN) - 1) << MM_GLB_RG_IS_RST_N_POS))

/* 0x60 : tz_mm_clkrst */
#define MM_GLB_TZ_MM_CLKRST_OFFSET         (0x60)
#define MM_GLB_TZC_MM_SWRST_LOCK           MM_GLB_TZC_MM_SWRST_LOCK
#define MM_GLB_TZC_MM_SWRST_LOCK_POS       (0U)
#define MM_GLB_TZC_MM_SWRST_LOCK_LEN       (1U)
#define MM_GLB_TZC_MM_SWRST_LOCK_MSK       (((1U << MM_GLB_TZC_MM_SWRST_LOCK_LEN) - 1) << MM_GLB_TZC_MM_SWRST_LOCK_POS)
#define MM_GLB_TZC_MM_SWRST_LOCK_UMSK      (~(((1U << MM_GLB_TZC_MM_SWRST_LOCK_LEN) - 1) << MM_GLB_TZC_MM_SWRST_LOCK_POS))
#define MM_GLB_TZC_MM_SYS_RESET_LOCK       MM_GLB_TZC_MM_SYS_RESET_LOCK
#define MM_GLB_TZC_MM_SYS_RESET_LOCK_POS   (1U)
#define MM_GLB_TZC_MM_SYS_RESET_LOCK_LEN   (1U)
#define MM_GLB_TZC_MM_SYS_RESET_LOCK_MSK   (((1U << MM_GLB_TZC_MM_SYS_RESET_LOCK_LEN) - 1) << MM_GLB_TZC_MM_SYS_RESET_LOCK_POS)
#define MM_GLB_TZC_MM_SYS_RESET_LOCK_UMSK  (~(((1U << MM_GLB_TZC_MM_SYS_RESET_LOCK_LEN) - 1) << MM_GLB_TZC_MM_SYS_RESET_LOCK_POS))
#define MM_GLB_TZC_MM_PWRON_RST_LOCK       MM_GLB_TZC_MM_PWRON_RST_LOCK
#define MM_GLB_TZC_MM_PWRON_RST_LOCK_POS   (2U)
#define MM_GLB_TZC_MM_PWRON_RST_LOCK_LEN   (1U)
#define MM_GLB_TZC_MM_PWRON_RST_LOCK_MSK   (((1U << MM_GLB_TZC_MM_PWRON_RST_LOCK_LEN) - 1) << MM_GLB_TZC_MM_PWRON_RST_LOCK_POS)
#define MM_GLB_TZC_MM_PWRON_RST_LOCK_UMSK  (~(((1U << MM_GLB_TZC_MM_PWRON_RST_LOCK_LEN) - 1) << MM_GLB_TZC_MM_PWRON_RST_LOCK_POS))
#define MM_GLB_TZC_MM_CPU0_RESET_LOCK      MM_GLB_TZC_MM_CPU0_RESET_LOCK
#define MM_GLB_TZC_MM_CPU0_RESET_LOCK_POS  (3U)
#define MM_GLB_TZC_MM_CPU0_RESET_LOCK_LEN  (1U)
#define MM_GLB_TZC_MM_CPU0_RESET_LOCK_MSK  (((1U << MM_GLB_TZC_MM_CPU0_RESET_LOCK_LEN) - 1) << MM_GLB_TZC_MM_CPU0_RESET_LOCK_POS)
#define MM_GLB_TZC_MM_CPU0_RESET_LOCK_UMSK (~(((1U << MM_GLB_TZC_MM_CPU0_RESET_LOCK_LEN) - 1) << MM_GLB_TZC_MM_CPU0_RESET_LOCK_POS))
#define MM_GLB_TZC_MM_CLK_LOCK             MM_GLB_TZC_MM_CLK_LOCK
#define MM_GLB_TZC_MM_CLK_LOCK_POS         (4U)
#define MM_GLB_TZC_MM_CLK_LOCK_LEN         (1U)
#define MM_GLB_TZC_MM_CLK_LOCK_MSK         (((1U << MM_GLB_TZC_MM_CLK_LOCK_LEN) - 1) << MM_GLB_TZC_MM_CLK_LOCK_POS)
#define MM_GLB_TZC_MM_CLK_LOCK_UMSK        (~(((1U << MM_GLB_TZC_MM_CLK_LOCK_LEN) - 1) << MM_GLB_TZC_MM_CLK_LOCK_POS))

struct mm_glb_reg {
    /* 0x0 : mm_clk_ctrl_cpu */
    union {
        struct {
            uint32_t reg_pll_en               : 1; /* [    0],        r/w,        0x1 */
            uint32_t reg_cpu_clk_en           : 1; /* [    1],        r/w,        0x1 */
            uint32_t reg_bclk_en              : 1; /* [    2],        r/w,        0x1 */
            uint32_t reg_mm_cpu_clk_en        : 1; /* [    3],        r/w,        0x1 */
            uint32_t reg_uart_clk_sel         : 2; /* [ 5: 4],        r/w,        0x0 */
            uint32_t reg_i2c_clk_sel          : 1; /* [    6],        r/w,        0x0 */
            uint32_t reg_spi_clk_sel          : 1; /* [    7],        r/w,        0x0 */
            uint32_t reg_cpu_clk_sel          : 2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reg_xclk_clk_sel         : 1; /* [   10],        r/w,        0x0 */
            uint32_t reg_cpu_root_clk_sel     : 1; /* [   11],        r/w,        0x0 */
            uint32_t reg_mmcpu0_clk_en        : 1; /* [   12],        r/w,        0x0 */
            uint32_t reg_bclk1x_sel           : 2; /* [14:13],        r/w,        0x0 */
            uint32_t reserved_15_17           : 3; /* [17:15],       rsvd,        0x0 */
            uint32_t reg_bclk2x_div_act_pulse : 1; /* [   18],        w1p,        0x0 */
            uint32_t reg_bclk2x_div_bypass    : 1; /* [   19],        r/w,        0x0 */
            uint32_t sts_bclk2x_prot_done     : 1; /* [   20],          r,        0x1 */
            uint32_t reserved_21_23           : 3; /* [23:21],       rsvd,        0x0 */
            uint32_t reg_bclk2x_sw_done_cnt   : 4; /* [27:24],        r/w,        0x5 */
            uint32_t cpu_clk_sw_state         : 3; /* [30:28],          r,        0x0 */
            uint32_t reserved_31              : 1; /* [   31],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mm_clk_ctrl_cpu;

    /* 0x4 : mm_clk_cpu */
    union {
        struct {
            uint32_t reg_cpu_clk_div    : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_cnn_clk_div_en : 1; /* [    8],        r/w,        0x1 */
            uint32_t reg_cnn_clk_sel    : 2; /* [10: 9],        r/w,        0x0 */
            uint32_t reserved_11        : 1; /* [   11],       rsvd,        0x0 */
            uint32_t reg_cnn_clk_div    : 3; /* [14:12],        r/w,        0x0 */
            uint32_t reserved_15        : 1; /* [   15],       rsvd,        0x0 */
            uint32_t reg_bclk2x_div     : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_bclk1x_div     : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } mm_clk_cpu;

    /* 0x8 : dp_clk */
    union {
        struct {
            uint32_t reserved_0_15     : 16; /* [15: 0],       rsvd,        0x0 */
            uint32_t reg_dp_clk_div_en : 1;  /* [   16],        r/w,        0x1 */
            uint32_t reg_dp_clk_sel    : 1;  /* [   17],        r/w,        0x0 */
            uint32_t reserved_18_19    : 2;  /* [19:18],       rsvd,        0x0 */
            uint32_t reg_dp_clk_div    : 4;  /* [23:20],        r/w,        0x0 */
            uint32_t reserved_24_31    : 8;  /* [31:24],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } dp_clk;

    /* 0xC : codec_clk */
    union {
        struct {
            uint32_t reserved_0_7        : 8;  /* [ 7: 0],       rsvd,        0x0 */
            uint32_t reg_h264_clk_div_en : 1;  /* [    8],        r/w,        0x1 */
            uint32_t reg_h264_clk_sel    : 2;  /* [10: 9],        r/w,        0x0 */
            uint32_t reserved_11         : 1;  /* [   11],       rsvd,        0x0 */
            uint32_t reg_h264_clk_div    : 3;  /* [14:12],        r/w,        0x0 */
            uint32_t reserved_15_31      : 17; /* [31:15],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } codec_clk;

    /* 0x10 : mm_clk_ctrl_peri */
    union {
        struct {
            uint32_t reg_i2c0_clk_div     : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_i2c0_clk_div_en  : 1; /* [    8],        r/w,        0x1 */
            uint32_t reg_i2c0_clk_en      : 1; /* [    9],        r/w,        0x1 */
            uint32_t reserved_10_15       : 6; /* [15:10],       rsvd,        0x0 */
            uint32_t reg_uart0_clk_div_en : 1; /* [   16],        r/w,        0x1 */
            uint32_t reg_uart0_clk_div    : 3; /* [19:17],        r/w,        0x0 */
            uint32_t reserved_20_22       : 3; /* [22:20],       rsvd,        0x0 */
            uint32_t reg_spi_clk_div_en   : 1; /* [   23],        r/w,        0x1 */
            uint32_t reg_spi_clk_div      : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } mm_clk_ctrl_peri;

    /* 0x14  reserved */
    uint8_t RESERVED0x14[4];

    /* 0x18 : mm_clk_ctrl_peri3 */
    union {
        struct {
            uint32_t reg_i2c1_clk_div     : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_i2c1_clk_div_en  : 1;  /* [    8],        r/w,        0x1 */
            uint32_t reg_i2c1_clk_en      : 1;  /* [    9],        r/w,        0x1 */
            uint32_t reserved_10_15       : 6;  /* [15:10],       rsvd,        0x0 */
            uint32_t reg_uart1_clk_div_en : 1;  /* [   16],        r/w,        0x1 */
            uint32_t reg_uart1_clk_div    : 3;  /* [19:17],        r/w,        0x0 */
            uint32_t reserved_20_31       : 12; /* [31:20],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mm_clk_ctrl_peri3;

    /* 0x1c  reserved */
    uint8_t RESERVED0x1c[36];

    /* 0x40 : mm_sw_sys_reset */
    union {
        struct {
            uint32_t reg_ctrl_sys_reset    : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1            : 1;  /* [    1],       rsvd,        0x0 */
            uint32_t reg_ctrl_pwron_rst    : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_7          : 5;  /* [ 7: 3],       rsvd,        0x0 */
            uint32_t reg_ctrl_mmcpu0_reset : 1;  /* [    8],        r/w,        0x1 */
            uint32_t reserved_9_31         : 23; /* [31: 9],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mm_sw_sys_reset;

    /* 0x44 : sw_reset_mm_peri */
    union {
        struct {
            uint32_t swrst_mm_misc  : 1;  /* [    0],        r/w,        0x0 */
            uint32_t swrst_dma      : 1;  /* [    1],        r/w,        0x0 */
            uint32_t swrst_uart0    : 1;  /* [    2],        r/w,        0x0 */
            uint32_t swrst_i2c0     : 1;  /* [    3],        r/w,        0x0 */
            uint32_t swrst_i2c1     : 1;  /* [    4],        r/w,        0x0 */
            uint32_t swrst_ipc      : 1;  /* [    5],        r/w,        0x0 */
            uint32_t swrst_dma2d    : 1;  /* [    6],        r/w,        0x0 */
            uint32_t reserved_7     : 1;  /* [    7],       rsvd,        0x0 */
            uint32_t swrst_spi      : 1;  /* [    8],        r/w,        0x0 */
            uint32_t swrst_timer    : 1;  /* [    9],        r/w,        0x0 */
            uint32_t swrst_i2s0     : 1;  /* [   10],        r/w,        0x0 */
            uint32_t swrst_i2s1     : 1;  /* [   11],        r/w,        0x0 */
            uint32_t swrst_pdm0     : 1;  /* [   12],        r/w,        0x0 */
            uint32_t swrst_pdm1     : 1;  /* [   13],        r/w,        0x0 */
            uint32_t swrst_uart1    : 1;  /* [   14],        r/w,        0x0 */
            uint32_t swrst_pUHS     : 1;  /* [   15],        r/w,        0x0 */
            uint32_t reserved_16_31 : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } sw_reset_mm_peri;

    /* 0x48 : sw_reset_sub */
    union {
        struct {
            uint32_t swrst_misc      : 1;  /* [    0],        r/w,        0x0 */
            uint32_t swrst_main      : 1;  /* [    1],        r/w,        0x0 */
            uint32_t swrst_tsrc      : 1;  /* [    2],        r/w,        0x0 */
            uint32_t swrst_dp_tsrc   : 1;  /* [    3],        r/w,        0x0 */
            uint32_t swrst_nr3d_ctrl : 1;  /* [    4],        r/w,        0x0 */
            uint32_t swrst_dvp2busA  : 1;  /* [    5],        r/w,        0x0 */
            uint32_t swrst_dvp2busB  : 1;  /* [    6],        r/w,        0x0 */
            uint32_t swrst_dvp2busC  : 1;  /* [    7],        r/w,        0x0 */
            uint32_t swrst_dvp2busD  : 1;  /* [    8],        r/w,        0x0 */
            uint32_t swrst_mipi      : 1;  /* [    9],        r/w,        0x0 */
            uint32_t reserved_10_15  : 6;  /* [15:10],       rsvd,        0x0 */
            uint32_t swrst_reg       : 1;  /* [   16],        r/w,        0x0 */
            uint32_t swrst_dvp2busE  : 1;  /* [   17],        r/w,        0x0 */
            uint32_t swrst_dvp2busF  : 1;  /* [   18],        r/w,        0x0 */
            uint32_t swrst_dvp2busG  : 1;  /* [   19],        r/w,        0x0 */
            uint32_t swrst_dvp2busH  : 1;  /* [   20],        r/w,        0x0 */
            uint32_t reserved_21_31  : 11; /* [31:21],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } sw_reset_sub;

    /* 0x4C : sw_reset_codec_sub */
    union {
        struct {
            uint32_t swrst_codec_misc : 1;  /* [    0],        r/w,        0x0 */
            uint32_t swrst_mjpeg      : 1;  /* [    1],        r/w,        0x0 */
            uint32_t swrst_h264       : 1;  /* [    2],        r/w,        0x0 */
            uint32_t swrst_mjpeg_dec  : 1;  /* [    3],        r/w,        0x0 */
            uint32_t swrst_cnn        : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_15    : 11; /* [15: 5],       rsvd,        0x0 */
            uint32_t swrst_vram       : 1;  /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_31   : 15; /* [31:17],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } sw_reset_codec_sub;

    /* 0x50 : image_sensor_ctrl */
    union {
        struct {
            uint32_t rg_is_rst_n   : 1;  /* [    0],        r/w,        0x1 */
            uint32_t reserved_1_31 : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } image_sensor_ctrl;

    /* 0x54  reserved */
    uint8_t RESERVED0x54[12];

    /* 0x60 : tz_mm_clkrst */
    union {
        struct {
            uint32_t tzc_mm_swrst_lock      : 1;  /* [    0],          r,        0x0 */
            uint32_t tzc_mm_sys_reset_lock  : 1;  /* [    1],          r,        0x0 */
            uint32_t tzc_mm_pwron_rst_lock  : 1;  /* [    2],          r,        0x0 */
            uint32_t tzc_mm_cpu0_reset_lock : 1;  /* [    3],          r,        0x0 */
            uint32_t tzc_mm_clk_lock        : 1;  /* [    4],          r,        0x0 */
            uint32_t reserved_5_31          : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } tz_mm_clkrst;
};

typedef volatile struct mm_glb_reg mm_glb_reg_t;

#endif /* __MM_GLB_REG_H__ */
