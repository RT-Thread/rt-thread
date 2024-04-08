/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-06-09     CDT               first version
 */

#include "board.h"
#include "drv_config.h"

#ifdef RT_USING_PULSE_ENCODER

#include "drv_irq.h"

// #define DRV_DEBUG
#define LOG_TAG             "drv_pulse_encoder"
#include <drv_log.h>

#if defined(BSP_USING_TMRA_PULSE_ENCODER)

#if !defined(BSP_USING_PULSE_ENCODER_TMRA_1) && !defined(BSP_USING_PULSE_ENCODER_TMRA_2) && !defined(BSP_USING_PULSE_ENCODER_TMRA_3) && \
    !defined(BSP_USING_PULSE_ENCODER_TMRA_4) && !defined(BSP_USING_PULSE_ENCODER_TMRA_5) && !defined(BSP_USING_PULSE_ENCODER_TMRA_6) && \
    !defined(BSP_USING_PULSE_ENCODER_TMRA_7) && !defined(BSP_USING_PULSE_ENCODER_TMRA_8) && !defined(BSP_USING_PULSE_ENCODER_TMRA_9) && \
    !defined(BSP_USING_PULSE_ENCODER_TMRA_10) && !defined(BSP_USING_PULSE_ENCODER_TMRA_11) && !defined(BSP_USING_PULSE_ENCODER_TMRA_12)
    #error "Please define at least one BSP_USING_PULSE_ENCODERx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

enum
{
#ifdef BSP_USING_PULSE_ENCODER_TMRA_1
    PULSE_ENCODER_TMRA_1_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_2
    PULSE_ENCODER_TMRA_2_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_3
    PULSE_ENCODER_TMRA_3_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_4
    PULSE_ENCODER_TMRA_4_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_5
    PULSE_ENCODER_TMRA_5_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_6
    PULSE_ENCODER_TMRA_6_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_7
    PULSE_ENCODER_TMRA_7_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_8
    PULSE_ENCODER_TMRA_8_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_9
    PULSE_ENCODER_TMRA_9_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_10
    PULSE_ENCODER_TMRA_10_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_11
    PULSE_ENCODER_TMRA_11_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_12
    PULSE_ENCODER_TMRA_12_INDEX,
#endif
};

struct hc32_pulse_encoder_tmra_device
{
    struct rt_pulse_encoder_device pulse_encoder;
    CM_TMRA_TypeDef *tmr_handler;
    uint32_t u32Fcg2Periph;
    struct
    {
        uint16_t u16CountUpCond;
        uint16_t u16CountDownCond;
    } hw_count;
    struct
    {
        en_int_src_t enIntSrc_Ovf;
        IRQn_Type enIRQn_Ovf;
        uint8_t u8Int_Prio_Ovf;
        func_ptr_t Irq_Ovf_Callback;
        en_int_src_t enIntSrc_Udf;
        IRQn_Type enIRQn_Udf;
        uint8_t u8Int_Prio_Udf;
        func_ptr_t Irq_Udf_Callback;
    } isr;
    rt_uint32_t u32PeriodValue;
    rt_int32_t Over_Under_Flowcount;
    char *name;
};

static struct hc32_pulse_encoder_tmra_device hc32_pulse_encoder_tmra_obj[] =
{
#ifdef BSP_USING_PULSE_ENCODER_TMRA_1
    PULSE_ENCODER_TMRA_1_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_2
    PULSE_ENCODER_TMRA_2_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_3
    PULSE_ENCODER_TMRA_3_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_4
    PULSE_ENCODER_TMRA_4_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_5
    PULSE_ENCODER_TMRA_5_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_6
    PULSE_ENCODER_TMRA_6_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_7
    PULSE_ENCODER_TMRA_7_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_8
    PULSE_ENCODER_TMRA_8_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_9
    PULSE_ENCODER_TMRA_9_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_10
    PULSE_ENCODER_TMRA_10_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_11
    PULSE_ENCODER_TMRA_11_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_12
    PULSE_ENCODER_TMRA_12_CONFIG,
#endif
};

