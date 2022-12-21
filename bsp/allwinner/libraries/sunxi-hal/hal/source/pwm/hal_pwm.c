
/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.

 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.

 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.


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


/*
 * ===========================================================================================
 *
 *  Filename:  hal_pwm.c
 *
 *  Description:   spi driver core hal,be used by drv_pwm.c
 *
 *  Version:  Melis3.0
 *  Create:  2019-12-23
 *  Revision:  none
 *  Compiler:  GCC:version 9.2.1 20170904 (release),ARM/embedded-7-branch revision 255204
 *
 *  Author:  liuyus@allwinnertech.com
 *  Organization:  SWC-BPD
 *  Last Modified:  2019-12-31 17:55
 *
 * ===========================================================================================
 */

#include <hal_log.h>
#include <stdio.h>
#include <stdint.h>
#include <hal_clk.h>
#include <hal_reset.h>
#include <sunxi_hal_common.h>
#include <sunxi_hal_pwm.h>
#include "sunxi/clk.h"
#include <hal_cfg.h>
#include <script.h>
// #include <standby/standby.h>

hal_pwm_t sunxi_pwm;
static int pwm_init = 0;

#define SET_REG_VAL(reg_val, shift, width, set_val)     ((reg_val & ~((-1UL) >> (32 - width) << shift)) | (set_val << shift))

#define pwm_do_div(n,base) ({                   \
        u32 __base = (base);                \
        u32 __rem;                      \
        __rem = ((u64)(n)) % __base;            \
        (n) = ((u64)(n)) / __base;              \
        if (__rem > __base / 2) \
            ++(n); \
        __rem;                          \
    })

/************** config *************************/
/*
*   pwm_set_clk_src(): pwm clock source selection
*
*   @channel_in: pwm channel number
*       pwm01 pwm23 pwm45 pwm67 pwm89
*
*   @clk_src: The clock you want to set
*       0:OSC24M  1:APB1
*/
void hal_pwm_clk_src_set(uint32_t channel_in, hal_pwm_clk_src clk_src)
{
    unsigned long reg_addr = PWM_BASE + PWM_PCCR_BASE;
    uint32_t reg_val;

    uint32_t channel = channel_in / 2;
    reg_addr += 4 * channel;
    /*set clock source OSC24M or apb1*/
    reg_val = hal_readl(reg_addr);
    reg_val = SET_REG_VAL(reg_val, PWM_CLK_SRC_SHIFT, PWM_CLK_SRC_WIDTH, clk_src);
    hal_writel(reg_val, reg_addr);
}

/*
*   pwm_clk_div_m(): pwm clock divide
*
*   @div_m: 1 2 4 8 16 32 64 128 256
*/
void hal_pwm_clk_div_m(uint32_t channel_in, uint32_t div_m)
{
    unsigned long reg_addr = PWM_BASE + PWM_PCCR_BASE;
    uint32_t reg_val;

    uint32_t channel = channel_in / 2;
    reg_addr += 4 * channel;
    /*set clock div_m*/
    reg_val = hal_readl(reg_addr);
    reg_val = SET_REG_VAL(reg_val, PWM_DIV_M_SHIFT, PWM_DIV_M_WIDTH, div_m);
    hal_writel(reg_val, reg_addr);
}


void hal_pwm_prescal_set(uint32_t channel_in, uint32_t prescal)
{
    unsigned long reg_addr = PWM_BASE + PWM_PCR;
    uint32_t reg_val;

    uint32_t channel = channel_in;
    reg_addr += 0x20 * channel;
    /*set prescal*/
    reg_val = hal_readl(reg_addr);
    reg_val = SET_REG_VAL(reg_val, PWM_PRESCAL_SHIFT, PWM_PRESCAL_WIDTH, prescal);
    hal_writel(reg_val, reg_addr);
}



/* active cycles  */
void hal_pwm_set_active_cycles(uint32_t channel_in, uint32_t active_cycles)  //64
{
    unsigned long reg_addr = PWM_BASE + PWM_PPR ;
    uint32_t reg_val;

    uint32_t channel = channel_in;
    reg_addr += 0x20 * channel;
    /*set active*/
    reg_val = hal_readl(reg_addr);
    reg_val = SET_REG_VAL(reg_val, PWM_ACTIVE_CYCLES_SHIFT, PWM_ACTIVE_CYCLES_WIDTH, active_cycles);
    hal_writel(reg_val, reg_addr);
}

/* entire cycles */
void hal_pwm_set_period_cycles(uint32_t channel_in, uint32_t period_cycles)
{
    unsigned long reg_addr = PWM_BASE + PWM_PPR ;
    uint32_t reg_val;

    uint32_t channel = channel_in;
    reg_addr += 0x20 * channel;
    /*set clock BYPASS*/
    reg_val = hal_readl(reg_addr);
    reg_val = SET_REG_VAL(reg_val, PWM_PERIOD_SHIFT, PWM_PERIOD_WIDTH, period_cycles);
    hal_writel(reg_val, reg_addr);
}

