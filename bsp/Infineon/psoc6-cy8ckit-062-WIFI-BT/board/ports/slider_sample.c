/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-28     Rbb666       first version
 */

#include <rtthread.h>
#include "drv_common.h"

#ifdef BSP_USING_SLIDER
#include "cycfg_capsense.h"

#define CAPSENSE_INTR_PRIORITY      (7u)
#define EZI2C_INTR_PRIORITY         (6u)

/* Allowed duty cycle for maximum brightness */
#define LED_MAX_BRIGHTNESS      (100u)

/* Allowed duty cycle for minimum brightness*/
#define LED_MIN_BRIGHTNESS      (0u)

#define GET_DUTY_CYCLE(x)       (1 * 1000 * 1000 - x * 10 * 1000)

typedef enum
{
    LED_OFF,
    LED_ON
} led_state_t;

typedef struct
{
    led_state_t state;
    uint32_t brightness;
} led_data_t;

static rt_sem_t trans_done_semphr = RT_NULL;

#ifndef RT_USING_PWM
    #error You need enable PWM to use this sample
#else
    #define PWM_DEV_NAME "pwm0"
    #define PWM_DEV_CHANNEL 3
    static struct rt_device_pwm *pwm_dev;
#endif

static void capsense_isr(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    Cy_CapSense_InterruptHandler(CYBSP_CSD_HW, &cy_capsense_context);

    /* leave interrupt */
    rt_interrupt_leave();
}

void capsense_callback(cy_stc_active_scan_sns_t *ptrActiveScan)
{
    rt_sem_release(trans_done_semphr);
}

static uint32_t initialize_capsense(void)
{
    uint32_t status = CYRET_SUCCESS;

    /* CapSense interrupt configuration parameters */
    static const cy_stc_sysint_t capSense_intr_config =
    {
        .intrSrc = csd_interrupt_IRQn,
        .intrPriority = CAPSENSE_INTR_PRIORITY,
    };

    /* Capture the CSD HW block and initialize it to the default state. */
    status = Cy_CapSense_Init(&cy_capsense_context);
    if (CYRET_SUCCESS != status)
    {
        return status;
    }

    /* Initialize CapSense interrupt */
    cyhal_system_set_isr(csd_interrupt_IRQn, csd_interrupt_IRQn, CAPSENSE_INTR_PRIORITY, &capsense_isr);
    NVIC_ClearPendingIRQ(capSense_intr_config.intrSrc);
    NVIC_EnableIRQ(capSense_intr_config.intrSrc);

    /* Initialize the CapSense firmware modules. */
    status = Cy_CapSense_Enable(&cy_capsense_context);
    if (CYRET_SUCCESS != status)
    {
        return status;
    }

    /* Assign a callback function to indicate end of CapSense scan. */
    status = Cy_CapSense_RegisterCallback(CY_CAPSENSE_END_OF_SCAN_E,
                                          capsense_callback, &cy_capsense_context);
    if (CYRET_SUCCESS != status)
    {
        return status;
    }

    return status;
}

void Slider_Init(void)
{
    cy_rslt_t result;

    result = initialize_capsense();

    if (CYRET_SUCCESS != result)
    {
        /* Halt the CPU if CapSense initialization failed */
        RT_ASSERT(0);
    }

    /* Initiate first scan */
    Cy_CapSense_ScanAllWidgets(&cy_capsense_context);

    trans_done_semphr = rt_sem_create("slider_sem", 1, RT_IPC_FLAG_PRIO);
    if (trans_done_semphr == RT_NULL)
    {
        rt_kprintf("create transform done semphr failed.\n");
        RT_ASSERT(0);
        return;
    }

#ifdef BSP_USING_PWM0_PORT13
    /* Initiate PWM*/
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);

    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("PWM init failed! can't find %s device!\n", PWM_DEV_NAME);
        RT_ASSERT(0);
    }

    /*default   period:1ms    pulse:0*/
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, 1 * 1000 * 1000, 1 * 1000 * 1000);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
#endif
}

void update_led_state(led_data_t *ledData)
{
    if (ledData->brightness >= 0)
    {
        uint32_t brightness = (ledData->brightness < LED_MIN_BRIGHTNESS) ? LED_MIN_BRIGHTNESS : ledData->brightness;

        /* Drive the LED with brightness */
        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, 1 * 1000 * 1000, GET_DUTY_CYCLE(brightness));
    }
}

static void process_touch(void)
{
    cy_stc_capsense_touch_t *slider_touch_info;
    uint16_t slider_pos;
    uint8_t slider_touch_status;
    bool led_update_req = false;

    static uint16_t slider_pos_prev;
    static led_data_t led_data = {LED_ON, LED_MAX_BRIGHTNESS};

    /* Get slider status */
    slider_touch_info = Cy_CapSense_GetTouchInfo(
                            CY_CAPSENSE_LINEARSLIDER0_WDGT_ID, &cy_capsense_context);
    slider_touch_status = slider_touch_info->numPosition;
    slider_pos = slider_touch_info->ptrPosition->x;

    /* Detect the new touch on slider */
    if ((RT_NULL != slider_touch_status) &&
            (slider_pos != slider_pos_prev))
    {
        led_data.brightness = (slider_pos * 100)
                              / cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LINEARSLIDER0_WDGT_ID].xResolution;

        led_update_req = true;
    }

#ifndef RT_USING_PWM
#error You need enable PWM to use this sample
#else
    /* Update the LED state if requested */
    if (led_update_req)
    {
        update_led_state(&led_data);
    }
#endif
    slider_pos_prev = slider_pos;
}

static void Slider_thread_entry(void *parameter)
{
    Slider_Init();

    for (;;)
    {
        rt_sem_take(trans_done_semphr, RT_WAITING_FOREVER);

        /* Process all widgets */
        Cy_CapSense_ProcessAllWidgets(&cy_capsense_context);

        /* Process touch input */
        process_touch();

        /* Establishes synchronized operation between the CapSense
         * middleware and the CapSense Tuner tool.
         */
        Cy_CapSense_RunTuner(&cy_capsense_context);

        /* Initiate next scan */
        Cy_CapSense_ScanAllWidgets(&cy_capsense_context);

        rt_thread_mdelay(50);
    }
}

int Slider_ctrl_sample(void)
{
    rt_err_t ret = RT_EOK;

    rt_thread_t thread = rt_thread_create("slider_th",
                                          Slider_thread_entry,
                                          RT_NULL,
                                          1024,
                                          25,
                                          10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = -RT_ERROR;
    }

    return ret;
}
MSH_CMD_EXPORT(Slider_ctrl_sample, Slider sample to ctrl led);
#endif
