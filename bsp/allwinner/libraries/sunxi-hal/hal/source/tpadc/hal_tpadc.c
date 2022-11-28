/*
 * ===========================================================================================
 *
 *       Filename:  hal_tpadc.c
 *
 *    Description:  tpadc hal layer code
 *
 *        Version:  Melis3.0
 *         Create:  2020-1-14
 *       Revision:  none
 *       Compiler:  GCC:version 9.2.1 20170904 (release),ARM/embedded-7-branch revision 255204
 *
 *         Author:  liuyu@allwinnertech.com
 *   Organization:  SWC-BPD
 *  Last Modified:  2021-1-14
 *
 * ===========================================================================================
 */
#include <hal_interrupt.h>
#include <hal_clk.h>
#include <hal_reset.h>
#include "sunxi_hal_tpadc.h"

hal_tpadc_t hal_tpadc;

static void sunxi_flush_fifo(unsigned long reg_base)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_INT_FIFOC);
    reg_val  = SET_BITS(TP_FIFO_FLUSH, TP_FIFO_FLUSH_WIDTH,reg_val, 0x1);

    writel(reg_val, reg_base + TP_INT_FIFOC);
}

static void sunxi_clear_fifo_status(unsigned long reg_base)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_INT_FIFOS);
    reg_val  = SET_BITS(FIFO_OVERRUN_PENDING, FIFO_OVERRUN_PENDIN_WIDTH,
                reg_val, 0x0);
    reg_val  = SET_BITS(FIFO_DATA_PENDING, FIFO_DATA_PENDING_WIDTH,
                reg_val, 0x0);

    writel(reg_val, reg_base + TP_INT_FIFOS);
}

static void sunxi_set_acqiure_time(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL0);
    reg_val  = SET_BITS(TACQ, TACQ_WIDTH, reg_val, val);

    writel(reg_val, reg_base + TP_CTRL0);
}

static void sunxi_set_frequency_divider(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL0);
    reg_val  = SET_BITS(FS_DIV, FS_DIV_WIDTH, reg_val, val);

    writel(reg_val, reg_base + TP_CTRL0);
}

static void sunxi_set_clk_divider(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL0);
    reg_val  = SET_BITS(ADC_CLK_DIVIDER, ADC_CLK_DIVIDER_WIDTH, reg_val, val);

    writel(reg_val, reg_base + TP_CTRL0);
}

static void sunxi_select_delay_mode(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL0);
    reg_val  = SET_BITS(ADC_FIRST_DLY_MODE, ADC_FIRST_DLY_MODE_WIDTH,reg_val, val);

    writel(reg_val, reg_base + TP_CTRL0);
}

static void sunxi_set_dealy_time(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL0);
    reg_val  = SET_BITS(ADC_FIRST_DLY, ADC_FIRST_DLY_WIDTH,reg_val, val);

    writel(reg_val, reg_base + TP_CTRL0);
}

static void sunxi_clk_init(unsigned long reg_base)
{
    sunxi_set_acqiure_time(reg_base, 0x02); //2us
    sunxi_set_frequency_divider(reg_base, 0xb);
    sunxi_set_clk_divider(reg_base, 0x3);
    sunxi_select_delay_mode(reg_base, 0x1);
    sunxi_set_dealy_time(reg_base, 0xf);
}

static uint32_t sunxi_tpadc_adc_ch_select(unsigned long reg_base, tp_channel_id id)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL1);
    switch (id) {
    case TP_CH_0:
        reg_val |= TP_CH0_SELECT;
        break;
    case TP_CH_1:
        reg_val |= TP_CH1_SELECT;
        break;
    case TP_CH_2:
        reg_val |= TP_CH2_SELECT;
        break;
    case TP_CH_3:
        reg_val |= TP_CH3_SELECT;
        break;
    default:
        TPADC_ERR("%s, invalid channel id!", __func__);
        return TPADC_ERROR;
    }
    writel(reg_val, reg_base + TP_CTRL1);

    return 0;
}

/* 0:TAPADC  1: ADC*/
static void sunxi_tpadc_mode_select(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL1);
    reg_val  = SET_BITS(TP_MODE_SELECT, TP_MODE_SELECT_WIDTH,reg_val, val);

    writel(reg_val, reg_base + TP_CTRL1);
}


static void sunxi_tpadc_enable(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL1);
    reg_val  = SET_BITS(TP_EN, TP_EN_WIDTH, reg_val, val);

    writel(reg_val, reg_base + TP_CTRL1);
}

