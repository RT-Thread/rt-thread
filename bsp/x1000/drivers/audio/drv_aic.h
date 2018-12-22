/*
 * File      : drv_i2s.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 */



#ifndef _DRV_I2S_H_
#define _DRV_I2S_H_

/*********************************************************************************************************
**   头文件
*********************************************************************************************************/
#include "x1000.h"

#include "drv_clock.h"
#include "drv_dma.h"

/*********************************************************************************************************
**   CODEC 配置
*********************************************************************************************************/
#define JZ_I2S_USE_INNER_CODEC
#undef  JZ_I2S_USE_EX_CODEC


/*********************************************************************************************************
**   AIC 数据结构
*********************************************************************************************************/
enum aic_mode {
    AIC_NO_MODE = 0,
    AIC_I2S_MODE,
    AIC_SPDIF_MODE,
    AIC_AC97_MODE
};

struct jz_aic_device;
struct jz_aic
{
    struct rt_device parent;
    uint32_t   base;

    struct clk  *clk;
    struct clk  *clk_gate;

    uint32_t    clk_rate;

    /* for interrupt */
    int         irqno;
    int         irqflags;
    uint32_t    ror;       /*counter for debug*/
    uint32_t    tur;
    uint32_t    mask;

    /* for AIC work mode protect */
    enum aic_mode   aic_working_mode;

    /* for sub device */
    uint32_t    dma_addr;

    struct jz_aic_device    *aic_dev;
};

struct jz_aic_device
{
    struct rt_device parent;
};


/*********************************************************************************************************
**   AIC 指令
*********************************************************************************************************/
#define AIC_CMD_SET_MODE        0x20
#define AIC_CMD_SET_RATE        0x21
#define AIC_CMD_SET_SUBDEV      0x22

/*********************************************************************************************************
**   AIC 寄存器操作
***********************************************************************************************************/
static void inline jz_aic_write_reg(struct jz_aic *aic,uint32_t reg, uint32_t val)
{
    writel(val, aic->base + reg);
}

static uint32_t inline jz_aic_read_reg(struct jz_aic *aic,uint32_t reg)
{
    return readl(aic->base + reg);
}


/* For AC97 and I2S */
#define AICFR		(0x00)
#define AICCR		(0x04)
#define ACCR1		(0x08)
#define ACCR2		(0x0c)
#define I2SCR		(0x10)
#define AICSR		(0x14)
#define ACSR		(0x18)
#define I2SSR		(0x1c)
#define ACCAR		(0x20)
#define ACCDR		(0x24)
#define ACSAR		(0x28)
#define ACSDR		(0x2c)
#define I2SDIV		(0x30)
#define AICDR		(0x34)

/* For SPDIF */
#define SPENA		(0x80)
#define SPCTRL		(0x84)
#define SPSTATE		(0x88)
#define SPCFG1		(0x8c)
#define SPCFG2		(0x90)
#define SPFIFO		(0x94)

#define I2S_CPM_VALID 0xb0000070
/* For AICFR */
#define AICFR_ENB_BIT		(0)
#define AICFR_ENB_MASK		(1 << AICFR_ENB_BIT)
#define AICFR_SYNCD_BIT		(1)
#define AICFR_SYNCD_MASK	(1 << AICFR_SYNCD_BIT)
#define AICFR_BCKD_BIT		(2)
#define AICFR_BCKD_MASK		(1 << AICFR_BCKD_BIT)
#define AICFR_RST_BIT		(3)
#define AICFR_RST_MASK		(1 << AICFR_RST_BIT)
#define AICFR_AUSEL_BIT		(4)
#define AICFR_AUSEL_MASK	(1 << AICFR_AUSEL_BIT)
#define AICFR_ICDC_BIT		(5)
#define AICFR_ICDC_MASK		(1 << AICFR_ICDC_BIT)
#define AICFR_LSMP_BIT		(6)
#define AICFR_LSMP_MASK		(1 << AICFR_LSMP_BIT)
#define AICFR_CDC_SLV_BIT	(7)
#define AICFR_CDC_SLV_MASK	(1 << AICFR_CDC_SLV_BIT)
#define AICFR_DMODE_BIT		(8)
#define AICFR_DMODE_MASK	(1 << AICFR_DMODE_BIT)
#define	AICFR_ISYNCD_BIT	(9)
#define	AICFR_ISYNCD_MASK	(1 << AICFR_ISYNCD_BIT)
#define AICFR_IBCKD_BIT		(10)
#define AICFR_IBCKD_MASK	(1 << AICFR_IBCKD_BIT)
#define AICFR_SYSCLKD_BIT	(11)
#define AICFR_SYSCLKD_MASK	(1 << AICFR_SYSCLKD_BIT)
#define AICFR_MSB_BIT		(12)
#define AICFR_MSB_MASK		(1 << AICFR_MSB_BIT)
#define AICFR_TFTH_BIT		(16)
#define AICFR_TFTH_MASK		(0x1f << AICFR_TFTH_BIT)
#define AICFR_RFTH_BIT		(24)
#define AICFR_RFTH_MASK		(0x1f << AICFR_RFTH_BIT)

