/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fpwm.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-04-15 11:45:05
 * Description: This file is for detailed description of the device configuration and driver.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/4/15   init commit
 */

#ifndef FPWM_H
#define FPWM_H

#include "ftypes.h"
#include "fdebug.h"
#include "ferror_code.h"
#include "fkernel.h"
#include "fassert.h"
#include "fparameters.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define FPWM_SUCCESS          FT_SUCCESS
#define FPWM_ERR_INVAL_PARM   FT_MAKE_ERRCODE(ErrModBsp, ErrBspPwm, 1)
#define FPWM_ERR_NOT_READY    FT_MAKE_ERRCODE(ErrModBsp, ErrBspPwm, 2)
#define FPWM_ERR_TIMEOUT      FT_MAKE_ERRCODE(ErrModBsp, ErrBspPwm, 3)
#define FPWM_ERR_NOT_SUPPORT  FT_MAKE_ERRCODE(ErrModBsp, ErrBspPwm, 4)
#define FPWM_ERR_CMD_FAILED   FT_MAKE_ERRCODE(ErrModBsp, ErrBspPwm, 5)

typedef enum
{
    FPWM_INTR_EVENT_COUNTER = 0,    /**< Handler type for counter interrupt */
    FPWM_INTR_EVENT_FIFO_EMPTY = 1, /**< Handler type for fifo empty interrupt*/
    FPWM_INTR_EVENT_NUM
} FPwmIntrEventType;

/* duty sel */
typedef enum
{
    FPWM_DUTY_CCR = 0,  /* duty value from pwm ccr register */
    FPWM_DUTY_FIFO = 1, /* duty value from fifo */
    FPWM_DUTY_SEL_MODE_NUM
} FPwmDutySourceMode;

/* tim_ctrl mode, counter mode */
typedef enum
{
    FPWM_MODULO = 0,    /* count from 0~period  */
    FPWM_UP_DOWN = 1,   /* count from 0~period~0  */
    FPWM_TIM_CTRL_MODE_NUM
} FPwmTimCtrlMode;

/* pwm mode, only the compare output mode is supported currently*/
typedef enum
{
    FPWM_NONE_MODE = 0,/* no mode */
    FPWM_OUTPUT_COMPARE = 1,/* compare output mode */
    FPWM_CTRL_MODE_NUM
} FPwmCtrlMode;

/**
 * enum pwm_polarity - polarity of a PWM compare signal
 * @FPWM_POLARITY_NORMAL: a high signal for the duration of the duty-
 * cycle, followed by a low signal for the remainder of the pulse
 * period
 * @FPWM_POLARITY_INVERSED: a low signal for the duration of the duty-
 * cycle, followed by a high signal for the remainder of the pulse
 * period
 */
typedef enum
{
    FPWM_POLARITY_OUTPUT_HIGH = 0b000,
    FPWM_POLARITY_OUTPUT_LOW = 0b001,
    FPWM_POLARITY_OUTPUT_FLIP = 0b010,
    FPWM_POLARITY_INVERSED = 0b011,
    FPWM_POLARITY_NORMAL = 0b100,
    FPWM_POLARITY_CCR_LOW = 0b101,
    FPWM_POLARITY_CCR_HIGH = 0b110,
    FPWM_POLARITY_INIT = 0b111,
    FPWM_POLARITY_NUM
} FPwmPolarity;


/* db polarity select */
typedef enum
{
    FPWM_DB_AH = 0, /* no flip */
    FPWM_DB_ALC = 1,/* pwm0 flip */
    FPWM_DB_AHC,    /* pwm1 flip */
    FPWM_DB_AL,     /* pwm0 and pwm1 flip */
    FPWM_DB_POLARITY_NUM
} FPwmDbPolarity;

/* db out mode */
typedef enum
{
    FPWM_DB_OUT_MODE_BYPASS = 0b00, /* by pass */
    FPWM_DB_OUT_MODE_FORBID_RISE = 0b01,/* forbid rise delay */
    FPWM_DB_OUT_MODE_FORBID_FALL = 0b10,/* forbid fall delay */
    FPWM_DB_OUT_MODE_ENABLE_RISE_FALL = 0b11,/* enable rise and fall delay */
    FPWM_DB_OUT_MODE_NUM
} FPwmDbOutMode;