static void sunxi_set_up_debou_time(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL1);
    reg_val  = SET_BITS(TP_DEBOUNCE, TP_DEBOUNCE_WIDTH, reg_val, val);

    writel(reg_val, reg_base + TP_CTRL1);
}

static void sunxi_set_pressure_thresholed(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL2);
    reg_val  = SET_BITS(PRE_MEA, PRE_MEA_WIDTH, reg_val, val);

    writel(reg_val, reg_base + TP_CTRL2);
}

static void sunxi_pressure_enable(unsigned long reg_base)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL2);
    reg_val  = SET_BITS(PRE_MEA_EN, PRE_MEA_EN_WIDTH, reg_val, 0x1);

    writel(reg_val, reg_base + TP_CTRL2);
}

/* 0: x_data y_data x_data y_data */
static void sunxi_tp_mode_fifo_select(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL2);
    reg_val  = SET_BITS(TP_FIFO_MODE, TP_FIFO_MODE_WIDTH, reg_val, val);

    writel(reg_val, reg_base + TP_CTRL2);
}

static void sunxi_set_sensitivity(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL2);
    reg_val  = SET_BITS(TP_SENSITIVE, TP_SENSITIVE_WIDTH, reg_val, val);

    writel(reg_val, reg_base + TP_CTRL2);
}

static void sunxi_set_filter_type(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL3);
    reg_val  = SET_BITS(FILTER_TYPE, FILTER_TYPE_WIDTH, reg_val, val);

    writel(reg_val, reg_base + TP_CTRL3);
}
static void sunxi_filter_enable(unsigned long reg_base)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_CTRL3);
    reg_val  = SET_BITS(FILTER_EN, FILTER_EN_WIDTH, reg_val, 0x1);

    writel(reg_val, reg_base + TP_CTRL3);
}

static void sunxi_downirq_enable(unsigned long reg_base)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_INT_FIFOC);
    reg_val  = SET_BITS(TP_DOWN_IRQ_EN, TP_DOWN_IRQ_ENWIDTH, reg_val, 0x1);

    writel(reg_val, reg_base + TP_INT_FIFOC);
}

static void sunxi_upirq_enable(unsigned long reg_base)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_INT_FIFOC);
    reg_val  = SET_BITS(TP_UP_IRQ_EN, TP_UP_IRQ_EN_WIDTH, reg_val, 0x1);

    writel(reg_val, reg_base + TP_INT_FIFOC);
}

static void sunxi_drq_enable(unsigned long reg_base)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_INT_FIFOC);
    reg_val  = SET_BITS(TP_DATA_DRQ_EN, TP_DATA_DRQ_EN_WIDTH, reg_val, 0x1);

    writel(reg_val, reg_base + TP_INT_FIFOC);
}

static void sunxi_set_trig_level(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_INT_FIFOC);
    reg_val  = SET_BITS(TP_FIFO_TRIG, TP_FIFO_TRIG_WIDTH, reg_val, val);

    writel(reg_val, reg_base + TP_INT_FIFOC);
}

static void sunxi_xydata_change_enable(unsigned long reg_base, uint32_t val)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_INT_FIFOC);
    reg_val = SET_BITS(TP_DATA_XY_CHANGE, TP_DATA_XY_CHANGE_WIDTH, reg_val, val);

    writel(reg_val, reg_base + TP_INT_FIFOC);
}

static void sunxi_irq_enable(unsigned long reg_base)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_INT_FIFOC);
    reg_val = SET_BITS(TP_DATA_IRQ_EN, TP_DATA_IRQ_EN_WIDTH, reg_val, 0x1);

    writel(reg_val, reg_base + TP_INT_FIFOC);
}

static void sunxi_irq_disable(unsigned long reg_base)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_INT_FIFOC);
    reg_val = SET_BITS(TP_DATA_IRQ_EN, TP_DATA_IRQ_EN_WIDTH, reg_val, 0x0);

    writel(reg_val, reg_base + TP_INT_FIFOC);
}

static void sunxi_overrun_enable(unsigned long reg_base)
{
    uint32_t reg_val;

    reg_val = readl(reg_base + TP_INT_FIFOC);
    reg_val = SET_BITS(TP_FIFO_OVERRUN_IRQ, TP_FIFO_OVERRUN_IRQ_WIDTH, reg_val, 0x1);

    writel(reg_val, reg_base + TP_INT_FIFOC);
}

static u32 sunxi_tpadc_irq_status(unsigned long reg_base)
{
    return readl(reg_base + TP_INT_FIFOS);
}

