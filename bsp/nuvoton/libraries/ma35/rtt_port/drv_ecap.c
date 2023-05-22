/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-10-7       Wayne            First version
*
******************************************************************************/
#include <rtconfig.h>

#if defined(BSP_USING_ECAP)

#include <rtdevice.h>
#include "drv_sys.h"
#include "drv_common.h"
#include "nu_bitutil.h"

#define ECAP_CHANNEL_NUM    0x3
#define ECAP_CHANNEL_MSK    ((1<<ECAP_CHANNEL_NUM)-1)

#define ECAP_CLK_DIV        ECAP_CAPTURE_TIMER_CLKDIV_32

/* Private typedef --------------------------------------------------------------*/
enum
{
    ECAP_START = -1,
#if defined(BSP_USING_ECAP0)
    ECAP0_IDX,
    ECAP1_IDX,
    ECAP2_IDX,
#endif
#if defined(BSP_USING_ECAP1)
    ECAP3_IDX,
    ECAP4_IDX,
    ECAP5_IDX,
#endif
#if defined(BSP_USING_ECAP2)
    ECAP6_IDX,
    ECAP7_IDX,
    ECAP8_IDX,
#endif
    ECAP_CNT
};

struct nu_ecap
{
    struct rt_inputcapture_device   parent;
    ECAP_T      *base;
    char        *name;
    IRQn_Type    irqn;
    uint32_t     rstidx;
    uint32_t     modid;

    float       fUsPerTick;
    uint8_t     u8Channel;
    rt_bool_t   bfirstData;
    uint32_t    u32CurrentCnt;
    uint32_t    u32LastCnt;
    rt_bool_t   input_data_level;
} ;
typedef struct nu_ecap *nu_ecap_t;

