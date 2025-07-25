/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-18     hywing       Initial version.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "fsl_pwm.h"

#ifdef RT_USING_PWM

#define BOARD_PWM_BASEADDR      (FLEXPWM0)
#define PWM_SRC_CLK_FREQ        (CLOCK_GetFreq(kCLOCK_BusClk))
#define FLEX_PWM_CLOCK_DEVIDER  (kPWM_Prescale_Divide_2)
#define FLEX_PWM_FAULT_LEVEL    true

typedef struct
{
    struct rt_device_pwm pwm_device;
    pwm_submodule_t submodule;
    pwm_module_control_t control;
    pwm_channels_t channel;
    pwm_clock_prescale_t prescale;
    char *name;
} mcx_pwm_obj_t;

static mcx_pwm_obj_t mcx_pwm_list[]=
{
#ifdef BSP_USING_PWM0
    {
        .submodule = kPWM_Module_0,
        .control = kPWM_Control_Module_0,
        .channel = kPWM_PwmA,
        .prescale = FLEX_PWM_CLOCK_DEVIDER,
        .name = "pwm0",
    },
#endif
#ifdef BSP_USING_PWM1
    {
        .submodule = kPWM_Module_1,
        .control = kPWM_Control_Module_1,
        .channel = kPWM_PwmA,
        .prescale = FLEX_PWM_CLOCK_DEVIDER,
        .name = "pwm1",
    },
#endif
#ifdef BSP_USING_PWM2
    {
        .submodule = kPWM_Module_2,
        .control = kPWM_Control_Module_2,
        .channel = kPWM_PwmA,
        .prescale = FLEX_PWM_CLOCK_DEVIDER,
        .name = "pwm2",
    },
#endif
};

static rt_err_t mcx_drv_pwm_get(mcx_pwm_obj_t *pwm, struct rt_pwm_configuration *configuration)
{
    return RT_EOK;
}

static rt_err_t mcx_drv_pwm_set(mcx_pwm_obj_t *pwm, struct rt_pwm_configuration *configuration)
{
    uint8_t dutyCyclePercent = configuration->pulse * 100 / configuration->period;
    pwm_signal_param_t pwmSignal[1];
    uint32_t pwmFrequencyInHz = 1000000000 / configuration->period;

    pwmSignal[0].pwmChannel       = pwm->channel;
    pwmSignal[0].level            = kPWM_HighTrue;
    pwmSignal[0].dutyCyclePercent = dutyCyclePercent;
    pwmSignal[0].deadtimeValue    = 0;
    pwmSignal[0].faultState       = kPWM_PwmFaultState0;
    pwmSignal[0].pwmchannelenable = true;

    PWM_SetupPwm(BOARD_PWM_BASEADDR, pwm->submodule, pwmSignal, 1, kPWM_SignedCenterAligned, pwmFrequencyInHz, PWM_SRC_CLK_FREQ);
    PWM_UpdatePwmDutycycle(BOARD_PWM_BASEADDR, pwm->submodule, pwm->channel, kPWM_SignedCenterAligned, dutyCyclePercent);
    PWM_SetPwmLdok(BOARD_PWM_BASEADDR, pwm->control, true);

    return 0;
}

static rt_err_t mcx_drv_pwm_enable(mcx_pwm_obj_t *pwm, struct rt_pwm_configuration *configuration)
{
    PWM_StartTimer(BOARD_PWM_BASEADDR, pwm->control);
    return 0;
}

static rt_err_t mcx_drv_pwm_disable(mcx_pwm_obj_t *pwm, struct rt_pwm_configuration *configuration)
{
    PWM_StopTimer(BOARD_PWM_BASEADDR, pwm->control);
    return 0;
}

