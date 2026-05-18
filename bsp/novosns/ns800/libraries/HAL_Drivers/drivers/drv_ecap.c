/**************************************************************************//**
*
* @copyright (C) 2026 Novosense Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2026-5-7        Alex-J           First version
*
******************************************************************************/
#include <rtconfig.h>
#include "drv_ecap.h"

#if defined(BSP_USING_ECAP)

#define DBG_TAG    "drv.ecap"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

static const struct rt_ecap_config ecap1_config =
{
    .name         = "ecap1",
    .instance     = ECAP1,
    .irq_type     = ECAP1_IRQn,
    .input_xbar   = XBAR_INPUT7,
    .input_source = GPIO_PIN_16,
    .gpio_port    = GPIOA,
    .gpio_pin     = GPIO_PIN_16,
    .gpio_mux     = ALT0_FUNCTION,
};

static struct rt_ecap_device ecap1_dev;

void ECAP1_IRQHandler (void);

/*
 *
 */
static void ecap_gpio_init (const struct rt_ecap_config *config)
{
    RT_ASSERT(config != RT_NULL);

    GPIO_setPinConfig(config->gpio_port, config->gpio_pin, config->gpio_mux);
    GPIO_setAnalogMode(config->gpio_port, config->gpio_pin, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(config->gpio_port, config->gpio_pin, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(config->gpio_port, config->gpio_pin, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(config->gpio_port, config->gpio_pin, GPIO_DIR_MODE_IN);
}

/*
 *
 */
static void ecap_xbar_init (const struct rt_ecap_config *config)
{
    RT_ASSERT(config != RT_NULL);

    XBAR_setInputPin(XBAR, config->input_xbar, config->input_source);
}

/*
 *
 */
static void ecap_hw_init (const struct rt_ecap_config *config)
{
    RT_ASSERT(config != RT_NULL);

    /*
     * Disable and clear all capture flags and interrupts.
     */
    ECAP_disableInterrupt(config->instance, ECAP_ECEINT_CEVT1_M | ECAP_ECEINT_CEVT2_M | ECAP_ECEINT_CEVT3_M |
                                                ECAP_ECEINT_CEVT4_M | ECAP_ECEINT_CTROVF_M | ECAP_ECEINT_CTREQPRD_M |
                                                ECAP_ECEINT_CTREQCMP_M);

    ECAP_clearInterrupt(config->instance, ECAP_ECCLR_CEVT1_M | ECAP_ECCLR_CEVT2_M | ECAP_ECCLR_CEVT3_M |
                                              ECAP_ECCLR_CEVT4_M | ECAP_ECCLR_CTROVF_M | ECAP_ECCLR_CTRPRD_M |
                                              ECAP_ECCLR_CTRCMP_M);

    ECAP_disableTimeStampCapture(config->instance);
    ECAP_stopCounter(config->instance);

    /*
     * Capture mode:
     * Event1 falling
     * Event2 rising
     * Event3 falling
     * Event4 rising
     */
    ECAP_enableCaptureMode(config->instance);
    ECAP_setCaptureMode(config->instance, ECAP_CONTINUOUS_CAPTURE_MODE, ECAP_EVENT_4);
    ECAP_setEventPrescaler(config->instance, 0U);

    ECAP_setEventPolarity(config->instance, ECAP_EVENT_1, ECAP_EVNT_FALLING_EDGE);
    ECAP_setEventPolarity(config->instance, ECAP_EVENT_2, ECAP_EVNT_RISING_EDGE);
    ECAP_setEventPolarity(config->instance, ECAP_EVENT_3, ECAP_EVNT_FALLING_EDGE);
    ECAP_setEventPolarity(config->instance, ECAP_EVENT_4, ECAP_EVNT_RISING_EDGE);

    ECAP_enableCounterResetOnEvent(config->instance, ECAP_EVENT_1);
    ECAP_enableCounterResetOnEvent(config->instance, ECAP_EVENT_2);
    ECAP_enableCounterResetOnEvent(config->instance, ECAP_EVENT_3);
    ECAP_enableCounterResetOnEvent(config->instance, ECAP_EVENT_4);

    ECAP_selectECAPInput(config->instance, ECAP_INPUT_XBAR_INPUT7);

    ECAP_setPhaseShiftCount(config->instance, 0U);
    ECAP_enableLoadCounter(config->instance);

    ECAP_setSyncOutMode(config->instance, ECAP_SYNC_OUT_SYNCI);
    ECAP_setEmulationMode(config->instance, ECAP_EMULATION_STOP);
    ECAP_setSyncInPulseSource(config->instance, ECAP_SYNC_IN_PULSE_SRC_DISABLE);

    /* ECAP_startCounter(config->instance); */
    /* ECAP_enableTimeStampCapture(config->instance); */
    /* ECAP_reArm(config->instance); */

    /*
     * 当前配置是 Event4 完成后产生中断。
     */
    /* ECAP_enableInterrupt(config->instance, ECAP_ECEINT_CEVT4_M); */
}

/*
 *
 */
static void ecap_hw_deinit (const struct rt_ecap_config *config)
{
    RT_ASSERT(config != RT_NULL);

    ECAP_disableInterrupt(config->instance, ECAP_ECEINT_CEVT1_M | ECAP_ECEINT_CEVT2_M | ECAP_ECEINT_CEVT3_M |
                                                ECAP_ECEINT_CEVT4_M | ECAP_ECEINT_CTROVF_M | ECAP_ECEINT_CTREQPRD_M |
                                                ECAP_ECEINT_CTREQCMP_M);

    ECAP_disableTimeStampCapture(config->instance);
    ECAP_stopCounter(config->instance);
}

static void ecap_hw_clear_flags (const struct rt_ecap_config *config)
{
    RT_ASSERT(config != RT_NULL);

    ECAP_clearInterrupt(config->instance, ECAP_ECCLR_CEVT1_M | ECAP_ECCLR_CEVT2_M | ECAP_ECCLR_CEVT3_M |
                                              ECAP_ECCLR_CEVT4_M | ECAP_ECCLR_CTROVF_M | ECAP_ECCLR_CTRPRD_M |
                                              ECAP_ECCLR_CTRCMP_M);
    ECAP_clearGlobalInterrupt(config->instance);
}

static void ecap_hw_rearm (const struct rt_ecap_config *config)
{
    RT_ASSERT(config != RT_NULL);

    ecap_hw_clear_flags(config);
    ECAP_reArm(config->instance);
}

static void ecap_calc_capture (struct rt_ecap_capture *cap)
{
    RT_ASSERT(cap != RT_NULL);

    /*
     * 由于当前配置为：
     * Event1 falling
     * Event2 rising
     * Event3 falling
     * Event4 rising
     *
     * 且每个 event 都 reset counter。
     *
     * 所以 cap1~cap4 并不是一个自由运行时间轴上的绝对时间戳，
     * 而是每段边沿之间的间隔计数。
     *
     * 这里给一个通用解释：
     * cap2: falling -> rising
     * cap3: rising  -> falling
     * cap4: falling -> rising
     *
     * 对 PWM 输入来说，需要根据实际输入波形起始边沿判断高低电平。
     */
    cap->period_high  = cap->cap2;
    cap->period_low   = cap->cap3;
    cap->period_total = cap->cap2 + cap->cap3;
}

static rt_err_t rt_ecap_init (rt_device_t dev)
{
    struct rt_ecap_device *ecap;

    RT_ASSERT(dev != RT_NULL);

    ecap = (struct rt_ecap_device *)dev;

    ecap_gpio_init(ecap->config);
    ecap_xbar_init(ecap->config);
    ecap_hw_init(ecap->config);

    ecap->last_capture.status = ECAP_STATUS_IDLE;

    return RT_EOK;
}

static rt_err_t rt_ecap_open (rt_device_t dev, rt_uint16_t oflag)
{
    struct rt_ecap_device *ecap;

    RT_ASSERT(dev != RT_NULL);

    ecap = (struct rt_ecap_device *)dev;

    rt_mutex_take(&ecap->lock, RT_WAITING_FOREVER);

    if (ecap->opened == 0U)
    {
        ecap_hw_clear_flags(ecap->config);
        ECAP_startCounter(ecap->config->instance);
        ECAP_enableTimeStampCapture(ecap->config->instance);
        ECAP_reArm(ecap->config->instance);
        ECAP_enableInterrupt(ecap->config->instance, ECAP_ECEINT_CEVT4_M);

        Interrupt_register(ecap->config->irq_type, &ECAP1_IRQHandler);
        Interrupt_enable(ecap->config->irq_type);
    }

    ecap->opened++;

    rt_mutex_release(&ecap->lock);

    return RT_EOK;
}

static rt_err_t rt_ecap_close (rt_device_t dev)
{
    struct rt_ecap_device *ecap;

    RT_ASSERT(dev != RT_NULL);

    ecap = (struct rt_ecap_device *)dev;

    rt_mutex_take(&ecap->lock, RT_WAITING_FOREVER);

    if (ecap->opened > 0U)
    {
        ecap->opened--;

        if (ecap->opened == 0U)
        {
            ECAP_disableInterrupt(ecap->config->instance, ECAP_ECEINT_CEVT4_M);
            ECAP_disableTimeStampCapture(ecap->config->instance);
            ECAP_stopCounter(ecap->config->instance);
            Interrupt_disable(ecap->config->irq_type);
        }
    }

    rt_mutex_release(&ecap->lock);

    return RT_EOK;
}

static rt_ssize_t rt_ecap_read (rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct rt_ecap_device *ecap;
    struct rt_ecap_capture *cap;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    ecap = (struct rt_ecap_device *)dev;

    if (size < sizeof(struct rt_ecap_capture))
    {
        return 0;
    }

    /*
     * 阻塞等待一次完整 capture。
     * 如果不希望阻塞，可以改成 RT_WAITING_NO。
     */
    if (rt_sem_take(&ecap->rx_sem, RT_WAITING_FOREVER) != RT_EOK)
    {
        return 0;
    }

    rt_mutex_take(&ecap->lock, RT_WAITING_FOREVER);

    cap  = (struct rt_ecap_capture *)buffer;
    *cap = ecap->last_capture;

    rt_mutex_release(&ecap->lock);

    return sizeof(struct rt_ecap_capture);
}

static rt_err_t rt_ecap_control (rt_device_t dev, int cmd, void *args)
{
    struct rt_ecap_device *ecap;

    RT_ASSERT(dev != RT_NULL);

    ecap = (struct rt_ecap_device *)dev;

    switch (cmd)
    {
        case ECAP_CMD_ENABLE:
            ECAP_startCounter(ecap->config->instance);
            ECAP_enableTimeStampCapture(ecap->config->instance);
            ECAP_enableInterrupt(ecap->config->instance, ECAP_ECEINT_CEVT4_M);
            break;

        case ECAP_CMD_DISABLE:
            ECAP_disableInterrupt(ecap->config->instance, ECAP_ECEINT_CEVT4_M);
            ECAP_disableTimeStampCapture(ecap->config->instance);
            ECAP_stopCounter(ecap->config->instance);
            break;

        case ECAP_CMD_REARM:
            ecap_hw_rearm(ecap->config);
            break;

        case ECAP_CMD_GET_LAST_CAPTURE:
            if (args == RT_NULL)
            {
                return -RT_EINVAL;
            }

            rt_mutex_take(&ecap->lock, RT_WAITING_FOREVER);
            *(struct rt_ecap_capture *)args = ecap->last_capture;
            rt_mutex_release(&ecap->lock);
            break;

        case ECAP_CMD_SET_CALLBACK:
        {
            struct rt_ecap_callback *cb;

            if (args == RT_NULL)
            {
                return -RT_EINVAL;
            }

            cb = (struct rt_ecap_callback *)args;

            rt_mutex_take(&ecap->lock, RT_WAITING_FOREVER);
            ecap->rx_callback  = cb->callback;
            ecap->rx_user_data = cb->user_data;
            rt_mutex_release(&ecap->lock);
            break;
        }

        case ECAP_CMD_CLEAR_FLAGS:
            ecap_hw_clear_flags(ecap->config);
            break;

        case ECAP_CMD_ENABLE_IRQ:
            ECAP_enableInterrupt(ecap->config->instance, ECAP_ECEINT_CEVT4_M);
            Interrupt_register(ecap->config->irq_type, &ECAP1_IRQHandler);
            Interrupt_enable(ecap->config->irq_type);
            break;

        case ECAP_CMD_DISABLE_IRQ:
            ECAP_disableInterrupt(ecap->config->instance, ECAP_ECEINT_CEVT4_M);
            Interrupt_disable(ecap->config->irq_type);
            break;

        default:
            return -RT_EINVAL;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops ecap_ops =
{
    rt_ecap_init,
    rt_ecap_open,
    rt_ecap_close,
    rt_ecap_read,
    RT_NULL,
    rt_ecap_control
};
#endif

static rt_err_t rt_hw_ecap_register (struct rt_ecap_device *ecap, const struct rt_ecap_config *config)
{
    struct rt_device *dev;

    RT_ASSERT(ecap != RT_NULL);
    RT_ASSERT(config != RT_NULL);

    rt_memset(ecap, 0, sizeof(struct rt_ecap_device));

    ecap->config = config;

    rt_mutex_init(&ecap->lock, config->name, RT_IPC_FLAG_PRIO);
    rt_sem_init(&ecap->rx_sem, config->name, 0, RT_IPC_FLAG_FIFO);

    dev              = &ecap->parent;

    dev->type        = RT_Device_Class_Miscellaneous;
    dev->rx_indicate = RT_NULL;
    dev->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    dev->ops = &ecap_ops;
#else
    dev->init    = rt_ecap_init;
    dev->open    = rt_ecap_open;
    dev->close   = rt_ecap_close;
    dev->read    = rt_ecap_read;
    dev->write   = RT_NULL;
    dev->control = rt_ecap_control;
#endif

    return rt_device_register(dev, config->name, RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_INT_RX);
}

int rt_hw_ecap_init (void)
{
    rt_err_t ret;

    ret = rt_hw_ecap_register(&ecap1_dev, &ecap1_config);

    if (ret != RT_EOK)
    {
        LOG_E("register ecap1 failed, ret = %d", ret);
        return ret;
    }

    LOG_I("ecap1 register done");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_ecap_init);

/*
 *
 */
void rt_hw_ecap1_isr(void)
{
    struct rt_ecap_device *ecap;
    struct rt_ecap_capture cap;

    ecap = &ecap1_dev;

    rt_interrupt_enter();

    rt_memset(&cap, 0, sizeof(cap));

    cap.cap1 = ECAP_getEventTimeStamp(ecap->config->instance, ECAP_EVENT_1);
    cap.cap2 = ECAP_getEventTimeStamp(ecap->config->instance, ECAP_EVENT_2);
    cap.cap3 = ECAP_getEventTimeStamp(ecap->config->instance, ECAP_EVENT_3);
    cap.cap4 = ECAP_getEventTimeStamp(ecap->config->instance, ECAP_EVENT_4);

    cap.status = ECAP_STATUS_DONE;
    ecap_calc_capture(&cap);

    ecap->last_capture = cap;

    /*
     * 当前是 one-shot capture mode，所以一次捕获完成后需要 re-arm。
     */
    ecap_hw_clear_flags(ecap->config);

    rt_sem_release(&ecap->rx_sem);

    if (ecap->rx_callback != RT_NULL)
    {
        ecap->rx_callback((struct rt_ecap_capture *)&ecap->last_capture,
                          ecap->rx_user_data);
    }

    rt_interrupt_leave();
}

void ECAP1_IRQHandler (void)
{
    rt_hw_ecap1_isr();
}


#endif /* #if defined(BSP_USING_ECAP) */