#ifdef BSP_USING_PULSE_ENCODER_TMRA_1
static void TMRA_1_Ovf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_1_INDEX].tmr_handler, TMRA_FLAG_OVF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_1_INDEX].Over_Under_Flowcount++;
}
static void TMRA_1_Udf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_1_INDEX].tmr_handler, TMRA_FLAG_UDF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_1_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_2
static void TMRA_2_Ovf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_2_INDEX].tmr_handler, TMRA_FLAG_OVF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_2_INDEX].Over_Under_Flowcount++;
}
static void TMRA_2_Udf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_2_INDEX].tmr_handler, TMRA_FLAG_UDF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_2_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_3
static void TMRA_3_Ovf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_3_INDEX].tmr_handler, TMRA_FLAG_OVF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_3_INDEX].Over_Under_Flowcount++;
}
static void TMRA_3_Udf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_3_INDEX].tmr_handler, TMRA_FLAG_UDF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_3_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_4
static void TMRA_4_Ovf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_4_INDEX].tmr_handler, TMRA_FLAG_OVF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_4_INDEX].Over_Under_Flowcount++;
}
static void TMRA_4_Udf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_4_INDEX].tmr_handler, TMRA_FLAG_UDF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_4_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_5
static void TMRA_5_Ovf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_5_INDEX].tmr_handler, TMRA_FLAG_OVF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_5_INDEX].Over_Under_Flowcount++;
}
static void TMRA_5_Udf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_5_INDEX].tmr_handler, TMRA_FLAG_UDF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_5_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_6
static void TMRA_6_Ovf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_6_INDEX].tmr_handler, TMRA_FLAG_OVF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_6_INDEX].Over_Under_Flowcount++;
}
static void TMRA_6_Udf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_6_INDEX].tmr_handler, TMRA_FLAG_UDF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_6_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_7
static void TMRA_7_Ovf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_7_INDEX].tmr_handler, TMRA_FLAG_OVF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_7_INDEX].Over_Under_Flowcount++;
}
static void TMRA_7_Udf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_7_INDEX].tmr_handler, TMRA_FLAG_UDF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_7_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_8
static void TMRA_8_Ovf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_8_INDEX].tmr_handler, TMRA_FLAG_OVF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_8_INDEX].Over_Under_Flowcount++;
}
static void TMRA_8_Udf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_8_INDEX].tmr_handler, TMRA_FLAG_UDF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_8_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_9
static void TMRA_9_Ovf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_9_INDEX].tmr_handler, TMRA_FLAG_OVF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_9_INDEX].Over_Under_Flowcount++;
}
static void TMRA_9_Udf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_9_INDEX].tmr_handler, TMRA_FLAG_UDF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_9_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_10
static void TMRA_10_Ovf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_10_INDEX].tmr_handler, TMRA_FLAG_OVF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_10_INDEX].Over_Under_Flowcount++;
}
static void TMRA_10_Udf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_10_INDEX].tmr_handler, TMRA_FLAG_UDF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_10_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_11
static void TMRA_11_Ovf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_11_INDEX].tmr_handler, TMRA_FLAG_OVF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_11_INDEX].Over_Under_Flowcount++;
}
static void TMRA_11_Udf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_11_INDEX].tmr_handler, TMRA_FLAG_UDF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_11_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_12
static void TMRA_12_Ovf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_12_INDEX].tmr_handler, TMRA_FLAG_OVF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_12_INDEX].Over_Under_Flowcount++;
}
static void TMRA_12_Udf_callback(void)
{
    TMRA_ClearStatus(hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_12_INDEX].tmr_handler, TMRA_FLAG_UDF);
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_12_INDEX].Over_Under_Flowcount--;
}
#endif

/**
  * @brief  This function gets pulse_encoder_tima irq handle.
  * @param  None
  * @retval None
  */
