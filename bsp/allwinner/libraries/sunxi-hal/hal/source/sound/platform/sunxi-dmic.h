/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
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
#ifndef __SUNXI_DMIC_H_
#define __SUNXI_DMIC_H_

#include <aw_common.h>
#include <hal_clk.h>
#include <hal_reset.h>
#include <hal_gpio.h>
#include <sound/snd_core.h>
#include <sound/snd_pcm.h>
#include <sound/snd_io.h>

#define DMIC_NAME_LEN       (16)

/*------------------DMIC register definition--------------------*/
#define SUNXI_DMIC_EN           0x00
#define SUNXI_DMIC_SR           0x04
#define SUNXI_DMIC_CTR          0x08
#define SUNXI_DMIC_DATA         0x10
#define SUNXI_DMIC_INTC         0x14
#define SUNXI_DMIC_INTS         0x18
#define SUNXI_DMIC_FIFO_CTR     0x1c
#define SUNXI_DMIC_FIFO_STA     0x20
#define SUNXI_DMIC_CH_NUM       0x24
#define SUNXI_DMIC_CH_MAP       0x28
#define SUNXI_DMIC_CNT          0x2c
#define SUNXI_DMIC_DATA0_1_VOL      0x30
#define SUNXI_DMIC_DATA2_3_VOL      0x34
#define SUNXI_DMIC_HPF_CTRL     0x38
#define SUNXI_DMIC_HPF_COEF     0x3C
#define SUNXI_DMIC_HPF_GAIN     0x40
#define SUNXI_DMIC_REV          0x50

/*0x00:SUNXI_DMIC_EN*/
#define GLOBE_EN            8
#define DATA3_CHR_EN            7
#define DATA3_CHL_EN            6
#define DATA2_CHR_EN            5
#define DATA2_CHL_EN            4
#define DATA1_CHR_EN            3
#define DATA1_CHL_EN            2
#define DATA0_CHR_EN            1
#define DATA0_CHL_EN            0
#define DATA_CH_EN          0

/*SUNXI_DMIC_SR:0x04*/
#define DMIC_SR             0

/*SUNXI_DMIC_CTR:0x08*/
#define DMICFDT             9
#define DMICDFEN            8
#define DATA3_LR_SWEEP_EN       7
#define DATA2_LR_SWEEP_EN       6
#define DATA1_LR_SWEEP_EN       5
#define DATA0_LR_SWEEP_EN       4
#define DMIC_OVERSAMPLE_RATE        0

/*SUNXI_DMIC_DATA:0x10*/
#define DMIC_DATA           0

/*SUNXI_DMIC_INTC:0x14*/
#define FIFO_DRQ_EN         2
#define FIFO_OVERRUN_IRQ_EN     1
#define DATA_IRQ_EN         0

/*SUNXI_DMIC_INTS:0x18*/
#define FIFO_OVERRUN_IRQ_PENDING    1
#define FIFO_DATA_IRQ_PENDING       0

/*SUNXI_DMIC_FIFO_CTR:0x1c*/
#define DMIC_FIFO_FLUSH         31
#define DMIC_FIFO_MODE          9
#define DMIC_SAMPLE_RESOLUTION      8
#define FIFO_TRG_LEVEL          0

/*SUNXI_DMIC_FIFO_STA:0x20*/
#define DMIC_DATA_CNT           0

/*SUNXI_DMIC_CH_NUM:0x24*/
#define DMIC_CH_NUM         0

/*SUNXI_DMIC_CH_MAP:0x28*/
#define DMIC_CH7_MAP            28
#define DMIC_CH6_MAP            24
#define DMIC_CH5_MAP            20
#define DMIC_CH4_MAP            16
#define DMIC_CH3_MAP            12
#define DMIC_CH2_MAP            8
#define DMIC_CH1_MAP            4
#define DMIC_CH0_MAP            0
#define DMIC_CHANMAP_DEFAULT        (0x76543210)
/*SUNXI_DMIC_CNT:0x2c*/
#define DMIC_CNT            0

/*SUNXI_DMIC_DATA0_1_VOL:0x30*/
#define DATA1L_VOL          24
#define DATA1R_VOL          16
#define DATA0L_VOL          8
#define DATA0R_VOL          0

/*SUNXI_DMIC_DATA2_3_VOL:0x34*/
#define DATA3L_VOL          24
#define DATA3R_VOL          16
#define DATA2L_VOL          8
#define DATA2R_VOL          0
#define DMIC_DEFAULT_VOL        0xB0B0B0B0

/*SUNXI_DMIC_HPF_EN_CTR:0x38*/
#define HPF_DATA3_CHR_EN        7
#define HPF_DATA3_CHL_EN        6
#define HPF_DATA2_CHR_EN        5
#define HPF_DATA2_CHL_EN        4
#define HPF_DATA1_CHR_EN        3
#define HPF_DATA1_CHL_EN        2
#define HPF_DATA0_CHR_EN        1
#define HPF_DATA0_CHL_EN        0

/*SUNXI_DMIC_HPF_COEF:0x3C*/
#define HPF_COEF            0

/*SUNXI_DMIC_HPF_GAIN:0x40*/
#define HPF_GAIN            0

#define SUNXI_DMIC_RATES (SNDRV_PCM_RATE_8000_48000 | SNDRV_PCM_RATE_KNOT)

typedef struct {
    gpio_pin_t gpio;
    unsigned int mux;
} dmic_gpio;

typedef struct {
    dmic_gpio clk;
    dmic_gpio din0;
    dmic_gpio din1;
    dmic_gpio din2;
    dmic_gpio din3;
} dmic_gpio_t;

struct dmic_rate {
    unsigned int samplerate;
    unsigned int rate_bit;
};

struct sunxi_dmic_info {
    struct sunxi_dma_params capture_dma_param;
    u32 chanmap;
    hal_clk_t pllclk;
    hal_clk_t moduleclk;
    hal_clk_t busclk;
    struct reset_control *rstclk;
};

/* aw1851 */
#ifdef CONFIG_ARCH_SUN8IW18P1
#include "platforms/dmic-sun8iw18.h"
#endif
/* aw1859 */
#ifdef CONFIG_ARCH_SUN8IW20
#include "platforms/dmic-sun8iw20.h"
#endif

#endif /* SUNXI_DMIC_H */
