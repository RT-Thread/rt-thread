/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
 */

#include <rtdevice.h>
#include <rtdbg.h>

#ifdef RT_USING_PULSE_ENCODER

#if !defined(BSP_USING_PULSE_ENCODER1)  && !defined(BSP_USING_PULSE_ENCODER2)  && !defined(BSP_USING_PULSE_ENCODER3) && \
    !defined(BSP_USING_PULSE_ENCODER4)  && !defined(BSP_USING_PULSE_ENCODER5)  && !defined(BSP_USING_PULSE_ENCODER6) && \
    !defined(BSP_USING_PULSE_ENCODER7)  && !defined(BSP_USING_PULSE_ENCODER8)  && !defined(BSP_USING_PULSE_ENCODER9) && \
    !defined(BSP_USING_PULSE_ENCODER10) && !defined(BSP_USING_PULSE_ENCODER11) && !defined(BSP_USING_PULSE_ENCODER12)
#error "Please define at least one BSP_USING_PULSE_ENCODERx"
/* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable Pulse Encoder */
#endif

#include "drv_pulse_encoder.h"
#include "drv_irq.h"

#define TIMER_AUTO_RELOAD_VALUE         (0xFFFFU)

enum
{
#ifdef BSP_USING_PULSE_ENCODER1
    PULSE_ENCODER1_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER2
    PULSE_ENCODER2_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER3
    PULSE_ENCODER3_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER4
    PULSE_ENCODER4_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER5
    PULSE_ENCODER5_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER6
    PULSE_ENCODER6_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER7
    PULSE_ENCODER7_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER8
    PULSE_ENCODER8_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER9
    PULSE_ENCODER9_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER10
    PULSE_ENCODER10_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER11
    PULSE_ENCODER11_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER12
    PULSE_ENCODER12_INDEX,
#endif
};

#ifdef BSP_USING_PULSE_ENCODER1
static void pulse_encoder1_irq_handler(void);
#endif
#ifdef BSP_USING_PULSE_ENCODER2
static void pulse_encoder2_irq_handler(void);
#endif
#ifdef BSP_USING_PULSE_ENCODER3
static void pulse_encoder3_irq_handler(void);
#endif
#ifdef BSP_USING_PULSE_ENCODER4
static void pulse_encoder4_irq_handler(void);
#endif
#ifdef BSP_USING_PULSE_ENCODER5
static void pulse_encoder5_irq_handler(void);
#endif
#ifdef BSP_USING_PULSE_ENCODER6
static void pulse_encoder6_irq_handler(void);
#endif
#ifdef BSP_USING_PULSE_ENCODER7
static void pulse_encoder7_irq_handler(void);
#endif
#ifdef BSP_USING_PULSE_ENCODER8
static void pulse_encoder8_irq_handler(void);
#endif
#ifdef BSP_USING_PULSE_ENCODER9
static void pulse_encoder9_irq_handler(void);
#endif
#ifdef BSP_USING_PULSE_ENCODER10
static void pulse_encoder10_irq_handler(void);
#endif
#ifdef BSP_USING_PULSE_ENCODER11
static void pulse_encoder11_irq_handler(void);
#endif
#ifdef BSP_USING_PULSE_ENCODER12
static void pulse_encoder12_irq_handler(void);
#endif

struct hc32_pulse_encoder_config
{
    struct rt_pulse_encoder_device pulse_encoder;
    M4_TMRA_TypeDef        *timer_periph;
    struct hc32_irq_config ovf_irq_config;
    struct hc32_irq_config udf_irq_config;
    func_ptr_t             irq_callback;
    rt_int32_t             ovf_udf_count;
    char                   *name;
};

#ifndef HC32_PULSE_ENCODER_CONFIG
#define HC32_PULSE_ENCODER_CONFIG(periph, irq, label, ovf_src, udf_src,        \
                                  ovf_irq_info, udf_irq_info)                  \
    {                                                                          \
        .timer_periph           = periph,                                      \
        .irq_callback           = irq,                                         \
        .name                   = label,                                       \
        .ovf_irq_config         = ovf_irq_info,                                \
        .udf_irq_config         = udf_irq_info,                                \
        .ovf_irq_config.int_src = ovf_src,                                     \
        .udf_irq_config.int_src = udf_src,                                     \
    }
#endif /* HC32_PULSE_ENCODER_CONFIG */

