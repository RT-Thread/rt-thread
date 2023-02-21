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

#if defined(BSP_USING_QEI)

#include <rtdevice.h>
#include "drv_sys.h"
#include "drv_common.h"

/* Private define ---------------------------------------------------------------*/
enum
{
    QEI_START = -1,
#if defined(BSP_USING_QEI0)
    QEI0_START,
#endif
#if defined(BSP_USING_QEI1)
    QEI1_START,
#endif
#if defined(BSP_USING_QEI2)
    QEI2_START,
#endif
    QEI_CNT
};

/* Private typedef --------------------------------------------------------------*/
struct nu_qei
{
    struct rt_pulse_encoder_device dev;
    char *name;
    QEI_T *base;
    IRQn_Type   irqn;
    uint32_t    rstidx;
    uint32_t    modid;

    rt_uint32_t max_cntval;
    rt_uint32_t cmp_val;
    rt_uint8_t  qei_flag;
};
typedef struct nu_qei *nu_qei_t;

/* Private functions ------------------------------------------------------------*/
static rt_uint32_t nu_qei_type(struct rt_pulse_encoder_device *pulse_encoder);
static rt_err_t nu_qei_init(struct rt_pulse_encoder_device *pulse_encoder);
static rt_int32_t nu_qei_get_count(struct rt_pulse_encoder_device *pulse_encoder);
static rt_err_t nu_qei_clear_count(struct rt_pulse_encoder_device *pulse_encoder);
static rt_err_t nu_qei_control(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t cmd, void *args);

/* Public functions -------------------------------------------------------------*/
rt_int32_t nu_qei_get_maxval(struct rt_pulse_encoder_device *pulse_encoder);
rt_int32_t nu_qei_get_cmpval(struct rt_pulse_encoder_device *pulse_encoder);
rt_int32_t nu_qei_get_type(struct rt_pulse_encoder_device *pulse_encoder);
void nu_qei_set_maxval_type(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t u32val, rt_uint8_t u8type);
void nu_qei_set_cmpval(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t u32val);

/* Private variables ------------------------------------------------------------*/
static struct nu_qei nu_qei_arr [] =
{
#if defined(BSP_USING_QEI0)
    {
        .name = "qei0",
        .base = QEI0,
        .irqn = QEI0_IRQn,
        .rstidx = QEI0_RST,
        .modid  = QEI0_MODULE,

        .max_cntval = 1000,
        .cmp_val = 100,
    },
#endif

#if defined(BSP_USING_QEI1)
    {
        .name = "qei1",
        .base = QEI1,
        .irqn = QEI1_IRQn,
        .rstidx = QEI1_RST,
        .modid  = QEI1_MODULE,

        .max_cntval = 1000,
        .cmp_val = 100,
    },
#endif

#if defined(BSP_USING_QEI2)
    {
        .name = "qei2",
        .base = QEI2,
        .irqn = QEI2_IRQn,
        .rstidx = QEI2_RST,
        .modid  = QEI2_MODULE,

        .max_cntval = 1000,
        .cmp_val = 100,
    },
#endif
};

static const struct rt_pulse_encoder_ops nu_qei_ops =
{
    .init = nu_qei_init,
    .get_count = nu_qei_get_count,
    .clear_count = nu_qei_clear_count,
    .control = nu_qei_control,
};

/* Public variables -------------------------------------------------------------*/
static rt_uint32_t nu_qei_type(struct rt_pulse_encoder_device *pulse_encoder)
{
    rt_uint32_t u32type;
    nu_qei_t psNuQei = (nu_qei_t)pulse_encoder;

    RT_ASSERT(pulse_encoder != RT_NULL);

    switch (pulse_encoder->type)
    {
    case SINGLE_PHASE_PULSE_ENCODER:
        u32type = (psNuQei->cmp_val) ? QEI_CTL_X2_COMPARE_COUNTING_MODE : QEI_CTL_X2_FREE_COUNTING_MODE;
        break;

    case UNKNOWN_PULSE_ENCODER_TYPE:
    case AB_PHASE_PULSE_ENCODER:
    default:
        u32type = (psNuQei->cmp_val) ? QEI_CTL_X4_COMPARE_COUNTING_MODE : QEI_CTL_X4_FREE_COUNTING_MODE;
        break;
    }

    return u32type;
}

void nu_qei_set_cmpval(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t u32val)
{
    nu_qei_t psNuQei = (nu_qei_t)pulse_encoder;

    RT_ASSERT(pulse_encoder != RT_NULL);

    QEI_SET_CNT_CMP(psNuQei->base, u32val);
    if (u32val > 0)
    {
        QEI_EnableInt(psNuQei->base, QEI_CTL_CMPIEN_Msk);
        QEI_ENABLE_CNT_CMP(psNuQei->base);
        rt_hw_interrupt_umask(psNuQei->irqn);
    }
    else
    {
        QEI_DisableInt(psNuQei->base, QEI_CTL_CMPIEN_Msk);
        QEI_DISABLE_CNT_CMP(psNuQei->base);
        rt_hw_interrupt_mask(psNuQei->irqn);
    }
}

