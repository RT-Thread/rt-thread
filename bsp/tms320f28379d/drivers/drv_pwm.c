/*
 * drv_pwm.c
 *
 *  Created on: 2022Äê6ÔÂ10ÈÕ
 *      Author: Felix
 */
#include "rtdevice.h"
#include "board.h"
#include "F2837xD_device.h"
#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "drv_config.h"
enum
{
#ifdef BSP_USING_PWM1
    PWM1_INDEX,
#endif
#ifdef BSP_USING_PWM2
    PWM2_INDEX,
#endif
#ifdef BSP_USING_PWM3
    PWM3_INDEX,
#endif
#ifdef BSP_USING_PWM4
    PWM4_INDEX,
#endif
#ifdef BSP_USING_PWM5
    PWM5_INDEX,
#endif
#ifdef BSP_USING_PWM6
    PWM6_INDEX,
#endif
#ifdef BSP_USING_PWM7
    PWM7_INDEX,
#endif
#ifdef BSP_USING_PWM8
    PWM8_INDEX,
#endif
#ifdef BSP_USING_PWM9
    PWM9_INDEX,
#endif
#ifdef BSP_USING_PWM10
    PWM10_INDEX,
#endif
#ifdef BSP_USING_PWM11
    PWM11_INDEX,
#endif
#ifdef BSP_USING_PWM12
    PWM12_INDEX,
#endif
};
struct c28x_pwm
{
    const char *name;
    volatile struct EPWM_REGS *pwm_regs;
    struct rt_device_pwm rt_pwm;
};


static struct c28x_pwm c28x_pwm_obj[3] ={0};

struct rt_pwm_configuration_ex
{
//    TODO
//    All of customed configuration need to be filled up
};

static rt_err_t c28x_control(struct rt_device_pwm *pwm, int cmd,void *arg);

static const struct rt_pwm_ops rt_pwm_ops = {
   .control = c28x_control
};

static rt_err_t c28x_control(struct rt_device_pwm *rt_pwm, int cmd,void *arg){
    struct c28x_pwm *pwm = (struct c28x_pwm *)rt_pwm->parent.user_data;
    struct rt_pwm_configuration_ex * pwm_cfg = (struct rt_pwm_configuration_ex *) arg;
    EALLOW;
    switch(cmd)
    {
    default:break;
    }
    EDIS;
    return RT_EOK;
}

static void pwm_isr(struct rt_device_pwm *rt_pwm)
{
    struct c28x_pwm *pwm;
    pwm = (struct c28x_pwm *)rt_pwm->parent.user_data;
//    rt_hw_pwm_isr
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    pwm->pwm_regs->ETCLR.bit.INT = 1;
}

#define EPWM_ISR_DEFINE(i) void EPWM##i##_Isr(){\
    rt_interrupt_enter();   \
    pwm_isr(&(c28x_pwm_obj[PWM##i##_INDEX].rt_pwm));  \
    rt_interrupt_leave();   \
}

#ifdef BSP_USING_PWM1
EPWM_ISR_DEFINE(1)
#endif

int c28x_hw_pwm_init(struct c28x_pwm *device)
{
    EALLOW;
//    TODO
//    Configure the GPIO accordingly

//    Assigning ISR to PIE
    PieVectTable.EPWM1_INT = &EPWM1_Isr;
//    ENABLE Interrupt

    EINT;
    EDIS;
    IER |= 0x100;                        // Enable CPU INT
    rt_err_t result = 0;
    device->pwm_regs = &EPwm1Regs;
    device->name = "pwm1";
    device->rt_pwm.ops = &rt_pwm_ops;

    return result;
}
static int c28x_pwm_init(void)
{
    int i = 0;
    int result = RT_EOK;

    pwm_get_channel();

    for (i = 0; i < sizeof(c28x_pwm_obj) / sizeof(c28x_pwm_obj[0]); i++)
    {
        /* pwm init */
        if (c28x_hw_pwm_init(&c28x_pwm_obj[i]) != RT_EOK)
        {
            LOG_E("%s init failed", c28x_pwm_obj[i].name);
            result = -RT_ERROR;
            goto __exit;
        }
        else
        {
            LOG_D("%s init success", c28x_pwm_obj[i].name);

            /* register pwm device */
            if (rt_device_pwm_register(rt_calloc(1, sizeof(struct rt_device_pwm)), c28x_pwm_obj[i].name, &drv_ops, &c28x_pwm_obj[i].tim_handle) == RT_EOK)
            {

                LOG_D("%s register success", c28x_pwm_obj[i].name);
            }
            else
            {
                LOG_E("%s register failed", c28x_pwm_obj[i].name);
                result = -RT_ERROR;
            }
        }
    }

__exit:
    return result;
}
INIT_DEVICE_EXPORT(c28x_pwm_init);