/* For AICCR */
#define AICCR_EREC_BIT		(0)
#define AICCR_EREC_MASK		(1 << AICCR_EREC_BIT)
#define AICCR_ERPL_BIT		(1)
#define AICCR_ERPL_MASK		(1 << AICCR_ERPL_BIT)
#define AICCR_ENLBF_BIT		(2)
#define AICCR_ENLBF_MASK	(1 << AICCR_ENLBF_BIT)
#define	AICCR_ETFS_BIT		(3)
#define	AICCR_ETFS_MASK		(1 << AICCR_ETFS_BIT)
#define AICCR_ERFS_BIT		(4)
#define AICCR_ERFS_MASK		(1 << AICCR_ERFS_BIT)
#define AICCR_ETUR_BIT		(5)
#define AICCR_ETUR_MASK		(1 << AICCR_ETUR_BIT)
#define AICCR_EROR_BIT		(6)
#define AICCR_EROR_MASK		(1 << AICCR_EROR_BIT)
#define AICCR_EALL_INT_MASK	(AICCR_EROR_MASK|AICCR_ETUR_MASK|AICCR_ERFS_MASK|AICCR_ETFS_MASK)
#define AICCR_RFLUSH_BIT	(7)
#define AICCR_RFLUSH_MASK	(1 << AICCR_RFLUSH_BIT)
#define AICCR_TFLUSH_BIT	(8)
#define AICCR_TFLUSH_MASK	(1 << AICCR_TFLUSH_BIT)
#define AICCR_ASVTSU_BIT	(9)
#define AICCR_ASVTSU_MASK	(1 << AICCR_ASVTSU_BIT)
#define AICCR_ENDSW_BIT		(10)
#define AICCR_ENDSW_MASK	(1 << AICCR_ENDSW_BIT)
#define AICCR_M2S_BIT		(11)
#define AICCR_M2S_MASK		(1 << AICCR_M2S_BIT)
#define AICCR_TDMS_BIT		(14)
#define AICCR_TDMS_MASK		(1 << AICCR_TDMS_BIT)
#define AICCR_RDMS_BIT		(15)
#define AICCR_RDMS_MASK		(1 << AICCR_RDMS_BIT)
#define AICCR_ISS_BIT		(16)
#define AICCR_ISS_MASK		(0x7 << AICCR_ISS_BIT)
#define AICCR_OSS_BIT		(19)
#define AICCR_OSS_MASK		(0x7 << AICCR_OSS_BIT)
#define AICCR_CHANNEL_BIT	(24)
#define AICCR_CHANNEL_MASK	(0x7 << AICCR_CHANNEL_BIT)
#define AICCR_PACK16_BIT	(28)
#define AICCR_PACK16_MASK	(1 << AICCR_PACK16_BIT)

/* For ACCR1 */
#define	ACCR1_XS_BIT		(0)
#define ACCR1_XS_MASK		(0x3ff << ACCR1_XS_BIT)
#define	ACCR1_RS_BIT		(16)
#define ACCR1_RS_MASK		(0x3ff << ACCR1_RS_BIT)

/* For ACCR2 */
#define	ACCR2_SA_BIT		(0)
#define	ACCR2_SA_MASK		(1 << ACCR2_SA_BIT)
#define	ACCR2_SS_BIT		(1)
#define	ACCR2_SS_MASK		(1 << ACCR2_SS_BIT)
#define	ACCR2_SR_BIT		(2)
#define	ACCR2_SR_MASK		(1 << ACCR2_SR_BIT)
#define	ACCR2_SO_BIT		(3)
#define	ACCR2_SO_MASK		(1 << ACCR2_SO_BIT)
#define	ACCR2_ECADT_BIT		(16)
#define	ACCR2_ECADT_MASK	(1 << ACCR2_ECADT_BIT)
#define	ACCR2_ECADR_BIT		(17)
#define	ACCR2_ECADR_MASK	(1 << ACCR2_ECADR_BIT)
#define	ACCR2_ERSTO_BIT		(18)
#define	ACCR2_ERSTO_MASK	(1 << ACCR2_ERSTO_BIT)

/* For I2SCR */
#define	I2SCR_AMSL_BIT		(0)
#define	I2SCR_AMSL_MASK		(1 << I2SCR_AMSL_BIT)
#define	I2SCR_ESCLK_BIT		(4)
#define	I2SCR_ESCLK_MASK	(1 << I2SCR_ESCLK_BIT)
#define	I2SCR_STPBK_BIT		(12)
#define	I2SCR_STPBK_MASK	(1 << I2SCR_STPBK_BIT)
#define	I2SCR_ISTPBK_BIT	(13)
#define	I2SCR_ISTPBK_MASK	(1 << I2SCR_ISTPBK_BIT)
#define	I2SCR_SWLH_BIT		(16)
#define	I2SCR_SWLH_MASK		(1 << I2SCR_SWLH_BIT)
#define	I2SCR_RFIRST_BIT	(17)
#define	I2SCR_RFIRST_MASK	(1 << I2SCR_RFIRST_BIT)

