/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author               Notes
 * 2025-01-10     CDT                  first version
 */

#include <rtconfig.h>

#if defined(BSP_USING_INPUT_CAPTURE)
#if defined(BSP_USING_INPUT_CAPTURE_TMR6_1) || defined(BSP_USING_INPUT_CAPTURE_TMR6_2) || defined(BSP_USING_INPUT_CAPTURE_TMR6_3) \
|| defined(BSP_USING_INPUT_CAPTURE_TMR6_4) || defined(BSP_USING_INPUT_CAPTURE_TMR6_5) || defined(BSP_USING_INPUT_CAPTURE_TMR6_6)  \
|| defined(BSP_USING_INPUT_CAPTURE_TMR6_7) || defined(BSP_USING_INPUT_CAPTURE_TMR6_8)

#include <rtdevice.h>
#include <drv_config.h>
#include <board_config.h>
#include "hc32_ll.h"
#include <drv_tmr_capture.h>

/* Private typedef --------------------------------------------------------------*/
typedef struct
{
    struct rt_inputcapture_device   parent;
    struct tmr_capture_dev_init_params init_params;
    uint32_t clk;
    void *tmr_instance;
    __IO uint32_t    cur_cnt;
    __IO uint32_t    ovf_cnt;
    __IO rt_bool_t   input_data_level;
    __IO rt_bool_t   is_first_edge;
    __IO rt_bool_t   is_open;
    uint32_t cond;
    en_int_src_t int_src_cap;
    en_int_src_t int_src_ovf;
    func_ptr_t isr_cap;
    func_ptr_t isr_ovf;
} tmr_capture_t;

enum
{
#ifdef BSP_USING_INPUT_CAPTURE_TMR6_1
    TMR_CAPTURE_IDX_TMR6_1,
#endif
#ifdef BSP_USING_INPUT_CAPTURE_TMR6_2
    TMR_CAPTURE_IDX_TMR6_2,
#endif
#ifdef BSP_USING_INPUT_CAPTURE_TMR6_3
    TMR_CAPTURE_IDX_TMR6_3,
#endif
#ifdef BSP_USING_INPUT_CAPTURE_TMR6_4
    TMR_CAPTURE_IDX_TMR6_4,
#endif
#ifdef BSP_USING_INPUT_CAPTURE_TMR6_5
    TMR_CAPTURE_IDX_TMR6_5,
#endif
#ifdef BSP_USING_INPUT_CAPTURE_TMR6_6
    TMR_CAPTURE_IDX_TMR6_6,
#endif
#ifdef BSP_USING_INPUT_CAPTURE_TMR6_7
    TMR_CAPTURE_IDX_TMR6_7,
#endif
#ifdef BSP_USING_INPUT_CAPTURE_TMR6_8
    TMR_CAPTURE_IDX_TMR6_8,
#endif
    TMR_CAPTURE_IDX_MAX,
};

/* Private functions ------------------------------------------------------------*/
static rt_err_t _tmr_capture_init(struct rt_inputcapture_device *inputcapture);
static rt_err_t _tmr_capture_open(struct rt_inputcapture_device *inputcapture);
static rt_err_t _tmr_capture_close(struct rt_inputcapture_device *inputcapture);
static rt_err_t _tmr_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us);
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_1)
    static void _tmr6_1_isr_ovf(void);
    static void _tmr6_1_isr_cap(void);
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_2)
    static void _tmr6_2_isr_ovf(void);
    static void _tmr6_2_isr_cap(void);
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_3)
    static void _tmr6_3_isr_ovf(void);
    static void _tmr6_3_isr_cap(void);
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_4)
    static void _tmr6_4_isr_ovf(void);
    static void _tmr6_4_isr_cap(void);
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_5)
    static void _tmr6_5_isr_ovf(void);
    static void _tmr6_5_isr_cap(void);
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_6)
    static void _tmr6_6_isr_ovf(void);
    static void _tmr6_6_isr_cap(void);
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_7)
    static void _tmr6_7_isr_ovf(void);
    static void _tmr6_7_isr_cap(void);
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_8)
    static void _tmr6_8_isr_ovf(void);
    static void _tmr6_8_isr_cap(void);
