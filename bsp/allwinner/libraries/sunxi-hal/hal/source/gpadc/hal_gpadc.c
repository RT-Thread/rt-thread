/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.

 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.

 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PARTY¡¯S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNERS¡¯SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY¡¯S TECHNOLOGY.


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
#include <hal_interrupt.h>
#include <hal_clk.h>
#include <sunxi_hal_gpadc.h>
#include <hal_reset.h>

hal_gpadc_t hal_gpadc;

#if defined(CONFIG_SOC_SUN20IW1)
static hal_gpadc_status_t hal_gpadc_clk_init(hal_gpadc_t *gpadc)
{
    hal_clk_type_t clk_type = HAL_SUNXI_CCU;
    hal_clk_id_t gpadc_clk_id = gpadc->bus_clk;
    hal_clk_t mclk;

    hal_reset_type_t reset_type = HAL_SUNXI_RESET;
    hal_reset_id_t gpadc_reset_id = gpadc->rst_clk;
    struct reset_control *reset;

    mclk = hal_clock_get(clk_type, gpadc_clk_id);
    if(hal_clock_enable(mclk))
    {
        GPADC_ERR("gpadc clk enable failed!\n");
        return GPADC_ERROR;
    }
    gpadc->mbus_clk = mclk;

    reset = hal_reset_control_get(reset_type, gpadc_reset_id);
    if (hal_reset_control_deassert(reset))
    {
        GPADC_ERR("gpadc reset deassert failed!\n");
        return GPADC_ERROR;
    }
    hal_reset_control_put(reset);
    return GPADC_OK;
}
#else
static hal_gpadc_status_t hal_gpadc_clk_init(hal_gpadc_t *gpadc)
{
#if !defined(CONFIG_ARCH_SUN8IW18P1)
    if (hal_clk_set_parent(gpadc->mclk, gpadc->pclk))
    {
        GPADC_ERR("[gpadc] clk set parent failed!");
        return GPADC_ERROR;
    }
#endif
    if (hal_clock_enable(gpadc->mclk))
    {
        GPADC_ERR("[gpadc] clk enable mclk failed!");
        return GPADC_ERROR;
    }

    return GPADC_OK;
}
#endif

static int gpadc_channel_check_valid(hal_gpadc_channel_t channal)
{
    hal_gpadc_t *gpadc = &hal_gpadc;

    return channal < gpadc->channel_num ? 0 : -1 ;
}

static void gpadc_channel_select(hal_gpadc_channel_t channal)
{
    uint32_t reg_val;
    hal_gpadc_t *gpadc = &hal_gpadc;

    reg_val = readl((unsigned long)(gpadc->reg_base) + GP_CS_EN_REG);
    reg_val |= (0x01 << channal);
    writel(reg_val, (unsigned long)(gpadc->reg_base) + GP_CS_EN_REG);

}

static void gpadc_channel_deselect(hal_gpadc_channel_t channal)
{
    uint32_t reg_val;
    hal_gpadc_t *gpadc = &hal_gpadc;

    reg_val = readl((unsigned long)(gpadc->reg_base) + GP_CS_EN_REG);
    reg_val &= ~(0x01 << channal);
    writel(reg_val, (unsigned long)(gpadc->reg_base) + GP_CS_EN_REG);

}

static void gpadc_compare_select(hal_gpadc_channel_t channal)
{
    uint32_t reg_val;
    hal_gpadc_t *gpadc = &hal_gpadc;

    reg_val = readl((unsigned long)(gpadc->reg_base) + GP_CS_EN_REG);
    reg_val |= (GP_CH0_CMP_EN << channal);
    writel(reg_val, (unsigned long)(gpadc->reg_base) + GP_CS_EN_REG);

}

static void gpadc_compare_deselect(hal_gpadc_channel_t channal)
{
    uint32_t reg_val;
    hal_gpadc_t *gpadc = &hal_gpadc;

    reg_val = readl((unsigned long)(gpadc->reg_base) + GP_CTRL_REG);
    reg_val &= ~(GP_CH0_CMP_EN << channal);
    writel(reg_val, (unsigned long)(gpadc->reg_base) + GP_CTRL_REG);

}

static void gpadc_channel_enable_lowirq(hal_gpadc_channel_t channal)
{
    uint32_t reg_val;
    hal_gpadc_t *gpadc = &hal_gpadc;

    reg_val = readl((unsigned long)(gpadc->reg_base) + GP_DATAL_INTC_REG);
    reg_val |= (0x01 << channal);
    writel(reg_val, (unsigned long)(gpadc->reg_base) + GP_DATAL_INTC_REG);
}