/* For AICSR */
#define AICSR_TFS_BIT		(3)
#define AICSR_TFS_MASK		(1 << AICSR_TFS_BIT)
#define AICSR_RFS_BIT		(4)
#define AICSR_RFS_MASK		(1 << AICSR_RFS_BIT)
#define AICSR_TUR_BIT		(5)
#define AICSR_TUR_MASK		(1 << AICSR_TUR_BIT)
#define AICSR_ROR_BIT		(6)
#define AICSR_ROR_MASK		(1 << AICSR_ROR_BIT)
#define AICSR_ALL_INT_MASK	(AICSR_TFS_MASK|AICSR_RFS_MASK|AICSR_TUR_MASK|AICSR_ROR_MASK)
#define AICSR_TFL_BIT		(8)
#define AICSR_TFL_MASK		(0x3f << AICSR_TFL_BIT)
#define AICSR_RFL_BIT		(24)
#define AICSR_RFL_MASK		(0x3f << AICSR_RFL_BIT)

/* For ACSR */
#define ACSR_CADT_BIT		(16)
#define ACSR_CADT_MASK		(1 << ACSR_CADT_BIT)
#define ACSR_SADR_BIT		(17)
#define ACSR_SADR_MASK		(1 << ACSR_SADR_BIT)
#define ACSR_RSTO_BIT		(18)
#define ACSR_RSTO_MASK		(1 << ACSR_RSTO_BIT)
#define ACSR_CLPM_BIT		(19)
#define ACSR_CLPM_MASK		(1 << ACSR_CLPM_BIT)
#define ACSR_CRDY_BIT		(20)
#define ACSR_CRDY_MASK		(1 << ACSR_CRDY_BIT)
#define ACSR_SLTERR_BIT		(21)
#define ACSR_SLTERR_MASK	(1 << ACSR_SLTERR_BIT)

/* For I2SSR */
#define I2SSR_BSY_BIT		(2)
#define I2SSR_BSY_MASK		(1 << I2SSR_BSY_BIT)
#define I2SSR_RBSY_BIT		(3)
#define I2SSR_RBSY_MASK		(1 << I2SSR_RBSY_BIT)
#define I2SSR_TBSY_BIT		(4)
#define I2SSR_TBSY_MASK		(1 << I2SSR_TBSY_BIT)
#define I2SSR_CHBSY_BIT		(5)
#define I2SSR_CHBSY_MASK	(1 << I2SSR_CHBSY_BIT)

/* For ACCAR */
#define ACCAR_CAR_BIT		(0)
#define ACCAR_CAR_MASK		(0xfffff << ACCAR_CAR_BIT)

/* For ACCDR */
#define ACCDR_CDR_BIT		(0)
#define ACCDR_CDR_MASK		(0xfffff << ACCDR_CDR_BIT)

/* For ACSAR */
#define ACSAR_SAR_BIT		(0)
#define ACSAR_SAR_MASK		(0xfffff << ACSAR_SAR_BIT)

/* For ACSDR */
#define ACSDR_SDR_BIT		(0)
#define ACSDR_SDR_MASK		(0xfffff << ACSDR_SDR_BIT)

/* For I2SDIV */
#define I2SDIV_DV_BIT		(0)
#define I2SDIV_DV_MASK		(0x1ff << I2SDIV_DV_BIT)
#define I2SDIV_IDV_BIT		(16)
#define I2SDIV_IDV_MASK		(0x1ff << I2SDIV_IDV_BIT)

/* For AICDR */
#define AICDR_DATA_BIT		(0)
#define AICDR_DATA_MASK		(0xfffffff << AICDR_DATA_BIT)

/* For SPENA */
#define	SPENA_SPEN_BIT		(0)
#define SPENA_SPEN_MASK		(1 << SPENA_SPEN_BIT)

/* For SPCTRL */
#define SPCTRL_M_FFUR_BIT	(0)
#define SPCTRL_M_FFUR_MASK	(1 << SPCTRL_M_FFUR_BIT)
#define SPCTRL_M_TRIG_BIT	(1)
#define SPCTRL_M_TRIG_MASK	(1 << SPCTRL_M_TRIG_BIT)
#define SPCTRL_SPDIF_I2S_BIT	(10)
#define SPCTRL_SPDIF_I2S_MASK	(1 << SPCTRL_SPDIF_I2S_BIT)
#define SPCTRL_SFT_RST_BIT	(11)
#define SPCTRL_SFT_RST_MASK	(1 << SPCTRL_SFT_RST_BIT)
#define SPCTRL_INVALID_BIT	(12)
#define SPCTRL_INVALID_MASK	(1 << SPCTRL_INVALID_BIT)
#define SPCTRL_SIGN_N_BIT	(13)
#define SPCTRL_SIGN_N_MASK	(1 << SPCTRL_SIGN_N_BIT)
#define SPCTRL_D_TYPE_BIT	(14)
#define SPCTRL_D_TYPE_MASK	(1 << SPCTRL_D_TYPE_BIT)
#define SPCTRL_DMA_EN_BIT	(15)
#define SPCTRL_DMA_EN_MASK	(1 << SPCTRL_DMA_EN_BIT)

/* For SPSTATE */
#define SPSTATE_F_FFUR_BIT	(0)
#define SPSTATE_F_FFUR_MASK	(1 << SPSTATE_F_FFUR_BIT)
#define SPSTATE_F_TRIG_BIT	(1)
#define SPSTATE_F_TRIG_MASK	(1 << SPSTATE_F_TRIG_BIT)
#define SPSTATE_BUSY_BIT	(7)
#define SPSTATE_BUSY_MASK	(1 << SPSTATE_BUSY_BIT)
#define SPSTATE_FIFO_LVL_BIT	(8)
#define SPSTATE_FIFO_LVL_MASK	(0x7f << SPSTATE_FIFO_LVL_BIT)