static uint32_t get_pccr_reg_offset(uint32_t channel)
{
    uint32_t val;

    switch (channel)
    {
        case 0:
        case 1:
            return PWM_PCCR01;
            break;
        case 2:
        case 3:
            return PWM_PCCR23;
            break;
        case 4:
        case 5:
            return PWM_PCCR45;
            break;
        case 6:
        case 7:
            return PWM_PCCR67;
            break;
        default :
            PWM_ERR("channel is error \n");
            return PWM_PCCR01;
            break;
    }
}

/************   enable  **************/

void hal_pwm_enable_clk_gating(uint32_t channel_in)
{
    unsigned long reg_addr = PWM_BASE + PWM_PCGR;
    uint32_t reg_val;

    uint32_t channel = channel_in / 2;
    /*enable clk_gating*/
    reg_addr += 4 * channel;
    reg_val = hal_readl(reg_addr);
    reg_val = SET_REG_VAL(reg_val, PWM_CLK_GATING_SHIFT, PWM_CLK_GATING_WIDTH, 1);
    hal_writel(reg_val, reg_addr);
}

void hal_pwm_enable_controller(uint32_t channel_in)
{
    unsigned long reg_addr = PWM_BASE + PWM_PER;
    uint32_t reg_val;

    reg_val = readl(reg_addr);
    reg_val |= 1 << channel_in;

    writel(reg_val, reg_addr);
}

/************   disable  **************/
void hal_pwm_disable_controller(uint32_t channel_in)
{
    unsigned long reg_val;
    unsigned long reg_addr = PWM_BASE + PWM_PER;

    reg_val = readl(reg_addr);
    reg_val |= 1 << channel_in;

    writel(reg_val, reg_addr);
}


/*************** polarity *****************/
void hal_pwm_porality(uint32_t channel_in, hal_pwm_polarity polarity)
{
    uint32_t reg_val;
    unsigned long reg_addr = PWM_BASE + PWM_PCR;

    uint32_t channel = channel_in;
    reg_addr += 0x20 * channel;
    /*set polarity*/
    reg_val = hal_readl(reg_addr);
    reg_val = SET_REG_VAL(reg_val, PWM_ACT_STA_SHIFT, PWM_ACT_STA_WIDTH, polarity);
    hal_writel(reg_val, reg_addr);
}

static int hal_pwm_pinctrl_init(hal_pwm_t sunxi_pwm, int channel)
{
    user_gpio_set_t gpio_cfg = {0};
    char pwm_name[16];
    int count, ret;

    sprintf(pwm_name, "pwm%d", channel);

    count = Hal_Cfg_GetGPIOSecKeyCount(pwm_name);
    if (!count)
    {
        PWM_ERR("[pwm%d] not support in sys_config\n", channel);
        return -1;
    }

    Hal_Cfg_GetGPIOSecData(pwm_name, &gpio_cfg, count);

    sunxi_pwm.pin[channel] = (gpio_cfg.port - 1) * 32 + gpio_cfg.port_num;
    sunxi_pwm.enable_muxsel[channel] = gpio_cfg.mul_sel;
    ret = hal_gpio_pinmux_set_function(sunxi_pwm.pin[channel], sunxi_pwm.enable_muxsel[channel]);
    if (ret)
    {
        PWM_ERR("[pwm%d] PIN%u set function failed! return %d\n", channel, sunxi_pwm.pin[channel], ret);
        return -1;
    }

    ret = hal_gpio_set_driving_level(sunxi_pwm.pin[channel], gpio_cfg.drv_level);
    if (ret)
    {
        PWM_ERR("[spi%d] PIN%u set driving level failed! return %d\n", channel, gpio_cfg.drv_level, ret);
        return -1;
    }

    if (gpio_cfg.pull)
    {
        return hal_gpio_set_pull(sunxi_pwm.pin[channel], gpio_cfg.pull);
    }

    return 0;
}

static int hal_pwm_pinctrl_exit(hal_pwm_t sunxi_pwm, uint32_t channel)
{
    if (sunxi_pwm.pin[channel]) //sys_config
    {
        return hal_gpio_pinmux_set_function(sunxi_pwm.pin[channel], 0);    //gpio_in
    }
    else
    {
        return hal_gpio_pinmux_set_function(pwm_gpio[channel].pwm_pin, 0);
    }
}

