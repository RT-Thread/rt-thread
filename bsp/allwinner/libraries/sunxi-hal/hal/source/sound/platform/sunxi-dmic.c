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
#include <hal_timer.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sound/snd_core.h>
#include <sound/snd_pcm.h>
#include <sound/snd_dma.h>
#include <sound/dma_wrap.h>
#include <hal_dma.h>
#include <hal_cmd.h>

#include "sunxi-pcm.h"
#include "sunxi-dmic.h"

static const struct dmic_rate dmic_rate_s[] = {
    {44100, 0x0},
    {48000, 0x0},
    {22050, 0x2},
    /* KNOT support */
    {24000, 0x2},
    {11025, 0x4},
    {12000, 0x4},
    {32000, 0x1},
    {16000, 0x3},
    {8000, 0x5},
};

/*
 * Configure DMA , Chan enable & Global enable
 */
static void sunxi_dmic_enable(struct snd_platform *platform, bool enable)
{
    struct sunxi_dmic_info *sunxi_dmic = platform->private_data;

    snd_print("\n");
    if (enable) {
        snd_platform_update_bits(platform, SUNXI_DMIC_INTC,
                (0x1 << FIFO_DRQ_EN), (0x1 << FIFO_DRQ_EN));

        snd_platform_update_bits(platform, SUNXI_DMIC_EN,
                (0xFF<<DATA_CH_EN),
                ((sunxi_dmic->chanmap)<<DATA_CH_EN));

        snd_platform_update_bits(platform, SUNXI_DMIC_EN,
                (0x1 << GLOBE_EN), (0x1 << GLOBE_EN));
    } else {
        snd_platform_update_bits(platform, SUNXI_DMIC_EN,
                (0x1 << GLOBE_EN), (0x0 << GLOBE_EN));
        snd_platform_update_bits(platform, SUNXI_DMIC_EN,
                (0xFF << DATA_CH_EN),
                (0x0 << DATA_CH_EN));
        snd_platform_update_bits(platform, SUNXI_DMIC_INTC,
                (0x1 << FIFO_DRQ_EN),
                (0x0 << FIFO_DRQ_EN));
    }
}

static void sunxi_dmic_init(struct snd_platform *platform)
{
    snd_print("\n");
    snd_platform_write(platform,
            SUNXI_DMIC_CH_MAP, DMIC_CHANMAP_DEFAULT);
    snd_platform_update_bits(platform, SUNXI_DMIC_CTR,
            (0x7<<DMICDFEN), (0x7<<DMICDFEN));

    /* set the vol */
    snd_platform_write(platform, SUNXI_DMIC_DATA0_1_VOL, DMIC_DEFAULT_VOL);
    snd_platform_write(platform, SUNXI_DMIC_DATA2_3_VOL, DMIC_DEFAULT_VOL);
}

static int sunxi_dmic_hw_params(struct snd_pcm_substream *substream,
        struct snd_pcm_hw_params *params, struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;
    struct sunxi_dmic_info *sunxi_dmic = platform->private_data;
    int i;

    snd_print("\n");
    /* if clk rst */
    sunxi_dmic_init(platform);

    /* sample resolution & sample fifo format */
    switch (params_format(params)) {
    case SNDRV_PCM_FORMAT_S16_LE:
        snd_platform_update_bits(platform, SUNXI_DMIC_FIFO_CTR,
                (0x1 << DMIC_SAMPLE_RESOLUTION),
                (0x0 << DMIC_SAMPLE_RESOLUTION));
        snd_platform_update_bits(platform, SUNXI_DMIC_FIFO_CTR,
                (0x1 << DMIC_FIFO_MODE),
                (0x1 << DMIC_FIFO_MODE));
        break;
    case SNDRV_PCM_FORMAT_S24_LE:
        snd_platform_update_bits(platform, SUNXI_DMIC_FIFO_CTR,
                (0x1 << DMIC_SAMPLE_RESOLUTION),
                (0x1 << DMIC_SAMPLE_RESOLUTION));
        snd_platform_update_bits(platform, SUNXI_DMIC_FIFO_CTR,
                (0x1 << DMIC_FIFO_MODE),
                (0x0 << DMIC_FIFO_MODE));
        break;
    default:
        snd_err( "Invalid format set\n");
        return -EINVAL;
    }

    for (i = 0; i < ARRAY_SIZE(dmic_rate_s); i++) {
        if (dmic_rate_s[i].samplerate == params_rate(params)) {
            snd_platform_update_bits(platform, SUNXI_DMIC_SR,
            (7<<DMIC_SR), (dmic_rate_s[i].rate_bit<<DMIC_SR));
            break;
        }
    }

    /* oversamplerate adjust */
    if (params_rate(params) >= 24000) {
        snd_platform_update_bits(platform, SUNXI_DMIC_CTR,
            (1<<DMIC_OVERSAMPLE_RATE), (1<<DMIC_OVERSAMPLE_RATE));
    } else {
        snd_platform_update_bits(platform, SUNXI_DMIC_CTR,
            (1<<DMIC_OVERSAMPLE_RATE), (0<<DMIC_OVERSAMPLE_RATE));
    }

    sunxi_dmic->chanmap = (1<<params_channels(params)) - 1;

    snd_platform_write(platform, SUNXI_DMIC_HPF_CTRL, sunxi_dmic->chanmap);

    /* DMIC num is M+1 */
    snd_platform_update_bits(platform, SUNXI_DMIC_CH_NUM,
        (7<<DMIC_CH_NUM), ((params_channels(params)-1)<<DMIC_CH_NUM));

    return 0;
}

