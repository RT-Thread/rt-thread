/**************************************************************************//**
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-12      Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_ADC)

#include <rtdevice.h>
#include "NuMicro.h"
#include <drv_sys.h>

/* Private define ---------------------------------------------------------------*/

/* Private Typedef --------------------------------------------------------------*/
struct nu_adc
{
    struct rt_adc_device dev;
    char *name;
    uint32_t OpFreqKHz;
    IRQn_Type irqn;
    E_SYS_IPRST rstidx;
    E_SYS_IPCLK clkidx;
    int chn_num;
    uint32_t chn_mask;
    rt_sem_t m_psSem;
};
typedef struct nu_adc *nu_adc_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled);
static rt_err_t nu_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value);

/* Public functions ------------------------------------------------------------*/
int rt_hw_adc_init(void);

/* Private variables ------------------------------------------------------------*/

static struct nu_adc g_sNuADC =
{
    .name = "adc",
    .OpFreqKHz = 4000,   /* 1000 <= OpFreqKHz <= 4000 */
    .chn_num = 8,
    .irqn = IRQ_ADC,
    .rstidx = ADCRST,
    .clkidx = ADCCKEN,
    .chn_mask = 0
};

static void nu_adc_isr(int vector, void *param)
{
    uint32_t isr, conf;
    nu_adc_t psNuAdc = (nu_adc_t)param;

    conf = inpw(REG_ADC_CONF);
    isr = inpw(REG_ADC_ISR);

    if ((isr & ADC_ISR_NACF) && (conf & ADC_CONF_NACEN))
    {
        outpw(REG_ADC_ISR, ADC_ISR_NACF);
    }

    if (isr & ADC_ISR_MF)
    {
        rt_err_t result;
        outpw(REG_ADC_ISR, ADC_ISR_MF);
        result = rt_sem_release(psNuAdc->m_psSem);
        RT_ASSERT(result == RT_EOK);
    }
}

static rt_err_t _nu_adc_init(rt_device_t dev)
{
    uint32_t div;
    nu_adc_t psNuAdc = (nu_adc_t)dev;

    /* ADC Engine Clock is set to freq Khz */
    if (psNuAdc->OpFreqKHz > 4000) psNuAdc->OpFreqKHz = 4000;
    if (psNuAdc->OpFreqKHz < 1000) psNuAdc->OpFreqKHz = 1000;

    div = 12000 / psNuAdc->OpFreqKHz;

    outpw(REG_CLK_DIVCTL7, inpw(REG_CLK_DIVCTL7) & ~((0x3 << 19) | (0x7 << 16) | (0xFFul << 24)));
    outpw(REG_CLK_DIVCTL7, (0 << 19) | (0 << 16) | ((div - 1) << 24));

    /* Install interrupt service routine */
    rt_hw_interrupt_install(psNuAdc->irqn, nu_adc_isr, (void *)psNuAdc, psNuAdc->name);

    return RT_EOK;
}

static rt_err_t _nu_adc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t ret = RT_EINVAL ;
    nu_adc_t psNuAdc = (nu_adc_t)dev;

    switch (cmd)
    {
    case START_MST:  /* Menu Start Conversion */
    {
        /* Enable interrupt */
        outpw(REG_ADC_IER, inpw(REG_ADC_IER) | ADC_IER_MIEN);

        /* Start conversion */
        outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) | ADC_CTL_MST);

        /* Wait it done */
        ret = rt_sem_take(psNuAdc->m_psSem, RT_WAITING_FOREVER);
        RT_ASSERT(ret == RT_EOK);

        /* Get data: valid data is 12-bit */
        *((uint32_t *)args) = inpw(REG_ADC_DATA) & 0x00000FFF;
    }
    break;
    case VBPOWER_ON: /* Enable ADC Internal Bandgap Power */
    {
        outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) | ADC_CTL_VBGEN);
    }
    break;
    case VBPOWER_OFF: /* Disable ADC Internal Bandgap Power */
    {
        outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) & ~ADC_CTL_VBGEN);
    }
    break;
    case NAC_ON: /* Enable Normal AD Conversion */
    {
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) | ADC_CONF_NACEN | ADC_CONF_REFSEL_AVDD33);
    }
    break;
    case NAC_OFF: /* Disable Normal AD Conversion */
    {
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) & ~ADC_CONF_NACEN);
    }
    break;
    case SWITCH_CH:
    {
        int chn = (int)args;
        if (chn >= psNuAdc->chn_num)
        {
            return -ret;
        }
        outpw(REG_ADC_CONF, (inpw(REG_ADC_CONF) & ~ADC_CONF_CHSEL_Msk) | (chn << ADC_CONF_CHSEL_Pos));
    }
    break;

    default:
        return -(ret);
    }

    return RT_EOK;
}