static rt_err_t mcx_drv_pwm_control(struct rt_device_pwm *device, int cmd, void *args)
{
    mcx_pwm_obj_t *pwm = device->parent.user_data;
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)args;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return mcx_drv_pwm_enable(pwm, configuration);

    case PWM_CMD_DISABLE:
        return mcx_drv_pwm_disable(pwm, configuration);

    case PWM_CMD_SET:
        return mcx_drv_pwm_set(pwm, configuration);

    case PWM_CMD_GET:
        return mcx_drv_pwm_get(pwm, configuration);

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_pwm_ops mcx_pwm_ops =
{
    .control = mcx_drv_pwm_control,
};

int mcx_pwm_init(void)
{
    rt_err_t ret;
    pwm_config_t pwmConfig;
    pwm_fault_param_t faultConfig;
    PWM_GetDefaultConfig(&pwmConfig);
    pwmConfig.prescale = FLEX_PWM_CLOCK_DEVIDER;
    pwmConfig.reloadLogic = kPWM_ReloadPwmFullCycle;

    int i;
    for (i = 0; i < sizeof(mcx_pwm_list) / sizeof(mcx_pwm_list[0]); i++)
    {
        pwm_config_t pwmConfig;
        pwm_fault_param_t faultConfig;
        PWM_GetDefaultConfig(&pwmConfig);
        pwmConfig.prescale = mcx_pwm_list[i].prescale;
        pwmConfig.reloadLogic = kPWM_ReloadPwmFullCycle;
        if (PWM_Init(BOARD_PWM_BASEADDR, mcx_pwm_list[i].submodule, &pwmConfig) == kStatus_Fail)
        {
            rt_kprintf("PWM Init Failed\n");
        }
        ret = rt_device_pwm_register(&mcx_pwm_list[i].pwm_device, mcx_pwm_list[i].name, &mcx_pwm_ops, &mcx_pwm_list[i]);
    }

    /*
     *   config->faultClearingMode = kPWM_Automatic;
     *   config->faultLevel = false;
     *   config->enableCombinationalPath = true;
     *   config->recoverMode = kPWM_NoRecovery;
     */
    PWM_FaultDefaultConfig(&faultConfig);
    faultConfig.faultLevel = FLEX_PWM_FAULT_LEVEL;

    /* Sets up the PWM fault protection */
    PWM_SetupFaults(BOARD_PWM_BASEADDR, kPWM_Fault_0, &faultConfig);
    PWM_SetupFaults(BOARD_PWM_BASEADDR, kPWM_Fault_1, &faultConfig);
    PWM_SetupFaults(BOARD_PWM_BASEADDR, kPWM_Fault_2, &faultConfig);
    PWM_SetupFaults(BOARD_PWM_BASEADDR, kPWM_Fault_3, &faultConfig);

    /* Set PWM fault disable mapping for submodule 0/1/2 */
    PWM_SetupFaultDisableMap(BOARD_PWM_BASEADDR, kPWM_Module_0, kPWM_PwmA, kPWM_faultchannel_0,
                             kPWM_FaultDisable_0 | kPWM_FaultDisable_1 | kPWM_FaultDisable_2 | kPWM_FaultDisable_3);
    PWM_SetupFaultDisableMap(BOARD_PWM_BASEADDR, kPWM_Module_1, kPWM_PwmA, kPWM_faultchannel_0,
                             kPWM_FaultDisable_0 | kPWM_FaultDisable_1 | kPWM_FaultDisable_2 | kPWM_FaultDisable_3);
    PWM_SetupFaultDisableMap(BOARD_PWM_BASEADDR, kPWM_Module_2, kPWM_PwmA, kPWM_faultchannel_0,
                             kPWM_FaultDisable_0 | kPWM_FaultDisable_1 | kPWM_FaultDisable_2 | kPWM_FaultDisable_3);


    /* Set the load okay bit for all submodules to load registers from their buffer */
    PWM_SetPwmLdok(BOARD_PWM_BASEADDR, kPWM_Control_Module_0 | kPWM_Control_Module_1 | kPWM_Control_Module_2, true);

    return ret;
}

INIT_DEVICE_EXPORT(mcx_pwm_init);

#endif /* RT_USING_PWM */
