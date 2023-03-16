/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-24     qiyu      first version
 */

#include "rtdbg.h"
#include "drv_pwm.h"
#include "F2837xD_device.h"
#include "F28x_Project.h"     /* Device Headerfile and Examples Include File */
#include "drv_config.h"
#include "F2837xD_epwm.h"
/*
 * for now, cpu rate is a fixed value, waiting to be modified to an auto-ajustable variable.
*/
#ifdef BSP_USING_PWM
rt_err_t rt_device_pwm_register(struct rt_device_pwm *device, const char *name, const struct rt_pwm_ops *ops, const void *user_data);

#define CPU_FREQUENCY 200e6
/*
 * TODO unknown issue, according to the configuration,
 * this division should be 2,
 * while 2 is inconsistent with the measured result
 */
#define PWM_DIVISION 2
#define CHANNEL_A       1
#define CHANNEL_B       2
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

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);

static struct rt_pwm_ops rt_pwm_ops =
{
    drv_pwm_control
};

static struct c28x_pwm c28x_pwm_obj[] =
{
#ifdef BSP_USING_PWM1
    PWM1_CONFIG,
#endif

#ifdef BSP_USING_PWM2
    PWM2_CONFIG,
#endif

#ifdef BSP_USING_PWM3
    PWM3_CONFIG,
#endif

#ifdef BSP_USING_PWM4
    PWM4_CONFIG,
#endif

#ifdef BSP_USING_PWM5
    PWM5_CONFIG,
#endif

#ifdef BSP_USING_PWM6
    PWM6_CONFIG,
#endif

#ifdef BSP_USING_PWM7
    PWM7_CONFIG,
#endif

#ifdef BSP_USING_PWM8
    PWM8_CONFIG,
#endif

};

static rt_err_t drv_pwm_set(volatile struct EPWM_REGS *epwm,struct rt_pwm_configuration *configuration)
{
    if(epwm == RT_NULL)
    {
        return -RT_ERROR;
    }
    /*
     * TODO Unknown problem
     * the clock division configuration of PWM module is 1
     * however, the experiment result shows the division is 2
     */

    /* Set the configuration of PWM according to the parameter*/
    rt_uint32_t prd = configuration->period/(1e9/(CPU_FREQUENCY/PWM_DIVISION))/2;
    rt_uint32_t comp = prd*configuration->pulse/configuration->period;
    rt_uint32_t dead_time = configuration->dead_time/(1e9/(CPU_FREQUENCY/PWM_DIVISION));
    rt_uint32_t phase = configuration->phase;

    epwm->TBPRD = prd;                       /* Set timer period*/
    epwm->TBCTR = 0x0000;                     /* Clear counter*/
    epwm->CMPCTL.bit.SHDWAMODE = RT_SHADOW_MODE;    /* Load registers every ZERO*/
    epwm->CMPCTL.bit.SHDWBMODE = RT_SHADOW_MODE;
    /* Setup compare */
    if(configuration->channel == CHANNEL_A)
    {
        epwm->CMPA.bit.CMPA = comp;
    }else
    {
        epwm->CMPB.bit.CMPB = comp;
    }

    /* Set actions */
    epwm->AQCTLA.bit.CAU = AQ_CLEAR;            /* Set PWMA on Zero*/
    epwm->AQCTLA.bit.CAD = AQ_SET;
    epwm->AQCTLB.bit.CBU = AQ_CLEAR;            /* Set PWMB on Zero*/
    epwm->AQCTLB.bit.CBD = AQ_SET;

    /* Active Low PWMs - Setup Deadband */
    /* TODO finish complementary setting */
    epwm->DBCTL.bit.POLSEL = DB_ACTV_HIC;
    epwm->DBRED.bit.DBRED = dead_time;
    epwm->DBFED.bit.DBFED = dead_time;
    epwm->DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    /*
    if(configuration->complementary)
    {
    }
    else
    {
        epwm->DBRED.bit.DBRED = 0;
        epwm->DBFED.bit.DBFED = 0;
        epwm->DBCTL.bit.POLSEL = DB_ACTV_HI;
        epwm->DBCTL.bit.OUT_MODE = DB_DISABLE;
    }
    */

    epwm->DBCTL.bit.IN_MODE = DBA_ALL;
    /* if disable dead time, set dead_time to 0 */

#ifdef BSP_PWM1_CTR_MODE_UPDOWN
    if(phase<180)
    {
        epwm->TBPHS.bit.TBPHS = prd * phase/180;
        epwm->TBCTL.bit.PHSDIR = 0; /* count up */
    }else
    {
        epwm->TBPHS.bit.TBPHS = prd-prd * (phase-180)/180;
        epwm->TBCTL.bit.PHSDIR = 1; /* count up*/
    }
#endif
    if(epwm == &EPwm1Regs)
    {
        epwm->TBCTL.bit.PHSEN = TB_DISABLE;        /* Disable phase loading */
        epwm->TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    }else
    {
        epwm->TBCTL.bit.PHSEN = TB_ENABLE;        /* Disable phase loading */
        epwm->TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    }
    return RT_EOK;
}

