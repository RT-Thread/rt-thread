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

#if defined(BSP_USING_TIMER_CAPTURE)

#include <rtdevice.h>
#include <NuMicro.h>

/* Private typedef --------------------------------------------------------------*/
typedef struct _timer
{
    struct rt_inputcapture_device   parent;
    TIMER_T     *timer;
    uint8_t     u8Channel;
    IRQn_Type   irq;
    uint32_t    u32CurrentCnt;
    rt_bool_t   input_data_level;
    rt_bool_t   first_edge;
} nu_capture_t;

/* Private functions ------------------------------------------------------------*/
static  rt_err_t nu_capture_init(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_open(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_close(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);

/* Private define ---------------------------------------------------------------*/
#define TIMER_CHANNEL_NUM   (4)

#define TIMER0_POS  (0)
#define TIMER1_POS  (1)
#define TIMER2_POS  (2)
#define TIMER3_POS  (3)

/* Timer prescale setting. Since it will affect the pulse width of measure, it is recommended to set to 2. */
#define PSC_DIV     (2)

/* Public functions -------------------------------------------------------------*/


/* Private variables ------------------------------------------------------------*/
static const char *nu_timer_device_name[TIMER_CHANNEL_NUM] = { "timer0i0", "timer1i0", "timer2i0", "timer3i0"};
static const IRQn_Type nu_timer_irq[TIMER_CHANNEL_NUM] = { TMR0_IRQn, TMR1_IRQn, TMR2_IRQn, TMR3_IRQn};
static TIMER_T *nu_timer_base[TIMER_CHANNEL_NUM] = { TIMER0, TIMER1, TIMER2, TIMER3};
static nu_capture_t *nu_timer_capture[TIMER_CHANNEL_NUM] = {0};

static struct rt_inputcapture_ops nu_capture_ops =
{
    .init   =   nu_capture_init,
    .open   =   nu_capture_open,
    .close  =   nu_capture_close,
    .get_pulsewidth =   nu_capture_get_pulsewidth,
};

/* Functions define ------------------------------------------------------------*/
void timer_interrupt_handler(nu_capture_t *nu_timer_capture)
{
    TIMER_ClearCaptureIntFlag(nu_timer_capture->timer);

    /* Frist event is rising edge */
    if (nu_timer_capture->first_edge == RT_TRUE)
    {
        nu_timer_capture->first_edge = RT_FALSE;
        nu_timer_capture->input_data_level = RT_FALSE;
    }
    else
    {
        nu_timer_capture->input_data_level = !nu_timer_capture->input_data_level;
        nu_timer_capture->u32CurrentCnt = TIMER_GetCaptureData(nu_timer_capture->timer);

        rt_hw_inputcapture_isr(&nu_timer_capture->parent, nu_timer_capture->input_data_level);
    }
}

#if defined(BSP_USING_TIMER0_CAPTURE)
void TMR0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    timer_interrupt_handler(nu_timer_capture[0]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif  //defined(BSP_USING_TIMER0_CAPTURE)

#if defined(BSP_USING_TIMER1_CAPTURE)
void TMR1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    timer_interrupt_handler(nu_timer_capture[1]);

    /* leave interrupt */
    rt_interrupt_leave();

}
#endif  //defined(BSP_USING_TIMER1_CAPTURE)

#if defined(BSP_USING_TIMER2_CAPTURE)
void TMR2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    timer_interrupt_handler(nu_timer_capture[2]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif  //defined(BSP_USING_TIMER2_CAPTURE)

#if defined(BSP_USING_TIMER3_CAPTURE)
void TMR3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    timer_interrupt_handler(nu_timer_capture[3]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif  //defined(BSP_USING_TIMER3_CAPTURE)

static rt_err_t nu_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us)
{
    rt_err_t ret = RT_EOK;
    nu_capture_t *nu_capture;

    nu_capture = (nu_capture_t *)inputcapture;

    *pulsewidth_us = nu_capture->u32CurrentCnt / PSC_DIV;

    return -(ret);
}

static rt_err_t nu_timer_init(nu_capture_t *nu_capture)
{
    rt_err_t ret = RT_ERROR;

    SYS_UnlockReg();

#if defined(BSP_USING_TIMER0_CAPTURE)
    if (nu_capture->timer == TIMER0)
    {
        /* Enable TIMER0 clock */
        CLK_EnableModuleClock(TMR0_MODULE);
        CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_PCLK0, 0);

        ret = RT_EOK;
        goto exit_nu_timer_init;
    }
#endif
#if defined(BSP_USING_TIMER1_CAPTURE)
    if (nu_capture->timer == TIMER1)
    {
        /* Enable TIMER1 clock */
        CLK_EnableModuleClock(TMR1_MODULE);
        CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_PCLK0, 0);

        ret = RT_EOK;
        goto exit_nu_timer_init;
    }
#endif
#if defined(BSP_USING_TIMER2_CAPTURE)
    if (nu_capture->timer == TIMER2)
    {
        /* Enable TIMER2 clock */
        CLK_EnableModuleClock(TMR2_MODULE);
        CLK_SetModuleClock(TMR2_MODULE, CLK_CLKSEL1_TMR2SEL_PCLK1, 0);

        ret = RT_EOK;
        goto exit_nu_timer_init;
    }
#endif
#if defined(BSP_USING_TIMER3_CAPTURE)
    if (nu_capture->timer == TIMER3)
    {
        /* Enable TIMER3 clock */
        CLK_EnableModuleClock(TMR3_MODULE);
        CLK_SetModuleClock(TMR3_MODULE, CLK_CLKSEL1_TMR3SEL_PCLK1, 0);
    }
#endif

exit_nu_timer_init:
    SYS_LockReg();
    return -(ret);
}

static rt_err_t nu_capture_init(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;
    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    if (nu_timer_init(nu_capture) != RT_EOK)
    {
        rt_kprintf("Failed to initialize TIMER.\n");
        ret = RT_ERROR;
    }

    return -(ret);
}

static uint8_t cal_time_prescale(nu_capture_t *nu_capture)
{
    uint32_t u32Clk = TIMER_GetModuleClock(nu_capture->timer);

    /* 1 tick = 1/PSC_DIV us */
    return (u32Clk / 1000000 / PSC_DIV) - 1;
}

static rt_err_t nu_capture_open(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;
    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    nu_capture->first_edge = RT_TRUE;

    /* Enable Timer NVIC */
    NVIC_EnableIRQ(nu_capture->irq);

    TIMER_Open(nu_capture->timer, TIMER_CONTINUOUS_MODE, 1);
    TIMER_SET_PRESCALE_VALUE(nu_capture->timer, cal_time_prescale(nu_capture));
    TIMER_SET_CMP_VALUE(nu_capture->timer, 0xFFFFFF);

    TIMER_EnableCapture(nu_capture->timer, TIMER_CAPTURE_COUNTER_RESET_MODE, TIMER_CAPTURE_EVENT_RISING_FALLING);

    TIMER_EnableInt(nu_capture->timer);

    TIMER_EnableCaptureInt(nu_capture->timer);

    TIMER_Start(nu_capture->timer);

    return ret;
}

static rt_err_t nu_capture_close(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;

    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    TIMER_Stop(nu_capture->timer);

    TIMER_DisableCaptureInt(nu_capture->timer);

    TIMER_DisableInt(nu_capture->timer);

    TIMER_Close(nu_capture->timer);

    NVIC_DisableIRQ(nu_capture->irq);

    return ret;
}

/* Init and register timer capture */
static int nu_timer_capture_device_init(void)
{
    uint8_t TIMER_MSK = 0;

#if defined(BSP_USING_TIMER0_CAPTURE)
    TIMER_MSK |= (0x1 << 0);
#endif
#if defined(BSP_USING_TIMER1_CAPTURE)
    TIMER_MSK |= (0x1 << 1);
#endif
#if defined(BSP_USING_TIMER2_CAPTURE)
    TIMER_MSK |= (0x1 << 2);
#endif
#if defined(BSP_USING_TIMER3_CAPTURE)
    TIMER_MSK |= (0x1 << 3);
#endif

    for (int i = 0; i < TIMER_CHANNEL_NUM; i++)
    {
        if (TIMER_MSK & (0x1 << i))
        {
            nu_timer_capture[i] = (nu_capture_t *)rt_malloc(sizeof(nu_capture_t));

            nu_timer_capture[i]->timer = nu_timer_base[i];
            nu_timer_capture[i]->u8Channel = i;
            nu_timer_capture[i]->irq =   nu_timer_irq[i];
            nu_timer_capture[i]->u32CurrentCnt = 0;
            nu_timer_capture[i]->parent.ops = &nu_capture_ops;
            nu_timer_capture[i]->first_edge = RT_TRUE;

            /* register inputcapture device */
            rt_device_inputcapture_register(&nu_timer_capture[i]->parent, nu_timer_device_name[i], &nu_timer_capture[i]);
        }
    }

    return 0;
}
INIT_DEVICE_EXPORT(nu_timer_capture_device_init);

#endif //#if defined(BSP_USING_TIMER_CAPTURE)