/****the function provide for pwm driverr******************************************/
pwm_status_t hal_pwm_init(void)
{
    PWM_INFO("pwm init start");

    if (pwm_init)
    {
        pwm_init++;
        return 0;
    }

    sunxi_pwm.pwm_clk_type = SUNXI_PWM_CLK_TYPE;
    sunxi_pwm.pwm_bus_clk_id = SUNXI_PWM_CLK_ID;
    sunxi_pwm.pwm_reset_type = SUNXI_PWM_RESET_TYPE;
    sunxi_pwm.pwm_reset_id = SUNXI_PWM_RESET_ID;

    if (!sunxi_pwm.pwm_reset)
    {
        sunxi_pwm.pwm_reset = hal_reset_control_get(sunxi_pwm.pwm_reset_type, sunxi_pwm.pwm_reset_id);
    }

    hal_reset_control_deassert(sunxi_pwm.pwm_reset);

    if (!sunxi_pwm.pwm_bus_clk)
    {
        sunxi_pwm.pwm_bus_clk = hal_clock_get(sunxi_pwm.pwm_clk_type, sunxi_pwm.pwm_bus_clk_id);
        PWM_INFO("pwm_bus_clk name:%s", sunxi_pwm.pwm_bus_clk->name);
    }

    if (hal_clock_enable(sunxi_pwm.pwm_bus_clk))
    {
        return -1;
    }

#ifdef CONFIG_STANDBY
    register_pm_dev_notify(hal_pwm_suspend, hal_pwm_resume, NULL);
#endif

    PWM_INFO("pwm init end ");

    pwm_init++;
    return 0;
}

pwm_status_t hal_pwm_deinit(void)
{
    if (pwm_init)
    {
        pwm_init--;
        if (!pwm_init)
        {
            hal_reset_control_assert(sunxi_pwm.pwm_reset);
            hal_reset_control_put(sunxi_pwm.pwm_reset);

            hal_clock_disable(sunxi_pwm.pwm_bus_clk);
            hal_clock_put(sunxi_pwm.pwm_bus_clk);
        }
    }
    PWM_INFO("pwm deinit end");
    return 0;
}

