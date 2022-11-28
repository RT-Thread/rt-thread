/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
 *
 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 *the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.
 *
 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
 * PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
 * THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
 * OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __SUN8IW19P1_CLK_H__
#define __SUN8IW19P1_CLK_H__

#include <stdio.h>
#include <string.h>

#include <hal_clk.h>
#include "../clk.h"

#define CLK_PARENT_MAX 6
// clk_fixed_factor_pt sunxi_clk_fixed_factor_arry[SUNXI_CLK_FIXED_FACTOR_MAX];
#define SUNXI_CLK_FACTOR_CPU_MAX_FREQ   (1200000000U)
#define SUNXI_CLK_FACTOR_DDR_MAX_FREQ   (2160000000U)
#define SUNXI_CLK_FACTOR_VIDEO_MAX_FREQ   (630000000U)
#define SUNXI_CLK_FACTOR_PERI0_MAX_FREQ (636000000U)

/********************************************************************************/
/* CCMU Register List */
#define CCU_REG_BASE         (0x03001000)
#define CLK_PLL_CPU          (volatile uint32_t *)(CCU_REG_BASE + 0x0000)
#define CLK_PLL_DDR          (volatile uint32_t *)(CCU_REG_BASE + 0x0010)
#define CLK_PLL_PERIPH0      (volatile uint32_t *)(CCU_REG_BASE + 0x0020)
#define CLK_PLL_PERIPH1      (volatile uint32_t *)(CCU_REG_BASE + 0x0028)
#define CLK_PLL_VIDEO0       (volatile uint32_t *)(CCU_REG_BASE + 0x0040)
#define CLK_PLL_AUDIO        (volatile uint32_t *)(CCU_REG_BASE + 0x0078)
#define CLK_PLL_CSI          (volatile uint32_t *)(CCU_REG_BASE + 0x00E0)


#define CLK_PLL_DDRPAT       (volatile uint32_t *)(CCU_REG_BASE + 0x0110)
#define CLK_PLL_PERI0PAT0    (volatile uint32_t *)(CCU_REG_BASE + 0x0120)
#define CLK_PLL_PERI0PAT1    (volatile uint32_t *)(CCU_REG_BASE + 0x0124)
#define CLK_PLL_PERI1PAT0    (volatile uint32_t *)(CCU_REG_BASE + 0x0128)
#define CLK_PLL_PERI1PAT1    (volatile uint32_t *)(CCU_REG_BASE + 0x012C)
#define CLK_PLL_VIDEO0PAT0   (volatile uint32_t *)(CCU_REG_BASE + 0x0140)
#define CLK_PLL_VIDEO0PAT1   (volatile uint32_t *)(CCU_REG_BASE + 0x0144)
#define CLK_PLL_VIDEO1PAT0   (volatile uint32_t *)(CCU_REG_BASE + 0x0148)
#define CLK_PLL_VIDEO1PAT1   (volatile uint32_t *)(CCU_REG_BASE + 0x014C)
#define CLK_PLL_DEPAT0       (volatile uint32_t *)(CCU_REG_BASE + 0x0160)
#define CLK_PLL_AUDIOPAT0    (volatile uint32_t *)(CCU_REG_BASE + 0x0178)
#define CLK_PLL_AUDIOPAT1    (volatile uint32_t *)(CCU_REG_BASE + 0x017C)
#define CLK_PLL_CSIPAT0      (volatile uint32_t *)(CCU_REG_BASE + 0x01E0)
#define CLK_PLL_CSIPAT1      (volatile uint32_t *)(CCU_REG_BASE + 0x01E4)

#define CLK_CPU_CFG          (volatile uint32_t *)(CCU_REG_BASE + 0x0500)
#define CLK_PSI_CFG          (volatile uint32_t *)(CCU_REG_BASE + 0x0510)
#define CLK_AHB3_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x051C)
#define CLK_APB1_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0520)
#define CLK_APB2_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0524)