static rt_err_t _nu_adc_open(rt_device_t dev, rt_uint16_t oflag)
{
    nu_adc_t psNuAdc = (nu_adc_t)dev;

    /* Enable ADC engine clock */
    nu_sys_ipclk_enable(psNuAdc->clkidx);

    /* Reset the ADC IP */
    nu_sys_ip_reset(psNuAdc->rstidx);

    /* Enable ADC Power */
    outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) | ADC_CTL_ADEN);

    /* Enable ADC to high speed mode */
    outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) | ADC_CONF_HSPEED);

    /* Enable interrupt */
    rt_hw_interrupt_umask(psNuAdc->irqn);

    /* Enable Normal AD Conversion */
    _nu_adc_control(dev, NAC_ON, RT_NULL);

    return RT_EOK;
}

static rt_err_t _nu_adc_close(rt_device_t dev)
{
    nu_adc_t psNuAdc = (nu_adc_t)dev;

    /* Disable Normal AD Conversion */
    _nu_adc_control(dev, NAC_OFF, RT_NULL);

    /* Disable interrupt */
    rt_hw_interrupt_mask(psNuAdc->irqn);

    /* Disable ADC Power */
    outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) & ~ADC_CTL_ADEN);

    /* Disable ADC engine clock */
    nu_sys_ipclk_disable(psNuAdc->clkidx);

    return RT_EOK;
}

static const struct rt_adc_ops nu_adc_ops =
{
    nu_adc_enabled,
    nu_adc_convert,
};

/* nu_adc_enabled - Enable ADC clock and wait for ready */
static rt_err_t nu_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    nu_adc_t psNuADC = (nu_adc_t)device;
    RT_ASSERT(device != RT_NULL);

    if (channel >= psNuADC->chn_num)
        return -(RT_EINVAL);

    if (enabled)
    {
        psNuADC->chn_mask |= (1 << channel);
    }
    else
    {
        psNuADC->chn_mask &= ~(1 << channel);
    }

    if (psNuADC->chn_mask > 0 && ((rt_device_t)device)->ref_count == 0)
    {
        _nu_adc_open((rt_device_t)device, 0);
        ((rt_device_t)device)->ref_count = 1;
    }
    else if ((psNuADC->chn_mask == 0) && ((rt_device_t)device)->ref_count == 1)
    {
        _nu_adc_close((rt_device_t)device);
        ((rt_device_t)device)->ref_count = 0;
    }
    return RT_EOK;
}

static rt_err_t nu_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    rt_err_t ret = RT_EOK;
    nu_adc_t psNuAdc = (nu_adc_t)device;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    if (channel >= psNuAdc->chn_num)
    {
        ret = RT_EINVAL;
        goto exit_nu_adc_convert;
    }
    else if ((ret = _nu_adc_control((rt_device_t)device, SWITCH_CH, (void *)channel)) != RT_EOK)
    {
        goto exit_nu_adc_convert;
    }
    else if ((ret = _nu_adc_control((rt_device_t)device, START_MST, (void *)value)) != RT_EOK)
    {
        goto exit_nu_adc_convert;
    }

exit_nu_adc_convert:

    return (-ret) ;
}

int rt_hw_adc_init(void)
{
    rt_err_t result = RT_ERROR;
    rt_device_t psDev = &g_sNuADC.dev.parent;

    result = rt_hw_adc_register(&g_sNuADC.dev, g_sNuADC.name, &nu_adc_ops, &g_sNuADC);
    RT_ASSERT(result == RT_EOK);

    result = _nu_adc_init(psDev);
    RT_ASSERT(result == RT_EOK);

    g_sNuADC.m_psSem = rt_sem_create("adc_mst_sem", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(g_sNuADC.m_psSem != RT_NULL);

    return (int)result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif //#if defined(BSP_USING_EADC)
