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
#include <stdio.h>
#include <stdlib.h>

#include <interrupt.h>
#include <hal_clk.h>
#include <hal_gpio.h>
#include <hal_reset.h>
#include <hal_cfg.h>
#include <script.h>

#include "common_cir.h"
#include "platform_cir.h"
#include "sunxi_hal_cir.h"

#ifdef CONFIG_DRIVERS_IR_DEBUG
#define CIR_INFO(fmt, arg...) printf("%s()%d " fmt, __func__, __LINE__, ##arg)
#else
#define CIR_INFO(fmt, arg...) do{}while(0);
#endif

#define CIR_ERR(fmt, arg...) printf("%s()%d " fmt, __func__, __LINE__, ##arg)

static uint32_t base[CIR_MASTER_NUM] = {
    SUNXI_IRADC_PBASE,
};

static uint32_t irq[CIR_MASTER_NUM] = {
    SUNXI_IRQ_IRADC,
};

static cir_gpio_t pin[CIR_MASTER_NUM] = {
    {GPIOB(7), 5, 0},
};

sunxi_cir_t sunxi_cir[CIR_MASTER_NUM];

void sunxi_cir_callback_register(cir_port_t port, cir_callback_t callback)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    cir->callback = callback;
}

static irqreturn_t sunxi_cir_handler(int irq, void *dev)
{
    sunxi_cir_t *cir = (sunxi_cir_t *)dev;

    uint32_t int_flag, count;
    uint32_t reg_data, i = 0;

    int_flag = readl(cir->base + CIR_RXSTA);


    writel(int_flag, cir->base + CIR_RXSTA);

    count = (int_flag & RAC) >> RAC_OFFSET;

    for(i = 0; i < count; i++)
    {
        reg_data = readl(cir->base + CIR_RXFIFO);
        if (cir->callback)
            cir->callback(cir->port, RA, reg_data);
    }

    if ((int_flag & ROI) && cir->callback) {
        cir->callback(cir->port, ROI, 0);
    }

    if ((int_flag & RPE) && cir->callback)
    {
        cir->callback(cir->port, RA, 0);
        cir->callback(cir->port, RPE, 0);
    }

    return 0;
}

void sunxi_cir_mode_enable(cir_port_t port, uint8_t enable)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    int reg_val;

    if (!cir->status)
        return ;

    reg_val = readl(cir->base + CIR_CTRL);

    if (enable)
        reg_val |= CIR_ENABLE;
    else
        reg_val &= ~CIR_ENABLE;

    writel(reg_val, cir->base + CIR_CTRL);
}

void sunxi_cir_mode_config(cir_port_t port, cir_mode_t mode)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    int reg_val;

    if (!cir->status)
        return ;

    reg_val = readl(cir->base + CIR_CTRL);

    reg_val &= ~CIR_MODE;
    reg_val |= (mode << CIR_MODE_OFFSET);

    writel(reg_val, cir->base + CIR_CTRL);
}

void sunxi_cir_sample_clock_select(cir_port_t port, cir_sample_clock_t div)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    int reg_val = 0;

    if (!cir->status)
        return ;

    reg_val = readl(cir->base + CIR_CONFIG);

    if (div == CIR_CLK) {
        reg_val &= ~SCS;
        reg_val |= SCS2;
    } else {
        reg_val &= ~SCS2;
        reg_val |= div;
    }

    writel(reg_val, cir->base + CIR_CONFIG);
}

void sunxi_cir_sample_noise_threshold(cir_port_t port, int8_t threshold)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    int reg_val = 0;

    if (!cir->status || threshold > 0x3f)
        return ;

    reg_val = readl(cir->base + CIR_CONFIG);

    reg_val &= ~NTHR;
    reg_val |= (threshold << NTHR_OFFSET);

    writel(reg_val, cir->base + CIR_CONFIG);
}

void sunxi_cir_sample_idle_threshold(cir_port_t port, int8_t threshold)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    int reg_val = 0;

    if (!cir->status || threshold > 0x3f)
        return ;

    reg_val = readl(cir->base + CIR_CONFIG);

    reg_val &= ~ITHR;
    reg_val |= (threshold << ITHR_OFFSET);

    writel(reg_val, cir->base + CIR_CONFIG);
}

void sunxi_cir_sample_active_threshold(cir_port_t port, int8_t threshold)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    int reg_val = 0;

    if (!cir->status || threshold > 0x3f)
        return ;

    reg_val = readl(cir->base + CIR_CONFIG);

    reg_val &= ~ATHR;
    reg_val |= (threshold << ATHR_OFFSET);

    writel(reg_val, cir->base + CIR_CONFIG);
}

