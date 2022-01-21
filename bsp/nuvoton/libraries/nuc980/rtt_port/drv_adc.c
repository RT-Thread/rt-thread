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
#include "drv_sys.h"
#include "nu_bitutil.h"
#include "drv_adc.h"

/* Private define ---------------------------------------------------------------*/
#define DEF_ADC_TOUCH_SMPL_TICK  40

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

#if defined(BSP_USING_ADC_TOUCH)
    rt_touch_t psRtTouch;
    rt_timer_t psRtTouchMenuTimer;
    rt_mq_t m_pmqTouchXYZ;
#endif

    nu_adc_cb m_isr[eAdc_ISR_CNT];
    nu_adc_cb m_wkisr[eAdc_WKISR_CNT];
};
typedef struct nu_adc *nu_adc_t;

#if defined(BSP_USING_ADC_TOUCH)
struct nu_adc_touch_data
{
    uint32_t    u32X;
    uint32_t    u32Y;
    uint32_t    u32Z0;
    uint32_t    u32Z1;
};
typedef struct nu_adc_touch_data *nu_adc_touch_data_t;
#endif

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled);
static rt_err_t nu_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value);
static rt_err_t _nu_adc_control(rt_device_t dev, int cmd, void *args);

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
    rt_int32_t isr, wkisr;
    nu_adc_t psNuAdc = (nu_adc_t)param;
    rt_int32_t irqidx;

    isr = inpw(REG_ADC_ISR);
    wkisr = inpw(REG_ADC_WKISR);

    while ((irqidx = nu_ctz(isr)) < eAdc_ISR_CNT)
    {
        uint32_t u32IsrBitMask =  1 << irqidx ;

        if (psNuAdc->m_isr[irqidx].cbfunc != RT_NULL)
        {
            //rt_kprintf("[%s] %d %x\n", __func__, irqidx, psNuAdc->m_isr[irqidx].cbfunc);
            psNuAdc->m_isr[irqidx].cbfunc(isr, psNuAdc->m_isr[irqidx].private_data);
        }

        /* Clear sent bit */
        outpw(REG_ADC_ISR, u32IsrBitMask);
        isr &= ~(u32IsrBitMask);
    } //while

    while ((irqidx = nu_ctz(wkisr)) < eAdc_WKISR_CNT)
    {
        uint32_t u32IsrBitMask = 1 << irqidx ;

        if (psNuAdc->m_wkisr[irqidx].cbfunc != RT_NULL)
        {
            psNuAdc->m_wkisr[irqidx].cbfunc(wkisr, psNuAdc->m_wkisr[irqidx].private_data);
        }

        /* Clear sent bit */
        outpw(REG_ADC_WKISR, u32IsrBitMask);
        wkisr &= ~(u32IsrBitMask);
    } //while
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

static int32_t AdcMenuStartCallback(uint32_t status, uint32_t userData)
{
    nu_adc_t psNuAdc = (nu_adc_t)userData;

#if defined(BSP_USING_ADC_TOUCH)

    static struct nu_adc_touch_data point;
    static rt_bool_t bDrop = RT_FALSE;
    static uint32_t u32LastZ0 = 0xffffu;

    if (psNuAdc->psRtTouch != RT_NULL)
    {
        uint32_t value;

        value = inpw(REG_ADC_XYDATA);
        point.u32X = (value & 0x0ffful);
        point.u32Y = ((value >> 16) & 0x0ffful);

        value = inpw(REG_ADC_ZDATA);
        point.u32Z0 = (value & 0x0ffful);
        point.u32Z1 = ((value >> 16) & 0x0ffful);

        /* Trigger next or not. */
        if (point.u32Z0 == 0)
        {
            /* Stop sampling procedure. */
            rt_timer_stop(g_sNuADC.psRtTouchMenuTimer);

            /* Re-start pendown detection */
            nu_adc_touch_detect(RT_TRUE);

            bDrop = RT_TRUE;
        }
        else
        {
            bDrop = RT_FALSE;
        }

        /* Notify upper layer. */
        if ((!bDrop || (u32LastZ0 != 0)) && rt_mq_send(psNuAdc->m_pmqTouchXYZ, (const void *)&point, sizeof(struct nu_adc_touch_data)) == RT_EOK)
        {
            rt_hw_touch_isr(psNuAdc->psRtTouch);
        }

        u32LastZ0 = point.u32Z0;
    }
    else
#endif
    {
        rt_err_t result = rt_sem_release(psNuAdc->m_psSem);
        RT_ASSERT(result == RT_EOK);
    }

    return 0;
}