static void gpadc_channel_disable_lowirq(hal_gpadc_channel_t channal)
{
    uint32_t reg_val;
    hal_gpadc_t *gpadc = &hal_gpadc;

    reg_val = readl((unsigned long)(gpadc->reg_base) + GP_DATAL_INTC_REG);
    reg_val &= ~(0x01 << channal);
    writel(reg_val, (unsigned long)(gpadc->reg_base) + GP_DATAL_INTC_REG);
}

static void gpadc_channel_compare_lowdata(hal_gpadc_channel_t channal,
        uint32_t low_uv)
{
    uint32_t reg_val = 0, low = 0, unit = 0;
    hal_gpadc_t *gpadc = &hal_gpadc;

    /* analog voltage range 0~1.8v, 12bits sample rate, unit=1.8v/(2^12) */
    unit = VOL_RANGE / 4096; /* 12bits sample rate */
    low = low_uv / unit;
    if (low > VOL_VALUE_MASK)
    {
        low = VOL_VALUE_MASK;
    }

    reg_val = readl((unsigned long)(gpadc->reg_base) + GP_CH0_CMP_DATA_REG + 4 * channal);
    reg_val &= ~VOL_VALUE_MASK;
    reg_val |= (low & VOL_VALUE_MASK);
    writel(reg_val, (unsigned long)(gpadc->reg_base) + GP_CH0_CMP_DATA_REG + 4 * channal);

}

static void gpadc_channel_enable_highirq(hal_gpadc_channel_t channal)
{
    uint32_t reg_val;
    hal_gpadc_t *gpadc = &hal_gpadc;

    reg_val = readl((unsigned long)(gpadc->reg_base) + GP_DATAH_INTC_REG);
    reg_val |= (1 << channal);
    writel(reg_val, (unsigned long)(gpadc->reg_base) + GP_DATAH_INTC_REG);

}

static void gpadc_channel_disable_highirq(hal_gpadc_channel_t channal)
{
    uint32_t reg_val;
    hal_gpadc_t *gpadc = &hal_gpadc;

    reg_val = readl((unsigned long)(gpadc->reg_base) + GP_DATAH_INTC_REG);
    reg_val &= ~(1 << channal);
    writel(reg_val, (unsigned long)(gpadc->reg_base) + GP_DATAH_INTC_REG);

}

static void gpadc_channel_compare_highdata(hal_gpadc_channel_t channal,
        uint32_t hig_uv)
{
    uint32_t reg_val = 0, hig_val = 0, unit_val = 0;
    hal_gpadc_t *gpadc = &hal_gpadc;

    /* anolog voltage range 0~1.8v, 12bits sample rate, unit=1.8v/(2^12) */
    unit_val = VOL_RANGE / 4096; /* 12bits sample rate */
    hig_val = hig_uv / unit_val;

    if (hig_val > VOL_VALUE_MASK)
    {
        hig_val = VOL_VALUE_MASK;
    }

    reg_val = readl((unsigned long)(gpadc->reg_base) + GP_CH0_CMP_DATA_REG + 4 * channal);
    reg_val &= ~(VOL_VALUE_MASK << 16);
    reg_val |= (hig_val & VOL_VALUE_MASK) << 16;
    writel(reg_val, (unsigned long)(gpadc->reg_base) + GP_CH0_CMP_DATA_REG + 4 * channal);

}

/* clk_in: source clock, round_clk: sample rate */
static void gpadc_sample_rate_set(uint32_t reg_base, uint32_t clk_in,
                                  uint32_t round_clk)
{
    uint32_t div, reg_val;
    if (round_clk > clk_in)
    {
        GPADC_ERR("invalid round clk!");
    }
    div = clk_in / round_clk - 1 ;
    reg_val = readl((unsigned long)(reg_base) + GP_SR_REG);
    reg_val &= ~GP_SR_CON;
    reg_val |= (div << 16);
    writel(reg_val, (unsigned long)(reg_base) + GP_SR_REG);
}

static void gpadc_calibration_enable(uint32_t reg_base)
{
    uint32_t reg_val;
    reg_val = readl((unsigned long)(reg_base) + GP_CTRL_REG);
    reg_val |= GP_CALI_EN;
    writel(reg_val, (unsigned long)(reg_base) + GP_CTRL_REG);
}