static int sunxi_dmic_trigger(struct snd_pcm_substream *substream,
                int cmd, struct snd_dai *dai)
{
    int ret = 0;
    struct snd_platform *platform = dai->component;

    snd_print("\n");
    switch (cmd) {
    case    SNDRV_PCM_TRIGGER_START:
    case    SNDRV_PCM_TRIGGER_RESUME:
    case    SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
        sunxi_dmic_enable(platform, true);
        break;
    case    SNDRV_PCM_TRIGGER_STOP:
    case    SNDRV_PCM_TRIGGER_SUSPEND:
    case    SNDRV_PCM_TRIGGER_PAUSE_PUSH:
        sunxi_dmic_enable(platform, false);
        break;
    default:
        ret = -EINVAL;
        break;
    }

    return ret;
}

/*
 * Reset & Flush FIFO
 */
static int sunxi_dmic_prepare(struct snd_pcm_substream *substream,
            struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;

    snd_print("\n");
    snd_platform_update_bits(platform, SUNXI_DMIC_FIFO_CTR,
            (1<<DMIC_FIFO_FLUSH), (1<<DMIC_FIFO_FLUSH));

    snd_platform_write(platform, SUNXI_DMIC_INTS,
        (1<<FIFO_OVERRUN_IRQ_PENDING) | (1<<FIFO_DATA_IRQ_PENDING));

    snd_platform_write(platform, SUNXI_DMIC_CNT, 0x0);

    return 0;
}

static int sunxi_dmic_startup(struct snd_pcm_substream *substream,
            struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;
    struct sunxi_dmic_info *sunxi_dmic = platform->private_data;

    snd_print("\n");
    dai->capture_dma_data = &sunxi_dmic->capture_dma_param;

    return 0;
}

static void sunxi_dmic_shutdown(struct snd_pcm_substream *substream,
            struct snd_dai *dai)
{
    snd_print("\n");
}

static int sunxi_dmic_set_sysclk(struct snd_dai *dai, int clk_id,
                        unsigned int freq, int dir)
{
    struct snd_platform *platform = dai->component;
    struct sunxi_dmic_info *sunxi_dmic = platform->private_data;

    snd_print("\n");
    if (hal_clk_set_rate(sunxi_dmic->pllclk, freq)) {
        snd_err("set pllclk %u failed\n", freq);
        return -EINVAL;
    }

    return 0;
}

/* Dmic module init status */
static int sunxi_dmic_dai_probe(struct snd_dai *dai)
{
    struct snd_platform *platform = dai->component;

    snd_print("\n");
    dai->capture_dma_data = 0;
    sunxi_dmic_init(platform);

    return 0;
}

static struct snd_dai_ops sunxi_dmic_dai_ops = {
    .startup = sunxi_dmic_startup,
    .trigger = sunxi_dmic_trigger,
    .prepare = sunxi_dmic_prepare,
    .hw_params = sunxi_dmic_hw_params,
    .set_sysclk = sunxi_dmic_set_sysclk,
    .shutdown = sunxi_dmic_shutdown,
};

static struct snd_dai sunxi_dmic_dai = {
    .id     = 1,
    .name       = "sunxi-dmic-cpudai",
    .capture    = {
        .stream_name    = "Capture",
        .channels_min   = 1,
        .channels_max   = 8,
        .rates      = SUNXI_DMIC_RATES,
        .formats    = SNDRV_PCM_FMTBIT_S16_LE
                | SNDRV_PCM_FMTBIT_S24_LE
                | SNDRV_PCM_FMTBIT_S32_LE,
        .rate_min   = 8000,
        .rate_max   = 48000,
    },
    .probe      = sunxi_dmic_dai_probe,
    .ops        = &sunxi_dmic_dai_ops,
};