static void hc32_get_pulse_encoder_tmra_callback(void)
{
#ifdef BSP_USING_PULSE_ENCODER_TMRA_1
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_1_INDEX].isr.Irq_Ovf_Callback = TMRA_1_Ovf_callback;
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_1_INDEX].isr.Irq_Udf_Callback = TMRA_1_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_2
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_2_INDEX].isr.Irq_Ovf_Callback = TMRA_2_Ovf_callback;
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_2_INDEX].isr.Irq_Udf_Callback = TMRA_2_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_3
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_3_INDEX].isr.Irq_Ovf_Callback = TMRA_3_Ovf_callback;
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_3_INDEX].isr.Irq_Udf_Callback = TMRA_3_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_4
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_4_INDEX].isr.Irq_Ovf_Callback = TMRA_4_Ovf_callback;
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_4_INDEX].isr.Irq_Udf_Callback = TMRA_4_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_5
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_5_INDEX].isr.Irq_Ovf_Callback = TMRA_5_Ovf_callback;
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_5_INDEX].isr.Irq_Udf_Callback = TMRA_5_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_6
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_6_INDEX].isr.Irq_Ovf_Callback = TMRA_6_Ovf_callback;
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_6_INDEX].isr.Irq_Udf_Callback = TMRA_6_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_7
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_7_INDEX].isr.Irq_Ovf_Callback = TMRA_7_Ovf_callback;
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_7_INDEX].isr.Irq_Udf_Callback = TMRA_7_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_8
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_8_INDEX].isr.Irq_Ovf_Callback = TMRA_8_Ovf_callback;
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_8_INDEX].isr.Irq_Udf_Callback = TMRA_8_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_9
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_9_INDEX].isr.Irq_Ovf_Callback = TMRA_9_Ovf_callback;
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_9_INDEX].isr.Irq_Udf_Callback = TMRA_9_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_10
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_10_INDEX].isr.Irq_Ovf_Callback = TMRA_10_Ovf_callback;
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_10_INDEX].isr.Irq_Udf_Callback = TMRA_10_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_11
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_11_INDEX].isr.Irq_Ovf_Callback = TMRA_11_Ovf_callback;
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_11_INDEX].isr.Irq_Udf_Callback = TMRA_11_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMRA_12
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_12_INDEX].isr.Irq_Ovf_Callback = TMRA_12_Ovf_callback;
    hc32_pulse_encoder_tmra_obj[PULSE_ENCODER_TMRA_12_INDEX].isr.Irq_Udf_Callback = TMRA_12_Udf_callback;
#endif
}

rt_err_t _tmra_pulse_encoder_init(struct rt_pulse_encoder_device *pulse_encoder)
{
    stc_tmra_init_t stcTmraInit;
    struct hc32_irq_config irq_config;
    struct hc32_pulse_encoder_tmra_device *hc32_device;
    hc32_device = (struct hc32_pulse_encoder_tmra_device *)pulse_encoder;

    /* Enable TimerA peripheral clock. */
    FCG_Fcg2PeriphClockCmd(hc32_device->u32Fcg2Periph, ENABLE);

    (void)TMRA_StructInit(&stcTmraInit);
    /* Initializes position-count unit. */
    stcTmraInit.u8CountSrc = TMRA_CNT_SRC_HW;
    stcTmraInit.hw_count.u16CountUpCond   = hc32_device->hw_count.u16CountUpCond;
    stcTmraInit.hw_count.u16CountDownCond = hc32_device->hw_count.u16CountDownCond;
    stcTmraInit.u32PeriodValue = hc32_device->u32PeriodValue;
    (void)TMRA_Init(hc32_device->tmr_handler, &stcTmraInit);

    /* OVF interrupt configuration */
    irq_config.irq_num = hc32_device->isr.enIRQn_Ovf;
    irq_config.int_src = hc32_device->isr.enIntSrc_Ovf;
    irq_config.irq_prio = hc32_device->isr.u8Int_Prio_Ovf;
    /* register interrupt */
    hc32_install_irq_handler(&irq_config,
                             hc32_device->isr.Irq_Ovf_Callback,
                             RT_TRUE);
    /* UDF interrupt configuration */
    irq_config.irq_num = hc32_device->isr.enIRQn_Udf;
    irq_config.int_src = hc32_device->isr.enIntSrc_Udf;
    irq_config.irq_prio = hc32_device->isr.u8Int_Prio_Udf;
    /* register interrupt */
    hc32_install_irq_handler(&irq_config,
                             hc32_device->isr.Irq_Udf_Callback,
                             RT_TRUE);

    /* Enable the specified interrupts of TimerA. */
    TMRA_IntCmd(hc32_device->tmr_handler, TMRA_INT_OVF | TMRA_INT_UDF, ENABLE);

    LOG_D("_tmra_pulse_encoder_init");

    return RT_EOK;
}