/* db input source select, channel 0 or 1 */
typedef enum
{
    FPWM_DB_IN_MODE_PWM0 = 0,/* db input source choose pwm0 */
    FPWM_DB_IN_MODE_PWM1 = 1,/* db input source choose pwm1 */
    FPWM_DB_IN_MODE_NUM
} FPwmDbInMode;

typedef struct
{
    FPwmDbPolarity db_polarity_sel;/* db polarity select*/
    FPwmDbOutMode db_out_mode;/* db output mode*/
    FPwmDbInMode db_in_mode;/* db input source*/
    u16 db_fall_cycle;/* db falling edge delay cycle */
    u16 db_rise_cycle;/* db rising edge delay cycle */
} FPwmDbVariableConfig;

typedef struct
{
    FPwmTimCtrlMode tim_ctrl_mode;/* tim_ctrl mode, counter mode */
    u16 tim_ctrl_div;/* pwm divider */
    u16 pwm_period;/* pwm period value */
    FPwmCtrlMode pwm_mode;/* pwm mode, compare output */
    FPwmPolarity pwm_polarity;/* pwm compare output polarity */
    FPwmDutySourceMode pwm_duty_source_mode;/* pwm duty value source */
    u16 pwm_pulse;/* pwm pulse value */

} FPwmVariableConfig;

typedef struct
{
    u8 instance_id;/* pwm id */
    uintptr db_base_addr;
    uintptr pwm_base_addr;

    u64 base_clk;
    u32 irq_num[FPWM_CHANNEL_NUM];      /* pwm irq num */
    u32 irq_prority[FPWM_CHANNEL_NUM];  /* pwm irq priority */
    const char *instance_name;/* instance name */

} FPwmConfig; /* Pwm配置 */

typedef void (*FPwmIntrEventHandler)(void *param);

typedef struct
{
    FPwmConfig config;/* Pwm配置 */
    u32 is_ready;/* Pwm初始化完成标志 */

    u8 channel_ctrl_enable[FPWM_CHANNEL_NUM];   /* pwm channel ctrl enable state */

    FPwmIntrEventHandler event_handler[FPWM_INTR_EVENT_NUM];  /* event handler for interrupt */
    void *event_param[FPWM_INTR_EVENT_NUM];   /* parameters ptr of event handler */

} FPwmCtrl;


/* interrupt handler function */
void FPwmIntrHandler(s32 vector, void *args);

/* register the handler function */
void FPwmRegisterInterruptHandler(FPwmCtrl *instance_p, FPwmIntrEventType event_type, FPwmIntrEventHandler handler, void *param);

/* get pwm configs by id */
const FPwmConfig *FPwmLookupConfig(u32 instance_id);

/* DeInitialization function for the device instance */
void FPwmDeInitialize(FPwmCtrl *pctrl);

/*Initializes a specific instance such that it is ready to be used*/
FError FPwmCfgInitialize(FPwmCtrl *pctrl, const FPwmConfig *input_config_p);

/* set pwm db configuration */
FError FPwmDbVariableSet(FPwmCtrl *pctrl, FPwmDbVariableConfig *db_cfg_p);

/* get pwm db configuration */
FError FPwmDbVariableGet(FPwmCtrl *pctrl, FPwmDbVariableConfig *db_cfg_p);

/* set pwm channel configuration */
FError FPwmVariableSet(FPwmCtrl *pctrl, u32 channel, FPwmVariableConfig *pwm_cfg_p);

/* get pwm channel configuration */
FError FPwmVariableGet(FPwmCtrl *pctrl, u32 channel, FPwmVariableConfig *pwm_cfg_p);

/* config pwm pulse, pwm_ccr is less than pwm_period */
FError FPwmPulseSet(FPwmCtrl *pctrl, u32 channel, u16 pwm_ccr);

/* disable pwm */
void FPwmDisable(FPwmCtrl *pctrl, u32 channel);

/* enable pwm */
void FPwmEnable(FPwmCtrl *pctrl, u32 channel);

/* dump some pwm registers value */
void FPwmDump(uintptr base_addr);

/* control gpio output */
void FPwmGpioSet(FPwmCtrl *pctrl, u32 channel, u32 output);

#ifdef __cplusplus
}
#endif

#endif