static void sunxi_tpadc_clear_pending(unsigned long reg_base)
{
    int reg;

    reg = readl(reg_base + TP_INT_FIFOS);
    writel(reg, reg_base + TP_INT_FIFOS);
}

static u32 sunxi_tpadc_ch_select(unsigned long reg_base, tp_channel_id id)
{
    u32 reg_val;

    reg_val = readl(reg_base + TP_CTRL1);
    switch (id) {
    case TP_CH_0:
        reg_val |= TP_CH0_SELECT;
        break;
    case TP_CH_1:
        reg_val |= TP_CH1_SELECT;
        break;
    case TP_CH_2:
        reg_val |= TP_CH2_SELECT;
        break;
    case TP_CH_3:
        reg_val |= TP_CH3_SELECT;
        break;
    default:
        TPADC_ERR("%s, invalid channel id!", __func__);
        return -1;
    }
    writel(reg_val, reg_base + TP_CTRL1);

    return 0;
}

static int sunxi_tpadc_ch_deselect(unsigned long reg_base, tp_channel_id id)
{
    u32 reg_val;

    reg_val = readl(reg_base + TP_CTRL1);
    switch (id) {
    case TP_CH_0:
        reg_val &= ~TP_CH0_SELECT;
        break;
    case TP_CH_1:
        reg_val &= ~TP_CH1_SELECT;
        break;
    case TP_CH_2:
        reg_val &= ~TP_CH2_SELECT;
        break;
    case TP_CH_3:
        reg_val &= ~TP_CH3_SELECT;
        break;
    default:
        TPADC_ERR("%s, invalid channel id!", __func__);
        return -1;
    }
    writel(reg_val, reg_base + TP_CTRL1);

    return 0;
}

static u32 hal_tpadc_data_read(unsigned long reg_base)
{
    hal_tpadc_t *tpadc = &hal_tpadc;

    return readl(reg_base + TP_DATA);
}

static int hal_tpadc_callback(uint32_t data, data_flag_t flag)
{
    TPADC_INFO("tpadc : tpadc mode interrupt, data_flag is %ld", flag);
    return 0;
}

static int hal_tpadc_adc_callback(uint32_t data, tp_channel_id channel)
{
    TPADC_INFO("tpadc : auxiliary adc mode interrupt");
    return 0;
}

static void sunxi_tpadc_setup(hal_tpadc_t *tpadc)
{
    u32 i;

    tpadc->reg_base = (unsigned long)TPADC_BASE;
    tpadc->irq_num = SUNXI_TPADC_IRQ;
    tpadc->rst_clk_id = (hal_reset_id_t)RST_BUS_TPADC;
    tpadc->bus_clk_id = (hal_clk_id_t)CLK_BUS_TPADC;
    tpadc->mod_clk_id = (hal_clk_id_t)CLK_TPADC;

    tpadc->callback = hal_tpadc_callback;
    for(i=0; i<TP_CH_MAX; i++)
        tpadc->adc_callback[i] = hal_tpadc_adc_callback;
}

static hal_tpadc_status_t hal_tpadc_clk_init(hal_tpadc_t *tpadc)
{
    hal_clk_type_t  clk_type = HAL_SUNXI_CCU;
    hal_clk_id_t bus_clk_id = tpadc->bus_clk_id;
    hal_clk_id_t mod_clk_id = tpadc->mod_clk_id;

    hal_reset_type_t reset_type = HAL_SUNXI_RESET;
    hal_reset_id_t  tpadc_reset_id = tpadc->rst_clk_id;
    struct reset_control *reset;

    reset = hal_reset_control_get(reset_type, tpadc_reset_id);
    if (hal_reset_control_deassert(reset))
    {
        TPADC_ERR("tpadc reset deassert  failed!");
        return TPADC_ERROR;
    }
    hal_reset_control_put(reset);

    tpadc->mod_clk = hal_clock_get(clk_type, mod_clk_id);
    if (hal_clock_enable(tpadc->mod_clk))
    {
        TPADC_ERR("tpadc mod clk enable mclk failed!");
        return TPADC_ERROR;
    }

    tpadc->bus_clk = hal_clock_get(clk_type, bus_clk_id);
    if (hal_clock_enable(tpadc->bus_clk))
    {
        TPADC_ERR("tpadc bus clk enable mclk failed!");
        return TPADC_ERROR;
    }

    return TPADC_OK;
}