/* Accelerator */
#define CLK_MBUS_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0540)
#define CLK_DE_CFG           (volatile uint32_t *)(CCU_REG_BASE + 0x0600)
#define CLK_DE_GATE          (volatile uint32_t *)(CCU_REG_BASE + 0x060C)
#define CLK_G2D_CFG          (volatile uint32_t *)(CCU_REG_BASE + 0x0630)
#define CLK_G2D_GATE         (volatile uint32_t *)(CCU_REG_BASE + 0x063C)
#define CLK_CE_CFG           (volatile uint32_t *)(CCU_REG_BASE + 0x0680)
#define CLK_CE_GATE          (volatile uint32_t *)(CCU_REG_BASE + 0x068C)
#define CLK_VE_CFG           (volatile uint32_t *)(CCU_REG_BASE + 0x0690)
#define CLK_VE_GATE          (volatile uint32_t *)(CCU_REG_BASE + 0x069C)
#define CLK_EISE_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x06D0)
#define CLK_EISE_GATE        (volatile uint32_t *)(CCU_REG_BASE + 0x06DC)
#define CLK_NNA_CFG          (volatile uint32_t *)(CCU_REG_BASE + 0x06E0)
#define CLK_NNA_GATE         (volatile uint32_t *)(CCU_REG_BASE + 0x06EC)

/* SYS Resource */
#define CLK_DMA_GATE         (volatile uint32_t *)(CCU_REG_BASE + 0x070C)
#define CLK_HSTIMER_GATE     (volatile uint32_t *)(CCU_REG_BASE + 0x073C)
#define CLK_AVS_CFG          (volatile uint32_t *)(CCU_REG_BASE + 0x0740)
#define CLK_DBGSYS_GATE      (volatile uint32_t *)(CCU_REG_BASE + 0x078C)
#define CLK_PSI_GATE         (volatile uint32_t *)(CCU_REG_BASE + 0x079C)
#define CLK_PWM_GATE         (volatile uint32_t *)(CCU_REG_BASE + 0x07AC)
#define CLK_IOMMU_GATE       (volatile uint32_t *)(CCU_REG_BASE + 0x07BC)

/* Storage Medium */
#define CLK_DRAM_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0800)
#define CLK_MBUS_GATE        (volatile uint32_t *)(CCU_REG_BASE + 0x0804)
#define CLK_DRAM_GATE        (volatile uint32_t *)(CCU_REG_BASE + 0x080C)
#define CLK_NAND0_CFG        (volatile uint32_t *)(CCU_REG_BASE + 0x0810)
//#define CLK_NAND1_CFG        (volatile uint32_t *)(CCU_REG_BASE + 0x0814)
//#define CLK_NAND_GATE        (volatile uint32_t *)(CCU_REG_BASE + 0x082C)
#define CLK_SMHC0_CFG        (volatile uint32_t *)(CCU_REG_BASE + 0x0830)
#define CLK_SMHC1_CFG        (volatile uint32_t *)(CCU_REG_BASE + 0x0834)
#define CLK_SMHC2_CFG        (volatile uint32_t *)(CCU_REG_BASE + 0x0838)
#define CLK_SMHC_GATE        (volatile uint32_t *)(CCU_REG_BASE + 0x084C)

