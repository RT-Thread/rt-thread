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
#include <interrupt.h>
#include <hal_clk.h>
#include <sunxi_hal_ir.h>
#include <init.h>


#define IRADC_ERR(fmt, arg...) printf("%s()%d " fmt, __func__, __LINE__, ##arg)
#define IRADC_INIT(fmt, arg...) printf("%s()%d " fmt, __func__, __LINE__, ##arg)

#ifdef IRADC_DEBUG
#define IR_INFO(fmt, arg...) printf("%s()%d " fmt, __func__, __LINE__, ##arg)
#define IR_INFO_IRQ(fmt, arg...) __log("%s()%d " fmt, __func__, __LINE__, ##arg)
#else
#define IR_INFO(fmt, arg...)                                                  \
    do {                                                                   \
    } while (0);
#define IR_INFO_IRQ(fmt, arg...)                                                  \
    do {                                                                   \
    } while (0);
#endif

hal_ir_t hal_ir;

static inline u8 ir_get_data(uint32_t reg_base)
{
    return (u8)(hal_readl(reg_base + IR_RXDAT_REG) & 0xff);
}

static inline uint32_t ir_get_intsta(uint32_t reg_base)
{
    return hal_readl(reg_base + IR_RXINTS_REG);
}

static inline void ir_clr_intsta(uint32_t reg_base, uint32_t bitmap)
{
    uint32_t tmp = hal_readl(reg_base + IR_RXINTS_REG);

    tmp &= ~0xff;
    tmp |= bitmap & 0xff;
    hal_writel(tmp, reg_base + IR_RXINTS_REG);
}

static irqreturn_t ir_handler(int irq, void *dev)
{
    hal_ir_t *ir = (hal_ir_t *)dev;
    uint32_t intsta, dcnt;
    uint32_t i = 0;
    uint32_t reg_data = 0;

    IR_INFO_IRQ("IR RX IRQ Serve\n");

    intsta = ir_get_intsta(ir->reg_base);
    ir_clr_intsta(ir->reg_base, intsta);

    /* get the count of signal */
    dcnt = (intsta >> 8) & 0x7f;
    IR_INFO_IRQ("receive cnt :%d\n", dcnt);
    /* Read FIFO and fill the raw event */
    for (i = 0; i < dcnt; i++)
    {
        /* get the data from fifo */
        reg_data = ir_get_data(ir->reg_base);
        ir->callback(IR_RXINTS_RXDA, reg_data);
    }

    if (intsta & IR_RXINTS_RXPE)
    {
        /* The last pulse can not call ir_raw_event_store() since miss
         * invert level in above, manu call
         */
        ir->callback(IR_RXINTS_RXPE, reg_data);
    }

    if (intsta & IR_RXINTS_RXOF)
    {
        /* FIFO Overflow */
        ir->callback(IR_RXINTS_RXPE, reg_data);
    }

    return IRQ_HANDLED;
}

static void ir_mode_set(uint32_t reg_base, enum ir_mode set_mode)
{
    uint32_t ctrl_reg = 0;

    switch (set_mode)
    {
        case CIR_MODE_ENABLE:
            ctrl_reg = hal_readl(reg_base + IR_CTRL_REG);
            ctrl_reg |= IR_CIR_MODE;
            break;
        case IR_MODULE_ENABLE:
            ctrl_reg = hal_readl(reg_base + IR_CTRL_REG);
            ctrl_reg |= IR_ENTIRE_ENABLE;
            break;
        case IR_BOTH_PULSE_MODE:
            ctrl_reg = hal_readl(reg_base + IR_CTRL_REG);
            ctrl_reg |= IR_BOTH_PULSE;
            break;
        case IR_LOW_PULSE_MODE:
            ctrl_reg = hal_readl(reg_base + IR_CTRL_REG);
            ctrl_reg |= IR_LOW_PULSE;
            break;
        case IR_HIGH_PULSE_MODE:
            ctrl_reg = hal_readl(reg_base + IR_CTRL_REG);
            ctrl_reg |= IR_HIGH_PULSE;
            break;
        default:
            IRADC_ERR("ir_mode_set error!!\n");
            return;
    }
    hal_writel(ctrl_reg, reg_base + IR_CTRL_REG);
}

static void ir_sample_config(uint32_t reg_base,
                             enum ir_sample_config set_sample)
{
    uint32_t sample_reg = 0;

    sample_reg = hal_readl(reg_base + IR_SPLCFG_REG);

    switch (set_sample)
    {
        case IR_SAMPLE_REG_CLEAR:
            sample_reg = 0;
            break;
        case IR_CLK_SAMPLE:
            sample_reg |= IR_SAMPLE_DEV;
            break;
        case IR_FILTER_TH_NEC:
            sample_reg |= IR_RXFILT_VAL;
            break;
        case IR_FILTER_TH_RC5:
            sample_reg |= IR_RXFILT_VAL_RC5;
            break;
        case IR_IDLE_TH:
            sample_reg |= IR_RXIDLE_VAL;
            break;
        case IR_ACTIVE_TH:
            sample_reg |= IR_ACTIVE_T;
            sample_reg |= IR_ACTIVE_T_C;
            break;
        case IR_ACTIVE_TH_SAMPLE:
            sample_reg |= IR_ACTIVE_T_SAMPLE;
            sample_reg &= ~IR_ACTIVE_T_C;
            break;
        default:
            IRADC_ERR("config err !\n");;
    }
    hal_writel(sample_reg, reg_base + IR_SPLCFG_REG);
}