static rt_err_t drv_pwm_get(struct EPWM_REGS *epwm,struct rt_pwm_configuration *configuration)
{
    /* Retrieve the pwm configuration */
    if(epwm == RT_NULL)
    {
        return -RT_ERROR;
    }
    rt_uint32_t prd = epwm->TBPRD;
    rt_uint32_t comp = epwm->CMPA.bit.CMPA;
    if(UPDOWN)
    {
        /* if in updown mode, period in configuration has to be doubled */
        configuration->period = prd*(1e9/(CPU_FREQUENCY/PWM_DIVISION))*2;
    }
    else
    {
        configuration->period = prd*(1e9/(CPU_FREQUENCY/PWM_DIVISION));
    }
    configuration->pulse = comp*configuration->period/prd;
    return RT_EOK;
}

static rt_err_t drv_pwm_set_period(struct EPWM_REGS *epwm, rt_uint32_t period)
{
    if(epwm == RT_NULL)
    {
        return -RT_ERROR;
    }
    rt_uint32_t prd = period/(1e9/(CPU_FREQUENCY/PWM_DIVISION))/2;
    epwm->TBPRD = prd;                       /* Set timer period */
    return RT_EOK;
}

static rt_err_t drv_pwm_set_pulse(struct EPWM_REGS *epwm, int channel, rt_uint32_t pulse)
{
    if(epwm == RT_NULL)
    {
        return -RT_ERROR;
    }
    rt_uint32_t comp = pulse/(1e9/(CPU_FREQUENCY/PWM_DIVISION));
    if(channel == CHANNEL_A)
    {
        epwm->CMPA.bit.CMPA = comp;    /* set comparator value */
    }else
    {
        epwm->CMPB.bit.CMPB = comp;    /* set comparator value */
    }
    return RT_EOK;
}

static rt_err_t drv_pwm_set_dead_time(struct EPWM_REGS *epwm, rt_uint32_t dead_time)
{
    if(epwm == RT_NULL)
    {
        return -RT_ERROR;
    }
    rt_uint32_t _dead_time = dead_time/(1e9/(CPU_FREQUENCY/PWM_DIVISION));
    epwm->DBRED.bit.DBRED = _dead_time;  /* rising dead time */
    epwm->DBFED.bit.DBFED = _dead_time;  /* falling dead time */
    return RT_EOK;
}