static struct hc32_pulse_encoder_config pulse_encoder_obj[] =
{
#ifdef BSP_USING_PULSE_ENCODER1
    HC32_PULSE_ENCODER_CONFIG(M4_TMRA_1,  pulse_encoder1_irq_handler,  "pulse1",  INT_TMRA_1_OVF,  INT_TMRA_1_UDF,
                              PULSE_ENCODER1_OVF_IRQ_CONFIG,  PULSE_ENCODER1_UDF_IRQ_CONFIG),
#endif
#ifdef BSP_USING_PULSE_ENCODER2
    HC32_PULSE_ENCODER_CONFIG(M4_TMRA_2,  pulse_encoder2_irq_handler,  "pulse2",  INT_TMRA_2_OVF,  INT_TMRA_2_UDF,
                              PULSE_ENCODER2_OVF_IRQ_CONFIG,  PULSE_ENCODER2_UDF_IRQ_CONFIG),
#endif
#ifdef BSP_USING_PULSE_ENCODER3
    HC32_PULSE_ENCODER_CONFIG(M4_TMRA_3,  pulse_encoder3_irq_handler,  "pulse3",  INT_TMRA_3_OVF,  INT_TMRA_3_UDF,
                              PULSE_ENCODER3_OVF_IRQ_CONFIG,  PULSE_ENCODER3_UDF_IRQ_CONFIG),
#endif
#ifdef BSP_USING_PULSE_ENCODER4
    HC32_PULSE_ENCODER_CONFIG(M4_TMRA_4,  pulse_encoder4_irq_handler,  "pulse4",  INT_TMRA_4_OVF,  INT_TMRA_4_UDF,
                              PULSE_ENCODER4_OVF_IRQ_CONFIG,  PULSE_ENCODER4_UDF_IRQ_CONFIG),
#endif
#ifdef BSP_USING_PULSE_ENCODER5
    HC32_PULSE_ENCODER_CONFIG(M4_TMRA_5,  pulse_encoder5_irq_handler,  "pulse5",  INT_TMRA_5_OVF,  INT_TMRA_5_UDF,
                              PULSE_ENCODER5_OVF_IRQ_CONFIG,  PULSE_ENCODER5_UDF_IRQ_CONFIG),
#endif
#ifdef BSP_USING_PULSE_ENCODER6
    HC32_PULSE_ENCODER_CONFIG(M4_TMRA_6,  pulse_encoder6_irq_handler,  "pulse6",  INT_TMRA_6_OVF,  INT_TMRA_6_UDF,
                              PULSE_ENCODER6_OVF_IRQ_CONFIG,  PULSE_ENCODER6_UDF_IRQ_CONFIG),
#endif
#ifdef BSP_USING_PULSE_ENCODER7
    HC32_PULSE_ENCODER_CONFIG(M4_TMRA_7,  pulse_encoder7_irq_handler,  "pulse7",  INT_TMRA_7_OVF,  INT_TMRA_7_UDF,
                              PULSE_ENCODER7_OVF_IRQ_CONFIG,  PULSE_ENCODER7_UDF_IRQ_CONFIG),
#endif
#ifdef BSP_USING_PULSE_ENCODER8
    HC32_PULSE_ENCODER_CONFIG(M4_TMRA_8,  pulse_encoder8_irq_handler,  "pulse8",  INT_TMRA_8_OVF,  INT_TMRA_8_UDF,
                              PULSE_ENCODER8_OVF_IRQ_CONFIG,  PULSE_ENCODER8_UDF_IRQ_CONFIG),
#endif
#ifdef BSP_USING_PULSE_ENCODER9
    HC32_PULSE_ENCODER_CONFIG(M4_TMRA_9,  pulse_encoder9_irq_handler,  "pulse9",  INT_TMRA_9_OVF,  INT_TMRA_9_UDF,
                              PULSE_ENCODER9_OVF_IRQ_CONFIG,  PULSE_ENCODER9_UDF_IRQ_CONFIG),
#endif
#ifdef BSP_USING_PULSE_ENCODER10
    HC32_PULSE_ENCODER_CONFIG(M4_TMRA_10, pulse_encoder10_irq_handler, "pulse10", INT_TMRA_10_OVF, INT_TMRA_10_UDF,
                              PULSE_ENCODER10_OVF_IRQ_CONFIG,  PULSE_ENCODER10_UDF_IRQ_CONFIG),
#endif
#ifdef BSP_USING_PULSE_ENCODER11
    HC32_PULSE_ENCODER_CONFIG(M4_TMRA_11, pulse_encoder11_irq_handler, "pulse11", INT_TMRA_11_OVF, INT_TMRA_11_UDF,
                              PULSE_ENCODER11_OVF_IRQ_CONFIG,  PULSE_ENCODER11_UDF_IRQ_CONFIG),
#endif
#ifdef BSP_USING_PULSE_ENCODER12
    HC32_PULSE_ENCODER_CONFIG(M4_TMRA_12, pulse_encoder12_irq_handler, "pulse12", INT_TMRA_12_OVF, INT_TMRA_12_UDF,
                              PULSE_ENCODER12_OVF_IRQ_CONFIG,  PULSE_ENCODER12_UDF_IRQ_CONFIG),
#endif
};

