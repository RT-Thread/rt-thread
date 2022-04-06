/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-01-18   onelife     Initial creation for EFM32
 * 2011-06-17   onelife     Modify init function for efm32lib v2 upgrading
 */

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "drv_timer.h"

#if (defined(RT_USING_TIMER0) || defined(RT_USING_TIMER1) || defined(RT_USING_TIMER2))
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef RT_TIMER_DEBUG
#define timer_debug(format,args...)         rt_kprintf(format, ##args)
#else
#define timer_debug(format,args...)
#endif
#define TIMER_TopCalculate(p) \
        (p * (EFM32_HFXO_FREQUENCY / (1 << TMR_CFG_PRESCALER) / 1000))

/* Private variables ---------------------------------------------------------*/
#ifdef RT_USING_TIMER0
    static struct rt_device timer0_device;
#endif
#ifdef RT_USING_TIMER1
    static struct rt_device timer1_device;
#endif
#ifdef RT_USING_TIMER2
    static struct rt_device timer2_device;
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/***************************************************************************//**
 * @brief
 *   Initialize Timer device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @return
 *   Error code
 ******************************************************************************/
 static rt_err_t rt_hs_timer_init (rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    struct efm32_timer_device_t *timer;

    timer = (struct efm32_timer_device_t *)(dev->user_data);

    timer->hook.cbFunc = RT_NULL;
    timer->hook.userPtr = RT_NULL;

    return RT_EOK;
}

/***************************************************************************//**
* @brief
*   Configure Timer device
*
* @details
*
* @note
*
* @param[in] dev
*   Pointer to device descriptor
*
* @param[in] cmd
*   Timer control command
*
* @param[in] args
*   Arguments
*
* @return
*   Error code
******************************************************************************/
static rt_err_t rt_hs_timer_control (
    rt_device_t     dev,
    rt_uint8_t      cmd,
    void            *args)
{
    RT_ASSERT(dev != RT_NULL);

    struct efm32_timer_device_t *timer;

    timer = (struct efm32_timer_device_t *)(dev->user_data);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SUSPEND:
        /* Suspend device */
        dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
        TIMER_Enable(timer->timer_device, false);
        break;

    case RT_DEVICE_CTRL_RESUME:
        /* Resume device */
        dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
        TIMER_Enable(timer->timer_device, true);
        break;

    case RT_DEVICE_CTRL_TIMER_PERIOD:
        {
            /* change device setting */
            struct efm32_timer_control_t *control;
            rt_uint32_t running;

            control = (struct efm32_timer_control_t *)args;
            running = timer->timer_device->STATUS & 0x00000001;

            TIMER_Enable(timer->timer_device, false);
            timer->timer_device->CNT = _TIMER_CNT_RESETVALUE;
            TIMER_TopSet(timer->timer_device, TIMER_TopCalculate(control->period));
            timer->hook.cbFunc = control->hook.cbFunc;
            timer->hook.userPtr = control->hook.userPtr;
            if (running)
            {
                TIMER_Enable(timer->timer_device, true);
            }
        }
        break;
    }

    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Register Timer device
 *
 * @details
 *
 * @note
 *
 * @param[in] device
 *   Pointer to device descriptor
 *
 * @param[in] name
 *   Device name
 *
 * @param[in] flag
 *   Configuration flags
 *
 * @param[in] timer
 *   Pointer to Timer device descriptor
 *
 * @return
 *   Error code
 ******************************************************************************/
rt_err_t rt_hw_timer_register(
    rt_device_t     device,
    const char      *name,
    rt_uint32_t     flag,
    struct efm32_timer_device_t *timer)
{
    RT_ASSERT(device != RT_NULL);

    device->type        = RT_Device_Class_Char; /* fixme: should be timer type*/
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->init        = rt_hs_timer_init;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = rt_hs_timer_control;
    device->user_data   = timer;

    /* register a character device */
    return rt_device_register(device, name, flag);
}

/***************************************************************************//**
 * @brief
 *  Timer counter overflow interrupt handler
 *
 * @details
 *
 * @note
 ******************************************************************************/
void rt_hw_timer_isr(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    struct efm32_timer_device_t *timer;

    timer = (struct efm32_timer_device_t *)(dev->user_data);

    if (timer->hook.cbFunc != RT_NULL)
    {
        (timer->hook.cbFunc)(timer->hook.userPtr);
    }
}