rt_err_t _tmra_pulse_encoder_clear_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    rt_uint8_t startFlag = RT_FALSE;
    struct hc32_pulse_encoder_tmra_device *hc32_device;
    hc32_device = (struct hc32_pulse_encoder_tmra_device *)pulse_encoder;
    hc32_device->Over_Under_Flowcount = 0;
    if (READ_REG8_BIT(hc32_device->tmr_handler->BCSTRL, TMRA_BCSTRL_START) == TMRA_BCSTRL_START)
    {
        startFlag = RT_TRUE;
    }
    TMRA_Stop(hc32_device->tmr_handler);
    TMRA_SetCountValue(hc32_device->tmr_handler, 0);
    if (RT_TRUE == startFlag)
    {
        TMRA_Start(hc32_device->tmr_handler);
    }
    return RT_EOK;
}

rt_int32_t _tmra_pulse_encoder_get_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    struct hc32_pulse_encoder_tmra_device *hc32_device;
    hc32_device = (struct hc32_pulse_encoder_tmra_device *)pulse_encoder;
    return (rt_int32_t)((rt_int16_t)TMRA_GetCountValue(hc32_device->tmr_handler) + (hc32_device->Over_Under_Flowcount * (hc32_device->u32PeriodValue + 1)));
}

rt_err_t _tmra_pulse_encoder_control(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t cmd, void *args)
{
    rt_err_t result;
    struct hc32_pulse_encoder_tmra_device *hc32_device;
    hc32_device = (struct hc32_pulse_encoder_tmra_device *)pulse_encoder;

    result = RT_EOK;

    switch (cmd)
    {
    case PULSE_ENCODER_CMD_ENABLE:
        TMRA_Start(hc32_device->tmr_handler);
        LOG_D("TMRA_Start");
        break;
    case PULSE_ENCODER_CMD_DISABLE:
        TMRA_Stop(hc32_device->tmr_handler);
        LOG_D("TMRA_Stop");
        break;
    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

static const struct rt_pulse_encoder_ops _tmra_ops =
{
    .init = _tmra_pulse_encoder_init,
    .get_count = _tmra_pulse_encoder_get_count,
    .clear_count = _tmra_pulse_encoder_clear_count,
    .control = _tmra_pulse_encoder_control,
};

#endif /* BSP_USING_TMRA_PULSE_ENCODER */

#if defined(BSP_USING_TMR6_PULSE_ENCODER)

#if !defined(BSP_USING_PULSE_ENCODER_TMR6_1) && !defined(BSP_USING_PULSE_ENCODER_TMR6_2) && !defined(BSP_USING_PULSE_ENCODER_TMR6_3) && \
    !defined(BSP_USING_PULSE_ENCODER_TMR6_4) && !defined(BSP_USING_PULSE_ENCODER_TMR6_5) && !defined(BSP_USING_PULSE_ENCODER_TMR6_6) && \
    !defined(BSP_USING_PULSE_ENCODER_TMR6_7) && !defined(BSP_USING_PULSE_ENCODER_TMR6_8)
    #error "Please define at least one BSP_USING_PULSE_ENCODERx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

enum
{
#ifdef BSP_USING_PULSE_ENCODER_TMR6_1
    PULSE_ENCODER_TMR6_1_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_2
    PULSE_ENCODER_TMR6_2_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_3
    PULSE_ENCODER_TMR6_3_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_4
    PULSE_ENCODER_TMR6_4_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_5
    PULSE_ENCODER_TMR6_5_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_6
    PULSE_ENCODER_TMR6_6_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_7
    PULSE_ENCODER_TMR6_7_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_8
    PULSE_ENCODER_TMR6_8_INDEX,
#endif
};

struct hc32_pulse_encoder_tmr6_device
{
    struct rt_pulse_encoder_device pulse_encoder;
    CM_TMR6_TypeDef *tmr_handler;
    uint32_t u32Fcg2Periph;
    struct
    {
        uint32_t u32CountUpCond;
        uint32_t u32CountDownCond;
    } hw_count;
    struct
    {
        en_int_src_t enIntSrc_Ovf;
        IRQn_Type enIRQn_Ovf;
        uint8_t u8Int_Prio_Ovf;
        func_ptr_t Irq_Ovf_Callback;
        en_int_src_t enIntSrc_Udf;
        IRQn_Type enIRQn_Udf;
        uint8_t u8Int_Prio_Udf;
        func_ptr_t Irq_Udf_Callback;
    } isr;
    rt_uint32_t u32PeriodValue;
    rt_int32_t Over_Under_Flowcount;
    char *name;
};

static struct hc32_pulse_encoder_tmr6_device hc32_pulse_encoder_tmr6_obj[] =
{
#ifdef BSP_USING_PULSE_ENCODER_TMR6_1
    PULSE_ENCODER_TMR6_1_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_2
    PULSE_ENCODER_TMR6_2_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_3
    PULSE_ENCODER_TMR6_3_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_4
    PULSE_ENCODER_TMR6_4_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_5
    PULSE_ENCODER_TMR6_5_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_6
    PULSE_ENCODER_TMR6_6_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_7
    PULSE_ENCODER_TMR6_7_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_8
    PULSE_ENCODER_TMR6_8_CONFIG,
#endif
};

#ifdef BSP_USING_PULSE_ENCODER_TMR6_1
void TMR6_1_Ovf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_1_INDEX].tmr_handler, TMR6_FLAG_OVF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_1_INDEX].Over_Under_Flowcount++;
}
void TMR6_1_Udf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_1_INDEX].tmr_handler, TMR6_FLAG_UDF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_1_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_2
void TMR6_2_Ovf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_2_INDEX].tmr_handler, TMR6_FLAG_OVF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_2_INDEX].Over_Under_Flowcount++;
}
void TMR6_2_Udf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_2_INDEX].tmr_handler, TMR6_FLAG_UDF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_2_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_3
void TMR6_3_Ovf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_3_INDEX].tmr_handler, TMR6_FLAG_OVF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_3_INDEX].Over_Under_Flowcount++;
}
void TMR6_3_Udf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_3_INDEX].tmr_handler, TMR6_FLAG_UDF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_3_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_4
void TMR6_4_Ovf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_4_INDEX].tmr_handler, TMR6_FLAG_OVF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_4_INDEX].Over_Under_Flowcount++;
}
void TMR6_4_Udf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_4_INDEX].tmr_handler, TMR6_FLAG_UDF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_4_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_5
void TMR6_5_Ovf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_5_INDEX].tmr_handler, TMR6_FLAG_OVF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_5_INDEX].Over_Under_Flowcount++;
}
void TMR6_5_Udf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_5_INDEX].tmr_handler, TMR6_FLAG_UDF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_5_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_6
void TMR6_6_Ovf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_6_INDEX].tmr_handler, TMR6_FLAG_OVF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_6_INDEX].Over_Under_Flowcount++;
}
void TMR6_6_Udf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_6_INDEX].tmr_handler, TMR6_FLAG_UDF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_6_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_7
void TMR6_7_Ovf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_7_INDEX].tmr_handler, TMR6_FLAG_OVF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_7_INDEX].Over_Under_Flowcount++;
}
void TMR6_7_Udf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_7_INDEX].tmr_handler, TMR6_FLAG_UDF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_7_INDEX].Over_Under_Flowcount--;
}
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_8
void TMR6_8_Ovf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_8_INDEX].tmr_handler, TMR6_FLAG_OVF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_8_INDEX].Over_Under_Flowcount++;
}
void TMR6_8_Udf_callback(void)
{
    TMR6_ClearStatus(hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_8_INDEX].tmr_handler, TMR6_FLAG_UDF);
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_8_INDEX].Over_Under_Flowcount--;
}
#endif