static void hc32_pulse_encoder_irq_handler(struct hc32_pulse_encoder_config *pulse_encoder_config)
{
    if (Set == TMRA_GetStatus(pulse_encoder_config->timer_periph, TMRA_FLAG_OVF))
    {
        pulse_encoder_config->ovf_udf_count++;
        TMRA_ClrStatus(pulse_encoder_config->timer_periph, TMRA_FLAG_OVF);
    }
    if (Set == TMRA_GetStatus(pulse_encoder_config->timer_periph, TMRA_FLAG_UNF))
    {
        pulse_encoder_config->ovf_udf_count--;
        TMRA_ClrStatus(pulse_encoder_config->timer_periph, TMRA_FLAG_UNF);
    }
}

#ifdef BSP_USING_PULSE_ENCODER1
static void pulse_encoder1_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_pulse_encoder_irq_handler(&pulse_encoder_obj[PULSE_ENCODER1_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER2
static void pulse_encoder2_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_pulse_encoder_irq_handler(&pulse_encoder_obj[PULSE_ENCODER2_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER3
static void pulse_encoder3_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_pulse_encoder_irq_handler(&pulse_encoder_obj[PULSE_ENCODER3_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER4
static void pulse_encoder4_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_pulse_encoder_irq_handler(&pulse_encoder_obj[PULSE_ENCODER4_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER5
static void pulse_encoder5_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_pulse_encoder_irq_handler(&pulse_encoder_obj[PULSE_ENCODER5_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER6
static void pulse_encoder6_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_pulse_encoder_irq_handler(&pulse_encoder_obj[PULSE_ENCODER6_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER7
static void pulse_encoder7_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_pulse_encoder_irq_handler(&pulse_encoder_obj[PULSE_ENCODER7_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER8
static void pulse_encoder8_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_pulse_encoder_irq_handler(&pulse_encoder_obj[PULSE_ENCODER8_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER9
static void pulse_encoder9_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_pulse_encoder_irq_handler(&pulse_encoder_obj[PULSE_ENCODER9_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER10
static void pulse_encoder10_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_pulse_encoder_irq_handler(&pulse_encoder_obj[PULSE_ENCODER10_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER11
static void pulse_encoder11_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_pulse_encoder_irq_handler(&pulse_encoder_obj[PULSE_ENCODER11_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER12
static void pulse_encoder12_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_pulse_encoder_irq_handler(&pulse_encoder_obj[PULSE_ENCODER12_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

static rt_uint16_t hc32_timer_get_unit_number(M4_TMRA_TypeDef *TMRAx)
{
    rt_uint16_t unit_num;
    const rt_uint32_t unit_step = 0x400U;

    if (((rt_uint32_t)TMRAx) >= ((rt_uint32_t)M4_TMRA_1))
    {
        unit_num = (((rt_uint32_t)TMRAx) - ((rt_uint32_t)M4_TMRA_1)) / unit_step;
    }
    else
    {
        unit_num = (((rt_uint32_t)TMRAx) - ((rt_uint32_t)M4_TMRA_5)) / unit_step + 4;
    }

    return unit_num;
}

static void hc32_timer_clock_config(M4_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState)
{
    rt_uint32_t timer_periph;
    rt_uint16_t unit_num;

    unit_num     = hc32_timer_get_unit_number(TMRAx);
    timer_periph = PWC_FCG2_TMRA_1 << unit_num;
    PWC_Fcg2PeriphClockCmd(timer_periph, enNewState);
}

extern rt_err_t rt_hw_board_pulse_encoder_init(M4_TMRA_TypeDef *TMRAx);

rt_err_t hc32_pulse_encoder_init(struct rt_pulse_encoder_device *pulse_encoder)
{
    struct hc32_pulse_encoder_config *pulse_encoder_device;
    stc_tmra_init_t stcTmraInit;
    rt_err_t result;

    RT_ASSERT(pulse_encoder != RT_NULL);
    pulse_encoder_device = (struct hc32_pulse_encoder_config*)pulse_encoder;
    /* Enable Timer peripheral clock. */
    hc32_timer_clock_config(pulse_encoder_device->timer_periph, Enable);
    /* pwm pin configuration */
    result = rt_hw_board_pulse_encoder_init(pulse_encoder_device->timer_periph);
    if (RT_EOK == result)
    {
        TMRA_DeInit(pulse_encoder_device->timer_periph);
        TMRA_StructInit(&stcTmraInit);
        stcTmraInit.u32PeriodVal = TIMER_AUTO_RELOAD_VALUE;
        stcTmraInit.u32ClkSrc    = TMRA_CLK_HW_UP_CLKBH_CLKAR | TMRA_CLK_HW_DOWN_CLKBL_CLKAR;
        TMRA_Init(pulse_encoder_device->timer_periph, &stcTmraInit);
        LOG_D("%s init success", pulse_encoder_device->name);

        hc32_install_irq_handler(&pulse_encoder_device->ovf_irq_config, pulse_encoder_device->irq_callback, RT_FALSE);
        NVIC_EnableIRQ(pulse_encoder_device->ovf_irq_config.irq);
        hc32_install_irq_handler(&pulse_encoder_device->udf_irq_config, pulse_encoder_device->irq_callback, RT_FALSE);
        NVIC_EnableIRQ(pulse_encoder_device->udf_irq_config.irq);
        /* clear update flag */
        TMRA_ClrStatus(pulse_encoder_device->timer_periph, (TMRA_FLAG_OVF | TMRA_FLAG_UNF));
    }

    return result;
}

rt_err_t hc32_pulse_encoder_clear_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    struct hc32_pulse_encoder_config *pulse_encoder_device;

    pulse_encoder_device = (struct hc32_pulse_encoder_config*)pulse_encoder;
    pulse_encoder_device->ovf_udf_count = 0;
    TMRA_Stop(pulse_encoder_device->timer_periph);
    TMRA_SetCntVal(pulse_encoder_device->timer_periph, 0);
    TMRA_ClrStatus(pulse_encoder_device->timer_periph, (TMRA_FLAG_OVF | TMRA_FLAG_UNF));
    TMRA_Start(pulse_encoder_device->timer_periph);  

    return RT_EOK;
}

rt_int32_t hc32_pulse_encoder_get_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    struct hc32_pulse_encoder_config *pulse_encoder_device;
    rt_int32_t period_val;
    rt_int32_t count_val;

    pulse_encoder_device = (struct hc32_pulse_encoder_config*)pulse_encoder;
    period_val = TMRA_GetCntVal(pulse_encoder_device->timer_periph);
    count_val = period_val + pulse_encoder_device->ovf_udf_count * TIMER_AUTO_RELOAD_VALUE;

    return count_val;
}

rt_err_t hc32_pulse_encoder_control(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t cmd, void *args)
{
    rt_err_t result = RT_EOK;
    struct hc32_pulse_encoder_config *pulse_encoder_device;
    pulse_encoder_device = (struct hc32_pulse_encoder_config*)pulse_encoder;

    switch (cmd)
    {
    case PULSE_ENCODER_CMD_ENABLE:
        TMRA_IntCmd(pulse_encoder_device->timer_periph, (TMRA_INT_OVF | TMRA_INT_UNF), Enable);
        TMRA_Start(pulse_encoder_device->timer_periph);
        break;
    case PULSE_ENCODER_CMD_DISABLE:
        TMRA_Stop(pulse_encoder_device->timer_periph);
        TMRA_IntCmd(pulse_encoder_device->timer_periph, (TMRA_INT_OVF | TMRA_INT_UNF), Disable);
        break;
    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

static const struct rt_pulse_encoder_ops pulse_encoder_ops =
{
    .init        = hc32_pulse_encoder_init,
    .get_count   = hc32_pulse_encoder_get_count,
    .clear_count = hc32_pulse_encoder_clear_count,
    .control     = hc32_pulse_encoder_control,
};

int hw_pulse_encoder_init(void)
{
    int i;
    int result;

    result = RT_EOK;
    for (i = 0; i < sizeof(pulse_encoder_obj) / sizeof(pulse_encoder_obj[0]); i++)
    {
        pulse_encoder_obj[i].pulse_encoder.type = AB_PHASE_PULSE_ENCODER;
        pulse_encoder_obj[i].pulse_encoder.ops  = &pulse_encoder_ops;

        if (rt_device_pulse_encoder_register(&pulse_encoder_obj[i].pulse_encoder, pulse_encoder_obj[i].name, pulse_encoder_obj[i].timer_periph) != RT_EOK)
        {
            LOG_E("%s register failed", pulse_encoder_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(hw_pulse_encoder_init);

#endif