/***************************************************************************//**
 * @brief
 *   Initialize the specified TIMER unit
 *
 * @details
 *
 * @note
 *
 * @param[in] device
 *   Pointer to device descriptor
 *
 * @param[in] unitNumber
 *   Unit number
 *
 * @return
 *   Pointer to TIMER device
 ******************************************************************************/
static struct efm32_timer_device_t *rt_hw_timer_unit_init(
    rt_device_t device,
    rt_uint8_t  unitNumber,
    rt_uint8_t  mode)
{
    struct efm32_timer_device_t     *timer;
    TIMER_Init_TypeDef              init;
    efm32_irq_hook_init_t           hook;
    CMU_Clock_TypeDef               timerClock;
    IRQn_Type                       timerIrq;

    do
    {
        /* Allocate device */
        timer = rt_malloc(sizeof(struct efm32_timer_device_t));
        if (timer == RT_NULL)
        {
            timer_debug("no memory for TIMER%d driver\n", unitNumber);
            break;
        }

        /* Initialization */
        if (unitNumber >= TIMER_COUNT)
        {
            break;
        }
        switch (unitNumber)
        {
        case 0:
            timer->timer_device = TIMER0;
            timerClock          = (CMU_Clock_TypeDef)cmuClock_TIMER0;
            timerIrq            = TIMER0_IRQn;
            break;

        case 1:
            timer->timer_device = TIMER1;
            timerClock          = (CMU_Clock_TypeDef)cmuClock_TIMER1;
            timerIrq            = TIMER1_IRQn;
            break;

        case 2:
            timer->timer_device = TIMER2;
            timerClock          = (CMU_Clock_TypeDef)cmuClock_TIMER2;
            timerIrq            = TIMER2_IRQn;
            break;

        default:
            break;
        }

        /* Enable TIMER clock */
        CMU_ClockEnable(timerClock, true);

        /* Reset */
        TIMER_Reset(timer->timer_device);

        /* Init specified TIMER unit */
        init.enable         = false;
        init.debugRun       = true;
        init.prescale       = TMR_CFG_PRESCALER;
        init.clkSel         = timerClkSelHFPerClk;
        init.fallAction     = timerInputActionNone;
        init.riseAction     = timerInputActionNone;
        init.mode           = timerModeUp;
        init.dmaClrAct      = false;
        init.quadModeX4     = false;
        init.oneShot        = (mode > 0) ? true : false;
        init.sync           = false;
        TIMER_Init(timer->timer_device, &init);

        /* Config interrupt and NVIC */
        hook.type           = efm32_irq_type_timer;
        hook.unit           = unitNumber;
        hook.cbFunc         = rt_hw_timer_isr;
        hook.userPtr        = device;
        efm32_irq_hook_register(&hook);

        /* Enable overflow interrupt */
        TIMER_IntEnable(timer->timer_device, TIMER_IF_OF);
        TIMER_IntClear(timer->timer_device, TIMER_IF_OF);

        /* Enable TIMERn interrupt vector in NVIC */
        NVIC_ClearPendingIRQ(timerIrq);
        NVIC_SetPriority(timerIrq, EFM32_IRQ_PRI_DEFAULT);
        NVIC_EnableIRQ(timerIrq);

        return timer;
    } while(0);

    if (timer)
    {
        rt_free(timer);
    }
    rt_kprintf("TIMER: Init failed!\n");
    return RT_NULL;
}

/***************************************************************************//**
 * @brief
 *   Initialize all Timer module related hardware and register Timer device to
 *   kernel
 *
 * @details
 *
 * @note
 ******************************************************************************/
void rt_hw_timer_init(void)
{
    struct efm32_timer_device_t *timer;

#ifdef RT_USING_TIMER0
    if ((timer = rt_hw_timer_unit_init(&timer0_device, 0, RT_USING_TIMER0)) \
        != RT_NULL)
    {
        rt_hw_timer_register(&timer0_device, RT_TIMER0_NAME, 0, timer);
    }
#endif


#ifdef RT_USING_TIMER1
    if ((timer = rt_hw_timer_unit_init(&timer1_device, 1, RT_USING_TIMER1)) \
        != RT_NULL)
    {
        rt_hw_timer_register(&timer1_device, RT_TIMER1_NAME, 0, timer);
    }
#endif

#ifdef RT_USING_TIMER2
    if ((timer = rt_hw_timer_unit_init(&timer2_device, 2, RT_USING_TIMER2)) \
        != RT_NULL)
    {
        rt_hw_timer_register(&timer2_device, RT_TIMER2_NAME, 0, timer);
    }
#endif
}

#endif
/***************************************************************************//**
 * @}
 ******************************************************************************/
