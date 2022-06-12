/*
 * drv_pwm.c
 *
 *  Created on: 2022610
 *      Author: Felix
 */
#include "rtdevice.h"
#include "board.h"
#include "F2837xD_device.h"
#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "drv_config.h"

#include "F2837xD_epwm.h"
//for now, cpu rate is a fixed value, waiting to be modified to an auto-ajustable variable.
#define CPU_FREQUENCY 200e6
#define PWM_DIVISION 2

#define UPDOWN 1
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

#define PHASE_SCALE 10
struct phase_configuration
{
    // phase is from 0~360, scaled up to 10x, for resolution of 0.1 degree
    rt_uint16_t phase;
    rt_bool_t phase_enable;
    rt_bool_t master_flag;
};

struct action_configuration{
    // rt_uint8_t aqa_cau;
    // rt_uint8_t aqa_cad;
    // rt_uint8_t aqa_cbu;
    // rt_uint8_t aqa_cbd;
    // rt_uint8_t aqa_zro;
    // rt_uint8_t aqa_prd;

    // rt_uint8_t aqb_cau;
    // rt_uint8_t aqb_cad;
    // rt_uint8_t aqb_cbu;
    // rt_uint8_t aqb_cbd;
    // rt_uint8_t aqb_zro;
    // rt_uint8_t aqb_prd;
};

//    TODO
//    All of customed configuration need to be filled up
struct rt_pwm_configuration_ex
{
    struct rt_pwm_configuration rt_cfg;
    struct phase_configuration phase_cfg;
    struct action_configuration action_cfg;
};

static rt_err_t c28x_control(struct rt_device_pwm *pwm, int cmd,void *arg);

static const struct rt_pwm_ops rt_pwm_ops = 
{
   .control = c28x_control
};

static rt_err_t drv_pwm_set(struct EPWM_REGS *epwm,struct rt_pwm_configuration *configuration)
{
    // Set the configuration of PWM according to the parameter
    rt_uint32_t prd = configuration->period/(1e9/(CPU_FREQUENCY/PWM_DIVISION));
    if(UPDOWN)
    {
        // if in updown mode, prd has to be halved
        epwm->TBPRD = prd/2;       // Set timer period
    }else
    {
        epwm->TBPRD = prd;       // Set timer period
    }
    epwm->TBCTR = 0x0000;                  // Clear counter
    return RT_EOK;
}

static rt_err_t drv_pwm_get(struct EPWM_REGS *epwm,struct rt_pwm_configuration *configuration)
{
    // Retrieve the pwm configuration
    rt_uint32_t prd = epwm->TBPRD;
    if(UPDOWN)
    {
        // if in updown mode, period in configuration has to be doubled
        configuration->period = prd*(1e9/(CPU_FREQUENCY/PWM_DIVISION))*2;
    }else
    {
        configuration->period = prd*(1e9/(CPU_FREQUENCY/PWM_DIVISION));
    }
    return RT_EOK;
}

static rt_err_t drv_pwm_enable(struct EPWM_REGS *epwm,struct rt_pwm_configuration *configuration,rt_bool_t enable)
{
    // TODO 
    // Still not sure about how to stop PWM in C2000
    if(epwm == RT_NULL || configuration == RT_NULL)
    {
        return RT_ERROR;
    }
    return RT_EOK;
}

static rt_err_t drv_pwm_set_phase(struct EPWM_REGS *epwm, struct phase_configuration *phase_cfg)
{
    if(epwm == RT_NULL || phase_cfg == RT_NULL)
    {
        return RT_ERROR;
    }
    // remapping angle into 0~360
    rt_uint16_t phase = phase_cfg->phase%(360*PHASE_SCALE);
    switch (epwm->TBCTL.bit.CTRMODE)
    {
    // TODO 
    // Still not sure of this configuration
    case TB_COUNT_UPDOWN:
        if(phase<180*PHASE_SCALE)
        {
            epwm->TBPHS.bit.TBPHS = epwm->TBPRD * phase / PHASE_SCALE;
            epwm->TBCTL.bit.PHSDIR = 0;// count up
        }
        else
        {
            epwm->TBPHS.bit.TBPHS = epwm->TBPRD - epwm->TBPRD * (phase-180) / PHASE_SCALE;
            epwm->TBCTL.bit.PHSDIR = 1;// count down
        }
        break;
    case TB_COUNT_UP:
        epwm->TBPHS.bit.TBPHS = epwm->TBPRD * phase / PHASE_SCALE;
        epwm->TBCTL.bit.PHSDIR = 0;// count up
        break;
    case TB_COUNT_DOWN:
        epwm->TBPHS.bit.TBPHS = epwm->TBPRD - epwm->TBPRD * phase / PHASE_SCALE;
        epwm->TBCTL.bit.PHSDIR = 1;// count up
        break;
    default:
        break;
    }
    
    epwm->TBCTL.bit.PHSEN  = phase_cfg->phase_enable ? TB_ENABLE : TB_DISABLE;

    epwm->TBCTL.bit.SYNCOSEL = phase_cfg->master_flag ? TB_CTR_ZERO : TB_SYNC_IN;
    
    return RT_EOK;
}

static rt_err_t drv_pwm_set_action(struct EPWM_REGS *epwm, struct action_configuration *action_cfg)
{
    if(epwm == RT_NULL || action_cfg == RT_NULL)
    {
        return RT_ERROR;
    }
    
    return RT_EOK;
}


static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    struct c28x_pwm *pwm = (struct c28x_pwm *)device->parent.user_data;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(pwm, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(pwm, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(pwm, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(pwm, configuration);
    default:
        return RT_EINVAL;
    }
}

static rt_err_t c28x_control_ex(struct rt_device_pwm *rt_pwm, int cmd,void *arg){
    struct c28x_pwm *pwm = (struct c28x_pwm *)rt_pwm->parent.user_data;
    struct rt_pwm_configuration_ex * pwm_cfg = (struct rt_pwm_configuration_ex *) arg;
    switch(cmd)
    {
    default:break;
    }
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