static int sunxi_dmic_clk_init(struct snd_platform *platform)
{
    struct sunxi_dmic_info *sunxi_dmic = platform->private_data;
    hal_reset_type_t reset_type = HAL_SUNXI_RESET;
    hal_clk_type_t clk_type = HAL_SUNXI_CCU;
    int ret;

    snd_print("\n");
    sunxi_dmic->pllclk = hal_clock_get(clk_type, SUNXI_DMIC_CLK_PLL_AUDIO);
    sunxi_dmic->moduleclk = hal_clock_get(clk_type, SUNXI_DMIC_CLK_DMIC);
    sunxi_dmic->busclk = hal_clock_get(clk_type, SUNXI_DMIC_CLK_BUS);
    sunxi_dmic->rstclk = hal_reset_control_get(reset_type, SUNXI_DMIC_CLK_RST);

    ret = hal_clk_set_parent(sunxi_dmic->moduleclk, sunxi_dmic->pllclk);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("sunxi_dmic clk_set_parent failed.\n");
        goto err_dmic_moduleclk_set_parent;
    }

    ret = hal_reset_control_deassert(sunxi_dmic->rstclk);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("dmic clk_deassert rstclk failed.\n");
        goto err_dmic_rstclk_deassert;
    }

    ret = hal_clock_enable(sunxi_dmic->busclk);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("dmic clk_enable busclk failed.\n");
        goto err_dmic_busclk_enable;
    }
    ret = hal_clock_enable(sunxi_dmic->pllclk);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("dmic clk_enable pllclk failed.\n");
        goto err_dmic_pllclk_enable;
    }
    ret = hal_clock_enable(sunxi_dmic->moduleclk);
    if (ret != HAL_CLK_STATUS_OK) {
        snd_err("dmic clk_enable moduleclk failed.\n");
        goto err_dmic_moduleclk_enable;
    }

    return 0;

err_dmic_moduleclk_enable:
    hal_clock_disable(sunxi_dmic->pllclk);
err_dmic_pllclk_enable:
err_dmic_busclk_enable:
err_dmic_rstclk_deassert:
err_dmic_moduleclk_set_parent:
    snd_free(sunxi_dmic);
    return ret;
}

static int sunxi_dmic_gpio_init(bool enable)
{
    snd_print("\n");
    if (enable) {
        /*CLK*/
        hal_gpio_pinmux_set_function(g_dmic_gpio.clk.gpio,
                    g_dmic_gpio.clk.mux);
        /*DATA0*/
        hal_gpio_pinmux_set_function(g_dmic_gpio.din0.gpio,
                    g_dmic_gpio.din0.mux);
        /*DATA1*/
        hal_gpio_pinmux_set_function(g_dmic_gpio.din1.gpio,
                    g_dmic_gpio.din1.mux);
        /*DATA2*/
        hal_gpio_pinmux_set_function(g_dmic_gpio.din2.gpio,
                    g_dmic_gpio.din2.mux);
        /*DATA3*/
        hal_gpio_pinmux_set_function(g_dmic_gpio.din3.gpio,
                    g_dmic_gpio.din3.mux);
    } else {
        /*CLK*/
        hal_gpio_pinmux_set_function(g_dmic_gpio.clk.gpio,
                    GPIO_MUXSEL_DISABLED);
        /*DATA0*/
        hal_gpio_pinmux_set_function(g_dmic_gpio.din0.gpio,
                    GPIO_MUXSEL_DISABLED);
        /*DATA1*/
        hal_gpio_pinmux_set_function(g_dmic_gpio.din1.gpio,
                    GPIO_MUXSEL_DISABLED);
        /*DATA2*/
        hal_gpio_pinmux_set_function(g_dmic_gpio.din2.gpio,
                    GPIO_MUXSEL_DISABLED);
        /*DATA3*/
        hal_gpio_pinmux_set_function(g_dmic_gpio.din3.gpio,
                    GPIO_MUXSEL_DISABLED);
    }

    return 0;
}

static int sunxi_dmic_platform_probe(struct snd_platform *platform)
{
    struct sunxi_dmic_info *sunxi_dmic;

    snd_print("\n");
    sunxi_dmic = snd_malloc(sizeof(struct sunxi_dmic_info));
    if (!sunxi_dmic) {
        snd_err("no memory\n");
        return -ENOMEM;
    }
    platform->private_data = (void *)sunxi_dmic;
    platform->cpu_dai->component = platform;

    /* mem base */
    platform->mem_base = (void *)SUNXI_DMIC_MEMBASE;

    /* clk */
    sunxi_dmic_clk_init(platform);

    /* pinctrl */
    sunxi_dmic_gpio_init(true);

    /* dma config */
    sunxi_dmic->capture_dma_param.src_maxburst = 8;
    sunxi_dmic->capture_dma_param.dst_maxburst = 8;
    sunxi_dmic->capture_dma_param.dma_addr =
            (dma_addr_t)platform->mem_base + SUNXI_DMIC_DATA;
    sunxi_dmic->capture_dma_param.dma_drq_type_num = DRQSRC_DMIC;

    return 0;
}