/* For SPCFG1 */
#define SPCFG1_CH2_NUM_BIT	(0)
#define SPCFG1_CH2_NUM_MASK	(0xf << SPCFG1_CH2_NUM_BIT)
#define SPCFG1_CH1_NUM_BIT	(4)
#define SPCFG1_CH1_NUM_MASK	(0xf << SPCFG1_CH1_NUM_BIT)
#define SPCFG1_SRC_NUM_BIT	(8)
#define SPCFG1_SRC_NUM_MASK	(0xf << SPCFG1_SRC_NUM_BIT)
#define SPCFG1_TRIG_BIT		(12)
#define SPCFG1_TRIG_MASK	(0x3 << SPCFG1_TRIG_BIT)
#define SPCFG1_ZRO_VLD_BIT	(16)
#define SPCFG1_ZRO_VLD_MASK	(1 << SPCFG1_ZRO_VLD_BIT)
#define SPCFG1_INIT_LVL_BIT	(17)
#define SPCFG1_INIT_LVL_MASK	(1 << SPCFG1_INIT_LVL_BIT)

/* For SPCFG2 */
#define SPCFG2_CON_PRO_BIT	(0)
#define SPCFG2_CON_PRO_MASK	(1 << SPCFG2_CON_PRO_BIT)
#define SPCFG2_AUDIO_N_BIT	(1)
#define SPCFG2_AUDIO_N_MASK	(1 << SPCFG2_AUDIO_N_BIT)
#define SPCFG2_COPY_N_BIT	(2)
#define SPCFG2_COPY_N_MASK	(1 << SPCFG2_COPY_N_BIT)
#define SPCFG2_PRE_BIT		(3)
#define SPCFG2_PRE_MASK		(1 << SPCFG2_PRE_BIT)
#define SPCFG2_CH_MD_BIT	(6)
#define SPCFG2_CH_MD_MASK	(0x3 << SPCFG2_CH_MD_BIT)
#define SPCFG2_CAT_CODE_BIT	(8)
#define SPCFG2_CAT_CODE_MASK	(0xff << SPCFG2_CAT_CODE_BIT)
#define SPCFG2_CLK_ACU_BIT	(16)
#define SPCFG2_CLK_ACU_MASK	(0x3 << SPCFG2_CLK_ACU_BIT)
#define SPCFG2_MAX_WL_BIT	(18)
#define SPCFG2_MAX_WL_MASK	(1 << SPCFG2_MAX_WL_BIT)
#define SPCFG2_SAMPL_WL_BIT	(19)
#define SPCFG2_SAMPL_WL_MASK	(0x7 << SPCFG2_SAMPL_WL_BIT)
#define SPCFG2_SAMPL_WL_20BITM	(0x1 << SPCFG2_SAMPL_WL_BIT)
#define SPCFG2_SAMPL_WL_21BIT	(0x6 << SPCFG2_SAMPL_WL_BIT)
#define SPCFG2_SAMPL_WL_22BIT	(0x2 << SPCFG2_SAMPL_WL_BIT)
#define SPCFG2_SAMPL_WL_23BIT	(0x4 << SPCFG2_SAMPL_WL_BIT)
#define SPCFG2_SAMPL_WL_24BIT	(0x5 << SPCFG2_SAMPL_WL_BIT)
#define SPCFG2_SAMPL_WL_16BIT	(0x1 << SPCFG2_SAMPL_WL_BIT)
#define SPCFG2_SAMPL_WL_17BIT	(0x6 << SPCFG2_SAMPL_WL_BIT)
#define SPCFG2_SAMPL_WL_18BIT	(0x2 << SPCFG2_SAMPL_WL_BIT)
#define SPCFG2_SAMPL_WL_19BIT	(0x4 << SPCFG2_SAMPL_WL_BIT)
#define SPCFG2_SAMPL_WL_20BITL	(0x5 << SPCFG2_SAMPL_WL_BIT)
#define SPCFG2_ORG_FRQ_BIT	(22)
#define SPCFG2_ORG_FRQ_MASK	(0xf << SPCFG2_ORG_FRQ_BIT)
#define SPCFG2_FS_BIT		(26)
#define SPCFG2_FS_MASK		(0xf << SPCFG2_FS_BIT)

#define SPFIFO_DATA_BIT		(0)
#define SPFIFO_DATA_MASK	(0xffffff << SPFIFO_DATA_BIT)

#define jz_aic_set_reg(parent, addr, val, mask, offset)		\
	do {							\
		volatile unsigned int reg_tmp;				\
		reg_tmp = jz_aic_read_reg(parent, addr);	\
		reg_tmp &= ~(mask);				\
		reg_tmp |= (val << offset) & mask;		\
		jz_aic_write_reg(parent, addr, reg_tmp);	\
	} while(0)

#define jz_aic_get_reg(parent, addr, mask, offset)	\
	((jz_aic_read_reg(parent, addr) & mask) >> offset)

/*For ALL*/
/*aic fr*/
#define __aic_enable_msb(parent)		\
	jz_aic_set_reg(parent, AICFR, 1, AICFR_MSB_MASK, AICFR_MSB_BIT)
#define __aic_disable_msb(parent)		\
	jz_aic_set_reg(parent, AICFR, 0, AICFR_MSB_MASK, AICFR_MSB_BIT)