static hal_tpadc_status_t hal_tpadc_clk_exit(hal_tpadc_t *tpadc)
{
    hal_clock_disable(tpadc->bus_clk);
    hal_clock_put(tpadc->bus_clk);

    hal_clock_disable(tpadc->mod_clk);
    hal_clock_put(tpadc->mod_clk);

    return TPADC_OK;
}

/* the rtpadc tpadc mode interface */
static irqreturn_t tpadc_handler(int irq, void *dev)
{
    hal_tpadc_t *tpadc = (hal_tpadc_t *)dev;
    u32  reg_val;
    u32 x_data, y_data;
    u32 i;

    reg_val = sunxi_tpadc_irq_status(tpadc->reg_base);
    if (reg_val & TP_DATAPEND) {
        x_data = hal_tpadc_data_read(tpadc->reg_base);
        tpadc->callback(x_data, DATA_X);
        y_data = hal_tpadc_data_read(tpadc->reg_base);
        tpadc->callback(y_data, DATA_Y);
    }

    if (reg_val & TP_UPPEND) {
        tpadc->callback(0, DATA_UP);
    }

    if (reg_val & TP_DOWNPEND) {
        TPADC_INFO("touch down ");
    }

    sunxi_tpadc_clear_pending(tpadc->reg_base);

    return TPADC_OK;
}

hal_tpadc_status_t hal_tpadc_register_callback(tpadc_usercallback_t user_callback)
{
    hal_tpadc_t *tpadc = &hal_tpadc;

    if (user_callback == NULL)
        return TPADC_ERROR;
    else
        tpadc->callback = user_callback;

    return TPADC_OK;
}

hal_tpadc_status_t hal_tpadc_init(void)
{
    hal_tpadc_t *tpadc = &hal_tpadc;
    u32 clk_in;

    sunxi_tpadc_setup(tpadc);

    if (hal_tpadc_clk_init(tpadc))
    {
        TPADC_ERR("tpadc init clk error");
        return TPADC_ERROR;
    }

    /* clear status */
    sunxi_flush_fifo(tpadc->reg_base);
    sunxi_clear_fifo_status(tpadc->reg_base);

    sunxi_clk_init(tpadc->reg_base);

    sunxi_tpadc_mode_select(tpadc->reg_base, 0);
    sunxi_tpadc_enable(tpadc->reg_base, 1);
    sunxi_set_up_debou_time(tpadc->reg_base, 0x00);

    sunxi_set_pressure_thresholed(tpadc->reg_base, 0x800fff);
    sunxi_pressure_enable(tpadc->reg_base);
    sunxi_tp_mode_fifo_select(tpadc->reg_base, 0x00);
    sunxi_set_sensitivity(tpadc->reg_base, 0xf);

    sunxi_set_filter_type(tpadc->reg_base, 0x1);
    sunxi_filter_enable(tpadc->reg_base);

    sunxi_downirq_enable(tpadc->reg_base);
    sunxi_upirq_enable(tpadc->reg_base);
    sunxi_drq_enable(tpadc->reg_base);
    sunxi_set_trig_level(tpadc->reg_base, 0x1);
    sunxi_xydata_change_enable(tpadc->reg_base, 0);
    sunxi_irq_enable(tpadc->reg_base);
    sunxi_overrun_enable(tpadc->reg_base);

    sunxi_tpadc_clear_pending(tpadc->reg_base);

    if (request_irq(tpadc->irq_num, tpadc_handler, 0, "tpadc", tpadc))
    {
        TPADC_ERR("tpadc request irq(%d) failed \n", tpadc->irq_num);
    return TPADC_ERROR;
    }

    enable_irq(tpadc->irq_num);

    TPADC_INFO("tpadc init success");

    return TPADC_OK;
}

hal_tpadc_status_t hal_tpadc_exit(void)
{
    hal_tpadc_t *tpadc = &hal_tpadc;

    sunxi_irq_disable(tpadc->reg_base);
    free_irq(tpadc->irq_num, tpadc);
    hal_tpadc_clk_exit(tpadc);

    return TPADC_OK;
}

hal_tpadc_status_t hal_tpadc_resume(void)
{
    hal_tpadc_t *tpadc = &hal_tpadc;

    hal_tpadc_clk_init(tpadc);
    sunxi_tpadc_enable(tpadc->reg_base, 1);

    return TPADC_OK;
}

hal_tpadc_status_t hal_tpadc_suspend(void)
{
    hal_tpadc_t *tpadc = &hal_tpadc;

    sunxi_tpadc_enable(tpadc->reg_base, 0);
    hal_tpadc_clk_exit(tpadc);

    return TPADC_OK;
}