#endif

/* Private define ---------------------------------------------------------------*/
#define TMR6_INSTANCE_MIN                                   ((uint32_t)CM_TMR6_1)
#if defined (HC32F4A0)
    #define TMR6_INSTANCE_MAX                               ((uint32_t)CM_TMR6_8)
#elif defined (HC32F460)
    #define TMR6_INSTANCE_MAX                               ((uint32_t)CM_TMR6_3)
#endif
#define TMR6_INSTANCE_ADDR_ALIGN                            (0x400UL)
#define TMR6_PERIOD_VALUE_MAX                               (0xFFFFUL)
#define IS_TMR6_UNIT(x)                                     (((x) >= TMR6_INSTANCE_MIN && (x) <= TMR6_INSTANCE_MAX) && ((x) % TMR6_INSTANCE_ADDR_ALIGN) == 0U)

#if defined (BSP_USING_INPUT_CAPTURE_TMR6)
    #define IS_CAPTURE_COND_RASING_EDGE(bit_pos)            ((bit_pos) % 2U == 0U)
    #if defined (HC32F4A0)
        #define VALID_CAPTURE_COND                          (TMR6_CAPT_COND_ALL & (~(TMR6_CAPT_COND_EVT0 | TMR6_CAPT_COND_EVT1 | TMR6_CAPT_COND_EVT2 | TMR6_CAPT_COND_EVT3)))
    #elif defined (HC32F460)
        #define VALID_CAPTURE_COND                          (TMR6_CAPT_COND_ALL & (~(TMR6_CAPT_COND_EVT0 | TMR6_CAPT_COND_EVT1)))
    #endif
#endif

#define TMR6_ISR_OVF(U)     \
static void _tmr6_##U##_isr_ovf(void)\
{\
    g_tmr_capturers[TMR_CAPTURE_IDX_TMR6_##U].ovf_cnt++;\
    TMR6_ClearStatus(CM_TMR6_##U, TMR6_FLAG_OVF);\
}

#define TMR6_ISR_CAP(U)     \
static void _tmr6_##U##_isr_cap(void)\
{\
  _tmr6_irq_cap_handler(&g_tmr_capturers[TMR_CAPTURE_IDX_TMR6_##U]);\
}

#define TMR6_CAPTURE_CFG(U)                                                                 \
{   {0}, INPUT_CAPTURE_CFG_TMR6_##U, 0, (CM_TMR6_##U), 0, 0, 0, 0, 0, 0,                    \
    INT_SRC_TMR6_##U##_GCMP_A, INT_SRC_TMR6_##U##_OVF, _tmr6_##U##_isr_cap, _tmr6_##U##_isr_ovf,    \
}

/* Private variables ------------------------------------------------------------*/
static tmr_capture_t g_tmr_capturers[] =
{
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_1)
    TMR6_CAPTURE_CFG(1),
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_2)
    TMR6_CAPTURE_CFG(2),
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_3)
    TMR6_CAPTURE_CFG(3),
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_4)
    TMR6_CAPTURE_CFG(4),
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_5)
    TMR6_CAPTURE_CFG(5),
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_6)
    TMR6_CAPTURE_CFG(6),
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_7)
    TMR6_CAPTURE_CFG(7),
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_8)
    TMR6_CAPTURE_CFG(8),
#endif
};

static struct rt_inputcapture_ops tmr_capture_ops =
{
    .init   =   _tmr_capture_init,
    .open   =   _tmr_capture_open,
    .close  =   _tmr_capture_close,
    .get_pulsewidth =   _tmr_capture_get_pulsewidth,
};