#define __aic_reset(parent)	\
	jz_aic_set_reg(parent, AICFR, 1, AICFR_RST_MASK, AICFR_RST_BIT)
/*aic cr*/
#define __aic_flush_rxfifo(parent)	\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_RFLUSH_MASK, AICCR_RFLUSH_BIT)
#define __aic_flush_txfifo(parent)	\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_TFLUSH_MASK, AICCR_TFLUSH_BIT)
#define __aic_en_ror_int(parent)	\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_EROR_MASK, AICCR_EROR_BIT)
#define __aic_dis_ror_int(parent)	\
	jz_aic_set_reg(parent, AICCR, 0, AICCR_EROR_MASK, AICCR_EROR_BIT)
#define __aic_en_tur_int(parent)	\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_ETUR_MASK, AICCR_ETUR_BIT)
#define __aic_dis_tur_int(parent)	\
	jz_aic_set_reg(parent, AICCR, 0, AICCR_ETUR_MASK, AICCR_ETUR_BIT)
#define __aic_en_rfs_int(parent)	\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_ERFS_MASK, AICCR_ERFS_BIT)
#define __aic_dis_rfs_int(parent)	\
	jz_aic_set_reg(parent, AICCR, 0, AICCR_ERFS_MASK, AICCR_ERFS_BIT)
#define __aic_en_tfs_int(parent)	\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_ETFS_MASK, AICCR_ETFS_BIT)
#define __aic_dis_tfs_int(parent)	\
	jz_aic_set_reg(parent, AICCR, 0, AICCR_ETFS_MASK, AICCR_ETFS_BIT)
#define __aic_get_irq_enmask(parent)	\
	jz_aic_get_reg(parent, AICCR, AICCR_EALL_INT_MASK, AICCR_ETFS_BIT)
#define __aic_set_irq_enmask(parent, mask)	\
	jz_aic_set_reg(parent, AICCR, mask, AICCR_EALL_INT_MASK, AICCR_ETFS_BIT)
/*aic sr*/
#define __aic_read_rfl(parent)		\
	jz_aic_get_reg(parent, AICSR ,AICSR_RFL_MASK, AICSR_RFL_BIT)
#define __aic_read_tfl(parent)		\
	jz_aic_get_reg(parent, AICSR, AICSR_TFL_MASK, AICSR_TFL_BIT)
#define __aic_clear_ror(parent)		\
	jz_aic_set_reg(parent, AICSR, 0, AICSR_ROR_MASK, AICSR_ROR_BIT)
#define __aic_test_ror(parent)		\
	jz_aic_get_reg(parent, AICSR, AICSR_ROR_MASK, AICSR_ROR_BIT)
#define __aic_clear_tur(parent)		\
	jz_aic_set_reg(parent, AICSR, 0, AICSR_TUR_MASK, AICSR_TUR_BIT)
#define __aic_test_tur(parent)		\
	jz_aic_get_reg(parent, AICSR, AICSR_TUR_MASK, AICSR_TUR_BIT)
#define __aic_clear_rfs(parent)		\
	jz_aic_set_reg(parent, AICSR, 0, AICSR_RFS_MASK, AICSR_RFS_BIT)
#define __aic_test_rfs(parent)		\
	jz_aic_get_reg(parent, AICSR, AICSR_RFS_MASK, AICSR_RFS_BIT)
#define __aic_clear_tfs(parent)		\
	jz_aic_set_reg(parent, AICSR, 0, AICSR_TFS_MASK, AICSR_TFS_BIT)
#define __aic_test_tfs(parent)		\
	jz_aic_get_reg(parent, AICSR, AICSR_TFS_MASK, AICSR_TFS_BIT)
#define __aic_get_irq_flag(parent)	\
	jz_aic_get_reg(parent, AICSR, AICSR_ALL_INT_MASK, AICSR_TFS_BIT)
#define __aic_clear_all_irq_flag(parent)	\
	jz_aic_set_reg(parent, AICSR, AICSR_ALL_INT_MASK, AICSR_ALL_INT_MASK, AICSR_TFS_BIT)
/* aic dr*/
#define __aic_write_txfifo(parent, n)	\
	jz_aic_write_reg(parent, AICDR, (n))

/* For SPFIFO */
#define __spdif_test_underrun(parent)     \
	jz_aic_get_reg(parent, SPSTATE, SPSTATE_F_FFUR_MASK, SPSTATE_F_FFUR_BIT)
#define __spdif_clear_underrun(parent)     \
	jz_aic_set_reg(parent, SPSTATE, 0, SPSTATE_F_FFUR_MASK, SPSTATE_F_FFUR_BIT)
#define __spdif_is_enable_transmit_dma(parent)    \
	jz_aic_get_reg(parent, SPCTRL, SPCTRL_DMA_EN_MASK, SPCTRL_DMA_EN_BIT)
#define __spdif_enable_transmit_dma(parent)    \
	jz_aic_set_reg(parent, SPCTRL, 1, SPCTRL_DMA_EN_MASK, SPCTRL_DMA_EN_BIT)
#define __spdif_disable_transmit_dma(parent)    \
	jz_aic_set_reg(parent, SPCTRL, 0, SPCTRL_DMA_EN_MASK, SPCTRL_DMA_EN_BIT)
