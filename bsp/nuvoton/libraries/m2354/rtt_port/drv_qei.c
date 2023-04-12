/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-4-20       FYChou       First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_QEI)
#include <rtdevice.h>
#include "NuMicro.h"

/* Private define ---------------------------------------------------------------*/

/* Private typedef --------------------------------------------------------------*/
struct nu_qei
{
    struct rt_pulse_encoder_device dev;
    char *name;
    QEI_T *qei_base;
    rt_uint32_t max_cntval;
    rt_uint32_t cmp_val;
    IRQn_Type IRQn;
    rt_uint8_t qei_type;
    rt_uint8_t qei_flag;
};
typedef struct nu_qei *nu_qei_t;


/* Private functions ------------------------------------------------------------*/
static rt_uint32_t nu_qei_type(struct rt_pulse_encoder_device *pulse_encoder);
static rt_err_t nu_qei_init(struct rt_pulse_encoder_device *pulse_encoder);
static rt_int32_t nu_qei_get_count(struct rt_pulse_encoder_device *pulse_encoder);
static rt_err_t nu_qei_clear_count(struct rt_pulse_encoder_device *pulse_encoder);
static rt_err_t nu_qei_control(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t cmd, void *args);

/* Public functions -------------------------------------------------------------*/
rt_int32_t nu_qei_get_maxval(rt_device_t *pulse_encoder);
rt_int32_t nu_qei_get_cmpval(rt_device_t *pulse_encoder);
rt_int32_t nu_qei_get_type(rt_device_t *pulse_encoder);
void nu_qei_set_maxval_type(rt_device_t *pulse_encoder, rt_uint32_t u32val, rt_uint8_t u8type);
void nu_qei_set_cmpval(rt_device_t *pulse_encoder, rt_uint32_t u32val);

/* Private variables ------------------------------------------------------------*/
static struct nu_qei nu_qei_arr [] =
{
#if defined(BSP_USING_QEI0)
    {
        .name = "qei0",
        .qei_base = QEI0,
        .max_cntval = 1000,
        .cmp_val = 100,
        .IRQn = QEI0_IRQn,
        .qei_type = AB_PHASE_PULSE_ENCODER,
        .qei_flag = 0
    },
#endif

#if defined(BSP_USING_QEI1)
    {
        .name = "qei1",
        .qei_base = QEI1,
        .max_cntval = 1000,
        .cmp_val = 100,
        .IRQn = QEI1_IRQn,
        .qei_type = AB_PHASE_PULSE_ENCODER,
        .qei_flag = 0
    },
#endif

    {0}
};

static const struct rt_pulse_encoder_ops nu_qei_ops =
{
    .init = nu_qei_init,
    .get_count = nu_qei_get_count,
    .clear_count = nu_qei_clear_count,
    .control = nu_qei_control,
};
typedef struct rt_pulse_encoder_ops *nu_qei_ops_t;

/* Public variables -------------------------------------------------------------*/


static rt_uint32_t nu_qei_type(struct rt_pulse_encoder_device *pulse_encoder)
{
    rt_uint32_t u32type;
    switch (pulse_encoder->type)
    {
    case SINGLE_PHASE_PULSE_ENCODER:
        u32type = (((nu_qei_t)pulse_encoder)->cmp_val) ? QEI_CTL_X2_COMPARE_COUNTING_MODE : QEI_CTL_X2_FREE_COUNTING_MODE;
        break;

    case UNKNOWN_PULSE_ENCODER_TYPE:
    case AB_PHASE_PULSE_ENCODER:
    default:
        u32type = (((nu_qei_t)pulse_encoder)->cmp_val) ? QEI_CTL_X4_COMPARE_COUNTING_MODE : QEI_CTL_X4_FREE_COUNTING_MODE;
        break;
    }

    return u32type;
}

static rt_err_t nu_qei_init(struct rt_pulse_encoder_device *pulse_encoder)
{
    rt_uint32_t u32type;
    QEI_T *qui_base;

    RT_ASSERT(pulse_encoder != RT_NULL);
    qui_base = ((nu_qei_t)pulse_encoder)->qei_base;

    /* enable noise filter */
    QEI_ENABLE_NOISE_FILTER(qui_base, QEI_CTL_NFCLKSEL_DIV2);

    /* set qei mode */
    u32type = nu_qei_type(pulse_encoder);

    /* set compare value and interrupt */
    if (((nu_qei_t)pulse_encoder)->cmp_val)
    {
        QEI_SET_CNT_CMP(qui_base, ((nu_qei_t)pulse_encoder)->cmp_val);
        QEI_EnableInt(qui_base, QEI_CTL_CMPIEN_Msk);
        QEI_ENABLE_CNT_CMP(qui_base);
        NVIC_EnableIRQ(((nu_qei_t)pulse_encoder)->IRQn);
    }
    QEI_Open(qui_base, u32type, ((nu_qei_t)pulse_encoder)->max_cntval);


    return RT_EOK;
}

static rt_int32_t nu_qei_get_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    QEI_T *qui_base;
    RT_ASSERT(pulse_encoder != RT_NULL);
    qui_base = ((nu_qei_t)pulse_encoder)->qei_base;
    return (rt_int32_t)QEI_GET_CNT_VALUE(qui_base);
}


static rt_err_t nu_qei_clear_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    QEI_T *qui_base;
    RT_ASSERT(pulse_encoder != RT_NULL);
    qui_base = ((nu_qei_t)pulse_encoder)->qei_base;
    QEI_Stop(qui_base);
    QEI_SET_CNT_VALUE(qui_base, 0);
    QEI_Start(qui_base);
    return RT_EOK;
}