/* Functions define ------------------------------------------------------------*/
static void _tmr6_irq_cap_handler(tmr_capture_t *p_capture)
{
    if (p_capture->is_first_edge == RT_TRUE)
    {
        p_capture->is_first_edge = RT_FALSE;
    }
    else
    {
        p_capture->cur_cnt = TMR6_GetCompareValue((CM_TMR6_TypeDef *)p_capture->tmr_instance, \
                             p_capture->init_params.ch);
        rt_interrupt_enter();
        rt_hw_inputcapture_isr(&p_capture->parent, p_capture->input_data_level);
        rt_interrupt_leave();
        p_capture->input_data_level = !p_capture->input_data_level;
    }
    p_capture->ovf_cnt = 0;
    TMR6_ClearStatus((CM_TMR6_TypeDef *)p_capture->tmr_instance, \
                     TMR6_FLAG_MATCH_A << p_capture->init_params.ch);
}

#if defined (BSP_USING_INPUT_CAPTURE_TMR6_1)
    TMR6_ISR_OVF(1)
    TMR6_ISR_CAP(1)
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_2)
    TMR6_ISR_OVF(2)
    TMR6_ISR_CAP(2)
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_3)
    TMR6_ISR_OVF(3)
    TMR6_ISR_CAP(3)
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_4)
    TMR6_ISR_OVF(4)
    TMR6_ISR_CAP(4)
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_5)
    TMR6_ISR_OVF(5)
    TMR6_ISR_CAP(5)
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_6)
    TMR6_ISR_OVF(6)
    TMR6_ISR_CAP(6)
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_7)
    TMR6_ISR_OVF(7)
    TMR6_ISR_CAP(7)
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_8)
    TMR6_ISR_OVF(8)
    TMR6_ISR_CAP(8)
#endif

static void _tmr_irq_init_cap(tmr_capture_t *p_capture)
{
    stc_irq_signin_config_t stcIrq;
    stcIrq.pfnCallback = p_capture->isr_cap;
    stcIrq.enIntSrc    = (en_int_src_t)((uint32_t)p_capture->int_src_cap + p_capture->init_params.ch);
    stcIrq.enIRQn      = p_capture->init_params.irq_num_cap;
    (void)INTC_IrqSignIn(&stcIrq);
    NVIC_ClearPendingIRQ(stcIrq.enIRQn);
    NVIC_SetPriority(stcIrq.enIRQn, p_capture->init_params.irq_prio_cap);
}

static void _tmr_irq_init_ovf(tmr_capture_t *p_capture)
{
    stc_irq_signin_config_t stcIrq;
    stcIrq.pfnCallback = p_capture->isr_ovf;
    stcIrq.enIntSrc = (en_int_src_t)(p_capture->int_src_ovf);
    stcIrq.enIRQn      = p_capture->init_params.irq_num_ovf;
    (void)INTC_IrqSignIn(&stcIrq);
    NVIC_ClearPendingIRQ(stcIrq.enIRQn);
    NVIC_SetPriority(stcIrq.enIRQn, p_capture->init_params.irq_prio_ovf);
}

static rt_bool_t _is_one_cond(uint32_t n)
{
    uint32_t count = 0;
    for (uint32_t i = 0U; i < 32U; i++)
    {
        if ((n & (1UL << i)) != 0UL)
        {
            count++;
            if (count > 1U)
            {
                return RT_FALSE;
            }
        }
    }

    return RT_TRUE;
}

static uint32_t _get_capture_cond_bit_pos(uint32_t n)
{
    uint32_t i;
    for (i = 0U; i < 32U; i++)
    {
        if ((n & (1UL << i)) != 0UL)
        {
            break;
        }
    }

    return i;
}

static void _tmr_capture_assert_params(tmr_capture_t *p_capture)
{
    struct tmr_capture_dev_init_params *p_init_params = &(p_capture->init_params);

    RT_ASSERT(p_init_params->first_edge != 0U);
    RT_ASSERT(_is_one_cond(p_init_params->first_edge));
    RT_ASSERT((p_init_params->first_edge | VALID_CAPTURE_COND) == VALID_CAPTURE_COND);
#if defined (BSP_USING_INPUT_CAPTURE_TMR6)
    RT_ASSERT((p_init_params->ch == TMR6_CH_A) || (p_init_params->ch == TMR6_CH_B));
#endif
}