#define __spdif_reset(parent)					\
	jz_aic_set_reg(parent, SPCTRL, 1, SPCTRL_SFT_RST_MASK, SPCTRL_SFT_RST_BIT)
#define __spdif_get_reset(parent)					\
	jz_aic_get_reg(parent, SPCTRL,SPCTRL_SFT_RST_MASK, SPCTRL_SFT_RST_BIT)
#define __spdif_enable(parent)					\
	jz_aic_set_reg(parent, SPENA, 1, SPENA_SPEN_MASK, SPENA_SPEN_BIT)
#define __spdif_disable(parent)					\
	jz_aic_set_reg(parent, SPENA, 0, SPENA_SPEN_MASK, SPENA_SPEN_BIT)
#define __spdif_set_dtype(parent, n)			\
	jz_aic_set_reg(parent, SPCTRL, n, SPCTRL_D_TYPE_MASK, SPCTRL_D_TYPE_BIT)
#define __spdif_set_trigger(parent, n)			\
	jz_aic_set_reg(parent, SPCFG1, n, SPCFG1_TRIG_MASK, SPCFG1_TRIG_BIT)
#define __spdif_set_ch1num(parent, n)		\
	jz_aic_set_reg(parent, SPCFG1, n, SPCFG1_CH1_NUM_MASK, SPCFG1_CH1_NUM_BIT)
#define __spdif_set_ch2num(parent, n)		\
	jz_aic_set_reg(parent, SPCFG1, n, SPCFG1_CH2_NUM_MASK, SPCFG1_CH2_NUM_BIT)
#define __spdif_set_srcnum(parent, n)		\
	jz_aic_set_reg(parent, SPCFG1, n, SPCFG1_SRC_NUM_MASK, SPCFG1_SRC_NUM_BIT)
#define __interface_select_spdif(parent)      \
	jz_aic_set_reg(parent, SPCTRL, 1, SPCTRL_SPDIF_I2S_MASK, SPCTRL_SPDIF_I2S_BIT)
#define __spdif_play_lastsample(parent)        \
	jz_aic_set_reg(parent, SPCFG1, 1, SPCFG1_ZRO_VLD_MASK, SPCFG1_ZRO_VLD_BIT)
#define __spdif_init_set_low(parent)			\
	jz_aic_set_reg(parent, SPCFG1, 0, SPCFG1_INIT_LVL_MASK, SPCFG1_INIT_LVL_BIT)
#define __spdif_choose_consumer(parent)					\
	jz_aic_set_reg(parent, SPCFG2, 0, SPCFG2_CON_PRO_MASK, SPCFG2_CON_PRO_BIT)
#define __spdif_clear_audion(parent)				\
	jz_aic_set_reg(parent, SPCFG2, 0, SPCFG2_AUDIO_N_MASK, SPCFG2_AUDIO_N_BIT)
#define __spdif_set_copyn(parent)					\
	jz_aic_set_reg(parent, SPCFG2, 1, SPCFG2_COPY_N_MASK, SPCFG2_COPY_N_BIT)
#define __spdif_clear_pre(parent)					\
	jz_aic_set_reg(parent, SPCFG2, 0, SPCFG2_PRE_MASK, SPCFG2_PRE_BIT)
#define __spdif_choose_chmd(parent)				\
	jz_aic_set_reg(parent, SPCFG2, 0, SPCFG2_CH_MD_MASK, SPCFG2_CH_MD_BIT)
#define __spdif_set_category_code_normal(parent)	\
	jz_aic_set_reg(parent, SPCFG2, 0, SPCFG2_CAT_CODE_MASK, SPCFG2_CAT_CODE_BIT)
#define __spdif_set_clkacu(parent, n)				\
	jz_aic_set_reg(parent, SPCFG2, n, SPCFG2_CLK_ACU_MASK, SPCFG2_CLK_ACU_BIT)
#define __spdif_set_sample_size(parent, n)		\
	jz_aic_set_reg(parent, SPCFG2, n, SPCFG2_SAMPL_WL_MASK, SPCFG2_SAMPL_WL_BIT)
#define __spdif_set_max_wl(parent, n)                           \
	jz_aic_set_reg(parent, SPCFG2, n, SPCFG2_MAX_WL_MASK, SPCFG2_MAX_WL_BIT)
#define	__spdif_set_ori_sample_freq(parent, org_frq_tmp)	\
	jz_aic_set_reg(parent, SPCFG2, org_frq_tmp, SPCFG2_ORG_FRQ_MASK, SPCFG2_ORG_FRQ_BIT)
#define	__spdif_set_sample_freq(parent, fs_tmp)			\
	jz_aic_set_reg(parent, SPCFG2, fs_tmp, SPCFG2_FS_MASK, SPCFG2_FS_BIT)
#define __spdif_set_valid(parent)				\
	jz_aic_set_reg(parent, SPCTRL, 0, SPCTRL_INVALID_MASK, SPCTRL_INVALID_BIT)
#define __spdif_mask_trig(parent)				\
	jz_aic_set_reg(parent, SPCTRL, 1, SPCTRL_M_TRIG_MASK, SPCTRL_M_TRIG_BIT)
#define __spdif_disable_underrun_intr(parent)  \
	jz_aic_set_reg(parent, SPCTRL, 1, SPCTRL_M_FFUR_MASK, SPCTRL_M_FFUR_BIT)