static rt_err_t drv_pwm_set_phase(struct EPWM_REGS *epwm, rt_uint32_t phase)
{
    if(epwm == RT_NULL)
    {
        return -RT_ERROR;
    }
    if(phase<180)
    {
        epwm->TBPHS.bit.TBPHS = epwm->TBPRD * phase/180;
        epwm->TBCTL.bit.PHSDIR = 0;/* count up */
    }else
    {
        epwm->TBPHS.bit.TBPHS = epwm->TBPRD-epwm->TBPRD * (phase-180)/180;
        epwm->TBCTL.bit.PHSDIR = 1;/* count up */
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_enable_irq(volatile struct EPWM_REGS *epwm,rt_bool_t enable)
{
    if(epwm == RT_NULL)
    {
        return -RT_ERROR;
    }
    if(enable == RT_TRUE)
    {
        /* Interrupt setting */
        epwm->ETSEL.bit.INTEN = 1;               /* Enable INT */
    }else{
        epwm->ETSEL.bit.INTEN = 0;               /* Enable INT */
    }
    return RT_EOK;
}

static rt_err_t drv_pwm_enable(volatile struct EPWM_REGS *epwm,rt_bool_t enable)
{
    /*
    * TODO
    * Still not sure about how to stop PWM in C2000
    */
    if(epwm == RT_NULL)
    {
        return -RT_ERROR;
    }
    if(enable == RT_TRUE)
    {
        /* clear trip zone flag */
        EALLOW;
        epwm->TZCLR.bit.OST = 1;
        EDIS;
    }
    else
    {
        /* set trip zone flag */
        EALLOW;
        epwm->TZFRC.bit.OST = 1;
        EDIS;
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
        return drv_pwm_enable((struct EPWM_REGS *)(pwm->pwm_regs), RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable((struct EPWM_REGS *)(pwm->pwm_regs), RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set((struct EPWM_REGS *)(pwm->pwm_regs), configuration);
    case PWM_CMD_GET:
        return drv_pwm_get((struct EPWM_REGS *)(pwm->pwm_regs), configuration);
    case PWM_CMD_SET_PERIOD:
        return drv_pwm_set_period((struct EPWM_REGS *)(pwm->pwm_regs), configuration->period);
    case PWM_CMD_SET_PULSE:
        return drv_pwm_set_pulse((struct EPWM_REGS *)(pwm->pwm_regs), configuration->channel,configuration->pulse);
    case PWM_CMD_SET_DEAD_TIME:
        return drv_pwm_set_dead_time((struct EPWM_REGS *)(pwm->pwm_regs), configuration->dead_time);
    case PWM_CMD_SET_PHASE:
        return drv_pwm_set_phase((struct EPWM_REGS *)(pwm->pwm_regs), configuration->phase);
    case PWM_CMD_ENABLE_IRQ:
        return drv_pwm_enable_irq((struct EPWM_REGS *)(pwm->pwm_regs), RT_TRUE);
    case PWM_CMD_DISABLE_IRQ:
        return drv_pwm_enable_irq((struct EPWM_REGS *)(pwm->pwm_regs), RT_FALSE);
    default:
        return -RT_EINVAL;
    }
}

static void pwm_isr(struct rt_device_pwm *rt_pwm)
{
    struct c28x_pwm *pwm;
    pwm = (struct c28x_pwm *)rt_pwm->parent.user_data;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    pwm->pwm_regs->ETCLR.bit.INT = 1;
}

#define EPWM_ISR_DEFINE(i) void EPWM##i##_Isr(){\
    rt_interrupt_enter();   \
    pwm_isr(&(c28x_pwm_obj[PWM##i##_INDEX].pwm_device));  \
    rt_interrupt_leave();   \
}

#ifdef BSP_PWM1_IT_ENABLE
EPWM_ISR_DEFINE(1)
void EPWM1_Isr();
#endif
#ifdef BSP_PWM2_IT_ENABLE
EPWM_ISR_DEFINE(2)
void EPWM2_Isr();
#endif
#ifdef BSP_PWM3_IT_ENABLE
EPWM_ISR_DEFINE(3)
void EPWM3_Isr();
#endif
#ifdef BSP_PWM4_IT_ENABLE
EPWM_ISR_DEFINE(4)
void EPWM4_Isr();
#endif


static int c28x_hw_pwm_init(struct c28x_pwm *device)
{
    IER |= M_INT3;
    rt_err_t result = 0;
    EALLOW;
#ifdef BSP_USING_PWM1
    GpioCtrlRegs.GPAPUD.all |= 5<<(1-1)*4;      /* Disable pull-up(EPWM1A) */
    GpioCtrlRegs.GPAMUX1.all|= 5<<(1-1)*4;      /* Configure as EPWM1A */
    EPwm1Regs.TZCTL.bit.TZA = TZ_OFF;           /* diable A when trip zone */
    EPwm1Regs.TZCTL.bit.TZB = TZ_OFF;           /* diable B when trip zone */
    EPwm1Regs.TBCTL.bit.CTRMODE = BSP_PWM1_CTRMODE;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = BSP_PWM1_HSPCLKDIV;       /* Clock ratio to SYSCLKOUT*/
    EPwm1Regs.TBCTL.bit.CLKDIV = BSP_PWM1_CLKDIV;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = BSP_PWM1_LOADAMODE;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = BSP_PWM1_LOADAMODE;
    #ifdef BSP_PWM1_IT_ENABLE
        EPwm1Regs.ETSEL.bit.INTEN = 1;               /* Enable INT */
        EPwm1Regs.ETSEL.bit.INTSEL = BSP_PWM1_INTSEL;
        EPwm1Regs.ETPS.bit.INTPRD = BSP_PWM1_INTPRD;
        /* Assigning ISR to PIE */
        PieVectTable.EPWM1_INT = &EPWM1_Isr;
        /* ENABLE Interrupt */
    #else
        EPwm1Regs.ETSEL.bit.INTEN = 0;               /* Disable INT */
    #endif
    #ifdef BSP_PWM1_ADC_TRIGGER
        EPwm1Regs.ETSEL.bit.SOCAEN    = 1;        // Enable SOC on A group
        EPwm1Regs.ETSEL.bit.SOCASEL  = BSP_PWM1_SOCASEL;        // Select SOC from zero
        EPwm1Regs.ETPS.bit.SOCAPRD   = BSP_PWM1_SOCAPRD;        // Generate pulse on 1st event
    #else
        EPwm1Regs.ETSEL.bit.SOCAEN    = 0;        // Disable SOC on A group
    #endif
    #ifdef BSP_PWM1_MASTER
        EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        /* Disable phase loading */
        EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    #else
        EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;        /* Disable phase loading */
        EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    #endif
#endif
#ifdef BSP_USING_PWM2
    GpioCtrlRegs.GPAPUD.all |= 5<<(2-1)*4;      /* Disable pull-up on  (EPWM2A) */
    GpioCtrlRegs.GPAMUX1.all|= 5<<(2-1)*4;      /* Configure as EPWM2A */
    EPwm2Regs.TZCTL.bit.TZA = TZ_OFF;           /* diable A when trip zone */
    EPwm2Regs.TZCTL.bit.TZB = TZ_OFF;           /* diable B when trip zone */
    EPwm2Regs.TBCTL.bit.CTRMODE = BSP_PWM2_CTRMODE;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = BSP_PWM2_HSPCLKDIV;       /* Clock ratio to SYSCLKOUT*/
    EPwm2Regs.TBCTL.bit.CLKDIV = BSP_PWM2_CLKDIV;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = BSP_PWM2_LOADAMODE;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = BSP_PWM2_LOADAMODE;
    #ifdef BSP_PWM2_IT_ENABLE
        EPwm2Regs.ETSEL.bit.INTEN = 1;               /* Enable INT */
        EPwm2Regs.ETSEL.bit.INTSEL = BSP_PWM2_INTSEL;
        EPwm2Regs.ETPS.bit.INTPRD = BSP_PWM2_INTPRD;
        /* Assigning ISR to PIE */
        PieVectTable.EPWM2_INT = &EPWM2_Isr;
        /* ENABLE Interrupt */
    #else
        EPwm2Regs.ETSEL.bit.INTEN = 0;               /* Disable INT */
    #endif
    #ifdef BSP_PWM2_ADC_TRIGGER
        EPwm2Regs.ETSEL.bit.SOCAEN    = 1;        // Enable SOC on A group
        EPwm2Regs.ETSEL.bit.SOCASEL  = BSP_PWM2_SOCASEL;        // Select SOC from zero
        EPwm2Regs.ETPS.bit.SOCAPRD   = BSP_PWM2_SOCAPRD;        // Generate pulse on 1st event
    #else
        EPwm2Regs.ETSEL.bit.SOCAEN    = 0;        // Disable SOC on A group
    #endif
    #ifdef BSP_PWM2_MASTER
        EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        /* Disable phase loading */
        EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    #else
        EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;        /* Disable phase loading */
        EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    #endif
#endif
#ifdef BSP_USING_PWM3
    GpioCtrlRegs.GPAPUD.all |= 5<<(3-1)*4;      /* Disable pull-up on (EPWM3A) */
    GpioCtrlRegs.GPAMUX1.all|= 5<<(3-1)*4;      /* Configure as EPWM3A */
    EPwm3Regs.TZCTL.bit.TZA = TZ_OFF;           /* diable A when trip zone */
    EPwm3Regs.TZCTL.bit.TZB = TZ_OFF;           /* diable B when trip zone */
    EPwm3Regs.TBCTL.bit.CTRMODE = BSP_PWM3_CTRMODE;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = BSP_PWM3_HSPCLKDIV;       /* Clock ratio to SYSCLKOUT*/
    EPwm3Regs.TBCTL.bit.CLKDIV = BSP_PWM3_CLKDIV;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = BSP_PWM3_LOADAMODE;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = BSP_PWM3_LOADAMODE;
    #ifdef BSP_PWM3_IT_ENABLE
        EPwm3Regs.ETSEL.bit.INTEN = 1;               /* Enable INT */
        EPwm3Regs.ETSEL.bit.INTSEL = BSP_PWM3_INTSEL;
        EPwm3Regs.ETPS.bit.INTPRD = BSP_PWM3_INTPRD;
        /* Assigning ISR to PIE */
        PieVectTable.EPWM3_INT = &EPWM3_Isr;
        /* ENABLE Interrupt */
    #else
        EPwm3Regs.ETSEL.bit.INTEN = 0;               /* Disable INT */
    #endif
    #ifdef BSP_PWM3_ADC_TRIGGER
        EPwm3Regs.ETSEL.bit.SOCAEN    = 1;        // Enable SOC on A group
        EPwm3Regs.ETSEL.bit.SOCASEL  = BSP_PWM3_SOCASEL;        // Select SOC from zero
        EPwm3Regs.ETPS.bit.SOCAPRD   = BSP_PWM3_SOCAPRD;        // Generate pulse on 1st event
    #else
        EPwm3Regs.ETSEL.bit.SOCAEN    = 0;        // Disable SOC on A group
    #endif
    #ifdef BSP_PWM3_MASTER
        EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;        /* Disable phase loading */
        EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    #else
        EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;        /* Disable phase loading */
        EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    #endif
#endif
#ifdef BSP_USING_PWM4
    GpioCtrlRegs.GPAPUD.all |= 5<<(4-1)*4;      /* Disable pull-up on (EPWM4A) */
    GpioCtrlRegs.GPAMUX1.all|= 5<<(4-1)*4;      /* Configure as EPWM4A */
    EPwm4Regs.TZCTL.bit.TZA = TZ_OFF;           /* diable A when trip zone */
    EPwm4Regs.TZCTL.bit.TZB = TZ_OFF;           /* diable B when trip zone */
    EPwm4Regs.TBCTL.bit.CTRMODE = BSP_PWM4_CTRMODE;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = BSP_PWM4_HSPCLKDIV;       /* Clock ratio to SYSCLKOUT*/
    EPwm4Regs.TBCTL.bit.CLKDIV = BSP_PWM4_CLKDIV;
    EPwm4Regs.CMPCTL.bit.LOADAMODE = BSP_PWM4_LOADAMODE;
    EPwm4Regs.CMPCTL.bit.LOADBMODE = BSP_PWM4_LOADAMODE;
    #ifdef BSP_PWM4_IT_ENABLE
        EPwm4Regs.ETSEL.bit.INTEN = 1;               /* Enable INT */
        EPwm4Regs.ETSEL.bit.INTSEL = BSP_PWM4_INTSEL;
        EPwm4Regs.ETPS.bit.INTPRD = BSP_PWM4_INTPRD;
        /* Assigning ISR to PIE */
        PieVectTable.EPWM4_INT = &EPWM4_Isr;
        /* ENABLE Interrupt */
    #else
        EPwm4Regs.ETSEL.bit.INTEN = 0;               /* Disable INT */
    #endif
    #ifdef BSP_PWM4_ADC_TRIGGER
        EPwm4Regs.ETSEL.bit.SOCAEN    = 1;        // Enable SOC on A group
        EPwm4Regs.ETSEL.bit.SOCASEL  = BSP_PWM4_SOCASEL;        // Select SOC from zero
        EPwm4Regs.ETPS.bit.SOCAPRD   = BSP_PWM4_SOCAPRD;        // Generate pulse on 1st event
    #else
        EPwm4Regs.ETSEL.bit.SOCAEN    = 0;        // Disable SOC on A group
    #endif
    #ifdef BSP_PWM4_MASTER
        EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;        /* Disable phase loading */
        EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    #else
        EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;        /* Disable phase loading */
        EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    #endif
#endif
    EDIS;

    return result;
}

int c28x_pwm_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(c28x_pwm_obj) / sizeof(c28x_pwm_obj[0]); i++)
    {
        /* pwm init */
        if (c28x_hw_pwm_init(&c28x_pwm_obj[i]) != RT_EOK)
        {
            LOG_E("%s init failed", c28x_pwm_obj[i].name);
            result = -RT_ERROR;
            return result;
        }
        else
        {
            LOG_D("%s init success", c28x_pwm_obj[i].name);

            /* register pwm device */
            if (rt_device_pwm_register(&c28x_pwm_obj[i].pwm_device, c28x_pwm_obj[i].name, &rt_pwm_ops, &c28x_pwm_obj[i]) == RT_EOK)
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
    struct rt_pwm_configuration config_tmp1 =
    {
       .channel = CHANNEL_A,
       .period = BSP_PWM1_INIT_PERIOD,
       .pulse = BSP_PWM1_INIT_PULSE,
       .dead_time = BSP_PWM1_DB,
       .phase = 0,
       .complementary = RT_TRUE
    };
    drv_pwm_set(c28x_pwm_obj[0].pwm_regs,&config_tmp1);
//    config_tmp1.phase = BSP_PWM2_PHASE;
//    drv_pwm_set(c28x_pwm_obj[1].pwm_regs,&config_tmp1);
//    config_tmp1.phase = BSP_PWM3_PHASE;
//    drv_pwm_set(c28x_pwm_obj[2].pwm_regs,&config_tmp1);
//    config_tmp1.phase = BSP_PWM4_PHASE;
//    drv_pwm_set(c28x_pwm_obj[3].pwm_regs,&config_tmp1);
    return result;

}
INIT_DEVICE_EXPORT(c28x_pwm_init);
#endif /* BSP_USING_PWM */