#if defined(BSP_USING_ADC_TOUCH)

void nu_adc_touch_detect(rt_bool_t bStartDetect)
{
    nu_adc_t psNuAdc = (nu_adc_t)&g_sNuADC;

    if (bStartDetect)
    {
        /* Start detect PenDown */
        _nu_adc_control((rt_device_t)psNuAdc, PEPOWER_ON, RT_NULL);
    }
    else
    {
        /* Stop detect PenDown */
        _nu_adc_control((rt_device_t)psNuAdc, PEPOWER_OFF, RT_NULL);
    }
}

static int32_t PenDownCallback(uint32_t status, uint32_t userData)
{
    nu_adc_touch_detect(RT_FALSE);

    rt_timer_start(g_sNuADC.psRtTouchMenuTimer);

    return 0;
}

int32_t nu_adc_touch_read_xyz(uint32_t *bufX, uint32_t *bufY, uint32_t *bufZ0, uint32_t *bufZ1, int32_t dataCnt)
{
    int i;
    struct nu_adc_touch_data value;

    for (i = 0 ; i < dataCnt; i++)
    {
        if (rt_mq_recv(g_sNuADC.m_pmqTouchXYZ, (void *)&value, sizeof(struct nu_adc_touch_data), 0) == -RT_ETIMEOUT)
            break;

        bufX[i]  = value.u32X;
        bufY[i]  = value.u32Y;
        bufZ0[i] = value.u32Z0;
        bufZ1[i] = value.u32Z1;
    }
    return i;
}

void nu_adc_touch_start_conv(void)
{
    nu_adc_t psNuAdc = (nu_adc_t)&g_sNuADC;
    _nu_adc_control((rt_device_t)psNuAdc, START_MST, RT_NULL);
}

rt_err_t nu_adc_touch_enable(rt_touch_t psRtTouch)
{
    nu_adc_t psNuAdc = (nu_adc_t)&g_sNuADC;
    nu_adc_cb sNuAdcCb;

    rt_adc_enable((rt_adc_device_t)psNuAdc, 4);
    rt_adc_enable((rt_adc_device_t)psNuAdc, 5);
    rt_adc_enable((rt_adc_device_t)psNuAdc, 6);
    rt_adc_enable((rt_adc_device_t)psNuAdc, 7);

    outpw(REG_ADC_CONF, (inpw(REG_ADC_CONF) & ~(0xfful << 24)) | 0xfful << 24);

    /* Register touch device. */
    psNuAdc->psRtTouch = psRtTouch;

    /* Enable TouchXY. */
    _nu_adc_control((rt_device_t)psNuAdc, T_ON, RT_NULL);

    /* Enable TouchZZ. */
    _nu_adc_control((rt_device_t)psNuAdc, Z_ON, RT_NULL);

    /* Register PenDown callback. */
    sNuAdcCb.cbfunc = PenDownCallback;
    sNuAdcCb.private_data = (rt_uint32_t)psRtTouch;
    _nu_adc_control((rt_device_t)psNuAdc, PEDEF_ON, (void *)&sNuAdcCb);

    nu_adc_touch_detect(RT_TRUE);

    return RT_EOK;
}

rt_err_t nu_adc_touch_disable(void)
{
    nu_adc_t psNuAdc = (nu_adc_t)&g_sNuADC;

    nu_adc_touch_detect(RT_FALSE);

    _nu_adc_control((rt_device_t)psNuAdc, T_OFF, RT_NULL);
    _nu_adc_control((rt_device_t)psNuAdc, Z_OFF, RT_NULL);
    _nu_adc_control((rt_device_t)psNuAdc, PEDEF_OFF, RT_NULL);

    rt_adc_disable((rt_adc_device_t)psNuAdc, 4);
    rt_adc_disable((rt_adc_device_t)psNuAdc, 5);
    rt_adc_disable((rt_adc_device_t)psNuAdc, 6);
    rt_adc_disable((rt_adc_device_t)psNuAdc, 7);

    return RT_EOK;
}

#endif