#define __spdif_set_signn(parent)                             \
	jz_aic_set_reg(parent, SPCTRL, 1, SPCTRL_SIGN_N_MASK, SPCTRL_SIGN_N_BIT)
#define __spdif_clear_signn(parent)                   \
	jz_aic_set_reg(parent, SPCTRL, 0, SPCTRL_SIGN_N_MASK, SPCTRL_SIGN_N_BIT)

/* For I2S */
/*aic fr*/
#define __i2s_is_enable(parent)	\
	jz_aic_get_reg(parent, AICFR, AICFR_ENB_MASK, AICFR_ENB_BIT)
#define __aic_enable(parent)			\
	jz_aic_set_reg(parent, AICFR, 1, AICFR_ENB_MASK, AICFR_ENB_BIT)

#define __aic_disable(parent)			\
	jz_aic_set_reg(parent, AICFR, 0, AICFR_ENB_MASK, AICFR_ENB_BIT)

#define __i2s_external_codec(parent)               \
	jz_aic_set_reg(parent, AICFR, 0, AICFR_ICDC_MASK, AICFR_ICDC_BIT)

#define __i2s_bclk_output(parent)            \
	jz_aic_set_reg(parent, AICFR, 1, AICFR_BCKD_MASK, AICFR_BCKD_BIT)

#define __i2s_bclk_input(parent)            \
	jz_aic_set_reg(parent, AICFR, 0, AICFR_BCKD_MASK, AICFR_BCKD_BIT)

#define __i2s_sync_output(parent)            \
	jz_aic_set_reg(parent, AICFR, 1, AICFR_SYNCD_MASK, AICFR_SYNCD_BIT)

#define __i2s_sync_input(parent)	\
	jz_aic_set_reg(parent, AICFR, 0, AICFR_SYNCD_MASK, AICFR_SYNCD_BIT)

#define __aic_select_i2s(parent)             \
	jz_aic_set_reg(parent, AICFR, 1, AICFR_AUSEL_MASK, AICFR_AUSEL_BIT)

#define __aic_select_internal_codec(parent)	\
	jz_aic_set_reg(parent, AICFR, 1, AICFR_ICDC_MASK, AICFR_ICDC_BIT)

#define __aic_select_external_codec(parent)	\
	jz_aic_set_reg(parent, AICFR, 0, AICFR_ICDC_MASK, AICFR_ICDC_BIT)

#define __i2s_play_zero(parent)              \
	jz_aic_set_reg(parent, AICFR, 0, AICFR_LSMP_MASK, AICFR_LSMP_BIT)

#define __i2s_play_lastsample(parent)        \
	jz_aic_set_reg(parent, AICFR, 1, AICFR_LSMP_MASK, AICFR_LSMP_BIT)

#define __i2s_codec_slave(parent)	\
	jz_aic_set_reg(parent, AICFR, 1, AICFR_CDC_SLV_MASK, AICFR_CDC_SLV_BIT)

#define __i2s_codec_master(parent)	\
	jz_aic_set_reg(parent, AICFR, 0, AICFR_CDC_SLV_MASK, AICFR_CDC_SLV_BIT)

#define __i2s_select_sysclk_output(parent)	\
	jz_aic_set_reg(parent, AICFR, 0, AICFR_SYSCLKD_MASK, AICFR_SYSCLKD_BIT)

#define __i2s_select_sysclk_input(parent)	\
	jz_aic_set_reg(parent, AICFR, 1, AICFR_SYSCLKD_MASK, AICFR_SYSCLKD_BIT)

#define __i2s_set_transmit_trigger(parent, n)  \
	jz_aic_set_reg(parent, AICFR, n, AICFR_TFTH_MASK, AICFR_TFTH_BIT)

#define __i2s_set_receive_trigger(parent, n)   \
	jz_aic_set_reg(parent, AICFR, n, AICFR_RFTH_MASK, AICFR_RFTH_BIT)
/*aiccr*/
#define I2S_SS2REG(n)   (((n) > 18 ? (n)/6 : (n)/9))	/* n = 8, 16, 18, 20, 24 */
#define __i2s_aic_packet16(parent)	\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_PACK16_MASK, AICCR_PACK16_BIT)
#define __i2s_aic_unpacket16(parent)	\
	jz_aic_set_reg(parent, AICCR, 0, AICCR_PACK16_MASK, AICCR_PACK16_BIT)
#define __i2s_channel(parent, n)	\
	jz_aic_set_reg(parent, AICCR, ((n) - 1), AICCR_CHANNEL_MASK, AICCR_CHANNEL_BIT)
#define __i2s_set_oss(parent, n)	\
	jz_aic_set_reg(parent, AICCR, I2S_SS2REG(n) , AICCR_OSS_MASK, AICCR_OSS_BIT)
#define __i2s_set_iss(parent, n)	\
	jz_aic_set_reg(parent, AICCR, I2S_SS2REG(n) , AICCR_ISS_MASK, AICCR_ISS_BIT)
#define __i2s_transmit_dma_is_enable(parent)	\
	jz_aic_get_reg(parent, AICCR, AICCR_TDMS_MASK,AICCR_TDMS_BIT)