static void gpadc_mode_select(uint32_t reg_base,
                              enum gp_select_mode mode)
{
    uint32_t reg_val;

    reg_val = readl((unsigned long)(reg_base) + GP_CTRL_REG);
    reg_val &= ~GP_MODE_SELECT;
    reg_val |= (mode << 18);
    writel(reg_val, (unsigned long)(reg_base) + GP_CTRL_REG);
}

/* enable gpadc function, true:enable, false:disable */
static void gpadc_enable(uint32_t reg_base)
{
    uint32_t reg_val = 0;

    reg_val = readl((unsigned long)(reg_base) + GP_CTRL_REG);
    reg_val |= GP_ADC_EN;
    writel(reg_val, (unsigned long)(reg_base) + GP_CTRL_REG);
}

/* enable gpadc function, true:enable, false:disable */
static void gpadc_disable(uint32_t reg_base)
{
    uint32_t reg_val = 0;

    reg_val = readl((unsigned long)(reg_base) + GP_CTRL_REG);
    reg_val &= ~GP_ADC_EN;
    writel(reg_val, (unsigned long)(reg_base) + GP_CTRL_REG);
}

static uint32_t gpadc_read_channel_irq_enable(uint32_t reg_base)
{
    return readl((unsigned long)(reg_base) + GP_DATA_INTC_REG);
}

static uint32_t gpadc_read_channel_lowirq_enable(uint32_t reg_base)
{
    return readl((unsigned long)(reg_base) + GP_DATAL_INTC_REG);
}

static uint32_t gpadc_read_channel_highirq_enable(uint32_t reg_base)
{
    return readl((unsigned long)(reg_base) + GP_DATAH_INTC_REG);
}

static uint32_t gpadc_channel_irq_status(uint32_t reg_base)
{
    return readl((unsigned long)(reg_base) + GP_DATA_INTS_REG);
}

static void gpadc_channel_clear_irq(uint32_t reg_base, uint32_t flags)
{
    writel(flags, (unsigned long)(reg_base) + GP_DATA_INTS_REG);
}

static uint32_t gpadc_channel_lowirq_status(uint32_t reg_base)
{
    return readl((unsigned long)(reg_base) + GP_DATAL_INTS_REG);
}

static void gpadc_channel_clear_lowirq(uint32_t reg_base, uint32_t flags)
{
    writel(flags, (unsigned long)(reg_base) + GP_DATAL_INTS_REG);
}

static uint32_t gpadc_channel_highirq_status(uint32_t reg_base)
{
    return readl((unsigned long)(reg_base) + GP_DATAH_INTS_REG);
}

static void gpadc_channel_clear_highirq(uint32_t reg_base, uint32_t flags)
{
    writel(flags, (unsigned long)(reg_base) + GP_DATAH_INTS_REG);
}

static int gpadc_read_data(uint32_t reg_base, hal_gpadc_channel_t channal)
{
    return readl((unsigned long)(reg_base) + GP_CH0_DATA_REG + 4 * channal) & GP_CH_DATA_MASK;
}

int hal_gpadc_callback(uint32_t data_type, uint32_t data)
{
    GPADC_INFO("gpadc interrupt, data_type is %ld", data_type);
    return 0;
}

static irqreturn_t gpadc_handler(int irq, void *dev)
{
    hal_gpadc_t *gpadc = (hal_gpadc_t *)dev;

    uint32_t reg_val, reg_low, reg_high;
    uint32_t reg_enable, reg_enable_low, reg_enable_high;
    uint32_t i, data = 0;

    reg_enable = gpadc_read_channel_irq_enable(gpadc->reg_base);
    reg_enable_low = gpadc_read_channel_lowirq_enable(gpadc->reg_base);
    reg_enable_high = gpadc_read_channel_highirq_enable(gpadc->reg_base);

    reg_val = gpadc_channel_irq_status(gpadc->reg_base);
    gpadc_channel_clear_irq(gpadc->reg_base, reg_val);
    reg_low = gpadc_channel_lowirq_status(gpadc->reg_base);
    gpadc_channel_clear_lowirq(gpadc->reg_base, reg_val);
    reg_high = gpadc_channel_highirq_status(gpadc->reg_base);
    gpadc_channel_clear_highirq(gpadc->reg_base, reg_val);

    for (i = 0; i < gpadc->channel_num; i++)
    {
        if (reg_low & (1 << i) & reg_enable_low)
        {
            data = gpadc_read_data(gpadc->reg_base, i);
            gpadc_channel_enable_highirq(i);

            if (gpadc->callback[i])
            {
                gpadc->callback[i](GPADC_DOWN, data);
            }
        }

        if (reg_high & (1 << i) & reg_enable_high)
        {
            gpadc_channel_disable_highirq(i);
            gpadc->callback[i](GPADC_UP, data);
        }
    }

    return 0;
}