static rt_err_t _nu_adc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t ret = RT_EINVAL ;
    nu_adc_t psNuAdc = (nu_adc_t)dev;

    nu_adc_cb_t psAdcCb = (nu_adc_cb_t)args;

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
        if (args != RT_NULL)
            *((uint32_t *)args) = inpw(REG_ADC_DATA) & 0x00000FFF;
    }
    break;

    /* case START_MST_POLLING:  Not supported. */

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

    case KPPOWER_ON: /* Enable ADC Keypad Power */
    {
        outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) | ADC_CTL_PWKPEN);
    }
    break;

    case KPPOWER_OFF: /* Disable ADC Keypad Power */
    {
        outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) & ~ADC_CTL_PWKPEN);
    }
    break;

    case PEPOWER_ON: /* Enable Pen Power */
    {
        int retry = 100;
        uint32_t treg = inpw(REG_ADC_IER);
        outpw(REG_ADC_IER, treg & ~(ADC_IER_PEDEIEN | ADC_IER_PEUEIEN));
        outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) | ADC_CTL_PEDEEN);
        do
        {
            outpw(REG_ADC_ISR, ADC_ISR_PEDEF | ADC_ISR_PEUEF);
            rt_thread_mdelay(1);
            if (retry-- == 0)
                break;
        }
        while (inpw(REG_ADC_ISR) & (ADC_ISR_PEDEF | ADC_ISR_PEUEF));
        outpw(REG_ADC_IER, treg);
    }
    break;

    case PEPOWER_OFF: /* Disable Pen Power */
    {
        outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) & ~ADC_CTL_PEDEEN);
    }
    break;

    case KPPRESS_ON:  /* Enable Keypad press event */
    {
        if (psAdcCb)
        {
            rt_memcpy(&psNuAdc->m_isr[eAdc_KPEF], psAdcCb, sizeof(nu_adc_cb));
        }
        outpw(REG_ADC_IER, inpw(REG_ADC_IER) | ADC_IER_KPEIEN);
    }
    break;

    case KPPRESS_OFF: /* Disable Keypad press event */
    {
        outpw(REG_ADC_IER, inpw(REG_ADC_IER & ~ADC_IER_KPEIEN));
    }
    break;

    case KPUP_ON:  /* Enable Keypad up event */
    {
        if (psAdcCb)
        {
            rt_memcpy(&psNuAdc->m_isr[eAdc_KPUEF], psAdcCb, sizeof(nu_adc_cb));
        }
        outpw(REG_ADC_IER, inpw(REG_ADC_IER) | ADC_IER_KPUEIEN);
    }
    break;

    case KPUP_OFF:  /* Disable Keypad up event */
    {
        outpw(REG_ADC_IER, inpw(REG_ADC_IER) & ~ADC_IER_KPUEIEN);
    }
    break;

    case PEDEF_ON:  /* Enable Pen Down Event */
    {
        if (psAdcCb)
        {
            rt_memcpy(&psNuAdc->m_isr[eAdc_PEDEF], psAdcCb, sizeof(nu_adc_cb));
        }
        outpw(REG_ADC_IER, inpw(REG_ADC_IER) | ADC_IER_PEDEIEN);
    }
    break;

    case PEDEF_OFF: /* Disable Pen Down Event */
    {
        outpw(REG_ADC_IER, inpw(REG_ADC_IER) & ~ADC_IER_PEDEIEN);
    }
    break;

    case WKP_ON:  /* Enable Keypad Press Wake Up */
    {
        if (psAdcCb)
        {
            rt_memcpy(&psNuAdc->m_wkisr[eAdc_WKPEF], psAdcCb, sizeof(nu_adc_cb));
        }

        outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) | ADC_CTL_WKPEN);
        outpw(REG_ADC_IER, inpw(REG_ADC_IER) | ADC_IER_WKPIEN);
        //outpw(REG_SYS_WKUPSER, inpw(REG_SYS_WKUPSER) | (1 << 26));
    }
    break;

    case WKP_OFF:  /* Disable Keypad Press Wake Up */
    {
        outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) & ~ADC_CTL_WKPEN);
        outpw(REG_ADC_IER, inpw(REG_ADC_IER) & ~ADC_IER_WKPIEN);
        //outpw(REG_SYS_WKUPSER, inpw(REG_SYS_WKUPSER) & ~(1 << 26));
    }
    break;

    case WKT_ON: /* Enable Touch Wake Up */
    {
        if (psAdcCb)
        {
            rt_memcpy(&psNuAdc->m_wkisr[eAdc_WPEDEF], psAdcCb, sizeof(nu_adc_cb));
        }

        outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) | ADC_CTL_WKTEN);
        outpw(REG_ADC_IER, inpw(REG_ADC_IER) | ADC_IER_WKTIEN);
        //outpw(REG_SYS_WKUPSER, inpw(REG_SYS_WKUPSER) | (1 << 26));
    }
    break;

    case WKT_OFF:  /* Disable Touch Wake Up */
    {
        outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) & ~ADC_CTL_WKTEN);
        outpw(REG_ADC_IER, inpw(REG_ADC_IER) & ~ADC_IER_WKTIEN);
        //outpw(REG_SYS_WKUPSER, inpw(REG_SYS_WKUPSER) & ~(1 << 26));
    }
    break;

    case SWITCH_5WIRE_ON:   /* Wire Mode Switch to 5-Wire */
    {
        outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) | ADC_CTL_WMSWCH);
    }
    break;

    case SWITCH_5WIRE_OFF:  /* Wire Mode Switch to 4-Wire */
    {
        outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) & ~ADC_CTL_WMSWCH);
    }
    break;

    case T_ON:   /* Enable Touch detection function */
    {
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) | ADC_CONF_TEN);
    }
    break;

    case T_OFF:   /* Disable Touch detection function */
    {
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) & ~ADC_CONF_TEN);
    }
    break;

    case TAVG_ON:   /* Enable Touch Mean average for X and Y function */
    {
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) | ADC_CONF_DISTMAVEN);
    }
    break;

    case TAVG_OFF:   /* Disable Touch Mean average for X and Y function */
    {
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) & ~ADC_CONF_DISTMAVEN);
    }
    break;

    case Z_ON:   /* Enable Press measure function */
    {
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) | ADC_CONF_ZEN);
    }
    break;

    case Z_OFF:   /* Disable Press measure function */
    {
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) & ~ADC_CONF_ZEN);
#if defined(BSP_USING_ADC_TOUCH)
        rt_mq_control(psNuAdc->m_pmqTouchXYZ, RT_IPC_CMD_RESET, RT_NULL);
