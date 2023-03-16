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
#define TOUCH_MQ_LENGTH      64

/* Private Typedef --------------------------------------------------------------*/
struct nu_adc
{
    struct rt_adc_device dev;
    char *name;
    ADC_T *base;
    uint32_t bReset;
    IRQn_Type irqn;
    E_SYS_IPRST rstidx;
    E_SYS_IPCLK clkidx;
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
    .base = (ADC_T *)ADC_BA,
    .bReset = 1,
    .irqn = IRQ_ADC,
    .rstidx = ADCRST,
    .clkidx = ADCCKEN,
    .chn_mask = 0
};

static void nu_adc_isr(int vector, void *param)
{
    volatile rt_int32_t isr, wkisr;
    nu_adc_t psNuAdc = (nu_adc_t)param;
    rt_int32_t irqidx;
    ADC_T  *adc = psNuAdc->base;

    //rt_kprintf("[%s %d] CTL: %08x CONF:%08x IER:%08x ISR:%08x\n", __func__, __LINE__, adc->CTL, adc->CONF, adc->IER, adc->ISR);

    isr = adc->ISR;
    wkisr = adc->WKISR;

    adc->ISR = isr;

    while ((irqidx = nu_ctz(isr)) < eAdc_ISR_CNT)
    {
        uint32_t u32IsrBitMask =  1 << irqidx ;

        if (psNuAdc->m_isr[irqidx].cbfunc != RT_NULL)
        {
            // rt_kprintf("[%s] %d %x\n", __func__, irqidx, psNuAdc->m_isr[irqidx].cbfunc);
            psNuAdc->m_isr[irqidx].cbfunc(isr, psNuAdc->m_isr[irqidx].private_data);
        }

        /* Clear sent bit */
        isr &= ~(u32IsrBitMask);
    } //while

    while ((irqidx = nu_ctz(wkisr)) < eAdc_WKISR_CNT)
    {
        uint32_t u32IsrBitMask = 1 << irqidx ;

        if (psNuAdc->m_wkisr[irqidx].cbfunc != RT_NULL)
        {
            psNuAdc->m_wkisr[irqidx].cbfunc(wkisr, psNuAdc->m_wkisr[irqidx].private_data);
        }

        wkisr &= ~(u32IsrBitMask);
    } //while
}


#define DEF_ADC_SRC_CLOCK_DIV  (12000 / 1000)
static rt_err_t _nu_adc_init(rt_device_t dev)
{
    nu_adc_t psNuAdc = (nu_adc_t)dev;

    /* Set ADC Engine Clock */
    outpw(REG_CLK_DIVCTL7, inpw(REG_CLK_DIVCTL7) & ~((0x3 << 19) | (0x7 << 16) | (0xFFul << 24)));
    outpw(REG_CLK_DIVCTL7, (0 << 19) | (0 << 16) | ((DEF_ADC_SRC_CLOCK_DIV - 1) << 24));

    /* Install interrupt service routine */
    rt_hw_interrupt_install(psNuAdc->irqn, nu_adc_isr, (void *)psNuAdc, psNuAdc->name);

    return RT_EOK;
}