/**
  * @brief  This function gets pulse_encoder_tim6 irq handle.
  * @param  None
  * @retval None
  */
static void hc32_get_pulse_encoder_tmr6_callback(void)
{
#ifdef BSP_USING_PULSE_ENCODER_TMR6_1
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_1_INDEX].isr.Irq_Ovf_Callback = TMR6_1_Ovf_callback;
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_1_INDEX].isr.Irq_Udf_Callback = TMR6_1_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_2
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_2_INDEX].isr.Irq_Ovf_Callback = TMR6_2_Ovf_callback;
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_2_INDEX].isr.Irq_Udf_Callback = TMR6_2_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_3
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_3_INDEX].isr.Irq_Ovf_Callback = TMR6_3_Ovf_callback;
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_3_INDEX].isr.Irq_Udf_Callback = TMR6_3_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_4
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_4_INDEX].isr.Irq_Ovf_Callback = TMR6_4_Ovf_callback;
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_4_INDEX].isr.Irq_Udf_Callback = TMR6_4_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_5
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_5_INDEX].isr.Irq_Ovf_Callback = TMR6_5_Ovf_callback;
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_5_INDEX].isr.Irq_Udf_Callback = TMR6_5_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_6
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_6_INDEX].isr.Irq_Ovf_Callback = TMR6_6_Ovf_callback;
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_6_INDEX].isr.Irq_Udf_Callback = TMR6_6_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_7
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_7_INDEX].isr.Irq_Ovf_Callback = TMR6_7_Ovf_callback;
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_7_INDEX].isr.Irq_Udf_Callback = TMR6_7_Udf_callback;
#endif
#ifdef BSP_USING_PULSE_ENCODER_TMR6_8
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_8_INDEX].isr.Irq_Ovf_Callback = TMR6_8_Ovf_callback;
    hc32_pulse_encoder_tmr6_obj[PULSE_ENCODER_TMR6_8_INDEX].isr.Irq_Udf_Callback = TMR6_8_Udf_callback;