/* Private functions ------------------------------------------------------------*/
static  rt_err_t nu_ecap_init(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_ecap_open(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_ecap_close(struct rt_inputcapture_device *inputcapture);
static  rt_err_t nu_ecap_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);

/* Private define ---------------------------------------------------------------*/
#define NU_ECAP_GET_LEVEL(status, channel)    ((status&(ECAP_STATUS_CAP0_Msk<<channel))?1:0)
#define ECAP_GET_CLK_DIV_INDEX(ecap)          ((ecap)->CTL1 = ((ecap)->CTL1 & ECAP_CTL1_CLKSEL_Msk)>>ECAP_CTL1_CLKSEL_Pos)

/* Public functions -------------------------------------------------------------*/


/* Private variables ------------------------------------------------------------*/
static struct nu_ecap nu_ecap_arr [] =
{
#if defined(BSP_USING_ECAP0)
    {  .base = ECAP0, .name = "ecap0i0", .irqn = ECAP0_IRQn, .rstidx = ECAP0_RST, .modid = ECAP0_MODULE },
    {  .base = ECAP0, .name = "ecap0i1", .irqn = ECAP0_IRQn, .rstidx = ECAP0_RST, .modid = ECAP0_MODULE },
    {  .base = ECAP0, .name = "ecap0i2", .irqn = ECAP0_IRQn, .rstidx = ECAP0_RST, .modid = ECAP0_MODULE },
#endif
#if defined(BSP_USING_ECAP1)
    {  .base = ECAP1, .name = "ecap1i0", .irqn = ECAP1_IRQn, .rstidx = ECAP1_RST, .modid = ECAP1_MODULE },
    {  .base = ECAP1, .name = "ecap1i1", .irqn = ECAP1_IRQn, .rstidx = ECAP1_RST, .modid = ECAP1_MODULE },
    {  .base = ECAP1, .name = "ecap1i2", .irqn = ECAP1_IRQn, .rstidx = ECAP1_RST, .modid = ECAP1_MODULE },
#endif
#if defined(BSP_USING_ECAP2)
    {  .base = ECAP2, .name = "ecap2i0", .irqn = ECAP2_IRQn, .rstidx = ECAP1_RST, .modid = ECAP2_MODULE },
    {  .base = ECAP2, .name = "ecap2i1", .irqn = ECAP2_IRQn, .rstidx = ECAP1_RST, .modid = ECAP2_MODULE },
    {  .base = ECAP2, .name = "ecap2i2", .irqn = ECAP2_IRQn, .rstidx = ECAP1_RST, .modid = ECAP2_MODULE },
#endif
};

static struct rt_inputcapture_ops nu_ecap_ops =
{
    .init   =   nu_ecap_init,
    .open   =   nu_ecap_open,
    .close  =   nu_ecap_close,
    .get_pulsewidth =   nu_ecap_get_pulsewidth,
};

/* Functions define ------------------------------------------------------------*/
static void nu_ecap_isr(int vector, void *param)
{
    /* Get base address of uart register */
    rt_int32_t irqindex;
    nu_ecap_t psNuEcap = (nu_ecap_t)param;
    ECAP_T *base = psNuEcap->base;

    /* Get input Capture status */
    uint32_t u32Status = ECAP_GET_INT_STATUS(base);
    uint32_t u32ChStatus = u32Status & ECAP_CHANNEL_MSK;

    /* Check input capture channel flag */
    /* Find index of pin is attached in pool. */
    while ((irqindex = nu_ctz(u32ChStatus)) < ECAP_CHANNEL_NUM) // Count Trailing Zeros ==> Find First One
    {
        if (u32Status & (ECAP_STATUS_CAPTF0_Msk << (psNuEcap->u8Channel)))
        {
            /* Clear input capture channel flag */
            ECAP_CLR_CAPTURE_FLAG(base, ECAP_STATUS_CAPTF0_Msk << (psNuEcap->u8Channel));

            psNuEcap->input_data_level = NU_ECAP_GET_LEVEL(u32Status, psNuEcap->u8Channel);

            psNuEcap->u32CurrentCnt = ECAP_GET_CNT_HOLD_VALUE(base, psNuEcap->u8Channel);

            rt_hw_inputcapture_isr(&psNuEcap->parent, psNuEcap->input_data_level);
        }
    }
}

static rt_err_t nu_ecap_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us)
{
    rt_err_t ret = RT_EOK;
    float fTempCnt;
    nu_ecap_t psNuEcap = (nu_ecap_t) inputcapture;

    RT_ASSERT(inputcapture != RT_NULL);

    if (psNuEcap->bfirstData)
    {
        psNuEcap->bfirstData = RT_FALSE;
        ret = -RT_ERROR;

        return -(ret);
    }

    if (psNuEcap->u32CurrentCnt > psNuEcap->u32LastCnt)
        fTempCnt = psNuEcap->u32CurrentCnt - psNuEcap->u32LastCnt;
    else    /* Overrun case */
        fTempCnt = psNuEcap->u32CurrentCnt + ((0x1000000 - psNuEcap->u32LastCnt) + 1);

    *pulsewidth_us = (int)(fTempCnt * psNuEcap->fUsPerTick);

    psNuEcap->u32LastCnt = psNuEcap->u32CurrentCnt;

    return -(ret);
}

static float get_ecap_tick_time_us(nu_ecap_t psNuEcap)
{
    uint8_t u8ClockDivider[8] = { 1, 4, 16, 32, 64, 96, 112, 128};

    if (psNuEcap->base == ECAP0)
        return ((float)1000000 / ((float)CLK_GetPCLK2Freq() / u8ClockDivider[(psNuEcap->base->CTL1 & ECAP_CTL1_CLKSEL_Msk) >> ECAP_CTL1_CLKSEL_Pos]));
    else
        return ((float)1000000 / ((float)CLK_GetPCLK1Freq() / u8ClockDivider[(psNuEcap->base->CTL1 & ECAP_CTL1_CLKSEL_Msk) >> ECAP_CTL1_CLKSEL_Pos]));
}

static rt_err_t nu_ecap_init(struct rt_inputcapture_device *inputcapture)
{
    return RT_EOK;
}

static rt_err_t nu_ecap_open(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;
    nu_ecap_t psNuEcap = (nu_ecap_t) inputcapture;

    RT_ASSERT(inputcapture != RT_NULL);

    psNuEcap->fUsPerTick = get_ecap_tick_time_us(psNuEcap);

    /* Enable ECAP Input Channel */
    ECAP_ENABLE_INPUT_CHANNEL(psNuEcap->base, 0x1 << (ECAP_CTL0_IC0EN_Pos + psNuEcap->u8Channel));

    /* Input Channel interrupt enabled */
    ECAP_EnableINT(psNuEcap->base, 0x1 << (ECAP_CTL0_CAPIEN0_Pos + psNuEcap->u8Channel));

    /* Enable interrupt. */
    if ((psNuEcap->base->CTL0 & (ECAP_CHANNEL_MSK << ECAP_CTL0_CAPIEN0_Pos)) != 0U)
        rt_hw_interrupt_umask(psNuEcap->irqn);

    /* ECAP_CNT starts up-counting */
    ECAP_CNT_START(psNuEcap->base);

    return ret;
}