#define __i2s_disable_transmit_dma(parent)			\
	jz_aic_set_reg(parent, AICCR, 0, AICCR_TDMS_MASK, AICCR_TDMS_BIT)
#define __i2s_enable_transmit_dma(parent)			\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_TDMS_MASK, AICCR_TDMS_BIT)
#define __i2s_receive_dma_is_enable(parent)	\
	jz_aic_get_reg(parent, AICCR, AICCR_RDMS_MASK,AICCR_RDMS_BIT)
#define __i2s_disable_receive_dma(parent)			\
	jz_aic_set_reg(parent, AICCR, 0, AICCR_RDMS_MASK, AICCR_RDMS_BIT)
#define __i2s_enable_receive_dma(parent)			\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_RDMS_MASK, AICCR_RDMS_BIT)
#define __i2s_m2s_enable(parent)	\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_M2S_MASK, AICCR_M2S_BIT)
#define __i2s_m2s_disable(parent)	\
	jz_aic_set_reg(parent, AICCR, 0, AICCR_M2S_MASK, AICCR_M2S_BIT)
#define __i2s_endsw_enable(parent)	\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_ENDSW_MASK, AICCR_ENDSW_BIT)
#define __i2s_endsw_disable(parent)	\
	jz_aic_set_reg(parent, AICCR, 0, AICCR_ENDSW_MASK, AICCR_ENDSW_BIT)
#define __i2s_asvtsu_enable(parent)	\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_ASVTSU_MASK, AICCR_ASVTSU_BIT)
#define __i2s_asvtsu_disable(parent)	\
	jz_aic_set_reg(parent, AICCR, 0, AICCR_ASVTSU_MASK, AICCR_ASVTSU_BIT)
#define __i2s_enable_replay(parent)				\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_ERPL_MASK, AICCR_ERPL_BIT)
#define __i2s_enable_record(parent)				\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_EREC_MASK, AICCR_EREC_BIT)
#define __i2s_enable_loopback(parent)				\
	jz_aic_set_reg(parent, AICCR, 1, AICCR_ENLBF_MASK, AICCR_ENLBF_BIT)
#define __i2s_disable_replay(parent)				\
	jz_aic_set_reg(parent, AICCR, 0, AICCR_ERPL_MASK, AICCR_ERPL_BIT)
#define __i2s_disable_record(parent)				\
	jz_aic_set_reg(parent, AICCR, 0, AICCR_EREC_MASK, AICCR_EREC_BIT)
#define __i2s_disable_loopback(parent)				\
	jz_aic_set_reg(parent, AICCR, 0, AICCR_ENLBF_MASK, AICCR_ENLBF_BIT)
/*i2scr*/
#define __i2s_select_i2s_fmt(parent)	\
	jz_aic_set_reg(parent, I2SCR, 0, I2SCR_AMSL_MASK, I2SCR_AMSL_BIT)
#define __i2s_select_msb_fmt(parent)	\
	jz_aic_set_reg(parent, I2SCR, 1, I2SCR_AMSL_MASK, I2SCR_AMSL_BIT)
#define __i2s_enable_sysclk_output(parent)   \
	jz_aic_set_reg(parent, I2SCR, 1, I2SCR_ESCLK_MASK, I2SCR_ESCLK_BIT)
#define __i2s_disable_sysclk_output(parent)  \
	jz_aic_set_reg(parent, I2SCR, 0, I2SCR_ESCLK_MASK, I2SCR_ESCLK_BIT)
#define __i2s_stop_bitclk(parent)            \
	jz_aic_set_reg(parent, I2SCR, 1, I2SCR_STPBK_MASK, I2SCR_STPBK_BIT)
#define __i2s_start_bitclk(parent)		\
	jz_aic_set_reg(parent, I2SCR, 0, I2SCR_STPBK_MASK, I2SCR_STPBK_BIT)
#define __i2s_select_packed_lrswap(parent)	\
	jz_aic_set_reg(parent, I2SCR, 1, I2SCR_SWLH_MASK, I2SCR_SWLH_BIT)
#define __i2s_select_packed_lrnorm(parent)	\
	jz_aic_set_reg(parent, I2SCR, 0, I2SCR_SWLH_MASK, I2SCR_SWLH_BIT)
#define __i2s_send_rfirst(parent)	\
	jz_aic_set_reg(parent, I2SCR, 1, I2SCR_RFIRST_MASK, I2SCR_RFIRST_BIT)
#define __i2s_send_lfirst(parent)	\
	jz_aic_set_reg(parent, I2SCR, 0, I2SCR_RFIRST_MASK, I2SCR_RFIRST_BIT)
/*i2ssr*/
#define __i2s_transmiter_is_busy(parent)	\
	(!!(jz_aic_read_reg(parent, I2SSR) & I2SSR_TBSY_MASK))
#define __i2s_receiver_is_busy(parent)	\
	(!!(jz_aic_read_reg(parent, I2SSR) & I2SSR_TBSY_MASK))

/*i2s_div*/
#define __i2s_set_idv(parent, div)	\
	jz_aic_set_reg(parent, I2SDIV, div, I2SDIV_IDV_MASK, I2SDIV_IDV_BIT)
#define __i2s_set_dv(parent, div)	\
	jz_aic_set_reg(parent, I2SDIV, div, I2SDIV_DV_MASK, I2SDIV_DV_BIT)


#endif /* _DRV_I2S_H_ */