static rt_err_t nu_qei_init(struct rt_pulse_encoder_device *pulse_encoder)
{
    nu_qei_t psNuQei = (nu_qei_t)pulse_encoder;

    RT_ASSERT(pulse_encoder != RT_NULL);

    /* enable noise filter */
    QEI_ENABLE_NOISE_FILTER(psNuQei->base, QEI_CTL_NFCLKSEL_DIV2);

    /* set compare value and interrupt */
    nu_qei_set_cmpval(pulse_encoder, psNuQei->cmp_val);

    /* set qei mode */
    QEI_Open(psNuQei->base, nu_qei_type(pulse_encoder), psNuQei->max_cntval);

    return RT_EOK;
}

static rt_int32_t nu_qei_get_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    nu_qei_t psNuQei = (nu_qei_t)pulse_encoder;
    RT_ASSERT(pulse_encoder != RT_NULL);
    return (rt_int32_t)QEI_GET_CNT_VALUE(psNuQei->base);
}

static rt_err_t nu_qei_clear_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    nu_qei_t psNuQei = (nu_qei_t)pulse_encoder;
    RT_ASSERT(pulse_encoder != RT_NULL);

    QEI_Stop(psNuQei->base);
    QEI_SET_CNT_VALUE(psNuQei->base, 0);
    QEI_Start(psNuQei->base);

    return RT_EOK;
}

static rt_err_t nu_qei_control(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t cmd, void *args)
{
    rt_err_t result = RT_EOK;
    nu_qei_t psNuQei = (nu_qei_t)pulse_encoder;

    RT_ASSERT(pulse_encoder != RT_NULL);

    switch (cmd)
    {
    case PULSE_ENCODER_CMD_ENABLE:
        /* set compare value and interrupt */
        QEI_Start(psNuQei->base);
        nu_qei_set_cmpval(pulse_encoder, psNuQei->cmp_val);
        break;
    case PULSE_ENCODER_CMD_DISABLE:
        QEI_Stop(psNuQei->base);
        nu_qei_set_cmpval(pulse_encoder, 0);
        break;
    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

static void nu_qei_isr(int vector, void *param)
{
    nu_qei_t psNuQei = (nu_qei_t)param;

    if (QEI_GET_INT_FLAG(psNuQei->base, QEI_STATUS_CMPF_Msk))
    {
        QEI_CLR_INT_FLAG(psNuQei->base, QEI_STATUS_CMPF_Msk);
        rt_kprintf("%s: CMP flag rising\n", psNuQei->name) ;
    }
}

rt_int32_t nu_qei_get_maxval(struct rt_pulse_encoder_device *pulse_encoder)
{
    nu_qei_t psNuQei = (nu_qei_t)pulse_encoder;
    RT_ASSERT(pulse_encoder != RT_NULL);

    return psNuQei->max_cntval;
}

rt_int32_t nu_qei_get_cmpval(struct rt_pulse_encoder_device *pulse_encoder)
{
    nu_qei_t psNuQei = (nu_qei_t)pulse_encoder;
    RT_ASSERT(pulse_encoder != RT_NULL);

    return psNuQei->cmp_val;
}

rt_int32_t nu_qei_get_type(struct rt_pulse_encoder_device *pulse_encoder)
{
    RT_ASSERT(pulse_encoder != RT_NULL);
    return nu_qei_type(pulse_encoder);
}

void nu_qei_set_maxval_type(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t u32val, enum rt_pulse_encoder_type eType)
{
    nu_qei_t psNuQei = (nu_qei_t)pulse_encoder;

    RT_ASSERT(pulse_encoder != RT_NULL);
    RT_ASSERT(eType <= AB_PHASE_PULSE_ENCODER);

    psNuQei->dev.type = eType;
    psNuQei->max_cntval = u32val;
    QEI_Open(psNuQei->base, nu_qei_type(&psNuQei->dev), u32val);
}

int rt_hw_qei_init(void)
{
    int i;
    rt_err_t result = RT_EOK;

    for (i = (QEI_START + 1); i < QEI_CNT; i++)
    {
        nu_qei_t psNuQei = &nu_qei_arr[i];

        psNuQei->dev.type = AB_PHASE_PULSE_ENCODER;
        psNuQei->dev.ops = &nu_qei_ops;

        /* Enable QEI module */
        CLK_EnableModuleClock(psNuQei->modid);
        SYS_ResetModule(psNuQei->rstidx);

        /* register isr */
        rt_hw_interrupt_install(psNuQei->irqn, nu_qei_isr, psNuQei, psNuQei->name);

        result = rt_device_pulse_encoder_register((struct rt_pulse_encoder_device *)&nu_qei_arr[i].dev, nu_qei_arr[i].name, RT_NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return (int)result;
}
INIT_APP_EXPORT(rt_hw_qei_init);

#endif /* BSP_USING_QEI */
