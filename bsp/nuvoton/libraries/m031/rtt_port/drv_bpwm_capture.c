/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-02-05      klcheng          First version
*
******************************************************************************/
#include <rtconfig.h>

#if defined(BSP_USING_BPWM_CAPTURE)
#if ((BSP_USING_BPWM0_CAPTURE_CHMSK+BSP_USING_BPWM1_CAPTURE_CHMSK)!=0)
#include <rtdevice.h>
#include "NuMicro.h"

/* Private typedef --------------------------------------------------------------*/
typedef struct _bpwm_dev
{
    BPWM_T      *bpwm_base;
    IRQn_Type   irq;
    float       fUsPerTick;
} nu_bpwm_dev_t;

typedef struct _bpwm
{
    struct rt_inputcapture_device   parent;
    nu_bpwm_dev_t *bpwm_dev;
    uint8_t     u8Channel;
    uint8_t     u8DummyData;
    uint32_t    u32CurrentRisingCnt;
    uint32_t    u32CurrentFallingCnt;
    uint32_t    u32LastRisingCnt;
    uint32_t    u32LastFallingCnt;
    rt_bool_t   input_data_level;
} nu_capture_t;

/* Private functions ------------------------------------------------------------*/
static  rt_err_t nu_capture_init(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_open(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_close(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);

/* Private define ---------------------------------------------------------------*/
#define NU_DUMMY_DATA   2   /* First rising and falling edge should be ignore */

#define NU_NO_EDGE      0
#define NU_RISING_EDGE  1
#define NU_FALLING_EDGE 2

/* Public functions -------------------------------------------------------------*/


/* Private variables ------------------------------------------------------------*/
#if (BSP_USING_BPWM0_CAPTURE_CHMSK!=0)
static const char *nu_bpwm0_device_name[BPWM_CHANNEL_NUM] = { "bpwm0i0", "bpwm0i1", "bpwm0i2", "bpwm0i3", "bpwm0i4", "bpwm0i5"};
static nu_capture_t *nu_bpwm0_capture[BPWM_CHANNEL_NUM] = {0};
static nu_bpwm_dev_t nu_bpwm0_dev = {.bpwm_base = BPWM0};
#endif

#if (BSP_USING_BPWM1_CAPTURE_CHMSK!=0)
static const char *nu_bpwm1_device_name[BPWM_CHANNEL_NUM] = { "bpwm1i0", "bpwm1i1", "bpwm1i2", "bpwm1i3", "bpwm1i4", "bpwm1i5"};
static nu_capture_t *nu_bpwm1_capture[BPWM_CHANNEL_NUM] = {0};
static nu_bpwm_dev_t nu_bpwm1_dev = {.bpwm_base = BPWM1};
#endif

static struct rt_inputcapture_ops nu_capture_ops =
{
    .init   =   nu_capture_init,
    .open   =   nu_capture_open,
    .close  =   nu_capture_close,
    .get_pulsewidth =   nu_capture_get_pulsewidth,
};

/* Functions define ------------------------------------------------------------*/
void bpwm_interrupt_handler(nu_capture_t *nu_capture[], uint32_t u32ChMsk)
{
    uint32_t u32Status;

    for (uint8_t i = 0; i < BPWM_CHANNEL_NUM ; i++)
    {
        if ((0x1 << i) & u32ChMsk)
        {
            if (nu_capture[i]->u8DummyData < NU_DUMMY_DATA)
            {
                nu_capture[i]->u8DummyData++;
            }
            else
            {
                u32Status = BPWM_GetCaptureIntFlag(nu_capture[i]->bpwm_dev->bpwm_base, nu_capture[i]->u8Channel);

                switch (u32Status)
                {
                case NU_NO_EDGE:
                    break;
                case NU_RISING_EDGE:
                    BPWM_ClearCaptureIntFlag(nu_capture[i]->bpwm_dev->bpwm_base, nu_capture[i]->u8Channel, BPWM_CAPTURE_INT_RISING_LATCH);
                    nu_capture[i]->u32CurrentRisingCnt = BPWM_GET_CAPTURE_RISING_DATA(nu_capture[i]->bpwm_dev->bpwm_base, nu_capture[i]->u8Channel);
                    rt_hw_inputcapture_isr(&nu_capture[i]->parent, nu_capture[i]->input_data_level);

                    break;
                case NU_FALLING_EDGE:
                    BPWM_ClearCaptureIntFlag(nu_capture[i]->bpwm_dev->bpwm_base, nu_capture[i]->u8Channel, BPWM_CAPTURE_INT_FALLING_LATCH);
                    nu_capture[i]->u32CurrentFallingCnt = BPWM_GET_CAPTURE_FALLING_DATA(nu_capture[i]->bpwm_dev->bpwm_base, nu_capture[i]->u8Channel);
                    rt_hw_inputcapture_isr(&nu_capture[i]->parent, nu_capture[i]->input_data_level);

                    break;
                default:
                    BPWM_ClearCaptureIntFlag(nu_capture[i]->bpwm_dev->bpwm_base, nu_capture[i]->u8Channel, BPWM_CAPTURE_INT_RISING_LATCH | BPWM_CAPTURE_INT_FALLING_LATCH);
                    BPWM_GET_CAPTURE_RISING_DATA(nu_capture[i]->bpwm_dev->bpwm_base, nu_capture[i]->u8Channel);
                    BPWM_GET_CAPTURE_FALLING_DATA(nu_capture[i]->bpwm_dev->bpwm_base, nu_capture[i]->u8Channel);

                    break;
                }
            }
        }
    }
}

#if (BSP_USING_BPWM0_CAPTURE_CHMSK!=0)
void BPWM0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    bpwm_interrupt_handler(nu_bpwm0_capture, BSP_USING_BPWM0_CAPTURE_CHMSK);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif  //(BSP_USING_BPWM0_CAPTURE_CHMSK!=0)

#if (BSP_USING_BPWM1_CAPTURE_CHMSK!=0)
void BPWM1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    bpwm_interrupt_handler(nu_bpwm1_capture, BSP_USING_BPWM1_CAPTURE_CHMSK);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif  //(BSP_USING_BPWM1_CAPTURE_CHMSK!=0)

static rt_err_t nu_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us)
{
    rt_err_t ret = RT_EOK;
    nu_capture_t *nu_capture;
    float fTempCnt;

    nu_capture = (nu_capture_t *)inputcapture;

    if (nu_capture->u32CurrentFallingCnt)
    {
        if (nu_capture->u32CurrentFallingCnt > nu_capture->u32LastRisingCnt)
            fTempCnt = nu_capture->u32CurrentFallingCnt - nu_capture->u32LastRisingCnt;
        else    /* Overrun case */
            fTempCnt = nu_capture->u32CurrentFallingCnt + (0x10000 - nu_capture->u32LastRisingCnt);

        *pulsewidth_us = fTempCnt * nu_capture->bpwm_dev->fUsPerTick;
        nu_capture->input_data_level = RT_FALSE;
        nu_capture->u32LastFallingCnt = nu_capture->u32CurrentFallingCnt;
        nu_capture->u32CurrentFallingCnt = 0;
    }
    else if (nu_capture->u32CurrentRisingCnt)
    {
        if (nu_capture->u32CurrentRisingCnt > nu_capture->u32LastFallingCnt)
            fTempCnt = nu_capture->u32CurrentRisingCnt - nu_capture->u32LastFallingCnt;
        else    /* Overrun case */
            fTempCnt = nu_capture->u32CurrentRisingCnt + (0x10000 - nu_capture->u32LastFallingCnt);

        *pulsewidth_us = fTempCnt * nu_capture->bpwm_dev->fUsPerTick;
        nu_capture->input_data_level = RT_TRUE;
        nu_capture->u32LastRisingCnt = nu_capture->u32CurrentRisingCnt;
        nu_capture->u32CurrentRisingCnt = 0;
    }
    else
    {
        ret = -RT_ERROR;
    }
    return -(ret);
}

static void bpwm_config(nu_capture_t *nu_capture)
{
    /* Set capture time as 500 nano second */
    nu_capture->bpwm_dev->fUsPerTick = (float)BPWM_ConfigCaptureChannel(nu_capture->bpwm_dev->bpwm_base, 0, 500, 0) / 1000;

    /* Enable BPWM NVIC interrupt */
    NVIC_EnableIRQ(nu_capture->bpwm_dev->irq);

    /* Set counter type as up count */
    BPWM_SET_ALIGNED_TYPE(nu_capture->bpwm_dev->bpwm_base, 0, BPWM_UP_COUNTER);

    /* Enable BPWM Timer */
    BPWM_Start(nu_capture->bpwm_dev->bpwm_base, 0);
}

static rt_err_t nu_bpwm_init(nu_capture_t *nu_capture)
{
    rt_err_t ret = -RT_ERROR;
    static rt_bool_t bBPWM0Inited = RT_FALSE;
    static rt_bool_t bBPWM1Inited = RT_FALSE;

    if (nu_capture->bpwm_dev->bpwm_base == BPWM0)
    {
        if (bBPWM0Inited == RT_FALSE)
        {
            /* Enable BPWM0 clock */
            SYS_UnlockReg();
            CLK_EnableModuleClock(BPWM0_MODULE);
            CLK_SetModuleClock(BPWM0_MODULE, CLK_CLKSEL2_BPWM0SEL_PCLK0, 0);
            SYS_LockReg();
            bpwm_config(nu_capture);
            bBPWM0Inited = RT_TRUE;
        }
        ret = RT_EOK;
    }
    else if (nu_capture->bpwm_dev->bpwm_base == BPWM1)
    {
        if (bBPWM1Inited == RT_FALSE)
        {
            /* Enable BPWM1 clock */
            SYS_UnlockReg();
            CLK_EnableModuleClock(BPWM1_MODULE);
            CLK_SetModuleClock(BPWM1_MODULE, CLK_CLKSEL2_BPWM1SEL_PCLK1, 0);
            SYS_LockReg();
            bpwm_config(nu_capture);
            bBPWM1Inited = RT_TRUE;
        }
        ret = RT_EOK;
    }

    return -(ret);
}

static rt_err_t nu_capture_init(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;
    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    if (nu_bpwm_init(nu_capture) != RT_EOK)
    {
        rt_kprintf("Failed to initialize BPWM.\n");
        ret = -RT_ERROR;
    }

    return -(ret);
}

static rt_err_t nu_capture_open(struct rt_inputcapture_device *inputcapture)
{
    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    /* Enable capture rising/falling edge interrupt */
    BPWM_EnableCaptureInt(nu_capture->bpwm_dev->bpwm_base, nu_capture->u8Channel, BPWM_CAPTURE_INT_FALLING_LATCH | BPWM_CAPTURE_INT_RISING_LATCH);

    /* Enable Capture Function for BPWM */
    BPWM_EnableCapture(nu_capture->bpwm_dev->bpwm_base, 0x1 << nu_capture->u8Channel);

    return RT_EOK;
}

static rt_err_t nu_capture_close(struct rt_inputcapture_device *inputcapture)
{
    nu_capture_t *nu_capture;

    RT_ASSERT(inputcapture != RT_NULL);

    nu_capture = (nu_capture_t *) inputcapture;

    /* Enable Capture Function for BPWM */
    BPWM_DisableCapture(nu_capture->bpwm_dev->bpwm_base, 0x1 << nu_capture->u8Channel);

    /* Disable capture rising/falling edge interrupt */
    BPWM_DisableCaptureInt(nu_capture->bpwm_dev->bpwm_base, nu_capture->u8Channel, BPWM_CAPTURE_INT_FALLING_LATCH | BPWM_CAPTURE_INT_RISING_LATCH);

    return RT_EOK;
}

static void bpwm_init(nu_capture_t *nu_capture, uint8_t u8Channel, nu_bpwm_dev_t *bpwm_dev, const char *device_name, IRQn_Type irq)
{
    nu_capture->bpwm_dev = bpwm_dev;
    nu_capture->bpwm_dev->irq = irq;
    nu_capture->u8Channel = u8Channel;
    nu_capture->u8DummyData = 0;
    nu_capture->u32CurrentFallingCnt = 0;
    nu_capture->u32CurrentRisingCnt = 0;
    nu_capture->u32LastRisingCnt = 0;
    nu_capture->u32LastFallingCnt = 0;
    nu_capture->parent.ops = &nu_capture_ops;

    /* register inputcapture device */
    rt_device_inputcapture_register(&nu_capture->parent, device_name, &nu_capture);
}

/* Init and register bpwm capture */
static int nu_bpwm_capture_device_init(void)
{
    for (int i = 0; i < BPWM_CHANNEL_NUM; i++)
    {
#if (BSP_USING_BPWM0_CAPTURE_CHMSK!=0)
        if (BSP_USING_BPWM0_CAPTURE_CHMSK & (0x1 << i))
        {
            nu_bpwm0_capture[i] = (nu_capture_t *)rt_malloc(sizeof(nu_capture_t));
            bpwm_init(nu_bpwm0_capture[i], i, &nu_bpwm0_dev, nu_bpwm0_device_name[i], BPWM0_IRQn);
        }
#endif //#if (BSP_USING_BPWM0_CAPTURE_CHMSK!=0)

#if (BSP_USING_BPWM1_CAPTURE_CHMSK!=0)
        if (BSP_USING_BPWM1_CAPTURE_CHMSK & (0x1 << i))
        {
            nu_bpwm1_capture[i] = (nu_capture_t *)rt_malloc(sizeof(nu_capture_t));
            bpwm_init(nu_bpwm1_capture[i], i, &nu_bpwm1_dev, nu_bpwm1_device_name[i], BPWM1_IRQn);
        }
#endif //#if (BSP_USING_BPWM1_CAPTURE_CHMSK!=0)
    }

    return 0;
}
INIT_DEVICE_EXPORT(nu_bpwm_capture_device_init);

#endif  //#if ((BSP_USING_BPWM0_CAPTURE_CHMSK+BSP_USING_BPWM1_CAPTURE_CHMSK)!=0)
#endif //#if defined(BSP_USING_BPWM_CAPTURE)