static void _tmr_capture_init_tmr6(tmr_capture_t *p_capture, CM_TMR6_TypeDef *instance, struct tmr_capture_dev_init_params *init_params)
{
    uint32_t unit = ((uint32_t)p_capture->tmr_instance - (uint32_t)CM_TMR6_1) / TMR6_INSTANCE_ADDR_ALIGN;

    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR6_1 << unit, ENABLE);
#if defined (HC32F460)
    if (instance != CM_TMR6_1)
    {
        FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR6_1, ENABLE);
    }
#endif
    stc_tmr6_init_t stcTmr6Init;
    (void)TMR6_StructInit(&stcTmr6Init);
    stcTmr6Init.u8CountSrc = TMR6_CNT_SRC_SW;
    stcTmr6Init.sw_count.u32ClockDiv = init_params->clk_div;
    stcTmr6Init.u32PeriodValue = TMR6_PERIOD_VALUE_MAX;
    (void)TMR6_Init(instance, &stcTmr6Init);
    TMR6_SetFunc(instance, init_params->ch, TMR6_PIN_CAPT_INPUT);

    uint32_t pin;
    uint32_t bit_pos = _get_capture_cond_bit_pos(init_params->first_edge);
#if defined (HC32F4A0)
    if (bit_pos <= TMR6_HCPAR_HCPA3_POS)
    {
        pin = TMR6_IO_PWMA + (bit_pos / 2U);
    }
    else
    {
        pin = TMR6_INPUT_TRIGA + (bit_pos - TMR6_HCPAR_HCPA16_POS) / 2U;
    }
#elif defined (HC32F460)
    pin = TMR6_IO_PWMA + (bit_pos - TMR6_HCPAR_HCPA4_POS) / 2U;
#endif
    TMR6_SetFilterClockDiv(instance, pin, TMR6_FILTER_CLK_DIV16);
    TMR6_FilterCmd(instance, pin, ENABLE);
    TMR6_HWCaptureCondCmd(instance, p_capture->init_params.ch, p_capture->cond, ENABLE);
    TMR6_HWClearCondCmd(instance, p_capture->cond, ENABLE);
    TMR6_HWClearCmd(instance, ENABLE);
    TMR6_IntCmd(instance, TMR6_INT_OVF, ENABLE);
    TMR6_IntCmd(instance, TMR6_INT_MATCH_A << init_params->ch, ENABLE);
}

static rt_err_t _tmr_capture_init(struct rt_inputcapture_device *inputcapture)
{
    RT_ASSERT(inputcapture != (void *)RT_NULL);
    rt_err_t ret = RT_EOK;
    tmr_capture_t *p_capture = (tmr_capture_t *)(void *)inputcapture;
    struct tmr_capture_dev_init_params *init_params = &(p_capture->init_params);

    rt_hw_board_input_capture_init(p_capture->tmr_instance);

    _tmr_irq_init_cap(p_capture);
    _tmr_irq_init_ovf(p_capture);

    uint32_t bit_pos = _get_capture_cond_bit_pos(init_params->first_edge);
    uint32_t second_edge = (IS_CAPTURE_COND_RASING_EDGE(bit_pos)) ? (1UL << (bit_pos + 1UL)) : (1UL << (bit_pos - 1UL));
    p_capture->cond = init_params->first_edge | second_edge;
    p_capture->clk = (HCLK_VALUE / (1UL << (init_params->clk_div >> TMR6_GCONR_CKDIV_POS)));

    do
    {
#if defined(BSP_USING_INPUT_CAPTURE_TMR6)
        CM_TMR6_TypeDef *instance = (CM_TMR6_TypeDef *)(p_capture->tmr_instance);
        if (IS_TMR6_UNIT((uint32_t)instance))
        {
            _tmr_capture_init_tmr6(p_capture, instance, init_params);
            break;
        }
#endif
        break;
    }
    while (0);

    return ret;
}