void sunxi_cir_sample_active_thrctrl(cir_port_t port, int8_t enable)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    int reg_val = 0;

    if (!cir->status)
        return ;

    reg_val = readl(cir->base + CIR_CONFIG);

    if (enable)
        reg_val |= ATHC;
    else
        reg_val &= ~ATHC;

    writel(reg_val, cir->base + CIR_CONFIG);
}

void sunxi_cir_fifo_level(cir_port_t port, int8_t size)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    int reg_val = 0;

    if (!cir->status || size > 0x3f + 1)
        return ;

    reg_val = readl(cir->base + CIR_RXINT);

    reg_val &= ~RAL;
    reg_val |= ((size -1) << RAL_OFFSET);

    writel(reg_val, cir->base + CIR_RXINT);
}

void sunxi_cir_irq_enable(cir_port_t port, int enable)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    int reg_val = 0;

    if (!cir->status)
        return ;

    reg_val = readl(cir->base + CIR_RXINT);

    reg_val &= ~IRQ_MASK;
    enable &= IRQ_MASK;
    reg_val |= enable;

    writel(reg_val, cir->base + CIR_RXINT);
}

void sunxi_cir_irq_disable(cir_port_t port)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    int reg_val = 0;

    if (!cir->status)
        return ;

    reg_val = readl(cir->base + CIR_RXINT);

    reg_val &= ~IRQ_MASK;

    writel(reg_val, cir->base + CIR_RXINT);
}

void sunxi_cir_signal_invert(cir_port_t port, uint8_t invert)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    int reg_val = 0;

    if (!cir->status)
        return ;

    reg_val = readl(cir->base + CIR_RXCTRL);

    if (invert)
        reg_val |= RPPI;
    else
        reg_val &= ~RPPI;

    writel(reg_val, cir->base + CIR_RXCTRL);
}

void sunxi_cir_module_enable(cir_port_t port, int8_t enable)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    int reg_val = 0;

    if (!cir->status)
        return ;

    reg_val = readl(cir->base + CIR_CTRL);

    if (enable)
        reg_val |= (GEN | RXEN);
    else
        reg_val &= ~(GEN | RXEN);

    writel(reg_val, cir->base + CIR_CTRL);
}

static int sunxi_cir_gpio_init(sunxi_cir_t *cir)
{

    user_gpio_set_t irpin = {0};
    cir_gpio_t pin_cir;

    Hal_Cfg_GetKeyValue("cir", "cir_pin", (int32_t *)&irpin, (sizeof(user_gpio_set_t) + 3) / sizeof(int));

    pin_cir.gpio = (irpin.port - 1) * PINS_PER_BANK + irpin.port_num;

    pin_cir.enable_mux = irpin.mul_sel;
    pin_cir.disable_mux = 0;

    return hal_gpio_pinmux_set_function(pin_cir.gpio, pin_cir.enable_mux);

}

static int sunxi_cir_gpio_exit(sunxi_cir_t *cir)
{
    cir_gpio_t *cir_pin = cir->pin;

    return hal_gpio_pinmux_set_function(cir_pin->gpio, cir_pin->disable_mux);
}