static rt_err_t nu_ecap_close(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;

    nu_ecap_t psNuEcap = (nu_ecap_t) inputcapture;

    RT_ASSERT(inputcapture != RT_NULL);

    /* Input Channel interrupt disabled */
    ECAP_DisableINT(psNuEcap->base, 0x1 << (ECAP_CTL0_CAPIEN0_Pos + psNuEcap->u8Channel));

    /* Disable interrupt. */
    if ((psNuEcap->base->CTL0 & (ECAP_CHANNEL_MSK << ECAP_CTL0_CAPIEN0_Pos)) == 0U)
        rt_hw_interrupt_mask(psNuEcap->irqn);

    /* Disable ECAP Input Channel */
    ECAP_DISABLE_INPUT_CHANNEL(psNuEcap->base, 0x1 << (ECAP_CTL0_IC0EN_Pos + psNuEcap->u8Channel));

    /* Clear input capture channel flag */
    ECAP_CLR_CAPTURE_FLAG(psNuEcap->base, 0x1 << (ECAP_STATUS_CAPTF0_Pos + psNuEcap->u8Channel));

    return ret;
}

static void nu_ecap_channel_init(ECAP_T *base)
{
    /* Enable ECAP */
    ECAP_Open(base, ECAP_DISABLE_COMPARE);

    ECAP_SEL_TIMER_CLK_DIV(base, ECAP_CLK_DIV);

    /* Select Reload function */
    ECAP_SET_CNT_CLEAR_EVENT(base, ECAP_CTL1_OVRLDEN_Msk);

    /* Enable ECAP source IC */
    ECAP_SEL_INPUT_SRC(base, ECAP_IC0, ECAP_CAP_INPUT_SRC_FROM_IC);
    ECAP_SEL_INPUT_SRC(base, ECAP_IC1, ECAP_CAP_INPUT_SRC_FROM_IC);
    ECAP_SEL_INPUT_SRC(base, ECAP_IC2, ECAP_CAP_INPUT_SRC_FROM_IC);

    /* Select IC detect rising edge */
    ECAP_SEL_CAPTURE_EDGE(base, ECAP_IC0, ECAP_RISING_FALLING_EDGE);
    ECAP_SEL_CAPTURE_EDGE(base, ECAP_IC1, ECAP_RISING_FALLING_EDGE);
    ECAP_SEL_CAPTURE_EDGE(base, ECAP_IC2, ECAP_RISING_FALLING_EDGE);
}

/* Init and register ecap capture */
static int rt_hw_ecap_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (ECAP_START + 1); i < ECAP_CNT; i++)
    {
        nu_ecap_t psNuEcap = &nu_ecap_arr[i];

        psNuEcap->u8Channel = i % ECAP_CHANNEL_NUM;
        psNuEcap->bfirstData = RT_TRUE;
        psNuEcap->u32CurrentCnt = 0;
        psNuEcap->u32LastCnt = 0;
        psNuEcap->parent.ops = &nu_ecap_ops;

        if ((psNuEcap->u8Channel % ECAP_CHANNEL_NUM) == 0)
        {
            /* register ecap module */
            CLK_EnableModuleClock(psNuEcap->modid);
            SYS_ResetModule(psNuEcap->rstidx);

            nu_ecap_channel_init(psNuEcap->base);

            /* register isr */
            rt_hw_interrupt_install(psNuEcap->irqn, nu_ecap_isr, psNuEcap, psNuEcap->name);
        }

        /* register inputcapture device */
        ret = rt_device_inputcapture_register(&psNuEcap->parent, psNuEcap->name, psNuEcap);
        RT_ASSERT(ret == RT_EOK);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_ecap_init);

#endif //#if defined(BSP_USING_ECAP)