#endif
    }
    break;

    case TZAVG_ON:   /* Enable Pressure Mean average for Z1 and Z2 function */
    {
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) | ADC_CONF_DISZMAVEN);
    }
    break;

    case TZAVG_OFF:   /* Disable Pressure Mean average for Z1 and Z2 function */
    {
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) & ~ADC_CONF_DISZMAVEN);
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

    case VBAT_ON:   /* Enable Voltage Battery Conversion */
    {
        if (psAdcCb)
        {
            rt_memcpy(&psNuAdc->m_isr[eAdc_VBF], psAdcCb, sizeof(nu_adc_cb));
        }
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) | ADC_CONF_VBATEN);
    }
    break;

    case VBAT_OFF:   /* Disable Voltage Battery */
    {
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) & ~ADC_CONF_VBATEN);
    }
    break;

    case KPCONV_ON:   /* Enable Keypad conversion function */
    {
        if (psAdcCb)
        {
            rt_memcpy(&psNuAdc->m_isr[eAdc_KPCF], psAdcCb, sizeof(nu_adc_cb));
        }
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) | ADC_CONF_KPCEN);
        outpw(REG_ADC_IER, inpw(REG_ADC_IER) | ADC_IER_KPEIEN);
    }
    break;

    case KPCONV_OFF:   /* Disable Keypad conversion function */
    {
        outpw(REG_ADC_CONF, inpw(REG_ADC_CONF) & ~ADC_CONF_KPCEN);
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

static void nu_adc_touch_smpl(void *p)
{
    /* Enable interrupt */
    outpw(REG_ADC_IER, inpw(REG_ADC_IER) | ADC_IER_MIEN);

    /* Start conversion */
    outpw(REG_ADC_CTL, inpw(REG_ADC_CTL) | ADC_CTL_MST);
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

#if defined(BSP_USING_ADC_TOUCH)
    g_sNuADC.m_pmqTouchXYZ = rt_mq_create("ADC_TOUCH_XYZ", sizeof(struct nu_adc_touch_data), TOUCH_MQ_LENGTH, RT_IPC_FLAG_FIFO);
    RT_ASSERT(g_sNuADC.m_pmqTouchXYZ != RT_NULL);

    g_sNuADC.psRtTouchMenuTimer = rt_timer_create("TOUCH_SMPL_TIMER", nu_adc_touch_smpl, (void *)&g_sNuADC, DEF_ADC_TOUCH_SMPL_TICK, RT_TIMER_FLAG_PERIODIC);
    RT_ASSERT(g_sNuADC.psRtTouchMenuTimer != RT_NULL);
#endif

    rt_memset(&g_sNuADC.m_isr, 0, sizeof(g_sNuADC.m_isr));
    rt_memset(&g_sNuADC.m_wkisr, 0, sizeof(g_sNuADC.m_wkisr));

    g_sNuADC.m_isr[eAdc_MF].cbfunc = AdcMenuStartCallback;
    g_sNuADC.m_isr[eAdc_MF].private_data = (UINT32)&g_sNuADC;

    return (int)result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif //#if defined(BSP_USING_ADC)