/* the rtpadc adc mode interface*/
static irqreturn_t tpadc_adc_handler(int irq, void *dev)
{
    hal_tpadc_t *tpadc = (hal_tpadc_t *)dev;
    u32 reg_val;
    u32 data;

    reg_val = sunxi_tpadc_irq_status(tpadc->reg_base);
    if (reg_val & TP_DATAPEND) {
        reg_val = readl(tpadc->reg_base + TP_CTRL1);
        if (reg_val & TP_CH0_SELECT)
        {
            data = hal_tpadc_data_read(tpadc->reg_base);
            if (tpadc->adc_callback[0])
                tpadc->adc_callback[0](data, TP_CH0_SELECT);
        }

        if (reg_val & TP_CH1_SELECT)
        {
            data = hal_tpadc_data_read(tpadc->reg_base);
            if (tpadc->adc_callback[1])
                tpadc->adc_callback[1](data, TP_CH1_SELECT);
        }

        if (reg_val & TP_CH2_SELECT)
        {
            data = hal_tpadc_data_read(tpadc->reg_base);
            if (tpadc->adc_callback[2])
                tpadc->adc_callback[2](data, TP_CH2_SELECT);
        }

        if (reg_val & TP_CH3_SELECT)
        {
            data = hal_tpadc_data_read(tpadc->reg_base);
            if (tpadc->adc_callback[3])
                tpadc->adc_callback[3](data, TP_CH3_SELECT);
        }

        if (reg_val & 0x0)
        {
            TPADC_ERR("no channel init, you need init 1~4 channel first");
            return -IRQ_HANDLED;
        }
    }

    sunxi_tpadc_clear_pending(tpadc->reg_base);

    return IRQ_NONE;
}

hal_tpadc_status_t hal_tpadc_adc_register_callback(tp_channel_id channel, tpadc_adc_usercallback_t user_adc_callback)
{
    hal_tpadc_t *tpadc = &hal_tpadc;

    if (user_adc_callback == NULL)
        return TPADC_ERROR;
    else
        tpadc->adc_callback[channel] = user_adc_callback;

    return TPADC_OK;
}

hal_tpadc_status_t hal_tpadc_adc_init(void)
{
    hal_tpadc_t *tpadc = &hal_tpadc;
    u32 clk_in;

    sunxi_tpadc_setup(tpadc);

    if (hal_tpadc_clk_init(tpadc))
    {
        TPADC_ERR("tpadc init clk error");
        return TPADC_ERROR;
    }

    /* clear status */
    sunxi_flush_fifo(tpadc->reg_base);
    sunxi_clear_fifo_status(tpadc->reg_base);

    sunxi_clk_init(tpadc->reg_base);

    sunxi_tpadc_mode_select(tpadc->reg_base, 1);
    sunxi_tpadc_enable(tpadc->reg_base, 1);

    sunxi_set_filter_type(tpadc->reg_base, 0x1);
    sunxi_filter_enable(tpadc->reg_base);

    sunxi_downirq_enable(tpadc->reg_base);
    sunxi_upirq_enable(tpadc->reg_base);
    sunxi_set_trig_level(tpadc->reg_base, 0x3);
    sunxi_irq_enable(tpadc->reg_base);

    sunxi_tpadc_clear_pending(tpadc->reg_base);

    if (request_irq(tpadc->irq_num, tpadc_adc_handler, 0, "tpadc", tpadc))
    {
        TPADC_ERR("tpadc request irq(%d) failed \n", tpadc->irq_num);
    return TPADC_ERROR;
    }

    enable_irq(tpadc->irq_num);

    TPADC_INFO("tpadc init success");

    return TPADC_OK;
}

hal_tpadc_status_t hal_tpadc_adc_channel_init(tp_channel_id channel)
{
    hal_tpadc_t *tpadc = &hal_tpadc;

    if (sunxi_tpadc_adc_ch_select(tpadc->reg_base, channel))
    {
        TPADC_ERR("TPADC adc mode channel select error");
        return -1;
    }

    return 0;
}

hal_tpadc_status_t hal_tpadc_adc_exit()
{
    hal_tpadc_t *tpadc = &hal_tpadc;

    sunxi_irq_disable(tpadc->reg_base);
    free_irq(tpadc->irq_num, tpadc);

    hal_clock_disable(tpadc->bus_clk);
    hal_clock_put(tpadc->bus_clk);

    hal_clock_disable(tpadc->mod_clk);
    hal_clock_put(tpadc->mod_clk);

    return TPADC_OK;
}