pwm_status_t hal_pwm_control(int channel, struct pwm_config *config_pwm)
{
    PWM_INFO("pwm control start");

    uint32_t ret;
    unsigned int temp;
    unsigned long long c = 0;
    unsigned long entire_cycles = 256, active_cycles = 192;
    unsigned int reg_offset, reg_shift, reg_width;
    unsigned int reg_bypass_shift /*, group_reg_offset*/;
    unsigned int reg_clk_src_shift, reg_clk_src_width;
    unsigned int reg_div_m_shift, reg_div_m_width, value;

    PWM_INFO("period_ns = %ld", config_pwm->period_ns);
    PWM_INFO("duty_ns = %ld", config_pwm->duty_ns);
    PWM_INFO("polarity = %d", config_pwm->polarity);
    PWM_INFO("channel = %d", channel);

    if ((config_pwm->period_ns < config_pwm->duty_ns) || (!config_pwm->period_ns))
    {
        PWM_ERR("paremeter error : period_ns can't greater than duty_ns and period_ns can't be 0");
        return -1;
    }

    /* pwm set port */
    ret = hal_pwm_pinctrl_init(sunxi_pwm, channel);
    if (ret)
    {
        hal_gpio_pinmux_set_function(pwm_gpio[channel].pwm_pin, pwm_gpio[channel].pwm_function);
    }

    /* pwm enable controller */
    hal_pwm_enable_controller(channel);

    /* pwm set polarity */
    hal_pwm_porality(channel, config_pwm->polarity);

    /* pwm config function */
    uint32_t pre_scal_id = 0, div_m = 0, prescale = 0;
    uint32_t pre_scal[][2] =
    {
        /*reg_val   clk_pre_div*/
        {0, 1},
        {1, 2},
        {2, 4},
        {3, 8},
        {4, 16},
        {5, 32},
        {6, 64},
        {7, 128},
        {8, 256},
    };

    reg_clk_src_shift = PWM_CLK_SRC_SHIFT;
    reg_clk_src_width = PWM_CLK_SRC_WIDTH;
    reg_offset = get_pccr_reg_offset(channel);

    if (config_pwm->period_ns > 0 && config_pwm->period_ns <= 10)
    {
        /* if freq lt 100M, then direct output 100M clock,set by pass. */
        c = 100000000;
        reg_bypass_shift = channel;
        reg_offset = get_pccr_reg_offset(channel);

        temp = hal_readl(PWM_BASE + PWM_PCGR);
        temp = SET_BITS(reg_bypass_shift, 1, temp, 1); /* bypass set */
        hal_writel(temp, PWM_BASE + PWM_PCGR);
        /*clk_src_reg*/
        temp = hal_readl(PWM_BASE + reg_offset);
        temp = SET_BITS(reg_clk_src_shift, reg_clk_src_width, temp, 1);/*clock source*/
        hal_writel(temp, PWM_BASE + reg_offset);

        return 0;
    }
    else if (config_pwm->period_ns > 10 && config_pwm->period_ns <= 334)
    {
        /* if freq between 3M~100M, then select 100M as clock */
        c = 100000000;

        /*clk_src_reg : use APB1 clock */
        temp = hal_readl(PWM_BASE + reg_offset);
        temp = SET_BITS(reg_clk_src_shift, reg_clk_src_width, temp, 1);
        hal_writel(temp, PWM_BASE + reg_offset);
    }
    else if (config_pwm->period_ns > 334)
    {
        /* if freq < 3M, then select 24M clock */
        c = 24000000;

        /*clk_src_reg : use OSC24M clock */
        temp = hal_readl(PWM_BASE + reg_offset);
        temp = SET_BITS(reg_clk_src_shift, reg_clk_src_width, temp, 0);
        hal_writel(temp, PWM_BASE + reg_offset);
    }

    c = c * config_pwm->period_ns;
    pwm_do_div(c, 1000000000);
    entire_cycles = (unsigned long)c;

    for (pre_scal_id = 0; pre_scal_id < 9; pre_scal_id++)
    {
        if (entire_cycles <= 65536)
        {
            break;
        }
        for (prescale = 0; prescale < PRESCALE_MAX + 1; prescale++)
        {
            entire_cycles = ((unsigned long)c / pre_scal[pre_scal_id][1]) / (prescale + 1);
            if (entire_cycles <= 65536)
            {
                div_m = pre_scal[pre_scal_id][0];
                break;
            }
        }
    }

    c = (unsigned long long)entire_cycles * config_pwm->duty_ns;
    pwm_do_div(c, config_pwm->period_ns);
    active_cycles = c;
    if (entire_cycles == 0)
    {
        entire_cycles++;
    }

    /* config clk div_m */
    reg_div_m_shift = PWM_DIV_M_SHIFT;
    reg_div_m_width = PWM_DIV_M_WIDTH;
    temp = hal_readl(PWM_BASE + reg_offset);
    temp = SET_BITS(reg_div_m_shift, reg_div_m_width, temp, div_m);
    hal_writel(temp, PWM_BASE + reg_offset);

    /* config gating */
    reg_shift = channel;
    value = hal_readl(PWM_BASE + PWM_PCGR);
    value = SET_BITS(reg_shift, 1, value, 1);/* set gating */
    hal_writel(value, PWM_BASE + PWM_PCGR);

    /* config prescal */
    reg_offset = PWM_PCR + 0x20 * channel;
    reg_shift = PWM_PRESCAL_SHIFT;
    reg_width = PWM_PRESCAL_WIDTH;
    temp = hal_readl(PWM_BASE + reg_offset);
    temp = SET_BITS(reg_shift, reg_width, temp, prescale);
    hal_writel(temp, PWM_BASE + reg_offset);

    /* config active cycles */
    reg_offset = PWM_PPR + 0x20 * channel;
    reg_shift = PWM_ACT_CYCLES_SHIFT;
    reg_width = PWM_ACT_CYCLES_WIDTH;
    temp = hal_readl(PWM_BASE + reg_offset);
    temp = SET_BITS(reg_shift, reg_width, temp, active_cycles);
    hal_writel(temp, PWM_BASE + reg_offset);

    /* config period cycles */
    reg_offset = PWM_PPR + 0x20 * channel;
    reg_shift = PWM_PERIOD_CYCLES_SHIFT;
    reg_width = PWM_PERIOD_CYCLES_WIDTH;
    temp = hal_readl(PWM_BASE + reg_offset);
    temp = SET_BITS(reg_shift, reg_width, temp, (entire_cycles - 1));
    hal_writel(temp, PWM_BASE + reg_offset);

    PWM_INFO("pwm control end ");

    return 0;
}

pwm_status_t hal_pwm_resume(void)
{
    if (hal_reset_control_assert(sunxi_pwm.pwm_reset))
    {
        return -1;
    }

    if (hal_reset_control_deassert(sunxi_pwm.pwm_reset))
    {
        return -1;
    }

    if (hal_clock_enable(sunxi_pwm.pwm_bus_clk))
    {
        return -1;
    }

    PWM_INFO("hal pwm resume");
    return 0;
}

pwm_status_t hal_pwm_suspend(void)
{
    if (hal_reset_control_assert(sunxi_pwm.pwm_reset))
    {
        return -1;
    }

    if (hal_clock_disable(sunxi_pwm.pwm_bus_clk))
    {
        return -1;
    }

    PWM_INFO("hal pwm suspend");
    return 0;
}