#endif
}

rt_err_t _tmr6_pulse_encoder_init(struct rt_pulse_encoder_device *pulse_encoder)
{
    stc_tmr6_init_t stcTmr6Init;
    struct hc32_irq_config irq_config;
    struct hc32_pulse_encoder_tmr6_device *hc32_device;
    hc32_device = (struct hc32_pulse_encoder_tmr6_device *)pulse_encoder;

    /* Enable Timer6 peripheral clock. */
    FCG_Fcg2PeriphClockCmd(hc32_device->u32Fcg2Periph, ENABLE);

    (void)TMR6_StructInit(&stcTmr6Init);
    /* Initializes position-count unit. */
    stcTmr6Init.u8CountSrc = TMR6_CNT_SRC_HW;
    stcTmr6Init.hw_count.u32CountUpCond   = hc32_device->hw_count.u32CountUpCond;
    stcTmr6Init.hw_count.u32CountDownCond = hc32_device->hw_count.u32CountDownCond;
    stcTmr6Init.u32PeriodValue = hc32_device->u32PeriodValue;
    (void)TMR6_Init(hc32_device->tmr_handler, &stcTmr6Init);

    /* OVF interrupt configuration */
    irq_config.irq_num = hc32_device->isr.enIRQn_Ovf;
    irq_config.int_src = hc32_device->isr.enIntSrc_Ovf;
    irq_config.irq_prio = hc32_device->isr.u8Int_Prio_Ovf;
    /* register interrupt */
    hc32_install_irq_handler(&irq_config,
                             hc32_device->isr.Irq_Ovf_Callback,
                             RT_TRUE);
    /* UDF interrupt configuration */
    irq_config.irq_num = hc32_device->isr.enIRQn_Udf;
    irq_config.int_src = hc32_device->isr.enIntSrc_Udf;
    irq_config.irq_prio = hc32_device->isr.u8Int_Prio_Udf;
    /* register interrupt */
    hc32_install_irq_handler(&irq_config,
                             hc32_device->isr.Irq_Udf_Callback,
                             RT_TRUE);

    /* Enable the specified interrupts of Timer6. */
    TMR6_IntCmd(hc32_device->tmr_handler, TMR6_INT_OVF | TMR6_INT_UDF, ENABLE);

    LOG_D("_tmr6_pulse_encoder_init");

    return RT_EOK;
}

rt_err_t _tmr6_pulse_encoder_clear_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    rt_uint8_t startFlag = RT_FALSE;
    struct hc32_pulse_encoder_tmr6_device *hc32_device;
    hc32_device = (struct hc32_pulse_encoder_tmr6_device *)pulse_encoder;
    hc32_device->Over_Under_Flowcount = 0;
    if (READ_REG32_BIT(hc32_device->tmr_handler->GCONR, TMR6_GCONR_START) == TMR6_GCONR_START)
    {
        startFlag = RT_TRUE;
    }
    TMR6_Stop(hc32_device->tmr_handler);
    TMR6_SetCountValue(hc32_device->tmr_handler, 0);
    if (RT_TRUE == startFlag)
    {
        TMR6_Start(hc32_device->tmr_handler);
    }
    return RT_EOK;
}