hal_gpadc_status_t hal_gpadc_register_callback(hal_gpadc_channel_t channal,
        gpadc_callback_t user_callback)
{
    hal_gpadc_t *gpadc = &hal_gpadc;

    if (gpadc_channel_check_valid(channal))
    {
        return GPADC_CHANNEL_ERROR;
    }

    if (user_callback == NULL)
    {
        return GPADC_ERROR;
    }

    gpadc->callback[channal] = user_callback;

    return GPADC_OK;
}

hal_gpadc_status_t hal_gpadc_channel_init(hal_gpadc_channel_t channal)
{
    hal_gpadc_t *gpadc = &hal_gpadc;

    if (gpadc_channel_check_valid(channal))
    {
        return GPADC_CHANNEL_ERROR;
    }

    gpadc_channel_select(channal);
    gpadc_compare_select(channal);
    gpadc_channel_enable_lowirq(channal);
    gpadc_channel_compare_lowdata(channal, COMPARE_LOWDATA);
    gpadc_channel_compare_highdata(channal, COMPARE_HIGDATA);

    return GPADC_OK;
}

hal_gpadc_status_t hal_gpadc_channel_exit(hal_gpadc_channel_t channal)
{
    hal_gpadc_t *gpadc = &hal_gpadc;

    if (gpadc_channel_check_valid(channal))
    {
        return GPADC_CHANNEL_ERROR;
    }

    gpadc_channel_deselect(channal);
    gpadc_compare_deselect(channal);
    gpadc_channel_disable_lowirq(channal);

    return GPADC_OK;
}

static void hal_gpadc_setup(hal_gpadc_t *gpadc)
{
    uint8_t i;

    gpadc->reg_base = GPADC_BASE;
    gpadc->channel_num = CHANNEL_NUM;
    gpadc->irq_num = SUNXI_GPADC_IRQ;
    gpadc->sample_rate = DEFAULT_SR;
#if defined(CONFIG_SOC_SUN20IW1)
    gpadc->bus_clk = CLK_BUS_GPADC;
    gpadc->rst_clk = RST_BUS_GPADC;
#else
    gpadc->pclk = HAL_CLK_SRC_HOSC24M;
    gpadc->mclk = HAL_CLK_PERIPH_GPADC;
#endif
    gpadc->mode = GP_CONTINUOUS_MODE;

    for (i = 0; i < gpadc->channel_num; i++)
    {
        gpadc->callback[i] = hal_gpadc_callback;
    }
};

int hal_gpadc_init(void)
{
    hal_gpadc_t *gpadc = &hal_gpadc;


    hal_gpadc_setup(gpadc);

    if (hal_gpadc_clk_init(gpadc))
    {
        GPADC_ERR("gpadc init clk error");
        return GPADC_CLK_ERROR;
    }

    GPADC_INFO("gpadc set sample rate");
    gpadc_sample_rate_set(gpadc->reg_base, OSC_24MHZ, gpadc->sample_rate);

    if (request_irq(gpadc->irq_num, gpadc_handler, IRQF_NO_SUSPEND, "gpadc", gpadc))
    {
        return GPADC_IRQ_ERROR;
    }

    enable_irq(gpadc->irq_num);

    GPADC_INFO("gpadc enable calibration");
    gpadc_calibration_enable(gpadc->reg_base);
    gpadc_mode_select(gpadc->reg_base, gpadc->mode);
    gpadc_enable(gpadc->reg_base);

    return GPADC_OK;
}

hal_gpadc_status_t hal_gpadc_deinit(void)
{
    disable_irq(hal_gpadc.irq_num);
#if defined(CONFIG_SOC_SUN20IW1)
    hal_clock_disable(hal_gpadc.mbus_clk);
#else
    hal_clock_disable(hal_gpadc.mclk);
#endif
    return GPADC_OK;
}

//device_initcall(hal_gpadc_init);
