/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if defined(BSP_USING_ECAP)

#include "drv_common.h"
#include "drv_sys.h"
#include "nu_bitutil.h"
#include "rtdevice.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.ecap"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

#define ECAP_CHANNEL_NUM    0x3
#define ECAP_CHANNEL_MSK    ((1 << ECAP_CHANNEL_NUM) - 1)
#define ECAP_CLK_DIV        ECAP_CAPTURE_TIMER_CLKDIV_32
#define NU_ECAP_GET_LEVEL(status, channel)    (((status) & (1 << (ECAP_STATUS_CAP0_Pos + (channel)))) ? 0 : 1)
#define DEFINE_NU_ECAP(_mod, _chn) \
    {                              \
        .base = ECAP##_mod,        \
        .name = "ecap" #_mod "i" #_chn, \
        .irqn = ECAP##_mod##_IRQn, \
        .rstidx = ECAP##_mod##_RST, \
        .modid = ECAP##_mod##_MODULE \
    }


/* Types / Structures ---------------------------------------------------------*/
enum
{
    ECAP_START = -1,
#if defined(BSP_USING_ECAP0)
    ECAP0_IDX,
    ECAP1_IDX,
    ECAP2_IDX,
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

    float        fUsPerTick;
    uint8_t      u8Channel;
    rt_bool_t    bfirstData;
    uint32_t     u32CurrentCnt;
    uint32_t     u32LastCnt;
    rt_bool_t    input_data_level;
};
typedef struct nu_ecap *nu_ecap_t;

/* Static Function Prototypes ------------------------------------------------*/
static rt_err_t nu_ecap_init(struct rt_inputcapture_device *inputcapture);
static rt_err_t nu_ecap_open(struct rt_inputcapture_device *inputcapture);
static rt_err_t nu_ecap_close(struct rt_inputcapture_device *inputcapture);
static rt_err_t nu_ecap_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);
static void nu_ecap_isr(nu_ecap_t psNuEcap);
static float get_ecap_tick_time_us(nu_ecap_t psNuEcap);
static void nu_ecap_channel_init(ECAP_T *base);
static int rt_hw_ecap_init(void);

/* Static Variables ----------------------------------------------------------*/
static struct nu_ecap nu_ecap_arr [] =
{
#if defined(BSP_USING_ECAP0)
    DEFINE_NU_ECAP(0, 0),
    DEFINE_NU_ECAP(0, 1),
    DEFINE_NU_ECAP(0, 2),
#endif
};

static struct rt_inputcapture_ops nu_ecap_ops =
{
    .init   = nu_ecap_init,
    .open   = nu_ecap_open,
    .close  = nu_ecap_close,
    .get_pulsewidth = nu_ecap_get_pulsewidth,
};

/* Functions Implementation --------------------------------------------------*/
#if defined(BSP_USING_ECAP0)
void ECAP0_IRQHandler(void)
{
    rt_interrupt_enter();

    nu_ecap_isr((void *)&nu_ecap_arr[ECAP0_IDX]);

    rt_interrupt_leave();
}
#endif

static void nu_ecap_isr(nu_ecap_t psNuEcapBase)
{
    int i32ChnId;
    ECAP_T *base = psNuEcapBase->base;

    /* Get input Capture status */
    uint32_t u32Status = ECAP_GET_INT_STATUS(base);
    uint32_t u32ChStatus = u32Status & ECAP_CHANNEL_MSK;

    /* Check input capture channel flag */
    /* Find index of pin is attached in pool. */
    while ((i32ChnId = nu_ctz(u32ChStatus)) < ECAP_CHANNEL_NUM) // Count Trailing Zeros == > Find First One
    {
        if (u32ChStatus & (ECAP_STATUS_CAPTF0_Msk << i32ChnId))
        {
            nu_ecap_t psNuEcap = psNuEcapBase + i32ChnId;
            struct rt_inputcapture_device *inputcapture = (struct rt_inputcapture_device *)&psNuEcap->parent;

            /* Clear input capture channel flag */
            ECAP_CLR_CAPTURE_FLAG(base, 1 << (ECAP_STATUS_CAPTF0_Pos + i32ChnId));

            if (inputcapture->ringbuff)
            {
                psNuEcap->input_data_level = NU_ECAP_GET_LEVEL(u32Status, i32ChnId);

                psNuEcap->u32CurrentCnt = ECAP_GET_CNT_HOLD_VALUE(base, i32ChnId);

                rt_hw_inputcapture_isr(inputcapture, psNuEcap->input_data_level);
            }
        }

        u32ChStatus &= ~(1 << i32ChnId);
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
        ret = RT_ERROR;

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
    uint8_t u8ClockDivider[8] = { 1, 4, 16, 32, 64, 96, 112, 128 };

    if (psNuEcap->base == ECAP0)
        return ((float)1000000 / ((float)CLK_GetPCLK0Freq() / u8ClockDivider[(psNuEcap->base->CTL1 & ECAP_CTL1_CLKSEL_Msk) >> ECAP_CTL1_CLKSEL_Pos]));
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
            NVIC_EnableIRQ((IRQn_Type)psNuEcap->irqn);
        }
        ret = rt_device_inputcapture_register(&psNuEcap->parent, psNuEcap->name, psNuEcap);
        RT_ASSERT(ret == RT_EOK);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_ecap_init);
#endif //#if defined(BSP_USING_ECAP)