static int sunxi_dmic_platform_remove(struct snd_platform *platform)
{
    struct sunxi_dmic_info *sunxi_dmic;

    snd_print("\n");
    sunxi_dmic = platform->private_data;
    if (!sunxi_dmic)
        return 0;

    hal_clock_disable(sunxi_dmic->busclk);
    hal_clock_disable(sunxi_dmic->moduleclk);
    hal_clock_disable(sunxi_dmic->pllclk);
    hal_clock_put(sunxi_dmic->busclk);
    hal_clock_put(sunxi_dmic->moduleclk);
    hal_clock_put(sunxi_dmic->pllclk);

    hal_reset_control_assert(sunxi_dmic->rstclk);
    hal_reset_control_put(sunxi_dmic->rstclk);

    sunxi_dmic_gpio_init(false);

    snd_free(sunxi_dmic);
    platform->private_data = NULL;

    return 0;
}

int snd_platform_dmic_register(struct snd_platform *platform, int unused)
{
    int ret;

    snd_print("\n");
    platform->name = snd_malloc(DMIC_NAME_LEN);
    if (!platform->name) {
        snd_err("no memory\n");
        return -ENOMEM;
    }
    snprintf(platform->name, DMIC_NAME_LEN, "dmic-cpudai");
    platform->ops = &sunxi_pcm_ops;
    platform->pcm_new = sunxi_pcm_new;
    platform->pcm_free = sunxi_pcm_free;

    platform->cpu_dai = snd_malloc(sizeof(struct snd_dai));
    if (!platform->cpu_dai) {
        snd_err("cpu_dai malloc failed.\n");
        ret = -ENOMEM;
        goto err_cpu_dai_malloc;
    }
    memcpy(platform->cpu_dai, &sunxi_dmic_dai, sizeof(struct snd_dai));

    platform->probe = sunxi_dmic_platform_probe;
    platform->remove = sunxi_dmic_platform_remove;

    return 0;

err_cpu_dai_malloc:
    snd_free(platform->name);
    platform->name = NULL;
    return ret;
}

#ifdef SUNXI_DMIC_DEBUG_REG
#define REG_LABEL(constant)     {#constant, constant}
#define REG_LABEL_END           {NULL, 0}
static struct dmic_label {
    const char *name;
    const unsigned int address;
    /*int value;*/
} reg_labels[] = {
    REG_LABEL(SUNXI_DMIC_EN),
    REG_LABEL(SUNXI_DMIC_SR),
    REG_LABEL(SUNXI_DMIC_CTR),
    REG_LABEL(SUNXI_DMIC_INTC),
    REG_LABEL(SUNXI_DMIC_INTS),
    REG_LABEL(SUNXI_DMIC_FIFO_CTR),
    REG_LABEL(SUNXI_DMIC_FIFO_STA),
    REG_LABEL(SUNXI_DMIC_CH_NUM),
    REG_LABEL(SUNXI_DMIC_CH_MAP),
    REG_LABEL(SUNXI_DMIC_CNT),
    REG_LABEL(SUNXI_DMIC_DATA0_1_VOL),
    REG_LABEL(SUNXI_DMIC_DATA2_3_VOL),
    REG_LABEL(SUNXI_DMIC_HPF_CTRL),
    REG_LABEL(SUNXI_DMIC_HPF_COEF),
    REG_LABEL(SUNXI_DMIC_HPF_GAIN),
    REG_LABEL_END,
};

/* for debug */
#include <console.h>
int cmd_dmic_dump(void)
{
    int dmic_num = 0;
    void *membase;
    int i = 0;

    membase = (void *)SUNXI_DMIC_MEMBASE ;

    while (reg_labels[i].name != NULL) {
        printf("%-20s[0x%03x]: 0x%-10x\n",
            reg_labels[i].name,
            reg_labels[i].address,
            snd_readl(membase + reg_labels[i].address));
        i++;
    }
}
FINSH_FUNCTION_EXPORT_CMD(cmd_dmic_dump, dmic, dmic dump reg);
#endif /* SUNXI_DMIC_DEBUG_REG */