static void ir_signal_invert(uint32_t reg_base)
{
    uint32_t reg_value;

    reg_value = 0x1 << 2;
    hal_writel(reg_value, reg_base + IR_RXCFG_REG);
}

static void ir_irq_config(uint32_t reg_base, enum ir_irq_config set_irq)
{
    uint32_t irq_reg = 0;

    switch (set_irq)
    {
        case IR_IRQ_STATUS_CLEAR:
            hal_writel(0xef, reg_base + IR_RXINTS_REG);
            return;
        case IR_IRQ_ENABLE:
            irq_reg = hal_readl(reg_base + IR_RXINTE_REG);
            irq_reg |= IR_IRQ_STATUS;
            break;
        case IR_IRQ_FIFO_SIZE:
            irq_reg = hal_readl(reg_base + IR_RXINTE_REG);
            irq_reg |= IR_FIFO_20;
            break;
        default:
            return;
    }
    hal_writel(irq_reg, reg_base + IR_RXINTE_REG);
}

static void hal_ir_reg_cfg(uint32_t reg_base)
{
    /* Enable IR Mode */
    ir_mode_set(reg_base, CIR_MODE_ENABLE);
    /* Config IR Smaple Register */
    ir_sample_config(reg_base, IR_SAMPLE_REG_CLEAR);
    ir_sample_config(reg_base, IR_CLK_SAMPLE);
    ir_sample_config(reg_base, IR_IDLE_TH); /* Set Idle Threshold */

    /* rc5 Set Active Threshold */
    ir_sample_config(reg_base, IR_ACTIVE_TH_SAMPLE);
    ir_sample_config(reg_base, IR_FILTER_TH_NEC); /* Set Filter Threshold */
    ir_signal_invert(reg_base);
    /* Clear All Rx Interrupt Status */
    ir_irq_config(reg_base, IR_IRQ_STATUS_CLEAR);
    /* Set Rx Interrupt Enable */
    ir_irq_config(reg_base, IR_IRQ_ENABLE);

    /* Rx FIFO Threshold = FIFOsz/2; */
    ir_irq_config(reg_base, IR_IRQ_FIFO_SIZE);
    /* for NEC decode which start with high level in the header so should
     * use IR_HIGH_PULSE_MODE mode, but some ICs don't support this function
     * therefor use IR_BOTH_PULSE_MODE mode as default
     */
    ir_mode_set(reg_base, IR_BOTH_PULSE_MODE);
    /* Enable IR Module */
    ir_mode_set(reg_base, IR_MODULE_ENABLE);
}


static hal_ir_status_t hal_ir_clk_init(void)
{
    int ret;
    int32_t rate;
    hal_clk_id_t mclk = HAL_CLK_PERIPH_IRTX;

    ret = hal_clk_set_parent(mclk, HAL_CLK_SRC_HOSC24M);
    if (ret)
    {
        IRADC_ERR("[ir] clk set parent failed! return %d\n", ret);
        return IR_CLK_ERR;
    }

    rate = hal_clk_round_rate(mclk, IR_CLK);
    if (rate < 0)
    {
        IRADC_ERR("[ir] clk round rate failed! return %ld\n", rate);
        return IR_CLK_ERR;
    }

    ret = hal_clk_set_rate(mclk, rate);
    if (ret)
    {
        IRADC_ERR("[ir] clk set rate failed! return %d\n", ret);
        return IR_CLK_ERR;
    }

    rate = hal_clk_get_rate(mclk);
    if (rate < 0)
    {
        IRADC_ERR("[ir] clk get rate failed! return %ld\n", rate);
        return IR_CLK_ERR;
    }

    ret = hal_clock_enable(mclk);
    if (ret)
    {
        IRADC_ERR("[ir] couldn't enable mlck! return %d\n", ret);
        return IR_CLK_ERR;
    }

    return IR_OK;
}

static hal_ir_status_t hal_ir_pinctrl_init(hal_ir_t *ir)
{
    int ret;

    ret = hal_gpio_pinmux_set_function(ir->pin, ir->pin_mux);
    if (ret)
    {
        IRADC_ERR(
            "[ir] PIN set function failed! return %d\n", ret);
        return IR_PIN_ERR;
    }
    ret = hal_gpio_set_driving_level(ir->pin, ir->pin_drv);
    if (ret)
    {
        IRADC_ERR(
            "[ir] PIN set driving level failed! return %d\n", ret);
        return IR_PIN_ERR;
    }
    return IR_OK;
}

int hal_ir_register_callback(ir_callback_t callback)
{
    hal_ir_t *ir = &hal_ir;
    ir->callback = callback;
    return IR_OK;
}

int hal_ir_init(void)
{
    hal_ir_t *ir = &hal_ir;

    ir->reg_base = SUNXI_IRADC_PBASE;
    ir->irq_num = SUNXI_IRQ_IRADC;
    ir->pin = IRADC_PIN;
    ir->pin_drv = IR_DRVSEL;
    ir->pin_mux = IR_MUXSEL;
    IRADC_INIT("ir init\n");

    if (hal_ir_pinctrl_init(ir))
    {
        IRADC_ERR("ir init pinctrl error\n");
        return IR_PIN_ERR;
    }

    if (hal_ir_clk_init())
    {
        IRADC_ERR("ir init clk error\n");
        return IR_CLK_ERR;
    }

    hal_ir_reg_cfg(ir->reg_base);
    if (request_irq(ir->irq_num, ir_handler, 0, "ir", ir))
    {
        IRADC_ERR("ir request irq failed\n");
        return IR_IRQ_ERR;
    }
    enable_irq(ir->irq_num);

    return IR_OK;
}
