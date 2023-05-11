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
 * FilePath: fadc.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:29:10
 * Description: This file is for detailed description of the device configuration and driver.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/4/15   init commit
 */

#ifndef FADC_H
#define FADC_H

#include "ftypes.h"
#include "fdebug.h"
#include "ferror_code.h"
#include "fkernel.h"
#include "fparameters.h"


#ifdef __cplusplus
extern "C"
{
#endif


#define FADC_SUCCESS                FT_SUCCESS
#define FADC_ERR_INVAL_PARM         FT_MAKE_ERRCODE(ErrModBsp, ErrBspAdc, 1)
#define FADC_ERR_NOT_READY          FT_MAKE_ERRCODE(ErrModBsp, ErrBspAdc, 2)
#define FADC_ERR_TIMEOUT            FT_MAKE_ERRCODE(ErrModBsp, ErrBspAdc, 3)
#define FADC_ERR_CMD_FAILED         FT_MAKE_ERRCODE(ErrModBsp, ErrBspAdc, 4)
#define FADC_ERR_NOT_SUPPORT        FT_MAKE_ERRCODE(ErrModBsp, ErrBspAdc, 5)

#define FADC_CTRL_PD_DISABLE    0
#define FADC_CTRL_PD_ENABLE     1

#define FADC_CONVERT_COMPLETE(x)    (x=TRUE)
#define FADC_CONVERT_UNCOMPLETE(x)  (x=FALSE)
#define FADC_READ_TIMEOUT           (600)
#define FADC_READ_DELAY             (10)

/* adc interrupt event type */
typedef enum
{
    FADC_INTR_EVENT_COVFIN = 0,    /**< Handler type for convert finish interrupt */
    FADC_INTR_EVENT_DLIMIT = 1,    /**< Handler type for low limit interrupt*/
    FADC_INTR_EVENT_ULIMIT = 2,    /**< Handler type for high limit interrupt*/
    FADC_INTR_EVENT_ERROR  = 3,    /**< Handler type for error interrupt*/

    FADC_INTR_EVENT_NUM
} FAdcIntrEventType;

/* adc convert mode */
typedef enum
{
    FADC_CONTINUOUS_CONVERT = 0,/* continuous conversion*/
    FADC_SINGLE_CONVERT = 1,    /* single conversion*/

    FADC_CONVERT_MODE_NUM

} FAdcConvertMode;

/* adc channel mode */
typedef enum
{
    FADC_MULTI_CHANNEL = 0, /* multi channel conversion*/
    FADC_FIXED_CHANNEL = 1, /* fixed channel conversion*/

    FADC_CHANNEL_MODE_NUM
} FAdcChannelMode;

/* adc base configuration */
typedef struct
{
    u32 instance_id;/* adc id */
    uintptr base_addr;/* adc control register base address*/
    u32 irq_num;/* adc interrupt number */
    u32 irq_prority;/* adc interrupt priority*/
    const char *instance_name;/* instance name */

} FAdcConfig;

typedef struct
{
    u32 convert_interval; /* convert interval time */
    u32 clk_div; /* clock divider, must be even*/
    FAdcConvertMode convert_mode;/*!<  convert mode */
    FAdcChannelMode channel_mode;/*!< channel mode */

} FAdcConvertConfig;

/* adc variable config */
typedef struct
{
    u16 high_threshold; /*!< Configures the ADC analog high threshold value.
                                           This parameter must be a 10-bit value. */
    u16 low_threshold;  /*!< Configures the ADC analog low threshold value.
                                            This parameter must be a 10-bit value. */
} FAdcThresholdConfig;


typedef void (*FAdcIntrEventHandler)(void *param);

typedef struct
{
    FAdcConfig config;/* adc config */
    u32 is_ready;/* adc init ready flag */
    u16 value[FADC_CHANNEL_NUM];  /* adc value */
    boolean convert_complete[FADC_CHANNEL_NUM]; /*!< Specifies whether the conversion is complete> */
    FAdcIntrEventHandler event_handler[FADC_INTR_EVENT_NUM];  /* event handler for interrupt */
    void *event_param[FADC_INTR_EVENT_NUM];   /* parameters of event handler */

} FAdcCtrl;

/* get default configuration of specific adc id */
const FAdcConfig *FAdcLookupConfig(u32 instance_id);

/* DeInitialization function for the device instance */
void FAdcDeInitialize(FAdcCtrl *pctrl);

/* Initializes a specific instance such that it is ready to be used */
FError FAdcCfgInitialize(FAdcCtrl *pctrl, const FAdcConfig *input_config_p);

/* config adc convert parameters */
FError FAdcConvertSet(FAdcCtrl *pctrl, FAdcConvertConfig *convert_config);

/* Set adc channel high_threshold and low_threshold */
FError FAdcChannelThresholdSet(FAdcCtrl *pctrl, FAdcChannel channel, FAdcThresholdConfig *threshold_config);

/* init adc variable configuration */
FError FAdcVariableConfig(FAdcCtrl *pctrl, FAdcConvertConfig *convert_config);

/* enable channel interrupt */
FError FAdcInterruptEnable(FAdcCtrl *pctrl, FAdcChannel channel, FAdcIntrEventType event_type);

/* disable channel interrupt */
FError FAdcInterruptDisable(FAdcCtrl *pctrl, FAdcChannel channel, FAdcIntrEventType event_type);

void FAdcChannelEnable(FAdcCtrl *pctrl, FAdcChannel channel, boolean state);

/* Start adc convert */
void FAdcConvertStart(FAdcCtrl *pctrl);

/* Stop adc convert */
void FAdcConvertStop(FAdcCtrl *pctrl);

/* read adc channel convert result value */
FError FAdcReadConvertResult(FAdcCtrl *pctrl, FAdcChannel channel, u16 *val);

/* read adc channel convert finish count */
FError FAdcReadFinishCnt(FAdcCtrl *pctrl, FAdcChannel channel, u32 *count);

/* read adc channel history limit value, include high limit and low limit */
FError FAdcReadHisLimit(FAdcCtrl *pctrl, FAdcChannel channel, u16 *u_his_limit, u16 *d_his_limit);

/* interrupt handler for the driver */
void FAdcIntrHandler(s32 vector, void *args);

/* register FAdc interrupt handler function */
void FAdcRegisterInterruptHandler(FAdcCtrl *instance_p, FAdcIntrEventType event_type,
                                  FAdcIntrEventHandler handler, void *param);

#ifdef __cplusplus
}
#endif

#endif