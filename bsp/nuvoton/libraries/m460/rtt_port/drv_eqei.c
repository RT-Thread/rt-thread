/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-10-21      Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_EQEI)

#include <rtdevice.h>
#include "drv_sys.h"
#include "drv_eqei.h"

/* Private define ---------------------------------------------------------------*/
enum
{
    EQEI_START = -1,
#if defined(BSP_USING_EQEI0)
    EQEI0_IDX,
#endif
#if defined(BSP_USING_EQEI1)
    EQEI1_IDX,
#endif
#if defined(BSP_USING_EQEI2)
    EQEI2_IDX,
#endif
#if defined(BSP_USING_EQEI3)
    EQEI3_IDX,
#endif
    EQEI_CNT
};

/* Private typedef --------------------------------------------------------------*/
struct nu_qei
{
    struct rt_pulse_encoder_device dev;
    char *name;
    EQEI_T *base;
    IRQn_Type   irqn;
    uint32_t    rstidx;
    uint32_t    modid;

    rt_uint32_t max_cntval;
    rt_uint32_t cmp_val;
    rt_uint8_t  qei_flag;
};
typedef struct nu_qei *nu_eqei_t;

/* Private functions ------------------------------------------------------------*/
static rt_uint32_t nu_eqei_type(struct rt_pulse_encoder_device *pulse_encoder);
static rt_err_t nu_eqei_init(struct rt_pulse_encoder_device *pulse_encoder);
static rt_int32_t nu_eqei_get_count(struct rt_pulse_encoder_device *pulse_encoder);
static rt_err_t nu_eqei_clear_count(struct rt_pulse_encoder_device *pulse_encoder);
static rt_err_t nu_eqei_control(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t cmd, void *args);
static void nu_eqei_isr(nu_eqei_t psNuEqei);

/* Public functions -------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/
static struct nu_qei nu_eqei_arr [] =
{
#if defined(BSP_USING_EQEI0)
    {
        .name = "eqei0",
        .base = EQEI0,
        .irqn = EQEI0_IRQn,
        .rstidx = EQEI0_RST,
        .modid  = EQEI0_MODULE,

        .max_cntval = 1000,
        .cmp_val = 100,
    },
#endif

#if defined(BSP_USING_EQEI1)
    {
        .name = "eqei1",
        .base = EQEI1,
        .irqn = EQEI1_IRQn,
        .rstidx = EQEI1_RST,
        .modid  = EQEI1_MODULE,

        .max_cntval = 1000,
        .cmp_val = 100,
    },
#endif

#if defined(BSP_USING_EQEI2)
    {
        .name = "eqei2",
        .base = EQEI2,
        .irqn = EQEI2_IRQn,
        .rstidx = EQEI2_RST,
        .modid  = EQEI2_MODULE,

        .max_cntval = 1000,
        .cmp_val = 100,
    },
#endif

#if defined(BSP_USING_EQEI3)
    {
        .name = "eqei3",
        .base = EQEI3,
        .irqn = EQEI3_IRQn,
        .rstidx = EQEI3_RST,
        .modid  = EQEI3_MODULE,

        .max_cntval = 1000,
        .cmp_val = 100,
    },
#endif
};

static const struct rt_pulse_encoder_ops nu_eqei_ops =
{
    .init = nu_eqei_init,
    .get_count = nu_eqei_get_count,
    .clear_count = nu_eqei_clear_count,
    .control = nu_eqei_control,
};

#if defined(BSP_USING_EQEI0)
void EQEI0_IRQHandler(void)
{
    rt_interrupt_enter();

    nu_eqei_isr((void *)&nu_eqei_arr[EQEI0_IDX]);

    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_EQEI1)
void EQEI1_IRQHandler(void)
{
    rt_interrupt_enter();

    nu_eqei_isr((void *)&nu_eqei_arr[EQEI1_IDX]);

    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_EQEI2)
void EQEI2_IRQHandler(void)
{
    rt_interrupt_enter();

    nu_eqei_isr((void *)&nu_eqei_arr[EQEI2_IDX]);

    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_EQEI3)
void EQEI3_IRQHandler(void)
{
    rt_interrupt_enter();

    nu_eqei_isr((void *)&nu_eqei_arr[EQEI3_IDX]);

    rt_interrupt_leave();
}
#endif

static rt_uint32_t nu_eqei_type(struct rt_pulse_encoder_device *pulse_encoder)
{
    rt_uint32_t u32type;
    nu_eqei_t psNuEqei = (nu_eqei_t)pulse_encoder;

    RT_ASSERT(pulse_encoder != RT_NULL);

    switch (pulse_encoder->type)
    {
    case SINGLE_PHASE_PULSE_ENCODER:
        u32type = (psNuEqei->cmp_val) ? EQEI_CTL_X2_COMPARE_COUNTING_MODE : EQEI_CTL_X2_FREE_COUNTING_MODE;
        break;

    case UNKNOWN_PULSE_ENCODER_TYPE:
    case AB_PHASE_PULSE_ENCODER:
    default:
        u32type = (psNuEqei->cmp_val) ? EQEI_CTL_X4_COMPARE_COUNTING_MODE : EQEI_CTL_X4_FREE_COUNTING_MODE;
        break;
    }

    rt_kprintf("[%d %d %d]\n", pulse_encoder->type, psNuEqei->cmp_val, u32type);
    return u32type;
}

void nu_eqei_set_cmpval(rt_device_t pulse_encoder, rt_uint32_t u32val)
{
    nu_eqei_t psNuEqei = (nu_eqei_t)pulse_encoder;

    RT_ASSERT(pulse_encoder != RT_NULL);

    psNuEqei->cmp_val = u32val;
    if (u32val > 0)
    {
        EQEI_DisableInt(psNuEqei->base, EQEI_CTL_CMPIEN_Msk);
        EQEI_SET_CNT_CMP(psNuEqei->base, u32val);
        EQEI_ENABLE_CNT_CMP(psNuEqei->base);
        EQEI_EnableInt(psNuEqei->base, EQEI_CTL_CMPIEN_Msk);
    }
    else
    {
        EQEI_DisableInt(psNuEqei->base, EQEI_CTL_CMPIEN_Msk);
        EQEI_DISABLE_CNT_CMP(psNuEqei->base);
        EQEI_SET_CNT_CMP(psNuEqei->base, 0);
    }
}

static rt_err_t nu_eqei_init(struct rt_pulse_encoder_device *pulse_encoder)
{
    nu_eqei_t psNuEqei = (nu_eqei_t)pulse_encoder;

    RT_ASSERT(pulse_encoder != RT_NULL);

    /* enable noise filter */
    EQEI_ENABLE_NOISE_FILTER(psNuEqei->base, EQEI_CTL_NFCLKSEL_DIV2);

    /* set compare value and interrupt */
    nu_eqei_set_cmpval((rt_device_t)pulse_encoder, psNuEqei->cmp_val);

    /* set qei mode */
    EQEI_Open(psNuEqei->base, nu_eqei_type(pulse_encoder), psNuEqei->max_cntval);

    return RT_EOK;
}

