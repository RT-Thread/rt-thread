/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-5-21       Philo            First version
*
******************************************************************************/
#include <rtconfig.h>

#if defined(BSP_USING_ECAP)
#include <rtdevice.h>
#include <NuMicro.h>

#define ECAP_CH0_POS    (0)
#define ECAP_CH1_POS    (1)
#define ECAP_CH2_POS    (2)

#define ECAP_CHANNEL_NUM    0x3
#define ECAP_CLK_DIV    ECAP_CAPTURE_TIMER_CLKDIV_32

/* Private typedef --------------------------------------------------------------*/
typedef struct _ecap_dev
{
    ECAP_T      *ecap_base;
    float       fUsPerTick;
} nu_ecap_dev_t;

typedef struct _ecap
{
    struct rt_inputcapture_device   parent;
    nu_ecap_dev_t *ecap_dev;
    uint8_t     u8Channel;
    rt_bool_t   bfirstData;
    uint32_t    u32CurrentCnt;
    uint32_t    u32LastCnt;
    rt_bool_t   input_data_level;
} nu_capture_t;

/* Private functions ------------------------------------------------------------*/
static  rt_err_t nu_capture_init(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_open(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_close(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);

/* Private define ---------------------------------------------------------------*/
#define NU_ECAP_GET_LEVEL(status, channel) ((status&(ECAP_STATUS_CAP0_Msk<<channel))?1:0)
#define ECAP_GET_CLK_DIV_INDEX(ecap) ((ecap)->CTL1 = ((ecap)->CTL1 & ECAP_CTL1_CLKSEL_Msk)>>ECAP_CTL1_CLKSEL_Pos)

/* Public functions -------------------------------------------------------------*/


/* Private variables ------------------------------------------------------------*/
#if (BSP_USING_ECAP0_CHMSK!=0)
static const char *nu_ecap0_device_name[ECAP_CHANNEL_NUM] = { "ecap0i0", "ecap0i1", "ecap0i2" };
static nu_capture_t *nu_ecap0_capture[ECAP_CHANNEL_NUM] = {0};
static nu_ecap_dev_t nu_ecap0_dev = {.ecap_base = ECAP0};
#endif

#if (BSP_USING_ECAP1_CHMSK!=0)
static const char *nu_ecap1_device_name[ECAP_CHANNEL_NUM] = { "ecap1i0", "ecap1i1", "ecap1i2" };
static nu_capture_t *nu_ecap1_capture[ECAP_CHANNEL_NUM] = {0};
static nu_ecap_dev_t nu_ecap1_dev = {.ecap_base = ECAP1};
#endif

static struct rt_inputcapture_ops nu_capture_ops =
{
    .init   =   nu_capture_init,
    .open   =   nu_capture_open,
    .close  =   nu_capture_close,
    .get_pulsewidth =   nu_capture_get_pulsewidth,
};

/* Functions define ------------------------------------------------------------*/
#if (BSP_USING_ECAP0_CHMSK!=0)
void ECAP0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uint32_t u32Status;

    /* Get input Capture status */
    u32Status = ECAP_GET_INT_STATUS(ECAP0);

#if (BSP_USING_ECAP0_CHMSK & (0x1<<ECAP_CH0_POS))
    /* Check input capture channel flag */
    if ((u32Status & ECAP_STATUS_CAPTF0_Msk) == ECAP_STATUS_CAPTF0_Msk)
    {
        /* Clear input capture channel flag */
        ECAP_CLR_CAPTURE_FLAG(ECAP0, ECAP_STATUS_CAPTF0_Msk);

        if (NU_ECAP_GET_LEVEL(u32Status, 0))
        {
            nu_ecap0_capture[0]->input_data_level = RT_FALSE;
        }
        else
        {
            nu_ecap0_capture[0]->input_data_level = RT_TRUE;
        }

        nu_ecap0_capture[0]->u32CurrentCnt   = ECAP_GET_CNT_HOLD_VALUE(ECAP0, ECAP_IC0);

        rt_hw_inputcapture_isr(&nu_ecap0_capture[0]->parent, nu_ecap0_capture[0]->input_data_level);
    }
#endif


#if (BSP_USING_ECAP0_CHMSK & (0x1<<ECAP_CH1_POS))
    /* Check input capture channel flag */
    if ((u32Status & ECAP_STATUS_CAPTF1_Msk) == ECAP_STATUS_CAPTF1_Msk)
    {
        /* Clear input capture channel  flag */
        ECAP_CLR_CAPTURE_FLAG(ECAP0, ECAP_STATUS_CAPTF1_Msk);

        if (NU_ECAP_GET_LEVEL(u32Status, 1))
        {
            nu_ecap0_capture[1]->input_data_level = RT_FALSE;
        }
        else
        {
            nu_ecap0_capture[1]->input_data_level = RT_TRUE;
        }

        nu_ecap0_capture[1]->u32CurrentCnt   = ECAP_GET_CNT_HOLD_VALUE(ECAP0, ECAP_IC1);

        rt_hw_inputcapture_isr(&nu_ecap0_capture[1]->parent, nu_ecap0_capture[1]->input_data_level);
    }
#endif

#if (BSP_USING_ECAP0_CHMSK & (0x1<<ECAP_CH2_POS))
    /* Check input capture channel flag */
    if ((u32Status & ECAP_STATUS_CAPTF2_Msk) == ECAP_STATUS_CAPTF2_Msk)
    {
        /* Clear input capture channel flag */
        ECAP_CLR_CAPTURE_FLAG(ECAP0, ECAP_STATUS_CAPTF2_Msk);

        if (NU_ECAP_GET_LEVEL(u32Status, 2))
        {
            nu_ecap0_capture[2]->input_data_level = RT_FALSE;
        }
        else
        {
            nu_ecap0_capture[2]->input_data_level = RT_TRUE;
        }

        nu_ecap0_capture[2]->u32CurrentCnt   = ECAP_GET_CNT_HOLD_VALUE(ECAP0, ECAP_IC2);

        rt_hw_inputcapture_isr(&nu_ecap0_capture[2]->parent, nu_ecap0_capture[2]->input_data_level);
    }
#endif
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif  //(BSP_USING_ECAP0_CHMSK!=0)


#if (BSP_USING_ECAP1_CHMSK!=0)
void ECAP1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uint32_t u32Status;

    /* Get input Capture status */
    u32Status = ECAP_GET_INT_STATUS(ECAP1);

#if (BSP_USING_ECAP1_CHMSK & (0x1<<ECAP_CH0_POS))
    /* Check input capture channel flag */
    if ((u32Status & ECAP_STATUS_CAPTF0_Msk) == ECAP_STATUS_CAPTF0_Msk)
    {
        /* Clear input capture channel flag */
        ECAP_CLR_CAPTURE_FLAG(ECAP1, ECAP_STATUS_CAPTF0_Msk);

        if (NU_ECAP_GET_LEVEL(u32Status, 0))
        {
            nu_ecap1_capture[0]->input_data_level = RT_FALSE;
        }
        else
        {
            nu_ecap1_capture[0]->input_data_level = RT_TRUE;
        }

        nu_ecap1_capture[0]->u32CurrentCnt = ECAP_GET_CNT_HOLD_VALUE(ECAP1, ECAP_IC0);

        rt_hw_inputcapture_isr(&nu_ecap1_capture[0]->parent, nu_ecap1_capture[0]->input_data_level);
    }
#endif


#if (BSP_USING_ECAP1_CHMSK & (0x1<<ECAP_CH1_POS))
    /* Check input capture channel flag */
    if ((u32Status & ECAP_STATUS_CAPTF1_Msk) == ECAP_STATUS_CAPTF1_Msk)
    {
        /* Clear input capture channel  flag */
        ECAP_CLR_CAPTURE_FLAG(ECAP1, ECAP_STATUS_CAPTF1_Msk);

        if (NU_ECAP_GET_LEVEL(u32Status, 1))
        {
            nu_ecap1_capture[1]->input_data_level = RT_FALSE;
        }
        else
        {
            nu_ecap1_capture[1]->input_data_level = RT_TRUE;
        }

        nu_ecap1_capture[1]->u32CurrentCnt = ECAP_GET_CNT_HOLD_VALUE(ECAP1, ECAP_IC1);

        rt_hw_inputcapture_isr(&nu_ecap1_capture[1]->parent, nu_ecap1_capture[1]->input_data_level);
    }
#endif

#if (BSP_USING_ECAP1_CHMSK & (0x1<<ECAP_CH2_POS))
    /* Check input capture channel flag */
    if ((u32Status & ECAP_STATUS_CAPTF2_Msk) == ECAP_STATUS_CAPTF2_Msk)
    {
        /* Clear input capture channel flag */
        ECAP_CLR_CAPTURE_FLAG(ECAP1, ECAP_STATUS_CAPTF2_Msk);

        if (NU_ECAP_GET_LEVEL(u32Status, 2))
        {
            nu_ecap1_capture[2]->input_data_level = RT_FALSE;
        }
        else
        {
            nu_ecap1_capture[2]->input_data_level = RT_TRUE;
        }

        nu_ecap1_capture[2]->u32CurrentCnt = ECAP_GET_CNT_HOLD_VALUE(ECAP1, ECAP_IC2);

        rt_hw_inputcapture_isr(&nu_ecap1_capture[2]->parent, nu_ecap1_capture[2]->input_data_level);
    }
#endif

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif  //(BSP_USING_ECAP1_CHMSK!=0)

static rt_err_t nu_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us)
{
    rt_err_t ret = RT_EOK;
    nu_capture_t *nu_capture;
    float fTempCnt;

    nu_capture = (nu_capture_t *)inputcapture;

    if (nu_capture->bfirstData)
    {
        nu_capture->bfirstData = RT_FALSE;
        ret = RT_ERROR;

        return -(ret);
    }

    if (nu_capture->u32CurrentCnt > nu_capture->u32LastCnt)
        fTempCnt = nu_capture->u32CurrentCnt - nu_capture->u32LastCnt;
    else    /* Overrun case */
        fTempCnt = nu_capture->u32CurrentCnt + ((0x1000000 - nu_capture->u32LastCnt) + 1);

    *pulsewidth_us =(int)(fTempCnt * nu_capture->ecap_dev->fUsPerTick);

    nu_capture->u32LastCnt = nu_capture->u32CurrentCnt;

    return -(ret);
}

static float get_ecap_tick_time_us(nu_capture_t *nu_capture)
{
    uint8_t u8ClockDivider[8] = { 1, 4, 16, 32, 64, 96, 112, 128};
    if (nu_capture->ecap_dev->ecap_base == ECAP0)
        return ((float)1000000 / ((float)CLK_GetPCLK0Freq() / u8ClockDivider[(nu_capture->ecap_dev->ecap_base->CTL1 & ECAP_CTL1_CLKSEL_Msk) >> ECAP_CTL1_CLKSEL_Pos]));
    else
        return ((float)1000000 / ((float)CLK_GetPCLK1Freq() / u8ClockDivider[(nu_capture->ecap_dev->ecap_base->CTL1 & ECAP_CTL1_CLKSEL_Msk) >> ECAP_CTL1_CLKSEL_Pos]));
}

static rt_err_t nu_ecap_init(nu_capture_t *nu_capture)
{
    rt_err_t ret = RT_ERROR;
    static rt_bool_t bECAP0Inited = RT_FALSE;
    static rt_bool_t bECAP1Inited = RT_FALSE;

    if (nu_capture->ecap_dev->ecap_base == ECAP0)
    {
        if (bECAP0Inited == RT_FALSE)
        {
            /* Enable ECAP0 clock */
            SYS_UnlockReg();
            CLK_EnableModuleClock(ECAP0_MODULE);
            SYS_LockReg();

            NVIC_EnableIRQ(ECAP0_IRQn);
            bECAP0Inited = RT_TRUE;
        }
        else
        {
            return ret = RT_EOK;
        }
    }
    else if (nu_capture->ecap_dev->ecap_base == ECAP1)
    {
        if (bECAP1Inited == RT_FALSE)
        {
            /* Enable ECAP1 clock */
            SYS_UnlockReg();
            CLK_EnableModuleClock(ECAP1_MODULE);
            SYS_LockReg();

            NVIC_EnableIRQ(ECAP1_IRQn);
            bECAP1Inited = RT_TRUE;
        }
        else
        {
            return ret = RT_EOK;
        }
    }
    else
    {
        return ret;
    }

    /* Enable ECAP */
    ECAP_Open(nu_capture->ecap_dev->ecap_base, ECAP_DISABLE_COMPARE);

    ECAP_SEL_TIMER_CLK_DIV(nu_capture->ecap_dev->ecap_base, ECAP_CLK_DIV);

    /* Select Reload function */
    ECAP_SET_CNT_CLEAR_EVENT(nu_capture->ecap_dev->ecap_base, ECAP_CTL1_OVRLDEN_Msk);

    /* Enable ECAP0 source IC */
    ECAP_SEL_INPUT_SRC(nu_capture->ecap_dev->ecap_base, ECAP_IC0, ECAP_CAP_INPUT_SRC_FROM_IC);
    ECAP_SEL_INPUT_SRC(nu_capture->ecap_dev->ecap_base, ECAP_IC1, ECAP_CAP_INPUT_SRC_FROM_IC);
    ECAP_SEL_INPUT_SRC(nu_capture->ecap_dev->ecap_base, ECAP_IC2, ECAP_CAP_INPUT_SRC_FROM_IC);

    /* Select IC detect rising edge */
    ECAP_SEL_CAPTURE_EDGE(nu_capture->ecap_dev->ecap_base, ECAP_IC0, ECAP_RISING_FALLING_EDGE);
    ECAP_SEL_CAPTURE_EDGE(nu_capture->ecap_dev->ecap_base, ECAP_IC1, ECAP_RISING_FALLING_EDGE);
    ECAP_SEL_CAPTURE_EDGE(nu_capture->ecap_dev->ecap_base, ECAP_IC2, ECAP_RISING_FALLING_EDGE);

    ret = RT_EOK;

    return -(ret);
}

static rt_err_t nu_capture_init(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;
    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    if (nu_ecap_init(nu_capture) != RT_EOK)
    {
        rt_kprintf("Failed to initialize ECAP.\n");
        ret = RT_ERROR;
    }

    return -(ret);
}

static rt_err_t nu_capture_open(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;
    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    nu_capture->ecap_dev->fUsPerTick = get_ecap_tick_time_us(nu_capture);

    /* Enable ECAP Input Channel */
    ECAP_ENABLE_INPUT_CHANNEL(nu_capture->ecap_dev->ecap_base, 0x1 << (ECAP_CTL0_IC0EN_Pos + nu_capture->u8Channel));

    /* Input Channel interrupt enabled */
    ECAP_EnableINT(nu_capture->ecap_dev->ecap_base, 0x1 << (ECAP_CTL0_CAPIEN0_Pos + nu_capture->u8Channel));

    /* ECAP_CNT starts up-counting */
    ECAP_CNT_START(nu_capture->ecap_dev->ecap_base);

    return ret;
}

static rt_err_t nu_capture_close(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;

    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    /* Input Channel interrupt disabled */
    ECAP_DisableINT(nu_capture->ecap_dev->ecap_base, 0x1 << (ECAP_CTL0_CAPIEN0_Pos + nu_capture->u8Channel));

    /* Disable ECAP Input Channel */
    ECAP_DISABLE_INPUT_CHANNEL(nu_capture->ecap_dev->ecap_base, 0x1 << (ECAP_CTL0_IC0EN_Pos + nu_capture->u8Channel));

    /* Clear input capture channel flag */
    ECAP_CLR_CAPTURE_FLAG(nu_capture->ecap_dev->ecap_base, 0x1 << (ECAP_STATUS_CAPTF0_Pos + nu_capture->u8Channel));

    return ret;
}

static void ecap_init(nu_capture_t *nu_capture, uint8_t u8Channel, nu_ecap_dev_t *ecap_dev, const char *device_name)
{
    nu_capture->ecap_dev = ecap_dev;
    nu_capture->u8Channel = u8Channel;
    nu_capture->bfirstData = RT_TRUE;
    nu_capture->u32CurrentCnt = 0;
    nu_capture->u32LastCnt = 0;
    nu_capture->parent.ops = &nu_capture_ops;

    /* register inputcapture device */
    rt_device_inputcapture_register(&nu_capture->parent, device_name, &nu_capture);
}

/* Init and register ecap capture */
static int nu_ecap_capture_device_init(void)
{
    for (int i = 0; i < ECAP_CHANNEL_NUM; i++)
    {
#if (BSP_USING_ECAP0_CHMSK!=0)
        if (BSP_USING_ECAP0_CHMSK & (0x1 << i))
        {
            nu_ecap0_capture[i] = (nu_capture_t*)rt_malloc(sizeof(nu_capture_t));
            ecap_init(nu_ecap0_capture[i], i, &nu_ecap0_dev, nu_ecap0_device_name[i]);
        }
#endif //#if (BSP_USING_ECAP0_CHMSK!=0)

#if (BSP_USING_ECAP1_CHMSK!=0)
        if (BSP_USING_ECAP1_CHMSK & (0x1 << i))
        {
            nu_ecap1_capture[i] = (nu_capture_t*)rt_malloc(sizeof(nu_capture_t));
            ecap_init(nu_ecap1_capture[i], i, &nu_ecap1_dev, nu_ecap1_device_name[i]);
        }
#endif //#if (BSP_USING_ECAP1_CHMSK!=0)
    }

    return 0;
}
INIT_DEVICE_EXPORT(nu_ecap_capture_device_init);

#endif //#if defined(BSP_USING_ECAP)