static rt_err_t nu_qei_control(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t cmd, void *args)
{
    rt_err_t result;
    QEI_T *qui_base;

    RT_ASSERT(pulse_encoder != RT_NULL);
    qui_base = ((nu_qei_t)pulse_encoder)->qei_base;

    RT_ASSERT(cmd != RT_NULL);

    result = RT_EOK;

    switch (cmd)
    {
    case PULSE_ENCODER_CMD_ENABLE:
        QEI_Start(qui_base);
        if (((nu_qei_t)pulse_encoder)->cmp_val)
        {
            QEI_EnableInt(qui_base, QEI_CTL_CMPIEN_Msk);
            QEI_ENABLE_CNT_CMP(qui_base);
            NVIC_EnableIRQ(((nu_qei_t)pulse_encoder)->IRQn);
        }
        break;
    case PULSE_ENCODER_CMD_DISABLE:
        if (((nu_qei_t)pulse_encoder)->cmp_val)
        {
            QEI_DisableInt(qui_base, QEI_CTL_CMPIEN_Msk);
            QEI_DISABLE_CNT_CMP(qui_base);
            NVIC_DisableIRQ(((nu_qei_t)pulse_encoder)->IRQn);
        }
        QEI_Stop(qui_base);
        break;
    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

#if defined(BSP_USING_QEI0)
/* QEI0 interrupt entry */
void QEI0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (QEI_GET_INT_FLAG(nu_qei_arr[0].qei_base, QEI_STATUS_CMPF_Msk))
    {
        nu_qei_arr[0].qei_flag = 1;
        QEI_CLR_INT_FLAG(nu_qei_arr[0].qei_base, QEI_STATUS_CMPF_Msk);
        rt_kprintf("QEI0 CMP flag rising\n") ;
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_QEI1)
/* QEI1 interrupt entry */
void QEI1_IRQHandler(void)
{

    /* enter interrupt */
    rt_interrupt_enter();

    if (QEI_GET_INT_FLAG(nu_qei_arr[1].qei_base, QEI_STATUS_CMPF_Msk))
    {
        nu_qei_arr[1].qei_flag = 1;
        QEI_CLR_INT_FLAG(nu_qei_arr[1].qei_base, QEI_STATUS_CMPF_Msk);
        rt_kprintf("QEI1 CMP flag rising\n") ;
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

rt_int32_t nu_qei_get_maxval(rt_device_t *pulse_encoder)
{
    return ((nu_qei_t) * pulse_encoder)->max_cntval;
}

rt_int32_t nu_qei_get_cmpval(rt_device_t *pulse_encoder)
{
    return ((nu_qei_t) * pulse_encoder)->cmp_val;
}

rt_int32_t nu_qei_get_type(rt_device_t *pulse_encoder)
{
    return ((nu_qei_t) * pulse_encoder)->qei_type;
}

void nu_qei_set_maxval_type(rt_device_t *pulse_encoder, rt_uint32_t u32val, rt_uint8_t u8type)
{
    QEI_T *qui_base;
    RT_ASSERT(pulse_encoder != RT_NULL);
    qui_base = ((nu_qei_t) * pulse_encoder)->qei_base;

    RT_ASSERT(u8type <= AB_PHASE_PULSE_ENCODER);
    ((nu_qei_t)*pulse_encoder)->qei_type = u8type;
    ((nu_qei_t)*pulse_encoder)->dev.type = (enum rt_pulse_encoder_type)u8type;
    ((nu_qei_t)*pulse_encoder)->max_cntval = u32val;
    QEI_Open(qui_base, nu_qei_type(&(((nu_qei_t)*pulse_encoder)->dev)), u32val);
}

void nu_qei_set_cmpval(rt_device_t *pulse_encoder, rt_uint32_t u32val)
{
    QEI_T *qui_base;
    RT_ASSERT(pulse_encoder != RT_NULL);
    qui_base = ((nu_qei_t) * pulse_encoder)->qei_base;

    ((nu_qei_t)*pulse_encoder)->cmp_val = u32val;
    QEI_SET_CNT_CMP(qui_base, ((nu_qei_t)*pulse_encoder)->cmp_val);

    if (((nu_qei_t)*pulse_encoder)->cmp_val)
    {
        QEI_EnableInt(qui_base, QEI_CTL_CMPIEN_Msk);
        QEI_ENABLE_CNT_CMP(qui_base);
        NVIC_EnableIRQ(((nu_qei_t)*pulse_encoder)->IRQn);
    }
    else
    {
        QEI_DisableInt(qui_base, QEI_CTL_CMPIEN_Msk);
        QEI_DISABLE_CNT_CMP(qui_base);
        NVIC_DisableIRQ(((nu_qei_t)*pulse_encoder)->IRQn);
    }
}


int rt_hw_qei_init(void)
{
    int result = -RT_ERROR;
    int nu_sel = 0;
    while (nu_qei_arr[nu_sel].name != 0)
    {
        nu_qei_arr[nu_sel].dev.type = (enum rt_pulse_encoder_type)nu_qei_arr[nu_sel].qei_type;
        nu_qei_arr[nu_sel].dev.ops = &nu_qei_ops;

        result = rt_device_pulse_encoder_register((void *)&nu_qei_arr[nu_sel], nu_qei_arr[nu_sel].name, &(nu_qei_arr[nu_sel].qei_flag));
        RT_ASSERT(result == RT_EOK);
        nu_sel++;
    }
    return result;
}
INIT_APP_EXPORT(rt_hw_qei_init);

#endif /* BSP_USING_QEI */