#if defined(CONFIG_ARCH_SUN20IW1)
static int sunxi_cir_clk_init(sunxi_cir_t *cir)
{
    int ret = 0;

    cir->cir_clk_type_R = HAL_SUNXI_R_CCU;
    cir->cir_clk_type_FIXED = HAL_SUNXI_FIXED_CCU;

    cir->m_clk_id = CLK_R_APB0_IRRX;
    cir->p_clk_id = CLK_SRC_HOSC24M;
    cir->b_clk_id = CLK_R_APB0_BUS_IRRX;

    cir->mclk = hal_clock_get(cir->cir_clk_type_R, cir->m_clk_id);
    if (hal_clock_enable(cir->mclk)) {
        CIR_ERR("cir mclk enabled failed\n");
        return -1;
    }

    cir->pclk = hal_clock_get(cir->cir_clk_type_FIXED, cir->p_clk_id);
    if (hal_clock_enable(cir->pclk)) {
        CIR_ERR("cir pclk enabled failed\n");
        return -1;
    }

    cir->bclk = hal_clock_get(cir->cir_clk_type_R, cir->b_clk_id);
    if (hal_clock_enable(cir->bclk)) {
        CIR_ERR("cir bclk enabled failed\n");
        return -1;
    }

    ret = hal_clk_set_parent(cir->mclk, cir->pclk);
    if (ret) {
        printf("hal_clk_set_parent failed\n");
        return -1;
    }

    hal_reset_type_t cir_reset_type = HAL_SUNXI_R_RESET;
    hal_reset_id_t cir_reset_id = RST_R_APB0_BUS_IRRX;

    cir->cir_reset = hal_reset_control_get(cir_reset_type, cir_reset_id);
    if (hal_reset_control_deassert(cir->cir_reset)) {
        CIR_ERR("cir reset deassert failed\n");
        return -1;
    }

    return 0;
}
#else
static int sunxi_cir_clk_init(sunxi_cir_t *cir)
{
    int ret = 0;
    int TEST_CLK_TYPE = 1;
    int TEST_CLK_DATA = 1;
    int TEST_RESET_TYPE = 1;
    int TEST_RESET_DATA = 1;

    cir->test_clk_type = TEST_CLK_TYPE;

    cir->test_clk_id = TEST_CLK_DATA;

    cir->test_clk = hal_clock_get(cir->test_clk_type, cir->test_clk_id);
    if (hal_clock_enable(cir->test_clk)) {
        CIR_ERR("cir TEST_CLK enabled failed\n");
        return -1;
    }

    hal_reset_type_t cir_reset_type = TEST_RESET_TYPE;
    hal_reset_id_t cir_reset_id = TEST_RESET_DATA;

    cir->cir_reset = hal_reset_control_get(cir_reset_type, cir_reset_id);
    if (hal_reset_control_deassert(cir->cir_reset)) {
        CIR_ERR("cir reset deassert failed\n");
        return -1;
    }

    return 0;
}

#endif

#if defined(CONFIG_ARCH_SUN20IW1)
static int sunxi_cir_clk_exit(sunxi_cir_t *cir)
{
    hal_clock_disable(cir->bclk);
    hal_clock_put(cir->bclk);

    hal_clock_disable(cir->pclk);
    hal_clock_put(cir->pclk);

    hal_clock_disable(cir->mclk);
    hal_clock_put(cir->mclk);

    hal_reset_control_assert(cir->cir_reset);
    hal_reset_control_put(cir->cir_reset);

    return 0;
}
#else

static int sunxi_cir_clk_exit(sunxi_cir_t *cir)
{
    hal_clock_disable(cir->test_clk);
    hal_clock_put(cir->test_clk);

    hal_reset_control_assert(cir->cir_reset);
    hal_reset_control_put(cir->cir_reset);

    return 0;
}
#endif
static cir_status_t sunxi_cir_hw_init(sunxi_cir_t *cir)
{
    if (sunxi_cir_clk_init(cir))
        return CIR_CLK_ERR;

    if (sunxi_cir_gpio_init(cir))
        return CIR_PIN_ERR;

    if (request_irq(cir->irq, sunxi_cir_handler, 0, "cir-irq", cir)) {
        printf("cir request irq err\n");
        return CIR_IRQ_ERR;
    }
    enable_irq(cir->irq);

    return CIR_OK;
}

static void sunxi_cir_hw_exit(sunxi_cir_t *cir)
{
    disable_irq(cir->irq);
    free_irq(cir->irq, cir);
    sunxi_cir_gpio_exit(cir);
    sunxi_cir_clk_exit(cir);
}

#ifdef CONFIG_STANDBY
void sunxi_cir_suspend(cir_port_t port)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    disable_irq(cir->irq);
    hal_clock_disable(cir->bclk);
    hal_clock_disable(cir->mclk);
    sunxi_cir_gpio_exit(cir);

    return;
}

void sunxi_cir_resume(cir_port_t port)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    sunxi_cir_gpio_init(cir);
    sunxi_cir_clk_init(cir);

    enable_irq(cir->irq);

    return;
}
#endif

cir_status_t sunxi_cir_init(cir_port_t port)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    cir_status_t ret = 0;

    cir->port = port;
    cir->base = base[port];
    cir->irq = irq[port];
    cir->pin = &pin[port];
    cir->status = 1;

    ret = sunxi_cir_hw_init(cir);
    if (ret)
    {
        CIR_ERR("cir[%d] hardware init error, ret:%d\n", port, ret);
        return ret;
    }

    return ret;
}

void sunxi_cir_deinit(cir_port_t port)
{
    sunxi_cir_t *cir = &sunxi_cir[port];
    cir->status = 0;

    sunxi_cir_hw_exit(cir);
}