rt_int32_t _tmr6_pulse_encoder_get_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    struct hc32_pulse_encoder_tmr6_device *hc32_device;
    hc32_device = (struct hc32_pulse_encoder_tmr6_device *)pulse_encoder;
    return (rt_int32_t)((rt_int16_t)TMR6_GetCountValue(hc32_device->tmr_handler) + (hc32_device->Over_Under_Flowcount * (hc32_device->u32PeriodValue + 1)));
}

rt_err_t _tmr6_pulse_encoder_control(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t cmd, void *args)
{
    rt_err_t result;
    struct hc32_pulse_encoder_tmr6_device *hc32_device;
    hc32_device = (struct hc32_pulse_encoder_tmr6_device *)pulse_encoder;

    result = RT_EOK;

    switch (cmd)
    {
    case PULSE_ENCODER_CMD_ENABLE:
        TMR6_Start(hc32_device->tmr_handler);
        LOG_D("TMR6_Start");
        break;
    case PULSE_ENCODER_CMD_DISABLE:
        TMR6_Stop(hc32_device->tmr_handler);
        LOG_D("TMR6_Stop");
        break;
    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

static const struct rt_pulse_encoder_ops _tmr6_ops =
{
    .init = _tmr6_pulse_encoder_init,
    .get_count = _tmr6_pulse_encoder_get_count,
    .clear_count = _tmr6_pulse_encoder_clear_count,
    .control = _tmr6_pulse_encoder_control,
};

#endif /* BSP_USING_TMR6_PULSE_ENCODER */

static int rt_hw_pulse_encoder_init(void)
{
    int result;

    result = RT_EOK;

#if defined(BSP_USING_TMRA_PULSE_ENCODER)
    extern rt_err_t rt_hw_board_pulse_encoder_tmra_init(void);
    result = rt_hw_board_pulse_encoder_tmra_init();
    hc32_get_pulse_encoder_tmra_callback();
    for (int i = 0; i < sizeof(hc32_pulse_encoder_tmra_obj) / sizeof(hc32_pulse_encoder_tmra_obj[0]); i++)
    {
        hc32_pulse_encoder_tmra_obj[i].pulse_encoder.type = AB_PHASE_PULSE_ENCODER;
        hc32_pulse_encoder_tmra_obj[i].pulse_encoder.ops = &_tmra_ops;

        if (rt_device_pulse_encoder_register(&hc32_pulse_encoder_tmra_obj[i].pulse_encoder, hc32_pulse_encoder_tmra_obj[i].name, RT_NULL) != RT_EOK)
        {
            LOG_E("%s register failed", hc32_pulse_encoder_tmra_obj[i].name);
            result = -RT_ERROR;
        }
    }
#endif /* BSP_USING_TMRA_PULSE_ENCODER */

#if defined(BSP_USING_TMR6_PULSE_ENCODER)
    extern rt_err_t rt_hw_board_pulse_encoder_tmr6_init(void);
    result = rt_hw_board_pulse_encoder_tmr6_init();
    hc32_get_pulse_encoder_tmr6_callback();
    for (int i = 0; i < sizeof(hc32_pulse_encoder_tmr6_obj) / sizeof(hc32_pulse_encoder_tmr6_obj[0]); i++)
    {
        hc32_pulse_encoder_tmr6_obj[i].pulse_encoder.type = AB_PHASE_PULSE_ENCODER;
        hc32_pulse_encoder_tmr6_obj[i].pulse_encoder.ops = &_tmr6_ops;

        if (rt_device_pulse_encoder_register(&hc32_pulse_encoder_tmr6_obj[i].pulse_encoder, hc32_pulse_encoder_tmr6_obj[i].name, RT_NULL) != RT_EOK)
        {
            LOG_E("%s register failed", hc32_pulse_encoder_tmr6_obj[i].name);
            result = -RT_ERROR;
        }
    }
#endif /* BSP_USING_TMR6_PULSE_ENCODER */

    return result;
}
INIT_BOARD_EXPORT(rt_hw_pulse_encoder_init);

#endif /* RT_USING_PULSE_ENCODER */