#define ADC_TOUCH_Z0_ACTIVE 20
static int32_t AdcMenuStartCallback(uint32_t status, uint32_t userData)
{
    nu_adc_t psNuAdc = (nu_adc_t)userData;

#if defined(BSP_USING_ADC_TOUCH)
    ADC_T  *adc = psNuAdc->base;
    static struct nu_adc_touch_data point;
    static rt_bool_t bDrop = RT_FALSE;
    static uint32_t u32LastZ0 = 0xffffu;

    if (psNuAdc->psRtTouch != RT_NULL)
    {
        point.u32X = ADC_GET_CONVERSION_XDATA(adc);
        point.u32Y = ADC_GET_CONVERSION_YDATA(adc);

        point.u32Z0 = ADC_GET_CONVERSION_Z1DATA(adc);
        point.u32Z1 = ADC_GET_CONVERSION_Z2DATA(adc);

        //rt_kprintf("x=%d y=%d z0=%d z1=%d\n", point.u32X, point.u32Y, point.u32Z0, point.u32Z1);
        /* Trigger next or not. */
        if (point.u32Z0 < ADC_TOUCH_Z0_ACTIVE)
        {
            /* Stop sampling procedure. */
            rt_timer_stop(g_sNuADC.psRtTouchMenuTimer);

            /* Re-start pendown detection */
            nu_adc_touch_detect(RT_TRUE);

            psNuAdc->bReset = 1;

            bDrop = RT_TRUE;
        }
        else
        {
            bDrop = RT_FALSE;
        }

        /* Notify upper layer. */
        if ((!bDrop || (u32LastZ0 > ADC_TOUCH_Z0_ACTIVE)) && rt_mq_send(psNuAdc->m_pmqTouchXYZ, (const void *)&point, sizeof(struct nu_adc_touch_data)) == RT_EOK)
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

static void nu_adc_touch_antiglitch(ADC_T  *adc)
{
    int count = 10;
    do
    {
        rt_hw_us_delay(1000); // 1ms
        ADC_CLR_INT_FLAG(adc, adc->ISR);
        if (adc->ISR == 0)
            break;
    }
    while (count-- > 0);
}

void nu_adc_touch_detect(rt_bool_t bStartDetect)
{
    nu_adc_t psNuAdc = (nu_adc_t)&g_sNuADC;
    ADC_T  *adc = psNuAdc->base;

    /* Disable interrupt */
    rt_hw_interrupt_mask(psNuAdc->irqn);

    ADC_POWER_DOWN(adc);

    /* Disable interrupt */
    ADC_DISABLE_INT(adc, ADC_IER_PEDEIEN_Msk | ADC_IER_MIEN_Msk);
    nu_adc_touch_antiglitch(adc);

    if (bStartDetect == RT_TRUE)
    {
        /* Switch to PenDown detection mode */
        ADC_DETECT_PD_MODE(adc);
        nu_adc_touch_antiglitch(adc);

        /* Enable interrupt */
        ADC_ENABLE_INT(adc, ADC_IER_PEDEIEN_Msk);
    }
    else
    {
        /* Switch to XY coordination converting mode */
        ADC_CONVERT_XY_MODE(adc);
        nu_adc_touch_antiglitch(adc);

        /* Enable interrupt */
        ADC_ENABLE_INT(adc, ADC_IER_MIEN_Msk);
    }

    ADC_POWER_ON(adc);

    /* Enable interrupt */
    rt_hw_interrupt_umask(psNuAdc->irqn);
}

static int32_t PenDownCallback(uint32_t status, uint32_t userData)
{
    nu_adc_t psNuAdc = (nu_adc_t)userData;
    return rt_timer_start(psNuAdc->psRtTouchMenuTimer);
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

rt_err_t nu_adc_touch_enable(rt_touch_t psRtTouch)
{
    nu_adc_t psNuAdc = (nu_adc_t)&g_sNuADC;
    nu_adc_cb sNuAdcCb;
    ADC_T  *adc = psNuAdc->base;

    adc->CONF = 0x0;

    rt_adc_enable((rt_adc_device_t)psNuAdc, 4);  //Channel number 4
    rt_adc_enable((rt_adc_device_t)psNuAdc, 5);  //Channel number 5
    rt_adc_enable((rt_adc_device_t)psNuAdc, 6);  //Channel number 6
    rt_adc_enable((rt_adc_device_t)psNuAdc, 7);  //Channel number 7

    /* Register touch device. */
    psNuAdc->psRtTouch = psRtTouch;

    /* Register PenDown callback. */
    sNuAdcCb.cbfunc = PenDownCallback;
    sNuAdcCb.private_data = (rt_uint32_t)psNuAdc;
    rt_memcpy(&psNuAdc->m_isr[eAdc_PEDEF], &sNuAdcCb, sizeof(nu_adc_cb));

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

    rt_adc_disable((rt_adc_device_t)psNuAdc, 4);  //Channel number 4
    rt_adc_disable((rt_adc_device_t)psNuAdc, 5);  //Channel number 5
    rt_adc_disable((rt_adc_device_t)psNuAdc, 6);  //Channel number 6
    rt_adc_disable((rt_adc_device_t)psNuAdc, 7);  //Channel number 7

    return RT_EOK;
}

static void nu_adc_touch_smpl(void *p)
{
    nu_adc_t psNuAdc = (nu_adc_t)p;
    if (psNuAdc->bReset)
    {
        psNuAdc->bReset = 0;
        nu_adc_touch_detect(RT_FALSE);
    }

    /* Start conversion */
    ADC_START_CONV(psNuAdc->base);
}
#endif

static rt_err_t _nu_adc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t ret = -RT_EINVAL ;
    nu_adc_t psNuAdc = (nu_adc_t)dev;
    ADC_T  *adc = psNuAdc->base;

    nu_adc_cb_t psAdcCb = (nu_adc_cb_t)args;

    switch (cmd)
    {
    case START_MST:  /* Menu Start Conversion */
    {
        /* Enable interrupt */
        ADC_ENABLE_INT(adc, ADC_IER_MIEN_Msk);

        /* Start conversion */
        ADC_START_CONV(adc);

        /* Wait it done */
        ret = rt_sem_take(psNuAdc->m_psSem, RT_WAITING_FOREVER);
        RT_ASSERT(ret == RT_EOK);

        /* Get data: valid data is 12-bit */
        if (args != RT_NULL)
            *((uint32_t *)args) = ADC_GET_CONVERSION_DATA(adc, 0);
    }
    break;

    case WKT_ON: /* Enable Touch Wake Up */
    {
        if (psAdcCb)
        {
            rt_memcpy(&psNuAdc->m_wkisr[eAdc_WPEDEF], psAdcCb, sizeof(nu_adc_cb));
        }
        adc->CTL |= ADC_CTL_WKTEN_Msk;
        adc->IER |= ADC_IER_WKTIEN_Msk;

        //TODO outpw(REG_SYS_WKUPSER, inpw(REG_SYS_WKUPSER) | (1 << 26));
    }
    break;

    case WKT_OFF:  /* Disable Touch Wake Up */
    {
        adc->CTL &= ~ADC_CTL_WKTEN_Msk;
        adc->IER &= ~ADC_IER_WKTIEN_Msk;

        //TODO outpw(REG_SYS_WKUPSER, inpw(REG_SYS_WKUPSER) & ~(1 << 26));
    }
    break;

    case SWITCH_5WIRE_ON:   /* Wire Mode Switch to 5-Wire */
    {
        adc->CTL |= ADC_CTL_WMSWCH_Msk;
    }
    break;

    case SWITCH_5WIRE_OFF:  /* Wire Mode Switch to 4-Wire */
    {
        adc->CTL &= ~ADC_CTL_WMSWCH_Msk;
    }
    break;

    case T_ON:   /* Enable Touch detection function */
    {
        adc->CONF |= ADC_CONF_TEN_Msk;
    }
    break;

    case T_OFF:   /* Disable Touch detection function */
    {
        adc->CONF &= ~ADC_CONF_TEN_Msk;
    }
    break;

    case TAVG_ON:   /* Enable Touch Mean average for X and Y function */
    {
        adc->CONF |= ADC_CONF_TMAVDIS_Msk;
    }
    break;

    case TAVG_OFF:   /* Disable Touch Mean average for X and Y function */
    {
        adc->CONF &= ~ADC_CONF_TMAVDIS_Msk;
    }
    break;

    case Z_ON:   /* Enable Press measure function */
    {
        adc->CONF |= ADC_CONF_ZEN_Msk;
    }
    break;

    case Z_OFF:   /* Disable Press measure function */
    {
        adc->CONF &= ~ADC_CONF_ZEN_Msk;
#if defined(BSP_USING_ADC_TOUCH)
        rt_mq_control(psNuAdc->m_pmqTouchXYZ, RT_IPC_CMD_RESET, RT_NULL);
#endif
    }
    break;

    case TZAVG_ON:   /* Enable Pressure Mean average for Z1 and Z2 function */
    {
        adc->CONF |= ADC_CONF_ZMAVDIS_Msk;
    }
    break;

    case TZAVG_OFF:   /* Disable Pressure Mean average for Z1 and Z2 function */
    {
        adc->CONF &= ~ADC_CONF_ZMAVDIS_Msk;
    }
    break;

    case NAC_ON: /* Enable Normal AD Conversion */
    {
        adc->CONF |= (ADC_CONF_NACEN_Msk | ADC_CONF_REFSEL_AVDD33);
    }
    break;

    case NAC_OFF: /* Disable Normal AD Conversion */
    {
        adc->CONF &= ~ADC_CONF_NACEN_Msk;
    }
    break;

    case SWITCH_CH:
    {
        int chn = (int)args;
        if (chn >= ADC_CH_NUM)
        {
            return -ret;
        }
        adc->CONF &= ~ADC_CONF_CHSEL_Msk;
        adc->CONF |= (chn << ADC_CONF_CHSEL_Pos);
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
    ADC_T  *adc = psNuAdc->base;

    /* Enable ADC engine clock */
    nu_sys_ipclk_enable(psNuAdc->clkidx);

    /* Reset the ADC IP */
    nu_sys_ip_reset(psNuAdc->rstidx);

    /* Enable ADC Power */
    ADC_POWER_ON(adc);

    /* Enable ADC to high speed mode */
    adc->CONF |= ADC_CONF_SPEED_Msk;

    /* Enable interrupt */
    rt_hw_interrupt_umask(psNuAdc->irqn);

    /* Enable Normal AD Conversion */
    _nu_adc_control(dev, NAC_ON, RT_NULL);

    return RT_EOK;
}

static rt_err_t _nu_adc_close(rt_device_t dev)
{
    nu_adc_t psNuAdc = (nu_adc_t)dev;
    ADC_T  *adc = psNuAdc->base;

    /* Disable Normal AD Conversion */
    _nu_adc_control(dev, NAC_OFF, RT_NULL);

    /* Disable interrupt */
    rt_hw_interrupt_mask(psNuAdc->irqn);

    /* Disable ADC Power */
    ADC_POWER_DOWN(adc);

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
    RT_ASSERT(device);

    if (channel >= ADC_CH_NUM)
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

    RT_ASSERT(device);
    RT_ASSERT(value);

    if (channel >= ADC_CH_NUM)
    {
        ret = -RT_EINVAL;
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
    RT_ASSERT(g_sNuADC.m_psSem);

#if defined(BSP_USING_ADC_TOUCH)
    g_sNuADC.m_pmqTouchXYZ = rt_mq_create("ADC_TOUCH_XYZ", sizeof(struct nu_adc_touch_data), TOUCH_MQ_LENGTH, RT_IPC_FLAG_FIFO);
    RT_ASSERT(g_sNuADC.m_pmqTouchXYZ);

    g_sNuADC.psRtTouchMenuTimer = rt_timer_create("TOUCH_SMPL_TIMER", nu_adc_touch_smpl, (void *)&g_sNuADC, DEF_ADC_TOUCH_SMPL_TICK, RT_TIMER_FLAG_PERIODIC);
    RT_ASSERT(g_sNuADC.psRtTouchMenuTimer);
#endif

    rt_memset(&g_sNuADC.m_isr, 0, sizeof(g_sNuADC.m_isr));
    rt_memset(&g_sNuADC.m_wkisr, 0, sizeof(g_sNuADC.m_wkisr));

    g_sNuADC.m_isr[eAdc_MF].cbfunc = AdcMenuStartCallback;
    g_sNuADC.m_isr[eAdc_MF].private_data = (uint32_t)&g_sNuADC;

    return (int)result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif //#if defined(BSP_USING_ADC)
