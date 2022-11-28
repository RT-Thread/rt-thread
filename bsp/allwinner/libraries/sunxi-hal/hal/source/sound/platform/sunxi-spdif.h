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
#ifndef __SUNXI_SPDIF_H_
#define __SUNXI_SPDIF_H_

#include <aw_common.h>
#include <hal_clk.h>
#include <hal_reset.h>
#include <hal_gpio.h>
#include <sound/snd_core.h>
#include <sound/snd_pcm.h>
#include <sound/snd_io.h>

/*#define SUNXI_SPDIF_DEBUG_REG*/

#define SPDIF_NAME_LEN      (16)

/*------------------SPDIF register definition--------------------*/
#define SUNXI_SPDIF_CTL     0x00
#define SUNXI_SPDIF_TXCFG   0x04
#define SUNXI_SPDIF_RXCFG   0x08
#define SUNXI_SPDIF_INT_STA (0x0C)
#define SUNXI_SPDIF_RXFIFO  0x10
#define SUNXI_SPDIF_FIFO_CTL    0x14
#define SUNXI_SPDIF_FIFO_STA    0x18
#define SUNXI_SPDIF_INT     0x1C
#define SUNXI_SPDIF_TXFIFO  (0x20)
#define SUNXI_SPDIF_TXCNT   0x24
#define SUNXI_SPDIF_RXCNT   0x28
#define SUNXI_SPDIF_TXCH_STA0   0x2C
#define SUNXI_SPDIF_TXCH_STA1   0x30
#define SUNXI_SPDIF_RXCH_STA0   0x34
#define SUNXI_SPDIF_RXCH_STA1   0x38

/* SUNXI_SPDIF_CTL register */
#define CTL_RESET       0
#define CTL_GEN_EN      1
#define CTL_LOOP_EN     2
#define CTL_RESET_RX        0

/* SUNXI_SPDIF_TXCFG register */
#define TXCFG_TXEN      0
/* Chan status generated form TX_CHSTA */
#define TXCFG_CHAN_STA_EN   1
#define TXCFG_SAMPLE_BIT    2
#define TXCFG_CLK_DIV_RATIO 4
#define TXCFG_DATA_TYPE     16
/* Only valid in PCM mode */
#define TXCFG_ASS       17
#define TXCFG_SINGLE_MOD    31

/* SUNXI_SPDIF_RXCFG register */
#define RXCFG_RXEN      0
#define RXCFG_CHSR_CP       1
#define RXCFG_CHST_SRC      3
#define RXCFG_LOCK_FLAG     4

/* SUNXI_SPDIF_FIFO_CTL register */
#define FIFO_CTL_RXOM       0
#define FIFO_CTL_TXIM       2
#define FIFO_CTL_RXTL       4
#define FIFO_CTL_TXTL       12
#define FIFO_CTL_FRX        29
#define FIFO_CTL_FTX        30
#define FIFO_CTL_HUBEN      31
#define CTL_TXTL_MASK       0xFF
#define CTL_TXTL_DEFAULT    0x40
#define CTL_RXTL_MASK       0x7F
#define CTL_RXTL_DEFAULT    0x20

/* SUNXI_SPDIF_FIFO_STA register */
#define FIFO_STA_RXA_CNT    0
#define FIFO_STA_RXA        15
#define FIFO_STA_TXA_CNT    16
#define FIFO_STA_TXE        31

/* SUNXI_SPDIF_INT register */
#define INT_RXAIEN      0
#define INT_RXOIEN      1
#define INT_RXDRQEN     2
#define INT_TXEIEN      4
#define INT_TXOIEN      5
#define INT_TXUIEN      6
#define INT_TXDRQEN     7
#define INT_RXPAREN     16
#define INT_RXUNLOCKEN      17
#define INT_RXLOCKEN        18

/* SUNXI_SPDIF_INT_STA  */
#define INT_STA_RXA     0
#define INT_STA_RXO     1
#define INT_STA_TXE     4
#define INT_STA_TXO     5
#define INT_STA_TXU     6
#define INT_STA_RXPAR       16
#define INT_STA_RXUNLOCK    17
#define INT_STA_RXLOCK      18

/* SUNXI_SPDIF_TXCH_STA0 register */
#define TXCHSTA0_PRO        0
#define TXCHSTA0_AUDIO      1
#define TXCHSTA0_CP     2
#define TXCHSTA0_EMPHASIS   3
#define TXCHSTA0_MODE       6
#define TXCHSTA0_CATACOD    8
#define TXCHSTA0_SRCNUM     16
#define TXCHSTA0_CHNUM      20
#define TXCHSTA0_SAMFREQ    24
#define TXCHSTA0_CLK        28

/* SUNXI_SPDIF_TXCH_STA1 register */
#define TXCHSTA1_MAXWORDLEN 0
#define TXCHSTA1_SAMWORDLEN 1
#define TXCHSTA1_ORISAMFREQ 4
#define TXCHSTA1_CGMSA      8

/* SUNXI_SPDIF_RXCH_STA0 register */
#define RXCHSTA0_PRO        0
#define RXCHSTA0_AUDIO      1
#define RXCHSTA0_CP     2
#define RXCHSTA0_EMPHASIS   3
#define RXCHSTA0_MODE       6
#define RXCHSTA0_CATACOD    8
#define RXCHSTA0_SRCNUM     16
#define RXCHSTA0_CHNUM      20
#define RXCHSTA0_SAMFREQ    24
#define RXCHSTA0_CLK        28

/* SUNXI_SPDIF_RXCH_STA1 register */
#define RXCHSTA1_MAXWORDLEN 0
#define RXCHSTA1_SAMWORDLEN 1
#define RXCHSTA1_ORISAMFREQ 4
#define RXCHSTA1_CGMSA      8

#define SUNXI_SPDIF_RATES (SNDRV_PCM_RATE_8000_192000 | SNDRV_PCM_RATE_KNOT)

typedef struct {
    gpio_pin_t gpio;
    unsigned int mux;
} spdif_gpio;

typedef struct {
//  spdif_gpio clk;
    spdif_gpio out;
    spdif_gpio in;
} spdif_gpio_t;

struct spdif_rate {
    unsigned int samplerate;
    unsigned int rate_bit;
};

struct sunxi_spdif_info {
    struct sunxi_dma_params playback_dma_param;
    struct sunxi_dma_params capture_dma_param;
    hal_clk_t pllclk;
    hal_clk_t moduleclk;
    hal_clk_t busclk;
    struct reset_control *rstclk;
    hal_clk_t pllclk1;
    hal_clk_t pllclk1_div;
    hal_clk_t moduleclk_rx;
};

/* aw1859 */
#ifdef CONFIG_ARCH_SUN8IW20
#include "platforms/spdif-sun8iw20.h"
#endif

#endif /* __SUNXI_SPDIF_H_ */