static rt_int32_t nu_eqei_get_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    nu_eqei_t psNuEqei = (nu_eqei_t)pulse_encoder;
    RT_ASSERT(pulse_encoder != RT_NULL);
    return (rt_int32_t)EQEI_GET_CNT_VALUE(psNuEqei->base);
}

static rt_err_t nu_eqei_clear_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    nu_eqei_t psNuEqei = (nu_eqei_t)pulse_encoder;
    RT_ASSERT(pulse_encoder != RT_NULL);

    EQEI_Stop(psNuEqei->base);
    EQEI_SET_CNT_VALUE(psNuEqei->base, 0);
    EQEI_Start(psNuEqei->base);

    return RT_EOK;
}

static rt_err_t nu_eqei_control(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t cmd, void *args)
{
    rt_err_t result = RT_EOK;
    nu_eqei_t psNuEqei = (nu_eqei_t)pulse_encoder;

    RT_ASSERT(pulse_encoder != RT_NULL);

    switch (cmd)
    {
    case PULSE_ENCODER_CMD_ENABLE:
        /* set compare value and interrupt */
        EQEI_Start(psNuEqei->base);
        nu_eqei_set_cmpval((rt_device_t)pulse_encoder, psNuEqei->cmp_val);
        break;
    case PULSE_ENCODER_CMD_DISABLE:
        EQEI_Stop(psNuEqei->base);
        nu_eqei_set_cmpval((rt_device_t)pulse_encoder, 0);
        break;
    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

static void nu_eqei_isr(nu_eqei_t psNuEqei)
{
    if (EQEI_GET_INT_FLAG(psNuEqei->base, EQEI_STATUS_CMPF_Msk))
    {
        psNuEqei->qei_flag = 1;
        EQEI_CLR_INT_FLAG(psNuEqei->base, EQEI_STATUS_CMPF_Msk);
        rt_kprintf("%s: CMP flag rising\n", psNuEqei->name) ;
    }
}

rt_int32_t nu_eqei_get_maxval(rt_device_t pulse_encoder)
{
    nu_eqei_t psNuEqei = (nu_eqei_t)pulse_encoder;
    RT_ASSERT(pulse_encoder != RT_NULL);

    return psNuEqei->max_cntval;
}

rt_int32_t nu_eqei_get_cmpval(rt_device_t pulse_encoder)
{
    nu_eqei_t psNuEqei = (nu_eqei_t)pulse_encoder;
    RT_ASSERT(pulse_encoder != RT_NULL);

    return psNuEqei->cmp_val;
}

rt_int32_t nu_eqei_get_type(rt_device_t pulse_encoder)
{
    RT_ASSERT(pulse_encoder != RT_NULL);
    return nu_eqei_type((struct rt_pulse_encoder_device *)pulse_encoder);
}

void nu_eqei_set_maxval_type(rt_device_t pulse_encoder, rt_uint32_t u32val, enum rt_pulse_encoder_type eType)
{
    nu_eqei_t psNuEqei = (nu_eqei_t)pulse_encoder;

    RT_ASSERT(pulse_encoder != RT_NULL);
    RT_ASSERT(eType <= AB_PHASE_PULSE_ENCODER);

    psNuEqei->dev.type = eType;
    psNuEqei->max_cntval = u32val;
    EQEI_Open(psNuEqei->base, nu_eqei_type(&psNuEqei->dev), u32val);
}

int rt_hw_qei_init(void)
{
    int i;
    rt_err_t result = RT_EOK;

    for (i = (EQEI_START + 1); i < EQEI_CNT; i++)
    {
        nu_eqei_t psNuEqei = &nu_eqei_arr[i];

        psNuEqei->dev.type = AB_PHASE_PULSE_ENCODER;
        psNuEqei->dev.ops = &nu_eqei_ops;

        /* Enable QEI module */
        CLK_EnableModuleClock(psNuEqei->modid);
        SYS_ResetModule(psNuEqei->rstidx);

        result = rt_device_pulse_encoder_register((struct rt_pulse_encoder_device *)&nu_eqei_arr[i].dev, nu_eqei_arr[i].name, (void *)&psNuEqei->qei_flag);
        RT_ASSERT(result == RT_EOK);
    }

    return (int)result;
}
INIT_APP_EXPORT(rt_hw_qei_init);

#endif /* BSP_USING_EQEI */