static rt_err_t _tmr_capture_open(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;
    RT_ASSERT(inputcapture != (void *)RT_NULL);

    tmr_capture_t *p_capture = (tmr_capture_t *)(void *)inputcapture;
    if (p_capture->is_open)
    {
        return ret;
    }

    struct tmr_capture_dev_init_params *init_params = &(p_capture->init_params);
    uint32_t bit_pos = _get_capture_cond_bit_pos(init_params->first_edge);
    p_capture->input_data_level = IS_CAPTURE_COND_RASING_EDGE(bit_pos);
    p_capture->is_first_edge = RT_TRUE;
    p_capture->is_open = RT_TRUE;

    NVIC_EnableIRQ(init_params->irq_num_ovf);
    NVIC_EnableIRQ(init_params->irq_num_cap);
    do
    {
#if defined(BSP_USING_INPUT_CAPTURE_TMR6)
        CM_TMR6_TypeDef *instance = (CM_TMR6_TypeDef *)(p_capture->tmr_instance);
        if (IS_TMR6_UNIT((uint32_t)instance))
        {
            TMR6_Start(instance);
            break;
        }
#endif
    }
    while (0);

    return ret;
}

static rt_err_t _tmr_capture_close(struct rt_inputcapture_device *inputcapture)
{
    rt_err_t ret = RT_EOK;
    tmr_capture_t *p_capture;

    RT_ASSERT(inputcapture != (void *)RT_NULL);

    p_capture = (tmr_capture_t *)(void *) inputcapture;
    NVIC_DisableIRQ(p_capture->init_params.irq_num_ovf);
    NVIC_DisableIRQ(p_capture->init_params.irq_num_cap);
    do
    {
#if defined(BSP_USING_INPUT_CAPTURE_TMR6)
        CM_TMR6_TypeDef *instance = (CM_TMR6_TypeDef *)(p_capture->tmr_instance);
        if (IS_TMR6_UNIT((uint32_t)instance))
        {
            TMR6_Stop((CM_TMR6_TypeDef *)instance);
            break;
        }
#endif
    }
    while (0);

    p_capture->is_open = RT_FALSE;
    return ret;
}

static rt_err_t _tmr_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture, rt_uint32_t *pulsewidth_us)
{
    rt_err_t ret = RT_EOK;
    RT_ASSERT(inputcapture != (void *)RT_NULL);

    tmr_capture_t *p_capture = (tmr_capture_t *)(void *)inputcapture;
    rt_uint64_t ovf_cnt = p_capture->ovf_cnt;
    rt_uint64_t cur_cnt = p_capture->cur_cnt;
    rt_uint64_t cnt = (uint64_t)((ovf_cnt * (uint64_t)TMR6_PERIOD_VALUE_MAX + cur_cnt) * (uint64_t)1000000);

    *pulsewidth_us = (uint32_t)((uint64_t)(cnt / (uint64_t)p_capture->clk) + 1U);

    return ret;
}

int tmr_capture_device_init(void)
{
    for (uint32_t i = 0U; i < (uint32_t)TMR_CAPTURE_IDX_MAX; i++)
    {
#if defined RT_DEBUGING_ASSERT
        _tmr_capture_assert_params(&g_tmr_capturers[i]);
#endif
        g_tmr_capturers[i].parent.ops = &tmr_capture_ops;
        rt_device_inputcapture_register(&g_tmr_capturers[i].parent, \
                                        g_tmr_capturers[i].init_params.name,
                                        &g_tmr_capturers[i]);
    }

    return 0;
}
INIT_DEVICE_EXPORT(tmr_capture_device_init);
#endif //#if defined(BSP_USING_INPUT_CAPTURE_*)
#endif //#if defined(BSP_USING_INPUT_CAPTURE)