/* Common Interface */
#define CLK_UART_GATE        (volatile uint32_t *)(CCU_REG_BASE + 0x090C)
#define CLK_TWI_GATE         (volatile uint32_t *)(CCU_REG_BASE + 0x091C)
//#define CLK_SCR_GATE         (volatile uint32_t *)(CCU_REG_BASE + 0x093C)
#define CLK_SPI0_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0940)
#define CLK_SPI1_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0944)
#define CLK_SPI2_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0948)
#define CLK_SPI_GATE         (volatile uint32_t *)(CCU_REG_BASE + 0x096C)
#define CLK_EPHY25M_CFG      (volatile uint32_t *)(CCU_REG_BASE + 0x0970)
#define CLK_GMAC_GATE        (volatile uint32_t *)(CCU_REG_BASE + 0x097C)
#define CLK_GPADC_GATE       (volatile uint32_t *)(CCU_REG_BASE + 0x09EC)
#define CLK_THS_GATE         (volatile uint32_t *)(CCU_REG_BASE + 0x09FC)
#define CLK_I2S0_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0A10)
#define CLK_I2S1_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0A14)
//#define CLK_I2S2_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0A18)
#define CLK_I2S_GATE         (volatile uint32_t *)(CCU_REG_BASE + 0x0A1C)
//#define CLK_SPDIF_CFG        (volatile uint32_t *)(CCU_REG_BASE + 0x0A20)
//#define CLK_SPDIF_GATE       (volatile uint32_t *)(CCU_REG_BASE + 0x0A2C)
//#define CLK_DMIC_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0A40)
//#define CLK_DMIC_GATE        (volatile uint32_t *)(CCU_REG_BASE + 0x0A4C)
#define CLK_CODEC_1X_CFG     (volatile uint32_t *)(CCU_REG_BASE + 0x0A50)
#define CLK_CODEC_4X_CFG     (volatile uint32_t *)(CCU_REG_BASE + 0x0A54)
#define CLK_CODEC_GATE       (volatile uint32_t *)(CCU_REG_BASE + 0x0A5C)
#define CLK_USB0_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0A70)
//#define CLK_USB1_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0A74)
#define CLK_USB_GATE         (volatile uint32_t *)(CCU_REG_BASE + 0x0A8C)
//#define CLK_MAD_GATE         (volatile uint32_t *)(CCU_REG_BASE + 0x0ACC)
//#define CLK_LPSD_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0AD0)
//#define CLK_LPSD_GATE        (volatile uint32_t *)(CCU_REG_BASE + 0x0ADC)
#define CLK_MIPI_DPHY0_CFG      (volatile uint32_t *)(CCU_REG_BASE + 0x0B20)
#define CLK_MIPI_HOST0_CFG      (volatile uint32_t *)(CCU_REG_BASE + 0x0B24)
#define CLK_MIPI_GATE           (volatile uint32_t *)(CCU_REG_BASE + 0x0B4C)
#define CLK_DISPLAY_TOP_GATE    (volatile uint32_t *)(CCU_REG_BASE + 0x0B5C)
#define CLK_TCON_LCD_CFG        (volatile uint32_t *)(CCU_REG_BASE + 0x0B60)
#define CLK_TCON_LCD_GATE       (volatile uint32_t *)(CCU_REG_BASE + 0x0B7C)
#define CLK_CSI_TOP_CFG         (volatile uint32_t *)(CCU_REG_BASE + 0x0C04)
#define CLK_CSI_MASTER0_CFG     (volatile uint32_t *)(CCU_REG_BASE + 0x0C08)
#define CLK_CSI_MASTER1_CFG     (volatile uint32_t *)(CCU_REG_BASE + 0x0C0C)
#define CLK_CSI_MASTER2_CFG     (volatile uint32_t *)(CCU_REG_BASE + 0x0C10)
#define CLK_CSI_MASTER3_CFG     (volatile uint32_t *)(CCU_REG_BASE + 0x0C14)
#define CLK_ISP_CFG             (volatile uint32_t *)(CCU_REG_BASE + 0x0C20)
#define CLK_CSI_GATE            (volatile uint32_t *)(CCU_REG_BASE + 0x0C2C)
/*
#define VDPO_CFG            (volatile uint32_t *)(CCU_REG_BASE + 0x0C50)
#define VDPO_GATE           (volatile uint32_t *)(CCU_REG_BASE + 0x0C5C)
*/
#define CLK_DSPO_CFG            (volatile uint32_t *)(CCU_REG_BASE + 0x0C60)
#define CLK_DSPO_GATE           (volatile uint32_t *)(CCU_REG_BASE + 0x0C6C)

#endif /* __SUN8IW19P1_CLK_H__ */
